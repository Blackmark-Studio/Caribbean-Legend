// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
            dialog.text = NPCStringReactionRepeat(RandPhraseSimple("「どんな質問だ」 "+GetSexPhrase("息子よ","娘よ")+"?","何でも聞いてくれ、聞いてるぜ……"),"聞いているぞ、今話せ。 "+GetSexPhrase("息子よ","娘よ")+"...","「これで三度目だが、」 "+GetSexPhrase("息子よ","娘よ")+"、必要なものがあれば言ってくれ。","聖職者にはやるべきことが山ほどあるんだ、君は俺の邪魔をしているぞ。 "+GetSexPhrase("息子よ","娘よ")+"...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("気が変わった……","今は違うんだ、神父…。"),"申し訳ないが、俺には何も言うことはねえ。","後で聞くぜ。すまねえ、神父。","失礼します、神父様……",npchar,Dialog.CurrentNode);
		    link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
