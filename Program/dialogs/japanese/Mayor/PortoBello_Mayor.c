// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("何の用だ？聞きたいことがあればどうぞ。","お聞きしましょう、ご質問は何でございますか？"),"これで二度目のお尋ねですね……","これで三度目のご質問でございますが……","いつになったら終わるのだ！？私は植民地の諸事に忙しい身であるのに、まだ私を煩わせるのか！","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("考えを変えました、申し訳ありません。","今は駄目です。場所も時もふさわしくありません。"),"確かに、今は申し上げることがございません、申し訳ありません。","後でお尋ねします。","「申し訳ありません」 "+GetAddress_FormToNPC(NPChar)+"...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;

		case "Cupture_after":
            dialog.text = RandPhraseSimple("すでに全てを奪ったではありませんか。まだ何をお望みですか？","「まだお取りにならなかった物が何か残っておりますか？」");
            link.l1 = RandPhraseSimple("少し見て回っているだけです……","ちょっと確認しているだけだ、何か取り忘れたかもしれないからな…");
            link.l1.go = "exit";
            NextDiag.TempNode = "Cupture_after";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
