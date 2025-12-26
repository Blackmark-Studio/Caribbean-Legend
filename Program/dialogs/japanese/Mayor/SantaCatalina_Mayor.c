// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("何の用だ？聞きたいことがあればどうぞ。","お聞きしましょう、ご質問は何でございますか？"),"これは二度目のご質問でございますね…","これで三度目のご質問でございますが……","いつまで続くのだ！？私は植民地の諸事で忙しい身だというのに、まだ私を煩わせるのか！","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("考え直しました、申し訳ありません。","今は駄目だ。場所も時もふさわしくない。"),"確かに、今は申し上げることがございません、申し訳ありません。","後で伺います。","「申し訳ありません」 "+GetAddress_FormToNPC(NPChar)+"...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;

		case "Cupture_after":
            dialog.text = RandPhraseSimple("すでに全てを奪ったではありませんか。まだ何を望むのですか？","まだ手に入れていない物が何か残っておりますか？");
            link.l1 = RandPhraseSimple("ちょっと見て回っているだけだ……","ちょっと確認してるだけだ、何か取り忘れたかもしれねえからな……");
            link.l1.go = "exit";
            NextDiag.TempNode = "Cupture_after";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
