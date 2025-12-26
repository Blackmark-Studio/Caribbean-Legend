// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("ご質問は何でしょうか？","ご用件は何でしょうか？"),"つい先ほど店の中で私に何か質問しようとしていましたね……","今日はそれで三度目の質問だ。私は商売をしなければならん、無意味なおしゃべりに付き合っている暇はないのだが…","まだ質問があるのか？それより取引でもしないか？","ブロック",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("考えが変わった……","今は話すことは何もない。"),"ああ、そうだ。その通りだ。店にいる間に……試してみたんだ……","はい、これが三つ目の質問ですね……","ふむ、取引ができるかもしれんな……",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;				
	}
	UnloadSegment(NPChar.FileDialog2);
}
