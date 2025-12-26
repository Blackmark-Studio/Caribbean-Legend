// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("兵士に何か聞きたいことがあるのか？","兵士は人生のすべてを計画している――警備に、せわしなく動き回ることに……どうなさいましたか、 "+GetAddress_Form(NPChar)+"?"),"「くだらねえ質問で兵隊を煩わせるんじゃねえぞ」 "+GetAddress_Form(NPChar)+"...","今日はこれで三度目だぜ、俺に質問しようとしたのは……","兵士の人生は楽じゃねえんだ、そして今やお前らクズどもが俺を狂わせてるんだよ……","ブロック",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("気が変わったんだ……","今は話すことは何もねえな。"),"了解だ…","ああ、その通りだ、もうこれで三度目だな……","すまねえ……",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
