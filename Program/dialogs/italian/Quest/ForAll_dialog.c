void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag, forName;
	string sTemp, sGem, sTitle;
	int iTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Non abbiamo nulla di cui cianciare.";
			link.l1 = "D'accordo...";
			link.l1.go = "exit";	
			NextDiag.TempNode = "First time";
		break;

		case "CitizenNotBlade":
			if(LoadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Ascolta, sono un cittadino di questa città e ti chiederei di abbassare la lama.","Ascolta, sono cittadino di questa città e ti chiederei di abbassare la lama.");
				link.l1 = LinkRandPhrase("Va bene.","Certo.","D'accordo...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Sta' in campana, "+GetSexPhrase("compare","ragazza")+", girare armato. Potrei innervosirmi...","Non mi piace quando ci sono "+GetSexPhrase("uomini","gente")+" camminando davanti a me con l’arma sguainata. Mi fa venire i brividi...");
				link.l1 = RandPhraseSimple("Capito.","Ci sono riuscito.");
			}
			
			link.l1.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		//--------------------------- квест официантки --------------------------------
		//грабитель
		case "WaitressBerglar":
			dialog.text = "Dài, compare, fammi vedere le tue tasche.";
			link.l1 = "Che?! ";
			link.l1.go = "WaitressBerglar_1";
		break;
		case "WaitressBerglar_1":
			dialog.text = "Mi hai sentito. Svelto, meno chiacchiere. Non mi piace sprecare fiato...";
			link.l1 = "Maledizione! E  fa "+pchar.questTemp.different.FackWaitress.Name+" lavorare con te?";
			link.l1.go = "WaitressBerglar_2";
		break;
		case "WaitressBerglar_2":
			dialog.text = "Ah sì, sì... Dammi il malloppo o ti apro la pancia come una sardina!";
			link.l1 = "No! Ti sventrerò, lurido bastardo!";
			link.l1.go = "WaitressBerglar_fight";
			link.l2 = "Prendi le mie monete, bastardo! Ma non te la caverai così facilmente...";
			link.l2.go = "WaitressBerglar_take";
		break;
		case "WaitressBerglar_take":
			dialog.text = "Certo, nulla da ridire. Addio, compare. E ricorda, non sei così bello da far bagnare le cameriere. Usaci il cervello la prossima volta!";
			link.l1 = "...Vai già, su.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WaitressFack_outRoom");
		break;
		case "WaitressBerglar_fight":
			dialog.text = "Come dite voi...";
			link.l1 = "Così è...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WaitressFack_fight");
		break;
		//официантка
		case "Waitress":
			dialog.text = "Ecco che sono! Mi desideri, bel capitano?";
			link.l1 = "Maledizione, è degenerato tutto in fretta...";
			link.l1.go = "Waitress_1";
		break;
		case "Waitress_1":
			dialog.text = "Non perdiamo tempo, forza!";
			link.l1 = "Eheh, non potrei essere più d'accordo!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WaitressFack_fack");
		break;
		
		//--------------------------- догнать кэпа, потерявшего судовой журнал --------------------------------
		//встретил в городе
		case "PortmansCap":
			dialog.text = "Buon dì. Il mio nome è "+GetFullName(npchar)+". Sono un capitano di "+GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName+"Acc"))+" '"+npchar.Ship.name+"'. "; 
			link.l1 = "Splendido! Finalmente ti ho trovato.";
			link.l1.go = "PortmansCap_1";
		break;
		case "PortmansCap_1":
			dialog.text = "Mi avete trovato?!";
			link.l1 = "Sì. Dunque, ho portato il tuo giornale di bordo, che hai dimenticato all’ufficio del porto di "+XI_ConvertString("Colony"+npchar.quest.firstCity+"Gen")+".";
			link.l1.go = "PortmansCap_2";
		break;
		case "PortmansCap_2":
			dialog.text = "Maledizione! Ora capisco dove l’avevo smarrito. Questa perdita ha quasi scatenato un ammutinamento sulla mia nave...";
			link.l1 = "Dunque, tutto è bene quel che finisce bene. Prendi il tuo giornale di bordo e parliamo dei miei soldi.";
			link.l1.go = "PortmansCap_3";
		break;
		case "PortmansCap_3":
			if (sti(npchar.quest.stepsQty) == 1)
			{
				dialog.text = "Che tempismo, non ho ancora iniziato uno nuovo, quindi ti pagherò quanto posso. "+FindRussianMoneyString(sti(npchar.quest.money))+" e accettare qualche mio gioiello privato.";
				link.l1 = "Bene. Prendilo.";
				link.l1.go = "PortmansCap_4";
			}
			else
			{
				if (sti(npchar.quest.stepsQty) < 5)
				{
					npchar.quest.money = makeint(sti(npchar.quest.money) / sti(npchar.quest.stepsQty)); //уменьшаем вознаграждение
					dialog.text = "Hm, sai, ho già cominciato il nuovo giornale di bordo. Tuttavia, quello vecchio ha ancora valore per me. Dunque ti pagherò "+FindRussianMoneyString(sti(npchar.quest.money))+" e accetta qualche mio gioiello personale.";
					link.l1 = "Affare fatto, prendi il tuo registro.";
					link.l1.go = "PortmansCap_4";
				}
				else
				{
					dialog.text = "Ho già iniziato il nuovo giornale di bordo. E ho trascritto tutte le note da quello vecchio. Non mi serve più, quindi niente monete per te.";
					link.l1 = "Magnifico. Tutto questo inseguimento per un pugno di mosche.";
					link.l1.go = "PortmansCap_5";
				}
			}
		break;
		case "PortmansCap_4":
			dialog.text = "Grazie. Addio, "+GetSexPhrase("compare","ragazza")+".";
			link.l1 = "Anche a te, furfante...";
			link.l1.go = "exit";
			sTemp = "Timer_" + npchar.id;
			pchar.quest.(sTemp).over = "yes"; //снимаем таймер на выход в море
			npchar.LifeDay = 2; // через пару дней снимаем кэпа
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");			
			group_DeleteGroup("PorpmansShip_" + npchar.index); //чистим группу, на всякий случай
			sld = characterFromId(npchar.quest.firstCity + "_PortMan");
			sTitle = sld.id + "PortmansBook_Delivery";
			AddQuestRecordEx(sTitle, "PortmansBook_Delivery", "3");
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.City + "Voc")); // belamour gen
			AddQuestUserData(sTitle, "sCity2", XI_ConvertString("Colony" + sld.city + "Gen"));
			CloseQuestHeader(sTitle);
			sGem = pchar.questTemp.PortmansJornal.gem;
			TakeNItems(pchar, sGem, 12+hrand(10));
			DeleteAttribute(pchar, "questTemp.PortmansJornal.gem");
			DeleteAttribute(sld, "quest.PortmansJornal");
			sld.quest = ""; //освобождаем личный флаг квеста для портмана
        	AddCharacterExpToSkill(pchar, "Repair", makeint(400/sti(npchar.quest.stepsQty)));
    		AddMoneyToCharacter(pchar, sti(npchar.quest.money));
    		ChangeCharacterComplexReputation(pchar,"nobility", 2);
			TakeItemFromCharacter(pchar, "PortmansBook");
			NextDiag.TempNode = "PortmansCap_inDeck_over";
		break;
		case "PortmansCap_5":
			dialog.text = "Ah, la prossima volta scegli meglio il momento, furfante.";
			link.l1 = "Già, proprio così.";
			link.l1.go = "exit";
			sTemp = "Timer_" + npchar.id;
			pchar.quest.(sTemp).over = "yes"; //снимаем таймер на выход в море
			npchar.LifeDay = 2; // через пару дней снимаем кэпа
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");			
			group_DeleteGroup("PorpmansShip_" + npchar.index); //чистим группу, на всякий случай
			sld = characterFromId(npchar.quest.firstCity + "_PortMan");
			sTitle = sld.id + "PortmansBook_Delivery";
			AddQuestRecordEx(sTitle, "PortmansBook_Delivery", "3");
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.City + "Voc")); // belamour gen
			AddQuestUserData(sTitle, "sCity2", XI_ConvertString("Colony" + sld.city + "Gen"));
			CloseQuestHeader(sTitle);
			DeleteAttribute(sld, "quest.PortmansJornal");
			sld.quest = ""; //освобождаем личный флаг квеста для портмана
        	AddCharacterExpToSkill(pchar, "Repair", makeint(200/sti(npchar.quest.stepsQty)));
			TakeItemFromCharacter(pchar, "PortmansBook");
			NextDiag.TempNode = "PortmansCap_inDeck_over";
		break;
		//догнал в море
		case "PortmansCap_inDeck":
			if (isBadReputation(pchar, 20))
			{
				dialog.text = "Ti do il benvenuto sul ponte della mia nave. A dirla tutta, mi hai fatto prendere un bello spavento, maledizione — ho pensato che il Cacciatore dello Stallone Guercio fosse sulle mie tracce...";
				link.l1 = "No, capitano, oggi sono di buon umore. Sono qui per darti una mano.";
			}
			else
			{
				dialog.text = "Ti do il benvenuto sul ponte della mia nave!";
				link.l1 = "Ahoy, capitano! Ti stavo cercando.";
			}
			link.l1.go = "PortmansCap_inDeck_1";
		break;
		case "PortmansCap_inDeck_1":
			dialog.text = "Perché?";
			link.l1 = "Hai dimenticato il tuo giornale di bordo a casa del capitano del porto di "+XI_ConvertString("Colony"+npchar.quest.firstCity+"Gen")+".";
			link.l1.go = "PortmansCap_inDeck_2";
		break;
		case "PortmansCap_inDeck_2":
			if (sti(npchar.quest.stepsQty) == 1)
			{
				dialog.text = "Maledizione, quindi era proprio quel posto! Questa perdita mi ha già portato un mare di guai.";
				link.l1 = "E che ne dici di una ricompensa?";
				link.l1.go = "PortmansCap_inDeck_3";
			}
			else
			{
				if (sti(npchar.quest.stepsQty) < 5)
				{
					npchar.quest.money = makeint(sti(npchar.quest.money) / sti(npchar.quest.stepsQty)); //уменьшаем вознаграждение
					dialog.text = "Maledizione, ora vedo dove l’avevo perso! Grazie, ma ci hai messo un’eternità a trovarmi. Ho già iniziato un nuovo giornale di bordo. Comunque, le vecchie annotazioni devono ancora essere trascritte nel nuovo...";
					link.l1 = "E quanto?";
					link.l1.go = "PortmansCap_inDeck_3";
				}
				else
				{
					dialog.text = "Ho già iniziato il nuovo giornale di bordo. E ho trascritto tutti gli appunti dal vecchio. Non mi serve più.";
					link.l1 = "Dunque, non ti serve un vecchio diario? Sul serio?";
					link.l1.go = "PortmansCap_inDeck_5";
				}
			}
		break;
		case "PortmansCap_inDeck_3":
			dialog.text = "Posso pagarti "+FindRussianMoneyString(sti(npchar.quest.money))+" e alcuni dei miei gioielli. È tutto ciò che posso permettermi.";
			link.l1 = "D'accordo allora. Prendi il tuo diario.";
			link.l1.go = "PortmansCap_inDeck_4";
		break;
		case "PortmansCap_inDeck_4":
			dialog.text = "Grazie ancora. Addio, compare.";
			link.l1 = "Continua così.";
			link.l1.go = "exit";
			npchar.LifeDay = 30; // через десять дней снимаем кэпа
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");	
			npchar.quest = "over"; //флаг кэпа квест закончен. энкаутер доплывет до назначения и исчезнет
			sld = characterFromId(npchar.quest.firstCity + "_PortMan");
			sTitle = sld.id + "PortmansBook_Delivery";
			AddQuestRecordEx(sTitle, "PortmansBook_Delivery", "2");
			AddQuestUserData(sTitle, "sTargetCity", XI_ConvertString("Colony" + npchar.quest.targetCity + "Acc"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + sld.city + "Gen"));
			CloseQuestHeader(sTitle);
			sGem = pchar.questTemp.PortmansJornal.gem;
			TakeNItems(pchar, sGem, 12+hrand(10));
			DeleteAttribute(pchar, "questTemp.PortmansJornal.gem");
			DeleteAttribute(sld, "quest.PortmansJornal");
			sld.quest = ""; //освобождаем личный флаг квеста для портмана
        	AddCharacterExpToSkill(pchar, "Sailing", makeint(200/sti(npchar.quest.stepsQty)));
    		AddMoneyToCharacter(pchar, sti(npchar.quest.money));
    		ChangeCharacterComplexReputation(pchar,"nobility", 5);
			TakeItemFromCharacter(pchar, "PortmansBook");
			npchar.DeckDialogNode = "PortmansCap_inDeck_over";
			NextDiag.TempNode = "PortmansCap_inDeck_over";
		break;
		case "PortmansCap_inDeck_5":
			dialog.text = "Certamente. Se rincorri qualcuno, devi esser più svelto.";
			link.l1 = "Non perdere i tuoi registri di bordo per cominciare. Va bene.";
			link.l1.go = "exit";
			npchar.LifeDay = 30; // через десять дней снимаем кэпа
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");	
			npchar.quest = "over"; //флаг кэпа квест закончен. энкаутер доплывет до назначения и исчезнет
			sld = characterFromId(npchar.quest.firstCity + "_PortMan");
			sTitle = sld.id + "PortmansBook_Delivery";
			AddQuestRecordEx(sTitle, "PortmansBook_Delivery", "2");
			AddQuestUserData(sTitle, "sTargetCity", XI_ConvertString("Colony" + npchar.quest.targetCity + "Acc"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + sld.city + "Gen"));
			CloseQuestHeader(sTitle);
			DeleteAttribute(sld, "quest.PortmansJornal");
			sld.quest = ""; //освобождаем личный флаг квеста для портмана
        	AddCharacterExpToSkill(pchar, "Sailing", makeint(100/sti(npchar.quest.stepsQty)));
			TakeItemFromCharacter(pchar, "PortmansBook");
			npchar.DeckDialogNode = "PortmansCap_inDeck_over";
			NextDiag.TempNode = "PortmansCap_inDeck_over";
		break;
		case "PortmansCap_inDeck_over":
			dialog.text = "Pensavo che avessimo già sistemato ogni cosa.";
			link.l1 = "Sì, è vero.";
			link.l1.go = "exit";
			NextDiag.TempNode = "PortmansCap_inDeck_over";
		break;
		//--------------------------- розыск украденного корабля --------------------------------
		case "SeekCap_inDeck":
			dialog.text = "Salute. Che vuoi?";
			link.l1 = "Non è nulla, volevo solo sentire qualche novità. Hai qualcosa da vendere?";
			link.l1.go = "SeekCap_inDeck_1";
		break;
		case "SeekCap_inDeck_1":
			dialog.text = "Non ho nulla da venderti e nessuna notizia da darti. A proposito, la tua presenza qui non è gradita. Sono stato chiaro?";
			link.l1 = "Tu sei... E allora addio, compare.";
			link.l1.go = "exit";
			NextDiag.TempNode = "SeekCap_inDeck_over";
			sld = characterFromId(npchar.quest.cribCity + "_PortMan");
			sTitle = sld.id + "Portmans_SeekShip";
			AddQuestRecordEx(sTitle, "Portmans_SeekShip", "4");
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.quest.cribCity + "Gen"));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName)));
		break;
		case "SeekCap_inDeck_over":
			dialog.text = "Ti ho già detto che qui non ci hai nulla da fare, canaglia!";
			link.l1 = "Capisco...";
			link.l1.go = "exit";
			NextDiag.TempNode = "SeekCap_inDeck_over";
		break;
		//абордаж
		case "SeekCap":
			dialog.text = "Perché m'hai assalito?!";
			link.l1 = "Devo restituire la nave al suo legittimo proprietario...";
			link.l1.go = "SeekCap_1";
		break;
		case "SeekCap_1":
			dialog.text = "A che tipo di padrone? Sono io il padrone!";
			link.l1 = "No, non lo sei. Non so chi sia il padrone di questa nave. Ma è stata rubata e devo riportarla indietro.";
			link.l1.go = "SeekCap_2";
		break;
		case "SeekCap_2":
			dialog.text = "Merda! Ma non è ancora finita per me. Almeno proverò ad ammazzarti...";
			link.l1 = "Tentar non nuoce, vecchio mio.";
			link.l1.go = "SeekCap_3";
		break;
		case "SeekCap_3":
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogExitWithBattle(""); 
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//-------------------------------------------поисковый генератор горожан--------------------------------------
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		
		case "SCQ_exit":
			DialogExit();
			npchar.lifeDay = 0;
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "SCQ_exit_clear":
			sld = characterFromId(npchar.quest.SeekCap.capId); //капитан	
			sld.lifeDay = 0;
			Map_ReleaseQuestEncounter(sld.id);
			string sGroup = "SeekCapShip_" + sld.index;
			group_DeleteGroup(sGroup);
			sTemp = "SCQ_" + sld.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть кэпа
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть квестодателя
			npchar.lifeDay = 0;
			LAi_CharacterDisableDialog(npchar);
            DialogExit();
		break;
		
