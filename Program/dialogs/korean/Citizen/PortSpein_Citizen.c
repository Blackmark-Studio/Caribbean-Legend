// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
            dialog.text = RandPhraseSimple("무슨 질문인데?","뭐 원하는 거야?");
			link.l1 = RandPhraseSimple("내 마음이 바뀌었어.'","지금은 할 말이 없어.");
		    link.l1.go = "exit";
			//Цена чахотки
			if (!CheckAttribute(npchar, "quest.Consumption") && CheckAttribute(pchar, "questTemp.Consumption.AskJuan"))
			{
				link.l1 = "말해 봐, 'Juan'이라는 이름이 기억나나?";
				link.l1.go = "Consumption";
			}
			if (!CheckAttribute(npchar, "quest.Guardoftruth") && CheckAttribute(pchar, "questTemp.Guardoftruth.Trinidad") && pchar.questTemp.Guardoftruth.Trinidad == "begin")
			{
				link.l1 = "이봐, 친구, 미겔 디초소가 지휘하던 프리깃이 1654년 4월에 이 항구에 정박했었어. 그날 그가 사라졌지. 혹시 그 일에 대해 기억나는 거 있어?";
				link.l1.go = "guardoftruth";
			}
		break;
		
		case "info":
        // заменить на описание неких НПС, по квестам
			dialog.text = "내가 비밀 정보국에서 일한다고 생각하나 "+NationNameGenitive(sti(NPChar.nation))+"?";
			link.l1 = "음... 아니. 그럼, 잘 가.";
			link.l1.go = "exit";
			link.l2 = "다른 질문 있나?";
			link.l2.go = "new question";
		break;
		
		case "town":
        // заменить на описание как пройти, по квестам
			dialog.text = "내가 조사국 직원처럼 보여? 몰라, 아무것도 모른다니까.";

            link.l1 = "너 정말 덜렁이구나! 꺼져.";
			link.l1.go = "exit";
			link.l2 = "다른 질문 있나?";
			link.l2.go = "new question";
		break;
		
		//Цена чахотки
		case "Consumption":
			dialog.text = "농담하는 거야? 식민지마다 후안이 두어 명씩은 꼭 있어!";
			link.l1 = "알겠소. 귀찮게 해서 미안하오...";
			link.l1.go = "exit";
			npchar.quest.Consumption = "true";
		break;
		
		// Страж Истины
		case "guardoftruth":
			dialog.text = LinkRandPhrase("어서요, 선장! 내가 그런 걸 기억할 거라 생각해?","용서하시오, 나리, 그 일은 도와드릴 수 없소.","나리, 내가 그런 쓸데없는 것까지 기억한다고 생각하시오? 나도 이미 골치 아픈 일이 많다네.");
			link.l1 = LinkRandPhrase("알겠소. 괜히 폐를 끼쳐 미안하오...","정말 안타깝군. 안녕히 가시오.","좋아, 잘 가라...");
			link.l1.go = "exit";
			npchar.quest.guardoftruth = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
