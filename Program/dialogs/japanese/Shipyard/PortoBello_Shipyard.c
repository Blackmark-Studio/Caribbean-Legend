// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("どんな質問があるんだ？","どうされましたか？"),"少し前に俺に質問しようとしただろう…","俺の造船所でも、この町のどこでも、こんなに好奇心旺盛な連中に会ったことはねえな。","なんだよ、その質問攻めは？俺の仕事は船を造ることだ。さっさと本題に入ろうぜ。","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("考えが変わった……","今は話すことは何もねえな。"),"うーん、俺の記憶はどこへ行っちまったんだ…","ふむ、そうだな……","どうぞ……",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.Slavetrader == "FindRatPortobello")
            {
                link.l1 = "聞いてくれ、フランソワ・ゴンティエって私掠船乗りが、もしかしてお前のところに寄って話しかけてきたりしてねえか？ 最近ポルトベロにいたのは知ってるんだ。";
                link.l1.go = "Portobello_ratS_1";
            }
		break;
		
		case "Portobello_ratS_1":
			dialog.text = "ああ、そうだ。俺からコルベットを手に入れて、すぐに海へ出ていったよ。";
			link.l1 = "ありがとう！それで、彼がどこへ向かったか心当たりはあるか？";
			link.l1.go = "Portobello_ratS_2";
		break;
			
		case "Portobello_ratS_2":
			dialog.text = "いや、相棒、さっぱり分からねえな。俺は船を修理して売るだけで、どこに行くかなんて追っちゃいねえ。 そんなの俺の知ったこっちゃねえよ。";
			link.l1 = "さて、グラシアス……どこへ行ったのか調べてみるか……";
			link.l1.go = "exit";
			pchar.questTemp.Slavetrader = "FindRatPortobello_1";
			AddQuestRecord("Slavetrader", "21_2");
		break;
			
			
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
