// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("질문, "+GetAddress_Form(NPChar)+"?","무엇을 도와드릴까요, "+GetAddress_Form(NPChar)+"?"),""+GetSexPhrase("흠, 이게 다 무슨 짓이야, "+GetAddress_Form(NPChar)+"? ","또 이상한 질문이냐? 이봐, 럼주나 한잔하고 가라...")+"","오늘 하루 종일, 그 질문을 벌써 세 번째 꺼내는군..."+GetSexPhrase(" 이게 애정의 표시인가?","")+"","질문이 더 있겠지, "+GetAddress_Form(NPChar)+"?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("마음이 바뀌었어","지금은 할 말이 없어."),"아니, 아니, 이쁜이...","말도 안 돼, 자기야...","아니, 무슨 질문이야?…",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;


	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
