// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    ref sld;
    int i, tempQty, chComp, iShip, iBaseType;
    string tempStr;
    switch (Dialog.CurrentNode)
	{
		case "quests":
			//Португалец
			if (CheckAttribute(pchar, "questTemp.Portugal.Villemstad") && pchar.location == "villemstad_townhall")
			{
				dialog.text = RandPhraseSimple("「どのようなご質問でしょうか？」","何をご所望ですか？");
				link.l1 = "オランダ西インド会社が有名な海賊バルトロメウ・ポルトガル人の首に高額な懸賞金をかけていることは存じております。 私が彼を捕らえることに成功いたしました。現在、彼は私の船の船倉におり、当局に引き渡す準備ができております。";
				link.l1.go = "Portugal";
				break;
			}
            dialog.text = RandPhraseSimple("「どんな質問ですか？」","ご用件は何でしょうか？");
			link.l1 = RandPhraseSimple("「特に重要なことはありません、旦那。」","申し訳ありませんが、私から申し上げることはございません。");
		    link.l1.go = "exit";
		break;
		
		case "work_1":  // работа на благо короны - линейка нации
			if (CheckAttribute(npchar, "notQuestLine"))
			{
                dialog.text = "残念ですが、あなたに仕事を任せるわけにはいきません。今はご一緒したい相手ではありませんので。ごきげんよう。";
                link.l1 = "本気じゃないだろう……まあ、仕方ない。";
                link.l1.go = "exit";
				break;
			}                   
		break;
		
		//Португалец
		case "Portugal":
			dialog.text = "バルト・ザ・ポルトガル人だと！？奴を捕らえたのか？生きているのか？";
			link.l1 = "あなたが彼を殺す必要がないことは分かっている。彼は生きている。そうさせるために、私は大変な努力をしたんだ！";
			link.l1.go = "Portugal_1";
		break;
		
		case "Portugal_1":
			dialog.text = "素晴らしい！これで奴はすべてを話すだろう……旦那、囚人の移送準備をしなさい。すぐに軍用バーク船をあなたの船へ送ります。 ";
			link.l1 = "まずは報酬について話したいのですが、旦那……よろしいでしょうか。";
			link.l1.go = "Portugal_2";
		break;
		
		case "Portugal_2":
			dialog.text = "報酬のことは心配なさらずに、船長。必ずお渡しします。 バルトロメウ・ザ・ポルトガル人の首には一千五百ドゥブロンの賞金をかけました。\n中尉！船長に報酬を持ってきなさい！";
			link.l1 = "ふむ……ヒューゴが二千ドゥブロンについて俺に嘘をついたようだな……まあ、いいさ。";
			link.l1.go = "Portugal_3";
		break;
		
		case "Portugal_3":
			TakeNItems(pchar, "gold_dublon", 1500);
			Log_Info("You have received 1500 doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "さて、船長、ポルトガル人を会社に引き渡していただけますか。\nぜひとも彼と話をしたくてたまりません。";
			link.l1 = "かしこまりました、旦那。バルク船を私の船に送ってください。";
			link.l1.go = "Portugal_4";
		break;
		
		case "Portugal_4":
			DialogExit();
			DoQuestReloadToLocation("Villemstad_town", "reload", "reload1", "Portugal_Final");
			DeleteAttribute(pchar, "questTemp.Portugal.Villemstad");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
