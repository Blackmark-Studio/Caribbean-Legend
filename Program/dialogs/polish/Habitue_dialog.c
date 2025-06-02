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
            dialog.text = "Wybór typu pijaka (beta)";
			link.l1 = "Pijak";
			link.l1.go = "Beta_test_alc";
            link.l2 = "Gracz w karty";
			link.l2.go = "Beta_test_card";
			link.l3 = "Gracz w kości";
			link.l3.go = "Beta_test_dice";
		break;
		
		case "Beta_test_alc":
            dialog.text = "Wybrano pijaka";
			link.l1 = "Kontynuuj";
			link.l1.go = "First time";
			npchar.quest.last_theme = 0;
		    npchar.quest.last_theme_game = 0;
		break;
		
		case "Beta_test_card":
            dialog.text = "Gracz w karty (30% szansy na natychmiastową niechęć)";
			link.l1 = "Kontynuuj";
			link.l1.go = "First time";
			npchar.quest.last_theme = 1;
		    npchar.quest.last_theme_game = 0;
		break;
		
		case "Beta_test_dice":
            dialog.text = "Gracz w kości (30% szans na natychmiastowe oburzenie)";
			link.l1 = "Kontynuuj";
			link.l1.go = "First time";
			npchar.quest.last_theme = 1;
		    npchar.quest.last_theme_game = 1;
		break;
		
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = LinkRandPhrase("Może i jestem pijany, ale nie jestem idiotą. Jeśli teraz się z tobą napije, następnego dnia złapią mnie żołnierze. Nie ma mowy!","Nie jestem wrogiem mojego własnego miasta. Nie będę z tobą pił!",""+GetSexPhrase("Kolego","Dziewczyno")+", lepiej opuść to miejsce, póki jeszcze możesz...");
				link.l1 = RandPhraseSimple("Cóż, jak sobie życzysz...","Heh, wiesz, nie muszę aż tak się upijać. To nie jest odpowiedni czas na to."); 
				link.l1.go = "exit";
				break;
			}
			if(CheckAttribute(pchar,"questTemp.HabitueSpeakDisable") && rand(1) == 0) // если дуэлянт то каждый второй посылает нафик
			{
				dialog.text = "Ha, Pani"+GetSexPhrase("e","enko")+", na pewno o tobie słyszałem, he-he. Ludzie w karczmach mówią, że jesteś kpiarzem i szermierzem. Naszego ludu nie tak łatwo da się przestraszyć, ale też nikt nie chce umierać za kufel rumu. Nawet siedzenie blisko ciebie budzi we mnie strach, więc lepiej odpuszczę.";
				link.l1 = LinkRandPhrase("Dobrze się stało, że się odsunąłeś!","Znikaj stąd, póki jestem jeszcze w dobrym nastroju...","Idź, idź! Spadaj, karmo dla ryb!");
				link.l1.go = "exit";
				link.l2 = "Czekaj, chce ci zadać pytanie....";
				link.l2.go = "talk_habitue_duel";
				break;
			}
			
            ok = CheckFreeSitFront(npchar);
            
            dialog.text = "Nie stój mi w świetle, nie widzę much w kubku!";
            link.l1 = "Nie stoję...";
		    link.l1.go = "exit";
		    if (!chrDisableReloadToLocation)
		    {
	            switch (npchar.quest.last_theme)
				{
					case "0": //пьяный.
						dialog.text = "Hep! O, "+GetSexPhrase("Kumplu, na pewno wyglądasz jak doświadczony wilk morski","Dziewczyno, wyglądasz mi na twardę dziewcze")+"! Być może, kupisz mi kubek rumu?";
						link.l1 = "Mogę sobie być wilkiem morskim, ale to wcale nie oznacza, że będe kupował alkohol dla hołoty...";
						link.l1.go = "exit";

						if (makeint(pchar.money) >= 100 && ok) // только старые острова окучены на сесть
						{
							link.l2 = "Chętnie dołączę do twojego towarzystwa.";
							link.l2.go = "talk_with_alchogol";
						}
						else
						{
	                        link.l2 = "A dlaczego tak?";
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
										Dialog.text = RandPhraseSimple("Gra w karty, może? Bardzo interesująca gra!","Proponuję zagrać w grę w karty. Co powiesz?");
										link.l1 = "A dlaczego nie? Pewnie, zagrajmy.";
										link.l1.go = "Cards_begin";
										link.l2 = "A jakie są zasady twojej gry?";
										link.l2.go = "Cards_Rule";
										link.l3 = "Nie teraz.";
										link.l3.go = "exit";
									}
									else
					    			{
										Dialog.text = "Nie, nie zagram już więcej z tobą w karty.";
						    			link.l1 = "Jak chcesz.";
						    			link.l1.go = "exit";
									}
			                        // Игра в карты boal 20/05/05 <--
		                        break;

								case 1:
								// кости
		    						// Игра в кости boal 13/07/05 -->
	                                if (CheckNPCQuestDate(npchar, "Dice_date_begin"))
									{
										Dialog.text = RandPhraseSimple("Gra w kości, może? Bardzo interesująca gra!","Proponuję rzucić kostkami. Co powiesz?");
										link.l1 = "A dlaczego nie? Jasne, zagrajmy.";
										link.l1.go = "Dice_begin";
										link.l2 = "A jakie są zasady twojej gry?";
										link.l2.go = "Dice_Rule";
										link.l3 = "Nie teraz.";
										link.l3.go = "exit";
									}
									else
					    			{
										Dialog.text = "Nie, nie będę już z tobą grać w kości.";
					    				link.l1 = "Jak chcesz.";
					    				link.l1.go = "exit";
									}
			                        // Игра в кости boal 13/07/05 <--
			                        //navy --> Дуэли
									if (CheckAttribute(NPchar, "Quest.DiceCheats") && sti(NPchar.Quest.DiceCheats) >= 1) 
									{
					    				link.l9 = RandSwear()+" Oszukiwałeś!!!";
					    				link.l9.go = "outraged";
									}
									//navy <--
			    				break;
	    					} 
						}
	        			else
	        			{
	                        dialog.text = RandPhraseSimple("Odejdź od mojego stołu! I to już!"," O? Co? Kto tam? Hep... Spływaj!");
	                        link.l1 = RandPhraseSimple("Picie pogrąża twoją grzeszną duszę! Ocknij się!","Sugeruje zmienić do mnie podejście.");
	        			    link.l1.go = "exit";
	        			    link.l2 = RandPhraseSimple("Uważaj na język, ty łajdaku! Bo cie zaraz nauczę dobrych manier.","Jeśli się zaraz nie utkasz, to ci trzepne w tę głowę, może to ci pomoże ochłonąć.");
	        	            link.l2.go = "tavern_keeper";
	        			}
					break;
				}
			}
			Diag.TempNode = "First time";
	    break;
	    
		case "talk_habitue_duel":
			dialog.text = "Nic ci nie powiem, Pan"+GetSexPhrase("ie","ienko")+"! I nie sądzę, aby ktokolwiek inny chciał z tobą rozmawiać, ponieważ zawsze oznacza to kłopoty. Ale wiesz, ludzie mają tendencję do krótkiej pamięci, więc za miesiąc czy dwa mogą zapomnieć o twojej przygodzie, jeśli im nie przypomnisz, oczywiście, he-he! Do widzenia, Pan"+GetSexPhrase("u","i")+". ";
			link.l1 = "W porządku...";
			link.l1.go = "exit";
		break;
		
	    // карты -->
	    case "Cards_Rule":
   			dialog.text = CARDS_RULE;
			link.l1 = "No to zaczynajmy...";
			link.l1.go = "Cards_begin";
			link.l3 = "Nie, to nie dla mnie...";
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

			Dialog.text = "Najpierw ustalmy zakład (wprowadź zakład).";
			link.l1 = "100";
			link.l1.edit = 1;
			link.l1.go = "Cards_Node_2";
			link.l3 = "Chyba muszę iść.";
			link.l3.go = "exit_sit";
		break;
		
		case "Cards_Node_2":
			iLa_Puesta = GetStrSmallRegister(dialogEditStrings[1]);
            if (!CheckCardsGameSmallRate())
		    {
                dialog.text = "Jesteś notorycznym oszustem. Nie będę z tobą grał.";
                link.l1 = "To wszystko kłamstwa! Ale rób jak chcesz.";
			    link.l1.go = "exit_sit";
			    break;
		    }
		    
			if (sti(PCHar.Money) < sti(iLa_Puesta)*3)
		    {
                dialog.text = "Widzę, że masz grosza przy duszy, "+GetSexPhrase("przyjacielu","kochanie")+". Wróć, kiedy się wzbogacisz.";
                link.l1 = "Dobrze.";
			    link.l1.go = "exit_sit";
			    break;
		    }
		
			if (sti(NPChar.Money) < sti(iLa_Puesta)*3)
		    {
                dialog.text = "Już straciłem wszystko, co miałem. Dziś dzień nie jest moim szczęśliwym.";
                link.l1 = "Dobrze.";
			    link.l1.go = "exit_sit";
			    break;
		    }
		else
		{
			if(sti(iLa_Puesta) < 50)
			{
				dialog.text = "Czy ty sobie ze mnie żartujesz, czy co?! Grając dla "+iLa_Puesta+" peso?! Grajmy za rozsądne stawki, albo odchodzę!";
				link.l1 = "Tak, masz rację. Musimy trochę podnieść stawkę.";
				link.l1.go = "Cards_begin_2";
				link.l2 = "Zmieniłem zdanie, nie gram.";
				link.l2.go = "exit_sit";
				break;
			}
			
			if(sti(iLa_Puesta) > 1000)
			{
				dialog.text = "Grać za tak olbrzymią sumę? Nie, podziękuję, chyba że zmienimy zakład.";
				link.l1 = "Tak, masz rację. Musimy trochę obniżyć zakład.";
				link.l1.go = "Cards_begin_2";
				link.l2 = "Właściwie, to odechciało mi się grać.";
				link.l2.go = "exit_sit";
				break;
			}
			dialog.text = "Dobrze, zagrajmy za "+iLa_Puesta+" peso.";
			link.l1 = "Rozdaj karty!";
			link.l1.go = "Cards_begin_go";
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
			pchar.GenQuest.Cards.iRate     = sti(iLa_Puesta);
            pchar.GenQuest.Cards.SitType   = true;
		}
		break;
		
		case "Cards_begin_2":
			dialog.text = "Więc jaki jest zakład? (Wprowadź zakład)";
			link.l1 = "50";
			link.l1.edit = 1;
			link.l1.go = "Cards_Node_2";
			link.l2 = "Myslę, że jednak nie będę grał...";
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
			link.l1 = "No cóż, zaczynajmy, w takim razie...";
			link.l1.go = "Dice_begin";
			link.l3 = "Nie, to nie dla mnie...";
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
			Dialog.text = "Określmy zakład (wprowadź zakład).";
			link.l1 = "50";
			link.l1.edit = 1;
			link.l1.go = "Dice_Node_2";
			link.l3 = "Chyba muszę już iść.";
			link.l3.go = "exit_sit";
		break;

		case "Dice_Node_2":
			iLa_Puesta = GetStrSmallRegister(dialogEditStrings[1]);
            if (!CheckDiceGameSmallRate())
		    {
				dialog.text = "Jesteś notorycznym oszustem. Nie będę z tobą grać w kości.";
                link.l1 = "To wszystko kłamstwa! A z resztą kij z tym.";
			    link.l1.go = "exit_sit";
			    break;
		    }

			if (sti(pchar.Money) < sti(iLa_Puesta)*6)
		    {
                dialog.text = "Widzę, że nie masz żadnych pieniędzy, "+GetSexPhrase("przyjacielu","kochanie")+". Wróć, kiedy się wzbogacisz.";
                link.l1 = "Dobrze.";
			    link.l1.go = "exit_sit";
			    break;
		    }
			
			if (sti(npchar.Money) < sti(iLa_Puesta)*6)
		    {
                dialog.text = "Już straciłem wszystko, co miałem. Dziś nie mój dzień.";
                link.l1 = "Dobrze.";
			    link.l1.go = "exit_sit";
			    break;
		    }
		else
		{
			if(sti(iLa_Puesta) < 50)
			{
				dialog.text = "Czy ty sobie ze mnie żartujesz, czy co?! Grając za "+iLa_Puesta+" peso?! Gramy za sensowne stawki, albo się wycofuję!";
				link.l1 = "Tak, masz rację. Musimy trochę podnieść stawkę.";
				link.l1.go = "Dice_begin_2";
				link.l2 = "Zmieniłem zdanie, nie gram.";
				link.l2.go = "exit_sit";
				break;
			}
			
			if(sti(iLa_Puesta) > 1000)
			{
				dialog.text = "Grać w kości o takie ogromne pieniądze? Nie, podziękuję, chyba że zmienimy zakład.";
				link.l1 = "Tak, masz rację. Musimy trochę obniżyć stawkę.";
				link.l1.go = "Dice_begin_2";
				link.l2 = "Właściwie, zdecydowałem się w ogóle nie grać.";
				link.l2.go = "exit_sit";
				break;
			}
			dialog.text = "Dobrze, zagrajmy za "+iLa_Puesta+" peso.";
			link.l1 = "Ruszajmy!";
			link.l1.go = "Dice_begin_go";
			pchar.GenQuest.Dice.npcharIdx = npchar.index;
			pchar.GenQuest.Dice.iRate     = sti(iLa_Puesta);
            pchar.GenQuest.Dice.SitType   = true;
		}
		break;
		
		case "Dice_begin_2":
			dialog.text = "Więc jaki jest zakład? (Wprowadź zakład)";
			link.l1 = "50";
			link.l1.edit = 1;
			link.l1.go = "Dice_Node_2";
			link.l2 = "Myślę, że jednak nie zagram...";
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
			dialog.text = "Cóż, h-hep! Dobrze się sprawy mają. Hep! Ty po prostu tego nie widzisz. He-ep! Ten rum jest dobry. Jamajski czarny rum. hep! Prosze, kładź i lej!";
			link.l1 = "Dobrze, czemu nie.";
			link.l1.go = "talk_with_alchogol_song_2";
			link.l2 = "Przykro mi przyjacielu, muszę iść.";
			link.l2.go = "exit";
		break;
		
		case "talk_with_alchogol_song_2":
			dialog.text = "Kufle i twarze przychodzą i odchodzą... Hep... Aż do upadku. Piję cały czas... Hep! Gdzie jest gorzałka... I jaki jest rym...";
			link.l1 = "Alkohol jest tu, i dziewczyny też, wszystkie chcą korsarza, tylko rum jest mój też.";
			link.l1.go = "talk_with_alchogol_song_3";
			link.l2 = "Nie mam na to czasu.";
			link.l2.go = "exit";
		break;
		
		case "talk_with_alchogol_song_3":
			dialog.text = "Gdy jesteś smutny, życia cienka nić, przyjdź, a my będziemy pić! Wszystko dobrze skończy się w przybytku tym, jestem twym przyjacielem, a ty mym!";
			link.l1 = "Świetnie mieć do picia dobrego człeka, kiedy ciebie nie ma, on zaczeka, z przyjacielem nie ma nienawiści, ale kiedy rum się skończy, zalążek rodzi się zawiści. Więc pijmy, kolego, zanim pójdę i spóźnię się...";
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
			dialog.text = LinkRandPhrase("Hep! Teraz jest lepiej! Naprawdę lepiej! Więc? Kupisz mi trochę rumu, czy jak?","Siadajże, "+GetAddress_Form(npchar)+", walnijmy kubek dobrego, starego jamajskiego rumu. To nigdy nie szkodzi zdrowiu. A jeśli jesteś zainteresowany tym, co się dzieje - nigdy nie znajdziesz lepszego miejsca niż ta karczma, zapewniam cię. Trochę pieniędzy, kilka kubków przyzwoitego rumu - a dowiesz się wszystkiego, co chciałeś wiedzieć, a nawet więcej, zaufaj staremu bywalcowi...","Heh, proszę, usiądź, "+GetSexPhrase("mój dobry przyjacielu","Panno")+", napijmy się razem... Czemu nie napić się w dobrej kompanii? Możesz usłyszeć wiele interesujących rzeczy, jeśli masz cierpliwość i pijesz powoli, małymi łykami... Są kapitanowie, którzy chwalą się swoimi przygodami, wielu innych wygaduje ważne rzeczy, kiedy już nie kontrolują siebie... Wiele osób spędza tam swój czas, i wielu ma coś do powiedzenia, uwierz mi, "+GetSexPhrase("mój dobry przyjacielu","Panno")+".");
			link.l1 = "A dlaczego nie! Karczmarzu! Rum, dla nas dwojga!";
			link.l1.go = "sit_2";
		break;

		// Церковный генератор. Квест №2 -->
		case "Alcogol_GenQuest_Church_2_1":
			dialog.text = "Jasne! Słyszałeś o tym pewnie... bandyci nawet plądrują kościoły!";
				link.l1 = "Cóż, to brzmi jak robota piratów, bo kogoż innego...";
				link.l1.go = "Alcogol_GenQuest_Church_2_2";
				DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.AskPeople");
				DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.AskBarmen");
				DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.AskAlcash");
			break;
			
		case "Alcogol_GenQuest_Church_2_2":
			dialog.text = "Jakich piratów? To robota zwykłych szczurów lądowych, i to na pewno tych cholernych miejscowych... Gdyby byli obcymi, nie wiedzieliby, kiedy skarbonka kościelna jest pełna. I w ogóle nie wpadliby w ten bałagan.";
				link.l1 = "Odwagi im nie brakuje, na pewno. Tak dzielnie otworzyli słaby drzwiowy zasiek...";
				link.l1.go = "Alcogol_GenQuest_Church_2_3";
			break;
			
		case "Alcogol_GenQuest_Church_2_3":
			dialog.text = "Ano. I mądrzy i odważni. Jak parafia mogła aż tak dać się pokusić?";
				link.l1 = "Prawda. Cała parafia oszczędzała pieniądze na ofiarę dla kościoła, a teraz ci spryciarze zrobili na tym nie małą fortunę. Na pewno zostaną złapani. Cały świat ich teraz szuka.";
				link.l1.go = "Alcogol_GenQuest_Church_2_4";
			break;
			
		case "Alcogol_GenQuest_Church_2_4":
			dialog.text = "Ledwo. Kto będzie tego szukał? Po prostu obrabowali kościół i opuścili miasto, tam gdzie wiatr ich poniósł. Dżungla jest duża, bardzo duża, szukałbyś ich tam do dnia sądu ostatecznego. A po kilku miesiącach ludzie po prostu zapomną o tym wszystkim, zapamiętaj moje słowa!";
				link.l1 = "Nie sądzę. Takie rzeczy nie mogą być wybaczone.";
				link.l1.go = "Alcogol_GenQuest_Church_2_5";
			break;
			
		case "Alcogol_GenQuest_Church_2_5":
			dialog.text = "Pamięć człowieka jest jak przeciekająca szalupa. Ludzie zapomną i wybaczą. Ale Bóg?! On widzi wszystko. Tego powinieneś się bać. Mówię ci, dziesięć lat temu coś strasznego spotkało mojego starego kumpla. On też nie szanował Stwórcy i przez to prawie trafił prosto w objęcia morskiego diabła...";
				link.l1 = "Przykro mi przyjacielu, muszę już iść. Porozmawiamy o twoim kumplu innym razem. Do zobaczenia.";
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
				dialog.text = "Ach, Francois! Oczywiście, pamiętam tego gościa... Nie, nie wiem. Ale wiesz, możesz zapytać naszą kelnerkę o niego. Przez cały czas, kiedy tu mieszkał, spędzała z nim każdą noc. Suka z niej jest, to na pewno. Może coś jej powiedział.";
				link.l1 = "Dzięki za radę, kumplu. Pójdę z nią porozmawiać.";
				link.l1.go = "exit_sit";
				pchar.questTemp.Slavetrader = "FindRatJamaica_W";
			break;
			
			case "EscapeSlave_Villemstad_H1":
				dialog.text = "Tak, na otwartym morzu czasami mogą zdarzyć się bardzo dziwne rzeczy. Podczas mojego ostatniego rejsu widziałem coś naprawdę...";
				link.l1 = "Proszę, opowiedz mi, tylko nie przesadzaj zbytnio. W międzyczasie przyniosę ci więcej rumu.";
				link.l1.go = "EscapeSlave_Villemstad_H2";
			break;
			
			case "EscapeSlave_Villemstad_H2":
				dialog.text = "Przysięgam na Boga, Mości "+GetSexPhrase("Panie","Pani")+" - Widziałem to na własne oczy... Statek płynął, ale zamiast marynarzy były tam jakieś gigantyczne małpy... albo makaki... a może jednak małpy?";
				link.l1 = "Co?! Powiedz mi, przyjacielu, czy ty pijesz również na warcie?";
				link.l1.go = "EscapeSlave_Villemstad_H3";
			break;
			
			case "EscapeSlave_Villemstad_H3":
				dialog.text = "Przywal mi na oślep, jeśli kłamię! Czy nigdy nie słyszałeś o małpim krewetku? O kurwa, krewetku ha-ha! ... o małpim statku.";
				link.l1 = "Jakim małpim statku?";
				link.l1.go = "EscapeSlave_Villemstad_H4";
			break;
			
			case "EscapeSlave_Villemstad_H4":
				dialog.text = "O-ho, mówię, że widziałem to na własne oczy. Była burza. Nic nie było widać, a potem statek pojawił się znikąd. Podarte żagle. Miała zepsuty fok jak i grot, a pota i cholera, miała wszystko zepsute! A mimo to pędziła pod wiatr! A na jej pokładzie były małpy... tak ich było dużo jak... kolonia fok! A czysty goryl stał przy sterze! Dziewięć stóp, czerwona koszula i zęby rekina zamiast krzyża na piersi... Oczy są czerwone, kły błyskają, zobaczyło nas i krzyknęło coś...";
				link.l1 = "Kłamiesz jak z nut, przyjacielu. Wiesz, kiedy jesteś pijany, widzisz rzeczy. Zaraz mi powiesz, że to był Latający Holender.";
				link.l1.go = "EscapeSlave_Villemstad_H5";
			break;
			
			case "EscapeSlave_Villemstad_H5":
				dialog.text = "Nie, to nie był Holender. Mówię ci prawdę! To była barka, a na rufie miała inskrypcje - "+pchar.questTemp.Slavetrader.ShipName+".";
				link.l1 = "Cholera! Wydaje mi się, że wiem, o jakich 'małpach' mówiłeś. Rzeczywiście, rum może rozwiązać języki - wystarczy tylko dobrze słuchać...";
				link.l1.go = "EscapeSlave_Villemstad_H6";
			break;
			
			case "EscapeSlave_Villemstad_H6":
				dialog.text = "Widzisz - mówiłem Ci! I nie wierzyłeś mi!.. Dobrze, walnijmy jeszcze po ostatnim kubku, i będe gotów do drogi.";
				link.l1 = "Dobrze, dzięki za ciekawą historię. Muszę iść. Powodzenia, kumplu.";
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
			dialog.text = "Nie, kapitanie. Życie marynarza nie jest dla mnie. Wiesz, ja też kiedyś miałem swój statek, ale... pewnego dnia dopadło mnie pasmo niepowodzeń.";
			link.l1 = "Słuchaj - zauważyłem w porcie niezwykły statek - 'Meifeng' to jej nazwa. Nigdy wcześniej nie widziałem takiego statku. Kto jest jej właścicielem? Może jest na sprzedaż? Chciałbym się jej bliżej przyjrzeć.";
			link.l1.go = "Lucas_Tavern_1";
		break;
		
		case "Lucas_Tavern_1":
			dialog.text = "Ha! Ledwo, kapitanie. Nie sądzę, żeby ten Chińczyk sprzedał tobie czy komukolwiek innemu swój statek.";
			link.l1 = "Chińczyk? Na Curacao są Chińczycy? A nawet kapitan własnego statku?";
			link.l1.go = "Lucas_Tavern_2";
		break;
		
		case "Lucas_Tavern_2":
			dialog.text = "Są, jak widzisz. Ale to nie jest jego statek, właściwie - należy do Kompanii Handlowej. Mówią, że Pan Rodenburg, wice dyrektor i obecny gubernator, go posiada.";
			link.l1 = "Czyli, Matthias Beck przeszedł na emeryturę?";
			link.l1.go = "Lucas_Tavern_3";
		break;
		
		case "Lucas_Tavern_3":
			dialog.text = "Ha! Panie, naprawdę powinieneś odwiedzać ląd dużo częściej - albo przynajmniej interesować się wiadomościami. Matthias Beck został odsunięty od władzy i wsadzony za kraty, dopóki wszystkie okoliczności nie zostaną wyjaśnione.";
			link.l1 = "Poważnie!? Faktycznie, spędzam zbyt wiele czasu na morzu. A kiedy to się stało?";
			link.l1.go = "Lucas_Tavern_4";
		break;
		
		case "Lucas_Tavern_4":
			dialog.text = "Właściwie, to zaledwie kilka dni temu. Kurierska brygantyna przypłynęła do portu. Była w nie najlepszym stanie, wyraźnie brała udział w zaciekłej walce. Kapitan poszedł prosto do mynheer Rodenburga ze swoim raportem, a po zaledwie kilku godzinach Matthias Beck został aresztowany przez mynheer Rodenburga i komendanta pod zarzutem współpracy z angielskim wywiadem.";
			link.l1 = "Straszne rzeczy opowiadasz. Jak to możliwe, że gubernator Curacao mógłby się okazać angielskim szpiegiem?";
			link.l1.go = "Lucas_Tavern_5";
		break;
		
		case "Lucas_Tavern_5":
			dialog.text = "Szczerze mówiąc, też w to ledwo wierzę. Słyszałem, że wkrótce dyrektor Kompanii, sam Peter Stuyvesant, przybędzie tutaj. Podobno osobiście przeprowadzi śledztwo.";
			link.l1 = "Wtedy masz rację. Może być ryzykowne przeszkadzać panu Rodenburgowi o tej porze.";
			link.l1.go = "Lucas_Tavern_6";
		break;
		
		case "Lucas_Tavern_6":
			dialog.text = "Dobrze myślisz, kapitanie! Tym bardziej, że 'Meifeng' jest obecnie załadowywany. Właśnie wrócił z podróży na południowym wybrzeżu kontynentu, a wkrótce znów wypłynie. I powiem Ci, dzieją się tam dziwne rzeczy. Holenderscy marynarze i strażnicy Kompanii zostali zwolnieni z obowiązków, a składa się nowa załoga. I przysięgam na wszystkie kieliszki rumu, które wypiłem w moim życiu, ci nowi ochotnicy to coś zupełnie innego, sami piraci, bandyci i mordercy!";
			link.l1 = "Cud, rzeczywiście! Szkoda! Taki ładny statek... Cóż, los postanowił inaczej... Dziękuję za ciekawą historię i wiadomości! Miło było z tobą rozmawiać!";
			link.l1.go = "Lucas_Tavern_7";
		break;
		
		case "Lucas_Tavern_7":
			dialog.text = "Cóż, dzięki za towarzystwo i rum, Kapitanie! Wpadnij kiedyś jeszcze!";
			link.l1 = "Jasne, że wpadne!";
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
				dialog.text = "Ha! "+pchar.GenQuest.FindFugitive.Name+"? Wiem, wiem... Ten twój kolega jest strasznie nietowarzyski. Samotny wilk, można powiedzieć. Pływa na tej swojej szalupie wzdłuż wybrzeża wyspy od świtu do zmierzchu. Ludzie myślą, że jest rybakiem, ale tak naprawdę łowi perły... He-he! Wiem to na pewno, do diabła!";
				link.l1 = "Heh! Więc... możesz mi powiedzieć, gdzie go znajdę?";
				link.l1.go = "FindFugitiveHb_1";
			}
			else
			{
				dialog.text = ""+pchar.GenQuest.FindFugitive.Name+"? Nie, przysięgam, że nigdy o nim nie słyszałem... Ale ty - Hep! Możesz zapytać naszego barmana - on na pewno wie!";
				link.l1 = "Hmm... Dobrze, zapytam się. Cóż, kumplu, dzięki za towarzystwo. Do zobaczenia!";
				link.l1.go = "exit_sit";
			}
		break;
		
		case "FindFugitiveHb_1":
			dialog.text = "Oczywiście, że mogę! Każdego poranka można go znaleźć na brzegu, przy "+XI_ConvertString(pchar.GenQuest.FindFugitive.Shore+"Gen")+". Przyjdź jak najwcześniej, inaczej odpłynie i będziesz musiał czekać do następnego poranka.";
			link.l1 = "Dzięki! Bardzo mi pomogłeś, przyjacielu! Do zobaczenia!";
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
			dialog.text = "Kręcił się po naszej stoczni, pytając stoczniowców o to i owo. I to zagrało na niego okrutny numer. Niektórzy ludzie zawiadomili komendanta o podejrzanych osobach kręcących się po mieście, więc go zatrzymał, a potem okazało się, że wcale nie jest kupcem.";
			link.l1 = "Rozumiem, że miał zamiar ukraść jakiś tajny projekt twojego stoczniowca?";
			link.l1.go = "trial_spy_1";
		break;
		
		case "trial_spy_1":
			dialog.text = "Kto wie? Ale jestem całkiem pewien, że przede wszystkim zainteresował go galeon 'Alacantara'! Hep! Mogę przysiąc! Ten statek jest wyposażany przez samego gubernatora, więc zakładam, że ten łotr próbował coś o nim wywąchać.";
			link.l1 = "Ha! To całkiem prawdopodobne. Na pewno gubernator załaduje ją czymś wartościowym...";
			link.l1.go = "trial_spy_2";
		break;
		
		case "trial_spy_2":
			dialog.text = "To jest oczywiste! To powinno być coś naprawdę wartego uwagi, mówię ci! O, a ludzie mówili, że rybacy zobaczyli obcy wojskowy okręt na tych wodach... najprawdopodobniej fregata. Może stąd przyszedł ten szpieg?";
			link.l1 = "Tak, może być... Dobrze, kolego, dzięki za towarzystwo, ale muszę iść!";
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
				dialog.text = "Za twoje zdrowie i twoją hojność!";
				link.l1 = "Kolego, czy widziałeś tutaj jakiegoś Chińczyka?";
				link.l1.go = "PZ_BasTerAlkash_1";
				break;
			}
			// <== Квест "Путеводная звезда" - Sinistra
			
			dialog.text = LinkRandPhrase("Jesteś "+GetSexPhrase("prawdziwym przyjacielem","świetną dziewczyną")+"! Miło cię spotkać! Na zdrowie!","Hep! To świetny rum! Hep... Na zdrowie!","Do twojego zdrowia i do twojej hojności!");
			link.l1 = "Heh, to naprawdę mocny rum. Dobrze, muszę już iść. Baw się dobrze!";
			link.l1.go = "exit_sit";
			if (makeint(pchar.money) >=2)
			{
				link.l2 = "Jeszcze jeden kubek, nie masz nic przeciwko?";
				link.l2.go = "sit_3";
			}

			link.l4 = LinkRandPhrase("Czuje się, jakbym spędził wieczność na morzu. Są jakieś nowiny?","Co ludzie mówią? Oczywiście, postawię ci drinka.","Powiedz mi, kumplu, jakie historie są teraz popularne w karczmach?");
			link.l4.go = "rumours_habitue";
		break;

		case "sit_3":
			int iSituation;
			if(IsEquipCharacterByArtefact(pchar, "totem_01")) iSituation = makeint(rand(3));
			else iSituation = makeint(rand(5));
			switch (iSituation)
			{
				case 0:
					dialog.text = "Oh! Świetny pomysł!";
					link.l1 = "Barmanie! Więcej rumu!";
					link.l1.go = "sit_2";
				break;

				case 1:
					dialog.text = "Za ciebie! O, cholera! Kto to jest?";
					link.l1 = "He? Co? Gdzie? Chyba halucynuję.";
					link.l1.go = "sit_2";// to_do "sit_case_5_exit";
				break;
				
                case 2:
	         		dialog.text = "Więc pijmy! Może jeszcze jedno?";
					link.l1 = "Proszę bardzo!";
					link.l1.go = "sit_2";
                break;				
				
				case 3:
					if(rand(1) == 0)
					{
						dialog.text = RandPhraseSimple("Hej, ty, "+GetAddress_Form(NPChar)+", na pewno myślisz, że wszyscy cię podziwiają, co? Cóż, jeśli pytasz mnie, jesteś po prostu zwykłym bandytą!.. I mordercą! 'Szlachetny pirat'! Ha! Bandyta to bandyta... Hep... Na lądzie czy na morzu..","Hep! "+GetSexPhrase("Łaj... Łajdaku","Ła... chudro")+"! Chcesz, żebym pił aż padnę - hep - a potem ukradniesz mi wszystkie pieniądze!");
						link.l1 = "Widzę, że już sporo wypiłeś... Idź się przespać... A ja sobie pójde...";
						link.l1.go = "exit_sit";						
						link.l2 = "Nie podoba mi się twój ton, kolego. Trzymaj język za zębami, dobrze?";
						link.l2.go = "sit_case_2_enemy";
						link.l3 = "Kogo ty właśnie nazwałeś bandytą, ty szczurze lądowy?! Zobaczymy co powiesz, mając dziure w brzuchu!";
						link.l3.go = "sit_case_2_enemy2";
					link.l4 = "Uspokój się! Czy zapomniałeś? Jestem twoim jedynym prawdziwym przyjacielem!";
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
							dialog.text = RandPhraseSimple("Dlaczego na mnie patrzysz? Czekasz, aż zemdleję - hep - a potem ukradniesz mi wszystkie pieniądze! Skąd się wzięła cała ta hołota?! Hep... W tej karczmie nie ma już miejsca dla porządnych ludzi?","Czy szanujesz mnie?.. Tak, ty! Czy szanujesz mnie?! Uważaj na siebie... Nie jestem tym, z kim można igrać... Jeden cios między oczy... I jesteś już jak martwy...");
							link.l1 = "Kumplu, jesteś pijany jak świnia. Idź do domu i pójdź spać... Ja też muszę iść...";	
							link.l1.go = "exit_sit";
							link.l2 = "Hamuj się, kumplu. Pamiętaj, z kim rozmawiasz.";
							link.l2.go = "sit_case_2_enemy1";
							link.l3 = "Co ty właśnie powiedziałeś?! Nauczę cię lekcji!";
							link.l3.go = "sit_case_2_enemy2";
							link.l4 = "Uspokój się! Czy zapomniałeś o mnie? Jestem twoim jedynym prawdziwym przyjacielem!";
							link.l4.go = "sit_case_2_friend";	
						//}
					}
				break;

				case 4:
					dialog.text = "Słuchaj! Jesteś dobrym człowiekiem! Być może, pomożesz mi... z pewną sprawą?";
					link.l1 = "Nie, myślę, że muszę teraz iść.";
					link.l1.go = "exit_sit";
					link.l2 = "Pewnie! Hik! Jesteśmy przyjaciółmi... prawda? Hep!";
					link.l2.go = "sit_case_3";
				break;

				case 5:
					if (GetSummonSkillFromName(pchar, SKILL_SNEAK) > rand(110) )
					{
						dialog.text = "...A potem złapałem jego szablę za ostrze...";
						link.l1 = "...a potem ona powiedziała...";
						link.l1.go = "sit_2";
					}
					else
					{
						dialog.text = "...A potem złapałem jego szablę za o-ostrze...";
						link.l1 = "...hep! ...a potem powiedziała...";
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
			dialog.text = "Ch-chodzi o to, że jeden z żołnierzy mnie obraził. T-tak jest!";
			link.l1 = "Żołnierz? N-Nie, myślę, że podziękuję.";
			link.l1.go = "exit_sit";
			link.l2 = "Uspokój się! Czy zapomniałeś o mnie? Jestem twoim jedynym prawdziwym przyjacielem!";
			link.l2.go = "sit_2";
		break;

		case "sit_case_2_friend":
			dialog.snd = "Voice\HADI\HADI038";
			dialog.text = "Ty? Jakim jesteś przyjacielem? N-nie! Ty... ty chcesz mnie zabić! T-Tak jest!";
			link.l1 = "Cóż, na pewno już wystarczająco dużo wypiłeś. Do widzenia.";
			link.l1.go = "exit_sit";
			link.l2 = "Co? Udowodnię ci, że nie zamierzam cię zabić! Ja... Ja odetnę ci rękę!... Bez niej nie można cię zabić!... Hep!";
			link.l2.go = "sit_case_2_friend_2";
		break;

		case "sit_case_2_friend_2":
			dialog.snd = "Voice\HADI\HADI039";
			dialog.text = "Aaaah! Zabierzcie "+GetSexPhrase("go","ją")+",odejdź ode mnie!";
			link.l1 = "Uspokój się... hep... Nie będzie bolało!... To boli mniej od golenia!";
			link.l1.go = "tavern_keeper";
		break;

		case "sit_case_2_enemy":
			dialog.snd = "Voice\HADI\HADI040";
			dialog.text = "Nie próbuj mnie zastraszyć! Hep! Nie jestem tak łatwo przestraszony!.. A ty - powinieneś wisieć na szubienicy... Ze wszystkimi twoimi - hep! Możesz nafuszyć swoje pióra, jak chcesz - ale nadal śmierdzisz zgniłą rybą! I nie zamierzam pilnować języka, kiedy - hep! - rozmawiam z twoim rodzajem! Wszyscy mnie obrzydzacie!";
			link.l1 = "Argh, dlaczego w ogóle rozmawiam z takim pijakiem... Chyba pójdę zaczerpnąć trochę świeżego powietrza...";
			link.l1.go = "exit_sit1";
			link.l2 = "Jesteś zbyt śmiały, kumplu. Wsadzę twoje słowa z powrotem do gardła!";
			link.l2.go = "sit_case_2_enemy3";
		break;

		case "sit_case_2_enemy1":		
			dialog.snd = "Voice\HADI\HADI040";
			dialog.text = "Co-o?! Uduszę cię własnymi rękami! Hep... Nikt mi - hep! - dotąd nie uciekł!";
			link.l1 = "Czyż nie jesteś pijanym świńskim ryjem? Zepsuć tak piękny wieczór... Dobrze, idź łapać swoje karaluchy - a ja stąd spadam.";
			link.l1.go = "exit_sit1";
			link.l2 = RandSwear()+"Widzę, że nie zamierzasz się uspokoić. No cóż, w takim razie pora na lekcję dobrych manier.";
			link.l2.go = "sit_case_2_enemy3";
		break;
		
		case "sit_case_2_enemy2":	
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			if(rand(1) == 0)
			{
				dialog.text = LinkRandPhrase("Podejdź bliżej, łotrzyku! Dostaniesz to, na co zasługujesz!",RandSwear()+"Dam ci to, na co zasługujesz!","Ha! Dobrze, wilku morski - zobaczmy, jak ci pójdzie na suchym lądzie!");
				link.l1 = RandPhraseSimple(RandPhraseSimple("Przysięgam, że tego pożałujesz!","Obetnę twój brudny język do uszu!"),RandPhraseSimple("Przepruję cię jak świnię, od dupy do tej dziury, którą niektórzy nazywają ustami!","Przysięgam, że cię zamknę!"));
				link.l1.go = "fight_right_now";
			}
			else
			{
				dialog.text = "Hej, chłopaki! Posprzątajmy to śmiecie z naszego miasta!";
				link.l1 = RandPhraseSimple(RandSwear()+"Odmówcie swoje modlitwy, łajdaki!","O, więc nie jesteś sam?! No, dobrze dla ciebie - będziesz miał towarzystwo w piekle!");
				link.l1.go = "fight_right_now_1";
			}
		break;
		
		case "sit_case_2_enemy3":	
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
			if(rand(1) == 0)
			{
				dialog.text = LinkRandPhrase("Podejdź bliżej, łobuzie! Dostaniesz to, na co zasługujesz!",RandSwear()+"Dam ci to, na co zasługujesz!","Ha! Dobrze, wilku morski - zobaczymy, jak ci pójdzie na suchym lądzie!");
				link.l1 = RandPhraseSimple(RandPhraseSimple("Przysięgam, że tego pożałujesz!","Przytnę twój brudny język do uszu!"),RandPhraseSimple("Przepruję cię jak świnię, od twojego tyłka do tej dziury pełnej gówna, którą niektórzy nazywają ustami!","Przysięgam, dopilnuje, że zamkniesz się na dobre!"));
				link.l1.go = "fight_right_now";
			}
			else
			{
				dialog.text = "Hej, chłopaki! Posprzątajmy to śmiecie z naszego miasta!";
				link.l1 = RandPhraseSimple(RandSwear()+"Odmówcie swoje modlitwy, łajdaki!","O, więc nie jesteś sam?! No cóż, dobrze dla ciebie - będziesz miał towarzystwo w piekle!");
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
			dialog.text = "Hej, czegoś tu nie rozumiem! Jak tylko skręciłem za róg, jakiś nowy żółtodziób wylądował na moim miejscu. Wynoś się stąd!";
			link.l1 = "Zawsze jest tak samo: dopiero co usiądę do stołu, a okazuje się, że już zajęty... Trzymaj swoje miejsce, miałem zamiar i tak zaraz wyjść.";
			link.l1.go = "bad_habitue1";
			link.l2 = "Jeszcze jedno takie zdanie z twojego brudnego pyska i to będzie ostatnia rzecz, którą powiesz w swoim życiu, rozumiesz?";
			link.l2.go = "bad_habitue2";
			link.l3 = "Nie wiem, czy to naprawdę twoje miejsce, ale nie pozwolę ci tak do mnie mówić. Uważaj na swoje słowa.";
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
				dialog.text = LinkRandPhrase("No, choć, łobuzie! Zaraz się najeście!",RandSwear()+"Teraz cię porządnie obnażę!","Ha! No dalej, marynarzu - pokaż, co potrafisz na lądzie!");
				link.l1 = RandPhraseSimple(RandPhraseSimple("Przysięgam, że tego pożałujesz!","Obetnę twój jebany język!"),RandPhraseSimple("Przepruję cię jak świnię, od tyłka do tej dziury, którą niektórzy nazywają gębą!","Przysięgam, że zmuszę cię do zamknięcia się!"));
				link.l1.go = "fight_right_now";
			}
			else
			{
				dialog.text = "Chodźcie chłopaki! Wywalmy tę łuskę z naszego miasta!";
				link.l1 = RandPhraseSimple(RandSwear()+"Módlcie się o litość, wy bękarty!","O, nie jesteś sam! Cóż, będziesz miał towarzystwo w piekle!");
				link.l1.go = "fight_right_now_1";
			}
		break;
		
		case "bad_habitue3":
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			if(rand(1) == 0)
			{
				dialog.text = LinkRandPhrase("No dalej, łobuzy! Zaraz dostaniecie swoje!",RandSwear()+"Teraz cię porządnie rozbiorę!","Ha! No dawaj, marynarzu - zobaczymy co potrafisz na lądzie!");
				link.l1 = RandPhraseSimple(RandPhraseSimple("Przysięgam, że tego pożałujesz!","Odetnę ci język, kurwa!"),RandPhraseSimple("Podetnę cię jak świnie, od tyłka do tej gnijącej dziury, którą niektórzy nazywają ustami!","Przysięgam, że zmuszę cię do zamknięcia się!"));
				link.l1.go = "fight_right_now";
			}
			else
			{
				dialog.text = "Chodźcie chłopaki! Wyrzućmy tę łuszczynę z naszego miasta!";
				link.l1 = RandPhraseSimple(RandSwear()+"Módlcie się, wy łajdaki!","O, nie jesteś sam! No cóż, będziesz miał towarzystwo w piekle!");
				link.l1.go = "fight_right_now_1";
			}
		break;
		
		//--> Sinistra Длинные тени старых грехов
		case "DTSG_NightIskat":
			dialog.text = "O-oczywiście, wszyscy się znamy! Dlaczego pytasz?";
            link.l1 = "Chciałem odwiedzić lichwiarza i dowiedziałem się, że sprzedał swój stary dom. Czy wiesz, gdzie teraz mieszka?";
            link.l1.go = "DTSG_NightIskat_2";
		break;
		
		case "DTSG_NightIskat_2":
			dialog.text = "Dlaczego potrzebujesz go o tej porze, hic? Po prostu odwiedź bank rano!";
            link.l1 = "Pilnie potrzebuję pieniędzy. Niechaj nareszcie sakiewka zapracuje! Ci z ich rodzaju zawsze nazywają nas darmozjadami, którzy tylko żebrzą, narzekają i nigdy nie oddają tego, co jesteśmy winni.";
            link.l1.go = "DTSG_NightIskat_3";
		break;
		
		case "DTSG_NightIskat_3":
			dialog.text = "Ha-ha-ha, hep, tak, niech on pracuje! Wiesz, gdzie mieszkał nasz wspaniały kapitan Fleetwood?";
            link.l1 = "Oczywiście, kto nie znał Richarda. Teraz mieszka tam bankier?";
            link.l1.go = "DTSG_NightIskat_4";
		break;
		
		case "DTSG_NightIskat_4":
			dialog.text = "Masz rację. Kiedy tam będziesz, przyjacielu - powiedz mu, że stał się zbyt zarozumiały.";
            link.l1 = "Heh-heh, na pewno to zrobię. Do widzenia.";
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
			dialog.text = "Ha-ha-ha, czy widziałem Chińczyka? Wszyscy go widzieliśmy!";
			link.l1 = "Co jest w tym takiego śmiesznego? Nie mówię o wędrownym cyrku, jeśli o to ci chodzi. Mówię o wojowniku, oficerze marynarki.";
			link.l1.go = "PZ_BasTerAlkash_2";
		break;
		
		case "PZ_BasTerAlkash_2":
			dialog.text = "Ach, rozumiem, o co ci chodzi! Tak, widziałem go. Nawet po wytrzeźwieniu, nie mogłem przestać go widzieć... Nie mogę tego zapomnieć!";
			link.l1 = "To interesujące. Mów dalej. Wypijmy jeszcze jedno - prawdopodobnie pijesz teraz, żeby wszystko zapomnieć. Powiedz mi, co widziałeś, zanim zapomnisz.";
			link.l1.go = "PZ_BasTerAlkash_3";
		break;
		
		case "PZ_BasTerAlkash_3":
			dialog.text = "Tego nie da się tak łatwo zapomnieć! On skakał, kręcił się i wirował tą szpadą - nigdy nie widziałem nikogo tak przerażającego i biegłego z bronią.";
			link.l1 = "To brzmi jak on. Z kim walczył? Pamiętasz?";
			link.l1.go = "PZ_BasTerAlkash_4";
		break;
		
		case "PZ_BasTerAlkash_4":
			dialog.text = "Ze stróżami, kumplu! Spoglądał na nich ze zwężonymi oczami! Chociaż, jestem przekonany, że on zawsze tak się patrzy. Jak myślisz?";
			link.l1 = "Nie wiem, kolego. Kontynuuj. Czy myśleli, że jest szpiegiem? Dlaczego straże go zaatakowały?";
			link.l1.go = "PZ_BasTerAlkash_5";
		break;
		
		case "PZ_BasTerAlkash_5":
			dialog.text = "Kto wie? Próbowali zrozumieć, co robił w mieście...";
			link.l1 = "Czy go aresztowali? Czy...";
			link.l1.go = "PZ_BasTerAlkash_6";
		break;
		
		case "PZ_BasTerAlkash_6":
			dialog.text = "Ha, chcieliby! Nie mogli go złapać. Zabił strażników w mieście i uciekł do dżungli. Wysłali za nim kilka grup, ale żadna nie wróciła. Możesz sobie wyobrazić? Przekształcił tę jaskinię w prawdziwą twierdzę!";
			link.l1 = "To dopiero coś. Odpocznij i spróbuj o tym zapomnieć. Myślę, że teraz pójdę - kręci mi się w głowie.";
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
			dialog.text = "Nie widziałem go osobiście - kręcił się wokół gubernatora. Ale jego załoga zorganizowała tu wielką imprezę.";
			link.l1 = "Czy tak jest?";
			link.l1.go = "Sotta2";
		break;
		
		case "Sotta2":
			dialog.text = "Wszyscy mówią, że jest kupcem. Ale jego załoga nie wyglądała jak losowa zbieranina, powiadam ci! Wyglądali jakby... jakby... jakie to było słowo...?";
			link.l1 = "Rozumiem. Dzięki za towarzystwo, kumplu. Trzymaj się.";
			link.l1.go = "exit_sit";
			
			npchar.questTemp.Sotta = true;
			pchar.questTemp.PZ_BelizAskCitizens = sti(pchar.questTemp.PZ_BelizAskCitizens) + 1;
			AddDialogExitQuest("PZ_LongwayBelizDialog");
		break;
		
		case "Lutter1":
			dialog.text = "Świętuję! A kto mówi, że jestem sam? Ty jesteś tutaj, kumplu! A co do Matta, to musiało się to wydarzyć prędzej czy później.";
			link.l1 = "Dlaczego tak mówisz? Słyszałem, że to był niezwykle szczęśliwy pirat, którego Fortuna faworyzowała przez lata!";
			link.l1.go = "Lutter2";
		break;
		
		case "Lutter2":
			dialog.text = "Heh, nie tylko Fortuna! Był samotnym piratem, nie członkiem Bractwa! A tacy długo nie wytrzymują... Chociaż, słyszałem plotki, że kiedyś był pod skrzydłami Levasseura.";
			link.l1 = "To prawda, samotnicy długo nie wytrzymują. No, baw się dobrze. Muszę już iść, kumplu.";
			link.l1.go = "exit_sit";
			
			npchar.questTemp.Lutter = true;
			pchar.questTemp.PZ_BelizAskCitizens = sti(pchar.questTemp.PZ_BelizAskCitizens) + 1;
			AddDialogExitQuest("PZ_LongwayBelizDialog");
		break;
		
		case "Sepp1":
			dialog.text = "Eek, tak n-nie, nigdy go nie widziałem. Kim on jest?";
			link.l1 = "Jest kapitanem jednego z najszybszych statków na Archipelagu, brygu 'Banten'. Słyszałeś o nim?";
			link.l1.go = "Sepp2";
		break;
		
		case "Sepp2":
			pchar.questTemp.PZ.TortugaHabitueBlock = true;
			
			dialog.text = "Eee, nie, nie interesują mnie statki, kolego, eek! Może napijemy się jeszcze po jednym?";
			link.l1 = "Ja odpadam. I tak nie dostałem tego, czego chciałem.";
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
