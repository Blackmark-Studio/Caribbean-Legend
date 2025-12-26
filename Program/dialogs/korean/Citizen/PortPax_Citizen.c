// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
            dialog.text = RandPhraseSimple("무슨 질문인데?","뭘 원하지?");
			link.l1 = RandPhraseSimple("내 마음이 바뀌었어.'","지금은 할 말이 없어.");
		    link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "portprince" && !CheckAttribute(npchar, "quest.Guardoftruth"))
			{
				link.l1 = "말해 봐, "+GetAddress_FormToNPC(NPChar)+", 최근에 갤리온 '산타 마르가리타'가 여기에 있었나? 혹시 사략선의 전리품으로 말이야?";
                link.l1.go = "guardoftruth";
			}
		break;
		
		case "info":
        // заменить на описание неких НПС, по квестам
			dialog.text = "내가 비밀 정보국에서 일한다고 생각하나 "+NationNameGenitive(sti(NPChar.nation))+"?";
			link.l1 = "음... 아니. 그럼 안녕히 가시오.";
			link.l1.go = "exit";
			link.l2 = "다른 질문 있나?";
			link.l2.go = "new question";
		break;
		
		case "town":
        // заменить на описание как пройти, по квестам
			dialog.text = "내가 무슨 조사국이라도 되는 줄 알아? 몰라, 아무것도 모른다니까.";

            link.l1 = "너 정말 덜렁대는구나! 썩 꺼져.";
			link.l1.go = "exit";
			link.l2 = "다른 질문 있나?";
			link.l2.go = "new question";
		break;
		
		case "guardoftruth":
			dialog.text = LinkRandPhrase("아니, 그 이름의 갤리온은 기억나지 않아. 이렇게 큰 배는 여기서 거의 본 적이 없어.","뭐라고? 갤리온? 여기서? 난 전혀 모르겠어.","아니오, 나리, 그 배는 최근에 여기 정박한 적이 없습니다, 적어도 내가 기억하는 한 그런 일은 없었소.");
			link.l1 = LinkRandPhrase("좋아...","좋아...","알겠어, 아쉽군...");
			link.l1.go = "exit";
			npchar.quest.Guardoftruth = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