//--------------------------------------------поисковые квесты дворян---------------------------------------------
		
		case "SCQ_Nobleman":
			dialog.text = "Salute, "+GetAddress_Form(NPChar)+". Vedo che siete il capitano della vostra nave? Il mio nome è "+GetFullName(npchar)+" e voglio proporti un patto.";
			link.l1 = RandPhraseSimple("Mi rincresce assai, ma debbo andarmene.","Perdonami, ma non ho tempo da perdere in chiacchiere con te.");
			link.l1.go = "SCQ_exit";
			link.l2 = "Sono tutto orecchi.";
			link.l2.go = "SCQ_Nobleman_1";
		break;

		case "SCQ_Nobleman_1":
			switch (sti(npchar.quest.SeekCap.numQuest))
			{
				case 0: //вариант А
					if (sti(pchar.reputation.nobility) < 35)
					{
						dialog.text = "Ascolta, dunque. "+SelectNB_battleText()+"\nNon ho né il tempo né la fortuna di rintracciarlo. Perché qui non mette mai piede, mai. Immagino che ora tu capisca, capisca cosa sto per proporti, vero?";
						link.l1 = LinkRandPhrase("Suppongo che debba rintracciare qualcuno e portartelo, vero?","Forse, scovare quel bastardo e portarlo da te?","Vuoi che trovi quest’uomo e te lo porti qui?");
						link.l1.go = "SCQ_NM_battle";
					}
					else //вариант В
					{
						SelectNB_prisonerText(npchar);
						dialog.text = "Ascolta allora."+SelectNB_battleText()+"\nNon ho né il tempo né la fortuna di rintracciarlo. Perché non si fa mai vedere da queste parti. Immagino che ora tu capisca, capisca cosa sto per proporti, eh?";
						link.l1 = LinkRandPhrase("Suppongo che tu voglia che io dia la caccia a qualcuno e te lo porti, eh?","Forse, trovare quel bastardo e portarlo da voi?","Vuoi che trovi quest'uomo e te lo porti qui?");
						link.l1.go = "SCQ_NM_prisoner"
					}
		break;
				
				case 1: //вариант С
					SelectNB_peaceText(npchar);
					dialog.text = "Ascolta allora. In verità, "+npchar.quest.text+" sta servendo nella marina come capitano. Non ha nemmeno idea che anch'io mi trovi qui!\nMi piacerebbe incontrarlo, ma né il tempo né la sorte mi permettono di rintracciarlo...";
					link.l1 = "Suppongo che tu voglia che io trovi questo capitano e gli parli di te?";
					link.l1.go = "SCQ_NM_peace";
				break;
			}
		break;
		
		case "SCQ_NM_battle": //вариант А
			dialog.text = "Non proprio così. Trovalo, ma non serve portarlo qui. Uccidilo, e basterà. Affondalo insieme alla sua lurida nave, sparami addosso, infilzalo con la tua lama – non me ne importa un accidente, basta che questo cane smetta di ammorbarmi l’aria con la sua presenza. La ricompensa sarà generosa.";
			link.l1 = "Ah! Semplice come bere un grog. Dimmi il suo nome e quello della sua nave.";
			link.l1.go = "SCQ_NM_battle_1";
		break;
		
		case "SCQ_NM_battle_1":
			npchar.quest.SeekCap = "NM_battle"; //личный флаг на квест
			SetSeekCapCitizenParam(npchar, rand(NON_PIRATES)); //любая нация кроме пиратов
			dialog.text = ""+npchar.quest.SeekCap.capName+" dei "+GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName+"Voc"))+" chiamato "+npchar.quest.SeekCap.shipName+". È spesso ospite nel porto di "+XI_ConvertString("Colony"+npchar.quest.Qcity)+". Ti pagherò "+FindRussianMoneyString(sti(npchar.quest.money))+" in dobloni d’oro.";
			link.l1 = "Ecco tutto ciò che mi serve sapere. Starò all’erta in mare. E quando troverò il tuo compare, gli farò... 'abbassa la voce' ...provare il freddo abbraccio di Nettuno.";
			link.l1.go = "SCQ_NM_battle_2";
			link.l2 = "Non basta per quel genere di lavoro.";
			link.l2.go = "SCQ_exit_clear";
		break;
		
		case "SCQ_NM_battle_2":
			dialog.text = "Sono lieto che abbiamo stretto un accordo. Ti aspetterò al tuo ritorno.";
			link.l1 = "Dove potrò trovarti? Mettiamolo in chiaro subito, non voglio perdere tempo a cercarti.";
			link.l1.go = "SCQ_NM_battle_3";
		break;
		
		case "SCQ_NM_battle_3":
			dialog.text = "Ogni mattina partecipo alla messa nella chiesa del villaggio. Puoi trovarmi lì tutti i giorni dalle otto alle nove.";
			link.l1 = "D'accordo allora! Presto avrai tue notizie.";
			link.l1.go = "exit";
			DeleteAttribute(npchar, "LifeDay");
			DeleteAttribute(npchar, "talker");
			DeleteAttribute(npchar, "CityType");//удалить признак фантома, иначе - пустые города
			LAi_SetLoginTime(npchar, 8.0, 10.0);
			pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
			npchar.location = npchar.city + "_church";
			npchar.location.locator = "goto2";			
            pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
			pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
			pchar.quest.SeekShip_Stay.Idx = npchar.index;
			NextDiag.TempNode = "SCQ_NM_result";
			sTitle = npchar.city + "SCQ_NM_battle";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "SCQ_NM_battle", "1");
			AddQuestUserDataForTitle(sTitle, "sName", GetFullName(npchar));
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sQCity", XI_ConvertString("Colony"+npchar.quest.Qcity));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Voc")));
			AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
			AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
		break;
		
		case "SCQ_NM_prisoner": //вариант В
			dialog.text = "Esatto. Trovamelo e portamelo vivo. Voglio occuparmene io stesso. Ti ricompenserò generosamente.";
			link.l1 = "Ebbene, posso provare a rintracciarlo, ma mi servono dettagli.";
			link.l1.go = "SCQ_NM_prisoner_1";
		break;
		
		case "SCQ_NM_prisoner_1":
			npchar.quest.SeekCap = "NM_prisoner"; //личный флаг на квест
			SetSeekCapCitizenParam(npchar, rand(NON_PIRATES)); //любая нация кроме пиратов
			makearef(forName, npchar.quest.SeekCap);
			forName.nation = sti(npchar.nation);
			forName.sex = "man";
			forName.name = GenerateRandomName(sti(npchar.nation), "man");
			dialog.text = "Quel bastardo si chiama "+npchar.quest.SeekCap.name+". Serve a bordo di "+GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName+"Voc"))+" chiamato "+npchar.quest.SeekCap.shipName+", che si trova sotto il comando di "+npchar.quest.SeekCap.capName+". La nave può essere spesso avvistata nel porto di "+XI_ConvertString("Colony"+npchar.quest.Qcity)+". Ti pagherò per questo lavoro "+FindRussianMoneyString(sti(npchar.quest.money))+" in dobloni d’oro.";
			link.l1 = "Basta così per me. Starò all’erta in mare aperto.";
			link.l1.go = "SCQ_NM_prisoner_2";
			link.l2 = "Non basta per quel tipo di lavoro.";
			link.l2.go = "SCQ_exit_clear";
		break;
		
		case "SCQ_NM_prisoner_2":
			dialog.text = "Sono lieto che abbiamo stretto questo accordo. Ti aspetterò al tuo ritorno.";
			link.l1 = "Dove potrò trovarti? Mettiamolo in chiaro subito, non ho voglia di perdere tempo a cercarti.";
			link.l1.go = "SCQ_NM_prisoner_3";
		break;
		
		case "SCQ_NM_prisoner_3":
			dialog.text = "Ogni mattina prendo parte alla messa nella chiesa del villaggio. Mi trovi lì ogni giorno dalle otto alle nove.";
			link.l1 = "Affare fatto! Presto avrai tue notizie.";
			link.l1.go = "exit";
			DeleteAttribute(npchar, "LifeDay");
			DeleteAttribute(npchar, "talker");
			DeleteAttribute(npchar, "CityType");//удалить признак фантома, иначе - пустые города
			LAi_SetLoginTime(npchar, 8.0, 10.0);
			pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
			npchar.location = npchar.city + "_church";
			npchar.location.locator = "goto2";			
            pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
			pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
			pchar.quest.SeekShip_Stay.Idx = npchar.index;
			NextDiag.TempNode = "SCQ_NM_result";
			sTitle = npchar.city + "SCQ_NM_prisoner";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "SCQ_NM_prisoner", "1");
			AddQuestUserDataForTitle(sTitle, "sName", GetFullName(npchar));
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sQCity", XI_ConvertString("Colony"+npchar.quest.Qcity));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Voc")));
			AddQuestUserData(sTitle, "sName1", npchar.quest.SeekCap.name);
			AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
			AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
		break;
		
		case "SCQ_NM_peace": //вариант С
			dialog.text = "Esatto! Trovate quel furfante e ditegli che vivo in questa città. Vi ricompenserò per il disturbo.";
			link.l1 = "Vediamo un po'... Posso provarci. Raccontami i dettagli.";
			link.l1.go = "SCQ_NM_peace_1";
		break;
		
		case "SCQ_NM_peace_1":
			npchar.quest.SeekCap = "NM_peace"; //личный флаг на квест
			SetSeekCapCitizenParam(npchar, sti(npchar.nation)); //нация = нации квестодателя
			dialog.text = "Si chiama "+npchar.quest.SeekCap.capName+". E serve a bordo di "+GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName+"Voc"))+" "+npchar.quest.SeekCap.shipName+"'. Viene spesso a far visita "+XI_ConvertString("Colony"+npchar.quest.Qcity)+". Ti pagherò per questo lavoro "+FindRussianMoneyString(sti(npchar.quest.money))+" in dobloni d’oro.";
			link.l1 = "Affare fatto! Suppongo che troverò il tuo compare piuttosto presto.";
			link.l1.go = "SCQ_NM_peace_2";
			link.l2 = "Non mi basta questo.";
			link.l2.go = "SCQ_exit_clear";
		break;
		
		case "SCQ_NM_peace_2":
			dialog.text = "Sono lieto che abbiamo stretto un accordo. Attenderò il tuo ritorno.";
			link.l1 = "Dove potrò trovarti? Facciamolo chiaro subito, non voglio perdere tempo a cercarti.";
			link.l1.go = "SCQ_NM_peace_3";
		break;
		
		case "SCQ_NM_peace_3":
			dialog.text = "Partecipo sempre alla funzione serale nella chiesa del posto. Mi trovi lì ogni giorno dalle sei alle otto di sera.";
			link.l1 = "Affare fatto! Presto avrai notizie.";
			link.l1.go = "exit";
			DeleteAttribute(npchar, "LifeDay");
			DeleteAttribute(npchar, "talker");
			DeleteAttribute(npchar, "CityType");//удалить признак фантома, иначе - пустые города
			LAi_SetLoginTime(npchar, 18.0, 20.0);
			pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
			npchar.location = npchar.city + "_church";
			npchar.location.locator = "goto2";			
            pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
			pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
			pchar.quest.SeekShip_Stay.Idx = npchar.index;
			NextDiag.TempNode = "SCQ_NM_result";
			sTitle = npchar.city + "SCQ_NM_peace";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "SCQ_NM_peace", "1");
			AddQuestUserDataForTitle(sTitle, "sName", GetFullName(npchar));
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sQCity", XI_ConvertString("Colony"+npchar.quest.Qcity));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Voc")));
			AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
			AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
		break;
		
		//--> разговор на суше, вариант А
		case "NM_battleCap":
			dialog.text = "E allora? Che volete, signore?";
			link.l1 = "Sei tu il capitano "+GetFullName(npchar)+"?";
			link.l1.go = "NM_battleCap_1";
		break;
		
		case "NM_battleCap_1":
			dialog.text = "Sì, lo sono. Di che si tratta?";
			link.l1 = "Un uomo nutre un vivo interesse per te, si chiama "+GetFullName(&characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)])+". Ricordi?";
			link.l1.go = "NM_battleCap_2";
			link.l2 = "Ho sentito dire che hai un bel po' di mogano nella stiva. Voglio comprarlo. Me lo venderesti?";
			link.l2.go = "NM_battleCap_4";
		break;
		
		case "NM_battleCap_2":
			dialog.text = "È la prima volta che sento questo nome. Hai preso un granchio, capitano. Abbiamo finito?";
			link.l1 = "Hm. Va bene, scusatemi...";
			link.l1.go = "NM_battleCap_exit";
			link.l2 = "Ah davvero? Ma lui si ricorda benissimo di te. Ha menzionato il debito che hai con lui...";
			link.l2.go = "NM_battleCap_3";
		break;
		
		case "NM_battleCap_3":
			dialog.text = "Quale debito? Di che diamine parli?";
			link.l1 = "Il debito d'onore!";
			link.l1.go = "NM_battleCap_fight";
		break;
		
		case "NM_battleCap_4":
			dialog.text = "Ti sbagli. Non commercio legname. Abbiamo finito qui?";
			link.l1 = "Hm. Va bene, scusatemi...";
			link.l1.go = "NM_battleCap_exit";
		break;
		
		case "NM_battleCap_exit":
			DialogExit();
			NextDiag.TempNode = "NM_battleDeck_exit";
			npchar.DeckDialogNode = "NM_battleDeck_exit";
		break;
		
		case "NM_battleCap_fight":
			NextDiag.TempNode = "NM_battleDeck_exit";
			npchar.DeckDialogNode = "NM_battleDeck_exit";
			LAi_group_Attack(NPChar, Pchar);
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		//--> разговор на суше и палубе одинаковый, вариант В
		case "NM_prisonerCap":
			dialog.text = "E allora? Che volete, signore?";
			link.l1 = "Sei tu il capitano "+GetFullName(npchar)+"?";
			link.l1.go = "NM_prisonerCap_1";
		break;
		
		case "NM_prisonerCap_1":
			sld = &characters[GetCharacterIndex("QuestCitiz_" + npchar.quest.cribCity)];//квестодатель
			dialog.text = "Sì, sono io. Di che si tratta?";
			link.l1 = "Un uomo chiamato "+sld.quest.SeekCap.name+" servire sotto il tuo comando?";
			link.l1.go = "NM_prisonerCap_2";
		break;
		 
		case "NM_prisonerCap_2":
			sld = &characters[GetCharacterIndex("QuestCitiz_" + npchar.quest.cribCity)];//квестодатель
			dialog.text = "Sì. È uno dei miei ufficiali. Ora dimmi, perché lo chiedi?";
			link.l1 = "Certo che te lo dirò. Sto cercando quest'uomo per ordine delle autorità di "+XI_ConvertString("Colony"+sld.city+"Gen")+", e ho il potere di arrestarlo e consegnarlo a "+XI_ConvertString("Colony"+sld.city)+". Ti chiedo di aiutarmi in questa faccenda, così potremo risolverla in modo pacifico.";
			link.l1.go = "NM_prisonerCap_3";
		break;
		
		case "NM_prisonerCap_3":
			if(sti(npchar.reputation.nobility) > 41)
			{
				dialog.text = "Davvero? E un simile uomo serve nella mia ciurma? Parli sul serio?";
				link.l1 = "Non ti crucciare per questa faccenda, "+GetAddress_FormToNPC(NPChar)+". Manderò una scialuppa alla tua nave e lo prenderemo noi stessi.";
				link.l1.go = "NM_prisonerCap_good";
			}
			else
			{
				dialog.text = "Ma guarda un po’. Sapete che vi dico, signore? Del suo passato non me ne importa un accidente. Non è affar mio. E voi chi sareste, di grazia? Autorità? Sul serio? Ah! Io i miei uomini non li consegno, né a voi né a nessun altro. La conversazione finisce qui. Fuori dai piedi!";
				link.l1 = "Scelta sbagliata... Maledettamente pessima!";
				link.l1.go = "NM_prisonerCap_bad";
			}
		break;
		
		case "NM_prisonerCap_good":
			dialog.text = "Fai quel che devi fare.";
			link.l1 = "Subito, capitano.";
			link.l1.go = "NM_prisonerCap_good_1";
		break;
		
		case "NM_prisonerCap_good_1":
			DialogExit();
			NextDiag.CurrentNode = "NM_prisonerDeck_exit";
			npchar.DeckDialogNode = "NM_prisonerDeck_exit";
			npchar.quest.release = "true";
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			ref chr = GetCharacter(NPC_GenerateCharacter(npchar.quest.SeekCap + "_" + npchar.quest.cribCity, "citiz_"+(rand(9)+21), "man", "man", 5, sti(npchar.nation), -1, false, "citizen"));
			chr.name = sld.quest.SeekCap.name;
			chr.lastname = "";
			//pchar.GenQuest.LastQuestPrisonerIdx = SetCharToPrisoner(chr);
			//SetCharacterRemovable(&characters[sti(pchar.GenQuest.LastQuestPrisonerIdx)], false);
			AddPassenger(pchar, chr, false);//добавить пассажира
			SetCharacterRemovable(chr, false);
			log_info(sld.quest.SeekCap.name+" is under arrest");
			PlaySound("interface\notebook.wav");
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).win_condition.l1 = "MapEnter";
			pchar.quest.(sTemp).function = "SCQ_seekCapIsDeath";
			//DoQuestFunctionDelay("SCQ_seekCapIsDeath", 0.5); // 170712
			AddCharacterExpToSkill(pchar, "Fortune", 200);//везение
		break;
		
		case "NM_prisonerCap_bad":
			DialogExit();
			NextDiag.CurrentNode = "NM_prisonerDeck_exit";
			npchar.DeckDialogNode = "NM_prisonerDeck_exit";
			npchar.quest.mustboarding = "true";
			sld = &characters[GetCharacterIndex("QuestCitiz_" + npchar.quest.cribCity)];//квестодатель
			sTitle = sld.City + "SCQ_" + sld.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + sld.quest.SeekCap, "6");
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
		break;
		
		case "NM_prisonerDeck_exit":
			dialog.text = "Abbiamo finito, capitano?";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "NM_prisonerDeck_exit";
		break;
		
		//--> разговор на суше и палубе одинаковый, вариант C
		case "NM_peaceCap":
			dialog.text = "Buongiorno. Che volete, capitano?";
			link.l1 = "Sei il capitano "+GetFullName(npchar)+", ho ragione?";
			link.l1.go = "NM_peaceCap_1";
		break;
		
		case "NM_peaceCap_1":
			sld = characterFromId("QuestCitiz_" + npchar.quest.cribCity);//квестодатель
			dialog.text = "Hai ragione. Hai qualcosa per me?";
			link.l1 = "Sì, ho incontrato. Un tale di nome "+GetFullName(sld)+" ti sta cercando. Vuole che tu gli faccia visita il prima possibile. Abita a "+XI_ConvertString("Colony"+npchar.quest.cribCity+"Voc")+".";
			link.l1.go = "NM_peaceCap_2";
		break;
		 
		case "NM_peaceCap_2":
			dialog.text = "Ah! Anche lui s'è trasferito nel Nuovo Mondo? Allora davvero dovrei fargli una visitina... Grazie per l'informazione, signore!";
			link.l1 = "Benvenuto. Il pagamento lo riceverò dal tuo compare. Buona fortuna, "+GetAddress_FormToNPC(NPChar)+"!";
			link.l1.go = "NM_peaceCap_3";
		break;
		
		case "NM_peaceCap_3":
			DialogExit();
			NextDiag.CurrentNode = "NM_peaceCap_exit";
			npchar.DeckDialogNode = "NM_peaceCap_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony"+npchar.quest.cribCity+"Acc"));
			sld = characterFromId("QuestCitiz_" + npchar.quest.cribCity);//квестодатель
			sld.quest.SeekCap = sld.quest.SeekCap + "over"; //дополняем флаг квест до 'выполнен'
			//удаляем запись в базе кэпов
			makearef(forName, NullCharacter.capitainBase);
			DeleteAttribute(forName, npchar.id);
		break;
		
		case "NM_peaceCap_exit":
			dialog.text = "È stato un piacere, "+GetAddress_Form(NPChar)+"!";
			link.l1 = "Il piacere è stato tutto mio, capitano.";
			link.l1.go = "exit";
			NextDiag.TempNode = "NM_peaceCap_exit";
		break;
		
		//--> встреча на палубе, вариант А
		case "NM_battleDeck":
			dialog.text = "Ahoy, "+GetAddress_Form(NPChar)+". Che vuoi, marinaio?";
			link.l1 = "Ho sentito dire che hai un bel carico di legno rosso nella stiva e vorrei comprarlo. Me lo vendi?";
			link.l1.go = "NM_battleDeck_1";
		break;
		
		case "NM_battleDeck_1":
			dialog.text = "Ti sbagli. Non commercio in legname e la tua visita qui mi puzza di bruciato. Penso che faresti meglio a sbarcare dalla mia nave!";
			link.l1 = "Va bene, chiedevo soltanto. Addio.";
			link.l1.go = "exit";
			NextDiag.TempNode = "NM_battleDeck_exit";
			npchar.DeckDialogNode = "NM_battleDeck_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName))); // belamour gen
		break;
		
		case "NM_battleDeck_exit":
			dialog.text = "Vuoi grane, signore? Devo ripetermi?";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "NM_battleDeck_exit";
		break;
		
		 //--> абордаж, вариант А
		case "NM_battleBoard":
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			dialog.text = "Perché hai assalito la mia nave, furfante?";
			link.l1 = "Sono qui per porgerti i più sentiti omaggi da parte di "+XI_ConvertString("Colony"+npchar.quest.cribCity)+" , da quell’uomo chiamato "+GetFullName(&characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)])+". Spero che tu abbia compreso la faccenda ora.";
			link.l1.go = "NM_battleBoard_1";
		break;
		
		case "NM_battleBoard_1":
			dialog.text = "Impossibile! Allora non ho nulla da perdere...";
			link.l1 = "E la tua vita, com'è andata finora?";
			link.l1.go = "NM_battleBoard_2";
		break;
		
		case "NM_battleBoard_2":
			DialogExit();
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		 //--> абордаж, вариант В
		case "NM_prisonerBoard":
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];//квестодатель
			dialog.text = "Perché hai assaltato la mia nave, furfante?";
			if (CheckAttribute(npchar, "quest.mustboarding"))
			{
				link.l1 = "Hai qualche idea? Ti ho chiesto di consegnarmi il tuo ufficiale senza storie. Ora mi prendo lui, te e la tua carretta!";
				link.l1.go = "NM_prisonerBoard_1";
			}
			else
			{
				link.l1 = "C’è un furfante al tuo servizio. Porta il nome di "+sld.quest.SeekCap.name+". Autorità di "+XI_ConvertString("Colony"+npchar.quest.cribCity)+" sono davvero impazienti di vederlo. Sarà arrestato e rinchiuso nella mia stiva.";
				link.l1.go = "NM_prisonerBoard_1";
			}
		break;
		
		case "NM_prisonerBoard_1":
			dialog.text = "E per questo hai scatenato una carneficina sulla mia nave? Maledetto bastardo! Ho ancora un po' di forza... Ti ammazzerò!";
			link.l1 = "Uomini più forti di te ci hanno già provato...";
			link.l1.go = "NM_prisonerBoard_2";
		break;
		
		case "NM_prisonerBoard_2":
			DialogExit();
			LAi_SetCurHPMax(npchar);
			pchar.GenQuest.mustboarding = "true";//ставим этот флаг для завершения квеста
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "CitizSeekCap_GivePrisoner");
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.GenQuest.CitizSeekCap.label = npchar.quest.SeekCap; //флаг квеста для нпс
			pchar.GenQuest.CitizSeekCap.nation = npchar.nation;	//нацию для нпс
			pchar.GenQuest.CitizSeekCap.sex = "man";
			pchar.GenQuest.CitizSeekCap.ani = "man";
			pchar.GenQuest.CitizSeekCap.model = "citiz_"+(rand(9)+21); //модель для нпс
			pchar.GenQuest.CitizSeekCap.PrisonerCity = npchar.quest.cribCity; //исходный город для нпс
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			pchar.GenQuest.CitizSeekCap.PrisonerName = sld.quest.SeekCap.name; //имя и фамилию для нпс
			pchar.GenQuest.CitizSeekCap.PrisonerLastname = "";
			AddComplexSeaExpToScill(50, 50, 50, 50, 50, 50, 0);
		break;
		
		//--> результаты квестов дворян
		case "SCQ_NM_result":
			dialog.text = "Che ne dici, capitano? Hai fatto passi avanti con la mia faccenda?";
			link.l1 = "Non ancora. Ma ci sto lavorando.";
			link.l1.go = "exit";
			switch (npchar.quest.SeekCap)
			{
				case "NM_battleover"://сдача квеста, вариант А
					dialog.text = "Che ne dici, capitano? Hai fatto progressi con la mia faccenda?";
					link.l1 = "Sì, certo. E ti piacerà, vedrai."+npchar.quest.SeekCap.capName+" è morto e il suo "+GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName))+" è sul fondo del mare.";
					link.l1.go = "SCQ_NM_result_A1";
				break;
				
				case "NM_prisonerover"://сдача квеста, вариант B
					dialog.text = "Che mi dici, capitano? Hai fatto progressi con la mia faccenda?";
					link.l1 = "Sì, e ti piacerà, fidati."+npchar.quest.SeekCap.Name+" è seduto nella cabina della mia nave agli arresti.";
					link.l1.go = "SCQ_NM_result_B1";
				break;
				
				case "NM_peaceover"://сдача квеста, вариант C
					dialog.text = "Aha, eccoti qui. Mi fa piacere vederti. Mi hanno detto che hai portato a termine la tua missione!";
					link.l1 = "Il tuo compare è venuto a trovarti?";
					link.l1.go = "SCQ_NM_result_C1";
				break;
			}
		break;
		
		case "SCQ_NM_result_A1":
			dialog.text = "Splendido! Sapevo che potevo contare su di te. Ecco, prendi il tuo oro. Te lo sei guadagnato.";
			link.l1 = "Grazie. Rivolgiti a me di nuovo se ti troverai con un altro nemico.";
			link.l1.go = "SCQ_exit";
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть горожанина-квестодателя
			TakeNItems(pchar, "gold_dublon", sti(npchar.quest.dublon));
			Log_Info("You have received "+FindRussianDublonString(sti(npchar.quest.dublon))+"");
			PlaySound("interface\important_item.wav");
			sTitle = npchar.city + "SCQ_NM_battle";
			CloseQuestHeader(sTitle);
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			OfficersReaction("bad");
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 2);
			AddComplexSeaExpToScill(100, 50, 50, 50, 50, 50, 0);
			AddCharacterExpToSkill(pchar, "Leadership", 100);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
		break;
		
		case "SCQ_NM_result_B1":
			dialog.text = "Splendido! Ordirò ai miei uomini di portarlo subito via dalla tua nave. Stavolta non scapperà! Ecco qui, prendi il tuo oro. Te lo sei guadagnato.";
			link.l1 = "Grazie. Rivolgiti pure a me ogni volta che ti serve un lavoro del genere.";
			link.l1.go = "SCQ_exit";
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть горожанина-квестодателя
			TakeNItems(pchar, "gold_dublon", sti(npchar.quest.dublon));
			Log_Info("You have received "+FindRussianDublonString(sti(npchar.quest.dublon))+"");
			PlaySound("interface\important_item.wav");
			sTitle = npchar.city + "SCQ_NM_prisoner";
			CloseQuestHeader(sTitle);
			sld = characterFromId("NM_prisoner_" + npchar.City);
			RemovePassenger(pchar, sld); // 170712
			//ReleasePrisoner(sld);
			sld.lifeday = 0;
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 2);
			AddCharacterExpToSkill(pchar, "Sailing", 100);//навигация
			AddCharacterExpToSkill(pchar, "Leadership", 150);//авторитет
		break;
		
		case "SCQ_NM_result_C1":
			dialog.text = "Sì, è stato qui e mi ha parlato di te. Ecco, prendi il tuo oro. Te lo sei guadagnato.";
			link.l1 = "Grazie a voi. Addio, signore!";
			link.l1.go = "SCQ_exit";
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть горожанина-квестодателя
			sld = characterFromId(npchar.quest.SeekCap.capId);
			sld.lifeday = 0;
			Map_ReleaseQuestEncounter(sld.id);
			sGroup = "SeekCapShip_" + sld.index;
			group_DeleteGroup(sGroup);
			sTemp = "SecondTimer_" + sld.id;
			pchar.quest.(sTemp).over = "yes"; //снимаем возможный таймер на выход в море
			sTemp = "SCQ_" + sld.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть кэпа
			TakeNItems(pchar, "gold_dublon", sti(npchar.quest.dublon));
			Log_Info("You have received "+FindRussianDublonString(sti(npchar.quest.dublon))+"");
			PlaySound("interface\important_item.wav");
			sTitle = npchar.city + "SCQ_NM_peace";
			CloseQuestHeader(sTitle);
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			OfficersReaction("good");
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 2);
			AddCharacterExpToSkill(pchar, "Sailing", 100);//навигация
			AddCharacterExpToSkill(pchar, "Leadership", 200);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
		break;
