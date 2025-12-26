// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
            dialog.text = RandPhraseSimple("どんな質問だ？","何の用だ？");
			link.l1 = RandPhraseSimple("気が変わったんだ。","今は何も言うことはねえ。");
		    link.l1.go = "exit";
		break;
		
		case "info":
			dialog.text = LinkRandPhrase("誰に興味があるんだ？","誰のことだ？","「で、誰なんだ？」");
			if (CheckAttribute(pchar, "questTemp.Saga"))
			{
				link.l1 = "ヤン・スヴェンソンについてもっと知りたいんだ。";
				link.l1.go = "svenson";
			}
			link.l2 = "話題を変えよう…";
			link.l2.go = "new question";
		break;
		
		case "town":
			dialog.text = LinkRandPhrase("どこへ行きたいんだ？","何を探しているんだ？","一体何が必要なんだ？");
			if (CheckAttribute(pchar, "questTemp.Saga"))
			{
				link.l1 = "ヤン・スヴェンソンの家はどこだ？";
				link.l1.go = "svenson_house";
			}
			link.l2 = "話題を変えよう…";
			link.l2.go = "new question";
		break;
		
		case "svenson":
			dialog.text = RandPhraseSimple("ああ、ヤン・スヴェンソンはとても重要な人物だよ。昔は西インディーズで一番イカした海賊だったし、 今でもまだまだ衰えちゃいねえ、はは！だが、あの頃はもう終わった。今は昔ほど活発じゃねえさ。屋敷を持ってて、 若い奥さんと一緒に暮らしてるし、総督の屋敷にもいつも歓迎される客なんだ。ヤンのところにはたくさんの客が来るぜ、 たいていは海賊仲間だ。","ヤン・スヴェンソンは西インディーズの伝説だぜ！森の悪魔――スペイン人どもは、あいつがここから奴らを追い払っていた時、そう呼んでたんだ。昔は有名な私掠船長だったが、 今じゃこの植民地の立派な市民さ。\nもっとも、今でも裏で“仕事”はしてるが、自分の手は汚さねえ。若い美女と結婚してからは、めったに家を出なくなったぜ。");
			link.l1 = "感謝する。";
			link.l1.go = "exit";
		break;
		
		case "svenson_house":
			dialog.text = RandPhraseSimple("桟橋からまっすぐ進んで広場に着いたら、噴水のそば右手の家がスヴェンソンの屋敷だ。","総督邸から広場を通って埠頭へ向かえ。噴水の近く、左手にある家がスヴェンソンの屋敷だ。");
			link.l1 = "感謝する。";
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
