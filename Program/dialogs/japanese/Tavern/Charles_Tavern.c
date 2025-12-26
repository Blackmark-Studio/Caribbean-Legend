// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("何か質問があるか？","どうなさいましたか、 "+GetAddress_Form(NPChar)+"?"),"「ついさっき俺に質問しようとしたじゃねえか、」 "+GetAddress_Form(NPChar)+"...","今日一日で、この質問を持ち出すのはこれで三度目だぞ……","「まだ質問があるのか？」","ブロック",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("気が変わったんだ……","今は話すことは何もねえな。"),"うーん、俺の記憶はどこへ行っちまったんだ……","「ああ、本当にこれで三度目だな……」","いや、何の質問だってんだ…",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// Сага
			if(CheckAttribute(pchar, "questTemp.Saga.BarbTemptation") && pchar.questTemp.Saga.BarbTemptation == "valet")
			{
				link.l1 = "「ヴァレと呼ばれている男を探しているんだ。あんた、知ってるか？」";
				link.l1.go = "valet_1";
				link.l2 = "「『マーリン』という名のポラッカ船の船長を探しているんだ。どこにいるか教えてくれないか？」";
				link.l2.go = "valet_2";
			}
		break;
		
		case "valet_1":
			dialog.text = NPCStringReactionRepeat("いや、知らねえな。だから、俺にできることは何もねえぜ。","もう知らねえって言っただろう！","酔ってるのか、それともふざけてるだけか？","ほっといてくれ！","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("なるほど。残念だな……","それは残念だ。覚えてると思ったんだが……","俺は酔っちゃいねえ！ただしつこいだけだ…","ふむ……",npchar,Dialog.CurrentNode); 
			link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);
		break;
		
		case "valet_2":
			dialog.text = NPCStringReactionRepeat("ああ、デイビッド・ファックマンさん！彼は造船所の近くに家を借りているぜ。そこで探してみな。","もう答えたぜ。お前、本当に俺の話を聞いてたのか？","酔ってるのか、それともふざけてるだけか？","ほっといてくれ！","ブロック",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("ありがとう！","ああ、すまねえ。","俺は酔ってねえ！ただしつこいだけだ…","ふむ……",npchar,Dialog.CurrentNode); 
			link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
