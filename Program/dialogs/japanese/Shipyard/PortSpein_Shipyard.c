// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("何か質問があるか？","どうされましたか？お手伝いできることはありますか？"),"少し前に俺に質問しようとしたよな……","俺の造船所でも、この町のどこでも、こんなに好奇心旺盛な連中に会ったことはねえな。","質問が多いな。俺の仕事は船を造ることだ。さあ、それを片付けよう。","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("考え直した……","今は話すことは何もねえな。"),"うーん、俺の記憶はどこへ行っちまったんだ…","うーん、そうだな……","どうぞ……",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//Цена чахотки
			if (!CheckAttribute(npchar, "quest.Consumption") && CheckAttribute(pchar, "questTemp.Consumption.AskJuan"))
			{
				link.l1 = "「教えてくれ、フアンという名前に心当たりはあるか？」";
				link.l1.go = "Consumption";
			}
			if (!CheckAttribute(npchar, "quest.Guardoftruth") && CheckAttribute(pchar, "questTemp.Guardoftruth.Trinidad") && pchar.questTemp.Guardoftruth.Trinidad == "begin")
			{
				link.l1 = "旦那、1654年4月にミゲル・ディチョーソの指揮するフリゲート艦がここに来ていたんだ。その後すぐに姿を消したんだが、 何か覚えていないか？もしかするとディチョーソが修理のために立ち寄って、何か話していかなかったか…";
				link.l1.go = "guardoftruth";
			}
		break;
		
		//Цена чахотки
		case "Consumption":
			dialog.text = "いや。何もない。";
			link.l1 = "わかった。邪魔して悪かったな……";
			link.l1.go = "exit";
			npchar.quest.Consumption = "true";
		break;
		
		case "guardoftruth":
			dialog.text = "ふむ。いや、修理のために立ち寄ったこともないし、何も聞いていないな。もしそんなことがあったとしても、 俺には覚えがねえ。力になれなくてすまねえ、旦那。";
			link.l1 = "わかった。ありがとう、相棒…";
			link.l1.go = "exit";
			npchar.quest.guardoftruth = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
