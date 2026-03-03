// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("무슨 일로 왔소? 물어보시오.","듣고 있소, 무슨 질문이오?"),"이것이 두 번째로 질문하려는 시도이오...","이것이 세 번째로 질문하려는 시도이오...","이게 도대체 언제 끝나겠소?! 나는 식민지 업무로 바쁜 몸인데, 아직도 나를 귀찮게 하다니!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("마음을 바꿨소, 미안하오.","지금은 아니오. 장소와 시간이 맞지 않소."),"사실 지금은 드릴 말씀이 없소, 미안하오.","나중에 물어보겠소.","죄송합니다, "+GetAddress_FormToNPC(NPChar)+"...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;

		case "Cupture_after":
            dialog.text = RandPhraseSimple("이미 모든 것을 가져갔소. 더 무엇을 원하시오?","아직 가져가지 않은 것이 남아 있소?");
            link.l1 = RandPhraseSimple("그저 둘러보고 있을 뿐이오...","그냥 확인하는 중이오, 뭔가 놓고 온 게 있을지도 몰라서...");
            link.l1.go = "exit";
            NextDiag.TempNode = "Cupture_after";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
