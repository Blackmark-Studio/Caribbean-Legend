// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	int i,n;
	string month;
	
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("무슨 질문인데?","무슨 일이오, "+GetAddress_Form(NPChar)+"?"),"이미 나에게 질문을 하려고 했잖아 "+GetAddress_Form(NPChar)+"...","오늘만 세 번째로 이 질문을 꺼내는군...","이봐, 항구 일에 대해 할 말이 없으면 쓸데없는 질문으로 귀찮게 하지 마라.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("내 마음이 바뀌었소.","나랑 할 말이 없어."),"신경 쓰지 마.","정말, 벌써 세 번째군...","미안하지만, 지금은 항구 일에 관심 없어.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.Slavetrader == "FindRatPortobello_1")
            {
                link.l1 = "안녕하십니까. 프랑수아 곤티에 선장이 어디 있는지 알고 싶습니다. 중요한 일이 있습니다.";
                link.l1.go = "Portobello_ratP_1";
            }
			// belamour legengary edition на пару с Акулой -->
			if(CheckAttribute(pchar,"questTemp.SharkGoldFleet"))
			{
				if(pchar.questTemp.SharkGoldFleet == "toPBPortOffice" || pchar.questTemp.SharkGoldFleet == "KillCurier")
				{
					link.l1 = "나는 상인인데, 카라카스에서 왔소, 그리고 이 항구 관리소의 당신 동료가 당신께 서신을 전해 달라고 부탁했소 ...";
					link.l1.go = "SharkGoldFleet";
				}
				if(pchar.questTemp.SharkGoldFleet == "MoneySpeak")
				{
					link.l1 = "그래, 나는 대금 받으러 왔소.";
					link.l1.go = "SharkGoldFleet_11";
				}
			}
			//<-- на пару с Акулой
		break;

		case "Portobello_ratP_1":
			dialog.text = "중요한 일이라고? 어디 보자. 음... 프랑수아 곤티에, 코르벳함 '"+pchar.questTemp.Slavetrader.ShipName+"... 내 기록에 따르면, 곤티에르 나리는 자메이카로 향하고 있었소.";
			link.l1 = "고마워! 정말 큰 도움이 됐어!";
			link.l1.go = "exit";
			pchar.questTemp.Slavetrader = "FindRatJamaica";
			AddQuestRecord("Slavetrader", "21_3");
			AddQuestUserData("Slavetrader", "sShip", pchar.questTemp.Slavetrader.ShipName);
		break;
		// на пару с Акулой -->
		case "SharkGoldFleet":
			if(!bImCasual) pchar.quest.SharkGoldFleetToPB10.over = "yes"; 
			RemoveItems(PChar, "letter_1", 1);
			ChangeItemDescribe("letter_1", "itmdescr_letter_1");
			dialog.text = "아, 그래, 드디어 왔군! 자네가 상인이라고? 또다시 전령 비용 아끼겠다고 출하를 마지막 빌어먹을... 그래, 물론이지! 맞는 말이야. 그런데 이렇게 촉박한 시간에 내가 그 물자로 함대를 어떻게 장비하란 말인가?...";
			link.l1 = "무책임하게 들리는데...";
			link.l1.go = "SharkGoldFleet_01";
		break;
		
		case "SharkGoldFleet_01":
			dialog.text = "그렇게 말할 수도 있지! 뭐, 어쩔 수 없군. 언젠가 다시 만나게 될 거야... 나 혼잣말이니 신경 쓰지 마. 이봐, 혹시 돌아갈 생각 있어?";
			link.l1 = "사실은 여기서 물건을 팔 생각이었고, 그 다음엔… 그래, 카라카스로 돌아가려고 했지…";
			link.l1.go = "SharkGoldFleet_02";
		break;
		
		case "SharkGoldFleet_02":
			dialog.text = "좋아! 이제 내가 답장을 쓸 테니, 그걸 네가 다시 전달해 줘야 하네. 그러니... 열흘 안에 꼭 전해 주게. 그렇지 않으면 그쪽에서 아무것도 할 시간이 없을 테니... 그리고 자네 이름을 말하게.";
			if(pchar.questTemp.SharkGoldFleet == "KillCurier")
			{
				link.l1 = "내 이름은 "+GetFullName(pchar)+".";
				link.l1.go = "SharkGoldFleet_03";
			}
			else
			{
				link.l1 = "내 이름은 Andreas Garcia요.";
				link.l1.go = "SharkGoldFleet_09";
			}
		break;
		
		case "SharkGoldFleet_03":
			TakeNItems(pchar, "letter_2", 1);
			ChangeItemDescribe("letter_2", "itmdescr_letter_SharkGoldFleet_2");
			dialog.text = "잠깐만... 기록했소. 여기 있소. 기억하시오: 열흘이오! 그동안 자네가 가져온 것을 좀 더 자세히 읽어보겠소.";
			link.l1 = "그래, 기억나지. 안녕!";
			link.l1.go = "SharkGoldFleet_04";
		break;

		case "SharkGoldFleet_04":
			dialog.text = "잠깐만... 이해가 안 되는데... 다시 한 번, 이름이 뭐라고 했지?";
			link.l1 = "나?.. 음... 그게 그렇게 중요한가?";
			link.l1.go = "SharkGoldFleet_05";
		break;
		
		case "SharkGoldFleet_05":
			n = GetAddingDataDay(0,0,21);
			if(n<21) i = GetAddingDataMonth(0,1,0);
			else i = GetDataMonth();
			month = XI_ConvertString("MonthGen_" + i);
			pchar.questTemp.SharkGoldFleet.Date = ""+n+" "+month+"";
			SetFunctionTimerCondition("SharkGoldFleet1269fail", 0, 0, 22, false);
			SetFunctionTimerCondition("SGF_FleetTime", 0, 0, 21, false);
			if(!bImCasual) SetFunctionTimerCondition("SharkGoldFleetToCPO10", 0, 0, 10, false);
			else NewGameTip("Exploration mode: timer is disabled.");
			dialog.text = "매우 중요하오! 이렇게 적혀 있소... 그러니... "+n+" "+month+"... 아니, 그게 아니야... 12, 50, 69, 55... 그런데 어디 있지... 아, 여기 있군! 이 편지는 반드시 선장이 전달해야 해 "+pchar.questTemp.SharkGoldFleet.CurierName+" "+pchar.questTemp.SharkGoldFleet.Curierlastname+". 그리고 이름이 뭐라고 했지... "+GetFullName(pchar)+"?";
			link.l1 = "뭔가 착오가 있었던 것 같은데...";
			link.l1.go = "SharkGoldFleet_06";
		break;
		
		case "SharkGoldFleet_06":
			DeleteAttribute(pchar,"questTemp.SharkGoldFleet.CurierName");
			DeleteAttribute(pchar,"questTemp.SharkGoldFleet.Curierlastname");
			dialog.text = "아니, 실수일 리 없어. 내가 준 편지를 돌려줘. 이 일을 알아봐야겠어!";
			link.l1 = "자, 가자... 내가 전달할 테니, 다 괜찮을 거야.";
			link.l1.go = "SharkGoldFleet_07";
		break;
		
		case "SharkGoldFleet_07":
			dialog.text = "안 돼! 편지를 내게 돌려줘! 경비병들아!!!";
			link.l1 = "아, 힘든 길을 택하겠다는 거군?";
			link.l1.go = "SharkGoldFleet_08";
		break;
		
		case "SharkGoldFleet_08":
			DialogExit();
			pchar.questTemp.SharkGoldFleet = "DifficultVar";
			LICENSE_AddViolation();
			for (i=1; i<=2; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("Sold"+i, "sold_" + NationShortName(SPAIN) + "_" + (rand(1) + 1), "man", "man", sti(pchar.rank), SPAIN, 0, true, "soldier"));
				SetFantomParamFromRank(sld, sti(pchar.rank), true);         
				ChangeCharacterAddressGroup(sld, pchar.location, "goto",  "goto3");
				LAi_SetWarriorType(sld); 
				LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
				LAi_group_Attack(sld, Pchar);
			}
			LAi_group_Attack(NPChar, Pchar);
			SetNationRelation2MainCharacter(SPAIN, RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
			SetFunctionExitFromLocationCondition("SharkGoldFleetExitPO", pchar.location, false);
		break; 
		
		case "SharkGoldFleet_09":
			dialog.text = "잠깐만... 됐네. 답신에 네 이름을 적어두겠다. 여기 있다. 명심해라, 열흘밖에 없어! 그동안 네가 가져온 걸 좀 더 자세히 읽어보겠다.";
			link.l1 = "그래, 기억나. 안녕!";
			link.l1.go = "SharkGoldFleet_10";
		break;
		
		case "SharkGoldFleet_10":
			DialogExit();
			pchar.questTemp.SharkGoldFleet = "MoneySpeak";
			TakeNItems(pchar, "letter_2", 1);
			ChangeItemDescribe("letter_2", "itmdescr_letter_SharkGoldFleet_2");
			AddQuestRecord("SharkGoldFleet", "17");
			chrDisableReloadToLocation = true;
			bDisableFastReload = true;
		break;
		
		case "SharkGoldFleet_11":
			dialog.text = "지불?..";
			link.l1 = "카라카스에서 당신 동료가 편지 배달 비용을 지불해 줄 거라고 말했소.";
			link.l1.go = "SharkGoldFleet_12";
		break;
		
		case "SharkGoldFleet_12":
			dialog.text = "아니, 거긴 완전히 미친 놈들이야! 이제 내가 그놈들 때문에 돈을 내야 한다니!";
			link.l1 = "...";
			link.l1.go = "SharkGoldFleet_13";
		break;
		
		case "SharkGoldFleet_13":
			dialog.text = "그래서 그들이 너한테 얼마를 약속했지?";
			link.l1 = "오천 페소.";
			link.l1.go = "SharkGoldFleet_14";
			link.l2 = "만 페소요.";
			link.l2.go = "SharkGoldFleet_15";
		break;
		
		case "SharkGoldFleet_14":
			pchar.questTemp.SharkGoldFleet = 5000;
			dialog.text = "분명히 저놈들은 내 돈으로 거기서 살기로 한 모양이야... 사신을 보내는 데 돈 쓰는 것도 싫다며, 이런 일까지 지나가는 상인선에 맡기더니, 결국 비용까지 나한테 떠넘기잖아! 내가 저놈들 고발장을 아바나에 써 보내겠어!";
			link.l1 = "당신의 분노는 이해하오, 나리. 하지만 내가 무엇을 해야 하오?";
			link.l1.go = "SharkGoldFleet_16";
		break;
		
		case "SharkGoldFleet_15":
			pchar.questTemp.SharkGoldFleet = 10000;
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			ChangeOfficersLoyality("bad", 1);
			dialog.text = "분명히 저놈들 내 돈으로 거기서 살기로 한 모양이군... 심부름꾼에게 돈 쓰는 것도 아까워서 지나가는 상선에나 이런 걸 맡기더니, 결국 비용까지 나한테 떠넘기잖아! 내가 하바나에 저놈들 고발장 써 올릴 거야!";
			link.l1 = "나리, 분노하신 건 이해하오. 하지만 제가 무엇을 해야 하오?";
			link.l1.go = "SharkGoldFleet_16";
		break;
		
		case "SharkGoldFleet_16":
			dialog.text = "아르, 카라카스의 누에바 에스파냐 관리들의 탐욕은 네 잘못이 아니지. 하지만 지금 당장 그만한 돈은 없어. 자금은 내일에나 도착할 거야... 여기서 잠깐 기다려 줘, 내가 지금 돈꾼에게 다녀올 테니 곧 돌아오겠어.";
			link.l1 = "...";
			link.l1.go = "SharkGoldFleet_17";
		break;
		
		case "SharkGoldFleet_17":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorTurnToLocator(pchar, "reload", "reload1");
			LAi_SetStayType(npchar);
			ChangeCharacterAddressGroup(npchar, pchar.location, "goto", "goto2");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "reload", "reload1","SGF_toUsurer", -1);
		break;
		
		case "SharkGoldFleet_18":
			AddMoneyToCharacter(pchar, makeint(pchar.questTemp.SharkGoldFleet));
			n = GetAddingDataDay(0,0,21);
			if(n<21) i = GetAddingDataMonth(0,1,0);
			else i = GetDataMonth();
			month = XI_ConvertString("MonthGen_" + i);
			pchar.questTemp.SharkGoldFleet.Date = ""+n+" "+month+"";
			SetFunctionTimerCondition("SharkGoldFleet1269fail", 0, 0, 22, false);
			SetFunctionTimerCondition("SGF_FleetTime", 0, 0, 21, false);
			if(!bImCasual) SetFunctionTimerCondition("SharkGoldFleetToCPO10", 0, 0, 10, false);
			else NewGameTip("Exploration mode: timer is disabled.");
			AddQuestRecord("SharkGoldFleet", "18");
			AddQuestUserData("SharkGoldFleet", "date", pchar.questTemp.SharkGoldFleet.Date);
			LAi_SetHuberType(npchar);
			Lai_SetPlayerType(pchar);
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			dialog.text = "기다리게 해서 죄송합니다. 여기 당신의\n "+makeint(pchar.questTemp.SharkGoldFleet)+" 에잇 피스지. 그리고 이번 경우에는, 그놈들이 직접 카라카스에서 대가를 치르게 될 거다. 내가 그렇게 했다고 전해라.";
			link.l1 = "좋아요, 전해드리겠습니다. 감사합니다, 행운을 빕니다!";
			link.l1.go = "exit";
			pchar.questTemp.SharkGoldFleet = "LightVar";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
