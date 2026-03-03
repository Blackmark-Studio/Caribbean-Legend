void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, Diag;
	string NPC_Meeting;	
	int Shit, i;
	ref refStore;
	ref sld;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
        case "exit":
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = NPC_Meeting;
			DialogExit();
		break;

        case "First time":
			Diag.TempNode = "first time";
			if(CheckAttribute(PChar, "quest.Contraband.active"))
			{
				int iTmp = false;
				int iChIdx;
				
				float fMaxClass = ((MOD_SKILL_ENEMY_RATE/5.0) + 1.5);
				if (IsEquipCharacterByArtefact(pchar, "talisman21")) fMaxClass = 2.0;
				
				if (GetCompanionQuantity(pchar) > 1) iTmp = true;
				if (GetCharacterShipClass(pchar) < fMaxClass) iTmp = true;

				// поиск мин.  те старшего класса
				/* for (i=0; i<COMPANION_MAX; i++)
				{
					iChIdx = GetCompanionIndex(GetMainCharacter(), i);
					if (iChIdx>=0)
					{
						sld = GetCharacter(iChIdx);
            			if (GetCharacterShipClass(sld) < ((MOD_SKILL_ENEMY_RATE/5.0) + 1.5)) iTmp = true;
					}
				} */
				
				if (iTmp)
				{
					dialog.text = NPCStringReactionRepeat("이렇게 눈에 띄는 배로 오지 말라고 하지 않았어! 전열함 두 척이라도 끌고 올 셈이냐? 꺼져, 그리고 더 작은 배로 다시 와.","나가! 아니면 우리가 직접 순찰대에 넘길 거야.","네 배로 가서 당장 떠나.","너무 지겨워...","block",1,npchar,Dialog.CurrentNode);
					link.l1 = HeroStringReactionRepeat("알겠어, 알겠어, 내 배를 바꿀게.","진정하시오, 내가 가는 중이오.","젠장, 될 줄 알았는데...","그래, 나는 정말 고집이 세지!",npchar,Dialog.CurrentNode);
						link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);	
					break;
				}
			
				Dialog.snd = "voice\SMSH\SMSH001";
				dialog.Text = RandPhraseSimple("이봐, 여기서 뭐 하고 있어, "+GetSexPhrase("친구","소녀")+"?",RandSwear()+"여기서 뭐 하는 거야?!");
				Link.l1 = "긴장 풀어, 친구야, 거래나 하자!";
				Pchar.quest.Contraband.Counter = 0; // не торговали
				if(Pchar.Location == Pchar.location.from_sea)
				{
					Link.l1.go = "Exchange";
				}
				else
				{
					Link.l1.go = "No_Ship";
				}
				//по заданию губернатора, истребление контры, только эта ветка.
				if (CheckAttribute(pchar, "GenQuest.KillSmugglers") && pchar.GenQuest.KillSmugglers == "" && pchar.GenQuest.KillSmugglers.Areal == GiveArealByLocation(&locations[FindLocation(pchar.location)]))				
				{
					Link.l2 = "나는 의 총독 명령을 받고 여기 왔다 "+XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.KillSmugglers.MayorId)].city+"Gen")+"무기 내려놓고 따라와! 너 체포됐어!";
					Link.l2.go = "GenQuestKillContraband_1";
				}
			}
			else
			{
//================ METRO ====================
				//если заплатил, то разговаривают, иначе посылают
				if (CheckAttribute(PChar, "GenQuest.contraTravel.payed") && sti(PChar.GenQuest.contraTravel.payed) == true)
				{
                    dialog.Text = RandPhraseSimple("아, 드디어 왔군! 우리가 기다리고 있었어. 가자, 이제 출항할 시간이야.","빨리 하자. 순찰대가 사방에 있어. 여기서 빨리 벗어나야 해!");
					//по заданию губернатора, истребление контры, только эта ветка.
					if (CheckAttribute(pchar, "GenQuest.KillSmugglers") && pchar.GenQuest.KillSmugglers == "" && pchar.GenQuest.KillSmugglers.Areal == GiveArealByLocation(&locations[FindLocation(pchar.location)]))
					{
						Link.l1 = "나는 주지사의 명령으로 여기 왔다 "+XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.KillSmugglers.MayorId)].city+"Gen")+"무기 내려놓고 따라와! 너 체포됐어!";
						Link.l1.go = "GenQuestKillContraband_1";
						break;
					}
					//если набрал пассажиров, в сад..
					if (GetPassengersQuantity(PChar) > 0)
					{
						dialog.Text = "너는 누구냐? 우리는 단 한 명의 승객에 대해 이야기하고 있었는데!";
						Link.l1 = "이런..";
						Link.l1.go = "Exit";
						break;
					}
					//если набрал компаньонов или купил корабль себе уже :), в сад..
					if (GetCompanionQuantity(PChar) > 1 || sti(PChar.ship.type) != SHIP_NOTUSED)
					{
						dialog.Text = RandPhraseSimple("누구시오? 우리는 선장이 아니라 승객을 기다리고 있었소.","꺼져! 네 배를 처분하기 전엔 다시 오지 마.");
						Link.l1 = "젠장!";
						Link.l1.go = "Exit";
						break;
					}
					//типа помог отбиться, свой парень... 
					if (CheckAttribute(PChar, "GenQuest.contraTravel.PatrolFight") && sti(PChar.GenQuest.contraTravel.PatrolFight) == true)
					{
						if (chrDisableReloadToLocation) // ещё бой идёт
						{
						    dialog.Text = "젠장, 순찰대다! 우리는 너를 모르고, 너도 우리를 몰라.";
							Link.l1 = "좋아...";
							Link.l1.go = "Exit";
							break;
						}
						dialog.Text = RandPhraseSimple("도와주셔서 감사합니다. 우리는 이 은혜를 잊지 않겠습니다. 이제 출항합시다.","잘했다! 멋지게 싸웠군. 이제 가자.");
						ChangeContrabandRelation(PChar, 5);
						PChar.GenQuest.contraTravel.PatrolFight = false;
						AddCharacterExpToSkill(Pchar, "Sneak", 50);
					}
					//тут все ок, отправляемся.
					Link.l2 = "나는 가는 중이다.";
					Link.l2.go = "Exit";
					//а это патруль... 
					if (GetSummonSkillFromNameToOld(Pchar, SKILL_SNEAK) < frandSmall(13.0*(1.0 - pow(0.9, sti(PChar.rank)))) && !CheckAttribute(PChar, "GenQuest.contraTravel.PatrolFight"))
					{
						AddDialogExitQuest("Rand_ContrabandInterruption");
						PChar.GenQuest.contraTravel.PatrolFight = true;
					}
					else 
					{
						//поместим Грея в локацию.
						refStore = CharacterFromID("Abracham_Gray");
						ChangeCharacterAddressGroup(refStore, "Ship_deck", "goto", "goto2");
						refStore.dialog.Filename = "Smuggler_Ship_dialog.c";
                        refStore.dialog.CurrentNode = "Travel_talkStart";
						//поплыл, иначе RemoveTravelSmugglers грохнет всю ветку
						PChar.GenQuest.contraTravel.ship = true;
						PChar.quest.Munity = "";  // признак выхода с палубы
						
						SetLaunchFrameFormParam(".. " + sti(Pchar.GenQuest.contraTravel.destination.days) + " days passed." + NewStr() + "Smuggler's ship deck.",
						                        "Reload_To_Location", 0.1, 5.0);
                        bQuestCheckProcessFreeze = true;
						WaitDate("", 0, 0, sti(Pchar.GenQuest.contraTravel.destination.days), rand(20), 0);
						bQuestCheckProcessFreeze = false;
						MakeCloneShipDeck(refStore, true); // подмена палубы
						SetLaunchFrameReloadLocationParam("Ship_deck", "reload", "reload1", "Travel_talkOnDeck");
						AddDialogExitQuest("LaunchFrameForm");
						AddCharacterExpToSkill(Pchar, "Sneak", 50);
					}
