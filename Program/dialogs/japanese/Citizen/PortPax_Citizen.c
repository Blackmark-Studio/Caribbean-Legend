// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
            dialog.text = RandPhraseSimple("どんな質問だ？","何の用だ？");
			link.l1 = RandPhraseSimple("気が変わった。","今は何も言うことはねえ。");
		    link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "portprince" && !CheckAttribute(npchar, "quest.Guardoftruth"))
			{
				link.l1 = "「教えてくれ、」 "+GetAddress_FormToNPC(NPChar)+"「最近、『サンタ・マルガリータ』というガレオン船がここに来ていたか？もしかして私掠船の戦利品としてか？」";
                link.l1.go = "guardoftruth";
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
			dialog.text = "俺が調査局に見えるか？知らねえよ、何も知らねえんだ。";

            link.l1 = "お前は本当にドジだな！さっさと失せろ。";
			link.l1.go = "exit";
			link.l2 = "他に質問はあるか？";
			link.l2.go = "new question";
		break;
		
		case "guardoftruth":
			dialog.text = LinkRandPhrase("いいや、その名前のガレオン船は覚えがねえな。ここじゃあんなでけえ船はめったに見かけねえんだよ。","何だって？ガレオン船？ここに？全然知らねえよ。","いいえ、旦那、その船は最近ここに停泊していません。少なくとも、俺の記憶にはありませんね。");
			link.l1 = LinkRandPhrase("……わかったぜ……","よし……","なるほど、残念だな……");
			link.l1.go = "exit";
			npchar.quest.Guardoftruth = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
