// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("兵士に何か聞きたいことがあるのか？","兵士の人生なんて決まってるさ――見張りに、せわしなく動き回ってな……で、俺に何か用か？ "+GetAddress_Form(NPChar)+"?"),"「くだらねえ質問で兵士を煩わせるんじゃねえぞ」 "+GetAddress_Form(NPChar)+"...","今日はこれで三度目だぜ、お前が俺に質問しようとしたのは……","兵士の人生は楽じゃねえんだ、なのにお前らクズどもが俺をイライラさせやがって……","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("気が変わったんだ……","今は話すことは何もねえぜ。"),"了解だ…","ああ、そうだな、もう三回目だぜ……","すまねえ……",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
