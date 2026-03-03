// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("兵士に何か聞きたいことがあるのか？","兵士ってのは人生のすべてが決まってるんだ――見張りやら、せわしなく動き回ったりな……で、どうしたんだ、 "+GetAddress_Form(NPChar)+"?"),"「くだらねえ質問で兵士を煩わせるんじゃねえぞ」 "+GetAddress_Form(NPChar)+"...","今日はこれで三度目だぜ、お前が俺に質問しようとしたのは……","兵士の運命ってのは楽じゃねえんだ、しかも今やお前らクズどもが俺をイラつかせてるんだよ……","ブロック",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("気が変わった……","今は話すことは何もねえぜ。"),"了解だ…","ああ、その通りだな、もう三回目だぜ……","すまねえ……",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//Цена чахотки
			if (!CheckAttribute(npchar, "quest.Consumption") && CheckAttribute(pchar, "questTemp.Consumption.AskJuan"))
			{
				link.l1 = "教えてくれ、フアンという名前に心当たりはあるか？";
				link.l1.go = "Consumption";
			}
		break;
		
		//Цена чахотки
		case "Consumption":
			dialog.text = "いや。以上か？";
			link.l1 = "ああ。迷惑かけて悪いな、兵士……";
			link.l1.go = "exit";
			npchar.quest.Consumption = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
