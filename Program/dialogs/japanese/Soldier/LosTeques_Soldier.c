// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("兵士に何か聞きたいことがあるのか？","兵士ってのは人生のすべてが決まってるんだ――見張りに、せかせか働いて……で、俺に何か用か、 "+GetAddress_Form(NPChar)+"?"),"「兵士にくだらねえ質問なんかするんじゃねえぜ」 "+GetAddress_Form(NPChar)+"...","今日はこれで三度目だぜ、お前が俺に質問しようとしたのは……","兵士の人生は楽じゃねえ、しかも今じゃお前らクズどもが俺をイライラさせてるんだ……","ブロック",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("考えが変わった……","今は話すことは何もねえんだ。"),"了解だ…","ああ、そうだな、もうこれで三度目だぜ……","すまねえ……",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
