// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("「質問だ」 "+GetAddress_Form(NPChar)+"?","「どうした、何か用か」 "+GetAddress_Form(NPChar)+"?"),""+GetSexPhrase("ふん、どういうつもりだ、 "+GetAddress_Form(NPChar)+"? ","また変な質問かい？お嬢ちゃん、ラムでも飲んでな。")+"","今日一日で、その質問を持ち出すのはこれで三度目だぞ…"+GetSexPhrase(" これは愛情のしるしか？","")+"","「また質問か、そうだろう」 "+GetAddress_Form(NPChar)+"?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("考えが変わった","今は話すことは何もねえぜ。"),"いやいや、美しいお嬢さん…","ありえねえよ、お嬢ちゃん…","いや、何の質問だって…",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;


	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