//================ METRO ====================
				}
				else
				{
                    // если таможня уже бежит
					if (CheckAttribute(NPChar, "ContrabandInterruption"))
					{
					    dialog.Text = RandSwear()+"순찰대다! 우리는 너를 모르고, 너도 우리를 모른다.";
						Link.l1 = "좋아!";
						Link.l1.go = "Exit";
					}
					else
					{
						dialog.Text = "꺼져! 우리 거래 망치면 네 배를 갈라버릴 거야.";
						Link.l1 = RandPhraseSimple("감히 나를 협박해? 이 잡놈아!?","네 말에 스스로 목이 멜 거다!");
						Link.l1.go = "Exit_fight";
						Link.l2 = "걱정 마, 내가 장사 이치쯤은 잘 아니까. 잘 가.";
						Link.l2.go = "Exit";
					}
				}
			}
		break;

		case "No_Ship":
			Dialog.snd = "voice\SMSH\SMSH003";
			dialog.Text = "등에 메고 다니는 거야? 네 배는 어디 있지?";
			Link.l1 = RandPhraseSimple("우선, 뭔가 함정이 있는지 확인해 보고 싶군.","배를 위험에 빠뜨리고 싶지 않았어. 나는 직접 내 두 눈으로 모든 걸 확인하는 게 좋아.");
			Link.l1.go = "No_ship_1";
			Link.l2 = "거래는 끝났다!";
			Link.l2.go = "Cancellation";
		break;

		case "No_ship_1":
			Dialog.snd = "voice\SMSH\SMSH004";
			dialog.Text = "우린 정직한 사람들이니 속이지 않아. 네 배를 여기로 가져와. 단, 순찰대가 따라오게 하진 마.";
			Link.l1 = "좋아. 여기서 기다려.";
			Link.l1.go = "Exit";
		break;

		case "Cancellation":
            if (sti(Pchar.quest.Contraband.Counter) == 0)
            {
    			dialog.Text = "끝났다고? 농담하는 거지!";
    			Link.l1 = "나는 진지하다.";
    			Link.l1.go = "Cancellation_1";
			}
			else
            {
    			dialog.Text = "좋아, 그럼. 오늘은 어차피 거래가 잘됐으니까.";
    			Link.l1 = "정답이야!";
    			Link.l1.go = "Finish_exit";
			}
		break;

		case "Cancellation_1":
			if( makeint(Pchar.rank) <= 3 || GetSummonSkillFromNameToOld(Pchar, SKILL_FENCING) <= 5 || GetSummonSkillFromNameToOld(Pchar, SKILL_LEADERSHIP) <= 5 )
			{
				if(Rand(1) == 1)
				{
					ChangeContrabandRelation(pchar, -30);
					Dialog.snd = "voice\SMSH\SMSH006";
					dialog.Text = "이 자식아! 그렇게 쉽게 우리를 속일 수 있을 줄 알았냐! 네 목으로 대가를 치르게 될 거다!";
					Link.l1 = "의심스럽군!";
					Link.l1.go = "Exit_fight";			
				}
				else
				{
					ChangeContrabandRelation(pchar, -10);
					Dialog.snd = "voice\SMSH\SMSH007";
					dialog.Text = "그렇게는 못 넘어갈 거야!";
					Link.l1 = "다른 데 가서 짖어라, 이 개놈들아!";
					Link.l1.go = "Exit_cancel";
				}
			}	
			else
			{
				ChangeContrabandRelation(pchar, -10);
				Dialog.snd = "voice\SMSH\SMSH008";
				dialog.Text = "그렇게 하면 후회하게 될 거야!";
				Link.l1 = "너 말이 너무 많아.";
				Link.l1.go = "Exit_cancel";			
			}	
		break;

		case "GenQuestKillContraband_1":
			//счетчик подстав по "метро"...
			if(CheckAttribute(PChar, "GenQuest.contraTravel.active") && sti(PChar.GenQuest.contraTravel.active) == true)
			{
				Statistic_AddValue(PChar, "contr_TravelKill", 1);
				ChangeContrabandRelation(pchar, -20); //репу контры вниз
			}
			dialog.Text = "그 대가를 치르게 될 거다!";
			Link.l1 = "그럼 너희는 전부 죽은 목숨이다. 나는 명확한 명령을 받았어 - 저항하면 모두 처치하라는 거지.";
			Link.l1.go = "Exit_fight";
		break;
		
		case "Exit_Cancel":
            DeleteAttribute(Pchar, "quest.Contraband");
            CloseQuestHeader("Gen_Contraband");
			Pchar.quest.Rand_Smuggling.over = "yes";
			RemoveSmugglersFromShore();
			RemoveAllContraGoods(CharacterFromId(pchar.GenQuest.Contraband.SmugglerId));
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = NPC_Meeting;
			DialogExit();
		break;
		
		case "Exit_fight":
            DeleteAttribute(Pchar, "quest.Contraband.active");
			DeleteAttribute(Pchar, "quest.Contraband.counter");			

			AddSimpleRumourCity("Heard the latest news? The local smugglers were rounded up by a patrol not long ago. And you know what? Captain who had a deal with them escaped!" +
				"He had dashing lads in his crew and the whole patrol was killed. And our local smugglers just vanished. There was nothing found on the shore. No goods, no stash and smugglers. See, how they do their business here!", Pchar.quest.contraband.City, 3, 5, "");	

			CloseQuestHeader("Gen_Contraband");
			Pchar.quest.Rand_Smuggling.over = "yes";
			LAi_group_FightGroups(LAI_GROUP_PLAYER, pchar.GenQuest.Smugglers_Group, true);
			RemoveSmugglersFromShore();
			RemoveAllContraGoods(CharacterFromId(pchar.GenQuest.Contraband.SmugglerId));
			LAi_SetFightMode(Pchar, true);

			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = NPC_Meeting;
			DialogExit();
		break;

		case "Finish_exit":
            // таможня на суше
            if(GetSummonSkillFromName(pchar, "Sneak") < Rand(120))
			{
				AddDialogExitQuest("Rand_ContrabandInterruption");
				for (i=1; i<=3; i++)
				{
					characters[GetCharacterIndex("Rand_Smug0"+i)].ContrabandInterruption = true;
				}
			}
			AddCharacterExpToSkill(Pchar, "Sneak", 100);
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = NPC_Meeting;
			DialogExit();
			ChangeContrabandRelation(pchar, 15);
            OfficersReaction("bad");
            ChangeCharacterComplexReputation(pchar,"nobility", -1);
            
            CloseQuestHeader("Gen_Contraband");
            
			DeleteAttribute(Pchar, "quest.Contraband.active");
			DeleteAttribute(Pchar, "quest.Contraband.counter");
	
			Pchar.quest.Rand_Smuggling.over = "yes";
			RemoveSmugglersFromShore();
			RemoveAllContraGoods(CharacterFromId(pchar.GenQuest.Contraband.SmugglerId));
		break;

		case "Exchange":
			// сама торговля -->
            if(FindContrabandGoods(Pchar) == -1 && sti(Pchar.quest.Contraband.Counter) == 0)
            {
				dialog.Text = "여기서 뭐 하는 거야? 팔 것도 없잖아! 네 화물에 있는 물건들은 전부 마을에서 팔 수 있어!";
				Link.l1 = "이번엔 운이 없었군.";
				Link.l1.go = "NoGoods";
			}
			else
			{
                // установим окружение -->
                if (sti(Pchar.quest.Contraband.Counter) == 0) // не торговали ещё
                {
                    if(hrand(11) == 3)
                    {
        				dialog.Text = "알겠군... 있잖아, 네 물건은 우리가 공짜로 가져가겠다. 어차피 네가 불평할 수 있을 것 같지도 않으니까.";
        				Link.l1 = "해봐라, 이 쓰레기야!";
        				Link.l1.go = "Exit_fight";
                        break;
        			}
        			// море и солдаты на суше НЕЗАВИСИМЫ!!!
        			if(GetSummonSkillFromNameToOld(Pchar, SKILL_SNEAK) < Rand(12))
        			{
                        SetCoastalGuardPursuit();
        			}
        			// при убегании от патруля на карту - корабли трем
        			SetTimerCondition("Rand_ContrabandInterruptionAtSeaEnded", 0, 0, 2, false);// если в порту сидим, спим, то 2 день
        			
                    Pchar.quest.Rand_ContrabandAtSeaEnded.win_condition.l1 = "MapEnter";
        			Pchar.quest.Rand_ContrabandAtSeaEnded.win_condition = "Rand_ContrabandAtSeaEnded";
    			}
    			// установим окружение <--
				dialog.text = "좋아, 어디 한번 네가 가진 걸 보자.";										  
				Link.l1 = "뭘 가지고 있는지 보여줘.";
				Link.l1.go = "Exchange1"; 
				if (sti(Pchar.quest.Contraband.Counter) == 0)
    			{
        			Link.l99 = "내 마음이 바뀌었어.";
    				Link.l99.go = "Cancellation";
				}				
            }
		break;
		
		case "Exchange1":
			NPChar.quest.meeting = NPC_Meeting;
			Diag.CurrentNode = Diag.TempNode;		 
			DialogExit();
			// belamour legendary edition опасный груз
			pchar.GenQuest.Smugglerzpq = npchar.id;
			
			LaunchContrabandTrade(CharacterFromId(pchar.GenQuest.Contraband.SmugglerId),  sti(pchar.FindContrabandGoods.StoreIdx));	
		break;				
		// belamour legendary edition опасный груз -->
		case "SmugglerZPQ":
			dialog.text = "좋은 거래였어요, 선장님! 다른 흥미로운 물건이 있으면 꼭 알려주십시오!";										  
			Link.l1 = "동의하오, 나 역시 이번 거래에 만족하오. 아, 내 물건을 항상 이런 좋은 값에 살 수만 있다면...";
			Link.l1.go = "SmugglerZPQ_1"; 
		break;

		case "SmugglerZPQ_1":
			dialog.text = "왜 우리가 평범한 물건을 그런 값에 사야 하지? 가게에서 합법적으로 살 수 있는데 말이야. \n하지만 실망하지 마. 사실 어떤 상품이든 팔 수 있어, 평범한 화약조차도! \n하늘 높은 줄 모르는 가격에 팔 수도 있지 — 단지 어디서 파는지 알기만 하면 돼.";										  
			Link.l1 = "가자. 누가 이런 터무니없이 비싼 값에 화약을 사겠어?";
			Link.l1.go = "SmugglerZPQ_2"; 
		break;
		
		case "SmugglerZPQ_2":
			dialog.text = "글쎄, 내가 이미 말했잖아, 헤헤... 하지만... 있잖아, 화약을 팔아서 큰돈을 벌 기회가 진짜 있긴 해. 그래도 그건 우리 같은 놈들이 할 수 있는 장사는 아니야. 그런 거래를 하려면 꽤 괜찮은 평판이 있어야 하거든. 우리야, 알다시피, 귀족도 아니고.";										  
			Link.l1 = "글쎄, 내가 한번 알아볼 수도 있지. 필요할 땐 착하고 친절하게 굴 수도 있으니까. 그 거래에 대해 말해줄 수 있나?";
			Link.l1.go = "SmugglerZPQ_3"; 
		break;
		
		case "SmugglerZPQ_3":
			dialog.text = "이 세상에 공짜는 없소, 선장님, 정보도 마찬가지요. 아니, 오히려 정보야말로 값이 더 나간다 할 수 있지. 내 제안이 있소: 이 정보를 상징적인 금액, 그러니까 오천 페소에 넘기겠소. 어떻소, 괜찮겠소?";										  
			Link.l1 = "의심스러운 정보에 오천 페소나 내고 화약을 비싸게 팔 수 있는 곳을 알려달라고? 아니, 이런 팁 없이도 내가 알아서 할 수 있을 것 같군.";
			Link.l1.go = "SmugglerZPQ_NM"; 
			if(sti(pchar.money) > 4999)
			{
				Link.l2 = "이 거래로 오천 달러보다 더 벌 수 있을 것 같아. 좋아, 동의하지.";
				Link.l2.go = "SmugglerZPQ_4";
			}
		break;	
		
		case "SmugglerZPQ_NM":
			npchar.Dialog.CurrentNode = "first time";
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar,"GenQuest.Smugglerzpq");
			dialog.text = "선장님이 결정하시오. 어쨌든, 우리는 좋은 거래를 했소. 행운을 빌겠소... 그리고 순찰대랑 마주치지 마시오!";										  
			Link.l1 = "너도. 잘 가.";
			Link.l1.go = "exit"; 
		break;
		
		case "SmugglerZPQ_4":
			AddMoneyToCharacter(pchar, -5000);
			dialog.text = "훌륭합니다, 선장님! 정말 뛰어난 손님이시군요. 자, 들어보십시오. 본토의 몇몇 스페인 도시에서 화약 문제가 있다는 소문을 들었습니다. 열대성 폭우 때문인지, 다른 이유 때문인지는 모르겠지만, 어쨌든 식민지를 지키는 요새에 비축된 화약이 매우 적다고 합니다. 그리고 이 요새의 사령관이 이 어려운 상황에서 도와줄 사람을 찾고 있답니다.\n문제는 두 가지입니다. 첫째, 이건 아주 민감한 일이라서 사령관이 아무 해적하고는 상의하지 않을 겁니다. 둘째, 아주 대규모 화물이라서 아무 배로나 실을 수 없으니 함대가 필요할 수도 있습니다. 게다가, 모든 선장이 자기 배를 떠돌이 포탄 한 방에 섬 전체를 날려버릴 수 있는 화약덩어리로 만들고 싶어 하지는 않을 테니 말이죠.";
			if(CheckAttribute(pchar,"questTemp.zpq"))
			{
				Link.l1 = "미안하지만, 이 거래에 대해서는 이미 알고 있어. 그래도 이 거래는 돈보다 더 가치 있으니, 오천은 받을 자격이 있지.";
				Link.l1.go = "SmugglerZPQ_5"; 
			}
			else
			{
				Link.l1 = "귀중한 정보군, 고맙네. 내가 메인에 가게 되면, 그곳 요새의 지휘관들에게 그들의 불운에 대해 물어보겠네. 그리고 어떻게든 내가 이 문제들을 해결하거나, 아니면 이용해 먹을 수 있겠지, 허허.";
				Link.l1.go = "SmugglerZPQ_6"; 
			}
		break;
		
		case "SmugglerZPQ_5":
			npchar.Dialog.CurrentNode = "first time";
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar,"GenQuest.Smugglerzpq");
			dialog.text = "원래 그런 법이지. 어쨌든, 우린 좋은 거래를 했어. 행운을 빌어... 그리고 순찰대랑 마주치지 마라!";										  
			Link.l1 = "너도. 잘 가.";
			Link.l1.go = "exit"; 
		break;
		
		case "SmugglerZPQ_6":
			npchar.Dialog.CurrentNode = "first time";
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar,"GenQuest.Smugglerzpq");
			AddQuestRecord("zpq", "0");
			dialog.text = "원래 그런 법이지. 어쨌든, 우리 좋은 거래였어. 행운을 빌어... 그리고 순찰대랑 마주치지 마!";										  
			Link.l1 = "너도. 잘 가.";
			Link.l1.go = "exit"; 
		break;
		// <-- legendary edition опасный груз
	}
}
