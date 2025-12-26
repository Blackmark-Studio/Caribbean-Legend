// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("どんな質問だ？","何の用だ、 "+GetAddress_Form(NPChar)+"?"),"もうすでに俺に質問しようとしただろ "+GetAddress_Form(NPChar)+"...","今日だけでその質問は三度目だぞ……","港の用件について何も話すことがないなら、俺に質問してくるんじゃねえ。","ブロック",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("考えを変えた。","話すことは何もねえ。"),"気にするな。","確かに、もう三度目だな……","悪いが、今は港のことには興味がないんだ。",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;

	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
