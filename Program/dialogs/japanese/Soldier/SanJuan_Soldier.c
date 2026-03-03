// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("兵士にどんな質問があるんだ？","兵士ってのは人生のすべてが決まってるんだ――見張りに、せわしなく動き回ってな……何か用か、 "+GetAddress_Form(NPChar)+"?"),"「くだらねえ質問で兵士を困らせるんじゃねえぞ」 "+GetAddress_Form(NPChar)+"...","今日はこれで三度目だぜ、お前が俺に質問しようとしたのは……","兵士の人生は楽じゃねえんだ、なのにお前らクズどもが俺をイラつかせやがって……","ブロック",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("考えが変わったんだ……","今は話すことは何もねえな。"),"了解だ…","ああ、その通りだ、もう三回目だな……","すまねえ……",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
