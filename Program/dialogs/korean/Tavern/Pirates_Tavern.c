// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("무슨 질문이 있소?","무엇을 도와드릴까요, "+GetAddress_Form(NPChar)+"?"),"얼마 전에 나한테 뭔가 물어보려고 했었지, "+GetAddress_Form(NPChar)+"...","오늘 하루 동안만 해도, 이 질문을 세 번째로 꺼내는군...","또 질문이 있나 보군?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("내 마음이 바뀌었어...","지금은 할 말이 없어."),"으음, 내 기억이 다 어디로 갔지...","그래, 정말로 이번이 세 번째야...","아니, 무슨 질문이야?…",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (CheckAttribute(PChar, "questTemp.Guardoftruth.Archy") && pchar.questTemp.Guardoftruth.Archy == "islatesorotavern")
			{
				link.l1 = "들어봐, "+npchar.name+", 미겔 디초소라는 남자에 대해 들어본 적 있나? 그의 배가 이슬라 테소로 근해에서 목격됐다고 하던데...";
				link.l1.go = "guardoftruth";
			}
			if(CheckAttribute(pchar, "questTemp.Tieyasal") && pchar.questTemp.Tieyasal == "begin" && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				link.l1 = "들어봐, "+npchar.name+", 요즘 Isla Tesoro 근처에서 Miguel Dichoso를 본 적 없나?";
				link.l1.go = "tieyasal";
			}
		break;
		
		case "guardoftruth":
			dialog.text = "그래, 있지. 그 스페인 돈이 샤크 도드슨에게 대단한 배, 즉 프리깃함을 팔았어, 그가 아직 여기 살 때 말이야. 아, 그 배... 정말 굉장했지...";
			link.l1 = "짐작해보지. 현대적이고 날렵한 선체에 열여섯 노트까지 낼 수 있었겠지? 그리고 이름은 '산타 키타리아'였나?";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "뼈대와 속도에 대해서는 네 말이 맞아. 하지만 그 배의 이름은 달랐지. '산 마르틴'이었어. 상어가 그 배를 그 악당에게서 사려고 금을 한 무더기나 줬지.";
			link.l1 = "정말로 '산 마르틴'이었고 '산타 키테리아'가 아니었어? 언제 그 배를 샀지? 그리고 왜 디초소를 악당이라고 불렀어?";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "빌어먹을, 내 두 눈을 걸고 맹세하는데 그건 분명히 '산 마르틴'이었어. 내가 직접 알렉서스 놈들이 선미에서 그 가톨릭 잡동사니가 적힌 명판을 뜯어내는 걸 봤거든. 샤크 돗슨이 그 배 이름을 '포춘'으로 바꿨지. 그런 미녀한테 훨씬 잘 어울리는 이름이야. (침을 뱉는다) 그 녀석이 '54년 겨울에 그 배를 샀어. 블레이즈가 살해당하기 얼마 전이었지\n왜 내가 돈 미겔을 악당이라고 불렀냐고? 그 자식이 그 빌어먹을 배를 프로비던스에서 스페인 해군한테서 훔쳤거든! 돗슨이 산 후안 요새랑 주둔군을 속이려고 불과 연기로 한바탕 쇼를 벌였지. 그 녀석이 술만 마시면 늘 내게 자랑하던 얘기야. 샤크는 손상된 러거 두 척을 희생해서 프리깃과의 싸움이 진짜처럼 보이게 만들었지\n밤이 되자 샤크는 몰래 '산 마르틴'을 이슬라 테소로로 끌고 갔어. 샤크는 배를 얻고, 디초소는 돈을 챙겼지. 그 교활한 놈이 나중에 상관들한테 프리깃이 해적 함대와 싸우다 침몰했다고 둘러댔고, 산 후안 요새 사령관도 그 말을 확인해줬다네.";
			link.l1 = "오, 저 스페인 돈들은 정말 주머니를 두둑이 채우는구나! 완전 교활한 녀석이지! 그런데, 정말 그 일이 1654년 겨울에 일어난 게 확실해? 혹시 봄에 있었던 건 아니야? 그리고 그 프리깃함, 폭풍 때문에 닳고 해진 흔적은 없었어?";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "분명 겨울이었던 것 같은데... 아, 누가 알겠어. 어쩌면 봄이었을지도. 정확히 기억은 안 나. 아마 취해 있었을 거야. 프리깃은 전혀 낡지 않았고, 완전히 새 배였지.";
			link.l1 = "그 멋진 프리깃은 지금 어디에 있지?";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			dialog.text = "어두운 이야기지... 블레이즈가 살해당했을 때, 모두가 샤크를 의심했어. 그의 목걸이, 상어 이빨이 시신에서 발견됐거든. 게다가, 그날 밤 샤크가 블레이즈 집에 있는 걸 본 사람도 있었지\n샤크는 검은 표식을 받기 전에 이슬라 테소로에서 도망쳤어. 다크 파스터를 찾아가서 자기 프리깃을 브리그로 바꿨지. 그 자가 지금 어디 있는지는 아무도 몰라. 자커리가 그 프리깃을 나중에 윌리엄 패터슨에게 팔았어.";
			link.l1 = "이 패터슨이 누구지?";
			link.l1.go = "guardoftruth_5";
		break;
		
		case "guardoftruth_5":
			dialog.text = "뭐야, 윌리 패터슨을 들어본 적도 없다고? 그 녀석은 스코틀랜드 놈인데, 이제 막 카리브에 도착했지. 자기가 왕립 함대의 선장이라도 되는 양 굴더군, 폭스 대령이 아주 아끼는 놈이야! 그런데 말인데, 그 자식이 잭맨하고도 거래를 시작했더라고. 패터슨의 기함은 바로 '포춘'이야.";
			link.l1 = "알겠소. 지금 디초소가 어디에 있는지 아시오?";
			link.l1.go = "guardoftruth_6";
		break;
		
		case "guardoftruth_6":
			dialog.text = "나도 전혀 모르겠어. '포춘' 사건 이후로는 그를 이슬라 테소로에서 본 적도 없고, 그에 대한 소문도 들은 게 없어.";
			link.l1 = "좋아, "+npchar.name+", 자세한 정보 고마워! 너 정말 훌륭한 주점 주인이구나! 너 같은 사람이 더 많았으면 좋겠어... 잘 있어!";
			link.l1.go = "guardoftruth_7";
		break;
		
		case "guardoftruth_7":
			dialog.text = "행운을 빌어, "+pchar.name+"!";
			link.l1 = "...";
			link.l1.go = "guardoftruth_8";
		break;
		
		case "guardoftruth_8":
			DialogExit();
			AddQuestRecord("Guardoftruth", "60_1");
			pchar.questTemp.Guardoftruth.Archy = "guadeloupe";
			// маленькая развлекуха
			pchar.quest.GuardOT_cabinattack.win_condition.l1 = "EnterToSea";
			pchar.quest.GuardOT_cabinattack.function = "GuardOT_PrepareCreateBandosInCabin";
		break;
		
		case "tieyasal":
			dialog.text = "둘 다 서로 쫓고 있는 것 같군, 친구. 그래, Dichoso가 여기 있었어, 바로 네가 서 있는 그 자리에서 말이야. 그리고 똑같이, 네가 Sharptown에 마지막으로 왔을 때 그 녀석도 너에 대해 물었지.";
			link.l1 = "젠장! 그게 소식이란 말이지... 그런데 미겔은 지금 어디에 있지?";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "나도 모르겠어. 그는 바다로 나갔지... 블루웰드에 대해 뭐라 했던 것 같아. 아마 널 찾으려고 거기로 간 거겠지.";
			link.l1 = "네가 그를 블루웰드로 보낸 놈이냐?";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			dialog.text = "아니. 내가 그에게 말한 건 너를 오랫동안 못 봤다는 것뿐이야.";
			link.l1 = "알겠어. 좋아, 그럼. 고마워, 친구!";
			link.l1.go = "tieyasal_3";
		break;
		
		case "tieyasal_3":
			DialogExit();
			AddQuestRecord("Tieyasal", "3");
			npchar.quest.tieyasal = "true";
			pchar.quest.Tieyasal_ITAttack.win_condition.l1 = "location";
			pchar.quest.Tieyasal_ITAttack.win_condition.l1.location = "Bermudes";
			pchar.quest.Tieyasal_ITAttack.function = "Tieyasal_CreateITShips";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
