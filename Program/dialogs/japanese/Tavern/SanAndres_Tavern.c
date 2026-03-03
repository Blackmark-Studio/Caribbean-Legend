// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("どんな質問があるんだ？","どうしたんだ、何か用か、 "+GetAddress_Form(NPChar)+"?"),"「さっき俺に何か質問しようとしたじゃねえか」 "+GetAddress_Form(NPChar)+"...","今日一日で、この質問を持ち出すのはこれで三度目だぞ…","また質問かい？","ブロック",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("考え直したぜ……","今は話すことは何もねえな。"),"うーん、俺の記憶はどこに行っちまったんだ……","ああ、本当にこれで三度目だな……","いや、何の質問だって…",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
