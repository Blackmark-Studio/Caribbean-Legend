// Якоб Джекман
int iBarbazonTotalTemp;
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sLoc;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

// ============================= блок angry ==========>>>>>>>>>>>>>>>>>>>>>>>>>
    if (CheckAttribute(npchar, "angry") && !CheckAttribute(npchar, "angry.ok"))
    {
        npchar.angry.ok = 1;
        if (!CheckAttribute(npchar, "angry.first")) //ловушка первого срабатывания
        {
            NextDiag.TempNode = NextDiag.CurrentNode;
            Dialog.CurrentNode = "AngryExitAgain";
            npchar.angry.first = 1;
        }
        else
        {
            switch (npchar.angry.kind) //сюда расписываем реакцию ангри. В npchar.angry.name пробелы удалены!!!
            {
                case "repeat":
                    if (npchar.angry.name == "Firsttime") Dialog.CurrentNode = "AngryRepeat_1";
                    if (npchar.angry.name == "I_know_you_good") Dialog.CurrentNode = "AngryRepeat_2";
                    if (npchar.angry.name == "pirate_threat")
                    {
                        if (Dialog.CurrentNode == "I_know_you_good") Dialog.CurrentNode = "AngryRepeat_2";
                        else Dialog.CurrentNode = "AngryRepeat_1";
                    }
                break;
            }
        }
    }
