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
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			dialog.text = "무슨 일이야?";
			link.l1 = "아무것도 아니야.";
			link.l1.go = "exit";
		break;
		
		case "dwh_gypsy_0":
			dialog.text = "...";
			link.l1 = "이봐, 검은 눈썹 녀석, 사람들을 심한 병에서도 고친다고 들었는데, 그게 사실이냐?";
			link.l1.go = "dwh_gypsy_1";
			DelLandQuestMark(npchar);
		break;
		
		case "dwh_gypsy_1":
			dialog.text = "진실, "+GetSexPhrase("여보","아름다움")+". 나는 모든 병을 다스리는 나만의 방법이 있지. 평민이든, 상인이든, 심지어 부자들까지 내가 다시 일으켜 세웠어. 아니, 아무도 도울 수 없을 때 총독조차 내 약에 의지했지. 병은 금을 두려워하지 않지만, 내 치료법은 거부하지 못하거든.";
			link.l1 = "그렇다면 왜 중병에 걸린 토마스 모리슨의 딸을 치료하기를 거부하는 것이오?";
			link.l1.go = "dwh_gypsy_2";
			pchar.questTemp.DWH_gipsy = true;
		break;
		
		case "dwh_gypsy_2":
			dialog.text = "누가 그런 헛소리를 했지, "+GetSexPhrase("팔코네트","도비")+"? 내가 도와주기를 거절한 게 아니야. 그녀의 아버지가 나를 집에서 쫓아냈지. 내가 그녀를 치료하기로 약속했는데, 갑자기 마음을 바꿨어. 마치 원수라도 되는 것처럼 나를 내쫓았다고.";
			link.l1 = "그래서 그는 자기 손으로 딸을 고통받게 했단 말인가?";
			link.l1.go = "dwh_gypsy_2_1";
		break;
		
		case "dwh_gypsy_2_1":
			dialog.text = "아니, 아니야, 그는 자상한 아버지야. 왜 그렇게 행동했는지 상상하기 어렵네.";
			link.l1 = "그 사람에게 다시 말해 보았나?";
			link.l1.go = "dwh_gypsy_3";
		break;
		
		case "dwh_gypsy_3":
			dialog.text = "그 집 근처에도 못 가게 해. 이봐, "+GetSexPhrase("여보","아름다움")+", 가엾은 소녀의 운명이 걱정된다면 무슨 일이 일어나고 있는지 알아봐 줄 수 있겠어요? 토마스와 이야기하고, 아이가 고통받지 않도록 도와주세요.";
			link.l1 = "물론 도와주지. 토마스는 어디서 찾을 수 있지?";
			link.l1.go = "dwh_gypsy_4";
			link.l2 = "아니, 검은 눈썹. 어쨌든 그녀 아버지가 네 도움을 거절한 데는 분명 이유가 있을 거다. 나는 끼어들지 않겠다. 결정은 그가 하게 둬라—그녀는 그의 딸이니까.";
			link.l2.go = "dwh_gypsy_otkaz";
		break;
		
		case "dwh_gypsy_otkaz":
			DialogExit();
			CloseQuestHeader("DWH");
		break;
		
		case "dwh_gypsy_4":
			dialog.text = "그들의 집은 마을 북쪽 성벽 옆, 기둥이 있는 큰 저택 옆에 있다네. 계속하게,\n "+GetSexPhrase("팔코넷","도비")+", 그와 이야기하고 나에게 다시 오시오.";
			link.l1 = "곧 돌아올게.";
			link.l1.go = "dwh_gypsy_5";
		break;
		
		case "dwh_gypsy_5":
			DialogExit();
			AddDialogExitQuestFunction("DWH_gypsy_5");
		break;

		case "dwh_gypsy_repeat":
			dialog.text = "음, "+GetSexPhrase("여보","여보")+", 토마스와 얘기해 봤어?";
			link.l1 = "아직 아니야.";
			link.l1.go = "dwh_exit";
		break;

		case "dwh_exit":
			DialogExit();
			NextDiag.TempNode = "dwh_gypsy_repeat";
		break;
		
		case "Tomas":
			dialog.text = ""+TimeGreeting()+"! 무슨 일로 내 집에 왔나?";
			link.l1 = "내 이름은 선장이오 "+GetFullName(pchar)+". 집시 여인의 부탁을 받고 왔소. 왜 그녀의 도움을 거절했는지 알고 싶어 하더군. 아무리 작은 기회라도 따님의 병을 고칠 수 있다면, 정말로 그걸 거부할 처지요?";
			link.l1.go = "Tomas_1";
			DelLandQuestMark(npchar);
		break;

		case "Tomas_1":
			dialog.text = "아이고, 선장님... 제발 이해해 주십시오. 제 의지로 거절한 게 아니었습니다. 믿어 주십시오, 에스더가 회복된다면 뭐든지 바칠 수 있습니다.";
			link.l1 = "그토록 절실히 필요했던 도움을 왜 거절한 거요?";
			link.l1.go = "Tomas_2";
		break;

		case "Tomas_2":
			dialog.text = "보시다시피, 우리 집안은 언제나 독실했소. 아내 올리비아가 세상을 떠난 뒤로 나는 오직 신앙만을 붙잡고 살아왔지. 집시가 도움을 주겠다고 해서, 딸을 구할 수만 있다면 뭐든 하겠다고 동의했소. 하지만... 우리 신부님이 그 사실을 알게 되었지.";
			link.l1 = "짐작컨대, 그는 그런 서비스에 반대하지?";
			link.l1.go = "Tomas_3";
		break;

		case "Tomas_3":
			dialog.text = "바로 그렇소. 그는 내게 오직 기도와 주님의 뜻만이 내 딸을 치유할 수 있다고 설득했소. 그리고 내가 이 길에서 벗어나 '마녀'의 도움을 쓴다면 교회에서 파문하겠다고 협박했지. 이해하겠소? 파문이오!";
			link.l1 = "그러면 에스더의 건강이 오로지 신부의 말에 달려 있다는 말인가?";
			link.l1.go = "Tomas_4";
		break;

		case "Tomas_4":
			dialog.text = "나와 내 딸은 교회 근처에 살고 있어. 신앙이 우리에겐 전부야. 만약 그 집시가 실패하면, 나는 딸뿐만 아니라 이 세상에서 남은 내 자리마저 잃게 돼. 사람들은 등을 돌릴 거고, 교회도 우리를 외면할 거야. 에스더와 나는 완전히 고립될 거야.";
			link.l1 = "만약 신부가 허락한다면? 그럼 그 집시가 시도해도 되겠소?";
			link.l1.go = "Tomas_5";
		break;

		case "Tomas_5":
			dialog.text = "그래. 만약 교회가 그녀의 행동을 축복했다면... 나도 그녀를 믿겠어. 도움이 될 만한 일이라면 뭐든 해볼 준비가 되어 있어.";
			link.l1 = "알겠네. 좋아, Thomas, 내가 도와주지. 네 신부와 이야기해 보겠네. 어쩌면 내가 그를 설득할 수 있을지도 모르지.";
			link.l1.go = "Tomas_6";
		break;

		case "Tomas_6":
			dialog.text = "당신이... 정말 우리를 도와주겠다고요? 선장님, 당신의 성공을 위해 기도하겠습니다. 하지만 명심하세요... 우리 신부님은 고집도 세고 원칙도 강해서, 설득하는 게 쉽지 않을 겁니다.";
			link.l1 = "원칙은 설득력 있는 논거로 극복할 수 있지. 기다려, 곧 돌아올 테니까.";
			link.l1.go = "Tomas_7";
		break;

		case "Tomas_7":
			DialogExit();
			AddDialogExitQuestFunction("DWH_Tomas_7");
		break;
		
		case "Tomas_11":
			dialog.text = "...";
			link.l1 = "토마스, 내가 신부를 설득했어.";
			link.l1.go = "Tomas_12";
			DelLandQuestMark(npchar);
		break;

		case "Tomas_12":
			dialog.text = "정말인가? 믿기지 않는군! 그럼 가능한 한 빨리 집시를 초대하자.";
			link.l1 = "물론 그렇게 하겠소, 하지만 한 가지가 있소. 신부님께서는 이것이 당신의 신앙을 흔들지 않기를 바라시며, 진심 어린 참회와 선행을 기대하고 계시오. 그런 선행 중 하나로 본당에 새 종을 구입하는 것이 있을 수 있소.";
			link.l1.go = "Tomas_13";
		break;

		case "Tomas_13":
			dialog.text = "아이고, 선장님... 종 하나 값이 만만치 않소. 아마도 돌아가신 아내의 보석 중에서 뭔가를 내놓아야 할지도 모르겠군. 하지만 에스더를 위해서라면 가진 것 전부, 아니 그 이상이라도 내줄 준비가 되어 있소. 물론 주님께 용서를 구할 것이오. 내가 대장장이에게 가서 주문을 넣고, 집시도 찾아보겠소.\n신부님께 종이 곧 준비될 거라고 꼭 전해 주시오. 필요하다면 땅속을 파서라도 구해오겠소.";
			link.l1 = "좋아, Thomas.";
			link.l1.go = "Tomas_14";
		break;
		
		case "Tomas_14":
			DialogExit();
			AddDialogExitQuestFunction("DWH_Tomas_14");
		break;
		
		case "Tomas_15":
			dialog.text = "...";
			link.l1 = "신부에게 네가 한 말을 전했어. 이제 더 이상 네 길을 막지 않을 테니, 시작해도 돼.";
			link.l1.go = "Tomas_16";
			DelLandQuestMark(npchar);
		break;

		case "Tomas_16":
			dialog.text = "참여해 주셔서 감사합니다, 선장님! 이 오십 두블룬을 받아 주십시오. 지금 내가 드릴 수 있는 건 이것뿐이오, 그리고 내가 가진 전부이기도 하오...";
			link.l1 = "말도 안 돼! 돈 때문에 도와준 게 아니야. 자, 그럼 모든 준비가 끝났으니... 흠... 치료를 시작할까?";
			link.l1.go = "Tomas_16_1";
			link.l2 = "글쎄, 그렇게까지 말한다면... 내가 더 도와줄 일이라도 있나?";
			link.l2.go = "Tomas_16_2";
			
			sld = CharacterFromID("DWH_gypsy");
			LAi_CharacterEnableDialog(sld);
		break;

		case "Tomas_16_1":
			StartInstantDialog("DWH_gypsy", "gypsy_1", "Quest\MiniEvents\DarkWatersOfHealing_dialog.c");
			AddCharacterExpToSkill(pchar, "Leadership", 150);
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			pchar.questTemp.DWH_GoodChoice = true;
		break;
		
		case "Tomas_16_2":
			StartInstantDialog("DWH_gypsy", "gypsy_1", "Quest\MiniEvents\DarkWatersOfHealing_dialog.c");
			AddCharacterExpToSkill(pchar, "Commerce", 150);
			AddItems(pchar, "gold_dublon", 50);
		break;
		
		case "gypsy_1":
			dialog.text = "그 소녀의 건강을 회복시킬 약을 만들려면 망가로사라는 희귀한 식물이 필요하네. 그 식물은 사람의 손이 거의 닿지 않는 곳에서 자라지. 나는 마을 밖에 있는 동굴을 알고 있는데, 그곳엔... 하층민들이 자주 들락거린다네.\n그 자들은 망가로사를 피우려고 태워버리지만, 그 힘을 알지 못하지. 나를 좀 도와주게, "+GetSexPhrase("팔코넷","도비")+", 망가로사를 좀 가져와라, 그거 없이는 아무것도 안 돼.";
			if (CheckAttribute(pchar, "questTemp.Mangarosa"))
			{
				link.l1 = "망가로사? 그 식물은 나도 잘 알고 있지.";
				link.l1.go = "gypsy_VD_manga_1";
			}
			else
			{
				link.l1 = "어떻게 생겼지?";
				link.l1.go = "gypsy_VD_no_manga";
			}
		break;

		case "gypsy_VD_no_manga":
			dialog.text = "꽤 키가 크고 잎이 갈라진 식물인데, 기분 좋으면서도 어지러운 향이 나지. 다른 것과 헷갈릴 일은 없을 거야.";
			link.l1 = "좋아, 내가 이 망가로사를 찾아볼게.";
			link.l1.go = "gypsy_2";
		break;

		case "gypsy_VD_manga_1":
			dialog.text = "너도 그걸 담배에 섞어 피우냐?";
			if (CheckAttribute(pchar, "questTemp.Mangarosa") && pchar.questTemp.Mangarosa == "amelia")
			{
				link.l1 = "아니, 전혀 아니야! 아멜리아라는 치료사가 있는데, 그 여자가 그걸로 정말 사람 정신을 뒤집어 놓을 만한 물약을 만든다네.";
				link.l1.go = "gypsy_VD_manga_1_2";
			}
			else
			{
				link.l1 = "아니, 하지만 망가로사를 몇 번 다뤄본 적은 있어.";
				link.l1.go = "gypsy_VD_manga_2";
			}
		break;

		case "gypsy_VD_manga_1_2":
			dialog.text = "아멜리아를 아는구나? 그래, "+GetSexPhrase("팔코넷","도비")+", 곧 있으면 네가 진짜로 나한테 경쟁을 걸겠구나. 하지만 지금은 그럴 때가 아니야. 가서 망가로사를 가져와. 나는 모든 걸 준비할 테니.";
			link.l1 = "가는 중이다.";
			link.l1.go = "gypsy_2";
			AddCharacterExpToSkill(pchar, "Fortune", 200);
		break;

		case "gypsy_VD_manga_2":
			dialog.text = "보아하니, 너 보통 녀석이 아니구나, "+GetSexPhrase("팔코넷","도비")+". 당신의 지식은 방대하고, 머리는 칼처럼 날카롭구나! 미지의 세계도 두려워하지 않고, 남들이 피하는 것도 기꺼이 받아들이려 하니. 토마스는 당신 같은 이의 도움을 받아 참으로 행운이야. 이제 가서 망가로사를 가져오게, 내가 그 소녀를 치료해 주겠네.";
			link.l1 = "...";
			link.l1.go = "gypsy_2";
		break;
		
		case "gypsy_2":
			DialogExit();
			AddDialogExitQuestFunction("DWH_gypsy_22");
		break;
		
		case "Bandit_1":
			dialog.text = "하하. 내가 말하는데, Mark, 저 녀석은 바보야. 집 문도 안 잠그거든.";
			link.l1 = "그 자의 암탉이 집에 가만히 있지 않을 거라고 확신하나?";
			link.l1.go = "Bandit_2";
			
			locCameraSleep(true);
			sld = CharacterFromID("DWH_Bandit_1");
			CharacterTurnToLoc(sld, "goto", "ass4");
			sld = CharacterFromID("DWH_Bandit_2");
			CharacterTurnToLoc(sld, "goto", "ass2");
		break;
		
		case "Bandit_2":
			DialogExit();
			AddDialogExitQuestFunction("DWH_Bandit_2");
		break;
		
		case "Bandit_3":
			sld = CharacterFromID("DWH_gypsy");
			dialog.text = "오, 오, 신선한 물고기가 우리 그물에 걸렸군! 자, 멍하니 서 있지 말고. 주머니 뒤져 봐, 빨리, 우리가 기분 나빠지기 전에.";
			link.l1 = "진정해라, 도적놈들아. 난 일 때문에 왔다. "+sld.name+" 보냈어. 망가로사가 필요해.";
			link.l1.go = "Bandit_4";

			locCameraSleep(false);
			locCameraFromToPos(3.39, 1.16, -1.80, true, 3.62, -0.50, 3.63);
			sld = CharacterFromID("DWH_Bandit_2");
			CharacterTurnToLoc(sld, "goto", "goto2");
		break;

		case "Bandit_4":
			sld = CharacterFromID("DWH_gypsy");
			dialog.text = "네가 말하지 "+sld.name+" 보냈다고? 좋아, 망가로사 있다. 금화 열 개 내면 가져가라.";
			if (PCharDublonsTotal() >= 10)
			{
				link.l1 = "자, 여기 있어.";
				link.l1.go = "Bandit_5";
			}
			link.l2 = "돈? 뭐 하려고? 나는 자선 따위 안 해. 대신 쇳덩이 두 파운드는 줄 수 있지!";
			link.l2.go = "Bandit_7";
		break;

		case "Bandit_5":
			dialog.text = "좋아, 여기 네 망가로사야. 그리고 기억해, 우릴 본 적 없다는 거야.";
			link.l1 = "헤. 경고는 필요 없었어.";
			link.l1.go = "Bandit_6";
			GiveItem2Character(PChar, "cannabis7");
			RemoveDublonsFromPCharTotal(10);
		break;
		
		case "Bandit_6":
			DialogExit();
			AddDialogExitQuestFunction("DWH_Bandit_6");
		break;
		
		case "Bandit_7":
			DialogExit();
			AddDialogExitQuestFunction("DWH_Bandit_7");
		break;
		
		case "gypsy_3":
			if (CheckCharacterItem(PChar, "cannabis7"))
			{
				dialog.text = "...";
				link.l1 = "한번 봐봐, "+npchar.name+", 이게 네가 필요한 식물이냐?";
				link.l1.go = "gypsy_4";
				DelLandQuestMark(npchar);
			}
			else
			{
				dialog.text = "내가 부탁한 것 가져왔나?";
				link.l1 = "아직 아니야, 지금 처리하고 있어.";
				link.l1.go = "exit";
				NextDiag.TempNode = "gypsy_3";
			}
		break;

		case "gypsy_4":
			dialog.text = "그래, 이거야. 이제 필요한 건 다 모였으니, 시작할 수 있겠군.";
			link.l1 = "...";
			link.l1.go = "gypsy_5";
			TakeItemFromCharacter(pchar, "cannabis7");
		break;

		case "gypsy_5":
			StartInstantDialog("DWH_Tomas", "Tomas_17", "Quest\MiniEvents\DarkWatersOfHealing_dialog.c");
		break;

		case "Tomas_17":
			dialog.text = "빨리 가자, 시간을 허비하면 안 돼.";
			link.l1 = "...";
			link.l1.go = "Tomas_18";
			CharacterTurnByChr(npchar, CharacterFromID("DWH_gypsy"));
		break;

		case "Tomas_18":
			dialog.text = "선장님, 괜찮으시다면 나중에 이야기합시다. 지금은 가장 중요한 순간이니... 치료를 해야 합니다.";
			link.l1 = "물론이지, Thomas. 따님이 빨리 회복하시길 바라네.";
			link.l1.go = "Tomas_19";
			CharacterTurnByChr(npchar, pchar);
		break;
		
		case "Tomas_19":
			DialogExit();
			
			sld = CharacterFromID("DWH_gypsy");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload2", "none", "", "", "", -1);
			
			sld = CharacterFromID("DWH_Tomas");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload2", "none", "", "", "", -1);
			
			LocatorReloadEnterDisable("SentJons_houseS3", "reload2", true);
			LocatorReloadEnterDisable("SentJons_town", "houseS3", true);
			
			AddQuestRecord("DWH", "6");
			SetTimerFunction("DWH_Vizdorovela", 0, 0, 30);
		break;
		
		case "gypsy_6":	// если не прошли проверку ВД у священника
			dialog.text = "...";
			link.l1 = ""+npchar.name+", 토마스가 자의로 당신을 내친 게 아니오. 신부가 당신의 도움을 받으면 파문하겠다고 협박했소.";
			link.l1.go = "gypsy_7";
			DelLandQuestMark(npchar);
		break;

		case "gypsy_7":
			dialog.text = "나는 바로 알았지, "+GetSexPhrase("자기야","아름다움")+", 그가 무거운 마음으로 나에게 그 거절을 전했다네.";
			link.l1 = "교회가 불쾌해하지 않으면서 그를 도울 방법이 있을까?";
			link.l1.go = "gypsy_8";
		break;

		case "gypsy_8":
			dialog.text = "오, "+GetSexPhrase("여보","아름다움")+", 이게 쉬운 일은 아니지만, 길은 내가 잘 알고 있지, 뭘 해야 할지도 알아. 다만, 네 도움이 없으면 할 수 없어, 알겠지.";
			link.l1 = "물론이지, 나만 믿어.";
			link.l1.go = "gypsy_10";
			link.l2 = "미안하다, 검은 눈썹. 하지만 지금은 정말 이럴 시간이 없어. 내가 할 수 있는 건 다 했어. 이제 내 일에 신경 써야겠군.";
			link.l2.go = "gypsy_9";
		break;
		
		case "gypsy_9":
			DialogExit();
			CloseQuestHeader("DWH");
			
			sld = CharacterFromID("DWH_gypsy");
			LAi_CharacterDisableDialog(sld);
			sld.lifeday = 0;
			
			sld = CharacterFromID("DWH_Tomas");
			sld.lifeday = 0;
		break;
		
		case "gypsy_10":
			dialog.text = "그럼 내가 필요한 건 이거야: 그 소녀의 소지품 하나, 독말풀 두 줄기, 아이페캑 한 줄기, 그리고 버베나 한 줄기야. 이걸 모두 가져오면, 내가 그녀를 위한 치유 물약을 만들 수 있어.";
			link.l1 = "좋아, 내가 필요한 건 다 준비할게.";
			link.l1.go = "gypsy_11";
		break;

		
		case "gypsy_11":
			DialogExit();
			AddQuestRecord("DWH", "7");
			
			LAi_CharacterDisableDialog(npchar);
			
			sld = CharacterFromID("DWH_Tomas");
			LAi_SetStayType(sld);
			sld.dialog.filename = "Quest\MiniEvents\DarkWatersOfHealing_dialog.c";
			sld.dialog.currentnode = "Tomas_21";
			AddLandQuestMark(sld, "questmarkmain");
		break;
		
		case "Tomas_21":
			dialog.text = "...";
			link.l1 = "토마스, 유감스럽게도 신부는 내 말을 듣지 않았어. 하지만 집시랑 내가 도와줄 수 있어. 내가 필요한 건...";
			link.l1.go = "Tomas_22";
			DelLandQuestMark(npchar);
		break;

		case "Tomas_22":
			dialog.text = "내가 교회에 맞서라는 말이오?";
			link.l1 = "우리가 조용히 다 처리할 테니 아무도 모를 거요. 곧 당신 딸은 다시 인생을 즐기고, 젊은 아가씨답게 자유롭게 마을을 돌아다닐 수 있을 거요.";
			link.l1.go = "Tomas_23";
			link.l2 = "젠장, Thomas Morrison, 네 딸이 정말 회복하길 바라는 거냐, 아니면 그럴듯한 말 뒤에 숨고 싶은 거냐?";
			link.l2.go = "Tomas_24";
		break;

		case "Tomas_23":
			dialog.text = "좋아, 동의하지. 하지만 제발 조심해서 행동해. 쓸데없는 소문이나 말썽은 원치 않으니까.";
			link.l1 = "물론이지. 그러니 따님이 소중하게 여기는 개인 물건이 필요해.";
			link.l1.go = "Tomas_25";
			AddCharacterExpToSkill(pchar, "Sneak", 200);
		break;

		case "Tomas_24":
			dialog.text = "좋아, 동의하지. 하지만 제발, 조심해서 행동해. 괜한 소문이나 말썽은 원치 않으니까.";
			link.l1 = "물론이죠. 그러니 따님이 소중하게 여기는 개인 물건이 필요합니다.";
			link.l1.go = "Tomas_25";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;

		case "Tomas_25":
			dialog.text = "흠... 그래! 뭐가 통할지 알겠어. 여기서 기다려, 금방 돌아올게.";
			link.l1 = "기다릴게...";
			link.l1.go = "Tomas_26";
		break;

		case "Tomas_26":
			DialogExit();
			SetLaunchFrameFormParam("A few minutes later...", "Run_Function", 0, 4.0);
			SetLaunchFrameRunFunctionParam("DWH_TomasGovotitAgain", 0.0);
			LaunchFrameForm();
		break;
		
		case "Tomas_27":
			dialog.text = "여기 있어. 이건 비취 구슬이야. 에스더는 이걸 절대 빼지 않았지, 그녀에게 정말 소중한 거야.";
			link.l1 = "훌륭해. 이제 기다리기만 하면 돼. 곧 보자, Thomas.";
			link.l1.go = "Tomas_28";
			GiveItem2Character(PChar, "jewelry49");
		break;

		case "Tomas_28":
			DialogExit();
			AddQuestRecord("DWH", "8");

			sld = CharacterFromID("DWH_gypsy");
			LAi_CharacterEnableDialog(sld);
			sld.dialog.filename = "Quest/MiniEvents/DarkWatersOfHealing_dialog.c";
			sld.dialog.currentnode = "gypsy_21";
			AddLandQuestMark(sld, "questmarkmain");
		break;

		case "gypsy_21":
			dialog.text = "필요한 것들 다 구했나?";
			if (GetCharacterItem(pchar, "cannabis1") >= 2 && GetCharacterItem(pchar, "cannabis4") >= 1 && GetCharacterItem(pchar, "cannabis3") >= 1)
			{
				link.l1 = "필요한 건 전부 구했어.";
				link.l1.go = "gypsy_22";
			}
			link.l2 = "내가 뭘 가져와야 하는지 다시 말해 줘.";
			link.l2.go = "gypsy_napomni";
		break;

		case "gypsy_napomni":
			dialog.text = "그럼 내가 필요한 건 이거야: 그 소녀의 소지품 하나, 다투라 두 줄기, 아이페캑 두 줄기, 그리고 버베나 한 줄기야. 이걸 전부 가져오면, 내가 그녀를 위한 약초차를 만들어 줄 수 있어.";
			link.l1 = "좋아, 내가 필요한 건 다 준비할게.";
			link.l1.go = "gypsy_napomni_2";
		break;

		case "gypsy_napomni_2":
			DialogExit();
			NextDiag.TempNode = "gypsy_21";
		break;

		case "gypsy_22":
			dialog.text = "훌륭해. 이제 그 소녀를 위한 치료약을 만들 수 있겠군. 내일 아침은 되어야 완성될 거야. 평소처럼 마을 거리에서 나를 찾으면 된다.";
			link.l1 = "좋아, 그럼 나중에 보자.";
			link.l1.go = "gypsy_23";
			DelLandQuestMark(npchar);
			RemoveItems(pchar, "cannabis1", 2);
			RemoveItems(pchar, "cannabis4", 1);
			RemoveItems(pchar, "cannabis3", 1);
			RemoveItems(pchar, "jewelry49", 1);
		break;
		
		case "gypsy_23":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			AddQuestRecord("DWH", "11");
			SetTimerFunction("DWH_GypsyPrigotovilaZelie", 0, 0, 1);
		break;
		
		case "gypsy_31":
			dialog.text = "...";
			link.l1 = "음, "+npchar.name+", 네 약은 준비됐나?";
			link.l1.go = "gypsy_32";
			DelLandQuestMark(npchar);
		break;

		case "gypsy_32":
			dialog.text = "저기 있다, "+GetSexPhrase("여보","아름다움")+". 저 아가씨에게 이 구슬을 걸고, 이 병에 든 약을 바닥까지 마시게 하시오. 한 달도 지나지 않아 완전히 건강을 되찾을 것이오.";
			link.l1 = "이걸 바로 토마스에게 가져가겠다. 잘 있어라, 검은 눈썹.";
			link.l1.go = "gypsy_33";
			GiveItem2Character(PChar, "quest_potion");
			GiveItem2Character(PChar, "jewelry49");
		break;

		case "gypsy_33":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);

			sld = CharacterFromID("DWH_Tomas");
			LAi_SetStayType(sld);
			sld.dialog.filename = "Quest/MiniEvents/DarkWatersOfHealing_dialog.c";
			sld.dialog.currentnode = "Tomas_31";
			AddLandQuestMark(sld, "questmarkmain");
		break;

		case "Tomas_31":
			if (CheckCharacterItem(PChar, "quest_potion"))
			{
				dialog.text = "...";
				link.l1 = "토머스, 모든 준비가 끝났어. 에스더가 이 구슬을 착용하고 이 약병을 한 번에 다 마셔야 해.";
				link.l1.go = "Tomas_32";
				DelLandQuestMark(npchar);
			}
			else
			{
				dialog.text = "...";
				link.l1 = "...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Tomas_31";
			}
		break;

		case "Tomas_32":
			dialog.text = "감사합니다, "+pchar.name+"! 용서해 주십시오, 저는 단 1분도 허비하고 싶지 않습니다...";
			link.l1 = "물론이지, 물론이야.";
			link.l1.go = "Tomas_33";
			TakeItemFromCharacter(pchar, "quest_potion");
		break;
		
		case "Tomas_33":
			DialogExit();
			
			sld = CharacterFromID("DWH_Tomas");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload2", "none", "", "", "", -1);
			
			LocatorReloadEnterDisable("SentJons_houseS3", "reload2", true);
			LocatorReloadEnterDisable("SentJons_town", "houseS3", true);
			
			AddQuestRecord("DWH", "6");
			SetTimerFunction("DWH_Vizdorovela", 0, 0, 30);
		break;
		
		case "Tomas_41":
			dialog.text = "안녕하시오, "+pchar.name+"! 내 에스테르가 회복됐어! 이제 완전히 건강해졌고, 지금 교회에서 당신과 그 집시를 우리에게 보내주신 주 하나님께 감사드리고 있어!";
			link.l1 = "토마스, 모든 일이 잘 풀려서 정말 기쁘네! 그 소녀를 잘 돌봐 주게, 이제 앞으로 긴 행복한 삶이 기다리고 있으니.";
			link.l1.go = "Tomas_42";
			DelLandQuestMark(npchar);
		break;

		case "Tomas_42":
			dialog.text = "이 삼백 두블론을 받아주십시오. 안타깝게도 이 금액을 마련하려고 빚까지 졌기에 더 드릴 수가 없습니다. 하지만 선장님께 드리는 감사의 마음은 어떤 말이나 금으로도 다 표현할 수 없습니다. 선장님께서는 제게 그녀의 생명에 대한 두려움에서 벗어나게 해주셨을 뿐만 아니라, 우리 가족에게 미래에 대한 희망까지 주셨습니다. 저는 평생 선장님께 빚진 마음으로 살겠습니다!";
			link.l1 = "고마워요! 삼백 두블룬이라니 정말 후한 보상이군요. 이제 마음 놓으세요 - 이미 충분히 감사 인사를 받았으니!";
			link.l1.go = "Tomas_43";
			link.l2 = "네 돈은 안 받아, Thomas. 억지로 주려고도 하지 마! 차라리 어린 Esther에게 예쁜 드레스를 사 줘. 그 아이가 받을 자격이 있으니까.";
			link.l2.go = "Tomas_46";
		break;

		case "Tomas_43":
			dialog.text = ""+pchar.name+", 언제든지 우리를 찾아오시오. 우리 집은 항상 당신을 환영할 것이오. 그리고 집시 여자에게도 말을 걸어보시오, 그 여자가 당신을 보고 싶어 했소.";
			link.l1 = "영광으로 생각하겠소! 이제 떠나야 하오 - 조수는 어느 선장도 기다려주지 않으니.";
			link.l1.go = "Tomas_44";
			AddItems(pchar, "gold_dublon", 300);
			AddCharacterExpToSkill(pchar, "Commerce", 200);
		break;

		case "Tomas_44":
			dialog.text = "물론이지, 물론. 신의 가호가 함께하길, "+GetFullName(pchar)+"!";
			link.l1 = "안녕히 가십시오.";
			link.l1.go = "Tomas_45";
		break;
		
		case "Tomas_45":
			DialogExit();
			
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("SentJons_houseS3", "reload2", false);
			LocatorReloadEnterDisable("SentJons_town", "houseS3", false);
			SetFunctionExitFromLocationCondition("DWH_Vizdorovela_3", PChar.location, false);
			
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);
			NextDiag.CurrentNode = "Tomas_51";
			
			sld = CharacterFromID("DWH_gypsy");
			LAi_CharacterEnableDialog(sld);
			sld.dialog.filename = "Quest\MiniEvents\DarkWatersOfHealing_dialog.c";
			sld.dialog.currentnode = "gypsy_41";
			AddLandQuestMark(sld, "questmarkmain");
		break;
		
		case "Tomas_46":
			dialog.text = "당신은 참으로 고귀한 분이십니다, "+GetFullName(pchar)+"! 성모 마리아께서 함께하시길! 우리 집에 언제든 찾아오시오, 당신은 항상 환영받는 손님이오. 그리고, "+pchar.name+", 집시 여자와 이야기해 봐, 네가 보고 싶다고 했어.";
			link.l1 = "틀림없이 그렇소! 이제 나는 가야 하오 - 바다가 나를 부르고 있소.";
			link.l1.go = "Tomas_47";
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
		break;
		
		case "Tomas_47":
			DialogExit();
			
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("SentJons_houseS3", "reload2", false);
			LocatorReloadEnterDisable("SentJons_town", "houseS3", false);
			SetFunctionExitFromLocationCondition("DWH_Vizdorovela_3", PChar.location, false);
			
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);
			NextDiag.CurrentNode = "Tomas_51";
			
			sld = CharacterFromID("DWH_gypsy");
			LAi_CharacterEnableDialog(sld);
			sld.dialog.filename = "Quest\MiniEvents\DarkWatersOfHealing_dialog.c";
			sld.dialog.currentnode = "gypsy_44";
			AddLandQuestMark(sld, "questmarkmain");
			
			pchar.questTemp.DWH_QuestCompleted = true;
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1;
			
			AddSimpleRumourCity("Have you heard? "+GetFullName(pchar)+" procured a remedy for Thomas Morrison's daughter that miraculously restored the poor girl's health!", "SentJons", 10, 1, "");
			AddSimpleRumourCity("Thomas Morrison lights a candle in the parish daily for the health of "+GetFullName(pchar)+". They say thanks to his (her) efforts, Thomas's daughter was freed from a prolonged illness.", "SentJons", 10, 1, "");
			AddSimpleRumourCity("Esther Morrison has blossomed before our eyes. As if she had never been ill. No one can really explain what made the illness retreat.", "SentJons", 10, 1, "");
		break;
		
		case "gypsy_41":
			dialog.text = "자, 여기 있군, "+GetSexPhrase("팔코넷","도비")+"! 네가 돌아올 줄 알았지. 네 덕분에 그 소녀가 회복해서 이제 비둘기처럼 잘 다닌다네. 온 마을 사람들이 그녀 이야기를 신기해하며 하고 있네.";
			link.l1 = "음, 검은 눈썹, 이건 나만의 공이 아니야 – 너무 칭찬하지 마. 네가 만든 약이 그녀의 건강을 회복시킨 거니까, 네 역할을 깎아내리지 마라.";
			link.l1.go = "gypsy_42";
			DelLandQuestMark(npchar);
		break;

		case "gypsy_42":
			dialog.text = "넌 마음씨가 참 착하구나, "+GetSexPhrase("팔코네트","도비")+", 그리고 예리한 두뇌까지! 너는 위대한 인물이 될 운명이야 – 그게 내 예언이다.";
			link.l1 = "헤... 뭐, 고맙다, "+npchar.name+".";
			link.l1.go = "gypsy_43";
		break;
		
		case "gypsy_43": // плохой вариант
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			AddCharacterExpToSkill(pchar, "Leadership", 200);
			AddQuestRecord("DWH", "9");
			CloseQuestHeader("DWH");
		break;
		
		case "gypsy_44":
			dialog.text = "거기 있었군, "+GetSexPhrase("팔코넷","도비")+"! 네가 다시 여기 나타날 줄 알았지. 네 덕분에 그 소녀가 회복해서 이제 비둘기처럼 날아다닌다네. 온 마을 사람들이 그녀를 칭찬하고 있어.";
			link.l1 = "자, 자, 네가 직접 그 아가씨를 구해 놓고, 내가 모든 공을 가져가길 바란다고? 그건 안 되지! 약도 네가 만들었고, 그녀를 다시 일으켜 세운 것도 너야. 영광은 네가 가져야지.";
			link.l1.go = "gypsy_45";
			DelLandQuestMark(npchar);
		break;

		case "gypsy_45":
			dialog.text = "자네는 마음씨가 곱군, "+GetSexPhrase("팔코넷","도비")+", 그리고 고귀한 영혼이군. 너에게 선물을 하나 주지. 어느 선장이라도 좋아할 만한 거야. 자, 받아. 이제 네 배의 쥐들은 행복도 평화도 없을 거다!";
			link.l1 = "나에게 선물이라고? 이런, 정말 뜻밖이군!";
			link.l1.go = "gypsy_46";
			GiveItem2Character(PChar, "rat_poison");
		break;

		case "gypsy_46":
			if (IsCharacterPerkOn(pchar, "Trustworthy"))
			{
				dialog.text = "그대의 영혼이 맑구나. 순간의 쾌락을 위해 망가로사를 태우지 않을 것임을 알겠어. 만약 급히 그녀가 필요하다면 내게 오게. "+GetSexPhrase("팔코넷","도비")+". 줄기 세 개는 삼백오십 두블론이오\n이 약초는 변덕이 심해서 아무나 구할 수 있는 게 아니오. 그러니 나를 재촉하지 마시오 – 한 달에 한 번 이상은 묻지 마시오, 어차피 구해줄 수 없으니.";
			}
			else
			{
				dialog.text = "그대의 영혼은 맑구나. 어리석지 않은 사람이네. 약초에 대해 웬만한 치료사 못지않게 아는군. 많은 것을 찾을 수 있겠지만, 행운이 늘 따르진 않을 거야. 아무나 찾지 못하는 희귀한 식물이 하나 있는데, 망가로사라고 불리지. 언젠가 그게 필요하다면 나를 찾아오게. "+GetSexPhrase("팔코넷","도비")+". 내가 줄기는 세 개 구해주겠지만, 공짜로는 안 돼 – 삼백오십 두블룬은 받아야겠어\n하지만 이 약초는 고집이 세니, 나를 재촉하지 마. 한 달에 한 번 이상은 묻지 마라 – 네가 운명의 패를 다 펼쳐 보여도, 더 빨리 구해주진 못해.";
			}
			link.l1 = "그래, 고맙다, "+npchar.name+".";
			link.l1.go = "gypsy_47";
		break;
		
		case "gypsy_47": // хороший вариант
			DialogExit();
			NextDiag.CurrentNode = "gypsy_Mangarosa";
			
			AddCharacterExpToSkill(pchar, "Leadership", 200);
			AddQuestRecord("DWH", "10");
			CloseQuestHeader("DWH");
			AddQuestRecordInfo("Useful_Acquaintances", "1");
			
			SetTimerFunction("DWH_Mangarosa", 0, 0, 30);
		break;
		
		case "Tomas_51":
			dialog.text = "선장님, 자꾸 생각이 드는군요 – 이건 분명 주님께서 직접 선장님을 이곳에 제때로 보내주신 게 틀림없습니다! 선장님께서 제 딸을 구해주셨으니, 그 은혜 평생 잊지 않겠습니다.";
			link.l1 = "아마도 그렇겠지, 토마스. 주님의 뜻은 헤아릴 수 없으니.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Tomas_52";
			SetTimerFunction("DWH_Tomas_HelloAgain", 0, 0, 1);
		break;

		case "Tomas_52":
			dialog.text = "와인 좀 드시겠습니까, 선장님? 귀한 손님을 위해 특별한 것이 있습니다.";
			link.l1 = "고맙네, Thomas, 하지만 유감스럽게도 나는 가야 하네.";
			link.l1.go = "exit";
		break;

		case "gypsy_Mangarosa":
			dialog.text = "무슨 일이야, 내 매야?";
			if (CheckAttribute(pchar, "questTemp.DWH_Mangarosa"))
			{
				link.l1 = "말해 봐, 검은 눈썹 녀석, 나한테 망가로사 좀 줄 수 있겠나?";
				link.l1.go = "gypsy_Mangarosa_1";
			}
			link.l2 = "그냥 인사하러 잠깐 들렀어. 이제 가봐야겠어!";
			link.l2.go = "exit";
			NextDiag.TempNode = "gypsy_Mangarosa";
		break;
		
		case "gypsy_Mangarosa_1":
			dialog.text = "나 말고 또 누가, "+GetSexPhrase("여보","아름다움")+", 이런 희귀한 물건을 어떻게 구했냐고? 삼백오십 두블룬이면 네 거다, 딱 세 줄기, 더도 말고 덜도 말고.";
			if (PCharDublonsTotal() >= 350)
			{
				link.l1 = "네 값은 공정하군. 금은 네 거다.";
				link.l1.go = "gypsy_Mangarosa_2";
			}
			link.l2 = "젠장! 내 주머니가 너무 가볍군. 운이 따라줄 때 다시 오겠다.";
			link.l2.go = "exit";
			NextDiag.TempNode = "gypsy_Mangarosa";
		break;

		case "gypsy_Mangarosa_2":
			dialog.text = "그래, 이제 됐다. 가져가라. 그리고 함부로 낭비하지 마라, 알겠지 – 망가로사는 평범한 약초가 아니야, 아무나 감당할 수 없는 힘이 숨겨져 있으니.";
			link.l1 = "걱정 마, 검은 눈썹 녀석, 내가 그 힘을 쓸만한 데 써주지.";
			link.l1.go = "gypsy_Mangarosa_3";
			AddItems(pchar, "cannabis7", 3);
			RemoveDublonsFromPCharTotal(350);
		break;
		
		case "gypsy_Mangarosa_3":
			DialogExit();
			
			NextDiag.CurrentNode = "gypsy_Mangarosa";
			DeleteAttribute(pchar, "questTemp.DWH_Mangarosa");
			SetTimerFunction("DWH_Mangarosa", 0, 0, 30);
		break;
	}
}