// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("ご質問は何でしょうか？","ご用件は何でしょうか？"),"少し前に私に質問しようとしましたね……","トルトゥーガの店でそんな質問をされたのは、久しぶりだな……","「質問、質問、また質問……」","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("考えが変わった……","今は話すことは何もない。"),"うーん、俺の記憶はどこへ行っちまったんだ……","よし、ずいぶん久しぶりだな。","また質問かよ……",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "tortuga2")
			{
				link.l1 = "聞いてくれ、ガイウス・マルシェを探しているんだ。私の耳に入った話では、奴は私掠活動に関わっていて、 スペインから見事なガレオン船を奪い取った交渉上手になったそうだ。 奴が取引用に何か商品をお前から買ったことはあるか？";
                link.l1.go = "guardoftruth";
			}
		break;
		
		case "guardoftruth":
			dialog.text = "ガイウス・マルシェ？ああ、もちろん覚えているよ！\nでも、彼は何も買わなかった。貨物運送に自分の船を提供してくれたんだ。 ちょうど広い船倉を持つ船が必要だったんだよ――原皮の大きなロットを運ぶためにな。";
			link.l1 = "「それで、荷下ろし場所はどこだったんだ？」";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "フィリップスブルフ、セント・マーチン。";
			link.l1 = "結構です。ありがとうございます、本当に助かりました！";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "いつでもどうぞ、船長。好きな時に私の店に立ち寄ってください！";
			link.l1 = "...";
			link.l1.go = "exit";
			AddQuestRecord("Guardoftruth", "10");
			pchar.questTemp.Guardoftruth = "maarten";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}
