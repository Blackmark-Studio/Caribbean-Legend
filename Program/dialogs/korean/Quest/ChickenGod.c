int questShips[50];
int questShipsNum = 0;

extern void InitGunExt(string id,			
				string sAttr,       
				string sBullet,     
				string sGunPowder,  
				float  DmgMin,   
				float  DmgMax, 
				float  EnergyP,
				bool   MultiDamage, 
				int    MisFire,     
				int    ChargeSpeed, 
				bool   isDefault );

void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	string sTemp, attr, companion;
	ref chref;
	int iTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	string node = Dialog.CurrentNode;
	if(HasSubStr(node, "joruba_p3_ship_")) {
		iTemp = findsubstr(node, "joruba_p3_ship_", 0);
	 	companion = strcut(node, iTemp + strlen("joruba_p3_ship_"), strlen(node) - 1);
 	    Dialog.CurrentNode = "joruba_p3";
	}
	
	if(HasSubStr(node, "joruba_p4_off_")) {
		iTemp = findsubstr(node, "joruba_p4_off_", 0);
	 	pchar.questTemp.ChickenGod.Sacrifice = strcut(node, iTemp + strlen("joruba_p4_off_"), strlen(node) - 1);
 	    Dialog.CurrentNode = "joruba_p4_off";
	}

	if(HasSubStr(node, "joruba_o6_off_")) {
		iTemp = findsubstr(node, "joruba_o6_off_", 0);
	 	pchar.questTemp.ChickenGod.Sacrifice = strcut(node, iTemp + strlen("joruba_o6_off_"), strlen(node) - 1);
 	    Dialog.CurrentNode = "joruba_o6_off";
	}

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
        case "First time":
			dialog.text = "이건 네가 보면 안 되는 거야.";
			link.l1 = "버그 리포트를 제출할 시간이군.";
			link.l1.go = "exit";
		break;
		
        case "native":
			dialog.text = "이런! 타카히, 젊은이. 무례하게 굴려는 건 아니지만, 어떻게 여기 들어왔지? 내가 머무는 동안은 마담에게 영업을 중단하라고 강력히 권했거든.";
			link.l1 = "정말 큰일이군. 어떻게 널 들여보낸 거지? 왜 이 창관이 아직도 분노한 신실한 사람들에게 불타지 않은 거야?";
			link.l1.go = "native_1";
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("Panama");
		break;
		
        case "native_1":
			dialog.text = "황금 두블룬이면 길이 다 열리고 백인 놈들도 더 행복해지지. 몰랐나?";
			if (HasSubStr(pchar.model, "Sharle")) {
				dialog.text = dialog.text+" 베르사유의 오래된 공기 냄새가 거의 나는 것 같군, 네가 그곳에 삐걱거리며 들어갔던 그때 말이야.";
			}
			link.l1 = "그딴 식으로 내게 말하지 마, 얼굴이 빨간 녀석. 내가 여기 처음인 건 사실이지만, 네가 어떻게 알았는지는 모르겠군. 지금 당장 여기서 널 쏴버릴 수도 있고, 그 불편함을 보상하려면 아무 여자나 밤새 데리고 있을 수도 있지.";
			link.l1.go = "native_var1";
			link.l2 = "누가 그런 헛소리를 했는지는 모르겠지만, 말은 제법 잘하는군. 그건 인정하지. 이렇게 교양 있는 원주민은 처음 본다.";
			if (HasSubStr(pchar.model, "Sharle")) {
				link.l2 = link.l2+" 베르사유, 내 엉덩이나 먹어라!";
			}
			link.l2.go = "native_var2";
		break;
		
        case "native_var1":
			dialog.text = "아니요, 선장님, 당신은 아무것도 모르십니다. 저는 여기서 완전히 안전해요... 지금은요. 하지만 우리가 이렇게 빨리 친해졌으니, 다시 한 번 시도해봅시다. 한잔 하실래요?";
			link.l1 = "그거 할 수 있지, 네가 내 흥미를 확실히 자극했어.";
			link.l1.go = "native_play";
		break;
		
        case "native_var2":
			dialog.text = "브라보! 이제 서로 이름을 부르며 신경전을 벌이는 사이가 되었군. 자, 평화를 위해 한잔하고 본격적으로 거래 이야기를 해보자.";
			link.l1 = "그거 할 수 있지, 네가 내 흥미를 제대로 자극했어.";
			link.l1.go = "native_play";
		break;
		
        case "native_play":
			dialog.text = "이곳의 목적을 생각해 보면, 선장님의 그 말씀이 꽤 걱정스럽군요! 저는 여기서 거의 한 달째 갇혀 있습니다.\n생각할 수 있는 건 다 해봤고, 이제는 지루함과 허무함에 벽이라도 타고 올라갈 지경입니다.";
			link.l1 = "그럼 가라. 가끔은 교회라도 들러 봐라... 물론 널 들여보내주진 않겠지만.";
			link.l1.go = "native_play_1";
		break;
		
        case "native_play_1":
			dialog.text = "그렇게 간단하지 않아, 내... 계약서에 따라 이 창관에서 스물네 시간을 더 보내야 하거든.";
			link.l1 = "끔찍하게 들리긴 하지만, 나한테 동정은 기대하지 마. 한 달 동안 고급 사창가를 전세 내는 건 꿈이 이루어진 거니까!";
			link.l1.go = "native_play_2";
		break;
		
        case "native_play_2":
			dialog.text = "욕망을 두려워하시오, 선장. 어떻게 여기까지 왔는지 모르겠군. 이번 달은 혼자 보내기로 했었거든. 여자들과 술만 곁에 두고 말이야. 하지만 사흘쯤 지나니 술밖에 상대할 수 없더군. 그리고 오늘은 그 술조차도 지겨워졌지.";
			link.l1 = "그래서 내가 뭘 해주길 바라는 거야? 여자들이랑 술이나 같이 나누자는 거냐?";
			link.l1.go = "native_play_3";
		break;
		
        case "native_play_3":
			dialog.text = "어쩌면 그렇겠지, 하지만 먼저 도박부터 하자고! 카드 한 장에 은화 천 냥이다! 참고로 내 이름은 아게이바나야.";
			link.l1 = "내 거다 "+GetFullName(pchar)+". 그래, 한 판 하자.";
			link.l1.go = "native_accept";
			link.l2 = "내 것은 "+GetFullName(pchar)+". 천 페소라고? 나쁘지 않군. 생각은 해보겠지만, 약속은 못 해.";
			link.l2.go = "native_decline";
		break;
		
        case "native_play_again":
			dialog.text = "마음이 바뀌었나, 선장? 갈까?";
			link.l1 = "그래, 왜 안 되겠어.";
			link.l1.go = "native_accept";
			link.l2 = "아직 아니야.";
			link.l2.go = "native_decline";
		break;
		
        case "native_decline":
			DialogExit();
			
			NextDiag.CurrentNode = "native_play_again";
		break;
		
        case "native_accept":
			DialogExit();
			
			AddDialogExitQuestFunction("ChickenGod_Game1");
		break;
		
        case "native_cards_loss":
			dialog.text = "게임 고마워, 선장. 기분이 좀 나아질 줄 알았는데, 전혀 아니었어. 나 좀 내버려 둬 – 어떻게든 하루쯤은 혼자 버틸 수 있을 거야. 젠장, 그 개자식!";
			link.l1 = "그게 다야? 솔직히 말해서, 내 실망감이 돈을 잔뜩 잃은 쓰라림보다 더 크군.";
			link.l1.go = "native_cards_loss_1";
		break;
		
        case "native_cards_loss_1":
			dialog.text = "여기 있을 생각도 없었잖소, 선장. 하지만 모든 진실을 알고 싶다면... 대륙에 있는 고대 사원을 찾아보시오. 그리고 투우니치 카아네를 넉넉히 가져가시오. 자, 하나 주겠소.";
			link.l1 = "애더 스톤이라고? 구멍이 뚫린 돌이라면 분명히 그 자리에 맞겠지. 고마워, 아구에이바나";
			link.l1.go = "native_cards_loss_2";
		break;
		
        case "native_cards_loss_2":
			dialog.text = "안녕히 가십시오, 선장님.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_Game1LossGoAway");
		break;
		
        case "native_cards_win":
			dialog.text = "이런! 고마워요, 선장님! 돈은 아깝지만, 그래도 오랜만에 인생의 맛을 다시 느꼈으니 다행이네요!";
			link.l1 = "그래, 이런 항로에 그렇게 흥분하는 사람은 처음 봤어. 그런데 그 많은 돈은 어디서 났지?";
			link.l1.go = "native_cards_win_1";
		break;
		
        case "native_cards_win_1":
			dialog.text = "동등한 자에게는 절대 묻지 않을 무례한 질문이군, 선장! 하지만 밤은 아직 젊고, 내게는 돈도 꽤 남아 있지. 한 판 더 어때?";
			link.l1 = "왜 안 되겠어? 한 판 더 하자!";
			link.l1.go = "native_cards_win_2";
		break;
		
        case "native_cards_win_2":
			dialog.text = "이번에는 주사위 게임을 하면서 판돈을 좀 올려보자고 제안하지. 그리고 너한테 해줄 이야기도 있으니, 우리 둘 다 위층 방을 빌려줘. 여기서는 귀가 너무 많아! 마담에게 가서 방값을 내주면 고맙겠어. 안타깝게도 내 신용은 너한테까지 미치지 않거든.";
			link.l1 = "방을 빌리자고? 둘이서? 여기서? 젠장, 아구에이바나! 난 나간다!";
			link.l1.go = "native_cards_rematch_decline";
			link.l2 = "아, 젠장. 이 이야기는 좋은 일화로 끝나든, 엄청 비싼 피바람으로 끝나든 둘 중 하나겠지. 내 검은 내가 가지고 있을 테니, 장난칠 생각 마라, 하하! 여기서 기다려, 내가 해결하고 올 테니까.";
			link.l2.go = "native_cards_rematch_accept";
		break;
		
        case "native_cards_rematch_decline":
			DialogExit();
			
			AddDialogExitQuestFunction("ChickenGod_Game1WinNoRematch");
		break;
		
        case "native_cards_rematch_accept":
			DialogExit();
			
			AddDialogExitQuestFunction("ChickenGod_Game1WinRematch");
		break;
		
        case "native_dice":
			dialog.text = "그래?";
			link.l1 = "진심으로 술 마시고 도박이나 하자고 나를 부른 거였으면 좋겠군.";
			link.l1.go = "native_dice_1";
		break;
		
        case "native_dice_1":
			dialog.text = "걱정 마시오, 선장님, 난 그런 헛소리에 관심 없어! 하지만, 만약 첫날에 여기 나타났다면... 하하! 시작할까?";
			link.l1 = "행운은 용감한 자의 편이다!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_Game2");
		break;
		
        case "native_dice_win":
			dialog.text = "어이쿠! 기분 좋은데! 승리를 축하하오, 선장.";
			link.l1 = "무리하지 마. 이제 대체 여기서 무슨 일이 벌어지고 있는지 나한테 설명해 볼래?";
			link.l1.go = "native_dice_story";
			link.l2 = "넌 참 이상하군, 아구에이바나. 이제 내가 당장 이곳을 떠나지 않으면, 신사로서도 남자로서도 내 명성에 씻을 수 없는 오명이 남게 될 거야. 내 은을 내놓고 각자 갈 길 가자.";
			link.l2.go = "native_dice_win_not_story";
		break;
		
        case "native_dice_loss":
			dialog.text = "정말 아쉽군, 오늘은 좀 다르게 끝내고 싶었는데...";
			link.l1 = "이렇게 천한 게임에서 이기고도 이렇게까지 화내는 남자는 처음 본다. 이제 도대체 여기서 무슨 일이 벌어지고 있는지 좀 설명해 줄 수 있겠나?!";
			link.l1.go = "native_dice_story";
			link.l2 = "꺼져, Agueybana! 이젠 진절머리가 난다!";
			link.l2.go = "native_dice_loss_not_story";
		break;
		
        case "native_dice_story":
			dialog.text = "할 수 있는 만큼 해드릴게요, 선장님. 해도 되는지 잘 모르겠지만, 그래도 선장님 덕분에 내 마지막 며칠이 밝아졌어요... 이 창관에서 말이에요.";
			link.l1 = "그래서 이게 무슨 일이었지?";
			link.l1.go = "native_dice_story_1";
		break;
		
        case "native_dice_story_1":
			dialog.text = "신경 쓰지 마라... 이봐, 백인! 나는 타이노족의 위대한 추장, 아게이바나다. 가끔 나는 백 년쯤 더 일찍 태어나서 스페인 침략자들을 내 섬에서 몰아냈다는 꿈을 꾸지. 하지만 현실은, 내 부족 삼천 명을 머리당 열 두블룬에 광산에 팔아넘겼지.";
			link.l1 = "훌륭한 전기로군. 갑자기 너를 쏴버리고, 아구에이바나, 이 시큼하고 술 냄새 나는 구덩이에 썩게 두고 싶은 충동이 드는군.";
			link.l1.go = "native_dice_story_2";
		break;
		
        case "native_dice_story_2":
			dialog.text = "알겠어요, 선장님. 난 항상 선장님처럼 되고 싶었을 뿐이에요.";
			link.l1 = "나처럼?";
			link.l1.go = "native_dice_story_3";
		break;
		
        case "native_dice_story_3":
			dialog.text = "나는 네 배들을 봤어 – 인간의 천재성이 빚어낸 경이로운 작품들이지 – 그래서 나도 하나 갖고 싶었어. 네 여자들이 몸에 딱 붙는 코르셋을 입은 것도 봤고, 그걸 내가 직접 벗겨보고 싶다는 꿈도 꿨어. 네놈들 중에서 제일 형편없는 지휘관조차 우리 지도자들이 꿈도 못 꿀 권력을 휘두르는 것도 지켜봤지. 유럽에 대한 이야기, 그리고 사람들이 겨우 살아가는 게 아니라 진짜로 살아가는 거대한 돌집들에 산다는 얘기도 들었어. 그리고 그 모든 걸 내가 다 누려봤지! 게다가, 지난 1년 동안 나는 유럽에도 가봤고, 그 모든 걸 직접 경험했어!\n";
			link.l1 = "술을 너무 많이 마셨군, 우두머리. 너한테 유럽으로 가는 유일한 표는 사슬에 묶여서 바티칸이랑 거리의 광대들이 좋아할 때뿐이야. 네가 하는 말은 우리가 사는 세상에선 애초에 불가능한 일이야.";
			link.l1.go = "native_dice_story_4";
		break;
		
        case "native_dice_story_4":
			dialog.text = "그게 우리가 사는 세상이오, 선장. 이미 우리 세상이 잘못됐고, 허상이며, 뭐든 가능하다는 말을 들었소.";
			link.l1 = "그래서 그 똑똑한 놈이 누군데 그런 말을 했지? 보아하니 네가 창관뿐만 아니라 미친놈들 수용소에도 그냥 들어갈 수 있나 보군!";
			link.l1.go = "native_dice_story_5";
		break;
		
        case "native_dice_story_5":
			dialog.text = "이제 내 이야기의 핵심으로 들어가고 있지. 여기서 일이 어떻게 돌아가는지 알겠지? 스페인 놈들이랑 영국 놈들은 전쟁 포로를 총, 도구, 화약으로 사간다. 나는 네 돈으로 우리 부족 사람들을 샀지. 그 이유가 뭔지 알겠나?";
			link.l1 = "왠지 곧 나를 깨우쳐줄 것 같은데.";
			link.l1.go = "native_dice_story_6";
		break;
		
        case "native_dice_story_6":
			dialog.text = "우리의 가장 깊고 부끄러운 욕망을 이루어줄 수 있는 건 신들뿐이야. 원하는 삶을 살 수 없다면, 그들에게 운명을 바꿔 달라고 빌어. 오직 신들만이 우리의 가장 깊고 부끄러운 욕망을 들어줄 수 있지. 이게 바로 길이야. 하지만 문제는, 우리 신들 대부분이 이미 죽었고, 살아 있었다 해도 금에는 관심이 없었다는 거지. 다행히도 자연은 빈자리를 싫어해서, 옛 피라미드 중 하나에 새로운 신이 나타났어. 그 신은 네가 누구든 상관하지 않아. 이곳 사람이든 유럽인이든, 악당이든 영웅이든, 돈만 내면 원하는 걸 얻게 해주지! 모든 부족이 그 사실을 알고 있고, 네 동료 중 몇몇도 알아. 나도 금으로 값을 치르고 너희처럼 살았지. 내일이면 딱 1년이 되겠군.";
			link.l1 = "무슨 신? 1년 만에 유럽까지 갔다 왔다고? 그런데 네 여행의 하이라이트가 카리브 해의 허름한 사창가였다고? 에이, 젠장. 완전 술주정뱅이 헛소리 같지만, 그냥 그런 이야기로 받아들이지. 한잔 하면서 계속 얘기해 봐.";
			link.l1.go = "native_dice_story_7";
		break;
		
        case "native_dice_story_7":
			dialog.text = "내가 말한 건 전부 진실이야. 더 이상 할 말은 없어.";
			link.l1 = "너는 우리 세상에서 오래 살아보지 않았구나, 아구에이바나. 술에 취해 창녀촌에서 떠드는 이야기라면, 끝에는 반드시 교훈이 있어야 해. 제대로 살롱을 마치기 전에 철학 한 번쯤은 해야지.";
			link.l1.go = "native_dice_story_8";
		break;
		
        case "native_dice_story_8":
			dialog.text = "보통 어떻게 끝나지?";
			link.l1 = "모른다고? 그야 참가자의 성별에 따라 다르지! 남자면 주먹질, 여자면 침대로 데려가고. 가끔은 유행 따라 반대가 되기도 하지. 그러니 네 우화의 교훈이 뭐냐? 돈으로 행복을 살 수 없다? 지루하군!";
			link.l1.go = "native_dice_story_9";
		break;
		
        case "native_dice_story_9":
			dialog.text = "그게 내가 말한 우화의 교훈은 아니야. 하지만 네가 먼저 시작했으니, 내 생각을 말해야겠군. 나는 네 주장에 동의하지 않아. 오히려 돈이 행복을 사고, 사람을 더 나아지게 만든다고 믿거든.";
			link.l1 = "헛소리 마! 지금 네 말이 앞뒤가 안 맞는 것 같군. 네 동족을 팔아 큰돈을 벌었잖아. 네가 챙긴 이익이 얼마였는지 기억하나? 거의 삼만 금화였지? 잠깐 생각 좀 해봐라. 하지만 내 눈엔 돈이 네 행복을 사주진 못한 것 같다. 그래도 이 근사한 방은 샀겠지.";
			link.l1.go = "native_dice_story_10";
		break;
		
        case "native_dice_story_10":
			dialog.text = "좋아, 내 처음 말을 좀 고치지. 돈이 있으면 삶도 사람도 더 나아진다.";
			link.l1 = "그게 더 낫긴 한데, 그게 사람을 더 나아지게 만든다고 생각하는 이유가 뭐지? 이제 네가 덕망 높은 본보기라도 된 거냐? 그리고 돈이 별로 없는 사람들은 어쩔 건데? 그 사람들도 나쁜 놈으로 낙인찍을 거야?";
			link.l1.go = "native_dice_story_11";
		break;
		
        case "native_dice_story_11":
			dialog.text = "있잖아, 선장. 난 이 대화가 정말 고마워. 한 번 더 분명히 말하지. 돈은 삶과 사람을 더 좋게 만들어주지. 하지만 이미 선함의 불씨를 지닌 자들에게만 해당되는 말이야.";
			link.l1 = "이봐, 이봐! 그래서 너한텐 불꽃이 없다는 거지, 응?";
			link.l1.go = "native_dice_story_12";
		break;
		
        case "native_dice_story_12":
			dialog.text = "아니. 나는 우리 부족의 족장이었고, 돈과는 달리 권력은 분명히 사람을 타락시키지. 있잖아, 선장. 지금 너를 보니 언젠가 너도 똑같은 딜레마에 직면하게 될 거란 걸 깨닫게 되는군.";
			link.l1 = "네 신도 예지의 능력을 주셨나? 그렇다면 산티아고로 가 보시지. 거긴 온갖 영매와 점쟁이에 특히 관심이 많다고 들었거든.";
			link.l1.go = "native_dice_story_13";
		break;
		
        case "native_dice_story_13":
			dialog.text = "우리의... 에헴, 살롱을 주먹질이나 침대로 이어지지 않게 끝내자고. 내 이야기에 교훈을 찾지 못했으니, 대신 건배를 제안하고 싶네.";
			link.l1 = "완전히 길을 잃었구나, 대장. 하지만 한 가지는 맞아. 그냥 한잔하자!";
			link.l1.go = "native_dice_story_14";
		break;
		
        case "native_dice_story_14":
			dialog.text = "우리의 욕망이 언제나 우리의 필요와 일치하길 바라며 건배하지. 고맙소, 선장님, 이 밤을 마무리하기에 딱 맞는 결말이군. 내 이야기가 사실인지 시험해 보고 싶다면, 대륙으로 가서 그곳의 고대 신전을 찾아보시오.\n거기에 투우니치 카아네 백십삼 개를 가져가야 하오. 나는 아흔아홉 개가 남았으니, 이것들을 가져가시오. 그럼, 안녕히!";
			link.l1 = "구멍 뚫린 돌무더기라니? 이곳 분위기엔 딱 어울리네. 오늘 밤 고마워, 아게이바나. 다시 볼 수 있을까?";
			link.l1.go = "native_dice_story_15";
		break;
		
        case "native_dice_story_15":
			dialog.text = "아니, 넌 못 해. 잘 가, 선장.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_BuyAmulets");
		break;
		
        case "native_dice_win_not_story":
			dialog.text = "알겠소, 선장. 좋든 나쁘든 보물에 대한 정보를 하나 알려주지. 어차피 자네 덕분에 내 마지막 나날이 좀 밝아졌으니... 이 창관에서 말이야. 본토에 있는 고대 신전을 찾아가서 투우니치 카아네 한 무더기를 거기에 가져다 놓으시오. 자, 여기 하나 가져가.";
			link.l1 = "구멍 뚫린 돌이라니? 정말 매력적이군, 그리고 구멍 난 돌이 이 장소에 딱 어울리지. 네가 하는 짓은 이제 진절머리가 난다!";
			link.l1.go = "native_dice_not_story";
		break;
		
        case "native_dice_loss_not_story":
			dialog.text = "화가 난 건 이해하오, 선장. 좋든 싫든 보물에 대한 정보를 하나 주겠소. 어차피 자네 덕분에 내 마지막 날들이 좀 밝아졌으니... 이 매음굴에서 말이오. 대지에 있는 고대 사원을 찾아가서 투우니치 카아네 한 무더기를 가져다 놓으시오. 여기, 하나 가져가게.";
			link.l1 = "애더 스톤이라고? 참 매력적이군, 그리고 구멍이 뚫린 돌이 이 장소에 딱 맞아. 네가 하는 짓, 이제 진절머리가 난다!";
			link.l1.go = "native_dice_not_story";
		break;
		
        case "native_dice_not_story":
			dialog.text = "안녕히 가십시오, 선장님.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_NotBuyAmulets");
		break;
		
		case "joruba":
			dialog.text = "또 한 놈이야? 젠장, 너희들 전부 진짜 지긋지긋하다!";
			link.l1 = "아, 아, 아! 꺼져!";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "joruba_1";
			AddDialogExitQuestFunction("ChickenGod_ShootJoruba");
		break;
		
		case "joruba_1":
			dialog.text = "어? 그래, 맞아. 내 앞에 무릎 꿇어라, 인간! 내 피라미드의 힘을 보아라!";
			link.l1 = "(필사적으로 비명을 지른다)";
			link.l1.go = "joruba_2";
			link.l2 = "(괴물을 죽여라)";
			link.l2.go = "joruba_3";
		break;
		
		case "joruba_2":
			dialog.text = "맞소. 내 소박한 상관에 온 것을 환영하오, 선장.";
			link.l1 = "너, 뭐야?";
			link.l1.go = "joruba_4";
		break;
		
		case "joruba_3":
			DialogExit();
			
			NextDiag.CurrentNode = "joruba_3_next";
			AddDialogExitQuestFunction("ChickenGod_ShootJoruba");
		break;
		
		case "joruba_3_next":
			dialog.text = "끈질긴 집념을 칭찬하오. 다음 수는 무엇이오, 선장? 무역을 좀 해볼 생각은 있소?";
			link.l1 = "너... 너 뭐야?";
			link.l1.go = "joruba_4";
		break;
		
		case "joruba_4":
			dialog.text = "내가 누구인지는 중요하지 않아, 내가 무슨 역할을 하느냐가 중요하지. 지금 이 순간, 나는 이 구멍 같은 곳의 주민들과 서로 이익이 되는 거래를 하고 있지.";
			link.l1 = "쥐구멍 말인가? 이 사원을 말하는 거야?";
			link.l1.go = "joruba_6";
			
			AddDialogExitQuestFunction("ChickenGod_JorubaToNormal");
		break;
		
		case "joruba_6":
			dialog.text = "첫 번째이자 마지막 경고다, 선장! 하지만 이 피라미드는 정말로 비좁군. 분명히 내가 이곳을 벗어날 때가 된 것 같아.";
			link.l1 = "거래에 대해 말했지. 무슨 종류의 거래를 말하는 거야?";
			if (CheckAttribute(pchar, "questTemp.ChickenGod.SawJoruba")) {
				link.l1.go = "joruba_7A";
			} else {
				link.l1.go = "joruba_7";
			}
		break;
		
		case "joruba_7":
			dialog.text = "나는 사람들이 가장 필요로 하는 것을 준다.";
			link.l1 = "소원을 들어준다고? 동화에 나오는 지니처럼? 이런, 대체 여기서 무슨 일이 벌어지고 있는 거야?!";
			link.l1.go = "joruba_7_1";
		break;
		
		case "joruba_7_1":
			dialog.text = "말도 안 되는 소리 하지 마! 나는 사람들이 이 세상에 온 목적을 가장 빠르고 기분 좋게 이루도록 도와줄 뿐이야.";
			link.l1 = "너 주술사 같은 거냐?";
			link.l1.go = "joruba_8";
		break;
		
		case "joruba_7A":
			dialog.text = "그래, 너는 아구에이바나를 만났으니, 이제 뭔가 감이 오겠지.";
			link.l1 = "그 불쌍하고 길 잃은 만취 인디언이 네 짓이었나?";
			link.l1.go = "joruba_7A_1";
		break;
		
		case "joruba_7A_1":
			dialog.text = "그의 부족을 몇 천 파운드 금에 팔아넘긴 건 내가 아니었고, 술통을 목구멍에 들이부은 것도 내가 아니며, 수백 명의 창녀에게서 온갖 병을 얻도록 강요한 적도 없어. 그가 나에게 백인 귀족으로 만들어 달라고 했으니, 나는 그렇게 했을 뿐이야. 그의 운명이 나에게 명령했으니까.";
			link.l1 = "소원을 들어준다고? 동화 속 요정이라도 된 거야? 이런, 도대체 무슨 일이야?!";
			link.l1.go = "joruba_7A_2";
		break;
		
		case "joruba_7A_2":
			dialog.text = "말도 안 되는 소리 하지 마! 나는 그저 사람들이 이 세상에 온 목적을 가장 빠르고 즐거운 방식으로 이루도록 도울 뿐이야. 아구에이바나는 원래 자기 민족을 유럽 침략자들의 멍에에서 구해야 했지. 그런데 정작 그는 사령관 딸의 코르셋에 정신이 팔려 자기 것까지 저당잡히기로 했지 뭐야.\n그때부터 그의 삶에 남은 의미는 자신의 실수가 얼마나 깊은지 깨닫고, 곧 다시 시작하는 것뿐이었어. 유럽에서의 1년, 간경화, 그리고 너희 둘이 창관에서 보낸 시간도 도움이 됐겠지. 인정하마, 그 녀석 정말 멋진 휴가를 보냈어, 하하!";
			link.l1 = "간경... 뭐라고? 너 혹시 주술사 같은 거냐?";
			link.l1.go = "joruba_8";
		break;
		
		case "joruba_8":
			dialog.text = "뭐 그런 거지. 그래도 내 제안은 마음에 들 거야. 그리고 이번에는 정말로 기꺼이 도와주고 싶어.";
			link.l1 = "그래. 얼마지?";
			link.l1.go = "joruba_9A";
			link.l2 = "왜? 내가 특별하냐?";
			link.l2.go = "joruba_9B";
		break;
		
		case "joruba_9A":
			dialog.text = "그렇게 나쁘진 않군, 선장. 네가 똑똑한 건지 당나귀만큼 멍청한 건지 모르겠지만, 네 가능성이 조금은 올라갔어. 값은 문제 안 될 거야.";
			link.l1 = "누굴 죽여야 해? 나는 그런 일 안 해.";
			link.l1.go = "joruba_10";
		break;
		
		case "joruba_9B":
			dialog.text = "네가 이 세상에 태어난 이유가 내 좋은 친구한테 구멍을 뚫어주려고 그런 거니까, 하하!";
			link.l1 = "누군가 죽이길 원해? 난 그런 일 안 해.";
			link.l1.go = "joruba_10";
		break;
		
		case "joruba_10":
			dialog.text = "첫째, 네가 한다. 둘째, 우리는 네 번의 큰 거래와 네 번의 작은 거래를 진행할 거다.\n각 거래마다 네가 훨씬 더 강해지고, 이 잔혹하고 기이한 세상에서 살아남을 확률도 높아질 거야.\n모든 거래를 완수하면, 언젠가 신들과 대등하게 싸울 수 있을 거라고 내가 장담하지. 평범한 인간 따위는 말할 것도 없고.";
			link.l1 = "재밌겠는데. 무슨 일인지 말해 봐.";
			link.l1.go = "joruba_11";
		break;
		
		case "joruba_11":
			dialog.text = "똑똑한 선택이군! 보통 내 연설이 끝나면 사람들은 심장마비 의심으로 블루웰드로 실려 가기 마련인데, 너는 꽤 잘 버티는구나. 자, 할 일 목록이다. 내가 맡기고 싶은 잡다한 거래 심부름 몇 가지야. 기한은 없어, 헤헤.";
			link.l1 = "흥미롭군. 목록은 나중에 읽어보지. 또 뭐 있나?";
			link.l1.go = "joruba_12";
		break;
		
		case "joruba_12":
			dialog.text = "그래, 첫 번째로 큰 거래지. 가격은 이천 두블룬이다.";
			link.l1 = "혹할지도 모르겠군... 하지만 돈이 너무 많잖아! 왜 그렇게 많이 필요하지? 페소로 내도 돼?";
			link.l1.go = "joruba_13";
			link.l2 = "미쳤어? 그 돈이면 프리깃 한 척은 살 수 있겠는데!";
			link.l2.go = "joruba_insult";
		break;
		
		case "joruba_13":
			dialog.text = "피라미드는 수리가 필요해. 석재가 가끔 손님들 머리 위로 떨어지는데, 그건 장사에 안 좋아. 내 부하들이 매일 임시로 고치고 있지만, 우리 조직이 이 문제를 완전히 해결하려면 외부에서 급하게 자금이 들어와야 해. 페소에 관해서라면, 난 별로 탐탁지 않아. 환율이 너무 들쭉날쭉하거든.";
			link.l1 = "너무 정직한 페소들에게 너무하군... 잠깐만, 너 혼자가 아니었어?";
			link.l1.go = "joruba_14";
		break;
		
		case "joruba_14":
			dialog.text = "아니, 나는 그저 진지한 조직의 허울일 뿐이야. 그래서, 할 거야?";
			link.l1 = "생각은 해보겠지만, 먼저 이렇게 큰 돈을 주고 내가 뭘 받는지부터 알고 싶군.";
			link.l1.go = "joruba_15";
		break;
		
		case "joruba_15":
			dialog.text = "왜 미리 알려서 재미를 망치겠어? 게다가, 그 돈은 그냥 세금이라 생각해. 네가 정말 얻게 될 가장 값진 건 다음 거래의 기회를 여는 거야.\n보상은 신의 축복처럼 대단할 거다. 그리고 어디서도 못 볼 특별한 것들이니, 명심해!";
			link.l1 = "좋아. 네 이름이 뭐였지?";
			link.l1.go = "joruba_16";
		break;
		
		case "joruba_16":
			dialog.text = "위대한 아루바. 마지막으로 한 가지 더, "+pchar.name+", 피라미드 입장은 하루에 한 번만 허락된다. 다른 손님들을 기다리게 하지 말고, 괜히 나를 귀찮게 하지 마라.";
			link.l1 = "줄이 서 있는 것 같진 않군... 안녕히 계십시오, 폐하.";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "joruba_wait";
			AddDialogExitQuestFunction("ChickenGod_GiveFirstTask");
		break;
		
		case "joruba_wait":
			dialog.text = "아, 선장님. 나한테 무슨 일이 있소?";
			
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.p1") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.p1.Completed") && PCharDublonsTotal() >= 2000) {
				link.p1 = "Here are your doubloons. It's hard enough to carry that damned metal around... but it is even harder to part with it!";
				link.p1.go = "joruba_p1";
			}
			
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.p2") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.p2.Completed") && GetCharacterItem(pchar, "cannabis7") >= 15) {
				link.p2 = "I kept my end of the bargain. Here's your herb, Aruba.";
				link.p2.go = "joruba_p2";
			}
			
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.p3") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.p3.Completed") && ChickenGod_FindQuestShips()) {
				for (i = 0; i < questShipsNum; i++) {
					sTemp = "p3_" + (i + 1);
				
					chref = GetCharacter(questShips[i]);
					sld = GetRealShip(sti(chref.ship.type));
					link.(sTemp) = "Aruba, ahoy! " + GetStrSmallRegister(XI_ConvertString(sld.BaseName)) + " '" + chref.Ship.Name + "' is all yours!";
					link.(sTemp).go = "joruba_p3_ship_" + questShips[i];
					if (FindCompanionShips(SHIP_PINK) && sti(pchar.questTemp.ChickenGod.Tasks.Schyot) <= 1 && startHeroType != 4)
					{
						link.(sTemp) = "Aruba, ahoy! Pink '" + chref.Ship.Name + "' is all yours!";
						link.(sTemp).go = "joruba_p3_PinkOtkaz";
					}
					/*if (FindCompanionShips(SHIP_GALEON_SM))
					{
						link.(sTemp) = "Aruba, ahoy! Galeon '" + chref.Ship.Name + "' is all yours!";
						link.(sTemp).go = "joruba_p3_HolyMercy";
					}*/
				}
			}
			
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.p4") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.p4.Completed")) {
				link.p3 = "I'm willing to make a sacrifice.";
				link.p3.go = "joruba_p4";
			}
			
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o2.Lady") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o2.Completed")) {
				link.o2 = "I am bringing you a bride and troubles with the Spanish authorities, sir. The lady is taking a stroll outside, well protected by my men. I will not give her to you until you convince me of the nobility of your intentions.";
				link.o2.go = "joruba_o2";
			}
			
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o3") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o3.Completed") && GetCharacterFreeItem(pchar, "cirass4") >= 1) {
				link.o3 = "Here's your armor, Aruba. Make sure my reward will make up for it.";
				link.o3.go = "joruba_o3";
			}
			
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o4") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o4.Completed") && GetPrisonerQty() >= 30) {
				link.o4 = "I have the prisoners you asked for.";
				link.o4.go = "joruba_o4";
			}
			
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o5") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o5.Completed") && GetCharacterItem(pchar, "talisman11") >= 113) {
				link.p2 = "I brought you your junk. Here, a hundred and thirteen stones, just like you asked for.";
				link.p2.go = "joruba_o5";
			}
			
			bOk = (PCharDublonsTotal() >= 25000) || (ChickenGod_HaveOfficers());
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o6") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o6.Completed") && bOk) {
				link.p3 = "I'm willing to make a sacrifice.";
				link.p3.go = "joruba_o6";
			}
			
			if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.p4.Completed")) {
				link.respec = "(Respec character's stats)";
				link.respec.go = "joruba_respec";
			}
			
			link.exit = "I am just passing by.";
			link.exit.go = "joruba_wait_1";
			
			NextDiag.TempNode = "joruba_wait";
		break;
		
		case "joruba_wait_1":
			dialog.text = "그럼 다음에 보자.";
			link.l1 = "";
			link.l1.go = "exit";
		break;
		
		case "joruba_p1":
			dialog.text = "나쁘지 않군, 그 금은 잘 써주지. 자, 이건 한때 아주 고결한 타이노 추장이 가졌던 작은 장신구다. 금덩이를 잔뜩 나르는 데 도움이 되지. 그 양반한텐 확실히 도움이 됐었지, 크크...";
			link.l1 = "고맙소, 후회하지 않길 바라오. 다음 거래는 무엇이오?";
			link.l1.go = "joruba_p1_1";
			link.l2 = "잠깐만. 내가 너한테 금덩이를 줬는데, 대신 진흙덩어리를 받았다고? 환불해 줘!";
			link.l2.go = "joruba_insult";
			
			RemoveDublonsFromPCharTotal(2000);
			pchar.questTemp.ChickenGod.Gold = 2000;
			
			pchar.questTemp.ChickenGod.Tasks.p1.Completed = true;
			GiveItem2Character(pchar, "talisman13");
			//Log_info("You received Taino Figurine");
			PlaySound("interface\important_item.wav");
		break;
		
		case "joruba_p1_1":
			dialog.text = "에? 그래, 다음 거래지. 이 금이면 당분간 충분하니, 이제는 좀 더 영적인 물건을 생각해봐야겠군. 치료약을 찾아야겠어.";
			link.l1 = "왜, 어디 아픈가?";
			link.l1.go = "joruba_p1_2";
		break;
		
		case "joruba_p1_2":
			dialog.text = "내 영혼이 그렇지. 알다시피, 그 종교재판 사건 이후로 신부들이 내 보잘것없는 피라미드를 피하고 있어서, 우리는 좀 더 전통적인 방법에 의존해야 해. 내가, 아니, 내 팩토리아가 계속 운영되려면 마가로사 식물 열다섯 개가 필요해.";
			if (!ChickenGod_TalkedToAmelia()) {
				link.l1 = "저게 약초야?";
			} else {
				link.l1 = "그게 뭔지 나도 알아, 헤헤.";
			}
			link.l1.go = "joruba_p1_3";
		break;
		
		case "joruba_p1_3":
			dialog.text = "솔직히 말하자면, 이건 아주 귀한 약초야. 군도를 돌아다니며 몇 년씩이나 이걸 모을 생각이라면 정말 신중히 생각해 봐.";
			link.l1 = "약속은 못 하지만, 건강을 빌고 약초에 대한 내 보상이 그만한 가치가 있길 바라네.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_GiveSecondTask");
		break;
		
		case "joruba_p2":
			dialog.text = "좋아, 오늘은 공식적으로 내 휴일이야! 이런 거래는 진짜 보물만큼 값지지. 자, 보라구!\n이 마체테는 한때 그 멍청이 카넥의 머리를 거의 쪼갤 뻔했어! 그래서 나한테 아주 소중한 물건이니, 부디 잘 다뤄주길 부탁할게. 오래됐지만 정말 잘 만들어졌어. 요즘은 이런 강철을 더 이상 만들지 않거든.";
			link.l1 = "카넥? 그게 누구야?";
			link.l1.go = "joruba_p2_1";
			
			TakeNItems(pchar, "cannabis7", -15);
			pchar.questTemp.ChickenGod.Tasks.p2.Completed = true;
			if (pchar.rank >= 21)
			{
				sld = ItemsFromID("machete2");
                sld.Attack = 80.0;
			}
			else
			{
				sld = ItemsFromID("machete2");
                sld.Attack = 60.0;
			}
			GiveItem2Character(pchar, "machete2");
			//Log_info("You received Machete Conquistador");
			PlaySound("interface\important_item.wav");
			SetAlchemyRecipeKnown("bullet_double");
			SetAlchemyRecipeKnown("grapeshot_double");
			ChickenGod_InitAmmo();
		break;
		
		case "joruba_p2_1":
			dialog.text = "오, 너희 둘이 만나게 되겠군. 그런데 너, 혹시 손에 흙 묻히는 일은 깔보는 잘난 척쟁이 아니지? 만약 그렇다면 운이 없겠어, 보상의 두 번째는 이중 장전 탄약 설계도거든.";
			if (pchar.HeroParam.HeroType == "HeroType_4") {
				link.l1 = "오, 나 그런 거 좋아하지. 하지만 그게 뭐가 특별한데? 화약을 두 번 넣는 건 새로울 게 없으니, 보아하니 자네는 그 박물관 마체테 시절 이후로 피라미드에서 한 발짝도 안 나간 모양이군.";
			} else {
				link.l1 = "그게 다야? 이봐...";
			}
			link.l1.go = "joruba_p2_2";
		break;
		
		case "joruba_p2_2":
			dialog.text = "똑똑한 척하지 말고 들어! 아무 멍청이나 화약 두 덩이를 통에 넣고 장님이 되거나, 얼굴이 타거나, 코가 부러질 위험을 감수할 수 있지. 내가 알려주는 건 좀 더 마법 같은 방법이야: 화약 품질을 꼼꼼히 확인하고, 알맞은 곱기로 갈아, 탄환이나 산탄을 넣고, 잘게 썬 두블룬으로 양념을 해. 그럼 폭발이 큐이라스도 산산조각 낼 거다!";
			link.l1 = "돈으로 해결하려고? 참 너답군.";
			link.l1.go = "joruba_p2_3";
		break;
		
		case "joruba_p2_3":
			dialog.text = "너 정말 못 말리겠군! 좋아, 수류탄 박격포 하나랑 그에 쓸 수류탄 열두 개도 챙겨. 그렇게 똑똑하다면, 수류탄 설계도쯤은 금방 네 힘으로 구해 오겠지!";
			link.l1 = "대단히 감사합니다, 나리. 이제 어떻게 할까요?";
			link.l1.go = "joruba_p2_4";
			
			//Log_info("You received Hand mortar");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "mortairgun");
			TakeNItems(pchar, "grenade", 10);
		break;
		
		case "joruba_p2_4":
			dialog.text = "마음에 안 들 거야. 배가 필요해... 아니, 그 배가 필요해. 알지? 사연이 깃든 그 배 말이야.";
			link.l1 = "왜? 너는 선장도 아니잖아.";
			link.l1.go = "joruba_p2_5";
		break;
		
		case "joruba_p2_5":
			dialog.text = "네 알 바 아니다! 네 보상이나 신경 써라. 내가 마음만 먹으면 이 피라미드를 위에서 아래까지 다 청소하라고 시킬 수도 있어! 그래도 너는 나한테 빚진 거다!";
			link.l1 = "넌 분명히 선장이 아니구나, 선장이라면 배가 정박하려면 부두나 만이 필요하다는 걸 알 텐데. 도대체 어떻게 내보고 네 피라미드 안에 배를 들여놓으라는 거야?!";
			link.l1.go = "joruba_p2_6";
		break;
		
		case "joruba_p2_6":
			dialog.text = "혹시 내 피라미드 뒤에 거대한 호수가 있는 거 봤냐? 맞아. 근처에 있는 함대에 적당한 배만 대면 내 부하들이 알아서 할 거다. 이제 꺼져, 줄 막고 있으니까.";
			link.l1 = "물론이지. 잘 가라!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_GiveThirdTask");
		break;
		
		case "joruba_p3":
			sld = GetCharacter(sti(companion));
			pchar.questTemp.ChickenGod.Tasks.p3.ship = sld.ship.type;
			RemoveCharacterCompanion(pchar, sld);
			AddPassenger(pchar, sld, false);
						
			npchar.ship.type = pchar.questTemp.ChickenGod.Tasks.p3.ship;
			SetCharacterShipLocation(npchar, "Temple");
						
			sld = GetRealShip(sti(pchar.questTemp.ChickenGod.Tasks.p3.ship));
					
			dialog.text = "좋아! 알겠어!";
			link.l1 = "건방진 척 그만하고 내 보상이나 내놔!";
			link.l1.go = "joruba_p3_1";
			switch (sti(sld.BaseType)) {
				case SHIP_MAYFANG:
					dialog.text = "나머지 둘은 어쩌고? 네가 직접 챙길 수도 있었잖아? 크크.";
				break;
				
				case SHIP_MIRAGE:
					dialog.text = "나머지 둘은 어쩌고? 너 혼자 챙길 생각은 안 했냐? 크크.";
				break;
				
				case SHIP_VALCIRIA:
					dialog.text = "나머지 둘은 어쩔 건데? 네가 챙길 수도 있었잖아? 크크.";
				break;
				
				case SHIP_FRIGATE_L:
					dialog.text = "젠장, 네가 그 여자를 자기 걸로 가지려 하지 않은 게 놀랍군. 이게 바로 사연 있는 배지! 젠장, 윌리엄... 네가 늘 꿈꾸던 대로 집에 돌아가서 훌륭한 은행을 세웠으면 정말 좋겠어.";
				break;
				
				case SHIP_CORVETTE_QUEST:
					sTemp = "privateer";
					if (isMainCharacterPatented()) {
						sTemp = GetStrSmallRegister(GetAddress_FormTitle(sti(Items[sti(pchar.EquipedPatentId)].Nation), sti(Items[sti(pchar.EquipedPatentId)].TitulCur)));
					}
					
					dialog.text = "이것 좀 봐라! 너는 네 임명장에 먹칠을 하는구나, "+sTemp+"!";
				break;
				
				case SHIP_POLACRE_QUEST:
					dialog.text = "찰리 프린스가 내 옛 피라미드에 있던 죄를 입증할 증거를 없애기로 했다고? 잘했군!";
				break;
				
				case SHIP_ECLIATON:
					dialog.text = "기함을 잃은 걸 상관들에게 어떻게 설명할지 잘 생각해 보시오, 제독 나리. 아, 실례, 총독 나리.";
				break;
				
				case SHIP_CURSED_FDM:
					dialog.text = "미신에 빠진 바보냐, 그냥 바보냐? 저 여자는 엄청난 가치를 지녔어! 이게 공정한 거래인지는 모르겠지만, 뭐 어때.";
				break;
				
				case SHIP_FDM:
					dialog.text = "미신에 빠진 바보냐, 그냥 바보냐? 저 여자는 엄청난 가치가 있어! 이게 공정한 거래인지는 모르겠지만, 뭐 어때.";
				break;
				
				case SHIP_RENOVATED_FDM:
					dialog.text = "미신에 빠진 바보냐, 그냥 바보냐? 저 여자는 엄청난 가치를 지녔어! 이게 공정한 거래인지는 모르겠지만, 뭐 어때.";
				break;
				
				case SHIP_ELCASADOR:
					dialog.text = "좋은 선택이야! 나 카스티야 놈들 좋아하거든. 일이 끝나면 그녀를 그놈들에게 돌려줄지도 몰라.";
				break;
				
				case SHIP_HIMERA:
					dialog.text = "정말로, 당신은 심장이 없군, 선장. 이 배에서는 배신의 냄새가 진동해. 내가 이 배를 가져가겠다.";
				break;
				
				case SHIP_PINK:
					if (startHeroType == 4)
					{
						dialog.text = "그래, 이 배도 뭔가 사연이 있을지 모르지... 하지만 너무 쉽게 손에 넣은 거 아니냐? 뭐, 좋아. 네 경우는 특별하니까 받아주지, 내 사랑. 적어도 내 젊은 시절이 떠오르는군.";
						Achievment_Set("ach_CL_127");
					}
					else 
					{
						dialog.text = "그래, 이 배에도 뭔가 사연이 있을지 모르지... 하지만 얻기엔 너무 쉬웠던 거 아니냐? 에이, 알겠다. 좋아, 선장. 네가 내 목록에 있던 일들을 잘 해냈으니 이번엔 그냥 넘어가 주지. 받아들이마. 그래도 젊었을 때 생각이 좀 나는군.";
					}
				break;
				
				case SHIP_GALEON_SM:
					dialog.text = "신부를 봤나? 뭐, 곧 만나게 될 거야. 그리고 쌍발 권총 탄환을 충분히 챙겨두는 게 좋을 거다. 그것도 안 통하면, 나무 말뚝을 써 봐.";
				break;
				
				case SHIP_LADYBETH:
					dialog.text = "신부를 봤나? 뭐, 곧 만나게 될 거야. 그리고 쌍발 권총 탄약을 충분히 챙기는 게 좋을 거다. 그걸로도 안 되면, 나무 말뚝을 써봐.";
				break;
				
				case SHIP_MEMENTO:
					dialog.text = "신부를 봤나? 뭐, 곧 만나게 될 거야. 그리고 쌍발 권총 탄약을 충분히 챙겨두는 게 좋을 거다. 그것도 안 통하면, 나무 말뚝을 써 봐.";
				break;
			}
		break;
		
		case "joruba_p3_PinkOtkaz":
			dialog.text = "그래, 이 배에도 역사가 있을지 몰라... 하지만 너무 쉽게 손에 넣은 거 아니냐? 말도 안 돼! 아직 해야 할 일이 산더미처럼 남았어. 그거 다 끝내고 나서야 이 희생에 대해 다시 얘기하지.";
			link.l1 = "...";
			link.l1.go = "exit";
		break;
		
		case "joruba_p3_1":
			dialog.text = "내가 그대를 축복하노라, "+GetFullName(pchar)+". 바다가 그대에게 순조롭기를. 이제 다음 거래에 대해 이야기해 보지...";
			link.l1 = "잠깐, 뭐라고? 우리 이성의 시대에 그런 헛소리에 속아넘어가는 촌놈 바보도 없을 텐데! 내가 네 자선함에 동전 한 푼 넣은 게 아니라, 제대로 된 군함 한 척을 준 거라고!";
			link.l1.go = "joruba_insult";
			link.l2 = "잠깐만. 당신의 축복이 나한테 대체 무슨 의미가 있지?";
			link.l2.go = "joruba_p3_2";
			
			pchar.questTemp.ChickenGod.Tasks.p3.Completed = true;
		break;
		
		case "joruba_p3_2":
			dialog.text = "이제부터 네가 지휘하는 모든 배는 더 튼튼한 선체의 축복을 받을 거다, 반면 네 적들은 그 반대의 고통을 겪게 되지. 그리고 바다에서의 시간도 너한테는 더 천천히 흐를 거야. 그래도 이 썩은 바다를 완전히 굴복시키기에 부족하다면, 네 애비한테 가서 환불이나 요구해라!";
			link.l1 = "안 되면, 오늘 밤에 다시 와서 네 피라미드를 불태워버릴 거라고 맹세한다! 이제, 다음 거래에 대해 말해봐!";
			link.l1.go = "joruba_p3_3";
			notification("+10% hull defence", "None");
			notification("+10% damage to enemy ships hull", "None");
			notification("+5% speed on the Global Map", "None");
			PlaySound("Interface\new_level.wav");
		break;
		
		case "joruba_p3_3":
			dialog.text = "이 맛에 점점 빠져드는 건가, 선장? 안타깝게도 나도 마찬가지야. 내가 왜 이 피라미드를 내 사무실로 골랐다고 생각하지?";
			link.l1 = "아직도 마녀 사냥이 계속되고 있어서 그런 거 아냐?";
			link.l1.go = "joruba_p3_4";
		break;
		
		case "joruba_p3_4":
			dialog.text = "헤헤, 아니, 꼭 그런 건 아니지. 내가 여기서 장사를 하는 건 최고의 거래엔 피가 필요하기 때문이야. 이 피라미드도 피를 요구하지. 나도 피가 필요해. 예전부터 그래왔고, 앞으로도 그럴 거다.";
			link.l1 = "꿈도 꾸지 마라, 이 괴물아. 네가 죽일 희생자를 내가 넘겨주진 않을 거다!";
			link.l1.go = "joruba_p3_5";
		break;
		
		case "joruba_p3_5":
			dialog.text = "그래서 너는 몇 명이나 죽였지, 응? 잠깐, 내가 정확한 숫자까지 말해줄게: 네가 직접 죽인 건 "+(Statistic_AddValue(pchar,"Solder_s",0)+Statistic_AddValue(pchar,"Citizen_s",0)+Statistic_AddValue(pchar,"Warrior_s",0)+Statistic_AddValue(pchar,"Solder_g",0)+Statistic_AddValue(pchar,"Citizen_g",0)+Statistic_AddValue(pchar,"Warrior_g",0))+" 이놈들아! 너희는 야망과 부에 대한 탐욕 때문에 시체의 산을 쌓아 올렸구나! ";
			if (HasSubStr(pchar.model, "Sharle")) {
				dialog.text = dialog.text+"네 형제의 빚 때문에 이미 보통 유럽 전쟁보다 더 많은 사람이 죽었어! ";
			}
			dialog.text = dialog.text+"여기서 나한테 훈계하려 들지도 마라, 나도 너를 심판할 생각 없으니. 누군가의 성공은 항상 다른 이의 비극으로 치러지는 법이고, 신들, 그래, 신들은 지켜보고 자기 몫을 챙길 거다!";
			link.l1 = "지금은 대답할 수 없어... 여기서 나가야겠어.";
			link.l1.go = "joruba_p3_6";
		break;
		
		case "joruba_p3_6":
			dialog.text = "머리를 식힐 급한 필요가 있나? 좋아, 하지만 먼저 내 말을 들어라. 네가 큰 가치를 지닌 자를 내게 데려온다면, 네 몸과 정신을 완전히 지배할 힘을 주겠다. 그냥 엑스트라나 거리의 이름 없는 쥐새끼, 썩은 선창의 쥐 따위는 안 된다. 네 뒤를 따르며, 네 비극과 희극에 중요한 역할을 하는 그런 사람을 데려와라.";
			link.l1 = "내 장교 중 한 명이라고? 너도 참 바닥까지 떨어졌구나, 아루바! 이 소문이 퍼지기라도 하면...";
			link.l1.go = "joruba_p3_7";
		break;
		
		case "joruba_p3_7":
			dialog.text = "항상 그랬듯이 비밀은 내가 지킨다. 그리고 또 징징대기 전에, 다른 방법도 있다는 걸 알려주지.";
			link.l1 = "그게 무슨 뜻이야? 내가 내 사람들을 억지로 제단까지 끌고 가지 않아도 된다는 거야?";
			link.l1.go = "joruba_p3_8";
		break;
		
		case "joruba_p3_8":
			dialog.text = "아니, 하지만 다른 방법은 마음에 들지 않을 거야. 피로 값을 치르고 싶지 않다면, 금으로 내도 돼. 삼천 두블론이면 양심도 깨끗해지지. 돈이란 게 그런 힘이 있거든 – 난 그게 정말 좋아!";
			link.l1 = "잘 있어라, 아루바. 더 이상 너랑 이야기하고 싶지 않아.";
			link.l1.go = "joruba_p3_9";
		break;
		
		case "joruba_p3_9":
			dialog.text = "나를 어디서 찾을 수 있는지 알잖아.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_GiveFourthTask");
		break;
		
		case "joruba_p4":
			dialog.text = "스페인 종교재판소가 오기 전에 빨리 끝내자. 피냐, 금이냐?";
			if (PCharDublonsTotal() >= 3000)
			{
				link.l1 = "금이지. 여기 삼천이다, 하지만 이 황야에서 네가 이렇게 엄청난 돈을 어떻게 쓸 수 있을지 상상이 안 가는군.";
				link.l1.go = "joruba_p4_1";
			}
			if (ChickenGod_HaveOfficers()) 
			{
				link.l2 = "피.";
				link.l2.go = "joruba_p4_other";
			}
			link.l3 = "신경 쓰지 마.";
			link.l3.go = "exit";
		break;
		
		case "joruba_p4_1":
			dialog.text = "...";
			link.l1 = "끝났어? 이제 내 보상에 대해 얘기하자.";
			link.l1.go = "joruba_p4_reward_1";
			RemoveDublonsFromPCharTotal(3000);
			pchar.questTemp.ChickenGod.Gold = sti(pchar.questTemp.ChickenGod.Gold) + 3000;
		break;
		
		case "joruba_p4_other":
			dialog.text = "그러면 되지. 이름을 말해.";
			
			ChickenGod_AddOfficerLink(link, "joruba_p4_off_", "Duran");
			ChickenGod_AddOfficerLink(link, "joruba_p4_off_", "Baker");
			ChickenGod_AddOfficerLink(link, "joruba_p4_off_", "Folke");
			ChickenGod_AddOfficerLink(link, "joruba_p4_off_", "Avendel");
			ChickenGod_AddOfficerLink(link, "joruba_p4_off_", "Tonzag");
			if (!CheckAttribute(pchar, "questTemp.PZ_LongwayNelzyaOtdatArube")) ChickenGod_AddOfficerLink(link, "joruba_p4_off_", "Longway");
			ChickenGod_AddOfficerLink(link, "joruba_p4_off_", "Knippel");
			ChickenGod_AddOfficerLink(link, "joruba_p4_off_", "Tichingitu");
			ChickenGod_AddOfficerLink(link, "joruba_p4_off_", "Irons");
		break;
		
		case "joruba_p4_off":
			if (pchar.questTemp.ChickenGod.Sacrifice == "Duran" && !CheckAttribute(pchar, "questTemp.SKD_DuranDruzhba"))
			{
				dialog.text = "Claude Durand는 장교가 아니라 무자비한 용병이니, 다른 희생자를 고르시오.";
				link.l1 = "";
				link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.ChickenGod.Sacrifice == "Duran" && CheckAttribute(pchar, "questTemp.SKD_DuranDruzhba") && CheckAttribute(pchar, "questTemp.SKD_DevushkaUbita"))
			{
				Achievment_Set("ach_CL_116");
			}
			
			dialog.text = "네 조공을 받겠다. 넌 지켜볼 필요 없어.";
			link.l1 = "아니, 없어. 한 시간 후에 내 보상을 받으러 올 거야.";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "joruba_p4_reward";
			ChangeCharacterComplexReputation(pchar, "nobility", -50);
			
			AddDialogExitQuestFunction("ChickenGod_KillOfficer");
		break;
		
		case "joruba_o6_money":
			dialog.text = "훌륭한 선택이군. 제단에 묻은 피를 치우는 건 질색이라서, 금이 더 낫지. 자, 이 물약을 가져가게—내 좋은 친구가 준 선물이네.";
			link.l1 = "맛이 꽤 괜찮은데...";
			link.l1.go = "exit";
			
			PlaySound("Ambient\Tavern\glotok_001.wav");
			RemoveDublonsFromPCharTotal(25000);
			pchar.questTemp.ChickenGod.Gold = sti(pchar.questTemp.ChickenGod.Gold) + 25000;
			
			if (sti(pchar.questTemp.ChickenGod.Gold) >= 30000) {
				Achievment_Set("ach_CL_87");
			}
			
			notification("+3 P.I.R.A.T.E.S. point", "None");
			PlaySound("Interface\new_level.wav");
			pchar.skill.FreeSPECIAL = 3;
			pchar.questTemp.ChickenGod.Tasks.o6.Sacrifices = sti(pchar.questTemp.ChickenGod.Tasks.o6.Sacrifices) + 5;
			if (sti(pchar.questTemp.ChickenGod.Tasks.o6.Sacrifices) >= 5) {
				pchar.questTemp.ChickenGod.Tasks.o6.Completed = true;
			}
			
			AddDialogExitQuestFunction("ChickenGod_Respec");
			
			if (ChickenGod_IsDone()) {
				link.l1.go = "joruba_final";
			}
		break;
		
		case "joruba_p4_reward":
			dialog.text = "";
			link.l1 = "끝났어? 이제 내 보상에 대해 얘기하자.";
			link.l1.go = "joruba_p4_reward_1";
		break;
		
		case "joruba_p4_reward_1":
			dialog.text = "운명을 바꾸고 싶을 때는 언제든 내게 말해.";
			link.l1 = "하지만 그게 나한테 정확히 무슨 의미가 있다는 거지?";
			link.l1.go = "joruba_p4_reward_2";
		break;
		
		case "joruba_p4_reward_2":
			dialog.text = "자기 자신을 다스려라! 한 번 해보면 분명 마음에 들 거야. 그동안 다음 거래에 대해 이야기해 주지. 가장 중요한 거래지.";
			link.l1 = "이젠 그럴 가치가 있는지 모르겠어!";
			link.l1.go = "joruba_p4_reward_3";
			link.l2 = "어서 말해, 얼른.";
			link.l2.go = "joruba_p4_reward_3";
		break;
		
		case "joruba_p4_reward_3":
			dialog.text = "그대는 자신의 운명을 바꿀 기회뿐만 아니라, 이 시대의 천재들과 신들과 어깨를 나란히 할 기회도 가졌네. \n그래, 이제는 몸과 마음을 원하는 만큼 바꿀 수 있겠지만, 평범한 자가 모든 면에서 뛰어날 수는 없으니, 결코 자신의 한계를 넘어서진 못할 걸세. \n내가 제안하는 건 바로 그 한계를 깨부수라는 거야.";
			link.l1 = "나한테 뭐가 더 들겠지? 피를 더 흘려야 하나? 아니면 금화를 더 내야 하나?";
			link.l1.go = "joruba_p4_reward_4";
		break;
		
		case "joruba_p4_reward_4":
			dialog.text = "그래. 나한테 2만 5천 두블룬을 가져오든 네 동료 중 한 명을 데려오든 해라. 우리가 끝내고 나면 더 이상 거래는 없다.";
			link.l1 = "생각 좀 해볼게.";
			link.l1.go = "joruba_p4_reward_5";
		break;
		
		case "joruba_p4_reward_5":
			dialog.text = "어디서 나를 찾을 수 있는지 알잖아. 그리고 운명을 바꾸고 싶을 때는 언제든 주저 말고 찾아오게.";
			link.l1 = "";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "joruba_wait";
			
			pchar.questTemp.ChickenGod.Tasks.p4.Completed = true;
			AddDialogExitQuestFunction("ChickenGod_GiveFifthTask");
		break;
		
		case "joruba_respec":
			dialog.text = "원하시는 대로 하겠습니다.";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ChickenGod_Respec");
		break;
		
		case "joruba_o2":
			dialog.text = "우선, 저 사람은 내 아내지 신부가 아니야. 둘째로, 네가 문제 삼는 건 카스티야 놈들이지 내가 아니고. 마지막으로, 나는 이미 그녀를 데려갔고 네 부하들도 내보냈어. 그리고 고상한 의도라니... 나 좀 봐라, 내가 제대로 된 신사의 표본 아니냐? 틀라솔테오틀이여, 저 자도 언젠가 진짜 여자를, 아니면 남자라도 만나게 해주소서.";
			link.l1 = "꺼져라, 아루바!";
			link.l1.go = "exit";
			
			notification("+ 10 HP, + 10 Energy!", "None");
			PlaySound("Interface\new_level.wav");
			ChickenGod_ModifyStats(10.0);
			pchar.questTemp.ChickenGod.Tasks.o2.Completed = true;
			pchar.questTemp.ChickenGod.Tasks.Schyot = sti(pchar.questTemp.ChickenGod.Tasks.Schyot) + 1;
			
			sld = CharacterFromID(pchar.questTemp.ChickenGod.Tasks.o2.Lady);
			RemovePassenger(pchar, sld);
			ChangeCharacterAddressGroup(sld, "Temple", "goto", "goto1");
			LAi_SetCitizenTypeNoGroup(sld);
			
			if (ChickenGod_IsDone()) {
				link.l1.go = "joruba_final";
			}
		break;
		
		case "joruba_o3":
			dialog.text = "나쁘지 않군, 고맙다. 솔직히 말해, 별로 필요는 없지만, 뭐 살롱 같은 데서라도 한 번 써볼까 한다. 이슈타르의 이름으로 그대를 축복하노라. 이제 가서 죄를 지어라.";
			link.l1 = "이상한 기분이군...";
			link.l1.go = "exit";
			
			notification("+ 15 HP, + 15 Energy!", "None");
			PlaySound("Interface\new_level.wav");
			ChickenGod_ModifyStats(15.0);
			pchar.questTemp.ChickenGod.Tasks.o3.Completed = true;
			pchar.questTemp.ChickenGod.Tasks.Schyot = sti(pchar.questTemp.ChickenGod.Tasks.Schyot) + 1;
			
			TakeItemFromCharacter(pchar, "cirass4");
			
			if (ChickenGod_IsDone()) {
				link.l1.go = "joruba_final";
			}
		break;
		
		case "joruba_o4":
			dialog.text = "내가 데려가겠다. 뭐? 나도 자네처럼 죽은 자들이 내 선원으로 필요하지. 다만 자네랑 달리 나는 선원을 선술집에서 모집할 수가 없어. 이제, 바스트여, 이 영웅의 앞날을 축복해 주시길.";
			link.l1 = "이상한 기분이군...";
			link.l1.go = "exit";
			
			notification("+ 15 HP, + 15 Energy!", "None");
			PlaySound("Interface\new_level.wav");
			ChickenGod_ModifyStats(15.0);
			pchar.questTemp.ChickenGod.Tasks.o4.Completed = true;
			pchar.questTemp.ChickenGod.Tasks.Schyot = sti(pchar.questTemp.ChickenGod.Tasks.Schyot) + 1;
			
			if (ChickenGod_IsDone()) {
				link.l1.go = "joruba_final";
			}
			
			AddDialogExitQuestFunction("ChickenGod_RemovePrisoners");
		break;
		
		case "joruba_o5":
			dialog.text = "그래, 또다시 돌을 흩뿌려야겠어. 사람들은 맨날 잃어버리니까, 우리도 손님이 필요하잖아. 프레이야, 이 위대한 돌 수집가를 지켜줘.";
			link.l1 = "이상한 기분이군...";
			link.l1.go = "exit";
			
			TakeNItems(pchar, "talisman11", -113);
			
			notification("+ 15 HP, + 15 Energy!", "None");
			PlaySound("Interface\new_level.wav");
			ChickenGod_ModifyStats(15.0);
			pchar.questTemp.ChickenGod.Tasks.o5.Completed = true;
			pchar.questTemp.ChickenGod.Tasks.Schyot = sti(pchar.questTemp.ChickenGod.Tasks.Schyot) + 1;
			
			if (ChickenGod_IsDone()) {
				link.l1.go = "joruba_final";
			}
		break;
		
		case "joruba_o6":
			dialog.text = "스페인 종교재판단이 오기 전에 빨리 끝내자. 피냐, 금이냐?";
			
			if (PCharDublonsTotal() >= 25000)
			{
				link.money = "Here's your gold, you greedy bastard.";
				link.money.go = "joruba_o6_money";
			}
			
			if (ChickenGod_HaveOfficers())
			{
				link.blood = "Blood.";
				link.blood.go = "joruba_o6_blood";
			}
			link.l3 = "신경 쓰지 마.";
			link.l3.go = "exit";
		break;
		
		case "joruba_o6_blood":
			dialog.text = "이름을 말해.";
			
			ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Duran");
			ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Baker");
			ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Folke");
			ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Avendel");
			ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Tonzag");
			if (!CheckAttribute(pchar, "questTemp.PZ_LongwayNelzyaOtdatArube")) ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Longway");
			ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Knippel");
			ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Tichingitu");
			ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Irons");
			
			if (!CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o6.gf")) {
				ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Helena");
				ChickenGod_AddOfficerLink(link, "joruba_o6_off_", "Mary");
			}
		break;
		
		case "joruba_o6_off":
			if (pchar.questTemp.ChickenGod.Sacrifice == "Mary" || pchar.questTemp.ChickenGod.Sacrifice == "Helena") {
				pchar.questTemp.ChickenGod.Tasks.o6.gf = true;
				sTemp = "future wife";
				sld = CharacterFromID(pchar.questTemp.ChickenGod.Sacrifice);
				if (sld.lastname == pchar.lastname) {
					sTemp = "current wife";
				}
				
				dialog.text = "꽤나 유혹적이지만, 이번 한 번만 예외로 하지. 네 희생은 받지 않겠다. 이 일은 네 \n "+sTemp+", 아마 그래야겠지만 말이야. 그녀 없이는 네가 아무것도 아니라는 걸 명심해. 이제 꺼져, 오늘은 나 귀찮게 하지 마.";
				link.l1 = "";
				link.l1.go = "exit";
				
				AddDialogExitQuestFunction("ChickenGod_KickedFromTemple");
				break;
			}
			if (pchar.questTemp.ChickenGod.Sacrifice == "Duran" && !CheckAttribute(pchar, "questTemp.SKD_DuranDruzhba"))
			{
				dialog.text = "Claude Durand는 장교가 아니라 무자비한 용병이니, 다른 희생자를 고르시오.";
				link.l1 = "";
				link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.ChickenGod.Sacrifice == "Duran" && CheckAttribute(pchar, "questTemp.SKD_DuranDruzhba") && CheckAttribute(pchar, "questTemp.SKD_DevushkaUbita"))
			{
				Achievment_Set("ach_CL_116");
			}
			
			dialog.text = "그러면 그렇게 하시지요. 자, 이 물약을 받으시오 – 내 좋은 친구가 준 선물이오.";
			link.l1 = "맛이 꽤 괜찮은데...";
			link.l1.go = "joruba_o6_reward";
			
			PlaySound("Ambient\Tavern\glotok_001.wav");
			
			ChangeCharacterComplexReputation(pchar, "nobility", -50);
			notification("+3 P.I.R.A.T.E.S. points", "None");
			PlaySound("Interface\new_level.wav");
			pchar.skill.FreeSPECIAL = 3;
			pchar.questTemp.ChickenGod.Tasks.o6.Sacrifices = sti(pchar.questTemp.ChickenGod.Tasks.o6.Sacrifices) + 5;
			if (sti(pchar.questTemp.ChickenGod.Tasks.o6.Sacrifices) >= 5) {
				pchar.questTemp.ChickenGod.Tasks.o6.Completed = true;
			}
			
			AddDialogExitQuestFunction("ChickenGod_KillOfficer");
			AddDialogExitQuestFunction("ChickenGod_Respec");
			
			if (ChickenGod_IsDone()) {
				link.l1.go = "joruba_final";
			}
		break;
		
		case "joruba_o6_reward":
			dialog.text = "다음에 또 뵙지요, 선장님.";
			link.l1 = "";
			link.l1.go = "exit";
			
			pchar.questTemp.ChickenGod.OnExitKick = true;
		break;
		
		case "joruba_final":
			dialog.text = "이봐! 드디어, 이제 다 끝났군!";
			link.l1 = "응?";
			link.l1.go = "joruba_final_1";
		break;
		
		case "joruba_final_1":
			dialog.text = "여기서 할 일은 끝났소, 선장님. 거래는 모두 성사됐고, 모두가 만족했으니 환불 따윈 없소. 우리 사무실은 이제 문을 닫고 다른 곳으로 옮길 거요.";
			link.l1 = "잠깐 기다려, 아루바. 나는 너한테 금도 넉넉히 줬고, 피로 값을 치렀으며, 여자들과 포로들도 이 악마 같은 소굴로 데려왔지. 카리브에서 벌어진다는 초자연적인 일쯤은 감당할 수 있어. 하지만 너와의 '거래'는 도무지 이치에 맞지 않아. 설명 좀 해봐.";
			link.l1.go = "joruba_final_2";
		break;
		
		case "joruba_final_2":
			dialog.text = "있지? 말해 줄게.\n이 세상에 진절머리가 나서 이제 그만두고 싶어. 매일 똑같은 일상이지: 천장이 무너져 내리는 고대 피라미드, 보기만 해도 지긋지긋한 똑같은 야자수들, 그리고 끝도 없이 밀려오는 선장들, 저마다 기발한 생각을 들고 오지. 그래, 나는 사람들이 원하는 걸 제공하지; 그게 내 소명이고, 자부심도 있어. 하지만 맙소사, 너희 모두가 정말 싫다!";
			link.l1 = "누가 너 여기 붙잡아 두고 있냐? 출구 저기 있잖아, 천재야!";
			link.l1.go = "joruba_final_3";
		break;
		
		case "joruba_final_3":
			dialog.text = "네 말이 완전히 맞아, 이제는 아무도 날 붙잡지 않아. 더 이상은 아니야. 이 모든 게 다 너 덕분이야, 친구.";
			link.l1 = "갑자기 마음이 바뀌었군. 나는 뭔가 이야기를 기대했는데, 지금까지 들은 건 먼지 쌓인 피라미드에 있는 비열한 꼬마 신의 의미 없는 헛소리뿐이야.";
			link.l1.go = "joruba_final_4";
		break;
		
		case "joruba_final_4":
			dialog.text = "글쎄, 누구나 가끔은 속을 털어놔야 하지 않겠어? 네가 여기 와줘서 정말 기뻐. 덕분에 이제야 이 세상을 떠날 수 있게 됐으니까. 금, 선원, 장비, 그리고 배, 친구야. 기억나지? 익숙하지 않아? 내가 필요했던 건 그게 전부였고, 넌 그걸 다 마련해줬어.";
			link.l1 = "천만에. 하지만 아직도 네가 이상하게 말하는 이유랑 거의 신에 가까운 힘을 가진 이유는 설명이 안 됐어. 그렇게 전능하다면 진작에 네 배랑 선원, 금까지 다 만들어냈겠지!";
			link.l1.go = "joruba_final_5";
		break;
		
		case "joruba_final_5":
			dialog.text = "내가 그렇게 했지, 보다시피. 누구나 자기만의 방식이 있는 법이야.";
			link.l1 = "아니, 도대체 어떻게 된 거지? 너 대체 누구야?";
			link.l1.go = "joruba_final_6";
		break;
		
		case "joruba_final_6":
			dialog.text = "음... 그게 내가 하는 일이지. 신세계에서 보자, "+GetPersonaName()+". 다음에는 정말 새로운 일이 있기를 바라오. 고맙소, 안녕히 가시오.";
			link.l1 = "아니, 다시는 너를 보고 싶지 않아.";
			link.l1.go = "exit";
			link.l2 = "그럼 또 보자, 아루바... 재미있었어.";
			link.l2.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_FinalGood");
		break;
		
		case "joruba_insult":
			dialog.text = "모든 거래가 끝난 것 같군. 이제 가야지, 선장.";
			link.l1 = "이제 네가 엿이나 먹을 시간이야...";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_Insult");
		break;
		
		case "ChickenGod_TheInquisition_1":
			dialog.text = "스페인 종교재판소의 이름으로, 이름을 대라!";
			link.l1 = "Captain "+GetFullName(pchar)+". 그리고 사람들이 말하는 게 사실이야, 아무도 스페인 종교재판을 예상하지 못하지...";
			link.l1.go = "ChickenGod_TheInquisition_2";
		break;
		
		case "ChickenGod_TheInquisition_2":
			dialog.text = "... 이 농담은 항상 적절하지. 비록 이 농담 때문에 꽤 많은 무고한 그리스도인들이 화형당했지만 말이야.";
			link.l1 = "...";
			link.l1.go = "ChickenGod_TheInquisition_3";
		break;
		
		case "ChickenGod_TheInquisition_3":
			dialog.text = "장난이오, 선장. 당신이 농담했으니 나도 농담한 거요. 내 이름은 에밀리오 보카네그라 신부이고, 이 그리스도의 병사들은 내 무장 경비들이오.";
			link.l1 = "무슨 일로 오셨습니까, 신부님?";
			link.l1.go = "ChickenGod_TheInquisition_4";
		break;
		
		case "ChickenGod_TheInquisition_4":
			dialog.text = "너, 아루바 나리라는 사람 알아?";
			link.l1 = "그래, 그는 최근까지 이 오래된 피라미드에서 살았어.";
			link.l1.go = "ChickenGod_TheInquisition_5";
		break;
		
		case "ChickenGod_TheInquisition_5":
			dialog.text = "거기서 살았다는 게 무슨 말이야? 거기서 사람이 살 수 있나? 그리고 왜 '최근까지'라고 한 거지?";
			link.l1 = "이 나리께서 몇 분 전에 우리를 배에 남겨두고 떠나버렸어.";
			link.l1.go = "ChickenGod_TheInquisition_6";
		break;
		
		case "ChickenGod_TheInquisition_6":
			dialog.text = "그걸 어떻게 아는 거지? 가장 가까운 만까지도 며칠이나 걸린다고!";
			link.l1 = "이 호수는 보기보다 훨씬 큰가 봅니다. 달리 설명할 길이 없군요, 신부님.";
			link.l1.go = "ChickenGod_TheInquisition_7";
		break;
		
		case "ChickenGod_TheInquisition_7":
			dialog.text = "부왕령 땅에서 이상한 일들이 벌어지고 있어.";
			link.l1 = "여기는 영국 땅이오, 신부님.";
			link.l1.go = "ChickenGod_TheInquisition_8";
		break;
		
		case "ChickenGod_TheInquisition_8":
			dialog.text = "이단자들이 그렇게 생각하게 내버려 두시오. 우리는 반드시 되찾을 것이오. 질문이 많았던 것을 용서하거라, 아들아. 산티아고께서 이 피라미드와 그 이전 거주자에 대해 공식 조사를 하라고 내게 지시하셨느니라.";
			link.l1 = "무슨 일이 있었던 겁니까, 신부님?";
			link.l1.go = "ChickenGod_TheInquisition_9";
		break;
		
		case "ChickenGod_TheInquisition_9":
			dialog.text = "사건이 곧 종결될 것 같으니, 작은 이야기를 하나 들려주지.\n이곳에 대한 소문은 한동안 메인 전역에 퍼져 있었네. 이 지역의 역사에 큰 흔적을 남긴 몇몇 인물들이 과거에 이곳을 자주 찾았다는 신뢰할 만한 보고도 받았지.\n하지만 산티아고가 이 소문에 진지하게 주목하기 시작한 건 파나마 사건 이후였네.\n어떤 인디언이 그 영광스러운 도시에서 큰 소동을 일으켰고, 철학적인 설교도 몇 차례 했지. 불행히도 파나마 주민들은 너무 피상적인 결론을 내리고, 이 피라미드에 헤아릴 수 없는 보물이 있고 어떤 소원이든 들어준다고 믿게 되었네.\n이건 순수한 이단이었지... 그래서 우리는 몇몇 파나마 주민들과 그 인디언, 아게바나를 상대로 조사를 시작할 수밖에 없었네.";
			link.l1 = "왜 파나마 당국은 이 일에 대해 단속하지 않았지?";
			link.l1.go = "ChickenGod_TheInquisition_10";
		break;
		
		case "ChickenGod_TheInquisition_10":
			dialog.text = "이런 경우에 늘 그렇듯이, 그들은 자신들이 마법에 걸렸다고 주장했지. 우리가 아게바나를 심문했다면 이 법적 허점은 막을 수 있었겠지만, 그는 갑자기 죽어버렸어.";
			link.l1 = "그가 어떻게 죽었지?";
			link.l1.go = "ChickenGod_TheInquisition_11";
		break;
		
		case "ChickenGod_TheInquisition_11":
			dialog.text = "술에 취해 죽었지. 하지만 그의 죽음으로 우리 문제는 해결되지 않았어. 이단이 군도 전체에 뿌리내렸고, 수백 명이 이 고대 사원으로 일종의 순례를 떠났으니까.";
			link.l1 = "여기서 이렇게 많은 사람들이 모인 건 처음 봐... 그래서 뭐, 아루바를 침공해서 그를 재판에 세우려고 했던 거야?";
			link.l1.go = "ChickenGod_TheInquisition_12";
		break;
		
		case "ChickenGod_TheInquisition_12":
			dialog.text = "물론 아니란다, 아들아. 종교재판소의 심판은 엄격하지만 공정하다. 재판에는 반드시 타당한 이유가 있어야 하지. 아니, 나는 단지 아루바 나리의 증언을 받아 산티아고에 전달하려 했을 뿐이다.";
			link.l1 = "그래, 그거 참 너한테는 불운이군.";
			link.l1.go = "ChickenGod_TheInquisition_13";
		break;
		
		case "ChickenGod_TheInquisition_13":
			dialog.text = "모르는 일이란다, 아들아. 모든 것은 신의 뜻이니라.";
			link.l1 = "안녕히 계십시오, 신부님.";
			link.l1.go = "ChickenGod_TheInquisition_14";
		break;
		
		case "ChickenGod_TheInquisition_14":
			DialogExit();
			
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("Temple", "reload2", false);
			LAi_SetActorType(npchar);
			//LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "ChickenGod_TheInquisitionLeave", -1);
			PChar.quest.ChickenGod_TheInquisitionLeave.win_condition.l1 = "ExitFromLocation";
			PChar.quest.ChickenGod_TheInquisitionLeave.win_condition.l1.location = PChar.location;
			PChar.quest.ChickenGod_TheInquisitionLeave.win_condition = "ChickenGod_TheInquisitionLeave";
		break;
		
	}
} 

