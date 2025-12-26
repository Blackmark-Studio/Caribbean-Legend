// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("「どんな質問だ」 "+GetSexPhrase("息子よ","娘よ")+"?","何でも聞いてくれ、聞いてるぜ…"),"聞いているぞ、今話せ。 "+GetSexPhrase("息子よ","娘よ")+"...","「三度目だが、」 "+GetSexPhrase("息子よ","娘よ")+"、必要なものがあれば言ってくれ。","聖職者にはやることが山ほどあるんだ、あんたは俺の邪魔をしてるぜ。 "+GetSexPhrase("息子よ","娘よ")+"...","ブロック",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("考えが変わった……","今は違うんだ、神父……"),"申し訳ないが、俺から言うことは何もねえ。","後で聞くぜ。すまねえ、神父さん。","失礼します、神父様……",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//Цена чахотки
			if (!CheckAttribute(npchar, "quest.Consumption") && CheckAttribute(pchar, "questTemp.Consumption.AskJuan"))
			{
				link.l1 = "教えてくれ、神父様、「フアン」という名前に聞き覚えはあるか？";
				link.l1.go = "Consumption";
			}
		break;
		
		//Цена чахотки
		case "Consumption":
			dialog.text = "そうだ、息子よ。この町にはフアンという名の信者がたくさんいるんだ。";
			link.l1 = "なるほど。ご迷惑をおかけしました、神父様……";
			link.l1.go = "exit";
			npchar.quest.Consumption = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
