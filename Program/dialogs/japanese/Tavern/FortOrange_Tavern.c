// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("どんな質問があるんだ？","「どうなさいましたか、」 "+GetAddress_Form(NPChar)+"?"),"「さっき俺に何か質問しようとしたじゃねえか、」 "+GetAddress_Form(NPChar)+"...","今日一日で、その質問を持ち出すのはこれで三度目だぞ…","「また質問かい？」","ブロック",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("気が変わったんだ……","今は話すことは何もねえな。"),"うーん、俺の記憶はどこに行っちまったんだ…","ああ、本当にこれで三度目だな……","いや、何の質問だって…",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.Slavetrader == "FindRatJamaica")
            {
                link.l1 = "フランソワ・ゴンティエという男がこの町に立ち寄ったことはあるか？どうしてもそいつが必要なんだ。";
                link.l1.go = "Jamaica_ratF_1";
            }
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "silk_4")
            {
                link.l1 = "聞けよ、相棒、ポートロイヤルから出た船が造船所用に特別な絹を買ってるんだ……とびきりの絹さ、きっと聞いたことあるだろう。その絹を売る奴がこの居留地のどこかにいるって話だ。 そいつを探す手がかり、何か知らねえか？俺から商談を持ちかけたいんだ。";
                link.l1.go = "mtraxx";
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "silk_5" && (PCharDublonsTotal() >= 50))
            {
                link.l1 = "俺はドゥブロン金貨を五十枚持ってるぜ。これを受け取って、話を始めろ。";
                link.l1.go = "mtraxx_4_1";
			}
		break;

		case "Jamaica_ratF_1":
			dialog.text = "ああ、いたよ。何日か部屋を借りてたんだ。あんまり感じのいい奴じゃなかったぜ。それに、 やたらと誰かに探されてることを気にしてたな。いつも怯えて周りを気にしてた。あんたが、 あいつがそんなに恐れてた相手なのか？";
			link.l1 = "いや、俺じゃねえよ。知ってるだろうが、私掠船乗りには敵が多いんだぜ。\nそれで、あいつはどこにいるんだ？俺とあいつで取引することにしたんだが、 まるで地面に飲み込まれたみたいに姿を消しちまったんだ。";
			link.l1.go = "Jamaica_ratF_2";
		break;
		
		case "Jamaica_ratF_2":
			dialog.text = "奴は自分の船で海へ出ていったぜ。どこへ向かったかは知らねえ。そこまでは俺に教えてくれなかったんだ。";
			link.l1 = "ああ、残念だぜ！これからどこであいつを探せばいいんだ？";
			link.l1.go = "Jamaica_ratF_3";
		break;
		
		case "Jamaica_ratF_3":
			dialog.text = "知らねえよ、相棒。知ってたら教えてやるさ。";
			link.l1 = "わかった、そうか。他の奴に聞いてみるぜ…";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "21_4");
			pchar.questTemp.Slavetrader = "FindRatJamaica_H";
		break;
		
		// Addon 2016-1 Jason пиратская линейка
		case "mtraxx":
            dialog.text = "ふん、もしうちの商人――店を切り盛りしてる奴を疑ってるなら、そいつじゃねえよ。あいつは絹の帆布なんか扱っちゃいねえ。 密輸業者もここには来ねえさ、税関がないから奴らの出番もねえしな。それに、 ここで商売してるのはうちの商人以外いねえんだぜ。周りを見てみな、俺たちはそんな連中じゃねえよ、ははっ！\n";
			link.l1 = "だが、誰かがポートロイヤルに絹を運んでいるのは間違いねえ。\nその仕入れ人が誰か、何か心当たりはあるか？";
			link.l1.go = "mtraxx_1";
		break;
		
		case "mtraxx_1":
            dialog.text = "ポートロイヤルから来た密輸業者かもな？それともはぐれ海賊か？ きっとどこかの隠れ入り江で戦利品を下ろしてるんだろう…ははっ！いい考えがあるぜ、相棒。この海域のことなら何でも知ってる地元の奴がいるんだ。 そいつが怪しいと思ってなけりゃ、絹の商人なんていやしねえよ。";
			link.l1 = "素晴らしい！その男の名前は何だ？";
			link.l1.go = "mtraxx_2";
		break;
		
		case "mtraxx_2":
            dialog.text = "うーん……名前を思い出そうとしてるんだが、どうしても出てこねえんだよな……";
			link.l1 = "「記憶を手伝うために、少し小銭をどうだ？」";
			link.l1.go = "mtraxx_3";
		break;
		
		case "mtraxx_3":
            dialog.text = "それが役に立つかもしれねえな……五十枚の金ドゥブロンなら、この年寄りの頭もきっと冴えるぜ。";
			if (PCharDublonsTotal() >= 50) // Rebbebion, учёт количества дублонов из рундука
			{
				link.l1 = "なるほどな。ほら、コインを受け取れ。";
				link.l1.go = "mtraxx_4_1";
			}
			else
			{
				link.l1 = "なるほど。戻ってくるぜ……";
				link.l1.go = "mtraxx_4_2";
			}
		break;
		
		case "mtraxx_4_1":
			RemoveDublonsFromPCharTotal(50);
			PlaySound("interface\important_item.wav");
            dialog.text = "ハスキー・ビリーって野郎があんたの探してる男だ。あいつはジャマイカにずっと住んでて、 街の犬まで知ってるくらいさ。昔は海賊で、イギリス野郎どもを散々悩ませてたが、 三年ほど前にケガしてからは大人しくなった。今じゃ主に漁をしたり、サメを狩ったり、 ジャマイカの入り江で琥珀を集めたりしてる。古いロングボートから降りるのは、 ラム酒とクラッカーを買い足す時くらいだぜ\nあいつを探すならジャマイカ近海だな。北側から東の端まで航海してるって話だが、 ロングボートを追いかけるのは馬鹿のやることだ。南西の岬あたりで張ってた方がいい――ネグリル岬の近くで週に一度は目撃されてるらしいぜ。あいつの小舟は『ザ・フライフィッシュ』って名だ。";
			link.l1 = "ありがとな、相棒。お前はちゃんと報酬に値する働きをしたぜ。";
			link.l1.go = "mtraxx_5";
		break;
		
		case "mtraxx_5":
            dialog.text = "幸運を祈るぜ、相棒！探してるものが見つかるといいな！";
			link.l1 = "...";
			link.l1.go = "mtraxx_6";
		break;
		
		case "mtraxx_4_2":
            DialogExit();
			AddQuestRecord("Roger_2", "6");
			pchar.questTemp.Mtraxx = "silk_5";
		break;
		
		case "mtraxx_6":
            DialogExit();
			AddQuestRecord("Roger_2", "7");
			pchar.questTemp.Mtraxx = "silk_6";
			/*pchar.quest.mtr_negril.win_condition.l1 = "Timer";
			pchar.quest.mtr_negril.win_condition.l1.date.hour  = 12+rand(12);
			pchar.quest.mtr_negril.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 2+rand(3));
			pchar.quest.mtr_negril.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 2+rand(3));
			pchar.quest.mtr_negril.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 2+rand(3));*/
			PChar.quest.mtr_negril.win_condition.l1 = "ExitFromLocation";
			PChar.quest.mtr_negril.win_condition.l1.location = PChar.location;
			pchar.quest.mtr_negril.function = "Mtraxx_CreateBilly";
			SetFunctionTimerCondition("Mtraxx_BillySeaTimeOver", 0, 0, 7, false);
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
