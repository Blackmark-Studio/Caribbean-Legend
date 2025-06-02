// Захария Марлоу, Чёрный Пастор, Пуэрто-Принсипе, Куба
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
    } //<-- блок angry

	switch(Dialog.CurrentNode)
	{
		case "First time":
            dialog.text = NPCStringReactionRepeat("Hai qualche affare con me? Se non ne hai, allora vattene da qui!","Credo di essermi spiegato chiaramente.","Nonostante mi sia espresso chiaramente, continui a infastidirmi!","Bene, sto stancando di questa maleducanza.","ripeti",3,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Me ne sto già andando.","Certo, Pastore.","Mi dispiace, Pastore.","Ops...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			
			if (sti(pchar.GenQuest.Piratekill) > 20)
			{
				dialog.text = RandPhraseSimple("Sei pazzo? Volevi fare il macellaio? Tutti i pirati sono arrabbiati con te, ragazzo, sarebbe meglio che tu lasciassi questo posto.","Sembra che tu sia impazzito, ragazzo. Volevi allungare un po' le mani? Senza offesa, ma non hai nulla da fare qui. Sparisci!");
				link.l1 = RandPhraseSimple("Ascolta, voglio risolvere la situazione...","Aiutami a risolvere questo problema...");
				link.l1.go = "pirate_town";
				break;
			}
			
			//--> Сага
			if(CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && !CheckAttribute(npchar, "quest.sharkbegin"))
			{
				link.l1 = "Sto cercando Shark Dodson. Dicono che tu sei l'ultimo uomo che l'ha visto. Puoi aiutarmi con questo?";
				link.l1.go = "Shark";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.BarbTemptation") && pchar.questTemp.Saga.BarbTemptation == "terrax" && CheckCharacterItem(pchar, "witches_hammer"))
			{
				link.l1 = "Perché sei così scortese? O non sei interessato a ottenere il tuo libro desiderato da me?";
				link.l1.go = "book";
			}
			//<-- Сага
			//поручение капитана - выкуп
			if (CheckAttribute(pchar, "GenQuest.CaptainComission") && NPChar.city == pchar.GenQuest.CaptainComission.PiratesCity)
			{
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.toMayor"))
				{
					link.l1 = "Voglio parlare del tuo prigioniero.";
					link.l1.go = "CapComission1";
					DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
				}	
				if (pchar.GenQuest.CaptainComission.PirateShips == "died" || pchar.GenQuest.CaptainComission.PirateShips == "goaway") // лесник. новая проверка. искл. возможность сразу сдать задание,минуя 15 дней.
				{
					link.l1 = "Ciao, Pastore. Voglio parlare della tua missione.";
					link.l1.go = "CapComission3";
				}
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.RepeatSpeak") && !CheckAttribute(pchar,"GenQuest.CaptainComission.vikupzaplatil")) 
				{ // лесник . второй диалог с проверкой ,если ГГ ещё не принес деньги за выкуп.
					link.l1 = "Voglio parlare del tuo prigioniero.";
					link.l1.go = "CapComission6";
				}
			}
		break;
		
		case "shark":
			dialog.text = "Steven Dodson? Non so come la mia storia possa aiutarti perché Shark è scomparso negli ultimi mesi e nessuno lo ha visto. Non è una sorpresa però, ha ucciso Blaze Sharp e ha disonorato il suo stesso nome con questa azione sciocca. Ha fatto di alcuni potenti corsari i suoi nemici.";
			link.l1 = "Ho tutte le ragioni per pensare che Shark sia innocente della morte di Sharp. Non posso provarlo, forse Shark può farlo da solo. Hai intenzione di dirmi qualcosa su di lui?";
			link.l1.go = "shark_1";
		break;
		
		case "shark_1":
			dialog.text = "Qualche mese fa, Steven si è avvicinato a me e ha proposto un affare molto strano: ha lasciato la sua fregata 'Fortuna' in pegno per un mese in cambio di una brigata completamente carica di provviste. Poi mi restituisce la brigata e i soldi per le provviste o tengo la sua fregata. Un mese è passato - nessun segno né di Shark, né della mia brigata, né dei soldi.\nInoltre, ho sentito voci che Blaze era stato ucciso e Shark era il sospettato. Cosa potevo pensare? Corretto! Ho pensato che Steven fosse scappato dal peggio. Ho venduto la sua fregata a un certo inglese di nome William Patterson, era molto contento e ha pagato un bel mucchio di dobloni per la nave.\nQuindi, ho completamente compensato le mie spese e non ho rancore nei suoi confronti. Non mi interessa della morte di Sharp, ho i miei problemi di cui preoccuparmi.";
			link.l1 = "Non pensi che se volesse scappare non avrebbe bisogno della tua brigata? Aveva la sua nave, cento volte migliore di qualsiasi brigata. Sembra che Shark avesse un piano, ma qualcosa è andato storto e non è tornato in tempo.";
			link.l1.go = "shark_2";
		break;
		
		case "shark_2":
			dialog.text = "Come ti ho già detto, non me ne frega niente dei problemi di Dodson. Ho adempiuto alla mia parte del patto. Riguardo alla nave, faresti meglio a chiedergli perché gli serviva quella dannata brigantina. Non l'ho costretto a prenderla.";
			link.l1 = "Bene, non parliamone più. Hai ragione, ovviamente. Dimmi, sai dove stava andando Steven sulla tua brigata?";
			link.l1.go = "shark_3";
		break;
		
		case "shark_3":
			dialog.text = "Chi può dirlo con certezza. Ma ho qualche ipotesi. Ha navigato verso Nord Ovest in direzione del Maine. Quindi è o la Baia del Pericolo, nota per i suoi Indiani ostili, o la Nuova Spagna, nota per i suoi Papisti e l'Inquisizione.\nDubito che avrebbe navigato verso uno di questi luoghi. Ma dicono che c'è un posto strano chiamato 'Città delle Navi Abbandonate' situato a Nord Ovest di Cuba. Molte persone considerano questo un mito, ma non io. Non perché sono una persona così romantica, ma perché ci sono veri uomini che ci navigano con le loro lunghe navi. Almeno usavano farlo.";
			link.l1 = "E chi sono loro?";
			link.l1.go = "shark_4";
		break;
		
		case "shark_4":
			dialog.text = "Corsari di Cuba. Caricavano le loro barcasse con carcasse di toro e navigavano verso nord ovest. Sono sempre tornati un po' dopo con le tasche piene di soldi o con merci rare e preziose.";
			link.l1 = "Intrigante! Dove posso trovare quei bucanieri?";
			link.l1.go = "shark_5";
		break;
		
		case "shark_5":
			dialog.text = "Perché mi stai chiedendo? Cerca nei boschi di Cuba. Anche se li trovi, non ti diranno nulla, perché dovrebbero rivelare la fonte del loro buon vivere? Quindi non perdere tempo, nessuno li ha visti farlo di nuovo da molto tempo.\nInoltre, ho sentito parlare di alcune note scritte dal marinaio spagnolo Alvarado che ha visitato l'isola di persona. Quindi sono curioso, forse Steven ha navigato lì dopo tutto.";
			link.l1 = "L'isola sconosciuta che non è sulle mappe... Beh. Questa non è un'informazione promettente.";
			link.l1.go = "shark_6";
		break;
		
		case "shark_6":
			dialog.text = "Ti ho detto fin dall'inizio che la mia storia non ti avrebbe aiutato. E perché hai bisogno di Dodson?";
			link.l1 = "Io e il Diavolo della Foresta vogliamo eleggerlo come leader dei Fratelli della Costa. Come ti ho già detto, ci sono alcune ragioni serie per suggerire che Blaze è stato assassinato da qualcun altro.";
			link.l1.go = "shark_7";
		break;
		
		case "shark_7":
			dialog.text = "Eh! Immagino che Jan lo stia rappresentando? Beh, conosci la legge - Dodson dovrà ottenere un voto da ogni barone.";
			link.l1 = "Conosco la legge. Allora la mia seconda domanda. Voterai per Dodson alle elezioni?";
			link.l1.go = "shark_8";
		break;
		
		case "shark_8":
			dialog.text = "Beh, dovrebbe tornare prima lui. In realtà, non mi importa chi guiderà i Fratelli, purché faccia bene il suo lavoro e non mi infastidisca. Come ho detto, ho problemi miei. Sai quanti stregoni e maghi ci sono sulla nostra isola? No? Te lo dirò: una legione! Inoltre, ci sono anche molti papisti a Santiago e all'Havana.\nParlando di maghi. C'è un libro chiamato 'Martello per le Streghe'. Vorrei davvero averlo, ma solo in inglese, non ho bisogno di traduzioni in latino, tedesco o spagnolo, non conosco queste lingue. Portami il libro e voterò per Dodson.\nSappi che anche Jackman mi ha promesso di trovarlo, quindi se lui ha successo prima... non incolparmi poi.";
			link.l1 = "Bene, lo prenderò in considerazione. Grazie per il tuo tempo. Ci vediamo.";
			link.l1.go = "shark_9";
		break;
		
		case "shark_9":
			DialogExit();
			pchar.questTemp.Saga.SharkHunt = "after_marlow";
			npchar.quest.sharkbegin = "true";
			AddQuestRecord("SharkHunt", "2");
		break;
		
		case "book":
			dialog.text = "Il libro? Presumo che tu stia parlando del 'Martello per le Streghe'?";
			link.l1 = "Certo. Sono riuscito a trovarlo per te. È in inglese come hai chiesto.";
			link.l1.go = "book_1";
		break;
		
		case "book_1":
			dialog.text = "Ah, scusa per un'accoglienza così brusca, compagno. Non succederà di nuovo... Fammi vedere quella meraviglia!";
			link.l1 = "Certo, dai un'occhiata.";
			link.l1.go = "book_2";
		break;
		
		case "book_2":
			RemoveItems(pchar, "witches_hammer", 1); // удалить трактат
			dialog.text = "Finalmente! Tremate ora, servi dell'Inferno! Non vi lascerò in pace finché la mia mano sarà in grado di colpire...";
			link.l1 = "Sono felice per te, Pastore. Quindi, cosa ne pensi del tuo voto?";
			link.l1.go = "book_3";
		break;
		
		case "book_3":
			dialog.text = "Come ti ho detto 'non mi importa di chi diventerà il capo'. Sono sicuro che Svenson non sceglierà un uomo indegno. Quindi prendi il mio voto. Fai quello che vuoi con esso. Ecco il mio frammento.";
			link.l1 = "Grazie, Zaccaria. Ci vediamo lì!";
			link.l1.go = "book_4";
		break;
		
		case "book_4":
			GiveItem2Character(pchar, "splinter_zm"); // дать осколок
			DialogExit();
			NextDiag.CurrentNode = "I_know_you_good";
			AddQuestRecord("BarbTemptation", "27");
			if (CheckCharacterItem(pchar, "splinter_mt") && CheckCharacterItem(pchar, "splinter_jb") && CheckCharacterItem(pchar, "splinter_zm")) Saga_GiveCalendar();
			ChangeCharacterComplexReputation(pchar, "fame", 1);
		break;

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

        case "I_know_you_good":
            dialog.text = NPCStringReactionRepeat(GetFullName(pchar)+", Sono lieto di vederti! Cosa vuoi?","Cosa altro vuoi?","Di nuovo? Non disturbare la gente se non hai nulla da fare!","Sei un "+GetSexPhrase("bravo corsaro","brava ragazza")+", quindi puoi vivere per ora. Ma non voglio più parlarti.","ripeti",10,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Sono solo di passaggio.","Niente...","Bene, Pastore, mi dispiace...","Maledizione, colpa mia!",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";
			
			if (sti(pchar.GenQuest.Piratekill) > 20)
			{
				dialog.text = RandPhraseSimple("Sei pazzo? Volevi fare il macellaio? Tutti i pirati sono arrabbiati con te, ragazzo, quindi sarebbe meglio per te lasciare questo posto...","Sembra che tu sia impazzito, ragazzo. Volevi allungare un po' le mani? Senza offesa, ma non hai nulla da fare qui. Sparisci!");
				link.l1 = RandPhraseSimple("Ascolta, voglio risolvere la situazione...","Aiutami a risolvere questo problema...");
				link.l1.go = "pirate_town";
				break;
			}
			//поручение капитана - выкуп
			if (CheckAttribute(pchar, "GenQuest.CaptainComission") && CheckAttribute(pchar,"GenQuest.CaptainComission.toMayor"))
			{
				link.l1 = "Si tratta del tuo prigioniero.";
				link.l1.go = "CapComission1";
				DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
			}		
			if (CheckAttribute(pchar, "GenQuest.CaptainComission") && CheckAttribute(pchar,"GenQuest.CaptainComission.toMayor"))
			{
				link.l1 = "Si tratta del tuo prigioniero.";
				link.l1.go = "CapComission1";
				DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
			}	
			if (pchar.GenQuest.CaptainComission.PirateShips == "died" || pchar.GenQuest.CaptainComission.PirateShips == "goaway")//  правка лесник,новая проверка ,исключающая тут же сдачу задания
			{
				link.l1 = "Salve, Pastore, sono qui per la vostra missione.";
				link.l1.go = "CapComission3";
			}
			if (CheckAttribute(pchar, "GenQuest.Marginpassenger") && pchar.GenQuest.Marginpassenger == "cabin" && CheckAttribute(pchar, "questTemp.LongHappy"))
			{ // лесник . похититель  ( после ДЛС ДиС ,когда барбазона уже нет)
				link.l1 = "Ho sentito dire che sei coinvolto in affari legati ai prigionieri...";
				link.l1.go = "Marginpassenger";
			}
		break;
		
	//-----------------------------------Поручение капитана - Выкуп-------------------------------------------------
		case "CapComission1":
			dialog.text = "Ha-ha. Pensi che abbia solo un prigioniero qui? Nominalo.";
			link.l1 = pchar.GenQuest.CaptainComission.SlaveName+". È qui?";
			link.l1.go = "CapComission2";
			DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
		break;

		case "CapComission2":
			if(CheckAttribute(pchar,"GenQuest.CaptainComission.DaysLeft"))
			{
				dialog.text = "Era. L'ho venduto a quel proprietario di piantagione di Barbados - colonnello Bishop, quando era qui una settimana fa.";
				link.l1 = "Maledizione...";
				link.l1.go = "CapComission2_1";
			}
			else
			{
				dialog.text = "Ah, finalmente. Stavo pensando di venderlo a quel proprietario di piantagioni da Barbados, sarà qui tra una settimana o due... Hai un riscatto?";
				link.l1 = "Guarda, c'è un piccolo problema... In realtà, non ho molti soldi. Ma sono pronto a lavorare.";
				link.l1.go = "CapComission2_2";
				if(makeint(pchar.money) > 150000)
				{
					link.l2 = "È bene che non l'abbia venduto. Ecco le tue monete - 150.000 pesos. Dove posso prenderlo?"link.l2.go ="CapComission2_3";
				}	
			}
		break;
		
		case "CapComission2_1":
			dialog.text = "Sei stato troppo lento... E perché ti importa di lui? Ho trattato solo con i suoi parenti.";
			link.l1 = "Hanno chiesto a me di venire qui.";
			link.l1.go = "CapComission2_11";
		break;
		
		case "CapComission2_11":
			dialog.text = "Beh, sei in ritardo. Non posso fare nulla.";
			link.l1 = "Ascolta, per quanto l'hai venduto se non è un segreto?"; 
			link.l1.go = "CapComission2_12";
		break;
		
		case "CapComission2_12":
			dialog.text = "Eh, non lo è. Ma non te lo dirò... riderai se lo faccio. Ah-ah-ah-ah! Addio.";
			link.l1 = "Ci vediamo.";
			link.l1.go = "exit";
			AddQuestRecord("CaptainComission1", "10");
			AddQuestUserData("CaptainComission1", "sName", "Zachary Marlow");//правка лесник.  в СЖ запись ниже не работает																																				  
			//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));																															 
			CaptainComission_GenerateManager();
		break;
		
		case "CapComission2_2":
			if(rand(3) == 1)
			{
				dialog.text = "Bene, "+pchar.name+", sai, non funziona così. Torna con i soldi e avrai il tuo debole, ah-ah.";
				link.l1 = "Bene. Ci vediamo.";
				link.l1.go = "CapComission2_4";
			}
			else
			{
				dialog.text = "Beh, beh.. Ho un affare... Non so nemmeno da dove iniziare. Ho bisogno di affondare un pirata che ha superato il limite.";
				link.l1 = "Non può semplicemente essere ucciso nella giungla?";
				link.l1.go = "CapComission2_2_1";
			}
		break;

		case "CapComission2_2_1":
			dialog.text = "Non è così che funzionano gli affari, lo sai... Non ho bisogno della sua morte, devo insegnare ad alcuni di evitare di prendere la mia parte di bottino. Ma non rimpiangerò la sua morte.";
			link.l1 = "Perché non mandi la tua gente a prenderlo?";
			link.l1.go = "CapComission2_2_2";
		break;
		
		case "CapComission2_2_2":
			CaptainComission_GetRandomShore();
			pchar.GenQuest.CaptainComission.ShipName1 = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.GenQuest.CaptainComission.ShipName2 = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.GenQuest.CaptainComission.UnknownPirateName = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);
			sLoc = XI_ConvertString(pchar.GenQuest.CaptainComission.Island + "Dat"); // belamour gen
			dialog.text = "Mh... Beh, "+GetName(NAMETYPE_ORIG,pchar.GenQuest.CaptainComission.UnknownPirateName,NAME_NOM)+" ha convinto alcuni pirati che la loro parte di bottino è tenuta nel nostro nascondiglio non lontano da "+XI_ConvertString(pchar.GenQuest.CaptainComission.Island.Shore+"Gen")+". Le loro due navi '"+pchar.GenQuest.CaptainComission.ShipName1+"' e '"+pchar.GenQuest.CaptainComission.ShipName2+"' ha levato l'ancora poco tempo fa e ha navigato verso "+sLoc+". Ora capisci perché non posso fidarmi dei miei uomini per fare quel lavoro?";
			link.l1 = "Lo faccio. Quanto tempo ho?";
			link.l1.go = "CapComission2_2_3";
		break;
		
		case "CapComission2_2_3":
			dialog.text = "Da 12 a 15 giorni, non di più, è importante per me se non arriveranno al nascondiglio, o sarà un nonsenso affondarli con un carico prezioso. In quel caso, sarebbe meglio se lo portassero qui...";
			link.l1 = "Bene, ci sono. Cercherò di prenderli.";
			link.l1.go = "CapComission2_2_4";
		break;
		
		case "CapComission2_2_4":
			AddQuestRecord("CaptainComission1", "24");
			AddQuestUserData("CaptainComission1", "sName", "Zachary Marlow");//правка																			   
			//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			AddQuestUserData("CaptainComission1", "sShipName1", pchar.GenQuest.CaptainComission.ShipName1);
			AddQuestUserData("CaptainComission1", "sShipName2", pchar.GenQuest.CaptainComission.ShipName2);
			AddQuestUserData("CaptainComission1", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.Island.Shore + "Dat")); // belamour gen
			AddQuestUserData("CaptainComission1", "sShoreType", XI_ConvertString(GetIslandByArealName(pchar.GenQuest.CaptainComission.Island) + "Voc")); // belamour gen
			pchar.quest.CapComission_PirateAttack.win_condition.l1 = "location";
            pchar.quest.CapComission_PirateAttack.win_condition.l1.location = pchar.GenQuest.CaptainComission.Island;
            pchar.quest.CapComission_PirateAttack.function = "CaptainComission_GeneratePirateShips"; 
			SetFunctionTimerCondition("CaptainComission_PirateShipsOver", 0, 0, 15, false);
			//pchar.GenQuest.CaptainComission.PirateShips = "sdatkwest";	// лесник - заменил проверку для сдачи сразу.
			DialogExit();
		break;
		
		case "CapComission2_3":
			dialog.text = "Non preoccuparti. I miei uomini lo consegneranno alla tua nave. E perché ti importa di lui?";
			link.l1 = "Non lo faccio. I suoi parenti mi hanno chiesto di consegnarglielo.";
			link.l1.go = "CapComission2_31";
		break;
		
		case "CapComission2_31":
			dialog.text = "Ah, perfetto. Quasi mi dispiaceva per aver dato un prezzo così basso per il tuo uomo. Ha-ha-ha-ha. Addio.";
			link.l1 = "Arrivederci.";
			link.l1.go = "CapComission2_32";
		break;
		
		case "CapComission2_32":
			AddQuestRecord("CaptainComission1", "9");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));	// belamour gen	
			addMoneyToCharacter(pchar, -150000);
			pchar.GenQuest.CaptainComission.vikupzaplatil = true; // новая проверка ,если шарль заплатил выкуп за пленника. лесник																																																			
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");	
		break;
		
		case "CapComission2_4":
			if(!CheckAttribute(pchar,"GenQuest.CaptainComission.RepeatSpeak"))
			{
				AddQuestRecord("CaptainComission1", "31");
				AddQuestUserData("CaptainComission1", "sName", "Zachary Marlow");		// лесник																											 
				//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));// в СЖ не работает
			}	
			pchar.GenQuest.CaptainComission.RepeatSpeak = true;		
			DialogExit();
		break;
		
		case "CapComission3":
			dialog.text = "Allora, , "+GetFullName(pchar)+", hai affondato i miei amici? He-he-he...";
			if(pchar.GenQuest.CaptainComission.PirateShips == "goaway")
			{
				link.l1 = "No. Non sono riuscito a prenderli. E non li ho incontrati al ritorno.";
				link.l1.go = "CapComission4";
			}
			if(pchar.GenQuest.CaptainComission.PirateShips == "died")	
			{
				link.l1 = "L'ho fatto. Li ho mandati a nutrire gli squali.";
				link.l1.go = "CapComission5";
			}
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
		break;
		
		case "CapComission4":
			dialog.text = "Maledizione! Che tu li abbia incontrati o no, ora non importa! E quale sarà il tuo prossimo suggerimento?";
			link.l1 = "Forse hai un lavoro più facile per me?";
			link.l1.go = "CapComission4_1";
			link.l2 = "Ascolta, "+NPChar.name+", abbassa il prezzo per il prigioniero...";
			link.l2.go = "CapComission4_2";
		break;
		
		case "CapComission4_1":
			dialog.text = "No.";
			link.l1 = "Allora addio...";
			link.l1.go = "CapComission4_3";
		break;
		
		case "CapComission4_2":
			dialog.text = "Abbassare il prezzo?! Ho appena perso la mia roba a causa della tua incompetenza! E ora potrei alzare il prezzo! Puoi prenderlo per 200.000 pesos se vuoi, oppure puoi andartene all'inferno da qui.";
			link.l1 = "È troppo costoso... Addio...";
			link.l1.go = "CapComission4_4";
			if(sti(pchar.money) >= 200000)
			{
				link.l2 = "Maledizione, prendi le tue monete.";
				link.l2.go = "CapComission4_5";
			}	
		break;
		
		case "CapComission4_3":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			AddQuestRecord("CaptainComission1", "27");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", "Marlow");		// лесник																								   
			//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_DAT));
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			DialogExit();
		break;
		
		case "CapComission4_4":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			AddQuestRecord("CaptainComission1", "28");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", "Marlow"); // правка	// лесник																											 
			//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			DialogExit();		
		break;
		
		case "CapComission4_5":
			dialog.text = "Potete prendervi questo debole...";
			link.l1 = "Addio.";
			link.l1.go = "CapComission4_6";
		break;
		
		case "CapComission4_6":
			addMoneyToCharacter(pchar, -200000);
			AddQuestRecord("CaptainComission1", "29");
			AddQuestUserData("CaptainComission1", "sName", "Marlow"); // правки имени в сж лесник																										  
			AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));// в сж не работает
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			pchar.GenQuest.CaptainComission.SlaveAddMoney = true;
			DialogExit();	
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");	
		break;
		
		case "CapComission5":
			dialog.text = "Oho! Ben fatto! Prendi il tuo debole e buona fortuna.";
			link.l1 = "Grazie. Addio.";
			link.l1.go = "CapComission5_1";
		break;
		
		case "CapComission5_1":
			AddQuestRecord("CaptainComission1", "34");
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			DialogExit();		
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");	
		break;
		
			/*case "CapComission6":    // ЕСЛИ В ПЕРВЫЙ РАЗ ОТКАЗАЛ В ЗАДАНИИ ,ТО ПУСТЬ БАБКИ ИЩЕТ
		     ИНАЧЕ ПОВТОРНАЯ ДАЧА ЗАДАНИЯ ПРЕВРАЩАЕТ КВЕСТ В КАШУ.. лесник
			dialog.text = "Hai portato il riscatto"+GetSexPhrase("","ла")+"? Non stavo scherzando quando ho detto che l'avrei venduto ai piantatori.";			
			link.l1 = "Ascolta, "+NPChar.name+", c'è una cosa... In breve, non ho così tanti soldi. Ma sono pronto"+GetSexPhrase("","а")+" lavorare.";
			link.l1.go = "CapComission2_2";
			if(makeint(pchar.money) > 150000)
			{
				link.l2 = "È bene che tu non l'abbia venduto. Ecco le tue monete - 150000 pesos. Dove posso prenderlo?"link.l2.go ="CapComission2_3";
			}			
		break;*/
		  case "CapComission6":                        // лесник . пусть шарль бабло ищет,или забить на пленника.
			dialog.text = "Hai portato i soldi? Non scherzavo vendendo quell'uomo alla piantagione.";			
			link.l1 = "Non ho i soldi, "+NPChar.name+", ma ci sto lavorando.";
			link.l1.go = "exit";
			if(makeint(pchar.money) > 150000)
			{
				link.l2 = "È bene che non lo hai venduto. Ecco le tue monete - 150.000 pesos. Dove posso prenderlo?"link.l2.go ="CapComission2_3";
			}			
		break;

																																				 																																													  																																															
