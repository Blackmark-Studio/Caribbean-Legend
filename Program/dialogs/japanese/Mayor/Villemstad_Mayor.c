// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("何の用だ？聞きたいことがあれば言え。","お聞きしましょう、ご質問は何でございますか？"),"これで二度目のご質問でございます…","これで三度目のご質問でございますが……","いつになったら終わるのだ！？私は植民地の案件で忙しい身なのに、まだ私を煩わせるつもりか！","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("考えが変わりました、申し訳ありません。","今は駄目だ。場所も時も間違っている。"),"確かに、今は申し上げることがございません、申し訳ありません。","後で伺います。","申し訳ありません。 "+GetAddress_FormToNPC(NPChar)+"...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//Португалец
			if (CheckAttribute(pchar, "questTemp.Portugal.Villemstad"))
			{
				link.l1 = "私はオランダ西インド会社がある海賊――ポルトガル人のバルトロメオ――の首に懸賞金をかけていることを存じております。\n私が彼を捕らえることに成功いたしました。現在、彼は私の船の貨物室に拘束されており、 当局に引き渡す準備ができております。";
                link.l1.go = "Portugeze";
			}
		break;

		case "Cupture_after":
            dialog.text = RandPhraseSimple("すでにすべて奪ったではありませんか。まだ何を望むのですか？","「まだお取りにならなかった物が何か残っておりますか？」");
            link.l1 = RandPhraseSimple("ちょっと見て回っているだけです……","念のため確認しているだけだ、何か取り忘れたかもしれないからな…");
            link.l1.go = "exit";
            NextDiag.TempNode = "Cupture_after";
		break;
		
		//Португалец
		case "Portugeze":
			dialog.text = "バルト・ザ・ポルトガル人だと！？生きているのか！？";
			link.l1 = "彼が死んでしまってはあなたにとって何の役にも立たないことは分かっています。彼は生きていますし、くそっ、 私も彼を生かしておくために自制しなければなりませんでした！";
			link.l1.go = "Portugeze_1";
		break;
		
		case "Portugeze_1":
			dialog.text = "素晴らしい！これで奴はすべてを話すでしょう……旦那、囚人の移送準備をなさいませ。すぐに軍用バーク船をあなたの船へ送ります。 ";
			link.l1 = "まずは報酬についてお話ししたいのですが、旦那、よろしければ。";
			link.l1.go = "Portugeze_2";
		break;
		
		case "Portugeze_2":
			dialog.text = "ご褒美のことはご心配なく、旦那。必ずお渡しいたします。 バルトロメオ・ザ・ポルトガルの首には千五百ドゥブロンの賞金をかけております。\n中尉！船長に報酬を持ってきなさい！";
			link.l1 = "ふむ……ユーゴは二千ドゥブロンだと言っていたが……まあ、いいだろう。";
			link.l1.go = "Portugeze_3";
		break;
		
		case "Portugeze_3":
			TakeNItems(pchar, "gold_dublon", 1500);
			Log_Info("You have received 1500 doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "さて、旦那、ポルトガル人を会社に引き渡していただけますか？\nぜひとも彼と話をしたいのです。";
			link.l1 = "かしこまりました、旦那。バーク船を私の船へ送ってください。";
			link.l1.go = "Portugeze_4";
		break;
		
		case "Portugeze_4":
			DialogExit();
			DoQuestReloadToLocation("Villemstad_town", "reload", "reload1", "Portugal_Final");
			DeleteAttribute(pchar, "questTemp.Portugal.Villemstad");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
