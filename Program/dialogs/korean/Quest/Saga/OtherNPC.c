// диалог прочих НПС по квесту Саги
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
			dialog.text = "뭐 원하는 거 있어?";
			link.l1 = "아니, 아무것도 없어.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
//---------------------------------------------Джимми в доме в Марун-Тауне------------------------------------
		case "Jimmy":
			dialog.text = "뭘 원해? 지금 내가 상중인 거 안 보여? 계단 아래로 걷어차기 전에 썩 꺼져!";
			link.l1 = "그럼 계단 있는 더 큰 집이나 사라. 그다음에나 사람을 계단에서 걷어차는 얘기를 하자고, 영웅님...";
			link.l1.go = "Jimmy_1_1";
			link.l2 = "왜 이렇게 화가 났어, 지미? 아름다운 여자가 아니고서야 평생 럼주를 끊겠다고 맹세하지! 너 같은 바다늑대가 옛 친구들한테 협박까지 하는 건 여자 때문일 수밖에 없지...";
			link.l2.go = "Jimmy_1_2";
		break;
		
		case "Jimmy_1_1":
			dialog.text = "나는 너처럼 까다로운 인간들이 정말 싫어! 항상 케이크에서 제일 좋은 조각만 챙기잖아. 건방진 놈 하나 죽이게도 안 해줬으니, 네놈한테 화풀이해야겠다!";
			link.l1 = "...";
			link.l1.go = "Jimmy_fight";
		break;
		
		case "Jimmy_fight":
			DialogExit();
			AddDialogExitQuestFunction("Saga_Jimmy_fight");
		break;
		
		case "Jimmy_1_2":
			dialog.text = "그래?! 내가 너를 아나? 젠장, 기억 안 나는데...";
			link.l1 = "나다, "+pchar.name+"! 네가 그 건방진 외투 입은 녀석 배를 거의 갈라놨을 때, 블루웰드에서 정말 신나게 놀았지. 그 자식 이름이 뭐였더라? 까먹었네... 어쨌든, 내가 바다에서 그놈 다시 만나도 그놈 코르벳의 대포 따위 신경도 안 쓸 거야!";
			link.l1.go = "Jimmy_2";
		break;
		
		case "Jimmy_2":
			dialog.text = "그 자 이름은 아서였어! 아서 도노반, '아버투스' 코르벳의 선장이었지! 더러운 놈! 그러니까 내가 그 자를 지옥으로 보낼 뻔했다는 데 동의하는 거지?";
			link.l1 = "물론이지! 그 자에겐 전혀 승산이 없었지만, 네 친구들이 끼어들었어. 용서해 줘, 네가 해군 장교 살인죄로 목매달리는 걸 원치 않았던 거야.";
			link.l1.go = "Jimmy_3";
		break;
		
		case "Jimmy_3":
			dialog.text = "아악! 내게 배만 있었더라면! 그 자식은 앤티과 근처에서 쉽게 쫓을 수 있는데... 하! 그놈을 바다 밑으로 보내주면 신세 한 번 크게 질게!";
			link.l1 = "거래지, 하하! 그런데, 럼바가 정말 그렇게 고생할 만한 가치가 있나?";
			link.l1.go = "Jimmy_4";
		break;
		
		case "Jimmy_4":
			dialog.text = "물론이지! 나보다 그녀를 더 잘 아는 사람은 없었어. 하지만 그녀는 나를 비웃기만 해. 모두가 그 인어를 원하지. 몇몇 선원들은 몰래 우리 야곱이 내 룸바랑 똑같이 생긴 여자를 찾고 있다고 말하더군. 그 녀석도 그녀를 원해! 이제 내가 어떻게 그 녀석 명령을 따르겠어?";
			link.l1 = "조용히 해, 이 친구야! 벽에도 귀가 있다니까... 그리고 잭맨이 왜 룸바를 찾는다고 생각해?";
			link.l1.go = "Jimmy_5";
		break;
		
		case "Jimmy_5":
			dialog.text = "맞아, 확실해! 그 자는 헨리 더 행맨이라는 놈이랑 금발에 파란 눈을 가진 스무 살짜리 아가씨를 찾고 있더라. 벨리즈 출신의 글래디스 챈들러라는 여자가 그 아가씨를 돌보고 있대.";
			link.l1 = "잠깐! 글래디스는 성이 달라. 그리고 그녀가 그녀의 어머니야!";
			link.l1.go = "Jimmy_6";
		break;
		
		case "Jimmy_6":
			dialog.text = "잭맨은 교활해! 그 자는 허를 찔릴 일이 없지! 내가 한동안 룸바를 꼬드기면서 알아낸 건, 글래디스가 정확히 이십 년 전에 션 맥아더와 결혼했다는 거야. 그 전에는 벨리즈에 살았고, 첫 남편 이름은 피트 챈들러였지.\n불쌍한 피트는 술에 취해 싸우다 죽었어. 맥아더가 그 일에 책임이 있다는 소문이 돌았지, 그때부터 통통한 글래디스에게 마음이 있었다더군. 글래디스는 아기를 안고 홀로 됐고, 그 애도 얼마 못 가서 열병으로 죽었어.\n그리고 몇 달 지나지 않아, 글래디스와 션이 블루웰드에 나타났지. 맥아더의 딸이라는 여자아이를 데리고 말이야. 그런데 글래디스가 그렇게 금방 또 아이를 낳을 수 있었겠어? 내 말 이해하지?";
			link.l1 = "이 일에 대해 다른 사람에게도 말했소?";
			link.l1.go = "Jimmy_7";
		break;
		
		case "Jimmy_7":
			dialog.text = "아직 아니야. 입 다물고 있어, 아니면... 뭐, 나 어떤 사람인지 알잖아!";
			link.l1 = "그래, 맞아. 네 입은 썩어서 비밀을 다 떠벌리고 다니지. 룸바가 너를 내쫓은 건 잘한 일이야, 수다쟁이 녀석...";
			link.l1.go = "Jimmy_8_1";
			link.l2 = "알겠어! 입 다물고 있을게! 이제 가봐야 해. 잘 있어, 지미.";
			link.l2.go = "Jimmy_8_2";
		break;
		
		case "Jimmy_8_1":
			dialog.text = "뭐... 뭐라고 했어?!";
			link.l1 = "다른 누구에게도 말하지 못할 거야...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Saga_KillToJimmy_kino");
		break;
		
		case "Jimmy_8_2":
			DialogExit();
			AddDialogExitQuestFunction("Saga_Jimmy_DlgExit");
		break;
// <-- Джимми 
		
//-------------------------------------------корвет Донована, абордаж-----------------------------------------
		//Донован
		case "Donovan_abordage":
			PlaySound("Voice\English\saga\Artur Donovan.wav");
			dialog.text = "으악, 이 괴물 놈아!";
			link.l1 = "혼잣말 하는 거야, 나리?! 룸바는 어디 있지?";
			link.l1.go = "Donovan_abordage_1";
		break;
		
		case "Donovan_abordage_1":
			dialog.text = "무슨 룸바? 내 배에는 별명 붙은 잡놈 따윈 없어. 여긴 영국 해군 함선이다!";
			link.l1 = "나랑 바보짓 하지 마, 도노반. 내가 누구 말하는지 뻔히 알잖아. 그 여자애 어디 있어? 헬렌 어디 있냐? 대답해, 이 더러운 놈아...";
			link.l1.go = "Donovan_abordage_2";
		break;
		
		case "Donovan_abordage_2":
			dialog.text = "헬렌? 내 배에는 뭍에서 온 창녀 따위 없어, 이 개새끼야!";
			link.l1 = "뭍 창녀가 없다고? 믿기 힘들군, 왜냐하면 바로 지금 내 앞에 한 명이 서 있으니까... 더 대화할 필요도 없겠지. 죽어라, 이 한심한 벌레야!";
			link.l1.go = "Donovan_abordage_3";
		break;
		
		case "Donovan_abordage_3":
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "Saga_AfterDonovanBoarding");
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.questTemp.Saga.Takehelen = "true";//признак, что абордировали судно
		break;
		
		//наш матрос
		case "Tempsailor":
			dialog.text = "선장님, 지시하신 대로 모든 선실과 화물창을 다 뒤졌습니다. 화물창에서 사슬에 묶인 소녀를 발견했습니다...";
			link.l1 = "정말 개자식이군! 내 예상대로야... 그 여자애는 풀어줬어?";
			link.l1.go = "Tempsailor_1";
		break;
		
		case "Tempsailor_1":
			dialog.text = "물론입니다, 선장님. 그녀는 안전하게 선장님의 배에 모셔졌습니다.";
			link.l1 = "잘했네! 그녀를 내 선실로 데려가게. 여기 일이 끝나면 그녀와 이야기하고 싶으니.";
			link.l1.go = "Tempsailor_2";
		break;
		
		case "Tempsailor_2":
			dialog.text = "알겠어요, 선장님!";
			link.l1 = "...";
			link.l1.go = "Tempsailor_3";
		break;
		
		case "Tempsailor_3":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 10.0);
		break;
		//<-- абордаж корвета Донована
		