//<-- поисковые квесты дворян

		//========= квесты мужиков ===========
		case "SCQ_man":
			dialog.text = LinkRandPhrase("Saluti, capitano. Ho bisogno del vostro aiuto.","Capitano! Mi potete aiutare? Vi prego.","Capitano, vi imploro il vostro aiuto!");
			link.l1 = RandPhraseSimple("Sono occupato.","Ho fretta.");
			link.l1.go = "SCQ_exit";
			link.l2 = RandPhraseSimple("Che succede?","Dimmi pure che t’affligge. Forse potrò darti una mano.");
			link.l2.go = "SCQ_man_1";
		break;
		case "SCQ_exit":
			//минус один шанс, что следующий квестодатель сам заговорит
			sld = &locations[FindLocation(npchar.location)];
			if (sti(sld.questSeekCap) > 0) sld.questSeekCap = sti(sld.questSeekCap)-1;
			npchar.lifeDay = 0;
			LAi_CharacterDisableDialog(npchar);
            DialogExit();
		break;
		case "SCQ_exit_clear":
			//минус один шанс, что следующий квестодатель сам заговорит
			sld = &locations[FindLocation(npchar.location)];
			if (sti(sld.questSeekCap) > 0) sld.questSeekCap = sti(sld.questSeekCap)-1;
			sld = characterFromId(npchar.quest.SeekCap.capId); //капитан	
			sld.lifeDay = 0;
			Map_ReleaseQuestEncounter(sld.id);
			sGroup = "SeekCapShip_" + sld.index;
			group_DeleteGroup(sGroup);
			sTemp = "SCQ_" + sld.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть кэпа
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть квестодателя
			npchar.lifeDay = 0;
			LAi_CharacterDisableDialog(npchar);
            DialogExit();
		break;
		//выбираем квест
		case "SCQ_man_1":
			switch (npchar.quest.SeekCap.numQuest)
			{
				case "0":
					dialog.text = "Un anno fa un capitano mi giurò che mi avrebbe portato a "+XI_ConvertString("Colony"+SelectNotEnemyColony(NPChar)+"Acc")+" Ma mentre ero a bordo della sua nave, fui gettato nella stiva e poi venduto come schiavo. Sono sopravvissuto per un pelo. Ho visto la morte in faccia più di una volta... Ad ogni modo, voglio far sapere al mio 'amico' che sono ancora vivo."; // belamour gen
					link.l1 = "Cosa vuoi dire? Dimmi esattamente cosa desideri.";
					link.l1.go = "SCQ_Slave";
				break;
				case "1":
					dialog.text = "Mia moglie è stata rapita. Un capitano, un pirata come dicono, la corteggiava. Mia moglie fu costretta a restare chiusa in casa per giorni, a causa delle sue insistenze. Ho provato a far intervenire le autorità della città, ma invano. E adesso...";
					link.l1 = "E adesso che si fa?";
					link.l1.go = "SCQ_RapeWife";
				break;
				case "2":
					dialog.text = "Sai, sto cercando un mio compaesano. Tre anni fa siamo arrivati qui insieme dall’Europa in cerca di fortuna. Ci siamo persi di vista. Ma poco tempo fa ho sentito dire che ora fa il capitano mercante! Ho provato a rintracciarlo da solo, ma senza successo.";
					link.l1 = "Allora?";
					link.l1.go = "SCQ_Friend";
				break;
			}
		break;
		// квест бывшего раба, которого негодяй-кэп взял в плен
		case "SCQ_Slave":
			dialog.text = "Voglio che tu lo trovi e lo faccia fuori. Lo voglio morto così tanto che non riesco nemmeno a mangiare...";
			link.l1 = "Capisco... Suppongo di poterti aiutare in questa faccenda. Dimmi il suo nome e quello della sua nave.";
			link.l1.go = "SCQ_Slave_1";
			link.l2 = "Mi dispiace, ma non m'interessa.";
			link.l2.go = "SCQ_exit";
		break;
		case "SCQ_Slave_1":
			npchar.quest.SeekCap = "manSlave"; //личный флаг ситизена на квест
			SetSeekCapCitizenParam(npchar, PIRATE);
			dialog.text = ""+npchar.quest.SeekCap.capName+" dei "+GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName+"Voc"))+" chiamato "+npchar.quest.SeekCap.shipName+". Ti pagherò  "+FindRussianMoneyString(sti(npchar.quest.money))+", più tutti i miei gioielli."; // belamour gen
			link.l1 = "Capisco. Starò all’erta in mare. Se troverò il bersaglio... consideralo già sepolto.";
			link.l1.go = "SCQ_Slave_2";
			link.l2 = "Non muoverò un dito per così pochi dobloni. Cercati un altro babbeo per la tua vendetta.";
			link.l2.go = "SCQ_exit_clear";
		break;
		case "SCQ_Slave_2":
			dialog.text = "Era proprio quello che speravo di sentire! Ah, ora posso mangiare! Finalmente! Devo procurarmi qualcosa da mettere sotto i denti...";
			link.l1 = "Buon appetito. Ti troverò quando il lavoro sarà finito.";
			link.l1.go = "SCQ_Slave_3";
		break;
		case "SCQ_Slave_3":
			dialog.text = "Ti aspetterò nella chiesa del posto.";
			link.l1 = "Bene.";
			link.l1.go = "exit";
			//==> ставим квестодателя в церковь
			pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
			npchar.location = npchar.city + "_church";
			npchar.location.locator = "goto2";			
            pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
			pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
			pchar.quest.SeekShip_Stay.Idx = npchar.index;
			NextDiag.TempNode = "SCQ_manResult";
			sTitle = npchar.city + "SCQ_manSlave";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "SCQ_manSlave", "1");
			AddQuestUserDataForTitle(sTitle, "sName", GetFullName(npchar));
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Voc"))); // belamour gen
			AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
			AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sName2", GetFullName(npchar));
		break;
		//пират похитил жену у ситизена
		case "SCQ_RapeWife":
			dialog.text = "Ero troppo indolente e quel bastardo ha preso mia moglie e l'ha portata a bordo della sua nave. Ti chiedo di trovare questo furfante!";
			link.l1 = "Eh, e perché mai dovrei incrociare le lame con un altro canaglia?";
			link.l1.go = "SCQ_RapeWife_1";
		break;
		case "SCQ_RapeWife_1":
			npchar.quest.SeekCap = "manRapeWife"; //личный флаг ситизена на квест
			SetSeekCapCitizenParam(npchar, PIRATE);
			makearef(forName, npchar.quest.SeekCap);
			forName.nation = npchar.nation;
			forName.sex = "woman";
			SetRandomNameToCharacter(forName); //npchar.quest.SeekCap.name - имя жены ситизена
			forName.lastname = npchar.lastname; //фамилия как и у мужа есно
			dialog.text = "Non sono ricco, ma sarà un onore darti tutto il valore che possiedo! Se liberi mia moglie e me la riporti, ti pagherò "+FindRussianMoneyString(sti(npchar.quest.money))+", più tutti i miei gioielli.";
			link.l1 = "D'accordo, ci sto. Dimmi i dettagli. Il suo nome, la sua nave e come si chiama tua moglie.";
			link.l1.go = "SCQ_RapeWife_2";
			link.l2 = "No, compare, non lo faccio mica per una cifra così misera. Mi spiace...";
			link.l2.go = "SCQ_exit_clear";
		break;
		case "SCQ_RapeWife_2":
			dialog.text = "Il suo nome è "+npchar.quest.SeekCap.name+". E il nome del bastardo è "+npchar.quest.SeekCap.capName+", nuota avanti "+GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName+"Voc"))+" chiamato "+npchar.quest.SeekCap.shipName+"."; // belamour gen
			link.l1 = "La merda galleggia, compare. I capitani veleggiano...";
			link.l1.go = "SCQ_RapeWife_3";
		break;
		case "SCQ_RapeWife_3":
			dialog.text = "Sì, sì, vi chiedo perdono! Non sono un marinaio, spero che possiate capirlo...";
			link.l1 = "Va bene, non ti preoccupare. In ogni caso, tornerò appena sarà fatto.";
			link.l1.go = "SCQ_RapeWife_4";
		break;
		case "SCQ_RapeWife_4":
			dialog.text = "Grazie di cuore! Ti aspetterò nella chiesa del posto. Ma ti supplico, fa' presto. Temo davvero per mia moglie...";
			link.l1 = "Già, non la invidio nemmeno io.";
			link.l1.go = "exit";
			//==> ставим квестодателя в церковь
			pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
			npchar.location = npchar.city + "_church";
			npchar.location.locator = "goto2";			
            pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
			pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
			pchar.quest.SeekShip_Stay.Idx = npchar.index;
			NextDiag.TempNode = "SCQ_manResult";
			sTitle = npchar.city + "SCQ_manRapeWife";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "SCQ_manRapeWife", "1");
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Voc"))); // belamour gen
			AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
			AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sName2", npchar.quest.SeekCap.name + " " + npchar.quest.SeekCap.lastname);
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
		break;
		//поиски земляка
		case "SCQ_Friend":
			dialog.text = "Il guaio è che il mio amico non possiede alcuna proprietà. La sua nave è la sua dimora. Dunque non riesco mai a trovarlo, perché naviga sempre. E non posso permettermi viaggi a vuoto, devo guadagnare il pane per campare.";
			link.l1 = "Non posso aiutarti, se non hai monete in tasca...";
			link.l1.go = "SCQ_Friend_1";
		break;
		case "SCQ_Friend_1":
			npchar.quest.SeekCap = "manFriend"; //личный флаг ситизена на квест
			SetSeekCapCitizenParam(npchar, sti(npchar.nation));
			dialog.text = "Posso pagarti "+FindRussianMoneyString(sti(npchar.quest.money))+" e ti darò tutti i miei gioielli. Questo è tutto ciò che posso permettermi al momento.";
			link.l1 = "Questa somma mi va a genio. Ci sto. Anzi, puoi salire a bordo come passeggero, così rivedrai il tuo compare appena lo troviamo.";
			link.l1.go = "SCQ_Friend_2";
			link.l2 = "Non mi basta. Cerca qualcun altro che faccia il lavoro.";
			link.l2.go = "SCQ_exit_clear";
		break;
		case "SCQ_Friend_2":
			dialog.text = "No, credo che resterò qui. Non si sa quanto dureranno queste ricerche e potrei perdere tutto il mio denaro. Qui ho un lavoro.";
			link.l1 = "Capisco. Ora dimmi, chi è il tuo compare e su quale nave si trova.";
			link.l1.go = "SCQ_Friend_3";
		break;
		case "SCQ_Friend_3":
			dialog.text = "Il suo nome è "+npchar.quest.SeekCap.capName+". Per quanto ne so, lui comanda una "+GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName+"Acc"))+" chiamato "+npchar.quest.SeekCap.shipName+"."; // belamour gen
			link.l1 = "Capisco. Beh, riferirò al tuo compare di te, se mai lo incrocio.";
			link.l1.go = "SCQ_Friend_4";
		break;
		case "SCQ_Friend_4":
			dialog.text = "Grazie. T’aspetterò nella chiesa del posto. Le tue monete le avrai quando il lavoro sarà fatto.";
			link.l1 = "Certo. Addio allora, presto avrai mie notizie.";
			link.l1.go = "exit";
			//==> ставим квестодателя в церковь
			pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
			npchar.location = npchar.city + "_church";
			npchar.location.locator = "goto2";			
            pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
			pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
			pchar.quest.SeekShip_Stay.Idx = npchar.index;
			NextDiag.TempNode = "SCQ_manResult";
			sTitle = npchar.city + "SCQ_manFriend";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "SCQ_manFriend", "1");
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Voc"))); // belamour gen
			AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
			AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "sSex1", GetSexPhrase("",""));
		break;

		// --- результаты мужских квестов ---
		case "SCQ_manResult":
			dialog.text = "Buondì a voi, capitano. Avete già qualche novità?";
			link.l1 = "Ricordammi qual è il tuo guaio...";
			link.l1.go = "SCQ_manResult_exit";
			switch (npchar.quest.SeekCap)
			{
				case "manSlaveover":
					dialog.text = "Immagino che la mia vendetta sia stata compiuta. È così?";
					link.l1 = "Esattamente. "+npchar.quest.SeekCap.capName+" è morto e il suo "+GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName))+" è sul fondo del mare.";
					link.l1.go = "SCQR_manSlave";
				break;
				case "manRapeWifeover":
					dialog.text = "Hai trovato mia moglie! Non ci posso credere! Davvero?";
					link.l1 = "Puoi farlo. È la mia passeggera. Puoi riportarla indietro, se vuoi "+npchar.quest.SeekCap.name+" "+npchar.quest.SeekCap.lastname+" sei davvero tu, moglie...";
					link.l1.go = "SCQR_manRapeWife";
				break;
				case "manFriendover":
					dialog.text = "Buon giorno a voi, capitano. Avete trovato il mio compare?";
					link.l1 = "Ho fatto e gli ho parlato di te.";
					link.l1.go = "SCQR_manFriend";
				break;
			}
		break;
		case "SCQ_manResult_exit":
			switch (npchar.quest.SeekCap)
			{
				case "manSlave":
					dialog.text = "Cosa? Hai davvero dimenticato che ti ho chiesto di vendicare il capitano "+npchar.quest.SeekCap.capName+" per un anno della mia schiavitù?";
					link.l1 = "No, non l'ho fatto.";
					link.l1.go = "exit";
				break;
				case "manRapeWife":
					dialog.text = "Non posso credere alle mie orecchie! Hai forse dimenticato che ti ho chiesto di trovare e liberare mia moglie? È stata catturata dal filibustiere chiamato "+npchar.quest.SeekCap.capName+"!";
					link.l1 = "Non l'ho fatto.";
					link.l1.go = "exit";
				break;
				case "manFriend":
					dialog.text = "Aspetta un attimo... Hai già dimenticato la promessa che mi hai fatto di cercare il mio compare di nome "+npchar.quest.SeekCap.capName+"?";
					link.l1 = "Non l’ho fatto.";
					link.l1.go = "exit";
				break;
			}
		break;

		case "SCQR_manSlave":
			dialog.text = "Eccellente, avevo visto giusto su di te! Dunque, come ti avevo promesso, ecco il tuo "+FindRussianMoneyString(sti(npchar.quest.money))+" e gioielli. Ti ringrazio per l’aiuto.";
			link.l1 = "Sei il benvenuto...";
			link.l1.go = "SCQ_exit";
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть горожанина-квестодателя
			AddMoneyToCharacter(pchar, sti(npchar.quest.money));
			TakeNItems(pchar, npchar.quest.gem, 10+hrand(8));
			sTitle = npchar.city + "SCQ_manSlave";
			CloseQuestHeader(sTitle);
		break;
		case "SCQR_manRapeWife":
			dialog.text = "Madonna santa! Ci hai salvati! Ti prego, prendi il tuo "+FindRussianMoneyString(sti(npchar.quest.money))+" e gioielli. Sappi che pregheremo per te in eterno!";
			link.l1 = "Prega pure, se ti fa piacere. Non ho nulla in contrario.";
			link.l1.go = "SCQ_exit";
			sld = characterFromId("manRapeWife_" + npchar.City);
			RemovePassenger(pchar, sld);
			sld.lifeDay = 0;
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть горожанина-квестодателя
			AddMoneyToCharacter(pchar, sti(npchar.quest.money));
			TakeNItems(pchar, npchar.quest.gem, 12+hrand(8));
			sTitle = npchar.city + "SCQ_manRapeWife";
			CloseQuestHeader(sTitle);
		break;
		case "SCQR_manFriend":
			dialog.text = "Splendido!... Ecco, prendi "+FindRussianMoneyString(sti(npchar.quest.money))+" e gioielli. E grazie, capitano.";
			link.l1 = "Sei il benvenuto, amico. Addio...";
			link.l1.go = "SCQ_exit";
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть горожанина-квестодателя
			AddMoneyToCharacter(pchar, sti(npchar.quest.money));
			TakeNItems(pchar, npchar.quest.gem, 8+hrand(8));
			sTitle = npchar.city + "SCQ_manFriend";
			CloseQuestHeader(sTitle);
		break;
		//========= квесты баб ===========
		case "SCQ_woman":
			dialog.text = LinkRandPhrase("Saluti, capitano. Puoi darmi una mano?","Capitano! Potete prestare soccorso a una donna? Vorreste essere così gentile da...","Capitano, aiuto "+GetSexPhrase("una fanciulla","io")+".");
			link.l1 = RandPhraseSimple("Sono occupato.","Mi dispiace, "+GetAddress_FormToNPC(NPChar)+", ma non ho tempo da perdere...");
			link.l1.go = "SCQ_exit";
			link.l2 = RandPhraseSimple("Che ti rode, "+GetAddress_FormToNPC(NPChar)+"?","Dimmi i tuoi guai, "+GetAddress_FormToNPC(NPChar)+"Ci proverò ad aiutarti.");
			link.l2.go = "SCQ_woman_1";
		break;
		//выбираем квест
		case "SCQ_woman_1":
			switch (npchar.quest.SeekCap.numQuest)
			{
				case "0":
					dialog.text = "Mio marito è un mercante, porta merci in ogni colonia dei dintorni. Tre mesi fa è salpato per mare. Non è ancora tornato!";
					link.l1 = "Pensi che gli sia capitato qualcosa?";
					link.l1.go = "SCQ_Hasband";
				break;
				case "1":
					dialog.text = ""+GetSexPhrase("Capitano, vedo che siete un coraggioso capitano, un vero furfante","Capitana, vedo che siete una donna di gran tempra, capace di tener testa a qualunque uomo")+"...";
					link.l1 = "E perché mai lo dici, "+GetAddress_FormToNPC(NPChar)+"?";
					link.l1.go = "SCQ_Revenge";
				break;
				case "2":
					dialog.text = "Capitano, vi prego, aiutatemi! Mio marito è stato catturato! Potete salvarlo?";
					link.l1 = "Aspetta un attimo, non ci sto capendo niente. Chi ha catturato chi?";
					link.l1.go = "SCQ_Pirates";
				break;
			}
		break;
		
		//жещина разыскивает мужа-торговца
		case "SCQ_Hasband":
			dialog.text = "Non lo so, ma continuo a sperare che sia solo troppo occupato per scrivermi. Avrebbe potuto mandarmi una lettera, sa bene quanto mi preoccupo per lui!";
			link.l1 = "Non è sicuro in mare, può capitare di tutto...";
			link.l1.go = "SCQ_Hasband_1";
		break;
		case "SCQ_Hasband_1":
			npchar.quest.SeekCap = "womanHasband"; //личный флаг ситизена на квест
			SetSeekCapCitizenParam(npchar, sti(npchar.nation));
			dialog.text = "Esatto! Capisci bene di cosa parlo. Hai proprio l’aspetto di un "+GetSexPhrase("capitano valoroso","ragazza coraggiosa")+", dunque vorrei chiederti di ritrovare mio marito. Sono pronta a pagarti "+FindRussianMoneyString(sti(npchar.quest.money))+", e in più ti consegnerò tutti i miei gioielli.";
			link.l1 = "Bene. Parlerò a tuo marito delle tue preoccupazioni, se lo incontrerò in mare o altrove. Dimmi il suo nome e il nome della sua nave.";
			link.l1.go = "SCQ_Hasband_2";
			link.l2 = "Una miseria del genere non mi interessa.";
			link.l2.go = "SCQ_exit_clear";
		break;
		case "SCQ_Hasband_2":
			dialog.text = "Si chiama "+npchar.quest.SeekCap.capName+". Naviga su un "+GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName+"Voc"))+" chiamato "+npchar.quest.SeekCap.shipName+".";  // belamour gen
			link.l1 = "Capisco. Ora devi aspettare. Cerca di passare la maggior parte del tempo in chiesa, così potrò trovarti.";
			link.l1.go = "exit";
			//==> ставим квестодателя в церковь
			pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
			npchar.location = npchar.city + "_church";
			npchar.location.locator = "goto2";			
            pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
			pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
			pchar.quest.SeekShip_Stay.Idx = npchar.index;
			NextDiag.TempNode = "SCQ_womanResult";
			sTitle = npchar.city + "SCQ_womanHasband";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "SCQ_womanHasband", "1");
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Dat")));
			AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
			AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
		break;
		//месть отвергнутой женщины
		case "SCQ_Revenge":
			dialog.text = ""+GetSexPhrase("Lo dico, buon signore, perché intendo ingaggiarvi per un incarico che vi è familiare... per così dire.","Voglio che tu mi dia una mano. Spero che tu riesca a capirmi come donna.")+"Un capitano m’ha fatto saltare la mosca al naso e lo voglio vedere crepare.";
			link.l1 = "E che t’ha fatto di male quell’anima disgraziata?";
			link.l1.go = "SCQ_Revenge_1";
		break;
		case "SCQ_Revenge_1":
			dialog.text = "Quel mascalzone mi ha ingannata. Ha finto d’essere innamorato di me, mi faceva pure la corte. E tutto solo per mettere le mani su qualcosa di prezioso che apparteneva a mio marito! E quando il cane ha ottenuto ciò che voleva, m’ha detto che non significava nulla... che eravamo solo amici!";
			link.l1 = "Hmm, forse aveva ragione?";
			link.l1.go = "SCQ_Revenge_2";
		break;
		case "SCQ_Revenge_2":
			dialog.text = "Sembro forse uno scimunito?! Credi davvero che non sappia distinguere tra un corteggiamento e quattro chiacchiere da bettola?";
			link.l1 = "Sicuro che sì...";
			link.l1.go = "SCQ_Revenge_3";
		break;
		case "SCQ_Revenge_3":
			dialog.text = "Mi ha usato, quel furfante! Non glielo perdonerò mai, dannazione!";
			link.l1 = "Sì, gli uomini sono fatti così. Ma forse puoi darti una calmata? Non c’è nulla di tremendo in tutto ciò...";
			link.l1.go = "SCQ_Revenge_4";
		break;
		case "SCQ_Revenge_4":
			dialog.text = "Niente di terribile?! "+GetSexPhrase("Sei un moralista di qualche sorta, non sei un vero pirata!","Pare proprio che tu non ti sia mai trovato in una situazione simile! Eh già, chi mai rischierebbe... e io sono solo una povera donna indifesa...");
			link.l1 = "Bene. Basta così. Voglio solo sapere quanto son serie le tue intenzioni.";
			link.l1.go = "SCQ_Revenge_5";
		break;
		case "SCQ_Revenge_5":
			dialog.text = "Maledizione, "+GetSexPhrase(" non hai la minima idea di come sia la vendetta di una donna respinta ","sei una donna e devi capire cosa si prova ad essere rifiutata! Voglio la mia vendetta ")+"!";
			link.l1 = ""+GetSexPhrase("È vero, mai vissuto niente di simile","Beh, sai, lei si metterebbe a piangere un po', spaccherebbe qualche bicchiere e tutto finirebbe lì")+"...";
			link.l1.go = "SCQ_Revenge_6";
		break;
		case "SCQ_Revenge_6":
			dialog.text = ""+GetSexPhrase("Considerati fortunato. Una donna respinta e tradita nelle sue attese è una furia, un demonio in gonnella! Nulla al mondo potrà placare la sua collera","E io non sono come lei. Nulla potrebbe placare la mia furia")+"!\nVoglio che tu lo mandi all’altro mondo di persona. E prima che esali l’ultimo respiro, dovrà sapere chi ha pagato per la sua morte...";
			link.l1 = "Hmm, non so nemmeno cosa dire... E quanto mi offri, capitano?";
			link.l1.go = "SCQ_Revenge_7";
		break;
		case "SCQ_Revenge_7":
			npchar.quest.SeekCap = "womanRevenge"; //личный флаг ситизена на квест
			SetSeekCapCitizenParam(npchar, PIRATE);
			dialog.text = "Tutto ciò che possiedo. Ti darò i miei gioielli e "+FindRussianMoneyString(sti(npchar.quest.money))+"Affare fatto?";
			link.l1 = "Sono interessato. Dimmi il suo nome e quello della sua nave.";
			link.l1.go = "SCQ_Revenge_8";
			link.l2 = "Non mi interessa. Addio.";
			link.l2.go = "SCQ_exit_clear";
		break;
		case "SCQ_Revenge_8":
			dialog.text = "Il nome di quella canaglia è "+npchar.quest.SeekCap.capName+" e naviga su una "+GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName+"Gen"))+" chiamato "+npchar.quest.SeekCap.shipName+"."; // belamour gen
			link.l1 = "Consideralo fatto, "+GetAddress_FormToNPC(NPChar)+". Aspettami nella chiesa del posto. Spero che ti calmerai un po'...";
			link.l1.go = "exit";
			//==> ставим квестодателя в церковь
			pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
			npchar.location = npchar.city + "_church";
			npchar.location.locator = "goto2";			
            pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
			pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
			pchar.quest.SeekShip_Stay.Idx = npchar.index;
			NextDiag.TempNode = "SCQ_womanResult";
			sTitle = npchar.city + "SCQ_womanRevenge";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "SCQ_womanRevenge", "1");
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Dat")));
			AddQuestUserData(sTitle, "sShipTypeName2", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Gen")));
			AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
			AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sName2", GetFullName(npchar));
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "sSex1", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "sSex2", GetSexPhrase("",""));
		break;
		//муж женщины попал в плен к пиратам
		case "SCQ_Pirates":
			dialog.text = "Ti spiego. Il guaio è che mio marito, un uomo semplice, è stato preso dai piratti! Ammazzavano chiunque e non hanno risparmiato anima viva...";
			link.l1 = "Pare che il capitano abbia osato ribellarsi. Altrimenti avrebbero risparmiato l’equipaggio.";
			link.l1.go = "SCQ_Pirates_1";
		break;
		case "SCQ_Pirates_1":
			dialog.text = "Forse sì, ma mio marito è un’anima innocente. Era solo un passeggero, laggiù. Ha dovuto dire loro d’esser ricco per salvar la pellaccia. I pirati l’han risparmiato, nemmeno l’han chiuso nella stiva.";
			link.l1 = "E come fai a saperlo?";
			link.l1.go = "SCQ_Pirates_2";
		break;
		case "SCQ_Pirates_2":
			dialog.text = "È riuscito a mandarmi una lettera. Scriveva che sta bene e che lo tengono in una cabina, non insieme agli altri prigionieri.";
			link.l1 = "E cosa pensi di fare? Non può andare avanti così. Prima o poi, quei cani di pirati lo sgameranno.";
			link.l1.go = "SCQ_Pirates_3";
		break;
		case "SCQ_Pirates_3":
			dialog.text = "Sei anche tu un pirata? Sì, sì, lo so... Ti supplico, aiutaci, salva mio marito! Ha descritto quella nave pirata e scritto il nome del capitano. Non ti sarà difficile trovarli!";
			link.l1 = "Non è così semplice come credi. Tutti i prigionieri spettano di diritto al capitano che ha catturato tuo marito, e poi ci vorrà del tempo.";
			link.l1.go = "SCQ_Pirates_4";
		break;
		case "SCQ_Pirates_4":
			dialog.text = "Ma almeno puoi provarci! Inoltre, hai abbastanza tempo per cercare. Mio marito non è uno sprovveduto e si spaccia per mercante del Vecchio Mondo, così quei filibustieri per ora non gli chiedono dobloni. Se lo liberi, ti darò tutto ciò che possiedo!";
			link.l1 = "E che cosa hai da offrire?";
			link.l1.go = "SCQ_Pirates_5";
		break;
		case "SCQ_Pirates_5":
			npchar.quest.SeekCap = "womanPirates"; //личный флаг ситизена на квест
			SetSeekCapCitizenParam(npchar, PIRATE);
			dialog.text = "Non molto, "+FindRussianMoneyString(sti(npchar.quest.money))+" e tutti i miei gioielli... Ma pregherò per la tua anima in eterno!";
			link.l1 = "Sì, davvero non è molto... Va bene, sono pronto ad aiutarti.";
			link.l1.go = "SCQ_Pirates_6";
			link.l2 = "Mi dispiace, ma per me non basta.";
			link.l2.go = "SCQ_exit_clear";
		break;
		case "SCQ_Pirates_6":
			dialog.text = "Grazie, grazie di cuore!";
			link.l1 = "Mi ringrazierai, se avrò successo, quindi fermati. Faresti meglio a dirmi il nome di tuo marito e tutto quello che sai su quei cani di pirati.";
			link.l1.go = "SCQ_Pirates_7";
		break;
		case "SCQ_Pirates_7":
			makearef(forName, npchar.quest.SeekCap);
			forName.nation = npchar.nation;
			forName.sex = "man";
			SetRandomNameToCharacter(forName); //npchar.quest.SeekCap.name - имя жены ситизена
			forName.lastname = npchar.lastname; //фамилия как и у жены есно
			dialog.text = "Si chiama "+GetFullName(forName)+". Del Capitano "+npchar.quest.SeekCap.capName+", naviga verso "+GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName+"Voc"))+" chiamato "+npchar.quest.SeekCap.shipName+"."; // belamour gen
			link.l1 = "Capisco. Ora non ti resta che attendere e sperare che io abbia fortuna nella mia ricerca. Rimani in chiesa, aspetta e prega...";
			link.l1.go = "exit";
			//==> ставим квестодателя в церковь
			pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
			npchar.location = npchar.city + "_church";
			npchar.location.locator = "goto2";			
            pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
			pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
			pchar.quest.SeekShip_Stay.Idx = npchar.index;
			NextDiag.TempNode = "SCQ_womanResult";
			sTitle = npchar.city + "SCQ_womanPirates";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "SCQ_womanPirates", "1");
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName + "Voc"))); // belamour gen
			AddQuestUserData(sTitle, "sShipTypeName2", GetStrSmallRegister(XI_ConvertString(npchar.quest.SeekCap.shipTapeName))); // belamour gen
			AddQuestUserData(sTitle, "sShipName", npchar.quest.SeekCap.shipName);
			AddQuestUserData(sTitle, "sCapName", npchar.quest.SeekCap.capName);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sName2", GetFullName(forName));
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "sSex1", GetSexPhrase("",""));
		break;
		// --- результаты женских квестов ---
		case "SCQ_womanResult":
			dialog.text = "Oh, capitano, che gioia vederti! Dimmi presto, che novità porti riguardo al mio incarico?";
			link.l1 = "Uh, rammentami, "+GetAddress_FormToNPC(NPChar)+", di quale incarico vai cianciando?";
			link.l1.go = "SCQ_womanResult_exit";
			switch (npchar.quest.SeekCap)
			{
				case "womanHasbandover":
					dialog.text = "Ah, capitano, ho ricevuto una lettera da mio marito! Ha scritto che l’avete trovato.";
					link.l1 = "Sì, è corretto, "+GetAddress_FormToNPC(NPChar)+".   Tuo marito, "+npchar.quest.SeekCap.capName+",  sta bene e in salute. È solo troppo occupato...";
					link.l1.go = "SCQR_womanHasband";
				break;
				case "womanRevengeover":
					dialog.text = "Che ne dici, capitano? Hai fatto quel che ti avevo chiesto? Il capitano "+npchar.quest.SeekCap.capName+" morto?";
					link.l1 = "Sì, è morto, "+GetAddress_FormToNPC(NPChar)+". Gli dissi chi fu la causa della sua morte. L’ultima parola che udì in vita sua fu il tuo nome.";
					link.l1.go = "SCQR_womanRevenge";
				break;
				case "womanPiratesover":
					dialog.text = "Hai salvato mio marito! Ti supplico, dimmi che è vero!";
					link.l1 = "Sì, proprio così. Al momento si trova sulla mia nave. Puoi vederlo se vuoi "+npchar.quest.SeekCap.name+" "+npchar.quest.SeekCap.lastname+"è davvero tuo marito...";
					link.l1.go = "SCQR_womanPirates";
				break;
			}
		break;
		case "SCQ_womanResult_exit":
			switch (npchar.quest.SeekCap)
			{
				case "womanHasband":
					dialog.text = "Davvero hai dimenticato che mi avevi promesso di ritrovare mio marito? Si chiama "+npchar.quest.SeekCap.capName+"!";
					link.l1 = "Oh, sì, certo... Non me ne sono dimenticato.";
					link.l1.go = "exit";
				break;
				case "womanRevenge":
					dialog.text = "Non capisco! Hai forse dimenticato che devi uccidere il mio torturatore, un capitano di nome "+npchar.quest.SeekCap.capName+"?!?";
					link.l1 = "Oh per carità, certo che no. Il tuo ordine è in lavorazione, abbi pazienza...";
					link.l1.go = "exit";
				break;
				case "womanPirates":
					dialog.text = "Per tutti i santi, capitano, avete già dimenticato la promessa di liberare mio marito?";
					link.l1 = "Non l'ho fatto. Ti ricordi ... 'Aspetta e prega!'. Basta aspettare, "+GetAddress_FormToNPC(NPChar)+" "+npchar.lastname+".";
					link.l1.go = "exit";
				break;
			}
		break;

		case "SCQR_womanHasband":
			dialog.text = "Oh, Dio, ti sono tanto riconoscente! E sì, prendi pure il tuo "+FindRussianMoneyString(sti(npchar.quest.money))+". E grazie ancora!";
			link.l1 = "Mm, sei il benvenuto...";
			link.l1.go = "SCQ_exit";
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть горожанина-квестодателя
			AddMoneyToCharacter(pchar, sti(npchar.quest.money));
			TakeNItems(pchar, npchar.quest.gem, 8+hrand(8));
			sTitle = npchar.city + "SCQ_womanHasband";
			CloseQuestHeader(sTitle);
		break;
		case "SCQR_womanRevenge":
			dialog.text = "Magnifico! Bene, prendi pure il tuo "+FindRussianMoneyString(sti(npchar.quest.money))+" e gioielli. Addio...";
			link.l1 = "Addio. ";
			link.l1.go = "SCQ_exit";
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть горожанина-квестодателя
			AddMoneyToCharacter(pchar, sti(npchar.quest.money));
			TakeNItems(pchar, npchar.quest.gem, 10+hrand(8));
			TakeNItems(pchar, "jewelry47", rand(3));
			TakeNItems(pchar, "jewelry43", rand(3));
			TakeNItems(pchar, "jewelry41", rand(3));
			TakeNItems(pchar, "jewelry48", rand(3));
			TakeNItems(pchar, "jewelry51", rand(3));
			TakeNItems(pchar, "jewelry46", rand(3));
			TakeNItems(pchar, "jewelry49", rand(3));
			TakeNItems(pchar, "jewelry40", rand(3));
			sTitle = npchar.city + "SCQ_womanRevenge";
			CloseQuestHeader(sTitle);
		break;
		case "SCQR_womanPirates":
			dialog.text = "Sicuro che sia lui! Santo cielo, capitano, vi sono tanto grato. Prendete il vostro "+FindRussianMoneyString(sti(npchar.quest.money))+". Pregarò per te ogni giorno della mia vita!";
			link.l1 = "Sembra una buona trovata...";
			link.l1.go = "SCQ_exit";
			sld = characterFromId("womanPirates_" + npchar.City);
			RemovePassenger(pchar, sld);
			sld.lifeDay = 0;
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть горожанина-квестодателя
			AddMoneyToCharacter(pchar, sti(npchar.quest.money));
			TakeNItems(pchar, npchar.quest.gem, 12+hrand(8));
			sTitle = npchar.city + "SCQ_womanPirates";
			CloseQuestHeader(sTitle);
		break;
		//========= разыскиваемый капитан-работорговец ===========
		case "CitizCap": //встреча на суше
			switch (npchar.quest.SeekCap)
			{
				case "manSlave":
					dialog.text = "Saluti al mio compagno. Cerchi qualcosa?"+GetSexPhrase(", compare ",",  ragazza")+"?";
					link.l1 = "Il tuo nome è "+GetFullName(npchar)+", ho ragione?";
					link.l1.go = "CCmanSlave";
				break;
			}
		break;
		case "CCmanSlave":
			dialog.text = "Sì, sei proprio tu!";
			link.l1 = "Peccato per te. Ti dirò un nome, e faresti meglio a ricordartelo."+GetFullName(&characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)])+". Te lo ricordi?";
			link.l1.go = "CCmanSlave_1";
		break;
		case "CCmanSlave_1":
			dialog.text = "Hm, sì che lo faccio...";
			link.l1 = "Ascolta bene, compare. È furibondo con te. È giunta l’ora di pagare per aver venduto un uomo libero in schiavitù.";
			link.l1.go = "CCmanSlave_2";
		break;
		case "CCmanSlave_2":
			dialog.text = "Pagare?! Ma che diavolo stai blaterando?";
			link.l1 = "Voglio dire che ti farò fuori proprio dove stai, maledetto.";
			link.l1.go = "CCmanSlave_3";
		break;
		case "CCmanSlave_3":
			dialog.text = "Pensa un po', per chi lavori tu?! Quest'uomo è un poveraccio e il suo posto è nelle piantagioni di zucchero!";
			link.l1 = "Ebbene, questo non ti riguarda. Ora devi rispondere delle tue azioni!";
			link.l1.go = "CCmanSlave_4";
		break;
		case "CCmanSlave_4":
			dialog.text = "Ho! Risponderò come sono solito fare!";
			link.l1 = "Continua...";
			link.l1.go = "CCmanSlave_fight";
		break;
		case "CCmanSlave_fight":
			NextDiag.TempNode = "CitizCap_inDeck_exit";
			npchar.DeckDialogNode = "CitizCap_inDeck_exit";
			LAi_group_Attack(NPChar, Pchar);
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "CitizCap_inDeck": //встреча на палубе
			dialog.text = "Cosa vuoi, marinaio?";
			link.l1 = "Voglio chiederti, porti passeggeri? ";
			link.l1.go = "CitizCap_inDeck_1";
		break;
		case "CitizCap_inDeck_1":
			dialog.text = "E che t’importa a te?";
			link.l1 = "Solo una domanda.";
			link.l1.go = "CitizCap_inDeck_2";
		break;
		case "CitizCap_inDeck_2":
			dialog.text = "Solo per chiedere... Senti, faresti meglio a toglierti dai piedi finché te ne do ancora la possibilità. Non mi piaci!";
			link.l1 = "Va bene, va bene, calmati. Me ne vado...";
			link.l1.go = "exit";
			NextDiag.TempNode = "CitizCap_inDeck_exit";
			npchar.DeckDialogNode = "CitizCap_inDeck_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName + "Gen")));
		break;
		case "CitizCap_inDeck_exit":
			dialog.text = "Abbiamo già parlato, quindi non mettere alla prova la mia pazienza!";
			link.l1 = "Non lo farò.";
			link.l1.go = "exit";
			NextDiag.TempNode = "CitizCap_inDeck_exit";
		break;
		//========= разыскиваемый кэп, похитивший чужую жену ===========
		case "RapeWifeCap":  //встреча на суше
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			dialog.text = "Salute, collega! Hai bisogno di qualcosa?";
			link.l1 = "Vorrei sapere, non sei stato tu a portare via la donna da "+XI_ConvertString("Colony"+npchar.quest.cribCity+"Gen")+" chiamato "+GetFullName(sld)+"?";
			link.l1.go = "RapeWifeCap_1";
		break;
		case "RapeWifeCap_1":
			dialog.text = "Heh, hai ragione, è nella mia cabina! Una bella pollastra, con gambe da favola... Ma perché lo chiedi?";
			link.l1 = "Compare, questa donna è sposata. Questo non va bene.";
			link.l1.go = "RapeWifeCap_2";
		break;
		case "RapeWifeCap_2":
			dialog.text = "E allora? Mi piace, punto e basta. Non lascerò che qualche pezzente venga a ficcare il naso nei nostri affari solo perché è suo marito!";
			link.l1 = "Lascia che ti dica che la Confraternita non vede di buon occhio certe faccende, e se certe orecchie vengono a sapere di quel che hai fatto, il marchio nero cadrà su di te.";
			link.l1.go = "RapeWifeCap_3";
		break;
		case "RapeWifeCap_3":
			dialog.text = "Vuoi forse farmi la predica?";
			link.l1 = "Calmati, volevo solo curiosare... Addio.";
			link.l1.go = "exit";
			NextDiag.TempNode = "RapeWifeCap_exit";
			npchar.DeckDialogNode = "RapeWifeCap_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName + "Gen")));
		break;
		case "RapeWifeCap_exit":
			dialog.text = "Abbiamo già parlato di quella donna. Non ho voglia di tornarci sopra, dannazione!";
			link.l1 = "Come vuoi...";
			link.l1.go = "exit";
			NextDiag.TempNode = "RapeWifeCap_exit";
		break;
		case "RapeWifeCap_inDeck":  //встреча на палубе
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			dialog.text = "Sono lieto di salutare un collega sul mio ponte! Che desideri?";
			link.l1 = "Vorrei sapere se avete rapito una donna da "+XI_ConvertString("Colony"+npchar.quest.cribCity+"Gen")+" di nome "+GetFullName(sld)+"?";
			link.l1.go = "RapeWifeCap_1";
		break;
		case "RapeWifeCap_inDeck_1":
			dialog.text = "Heh, hai ragione, è nella mia cabina! Una bella figliola, gambe da urlo!... Ma perché lo chiedi?";
			link.l1 = "Compare, questa donna è maritata. Non è cosa giusta.";
			link.l1.go = "RapeWifeCap_inDeck_2";
		break;
		case "RapeWifeCap_inDeck_2":
			dialog.text = "E allora? Mi piace, punto e basta. Non lascerò che qualche straccione si metta in mezzo tra noi solo perché è suo marito!";
			link.l1 = "Lascia che ti dica che la Fratellanza non guarda di buon occhio certe faccende, e se la voce di ciò che hai fatto giungesse alle orecchie sbagliate, il marchio nero ti verrebbe recapitato.";
			link.l1.go = "RapeWifeCap_inDeck_3";
		break;
		case "RapeWifeCap_inDeck_3":
			dialog.text = "Vuoi forse farmi la predica?";
			link.l1 = "Rilassati, era solo curiosità... Addio.";
			link.l1.go = "exit";
			NextDiag.TempNode = "RapeWifeCap_exit";
			npchar.DeckDialogNode = "RapeWifeCap_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName + "Gen")));
		break;
		case "RapeWifeCap_Board": //абордаж
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			dialog.text = "Cosa vuoi da me, canaglia?!";
			link.l1 = "Sono qui per la donna che hai rapito al marito. Ricorda "+XI_ConvertString("Colony"+npchar.quest.cribCity)+"? Il suo nome è "+sld.quest.SeekCap.name+" "+sld.quest.SeekCap.lastname+".";
			link.l1.go = "RapeWifeCap_Board_1";
		break;
		case "RapeWifeCap_Board_1":
			dialog.text = "Maledizione! Non la vedrai mai, come non vedrai mai le tue orecchie!";
			link.l1 = "Idiota. Li vedo riflessi nello specchio. E ora taglierò i tuoi!";
			link.l1.go = "RapeWifeCap_Board_2";
		break;
		case "RapeWifeCap_Board_2":
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogFree(); // важный метод
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "CitizSeekCap_afterCabinFight");
			pchar.GenQuest.CitizSeekCap.label = npchar.quest.SeekCap; //флаг квеста для нпс
			pchar.GenQuest.CitizSeekCap.nation = npchar.nation;	//нацию для нпс
			pchar.GenQuest.CitizSeekCap.sex = "woman";
			pchar.GenQuest.CitizSeekCap.ani = "towngirl";
			pchar.GenQuest.CitizSeekCap.model = "women_"+(hrand(3)+7); //модель для нпс
			pchar.GenQuest.CitizSeekCap.WifeCity = npchar.quest.cribCity; //исходный город для нпс
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			pchar.GenQuest.CitizSeekCap.WifeName = sld.quest.SeekCap.name; //имя и фамилию для нпс
			pchar.GenQuest.CitizSeekCap.WifeLastname = sld.quest.SeekCap.lastname;
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		//========= похищенная жена ===========
		case "manRapeWife_Board":
			dialog.text = "Chi sei, tu?";
			link.l1 = "Salve. Sono venuto per te su richiesta di tuo marito. Ora sei libera e posso portarti da lui.";
			link.l1.go = "manRapeWife_Board_1";
		break;
		case "manRapeWife_Board_1":
			dialog.text = "È forse un sogno?! Può esser vero?!";
			link.l1 = "Così è, "+GetAddress_FormToNPC(NPChar)+".";
			link.l1.go = "manRapeWife_Board_2";
		break;
		case "manRapeWife_Board_2":
			dialog.text = "Lodiamo il Signore! Son pronto, portami via da questa maledetta tana!";
			link.l1 = "Certo, "+GetAddress_FormToNPC(NPChar)+", preparatevi per un sicuro ritorno da vostro marito.";
			link.l1.go = "exit";
			//уберем жену из каюты
			npchar.location = "none";
			npchar.location.locator = "";
			LAi_SetPlayerType(pchar);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			sld.quest.SeekCap = sld.quest.SeekCap + "over"; //дополняем флаг квест до 'выполнен'
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "6");
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony"+npchar.quest.cribCity+"Acc"));
		break;
		//========= разыскиваемый земляк-торговый кэп ===========
		case "FriendCap": //встреча на суше
			dialog.text = "Salve! Lieto di salutare un collega a terra...";
			link.l1 = TimeGreeting()+", ho da discutere d'affari con te.";
			link.l1.go = "FriendCap_1";
		break;
		case "FriendCap_1":
			dialog.text = "Ascolto, parla pure.";
			link.l1 = "Un tuo compare ti sta cercando. Veleggiavate insieme e siete arrivati qui dal Vecchio Mondo."+GetFullName(&characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)])+", ricordi?";
			link.l1.go = "FriendCap_2";
		break;
		case "FriendCap_2":
			dialog.text = "Ah, certo che lo so! E dove diavolo abita adesso?";
			link.l1 = "In "+XI_ConvertString("Colony"+npchar.quest.cribCity+"Dat");
			link.l1.go = "FriendCap_3";
		break;
		case "FriendCap_3":
			dialog.text = " Grazie! Sai, pensavo che tu fossi un pirata!";
			link.l1 = "Lo sono. In un certo senso. O forse no. Ma oggi sono di buon umore, quindi non hai nulla da temere. Addio.";
			link.l1.go = "exit";
			NextDiag.TempNode = "FriendCap_exit";
			npchar.DeckDialogNode = "FriendCap_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony"+npchar.quest.cribCity+"Acc"));
			sTemp = "SecondTimer_" + npchar.id;
			pchar.quest.(sTemp).over = "yes"; //снимаем установленный таймер на выход в море
			npchar.lifeDay = 0;
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть кэпа
			sld = characterFromId("QuestCitiz_" + npchar.quest.cribCity);
			sld.quest.SeekCap = sld.quest.SeekCap + "over"; //дополняем флаг квест до 'выполнен'
			//удаляем запись в базе кэпов
			makearef(forName, NullCharacter.capitainBase);
			DeleteAttribute(forName, npchar.id);
		break;
		case "FriendCap_exit":
			dialog.text = "C'è qualche problema? Perdona la mia agitazione, sono un po’ nervoso...";
			link.l1 = "Tutto a posto, compare.";
			link.l1.go = "exit";
			NextDiag.TempNode = "FriendCap_exit";
		break;
		case "FriendCap_inDeck": //встреча на палубе
			dialog.text = TimeGreeting()+"Che volete da me? Sono solo un semplice mercante e...";
			link.l1 = "Lo so, compare. Non ti crucciare tanto, dicono che fa male alla salute. Ho un affare da discutere con te.";
			link.l1.go = "FriendCap_inDeck_1";
		break;
		case "FriendCap_inDeck_1":
			dialog.text = "Che razza d'affare sarebbe?";
			link.l1 = "Un tuo compare ti cerca. Si fa chiamare "+GetFullName(&characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)])+". Lo conosci, per caso?";
			link.l1.go = "FriendCap_inDeck_2";
		break;
		case "FriendCap_inDeck_2":
			dialog.text = "Oh, finalmente! Che sollievo... Perdona il mio benvenuto così brusco, ma pensavo fossi un filibustiere.";
			link.l1 = "Lo sono. In un certo senso. O forse no. Ma comunque, oggi sono di buon umore, quindi non hai nulla di cui preoccuparti. Mi hanno chiesto di portarti un messaggio e il mio compito è fatto. Il tuo compare abita a "+XI_ConvertString("Colony"+npchar.quest.cribCity+"Voc")+"."; // belamour gen
			link.l1.go = "FriendCap_inDeck_3";
		break;
		case "FriendCap_inDeck_3":
			dialog.text = "Ma guarda un po'! Sei davvero un uomo d'onore. Ti ringrazio!";
			link.l1 = "Sei il benvenuto. Addio e stai in guardia, compare.";
			link.l1.go = "exit";
			NextDiag.TempNode = "FriendCap_exit";
			npchar.DeckDialogNode = "FriendCap_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony"+npchar.quest.cribCity+"Acc"));
			npchar.quest = "outMap"; //доходит до нужной точки - и исчезает
			sld = characterFromId("QuestCitiz_" + npchar.quest.cribCity);
			sld.quest.SeekCap = sld.quest.SeekCap + "over"; //дополняем флаг квест до 'выполнен'
			//удаляем запись в базе кэпов
			makearef(forName, NullCharacter.capitainBase);
			DeleteAttribute(forName, npchar.id);
		break;
		//========= разыскиваемый муж-торговец ===========
		case "HasbandCap": //встреча на суше
			dialog.text = "Ciao. Cerchi qualcosa?";
			link.l1 = "Il tuo nome è "+GetFullName(npchar)+", ho ragione?";
			link.l1.go = "HasbandCap_1";
		break;
		case "HasbandCap_1":
			dialog.text = "Sì, sono proprio io.";
			link.l1 = "Potrà sembrarvi una sciocchezza, ma vostra moglie mi ha pregato di dirvi che si cruccia per voi.";
			link.l1.go = "HasbandCap_2";
		break;
		case "HasbandCap_2":
			dialog.text = "Ah! Capisco... In verità, ero troppo preso dagli affari, le occasioni di guadagno qui non mancano e non posso mica perdere monete solo perché mia moglie si fa troppi crucci.";
			link.l1 = "Ma potresti almeno scriverle una lettera e dirle che stai bene.";
			link.l1.go = "HasbandCap_3";
		break;
		case "HasbandCap_3":
			dialog.text = "Hai ragione, lo farò subito! Grazie per esserti impicciato dei nostri affari di famiglia!";
			link.l1 = "Benvenuto, compare.";
			link.l1.go = "exit";
			NextDiag.TempNode = "HasbandCap_inDeck_exit";
			npchar.DeckDialogNode = "HasbandCap_inDeck_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			sTemp = "SecondTimer_" + npchar.id;
			pchar.quest.(sTemp).over = "yes"; //снимаем установленный таймер на выход в море
			npchar.lifeDay = 0;
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть кэпа
			sld = characterFromId("QuestCitiz_" + npchar.quest.cribCity);
			sld.quest.SeekCap = sld.quest.SeekCap + "over"; //дополняем флаг квест до 'выполнен'
			//удаляем запись в базе кэпов
			makearef(forName, NullCharacter.capitainBase);
			DeleteAttribute(forName, npchar.id);
		break;
		case "HasbandCap_inDeck": //встреча на палубе
			dialog.text = "Buon dì a voi. Come posso esservi utile?";
			link.l1 = "Il tuo nome è "+GetFullName(npchar)+", ho ragione?";
			link.l1.go = "HasbandCap_inDeck_1";
		break;
		case "HasbandCap_inDeck_1":
			dialog.text = "Sì, sono proprio io.";
			link.l1 = "Potrà sembrarvi una sciocchezza, ma vostra moglie mi ha pregato di dirvi che si preoccupa per voi.";
			link.l1.go = "HasbandCap_inDeck_2";
		break;
		case "HasbandCap_inDeck_2":
			dialog.text = "Uff, maledizione! Ho temuto che fosse quel famoso cacciatore di taglie venuto per me, si chiama Steve l’Occhio Solo. Beh, meno male che mi sono sbagliato\nVedi, sono così preso dal mio lavoro che non riesco a trovare un attimo per lei. Continuano ad arrivare offerte che rendono bene e non posso rifiutarle solo perché mia moglie si preoccupa.";			
			link.l1 = "Hai ragione, certo. Ma potresti almeno scriverle una lettera per dirle che stai bene.";
			link.l1.go = "HasbandCap_inDeck_3";
		break;
		case "HasbandCap_inDeck_3":
			dialog.text = "Sì, hai ragione. Lo farò appena metto piede nel primo porto... Grazie per esserti immischiato nei nostri affari di famiglia!";
			link.l1 = "Sei il benvenuto, compare.";
			link.l1.go = "exit";
			NextDiag.TempNode = "HasbandCap_inDeck_exit";
			npchar.DeckDialogNode = "HasbandCap_inDeck_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			npchar.quest = "outMap"; //доходит до нужной точки - и исчезает
			sld = characterFromId("QuestCitiz_" + npchar.quest.cribCity);
			sld.quest.SeekCap = sld.quest.SeekCap + "over"; //дополняем флаг квест до 'выполнен'
			//удаляем запись в базе кэпов
			makearef(forName, NullCharacter.capitainBase);
			DeleteAttribute(forName, npchar.id);
		break;
		case "HasbandCap_inDeck_exit":
			dialog.text = "Hai la mia gratitudine, capitano...";
			link.l1 = "Sei il benvenuto.";
			link.l1.go = "exit";
			NextDiag.TempNode = "HasbandCap_inDeck_exit";
		break;
		//========= разыскиваемый капитан-обманщик ===========
		case "RevengeCap": //встреча на суше
			dialog.text = "Felice di vederti in questa città, capitano. Hai bisogno di qualcosa da me?";
			link.l1 = ""+GetSexPhrase("Sai, capitano... Bah, non so nemmeno come dirlo!","Sì, l’ho fatto.")+"";
			link.l1.go = "RevengeCap_1";
		break;
		case "RevengeCap_1":
			dialog.text = ""+GetSexPhrase("Dì le cose come stanno.","Interessante, e di cosa si tratta?")+"";
			link.l1 = " Ho una domanda per te. Conosci una donna di nome "+GetFullName(&characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)])+"?";
			link.l1.go = "RevengeCap_2";
		break;
		case "RevengeCap_2":
			dialog.text = "Heh, sì che la conosco. Son stato sfortunato ad averci a che fare. Una ragazza sciocca, te lo dico io...";
			link.l1 = "Hm... Sì, e questa sciocca ragazza mi ha chiesto di farti fuori. Tutto qui....";
			link.l1.go = "RevengeCap_3";
		break;
		case "RevengeCap_3":
			dialog.text = "Bagianate.";
			link.l1 = ""+GetSexPhrase("Sono d'accordo. Perdona l'ardire, ma c'è una taglia sulla tua testa","Non è così. C’è una taglia.")+". E io ho intenzione di prenderlo.";
			link.l1.go = "RevengeCap_4";
		break;
		case "RevengeCap_4":
			dialog.text = "Ho-ho!... Mi prendi per fesso, capitano?";
			link.l1 = ""+GetSexPhrase("No, amico.","Non ci pensavo nemmeno!")+"";
			link.l1.go = "RevengeCap_5";
		break;
		case "RevengeCap_5":
			dialog.text = ""+GetSexPhrase("Tu non sei mio amico, idiota! Non puoi nemmeno definirti capitano. Sei solo il burattino di questa furia da strapazzo!","Maledizione! Una furia ne ha ingaggiata un’altra! Che diavolo sta succedendo a questo mondo?")+"!";
			link.l1 = ""+GetSexPhrase("Attento a come parli, feccia.","L’hai sfruttata, dunque non ti meravigliare se ha scelto di vendicarsi.")+"";
			link.l1.go = "RevengeCap_6";
		break;
		case "RevengeCap_6":
			dialog.text = ""+GetSexPhrase("Ti ho punto sul vivo?","Solidarietà femminile?!")+"";
			link.l1 = "Mettiamo fine a questa faccenda!";
			link.l1.go = "RevengeCap_7";
		break;
		case "RevengeCap_7":
			NextDiag.TempNode = "RevengeCapCap_exit";
			npchar.DeckDialogNode = "RevengeCapCap_exit";
			npchar.quest.SeekCap = "womanRevengeFight"; //флаг квеста для зачета в прерывании на убийство
			LAi_group_Attack(NPChar, Pchar);
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		case "RevengeCapCap_exit":
			dialog.text = "Ti ho già parlato. Sparisci, idiota!";
			link.l1 = "Imbecille?! Va bene allora...";
			link.l1.go = "exit";
			NextDiag.TempNode = "RevengeCapCap_exit";
		break;
		case "RevengeCap_inDeck": //встреча на палубе
			dialog.text = "Felice di vederti a bordo, capitano. Che vuoi?";
			link.l1 = "Ho una domanda per te. Conosci una donna di nome "+GetFullName(&characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)])+"?";
			link.l1.go = "RevengeCap_inDeck_1";
		break;
		case "RevengeCap_inDeck_1":
			dialog.text = "Eheh, eccome se la conosco. Una sfortuna averci a che fare. Una ragazzina sciocca, te lo dico io...";
			link.l1 = "Sì, e questa sciocca ragazza mi ha chiesto di toglierti la vita.";
			link.l1.go = "RevengeCap_inDeck_2";
		break;
		case "RevengeCap_inDeck_2":
			dialog.text = "Capitano, non farmi ridere. Se non hai faccende serie con me, allora ti dico addio.";
			link.l1 = "Addio, allora. Ma pensa bene a ciò che t'ho detto.";
			link.l1.go = "RevengeCap_inDeck_3";
		break;
		case "RevengeCap_inDeck_3":
			dialog.text = "Certo, capitano, come potrebbe essere altrimenti?!";
			link.l1 = "Addio.";
			link.l1.go = "exit";
			NextDiag.TempNode = "RevengeCapCap_inDeck_exit";
			npchar.DeckDialogNode = "RevengeCapCap_inDeck_exit";
			npchar.quest.SeekCap = "womanRevengeFight"; //флаг квеста для зачета в прерывании на убийство
		break;
		case "RevengeCapCap_inDeck_exit":
			dialog.text = "Non voglio più parlarne, capitano. Questa faccenda è troppo assurda.";
			link.l1 = "Come desideri...";
			link.l1.go = "exit";
			NextDiag.TempNode = "RevengeCapCap_exit";
		break;
		case "RevengeCap_board": //абордаж
			dialog.text = "Che diavolo sta succedendo qui?! Perché avete assaltato la mia nave?";
			link.l1 = "Su richiesta della dama chiamata "+GetFullName(&characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)])+". La conosci?";
			link.l1.go = "RevengeCap_board_1";
		break;
		case "RevengeCap_board_1":
			dialog.text = "Diavolo!!! Non ci posso credere...";
			link.l1 = "Devi farlo! Non conosci le donne, compare? Sanno essere delle vere vipere.";
			link.l1.go = "RevengeCap_board_2";
		break;
		case "RevengeCap_board_2":
			dialog.text = "Ebbene, non ho intenzione di crepare così, senza combattere. Grazie per le chiacchiere, ora ho ripreso un po' di forze.";
			link.l1 = "Non ti servirà a nulla.";
			link.l1.go = "RevengeCap_board_3";
		break;
		case "RevengeCap_board_3":
			LAi_SetCurHPMax(npchar);
			//==> флаг квеста сменим у оригинального кэпа
			characters[sti(npchar.baseCapIdx)].quest.SeekCap = "womanRevengeFight"; 
			QuestAboardCabinDialogFree(); // важный метод
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		//========= вызволение мужа из пиратских затрюмков =========
		case "PiratesCap_inDeck": //встреча на палубе
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			dialog.text = "Felice di vederti a bordo. Posso esserti d’aiuto?";
			link.l1 = "Puoi farlo. Sto cercando un uomo di nome "+sld.quest.SeekCap.name+" "+sld.quest.SeekCap.lastname+".";
			link.l1.go = "PiratesCap_1";
		break;
		case "PiratesCap_inDeck_1":
			dialog.text = "Quest'uomo è il mio prigioniero e ho intenzione di chiedere un riscatto per lui.";
			link.l1 = "Voglio portarlo con me.";
			link.l1.go = "PiratesCap_inDeck_2";
		break;
		case "PiratesCap_inDeck_2":
			dialog.text = "Purtroppo, ciò è impossibile. Se non hai altro da dire, ti pregherei di lasciare la mia nave.";
			link.l1 = "D'accordo, capitano, come volete.";
			link.l1.go = "exit";
			NextDiag.TempNode = "PiratesCapCap_exit";
			npchar.DeckDialogNode = "PiratesCapCap_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName))); // belamour gen
		break;
		case "PiratesCapCap_exit":
			dialog.text = "Abbiamo già discusso del mio prigioniero. Nulla è cambiato.";
			link.l1 = "Capisco...";
			link.l1.go = "exit";
		break;
		case "PiratesCap": //встреча на суше
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			dialog.text = "Un piacere fare la vostra conoscenza. Posso esservi d’aiuto?";
			link.l1 = "Puoi farlo. Sto cercando un uomo di nome "+sld.quest.SeekCap.name+" "+sld.quest.SeekCap.lastname+".";
			link.l1.go = "PiratesCap_1";
		break;
		case "PiratesCap_1":
			dialog.text = "Quest'uomo è il mio prigioniero e ho intenzione di chiedere un riscatto per lui.";
			link.l1 = "Voglio portarlo con me.";
			link.l1.go = "PiratesCap_2";
		break;
		case "PiratesCap_2":
			dialog.text = "Mi dispiace, ma non è possibile.";
			link.l1 = "Peccato...";
			link.l1.go = "exit";
			NextDiag.TempNode = "PiratesCapCap_exit";
			npchar.DeckDialogNode = "PiratesCapCap_exit";
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "5");
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(npchar.Ship.Type)].BaseName))); // belamour gen
		break;
		case "PiratesCap_Board": //абордаж
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			dialog.text = "Maledizione! Che diavolo?!";
			link.l1 = "Ho bisogno del tuo prigioniero di nome "+sld.quest.SeekCap.name+" "+sld.quest.SeekCap.lastname+".";
			link.l1.go = "PiratesCap_Board_1";
		break;
		case "PiratesCap_Board_1":
			dialog.text = "Ah! Neanche per sogno, solo sul mio cadavere!";
			link.l1 = "Visto che me lo chiedi...";
			link.l1.go = "PiratesCap_Board_2";
		break;
		case "PiratesCap_Board_2":
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogFree(); // важный метод
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "CitizSeekCap_afterCabinFight");
			pchar.GenQuest.CitizSeekCap.label = npchar.quest.SeekCap; //флаг квеста для нпс
			pchar.GenQuest.CitizSeekCap.nation = npchar.nation;	//нацию для нпс
			pchar.GenQuest.CitizSeekCap.model = "citiz_"+(rand(9)+11); //модель для нпс
			pchar.GenQuest.CitizSeekCap.sex = "man";
			pchar.GenQuest.CitizSeekCap.ani = "man";
			pchar.GenQuest.CitizSeekCap.WifeCity = npchar.quest.cribCity; //исходный город для нпс
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			pchar.GenQuest.CitizSeekCap.WifeName = sld.quest.SeekCap.name; //имя и фамилию для нпс
			pchar.GenQuest.CitizSeekCap.WifeLastname = sld.quest.SeekCap.lastname;
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		//========= пленный муж ===========
		case "womanPirates_Board":
			dialog.text = "Chi sei, tu?";
			link.l1 = "Sono il capitano "+GetFullName(pchar)+"Non temere, son qui per ricondurti alla tua consorte.";
			link.l1.go = "womanPirates_Board_1";
		break;
		case "womanPirates_Board_1":
			dialog.text = "Maledizione, devo star sognando!";
			link.l1 = "Posso assicurarti che non è così... Beh, ormai è finita, andiamo via da qui.";
			link.l1.go = "exit";
			//уберем мужа из каюты
			npchar.location = "none";
			npchar.location.locator = "";
			LAi_SetPlayerType(pchar);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			sld = &characters[GetCharacterIndex("QuestCitiz_"+npchar.quest.cribCity)];
			sld.quest.SeekCap = sld.quest.SeekCap + "over"; //дополняем флаг квест до 'выполнен'
			sTitle = npchar.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "6");
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony"+npchar.quest.cribCity+"Acc"));
		break;
		
		case "plantation_slave":
			if (CheckAttribute(npchar, "CityType") && npchar.CityType == "citizen" && findsubstr(npchar.id, "Slave_" , 0) != -1)
    		{
				dialog.text = RandPhraseSimple(RandPhraseSimple("Sono sfinito, aiutami.","Non ho più la forza di vivere così!"),RandPhraseSimple("Questo lavoro ci sta divorando vivi.","Maledetti sbirri, mi hanno spellato la schiena viva!"));				
				link.l1 = RandPhraseSimple("Che peccato.","Sì, la vita è una carogna.");
				link.l1.go = "exit";				
    		} 
		break;
		
		//=====================================================================================================================================
		// Warship, 25.05.11. && Jason 10.02.12 Серия миниквестов "Дело чести" -->
		//=====================================================================================================================================
		case "AffairOfHonor_1":
			LAi_CharacterDisableDialog(NPChar);
			
			if(LoadedLocation.type == "tavern")
			{
				// "Честь мундира".
				if(!CheckAttribute(PChar, "QuestTemp.AffairOfHonor.CoatHonor"))
				{
					dialog.text = "Oh, capitano, siediti qui con me. Offro io!";
					link.l1 = "Con gran piacere.";
					link.l1.go = "AffairOfHonor_CoatHonor_1";
					PChar.QuestTemp.AffairOfHonor.CoatHonor = true;
					break;
				}
			}
			else
			{
				if(NPChar.sex == "man")
				{
					// "Невольник чести".
					if(!CheckAttribute(PChar, "QuestTemp.AffairOfHonor.HonorSlave"))
					{
						dialog.text = "Salve, capitano. Siete un capitano, vero? Forse persino della marina?\nGià, dovete avere una buona mano con la spada, a differenza di mio figlio buono a nulla che domani farà una brutta fine... E tutto per colpa di quel bastardo lussurioso che ha posato gli occhi sulla dama che interessa a mio figlio!";
						link.l1 = "Sì, sono un capitano, e la mia spada m’ha già salvato più volte, ma che dire del resto del tuo discorso da menagramo? Vuoi spiegarti meglio?";
						link.l1.go = "AffairOfHonor_HonorSlave_1";
						PChar.QuestTemp.AffairOfHonor.HonorSlave = true;
						break;
					}
					
					// "Красотка и пират".
					if(!CheckAttribute(PChar, "QuestTemp.AffairOfHonor.BeautifulPirate"))
					{
						dialog.text = "Saluti, capitano. Posso chiedere, non sarai mica un pirata per caso? Oh, certo che no! Non lo sei. I pirati hanno un aspetto losco, si comportano come bestie e quell’odore nauseabondo...";
						link.l1 = "Hai del rancore verso i pirati?";
						link.l1.go = "AffairOfHonor_BeautifulPirate_1";
						PChar.QuestTemp.AffairOfHonor.BeautifulPirate = true;
						break;
					}
					
					// "Заносчивый нахал".
					if(!CheckAttribute(PChar, "QuestTemp.AffairOfHonor.Jackanapes"))
					{
						//if(NPChar.city == "PortRoyal" || NPChar.city == "Havana" || NPChar.city == "Villemstad" || NPChar.city == "FortFrance")
						//{
						// Jason: что за чудное условие? Типа - столица? Кроме Гаваны, квест более нигде не выпадет - остальные города непригодны априори. Убираю. Неразумно ограничивать одним городом.
							dialog.text = "Ehi, tu! Sì, proprio tu, dimmi, dove sono finite le tue buone maniere? Maledizione, perché diavolo stai qui impalato a rompermi le scatole? Guarda un po’, che idiota! Sto parlando con te! Levati di mezzo! Troppa feccia forestiera qui!";
							link.l1 = "Calmati, non volevo disturbarti. Perdona la mia sfacciataggine.";
							link.l1.go = "AffairOfHonor_Exit";
							link.l2 = "Frena la lingua, o te la taglio, buon uomo.";
							link.l2.go = "AffairOfHonor_Jackanapes_1";
							PChar.QuestTemp.AffairOfHonor.Jackanapes = true;
							break;
						//}
					}
					
					// "Волки и овцы".
					if(!CheckAttribute(PChar, "QuestTemp.AffairOfHonor.WolvesAndSheeps"))
					{
						dialog.text = "Saluti, capitano. Ho da chiederti un favore. Se hai un briciolo d’onore, non ti tirerai indietro.\nBando alle ciance: un nobilastro ha alloggiato nella nostra taverna un mese fa. Si è rivelato uno scellerato e un maledetto furfante! E, peggio ancora, è pure un assassino!";
						link.l1 = "Per quel che ricordo, l’impiccagione aspetta chi ammazza un innocente. Essere un libertino e un bastardo non ti farà guadagnare grazia davanti al giudice, vero?";
						link.l1.go = "AffairOfHonor_WolvesAndSheeps_1";
						PChar.QuestTemp.AffairOfHonor.WolvesAndSheeps = true;
						break;
					}
					                                                                                                                                                
					// "Трусливый фехтовалщик".
					if(!CheckAttribute(PChar, "QuestTemp.AffairOfHonor.CowardFencer"))
					{
						dialog.text = "Capitano, aspetta, te ne supplico. Sembri un maestro di spada, ben più abile di me. Vorrei chiederti di prendere il mio posto.";
						link.l1 = "Interessante. Continua.";
						link.l1.go = "AffairOfHonor_CowardFencer_1";
						PChar.QuestTemp.AffairOfHonor.CowardFencer = true;
						break;
					}
					
					// "Божий суд".
					if(!CheckAttribute(PChar, "QuestTemp.AffairOfHonor.GodJudgement"))
					{
						dialog.text = "Ti prego, ti scongiuro, non andartene! Aspetta... Non potresti aiutare una povera anima in una faccenda che richiede l’intervento d’un così valoroso ufficiale come te?\nLa faccenda è questa: ho avuto una lite riguardo le vigne locali col mio vicino, che tra l’altro è sospettato di traffici con contrabbandieri. Sì, sì, e forse pure d’intese con pirati, come potrebbe altrimenti aver messo insieme una fortuna in così poco tempo?\nUn anno fa aveva solo una barchetta e ora vuol prendersi le mie vigne, mi senti?! Le MIE vigne!";
						link.l1 = "Mi dispiace davvero per le tue vigne. Davvero. Addio.";
						link.l1.go = "exit";
						link.l2 = "Chiedo venia, ma non potresti rivolgerti alle autorità locali?";
						link.l2.go = "AffairOfHonor_GodJudgement_1";
						PChar.QuestTemp.AffairOfHonor.GodJudgement = true;
						break;
					}
				}
				else
				{
					// "Навязчивый кавалер".
					if(!CheckAttribute(PChar, "QuestTemp.AffairOfHonor.Cavalier"))
					{
						dialog.text = "Capitano, capitano, vi scongiuro! Difendete l’onore d’una fanciulla innocente!";
						link.l1 = "Non ho tempo per queste bagattelle, bella mia. Cerca qualcun altro...";
						link.l1.go = "AffairOfHonor_Exit";
						link.l2 = "Salute, mia signora. Non tremate così! Che vi è accaduto?";
						link.l2.go = "AffairOfHonor_Cavalier_1";
						PChar.QuestTemp.AffairOfHonor.Cavalier = true;
						break;
					}
				}
			}
			
			dialog.text = "Errore. Avvisa i maledetti sviluppatori.";
			link.l1 = RandSwear();
			link.l1.go = "exit";
		break;
		
		case "AffairOfHonor_Exit":
			ChangeCharacterComplexReputation(PChar, "nobility", -2);
			NextDiag.CurrentNode = "First time";
			DialogExit();
		break;
		
		case "AffairOfHonor_Cavalier_1":
			dialog.text = "Capitano, sono stato pedinato in modo più che palese da un ufficiale della nostra guarnigione. Avreste dovuto sentire le luride chiacchiere che va spargendo sul mio conto, cercando di gettarmi nel fango!\nAhimè, non ho amici in grado di difendere il mio buon nome! Sono disperata! Oh Dio, eccolo! Aiutatemi!";
			link.l1 = "Non temere, porterò tutto a termine.";
			link.l1.go = "exit";
			int Rank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+12;
			int Scl = 30+2*sti(pchar.rank);
			sld = GetCharacter(NPC_GenerateCharacter("AffairOfHonor_Cavalier_Man", GetRandQuestSoldierModel(sti(NPChar.nation)), "man", "man", Rank, sti(NPChar.nation), -1, true, "soldier"));
			// Jason: дохляки нам не нужны - делаем кулфайтера
			FantomMakeCoolFighter(sld, Rank, Scl, Scl, RandPhraseSimple("blade_12","blade_14"), RandPhraseSimple("pistol6","pistol5"), "bullet", Scl*3);
			float Mft = MOD_SKILL_ENEMY_RATE/20;
			sld.MultiFighter = 1.0+Mft; // мультифайтер
			ChangeCharacterAddressGroup(sld, PChar.location, "goto", FindNearestFreeLocator("goto"));
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, PChar, "", -1, 5);
			LAi_SetImmortal(sld, true); // Еще успеем.
			sld.dialog.filename = "Quest\ForAll_dialog.c";
			sld.dialog.currentnode = "AffairOfHonor_Cavalier_2";
			PChar.QuestTemp.AffairOfHonor.Cavalier.Started = true;
			DisableAllExits(true);
		break;
		
		case "AffairOfHonor_Cavalier_2":
			dialog.text = "Ah, eccoti qua, mia signora! Un altro cavaliere, eh? Quando mai ti sistemerai? Forse mai... Vai a lavorare al bordello, è il posto più adatto a te...";
			link.l1 = "Ufficiale, chiudi quella bocca prima che vomiti altre offese, o ti farò tacere a modo mio!";
			link.l1.go = "AffairOfHonor_Cavalier_2a";
		break;
		
		case "AffairOfHonor_Cavalier_2a":
			dialog.text = "Hm... Chi sei tu? Ah-ah, temprato dal sale del mare, il coraggioso capitano di una barchetta, ho ragione? E dimmi, che vuoi fare, cucciolo di mare?";
			link.l1 = "Questa dama è mia amica! E ti lancerò il guanto di sfida, mascalzone!";
			link.l1.go = "AffairOfHonor_Cavalier_3";
		break;
		
		case "AffairOfHonor_Cavalier_3":
			dialog.text = "Cosa?! Non vorrai sfidarmi per questa bagatella...";
			link.l1 = "Basta! Ti aspetterò vicino al faro tra due ore. E non dimenticare di portare la tua spada!";
			link.l1.go = "AffairOfHonor_Cavalier_4";
		break;
		
		case "AffairOfHonor_Cavalier_4":
			DialogExit();
			DeleteAttribute(npchar, "LifeDay");
			DisableAllExits(false);
			LAi_ActorGoToLocation(NPChar, "reload", FindNearestFreeLocator("reload"), "none", "", "", "", 3.0);
			Locations[FindLocation(PChar.QuestTemp.AffairOfHonor.LighthouseId)].DisableEncounters = true;
			LAi_LocationDisableOfficersGen(PChar.QuestTemp.AffairOfHonor.LighthouseId, true);
			SetFunctionTimerConditionParam("AffairOfHonor_TimeIsLeft", 0, 0, 0, GetHour() + 3, false);
			// Jason: отсрочка на 2 часа как договаривались
			SetFunctionTimerConditionParam("AffairOfHonor_LighthouseGotoMeeting", 0, 0, 0, GetHour()+2, false);
			ReOpenQuestHeader("AffairOfHonor");
			AddQuestRecord("AffairOfHonor", "1");
		break;
		
		case "AffairOfHonor_Cavalier_5":
			dialog.text = "Ah, so tutto, signore! Non potete immaginare quanto vi sia riconoscente! Che il Signore vi protegga!";
			link.l1 = "Sono lieto d’aver potuto aiutarti. Buona fortuna!";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(PChar, "nobility", 7);
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 2);
			ChangeOfficersLoyality("good_all", 1);
			AddComplexSelfExpToScill(50, 50, 50, 50);
			AddCharacterExpToSkill(pchar, "Leadership", 300);
			AddCharacterExpToSkill(pchar, "Fortune", 100);
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(NPChar);
		break;
		
		case "AffairOfHonor_Cavalier_6":
			dialog.text = "Ah, siete tutti uguali, lasciatemi in pace!";
			link.l1 = "...";
			link.l1.go = "exit";
			LAi_CharacterDisableDialog(NPChar);
		break;
		
		case "AffairOfHonor_HonorSlave_1":
			sTemp = "";
			if (FindLocation(NPChar.city + "_brothel") != -1) sTemp = "or in the brothel ";
			dialog.text = "Oh, "+GetAddress_Form(NPChar)+"... Non oso sperare, ma forse la tua spada potrebbe proteggere la mia famiglia questa volta?\nCome ti ho detto, mio figlio non è un duellante, ma domani mattina dovrà battersi. Ah, se non fosse per quella sua dama e il maledetto onore...\nMa non ha potuto tirarsi indietro e ora è condannato, non lo vedi? Sono disperato, è il mio unico figlio e il mio erede, perciò ti chiedo di far fuori il bastardo che ha sfidato il mio ragazzo prima che sorga il sole. Ti ricompenserò a dovere, su questo puoi contarci!\nTroverai quell’uomo nella taverna "+sTemp+" - là, dove canaglie come lui passano il loro tempo libero... Ti supplico...";
			link.l1 = "Non me ne frega un accidente né di te né di tuo figlio. Lasciami andare!";
			link.l1.go = "exit";
			link.l2 = "Hm ... Così, senza tante storie? Bene, vedremo come va a finire.";
			link.l2.go = "AffairOfHonor_HonorSlave_1a";
		break;
		
		case "AffairOfHonor_HonorSlave_1a":
			dialog.text = "Mi aiuterai davvero con mio figlio? Oh, "+GetAddress_Form(NPChar)+"! Pregherò per te e per la tua fortuna!";
			link.l1 = "Non ci vedo nulla di male... Aspettami!";
			link.l1.go = "AffairOfHonor_HonorSlave_2";
		break;
		
		case "AffairOfHonor_HonorSlave_2":
			DialogExit();
			Rank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+8;
			Scl = 30+2*sti(pchar.rank);
			sld = GetCharacter(NPC_GenerateCharacter("AffairOfHonor_HonorSlave_Man", "citiz_" + (rand(9) + 41), "man", "man", Rank, sti(NPChar.nation), -1, true, "soldier"));
			// Jason: дохляки нам не нужны - делаем кулфайтера
			FantomMakeCoolFighter(sld, Rank, Scl, Scl, RandPhraseSimple("blade_04","blade_06"), RandPhraseSimple("pistol1","pistol5"), "bullet", Scl*3);
			Mft = MOD_SKILL_ENEMY_RATE/20;
			sld.MultiFighter = 1.0+Mft; // мультифайтер
			if(rand(1) == 0 || FindLocation(NPChar.city + "_brothel") == -1 || CheckAttribute(pchar, "questTemp.Mtraxx.AffairOfHonor"))
			{
				FreeSitLocator(NPChar.city + "_tavern", "sit_front1");
				ChangeCharacterAddressGroup(sld, NPChar.city + "_tavern", "sit", "sit_front1");
				LAi_SetSitType(sld);
			}
			else
			{
				ChangeCharacterAddressGroup(sld, NPChar.city + "_brothel", "goto", "goto3");
				LAi_SetCitizenType(sld);
			}
			LAi_SetImmortal(sld, true); // Еще успеем.
			sld.dialog.filename = "Quest\ForAll_dialog.c";
			sld.dialog.currentnode = "AffairOfHonor_HonorSlave_3";
			SetFunctionTimerCondition("AffairOfHonor_TimeIsLeft", 0, 0, 1, false);
			PChar.QuestTemp.AffairOfHonor.HonorSlave.Started = true;
			ReOpenQuestHeader("AffairOfHonor");
			AddQuestRecord("AffairOfHonor", "3");
		break;
		
		case "AffairOfHonor_HonorSlave_3":
			dialog.text = "Che diavolo vuoi da me? Mi sto riposando qui e non ho voglia d’esser seccato. Ci sono un mucchio di sedie libere e orecchie da riempire, dunque lasciami in pace, signore!";
			link.l1 = "Sfortunatamente, dovrai sospendere il tuo riposo fino a tempi migliori.";
			link.l1.go = "AffairOfHonor_HonorSlave_3a";
		break;
		
		case "AffairOfHonor_HonorSlave_3a":
			dialog.text = "Cosa?! E chi diavolo sei tu per dirmi cosa devo fare?!";
			link.l1 = "Mi hai già dimenticato, eh? Ma io mi ricordo di te! E la verità è che canaglie come te avvelenano il nostro mondo solo con la loro lurida presenza!";
			link.l1.go = "AffairOfHonor_HonorSlave_3b";
		break;
		
		case "AffairOfHonor_HonorSlave_3b":
			dialog.text = "Eh?! Marinaio, mi sa che hai tracannato troppo rum! È la prima volta che ti vedo! Ma non intendo passar sopra ai tuoi modi! Questa è l’ultima occasione che hai per salvare la pellaccia! Chiedi scusa subito, pesce marcio gonfio, e mi scorderò della tua insolenza!";
			link.l1 = "Mi scuso solo con uomini d’onore, non con porci luridi!";
			link.l1.go = "AffairOfHonor_HonorSlave_4";
		break;
		
		case "AffairOfHonor_HonorSlave_4":
			dialog.text = "Che diavolo?! Cerchi rogne, lurido scarafaggio di latrina?";
			link.l1 = "Ti stapperò la fottuta gola con le tue stesse parole, ratto! Ti aspetto vicino al faro fra due ore, e non scordarti di portare quella ferraglia arrugginita che ti penzola alla cintura!";
			link.l1.go = "AffairOfHonor_HonorSlave_5";
		break;
		
		case "AffairOfHonor_HonorSlave_5":
			dialog.text = "Ah! Ci sarò, dannazione!";
			link.l1 = "A presto, compare!";
			link.l1.go = "AffairOfHonor_HonorSlave_6";
		break;
		
		case "AffairOfHonor_HonorSlave_6":
			DialogExit();
			LAi_CharacterDisableDialog(NPChar);
			Locations[FindLocation(PChar.QuestTemp.AffairOfHonor.LighthouseId)].DisableEncounters = true;
			LAi_LocationDisableOfficersGen(PChar.QuestTemp.AffairOfHonor.LighthouseId, true);
			// Jason: отсрочка на 2 часа как договаривались
			SetFunctionTimerConditionParam("AffairOfHonor_LighthouseGotoMeeting", 0, 0, 0, GetHour()+2, false);
			AddQuestRecord("AffairOfHonor", "3_1");
		break;
		
		case "AffairOfHonor_HonorSlave_7":
			dialog.text = "Oh, sei tu! Sei ancora tra i vivi, il che vuol dire che...";
			link.l1 = "Sì, lo sono, e tuo figlio non dovrà battersi in duello domattina...";
			link.l1.go = "AffairOfHonor_HonorSlave_8";
		break;
		
		case "AffairOfHonor_HonorSlave_8":
			dialog.text = "Che giornata splendida! Devo correre a raccontare le buone novelle a mia moglie! \nCapitano, il destino stesso vi ha mandato ad aiutarmi. Prendete queste monete e accettate la gratitudine della nostra famiglia!";
			link.l1 = "Grazie di cuore!";
			link.l1.go = "exit";
			iTemp = 50+hrand(5)*10;
			TakeNItems(pchar, "gold_dublon", iTemp);
			Log_Info("You have received "+FindRussianDublonString(iTemp)+"");
			PlaySound("interface\important_item.wav");
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 2);
			AddComplexSelfExpToScill(50, 50, 50, 50);
			AddCharacterExpToSkill(pchar, "Leadership", 200);
			AddCharacterExpToSkill(pchar, "Fortune", 50);
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(NPChar);
		break;
		
		case "AffairOfHonor_HonorSlave_9":
			dialog.text = "Vattene, assassino di marmocchi!";
			link.l1 = "...";
			link.l1.go = "exit";
			LAi_CharacterDisableDialog(NPChar);
		break;
		
		case "AffairOfHonor_BeautifulPirate_1":
			dialog.text = "Io? Grazie al cielo, sto bene, ma mia sorella non ha avuto la stessa fortuna. Lavora in una taverna... Lì si presenta spesso un corsaro, di quelli pericolosi. Un vero filibustiere! La sua nave non ha visto porto da almeno una settimana. Beve come una spugna, minaccia la gente e giura di far fuori chiunque osi contraddirlo. Il peggio è che mia sorella mi ha detto che si vanta di portarla via con sé, chissà dove, se non accontenta i suoi luridi capricci!\nNon so davvero che fare! Le autorità se ne fregano di una povera serva come lei e la brava gente come me ha il terrore di quel mascalzone. Aiutaci a sbarazzarcene, ti prego!";
			link.l1 = "Non ho tempo per calmare gli ubriachi nelle taverne. Parla col comandante, lo pagano proprio per risolvere queste faccende.";
			link.l1.go = "exit";
			link.l2 = "Mm, un corsaro minaccioso? Va bene, ci penserò io.";
			link.l2.go = "AffairOfHonor_BeautifulPirate_1a";
		break;
		
		case "AffairOfHonor_BeautifulPirate_1a":
			dialog.text = "Ah, grazie, capitano! Son sicuro che ti darà retta, come un marinaio ascolta un altro marinaio! Fallo smettere di importunare mia sorella per sempre! Non siamo ricchi, ma ti pagheremo quanto basta per il disturbo!";
			link.l1 = "Va bene, va bene... Sto andando a risolvere i tuoi guai. Aspettami!";
			link.l1.go = "AffairOfHonor_BeautifulPirate_1_1";
		break;
		
		case "AffairOfHonor_BeautifulPirate_1_1":
			DialogExit();
			NextDiag.CurrentNode = "AffairOfHonor_BeautifulPirate_r";
			npchar.lifeday = 3;
			Rank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+12;
			Scl = 25+3*sti(pchar.rank);
			Mft = MOD_SKILL_ENEMY_RATE/15;
			sld = GetCharacter(NPC_GenerateCharacter("AffairOfHonor_BeautifulPirate_Man", "mercen_" + (rand(9)+1), "man", "man", Rank, sti(NPChar.nation), -1, true, "soldier"));
			// Jason: дохляки нам не нужны - делаем кулфайтера
			FantomMakeCoolFighter(sld, Rank, Scl, Scl, RandPhraseSimple("blade_10","blade_13"), RandPhraseSimple("pistol6","pistol4"), "bullet", Scl*3);
			sld.MultiFighter = 1.0+Mft; // мультифайтер
			FreeSitLocator(NPChar.city + "_tavern", "sit_front1");
			ChangeCharacterAddressGroup(sld, NPChar.city + "_tavern", "sit", "sit_front1");
			LAi_SetSitType(sld);
			LAi_SetImmortal(sld, true); // Еще успеем.
			sld.dialog.filename = "Quest\ForAll_dialog.c";
			sld.dialog.currentnode = "AffairOfHonor_BeautifulPirate_2";
			SetFunctionTimerCondition("AffairOfHonor_TimeIsLeft", 0, 0, 1, false);
			PChar.QuestTemp.AffairOfHonor.BeautifulPirate.Started = true;
			ReOpenQuestHeader("AffairOfHonor");
			AddQuestRecord("AffairOfHonor", "5");
		break;
		
		case "AffairOfHonor_BeautifulPirate_r":
			dialog.text = "E allora? Hai parlato con quel filibustiere? Ci lascerà in pace?";
			link.l1 = "Aspetta un po’. Ci sto lavorando.";
			link.l1.go = "exit";
			NextDiag.TempNode = "AffairOfHonor_BeautifulPirate_r";
		break;
		
		case "AffairOfHonor_BeautifulPirate_2":
			dialog.text = "Cosa vuoi? Non vedi che sto cercando di riposare qui?";
			link.l1 = "Eh, eh... Guarda un po', il gran signore delle pinte, rapinatore di donzelle e flagello di questa povera cittadina in carne ed ossa, ho ragione? Ma saresti altrettanto audace fuori dalle mura? Vicino al faro, un duello, fra due ore?";
			link.l1.go = "AffairOfHonor_BeautifulPirate_2a";
			DeleteQuestCondition("AffairOfHonor_TimeIsLeft");
			SetFunctionTimerConditionParam("AffairOfHonor_TimeIsLeft2", 0, 0, 0, GetHour() + 3, false);
		break;
		
		case "AffairOfHonor_BeautifulPirate_2a":
			dialog.text = "Oh-ho-ho! Ti spacchi la faccia da eroe, eh? Bah, lasciamo stare, compagno, oggi sono di buon umore quindi ti perdono. Vai a prendermi qualche boccale di birra!";
			link.l1 = "Non sono tuo compare. Devo ripetermi per uno scimunito come te? Hai fegato abbastanza per presentarti a duello come ne hai per farti vedere in taverna?";
			link.l1.go = "AffairOfHonor_BeautifulPirate_3";
		break;
		
		case "AffairOfHonor_BeautifulPirate_3":
			dialog.text = "Mi stai sfidando?! Che diavolo ti prende? Ti sei stufato di vivere, vuoi crepare, cane? Va bene, se proprio insisti, marcerò fino al faro, ti sventrerò e poi ridurrò in cenere anche questa dannata taverna!";
			link.l1 = "Parlar è facile, ma le spade costano — non scordarti di portarne una!";
			link.l1.go = "AffairOfHonor_BeautifulPirate_4";
		break;
		
		case "AffairOfHonor_BeautifulPirate_4":
			DialogExit();
			LAi_CharacterDisableDialog(NPChar);
			Locations[FindLocation(PChar.QuestTemp.AffairOfHonor.LighthouseId)].DisableEncounters = true;
			LAi_LocationDisableOfficersGen(PChar.QuestTemp.AffairOfHonor.LighthouseId, true);
			SetFunctionLocationCondition("AffairOfHonor_LighthouseLocEnter", PChar.QuestTemp.AffairOfHonor.LighthouseId, false);
		break;
		
		case "AffairOfHonor_BeautifulPirate_5":
			dialog.text = "E allora? Hai parlato con quel filibustiere? Se ne andrà finalmente e ci lascerà in pace? Mia sorella mi aveva detto che era uscito dalla taverna e non si era più fatto vedere...";
			link.l1 = "Già fatto. Quel tizio era un po’ sgarbato, ma le mie parole erano più che ragionevoli e convincenti. Tua sorella ormai non ha più nulla da temere.";
			link.l1.go = "AffairOfHonor_BeautifulPirate_6";
		break;
		
		case "AffairOfHonor_BeautifulPirate_6":
			dialog.text = "È... è finita? Possiamo finalmente respirare liberi? Grazie, capitano! E dove... dove si è cacciato quel furfante??";
			link.l1 = "Lui... è sulla sua nave. Ha deciso di mollare questa città il prima possibile.";
			link.l1.go = "AffairOfHonor_BeautifulPirate_7";
		break;
		
		case "AffairOfHonor_BeautifulPirate_7":
			dialog.text = "Hai reso un gran servizio ai cittadini di questa colonia! Tieni, prendi questa ricompensa per il tuo aiuto! È poca cosa, ma guadagnerai la stima di tutti i miei compari e, credimi, ne ho parecchi!";
			link.l1 = "Grazie di cuore! Buona fortuna a te e a tua sorella. Che possa trovare un marito d’onore. Addio!";
			link.l1.go = "exit";
			iTemp = 50+hrand(5)*10;
			AddMoneyToCharacter(pchar, iTemp*100);
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 2);
			AddComplexSelfExpToScill(50, 50, 50, 50);
			AddCharacterExpToSkill(pchar, "Leadership", 200);
			AddCharacterExpToSkill(pchar, "Fortune", 50);
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(NPChar);
		break;
		
		case "AffairOfHonor_Jackanapes_1":
			dialog.text = "Ah, davvero? E come pensi di fermarmi, eh?";
			link.l1 = "Con la mia spada, ovviamente, ché solo così si tratta un porco sfacciato come te.";
			link.l1.go = "AffairOfHonor_Jackanapes_1_1";
		break;
		
		case "AffairOfHonor_Jackanapes_1_1":
			dialog.text = "Splendido! Ti aspetterò vicino al faro fra due ore.";
			link.l1 = "Bene! Ci sarò di sicuro.";
			link.l1.go = "AffairOfHonor_Jackanapes_1_2";
		break;
		
		case "AffairOfHonor_Jackanapes_1_2":
			DialogExit();
			PChar.QuestTemp.AffairOfHonor.Jackanapes.Started = true;
			Locations[FindLocation(PChar.QuestTemp.AffairOfHonor.LighthouseId)].DisableEncounters = true;
			LAi_LocationDisableOfficersGen(PChar.QuestTemp.AffairOfHonor.LighthouseId, true);
			NPChar.id = "AffairOfHonor_Jackanapes_Man";
			LAi_SetImmortal(NPChar, true); // Еще успеем.
			SetFunctionTimerConditionParam("AffairOfHonor_TimeIsLeft", 0, 0, 0, GetHour() + 3, false);
			// Jason: отсрочка на 2 часа как договаривались
			SetFunctionTimerConditionParam("AffairOfHonor_LighthouseGotoMeeting", 0, 0, 0, GetHour()+2, false);
			ReOpenQuestHeader("AffairOfHonor");
			AddQuestRecord("AffairOfHonor", "7");
		break;
		
		case "AffairOfHonor_Jackanapes_2":
			dialog.text = "Levati dai piedi, vigliacco!";
			link.l1 = "...";
			link.l1.go = "exit";
			LAi_CharacterDisableDialog(NPChar);
		break;
		
		case "AffairOfHonor_WolvesAndSheeps_1":
			dialog.text = "Capitano, quel bastardo non è così semplice, Tom, mio vecchio compare, è crepato in duello contro di lui, accusato di barare alle carte! Era innocente, lo giuro. Ma il governatore ha detto che in quel dannato duello non c’era reato.";
			link.l1 = "Hm... Tutta colpa del tuo compare. Il gioco truccato a carte può farti finire male, credimi.";
			link.l1.go = "AffairOfHonor_WolvesAndSheeps_2";
		break;
		
		case "AffairOfHonor_WolvesAndSheeps_2":
			dialog.text = "Già? Sono arrivati quattro bari negli ultimi quindici giorni in città. E tutti quanti cercavano di fregare il nostro nobiluomo? Cosa ne pensi? Ti dico io: è proprio quel nobiluomo il vero baro. Se non ci credi, vai a controllare con i tuoi occhi.";
			link.l1 = "Vuoi rischiare con lui? No, non mi piace giocare d’azzardo. Manco per sogno.";
			link.l1.go = "exit";
			link.l2 = "Suppongo che lo farò... Qui c’è qualcosa che puzza davvero.";
			link.l2.go = "AffairOfHonor_WolvesAndSheeps_3";
		break;
		
		case "AffairOfHonor_WolvesAndSheeps_3":
			dialog.text = "Capitano, io e i miei compari abbiamo messo insieme una bella somma per pagare colui che ci svelerà l’identità di quel nobile, e per vendicarci di tutte le sue malefatte. Ti aspetterò in città per darti la tua ricompensa, una volta che il lavoro sarà compiuto.";
			link.l1 = "Lo farò, se ciò che dici corrisponde a verità.";
			link.l1.go = "AffairOfHonor_WolvesAndSheeps_4";
		break;
		
		case "AffairOfHonor_WolvesAndSheeps_4":
			DialogExit();
			PChar.QuestTemp.AffairOfHonor.WolvesAndSheeps.Started = true;
			npchar.lifeday = 3;
			// Jason: дохляки нам не нужны - делаем кулфайтера
			Rank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+10;
			Scl = 30+2*sti(pchar.rank);
			Mft = MOD_SKILL_ENEMY_RATE/20;
			sld = GetCharacter(NPC_GenerateCharacter("AffairOfHonor_WolvesAndSheeps_Man", "citiz_" + (rand(9)+1), "man", "man", Rank, sti(NPChar.nation), -1, true, "soldier"));
			FantomMakeCoolFighter(sld, Rank, Scl, Scl, RandPhraseSimple("blade_08","blade_09"), RandPhraseSimple("pistol1","pistol5"), "bullet", Scl*3);
			sld.MultiFighter = 1.0+Mft; // мультифайтер
			sld.skill.Fortune = 1;
			sld.Default = NPChar.city + "_tavern";
			sld.Default.group = "sit";
			sld.Default.ToLocator = "sit_front1";
			LAi_SetSitType(sld);
			ChangeCharacterAddressGroup(sld, NPChar.city + "_tavern", "sit", "sit_base1");
			LAi_SetImmortal(sld, true); // Еще успеем.
			sld.dialog.filename = "Quest\ForAll_dialog.c";
			sld.dialog.currentnode = "AffairOfHonor_WolvesAndSheeps_5";
			SetFunctionTimerCondition("AffairOfHonor_TimeIsLeft", 0, 0, 1, false);
			ReOpenQuestHeader("AffairOfHonor");
			AddQuestRecord("AffairOfHonor", "9");
		break;
		
		case "AffairOfHonor_WolvesAndSheeps_5":
			dialog.text = "I miei rispetti, signore! Vedo davanti a me un uomo d’onore e forse... un giocatore d’azzardo? Che ne dite di una partita, eh?";
			link.l1 = "Certo! Parliamo della posta in gioco. Che ne dici di 50 monete?";
			link.l1.go = "AffairOfHonor_WolvesAndSheeps_6";
		break;
		
		case "AffairOfHonor_WolvesAndSheeps_6":
			if(sti(PChar.money) < 200)
			{
				dialog.text = "Mi stai prendendo in giro? Non ce li hai, vero!";
				link.l1 = "Hai ragione...";
				link.l1.go = "exit";
				NextDiag.TempNode = "AffairOfHonor_WolvesAndSheeps_5";
			}
			else
			{
				dialog.text = "La posta non importa, giochiamo d’azzardo, ed è questo il bello. Quasi non ricordo più che aspetto hanno le carte, per colpa degli idioti locali.";
				link.l1 = "Ebbene, cominciamo.";
				link.l1.go = "exit";
				PChar.QuestTemp.friend_in_tavern = NPChar.id;
				AddDialogExitQuest("alc");
				DeleteQuestCondition("AffairOfHonor_TimeIsLeft");
				SetFunctionTimerConditionParam("AffairOfHonor_TimeIsLeft2", 0, 0, 0, GetHour() + 3, false);
				NextDiag.TempNode = "AffairOfHonor_WolvesAndSheeps_7";
				NextDiag.CurrentNode = NextDiag.TempNode;
				DialogExit();
			}
		break;
		
		case "AffairOfHonor_WolvesAndSheeps_7":
			dialog.text = "Dunque, la posta è di 50 monete.";
			link.l1 = "...";
			link.l1.go = "AffairOfHonor_WolvesAndSheeps_8";
			PChar.GenQuest.Cards.npcharIdx = NPChar.index;
			PChar.GenQuest.Cards.iRate = 50;
            PChar.GenQuest.Cards.SitType = true;
		break;
		
		case "AffairOfHonor_WolvesAndSheeps_8":
			NextDiag.TempNode = "AffairOfHonor_WolvesAndSheeps_9";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchCardsGame();
		break;
		
		case "AffairOfHonor_WolvesAndSheeps_9":
			dialog.text = "Aspetta un attimo, che succede?.. Impossibile! Signore, siete un imbroglione! Ridatemi le mie monete!";
			link.l1 = "Devi avere buone ragioni per accusarmi,  "+GetAddress_FormToNPC(NPChar)+" Faresti meglio a sparare subito, o sarà un duello!";
			link.l1.go = "AffairOfHonor_WolvesAndSheeps_10";
		break;
		
		case "AffairOfHonor_WolvesAndSheeps_10":
			dialog.text = "Ah, così, senza tante storie? Va bene, allora a duello! Oggi, tra due ore, vicino al faro!";
			link.l1 = "Affare fatto!";
			link.l1.go = "AffairOfHonor_WolvesAndSheeps_11";
		break;
		
		case "AffairOfHonor_WolvesAndSheeps_11":
			AddDialogExitQuest("exit_sit");
			DialogExit();
			LAi_CharacterDisableDialog(NPChar);
			Locations[FindLocation(PChar.QuestTemp.AffairOfHonor.LighthouseId)].DisableEncounters = true;
			LAi_LocationDisableOfficersGen(PChar.QuestTemp.AffairOfHonor.LighthouseId, true);
			// Jason: отсрочка на 2 часа как договаривались
			SetFunctionTimerConditionParam("AffairOfHonor_LighthouseGotoMeeting", 0, 0, 0, GetHour()+2, false);
		break;
		
		case "AffairOfHonor_WolvesAndSheeps_12":
			dialog.text = "Qualche novità, capitano?";
			link.l1 = "Avevi ragione, mi accusarono pure di barare, così dovetti sventrare quel bastardo in duello.";
			link.l1.go = "AffairOfHonor_WolvesAndSheeps_13";
		break;
		
		case "AffairOfHonor_WolvesAndSheeps_13":
			dialog.text = "Vedi? Lo sapevo! Mille grazie da parte mia e dei miei compari! Tieni, prendi la tua ricompensa, capitano.";
			link.l1 = "Grazie.";
			link.l1.go = "exit";
			iTemp = 50+hrand(5)*10;
			AddMoneyToCharacter(pchar, iTemp*100);
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterComplexReputation(PChar, "nobility", 2);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 2);
			AddComplexSelfExpToScill(50, 50, 50, 50);
			AddCharacterExpToSkill(pchar, "Leadership", 200);
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(NPChar);
		break;
		
		case "AffairOfHonor_CowardFencer_1":
			dialog.text = "Ti ho già detto che sono venuto qui per propormi come maestro di scherma? No? Dunque, il governatore locale cerca un insegnante per il nipote e la cosa mi calza a pennello. Conosco i rudimenti di quest’arte, ma non l’ho mai praticata davvero sul campo.\nQuasi avevo la faccenda in pugno, quando è venuto fuori che un mercante del posto è nei guai: qualche furfante minaccioso gli sta dando del filo da torcere. Il governatore mi ha ordinato di occuparmi della questione, così da mettere alla prova le mie abilità.";
			link.l1 = "Allora fallo. Addio.";
			link.l1.go = "exit";
			link.l2 = "E cosa vuole questo furfante dal mercante, e perché dovrei impicciarmi io?";
			link.l2.go = "AffairOfHonor_CowardFencer_1_1";
		break;
		
		case "AffairOfHonor_CowardFencer_1_1":
			dialog.text = "Pensavo che quell’uomo fosse un mercenario e che si potesse sempre trattare coi mercenari. Vecchi debiti o chissà cosa… Ma quello era davvero deciso a continuare a tormentare il mercante. Volevo chiederti di aiutare sia me che lui: salva il mercante dalle grinfie di quel cane e così adempirai pure agli ordini del governatore.\nHo davvero bisogno di questo posto e non riesco a liberarmi del mercenario da solo. Ti scongiuro, aiutami! Ti darò fino all’ultimo reale che ho messo da parte, oppure sarò costretto a lasciare la città coperto di vergogna!";
			link.l1 = "Va bene, va bene, ti aiuterò... 'gran maestro di scherma'.";
			link.l1.go = "AffairOfHonor_CowardFencer_1_2";
		break;
		
		case "AffairOfHonor_CowardFencer_1_2":
			DialogExit();
			npchar.lifeday = 3;
			// Jason: дохляки нам не нужны - делаем кулфайтера
			Rank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+15;
			Scl = 30+3*sti(pchar.rank);
			Mft = MOD_SKILL_ENEMY_RATE/15;
			sld = GetCharacter(NPC_GenerateCharacter("AffairOfHonor_CowardFencer_Man", "mercen_"+(rand(7)+23), "man", "man", Rank, sti(NPChar.nation), -1, true, "soldier"));
			FantomMakeCoolFighter(sld, Rank, Scl, Scl, RandPhraseSimple("blade_06","blade_10"), RandPhraseSimple("pistol4","pistol6"), "bullet", Scl*3+70);
			sld.MultiFighter = 1.0+Mft; // мультифайтер
			LAi_SetCitizenType(sld);
			ChangeCharacterAddressGroup(sld, NPChar.city + "_store", "goto", "goto3");
			LAi_SetImmortal(sld, true); // Еще успеем.
			sld.dialog.filename = "Quest\ForAll_dialog.c";
			sld.dialog.currentnode = "AffairOfHonor_CowardFencer_2";
			SetFunctionTimerCondition("AffairOfHonor_TimeIsLeft", 0, 0, 1, false);
			PChar.QuestTemp.AffairOfHonor.CowardFencer.Started = true;
			ReOpenQuestHeader("AffairOfHonor");
			AddQuestRecord("AffairOfHonor", "11");
		break;
		
		case "AffairOfHonor_CowardFencer_2":
			dialog.text = "Cosa vuoi? Non vedi che sono occupato?!";
			link.l1 = "Disturbi un mercante rispettabile e fai tutto questo baccano!?";
			link.l1.go = "AffairOfHonor_CowardFencer_3";
			DeleteQuestCondition("AffairOfHonor_TimeIsLeft");
			SetFunctionTimerConditionParam("AffairOfHonor_TimeIsLeft2", 0, 0, 0, GetHour() + 3, false);
		break;
		
		case "AffairOfHonor_CowardFencer_3":
			dialog.text = "Bah! Un altro protettore? Mi costa meno pagarmi che assumere guardie ogni giorno. Non sono un amante delle uccisioni, preferisco riscuotere i debiti, quindi se ti credi tanto valoroso vieni al faro e misuriamoci a duello. E se non lo sei, non venire più a rompermi le scatole.";
			link.l1 = "D’accordo! Ti aspetterò laggiù.";
			link.l1.go = "AffairOfHonor_CowardFencer_4";
		break;
		
		case "AffairOfHonor_CowardFencer_4":
			DialogExit();
			Locations[FindLocation(PChar.QuestTemp.AffairOfHonor.LighthouseId)].DisableEncounters = true;
			LAi_LocationDisableOfficersGen(PChar.QuestTemp.AffairOfHonor.LighthouseId, true);
			SetFunctionLocationCondition("AffairOfHonor_LighthouseLocEnter", PChar.QuestTemp.AffairOfHonor.LighthouseId, false);
			LAi_CharacterDisableDialog(NPChar);
		break;
		
		case "AffairOfHonor_CowardFencer_4_1":
			dialog.text = "Pare che tu sia ancora più codardo di me...";
			link.l1 = "Già, sono proprio io.";
			link.l1.go = "exit";
			LAi_CharacterDisableDialog(NPChar);
		break;
		
		case "AffairOfHonor_CowardFencer_5":
			dialog.text = "Novità, capitano?";
			link.l1 = "Il mercenario è morto. Spero che tu abbia preso il suo posto, adesso?";
			link.l1.go = "AffairOfHonor_CowardFencer_6";
		break;
		
		case "AffairOfHonor_CowardFencer_6":
			dialog.text = "Oh, capitano, grazie infinite! Prendi la tua ricompensa e andrò subito a riferire al nostro governatore!";
			link.l1 = "Addio... padrone.";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterComplexReputation(PChar, "nobility", 2);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 1);
			AddComplexSelfExpToScill(60, 60, 60, 60);
			AddCharacterExpToSkill(pchar, "Leadership", 200);
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(NPChar);
			GiveItem2Character(pchar, "chest"); 
			Log_Info("You have received a chest filled with doubloons");
			PlaySound("interface\important_item.wav");
		break;
		
		case "AffairOfHonor_CoatHonor_1":
			LAi_CharacterEnableDialog(NPChar);
			NextDiag.TempNode = "AffairOfHonor_CoatHonor_2";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			PChar.QuestTemp.friend_in_tavern = npchar.id;
			AddDialogExitQuest("alc");
		break;
		
		case "AffairOfHonor_CoatHonor_2":
			dialog.text = "Un altro giro?";
			link.l1 = "Alla salute, beviamo fino in fondo.";
			link.l1.go = "AffairOfHonor_CoatHonor_2_1";
		break;
		
		case "AffairOfHonor_CoatHonor_2_1":
			dialog.text = "E ancora di più!";
			link.l1 = "Aspetta un attimo! Dove diavolo te ne vai così in fretta?";
			link.l1.go = "AffairOfHonor_CoatHonor_2_2";
		break;
		
		case "AffairOfHonor_CoatHonor_2_2":
			dialog.text = "Al diavolo le domande! Beviamo!";
			link.l1 = "D'accordo, ma magari poi mi racconterai che ti è successo, eh?";
			link.l1.go = "AffairOfHonor_CoatHonor_2_3";
		break;
		
		case "AffairOfHonor_CoatHonor_2_3":
			dialog.text = "Sei davvero interessato? Allora ascolta finché la mia lingua regge! Tra qualche giorno non potrò più fiatare, perché sarò stecchito... Già, stecchito! E la colpa è del rum. Troppo rum, e quell’ufficialaccio che il diavolo mi ha scagliato addosso!\nNon mi sarei mai messo a duellare col miglior schermidore della guarnigione e dell’intera città se fossi stato sobrio, o almeno non così ubriaco. Ma ormai? Sono spacciato, rovinato, morto! Che idiota ubriacone che sono...";
			link.l1 = "Sì, quella è stata proprio una sciocchezza. Ma forse userai più cervello in futuro... sempre che tu sopravviva al duello, s'intende. Addio.";
			link.l1.go = "AffairOfHonor_CoatHonor_Exit";
			link.l2 = "Ubriacarsi non è nemmeno la scelta migliore, ufficiale. Son certo che una via d’uscita da questo guaio si troverà.";
			link.l2.go = "AffairOfHonor_CoatHonor_2_4";
		break;
		
		case "AffairOfHonor_CoatHonor_2_4":
			dialog.text = "Che razza di soluzione? Disertare e perdere la reputazione e la divisa da ufficiale? O magari tagliarmi la gola da solo, così non mi sgozzeranno come un porco? Qual è il tuo consiglio, allora?";
			link.l1 = "Nessuno dei due. Ti darò una mano, e cercherò di impedire al tuo avversario di farti del male prima del duello. Dove posso trovarlo?";
			link.l1.go = "AffairOfHonor_CoatHonor_2_5";
		break;
		
		case "AffairOfHonor_CoatHonor_2_5":
			dialog.text = "Sei davvero serio? Lo farai?! Oh, te lo giuro, te ne sarai ben ricompensato!\nLo puoi trovare in città. La sua amante vive qui, tutti gli ufficiali ne hanno sentito parlare, ma ahimè, nessuno sa dove abita... Scommetto che anche lui si trova là.";
			link.l1 = "Basta così. Aspettami qui. Vado io a scambiare due parole con questo... 'gran schermidore'.";
			link.l1.go = "AffairOfHonor_CoatHonor_3";
		break;
		
		case "AffairOfHonor_CoatHonor_Exit":
			DialogExit();
			AddDialogExitQuest("exit_sit");
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		
		case "AffairOfHonor_CoatHonor_3":
			AddDialogExitQuest("exit_sit");
			NextDiag.CurrentNode = "AffairOfHonor_CoatHonor_Next";
			DialogExit();
			SetFunctionTimerCondition("AffairOfHonor_TimeIsLeft", 0, 0, 2, false);
			PChar.QuestTemp.AffairOfHonor.CoatHonor.Started = true;
			PChar.QuestTemp.AffairOfHonor.CoatHonor.CityId = NPChar.city;
			PChar.QuestTemp.AffairOfHonor.CoatHonor.NeedGenerateDuelMan = true;
			ReOpenQuestHeader("AffairOfHonor");
			AddQuestRecord("AffairOfHonor", "13");
			npchar.lifeday = 2;
		break;
		
		case "AffairOfHonor_CoatHonor_Next":
			dialog.text = "Avete novità per me, signore? Buone, o... non proprio buone?";
			link.l1 = "Non ho ancora novità. Aspetta qui. Andrà tutto bene.";
			link.l1.go = "exit";
			NextDiag.TempNode = "AffairOfHonor_CoatHonor_Next";
		break;
		
		case "AffairOfHonor_CoatHonor_Final":
			dialog.text = "Hai qualche novità per me, signore? Buone... o sono tempeste in vista?";
			link.l1 = "È finita. Il tuo possibile avversario non farà più del male a nessuno... Ora sei al sicuro. Ma spero che tu abbia imparato la lezione e non sia più aggressivo con chi non conosci.";
			link.l1.go = "AffairOfHonor_CoatHonor_Final_1";
		break;
		
		case "AffairOfHonor_CoatHonor_Final_1":
			dialog.text = "Non stai scherzando, vero? Io... ti sono davvero riconoscente, "+GetAddress_Form(NPChar)+"! Ecco, prendi tutto quello che ho. Questo è il mio salario, prendilo tutto!\nUna lezione, dici? Sì, maledizione, hai ragione! Non succederà mai più! Te lo prometto, e grazie ancora per avermi dato un'altra possibilità!";
			link.l1 = "Va bene allora. Addio, ufficiale...";
			link.l1.go = "AffairOfHonor_CoatHonor_Final_2";
		break;
		
		case "AffairOfHonor_CoatHonor_Final_2":
			DialogExit();
			npchar.lifeday = 0;
			NextDiag.CurrentNode = "AffairOfHonor_CoatHonor_End";
			TakeNItems(pchar, "purse3", 1); 
			Log_Info("You have received a purse with doubloons");
			PlaySound("interface\important_item.wav");
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 2);
			AddComplexSelfExpToScill(50, 50, 50, 50);
			AddCharacterExpToSkill(pchar, "Leadership", 200);
			AddCharacterExpToSkill(pchar, "Fortune", 50);
		break;
		
		case "AffairOfHonor_CoatHonor_End":
			dialog.text = "Grazie ancora, "+GetAddress_Form(NPChar)+", per il tuo aiuto!";
			link.l1 = "Sarai sempre il benvenuto...";
			link.l1.go = "exit";
			NextDiag.TempNode = "AffairOfHonor_CoatHonor_End";
		break;
		
		case "AffairOfHonor_CoatHonor_4":
			dialog.text = "Ehi, che diavolo? Che ci fai nelle stanze della mia dama? Sparisci di qui o ti trascinerò fuori a calci!";
			link.l1 = "Vado dove mi pare e non ti devo spiegazioni per il mio comportamento! Con la forza? Provaci allora!";
			link.l1.go = "AffairOfHonor_CoatHonor_5";
		break;
		
		case "AffairOfHonor_CoatHonor_5":
			dialog.text = "Che insolenza! Un'audacia mai vista! Signore, siete proprio in errore! Lasciate questa casa all'istante o vi giuro che vi pentirete d’esser venuto al mondo!";
			link.l1 = "Parole al vento! Sarai tu a pentirtene, non io, "+GetAddress_FormToNPC(NPChar)+"! ";
			link.l1.go = "AffairOfHonor_CoatHonor_6";
		break;
		
		case "AffairOfHonor_CoatHonor_6":
			dialog.text = "Davvero? Allora sta' attento! Se ti uccido sotto questo tetto, sarà omicidio. La tua fine macchierebbe il mio nome: gli uomini d’onore risolvono certe faccende presso un faro!\nTi sfido, "+GetAddress_Form(NPChar)+", uomo insolente! Pagherai per le tue parole! Allora, un duello tra due ore?";
			link.l1 = "Certo, "+GetAddress_FormToNPC(NPChar)+" tipo tosto.";
			link.l1.go = "AffairOfHonor_CoatHonor_7";
		break;
		
		case "AffairOfHonor_CoatHonor_7":
			dialog.text = "Allora assicurati di essere lì al momento giusto. Hai ancora tempo per ordinare un requiem dal nostro prete.";
			link.l1 = "Un requiem per te? Non vali neanche un reale bucato. Ci si vede vicino al faro!";
			link.l1.go = "AffairOfHonor_CoatHonor_8";
		break;
		
		case "AffairOfHonor_CoatHonor_8":
			DialogExit();
			Locations[FindLocation(PChar.QuestTemp.AffairOfHonor.LighthouseId)].DisableEncounters = true;
			LAi_LocationDisableOfficersGen(PChar.QuestTemp.AffairOfHonor.LighthouseId, true);
			// Jason: отсрочка на 2 часа как договаривались
			SetFunctionTimerConditionParam("AffairOfHonor_LighthouseGotoMeeting", 0, 0, 0, GetHour()+2, false);
			DeleteQuestCondition("AffairOfHonor_TimeIsLeft");
			SetFunctionTimerConditionParam("AffairOfHonor_TimeIsLeft2", 0, 0, 0, GetHour() + 3, false);
			NextDiag.CurrentNode = "AffairOfHonor_CoatHonor_9";
			LAi_SetWarriorType(npchar); // 140313
		break;
		
		case "AffairOfHonor_CoatHonor_9":
			dialog.text = "Vattene, furfante!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "AffairOfHonor_CoatHonor_9";
		break;
		
		case "AffairOfHonor_GodJudgement_1":
			dialog.text = "Intendi il governatore? Ah! 'Il giudizio di Dio', ecco cosa mi ha risposto il governatore alle mie lamentele! Duello! Che ne dici? Io sono solo un tranquillo piantatore amante della pace, non un bandito né un combattente.\nQuesta sarà un’esecuzione, non un duello! E tu, senza dubbio, te la cavi meglio di me in queste faccende. Perciò ti chiedo di rappresentarmi nel duello che si avvicina. Fidati, non resterai senza ricompensa.";
			link.l1 = "Quando si terrà il duello?";
			link.l1.go = "AffairOfHonor_GodJudgement_1_1";
		break;
		
		case "AffairOfHonor_GodJudgement_1_1":
			dialog.text = "Oggi, prima di mezzanotte, vicino al faro. Mi darai una mano?";
			link.l1 = "D'accordo, ti aiuterò. Aspettami in città!";
			link.l1.go = "AffairOfHonor_GodJudgement_1_2";
		break;
		
		case "AffairOfHonor_GodJudgement_1_2":
			DialogExit();
			PChar.QuestTemp.AffairOfHonor.GodJudgement.Started = true;
			PChar.QuestTemp.AffairOfHonor.GodJudgement.CanSpeakPriest = true;
			PChar.QuestTemp.AffairOfHonor.GodJudgement.CityId = NPChar.city;
			Locations[FindLocation(PChar.QuestTemp.AffairOfHonor.LighthouseId)].DisableEncounters = true;
			LAi_LocationDisableOfficersGen(PChar.QuestTemp.AffairOfHonor.LighthouseId, true);
			SetFunctionTimerConditionParam("AffairOfHonor_TimeIsLeft", 0, 0, 0, GetHour() + 3, false);
			SetFunctionLocationCondition("AffairOfHonor_LighthouseLocEnter", PChar.QuestTemp.AffairOfHonor.LighthouseId, false);
			npchar.lifeday = 3;
			// Jason: дохляки нам не нужны - делаем кулфайтера
			Rank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+12;
			Scl = 30+2*sti(pchar.rank);
			Mft = MOD_SKILL_ENEMY_RATE/20;
			sld = GetCharacter(NPC_GenerateCharacter("AffairOfHonor_GodJudgement_Man", "citiz_" + (rand(9) + 41), "man", "man", Rank, sti(NPChar.nation), -1, true, "soldier"));
			FantomMakeCoolFighter(sld, Rank, Scl, Scl, RandPhraseSimple("blade_05","blade_07"), RandPhraseSimple("pistol1","pistol5"), "bullet", Scl*3);
			sld.MultiFighter = 1.0+Mft; // мультифайтер
			LAi_SetImmortal(sld, true); // Еще успеем.
			sld.dialog.filename = "Quest\ForAll_dialog.c";
			ReOpenQuestHeader("AffairOfHonor");
			AddQuestRecord("AffairOfHonor", "15");
		break;
		
		case "AffairOfHonor_GodJudgement_2":
			dialog.text = "Dimmi, che diavolo è successo laggiù? Abbiamo... scusa, hai vinto tu?";
			link.l1 = "Sono certo che ti interesserà sapere che c’è stata un’imboscata. Pare che il tuo vicino abbia voluto andare sul sicuro invitando qualche compare in più invece che uno solo, e tutti erano furfanti navigati. Per fortuna, io sono un vecchio lupo di mare con la spada.";
			link.l1.go = "AffairOfHonor_GodJudgement_3";
		break;
		
		case "AffairOfHonor_GodJudgement_3":
			dialog.text = "Che canaglia! Ora, suppongo, il nostro governatore non avrà più alcuna ragione per rifiutare la mia richiesta di far arrestare quel furfante! Grazie! Prendi la tua ricompensa e io devo recarmi alla residenza.";
			link.l1 = "Addio.";
			link.l1.go = "exit";
			npchar.lifeday = 0;
			TakeNItems(pchar, "purse3", 1); 
			TakeNItems(pchar, "purse"+(hrand(2)+1), 1); 
			Log_Info("You have received purses of doubloons");
			PlaySound("interface\important_item.wav");
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterComplexReputation(PChar, "nobility", 3);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 2);
			AddComplexSelfExpToScill(50, 50, 50, 50);
			AddCharacterExpToSkill(pchar, "Leadership", 200);
			AddCharacterExpToSkill(pchar, "Fortune", 50);
			LAi_CharacterDisableDialog(NPChar);
		break;
		
		// Диалоги до боя -->
		case "AffairOfHonor_BeforeFight_1":
			dialog.text = "È una vera goduria giocare senza grane, ché quelle maledette sono più sfuggenti di un'anguilla.";
			link.l1 = "Calmati, informerò gli sviluppatori.";
			link.l1.go = "AffairOfHonor_BeforeFight_2";
			
			switch(AffairOfHonor_GetCurQuest())
			{
				case "Cavalier":
					dialog.text = "Ah, eccoti. Questi sono i miei compari e luogotenenti. Iniziamo?";
					link.l1 = "Sono al vostro servizio!";
					link.l1.go = "AffairOfHonor_BeforeFight_2";
				break;
				
				case "HonorSlave":
					dialog.text = "Tutti sono radunati. Sei pronto?";
					link.l1 = "Sì, possiamo cominciare!";
					link.l1.go = "AffairOfHonor_BeforeFight_2";
				break;
				
				case "BeautifulPirate":
					dialog.text = "Finalmente! Cominciavo a pensare che tutta questa scarpinata fosse stata per niente... Sbrighiamoci, ho lasciato una tazza di rum e una bella sgualdrina calda in taverna!";
					link.l1 = "Sono certo che non avrai più bisogno di nessuno dei due, ormai!";
					link.l1.go = "AffairOfHonor_BeforeFight_2"
				break;
				
				case "Jackanapes":
					dialog.text = "Dunque hai deciso di venire? Finalmente! Allora, cominciamo!";
					link.l1 = "Non correre così, potresti inciampare su una lama.";
					link.l1.go = "AffairOfHonor_BeforeFight_2"
				break;
				
				case "WolvesAndSheeps":
					dialog.text = "E questi sono i miei luogotenenti, signore. Ora preparatevi a crepare!";
					link.l1 = "Dopo di te.";
					link.l1.go = "AffairOfHonor_BeforeFight_2"
				break;
				
				case "CowardFencer":
					dialog.text = "Eccoci qua. Prepara la tua spada, signore!";
					link.l1 = "Volentieri, che vinca il migliore!";
					link.l1.go = "AffairOfHonor_BeforeFight_2"
				break;
				
				case "CoatHonor":
					dialog.text = "Eccellente, sono arrivati tutti... Iniziamo, signore!";
					link.l1 = "Andiamo a ballare!";
					link.l1.go = "AffairOfHonor_BeforeFight_2"
				break;
				
				case "GodJudgement":
					dialog.text = "E tu chi saresti? Non hai proprio l’aria d’un cittadino qualsiasi, compare...";
					link.l1 = "E allora? Dovrei incrociare le lame con te?!";
					link.l1.go = "AffairOfHonor_BeforeFight_2_1"
				break;
			}
		break;
		
		case "AffairOfHonor_BeforeFight_2_1":
			dialog.text = "Ah! Un duello! Pare che tu sia proprio il nostro cliente. Ragazzi, infilziamolo e andiamo a riscuotere la ricompensa. Sventriamolo!";
			link.l1 = "Un agguato? Che miseria, vi servirà ben altro per mettermi al tappeto...";
			link.l1.go = "AffairOfHonor_BeforeFight_2";
		break;
		
		case "AffairOfHonor_BeforeFight_2":
			LAi_LocationFightDisable(LoadedLocation, false);
			AddDialogExitQuest("MainHeroFightModeOn");
			PChar.Quest.AffairOfHonor_KillChar.win_condition.l1 = "NPC_Death";
			PChar.Quest.AffairOfHonor_KillChar.win_condition.l1.character = "AffairOfHonor_" + AffairOfHonor_GetCurQuest() + "_Man";
			PChar.Quest.AffairOfHonor_KillChar.function = "AffairOfHonor_KillChar";
			if(hrand(1) == 0 && AffairOfHonor_GetCurQuest() != "CowardFencer" && AffairOfHonor_GetCurQuest() != "CoatHonor")
			{
				PChar.QuestTemp.AffairOfHonor.FightWithHelpers = true;
				Log_TestInfo("Seconds will fight");
			}
			// В квесте "Божий суд" всегда нападают.
			if(AffairOfHonor_GetCurQuest() == "GodJudgement")
			{
				Log_TestInfo("Global massacre");
				sld = CharacterFromID("AffairOfHonor_Helper_1");
				LAi_Group_MoveCharacter(sld, "AffairOfHonor_Enemies");
				LAi_SetImmortal(sld, false);
				sld = CharacterFromID("AffairOfHonor_Helper_2");
				LAi_Group_MoveCharacter(sld, "AffairOfHonor_Enemies");
				LAi_SetImmortal(sld, false);
				iTemp = hrand(3);
				if(AffairOfHonor_GetCurQuest() == "GodJudgement")
				{
					for(i = 0; i < iTemp; i++)
					{
						sld = GetCharacter(NPC_GenerateCharacter("AffairOfHonor_GodJudgement_Man_" + i, "pirate_" + (rand(9) + 1), "man", "man", sti(PChar.rank) + rand(5), sti(sld.nation), -1, true, "soldier"));
						SetFantomParamFromRank(sld, sti(PChar.rank) + rand(5), true);
						ChangeCharacterAddressGroup(sld, PChar.location, "smugglers", "smuggler0" + (i + 1));
						LAi_Group_MoveCharacter(sld, "AffairOfHonor_Enemies");
					}
				}
			}
			LAi_Group_MoveCharacter(NPChar, "AffairOfHonor_Enemies");
			LAi_Group_SetRelation("AffairOfHonor_Enemies", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_Group_FightGroups("AffairOfHonor_Enemies", LAI_GROUP_PLAYER, true);
			
			DialogExit();
		break;
		// <-- Диалоги до боя.
		
		// Диалоги после боя -->
		case "AffairOfHonor_AfterFight_1":
			if(CheckAttribute(PChar, "QuestTemp.AffairOfHonor.FightWithHelpers"))
			{
				dialog.text = "Credi forse che ti lasceremo ammazzare il nostro compagno e filartela così, senza conseguenze? Alle armi!";
				link.l1 = "Me lo dovevo aspettare da un furfante così miserabile!";
				link.l1.go = "AffairOfHonor_AfterFight_FightWithHelpers";
				break;
			}
			if(AffairOfHonor_GetCurQuest() == "CoatHonor")
			{
				dialog.text = "Capitano, l’onore è stato ristabilito, hai vinto. Ma lascia che ti dia un buon consiglio: sparisci da questa città e non farti vedere qui per un po’ di tempo...";
				link.l1 = "E qual è il problema??";
				link.l1.go = "AffairOfHonor_AfterFight_2_1";
			}
			else
			{
				dialog.text = "Tutto fu fatto per onore, ora andiamo a riprenderci il nostro compagno.";
				link.l1 = "Certo, non ti fermerò...";
				link.l1.go = "AffairOfHonor_AfterFight_2";
			}
		break;
		
		case "AffairOfHonor_AfterFight_2_1":
			dialog.text = "Il problema è che hai fatto fuori un attendente del nostro comandante. Era una canaglia, nessuno sentirà la sua mancanza... ma il comandante gli voleva bene e non ti perdonerà mai per la morte del suo compare.";
			link.l1 = "Grazie per il consiglio, ne farò tesoro. Addio.";
			link.l1.go = "AffairOfHonor_AfterFight_2";
		break;
		
		case "AffairOfHonor_AfterFight_2":
			DialogExit();
			LAi_ActorGoToLocation(NPChar, "reload", FindNearestFreeLocator("reload"), "none", "", "", "", 3.0);
			LAi_ActorGoToLocation(CharacterFromID("AffairOfHonor_Helper_2"), "reload", FindNearestFreeLocator("reload"), "none", "", "", "", 3.0);
			if(AffairOfHonor_GetCurQuest() == "CoatHonor")
			{
				ChangeCharacterComplexReputation(PChar, "nobility", 5);
			}
		break;
		
		case "AffairOfHonor_AfterFight_FightWithHelpers":
			iTemp = hrand(3);
			AddDialogExitQuest("MainHeroFightModeOn");
			sld = CharacterFromID("AffairOfHonor_Helper_1");
			LAi_Group_MoveCharacter(sld, "AffairOfHonor_Enemies");
			LAi_SetImmortal(sld, false);
			sld = CharacterFromID("AffairOfHonor_Helper_2");
			LAi_Group_MoveCharacter(sld, "AffairOfHonor_Enemies");
			LAi_SetImmortal(sld, false);
			if(AffairOfHonor_GetCurQuest() == "GodJudgement")
			{
				for(i = 0; i < iTemp; i++)
				{
					sld = GetCharacter(NPC_GenerateCharacter("AffairOfHonor_GodJudgement_Man_" + i, "pirate_" + (rand(9) + 1), "man", "man", sti(PChar.rank) + rand(5), sti(sld.nation), -1, true, "soldier"));
					SetFantomParamFromRank(sld, sti(PChar.rank) + rand(5), true);
					ChangeCharacterAddressGroup(sld, PChar.location, "smugglers", "smuggler0" + (i + 1));
					LAi_Group_MoveCharacter(sld, "AffairOfHonor_Enemies");
				}
			}
			LAi_Group_SetRelation("AffairOfHonor_Enemies", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_Group_FightGroups("AffairOfHonor_Enemies", LAI_GROUP_PLAYER, true);
			
			DialogExit();
		break;
		// <-- Диалоги после боя.
		//=====================================================================================================================================
		// <-- Серия миниквестов "Дело чести".
		//=====================================================================================================================================
	}
}

