// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("兵士に何か聞きたいことがあるのか？","兵士ってのは人生すべて計画済みさ――警備して、働いて……で、どうしたんだ、 "+GetAddress_Form(NPChar)+"?"),"「くだらねえ質問で兵士を煩わせるんじゃねえぞ」 "+GetAddress_Form(NPChar)+"...","今日はこれで三度目だぜ、お前が俺に質問しようとしたのは……","兵士の運命ってのは楽じゃねえんだ、なのに今やお前らクズどもが俺を狂わせやがる……","ブロック",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("気が変わった……","今は話すことは何もねえな。"),"了解だ…","ああ、その通りだな、もう三度目だぜ……","すまねえ……",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