void ChickenGod_InitAmmo() {
	if(LoadSegment("items\initItems.c")) {
		InitGunExt(		 "pistol1", "t3", 	 "bullet_double",               "", 100.0, 300.0,    0.0,  0, 0,  20, 0);
		InitGunExt( 	 "pistol2", "t2", "grapeshot_double",               "",  60.0, 160.0,      0.0,  1, 0,  20, 0);
		InitGunExt(		 "pistol3", "t2", "grapeshot_double",               "",  80.0, 180.0,    0.0,  1, 2,  20, 0);
		InitGunExt(		 "pistol4", "t3",    "bullet_double",               "",  70.0, 270.0,     0.0,  0, 0,  30, 0);
		InitGunExt(		 "pistol5", "t3", 	 "bullet_double",               "", 130.0, 330.0,     0.0,  0, 2,  30, 0);
		InitGunExt(		 "pistol6", "t3",    "bullet_double",               "", 100.0, 300.0,     0.0,  0, 0,  20, 0);
		InitGunExt(		 "pistol8", "t4", "grapeshot_double",               "",  50.0, 100.0,    5.0,   1, 0,  20, 0);
		InitGunExt(		 "pistol9", "t3", 	 "bullet_double",               "", 100.0, 320.0,     0.0,  0, 0,  30, 0);
		InitGunExt(		 "pistol10", "t3",   "bullet_double",               "", 140.0, 280.0,    0.0,  0, 0,  30, 0);
		InitGunExt(		 "pistol11", "t3",   "bullet_double",               "",  10.0, 700.0,   40.0,   0, 0, 100, 0);
		InitGunExt(		 "pistol12", "t3",   "bullet_double",               "",  80.0, 290.0,    0.0,   0, 0,  20, 0);
		InitGunExt(		 "pistol13", "t3",   "bullet_double",               "", 130.0, 300.0,  15.0,    0, 0,  30, 0);
		InitGunExt(		 "howdah",  "t3", "grapeshot_double",	            "",  50.0, 140.0,   5.0,    1, 0,  30, 0);
		InitGunExt(		 "pistol14", "t3",   "bullet_double",               "", 130.0, 330.0,   0.0,    0, 4,  34, 0); // Дуэльный двухзарядный пистоль cle 1.3
		
		InitGunExt(		"mushket1", "t3",    "bullet_double",      			"", 240.0, 440.0,  0.0,    0, 0,  20, 0);
		InitGunExt(		"mushket2", "t3", 	 "bullet_double",      			"", 270.0, 470.0,  0.0,    0, 0,  15, 0);
		InitGunExt(		"mushket5", "t3", 	 "bullet_double",      			"", 400.0, 600.0,  15.0,   0, 0,  15, 0);
		InitGunExt(		"mushket7", "t3", 	 "bullet_double",      			"", 300.0, 440.0,   0.0,   0, 0,  18, 0); // Качественный мушкет cle
		InitGunExt(		"mushket8", "t3", 	 "bullet_double",      			"", 200.0, 400.0,  0.0,    0, 0,  20, 0); // Четырехзарядный штуцер cle
		InitGunExt(	  "mushket2x2", "t3", 	 "bullet_double",      			"", 360.0, 560.0,  15.0,   0, 0,  15, 0);
		
		InitGunExt(		"mushket3", "t2", "grapeshot_double",	            "", 140.0, 240.0,    0.0,    1, 0,  13, 0);
		InitGunExt(		"mushket6", "t3", "grapeshot_double",	            "", 180.0, 310.0,  20.0,   1, 0,  15, 0);
		InitGunExt(		"mushket9", "t3", "grapeshot_double",	            "", 140.0, 240.0,   0.0,   1, 0,  23, 0);
		InitGunExt(	  "mushket10",  "t3", 	 "bullet_double",      			"", 360.0, 440.0,   0.0,   0, 0,  21, 0);
		
		UnloadSegment("items\initItems.c");
	}
	
	CGInitGrapeGunExt(	"pistol2",	"t2",		3,		50,		4.25,	5.0,	3);		// трёхствольный дробовик, двойной заряд
	CGInitGrapeGunExt(	"pistol3",	"t2",		4,		40,		6.0,	5.0,	4);		// тромбон, двойной заряд
	CGInitGrapeGunExt(	"pistol8",	"t4",		4,		110,	5.0,	3.0,	2);		// бландербуз, двойной заряд
	CGInitGrapeGunExt(	"howdah",	"t3",		3,		85,		3.0,	5.5,	2);		// гауда, двойной заряд
	CGInitGrapeGunExt(	"mushket3",	"t2",		3,		60,		6.0,	3.0,	3);		// аркебуза, картечь
	CGInitGrapeGunExt(	"mushket6",	"t3",		3,		90,		4.0,	3.5,	2);		// башенный мушкетон, картечь
	
	ref itm;
	
	makeref(itm, items[FindItem("mushket9")]);
	
	itm.type.t3.basedmg  = 3;
	itm.type.t3.shards  = 110;
	itm.type.t3.width   = 8.5;
	itm.type.t3.height  = 7.85;
	itm.type.t3.area    = XI_ConvertString("grapes_area_4");
		
	if(CheckAttribute(itm, "UpgradeStage"))
	{
		int iUpgradeStage = sti(itm.UpgradeStage);
		
		switch (iUpgradeStage)
		{
			case 2:	
				itm.type.t3.basedmg  = 3;
				itm.type.t3.shards  = 120;
				itm.type.t3.width   = 7.0;
				itm.type.t3.height  = 5.75;
				itm.type.t3.area    = XI_ConvertString("grapes_area_4");
			break;
			
			case 3:	
				itm.type.t3.basedmg  = 4;
				itm.type.t3.shards  = 130;
				itm.type.t3.width   = 5.5;
				itm.type.t3.height  = 4.5;
				itm.type.t3.area    = XI_ConvertString("grapes_area_3");
			break;
			
			case 4:	
				itm.type.t3.basedmg  = 5;
				itm.type.t3.shards  = 130;
				itm.type.t3.width   = 4.5;
				itm.type.t3.height  = 3.75;
				itm.type.t3.area    = XI_ConvertString("grapes_area_2");
				itm.type.t3.ChargeSpeed = 18;
			break;
		}
	}
}

