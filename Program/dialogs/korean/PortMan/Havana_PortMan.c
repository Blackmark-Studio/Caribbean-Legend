// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("무슨 질문인데?","무슨 일이오, "+GetAddress_Form(NPChar)+"?"),"이미 나에게 질문을 하려고 했잖아 "+GetAddress_Form(NPChar)+"...","오늘만 세 번째로 이 질문을 꺼내는군...","이봐, 항구 일에 대해 할 말이 없으면 쓸데없는 질문으로 귀찮게 하지 마라.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("내 마음이 바뀌었소.","나랑 할 얘기는 없어."),"신경 쓰지 마시오.","정말, 벌써 세 번째군...","미안하지만, 지금은 항구 일에 관심 없어.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.Slavetrader == "FindRatHavana")
            {
                link.l1 = "좋은 하루입니다. '라는 이름의 코르벳에 대해 알고 싶습니다."+pchar.questTemp.Slavetrader.ShipName+"' 프랑수아 곤티에르의 지휘 아래.";
                link.l1.go = "Havana_ratP_1";
			}
			// калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "graveyard" && !CheckAttribute(npchar, "quest.caleuche"))
			{
				link.l1 = "실례합니다만, Joachim Merriman이라는 이름의 남자가 이 항구에 도착했습니까? 중년의 나리인데, 포르투갈 사람이고, 콧수염과 염소수염이 있으며, 눈빛이 날카로운 자입니다?";
				link.l1.go = "caleuche";
			}
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "jewelry_3" && !CheckAttribute(npchar, "quest.Mtraxx"))
			{
				link.l1 = "나는 'Cantavro'라는 배에 관심이 있소. 그 배의 선장인 에스베르도 카바냐스를 개인적인 일로 찾고 있소. 도와줄 수 있겠소?";
				link.l1.go = "mtraxx";
			}
		break;
		
		case "Havana_ratP_1":
			dialog.text = NPCStringReactionRepeat("네, 그가 여기 있었소. 하지만 이미 떠났소. 그에 대해선 우리 선술집 주인에게 물어보시오, 위층에 방을 빌렸으니.","이것에 대해 이미 물었고 내가 대답했소.","이미 말했잖아, 이 곤티에르에 대해서는 벌써 물어봤다고..","나를 귀찮게 하지 말아 주시오!","block",0,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("고맙소. 그렇게 하겠소.","흠, 그래 ...","그래, 내가 정말로 요청했지 ...","실례합니다, "+npchar.name+"...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
		
		// калеуче
		case "caleuche":
			dialog.text = "그에 대해선 아무것도 말해줄 수 없소. 설령 도착했다 해도, 어디에도 등록하지 않았소.";
			link.l1 = "알겠소. 참 안타깝군... 좋아, 계속 찾아보겠소...";
			link.l1.go = "exit";
			npchar.quest.caleuche = "true";
		break;
		
		// Addon 2016-1 Jason пиратская линейка
		case "mtraxx":
			dialog.text = "어디 보자... '칸타브로' 스쿠너는 이틀 전에 순찰을 나갔네... 하지만 위치는 기록되어 있지 않네. 군함이니 목적지는 선장과 요새 사령관만이 알고 있지. 더 알고 싶다면 직접 사령관과 이야기해 보게. 요새에 가면 만날 수 있을 걸세. 유감이지만 내가 도와줄 수 있는 건 여기까지일세.";
			link.l1 = "알겠습니다. 시간 내주셔서 감사합니다...";
			link.l1.go = "exit";
			npchar.quest.Mtraxx = "true";
			AddQuestRecord("Roger_1", "5");
			DelLandQuestMark(npchar);
			AddLandQuestMark(characterFromId("Havana_tavernkeeper"), "questmarkmain");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
