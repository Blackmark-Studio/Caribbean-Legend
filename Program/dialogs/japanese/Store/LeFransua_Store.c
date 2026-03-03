// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("ご質問は何でしょうか？","ご用件は何でしょうか？"),"少し前に私の店にいた時、あなたは私に何か質問しようとしましたね……","今日はこれで三度目の質問だ。私は商売をしなければならん、無駄話に付き合っている暇はないんだが…","まだ質問があるのか？取引でもしないか？","ブロック",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("考えが変わった……","今は話すことは何もない。"),"ああ、そうだ。その通りだ。俺は試したんだ…店にいる間に…","ああ、これが三つ目の質問だな……","ふむ、取引ができるかもしれませんね…",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}
