// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = RandPhraseSimple("どんな質問だ？","何の用だ？");
			link.l1 = RandPhraseSimple("気が変わったんだ。","今は何も言うことはねえ。");
			link.l1.go = "exit";
			//Бремя гасконца
			if (CheckAttribute(pchar, "questTemp.Sharlie.Citcount") && !CheckAttribute(npchar, "quest.Sharlie"))
			{
				link.l1 = "「失礼」 "+GetAddress_FormToNPC(NPChar)+" ミシェル・ド・モンペールがどこにいるか教えてくれないか？この町にいると聞いたんだ。";
				link.l1.go = "Sharlie";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "findskiper" && !CheckAttribute(npchar, "quest.Sharlie1"))
			{
				link.l1 = "「聞け、」 "+GetAddress_FormToNPC(NPChar)+"……ちょっと聞きたいことがあるんだが……俺の船で働いてくれる航海士を探してるんだ。誰か心当たりはないか？";
				link.l1.go = "Sharlie_1";
			}
			//Бремя гасконца
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

            link.l1 = "お前は本当にドジだな！消えろ。";
			link.l1.go = "exit";
			link.l2 = "他に質問はあるか？";
			link.l2.go = "new question";
		break;
		
		//--> Бремя гасконца
		case "Sharlie":
			if (sti(pchar.questTemp.Sharlie.Citcount) == 3)
			{
				dialog.text = "ふむ……そんな質問を平然とするあたり、あんたはここに来たばかりなんじゃねえか……面倒ごとが嫌なら、やめておいたほうがいいぜ。修道院長に話してみな、あんたの目を覚まさせてくれるかもな。 教会にいるぜ。";
				link.l1 = "なるほど……";
				link.l1.go = "exit";
				AddDialogExitQuest("Sharlie_SetBenua");
				DelLandQuestMark(characterFromId("FortFrance_Mayor"));
			}
			else
			{
				dialog.text = LinkRandPhrase("いや、そいつのことは聞いたことがねえな。","手伝えねえ、俺にはやることがあるんだ。","誰だ？聞き覚えがねえな。じゃあ、俺は行くぜ。");
				link.l1 = "なるほど……それじゃあ、俺は行くぜ。 ";
				link.l1.go = "exit";
				npchar.quest.Sharlie = "true";
			}
		break;
		
		case "Sharlie_1":
			dialog.text = LinkRandPhrase("いいや、航海士なんて知らねえな。","俺にはやることがあるんだ。他の奴に聞いてくれ……","残念だが、俺には手伝えねえ。誰のことも知らねえんだ。");
			link.l1 = "なるほど。他を当たってみるぜ。";
			link.l1.go = "exit";
			npchar.quest.Sharlie1 = "true";
			npchar.dialog.currentnode = "first time";
		break;
		//<-- Бремя Гасконца
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
