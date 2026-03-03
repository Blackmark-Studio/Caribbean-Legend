// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("兵士にどんな質問があるんだ？","兵士ってのは人生のすべてが決まってるんだ――警備して、せかせか働いて……どうした、俺に何か用か、 "+GetAddress_Form(NPChar)+"?"),"「くだらねえ質問で兵士を困らせるんじゃねえぞ」 "+GetAddress_Form(NPChar)+"...","今日はこれで三度目だぜ、俺に質問しようとしたのは……","兵士の人生は楽じゃねえんだ、なのにお前らクズどもが俺をイライラさせやがって……","ブロック",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("気が変わった……","今は話すことは何もねえぜ。"),"了解だ…","ああ、その通りだ、もうこれで三度目だぜ……","すまねえ……",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
