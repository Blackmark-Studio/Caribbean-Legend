// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("何か質問があるか？","どうされましたか？"),"少し前に俺に何か質問しようとしたよな……","俺の造船所でも、この町のどこでも、こんなに好奇心旺盛な連中に会ったことはねえよ。","何をそんなに質問してくるんだ？俺の仕事は船を造ることだぜ。さっさとそれを片付けよう。","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("考え直した……","今は話すことは何もねえ。"),"うーん、俺の記憶はどこへ行っちまったんだ……","ふむ、そうだな……","どうぞ……",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
		
		case "helendrinking_buy_rainbow":
			dialog.text = "…立派な選択だ、旦那。さて、取引成立か？";
			link.l1 = "は、はい！乾杯だ！包んで波止場に運んでくれ。急いでくれよ、通りで女が俺を待ってるんだ！";
			link.l1.go = "helendrinking_buy_rainbow_1";
			locCameraFromToPos(0.36, 1.86, 1.15, true, 2.06, -0.20, -4.38);
		break;
		
		case "helendrinking_buy_rainbow_1":
			dialog.text = "すべて合わせて五万銀貨だ、旦那。";
			if (sti(pchar.money) >= 55000) {
				link.l1 = "な、なんだって？ご、五万だと？よし、自分で数えてくれ！それにチップとしてもう五千やる。行くぞ！";
				link.l1.go = "helendrinking_buy_rainbow_yes";
			}
			
			link.l2 = "いやいや、俺は金持ち、ひっく！…な奴かもしれねえが、そんな大金じゃ買わねえぞ。いや、旦那！じゃあな、船頭。";
			link.l2.go = "helendrinking_buy_rainbow_no";
		break;
		
		case "helendrinking_buy_rainbow_yes":
			dialog.text = "ありがとうございます、旦那。どうかこの船があなたのお役に立ちますように！";
			link.l1 = "";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "First time";
			
			AddMoneyToCharacter(pchar, -55000);
			pchar.questTemp.HelenDrinking.BoughtRainbow = true;
			
			AddDialogExitQuestFunction("HelenDrinking_GoToPerlas");
		break;
		
		case "helendrinking_buy_rainbow_no":
			dialog.text = "ああ、さっさと失せろ、坊ちゃん。うちは三時間前に閉めたんだ。";
			link.l1 = "";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "First time";
			
			AddDialogExitQuestFunction("HelenDrinking_GoToPerlas");
		break;
		
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