//--------------------------------------------Похититель------------------------------------------------------
		case "Marginpassenger":
			dialog.text = "E perché ti importa di quello che faccio? Sai, faresti meglio ad andartene...";
			link.l1 = "Tshh, calmati. Ho un affare con te. Riguarda il tuo prigioniero.";
			link.l1.go = "Marginpassenger_1";
		break;
		
		case "Marginpassenger_1":
			dialog.text = "Ah, va bene. Chi vuoi riscattare?";
			link.l1 = "Aspetta. Non sono qui per comprare, sono qui per offrirti di comprare un prigioniero. Beh, e avrai l'opportunità di ottenere un riscatto per lui.";
			link.l1.go = "Marginpassenger_2";
		break;
		
		case "Marginpassenger_2":
			dialog.text = "Hm. E perché hai bisogno della mia agenzia? Perché non vuoi ottenere soldi direttamente per te stesso?";
			link.l1 = "È piuttosto rischioso per me. Potrei avere problemi con le autorità.";
			link.l1.go = "Marginpassenger_3";
		break;
		
		case "Marginpassenger_3":
			dialog.text = "Ah-ah... va bene allora. Diamo un'occhiata. Chi è il tuo prigioniero?";
			link.l1 = "Questo è "+pchar.GenQuest.Marginpassenger.Text+" "+XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.City+"Gen")+".";
			link.l1.go = "Marginpassenger_4";
		break;
		
		case "Marginpassenger_4":
			int iTemp = makeint(sti(pchar.GenQuest.Marginpassenger.Dublon)*2*stf(pchar.GenQuest.Marginpassenger.Chance))*100;
			dialog.text = "Capisco... sarebbe un bel commercio se non stai mentendo. Suppongo che potrei pagarti per quest'uomo "+iTemp+" pesos o dai qualche informazione interessante invece. È la tua scelta.";
			link.l1 = "È meglio che prenda i pesos. Ne ho avuto abbastanza di questo affare...";
			link.l1.go = "Marginpassenger_money";
			link.l2 = "Ah! Raccontami di più. Sono certo che mi dirai qualcosa di interessante.";
			link.l2.go = "Marginpassenger_offer";
		break;
		
		case "Marginpassenger_money":
			dialog.text = "Allora, soldi. Prendili. Ora, non è più il tuo problema. Porta l'oggetto della vendita qui.";
			link.l1 = "Dovrebbe essere già vicino alle porte della città. Grazie! Mi hai davvero aiutato.";
			link.l1.go = "Marginpassenger_money_1";
		break;
		
		case "Marginpassenger_money_1":
			iTemp = makeint(sti(pchar.GenQuest.Marginpassenger.Dublon)*2*stf(pchar.GenQuest.Marginpassenger.Chance))*100;
			dialog.text = "Prego, portami di più... Ci vediamo!";
			link.l1 = "Buona fortuna...";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, iTemp);
			sld = characterFromId("MarginPass");
			RemovePassenger(Pchar, sld);
			sld.lifeday = 0;
			AddQuestRecord("Marginpassenger", "12");
			AddQuestUserData("Marginpassenger", "sSum", iTemp);
			CloseQuestHeader("Marginpassenger");
			DeleteAttribute(Pchar, "GenQuest.Marginpassenger");
		break;
		
		case "Marginpassenger_offer":
			pchar.GenQuest.Marginpassenger.Goods = GOOD_EBONY + rand(makeint(GOOD_MAHOGANY - GOOD_EBONY));
			pchar.GenQuest.Marginpassenger.GoodsQty = 200+rand(10)*10;
			switch (hrand(1))
			{
				case 0: //бухта на южном мейне
					SelectSouthshore();
					while (!isLocationFreeForQuests(pchar.GenQuest.Marginpassenger.Shore)) SelectSouthshore();
					dialog.text = "È bello fare affari con un uomo intelligente. Ora ascolta: tra pochi giorni "+XI_ConvertString(pchar.GenQuest.Marginpassenger.Shore+"Quel")+" arriverà una spedizione spagnola dal continente, carica di merci preziose. Aspetteranno una nave che dovrebbe prendere il carico. Se arrivi lì in una settimana, avrai la possibilità di prendere il carico per te stesso.\nSe fossi in te, sarei già in movimento verso la mia nave. E porta il prigioniero qui.";
					link.l1 = "Grazie! Le merci saranno una bella compensazione per i miei guai. E il mio passeggero deve essere già vicino alle porte della città. Vi sarà portato.";
					link.l1.go = "Marginpassenger_offer_1";
				break;
				
				case 1: //просто кораблик
					SelectSouthcity();
					pchar.GenQuest.Marginpassenger.ShipName1 = GenerateRandomNameToShip(SPAIN);
					dialog.text = "È bello fare affari con un uomo intelligente. Ora ascolta: tra circa una settimana una brigantina spagnola '"+pchar.GenQuest.Marginpassenger.ShipName1+"' carico di merci preziose salperà da "+XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Southcity+"Gen")+" a "+XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Southcity1+"Gen")+". Se ti affretti, lo prenderai facilmente.\nSei ancora qui? Se fossi in te, sarei già sulla mia nave. E porta qui il prigioniero.";
					link.l1 = "Grazie! Le merci saranno un bel compenso per i miei guai. E il mio passeggero dovrebbe essere già vicino alle porte della città. Ti sarà portato.";
					link.l1.go = "Marginpassenger_offer_2";
				break;
			}
			sld = characterFromId("MarginPass");
			RemovePassenger(Pchar, sld);
			sld.lifeday = 0;
			pchar.GenQuest.Marginpassenger = "final";
		break;
		
		case "Marginpassenger_offer_1":
			DialogExit();
			AddQuestRecord("Marginpassenger", "13");
			AddQuestUserData("Marginpassenger", "sShore", XI_ConvertString(pchar.GenQuest.Marginpassenger.Shore+"Dat"));//лесник - окончание в СЖ // belamour gen: Abl - это к Залив"ом", нужен дательный
			AddQuestUserData("Marginpassenger", "sName", "Zachary Marlow")); // belamour gen : как-то странно, наводку даёт Захар, а в сж Добряк дефолтом
			SetFunctionTimerCondition("Marginpassenger_SouthshoreOver", 0, 0, 7, false);
			pchar.quest.Marginpassenger.win_condition.l1 = "location";
			pchar.quest.Marginpassenger.win_condition.l1.location = pchar.GenQuest.Marginpassenger.Shore;
			pchar.quest.Marginpassenger.function = "Marginpassenger_Southshore";
		break;
		
		case "Marginpassenger_offer_2":
			DialogExit();
			AddQuestRecord("Marginpassenger", "16");
			AddQuestUserData("Marginpassenger", "sName", "Zachary Marlow")); // belamour gen 
			AddQuestUserData("Marginpassenger", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Southcity+"Gen"));
			AddQuestUserData("Marginpassenger", "sCity1", XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Southcity1+"Acc")); // лесник - окончание в СЖ
			AddQuestUserData("Marginpassenger", "sShipName", pchar.GenQuest.Marginpassenger.ShipName1);
			SetFunctionTimerCondition("Marginpassenger_SouthshipInWorld", 0, 0, 5+rand(2), false);
		break;
		
		// ============== Грабеж среди бела дня, попытка залезть в сундуки =========================
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Rapina!!! È inaccettabile! Preparati, "+GetSexPhrase("ragazzo","ragazza")+"...","Ehi, cosa diavolo stai facendo lì?! Pensavi di potermi derubare? Sei finito...","Aspetta, che diavolo? Togliti di dosso! Risulta che sei un ladro! Fine della linea, bastardo...");
			link.l1 = LinkRandPhrase("Merda!","Carramba!!","Maledizione!!");
			link.l1.go = "PL_Q3_fight";
		break;
					
		// ======================== блок нод angry ===============>>>>>>>>>>>>>>>
		case "AngryRepeat_1":
            dialog.text = RandPhraseSimple(""+GetSexPhrase("Vattene ","Allontanati")+" da qui!","Vattene dalla mia casa!");
			link.l1 = "Ops...";
		    link.l1.go = "AngryExitAgainWithOut";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся через 10 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "Non infastidirmi con le tue chiacchiere da quattro soldi. La prossima volta il risultato non ti piacerà...";
        			link.l1 = "L'ho capito.";
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
            }
    	break;
		
		case "AngryRepeat_2":
            dialog.text = RandPhraseSimple("È finita, niente chiacchiere.","Non voglio più parlarti, quindi sarebbe meglio se non mi infastidissi.");
			link.l1 = RandPhraseSimple("Come desideri...","Mh, va bene allora...");
		    link.l1.go = "AngryExitAgain";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся через 10 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "Spero che dimostrerai più rispetto e smetterai di essere maleducato?";
        			link.l1 = "Potete stare tranquilli, Pastore, lo farò.";
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
            DoReloadCharacterToLocation("Puertoprincipe_town","reload","reload6");
		break;
		// <<<<<<<<<<<<============= блок нод angry =============================
		case "pirate_town":
            dialog.text = "Risolvere il problema? Hai idea di quello che hai fatto? Comunque, portami un milione di pesos e persuaderò i ragazzi a dimenticare la tua azione. Se l'idea non ti piace, allora puoi andare all'inferno.";
			if (sti(Pchar.money) >= 1000000)
			{
				link.l1 = "Bene, sono pronto a pagare.";
				link.l1.go = "pirate_town_pay";
			}
			link.l2 = "Capito. Me ne vado.";
			link.l2.go = "pirate_town_exit";
		break;
		
		case "pirate_town_exit":
			DialogExit();
            bDisableFastReload = true;//закрыть переход
			pchar.quest.pirate_in_town.win_condition.l1 = "ExitFromLocation";
			pchar.quest.pirate_in_town.win_condition.l1.location = pchar.location;
			pchar.quest.pirate_in_town.function = "TownPirate_battle";
		break;
		
		case "pirate_town_pay":
            dialog.text = "Bene! Considerati pulito di nuovo. Ma spero che non farai più queste cose disgustose.";
			link.l1 = "Non lo farò. Troppo costoso per me. Addio...";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -1000000);
			pchar.GenQuest.Piratekill = 0;
		break;
	}
}

