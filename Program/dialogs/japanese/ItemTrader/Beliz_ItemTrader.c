// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("「どんな質問だ？」","何の用だ、 "+GetAddress_Form(NPChar)+"?"),"「また質問か」 "+GetAddress_Form(NPChar)+"...","質問ばかりだな……取引でもどうだ、 "+GetAddress_Form(NPChar)+"ん？","聞けよ、いつまで話すつもりだ？","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("今のところ質問はない……","すまない、今は話すことがないんだ……"),"またしても、すまねえ…","本当にそろそろ取引する時かもしれねえな……","申し訳ないが、取引しよう…",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
