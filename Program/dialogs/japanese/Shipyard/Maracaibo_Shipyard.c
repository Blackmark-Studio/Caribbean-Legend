// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("何か質問があるか？","どうされましたか？お手伝いできることはありますか？"),"少し前に俺に質問しようとしたよな……","俺の船渠でも、この町のどこでも、こんなに好奇心旺盛な連中に会ったことはねえよ。","なんだよ、その質問攻めは？俺の仕事は船を造ることだ。さっさとそっちを片付けようぜ。","ブロック",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("気が変わった……","今は話すことは何もないぜ。"),"うーん、俺の記憶はどこに行っちまったんだ……","うーん、そうだな……","どうぞ……",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
