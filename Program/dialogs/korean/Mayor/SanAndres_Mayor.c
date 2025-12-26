// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("무슨 일로 왔소? 묻고 싶은 것이 있으면 말하시오.","듣고 있소, 무슨 질문이오?"),"이것이 두 번째로 물어보는 것이오...","이것이 세 번째로 질문하시는군요...","이게 도대체 언제 끝나겠소?! 나는 식민지 업무로 바쁜 사람이오, 그런데도 아직도 나를 귀찮게 하다니!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("생각이 바뀌었소, 미안하오.","지금은 아니오. 장소와 시간이 맞지 않소."),"사실 지금은 드릴 말씀이 없소, 미안하오.","나중에 물어보겠소.","죄송하오, "+GetAddress_FormToNPC(NPChar)+"...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
