// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
            dialog.text = RandPhraseSimple("どんな質問だ？","何の用だ？");
			link.l1 = RandPhraseSimple("気が変わったんだ。","今はもう話すことはねえ。");
		    link.l1.go = "exit";
		break;
		
		case "info":
        // заменить на описание неких НПС, по квестам
			dialog.text = "俺があの秘密組織のために働いてると思うのか "+NationNameGenitive(sti(NPChar.nation))+"?";
			link.l1 = "そうか……いや、違うな。じゃあ、達者でな。";
			link.l1.go = "exit";
			link.l2 = "他に質問はあるか？";
			link.l2.go = "new question";
		break;
		
		case "town":
        // заменить на описание как пройти, по квестам
			dialog.text = "俺が調査局に見えるか？知らねえよ、何も知らねえ。";

            link.l1 = "お前は本当にドジだな！さっさと消えろ。";
			link.l1.go = "exit";
			link.l2 = "他に質問はあるか？";
			link.l2.go = "new question";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
