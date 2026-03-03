// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("どのようなご質問がありますか？","ご用件をお伺いしましょうか？"),"「その質問は少し前にも私に尋ねましたね…」","ああ、当ててみようか……また同じところをぐるぐる回ってるんじゃねえか？","聞きなさい、ここで財務を担当しているのは私です、質問にはお答えしません…","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("考えが変わった……","今は話すことは何もありません。"),"うーん、俺の記憶はどこへ行っちまったんだ…","ご明察です、申し訳ありません……","承知しました…",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			
			// --> Sinistra Длинные тени старых грехов	
			if (CheckAttribute(pchar, "questTemp.DTSG_depozit"))
			{
				link.l1 = "教えてくれ、大佐が君のところに来たか？俺への報酬を用意してあると言っていたんだ。";
				link.l1.go = "DTSG_depozit_1";
			}
			// <-- Длинные тени старых грехов
		break;
		
		// --> Sinistra Длинные тени старых грехов	
		case "DTSG_depozit_1":
			dialog.text = "どの大佐のことだ？";
			link.l1 = "「トーマス・リンチ。」";
			link.l1.go = "DTSG_depozit_2";
		break;
		
		case "DTSG_depozit_2":
			dialog.text = "静かに話してください！あの男を知っています。ええ、彼は来ました。報酬は用意してあります、船長。";
			link.l1 = "「それで、いくらあるんですか？」";
			link.l1.go = "DTSG_depozit_3";
		break;
		
		case "DTSG_depozit_3":
			dialog.text = "ちょうど金貨一万枚です。ペソは一枚もありません――すべて金貨です。";
			link.l1 = "少なくとも銀貨三十枚じゃないだけマシだな……";
			link.l1.go = "DTSG_depozit_4";
			AddItems(pchar, "chest", 70);
			Log_Info("You have received 70 chests");
			PlaySound("interface\important_item.wav");
		break;
		
		case "DTSG_depozit_4":
			dialog.text = "「今のは何だ？」";
			link.l1 = "ああ、なんでもありません……ありがとうございます。さようなら。";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.DTSG_depozit");
		break;
		// <-- Длинные тени старых грехов
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
