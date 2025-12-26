// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("どうぞ、何のご用ですか？","ちょうどその話をしていたところだ。忘れてしまったんじゃないか…","今日はその質問を持ち出すのはこれで三度目ですよ……","聞け、ここは店だ。みんなここで物を買うんだ。邪魔しないでくれ！","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("「知ってるだろう、」 "+NPChar.name+"、また今度かもしれませんね。","そうだ、なぜか忘れてしまったな……","ああ、本当にこれで三度目だな……","ふむ、俺はしない……",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}
