// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("어서 말해라, 무엇을 원하는가?","우리가 방금 그 얘기를 하고 있었소. 당신이 잊은 모양이군...","오늘만 세 번째로 뭔가를 또 물어보시는군요...","이봐, 여긴 상점이야. 사람들은 여기서 물건을 산다네. 방해하지 말게!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("있잖아, "+NPChar.name+", 아마 다음번에.","맞아요, 무슨 이유에선지 내가 잊고 있었군요...","그래, 정말로 이번이 세 번째야...","흠, 나는 안 하겠어...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "graveyard" && !CheckAttribute(npchar, "quest.caleuche"))
			{
				link.l1 = "이봐, 혹시 조아킴 메리만이라는 이름의 남자가 네 가게에 온 적 있나? 중년의 나리인데, 포르투갈 사람이고, 콧수염과 엠페러드 수염에 눈빛이 날카로운 사람이야. 혹시 뭔가를 사간 적 있나?";
				link.l1.go = "caleuche";
			}
		break;
		
		// калеуче
		case "caleuche":
			dialog.text = "아니오, 제 손님들 중에 당신이 말한 사람과 비슷한 이는 없습니다. 그리고 그 이름도 처음 듣는군요. 미안하지만 더 이상 도와드릴 수 없겠소.";
			link.l1 = "알겠소. 유감이군. 그럼, 계속 찾아보겠소...";
			link.l1.go = "exit";
			npchar.quest.caleuche = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}
