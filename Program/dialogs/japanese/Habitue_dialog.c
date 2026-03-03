#include "DIALOGS\%language%\Common_Duel.c" //navy
#include "DIALOGS\%language%\Rumours\Common_rumours.c"  //homo 25/06/06
void ProcessDialogEvent()
{
    ref NPChar, d;
	aref Link, Diag;
	string NPC_Meeting, TempInfoCharacterID_1, TempInfoCharacterID_2, sQuestTitle, sStr;
	int DonationSize;
    	
	// Warship 18.05.08
	int iLa_Puesta; // La puesta - это ставка по-испански
    	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makeref(d, Dialog);
	makearef(Diag, NPChar.Dialog);
	
    ProcessCommonDialogRumors(NPChar, Link, Diag);//homo 25/06/06
    ProcessDuelDialog(NPChar, Link, Diag); //navy

	int iEnemyDice, iPCDice;
	int d1,d2,d3,d4;
	bool ok;
    ref sld;
    
	if (npchar.quest.Meeting != LastSpeakDate())
	{
		npchar.quest.Meeting = LastSpeakDate();
		npchar.money = 100 + rand(10) * makeint(50 * sti(PChar.rank) * (10.0 / MOD_SKILL_ENEMY_RATE));
		if (sti(npchar.money) < 150) npchar.money = 150;
        if (bBettaTestMode)
        {
            Dialog.CurrentNode = "Beta_test";
        }
	}
	switch (Dialog.CurrentNode)
	{
		// -----------------------------------Диалог первый - первая встреча
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
		break;

        case "Beta_test":
            dialog.text = "酔っ払いタイプ選択（ベータ版）";
			link.l1 = "Drunkard";
			link.l1.go = "Beta_test_alc";
            link.l2 = "カード賭博師";
			link.l2.go = "Beta_test_card";
			link.l3 = "サイコロ賭博師";
			link.l3.go = "Beta_test_dice";
		break;
		
		case "Beta_test_alc":
            dialog.text = "酔っ払いが選ばれた";
			link.l1 = "Continue";
			link.l1.go = "First time";
			npchar.quest.last_theme = 0;
		    npchar.quest.last_theme_game = 0;
		break;
		
		case "Beta_test_card":
            dialog.text = "カード賭博師（即座に反感を持つ確率30％）";
			link.l1 = "Continue";
			link.l1.go = "First time";
			npchar.quest.last_theme = 1;
		    npchar.quest.last_theme_game = 0;
		break;
		
		case "Beta_test_dice":
            dialog.text = "ダイス賭博師（即座に反感を持つ確率30％）";
			link.l1 = "Continue";
			link.l1.go = "First time";
			npchar.quest.last_theme = 1;
		    npchar.quest.last_theme_game = 1;
		break;
		
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = LinkRandPhrase("酔っ払ってるかもしれねえが、俺はバカじゃねえ。今お前と飲んだら、翌日には兵隊どもに捕まっちまうだろう。 冗談じゃねえ！","俺は自分の町の敵じゃねえ。お前なんかと酒は飲まねえ！",""+GetSexPhrase("相棒","娘")+"……まだ間に合ううちに、ここを離れた方がいいぞ……");
				link.l1 = RandPhraseSimple("「まあ、お望み通りに……」","へっ、なあ、そんなに酔っ払う必要はねえよ。今はそういう時じゃねえからな。"); 
				link.l1.go = "exit";
				break;
			}
			if(CheckAttribute(pchar,"questTemp.HabitueSpeakDisable") && rand(1) == 0) // если дуэлянт то каждый второй посылает нафик
			{
				dialog.text = "はっ、嬢ちゃん"+GetSexPhrase("ター","ｓ")+"「へっ、確かにお前の噂は聞いたことがあるぜ。酒場じゃお前は厄介者で決闘好きだって話だ。 俺たちの仲間はそう簡単に怖がらねえが、ラム一杯のために死にたがる奴はいねえよ。正直、 お前の隣に座るだけでも落ち着かねえから、俺は遠慮しとくぜ。」";
				link.l1 = LinkRandPhrase("じゃあ、せいせいするぜ！","俺がまだ機嫌がいいうちに、とっとと失せろ……","行け、行け！消え失せろ、魚のエサ野郎！");
				link.l1.go = "exit";
				link.l2 = "待ってくれ、ちょっと聞きたいことがあるんだ…";
				link.l2.go = "talk_habitue_duel";
				break;
			}
			
            ok = CheckFreeSitFront(npchar);
            
            dialog.text = "俺の光を遮るな、ジョッキの中のハエが見えねえじゃねえか！";
            link.l1 = "俺は立ってねえ…";
		    link.l1.go = "exit";
		    if (!chrDisableReloadToLocation)
		    {
	            switch (npchar.quest.last_theme)
				{
					case "0": //пьяный.
						dialog.text = "ひっく！ああ、 "+GetSexPhrase("おい、相棒、どう見てもベテランの古参水夫だな","お嬢ちゃん、ずいぶんと海の荒くれ者みたいな風格だな")+"！もしかして、ラム酒を一杯おごってくれないか？";
						link.l1 = "俺ぁ年季の入った船乗りかもしれねえが、だからってクズどものために酒をおごる気はねえぞ…";
						link.l1.go = "exit";

						if (makeint(pchar.money) >= 100 && ok) // только старые острова окучены на сесть
						{
							link.l2 = "喜んであなたの仲間に加わるぜ。";
							link.l2.go = "talk_with_alchogol";
						}
						else
						{
	                        link.l2 = "「それはなぜだ？」";
							link.l2.go = "talk_with_alchogol_song";
						}
					break;

					case "1":
	                    if (rand(3) != 1 && ok)
	                    {
							switch (sti(npchar.quest.last_theme_game))
							{
							    case 0 :
									// Игра в карты boal 20/05/05 -->
	                                if (CheckNPCQuestDate(npchar, "Card_date_begin"))
									{
										Dialog.text = RandPhraseSimple("カードでもどうだ？とても面白い勝負だぜ！","カードでもやらないか。どうだ？");
										link.l1 = "「どうして駄目なんだ？もちろん、やろうぜ。」";
										link.l1.go = "Cards_begin";
										link.l2 = "「それで、お前の遊びのルールは何だ？」";
										link.l2.go = "Cards_Rule";
										link.l3 = "今は駄目だ。";
										link.l3.go = "exit";
									}
									else
					    			{
										Dialog.text = "いや、もうお前とはカードをやらねえ。";
						    			link.l1 = "おっしゃる通りです。";
						    			link.l1.go = "exit";
									}
			                        // Игра в карты boal 20/05/05 <--
		                        break;

								case 1:
								// кости
		    						// Игра в кости boal 13/07/05 -->
	                                if (CheckNPCQuestDate(npchar, "Dice_date_begin"))
									{
										Dialog.text = RandPhraseSimple("サイコロでもどうだ？なかなか面白い遊びだぜ！","サイコロを振ってみないか？どうだ？");
										link.l1 = "なぜだ？もちろん、やろうじゃねえか。";
										link.l1.go = "Dice_begin";
										link.l2 = "「それで、お前の遊びのルールは何だ？」";
										link.l2.go = "Dice_Rule";
										link.l3 = "今は無理だ。";
										link.l3.go = "exit";
									}
									else
					    			{
										Dialog.text = "いや、もうお前とはサイコロ勝負はしねえ。";
					    				link.l1 = "おっしゃる通りです。";
					    				link.l1.go = "exit";
									}
			                        // Игра в кости boal 13/07/05 <--
			                        //navy --> Дуэли
									if (CheckAttribute(NPchar, "Quest.DiceCheats") && sti(NPchar.Quest.DiceCheats) >= 1) 
									{
					    				link.l9 = RandSwear()+" お前、不正してたな！！！";
					    				link.l9.go = "outraged";
									}
									//navy <--
			    				break;
	    					} 
						}
	        			else
	        			{
	                        dialog.text = RandPhraseSimple("俺の席から離れろ！今すぐだ！"," おお？なんだ？誰だ？ひっく……消え失せろ！");
	                        link.l1 = RandPhraseSimple("酒を飲むと罪深い魂が滅びるぞ！目を覚ませ！","俺に無礼な口をきくんじゃねえ。");
	        			    link.l1.go = "exit";
	        			    link.l2 = RandPhraseSimple("舌の利き方に気をつけろ、この野郎！さもないと礼儀ってもんを叩き込んでやるぜ。","今ここでお前の頭をぶん殴ったら、少しは酔いが覚めるんじゃねえか。");
	        	            link.l2.go = "tavern_keeper";
	        			}
					break;
				}
			}
			Diag.TempNode = "First time";
	    break;
	    
		case "talk_habitue_duel":
			dialog.text = "あんたには何も教えないよ、お嬢ちゃん"+GetSexPhrase("ター","ｓ")+"！それに、他の誰もお前に話しかけてこないと思うぜ、そういうのはたいてい厄介事の元だからな。でもな、 人間ってのは忘れっぽいもんだ。だから一月か二月もすりゃ、お前の冒険のことも忘れちまうかもな――もちろん、また蒸し返さなきゃの話だが、へへ！じゃあな、旦那"+GetSexPhrase("テール","ｓ")+". ";
			link.l1 = "「よし…」";
			link.l1.go = "exit";
		break;
		
	    // карты -->
	    case "Cards_Rule":
   			dialog.text = CARDS_RULE;
			link.l1 = "さて、始めようか……";
			link.l1.go = "Cards_begin";
			link.l3 = "いや、俺のためじゃねえんだ……";
			link.l3.go = "exit";
		break;
		
		case "Cards_begin":
			Diag.tempnode = "Cards_Node";
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			pchar.questTemp.friend_in_tavern = npchar.id;
			AddDialogExitQuest("alc");
		break;

		case "Cards_Node":
			Diag.tempNode = "first time";

			Dialog.text = "まずは賭けの内容を決めようぜ（賭け金を入力してくれ）。";
			link.l1 = "100";
			link.l1.edit = 1;
			link.l1.go = "Cards_Node_2";
			link.l3 = "仕方ない、行かなくちゃな。";
			link.l3.go = "exit_sit";
		break;
		
		case "Cards_Node_2":
			iLa_Puesta = GetStrSmallRegister(dialogEditStrings[1]);
            if (!CheckCardsGameSmallRate())
		    {
                dialog.text = "お前は悪名高いイカサマ師だ。俺はお前とは賭けをしねえ。";
                link.l1 = "全部嘘だ！まあ、どうでもいいさ。";
			    link.l1.go = "exit_sit";
			    break;
		    }
		    
			if (sti(PCHar.Money) < sti(iLa_Puesta)*3)
		    {
                dialog.text = "「金がねえみたいだな、」 "+GetSexPhrase("友達","「あなた」")+"。金持ちになったら戻ってこい。";
                link.l1 = "「いいだろう。」";
			    link.l1.go = "exit_sit";
			    break;
		    }
		
			if (sti(NPChar.Money) < sti(iLa_Puesta)*3)
		    {
                dialog.text = "俺はもう持っていたものをすべて失っちまった。今日はついてねえ日だな。";
                link.l1 = "「いいだろう。」";
			    link.l1.go = "exit_sit";
			    break;
		    }
		else
		{
			if(sti(iLa_Puesta) < 50)
			{
				dialog.text = "俺を笑ってるのか、それとも何だ！？遊んでるのか "+iLa_Puesta+" ペソだと！？もっと手頃な賭け金でやろうぜ、じゃなきゃ俺は降りる！";
				link.l1 = "ああ、その通りだ。もう少し賭け金を上げる必要があるな。";
				link.l1.go = "Cards_begin_2";
				link.l2 = "考え直した、俺はやらない。";
				link.l2.go = "exit_sit";
				break;
			}
			
			if(sti(iLa_Puesta) > 1000)
			{
				dialog.text = "そんな大金を賭けるのか？いや、俺は遠慮しておくぜ、賭け金を変えない限りな。";
				link.l1 = "ああ、その通りだ。賭け金を少し下げる必要があるな。";
				link.l1.go = "Cards_begin_2";
				link.l2 = "実は、俺はまったく遊ばないことにしたんだ。";
				link.l2.go = "exit_sit";
				break;
			}
			dialog.text = "よし、これで勝負しよう "+iLa_Puesta+" コインだ。";
			link.l1 = "カードを配れ！";
			link.l1.go = "Cards_begin_go";
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
			pchar.GenQuest.Cards.iRate     = sti(iLa_Puesta);
            pchar.GenQuest.Cards.SitType   = true;
		}
		break;
		
		case "Cards_begin_2":
			dialog.text = "それで、賭けは何だ？（賭け金を入力せよ）";
			link.l1 = "50";
			link.l1.edit = 1;
			link.l1.go = "Cards_Node_2";
			link.l2 = "やっぱり俺は遊ばないことにするよ……";
			link.l2.go = "exit_sit";
		break;
							
		case "Cards_begin_go":
            // анлим игры в день SetNPCQuestDate(npchar, "Card_date_begin");
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
            LaunchCardsGame();
		break;
	    // карты <--
	    // КОСТИ -->
	    case "Dice_Rule":
   			dialog.text = DICE_RULE;
			link.l1 = "さて、始めようか……";
			link.l1.go = "Dice_begin";
			link.l3 = "いや、俺のためじゃねえんだ……";
			link.l3.go = "exit";
		break;

		case "Dice_begin":
			Diag.tempnode = "Dice_Node";
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			pchar.questTemp.friend_in_tavern = npchar.id;
			AddDialogExitQuest("alc");
		break;

		case "Dice_Node":
		    Diag.tempNode = "first time";		    
			Dialog.text = "賭け金を決めよう（賭け金を入力してくれ）。";
			link.l1 = "50";
			link.l1.edit = 1;
			link.l1.go = "Dice_Node_2";
			link.l3 = "行かなきゃならねえな。";
			link.l3.go = "exit_sit";
		break;

		case "Dice_Node_2":
			iLa_Puesta = GetStrSmallRegister(dialogEditStrings[1]);
            if (!CheckDiceGameSmallRate())
		    {
				dialog.text = "お前は悪名高いイカサマ師だ。俺はお前とサイコロを振らねえ。";
                link.l1 = "全部嘘だ！まあ、どうでもいいさ。";
			    link.l1.go = "exit_sit";
			    break;
		    }

			if (sti(pchar.Money) < sti(iLa_Puesta)*6)
		    {
                dialog.text = "「金がねえみたいだな、」 "+GetSexPhrase("友達","「あなた」")+"。金持ちになったら戻ってこい。";
                link.l1 = "「いいだろう。」";
			    link.l1.go = "exit_sit";
			    break;
		    }
			
			if (sti(npchar.Money) < sti(iLa_Puesta)*6)
		    {
                dialog.text = "俺はもう持っていたものをすべて失っちまった。今日は運の悪い日だぜ。";
                link.l1 = "「いいだろう。」";
			    link.l1.go = "exit_sit";
			    break;
		    }
		else
		{
			if(sti(iLa_Puesta) < 50)
			{
				dialog.text = "俺を笑ってるのか、それとも何だ！？遊んでるのか "+iLa_Puesta+" 1日あたりペソだと！？もっと手頃な賭け金でやろうぜ、じゃなきゃ俺は降りる！";
				link.l1 = "ああ、その通りだ。もう少し賭け金を上げる必要があるな。";
				link.l1.go = "Dice_begin_2";
				link.l2 = "気が変わった、俺はやらない。";
				link.l2.go = "exit_sit";
				break;
			}
			
			if(sti(iLa_Puesta) > 1000)
			{
				dialog.text = "そんな大金でサイコロをやるのか？いや、俺は遠慮しとくぜ、賭け金を変えない限りな。";
				link.l1 = "ああ、その通りだ。賭け金を少し下げる必要があるな。";
				link.l1.go = "Dice_begin_2";
				link.l2 = "実は、まったく遊ばないことにしたんだ。";
				link.l2.go = "exit_sit";
				break;
			}
			dialog.text = "よし、それじゃあ賭けようか "+iLa_Puesta+" 「1個のサイコロごとにコイン。」";
			link.l1 = "行くぜ！";
			link.l1.go = "Dice_begin_go";
			pchar.GenQuest.Dice.npcharIdx = npchar.index;
			pchar.GenQuest.Dice.iRate     = sti(iLa_Puesta);
            pchar.GenQuest.Dice.SitType   = true;
		}
		break;
		
		case "Dice_begin_2":
			dialog.text = "それで、賭けは何だ？（賭け金を入力せよ）";
			link.l1 = "50";
			link.l1.edit = 1;
			link.l1.go = "Dice_Node_2";
			link.l2 = "やっぱり俺は遊ばないことにするぜ……";
			link.l2.go = "exit_sit";
			break;

		case "Dice_begin_go":
            // анлим игры в день SetNPCQuestDate(npchar, "Dice_date_begin");
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
            LaunchDiceGame();
		break;
	    // КОСТИ <--

		/////////////////////////////////////////////
        case "talk_with_alchogol_song":
			dialog.text = "おう、ひっく！調子はいいぜ。ひっく！油断してるとやられるからな。ひーっく！このラムは最高だ。 ジャマイカのブラックラムだぜ。ひっく！\nほら、自分で一杯注げよ！";
			link.l1 = "よし、いいだろう。";
			link.l1.go = "talk_with_alchogol_song_2";
			link.l2 = "悪いな、友よ、俺は行かなきゃならねえ。";
			link.l2.go = "exit";
		break;
		
		case "talk_with_alchogol_song_2":
			dialog.text = "ジョッキも顔も次々と入れ替わる……ひっく……床に倒れるまでな。俺はずっと飲んでるぜ……ひっく！酒はどこだ……で、何の歌だったっけ……";
			link.l1 = "酒はここにあるし、女たちも上物だ。みんなバッカニアを欲しがってるが、俺のものになるのはラム酒だけみたいだぜ。";
			link.l1.go = "talk_with_alchogol_song_3";
			link.l2 = "こんなことにかまってる暇はねえ。";
			link.l2.go = "exit";
		break;
		
		case "talk_with_alchogol_song_3":
			dialog.text = "悲しい時は考え込むな、こっちに来て一緒に飲もうぜ！\nきっとすべてうまくいくさ、俺はお前の友達、お前も俺の友達だ！";
			link.l1 = "友がいるのは本当に素晴らしいことさ、いなくなっても待っていてくれる。\n友がいれば憎しみなんてない。だがラムがなくなれば、ただ口論が残るだけ。\nだから飲もうぜ、相棒、俺が行って遅れる前にな… ";
			link.l1.go = "exit";
		break;
		
		case "talk_with_alchogol":
			Diag.TempNode = "begin_sit";
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			pchar.questTemp.friend_in_tavern = npchar.id;
			AddDialogExitQuest("alc");
		break;

		case "begin_sit":
			Diag.TempNode = "first time";
			dialog.snd = "Voice\HADI\HADI028";
			dialog.text = LinkRandPhrase("ひっく！これでよし！ずっとよくなったぜ！で、どうする？俺にラム酒をおごってくれるのか、それともどうなんだ？","「座れ」 "+GetAddress_Form(npchar)+"さあ、昔ながらのジャマイカ産ラムを一杯やろうぜ。体にも悪くねえしな。それに、今何が起きてるか気になるなら――この酒場ほどいい場所はねえって保証するぜ。ちょっと金を出して、まともなラムを二、三杯飲めば、知りたいことも、 それ以上のこともわかるさ。年季の入った常連を信じな…","へっ、どうぞ、座ってくれ。 "+GetSexPhrase("親愛なる友","お嬢さん")+"、一杯やろうぜ…いい仲間と飲むのも悪くねえだろ？ゆっくりと、ちびちび飲みながら辛抱強く耳を傾けてりゃ、 面白い話がたくさん聞けるもんさ…冒険を自慢する船長もいれば、酔いが回って大事なことを口走る奴もいる…そこにはいろんな連中が集まってて、誰もが何かしら話したいことを持ってるんだ、信じてくれよ、\n "+GetSexPhrase("俺の親友","Miss")+".");
			link.l1 = "もちろんだ！酒場の親父！俺たち二人にラムを持ってこい！";
			link.l1.go = "sit_2";
		break;

		// Церковный генератор. Квест №2 -->
		case "Alcogol_GenQuest_Church_2_1":
			dialog.text = "もちろんだ！聞いたか…盗賊どもは教会まで襲うらしいぞ！";
				link.l1 = "なるほど、それは海賊の仕業だろう、他に誰がいるってんだ…";
				link.l1.go = "Alcogol_GenQuest_Church_2_2";
				DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.AskPeople");
				DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.AskBarmen");
				DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.AskAlcash");
			break;
			
		case "Alcogol_GenQuest_Church_2_2":
			dialog.text = "どんな海賊だって？ただの陸の素人どもさ、しかもきっとこの辺の連中に違いねえ……もしよそ者だったら、教会の金庫がいつ満杯になるかなんて知るわけねえだろう。そもそも、 あんな厄介ごとに巻き込まれるはずもねえさ。";
				link.l1 = "勇敢な奴らだな、間違いねえ。あんな頼りない扉の閂を堂々と開けやがって…";
				link.l1.go = "Alcogol_GenQuest_Church_2_3";
			break;
			
		case "Alcogol_GenQuest_Church_2_3":
			dialog.text = "ほう、しかも賢い連中だな。そんな風に自分をさらけ出す奴がいるか？";
				link.l1 = "その通りだ。教区全体が教会への寄付のためにお金を貯めていたのに、 今やあの抜け目ない連中がそれで一儲けしたってわけか？きっと奴らは捕まるだろう。 今や誰もが奴らを探しているからな。";
				link.l1.go = "Alcogol_GenQuest_Church_2_4";
			break;
			
		case "Alcogol_GenQuest_Church_2_4":
			dialog.text = "とんでもない。誰があいつらを探すってんだ？やつらは教会を襲って町を出て、風のように消えちまったんだ。 ジャングルは広い、ものすごく広いんだぜ。あんな所で探したら、死ぬまで見つかりゃしねえよ。しかも、 数ヶ月もすりゃ、みんなそんなこと忘れちまうさ、俺の言うこと信じな！";
				link.l1 = "そうは思わねえ。そんなこと、許されるわけがねえ。";
				link.l1.go = "Alcogol_GenQuest_Church_2_5";
			break;
			
		case "Alcogol_GenQuest_Church_2_5":
			dialog.text = "人間の記憶なんて、漏れる小舟みたいなもんだ。人は忘れるし、許してくれるさ。だが、神様は違う！ 神様はすべてを見ておられる。恐れるべきは神様だぜ。俺の古い仲間にもな、十年前にひどいことが起きたんだ。 あいつも創造主への敬意が足りなくて、もう少しで海の悪魔のもとへ直行するところだったんだよ…";
				link.l1 = "悪いな、友よ、俺は行かなくちゃならねえ。その仲間の話はまた今度にしよう。じゃあな。";
				link.l1.go = "Alcogol_GenQuest_Church_2_6";
			break;
			
		case "Alcogol_GenQuest_Church_2_6":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("exit_sit");			
			string sGenLocation = QuestGetGangLocation(PChar.GenQuest.ChurchQuest_2.QuestTown);
			PChar.GenQuest.ChurchQuest_2.QuestGangJungle = sGenLocation;
			SetFunctionLocationCondition("Church_GenQuest2_GenerateBandits", sGenLocation, false);
			locations[FindLocation(sGenLocation)].DisableEncounters = true;
			PChar.GenQuest.ChurchQuest_2.WayOfShortVariant = true; // Нужно для проверки при убийстве банды
			SetFunctionTimerConditionParam("Church_GenQuest2_TimeIsLeft", 0, 0, 1, MakeInt(24 - GetHour()), false);
			Log_TestInfo("The bandits who raided the church shall be in location - " + sGenLocation + " Time to search for them - 1 day");
			sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "2");
			break;
		// <-- Церковный генератор. Квест №2
		//--> работорговец
			case "Jamaica_ratH_1":
				dialog.text = "おお、フランソワか！ああ、あいつのことはもちろん覚えてるぜ…いや、知らねえな。でもよ、うちの給仕に聞いてみな。あいつがここにいた間、毎晩一緒に過ごしてたんだ。 あの女は間違いなく尻軽だぜ。もしかしたら、何かペラペラしゃべったかもしれねえな。";
				link.l1 = "助言ありがとな、相棒。これからあの女に話をしに行くぜ。";
				link.l1.go = "exit_sit";
				pchar.questTemp.Slavetrader = "FindRatJamaica_W";
			break;
			
			case "EscapeSlave_Villemstad_H1":
				dialog.text = "ああ、時々外洋では本当に奇妙なことが起こるもんだぜ。俺の前の航海じゃ、本当に……\n";
				link.l1 = "さあ、話してくれ。ただし大げさには言うなよ。その間にラムをもう少し持ってきてやるぜ。";
				link.l1.go = "EscapeSlave_Villemstad_H2";
			break;
			
			case "EscapeSlave_Villemstad_H2":
				dialog.text = "神に誓うぜ、貴族"+GetSexPhrase("旦那","ご婦人")+" - この目で見たんだ……船が航海してたんだが、船員の代わりに巨大な猿がいてさ……マカクか何か……つまり、サルだよ。";
				link.l1 = "「なんだと！？教えてくれ、友よ、お前も見張り中に酒を飲んでるのか？」";
				link.l1.go = "EscapeSlave_Villemstad_H3";
			break;
			
			case "EscapeSlave_Villemstad_H3":
				dialog.text = "俺が嘘ついてたら目が見えなくなってもいいぜ！猿エビの話を聞いたことねえのか？くそっ、エビだってよ、ははは！…いや、猿船だ。";
				link.l1 = "「猿船ってなんだ？」";
				link.l1.go = "EscapeSlave_Villemstad_H4";
			break;
			
			case "EscapeSlave_Villemstad_H4":
				dialog.text = "おおっと、言うぞ、俺はこの目で見たんだ。嵐だった。何も見えやしねえ、そしたら突然船が現れたんだ。帆はボロボロ。 前帆も大破してて、大帆も同じく、神に誓って、全部めちゃくちゃだった！それなのに、 あの船は逆風に向かって突っ込んできたんだ！\nそして甲板には猿がいた…それも山ほど、まるでアザラシの群れみたいによ！舵輪には本物のゴリラが立ってたんだぜ！身の丈九尺、赤いシャツ、 胸には十字架の代わりにサメの歯…目は真っ赤に燃えて、牙がギラリと光って、俺たちを見て何か叫んだんだ…";
				link.l1 = "お前は真っ赤な嘘をついてるな、相棒。酔っぱらうと幻が見えるもんだ。 次はあの女がフライング・ダッチマンだったって言い出すんじゃねえか。";
				link.l1.go = "EscapeSlave_Villemstad_H5";
			break;
			
			case "EscapeSlave_Villemstad_H5":
				dialog.text = "いや、あれはオランダ船じゃなかった。本当のことを言ってるんだ！バーク船で、船尾には銘があったんだ―― "+pchar.questTemp.Slavetrader.ShipName+".";
				link.l1 = "ちくしょう！お前が言ってた「猿」ってやつが何かわかった気がするぜ。確かにラム酒は口を軽くさせるもんだな……あとは耳を澄ませりゃいいだけだ。";
				link.l1.go = "EscapeSlave_Villemstad_H6";
			break;
			
			case "EscapeSlave_Villemstad_H6":
				dialog.text = "見ただろう、言ったじゃねえか！それでも信じなかったくせに…よし、最後の一杯をあおって、俺はもう行くぜ。";
				link.l1 = "わかった、面白い話をありがとう。俺は行かなくちゃならねえ。幸運を祈るぜ、相棒。";
				link.l1.go = "exit_sit";
				Pchar.quest.Slavetrader_EscapeSlave.win_condition.l1 = "location";
				Pchar.quest.Slavetrader_EscapeSlave.win_condition.l1.location = pchar.questTemp.Slavetrader.Island.Shore;
				Pchar.quest.Slavetrader_EscapeSlave.function = "Slavetrader_EscapeSlaveInShore";
				AddQuestRecord("Slavetrader", "22_4");
				AddQuestUserData("Slavetrader", "sAreal", pchar.questTemp.SlavetraderAreal.add);
				pchar.questTemp.Slavetrader = "FindMayak";
			break;
		
		//Голландский Гамбит, против всех
		case "Lucas_Tavern":
			DelMarkInTavernHWIC();
			dialog.text = "いいえ、船長。俺には水夫の人生は向いてねえんだ。実はな、俺もかつては船を持ってたんだが……とんでもねえ不運に見舞われちまったんだよ。";
			link.l1 = "聞いてくれ――沖合に見慣れない船が停泊しているんだ――名前は「Meifeng」っていう。あんな船は今まで見たことがねえ。誰の持ち物なんだ？もしかして売りに出てるのか？ ちょっと見てみたいんだが。";
			link.l1.go = "Lucas_Tavern_1";
		break;
		
		case "Lucas_Tavern_1":
			dialog.text = "はっ！とんでもねえよ、船長。その中国人があんたにも他の誰にも自分の船を売るとは思えねえな。";
			link.l1 = "中国人だと？キュラソーに中国人がいるのか？しかも自分の船を持つ船長までいるとは！？";
			link.l1.go = "Lucas_Tavern_2";
		break;
		
		case "Lucas_Tavern_2":
			dialog.text = "ご覧の通り、ありますよ。しかし、これは彼の船ではなくて、実は交易会社の所有物です。副社長であり、 今は代理総督を務めているローデンブルク旦那が持ち主だそうです。";
			link.l1 = "それで、マティアス・ベックは引退したのか？";
			link.l1.go = "Lucas_Tavern_3";
		break;
		
		case "Lucas_Tavern_3":
			dialog.text = "はっ！旦那、もっと陸に上がるべきだぜ――せめて噂くらいは耳に入れておきな。マティアス・ベックは解任されて、 すべての事情が明らかになるまで牢にぶち込まれたんだ。";
			link.l1 = "そりゃ驚いたぜ！確かに、俺は海の上で過ごしすぎてるな。それで、いつそんなことが起きたんだ？";
			link.l1.go = "Lucas_Tavern_4";
		break;
		
		case "Lucas_Tavern_4":
			dialog.text = "実は、ほんの数日前のことだ。港に急使のブリガンティンが到着したんだ。船の状態はあまり良くなくて、 どう見ても激しい戦闘に巻き込まれた様子だった。船長はすぐにローデンブルク旦那のもとへ報告に向かったよ。 そして数時間後には、マティアス・ベックがローデンブルク旦那と司令官によって、 イギリスの諜報機関と通じていた疑いで逮捕されたんだ。";
			link.l1 = "ひどいことを言うな。どうしてキュラソー総督がイギリスの間者だなんてありえるんだ？";
			link.l1.go = "Lucas_Tavern_5";
		break;
		
		case "Lucas_Tavern_5":
			dialog.text = "正直なところ、俺自身もほとんど信じられねえよ。まもなく会社の総監督、 ピーター・スタイフェサント本人がここに来るって聞いたんだ。どうやら彼が自ら調査を行うらしいぜ。";
			link.l1 = "それならお前の言う通りだな。今この時にローデンブルク旦那を煩わせるのは危険かもしれねえ。";
			link.l1.go = "Lucas_Tavern_6";
		break;
		
		case "Lucas_Tavern_6":
			dialog.text = "いい考えだな、船長！特に今は「メイフェン」が積み込み中だからな。ちょうど本土南岸への航海から戻ったばかりで、 もうすぐまた出航するんだ。それに、言っておくが、あそこでは妙なことが起きてるぜ。 オランダ人の水夫や会社の護衛たちは任務を解かれ、新しい乗組員が集められてる。 そして俺がこれまで飲んだラム酒の杯にかけて誓うが、その新しい志願者たちはまるで別物だ、全員が海賊や盗賊、 殺し屋ばかりなんだよ！";
			link.l1 = "まさに奇跡だな！まあ、残念だぜ！あんな立派な船が……だが、運命ってやつは違う道を選んだんだな……面白い話と知らせをありがとう！お前と話せて楽しかったぜ！";
			link.l1.go = "Lucas_Tavern_7";
		break;
		
		case "Lucas_Tavern_7":
			dialog.text = "ああ、船長、付き合ってくれてラムもありがとう！またいつでも寄ってくれよ！";
			link.l1 = "もちろんやるぜ！";
			link.l1.go = "exit_sit";
			AddQuestRecord("Holl_Gambit", "3-44");
			pchar.questTemp.HWIC.Self = "AttackMeifeng";
			//ставим прерывание на выход в море Мейфенг
			pchar.quest.HWIC_Meifeng.win_condition.l1 = "Timer";
			pchar.quest.HWIC_Meifeng.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.HWIC_Meifeng.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.HWIC_Meifeng.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.HWIC_Meifeng.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.HWIC_Meifeng.function = "CreateMeifengOnMap";
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			SetFunctionTimerCondition("QuestShipsTerms_Over", 0, 0, 12, false); // таймер
			pchar.quest.Meifeng_fail.over = "yes"; //снять прерывание
			Group_DelCharacter("Meifeng_Empty", "Longway");
			Group_DeleteGroup("Meifeng_Empty");//удалить Мейфенг из порта
		break;
		
			//Jason --> поиск дезертира
		case "FindFugitiveHb":
			npchar.quest.fugitive = "true";
			if (npchar.location == pchar.GenQuest.FindFugitive.City+"_tavern" && sti(pchar.GenQuest.FindFugitive.Chance) == 2)
			{
				pchar.GenQuest.FindFugitive.Shore = SelectQuestShoreLocation();
				dialog.text = "「はっ！」 "+pchar.GenQuest.FindFugitive.Name+"？わかってる、わかってるよ……あんたの仲間は本当に無愛想な奴だな。いわば一匹狼ってやつさ。あいつは一日中ロングボートで島の沿岸をうろついて、 日が暮れるまで戻らねえ。みんな漁師だと思ってるが、実は真珠採りなんだよ……へっ！俺はそれを間違いなく知ってるぜ！";
				link.l1 = "へっ！それで…奴がどこにいるか教えてくれるか？";
				link.l1.go = "FindFugitiveHb_1";
			}
			else
			{
				dialog.text = ""+pchar.GenQuest.FindFugitive.Name+"「？いや、誓ってそんな奴は聞いたことねえよ……でもな、お前さんは――ヒック！酒場の旦那に聞いてみな、あいつならきっと知ってるはずだぜ！」";
				link.l1 = "ふむ……よし、もう少し聞き込みしてみるか。\nじゃあな、相棒。付き合ってくれてありがとな。またな！";
				link.l1.go = "exit_sit";
			}
		break;
		
		case "FindFugitiveHb_1":
			dialog.text = "もちろんできるぜ！毎朝あいつは岸辺で見かける、場所は "+XI_ConvertString(pchar.GenQuest.FindFugitive.Shore+"Gen")+"。できるだけ早く来てくれ、さもないと彼は出航してしまうから、次の朝まで待たなきゃならなくなるぞ。";
			link.l1 = "助かったぜ！お前には本当に世話になった、相棒！またな！";
			link.l1.go = "exit_sit";
			pchar.GenQuest.FindFugitive.Chance = 3; // чтобы никто больше не говорил
			AddQuestRecord("MayorsQuestsList", "12-3");
			AddQuestUserData("MayorsQuestsList", "sShore", XI_ConvertString(pchar.GenQuest.FindFugitive.Shore+"Gen"));
			sld = characterFromId("Fugitive");
			LAi_SetWarriorType(sld);
			LAi_warrior_DialogEnable(sld, true);
			sld.dialog.currentnode = "Fugitive_shore";
			LAi_SetLoginTime(sld, 4.0, 6.0);
			ChangeCharacterAddressGroup(sld, pchar.GenQuest.FindFugitive.Shore, "goto", "goto1");
		break;
		//<-- поиск дезертира
		
		// Карибские нравы
		case "trial_spy":
			dialog.text = "奴はうちの造船所をうろついてて、船大工たちにあれこれ聞いて回ってたんだ。それが仇になったのさ。 町で怪しい奴がうろついてるって誰かが司令官に知らせてな、そいつは捕まっちまった。それで結局、 商人なんかじゃなかったってバレたんだ。";
			link.l1 = "お前の船大工から何か秘密の計画を盗もうとしていたってことか？";
			link.l1.go = "trial_spy_1";
		break;
		
		case "trial_spy_1":
			dialog.text = "誰にも分からねえさ。でもな、最初から奴がガレオン船『アラカンタラ』に興味を持ってたのは間違いねえ！ひっく！ それは誓ってもいいぜ！この船は旦那総督自らが装備してるんだ、 だからあのろくでなしが何か探りを入れようとしたに違いねえ。";
			link.l1 = "はっ！そりゃありそうだな。きっと総督が何か貴重なものを積み込むに違いねえ……";
			link.l1.go = "trial_spy_2";
		break;
		
		case "trial_spy_2":
			dialog.text = "それは言うまでもねえぜ！きっと本当に注目すべき何かに違いねえ、俺が保証する！\nそれとよ、漁師たちがこの海域で異国の軍艦を見たって噂してた……たぶんフリゲートだろうな。\nもしかして、そのスパイはそこから来たんじゃねえか？";
			link.l1 = "ああ、そうかもな……よし、相棒、付き合ってくれてありがとな。でも俺はもう行かなきゃいけねえ！";
			link.l1.go = "exit_sit";
			Trial_Habitue_DlgExit();
		break;
		
		case "sit_2":
			Statistic_AddValue(pchar, "TavernDrink", 1);
			AddMoneyToCharacter(pchar, -2);
			//navy --> Alcohol - rum count;
			if(!IsEquipCharacterByArtefact(pchar, "totem_01"))
			{
				if (CheckAttribute(pchar, "questTemp.Rum"))
				{
					pchar.questTemp.Rum = sti(pchar.questTemp.Rum) + 1;
				}
				else pchar.questTemp.Rum = 1;
			}
			else 
			{
				if(CheckAttribute(pchar, "questTemp.Rum")) DeleteAttribute(pchar, "questTemp.Rum");
			}				
			//<-- navy
			if(!CheckAttribute(pchar, "questTemp.TimeLock")) WaitDate("",0,0,0, 0, 30);
			
			if (CheckAttribute(pchar, "questTemp.Rum"))
			{
				DeleteAttribute(pchar, "chr_ai.drunk");
				if (sti(pchar.questTemp.Rum) < 3) LAi_AlcoholSetDrunk(pchar, 51, 5600);
				else
				{
					LAi_AlcoholSetDrunk(pchar, 71, sti(pchar.questTemp.Rum)*2800);
					Pchar.GenQuest.CamShuttle = makeint(sti(pchar.questTemp.Rum)/2); // Jason
				}
			}
			
			// Sinistra - Квест "Путеводная звезда" ==>
			if (CheckAttribute(pchar, "questTemp.PZ_BasTerAlkash") && npchar.city == "baster")
			{
				dialog.text = "あなたの健康と寛大さに乾杯！";
				link.l1 = "おい、相棒、この町で中国人を見かけなかったか？";
				link.l1.go = "PZ_BasTerAlkash_1";
				break;
			}
			// <== Квест "Путеводная звезда" - Sinistra
			
			dialog.text = LinkRandPhrase("お前は "+GetSexPhrase("本当の友","いい女")+"！はじめまして！乾杯！","ひっく！うまいラムだな！ひっく……乾杯！","あなたの健康と寛大さに乾杯！");
			link.l1 = "へえ、こいつは本当に強いラムだな。さて、俺は行かなくちゃ。楽しんでくれよ！";
			link.l1.go = "exit_sit";
			if (makeint(pchar.money) >=2)
			{
				link.l2 = "もう一杯どうだ、構わねえか？";
				link.l2.go = "sit_3";
			}

			link.l4 = LinkRandPhrase("まるで永遠に海の上にいる気分だ。何か新しい知らせはあるか？","人々は何と言っている？もちろん、俺が酒を奢ってやるぜ。","なあ相棒、最近酒場で流行ってる噂話は何だ？");
			link.l4.go = "rumours_habitue";
		break;

		case "sit_3":
			int iSituation;
			if(IsEquipCharacterByArtefact(pchar, "totem_01")) iSituation = makeint(rand(3));
			else iSituation = makeint(rand(5));
			switch (iSituation)
			{
				case 0:
					dialog.text = "おお！素晴らしい考えだな！";
					link.l1 = "バーテンダー！ラムをもっと持ってこい！";
					link.l1.go = "sit_2";
				break;

				case 1:
					dialog.text = "お前にだ！くそっ！誰だ、あれは？";
					link.l1 = "えっ？なんだ？どこだ？幻でも見てるのか。";
					link.l1.go = "sit_2";// to_do "sit_case_5_exit";
				break;
				
                case 2:
	         		dialog.text = "さあ、飲もうぜ！もう一杯どうだ？";
					link.l1 = "進め！";
					link.l1.go = "sit_2";
                break;				
				
				case 3:
					if(rand(1) == 0)
					{
						dialog.text = RandPhraseSimple("「おい、そこのお前」 "+GetAddress_Form(NPChar)+"、お前はきっと皆がお前を称賛してると思ってるんだろうな？でもな、俺に言わせりゃただの普通の盗賊だぜ！…それに人殺しだ！“高貴な海賊”だと！？はっ！盗賊は盗賊だ…ひっく…陸でも海でもな…","「ヒック！」 "+GetSexPhrase("くっ…くそ野郎","くっ…汚え")+"「！俺に酔いつぶれるまで飲ませて、ひっく、そしたら全部の金を盗むつもりだな！」");
						link.l1 = "もう十分飲んだみたいだな……酔いをさましてこい……俺も行かなくちゃ……";
						link.l1.go = "exit_sit";						
						link.l2 = "お前の口のきき方が気に入らねえぜ、相棒。舌を慎めよ、わかったか？";
						link.l2.go = "sit_case_2_enemy";
						link.l3 = "今なんて言った、陸のネズミが！？腹に穴が開いたら、どんな口をきくか見せてもらおうじゃねえか！";
						link.l3.go = "sit_case_2_enemy2";
					link.l4 = "落ち着けよ！忘れたのか？俺はお前の唯一の本当の友達だぜ！";
					link.l4.go = "sit_case_2_friend";		
					}
					else
					{
						// Captain Beltrop, 27.06.21, новый вариант
						/* if (rand(1) == 0)
						{
							Diag.CurrentNode = Diag.TempNode;
							AddDialogExitQuestFunction("Tavern_SetBadHabitue");
							DialogExit();
						}
						else
						{ */
							dialog.text = RandPhraseSimple("なんで俺をじろじろ見てやがるんだ？俺が酔いつぶれるまで待って――ひっく――それから俺の金を全部盗むつもりだろ！この下賤な連中はどこから湧いてきやがったんだ？！ひっ……この酒場にはまともな人間の居場所なんてねえのか？","俺のことを尊敬してるか？…ああ、お前だよ！俺のことを尊敬してるのか！？よく覚えとけよ…俺はなめられるような奴じゃねえ…一発、目の間に食らわせりゃ…お前なんざもう終わりだぞ…");
							link.l1 = "おい、相棒、お前は豚みたいに酔っ払ってるぜ。家に帰って寝てこいよ……俺も行かなきゃならねえ……";	
							link.l1.go = "exit_sit";
							link.l2 = "落ち着けよ、相棒。誰に話してるのか気をつけろよ。";
							link.l2.go = "sit_case_2_enemy1";
							link.l3 = "今なんて言った！？痛い目にあわせてやるぜ！";
							link.l3.go = "sit_case_2_enemy2";
							link.l4 = "落ち着け！俺のことを忘れたのか？俺はお前の唯一の本当の友だぜ！";
							link.l4.go = "sit_case_2_friend";	
						//}
					}
				break;

				case 4:
					dialog.text = "聞いてくれ！あんたはいい奴だな！もしかしたら……ちょっとしたことで俺を助けてくれないか？";
					link.l1 = "いや、もう行かなくちゃいけないと思う。";
					link.l1.go = "exit_sit";
					link.l2 = "もちろんだ！ひっく！俺たちは友達だろ…なあ？ひっく！";
					link.l2.go = "sit_case_3";
				break;

				case 5:
					if (GetSummonSkillFromName(pchar, SKILL_SNEAK) > rand(110) || CheckAttribute(pchar, "questTemp.Sharlie.Lock"))
					{
						dialog.text = "「……そ、それで俺はあいつのサーベルの刃をつ、つかんじまったんだ……」";
						link.l1 = "…それから彼女はこう言った…";
						link.l1.go = "sit_2";
					}
					else
					{
						dialog.text = "「……それで俺は、そいつのサーベルの刃を、つ、つかんじまったんだ……」";
						link.l1 = "…ひっく！…それで彼女がこう言ったんだ…";
						link.l1.go = "sit_case_4_exit";
					}
				break;
			}
		break;

		case "sit_case_5_exit": // дуэль
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("fighting");
		break;

		case "sit_case_4_exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			pchar.questTemp.friend_in_tavern = npchar.id;
			AddDialogExitQuest("without_memory");
		break;

		case "sit_case_3":
			dialog.snd = "Voice\HADI\HADI037";
			dialog.text = "「だ、だから…その、兵士の一人が俺を侮辱したんだ。それだけだ！」";
			link.l1 = "兵士、ですか？い、いや、遠慮しておきます。";
			link.l1.go = "exit_sit";
			link.l2 = "落ち着け！俺のことを忘れたのか？俺はお前の唯一の本当の友だぜ！";
			link.l2.go = "sit_2";
		break;

		case "sit_case_2_friend":
			dialog.snd = "Voice\HADI\HADI038";
			dialog.text = "お前か？どんな友達だよ、お前は？い、いやだ！お前…お前は俺を殺すつもりだろ！そ、そうなんだな！";
			link.l1 = "もう十分飲んだだろう。じゃあな。";
			link.l1.go = "exit_sit";
			link.l2 = "何だと？お、お前を殺すつもりなんかないって証明してやるよ！俺は…お前の手を切り落としてやる！…それがなけりゃ殺されることはねえ！…ひっく！";
			link.l2.go = "sit_case_2_friend_2";
		break;

		case "sit_case_2_friend_2":
			dialog.snd = "Voice\HADI\HADI039";
			dialog.text = "ああっ！持っていけ "+GetSexPhrase("彼","彼女")+" 俺に近寄るな！";
			link.l1 = "落ち着けよ……ひっく……痛くねえって！……髭剃りよりも楽だぜ！";
			link.l1.go = "tavern_keeper";
		break;

		case "sit_case_2_enemy":
			dialog.snd = "Voice\HADI\HADI040";
			dialog.text = "俺を脅そうなんて思うな！ひっく！俺はそんなに簡単に怯えねえぞ…！\nそれにお前は…お前みたいな奴は絞首台にぶら下がってるべきだ…お仲間もみんなな、ひっく！いくら威張って羽を広げても、腐った魚の臭いが消えねえんだよ！\nそれに俺はな、ひっく！お前らみたいな奴と話すときに言葉を選ぶ気なんてねえ！みんな大嫌いだ！";
			link.l1 = "ああ、なんでこんな酔っ払いと話してるんだよ……ちょっと外の新鮮な空気でも吸いに行くか……";
			link.l1.go = "exit_sit1";
			link.l2 = "お前はずいぶん大胆だな、相棒。てめえの言葉、そのまま喉に叩き込んでやるぜ！";
			link.l2.go = "sit_case_2_enemy3";
		break;

		case "sit_case_2_enemy1":		
			dialog.snd = "Voice\HADI\HADI040";
			dialog.text = "な、なんだと！？この手でお前を絞め殺してやる！ひっく……今まで俺から逃げ切った奴はいねえんだ、ひっく……！";
			link.l1 = "お前は酔っ払いの豚じゃねえか？せっかくのいい夜を台無しにしやがって……まあいい、好きにゴキブリでも捕まえてろ。俺はもう行くぜ。";
			link.l1.go = "exit_sit1";
			link.l2 = RandSwear()+"黙るつもりはなさそうだな。なら、礼儀ってものを教えてやるぜ。";
			link.l2.go = "sit_case_2_enemy3";
		break;
		
		case "sit_case_2_enemy2":	
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			if(rand(1) == 0)
			{
				dialog.text = LinkRandPhrase("近寄れ、この野郎！お前には相応の報いをくれてやるぜ！",RandSwear()+"貴様には相応の報いをくれてやるぜ！","ははっ！よし、海の野郎――陸の上でどれだけやれるか見せてもらおうじゃねえか！");
				link.l1 = RandPhraseSimple(RandPhraseSimple("誓ってやる、後悔させてやるぞ！","その汚ねえ舌、耳のために短くしてやるぜ！"),RandPhraseSimple("てめえを豚みてえに腹からケツ、そして口って呼ばれてるクソ穴まで切り裂いてやるぜ！","黙らせてやるって誓うぜ！"));
				link.l1.go = "fight_right_now";
			}
			else
			{
				dialog.text = "おい、野郎ども！このクズどもを俺たちの町から叩き出すぞ！";
				link.l1 = RandPhraseSimple(RandSwear()+"覚悟しやがれ、この野郎ども！","おお、ひとりじゃねえのか！？まあいいさ――地獄でも仲間ができるってわけだ！");
				link.l1.go = "fight_right_now_1";
			}
		break;
		
		case "sit_case_2_enemy3":	
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
			if(rand(1) == 0)
			{
				dialog.text = LinkRandPhrase("近寄れ、この野郎！お前にはふさわしい報いをくれてやるぜ！",RandSwear()+"お前にはふさわしい報いをくれてやるぜ！","ははっ！よし、海の野郎――陸の上でどれほどやれるか見せてもらおうじゃねえか！");
				link.l1 = RandPhraseSimple(RandPhraseSimple("必ず後悔させてやるぜ！","その汚ねえ舌、耳まで切り落としてやるぜ！"),RandPhraseSimple("てめえを豚みてえに腹から口って呼ばれてるクソ穴まで切り裂いてやるぜ！","黙らせてやるって誓うぜ！"));
				link.l1.go = "fight_right_now";
			}
			else
			{
				dialog.text = "おい、野郎ども！このクズどもを俺たちの町から叩き出すぞ！";
				link.l1 = RandPhraseSimple(RandSwear()+"祈りでも捧げな、野郎ども！","おお、ってことは一人じゃねえのか！？そりゃよかったな――地獄でも仲間ができるぜ！");
				link.l1.go = "fight_right_now_1";
			}
		break;		
		
		case "exit_sit":			
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("exit_sit");
		break;

		case "exit_sit1":
			ChangeCharacterComplexReputationToNeutral(pchar,"nobility", 2.0);			
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("exit_sit");
		break;
				
		case "tavern_keeper":			
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("tavern_keeper");
		break;
		
		// Captain Beltrop, 27.06.21, новый вариант
		case "bad_habitue":
			dialog.text = "おい、わけがわからねえ！角を曲がった途端に、新入りが俺の場所を取ってやがった。さっさと失せろ！";
			link.l1 = "いつも同じだな。席に座ろうとすると、もう誰かが取ってるってわけさ……まあ、席はそのままにしておけよ。どうせ俺はもう出ていくところだったからな。";
			link.l1.go = "bad_habitue1";
			link.l2 = "もう一言でもそんな汚い口をきいたら、それが貴様の最後の言葉になるぞ、わかったか？";
			link.l2.go = "bad_habitue2";
			link.l3 = "ここが本当にお前の場所だったかどうかは知らねえが、そんな口のきき方は許さねえ。言葉に気をつけろよ。";
			link.l3.go = "bad_habitue3";
		break;
		
		case "bad_habitue1":
			DialogExit();
			pchar.questTemp.BadHabitueSit = true; // атрибут усаживания
			AddDialogExitQuest("exit_sit");
		break;
		
		case "bad_habitue2":
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			if(rand(1) == 0)
			{
				dialog.text = LinkRandPhrase("かかってこい、この野郎ども！たっぷり味わわせてやるぜ！",RandSwear()+"今度こそ、きっちり剥いでやるぜ！","ははっ！来いよ、水夫――陸でお前の腕前を見せてもらおうじゃねえか！");
				link.l1 = RandPhraseSimple(RandPhraseSimple("これを後悔することになるぜ！","てめえの汚ねえ舌を引きちぎってやるぜ！"),RandPhraseSimple("てめえを豚みてえに腹からケツまで切り裂いてやる、そのクソみてえな口までな！","黙らせてやるって誓うぜ！"));
				link.l1.go = "fight_right_now";
			}
			else
			{
				dialog.text = "行くぞ、野郎ども！こいつらのクズを俺たちの町から叩き出すぞ！";
				link.l1 = RandPhraseSimple(RandSwear()+"祈れ、この野郎ども！","「おっと、一人じゃねえんだな！まあ、地獄で仲間ができるぜ！」");
				link.l1.go = "fight_right_now_1";
			}
		break;
		
		case "bad_habitue3":
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			if(rand(1) == 0)
			{
				dialog.text = LinkRandPhrase("かかってこい、この野郎ども！たっぷり味わわせてやるぜ！",RandSwear()+"今度こそきっちり剥いでやるぜ！","ははっ！さあ来い、水夫―陸でもお前の腕前を見せてみろ！");
				link.l1 = RandPhraseSimple(RandPhraseSimple("これを後悔することになるぜ！","てめえの汚ねえ舌を引きちぎってやるぜ！"),RandPhraseSimple("てめえを豚みたいに腹からケツ、そしてそのクソみてえな口まで切り裂いてやるぜ！","黙らせてやるって誓うぜ！"));
				link.l1.go = "fight_right_now";
			}
			else
			{
				dialog.text = "行くぞ、野郎ども！こいつらを俺たちの町から叩き出すぞ！";
				link.l1 = RandPhraseSimple(RandSwear()+"祈れ、この野郎ども！","おっと、一人じゃねえんだな！まあ、地獄で仲間ができるぜ！");
				link.l1.go = "fight_right_now_1";
			}
		break;
		
		//--> Sinistra Длинные тени старых грехов
		case "DTSG_NightIskat":
			dialog.text = "も、もちろん、みんなお互いを知ってるさ！どうしてそんなこと聞くんだ？";
            link.l1 = "金貸しに会いに行こうと思ったら、彼が古い家を売ったと聞いたんだ。今はどこに住んでいるか知ってるか？";
            link.l1.go = "DTSG_NightIskat_2";
		break;
		
		case "DTSG_NightIskat_2":
			dialog.text = "こんな時間にあいつが必要なのはなぜだ、ひっく？朝になったら銀行に行けばいいじゃねえか！";
            link.l1 = "俺は今すぐ金が必要なんだ。たまには金持ちどもに働かせてやろうじゃねえか！あいつらはいつも、 俺たちのことをタカリ屋だの、文句ばかりで借りたものも返さねえって言いやがるんだ。";
            link.l1.go = "DTSG_NightIskat_3";
		break;
		
		case "DTSG_NightIskat_3":
			dialog.text = "ははは、ひっく、そうだ、働かせてやれ！俺たちの自慢のフリートウッド船長がどこに住んでたか知ってるか？";
            link.l1 = "もちろん、リチャードを知らない者なんていなかったさ。今はあそこに銀行家が住んでるのか？";
            link.l1.go = "DTSG_NightIskat_4";
		break;
		
		case "DTSG_NightIskat_4":
			dialog.text = "あんたの言う通りだ。そこに着いたら、友よ――あいつに、調子に乗りすぎだって伝えてくれ。";
            link.l1 = "へっへっ、ちゃんとやっておくぜ。じゃあな。";
            link.l1.go = "DTSG_NightIskat_5";
		break;
		
		case "DTSG_NightIskat_5":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.DTSG_NightIskat");
			Diag.CurrentNode = Diag.TempNode;
			AddDialogExitQuest("exit_sit");
			
			chrDisableReloadToLocation = true;
			sld = CharacterFromID("Knippel");
			ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto4");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Knippel_SluhSmertFleetWood";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		//<-- Длинные тени старых грехов
		
		//--> Путеводная звезда
		case "PZ_BasTerAlkash_1":
			dialog.text = "ハハハ、俺が中国人を見たかって？俺たちはみんな見たことあるぜ！";
			link.l1 = "何がおかしいんだ？旅回りのサーカスの話じゃねえぞ、もしそう思ってるならな。俺が言ってるのは戦士、 海軍士官のことだ。";
			link.l1.go = "PZ_BasTerAlkash_2";
		break;
		
		case "PZ_BasTerAlkash_2":
			dialog.text = "ああ、言いたいことは分かるぜ！ああ、確かに見たんだ。酔いが覚めても、あいつの姿が頭から離れなかった……忘れられねえよ！";
			link.l1 = "それは面白いな。続けてくれ。もう一杯飲もうぜ――どうせ今も全部忘れたくて飲んでるんだろう。忘れる前に、何を見たのか話してくれよ。";
			link.l1.go = "PZ_BasTerAlkash_3";
		break;
		
		case "PZ_BasTerAlkash_3":
			dialog.text = "旅回りのサーカスだと？冗談じゃねえ！あいつは飛び跳ねて、回転して、そのサーベルを振り回してた――あんなに武器の扱いが巧みで恐ろしい奴は見たことがねえ。";
			link.l1 = "あいつらしいな。誰と戦ってたんだ？覚えてるか？";
			link.l1.go = "PZ_BasTerAlkash_4";
		break;
		
		case "PZ_BasTerAlkash_4":
			dialog.text = "衛兵たちだぜ、相棒！あいつらにも目を細めて睨んでやがる！もっとも、あいつはいつもあんな顔してる気がするけどな。 お前はどう思う？";
			link.l1 = "知らねえよ、相棒。続けろ。あいつがスパイだと思われたのか？なんで衛兵たちはあいつを襲ったんだ？";
			link.l1.go = "PZ_BasTerAlkash_5";
		break;
		
		case "PZ_BasTerAlkash_5":
			dialog.text = "誰にも分からねえさ。奴が町で何をしていたのか、みんな首をひねってたんだよ…";
			link.l1 = "それで、奴は捕まったのか？それとも……";
			link.l1.go = "PZ_BasTerAlkash_6";
		break;
		
		case "PZ_BasTerAlkash_6":
			dialog.text = "はっ、そんなの無理だぜ！奴は捕まらなかった。街の衛兵どもを斬り捨てて、ジャングルに逃げ込んだんだ。 何組も追っ手を送ったが、誰一人戻っちゃこねえ。想像できるか？あの洞窟を本物の要塞にしちまったんだよ！";
			link.l1 = "そりゃ大変だったな。少し休んで、忘れるようにしな。俺はもう行くぜ――頭がくらくらしてきたからな。";
			link.l1.go = "PZ_BasTerAlkash_7";
		break;
		
		case "PZ_BasTerAlkash_7":
			DialogExit();
			bDisableLandEncounters = true;
			DeleteAttribute(pchar, "questTemp.PZ_BasTerTavern");
			DeleteAttribute(pchar, "questTemp.PZ_BasTerAlkash");
			pchar.questTemp.PZ_BasTerAlkash2 = true;
			DeleteQuestCondition("PZ_BasTer_Opozdal");
			pchar.questTemp.PZ_BasTerTurma = true;
			AddLandQuestMarkToPhantom("baster_prison", "basterJailOff");
			DelMapQuestMarkIsland("Guadeloupe");
			AddQuestRecord("PZ", "3");
			Diag.CurrentNode = Diag.TempNode;
			AddDialogExitQuest("exit_sit");
			
			PChar.quest.PZ_BasTerPeshera.win_condition.l1 = "location";
			PChar.quest.PZ_BasTerPeshera.win_condition.l1.location = "Guadeloupe_CaveEntrance";
			PChar.quest.PZ_BasTerPeshera.win_condition = "PZ_BasTerPeshera";
			
			LAi_LocationDisableOfficersGen("Guadeloupe_jungle_02", false);
			LAi_LocationDisableOfficersGen("Guadeloupe_CaveEntrance", false);
			//LAi_LocationDisableOfficersGen("Guadeloupe_Cave", false);
		break;
		
		case "Sotta1":
			dialog.text = "俺はあいつを自分の目で見ちゃいねえ――最近は総督の執務室のあたりをうろついてるらしいぜ！でも、あいつの船員どもはここで盛大に宴会をやってたよ。";
			link.l1 = "そうなのか？";
			link.l1.go = "Sotta2";
		break;
		
		case "Sotta2":
			dialog.text = "みんな彼のことを商人だと言ってる。でもな、あいつの船員は酒場のゴロツキなんかじゃなかったぜ！まるで……まるで……なんて言うんだ……？";
			link.l1 = "わかったぜ。付き合ってくれてありがとな、相棒。元気でな。";
			link.l1.go = "exit_sit";
			
			npchar.questTemp.PZ_Sotta = true;
			pchar.questTemp.PZ_BelizAskCitizens = sti(pchar.questTemp.PZ_BelizAskCitizens) + 1;
			AddDialogExitQuest("PZ_LongwayBelizDialog");
		break;
		
		case "Lutter1":
			dialog.text = "俺は祝ってるんだぜ！それに、誰が俺が一人だって言ったんだ？お前がいるじゃねえか、相棒！それにマットのことだが、 遅かれ早かれこうなる運命だったのさ。";
			link.l1 = "なぜそう言うんだ？あいつは何年も運に恵まれた、ものすごく幸運な海賊だったって聞いてるぜ！";
			link.l1.go = "Lutter2";
		break;
		
		case "Lutter2":
			dialog.text = "へっ、運だけじゃなかったんだな！あいつは一匹狼の海賊で、兄弟団の一員じゃなかったんだぜ！ そういう奴は長くはもたねえ……まあ、昔はルヴァスールの庇護下にいたって噂も聞いたがな。";
			link.l1 = "そうだな、独り者は長くはもたねえ。まあ、祝えよ。俺は行くぜ、相棒。";
			link.l1.go = "exit_sit";
			
			npchar.questTemp.PZ_Lutter = true;
			pchar.questTemp.PZ_BelizAskCitizens = sti(pchar.questTemp.PZ_BelizAskCitizens) + 1;
			AddDialogExitQuest("PZ_LongwayBelizDialog");
		break;
		
		case "Sepp1":
			dialog.text = "ひゃっ、い、いいえ、私は彼を見たことありません。誰なんですか？";
			link.l1 = "奴は諸島で最速クラスの船、ブリッグ『バンテン』の船長だぜ。聞いたことあるか？";
			link.l1.go = "Sepp2";
		break;
		
		case "Sepp2":
			pchar.questTemp.PZ.TortugaHabitueBlock = true;
			
			dialog.text = "え、いや、俺は船には興味ねえんだ、相棒、ひゃっ！もう一杯どうだ？";
			link.l1 = "俺には関係ねえ。どうせここじゃ欲しいものは手に入らなかったしな。";
			link.l1.go = "exit_sit";
		break;
		//<-- Путеводная звезда
		
	}
}

bool CheckFreeSitFront(ref _npchar)
{
 	ref rCharacter; //ищем
	int n;

	if (!CheckAttribute(_npchar, "Default.ToLocator")) return false;
	
	for (n=0; n<MAX_CHARACTERS; n++)
	{
		makeref(rCharacter, Characters[n]);
		if (CheckAttribute(rCharacter, "location") && rCharacter.location == _npchar.location)
		{
            if (rCharacter.location.locator == _npchar.Default.ToLocator)
                return  false;
		}
    }
    return  true;
}
