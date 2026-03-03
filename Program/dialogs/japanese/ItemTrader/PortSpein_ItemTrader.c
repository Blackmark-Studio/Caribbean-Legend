// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("「どんな質問だ？」","何の用だ、 "+GetAddress_Form(NPChar)+"?"),"「また質問か」 "+GetAddress_Form(NPChar)+"...","質問ばかりだな……取引でもどうだ、 "+GetAddress_Form(NPChar)+"ん？","聞けよ、いつまで話すつもりだ？","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("今のところ質問はない……","すまねえ、今は話すことがねえんだ…"),"またしても、すまねえ…","本当にそろそろ取引する時かもしれねえな……","申し訳ないが、取引しよう…",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//Цена чахотки
			if (!CheckAttribute(npchar, "quest.Consumption") && CheckAttribute(pchar, "questTemp.Consumption.AskJuan"))
			{
				link.l1 = "聞いてくれ、「フアン」という名前に心当たりはあるか？";
				link.l1.go = "Consumption";
			}			
		break;
		
		//Цена чахотки
		case "Consumption":
			dialog.text = "いいや、違う……さて、もう邪魔しないでくれ、俺はかなり忙しいんだ……なんて馬鹿げた質問だ……";
			link.l1 = "なるほど。時間を無駄にしてすまねえ…";
			link.l1.go = "exit";
			npchar.quest.Consumption = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
