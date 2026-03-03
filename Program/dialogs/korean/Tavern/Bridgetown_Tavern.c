// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("무슨 질문이 있소?","무엇을 도와드릴까요, "+GetAddress_Form(NPChar)+"?"),"얼마 전에 나한테 뭔가 물어보려고 했지, "+GetAddress_Form(NPChar)+"...","이제 세 번째로 나를 귀찮게 하는군...","또 질문이 있나 보군?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("내 마음이 바뀌었어...","지금은 할 말이 없어."),"음, 내 기억이 다 어디로 갔지...","그래, 정말 이번이 세 번째야...","아니, 무슨 질문이야?…",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//Голландский гамбит /за Англию/
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng") && pchar.questTemp.HWIC.Eng == "GotoBridgetown" && !CheckAttribute(npchar, "quest.HWICTalked"))
            {
                link.l1 = "술 한잔 하고 싶군. 제일 좋은 럼 좀 따라 줘.";
                link.l1.go = "TavernDone";
            }
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng") && pchar.questTemp.HWIC.Eng == "toBarbados")
            {
                link.l1 = "이봐, 칼로우 개스톤은 어디 있지?";
                link.l1.go = "Tonzag_Letter";
            }
			//Голландский гамбит /против всех/
			if (!CheckAttribute(npchar, "quest.HWICTake") && CheckAttribute(pchar, "questTemp.HWIC.CanTake") && !CheckAttribute(pchar, "questTemp.HWIC.CanTake.Self") && !CheckAttribute(pchar, "questTemp.HWIC.Eng") && !CheckAttribute(pchar, "questTemp.HWIC.Holl"))
			{
                link.l1 = "혹시 일거리라도 있나? 아니면 뭔가 추천해줄 만한 게 있나?";
                link.l1.go = "Tonzag_check";
            }
			if (CheckAttribute(pchar, "questTemp.HWIC.Self") && pchar.questTemp.HWIC.Self == "FernandoDie")
			{
                link.l1 = "일을 끝냈어. Fernando Rodriguez는 죽었어.";
                link.l1.go = "Task_check";
            }
			// Страж Истины
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "merdok" && !CheckAttribute(npchar, "quest.jino"))
			{
				link.l1 = "이봐, 이 마을에 연금술사나 의사가 온 적 있나? 이탈리아인이고, 나이는 서른쯤 된다고 해. 이름은 지노 그비네일리야. 그에 대해 들은 게 있나?";
				link.l1.go = "guardoftruth";
			}
		break;
		
		//Голландский гамбит /за Англию/
		case "TavernDone":
			dialog.text = "여기 술이요. 우리 새로운 손님을 위한 최고의 럼이지! 오늘 무슨 특별한 일이라도 있소, 아니면 그냥 목이나 축이러 들른 거요\n";
			link.l1 = "그래, 특별한 일이 있다고 할 수 있지. 나는 노예들을 블루웰드로 데려가는 중이야. 최근에 내 새 브리그의 화물칸을 이 목적에 맞게 개조했거든. 방금 플랜테이션에 들러 감독관과 얘기했는데, 그가 나한테 좋은 '흑상아' 한 무더기를 주문했어. 그러니 곧 네 선술집에서 나를 기다려. 내가 블루웰드에 물건을 넘기고 나면 여기 바베이도스에서 또 장사를 좀 할 거니까, 요호!";
			link.l1.go = "TavernDone_1";
		break;
		
		case "TavernDone_1":
			dialog.text = "정말인가? 뭐, 좋은 거래를 위해 마시는 건 부끄러운 일이 아니지! 그런데 바베이도스에서 장사를 할 거라고? 멋진데! 건배하자, 선장!";
			link.l1 = "고맙다, 친구. 좋아... 앉을 자리를 좀 찾아볼게.";
			link.l1.go = "exit";	
			npchar.quest.HWICTalked = "true";
			pchar.questTemp.HWIC.Eng.BridgeCounter = sti(pchar.questTemp.HWIC.Eng.BridgeCounter)+1;
			AddQuestRecord("Holl_Gambit", "2-12");
			DelLandQuestMark(npchar);
			if (sti(pchar.questTemp.HWIC.Eng.BridgeCounter) == 7) 
			{
				AddQuestRecord("Holl_Gambit", "2-6");
				pchar.questTemp.HWIC.Eng = "SeekVanBerg";
				pchar.quest.GotoBridgetownOver.over = "yes";//снять таймер
				DelMapQuestMarkCity("Bridgetown");
				pchar.quest.VanBergAttack_Check.win_condition.l1 = "MapEnter";
				pchar.quest.VanBergAttack_Check.function = "VanBergAttackCheck";
			}
		break;
		
		case "Tonzag_Letter":
			dialog.text = "가스통은 네가 '상인' 행세를 한 지 이틀 뒤에 마을을 떠났어. 여기서 제대로 한바탕 벌였지, 하하! 네 속임수는 금방 들통났어. 이 마을은 작고 소문이 빨리 퍼지거든. 그래서 가스통이 떠난 거야. 그 이후로 아무도 그를 본 적 없어. 그래도 네게 편지를 남기고 갔더라.\n가스통은 만약 네가 그가 돌아오기 전에 여기 오면 꼭 직접 전해주라고 내게 부탁했어. 사실, 가스통을 찾으러 온 사람이 너만이 아니야. 눈이 가늘고 덩치 큰 사내 하나, 그리고 나이 든 사내가 있었지. 스페인 놈인지 포르투갈 놈인지 확실하진 않아. 하지만 그 얼굴은 잊을 수가 없어—뭔가 아주 이상한 기운이 느껴졌거든...";
			link.l1 = "그 편지 내놔... 고마워!";
			link.l1.go = "Tonzag_Letter_1";
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("Bridgetown");
		break;
		
		case "Tonzag_Letter_1":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "2-22");
			AddQuestRecordInfo("LetterFromGaston", "1");
			pchar.questTemp.HWIC.Eng = "toCuracao";
			LocatorReloadEnterDisable("SentJons_town", "houseSP3", true);//закрыть дом Флитвуда
			LocatorReloadEnterDisable("SentJons_town", "HouseF3", true);//закрыть аптеку
			LocatorReloadEnterDisable("SentJons_town", "basement1_back", true);//закрыть подземелье
			pchar.quest.Knippel_Shore.win_condition.l1 = "location";
			pchar.quest.Knippel_Shore.win_condition.l1.location = "Shore24";
			pchar.quest.Knippel_Shore.function = "KnippelOnCuracao";
			AddMapQuestMarkShore("Shore24", true);
		break;
		
		//Голландский гамбит /против всех/
		case "Tonzag_check"://начинаем проверять нашего ГГ по всем статьям
			if(sti(pchar.reputation.nobility) > 48)//высокая репа
			{
				// belamour legendary edition покажем критерии
				Notification_Reputation(false, 48, "high");
				PlaySound("Voice\English\hambit\Ercule Tongzag-03.wav");
				dialog.text = "나는 악당의 도움 따위 필요 없어. 너한테 맡길 일도 없어.";
				link.l1 = "이봐, 이봐. 말 좀 조심해, 친구!";
				link.l1.go = "exit";
				break;
			}
			bool bOk = GetSummonSkillFromName(pchar, SKILL_F_LIGHT) > 34 || GetSummonSkillFromName(pchar, SKILL_FENCING) > 34 || GetSummonSkillFromName(pchar, SKILL_F_HEAVY) > 34 || GetSummonSkillFromName(pchar, SKILL_PISTOL) > 34;
			if(!bOk)//слабое фехтование
			{
				// belamour legendary edition покажем критерии -->
				Notification_Skill(false, 35, SKILL_F_LIGHT);
				Notification_Skill(false, 35, SKILL_FENCING);
				Notification_Skill(false, 35, SKILL_F_HEAVY);
				Notification_Skill(false, 35, SKILL_PISTOL);
				// <--
				dialog.text = "선장, 너무 물러터졌군. 난 너보다 좀 더 명성 있는 싸움꾼이 필요해. 허리춤에 매단 칼이나 제대로 다루게 되면 다시 와라. 사격 실력도 좀 더 정확해지면 나쁠 것 없지.";
				link.l1 = "알겠소. 그럼 나중에 찾아가겠소.";
				link.l1.go = "exit";
				break;
			}
			PlaySound("Voice\English\hambit\Ercule Tongzag-02.wav");
			dialog.text = "흠... 제시간에 왔구나. 지금 당장 처리해야 할 일이 하나 있다. 네가 잘만 해내면, 영향력 있는 사람들에게 소개해 주지. 이제 잘 들어, 해야 할 일을 말해주겠다.";
			link.l1 = "듣고 있지.";
			link.l1.go = "Tonzag_task";
		break;
		
		case "Tonzag_task":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("Bridgetown");
			pchar.questTemp.HWIC.Self.SpainCity = FindSpainCity();
			log_Testinfo(pchar.questTemp.HWIC.Self.SpainCity);
			dialog.text = "세비야에서 온 이달고 한 명이 최근에 도착했네. 유럽에서 벌어진 결투의 불미스러운 결과를 피하려고 말이야. 하지만 복수에는 한계가 없지. 한 스페인 귀족 가문이 이 이달고의 죽음을 원하고 있네. 어떤 수단을 써서라도 그들의 의뢰를 완수하게.\n증거로 그 남자의 반지가 낀 손가락을 가져오게. 시신에서 발견한 다른 물건들도 모두 챙겨오고. 일을 맡을 준비가 되었나?";
			link.l1 = "보수가 괜찮으면 나도 끼지.";
			link.l1.go = "Tonzag_task_1";
			link.l2 = "암살자로 일하라고? 절대 안 돼!";
			link.l2.go = "Tonzag_exit";
			npchar.quest.HWICTake = "true";
			pchar.questTemp.HWIC.CanTake.Self = "true";//признак, что против всех уже бралась
		break;
		
		case "Tonzag_exit":
			dialog.text = "그럼 꺼져서 우리가 나눈 얘기는 다 잊어버려라.";
			link.l1 = "나 간다.";
			link.l1.go = "exit";	
			DeleteAttribute(pchar, "questTemp.HWIC.Self");//откат к двум другим вариантам
			pchar.questTemp.HWIC.Fail3 = "true";
			if(!CheckAttribute(pchar, "questTemp.HWIC.Fail1"))
			{
				AddMapQuestMarkCity("Villemstad", false);
				AddLandQuestMark(characterFromId("Lucas"), "questmarkmain");
			}
			if(!CheckAttribute(pchar, "questTemp.HWIC.Fail2"))
			{
				AddMapQuestMarkCity("SentJons", false);
				AddLandQuestMark(characterFromId("Knippel"), "questmarkmain");
			}
		break;
		
		case "Tonzag_task_1":
			dialog.text = "보상은 30,000피스의 에이트, 꽤 쓸 만한 돈이지. 거기에 더해, 놈 시체에서 찾은 동전은 전부 가져도 된다. 이제 세부 사항을 이야기하자. 이름은 돈 페르난도 로드리게스, 35세, 키 크고, 피부가 어둡고, 군 장교처럼 입고 다닌다. 항해 실력도 좋고, 검술에도 능하다\n어디에 있는지는 모르겠고, 내가 아는 건 그가 카리브 어딘가에 있다는 것뿐이야\n스페인 도시마다 샅샅이 뒤져서 놈을 잡아라. 기한은 두 달이다. 마지막으로 한 가지 더 말해두지. 그가 가지고 있는 물건에 대해 나는 다 알고 있으니, 내게 숨길 생각은 하지 마라. 질문 있나?";
			link.l1 = "질문 없어. 이제 간다!";
			link.l1.go = "Tonzag_task_2";	
		break;
		
		case "Tonzag_task_2":
			DialogExit();
			pchar.questTemp.HWIC.Self = "start";
			SetFunctionTimerCondition("TargetFernandoOver", 0, 0, 60, false); //таймер
			//SetFunctionExitFromLocationCondition("CreateMapMarksTonzag", pchar.location, false);
			AddQuestRecord("Holl_Gambit", "3-1");
			ReOpenQuestHeader("Holl_Gambit"); // данила . чтобы вышел из архива																				  
			Log_TestInfo(""+XI_ConvertString("Colony"+pchar.questTemp.HWIC.Self.SpainCity)+"");
			DelLandQuestMark(npchar);
			DelLandQuestMark(characterFromId("Lucas"));
			DelLandQuestMark(characterFromId("Knippel"));
			DelMapQuestMarkCity("Bridgetown");
			DelMapQuestMarkCity("Villemstad");
			DelMapQuestMarkCity("SentJons");
			AddMapQuestMarkCity(pchar.questTemp.HWIC.Self.SpainCity, true);
			AddLandQuestMark(characterFromId(pchar.questTemp.HWIC.Self.SpainCity+"_tavernkeeper"), "questmarkmain");
		break;
		
		case "Task_check":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("bridgetown");
			dialog.text = "반지 낀 손가락을 가지고 있나? 내게 좀 보여 줘.";
			if (CheckCharacterItem(pchar, "Finger"))
			{
				link.l1 = "그래, 물론이지. 여기 있다.";
				link.l1.go = "Task_check_1";	
			}
			else
			{
				link.l1 = "아니. 페르난도는 그의 배와 함께 물속으로 가라앉았고, 그 손가락도 페르난도와 함께 가라앉았어.";
				link.l1.go = "Task_fail";	
			}
		break;
		
		case "Task_fail":
			dialog.text = "반지 낀 손가락은 계약의 필수 조건이었지. 그게 의뢰인의 죽음을 증명하는 증거였거든. 로드리게스가 침몰한 배에서 육지까지 살아남았는지 누가 알겠어? 확인해 봤나? 아니지. 사실상 임무를 실패한 셈이니, 우리 계약은 끝이다. 행운을 빌지.";
			link.l1 = "하지만 내가 그 자를 처리했어. 이제 끝났지! 젠장할 놈... 카리브에는 할 일이 아직 많아. 잘 있어라.";
			link.l1.go = "exit";
			if(!CheckAttribute(pchar, "questTemp.HWIC.Fail1"))
			{
				AddMapQuestMarkCity("Villemstad", false);
				AddLandQuestMark(characterFromId("Lucas"), "questmarkmain");
			}
			if(!CheckAttribute(pchar, "questTemp.HWIC.Fail2"))
			{
				AddMapQuestMarkCity("SentJons", false);
				AddLandQuestMark(characterFromId("Knippel"), "questmarkmain");
			}
			pchar.questTemp.HWIC.Fail3 = "true";
			AddQuestRecord("Holl_Gambit", "3-8");
			CloseQuestHeader("Holl_Gambit");
			DeleteAttribute(pchar, "questTemp.HWIC.Self");//зачищаем для возможности отката к голландскому варианту
		break;
		
		case "Task_check_1":
			RemoveItems(PChar, "Finger", 1);
			dialog.text = "훌륭해! 손가락은 내가 직접 챙기지. 이제, 저 자의 주머니에 뭐가 들었는지 보자고. 네가 가져온 것도 한번 볼까.";
			link.l1 = "자, 한번 봐봐...";
			link.l1.go = "Task_check_2";	
		break;
		
		case "Task_check_2":
			if (CheckCharacterItem(pchar, "jewelry7") && CheckCharacterItem(pchar, "totem_05") && CheckCharacterItem(pchar, "amulet_1"))
			{
				dialog.text = "아하, 이거면 충분해. 잘했어! 정말 수고했구나. 나는 네가 아주 마음에 들어.";
				link.l1 = "고마워! 일을 잘했다고 칭찬받으면 언제나 기분이 좋지.";
				link.l1.go = "Task_complete";	
			}
			else
			{
				dialog.text = "흠... 내가 경고했지, 로드리게스가 절대 없이 못 사는 게 뭔지 안다고. 그런데 내가 필요한 건 여기 없어. 네가 그 물건들을 슬쩍한 거냐? 아니면 잃어버린 거냐? 어차피 상관없어. 더 이상 너랑 엮이고 싶지 않다. 당장 꺼져.";
				link.l1 = "아, 젠장할 놈...";
				link.l1.go = "exit";
				pchar.questTemp.HWIC.Fail3 = "true";
				if(!CheckAttribute(pchar, "questTemp.HWIC.Fail1"))
				{
					AddMapQuestMarkCity("Villemstad", false);
					AddLandQuestMark(characterFromId("Lucas"), "questmarkmain");
				}
				if(!CheckAttribute(pchar, "questTemp.HWIC.Fail2"))
				{
					AddMapQuestMarkCity("SentJons", false);
					AddLandQuestMark(characterFromId("Knippel"), "questmarkmain");
				}
				AddQuestRecord("Holl_Gambit", "3-9");
				CloseQuestHeader("Holl_Gambit");
				DeleteAttribute(pchar, "questTemp.HWIC.Self");//зачищаем для возможности отката к голландскому варианту
			}
		break;
		
		case "Task_complete":
			RemoveItems(PChar, "jewelry7", 1);
			RemoveItems(PChar, "totem_05", 1);
			RemoveItems(PChar, "amulet_1", 1);
			AddMoneyToCharacter(pchar, 30000);
			dialog.text = "약속한 보상이다, 삼만이다. 그리고 추가로, 책임이 크고 위험도 높은 임무가 하나 더 있는데, 그만큼 보수도 오른다네: 사만 페소지.";
			link.l1 = "듣고 있지. 다음 손님이 누구야?";
			link.l1.go = "Fleetwood_house";	
		break;
		
		//2 задание
		case "Fleetwood_house":
			PlaySound("Voice\English\hambit\Ercule Tongzag-05.wav");
			dialog.text = "이번에는 사람을 사냥하는 게 아니라 물건을 훔쳐야 해. 너는 앤티과에 있는 리처드 플리트우드의 집에 몰래 들어가서 그의 항해일지를 훔쳐와야 한다. 그는 영국 선장이야. 그 집은 경비가 삼엄하고, 리처드 본인도 집에 잘 오지 않아\n계획은 간단하다. 열흘 뒤에 세인트 존스의 총독이 비공개 파티를 열 건데, 플리트우드가 참석할 거야. 너는 밤 1시에서 3시 사이에 그의 집에 들어가야 한다. 안에는 병사 한 명만 있을 거다\n그놈을 처리해. 리처드의 방 안에서 항해일지를 찾아라. 이 열쇠를 가져가.";
			link.l1 = "흠... 흥미롭군. 뭘 해야 하는지 알겠어. 이제 출발할 준비 됐어!";
			link.l1.go = "Fleetwood_house_1";	
		break;
		
		case "Fleetwood_house_1":
			GiveItem2Character(pchar, "key3");
			dialog.text = "조심해라. 내가 알려준 날짜 전에 집에 몰래 들어가지 마라. 그렇지 않으면, 잘해야 쫓겨나고, 운이 나쁘면 감옥 신세를 질 거다. 날짜와 시간을 다시 말해 봐라.";
			link.l1 = "정확히 열흘 후, 새벽 1시에서 3시 사이에.";
			link.l1.go = "Fleetwood_house_2";	
		break;
		
		case "Fleetwood_house_2":
			dialog.text = "좋아. 가도 된다. 행운을 빌지!";
			link.l1 = "고마워, Gaston.";
			link.l1.go = "Fleetwood_house_3";
		break;
		
		case "Fleetwood_house_3":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "3-10");
			pchar.questTemp.HWIC.Self = "theft";
			DeleteAttribute(pchar, "questTemp.HWIC.CanTake");//иные варианты более невозможны
			LocatorReloadEnterDisable("SentJons_houseSP3", "reload2", true);//комнату закроем
			pchar.GenQuestBox.SentJons_houseSP3_room = true;
			pchar.GenQuestBox.SentJons_houseSP3_room.box1.items.FleetwoodJournal = 1;//положим в комод СЖ
			pchar.GenQuestBox.SentJons_houseSP3_room.box1.items.sand_clock = 1;//и песочные часы
			AddDialogExitQuestFunction("CreateFleetwoodSoldiers");//4 солдат в доме
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			SetFunctionTimerCondition("FleetwoodJournalOver", 0, 0, 11, false);//таймер
			pchar.quest.Fleetwood_Journal.win_condition.l1 = "Timer";
			pchar.quest.Fleetwood_Journal.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.Fleetwood_Journal.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 9);
			pchar.quest.Fleetwood_Journal.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 9);
			pchar.quest.Fleetwood_Journal.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 9);
			pchar.quest.Fleetwood_Journal.win_condition.l2 = "Hour";
			pchar.quest.Fleetwood_Journal.win_condition.l2.start.hour = 0;
			pchar.quest.Fleetwood_Journal.win_condition.l2.finish.hour = 3;
			pchar.quest.Fleetwood_Journal.win_condition.l3 = "locator";
			pchar.quest.Fleetwood_Journal.win_condition.l3.location = "SentJons_town";
			pchar.quest.Fleetwood_Journal.win_condition.l3.locator_group = "reload";
			pchar.quest.Fleetwood_Journal.win_condition.l3.locator = "houseSP3";//доступно открывание двери
			pchar.quest.Fleetwood_Journal.function = "FleetwoodHouseEnter";
			pchar.quest.Fleetwood_Soldier.win_condition.l1 = "location";
			pchar.quest.Fleetwood_Soldier.win_condition.l1.location = "SentJons_houseSP3";
			pchar.quest.Fleetwood_Soldier.function = "Fleetwood_Soldier";//если надумает раньше заявиться
			AddMapQuestMarkCity("sentjons", true);
		break;
		
		case "guardoftruth":
			dialog.text = LinkRandPhrase("아니, 못 봤어. 약초사랑 의사들은 있지만, 그런 이름을 가진 사람은 없어.","이렇게 이상한 이름은 처음 들어보네. 아니, 네가 말한 그 남자는 우리한테 온 적 없어.","우리에겐 연금술사 같은 사람은 전혀 없어. 의사들은 있지만, 그런 이상한 이름을 가진 자는 없어.");
			link.l1 = "알겠어. 아쉽군. 계속 찾아볼게!";
			link.l1.go = "exit";
			npchar.quest.jino = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

string FindSpainCity()//Jason выбрать радномный испанский город - пусть побегает
{
	int n, nation;
    int storeArray[2];
	SetArraySize(&storeArray, MAX_COLONIES);
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		if (colonies[n].nation == SPAIN && colonies[n].id != "Panama" && colonies[n].id != "LosTeques" && colonies[n].id != "SanAndres" && colonies[n].nation != "none")
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	if (howStore == 0) return "none";
	nation = storeArray[hrand(howStore-1)];
	return colonies[nation].id;
}
