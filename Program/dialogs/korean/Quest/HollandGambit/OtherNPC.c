// диалоги прочих НПС
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "버그다. 개발자들에게 알려라.";
			link.l1 = "내가 하겠소!";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			if (npchar.id == "HWICFernando") NextDiag.CurrentNode = "Fernando";
			DialogExit();
		break;
	
//---------------------------------------за Голландию--------------------------------------------------
		//сопроводить торговца
		case "Baltazar":
			pchar.quest.Create_BaltazarOver.over = "yes";//снять прерывание
			dialog.text = "이런 행운이 있나! 선장님, 마침 필립스버그까지 급히 호위를 부탁드릴 일이 있소...";
			link.l1 = "당신이 발타자르 리더복이오?";
			link.l1.go = "Baltazar_1";
			DelLandQuestMark(npchar);
		break;
		
		case "Baltazar_1":
			dialog.text = "이런 젠장, 나 이미 총독보다 더 유명하잖아! 너 누구야? 뭘 원하는데?";
			link.l1 = "나는 선장이오 "+GetFullName(pchar)+". 나는 루카스 로덴부르크에게서 파견되었소. 나는 당신과 당신의 배를 내 보호 아래 둘 권한이 있소.";
			link.l1.go = "Baltazar_2";			
		break;
		
		case "Baltazar_2":
			dialog.text = "오, 로덴부르크 나리께서 내 도움 요청을 들으셨나 보군! 있잖소, 여기 사략선이...";
			link.l1 = "네 이야기의 자세한 내용은 생략하자, 이미 다 알고 있으니.";
			link.l1.go = "Baltazar_3";			
		break;
		
		case "Baltazar_3":
			dialog.text = "물론이지! 이미 너무 많은 시간을 허비했어... 아무리 늦어도 2주 안에는 필립스버그에 도착해야 해.";
			link.l1 = "그럼 네 배로 가서 출항 준비를 해라. 곧바로 출항한다!";
			link.l1.go = "Baltazar_4";			
		break;
		
		case "Baltazar_4":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 4);
			SetCharacterRemovable(npchar, false);
			npchar.CompanionEnemyEnable = false; //всегда друзья
			SetCompanionIndex(pchar, -1, sti(npchar.index));
			npchar.loyality = MAX_LOYALITY;
			AddQuestRecord("Holl_Gambit", "1-3");
			AddMapQuestMarkCity("Marigo", true);
			if(bImCasual)
			{
				NewGameTip("Exploration mode: quest duration doubled");
				SetFunctionTimerCondition("Baltazar_ConvoyOver", 0, 0, 28, false);
			}
			else SetFunctionTimerCondition("Baltazar_ConvoyOver", 0, 0, 14, false); //таймер
			pchar.quest.BaltazarConvoy_fail.win_condition.l1 = "NPC_Death";//прерывание на потопление сопровождаемого
			pchar.quest.BaltazarConvoy_fail.win_condition.l1.character = "Baltazar";
			pchar.quest.BaltazarConvoy_fail.function = "Baltazar_fail";
			pchar.quest.BaltazarConvoy_complete.win_condition.l1 = "location";//прерывание на выполнение
			pchar.quest.BaltazarConvoy_complete.win_condition.l1.location = "Marigo_town";
			pchar.quest.BaltazarConvoy_complete.function = "Baltazar_complete";
			if (rand(1) == 0)
			{
				BaltazarPirateGlobalCreate();
			}
			else
			{
				pchar.questTemp.HWIC.Holl.BaltazarAttack = "true";
				pchar.quest.BaltazarConvoy_Attack.win_condition.l1 = "location";//прерывание на выполнение
				pchar.quest.BaltazarConvoy_Attack.win_condition.l1.location = "SentMartin";
				pchar.quest.BaltazarConvoy_Attack.function = "BaltazarPirateSeaCreate";
			}
		break;
		
		case "Baltazar_5":
			dialog.text = "도와주셔서 감사합니다, 선장님! 선장님의 보호가 이보다 더 적절할 수는 없었소. 제 감사의 뜻과 함께 이 5,000페소를 받아주십시오.";
			link.l1 = "흠... 목숨을 구해줬는데 보상이 그리 후하지는 않군...";
			link.l1.go = "Baltazar_6";			
		break;
		
		case "Baltazar_6":
			dialog.text = "게다가 기회가 되면 로덴부르크 나리께도 편지를 보내겠소 – 그대의 행동을 최대한 높이 평가해서 말이오. 이제 가봐야겠소.";
			link.l1 = "그래, 그럼 잘 가라, 발타자르.";
			link.l1.go = "Baltazar_7";			
		break;
		
		case "Baltazar_7":
			DialogExit();
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2_back", "none", "", "", "", 3.0);
			AddQuestRecord("Holl_Gambit", "1-6");
			AddMoneyToCharacter(pchar, 5000);
			ChangeCharacterComplexReputation(pchar,"nobility", 2); 
			ChangeCharacterNationReputation(pchar, HOLLAND, 1);
			ChangeOfficersLoyality("good_all", 1);
			pchar.questTemp.HWIC.Holl = "BaltazarCom";
			AddLandQuestMark(characterFromId("Lucas"), "questmarkmain");
			AddMapQuestMarkCity("Villemstad", true);
		break;
		
		//командировка в Сантьяго
		case "Santiago_Trip":
			dialog.text = "나리! 잠깐만요... 뭔가 떨어뜨리신 것 같은데요...";
			link.l1 = "뭐? 어?!";
			link.l1.go = "Santiago_Trip_1";
		break;
		
		case "Santiago_Trip_1":
			DialogExit();
			PlaySound("People Fight\Death_NPC_08.wav");
			pchar.GenQuest.FrameLockEsc = true;
			SetLaunchFrameFormParam("You were knocked unconscious from behind", "", 0, 4);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 15, 10); //крутим время
			RecalculateJumpTable();
			DoQuestFunctionDelay("SantiagoTripInHouse", 4.0);
		break;
		
		case "Santiago_Trip_2":
			dialog.text = "미안하다, 친구야 – 네가 말썽 부리지 않게 살짝 한 대 때릴 수밖에 없었어. 머리가 좀 아플 거라는 건 알지만, 뭐 어쩔 수 없지, 살아남을 거야. 시간이 허락한다면 말이지...\n";
			link.l1 = "너 대체 누구야, 젠장, 그리고 여기서 무슨 일이 벌어지고 있는 거야?";
			link.l1.go = "Santiago_Trip_3";
		break;
		
		case "Santiago_Trip_3":
			dialog.text = "진정해, 진정하라고, 친구. 또다시 네 놈을 진정시켜야 하나? 저 꼰대들이 녹슨 칼 휘두르며 들이닥치는 꼴은 보고 싶지 않잖아? 조용히 얘기 좀 하자고.";
			link.l1 = "내 칼 돌려줘, 이 자식아, 그러면 제대로 얘기해 줄게, 맹세한다!";
			link.l1.go = "Santiago_Trip_4";
		break;
		
		case "Santiago_Trip_4":
			dialog.text = "너 제법 재빠른 녀석이구나, 그렇지? 지금은 칼을 쓸 필요 없어. 내가 알고 싶은 걸 말하면, 어쩌면 네 몸뚱이 멀쩡히 이곳을 나갈 수도 있겠지. 내 말 이해했나? 자, 잠깐 이야기 좀 해보자고.\n입 다물겠다는 건가? 좋아, 그럼 거래가 성사된 거지. 로덴부르크에서 은행가에게 뭘 운반했지?";
			link.l1 = "편지요.";
			link.l1.go = "Santiago_Trip_5";
		break;
		
		case "Santiago_Trip_5":
			dialog.text = "영리하군. 데이지 꽃다발이 아니었다는 건 알아. 그 편지에 뭐가 들어 있었지, 이 녀석?";
			link.l1 = "내가 어떻게 알겠어? 나한테 맡겨진 편지를 읽는 버릇은 없거든. 어쩌면 연애편지였을지도 모르지. 권력자들에 대해 사람들이 뭐라고 하는지 알잖아...";
			link.l1.go = "Santiago_Trip_6";
		break;
		
		case "Santiago_Trip_6":
			dialog.text = "...정직한 선장은 이 비참한 시대에 정말 보기 드문 존재지. 뭐, 그건 너한테는 나쁜 소식이군. 그 빌어먹을 은행원이 소포를 받았을 때 뭐라고 했지? 그 자가 네덜란드 놈들과 무슨 거래를 하고 있던 거야?\n";
			link.l1 = "프랑스에서 밀수한 향수를 거래하고 있어... 아니면 바이에른 소똥일지도 몰라, 내 생각엔.";
			link.l1.go = "Santiago_Trip_7";
			link.l2 = "보상에 관한 질문이었소. 내가 아는 건 그게 전부요.";
			link.l2.go = "Santiago_Trip_8";
		break;
		
		case "Santiago_Trip_7":
			dialog.text = "자네는 용감한 녀석이군... 게다가 유머 감각도 있지. 자네를 죽이기엔 아까운걸. 가스통도 자네를 좋아했을 거야. 하지만... 당분간 여기 머물게. 내가 뭔가 확인하러 가야 하니, 내가 없는 동안 미겔이 자네를 돌볼 거다.";
			link.l1 = "맹세컨대, '내 친구' – 너 반드시 후회하게 될 거야! ";
			link.l1.go = "Santiago_Trip_9";
		break;
		
		case "Santiago_Trip_8":
			dialog.text = "거만함은 이제 그만두는군... 상황이 나빠지니 우리 용감한 선장님도 이성을 찾으셨네. 진작 그렇게 했으면 시간과 수고를 아꼈을 텐데. 자, 나는 뭘 좀 확인하러 가야 하니 잠시 자리를 비우겠소. 돌아오면 아직 할 얘기가 남아 있다면 다시 이야기하지. 그동안은 여기서 기다리시오. 내가 없는 동안 미겔이 당신을 돌볼 거요.";
			link.l1 = "맹세코, '내 친구' – 너 이 일 후회하게 될 거야! ";
			link.l1.go = "Santiago_Trip_11";
		break;
		
		case "Santiago_Trip_9":
			dialog.text = "물론이지. 조용히 해, '영웅'아 - 어쩌면 아직 다 잘될지도 모르니.";
			link.l1 = "...";
			link.l1.go = "Santiago_Trip_11";
		break;
		
		case "Santiago_Trip_10":
			dialog.text = "여기 남아서 네 융통성이 값어치를 하길 바라.";
			link.l1 = "...";
			link.l1.go = "Santiago_Trip_11";
		break;
		
		case "Santiago_Trip_11":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "1-44");
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "Santiago_HouseSp2", "goto", "goto4", "", -1);
			pchar.quest.Santiago_Trip1.win_condition.l1 = "item";
			pchar.quest.Santiago_Trip1.win_condition.l1.item = "slave_01";
			pchar.quest.Santiago_Trip1.function = "SantiagoTrip_wait";
		break;
		
		case "Santiago_Trip_12":
			dialog.text = "이게 뭐야?!";
			link.l1 = "죽을 준비나 해라, 이 악당놈아!";
			link.l1.go = "Santiago_Trip_13";
		break;
		
		case "Santiago_Trip_13":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "SantiagoTripExitFromRoom");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "Santiago_Trip_14":
			dialog.text = "엉망진창이군! 이 소란이 뭔가 했더니 이런 일이었구나. 축하하네 - 자네, 제법 똑똑한 녀석이야!";
			link.l1 = "네가 생각하는 것보다 더 똑똑하군... 이제 무장한 적을 상대로 뭘 할 수 있는지 보자고!";
			link.l1.go = "Santiago_Trip_15";
		break;
		
		case "Santiago_Trip_15":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "SantiagoTripExitHouse");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		//офицер-посланник по 5 заданию
		case "HollQuest_Officer":
			dialog.text = "루카스 로덴부르흐 나리께서 지금 당장 당신을 보자고 하셨소. 즉시 그분께 가시오.";
			link.l1 = "가는 중이오.";
			link.l1.go = "HollQuest_Officer_exit";			
		break;
		
		case "HollQuest_Officer_exit":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", -1);
			pchar.questTemp.HWIC.Holl = "MerdokStart";
			AddQuestRecord("Holl_Gambit", "1-36");
		break;
		
