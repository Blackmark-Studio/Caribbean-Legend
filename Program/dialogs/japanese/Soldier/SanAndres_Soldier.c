// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("兵士に何か聞きたいことがあるのか？","兵士は自分の人生を全部決めてるんだ――見張りに、せわしなく動き回ってな……で、俺に何か用か、 "+GetAddress_Form(NPChar)+"?"),"「くだらねえ質問で兵士を困らせるんじゃねえぞ」 "+GetAddress_Form(NPChar)+"...","今日はこれで三度目だぜ、お前が俺に質問しようとしたのは……","兵士の運命は楽じゃねえ、しかも今やお前らクズどもが俺を気が狂いそうにさせてるんだ……","ブロック",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("考え直した……","今は話すことは何もねえぜ。"),"了解だ……","ああ、その通りだ、もう三回目だぜ……","すまねえ……",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
