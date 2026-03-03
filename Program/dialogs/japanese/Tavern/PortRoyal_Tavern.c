// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("すべての噂話は "+GetCityName(npchar.city)+" お役に立ちますぜ。何を知りたいんだ？","ちょうどその話をしていたところだぜ。お前、忘れちまったのか……","今日はそれを聞くの、これで三度目だぞ……","お前、オウムみたいに同じことばっかり繰り返してるじゃねえか…","ブロック",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("「知ってるか、 "+NPChar.name+"、たぶん次の機会にな。","そうだ、なぜか忘れちまってたんだ……","ああ、本当にこれで三度目だな……","ああ……",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.Slavetrader == "FindRatJamaica")
            {
                link.l1 = "ひょっとしてフランソワ・ゴンティエがどこにいるか知らねえか？";
                link.l1.go = "Jamaica_ratP_1";
            }
			// Страж Истины
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "merdok" && !CheckAttribute(npchar, "quest.jino"))
			{
				link.l1 = "聞いてくれ、この町に錬金術師が来ていないか？医者なんだ。イタリア人で三十歳くらい、 名前はジーノ・グヴィネイリっていうんだ。何か聞いてないか？";
				link.l1.go = "guardoftruth";
			}
		break;

		case "Jamaica_ratP_1":
			dialog.text = NPCStringReactionRepeat("全く見当もつかねえ。その名前なんざ聞いたこともねえよ。","それはもう聞かれたし、俺はちゃんと答えたぜ。","言っただろう、もうそのことは聞かれたぜ、ゴンティエ。","聞けよ、さっさとどっか行って俺の邪魔すんじゃねえ！頭がどうかしちまったのか！？","ブロック",0,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("そうかい、じゃあ俺は引き続き探すぜ。","ふむ、そうかもな……","ああ、そうだ、そのことは俺が頼んだんだ…","「すまねえ」 "+npchar.name+"...",npchar,Dialog.CurrentNode);
		break;
		
		case "guardoftruth":
			dialog.text = LinkRandPhrase("いいや、知らねえな。薬草師や医者はいるが、その名前のやつはいねえぜ。","こんな変わった名前は初めて聞いたぜ。いや、あんたの言うその男はここに来たことはねえな。","ここには錬金術師なんて一人もいねえよ。医者ならいるが、そんな変な名前の奴はいねえな。");
			link.l1 = "なるほど。残念だな。引き続き探してみるぜ！";
			link.l1.go = "exit";
			npchar.quest.jino = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
