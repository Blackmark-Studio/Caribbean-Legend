// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("何の用だ？聞きたいことがあれば言え。","お聞きしましょう、ご質問は何ですか？"),"これは二度目のご質問でございます…","これで三度目のご質問でございます…","いつになったら終わるのだ？！私は植民地の仕事で忙しい身なのに、まだ私を煩わせるのか！","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("考え直しました……","今は駄目だ。場所も時も間違っている"),"「そうだな……だが、今ではなく後で……」","聞いてみよう……だが、少し後でな……","「申し訳ありません」 "+GetAddress_FormToNPC(NPChar)+"...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// Jason Дороже золота
			if (CheckAttribute(pchar, "questTemp.GoldenGirl") && pchar.questTemp.GoldenGirl == "antigua")
			{
				link.l1 = "閣下、マーキュリー号の失踪に関して、私がある情報を持っていることをお伝えしたく存じます。";
                link.l1.go = "G_Girl";
			}
		break;
		
		// Jason Дороже золота
		case "G_Girl":
			dialog.text = "「情報？また何についてだ？」";
			link.l1 = "ブリガンティン号でございます、閣下。郵便物を運んでおります。重要な書類などでございます。 調査の件は伺っておりますし、当然ながら、英国王室の忠実なる友人としてお力添えしたく存じます。";
			link.l1.go = "G_Girl_1";
		break;
		
		case "G_Girl_1":
			dialog.text = "素晴らしい！コートニー準男爵もあなたをお迎えできて喜ぶことでしょう！すぐに面会の手配をいたします。";
			link.l1 = "ありがとうございます、旦那。私は急いでおりますので、できるだけ早く済ませていただけるとありがたいです。";
			link.l1.go = "G_Girl_2";
		break;
		
		case "G_Girl_2":
			dialog.text = "ご心配なく、時間はたっぷりありますよ。\n衛兵たち！そやつを捕らえよ！";
			link.l1 = "「ありがとう…待て、何だと？これは冗談か！？」";
			link.l1.go = "G_Girl_3";
		break;
		
		case "G_Girl_3":
			DialogExit();
			GoldenGirl_AntiguaArest();
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
