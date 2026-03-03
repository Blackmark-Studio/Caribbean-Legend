// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
            dialog.text = RandPhraseSimple("どんな質問だ？","何の用だ？");
			link.l1 = RandPhraseSimple("気が変わったんだ。","今は何も言うことはねえ。");
		    link.l1.go = "exit";
			//Цена чахотки
			if (!CheckAttribute(npchar, "quest.Consumption") && CheckAttribute(pchar, "questTemp.Consumption.AskJuan"))
			{
				link.l1 = "教えてくれ、「フアン」という名前に心当たりはあるか？";
				link.l1.go = "Consumption";
			}
			if (!CheckAttribute(npchar, "quest.Guardoftruth") && CheckAttribute(pchar, "questTemp.Guardoftruth.Trinidad") && pchar.questTemp.Guardoftruth.Trinidad == "begin")
			{
				link.l1 = "聞けよ、相棒、ミゲル・ディチョソが指揮するフリゲートが1654年4月にこの港に停泊したんだ。その日に奴は姿を消した。何か覚えてることはあるか？";
				link.l1.go = "guardoftruth";
			}
		break;
		
		case "info":
        // заменить на описание неких НПС, по квестам
			dialog.text = "俺があの秘密組織のために働いてると思うのか "+NationNameGenitive(sti(NPChar.nation))+"?";
			link.l1 = "うーん……いや。じゃあ、さらばだ。";
			link.l1.go = "exit";
			link.l2 = "他に質問はあるか？";
			link.l2.go = "new question";
		break;
		
		case "town":
        // заменить на описание как пройти, по квестам
			dialog.text = "俺が調査局に見えるか？知らねえよ、何も知らねえ。";

            link.l1 = "お前は本当にドジだな！消え失せろ。";
			link.l1.go = "exit";
			link.l2 = "他に質問はあるか？";
			link.l2.go = "new question";
		break;
		
		//Цена чахотки
		case "Consumption":
			dialog.text = "ふざけてるのか？どの植民地にもフアンが二十人はいるぜ！";
			link.l1 = "なるほど。ご迷惑をおかけしてすみません…";
			link.l1.go = "exit";
			npchar.quest.Consumption = "true";
		break;
		
		// Страж Истины
		case "guardoftruth":
			dialog.text = LinkRandPhrase("さあ、船長！そんなこと覚えてると思うのか？","すまねえな、旦那、それについては力になれねえんだ。","旦那、そんなくだらねえこと覚えてると思うのか？俺には他に悩みが山ほどあるんだよ。");
			link.l1 = LinkRandPhrase("そうか。迷惑をかけてすまねえな…","残念だな。じゃあな。","ああ、じゃあな……");
			link.l1.go = "exit";
			npchar.quest.guardoftruth = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
