// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    ref sld;
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("「どんなご質問でございますか、」 "+GetSexPhrase("若い男","お嬢さん")+"?","「ご用件は何でしょうか」 "+GetSexPhrase("「ハンサム」","かわい子ちゃん")+"？何でもお聞きください。"),"「またご質問ですの？」","うふふ、もしよろしければ――ご質問をどうぞ…",""+GetSexPhrase("ふむ、ご自分の好みの美女を選んではいかがですの？あなたのこと、ちょっと怪しく思えてきましたわ……","ふふん、ご自分のお気に入りの美女を選んでみてはいかが？残念ながら、ここには男の子はいないのよ、うふふ…")+"","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("気が変わりました、失礼します。","実は、やっぱりいいわ……"),"わたくし……失礼いたしました、今のところ質問はございませんわ。","おっしゃる通り、もう三度目ですわ。ごめんなさいませ。","「また次の機会にいたしましょう、マダム。」",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
