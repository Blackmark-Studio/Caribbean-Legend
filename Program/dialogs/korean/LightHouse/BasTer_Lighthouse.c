// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("뭐 원하는 거야?","무엇을 알고 싶으신가?"),"무슨 일이냐, "+GetAddress_Form(NPChar)+"?","그거 세 번째로 나한테 물어보는 거야...","너 이제 지긋지긋하다, 꺼져!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("미안하지만, 마음이 바뀌었어.","별일 아니오, 미안하오."),"잊어버렸네, 미안하오...","세 번째면 행운이 따르지, 안 그래? 실례하네...","미안, 미안! 그럼 내가 나갈게...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2); 
}
