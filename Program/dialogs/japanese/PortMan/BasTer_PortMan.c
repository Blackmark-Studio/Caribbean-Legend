// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("どんな質問だ？","何の用だ、 "+GetAddress_Form(NPChar)+"?"),"もう俺に質問しようとしただろ "+GetAddress_Form(NPChar)+"...","今日はこれで三度目の質問だな……","港のことについて話すことがないなら、余計な質問で俺を煩わせるな。","ブロック",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("考えが変わった。","話すことは何もねえ。"),"気にするな。","「確かに、もう三度目だな……」","悪いが、今は港のことには興味がないんだ。",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;

	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
