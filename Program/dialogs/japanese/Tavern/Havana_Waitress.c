// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("「質問」 "+GetAddress_Form(NPChar)+"?","「どうした、何か用か」 "+GetAddress_Form(NPChar)+"?"),""+GetSexPhrase("ふん、何のつもりだ、 "+GetAddress_Form(NPChar)+"? ","また変な質問かい？お嬢ちゃん、ラムでも飲んでなよ…")+"","この一日中、これで三度目だぜ、その質問を持ち出すのは……"+GetSexPhrase(" これは愛情のしるしか？","")+"","「また質問か、そうだろう」 "+GetAddress_Form(NPChar)+"?","ブロック",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("気が変わった","今は話すことは何もねえぜ。"),"いや、美しくねえ……","無理だよ、お嬢ちゃん…","いや、何の質問だって…",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
