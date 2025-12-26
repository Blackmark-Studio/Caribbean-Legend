// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("何か質問があるか？","どうされましたか？"),"少し前に俺に何か質問しようとしたよな……","俺の造船所でも、この町のどこでも、こんなに好奇心旺盛な連中に会ったことはねえな。","質問が多いな。俺の仕事は船を造ることだぜ。さっさとそれを片付けよう。","ブロック",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("考え直した……","今は話すことは何もねえぜ。"),"うーん、俺の記憶はどこへ行っちまったんだ……","ふむ、そうだな……","どうぞ……",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "graveyard" && !CheckAttribute(npchar, "quest.caleuche"))
			{
				link.l1 = "聞いてくれ、最近ここにジョアキム・メリマンという男が来なかったか？中年の旦那で、ポルトガル人、 口ひげとあごひげがあって、鋭い目をしてるんだ。もしかして船を買いたがってたかもしれないんだが？";
				link.l1.go = "caleuche";
			}
		break;
		
		// калеуче
		case "caleuche":
			dialog.text = "いや、旦那。そんな客は見たことねえな。";
			link.l1 = "なるほど。残念だ。じゃあ、引き続き探してみるとするか……";
			link.l1.go = "exit";
			npchar.quest.caleuche = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
