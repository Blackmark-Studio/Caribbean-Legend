// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("何の用だ？聞きたいことがあれば言え。","お聞きしましょう、ご質問は何でしょうか？"),"これで二度目のご質問でございますね…","これで三度目のご質問でございますが……","いつになったら終わるのだ！？私は植民地の仕事で忙しい身だ、なのにまだ私を煩わせるのか！","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("考えが変わりました、申し訳ありません。","今は駄目だ。場所も時も間違っている。"),"確かに、今は申し上げることがございません、申し訳ありません。","後で伺います。","申し訳ありません。 "+GetAddress_FormToNPC(NPChar)+"...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;

		case "Cupture_after":
            dialog.text = RandPhraseSimple("すでにすべて奪われました。これ以上何を望むのですか？","「まだお取りにならなかったものが何か残っておりますか？」");
            link.l1 = RandPhraseSimple("ちょっと見て回っているだけです……","ちょっと確認しているだけだ、何か取り忘れたかもしれないからな…");
            link.l1.go = "exit";
            NextDiag.TempNode = "Cupture_after";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