//----------------------------------------поиск Энрике Гонсалеса, Картахена----------------------------------
		//фальшивый Гонсалес №1, дом
		case "GonsalesA":
			dialog.text = "뭐 원하는 거라도 있어?";
			link.l1 = "이봐, 교수형 집행인! 부처 선장이 안부 전하래.";
			link.l1.go = "GonsalesA_1_1";
			link.l2 = "내 이름은 샤를 드 모르다. 나는 세뇨라 곤살레스의 옛 친구를 대신해 그녀의 아들 엔리케를 찾고 있다. 네가 바로 그 사람이라고 생각하는데...\n";
			link.l2.go = "GonsalesA_2_1";
		break;
		
		case "GonsalesA_1_1":
			dialog.text = "이런 젠장! 나는 도살꾼이라는 놈을 전혀 몰라!";
			link.l1 = "어서 말해, 헨리. 왜 잭맨의 해적들이 너를 쫓는지 말하면 다치게 하진 않을 테니까.";
			link.l1.go = "GonsalesA_1_2";
		break;
		
		case "GonsalesA_1_2":
			dialog.text = "도와줘! 해적이다! 살인이다!";
			link.l1 = "닥쳐, 바보야! 네가 소리 지르는 바람에 마을 절반이 여기로 몰려올 거라고. 아, 그게 네 목적이냐?!";
			link.l1.go = "GonsalesA_1_fight";
		break;
		
		case "GonsalesA_1_fight":
			DialogExit();
			SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			LAi_group_MoveCharacter(NPChar, "EnemyFight");
			LAi_group_Attack(NPChar, Pchar);
			LAi_group_SetCheck("EnemyFight", "Saga_KillGonsalesA");
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.questTemp.Saga.Trap = "true";
		break;
		
		case "GonsalesA_2_1":
			dialog.text = "흠... 나리, 착각하신 것 같습니다. 저는 외국인 가정에서 자랐고, 친어머니에 대한 기억이 없습니다. 양부의 성을 물려받았지요. 어머니의 이름도 모르고, 곤살레스였을 것 같지도 않습니다. 저에 대해 물어보시면 이 마을의 오래된 주민 누구든 제 말을 확인해줄 겁니다. 제 양아버지는 유명한 분이셨고, 자식이 없으셔서 이 집을 제가 물려받았고...\n";
			link.l1 = "미안하오. 내가 착각했던 것 같소. 안녕히 가시오.";
			if(CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold")) link.l1.go = "GonsalesA_3_1";
			else link.l1.go = "GonsalesA_2_2";
		break;
		
		case "GonsalesA_2_2":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			chrDisableReloadToLocation = false;//открыть локацию
			AddQuestRecord("Saga", "17");
		break;
		
		// belamour участвовал в событиях Картахены -->
		case "GonsalesA_3_1":
			dialog.text = "그렇지 않다고 생각해.";
			link.l1 = "뭐라고?";
			link.l1.go = "GonsalesA_3_2";
		break;
		
		case "GonsalesA_3_2":
			dialog.text = "있잖소, 최근에 우리 식민지가 해적들에게 잔혹하게 습격당했소. 이 소식은 이미 들었으리라 믿소만? 그 습격으로 인해 수많은 사람들이 고통을 겪었소. 나는 다치지 않았지만, 대대로 이어온 내 사업이 지금 큰 어려움을 겪고 있소. 그리고 이 모든 재앙의 원흉은 바로 그 해적들의 두목, 찰리 프린스라는 악당이오.";
			link.l1 = "정말 유감이지만, 그게 나와 무슨 상관이 있소?";
			link.l1.go = "GonsalesA_3_3";
		break;
		
		case "GonsalesA_3_3":
			dialog.text = "하하, 이 순진한 양 좀 봐라! 내 손해를 네가 대신 갚는 게 어떻겠냐? 네가 책임이 있으니 말이지. 만오천 페소면 만족하겠다. 그리고 네가 내 집에 온 적 없던 걸로 해주지.";
			if (sti(pchar.money) >= 15000)
			{
				link.l1 = "정말들 앙심이 깊군... 자, 돈이다. 그리고 기억해둬라, 내가 이 마을에 있었다는 걸 누가 알게 되면, 반드시 너희를 찾아올 거다.";
				link.l1.go = "GonsalesA_3_4";
			}
			link.l2 = "만오천? 흠... 네 목숨이 그 정도 가치가 있다고는 생각 안 하는데. 그러니 입을 막으려면 그냥 베어버리는 게 더 싸게 먹히겠군.";
			link.l2.go = "GonsalesA_3_5";
		break;
		
		case "GonsalesA_3_4":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			chrDisableReloadToLocation = false;//открыть локацию
			AddQuestRecord("Saga", "171");
		break;
		
		case "GonsalesA_3_5":
			dialog.text = "경비병들! 해적이다! 살인이다!";
			link.l1 = "닥쳐, 이 멍청아!";
			link.l1.go = "GonsalesA_3_6";
		break;
		
		case "GonsalesA_3_6":
			DialogExit();
			iTemp = sti(pchar.rank) + MOD_SKILL_ENEMY_RATE - 2;
			for (i=1; i<=2; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("SpSold"+i, "sold_" + NationShortName(SPAIN) + "_" + (rand(1) + 1), "man", "man", iTemp, SPAIN, 0, true, "soldier"));
				SetFantomParamFromRank(sld, iTemp, true);         
				LAi_SetWarriorType(sld); 
				LAi_warrior_DialogEnable(sld, false);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload1");
			}
			sld = GetCharacter(NPC_GenerateCharacter("SpOfficer", "off_" + NationShortName(SPAIN) + "_" + (rand(1) + 1), "man", "man", iTemp, SPAIN, 0, true, "quest"));
			FantomMakeCoolFighter(sld, 25, 100, 100, "blade_13", "pistol6", "bullet", 150);
			ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload1");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_MoveCharacter(NPChar, "EnemyFight");
			LAi_group_Attack(NPChar, Pchar);
			LAi_group_SetCheck("EnemyFight", "Saga_KillGonsalesAK");
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.questTemp.Saga.Trap = "true";
		break;
		// <-- участвовал в событиях Картахены
		
		// фальшивый Гонсалес №2, улицы
		case "GonsalesB":
			PlaySound("Voice\English\citizen\Pirati v Gorode-08.wav");
			dialog.text = "내 커틀라스가 마음에 드는 모양이군. 원한다면 팔 수도 있지. 많이는 안 받을 거야, 럼주 한 잔이 간절한데 주머니가 텅 비었거든.";
			link.l1 = "대체 내가 그걸 왜 필요로 하지? 숲의 악마가 너에게 안부 전해 달라고 했어.";
			link.l1.go = "GonsalesB_1_1";
			if (sti(pchar.money) >= 1000)
			{
				link.l2 = "그래, 맞아. 정말 멋진 커틀라스구나. 얼마지?";
				link.l2.go = "GonsalesB_2_1";
			}
		break;
		
		case "GonsalesB_1_1":
			dialog.text = "차라리 내게 페소 몇 백 개를 줬으면 더 나았을 텐데!";
			link.l1 = "스벤손을 아는 거야?";
			link.l1.go = "GonsalesB_1_2";
		break;
		
		case "GonsalesB_1_2":
			dialog.text = "좆까, 그리고 네 스벤손도 좆까. 그 자식은 지옥으로나 보내버려. 숲의 악마든 바다의 악마든, 나한텐 상관없어. 병든 놈이 칼 한 자루 팔겠다는데 도와줄 생각이 없다면, 공짜로 네 엉덩이에 꽂아주지.";
			link.l1 = "정말이냐? 어디 한번 어떻게 할 건지 보자, 개새끼야!";
			link.l1.go = "GonsalesB_1_fight";
		break;
		
		case "GonsalesB_1_fight":
			chrDisableReloadToLocation = true;
			DialogExit();
			LAi_group_MoveCharacter(NPChar, "EnemyFight");
			LAi_group_Attack(NPChar, Pchar);
			LAi_group_SetCheck("EnemyFight", "Saga_KillGonsalesB");
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.questTemp.Saga.Trap = "true";
		break;
		
		case "GonsalesB_2_1":
			dialog.text = "경험이 많은 분이시군요! 천 페소면 당신 겁니다.";
			link.l1 = "거래 성사!";
			link.l1.go = "GonsalesB_2_2";
		break;
		
		case "GonsalesB_2_2":
			AddMoneyToCharacter(pchar, -1000);
			GiveItem2Character(pchar, "blade_10");
			RemoveCharacterEquip(npchar, BLADE_ITEM_TYPE);
			dialog.text = "카르타헤나에는 이런 커틀라스가 두 자루밖에 없어. 내 거랑 등대의 늙은 알바레스 거지. 하지만 그는 절대 자기 걸 팔지 않아. 위선자야, 난 전직 해적 냄새를 멀리서도 맡을 수 있거든. 그에게 이 칼날은 일종의 부적인가 봐.\n불쌍한 영혼이 잊고 싶은 걸 후회하는 모양이야. 그래서 매달 교회에 가는 거겠지, 잠도 못 이루게 괴롭히는 죄 때문에.";
			link.l1 = "그리고 보니 너도 뭔가 사연이 있군. 네가 바로 스벤손이 말하던 그 사람인가 보네. 내가 카르타헤나에서 너를 만나면 꼭 안부를 전해 달라고 했어.";
			link.l1.go = "GonsalesB_2_3";
		break;
		
		case "GonsalesB_2_3":
			dialog.text = "스벤손? 처음 듣는 이름인데. 내 이름은 엔리케 가야르도야. 근데 네 스벤손이 나한테 럼주 한 병 준다면, 그를 위해 헨리라고 불려도 상관없지. 뭐라고 불러도 좋아, 저녁만 늦지 않게 불러라. 자, 우리 가는 거냐?\n";
			link.l1 = "오늘은 아니야. 스벤손은 멀리 있지만, 선술집은 가까워. 이제 주머니도 비지 않았으니 조심해, 엔리케.";
			if(CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold")) link.l1.go = "GonsalesB_3_1";
			else link.l1.go = "GonsalesB_2_4";
		break;
		
		case "GonsalesB_2_4":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 20.0);
			npchar.lifeday = 0;
			AddQuestRecord("Saga", "19");
			pchar.questTemp.Saga = "ortega";
			Saga_SetOrtega();
		break;
		
		// belamour участвовал в событиях Картахены -->
		case "GonsalesB_3_1":
			dialog.text = "아직 완전히 차진 않았어. 더 원해. 그리고 네가 돈을 내야 해.";
			link.l1 = "어이가 없군... 네 목숨이 소중하지도 않나? 도시 한복판에서 나를 털 생각이야? 게다가 방금 네 무기를 직접 나한테 팔아놓고?";
			link.l1.go = "GonsalesB_3_2";
		break;
		
		case "GonsalesB_3_2":
			dialog.text = "아니, 네가 직접 내게 돈을 내야 해. 그리고 이유는 알겠지?";
			link.l1 = "흥미롭군.";
			link.l1.go = "GonsalesB_3_3";
		break;
		
		case "GonsalesB_3_3":
			dialog.text = "널 알아봤지. 내가 선술집에서 술 마시다 싸움이 붙어서 감옥에 갇혀 있었는데, 네 놈들이 감옥에 들이닥쳐서 간수들을 다 베어버렸거든. 나는 열쇠 가진 간수 시체까지 겨우 기어가서 거리로 빠져나왔지. 도시 전체가 불타고, 시체랑 피, 화약 연기가 사방에 자욱했어... 마치 배에 올라타 싸울 때처럼 말이야! 그리고 그 연기 사이로 네가 총독 관저에서 나오는 걸 봤다. 시 같지 않냐? 요호호, 안녕하신가, 찰리 프린스!";
			link.l1 = "그렇게 소리치지 마! 네가 아는 걸 생각하면, 특히 나한테 돈을 뜯으려 들면 안 되지. 내가 너한테 뭘 할 수 있는지 알기나 해?";
			link.l1.go = "GonsalesB_3_4";
		break;
		
		case "GonsalesB_3_4":
			dialog.text = "네가 한때 털었던 그 도시 한복판에서? 넌 아무것도 못 해. 그러니 결론을 내리자면... 이렇게 하자. 지금 당장 나한테... 글쎄, 만 페소쯤 주면 되겠군. 그 정도면 한 달은 충분하겠지. 그리고 넌 네 갈 길을 가라! 네가 사랑하는 헨리든, 스벤손이든, 아니면 네가 고를 다른 악마에게든 말이야... 만약 안 준다면, 내가 소리만 지르면, 널 고문 도구로 가득 찬 특별히 준비된 개인 방으로 끌고 갈 거다.";
			if (sti(pchar.money) >= 10000)
			{
				link.l1 = "젠장, 만 냥 챙기고 내 눈앞에서 꺼져라! 그리고, 다시는 내 앞에 나타나지 마라, 제발.";
				link.l1.go = "GonsalesB_3_5";
			}
			link.l2 = "이제 끝이다, 더는 못 참겠다. 네 무기는 내 손에 있으니, 넌 이제 아무런 희망도 없어, 이 쓰레기야.";
			link.l2.go = "GonsalesB_3_7";
			link.l3 = "하하, 너 제법인데! 있잖아, 다른 놈들이었으면 진작에 배부터 목까지 갈랐을 거다. 하지만 너 같은 녀석은 필요해. 이렇게 하자: 내가 만 페소를 주고, 네 '교수형 당한 자'도 돌려주지. 거기에 매달 삼천 페소씩 더 얹어줄게—술 마시기엔 충분할 거다—그리고 넌 내 배에 승선하는 식구가 되는 거야.";
			link.l3.go = "GonsalesB_3_9";
		break;
		
		case "GonsalesB_3_5":
			dialog.text = "알았어, 알았다고, 벌써 가고 있어! 수색 잘 하라고, 찰리 프린스!";
			link.l1 = "...";
			link.l1.go = "GonsalesB_3_6";
		break;
		
		case "GonsalesB_3_6":
			AddMoneyToCharacter(pchar, -10000);
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 20.0);
			npchar.lifeday = 0;
			AddQuestRecord("Saga", "191");
			pchar.questTemp.Saga = "ortega";
			Saga_SetOrtega();
		break;
		
		case "GonsalesB_3_7":
			dialog.text = "경비병들! 경비병들!!! 샤를리 프린스다!!!";
			link.l1 = "이 자식아!";
			link.l1.go = "GonsalesB_3_8";
		break;
		
		case "GonsalesB_3_8":
			DialogExit();
			LAi_SetActorTypeNoGroup(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 20.0);
			LAi_group_AttackGroup("Spain_citizens", LAI_GROUP_PLAYER);
			npchar.lifeday = 0;
			AddQuestRecord("Saga", "192");
			pchar.questTemp.Saga = "ortega";
			Saga_SetOrtega(); 
		break;
		
		case "GonsalesB_3_9":
			dialog.text = "내가 네 선원으로 들어가라는 말이냐?";
			link.l1 = "정확해. 하지만 이건 단 한 번뿐인 제안이야. 자, 어쩔래? 동의할 거야, 아니면 네 배를 갈라버릴 거다. 네가 그렇게 쉽게 찰리 프린스를 협박할 수 있다고 진짜 생각하는 건 아니겠지?";
			link.l1.go = "GonsalesB_3_10";
		break;
		
		case "GonsalesB_3_10":
			if(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > 34 && makeint(pchar.reputation.nobility) < 48)
			{
				dialog.text = "악마 같은 놈! 찰리 프린스 네가 직접 내게 선원 자리를 제안하다니! 젠장, 받아들이겠다! 내 칼이랑 만 페소 돌려줘. 이렇게 될 줄은 꿈에도 몰랐지!";
				link.l1 = "여기 있어. 그리고 입 다물어라. 이 도시에서 내가 누군지 아무도 알 필요 없어, 알겠지?";
				link.l1.go = "GonsalesB_3_11";
				break;
			}
			if(makeint(pchar.reputation.nobility) > 47)
			{
				dialog.text = "아니. 너 선장질은 제법 하는 것 같은데, 내 보기엔 너무 꽉 막혔어. 그래, 한때 카르타헤나에서 대담한 습격을 벌여 스페인 놈들 간담을 서늘하게 하긴 했지. 하지만 그건 전부 마커스 타이렉스 덕분이었잖아. 너 혼자 힘으론 제대로 약탈할 배짱도 없으면서. 그러니 돈이나 내놔!";
			}
			if(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 35)
			{
				dialog.text = "아니. 너야 악명 높은 해적이긴 한데, 선장으로서는 별로 대단해 보이지 않아. 마커스 타이렉스의 도움 덕분에 겨우 식민지를 약탈한 거잖아 – 너 혼자였으면 낡은 슬루프에도 감히 올라타지 못했을 거다. 그러니까 돈이나 내놔!\n";
			}
			if (sti(pchar.money) >= 10000)
			{
				link.l1 = "젠장, 만 달러 가져가서 내 눈앞에서 꺼져! 그리고, 다시는 내 앞에 나타나지 마라, 제발.";
				link.l1.go = "GonsalesB_3_5";
			}
			link.l2 = "이제 됐다, 더는 못 참겠다. 네 무기는 내 손에 있으니, 넌 이제 끝장이야, 이 쓰레기야.";
			link.l2.go = "GonsalesB_3_7";
		break;
		
		case "GonsalesB_3_11":
			dialog.text = "알겠소, 내가 바보는 아니오.";
			link.l1 = "좋아.";
			link.l1.go = "GonsalesB_3_12";
		break;
		
		case "GonsalesB_3_12":
			DialogExit();
			AddMoneyToCharacter(pchar, -10000);
			LAi_RemoveLoginTime(npchar);
			npchar.quest.OfficerPrice = 3000;
			npchar.reputation.nobility = 30;
			npchar.dialog.FileName = "Enc_Officer_dialog.c";
			npchar.loyality = MAX_LOYALITY;
			GiveItem2Character(npchar, "blade_10");
			EquipCharacterByItem(npchar, "blade_10");
			TakeItemFromCharacter(pchar, "blade_10");
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(npchar.id);
			AddQuestRecord("Saga", "193");
			pchar.questTemp.Saga = "ortega";
			Saga_SetOrtega(); 
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
		break;
		// <-- участвовал в событиях Картахены
		
		//настоящий Гонсалес - Ортега, маяк
		case "Ortega":
			dialog.text = "나는 오늘도, 그리고 앞으로도 손님을 받을 생각이 없네. 무슨 일로 왔나?";
			link.l1 = "안녕, 교수형 집행인. 숲의 악마가 나를 보냈어. 내가 잭맨 놈들보다 먼저 널 찾아서 다행이군. 그의 부하들이 카리브 해 전역에서 널 찾고 있어. 운이 좋았지, 헨리. 네가 어디서 태어났는지 아는 건 스벤손뿐이야. 그가 나더러 너에게 경고하라고 했어.";
			link.l1.go = "Ortega_1";
		break;
		
		case "Ortega_1":
			dialog.text = "이제 알겠군... 그러니까, 스벤손이 아직 살아 있고 옛 친구를 잊지 않았다는 말이로군. 내가 그를 처음 봤을 때, 그가 망가진 브리그 갑판 위에 서 있던 풋내기였을 때부터 많은 피가 흘렀지... 인생이 너무 빨리 지나가 버렸고, 내게 남은 시간도 많지 않네\n나는 이 황무지에서, 인간들과 멀리 떨어져 바다 가까이에서 자연사하고 싶었네. 하지만 잭맨이 카리브로 돌아왔다면, 날 가만두지 않겠지. 내 잘못은 아니었지만, 그의 주인에게 빚이 있지. 어쨌든, 지금 누가 내 말을 믿겠나.\n나는 죽음이 아니라 고통이 두렵네. 그리고 잭맨은 고통에 대해 아주 잘 알지. 그 생각만 해도 가슴이 멎고, 모든 것이 어두워지는구나.";
			link.l1 = "도살자는 이십 년 전에 교수형당했으니, 이제 누구에게도 빚을 갚을 필요 없어. 잭맨이 무섭다면 네 빚을 나한테 넘겨도 돼. 어차피 조만간 그를 만나게 될 거라고 생각하거든.";
			link.l1.go = "Ortega_2";
		break;
		
		case "Ortega_2":
			dialog.text = "도살자 같은 자를 교수형에 처하는 건 쉽지 않지. 세인트 존스의 전직 형리라면 지옥에서 돌아온 시체들에 관한 흥미로운 이야기를 많이 들려줄 수 있을 거야.\n그리고 야곱은 그의 선장에게 제대로 배웠으니, 내가 누구를 더 두려워해야 할지 모르겠군.";
			link.l1 = "잭맨이 너를 왜 필요로 하지?";
			link.l1.go = "Ortega_3";
		break;
		
		case "Ortega_3":
			dialog.text = "나는 도살장의 딸을 안전하게 지켜준 대가로 금을 한 과부에게 전달해야 했어. 왜 그런 눈으로 나를 보는 거지? 그래, 그 애는 '넵튠'호가 침몰하기 얼마 전에 태어났어. 그는 제때 돌아와서 딸을 데려갈 수 없었고, 그래서 나에게 아기와 보모를 돌보라고 시킨 거야.";
			link.l1 = "관리인의 이름이 글래디스 챈들러였나?";
			link.l1.go = "Ortega_4";
		break;
		
		case "Ortega_4":
			dialog.text = "바보 짓 그만해. 잭맨이 날 찾는다면, 그건 그가 도살업자의 딸이 필요해서지. 그는 이미 벨리즈 출신의 글래디스라는 여자와 그녀가 기른 아이를 찾고 있다는 걸 너도 알고 있을 거야. 솔직하게 말해. 그러면 너를 믿어줄 수도 있겠지.";
			link.l1 = "글래디스에게 무슨 말을 전하라고 했지?";
			link.l1.go = "Ortega_5";
		break;
		
		case "Ortega_5":
			dialog.text = "아무것도 아니야. 내가 그녀에게 도살업자의 반지를 보여주기로 되어 있었지, 그래야만 내가 선장님이 보낸 심부름꾼이라는 걸 알 수 있었거든. 또 아기에게 필요한 걸 위해 더블룬 상자도 건네줘야 했고. 그 반지를 손에 넣으려면 어떤 개자식을 죽여야 했어. 그래서 앤티과에 한 달이나 더 머물러야 했지.\n마침내 벨리즈에 도착했을 때는 글래디스는 이미 떠나고, 도시는 스페인 놈들에게 불타고 약탈당한 뒤였어. 그녀는 집을 팔고 새 애인, 그리고 아기 헬렌과 함께 도망쳤지. 부디 그녀가 헬렌을 잘 돌보고, 그 아이를 집시나 창녀촌에 팔지 않았길 바란다.";
			link.l1 = "도살업자의 딸 이름이 헬렌이었지, 맞아?";
			link.l1.go = "Ortega_6";
		break;
		
		case "Ortega_6":
			dialog.text = "정확히 그래. 도살자의 어머니를 기리는 거지. 만약 산 자의 죽은 자와 해적들이 죽은 눈으로 널 쳐다보는 게 두렵지 않다면, 반지랑 금을 줄 수 있어. 난 한 번도 손대지 않았어. 굶어 죽을 지경이었지만, 건드리지 않았지. 네 마음대로 해. 그리고 대신 나는 너에게 \n";
			link.l1 = "무슨 일이야, 헨리?!";
			link.l1.go = "Ortega_7";
		break;
		
		case "Ortega_7":
			dialog.text = "너... 너... 나... 묻... 어, 어이!";
			link.l1 = "안 돼!";
			link.l1.go = "Ortega_8";
		break;
		
		case "Ortega_8":
			DialogExit();
			LAi_SetImmortal(npchar, false);
			LAi_KillCharacter(npchar);
			AddQuestRecord("Saga", "20");
			pchar.questTemp.Saga = "svenson1";
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "chest");
			GiveItem2Character(pchar, "bucher_ring"); //перстень Бучера
			//таймер на возврат смотрителя
			SetFunctionTimerCondition("Saga_LightmanReturn", 0, 0, 10, false);
			//ставим прерывания, если ГГ наследил в городе
			if (CheckAttribute(pchar, "questTemp.Saga.Trap"))
			{
				pchar.quest.Saga_Trap.win_condition.l1 = "location";
				pchar.quest.Saga_Trap.win_condition.l1.location = "Mayak11";
				pchar.quest.Saga_Trap.function = "Saga_CreateTrapBandos";
				TraderHunterOnMap(true);
			}
			AddCharacterExpToSkill(pchar, "Sneak", 50);//скрытность
			
			DeleteAttribute(pchar, "questTemp.HelenDrinking.Dialogs");
			//pchar.questTemp.HelenDrinking = "end_henry";
		break;
		
		//бандиты в поисках Гонсалеса, маяк
		case "saga_trap":
			dialog.text = "아-아, 저기 우리 호기심 많은 친구가 있군! 결국 곤살레스를 찾았나? 잘했어, 네 덕에 우리가 그를 찾았지... 이제 넌 필요 없어. 얘들아, 이 광대 놈을 죽여라!";
			link.l1 = "죽을 때다, 게 내장들아!";
			link.l1.go = "saga_trap_1";
		break;
		
		case "saga_trap_1":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			int n = makeint(MOD_SKILL_ENEMY_RATE/3);
			for (i=1; i<=3+n; i++)
			{	
				sld = characterFromId("sagatrap_sold_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		//<-- поиск Гонсалеса, Картахена
		
//--------------------------------------------НПС по квесту Возвращение барона---------------------------------
		
		// доминиканский вождь
		case "DominicaHead":
			dialog.text = "우아! 우아! 위대한 쿠쿨칸께서 새로운 희생자를 요구하신다! 오에! 과거의 강력한 전사의 혼이 우리 마을에 와서 위대한 쿠쿨칸께 제물로 바쳐지려 한다! 오에! 모두들 강력한 전사 혼에게 절하라!";
			link.l1 = "(희미하게) 젠장, 여기가 어디지?";
			link.l1.go = "DominicaHead_1";
			NextDiag.TempNode = "DominicaHead";
			if (CheckCharacterItem(pchar, "Ultimate_potion"))
			{
				pchar.systeminfo.NoNotifications = true;
				RemoveItems(pchar, "Ultimate_potion", 1);
				DeleteAttribute(pchar,"systeminfo.NoNotifications");
				notification("A Comanche potion is used", "None");
				LAi_SetCurHPMax(PChar);
				AddCharacterHealth(pchar, 50);
				DeleteAttribute(pchar, "chr_ai.poison");
				notification("You are feeling that your health is restored!", "None");
				//Log_Info("A Comanche potion is used");
				//Log_Info("You are feeling that your health is restored!");
				//PlaySound("Ambient\Tavern\glotok_001.wav");
				PlaySound("Ambient\Horror\Fear_breath_01.wav");
			}
		break;
		
		case "DominicaHead_1":
			dialog.text = "오-에! 위대한 전사가 위대한 쿠쿨칸에게 잡아먹히길 원하네! 해가 떠오르고, 그림자가 짧아진다! 곧 위대한 쿠쿨칸이 깨어날 것이네! 우리가 그분께 널 데려가리라, 오 위대한 전사여, 그러면 너는 조상들의 땅을 계속 지나가게 될 것이야!\n";
			link.l1 = "(희미하게) 말도 안 돼... 또 쿠쿨칸이라고? 이봐, 추장, 난 평화롭게 왔어! 나는 여기서...";
			link.l1.go = "DominicaHead_2";
		break;
		
		case "DominicaHead_2":
			dialog.text = "오-에! 위대한 전사가 즉시 쿠쿨칸에게 제물로 바쳐지길 원한다고 말한다. 오, 위대한 전사여! 우리는 지금 쿠쿨칸에게 가서 그분의 오심을 기다린다! 전사들이여! 조상의 영혼을 쿠쿨칸에게 데려가는 것은 우리에게 큰 영광이다!";
			link.l1 = "(희미하게) 바보 같으니라고... 좋아, 저놈들이랑 같이 가야겠군. 아직 나를 공격하지 않은 게 다행이야, 이 꼴로는 도저히 스스로를 지킬 수 없을 테니까...";
			link.l1.go = "DominicaHead_3";
		break;
		
		case "DominicaHead_3":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "reload", "reload1_back", "Saga_DominicaDollyReload", -1);
			LAi_ActorFollow(pchar, npchar, "", -1);
			for (i=2; i<=10; i++)
			{
				sld = characterFromId("Dominica_ind_"+i);
				LAi_SetActorType(sld);
				LAi_ActorFollow(sld, npchar, "", -1);
			}
		break;
		
		case "DominicaHead_4":
			dialog.text = "우리는 쿠쿨칸, 위대한 조상 영혼께 나아간다. 곧 해가 지고, 그림자가 길어지면 쿠쿨칸께서 우리를 찾아오실 것이다. 기다리라, 위대한 전사여...";
			link.l1 = "(희미하게) 이제야 알겠군, 인디언 전쟁 족장...";
			link.l1.go = "DominicaHead_5";
		break;
		
		case "DominicaHead_5":
			DialogExit();
			bDisableCharacterMenu = true;//лочим Ф2
			AddQuestRecord("BaronReturn", "7");
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("Saga_DominicaDollyWait", 5.0);
			pchar.questTemp.Saga.BaronReturn = "third_teleport";
		break;
		
		case "DominicaHead_6":
			dialog.text = "쿠쿨칸이 살아 있다! 쿠쿨칸이 우리와 함께한다! 위대한 전사를 쿠쿨칸에게 제물로 바칠 수 있다! 전사들이여, 위대한 조상 신령 앞에 머리를 숙여라!";
			link.l1 = "(희미하게) 비켜요, 우두머리. 내가 직접 할게. 처음 하는 것도 아니니까...";
			link.l1.go = "DominicaHead_7";
		break;
		
		case "DominicaHead_7":
			DialogExit();
			bDisableCharacterMenu = false;//разлочим Ф2
			AddQuestRecord("BaronReturn", "8");
			for (i=2; i<=10; i++)
			{
				sld = characterFromId("Dominica_ind_"+i);
				LAi_SetActorType(sld);
			}
		break;
		
//----------------------------------------НПС по квесту Искушение Барбазона----------------------------------
		// капитан рыболовного баркаса, стыривший шелк, море
		case "BarbCapBarkas":
			dialog.text = "무엇을 도와드릴까요, 나리?";
			link.l1 = "그래, 그래... 이봐, 친구, 여기서 뭐 하고 있는 거야?";
			link.l1.go = "BarbCapBarkas_1";
		break;
		
		case "BarbCapBarkas_1":
			dialog.text = "내가 여기서 뭐 하고 있냐고? 난 어부고, 여기서 낚시하고 있지. 그런데 대체 왜 이런 말투로 나한테 캐묻는 거야?";
			link.l1 = "나한테 거짓말하지 마, 이 친구야. 네가 정말 어부일 수도 있겠지만, 여기서 낚시한 건 아니잖아. 값비싼 선박용 비단이 바로 이 자리에서 바다에 버려졌거든. 그리고 네가 여기 있다는 것 자체가 내 눈엔 꽤 수상해 보여.";
			link.l1.go = "BarbCapBarkas_2";
		break;
		
		case "BarbCapBarkas_2":
			dialog.text = "무슨 헛소리야? 무슨 비단을 말하는 거지?";
			link.l1 = "무슨 비단이냐고? 중국산 비단 말이다... 바보짓 그만해라! 이제 내 말 잘 들어. 당장 네 화물칸에서 비단을 꺼내서 내놓든가, 아니면 내가 직접 가져가겠다. 하지만 먼저, 내 승선조가 너랑 네 선원들을 처리할 거다. 자, 어쩔래? 내 부하들을 부를까?\n";
			link.l1.go = "BarbCapBarkas_3";
		break;
		
		case "BarbCapBarkas_3":
			dialog.text = "안 돼요! 나리, 몰랐어요... 그 짐짝들이 그냥 떠다니길래, 그래서 제가 그냥...";
			link.l1 = "비단을 내 배로 가져와라. 서둘러!";
			link.l1.go = "BarbCapBarkas_4";
		break;
		
		case "BarbCapBarkas_4":
			dialog.text = "그래, 그래, 물론이지. 당장 그렇게 하겠네, 제발 내 배만은 가져가지 마!";
			link.l1 = "엉덩이 좀 움직여! 나 시간 별로 없어...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Saga_BarbBarkasSilk");
		break;
		
		case "BarbCapBarkas_5":
			dialog.text = "여기, 우리가 찾은 건 전부 가져왔어 - 아홉 개의 짐 모두야. 이게 전부야, 맹세해...";
			link.l1 = "좋아. 계속 낚시해도 되지만, 앞으로는 남의 물건에 눈독 들이지 마라!";
			link.l1.go = "BarbCapBarkas_6";
		break;
		
		case "BarbCapBarkas_6":
			DialogExit();
			npchar.DontDeskTalk = true;
			npchar.lifeday = 0;
			LAi_SetStayType(npchar);
			pchar.quest.BarbBarkas_Sink.over = "yes"; //снять прерывание
			pchar.quest.BarbBarkas_Abordage.over = "yes"; //снять прерывание
			NextDiag.CurrentNode = "BarbCapBarkas_7";
			AddQuestRecord("BarbTemptation", "6");
			pchar.questTemp.Saga.BarbTemptation = "give_silk";
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 50);//скрытность
		break;
		
		case "BarbCapBarkas_7":
			dialog.text = "이미 원하는 건 가져갔잖아. 난 더 이상 아무것도 없어! 또 뭘 바라는 거야?";
			link.l1 = "진정해, 친구. 난 간다.";
			link.l1.go = "exit";
			NextDiag.TempNode = "BarbCapBarkas_7";
		break;
		
		// Моррель, капитан потопленного судна, тюрьма
		case "Morelle":
			dialog.text = "바르바종이 보냈다면, 그에게 전해라. 나는 스스로 감옥을 나가고 싶지 않다고. 차라리 재판을 기다리겠다. 네덜란드 밧줄이 목에 감기는 게, 그 자의 친절보다 낫지.";
			link.l1 = "김칫국부터 마시지 마라. 네 항해사가 자크에게 네가 죽었다고 말했다. 자크가 네가 바다에 던진 비단을 찾으라고 나를 보냈다. 네 브리건틴에 비단이 얼마나 있었지?";
			link.l1.go = "Morelle_1";
		break;
		
		case "Morelle_1":
			dialog.text = "내 잘못이었어, 젠장. 사환이 바르바종에게 가져갈 비단 아홉 꾸러미를 가져왔지. 내가 그를 쫓으라고 명령했어. 그가 소란을 피워서, 우리는 그의 목을 따야 했지. 그런데 그의 은닉처에 비단 세 꾸러미가 더 있었어. 그걸 내가 챙겨서 내 은닉처에 숨겼지. 하지만 우리가 원치 않는 관심을 끈 것 같아.\n놈들이 금방 우리를 찾아냈고, 네덜란드 순찰대가 공해상에서 '솔트 도그'를 기다리고 있었어. 도망치지 못했지. 네가 바르바종에게 내 얘기만 안 하면 그 비단은 가져도 돼. 은닉처는 그랑 카스 해변, 막다른 곳 근처 바위 사이야. 내가 다시 쓸 일은 없을 것 같으니까.";
			link.l1 = "좋아. 바르바종에게 네가 아직 살아 있다는 건 말하지 않겠다. 그에 대한 소문이 사실이라면, 네가 네덜란드 놈들에게 목매달리는 게 차라리 나을 거다. 아니면 운이 좋으면 강제 노역형을 받을지도 모르지.";
			link.l1.go = "Morelle_2";
		break;
		
		case "Morelle_2":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			// тайник - модель
			//int m = Findlocation("Shore40");
			//locations[m].models.always.Roll = "Roll_of_rolls";
			//Locations[m].models.always.Roll.locator.group = "quest";
			//Locations[m].models.always.Roll.locator.name = "quest1";
			pchar.quest.Saga_MorelGoods.win_condition.l1 = "locator";
			pchar.quest.Saga_MorelGoods.win_condition.l1.location = "Shore40";
			pchar.quest.Saga_MorelGoods.win_condition.l1.locator_group = "quest";
			pchar.quest.Saga_MorelGoods.win_condition.l1.locator = "quest1";
			pchar.quest.Saga_MorelGoods.function = "Saga_SetMorelGoods";
			AddCharacterExpToSkill(pchar, "Fortune", 200);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 200);//скрытность
		break;
		
		// Валет, брат Джекмана в Капстервиле
		case "valet":
			dialog.text = "나는 흰상어 사냥이 언제 시작되는지 아는 남자를 기다리고 있다.";
			link.l1 = "사냥이 시작되었다.";
			link.l1.go = "valet_1";
		break;
		
		case "valet_1":
			dialog.text = "드디어군! 이제 잘 들어라. 너는 라 베가에 있는 마르쿠스 타이렉스를 찾아가서, 브리건틴 '세퍼레이터'가 터크스 섬 근처에서 공격을 받아 지금은 남쪽 만에 숨어 있다고 전해야 한다. 선장은 중상을 입었고, 선원들은 도움을 기다리고 있다. 너는 '세퍼레이터'에서 한 선원을 데려왔고, 그가 모든 걸 말해줬다. 그는 지금 죽었다. 네가 아는 건 이게 전부다. 알겠나?";
			link.l1 = "그 일에 왜 내가 필요한 거지? 겨우 그거 하려고 내가 이렇게 오래 기다렸단 말이야...";
			link.l1.go = "valet_2";
		break;
		
		case "valet_2":
			dialog.text = "너는 네 일만 하고 질문하지 말라고 돈을 받고 있지. 하지만 네 말도 맞아. 미리 경고하겠는데, 타이렉스는 네가 진실을 말하는지 확신할 때까지 널 보내주지 않을 거다. 하지만 모든 걸 알아내면 넉넉하게 보상해줄 거야. 물론 그럴 수 있다면 말이지...";
			link.l1 = "나한테 눈속임을 하는군, 나리... 왜 직접 그의 감사를 받으려 하지 않는 거지?";
			link.l1.go = "valet_3";
		break;
		
		case "valet_3":
			dialog.text = "카람바! 네 쓸데없는 호기심이 마음에 안 들어! 그렇게 떠들다간 언젠가 일찍 무덤에 들어가게 될 거다.";
			link.l1 = "그래, 가끔 나도 참을 수 없을 때가 있지. 특히 누가 나한테 사기 치려는 게 보일 때 말이야. 아니, 이 친구야, 이제부터는 내 규칙대로 할 거다. 네 주인이 누구냐, 젠장? 대답해, 아니면 내가 억지로 말하게 해주지!";
			link.l1.go = "valet_4";
		break;
		
		case "valet_4":
			dialog.text = "너... 이 개자식아! 바르바종이 이 일에 대해 반드시 복수할 거다, 그리고 네 목숨도 끝장날 거야, 똥이나 처먹는 놈아!";
			link.l1 = "하! 이럴 줄 알았다. 준비해라, 악당 놈!";
			link.l1.go = "valet_5";
		break;
		
		case "valet_5":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Saga_ValetDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "vensan":
			// Addon 2016-1 Jason пиратская линейка патч 17/1
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "full_complete_end")
			{
				dialog.text = "찰리 프린스? 여기서 뭐 하는 거야? 아-악, 젠장, 너였구나! 이게 다 네 짓이었어!";
				link.l1 = "진정해, 버니. 나는 네 편이야. 매복은 제거됐고, 너와 네 배는 이제 안전해.";
				link.l1.go = "vensan_8";
			}
			else
			{
				dialog.text = "너 누구야, 젠장? 어떻게 여기까지 온 거지? 당장 나가, 내 배에는 폭약이 설치돼 있고, 저 해안에 있는 놈들이 한 방이면 터뜨릴 수 있어.";
				link.l1 = "걱정 마시오, 나리. 해안의 매복은 처리했소. 갑판에서 파이프만 피우지 않는다면, 당신 배는 이제 안전하오. 이름이 무엇이오?";
				link.l1.go = "vensan_1";
			}
		break;
		
		case "vensan_1":
			dialog.text = "뱅상. 베르나르 뱅상. 그런데 너 이름이 뭐지?";
			link.l1 = "Captain "+GetFullName(pchar)+"... 내가 그 밧줄을 끊고 널 자유롭게 해주겠어...";
			link.l1.go = "vensan_2";
		break;
		
		case "vensan_2":
			LAi_SetStayType(npchar);
			dialog.text = "오... 정말 감사드립니다. 어떻게 보답해야 할지 모르겠군요.";
			link.l1 = "아직 끝나지 않았소, 나리. 당신 선원 중에 아직 살아 있는 자가 있소?";
			link.l1.go = "vensan_3";
		break;
		
		case "vensan_3":
			dialog.text = "내 부하 서른여섯 명이 화물창에 갇혀 있어...";
			link.l1 = "놈들을 풀어주고 당장 여기서 꺼져. ";
			link.l1.go = "vensan_4";
		break;
		
		case "vensan_4":
			dialog.text = "하지만...";
			link.l1 = "시간 낭비하지 마, 베르나르. 감사 인사는 라 베가에서 해도 돼... 티렉스도 나한테 고마워할지 모르지.";
			link.l1.go = "vensan_5";
		break;
		
		case "vensan_5":
			dialog.text = "그래서, 일부러 온 거였어? 다 알고 있었던 거야?";
			link.l1 = "그래, 알고 있었지. 내가 잭맨의 계략과 마커스를 죽이려는 계획을 밝혀냈어. 아, 타이렉스에게 가만히 있으라고 해. 괜히 끼어들다가 잭맨이 도망칠지도 몰라.";
			link.l1.go = "vensan_6";
		break;
		
		case "vensan_6":
			dialog.text = "반드시 전하겠어요! 이제 떠나시는 건가요?";
			link.l1 = "그래. 그리고 너도 서둘러야 해.";
			link.l1.go = "vensan_7";
		break;
		
		case "vensan_7":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "goto", "goto2", "none", "", "", "", 5.0);
			Ship_SetTaskRunaway(SECONDARY_TASK, GetCharacterIndex("Cap_Vensan"), GetMainCharacterIndex());
			pchar.questTemp.Saga.BarbTemptation.Vensan_free = "true";
			if (!CheckAttribute(pchar, "questTemp.Saga.BarbTemptation.vensan_attack"))
			{
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sld = characterFromId("Mary");
				else sld = characterFromId("Helena");
				sld.dialog.currentnode = "sea_bomb"; 
				LAi_SetActorType(sld);
				ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto6");
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			}
			AddCharacterExpToSkill(pchar, "Leadership", 100);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 50);//скрытность
			sld = characterFromId("Cap_Vensan");
			sld.lifeday = 1;
			sld.DontDeskTalk = true;
		break;
		
		// Addon 2016-1 Jason пиратская линейка патч 17/1
		case "vensan_8":
			dialog.text = "정말이야? 미안해, 형...";
			link.l1 = "잊어버려. 그냥 내가 밧줄을 끊고 널 풀어줄게.";
			link.l1.go = "vensan_9";
		break;
		
		case "vensan_9":
			LAi_SetStayType(npchar);
			dialog.text = "젠장... 손이 안 느껴져...";
			link.l1 = "버니, 배에 살아남은 사람이 더 있나?";
			link.l1.go = "vensan_10";
		break;
		
		case "vensan_10":
			dialog.text = "삼십 명이 화물창에 갇혀 있어...";
			link.l1 = "놈들을 풀어주고 당장 여기서 꺼져. 지금 당장!";
			link.l1.go = "vensan_11";
		break;
		
		case "vensan_11":
			dialog.text = "하지만...";
			link.l1 = "즉시 라 베가로 항해하라. 마르쿠스에게 이 혼란에 대해 모든 것을 빠짐없이 전하라.";
			link.l1.go = "vensan_12";
		break;
		
		case "vensan_12":
			dialog.text = "마르쿠스가 너를 보냈냐?";
			link.l1 = "그렇지 않아. 내가 어떤 놈의 음모를 밝혀냈지. 그 자가 이 계략으로 마르쿠스를 제거하려 했어. 마르쿠스에게는 당분간 가만히 있으라고, 지금은 끼어들지 말라고 전해 줘... 나중에 내가 직접 모든 걸 설명할 테니. 그리고 제발 나한테 화내는 것도 그만두라고 전해 줘.";
			link.l1.go = "vensan_7";
		break;
		
 //--------------------------------------НПС по Завещанию Шарпа--------------------------------------------------
		// Устрица, Поль Моллиган
		case "molligan":
			dialog.text = "내 배에서 뭘 원하는 거요, 나리?";
			link.l1 = "좋은 하루네, 폴. 자네 이름이 폴 몰리건 맞지?";
			link.l1.go = "molligan_0";
		break;
		
		case "molligan_0":
			dialog.text = "그래, 나야. 무엇을 도와줄까?";
			link.l1 = "내 이름은 "+GetFullName(pchar)+" 그리고 얀 스벤손이 나를 보냈소.";
			link.l1.go = "molligan_1";
		break;
		
		case "molligan_1":
			dialog.text = "얀? 아-아, 기억나. 물론이지! 요즘 그의 집에 자주 들르더군. 그래서, 얀이 나한테 뭘 원하지?";
			link.l1 = "너는 그렇게 급하게 블루웰드에서 떠나려고 했지. 얀은 네 배에 마호가니 200센트너를 더 실어서 브리지타운의 윌러비 경에게 가져다주길 원했어. 배를 준비해라, 내 사람들이 마호가니를 네 화물창에 실어줄 테니.";
			link.l1.go = "molligan_2";
		break;
		
		case "molligan_2":
			dialog.text = "마호가니라고? 얀이 그렇게 말했나? 흠. 그런데 왜 자네가 직접 바베이도스로 가져가지 않고 나한테 시키는 거지?";
			link.l1 = "네가 그리로 항해하고 나는 아니기 때문이야. 나는 스벤손에게서 급한 임무를 받았으니 브리지타운까지 항해하며 시간을 낭비할 수 없어. 게다가 얀은 내가 윌러비 경과 거래하는 걸 믿지 않으니 네가 맡아주길 바라고 있어. 미안하다. 이제 짐을 싣자, 나는 가봐야 해.";
			link.l1.go = "molligan_3";
		break;
		
		case "molligan_3":
			dialog.text = "이봐, 내 화물칸에 빈 공간이 하나도 없어. 나도 야네 부탁을 들어주고 싶지만, 지금은 할 수 없겠어.";
			link.l1 = "방이 없다고? 이상하네... 얀은 빈자리가 있다고 했는데.";
			link.l1.go = "molligan_4";
		break;
		
		case "molligan_4":
			dialog.text = "맞아, 하지만 얀은 내가 '오이스터'에 더 무거운 대포를 장착한 걸 몰랐지. 지금 실은 것보다 더 이상 화물을 실을 수가 없어. 그러니 나무는 네가 직접 바베이도스로 가져가, 친구? 얀에게 내가 못 했다고 전해 줘. 윌러비 상대하는 건 쉽지: 그냥 만나서 화물 주고 영수증 받으면 돼. 간단하잖아.";
			link.l1 = "흠. 이건 내 계획이 아니었는데... 자, 화물창을 확인해 볼까? 내 선임 사관이 짐 싸는 데 아주 능숙해서, 네 화물창에 물건을 다 실어도 공간이 좀 남을 거야...";
			link.l1.go = "molligan_5";
		break;
		
		case "molligan_5":
			dialog.text = "이봐, 더 이상 물건을 실을 수 없어. 내가 대포를 버리고 '오이스터'를 무방비로 두길 바라는 거야?";
			link.l1 = "글쎄, 그렇게 확신한다면야... 하지만 얀은 좋아하지 않을 테니, 그 점 명심해!";
			link.l1.go = "molligan_6";
		break;
		
		case "molligan_6":
			dialog.text = "스벤손에게 내가 설명할 테니 걱정 마. 결국 이건 그 녀석 잘못이야—내 배의 톤수에 대해 물어보지도 않았으니까.";
			link.l1 = "에이, 이제 저 통나무들을 바르바도스까지 실어 나르며 항해해야 하잖아, 젠장... 잘 가라, 친구.";
			link.l1.go = "molligan_7";
		break;
		
		case "molligan_7":
			DialogExit();
			// ставим проверку скрытности
			if (GetSummonSkillFromName(pchar, SKILL_SNEAK) > (10+hrand(50)))
			{
				pchar.questTemp.Saga.Molligan.friend = "true"; // будет шанс критического залпа картечью
				sTemp = "The scoundrel is still not suspecting a thing. I should get closer and shoot at him with grapeshot. A sudden strike will always win in any battle. ";
				log_Testinfo("Friends");
				AddCharacterExpToSkill(pchar, "Fortune", 200);//везение
				AddCharacterExpToSkill(pchar, "Sneak", 300);//скрытность
			}
			else
			{
				pchar.questTemp.Saga.Molligan.enemy = "true"; // нападет
				sTemp = "";
				log_Testinfo("Enemies");
				AddCharacterExpToSkill(pchar, "Sneak", 150);//скрытность
			}
			AddQuestRecord("Testament", "7");
			AddQuestUserData("Saga", "sText", sTemp);
			NextDiag.CurrentNode = "molligan_8";
			npchar.DontDeskTalk = true; // patch-5
		break;
		
		case "molligan_8":
			dialog.text = "우리 서로 이해한 거 맞지?";
			link.l1 = "그래, 그래. 나는 내 배로 가고 있다.";
			link.l1.go = "exit";
			NextDiag.TempNode = "molligan_8";
		break;
		
	//-----------------------------------------НПС по Теням прошлого--------------------------------------------
		// Джим Бенсон, плешивая мэгги
		case "benson":
			dialog.text = "나한테 뭘 원하지? 나는 소문이나 도박 따위엔 관심 없어. 럼도 혼자 마신다. 게다가 지난 항해 이후로 기분이 아주 더럽거든.";
			link.l1 = "지난 항해에서 무슨 특별한 일이 있었소?";
			link.l1.go = "benson_1";
		break;
		
		case "benson_1":
			dialog.text = "좋은 사람 한 명이 나를 믿었는데, 내 선원들이 요구해서 내가 그를 바다에 던져버렸지.";
			link.l1 = "그의 죄가 무엇이었소?";
			link.l1.go = "benson_2";
		break;
		
		case "benson_2":
			dialog.text = "나는 신참이라 여기 아는 사람이 별로 없어. 그래서 그 마음씨 좋은 뚱보를 과거도 모르고 외과의로 고용했지. 우리가 바베이도스를 떠난 뒤로 해적들이 줄곧 쫓아왔어. 대체 왜 내 달걀껍데기를 노리는 거지?\n강풍 덕분에 간신히 도망쳤어. 그 기념으로 한잔 했지. 그런데 그 멍청한 뚱보는 해적들이 자기 때문에 쫓아온 거라고, 자기가 전직 사형집행인이라 남들이 몰라야 할 걸 안다고 모두에게 떠벌렸지 뭐야.\n당연히 선원들이 엄청 화가 났지. 아니, 진짜?! 사형집행인이 외과의로 배에 타 있다니! 해적이랑 엮이고 싶은 사람도 없었고... 그래서 불쌍한 놈을 뭍에 내려놓을 수밖에 없었어. 다 그놈 입 때문이지. 그래도 촌놈이 안쓰럽긴 해, 정말 뛰어난 의사였거든. 내 숙취도 순식간에 고쳐줬으니까.";
			link.l1 = "젠장! 네 의사 이름이 레이먼드 베이커 맞지?";
			link.l1.go = "benson_3";
		break;
		
		case "benson_3":
			dialog.text = "그래. 맞아. 그런데 어떻게 알았지? 나를 따라온 거야?";
			link.l1 = "아니, 그건 내가 아니야. 난 저 사람이 필요할 뿐이야, 그는 훌륭한 의사거든. 어디에 그를 상륙시켰지?";
			link.l1.go = "benson_4";
		break;
		
		case "benson_4":
			dialog.text = "북위 15도 28분, 서경 63도 28분. 서두르시오, 나리! 그가 아직 살아 있을 거요. 당신이 그를 구하면 내 누명도 벗겨질 테니!";
			link.l1 = "나는 이미 닻을 올리고 있다!";
			link.l1.go = "benson_5";
		break;
		
		case "benson_5":
			DialogExit();
			NextDiag.CurrentNode = "benson_6";
			AddQuestRecord("Shadows", "3");
			npchar.lifeday = 0;
			bQuestDisableMapEnter = false;
			pchar.quest.Saga_Shadows_Baker.win_condition.l1 = "location";
			pchar.quest.Saga_Shadows_Baker.win_condition.l1.location = "Dominica";
			pchar.quest.Saga_Shadows_Baker.function = "Saga_SetBakerBoat";
			DeleteAttribute(pchar, "Cheats.SeaTeleport");
		break;
		
		case "benson_6":
			dialog.text = "선장님, 서두르세요! 아직 살아 있을 거예요!";
			link.l1 = "그래, 그래, 지금 가고 있어...";
			link.l1.go = "exit";
			NextDiag.TempNode = "benson_6";
		break;
		
	//---------------------------------------бандиты у джекмановского рудника-------------------------------
		case "mine_bandit":
			locCameraFromToPos(6.21, 2.31, 8.46, true, -2.26, -1.10, 4.99);
			if (CheckAttribute(pchar, "questTemp.Saga.MineAttack"))
			{
				dialog.text = "이봐! 거기 그대로 있어! 움직이지 마. 이 구역은 우리가 장악했어!";
				link.l1 = "너무 심하게 굴지 마, 친구! 동료들! 잭맨이 우리를 보냈어. 우리는 광산에 가야 해. 주인님의 명령이야...";
				link.l1.go = "mine_attack";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "이봐! 거기 가만히 있어! 움직이지 마. 이 구역은 우리가 장악했어!";
				link.l1 = "흠. 하지만 나는 지나가고 싶은데... 도대체 왜 막는 거야?";
				link.l1.go = "mine_bandit_1";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "아, 또 너냐? 아직도 모르겠어... 얘들아, 쏴라!!";
				link.l1 = "...";
				link.l1.go = "mine_bandit_fire";
			}
		break;
		
		case "mine_bandit_0":
			dialog.text = "어서 가, 비켜!";
			link.l1 = "좋아...";
			link.l1.go = "exit";
			NextDiag.TempNode = "mine_bandit_0";
		break;
		
		case "mine_bandit_1":
			dialog.text = "내 뒤에 있는 광산은 사유지라서, 너 같은 낯선 자가 지나가지 못하게 막으러 여기 있는 거다. 돌아서서 이곳을 떠나는 게 좋을 거다, 이방인. 우리 대포는 산탄으로 장전되어 있으니, 한 발짝만 더 다가오면 너는 피범벅이 되어버릴 거다.";
			link.l1 = "헤, 알겠어. 네 광산은 경비가 삼엄하군. 좋아, 나 간다.";
			link.l1.go = "mine_bandit_exit";
			link.l2 = "이 자식아! 어디 두고 보자, 누가 바닥에 널브러지나!\n";
			link.l2.go = "mine_bandit_2";
		break;
		
		case "mine_bandit_exit":
			DialogExit();
			LAi_SetGuardianType(npchar);
			LAi_group_MoveCharacter(npchar, "PIRATE_CITIZENS");
			chrDisableReloadToLocation = false;//открыть локацию
			DoQuestReloadToLocation("Mine_02", "reload", "reload3", "");
		break;
		
		case "mine_bandit_2":
			dialog.text = "기회를 줬다... 이 녀석들아, 쏴라!!";
			link.l1 = "...";
			link.l1.go = "mine_bandit_fire";
		break;
		
		case "mine_bandit_fire":
			DialogExit();
			DoQuestCheckDelay("Saga_MineBanditsFire", 1.5);
		break;
		
		case "mine_banditx":
			locCameraFromToPos(6.21, 2.31, 8.46, true, -2.26, -1.10, 4.99);
			if (CheckAttribute(pchar, "questTemp.Saga.MineAttack"))
			{
				dialog.text = "이봐! 꺼져! 이 구역은 통제 중이야!";
				link.l1 = "이봐, 진정해, 친구! 잭맨이 우리를 보냈어. 우리는 광산에 가야 해. 주인님의 명령이야...";
				link.l1.go = "mine_attackx";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "이봐! 꺼져! 이 구역은 우리가 지키고 있어!";
				link.l1 = "흠. 거기에 뭐가 있는데?";
				link.l1.go = "mine_banditx_1";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "아, 또 너냐? 아직도 눈치 못 챘군... 얘들아, 쏴라!!";
				link.l1 = "...";
				link.l1.go = "mine_banditx_fire";
			}
		break;
		
		case "mine_banditx_1":
			dialog.text = "네 알 바 아니다. 꺼져라, 안 그러면 진짜 쏜다, 맹세코!";
			link.l1 = "진정하게. 나는 떠난다.";
			link.l1.go = "mine_banditx_exit";
			link.l2 = "이 자식아! 어디 누가 먼저 쏘나 두고 보자!";
			link.l2.go = "mine_banditx_2";
		break;
		
		case "mine_banditx_exit":
			DialogExit();
			LAi_SetGuardianType(npchar);
			LAi_group_MoveCharacter(npchar, "PIRATE_CITIZENS");
			DoQuestReloadToLocation("Mine_04", "reload", "reload3", "");
		break;
		
		case "mine_banditx_2":
			dialog.text = "기회를 줬다... 머스킷 준비! 쏴라!!";
			link.l1 = "...";
			link.l1.go = "mine_banditx_fire";
		break;
		
		case "mine_banditx_fire":
			DialogExit();
			DoQuestCheckDelay("Saga_MineBanditsxFire", 0.6);
		break;
		
		case "mine_attackx":
			dialog.text = "정말이야? 그럼 암호를 알고 있겠군. 말해 봐, 하지만 거짓말이면 후회하게 될 거다...";
			link.l1 = "Triton";
			link.l1.go = "mine_wrongx_password";
			link.l2 = "Neptune";
			link.l2.go = "mine_attackx_1";
			link.l3 = "Centurion";
			link.l3.go = "mine_wrongx_password";
			link.l4 = "Harpoon";
			link.l4.go = "mine_wrongx_password";
		break;
		
		case "mine_attackx_1":
			dialog.text = "맞아. 그런데 너, 이봐, 잘못된 쪽으로 왔구나. 아무도 경고 안 했냐? 돌아가서 마른 우물에서 왼쪽 길로 가. 그러고 언덕을 돌아가면 거기서 정문을 볼 수 있을 거야.";
			link.l1 = "여기 들어가면 안 돼?";
			link.l1.go = "mine_attackx_2";
		break;
		
		case "mine_wrongx_password":
			dialog.text = "이봐, 녀석들, 첩자가 있어! 머스킷 준비해! 쏴라!!";
			link.l1 = "...";
			link.l1.go = "mine_banditx_fire";
		break;
		
		case "mine_attackx_2":
			dialog.text = "아니. 중앙 입구로만 들어갈 수 있어.";
			link.l1 = "좋아, 친구... 이봐! 저기 봐! 저 성벽 위에 있는 저건 도대체 뭐야?";
			link.l1.go = "mine_attackx_3";
		break;
		
		case "mine_attackx_3":
			DialogExit();
			for (i=1; i<=4; i++)
			{
				sld = characterFromId("Mine_banditx_"+i);
				LAi_RemoveCheckMinHP(sld);
			}
			sld = characterFromId("Svensons_sold_12");
			LAi_SetActorType(sld);
			LAi_ActorTurnToLocator(sld, "soldiers", "soldier1");
			LAi_ActorAnimation(sld, "shot", "Saga_MineBanditxDie", 1.0);
		break;
		
		case "mine_attack":
			dialog.text = "정말이야? 그럼 암호를 알아야 할 텐데. 크게 말해서 내가 들을 수 있게 해. 그리고 날 속이려 한다면, 그게 네 인생에서 마지막으로 치는 농담이 될 거다.";
			link.l1 = "Triton";
			link.l1.go = "mine_wrong_password";
			link.l2 = "Neptune";
			link.l2.go = "mine_attack_1";
			link.l3 = "Centurion";
			link.l3.go = "mine_wrong_password";
			link.l4 = "Harpoon";
			link.l4.go = "mine_wrong_password";
		break;
		
		case "mine_attack_1":
			dialog.text = "맞다. 지나가라. 야영지의 책임자는 광산 입구 왼쪽에 있는 집에 있다. 가서 그를 만나봐라.";
			link.l1 = "좋아, 친구...";
			link.l1.go = "mine_attack_2";
		break;
		
		case "mine_wrong_password":
			dialog.text = "얘들아, 첩자가 나타났다! 대포, 발사해!!";
			link.l1 = "...";
			link.l1.go = "mine_bandit_fire";
		break;
		
		case "mine_attack_2":
			DialogExit();
			locCameraFollowEx(true);
			NextDiag.CurrentNode = "mine_attack_3";
			LAi_SetActorType(pchar);
			LAi_ActorFollow(pchar, npchar, "ActorDialog_Any2Pchar", -1);
			LAi_ActorTurnToCharacter(npchar, pchar);
			SetActorDialogAny2Pchar(npchar.id, "", 0.0, 0.0);
		break;
		
		case "mine_attack_3":
			dialog.text = "또 뭐 있나? 잊은 거라도 있나?";
			link.l1 = "예. 당신께 최고의 안부를 전해 달라는 부탁을 받았습니다.";
			link.l1.go = "mine_attack_4";
		break;
		
		case "mine_attack_4":
			dialog.text = "나한테? 하하! 누구한테서?";
			link.l1 = "얀 스벤손, 이 자식아!";
			link.l1.go = "mine_attack_5";
		break;
		
		case "mine_attack_5":
			DialogExit();
			AddDialogExitQuestFunction("Saga_MineAttack");
		break;
		
	// ----------------------------- диалоги НПС при штурме бандитского рудника -------------------------------
		case "Svensons_off":
			dialog.text = LinkRandPhrase("저 놈들 갈기갈기 찢어버릴 거야!","저 놈들 혼내줄 생각에 기대가 되네!","잭맨의 졸개들은 서부 메인에 있을 자격이 없어! 우리가 저놈들을 여기서 쫓아낼 거야!");
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Svensons_off";
		break;
		
		case "Svensons_sold":
			dialog.text = LinkRandPhrase("우린 싸울 준비가 됐어!","우리가 놈들에게 본때를 보여주자!","쟤네는 자기들이 누구랑 엮이고 있는지도 몰라!");
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Svensons_sold";
		break;
		
		case "gunner":
			PlaySound("Voice\English\evilpirates01.wav");
			dialog.text = "지휘관님, 대포 준비됐습니다. 명령하신 대로 폭탄을 장전했습니다.";
			link.l1 = "여기서 우리를 기다리는 사람은 없는 것 같군... 이제 우리를 소개할 시간이야. 얀 말로는 저 언덕 뒤에 그들의 야영지가 있다더군. 거기까지 갈 수 있겠어?";
			link.l1.go = "gunner_0_1";
		break;
		
		case "gunner_0_1":
			dialog.text = "쉽군요, 사령관. 포신을 조금만 더 올려 봅시다, 그러면 될 겁니다... 됐습니다.\n준비하세요!.. 발사!!";
			link.l1 = "...";
			link.l1.go = "gunner_0_2";
			npchar.quest.canonada = "1";
		break;
		
		case "gunner_0_2":
			DialogExit();
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("Saga_Gunfire", 3.0);
			LAi_ActorTurnToLocator(npchar, "goto", "goto14");
		break;
		
		case "gunner_1":
			dialog.text = "";
			link.l1 = "흠. 랜돌프, 우리가 뭔가에 부딪힌 것 같나? 자네 의견을 듣고 싶군.";
			link.l1.go = "gunner_1_1";
		break;
		
		case "gunner_1_1":
			PlaySound("interface\" + LanguageGetLanguage() + "\_bombs_npc.wav");
			dialog.text = "지휘관님, 뭔가나 누군가를 맞히긴 했는데, 더 이상은 말씀드릴 수 없습니다... 이 빌어먹을 언덕 때문에 시야가 가려집니다. 각도를 바꾸겠습니다.\n준비 완료! 발사!";
			link.l1 = "...";
			link.l1.go = "gunner_0_2";
			npchar.quest.canonada = "2";
		break;
		
		case "gunner_2":
			PlaySound("interface\abordage_wining.wav");
			PlaySound("types\warrior03.wav");
			dialog.text = "하! 저기 보시오, 지휘관! 연기가 나요! 젠장, 산적 놈들 헛간을 맞췄나 봅니다! 만세-야!\n";
			link.l1 = "그래, 연기가 보이는군... 이미 대단한 승리인 게 분명하지. 대포를 다시 장전해서 길 쪽으로 겨눠라, 손님들이 오는 것 같으니. 제대로 환영해 주자고!";
			link.l1.go = "gunner_2_1";
		break;
		
		case "gunner_2_1":
			PlaySound("interface\" + LanguageGetLanguage() + "\_bombs_npc.wav");
			dialog.text = "알겠슴다, 지휘관님! 폭탄 장전! 포병 대기! 도화선 준비! 내 명령에 맞춰 발사!";
			link.l1 = "...";
			link.l1.go = "gunner_2_2";
			npchar.quest.canonada = "3";
		break;
		
		case "gunner_2_2":
			DialogExit();
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("Saga_LoginBandos_01", 6.0);
			LAi_ActorTurnToLocator(pchar, "goto", "goto14");
			LAi_ActorTurnToLocator(npchar, "goto", "goto14");
		break;
		
		case "gunner_3":
			PlaySound("interface\abordage_wining.wav");
			PlaySound("types\warrior03.wav");
			PlaySound("Voice\English\evilpirates05.wav");
			dialog.text = "하하, 저거 꽤 아프겠는데!";
			link.l1 = "아직 방심하지 마! 대포 장전해! 녀석들 아직 덜 당한 것 같아. 더 몰려오고 있어!";
			link.l1.go = "gunner_3_1";
		break;
		
		case "gunner_3_1":
			PlaySound("interface\" + LanguageGetLanguage() + "\_bombs_npc.wav");//
			dialog.text = "알겠어요, 지휘관님! 폭탄 장전! 준비 완료! 내 명령에 쏴라!";
			link.l1 = "...";
			link.l1.go = "gunner_3_2";
			npchar.quest.canonada = "4";
		break;
		
		case "gunner_3_2":
			DialogExit();
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("Saga_LoginBandos_02", 5.0);
			LAi_ActorTurnToLocator(pchar, "goto", "goto14");
			LAi_ActorTurnToLocator(npchar, "goto", "goto14");
		break;
		
		case "gunner_5":
			PlaySound("types\warrior04.wav");
			PlaySound("Voice\English\evilpirates06.wav");
			dialog.text = "하하하, 저 놈들이 도망치고 있군! 개밥 신세로구나! 이 거리에서 산탄이 저놈들을 갈기갈기 찢어버리고 있어! 다시 덤빌 배짱은 없는 모양이지!";
			link.l1 = "이제 우리 차례다. 랜돌프, 너는 여기서 대포 옆에 있어라. 길 쪽으로 몇 번 쏘고, 그 다음엔 연기를 조준해서 놈들 소굴을 불태워! 우리만 쏘지 마라.";
			link.l1.go = "gunner_5_1";
		break;
		
		case "gunner_5_1":
			PlaySound("interface\" + LanguageGetLanguage() + "\_bombs_npc.wav");
			dialog.text = "예, 지휘관님! 대포 준비해! 포탄 장전해!";
			link.l1 = "놈들아! 무장해라! 나를 따라, 공격이다! 우라!!";
			link.l1.go = "attack";
		break;
		
		case "attack":
			DialogExit();
			n = Findlocation("mine");
			Locations[n].hidden_fire = true;
			PlaySound("interface\abordage_wining.wav");
			PlaySound("interface\abordage_wining.wav");
			LAi_ActorTurnToLocator(npchar, "goto", "goto14");
			LAi_group_MoveCharacter(npchar, "TMP_FRIEND");
			if (GetCharacterIndex("Svensons_sold_12") != -1 && pchar.questTemp.Saga.MineAttack == "soldiers")
			{
				sld = characterFromId("Svensons_sold_12");
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			for (i=1; i<=8; i++)
			{
				if (GetCharacterIndex("Ourmine_sold_"+i) != -1)
				{
					sld = characterFromId("Ourmine_sold_"+i);
					if (i == 1) sld.MusketerDistance = 10; 
					LAi_SetWarriorType(sld);
					LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				}
			}
			LAi_group_SetRelation("EnemyFight", "TMP_FRIEND", LAI_GROUP_NEITRAL);
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Saga_MineBandos_05Die");
			AddDialogExitQuest("MainHeroFightModeOn");	
			DoQuestCheckDelay("Saga_MineSetMusic", 0.3);
			// запускаем автобабахалку на 10 выстрелов
			iTotalTemp = 0;
			DoQuestCheckDelay("Saga_GunAutoFire", 7.0);
			bDisableCharacterMenu = false;//разлочим интерфейсы
			InterfaceStates.Buttons.Save.enable = true;//разрешим сохраняться
		break;
		
		case "convict":
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = LinkRandPhrase("나를 해치지 마, 난 그들 편이 아니야! 도적들을 죽여!","우릴 풀어줘, 친구! 그리고 저놈들 전부 죽여!","베어버려, 친구야, 베어버려! 다 죽여버려!");
				link.l1 = "하! 걱정 마, 우리가 지금 딱 그걸 하고 있으니까.";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = LinkRandPhrase("우리의 노예 생활이 끝난 건가요? 우리를 자유롭게 해주실 건가요?","헤, 내가 정말 이 날까지 살아남았단 말인가?","저 자식들이 우리 피를 다 빨아먹었어....");
				link.l1 = "곧 자유를 만끽할 수 있을 거라 생각해, 이 친구...";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "convict";
		break;
		
		// жена Яна Свенсона
		case "js_girl":
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = "여기를 떠나는 게 좋겠소, 나리. 우리는 범죄자를 숨겨주지 않으며, 식민지 당국과의 분쟁도 원치 않소.";
				link.l1 = "좋아, 나 간다...";
				link.l1.go = "exit";
				NextDiag.TempNode = "js_girl";
				break;
			}
			if(NPChar.quest.meeting == "0")
			{
				// Первый диалог с Элен
				if(startHeroType == 4)
				{
					dialog.text = "아, 헬렌. 네가 얀을 만나러 오기 전에 좀 더 단정하게 차려입을 수도 있었을 텐데, 네 본모습을 다 보여주다니. 그가 내 말을 믿지 않는 게 안타깝군.";
					link.l1 = "내가 도대체 어떤 사람인데? 그는 어릴 때부터 나를 키워 주셨고, 누구보다 나를 잘 알아. 나는 그분에게 숨기는 게 없어. 나는 어릴 때부터 이 더위에 시달려서, 나만의 방식으로 견딜 수밖에 없었을 뿐이야, 그게 다야.";
					link.l1.go = "js_helen_ft";
					NextDiag.TempNode = "js_girl";
					NPChar.quest.meeting = "1";
					break;
				}
				dialog.text = TimeGreeting()+", 나리. 얀을 만나시겠습니까?";
				link.l1 = "안녕하세요. 만나서 반가웠습니다, 아가씨?.. ";
				link.l1.go = "js_girl_1";
			}
			else
			{
				// заглушка элен
				if(startHeroType == 4)
				{
					dialog.text = "얀은 안에 있어. 어서 들어가, 여기 볼 것도 없고, 너 때문에 짜증나니까.";
					link.l1 = "어차피 별로 그럴 기분도 아니었어.";
					link.l1.go = "exit";
					NextDiag.TempNode = "js_girl";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.HelenDrinking.Dialogs.Joan")) {
					dialog.text = "그르르!";
					link.l1 = "스벤손 부인, 당신도 건강하시길 바랍니다.";
					link.l1.go = "exit";
					break;
				}
				
				if (CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "blueveld")
				{
					dialog.text = TimeGreeting()+", 선장 "+GetFullName(pchar)+". 만약 얀을 찾아온 거라면 실망하게 될 거요 – 그는 여기 없어. 중요한 일 때문에 나가 있거든.";
					link.l1 = "젠장! 난 그가 꼭 필요하다고! 스벤손 부인, 그가 언제 돌아올지 말해줬소?";
					link.l1.go = "js_girl_3";
					break;
				}
				dialog.text = "아, 또 당신이군, 선장 "+GetFullName(pchar)+"... 지나가, 얀은 평소처럼 위층에 있어.";
				link.l1 = "감사합니다, 스벤손 부인...";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "js_girl";
		break;
		
		case "js_girl_1":
			dialog.text = "부인, 요한나 스벤손 부인.";
			link.l1 = "Captain "+GetFullName(pchar)+".";
			link.l1.go = "js_girl_2";
		break;
		
		case "js_girl_2":
			if (CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "blueveld")
			{
				dialog.text = "선장님? 자, 저희 집에 오신 걸 환영합니다. 하지만 얀 때문에 오셨다면 실망시켜 드려야겠군요 - 그는 여기 없습니다. 중요한 일을 보러 나갔거든요.";
				link.l1 = "젠장! 나한텐 그 사람이 꼭 필요하다고! 말씀해 보시오, 스벤손 부인, 그가 언제 돌아온다고 했소?";
				link.l1.go = "js_girl_3";
				break;
			}
			dialog.text = "선장님? 자, 우리 집에 오신 걸 환영합니다. 제 남편은 2층 서재에 있습니다. 위층으로 올라가세요.";
			link.l1 = "알겠습니다, 스벤손 부인...";
			link.l1.go = "exit";
			NPChar.quest.meeting = "1";
			NextDiag.TempNode = "js_girl";
		break;
		
		case "js_girl_3":
			dialog.text = "아니오. 그는 언제 돌아올지 본인도 몰라서, 귀환 날짜조차 정확히 말해주지 않았소.";
			link.l1 = "방해해서 미안하지만, 저 사람은 정말 필요해... 무슨 조사를 하고 있는 거지?";
			link.l1.go = "js_girl_4";
		break;
		
		case "js_girl_4":
			dialog.text = "말해주지. 사랑스러운 헬렌, 일명 룸바, 고(故) 션 맥아더의 딸이 사라졌네. 얀은 그 어린 악동을 친딸처럼 아끼지. 헬렌은 얀의 옛 연인을 떠올리게 해, 똑같이 무모한 성격이었거든. 최소한, 내가 알기론 그게 얀이 끌리는 이유라네.\n어쨌든, 그 소녀는 일주일 전에 자신의 스쿠너 '레인보우'와 전 선원들과 함께 사라졌어. 션 맥아더가 헬렌에게 항해술을 가르쳤고, '레인보우'는 유언장에 따라 그녀에게 넘어갔지. 그리고 지금은 자기가 선장인 척하고 있다네...";
			link.l1 = "그녀에게 무슨 일이 있었던 걸까?";
			link.l1.go = "js_girl_5";
		break;
		
		case "js_girl_5":
			dialog.text = "누가 알겠어... 일주일이 그리 긴 시간은 아니지만, 맥아더의 미망인은 딸에게 무슨 일이 생겼다고 확신하고 있고, 얀도 그녀의 설득에 넘어갔지. 그래서 얀이 자기 부하들을 모아 직접 딸을 찾으러 나섰지만, 아직까지 성과는 없어. 내 생각엔 헬렌은 멀쩡하고, 얀만 괜히 스스로를 괴롭히는 거야.\n그 늙고 뚱뚱한 여자의 헛소리를 너무 믿고는 괜히 호들갑을 떤 거지. 그 아가씨는 지금쯤 다른 남자친구랑 어디 안전한 곳에서 남의 눈 피해 신나게 놀고 있을 거다. 배고픔만 채우면 곧 돌아올 거야.";
			link.l1 = "요한나, 글래디스는 어디에 있지? 그녀와 얘기하고 싶은데...";
			link.l1.go = "js_girl_6";
		break;
		
		case "js_girl_6":
			dialog.text = "그녀의 집은 부두 근처, 왼쪽에 있어. 하지만 아마 거기엔 없을 거야. 매일 요새 성벽에 서서 소중한 딸을 기다리며 시간을 허비하거든.";
			link.l1 = "알겠습니다. 정보 주셔서 대단히 감사합니다!";
			link.l1.go = "js_girl_7";
		break;
		
		case "js_girl_7":
			DialogExit();
			NextDiag.CurrentNode = "js_girl_8";
			sld = characterFromId("Gladis"); //устанавливаем Глэдис на форт
			ChangeCharacterAddressGroup(sld, "SantaCatalina_fort", "goto", "goto53");
			LAi_SetStayType(sld);
			sld.dialog.currentnode = "FindHelena";
			pchar.questTemp.Saga = "gladis";
			DelLandQuestMark(npchar);
			DelLandQuestMark(characterFromId("SantaCatalina_tavernkeeper"));
			DelMapQuestMarkCity("SantaCatalina");
		break;
		
		case "js_girl_8":
			dialog.text = "얀은 아직 안 왔으니, 선장님, 나중에 다시 오십시오.";
			link.l1 = "그렇군...";
			link.l1.go = "exit";
			NextDiag.TempNode = "js_girl_8";
		break;
		
		case "js_helen_ft":
			dialog.text = "넌 항상 발정난 것 같아. 교회에 좀 가봐라; 거기서 널 거의 본 적이 없거든.";
			link.l1 = "내 양심은 떳떳해 – 용서를 구할 일은 없어. 아직도 그가 내 배에 보급해준 게 못마땅해서 그래, 조안나? 차라리 네 드레스 하나 더 사줬으면 좋았겠다고?";
			link.l1.go = "js_helen_ft_1";
		break;
		
		case "js_helen_ft_1":
			dialog.text = "나? 씁쓸하냐고? 너 따위 때문에 그럴 일 없어. 그냥 너는 모든 게 너무 쉽게 풀리잖아, 근데 그럴 자격도 없으면서.";
			link.l1 = "하지만 내가 그 배를 손에 넣자마자 직접 돈을 벌기 시작했지. 그런데 넌, 그가 길고양이 주워오듯 데려간 뒤로 하루도 일한 적 없잖아. 그러니 진짜로 그 사람 등골 빼먹는 건 누굴까?";
			link.l1.go = "js_helen_ft_2";
		break;
		
		case "js_helen_ft_2":
			dialog.text = "계속 그렇게 말하다가는 언젠가 대가를 치르게 될 거야. 얀하고 글래디스가 너한테 예의 좀 가르쳤어야 했는데. 좋아, 할 말 있으면 해봐 – 그리고 내 눈앞에서 꺼져, 헬렌. 그는 안에 있어.";
			link.l1 = "멍청한 암탉 같으니. 그래, 해줄게.";
			link.l1.go = "exit";
		break;
		
		// хронометр Алекса
		case "Alexs_bandos":
			dialog.text = "이봐! 여기서 뭐 하는 거야?";
			link.l1 = "나도 묻고 싶군 – 너랑 네 친구들은 여기, 내 감옥에서 뭘 하고 있는 거지?";
			link.l1.go = "Alexs_bandos_1";
		break;
		
		case "Alexs_bandos_1":
			dialog.text = "하! 네 감옥이라고? 언제부터 네 것이 되었지, 이 망할 놈아?";
			link.l1 = "네 아버지가 네 어머니와 잘못된 짓을 한 그날.";
			link.l1.go = "Alexs_bandos_2";
		break;
		
		case "Alexs_bandos_2":
			dialog.text = "문제라도 찾는 거야?";
			link.l1 = "이봐, 친구, 마지막으로 한 번 더 기회를 줄게. 여기서 나가. 여긴 내 감옥이야, 아무나 함부로 들어오게 두지 않아, 알겠어? 내가 휘파람 한 번만 불면, 이슬라 테소로의 해적 절반이 1분 안에 몰려올 거야.";
			link.l1.go = "Alexs_bandos_3";
		break;
		
		case "Alexs_bandos_3":
			dialog.text = "좋아, 그럼 네 입을 다물게 해 주지!";
			link.l1 = "하하! 한심하구나, 이 쓰레기야!";
			link.l1.go = "Alexs_bandos_4";
		break;
		
		case "Alexs_bandos_4":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation("Bermudes_Dungeon")], false);
			for (i=1; i<=4; i++)
			{
				sld = characterFromId("Alexs_bandos_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+5;
			int iScl = 25+2*sti(pchar.rank);
			sld = GetCharacter(NPC_GenerateCharacter("Alexs_bandos_5", "mush_ctz_8", "man", "mushketer", iRank, PIRATE, -1, false, "soldier"));
			FantomMakeCoolFighter(sld, iRank, iScl, iScl, "", "mushket1", "bullet", iScl*2+50);
			ChangeCharacterAddressGroup(sld, "Bermudes_Dungeon", "monsters", "monster8");
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "AlexClock_BandosDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "helendrinking_gypsy":
			dialog.text = "잠깐 기다려라, 매야!";
			link.l1 = "타이밍이 별로 좋지 않네, 자기야.";
			link.l1.go = "helendrinking_gypsy_1";
		break;
		
		case "helendrinking_gypsy_1":
			dialog.text = "오, 잘못 알았군, 잘생긴이. 이 아가씨가 너를 좋아하고, 너도 그녀에게 마음이 있는 게 보여.";
			link.l1 = "별로 좋은 추천은 아니군... 좋아, 뭘 원하는 거지? 한 푼 달라고?";
			link.l1.go = "helendrinking_gypsy_2";
		break;
		
		case "helendrinking_gypsy_2":
			dialog.text = "당신의 힘든 도전에 지원을 해주고 싶소. 여기 보시오! 마법 머그잔과 금단의 연고가 있소. 머그잔은 술 마실 때 도움이 될 것이고, 연고는 사랑의 문제에 도움이 될 것이오. 무엇을 고르겠소? 단 이천!\n";
			link.l1 = "나는 아무것도 필요 없어 - 이미 너희 같은 놈들에게 은을 한 무더기나 줬으니까.";
			link.l1.go = "helendrinking_gypsy_refuse";
			if (sti(pchar.money) >= 2000) {
				link.l2 = "금지된 연고라고? 뭐, 내가 성인은 아니지. 이리 내놔.";
				link.l2.go = "helendrinking_gypsy_fuck";
				link.l3 = "머그잔? 내가 주정뱅이처럼 보여? 뭐, 나도 알지... 마시겠어!";
				link.l3.go = "helendrinking_gypsy_drink";
			}
			
			AddDialogExitQuestFunction("HelenDrinking_TalkedToGypsy");
		break;
		
		case "helendrinking_gypsy_refuse":
			dialog.text = "잘생겼지만 어리석군. 그럼 날아가라, 매여.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_TalkedToGypsy");
		break;
		
		case "helendrinking_gypsy_drink":
			dialog.text = "아, 그 밑 빠진 주머니에 숨기지 마! 날아가라, 매야, 그리고 죄 짓지 마라!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddMoneyToCharacter(pchar, -2000);
			GiveItem2Character(pchar, "totem_01");
			Log_Info("Talisman 'Throat of cast iron' acquired!");
			PlaySound("interface\important_item.wav");
			
			AddDialogExitQuestFunction("HelenDrinking_TalkedToGypsy");
		break;
		
		case "helendrinking_gypsy_fuck":
			dialog.text = "아, 그 끝도 없는 주머니에 숨기지 마! 날아가라, 매야, 그리고 죄짓지 말거라!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddMoneyToCharacter(pchar, -2000);
			GiveItem2Character(pchar, "totem_03");
			Log_Info("Talisman 'Cupid's Balm' acquired!");
			PlaySound("interface\important_item.wav");
			pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) - 1;
			Notification_Approve(false, "Helena");
			
			AddDialogExitQuestFunction("HelenDrinking_TalkedToGypsy");
		break;
		
		case "helendrinking_joan":
			dialog.text = "아! 썩 꺼져라, 이 악당아! 내가 몇 번이나 내 집에 몰래 들어오지 말라고 했지! 그리고 이 자식은 누구냐?";
			link.l1 = "부인, 우리는 이미 아는 사이입니다.";
			link.l1.go = "helendrinking_joan_1";
		break;
		
		case "helendrinking_joan_1":
			dialog.text = "드 모르 나리? 정말 기가 막히네요! 당신이 내 남편과 이렇게 거래를 하는 겁니까?! 내가 알았어요! 내가 얀에게 경고했잖아요. 언젠가 저 여자가 자기 부하들을 잘못된 길로 이끌 거라고! 그리고 당신 손에 든 건 뭐죠?";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_JoanDialog1");
		break;
		
		case "helendrinking_joan_2":
			dialog.text = "뭐어어어?! 감히 네가, 이 망할 놈아?! 넌 어디도 못 가! 내 남편이 곧 올 거니까, 네가 어른한테 어떻게 말해야 하는지 똑똑히 가르쳐 줄 거다!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_JoanDialog3");
		break;
		
		case "helendrinking_fort_officer":
			dialog.text = "여기서 무슨 일이 벌어지고 있소? 맥아더 양! 나는 당신 아버지를 매우 존경했었고, 스벤손 씨는 우리 친구요... 하지만 지난번에 어떻게 끝났는지 기억 안 나시오?\n실망스럽소, 장교의 명예를 걸고, 정말 실망스럽소! 우리도 초대할 수 있었잖소!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_FortDialog");
		break;
		
		case "helendrinking_fort_officer_1":
			dialog.text = "환대해 주셔서 감사합니다, 맥아더 양. 모두가 당신이 돌아온 것을 진심으로 기뻐하고 있다는 말씀을 드리고 싶습니다. 무슨 일이 있었는지는 큰 미스터리지만, 마을 사람들이 알게 된 것도 놀랄 일은 아니지요. 그래도 아무도 소문을 내지 않을 것임을 확실히 약속드립니다. 최근 우리 선장 중 한 명의 행동에 대해 진심으로 사과드립니다. 그리고 특별히 감사드리고 싶습니다, 드 모르 나리.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_FortDialog3");
		break;
		
		case "helendrinking_fort_officer_2":
			dialog.text = "모든 게 잘 될 겁니다, 아가씨. 드 모르 나리, 솔직히 말씀드리죠 – 도노반이 진짜 악당이자 도적처럼 행동했음에도 불구하고, 함대는 결코 그를 공개적으로 비난하지 않을 겁니다. 오히려 그를 두둔할 가능성이 더 높죠. 당신의 작은 원정은 보고서에 올라갔고, 그로 인해 우리 두 나라의 관계가 상당히 복잡해졌습니다.\n그럼에도 불구하고, 스벤손 나리의 영향력과 캡스터빌이 당신께 내준 놀라운 양보를 고려하면, 두려워할 일은 없습니다.";
			link.l1 = "훌륭하군. 자, 그걸 위해 한잔하자!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_FortDialog1");
		break;
		
		case "helendrinking_poorman":
			dialog.text = "실례합니다만, 그 일은 어떻게 된 겁니까?";
			link.l1 = "아직도 여기 있나?";
			link.l1.go = "helendrinking_poorman_1";
		break;
		
		case "helendrinking_poorman_1":
			dialog.text = "나리, 제가 어디로 가겠습니까? 그냥 볼일 좀 보러 갔다가, 나리의 감상적인 대화를 우연히 듣게 되었고, 좀 달아올랐습니다. 감정적으로 말이지요!";
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.BoughtRainbow")) {
				link.l1 = "맙소사! 뭐, 내가 이미 약속했으니 어쩔 수 없군. 가서 지휘를 맡으시오.";
				link.l1.go = "helendrinking_poorman_bought";
			} else {
				link.l1 = "당신에게 줄 일이 없소, 나리.";
				link.l1.go = "helendrinking_poorman_notbought";
			}
		break;
		
		case "helendrinking_poorman_bought":
			dialog.text = "알겠어요, 선장님!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AddRainbow");
			AddDialogExitQuestFunction("HelenDrinking_LightsOut1NoArg");
		break;
		
		case "helendrinking_poorman_notbought":
			dialog.text = "안타깝네! 어쨌든 대접 고마워, 선장!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AddRainbow");
			AddDialogExitQuestFunction("HelenDrinking_LightsOut1NoArg");
		break;
		
		case "helensleep_amelia_mary":
			dialog.text = "In nomine Patris et Filii et Spiritus Sancti... 들어오너라, 아들아.";
			if (HelenSleep_TalkedToAmelia()) {
				link.l1 = "안녕하세요, 아멜리아 어머니. 저한테도 소리치실 건가요?";
				link.l1.go = "helensleep_amelia_mary_know";
			} else {
				link.l1 = "사라져! 이게 대체 무슨 악몽이야? 무슨 일이 일어나고 있는 거지? 내가 꿈을 꾸고 있는 건가?";
				link.l1.go = "helensleep_amelia_mary_notknow";
			}
		break;
		
		case "helensleep_amelia_mary_know":
			dialog.text = "아니야, 내 작은 매야. 그리고 얀을 용서해 줘라 – 그 불쌍한 자가 흥분했을 뿐이니. 하지만 그래, 나는 네게 잔소리 좀 하고 싶구나. 왜 교회에 온 것이냐? 죄를 뉘우치러 온 것이냐? 아니면 그 빨간 머리 녀석을 따라온 것이냐?";
			link.l1 = "나도 나 자신을 모르겠어...";
			link.l1.go = "helensleep_amelia";
			link.l2 = "너도 그녀를 봤어? 내 눈길을 사로잡더라.";
			link.l2.go = "helensleep_amelia";
		break;
		
		case "helensleep_amelia_mary_notknow":
			dialog.text = "사라져. 우린 이미 만났어야 했는데, 네가 모든 걸 질질 끌고 있군. 왜 교회에 온 거지? 죄를 뉘우치러? 아니면 그 빨간 머리 녀석을 노린 건가?";
			link.l1 = "나도 잘 모르겠어...";
			link.l1.go = "helensleep_amelia";
			link.l2 = "너도 그녀를 봤어? 내 눈길을 사로잡더라.";
			link.l2.go = "helensleep_amelia";
		break;
		
		case "helensleep_amelia_helen":
			dialog.text = "좋은 아침이오, 내 팔콘. 연회는 아직 시작하지 않았으니, 줄을 서서 기다리시오.";
			if (HelenSleep_TalkedToAmelia()) {
				link.l1 = "안녕하십니까, 각하. 각하께서도 저에게 소리치실 생각이십니까?";
				link.l1.go = "helensleep_amelia_helen_know";
			} else {
				link.l1 = "사라져! 이게 무슨 악몽이야? 무슨 일이 일어나고 있는 거지? 내가 꿈을 꾸고 있는 건가?";
				link.l1.go = "helensleep_amelia_helen_notknow";
			}
		break;
		
		case "helensleep_amelia_helen_know":
			dialog.text = "아니야, 내 매야. 그리고 얀을 용서해라, 그 불쌍한 남자가 흥분했거든. 너를 꾸짖을 필요는 없어; 넌 다 잘했어 - 빨간 머리 녀석을 따라 교회로 가지도 않았잖아. 착하지!";
			link.l1 = "칭찬받는 건 기분 좋지. 특히 무슨 이유로 받는지 분명할 때는 더 그렇지.";
			link.l1.go = "helensleep_amelia";
			link.l2 = "너도 그녀를 봤어? 내 눈길을 사로잡더라.";
			link.l2.go = "helensleep_amelia";
		break;
		
		case "helensleep_amelia_helen_notknow":
			dialog.text = "사라져라. 이미 만났어야 했는데, 네가 모든 걸 질질 끌고 있군. 이리 와, 칭찬해 줄게 – 빨간 머리 녀석을 교회까지 쫓아가지 않았으니. 착하지!";
			link.l1 = "칭찬받는 건 기분 좋지. 특히 왜 칭찬받는지 분명할 때 더 그렇지.";
			link.l1.go = "helensleep_amelia";
			link.l2 = "너도 그녀를 봤어? 내 눈길을 사로잡더라.";
			link.l2.go = "helensleep_amelia";
		break;
		
		case "helensleep_amelia":
			dialog.text = "자세한 이야기는 하지 않겠어, 바보야. 하지만 이것만은 말해주지. 너는 위대한 인물이 될 운명이야. 많은 악을 저지를 테지만, 훨씬 더 많은 선을 이루게 될 거야. 하지만 행복이 너에게 보장된 것은 아니야. 행복이란, 내 매 같은 아이야, 자신의 길을 걷고 그 길에서 벗어나지 않는 자에게만 주어지는 것이지. 그리고 한결같은 여인이 네가 길을 잃지 않도록 도와줄 거야.\n너에겐 그런 여인이 둘 있을 것이고, 둘 다 행복을 가져다주겠지만, 금발인 여인을 선택해야 해.";
			link.l1 = "그게 왜 그래야 하지? 내가 직접 결정할 거야!";
			link.l1.go = "helensleep_amelia_1";
		break;
		
		case "helensleep_amelia_1":
			dialog.text = "물론, 네가 직접 고르도록 해. 하지만 금발이 더 낫지. 우리는 그렇게 정했어.";
			link.l1 = "우리는 누구지?";
			link.l1.go = "helensleep_amelia_2";
		break;
		
		case "helensleep_amelia_2":
			dialog.text = "그 불쌍한 여자는 자기 진짜 이름조차 모른다네. 그 이름을 말하면, 그녀는 그대의 것이 되리라. 그렇게들 말하지.";
			link.l1 = "이제 아무것도 이해가 안 돼.";
			link.l1.go = "helensleep_amelia_3";
		break;
		
		case "helensleep_amelia_3":
			dialog.text = "저 두드리는 소리 들려? 문 열어, 실수하지 말고.";
			link.l1 = "정말로, 누가 문을 두드리고 있군... 들어오시오!";
			link.l1.go = "exit";
			
			PlaySound("interface\knock.wav");
			
			AddDialogExitQuestFunction("HelenSleep_WakeUp");
		break;
		
		case "helendrinking_notifier":
			dialog.text = "나리, 스벤손 씨께서 잠시 시간 좀 내 달라고 부탁하셨습니다.";
			link.l1 = "젠장, 이거 영 불길하군. 해보겠지만 장담은 못 해.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_End");
		break;
		
		case "islatesoro_pirate1":
			dialog.text = "운 좋은 날이구나, 얘들아! 내가 언젠가는 이쪽으로 올 거라고 했지? 자, 아가씨, 무기 넘기고 우리랑 같이 가자.";
			link.l1 = "잘못 알았군, 얘들아. 저 여자는 내 사람이야.";
			link.l1.go = "islatesoro_pirate1_1";
		break;
		
		case "islatesoro_pirate1_1":
			dialog.text = "끼어들지 마라, 아니면 개처럼 쏴 죽일 거다. 그 계집애한테는 꽤 큰 현상금이 걸렸고, 우리는 배고픈 놈들이라 양심 따윈 없다.";
			link.l1 = "계속 그런 말투로 굴면, 네 배고픔은 영원히 해결해 주지.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroSpawnSecond");
		break;
		
		case "islatesoro_pirate1_2":
			dialog.text = "완전히 미쳤냐, 럭키? 우리가 먼저 그녀를 찾았잖아! 나한테 그렇게 멍청하게 떠드는 데에는 제대로 된 이유가 있어야 할 거다!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroPirateDialog1");
		break;
		
		case "islatesoro_pirate1_3":
			dialog.text = "여기서 쥐새끼는 너잖아! 우리 방금 통통한 스페인 놈 하나 갈가리 찢어놨으니, 1년이고 엉덩이 붙이고 놀아도 되겠지!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroPirateDialog3");
		break;
		
		case "islatesoro_pirate2":
			dialog.text = "자, 이게 누구신가. 좋아, 나머지는 다 나가고, 당신, 부인, 우리랑 같이 가시지.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroPirateDialog");
		break;
		
		case "islatesoro_pirate2_1":
			dialog.text = "우리가 너희보다 숫자도 많고, 힘도 세다, 덴마크 놈아. 더 무슨 이유가 필요해, 이 선창 쥐야? 너, 제대로 된 전리품 본 지 반 년이나 됐잖아, 그동안 부아지 놈 식탁에서 빵 부스러기나 주워 먹었지!\n";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroPirateDialog2");
		break;
		
		case "islatesoro_pirate2_2":
			dialog.text = "";
			link.l1 = "여기서는 평화롭게 해결될 것 같지 않군.";
			link.l1.go = "islatesoro_pirate_a";
			if (!CheckAttribute(pchar, "questTemp.HelenDrinking.IslaTesoroAmbush.TriedB")) {
				link.l2 = "뭐라고 했어? 운이 좋다고? 그 녀석이랑 부아지에가 짜고 너한테 엉터리 정보를 줬다는 소문을 들었어. 그래서 네가 바다에서 계속 운이 없었던 거구나.";
				link.l2.go = "islatesoro_pirate_b";
			}
			bOk = (!CheckAttribute(pchar, "questTemp.Mtraxx.Retribution.Choice")) || (pchar.questTemp.Mtraxx.Retribution.Choice == "bad");
			if (!CheckAttribute(pchar, "questTemp.HelenDrinking.IslaTesoroAmbush.TriedC") && CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold") && bOk) {
				link.l3 = "이런 소동은 이제 지겹다. 이슬라 테소로, 내 말 들어라! 카르타헤나에서 나와 함께했던 자가 누구였지?! 메리다를 나와 함께 불태운 자가 누구였나?! 이 쥐새끼들이 감히 찰리 프린스 본인에게 덤비다니! 보여주자, 녀석들아!";
				link.l3.go = "islatesoro_pirate_c";
			}
		break;
		
		case "islatesoro_pirate_a":
			dialog.text = "아직도 여기 있냐, 해파리 녀석? 좋아, 얘들아, 가자: 선장부터 묶어 두고, 그 계집애는 나중에 처리한다, 알겠지?\n";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroPirateDialog4");
		break;
		
		case "islatesoro_pirate_a_1":
			dialog.text = "그래, 피라도 좀 흘려보자. 헤헤.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroA");
		break;
		
		case "islatesoro_pirate_b":
			pchar.questTemp.HelenDrinking.IslaTesoroAmbush.TriedB = true;
		
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > 60) {
				dialog.text = "뭐라고?! 젠장, 네가 그 안경 쓴 악당이랑 한패인 줄 알았지! 다들, 저놈들 모조리 베어버려! 그 계집애는 나중에 데려가면 되니까!";
				link.l1 = "";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("HelenDrinking_IslaTesoroB");
			} else {
				dialog.text = "무슨 헛소리야, 선장? 체면 있는 사람들이 사업 얘기하는데 얼른 꺼져.";
				link.l1 = "";
				link.l1.go = "islatesoro_pirate2_2";
			}
			
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		
		case "islatesoro_pirate_c":
			pchar.questTemp.HelenDrinking.IslaTesoroAmbush.TriedC = true;
		
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > 50) {
				DialogExit();
				AddDialogExitQuestFunction("HelenDrinking_IslaTesoroC");
			} else {
				dialog.text = "뭐라고 떠드는 거야, 선장? 나는 찰리 프린스를 봤는데, 너는 그에 비하면 한참 모자라. 어서 꺼져, 어른들이 사업 이야기하는 중이니까.";
				link.l1 = "";
				link.l1.go = "islatesoro_pirate2_2";
			}
			
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		
		case "francois":
			dialog.text = "샤를 드 모르? 앙리 드 몽프의 아들이냐?";
			link.l1 = "맞습니다, 나리. 그런데 당신은 누구십니까?";
			link.l1.go = "francois_1";
		break;
		
		case "francois_1":
			dialog.text = "프랑수아 드 타반 대령. 이것을 직접적인 도전으로 받아들이시오, 나리. 결투의 장갑은 이미 던져졌소. 너 같은 자와 손을 더럽히고 싶지도 않지만, 맹세코 내 검이 네 피를 맛보게 될 것이오!";
			link.l1 = "결투라고? 그렇다면 더 열심히 해야겠군, 대령. 지금 모습으론 산적으로밖에 안 보이니, 이곳에선 그런 자들과의 대화는 짧게 끝나지! 변명해 보시오!";
			link.l1.go = "francois_2";
		break;
		
		case "francois_2":
			dialog.text = "당신이 내 아내를 유혹했소, 나리! 나는 왕과 조국을 위해 피를 흘리고 있었는데, 당신은... 당신은 내 아내와 즐기고 있었단 말이오!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog");
		break;
		
		case "francois_3":
			dialog.text = "조용히 하시오, 부인. 그 대담한 옷차림은 어느 여인의 명예라도 더럽히는 것이오. 하지만 이처럼 천박한 귀부인 유혹꾼 옆에 서 있으니 오히려 잘 어울리는군!";
			link.l1 = "아직 결투를 할 만한 이유는 부족하오, 대령 나리. 그리고 이 자리에서 나리 역시 그리 품위 있게 행동하고 계신 것 같지는 않다는 점을 지적하고 싶소.";
			link.l1.go = "francois_4";
		break;
		
		case "francois_4":
			dialog.text = "그것으로 충분하지 않소? 내가 알아봤는데, 지금 내 자리에 귀족 남편 열두 명쯤은 앉아 있을 수도 있겠더이다, 나리. 하지만 자세한 이야기를 원하신다면, 부끄럽게도 고백하오, 당신의 정열 중 하나는 바로 루루 드 타반, 가장 아름답고 정직한 여인이었소!";
			link.l1 = "루루라니... 그 아가씨는 어떻게 지내?";
			link.l1.go = "francois_5";
		break;
		
		case "francois_5":
			dialog.text = "조용히 하라! 네가 가한 고통을 견디지 못해 내 아내가 최근에 세상을 떴다! 너를 찾느라 거의 1년과 막대한 돈을 쏟아부었다, 이 악당아! 말은 충분하다! 결투를 받아들이든지, 아니면 개처럼 죽여주겠다. 리처드! 증인이 되어라!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog2");
		break;
		
		case "francois_6":
			dialog.text = "조용히 하시오, 나리! 도전을 받아들이거나 남아 있는 명예의 조각마저 잃을 것이오!";
			if (pchar.HeroParam.HeroType == "HeroType_1") {
				link.l1 = "결투는 결투지. 솔직히 말해서, 난 이런 거 꽤 즐긴다. 선장, 대령에게 이제 적당한 관을 준비하라고 전해 줘.";
			} else {
				link.l1 = "싸움을 원해? 원한다면 해주지! 선장, 대령에게 전해라. 이제 관을 준비하라고 할 때라고.";
			}
			link.l1.go = "francois_duel";
			link.l2 = "여기는 유럽이 아니오, 대령. 카리브에서는 명예를 얻기는 더 어렵지만, 잃기도 그리 쉽지 않소. 결투를 거절하는 이유는, 내가 원하지 않기 때문이오.";
			link.l2.go = "francois_refuse";
		break;
		
		case "francois_7":
			dialog.text = "네 아버지는 이미 무덤 문턱에 한 발짝 남았어, 이 쓰레기야! 그리고 네 비겁함을 반드시 알게 해주지!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog7");
		break;
		
		case "richard":
			dialog.text = "대령 나리, 결투할 권리는 인정하오. 하지만 단순한 강도질은 용납하지 않겠소! 드 모르 나리, 나는 리처드 스몰 선장이오. 타반느 대령께 만족을 드릴 의향이 있소?";
			link.l1 = "잠시만요, 선장님. 나는 루루를 잘 알았소... 그리고 그 여자는... 구애자를 자주 바꾸는 편이었고, 건강도 내 것보다 더 좋았지... 대령, 루루는 어떻게 죽었소? 당신이 집에 돌아오기 전이오, 아니면 후였소?";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog3");
		break;
		
		case "richard_1":
			dialog.text = "부탁하네, 프랑수아. 내가 하겠네. 드 모르 나리, 당신에게 결투 신청이 들어왔소. 블루웰드 장교회는 타반 대령의 명예 회복 요구가 정당함을 인정하오. 결투를 받아들이지 않으면 명예를 잃게 될 것이오.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog5");
		break;
		
		case "richard_2":
			dialog.text = "샤를, 제발, 우리는 여기서 신사들이오. 이러는 건 옳지 않소. 대령께서 이렇게 멀리까지 당신을 만나러 오셨다오! 이건 스캔들이오!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog8");
		break;
		
		case "richard_3":
			dialog.text = "예, 예, 물론입니다, 아가씨. 하지만 저는...";
			link.l1 = "";
			link.l1.go = "exit";
			CharacterTurnToLoc(npchar, "quest", "helen");
			
			AddDialogExitQuestFunction("HelenDrinking_AfterFrancoisDeath1");
		break;
		
		case "richard_4":
			dialog.text = "드 모르 선장, 오늘은 당신의 날이오! 가장 정정당당한 싸움은 아니었지만, 오늘 당신의 명예를 지켜냈소.";
			link.l1 = "무슨 말씀하셨습니까, 선장님? 오늘 일정에 결투 하나쯤 더 끼워 넣을 수도 있겠군요.";
			link.l1.go = "richard_5";
		break;
		
		case "richard_5":
			dialog.text = "죄송합니다, 선장님. 그냥 긴장해서 그랬습니다!";
			link.l1 = "여기 더 이상 계실 필요는 없다고 생각하오.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_DuelVictory");
		break;
		
		case "richard_duel":
			dialog.text = "공정한 결정이오! 비록 그리 품위 있게 말하진 않았지만... 신사 여러분! 시작합시다!\n";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_SetupDuel");
		break;
		
		case "alonso":
			dialog.text = "선장님, 저 고관들이 무슨 번지르르한 말을 하는진 다 못 알아듣겠지만, 겁쟁이란 소릴 들으면 그냥 넘어가면 안 되지요. 한 방 먹이세요, 선장님. 안 그러면 우리 선원들이 걱정하기 시작할 겁니다.";
			link.l1 = "피를 원해? 인생이 너무 지루하고 자극이 없지? 피를 보게 해주지, 이 짐승들아!";
			link.l1.go = "francois_duel";
			link.l2 = "흑흑, 무서워 죽겠네. 여기서 다 끝났소, 나리들? 나도 가야 할 데가 있거든.";
			link.l2.go = "alonso_refuse";
		break;
		
		case "alonso_1":
			dialog.text = "우리 선장님이 공개 도전을 피하면 체면이 안 서지. 그냥 그 귀족놈 한 대 제대로 갈겨 줘. 검 솜씨 좋은 거 우리 다 알잖아!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog9");
		break;
		
		case "alonso_refuse":
			DialogExit();
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog6");
		break;
		
		case "francois_refuse":
			dialog.text = "겁쟁이! 난봉꾼! 쥐새끼! 겁났냐, 이 악당아? 다들 봤지?! 리처드, 어차피 내가 저놈 죽일 거야!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog4");
		break;
		
		case "francois_duel":
			DialogExit();
			
			AddDialogExitQuestFunction("HelenDrinking_SetupDuelDialog");
		break;
		
		case "francois_sit":
			dialog.text = "이, 이 악당놈! 괜찮아, 난 상처엔 익숙하니까. 곧 회복할 거야, 그리고...";
			link.l1 = "위협처럼 들리는군, 대령. 그리고 나는 위협을 가볍게 넘기지 않아.";
			link.l1.go = "francois_sit_kill";
			link.l2 = "회복하면, 부상당한 사연을 장교들 모임에서 자랑하는 것 잊지 마시오.";
			link.l2.go = "francois_sit_taunt";
		break;
		
		case "francois_sit_kill":
			DialogExit();
			
			pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) - 1;
			Notification_Approve(false, "Helena");
			
			AddDialogExitQuestFunction("HelenDrinking_FinishFrancois");
		break;
		
		case "francois_sit_taunt":
			DialogExit();
			
			pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) + 1;
			Notification_Approve(true, "Helena");
			AddCharacterExpToSkill(pchar, SKILL_LEADERSHIP, 300);
			AddCharacterExpToSkill(pchar, SKILL_FORTUNE, 300);
			
			AddDialogExitQuestFunction("HelenDrinking_SpareFrancois");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}

bool HelenSleep_TalkedToAmelia() {
	if (GetCharacterIndex("Amelia") < 0) {
		return false;
	}
	
	sld = CharacterFromID("Amelia");
	if (sld.dialog.currentnode == "amelia") {
		return false;
	}
	
	return true;
}
