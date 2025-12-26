// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("모든 소문이 "+GetCityName(npchar.city)+" 항상 대기 중이오. 무엇을 알고 싶으시오?","우리가 방금 그 얘기하고 있었잖아. 너 잊어버린 거 아냐...","오늘만 벌써 세 번째로 나한테 묻는군...","앵무새처럼 똑같은 말만 반복하네...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("있잖아, "+NPChar.name+", 다음에 하자.","그래, 뭔가 이유가 있었는지 내가 잊어버렸군...","그래, 정말로 이번이 세 번째야...","그래...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// Страж Истины
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "merdok" && !CheckAttribute(npchar, "quest.jino"))
			{
				link.l1 = "이봐, 이 마을에 연금술사가 온 적 있나, 의사 말이야? 이탈리아인이고, 나이는 서른쯤, 이름은 지노 그비네일리라고 하는데?";
				link.l1.go = "guardoftruth";
			}
			// Калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "hunting" && !CheckAttribute(npchar, "quest.Caleuche"))
			{
				link.l1 = "이봐, 퍼거스 후퍼라는 사냥꾼을 찾아야 해. 여기 산다고 들었는데, 어디서 그를 찾을 수 있지?";
				link.l1.go = "caleuche";
				DelLandQuestMark(npchar);
			}
			//--> Дикая Роза
			if (CheckAttribute(pchar, "questTemp.WildRose_Etap6_Beliz"))
			{
				link.l1 = "약 한 달 반 전에 제롬 소브르니에라는 자가 당신네 마을에 왔었지. 기억나오?";
				link.l1.go = "WildRose_Tavern_1";
			}
			//<-- Дикая Роза
		break;
		
		case "guardoftruth":
			dialog.text = LinkRandPhrase("아니, 못 봤어. 약초사랑 의원들은 있지만, 그 이름을 가진 사람은 없어.","이렇게 이상한 이름은 처음 들어보네. 아니, 네가 말한 그 남자가 우리를 찾아온 적은 한 번도 없어.","우리에겐 연금술사는 전혀 없어. 의사는 있지만, 그런 이름을 가진 사람은 없어.");
			link.l1 = "알겠어. 아쉽군. 계속 찾아볼게!";
			link.l1.go = "exit";
			npchar.quest.jino = "true";
		break;
		
		// Калеуче
		case "caleuche":
			dialog.text = "퍼거스? 자주 내 집에 들르지. 그런데 어제부터 셀바에 가 있어. 걱정 마, 일주일이면 돌아와서 럼주 마시며 바다에서 겪은 일을 자랑할 거야. 인정하자면, 그 녀석 사냥 솜씨는 끝내주지. 저렇게 뱀을 잘 잡는 사람은 본 적이 없어.";
			link.l1 = "뱀들이라고? 흠. 그를 찾으려면 언제 다시 여기로 오면 되지?";
			link.l1.go = "caleuche_1";
		break;
		
		case "caleuche_1":
			dialog.text = "최소한 사흘은 걸릴 거야. 참고로 그 사람은 항상 저녁 여섯 시 이전에는 여기 오지 않고, 열 시 넘기기 전에 떠나.";
			link.l1 = "어떻게 생겼지? 전에 본 적 없어.";
			link.l1.go = "caleuche_2";
		break;
		
		case "caleuche_2":
			dialog.text = "수염이 있고, 중년이며, 갈색 코트와 모자, 긴 부츠를 신었다.";
			link.l1 = "고마워! 정말 많은 도움이 됐어, 친구. 또 보자!";
			link.l1.go = "caleuche_3";
		break;
		
		case "caleuche_3":
			DialogExit();
			AddQuestRecord("Caleuche", "8");
			int iTerms = sti(pchar.questTemp.Caleuche.Belizterms);
			SetFunctionTimerCondition("Caleuche_FergusCome", 0, 0, iTerms, false);
			npchar.quest.Caleuche = "true";
		break;
		
		//--> Дикая Роза
		case "WildRose_Tavern_1":
			dialog.text = "어... 그런 것 같아. 그래, 그 신사를 기억해. 옷차림은 번듯하지 않았지만 돈은 있었지.";
			link.l1 = "네 술집에서 싸움이 벌어졌을 때 그가 다쳤어.";
			link.l1.go = "WildRose_Tavern_2";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Tavern_2":
			dialog.text = "그래서 뭐 어쩌라고? 여기선 하루가 멀다 하고 싸움이 벌어지지. 선원들이 술에 취해 말다툼하다가, 그다음엔 말려도 소용없어. 너처럼 노련해 보이는 사람이 이런 일에 놀랄 리 없잖아?";
			link.l1 = "전혀 아닙니다. 사실 이 사람은 제 오랜 지인입니다. 여기서 만나기로 했는데 제가 좀 늦었어요. 혹시 어디서 그를 찾을 수 있는지 알려주실 수 있습니까?";
			link.l1.go = "WildRose_Tavern_3";
		break;

		case "WildRose_Tavern_3":
			dialog.text = "왜 말하지 말아야 하오, 나리? 내가 말했듯이, 그는 돈이 충분했소 – 그래서 항만청 근처에 집을 빌렸지. 눈에 띄는 집이오, 빨간 지붕이 있소. 거기 틀어박혀서 다리나 고치며 거의 나오지 않소. 가끔씩 여기 와서 한잔하긴 하오. 하지만 확실하진 않소 – 올 때도 있고, 안 올 때도 있지.";
			link.l1 = "그럼 그의 집으로 직접 찾아가겠소. 정보 고맙소. 안녕히 계시오.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_3_tavern");
		break;
		//<-- Дикая Роза

	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
