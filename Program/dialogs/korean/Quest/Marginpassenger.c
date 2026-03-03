void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "버그다. 반드시 개발자들에게 알려라.";
			link.l1 = "OK";
			link.l1.go = "exit";
		break;
		
		//разговор на палубе
		case "MarginCap":
			dialog.text = "안녕하십니까, 선장님. 저에게 원하시는 것이 있습니까?";
			link.l1 = "그래. 바로 그거야. "+GetAddress_FormToNPC(NPChar)+". 네 배에 내가 꽤 관심 있는 승객이 타고 있더군. 이름은 "+pchar.GenQuest.Marginpassenger.q1Name+". 네 승객을 내 승객으로 삼고 싶다. 네가 괜찮다면, 우리는 여기서 갈라서 다시는 서로 보지 않게 될 거다.";
			link.l1.go = "MarginCap_1";
		break;
	
		case "MarginCap_1":
			dialog.text = "그래? 내가 싫다고 하면 어쩔 건데?";
			link.l1 = "그럼 내 대포 몇 발로 네 결정을 다시 생각하게 만들어 주겠다. 지금 이 순간 네 쪽을 조준하고 있으니 운을 너무 믿지 마라,\n "+GetAddress_FormToNPC(NPChar)+".";
			link.l1.go = "MarginCap_2";
		break;
		
		case "MarginCap_2":
			int MCparam = (7-sti(RealShips[sti(pchar.ship.type)].Class))*100+sti(pchar.ship.Crew.Morale)+sti(pchar.Ship.Crew.Exp.Sailors)+sti(pchar.Ship.Crew.Exp.Cannoners)+sti(pchar.Ship.Crew.Exp.Soldiers);
			int NPCparam = (7-sti(RealShips[sti(npchar.ship.type)].Class))*100+sti(npchar.ship.Crew.Morale)+sti(npchar.Ship.Crew.Exp.Sailors)+sti(npchar.Ship.Crew.Exp.Cannoners)+sti(npchar.Ship.Crew.Exp.Soldiers);
			if (MCparam > NPCparam)//отдаст сам
			{
				dialog.text = "그럼 어쩔 수 없군. 내 선원들의 운명이 한 사람의 운명보다 내겐 더 소중하니까. 하지만 그렇게 쉽게 넘어갈 줄 알지 마! 이 일, 절대 잊지 않겠다!";
				link.l1 = "진정하고, 심장마비나 일으키지 말라고... 내 새 승객을 데려와!";
				link.l1.go = "MarginCap_3";
			}
			else
			{
				dialog.text = "내가 아직 허락할 때 내 배에서 나가는 게 좋을 거요, 나리. 나를 겁주려 들지 마시오. 그리고 내 배를 공격할 생각은 꿈도 꾸지 마시오, 바로 쫓아낼 테니. 내가 아직 기분 좋을 때 썩 꺼지시오!";
				link.l1 = "경고했지. 지금 가는 중이다. 곧 보자, "+GetAddress_FormToNPC(NPChar)+"!";
				link.l1.go = "MarginCap_4";
			}
		break;
	
		case "MarginCap_3":
			DialogExit();
			npchar.Dialog.CurrentNode = "MarginCap_repeat";
			//отдаем пассажира
			sld = GetCharacter(NPC_GenerateCharacter("MarginPass", pchar.GenQuest.Marginpassenger.model, pchar.GenQuest.Marginpassenger.sex, pchar.GenQuest.Marginpassenger.ani, 2, sti(pchar.GenQuest.Marginpassenger.Nation), -1, true, "quest"));
			sld.Dialog.Filename = "Quest\Marginpassenger.c";
			sld.Dialog.currentnode = "MarginPass";
			sld.name = pchar.GenQuest.Marginpassenger.q1Name;
			sld.lastname = "";
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(sld, pchar.location, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			Map_ReleaseQuestEncounter(npchar.id);
			npchar.Abordage.Enable = false; // запрет абордажа
			npchar.ShipEnemyDisable = true;
			npchar.AlwaysFriend = true;
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), -1);
		break;
		
		case "MarginCap_4":
			DialogExit();
			NextDiag.CurrentNode = "MarginCap_repeat";
			pchar.GenQuest.Marginpassenger.Mustboarding = "true";
			AddQuestRecord("Marginpassenger", "5");
			AddQuestUserData("Marginpassenger", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Marginpassenger.ShipType), "Name")+"Acc")));
			AddQuestUserData("Marginpassenger", "sShipName", pchar.GenQuest.Marginpassenger.ShipName);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), -1);
		break;
		
		case "MarginCap_repeat":
			dialog.text = "우린 이미 이 얘기 했잖아, 기억 안 나? 내 배에서 내려!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "MarginCap_repeat";
		break;
		
		case "MarginCap_abordage":
			if (CheckAttribute(pchar, "GenQuest.Marginpassenger.Mustboarding"))
			{
				dialog.text = "아르그, 이 개자식아! 네 짓거리 때문에 지옥에서 불타라!";
				link.l1 = "내가 너한테 승객을 평화롭게 넘길 기회를 줬는데... 네가 내 제안을 거절했지. 이제 모든 책임은 너한테 있다!";
				link.l1.go = "MarginCap_abordage_1";
			}
			else
			{
				dialog.text = "아으, 이 망할 놈아! 왜 이 평화로운 배를 공격한 거냐? 우리에겐 금도 없고 값진 물건도 없어!";
				link.l1 = "하지만 네 배에는 귀중한 인물이 타고 있지..."+pchar.GenQuest.Marginpassenger.q1Name+". 네 승객을 내놔.";
				link.l1.go = "MarginCap_abordage_2";
			}
		break;
		
		case "MarginCap_abordage_1":
			dialog.text = "너... 더러운 해적 놈이구나!";
			link.l1 = "말이 너무 많군, 친구야...";
			link.l1.go = "MarginCap_abordage_3";
		break;
		
		case "MarginCap_abordage_2":
			dialog.text = "그래서 내 배에서 학살을 저질렀다는 건가? 많은 사내들이 죽었어! 이 해적 놈!";
			link.l1 = "말이 너무 많군, 친구야...";
			link.l1.go = "MarginCap_abordage_3";
		break;
		
		case "MarginCap_abordage_3":
			DialogExit();
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "Marginpassenger_GivePrisoner");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "MarginNeed":
			dialog.text = "뭘 원하지, "+GetAddress_Form(NPChar)+"?";
			link.l1 = "너냐 "+pchar.GenQuest.Marginpassenger.q2Name+"?";
			link.l1.go = "MarginNeed_1";
		break;
		
		case "MarginNeed_1":
			dialog.text = "그래, 나야. 신청서를 내고 싶어? 그렇다면 알아둬야 할 게 있어...";
			link.l1 = "잠깐만요, 나리. 제 부탁은 좀 다릅니다... 혹시 이름이 "+pchar.GenQuest.Marginpassenger.q1Name+"?";
			link.l1.go = "MarginNeed_2";
		break;
		
		case "MarginNeed_2":
			switch (pchar.GenQuest.Marginpassenger.sex)
			{
				case "woman":
					dialog.text = "그래, 그녀를 알아... 물론이지! 무슨 일이야?";
					link.l1 = "그녀는 아주 불쾌한 상황에 처했어: 해적들에게 배를 빼앗겼지. 다행히 내가 그 배에 올라타서 그 불쌍한 사람을 구할 수 있었어. 그녀가 네 이름을 알려줬고, 그래서 내가 여기 온 거야.";
					link.l1.go = "MarginNeed_woman";
				break;
				case "man":
					dialog.text = "그래, 이 사람을 아주 잘 알고 있지. 무슨 일인가?";
					link.l1 = "그 자는 아주 곤란한 상황에 처했소. 해적들에게 배를 빼앗겼지. 다행히도 내가 그 배에 올라타서 그 포로를 구출할 기회가 있었소. 그가 내게 자네 이름을 말해주었고, 그래서 내가 여기 온 것이오.";
					link.l1.go = "MarginNeed_man";
				break;
			}
		break;
		
		case "MarginNeed_woman":
			dialog.text = "오, 신이시여! 지금 그녀는 어디에 있지? 왜 그녀를 여기로 데려오지 않았어?";
			link.l1 = "그녀는 안전하다. 그리고 네 질문에 대해서는... 그렇게 간단하지 않아. 내가 직접 그녀를 집으로 데려다줄 수도 있었지만, 이 기회를 너에게 줄 수도 있지. 물론 약간의 보수는 받아야겠지만.";
			link.l1.go = "MarginNeed_woman_1";
		break;
		
		case "MarginNeed_woman_1":
			dialog.text = "흠... 이해가 안 되는데...";
			link.l1 = "왜 안 되겠어? 자네가 나한테 금을 주면, 나는 그 아가씨를 넘기지. 그리고 자네는 이 상황을 유리하게 쓸 수 있을 거야... 자네, 그 아가씨와 결혼하고 싶지? 맞지? 나는 그 돈으로 내 배를 수리할 거야. 해적들과 싸울 때 손상됐거든.";
			link.l1.go = "MarginNeed_money";
		break;
		
		case "MarginNeed_man":
			dialog.text = "오, 맙소사! 지금 그는 어디 있지? 왜 그를 여기로 데려오지 않았어?";
			link.l1 = "그는 무사하다. 그리고 네 질문에 대해서는... 그렇게 간단하지 않아. 내가 직접 그를 집으로 데려다줄 수도 있었지만, 네가 그 가족에게 관심이 있으니 이번 기회를 너에게 주마. 물론 적당한 보수는 받아야겠지.";
			link.l1.go = "MarginNeed_man_1";
		break;
		
		case "MarginNeed_man_1":
			dialog.text = "흠... 이해가 안 되는데...";
			link.l1 = "왜 안 하겠어? 네가 나한테 금으로 값을 치르면, 나는 네 친구를 넘겨주지. 그리고 넌 이 상황을 네 이익으로 이용할 수 있을 거야. 나도 정보가 좀 있거든... 그 돈으로 내 배를 수리할 거야. 해적들과 싸울 때 손상됐거든.";
			link.l1.go = "MarginNeed_money";
		break;
		
		case "MarginNeed_money":
			dialog.text = "그래, 그래... 그래서 얼마를 원하는 거지?";
			link.l1 = "명심해, 나는 페소가 아니라 두블룬을 원해.";
			link.l1.go = "MarginNeed_money_1";
		break;
		
		case "MarginNeed_money_1":
			dialog.text = "좋아, 좋아... 그래서 도블론을 몇 개나 원하는 거야?";
			Link.l1.edit = 1;			
			link.l1 = "";
			link.l1.go = "MarginNeed_money_2";
		break;
		
		case "MarginNeed_money_2":
		iTemp = sti(dialogEditStrings[1]);
		int iSum = makeint(sti(pchar.GenQuest.Marginpassenger.Dublon)*5*stf(pchar.GenQuest.Marginpassenger.Chance));
		if (iTemp <= 0)
		{
			dialog.text = "아주 웃기네. 좋아, 네 농담이 진짜 웃겼다고 치자. 잘 가라!";
			link.l1 = "흠...";
			link.l1.go = "MarginNeed_exit";
			break;
		}
		if (iTemp > 0 && iTemp <= iSum)
		{
			if (hrand(2) > 1) // Addon-2016 Jason уменьшаем раздачу дублонов
			{
				dialog.text = "좋아, 동의하지. 필요한 금액은 가지고 있어. 어디 있지\n "+pchar.GenQuest.Marginpassenger.q1Name+"?";
				link.l1 = "지금쯤 부두에 있을 거야. 그러니 가서 승객을 데려와.";
				link.l1.go = "MarginNeed_dublon";
			}
			else
			{
				dialog.text = "미안하지만, 그렇게 많은 두블룬은 없어. 페소로 해도 되겠나?";
				link.l1 = "나는 두블룬을 원하지만, 선박 관리인은 페소도 받을 테지... 내게 줘.";
				link.l1.go = "MarginNeed_peso";
				link.l2 = "아니, 나는 두블룬만 필요해.";
				link.l2.go = "MarginNeed_dublon_exit";
			}
			break;
		}
		if (iTemp > iSum && iTemp < 1000)
		{
			dialog.text = "유감이지만, 나는 그런 돈이 없어. 그래서 아무리 그러고 싶어도 네 제안을 받아들일 수 없어.";
			link.l1 = "흠...";
			link.l1.go = "MarginNeed_exit";
			break;
		}
		if (iTemp > 1000 && iTemp < 3000)
		{
			dialog.text = "나리, 자기가 무슨 말을 하는지나 아시오? 이 금액이 얼마나 터무니없이 큰지 알고 있소? 당장 꺼져!";
			link.l1 = "흠...";
			link.l1.go = "MarginNeed_exit";
			break;
		}
			dialog.text = "음... 나리, 당장 의사를 찾아가셔야 합니다. 열이 아주 심하신 것 같거나... 아무튼, 의사가 필요하십니다. 그리고 저는 너무 바쁩니다. 그럼 이만!";
			link.l1 = "흠...";
			link.l1.go = "MarginNeed_exit";
		break;
		
		case "MarginNeed_dublon":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			npchar.lifeday = 0;
			sld = characterFromId("MarginPass");
			RemovePassenger(Pchar, sld);
			sld.lifeday = 0;
			iTemp = sti(dialogEditStrings[1]);
			TakeNItems(pchar, "gold_dublon", iTemp);
			AddQuestRecord("Marginpassenger", "9");
			AddQuestUserData("Marginpassenger", "sSum", iTemp);
			CloseQuestHeader("Marginpassenger");
			DeleteAttribute(Pchar, "GenQuest.Marginpassenger");
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
		break;
		
		case "MarginNeed_peso":
			dialog.text = "여기 있습니다, 원하던 대로 전액을 페소로 준비했소... 어디 있소\n "+pchar.GenQuest.Marginpassenger.q1Name+"?";
			link.l1 = "지금쯤 부두에 있을 거야. 그러니 가서 승객을 데려오면 돼.";
			link.l1.go = "MarginNeed_peso_1";
		break;
		
		case "MarginNeed_peso_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			npchar.lifeday = 0;
			sld = characterFromId("MarginPass");
			RemovePassenger(Pchar, sld);
			sld.lifeday = 0;
			iTemp = sti(dialogEditStrings[1])*500;
			AddMoneyToCharacter(pchar, iTemp);
			AddQuestRecord("Marginpassenger", "10");
			AddQuestUserData("Marginpassenger", "sSum", FindRussianMoneyString(iTemp));
			CloseQuestHeader("Marginpassenger");
			DeleteAttribute(Pchar, "GenQuest.Marginpassenger");
			AddCharacterExpToSkill(pchar, "Fortune", 80);//везение
		break;
		
		case "MarginNeed_dublon_exit":
			dialog.text = "네 제안은 받아들일 수 없겠군, 정말 그러고 싶어도 말이야. 잘 가라!";
			link.l1 = "음...";
			link.l1.go = "MarginNeed_exit";
		break;
		
		case "MarginNeed_exit":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			AddQuestRecord("Marginpassenger", "11");
			AddQuestUserData("Marginpassenger", "sName2", pchar.GenQuest.Marginpassenger.q2Name);
			AddQuestUserData("Marginpassenger", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.City));
			// belamour gen: Добряку недолго осталось -->
			if(CheckAttribute(pchar, "questTemp.LongHappy"))
			{
				AddQuestUserData("Marginpassenger", "sBaron", "to Puerto Principe, to the Black Pastor");
			}
			else
			{
				AddQuestUserData("Marginpassenger", "sBaron", "to Le Francois, to Kindly Jacques");
			}
			// <-- belamour gen
			pchar.GenQuest.Marginpassenger = "cabin";
		break;
		
		case "MarginPass":
			dialog.text = "뭐지... 여기서 무슨 일이 벌어지고 있는 거야?!";
			link.l1 = "아주 간단하네, "+NPCharSexPhrase(NPChar,"친구","소녀")+". 이제 너는 내 소중한 승객이야. 감시받는 승객이지. 저항하려 들면 화물칸에 처박힐 줄 알아.";
			link.l1.go = "MarginPass_1";
		break;
		
		case "MarginPass_1":
			dialog.text = "내가 네 포로라는 말이냐?";
			link.l1 = "오, 아니야. 물론 아니지. 죄수가 아니라 소중한 손님이지. 아주 귀중한 손님이야...";
			link.l1.go = "MarginPass_2";
		break;
		
		case "MarginPass_2":
			dialog.text = "너... 네 짓에 대한 대가를 치르게 될 거야!";
			link.l1 = "또 틀렸군,"+NPCharSexPhrase(NPChar,", 친구",", 그대여")+". 나는 돈을 내지 않을 거다, 하지만 돈은 받아야지. 말은 그만하고, 네 선실로 가!";
			link.l1.go = "MarginPass_3";
		break;
		
		case "MarginPass_3":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "", "", "none", "", "", "", 1.0);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			pchar.quest.Marginpassenger_InWorldOver.over = "yes"; //снять прерывание
			pchar.quest.Marginpassenger_Sink.over = "yes"; //снять прерывание
			pchar.GenQuest.Marginpassenger = "take";
			if (rand(2) == 1) pchar.GenQuest.Marginpassenger.lose = "true";
			else Marginpassenger_CreateNeedman();
			if (CheckAttribute(pchar, "GenQuest.Marginpassenger.Boarding")) AddQuestRecord("Marginpassenger", "6");
			else AddQuestRecord("Marginpassenger", "4");
			AddQuestUserData("Marginpassenger", "sName1", pchar.GenQuest.Marginpassenger.q1Name);
			AddQuestUserData("Marginpassenger", "sShipName", pchar.GenQuest.Marginpassenger.ShipName);
			AddQuestUserData("Marginpassenger", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Marginpassenger.ShipType), "Name")+"Acc")));
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
