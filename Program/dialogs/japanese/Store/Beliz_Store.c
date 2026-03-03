// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("さあ、何の用だ？","ちょうどその話をしていたところだ。忘れてしまったんじゃないか…","今日はもう三度目だ、その質問を持ち出すのは……","聞け、ここは店だ。人々はここで物を買うんだ。邪魔しないでくれ！","ブロック",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("「知っているだろう、」 "+NPChar.name+"、また今度かもしれませんね。","「そうだ、なぜか忘れてしまっていた……」","「ああ、本当にこれで三度目だな……」","ふむ、俺はやらない……",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}