// <<<<<<<<<<<<<<<<<<<<<<======= блок angry ===================================
// ============================================================================

	switch(Dialog.CurrentNode)
	{
		// ----------------------------------- Диалог первый - первая встреча
		case "First time":
            if (sti(pchar.GenQuest.Piratekill) > 20)
			{
				dialog.text = RandPhraseSimple("미쳤냐? 도살놀이라도 하고 싶었던 거야? 모든 해적들이 너한테 빡쳐 있어, 이 녀석아, 여기서 얼른 꺼지는 게 좋을 거다...","미친 거 아니냐, 이놈아. 팔다리 좀 펴보고 싶었나? 기분 나쁘게 듣지 마라, 네가 여기 있을 자리는 없어. 꺼져!");
				link.l1 = RandPhraseSimple("이봐, 내가 이 상황을 바로잡고 싶어...","이 문제 좀 해결해 줘...");
				link.l1.go = "pirate_town";
				break;
			}
			
			link.l0 = ""+npchar.name+", 나는" + GetSexPhrase("", "요") + " 바다에서의 내 안전에 대해 이야기하고 싶어. 해안 형제단 녀석들이 내 겸손한 존재에 지나치게 관심을 보이고 있어. 그들을 좀 억눌러 줄 수 있겠어?";
			link.l0.go = "pirate_threat";

			dialog.text = NPCStringReactionRepeat("나한테 할 말 있냐? 없어? 그럼 꺼져!",
						"내 말 알아들었지, 그만 귀찮게 해.","내가 분명히 말했는데도, 자꾸 성가시게 굴잖아!",
						"그래, 이 무례함에 슬슬 질린다.","repeat",3,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("나 이제 간다.",
						"그래, "+npchar.name+"...",
						"미안하다, "+npchar.name+"...",
						"아야...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";

			//--> Сага
			if(CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "maruntown")
			{
				link.l1 = "Jimmy Higgins은 어디에 있지?";
				link.l1.go = "Saga_Jimmy";
			}	
			if(CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "jackman")
			{
				link.l1 = "또 나야, Jackman. 실종된 사람들을 찾고 있다던데...";
				link.l1.go = "Saga_search";
			}	
			//<-- Сага

			//поручение капитана - выкуп
			if (CheckAttribute(pchar, "GenQuest.CaptainComission") && NPChar.city == pchar.GenQuest.CaptainComission.PiratesCity)
			{
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.toMayor"))
				{
					link.l1 = "네 죄수에 관한 일이야.";
					link.l1.go = "CapComission1";
					DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
				}	
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.PirateShips"))
				{
					link.l1 = "안녕, Jackman. 네 임무에 대해 할 말이 있어...";
					link.l1.go = "CapComission3";
				}
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.RepeatSpeak"))
				{
					link.l1 = "네 죄수에 관한 일이야.";
					link.l1.go = "CapComission6";
				}
			}	
		break;

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

        case "I_know_you_good":
            if (sti(pchar.GenQuest.Piratekill) > 20)
			{
				dialog.text = RandPhraseSimple("미쳤냐? 도살장 놀이하고 싶었던 거야? 모든 해적들이 너한테 화났어, 이 녀석. 여기서 당장 꺼지는 게 좋을 거다...");
				link.l1 = RandPhraseSimple("이봐, 이 상황을 바로잡고 싶어...","이 문제 좀 해결해 줘...");
				link.l1.go = "pirate_town";
				break;
			}
			
			link.l0 = ""+npchar.name+", 나는" + GetSexPhrase("", "요") + " 바다에서의 내 안전에 대해 이야기하고 싶어. 해안 형제단 녀석들이 내 겸손한 존재에 지나치게 관심을 보이고 있어. 그들을 좀 억눌러 줄 수 있겠어?";
			link.l0.go = "pirate_threat";

			dialog.text = NPCStringReactionRepeat("나한테 할 말 있냐? 없어? 그럼 꺼져!",
						"내 말 알아들었지, 그만 귀찮게 해.","내가 분명히 말했는데도, 자꾸 성가시게 굴잖아!",
						"그래, 이 무례함에 슬슬 질린다.","repeat",3,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("나 이제 간다.",
						"그래, "+npchar.name+"...",
						"미안하다, "+npchar.name+"...",
						"아야...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";

			//поручение капитана - выкуп
			if (CheckAttribute(pchar, "GenQuest.CaptainComission") && CheckAttribute(pchar,"GenQuest.CaptainComission.toMayor"))
			{
				link.l1 = "네 죄수에 관한 일이야.";
				link.l1.go = "CapComission1";
				DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
			}				
		break;

//-----------------------------------------пиратская сага----------------------------------------------------
		case "Saga_Jimmy":
			dialog.text = "정말이냐! 누군가 저 게으른 놈을 찾는다고? 그 자식은 며칠째 자기 오두막에서 혼자 럼주만 퍼마시고 있다. 나 같으면 찾아가지 않겠어. 맨정신일 때도 별로 좋은 놈은 아니거든...";
			link.l1 = "괜찮아, 나도 성인은 아니니까. 그의 오두막은 어디 있지?";
			link.l1.go = "Saga_Jimmy_1";
		break;
		
		case "Saga_Jimmy_1":
			dialog.text = "선술집 바로 앞에 있어. 술 한잔 하러 빠르게 들르기엔 딱 좋은 자리를 골랐지.";
			link.l1 = "고맙다!";
			link.l1.go = "Saga_Jimmy_2";
		break;
		
		case "Saga_Jimmy_2":
			DialogExit();
			pchar.quest.Saga_createJimmy.win_condition.l1 = "location";
			pchar.quest.Saga_createJimmy.win_condition.l1.location = "FortOrange_House1";
			pchar.quest.Saga_createJimmy.function = "Saga_CreateJimmy";
			pchar.questTemp.Saga = "jimmy";
		break;
		
		case "Saga_search":
			dialog.text = "그걸 누가 말했지? 그 주정뱅이 히긴스냐? 글래디스 챈들러나 교수형 집행인 헨리에 대해 뭐라도 알아냈어?";
			link.l1 = "별건 아니지만, 그 교수형 집행인에 대해 뭔가 구체적으로 알고 싶어서.";
			link.l1.go = "Saga_search_1";
		break;
		
		case "Saga_search_1":
			dialog.text = "알아야 할 건 별로 없어. 지금은 몇 명만 기억하지만, 이십 년 전만 해도 헨리는 브리짓타운에서 토르투가까지 창녀들 사이에서 아주 인기였지. 당연하지! '넵튠'호의 보선이었거든, 그것도 부처 선장 밑에서! 지금 살아 있다면 꽤 늙었을 거야, 물론 아직 살아 있다면 말이지.\n가능성은 희박하지만, 세상에 불가능한 건 없잖아. 그에 대한 정보만 주면 이만 페소를 주지. 살아서 여기 데려오면 두 배로 쳐주마.";
			link.l1 = "글래디스랑 그 딸년한테 얼마 줄 건데?";
			link.l1.go = "Saga_search_2";
		break;
		
		case "Saga_search_2":
			dialog.text = "오, 그 애는 그녀의 딸이 아니야. 그 계집애를 살아서 데려오면, 더블룬 한 무더기를 주지. 글래디스 따위엔 관심 없어. 질문 있나?";
			link.l1 = "이 소동의 이유를 알았으면 좋겠지만, 묻진 않겠다. 내 인생이 짧아질지도 모르니까.";
			link.l1.go = "Saga_search_3";
		break;
		
		case "Saga_search_3":
			dialog.text = "아마도... 그 비밀은 네 알 바 아니다. 덜 알수록 오래 살지. 다시는 그런 질문 하지 마라, 점점 네가 수상해진다고 느껴지니까. 내 마음이 바뀌기 전에 꺼져라.";
			link.l1 = "또 보자, 남작!";
			link.l1.go = "Saga_search_4";
		break;
		
		case "Saga_search_4":
			DialogExit();
			AddQuestRecord("Saga", "6");
			if (CheckAttribute(pchar, "questTemp.Saga.Jimmysecret"))
			{
				AddQuestUserData("Saga", "sText", "To Antigua now. The corvette must be boarded.");
				DeleteAttribute(pchar, "questTemp.Saga.Jimmysecret");
			}
			pchar.quest.Saga_createDonovan.win_condition.l1 = "location";
			pchar.quest.Saga_createDonovan.win_condition.l1.location = "Antigua";
			pchar.quest.Saga_createDonovan.function = "Saga_createDonovan";
			pchar.questTemp.Saga = "donovan";
		break;
		
		// абордаж, в каюте
		case "Jackman_abordage":
			dialog.text = "하! 또 만났군, 선장. "+GetFullName(pchar)+". 인정하지, 네가 마룬타운에서 바보인 척하려 했음에도 불구하고 꽤나 쓸만한 상대더군. 네가 네덜란드 서인도 회사와 꾸민 음모도 알아냈다... 이제야 네가 어떤 놈인지 알겠군.";
			link.l1 = "나도 네 같은 놈 잘 알아, Jacob. 그러니 우리끼리 착각은 하지 말자.";
			link.l1.go = "Jackman_abordage_1";
		break;
		
		case "Jackman_abordage_1":
			dialog.text = "그리고 네가 'Marlin'으로 나를 어떻게 속였는지! 내 불쌍한 형제는 죽었겠지...";
			link.l1 = "그 놈을 위해 복수하러 온 거냐? 하지만 너한테도 갚을 게 산더미처럼 쌓여 있지. 궁지에 몰린 네이선리얼, 그 마누라, 그 프리깃, 모욕당한 샤크, 블레이즈 샤프까지...";
			link.l1.go = "Jackman_abordage_2";
		break;
		
		case "Jackman_abordage_2":
			dialog.text = "블레이즈? 내가 그 놈 안 죽였어.";
			link.l1 = "설령 그게 사실이라 해도, 내 목록의 나머지로도 충분하다. 네 이름은 이제 지긋지긋하다. 말은 그만해, 잭맨! 이제 칼로 말하자!";
			link.l1.go = "Jackman_abordage_3";
		break;
		
		case "Jackman_abordage_3":
			dialog.text = "저렇게 성질 더러운 멍청이 같으니... 젠장할 놈! 이제 제대로 각오해라! Jacob Jackman은 한 번도 진 적이 없다! Carpacho, 딱 맞춰 왔군! 이리 와!";
			link.l1 = "...";
			link.l1.go = "Jackman_abordage_4";
		break;
		
		case "Jackman_abordage_4":
			DialogExit();
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "Saga_AfterJackmanBoarding");
			AddDialogExitQuest("MainHeroFightModeOn");
			// подкрепление
			int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+12;
			int iScl = 30 + 2*sti(pchar.rank);
			sld = GetCharacter(NPC_GenerateCharacter("Saga_JackmanCabinHelper", "citiz_58", "man", "man", iRank, sti(npchar.nation), 0, true, "quest"));
			FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_21", "pistol4", "bullet", iScl*2+100);
			LAi_SetCheckMinHP(sld, 150, true, "Saga_DannyHurryHelp");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_BRDENEMY);
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
			sld = characterFromId("Danielle");
			RemovePassenger(Pchar, sld);
		break;

		//*************************** Генератор "Captain's offer - Ransom" **********************
		case "CapComission1":
			dialog.text = "하하. 내가 여기 죄수를 한 명만 데리고 있다고 생각하나? 이름을 대봐.";
			link.l1 = pchar.GenQuest.CaptainComission.SlaveName+". 여기 있나?";
			link.l1.go = "CapComission2";
			DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
		break;

		case "CapComission2":
			if(CheckAttribute(pchar,"GenQuest.CaptainComission.DaysLeft"))
			{
				dialog.text = "그랬지. 내가 그를 바베이도스에서 온 플랜테이션 주인, 비숍 대령에게 팔았어 – 그자가 여기 온 게 일주일 전이었지.";
				link.l1 = "젠장...";
				link.l1.go = "CapComission2_1";
			}
			else
			{
				dialog.text = "아, 드디어 왔군. 난 그 녀석을 바베이도스의 플랜테이션 주인놈한테 팔아넘길까 생각 중이었지, 그 자식이 일주일이나 이주일 안에 올 거거든... 몸값은 가져왔냐?";
				link.l1 = "봐라, 약간 문제가 있어... 사실, 내가 그렇게 많은 돈은 없어. 하지만 일할 의지는 있다.";
				link.l1.go = "CapComission2_2";
				if(makeint(pchar.money) > 150000)
				{
					link.l2 = "그놈을 아직 팔지 않아서 다행이군. 여기 네 돈이다 - 15만 페소다. 그놈은 어디에 있지?"link.l2.go ="CapComission2_3";
				}	
			}
		break;
		
		case "CapComission2_1":
			dialog.text = "너무 느렸군... 그리고 그 자가 뭐가 그리 중요하지? 나는 그의 친척들과만 협상했을 뿐이야.";
			link.l1 = "놈들이 나보고 여기 오라고 했지.";
			link.l1.go = "CapComission2_11";
		break;
		
		case "CapComission2_11":
			dialog.text = "그래, 너 늦었군. 내가 해줄 수 있는 건 없어.";
			link.l1 = "이봐, 비밀 아니면 그놈을 얼마에 팔았지?"; 
			link.l1.go = "CapComission2_12";
		break;
		
		case "CapComission2_12":
			dialog.text = "에이, 아니야. 하지만 말 안 해줄 거다... 말하면 네가 비웃을 테니까. 하하하하! 잘 가라.";
			link.l1 = "또 보자...";
			link.l1.go = "exit";
			AddQuestRecord("CaptainComission1", "10");
			AddQuestUserData("CaptainComission1", "sName", "Jackman")); // belamour gen
			//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			CaptainComission_GenerateManager();
		break;
		
		case "CapComission2_2":
			if(rand(1) == 0)
			{
				dialog.text = "그래, 그래... 볼일이 좀 있지... 어디서부터 시작해야 할지 모르겠군. 선을 넘은 해적 놈을 바다에 수장시켜야 해.";
				link.l1 = "정글에서 그냥 죽이면 안 되나?";
				link.l1.go = "CapComission2_2_1";
			}
			else
			{
				dialog.text = "그래, "+pchar.name+", 있잖아, 세상일이 그렇게 쉽게 돌아가지 않아. 돈 들고 다시 오면 네 그 약골을 돌려주지, 하하.";
				link.l1 = "좋아. 또 보자.";
				link.l1.go = "CapComission2_4";
			}
		break;

		case "CapComission2_2_1":
			dialog.text = "장사는 그렇게 돌아가는 게 아니야, 알겠어... 내가 그 자를 죽일 필요는 없어, 그냥 몇 놈한테 내 몫의 전리품에 손대지 말라고 가르쳐 주면 돼. 하지만 그 자가 상어 밥이 된다 해도, 난 신경 안 쓸 거다.";
			link.l1 = "왜 네 놈 부하들을 보내지 않지?";
			link.l1.go = "CapComission2_2_2";
		break;
		
		case "CapComission2_2_2":
			CaptainComission_GetRandomShore();
			pchar.GenQuest.CaptainComission.ShipName1 = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.GenQuest.CaptainComission.ShipName2 = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.GenQuest.CaptainComission.UnknownPirateName = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);
			sLoc = XI_ConvertString(pchar.GenQuest.CaptainComission.Island + "Abl");
			dialog.text = "흠... 그래, "+GetName(NAMETYPE_ORIG,pchar.GenQuest.CaptainComission.UnknownPirateName,NAME_NOM)+" 우리 보물창고가 멀지 않은 곳에 있어서 거기에 자기 몫의 전리품이 보관되어 있다고 몇몇 해적들을 설득했지 "+XI_ConvertString(pchar.GenQuest.CaptainComission.Island.Shore+"Gen")+". 그들의 두 척 배 '"+pchar.GenQuest.CaptainComission.ShipName1+"' 그리고 '"+pchar.GenQuest.CaptainComission.ShipName2+"'이(가) 얼마 전에 닻을 올리고 출항해서 "+sLoc+". 이제 내가 왜 내 부하놈들한테 이 일을 맡길 수 없는지 알겠지?";
			link.l1 = "그래. 시간이 얼마나 남았지?";
			link.l1.go = "CapComission2_2_3";
		break;
		
		case "CapComission2_2_3":
			dialog.text = "12일에서 15일, 그 이상은 안 되겠지. 놈들이 은닉처에 도착하면 값진 화물을 싣고 침몰시키는 게 아무 의미 없으니까. 그런 경우라면 차라리 여기로 가져오게 하는 게 낫겠군...";
			link.l1 = "좋아, 나도 끼지. 놈들 잡아보겠다.";
			link.l1.go = "CapComission2_2_4";
		break;
		
		case "CapComission2_2_4":
			AddQuestRecord("CaptainComission1", "24");
			AddQuestUserData("CaptainComission1", "sName", "Jackman")); // belamour gen
			//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			AddQuestUserData("CaptainComission1", "sShipName1", pchar.GenQuest.CaptainComission.ShipName1);
			AddQuestUserData("CaptainComission1", "sShipName2", pchar.GenQuest.CaptainComission.ShipName2);
			AddQuestUserData("CaptainComission1", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.Island.Shore + "Dat")); // belamour gen
			AddQuestUserData("CaptainComission1", "sShoreType", XI_ConvertString(GetIslandByArealName(pchar.GenQuest.CaptainComission.Island) + "Voc")); // belamour gen
			pchar.quest.CapComission_PirateAttack.win_condition.l1 = "location";
            pchar.quest.CapComission_PirateAttack.win_condition.l1.location = pchar.GenQuest.CaptainComission.Island;
            pchar.quest.CapComission_PirateAttack.function = "CaptainComission_GeneratePirateShips"; 
			SetFunctionTimerCondition("CaptainComission_PirateShipsOver", 0, 0, 15, false);
			pchar.GenQuest.CaptainComission.PirateShips = "goaway";	
			DialogExit();
		break;
		
		case "CapComission2_3":
			dialog.text = "걱정하지 마라. 내 부하들이 그 놈을 네 배로 데려다줄 거다. 그런데 넌 왜 그 놈한테 신경 쓰는 거지?";
			link.l1 = "나는 아니다. 그의 친척들이 나한테 그를 데려다 달라고 했지.";
			link.l1.go = "CapComission2_31";
		break;
		
		case "CapComission2_31":
			dialog.text = "아, 괜찮아. 네 놈 부하를 이렇게 헐값에 사려던 내가 좀 미안할 뻔했군. 하하하하. 잘 가라.";
			link.l1 = "또 보자.";
			link.l1.go = "CapComission2_32";
		break;
		
		case "CapComission2_32":
			AddQuestRecord("CaptainComission1", "9");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));	// belamour gen		
			addMoneyToCharacter(pchar, -150000);
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");	
		break;
		
		case "CapComission2_4":
			if(!CheckAttribute(pchar,"GenQuest.CaptainComission.RepeatSpeak"))
			{
				AddQuestRecord("CaptainComission1", "31");
				AddQuestUserData("CaptainComission1", "sName", "Jackman"); // belamour gen
				//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			}	
			pchar.GenQuest.CaptainComission.RepeatSpeak = true;		
			DialogExit();
		break;
		
		case "CapComission3":
			dialog.text = "그래서, , "+GetFullName(pchar)+", 내 동료를 네가 침몰시켰냐? 크크크...";
			if(pchar.GenQuest.CaptainComission.PirateShips == "goaway")
			{
				link.l1 = "아니. 놈들을 잡지 못했어. 돌아오는 길에도 만나지 못했지.";
				link.l1.go = "CapComission4";
			}
			if(pchar.GenQuest.CaptainComission.PirateShips == "died")	
			{
				link.l1 = "내가 했다. 놈들은 상어밥으로 던져줬지.";
				link.l1.go = "CapComission5";
			}
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
		break;
		
		case "CapComission4":
			dialog.text = "젠장! 내가 그놈들을 만났든 말든 이제 상관없어! 다음엔 뭘 제안할 건데?";
			link.l1 = "좀 더 쉬운 일 없나?";
			link.l1.go = "CapComission4_1";
			link.l2 = "이봐, Jackman, 포로 값 좀 깎아라...";
			link.l2.go = "CapComission4_2";
		break;
		
		case "CapComission4_1":
			dialog.text = "아니.";
			link.l1 = "그럼 이만...";
			link.l1.go = "CapComission4_3";
		break;
		
		case "CapComission4_2":
			dialog.text = "값을 깎으라고? 네 놈 무능함 때문에 내 물건 다 날렸잖아! 이제는 오히려 값을 올릴 수 있지! 원하면 20만 페소에 데려가든가, 아니면 당장 꺼져라.";
			link.l1 = "너무 비싸군... 잘 가라...";
			link.l1.go = "CapComission4_4";
			if(sti(pchar.money) >= 200000)
			{
				link.l2 = "젠장, 돈이나 가져가.";
				link.l2.go = "CapComission4_5";
			}	
		break;
		
		case "CapComission4_3":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			AddQuestRecord("CaptainComission1", "27");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_DAT));
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			DialogExit();
		break;
		
		case "CapComission4_4":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			AddQuestRecord("CaptainComission1", "28");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			DialogExit();		
		break;
		
		case "CapComission4_5":
			dialog.text = "좋아, 이 약골은 네가 데려가라...";
			link.l1 = "잘 가라.";
			link.l1.go = "CapComission4_6";
		break;
		
		case "CapComission4_6":
			addMoneyToCharacter(pchar, -200000);
			AddQuestRecord("CaptainComission1", "29");
			AddQuestUserData("CaptainComission1", "sName", "Jackman"); // belamour gen
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc")); // belamour gen
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			pchar.GenQuest.CaptainComission.SlaveAddMoney = true;
			DialogExit();	
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");	
		break;
		
		case "CapComission5":
			dialog.text = "호호! 잘했군! 네 그 약골이나 데려가고, 행운을 빌어.";
			link.l1 = "고맙다. 잘 가라.";
			link.l1.go = "CapComission5_1";
		break;
		
		case "CapComission5_1":
			AddQuestRecord("CaptainComission1", "34");
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc")); // belamour gen
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			DialogExit();		
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");	
		break;
		
		case "CapComission6":
			dialog.text = "돈 가져왔냐, Charles? 내가 그 남자를 플랜테이션에 팔겠다는 말, 농담 아니었어.";			
			link.l1 = "들어봐, "+NPChar.name+", 문제가 있어... 그만한 돈은 없어. 하지만 일할 의지는 있지.";
			link.l1.go = "CapComission2_2";
			if(makeint(pchar.money) > 150000)
			{
				link.l2 = "그놈을 아직 팔지 않았다니 다행이군. 여기 네 돈이다 - 15만 페소. 그놈은 어디에 있지?"link.l2.go ="CapComission2_3";
			}			
		break;
		
		// ============== Грабеж среди бела дня, попытка залезть в сундуки =========================
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("강도질이냐! 그건 용납 못 한다! 각오해라, "+GetSexPhrase("놈","여자")+"...","이봐, 거기서 뭐 하는 거야?! 나를 털 수 있을 줄 알았냐? 이제 끝장이다...","잠깐, 뭐야 이게? 손 떼! 결국 도둑이었군! 여기서 끝이다, 이 자식아...");
			link.l1 = LinkRandPhrase("젠장!","제기랄!!","젠장!!");
			link.l1.go = "PL_Q3_fight";
		break;
					
		// ======================== блок нод angry ===============>>>>>>>>>>>>>>>
		case "AngryRepeat_1":
            dialog.text = RandPhraseSimple("여기서 꺼져!","내 집에서 썩 꺼져!");
			link.l1 = "이런...";
		    link.l1.go = "AngryExitAgainWithOut";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся с Джекменом через 10 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "싸구려 말로 귀찮게 하지 마라. 다음엔 결과가 마음에 안 들 거다...";
        			link.l1 = "알겠어.";
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
            }
    	break;
		case "AngryRepeat_2":
            dialog.text = "끝났어, 말은 필요 없어.""더 이상 너랑 말하고 싶지 않으니까, 귀찮게 하지 마.";
			link.l1 = RandPhraseSimple("네 뜻대로 해...","좋아, 그럼...");
		    link.l1.go = "AngryExitAgain";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся с Джекменом через 10 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "네가 좀 더 예의를 갖추고 무례하게 굴지 않길 바란다. 그렇지 않으면 널 죽여야 할 테니까. 그건 정말 불쾌한 일이 될 거다.";
        			link.l1 = "확실히 할 거다, Jackman.";
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
            }
    	break;
		case "AngryExitAgain":
            DialogExit();
            DeleteAttribute(npchar, "angry.ok");
		break;
		case "AngryExitAgainWithOut":
            DialogExit();
            DeleteAttribute(npchar, "angry.ok");
            DoReloadCharacterToLocation("Fortorange_town","reload","reload6");
		break;
		// <<<<<<<<<<<<============= блок нод angry =============================
		case "pirate_town":
            dialog.text = "문제를 해결하라고? 네가 뭘 저질렀는지나 아냐? 어쨌든, 백만 페소 가져와라. 그러면 내가 놈들에게 네 '업적'을 잊으라고 설득해주지. 이게 싫으면 지옥이나 꺼져라.";
			if (sti(Pchar.money) >= 1000000)
			{
				link.l1 = "좋아, 돈 낼 준비 됐어.";
				link.l1.go = "pirate_town_pay";
			}
			link.l2 = "알겠다. 나 간다.";
			link.l2.go = "pirate_town_exit";
		break;
		
		case "pirate_town_exit":
			DialogExit();
            bDisableFastReload = true;//закрыть переход
			pchar.quest.pirate_in_town.win_condition.l1 = "ExitFromLocation";
			pchar.quest.pirate_in_town.win_condition.l1.location = pchar.location;
			pchar.quest.pirate_in_town.function = "TownPirate_battle";
		break;
		
		case "pirate_town_pay":
            dialog.text = "좋아! 이제 다시 깨끗해졌다고 생각해라. 하지만 다시는 그런 역겨운 짓 하지 마라.";
			link.l1 = "안 해. 나한텐 너무 비싸. 잘 있어...";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -1000000);
			pchar.GenQuest.Piratekill = 0;
		break;
		
		case "pirate_threat":
			if (GetNpcQuestPastDayWOInit(NPChar, "ThreatTalk") == 0)
			{
				dialog.text = NPCStringReactionRepeat("오늘은 이미 그 얘길 했잖아.",
				                                      "내 말이 이해가 안 됐나?",
				                                      "너무 끈질기군.",
				                                      "더는 못 참겠다. 당장 꺼져!",
				                                      "repeat", 3, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("다음에 다시 이야기하지 뭐...",
				                                   "물론이지, "+npchar.name+"...",
				                                   "미안해, "+npchar.name+"...",
				                                   "아야...", npchar, Dialog.CurrentNode);
				link.l1.go = "exit";
				break;
			}
			if (iGPThreat != 0)
			{
				iBarbazonTotalTemp = 10 * iGPThreatRate;
				dialog.text = "하! 우리 형제단이 널 괴롭히고 있나 보군, " + GetSexPhrase("친구", "아가씨") + "? 뭐, 잠시 동안은 그들을 진정시켜 줄 수 있지. 하지만 대가가 필요해. " + FindRussianDublonString(iBarbazonTotalTemp) + "만 내면, 그렇게 하지.";
				if (PCharDublonsTotal() > iBarbazonTotalTemp)
				{
					if (iGPThreat < 5) link.l0 = "좋아, 여기 네 돈이야.";
					else link.l0 = "어쩔 수 없지. 여기 있어.";
					link.l0.go = "pirate_threat_pay";
				}
				link.l1 = "다음에 다시 올게...";
				link.l1.go = "exit";
			}
			else
			{
				SaveCurrentNpcQuestDateParam(NPChar, "ThreatTalk");
				if (NextDiag.TempNode != "I_know_you_good")
					dialog.text = "미쳤" + GetSexPhrase("니", "니") + "? 우리 녀석들은 널 마치 전염병처럼 피해 다녀. 그러니까 꺼지고 귀찮게 하지 마.";
				else
					dialog.text = "무슨 말이야, " + GetSexPhrase("친구", "아가씨") + "? 넌 골칫덩어리야 — 개들조차도 그걸 알아. 아무도 너랑 엮이고 싶어하지 않아.";
				link.l1 = "알겠어...";
				link.l1.go = "exit";
			}
		break;

		case "pirate_threat_pay":
			iGPThreatRate = 0;
			iGPThreat = 0;
			SaveCurrentNpcQuestDateParam(NPChar, "ThreatTalk");
			RemoveDublonsFromPCharTotal(iBarbazonTotalTemp);
			DialogExit();
			PiratesDecreaseNotif("");
		break;
	}
}
