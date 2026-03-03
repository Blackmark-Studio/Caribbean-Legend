// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("どんな質問だ？","何の用だ、 "+GetAddress_Form(NPChar)+"?"),"もうすでに俺に質問しようとしたじゃねえか "+GetAddress_Form(NPChar)+"...","今日はこれで三度目の質問だな……","港の用事について何も話すことがないなら、くだらない質問で俺を煩わせるな。","ブロック",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("考えを変えた。","話すことは何もねえ。"),"気にするな。","確かに、これで三度目だな……","悪いが、今のところ港の用事には興味がないんだ。",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			
			if (pchar.questTemp.Slavetrader == "FindRatJamaica")
            {
                link.l1 = "ごきげんよう。フランソワ・ゴンティエ船長はここで登録していますか？彼はポルトベロから『』 というコルベットで航海していましたが\n"+pchar.questTemp.Slavetrader.ShipName+"『。』";
                link.l1.go = "Jamaica_ratPP_1";
            }
			
		break;
		
		case "Jamaica_ratPP_1":
			dialog.text = NPCStringReactionRepeat("いいや、まだだ。それにコルベット『"+pchar.questTemp.Slavetrader.ShipName+"「」はポートロイヤルで目撃されていない。","この件についてはすでに聞かれたし、俺はもう答えたぜ。","このゴンティエとかいう男については、もうすでに聞かれたと申しましたぞ。","お願いだから、仕事の邪魔をしないでくれ！","ブロック",0,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("ありがとう。引き続き探してみる。","ふむ、そうだな……","ああ、本当に頼んだんだ……","「失礼」 "+npchar.name+"...",npchar,Dialog.CurrentNode);
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
