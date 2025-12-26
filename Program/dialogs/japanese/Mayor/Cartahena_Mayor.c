// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("何の用だ？聞きたいことがあれば言え。","お聞きしましょう、ご質問は何でございますか？"),"これで二度目のご質問でございます…","これで三度目のご質問でございます…","いつまで続くのですか！？私は植民地の案件で多忙な身でございますのに、まだ私を煩わせるのですか！","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("考え直しました、申し訳ありません。","今は駄目だ。場所も時も間違っている。"),"確かに、今は申し上げることがございません、申し訳ありません。","後でお尋ねします。","申し訳ございません。 "+GetAddress_FormToNPC(NPChar)+"...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
