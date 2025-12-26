// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = RandPhraseSimple("무슨 질문인데?","뭐 원하는 거야?");
			link.l1 = RandPhraseSimple("내 마음이 바뀌었어.'","지금은 할 말이 없어.");
			link.l1.go = "exit";
			//Бремя гасконца
			if (CheckAttribute(pchar, "questTemp.Sharlie.Citcount") && !CheckAttribute(npchar, "quest.Sharlie"))
			{
				link.l1 = "실례합니다, "+GetAddress_FormToNPC(NPChar)+" 미셸 드 몽페르가 어디에 있는지 알려줄 수 있나? 이 마을에 있다고 들었거든.";
				link.l1.go = "Sharlie";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "findskiper" && !CheckAttribute(npchar, "quest.Sharlie1"))
			{
				link.l1 = "이봐, "+GetAddress_FormToNPC(NPChar)+", 너한테 물어볼 게 있어... 내 배에서 일할 항해사를 찾고 있는데, 아는 사람 있어?";
				link.l1.go = "Sharlie_1";
			}
			//Бремя гасконца
		break;
		
		case "info":
        // заменить на описание неких НПС, по квестам
			dialog.text = "내가 혹시 비밀 정보국에서 일한다고 생각하나 "+NationNameGenitive(sti(NPChar.nation))+"?";
			link.l1 = "음... 아니. 그럼 이만.";
			link.l1.go = "exit";
			link.l2 = "다른 질문 있나?";
			link.l2.go = "new question";
		break;
		
		case "town":
        // заменить на описание как пройти, по квестам
			dialog.text = "내가 무슨 조사국 직원처럼 보여? 몰라, 아무것도 모른다니까.";

            link.l1 = "너 정말 덜렁이구나! 썩 꺼져.";
			link.l1.go = "exit";
			link.l2 = "그럼, 다른 질문 있나?";
			link.l2.go = "new question";
		break;
		
		//--> Бремя гасконца
		case "Sharlie":
			if (sti(pchar.questTemp.Sharlie.Citcount) == 3)
			{
				dialog.text = "흠... 네가 이런 질문을 겁도 없이 하는 걸 보니, 막 도착한 모양이군... 괜히 문제 생기기 싫으면 그만두는 게 좋을 거다. 수도원장에게 가 봐라. '정신 차릴' 수 있게 도와줄지도 모르지. 교회에 가면 만날 수 있을 거다.";
				link.l1 = "그렇군...";
				link.l1.go = "exit";
				AddDialogExitQuest("Sharlie_SetBenua");
				DelLandQuestMark(characterFromId("FortFrance_Mayor"));
			}
			else
			{
				dialog.text = LinkRandPhrase("아니, 그 사람에 대해 들어본 적 없어.","도와줄 수 없어, 할 일이 있거든.","누구? 기억 안 나는데. 난 이만 간다.");
				link.l1 = "알겠소... 그럼 이만 가보겠소. ";
				link.l1.go = "exit";
				npchar.quest.Sharlie = "true";
			}
		break;
		
		case "Sharlie_1":
			dialog.text = LinkRandPhrase("아니, 나는 항해사를 전혀 모른다.","나는 할 일이 있어서 안 돼, 다른 사람한테 물어봐...","유감이지만, 나는 도와줄 수 없어. 아는 사람이 없어.");
			link.l1 = "알겠어. 그럼 다른 데 가서 물어볼게.";
			link.l1.go = "exit";
			npchar.quest.Sharlie1 = "true";
			npchar.dialog.currentnode = "first time";
		break;
		//<-- Бремя Гасконца
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
