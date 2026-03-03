// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    ref sld;
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("「どんなご質問でございますか、」 "+GetSexPhrase("若い男","お嬢さん")+"?","「ご用件は何ですの、」 "+GetSexPhrase("「ハンサム」","「可愛い子」")+"？どうぞ、お尋ねください。"),"またご質問ですの？","うふふ、もしよろしければ――ご質問をどうぞ…",""+GetSexPhrase("ふむ、ご自分の好みの美女を選んではいかが？あなたのこと、ちょっと怪しく思えてきましたわ……","ふふん、ご自分のお気に入りの美女を選んでみてはいかが？あいにく、うちには男の子はいないのよ、うふふ…")+"","ブロック",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("気が変わりました、失礼します。","実は、やっぱりいいわ……"),"わたくし……失礼いたしました、今のところ質問はございませんわ。","おっしゃる通り、もう三度目ですね。失礼いたしました。","「また今度にしましょう、マダム。」",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
