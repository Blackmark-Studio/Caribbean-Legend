// диалог коменданта форта
void ProcessDialogEvent()
{
	int amount, iGunQty, iGunGoods, iGunPrice, iTemp;
	int iTest;
	ref NPChar, sld, location;
	ref arItem;
	ref rColony;
	aref Link, NextDiag;
	string sTemp;
	float locx, locy, locz;
	bool  ok;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
   /*NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Prison\" + NPChar.City + "_Prison.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}*/
    // вызов диалога по городам <--

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "NoMoreTalkExit":
			LAi_CharacterDisableDialog(npchar);
			DialogExit();
		break;
		
		case "First time":
			location = &Locations[FindLocation(pchar.location)];
			if (rand(4) == 4 && GetNpcQuestPastDayParam(location, "gun_date") > 365 && !CheckAttribute(pchar, "questTemp.PrisonGun"))
			{
				dialog.text = RandPhraseSimple(RandPhraseSimple("이봐, 너랑 중요한 일이 있어. 네가 도와줄 수 있길 바란다.","선장님, 꽤 이익이 되는 제안을 드려도 되겠습니까?"),RandPhraseSimple("중요한 일에 대해 당신이 우리를 도와줄 수 있을 것 같군.","선장님, 저에게는 당신과 저 모두에게 꽤 이득이 될 수 있는 섬세한 제안이 있습니다."));					
				link.l1 = "자, 할 말 있으면 해 봐. 그럼 어떻게 할지 보자...";
				link.l1.go = "GiveTaskGun";
				location.quest.PrisonGun = "Target"; 
				SaveCurrentNpcQuestDateParam(location, "gun_date");
				break;
			}
		
			dialog.text = RandPhraseSimple("나는 요새의 사령관이다. 무슨 일로 왔나?","무슨 일로 왔지? 여기 왜 온 거야?");
			link.l1 = "아, 아무것도 아니야. 그냥 마을이랑 주변을 둘러보고 있었어. 정말 우연히 여기 오게 된 거야.";
			//belamour legendary edition диалоги, если герой имеет звания и заслуги перед отечеством -->
			// Офицер с патентом
			if(IsOfficerFullEquip())
			{
				dialog.text = "요새에 오신 것을 환영합니다, 선장님. 필요한 것이 있습니까?";
				link.l1 = "아니, 아무것도 아니야, 그냥 지나가다가 들렀어.";
			}
			// вице-адмирал
			if(isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation))
			{
				dialog.text = "안녕하십니까, 부제독님! 명령이 있으십니까?";
				link.l1 = "아니요, 장교 나리, 명령은 없습니다. 저는 그냥 요새를 보러 왔습니다.";
			}
			// генерал-губернатор
			if(CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE)
			{
				dialog.text = "총독 각하! 요새는 완벽하게 정비되어 있습니다. 명령이 있으십니까?";
				link.l1 = "무사해서 다행이네, 장교. 특별한 명령은 없고, 그냥 요새 상태를 확인하러 들렀어.";
			}
			// <-- legendary edition
			link.l1.go = "exit";
			//Jason --> мини-квест Дефицитный товар
			if (CheckAttribute(pchar, "questTemp.Wine.bottle") && NPChar.location == pchar.questTemp.Wine.City + "_ammo" && GetQuestPastDayParam("questTemp.Wine_bottle") < 5)
			{
				link.l11 = "장교님께 흥미로운 정보를 드릴 게 있습니다. 당신 부하 중 한 명이, "+pchar.questTemp.Wine.SName+" 저를 통해 마을에서 포도주를 사 오라고 부탁했습니다. 나리의 명령을 생각해 보면...";
				link.l11.go = "Wine_prison";
			}
			// <-- мини-квест Дефицитный товар
			// Карибские нравы
			if (CheckAttribute(pchar, "questTemp.Trial") && pchar.questTemp.Trial == "fraht" && NPChar.location == "portpax_ammo")
			{
				link.l11 = "안녕하세요, 장교님. 저는 바스테르 식민지에서 왔으며, 제라르 르크루아라는 사람의 명령을 받고 왔습니다. 제 화물칸에 당신을 위한 화약과 폭탄이 실려 있습니다...";
				link.l11.go = "trial";
			}
			// Опасный груз -->
			if (pchar.location == "Cumana_Ammo")
			{
				if (pchar.questTemp.zpq != "begin" && pchar.questTemp.zpq != "failed" && pchar.questTemp.zpq != "completed")
				{
					link.l2 = "걱정이 많아 보이는데, 장교님. 내가 어떻게 도와드릴까요?";
					link.l2.go = "zpq_prs1";
				}
				if (pchar.questTemp.zpq == "begin" && GetSquadronGoods(pchar, GOOD_POWDER) >= 15000 && GetQuestPastDayParam("pchar.questTemp.zpq") >= 7)
				{
					link.l3 = "화약 전량을 모두 운반했다는 보고를 드릴 준비가 되었습니다. 내 배는 하역 준비가 되어 있습니다.";
					link.l3.go = "zpq_ex";
				}
				if (pchar.questTemp.zpq == "begin")
				{
					link.l4 = "화약 거래를 취소하고 싶어. 이건 너무 골치 아프군.";
					link.l4.go = "zpq_fld2";
				}
			}
			// <-- Опасный груз
			NextDiag.TempNode = "First time";
		break;

		// --> Орудия для форта
		case "GiveTaskGun":
			dialog.Text = LinkRandPhrase("보시다시피, 요새의 대포들은 꽤 낡았습니다. 재무관에서 교체 자금을 배정해 주었지만, 어디서 새 대포를 구입해야 할지 전혀 모르겠군요. 우리 식민지에서는 필요한 만큼의 대포를 구할 방법이 없습니다. 그래서 당신이 나포한 배에서 얻은 대포들이 우리에게 아주 쓸모가 있을 것 같다고 생각했습니다.","요새의 대포를 교체해야 해. 자금은 이미 배정됐지만, 알다시피... 우리 식민지에서는 필요한 수량을 구하는 게 정말 불가능하지.","낡은 요새 대포를 교체하라는 임무를 받았는데, 아무리 찾아도 충분한 수를 구할 수가 없어.");
			Link.l1 = "흠... 좀 더 자세히 말해줄 수 있나? 구경, 수량, 가격은?";
			Link.l1.go = "GiveTaskGun_1";
			pchar.questTemp.PrisonGun = true;
			SaveCurrentQuestDateParam("pchar.questTemp.PrisonGun");
		break;
			
		case "GiveTaskGun_1":
			GetGunType();
			pchar.questTemp.PrisonGun.Sum = makeint(sti(pchar.questTemp.PrisonGun.Price)*sti(pchar.questTemp.PrisonGun.Qty));
			pchar.questTemp.PrisonGun.Luck = rand(4);
			pchar.questTemp.PrisonGun.Id = npchar.location;
			dialog.Text = "필요해 "+pchar.questTemp.PrisonGun.Text+", 수량은 "+sti(pchar.questTemp.PrisonGun.Qty)+"  정확히 그 수만큼. 금화 더블룬으로 지불하지. "+sti(pchar.questTemp.PrisonGun.Price)+" 한 조각당입니다. 그러면 총 "+FindRussianDublonString(sti(pchar.questTemp.PrisonGun.Sum))+" 전부 합해서. 어때? 아, 그리고 한 가지 더 있는데 - 나는 한 달이 지나야 전부 가져가겠네. 돈이 아직 도착하지 않았거든.";
			Link.l1 = RandPhraseSimple("아니오, 경관 나리, 당신의 제안에는 전혀 관심이 없습니다... 유감이군요.","솔깃하긴 하지만, 사양하겠소. 내 이유는 나만 알고 있겠소.");
			Link.l1.go = "exit_gun";
			Link.l2 = RandPhraseSimple("음, 그 제안은 확실히 흥미롭군. 거래 성립이오.","내가 맡아야겠군. 그렇게 어렵지도 않고, 분명히 이득이 되니까.");
			Link.l2.go = "GiveTaskGun_2";
		break;
			
		case "exit_gun":
			dialog.Text = "정말 안타깝군요, 선장님. 나는 당신을 믿고 있었소. 그리고... 이 대화가 요새 안에서만 머물길 바라오.";
			Link.l1 = "그건 굳이 상기시켜 줄 필요 없어. 안부 전해.";
			Link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.PrisonGun");
			NextDiag.TempNode = "First time";
		break;
			
		case "GiveTaskGun_2":
			dialog.Text = "좋아, 그럼 그렇게 합시다! 특별한 조건은 없으니, 다만 반년을 넘기지 않도록 해주시오. 그리고 이건 철저히 비밀이라는 점, 이해하고 있겠지?";
			Link.l1 = "물론이지. 또 보자, 사령관.";
			Link.l1.go = "exit";
			ReOpenQuestHeader("PrisonGun");
			AddQuestRecord("PrisonGun", "1");
			AddQuestUserData("PrisonGun", "sSex", GetSexPhrase("",""));
			AddQuestUserData("PrisonGun", "sName", GetFullName(npchar));
			AddQuestUserData("PrisonGun", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData("PrisonGun", "sQty", makeint(pchar.questTemp.PrisonGun.Qty));
			AddQuestUserData("PrisonGun", "sSum", makeint(pchar.questTemp.PrisonGun.Sum));
			AddQuestUserData("PrisonGun", "sText", pchar.questTemp.PrisonGun.Text);
			NextDiag.TempNode = "First time";
		break;	
		
		case "CheckGun":
			if (GetQuestPastDayParam("pchar.questTemp.PrisonGun") < 30)
			{
				dialog.Text = "한 달이 지나기 전에는 돌아오지 말라고 했잖아!";
				Link.l1 = "젠장! 내가 너무 바빴는데\n"+GetSexPhrase("","")+", 내가 하나 잃어버린"+GetSexPhrase("","")+" 시간 가는 줄 몰랐네... 미안하지만, 약속한 대로 나중에 다시 올게.";
				Link.l1.go = "exit";
				NextDiag.TempNode = "First time";
				break;
			}
			if (GetQuestPastDayParam("pchar.questTemp.PrisonGun") > 180)
			{
				dialog.Text = "흠... 있잖아, 우리가 '거래'를 한 지도 벌써 반년이 넘었어. 나는 이미 대포를 샀지. 내가 정말로 너를 영원히 기다릴 거라고 생각했어?";
				Link.l1 = "젠장! 이제 저놈들을 어쩌란 말이야?";
				Link.l1.go = "TakeGun_late";
				break;
			}
			iGunGoods = pchar.questTemp.PrisonGun.Goods;
			amount = GetSquadronGoods(Pchar, iGunGoods) - sti(pchar.questTemp.PrisonGun.Qty);
			sTemp = sti(pchar.questTemp.PrisonGun.Qty);
			iTest = FindColony(NPChar.City); // город
			
			if (iTest != -1)
			{
				rColony = GetColonyByIndex(iTest);
			}
			ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
			if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
				dialog.Text = "그래, 나 도와줄 준비됐어?";
				if (amount < 0)
				{
					Link.l1 = "아니, 아직 진행 중이야. 우리 거래가 여전히 유효한지 확인하고 싶었을 뿐이야.";
					Link.l1.go = "exit";
				}
				else
				{
					Link.l1 = "그래. 전부 화물칸에 있어 - "+sTemp+" 약속한 대로, 단위들.";
					Link.l1.go = "TakeGun";
				}
			}
			else 
			{
				dialog.text = "항구에 네 배가 안 보여. 우리가 그 대포를 정글로 끌고 가자는 거냐? 어서 우리 항구로 가서 돌아와라.";
				link.l1 = "내 배는 섬 반대편에 있어. 내가 항구로 가져올게.";
				link.l1.go = "exit";
			}
		break;
		
		case "TakeGun":
			if (pchar.questTemp.PrisonGun.Luck == 4)
			{
				dialog.Text = RandPhraseSimple("있잖아, 정말 난처하지만 우리 거래에서 빠져야겠어. 방금 재정 감사가 있었는데, 그런 일에 얼마나 깐깐한지 알잖아. 내가 아무것도 할 수가 없어. 미안해.","선장님, 그게 말이지요... 음, 대도시에서 우리에게 대포가 보내져서, 어쩔 수 없이 제가 그걸 샀습니다. 바가지 쓴 가격이었지만... 선장님을 실망시켜 정말 죄송합니다... 저도 마음이 편치 않습니다.");
				Link.l1 = "젠장! 이제 저놈들을 어쩌란 말이야?";
				Link.l1.go = "TakeGun_no";
			}
			else
			{
				dialog.Text = RandPhraseSimple("훌륭하군. 내가 주둔지에서 분대를 보내 물건을 내리게 하겠다.","훌륭하군. 내 병사들이 대포를 내리는 걸 도와줄 거야.");
				Link.l1 = "지불할 돈을 준비했나?";
				Link.l1.go = "TakeGun_1";
			}
		break;
		
		case "TakeGun_no":
			dialog.Text = "모르겠어. 조선소에 팔든, 무역선을 장만하든, 침몰시키든... 정말로 아무 생각 없어. 그리고 제발, 이 거래에 대해 아무한테도 말하지 마.";
			Link.l1 = "오, 정말이야! 할 말을 잃었군!";
            Link.l1.go = "exit";
			AddQuestRecord("PrisonGun", "3");
			CloseQuestHeader("PrisonGun");
			DeleteAttribute(pchar, "questTemp.PrisonGun");
			NextDiag.TempNode = "First time";
		break;
		
		case "TakeGun_late":
			dialog.Text = "모르겠어. 그건 네 문제야. 팔든, 버리든, 바다에 가라앉히든, 난 정말 상관 안 해.";
			Link.l1 = "아, 그건 정말 시간 낭비였군...";
            Link.l1.go = "exit";
			AddQuestRecord("PrisonGun", "4");
			AddQuestUserData("PrisonGun", "sSex", GetSexPhrase("",""));
			AddQuestUserData("PrisonGun", "sName", GetFullName(npchar));
			CloseQuestHeader("PrisonGun");
			DeleteAttribute(pchar, "questTemp.PrisonGun");
			NextDiag.TempNode = "First time";
		break;
		
		case "TakeGun_1":
			iGunGoods = pchar.questTemp.PrisonGun.Goods;
			amount = sti(pchar.questTemp.PrisonGun.Qty);
			iTemp = sti(pchar.questTemp.PrisonGun.Sum);
			dialog.Text = "물론이지. 여기 네 금화야 - 마음대로 해.";
			Link.l1 = "감사합니다! 함께 거래해서 즐거웠습니다!";
            Link.l1.go = "TakeGun_2";
			TakeNItems(pchar, "gold_dublon", iTemp);
			Log_Info("You have received "+FindRussianDublonString(sti(pchar.questTemp.WPU.Escort.Money))+"");
			PlaySound("interface\important_item.wav");
			RemoveCharacterGoods(Pchar, iGunGoods, amount);
		break;
		
		case "TakeGun_2":
			dialog.Text = "나도 같은 마음이오. 당신은 정말 많은 도움을 주었소. 그리고 부탁하건대, 이 거래는 이 방 안에만 묻어두시오.";
			Link.l1 = "물론이지. 행운을 빌어.";
            Link.l1.go = "exit";
			AddQuestRecord("PrisonGun", "2");
			AddQuestUserData("PrisonGun", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("PrisonGun");
			DeleteAttribute(pchar, "questTemp.PrisonGun");
			NextDiag.TempNode = "First time";
		break;
		// <-- орудия для форта

		//Jason --> мини-квест Дефицитный товар
		case "Wine_prison":
			dialog.text = "뭐라고?! 내가 요새 안에서 술 마시는 걸 엄격히 금지했는데! 좋아, 이 일에 대한 대가를 치르게 하겠다. 그의 급여에서 1000페소를 제하고, 그 돈을 네 경계심에 대한 보상으로 주겠다. 그리고 이 자는 3일 동안 구금될 것이다.";
			link.l1 = "감사합니다, "+GetAddress_FormToNPC(NPChar)+". 이러한 위반을 막는 것은 우리 모두의 공동 의무입니다.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 1000);
			ChangeCharacterComplexReputation(pchar,"nobility", -1); 
			DeleteAttribute(pchar, "questTemp.Wine.bottle");
			pchar.quest.Wine_Exchange.over = "yes";//снять прерывание
			pchar.quest.WineTraderQM.over = "yes";//снять прерывание
			WineTraderQMDel();
			sld = characterFromId(pchar.questTemp.Wine.id);
			sld.lifeday = 0;
			CloseQuestHeader("Wine");
			NextDiag.TempNode = "First time";
		break;
		// <-- мини-квест Дефицитный товар
		
		// Карибские нравы
		case "trial":
			iTest = FindColony(NPChar.City); // город
			QuestPointerDelLoc("portpax_town", "reload", "gate_back");
			QuestPointerDelLoc("portpax_exittown", "reload", "reload2_back");
			QuestPointerDelLoc("portpax_fort", "reload", "reload2");
			if (iTest != -1)
			{
				rColony = GetColonyByIndex(iTest);
			}
			ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
			if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
				if (GetSquadronGoods(pchar, GOOD_BOMBS) < 2500 || GetSquadronGoods(pchar, GOOD_POWDER) < 2500)
				{
					dialog.text = "흠. 그런데 이 배치는 꽉 차지 않았잖아! 어떻게 된 거지?";
					link.l1 = "젠장! 제발 용서해 주십시오, 제 잘못입니다. 바로 부족한 양을 사서 약속한 대로 전량을 당신께 넘기겠습니다.";
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = "그래, 네가 우리 심부름꾼이란 말이지? 좋아. 화물부터 정리하고 나면 다음 지시를 내리겠다.";
					link.l1 = "좋아.";
					link.l1.go = "trial_1";
				}
			}
			else
			{
				dialog.text = "항구에 네 배가 안 보여. 설마 화물을 정글로 끌고 가자는 거냐? 우리 항구로 서둘러 가서 돌아와라.";
				link.l1 = "내 배는 섬 반대편에 있어. 내가 항구로 가져올게.";
				link.l1.go = "exit";
			}
		break;
		
		case "trial_1":
			if(!bImCasual) pchar.quest.Trial_FrahtFail.over = "yes"; // belamour legendary edition если был - снять таймер
			dialog.text = "좋아, 폭탄과 화약 각각 2,500단위씩... 좋아. 군인들이 화물을 내릴 테니, 네 부하들은 쉬게 해라. 여기 운송료다 - 오천 페소다.";
			link.l1 = "고마워! 이제 뭘 해야 하지? LeCroix 나리가 이렇게 말했는데...";
			link.l1.go = "trial_2";
			DelLandQuestMark(npchar);
		break;
		
		case "trial_2":
			AddMoneyToCharacter(pchar, 5000);
			RemoveCharacterGoods(pchar, GOOD_BOMBS, 2500);
			RemoveCharacterGoods(pchar, GOOD_POWDER, 2500);
			dialog.text = "그래, 그래, 이제 지시를 받게 될 거야. 집중할 준비됐나?";
			link.l1 = "알겠소, 경관.";
			link.l1.go = "trial_3";
		break;
		
		case "trial_3":
			dialog.text = "그러니까, 우리 군함 'Warlike'가 스페인 식민지 포르토 벨로 근처, 스페인 메인 남부 해역을 순찰 중이오. 이 함선은 플로리안 쇼크가 지휘하고 있으며, 2주 후 포르토 벨로를 출항할 예정인 스페인 중무장 갈레온을 매복할 준비를 하고 있소.\n문제는 우리 프리깃함의 대포에 주조 결함이 있어 임무를 성공시키려면 대포 15문을 교체해야 한다는 점이오. 그렇지 않으면 갈레온이 'Warlike'보다 화력도, 병력도 더 많게 될 것이오.\n교체가 이루어지지 않으면 플로리안 쇼크는 아무런 성과 없이 퇴각할 수밖에 없소. 이런 사태는 반드시 막아야 하오. 그대의 임무는 14일 이내에 대포 15문을 전달하여 작전을 구하는 것이오.";
			link.l1 = "그러니까, 내가 대포 열다섯 문을 싣고 포르토벨로로 가서, 프리깃 '밀리턴트'를 찾아서 그 대포들을 플로리안 쇼크 선장에게 넘기면 되는 거지?";
			link.l1.go = "trial_4";
		break;
		
		case "trial_4":
			dialog.text = "정확해. 제대로 이해했군. 이 임무를 맡을 준비됐어?";
			link.l1 = "보수는 어떻게 되지?";
			link.l1.go = "trial_5";
			link.l2 = "죄송합니다, 장교 나리, 하지만 저는 그냥 관여하고 싶지 않습니다. 양해해 주십시오.";
			link.l2.go = "trial_exit";
		break;
		
		case "trial_exit":
			dialog.text = "당신이 거절할 권리가 있다는 건 알지만, 나는 당신이 동의해 줄 거라 생각했소. 이제 다른 심부름꾼을 찾아야겠군, 하지만 시간이 별로 없는데... 더 이상 붙잡지 않겠소, 선장.";
			link.l1 = "안부를 전합니다.";
			link.l1.go = "trial_exit_1";
		break;
		
		case "trial_exit_1":
			DialogExit();
			AddQuestRecord("Trial", "6");
			CloseQuestHeader("Trial");
			DeleteAttribute(pchar, "questTemp.Trial");
			pchar.questTemp.TrialEnd = true;
		break;
		
		case "trial_5":
			dialog.text = "그건 걱정하지 마시오. 플로리안 쇼크가 배의 금고에서 금화 200더블룬을 줄 것이오. 게다가, 분명히 그가 당신과 당신의 배를 자신의 목적을 위해 쓰고 싶어 할 거요 - 물론 당신이 동의한다면 말이오.";
			link.l1 = "좋아, 이 임무는 내가 맡을게! 대포는 어디 있지?";
			link.l1.go = "trial_6";
		break;
		
		case "trial_6":
			dialog.text = "군인들에게 즉시 당신의 배에 그것들을 싣도록 명령하겠습니다. 가능한 한 빨리 출항하십시오, 나리! 행운을 빕니다!";
			link.l1 = "고맙소. 행운도, 순풍도 분명 도움이 될 테니...";
			link.l1.go = "trial_7";
		break;
		
		case "trial_7":
			DialogExit();
			AddQuestRecord("Trial", "7");
			pchar.questTemp.Trial = "cannon";
			// belamour legendary edition
			if(!bImCasual) SetFunctionTimerCondition("Trial_CannonFail", 0, 0, 21, false); 
			else NewGameTip("Exploration mode: timer is disabled.");
			SetCharacterGoods(pchar, GOOD_CANNON_24, GetCargoGoods(pchar, GOOD_CANNON_24)+15);
			if (MOD_SKILL_ENEMY_RATE >= 6)
			{
				EnemyNationHunterOnMap(true);//запуск перехватчиков
			}
			pchar.quest.Trial_cannon.win_condition.l1 = "location";
			pchar.quest.Trial_cannon.win_condition.l1.location = "Portobello";
			pchar.quest.Trial_cannon.function = "Trial_CreateFlorianFrigate";
			// Sinistra - квест "Встреча с Диего"
			bDisableFastReload = true;
			PChar.quest.VsD_GiumDyubua.win_condition.l1 = "location";
			PChar.quest.VsD_GiumDyubua.win_condition.l1.location = "PortPax_Fort";
			PChar.quest.VsD_GiumDyubua.win_condition = "VsD_GiumDyubua";
			AddMapQuestMarkShore("Shore47", false);
		break;
		
		// Опасный груз -->
		case "zpq_prs1":
			if(!isBadReputation(pchar, 70))
			{
				dialog.text = "흠, 그럴 수도 있겠군. 뭐, 당신 평판이 좋아서 한번 믿어보지. 아니었으면 이런 얘기조차 안 했을 거야. 사실은, 우리가 꽤 큰 양의 특별 화물을 필요로 해서, 대형 선박이랑 위험을 감수할 각오가 있어야 해. 그리고 아무에게도 이 일에 대해 말하지 않겠다고 약속해야 해.\n이게 마음에 걸린다면 지금 바로 말해. 내 말 충분히 이해했으리라 생각해...";
				link.l1 = "흥미롭군. 보수가 괜찮다면 나도 끼지. 다만 무슨 화물인지 전혀 모르겠어. 어쨌든 내 약속은 지키지.";
				link.l1.go = "zpq_prs2";
				link.l2 = "아니라고 해야겠군, 아마도... 내가 약속을 하면 일해야 하잖아, 그건 꽤 귀찮을 것 같아. 안 할 거야.";
				link.l2.go = "zpq_fld";
				Notification_Reputation(true, 71, "low");
			}
			else
			{
				dialog.text = "당신의 평판은 나로서는 도저히 받아들일 수 없소. 방에서 나가 주시오. 우리 문제는 우리가 스스로 해결할 수 있소.";
				link.l1 = "뭐든지, 그럼 해결해 봐...";
				link.l1.go = "exit";
				Notification_Reputation(false, 71, "low");
			}		
		break;
		
		case "zpq_fld":
			dialog.text = "그래도 적어도 솔직하게 거절해 줬군... 더 이상 붙잡지 않겠다.";
			link.l1 = "안녕히 가십시오.";
			link.l1.go = "exit";
			pchar.questTemp.zpq = "failed";
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("Cumana");
		break;
		
		case "zpq_fld2":
			dialog.text = "흠, 사실 너한테 그런 행동을 기대하지 않았는데. 나가 줘야겠어... 그리고 어떤 정보도 누설하지 않겠다는 약속, 꼭 기억해.";
			link.l1 = "미안하오...";
			link.l1.go = "exit";
    		ChangeCharacterComplexReputation(pchar,"nobility", -3);
			if (pchar.questTemp.zpq == "begin")
			{
				AddQuestRecord("zpq", "6");
				AddQuestUserData("zpq", "sSex", GetSexPhrase("",""));
				CloseQuestHeader("zpq");
			}
			pchar.questTemp.zpq = "failed";
		break;
		
		case "zpq_prs2":
			dialog.text = "훌륭하오. 훌륭하오. 문제는 최근 폭풍 때문에 요새 무기고의 화약이 손상되었다는 것이오. 내가 굳이 설명하지 않아도 이게 얼마나 미묘한 문제인지 알겠지. 만약 오랜 포위가 이어진다면 요새는 아무것도 할 수 없을 것이오. 오래 버티지 못할 거요.";
			link.l1 = "이제 알겠소. 어떤 화물이 필요하며, 얼마나 필요한가?";
			link.l1.go = "zpq_prs3";
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("Cumana");
		break;
		
		case "zpq_prs3":
			dialog.text = "화약 15,000통이 필요하오. 100,000페소를 지불하겠소... 이 가격이 매우 좋은 조건임을 이해해야 하오. 현재 상황이 나로 하여금 이런 비용을 감수하게 만들었소, 총무관을 설득하는 것도 쉽지 않았지... 폭풍우 철이라 우리 보급로를 쓸 수 없고, 이 문제를 모두가 알게 되는 것도 원치 않소...\n";
			link.l1 = "그렇군... 값이 정말 좋네. 위험에 대해 언급했지...";
			link.l1.go = "zpq_prs4";
		break;
		
		case "zpq_prs4":
			dialog.text = "나는 그렇게 많은 화약이 운송 중에 매우 위험할 수 있다는 뜻이었어. 내 두 눈으로 몇 번이나 폭발을 본 적이 있지; 때로는 작은 불꽃 하나로도 충분하거든. 그런데 만약 폭풍을 만나면... 전체 호위대가 보통은 화공선이 될 만한 배와 거리를 두고 다녀. 만약 그게 폭발하면, 모두 끝장이지!";
			link.l1 = "알겠소... 하지만 나는 항상 내 말을 지키니, 이미 끝난 일로 여기시오.";
			link.l1.go = "zpq_prs5";
			link.l2 = "글쎄, 나리... 당신이 너무 끔찍한 이야기만 해서, 그 일은 더 이상 하고 싶지 않소.";
			link.l2.go = "zpq_fld2";
		break;
		
		case "zpq_prs5":
			dialog.text = "좋아, 우리가 거래를 성사시켜서 정말 기쁘네. 화물을 가져오면 바로 돈을 주겠네.\n돈은 일주일 후에나 준비될 테니 너무 서두르지 말고 천천히 오게. 하지만 너무 늦지는 말아주게.";
			link.l1 = "알겠습니다, 나리. 바로 하겠습니다.";
			link.l1.go = "zpq_prs5_ok";
		break;
		
		case "zpq_prs5_ok":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			pchar.questTemp.zpq = "begin";
			pchar.questTemp.zpq.time = 20;
			AddQuestRecord("zpq", "1");
			AddQuestUserData("zpq", "sSex", GetSexPhrase("",""));
			SaveCurrentQuestDateParam("pchar.questTemp.zpq");
		break;
		
		case "zpq_ex":
			dialog.text = "드디어 왔군! 자네가 우리 거래를 잊은 줄 알았지. 곧바로 내 병사들에게 자네 배에서 짐을 내리게 하겠네. 화약 다루는 일은 아주 민감한 일이거든, 하하!";
			link.l1 = "훌륭합니다, 나리. 하지만 대금 지불을 상기시켜 드려야겠습니다.";
			link.l1.go = "zpq_ex2";
			RemoveCharacterGoods(pchar, GOOD_POWDER, 15000);
			AddCharacterExpToSkill(pchar, "Sailing", 500);
			AddCharacterExpToSkill(pchar, "Fortune", 500);

            pchar.quest.zpq_sld1_fc.win_condition.l1 = "location";
            pchar.quest.zpq_sld1_fc.win_condition.l1.location = "Cumana_ExitTown";
            pchar.quest.zpq_sld1_fc.function = "zpq_sld1_fc";
		break;
		
		case "zpq_ex2":
			dialog.text = "네, 물론이지. 약속한 대로 5만 페소를 지급하겠소.";
			link.l1 = "장난하는 거야, 나리?! 우리 10만 페소에 거래했잖아!";
			link.l1.go = "zpq_ex3";
			if(CheckCharacterPerk(pchar, "Trustworthy"))
			{
				Notification_Perk(true, "Trustworthy");
				link.l2 = "(믿을 만한 사람) 자네가 날 속일 것 같아서 말인데, 12만 5천 페소를 받을 때까지 절대 안 떠날 거야!";
				link.l2.go = "zpq_ex4";
			}
			link.l3 = "음... 상황이 바뀐 것 같군. 좋아, 돈이나 챙기고 떠나는 게 낫겠어...";
			link.l3.go = "zpq_ex5";
		break;
		
		case "zpq_ex3":
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > 35)
			{
				Notification_Skill(true, 36, SKILL_LEADERSHIP);
				dialog.text = "아, 맞아요... 그렇지! 10만 페소지. 깜빡했군, 미안하오. 나이 탓이오, 건망증이 심해서... 물론이지, 여기 돈이오. 거래하게 되어 즐거웠소, 선장. 이제 미안하지만, 할 일이 많아서 말이오...\n";
				link.l1 = "당신도 마찬가지요, 나리. 또 봅시다.";
				link.l1.go = "exit";
				pchar.questTemp.zpq = "completed";
				AddQuestRecord("zpq", "2");
				AddQuestUserData("zpq", "sSex", GetSexPhrase("",""));
				CloseQuestHeader("zpq");
				pchar.questTemp.zpq.sum = 100000;
				AddMoneyToCharacter(pchar, makeint(pchar.questTemp.zpq.sum));
			}
			else
			{
				Notification_Skill(false, 36, SKILL_LEADERSHIP);
				dialog.text = "뭐?! 돈이나 챙기고 꺼져, 안 그러면 이 감방에서 썩게 될 거야!";
				link.l1 = "너 정말 거짓말쟁이구나, 나리! 내 충고를 듣고 내 돈을 순순히 돌려주지 않으면, 내가 화물을 압수하겠다!";
				link.l1.go = "zpq_ex_agry";
				link.l2 = "실례하오... 좋아, 제시한 금액을 받겠소, 이걸로 끝내지.";
				link.l2.go = "zpq_ex5";
			}
		break;
		
		case "zpq_ex4":
				dialog.text = "이런 무례함이 있나! 나는 정신이 온전하고, 분명히 10만 페소를 제안했던 걸 기억하오.\n 젠장! 네 수작에 놀아나지 않을 거야!";
				link.l1 = "진정해라. 네 요새 바로 앞에 화약을 가득 실은 불배가 있다는 걸 생각해 봐. 내가 한마디만 하면 네 요새는 폐허가 될 거다.";
				link.l1.go = "zpq_ex6";
		break;
		
		case "zpq_ex6":
			dialog.text = "흠흠... 강한 논리로군. 12만 5천 페소라고? 여기, 가져가시오. 이제 용서하게, 할 일이 있어서...";
			link.l1 = "안녕히 가시오, 나리. 또 봅시다.";
			link.l1.go = "exit";
			pchar.questTemp.zpq = "completed";
            AddQuestRecord("zpq", "5");
			CloseQuestHeader("zpq");
			pchar.questTemp.zpq.sum = 125000;
			AddMoneyToCharacter(pchar, makeint(pchar.questTemp.zpq.sum));
			/*else
			{
				dialog.text = "뭐?! 나는 군 장교다! 네가 나를 겁줄 수 있을 거라 생각하나, 꼬마야?! 경비병들, 잡아라 "+GetSexPhrase("그를","그녀의")+"!";
				link.l1 = "해보려면 해봐라, 지하 감옥의 쥐새끼들아...";
				link.l1.go = "zpq_ex_war";
			}*/
		break;
		
		case "zpq_ex5":
			dialog.text = "훌륭하군! 올바른 선택을 했소. 돈을 가져가시오, 그리고 작별이오. 즐거웠소!";
			link.l1 = "안녕히 가시오...";
			link.l1.go = "exit";
			pchar.questTemp.zpq = "completed";
            AddQuestRecord("zpq", "3");
			AddQuestUserData("zpq", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("zpq");
			pchar.questTemp.zpq.sum = 50000;
			AddMoneyToCharacter(pchar, makeint(pchar.questTemp.zpq.sum));
		break;
		
		case "zpq_ex_agry":
			dialog.text = "아, 이 자식아! 경비병들, 잡아라 "+GetSexPhrase("그를","그녀")+"!";
			link.l1 = "으악! 네 시체에서 내 돈을 직접 가져가야겠군...";
			link.l1.go = "zpq_ex_war";
		break;
		
        case "zpq_ex_war":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_SetFightMode(PChar, true);
			pchar.questTemp.zpq = "failed";
            AddQuestRecord("zpq", "4");
			CloseQuestHeader("zpq");
			pchar.questTemp.zpq.sum = 100000;
			AddMoneyToCharacter(npchar, makeint(sti(pchar.questTemp.zpq.sum)*2 + rand(5000)));
			GiveItem2Character(npchar, "blade_21");
			EquipCharacterbyItem(npchar, "blade_21");
			npchar.SaveItemsForDead  = true;
			npchar.DontClearDead = true;
			npchar.cirassId = Items_FindItemIdx("cirass3");
			chrDisableReloadToLocation = true;
			string slai_group = GetNationNameByType(sti(npchar.nation))  + "_citizens";
			LAi_group_AttackGroup(slai_group, LAI_GROUP_PLAYER);
			LAi_group_SetCheck(slai_group, "OpenTheDoors");
			AddSimpleRumour("Such terrible things happen here! They say that some prisoner has escaped from the casemates! He slaughtered all the guards, stole the treasury, and just went away! Shiver me timbers!", SPAIN, 5, 1);
		break;
		// <-- Опасный груз
	}
}