void SelectSouthshore()
{
	switch (rand(6))
	{
		case 0: pchar.GenQuest.Marginpassenger.Shore = "shore37"; break;
		case 1: pchar.GenQuest.Marginpassenger.Shore = "shore47"; break;
		case 2: pchar.GenQuest.Marginpassenger.Shore = "shore48"; break;
		case 3: pchar.GenQuest.Marginpassenger.Shore = "shore25"; break;
		case 4: pchar.GenQuest.Marginpassenger.Shore = "shore21"; break;
		case 5: pchar.GenQuest.Marginpassenger.Shore = "shore20"; break;
		case 6: pchar.GenQuest.Marginpassenger.Shore = "shore19"; break;
	}
}

void SelectSouthcity()
{
	switch (hrand(2))
	{
		case 0: 
			pchar.GenQuest.Marginpassenger.Southcity = "Maracaibo";
			pchar.GenQuest.Marginpassenger.Southcity1 = "Havana"; 
		break;
		
		case 1:
			pchar.GenQuest.Marginpassenger.Southcity = "Cartahena";
			pchar.GenQuest.Marginpassenger.Southcity1 = "Santiago"; 
		break;
		
		case 2:
			pchar.GenQuest.Marginpassenger.Southcity = "Portobello";
			pchar.GenQuest.Marginpassenger.Southcity1 = "Santodomingo"; 
		break;
	}
}
