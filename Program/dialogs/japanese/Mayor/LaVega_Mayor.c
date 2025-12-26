// заместитель Маркуса Тиракса в Ла Веге
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sLoc;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

// ------------------------------------------блок angry-----------------------------------------------
    if (CheckAttribute(npchar, "angry") && !CheckAttribute(npchar, "angry.ok"))
    {
        npchar.angry.ok = 1;
        if (!CheckAttribute(npchar, "angry.first")) //ловушка первого срабатывания
        {
            NextDiag.TempNode = NextDiag.CurrentNode;
            Dialog.CurrentNode = "AngryExitAgain";
            npchar.angry.first = 1;
        }
        else
        {
            switch (npchar.angry.kind) //сюда расписываем реакцию ангри. В npchar.angry.name пробелы удалены!!!
            {
                case "repeat":
                    if (npchar.angry.name == "Firsttime") Dialog.CurrentNode = "AngryRepeat_1";
                    if (npchar.angry.name == "I_know_you_good") Dialog.CurrentNode = "AngryRepeat_2";
                break;
            }
        }
    }
// ------------------------------------------блок angry-----------------------------------------------

	switch(Dialog.CurrentNode)
	{
		// ----------------------------------- Диалог первый - первая встреча
		case "First time":
            dialog.text = NPCStringReactionRepeat("私に何か言いたいことがあるのか？ないのか？では、さっさと出て行け！","私の言いたいことは十分伝わったはずだ、これ以上私を煩わせるな。","私がはっきり申し上げたにもかかわらず、あなたはしつこく私を煩わせ続けますね！","そうか、私はこの無礼さにうんざりしてきました。","repeat",3,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("私はもう出発いたします。","Sure"+npchar.name+"...","申し訳ありません。 "+npchar.name+"...","「おっと……」",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

        case "I_know_you_good":
            dialog.text = NPCStringReactionRepeat(GetFullName(pchar)+"、お会いできて嬉しいです！ご用件は何でしょうか？","他には？"," またお前か？用がないなら人を煩わせるな！","あなたが立派な方であることは存じております。しかし、これ以上あなたとお話しするつもりはございません。","repeat",10,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("何でもありません。ただお会いしたかっただけです。","「何も……」","「よろしい」 "+npchar.name+"…申し訳ありません…","くそっ、全部俺のせいだ……",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";
		break;

		// ============== Грабеж среди бела дня, попытка залезть в сундуки =========================
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("盗みだと！？本気か！？お前はもう終わりだぜ……","待て、なんだと？お前、泥棒だったのか！もう終わりだ……");
			link.l1 = LinkRandPhrase("「くそっ！」","カランバ！！","くそっ！！");
			link.l1.go = "PL_Q3_fight";
		break;
					
		// ======================== блок нод angry ===============>>>>>>>>>>>>>>>
		case "AngryRepeat_1":
            dialog.text = RandPhraseSimple(""+GetSexPhrase("立ち去りなさい","「立ち去れ」 ")+" ここからだ！","私の家から出ていけ！");
			link.l1 = "「おっと……」";
		    link.l1.go = "AngryExitAgainWithOut";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся через 10 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "安っぽい話で私を煩わせるな。次は後悔することになるぞ……";
        			link.l1 = "承知いたしました。";
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
            }
    	break;
		case "AngryRepeat_2":
            dialog.text = "終わりだ、もう話すことはない。";
			link.l1 = RandPhraseSimple("ご意向のままに……","よろしいでしょう……");
		    link.l1.go = "AngryExitAgain";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся через 10 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "私にもっと敬意を払い、無礼な態度をやめていただきたいものです。\nさもなくば、あなたを殺さねばなりません。それは非常に不本意なことです。";
        			link.l1 = ""+npchar.name+"、ご安心ください、必ずそういたします。";
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
            }
    	break;
		case "AngryExitAgain":
            DialogExit();
            DeleteAttribute(npchar, "angry.ok");
		break;
		case "AngryExitAgainWithOut":
            DialogExit();
            DeleteAttribute(npchar, "angry.ok");
            DoReloadCharacterToLocation("Lavega_town","reload","reload6");
		break;
		// <<<<<<<<<<<<============= блок нод angry =============================
		
		// Rebbebion, квест "Путеводная звезда"
		case "PZ_1":
			dialog.text = "ああ、君か、ド・モール。いやはや、これは驚いたな。海の悪魔にかけて、 君の来訪は久しぶりに起きた一番面白い出来事だ、ちくしょう。";
			link.l1 = "私もお会いできて嬉しいです、ヴェンサン。村を治めるのは楽しいですか？";
			link.l1.go = "PZ_2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_2":
			dialog.text = "どうしてそんなことができる？俺は船長だ、それも腕利きのな。くそったれな会計係なんかじゃねえ。しかも、 マーカスの使者が新しい航海に呼びに来るのを、クリスマスを待つより長く待ってるんだぜ、ちくしょうめ！";
			link.l1 = "クリスマスと呪いを同じ文で語るとは、なかなかだな。ああ、俺はお前が羨ましいとは思わねえよ。だが、 今のお前の立場に憧れる者は多いだろうさ。\nだが、今日は仕事で来たんだ、ヴェンサン。";
			link.l1.go = "PZ_3";
		break;
		
		case "PZ_3":
			dialog.text = "商売だと！？で、何なんだ、早く言えよ――何か思いついたのか？いい情報でもあるのか？この忌々しい計算ばかりで退屈すぎて、 もう地元の酒蔵を飲み干しちまいそうだぜ。";
			link.l1 = "まあ、実はあなたに質問があるだけでして、それ以上のことではありません。";
			link.l1.go = "PZ_4";
		break;
		
		case "PZ_4":
			dialog.text = "くそっ！よし、話を聞こう、チャールズ。";
			link.l1 = "女性があなたに会いに来たことはありますか？それとも、ラ・ベガで彼女を見かけたことは？彼女は「ベル・エトワール」 と名乗っていますが、それは偽名で、別の名前で自己紹介したかもしれません。重要なのは……彼女は黄色い肌をしています。しかし、奴隷や労働者ではなく、裕福な女性です。";
			link.l1.go = "PZ_5";
		break;
		
		case "PZ_5":
			dialog.text = "黄色い肌だが裕福とは？ここにはそんな者は今まで一人もいなかったぞ！さすがはあなたの波乱万丈な人生ですな、 ド・モール殿！少し羨ましいくらいですわ。";
			link.l1 = "そうか……まあ、お時間を取らせてしまいましたね、ヴァンサン。これ以上帳簿付けの邪魔はしませんよ、ふふっ。";
			link.l1.go = "Exit";
			
			AddQuestRecord("PZ", "40");
			
			pchar.quest.PZ_SetHeavyFrigate.win_condition.l1 = "location";
			pchar.quest.PZ_SetHeavyFrigate.win_condition.l1.location = "Hispaniola1";
			pchar.quest.PZ_SetHeavyFrigate.win_condition = "PZ_SetHeavyFrigate";
			DelMapQuestMarkCity("LaVega");
			AddMapQuestMarkCity("PortPax", false);
			LocatorReloadEnterDisable("LaVega_ExitTown", "reload1_back", true);
			LocatorReloadEnterDisable("PortPax_town", "gate_back", true);
		break;
	}
}
