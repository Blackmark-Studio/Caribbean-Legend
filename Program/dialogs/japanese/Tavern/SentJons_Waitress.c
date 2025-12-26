// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("「質問」 "+GetAddress_Form(NPChar)+"?","「どうした、何か用か」 "+GetAddress_Form(NPChar)+"?"),""+GetSexPhrase("ふん、何のつもりだ、 "+GetAddress_Form(NPChar)+"? ","また変な質問か？お嬢ちゃん、ラムでも飲んでな。")+"","今日一日で、その質問を持ち出すのはこれで三度目だぞ…"+GetSexPhrase(" これは好意のしるしか？","")+"","「また質問か、そうだろう。」 "+GetAddress_Form(NPChar)+"?","ブロック",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("気が変わった","今は話すことは何もねえんだ。"),"いやいや、美人さんよ…","いやだ。","いや、何の質問だって…",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;


	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
