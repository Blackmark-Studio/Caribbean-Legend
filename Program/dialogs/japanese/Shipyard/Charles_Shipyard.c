// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("何か質問があるか？","どうされましたか？お手伝いできることはありますか？"),"少し前に俺に何か質問しようとしたよな…","俺の造船所でも、この町のどこでも、こんなに好奇心旺盛な奴らに会ったことはねえな。","質問が多いな。俺の仕事は船を造ることだぜ。さあ、それを片付けよう。","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("考えが変わった……","今は話すことは何もねえぜ。"),"うーん、俺の記憶はどこに行っちまったんだ…","ふむ、そうだな……","どうぞ……",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// Addon 2016-1 Jason пиратскаЯ линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "silk_2")
            {
                link.l1 = "聞いてくれ、親方、ここで船を造ってるんだろ？…それに帆も張り替えてるよな…もっといい帆布の素材について考えたことはあるか？";
                link.l1.go = "mtraxx";
			}
		break;
		
		// Addon 2016-1 Jason пиратскаЯ линейка
		case "mtraxx":
            dialog.text = "謎かけみたいな話し方はやめてくれ、旦那……はっきり言えよ、何の用だ？心配はいらねえ、俺は書類屋じゃねえし、ここは税関でもねえからな。";
			link.l1 = "ああ、意見が一致して嬉しいです！シルクの帆布ですよ、旦那。私の理解では、 速さを求めるならこれ以上の帆材はありません。";
			link.l1.go = "mtraxx_1";
		break;
		
		case "mtraxx_1":
            dialog.text = "速さだけじゃなく、風上に向かって帆走する能力も素晴らしいな。船用シルクを売りに来たのか？確かに貴重な貨物だ。 しかし問題がある。正直なところ、私はそれをどう生産に使えばいいのか分からないんだ。分かるか？ こういう素材は特別な技術と技能が必要だが、私にはそれがない。正直に言えば、 うちの造船所は全く別の分野が専門なんだ。もしロシア帝国産のロープを持ってきてくれたなら、 値段に関係なく全部買い取るさ。ロープは常に必要なんだが、船用シルクはここでは需要がないんだ、すまない！";
			link.l1 = "ふむ。なるほど。時間を取ってくれてありがとう、親方。幸運を祈るぜ！";
			link.l1.go = "mtraxx_2";
		break;
		
		case "mtraxx_2":
            DialogExit();
			AddQuestRecord("Roger_2", "4");
			pchar.questTemp.Mtraxx = "silk_3";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
