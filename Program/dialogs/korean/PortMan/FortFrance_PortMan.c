// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("무슨 질문인데?","무슨 일이오, "+GetAddress_Form(NPChar)+"?"),"이미 나에게 질문을 하려고 했잖아 "+GetAddress_Form(NPChar)+"...","오늘만 벌써 세 번째로 그 질문을 하는군...","봐라, 항구 일에 대해 할 말이 없으면 쓸데없는 질문으로 나를 귀찮게 하지 마라.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("내 마음이 바뀌었소.","나한테 할 말 없어."),"신경 쓰지 마.","정말, 벌써 세 번째군...","미안하지만, 지금은 항구 일에 관심 없어.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//--> Бремя гасконца
		if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "ship" && !CheckAttribute(npchar, "quest.RescueDaughter"))
		{
			DelLandQuestMark(npchar);
			link.l1 = "나리, 저는 일거리를 찾고 있습니다. 하지만 짐꾼 같은 일 말고, 제 신분에 걸맞은 일을 원합니다. 임무나, 봉사, 혹은 민감한 사안이 얽힌 일이라면 무엇이든 좋습니다... 맡기실 일이 있다면 뭐든 받겠습니다.";
			link.l1.go = "Sharlie";
		}
		//<-- Бремя гасконца
		
		// Jason „олго и счастливо
		if (CheckAttribute(pchar, "questTemp.LongHappy") && pchar.questTemp.LongHappy == "portman")
		{
			link.l1 = "저에게 편지가 있다고 들었습니다. 이름은 샤를 드 모르 선장입니다.";
			link.l1.go = "LH_letter";
		}
		//--> Эпилог
		if (CheckAttribute(pchar, "questTemp.SharlieEpilog_PU_Ulysse"))
		{
			link.l1 = "'"+GetShipName("Ulysse")+"'라는 피나스선이 최근 경매에 나왔다고 들었어요. 사실인가요?";
			link.l1.go = "SharlieEpilog_PU_Ulysse_1";
		}
		//<-- Эпилог
		break;
		
		case "Sharlie":
			dialog.text = "도움? 흠. 나는 괜찮네, 하느님께 감사할 일이지. 하지만 내 친구 중 한 명이 정말로 도움이 절실하고, 급한 상황이야. 그 친구가 혼자 정글로 들어가 인디언들과 싸우려 한단 말이야, 이건 완전 미친 짓이야!\n내가 말려보려고 했고, 애원도 했지만 듣질 않더군! 딸 걱정이 너무 커서 자기 목숨까지 내놓을 각오를 하고 있어!";
			link.l1 = "잠깐만, 다시 시작하자. 네 친구가 누구고, 어디서 찾을 수 있으며, 어떤 도움이 필요한 거지?";
			link.l1.go = "Sharlie_1";			
		break;
		
		case "Sharlie_1":
			dialog.text = "아, 미안하오, 내가 너무 불안해서 그랬소. 그의 이름은 프로스페르... 프로스페르 트루발이오. 그는 분명히 죽고 말 거요! 나는 도와줄 수 없소 - 나는 군인이 아니니까. 그의 딸이 사라졌고, 그는 이 지역 인디언들이 책임이 있다고 믿고 있소.\n생각해 보시오, 그가 혼자서 저 야만인들을 쫓아가려 한다니! 그 자들이 그를 산산조각 낼 거요... 지금 그는 머스킷을 사고 정글로 나갈 준비를 하고 있소!";
			link.l1 = "넌 형편없는 이야기꾼이구나, 이봐. 네 친구는 어디 있지... 이름이 뭐였더라... 프로스페르?";
			link.l1.go = "Sharlie_2";			
		break;
		
		case "Sharlie_2":
			dialog.text = "방금 그와 얘기하면서 마음을 바꿔보라고 했어. 그는 지금 성문에서 멀지 않은 우물가에서 머스킷과 탄약을 점검하고 있지. 어서 그에게 가서 뭔가 해 봐! 그가 혼자 정글로 들어가면 돌아오지 못할 거야, 분명해. 붉은 피부의 악마들이 그를 갈기갈기 찢어버릴 테니까...";
			link.l1 = "쓸데없는 소리 그만해, 늙은 여자처럼 군다! 네 친구한테 바로 갈 거야. 내가 그를 도울 수 있길 바란다.";
			link.l1.go = "Sharlie_3";			
		break;
		
		case "Sharlie_3":
			DialogExit();
			AddQuestRecord("SharlieF", "1");
			RescueDaughter_CreateProsper();
			npchar.quest.RescueDaughter = "true";
			QuestPointerDelLoc("fortfrance_town", "reload", "reload10_back");
		break;
		
		// Jason „олго и счастливо
		case "LH_letter":
			dialog.text = "네, 맞아요 - 봉투가 있습니다. 여기 있습니다만, 먼저 배달비로 은화 만이천 페소를 지불하셔야 합니다.";
			if (sti(pchar.money) >= 12000)
			{
				link.l1 = "나는 항상 자네 장사가 원래 도둑질에서 시작된 거라 의심했었네만, 어쩐지 빗나갔군, 흠. 자, 여기 자네 돈이네.";
				link.l1.go = "LH_letter_1";
			}
			else
			{
				link.l1 = "조금 있다가 다시 오겠소, 내 돈주머니를 선술집에 두고 온 것 같아서.";
				link.l1.go = "exit";
			}
		break;
		
		case "LH_letter_1":
			DialogExit();
			AddMoneyToCharacter(pchar, -12000);
			LongHappy_RecibeLetter();
		break;
		
		//--> Эпилог
		case "SharlieEpilog_PU_Ulysse_1":
			dialog.text = "맞아요. 배의 주인이 보험 빚에 허덕이다가 선박을 경매에 내놨어요. 하지만 조금 늦으셨어요 — 이미 경매는 끝났고, 새 소유자가 서류 작업 중이에요.";
			link.l1 = "그 사람을 어디서 찾을 수 있을까요? 꼭 만나야 해요.";
			link.l1.go = "SharlieEpilog_PU_Ulysse_2";
			DelLandQuestMark(npchar);
			SharlieEpilog_SpawnPikar();
		break;
		
		case "SharlieEpilog_PU_Ulysse_2":
			dialog.text = "찾을 필요 없어요. 뒤를 보세요 — 바로 당신 뒤에 있어요.";
			link.l1 = "...";
			link.l1.go = "exit";			
		break;
		//<-- Эпилог
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