void SetSeekCapCitizenParam(ref npchar, int iNation)
{
	//создаем кэпов
	int Rank = sti(pchar.rank)+5;
	if (Rank > 30) Rank = 30;
	ref sld = GetCharacter(NPC_GenerateCharacter("SeekCitizCap_"+npchar.index, "", "man", "man", Rank, iNation, -1, true, "soldier"));
	switch (npchar.quest.SeekCap)
	{
		case "NM_battle": 
			SetShipToFantom(sld, "pirate", true);
			sld.Ship.Mode = "trade";
			SetCaptanModelByEncType(sld, "trade");
			sld.dialog.currentnode = "NM_battleCap";
			sld.DeckDialogNode = "NM_battleDeck";
			npchar.quest.money = (10-sti(RealShips[sti(sld.Ship.Type)].Class))*8000+sti(pchar.rank)*500;
			npchar.quest.dublon = makeint(sti(npchar.quest.money)/100);
		break;
		
		case "NM_prisoner": 
			SetShipToFantom(sld, "pirate", true);
			sld.Ship.Mode = "trade";
			SetCaptanModelByEncType(sld, "trade");
			sld.dialog.currentnode = "NM_prisonerCap";
			sld.DeckDialogNode = "NM_prisonerCap";
			npchar.quest.money = (10-sti(RealShips[sti(sld.Ship.Type)].Class))*10000+sti(pchar.rank)*600;
			npchar.quest.dublon = makeint(sti(npchar.quest.money)/100);
		break;
		
		case "NM_peace": 
			SetShipToFantom(sld, "pirate", true);
			sld.Ship.Mode = "war";
			SetCaptanModelByEncType(sld, "war");
			sld.dialog.currentnode = "NM_peaceCap";
			sld.DeckDialogNode = "NM_peaceCap";
			npchar.quest.money = (10-sti(RealShips[sti(sld.Ship.Type)].Class))*6000+sti(pchar.rank)*400;
			npchar.quest.dublon = makeint(sti(npchar.quest.money)/100);
		break;
	
		case "manSlave": 
			SetShipToFantom(sld, "pirate", true);
			sld.Ship.Mode = "pirate";
			SetCaptanModelByEncType(sld, "pirate");
			sld.dialog.currentnode = "CitizCap";
			sld.DeckDialogNode = "CitizCap_inDeck";
			npchar.quest.money = (10-sti(RealShips[sti(sld.Ship.Type)].Class))*10000+(sti(pchar.rank)*500);
		break;
		
		case "manRapeWife": 
			SetShipToFantom(sld, "pirate", true);
			sld.Ship.Mode = "pirate";
			SetCaptanModelByEncType(sld, "pirate");
			sld.dialog.currentnode = "RapeWifeCap";
			sld.DeckDialogNode = "RapeWifeCap_inDeck";
			npchar.quest.money = (10-sti(RealShips[sti(sld.Ship.Type)].Class))*10000+(sti(pchar.rank)*500);
		break;
		
		case "manFriend": 
			SetShipToFantom(sld, "trade", true);
			sld.Ship.Mode = "trade";
			SetCaptanModelByEncType(sld, "trade");
			sld.dialog.currentnode = "FriendCap";
			sld.DeckDialogNode = "FriendCap_inDeck";
			npchar.quest.money = (10-sti(RealShips[sti(sld.Ship.Type)].Class))*10000+(sti(pchar.rank)*500);
		break;
		
		case "womanHasband": 
			SetShipToFantom(sld, "trade", true);
			sld.Ship.Mode = "trade";
			SetCaptanModelByEncType(sld, "trade");
			sld.dialog.currentnode = "HasbandCap";
			sld.DeckDialogNode = "HasbandCap_inDeck";
			npchar.quest.money = (10-sti(RealShips[sti(sld.Ship.Type)].Class))*10000+(sti(pchar.rank)*500);
		break;
		
		case "womanRevenge": 
			SetShipToFantom(sld, "pirate", true);
			sld.Ship.Mode = "pirate";
			SetCaptanModelByEncType(sld, "pirate");
			sld.dialog.currentnode = "RevengeCap";
			sld.DeckDialogNode = "RevengeCap_inDeck";
			npchar.quest.money = (10-sti(RealShips[sti(sld.Ship.Type)].Class))*10000+(sti(pchar.rank)*500);
		break;
		
		case "womanPirates": 
			SetShipToFantom(sld, "pirate", true);
			sld.Ship.Mode = "pirate";
			SetCaptanModelByEncType(sld, "pirate");
			sld.dialog.currentnode = "PiratesCap";
			sld.DeckDialogNode = "PiratesCap_inDeck";
			npchar.quest.money = (10-sti(RealShips[sti(sld.Ship.Type)].Class))*10000+(sti(pchar.rank)*500);
		break;
	}
	sld.dialog.filename = "Quest\ForAll_dialog.c";
	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	DeleteAttribute(sld, "AboardToFinalDeck");
	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "DontRansackCaptain");
	sld.AlwaysSandbankManeuver = true;
	sld.AnalizeShips = true;  //анализировать вражеские корабли при выборе таска
	sld.DontRansackCaptain = true; //не сдаваться
	SetCharacterPerk(sld, "FastReload");
	SetCharacterPerk(sld, "HullDamageUp");
	SetCharacterPerk(sld, "SailsDamageUp");
	SetCharacterPerk(sld, "CrewDamageUp");
	SetCharacterPerk(sld, "CriticalShoot");
	SetCharacterPerk(sld, "LongRangeShoot");
	SetCharacterPerk(sld, "CannonProfessional");
	SetCharacterPerk(sld, "ShipDefenseProfessional");
	SetCharacterPerk(sld, "ShipTurnRateUp");
	SetCharacterPerk(sld, "ShipTurnRateUp");
	SetCharacterPerk(sld, "StormProfessional");
	SetCharacterPerk(sld, "SwordplayProfessional");
	SetCharacterPerk(sld, "AdvancedDefense");
	SetCharacterPerk(sld, "CriticalHit");
	SetCharacterPerk(sld, "Sliding");
	SetCharacterPerk(sld, "Tireless");
	SetCharacterPerk(sld, "HardHitter");
	SetCharacterPerk(sld, "GunProfessional");
	//в морскую группу кэпа
	string sGroup = "SeekCapShip_" + sld.index;
	Group_FindOrCreateGroup(sGroup);
	Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
	Group_LockTask(sGroup);
	Group_AddCharacter(sGroup, sld.id);
	Group_SetGroupCommander(sGroup, sld.id);
	SetRandGeraldSail(sld, sti(sld.Nation)); 
	//записываем данные в структуры портмана и кэпа
	npchar.quest.SeekCap.capId = sld.id //Id искомого кэпа
	npchar.quest.SeekCap.capName = GetFullName(sld); //имя искомого кэпа
	npchar.quest.SeekCap.shipName = sld.Ship.name; //имя украденного корабля
	npchar.quest.SeekCap.shipTapeName = RealShips[sti(sld.Ship.Type)].BaseName; //название украденного корабля
	//npchar.quest.money = ((sti(RealShips[sti(sld.Ship.Type)].basetype)+1)*1000)+(sti(pchar.rank)*500); //вознаграждение
	sld.quest = "InMap"; //личный флаг искомого кэпа
	sld.quest.SeekCap = npchar.quest.SeekCap; //запишем кэпу флаг квеста
	sld.quest.nation = iNation; //запомним базовую нацию кэпа
	sld.city = SelectAnyColony(npchar.city); //определим колонию, откуда кэп-вор выйдет
	sld.quest.targetCity = SelectAnyColony2(npchar.city, sld.city); //определим колонию, куда он придёт
	//Log_TestInfo("Разыскиваемый кэп " + sld.id + " вышел из: " + sld.city + " и направился в: " + sld.quest.targetCity);
	sld.quest.cribCity = npchar.city; //город, где ошивается квестодатель
	npchar.quest.Qcity = sld.city;
	//==> на карту
	sld.mapEnc.type = "trade";
	//выбор типа кораблика на карте
	switch (npchar.quest.SeekCap)
	{
		case "NM_battle":	 sld.mapEnc.worldMapShip = "Galleon_red"; break;
		case "NM_prisoner":	 sld.mapEnc.worldMapShip = "Galleon_red"; break;
		case "NM_peace":	 sld.mapEnc.worldMapShip = "ranger";	  break;
		case "manSlave":	 sld.mapEnc.worldMapShip = "Galleon_red"; break;
		case "manRapeWife":	 sld.mapEnc.worldMapShip = "Galleon_red"; break;
		case "manFriend":	 sld.mapEnc.worldMapShip = "ranger";	  break;
		case "womanHasband": sld.mapEnc.worldMapShip = "ranger";	  break;
		case "womanRevenge": sld.mapEnc.worldMapShip = "Galleon_red"; break;
		case "womanPirates": sld.mapEnc.worldMapShip = "Galleon_red"; break;
	}
	sld.mapEnc.Name = XI_ConvertString(npchar.quest.SeekCap.shipTapeName) + " '" + npchar.quest.SeekCap.shipName + "'";
	int daysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(sld.quest.targetCity), GetArealByCityName(sld.city))+5; //дней доехать даем с запасом
	Map_CreateTrader(sld.city, sld.quest.targetCity, sld.id, daysQty);
	//прерывание на смерть кэпа
	string sTemp = "SCQ_" + sld.index;
	pchar.quest.(sTemp).win_condition.l1 = "NPC_Death";
	pchar.quest.(sTemp).win_condition.l1.character = sld.id;
	pchar.quest.(sTemp).function = "SCQ_seekCapIsDeath";
	pchar.quest.(sTemp).CapId = sld.id;
	//прерывание на смерть квестодателя
	sTemp = "SCQ_" + npchar.index;
	pchar.quest.(sTemp).win_condition.l1 = "NPC_Death";
	pchar.quest.(sTemp).win_condition.l1.character = npchar.id;
	pchar.quest.(sTemp).function = "SCQ_CitizenIsDeath";
	pchar.quest.(sTemp).CapId = sld.id;
	pchar.quest.(sTemp).CitizenId = npchar.id;
	//заносим Id кэпа в базу нпс-кэпов
	sTemp = sld.id;
	NullCharacter.capitainBase.(sTemp).quest = "citizen"; //идентификатор квеста
	NullCharacter.capitainBase.(sTemp).questGiver = npchar.id; //запомним Id квестодателя для затирки в случае чего
	NullCharacter.capitainBase.(sTemp).Tilte1 = sld.quest.cribCity + "SCQ_" + npchar.quest.SeekCap; //заголовок квестбука
	NullCharacter.capitainBase.(sTemp).Tilte2 = "SCQ_" + npchar.quest.SeekCap; //имя квеста в квестбуке
	NullCharacter.capitainBase.(sTemp).checkTime = daysQty + 5;
    NullCharacter.capitainBase.(sTemp).checkTime.control_day = GetDataDay();
    NullCharacter.capitainBase.(sTemp).checkTime.control_month = GetDataMonth();
    NullCharacter.capitainBase.(sTemp).checkTime.control_year = GetDataYear();
}