void CGInitGrapeGunExt(string id, string sAttr, int basedmg, int shards, float width, float height, int dispersion)
{
	ref gun = ItemsFromID(id);
	gun.type.(sAttr).basedmg = basedmg;
	gun.type.(sAttr).shards = shards;
	string sArea = "grapes_area_"+dispersion;
	gun.type.(sAttr).area = XI_ConvertString(sArea);
	gun.type.(sAttr).width = width;
	gun.type.(sAttr).height = height;
}

bool ChickenGod_FindQuestShips() {
	questShipsNum = 0;
	
	for(int i = 1; i < COMPANION_MAX; i++) {
		int index = GetCompanionIndex(pchar, i);
		if (index < 0) {
			continue;
		}
		
		sld = GetCharacter(index);
		int shipIndex = sti(sld.ship.type);
		if (shipIndex == SHIP_NOTUSED) {
			continue;
		}
		
		ref realShip = GetRealShip(shipIndex);
		if (!CheckAttribute(realShip, "QuestShip")) {
			continue;
		}
		
		if (!GetRemovable(sld) || !GetShipRemovable(sld)) {
			continue;
		}
		
		if (CheckAttribute(pchar, "questTemp.HWIC.TakeQuestShip")) {
			if (sti(realShip.BaseType) == SHIP_MAYFANG || sti(realShip.BaseType) == SHIP_MIRAGE || sti(realShip.BaseType) == SHIP_VALCIRIA) {
				continue;
			}
		}
		
		questShips[questShipsNum] = sti(sld.index);
		questShipsNum++;
	}
	
	return (questShipsNum > 0);
}

