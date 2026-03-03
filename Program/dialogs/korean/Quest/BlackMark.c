void ProcessDialogEvent()
{
	ref NPChar, sld, rItm, rItem;
	aref Link, NextDiag, rType;
	int i, n;
	string sTemp, sStr, sStr2, sGun, sBullet, attrL;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	sAttr = Dialog.CurrentNode;
	if (findsubstr(sAttr, "SetGunBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	NPChar.SetGunBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
 	    Dialog.CurrentNode = "SetGunBullets2";
 	}
	if (findsubstr(sAttr, "SetMusketBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	NPChar.SetMusketBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
 	    Dialog.CurrentNode = "SetMusketBullets2";
 	}

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
		
		case "BM_Contra_1":
			dialog.text = "너 누구야, 그리고 대체 여기서 뭐하고 있는 거야?!";
			if (sti(pchar.reputation.nobility) >= 40)
			{
				link.l1 = "진정해, 친구. 그냥 지나가는 길이야. 네가 하는... 뭐든지 간섭할 생각 없어.";
			}
			else
			{
				link.l1 = "어? 이 등대가 네 거냐? 다음엔 야자수에 네 이름이라도 써 붙이든가, 아니면 빌어먹을 울타리라도 세워 놔라.";
			}
			link.l1.go = "BM_Contra_2";
			DelLandQuestMark(npchar);
		break;
		
		case "BM_Contra_2":
			if (sti(pchar.reputation.nobility) >= 40)
			{
				dialog.text = "여기서 꺼져! 네가 손님을 겁줘서 거래를 망치기라도 하면, 나…";
			}
			else
			{
				dialog.text = "이봐, 꼬마야, 나랑 내 놈들이 네 칼이 네 혓바닥만큼 날카로운지 시험하게 만들지 마. 그냥 꺼져주고...";
			}
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_BarbadosPatrolPribegaet");
		break;
		
		case "BM_Contra_3":
			dialog.text = "그래, 프랭키, 어느 쪽이야?";
			link.l1 = "...";
			link.l1.go = "BM_Contra_3_1";
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "dialog_stay12", "1", 1.9);
		break;
		case "BM_Contra_3_1":
			StartInstantDialog("BM_PatrolZhitel", "BM_Contra_4", "Quest\BlackMark.c");
		break;
		
		case "BM_Contra_4":
			dialog.text = "아니... 젠장, 저 얼굴들 중에 아는 놈 하나도 없는데.";
			link.l1 = "...";
			link.l1.go = "BM_Contra_4_1";
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "dialog_stay15", "1", 1.9);
		break;
		case "BM_Contra_4_1":
			StartInstantDialog("BM_PatrolOff", "BM_Contra_5", "Quest\BlackMark.c");
		break;
		
		case "BM_Contra_5":
			dialog.text = "뭐라고?! 정말이야?";
			link.l1 = "...";
			link.l1.go = "BM_Contra_5_1";
			CharacterTurnByChr(npchar, CharacterFromID("BM_PatrolZhitel"));
		break;
		case "BM_Contra_5_1":
			StartInstantDialog("BM_PatrolZhitel", "BM_Contra_6", "Quest\BlackMark.c");
		break;
		
		case "BM_Contra_6":
			dialog.text = "내가 눈이 멀었다고 생각하나?! 내가 말하고 있잖아, 뭐...";
			link.l1 = "...";
			link.l1.go = "exit";
			CharacterTurnByChr(npchar, CharacterFromID("BM_PatrolOff"));
			CharacterTurnByChr(CharacterFromID("BM_PatrolOff"), CharacterFromID("BM_PatrolZhitel"));
			AddDialogExitQuest("BM_BarbadosMayakVystrel");
		break;
		
		case "BM_Contra_7":
			dialog.text = "이게 뭐야?!";
			link.l1 = "...";
			link.l1.go = "BM_Contra_7_1";
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "dialog_stay9", "1", 1.9);
			CharacterTurnByChr(npchar, CharacterFromID("BM_Contra_1"));
		break;
		
		case "BM_Contra_7_1":
			StartInstantDialog("BM_Contra_1", "BM_Contra_8", "Quest\BlackMark.c");
		break;
		
		case "BM_Contra_8":
			dialog.text = "누가 쐈어?!";
			link.l1 = "...";
			link.l1.go = "BM_Contra_8_1";
			locCameraFromToPos(-84.11, 6.33, -62.68, true, -78.07, 3.20, -66.67);
			CharacterTurnByChr(npchar, CharacterFromID("BM_PatrolOff"));
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "dialog_stay13", "1", 1.9);
		break;
		
		case "BM_Contra_8_1":
			StartInstantDialog("BM_PatrolOff", "BM_Contra_9", "Quest\BlackMark.c");
		break;
		
		case "BM_Contra_9":
			dialog.text = "우릴 바보로 아나, 이 쓰레기들아? 전부 총 내려놔! 너도 마찬가지야!";
			link.l1 = "...";
			link.l1.go = "BM_Contra_9_1";
			CharacterTurnByChr(npchar, CharacterFromID("BM_Contra_1"));
		break;
		
		case "BM_Contra_9_1":
			StartInstantDialog("BM_Contra_1", "BM_Contra_10", "Quest\BlackMark.c");
		break;
		
		case "BM_Contra_10":
			dialog.text = "진정 좀 하시오, 장교 양반. 우리 짓이 아니란 거 안 보이오? 우리 총은 원래 있던 자리에 그대로 있소. 그리고 당신 총에는 손대지 마시오!";
			link.l1 = "...";
			link.l1.go = "BM_Contra_10_1";
			CharacterTurnByChr(npchar, CharacterFromID("BM_PatrolOff"));
		break;
		case "BM_Contra_10_1":
			StartInstantDialog("BM_PatrolOff", "BM_Contra_11", "Quest\BlackMark.c");
		break;
		
		case "BM_Contra_11":
			dialog.text = "네가 나한테 명령하는 거냐, 이 자식아?! 당장 저놈들 전부 체포해라!";
			link.l1 = "...";
			link.l1.go = "BM_Contra_11_1";
			CharacterTurnByChr(npchar, CharacterFromID("BM_Contra_1"));
		break;
		
		case "BM_Contra_11_1":
			StartInstantDialog("BM_Contra_1", "BM_Contra_12", "Quest\BlackMark.c");
		break;
		
		case "BM_Contra_12":
			dialog.text = "꺼져라! 그럴 일은 없어. 얘들아, 무기 들어!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_BarbadosMayakBoinya");
			CharacterTurnByChr(npchar, CharacterFromID("BM_PatrolOff"));
		break;
		
		case "BM_Irons_1":
			dialog.text = "이봐, 이봐, 조심해! 그렇게 칼을 마구 휘두르다간 누가 다칠 수도 있잖아.";
			link.l1 = "하, 누구?";
			link.l1.go = "BM_Irons_2";
			LAi_SetCurHPMax(npchar);
			SetOfficerToMushketer(npchar, "mushket1", true);
		break;
		
		case "BM_Irons_2":
			dialog.text = "당연히 나지.";
			link.l1 = "뭐야...? 너 대체 누구야?";
			link.l1.go = "BM_Irons_4";
			link.l2 = "그게 바로 내가 하려는 거야. 갈까?";
			link.l2.go = "BM_Irons_3";
		break;
		
		case "BM_Irons_3":
			DialogExit();
			AddDialogExitQuestFunction("BM_Irons_DlgExit_1");
		break;
		
		case "BM_Irons_4":
			if (startHeroType == 4)
			{
				dialog.text = "나는 토미야! 토미 아이언스지. 아마도. 너는 누구야? 그렇게 돌아다니는 걸 보니 참 대담한 여자네, 내가 말하는데, 헤헤헤.";
				link.l1 = "용감하긴 하군. 그리고 필요하다면 네 입도 닫게 할 수 있어. 여긴 더운 곳이라 옷을 가볍게 입는 거지, 너나 네 부류를 즐겁게 해주려고 그런 건 아니야. 내 이름은 헬렌 맥아더야. 친구들은 나를 룸바라고 부르기도 하지만, 너는 분명 그중 하나가 아니지. 그리고 방금 그 '아마도'는 또 뭐였어?";
				link.l1.go = "BM_Irons_5";
			}
			else
			{
				dialog.text = "나는 토미야! 토미 아이언스지. 아마도. 너는?";
				link.l1 = ""+GetFullName(pchar)+". 그런데 '아마도'라니, 그게 무슨 뜻이오?";
				link.l1.go = "BM_Irons_5";
			}
			LAi_SetCurHPMax(pchar);
		break;
		
		case "BM_Irons_5":
			dialog.text = "그 말은 말 그대로야. 나는 기억을 잃었어 – 전투에서 심하게 얻어맞았지. 알잖아, 가끔은 모든 걸 다 잃기도 해. 그래도 나는 운이 좋은 편이야. 이름만 잊어버렸으니까. 다행히 목에 '토마스'라고 적힌 펜던트가 걸려 있었지. 하지만 나는 토미가 더 좋아. 그리고 아이언스. 나는 크롬웰 밑에서 아이언사이드 부대에서 싸웠어, 그건 기억해둬. 하지만 ‘아이언사이드’는 너무 길잖아. 아이언스가 훨씬 낫지.";
			link.l1 = "무슨 일인지 알겠구나, 토미. 자, 말해 봐라 - 무슨 일이었지? 누군가를 노리고 쏜 거냐? 제대로 맞췄어? 아니면 그냥 재미로 쏜 거냐? 뭐, 놀랍지도 않군.";
			link.l1.go = "BM_Irons_6";
		break;
		
		case "BM_Irons_6":
			dialog.text = "세게 한 방 먹였지! 여러모로 말이야. 그 잘난 양반 기억나? 내 뒤를 쫓아와서 군인들까지 데려왔어. 내가 그놈 마누라랑 잤다는 이유로 분대 전체를 끌고 왔다니까.";
			link.l1 = "정말 제대로 맞췄군, 흐. 둘이 뭐 하는 거 들켰나 보지?";
			link.l1.go = "BM_Irons_7";
		break;
		
		case "BM_Irons_7":
			dialog.text = "하! 믿기 힘들겠지만, 아니야. 그 계집애가 나중에 자백했거든. 양심의 가책이었는지, 아니면 나만큼 즐기지 못했는지, 헤헤. 여자들 머릿속엔 뭐가 들어 있는지 누가 알겠냐? 난 별로 신경 안 써, 하하하!";
			link.l1 = ""+GetSexPhrase("흠, 저 여자는 참 이상한 녀석이군.","남자들이란... 한순간엔 우리 머릿속에 뭐가 있는지 궁금해하다가, 다음 순간엔 신경도 안 쓴다고 하지. 하지만 한 가지는 네 말이 맞아 – 그 여자가 한 짓은 이상했어. 그냥 떠나서 나쁜 꿈처럼 잊어버렸어야 했지. 나라도 그런 일이 생기면 딱 그렇게 했을 거야.")+"";
			link.l1.go = "BM_Irons_8";
		break;
		
		case "BM_Irons_8":
			dialog.text = "그래, 맞아! 사람들은 내가 뭔가 이상하다고들 하지. 죽은 병사들이 안쓰러워. 나도 한때 그냥 졸병이었으니 그 마음 알아. 내가 말하지 않았나?";
			link.l1 = "그래, 맞아. 아이언사이드에서 왔지. 크롬웰.";
			link.l1.go = "BM_Irons_9";
		break;
		
		case "BM_Irons_9":
			dialog.text = "오, 정말인가? 내가 그랬는지 안 그랬는지 기억이 안 나네. 내가 어떻게 신세계에 오게 됐는지 알아? 말해줄까?";
			link.l1 = "아니, 그리고 난 관심도 없어, 토미.";
			link.l1.go = "BM_Irons_10";
		break;
		
		case "BM_Irons_10":
			dialog.text = "그렇지, 그렇지. 내가 말해줄게.";
			link.l1 = "좋아, 젠장할, 그냥 쏴. 아니, 어서 해.";
			link.l1.go = "BM_Irons_11";
		break;
		
		case "BM_Irons_11":
			dialog.text = "그럼 내 말 끊지 마! 어디까지 말했더라? 그래, 내가 부상당했다고 했지? 이겼으니까 공식적으로 사직서를 받았어. 그런데 그 책상머리 쥐새끼들 표정 좀 봤어야 했어! 내가 일부러 기억을 잃은 척한다고 생각하더라고. 계속 내 가족에 대해 물어봤지.";
			link.l1 = "그래서, 너 그놈들한테 뭐라고 했어?";
			link.l1.go = "BM_Irons_12";
		break;
		
		case "BM_Irons_12":
			dialog.text = "내가 뭐라고 했는지 알아? 기억이 안 난다고 했지. 거짓말 아니야 - 난 내 부모도 몰라. 거리에서, 빈민가의 노동자들과 하인들 손에서 자랐으니까. 그들을 위해 혁명에 뛰어들었지. 그런데 사람들의 배은망덕함이란 정말 놀라워 - 내가 팔이나 다리를 잃었으면, 영웅인 나한테 당장 은퇴를 시켜줬을 거야. 그런데 말이지, 사실 내 목이 날아갈 뻔도 했다고!\n";
			link.l1 = "그래서, 전쟁 영웅, 어떻게 신세계까지 오게 된 거지?";
			link.l1.go = "BM_Irons_13";
		break;
		
		case "BM_Irons_13":
			dialog.text = "의심하나? 평민들을 위해 싸우는 게 뭐가 영웅적이지 않다는 거냐? 언젠가 너 같은 겁쟁이도 진짜 자유가 뭔지 알게 되길 바란다!";
			link.l1 = "자유가 좋은 거긴 한데, 어쩐지 너 말은 협박처럼 들리네. 좋아, 토미, 계속해.";
			link.l1.go = "BM_Irons_14";
		break;
		
		case "BM_Irons_14":
			dialog.text = "그래. 혁명이 끝나고 나서야 사직서를 받았지. 그리고 나서야 난 총 쏘고 주먹질하는 것밖에 할 줄 모른다는 걸 깨달았어. 군대에 다시 들어갈 수도 없어. 내가 사직하려고 그렇게 악착같이 싸웠으니, 다시 오겠다고 하면 비웃을 거야. 허, 내 생각엔 내가 진짜로 팔이나 다리를 잃었어도, 그 책상물림 놈들은 내가 그걸 어딘가에 숨겨놨다가 전역 서류 받으면 다시 꿰매 붙일 거라고 생각했을 거야, 하하하!";
			link.l1 = "재밌군. 하지만 아직도 네가 어떻게 여기 오게 됐는지는 말하지 않았잖아.";
			link.l1.go = "BM_Irons_15";
		break;
		
		case "BM_Irons_15":
			dialog.text = "아, 너 정말 재미없구나. 인내심도 못 배웠냐,\n "+GetSexPhrase("젊은이","내 딸")+"? 집에서는 오리랑 사슴이나 쏘는 것밖에 할 일이 없어서 신세계로 왔지. 재미 삼아 한동안 해적들과 함께 항해하다가, 무법이 지겨워지니 용병이 되었어.";
			link.l1 = "별로 참신하지 않은 이야기군.";
			link.l1.go = "BM_Irons_16";
		break;
		
		case "BM_Irons_16":
			dialog.text = "혹시 더 나은 제안 있어? 혹시 경호원이 필요하지 않아? 왜냐면 너... 약해 보여서 말이야. 멀리 못 갈까 봐 걱정돼, 헤헤. 기억해, 왕을 만드는 건 수행원이야. 그리고 나쁜 수행원은 왕을 망치기도 하지.";
			link.l1 = "그리고 어떤 종류의 "+GetSexPhrase("왕","여왕")+" 내가 너 같은 수행원을 데리고 다니겠어? "+GetSexPhrase("King","Queen")+" 똥더미의?";
			link.l1.go = "BM_Irons_17";
		break;
		
		case "BM_Irons_17":
			dialog.text = "아니, 아니야! 나는 진짜 제안을 하는 거고, 너는...";
			link.l1 = "아직 아무 제안도 못 받았어. 네 서비스에 얼마를 요구하는 거지, 토미?";
			link.l1.go = "BM_Irons_18";
		break;
		
		case "BM_Irons_18":
			dialog.text = "선불로 150두블론이다! 네가 진심인지, 사기꾼이 아닌지 확인하려면 말이지. 그리고 그 뒤엔 매달 수수료를 내야 해. 우리 거래할 수 있을 것 같은데.";
			link.l1 = "그리고 너는 안...";
			link.l1.go = "BM_Irons_19";
		break;
		
		case "BM_Irons_19":
			dialog.text = "... 네가 배짱이 있다고 생각해? 흥, 너랑 말싸움도 안 할 거다 – 등대에서 내가 그 머저리 쏜 거 봤지? 첫 발에 끝냈어! 흥정 같은 건 꿈도 꾸지 마, 혹시 그런 생각 하고 있다면. 나 같은 프로를 쓰려면 네가 그만한 값은 치를 수 있다는 걸 보여야 해.";
			if (PCharDublonsTotal() >= 150)
			{
				link.l1 = "그래, 할 수 있지! 150골드다. 여기 있어.";
				link.l1.go = "BM_Irons_Hire1";
			}
			link.l2 = "그 한 방은 운이 좋았을 뿐이야. 이제 와서 허세로 네 가치를 부풀리려 드는군. 너 같은 전문가 없어도 돼. 그건 명예도 돈도 지나치게 많아.";
			link.l2.go = "BM_Irons_NoHire1";
			link.l3 = "지금은 그만한 돈이 없어, 주머니에 그렇게 많이 들고 다니지 않거든. 여기서 기다려, 어디 가지 말고. 내가 배에서 금을 가져와서 돌아올게.";
			link.l3.go = "BM_Irons_Wait1";
		break;
		
		case "BM_Irons_Hire1":
			RemoveDublonsFromPCharTotal(150);
			
			dialog.text = "생각보다 그렇게 나쁘진 않구나! 하지만 내가 심심하지 않게 해 줘야 할 거야. 내 재능을 낭비하면 안 되지, 안 그래? 토미랑\n "+pchar.name+"! 카리브 해를 뒤흔들자!";
			link.l1 = "명령 체계를 존중하는 법부터 배워, 토미. 그리고 두 번째로, 나한테는 '선장'이라고 불러. 알겠어?";
			link.l1.go = "BM_Irons_Hire2";
		break;
		
		case "BM_Irons_Hire2":
			dialog.text = "헤, 맞아, Boring 선장. "+GetSexPhrase("나리","아가씨")+".";
			link.l1 = "아, 벌써부터 이걸 후회하기 시작했네...";
			link.l1.go = "Irons_hire";
		break;
		
		case "Irons_Hire":
			DialogExit();
			AddDialogExitQuestFunction("BM_Irons_Hire");
			
			if (CheckAttribute(pchar, "questTemp.BM_hireInGrot"))
			{
				AddQuestRecord("BlackMark", "4");
			}
			else
			{
				AddQuestRecord("BlackMark", "1");
			}
		break;
		
		case "BM_Irons_NoHire1":
			dialog.text = "글쎄, 너 정말 멍청하구나, 어린놈아 "+GetSexPhrase("남자","여자")+"! 그리고 전혀 분별력이 없군. 그 점을 고치지 않으면 오래 못 버틸 거다. 특히 이 군도에서는 말이지.";
			link.l1 = "너 없이도 알아서 할 수 있어, 토미. 잘 가라.";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_IronsGoodbye");
		break;
		
		case "BM_Irons_Wait1":
			dialog.text = "진심이야? 여기서 군인들이 한 무리나 죽었잖아, 천재야! 아마 곧 다른 부대를 또 보낼 거야. 아니, 내가 등대 문을 잠그고 방어를 조직할 수도 있지. 근데 내가 그걸 하고 싶을까? 아니, 전혀.";
			link.l1 = "그래서 어떻게 하자는 거지?";
			link.l1.go = "BM_Irons_Wait2";
		break;
		
		case "BM_Irons_Wait2":
			dialog.text = "정글에 있는 동굴에서 나를 만나. 내 서비스를 받을 돈을 벌 시간 이틀쯤 줄게 – 칼 다루는 법은 알 테니, 어떻게든 해내겠지.";
			link.l1 = "진심이야? 거기 가면 쥐구멍에 몰린 신세가 될 텐데.";
			link.l1.go = "BM_Irons_Wait3";
		break;
		
		case "BM_Irons_Wait3":
			dialog.text = "나를 특별히 찾으려고 대규모 부대를 동원하지 않는 이상, 괜찮을 거야. 그러니 난 문제없을 거라고 생각해. 이제 가봐야겠어 - 곧 도착할 테니까. 나중에 보자.";
			link.l1 = "그래, 나도 혹시 모르니까 가봐야겠어.";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_IronsToCave");
		break;
		
		case "BM_Irons_WaitInCave1":
			dialog.text = "그래, 거기 있었군! 너한테 돈 버는 재주가 없는 줄 알 뻔했잖아. 가끔은 너 같은 놈들은 타고난 거라고 생각하게 돼. 그리고 그런 게 없으면, 정직하게 일하는 사람들처럼 하루도 일 안 하고 가난하게 죽는 거지.";
			link.l1 = "그래, 그래, 토미. 내 선원으로 들어오고 싶지 않으면 안 해도 돼. 네가 이 구멍에서 둥지 트는 걸 좋아하는 것 같군.";
			link.l1.go = "BM_Irons_WaitInCave2";
			DelLandQuestMark(npchar);
		break;
		
		case "BM_Irons_WaitInCave2":
			dialog.text = "너 아일랜드 우기 때 구덩이에 숨어본 적 없지, "+GetSexPhrase("젊은이","내 딸")+"! 하지만 너랑 같이 가는 게 여기 숨어 있는 것보단 낫지. 자, 그 금에 대해서 말인데...";
			if (PCharDublonsTotal() >= 150)
			{
				link.l1 = "여기 네 금화다.";
				link.l1.go = "BM_Irons_HireInCave1";
			}
			link.l2 = "아직 못 받았어. 혹시 어디 딴 데로 도망친 건 아닌가 해서 확인해봤지.";
			link.l2.go = "BM_Irons_NoHireInCave1";
		break;
		
		case "BM_Irons_HireInCave1":
			RemoveDublonsFromPCharTotal(150);
			pchar.quest.BM_IronsTimeOver.over = "yes";
			pchar.questTemp.BM_hireInGrot = true;
			
			dialog.text = "이제야 제대로 말이 통하는군! 다음엔 뭘 하지... 선장?";
			link.l1 = "우선 이 눅눅한 곳에서 나가자, 안 그럼 나 재채기하기 시작할 거야.";
			link.l1.go = "BM_Irons_HireInCave2";
		break;
		
		case "BM_Irons_HireInCave2":
			dialog.text = "오, 전쟁을 한번 겪어봐. 난 이런 곳이 거의 집처럼 느껴지거든.";
			link.l1 = "그래, 사직서를 받고 나니까 예의랑 상하관계는 다 잊어버린 거냐, 토미? 걱정 마라, 필요하면 또 한 번 본때를 보여줄 테니까. 자, 이제 가자.";
			link.l1.go = "Irons_hire";
		break;
		
		case "BM_Irons_NoHireInCave1":
			NextDiag.TempNode = "BM_Irons_WaitInCave3";
			
			dialog.text = "헤, 토미 아이언스는 절대 도망치지 않아! 약속은 반드시 지키지. 너도 네 약속을 지킬 거냐?";
			link.l1 = "하고 있어.";
			link.l1.go = "Exit";
		break;
		
		case "BM_Irons_WaitInCave3":
			dialog.text = "금 가져왔어?";
			if (PCharDublonsTotal() >= 150)
			{
				link.l1 = "여기 네 금화다.";
				link.l1.go = "BM_Irons_HireInCave1";
			}
			link.l2 = "아직 못 받았어. 혹시 어디 딴 데로 도망친 건 아닌가 해서 확인하러 왔지.";
			link.l2.go = "BM_Irons_NoHireInCave1";
		break;
		
		case "BM_IronsJungleUhodit":
			DialogExit();
			AddDialogExitQuestFunction("BM_IronsJungleUhodit");
		break;
		
		case "BM_IronsFirstJungle_1":
			dialog.text = "듣시오, 선장...";
			link.l1 = "무슨 일이야, Tommy?";
			link.l1.go = "BM_IronsFirstJungle_2";
		break;
		
		case "BM_IronsFirstJungle_2":
			dialog.text = "혹시 여분의 탄환이 있나? 그냥 총알 말고, 제대로 종이에 싼 탄약 말이야.";
			link.l1 = "이것도 또 네 농담이냐? 나는 네가 필요할 때마다 총알이랑 탄약을 챙겨주잖아. 그런데 왜 하필 한 발만 달라는 거지, 한 움큼도 아니고?";
			link.l1.go = "BM_IronsFirstJungle_3";
		break;
		
		case "BM_IronsFirstJungle_3":
			dialog.text = "내 부탁을 왜 그렇게 심각하게 받아들이는 거야? 피 묻은 진주를 달라는 것도 아니고, 그냥 탄환 하나 달라는 건데. 네 일 방해하지 않으려고, 미친놈처럼 굴지 않으려고 타이밍까지 봤다니까, 헤헤. \n그러니까... 탄환 있냐?";
			if (CheckCharacterItem(PChar, "cartridge") || CheckCharacterItem(PChar, "bullet"))
			{
				link.l1 = "그래, 내가 한 잔 샀어. 자, 여기 있다. 근데 그 총알로 바보 같은 장난치지 마라. 알겠지, 토미?";
				link.l1.go = "BM_IronsFirstJungle_7";
			}
			link.l2 = "지금은 없어. 내가 주머니에 탄환 하나 들고 다니면서, 혹시 토미가 달라고 하면 어쩌지... 그런 생각이나 하겠어?";
			link.l2.go = "BM_IronsFirstJungle_4";
		break;
		
		case "BM_IronsFirstJungle_4":
			dialog.text = "음, 그거 좋은 지적이네, 그리고 눈치도 빠르군, 헤헤. 하지만 아쉽게도 여기서 우리 길이 갈라지는 것 같아.";
			link.l1 = "진심이야? 총알 한 방 때문에 기분이 상한 거야? 에이, 가자. 배에 가면 구할 수 있어. 그렇게 급하면 내가 하나든, 열 개든, 필요한 만큼 구해줄게.";
			link.l1.go = "BM_IronsFirstJungle_5";
		break;
		
		case "BM_IronsFirstJungle_5":
			dialog.text = "아니. 결국 너한테는 별다를 게 없어. 훌륭한 선장은 언제나 선원들에게 필요한 걸 다 마련해 주지. 그러니 난 간다.";
			link.l1 = "그리고 우리가 바다에 있는데 럼주가 다 떨어졌고, 네가 더 마시고 싶으면 어쩔 거야? 작은 배를 풀어서 도망칠 거냐? 아니면 물에 뛰어들 거야?";
			link.l1.go = "BM_IronsFirstJungle_6";
		break;
		
		case "BM_IronsFirstJungle_6":
			dialog.text = "하하하! 웃었지만, 이 슬픈 순간엔 아무리 좋은 농담도 소용없어. 잘 가라, 지루한 선장.";
			link.l1 = "그래, 엿 먹어라, 토미. 잘 가라.";
			link.l1.go = "BM_IronsJungleUhodit";
		break;
		
		case "BM_IronsFirstJungle_7":
			dialog.text = "아무것도 약속 못 해, 헤헤. 농담 하나면 분위기가 풀리거든. 그래도 고맙다, 물론.";
			link.l1 = "좋아, 가자, 이 녀석아.";
			link.l1.go = "BM_IronsFirstJungle_8";
			if (CheckCharacterItem(PChar, "cartridge"))
			{
    			TakeItemFromCharacter(PChar, "cartridge");
			}
			else if (CheckCharacterItem(PChar, "bullet"))
			{
    			TakeItemFromCharacter(PChar, "bullet");
			}
		break;
		
		case "BM_IronsFirstJungle_8":
			DialogExit();
			AddDialogExitQuestFunction("BM_IronsFirstJungle");
		break;
		
		case "BM_IronsSecondJungle_1":
			dialog.text = "이봐, 선장!";
			link.l1 = "그래, Tommy?";
			link.l1.go = "BM_IronsSecondJungle_2";
		break;
		
		case "BM_IronsSecondJungle_2":
			dialog.text = "종이 탄약 하나 더 있냐?";
			link.l1 = "지난번 녀석한테 무슨 일이 있었지? 그리고 그 탄약 농담은 또 뭐였어? 내가 너한테서 멍청한 농담 하나 들으려고 2주나 기다렸는데, 아무것도 없잖아.";
			link.l1.go = "BM_IronsSecondJungle_3";
		break;
		
		case "BM_IronsSecondJungle_3":
			dialog.text = "오, 이거 끝내주는 농담이 될 거야, 믿어 봐. 너도 분명 좋아할 거야, 헤헤. 아직 다 완성하진 않았지만. 그런데 탄약통은 어떻게 됐지?";
			if (CheckCharacterItem(PChar, "cartridge") || CheckCharacterItem(PChar, "bullet"))
			{
				link.l1 = "자, 받아라. 네가 다음에 할 장난이 정말 기대되는군. 그런데 마지막 탄환은 어디다 뒀지? 내가 그런 건 넉넉히 줬잖아. 아니면 싸울 때 쓸 탄약이랑 장난칠 때 쓸 건 따로 보관하냐?";
				link.l1.go = "BM_IronsSecondJungle_7";
			}
			link.l2 = "네 멍청한 농담에 쓸 탄약은 안 들고 다녀, 토미! 두 주 전에 탄환 한 발만 달라고 하지 말고 그냥 한 묶음 통째로 달라고 했으면 됐잖아!";
			link.l2.go = "BM_IronsSecondJungle_4";
		break;
		
		case "BM_IronsSecondJungle_4":
			dialog.text = "내가 했지! 내 선장이라고 하는 자는 언제나 선원들에게 필요한 걸 마련해 준다고 생각했거든.";
			link.l1 = "나는 아무것도 흉내 내는 게 아니야, 토미. 난 오래전에 내 자신이 되기로 했어. 나랑 편한 사람은 그걸로 좋고, 아니면 그것도 괜찮아.";
			link.l1.go = "BM_IronsSecondJungle_5";
		break;
		
		case "BM_IronsSecondJungle_5":
			dialog.text = "헤, 너랑 나는 그런 점에서 닮았지. 하지만 내 선장에게는 내가 원하는 조건이 있어. 그리고 이제는 네가 그 조건에 맞지 않아, 젊은이. 여기서 우리 길은 갈라진다.";
			link.l1 = "진심이야? 내가 빌어먹을 종이 탄약통이 없었다고 이런 거냐?";
			link.l1.go = "BM_IronsSecondJungle_6";
		break;
		
		case "BM_IronsSecondJungle_6":
			dialog.text = "그건 말도 안 돼. 나는 보통 사람들에게 자기 마음대로 살고 원하는 걸 쟁취하라고 조언하지. 앞으로는 네 사람들에 대해 더 생각해보라고 충고하겠어. 잘 가라.";
			link.l1 = "그리고 네 머리 조심하는 게 좋겠어 – 네가 아는 것보다 더 많이 다쳤으니까. 잘 가라, 토미.";
			link.l1.go = "BM_IronsJungleUhodit";
		break;
		
		case "BM_IronsSecondJungle_7":
			dialog.text = "알게 될 거야. 때가 되면 다 알게 되지, 헤헤.";
			link.l1 = "아, 왠지 불길한 예감이 들어, 토미...";
			link.l1.go = "BM_IronsSecondJungle_8";
			if (CheckCharacterItem(PChar, "cartridge"))
			{
    			TakeItemFromCharacter(PChar, "cartridge");
			}
			else if (CheckCharacterItem(PChar, "bullet"))
			{
    			TakeItemFromCharacter(PChar, "bullet");
			}
		break;
		
		case "BM_IronsSecondJungle_8":
			DialogExit();
			AddDialogExitQuestFunction("BM_IronsSecondJungle");
		break;
		
		case "BM_IronsThirdJungle_1":
			dialog.text = "선장, 너한테 물어볼 게 있어.";
			link.l1 = "그래, 토미, 무슨 일이야?";
			link.l1.go = "BM_IronsThirdJungle_2";
		break;
		
		case "BM_IronsThirdJungle_2":
			dialog.text = "눈치 못 챘어? 눈치는 쓸모 있는 기술이지, 헤헤. 너, 나, 그리고 정글... 한 이주쯤 전에 우리 이런 대화를 했었지. 종이 탄약통 하나 더 필요해.";
			if (CheckCharacterItem(PChar, "cartridge") || CheckCharacterItem(PChar, "bullet"))
			{
				link.l1 = "이거 꽤나 전통이 되어 가는군, 안 그래? 벌써 2주가 지났는데, 또 토미가 탄약을 달라고 하네. 자, 여기 있다. 네 농담을 위해서 도대체 탄약이 몇 개나 더 필요한 거냐?";
				link.l1.go = "BM_IronsThirdJungle_5";
			}
			link.l2 = "얼마나 더 기다려야 해, 토미?! 이게 언제까지 계속될 거야? 너희 아이언사이드는 전투마다 탄환 한 발씩만 받는 거냐?! 너희들 이상한 버릇 때문에 내가 항상 탄환을 들고 다녀야 하는 건 아니잖아, 알지?!";
			link.l2.go = "BM_IronsThirdJungle_3";
		break;
		
		case "BM_IronsThirdJungle_3":
			dialog.text = "사실, 내 선장으로서 전투에 필요한 모든 것뿐만 아니라 그 이상도 나에게 제공하는 게 당신의 의무야.";
			link.l1 = "넌 혼란스러운 거야, 토미. 네 임무는 선장의 명령을 따르는 거다. 나는 항상 너희 모두에게 필요한 것들―약, 탄약, 럼―을 다 공급해 주고 있어. 제때 필요한 걸 챙기지 않고 나중에 거지처럼 구는 건 전적으로 네 잘못이야!";
			link.l1.go = "BM_IronsThirdJungle_4";
		break;
		
		case "BM_IronsThirdJungle_4":
			dialog.text = "너 참 똑똑하구나 - 그런데 왜 여기서 지금까지 아무런 성과도 못 냈지? 내가 이유를 말해주지. 넌 앞을 내다보지 못하고, 항상 아무 준비도 안 하니까 그래. 네가 뭘 하는지도 모르겠고, 지루하기 짝이 없어. 난 그런 사람을 내 지휘관으로 인정 못 하겠으니, 잘 가라.";
			link.l1 = "넌 정말 머리를 안 쓰는구나! 잘 됐다, 이 멍청한 놈아!";
			link.l1.go = "BM_IronsJungleUhodit";
		break;
		
		case "BM_IronsThirdJungle_5":
			dialog.text = "이 녀석이면 되겠군, 헤헤.";
			link.l1 = "드디어 정신 좀 차렸나? 그런데 그게 다 무슨 소용이지?";
			link.l1.go = "BM_IronsThirdJungle_6";
			if (CheckCharacterItem(PChar, "cartridge"))
			{
   				TakeItemFromCharacter(PChar, "cartridge");
			}
			else if (CheckCharacterItem(PChar, "bullet"))
			{
    			TakeItemFromCharacter(PChar, "bullet");
			}
		break;
		
		case "BM_IronsThirdJungle_6":
			dialog.text = "그냥 장난친 거야, 네가 다시 심술궂게 변하나 보려고 했지. 헤헤. 그래도 탄약 줘서 고마워.";
			link.l1 = "네 농담은 이상해, Tommy.";
			link.l1.go = "BM_IronsThirdJungle_7";
		break;
		
		case "BM_IronsThirdJungle_7":
			dialog.text = "그것도 농담이었지. 모으고 있었던 게 아니라, 고르고 있었던 거야. 거의 완벽한 탄환이 필요했거든. 이거면 되겠어. 그래, 이 탄환이면 총알이 멀리, 그리고 정확하게 날아가지. 예전에 리즐리 영감 머리를 날려버렸을 때처럼, 하하하!\n";
			link.l1 = "올드 리즐리, 그렇게 말했지... 프랭키 그 바람둥이, 맞지? 등대에서 네가 쏜 그 놈 말이야? 그럼, 너희 오래전부터 알고 지낸 사이였구나?";
			link.l1.go = "BM_IronsThirdJungle_8";
		break;
		
		case "BM_IronsThirdJungle_8":
			dialog.text = "뭐? 아, 젠장, 그 말이 튀어나왔군. 하지만 신경 안 써 – 난 거짓말이나 비밀 지키는 데 소질이 없거든.";
			link.l1 = "두 번째 총알은 누군가를 노린 거였지, 그렇지, 토미?";
			link.l1.go = "BM_IronsThirdJungle_9";
		break;
		
		case "BM_IronsThirdJungle_9":
			dialog.text = "그래, 천재님. 뭐, 나는 내 자신과 내 목표를 잘 알고 있고, 부끄러울 것도 없어. 그래서 네가 뭘 생각하든 신경 안 써 – 전부 다 얘기해주지, 도대체 왜 안 하겠어.";
			link.l1 = "그래, 말해 봐라. 네가 무슨 꿍꿍이인지 알아둬도 나쁠 건 없으니까.";
			link.l1.go = "BM_IronsThirdJungle_10";
		break;
		
		case "BM_IronsThirdJungle_10":
			dialog.text = "자, 평소처럼 내 말 끊지 마라. 내랑 같이 있던 놈 둘 있었지 - 프랜시스 리슬리랑 가브리엘 캘로. 진짜 쥐새끼들이었어! 내 사직서 내는 것도 쉽지 않았는데, 그걸 안 내주던 사무실 쥐새끼들보다도 더한 놈들이었지.";
			link.l1 = "그럼 그 자들은 뭘 했지? 특히 두 번째 놈, 캘로우 말이야. 그 자 부인하고도 잤냐? 그리고 그놈도 병사들을 보냈어?";
			link.l1.go = "BM_IronsThirdJungle_11";
		break;
		
		case "BM_IronsThirdJungle_11":
			dialog.text = "입 다물고 있어, 알았지? 뭐... 사실 싫진 않지만, 헤헤. 하지만 안 돼. 그날 왕당파 놈들이 우리를 공격했어. 기병대도 있었지. 놈들이 훨씬 많았어. 게이브랑 프랭키는 겁먹은 토끼처럼 도망쳤지. 하지만 나는 동료들과 함께 있었어. 살아남은 건 나뿐이었지. 어린 시절과 젊었을 때 기억은 많이 잊었지만, 그 일만은 잊지 못해.";
			link.l1 = "그리고 놈들이 도망쳤다고 복수를 원하나? 모두가 이상을 위해 싸우는 건 아니지. 누구나 살아남고 싶어 해. 아니, 거의 모두가 그렇지. 혁명을 위해 싸우는 자라 해도, 우연히 끼어들었다가 후회할 수도 있는 법이야.";
			link.l1.go = "BM_IronsThirdJungle_12";
		break;
		
		case "BM_IronsThirdJungle_12":
			dialog.text = "하, 내가 겁쟁이들마다 사냥했다면 세상 모두를 쏴야 했을 거야. 겁쟁이 놈들, 지옥에나 가라지. 하지만 그놈들이 날 배신했어. 내가 혁명을 배신하고 왕당파 명령으로 우리 부대를 전부 죽였다고 모두에게 떠들고 다녔지. 한 가지는 거짓말했어, 선장.";
			link.l1 = "뭔데? 프랭키가 자기 아내 일 때문에 너를 쫓는다고 거짓말한 것 말고 또 뭐가 있는데?";
			link.l1.go = "BM_IronsThirdJungle_13";
		break;
		
		case "BM_IronsThirdJungle_13":
			dialog.text = "아니야, 아니라고! 내가 너한테 거짓말한 건 아니고, 그냥 전부 말하지 않았을 뿐이야. 그건 다르지. 내가 거짓말한 건 사직에 관한 거였어. 사직은 없었어. 재판이 있었지. 그리고 우리 토미는 운이 좋았어 – 교수형 대신 남부 식민지의 채석장으로 보내기로 했거든. 정확히 말하면 바베이도스야.";
			link.l1 = "그래, 운이 좋았지. 거기서 몇 년이나 일했어?";
			link.l1.go = "BM_IronsThirdJungle_14";
		break;
		
		case "BM_IronsThirdJungle_14":
			dialog.text = "없어. 저 쥐새끼들 때문에 지상 법정에서 유죄 판결을 받았으니, 위에 계신 하늘 법정에서는 나를 살려주기로 한 거지. 우리가 군도에 들어서자마자 그 분위기를 느꼈어\n우리 배에 해적들이 들이닥쳤거든.";
			link.l1 = "그래서 바베이도스의 채석장이나 플랜테이션 대신, 해적들에게 팔려 노예가 된 거야? 그런데 채석장에서 일한 적은 없다고 했잖아.";
			link.l1.go = "BM_IronsThirdJungle_15";
		break;
		
		case "BM_IronsThirdJungle_15":
			dialog.text = "내가 한 말이 그거야 - 누군가 위에서 날 구해주기로 한 거지. 뭐, 정말 대단한 구출이었어, 헤헤! 네 말이 맞아 - 해적들이 결박당하고 사슬에 묶인 자들을 괴롭히던 놈들을 물리쳤지. 하지만 싸움은 여전히 치열했어, 이곳 태양만큼이나 뜨거웠지. 그리고 우리를 구해준 이들도 피해를 입었어. 그래서 그들은 함께할 사람은 누구든 받아주겠다고 했지.";
			link.l1 = "그들과 함께했나? 해적들과 같이 항해했다고 했잖아.";
			link.l1.go = "BM_IronsThirdJungle_16";
		break;
		
		case "BM_IronsThirdJungle_16":
			dialog.text = "그래, 당연하지! 내 인생 최고의 시절이었어. 잭 밀스는 진짜 대단한 선장이었지 – 언젠가 너도 그처럼 되길 바란다. 나는 그의 '크레인'에서 한 2년 정도 항해했었지, 그러다가...\n";
			link.l1 = "... 네가 말한 대로 무법자 생활에 질릴 때까지? 그런데 왜 그 시절이 네 인생에서 가장 좋았다고 말하는 거지?";
			link.l1.go = "BM_IronsThirdJungle_17";
		break;
		
		case "BM_IronsThirdJungle_17":
			dialog.text = "에... 그 두 배신자들도 결국 군도에 나타났다는 소식을 듣기 전까지는 말이야. 그래, 알아, 내가 대양에서 해적질하는 데 질렸다고 너한테 말했었지. 그리고 네가 어떻게 생각하든 신경 안 쓴다고도 이미 말했잖아. 그건 여전히 사실이야. 하지만 우리가 처음 만났을 때는 너를 잘 몰랐거든. 네가 어떻게 반응할지 몰랐지. 그래서 그때는 다르게 말했던 거야.";
			link.l1 = "너 거짓말쟁이야, 토미! 그래, 그런데 왜 '크레인'을 떠난 거지?";
			link.l1.go = "BM_IronsThirdJungle_18";
		break;
		
		case "BM_IronsThirdJungle_18":
			dialog.text = "잭은 진정한 지도자였기 때문에, 한 사람 때문에 우회하거나, 그를 기다리거나, 복수하거나, 살찐 상선 대신 영국 해군의 고위 장교들과 엮이지 않겠다고 말했다.";
			link.l1 = "유명한 장교들? 프랭크는 민간인이었던 걸로 아는데.";
			link.l1.go = "BM_IronsThirdJungle_19";
		break;
		
		case "BM_IronsThirdJungle_19":
			dialog.text = "에이, 원래부터 그런 놈은 아니었지. 항상 좀, 알잖아, 수상쩍은 구석이 있었어. 누굴 함정에 빠뜨리려다 망신당하고 쫓겨났지. 상선 타고 일해보려고 했지만, 성실한 일은 그놈 체질이 아니었어. 결국 여기 정착하게 됐지.";
			link.l1 = "아직 그를 훌륭한 장교라고 부를 수는 없지.";
			link.l1.go = "BM_IronsThirdJungle_20";
		break;
		
		case "BM_IronsThirdJungle_20":
			dialog.text = "게이브를 잊지 마. 그는 고향에서 중위가 됐어. 그리고 여기 포트 로얄에서 '프린시피오' 호의 선장 임명을 받았지.";
			link.l1 = "영국식 같지 않은데.";
			link.l1.go = "BM_IronsThirdJungle_21";
		break;
		
		case "BM_IronsThirdJungle_21":
			dialog.text = "좋은 지적이야! 그 배는 항구의 처녀처럼 주인이 자주 바뀌었으니 별별 꼴을 다 봤지. 그래도 아직 바다에 나갈 만해. 그리고 게이브 녀석, 젠장, 선장 솜씨 하나는 끝내주지.";
			link.l1 = "그래서 잭도 그와 엮이기 두려워했단 말이야? 네 말대로 정말 그렇게 대단한 놈이냐?";
			link.l1.go = "BM_IronsThirdJungle_22";
		break;
		
		case "BM_IronsThirdJungle_22":
			dialog.text = "좋아, 좋아! 사실은 내 일 때문에 시간 낭비하기 싫었던 거겠지. 그런데 잭 얘기가 나와서 말인데, 내가 처음으로 그에게서 본 전통 몇 가지가 마음에 들었어. 판자 걷기랑 블랙 마크를 나눠주는 거 말이야. 그때 그거 보고 재밌는 생각이 떠올랐지.";
			link.l1 = "검은... 표시라고? 너 검은 점을 말하는 거지? 근데 그게 뭐였는데, 토미? 네가 그놈한테 검은 점을 건넸다면 뭘 해야 할지 모를 놈일 텐데. 그게 있었던 일이냐? 네가 그걸 건네주려고 했고, 그놈이 널 보자마자 덤벼들어서 네가 등대로 도망쳤고, 그놈은 병사들을 데리고 가서는 네가 해적이라고 말한 거야?";
			link.l1.go = "BM_IronsThirdJungle_23";
		break;
		
		case "BM_IronsThirdJungle_23":
			dialog.text = "나는 그걸 그냥 ‘검은 표식’이라고 부르는 게 더 낫다고 생각해. 그게 더 그럴싸하게 들리거든. 단순한 검은 표식만으로는 그 자가 아무것도 깨닫지 못했을 거야. 하지만 우리 회사만의 특징이었던 비단 손수건으로 만든 검은 표식이라면, 그건 분명히 알아차릴 테지. 나는 그걸 몰래 그의 주머니에 넣었어. 그리고 내가 등대로 향하는 걸 그가 확실히 보게 했지. 그 뒤 이야기는 너도 알잖아.";
			link.l1 = "그리고 밀수꾼들은?";
			link.l1.go = "BM_IronsThirdJungle_24";
		break;
		
		case "BM_IronsThirdJungle_24":
			dialog.text = "잘못된 곳, 잘못된 시간에 있었지. 나도 그놈들이 좀 불쌍하긴 했어. 하지만 아주 조금만, 헤헤.";
			link.l1 = "그리고 프랭키는?";
			link.l1.go = "BM_IronsThirdJungle_25";
		break;
		
		case "BM_IronsThirdJungle_25":
			dialog.text = "지금 누가 신경 쓰겠어? 더 중요한 일이 있잖아. 이제 남은 건 게이브야. 그게 골치 아프겠군. 우리는...";
			link.l1 = "우리?";
			link.l1.go = "BM_IronsThirdJungle_26";
		break;
		
		case "BM_IronsThirdJungle_26":
			dialog.text = "흥미로운 이야기를 듣는 것과 직접 만들어내는 건 전혀 다른 일이야! 그래서 계획은 이렇다. 게이브한테 또 하나의 특별한 검은 표식을 남겨야 해 - 이미 하나 만들어 뒀지. 그다음엔 그의 흔적을 따라 포틀랜드 코브로 가서, 아무 흔적도 남기지 않고 그를 처리하는 거야.";
			link.l1 = "그럼 어디에 심을 건데?";
			link.l1.go = "BM_IronsThirdJungle_27";
		break;
		
		case "BM_IronsThirdJungle_27":
			dialog.text = "하하하, 내가 처럼 좀 더 닮았으면 좋겠다고 말한 게 바로 그 뜻이었소, 선장. 자, 재미없게 굴지 마시오, 눈빛이 이글거리는 게 다 보이는데!";
			link.l1 = "사실, 나는 자네 이야기에 꽤 흥미가 있었네.";
			link.l1.go = "BM_IronsThirdJungle_28";
		break;
		
		case "BM_IronsThirdJungle_28":
			dialog.text = "당연히 자기 집이지! 그게 무슨 질문이야? 그는 포트 로얄에 자리 잡았어. 그러니 너랑 나는 만에 정박할 거야, 무슨 일이 잘못되면 바로 섬을 떠날 수 있게.";
			link.l1 = "그의 집이 어디 있는지 알아?";
			link.l1.go = "BM_IronsThirdJungle_29";
		break;
		
		case "BM_IronsThirdJungle_29":
			dialog.text = "아니. 하지만 알아내는 건 어렵지 않아. 술주정뱅이들한테 물어보면 돼 – 술 한두 잔만 사주면 지들 어미라도 팔 놈들이거든. 자, 내 계획 어때?\n";
			if (GetSummonSkillFromName(pchar, SKILL_ACCURACY) > 24 && GetSummonSkillFromName(pchar, SKILL_GRAPPLING) > 24 && GetSummonSkillFromName(pchar, SKILL_SAILING) > 24)
			{
				link.l1 = "그가 자메이카로 향하는 배의 선장이라면, 항상 그 섬 근해를 순찰하고 있을 거야. 도시에서 뭘 시도하는 것보단 거짓 깃발을 달고 공격하는 게 더 낫지.";
				link.l1.go = "BM_IronsThirdJungle_Sea1";	// Морской вариант
				notification("Skill Check Passed", SKILL_SAILING);
				notification("Skill Check Passed", SKILL_ACCURACY);
				notification("Skill Check Passed", SKILL_GRAPPLING);
			}
			else
			{
				if (GetSummonSkillFromName(pchar, SKILL_SAILING) < 25) notification("Skill Check Failed (25)", SKILL_SAILING);
				if (GetSummonSkillFromName(pchar, SKILL_ACCURACY) < 25) notification("Skill Check Failed (25)", SKILL_ACCURACY);
				if (GetSummonSkillFromName(pchar, SKILL_GRAPPLING) < 25) notification("Skill Check Failed (25)", SKILL_GRAPPLING);
			}
			link.l2 = "완벽하진 않지만, 운에 맡기는 부분도 많군. 그래도 전체적으로 해볼 만해. 나도 함께할게, 토미. 하나는 처리했으니, 다른 놈도 그냥 둘 수 없지, 안 그래?";
			link.l2.go = "BM_IronsThirdJungle_Land1";	// Сухопутный вариант
			link.l3 = "난 네 복수에 끼어들 생각도 없고, 이 모험 때문에 영국과의 관계를 위험에 빠뜨릴 생각도 없어. 이건 너무 운에 달려 있잖아, 토미.";
			link.l3.go = "BM_IronsThirdJungle_Otkaz1";	// Отказ
		break;
		
		case "BM_IronsThirdJungle_Sea1":
			dialog.text = "대담하군, 선장! 점점 마음에 드는걸. 하지만 옛 '프린시피오'의 게이브는 만만한 상대가 아니야\n그 녀석은 그런 배에 있는 다른 선장들보다 훨씬 위험하지.";
			link.l1 = "날 뭘로 보는 거야, 겁쟁이로 보냐, 토미? 우리가 직접 놈을 올라탈 거다. 네가 가서 진심으로 얘기 좀 해 봐. 자리에서 끌어내리기 직전에 흑점을 건네줘.";
			link.l1.go = "BM_IronsThirdJungle_Sea2";
		break;
		
		case "BM_IronsThirdJungle_Sea2":
			dialog.text = "헤, 너는 겁쟁이가 아닐지 몰라도, 저 녀석은 맞아. 물론 약삭빠르긴 하지. 군인이나 자기보다 큰 배를 가진 해적은 절대 공격하지 않아. 그런 배가 지평선에 보이면 요새 그늘 아래로 숨어버린다니까.";
			link.l1 = "흠, 상선들은 어쩌지?";
			link.l1.go = "BM_IronsThirdJungle_Sea3";
		break;
		
		case "BM_IronsThirdJungle_Sea3":
			dialog.text = "그래, 그거면 될 수도 있겠어! 하지만 다시 말하지만, 바크나 바크엔틴보다 큰 배는 안 돼! 게이브는 단순한 겁쟁이가 아니야 - 조심성보다 탐욕이 앞선 적은 한 번도 없었지.";
			link.l1 = "잘 되길 바라자, 토미. 그러니까, 스페인이나 네덜란드 깃발을 단 5등급 바크나 바크틴이군. 네 옛 전우를 만날 준비해!";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_SeaVariant");
		break;
		
		case "BM_IronsThirdJungle_Land1":
			dialog.text = "네가 믿을 만한 녀석인 줄 알았지! 언젠가 잭보다 더 훌륭한 선장이 될지도 모르겠군. 그리고 내 운에 관해서라면... 지금까지 여기까지 데려다줬으니, 또 한 번 믿어보지. 그럼, 가볼까?";
			link.l1 = "그래, 이 일 너무 질질 끌지 말자. 빨리 끝날수록 더 좋으니까.";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_LandVariant");
		break;
		
		case "BM_IronsThirdJungle_Otkaz1":
			dialog.text = "헤, 다르게 기대했지만, 결국 이럴 줄 알았지 - 너 같은 놈은 이런 일 할 배짱이 없어. "+GetSexPhrase("젊은이","내 딸")+". 진짜 선장이라면 그런 식으로 쥐새끼들을 조용히 처리한 적이 몇 번쯤은 있기 마련이지. 가끔은 자기 배의 쥐새끼들까지도 말이야.";
			link.l1 = "내가 그 도발에 넘어가서 마음을 바꿨다고, 내가 진짜 선장임을 증명하겠다고 말하길 바라는 거지, 토미? 하지만 네 복수심은 이해한다. 잭처럼 억지로 널 선원에서 내쫓을 생각은 없어. 그 일에 시간이 얼마나 필요하지? 그때까지 나는 자메이카에 도착할 거야.";
			link.l1.go = "BM_IronsThirdJungle_Otkaz2";
		break;
		
		case "BM_IronsThirdJungle_Otkaz2":
			dialog.text = "하하하, 이제 좀 컸구나. 그 수에 안 넘어가서 거의 존경할 뻔했어. 하지만 굳이 기다렸다가 날 데리러 올 필요 없어 – 이건 내가 알아서 끝낼 거야. 결국 내가 바란 건 내 선장으로서 뭔가 해줄 의지가 있는 사람이었으니까. 그러니 잘 가라. 영국 잘 챙기고, 하하.";
			link.l1 = "넌 정말 이상한 녀석이야. 하지만 네 뜻대로 해. 잘 가라! 그리고 복수, 잘하길 바란다, 토미.";
			link.l1.go = "BM_IronsThirdJungle_Otkaz3";
		break;
		
		case "BM_IronsThirdJungle_Otkaz3":
			DialogExit();
			AddDialogExitQuestFunction("BM_IronsThirdJungle_Otkaz");
		break;
		
		case "BM_IronsJamaicaShore1":
			dialog.text = "좋아, 필요하면 여기서 바로 후퇴할 수 있겠군. 이걸 가져가. Gabe가 어디에 살고 언제 집에 있는지 알아내면 쪽지랑 검은 표식을 그에게 전해 줘.";
			link.l1 = "오, 이제 네가 명령을 내리겠다는 거냐, 토미. 하지만 기억해, 아직도 나는 네 선장이야. 내가 마을에 있는 동안 뭘 할 생각이냐?";
			link.l1.go = "BM_IronsJamaicaShore2";
		break;
		
		case "BM_IronsJamaicaShore2":
			dialog.text = "헤, 그걸 어떻게 잊겠어, Boring 선장? Gabe가 거리에서 나를 보면 경보를 울리거나 섬에서 도망칠 거야, 그 겁쟁이 놈. 걱정 마, 여기서 매복을 준비할 테니까, 헤헤헤.";
			link.l1 = "매복이라고? 좋아, 토미. 네 옛 전우에게 제대로 된 재회를 선사해 주자고, 하하하하!";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_IronsJamaicaGo");
		break;
		
		case "BM_Pyanitsa_0":
			dialog.text = "히크! 이거 끝내주는 럼이군! 히크... 건배!";
				link.l1 = "이봐, 친구, 이 마을에서 가브리엘 캘로우 선장에 대해 무슨 소문 들었어?";
			link.l1.go = "BM_Pyanitsa_1";
			DelLandQuestMark(npchar);	//Удаляем квестмарку
		break;
		
		case "BM_Pyanitsa_1":
			dialog.text = "올드 게이브?! 좋은 얘기만 있지! 왜, 힉, 그게 뭐야?";
			link.l1 = "오, 정말인가? 듣게 되어 기쁘군. 자, 해적 때문에 문제가 좀 있네. 사령관은 주로 육지 일을 맡고 있고, 나는 영주 나리께 폐를 끼치고 싶지 않네.";
			link.l1.go = "BM_Pyanitsa_2";
		break;
		
		case "BM_Pyanitsa_2":
			dialog.text = "그럼 곧장 게이브한테 가라고 했잖아! 이 마을에서 게이브보다 더 정직하고 용감한 선장은 없어. 도일리 대령조차도 그를 높이 평가한다니까. 그가 타는 배는 니콜라스 샤프가 직접 소유했던 배라네, 믿어지나?";
			link.l1 = " 아직 그걸 믿을 만큼 취하지는 않았어, 친구.";
			link.l1.go = "BM_Pyanitsa_3";
		break;
		
		case "BM_Pyanitsa_3":
			dialog.text = "아-아, 맞아, 바로 너야! 프린치피오잖아! 기억나지, 응?";
			link.l1 = "스페인 전리품선이라고? 왜지?";
			link.l1.go = "BM_Pyanitsa_4";
		break;
		
		case "BM_Pyanitsa_4":
			dialog.text = "네가 마지막으로 분홍색 놈을 직접 본 게 언제였지, 응? 내가 무슨 말 하는지 알거든, 으악!";
			link.l1 = "글쎄, 배의 설계가 그렇게 특이한지는 잘 모르겠어.";
			link.l1.go = "BM_Pyanitsa_5";
		break;
		
		case "BM_Pyanitsa_5":
			dialog.text = "하지만 진짜야! 요즘 새 설계들이 이렇게 많은데, 누가 그런 고물에 명령을 내리겠어! 조선소에서 그런 배는 거의 서, 서른 년 전에 만들기를 멈췄다고! 니크가 직접 그 배를 몰았다고, 내가 말하는 거야.";
			link.l1 = "좋아, 내가 사겠어. 그러니까, 이게 그 배라는 거지. 그런데 이런 난파선이 아직도 안 부서진 게 신기하군?";
			link.l1.go = "BM_Pyanitsa_6";
		break;
		
		case "BM_Pyanitsa_6":
			if (sti(pchar.basenation) == ENGLAND) sStr = "our";
			else sStr = "your";
			dialog.text = "글쎄, 이 배도 전성기 때만큼 빠르진 않아. 나도 한 잔 더 마신 뒤엔 그렇지, 하하하! 그래도 좋은 선장이라면 이 늙은 배에서도 뭔가를 뽑아낼 수 있지. 게이브도 이 배를 함포 사선에 세우지 않으려고 애쓰고 있어.";
			link.l1 = "그런데 왜 아직 배 이름을 바꾸지 않은 거지? 어쩌면 폐하의 함선 스래싱 같은 이름으로, 그 아래에서 "+sStr+" 옛 체제?";
			link.l1.go = "BM_Pyanitsa_7";
		break;
		
		case "BM_Pyanitsa_7":
			dialog.text = "전통... 전-전-전통이지, 으악! 니크 본인도 쿠바의 스페인 농장에서 도망친 뒤에 그 배 이름을 바꾸지 않았어. 그 경험을 절대 잊고 싶지 않았던 거지 — 스페인 놈들도 마찬가지였고! 내가 말해줄게, 텐다레스 해안 근처에서 벌어진 그 전투 말이야...";
			if (startHeroType == 4)
			{
				link.l1 = "텐달레스, 맞지? 흠, 내가 그 이름을 마지막으로 들은 건 어릴 때였어. 이제는 아무도 그 버려진 바위들을 기억하거나 아는 사람이 있을 거라고는 생각도 못 했지.";
				link.l1.go = "BM_Pyanitsa_8";
			}
			else
			{
				link.l1 = "텐달레스? 그게 어디야?";
				link.l1.go = "BM_Pyanitsa_8";
			}
		break;
		
		case "BM_Pyanitsa_8":
			dialog.text = "아니면, 으으, 하이록이었나? 아-아니, 거긴 절대 아니었지... 뭐, 어쨌든 상관없어! 닉은 그 분홍색 배에서 싸워 이겼어, 해적 남작 데스몬드 레이 벨트롭이 보낸 커틀피시 브리그를 상대로 믿기 힘든 승리를 거뒀지. 둘은 오랫동안 피를 흘리며 싸웠고, 결국 닉이 데스몬드 본인을 베어버렸어.";
			if (startHeroType == 4)
			{
				link.l1 = "이런 젠장, 대단하군! 뭐, 니콜라스라면 이 정도는 당연하지. 에이, 샤프 집안이랑 벨트롭 집안은 항상 붙었다가 떨어졌다가 하잖아 – 역시 역사는 가끔씩 반복되는 법이지.";
				link.l1.go = "BM_Pyanitsa_9";
			}
			else
			{
				link.l1 = "인상적이군. 그래서, 샤프는 그 배와 어떻게 헤어졌지? 조선소에서 팔았나?";
				link.l1.go = "BM_Pyanitsa_9";
			}
		break;
		
		case "BM_Pyanitsa_9":
			dialog.text = "아니. 그때 승선을 당한 후로 배가 새기 시작해서, 니크가 버렸지. 그러고 나서 큰 조수가 들이닥치자, 그 핑크선이 마을 근처 해안에 밀려왔어.";
			link.l1 = "누가 그 난파선에 관심이나 있었겠어.";
			link.l1.go = "BM_Pyanitsa_10";
		break;
		
		case "BM_Pyanitsa_10":
			dialog.text = "오, 하지만 해군은 관심을 가졌지! 실용적인 녀석들이야. 영국 깃발을 달았지만 스페인 이름을 가진 배를 보고 궁금해했거든. 닉은 몇 년 뒤에 죽었지만, 그의 배는 계속 항해했어. 주인이 피비린내 나는 방식으로 계속 바뀌었지.";
			link.l1 = "이건 그냥 또 하나의 유령선 이야기일 뿐이야. 하지만 게이브의 선장직은 아주 현실적이지. 그러니 나는 그를 만나러 가볼 생각이야. 어디에 사는지 알아?";
			link.l1.go = "BM_Pyanitsa_11";
		break;
		
		case "BM_Pyanitsa_11":
			dialog.text = "하하! 그럼, 히끅, 알지! 다들 알잖아! 늙은 게이브는 오래된 풍차 옆에 살아. 선술집을 돌아서 위를 봐... 히끅!";
			link.l1 = "그 사람 언제 집에 있어? 바쁜 사람인 것 같네.";
			link.l1.go = "BM_Pyanitsa_12";
		break;
		
		case "BM_Pyanitsa_12":
			dialog.text = "맞아, 친구! 그 녀석 할 일이 많지. 집에는 저녁 열 시부터만 들어와. 그리고 매일 아침 여섯 시 정각에 혼자 일어나. 철저한 규율이지!";
			link.l1 = "정말 고마워! 이제 해적 이야기에는 질렸어.";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_SearchGabeHouse");
		break;
		
		case "BM_Callow1":
			if (startHeroType == 4) 
			{
				dialog.text = "정말로... 룸바냐? 네 소문은 들었지만... 네가 동료를 배신한 적은 없었잖아!";
				link.l1 = "그리고 나는 그렇지 않아. 내 불만은 내 조국이 아니라 너야, 게이브.";
				link.l1.go = "BM_Callow_Helena1";
			}
			else
			{
				dialog.text = "너는 상인이 아니군...";
				link.l1 = "놀랐지, 게이브! 네가 조심성 많고 심지어 겁쟁이라는 소문을 들었는데. 탐욕이 네 판단을 흐렸구나, 그렇지? 상인이라면 나처럼 일부러 배에 올라타려 하지 않을 텐데.";
				link.l1.go = "BM_Callow2";
			}
		break;
		
		case "BM_Callow_Helena1":
			dialog.text = "나랑? 무슨 문제라도 있어? 내 방이나 네 방에서 제대로 얘기할 수도 있잖아, 선장들답게 말이야, 그리고... 그런데 넌 여기서 뭐 하는 거야?!";
			link.l1 = "";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_CabinDialog");
		break;
		
		case "BM_Callow2":
			dialog.text = "그래. 그런데 넌 누구냐? 아니, 됐다, 신경 끄자. 저 사람은 누구지...";
			link.l1 = "";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_CabinDialog");
		break;
		
		case "BM_IronsClone1":
			dialog.text = "토마스, 너냐...?";
			link.l1 = "그래, Gabe. 그리고 내가 그날 네가 내게 한 짓에 대해 벌을 주러 왔다.";
			link.l1.go = "BM_IronsClone2";
			sld = &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)];
			CharacterTurnByChr(sld, CharacterFromID("IronsClone"));
			sld = CharacterFromID("IronsClone");
			CharacterTurnByChr(sld, &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)]);
		break;
		
		case "BM_IronsClone2":
			dialog.text = "나를 벌주겠다고?! 말 조심해, 토마스! 벌을 받아야 할 놈이 있다면 그건 바로 너야! 네가 증원군을 데려오겠다고 했잖아! 그런데 우리는 기다리기만 했고, 왕의 기병대 총알과 칼날 아래서 죽어갔어!";
			link.l1 = "나는 미친 듯이 달려가서 도움을 청했어! 그런데 또 다른 빌어먹을 놈들이 덮쳐 왔지! 찰스 그 자식의 추종자들이 사방에 깔려 있었어! 놈들이 날 포위해서, 거의 죽을 뻔했다고! 다행히 놈들이 내가 죽은 줄 알았지. 그런데, 게이브, 내가 뭘 봤는지 아니?!";
			link.l1.go = "BM_IronsClone3";
		break;
		
		case "BM_IronsClone3":
			dialog.text = "무슨 일이야, 톰? 이 사람을 계속 믿게 하려고 아무 이야기나 지어낼 셈이냐?!";
			link.l1 = "헤, 그 남자는 어차피 나를 배신하지 않아. 어떤 놈들처럼 쥐새끼는 아니거든.";
			link.l1.go = "BM_IronsClone4";
		break;
		
		case "BM_IronsClone4":
			dialog.text = "그 자식은 선택의 여지가 없어! 영국 해군의 배를 공격하다니!";
			link.l1 = "오, 그는 처음부터 선택권이 있었어. 그리고 나를 돕기로 선택했지. 너랑 프랭키도 선택할 수 있었어. 너희는 죽지 않으려고 도망치는 걸 택했지. 그리고 나서 돌아와서, 반쯤 죽어 있는 나를 발견했어. 그리고 재판에서 너희 더러운 거짓말을 늘어놨지. 내가 머리를 맞고 기억을 잃어서 아무도 내 말을 듣지 않을 거란 걸 너희는 알고 있었잖아!";
			link.l1.go = "BM_IronsClone5";
		break;
		
		case "BM_IronsClone5":
			dialog.text = "어차피 아무도 네 말을 듣지 않았을 거야. 넌 예전부터 항상... 엉망이었지, 토마스.";
			link.l1 = "오, 그날 네가 한 짓을 숨기지 않는구나. 너한테 줄 게 있어, 게이브. 바로 검은 표식이지. 하지만 이제 와서 이걸 너한테 준들 무슨 소용이겠냐? 배는 이미 빼앗겼고, 곧 네 배를 갈라놓을 테니까. 히히히히히히...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("BM_IronsClone5_function"); // здесь переход на кейс с боёвкой
		break;
		
		case "BM_IronsClone8":
			dialog.text = "글쎄, 게이브는 이제 쫓겨났지, 헤헤헤. 오래전부터 이 말 하고 싶었어. 이제 네가 더는 못 듣는 게 아쉽구나, 친구. 아, 잠깐! 들을 수도 있겠지 - 지옥에서.";
			link.l1 = "가자, 토미. 그가 듣지 못했다 해도, 네 계략이자 복수라는 걸 보고 다 알았지. 그리고 그가 할 수 있는 건 아무것도 없었어.";
			link.l1.go = "BM_IronsClone9";
		break;
		
		case "BM_IronsClone9":
			if (startHeroType == 4) 
			{
				dialog.text = "헤, 네 말이 맞아! 완전 맞지! 이번 일 도와줘서 고맙다. 있잖아, 난 네가 그냥 멋 부린 옷 입고 배나 끌고 다니는 응석받이 아가씨인 줄 알았거든. 근데 너 진짜 멋진 선장이더라! 잭도 너한테 한 수 접고 갈걸.";
			}
			else
			{
				dialog.text = "헤헤, 네 말이 맞아! 완전 맞지! 이번 일 도와줘서 고맙다. 있잖아, 너도 잭만큼 훌륭한 선장인 것 같아. 아니, 어쩌면 더 나을지도!";
			}
			link.l1 = "오, 이제 나를 치켜세우는군. 고맙다. 그래, 뭐.";
			link.l1.go = "BM_IronsClone10";
		break;
		
		case "BM_IronsClone10":
			dialog.text = "전혀 아니야. 아부 따위는 없어. 너도 알다시피, 내가 그렇게 누구를 칭찬하는 일은 드물지. 그러니까 입 닥치고 내가 너를 높이 평가한다는 사실이나 기뻐해라\n";
			link.l1 = "네가 날 좋은 선장이라고 생각해줘서 기쁘긴 한데, 네가 말하는 방식은 마음에 들지 않아. 하지만... 명령 체계야, 토미, 명령 체계라고.";
			link.l1.go = "BM_IronsClone11";
		break;
		
		case "BM_IronsClone11":
			if (startHeroType == 4) 
			{
				dialog.text = "아, 왜 이래! 우리가 겪은 모든 일들이 우리를 더 가깝게 만든 것 같아, 엘리. 우린 단순히 선장과 장교 그 이상이 될 수도 있어. 인정해, 네 마음속으로라도. 너도 느끼고 있잖아.";
				link.l1 = "네 꿈속에서나 가능하지, 토미. 그리고 내 이름은 엘리가 아니라 헬렌이야. 뭐, 이제는 나를 룸바라고 불러도 되겠지만.";
				link.l1.go = "BM_IronsClone12";
			}
			else
			{
				dialog.text = "아, 제발 좀, 재미없게 굴지 마! 이제 우리 단순히 선장과 장교 사이가 아니라 진짜 친구가 된 것 같지 않아? 너도 그렇게 생각하지?!";
				link.l1 = "헤. 그럴지도. 네 적이 되는 것보단 친구가 되는 게 낫지. 그리고 예의범절은 네 스타일이 아닌 것 같으니, 그냥 익숙해져야겠군.";
				link.l1.go = "BM_IronsClone12";
			}
		break;
		
		case "BM_IronsClone12":
			dialog.text = "선장님, 당신을 위한... 선물이 있습니다.";
			link.l1 = "이봐, 저거 좀 봐! 검은 점이잖아? 너도 나를 쫓아내고 싶다는 거냐, 토미? 네가 직접 선장이 되고 싶어서 그래? 하하하하! 우리가 친구라고 하지 않았냐?";
			link.l1.go = "BM_IronsClone13";
			GiveItem2Character(PChar, "talisman15");		//Предмет Чёрная Метка
		break;
		
		case "BM_IronsClone13":
			dialog.text = "이건 블랙 마크야, 이 멍청아. 있잖아, 내가 이 스카프에 해골과 뼈를 수놓은 순간부터 운이 트이기 시작한 것 같아. 설명은 못 하겠어. 가져가. 그리고... 원하면 내 믿음직한 검이랑 갑옷도 빌려줄게... 남아 있는 건 좀밖에 없지만, 하하! 분명 쓸모가 있을 거야! 넌 멀리 갈 놈이야. 내가 그걸 직접 보고 싶어. 괜히 어이없이 총알 맞고 죽지는 마라.";
			link.l1 = "고마워, 친구! 최선을 다할게. 그리고 너는... 잘 보고 감탄이나 해라, 하하하!";
			link.l1.go = "BM_IronsClone14";
		break;
		
		case "BM_IronsClone14":
			dialog.text = "감탄하라고? 그래, 하하하. 그래. 그래서, 이 배를 어떻게 할 생각이냐? 한편으론 이제 쓸모가 별로 없지. 하지만 또 한편으론 이런 배는 더 이상 없어. 앞으로도 다시는 이런 배를 못 볼 거라 생각한다네.";
			if (startHeroType == 4) 
			{
				link.l1 = "아직 결정 못 했어... 있잖아, 토미, 이 배랑 뭔가 연결된 느낌이 들어. 설명은 못 하겠어. 그러니까, 우선 이 썩은 시체부터 치우자. 창고에 물이 새지 않으면, 아마 이 녀석은 내가 가져갈 거야.";
			}
			else
			{
				link.l1 = "나도 모르겠어, 토미. 아직 결정하지 않았어. \n그동안 게이브 시체부터 치우자. 혹시라도 우리가 이 배를 갖게 될지도 모르니까.";
			}
			link.l1.go = "BM_IronsClone15";
		break;
		
		case "BM_IronsClone15":
			DialogExit();
			LAi_EnableReload();
			Log_SetActiveAction("Reload");
		break;
		
		case "BM_IronsPinkPotopil1":
			dialog.text = "그래, 그 낡은 배를 잘 다뤘구먼, 선장! 그리고 내가 직접 게이브를 끝장내고 싶었지만, 이 승리를 깎아내려 창조주를 노하게 하진 않겠네.";
			link.l1 = "그럴 필요 없네, 토미. 이제 네 영혼이 평안하길 바란다.";
			link.l1.go = "BM_IronsPinkPotopil2";
		break;
		
		case "BM_IronsPinkPotopil2":
			if (startHeroType == 4) 
			{
				dialog.text = "우리가 함께 겪은 모든 일이 우리를 더 가깝게 만든 것 같아, 엘리. 우리는 단순히 선장과 장교 그 이상이 될 수도 있어. 인정해, 비록 네 마음속으로만이라도, 너도 느끼고 있잖아.";
				link.l1 = "네 꿈에서나 가능하지, 토미. 그리고 내 이름은 헬렌이야, 엘리가 아니고. 하지만 아첨만 그만두면 이제 날 룸바라고 불러도 돼.";
			}
			else
			{
				dialog.text = "내 평생 이렇게 행복했던 적은 없어! 이번 일 도와줘서 고마워. 있잖아, 네가 선장으로서 잭만큼 훌륭하다고 생각해. 아니, 어쩌면 더 나을지도 몰라!";
				link.l1 = "아, 과찬이십니다. 비교까지 해주시니 감사하군요.";
			}
			link.l1.go = "BM_IronsPinkPotopil3";
		break;
		
		case "BM_IronsPinkPotopil3":
			if (startHeroType == 4) 
			{
				dialog.text = "전혀 아니야. 아부 같은 건 없어. 지금쯤 눈치챘겠지만, 난 그런 식으로 아무나 칭찬하지 않아. 그러니까 입 닥치고 내가 너를 높이 평가한다는 걸 기뻐해.";
				link.l1 = "네가 그렇게 말하는 방식이 마음에 들진 않지만, 나를 대체로 좋은 선장이라고 생각해줘서 기쁘다. 하지만... 지휘 체계 말이야, 토미, 지휘 체계.";
			}
			else
			{
				dialog.text = "전혀 아니야. 아부 따위는 없어. 너도 이제 눈치챘겠지만, 내가 그렇게 누구를 칭찬하는 일은 거의 없거든. 그러니까 입 다물고 내가 널 높이 평가한다는 걸 기뻐해라.";
				link.l1 = "네가 그렇게 말하는 방식이 마음에 들진 않지만, 대체로 나를 좋은 선장으로 생각해줘서 기쁘다. 하지만... 명령 체계 말이다, 토미, 명령 체계.";
			}
			link.l1.go = "BM_IronsPinkPotopil4";
		break;
		
		case "BM_IronsPinkPotopil4":
			if (startHeroType == 4) 
			{
				dialog.text = "아, 제발 좀, 재미없는 녀석! 이제 우리 둘은 단순히 선장과 부관이 아니라 진짜 친구가 된 것 같지 않아? 너도 그렇게 생각하지?!";
				link.l1 = "헤. 그럴지도. 네 적이 되는 것보단 친구가 되는 게 낫지. 그리고 예법 따위엔 관심 없는 것 같으니, 그냥 익숙해져야겠군.";
			}
			else
			{
				dialog.text = "아, 제발 좀 해라, 이 지루한 놈아! 이제 우리 둘은 단순히 선장과 부하가 아니라 진짜 친구 사이라고 생각하는데, 너도 그렇게 생각하지 않냐?!";
				link.l1 = "헤. 그럴지도 모르지. 네 적이 되는 것보단 친구가 되는 게 낫지. 그리고 예의범절은 네 취향이 아닌 것 같으니, 그냥 익숙해져야겠군.";
			}
			link.l1.go = "BM_IronsPinkPotopil5";
		break;
		
		case "BM_IronsPinkPotopil5":
			if (startHeroType == 4) 
			{
				dialog.text = "선장님, 당신을 위한... 선물이 있소.";
			}
			else
			{
				dialog.text = "선장님, 당신을 위한... 선물이 있어요.";
			}
			link.l1 = "이봐, 저거 좀 봐! 검은 점이잖아? 너도 나를 쫓아내고 싶다는 거냐, 토미? 네가 직접 선장이 되고 싶어? 하하하하! 우리가 친구라고 하지 않았냐?";
			link.l1.go = "BM_IronsPinkPotopil6";
		break;
		
		case "BM_IronsPinkPotopil6":
			dialog.text = "이건 블랙 마크야, 이 멍청아. 있잖아, 내가 이 스카프에 해골과 뼈 자수를 놓은 순간부터 운이 트이기 시작한 것 같아. 설명은 못 하겠어. 가져가. 그리고... 원하면 내 믿음직한 검이랑 갑옷도 빌려줄 수 있어... 남아 있는 것들이지만, 하하! 쓸모 있을 거야! 넌 크게 될 놈이야. 내가 그걸 직접 보고 싶어. 어이없는 총알에 죽는 꼴은 보고 싶지 않거든.";
			link.l1 = "고마워, 친구! 최선을 다할게. 그리고 너는 잘 보고 감탄이나 해, 하하하!";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_PinkPotopil_4");
			GiveItem2Character(PChar, "talisman15");		//Предмет Чёрная Метка
		break;
		
		case "BM_GabeHouseGood1":
			Notification_Reputation(true, 71, "low");
			if (startHeroType == 4)
			{
				dialog.text = "그런 걸 누가 믿겠어... 미안해, 아가씨. "+TimeGreeting()+". 무엇을 도와드릴까요? 무척 걱정스러워 보이시네요.";
			}
			else
			{
				dialog.text = "뭐야? 이 늦은 시간에 누가 오는 거지? 꽤 걱정스러워 보이는데, 나리. 내가 뭘 도와줄까?";
			}
			link.l1 = "쉬고 계신데 방해해서 죄송합니다, Callow 선장. 제 이름은 "+GetFullName(pchar)+", 그리고 나는 그대의 옛 전우 중 한 사람을 대신해 왔소.";
			link.l1.go = "BM_GabeHouseGood2";
		break;
		
		case "BM_GabeHouseGood2":
			dialog.text = "어떤 동무 말인가? 나는 구세계에서도, 신세계에서도 동무가 많았지.";
			link.l1 = "처음에는 네 트렁크 중 하나에 뭔가를 남겨두려고 했어. 아니면 네가 더 빨리 알아차릴 수 있게 탁자 위에 둘까도 생각했지. 네 과거와 관련된 남자에 관한 거야. 여기, 직접 보고 읽어봐.";
			link.l1.go = "BM_GabeHouseGood3";
		break;
		
		case "BM_GabeHouseGood3":
			dialog.text = "검은 표? 내 동료 중에 해적이 있었던가? 아니면 몇몇 녀석들이 그 길로 빠졌나? 검은 비단이라고? 정말이야... 오, 토마스. 너 같은 사람이 그 악당과 어울린다니 놀랍군.";
			link.l1 = "미안하지만, 그를 악당이라고 부를 자격은 당신에게 없어. 당신은 전장에서 도망쳤고 톰을 중상했지. 나중에 후회해서 이 군도에서 모범적인 장교가 되었을지라도, 과거는 변하지 않아.";
			link.l1.go = "BM_GabeHouseGood4";
		break;
		
		case "BM_GabeHouseGood4":
			dialog.text = "그가 그렇게 말했나? 놀랄 일도 아니지 - 그 자는 언제나 제 이야기를 잘 들어줄 사람을 찾아내는 재주가 있었으니까. 토마스는 말재주가 뛰어났지. 자네는 그를 모르고, 진짜 이야기도 모르며, 지금 뭘 겪게 될지도 모를 거야. 내가 말해주지 - 어차피 이제 잠도 못 잘 테니.";
			link.l1 = "듣는 건 언제나 나쁠 게 없지. 계속 말해봐, Callow 선장.";
			link.l1.go = "BM_GabeHouseGood5";
		break;
		
		case "BM_GabeHouseGood5":
			dialog.text = "그래서, 토마스가 내가 도망쳤고 그다음에 자기 명예를 더럽혔다고 주장한다고? 글쎄, 사실은 그 반대였다는 걸 알아둬! 왕의 기병대가 다가왔을 때, 톰이 증원군을 데리러 간다고 했지. 그래서 우리는 후퇴하지 않고 기다렸어. 우리 중대 전원이 몰살당했다고! 만약 톰이 약속한 증원군을 기다리지 않았다면, 우린 철수해서 살 수 있었을 거야! 결국 살아남은 건 나랑 프랭키, 그리고 빌어먹을 토마스 셋뿐이었지.";
			link.l1 = "그러니까 네 말은...";
			link.l1.go = "BM_GabeHouseGood6";
		break;
		
		case "BM_GabeHouseGood6":
			dialog.text = "우리 동료들의 피가 왕당파 놈들만큼이나 톰의 손에도 묻었다고 말하는 거야. 그 자식, 교수형 대신 강제노역형을 받은 것만 해도 운이 좋은 줄 알아야지! 그런데도 감히 나한테 원한을 품고 결투를 신청하다니! 그럴 자격도 없는 놈이야!\n";
			link.l1 = "안 가겠다는 건가? 그게 무슨 뜻인지 알지. 명예의 법은 모두에게 적용되는 거야.";
			link.l1.go = "BM_GabeHouseGood7";
		break;
		
		case "BM_GabeHouseGood7":
			dialog.text = "물론이지. 그래서 내가 가려고 하는 거야. 우리 공화국 법정이 톰의 과거 군 경력 때문에 끝내지 못한 일을 마무리해야 해. 그리고 너... 너는 괜찮은 사람처럼 보이네. 사람을 좀 더 신중하게 사귀는 게 좋을 거야. 톰 같은 놈들이랑 엮이지 마.";
			link.l1 = "하지만 토마스는 이제 내 부하야, 내 배의 장교지. "+GetSexPhrase("내가 그를 지켜볼 테니, 자네와의 만남에서 살아남는다면 더 이상 망신당하지 않게 하겠네.","")+"";
			link.l1.go = "BM_GabeHouseGood_Tommi1";
			link.l2 = "내 입장이라면 어떻게 하겠소, Callow 선장?";
			link.l2.go = "BM_GabeHouseGood_Gabe1";
		break;
		
		case "BM_GabeHouseGood_Tommi1":
			dialog.text = "에이, 톰이 그 얘기로 너를 설득했다면 또다시 그렇게 하는 건 식은 죽 먹기겠지.";
			link.l1 = ""+GetSexPhrase("하지만 명예의 법도에 따라, 나는 그를 배신할 수 없어. 나는","나는")+" 내 부하들에게 책임이 있지... 나는 그 자처럼 되지 않을 거야. 그리고 이제부터는 그를 더 조심스럽고 비판적으로 대할 거야, 만약 그가 살아남는다면.";
			link.l1.go = "BM_GabeHouseGood_Tommi2";
		break;
		
		case "BM_GabeHouseGood_Tommi2":
			dialog.text = "어려운 결정이군. 하지만 네 마음을 바꿀 생각은 없어. 그럼, 잘 가라, "+GetSexPhrase("나리","아가씨")+" - 아직 Tom을 만날 준비를 해야 해.";
			link.l1 = "안녕히 가십시오, Callow 선장.";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_GoToJamaicaJungle_TommiPlan");
		break;
		
		case "BM_GabeHouseGood_Gabe1":
			dialog.text = "정의가 실현되게 하자! 토머스를 무너뜨리는 데 나를 도와줘, "+pchar.lastname+". 놈은 보기 드문 악당이자 겁쟁이지만, 사격 솜씨만큼은 뛰어나. 쉽지 않을 거야. 하지만 우리 함께라면...";
			link.l1 = "흠, 토마스를 쓰러뜨리는 걸 도와달라고? 그런 결투에 무슨 명예가 있겠나? 너희끼리 해결해라, 나는 빠지겠어.";
			link.l1.go = "BM_GabeHouseGood_Gabe2";
		break;
		
		case "BM_GabeHouseGood_Gabe2":
			dialog.text = "그 자를 아는 내가 보기에, 공정한 결투는 기대도 안 해. 중립을 지키는 건 결국 불의를 용인하는 거야. 내가 틀렸나?";
			link.l1 = "너는 나보다 톰을 더 잘 아는 것 같군, 그리고 그 녀석이 어떤 놈인지도. 네 말이 맞아 – 그는 이미 포틀랜드 만에 매복을 준비하고 있고, 내 도움이 필요하다고 생각하고 있지 – 지금 네가 그러는 것처럼.";
			link.l1.go = "BM_GabeHouseGood_Gabe3";
		break;
		
		case "BM_GabeHouseGood_Gabe3":
			dialog.text = "그렇다면 결투가 아니라 그냥 싸움이군. 하지만 내가 토마스를 직접 죽이자고 하는 건 아니야. 우리가 그를 체포하자! 내가 병사들을 데려올 테니, 구세계에서 못 끝낸 일을 여기서 마무리하자고. 또다시 그를 변명하려 든다면, 내가 대령에게 편지를 쓰거나 직접 이곳으로 데려와 재판을 열게 하겠어. 토마스가 무기를 내려놓지 않는다면, 그건 전적으로 그의 잘못이지.";
			link.l1 = "그게 훨씬 낫게 들리는군.";
			link.l1.go = "BM_GabeHouseGood_Gabe4";
		break;
		
		case "BM_GabeHouseGood_Gabe4":
			dialog.text = "그 말 들으니 기쁘군, "+pchar.lastname+"! 이런 결정을 내리기 쉽지 않다는 건 잘 압니다만, 분명 옳은 선택을 하셨습니다. 그리고 그 선택이 옳았다는 걸 확실히 하기 위해, 제가 다른 일도 도와드리겠습니다.";
			link.l1 = "무슨 일이오, Callow 선장?";
			link.l1.go = "BM_GabeHouseGood_Gabe5";
		break;
		
		case "BM_GabeHouseGood_Gabe5":
			dialog.text = "여기, 이걸 가져가. 선물은 아니고, 빌려주는 거야. 토마스는 내가 말했듯이 정말 싸움을 잘하는 놈이라, 녹슨 쇳조각 말고 제대로 된 무기로 상대하는 게 낫지. 이 멋진 검은 도일리 대령님이 직접 내게 주신 거지만, 진짜 싸움이라면 난 언제나 브로드소드부터 집어 들 거야.";
			link.l1 = "정말 훌륭한 레이피어군. 고맙다.";
			link.l1.go = "BM_GabeHouseGood_Gabe6";
			GiveItem2Character(PChar, "blade_40");
		break;
		
		case "BM_GabeHouseGood_Gabe6":
			dialog.text = "고마워할 필요 없어 - 내가 너한테 빌려주는 거지 주는 게 아니란 거 기억해라? 이제 만으로 가서 우리 친애하는 톰이랑 네 역할을 해. 나는 지원군을 모으고 있을 테니. 거기서 보자.";
			link.l1 = "거기서 봅시다, Callow 선장.";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_GoToJamaicaJungle_GabePlan");
		break;
		
		case "BM_GabeHouseNeutral1":
			Notification_Reputation(false, 71, "low");
			if (startHeroType == 4)
			{
				dialog.text = "이봐, 아가씨, 누구시죠? 주소를 잘못 찾으신 것 같은데. 나는, 어, 하룻밤 서비스 같은 건 주문한 적 없소.";
				link.l1 = "헬렌 맥아더야. 그리고 네 욕망 좀 자제해, 캘로우 씨. 난 제대로 된 아가씨거든. 우리 기후가 밤에도 덥게 만들어. 그런 말을 처음 보는 여자한테 하다니, 부끄럽지도 않아? 너 훌륭한 장교라고 들었는데.";
				link.l1.go = "BM_GabeHouseNeutral2";
			}
			else
			{
				dialog.text = "너 누구야, 그리고 뭘 원하는 거지? 네 그 비웃는 표정 마음에 안 들어, 나리.";
				link.l1 = ""+GetFullName(pchar)+". 그리고 당신은 별로 환대하지 않는군, Callow 나리.";
				link.l1.go = "BM_GabeHouseNeutral2";
			}
		break;
		
		case "BM_GabeHouseNeutral2":
			dialog.text = "이 시간에는 낯선 사람을 다르게 맞이하나?";
			link.l1 = "다른 때는 집에 없다고 들었어.";
			link.l1.go = "BM_GabeHouseNeutral3";
		break;
		
		case "BM_GabeHouseNeutral3":
			dialog.text = "당연히 아니지 - 나는 임무와 의무, 그리고 정직한 노동이 있거든. 네 꼴을 보아하니 이런 말들은 너한텐 생소한 것 같군.";
			link.l1 = "참 자신감이 넘치는군! 하지만 그렇지 않았다면 도일리 대령과 다른 이들에게 네가 정직하다는 걸 설득하지 못했겠지. 나는 너한테 바랄 게 없지만, 네 옛 지인이 필요로 하는 게 있더군, 게이브. 자, 받아라.";
			link.l1.go = "BM_GabeHouseNeutral4";
		break;
		
		case "BM_GabeHouseNeutral4":
			dialog.text = "납득했어? 게이브? 이봐! 흑점이라고? 그럼 너 해적이란 거야? 잠깐만... 검은 비단... 이게 혹시... 아, 알겠다. 토마스, 이 빌어먹을 자식, 아직도 나랑 프랭크가 널 고발한 거 때문에 화가 난 거냐, 하하하하!";
			link.l1 = "이봐! 톰은 내 배의 장교이고 존경받아 마땅한 사람이야. 그는 이 군도의 최고의 사수 중 한 명이지.";
			link.l1.go = "BM_GabeHouseNeutral5";
		break;
		
		case "BM_GabeHouseNeutral5":
			dialog.text = "나는 그가 사격을 못한다고 말한 게 아니야. 하지만 자네는 토마스를 잘 모르는군. 그 녀석이 우리 모두를 배신한 장본인이야. 그래도 자네랑 말다툼해봤자 소용없겠지\n둘이 정말 잘 어울리는구만.";
			link.l1 = "신경 안 써. 그런 얘기는 도일리랑 그 멍청한 놈들한테나 해. 네가 소문대로 용감하고 명예로운 놈이라면, 도전을 받아들이고 지금 당장 와라. 자, 받아들이겠냐?";
			link.l1.go = "BM_GabeHouseNeutral6";
		break;
		
		case "BM_GabeHouseNeutral6":
			dialog.text = "알겠어, 알겠다고. 이제 당장 내 집에서 나가, 안 그러면 경비병을 부를 거야.";
			link.l1 = "기꺼이 그러지, Gabe.";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_GoToJamaicaJungle_TommiPlan");
		break;
		
		case "BM_IronsJamaicaJungle1":
			if (CheckAttribute(pchar, "questTemp.BM_GabePlan"))
			{
				dialog.text = "왜 이렇게 안절부절못해? 무섭기라도 한 거야, 뭐야?";
				link.l1 = "머스킷을 들고 달려오는 남자를 보면 누구라도 긴장하지. 처음엔 네가 누군지 못 알아봤어. 여기서 뭐 하는 거야, 토미?";
				link.l1.go = "BM_IronsJamaicaJungle_GabePlan_2";
			}
			else
			{
				dialog.text = "어떻게 됐어? 이봐, 이봐, 왜 그렇게 날 쳐다보는 거야? 깜짝 놀랐잖아, 헤헤헤.";
				link.l1 = "누가 누구를 겁주고 있는 거야! 누가 저렇게 도망치고 있지?! 우리가 만으로 손님들을 맞이하기로 했잖아!";
				link.l1.go = "BM_IronsJamaicaJungle2";
			}
		break;
		
		case "BM_IronsJamaicaJungle_GabePlan_2":
			dialog.text = "헤, 뭐, 그럴 수도 있지. 나는 기다리는 게 지겨워졌거든 – 우리 귀한 손님들이나 너나. 그래서 제대로 매복하려면 이곳이 더 낫겠다 싶었지. 어차피 나는 결투사가 아니라 사냥꾼이니까.";
			link.l1 = "알겠군.";
			link.l1.go = "BM_IronsJamaicaJungle_GabePlan_3";
		break;
		
		case "BM_IronsJamaicaJungle_GabePlan_3":
			dialog.text = "그래. 내 선물을 게이브 집에 두고 왔나? 꽤 오래 걸렸군. 내가 마을에 들어갈 수만 있다면 훨씬 빨랐을 텐데. 선장, 뭘 그렇게 두리번거리고 있어? 무슨 문제라도 있나?";
			if (IsCharacterPerkOn(pchar, "Trustworthy"))
			{
				link.l1 = "(믿음직한) 나 긴장돼. 게이브는 겁쟁이지만 멍청이는 아니야. 만약 그 대신 군인들 한 부대가 여기로 오면 어쩌지? 아니면 저쪽 만으로 접근해서 우리 배부터 침몰시키면 어떡하지?";
				link.l1.go = "BM_IronsJamaicaJungle_GabePlan_VD1";
				Notification_Perk(true, "Trustworthy");
			}
			else
			{
				link.l2 = "게이브가 나를 봤어. 나는 도망쳐야 했어.";
				link.l2.go = "BM_IronsJamaicaJungle_GabePlan_4";
				Notification_Perk(false, "Trustworthy");
			}
		break;
		
		case "BM_IronsJamaicaJungle_GabePlan_VD1":
			dialog.text = "헤, 나도 알아. 사실 나도 이게 제대로 될지 확신은 없어. 이런 큰일은 네게 처음이지? 괜찮아, 다들 겪는 일이야. 나는 다 계획해 놨어. 군인들이 게이브 없이 오면 그냥 떠나면 돼. 게이브랑 같이 오면, 내가 그놈 눈 사이에 총알 박아주고, 또 그냥 떠나면 돼. 만약 배가 만에 들어오면, 마룬 타운으로 달리는 거야. 거긴 감히 못 쫓아올 테니까, 그다음에 뭘 할지 정하면 돼.";
			link.l1 = "네가 정말 모든 걸 다 생각했구나, 토미.";
			link.l1.go = "BM_IronsJamaicaJungle_GabePlan_VD2";
		break;
		
		case "BM_IronsJamaicaJungle_GabePlan_VD2":
			dialog.text = "물론이지. 이제 우리 손님을 기다리자...";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_GabePlan_GazgovorTommiAndGabe");
		break;
		
		case "BM_IronsJamaicaJungle_GabePlan_4":
			dialog.text = "하하, 네가 도둑질을 잘하는 만큼 나는 왕당파지. 그런데 왜 내 눈을 못 쳐다보는 거지... 선장? 아까 게이브랑 얘기하고 있었지?";
			link.l1 = "아니, 무슨 소리야? 내가 왜 걔한테 말이라도 걸겠어?";
			link.l1.go = "BM_IronsJamaicaJungle_GabePlan_5";
		break;
		
		case "BM_IronsJamaicaJungle_GabePlan_5":
			dialog.text = "너희들은 입만 살아서 그렇지. 맨날 말만 하지. 그래서, 우리 귀여운 게이브가 너희한테 뭐라고 했는데?";
			link.l1 = "그게 중요해, 토미?";
			link.l1.go = "BM_IronsJamaicaJungle_GabePlan_6";
		break;
		
		case "BM_IronsJamaicaJungle_GabePlan_6":
			dialog.text = "솔직히, 아니. 네가 내 등에 칼만 꽂지 않는다면야 상관없지. 하지만 이미 꽂은 것 같군. 그 녀석이 너를 자기 편으로 끌어들였지, 안 그래?";
			link.l1 = "아니. 꼭 그런 건 아니야. 총 내려, 토미. 약속할게, 돌이킬 수 없는 일은 일어나지 않아도 돼. 채석장에서 일할 수도 있겠지. 내가 게이브에게 자비를 베풀어 달라고 부탁할게. 필요하다면 도일리 대령에게도 부탁하겠어.";
			link.l1.go = "BM_IronsJamaicaJungle_GabePlan_7";
		break;
		
		case "BM_IronsJamaicaJungle_GabePlan_7":
			dialog.text = "참 착한 사마리아인이시군. 내가 채석장에서 몇 년을 보내고 이제야 폐를 토해내게 해주다니, 자비롭기도 하지. 하지만 난 다시는 죄수선으로 돌아가지 않아. 절대 다시는. 그리고 너... 널 보니 딱 알겠더라, 또 다른 쥐새끼일 뿐이라는 걸. 네 꼴을 보니 뭔가 수상했지. 먼저 너부터 처리하겠다. 그래야 나중에 게이브를 상대하기가 쉬울 테니까.";
			link.l1 = "우리에겐 선택지가 없게 만드는군!";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_GabePlan_BitvaSTommi");
		break;
		
		case "BM_GabePlan_TommiMertv":
			dialog.text = "흠, 보아하니 이미 해냈군, "+GetSexPhrase("나리","아가씨")+". 그리고 나는 병력을 모으고 있었지. 수적으로 우세하면 톰도 두 번 생각하고 무기를 내려놓을 거라고 생각했거든.";
			link.l1 = "꽤 오래 걸렸군, Callow 선장.";
			link.l1.go = "BM_GabePlan_TommiMertv2";
		break;
		
		case "BM_GabePlan_TommiMertv2":
			dialog.text = "내가 말했잖아, 사람들을 모으고 있었다고. 우리 주둔지에서 제일 좋은 놈들이지. 톰은 어쨌든 노련한 군인이고. 그런데 내가 이걸 누구한테 말하고 있는 거지? 잘했어,\n "+GetSexPhrase("나리","아가씨")+" "+pchar.lastname+". "+GetSexPhrase("자랑스럽구나, 젊은이","인정해야겠군, 아가씨는 아름다움, 지성, 그리고 실력을 고루 갖췄구나")+". 처음 만났을 때 내가 말했듯이, 너는 옳은 결정을 내렸어. 이제 정의가 실현되었군.";
			link.l1 = "그렇게 잘 풀렸군. 자랑스럽냐?";
			link.l1.go = "BM_GabePlan_TommiMertv_Konflict";
			link.l2 = "글쎄, 나는 노련한 군인은 아니지만, 방금 봤듯이 싸울 수는 있지. 하지만 고맙소, 나리. 정의는 내게 결코 헛된 말이 아니오.";
			link.l2.go = "BM_GabePlan_TommiMertv_Mir";
		break;
		
		case "BM_GabePlan_TommiMertv_Mir":
			dialog.text = "그건 칭찬할 만하군, "+GetSexPhrase("젊은이","아가씨")+". 하지만 이 멋진 하루를 완성하려면 아직 한 가지 더 해야 할 일이 남아 있지.";
			link.l1 = "흠, 그게 뭔데? 어차피 톰은 이미 졌잖아.";
			link.l1.go = "BM_GabePlan_TommiMertv_Mir2";
		break;
		
		case "BM_GabePlan_TommiMertv_Mir2":
			dialog.text = "내 물건이 네 손에 있군. 내 아름다운 이탈리아제 레이피어를 돌려줘. 그건 그냥 이쑤시개가 아니라, 대령 도일리께서 직접 주신 기념품이란 말이야.";
			if (!CheckCharacterItem(PChar, "blade_40"))
			{
				link.l1 = "에... 그게 말이오, Callow 선장... 레이피어가 없어졌소. 내가 잃어버렸소. 미안하오.";
				link.l1.go = "BM_GabePlan_TommiMertv_Poteryal";			//Потеряли Рапиру
				break;
			}
			if (CheckCharacterItem(PChar, "blade_40"))
			{
				link.l2 = "아, 물론이지. 가져가시오. 훔치려던 건 아니었소. 거짓말은 안 하겠소 - 사실 가지고 있고 싶었소. 하지만 여기 있소, Callow 선장.";
				link.l2.go = "BM_GabePlan_TommiMertv_Soglasen";			//Согласен
			}
			if (CheckCharacterItem(PChar, "blade_42"))
			{
				link.l3 = "선장님, 당신께 더 나은 제안을 하나 드리겠습니다.";
				link.l3.go = "BM_GabePlan_TommiMertv_Obmen";			//Обмен
			}
			link.l4 = "근데 방금 그걸 이쑤시개라고 했잖아. 게다가 너는 레이피어도 별로 안 좋아한다고 했고. 반면에 나는 보상을 받을 만하지.";
			link.l4.go = "BM_GabePlan_TommiMertv_Otkaz";				//Отказ
		break;
		
		case "BM_GabePlan_TommiMertv_Soglasen":
			dialog.text = "누구라도 이런 미녀를 갖고 싶어 했을 거야! 그녀를 돌려줘서 고맙다. 네 입장이라면 많은 사람들이 고집을 부렸을 텐데.";
			link.l1 = "네 거다. 이제 우리 할 일은 끝난 거지?";
			link.l1.go = "BM_GabePlan_TommiMertv_Platok";
			RemoveCharacterEquip(pchar, BLADE_ITEM_TYPE);
			TakeItemFromCharacter(pchar, "blade_40");
			AddCharacterExpToSkill(pchar, "Leadership", 300);
			ChangeCharacterNationReputation(pchar, ENGLAND, 5);
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
		break;
		
		case "BM_GabePlan_TommiMertv_Obmen":
			dialog.text = "흥미 없어. 그냥 레이피어만 돌려주면 우리 좋게 헤어지자, "+GetSexPhrase("나리","아가씨")+" "+pchar.lastname+".";
			link.l1 = "이 레이피어가 너한테 소중한 건 역사 있는 무기를 좋아해서지, 맞지? 나도 똑같은 걸 가지고 있는데, 이건 서랍에 넣어두기보단 들고 다니고 싶은 그런 무기잖아.";
			link.l1.go = "BM_GabePlan_TommiMertv_Obmen2";
		break;
		
		case "BM_GabePlan_TommiMertv_Obmen2":
			dialog.text = "그래? 뭐, 우리가 합의에 이를 수 있다고는 장담 못 하겠지만, 들어나 보지. 나도 역사 있는 무기에 관심이 있지. 하지만 이 레이피어는 대령님께서 주신 선물이야. 그래서 나한테는 아주 소중하지.";
			link.l1 = "너가 브로드소드(넓은 칼)를 좋아한다고 했지. 여기 있어. 우리 소중한 토미의 것이었어. 이 무기가 수년 동안 어떤 일들을 겪었을지 상상해 봐. 그리고 네 손에서 앞으로 또 어떤 일들을 겪게 될지.";
			link.l1.go = "BM_GabePlan_TommiMertv_Obmen3";
		break;
		
		case "BM_GabePlan_TommiMertv_Obmen3":
			dialog.text = "넌 정말 설득력이 있구나, 젊은이! 토마스의 검을 휘두르다니... 참 아이러니하군. 뭐, 좋아, 레이피어를 가져가라. 그렇다고 내가 쉽게 내주는 건 아니니 알아둬.";
			link.l1 = "합의에 이를 수 있어서 기쁩니다. 이제 작별이겠군요, Callow 선장?";
			link.l1.go = "BM_GabePlan_TommiMertv_Platok";
			RemoveCharacterEquip(pchar, BLADE_ITEM_TYPE);
			TakeItemFromCharacter(pchar, "blade_42");
			AddCharacterExpToSkill(pchar, "Leadership", 250);
			AddCharacterExpToSkill(pchar, "Commerce", 500);
		break;
		
		case "BM_GabePlan_TommiMertv_Poteryal":
			dialog.text = "뭐라고?! 어떻게... 어떻게 칼 한 자루를 통째로 잃어버릴 수가 있지?! 너 정말 멍청이구나!";
			link.l1 = "진정해! 그냥 레이피어일 뿐이야. 어차피 너 그거 쓸 일도 없잖아. 톰은 죽었어—지금 중요한 건 그거 하나 아니냐?";
			link.l1.go = "BM_GabePlan_TommiMertv_Poteryal2";
		break;
		
		case "BM_GabePlan_TommiMertv_Poteryal2":
			dialog.text = "레피어 한 자루뿐이라고?! 그건 내 보물이었어! 도일리 대령님이 직접 주신 선물이란 말이야! 한 번도 안 썼다 해도 상관없어!";
			link.l1 = "그럼 나한테 주지 말았어야지, 안 그래?";
			link.l1.go = "BM_GabePlan_TommiMertv_Poteryal3";
		break;
		
		case "BM_GabePlan_TommiMertv_Poteryal3":
			dialog.text = "이제 입 다무는 게 좋겠어, "+GetSexPhrase("나리","아가씨")+" "+pchar.lastname+". 우리 평화롭게 헤어질 수도 있었지. 하지만 이제... 이제는 네게 본때를 보여주고 싶군, "+GetSexPhrase("젊은이","아가씨")+".";
			link.l1 = "너 같은 선생들은 묘지에 가득하지.";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_GabePlan_BitvaCallowSoloConflict");
			pchar.questTemp.BM_GabeCallow_Rapira = true;
		break;
		
		case "BM_GabePlan_TommiMertv_Otkaz":
			dialog.text = "당연히 그렇지. 하지만 네가 도와줬다고 해서 장교의 개인 무기를 그냥 가져갈 순 없잖아?";
			link.l1 = "나도 동의하겠지만, 어차피 너 그거 안 쓰잖아. 네 방에 못에만 걸려 있을 거 아냐. 하지만 나한텐 제대로 쓸 데가 있지. 도일리 대령이 그거 네가 잃어버렸는지 확인하러 오진 않을 거 아냐, 안 그래?";
			link.l1.go = "BM_GabePlan_TommiMertv_Otkaz2";
		break;
		
		case "BM_GabePlan_TommiMertv_Otkaz2":
			dialog.text = "이건 논의할 문제가 아니야, 젊은이. 처음부터 말했지, 이건 선물이 아니라고. 레이피어 내놔. 지금.";
			link.l1 = ""+GetSexPhrase("나는 네 장난감 병정이 아니야","나는 네가 부리는 항구의 창녀가 아니야")+", 네 명령을 따르라고? 나도 너처럼 배의 선장이야. 이 레이피어는 내가 가진다, 네가 싫든 좋든.";
			link.l1.go = "BM_GabePlan_TommiMertv_Otkaz3";
		break;
		
		case "BM_GabePlan_TommiMertv_Otkaz3":
			dialog.text = "토마스가 너한테 꽤 영향을 준 모양이군. 그렇게 원한다면, 그걸 위해 죽어라.";
			link.l1 = "나도 딱 그렇게 생각했어!";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_GabePlan_BitvaCallowSoloConflict");
			pchar.questTemp.BM_GabeCallow_Rapira = true;
		break;
		
		case "BM_GabePlan_TommiMertv_Platok":
			dialog.text = "여기, 이거 가져가. 난 전혀 필요 없어. 오늘의 기념품으로 삼아. 이제부터는 좀 덜 쉽게 속도록 해. 그리고 토마스 같은 악당들이 너를 더러운 일에 끌어들이지 못하게 조심해.";
			link.l1 = "헤, 나한테 블랙 스팟을 주려는 거야, Callow 선장?";
			link.l1.go = "BM_GabePlan_TommiMertv_Platok2";
			GiveItem2Character(PChar, "talisman15");		//Предмет Чёрная Метка
		break;
		
		case "BM_GabePlan_TommiMertv_Platok2":
			dialog.text = "뭐, 우리 둘 다 해적은 아니잖아, 그렇지, "+pchar.name+"? 이것이 경각심이 되길 바라네. 몸조심하게, 군도에는 자네 같은 이가 필요하니. "+GetSexPhrase("아마 해군에 입대하는 걸 제안하고 도일리 대령에게 추천서를 써 주는 게 어떨까...","")+"";
			link.l1 = "유감이지만 당신의 제안을 받아들일 수 없소, 선장.";
			if (startHeroType == 3)
			{
				link.l1 = "흠. 곰곰이 생각해 보지. 제대로 말이야.";
			}
			if (startHeroType == 4)
			{
				link.l1 = "안녕히 가십시오, 나리.";
				link.l1.go = "exit";
				AddDialogExitQuest("BM_GabePlan_CallowDruzhba");
				break;
			}
			link.l1.go = "BM_GabePlan_TommiMertv_Platok3";
		break;
		
		case "BM_GabePlan_TommiMertv_Platok3":
			dialog.text = "알아서 해. 그럼, 잘 가. "+GetSexPhrase("나리","아가씨")+" "+pchar.lastname+". 너는 아이언사이드의 남은 것을 가질 자격이 있어. 잘 가라.";
			link.l1 = "안녕히 가십시오, 나리.";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_GabePlan_CallowDruzhba");
		break;
		
		case "BM_GabePlan_TommiMertv_Konflict":
			dialog.text = "네 말투가 마음에 안 들어, "+GetSexPhrase("나리","아가씨")+". 그래서 뭐가 하고 싶은 말이지?";
			link.l1 = "일부러 시간을 끌면서 '최정예 부하들'을 모았군. 뭐 하려고? 단 한 사람을 잡으려고? 그냥 시내를 순찰하는 병사 몇 명만 데려와서 당장 나를 도왔어야지!";
			link.l1.go = "BM_GabePlan_TommiMertv_Konflict2";
		break;
		
		case "BM_GabePlan_TommiMertv_Konflict2":
			dialog.text = "대포밥이나 데려온 거야?! 톰은 저놈들처럼 그냥 시 경비병이 아니었어. 완전히 다른 훈련과 경험을 쌓았지—그 녀석은 나처럼 피에 굶주린 아이언클래드야! 그걸 왜 못 알아차리는 거지?";
			link.l1 = "오, 그 반대야. 나는 잘 알고 있지. 그래서 너랑 내가 여기 있었던 거야. 톰이랑 칼을 맞대는 동안 애들이 그를 산 채로 잡을 수 있게 말이야. 게다가 너도 아이언클래드잖아. 같은 패거리 아니냐. 직접 싸우는 게 그렇게 두려웠냐?";
			link.l1.go = "BM_GabePlan_TommiMertv_Konflict3";
		break;
		
		case "BM_GabePlan_TommiMertv_Konflict3":
			dialog.text = "감히 나를 비겁하다고 몰아붙이다니, 젊은이 "+GetSexPhrase("남자","아가씨")+"! 아무한테나 물어봐, 내가 이 도시를 위해 이룬 업적들에 대해 자세히 말해줄 테니까.";
			link.l1 = "아직 끝난 거 아니야. 이제 와서 생각해보니, 네가 말한 그 ‘공적’들이 정말 네 손으로 이룬 건지 의심이 드는군. 넌 톰이랑 나를 서로 죽이게 만들어서 영광을 혼자 차지하려 했지. 예전에도 그랬잖아, 안 그래?";
			link.l1.go = "BM_GabePlan_TommiMertv_Konflict4";
		break;
		
		case "BM_GabePlan_TommiMertv_Konflict4":
			dialog.text = "네 비난은 이제 지긋지긋하다, "+GetSexPhrase("나리","아가씨")+" "+pchar.lastname+". 싸움을 원해? 지금 당장 해주지.";
			link.l1 = "진실은 아프지, 그렇지 않냐, 게이브?";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_GabePlan_BitvaCallowSoloConflict");
			pchar.questTemp.BM_GabeCallow_Conflict = true;
		break;
		
		case "BM_GabePlan_GazgovorTommiAndGabe_1":
			dialog.text = "";
			link.l1 = "게이브! 정말 오랜만이군, 그 긴긴 우울한 겨울들을 지나서! 그런데 널 봐라 - 여전히 그 잘난 척하는 표정이네, 젠장할 놈!";
			link.l1.go = "BM_GabePlan_GazgovorTommiAndGabe_2";
			CharacterTurnByChr(npchar, characterFromID("Irons"));
		break;
		
		case "BM_GabePlan_GazgovorTommiAndGabe_2":
			dialog.text = "토마스! 오늘 드디어 내 손으로 우리 사법 체계가 수년간 해내지 못한 일을 이루게 되어 기쁘군. 그리고 내가 기분이 좋으니, 무기를 내려놓고 우리와 함께 가는 것을 허락하지. 운이 좋으면 다시 노역지로 보내질 수도 있겠군. 그럴 경우 내가 직접 너를 호송하겠다.";
			link.l1 = "흥, 한번 해보시지! 네 옆에 몇 놈 서 있다고 내가 멈출 것 같아?!!!";
			link.l1.go = "BM_GabePlan_GazgovorTommiAndGabe_3";
		break;
		
		case "BM_GabePlan_GazgovorTommiAndGabe_3":
			dialog.text = "누가 나랑 있는 사람이 걔네뿐이라고 했지? 내가 말하는 건 지금 네 옆에 서 있는 사람이야.";
			link.l1 = "뭐?";
			link.l1.go = "BM_GabePlan_GazgovorTommiAndGabe_4";
		break;
		
		case "BM_GabePlan_GazgovorTommiAndGabe_4":
			dialog.text = "토마스, 토마스, 토마스... 넌 언제나처럼 이 세상에 혼자구나. 거의 불쌍할 지경이야!";
			link.l1 = "피투성이 쥐새끼들! 개자식들!";
			link.l1.go = "BM_GabePlan_GazgovorTommiAndGabe_5";
		break;
		
		case "BM_GabePlan_GazgovorTommiAndGabe_5":
			StartInstantDialog("Irons", "BM_GabePlan_GazgovorTommiAndGabe_6", "Quest\BlackMark.c");
		break;
		
		case "BM_GabePlan_GazgovorTommiAndGabe_6":
			dialog.text = "그게 무슨 뜻이야?! 그 말이 무슨 의미였지?!";
			link.l1 = "토미, 들어봐...";
			link.l1.go = "BM_GabePlan_GazgovorTommiAndGabe_7";
			CharacterTurnByChr(npchar, pchar);
		break;
		
		case "BM_GabePlan_GazgovorTommiAndGabe_7":
			dialog.text = "바로 그거 하고 있잖아! 그가 거짓말한다고 말해 봐!";
			link.l1 = "안타깝게도, 저 사람이 맞아. 무기를 내려놔. 오늘은 아무도 죽을 필요 없어. 내가 직접 네 편을 들어줄 테니 교수형은 면할 거야. 언젠가는 정직하게 살아갈 수도 있을 거다.";
			link.l1.go = "BM_GabePlan_GazgovorTommiAndGabe_8";
		break;
		
		case "BM_GabePlan_GazgovorTommiAndGabe_8":
			dialog.text = "그건 네가 결정할 일이 아니야! 그리고 너는 더더욱 아니지! 저런 지휘관이 있는데 적이 뭐가 필요하겠어! 또 한 마리의 빌어먹을 쥐새끼군.";
			link.l1 = "어서 가자, 토미. 너 같은 놈들에게는 깔끔한 도망이란 없어.";
			link.l1.go = "BM_GabePlan_GazgovorTommiAndGabe_9";
		break;
		
		case "BM_GabePlan_GazgovorTommiAndGabe_9":
			dialog.text = " 네 배, 네 선원들 사이에 자리 하나만 줬어도 시작이 됐을 거다, 네가 네 놈들 편 좀 들어줬다면 말이지! 하지만 이제 다 소용없어. 젠장할 놈들, 다 죽어라! 네 비겁한 내장을 다 쏟아놓고 말 거다, 이 쥐새끼야. 그리고 너도, 게이브, 널 끌고 같이 가볼 생각이다...\n";
			link.l1 = "잠깐만, 토미, 안 돼!";
			link.l1.go = "exit";
			AddDialogExitQuest("BM_GabePlan_GazgovorTommiAndGabe_Fight");
		break;
		
		case "BM_GabePlan_GabeWin_1":
			dialog.text = "축하하오, "+GetSexPhrase("젊은이","아가씨")+"! 네가 토마스에게 모든 일이 그의 계획대로 진행되는 것처럼 느끼게 만들었다니 감탄스럽군. 그 자는 배신을 귀신같이 알아차리는 놈이었지.";
			link.l1 = "아, 감사합니다, 물론이지요, Callow 선장.";
			link.l1.go = "BM_GabePlan_GabeWin_2";
		break;
		
		case "BM_GabePlan_GabeWin_2":
			dialog.text = "무슨 걱정이라도 있소, "+GetSexPhrase("나리","아가씨")+" "+pchar.lastname+"?";
			link.l1 = "톰... 그는 내가 네 편에 선 것만으로 화난 게 아니었어. 그의 목소리엔 진짜 절망과 이해할 수 없는 감정이 담겨 있었지, 마치...";
			link.l1.go = "BM_GabePlan_GabeWin_3";
		break;
		
		case "BM_GabePlan_GabeWin_3":
			dialog.text = "...마치 자기가 피해자인 것처럼 굴더군. 예상했던 일이야. 기억해, Charles, 괴물도 고통을 느낄 수 있어. 하지만 그렇다고 괴물이 아닌 건 아니지. 많은 범죄자들이 종종 자신이 옳고 결백하다고 진심으로 믿고 있거든.";
			link.l1 = "명심하도록 하지. 여기서 할 일은 다 끝난 것 같은데, 그렇지 않아, 선장?";
			link.l1.go = "BM_GabePlan_GabeWin_4";
		break;
		
		case "BM_GabePlan_GabeWin_4":
			dialog.text = "대체로 그렇지만, 이 멋진 하루를 완성하려면 아직 한 가지 더 해야 할 일이 남아 있소.";
			link.l1 = "오? 뭐지?";
			link.l1.go = "BM_GabePlan_TommiMertv_Mir2";
		break;
		
		case "BM_IronsJamaicaJungle2":
			dialog.text = "꽤 오래 걸렸군. 그래서 내가 좀 정찰을 해봤지. 아무튼, 해변에서 멋 부리며 결투하는 것보단 여기서 매복하는 게 낫다고 생각해. Gabe의 집을 찾아서 모든 걸 잘 보이게 두고 왔겠지?";
			link.l1 = "당연히 했지, 날 뭘로 보는 거야, 바보로 아나? 사실 난 네 선장이야, 토미. 네가 바보 밑에서 일한다면 넌 뭐가 되겠냐?";
			link.l1.go = "BM_IronsJamaicaJungle3";
		break;
		
		case "BM_IronsJamaicaJungle3":
			dialog.text = "하하하하, 내가 근무할 때 그런 말도 안 되는 일 얼마나 자주 겪었는지 믿지도 못할 거야! 하지만 우리 경우엔 다행히 그런 상황이 아니지. 좋아, 그럼. 손님이 올 거다. 준비됐어?";
			link.l1 = "글쎄, 포트 로열의 함대 전체나 주둔군이 여기 들이닥치지 않는 한, 난 준비됐어.";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_CreateGabeInJungle");
		break;
		
		case "BM_GabeJungle1":
			dialog.text = "토마스? 정말 너였구나...";
			link.l1 = "당연히 나지, 아니면 다른 사람이라도 기대했나, 게이브? 허, 귀신이라도 본 것처럼 창백하군. 그리고 예전 영국에 있을 때보다 더 뚱뚱해졌네.";
			link.l1.go = "BM_GabeJungle2";
			CharacterTurnByChr(npchar, characterFromID("Irons"));
		break;
		
		case "BM_GabeJungle2":
			dialog.text = "이제야 정말 네가 맞다는 게 확실해졌군. 여전히 버릇없기는. 뭐, 상관없어. 곧 네 더러운 입을 영영 다물게 해주지, 이 자식아.";
			link.l1 = "하하하, 이제야 말이 통하는군! 있잖아, 게이브, 넌 또 날 실망시켰어. 너 혼자 나 하나 감당하려면 사람을 더 데려왔어야 했지. 그런데 우리 둘이나 있다고! 아니면 그게 네가 받을 수 있는 전부였냐, 이 겁쟁이야?";
			link.l1.go = "BM_GabeJungle3";
		break;
		
		case "BM_GabeJungle3":
			dialog.text = "그만해! 더 이상 우리끼리 얘기할 필요 없겠군.";
			link.l1 = "그 점에 대해서는 나도 동의해! "+pchar.name+"! 전투다, 선장님!";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_GabeJungleFight");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "BM_IronsJamaicaJungle4":
			dialog.text = "헤, 됐다! 편히 잠들어라, 이 자식아.";
			link.l1 = "자, 이제 만족하냐, 토미? 복수하고 나면 더 나빠지는 사람이 많다는 거, 너도 알잖아.";
			link.l1.go = "BM_IronsJamaicaJungle5";
		break;
		
		case "BM_IronsJamaicaJungle5":
			dialog.text = "하, 어디서 그런 말 주워들었냐? 난 그런 약골들을 도통 이해 못 하겠더라. 쳇! 내가 만족하냐고? 너무 좋아서 오줌 지릴 지경이다! 저 자식들이 내 인생 최악의 불행의 근원이었거든!";
			link.l1 = "네가 잘 돼서 기쁘다. 아직 복수해야 할 사람이 더 남았나? 또 종이 탄약 농담을 들어야 하나?";
			link.l1.go = "BM_IronsJamaicaJungle6";
		break;
		
		case "BM_IronsJamaicaJungle6":
			dialog.text = "진정해, 게이브가 마지막이었어. 그리고 농담에 관해서라면 걱정 마, 적어도 너한테는 더 이상 없을 테니까.";
			link.l1 = "그럼 배로 돌아갈까?";
			link.l1.go = "BM_IronsJamaicaJungle7";
		break;
		
		case "BM_IronsJamaicaJungle7":
			dialog.text = "어차피 복수할 놈이 남았든 아니든, 우리는 다시 그 배에 타게 될 거야. 그런데 잠깐만...";
			link.l1 = "아, 그러니까 아직 끝난 게 아니군...";
			link.l1.go = "BM_IronsJamaicaJungle8";
		break;
		
		case "BM_IronsJamaicaJungle8":
			dialog.text = "그래, 그래. 너한테 하고 싶은 말이 있어. 이건 정말 극소수한 사람한테만 하는 말이야. 다시는 말 안 할 거야. 나를 비웃으면 정말 화낼 거니까.";
			link.l1 = "웃지 않겠다고 약속하지. 어쨌든, 네 농담은 웃기다기보다 더 긴장되더라고.";
			link.l1.go = "BM_IronsJamaicaJungle9";
		break;
		
		case "BM_IronsJamaicaJungle9":
			dialog.text = "좋아. 그래서 말인데, 네가 잭처럼 행동하지 않고 나를 도와주기로 한 데 정말 고맙게 생각해. 너야말로 진정한 친구야, 선장. 고마워. 그리고... 원한다면 내 믿음직한 검이랑 갑옷도 빌려줄게... 남아 있는 것만큼이지만, 하하!";
			link.l1 = "그래, 그렇게 말해줘서 고맙다. 부하한테 그런 말 듣는 날이 흔하지 않지. 가자, 친구.";
			link.l1.go = "Exit";
			AddDialogExitQuest("BM_FinalInJungleWithTommy");
		break;
		
		//--> ----------------------------------- офицерский блок ------------------------------------------
		case "Irons_officer":
			dialog.text = "예, 선장님?";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_FarewellOfficers") && !CheckAttribute(npchar, "quest.SharlieEpilog_FarewellOfficers"))
			{
				Link.l1 = "토미, 이제 우리 길은 여기서 갈라지는 것 같아.";
				Link.l1.go = "SharlieEpilog_Irons_1";
				break;
			}
			if (startHeroType == 4 && CheckAttribute(pchar, "questTemp.BlackMarkQuestCompleted"))
			{
				dialog.text = "그래, 룸바, 오늘 밤엔 누구의 뼈 위에서 춤을 출까?";
			}
			if (startHeroType == 4 && !CheckAttribute(pchar, "questTemp.BlackMarkQuestCompleted"))
			{
				dialog.text = "그래, Ellie?";
			}
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				dialog.text = "듣고 있소, 선장.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				dialog.text = ""+pchar.name+"?";
			}
			//////
			if (CheckAttribute(pchar, "questTemp.Dolly_Tieyasal") && !CheckAttribute(npchar, "quest.Tieyasal") && !CheckAttribute(pchar, "questTemp.BM_TommiTieyasalOtkaz"))
			{
				Link.l4 = "토미, 너한테 정말 진지하게 물어보고 싶은 게 있어. 하나 있는데... 레드스킨들의 돌 우상 말이야. 그리고 도움이 필요해. 이런 일은 너처럼 가장 가까운 친구들에게만 부탁할 수 있어. 새로 온 사람들이나 아직 잘 못 믿는 녀석들한테는 안 돼.";
				Link.l4.go = "tieyasal_1";
			}
			
			////////////////////////казначей///////////////////////////////////////////////////////////
           	// boal отчёт о корабле
			if(CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
			{
			    Link.l11 = "토미, 갈매기 세는 거 그만해. 화물 전부 다 확인했어? 전체 보고서랑 예측까지 내놔.";
			    Link.l11.go = "QMASTER_1";
				
			    // Warship. Автозакупка товара
				Link.l12 = "Tommy, 오늘부터 항구에서 특정 물품들을 사 와야겠어.";
				Link.l12.go = "QMASTER_2";
				
				if (startHeroType == 4)
				{
					Link.l11 = "토미, 배에 관한 모든 걸 보고해 줄 수 있겠나?";
					Link.l12 = "Tommy, 나 좀 피곤해지고 있어. 각 항구에서 필요한 물품 좀 채워줄 수 있겠나?";
				}
				if (pchar.sex == "man" && pchar.rank >= 15)
				{
					Link.l11 = "배 상태와 선상 모든 것에 대한 보고서를 준비해, 토미.";
					Link.l12 = "우리 항구에 들를 때 특정 물자를 비축해 줄 수 있겠나?";
				}
				if (pchar.sex == "man" && pchar.rank >= 25)
				{
					Link.l11 = "내가 배에 가지고 있는 모든 것을 전부 세어 보고, 전체 상태를 보고하라.";
					Link.l12 = "각 항구에 들를 때마다 이 물품들을 사 와 줘야 해.";
				}
			}
			//////
			Link.l1 = "내 명령을 잘 들어!";
			if (startHeroType == 4 && CheckAttribute(pchar, "questTemp.BlackMarkQuestCompleted"))
			{
				Link.l1 = "누군가는 분명히 그렇지. 하지만 지금은 내 명령을 들어.";
			}
			if (startHeroType == 4 && !CheckAttribute(pchar, "questTemp.BlackMarkQuestCompleted"))
			{
				Link.l1 = "내 명령을 들어라... 토미. ";
			}
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				Link.l1 = "그거 잘됐군, 토미. 내가 너한테 새 명령을 내릴 게.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				Link.l1 = "내 명령을 들어, Tom.";
			}
			Link.l1.go = "stay_follow";
			//////
			link.l2 = "아무것도 아니야, 토미. 편히 있어.";
			if (startHeroType == 4 && CheckAttribute(pchar, "questTemp.BlackMarkQuestCompleted"))
			{
				link.l2 = "어떻게 되는지 두고 보자, 토미.";
			}
			if (startHeroType == 4 && !CheckAttribute(pchar, "questTemp.BlackMarkQuestCompleted"))
			{
				link.l2 = "아니, 톰, 아무것도 아니야.";
			}
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				Link.l2 = "아니, 아무것도 없어.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				Link.l2 = "아니, 아무 문제 없어.";
			}
			link.l2.go = "exit";
			NextDiag.TempNode = "Irons_officer";
		break;
		
		/////////////////////////// ответы для казначея ///////////////////////////////////
		case "QMASTER_1":
			dialog.Text = "아직 재고조사도 시작 안 했어. 내가 이익과 손해나 계산해 주는 것만으로도 감사해야지, 저 탐욕스러운 상인들이랑 흥정까지 하라고? 재고는 내 일이 아니야. 군대에 있을 때도 안 했고, 지금도 할 생각 없어.";
			Link.l1 = "여긴 군대가 아니야, 토미. 하지만 알겠어, 강요하지 않을게.";
			if (startHeroType == 4)
			{
				dialog.Text = "나는 필경사가 아니야, 엘리. 예전에 다니엘 크림슨이라는 녀석을 알았는데, 자기는 늘 필경사라고 주장했지만 전장을 제대로 본 적도 없었지. 그런데도 싸움에서는 짐승 같았어. 하지만 나는 그런 사람이 아니고, 거짓말할 생각도 없어. 물품 정리는 내 적성이 아니야. 네 때문에 이미 장부 정리도 하고 있잖아. 더 이상 강요하지 마.";
				Link.l1 = "알겠어, Tommy, 안 할게.";
			}
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				dialog.text = "봐, 나는 서기가 아니야. 우리 같은 평민 병사들에게 이런 걸 요구한 적은 한 번도 없었어, 군대에서도 마찬가지였지. 그 규칙은 바꾸지 말자.";
				Link.l1 = "좋아, 그러지 말자.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				dialog.text = "내가 셀 수 있는 건 우리 적을 몇 놈이나 쏴 죽였는지뿐이야, 하하하. 그것도 가끔은 헷갈려. 나는 그냥 평범한 병사거든. 배에 대해선 누가 알겠어 – 난 평생 땅에서만 굴러다녔으니까.";
				Link.l1 = "내가 직접 해야겠군.";
			}
			Link.l1.go = "exit";
		break;

		case "QMASTER_2":
			dialog.text = "날 뭘로 보는 거야, 뒷골목 짐꾼쯤으로 아나? 우리 고향에서 그런 물렁한 겁쟁이들은 경멸밖에 안 했지. 내가 귀족은 아닐지 몰라도, 자존심은 남아 있어.";
			link.l1 = "알았어, 알았어, 안 한다면 안 하는 거지.";
			link.l1.go = "exit";
			if (startHeroType == 4)
			{
				dialog.Text = "이봐, 나는 그냥 평범하고 정직한 군인이었지, 보급 장교가 아니야, 아가씨. 그런 건 잘 모르고, 배우고 싶지도 않아. 그건 마치 네더러 머스킷을 시간 안에 조립하고 분해하라고 시키는 거랑 똑같아.";
				Link.l1 = "음, 이 배의 고정 장치와 움직이는 장치 하나하나까지 다 외우고 있지. 하지만 네가 원한다면, 톰. 이 일은 여기서 끝내자.";
			}
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				dialog.text = "아니, 못 했어. 아마 네가 잊었거나 아예 모를 수도 있으니 설명해 줄게. 너한텐 이런 일이 평범한 일일지 모르지만, 우리 군대에선 보급이나 후방 지원을 그리 잘 대우하지 않아. 나를 그들과 같은 취급은 하지 말아줘.";
				Link.l1 = "하하, 좋아, 좋아.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				dialog.text = "이봐, 물론 나는 너를 존중하지만, 내 자신을 배신하면서까지 내가 못 하거나 못 견디는 일을 하진 않을 거야. 그때 겨우 숫자 세는 법을 배웠는데, 이제 와서 제대로 된 공급업자가 되라고? 그리고 말인데, 우리도 걔네들 별로 안 좋아했어 – 탄약, 물, 식량도 아끼고, 신선도도 엉망이거든.";
				Link.l1 = "흠, 좋아, 그 일은 잊자.";
			}
		break;
		
		case "stay_follow":
            dialog.Text = ""+GetSexPhrase("오, 명령이야? 너는 훈련이랑 군대식 그런 거 좋아하지? 난 그냥 뭐 해야 하는지만 말해줬으면 좋겠어.","너는 무슨 하사관 같은데, 그건 너한테 안 어울려. 너무 예뻐서 군대에선 하루도 못 버텼을 거야. 하지만 듣고 있어.")+"";
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				dialog.text = "보아하니, 너 정말 제복이랑 훈련 같은 거 엄청 좋아하는구나. 뭐, 알겠다. 계속 해봐.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				dialog.text = "어느 쪽?";
			}
			
            Link.l1 = ""+GetSexPhrase("아무 데도 가지 말고 아무 짓도 하지 마라 - 그냥 지켜봐, 알겠어? 나는 너를 잘 아니까.","거기 그대로 있어, 알겠어?")+"";
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				Link.l1 = "여기 가만히 있어, 아무 데도 가지 말고, 아무것도 건드리지 마.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				Link.l1 = "여기서 기다리고 아무도 지나가지 못하게 해.";
			}
			Link.l1.go = "Boal_Stay";
            Link.l2 = ""+GetSexPhrase("나를 따라오고, 아무것에도 정신 팔리지 마라 – 길 잃은 아내나 갑자기 나타나는 옛 전우까지도 말이야.","가까이 있어 줘, 알겠지? 내 뒤를 좀 지켜줬으면 해.")+"";
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				Link.l2 = "나를 따라와. 생각에 잠겨 있는 게 보이네.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				Link.l2 = "날 따라와, 뭔가 이유가 있어서 멈춘 게 아니라면.";
			}
			Link.l2.go = "Boal_Follow";
			
			if(CheckAttribute(NPChar, "equip.gun"))
			{
				if(CheckAttribute(NPChar, "chr_ai.gun.bulletNum") && sti(NPChar.chr_ai.gun.bulletNum) > 1)
				{
					Link.l3 = "이번에는 다른 걸 쏴 줘야겠어.";
					Link.l3.go = "SetGunBullets";
					if (pchar.sex == "man" && pchar.rank >= 15)
					{
						Link.l3 = "다가올 전투에서는 다른 탄약을 써 줬으면 해.";
					}
					if (pchar.sex == "man" && pchar.rank >= 25)
					{
						Link.l3 = "다음 전투에서는 다른 탄약을 쓰게 될 거야.";
					}
				}	
			}
			if(CheckAttribute(NPChar, "equip.musket"))
			{
				if(CheckAttribute(NPChar, "chr_ai.musket.bulletNum") && sti(NPChar.chr_ai.musket.bulletNum) > 1)
				{
					Link.l4 = "당신의 머스킷 탄환 종류를 변경하십시오.";
					Link.l4.go = "SetMusketBullets";
				}
				Link.l5 = "전투에 사용할 주무기를 바꿔라.";
				Link.l5.go = "SetPriorityMode";
				Link.l6 = "적들과는 일정 거리를 유지해 주었으면 해.";
				Link.l6.go = "TargetDistance";
				if (pchar.sex == "man" && pchar.rank >= 15)
				{
					Link.l6 = "적과는 어느 정도 거리를 두었으면 하네, 토미.";
				}
				if (pchar.sex == "man" && pchar.rank >= 25)
				{
					Link.l6 = "적과는 일정 거리를 유지해, 토미.";
				}
			}
		break;
		
		case "SetGunBullets":
			Dialog.Text = ""+GetSexPhrase("어떤 탄환들 말이오? 하나하나 정성껏 만들었길 바라오, 어디로 떨어질지 누가 알겠소, 헤헤.","너를 위해 뭐든 쏴줄게. 뭐든지, 하지만 공포탄은 절대 안 쏴, 헤헤. ")+"";
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				dialog.text = "뭔가 재미있는 일이 벌어지고 있는 것 같은데! 좋아, 어떤 종류지?";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				dialog.text = "또 싸우자고...? 좋아, 어떤 싸움인데?";
			}
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(NPChar.chr_ai.gun.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetItemName(rItem);
				Link.(attrL).go = "SetGunBullets1_" + i;
			}
		break;	

		case "SetGunBullets2":
			i = sti(NPChar.SetGunBullets) + 1; 
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(NPChar, GUN_ITEM_TYPE, sBullet);
			LAi_GunSetUnload(NPChar, GUN_ITEM_TYPE);
			NextDiag.CurrentNode = NextDiag.TempNode;
			rItem = ItemsFromID(sBullet);
			notification(GetFullName(NPChar)+" "+XI_ConvertString("AmmoSelectNotif")+GetItemName(rItem)+"", "AmmoSelect");
			DeleteAttribute(NPChar,"SetGunBullets");
			DialogExit();
		break;

		case "SetMusketBullets":
			Dialog.Text = "탄약 종류를 선택하십시오:";
			sGun = GetCharacterEquipByGroup(NPChar, MUSKET_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(NPChar.chr_ai.musket.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetItemName(rItem);
				Link.(attrL).go = "SetGunBullets1_" + i;
			}
		break;	

		case "SetMusketBullets2":
			i = sti(NPChar.SetMusketBullets) + 1; 
			sGun = GetCharacterEquipByGroup(NPChar, MUSKET_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(NPChar, MUSKET_ITEM_TYPE, sBullet);
			LAi_GunSetUnload(NPChar, MUSKET_ITEM_TYPE);
			NextDiag.CurrentNode = NextDiag.TempNode;
			rItem = ItemsFromID(sBullet);
			notification(GetFullName(NPChar)+" "+XI_ConvertString("AmmoSelectNotif")+GetItemName(rItem)+"", "AmmoSelect");
			DeleteAttribute(NPChar,"SetMusketBullets");
			DialogExit();
		break;
		
		case "SetPriorityMode":
			Dialog.Text = "전투가 시작될 때 사용할 무기:";
			Link.l1 = "Blade";
			Link.l1.go = "BladePriorityMode";
			Link.l2 = "Musket";
			Link.l2.go = "MusketPriorityMode";
		break;
		
		case "BladePriorityMode":
			SetPriorityMode(NPChar, 1);
			DialogExit();
		break;
		
		case "MusketPriorityMode":
			SetPriorityMode(NPChar, 2);
			DialogExit();
		break;
		
        case "Boal_Stay":
            Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
            AddDialogExitQuestFunction("LandEnc_OfficerStay");
            dialog.Text = ""+GetSexPhrase("거기서 두들겨 맞아도 말이지, 헤헤? 알았어, 그냥 구경만 할게.","나를 경비로 만들 생각이야? 네가 맞거나 다치면 어쩌라고?")+"";
            Link.l1 = ""+GetSexPhrase("이봐, 조심해! 그렇게 되면 우리가 뭔가 방법을 찾아볼 테니까.","가만히 서서 구경만 할 건 아니겠지? 네가 네 선장이 그렇게 대단하다고 생각한다면 뭔가 해봐야지.")+"";
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				dialog.text = "머리까지 노린다고? 알았어, 알았다고, 그렇게 쳐다보지 마.";
				Link.l1 = "그러길 바란다.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				dialog.text = "겁내지 마, 아무도 못 지나갈 거야.";
				Link.l1 = "누구도 그립지 않다면 말이지. 하지만 좋아.";
			}
            Link.l1.go = "Exit";
            Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
        break;
        
        case "Boal_Follow":
            SetCharacterTask_FollowCharacter(Npchar, PChar);
            dialog.Text = ""+GetSexPhrase("아주 웃기네. 하지만 무슨 말인지는 알겠어.","오, 걱정 마. 난 항상 네 편이야, 헤헤.")+"";
            Link.l1 = ""+GetSexPhrase("좋아.","정말 못 참겠군, Tom.")+"";
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				dialog.text = "음, 지금 아주 중요한 뭔가를 떠올리려고 하고 있었어. 그런데 곧 내가 그게 뭔지도 모른다는 걸 깨달았지, 그때 기억을 잃었으니까. 결국 아무 소용도 없겠네. 좋아, 가자.";
				Link.l1 = "재치 있군, 그래.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				dialog.text = "글쎄, 내가 여기 서 있는 건 아까 네가 직접 시켜서야. 간다, 간다.";
				Link.l1 = "흠, 알겠어, 알겠다고.";
			}
            Link.l1.go = "Exit";
        break;
		
		//--> задать дистанцию стрельбы
		case "TargetDistance":
			dialog.text = ""+GetSexPhrase("무슨 거리 말인가? 스무 야드만 넘어가면 제대로 조준할 수 없다는 걸 명심해. 물론, 내가 뭘 맞출 필요가 없다면 상관없겠지만, 헤헤.","너 같은 놈 옆에 있다가 또 냄새나는 놈들한테 가까이 가고 싶겠냐. 그래서, 거리가 얼마나 되지? 하지만 명심해, 내 화기를 이십 야드 이상 멀리 조준할 수는 없어. 아무도 못 해.")+"";
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				dialog.text = "좋아, 어느 정도 거리 말이지? 하지만 전투 중에 이십 미터가 넘으면 정확하게 천천히 사격하는 건 불가능하다는 걸 미리 말해두겠어.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				dialog.text = "그래. 뭐라고? 저 너머에 대해 기억해... 음, 이제 우리 둘 다 더 이상 어린애가 아니라는 거, 너도 나도 알잖아.";
			}
			link.l1 = "";
			Link.l1.edit = 3;
			link.l1.go = "TargetDistance_1";
		break;
		
		case "TargetDistance_1":
			iTemp = sti(dialogEditStrings[3]);
			if (iTemp < 0)
			{
				dialog.text = ""+GetSexPhrase("농담은 하지 않는 게 좋겠어.","유머에 대해서는 아직 나한테 배울 게 많아, 아가씨. 그래도 점점 나아지고 있군!")+"";
				link.l1 = ""+GetSexPhrase("이상하군; 나는 항상 그 반대라고 들었는데.","아주 웃기네, 토미.")+"";
				if (pchar.sex == "man" && pchar.rank >= 15)
				{
					dialog.text = "네 농담치고는 그나마 낫군. 언젠가는 그렇게 심술궂게 굴지도 않게 될지도 모르지, 헤헤.";
					Link.l1 = "뭐, 어쩔 수 없지.";
				}
				if (pchar.sex == "man" && pchar.rank >= 25)
				{
					dialog.text = "하하하, 웃기는 농담이군.";
					Link.l1 = "사실, 나는 그냥... 알겠어.";
				}
				link.l1.go = "exit";
				break;
			}
			if (iTemp == 0)
			{
				dialog.text = "좋아, 그럼 난 그냥 가만히 서서 버틸게. 너무 멀리서 싸우면 네 목숨이 위험해, 헤헤.";
				link.l1 = "빈정거리지 마. 이제부터는 네가 버티는 게 내가 딱 원하는 거야.";
				if (pchar.sex == "man" && pchar.rank >= 15)
				{
					dialog.text = "헤, 그냥 진형을 유지하라고 말하면 될 걸, 거리니 숫자니 하는 소리는 왜 한 거야?";
					Link.l1 = "그래, 중요한 건 네가 내 말을 이해했다는 거지.";
				}
				if (pchar.sex == "man" && pchar.rank >= 25)
				{
					dialog.text = "알겠어, 여기서 버틸게. 그럼 놈들을 더 가까이 데려와, 내가 쏠 수 있게.";
					Link.l1 = "물론이지.";
				}
				link.l1.go = "exit";
				npchar.MusketerDistance = 0;
				break;
			}
			if (iTemp > 20)
			{
				dialog.text = "봐, 내가 등대에서 쏜 것처럼 매번 그렇게 쏘길 바라는 건 알지만, 그건 불가능해. 거긴 위치가 좋았지. 침착하고 안정적이었어. 전투의 한가운데서는 그런 걸 똑같이 할 수 없어.";
				link.l1 = "흠. 그럼 이십 야드 떨어져 있어.";
				if (pchar.sex == "man" && pchar.rank >= 15)
				{
					dialog.text = "너도 그걸 원하겠지, 다른 녀석들도 다 원할 거야. 하지만 등대에서 그랬던 것처럼, 이제는 더 이상 통하지 않아. 좋은 장소가 필요하고, 아무도 나한테 접근하지 않아야 해. 그렇지 않으면 내 신경이 다 무너질 거야.";
					Link.l1 = "흠, 알겠어.";
				}
				if (pchar.sex == "man" && pchar.rank >= 25)
				{
					dialog.text = "그때 이후로 분명히 실력이 늘긴 했지만, 불가능한 건 여전히 불가능하지. 전투의 열기 속에서 등대에서 쐈던 그 한 방을 다시는 재현할 수 없어. 휠록 소총을 쓴다 해도 말이야.";
					Link.l1 = "불가능도 가능하지, 토미. 하지만 알겠어, 안 된다는 건 안 된다는 거지.";
				}
				link.l1.go = "exit";
				npchar.MusketerDistance = 20.0;
				break;
			}
			dialog.text = RandPhraseSimple("아주 좋아. 그 거리를 딱 맞춰 줄게. 하지만 선술집이나 동굴 안에서 싸우게 되면, 거리를 유지하려고 밖으로 나갈 거야, 헤헤.","해보지. 하지만 갑판이랑 비좁은 공간에서는 상황이 마음대로 안 될 수도 있지.");
			link.l1 = ""+GetSexPhrase("재미없어, 토미. 똑바로 행동해, 그리고 농담이나 멍청한 장난 따윈 하지 마.","그건 알아, Thomas. 내가 바보는 아니거든.")+"";
			if (pchar.sex == "man" && pchar.rank >= 15)
			{
				dialog.text = "기억하려고 해.";
				Link.l1 = "좋아, 믿고 맡길게.";
			}
			if (pchar.sex == "man" && pchar.rank >= 25)
			{
				dialog.text = "예, 선장님.";
				Link.l1 = "편히 있어, Tommy.";
			}
			link.l1.go = "exit";
			npchar.MusketerDistance = iTemp;
		break;
		//<-- задать дистанцию стрельбы
	//<-- ----------------------------------- офицерский блок ----------------------------------------
	
	// на Тайясаль
		case "tieyasal_1":
			dialog.text = "뭘 도와달라는 거지, 훔치라고? 그런데 왜? 물론 칭찬은 고맙지만, 진작에 다 말할 수도 있었잖아. 자, 어서 털어놔.";
			link.l1 = "입 조심해, 알았어? 뭐, 젠장 – 네가 어떻게 말하든 내 편만 되어주면 상관없어. 그래서, 그 우상 말인데. 그걸 통해서... 마법처럼 다른 곳으로 이동할 수 있어. 그렇게 쳐다보지 마 – 나도 이게 어떻게 들리는지 알아. 하지만 나 이미 한 번 겪었고, 내 두 눈으로 다 봤어. 그건... 영약 하나만 마시면 안전해.\n";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			dialog.text = "이미 한두 잔 마신 것 같군. 아니, 아니군, 멀쩡해 보여. 그런데도 사람들은 내가 항상 헛소리만 한다고 하더라...";
			link.l1 = "나랑 같이 갈 거야, 말 거야? 그 우상은 우리를 고대 마야 도시로 이끌 거라고 했지, 거기서 무슨 일이 기다릴지 누가 알겠어? 어려운 순간에 내가 믿고 의지할 수 있는 몇 안 되는 사람 중 하나가 바로 너야. 그리고 지금이 바로 그런 순간이야.";
			link.l1.go = "tieyasal_3";
		break;
		
		case "tieyasal_3":
			dialog.text = "이 모든 게 영 찜찜해. 네가 내 선장이 아니었으면 정신병원에나 있어야 할 인간이라고 했을 거야. 다음엔 신이 존재한다고 말하겠지.";
			link.l1 = "그래, 토미. 그리고 내가 이 군도에서 놀랍게도 알게 된 건, 우리만 그런 게 아니라는 거야. 여기서 온갖 악행이 벌어지는 걸 너도 직접 볼 수 있었지. 그리고 축복받았든 저주받았든, 온갖 장신구들의 영향도 아마 눈치챘을 거야.";
			link.l1.go = "tieyasal_4";
		break;
		
		case "tieyasal_4":
			dialog.text = "집에서도 악마 같은 일은 있지. 그리고 항상 평범한 설명이 있었어. 미안하지만, 선장, 나는 너랑 돌 우상 주위를 돌며 춤추진 않을 거야. 적을 쏘는 건 언제든 환영이지. 내가 기억은 잃었을지 몰라도, 정신까지 잃진 않았어. 적어도, 내 생각엔 그래.";
			link.l1 = "음, 강제로 시킬 순 없지. 그러니... 네가 원하는 대로 해, 토미.";
			link.l1.go = "tieyasal_5";
			link.l2 = "우상 근처에 가는 것도 무서워하는 주제에, 네가 저놈들을 쏠 배짱이 있을 것 같진 않군, 이 용감한 녀석아.";
			link.l2.go = "tieyasal_6";
		break;
		
		case "tieyasal_5":
			dialog.text = "오, 그래, 그래, 그렇게 입 내밀지 마. 좋아, 그 우상 주위를 한바탕 춤추고 돌아오면, 다음엔 생각해 보지.";
			link.l1 = "다음 기회는 없을지도 몰라. 배로 돌아가, Tom.";
			link.l1.go = "exit";
			pchar.questTemp.BM_TommiTieyasalOtkaz = true;
		break;
		
		case "tieyasal_6":
			dialog.text = "난 두렵지 않아, 오해하지 마. 하지만 난 내 직감을 믿는 데 익숙해, 그동안 한 번도 틀린 적이 없었지. 그런데 지금은 이 일에서 좋은 일이 생기지 않을 거라고 내 직감이 말하고 있어. 그리고... 뭐, 어차피 말해봤자 너 기분만 상할 거야.";
			link.l1 = "어서 말해 봐.";
			link.l1.go = "tieyasal_7";
		break;
		
		case "tieyasal_7":
			dialog.text = "그래, 그렇다면야! 나는 너와 함께 싸우기로 했지. 하지만 만약, 상상해보자, 이게 정말 효과가 있다면 어쩌지? 만약 저주받은 거라면? 난 누구를 위해서도 죽을 생각 없어, 미안하지만.";
			link.l1 = "이제 네가 어떤 놈인지 알겠구나, 토미. 나는 가장 충직한 자들이 필요했지. 그런데 이제 보니 너는 그중 하나가 아니로군. 나는 그리로 간다. 그리고 너는... 하고 싶은 대로 해라.";
			link.l1.go = "tieyasal_8";
		break;
		
		case "tieyasal_8":
			dialog.text = "저 녀석 좀 봐. 결국 기분이 상했잖아.";
			link.l1 = "입 닥쳐. 우리가 그렇게 역겹다면, 굳이 배로 돌아올 필요 없어.";
			link.l1.go = "tieyasal_9";
		break;
		
		case "tieyasal_9":
			dialog.text = "이런 젠장! 진심이야? 뭐, 어쩌면 그게 나을지도 모르지. 농담도 못 알아듣는 재미없는 놈들이랑은 같이 있고 싶지 않아. 그렇다면... 작별이오, 각하.";
			link.l1 = "잘 가라, 토미. 그리고 지옥이나 가라.";
			link.l1.go = "tieyasal_10";
		break;
		
		case "tieyasal_10":
			DialogExit();
			AddDialogExitQuestFunction("BM_Irons_tieyasal_otkaz");
		break;
		
		// Эпилог
		case "SharlieEpilog_Irons_1":
			dialog.text = "하. 이제 농담도 할 줄 아는구나. 거의 나처럼 말이지. 하지만 그런 미끼엔 안 속아, 기대하지 마.";
			link.l1 = "아니야, 이건 농담이 아니야. 난 유럽으로 가, 아버지를 만나러. 넌 여기 남아서 기다릴 수도 있겠지만... 얼마나 걸릴지 몰라.";
			link.l1.go = "SharlieEpilog_Irons_2";
		break;
		
		case "SharlieEpilog_Irons_2":
			dialog.text = "그래, 그런 얼굴로 농담할 정도로 넌 재미없어. 결국 날 내치는 거냐? 내가 네 목숨을 구했는데도? 내가 널 위해 해온 모든 걸 무시하는 거냐?";
			link.l1 = "오버하지 마, 토미. 넌 너의 일을 했고, 그 대가로 월급을 받았잖아. 인정하지, 넌 유능해. 기다리겠다면 나야 반갑게 다시 맞이하지. 하지만 지금은...";
			link.l1.go = "SharlieEpilog_Irons_3";
		break;
		
		case "SharlieEpilog_Irons_3":
			dialog.text = "관대하시네, 젠장. 고맙군요, 배신자 선장님. 이렇게 기록해두지 – '충견은 주인을 기다릴 수 있다. 지루해 죽지 않는다면 말이지'.";
			link.l1 = "개인적으로 받아들이지 마. 어쩔 수 없는 상황이었어.";
			link.l1.go = "SharlieEpilog_Irons_nothing";
			link.l2 = "화나는 거 이해해. 나라면 나도 기분 안 좋았을 거야. 네가 받아야 할 것 외에 한 달치 월급을 더 줄게. 나한테 원한은 갖지 않길 바란다.";
			link.l2.go = "SharlieEpilog_Irons_salary";
			link.l3 = "갑작스러운 소식이었고, 네가 화낼 만한 이유도 있어. 그래서 난 네가 받을 금액 외에 세 달치 월급을 더 줄 생각이야.";
			link.l3.go = "SharlieEpilog_Irons_salary_X3";
		break;
		
		case "SharlieEpilog_Irons_nothing":
			dialog.text = "상황 같은 건 집어치워. 그리고 너도. 너랑 엮인 걸 후회한다. 그리고 알겠어? 날 내쫓는 건 네가 아니라, 내가 스스로 떠나는 거야.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Irons_exit";
		break;
		
		case "SharlieEpilog_Irons_salary":
			dialog.text = "그 푼돈은 거지들한테나 줘. 너의 자선 따윈 필요 없어.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Irons_exit";
			//
			AddMoneyToCharacter(pchar, - sti(npchar.quest.OfficerPrice));
		break;
		
		case "SharlieEpilog_Irons_salary_X3":
			dialog.text = "세 달치 월급이라고? 이거 참 후하군... 감동이네. 자, 그 시혜금 줘. 선장 샤를 드 모르를 기리며 선술집에서 녀석들에게 술이나 돌리지 – 충성의 상징, 우정의 아이콘, 본받을 인물 말이야.";
			link.l1 = "...";
			link.l1.go = "SharlieEpilog_Irons_exit";
			//
			AddMoneyToCharacter(pchar, -sti(npchar.quest.OfficerPrice) * 3);
		break;
		
		case "SharlieEpilog_Irons_exit":
			DialogExit();
			AddDialogExitQuestFunction("SharlieEpilog_Irons_exit");
		break;
	}
} 