//---------------------------------------------против всех----------------------------------------------
		//убрать испанского идальго
		case "Fernando":
			dialog.text = "나에게서 뭘 원하는 거지?";
			link.l1 = "네 놈의 머리다!";
			link.l1.go = "Fernando_fight";
			link.l2 = "아니야, 신경 쓰지 마.";
			link.l2.go = "exit";	
			NextDiag.TempNode = "Fernando_repeat";
		break;
		
		case "Fernando_repeat":
			dialog.text = "또 너냐? 나한테 뭘 원하는 거야?! 설명해 봐!";
			link.l1 = "네 놈의 머리다!";
			link.l1.go = "Fernando_fight";
			link.l2 = "아니오, 아무것도 아닙니다.";
			link.l2.go = "exit";	
			NextDiag.TempNode = "Fernando_repeat";		
		break;
		
		case "Fernando_fight":
			chrDisableReloadToLocation = true;//выходы закроем
			LAi_SetWarriorType(npchar);
            LAi_group_MoveCharacter(npchar, "SPAIN_CITIZENS");
			LAi_group_Attack(NPChar, Pchar);
			SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");	
			pchar.quest.HWIC_Fernando.win_condition.l1 = "NPC_Death";
			pchar.quest.HWIC_Fernando.win_condition.l1.character = "HWICFernando";
			pchar.quest.HWIC_Fernando.function = "Fernando_died";
		break;
		
		//в доме Флитвуда
		case "Fleetwood_soldier"://для любителей сунуть нос куда не надо
			if (CheckAttribute(npchar, "quest.talked"))
			{
			dialog.text = "또 너냐? 여기서 왜 기웃거리고 있는 거지? 영 마음에 안 들어. 좋아, 널 체포해서 사령관실로 끌고 가 심문하겠다. 얘들아, 이 자를 잡아라!";
			link.l1 = "하지만 난 그냥...";
			link.l1.go = "Fleetwood_soldier_4";	
			}
			else
			{
			dialog.text = "너는 누구고, 뭘 원하는 거냐? 당장 설명해!";
			link.l1 = "죄송합니다, 나리, 제가 집을 잘못 찾아온 것 같습니다. 용서해 주십시오.";
			link.l1.go = "Fleetwood_soldier_1";	
			link.l2 = "리처드 플리트우드를 만나고 싶소.";
			link.l2.go = "Fleetwood_soldier_2";		
			}
		break;
		
		case "Fleetwood_soldier_1":
			dialog.text = "맞소. 당신은 잘못된 사람에게 말하고 있소. 어서 나가 주시오!";
			link.l1 = "그래. 물론이지.";
			link.l1.go = "Fleetwood_soldier_3";			
		break;
		
		case "Fleetwood_soldier_2":
			dialog.text = "정말인가? 누가 그가 여기 산다고 말했지? 수상한데... 좋아, 널 체포해서 사령관실로 데려가 심문하겠다. 얘들아, 이 자를 잡아라!";
			link.l1 = "하지만 난 그냥 리처드를 보고 싶었을 뿐인데...";
			link.l1.go = "Fleetwood_soldier_4";	
		break;
		
		case "Fleetwood_soldier_3":
			DialogExit();
			npchar.quest.talked = "true";
			DoQuestReloadToLocation("SentJons_town", "reload", "houseSP3", "");
			pchar.quest.Fleetwood_Soldier.win_condition.l1 = "location";
			pchar.quest.Fleetwood_Soldier.win_condition.l1.location = "SentJons_houseSP3";
			pchar.quest.Fleetwood_Soldier.function = "Fleetwood_Soldier";//для настырных
		break;
		
		case "Fleetwood_soldier_4":
			DialogExit();
			GoToPrison("SentJons", 1000, 10);			
		break;
		
		case "Theft_soldier":
			dialog.text = "아! 도둑이냐? 첩자냐? 이제 모자나 꽉 잡아라!";
			link.l1 = "얍!";
			link.l1.go = "Attack_Theft_soldier";			
		break;
		
		case "Attack_Theft_soldier":
			LAi_group_Delete("EnemyFight");
			LAi_SetHP(npchar, 500, 500);
			LAi_SetWarriorType(npchar);
            LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "Attack_soldier":
			dialog.text = "아! 이 녀석이 여기서 뭐 하는 거야? 얘들아, 여기 첩자가 있잖아! 무장해!";
			link.l1 = "얍!";
			link.l1.go = "Attack_soldier_fight";			
		break;
		
		case "Attack_soldier_fight":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//снять запрет драки
			LAi_group_Delete("EnemyFight");
			for (i=1; i<=4; i++)
			{
			sld = characterFromId("Attack_sold_"+i);	
			LAi_SetWarriorType(sld);
            LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "PrepareToStreetFight");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		//Книппель-пленник в трюме
		case "Sailor_deck":
			chrDisableReloadToLocation = true;
			dialog.text = "선장님, 지시하신 대로 이 악당을 심문했습니다. 좀 지져야 했습니다... 이 편지를 가지고 있더군요. 먹으려고 했지만 우리가 막았습니다. 예상대로, 이 자는 빌렘스타드에서 어떤 여자를 데려다가 자기 상사에게 넘기려 했습니다.";
			link.l1 = "편지라고? 어디 한 번 보자. 그 다음 내가 직접 그에게 말하겠다.";
			link.l1.go = "Sailor_deck_1";			
		break;
		
		case "Sailor_deck_1":
			DialogExit();
			AddLandQuestMark(characterFromId("KnippelClone"), "questmarkmain");
			GiveItem2Character(pchar, "NPC_Letter");
			AddQuestRecordInfo("LetterToAbi", "1");
		break;
		
		case "Sailor_deck_2":
			dialog.text = "명령이 무엇입니까, 선장님?";
			link.l1 = "시체를 바다에 던져라. 그리고 상륙할 준비를 해!";
			link.l1.go = "Sailor_deck_3";			
			// belamour legendary edition -->
			link.l2 = "그를 군사 예우를 갖추어 바다에 묻으시오.\n저 노인은 마지막 순간까지 용감하게 싸웠소.\n포가 포차에서 떨어진 뒤에도 직접 장전하고 조준까지 했지.\n참으로 안타깝군.\n다른 세상에서라면 우리도 동지가 되었을 텐데...";
			link.l2.go = "Sailor_deck_3a";
		break;
		
		case "Sailor_deck_3a":
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			AddCharacterExpToSkill(pchar, "Leadership", 120);
			dialog.text = "예, 선장님!";
			link.l1 = "...";
			link.l1.go = "Sailor_deck_4";			
		break;
		
		case "Sailor_deck_3":
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			AddCharacterExpToSkill(pchar, "Sneak", 120);
			AddCharacterExpToSkill(pchar, "FencingL", 30);
			AddCharacterExpToSkill(pchar, "FencingS", 30);
			AddCharacterExpToSkill(pchar, "FencingH", 30);
			AddCharacterExpToSkill(pchar, "Pistol", 30);
			// <-- legendary edition
			dialog.text = "알겠소, 선장님!";
			link.l1 = "...";
			link.l1.go = "Sailor_deck_4";			
		break;
		
		case "Sailor_deck_4":
			DialogExit();
			chrDisableReloadToLocation = false;
			AddQuestRecord("Holl_Gambit", "3-21");
			LAi_SetActorType(pchar);
			sld = characterFromId("KnippelClone");
			ChangeCharacterAddressGroup(sld, "none", "", "");
			sld.lifeday = 0;
			for (i=1; i<=3; i++)
			{
				sld = characterFromId("Sailor_"+i);
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "ReturnMCPlayer", 3);
			}
			pchar.questTemp.HWIC.Self = "toVillemstad";
			sld = characterFromId("Solomon");
			sld.greeting = "solomon_2";
			AddLandQuestMark(sld, "questmarkmain");
			AddMapQuestMarkCity("Villemstad", false);
			LocatorReloadEnterDisable("Villemstad_town", "houseSP2", false);//откроем дом Аби
			LocatorReloadEnterDisable("Villemstad_houseSP2", "reload2", true);//закроем комнату Аби
		break;
		
		//Лонгвэй-пленник в трюме
		case "Sailor_deck_5":
			chrDisableReloadToLocation = true;
			dialog.text = "명령하신 대로 중국인을 심문할 준비를 마쳤습니다, 선장님. 그 자에겐 아무것도 없었고, 서류도 없었습니다. 화로를 준비해두었고, 수갑과 집게를 벌겋게 달궈지고 있습니다.";
			link.l1 = "수고했네, 알론소. 하지만 시작하기 전에 내가 먼저 그와 이성적으로 대화해 보고 싶군. 어쩌면 자발적으로 협조할지도 모르지?";
			link.l1.go = "Sailor_deck_6";			
		break;
		
		case "Sailor_deck_6":
			dialog.text = "말씀대로 하겠습니다, 선장님.";
			link.l1 = "...";
			link.l1.go = "exit";	
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
		break;
		
		case "Sailor_deck_7":
			dialog.text = "예, 선장님?";
			link.l1 = "저 자를 족쇄에 채우고 과달루프에 도착할 때까지 한시도 눈을 떼지 마라.\n너희 셋은 항상 여기 있어야 한다.\n저 자에게 무슨 일이라도 생기면 목숨으로 책임질 줄 알아라.";
			link.l1.go = "Sailor_deck_8";			
		break;
		
		case "Sailor_deck_8":
			dialog.text = "알겠소, 선장님!";
			link.l1 = "";
			link.l1.go = "Sailor_deck_9";			
		break;
		
		case "Sailor_deck_9":
			chrDisableReloadToLocation = false;
			AddQuestRecord("Holl_Gambit", "3-48");
			sld = characterFromId("LongwayClone");
			LAi_SetActorType(sld);
			LAi_SetGroundSitType(sld);
			DialogExit();
			pchar.quest.Longway_Shore.win_condition.l1 = "location";
			pchar.quest.Longway_Shore.win_condition.l1.location = "Shore31";
			pchar.quest.Longway_Shore.function = "LongwayInShore";
			AddMapQuestMarkShore("Shore31", true);
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
		break;
		
		//пьяница - передача письма Флитвуду
		case "Drunkard":
			DelLandQuestMark(npchar);
			dialog.text = "힉! 좋은 저녁입니다, 나리! 무엇을 드시겠습니까? 혹시 이 늙은 주정뱅이에게 한 잔 사주실 수 있겠습니까? 그리고 저는...";
			link.l1 = "이봐, 늙은 주정뱅이... 너 잭 해리슨 맞지?";
			link.l1.go = "Drunkard_1";			
		break;
		
		case "Drunkard_1":
			dialog.text = "오! 그래, 나야. 또 누가 있겠어? 왜? 우-리-는 취-한 선-원-을 어-쩌-면 좋-을-까...";
			link.l1 = "오, 주여, 인내심을 주소서! 무슨 선원? 네 얼굴에 땅개라고 다 써 있구만... 돈 좀 벌고 싶나?";
			link.l1.go = "Drunkard_2";			
		break;
		
		case "Drunkard_2":
			dialog.text = "나는 항상 돈을 벌고 싶어. 어떻게 해야 하지? 하지만 누구도 죽이지 않을 거야. 훔치지도 않을 거고. 그리고 넌 내 타입이 아니야.";
			link.l1 = "아무도 죽일 필요 없어, 그리고 네가 그럴 수 있을 거라고도 생각 안 해. 넌 너무 서툴러. 자, 여기 편지다. 이걸 받아서 총독 관저 왼쪽에 있는 집에 전해 줘. 리처드 플리트우드에게 가는 거다.";
			link.l1.go = "Drunkard_3";			
		break;
		
		case "Drunkard_3":
			dialog.text = "리처드 플리트우드 때문에? 아니... 나 보자마자 체포당할 거야.";
			link.l1 = "닥치고 들어. 아무도 너를 체포하지 않을 거야. 너는 애비게일 일로 찰리 크니펠에게서 왔다고 말해. 그러면 들여보내 줄 거다. 내가 한 말을 반복해.";
			link.l1.go = "Drunkard_4";			
		break;
		
		case "Drunkard_4":
			dialog.text = "아비게일이 누구지? 나는 크니펠은 아는데...";
			link.l1 = "알 바 아니야. 덜 알수록 오래 살지. 자, 기다리고 있다. 다시 말해.";
			link.l1.go = "Drunkard_5";			
		break;
		
		case "Drunkard_5":
			dialog.text = "나는 찰리 크니펠에게서 왔소, 당신의... 아비게일 말이오. 그래, 그거요. ";
			link.l1 = "잘했소. 이 일에 대해 5,000페소를 받게 될 것이오.";
			link.l1.go = "Drunkard_6";			
		break;
		
		case "Drunkard_6":
			if (makeint(Pchar.money) >= 5000)
			{
				dialog.text = "5000페소? 오... 편지 한 통 전달하는 것뿐인데?";
				link.l1 = "아니. 다른 편지를 줄 거다. 그걸 선술집에 가져와서 여기 앉아 있어. 내가 받아가겠다. 멍청한 짓 하지 말고, 겁낼 필요도 없어 – 내가 널 지켜보고 곁에 있을 테니. 이 돈은 선불이니, 마음 편히 가지도록 해.";
				link.l1.go = "Drunkard_7";	
			}
			else
			{
				dialog.text = "오천? 그 정도 돈이나 있기는 해?";
				link.l1 = "하! 당연히 있지. 지금 가져올게.";
				link.l1.go = "Drunkard_no_money";	
				NextDiag.CurrentNode = "Drunkard_no_money";
			}
		break;
		
		case "Drunkard_no_money":
			dialog.text = "오천 가져왔나?";
			if (makeint(Pchar.money) >= 5000)
			{
				link.l1 = "그래. 여기 있다. 걱정하지 마라.";
				link.l1.go = "Drunkard_7";
			}
			else
			{
				link.l1 = "아니. 잠깐만. 곧 돌아오겠소.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Drunkard_no_money";
			}
		break;
		
		case "Drunkard_7":
			AddMoneyToCharacter(pchar, -5000);
			RemoveItems(PChar, "MC_Letter", 1);
			dialog.text = "흠... 이제 가야 할까요, 나리?";
			link.l1 = "아니, 목요일 아침에... 당연히 지금이지, 이 멍청아! 이제 럼주나 다 마시고 꺼져!";
			link.l1.go = "Drunkard_8";			
		break;
		
		case "Drunkard_8":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "3-26");
			LAi_SetStayType(npchar);
			LAi_RemoveLoginTime(npchar);//удалить время загрузки
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(npchar, "sentjons_tavern", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "sentjons_town", "reload", "reload4_back", "DrunkardGoTown", -1);
			chrDisableReloadToLocation = true;//закрыть локацию
			LocatorReloadEnterDisable("SentJons_town", "reload1_back", true);
			LocatorReloadEnterDisable("SentJons_town", "reload2_back", true);
			LocatorReloadEnterDisable("SentJons_town", "gate_back", true);//чтобы не сбежал
		break;
		
		case "Drunkard_9":
			DelLandQuestMark(npchar);
			dialog.text = "아, 여기 계셨군요, 나리... 이 일을 하지 말았어야 했습니다. 리처드가 다 읽고 나서 분노했어요. 저를 죽일 것 같았거든요.";
			link.l1 = "하지만 여기 있군! 걱정 마라 - 그가 감히 그럴 리 없지 - 그 순간 너는 그에게 너무나 소중했으니까, 하하! 네가 상상도 못할 만큼이나...";
			link.l1.go = "Drunkard_10";			
		break;
		
		case "Drunkard_10":
			dialog.text = "술이 필요하군... 자, 이게 그가 당신에게 보낸 답장이오.";
			link.l1 = "내놔! 그리고 입 다물고 있어!";
			link.l1.go = "Drunkard_11";			
		break;
		
		case "Drunkard_11":
			GiveItem2Character(pchar, "MC_Letter");
			ChangeItemDescribe("MC_Letter", "itmdescr_MC_Letter1");
			AddQuestRecordInfo("FleetwoodAnswer", "1");
			dialog.text = "며칠 동안은 말을 하기 힘들겠군... 잘 가시오... 다시는 당신을 보지 않기를 바라오.";
			link.l1 = "진정해, 이 늙은 주정뱅이야, 하하하! 취~한 선~원을 어~찌~할~까~나~... 마시고 쉬어, 이제 다 끝났으니!";
			link.l1.go = "Drunkard_12";			
		break;
		
		case "Drunkard_12":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			AddQuestRecord("Holl_Gambit", "3-27");
			pchar.questTemp.HWIC.Self = "FleetwoodAgree";
			AddCharacterExpToSkill(pchar, "Sneak", 300);//скрытность
			AddLandQuestMark(characterFromId("Merdok"), "questmarkmain");
		break;
		
		//кэп курьерского судна
		case "Cureer_abordage":
			dialog.text = "대체 왜 내 배를 공격한 거야? 내게는 귀중품도 돈도 없어—그저 서류뿐인데, 너희한테 아무 쓸모도 없잖아!";
			link.l1 = "닥쳐라. 이제 네가 졌으니 내 말이나 들어라. 나는 네 배도, 서류도 필요 없다. 네 놈은 네 상사, 그 더러운 쥐새끼 루카스 로덴부르크에게 이 전갈을 전해라. 플리트우드 선장이 안부를 전한다고 말해.";
			link.l1.go = "Cureer_abordage_1";			
		break;
		
		case "Cureer_abordage_1":
			dialog.text = "플리트우드 선장? 하지만...";
			link.l1 = "이 편지를 네 상사에게 전할 거냐, 아니면 내가 널 찔러야 하겠냐? 전달할 다른 놈을 찾아도 상관없다. 참고로, 난 심심해서 네 더러운 회사 배를 매주 털고 다닌다, 알아둬라.";
			link.l1.go = "Cureer_abordage_2";			
		break;
		
		case "Cureer_abordage_2":
			dialog.text = "알겠습니다, 플리트우드 나리. 제가 전달하겠습니다.";
			link.l1 = "좋군. 이제 서로 작별할 수 있겠군, 마인헤르. 오늘은 운이 아주 좋았다고 생각하게. 그리고 도착하면 교회에 꼭 들르도록 하게!";
			link.l1.go = "Cureer_abordage_3";			
		break;
		
		case "Cureer_abordage_3":
			DialogExit();
			sld = &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)];
			Lai_SetPlayerType(pchar);
			LAi_RemoveCheckMinHP(sld);
			LAi_SetImmortal(sld, true);
			sld.ShipEnemyDisable  = true;
			pchar.quest.HWICCureer_AfterBattle.over = "yes";
			pchar.quest.HWICCureerOnMapOver.over = "yes";
			AddQuestRecord("Holl_Gambit", "3-39");
			Log_TestInfo("THE LETTER HAS BEEN DELIVERED!");
			RemoveItems(PChar, "MC_Letter", 1);
			pchar.questTemp.HWIC.Self = "LetterToLucasSent";
			pchar.quest.Curacao_exploring.win_condition.l1 = "location";
			pchar.quest.Curacao_exploring.win_condition.l1.location = "Curacao";
			pchar.quest.Curacao_exploring.function = "CuracaoExploring";
			DoQuestCheckDelay("LAi_ReloadBoarding", 1.0);
			AddComplexSeaExpToScill(50, 50, 50, 100, 50, 50, 0);
			AddComplexSelfExpToScill(30, 30, 30, 30);
			AddMapQuestMarkIsland("Curacao", true);
		break;
		
		//Матиас Бек в тюрьме
		case "MatiasBek"://на случай если геймер захочет пообщаться
			dialog.text = "나는 불법적으로 체포당했소! 나는 영국 놈들과 아무런 관련도 없소! 이 모든 건 다 로덴부르크의 음모요. 신경 쓰지 마시오. 곧 피터 스타이베산트가 도착할 것이니, 그가 모든 걸 해결할 것이오!\n";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "MatiasBek";
		break;
		
		//стражник у входа в резиденцию
		case "QuestGuard":
			dialog.text = "루카스 로덴부르흐 나리께서는 지금 아무도 만나고 싶어하지 않으십니다. 즉시 저택을 떠나 주시기 바랍니다.";
			link.l1 = "흠. 알겠소. 일주일 안에 들르도록 하겠소...";
			link.l1.go = "exit";
			NextDiag.TempNode = "QuestGuard";		
		break;
		
		//Питер Стайвесант
		case "Stivesant":
			dialog.text = "저희는 관저로 갑니다, 선장님. 이미 제 부하들을 요새로 보내 마티아스 벡에 대한 정보를 알아보게 했습니다. 만약 그가 지금 실제로 감옥에 있다면, 이미 풀려나서 마을로 이송됐을 겁니다. 저를 따라오십시오!\n";
			link.l1 = "예, 스타이베산트 나리.";
			link.l1.go = "Stivesant_1";			
		break;
		
		case "Stivesant_1":
			DialogExit();
			AddLandQuestMark(npchar, "questmarkmain");
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "Villemstad_townhall", "goto", "goto2", "OpenVillemstadResidence", -1);
		break;
		
		case "ArestLucas_1":
			dialog.text = "루카스! 여기서 무슨 일이 벌어지고 있나? 마티아스 벡은 어디 있지? 그를 감옥에 보냈다는 게 사실인가?";
			link.l1 = "";
			link.l1.go = "ArestLucas_2";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Lucas"));
		break;
		
		case "ArestLucas_2":
			StartInstantDialog("Lucas", "ArestLucas_3", "Quest\HollandGambit\OtherNPC.c");
		break;
		
		case "ArestLucas_3":
			dialog.text = "안녕하십니까, 스타이베산트 나리. 그가 영국 정보부, 그리고 직접 플리트우드 선장과 연계되어 있다는 증거를 가져왔습니다. 그 자가 저주받은 영국놈에게 우리 회사의 특급 브리건틴을 습격하고 기밀 서신을 빼앗으라고 정보를 흘렸습니다.";
			link.l1 = "";
			link.l1.go = "ArestLucas_4";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Stivesant"));
			LAi_ActorAnimation(npchar, "dialog_stay13", "1", 4.5);
		break;
		
		case "ArestLucas_4":
			StartInstantDialog("Stivesant", "ArestLucas_5", "Quest\HollandGambit\OtherNPC.c");
		break;
		
		case "ArestLucas_5":
			dialog.text = "이 정보를 어디서 얻었소?";
			link.l1 = "";
			link.l1.go = "ArestLucas_6";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Lucas"));
		break;
		
		case "ArestLucas_6":
			StartInstantDialog("Lucas", "ArestLucas_7", "Quest\HollandGambit\OtherNPC.c");
		break;
		
		case "ArestLucas_7":
			dialog.text = "그것은 연락 브리건틴의 선장이 주장했소. 리처드 플리트우드가 그의 배에 올라타 서류를 가져갔고, 그 후 배는 풀려났소. 나와 자네, 그리고 마티아스 벡 외에는 항로나 일정에 대해 아는 사람이 아무도 없었소.";
			link.l1 = "";
			link.l1.go = "ArestLucas_8";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Stivesant"));
		break;
		
		case "ArestLucas_8":
			StartInstantDialog("Stivesant", "ArestLucas_9", "Quest\HollandGambit\OtherNPC.c");
		break;
		
		case "ArestLucas_9":
			dialog.text = "그래서 그대는 베크가 플리트우드에게 브리건틴을 공격하라고 밀고했다고 생각한다는 건가? 말도 안 되는 소리군! 플리트우드는 평범한 해적일 뿐이야. 그는 상선만 노린다네. 그런데 왜 그가 그 서류가 필요하겠나? 게다가 그 서류엔 고작 회계 정보밖에 없었는데?";
			link.l1 = "";
			link.l1.go = "ArestLucas_10";		
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Lucas"));
		break;
		
		case "ArestLucas_10":
			StartInstantDialog("Lucas", "ArestLucas_11", "Quest\HollandGambit\OtherNPC.c");
		break;
		
		case "ArestLucas_11":
			dialog.text = "마인헤르, 사환이 평소의 보고서뿐만 아니라 다른 중요한 회사 문서들도 운반했소. 그런데 지금 그 모든 문서가 영국인들 손에 들어갔지. 그래서 내가 베크를 체포하기로 결정한 것이오.";
			link.l1 = "";
			link.l1.go = "ArestLucas_12";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Stivesant"));			
		break;
		
		case "ArestLucas_12":
			StartInstantDialog("Stivesant", "ArestLucas_13", "Quest\HollandGambit\OtherNPC.c");
		break;
		
		case "ArestLucas_13":
			dialog.text = "젠장! 이건 진짜 권력 찬탈이잖아! 루카스, 네가 지금 무슨 짓을 하고 있는지 정말 알고는 있나? 급행 브리건틴의 선장은 어디 있지?";
			link.l1 = "";
			link.l1.go = "ArestLucas_14";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Lucas"));
			LAi_ActorAnimation(npchar, "dialog_stay13", "1", 4.5);
		break;
		
		case "ArestLucas_14":
			StartInstantDialog("Lucas", "ArestLucas_15", "Quest\HollandGambit\OtherNPC.c");
		break;
		
		case "ArestLucas_15":
			dialog.text = "필립스버그로 갔소, 마인헤르.";
			link.l1 = "";
			link.l1.go = "ArestLucas_16";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Stivesant"));	
		break;
		
		case "ArestLucas_16":
			StartInstantDialog("Stivesant", "ArestLucas_17", "Quest\HollandGambit\OtherNPC.c");
		break;
		
		case "ArestLucas_17":
			dialog.text = "좋소, 그러면. 내가 벡을 석방하라고 명령했네. 곧 이리로 데려올 테니, 우리 셋이서 이야기를 나누지.";
			link.l1 = "";
			link.l1.go = "ArestLucas_18";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Lucas"));
		break;
		
		case "ArestLucas_18":
			StartInstantDialog("Lucas", "ArestLucas_19", "Quest\HollandGambit\OtherNPC.c");
		break;
		
		case "ArestLucas_19":
			dialog.text = "좋아, 상관없어. 우리 셋이라도 괜찮아. 얘기하자.";
			link.l1 = "";
			link.l1.go = "ArestLucas_20";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Stivesant"));	
		break;
		
		case "ArestLucas_20":
			DialogExit();
			sld = characterFromId("Villemstad_Mayor"); // belamour legendary edition
			ChangeCharacterAddressGroup(sld, "Villemstad_townhall", "reload", "reload1");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "goto", "governor1", "DoubleTalkWithLucas", -1.0);
			locCameraFromToPos(4.70, 2.92, -4.19, false, 3.60, -0.70, 5.00);
			DoQuestCheckDelay("PiterTalkWithLucas_2", 4.5);
		break;
		
		case "ArestLucas_40":
			dialog.text = "네 무법 행위에 대한 대가를 치르게 될 것이다, 로덴부르크! 네 비난은 터무니없다. 너는 나에게 브리건틴 선장조차 만나게 하지 않았잖아! 아무런 증거도 제시하지 않았고, 모든 비난은 전부 네 개인적인 주장일 뿐이다.\n맹세코, 나는 결백하다! 영국놈들과는 지금도, 예전에도 아무런 접촉이 없었다!";
			link.l1 = "";
			link.l1.go = "ArestLucas_41";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Lucas"));
		break;
		
		case "ArestLucas_41":
			StartInstantDialog("Lucas", "ArestLucas_42", "Quest\HollandGambit\OtherNPC.c");
		break;
		
		case "ArestLucas_42":
			dialog.text = "오, 정말인가? 그렇다면 플리트우드가 어떻게 우리 브리건틴과, 그 배에 평범한 서류 말고도 다른 것이 있다는 사실을 알게 된 거지?";
			link.l1 = "";
			link.l1.go = "ArestLucas_43";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Villemstad_Mayor"));
		break;
		
		case "ArestLucas_43":
			dialog.text = "...";
			link.l1 = "로덴부르크가 거짓말하고 있어. 리처드 플리트우드는 절대 그 연락 브리건틴을 공격할 수 없었어.";
			link.l1.go = "ArestLucas_44";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, pchar);
			sld = characterFromId("Stivesant");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, pchar);
			sld = characterFromId("Villemstad_Mayor");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, pchar);
		break;
		
		case "ArestLucas_44":
			dialog.text = "그런데 당신은 누구요, 마인헤르? 무슨 근거로 그런 말을 하는 거요?";
			link.l1 = "내 이름은 "+GetFullName(pchar)+". 나는 직접 플리트우드 선장을 함정에 끌어들여 제거했소. 그의 시체는 터크스 해안에서 갈매기 밥이 되고 있지. 관리들은 우리 네덜란드 상인들을 그의 공격으로부터 지켜내지 못했으니, 내가 직접 끝을 내버렸소. 그리고 그 일은 사신 브리건틴이 약탈당하기 전에 벌어진 일이오...";
			link.l1.go = "ArestLucas_46";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, pchar);
		break;
		
		case "ArestLucas_46":
			dialog.text = "";
			link.l1 = "플리트우드는 도저히 그럴 수 없었지, 그는 이미 죽었으니까. 내가 선술집에서 현지인들에게 들은 바로는 마티아스 벡이 체포되었다고 하더군. 그래서 나는 이 문제를 조사해 보기로 했어, 왜냐하면 나는 언제나 벡 나리가 흠 없는 명성을 가진 분이라고 믿어 왔으니까...";
			link.l1.go = "ArestLucas_47";			
		break;
		
		case "ArestLucas_47":
			dialog.text = "";
			link.l1 = "항구 사람들 말로는 자네가 자네의 제벡에 온갖 범죄자와 용병들을 태우고, 회사의 경비병들은 육지에 남겨 두었다더군. 나는 자네 배를 쫓아가서 붙잡았고, 자네가 고용한 악당들을 모조리 죽였다네. 롱웨이 선장을 심문했지; 자유를 대가로 그는 모든 걸 내게 털어놓았네, 로덴부르크 나리...\n";
			link.l1.go = "ArestLucas_48";			
		break;
		
		case "ArestLucas_48":
			dialog.text = "";
			link.l1 = "너는 퀴라소의 권력을 잡으려 했고, 롱웨이에게 스타이베산트 나리의 갤리온을 침몰시키라고 명령했지. 네 수법을 아니까, 브리건틴의 불쌍한 선장은 이미 죽었을 거라 확신한다. 전례를 만들려고 통신선 공격도 네가 꾸몄겠지, 맞나? 그리고 그 짓은 네 암살자 야콥 판 베르흐가 했지? 롱웨이가 그 자에 대해 많은 이야기를 해줬다네.";
			link.l1.go = "ArestLucas_49";			
		break;
		
		case "ArestLucas_49":
			dialog.text = "이... 이건 명백한 거짓말이오! 무슨 소리를 하는 거요, 마인헤르? 대체 자네는 누구지?";
			link.l1 = "나는 그 악당 플리트우드를 바다와 육지에서 몰아내고 싶었던 독립 선장이오. 그런데 당신네 정치적 음모에 휘말리고 말았지! 나는 스타이베산트 나리에게 그가 처한 위험을 경고했소. 그리고 나는 지금 큐라소에서 당신의 약탈 행위를 끝장내기 위해, 합법적인 당국과 함께 여기 왔소!";
			link.l1.go = "ArestLucas_50";			
		break;
		
		case "ArestLucas_50":
			dialog.text = "이런 무례가 있나! 네 말에 반드시 책임을 지게 될 것이오, '독립 선장' 나리! 너는...\n";
			link.l1 = "";
			link.l1.go = "ArestLucas_51";
		break;
		
		case "ArestLucas_51":
			StartInstantDialog("Stivesant", "ArestLucas_52", "Quest\HollandGambit\OtherNPC.c");
		break;
		
		case "ArestLucas_52":
			dialog.text = "그만하시오, 루카스. 네 죄값을 치르게 될 것이다! 나는 이미 충분히 듣고, 충분히 보았소. 루카스 로덴부르크, 자네를 회사 이사장의 생명을 노린 혐의, 무력으로 권력을 장악하려 한 혐의, 그리고 특송선 선장을 살해한 혐의로 체포하겠소.\n게다가 공식 조사 과정에서 자네의 흥미로운 이력에 대해 더 많은 것을 알게 되리라 확신하오. 자네는 구금되어 암스테르담으로 이송될 것이며, 그곳에서 재판을 받게 될 것이오. 끌고 가라!";
			link.l1 = "";
			link.l1.go = "ArestLucas_53";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Lucas"));
			sld = characterFromId("Lucas");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, characterFromID("Stivesant"));					
		break;
		
		case "ArestLucas_53":
			StartInstantDialog("Lucas", "ArestLucas_54", "Quest\HollandGambit\OtherNPC.c");
		break;
		
		case "ArestLucas_54":
			dialog.text = "하지만...";
			link.l1 = "";
			link.l1.go = "ArestLucas_55";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Stivesant"));			
		break;
		
		case "ArestLucas_55":
			DialogExit();
			LAi_ActorTurnToCharacter(pchar, characterFromID("Lucas"));
			sld = characterFromId("Lucas");
			LAi_SetImmortal(sld, true);//защита от хитреца
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Villemstad_townhall", "goto", "goto6");
			LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "LucasGoToPrison", -1);
			for (i=3; i<=5; i++)
			{
			sld = characterFromId("StivesantGuard_"+i);
			LAi_ActorFollow(sld, characterFromID("Lucas"), "", -1);
			}
			LAi_SetActorType(PChar);
			locCameraFromToPos(4.70, 2.92, -4.19, false, -4.60, -1.70, 5.50);
			DoQuestFunctionDelay("SecondDayInVillemstad", 6.0);
		break;
		
		case "Stivesant_10":
			dialog.text = "Captain "+GetFullName(pchar)+"! 윌렘스타트 식민지 행정 당국을 대표하여, 그 위험한 범죄자를 체포하는 데 도움을 준 당신의 행동에 진심으로 감사의 뜻을 전합니다. 또한, 제 개인적으로도 감사 인사를 드리고 싶습니다. 어쩌면 제 목숨을 당신에게 빚진 셈이니까요.";
			link.l1 = "나는 모든 네덜란드 식민지의 이익을 위해 행동했소, 미인헤르.";
			link.l1.go = "Stivesant_11";			
		break;
		
		case "Stivesant_11":
			dialog.text = "그대의 겸손함은 존경을 자아내는군, 친구여. 이제 몇 가지 형식적인 절차를 마무리하고 싶소:\n그대가 메이펑을 점령한 것은 오직 선한 목적과 절박한 상황 때문이었으니, 이 일에 대해 문제 삼을 이유는 없소. 하지만 이 배는 회사 소유이니, 부디 돌려주길 바라오.";
			link.l1 = "물론이오, 나리.";
			link.l1.go = "Stivesant_12";			
		break;
		
		case "Stivesant_12":
		//удаляем Мейфенг
		DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");//удаляем атрибут квестового корабля
		if(sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_MAYFANG)
		{
			pchar.Ship.Type = GenerateShipExt(SHIP_TARTANE, true, pchar);
			pchar.Ship.name = "A boat";
			SetBaseShipData(pchar);
			SetCrewQuantityOverMax(PChar, 0);//сажаем на тартану
		}
		else
		{
			for(i = 1; i < COMPANION_MAX; i++)
			{
			int iTemp = GetCompanionIndex(PChar, i);
			if(iTemp > 0)
				{
				sld = GetCharacter(iTemp);
				if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_MAYFANG)
					{
						pchar.questTemp.HWIC.Self.CompanionIndex = sld.Index;
						sld = GetCharacter(sti(pchar.questTemp.HWIC.Self.CompanionIndex));
						RemoveCharacterCompanion(PChar, sld);
						AddPassenger(PChar, sld, false);
					}
				}
			}
		}
			dialog.text = "내일 저의 저택으로 와주십시오 – 공화국 자유주를 위해 큰 공을 세우셨으니, 그에 대한 예우를 받게 될 것입니다. 부디 이 도시에 머물러 주시길 정중히 부탁드립니다.";
			link.l1 = "알겠소, 나리. 내일 들르겠소.";
			link.l1.go = "Stivesant_13";			
		break;
		
		case "Stivesant_13":
			DialogExit();
			sld = characterFromId("Villemstad_Mayor"); // belamour legendary edition
			sld.dialog.currentnode = "Bek_2";
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "Bek_2":
			dialog.text = "개인적으로도 감사드리고 싶습니다, 선장님. 당신의 진취적인 정신과 시기적절한 도움에 말이지요. 내일 꼭 이곳에 들르십시오, 귀중한 선물을 준비해 두겠습니다.";
			link.l1 = "감사합니다, 벡 나리. 곧 가겠습니다!";
			link.l1.go = "Bek_3";			
		break;
		
		case "Bek_3":
			DialogExit();
			pchar.quest.Award_FromPiter.win_condition.l1 = "Timer";
			pchar.quest.Award_FromPiter.win_condition.l1.date.hour  = 9.0;
			pchar.quest.Award_FromPiter.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Award_FromPiter.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Award_FromPiter.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Award_FromPiter.function = "OpenResidenceDoor";
			bDisableFastReload = false;
			LocatorReloadEnterDisable("Villemstad_town", "reload5_back", false);
			LocatorReloadEnterDisable("Villemstad_town", "reload10_back", false);
			LocatorReloadEnterDisable("Villemstad_town", "reload3_back", true);//закрыть вход в резиденцию
			LocatorReloadEnterDisable("Villemstad_town", "reloadR2", true);//закрыть боковой вход в резиденцию
			AddQuestRecord("Holl_Gambit", "3-53");
			DoQuestReloadToLocation("Villemstad_prison", "goto", "goto23", "TalkWithLucasPrisoner");
			for (i=4; i<=5; i++)
			{
				sld = characterFromId("StivesantGuard_"+i);
				sld.lifeday = 0;//подчистим солдат
			}
		break;
		
		case "Stivesant_14":
			dialog.text = ""+GetFullName(pchar)+", 자유주 공화국을 대표하여, 모든 네덜란드인의 적이자 국가 범죄자인 리처드 플리트우드를 처단하는 데 기여한 공로로 당신에게 개인 무기와 10만 페소를 수여합니다. 축하합니다!";
			link.l1 = "감사합니다, 스타이베산트 나리!";
			link.l1.go = "Stivesant_15";			
		break;
		
		case "Stivesant_15":
			dialog.text = "또한, 전례 없는 용기와 회사 내의 반역 음모를 밝혀낸 공로, 그리고 전 부사장을 대담하게 생포한 업적을 인정하여 15만 페소를 수여하오. 네덜란드 서인도 회사와의 계약 체결도 허락하겠소\n우리의 새로운 부국장이 그대처럼 용감한 선장에게는 분명히 보수가 좋은 자리를 마련해 줄 것이라 확신하오.";
			link.l1 = "감사합니다! 명심하겠습니다.";
			link.l1.go = "Stivesant_16";			
		break;
		
		case "Stivesant_16":
			AddMoneyToCharacter(pchar, 250000);
			GiveItem2Character(pchar, GetGeneratedItem("blade_16")); // belamour legendary edition используем GetGeneratedItem иначе пачка одинаковых клинков из первой части массива
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			dialog.text = "네가 항상 네 행동이 네덜란드의 편에 있고, 네덜란드의 이익을 위해서라면 언제든 내 도움을 받을 수 있다는 점을 명심하게. 이제 빌렘스타트의 총독 마티아스 벡이 무슨 말을 하는지 들어보세.";
			link.l1 = "";
			link.l1.go = "Stivesant_17";			
		break;
		
		case "Stivesant_17":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Villemstad_Mayor"); // belamour legendary edition
			LAi_SetActorType(sld);
			sld.dialog.currentnode = "Bek_4";
			LAi_ActorDialog(sld, pchar, "", -1, 0);		
		break;
		
		case "Bek_4":
			dialog.text = "진심으로 감사의 뜻을 표합니다, 선장님. 국가를 해치는 음모를 밝혀내신 용기와 통찰에 경의를 표합니다. 전함의 선원이라면 누구에게나 꼭 필요한 이 귀중한 항해 도구를 드리고 싶습니다.";
			link.l1 = "감사합니다, 벡 나리";
			link.l1.go = "Bek_5";			
		break;
		
		case "Bek_5":
			GiveItem2Character(pchar, "bussol");
			dialog.text = "알아두었으면 하오: 이제 그대는 내 친구요, 이는 내게 큰 의미가 있소. 내 저택에는 언제나 환영받는 손님이 될 것이니, 언제든 어떤 이유로든 찾아오시오. 그대가 필요로 하는 어떤 도움이라도 기꺼이 베풀겠소.";
			link.l1 = "그 말을 들으니 기쁘군, 나리!";
			link.l1.go = "Bek_6";			
		break;
		
		case "Bek_6"://наведем порядок в городе
			DialogExit();
			AddQuestRecord("Holl_Gambit", "3-54");
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Villemstad_Mayor"); // belamour legendary edition
			LAi_SetHuberStayType(sld);
			sld.Dialog.Filename = "Common_Mayor.c";//patch-8
			sld.dialog.currentnode = "First time";
			sld.quest.meeting = "1";
			for (i=1; i<=3; i++)
			{
				sld = characterFromId("StivesantGuard_"+i);
				sld.lifeday = 0;//подчистим солдат
			}
			sld = characterFromId("Stivesant");
			LAi_ActorGoToLocator(sld, "goto", "goto6", "StivesantSitDown", -1);
			bDisableFastReload = false;
			LocatorReloadEnterDisable("Villemstad_town", "reload1_back", false);
			LocatorReloadEnterDisable("Villemstad_town", "reload2_back", false);
			LocatorReloadEnterDisable("Villemstad_town", "gate_back", false);
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
			DelMapQuestMarkCity("Villemstad");
		break;
		
		case "Bek_7":
			dialog.text = "네 덕분에 네덜란드는 자랑스럽소, 마인헤르. 자네 같은 선장들이야말로 카리브 해 네덜란드 함대의 주춧돌이오. 자, 여기 있소, 보상을 받아주시오.";
			link.l1 = "감사합니다, 나리. 네덜란드를 위해 봉사하게 되어 영광입니다!";
			link.l1.go = "Bek_8";
		break;
		
		case "Bek_8":
			TakeNItems(pchar, "gold_dublon", 1000);
			ChangeCharacterComplexReputation(pchar,"authority", 5);
			ChangeCharacterNationReputation(pchar, HOLLAND, 20);
			DialogExit();
			sld = characterFromId("Lucas");
			LAi_SetActorType(sld);
			sld.dialog.currentnode = "LucasAward_2";
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Stivesant_18":
			dialog.text = "만나서 반갑소. 잘 지내시오?";
			link.l1 = "나는 괜찮아. 그냥 너를 보러 잠깐 들렀어.";
			link.l1.go = "exit";	
			NextDiag.TempNode = "Stivesant_18";
		break;
		
		// Jason НСО
		case "Stivesant_19":
			if (ChangeCharacterHunterScore(pchar, "holhunter", 0) > 10)
			{
				dialog.text = "이게 누구야! 바로 "+GetFullName(pchar)+". 최근에 우리 사냥꾼들을 보내 너를 여기로 데려오게 했지. 그리고 그 일에 꽤 많은 돈이 들었어.";
				link.l1 = "음... 가야겠다...";
				link.l1.go = "arest";
				break;
			}
			// belamour legendary edition фикс проверки мундира с мушкетом
			if (pchar.questTemp.Patria == "epizode_4" && IsUniformEquip())
			{
				dialog.text = "프랑스 해군의 선장이오? 좋아, 시간이 부족하니 짧게 듣겠소. 무슨 일로 여기 온 것이오?";
				link.l1 = "스타이베산트 나리, 저는 생크리스토퍼에서 프랑스 식민지 총독 포앵시 기사 나리의 전갈을 가지고 왔습니다.";
				link.l1.go = "Stivesant_20";
			}
			else
			{
				dialog.text = "실례합니다, 선장님. 지금은 너무 바빠서 시간을 내드릴 수 없습니다. 마티아스 벡 나리에게 말씀해 보십시오. 그분께서 당신의 이야기를 들어주실 겁니다.";
				link.l1 = "흠...";
				link.l1.go = "Stivesant_19_1";
			}
		break;
		
		case "Stivesant_19_1":
			DialogExit();
			npchar.dialog.currentnode = "Stivesant_19";
		break;
		
		case "Stivesant_20":
			sld = characterFromId("Patria_FlautCap");
			dialog.text = "드 푸앵시 기사님이 보낸 건가? 이렇게 쉽게 될 줄은 정말 몰랐네... 크흠... 기사님은 요즘 어떠신가?";
			link.l1 = "모든 것이 괜찮습니다, 마인헤르. 드 푸앵시 나리께서 이 편지를 당신께 전하라고 명하셨습니다. 또 다른 임무는 호위하는 것이었습니다\n "+sld.ship.name+"' 자네 회사의 화물을 싣고 윌렘스타드 항구에 도착했소. 배는 부두에 정박해 있고 화물도 손상되지 않았소.'";
			link.l1.go = "Stivesant_21";
		break;
		
		case "Stivesant_21":
			dialog.text = "우리 회사로 향하는 화물 함대라니? 흥미롭군... 그리고 편지는, 선장?";
			link.l1 = "여기요. 자, 받아요.";
			link.l1.go = "Stivesant_22";
		break;
		
		case "Stivesant_22":
			RemoveItems(pchar, "Reserve_item_01", 1);
			dialog.text = "흠... (읽는 중). 본국에서 온 시찰이라... 음흠... 흠, 뭐야... 이거 흥미로운데, 흐흐... 그런데, 선장, 프랑스가 카리브 해에서 스페인과 전쟁 중이라는 소문 들었소? 산호세 요새 포위와 약탈, 쿠바 동쪽 해안에서 스페인 전대가 박살났다는 얘기까지...\n";
			link.l1 = "히스파니올라 서쪽 해안, 포르토프랭스 근처입니다, 나리. 그리고 산호세 공성전의 유일한 목적은 스페인인들이 생피에르를 공격한 것에 대한 금전적 보상을 받기 위함이었지요. 우리는 스페인과 꽤 오랫동안 사이가 좋지 않았습니다... 답을 받으러 언제 다시 오면 되겠습니까?\n";
			link.l1.go = "Stivesant_23";
		break;
		
		case "Stivesant_23":
			dialog.text = "붙잡지는 않겠소, 선장. 자네는 군인이라 바쁜 일이 많을 테고, 슈발리에도 자네의 귀환을 손꼽아 기다리고 있을 것이오. 부디 여기 거실에서 두 시간만 기다려 주겠소? 내가 그 편지에 대한 답장을 쓰는 동안 말이오. 앉아서 쉬게, 원한다면 포도주나 럼주를 가져다줄 것이오...\n";
			link.l1 = "감사하오, 마인헤르, 하지만 나는 좋은 와인 한 잔이 더 좋겠소...";
			link.l1.go = "Stivesant_24";
		break;
		
		case "Stivesant_24":
			chrDisableReloadToLocation = true;//закрыть локацию
			pchar.quest.Patria_CureerTimeOver.over = "yes"; //снять таймер
			pchar.quest.Patria_CureerFail.over = "yes"; //снять прерывание
			sld = characterFromId("Patria_FlautCap");
			RemoveCharacterCompanion(pchar, sld);
			sld.lifeday = 0;
			DialogExit();
			npchar.dialog.currentnode = "Stivesant_25";
			LAi_SetActorType(npchar);
			ChangeCharacterAddressGroup(npchar, "Villemstad_townhall", "goto", "goto6");
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "none", "", "", "Patria_StivesantWait", -1);
			pchar.questTemp.Patria = "epizode_4_return";
		break;
		
		case "Stivesant_25":
			GiveItem2Character(pchar, "Reserve_item_01");
			ChangeItemDescribe("Reserve_item_01", "itmdescr_Reserve_item_01_2");
			dialog.text = "드 푸앵시 나리께 드릴 답장이 준비되었습니다. 여기 있습니다, 받아 주십시오... 행운을 빕니다, 선장님.";
			link.l1 = "감사합니다, 나리. 안녕히 가십시오!";
			link.l1.go = "Stivesant_26";
		break;
		
		case "Stivesant_26":
			DialogExit();
			npchar.dialog.currentnode = "Stivesant_19";
			chrDisableReloadToLocation = false;
			AddQuestRecord("Patria", "23");
			SetFunctionTimerCondition("Patria_CureerBackOver", 0, 0, 31, false);
		break;
		
		case "Stivesant_27":
			if (ChangeCharacterHunterScore(pchar, "holhunter", 0) > 10)
			{
				dialog.text = "이게 누구야! 바로 "+GetFullName(pchar)+". 최근에 우리 사냥꾼들을 보내 너를 여기로 데려오게 했지. 그리고 그 일에는 꽤 많은 돈이 들었어.";
				link.l1 = "음... 나 가봐야겠다...";
				link.l1.go = "arest";
				break;
			}
			if (pchar.questTemp.Patria == "epizode_6" && IsUniformEquip())
			{
				dialog.text = "또 총독 필리프 드 푸앵시 나리의 전갈을 가지고 왔군?";
				link.l1 = "예, 스타이베산트 나리. 신트마르턴 해안에서 유감스러운 오해가 있었습니다\n파리에서 온 감찰관 노엘 포르게 남작이 탄 배가 필립스버그 요새에서 포격을 받았고...";
				link.l1.go = "Stivesant_28";
			}
			else
			{
				dialog.text = "실례합니다, 선장님. 지금 너무 바빠서 시간을 낼 수 없습니다. 마티아스 벡 나리에게 말씀해 보십시오. 그분이 당신 얘기를 들어줄 겁니다.";
				link.l1 = "흠...";
				link.l1.go = "Stivesant_27_1";
			}
		break;
		
		case "Stivesant_27_1":
			DialogExit();
			npchar.dialog.currentnode = "Stivesant_27";
		break;
		
		case "Stivesant_28":
			if (pchar.questTemp.HWIC.Detector == "holl_win" || pchar.questTemp.HWIC.Detector == "self_win")
			{
				dialog.text = "그래서 여기 온 거요, 선장. 나는 외교적 논의 따위 할 생각 없소. 기사 나리에게 전하시오, 이제부터 그는 신트마르턴의 책임자가 아니라고. 그만 됐소. 그리고 본국에서 오는 감찰에 대해서는… 알아서 대책을 세우라고 하시오. 드 푸앵시 나리는 언제든 세상을 뒤집는 데 능했으니, 어려울 것도 없을 거요.";
				link.l1 = "정확히 그렇게 전해야 하오?";
				link.l1.go = "Stivesant_29";
			}
			else
			{
				dialog.text = "그래서 여기 온 것이오, 선장. 외교적 논의는 하지 않겠소. 당신의 주군이 최근 신트마르턴에서 지나치게 탐욕을 부렸으니, 이제 그의 끝없는 욕망을 누그러뜨릴 때요. 그리고 그는 그 점을 아주 잘 알고 있을 것이오. 그리고 자네, 샤를 드 모르 선장, 최근 영국 산적 리처드 플리트우드와 관련된 사건에 대해서도 우리가 궁금한 점이 있으니, 당분간 여기 머물러야 하오.\n병장! 선장의 무기를 압수하고 지휘관실로 데려가라!";
				link.l1 = "프랑스 장교의 임무를 지연시키는 것은 용납할 수 없소!";
				link.l1.go = "Stivesant_31";
			}
		break;
		
		case "Stivesant_29":
			dialog.text = "나도 그보다 더 잘 말할 수 없겠소, 선장. 당신의 상관도 모든 걸 이해할 테니 굳이 더 파고들 필요 없소, 어차피 달라질 건 없으니. 행운을 빌겠소. 하사관, 샤를 드 모르 나리를 출구까지 안내하라!\n";
			link.l1 = "...";
			link.l1.go = "Stivesant_30";
		break;
		
		case "Stivesant_30":
			DialogExit();
			DoQuestReloadToLocation("Villemstad_town", "reload", "reload3", "Patria_DiplomatGetOut");
		break;
		
		case "Stivesant_31":
			dialog.text = "유감이지만, 내 생각은 다르다. 하사! 저들이 저항하면, 무력을 사용하라!";
			link.l1 = "너는 아직 네가 누구를 상대하는지 모르는구나, 마인헤르 ...";
			link.l1.go = "Stivesant_32";
		break;
		
		case "Stivesant_32":
			DialogExit();
			Patria_DiplomatFight();
		break;
		
		case "Stivesant_33":
			dialog.text = "이런 역할을 맡은 "+pchar.name+" 드 모르 선장을 보니 좀 이상하군... 협상을 위해 찾아오는 이들에게 면책을 보장할 수 있기를 바라오..";
			link.l1 = "틀림없소, 스타이베산트 나리.";
			link.l1.go = "Stivesant_34";
		break;
		
		case "Stivesant_34":
			dialog.text = "그러면, 준비하신 계약서를 한 번 읽어볼 기회를 주시겠습니까? 제 이해로는, 그 안에 편지의 내용이 포함되어 있지요?";
			link.l1 = "정확히 그렇소, 마인헤르, 다만 공식적인 형태로 말이오. 프랑스 측에서는 관계를 중립으로 복원하고, 생마르탱 섬에 대한 모든 권리를 포기하는 것이오. 영국 측에서는 무역 전쟁의 종결이오. 세부 사항은 모두 여기에 적혀 있소 ... 그리고 물론, 당신들이 시작한 군사 행동으로 우리가 입은 피해에 대한 금전적 보상도 포함되어 있소.";
			link.l1.go = "Stivesant_35";
		break;
		
		case "Stivesant_35":
			dialog.text = "부디 그 문서를 저에게 주시겠습니까?";
			link.l1 = "물론이지.";
			link.l1.go = "Stivesant_36";
		break;
		
		case "Stivesant_36":
			dialog.text = "...(읽는 중)...";
			link.l1 = "...";
			link.l1.go = "Stivesant_37";
		break;
		
		case "Stivesant_37":
			LAi_Fade("", "");
			dialog.text = "선택의 여지가 없으니 이 계약서에 서명하겠소. 하지만 내게 윌렘스타트와 그 주민들의 안전이 최우선임을 명심하시오";
			link.l1 = "그럼 세 부 모두 서명으로 확인하겠습니다. 저는 프랑스 측을 대표하여 필리프 드 푸앵시 총독의 위임을 받아 서명할 권한이 있고, 잉글랜드 측은 도일리 대령이 서명할 것입니다.";
			link.l1.go = "Stivesant_38";
		break;
		
		case "Stivesant_38":
			dialog.text = "...(서명 중)...";
			link.l1 = "완벽하군! 이제 이걸 서명해야겠지...";
			link.l1.go = "Stivesant_39";
		break;
		
		case "Stivesant_39":
			LAi_Fade("", "");
			dialog.text = "이제 포위를 풀 거라 믿어도 되겠소?";
			link.l1 = "의심할 여지 없소. 네덜란드 측에서 합의 조건을 모두 위반 없이 지켜주길 바라오.";
			link.l1.go = "Stivesant_40";
		break;
		
		case "Stivesant_40":
			dialog.text = "영국이나 프랑스가 위반하지 않는다면, 우리는 계약 조건을 지킬 것이니 걱정하지 마시오.";
			link.l1 = "싸우는 것보다 거래하는 게 언제나 더 낫지요, 스타이베산트 나리. 이제 안심하고 빌렘스타트로 돌아가셔도 됩니다. 포위는 곧 풀릴 것이고, 우리 전대도 곧 퀴라소 해역을 떠날 겁니다.";
			link.l1.go = "Stivesant_41";
		break;
		
		case "Stivesant_41":
			DialogExit(); // Стайвесант уходит, подходит д'Ойли
			Patria_CuracaoStivesantGo();
		break;
		
		case "Stivesant_42":
			dialog.text = "그래서, 당신이 노엘 포르게 남작이오? 흠, 그리고 당신이 바로 샤를 드 모르 나리로군! 반갑소, 부제독 나리! 당신이 이 제도에서 가장 교활한 책략가로 불리는 데에는 이유가 있지. 누구 편인지 도무지 알 수가 없으니 말이오...";
			link.l1 = "부제독께서는 국왕 편에 계시고, 지금 이 순간 그의 정당한 대리인으로서 진심으로 당신 편이기도 하오.";
			link.l1.go = "Stivesant_43";
		break;
		
		case "Stivesant_43":
			dialog.text = "여기서 왕도 멀고, 프랑스도 멀지요, 남작 나리. 하지만 생크리스토프와 드 푸앵시 기사님은 가까이 있습니다. 그분이야말로 프랑스 식민지의 진정한 주인이오. 사실상 그렇지요... 그런데, 혹시 재무장관의 눈에 드 푸앵시를 곤란하게 만들만한 무언가를 얻으러 온 것이오?\n";
			link.l1 = "정확합니다, 마인헤르.";
			link.l1.go = "Stivesant_44";
		break;
		
		case "Stivesant_44":
			dialog.text = "내게 그런 문서들이 있소. 이것은 내 계좌와 드 푸앵시의 광산 관련 거래, 그리고 다른 몇몇 일들까지 모두 기록된 장부요. 안에는 이 사업과 관련된 온갖 서류 뭉치가 들어 있는데, 각각에는 필리프 드 푸앵시의 친필 서명이 있소. 장담하건대, 이 서류들의 내용이 관심 있는 자의 손에 들어가면, 슈발리에를 카리브 해 바닥보다 더 깊은 곳으로 끌어내릴 것이오.";
			link.l1 = "이 장부로 무엇을 원하는가?";
			link.l1.go = "Stivesant_45";
		break;
		
		case "Stivesant_45":
			dialog.text = "거저 넘기는 거지. 은화로 겨우 백만 페소일 뿐이야.";
			link.l1 = "백만 페소?!!";
			link.l1.go = "Stivesant_46";
		break;
		
		case "Stivesant_46":
			dialog.text = "맞습니다, 남작 나리. 이 금액이면 최근 전쟁으로 인한 손실을 적어도 일부는 메울 수 있을 것입니다. 한 가지 조언을 드리죠. 샤를 드 모르 나리에게 의지해 보십시오. 드 푸앵시와, 음... 다른 이들을 위해 일하는 동안 아마도 막대한 재산을 모았을 테니, 백만 정도는 그에게 아무 문제도 아닐 겁니다. 거의 확신합니다.\n기한을 드리겠습니다. 한 달입니다. 그 기간 내에 지정한 금액을 가져오지 않으면, 슈발리에에게 편지를 보내 당신이 나를 찾아온 내막을 모두 적어 보낼 것입니다. 그 다음에 무슨 일이 일어날지는 짐작할 수 있겠지요.";
			link.l1 = "나를 협박하는 거요! 내가 식민지에서 백만을 가질 수 없다는 건 이해해야 하오!";
			link.l1.go = "Stivesant_47";
		break;
		
		case "Stivesant_47":
			dialog.text = "물론 이해하오. 그래서 즉시 이 백만을 가진 자를 당신에게 알려준 것이오. 만약 드 모르 나리가 거절한다면, 남작께서는 내가 슈발리에에게 편지를 보내기 전에 유럽으로 떠나는 것이 좋소. 그렇지 않으면 영원히 여기 남게 될 수도 있소. 드 모르 나리라면... 물론 제독의 지위는 잃겠지만, 빠져나올 것이고... 어쩌면 자기 방식대로 드 푸앵시까지 처리할지도 모르지, 나로선 그게 전혀 상관없소.\n자, 신사 여러분, 내 말 들으셨지요. 한 달 뒤 내 저택에서 백만을 가지고 오시기 바라오. 자유롭게 드나들 수 있도록 보장하겠소.";
			link.l1 = "...";
			link.l1.go = "Stivesant_48";
		break;
		
		case "Stivesant_48":
			DialogExit();
			LAi_SetActorType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			locCameraTarget(pchar);
			locCameraFollow();
			EndQuestMovie();
			InterfaceStates.Buttons.Save.enable = true;
			bDisableCharacterMenu = false;
			sld = CharacterFromID("Noel");
			sld.dialog.currentnode = "noel_84";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.5);
			sld = CharacterFromID("Stivesant");
			LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "Patria_CondotierStivesantInHall", 12.0);
			for (i=1; i<=3; i++)
			{
				sld = CharacterFromID("Stivesant_sold_"+i);
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", 10.0);
			}
		break;
		
		case "Stivesant_49":
			if (sti(pchar.money) >= 1000000)
			{
				dialog.text = "나는 한 번도 의심하지 않았소, 샤를 드 모르 부제독 나리, 그대가 이 돈을 가져올 거라는 것을. 어쩌면 내가 그대에게 너무 적게 요구했을지도 모르지, 뭐... 남작은 그대의 다음 게임에서 그냥 졸에 불과하잖소? 지위와 돈만으로는 만족하지 못하고, 이제 드 푸앵시의 자리를 노리는 거요, 맞지? 인정해야 하오, 프랑스 식민지 총독 자리에 비하면 백만은 적은 돈이오! 그대의 강철 같은 통제력을 생각하면, 이 돈은 몇 달 만에 다시 벌 수 있을 테니.";
				link.l1 = "자, 백만 길더 가져가시오, 마인헤르. 약속한 장부를 받고 싶소.";
				link.l1.go = "Stivesant_50";
			}
			else
			{
				dialog.text = "백만을 모으는 데 집중하는 게 좋겠소, 나리. 쓸데없는 방문으로 시간 낭비하지 말고.";
				link.l1 = "...";
				link.l1.go = "Stivesant_49_1";
			}
		break;
		
		case "Stivesant_49_1":
			DialogExit();
			npchar.dialog.currentnode = "Stivesant_49";
		break;
		
		case "Stivesant_50":
			pchar.quest.Patria_CondotierStivesantTimeOver.over = "yes"; // снять таймер
			AddMoneyToCharacter(pchar, -1000000);
			GiveItem2Character(pchar, "Reserve_item_01");
			ref itm = ItemsFromID("Reserve_item_01");
			itm.picIndex = 15;
			itm.picTexture = "ITEMS_26";
			itm.price = 0;
			itm.Weight = 2.0;
			itm.name = "itmname_Reserve_item_01_1";
			ChangeItemDescribe("Reserve_item_01", "itmdescr_Reserve_item_01_4");
			dialog.text = "물론이지요, 부제독 나리. 그리고 찡그리지 마시오. 장차 총독이 되면 알게 될 것이오. 네덜란드 서인도 무역회사가 탐욕스럽고 전쟁광인 영국놈들보다 훨씬 이익이 되는 사업 파트너라는 걸 말이오. 영국놈들한테 손가락 하나 내주면 손 전체를 가져간다는 걸 모르시오? 모른다면, 곧 뼈저리게 배우게 될 것이오. 그러니 아직 작별 인사는 하지 않겠소. 서류는 가지고 계시오. 자네네 남작이 기사님을 이길 만한 실력이 있길 바라오.";
			link.l1 = "감사하오. 안녕히 계시오, 스타이베산트 나리.";
			link.l1.go = "Stivesant_51";
		break;
		
		case "Stivesant_51":
			DialogExit();
			AddQuestRecord("Patria", "84");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "none", "", "", "", -1);
			pchar.quest.Patria_CondotierCabin.win_condition.l1 = "location";
			pchar.quest.Patria_CondotierCabin.win_condition.l1.location = "Curacao";
			pchar.quest.Patria_CondotierCabin.function = "Patria_CondotierCabin";
		break;
		
		case "vanberg_sold":
			dialog.text = "하하하! 저것 좀 봐라! 제이콥 말이 항상 맞았지 - 이 여우가 괜히 섬에 온 게 아니었군. 상자에 금이 잔뜩 들어 있는 모양이야. 혼자 여기 온 건 참 부주의했구나, 이 친구야. 뭐, 덕분에 우리 일은 훨씬 쉬워졌지만!\n";
			link.l1 = "그 쓰레기들이 나를 찾아냈군! 전혀 예상 못 했는데... 하지만 내가 그렇게 만만한 먹잇감일 줄 알지 마라!";
			link.l1.go = "vanberg_sold_1";			
		break;
		
		case "vanberg_sold_1":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			for (i=1; i<=4; i++)
			{
				sld = characterFromId("vanberg_sold_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "PrepareMassakraInShore");
			AddDialogExitQuest("MainHeroFightModeOn");			
		break;
		
		case "Abihouselady":
			dialog.text = "누구 찾고 있나?";
			link.l1 = "그래, 나다. 솔로몬과 아비가일 슈네우르는 어디 있지?";
			link.l1.go = "Abihouselady_1";			
		break;
		
		case "Abihouselady_1":
			dialog.text = "이제 그들은 여기서 살지 않아. 더 이상 이곳을 감당할 수 없었거든. 애비게일은 불쌍하게도 지금 총독의 하녀로 일하고 있어. 자기와 아버지를 부양하려고 매일 열심히 일하지. 솔로몬은 매일 선술집에서 술만 마셔. 그들에게 일어난 일을 견딜 수가 없는 거지. 지금은 바다에서 멀지 않은 작은 오두막에서 살고 있어...\n";
			link.l1 = "오... 알겠소, 정보 고맙소. 이제 가봐야겠군.";
			link.l1.go = "Abihouselady_2";
		break;
		
		case "Abihouselady_2":
			DialogExit();
			NextDiag.CurrentNode = "Abihouselady_3";
		break;
		
		case "Abihouselady_3":
			dialog.text = "또 무엇이 궁금하신가요, 나리?";
			link.l1 = "아니야, 신경 쓰지 마.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Abihouselady_3";
		break;
		
		//удаление Мейфенг при провале квеста
		case "TempOffGuard":
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");//удаляем атрибут квестового корабля
			if(sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_MAYFANG)
			{
				pchar.Ship.Type = GenerateShipExt(SHIP_TARTANE, true, pchar);
				pchar.Ship.name = "A boat";
				SetBaseShipData(pchar);
				SetCrewQuantityOverMax(PChar, 0);//сажаем на тартану
			}
			else
			{
				for(i = 1; i < COMPANION_MAX; i++)
				{
						iTemp = GetCompanionIndex(PChar, i);
					if(iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_MAYFANG)
						{
							pchar.questTemp.HWIC.Self.CompanionIndex = sld.Index;
							sld = GetCharacter(sti(pchar.questTemp.HWIC.Self.CompanionIndex));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
			}
			dialog.text = "선장, 당신은 네덜란드 서인도 회사 소속의 배를 불법으로 점유했소. 나는 이를 압수할 권한이 있으며, 저항할 경우 무력을 사용할 수 있소. 이것은 피터 스토이브산트의 명령이오.";
			link.l1 = "음, 피터 스타이브센트 본인에게서 온 명령이라면... 나는 배 한 척 때문에 네덜란드와 전쟁을 벌일 생각은 없소. 가져가시오.";
			link.l1.go = "TempOffGuard_1";			
		break;
		
		case "TempOffGuard_1":
			dialog.text = "이성적으로 행동해 주어 다행이군.";
			link.l1 = "...";
			link.l1.go = "TempOffGuard_2";
		break;
		
		case "TempOffGuard_2":
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 10.0);
			chrDisableReloadToLocation = false;//открыть локацию
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");
		break;
		
		// Jason НСО
		case "arest":
			dialog.text = "물론 이제 나갈 시간이오, 호위도 붙여주지. 경비병들! 저 자를 잡아라!";
		    link.l1 = "나한테 시켜 봐!";
		    link.l1.go = "fight";
		break;
		
		case "fight":
            Pchar.quest.ArestInResidenceEnd.win_condition.l1          = "ExitFromLocation";
		    Pchar.quest.ArestInResidenceEnd.win_condition.l1.location = Pchar.location;
		    Pchar.quest.ArestInResidenceEnd.win_condition             = "ArestInResidenceEnd";
		    Pchar.quest.ArestInResidenceEnd.ResidenceLocation = Pchar.location;
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_LockFightMode(Pchar, true); // ножками путь убегает
		    LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
		    LAi_group_Attack(NPChar, Pchar); // не работает на бессмертного мера :(
			i = GetCharIDXByParam("CityType", "location", Pchar.location); // фантом солдат
			if (i != -1)
			{
			    LAi_group_Attack(&Characters[i], Pchar);
			}
		break;
		
		//замечание по обнажённому оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar,"이봐, 잘 들어! 이 마을 시민으로서 부탁하는데, 칼집에서 뽑은 칼을 들고 다니지 말아 주시오.","있지, 이 마을 시민으로서 부탁하는데, 칼을 뽑은 채로 돌아다니지 말아 주시오.");
			link.l1 = LinkRandPhrase("좋아.","좋아.","말씀대로...");
			link.l1.go = "exit";
		break;
	}
}
