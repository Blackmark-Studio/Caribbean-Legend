// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("どのようなご質問がありますか？","ご用件は何でしょうか？"),"つい最近もその質問を私にしようとしましたね……","ああ、さては……また同じことをぐるぐる繰り返しているんじゃないか？","聞いてくれ、ここで財務を担当しているのは私だ、質問には答えません…","ブロック",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("考え直した……","今は話すことは何もありません。"),"うーん、俺の記憶はどこへ行っちまったんだ…","お察しの通りです、申し訳ありません……","承知しました……",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//Цена чахотки
			if (!CheckAttribute(npchar, "quest.Consumption") && CheckAttribute(pchar, "questTemp.Consumption.AskJuan"))
			{
				link.l1 = "聞いてくれ、「フアン」という名前に心当たりはあるか？";
				link.l1.go = "Consumption";
			}
		break;
		
		//Цена чахотки
		case "Consumption":
			dialog.text = "私には分かりませんし、知りたくもありません。あなたも調べない方がいいですよ。\nさて、失礼しますが、私は戻らなければならない仕事があります。あなたにもきっと用事があるのでしょう？それなら、 さっさと行って自分の仕事を済ませてください。";
			link.l1 = "わかりました、いいでしょう。お手数をおかけしてすみません…";
			link.l1.go = "exit";
			pchar.questTemp.Consumption.AskJuan = sti(pchar.questTemp.Consumption.AskJuan)+1;
			if(sti(pchar.questTemp.Consumption.AskJuan) == 3)
			{
				pchar.quest.Consumption2.win_condition.l1 = "location";
				pchar.quest.Consumption2.win_condition.l1.location = "PortSpein_town";
				pchar.quest.Consumption2.function = "Consumption_CreateSergio";
			}
			npchar.quest.Consumption = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
