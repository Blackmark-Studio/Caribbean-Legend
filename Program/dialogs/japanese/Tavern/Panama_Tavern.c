// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("「すべての噂話は」 "+GetCityName(npchar.city)+" お役に立ちますぜ。何をお知りになりたいんだ？","ちょうどその話をしていたところだぜ。お前、忘れちまったのか……","今日はこれで三度目だぜ、その質問を持ち出すのは……","お前、オウムみたいに同じことばかり繰り返してるじゃねえか…","ブロック",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("「知ってるか、」 "+NPChar.name+"、また今度にしようぜ。","ああ、なぜか忘れちまったんだよな……","ああ、本当にこれで三度目だな……","ああ……",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.Slavetrader == "FindRatPanama")
            {
                link.l1 = "あんたの町にフランソワ・ゴンティエって私掠船乗りがいるって聞いたんだが、どこにいるか知らねえか？";
                link.l1.go = "Panama_rat_1";
            }
			// Addon-2016 Jason ”ЊЉ-ѓваделупа
			if (CheckAttribute(pchar, "questTemp.FMQG") && pchar.questTemp.FMQG == "headhunter_panama")
            {
                link.l1 = "見てくれ、俺はベルtrand・ピネットって男を探してるんだが、聞いたことあるか？つい最近パナマに着いたらしい。 カツラをかぶった威厳のある紳士だ。ここに来てたかもしれねえ…";
                link.l1.go = "FMQG";
            }
		break;

		//-->работорговец
		case "Panama_rat_1":
			dialog.text = NPCStringReactionRepeat("ああ、そんな奴がこの町にいたぜ。暗がりでうろついてやがった…そしたら仲間らしき連中がやってきて、まるで殺し屋の一団みてえだった。そいつはそいつらと一緒に町を出ていったよ。 ","それはもう聞かれたし、俺はちゃんと答えたぜ。","言っただろ、あんたはそのゴンティエについてもう聞いたじゃねえか。","聞けよ、さっさとどっか行って俺の邪魔すんじゃねえ！頭がどうかしちまったのか！？","ブロック",0,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("「それで、奴はどこへ行ったんだ、知ってるか？」","ふむ、そうかもな……","ああ、そうだ、そのことは俺が頼んだんだ…","「すまねえ」 "+npchar.name+"...",npchar,Dialog.CurrentNode);
			link.l1.go = "Panama_rat_2";
		break;
		
		case "Panama_rat_2":
			dialog.text = "ここから歩いて出られる道は一つだけ――ポルトベロだ。あいつはそこへ逃げたんだ。だから、そこで探してみな。";
			link.l1 = "ありがとう、すごく助かったぜ！";
			link.l1.go = "exit";
			pchar.questTemp.Slavetrader = "FindRatPortobello";
			AddQuestRecord("Slavetrader", "21_1");
		break;
		//<--работорговец
		
		// Addon-2016 Jason ”ЊЉ-ѓваделупа
		case "FMQG":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("panama");
			dialog.text = "「ベルトラン・ピネット？フランス人か？聞いたことねえな。いや、相棒、ここしばらくフランス野郎は見かけてねえぜ。 」";
			link.l1 = "なんてこった……本当か？あいつはドン・カルロス・デ・ミリヤルっていう偉いイダルゴの友人なんだぜ。 二人は一緒にここへ来るはずだったんだ。";
			link.l1.go = "FMQG_1";
		break;
		
		case "FMQG_1":
			dialog.text = "ドン・デ・ミリヤール？あの旦那は一年前にパナマを訪れたぜ。実は、 ドン・カルロス・デ・ミリヤールはポルトベロに住んでるんだ。あいつは地元総督の親しい友人さ。";
			link.l1 = "なるほどな。ジャングルで時間と息を無駄にする必要はなかったってわけだ。ありがとな、相棒。";
			link.l1.go = "FMQG_2";
		break;
		
		case "FMQG_2":
			DialogExit();
			pchar.questTemp.FMQG = "headhunter_portobello";
			AddQuestRecord("FMQ_Guadeloupe", "8");
			AddMapQuestMarkCity("PortoBello", true);
			AddLandQuestMark(characterFromId("PortoBello_tavernkeeper"), "questmarkmain");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
