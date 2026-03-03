// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("뭘 원하지?","무엇을 알고 싶으시오?"),"무엇이 필요한가, "+GetAddress_Form(NPChar)+"?","그거 나한테 세 번째로 물어보는 거야...","너 때문에 진절머리가 나, 꺼져!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("미안하지만, 마음이 바뀌었어.","별거 아니오, 미안하오."),"잊어버렸네, 미안하군...","세 번째면 행운이 따르겠지, 응? 실례하네...","미안, 미안! 그럼 내가 나갈게...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2); 
}
