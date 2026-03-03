// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("무엇을 원하시오? 물어보시오.","듣고 있소, 무슨 질문이오?"),"이것이 두 번째로 질문하려는 시도이오...","이것이 세 번째로 질문하려는 시도이오...","이게 도대체 언제 끝나겠소?! 나는 식민지 업무로 바쁜 사람인데, 아직도 나를 귀찮게 하다니!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("마음을 바꿨소, 미안하오.","지금은 아니오. 장소와 시간이 맞지 않소."),"맞습니다, 지금은 드릴 말씀이 없군요. 미안합니다.","나중에 물어보겠소.","죄송하오, "+GetAddress_FormToNPC(NPChar)+"...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (!CheckAttribute(npchar, "quest.Guardoftruth") && CheckAttribute(pchar, "questTemp.Guardoftruth.Trinidad") && pchar.questTemp.Guardoftruth.Trinidad == "begin")
			{
				link.l1 = "각하, 1654년 4월에 미겔 디초소가 지휘하던 프리깃함이 있었습니다. 그 이후로 그는 행방불명되었습니다. 혹시 그에 대해 기억하십니까? 어쩌면 각하를 찾아와 대화를 나눈 적이 있을지도...";
				link.l1.go = "guardoftruth";
			}
		break;
		
		case "guardoftruth":
			dialog.text = "네, 그 사람은 기억합니다. 하지만 그에 대한 자세한 내용은 기억나지 않습니다. 여기 왔다가 그냥 떠났습니다. 도와드릴 수 없겠군요.";
			link.l1 = "알겠소. 폐를 끼쳐 미안하오.";
			link.l1.go = "exit";
			npchar.quest.guardoftruth = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
