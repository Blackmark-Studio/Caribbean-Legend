// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("兵士に何か聞きたいことがあるのか？","兵士ってのは人生のすべてが決まってるんだ――見張りに、せわしなく動き回ってな……で、俺に何か用か、 "+GetAddress_Form(NPChar)+"?"),"「くだらねえ質問で兵士を困らせるんじゃねえぞ」 "+GetAddress_Form(NPChar)+"...","今日はもう三度目だぜ、お前が俺に質問しようとするのは……","兵士の人生は楽じゃねえんだ、なのに今じゃお前らクズどもが俺を狂わせやがる……","ブロック",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("考えが変わった……","今は話すことは何もねえんだ。"),"了解だ…","ああ、その通りだ、もう三回目だな……","すまねえ……",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
