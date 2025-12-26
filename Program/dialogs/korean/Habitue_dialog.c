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
            dialog.text = "주정뱅이 유형 선택(베타)";
			link.l1 = "Drunkard";
			link.l1.go = "Beta_test_alc";
            link.l2 = "카드 도박꾼";
			link.l2.go = "Beta_test_card";
			link.l3 = "주사위 도박꾼";
			link.l3.go = "Beta_test_dice";
		break;
		
		case "Beta_test_alc":
            dialog.text = "술주정뱅이 선택됨";
			link.l1 = "Continue";
			link.l1.go = "First time";
			npchar.quest.last_theme = 0;
		    npchar.quest.last_theme_game = 0;
		break;
		
		case "Beta_test_card":
            dialog.text = "카드 도박꾼 (즉시 불쾌해할 확률 30%)";
			link.l1 = "Continue";
			link.l1.go = "First time";
			npchar.quest.last_theme = 1;
		    npchar.quest.last_theme_game = 0;
		break;
		
		case "Beta_test_dice":
            dialog.text = "주사위 도박꾼 (30% 확률로 즉시 불쾌해함)";
			link.l1 = "Continue";
			link.l1.go = "First time";
			npchar.quest.last_theme = 1;
		    npchar.quest.last_theme_game = 1;
		break;
		
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = LinkRandPhrase("나 술에 취했을지는 몰라도 바보는 아니야. 지금 너랑 술 마시면 내일 당장 군인들이 날 잡으러 올 거라고. 절대 안 돼!","나는 내 고향의 적이 아니야. 너랑은 술 못 마시겠다!",""+GetSexPhrase("동료","아가씨")+", 아직 기회가 있을 때 이곳을 떠나는 게 좋을 거야...");
				link.l1 = RandPhraseSimple("글쎄, 원하시는 대로 하시지...","헤, 있잖아, 난 그렇게까지 취할 필요 없어. 지금은 그럴 때가 아니거든."); 
				link.l1.go = "exit";
				break;
			}
			if(CheckAttribute(pchar,"questTemp.HabitueSpeakDisable") && rand(1) == 0) // если дуэлянт то каждый второй посылает нафик
			{
				dialog.text = "하, 아가씨"+GetSexPhrase("터","s")+", 분명히 자네 소문은 들었지, 헤헤. 선술집 사람들은 자네가 말썽꾼이자 결투광이라고 하더군. 우리 동네 사람들은 쉽게 겁먹지 않지만, 럼 한 잔 때문에 죽고 싶은 사람은 없어. 자네 옆에 앉아 있는 것만으로도 불안하니, 난 그냥 넘어가겠네.";
				link.l1 = LinkRandPhrase("잘 됐군, 그럼!","기분 좋을 때 꺼져라...","가, 가! 꺼져, 물고기 밥이나 돼라!");
				link.l1.go = "exit";
				link.l2 = "잠깐, 물어보고 싶은 게 있었는데...";
				link.l2.go = "talk_habitue_duel";
				break;
			}
			
            ok = CheckFreeSitFront(npchar);
            
            dialog.text = "내 빛 가리지 마, 머그잔 안의 파리도 안 보이잖아!";
            link.l1 = "나는 서 있지 않아...";
		    link.l1.go = "exit";
		    if (!chrDisableReloadToLocation)
		    {
	            switch (npchar.quest.last_theme)
				{
					case "0": //пьяный.
						dialog.text = "히익! 오, "+GetSexPhrase("이봐, 너 딱 봐도 바다에서 잔뼈가 굵은 놈 같구나","아가씨, 확실히 노련한 뱃사람처럼 보이네")+"! 혹시 나에게 럼 한 잔 사줄 수 있겠어?";
						link.l1 = "나는 늙은 뱃사람일지 몰라도, 그렇다고 해서 잡놈들 술까지 사줄 생각은 없어...";
						link.l1.go = "exit";

						if (makeint(pchar.money) >= 100 && ok) // только старые острова окучены на сесть
						{
							link.l2 = "기꺼이 당신 일행에 합류하겠소.";
							link.l2.go = "talk_with_alchogol";
						}
						else
						{
	                        link.l2 = "그건 왜지?";
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
										Dialog.text = RandPhraseSimple("카드 게임 한 판 어때? 아주 흥미로운 게임이지!","카드 게임 한 판 하자는 게 어때? 어떻게 생각해?");
										link.l1 = "왜 안 되겠어? 그래, 한 판 하자.";
										link.l1.go = "Cards_begin";
										link.l2 = "그럼 네놈들 게임의 규칙은 뭐지?";
										link.l2.go = "Cards_Rule";
										link.l3 = "지금은 아니야.";
										link.l3.go = "exit";
									}
									else
					    			{
										Dialog.text = "아니, 이제 너랑은 카드 안 칠 거야.";
						    			link.l1 = "말씀대로 하겠습니다.";
						    			link.l1.go = "exit";
									}
			                        // Игра в карты boal 20/05/05 <--
		                        break;

								case 1:
								// кости
		    						// Игра в кости boal 13/07/05 -->
	                                if (CheckNPCQuestDate(npchar, "Dice_date_begin"))
									{
										Dialog.text = RandPhraseSimple("주사위 게임 한 판 어때? 아주 재미있는 게임이지!","주사위나 굴려보자고. 어때?");
										link.l1 = "왜 안 되겠어? 그래, 한 판 하자.";
										link.l1.go = "Dice_begin";
										link.l2 = "그럼 네놈들 게임의 규칙은 뭐지?";
										link.l2.go = "Dice_Rule";
										link.l3 = "지금은 안 돼.";
										link.l3.go = "exit";
									}
									else
					    			{
										Dialog.text = "아니, 이제 너랑 주사위 놀이 안 해.";
					    				link.l1 = "말씀대로 하겠습니다.";
					    				link.l1.go = "exit";
									}
			                        // Игра в кости boal 13/07/05 <--
			                        //navy --> Дуэли
									if (CheckAttribute(NPchar, "Quest.DiceCheats") && sti(NPchar.Quest.DiceCheats) >= 1) 
									{
					    				link.l9 = RandSwear()+" 너 속였잖아!!!";
					    				link.l9.go = "outraged";
									}
									//navy <--
			    				break;
	    					} 
						}
	        			else
	        			{
	                        dialog.text = RandPhraseSimple("내 자리에서 꺼져! 당장!"," 오? 뭐야? 누구냐? 힉... 꺼져!");
	                        link.l1 = RandPhraseSimple("술은 네 죄 많은 영혼을 파멸로 이끈다! 정신 차려라!","나한테 무례하게 굴지 마.");
	        			    link.l1.go = "exit";
	        			    link.l2 = RandPhraseSimple("입 조심해라, 이 개새끼야! 아니면 내가 예의를 가르쳐 줄 테니.","지금 네 머리를 한 대 치면 정신이 좀 들겠지.");
	        	            link.l2.go = "tavern_keeper";
	        			}
					break;
				}
			}
			Diag.TempNode = "First time";
	    break;
	    
		case "talk_habitue_duel":
			dialog.text = "나는 아무 말도 안 해, 아가씨"+GetSexPhrase("테르","s")+"! 그리고 아무도 너한테 더 이상 말을 걸 것 같지 않아, 그런 건 항상 문제를 일으키거든. 하지만 말이야, 사람들 기억력은 짧은 편이라 한두 달쯤 지나면 네 모험도 잊어버릴지 몰라, 물론 네가 다시 떠들지만 않으면 말이지, 헤헤! 잘 가라, 나리\n"+GetSexPhrase("ter","s")+". ";
			link.l1 = "좋아...";
			link.l1.go = "exit";
		break;
		
	    // карты -->
	    case "Cards_Rule":
   			dialog.text = CARDS_RULE;
			link.l1 = "자, 그럼 시작하자...";
			link.l1.go = "Cards_begin";
			link.l3 = "아니, 나를 위한 게 아니야...";
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

			Dialog.text = "그럼 먼저 내기부터 정하자 (내기를 입력하라).";
			link.l1 = "100";
			link.l1.edit = 1;
			link.l1.go = "Cards_Node_2";
			link.l3 = "가야겠군.";
			link.l3.go = "exit_sit";
		break;
		
		case "Cards_Node_2":
			iLa_Puesta = GetStrSmallRegister(dialogEditStrings[1]);
            if (!CheckCardsGameSmallRate())
		    {
                dialog.text = "너는 악명 높은 사기꾼이야. 너랑은 도박 안 해.";
                link.l1 = "다 거짓말이야! 뭐, 어쩌라고.";
			    link.l1.go = "exit_sit";
			    break;
		    }
		    
			if (sti(PCHar.Money) < sti(iLa_Puesta)*3)
		    {
                dialog.text = "보아하니 돈이 하나도 없군, "+GetSexPhrase("친구","자기야")+". 부자가 되면 다시 오시오.";
                link.l1 = "좋아.";
			    link.l1.go = "exit_sit";
			    break;
		    }
		
			if (sti(NPChar.Money) < sti(iLa_Puesta)*3)
		    {
                dialog.text = "나는 이미 가진 모든 것을 잃었어. 오늘은 운이 없는 날이군.";
                link.l1 = "좋아.";
			    link.l1.go = "exit_sit";
			    break;
		    }
		else
		{
			if(sti(iLa_Puesta) < 50)
			{
				dialog.text = "나를 비웃는 거야, 뭐야?! 놀리는 거냐고 "+iLa_Puesta+" 페소라고?! 적당한 판돈으로 하자, 아니면 난 빠질 거야!";
				link.l1 = "그래, 네 말이 맞아. 판을 좀 더 키워야겠어.";
				link.l1.go = "Cards_begin_2";
				link.l2 = "마음이 바뀌었어, 안 할래.";
				link.l2.go = "exit_sit";
				break;
			}
			
			if(sti(iLa_Puesta) > 1000)
			{
				dialog.text = "그렇게 큰 돈을 걸고 하자고? 아니, 난 패스할게. 내기가 바뀌지 않는 한.";
				link.l1 = "그래, 네 말이 맞아. 우리 판돈을 좀 줄여야겠어.";
				link.l1.go = "Cards_begin_2";
				link.l2 = "사실, 나는 아예 참가하지 않기로 했어.";
				link.l2.go = "exit_sit";
				break;
			}
			dialog.text = "좋아, 내기를 하자 "+iLa_Puesta+" 동전이다.";
			link.l1 = "카드를 돌려라!";
			link.l1.go = "Cards_begin_go";
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
			pchar.GenQuest.Cards.iRate     = sti(iLa_Puesta);
            pchar.GenQuest.Cards.SitType   = true;
		}
		break;
		
		case "Cards_begin_2":
			dialog.text = "그래서, 내기는 뭐지? (내기를 입력하시오)";
			link.l1 = "50";
			link.l1.edit = 1;
			link.l1.go = "Cards_Node_2";
			link.l2 = "나는 결국 안 하기로 할 것 같아...";
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
			link.l1 = "그럼, 시작하자...";
			link.l1.go = "Dice_begin";
			link.l3 = "아니, 나한테 필요한 건 아니야...";
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
			Dialog.text = "내기를 정하자 (내기 금액을 입력하시오).";
			link.l1 = "50";
			link.l1.edit = 1;
			link.l1.go = "Dice_Node_2";
			link.l3 = "가야겠군.";
			link.l3.go = "exit_sit";
		break;

		case "Dice_Node_2":
			iLa_Puesta = GetStrSmallRegister(dialogEditStrings[1]);
            if (!CheckDiceGameSmallRate())
		    {
				dialog.text = "너는 악명 높은 사기꾼이야. 너랑 주사위는 안 굴릴 거다.";
                link.l1 = "다 거짓말이야! 뭐, 어쨌든.";
			    link.l1.go = "exit_sit";
			    break;
		    }

			if (sti(pchar.Money) < sti(iLa_Puesta)*6)
		    {
                dialog.text = "보니까 돈이 하나도 없군, "+GetSexPhrase("친구","여보")+". 부자가 되면 다시 오시오.";
                link.l1 = "좋아.";
			    link.l1.go = "exit_sit";
			    break;
		    }
			
			if (sti(npchar.Money) < sti(iLa_Puesta)*6)
		    {
                dialog.text = "나는 이미 가진 모든 것을 잃었어. 오늘은 운이 정말 없는 날이군.";
                link.l1 = "좋아.";
			    link.l1.go = "exit_sit";
			    break;
		    }
		else
		{
			if(sti(iLa_Puesta) < 50)
			{
				dialog.text = "나를 비웃는 거야, 뭐야?! \n장난치는 거냐 "+iLa_Puesta+" 페소를 하루에?! 적당한 판돈으로 하자, 아니면 난 빠질 거야!";
				link.l1 = "그래, 네 말이 맞아. 판을 좀 더 키워야겠어.";
				link.l1.go = "Dice_begin_2";
				link.l2 = "생각이 바뀌었어, 나 안 할래.";
				link.l2.go = "exit_sit";
				break;
			}
			
			if(sti(iLa_Puesta) > 1000)
			{
				dialog.text = "이렇게 큰 돈을 걸고 주사위를 친다고? 아니, 난 패스하겠어, 내기를 바꾸지 않는 한.";
				link.l1 = "그래, 네 말이 맞아. 판돈을 좀 줄여야겠어.";
				link.l1.go = "Dice_begin_2";
				link.l2 = "사실, 나는 아예 놀지 않기로 했어.";
				link.l2.go = "exit_sit";
				break;
			}
			dialog.text = "좋아, 내기를 하자 "+iLa_Puesta+" 주사위당 동전.";
			link.l1 = "가자!";
			link.l1.go = "Dice_begin_go";
			pchar.GenQuest.Dice.npcharIdx = npchar.index;
			pchar.GenQuest.Dice.iRate     = sti(iLa_Puesta);
            pchar.GenQuest.Dice.SitType   = true;
		}
		break;
		
		case "Dice_begin_2":
			dialog.text = "그래서 내기는 뭐지? (내기를 입력하시오)";
			link.l1 = "50";
			link.l1.edit = 1;
			link.l1.go = "Dice_Node_2";
			link.l2 = "나는 결국 안 하기로 할 것 같아...";
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
			dialog.text = "음, 히-잇! 다 잘 지내고 있지. 히잇! 예상 못 했지. 히-익! 이 럼 진짜 끝내줘. 자메이카 블랙 럼이야. 히잇!\n여기, 한 잔 따라 마셔!";
			link.l1 = "좋아, 왜 안 되겠어.";
			link.l1.go = "talk_with_alchogol_song_2";
			link.l2 = "미안하다, 친구, 나 가봐야 해.";
			link.l2.go = "exit";
		break;
		
		case "talk_with_alchogol_song_2":
			dialog.text = "잔도 얼굴도 왔다 갔다 하지... 헉... 바닥에 쓰러질 때까지 말이야. 난 항상 술 마시고 있어... 헉! 술은 어디 있지... 그리고 무슨 노래였더라...";
			link.l1 = "술은 넘치고 아가씨들도 모두 곱지만, 모두 해적을 원해도 내 곁엔 럼주만 남았네.";
			link.l1.go = "talk_with_alchogol_song_3";
			link.l2 = "이럴 시간 없어.";
			link.l2.go = "exit";
		break;
		
		case "talk_with_alchogol_song_3":
			dialog.text = "슬플 때는 생각하려 하지 말고, 이리 와서 우리랑 한잔하자!\n모든 게 분명 괜찮아질 거야, 나는 네 친구고, 너도 내 친구니까!";
			link.l1 = "친구가 있다는 건 참 좋은 일이야, 네가 떠나도 친구는 기다려주지. 친구와 함께라면 미움도 없지. 하지만 럼주가 떨어지면 논쟁만 남는 법. 그러니 마시자, 친구야, 내가 가서 늦기 전에... ";
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
			dialog.text = LinkRandPhrase("히익! 이제야 좀 낫네! 훨씬 낫군! 그래서? 나한테 럼 좀 사줄 거야, 말 거야?","앉아라, "+GetAddress_Form(npchar)+", 자, 옛날 자메이카 럼 한 잔 들이켜자고. 건강에 나쁠 리 없지. 그리고 무슨 일이 벌어지고 있는지 궁금하다면, 이 선술집만한 곳이 없어, 내가 장담하지. 돈 좀 쓰고, 괜찮은 럼 두어 잔만 마시면 알아야 할 건 다 알게 될 거야. 아니, 그 이상도 알게 되지, 이 늙은 단골을 믿으라고...","헤헤, 앉으시지. "+GetSexPhrase("내 좋은 친구","아가씨")+", 한잔하자... 좋은 사람들과 술 한잔 즐기는 게 어때? 인내심을 갖고 천천히, 조금씩 마시면 흥미로운 이야기를 많이 들을 수 있어... 자기 모험을 자랑하는 선장들도 있고, 술에 취해 정신을 놓으면 중요한 말을 내뱉는 사람들도 많지... 거기엔 많은 사람들이 시간을 보내고, 모두가 할 이야기가 있으니 믿어봐, "+GetSexPhrase("내 좋은 친구","Miss")+".");
			link.l1 = "왜 안 되겠어! 바텐더! 우리 둘에게 럼 한 잔씩 줘!";
			link.l1.go = "sit_2";
		break;

		// Церковный генератор. Квест №2 -->
		case "Alcogol_GenQuest_Church_2_1":
			dialog.text = "물론이지! 들었나... 산적들이 교회까지 약탈한대!";
				link.l1 = "글쎄, 그거야 해적들이지, 또 누가 있겠어...";
				link.l1.go = "Alcogol_GenQuest_Church_2_2";
				DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.AskPeople");
				DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.AskBarmen");
				DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.AskAlcash");
			break;
			
		case "Alcogol_GenQuest_Church_2_2":
			dialog.text = "무슨 해적? 그냥 평범한 뭍사람들이지, 분명히 이 동네 놈들일 거야... 외지인들이었으면 교회 금고가 언제 가득 찼는지 알 리가 없지. 그리고 그런 일에 휘말릴 일도 없었을 거고.";
				link.l1 = "대담한 녀석들이지, 그건 확실해. 허술한 문빗장을 그렇게 용감하게 열다니...";
				link.l1.go = "Alcogol_GenQuest_Church_2_3";
			break;
			
		case "Alcogol_GenQuest_Church_2_3":
			dialog.text = "아하. 게다가 영리하기까지 하군. 누가 그렇게 자신을 드러내겠어?";
				link.l1 = "맞아요. 온 교구가 교회에 기부하려고 돈을 모았는데, 이제 저 영악한 녀석들이 그 돈으로 한몫 잡았단 말이오? 분명 곧 잡힐 거요. 이제 모두가 그놈들을 찾을 테니.";
				link.l1.go = "Alcogol_GenQuest_Church_2_4";
			break;
			
		case "Alcogol_GenQuest_Church_2_4":
			dialog.text = "글쎄다. 누가 그놈들을 찾겠어? 놈들은 방금 교회를 털고 마을을 떠나 바람처럼 사라졌지. 정글은 넓어, 아주 넓지. 거기서 놈들을 찾으려면 세월아 네월아 할 거야. 몇 달만 지나면 사람들은 다 잊어버릴 거다, 내 말 명심해!";
				link.l1 = "나는 그렇게 생각하지 않아. 그런 일은 용서할 수 없어.";
				link.l1.go = "Alcogol_GenQuest_Church_2_5";
			break;
			
		case "Alcogol_GenQuest_Church_2_5":
			dialog.text = "남자의 기억은 새는 작은 배와 같지. 사람들은 잊고 용서하지. 하지만 신은?! 신은 모든 걸 보고 계시지. 두려워해야 할 분은 바로 그분이야. 내가 말하건대, 십 년 전 내 옛 친구에게 끔찍한 일이 일어났지. 그 친구도 창조주를 경외하지 않았고, 거의 바다 악마에게 바로 끌려갈 뻔했어...";
				link.l1 = "미안하다, 친구야, 나 가봐야 해. 네 동료 얘기는 다음에 하자. 또 보자.";
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
				dialog.text = "오, 프랑수아! 물론이지, 그 녀석 기억나... 아니, 난 몰라. 하지만 말이야, 우리 여급한테 물어보는 게 좋을 거야. 그가 여기 사는 동안, 매일 밤 그녀랑 같이 있었거든. 걔는 진짜 못된 년이야, 그건 확실하지. 아마 그 녀석이 뭔가 떠들었을지도 몰라.";
				link.l1 = "조언 고마워, 친구. 내가 가서 그녀와 얘기할게.";
				link.l1.go = "exit_sit";
				pchar.questTemp.Slavetrader = "FindRatJamaica_W";
			break;
			
			case "EscapeSlave_Villemstad_H1":
				dialog.text = "그래, 때때로 망망대해에선 정말 이상한 일들이 벌어지기도 하지. 지난 항해 때 나는 정말이지...\n";
				link.l1 = "자, 말해 봐. 너무 과장하지만 말고. 그동안 내가 럼주 좀 더 가져올게.";
				link.l1.go = "EscapeSlave_Villemstad_H2";
			break;
			
			case "EscapeSlave_Villemstad_H2":
				dialog.text = "신께 맹세하오, 나리"+GetSexPhrase("나리","아가씨")+" - 내 두 눈으로 똑똑히 봤어... 배가 항해하고 있었는데, 선원들 대신에 거대한 유인원들이 있었어... 아니면 마카크... 원숭이들 말이야, 알겠지.";
				link.l1 = "뭐라고?! 이봐, 친구, 너도 당직 중에 술 마시는 거야?";
				link.l1.go = "EscapeSlave_Villemstad_H3";
			break;
			
			case "EscapeSlave_Villemstad_H3":
				dialog.text = "내가 거짓말하면 눈이 멀어도 좋아! 원숭이 새우 얘기 들어본 적 없어? 젠장, 새우라니 하하! ... 원숭이 배 말이야.";
				link.l1 = "무슨 원숭이 배?";
				link.l1.go = "EscapeSlave_Villemstad_H4";
			break;
			
			case "EscapeSlave_Villemstad_H4":
				dialog.text = "오-호, 내가 직접 두 눈으로 봤다니까. 폭풍이 몰아쳤어. 아무것도 안 보였는데, 갑자기 배가 어디선가 나타났지. 돛은 다 찢어지고, 앞돛도 부러졌고, 주돛도 마찬가지였어, 맹세코 전부 박살이 났다! 그런데도 그 배는 바람을 거슬러 돌진하고 있었어!\n그리고 갑판에는 원숭이들이 있었지... 엄청 많았어, 마치 물개 떼처럼! 진짜 고릴라가 키를 잡고 서 있었어! 키가 아홉 자는 됐고, 빨간 셔츠에, 가슴에는 십자가 대신 상어 이빨이 박혀 있었지... 눈은 시뻘겋게 빛나고, 송곳니가 번쩍였어, 우리를 보더니 뭔가를 소리쳤다니까...";
				link.l1 = "이봐, 뻔히 거짓말하고 있잖아. 술 취하면 별 게 다 보이지. 다음엔 그 여자가 플라잉 더치맨이었다고 하겠군.";
				link.l1.go = "EscapeSlave_Villemstad_H5";
			break;
			
			case "EscapeSlave_Villemstad_H5":
				dialog.text = "아니, 그 배는 네덜란드 배가 아니었어. 진짜야! 바크였고, 선미에 글씨가 적혀 있었지 - "+pchar.questTemp.Slavetrader.ShipName+".";
				link.l1 = "젠장! 네가 말한 '원숭이들'이 뭔지 이제 알겠군. 정말이지, 럼주만 있으면 입이 잘 풀리지... 그냥 귀만 기울이면 돼...";
				link.l1.go = "EscapeSlave_Villemstad_H6";
			break;
			
			case "EscapeSlave_Villemstad_H6":
				dialog.text = "봐라, 내가 뭐랬어! 그런데도 안 믿더니!.. 좋아, 마지막으로 한 잔 더 하고, 난 간다.";
				link.l1 = "알겠어, 재미있는 이야기 고마워. 이제 가봐야겠어. 행운을 빌어, 친구.";
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
			dialog.text = "아니오, 선장님. 저는 뱃사람의 삶이 체질이 아닙니다. 있잖아요, 저도 한때는 배가 있었지만... 정말 운이 지독하게 없었거든요.";
			link.l1 = "이봐, 바다에 떠 있는 이상한 배를 봤어. 이름이 '메이펑'이더군. 그런 배는 처음 봐. 저 배 주인이 누군지 알아? 혹시 팔 생각 있는 건가? 한번 구경해 보고 싶은데.";
			link.l1.go = "Lucas_Tavern_1";
		break;
		
		case "Lucas_Tavern_1":
			dialog.text = "하! 전혀 아니오, 선장님. 그 중국인은 당신이나 다른 누구에게도 자기 배를 팔 생각이 없어 보여.";
			link.l1 = "중국인이라고? 퀴라소에 중국인이 있다고? 게다가 자기 배의 선장이라니?";
			link.l1.go = "Lucas_Tavern_2";
		break;
		
		case "Lucas_Tavern_2":
			dialog.text = "보시다시피 있소. 하지만 사실 이건 그의 배가 아니오 – 무역회사의 소유지. 부국장이자 현재 대행 총독인 로덴부르흐 나리가 이 배의 주인이라고들 하오.";
			link.l1 = "그래서 마티아스 벡이 은퇴했나?";
			link.l1.go = "Lucas_Tavern_3";
		break;
		
		case "Lucas_Tavern_3":
			dialog.text = "하! 마인헤르, 뭍에 좀 더 자주 나가 보셔야겠소 – 아니면 적어도 소식은 챙기셔야지. 마티아스 벡은 해임당하고 모든 상황이 명확해질 때까지 감옥에 갇혔소.";
			link.l1 = "정말이군! 사실 바다에서 너무 많은 시간을 보내고 있지. 그런데 그게 언제 일어난 일이냐?";
			link.l1.go = "Lucas_Tavern_4";
		break;
		
		case "Lucas_Tavern_4":
			dialog.text = "사실, 바로 며칠 전에 있었소. 항구에 급송 브리건틴이 도착했지. 상태가 썩 좋지는 않았는데, 치열한 전투에 참여했던 게 분명했어. 선장은 곧장 로덴부르크 나리에게 보고하러 갔고, 몇 시간 만에 마티아스 벡이 로덴부르크 나리와 사령관에게 영국 정보국과 협력한 혐의로 체포되었소.";
			link.l1 = "끔찍한 말을 하는군. 쿠라사오의 총독이 어떻게 영국 첩자일 수 있겠어?";
			link.l1.go = "Lucas_Tavern_5";
		break;
		
		case "Lucas_Tavern_5":
			dialog.text = "솔직히, 나도 좀처럼 믿기 어렵군. 곧 회사의 이사인 피터 스타이브센트 나리가 직접 여기 온다고 들었어. 아마도 그가 직접 조사를 진행할 모양이야.";
			link.l1 = "그렇다면 네 말이 맞아. 지금은 로덴부르흐 나리를 귀찮게 하는 건 위험할 수 있지.";
			link.l1.go = "Lucas_Tavern_6";
		break;
		
		case "Lucas_Tavern_6":
			dialog.text = "좋은 생각이오, 선장! 하필이면 지금 '메이펑'이 선적 중이기도 하니까 말이오. 방금 메이펑이 본토 남쪽 해안으로 항해를 다녀왔고, 곧 다시 출항할 거요. 그런데 말인데, 거기서 이상한 일들이 벌어지고 있소. 네덜란드 선원들과 회사 경비병들은 임무에서 해제됐고, 다른 선원들이 새로 모이고 있소. 내가 평생 마신 럼주 잔을 걸고 맹세하는데, 그 새로 온 지원자들은 완전히 딴판이오. 전부 해적, 도적, 살인자들이라니까!\n";
			link.l1 = "정말 기적이구나! 뭐, 안타깝군! 그렇게 멋진 배였는데... 운명이 달랐던 모양이지... 흥미로운 이야기와 소식 고마워! 너랑 얘기해서 즐거웠어!";
			link.l1.go = "Lucas_Tavern_7";
		break;
		
		case "Lucas_Tavern_7":
			dialog.text = "그래, 같이 있어주고 럼도 줘서 고마워, 선장! 또 들르라고!";
			link.l1 = "당연히 할게!";
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
				dialog.text = "하! "+pchar.GenQuest.FindFugitive.Name+"? 나도 알아, 알아... 네 동료는 정말 말이 없는 사람이야. 말하자면 외로운 늑대지. 하루 종일 섬 해안을 따라 자기 작은 배를 몰고 다니다가 해질 때쯤 돌아오더군. 사람들은 그가 어부라고 생각하지만, 사실 진짜 진주 채취꾼이야... 허! 이건 내가 확실히 아는 사실이야!";
				link.l1 = "헤! 그래서... 그를 어디서 찾을 수 있는지 말해 줄 수 있나?";
				link.l1.go = "FindFugitiveHb_1";
			}
			else
			{
				dialog.text = ""+pchar.GenQuest.FindFugitive.Name+"? 아니, 맹세코 그 사람에 대해 들어본 적 없어... 하지만 너, 히익! 우리 바텐더에게 물어봐. 그 사람은 분명히 알고 있을 거야!";
				link.l1 = "흠... 알겠어, 좀 더 알아볼게. 그래, 친구, 같이 있어줘서 고마워. 또 보자!";
				link.l1.go = "exit_sit";
			}
		break;
		
		case "FindFugitiveHb_1":
			dialog.text = "물론이지! 그는 매일 아침 해안에서, "+XI_ConvertString(pchar.GenQuest.FindFugitive.Shore+"Gen")+". 최대한 일찍 오시오, 그렇지 않으면 그가 출항해버려서 다음 날 아침까지 기다려야 할 것이오.";
			link.l1 = "고마워! 정말 큰 도움이 됐어, 친구! 또 보자!";
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
			dialog.text = "우리 조선소에서 어슬렁거리며 조선공들에게 이것저것 물어보고 있었어. 그게 결국 그놈한테 화를 불렀지. 어떤 사람들이 마을에 수상한 자가 돌아다닌다고 사령관에게 알렸고, 그래서 그를 붙잡았어. 그리고 나서야 그가 상인이 아니라는 게 밝혀졌지.";
			link.l1 = "그가 당신의 조선공에게서 어떤 비밀 프로젝트를 훔칠 계획이었던 것 같군요?";
			link.l1.go = "trial_spy_1";
		break;
		
		case "trial_spy_1":
			dialog.text = "누가 알겠어? 하지만 난 그가 처음부터 '알라칸타라' 갤리온에 관심이 있었다는 걸 확신해! 힉! 맹세할 수 있다니까! 이 배는 총독 나리께서 직접 준비 중이니, 분명 그 악당이 뭔가 캐내려고 했을 거야.";
			link.l1 = "하! 그럴 법도 하지. 분명히 총독이 그녀에게 귀한 물건을 싣게 할 거야...";
			link.l1.go = "trial_spy_2";
		break;
		
		case "trial_spy_2":
			dialog.text = "그건 말할 필요도 없지! 정말 주목할 만한 일이 틀림없어, 내가 장담해! 아, 그리고 사람들이 그러는데, 어부들이 이 근해에서 외국 군함을 봤다고 하더군 ... 아마 프리깃함일 거야. 혹시 그 첩자가 거기서 온 건 아닐까?";
			link.l1 = "그래, 그럴 수도 있지... 좋아, 친구, 같이 있어줘서 고맙다. 이제 난 가봐야겠어!";
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
				dialog.text = "그대의 건강과 너그러움에 건배하오!";
				link.l1 = "이봐, 이 근처에서 중국인 남자 본 적 있어?";
				link.l1.go = "PZ_BasTerAlkash_1";
				break;
			}
			// <== Квест "Путеводная звезда" - Sinistra
			
			dialog.text = LinkRandPhrase("너는 "+GetSexPhrase("진정한 친구","대단한 아가씨")+"! 만나서 반갑다! 건배!","힉! 이거 끝내주는 럼이네! 힉... 건배!","당신의 건강과 너그러움에 건배!");
			link.l1 = "헤헤, 정말 독한 럼이군. 좋아, 난 이제 가봐야겠어. 잘 즐겨!";
			link.l1.go = "exit_sit";
			if (makeint(pchar.money) >=2)
			{
				link.l2 = "한 잔 더 해도 괜찮겠어?";
				link.l2.go = "sit_3";
			}

			link.l4 = LinkRandPhrase("바다에서 영원을 보낸 기분이야. 소식 좀 있나?","사람들이 뭐라고 하던가? 물론 내가 술을 사주지.","이봐, 친구, 요즘 선술집에서 어떤 이야기들이 인기냐?");
			link.l4.go = "rumours_habitue";
		break;

		case "sit_3":
			int iSituation;
			if(IsEquipCharacterByArtefact(pchar, "totem_01")) iSituation = makeint(rand(3));
			else iSituation = makeint(rand(5));
			switch (iSituation)
			{
				case 0:
					dialog.text = "오! 훌륭한 생각이군!";
					link.l1 = "술집 주인! 럼 좀 더 가져와!";
					link.l1.go = "sit_2";
				break;

				case 1:
					dialog.text = "너한테! 이런 젠장! 저게 누구야?";
					link.l1 = "어? 뭐지? 어디야? 헛것을 본 건가?";
					link.l1.go = "sit_2";// to_do "sit_case_5_exit";
				break;
				
                case 2:
	         		dialog.text = "그럼 마시자! 한 잔 더 할래?";
					link.l1 = "앞장서!";
					link.l1.go = "sit_2";
                break;				
				
				case 3:
					if(rand(1) == 0)
					{
						dialog.text = RandPhraseSimple("이봐, 너, "+GetAddress_Form(NPChar)+", 너 지금 다들 너를 존경한다고 생각하고 있겠지, 그렇지? 하지만 내 생각엔, 너 그냥 평범한 도적일 뿐이야!.. 그리고 살인자지! '고귀한 해적'이라니! 하! 도적은 도적일 뿐이야... 히끅... 땅에서든 바다에서든 말이지..","히끅! "+GetSexPhrase("스... 쓰레기놈","더... 더러운 놈")+"! 나를 취할 때까지 술 마시게 하고, 히끅, 그다음에 내 돈을 다 훔치려는 거지!");
						link.l1 = "이미 술을 충분히 마신 것 같군... 가서 술 좀 깨고 와... 나는 가봐야겠어...";
						link.l1.go = "exit_sit";						
						link.l2 = "네 말투가 마음에 안 들어, 이봐. 말 조심해, 알았지?";
						link.l2.go = "sit_case_2_enemy";
						link.l3 = "방금 누구를 도둑놈이라고 불렀어, 이 땅개야?! 네 배에 구멍이 나면 무슨 말을 할지 두고 보자!";
						link.l3.go = "sit_case_2_enemy2";
					link.l4 = "진정해! 잊었어? 나는 네 유일한 진짜 친구야!";
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
							dialog.text = RandPhraseSimple("왜 나를 그렇게 쳐다보는 거야? 내가 취해서 쓰러질 때까지 기다렸다가, 크- hic - 내 돈 다 훔치려고 그러지! 이런 잡놈들은 다 어디서 온 거야?! 힉... 이 선술집엔 제대로 된 사람 앉을 자리도 없네?","나를 존중하냐?.. 그래, 너 말이야! 나를 존중하냐고?! 잘해라... 나 만만한 사람 아니야... 눈 사이에 한 방이면... 넌 끝장이야...");
							link.l1 = "이봐, 너 돼지처럼 취했잖아. 집에 가서 자라... 나도 이제 가봐야겠어...";	
							link.l1.go = "exit_sit";
							link.l2 = "진정해, 친구. 누구한테 말하는지 좀 생각해.";
							link.l2.go = "sit_case_2_enemy1";
							link.l3 = "뭐라고 방금 말했어?! 내가 혼쭐을 내주마!";
							link.l3.go = "sit_case_2_enemy2";
							link.l4 = "진정해! 나를 잊었어? 나는 네 유일한 진짜 친구야!";
							link.l4.go = "sit_case_2_friend";	
						//}
					}
				break;

				case 4:
					dialog.text = "이봐! 자네 참 괜찮은 사람이군! 혹시 내 부탁 하나 들어줄 수 있겠나... 어떤 일인데?";
					link.l1 = "아니, 이제 가봐야 할 것 같아.";
					link.l1.go = "exit_sit";
					link.l2 = "그럼! 히끅! 우린 친구잖아... 안 그래? 히끅!";
					link.l2.go = "sit_case_3";
				break;

				case 5:
					if (GetSummonSkillFromName(pchar, SKILL_SNEAK) > rand(110) || CheckAttribute(pchar, "questTemp.Sharlie.Lock"))
					{
						dialog.text = "...그러고 나서 나는 그 자의 검날을, 칼날을 잡았지...";
						link.l1 = "...그리고 나서 그녀가 말하길...";
						link.l1.go = "sit_2";
					}
					else
					{
						dialog.text = "...그리고 나서 내가 그 자의 검날을 손으로 잡았지...";
						link.l1 = "...히익! ...그리고 나서 그녀가 말하길...";
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
			dialog.text = "그... 그게, 군인 중 한 명이 나를 모욕했어. 그, 그게 다야!";
			link.l1 = "군, 군인이라고? 아, 아니, 나는 사양할게.";
			link.l1.go = "exit_sit";
			link.l2 = "진정해! 나를 잊은 거야? 나는 네 유일한 진짜 친구야!";
			link.l2.go = "sit_2";
		break;

		case "sit_case_2_friend":
			dialog.snd = "Voice\HADI\HADI038";
			dialog.text = "너? 네가 무슨 친구야? 아, 아냐! 너... 너 나를 죽이려는 거지! 그, 그렇지!";
			link.l1 = "글쎄, 너 이미 충분히 마셨으니 이만 가라.";
			link.l1.go = "exit_sit";
			link.l2 = "뭐? 내가 너를 죽일 생각이 없다는 걸 증명해주지! 나... 네 손을 잘라버릴 거야!... 그거 없으면 죽일 수 없으니까!... 딸꾹!";
			link.l2.go = "sit_case_2_friend_2";
		break;

		case "sit_case_2_friend_2":
			dialog.snd = "Voice\HADI\HADI039";
			dialog.text = "아아악! 가져가라 "+GetSexPhrase("그를","그녀의")+" 내게서 떨어져!";
			link.l1 = "진정해... 히끅... 아프지 않을 거야!... 면도보다 덜 아파!";
			link.l1.go = "tavern_keeper";
		break;

		case "sit_case_2_enemy":
			dialog.snd = "Voice\HADI\HADI040";
			dialog.text = "나를 겁주려고 하지 마! 헉! 나는 그렇게 쉽게 겁먹지 않아!.. 그리고 너, 너야말로 교수대에 매달려야 해... 네놈들 모두랑 말이지 - 헉! 아무리 으스대 봐도 썩은 생선 냄새가 진동한다고! 그리고 나는 네놈들한테 말할 때 - 헉! - 내 입 조심 따위 안 할 거야! 다들 역겨워!";
			link.l1 = "아르, 내가 왜 이런 주정뱅이랑 얘기하고 있는 거지...\n차라리 바깥에 나가서 신선한 공기나 좀 마셔야겠다...";
			link.l1.go = "exit_sit1";
			link.l2 = "너 너무 대담하군, 이 친구야. 네 말 그대로 네 목구멍에 쑤셔 넣어주마!";
			link.l2.go = "sit_case_2_enemy3";
		break;

		case "sit_case_2_enemy1":		
			dialog.snd = "Voice\HADI\HADI040";
			dialog.text = "뭐, 뭐라고?! 내 손으로 직접 목을 졸라주마! 헉... 지금까지 나한테서 도망친 놈은 없어 - 헉! - 한 놈도!";
			link.l1 = "너 술 취한 돼지 아니냐? 이렇게 좋은 저녁을 망치다니... 좋아, 네 바퀴벌레나 잡아라 - 난 여기서 나간다.";
			link.l1.go = "exit_sit1";
			link.l2 = RandSwear()+"가만히 있지 않겠다는 거군. 좋아, 예의범절을 제대로 가르쳐 주지.";
			link.l2.go = "sit_case_2_enemy3";
		break;
		
		case "sit_case_2_enemy2":	
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			if(rand(1) == 0)
			{
				dialog.text = LinkRandPhrase("가까이 와, 이 망할 놈아! 네 꼴에 맞는 대가를 받게 될 거야!",RandSwear()+"네놈에게 마땅한 대가를 주겠다!","하! 좋아, 바다의 개야 - 육지에서는 얼마나 잘하는지 한번 보자!");
				link.l1 = RandPhraseSimple(RandPhraseSimple("네놈, 반드시 후회하게 될 거다!","네 더러운 혀를 귀에 맞게 잘라주마!"),RandPhraseSimple("네 놈 창자 싹 다 꺼내주마, 엉덩이에서 그 더러운 입구멍까지 쭉 갈라버릴 테니까!","내가 반드시 네 입을 다물게 해주겠다!"));
				link.l1.go = "fight_right_now";
			}
			else
			{
				dialog.text = "이봐, 얘들아! 이 쓰레기들을 우리 마을에서 쓸어내자!";
				link.l1 = RandPhraseSimple(RandSwear()+"기도나 해라, 이 개자식들아!","오, 혼자가 아니었군?! 그래, 잘됐네 - 지옥에서 동료랑 같이 가겠구나!");
				link.l1.go = "fight_right_now_1";
			}
		break;
		
		case "sit_case_2_enemy3":	
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
			if(rand(1) == 0)
			{
				dialog.text = LinkRandPhrase("가까이 와, 이 망할 놈아! 네가 받을 벌을 받게 될 거야!",RandSwear()+"네놈에게 마땅한 대가를 주겠다!","하! 좋아, 바다개야 - 뭍에서는 얼마나 잘하는지 한번 보자!");
				link.l1 = RandPhraseSimple(RandPhraseSimple("내가 맹세하는데, 넌 반드시 후회하게 될 거야!","네 더러운 혀를 귀까지 잘라버리겠다!"),RandPhraseSimple("네 놈 배를 돼지처럼 갈라버릴 거다, 엉덩이에서 그 더러운 입까지 쭉!","내가 꼭 네 입을 다물게 해주겠다!"));
				link.l1.go = "fight_right_now";
			}
			else
			{
				dialog.text = "이봐, 녀석들아! 이 쓰레기들을 우리 마을에서 쓸어내자!";
				link.l1 = RandPhraseSimple(RandSwear()+"기도나 해라, 이 개자식들아!","오, 혼자가 아니었군?! 그래, 잘됐네 – 지옥에서 같이 가겠구만!");
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
			dialog.text = "이봐, 이해가 안 돼! 내가 모퉁이를 도는 순간, 어떤 신참이 내 자리를 차지했어. 꺼져!";
			link.l1 = "항상 똑같지: 자리에 앉으면 이미 누가 앉아 있더라고... 그냥 앉아 있어, 어차피 나도 곧 일어날 참이었으니까.";
			link.l1.go = "bad_habitue1";
			link.l2 = "네 더러운 입에서 그런 말 한 마디만 더 나오면 그게 네가 마지막으로 하는 말이 될 거다, 알겠어?";
			link.l2.go = "bad_habitue2";
			link.l3 = "여기가 정말 네 자리였는지는 모르겠지만, 나한테 그런 식으로 말하게 두지 않을 거야. 말 조심해.";
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
				dialog.text = LinkRandPhrase("어서 와라, 이놈들아! 이제 실컷 당해볼 테니!",RandSwear()+"이제 제대로 벗겨주지!","하! 이리 와, 선원아 - 육지에서 네가 뭘 할 수 있는지 한번 보자!");
				link.l1 = RandPhraseSimple(RandPhraseSimple("이 일 반드시 후회하게 될 거야!","네 더러운 혀를 잘라버리겠다!"),RandPhraseSimple("네 놈을 돼지처럼 배 갈라주마, 엉덩이에서 그 더러운 입구멍까지!","내가 반드시 네 입을 다물게 해주마!"));
				link.l1.go = "fight_right_now";
			}
			else
			{
				dialog.text = "자, 얘들아! 이 쓰레기들을 우리 마을에서 쫓아내자!";
				link.l1 = RandPhraseSimple(RandSwear()+"기도나 해라, 이 개자식들아!","오, 혼자가 아니구나! 그래, 지옥에서 동료를 만나게 될 거야!");
				link.l1.go = "fight_right_now_1";
			}
		break;
		
		case "bad_habitue3":
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			if(rand(1) == 0)
			{
				dialog.text = LinkRandPhrase("어서 와라, 이 악당들아! 이제 실컷 맛 좀 볼 테니까!",RandSwear()+"이제 제대로 벗겨주마!","하! 이리 와, 뱃사람아 - 뭍에서는 네가 뭘 할 수 있는지 보자!");
				link.l1 = RandPhraseSimple(RandPhraseSimple("이 일 반드시 후회하게 될 거다!","네 놈 혓바닥을 뽑아버릴 거다!"),RandPhraseSimple("네 놈 배를 돼지처럼 갈라버릴 거다, 엉덩이에서 그 더러운 입구멍까지!","내가 반드시 네 입을 다물게 해주겠다!"));
				link.l1.go = "fight_right_now";
			}
			else
			{
				dialog.text = "자, 얘들아! 이 쓰레기들을 우리 마을에서 쫓아내자!";
				link.l1 = RandPhraseSimple(RandSwear()+"기도나 해라, 이 개자식들아!","오, 혼자가 아니군! 좋아, 지옥에서 동료를 만나게 될 거야!");
				link.l1.go = "fight_right_now_1";
			}
		break;
		
		//--> Sinistra Длинные тени старых грехов
		case "DTSG_NightIskat":
			dialog.text = "그, 그럼요, 우리 다 서로 잘 알지! 왜 물어보는 거야?";
            link.l1 = "나는 돈꾼을 찾아가려고 했는데, 그가 옛집을 팔았다는 걸 알게 됐어. 지금은 어디에 사는지 알아?";
            link.l1.go = "DTSG_NightIskat_2";
		break;
		
		case "DTSG_NightIskat_2":
			dialog.text = "이 시간에 그 사람을 왜 찾는 거야, 헉? 아침에 은행에 가면 되잖아!";
            link.l1 = "나 지금 당장 돈이 급해. 이번엔 돈 많은 놈들이나 좀 일해 보라고 해! 저런 부자 놈들은 항상 우리더러 거지 근성에, 맨날 구걸이나 하고 불평만 하다가 빚도 안 갚는다고 하잖아.";
            link.l1.go = "DTSG_NightIskat_3";
		break;
		
		case "DTSG_NightIskat_3":
			dialog.text = "하하하, 힉, 그래, 일하게 두자! 우리 영광스러운 플리트우드 선장이 어디 살았는지 알아?";
            link.l1 = "물론이지, 리처드를 모르는 사람이 어디 있겠어. 이제 그 은행가가 거기서 살고 있나?";
            link.l1.go = "DTSG_NightIskat_4";
		break;
		
		case "DTSG_NightIskat_4":
			dialog.text = "네 말이 맞아. 거기 도착하면, 친구야 - 그 자식 너무 우쭐댄다고 전해 줘.";
            link.l1 = "헤헤, 꼭 그렇게 하지. 잘 가라.";
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
			dialog.text = "하하하, 내가 중국인을 봤냐고? 우리 모두 봤지!";
			link.l1 = "뭐가 그렇게 웃기지? 내가 떠돌이 서커스 얘기하는 거 아니야, 네가 생각하는 그런 거라면. 나는 싸움꾼, 해군 장교 얘기하는 거야.";
			link.l1.go = "PZ_BasTerAlkash_2";
		break;
		
		case "PZ_BasTerAlkash_2":
			dialog.text = "아, 무슨 말인지 알겠어! 그래, 그를 봤지. 술이 깨고 나서도 계속 그 사람이 보이더라고... 잊을 수가 없어!";
			link.l1 = "흥미로운데. 계속해 봐. 한잔 더 하자고 – 지금 이 모든 걸 잊으려고 마시고 있는 거겠지. 다 잊기 전에 뭘 봤는지 말해 봐.";
			link.l1.go = "PZ_BasTerAlkash_3";
		break;
		
		case "PZ_BasTerAlkash_3":
			dialog.text = "떠돌이 서커스라니, 웃기고 있네! 그 자식, 칼을 들고 뛰고, 돌고, 휘두르며 난리도 아니었어 - 그렇게 무기 다루는 데 능숙하고 무서운 사람은 처음 봤다.";
			link.l1 = "그 사람답군. 누구와 싸우고 있었지? 기억나나?";
			link.l1.go = "PZ_BasTerAlkash_4";
		break;
		
		case "PZ_BasTerAlkash_4":
			dialog.text = "경비병들 말이야, 이 친구! 쟤네한테도 눈을 가늘게 뜨고 있더라고! 근데, 원래 늘 그런 표정인 것 같기도 해. 너는 어떻게 생각해?";
			link.l1 = "모르겠어, 친구. 계속해 봐. 그들이 그를 첩자로 생각한 건가? 왜 경비병들이 그를 공격했지?";
			link.l1.go = "PZ_BasTerAlkash_5";
		break;
		
		case "PZ_BasTerAlkash_5":
			dialog.text = "누가 알겠어? 그들은 그가 마을에서 뭘 하고 있는지 알아내려고 했지...";
			link.l1 = "그래서, 그를 체포했나? 아니면...";
			link.l1.go = "PZ_BasTerAlkash_6";
		break;
		
		case "PZ_BasTerAlkash_6":
			dialog.text = "하, 어림도 없지! 놈들은 그를 잡지 못했어. 도시에서 경비병들을 베어 넘기고 정글로 도망쳤거든. 놈을 잡으려고 여러 무리를 보냈지만, 아무도 돌아오지 않았어. 상상이나 해 봐! 그 동굴을 진짜 요새로 만들어 놨다니까!";
			link.l1 = "그거 참. 좀 쉬고 잊으려고 해봐. 난 이제 가야겠어 - 머리가 빙빙 도는군.";
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
			dialog.text = "나도 직접 본 적은 없어 - 그 자식은 총독 관청 근처에서 어슬렁거리고 있더라고, 응! 하지만 그놈 선원들은 여기서 크게 한판 벌였지.";
			link.l1 = "그런가?";
			link.l1.go = "Sotta2";
		break;
		
		case "Sotta2":
			dialog.text = "다들 그가 상인이라고 하더군. 하지만 그의 선원들은 술집에서 굴러다니는 부랑자 같지 않았어, 정말이야! 그들은 마치... 마치... 뭐랄까... 무슨 말이더라...?";
			link.l1 = "알겠어. 같이 있어줘서 고마워, 친구. 몸조심해.";
			link.l1.go = "exit_sit";
			
			npchar.questTemp.PZ_Sotta = true;
			pchar.questTemp.PZ_BelizAskCitizens = sti(pchar.questTemp.PZ_BelizAskCitizens) + 1;
			AddDialogExitQuest("PZ_LongwayBelizDialog");
		break;
		
		case "Lutter1":
			dialog.text = "나는 축하 중이야! 그리고 내가 혼자라고 누가 그래? 네가 여기 있잖아, 친구! 그리고 매트에 관해서라면, 언젠가는 일어날 일이었지.";
			link.l1 = "왜 그렇게 말하는 거지? 나는 그가 수년간 행운의 여신이 돌봐준, 엄청나게 운 좋은 해적이었다고 들었어!";
			link.l1.go = "Lutter2";
		break;
		
		case "Lutter2":
			dialog.text = "헤헷, 포춘만 있었던 게 아니었군! 그는 혼자 다니는 해적이었지, 형제단 소속도 아니었고! 그런 놈들은 오래 못 버텨... 그래도, 예전에 르바쇠르 밑에 있었다는 소문은 들었어.";
			link.l1 = "맞아, 혼자서는 오래 못 버텨. 자, 축하해라. 난 가봐야겠어, 친구.";
			link.l1.go = "exit_sit";
			
			npchar.questTemp.PZ_Lutter = true;
			pchar.questTemp.PZ_BelizAskCitizens = sti(pchar.questTemp.PZ_BelizAskCitizens) + 1;
			AddDialogExitQuest("PZ_LongwayBelizDialog");
		break;
		
		case "Sepp1":
			dialog.text = "으윽, 아니, 나-나 그 사람 본 적 없어. 그 사람이 누구야?";
			link.l1 = "그는 군도에서 가장 빠른 배 중 하나인 브리그 '반텐'의 선장이야. 들어본 적 있어?";
			link.l1.go = "Sepp2";
		break;
		
		case "Sepp2":
			pchar.questTemp.PZ.TortugaHabitueBlock = true;
			
			dialog.text = "어, 아니, 난 배에는 관심 없어, 친구야, 으악! 한 잔 더 할까?";
			link.l1 = "나는 아니야. 어차피 여기서 내가 원하던 걸 얻지 못했으니까.";
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
