// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("どんな質問だ？","何の用だ、 "+GetAddress_Form(NPChar)+"?"),"もうすでに俺に質問しようとしたじゃねえか "+GetAddress_Form(NPChar)+"...","今日はこれで三度目の質問だな……","港の用件について何も話すことがないなら、くだらない質問で俺を煩わせるな。","ブロック",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("考えを変えた。","話すことは何もねえ。"),"気にするな。","「本当に、もう三度目だな……」","申し訳ないが、今のところ港の用事には興味がないんだ。",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			
			if (pchar.questTemp.Slavetrader == "FindRatTortuga")
            {
                link.l1 = "ごきげんよう。フランソワ・ゴンティエを探しています。彼のコルベット『"+pchar.questTemp.Slavetrader.ShipName+"「'はきっとここ、お前さんの港にいたはずだ。」";
                link.l1.go = "Tortuga_ratP_1";
            }
			
		break;

		case "Tortuga_ratP_1":
			dialog.text = NPCStringReactionRepeat("ふむ……残念だが、コルベット『"+pchar.questTemp.Slavetrader.ShipName+" ここに来たことは一度もなく、フランソワ・ゴンティエもここで登録していません。","この件についてはすでに尋ねられ、俺はもう答えたぜ。","言っただろう、もうそのゴンティエについては聞かれたぜ。","お願いだから、仕事の邪魔をしないでくれ！","ブロック",0,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("ありがとう。引き続き探してみる。","ふむ、そうだな……","ああ、本当に俺が頼んだんだ……","「失礼」 "+npchar.name+"...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;

	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
