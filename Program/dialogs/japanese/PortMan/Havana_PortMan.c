// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("どんな質問だ？","何の用だ、 "+GetAddress_Form(NPChar)+"?"),"もうすでに俺に質問しようとしたじゃねえか "+GetAddress_Form(NPChar)+"...","今日はこれで三度目の質問だな……","港の用件について何も話すことがないなら、俺に質問して邪魔しないでくれ。","ブロック",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("考え直した。","話すことは何もねえ。"),"気にするな。","「本当に、もう三度目だな……」","悪いが、今のところ港の用事には興味がないんだ。",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.Slavetrader == "FindRatHavana")
            {
                link.l1 = "ごきげんよう。『という名のコルベットについて知りたいのですが"+pchar.questTemp.Slavetrader.ShipName+"「フランソワ・ゴンティエ」指揮下で。";
                link.l1.go = "Havana_ratP_1";
			}
			// калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "graveyard" && !CheckAttribute(npchar, "quest.caleuche"))
			{
				link.l1 = "失礼ですが、ジョアキム・メリマンという名の男があなたの港に到着しましたか？中年の旦那で、ポルトガル人、 口ひげと山羊ひげがあり、鋭い目をした人物ですか？";
				link.l1.go = "caleuche";
			}
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "jewelry_3" && !CheckAttribute(npchar, "quest.Mtraxx"))
			{
				link.l1 = "「カンタブロ」という名の船に興味があるんだ。その船長エスベルド・カバナスを個人的な用件で探しているんだが、 手を貸してくれないか？";
				link.l1.go = "mtraxx";
			}
		break;
		
		case "Havana_ratP_1":
			dialog.text = NPCStringReactionRepeat("ああ、彼はここにいたよ。しかし、もう出て行った。彼についてはうちの酒場の主人に聞いてくれ、 上の階の部屋を借りていたからな。","この件についてはすでに尋ねられ、私は答えたはずだ。","言っただろう、ゴンティエのことはもう聞かれたぜ……","俺にかまうなって言ってるだろう！","block",0,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("ありがとう。そうするよ。","ふむ、そうだな……","ああ、本当に頼んだんだ…","「失礼」 "+npchar.name+"...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
		
		// калеуче
		case "caleuche":
			dialog.text = "彼については何も話せねえ。たとえ到着していたとしても、どこにも登録されてねえんだ。";
			link.l1 = "そうか……残念だな……よし、引き続き探してみるぜ……";
			link.l1.go = "exit";
			npchar.quest.caleuche = "true";
		break;
		
		// Addon 2016-1 Jason пиратская линейка
		case "mtraxx":
			dialog.text = "そうだな……スクーナー船『カンタヴロ』は二日前に哨戒任務で出航した……だが、行き先は記録されていない。軍艦だから、目的地を知っているのは船長と砦の司令官だけだ。 もっと詳しく知りたければ、直接司令官に話を聞くといい。砦に行けば会えるはずだ。\n残念だが、私にできるのはここまでだ。";
			link.l1 = "なるほど。では、お時間をいただきありがとうございました……";
			link.l1.go = "exit";
			npchar.quest.Mtraxx = "true";
			AddQuestRecord("Roger_1", "5");
			DelLandQuestMark(npchar);
			AddLandQuestMark(characterFromId("Havana_tavernkeeper"), "questmarkmain");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
