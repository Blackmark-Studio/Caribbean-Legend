// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("何の用だ？聞きたいことがあれば言え。","お聞きしましょう、ご質問は何でしょうか？"),"これで二度目のご質問ですね……","これで三度目のご質問でございます…","いつまで続くのだ！？私は植民地の諸事に忙しい身であるのに、まだ私を煩わせるつもりか！","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("考えが変わりました、申し訳ありません。","今は駄目だ。場所も時もふさわしくない。"),"確かに、今は申し上げることがございません、申し訳ありません。","後でお伺いします。","申し訳ありません。 "+GetAddress_FormToNPC(NPChar)+"...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;

		case "Cupture_after":
            dialog.text = RandPhraseSimple("あなたはすでにすべてを奪いました。これ以上何を望むのですか？","「まだお取りにならなかった物が何か残っておりますか？」");
            link.l1 = RandPhraseSimple("ちょっと見て回っているだけです……","ちょっと確認しているだけだ、何か取り忘れたかもしれないからな…");
            link.l1.go = "exit";
            NextDiag.TempNode = "Cupture_after";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
