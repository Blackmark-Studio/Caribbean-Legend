// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("どうぞ、何のご用ですか？","ちょうどその話をしていたところだ。忘れてしまったんじゃないか…","今日はこれで三度目だ、この質問を持ち出すのは……","聞け、ここは店だ。人々がここで物を買うんだ。邪魔しないでくれ！","ブロック",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("「知ってるだろう、 "+NPChar.name+"、また今度にしようか。","そうだ、なぜか忘れてしまっていた……","「ああ、本当にこれで三度目だな……」","ふむ、俺はしないぞ…",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}
