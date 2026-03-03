// Чад Каппер - боцман Акулы и тюремщик
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
			dialog.text = "뭐 원하는 거라도 있어?";
			link.l1 = "아니, 아무것도 없어.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// вариант R
		case "Chimiset":
			dialog.text = "흠, 흠... 네가 그 수상한 도둑이란 말이지? 음... 평범한 좀도둑처럼은 안 보이는데.";
			link.l1 = "나리, 착각하셨소. 나는 여기 온 지 얼마 안 된 사람이오. 그러니 당신 사람들이 나를 붙잡은 그 화물창이 당신 소유라는 걸 어떻게 알겠소?";
			link.l1.go = "Chimiset_1";
		break;
		
		case "Chimiset_1":
			dialog.text = "정말이야? 웃기는 소리 하네, 이봐... 그럼 어디서 여기로 온 거지?";
			link.l1 = "스페인 본토에서, 인디언 우상을 거쳐서... 어떻게 설명해야 할지 잘 모르겠어...";
			link.l1.go = "Chimiset_2";
		break;
		
		case "Chimiset_2":
			dialog.text = "조각상? 하하! 넌 참 웃기는 녀석이구나...? 내가 한 번 맞혀볼까: 네가 우리 창고에 몰래 들어오려고 배 선체에 난 구멍으로 헤엄쳐 들어왔지. 그런데 얼굴이 낯선데? 나는 리바도스 놈들은 다 아는데...";
			link.l1 = "리바도스? 무슨 말인지 전혀 모르겠어! 이봐, 나 여기 온 지 한 시간쯤 됐다고--";
			link.l1.go = "Chimiset_3";
		break;
		
		case "Chimiset_3":
			dialog.text = "소리 지르지 마, 나 귀 안 먹었어. 아니, 네가 존나 웃기긴 한데, 난 그냥 널 좀 더 썩게 둘 생각이야. 쥐들이 네 발가락을 갉아먹고 나면, 생각이 좀 달라질지도 모르지.";
			link.l1 = "나는 이 리바도스에 대해 아무것도 몰라! 내 이름은 샤를 드 모르야!";
			link.l1.go = "Chimiset_4";
		break;
		
		case "Chimiset_4":
			dialog.text = "흠... 네 말이 사실일지도 모르겠군... 리바도스는 백인들과 어울리는 일이 드물지. 솔직하게 대답해... 너도 그들 중 한 명이냐?";
			link.l1 = "맹세코, 그 이름은 처음 들어봐! 난 누구랑도 한패가 아니야!";
			link.l1.go = "Chimiset_5";
		break;
		
		case "Chimiset_5":
			dialog.text = "정말이냐? 좋아, 증명해 봐라. 아래층으로 내려가면 우리 리바도스가 우리 안에 앉아 있다. 위험한 마법사다. 그놈을 죽이면 내가 믿어주지.\n그리고 네가 우리 창고에 무단침입한 일도 잊어주마. 자, 어떻게 할래? 겁먹지 마라, 그 마법사는 무기도 없고 약하다. 뭐... 주문 한 방에 널 먼지로 만들어버릴 수도 있지만, 하하...";
			link.l1 = "내가 본 걸 네가 봤다면, 농담 따위 안 했을 거야--";
			link.l1.go = "Chimiset_6";
		break;
		
		case "Chimiset_6":
			dialog.text = "좋아, 그만해! 이 일을 할 거야, 말 거야? 할 거면 이 마체테를 들고 마법사를 베어라. 아니면 타르타로스의 심연에서 죽게 될 거다. 알겠어?";
			link.l1 = "... 마체테를 줘.";
			link.l1.go = "Chimiset_7";
		break;
		
		case "Chimiset_7":
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "slave_02");
			EquipCharacterbyItem(pchar, "slave_02");
			dialog.text = "착하지. 이제 가서 그 흑인 부두교 주술사를 죽여. 그의 우리 문은 열려 있다. 멍청한 짓 하지 마라 - 네가 도망칠 생각만 해도 우린 주저 없이 널 끝장낼 거다. 어서 가!";
			link.l1 = "이 녹슨 고물로 너희 놈들 배라도 갈라버릴까 봐 겁나냐?";
			link.l1.go = "Chimiset_8";
		break;
		
		case "Chimiset_8":
			dialog.text = "내 인내심도 바닥나고 있어, 이봐. 화물 창고로 가서 시키는 대로 해!";
			link.l1 = "알았어, 알았어, 간다...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Chimiset_9";
			LAi_SetPlayerType(pchar);
			bDisableCharacterMenu = false;//разлочим Ф2
		break;
		
		case "Chimiset_9":
			dialog.text = "내 인내심을 시험하는군, 이 멍청아! 나를 화나게 하고 싶지 않을 거다...";
			link.l1 = "아, 알았어, 진정해.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Chimiset_9";
		break;
		
		case "Fightfail_Final":
			dialog.text = "흑인을 죽였나? 좋아... 다행이군. 네가 리바도스가 아니라는 걸 증명했어.";
			link.l1 = "이 지긋지긋한 배에서 드디어 풀려나는 건가? 상어 도드슨을 당장 만나야겠어.";
			link.l1.go = "Fightfail_Final_1";
		break;
		
		case "Fightfail_Final_1":
			dialog.text = "그를 보게 될 거야... 지옥으로 가는 길에서.";
			link.l1 = "... 젠장.";
			link.l1.go = "Fightfail_Final_2";
		break;
		
		case "Fightfail_Final_2":
			DialogExit();
			DoQuestCheckDelay("LSC_ChadGuardAttack_Fail", 0.1);
		break;
		
		// вариант N
		case "prisoner":
			dialog.text = "하! 이것 좀 봐라. 내 감옥에서 뭐 하고 있지?";
			link.l1 = "네 이름이 챈드 캐퍼 맞지? 나는 "+GetFullName(pchar)+", 샤크 도드슨을 대신해서 왔어. 그가 열쇠를 줬지.";
			link.l1.go = "prisoner_1";
		break;
		
		case "prisoner_1":
			dialog.text = "제독이 널 보냈다고? 흠. 이제 그의 새로운 심부름꾼이냐?";
			link.l1 = "입 조심해, 나리... 아니면 그 혀를 잃게 될 거야. 난 누구의 심부름꾼이 아니야.";
			link.l1.go = "prisoner_2";
		break;
		
		case "prisoner_2":
			dialog.text = "하하! 너 마음에 드는군, 친구. 내가 한 말은 잊어버려... 그런데, 여기서 무슨 일로 온 거야?";
			link.l1 = "샤크가 치미셋을 풀어주라고 명령했어.";
			link.l1.go = "prisoner_3";
		break;
		
		case "prisoner_3":
			dialog.text = "리바도스 부두교 주술사 말인가? 흠, 그거 이상하군... 정말 놀랄 소식이야...";
			link.l1 = "상어가 리바도스와 화해하고 싶어 해.";
			link.l1.go = "prisoner_4";
		break;
		
		case "prisoner_4":
			dialog.text = "아-아, 알겠어... 좋아. 리바도스에 사람을 보낼게; 그들이 자기네 마법사를 데려가라고 해.";
			link.l1 = "왜 그냥 그를 풀어줄 수 없는 거지?";
			link.l1.go = "prisoner_5";
		break;
		
		case "prisoner_5":
			dialog.text = "내가 할 수야 있지... 하지만 그러면 그를 죽게 만드는 셈이야. 치미셋은 이 근방에서 유명한 인물이거든. 그가 에스메랄다 갑판, 즉 그의 적인 나르발의 영역에 발을 디디는 순간 목숨을 잃게 될 거야.\n타르타로스를 떠날 다른 방법은 없어, 그리고 우리가 그 노인을 섬 주변으로 헤엄치게 할 수도 없잖아! 만약 그에게 무슨 일이라도 생기면, 리바도스가 우리를 탓할 거야—특히 나를 말이지!\n그런 골치 아픈 일은 싫으니까, 그의 안전을 그의 부족이 책임진다면 그때만 그를 풀어주겠어. 네가 직접 치미셋과 얘기하고 싶다고? 꽤나 독특한 인물이야...";
			if (CheckAttribute(npchar, "quest.chimiset_talk")) link.l1 = "나는 이미 그와 얘기했어. 정말 이상한 사람이더군... 자, 이제 가봐야겠어. 잘 있어, 채드.";
			else link.l1 = "그럴 생각이오. 지금 그를 만나러 가겠소.";
			link.l1.go = "prisoner_6";
		break;
		
		case "prisoner_6":
			DialogExit();
			sld = characterFromId("Chimiset");
			sld.quest.capper_talk = "true"; // разговор с Каппером состоялся
			if (!CheckAttribute(npchar, "quest.chimiset_talk")) chrDisableReloadToLocation = true;//закрыть локацию
			else chrDisableReloadToLocation = false;//открыть локацию
			NextDiag.CurrentNode = "prisoner_7";
		break;
		
		case "prisoner_7":
			dialog.text = "리바도스에게 심부름꾼을 보내서 그들이 부두교 주술사를 데려가게 할 거야. 걱정 마, 친구, 이제 가도 돼.";
			link.l1 = "좋아.";
			link.l1.go = "exit";
			NextDiag.TempNode = "prisoner_7";
		break;
		
		// вариант M
		case "Aeva_attack":
			dialog.text = "... 벌써 그 놈이 통을 열었겠지, 분명해. 걔가 제일 좋아하는 위스키야: 부쉬밀스. 곧 끝날 거야, 내가 그 통에 코끼리도 죽일 만큼 비소를 넣었으니까...";
			link.l1 = "";
			link.l1.go = "Aeva_attack_1";
			CharacterTurnToLoc(npchar, "quest", "quest2");
		break;
		
		case "Aeva_attack_1":
			dialog.text = "음? 젠장, 여기서 뭐 하는 거야?! 꺼져!";
			link.l1 = "널 찾고 있었지, 독쟁이. 이상하군, 외눈박이는 안 보이네... 상어의 자리를 차지하고 싶었던 거 맞지?";
			link.l1.go = "Aeva_attack_2";
			CharacterTurnByChr(npchar, pchar);
		break;
		
		case "Aeva_attack_2":
			dialog.text = "하하, 상어는 아마 이미 죽었겠지! 그리고 너도 곧 그놈 곁에 가게 될 거다, 첩자 놈아!";
			link.l1 = "...";
			link.l1.go = "Aeva_attack_fight";
		break;
		
		case "Aeva_attack_fight":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			for (i=1; i<=3; i++)
			{
				sld = CharacterFromID("ChadNarval_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "LSC_CapperDieAeva");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "Aeva_attack_2":
			dialog.text = "... 이건 정말 지옥 같은 술판이 되겠군. 샤크는 이 위스키를 얼마나 오래 꿈꿔왔는지, 한 번에 들이켜 버릴 거야. 비소는 어디 있지? 확실하게 하려면 두 병을 쓰자... 그러면 우리 친구 파지오가 이 통을 정의의 섬의 나리발들이 준 선물이라며 제독에게 전해줄 수 있겠지, 하하!\n맞지, 주세페? 기운 내, 친구야. 제대로만 하면 걱정할 거 없어-- 아! 손님이 왔군, 얘들아! 뭘 원하지, 이 멍청아? 여긴 사적인 모임이야.";
			link.l1 = "네 계획은 실패했어, 카퍼. 너랑 네 친구 마르첼로가 뭘 하려는지 다 알고 있어. 비소를 버려! 샤크를 독살하게 두지 않을 거야!";
			link.l1.go = "Aeva_attack_3";
		break;
		
		case "Aeva_attack_3":
			dialog.text = "아, 젠장. 좋아... 네가 먼저 죽고, 그다음은 샤크다! 무기 들어, 녀석들!";
			link.l1 = "...";
			link.l1.go = "Aeva_attack_fight";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}
