// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("질문, "+GetAddress_Form(NPChar)+"?","무엇을 도와드릴까요, "+GetAddress_Form(NPChar)+"?"),""+GetSexPhrase("음, 이게 무슨 수작이지, "+GetAddress_Form(NPChar)+"? ","또 이상한 질문이야? 자기야, 가서 럼주라도 한잔해...")+"","오늘 하루 동안만 벌써 세 번째로 그 질문을 꺼내는군..."+GetSexPhrase(" 이게 애정의 표시인가?","")+"","또 질문이 있겠군. "+GetAddress_Form(NPChar)+"?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("마음이 바뀌었어","지금은 할 말이 없어."),"아니, 아니, 이쁜이...","말도 안 돼, 자기야, 노망이야...","아니, 무슨 질문이야?...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;


	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
