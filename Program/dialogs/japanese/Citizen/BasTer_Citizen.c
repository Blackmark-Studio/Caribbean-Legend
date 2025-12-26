// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
            dialog.text = RandPhraseSimple("どんな質問だ？","何の用だ？");
			link.l1 = RandPhraseSimple("考えが変わったんだ。","今は何も言うことはねえ。");
		    link.l1.go = "exit";
		break;
		
		case "info":
			dialog.text = LinkRandPhrase("誰に興味があるんだ？","誰のことだ？","「で、誰なんだ？」");
			link.l1 = "俺はモスクワ人のファディについてもっと知りたいんだ。";
			link.l1.go = "fadey";
			link.l2 = "誰もいない、気にするな。";
			link.l2.go = "new question";
		break;
		
		case "town":
			dialog.text = LinkRandPhrase("どこへ行きたいんだ？","何を探しているんだ？","一体何が必要なんだ？");
            link.l1 = "ファディの家はどこだ？";
			link.l1.go = "fadey_house";
			link.l2 = "他の話をしようぜ……";
			link.l2.go = "new question";
		break;
		
		case "fadey":
			dialog.text = RandPhraseSimple("ああ、あの人は偉いお方だぜ。地元の工場を持ってて、バステールの上流社会とも親しいんだ。強い訛りがあって、 酒が大好きなんだが……酔っぱらうことは決してねえんだよ。","あいつは大物で、総督の友人だ。ファディは地元の工場を持っている。北の国、ここからはるか遠くから来たんだ……国の名前すら俺は知らねえ。手はごつくて、ラム酒の樽一本を飲んでも酔わねえんだ。");
			link.l1 = "感謝する。";
			link.l1.go = "exit";
		break;
		
		case "fadey_house":
			dialog.text = RandPhraseSimple("桟橋からまっすぐ進んで広場に着いたら、左手にある家がファディの屋敷だ。","総督邸から広場を抜けて桟橋へ行くと、右手にある家がファディの屋敷だ。");
			link.l1 = "感謝する。";
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
