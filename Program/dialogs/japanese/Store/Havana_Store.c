// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("さあ、用件は何だ？","ちょうどその話をしていたところだ。忘れてしまったんじゃないか…","今日はこれで三度目だぞ、何か質問を持ち込むのは……","聞け、ここは店だ。人々はここで物を買うんだ。邪魔しないでくれ！","ブロック",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("「知ってるだろう、」 "+NPChar.name+"、また今度かもしれませんね。","そうだ、なぜか忘れてしまったんだ……","ああ、本当にこれで三度目だな……","ふむ、俺はしない……",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "graveyard" && !CheckAttribute(npchar, "quest.caleuche"))
			{
				link.l1 = "聞きたいんだが、ジョアキム・メリマンという名の男がここに店に来たことはあるか？中年のポルトガル人の旦那で、 口ひげとあごひげがあって、鋭い目をしている。何か買っていったことはないか？";
				link.l1.go = "caleuche";
			}
		break;
		
		// калеуче
		case "caleuche":
			dialog.text = "いいえ、お客様の中にあなたが言ったような人物はいませんでした。それに、その名前も聞いたことがありません。 申し訳ありませんが、これ以上お力にはなれません。";
			link.l1 = "なるほど。残念だ。さて、引き続き探してみるとしよう…";
			link.l1.go = "exit";
			npchar.quest.caleuche = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}
