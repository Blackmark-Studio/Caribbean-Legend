// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("「すべての噂話は」 "+GetCityName(npchar.city)+" お役に立ちますぜ。何を知りたいんだ？","ちょうどその話をしてたんだぜ。お前、忘れちまったのか…","今日はこれで三度目だぜ、この質問を持ち出すのは……","お前、オウムみたいに同じことばかり繰り返してるじゃねえか…","ブロック",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("「知ってるか、」 "+NPChar.name+"、また今度だな。","ああ、何かの理由で忘れちまったんだよな……","ああ、本当にこれで三度目だな……","ああ……",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
