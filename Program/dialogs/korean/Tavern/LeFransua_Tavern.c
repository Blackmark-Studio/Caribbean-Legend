// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("무슨 질문이 있소?","무엇을 도와드릴까요, "+GetAddress_Form(NPChar)+"?"),"얼마 전에 나한테 뭔가 물어보려고 했었지, "+GetAddress_Form(NPChar)+"...","오늘 하루 동안, 그 질문을 네가 벌써 세 번째 꺼내는구나...","또 질문이 있나 보군?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("내 마음이 바뀌었어...","지금은 할 말이 없어."),"으음, 내 기억이 다 어디로 갔지...","그래, 정말로 이번이 세 번째야...","아니, 무슨 질문이야?…",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";						
			//Jason, Бремя гасконца
			if (CheckAttribute(PChar, "questTemp.Sharlie.Storehelper") && pchar.questTemp.Sharlie.Storehelper == "hire" && !CheckAttribute(npchar, "quest.storehelper"))
			{
				link.l1 = "들어봐, "+npchar.name+", 오늘은 좀 특이한 일로 왔소. 생피에르 상점에서 상인의 조수로 일하면서 만만하고 평화로운 삶을 원하는 사람을 찾고 있소. 급여도 좋고 머물 집도 제공된다오. 혹시 내가 누구에게 물어봐야 할지 추천해줄 수 있겠소?";
				link.l1.go = "storehelper";
			}
			if (CheckAttribute(PChar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "seabattle" && !CheckAttribute(npchar, "quest.seabattle") && pchar.location.from_sea == "LeFransua_town")
			{
				link.l1 = "내가 여기 온 건 곧 내 배에 실어 과들루프까지 운송할 와인 통들 때문이야...";
				link.l1.go = "seabattle";
			}
			//Бремя гасконца
			//Jason, Португалец
			if (CheckAttribute(PChar, "questTemp.Portugal") && pchar.questTemp.Portugal == "PortugalLeFransua" && !CheckAttribute(npchar, "quest.portugal") && Pchar.location.from_sea == "LeFransua_town")
			{
				link.l1 = "있잖아, "+npchar.name+", 내 친구를 찾고 있어. 여기 도착하기로 했는데 몸이 안 좋았거든. 아마 친구들이 도와줬을지도...";
				link.l1.go = "Portugal";
			}
			//Португалец
		break;
		
		case "storehelper":
			dialog.text = "흠... 여기 뱃사람 생활을 그만두고 뭍사람이 되고 싶어하는 이들이 몇 명 있지. 내가 도와줄 수는 있지만, 미리 말해두겠네. 공짜는 아니야.";
			link.l1 = "헤! 그래서 얼마나 원하는 거야?";
			link.l1.go = "storehelper_1";
		break;
		
		case "storehelper_1":
			dialog.text = "천 피스의 에잇. 자네가 할 일은 아무것도 없어; 한 시간 안에 내 선술집에 일할 후보들이 올 거야—여럿이 말이지. 자네는 그들과 직접 이야기해 보고, 마음에 드는 사람을 고르면 돼.";
			if (sti(Pchar.money) >= 1000)
			{
				link.l1 = "아... 알겠다, 여기, 천 닢 가져가!";
				link.l1.go = "storehelper_2";
			}
			link.l2 = "미안하지만, 나한텐 그만한 돈이 없어!";
			link.l2.go = "storehelper_exit";
		break;
		
		case "storehelper_2":
			AddMoneyToCharacter(pchar, -1000);
			dialog.text = "걱정 마, 친구. 이 금액의 절반은 후보한테서 돌려받게 될 거야. 네가 한 일에 대한 대가라고 내가 말해줄 테니, 헤헤... 오백 이상은 절대 안 줘. 한 시간 뒤에 내 선술집에 들러. 그때쯤이면 네가 필요한 사람들을 기다리게 해둘 테니까.";
			link.l1 = "좋아. 한 시간 후에 돌아올게, "+npchar.name+".";
			link.l1.go = "storehelper_3";
			npchar.quest.storehelper = "true";
			DelLandQuestMark(npchar);
		break;
		
		case "storehelper_3":
			DialogExit();
			SetLaunchFrameFormParam("One hour passed...", "", 0, 5);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 0); //крутим время
			RecalculateJumpTable();
			Storehelper_hire("");
		break;
		
		case "storehelper_exit":
			dialog.text = "그런 돈도 없으시다니 유감이오. 하지만 알다시피, 그런 일은 단순히 '고맙다'고 해서 되는 게 아니지. 그러니...";
			link.l1 = "알겠어. 하지만 정말 돈이 없어. 좋아, 그럼 잘 가...";
			link.l1.go = "exit";
			//pchar.quest.storehelper.over = "yes";
			//AddTimeToCurrent(2,0);
			//DeleteAttribute(pchar, "questTemp.Sharlie.Storehelper");
			//CloseQuestHeader("SharlieA");
		break;
		
		case "seabattle":
			DelLandQuestMark(npchar);
			dialog.text = "무슨 소리야, 이봐? 무슨 와인 얘기하는 거지?";
			link.l1 = "월터 캐처라는 사람이 나를 당신에게 보냈소. 그 사람이 말하길, 당신이 와인 화물을 과들루프로 운송할 배가 필요하고, 보수는 만 페소라 하더군. 그리고 이 일에는 바로 내 배가 꼭 필요하다고도 했소...";
			link.l1.go = "seabattle_1";
			npchar.quest.seabattle = "true";
		break;
		
		case "seabattle_1":
			dialog.text = "이봐, 나는 와인 장사 안 해, 네 서비스도 필요 없어, 그리고 Walter Catcher라는 사람도 몰라.";
			link.l1 = "이런! 그럼 그 캐처는 네가 보낸 게 아니었군... 그럼, 이게 다 무슨 소동이란 말이냐?";
			link.l1.go = "seabattle_2";
		break;
		
		case "seabattle_2":
			dialog.text = "헤! 글쎄, 이건 뭔가 착오이거나 형편없는 농담이거나, 아니면...";
			link.l1 = "아니면 뭐?";
			link.l1.go = "seabattle_3";
		break;
		
		case "seabattle_3":
			dialog.text = "스스로 눈치 못 채겠어? 누군가 널 르 프랑수아로 유인할 필요가 있었던 거지, 이유는 나도 모르겠지만. 내가 너라면 당장이라도 온갖 조심 다 하면서 여기서 빠져나가겠어. 이거, 뭔가 수상한 냄새가 나, 친구...\n";
			link.l1 = "네 말이 맞는 것 같아. 나도 그 캐처라는 녀석 얼굴이 마음에 안 들었거든. 좋아, 네 조언을 따르지. 잘 있어, 세자르!";
			link.l1.go = "seabattle_4";
		break;
		
		case "seabattle_4":
			DialogExit();
			AddQuestRecord("Sharlie", "16");
			pchar.quest.seabattle.win_condition.l1 = "location";
			pchar.quest.seabattle.win_condition.l1.location = "Martinique";
			pchar.quest.seabattle.function = "SharlieSeabattle_ship";
			
			pchar.quest.NewGameTip4.win_condition.l1 = "location";
			pchar.quest.NewGameTip4.win_condition.l1.location = "LeFransua_town";
			pchar.quest.NewGameTip4.function = "ShowNewGameTip";
			pchar.quest.NewGameTip4.text = "Your first sea battle is coming! Save you game!";					  
		break;
		
		case "Portugal":
			dialog.text = "그래, 네 친구 여기 왔어, 선장. 어제 도착해서 위층 방을 빌렸지. 그 동료들도 같이 왔고, 헤헤... 저기 앉아 있어. 가서 물어봐!";
			link.l1 = "...";
			link.l1.go = "Portugal_1";
		break;
		
		case "Portugal_1":
			DialogExit();
			AddDialogExitQuestFunction("Portugal_enterPirates");
			npchar.quest.portugal = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
