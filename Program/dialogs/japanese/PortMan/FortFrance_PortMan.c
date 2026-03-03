// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("どんな質問だ？","何の用だ、 "+GetAddress_Form(NPChar)+"?"),"もうすでに俺に質問しようとしたじゃねえか "+GetAddress_Form(NPChar)+"...","今日はそれを三度も聞いてきたな……","港の用件について何も話すことがないなら、余計な質問で俺を煩わせるな。","ブロック",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("考え直した。","話すことは何もないぜ。"),"気にするな。","「本当に、もう三度目だな……」","悪いが、今のところ港の用事には興味がないんだ。",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//--> Бремя гасконца
		if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "ship" && !CheckAttribute(npchar, "quest.RescueDaughter"))
		{
			DelLandQuestMark(npchar);
			link.l1 = "旦那、仕事を探しております。ただし、荷運びのようなものではなく、私の身分にふさわしい任務を望んでおります。 何か任務や奉仕、繊細な事柄に関わる仕事……どんな依頼でもお受けします。";
			link.l1.go = "Sharlie";
		}
		//<-- Бремя гасконца
		
		// Jason „олго и счастливо
		if (CheckAttribute(pchar, "questTemp.LongHappy") && pchar.questTemp.LongHappy == "portman")
		{
			link.l1 = "私に宛てた手紙があると聞いた。名はシャルル・ド・モール船長だ。";
			link.l1.go = "LH_letter";
		}
		//--> Эпилог
		if (CheckAttribute(pchar, "questTemp.SharlieEpilog_PU_Ulysse"))
		{
			link.l1 = "「"+GetShipName("Ulysse")+"」というピナス船が最近オークションに出されたって聞いたけど、本当？";
			link.l1.go = "SharlieEpilog_PU_Ulysse_1";
		}
		//<-- Эпилог
		break;
		
		case "Sharlie":
			dialog.text = "助け？ふむ。私は神のおかげで元気にやっているよ。でも、友人の一人が本当に助けを必要としていて、 しかも急を要するんだ。彼は一人でジャングルに入ってインディアンと戦おうとしている、まったく正気の沙汰じゃない！ \nなんとか思いとどまらせようと説得して、頼み込んだんだが、全然聞く耳を持たなかった！娘のことを心配しすぎて、 命を投げ出す覚悟までしているんだよ！";
			link.l1 = "ちょっと待て、もう一度最初から聞くぜ。お前の友達は誰で、どこにいるんだ？それに、どんな助けが必要なんだ？";
			link.l1.go = "Sharlie_1";			
		break;
		
		case "Sharlie_1":
			dialog.text = "ああ、すまない、つい取り乱してしまった。彼の名はプロスパー…プロスパー・トルバルだ。きっと死んじまう！俺には助けられねえ―俺は兵士じゃないからな。彼の娘が行方不明で、地元のインディアンの仕業だと信じてるんだ。\n考えてみろよ、あいつ、自分ひとりで野蛮人どもに立ち向かうつもりなんだぜ！奴らにバラバラにされちまう…今ごろ、マスケット銃を買って、セルバに向かう準備をしてるところだ！";
			link.l1 = "お前はひどい語り手だな、旦那。お前の友人はどこにいる……なんて名前だったか……プロスパーか？";
			link.l1.go = "Sharlie_2";			
		break;
		
		case "Sharlie_2":
			dialog.text = "さっき彼と話して、考え直すよう説得しようとしたんだ。今は街門のすぐ近く、 井戸のそばで火縄銃と弾薬を点検している。あいつのところへ行って、何とかしてくれ！ もし一人でジャングルに入ったら、絶対に戻ってこないぞ。赤い肌の悪魔どもに八つ裂きにされちまう……";
			link.l1 = "くだらないことを言うな、まるで年寄りの女みたいだぞ！\nすぐにお前の仲間のところへ向かうぜ。\n俺が助けになれるといいがな。";
			link.l1.go = "Sharlie_3";			
		break;
		
		case "Sharlie_3":
			DialogExit();
			AddQuestRecord("SharlieF", "1");
			RescueDaughter_CreateProsper();
			npchar.quest.RescueDaughter = "true";
			QuestPointerDelLoc("fortfrance_town", "reload", "reload10_back");
		break;
		
		// Jason „олго и счастливо
		case "LH_letter":
			dialog.text = "はい、その通りです――封筒があります。\nこれです、しかしまず配達料として一万二千銀ペソを支払ってもらいます。";
			if (sti(pchar.money) >= 12000)
			{
				link.l1 = "俺はずっと、お前の商売は元々盗人の稼業だと思ってたんだが、どうやら見当違いだったみたいだな、ふむ。どうぞ、 これが報酬だ。";
				link.l1.go = "LH_letter_1";
			}
			else
			{
				link.l1 = "少し後で戻るぜ、酒場に財布を忘れたみてえだ。";
				link.l1.go = "exit";
			}
		break;
		
		case "LH_letter_1":
			DialogExit();
			AddMoneyToCharacter(pchar, -12000);
			LongHappy_RecibeLetter();
		break;
		
		//--> Эпилог
		case "SharlieEpilog_PU_Ulysse_1":
			dialog.text = "その通りだ。船の持ち主は保険の借金で首が回らなくなって、船をオークションに出したんだ。ただ、少し遅かったね——競売はもう終わって、新しい所有者が書類の手続きをしているところさ。";
			link.l1 = "その人がどこにいるか教えてもらえますか？話をしたいんです。";
			link.l1.go = "SharlieEpilog_PU_Ulysse_2";
			DelLandQuestMark(npchar);
			SharlieEpilog_SpawnPikar();
		break;
		
		case "SharlieEpilog_PU_Ulysse_2":
			dialog.text = "探すまでもないよ。振り向いてごらん——彼はすぐ後ろにいるよ。";
			link.l1 = "...";
			link.l1.go = "exit";			
		break;
		//<-- Эпилог
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
