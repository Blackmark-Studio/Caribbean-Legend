// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("무슨 일로 왔소? 묻고 싶은 것이 있으면 말하시오.","듣고 있소, 무슨 질문이오?"),"이것이 두 번째로 질문하려는 시도이오...","이것이 세 번째로 질문하려는 시도이오...","이게 도대체 언제 끝나는 것이오?! 나는 식민지 업무로 바쁜 사람이오, 그런데도 아직도 나를 귀찮게 하다니!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("생각이 바뀌었소, 미안하오.","지금은 아니오. 장소와 시간이 맞지 않소."),"사실 지금은 드릴 말씀이 없소, 미안하오.","나중에 여쭙겠소.","죄송하오, "+GetAddress_FormToNPC(NPChar)+"...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;

		case "Cupture_after":
            dialog.text = RandPhraseSimple("이미 모든 것을 가져가셨소. 이제 또 무엇을 원하시오?","아직 챙기지 않은 것이 남아 있소?");
            link.l1 = RandPhraseSimple("그냥 둘러보고 있을 뿐이오...","그냥 확인하는 중이오, 뭔가 깜빡하고 안 챙겼을 수도 있어서...");
            link.l1.go = "exit";
            NextDiag.TempNode = "Cupture_after";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
