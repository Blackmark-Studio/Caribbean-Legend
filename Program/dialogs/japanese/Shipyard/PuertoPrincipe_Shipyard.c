// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("どんな質問があるんだ？","ご用件は何でしょうか？"),"少し前に俺に質問しようとしたよな……","俺の船渠でも、この町のどこでも、こんなに好奇心旺盛な連中に会ったことはねえな。","質問が多いな。俺の仕事は船を造ることだぜ。さっさとそれを片付けよう。","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("考えが変わった……","今は話すことは何もねえな。"),"うーん、俺の記憶はどこへ行っちまったんだ……","ふむ、そうだな……","どうぞ……",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
