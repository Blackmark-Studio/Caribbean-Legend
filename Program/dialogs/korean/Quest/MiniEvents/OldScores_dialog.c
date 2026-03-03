void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;
	bool bOk1, bOk2;
	
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
			dialog.text = "뭘 원하지?";
			link.l1 = "아무것도 아니야.";
			link.l1.go = "exit";
		break;

		case "OS_Matros_sluh":
			bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.OS_Start") && npchar.city == "PuertoPrincipe";
			bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.OS_Start") && npchar.city == "PuertoPrincipe";
			if (bOk1 || bOk2)
			{
				dialog.text = "어젯밤 선술집에서 싸움이 있었다던데... 누가 싸웠는지는 나도 모르겠어. 내 얼굴은 아직 멀쩡하네. 아마도.";
				link.l1 = "여기서 꽤나 술판이 벌어졌던 모양이군?";
				link.l1.go = "OS_Matros_sluh_2";
			}
			else
			{
				switch (rand(2))
				{
					case 0:
						dialog.text = "이봐, "+GetSexPhrase("동료","아가씨")+", 내 부츠 못 봤어? 선술집 탁자 밑에서 뻗어 있는 사이에 어떤 썩을 도둑놈이 훔쳐 갔어.";
						link.l1 = "더 잘 살펴봐라, 아니면 다른 눈도 똑같이 될 테니까.";
						link.l1.go = "exit";
						NextDiag.TempNode = "OS_Matros_sluh";
					break;

					case 1:
						dialog.text = "어제 선술집에서 싸움이 있었다더군... 누가 싸웠는지는 아무도 몰라. 내 얼굴은 멀쩡한 것 같아. 아마도.";
						link.l1 = "아마도 네 얼굴이 이미 충분히 망가졌다고 생각했나 보군.";
						link.l1.go = "exit";
						NextDiag.TempNode = "OS_Matros_sluh";
					break;

					case 2:
						dialog.text = "지옥의 모든 악마가 증인이다, 어제만 해도 내 주머니에 금이 가득했는데! 도대체 지금 어디로 사라진 거야?!";
						link.l1 = "진짜 해적에게는 금이 가장 중요한 보물이 아니지. 자유야말로 훨씬 더 소중한 가치다.";
						link.l1.go = "exit";
						NextDiag.TempNode = "OS_Matros_sluh";
					break;
				}
			}
		break;
		
		case "OS_Matros_sluh_2":
			dialog.text = "오, 그럼! 주점 주인은 손이 열 개라도 모자랐지... 헉... 게다가 말이야... 누가 그의 진을 훔쳐 갔어! 그냥 병 하나가 아니라 통째로 한 통을! 그것도 아무 통이 아니야 — 카리브 해 어디서도 구할 수 없는 거라구! 유럽에서 일부러 가져온 거래. 누구를 위해서였는지는 말 안 하더라만, 한 가지는 확실해: 그걸 빨리 못 찾으면, 불쌍한 주인은 큰일 나게 생겼어!\n";
			link.l1 = "재밌군. 그럼, 몸 조심해라, 이 늙은 주정뱅이.";
			link.l1.go = "exit";
			NextDiag.TempNode = "OS_Matros_sluh";
			OS_Start();
		break;

		case "OS_Matros_again":
			switch (rand(2))
			{
				case 0:
					dialog.text = "뭐 또 원하는 거야? 내 머리통이 곧 터질 것 안 보여? 꺼져.";
					link.l1 = "술을 좀 덜 마시면 만취한 폐인 대신 제대로 된 사내로 보일지도 모르겠군.";
					link.l1.go = "exit";
					NextDiag.TempNode = "OS_Matros_again";
				break;

				case 1:
					dialog.text = "날 내버려 둬... 머리가 터질 것 같아!";
					link.l1 = "네 어깨에 아직도 붙어 있는 게 신기할 정도군.";
					link.l1.go = "exit";
					NextDiag.TempNode = "OS_Matros_again";
				break;

				case 2:
					dialog.text = "저주받을 놈... 나 좀 내버려 둬라, 지금 말할 기분 아닌 거 안 보이냐!";
					link.l1 = "...";
					link.l1.go = "exit";
					NextDiag.TempNode = "OS_Matros_again";
				break;
			}
		break;
		
		case "OS_Matros":
			dialog.text = "물러서! 지금 한계까지 왔다는 거 안 보여? 내 주먹이 누군가의 턱에 한 방 먹이고 싶어서 근질거리거든.";
			link.l1 = "진정해, 선원. 난 어제 선술집에서 무슨 일이 있었는지만 들으려고 하는 거야.";
			link.l1.go = "OS_Matros_2";
			DelLandQuestMark(npchar);
		break;

		case "OS_Matros_2":
			dialog.text = "제기랄! 너 지금 "+GetSexPhrase("그 미친 시녀의 또 다른 애인놈","친척")+"? 뭐야, 돌풍에 휩쓸려 바다에 빠지고 싶어서 온 거냐? 나한테 결투라도 신청하려는 거야? 아니면 지금 당장 칼을 뽑겠다는 거냐?";
			if (pchar.sex == "woman")
			{
				link.l1 = "친척이라고? 전혀 아니지. 그런데 너, 그 여자 별로 대단하게 생각하지 않는 것 같은데?";
				link.l1.go = "OS_Matros_3_scrit";
			}
			else
			{
				link.l1 = "연인? 그건 아니지. 저 계집은 정복한 남자 수만 따지는 것 같지 않나?";
				link.l1.go = "OS_Matros_3_scrit";
				link.l2 = "그 여자의 일은 내 알 바 아니야. 그냥 무슨 일이 있었는지만 말해, 그럼 널 내버려둘게. 네가 그 여자를 그렇게 분노하게 만든 거지, 안 그래?";
				link.l2.go = "OS_Matros_3_fortuna";
			}
		break;
		
		case "OS_Matros_3_scrit":
			dialog.text = "그 악녀는 바다에서 몇 달 굶은 선원만큼이나 분별이 없어 - 가까운 거부터 집어 들고 나중에 정리하지! 저녁 내내 나한테 추파를 던지더니, 선술집 고양이처럼 남은 음식 노리며 들이대더라고. 그런데 내가 그녀의 항구에 닻을 내리려 하자마자, 비명 소리가 얼마나 컸던지 만에 있는 물고기들까지 깊은 곳으로 도망쳤다니까!";
			link.l1 = "혹시 럼을 너무 많이 마셔서 지나치게 들이댄 건 아니었소?";
			link.l1.go = "OS_Matros_4";
			AddCharacterExpToSkill(pchar, "Sneak", 100);
		break;

		case "OS_Matros_3_fortuna":
			dialog.text = "그 악녀는 바다에서 몇 달 굶은 선원만큼이나 가리는 게 없어 – 눈앞에 있는 거부터 집어 들고 나중에 생각하지! 저녁 내내 나한테 눈길을 주고, 선술집 고양이처럼 추파를 던지더니 말이야. 그런데 내가 그녀의 항구에 닻을 내리려고 하자마자, 비명 소리가 얼마나 컸던지 만에 있는 물고기들까지 깊은 데로 도망쳤다니까!";
			link.l1 = "혹시 럼주를 너무 많이 마셔서 지나치게 들이댄 건 아니었나?";
			link.l1.go = "OS_Matros_4";
			AddCharacterExpToSkill(pchar, "Fortune", 100);
		break;

		case "OS_Matros_4":
			dialog.text = "술에 좀 취했을지도 모르지만, 그곳에서 무슨 일이 있었는지는 잔잔한 바다처럼 또렷이 기억나. 내가 그 여자를 쫓은 게 아니야 – 오히려 그 여자가 피 냄새 맡은 상어처럼 나를 맴돌았지. 하루 종일 내 주변을 빙빙 돌고 있었다고!";
			if (pchar.sex == "woman")
			{
				link.l1 = "그렇게 사소한 일로 처음 만난 사람과 싸울 준비가 된 거요? 아니면 그날 저녁에 또 다른 일이 있었소?";
			}
			else
			{
				link.l1 = "이봐, 너 방금 '또 다른 연인'이라고 했지. 그녀의 바람기에 대해 뭔가 아는 거냐?";
			}
			link.l1.go = "OS_Matros_5";
		break;

		case "OS_Matros_5":
			dialog.text = "그녀의 비명이 잦아든 뒤, 내 동료들은 내가 그녀 주변에서 낚시질하려는 건 시간 낭비라고 하더군. 그녀는 우리 선장이랑 죽이 잘 맞는 동네 구혼자가 있다고 했지.";
			link.l1 = "흥미롭군. 또 다른 이상한 점은 못 봤나? 소란 중에 누가 바 카운터로 다가오는 걸 본 적은?";
			link.l1.go = "OS_Matros_6";
		break;

		case "OS_Matros_6":
			dialog.text = "빌어먹을... 머리가 암초에 부딪힌 선체처럼 쪼개질 것 같군, 그런데 네놈은 또 저주스러운 질문을 해대고 있잖아. 난 아무것도 못 봤고, 아무 소리도 못 들었어. 이런 심문으로 노련한 선원을 괴롭히지 말고 페소나 좀 쥐여주는 게 낫지 않겠냐.";
			if (sti(pchar.Money) >= 100)
			{
				link.l1 = "여기 백 페소다. 또 술에 취해 정신 못 차리고 그 시중드는 아가씨한테 홀리지 말라고, 알겠지?";
				link.l1.go = "OS_Matros_7_harizma";
			}
			link.l2 = "내 돈 없이도 잘 버틸 거야. 아니면 또 술에 취해서 그 여종업원이나 귀찮게 굴겠지.";
			link.l2.go = "OS_Matros_7_fortuna";
		break;
		
		case "OS_Matros_7_harizma":
			DialogExit();
			
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			AddQuestRecord("OS", "3");
			AddMoneyToCharacter(pchar, -100);
			pchar.questTemp.OS_Tavern_2 = true;
			AddLandQuestMark(characterFromId("PuertoPrincipe_waitress"), "questmarkmain");
			
			for (i=1; i<=3; i++)
			{
				if (CharacterIsAlive("OS_Matros_"+i))
				{
					sld = CharacterFromID("OS_Matros_"+i);
					sld.dialog.filename = "Quest\MiniEvents\OldScores_dialog.c";
					sld.dialog.currentnode = "OS_Matros_again";
				}
			}
		break;
		
		case "OS_Matros_7_fortuna":
			DialogExit();
			
			AddCharacterExpToSkill(pchar, "Fortune", 100);
			AddQuestRecord("OS", "3");
			pchar.questTemp.OS_Tavern_2 = true;
			AddLandQuestMark(characterFromId("PuertoPrincipe_waitress"), "questmarkmain");
			
			for (i=1; i<=3; i++)
			{
				if (CharacterIsAlive("OS_Matros_"+i))
				{
					sld = CharacterFromID("OS_Matros_"+i);
					sld.dialog.filename = "Quest\MiniEvents\OldScores_dialog.c";
					sld.dialog.currentnode = "OS_Matros_again";
				}
			}
		break;
		
		case "OS_Dialog_1":
			if (pchar.sex == "woman")
			{
				dialog.text = "이봐, 잭! 네 방에 부두 창녀가 있잖아! 하하! 저 여자 좀 봐라—참 매력적인 악마로군! 궁금한데, 우리 보물상자를 다 뒤졌을까, 아니면 우리가 제일 재미있는 순간에 방해한 건가?";
				link.l1 = "...";
			}
			else
			{
				dialog.text = "이봐, 잭! 여기 좀 봐라 - 도둑질하는 쥐새끼가 있잖아! 하하! 이 악당 좀 봐라! 벌써 우리 해상 상자 뒤지고 있었네, 이 비열한 놈이?";
				link.l1 = "...";
			}
			link.l1.go = "OS_Dialog_2";
		break;

		case "OS_Dialog_2":
			StartInstantDialog("OS_Jack", "OS_Dialog_3", "Quest\\MiniEvents\\OldScores_dialog.c");
		break;

		case "OS_Dialog_3":
			if (pchar.sex == "woman")
			{
				dialog.text = "대담한 작은 암탉이군. 잭 베일스의 소굴에 쳐들어오다니, 감히 그렇게 할 놈은 많지 않아. 그런데 여기엔 무슨 일로 온 거지, 이쁜이? 우리를 좀 즐겁게 해줄 생각이었나?";
				link.l1 = "즐겁게 해달라고? 하! 너희들 참 꿈도 크구나, 양반들. 난 네놈들이 훔친 걸 되찾으러 왔다. 정말로 너희 그 한심한 연극이 들키지 않을 거라 생각했냐?";
			}
			else
			{
				dialog.text = "참 대담한 놈이군. 잭 베일스의 집에 침입하다니 감히 시도할 자가 많지 않지. 자, 여기서 무슨 용건이냐?";
				link.l1 = "그냥 내가 도둑맞은 물건을 되찾고 있다고 해두지. 아니면 너희 양반들이 그 보잘것없는 연극이 들키지 않을 거라고 진심으로 믿었나?";
			}
			link.l1.go = "OS_Dialog_4";
		break;

		case "OS_Dialog_4":
			StartInstantDialog("OS_capWolf", "OS_Dialog_5", "Quest\MiniEvents\OldScores_dialog.c");
		break;

		case "OS_Dialog_5":
			if (pchar.sex == "woman")
			{
				dialog.text = "한심한 짓거리라고?! 악마가 날 구워 먹을지어다, 내가 네놈을 산 채로 가죽을 벗겨 돛으로 써주마! 하하! 하지만 먼저... 우리랑 좀 재미 좀 볼까?";
				link.l1 = "네놈들, 저승사자를 빨리 만나고 싶나 보군? 좋아, 오래 기다리게 하지 않겠다 - 덤벼라, 이 더러운 놈들아!";
			}
			else
			{
				dialog.text = "한심한 연극이라고? 망할 놈, 네 등가죽을 벗겨 돛천으로 써 주마! 말은 그만, 이제 네 놈의 시간이 끝났어, 이 비참한 개새끼야!";
				link.l1 = "네가 그렇게 원한다면, 덤벼라, 악당들아!";
			}
			link.l1.go = "OS_Dialog_bitva";
		break;
		
		case "OS_Dialog_bitva":
			DialogExit();
			
			LAi_LocationFightDisable(loadedLocation, false);
			LAi_SetFightMode(pchar, true);
			
			sld = CharacterFromID("OS_Jack");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			sld = CharacterFromID("OS_capWolf");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheckFunction("EnemyFight", "OS_VernuliBochonok");
		break;
		
		case "Zaharia_1":
			sld = CharacterFromID("PuertoPrincipe_tavernkeeper");
			dialog.text = ""+sld.name+", 내 진 어디 있지?! 없으면 내가 직접 너를 항구 바닥에 물고기 밥으로 보내버릴 거야!";
			link.l1 = "...";
			link.l1.go = "Zaharia_2";
			CharacterTurnByChr(npchar, sld);
			//locCameraFromToPos(-2.53, 2.00, 1.26, false, 0.03, 0.00, -1.11);
		break;

		case "Zaharia_2":
			sld = CharacterFromID("PuertoPrincipe_tavernkeeper");
			dialog.text = "...";
			link.l1 = "내가 직접 방금 전달했어. 여기 있어.";
			link.l1.go = "Zaharia_3";
			CharacterTurnByChr(npchar, pchar);
			TakeItemFromCharacter(pchar, "cask_gin");
			notification("You gave the barrel of gin", "NONE");
		break;

		case "Zaharia_3":
			sld = CharacterFromID("PuertoPrincipe_tavernkeeper");
			dialog.text = "내가 너를 믿은 게 헛된 일이 아니어서 다행이군, "+sld.name+". 내일 내 방으로 와서 두블룬을 받아가라.";
			link.l1 = "...";
			link.l1.go = "Zaharia_4";
			CharacterTurnByChr(npchar, sld);
		break;
		
		case "Zaharia_4":
			DialogExit();
			
			//ChangeShowIntarface();
			LAi_SetStayType(pchar);
			
			sld = CharacterFromID("OS_Zaharia");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1", "", "", "", "", -1);
			sld.lifeday = 0;
			sld.location = "None";
			
			DoQuestFunctionDelay("OS_RazgovorTavern", 1.5);
		break;
		
		case "Tavern_1":
			dialog.text = "선장님, 그 명패 말인데...";
			link.l1 = "무슨 명패? 아, 그거 말이오... 솔직히 그런 영예는 필요 없소. 나 때문에 일부러 신경 쓸 것 없소.";
			link.l1.go = "Tavern_2";
		break;

		case "Tavern_2":
			dialog.text = "훨씬 더 좋은 걸 줄 수 있소! 오늘부터 내 선술집에서 숙박과 술은 언제나 공짜요! 그대만큼 훌륭한 사람이라면 이 정도 대접은 당연하지!";
			link.l1 = "이제야 내 마음에 드는군! 이런 특권이라면 진심으로 환영이지! 다시 만날 때까지, "+npchar.name+".";
			link.l1.go = "Tavern_3";
		break;
		
		case "Tavern_3":
			DialogExit();
			
			LAi_SetPlayerType(pchar);
			AddQuestRecord("OS", "5");
			AddQuestUserData("OS", "sSex", GetSexPhrase("","а"));
			pchar.questTemp.OS_Tavern_FreeBuhlo = true;
			ChangeShowIntarface();
			
			sld = CharacterFromID("PuertoPrincipe_tavernkeeper");
			sld.dialog.filename = "Common_Tavern.c";
			sld.dialog.currentnode = "First Time";
			LAi_SetBarmanType(sld);
			LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
			
			for (i=1; i<=3; i++)
			{
				if (CharacterIsAlive("OS_Matros_"+i))
				{
					sld = CharacterFromID("OS_Matros_"+i);
					sld.lifeday = 0;
				}
			}
			
			PChar.quest.OS_AttackSea.win_condition.l1 = "location";
			PChar.quest.OS_AttackSea.win_condition.l1.location = "Cuba1";
			PChar.quest.OS_AttackSea.function = "OS_AttackSea";
			
			// вражеский корабль атакует в море
			sld = CharacterFromID("OS_Pirate");
			DeleteAttribute(sld, "AlwaysFriend");
			DeleteAttribute(sld, "ShipEnemyDisable");
			sld.AlwaysEnemy = true;
			LAi_SetImmortal(sld, false);
			
			PChar.quest.TPZ_Potopil.win_condition.l1 = "NPC_Death";
			PChar.quest.TPZ_Potopil.win_condition.l1.character = "OS_Pirate";
			PChar.quest.TPZ_Potopil.function = "OS_Pobeda";
		break;
		
		
		
		
		
		
		
	}
}