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
            dialog.text = "Auswahl des Trunkenbold-Typs (Beta)";
			link.l1 = "Säufer";
			link.l1.go = "Beta_test_alc";
            link.l2 = "Kartenspieler";
			link.l2.go = "Beta_test_card";
			link.l3 = "Würfelspieler";
			link.l3.go = "Beta_test_dice";
		break;
		
		case "Beta_test_alc":
            dialog.text = "Besoffener ausgewählt";
			link.l1 = "Weiter";
			link.l1.go = "First time";
			npchar.quest.last_theme = 0;
		    npchar.quest.last_theme_game = 0;
		break;
		
		case "Beta_test_card":
            dialog.text = "Kartenspieler (30% sofort verärgert)";
			link.l1 = "Weiter";
			link.l1.go = "First time";
			npchar.quest.last_theme = 1;
		    npchar.quest.last_theme_game = 0;
		break;
		
		case "Beta_test_dice":
            dialog.text = "Würfelspieler (30% sofort verärgern)";
			link.l1 = "Weiter";
			link.l1.go = "First time";
			npchar.quest.last_theme = 1;
		    npchar.quest.last_theme_game = 1;
		break;
		
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = LinkRandPhrase("Ich bin vielleicht betrunken, aber kein Idiot. Wenn ich jetzt mit dir trinke, holen mich die Soldaten am nächsten Tag. Auf keinen Fall!","Ich bin kein Feind meiner eigenen Stadt. Ich trinke nicht mit dir!",""+GetSexPhrase("Kumpel","Fräulein")+", du solltest diesen Ort verlassen, solange du noch kannst...");
				link.l1 = RandPhraseSimple("Nun, wie du willst...","Heh, weißt du, ich sollte sowieso nicht viel trinken. Es ist nicht die richtige Zeit dafür."); 
				link.l1.go = "exit";
				break;
			}
			if(CheckAttribute(pchar,"questTemp.HabitueSpeakDisable") && rand(1) == 0) // если дуэлянт то каждый второй посылает нафик
			{
				dialog.text = "Ha, mis"+GetSexPhrase("ter","s")+", ich habe ganz sicher von dir schon gehört, he-he. Die Leute in den Tavernen sagen, dass du ein Spötter und ein Duellant bist. Ich sage es dir, unser Volk ist nicht leicht zu erschrecken, aber niemand will für einen Becher Rum sterben. Ich finde es sogar beängstigend, in deiner Nähe zu sitzen, also lasse ich es besser sein.";
				link.l1 = LinkRandPhrase("Auf Nimmerwiedersehen dann!","Verschwinde, während ich noch gut gelaunt bin...","Geh, geh! Verschwinde, Fischfutter!");
				link.l1.go = "exit";
				link.l2 = "Warte, ich wollte eine Frage stellen....";
				link.l2.go = "talk_habitue_duel";
				break;
			}
			
            ok = CheckFreeSitFront(npchar);
            
            dialog.text = "Steh nicht in meinem Licht, ich kann die Fliegen im Krug nicht sehen!";
            link.l1 = "Ich stehe nicht...";
		    link.l1.go = "exit";
		    if (!chrDisableReloadToLocation)
		    {
	            switch (npchar.quest.last_theme)
				{
					case "0": //пьяный.
						dialog.text = "Hicks! Oh, "+GetSexPhrase("Kumpel, du siehst aus wie ein echter erfahrener Seebär","Fräulein, du siehst aus wie eine echte erfahrene Seewölfin")+"! Vielleicht würden Sie mir ein Glas Rum kaufen?";
						link.l1 = "Mag sein, aber das bedeutet nicht, dass ich Fusel für Gesindel kaufe...";
						link.l1.go = "exit";

						if (makeint(pchar.money) >= 100 && ok) // только старые острова окучены на сесть
						{
							link.l2 = "Ich schließe mich gerne deiner Gesellschaft an.";
							link.l2.go = "talk_with_alchogol";
						}
						else
						{
	                        link.l2 = "Und warum ist das so?";
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
										Dialog.text = RandPhraseSimple("Ein Kartenspiel, vielleicht? Ein sehr interessantes Spiel!","Ich schlage vor, eine Partie Karten zu spielen. Was sagst du dazu?");
										link.l1 = "Und warum nicht? Sicher, lass uns spielen.";
										link.l1.go = "Cards_begin";
										link.l2 = "Und was sind die Regeln deines Spiels?";
										link.l2.go = "Cards_Rule";
										link.l3 = "Nicht jetzt.";
										link.l3.go = "exit";
									}
									else
					    			{
										Dialog.text = "Nein, ich spiele keine Karten mehr mit dir.";
						    			link.l1 = "Wie du sagst.";
						    			link.l1.go = "exit";
									}
			                        // Игра в карты boal 20/05/05 <--
		                        break;

								case 1:
								// кости
		    						// Игра в кости boal 13/07/05 -->
	                                if (CheckNPCQuestDate(npchar, "Dice_date_begin"))
									{
										Dialog.text = RandPhraseSimple("Ein Spiel mit Würfeln, vielleicht? Ein sehr interessantes Spiel!","Ich schlage vor, einige Würfel zu werfen. Was sagst du dazu?");
										link.l1 = "Und warum nicht? Sicher, lass uns spielen.";
										link.l1.go = "Dice_begin";
										link.l2 = "Und was sind die Regeln deines Spiels?";
										link.l2.go = "Dice_Rule";
										link.l3 = "Nicht jetzt.";
										link.l3.go = "exit";
									}
									else
					    			{
										Dialog.text = "Nein, ich würfle nicht mehr mit dir.";
					    				link.l1 = "Wie du sagst.";
					    				link.l1.go = "exit";
									}
			                        // Игра в кости boal 13/07/05 <--
			                        //navy --> Дуэли
									if (CheckAttribute(NPchar, "Quest.DiceCheats") && sti(NPchar.Quest.DiceCheats) >= 1) 
									{
					    				link.l9 = RandSwear()+" Du hast betrogen!!!";
					    				link.l9.go = "outraged";
									}
									//navy <--
			    				break;
	    					} 
						}
	        			else
	        			{
	                        dialog.text = RandPhraseSimple("Verschwinde von meinem Tisch! Sofort!"," Oh? Was? Wer ist das? Hic... Verschwinde!");
	                        link.l1 = RandPhraseSimple("Trinken verdammt deine sündige Seele! Komm zur Besinnung!","Sei nicht unhöflich zu mir.");
	        			    link.l1.go = "exit";
	        			    link.l2 = RandPhraseSimple("Hüte deine Zunge, du Tölpel! Oder ich bringe dir gute Manieren bei.","Was wäre, wenn ich dir jetzt eins auf den Kopf gebe, ich denke, das wird dir helfen nüchtern zu werden.");
	        	            link.l2.go = "tavern_keeper";
	        			}
					break;
				}
			}
			Diag.TempNode = "First time";
	    break;
	    
		case "talk_habitue_duel":
			dialog.text = "Ich sage Ihnen gar nichts, mis"+GetSexPhrase("ter","s")+"! Und ich glaube nicht, dass noch jemand mit dir sprechen wird, denn das bedeutet immer Ärger. Aber weißt du, die Leute neigen dazu, ein kurzes Gedächtnis zu haben, also könnten sie in einem Monat oder zwei deine Abenteuer vergessen, wenn du sie natürlich nicht noch einmal daran erinnerst, he-he! Auf Wiedersehen, mis"+GetSexPhrase("ter","s")+". ";
			link.l1 = "In Ordnung...";
			link.l1.go = "exit";
		break;
		
	    // карты -->
	    case "Cards_Rule":
   			dialog.text = CARDS_RULE;
			link.l1 = "Nun, dann lass uns anfangen...";
			link.l1.go = "Cards_begin";
			link.l3 = "Nein, das ist nichts für mich...";
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

			Dialog.text = "Lass uns zuerst die Wette festlegen (Wette eingeben).";
			link.l1 = "100";
			link.l1.edit = 1;
			link.l1.go = "Cards_Node_2";
			link.l3 = "Ich vermute, ich muss gehen.";
			link.l3.go = "exit_sit";
		break;
		
		case "Cards_Node_2":
			iLa_Puesta = GetStrSmallRegister(dialogEditStrings[1]);
            if (!CheckCardsGameSmallRate())
		    {
                dialog.text = "Du bist ein berüchtigter Betrüger. Ich werde nicht mit dir spielen.";
                link.l1 = "Es ist alles Lüge! Na ja, was auch immer.";
			    link.l1.go = "exit_sit";
			    break;
		    }
		    
			if (sti(PCHar.Money) < sti(iLa_Puesta)*3)
		    {
                dialog.text = "Ich sehe, du bist pleite, "+GetSexPhrase("Freund","Schätzchen")+". Komm zurück, wenn du reich wirst.";
                link.l1 = "Gut.";
			    link.l1.go = "exit_sit";
			    break;
		    }
		
			if (sti(NPChar.Money) < sti(iLa_Puesta)*3)
		    {
                dialog.text = "Ich habe bereits alles verloren, was ich hatte. Heute ist nicht mein Glückstag.";
                link.l1 = "Gut.";
			    link.l1.go = "exit_sit";
			    break;
		    }
		else
		{
			if(sti(iLa_Puesta) < 50)
			{
				dialog.text = "Lachst du über mich oder was?! Du willst für "+iLa_Puesta+" Pesos spielen?! Lass uns um vernünftige Einsätze spielen, oder ich bin raus!";
				link.l1 = "Ja, du hast Recht. Wir sollten die Wette ein bisschen erhöhen.";
				link.l1.go = "Cards_begin_2";
				link.l2 = "Ich habe es mir anders überlegt, ich spiele nicht.";
				link.l2.go = "exit_sit";
				break;
			}
			
			if(sti(iLa_Puesta) > 1000)
			{
				dialog.text = "Um so viel Geld spielen? Nein, ich passe, es sei denn, wir ändern den Einsatz.";
				link.l1 = "Ja, du hast recht. Wir sollten den Einsatz ein bisschen senken.";
				link.l1.go = "Cards_begin_2";
				link.l2 = "Eigentlich habe ich beschlossen, überhaupt nicht zu spielen.";
				link.l2.go = "exit_sit";
				break;
			}
			dialog.text = "In Ordnung, wir spielen um "+iLa_Puesta+" Münzen.";
			link.l1 = "Gib die Karten aus!";
			link.l1.go = "Cards_begin_go";
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
			pchar.GenQuest.Cards.iRate     = sti(iLa_Puesta);
            pchar.GenQuest.Cards.SitType   = true;
		}
		break;
		
		case "Cards_begin_2":
			dialog.text = "Also, was ist der Einsatz? (Gib Einsatz ein)";
			link.l1 = "50";
			link.l1.edit = 1;
			link.l1.go = "Cards_Node_2";
			link.l2 = "Ich glaube, ich werde doch nicht spielen...";
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
			link.l1 = "Nun, dann lass uns anfangen...";
			link.l1.go = "Dice_begin";
			link.l3 = "Nein, das ist nichts für mich...";
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
			Dialog.text = "Lass uns den Einsatz festlegen (Einsatz eingeben).";
			link.l1 = "50";
			link.l1.edit = 1;
			link.l1.go = "Dice_Node_2";
			link.l3 = "Ich denke, ich muss gehen.";
			link.l3.go = "exit_sit";
		break;

		case "Dice_Node_2":
			iLa_Puesta = GetStrSmallRegister(dialogEditStrings[1]);
            if (!CheckDiceGameSmallRate())
		    {
				dialog.text = "Du bist ein berüchtigter Betrüger. Ich werde nicht mit dir würfeln.";
                link.l1 = "Alles Lügen! Na ja, was auch immer.";
			    link.l1.go = "exit_sit";
			    break;
		    }

			if (sti(pchar.Money) < sti(iLa_Puesta)*6)
		    {
                dialog.text = "Ich sehe, du bist pleite, "+GetSexPhrase("Freund","Schätzchen")+". Komm zurück, wenn du reich bist.";
                link.l1 = "Gut.";
			    link.l1.go = "exit_sit";
			    break;
		    }
			
			if (sti(npchar.Money) < sti(iLa_Puesta)*6)
		    {
                dialog.text = "Ich habe bereits alles verloren, was ich hatte. Heute ist nicht mein Glückstag.";
                link.l1 = "Gut.";
			    link.l1.go = "exit_sit";
			    break;
		    }
		else
		{
			if(sti(iLa_Puesta) < 50)
			{
				dialog.text = "Lachst du über mich oder was?! Du willst für "+iLa_Puesta+" Pesos pro Würfel spielen?! Spielen wir um vernünftige Einsätze, oder ich bin raus!";
				link.l1 = "Ja, du hast recht. Wir sollten den Einsatz etwas erhöhen.";
				link.l1.go = "Dice_begin_2";
				link.l2 = "Ich habe es mir anders überlegt, ich spiele nicht.";
				link.l2.go = "exit_sit";
				break;
			}
			
			if(sti(iLa_Puesta) > 1000)
			{
				dialog.text = "Um so viel Geld würfeln? Nein, ich verzichte, es sei denn, wir ändern den Einsatz.";
				link.l1 = "Ja, du hast recht. Wir sollten den Einsatz ein bisschen senken.";
				link.l1.go = "Dice_begin_2";
				link.l2 = "Eigentlich habe ich beschlossen, überhaupt nicht zu spielen.";
				link.l2.go = "exit_sit";
				break;
			}
			dialog.text = "Gut, wir spielen um "+iLa_Puesta+" Münzen pro Würfel.";
			link.l1 = "Lass uns loslegen!";
			link.l1.go = "Dice_begin_go";
			pchar.GenQuest.Dice.npcharIdx = npchar.index;
			pchar.GenQuest.Dice.iRate     = sti(iLa_Puesta);
            pchar.GenQuest.Dice.SitType   = true;
		}
		break;
		
		case "Dice_begin_2":
			dialog.text = "Also, was ist der Einsatz? (Einsatz eingeben)";
			link.l1 = "50";
			link.l1.edit = 1;
			link.l1.go = "Dice_Node_2";
			link.l2 = "Ich glaube, ich werde doch nicht spielen...";
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
			dialog.text = "Nun, h-hicks! Alles ist gut. Hicks! Du siehst es nicht kommen. Hi-icks! Dieser Rum ist gut. Jamaika schwarzer Rum. hicks!\nHier, komm her und gieß ein!";
			link.l1 = "In Ordnung, warum nicht.";
			link.l1.go = "talk_with_alchogol_song_2";
			link.l2 = "Entschuldigung Freund, ich muss gehen.";
			link.l2.go = "exit";
		break;
		
		case "talk_with_alchogol_song_2":
			dialog.text = "Krüge und Gesichter kommen und gehen... Hicks... Bis ich auf den Boden falle. Ich trinke die ganze Zeit... Hicks! Wo ist der Schnaps... Und was ist der Reim...";
			link.l1 = "Der Schnaps ist hier und die Mädchen sind fein, alle wollen einen Freibeuter, aber nur der Rum scheint mein zu sein.";
			link.l1.go = "talk_with_alchogol_song_3";
			link.l2 = "Ich habe keine Zeit dafür.";
			link.l2.go = "exit";
		break;
		
		case "talk_with_alchogol_song_3":
			dialog.text = "Wenn du traurig bist, versuch nicht zu denken, komm vorbei, und lasst uns trinken! Alles wird sicher gut, ich bin dein Freund, und du bist meiner!";
			link.l1 = "Einen Freund zu haben ist wahrlich großartig, wenn du weg bist, wird er warten, mit einem Freund gibt es keinen Hass, aber wenn der Rum weg ist, gibt es nur eine Debatte. Also lasst uns trinken, Kumpel, bevor ich gehe und zu spät komme... ";
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
			dialog.text = LinkRandPhrase("Hicks! Jetzt ist es besser! Das ist sicherlich besser! Also? Kaufen Sie mir etwas Rum oder was?","Setz dich, "+GetAddress_Form(npchar)+", lass uns einen Becher guten alten jamaikanischen Rum kippen. Das ist nie schlecht für die Gesundheit. Und wenn du interessiert bist, was los ist - du wirst nie einen besseren Ort als diese Taverne finden, das versichere ich dir. Ein wenig Geld, ein paar Becher anständigen Rum - und du wirst alles wissen, was du wissen musstest, und noch mehr, vertraue einem alten Stammgast...","Heh, bitte, setz dich, "+GetSexPhrase("guter Freund","Fräulein")+", lasst uns einen Trinken... Warum nicht in guter Gesellschaft trinken? Man kann viel Interessantes hören, wenn man geduldig ist und langsam, in kleinen Schlucken trinkt... Es gibt Kapitäne, die mit ihren Abenteuern prahlen, es gibt viele andere, die wichtige Dinge ausplaudern, wenn sie sich nicht mehr kontrollieren können... Viele Leute verbringen dort ihre Zeit, und viele haben etwas zu erzählen, glaub mir, "+GetSexPhrase("guter Freund","Fräulein")+".");
			link.l1 = "Und warum nicht! Wirt! Rum, für uns beide!";
			link.l1.go = "sit_2";
		break;

		// Церковный генератор. Квест №2 -->
		case "Alcogol_GenQuest_Church_2_1":
			dialog.text = "Sicher! Hast du gehört... Banditen plündern sogar Kirchen!";
				link.l1 = "Nun, das klingt wie Piraten, wer sonst...";
				link.l1.go = "Alcogol_GenQuest_Church_2_2";
				DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.AskPeople");
				DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.AskBarmen");
				DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.AskAlcash");
			break;
			
		case "Alcogol_GenQuest_Church_2_2":
			dialog.text = "Welche Piraten? Nur die gewöhnlichen Landratten, und natürlich die verdammten Lokalen... Wenn es Besucher wären, hätten sie nicht gewusst, wann die Kirchentruhen voll sind. Und sie würden sich kaum in dieses Durcheinander einmischen.";
				link.l1 = "Wagemutige Kerle, das ist sicher. Sie öffneten so galant einen fadenscheinigen Türriegel...";
				link.l1.go = "Alcogol_GenQuest_Church_2_3";
			break;
			
		case "Alcogol_GenQuest_Church_2_3":
			dialog.text = "A-ha. Und auch kluge. Wer würde sich derart bloßstellen?";
				link.l1 = "Wahr. Die ganze Gemeinde hat Geld gespart, um es der Kirche zu spenden, und jetzt haben diese klugen Kerle ihr Vermögen daraus gemacht? Sicherlich werden sie gefangen genommen. Die ganze Welt wird jetzt nach ihnen suchen.";
				link.l1.go = "Alcogol_GenQuest_Church_2_4";
			break;
			
		case "Alcogol_GenQuest_Church_2_4":
			dialog.text = "Wohl kaum. Wer wird nach ihnen suchen? Sie haben einfach die Kirche ausgeraubt und die Stadt verlassen, fort mit dem Wind. Der Dschungel ist groß, sehr groß, du würdest bis zum Jüngsten Tag nach ihnen suchen. Und nach ein paar Monaten werden die Leute es einfach vergessen, merke dir meine Worte!";
				link.l1 = "Ich glaube nicht. Solche Dinge können nicht vergeben werden.";
				link.l1.go = "Alcogol_GenQuest_Church_2_5";
			break;
			
		case "Alcogol_GenQuest_Church_2_5":
			dialog.text = "Ein Menschenerinnerung ist wie ein sinkendes Boot. Die Leute werden vergessen und vergeben. Aber Gott?! Er sieht alles. Vor ihm musst du Angst haben. Ich sage es dir, vor zehn Jahren ist meinem alten Kumpel etwas Schreckliches passiert. Er hatte auch keinen Respekt vor dem Schöpfer und wäre fast direkt zum Seeteufel gegangen...";
				link.l1 = "Entschuldigung Freund, ich muss gehen. Wir werden ein anderes Mal über deinen Kumpel sprechen. Bis dann.";
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
			Log_TestInfo("Die Banditen, welche die Kirche überfallen haben, sollten irgendwo im - " + sGenLocation + " sein. Zeit diese zu suchen - 1 Tag");
			sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "2");
			break;
		// <-- Церковный генератор. Квест №2
		//--> работорговец
			case "Jamaica_ratH_1":
				dialog.text = "Oh Francois! Sicher, ich erinnere mich an diesen Kerl... Nein, ich weiß es nicht. Aber, weißt du, du kannst unsere Kellnerin über ihn fragen. Solange er hier gelebt hat, hat sie jede Nacht mit ihm verbracht. Eine Schlampe ist sie, das ist sicher. Vielleicht hat er ihr etwas ausgeplaudert.";
				link.l1 = "Danke für den Rat, Kumpel. Ich werde mit ihr reden.";
				link.l1.go = "exit_sit";
				pchar.questTemp.Slavetrader = "FindRatJamaica_W";
			break;
			
			case "EscapeSlave_Villemstad_H1":
				dialog.text = "Ja, sehr seltsame Dinge können manchmal auf offener See passieren. Auf meiner letzten Reise habe ich etwas wirklich ...";
				link.l1 = "Mach weiter, erzähl es mir, übertreib es nur nicht zu sehr. Ich hole dir derweil noch mehr Rum.";
				link.l1.go = "EscapeSlave_Villemstad_H2";
			break;
			
			case "EscapeSlave_Villemstad_H2":
				dialog.text = "Ich schwöre bei Gott, "+GetSexPhrase("edler Herr","edle Dame")+" - Ich habe es mit meinen eigenen Augen gesehen... Ein Schiff segelte, aber anstelle von Matrosen gab es riesige Affen... oder Makaken... Affen, weißt du.";
				link.l1 = "Was?! Sag mir, Freund, trinkst du auch während der Wache?";
				link.l1.go = "EscapeSlave_Villemstad_H3";
			break;
			
			case "EscapeSlave_Villemstad_H3":
				dialog.text = "Bei Gott, ich lüg nicht! Hast du noch nie vom Affenshrimp gehört? Verdammt, Shrimp, ha-ha! ... Das Affenschiff.";
				link.l1 = "Welches Affenschiff?";
				link.l1.go = "EscapeSlave_Villemstad_H4";
			break;
			
			case "EscapeSlave_Villemstad_H4":
				dialog.text = "Oh-hoe, ich sage, dass ich es mit meinen eigenen Augen gesehen habe. Es stürmte. Man konnte nichts sehen, und dann tauchte das Schiff aus dem Nichts auf. Zerrissene Segel. Sie hatte ihr Vorsegel ebenso wie das Großsegel gebrochen, und verdammt noch mal, sie hatte alles gebrochen! Und doch stürmte sie gegen den Wind!\nUnd es waren Affen an Deck... viele von ihnen wie... eine Robbenkolonie! Und ein reiner Gorilla stand am Ruder! Neun Fuß, rotes Hemd und Haifischzähne anstelle des Kreuzes auf seiner Brust... Die Augen sind rot, die Reißzähne blitzen, es sah uns und schrie etwas...";
				link.l1 = "Du lügst, dass sich die Balken biegen, Freund. Weißt du, man sieht Dinge, wenn man betrunken ist. Als nächstes erzählst du mir, dass sie der Fliegende Holländer war.";
				link.l1.go = "EscapeSlave_Villemstad_H5";
			break;
			
			case "EscapeSlave_Villemstad_H5":
				dialog.text = "Nein, sie war kein Holländer. Ich sage Ihnen die Wahrheit! Es war eine Bark, und am Heck gab es eine Inschrift - "+pchar.questTemp.Slavetrader.ShipName+".";
				link.l1 = "Verdammt noch mal! Ich glaube, ich weiß, von welchen 'Affen' du gesprochen hast. Tatsächlich kann Rum Zungen lösen - man muss nur zuhören...";
				link.l1.go = "EscapeSlave_Villemstad_H6";
			break;
			
			case "EscapeSlave_Villemstad_H6":
				dialog.text = "Siehst du - Ich habe es dir gesagt! Und du hast mir nicht geglaubt!.. Also gut, lass uns noch einen letzten Becher leeren, und dann bin ich bereit zu gehen.";
				link.l1 = "Also gut, danke für die interessante Geschichte. Ich muss gehen. Viel Glück, Kumpel.";
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
			dialog.text = "Nein, Kapitän. Ein Seemannsleben ist nichts für mich. Wissen Sie, ich hatte auch einmal ein Schiff, aber... Ich hatte wirklich großes Pech.";
			link.l1 = "Hört zu - Ich habe ein ungewöhnliches Schiff vor Anker gesehen - 'Meifeng' ist ihr Name. Ich habe noch nie ein solches Schiff gesehen. Wer ist der Besitzer? Vielleicht steht es zum Verkauf? Ich würde einen Blick darauf werfen.";
			link.l1.go = "Lucas_Tavern_1";
		break;
		
		case "Lucas_Tavern_1":
			dialog.text = "Ha! Wohl kaum, Kapitän. Ich glaube nicht, dass der Chinese sein Schiff an dich oder sonst jemanden verkaufen wird.";
			link.l1 = "Ein Chinese? Es gibt Chinesen auf Curacao? Und sogar einen Kapitän mit sein eigenes Schiff?";
			link.l1.go = "Lucas_Tavern_2";
		break;
		
		case "Lucas_Tavern_2":
			dialog.text = "Es gibt sie, wie Sie sehen können. Aber das ist eigentlich nicht sein Schiff - es gehört der Handelsgesellschaft. Sie sagen, Mynheer Rodenburg, der stellvertretende Direktor und jetzt amtierende Gouverneur, besitzt es.";
			link.l1 = "Also ist Matthias Beck im Ruhestand?";
			link.l1.go = "Lucas_Tavern_3";
		break;
		
		case "Lucas_Tavern_3":
			dialog.text = "Ha! Herr, Sie sollten wirklich öfter an Land gehen - oder zumindest für die Nachrichten sorgen. Matthias Beck wurde entlassen und hinter Gitter gebracht, bis alle Umstände geklärt sind.";
			link.l1 = "Was du nicht sagst! Tatsächlich, ich verbringe zu viel Zeit auf See. Und wann ist das passiert?";
			link.l1.go = "Lucas_Tavern_4";
		break;
		
		case "Lucas_Tavern_4":
			dialog.text = "Eigentlich erst vor ein paar Tagen. Eine Kurier-Brigg kam im Hafen an. Sie war nicht im besten Zustand, sie hat offensichtlich an einem heftigen Kampf teilgenommen. Der Kapitän ging direkt zu Mynheer Rodenburg mit seinem Bericht, und nur wenige Stunden später wurde Matthias Beck von Mynheer Rodenburg und dem Kommandanten auf Verdacht der Zusammenarbeit mit dem englischen Geheimdienst festgenommen.";
			link.l1 = "Du erzählst schreckliche Dinge. Wie kann ein Gouverneur von Curacao ein englischer Spion sein?";
			link.l1.go = "Lucas_Tavern_5";
		break;
		
		case "Lucas_Tavern_5":
			dialog.text = "Ehrlich gesagt, ich kann es kaum glauben. Ich habe gehört, dass bald der Direktor der Gesellschaft, Peter Stuyvesant selbst, hier eintreffen wird. Anscheinend wird er die Untersuchung persönlich durchführen.";
			link.l1 = "Dann liegst du richtig. Es kann riskant sein, Mynheer Rodenburg zu dieser Zeit zu belästigen.";
			link.l1.go = "Lucas_Tavern_6";
		break;
		
		case "Lucas_Tavern_6":
			dialog.text = "Guter Gedanke, Kapitän! Umso mehr, dass die 'Meifeng' gerade beladen wird. Sie ist gerade von der Reise zur Südküste des Main zurückgekehrt und wird bald wieder in See stechen. Und, ich sage dir, dort geschehen seltsame Dinge. Holländische Matrosen und Wachen der Kompanie wurden vom Dienst befreit und eine andere Mannschaft wird zusammengestellt. Und ich schwöre bei allen Rumtassen, die ich in meinem Leben getrunken habe, diese neuen Freiwilligen sind ganz anders, alles Piraten, Banditen und Halsabschneider!";
			link.l1 = "Ein Wunder, tatsächlich! Nun, es ist eine Schande! So ein schönes Schiff... Nun, das Schicksal hat es anders bestimmt... Danke für die interessante Geschichte und die Neuigkeiten! Es war ein Vergnügen, mit dir zu sprechen!";
			link.l1.go = "Lucas_Tavern_7";
		break;
		
		case "Lucas_Tavern_7":
			dialog.text = "Nun, danke für die Gesellschaft und den Rum, Kapitän! Schau mal wieder vorbei!";
			link.l1 = "Sicher, werde ich!";
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
			if(bImCasual) NewGameTip("Erkundungsmodus: Der Timer ist nicht deaktiviert. Halten Sie die Frist ein!");
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
				dialog.text = "Ha! "+pchar.GenQuest.FindFugitive.Name+"? Ich weiß, ich weiß... Er ist sehr zurückgezogen, dieser Kollege von dir. Ein Einzelgänger, sozusagen. Er segelt den ganzen Tag bis in die Nacht hinein mit seinem Langboot entlang der Küste der Insel. Die Leute denken, er ist ein Fischer, aber eigentlich ist er ein Perlentaucher... He-he! Ich weiß es verdammt sicher!";
				link.l1 = "Heh! Also... kannst du mir sagen, wo ich ihn finden kann?";
				link.l1.go = "FindFugitiveHb_1";
			}
			else
			{
				dialog.text = ""+pchar.GenQuest.FindFugitive.Name+"? Nein, ich schwöre, ich habe noch nie von ihm gehört... Aber du - Hic! Du kannst unseren Barkeeper fragen - er muss es sicher wissen!";
				link.l1 = "Hmm... Gut, ich werde mich noch etwas umhören. Nun, Kumpel, danke für die Gesellschaft. Bis dann!";
				link.l1.go = "exit_sit";
			}
		break;
		
		case "FindFugitiveHb_1":
			dialog.text = "Natürlich kann ich! Jeden Morgen kann er am Ufer gefunden werden, bei "+XI_ConvertString(pchar.GenQuest.FindFugitive.Shore+"Gen")+". Kommen Sie so früh wie möglich, sonst wird er die Segel setzen und Sie müssen bis zum nächsten Morgen warten.";
			link.l1 = "Danke! Du hast mir sehr geholfen, Freund! Auf Wiedersehen!";
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
			dialog.text = "Er hing in unserer Werft herum und fragte die Schiffsbauer dies und das. Und das hat ihm einen üblen Streich gespielt. Einige Leute haben den Kommandanten über verdächtige Leute, die in der Stadt herumlungerten, alarmiert, also hat er ihn festgenommen, und dann stellte sich heraus, dass er überhaupt kein Händler war.";
			link.l1 = "Ich nehme an, er wollte irgendein Geheimprojekt deines Schiffbauers stehlen?";
			link.l1.go = "trial_spy_1";
		break;
		
		case "trial_spy_1":
			dialog.text = "Wer weiß? Aber ich bin mir ziemlich sicher, dass er sich in erster Linie für die Galeone 'Alacantara' interessiert hat! Hic! Ich kann darauf schwören! Dieses Schiff wird vom Señor Gouverneur selbst ausgestattet, also wette ich, dass dieser Schurke versucht hat, etwas über sie herauszufinden.";
			link.l1 = "Ha! Das ist ziemlich wahrscheinlich. Sicherlich wird der Gouverneur sie mit etwas Wertvollem beladen...";
			link.l1.go = "trial_spy_2";
		break;
		
		case "trial_spy_2":
			dialog.text = "Das versteht sich von selbst! Das sollte wirklich etwas Beachtenswertes sein, sag ich dir! Oh, und die Leute sagten, dass die Fischer ein ausländisches Kriegsschiff in diesen Gewässern gesehen haben... wahrscheinlich eine Fregatte. Vielleicht ist das der Ort, von dem dieser Spion gekommen ist?";
			link.l1 = "Ja, das kann sein... In Ordnung, Kumpel, danke für die Gesellschaft, aber ich muss gehen!";
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
				dialog.text = "Auf Ihre Gesundheit und Ihre Großzügigkeit!";
				link.l1 = "Kumpel, hast du einen Chinesen in der Stadt gesehen?";
				link.l1.go = "PZ_BasTerAlkash_1";
				break;
			}
			// <== Квест "Путеводная звезда" - Sinistra
			
			dialog.text = LinkRandPhrase("Du bist ein "+GetSexPhrase("echter Freund","tolles Mädel")+"! Schön dich zu treffen! Prost!","Hicks! Das ist toller Rum! Hicks... Prost!","Auf Ihre Gesundheit und auf Ihre Großzügigkeit!");
			link.l1 = "Heh, das ist wirklich starker Rum. Also gut, ich muss gehen. Viel Spaß noch!";
			link.l1.go = "exit_sit";
			if (makeint(pchar.money) >=2)
			{
				link.l2 = "Noch eine Tasse, macht es dir etwas aus?";
				link.l2.go = "sit_3";
			}

			link.l4 = LinkRandPhrase("Es fühlt sich an, als hätte ich eine Ewigkeit auf See verbracht. Gibt es Neuigkeiten?","Was sagen die Leute? Natürlich werde ich dir Drinks kaufen.","Sag mir, Kumpel, welche Geschichten sind jetzt in Tavernen beliebt?");
			link.l4.go = "rumours_habitue";
		break;

		case "sit_3":
			int iSituation;
			if(IsEquipCharacterByArtefact(pchar, "totem_01")) iSituation = makeint(rand(3));
			else iSituation = makeint(rand(5));
			switch (iSituation)
			{
				case 0:
					dialog.text = "Oh! Eine großartige Idee!";
					link.l1 = "Wirt! Mehr Rum!";
					link.l1.go = "sit_2";
				break;

				case 1:
					dialog.text = "Für dich! Oh, Hölle! Wer ist das?";
					link.l1 = "Hä? Was? Wo? Ich muss Dinge sehen.";
					link.l1.go = "sit_2";// to_do "sit_case_5_exit";
				break;
				
                case 2:
	         		dialog.text = "Lass uns trinken, dann! Noch einen?";
					link.l1 = "Nur zu!";
					link.l1.go = "sit_2";
                break;				
				
				case 3:
					if(rand(1) == 0)
					{
						dialog.text = RandPhraseSimple("He, du, "+GetAddress_Form(NPChar)+", du denkst sicher, dass dich alle bewundern, nicht wahr? Nun, wenn du mich fragst, bist du nur ein gewöhnlicher Räuber!.. Und Mörder! 'Edler Pirat'! Ha! Ein Bandit ist ein Bandit... Hic... Sei es an Land oder auf See..","Hicks! "+GetSexPhrase("Scho... Schurke","Dre... Drecksau")+"! Du willst, dass ich trinke, bis ich ohnmächtig werde - hic - und dann stiehlst du all mein Geld!");
						link.l1 = "Ich sehe, du hast schon genug getrunken... Geh es ausschlafen... Und ich muss gehen...";
						link.l1.go = "exit_sit";						
						link.l2 = "Ich mag deinen Ton nicht, Kumpel. Halt deine Klappe, klar?";
						link.l2.go = "sit_case_2_enemy";
						link.l3 = "Wen hast du gerade einen Banditen genannt, du Landratte?! Mal sehen, was du sagst, wenn du ein Loch im Bauch hast!";
						link.l3.go = "sit_case_2_enemy2";
					link.l4 = "Beruhige dich! Hast du vergessen? Ich bin dein einziger wahrer Freund!";
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
							dialog.text = RandPhraseSimple("Warum starrst du mich an? Du wirst warten, bis ich ohnmächtig werde - hic - und dann wirst du all mein Geld stehlen! Woher kommt dieser ganze Pöbel?! Hic... Kein Platz für anständige Leute in dieser Kneipe?","Respektierst du mich?.. Ja, du! Respektierst du mich?! Pass nur auf dich auf... Ich bin nicht derjenige, mit dem man sich anlegt... Ein Schlag zwischen die Augen... Und du bist so gut wie tot...");
							link.l1 = "Kumpel, du bist betrunken wie ein Schwein. Geh nach Hause und schlaf es aus... Und ich muss auch gehen...";	
							link.l1.go = "exit_sit";
							link.l2 = "Zügle dein Temperament, Kumpel. Pass auf, mit wem du redest.";
							link.l2.go = "sit_case_2_enemy1";
							link.l3 = "Was hast du gerade gesagt?! Ich werde dir eine Lektion erteilen!";
							link.l3.go = "sit_case_2_enemy2";
							link.l4 = "Beruhige dich! Hast du mich vergessen? Ich bin dein einziger wahrer Freund!";
							link.l4.go = "sit_case_2_friend";	
						//}
					}
				break;

				case 4:
					dialog.text = "Hör zu! Du bist ein guter Mann! Vielleicht... hilfst du mir bei einer Angelegenheit?";
					link.l1 = "Nein, ich glaube, ich muss jetzt gehen.";
					link.l1.go = "exit_sit";
					link.l2 = "Sicher! Hicks! Wir sind Freunde... oder nicht? Hicks!";
					link.l2.go = "sit_case_3";
				break;

				case 5:
					if (GetSummonSkillFromName(pchar, SKILL_SNEAK) > rand(110) || CheckAttribute(pchar, "questTemp.Sharlie.Lock"))
					{
						dialog.text = "...Und dann habe ich sein S-schwert an der K-klinge gefangen...";
						link.l1 = "...und dann sagte sie...";
						link.l1.go = "sit_2";
					}
					else
					{
						dialog.text = "...Und dann fing ich s-sein Säbel mit der K-Klinge...";
						link.l1 = "...hic! ...und dann hat sie gesagt...";
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
			dialog.text = "Der P-Punkt ist, dass einer der S-Soldaten mich beleidigt hat. D-Das ist es!";
			link.l1 = "Ein S-Soldat? N-Nein, ich glaube, ich verzichte.";
			link.l1.go = "exit_sit";
			link.l2 = "Beruhige dich! Hast du mich vergessen? Ich bin dein einziger wahrer Freund!";
			link.l2.go = "sit_2";
		break;

		case "sit_case_2_friend":
			dialog.snd = "Voice\HADI\HADI038";
			dialog.text = "Du? Was für ein Freund bist du? N-nein! Du... du willst mich töten! D-Das ist es!";
			link.l1 = "Nun, sicherlich hast du schon genug getrunken. Auf Wiedersehen.";
			link.l1.go = "exit_sit";
			link.l2 = "Was? Ich werde dir beweisen, dass ich dich n-nicht töten werde! Ich... Ich werde dir die Hand abhacken!... Ohne... sie kannst du nicht getötet werden!... Hic!";
			link.l2.go = "sit_case_2_friend_2";
		break;

		case "sit_case_2_friend_2":
			dialog.snd = "Voice\HADI\HADI039";
			dialog.text = "Aaaah! Nimm "+GetSexPhrase("ihn","sie")+" weg von mir!";
			link.l1 = "Beruhige dich... hicks... Es wird nicht wehtun!... Es ist weniger schmerzhaft als eine Rasur!";
			link.l1.go = "tavern_keeper";
		break;

		case "sit_case_2_enemy":
			dialog.snd = "Voice\HADI\HADI040";
			dialog.text = "Versuch nicht, mir Angst zu machen! Hicks! Ich lasse mich nicht so leicht einschüchtern!.. Und du - du solltest am Galgen hängen... Mit all deinesgleichen - hicks! Du kannst deine Federn aufplustern, so viel du willst - aber du stinkst immer noch nach faulem Fisch! Und ich werde meine Zunge nicht hüten, wenn ich - hicks! - mit deinesgleichen spreche! Ihr ekelt mich alle an!";
			link.l1 = "Argh, warum rede ich überhaupt mit so einem Trunkenbold... Ich glaube, ich gehe mal an die frische Luft...";
			link.l1.go = "exit_sit1";
			link.l2 = "Du bist zu frech, Kumpel. Ich werde deine Worte zurück in deinen Hals stecken!";
			link.l2.go = "sit_case_2_enemy3";
		break;

		case "sit_case_2_enemy1":		
			dialog.snd = "Voice\HADI\HADI040";
			dialog.text = "Was?! Ich werde dich mit meinen eigenen Händen erwürgen! Hic... Niemand ist mir bisher entkommen - hic!";
			link.l1 = "Bist du nicht ein besoffenes Schwein? Einen so schönen Abend zu verderben... Gut, geh und fang deine Kakerlaken - und ich bin weg.";
			link.l1.go = "exit_sit1";
			link.l2 = RandSwear()+"Ich sehe, du wirst nicht ruhig werden. Nun, dann ist eine Lektion in guten Manieren fällig.";
			link.l2.go = "sit_case_2_enemy3";
		break;
		
		case "sit_case_2_enemy2":	
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			if(rand(1) == 0)
			{
				dialog.text = LinkRandPhrase("Komm näher, du Schurke! Du wirst bekommen, was du verdienst!",RandSwear()+"Ich werde dir geben, was du verdienst!","Ha! Na gut, Seehund - mal sehen, wie du an Land zurechtkommst!");
				link.l1 = RandPhraseSimple(RandPhraseSimple("Ich schwöre, du wirst es bereuen!","Ich werde deine freche Zunge bis zu den Ohren kürzen!"),RandPhraseSimple("Ich werd' dich aufschlitzen wie ein Schwein, vom Hintern bis zu deinem Dreckloch, das manche Maul nennen!","Ich schwöre, ich werde dich zum Schweigen bringen!"));
				link.l1.go = "fight_right_now";
			}
			else
			{
				dialog.text = "He, Jungs! Lasst uns diesen Müll aus unserer Stadt fegen!";
				link.l1 = RandPhraseSimple(RandSwear()+"Sagt eure Gebete, ihr Bastarde!","Oh, also bist du nicht allein?! Nun, gut für dich - du wirst Gesellschaft in der Hölle haben!");
				link.l1.go = "fight_right_now_1";
			}
		break;
		
		case "sit_case_2_enemy3":	
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
			if(rand(1) == 0)
			{
				dialog.text = LinkRandPhrase("Komm näher, du Schurke! Du wirst bekommen, was du verdienst!",RandSwear()+"Ich werde dir geben, was du verdienst!","Ha! Also gut, Seehund - mal sehen, wie du dich an Land schlägst!");
				link.l1 = RandPhraseSimple(RandPhraseSimple("Ich schwöre dir, du wirst es bereuen!","Ich werde deine unflätige Zunge bis zu den Ohren kürzen!"),RandPhraseSimple("Ich werde dich wie ein Schwein aufschlitzen, von deinem Arsch bis zu deinem Scheißloch, das einige Mund nennen!","Ich schwöre, ich bringe dich zum Schweigen!"));
				link.l1.go = "fight_right_now";
			}
			else
			{
				dialog.text = "He, Jungs! Lasst uns diesen Abschaum aus unserer Stadt fegen!";
				link.l1 = RandPhraseSimple(RandSwear()+"Sagt eure Gebete, ihr Bastarde!","Oh, also bist du nicht allein?! Nun, gut für dich - du wirst Gesellschaft in der Hölle haben!");
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
			dialog.text = "He, ich habe etwas nicht verstanden! Kaum bin ich um die Ecke gegangen, ist irgendein neuer Anfänger an meiner Stelle gelandet. Hau ab hier!";
			link.l1 = "Es ist immer so: Man setzt sich nur an den Tisch und es stellt sich heraus, dass er schon besetzt ist... Halten Sie Ihren Platz, ich wollte ohnehin gerade gehen.";
			link.l1.go = "bad_habitue1";
			link.l2 = "Noch ein Satz wie dieser aus deinem dreckigen Mund und es wird das Letzte sein, was du in deinem Leben sagst, verstanden?";
			link.l2.go = "bad_habitue2";
			link.l3 = "Ich weiß nicht, ob das wirklich dein Platz war, aber ich lasse nicht zu, dass du so mit mir sprichst. Achte auf deine Worte.";
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
				dialog.text = LinkRandPhrase("Los geht's, Schurken! Gleich bekommt ihr eure Portion!",RandSwear()+"Jetzt werde ich dich richtig ausplündern!","Ha! Komm schon, Seemann - lass uns sehen, was du an Land kannst!");
				link.l1 = RandPhraseSimple(RandPhraseSimple("Ich schwöre, du wirst das bereuen!","Ich werde deine verdammte Zunge kürzen!"),RandPhraseSimple("Ich werde dich wie ein Schwein ausnehmen, von deinem Hintern zu deinem Scheißloch, das manche Mund nennen!","Ich schwöre, ich bringe dich zum Schweigen!"));
				link.l1.go = "fight_right_now";
			}
			else
			{
				dialog.text = "Los, Jungs! Lasst uns diesen Abschaum aus unserer Stadt fegen!";
				link.l1 = RandPhraseSimple(RandSwear()+"Betet, ihr Bastarde!","Oh, du bist nicht allein! Nun, du wirst Gesellschaft in der Hölle haben!");
				link.l1.go = "fight_right_now_1";
			}
		break;
		
		case "bad_habitue3":
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			if(rand(1) == 0)
			{
				dialog.text = LinkRandPhrase("Los, ihr Halunken! Ihr werdet gleich kriegen was ihr verdient!",RandSwear()+"Jetzt werde ich dich richtig ausziehen!","Ha! Los, Seemann - lass uns mal sehen, was du an Land kannst!");
				link.l1 = RandPhraseSimple(RandPhraseSimple("Ich schwöre, du wirst das bereuen!","Ich werde deine verdammte Zunge kürzen!"),RandPhraseSimple("Ich schlitz dich auf wie ein Schwein, von deinem Arsch zu dem Scheißloch, das einige Mund nennen!","Ich schwöre, ich bringe dich zum Schweigen!"));
				link.l1.go = "fight_right_now";
			}
			else
			{
				dialog.text = "Los Leute! Lasst uns diesen Abschaum aus unserer Stadt fegen!";
				link.l1 = RandPhraseSimple(RandSwear()+"Betet, ihr Bastarde!","Oh, du bist nicht allein! Nun, du wirst Gesellschaft in der Hölle haben!");
				link.l1.go = "fight_right_now_1";
			}
		break;
		
		//--> Sinistra Длинные тени старых грехов
		case "DTSG_NightIskat":
			dialog.text = "N-natürlich, wir kennen uns alle! Warum fragst du?";
            link.l1 = "Ich wollte den Geldverleiher besuchen und habe herausgefunden, dass er sein altes Haus verkauft hat. Weißt du, wo er jetzt wohnt?";
            link.l1.go = "DTSG_NightIskat_2";
		break;
		
		case "DTSG_NightIskat_2":
			dialog.text = "Warum brauchst du ihn um diese Stunde, hicks? Besuche einfach morgens die Bank!";
            link.l1 = "Ich brauche dringend Geld. Lass den Geldsack mal dafür arbeiten! Ihre Art nennt uns immer Schmarotzer, die nur betteln, klagen und nie zurückzahlen, was wir schulden.";
            link.l1.go = "DTSG_NightIskat_3";
		break;
		
		case "DTSG_NightIskat_3":
			dialog.text = "Ha-ha-ha, hic, ja, lass ihn arbeiten! Weißt du, wo unser glorreicher Kapitän Fleetwood gelebt hat?";
            link.l1 = "Natürlich, wer kennt Richard nicht. Jetzt wohnt dort der Bankier?";
            link.l1.go = "DTSG_NightIskat_4";
		break;
		
		case "DTSG_NightIskat_4":
			dialog.text = "Du hast recht. Wenn du dort bist, Freund - sag ihm, er ist zu überheblich geworden.";
            link.l1 = "Heh-heh, das werde ich sicher tun. Lebewohl.";
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
			dialog.text = "Ha-ha-ha, habe ich einen Chinesen gesehen? Wir haben ihn alle gesehen!";
			link.l1 = "Was ist so lustig? Ich rede nicht von einem reisenden Zirkus, falls du das meinst. Ich rede von einem Kämpfer, einem Marineoffizier.";
			link.l1.go = "PZ_BasTerAlkash_2";
		break;
		
		case "PZ_BasTerAlkash_2":
			dialog.text = "Ah, ich verstehe, was du meinst! Ja, ich habe ihn gesehen. Selbst nachdem ich nüchtern geworden bin, konnte ich nicht aufhören, ihn zu sehen... Ich kann es nicht vergessen!";
			link.l1 = "Das ist interessant. Erzähl weiter. Lass uns noch einen trinken - du trinkst wahrscheinlich jetzt, um alles zu vergessen. Erzähl mir, was du gesehen hast, bevor du es tust.";
			link.l1.go = "PZ_BasTerAlkash_3";
		break;
		
		case "PZ_BasTerAlkash_3":
			dialog.text = "Ein Wanderzirkus, am Arsch! Er sprang, drehte sich und wirbelte mit diesem Säbel herum - Ich habe noch nie jemanden so geschickt und erschreckend mit einer Waffe gesehen.";
			link.l1 = "Das klingt nach ihm. Mit wem hat er gekämpft? Erinnern Sie sich?";
			link.l1.go = "PZ_BasTerAlkash_4";
		break;
		
		case "PZ_BasTerAlkash_4":
			dialog.text = "Die Wachen, Kamerad! Er verengt auch die Augen bei ihnen! Obwohl, ich denke, er sieht immer so aus. Was denkst du?";
			link.l1 = "Ich weiß nicht, Kumpel. Erzähl weiter. Dachten sie, er wäre ein Spion? Warum haben die Wachen ihn angegriffen?";
			link.l1.go = "PZ_BasTerAlkash_5";
		break;
		
		case "PZ_BasTerAlkash_5":
			dialog.text = "Wer weiß? Sie versuchten herauszufinden, was er in der Stadt machte...";
			link.l1 = "Also, haben sie ihn verhaftet? Oder...";
			link.l1.go = "PZ_BasTerAlkash_6";
		break;
		
		case "PZ_BasTerAlkash_6":
			dialog.text = "Ha, fette Chance! Sie könnten ihn nicht fangen. Er hat die Wachen in der Stadt niedergemacht und ist in den Dschungel geflohen. Sie haben mehrere Gruppen hinter ihm hergeschickt, aber keine ist zurückgekommen. Kannst du dir das vorstellen? Er hat diese Höhle zu einer echten Festung gemacht!";
			link.l1 = "Das ist etwas. Ruhe dich aus und versuche es zu vergessen. Ich glaube, ich gehe jetzt - mir dreht sich der Kopf.";
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
			dialog.text = "Habe ihn selbst nicht gesehen - er war beim Büro des Gouverneurs, eh! Aber seine Crew hat hier eine große Party gefeiert.";
			link.l1 = "Ist das so?";
			link.l1.go = "Sotta2";
		break;
		
		case "Sotta2":
			dialog.text = "Alle sagen, er sei ein Händler. Aber seine Mannschaft sah nicht aus wie Spelunkenabschaum, sag ich dir! Sie sahen aus, als ob... als ob... wie heißt das Wort...?";
			link.l1 = "Ich verstehe. Danke für die Gesellschaft, Kumpel. Mach's gut.";
			link.l1.go = "exit_sit";
			
			npchar.questTemp.PZ_Sotta = true;
			pchar.questTemp.PZ_BelizAskCitizens = sti(pchar.questTemp.PZ_BelizAskCitizens) + 1;
			AddDialogExitQuest("PZ_LongwayBelizDialog");
		break;
		
		case "Lutter1":
			dialog.text = "Ich feiere! Und wer sagt, dass ich alleine bin? Du bist hier, Kumpel! Und was Matt betrifft, es war früher oder später klar.";
			link.l1 = "Was lässt dich das sagen? Ich habe gehört, er war ein bemerkenswert glücklicher Pirat, der jahrelang von Fortuna begünstigt wurde!";
			link.l1.go = "Lutter2";
		break;
		
		case "Lutter2":
			dialog.text = "Heh, es war nicht nur das Glück, eh! Er war ein einsamer Pirat, kein Mitglied der Bruderschaft! Und die halten nicht lange... Obwohl, ich habe gehört, dass er einmal unter Levasseurs Flügel war.";
			link.l1 = "Das stimmt, Einzelgänger halten nicht lange durch. Nun, feiere. Ich muss gehen, Kumpel.";
			link.l1.go = "exit_sit";
			
			npchar.questTemp.PZ_Lutter = true;
			pchar.questTemp.PZ_BelizAskCitizens = sti(pchar.questTemp.PZ_BelizAskCitizens) + 1;
			AddDialogExitQuest("PZ_LongwayBelizDialog");
		break;
		
		case "Sepp1":
			dialog.text = "Eek, ja n-nein, ich habe ihn noch nie gesehen. Wer ist er?";
			link.l1 = "Er ist der Kapitän eines der schnellsten Schiffe im Archipel, der Brigg 'Banten'. Hast du von ihm gehört?";
			link.l1.go = "Sepp2";
		break;
		
		case "Sepp2":
			pchar.questTemp.PZ.TortugaHabitueBlock = true;
			
			dialog.text = "Äh, nein, ich interessiere mich nicht für Schiffe, Kumpel, igitt! Sollen wir noch einen Becher nehmen?";
			link.l1 = "Nicht für mich. Ich habe hier sowieso nicht bekommen, was ich wollte.";
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
