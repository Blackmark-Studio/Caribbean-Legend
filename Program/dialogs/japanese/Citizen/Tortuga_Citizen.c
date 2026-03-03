// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
            dialog.text = RandPhraseSimple("どんな質問だ？","何の用だ？");
			link.l1 = RandPhraseSimple("気が変わったんだ。","今は何も言うことはねえ。");
		    link.l1.go = "exit";
			
			// Rebbebion, "Путеводная звезда"
			if (CheckAttribute(pchar, "questTemp.PZ.TortugaCitizensAsk") && npchar.sex == "man")
			{
				link.l1 = "「ジョープ・ファン・デル・ヴィンクって奴を知ってたりしねえか？」";
				link.l1.go = "PZ_1";
			}
		break;
		
		case "info":
        // заменить на описание неких НПС, по квестам
			dialog.text = "俺が秘密情報部の手先だと思ってるのか "+NationNameGenitive(sti(NPChar.nation))+"?";
			link.l1 = "そうか……いや、違うな。じゃあ、達者でな。";
			link.l1.go = "exit";
			link.l2 = "他に質問はあるか？";
			link.l2.go = "new question";
		break;
		
		case "town":
        // заменить на описание как пройти, по квестам
			dialog.text = "俺が調査局に見えるか？知らねえよ、何も知らねえ。";

            link.l1 = "お前は本当にドジだな！消え失せろ。";
			link.l1.go = "exit";
			link.l2 = "他に何か質問はあるか？";
			link.l2.go = "new question";
		break;
		
		case "PZ_1":
			dialog.text = "そうだな、俺はあいつを個人的には知らねえが、時々ここで見かけるぜ。どうしてそんなこと聞くんだ？";
			link.l1 = "俺はあいつに直接荷物を届けるよう任されたんだ。\nでも誰もあいつのことを話したがらねえし、理由も分からねえ。\nあんたは知ってるか？あいつは悪い奴なのか？\n正直な意見を聞かせてくれるとありがたいぜ。";
			link.l1.go = "PZ_2";
		break;
		
		case "PZ_2":
			dialog.text = "また、俺たちは個人的に知り合いじゃねえから、ほとんど何も知らねえんだ。でもな、 あいつにはこの町に親しい友人がいて、よく一緒にいるのを見かけるぜ。そいつのところへ行きな、 話すかどうかはそいつが決めるだろう。友人の名前はロベール・マルテンだ。";
			link.l1 = "ロベール・マルテーヌと言ったな……そいつは何者だ？どこで会えるんだ？";
			link.l1.go = "PZ_3";
		break;
		
		case "PZ_3":
			dialog.text = "いろんな場所にいるが、今はうちの灯台にいるぜ――ひどい嵐の後でガレオン船を修理中なんだ。船の名前は『ヴォルティジュー』っていうんだ。";
			link.l1 = "本当にありがとうございます！どれほど助かったか、あなたには分からないでしょう。";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_CreateRobertMartin");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