void ChickenGod_AddOfficerLink(aref link, string prefix, string id) {
	if (GetCharacterIndex(id) < 0) {
		return;
	}
	
	if (!CheckPassengerInCharacter(pchar, id)) {
		return;
	}
	
	if (id == "Mary" && !CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) {
		return;
	}
	
	if (id == "Helena" && !CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) {
		return;
	}
	
	sld = CharacterFromID(id);
	
	if (!GetRemovable(sld)) {
		return;
	}
	
	link.(id) = GetFullName(sld) + ".";
	link.(id).go = prefix + id;
}

bool ChickenGod_TalkedToAmelia() {
	if (GetCharacterIndex("Amelia") < 0) {
		return false;
	}
	
	sld = CharacterFromID("Amelia");
	if (sld.dialog.currentnode == "amelia") {
		return false;
	}
	
	return true;
}

bool ChickenGod_HaveOfficers() {
	object fakelink;
	
	ChickenGod_AddOfficerLink(&fakelink, "", "Duran");
	ChickenGod_AddOfficerLink(&fakelink, "", "Baker");
	ChickenGod_AddOfficerLink(&fakelink, "", "Folke");
	ChickenGod_AddOfficerLink(&fakelink, "", "Avendel");
	ChickenGod_AddOfficerLink(&fakelink, "", "Tonzag");
	if (!CheckAttribute(pchar, "questTemp.PZ_LongwayNelzyaOtdatArube")) ChickenGod_AddOfficerLink(&fakelink, "", "Longway");
	ChickenGod_AddOfficerLink(&fakelink, "", "Knippel");
	ChickenGod_AddOfficerLink(&fakelink, "", "Tichingitu");
	ChickenGod_AddOfficerLink(&fakelink, "", "Irons");
	
	if (CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o6") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o6.gf")) {
		ChickenGod_AddOfficerLink(&fakelink, "", "Helena");
		ChickenGod_AddOfficerLink(&fakelink, "", "Mary");
	}
	
	return (GetAttributesNum(&fakelink) > 0);
}
