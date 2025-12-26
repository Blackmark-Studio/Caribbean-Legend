// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("どうぞ、ご用件は何ですか？","ちょうどその話をしていたところだ。忘れてしまったのか……","今日はこれで三度目だ、何か質問を持ち込んできたのは……","聞け、ここは店だ。みんなここで物を買うんだ。邪魔しないでくれ！","ブロック",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("「知っているだろう、 "+NPChar.name+"、また今度かもしれませんね。","そうだ、なぜか忘れてしまっていた……","「ああ、本当にこれで三度目だな……」","ふむ、俺はやらない……",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//Цена чахотки
			if (!CheckAttribute(npchar, "quest.Consumption") && CheckAttribute(pchar, "questTemp.Consumption.AskJuan"))
			{
				link.l1 = "「教えてくれ、フアンという名前に心当たりはあるか？」";
				link.l1.go = "Consumption";
			}
			if (!CheckAttribute(npchar, "quest.Guardoftruth") && CheckAttribute(pchar, "questTemp.Guardoftruth.Trinidad") && pchar.questTemp.Guardoftruth.Trinidad == "begin")
			{
				link.l1 = "1654年4月、ミゲル・ディチョソ船長率いるフリゲート艦があなたの港に寄港し、その後彼は姿を消しました。\nこの名前に心当たりはありませんか？もしかすると、彼があなたから何か商品を買ったり、 何か話したりしませんでしたか…";
				link.l1.go = "guardoftruth";
			}
		break;
		
		//Цена чахотки
		case "Consumption":
			dialog.text = "おいおい、船長！今日は店にフアンが二人も来たし、昨日もまた一人来たんだぜ。いちいち全員覚えてろってのか？";
			link.l1 = "わかった。邪魔して悪かったな……";
			link.l1.go = "exit";
			npchar.quest.Consumption = "true";
		break;
		
		case "guardoftruth":
			dialog.text = "ああ、船長、その間に何隻ものフリゲートやガレオンが出入りするのを見てきましたよ、ミゲルやカルロスたちも……";
			link.l1 = "なるほど。つまり、あなたは何の役にも立たないということですね……";
			link.l1.go = "exit";
			npchar.quest.guardoftruth = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}
