// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("兵士に何か聞きたいことがあるのか？","兵士は人生のすべてを計画してる――警備に、せわしなく動き回ってな……どうした、俺に何か用か、 "+GetAddress_Form(NPChar)+"?"),"「兵士にくだらねえ質問なんかするんじゃねえぜ」 "+GetAddress_Form(NPChar)+"...","今日はこれで三度目だぜ、俺に質問しようとしたのは……","兵士の人生は楽じゃねえんだ、しかも今やお前らクズどもが俺をイライラさせてるんだよ……","ブロック",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("考えが変わったんだ……","今は話すことは何もねえぜ。"),"了解だ…","ああ、その通りだ、もうこれで三回目だぜ……","すまねえ……",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
