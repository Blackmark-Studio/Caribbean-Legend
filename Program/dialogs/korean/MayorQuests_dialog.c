void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, Diag;
	int i;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();			
		break;
		//----------------- уничтожение банды ----------------------
		case "DestroyGang_begin":
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false); //боевке можно
			DeleteAttribute(&locations[FindLocation(pchar.GenQuest.DestroyGang.Location)], "DisableEncounters"); //энкаунтеры можно 
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("MayorQuestGang_" + i) == -1) continue;
				sld = CharacterFromID("MayorQuestGang_" + i);
				LAi_type_actor_Reset(sld);
				LAi_RemoveCheckMinHP(sld);
			}
			sTemp = GetFullName(&characters[GetCharacterIndex(pchar.GenQuest.DestroyGang.MayorId)]);
			dialog.text = LinkRandPhrase("통에 현찰로 "+GetSexPhrase("동료","아가씨")+"! 내 이름은 "+GetFullName(npchar)+", 그리고 난 반대에 익숙하지 않지...","이제 네 돈주머니를 보여 줘, "+GetSexPhrase("동료","아가씨")+", 그리고 서둘러라! 내 이름은  "+GetFullName(npchar)+", 그리고 내 소문을 들었길 바라네...","가진 값진 것 전부 내놔, 그리고 네 돈주머니도 내가 가져가겠다. 서둘러라, 난 참을성이 별로 없거든. 피에 대한 갈증은 그렇지 않다는 건 확실히 말할 수 있지!");
			Link.l1 = LinkRandPhrase("헤, 네가 그 유명한 도적이구나 "+GetFullName(npchar)+", 그 지역 총독이 대해 "+sTemp+" 말이 끊이질 않아?","오, 그러니까 네가 이 지역 총독에게 쫓기는 그 산적이로군 "+sTemp+"?!","Glad"+GetSexPhrase("","")+" 당신을 보게 되어, "+GetFullName(npchar)+". 현지 총독, "+sTemp+" 너에 대해서만 이야기하고 있어.");
			Link.l1.go = "DestroyGang_1";
		break;		
		case "DestroyGang_1":
			dialog.text = LinkRandPhrase("그래, 이 땅에서 내 이름 좀 알려졌지, 헤헤... 잠깐, 너도 또 다른 놈 아니냐 "+GetSexPhrase("더러운 개새끼","더러운 년")+" 나를 추적하라고 그를 보낸 총독의 부하인가?","총독은 내 좋은 친구지, 그건 사실이야. 그런데 혹시, 너는\n "+GetSexPhrase("또 다른 영웅이 보내졌군","또 한 명의 여주인공이 보내졌다")+" 그가 내 목을 노리고?","총독은 내 제일 친한 친구야, 다들 아는 사실이지, 헤헤. 그런데 그걸 어떻게 알았지? 혹시 총독이 나를 쫓으라고 너를 보낸 건가?");
			Link.l1 = LinkRandPhrase("그래, 이 악당아. 죽을 준비나 해라!","눈치 빠른 녀석이군! 좋아, 이제 네 처분을 진행할 시간이야. 말은 그만하지.","그래, 나야. 무기 뽑아라, 이 친구! 네 피가 무슨 색인지 한번 보자.");
			Link.l1.go = "DestroyGang_ExitFight";	
			Link.l2 = LinkRandPhrase("아, 됐어! 그런 골치 아픈 일 따위 전혀 필요 없어...","아니, 아니오, 나는 결코 영웅이 아닙니다...","아니, 아니야, 절대 그런 일 없어! 나는 문제 일으키고 싶지 않아...");
			Link.l2.go = "DestroyGang_2";	
		break;
		case "DestroyGang_2":
			dialog.text = LinkRandPhrase("이제 좀 낫군, "+GetSexPhrase("동료","아가씨")+"...이제 썩 꺼져라!","그래, 그게 옳은 결정이지. 내가 얼마나 많은 영웅들을 저세상으로 보냈는지 네가 알았으면 좋겠군... 됐다, 말은 여기까지다. 꺼져라, "+GetSexPhrase("개똥 같은 놈","개년")+"!","Good "+GetSexPhrase("소년","소녀")+"! 아주 현명한 결정이군 - 남의 일에 끼어들지 않는 게 좋아... 좋아, 이제 가 보거라, "+GetSexPhrase("동료","아가씨")+".");
			Link.l1 = "안녕히 가시오, 행운이 함께하길 바라오...";
			Link.l1.go = "DestroyGang_ExitAfraid";	
		break;

		case "DestroyGang_ExitAfraid":
			pchar.GenQuest.DestroyGang = "Found"; //флаг нашёл, но струсил
			npchar.money = AddMoneyToCharacter(npchar, sti(pchar.money));
			pchar.money = 0;
			LAi_SetWarriorType(npchar);
			LAi_SetImmortal(npchar, false);
			LAi_SetCheckMinHP(npchar, LAi_GetCharacterHP(npchar)-1, false, "DestroyGang_SuddenAttack");
			for(i = 1; i < 4; i++)
			{
				if (GetCharacterIndex("MayorQuestGang_" + i) == -1) continue;	
				sld = CharacterFromID("MayorQuestGang_" + i);
				LAi_SetActorType(sld);
				LAi_ActorFollow(sld, npchar, "", -1);
				LAi_SetImmortal(sld, true);
				LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, false, "DestroyGang_SuddenAttack");
			}
			DialogExit();
		break;

		case "DestroyGang_ExitFight":
			for(i = 0; i < 4; i++)
			{
				if (GetCharacterIndex("MayorQuestGang_" + i) == -1) continue;
				sld = CharacterFromID("MayorQuestGang_" + i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "DestroyGang_Afrer");
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		// ОЗГ - пассажир
		case "ContraPass_abordage":
			dialog.text = "아르그, 이 악당 녀석! 감히 내 배를 공격하다니?! 그 대가를 치르게 해주마!";
			link.l1 = "반대로, 나는 사실 이 일로 돈을 받고 있지. 네 배에 한 남자가 타고 있는데, 이름은 "+pchar.GenQuest.TakePassenger.Name+". 내가 필요한 사람이다.";
			link.l1.go = "ContraPass_abordage_1";
		break;
		
		case "ContraPass_abordage_1":
			dialog.text = "나는 이 사기꾼이 우리에게 문제를 가져올 줄 알았지... 하지만 나를 그렇게 쉽게 잡을 순 없을 거다! 각오해라, 더러운 해적놈!";
			link.l1 = "방어를 생각해야 할 놈은 바로 너다, 이 개새끼야.";
			link.l1.go = "ContraPass_abordage_2";
		break;
		
		case "ContraPass_abordage_2":
			DialogExit();
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "ContraPass_GivePrisoner");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Tempsailor":
			dialog.text = "선장님, 명령하신 대로 선실과 화물창을 모두 수색했습니다. 그 악당이 숨으려 했지만 우리가 찾아냈습니다.";
			link.l1 = "훌륭해! 지금 그는 어디 있지?";
			link.l1.go = "Tempsailor_1";
		break;
		
		case "Tempsailor_1":
			dialog.text = "명령하신 대로 그는 선창에 있습니다.";
			link.l1 = "훌륭해! 이제 이 낡은 배에서 내려가자. 돌아갈 시간이야.";
			link.l1.go = "Tempsailor_2";
		break;
		
		case "Tempsailor_2":
			dialog.text = "바로 하겠습니다, 선장님!";
			link.l1 = "...";
			link.l1.go = "Tempsailor_3";
		break;
		
		case "Tempsailor_3":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 10.0);
			sld = GetCharacter(NPC_GenerateCharacter("ContraPass", "citiz_"+(rand(9)+11), "man", "man", 10, sti(pchar.GenQuest.TakePassenger.Nation), -1, true, "quest"));
			sld.name = pchar.GenQuest.TakePassenger.Name;
			sld.lastname = "";
			pchar.GenQuest.LastQuestPrisonerIdx = SetCharToPrisoner(sld);
			SetCharacterRemovable(&characters[sti(pchar.GenQuest.LastQuestPrisonerIdx)], false);
			Pchar.GenQuest.TakePassenger.PrisonerIDX = sti(pchar.GenQuest.LastQuestPrisonerIdx);
		break;
		
		case "Fugitive_city": // ходит по городу
			pchar.quest.AllMayorsQuests_Late.over = "yes"; //снимаем общий таймер
			dialog.text = "무슨 일이십니까, 나리?";
			link.l1 = "그래, 그래... 그러니까 네가 "+pchar.GenQuest.FindFugitive.Name+", 아니오? 다시 보게 되어 정말 반갑소...";
			link.l1.go = "Fugitive_city_1";
		break;
		
		case "Fugitive_city_1":
			dialog.text = "그래, 그게 바로 나지. 그런데 왜 나를 보고 반가워하는 거지? 난 너를 처음 보는데 좀 이상하군... 설명 좀 해볼래?";
			link.l1 = "물론이지. 나는 ...에서 왔어 "+XI_ConvertString("Colony"+pchar.GenQuest.FindFugitive.Startcity+"Gen")+", 이 지역 총독의 명령이다. 너는 체포됐고, 내가 너를 바로 그 도시로 데려가야 해... 아, 그리고 칼에 손 대지 마! 멍청한 짓 하지 마라, 착한 친구, 그러지 않으면 큰일 날 거다!";
			link.l1.go = "Fugitive_city_2";
		break;
		
		case "Fugitive_city_2":
			dialog.text = "그래, 결국 나를 찾아냈군... 나리, 내 말 좀 들어보시오. 그러면 생각이 바뀔지도 모르지. 그래, 나는 주둔지에서 탈영했소. 하지만 우리 군대가 타락해가는 모습을 더는 볼 수 없었소!\n나는 평화로운 삶을 원했고, 이 마을에서 그런 삶을 찾았소... 그냥 나를 내버려 두시오. 나를 못 찾았다고 하거나, 내가 해적들과 함께 바다로 도망쳤다고 전해주시오. 대신 이 호박 주머니를 드리겠소. 아주 귀한 물건이오, 분명히...";
			link.l1 = "나한테 뇌물 생각도 하지 마, 나리! 무기 내려놓고 따라와!";
			link.l1.go = "Fugitive_city_fight";
			link.l2 = "흠... 타락이라고? 조용하고 평화로운 삶을 원하나? 좋아, 네 소원을 들어주지. 네 호박은 어디 있지?";
			link.l2.go = "Fugitive_city_gift";
		break;
		
		case "Fugitive_city_fight":
			dialog.text = "그럼 칼을 뽑아라, 용병놈! 이렇게 쉽게 날 잡을 순 없을 거다!";
			link.l1 = "좋아, 네가 얼마나 쓸모 있는지 보자!";
			link.l1.go = "Fugitive_fight_1";
		break;
		
		case "Fugitive_city_gift":
			TakeNItems(pchar, "jewelry8", 50+hrand(25));
			TakeNItems(pchar, "jewelry7", 2+hrand(5));
			PlaySound("interface\important_item.wav");
			Log_Info("You have received amber");
			dialog.text = "여기... 그리고 나는 다시는 너나 다른 '사절'들을 보고 싶지 않다는 걸 정말 바란다.";
			link.l1 = "장담하건대, 그런 일은 없을 것이오. 안녕히 가시오, 나리!";
			link.l1.go = "Fugitive_gift_exit";
		break;
		
		case "Fugitive_gift_exit":
			DialogExit();
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
			pchar.GenQuest.FindFugitive = "Found"; //флаг провалил
			AddQuestRecord("MayorsQuestsList", "12-4");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+pchar.GenQuest.FindFugitive.Startcity));
		break;
		
		case "Fugitive_fight_1":// в городе и бухте
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			Diag.currentnode = "Fugitive_afterfight";
			LAi_SetImmortal(npchar, false);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_SetCheckMinHP(npchar, 10.0, true, "Fugitive_afterfight");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "Fugitive_afterfight":
			dialog.text = "아르르! 젠장, 네가 이겼군! 항복하겠다...";
			link.l1 = "말조심하시오, 나리! 이제 검을 내놓으시오... 따라오시오, 쓸데없는 짓 하지 말고!";
			link.l1.go = "Fugitive_afterfight_1";
		break;
		
		case "Fugitive_afterfight_1":
			DialogExit();
			RemoveAllCharacterItems(npchar, true);
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			//DeleteAttribute(npchar, "LifeDay");
			npchar.lifeday = 0;
			LAi_SetImmortal(npchar, true);
			pchar.GenQuest.LastQuestPrisonerIdx = SetCharToPrisoner(npchar);
			SetCharacterRemovable(&characters[sti(pchar.GenQuest.LastQuestPrisonerIdx)], false);
			Pchar.GenQuest.FindFugitive.PrisonerIDX = sti(pchar.GenQuest.LastQuestPrisonerIdx);
			pchar.GenQuest.FindFugitive = "Execute"; //флаг выполнил успешно
			pchar.quest.FindFugitive1.win_condition.l1 = "location";
			pchar.quest.FindFugitive1.win_condition.l1.location = pchar.GenQuest.FindFugitive.Startcity+"_townhall";
			pchar.quest.FindFugitive1.function = "FindFugitive_inResidence";
			SetFunctionTimerCondition("FindFugitive_Over", 0, 0, 30, false);
		break;
		
		case "Fugitive_shore": // в бухте
			pchar.quest.AllMayorsQuests_Late.over = "yes"; //снимаем общий таймер
			dialog.text = "나리, 지금은 당신과 이야기할 기분이 아니니, 그러니...";
			link.l1 = "그럼에도 불구하고, 나와 이야기해야 할 거요. 당신은 "+pchar.GenQuest.FindFugitive.Name+", 그렇지? 부정하지 않는 게 좋을 거야.";
			link.l1.go = "Fugitive_shore_1";
		break;
		
		case "Fugitive_shore_1":
			dialog.text = "그리고 그건 부정하지 않겠어, 그게 나야. 그런데 뭘 원하는 거지?";
			link.l1 = "너를 데려가야 해 "+XI_ConvertString("Colony"+pchar.GenQuest.FindFugitive.Startcity)+", 이 지역 총독께서 당신을 뵙고 싶어 하신다네. 장난은 금물이야! 무기를 넘기고 나를 따라오시오!";
			link.l1.go = "Fugitive_shore_2";
		break;
		
		case "Fugitive_shore_2":
			dialog.text = "알겠소... 나리, 경솔하게 행동하기 전에 제 말을 좀 들어주십시오. 그래요, 저는 수비대를 탈영했소. 하지만 나름대로 이유가 있었소. 더는 그 복무를 견딜 수 없었소! 제 말 이해하시겠습니까? 정말 못 하겠소!\n저는 평화로운 삶을 원했고, 이 마을에서 그걸 찾았소... 저를 내버려 두시고, 저를 못 찾았다고 하거나 해적들과 함께 바다로 도망쳤다고 전해주십시오. 대신, 제가 매주 잡는 진주를 드리겠소. 그게 제가 가진 전부요.";
			link.l1 = "나한테 뇌물 생각도 하지 마시오, 나리! 무기를 넘기고 따라오시오!";
			link.l1.go = "Fugitive_city_fight";
			link.l2 = "흠... 군 복무가 지겨운가? 평화로운 삶을 원해? 좋아, 네 소원을 들어줄 수도 있지. 진주는 어디 있지?";
			link.l2.go = "Fugitive_shore_gift";
		break;
		
		case "Fugitive_shore_gift":
			TakeNItems(pchar, "jewelry52", 100+hrand(40));
			TakeNItems(pchar, "jewelry53", 400+hrand(100));
			PlaySound("interface\important_item.wav");
			Log_Info("You have received pearls");
			dialog.text = "여기... 그리고 너나 다른 '사절'들을 다시는 보고 싶지 않다는 걸 정말 바란다.";
			link.l1 = "장담하건대, 그럴 일 없을 거요. 안녕히 가시오, 나리!";
			link.l1.go = "Fugitive_gift_exit";
		break;
		
		case "Fugitive_tavern": // в таверне
			pchar.quest.AllMayorsQuests_Late.over = "yes"; //снимаем общий таймер
			dialog.text = "에에... 힉! 나리, 나는 동행을 찾지 않아 - 특히 너 같은 놈은 더더욱. 꺼져!";
			link.l1 = "하지만 나는 정말로 네가 함께해 주길 바라고 있어, "+pchar.GenQuest.FindFugitive.Name+"! 그리고 내 배의 창고에서 내 동행을 참아야 할 거야. 우리는 갈 거다  "+XI_ConvertString("Colony"+pchar.GenQuest.FindFugitive.Startcity)+", 그 도시의 총독에게로. 그는 당신을 거의 애타게 기다리고 있어요.";
			link.l1.go = "Fugitive_tavern_1";
		break;
		
		case "Fugitive_tavern_1":
			dialog.text = "히- hic!"+RandSwear()+" 결국 나를 찾아냈군! 이봐, 친구, 넌 무슨 일이 있었는지 몰라, 거기 없었잖아! 난 더 이상 그 일을 계속할 수 없었어, 정말로 못 하겠더라고! 아직도 그걸 잊으려고 매일 저녁 술에 취해 살아.\n자, 우리 거래하자. 그 사람한테 날 못 찾았다고 하든지, 아니면 내가 해적들과 함께 바다로 도망쳤다고 해 줘. 대신 내가 이 근처 동굴에서 찾은 금덩이 전부 줄게. 내가 가진 건 이게 다야, 알겠지? 네게 전부 주는 거야, 다시는 그 사람을 보지 않으려고. "+XI_ConvertString("Colony"+pchar.GenQuest.FindFugitive.Startcity)+"...";
			link.l1 = "나한테 뇌물 생각도 하지 마, 나리! 무기 내려놓고 따라와!";
			link.l1.go = "Fugitive_tavern_fight";
			link.l2 = "흠... 불쾌한 이야기인가? 악몽에 시달리거나 양심의 가책을 느끼는 거야? 좋아, 네가 알아서 하도록 내버려두지. 너의 금덩이들은 어디 있지?";
			link.l2.go = "Fugitive_tavern_gift";
		break;
		
		case "Fugitive_tavern_gift":
			TakeNItems(pchar, "jewelry5", 50+hrand(30));
			TakeNItems(pchar, "jewelry6", 100+hrand(50));
			PlaySound("interface\important_item.wav");
			Log_Info("You have received nuggets");
			dialog.text = "여기... 그리고 나는 다시는 너나 다른 '사절'들을 보고 싶지 않다는 걸 진심으로 바란다.";
			link.l1 = "장담하건대, 절대 그럴 일 없소. 안녕히 가시오, 나리!";
			link.l1.go = "Fugitive_gift_exit";
		break;
		
		case "Fugitive_tavern_fight":
			dialog.text = "그렇다면 칼을 뽑아라, 용병놈! 그렇게 쉽게 날 잡을 수 있을 줄 알았나!";
			link.l1 = "좋아, 네가 얼마나 쓸모 있는지 보자!";
			link.l1.go = "Fugitive_fight_2";
		break;
		
		case "Fugitive_fight_2":// в таверне
			DialogExit();
			chrDisableReloadToLocation = true;//закрыть локацию
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			LAi_SetImmortal(npchar, false);
			LAi_SetStayType(npchar);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(npchar, pchar.location, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			Diag.currentnode = "Fugitive_afterfight";
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_SetCheckMinHP(npchar, 10.0, true, "Fugitive_afterfight");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
	}
}
