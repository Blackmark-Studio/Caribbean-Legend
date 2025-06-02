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
            dialog.text = "Это меню выбора типа пьяни (бетатест)";
			link.l1 = "Пусть будет алкаш";
			link.l1.go = "Beta_test_alc";
            link.l2 = "Игрок в карты";
			link.l2.go = "Beta_test_card";
			link.l3 = "Игрок в кости";
			link.l3.go = "Beta_test_dice";
		break;
		
		case "Beta_test_alc":
            dialog.text = "Алкаш выбран";
			link.l1 = "Продолжить";
			link.l1.go = "First time";
			npchar.quest.last_theme = 0;
		    npchar.quest.last_theme_game = 0;
		break;
		
		case "Beta_test_card":
            dialog.text = "Игрок в карты (30%% что пошлёт с первого раза)";
			link.l1 = "Продолжить";
			link.l1.go = "First time";
			npchar.quest.last_theme = 1;
		    npchar.quest.last_theme_game = 0;
		break;
		
		case "Beta_test_dice":
            dialog.text = "Игрок в кости (30%% что пошлёт с первого раза)";
			link.l1 = "Продолжить";
			link.l1.go = "First time";
			npchar.quest.last_theme = 1;
		    npchar.quest.last_theme_game = 1;
		break;
		
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = LinkRandPhrase("Я, может, и пьян, но в своём уме. Сейчас вот выпью с тобой, а солдаты и меня загребут! Не-е-ет...", "Я не враг городу, в котором живу. Не буду с тобой пить!" , ""+ GetSexPhrase("Приятель","Подруга") +", тебе лучше бы убраться отсюда подобру-поздорову...");
				link.l1 = RandPhraseSimple("Ну, как знаешь...", "Хех, больно надо глаза заливать! Не то время."); 
				link.l1.go = "exit";
				break;
			}
			if(CheckAttribute(pchar,"questTemp.HabitueSpeakDisable") && rand(1) == 0) // если дуэлянт то каждый второй посылает нафик
			{
				dialog.text = "Ха, судар"+ GetSexPhrase("ь","ыня") +", слыхал я о вас, как же, как же, хе-хе. В тавернах говорят, что вы записн"+ GetSexPhrase("ой","ая") +" задира и дуэлянт"+ GetSexPhrase("","ка") +", и по пьяному делу уже чуть ли не дюжину душ представили пред очи Господни. Смотрите, народ у нас, конечно, не из пугливых, да только кому охота за кружку рому живота лишиться. Мне вот лично даже за одним столом с вами сидеть боязно, так что, пойду я пожалуй.";
				link.l1 = LinkRandPhrase("Ну и скатертью дорога!","Катись, пока я добр"+ GetSexPhrase("ый","ая") +"...","Давай-давай! Улепетывай, рыбья снедь!");
				link.l1.go = "exit";
				link.l2 = "Постойте, я хотел"+ GetSexPhrase("","а") +" спросить кое-что....";
				link.l2.go = "talk_habitue_duel";
				break;
			}
			
            ok = CheckFreeSitFront(npchar);
            
            dialog.text = "Не загораживай мне свет, мух в кружке не видно!";
            link.l1 = "Уже отош"+ GetSexPhrase("ёл","ла") +"...";
		    link.l1.go = "exit";
		    if (!chrDisableReloadToLocation)
		    {
	            switch (npchar.quest.last_theme)
				{
					case "0": //пьяный.
						dialog.text = "И-ик! О, "+ GetSexPhrase("парень, ты выглядишь бывалым морским волком","деваха, ты выглядишь настоящей морской волчицей") +"! Может, купишь мне стаканчик рома?";
						link.l1 = "Может, я и "+ GetSexPhrase("морской волк","морская волчица") +", только это не значит, что я буду поить всякую рвань...";
						link.l1.go = "exit";

						if (makeint(pchar.money) >= 100 && ok) // только старые острова окучены на сесть
						{
							link.l2 = "Я и сам"+ GetSexPhrase("","а") +" с радостью присоединюсь к тебе, за компанию.";
							link.l2.go = "talk_with_alchogol";
						}
						else
						{
	                        link.l2 = "Это ещё почему?";
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
										Dialog.text = RandPhraseSimple("Сыграем в карты? Очень интересная игра!", "Предлагаю перекинуться в картишки. Ты как?");
										link.l1 = "Отчего же не сыграть? Давай сыграем.";
										link.l1.go = "Cards_begin";
										link.l2 = "А правила игры какие?";
										link.l2.go = "Cards_Rule";
										link.l3 = "Не сейчас.";
										link.l3.go = "exit";
									}
									else
					    			{
										Dialog.text = "Нет, не хочу я больше играть с тобой в карты.";
						    			link.l1 = "Ну и не надо.";
						    			link.l1.go = "exit";
									}
			                        // Игра в карты boal 20/05/05 <--
		                        break;

								case 1:
								// кости
		    						// Игра в кости boal 13/07/05 -->
	                                if (CheckNPCQuestDate(npchar, "Dice_date_begin"))
									{
										Dialog.text = RandPhraseSimple("Сыграем в кости? Очень интересная игра!", "Предлагаю постучать костяшками. Ты как?");
										link.l1 = "Отчего же не сыграть? Давай сыграем.";
										link.l1.go = "Dice_begin";
										link.l2 = "А правила игры какие?";
										link.l2.go = "Dice_Rule";
										link.l3 = "Не сейчас.";
										link.l3.go = "exit";
									}
									else
					    			{
										Dialog.text = "Нет, не хочу я больше играть с тобой в кости.";
					    				link.l1 = "Ну и не надо.";
					    				link.l1.go = "exit";
									}
			                        // Игра в кости boal 13/07/05 <--
			                        //navy --> Дуэли
									if (CheckAttribute(NPchar, "Quest.DiceCheats") && sti(NPchar.Quest.DiceCheats) >= 1) 
									{
					    				link.l9 = RandSwear() + " Ты жульничал!!!";
					    				link.l9.go = "outraged";
									}
									//navy <--
			    				break;
	    					} 
						}
	        			else
	        			{
	                        dialog.text = RandPhraseSimple("Убирайся от моего стола ко всем чертям!", " А... чего? Кто это?.. и-ик.. Отвали!");
	                        link.l1 = RandPhraseSimple("Пьянство губит твою грешную душу - опомнись!", "Не нужно мне грубить.");
	        			    link.l1.go = "exit";
	        			    link.l2 = RandPhraseSimple("Как ты со мной разговариваешь, скотина! Сейчас я научу тебя хорошим манерам.", "Вот я тресну тебя сейчас по башке, вмиг протрезвеешь.");
	        	            link.l2.go = "tavern_keeper";
	        			}
					break;
				}
			}
			Diag.TempNode = "First time";
	    break;
	    
		case "talk_habitue_duel":
			dialog.text = "Ничего, судар"+ GetSexPhrase("ь","ыня") +", я вам не скажу! И вряд ли кто ещё согласится, ведь разговоры с вами плохо кончаются... Но память людская коротка - глядишь через месяцок-другой все ваши похождения и подзабудутся. Если вы, конечно, память-то людям не освежите, хе-хе... Прощайте, судар"+ GetSexPhrase("ь","ыня") +". ";
			link.l1 = "Ну и ладно ....";
			link.l1.go = "exit";
		break;
		
	    // карты -->
	    case "Cards_Rule":
   			dialog.text = CARDS_RULE;
			link.l1 = "Что ж, давай начнём!";
			link.l1.go = "Cards_begin";
			link.l3 = "Нет, это не для меня...";
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

			Dialog.text = "Тогда давай определимся со ставкой (введите ставку).";
			link.l1 = "100";
			link.l1.edit = 1;
			link.l1.go = "Cards_Node_2";
			link.l3 = "Пожалуй, мне пора.";
			link.l3.go = "exit_sit";
		break;
		
		case "Cards_Node_2":
			iLa_Puesta = GetStrSmallRegister(dialogEditStrings[1]);
            if (!CheckCardsGameSmallRate())
		    {
                dialog.text = "О тебе ходит слава непревзойденного шулера. Я не буду с тобой играть в карты вообще.";
                link.l1 = "Все врут! Ну и не нужно.";
			    link.l1.go = "exit_sit";
			    break;
		    }
		    
			if (sti(PCHar.Money) < sti(iLa_Puesta)*3)
		    {
                dialog.text = "Да ты, "+ GetSexPhrase("дружок","дорогуша") +", на мели. Приходи, когда разбогатеешь.";
                link.l1 = "Ладно.";
			    link.l1.go = "exit_sit";
			    break;
		    }
		
			if (sti(NPChar.Money) < sti(iLa_Puesta)*3)
		    {
                dialog.text = "Я уже проигрался в пух и прах, не мой день.";
                link.l1 = "Ладно.";
			    link.l1.go = "exit_sit";
			    break;
		    }
		else
		{
			if(sti(iLa_Puesta) < 50)
			{
				dialog.text = "Хех, ты смеёшься?! Играть на " + iLa_Puesta + " песо?! Давай ставку поменяем, иначе я с тобой играть не буду!";
				link.l1 = "Да, пожалуй. Ставку надо бы повысить.";
				link.l1.go = "Cards_begin_2";
				link.l2 = "Что-то я играть раздумал"+ GetSexPhrase("","а") +".";
				link.l2.go = "exit_sit";
				break;
			}
			
			if(sti(iLa_Puesta) > 1000)
			{
				dialog.text = "Играть на такие деньжища? Нет, увольте... Давай ставку менять!";
				link.l1 = "Да, ты прав. Ставку нужно понизить.";
				link.l1.go = "Cards_begin_2";
				link.l2 = "Что-то я вообще играть раздумал"+ GetSexPhrase("","а") +".";
				link.l2.go = "exit_sit";
				break;
			}
			dialog.text = "Хорошо, играем по " + iLa_Puesta + " монет.";
			link.l1 = "Сдавай!";
			link.l1.go = "Cards_begin_go";
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
			pchar.GenQuest.Cards.iRate     = sti(iLa_Puesta);
            pchar.GenQuest.Cards.SitType   = true;
		}
		break;
		
		case "Cards_begin_2":
			dialog.text = "Так какая ставка будет? (Введите ставку).";
			link.l1 = "50";
			link.l1.edit = 1;
			link.l1.go = "Cards_Node_2";
			link.l2 = "Пожалуй, я играть не буду...";
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
			link.l1 = "Что ж, давай начнём!";
			link.l1.go = "Dice_begin";
			link.l3 = "Нет, это не для меня...";
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
			Dialog.text = "Давай определимся со ставкой (введите ставку).";
			link.l1 = "50";
			link.l1.edit = 1;
			link.l1.go = "Dice_Node_2";
			link.l3 = "Пожалуй, мне пора.";
			link.l3.go = "exit_sit";
		break;

		case "Dice_Node_2":
			iLa_Puesta = GetStrSmallRegister(dialogEditStrings[1]);
            if (!CheckDiceGameSmallRate())
		    {
				dialog.text = "О тебе ходит слава непревзойденного шулера. Я не буду с тобой играть в кубики вообще.";
                link.l1 = "Все врут! Ну и не нужно.";
			    link.l1.go = "exit_sit";
			    break;
		    }

			if (sti(pchar.Money) < sti(iLa_Puesta)*6)
		    {
                dialog.text = "Да ты, "+ GetSexPhrase("дружок","дорогуша") +", на мели. Приходи, когда разбогатеешь.";
                link.l1 = "Ладно.";
			    link.l1.go = "exit_sit";
			    break;
		    }
			
			if (sti(npchar.Money) < sti(iLa_Puesta)*6)
		    {
                dialog.text = "Я уже проигрался в пух и прах, не мой день.";
                link.l1 = "Ладно.";
			    link.l1.go = "exit_sit";
			    break;
		    }
		else
		{
			if(sti(iLa_Puesta) < 50)
			{
				dialog.text = "Хех, ты смеёшься?! Играть по " + iLa_Puesta + " песо за кубик?! Давай ставку поменяем, иначе я с тобой играть не буду!";
				link.l1 = "Да, пожалуй. Ставку надо бы повысить.";
				link.l1.go = "Dice_begin_2";
				link.l2 = "Что-то я играть раздумал"+ GetSexPhrase("","а") +".";
				link.l2.go = "exit_sit";
				break;
			}
			
			if(sti(iLa_Puesta) > 1000)
			{
				dialog.text = "Играть в кубики на такие деньжища? Нет, увольте... Давай ставку менять!";
				link.l1 = "Да, ты прав. Ставку нужно понизить";
				link.l1.go = "Dice_begin_2";
				link.l2 = "Что-то я вообще играть раздумал"+ GetSexPhrase("","а") +".";
				link.l2.go = "exit_sit";
				break;
			}
			dialog.text = "Хорошо, играем по " + iLa_Puesta + " монет за кубик.";
			link.l1 = "Поехали!";
			link.l1.go = "Dice_begin_go";
			pchar.GenQuest.Dice.npcharIdx = npchar.index;
			pchar.GenQuest.Dice.iRate     = sti(iLa_Puesta);
            pchar.GenQuest.Dice.SitType   = true;
		}
		break;
		
		case "Dice_begin_2":
			dialog.text = "Так какая ставка будет? (Введите ставку).";
			link.l1 = "50";
			link.l1.edit = 1;
			link.l1.go = "Dice_Node_2";
			link.l2 = "Пожалуй, я играть не буду...";
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
			dialog.text = "Ну... И-ик! Бывает все на свете хорошо... И-ик! В чем дело сразу не поймешь... И-ик! А просто славно ром пошёл... И-ик! ямайский чёрный ром... И-ик!\nПодставляй, наливай!";
			link.l1 = "А дальше?";
			link.l1.go = "talk_with_alchogol_song_2";
			link.l2 = "Да ну тебя!";
			link.l2.go = "exit";
		break;
		
		case "talk_with_alchogol_song_2":
			dialog.text = "Мелькают кружки, лица, каблуки... И-ик! И полом по башке. Я пью всегда со всеми и везде... И-ик! Где выпивка? Нужна!";
			link.l1 = "А дальше?";
			link.l1.go = "talk_with_alchogol_song_3";
			link.l2 = "Да ну тебя!";
			link.l2.go = "exit";
		break;
		
		case "talk_with_alchogol_song_3":
			dialog.text = "Когда на сердце тяжесть и холодно в груди, ты пару кружек рома на грудь себе прими! И без забот и фальши всё станет вдруг вокруг. Поймешь ты, что я лучший тебе я самый друг!";
			link.l1 = "Да ну тебя!";
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
			dialog.text = LinkRandPhrase("Ик! Вот это я понимаю! Вот это по-нашему! Ну, так чего? Поставишь мне кружечку рома?",
						"Присаживайтесь, " + GetAddress_Form(npchar) + ", опрокинем по кружечке доброго ямайского рому. Это здоровью никогда не повредит. А для человека, интересующегося делами, лучше места, чем таверна не найти, это я вам точно говорю... Немного денег, пара кружек хорошей выпивки - и вы узнаете все, что хотите... и даже больше. Уж поверьте старому завсегдатаю...",
						"Эхе-хе, присаживайтесь, "+ GetSexPhrase("сударь мой","сударыня") +", выпьем... отчего ж не выпить в хорошей-то кампании? В нашей портовой таверне иногда очень интересные вещи можно услышать, если иметь терпение и пить маленькими глотками, чтобы оверкиль не свалиться... То кэп какой-нибудь загрузит лишку на борт и начнёт своими похождениями хвалиться, то кто-то знающий чего сболтнет в нужной кондиции... Тут разный люд обретается, и многим есть что порассказать, поверьте, "+ GetSexPhrase("сударь мой","сударыня") +".");
			link.l1 = "Да запросто! Трактирщик, рома!";
			link.l1.go = "sit_2";
		break;

		// Церковный генератор. Квест №2 -->
		case "Alcogol_GenQuest_Church_2_1":
			dialog.text = "А то! Слыхал"+ GetSexPhrase("","а") +" - уже и церкви грабить начали!";
				link.l1 = "Ну, на такое только пираты способны...";
				link.l1.go = "Alcogol_GenQuest_Church_2_2";
				DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.AskPeople");
				DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.AskBarmen");
				DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.AskAlcash");
			break;
			
		case "Alcogol_GenQuest_Church_2_2":
			dialog.text = "Да какие там пираты! Обыкновенные сухопутные проходимцы, к тому же явно свои, местные: откуда пиратам знать, когда церковная мошна полным-полна под завязку? Да и не стали бы они связываться.";
				link.l1 = "Храбрые однако молодчики. Отважно вскрыли хлипкий церковный засов...";
				link.l1.go = "Alcogol_GenQuest_Church_2_3";
			break;
			
		case "Alcogol_GenQuest_Church_2_3":
			dialog.text = "Во-во. И умные, сил нет. Кто ж так подставляется?!";
				link.l1 = "Твоя правда. Весь приход, затянув пояса, откладывал лишнюю монету, чтоб отнести в церковную кружку, а теперь какие-то умники одним махом нажились? Да им теперь спуску не дадут, всем миром выловят.";
				link.l1.go = "Alcogol_GenQuest_Church_2_4";
			break;
			
		case "Alcogol_GenQuest_Church_2_4":
			dialog.text = "Да не. Кто их выловит, грабанули пожертвования - и поминай как звали, за город рванули. А джунгли-то большие, их теперь ищи-свищи хоть до второго пришествия. А пройдёт месяц-другой, и про это дело совсем забудут. Я тебе другое толкую...";
				link.l1 = "Ну знаешь, такое люди не прощают.";
				link.l1.go = "Alcogol_GenQuest_Church_2_5";
			break;
			
		case "Alcogol_GenQuest_Church_2_5":
			dialog.text = "У людей память, как дырявый ялик. Люди простят. А Бог?! Он всё видит... Вот кого бояться надо! Случилась лет десять назад жуткая история с одним моим приятелем, который за неуважение к Создателю чуть не угодил морскому чёрту в зубы...";
				link.l1 = "Извини, друг, твою историю я послушаю в другой раз. Бывай.";
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
			Log_TestInfo("Бандюганы, грабанувшие церковь, будут в локации - " + sGenLocation + " Времени на их поиск - 1 день");
			sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "2");
			break;
		// <-- Церковный генератор. Квест №2
		//--> работорговец
			case "Jamaica_ratH_1":
				dialog.text = "А-а, Франсуа! Помню, помню такого... Не, не знаю. Но вот что я тебе скажу: расспроси-ка ты о нём нашу официантку. Сколько он здесь жил - она каждую ночь к нему бегала. Оторва, одно слово. Может, он ей чего сболтнул.";
				link.l1 = "Спасибо тебе, приятель, за добрый совет. Пойду, поговорю с ней.";
				link.l1.go = "exit_sit";
				pchar.questTemp.Slavetrader = "FindRatJamaica_W";
			break;
			
			case "EscapeSlave_Villemstad_H1":
				dialog.text = "Да-а-а, чего только не увидишь в море... Вот и в последнем рейсе тако-ое случилось...";
				link.l1 = "Ну, рассказывай, только не ври сильно. А я пока ещё рому налью.";
				link.l1.go = "EscapeSlave_Villemstad_H2";
			break;
			
			case "EscapeSlave_Villemstad_H2":
				dialog.text = "Вот вам крест, благородн"+ GetSexPhrase("ый господин","ая госпожа") +" - своими глазами видел... Идёт корабль, а вместо экипажа на нём - образины-гаврилы... э-э... обезьяны-гориллы... ну, или макаки, чёрт их разберет...";
				link.l1 = "Чего-о?! А скажи, любезный, ты и на вахте к бутылке прикладываешься?";
				link.l1.go = "EscapeSlave_Villemstad_H3";
			break;
			
			case "EscapeSlave_Villemstad_H3":
				dialog.text = "Да не сойти мне с этого места, ежели я вру! Ты разве никогда не слыхал"+ GetSexPhrase("","а") +" про корабль обезьян? Так вот, это был он... забодай меня креветка!";
				link.l1 = "Какой ещё корабль обезьян? Нет, не слыхал"+ GetSexPhrase("","а") +".";
				link.l1.go = "EscapeSlave_Villemstad_H4";
			break;
			
			case "EscapeSlave_Villemstad_H4":
				dialog.text = "О-о... а я говорю, что видел его собственными глазами. В шторм это было, " + pchar.questTemp.SlavetraderAreal.add + ". Темень - хоть глаз выколи, и тут появляется из ниоткуда он - корабль с рваными парусами... У него были сломаны фок, и грот, и нок, и бак, и-и-и... короче - все было у него сломано! А он себе идёт прямо против ветра и хоть бы что!\nА на палубе - столько обезьян в лохмотьях, как тюленей на лежбище! И за штурвалом стоит натуральная горилла! Роста девяти футов, в леопардовой шкуре, а на груди вместо нательного креста у него акульи зубы... Глаза горят, зубы сверкают, увидел он нас и ка-а-ак заорет нечеловеческим голосом...";
				link.l1 = "Ну, совсем ты, братец, заврался. Чего только с пьяных глаз не привидится. Ты ещё скажи, что на корме у него надпись была 'Летучий Голландец'.";
				link.l1.go = "EscapeSlave_Villemstad_H5";
			break;
			
			case "EscapeSlave_Villemstad_H5":
				dialog.text = "Э, нет, это был не 'Голландец'. Говорю же - не вру я! Это был барк, а на корме было написано " + pchar.questTemp.Slavetrader.ShipName + ".";
				link.l1 = "Кха-ркх!! Чёрт возьми! Кажется, я знаю, что это были за обезьяны... Действительно, ром развязывает языки, надо только слушать.";
				link.l1.go = "EscapeSlave_Villemstad_H6";
			break;
			
			case "EscapeSlave_Villemstad_H6":
				dialog.text = "Ну я же говорю тебе! А ты не веришь!.. Давай, выпьем по единой и все... я швартуюсь.";
				link.l1 = "Ладно, спасибо тебе за интересную историю. Мне пора. Счастливо, приятель.";
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
			dialog.text = "Не-е, капитан. Матросом - это не моё. У меня у самого когда-то был корабль, да... эх! Неудача однажды приключилась.";
			link.l1 = "Послушай, я вот видел на рейде необычный корабль - 'Мейфенг' называется. Я раньше таких никогда не видел. Чей он? Может, продается? Я бы посмотрел.";
			link.l1.go = "Lucas_Tavern_1";
		break;
		
		case "Lucas_Tavern_1":
			dialog.text = "Ха! Эка хватил, капитан! Не думаю, что китаец захочет продать тебе или кому-либо свою посудину.";
			link.l1 = "Китаец? А что, на Кюрасао есть китайцы, да ещё и капитаны собственных кораблей?";
			link.l1.go = "Lucas_Tavern_2";
		break;
		
		case "Lucas_Tavern_2":
			dialog.text = "Как видишь, есть. Хотя корабль вовсе и не его, а принадлежит Торговой Компании. Причём, говорят, самому вице-директору, а теперь исполняющему обязанности губернатора, минхеру Роденбургу.";
			link.l1 = "О! Так Матиас Бек ушёл в отставку?";
			link.l1.go = "Lucas_Tavern_3";
		break;
		
		case "Lucas_Tavern_3":
			dialog.text = "Ха! Минхер, надо почаще бывать на берегу, или новости узнавать. Матиас Бек отстранен от исполнения обязанностей губернатора и помещен в тюрьму до выяснения.";
			link.l1 = "Ну дела! Действительно, надо чаще на суше бывать. И давно это случилось?";
			link.l1.go = "Lucas_Tavern_4";
		break;
		
		case "Lucas_Tavern_4":
			dialog.text = "Да буквально два дня назад. В порт прибыла курьерская бригантина. Весьма потрепанная, надо сказать - явно побывала в серьёзном бою. Капитан бригантины отправился на доклад к минхеру Роденбургу. А буквально через несколько часов Матиас Бек был арестован минхером Роденбургом и комендантом по подозрению в связи с агентами английской разведки.";
			link.l1 = "Ты рассказываешь просто невероятные вещи. Губернатор Кюрасао - английский шпион?";
			link.l1.go = "Lucas_Tavern_5";
		break;
		
		case "Lucas_Tavern_5":
			dialog.text = "Честно говоря, мне тоже в это слабо верится. Я слышал, к нам скоро должен прибыть директор Компании, сам Питер Стайвесант. Наверно, он и будет вести следствие.";
			link.l1 = "Ну, тогда, пожалуй, ты прав - рискованно беспокоить минхера Роденбурга в такое время.";
			link.l1.go = "Lucas_Tavern_6";
		break;
		
		case "Lucas_Tavern_6":
			dialog.text = "Ты здраво мыслишь, капитан! Тем более, что 'Мейфенг' сейчас под погрузкой - она сегодня ночью вернулась из плавания к берегам южного Мэйна и вновь выходит в море. И вообще, на этом корабле сейчас творится что-то невероятное - голландские матросы и гвардейцы Компании отправлены в увольнение на берег, и набирается другая команда. И скажу тебе - эти новые волонтеры через одного - пираты и уголовники, не пить мне рома до конца дней моих...";
			link.l1 = "Чудеса, да и только... Эх, жаль! Такой красивый кораблик... Ну, значит, не судьба. Спасибо за интересный рассказ, за свежие новости! Рад был пообщаться.";
			link.l1.go = "Lucas_Tavern_7";
		break;
		
		case "Lucas_Tavern_7":
			dialog.text = "И тебе спасибо за компанию и за ром, капитан! Заходи ещё!";
			link.l1 = "Непременно!";
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
			if(bImCasual) NewGameTip("Режим исследования: таймер не отключён. Уложитесь в срок!");
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
				dialog.text = "Ха! "+pchar.GenQuest.FindFugitive.Name+"? Знаю, знаю... Очень он нелюдимый, твой сослуживец. Одиночка, одно слово. Целый день, до ночи, на своём баркасе шарится вдоль берегов острова. Скажу по секрету: все думают, что он рыбак, а он ловит жемчуг... Хе-хе, я точно знаю!";
				link.l1 = "Хех! Так ты не подскажешь, где я смогу его найти?";
				link.l1.go = "FindFugitiveHb_1";
			}
			else
			{
				dialog.text = ""+pchar.GenQuest.FindFugitive.Name+"? Нет, клянусь всеми выпитыми кружками, я впервые слышу это имя... А ты... ик! Спроси у нашего бармена - он-то точно всё знает!";
				link.l1 = "Хм... Ладно, поспрашиваю ещё людей. Ну, дружище, спасибо за компанию. Бывай!";
				link.l1.go = "exit_sit";
			}
		break;
		
		case "FindFugitiveHb_1":
			dialog.text = "Подскажу, конечно! Каждое утро его можно найти на берегу, у "+XI_ConvertString(pchar.GenQuest.FindFugitive.Shore+"Gen")+". Только приходи очень рано, не то уйдёт в море, и будешь ждать до следующего утра.";
			link.l1 = "Спасибо! Ты мне очень помог, дружище. Бывай!";
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
			dialog.text = "Да все около верфи нашей ошивался, плотников о чём-то расспрашивал... Вот и дорасспрашивался. Шепнули добрые люди коменданту, что подозрительный тип по городу расхаживает, тот его - р-раз! Ик! И в казематы. Там-то и оказалось, что он вовсе не торговец.";
			link.l1 = "Не иначе, как хотел украсть какую-то секретную разработку вашего корабела, да?";
			link.l1.go = "trial_spy_1";
		break;
		
		case "trial_spy_1":
			dialog.text = "А кто же его ведает! Но скажу тебе так, дружище: я лично уверен, что его интересовал галеон 'Алькантара'. Ик! Вот руку на отсечение даю! Этот корабль снаряжает сам сеньор губернатор, так что целью этого прохвоста наверняка был сбор информации об этом судне.";
			link.l1 = "Ха! Вполне возможно. Наверняка сеньор губернатор повезёт на нём что-то ценное...";
			link.l1.go = "trial_spy_2";
		break;
		
		case "trial_spy_2":
			dialog.text = "А то как же! Уж наверняка что-то стоящее внимания, ик! Да и поговаривают, что видали рыбаки в наших водах какое-то чужое военное судно, вроде как фрегат. Уж не оттуда ли этот шпик пришёл?";
			link.l1 = "Всякое может быть. Ладно, приятель, спасибо за компанию, пора мне уже!";
			link.l1.go = "exit_sit";
			pchar.questTemp.Trial = "spy_drink";
			
			if(CheckAttribute(pchar,"questTemp.trialHabitueId"))
			{
				if (GetCharacterIndex(pchar.questTemp.trialHabitueId) != -1)
				{
					sld = characterFromId(pchar.questTemp.trialHabitueId);
					sld.lifeday = 0;
					DeleteAttribute(pchar,"questTemp.trialHabitueId");
					LAi_CharacterDisableDialog(sld);
					DelLandQuestMark(sld);
				}
			}
			// belamour legendary edtion -->
			if (GetCharacterIndex("PortoBello_Poorman") < 0)
			{
				// новый нищий
				sld = GetCharacter(NPC_GenerateCharacter("PortoBello_Poorman", "panhandler_"+(rand(5)+1), "man", "man", 5, SPAIN, -1, false, "slave"));
				sld.city = "PortoBello";
				sld.location	= "PortoBello_town";
				sld.location.group = "goto";
				sld.location.locator = "goto15";
				sld.forStay.locator = "goto15"; //где генеримся в случае стояния
				sld.forSit.locator0 = "goto3";
				sld.forSit.locator1 = "goto25"; //три локатора, где генеримся в случае сидения
				sld.forSit.locator2 = "goto12";
				LAi_SetLoginTime(sld, 9.0, 21.99);
				sld.Dialog.Filename = "Common_poorman.c";
				LAi_SetPoorType(sld);
				LAi_SetHP(sld, 50.0, 50.0);
				sld.greeting = "poorman_male";
				LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
			}
			sld = characterFromId("PortoBello_Poorman");
			LAi_RemoveLoginTime(sld);
			ChangeCharacterAddressGroup(sld, "Portobello_town", "goto", "goto15");
			AddLandQuestMark(sld, "questmarkmain");
			DelLandQuestMark(characterFromId("portobello_tavernkeeper"));
			// <-- legendary edtion
			AddQuestRecord("Trial", "14");
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
				dialog.text = "За твоё здоровье и за твою щедрость!";
				link.l1 = "Дружище, а ты не видел в городе одного китайца?";
				link.l1.go = "PZ_BasTerAlkash_1";
				break;
			}
			// <== Квест "Путеводная звезда" - Sinistra
			
			dialog.text = LinkRandPhrase("Ты настоящ"+ GetSexPhrase("ий друг","ая морячка") +"! Давай за знакомство!",
										 "Ик! Какой ром! Ну... вздрогнем!",
										 "За твоё здоровье и за твою щедрость!");
			link.l1 = "Эх, забористый ром. Ладно, мне уже пора, удачно посидеть.";
			link.l1.go = "exit_sit";
			if (makeint(pchar.money) >=2)
			{
				link.l2 = "Давай ещё по одной кружечке.";
				link.l2.go = "sit_3";
			}

			link.l4 = LinkRandPhrase("Кажется, что пров"+ GetSexPhrase("ёл","ела") +" в море целую вечность. Что новенького в ваших краях?",
									"Расскажи-ка мне, о чём теперь болтают? Не зря же я пою тебя ромом...",
									"Скажи мне, братец, какие байки ходят по тавернам?");
			link.l4.go = "rumours_habitue";
		break;

		case "sit_3":
			int iSituation;
			if(IsEquipCharacterByArtefact(pchar, "totem_01")) iSituation = makeint(rand(3));
			else iSituation = makeint(rand(5));
			switch (iSituation)
			{
				case 0:
					dialog.text = "О! Здравая идея!";
					link.l1 = "Трактирщик! Рома!";
					link.l1.go = "sit_2";
				break;

				case 1:
					dialog.text = "За тебя! А, дьявол! Кто это?!";
					link.l1 = "А? Что? Где? Показалось видать.";
					link.l1.go = "sit_2";// to_do "sit_case_5_exit";
				break;
				
                case 2:
	         		dialog.text = "Пить так пить! Ещё давай?";
					link.l1 = "Наливай!";
					link.l1.go = "sit_2";
                break;				
				
				case 3:
					if(rand(1) == 0)
					{
						dialog.text = RandPhraseSimple("Вот вы, " + GetAddress_Form(NPChar) + ", наверное думаете, что вами все восхищаются, да? А по мне - так вы обычн"+ GetSexPhrase("ый","ая") +" разбойни-"+ GetSexPhrase("гик","гица") +"!.. и убийца. Придумали тоже - 'бла-ародн"+GetSexPhrase("ый","ая")+" пират"+GetSexPhrase("","ка")+"'! Бандит"+GetSexPhrase("","ка")+" - он"+GetSexPhrase("","а")+" и есть бандит"+GetSexPhrase("","ка")+", что на мор-ик, что на суше...",
							"Ик! "+ GetSexPhrase("Под... подонок","Др... дрянь") +"! Ты х-хочешь меня споить, ик! И украсть мои деньги!");
						link.l1 = "Я вижу, ты уже лишнего на борт принял... иди-ка - проспись, да и мне уже пора.";
						link.l1.go = "exit_sit";						
						link.l2 = "Что-то не нравится мне твой тон, приятель. Попридержал бы ты язык.";
						link.l2.go = "sit_case_2_enemy";
						link.l3 = "Ты кого бандит"+GetSexPhrase("ом","кой")+" назвал, сухопутная крыса?! Поглядим, как ты запоёшь, с дырой в брюхе!";
						link.l3.go = "sit_case_2_enemy2";
						link.l4 = "Спокойней! Ты чего, забыл? Я "+GetSexPhrase("твой единственный настоящий друг","твоя единственная настоящая подруга")+"!";
						link.l4.go = "sit_case_2_friend";					
					}
					else
					{
						/* // Captain Beltrop, 27.06.21, новый вариант
						if (rand(1) == 0)
						{
							Diag.CurrentNode = Diag.TempNode;
							AddDialogExitQuestFunction("Tavern_SetBadHabitue");
							DialogExit();
						}
						else
						{ */
							dialog.text = RandPhraseSimple("Чего ты на меня так уставил"+ GetSexPhrase("ся","ась") +"? Н-небось, хочешь споить и обчистить карманы?! Понаехало здесь разного сброду!  Ик!.. Честному человеку уже и в таверну зайти нельзя!",
							"Ты меня уважаешь?.. Уважаешь, я тебя с-спрашиваю?!! А-то гляди у меня... Я ни-ко-му не спущу - сразу промеж глаз ка-ак... и всё - заказывай п-панихиду.");
							link.l1 = "Приятель, вижу - трюм у тебя под завязку. Шёл бы ты домой... да и мне уже пора.";	
							link.l1.go = "exit_sit";
							link.l2 = "Не так шибко, парень. Ты всё-таки знай, с кем разговариваешь...";
							link.l2.go = "sit_case_2_enemy1";
							link.l3 = "Ты на кого рот разинул?! Сейчас я тебя научу уму-разуму!";
							link.l3.go = "sit_case_2_enemy2";
							link.l4 = "Спокойней! Ты чего, забыл? Я "+GetSexPhrase("твой единственный настоящий друг","твоя единственная настоящая подруга")+"!";
							link.l4.go = "sit_case_2_friend";
						//}
					}			
				break;

				case 4:
					dialog.text = "Слушай! Ты х-хороший человек! М-может быть, т-ты поможешь мне в... в... в одном дельце?";
					link.l1 = "Нет, пожалуй, мне уже пора идти.";
					link.l1.go = "exit_sit";
					link.l2 = "К-конечно! Ведь мы же... ик... друзья!";
					link.l2.go = "sit_case_3";
				break;

				case 5:
					if (GetSummonSkillFromName(pchar, SKILL_SNEAK) > rand(110) )
					{
						dialog.text = "...И тогда я схв-схватил его шпагу за л-лезвие и...";
						link.l1 = "... а она мне и говорит...";
						link.l1.go = "sit_2";
					}
					else
					{
						dialog.text = "...И тогда я схв-схватил его шпагу за л-лезвие и...";
						link.l1 = "... и-ик! А она мне и г-говорит...";
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
			dialog.text = "Дело в т-том, что м-меня оскорбил один из с-солдат. В-вот!";
			link.l1 = "С-солдат? Н-нет, я, пожалуй пас.";
			link.l1.go = "exit_sit";
			link.l2 = "Спокойней! Ты чего, забыл? Я "+GetSexPhrase("твой единственный настоящий друг","твоя единственная настоящая подруга")+"!";
			link.l2.go = "sit_2";
		break;

		case "sit_case_2_friend":
			dialog.snd = "Voice\HADI\HADI038";
			dialog.text = "Ты? К-как"+GetSexPhrase("ой","ая")+" ты мне "+GetSexPhrase("друг","подруга")+"?! Н-нет! Ты хочешь... ик...  ты хочешь меня убить! В-вот!";
			link.l1 = "Ладно, вижу, тебе уже хватит на сегодня. Прощай.";
			link.l1.go = "exit_sit";
			link.l2 = "Что? Да я тебе сейчас докажу, что я не хочу тебя убивать! Я тебе сейчас руку... ик... отрежу!";
			link.l2.go = "sit_case_2_friend_2";
		break;

		case "sit_case_2_friend_2":
			dialog.snd = "Voice\HADI\HADI039";
			dialog.text = "А-а-а! Уберите "+ GetSexPhrase("его","её") +" от меня!!";
			link.l1 = "Да ты успокойся... ик... больно не будет!";
			link.l1.go = "tavern_keeper";
		break;

		case "sit_case_2_enemy":
			dialog.snd = "Voice\HADI\HADI040";
			dialog.text = "А вы меня не пугайте!.. не на того напал-ик!.. Таким как вы, самое место на виселице, как и всякому отре-ик! Сколько перья ни распускай - а гнилой рыбой за версту несёт. И выбирать выражения с таки-ик, как вы, я не намерен!";
			link.l1 = "Арх, да что с такой пьяни взять. Пойду, подышу свежим воздухом...";
			link.l1.go = "exit_sit1";
			link.l2 = "А ты, парень, зарвался. Сейчас я запихну эти слова тебе в глотку!";
			link.l2.go = "sit_case_2_enemy3";
		break;

		case "sit_case_2_enemy1":		
			dialog.snd = "Voice\HADI\HADI040";
			dialog.text = "Чего-о?! Да я тебя сейчас вот этими руками... Ик!.. От меня ещё "+GetSexPhrase("ни один","никто")+" не ушёл!";
			link.l1 = "Вот же пьяная свинья, такой вечер испортил. Ладно, лови своих тараканов, пойду я, пожалуй.";
			link.l1.go = "exit_sit1";
			link.l2 = RandSwear() + "Вижу, ты не угомонишься. Придётся дать урок хороших манер.";
			link.l2.go = "sit_case_2_enemy3";
		break;
		
		case "sit_case_2_enemy2":	
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			if(rand(1) == 0)
			{
				dialog.text = LinkRandPhrase("Подходи, каналья! Сейчас ты получишь сполна!", RandSwear() + "Сейчас я тебя разделаю, как подобает!","Ха! Давай, моряч"+ GetSexPhrase("ок","ка") +" - поглядим, что ты можешь на суше!");
				link.l1 = RandPhraseSimple(RandPhraseSimple("Клянусь, ты об этом пожалеешь!!!","Я укорочу твой поганый язык по самые уши!"), RandPhraseSimple("Я выпотрошу тебя, как селёдку!","Клянусь, я заставлю тебя замолчать!!!"));
				link.l1.go = "fight_right_now";
			}
			else
			{
				dialog.text = "А ну-ка, парни! Выметем эту чешую из нашего города!";
				link.l1 = RandPhraseSimple(RandSwear() + "Ну, молитесь, недоноски!","Ах, ты ещё и не один!!! Ну - будет тебе в аду компания!");
				link.l1.go = "fight_right_now_1";
			}
		break;
		
		case "sit_case_2_enemy3":	
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
			if(rand(1) == 0)
			{
				dialog.text = LinkRandPhrase("Подходи, каналья! Сейчас ты получишь сполна!", RandSwear() + "Сейчас я тебя разделаю, как подобает!","Ха! Давай, моряч"+ GetSexPhrase("ок","ка") +" - поглядим, что ты можешь на суше!");
				link.l1 = RandPhraseSimple(RandPhraseSimple("Клянусь, ты об этом пожалеешь!!!","Я укорочу твой поганый язык по самые уши!"), RandPhraseSimple("Я выпотрошу тебя, как селёдку!","Клянусь, я заставлю тебя замолчать!!!"));
				link.l1.go = "fight_right_now";
			}
			else
			{
				dialog.text = "А ну-ка, парни! Выметем эту чешую из нашего города!";
				link.l1 = RandPhraseSimple(RandSwear() + "Ну, молитесь, недоноски!","Ах, ты ещё и не один!!! Ну - будет тебе в аду компания!");
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
			dialog.text = "Эй, я что-то не понял! Стоило мне сходить за угол, а на моё место уже какой-то салага приземлился. А ну пошёл отсюда!";
			link.l1 = "Вот так всегда: только сядешь за стол - и окажется, что здесь уже занято... Держи своё место, я всё равно уже хотел уходить.";
			link.l1.go = "bad_habitue1";
			link.l2 = "Ещё одна такая фраза из твоего грязного рта - и это будет последнее, что ты скажешь в своей жизни, понял?";
			link.l2.go = "bad_habitue2";
			link.l3 = "Не знаю, действительно ли это было твоё место, но я не позволю так с собой разговаривать. Следи за словами.";
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
				dialog.text = LinkRandPhrase("Подходи, каналья! Сейчас ты получишь сполна!", RandSwear() + "Сейчас я тебя разделаю, как подобает!","Ха! Давай, моряч"+ GetSexPhrase("ок","ка") +" - поглядим, что ты можешь на суше!");
				link.l1 = RandPhraseSimple(RandPhraseSimple("Клянусь, ты об этом пожалеешь!!!","Я укорочу твой поганый язык по самые уши!"), RandPhraseSimple("Я выпотрошу тебя, как селёдку!","Клянусь, я заставлю тебя замолчать!!!"));
				link.l1.go = "fight_right_now";
			}
			else
			{
				dialog.text = "А ну-ка, парни! Выметем эту чешую из нашего города!";
				link.l1 = RandPhraseSimple(RandSwear() + "Ну, молитесь, недоноски!","Ах, ты ещё и не один!!! Ну - будет тебе в аду компания!");
				link.l1.go = "fight_right_now_1";
			}
		break;
		
		case "bad_habitue3":
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			if(rand(1) == 0)
			{
				dialog.text = LinkRandPhrase("Подходи, каналья! Сейчас ты получишь сполна!", RandSwear() + "Сейчас я тебя разделаю, как подобает!","Ха! Давай, моряч"+ GetSexPhrase("ок","ка") +" - поглядим, что ты можешь на суше!");
				link.l1 = RandPhraseSimple(RandPhraseSimple("Клянусь, ты об этом пожалеешь!!!","Я укорочу твой поганый язык по самые уши!"), RandPhraseSimple("Я выпотрошу тебя, как селёдку!","Клянусь, я заставлю тебя замолчать!!!"));
				link.l1.go = "fight_right_now";
			}
			else
			{
				dialog.text = "А ну-ка, парни! Выметем эту чешую из нашего города!";
				link.l1 = RandPhraseSimple(RandSwear() + "Ну, молитесь, недоноски!","Ах, ты ещё и не один!!! Ну - будет тебе в аду компания!");
				link.l1.go = "fight_right_now_1";
			}
		break;
		
		//--> Sinistra Длинные тени старых грехов
		case "DTSG_NightIskat":
			dialog.text = "К-конечно, мы ведь все друг друга знаем! А почему ты с-спрашиваешь?";
            link.l1 = "Да вот к ростовщику хотел зайти и узнал, что он продал свой старый дом. Не подскажешь, где он теперь живёт?";
            link.l1.go = "DTSG_NightIskat_2";
		break;
		
		case "DTSG_NightIskat_2":
			dialog.text = "А зачем он тебе п-понадобился в такое время, ик? Зайди в банк утром, делов-то!";
            link.l1 = "Деньги нужны срочно. Пусть поработает! Он же говорит на всех нас, что мы дармоеды, которые только клянчат и не возвращают ничего, а потом ещё и жалуются.";
            link.l1.go = "DTSG_NightIskat_3";
		break;
		
		case "DTSG_NightIskat_3":
			dialog.text = "Ха-ха-ха, ик, да, пусть поработает! Ты же знаешь, где жил наш славный к-капитан Флитвуд?";
            link.l1 = "Ещё бы, кто ж не знал Ричарда. Теперь банкир там живёт?";
            link.l1.go = "DTSG_NightIskat_4";
		break;
		
		case "DTSG_NightIskat_4":
			dialog.text = "Верно говоришь. Будешь там, дружище - с-скажи ему, что он уже совсем зазнался.";
            link.l1 = "Хе-хе, непременно так и сделаю. Бывай.";
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
			dialog.text = "Ха-ха-ха, в-видел ли я китайца?! Мы все его, ик, видели!";
			link.l1 = "А что смешного? Я сейчас не про бродячие цирки, если что. Про другого китайца, он свободно разгуливал по городу.";
			link.l1.go = "PZ_BasTerAlkash_2";
		break;
		
		case "PZ_BasTerAlkash_2":
			dialog.text = "Я сразу понял, я парень, ик, умный, знаешь ли. В-видел его, конечно. Аж протрезвел, но всё равно продолжил при этом его видеть... До сих пор не могу забыть!";
			link.l1 = "Ого! Как любопытно, продолжай. Выпьем ещё, наверняка сейчас пьёшь, чтобы забыть всё это. Расскажи, что видел-то.";
			link.l1.go = "PZ_BasTerAlkash_3";
		break;
		
		case "PZ_BasTerAlkash_3":
			dialog.text = "Не зря ты сказал про цирк! Как же он прыгал, вертелся, вращал сабелькой - никогда не видел, чтобы кто-то т-так необычно и страшно владел, ик, оружием.";
			link.l1 = "Это точно он. А с кем же он подрался, не припоминаешь?";
			link.l1.go = "PZ_BasTerAlkash_4";
		break;
		
		case "PZ_BasTerAlkash_4":
			dialog.text = "Дак понятное дело с кем - с-со стражей! Ходил везде, щурил свои узкие глаза. Хотя он и так их всё время щурит. Или нет? Как думаешь?";
			link.l1 = "Не знаю, дружище. Ты продолжай, продолжай. За лазутчика его приняли? За что стража-то накинулась?";
			link.l1.go = "PZ_BasTerAlkash_5";
		break;
		
		case "PZ_BasTerAlkash_5":
			dialog.text = "А к-кто ж его знает, ик. Пытались выяснить, что он у нас в городе забыл...";
			link.l1 = "И что же, арестовали китайца, получается? Или...";
			link.l1.go = "PZ_BasTerAlkash_6";
		break;
		
		case "PZ_BasTerAlkash_6":
			dialog.text = "Ха, да какое там! До сих пор п-поймать его не могут. Порубал стражников в городе и бежал в сельву. За ним посылают уже не первый отряд, и до сих пор никто не вернулся, ты, ик, представляешь?! Он превратил эту пещеру в настоящую крепость!..";
			link.l1 = "Да, дела. Отдохни, постарайся забыть. Я, пожалуй, пойду - голова кругом уже идёт.";
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
			dialog.text = "Самого его толком н-не видал, он больше у губернатора крутился, ик! А вот его команда тут закатила знатную пирушку!";
			link.l1 = "Вот как. Я тогда...";
			link.l1.go = "Sotta2";
		break;
		
		case "Sotta2":
			dialog.text = "П-погоди-погоди, ик, я ж даже не дорассказал! Все ж говорят, торговец, торговец. А его ребятишки отнюдь не торговая команда, скажу я тебе! Взгляды у них были, как будто, как будто... да как же это называется...";
			link.l1 = "Да я понял. Спасибо за компанию, дружище, не напрягайся.";
			link.l1.go = "exit_sit";
			
			npchar.questTemp.Sotta = true;
			pchar.questTemp.PZ_BelizAskCitizens = sti(pchar.questTemp.PZ_BelizAskCitizens) + 1;
			AddDialogExitQuest("PZ_LongwayBelizDialog");
		break;
		
		case "Lutter1":
			dialog.text = "А я к-как раз, ик, праздную! И кто сказал, что в одиночестве! С тобой, друг мой! А что касается Мэтта - это всё равно рано или поздно бы случилось.";
			link.l1 = "Почему ты так думаешь? Я слышал, что он был крайне удачливым пиратом, которому Фортуна не изменяла в течение нескольких лет!";
			link.l1.go = "Lutter2";
		break;
		
		case "Lutter2":
			dialog.text = "Хе-хе, не Ф-фортуной единой, ик! Он ведь был пиратом-одиночкой, не входил в Братство! А такие долго не живут. Говорят, что он когда-то был под крылышком у Левассера.";
			link.l1 = "Это точно, одиночки редко долго живут. Ну, празднуй, а мне уже пора, приятель.";
			link.l1.go = "exit_sit";
			
			npchar.questTemp.Lutter = true;
			pchar.questTemp.PZ_BelizAskCitizens = sti(pchar.questTemp.PZ_BelizAskCitizens) + 1;
			AddDialogExitQuest("PZ_LongwayBelizDialog");
		break;
		
		case "Sepp1":
			dialog.text = "Ик, да н-нет, не видел никогда такого. А кто он такой?";
			link.l1 = "Он капитан одного из самых быстрых кораблей на Архипелаге - брига 'Бантен'. Может, о нём хотя бы слышал?";
			link.l1.go = "Sepp2";
		break;
		
		case "Sepp2":
			pchar.questTemp.PZ.TortugaHabitueBlock = true;
			
			dialog.text = "Э, не, я, ко-кораблями не интересуюсь, приятель, ик! Может, ещё по чарочке?";
			link.l1 = "Без меня. Всё равно того, что хотел, я здесь не получил.";
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
