// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("何か質問があるか？","「どうなさいましたか、」 "+GetAddress_Form(NPChar)+"?"),"「さっき俺に何か質問しようとしたじゃねえか」 "+GetAddress_Form(NPChar)+"...","もうこれで三度目だぞ、俺にちょっかい出すのは…","「まだ質問があるんだろう？」","ブロック",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("考えが変わったんだ……","今は話すことは何もねえな。"),"うーん、俺の記憶はどこへ行っちまったんだ…","ああ、本当にこれで三度目だな……","いや、何の質問だって…",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
