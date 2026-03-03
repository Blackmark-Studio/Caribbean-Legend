//navy 26.07.06
//генератор дуэлей...
//в диалоге НПС делаем линк с проверкой флага оскорбления... по нему переход на "outraged"
//если НПС сделал что-то ГГ (продажа фальшивки) или ГГ наехал на НПС, вешаем на него флаг.
//для некоторых, например ПГГ, можно делать переход сразу на вызов: "let_s_duel"
void ProcessDuelDialog(ref NPChar, aref Link, aref NextDiag)
{
	int iHour;
	string sLocation;

	//флаг убираем
	DeleteAttribute(NPChar, "Outrage");
    switch (Dialog.CurrentNode)
	{
	case "outraged":
		Dialog.Text = NPCharRepPhrase(NPChar,RandSwear()+RandPhraseSimple("俺を侮辱するとは、なんて奴だ、この野郎！？","その言葉は高くつくぜ！"),RandPhraseSimple("「俺の名誉を侮辱したな」 "+GetAddress_Form(NPChar)+"！そしてその報いは受けてもらうぜ。","よくもそんなことを言いやがったな？今すぐその言葉を取り消せ！"));

		//это такая засада.. чтобы читали текст :)
		MakeRandomLinkOrderTwo(link, 
					NPCharRepPhrase(pchar, 
				RandPhraseSimple("Ha?! I don't even want to stain my sword with your blood!", "Ha?! I don't even want to stain my sword with your blood!"), 
				RandPhraseSimple("I am always at your service!", "I am not going to choose words while speaking with the rabble!")), "outraged_1",
					NPCharRepPhrase(pchar, RandSwear() + 
				RandPhraseSimple("I didn't mean it!", "I fired up..."), 
				RandPhraseSimple("That was a mistake. I am sorry.", "I took you for someone else, " + GetAddress_FormToNPC(NPChar) + ". Please forgive me.")), "change_mind");
		break;

	case "outraged_1":
		Dialog.Text = NPCharRepPhrase(NPChar,RandPhraseSimple("耳を切り落としてやるぜ！","てめえの心臓をえぐり取ってやるぜ！"),RandPhraseSimple("言い訳を聞かせてもらおうじゃねえか、さもないと俺も自分を抑えられる自信がねえぞ！","お前、これが何を意味するかわかってるのか……わかってるのか？"));

		MakeRandomLinkOrderTwo(link,
					NPCharRepPhrase(pchar, RandSwear() + 
				RandPhraseSimple("I hope that your saber is as swift as your tongue!", "My blade will speak for me."), 
				RandPhraseSimple("I challenge you to a duel!", "That's a matter of honor!")), "let_s_duel",
					NPCharRepPhrase(pchar, 
				RandPhraseSimple("I think I am not ready yet!", "Think, we shouldn't get excited! These are words only!"), 
				RandPhraseSimple("I remembered, I am waiting. All blessings...", "Ah! Seems, my ship is sailing already. Bye.")), "change_mind");
		break;

	case "let_s_duel":
		//проверка на начатые дуэли.
		if (CheckAttribute(PChar, "questTemp.duel.Start") && sti(PChar.questTemp.duel.Start))
		{
			Dialog.Text = "まずは他の連中との用事を片付けてから、俺と話そう。";
			if (PChar.questTemp.duel.enemy == NPChar.id)
			{
				Dialog.Text = "我々はすでに合意に達している。";
			}
			link.l1 = RandSwear()+"「ああ、どうして忘れてしまったんだ……」";
			link.l1.go = "exit";
			break
		}
		//может отказаться.
		if (rand(100) < 30)
		{
			Dialog.Text = RandPhraseSimple("決闘だと！？消え失せろ、お前なんかに俺の時間を無駄にする価値はねえ。","決闘だと？お前にそんな名誉はないぜ！消え失せろ！");
			link.l1 = RandPhraseSimple("……わかった……","待つしかねえか……");
			link.l1.go = "exit";
/**/
			//можно дать возможность драться полюбому :)			
			if (rand(100) < 30)
			{
				link.l1 = RandPhraseSimple("そう思うのか？そんなに自信持つな、この野郎！！！","「ほう、そうか！？てめえの血の色、見せてもらうぜ！」");
				link.l1.go = "fight_right_now";
			}
/**/
			break;
		}

		//согласен.
		Dialog.Text = RandPhraseSimple("決闘だと？俺は構わねえぜ。武器は剣とピストルだ。","剣をちゃんと持てるのか？");
		link.l1 = RandPhraseSimple("命乞いをすることになるぜ、ひざまずいてな。","この手でお前を絞め殺してやるぞ、この野郎！");
		link.l1.go = "land_duel";
		if (sti(pchar.Ship.Type) != SHIP_NOTUSED && sti(NPChar.Ship.Type) != SHIP_NOTUSED)
		{
			Dialog.Text = RandPhraseSimple(Dialog.Text+" それとも、俺たちが出航して、誰が何者か見極めてやるか！","決闘だと？！！ははっ、虫けらみてえに叩き潰してやるぜ！死に方を選びな！");
			link.l2 = RandPhraseSimple("海の上じゃ、俺が一番だぜ。","俺の船なら、お前のボロ船なんざ楽に沈めてやるぜ！");
			link.l2.go = "sea_duel";
		}
		link.l3 = "気が変わった……";
		link.l3.go = "change_mind";
		break;

	//дуэль на подводных лодках :))))
	case "sea_duel":
		Dialog.Text = RandPhraseSimple("港にお前の船が見当たらねえな……","せめてボロ船でも見つけてから出直してこい！");
		link.l1 = RandPhraseSimple("俺の勘違いだ……","それでは、お前を置いていく。");
		link.l1.go = "exit";
		if (pchar.location.from_sea == GetCurrentTown() + "_town")
		{
			Dialog.Text = "よし、入り江の出口で待ってるぜ…";
			link.l1 = "あまりお待たせしないよ。";

			pchar.questTemp.Duel.enemy = NPChar.id;
			pchar.questTemp.Duel.Sea_Location = Islands[GetCharacterCurrentIsland(PChar)].id;
			AddDialogExitQuestFunction("Duel_Sea_Prepare");
		}

		break;

	//на суше
	case "land_duel":
		iHour = 1 + rand(2);
		if (GetTime() > 4.0 && GetTime() < 17.0)
		{
//			iHour = MakeInt(18.0 - GetTime()) + rand(2); //раскоментировать для дуэлей только по ночам
		}
		pchar.questTemp.Duel.WaitTime = iHour;
		Dialog.Text = RandSwear()+RandPhraseSimple("剣を抜け、てめえの血の色を見せてもらおうじゃねえか！","さて、死に急ぐつもりなら……");
		link.l1 = RandPhraseSimple("あまり人目のない場所に行った方がいいな。城門を越えたところにちょうどいい場所を知ってるんだ。そこで会おう、 "+iHour+" 時間。","落ち着け。こういう話は証人がいない方がいい。中へ入れ "+iHour+"  市門まであと数時間だ。");
		link.l1.go = "fight_off_town";
		link.l2 = RandPhraseSimple("そんなに死にてえなら……","くそっ！お前に地獄を見せてやるぜ！");
		link.l2.go = "fight_right_now";
		link.l3 = "考え直した……";
		link.l3.go = "change_mind";

		if (rand(1))
		{
			Dialog.Text = RandSwear()+RandPhraseSimple("城門を通り抜けた方がいいと思うぜ。そこで待ってるからな、 "+pchar.questTemp.Duel.WaitTime+" 数時間だ。ぐずぐずするなよ！","ここは争いを解決するには最適な場所じゃねえ。町を出たほうがいいぜ。\n "+pchar.questTemp.Duel.WaitTime+" 数時間後にはそこにいる。");
			link.l1 = RandPhraseSimple("貴様にその名誉はふさわしくねえ！覚悟しやがれ！","時間がない！剣を抜け！");
			link.l1.go = "fight_right_now";
			link.l2 = RandPhraseSimple("よし、散歩に行こうぜ。","たぶん君の言う通りだ。門を越えた先で会おう。");
			link.l2.go = "fight_off_town_prep";
		}
		break;

	//предложение "пойдём выйдем" рассматривается
	case "fight_off_town":
		Dialog.Text = RandPhraseSimple("貴様にその名誉はふさわしくねえ！覚悟しやがれ！","時間がない！今ここで、今すぐだ！");
		link.l1 = RandPhraseSimple("そんなに死にてえなら……","くそっ！お前に地獄をこの目で見せてやるぜ！");
		link.l1.go = "fight_right_now";
		if (rand(1))
		{
			Dialog.Text = RandPhraseSimple("よし、散歩でもしようぜ。","たぶん君の言う通りだな。門を越えた先で会おう。");
			link.l1 = RandPhraseSimple("そこで待ってるぜ。","遅れるな。");
			link.l1.go = "fight_off_town_prep";
		}
		break;

	//что ж, пойдём выйдем
	case "fight_off_town_prep":
		SaveCurrentQuestDateParam("questTemp.Duel.StartTime");
		PChar.questTemp.duel.Start = true;
		PChar.questTemp.duel.enemy = NPChar.id;
		sLocation = GetCurrentTown();
		if (sLocation != "")
		{
			//где?
			sLocation += "_ExitTown";
			pchar.questTemp.duel.place = sLocation;

			Locations[FindLocation(sLocation)].DisableEncounters = true;
			//приходит ко времени.
			pchar.quest.duel_move_opponent2place.win_condition.l1 = "Location";
			pchar.quest.duel_move_opponent2place.win_condition.l1.location = pchar.questTemp.duel.place;
			pchar.quest.duel_move_opponent2place.function = "Duel_Move_Opponent2Place";
			//на случай, если не дождется, часа вполне достаточно
			SetTimerConditionParam("duel_move_opponentBack", "Duel_Move_OpponentBack", 0, 0, 0, sti(GetTime() + 0.5) + sti(pchar.questTemp.Duel.WaitTime) + 1, false);
			pchar.quest.duel_move_opponentBack.function = "Duel_Move_OpponentBack";
			if (CheckAttribute(NPChar, "CityType"))
			{
				DeleteAttribute(NPChar, "City"); // чтоб не было ругани с нацией
	    		DeleteAttribute(NPChar, "CityType");
				if (!CheckAttribute(NPChar, "PGGAi")) 
				{
					if (!CheckAttribute(NPChar, "LifeDay")) npchar.LifeDay = 0;
					npchar.LifeDay = sti(npchar.LifeDay) + 3; // чтоб до дуэли не помер
				}
    		}
		}
		NextDiag.CurrentNode = "let_s_duel";
		DialogExit();
		break;

	//последнее слово перед боем
	case "talk_off_town":
		Dialog.Text = "それで、準備はできたか？";
		link.l1 = "ああ。どっちが上か、勝負しようぜ！";
		link.l1.go = "fight_right_now";
		link.l2 = "いや、俺は謝りに来たんだ。俺が悪かった、つい熱くなっちまってな。";
		link.l2.go = "change_mind";
		if (rand(100) < 20)
		{
			Dialog.Text = RandPhraseSimple("おい、聞いてくれ、考え直してみたんだが、俺が間違ってたと今はわかる。すまなかった。","くそっ！全部あの忌々しいラムのせいだ！！！すまねえ、 "+GetSexPhrase("兄弟","姉妹")+"!");
			link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("いや、今はお前の血だけが俺を満たしてくれるんだ！","剣を抜け、いつまでも泣き言を言うんじゃねえ！"),RandPhraseSimple("いやだ！俺は決着をつけることを要求する！","お前は家族の恥さらしだ！剣を抜け！"));
			link.l1.go = "fight_right_now";
			link.l2 = NPCharRepPhrase(pchar,RandPhraseSimple("よし、わかった。ちょっと熱くなりすぎたな。","友達同士で点数なんて気にするなよ！"),RandPhraseSimple("たぶんお前の言う通りだな。こんな些細なことで血を流すべきじゃねえ。","俺の寛大さに限りはねえ！許してやるぜ！"));
			link.l2.go = "peace";
		}
		NextDiag.TempNode = npchar.BackUp.DialogNode;
		pchar.questTemp.Duel.End = true;
		break;

	//дуэли быть!
	case "fight_right_now":
		PChar.questTemp.duel.enemy = NPChar.id;
		AddDialogExitQuestFunction("Duel_Prepare_Fight");
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;

	case "fight_right_now_1":	
		PChar.questTemp.duel.enemy = NPChar.id;
		PChar.questTemp.duel.enemyQty = rand(2) + 1;
		AddDialogExitQuestFunction("Duel_Prepare_Fight");
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();	
		break;
		
	//передумал, э... не хорошо ;)
	case "change_mind":
		if (CheckAttribute(pchar, "questTemp.Duel.End")) LAi_SetWarriorType(NPChar);
		Dialog.Text = NPCharRepPhrase(NPChar,RandSwear()+RandPhraseSimple("だったら、とっとと失せろ！","さっさと失せな、気が変わらないうちにな。"),RandPhraseSimple("それなら、これ以上引き止めはしません！","気が変わらないうちに、とっとと出ていくんだな。"));
		link.l1 = "もう行くところだ……";
		link.l1.go = "peace";
		break;

	case "after_peace":
		Dialog.Text = NPCharRepPhrase(NPChar,RandSwear()+RandPhraseSimple("失せろ！","俺の目の前から消えろ、気が変わらないうちにな。"),RandPhraseSimple("お手伝いしましょうか？","何か用か？"));
		link.l1 = "俺は行くぜ。";
		link.l1.go = "peace";
		break;

	//мир и все такое.
	case "peace":
		LAi_SetWarriorType(NPChar);
		NextDiag.CurrentNode = "after_peace";
		DialogExit();
		break;
	}
}