void GetGunType()
{
	int iGunType;
	if(makeint(pchar.rank) < 6) iGunType = rand(1);	//18&&24
	if(makeint(pchar.rank) >= 6 && makeint(pchar.rank) < 15) iGunType = rand(2); //24&&32	
	if(makeint(pchar.rank) >= 15 && makeint(pchar.rank) < 24) iGunType = rand(2)+2; //32&&36&&42
	if(makeint(pchar.rank) >= 24) iGunType = 5-rand(1); //36clv&&42
	int iAdd = makeint(GetSummonSkillFromName(pchar, SKILL_COMMERCE)/20);
	
	switch (iGunType)
	{
		case 0:  
			pchar.questTemp.PrisonGun.Goods = GOOD_CANNON_24;     					
			pchar.questTemp.PrisonGun.Price = 28 + iAdd;
			pchar.questTemp.PrisonGun.Qty = sti(pchar.rank)*5+25+rand(sti(pchar.rank));
			pchar.questTemp.PrisonGun.Text = "24 calibre cannons";
		break; 
		case 1:  
			pchar.questTemp.PrisonGun.Goods = GOOD_CULVERINE_18;     					
			pchar.questTemp.PrisonGun.Price = 25 + iAdd;
			pchar.questTemp.PrisonGun.Qty = sti(pchar.rank)*5+25+rand(sti(pchar.rank));
			pchar.questTemp.PrisonGun.Text = "couleuvrines";
		break; 
		case 2:  
			pchar.questTemp.PrisonGun.Goods = GOOD_CANNON_32;     					
			pchar.questTemp.PrisonGun.Price = 32 + iAdd;
			pchar.questTemp.PrisonGun.Qty = sti(pchar.rank)*3+15+rand(sti(pchar.rank));
			pchar.questTemp.PrisonGun.Text = "32 calibre cannons";
		break; 
		case 3:  
			pchar.questTemp.PrisonGun.Goods = GOOD_CANNON_36;     					
			pchar.questTemp.PrisonGun.Price = 36 + iAdd;
			pchar.questTemp.PrisonGun.Qty = sti(pchar.rank)*3+15+rand(sti(pchar.rank));
			pchar.questTemp.PrisonGun.Text = "36 calibre cannons";
		break;
		case 4:  
			pchar.questTemp.PrisonGun.Goods = GOOD_CULVERINE_36;     					
			pchar.questTemp.PrisonGun.Price = 49 + iAdd;
			pchar.questTemp.PrisonGun.Qty = sti(pchar.rank)+15+rand(sti(pchar.rank));
			pchar.questTemp.PrisonGun.Text = "full couleuvrines";
		break; 
		case 5:  
			pchar.questTemp.PrisonGun.Goods = GOOD_CANNON_42;     					
			pchar.questTemp.PrisonGun.Price = 40 + iAdd;
			pchar.questTemp.PrisonGun.Qty = sti(pchar.rank)+20+rand(sti(pchar.rank));
			pchar.questTemp.PrisonGun.Text = "42 calibre cannons";
		break; 
	}
}
