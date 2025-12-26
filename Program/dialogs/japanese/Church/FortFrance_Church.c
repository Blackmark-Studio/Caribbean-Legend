// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("「どんな質問だ、」 "+GetSexPhrase("息子よ","娘よ")+"?","何でも聞いてくれ、聞いてるぜ…"),"聞いているぞ、今話せ。 "+GetSexPhrase("息子よ","娘よ")+"...","「三度目だが、」 "+GetSexPhrase("息子よ","娘よ")+"、必要なものがあれば言ってくれ。","「聖職者にはやることが山ほどあるんだ、あんたは俺の邪魔をしてるぞ。」 "+GetSexPhrase("息子よ","娘よ")+"...","ブロック",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("気が変わったんだ……","今はまだです、神父……"),"申し訳ないが、俺から言うことは何もねえ。","後で聞くぜ。すまねえな、神父。","失礼します、神父様……",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// Jason Долго и счастливо
			if (CheckAttribute(pchar, "questTemp.LongHappy") && pchar.questTemp.LongHappy == "choose" && !CheckAttribute(npchar, "quest.LongHappy"))
			{
				link.l1 = "聖父様、修道院長ブノワを探しています。急用があるんです。どこにいるか教えていただけますか？";
				link.l1.go = "LH_church";
			}
		break;
		
		// Jason Долго и счастливо
		case "LH_church":
			dialog.text = "ベノワ院長は新世界のスペイン・カトリック宣教団の代表者たちと教会の用事で町を離れました。\n詳しいことは分かりませんが、ベノワ院長が長く不在なので、交渉が長引いているか、 道中で何かあったのかもしれません。\n皆、不安でなりませんが、ただ祈り、知らせを待つしかありません。";
			link.l1 = "すべてが簡単にいくとは限らねえ。神父様、ベノワ院長が正確にどこへ行ったのか教えてくれねえか？ できるだけ早く見つける必要があるんだ。";
			link.l1.go = "LH_church_1";
		break;
		
		case "LH_church_1":
			dialog.text = "申し訳ないが、息子よ、私にはできぬ。私の知る限り、 ブノワ院長は新スペインの司教と異端審問所の首席司祭ヴィンチェント・パロッティ神父と交渉に向かったが、 会合がどこで行われるかは明かしていなかったのだ。";
			link.l1 = "それで十分です、神父様、ありがとうございます。パロッティ神父には何らかの形で心当たりがあります……サンティアゴで探してみます。";
			link.l1.go = "LH_church_2";
		break;
		
		case "LH_church_2":
			DialogExit();
			npchar.quest.LongHappy = "true";
			LongHappy_GoToSantiago();
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
