// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("何の用だ？聞きたいことがあれば言え。","お聞きします、どのようなご質問でしょうか？"),"これで二度目のご質問でございますね…","これで三度目のご質問ですね……","いつまで続くのだ！？私は植民地の案件で忙しい身なのだ、まだ私を煩わせるつもりか！","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("考えを変えました、申し訳ありません。","今は駄目だ。場所も時も間違っている。"),"確かに、今は申し上げることがございません、申し訳ありません。","後でお伺いします。","「申し訳ありません」 "+GetAddress_FormToNPC(NPChar)+"...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (!CheckAttribute(npchar, "quest.Guardoftruth") && CheckAttribute(pchar, "questTemp.Guardoftruth.Trinidad") && pchar.questTemp.Guardoftruth.Trinidad == "begin")
			{
				link.l1 = "閣下、1654年4月にミゲル・ディチョソの指揮するフリゲート艦がございました。それ以来、彼は行方不明でございます。 何か心当たりはございますか？もしかすると、閣下のもとを訪れ、お話しされたことがあるのでは……";
				link.l1.go = "guardoftruth";
			}
		break;
		
		case "guardoftruth":
			dialog.text = "はい、その男のことは覚えております。しかし、彼についての詳細は思い出せません。ここに来て、 それからすぐに去っていきました。お力にはなれません。";
			link.l1 = "なるほど。ご迷惑をおかけしました。";
			link.l1.go = "exit";
			npchar.quest.guardoftruth = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
