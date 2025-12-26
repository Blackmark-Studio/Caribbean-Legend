// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("「すべての噂話は」 "+GetCityName(npchar.city)+" お役に立ちますぜ。何を知りたいんだ？","ちょうどその話をしていたところだぜ。お前、忘れちまったのか……","今日はこれで三度目だぜ、この質問を持ち出すのは……","「お前、オウムみたいに同じことばかり繰り返してるじゃねえか…」","ブロック",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("「知ってるか、 "+NPChar.name+"、また今度だな。","ああ、何かの理由で忘れちまったんだよな……","ああ、これで本当に三度目だな…","ああ……",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.Slavetrader") && pchar.questTemp.Slavetrader == "FindRatHavana")
            {
                link.l1 = "フランソワ・ゴンティエがたまたまこの町に立ち寄ったことはあるか？奴はコルベット『"+pchar.questTemp.Slavetrader.ShipName+"「…念のため…」 ";
                link.l1.go = "Havana_ratT_1";
            }
			if (CheckAttribute(npchar, "quest.batabano"))
            {
                link.l1 = "教えてくれ、相棒、ドン・ディエゴ・デ・モントーヤはどこにいる？俺は遅かったか？もう本土へ出発しちまったのか？";
                link.l1.go = "guardoftruth";
            }
			// калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "graveyard" && !CheckAttribute(npchar, "quest.caleuche"))
			{
				link.l1 = "聞いてくれ、ジョアキム・メリマンという名の男がここに立ち寄らなかったか？中年の医者で、ポルトガル人、 口ひげとあごひげがあって、鋭い目つきをしているんだ。もしかして部屋を借りたがっていたか？";
				link.l1.go = "caleuche";
			}
		break;

		case "Havana_ratT_1":
			dialog.text = "ああ、あの陰気な奴か？ああ、うちの店に寄ったぜ。ひとつ教えてやろうか、奴はオレゴン＝アンド＝ ハスコンと約束があったんだ。特許を申請したが、うまくいかずに出て行ったよ。";
			Link.l1 = "「で、あいつはどこへ航海して行ったんだ、知ってるか？俺はポルトベロからずっと追いかけてるんだが、 全然見つからねえんだ。」";
			Link.l1.go = "Havana_ratT_2";
		break;
		
		case "Havana_ratT_2":
			dialog.text = "あんた、あいつに何の用だ？あいつはよそ者を怖がって、いつも誰からも隠れてるんだぜ。武装した見知らぬ奴を見ると、 すぐに剣を抜くし、いつも四人の護衛に囲まれて歩いてる。もしかして、 あいつがそんなに警戒してるのはあんたじゃねえか？";
			Link.l1 = "旦那、みんなそればっかり言いやがるな！俺が人殺しに見えるのか？あいつは昔からの友達だぜ、 ただ急いで知らせを伝えたいだけさ。もう誰もあいつを探してねえって知ったら、きっと大喜びするだろうよ――もう隠れる必要はねえんだからな。";
			Link.l1.go = "Havana_ratT_3";
		break;
		
		case "Havana_ratT_3":
			dialog.text = "奴が隠れる必要がないって？ハハハ！ハバナを出発するたった一日前に、 ジャングルでごろつきどもが奴を殺そうとしたんだぜ…もちろん奴にも手下がいて、そいつらは一瞬でごろつきどもをミンチにしちまった。で、あんたはこう言うんだな…";
			Link.l1 = "おいおい、たぶん地元のゴロツキが財布を狙っただけだろう。自分でも分かってるだろ、 あのジャングルには悪党がうようよしてるんだ。で、そいつはどこへ行ったんだ？";
			Link.l1.go = "Havana_ratT_4";
		break;
		
		case "Havana_ratT_4":
			dialog.text = "あいつは屋敷から遠く離れて長い間追放された後も、ずっと自分はカエル野郎ども――つまり同胞に自首するって言い張ってたぜ。トルトゥーガのド・オジェロンとかいう奴のところへ向かったらしい……恋人のことも何かブツブツ言ってたが、俺にはよく分からなかったな。";
			Link.l1 = "「なるほど、トルトゥーガか？素晴らしい！あそこで奴を捕まえられるといいが。ありがとう、」 "+npchar.name+"、助かったぜ。じゃあな。";
			Link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "21_7");
			pchar.questTemp.Slavetrader = "FindRatTortuga";
			pchar.quest.Slavetrader_findTortugaRat.win_condition.l1 = "location";
            pchar.quest.Slavetrader_findTortugaRat.win_condition.l1.location = "Tortuga_HouseHut";
            pchar.quest.Slavetrader_findTortugaRat.win_condition = "Slavetrader_findTortugaRat";
		break;

		case "guardoftruth":
			dialog.text = "ふむ……それでフランス野郎がドン・ディエゴに興味を持つ理由は何だ、ん？";
			link.l1 = "俺がフランス人だってことは関係ねえ。重要なのはこの異端審問官の署名入りの書類だ。見てみな……わかったか？ディエゴに伝える急ぎの用件があるんだ。";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "ほう、あんたはヴィンチェント神父様の使いか？それなら話が変わるぜ。 ドン・ディエゴ・デ・モントーヤは二日前に艦隊を率いて出港したが、すぐに自分のクーリエ・ラガーで戻ってきた。 彼の船の一隻がキューバ南方の岩礁で座礁しちまってな、今日になって修理資材を買い込んでいたぜ\n南の湾を見てみな、そこに船と本人がいるはずだ。まだ穴を塞ぎ終えてはいないだろうよ。";
			link.l1 = "助かったぜ、相棒！お前は本当に頼りになるな！";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "とんでもない、いつでもどうぞ。イエズス会の兄弟なら喜んで力になるぜ。";
			link.l1 = "ああ、パックス・ヴォビスクムとかなんとかだぜ。";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			DialogExit();
			DeleteAttribute(npchar, "quest.batabano");
			AddQuestRecord("Guardoftruth", "47");
			pchar.quest.GuardOT_Batabano.win_condition.l1 = "location";
			pchar.quest.GuardOT_Batabano.win_condition.l1.location = "Shore13";
			pchar.quest.GuardOT_Batabano.function = "GuardOT_SanAntonioPrepare";
		break;
		
		// калеуче
		case "caleuche":
			dialog.text = "悪魔しか知らねえな、相棒。もしかしたら来てるかもしれねえが、俺は知らねえよ。悪いな。";
			link.l1 = "なるほど。残念だ。俺は引き続き探すとするか……";
			link.l1.go = "exit";
			npchar.quest.caleuche = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