string SelectNB_battleText()
{
	string sText;
	switch (hrand(5))
	{
		case 0: sText = "One bastard has seduced my sister because of her naivety and then left her once he had his way with her. I couldn't let him get away unpunished and so I challenged him. He got frightened and run away on his ship" break;
		case 1: sText = "One dishonourable bastard has lost a huge sum to me in gambling and has run away on his ship" break;
		case 2: sText = "One scoundrel has loaned money from me, and when I wasn't at home he has repaid the debt with false coins to my servant. Now he is hiding somewhere on his ship" break;
		case 3: sText = "One scoundrel has tried to dishonour me in the eyes of our governor but his lie was revealed and this bastard had run away on his ship " break;
		case 4: sText = "It was my mistake, I have hired some rogue as an accountant. He has committed a great peculation, bought a ship and run away " break;
		case 5: sText = "My ex-guard has stolen a box filled with jewels from my wife's boudoir and run away. Now I see where has he got enough coins to buy a ship " break;
	}
	return sText;
}

void SelectNB_prisonerText(ref npchar)
{
	switch (hrand(5))
	{
		case 0:
			npchar.quest.text = "One bastard has seduced my sister because of her naivety and then left her once he had his way with her. I couldn't let him get away unpunished and so I challenged him. But he got hired as a ship master and sailed away";
			npchar.quest.text1 = " dishonoured a woman and cowardly run away";
		break;
		case 1:
			npchar.quest.text = "One dishonourable bastard had lost a huge sum to me in gambling but he didn't pay me yet, I heard that he got hired as a cannoneer and run away";
			npchar.quest.text1 = "lost all his money in gambling and didn't want to repay the debit ";
		break;
		case 2:
			npchar.quest.text = "One scoundrel has loaned money from me, and when I wasn't at home he had repaid the debt with false coins to my servant. Now he is serving on one ship as quartermaster and hiding from me ";
			npchar.quest.text1 = "counterfeiter who has committed a crime";
		break;
		case 3:
			npchar.quest.text = "One scoundrel has tried to dishonour me in the eyes of our governor but his lie was revealed. Luckily for him bastard got hired as a doctor on one ship and run away";
			npchar.quest.text1 = "slanderer and intrigant who has tried to dishonour one good citizen";
		break;
		case 4:
			npchar.quest.text = "It was my mistake, I have hired some rogue as an accountant. He had committed a great peculation and now he is serving on one ship as quartermaster and hiding from me";
			npchar.quest.text1 = "is blamed in peculation and misappropriation";
		break;
		case 5:
			npchar.quest.text = "My ex-guard stole a box filled with jewels from my wife's boudoir and run away. He got hired as an officer for the boarding party on one ship";
			npchar.quest.text1 = "a common thief and his place is in jail. He has stolen jewels from his own employer";
		break;
	}
}

void SelectNB_peaceText(ref npchar)
{
	switch (hrand(5))
	{
		case 0: 
			npchar.quest.text = "my old pal, who was my close friend in the Old World";
			npchar.quest.text1 = "he is your old friend";
		break;
		case 1:
			npchar.quest.text = "a man, who basically was my father";
			npchar.quest.text1 = "you were like a father for him";
		break;
		case 2:
			npchar.quest.text = "my stepbrother, who had left the old world in his youth";
			npchar.quest.text1 = "you are his stepbrother";
		break;
		case 3:
			npchar.quest.text = "a man who really helped me in the Old World";
			npchar.quest.text1 = "you have helped him a lot";
		break;
		case 4:
			npchar.quest.text = "my sister's husband who was my friend in the Old World";
			npchar.quest.text1 = "you are his sister's husband";
		break;
		case 5:
			npchar.quest.text = "my friend, my brother in arms in the Old World";
			npchar.quest.text1 = "you were brothers in arms";
		break;
	}
}
