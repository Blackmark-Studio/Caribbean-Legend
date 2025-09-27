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
            dialog.text = "Részeges típusválasztás (béta)";
			link.l1 = "Részeg";
			link.l1.go = "Beta_test_alc";
            link.l2 = "Kártyás szerencsejátékos";
			link.l2.go = "Beta_test_card";
			link.l3 = "Kockás szerencsejátékos";
			link.l3.go = "Beta_test_dice";
		break;
		
		case "Beta_test_alc":
            dialog.text = "Részeg kiválasztott";
			link.l1 = "Tovább";
			link.l1.go = "First time";
			npchar.quest.last_theme = 0;
		    npchar.quest.last_theme_game = 0;
		break;
		
		case "Beta_test_card":
            dialog.text = "Kártyák szerencsejátékos (30% azonnal elküldeni)";
			link.l1 = "Tovább";
			link.l1.go = "First time";
			npchar.quest.last_theme = 1;
		    npchar.quest.last_theme_game = 0;
		break;
		
		case "Beta_test_dice":
            dialog.text = "Dice szerencsejátékos (30% hogy azonnal elküldje újra)";
			link.l1 = "Tovább";
			link.l1.go = "First time";
			npchar.quest.last_theme = 1;
		    npchar.quest.last_theme_game = 1;
		break;
		
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = LinkRandPhrase("Lehet, hogy részeg vagyok, de nem vagyok idióta. Ha most iszom veled, másnap a katonák elkapnak. Kizárt dolog!", "Nem vagyok ellensége a saját városomnak. Nem iszom veled!" , ""+ GetSexPhrase("pajtás","lány") +", jobb, ha elmész innen, amíg még lehet...");
				link.l1 = RandPhraseSimple("Nos, ahogy kívánod...", "Heh, tudod, nem kell annyira berúgnom. Nem ez a megfelelô idô rá."); 
				link.l1.go = "exit";
				break;
			}
			if(CheckAttribute(pchar,"questTemp.HabitueSpeakDisable") && rand(1) == 0) // если дуэлянт то каждый второй посылает нафик
			{
				dialog.text = "Ha, mis"+ GetSexPhrase("ter","s") +", bizonyára hallottam rólad, he-he. Az emberek a kocsmákban azt mondják, hogy te egy kötekedô és párbajozó vagy. Én azt mondom, hogy a mi népünket nem könnyû megijeszteni, de egy pohár rumért senki sem akar meghalni. Félelmetesnek találom, hogy még csak a közeledbe is leüljek, úgyhogy inkább passzolok.";
				link.l1 = LinkRandPhrase("Akkor jó, hogy megszabadultunk tôle!","Tûnj el, amíg még jó kedvem van...","Menj, menj! Tûnj el, haleledel!");
				link.l1.go = "exit";
				link.l2 = "Várj, kérdezni akartam valamit. ....";
				link.l2.go = "talk_habitue_duel";
				break;
			}
			
            ok = CheckFreeSitFront(npchar);
            
            dialog.text = "Ne állj a fényembe, nem látom a legyeket a bögrében!";
            link.l1 = "Nem állok...";
		    link.l1.go = "exit";
		    if (!chrDisableReloadToLocation)
		    {
	            switch (npchar.quest.last_theme)
				{
					case "0": //пьяный.
						dialog.text = "Hic! Oh, "+ GetSexPhrase("haver, biztosan úgy nézel ki, mint egy tapasztalt öreg só","lass, biztosan úgy nézel ki, mint egy tapasztalt öreg só") +"! Talán meghívnál egy pohár rumra?";
						link.l1 = "Lehet, hogy én egy öreg senki vagyok, de ez nem jelenti azt, hogy piát veszek a csôcseléknek...";
						link.l1.go = "exit";

						if (makeint(pchar.money) >= 100 && ok) // только старые острова окучены на сесть
						{
							link.l2 = "Szívesen csatlakoznék a társaságodhoz.";
							link.l2.go = "talk_with_alchogol";
						}
						else
						{
	                        link.l2 = "És miért is?";
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
										Dialog.text = RandPhraseSimple("Talán egy kártyaparti? Nagyon érdekes játék!", "Javaslom, hogy játsszon kártyapartit. Mit fogsz mondani?");
										link.l1 = "És miért nem? Persze, játsszunk.";
										link.l1.go = "Cards_begin";
										link.l2 = "És mik a játékszabályok?";
										link.l2.go = "Cards_Rule";
										link.l3 = "Ne most.";
										link.l3.go = "exit";
									}
									else
					    			{
										Dialog.text = "Nem, nem kártyázom veled többé.";
						    			link.l1 = "Ahogy mondja.";
						    			link.l1.go = "exit";
									}
			                        // Игра в карты boal 20/05/05 <--
		                        break;

								case 1:
								// кости
		    						// Игра в кости boal 13/07/05 -->
	                                if (CheckNPCQuestDate(npchar, "Dice_date_begin"))
									{
										Dialog.text = RandPhraseSimple("Talán egy kockajáték? Nagyon érdekes játék!", "Javaslom, hogy dobj néhány kockát. Mit fogsz mondani?");
										link.l1 = "És miért nem? Persze, játsszunk.";
										link.l1.go = "Dice_begin";
										link.l2 = "És mik a játékszabályok?";
										link.l2.go = "Dice_Rule";
										link.l3 = "Ne most.";
										link.l3.go = "exit";
									}
									else
					    			{
										Dialog.text = "Nem, nem kockázok veled többé.";
					    				link.l1 = "Ahogy mondja.";
					    				link.l1.go = "exit";
									}
			                        // Игра в кости boal 13/07/05 <--
			                        //navy --> Дуэли
									if (CheckAttribute(NPchar, "Quest.DiceCheats") && sti(NPchar.Quest.DiceCheats) >= 1) 
									{
					    				link.l9 = RandSwear() + " Csalsz!!!";
					    				link.l9.go = "outraged";
									}
									//navy <--
			    				break;
	    					} 
						}
	        			else
	        			{
	                        dialog.text = RandPhraseSimple("Takarodj az asztalomtól! Azonnal!", " Ó? Mi van? Ki az? Hic... Tûnj el!");
	                        link.l1 = RandPhraseSimple("Az ivás bûnös lelkedre kárhoztatja! Térj észhez!", "Ne légy velem durva.");
	        			    link.l1.go = "exit";
	        			    link.l2 = RandPhraseSimple("Vigyázz a nyelvedre, te görény! Vagy megtanítalak a jó modorra.", "Mi lenne, ha most fejbe vágnálak, gondolom, az majd segít kijózanodni.");
	        	            link.l2.go = "tavern_keeper";
	        			}
					break;
				}
			}
			Diag.TempNode = "First time";
	    break;
	    
		case "talk_habitue_duel":
			dialog.text = "Nem mondok semmit, mis"+ GetSexPhrase("ter","s") +"! És nem hiszem, hogy bárki más is beszélni fog veled, hiszen az mindig bajt jelent. De tudod, az embereknek általában rövid a memóriájuk, úgyhogy egy-két hónap múlva talán elfelejtik a kalandodat, ha nem emlékezteted ôket még egyszer, persze, he-he! Viszlát, mis"+ GetSexPhrase("ter","s") +". ";
			link.l1 = "Rendben...";
			link.l1.go = "exit";
		break;
		
	    // карты -->
	    case "Cards_Rule":
   			dialog.text = CARDS_RULE;
			link.l1 = "Nos, akkor kezdjük is el...";
			link.l1.go = "Cards_begin";
			link.l3 = "Nem, ez nem nekem való...";
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

			Dialog.text = "Elôször határozzuk meg a tétet, majd (beírjuk a tétet).";
			link.l1 = "100";
			link.l1.edit = 1;
			link.l1.go = "Cards_Node_2";
			link.l3 = "Azt hiszem, mennem kell.";
			link.l3.go = "exit_sit";
		break;
		
		case "Cards_Node_2":
			iLa_Puesta = GetStrSmallRegister(dialogEditStrings[1]);
            if (!CheckCardsGameSmallRate())
		    {
                dialog.text = "Te egy hírhedt csaló vagy. Nem játszom veled.";
                link.l1 = "Ez mind hazugság! Hát, mindegy.";
			    link.l1.go = "exit_sit";
			    break;
		    }
		    
			if (sti(PCHar.Money) < sti(iLa_Puesta)*3)
		    {
                dialog.text = "Látom, csóró vagy, "+ GetSexPhrase("barátom","drága") +". Gyere vissza, ha meggazdagodtál.";
                link.l1 = "Rendben.";
			    link.l1.go = "exit_sit";
			    break;
		    }
		
			if (sti(NPChar.Money) < sti(iLa_Puesta)*3)
		    {
                dialog.text = "Már mindent elvesztettem, amim volt. Ma nem a szerencsenapom van.";
                link.l1 = "Rendben.";
			    link.l1.go = "exit_sit";
			    break;
		    }
		else
		{
			if(sti(iLa_Puesta) < 50)
			{
				dialog.text = "Most nevetsz rajtam, vagy mi?! A " + iLa_Puesta + " pezóért játszol?! Játsszunk ésszerû tétekért, különben kiszállok!";
				link.l1 = "Igen, igazad van. Kicsit feljebb kell emelnünk a tétet.";
				link.l1.go = "Cards_begin_2";
				link.l2 = "Meggondoltam magam, nem játszom.";
				link.l2.go = "exit_sit";
				break;
			}
			
			if(sti(iLa_Puesta) > 1000)
			{
				dialog.text = "Ilyen nagy pénzért játszani? Nem, passzolok, hacsak nem változtatunk a téten.";
				link.l1 = "Igen, igazad van. Le kell csökkentenünk a tétet egy kicsit.";
				link.l1.go = "Cards_begin_2";
				link.l2 = "Igazából úgy döntöttem, hogy egyáltalán nem játszom.";
				link.l2.go = "exit_sit";
				break;
			}
			dialog.text = "Rendben, játsszunk a " + iLa_Puesta + " érmékért.";
			link.l1 = "Osszátok ki a lapokat!";
			link.l1.go = "Cards_begin_go";
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
			pchar.GenQuest.Cards.iRate     = sti(iLa_Puesta);
            pchar.GenQuest.Cards.SitType   = true;
		}
		break;
		
		case "Cards_begin_2":
			dialog.text = "Mi a tét? (Add meg a fogadást)";
			link.l1 = "50";
			link.l1.edit = 1;
			link.l1.go = "Cards_Node_2";
			link.l2 = "Azt hiszem, végül is nem fogok játszani...";
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
			link.l1 = "Nos, akkor kezdjük is el...";
			link.l1.go = "Dice_begin";
			link.l3 = "Nem, ez nem nekem való...";
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
			Dialog.text = "Határozzuk meg a tétet (befogadás tét).";
			link.l1 = "50";
			link.l1.edit = 1;
			link.l1.go = "Dice_Node_2";
			link.l3 = "Azt hiszem, mennem kell.";
			link.l3.go = "exit_sit";
		break;

		case "Dice_Node_2":
			iLa_Puesta = GetStrSmallRegister(dialogEditStrings[1]);
            if (!CheckDiceGameSmallRate())
		    {
				dialog.text = "Te egy hírhedt csaló vagy. Nem fogok veled kockázni.";
                link.l1 = "Ez mind hazugság! Hát, mindegy.";
			    link.l1.go = "exit_sit";
			    break;
		    }

			if (sti(pchar.Money) < sti(iLa_Puesta)*6)
		    {
                dialog.text = "Látom, csóró vagy, "+ GetSexPhrase("barátom","drága") +". Gyere vissza, ha meggazdagodtál.";
                link.l1 = "Rendben.";
			    link.l1.go = "exit_sit";
			    break;
		    }
			
			if (sti(npchar.Money) < sti(iLa_Puesta)*6)
		    {
                dialog.text = "Már mindent elvesztettem, amim volt. Ma nem a szerencsenapom van.";
                link.l1 = "Rendben.";
			    link.l1.go = "exit_sit";
			    break;
		    }
		else
		{
			if(sti(iLa_Puesta) < 50)
			{
				dialog.text = "Most nevetsz rajtam, vagy mi?! " + iLa_Puesta + " pezóért játszol kockánként?! Játsszunk ésszerû tétekért, vagy én kiszállok!";
				link.l1 = "Igen, igazad van. Kicsit feljebb kell emelnünk a tétet.";
				link.l1.go = "Dice_begin_2";
				link.l2 = "Meggondoltam magam, nem játszom.";
				link.l2.go = "exit_sit";
				break;
			}
			
			if(sti(iLa_Puesta) > 1000)
			{
				dialog.text = "Kockázni ilyen nagy pénzért? Nem, passzolok, hacsak nem változtatunk a téten.";
				link.l1 = "Igen, igazad van. Le kell csökkentenünk a tétet egy kicsit.";
				link.l1.go = "Dice_begin_2";
				link.l2 = "Igazából úgy döntöttem, hogy egyáltalán nem játszom.";
				link.l2.go = "exit_sit";
				break;
			}
			dialog.text = "Rendben, játsszunk " + iLa_Puesta + " érmékért kockánként.";
			link.l1 = "Dobjunk!";
			link.l1.go = "Dice_begin_go";
			pchar.GenQuest.Dice.npcharIdx = npchar.index;
			pchar.GenQuest.Dice.iRate     = sti(iLa_Puesta);
            pchar.GenQuest.Dice.SitType   = true;
		}
		break;
		
		case "Dice_begin_2":
			dialog.text = "Mi a tét? (Add meg a fogadást)";
			link.l1 = "50";
			link.l1.edit = 1;
			link.l1.go = "Dice_Node_2";
			link.l2 = "Azt hiszem, végül is nem fogok játszani...";
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
			dialog.text = "Nos, h-hic! A dolgok jól mennek. Hic! Nem látod, hogy ez jön. Hi-ic! Ez a rum jó. Jamaikai fekete rum. hic!\nTessék, tedd és töltsd!";
			link.l1 = "Rendben, miért ne.";
			link.l1.go = "talk_with_alchogol_song_2";
			link.l2 = "Sajnálom barátom, de mennem kell.";
			link.l2.go = "exit";
		break;
		
		case "talk_with_alchogol_song_2":
			dialog.text = "Bögrék és arcok jönnek és mennek... Hic... Egészen addig, amíg a padlóra nem esek. Mindig iszom... Hic! Hol van a pia... És mi a rím...";
			link.l1 = "A pia itt van, és a lányok jól vannak, Mindenki akar egy buccaneert, de úgy látszik, csak a rum az enyém.";
			link.l1.go = "talk_with_alchogol_song_3";
			link.l2 = "Erre nincs idôm.";
			link.l2.go = "exit";
		break;
		
		case "talk_with_alchogol_song_3":
			dialog.text = "Ha szomorú vagy, ne próbálj gondolkodni, gyere ide, hadd igyunk! Biztos minden rendben lesz, én a barátod vagyok, te pedig az enyém!";
			link.l1 = "Barátnak lenni biztos nagyszerû, ha elmentél, ô vár, baráttal nincs gyûlölet, de ha elfogy a rum, csak vita van. Szóval igyunk, haver, mielôtt elmegyek és elkések... ";
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
			dialog.text = LinkRandPhrase("Hic! Így már jobb! Így már biztosan jobb! Na és? Veszel nekem egy kis rumot, vagy mi lesz?",
						"Ülj le, " + GetAddress_Form(npchar) + ", csapjunk le egy pohár jó öreg jamaikai rumra. Az sosem árt az egészségnek. És ha érdekli, mi történik - ennél a kocsmánál jobb helyet nem talál, biztosíthatom. Egy kis pénz, néhány csésze tisztességes rum - és mindent megtudsz, amit tudni akartál, sôt, még többet is, bízz egy öreg patrónusban...",
						"Heh, kérem, üljön le, "+ GetSexPhrase("jó barátom","kisasszony") +", igyunk egyet... Miért ne ihatnánk egy jó társaságban? Sok érdekes dolgot hallhatsz, ha türelmes vagy és lassan, kis kortyokban iszol... Vannak kapitányok, akik kalandjaikkal dicsekednek, vannak sokan mások, akik fontos dolgokat fecsegnek ki, amikor már nem bírnak magukkal... Sokan töltik ott az idejüket, és sokaknak van mondanivalója, higgyétek el, "+ GetSexPhrase("jó barátom","Miss") +".");
			link.l1 = "És miért is ne! Csapos! Rumot, kettônknek!";
			link.l1.go = "sit_2";
		break;

		// Церковный генератор. Квест №2 -->
		case "Alcogol_GenQuest_Church_2_1":
			dialog.text = "Persze! Hallottad... a banditák még a templomokat is kifosztják!";
				link.l1 = "Nos, ez úgy hangzik, mint a kalózok, ki más...";
				link.l1.go = "Alcogol_GenQuest_Church_2_2";
				DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.AskPeople");
				DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.AskBarmen");
				DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.AskAlcash");
			break;
			
		case "Alcogol_GenQuest_Church_2_2":
			dialog.text = "Milyen kalózok? Csak a közönséges szárazföldi csavargók, és persze az átkozott helyi... Ha látogatók lennének, akkor nem tudnák, hogy mikor van tele a templom kasszája. És amúgy is aligha keverednének bele ebbe a zûrzavarba.";
				link.l1 = "Merész fickók, az biztos. Olyan gálánsan kinyitották a gyarló ajtórudat...";
				link.l1.go = "Alcogol_GenQuest_Church_2_3";
			break;
			
		case "Alcogol_GenQuest_Church_2_3":
			dialog.text = "A-ha. És okosak is. Ki tenné ki magát ilyen módon?";
				link.l1 = "Ez igaz. Az egész egyházközség pénzt spórolt, hogy a templomnak adományozzon, és most ezek az ügyes fickók meggazdagodtak belôle? Biztosan elkapják ôket. Az egész világ ôket fogja keresni.";
				link.l1.go = "Alcogol_GenQuest_Church_2_4";
			break;
			
		case "Alcogol_GenQuest_Church_2_4":
			dialog.text = "Aligha. Ki fogja ôket keresni? Csak kirabolták a templomot, és elhagyták a várost, elszálltak a széllel. A dzsungel nagy, nagyon nagy, ott keresnéd ôket ítéletnapig. És pár hónap múlva az emberek elfelejtik az egészet, jegyezzék meg, amit mondok!";
				link.l1 = "Nem hiszem. Az ilyen dolgokat nem lehet megbocsátani.";
				link.l1.go = "Alcogol_GenQuest_Church_2_5";
			break;
			
		case "Alcogol_GenQuest_Church_2_5":
			dialog.text = "Az ember emlékezete olyan, mint egy szivárgó hajó. Az emberek elfelejtenek és megbocsátanak. De Isten?! Ô mindent lát. Ô az, akitôl félned kell. Mondom, tíz évvel ezelôtt valami szörnyûség történt egy régi barátommal. Neki is hiányzott a Teremtô iránti tisztelet, és majdnem egyenesen a tengeri ördöghöz ment...";
				link.l1 = "Sajnálom barátom, de most mennem kell. Majd máskor beszélünk a haverodról. Viszlát.";
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
				dialog.text = "Ó, Francois! Persze, emlékszem arra a fickóra... Nem, nem tudom. De, tudod, megkérdezheted a pincérnôt róla. Amióta itt lakik, minden éjszakát vele töltött. Az biztos, hogy egy ribanc. Talán elárult neki valamit.";
				link.l1 = "Kösz a tanácsot, haver. Megyek, beszélek vele.";
				link.l1.go = "exit_sit";
				pchar.questTemp.Slavetrader = "FindRatJamaica_W";
			break;
			
			case "EscapeSlave_Villemstad_H1":
				dialog.text = "Igen, nagyon furcsa dolgok történhetnek néha a nyílt tengeren. A legutóbbi utamon láttam valami igazán...";
				link.l1 = "Gyerünk, mondd el, csak ne túlozz túlságosan. Addig is hozok még rumot.";
				link.l1.go = "EscapeSlave_Villemstad_H2";
			break;
			
			case "EscapeSlave_Villemstad_H2":
				dialog.text = "Istenre esküszöm, nemes"+ GetSexPhrase("uram","hölgy") +" - a saját szememmel láttam... Egy hajó hajózott, de matrózok helyett óriásmajmok voltak... vagy makákók... majmok, tudod.";
				link.l1 = "Micsoda?! Mondd csak, barátom, te is iszol az ôrségben?";
				link.l1.go = "EscapeSlave_Villemstad_H3";
			break;
			
			case "EscapeSlave_Villemstad_H3":
				dialog.text = "Ha hazudnék, akkor vakon üssön meg! Nem hallottál még a majomrákról? Baszd meg, garnélarák, ha-ha! ... A majomhajó.";
				link.l1 = "Milyen majomhajó?";
				link.l1.go = "EscapeSlave_Villemstad_H4";
			break;
			
			case "EscapeSlave_Villemstad_H4":
				dialog.text = "Óh-óh, mondom, hogy a saját szememmel láttam. Vihar volt. Nem láttam semmit, és akkor a hajó megjelent a semmibôl. Tépett vitorlák. Az elôvitorla is el volt törve, a nagyvitorla is, és a fene egye meg, minden el volt törve! És mégis széllel szemben száguldott!\nÉs majmok voltak a fedélzetén... rengeteg, mint a... fókák bástyája! És egy tiszta gorilla állt a kormánynál! Kilenclábú, piros ingben és cápafogak helyett kereszt a mellkasán... Szeme vörös, agyarai villogtak, meglátott minket, és kiáltott valamit...";
				link.l1 = "Hazudsz, mint a vízfolyás, barátom! Tudod, részegen is lehet látni dolgokat. Legközelebb azt fogod mondani, hogy ô volt a repülô holland.";
				link.l1.go = "EscapeSlave_Villemstad_H5";
			break;
			
			case "EscapeSlave_Villemstad_H5":
				dialog.text = "Nem, ô nem volt holland. Az igazat mondom! Egy bárka volt, és a tatján volt egy felirat - " + pchar.questTemp.Slavetrader.ShipName + ".";
				link.l1 = "Az istenit! Azt hiszem, tudom, mirôl 'majmok' beszéltél. Valóban, a rum meg tudja oldani a nyelveket - csak hallgatni kell...";
				link.l1.go = "EscapeSlave_Villemstad_H6";
			break;
			
			case "EscapeSlave_Villemstad_H6":
				dialog.text = "Látod - én megmondtam neked! És te nem hittél nekem!... Jól van, még egy utolsó pohárral, aztán mehetünk.";
				link.l1 = "Rendben, köszönöm az érdekes történetet. Mennem kell. Sok szerencsét, haver.";
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
			dialog.text = "Nem, kapitány. A tengerészélet nem nekem való. Tudja, nekem is volt egyszer egy hajóm, de... de nagyon balszerencsés voltam.";
			link.l1 = "Figyelj - láttam egy szokatlan hajót, amelyik a parton fekszik - 'Meifeng' ez a neve. Még sosem láttam ilyen hajót. Ki a tulajdonosa? Talán eladó? Megnézném.";
			link.l1.go = "Lucas_Tavern_1";
		break;
		
		case "Lucas_Tavern_1":
			dialog.text = "Ha! Aligha, kapitány. Nem hiszem, hogy a kínai fickó eladná magának vagy bárki másnak a hajóját.";
			link.l1 = "Egy kínai? Vannak kínaiak Curacaón? És még a saját hajójának a kapitánya is?";
			link.l1.go = "Lucas_Tavern_2";
		break;
		
		case "Lucas_Tavern_2":
			dialog.text = "De van, ahogy látja. De ez valójában nem az ô hajója - ez a Kereskedelmi Társaságé. Azt mondják, mynheer Rodenburg, az igazgatóhelyettes és most megbízott kormányzó a tulajdonosa.";
			link.l1 = "Tehát Matthias Beck visszavonult?";
			link.l1.go = "Lucas_Tavern_3";
		break;
		
		case "Lucas_Tavern_3":
			dialog.text = "Ha! Mynheer, tényleg gyakrabban kellene látogatnia a földet - vagy legalább a hírekkel törôdnie. Matthias Becket elbocsátották és rács mögé helyezték, amíg minden körülményt tisztáznak.";
			link.l1 = "Ezt ne mondd! Valóban túl sok idôt töltök a tengeren. És mikor történt ez?";
			link.l1.go = "Lucas_Tavern_4";
		break;
		
		case "Lucas_Tavern_4":
			dialog.text = "Valójában csak néhány nappal ezelôtt. Egy futárbrigantin érkezett a kikötôbe. Nem volt a legjobb állapotban, nyilván heves harcban vett részt. A kapitány egyenesen Rodenburg mynheerhez ment a jelentésével, és néhány órán belül Matthias Becket Rodenburg mynheer és a parancsnok letartóztatta az angol hírszerzéssel való együttmûködés gyanújával.";
			link.l1 = "Szörnyû dolgokat mondasz. Hogyan lehet Curacao kormányzója angol kém?";
			link.l1.go = "Lucas_Tavern_5";
		break;
		
		case "Lucas_Tavern_5":
			dialog.text = "Ôszintén szólva én is alig hiszem el. Úgy hallottam, hogy hamarosan maga Peter Stuyvesant, a Társaság igazgatója érkezik ide. Úgy tûnik, személyesen fogja lefolytatni a nyomozást.";
			link.l1 = "Akkor igaza van. Kockázatos lehet most a mynheer Rodenburgot zaklatni.";
			link.l1.go = "Lucas_Tavern_6";
		break;
		
		case "Lucas_Tavern_6":
			dialog.text = "Jó gondolat, kapitány! Annál is inkább, mert 'Meifeng' már töltés alatt van. Most tért vissza a Fô-tenger déli partvidékére tett útjáról, és hamarosan újra vitorlát bont. És mondhatom, furcsa dolgok történnek ott. A holland matrózokat és a Társaság gárdistáit felmentették a szolgálat alól, és egy másik legénységet állítanak össze. És esküszöm minden kupa rumra, amit életemben megittam, hogy azok az új önkéntesek valami egészen másfélék, csupa kalóz, bandita és gyilkos!";
			link.l1 = "Valóban csoda! Hát, kár érte! Olyan szép hajó... Hát, a sors másképp akarta... Köszönöm az érdekes történetet és a híreket! Öröm volt veled beszélgetni!";
			link.l1.go = "Lucas_Tavern_7";
		break;
		
		case "Lucas_Tavern_7":
			dialog.text = "Nos, köszönöm a társaságot és a rumot, kapitány úr! Ugorjon be máskor is!";
			link.l1 = "Persze, hogy be fogok!";
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
			if(bImCasual) NewGameTip("Felfedezô mód: az idôzítô nincs kikapcsolva. Tartsd be a határidôt!");
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
				dialog.text = "Ha! "+pchar.GenQuest.FindFugitive.Name+"? Tudom, tudom... Nagyon nem társasági ember az a kolléga. Egy magányos farkas, hogy úgy mondjam. Egész nap a hosszú csónakján hajózik a sziget partjainál, egészen estig. Az emberek azt hiszik, hogy halász, de valójában gyöngyhalász... He-he! Én ezt biztosan tudom!";
				link.l1 = "Heh! Szóval... meg tudod mondani, hol találom?";
				link.l1.go = "FindFugitiveHb_1";
			}
			else
			{
				dialog.text = ""+pchar.GenQuest.FindFugitive.Name+"? Nem, esküszöm, soha nem hallottam róla... De te - Hic! Megkérdezheted a csaposunkat - ô biztosan tudja!";
				link.l1 = "Hmm... Rendben, majd még kérdezôsködöm egy kicsit. Nos, haver, köszönöm a társaságot. Viszlát!";
				link.l1.go = "exit_sit";
			}
		break;
		
		case "FindFugitiveHb_1":
			dialog.text = "Persze, hogy tudok! Minden reggel megtalálható a parton, a "+XI_ConvertString(pchar.GenQuest.FindFugitive.Shore+"Gen")+". Csak minél korábban gyere, különben vitorlát bont, és várnod kell másnap reggelig.";
			link.l1 = "Köszönöm! Sokat segítettél nekem, barátom! Viszlát!";
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
			dialog.text = "A hajógyárunkban lézengett, és kérdezgette a hajósokat errôl-arról. És ez gonosz tréfát ûzött vele. Néhányan figyelmeztették a parancsnokot, hogy gyanús emberek lézengenek a városban, ezért ôrizetbe vette, aztán kiderült, hogy valójában nem is kereskedô.";
			link.l1 = "Gondolom, el akarta lopni a hajóépítôd valamelyik titkos projektjét?";
			link.l1.go = "trial_spy_1";
		break;
		
		case "trial_spy_1":
			dialog.text = "Ki tudja? De abban egészen biztos vagyok, hogy a gálya 'Alacantara' a gálya érdekelte! Hic! Erre megesküszöm! Ezt a hajót maga a senor governor szereli fel, úgyhogy lefogadom, hogy ez a gazember megpróbált valamit kiszagolni róla.";
			link.l1 = "Ha! Ez elég valószínû. A kormányzó biztosan valami értékes dologgal fogja megrakodni...";
			link.l1.go = "trial_spy_2";
		break;
		
		case "trial_spy_2":
			dialog.text = "Ez magától értetôdô! Ez valami igazán figyelemre méltó dolog lehet, én mondom neked! Ó, és az emberek azt mondták, hogy a halászok egy idegen katonai hajót láttak ezeken a vizeken... valószínûleg egy fregattot. Talán onnan jött az a kém?";
			link.l1 = "Igen, lehet... Rendben, haver, köszönöm a társaságot, de most mennem kell!";
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
				dialog.text = "Egészségedre és nagylelkûségedre!";
				link.l1 = "Haver, nem láttál egy kínai fickót a városban?";
				link.l1.go = "PZ_BasTerAlkash_1";
				break;
			}
			// <== Квест "Путеводная звезда" - Sinistra
			
			dialog.text = LinkRandPhrase("Te egy "+ GetSexPhrase("igazi barát vagy","nagyszerû lány") +"! Örülök, hogy megismertelek! Egészségedre!",
										 "Hic! Ez nagyszerû rum! Hic... Egészségedre!",
										 "Egészségedre és nagylelkûségedre!");
			link.l1 = "Heh, ez valóban erôs rum. Rendben, mennem kell. Érezzétek jól magatokat!";
			link.l1.go = "exit_sit";
			if (makeint(pchar.money) >=2)
			{
				link.l2 = "Még egy pohárral, nem bánod?";
				link.l2.go = "sit_3";
			}

			link.l4 = LinkRandPhrase("Olyan érzés, mintha egy örökkévalóságot töltöttem volna a tengerben. Van valami hír?",
									"Mit mondanak az emberek? Biztos, hogy meghívlak egy italra.",
									"Mondd csak, pajtás, milyen mesék népszerûek most a kocsmákban?");
			link.l4.go = "rumours_habitue";
		break;

		case "sit_3":
			int iSituation;
			if(IsEquipCharacterByArtefact(pchar, "totem_01")) iSituation = makeint(rand(3));
			else iSituation = makeint(rand(5));
			switch (iSituation)
			{
				case 0:
					dialog.text = "Ó! Remek ötlet!";
					link.l1 = "Csapos! Több rumot!";
					link.l1.go = "sit_2";
				break;

				case 1:
					dialog.text = "Neked! Ó, a pokolba! Ki az?";
					link.l1 = "Huh? Micsoda? Hová? Biztos látok dolgokat.";
					link.l1.go = "sit_2";// to_do "sit_case_5_exit";
				break;
				
                case 2:
	         		dialog.text = "Akkor igyunk! Még egyet?";
					link.l1 = "Gyerünk!";
					link.l1.go = "sit_2";
                break;				
				
				case 3:
					if(rand(1) == 0)
					{
						dialog.text = RandPhraseSimple("Hé, te, " + GetAddress_Form(NPChar) + ", biztosan azt gondolod, hogy mindenki csodál téged, igaz? Nos, ha engem kérdezel, te csak egy közönséges rabló vagy!... És gyilkos! 'Nemes kalóz'! Ha! A bandita az bandita... Hic... Akár a szárazföldön, akár a tengeren...",
							"Hic! "+ GetSexPhrase("Sco... Csibész","Fi... Mocsok") +"! Azt akarod, hogy addig igyak, amíg el nem ájulok - hic - aztán ellopod az összes pénzemet!");
						link.l1 = "Látom, már eleget ittál... Menj, aludd ki magad... Nekem meg mennem kell...";
						link.l1.go = "exit_sit";						
						link.l2 = "Nem tetszik a hangnemed, haver. Fogd be a szád, rendben?";
						link.l2.go = "sit_case_2_enemy";
						link.l3 = "Kit neveztél most banditának, te szárazföldi csavargó?! Lássuk, mit fogsz mondani egy lyukkal a hasadban!";
						link.l3.go = "sit_case_2_enemy2";
					link.l4 = "Nyugodj meg! Elfelejtetted? Én vagyok az egyetlen igaz barátod!";
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
							dialog.text = RandPhraseSimple("Miért bámulsz engem? Megvárjátok, amíg elájulok - hic - és akkor ellopjátok az összes pénzemet! Honnan jött ez a sok csôcselék?! Hic... Nincs hely egy tisztességes embernek ebben a kocsmában?",
								"Tisztelsz engem?... Igen, te! Tisztelsz engem?! Te csak vigyázz magadra... Velem nem lehet szórakozni... Egy ütés a szemem közé... és olyan jó vagy, mintha halott lennél...");
							link.l1 = "Haver, részeg vagy, mint egy disznó. Menj haza és aludd ki magad... Nekem is mennem kell...";	
							link.l1.go = "exit_sit";
							link.l2 = "Nyugalom, haver. Vigyázz, kivel beszélsz.";
							link.l2.go = "sit_case_2_enemy1";
							link.l3 = "Mit mondtál?! Majd én megleckéztetlek!";
							link.l3.go = "sit_case_2_enemy2";
							link.l4 = "Nyugodj meg! Elfelejtettél engem? Én vagyok az egyetlen igaz barátod!";
							link.l4.go = "sit_case_2_friend";	
						//}
					}
				break;

				case 4:
					dialog.text = "Hallgass ide! Te jó ember vagy! Talán segíthetnél nekem... egy ügyben?";
					link.l1 = "Nem, azt hiszem, most mennem kell.";
					link.l1.go = "exit_sit";
					link.l2 = "Persze! Hic! Barátok vagyunk... nem igaz? Hic!";
					link.l2.go = "sit_case_3";
				break;

				case 5:
					if (GetSummonSkillFromName(pchar, SKILL_SNEAK) > rand(110) || CheckAttribute(pchar, "questTemp.Sharlie.Lock"))
					{
						dialog.text = "...És aztán elkaptam a szablyáját a pengéjénél fogva...";
						link.l1 = "...és aztán azt mondta...";
						link.l1.go = "sit_2";
					}
					else
					{
						dialog.text = "...És aztán elkaptam a szablyáját a pengéjénél fogva...";
						link.l1 = "...hic! ...és aztán azt mondta...";
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
			dialog.text = "A p-pont az, hogy az egyik s-katona megsértett engem. A-azt!";
			link.l1 = "Egy katona? Nem, azt hiszem, kihagyom.";
			link.l1.go = "exit_sit";
			link.l2 = "Nyugodj meg! Elfelejtettél engem? Én vagyok az egyetlen igaz barátod!";
			link.l2.go = "sit_2";
		break;

		case "sit_case_2_friend":
			dialog.snd = "Voice\HADI\HADI038";
			dialog.text = "És te? Miféle barát vagy te? N-nem! Te... meg akarsz ölni! Ez az!";
			link.l1 = "Nos, már így is eleget ittál. Viszontlátásra.";
			link.l1.go = "exit_sit";
			link.l2 = "Micsoda? Bebizonyítom neked, hogy n-nem foglak megölni! I... Levágom a kezed!... Anélkül... nem lehet megölni téged!... Hic!";
			link.l2.go = "sit_case_2_friend_2";
		break;

		case "sit_case_2_friend_2":
			dialog.snd = "Voice\HADI\HADI039";
			dialog.text = "Aaaah! Vigyétek "+ GetSexPhrase("ôt","ôt") +" el tôlem!";
			link.l1 = "Nyugodj meg... hic... Nem fog fájni!... Kevésbé fájdalmas, mint egy borotválkozás!";
			link.l1.go = "tavern_keeper";
		break;

		case "sit_case_2_enemy":
			dialog.snd = "Voice\HADI\HADI040";
			dialog.text = "Ne próbálj megfélemlíteni! Hic! Engem nem lehet ilyen könnyen megijeszteni!... Te pedig - akasztófán kellene lógnod... A magadfajtákkal együtt - hic! Fújhatod a tollaidat, amennyit csak akarod - de akkor is bûzlesz a rothadt halaktól! És nem fogok vigyázni a nyelvemre, amikor - hic! - amikor a fajtáddal beszélek! Mindannyian undorodom tôletek!";
			link.l1 = "Argh, miért is beszélek egy ilyen részeges alakkal... Azt hiszem, megyek és szívok egy kis friss levegôt...";
			link.l1.go = "exit_sit1";
			link.l2 = "Túl merész vagy, haver. Visszatömöm a szavaidat a torkodba!";
			link.l2.go = "sit_case_2_enemy3";
		break;

		case "sit_case_2_enemy1":		
			dialog.snd = "Voice\HADI\HADI040";
			dialog.text = "Mi-mi?! A saját kezemmel foglak megfojtani! Hic... Senki sem menekült el elôlem - hic! - eddig!";
			link.l1 = "Nem vagy te egy részeg disznó? Elrontani egy ilyen szép estét... Rendben, menjetek, kapjátok el a csótányokat - és én lelépek innen.";
			link.l1.go = "exit_sit1";
			link.l2 = RandSwear() + "Látom, nem fogsz csendben maradni. Hát, akkor egy lecke jó modorból jár.";
			link.l2.go = "sit_case_2_enemy3";
		break;
		
		case "sit_case_2_enemy2":	
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			if(rand(1) == 0)
			{
				dialog.text = LinkRandPhrase("Gyere közelebb, te gazember! Megkapod, amit megérdemelsz!", RandSwear() + "Megkapod, amit megérdemelsz!","Ha! Jól van, tengeri kutya - lássuk, mit fogsz csinálni a szárazföldön!");
				link.l1 = RandPhraseSimple(RandPhraseSimple("Esküszöm, meg fogod bánni!","Fülekre fogom rövidíteni a mocskos nyelvedet!"), RandPhraseSimple("kibelezlek, mint egy disznót, a seggedtôl a szaros lyukad felé, amit egyesek szájnak hívnak!","Esküszöm, hogy elhallgattatlak!"));
				link.l1.go = "fight_right_now";
			}
			else
			{
				dialog.text = "Hé, fiúk! Söpörjük ki ezt a szemetet a városunkból!";
				link.l1 = RandPhraseSimple(RandSwear() + "Imádkozzatok, szemetek!","Ó, szóval nem vagy egyedül?! Hát, jó neked - lesz társaságod a pokolban!");
				link.l1.go = "fight_right_now_1";
			}
		break;
		
		case "sit_case_2_enemy3":	
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
			if(rand(1) == 0)
			{
				dialog.text = LinkRandPhrase("Gyere közelebb, te gazember! Megkapod, amit megérdemelsz!", RandSwear() + "Megkapod, amit megérdemelsz!","Ha! Jól van, tengeri kutya - lássuk, mit fogsz csinálni a szárazföldön!");
				link.l1 = RandPhraseSimple(RandPhraseSimple("Esküszöm, meg fogod bánni!","Fülekre fogom rövidíteni a mocskos nyelvedet!"), RandPhraseSimple("kibelezlek, mint egy disznót, a seggedtôl a szaros lyukad felé, amit egyesek szájnak hívnak!","Esküszöm, hogy elhallgattatlak!"));
				link.l1.go = "fight_right_now";
			}
			else
			{
				dialog.text = "Hé, fiúk! Söpörjük ki ezt a szemetet a városunkból!";
				link.l1 = RandPhraseSimple(RandSwear() + "Imádkozzatok, szemetek!","Ó, szóval nem vagy egyedül?! Hát, jó neked - lesz társaságod a pokolban!");
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
			dialog.text = "Hé, valamit nem értettem! Amint befordultam a sarkon, valami új újonc landolt a helyemen. Takarodj innen!";
			link.l1 = "Mindig ez van: csak leülsz az asztalhoz, és kiderül, hogy már foglalt... Tartsd a helyed, úgyis el akartam menni.";
			link.l1.go = "bad_habitue1";
			link.l2 = "Még egy ilyen mondat a mocskos szádból, és ez lesz az utolsó, amit életedben mondasz, érted?";
			link.l2.go = "bad_habitue2";
			link.l3 = "Nem tudom, hogy ez tényleg a te helyed volt-e, de nem hagyom, hogy így beszélj velem. Vigyázz a szavaidra.";
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
				dialog.text = LinkRandPhrase("Gyerünk, csibészek! Mindjárt jóllaksz!", RandSwear() + "Most pedig rendesen levetkôztetlek titeket!","Ha! Gyerünk, tengerész - lássuk, mit tudsz a szárazföldön!") ;
				link.l1 = RandPhraseSimple(RandPhraseSimple("Esküszöm, ezt még megbánod!","Rövidre vágom a kibaszott nyelvedet!"), RandPhraseSimple("kibelezlek, mint egy disznót, a seggedtôl a szaros lyukad felé, amit egyesek szájnak hívnak!","Esküszöm, hogy elhallgattatlak!"));
				link.l1.go = "fight_right_now";
			}
			else
			{
				dialog.text = "Gyerünk srácok! Tüntessük el ezt a skálát a városunkból!";
				link.l1 = RandPhraseSimple(RandSwear() + "Imádkozzatok, ti szemetek!","Ó, nem vagy egyedül! Hát, a pokolban lesz társaságod!");
				link.l1.go = "fight_right_now_1";
			}
		break;
		
		case "bad_habitue3":
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			if(rand(1) == 0)
			{
				dialog.text = LinkRandPhrase("Gyerünk, csibészek! Mindjárt jóllaksz!", RandSwear() + "Most pedig rendesen levetkôztetlek titeket!","Ha! Gyerünk, tengerész - lássuk, mit tudsz a szárazföldön!") ;
				link.l1 = RandPhraseSimple(RandPhraseSimple("Esküszöm, ezt még megbánod!","Rövidre vágom a kibaszott nyelvedet!"), RandPhraseSimple("kibelezlek, mint egy disznót, a seggedtôl a szaros lyukad felé, amit egyesek szájnak hívnak!","Esküszöm, hogy elhallgattatlak!"));
				link.l1.go = "fight_right_now";
			}
			else
			{
				dialog.text = "Gyerünk srácok! Tüntessük el ezt a skálát a városunkból!";
				link.l1 = RandPhraseSimple(RandSwear() + "Imádkozzatok, ti szemetek!","Ó, nem vagy egyedül! Hát, a pokolban lesz társaságod!");
				link.l1.go = "fight_right_now_1";
			}
		break;
		
		//--> Sinistra Длинные тени старых грехов
		case "DTSG_NightIskat":
			dialog.text = "Persze, mindannyian ismerjük egymást! Miért kérdezed?";
            link.l1 = "Meg akartam látogatni az uzsorást, és megtudtam, hogy eladta a régi házát. Tudod, hol lakik most?";
            link.l1.go = "DTSG_NightIskat_2";
		break;
		
		case "DTSG_NightIskat_2":
			dialog.text = "Miért van rá szükséged ilyenkor, hic? Csak látogass el a bankba reggel!";
            link.l1 = "Sürgôsen pénzre van szükségem. Hadd dolgozzon érte a pénzeszsák a változatosság kedvéért! A fajtájuk mindig ingyenélôknek nevez minket, akik csak koldulunk, panaszkodunk, és soha nem adjuk vissza, amivel tartozunk.";
            link.l1.go = "DTSG_NightIskat_3";
		break;
		
		case "DTSG_NightIskat_3":
			dialog.text = "Ha-ha-ha, hic, igen, hadd dolgozzon! Tudod, hol lakott a mi dicsô Fleetwood kapitányunk?";
            link.l1 = "Persze, ki ne ismerné Richardot. Most meg a bankár lakik ott?";
            link.l1.go = "DTSG_NightIskat_4";
		break;
		
		case "DTSG_NightIskat_4":
			dialog.text = "Igen, igaza van. Ha ott leszel, barátom - mondd meg neki, hogy túlságosan el van telve magával.";
            link.l1 = "Heh-heh, majd megnézem. Viszontlátásra.";
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
			dialog.text = "Ha-ha-ha-ha, láttam egy kínait? Mindannyian láttuk!";
			link.l1 = "Mi olyan vicces? Nem egy vándorcirkuszról beszélek, ha erre gondolsz. Hanem egy harcosról, egy tengerésztisztrôl.";
			link.l1.go = "PZ_BasTerAlkash_2";
		break;
		
		case "PZ_BasTerAlkash_2":
			dialog.text = "Ah, értem, mire gondolsz! Igen, láttam ôt. Még miután kijózanodtam, nem tudtam nem látni ôt...  Nem tudom elfelejteni!";
			link.l1 = "Ez érdekes. Folytasd csak. Igyunk még egyet - most valószínûleg azért iszol, hogy elfelejtsd az egészet. Mondd el, mit láttál, mielôtt megteszed.";
			link.l1.go = "PZ_BasTerAlkash_3";
		break;
		
		case "PZ_BasTerAlkash_3":
			dialog.text = "Egy vándorcirkuszt, a seggemet! Ugrált, pörgött, és pörgette azt a szablyát - még senkit sem láttam ilyen ügyesen és félelmetes módon bánni a fegyverrel.";
			link.l1 = "Ez rá vall. Kivel harcolt? Emlékszik rá?";
			link.l1.go = "PZ_BasTerAlkash_4";
		break;
		
		case "PZ_BasTerAlkash_4":
			dialog.text = "Az ôrökkel, haver! Rájuk is összehúzta a szemét! Bár szerintem mindig így néz ki. Mit gondolsz?";
			link.l1 = "Nem tudom, haver. Folytasd csak. Azt hitték, hogy kém? Miért támadtak rá az ôrök?";
			link.l1.go = "PZ_BasTerAlkash_5";
		break;
		
		case "PZ_BasTerAlkash_5":
			dialog.text = "Ki tudja? Megpróbálták kitalálni, hogy mit keresett a városban...";
			link.l1 = "Szóval, letartóztatták? Vagy...";
			link.l1.go = "PZ_BasTerAlkash_6";
		break;
		
		case "PZ_BasTerAlkash_6":
			dialog.text = "Ha, nagy esélye van! Nem tudták elkapni. Legyilkolta az ôröket a városban és elmenekült a dzsungelbe. Több csoportot is utána küldtek, de egyik sem tért vissza. El tudod képzelni? Igazi erôdöt csinált abból a barlangból!";
			link.l1 = "Ez nem semmi. Pihenj egy kicsit, és próbáld meg elfelejteni. Azt hiszem, én most megyek - forog a fejem.";
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
			dialog.text = "Én magam még nem láttam - a kormányzó irodájában lógott, mi?! De a csapata nagy bulit rendezett itt.";
			link.l1 = "Tényleg?";
			link.l1.go = "Sotta2";
		break;
		
		case "Sotta2":
			dialog.text = "Mindenki azt mondja, hogy kereskedô. De a legénysége nem úgy nézett ki, mint a kocsmai csôcselék, én mondom neked! Olyan volt a tekintetük, mintha... mintha... hogy is mondják...?";
			link.l1 = "Már értem. Köszönöm a társaságot, haver. Vigyázz magadra.";
			link.l1.go = "exit_sit";
			
			npchar.questTemp.PZ_Sotta = true;
			pchar.questTemp.PZ_BelizAskCitizens = sti(pchar.questTemp.PZ_BelizAskCitizens) + 1;
			AddDialogExitQuest("PZ_LongwayBelizDialog");
		break;
		
		case "Lutter1":
			dialog.text = "Ünnepelek! És ki mondta, hogy egyedül vagyok? Itt vagy, haver! És ami Matt-et illeti, elôbb-utóbb meg kellett történnie.";
			link.l1 = "Mibôl gondolod ezt? Azt hallottam, hogy egy rendkívül szerencsés kalóz volt, akit Fortuna évek óta kegyben tart!";
			link.l1.go = "Lutter2";
		break;
		
		case "Lutter2":
			dialog.text = "Heh, nem csak Fortune volt, eh! Egy magányos kalóz volt, nem a Testvériség tagja! És azok nem tartanak sokáig... Bár hallottam, hogy a népek azt pletykálják, hogy egykor Levasseur szárnyai alatt állt.";
			link.l1 = "Így van, a magányosok nem tartanak sokáig. Nos, ünnepeljük meg. Mennem kell, haver.";
			link.l1.go = "exit_sit";
			
			npchar.questTemp.PZ_Lutter = true;
			pchar.questTemp.PZ_BelizAskCitizens = sti(pchar.questTemp.PZ_BelizAskCitizens) + 1;
			AddDialogExitQuest("PZ_LongwayBelizDialog");
		break;
		
		case "Sepp1":
			dialog.text = "Hé, igen, nem, még sosem láttam ôt. Ki az?";
			link.l1 = "Ô a szigetvilág egyik leggyorsabb hajójának, a briggnek a kapitánya 'Banten'. Hallottál már róla?";
			link.l1.go = "Sepp2";
		break;
		
		case "Sepp2":
			pchar.questTemp.PZ.TortugaHabitueBlock = true;
			
			dialog.text = "Ööö, nem, nem érdekelnek a hajók, pajtás, fúj! Iszunk még egy pohárral?";
			link.l1 = "Nekem nem. Úgysem azt kaptam, amit akartam.";
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
