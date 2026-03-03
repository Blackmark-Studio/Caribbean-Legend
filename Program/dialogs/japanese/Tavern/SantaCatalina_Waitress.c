// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("「質問」 "+GetAddress_Form(NPChar)+"?","「どうなさいましたか、」 "+GetAddress_Form(NPChar)+"?"),""+GetSexPhrase("ふん、何のつもりだ、 "+GetAddress_Form(NPChar)+"? ","また変な質問かい？お嬢ちゃん、ラムでも飲んできなよ……")+"","今日一日で、この質問を持ち出すのはこれで三度目だな…"+GetSexPhrase(" これは愛情のしるしか？","")+"","「また質問か、そうだろう。」 "+GetAddress_Form(NPChar)+"?","ブロック",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("気が変わった","今は話すことは何もねえな。"),"いや、美しくねえ……","ありえねえよ、お嬢ちゃん…","いや、何の質問だって…",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;

		case "helendrinking":
			dialog.text = "「よくお休みになれましたか、旦那？マッカーサー嬢から、あなたの快適さを万全にするよう命じられております！」";
			link.l1 = "俺はとても奇妙な夢を見たんだ……";
			link.l1.go = "helendrinking_1";
		break;

		case "helendrinking_1":
			dialog.text = "あっ……";
			link.l1 = "どうしたんだい、お嬢さん？何か手伝えることがあるかい？";
			link.l1.go = "helendrinking_2";
		break;

		case "helendrinking_2":
			dialog.text = "ごめんなさい、船長……罪だとわかってるけど、我慢できないの！あたし、あまり経験ないけど、どうか追い返さないで、船長！あなた、 すごく素敵だもの！喜ばせたい、触れたいの……";
			link.l1 = "まったく、快適そのものだな……それにあんた、とても美人じゃねえか！さあ、恥ずかしがるなよ。";
			link.l1.go = "helendrinking_sex";
			link.l2 = "今は俺に触らない方がいいぜ、お嬢さん――ラム酒臭いからな。\nでも、もし朝飯を用意してくれたら嬉しいぜ！";
			link.l2.go = "helendrinking_nosex";
		break;
		
		case "helendrinking_sex":
			dialog.text = "おやおや！";
			link.l1 = "";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "exit";
			
			pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) - 1;
			Notification_Approve(false, "Helena");
			AddDialogExitQuestFunction("HelenDrinking_WaitressSex");
		break;

		case "helendrinking_nosex":
			dialog.text = "失礼だな！";
			link.l1 = "朝飯はなしってことか？";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "exit";
			
			pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) + 1;
			Notification_Approve(true, "Helena");
			AddDialogExitQuestFunction("HelenDrinking_WaitressNoSex");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
