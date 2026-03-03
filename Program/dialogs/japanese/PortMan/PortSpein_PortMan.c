// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("どんな質問だ？","何の用だ、 "+GetAddress_Form(NPChar)+"?"),"もうすでに俺に質問しようとしたじゃねえか "+GetAddress_Form(NPChar)+"...","「今日はそれを三度も聞いてきたな……」","港の用件について何も話すことがないなら、俺に質問して邪魔するんじゃねえ。","ブロック",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("考えを変えた。","話すことは何もねえ。"),"気にするな。","確かに、もう三度目だな……","悪いが、今のところ港の用事には興味がないんだ。",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//Цена чахотки
			if (!CheckAttribute(npchar, "quest.Consumption") && CheckAttribute(pchar, "questTemp.Consumption.AskJuan"))
			{
				link.l1 = "「教えてくれ、『フアン』という名前に心当たりはあるか？」";
				link.l1.go = "Consumption";
			}
			if (!CheckAttribute(npchar, "quest.Guardoftruth") && CheckAttribute(pchar, "questTemp.Guardoftruth.Trinidad") && pchar.questTemp.Guardoftruth.Trinidad == "begin")
			{
				link.l1 = "旦那、1654年4月にミゲル・ディチョソの指揮するフリゲート艦がここにいました。その時に彼は姿を消しました。 何か覚えていませんか？もしかするとディチョソがここに来て、船の登録をしたかもしれませんが…";
				link.l1.go = "guardoftruth";
			}
		break;
		
		//Цена чахотки
		case "Consumption":
			dialog.text = "「フアン？それだけか？旦那、酔ってるのか、それとも俺をからかってるのか？姓か、 せめて船の名前くらい覚えてないのか？ここはスペインの植民地だぞ、頼むから。 こっちにフアンが何人いると思ってるんだ？詳細がなけりゃ手助けできねえよ。」";
			link.l1 = "なるほど。お邪魔してすまなかったな…";
			link.l1.go = "exit";
			pchar.questTemp.Consumption.AskJuan = sti(pchar.questTemp.Consumption.AskJuan)+1;
			if(sti(pchar.questTemp.Consumption.AskJuan) == 3)
			{
				pchar.quest.Consumption2.win_condition.l1 = "location";
				pchar.quest.Consumption2.win_condition.l1.location = "PortSpein_town";
				pchar.quest.Consumption2.function = "Consumption_CreateSergio";
			}
			npchar.quest.Consumption = "true";
		break;
		
		case "guardoftruth":
			dialog.text = "ええと、私の記録を見てみよう……ああ、あった！そうだ、ミゲル・ディチョソ船長は1654年4月にここに来ていた、フリゲート艦『サンタ・キテリア』でな。彼はサン＝アンドレス、 プロビデンス植民地から来たと登録している。スペインのカディスへ向かっていた。1654年4月14日に出港した。それが私の持っている全ての情報だ。";
			link.l1 = "ヨーロッパへ航海するのか。なるほど。ありがとう！";
			link.l1.go = "exit";
			npchar.quest.guardoftruth = "true";
			AddQuestRecord("Guardoftruth", "39");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
