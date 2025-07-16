// Маркус Тиракс, барон Ла Веги
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sLoc, sTemp;
	int i;
	bool bOk;

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
			// Addon 2016-1 Jason пиратская линейка патч 17/1
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && !CheckAttribute(npchar, "quest.mtraxx_complete")) 
			{
				if (pchar.questTemp.Mtraxx == "full_complete_end" || pchar.questTemp.Mtraxx == "full_complete")
				{
					dialog.text = "Ah Principe, sei finalmente qui. Almeno uno di voi si è degnato di presentarsi! Il lavoro aspetta e tutti voi siete spariti! Dove diavolo sono tutti?";
					link.l1 = "Non ho idea... Marcus, me ne vado. Ho avuto abbastanza. Uomini morti vengono da me nei miei sogni e Lucifero stesso mi sta soffiando sulla schiena. Troppo sangue è stato versato di recente.";
					link.l1.go = "mtraxx_113";
					break;
				}
			}
			// Jason НСО
			// если Сага завалена, то у Маркуса ноды в двух местах и оплата вперед
			if(CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && pchar.questTemp.Patria == "epizode_12_pirates")
			{
				dialog.text = "Hai qualche 'affare' per me?";
				link.l1 = "Saluti, Marcus. Sì, ho un 'affare'. Redditizio e pratico.";
				link.l1.go = "patria_x";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Condotier.NeedMoney") && pchar.questTemp.Patria == "epizode_12_pirates" && sti(pchar.money) >= 100000)
			{
				dialog.text = "Hai portato i soldi?";
				link.l1 = "L'ho fatto.";
				link.l1.go = "patria_x8";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && pchar.questTemp.Patria == "epizode_12_talk")
			{
				dialog.text = "Questo è il nostro cliente! Il lavoro è fatto, il tuo Barone è seduto in un dungeon ben custodito. Forse, vorresti dare un'occhiata, eh-eh?!";
				link.l1 = "Avrò tutto il tempo per farlo, ah-ah. È trattato bene?";
				link.l1.go = "patria_10";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && CheckAttribute(pchar, "questTemp.Patria.DodsonFail"))
			{
				dialog.text = "Charles, che diavolo?!";
				link.l1 = "Marcus, tutto è andato storto. Non potevo né venire né informarti...";
				link.l1.go = "patria_x33";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && CheckAttribute(pchar, "questTemp.Patria.DodsonAgain"))
			{
				dialog.text = "Ecco il nostro burattinaio!";
				link.l1 = "Ah-ah! Lo spettacolo era perfetto!";
				link.l1.go = "patria_x29";
				break;
			}
            dialog.text = NPCStringReactionRepeat(""+GetSexPhrase("Hai qualcosa da dirmi? No? Allora lasciami in pace!","Ehi, "+pchar.name+"! Hai qualche affare con me? No? Allora non disturbarmi.")+"","Pensavo di essermi spiegato chiaramente... Ti ho detto di andartene ma continui a infastidirmi!","Bene, sto perdendo la pazienza con questa maleducazione.","ripeti",3,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Me ne sto già andando.","Certo, Marcus...","Mi dispiace, Marcus...","Ops...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			
			if (sti(pchar.GenQuest.Piratekill) > 20)
			{
				dialog.text = RandPhraseSimple("Sei pazzo? Volevi giocare al macellaio, eh? Tutti i pirati sono arrabbiati con te, ragazzo, faresti meglio a lasciare questo posto...","Sembra che tu sia diventato un cane rabbioso, ragazzo. Volevi allungare un po' le mani? Senza offesa, ma qui non c'è niente per te. Sparisci!");
				link.l1 = RandPhraseSimple("Ascolta, voglio risolvere la situazione.","Aiutami a risolvere questo problema, per favore...");
				link.l1.go = "pirate_town";
				break;
			}
			// Сага - завершаем искушение барбазона
			if (CheckAttribute(pchar, "questTemp.Saga.BarbTemptation") && pchar.questTemp.Saga.BarbTemptation == "terrax")
			{
				// Addon 2016-1 Jason пиратская линейка патч 17/1
				if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "full_complete_end")
				{
					link.l1 = "Marcus, smetterai mai di essere arrabbiato con me? Ho salvato il tuo amico, Vincent, che ha saccheggiato Cartagena con noi, e ho anche salvato il tuo culo! O Bernard non te l'ha nemmeno detto?";
					link.l1.go = "Temptation_13";
				}
				else
				{
					link.l1 = "Perché sei così maleducato, Marcus? Bernard non ti ha detto nulla su di me?";
					link.l1.go = "Temptation";
				}
			}
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "to_lavega")
			{
				link.l2 = "Sto cercando un lavoro... Hai qualcosa di redditizio in mente?";
				link.l2.go = "Mtraxx";
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx.SilkTrade") && GetSquadronGoods(pchar, GOOD_SHIPSILK) >= 20)
			{
				link.l2 = "Ho della seta da vendere.";
				link.l2.go = "Mtraxx_silktrade";
			}
			if (pchar.questTemp.Mtraxx == "silk_14")
			{
				link.l1 = "Ti ho trovato un compratore. È un costruttore di navi di Port Royal. Ha bisogno di seta per navi per la sua produzione e sarà in grado di acquistare lotti di cento rotoli ogni mese per 25 dobloni a rotolo. I suoi uomini riceveranno la merce dal 10 al 15, di notte, la location è Capo Negril. La parola d'ordine - 'Un mercante di Lione'. Il calvo Geffrey ha già consegnato il primo lotto a Giamaica.";
				link.l1.go = "mtraxx_13";
			}
			if (pchar.questTemp.Mtraxx == "silk_15")
			{
				link.l1 = "Ho trovato un acquirente per te. È un costruttore di navi di Port Royal. Ha bisogno di seta per nave per la sua produzione e sarà in grado di comprare lotti di cento rotoli ogni mese per 25 dobloni a rotolo. I suoi uomini riceveranno la merce dal 10 al 15, di notte, la location è Capo Negril. La parola d'ordine - 'Un mercante di Lione'. Mi sono voluti più di due mesi per trovare un acquirente del genere, Geffrey deve aver già venduto la seta ai contrabbandieri. Mi dispiace, Marcus.";
				link.l1.go = "mtraxx_15";
			}
		break;

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

        case "I_know_you_good":
			if (sti(pchar.GenQuest.Piratekill) > 20)
			{
				dialog.text = RandPhraseSimple("Sei pazzo? Volevi fare il macellaio? Tutti i pirati sono arrabbiati con te, ragazzo, sarebbe meglio che te ne andassi da questo posto...","Sembra che tu sia diventato un cane rabbioso, ragazzo. Volevi allungare un po' le mani? Senza offesa, ma qui non c'è posto per te. Sparisci!");
				link.l1 = RandPhraseSimple("Ascolta, voglio risolvere la situazione...","Aiutami a risolvere questo problema, per favore...");
				link.l1.go = "pirate_town";
				break;
			}
			// Jason НСО
			if(!CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && CheckAttribute(pchar, "questTemp.Patria.DodsonFail"))
			{
				dialog.text = "Charles, che diavolo?!";
				link.l1 = "Marcus, tutto è andato storto. Non potevo né venire né informarti...";
				link.l1.go = "patria_33";
				break;
			}
			if(!CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && CheckAttribute(pchar, "questTemp.Patria.DodsonAgain"))
			{
				dialog.text = "Contento di vederti, amico!";
				link.l1 = "Contento di vederti anche tu. Grazie per lo spettacolo straordinario!";
				link.l1.go = "patria_29";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Saga.Terrax") && pchar.questTemp.Patria == "epizode_12_pirates")
			{
				dialog.text = "Contento di vederti, ragazzo! Come posso aiutarti?";
				link.l1 = "Ho una proposta per te. Degna di un pirata, sai!";
				link.l1.go = "patria";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Saga.Terrax") && pchar.questTemp.Patria == "epizode_12_talk")
			{
				dialog.text = "Ecco il nostro cliente! Il lavoro è fatto, il tuo Barone è rinchiuso in un dungeon ben sorvegliato. Forse vorresti dare un'occhiata, eh-eh?!";
				link.l1 = "Avrò tutto il tempo per farlo, ah-ah. Lo trattano bene?";
				link.l1.go = "patria_10";
				break;
			}
			// если Сага завалена, то у Маркуса ноды в двух местах и оплата вперед
			if(CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && pchar.questTemp.Patria == "epizode_12_pirates")
			{
				dialog.text = "Hai qualche affare per me?";
				link.l1 = "Saluti, Marcus. Sì, un affare. Redditizio e pirata.";
				link.l1.go = "patria_x";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Condotier.NeedMoney") && pchar.questTemp.Patria == "epizode_12_pirates" && sti(pchar.money) >= 100000)
			{
				dialog.text = "Hai portato i soldi?";
				link.l1 = "L'ho fatto.";
				link.l1.go = "patria_x8";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && pchar.questTemp.Patria == "epizode_12_talk")
			{
				dialog.text = "Ecco il nostro cliente! Il lavoro è fatto, il tuo Barone è seduto in una prigione ben sorvegliata. Forse vorresti dare un'occhiata, eh-eh?!";
				link.l1 = "Avrò tutto il tempo per farlo, ah-ah. Sta bene, lui?";
				link.l1.go = "patria_10";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && CheckAttribute(pchar, "questTemp.Patria.DodsonFail"))
			{
				dialog.text = "Charles, che diavolo?!";
				link.l1 = "Marcus, tutto è andato storto. Non potevo né venire né informarti...";
				link.l1.go = "patria_x33";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && CheckAttribute(pchar, "questTemp.Patria.DodsonAgain"))
			{
				dialog.text = "Ecco il nostro burattinaio!";
				link.l1 = "Ah-ah! Lo spettacolo era perfetto!";
				link.l1.go = "patria_x29";
				break;
			}
			// Тени прошлого
			if(CheckAttribute(pchar, "questTemp.Saga.Shadows") && pchar.questTemp.Saga.Shadows == "islatesoro" && npchar.location == "Pirates_townhall")
			{
				dialog.text = "Contento di vederti, ragazzo! Come posso aiutarti?";
				link.l1 = "Marcus, devo parlarti. Non sono sicuro che ti piacerà, ma ho comunque bisogno del tuo aiuto.";
				link.l1.go = "shadows";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "islatesoro" && npchar.location == "Pirates_townhall")
			{
				dialog.text = "Ah, eccoti, "+pchar.name+". Stavo aspettando il tuo arrivo. Il Diavolo della Foresta mi ha messo in difficoltà con il tuo problema riguardo a Tortuga...";
				link.l1 = "Mi ha detto che hai trovato una soluzione. Ho ragione?";
				link.l1.go = "terrapin";
				break;
			}
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx.SilkTrade") && GetSquadronGoods(pchar, GOOD_SHIPSILK) >= 20)
			{
				link.l2 = "Ho seta da vendere.";
				link.l2.go = "Mtraxx_silktrade";
			}
            dialog.text = NPCStringReactionRepeat(GetFullName(pchar)+", lieto di vederti! Di cosa hai bisogno questa volta, amico?","Cosa vuoi?","Di nuovo? Non disturbare la gente se non hai nulla da fare!","Sei un "+GetSexPhrase("bravo corsaro","brava ragazza")+", quindi puoi vivere per ora. Ma non voglio più parlarti.","ripeti",10,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Solo volevo vederti.","Nulla.","Bene, Marcus, mi dispiace.","Maledizione, mi dispiace davvero, Marcus!",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";
		break;

		// ============== Грабеж среди бела дня, попытка залезть в сундуки =========================
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Rapina!!! Questo è inaccettabile! Preparati a morire, ratto...","Ehi, cosa stai facendo lì?! Pensavi di potermi derubare? Sei finito...","Aspetta, che diavolo?! Risulta che tu sei un ladro! Fine della corsa, bastardo...");
			link.l1 = LinkRandPhrase("Merda!","Carramba!","Ah, dannazione!");
			link.l1.go = "PL_Q3_fight";
		break;
					
		// ======================== блок нод angry ===============>>>>>>>>>>>>>>>
		case "AngryRepeat_1":
            dialog.text = RandPhraseSimple(""+GetSexPhrase("Vattene","Allontanati")+" da qui!","Vattene dalla mia casa!");
			link.l1 = "Ops...";
		    link.l1.go = "AngryExitAgainWithOut";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся через 10 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "Non distrarmi dal mio lavoro con le tue chiacchiere inutili. La prossima volta non finirà così bene per te...";
        			link.l1 = "Capito, Marcus.";
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
            }
    	break;
		case "AngryRepeat_2":
            dialog.text = RandPhraseSimple("Sono stanco di te.","Non voglio parlare con te, quindi sarebbe meglio se ti tenessi alla larga da me.");
			link.l1 = RandPhraseSimple("Ebbene...","Ehm, va bene allora...");
		    link.l1.go = "AngryExitAgain";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся через 10 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "Spero che non mi infastidirai più con le tue chiacchiere vuote o dovrò ucciderti. Dico, che non mi farà piacere farlo.";
        			link.l1 = "Puoi starne certo, Marcus, io non lo farò...";
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
		
//--> -----------------------------Сага - Искушение Барбазона завершающие этапы---------------------------
		case "Temptation":
			dialog.text = "Ah! L'eroe di Turks? Scusa per il brutale saluto, ragazzo. Bernard mi ha già parlato del tuo meraviglioso coinvolgimento e ha detto qualcosa su una trappola per me. Mi piacerebbe sentire i dettagli...";
			link.l1 = "Effettivamente era una trappola. Ti stavano cacciando, non Bernard. Lui era solo l'esca";
			link.l1.go = "Temptation_1";
		break;
		
		case "Temptation_1":
			dialog.text = "";
			link.l1 = "Il piano era semplice. Dovevi salvare il tuo amico e saresti stato il primo ad imbarcarti sul 'Separator'. E proprio in quel momento avrebbero sparato alla nave e l'avrebbero fatta saltare in aria. La brigantina era carica di polvere da sparo come l'inferno di zolfo.";
			link.l1.go = "Temptation_2";
		break;
		
		case "Temptation_2":
			dialog.text = "Maledizione! Di chi era quell'idea folle?! E come avrei potuto scoprire dove si nascondevano Bernard?!";
			link.l1 = "Gli autori di quel piano erano Jackman e suo fratello David. Un messaggero ti avrebbe informato che il 'Separatore' stava aspettando il tuo aiuto nella baia meridionale di Turks. Hanno scelto me come quel messaggero e quello è stato il loro errore.";
			link.l1.go = "Temptation_3";
		break;
		
		case "Temptation_3":
			dialog.text = "Non capisco! Qual è il tuo ruolo in tutto questo?";
			link.l1 = "Sto osservando quel bastardo di Jackman da molto tempo. Lavoro con Jan Svenson, se non lo sapevi. Io e il Diavolo della Foresta abbiamo deciso di smascherarlo. Jan è sicuro che sia lui il colpevole della morte di Blaze e Steven è stato accusato ingiustamente.";
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "full_complete_end") link.l1.go = "Temptation_14";
			else link.l1.go = "Temptation_4"; //патч 17/1
		break;
		
		case "Temptation_4":
			dialog.text = "Eh! Ma un dente di squalo con le sue iniziali è stato trovato sul corpo di Blaze con le sue iniziali - S.D. - questa cosa appartiene a Steven, tutti lo sanno...";
			link.l1 = "È stato tutto organizzato. Jackman ha giocato una posta alta. Si è liberato di Nathaniel Hawk e ha preso il suo posto a Maroon Town, poi ha assassinato Sharp e ha fatto in modo che Shark fosse responsabile dell'omicidio. Ho abbastanza prove dei suoi crimini. Le ho trovate nel baule di Jacob. È lì che erano la seconda parte della mappa di Sharp e il frammento di Hawk.";
			link.l1.go = "Temptation_5";
		break;
		
		case "Temptation_5":
			dialog.text = "Maledizione! Quindi Steven è innocente? E perché Jacob ha fatto tutto questo?";
			link.l1 = "Si aspettava di diventare il capo dei Fratelli e si aspettava qualcosa legato a Isla Tesoro. Non è riuscito a ottenere il tuo e il sostegno di Svenson, quindi ha deciso di sbarazzarsi di entrambi. Tu eri il primo nella lista. Jan, come il più pericoloso, era il secondo.";
			link.l1.go = "Temptation_6";
		break;
		
		case "Temptation_6":
			dialog.text = "Dove si nasconde quel bastardo?! Lo farò a pezzi!";
			if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) // Акула жив
			{
				link.l1 = "Jackman e suo fratello sono morti, così come il resto dei suoi cacciatori. Me ne sono occupato personalmente. Questo bastardo non nuocerà più a nessuno. Marcus, voteresti per Steven Dodson? Questo è un favore personale.";
				link.l1.go = "Temptation_7";
			}
			else
			{
				link.l1 = "Jackman e suo fratello sono morti così come il resto dei cacciatori. Me ne sono occupato personalmente. Questo bastardo non farà più del male a nessuno. Purtroppo, Steven è stato ucciso...";
				link.l1.go = "Temptation_10";
			}
		break;
		
		case "Temptation_7":
			dialog.text = "Certo che voterò! Ho sempre considerato Shark il più degno di noi dopo Blaze. E ho quasi creduto alla sua colpa. Tutti noi l'abbiamo fatto! Ecco, prendi il mio frammento.";
			link.l1 = "Molto bene! Ora puoi respirare liberamente.";
			link.l1.go = "Temptation_8";
		break;
		
		case "Temptation_8":
			GiveItem2Character(pchar, "splinter_mt"); // дать осколок
			dialog.text = "Vero... Da quanto capisco, rappresenti gli interessi dello Squalo?";
			link.l1 = "Sì. Io e Jan Svenson. Bene, Marcus, ci vediamo!";
			link.l1.go = "Temptation_9";
		break;
		
		case "Temptation_10":
			dialog.text = "Morto?! Come? Opera di Jackman anche?";
			link.l1 = "No. Lo ha fatto il suo proprio contramaestro, Chad Kapper era il suo nome. Ha già ottenuto ciò che meritava... Marcus, Svenson pensa che tu sia il più degno di essere il nuovo leader dei Fratelli. Il resto dei baroni supporterà questa decisione. Accetti?";
			link.l1.go = "Temptation_11";
		break;
		
		case "Temptation_11":
			dialog.text = "Eh! Non hai bisogno di chiedermelo due volte. È un grande onore essere il Capo dei Fratelli! Non pensare nemmeno che non sarò d'accordo.";
			link.l1 = "Ottimo. Sono contento che tu l'abbia accettato.";
			link.l1.go = "Temptation_12";
		break;
		
		case "Temptation_12":
			GiveItem2Character(pchar, "splinter_mt"); // дать осколок
			dialog.text = "Ecco, prendi il mio frammento. Consegnalo a Svenson. Immagino che sia lui il capo?";
			link.l1 = "Sì, lo è. Bene, Marcus, ci vediamo!";
			link.l1.go = "Temptation_9";
		break;
		
		case "Temptation_9":
			dialog.text = "Sì, e voglio ringraziarti per aver salvato il mio amico Bernard. Ecco, prendi questa borsa piena d'oro.";
			link.l1 = "Grazie! Addio!";
			link.l1.go = "Temptation_exit";
		break;
		
		case "Temptation_exit":
			DialogExit();
			TakeNItems(pchar, "gold_dublon", 300);
			Log_Info("You have received 300 doubloons");
			PlaySound("interface\important_item.wav");
			NextDiag.CurrentNode = "I_know_you_good";
			AddQuestRecord("BarbTemptation", "25");
			if (CheckCharacterItem(pchar, "splinter_mt") && CheckCharacterItem(pchar, "splinter_jb") && CheckCharacterItem(pchar, "splinter_zm")) Saga_GiveCalendar();
			ChangeCharacterComplexReputation(pchar, "fame", 1);
		break;
		
		// Addon 2016-1 Jason пиратская линейка патч 17/1
		case "Temptation_13":
			dialog.text = "Sì, mi ha parlato dell'arrivo magnifico di Charlie Prince a Turks... Mi ha salvato il culo dici? Come? Bernard mi ha detto qualcosa di una trappola...";
			link.l1 = "Sì, era una trappola. Tu eri il bersaglio, Bernard era solo l'esca...";
			link.l1.go = "Temptation_1";
		break;
		
		case "Temptation_14":
			dialog.text = "Ah-ah-ah, lavorando per il Diavolo della Foresta, eh Principe? Quindi, guadagni più soldi con lui di quanto ne guadagnassi con me? Dimmelo in tutta onestà!";
			link.l1 = "Marcus, mettiamo da parte il passato per sempre. Ora abbiamo un obiettivo comune ed è più importante di saccheggiare carovane. Dannazione! È la cosa più importante ora! Il futuro dei Fratelli è in gioco!";
			link.l1.go = "Temptation_15";
		break;
		
		case "Temptation_15":
			dialog.text = "Bene Principe, ho capito! Dopotutto sei un corsaro libero, lavorare per il Diavolo della Foresta è stata la tua scelta, e hai preso una buona decisione... Steven allora... Hai detto che è stato diffamato, giusto?";
			link.l1 = "Assolutamente giusto.";
			link.l1.go = "Temptation_4";
		break;
		
		// Тени прошлого
		case "shadows":
			dialog.text = "Certo, farò del mio meglio per aiutarti! Continua.";
			link.l1 = "Dai un'occhiata, Marcus... Ecco un dente di squalo. Cosa puoi dirmi al riguardo?";
			link.l1.go = "shadows_1";
		break;
		
		case "shadows_1":
			RemoveItems(pchar, "shark_teeth", 1);
			dialog.text = "Ah! È il dente di uno squalo bianco che fu ucciso da Steven Dodson, sperava di impressionare una ragazza. Da allora la gente ha iniziato a chiamarlo Squalo. Solo pochi avrebbero potuto farlo sott'acqua con una semplice sciabola. Ma lui era giovane e stupido e Beatrice Sharp era la ragazza più bella dei Caraibi... Quindi, come l'hai ottenuto tu?";
			link.l1 = "Me l'ha dato l'ex boia di Saint John's. Questo dente è stato usato per uccidere un uomo. Il suo nome era... Joshua Leadbeater.";
			link.l1.go = "shadows_2";
		break;
		
		case "shadows_2":
			dialog.text = "È una vecchia storia. Steven ha ucciso quell'uomo. Fu scioccato dalla morte di Beatrice e pensò che Leadbeater fosse l'unico vivente responsabile della sua morte. Ma poi trovò alcuni documenti sul cadavere di Joshua, li studiò e si pentì del suo gesto.\nLa Maschera non doveva essere incolpata per la morte di Beatrice, aveva bisogno solo del Macellaio. La gelosa ex fidanzata del Macellaio, Jessica, aveva organizzato tutto questo.";
			link.l1 = "Hai letto quei documenti?";
			link.l1.go = "shadows_3";
		break;
		
		case "shadows_3":
			dialog.text = "Perché dovrei? Certo che no. Non mi interessavano. Ma posso dirti perché la Maschera stava inseguendo il Macellaio se hai un po' di tempo libero. Steven l'ubriaco mi ha raccontato questa storia molte volte.";
			link.l1 = "Ho tempo. Fidati di me, il mio interesse ha uno scopo. Posso anche scrivere questa storia.";
			link.l1.go = "shadows_4";
		break;
		
		case "shadows_4":
			dialog.text = "So che non perdi mai tempo. Allora ascolta. Joshua Leadbeater era il capitano navale inglese e la leggendaria 'Nettuno' era sotto il suo comando...";
			link.l1 = "...";
			link.l1.go = "shadows_5";
		break;
		
		case "shadows_5":
			DialogExit();
			SetLaunchFrameFormParam("One hour later", "Saga_FinalLedbitterStory", 0, 4);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 10); //крутим время
			RecalculateJumpTable();
		break;
		
		case "shadows_6":
			AddQuestRecordInfo("Mask", "1");
			dialog.text = "... ma Leadbeater sopravvisse e fu raccolto da una nave. La sua ferita lo ha sfigurato e da allora ha indossato una maschera. Dopo un po' di tempo, la gente ha iniziato a chiamarlo la Maschera. Vendicarsi dell'uomo che lo aveva segnato per la vita divenne il suo obiettivo di vita.";
			link.l1 = "Capisco... Ho scritto tutto. Credo che dovrò rileggerlo e fare paragoni con tutte le informazioni che ho già. Una storia triste davvero. Hai mai visto Jessica?";
			link.l1.go = "shadows_7";
		break;
		
		case "shadows_7":
			dialog.text = "Certo! Ha accompagnato il Macellaio in tutti i suoi viaggi fino a quando lui l'ha lasciata per Beatrice. Jess non glielo ha mai perdonato. La gente la chiamava il talismano del Macellaio, perché lui aveva sempre fortuna quando lei era con lui.  Che tu ci creda o no, ma non appena lui si è liberato di lei a Barbados, i suoi affari sono andati male, il bottino è diventato scarso e il 'Nettuno' è diventato un ospite frequente nel cantiere navale di Isla Tesoro. Ma si può spiegare con il fatto che il Macellaio passava la maggior parte del suo tempo con Beatrice nella cabina piuttosto che sul cassero.  Beatrice non era come Jessica, non era avvezza alle avventure e alla guerra, anche se Nicholas le insegnò a scherma e a navigare. Sì, era affascinata dai romanzi di mare ma non aveva abbastanza durezza dentro. Il 'Nettuno' del Macellaio non era il posto giusto per lei. Alla fine, l'ha uccisa.";
			link.l1 = "E che ne è di Jessica?";
			link.l1.go = "shadows_8";
		break;
		
		case "shadows_8":
			dialog.text = "Oh, era qualcosa di veramente speciale... Ogni marinaio del 'Nettuno' obbediva ai suoi ordini e non solo perché era la fidanzata del capitano. Jess era una maestra di scherma e vela, gli sforzi del Macellaio non erano stati sprecati. Era dura e spensierata, e era così bella.\nMolti uomini volevano condividere il letto con lei, ma lei voleva solo il Macellaio, infastidirla era davvero rischioso, molti hanno provato i risultati sulla loro stessa pelle, letteralmente, e per i più persistenti le sue lezioni di scherma si sono rivelate l'ultima della loro vita.\nJess possedeva una spada molto speciale, l'unica del suo genere nei Caraibi, non ho idea di dove l'abbia presa. Una spada con la lama di fiamma. Non si poteva afferrare la lama con la mano e anche il minimo tocco lasciava una ferita terribile.\nJess era un'avventuriera non di nascita, ma per vocazione. A proposito, se vuoi saperne di più su di lei, puoi parlare con un tuo conoscente. Lui può raccontarti molto di più su di lei di quanto possa fare io.";
			link.l1 = "Davvero? E chi è quest'uomo?";
			link.l1.go = "shadows_9";
		break;
		
		case "shadows_9":
			dialog.text = "Jan Svenson. Il Diavolo della Foresta non lo ammetterà mai, ma aveva dei progetti con Jessica. Era il periodo in cui aveva già preso Western Main per sé e la sua fama era qualcosa da invidiare, quindi la tigre era buona per lui.\nDopo che il Macellaio si era sbarazzato di Jess, Jan ha iniziato a visitare Barbados sospettosamente spesso, faceva tremare di paura la guarnigione. Come sai, Jessica era la figlia di un coltivatore di Bridgetown.\nIn definitiva, i suoi piani erano ben noti nei circoli privati, ma nessuno osava parlare apertamente di esso. Jan può sedersi sulle sue terga a Blueweld al giorno d'oggi, ma all'epoca una parola sbagliata in suo indirizzo poteva finire male.\nAlla fine, non ha funzionato per loro. Jess non riusciva a vivere con il dolore causato dal tradimento del Macellaio, e si è presa la sua vendetta un anno dopo con l'aiuto della Maschera. Questa vendetta è finita in modo terribile per tutti: per il Macellaio, per Beatrice, per la Maschera e per se stessa. Sono tutti morti.";
			link.l1 = "No. Il macellaio è ancora vivo.";
			link.l1.go = "shadows_10";
		break;
		
		case "shadows_10":
			dialog.text = "Cosa?! Ho sentito male?! È vivo?!";
			link.l1 = "Sì. Il capitano Macellaio non è stato impiccato. Hm, in realtà lo era, ma grazie a Jacob Jackman e Henry il Boia, che aveva spaventato il boia, è sopravvissuto. L'impiccagione era solo una messinscena. Ho delle prove.";
			link.l1.go = "shadows_11";
		break;
		
		case "shadows_11":
			dialog.text = "Incredibile! E dove si trova ora?";
			link.l1 = "È conosciuto come Lawrence Beltrop ed abita a Port-Royal. Ma sembra che non sia cambiato e che sia ancora pericoloso. Jackman, che ha causato un sacco di trambusto tra i Fratelli, stava seguendo i suoi ordini.";
			link.l1.go = "shadows_12";
		break;
		
		case "shadows_12":
			dialog.text = "Cavolo! Il quartiermastro ha trovato il suo capitano dopo tutto! Dopo tanti anni... Beltrop dici... aspetta! Ora capisco perché nei documenti di Blaze c'era quel strano protocollo dell'interrogatorio... Sembra che Blaze abbia scoperto qualcosa di interessante su Macellaio-Beltrop...";
			link.l1 = "Di cosa stai parlando?";
			link.l1.go = "shadows_13";
		break;
		
		case "shadows_13":
			dialog.text = "Quando ho preso questa residenza, mi sono concesso del tempo per dare un'occhiata ai documenti di Blaze. Ho trovato un protocollo di interrogatorio di qualcuno chiamato Samuel Brooks. C'erano un sacco di dettagli sulle avventure di Thomas Beltrope, un famoso pirata e l'amico più stretto di Nicolas Sharp. Sembra che sia il padre di Macellaio.";
			link.l1 = "Interessante. Sembra che i figli di Beltrop e Sharp abbiano continuato il lavoro dei loro padri...";
			link.l1.go = "shadows_14";
		break;
		
		case "shadows_14":
			dialog.text = "Sembra proprio così... Dimmi, amico, perché sei così interessato al passato di persone che sono morte da molto tempo? Di cosa si tratta tutto questo?";
			link.l1 = "Mi servono documenti che possano provare che Ellen McArthur è la figlia di Beatrice Sharp e la nipote di Nicolas Sharp e ha tutti i diritti di portare questo cognome. Non mi importa che il suo cognome potrebbe essere Beltrop.";
			link.l1.go = "shadows_15";
		break;
		
		case "shadows_15":
			dialog.text = "Non ho trovato nulla su Ellen McArthur negli archivi di Blaze. È strano che Beatrice non abbia parlato a Blaze della nascita di sua nipote. Non è nel suo stile.";
			link.l1 = "Ascolta, forse c'è qualcosa di più nei documenti di Sharp su questa storia? Ho bisogno di ogni dettaglio che posso ottenere!";
			link.l1.go = "shadows_16";
		break;
		
		case "shadows_16":
			dialog.text = "Mh... Forse. Secondo le note di Blaze, stava cercando di trovare l'isola dove era morta sua sorella. Ci sono copie di documenti d'archivio riguardanti la spedizione punitiva di Leadbeater. Niente di interessante, a parte alcuni numeri di latitudine.\nQuesta parallela attraversa il Mar dei Caraibi nella sua parte settentrionale. Ma non c'è traccia di longitudine. Ovviamente, le ricerche di Blaze non hanno avuto successo, non puoi nemmeno immaginare quanti piccoli isolotti si trovano a quella latitudine.";
			link.l1 = "E qual è la latitudine?";
			link.l1.go = "shadows_17";
		break;
		
		case "shadows_17":
			dialog.text = "Vediamo... Ecco: 21 32' Nord. Non so come possa aiutarti.";
			link.l1 = "Può. Grazie mille, Marcus, per la tua storia franca. Ci vediamo!";
			link.l1.go = "shadows_18";
		break;
		
		case "shadows_18":
			DialogExit();
			pchar.questTemp.Saga.Shadows = "jessika";
			AddQuestRecord("Shadows", "6");
			LAi_SetHuberType(npchar);
			NextDiag.CurrentNode = "I_know_you_good";
			sld = characterFromId("Svenson");
			sld.quest.jessika = "true";
			// рифы доступны для посещения
			i = FindIsland("RockIsland");
			Islands[i].visible = true;
			Islands[i].reload_enable = true;
			// для любителей самостоятельно добавлять локаторы
			LAi_LocationDisableOfficersGen("Shore67", true);//офицеров не пускать
			// и сразу прерывание
			pchar.quest.Saga_Jess_Island.win_condition.l1 = "location";
			pchar.quest.Saga_Jess_Island.win_condition.l1.location = "Shore67";
			pchar.quest.Saga_Jess_Island.function = "Saga_JessikaIsland"; 
			// активируем квест хронометра Алекса
			pchar.questTemp.AlexClock = "terrax"; // 280912
		break;		
		
		// суп из черепахи
		case "terrapin":
			dialog.text = "Ebbene, posso fare qualcosa per te. Come sai, la sicurezza di Tortuga non è garantita solo dal forte La Roche, ma anche da uno squadrone di pirati che vigilano costantemente le coste dell'isola. Il porto di Tortuga è sicuro, questi ragazzi sanno il loro mestiere e hanno navi potenti. Levasseur ha tentato di attirare questi capitani per molto tempo.\nSono capaci di combattere anche contro uno squadrone di linea e saranno avversari seri. Quindi, essendo il custode del Codice e anche il leader dei Fratelli della Costa, posso far sì che questi cani da guardia lascino le coste di Tortuga.";
			link.l1 = "E questo è tutto?";
			link.l1.go = "terrapin_1";
		break;
		
		case "terrapin_1":
			dialog.text = "Non è abbastanza? Non posso aiutarti di più. Devi distruggere il forte, ma almeno non devi combattere quelle navi da guardia. Credimi, sono più pericolose del Forte, quindi il mio aiuto renderà tutto più facile.";
			link.l1 = "Ebbene, se devo attaccarlo comunque, la partenza della squadra di pirati sarà davvero utile. Grazie, Marcus! Quando posso attaccare Tortuga?";
			link.l1.go = "terrapin_2";
		break;
		
		case "terrapin_2":
			dialog.text = "Quando vuoi. Le navi da guardia partiranno al mio segnale.";
			link.l1 = "Bene. Allora devo andare a prepararmi.";
			link.l1.go = "terrapin_3";
		break;
		
		case "terrapin_3":
			DialogExit();
			// Левассера - к барьеру!
			sld = characterFromId("Tortuga_Mayor");
			LAi_LoginInCaptureTown(sld, true);
			pchar.questTemp.Sharlie.Hardcore_Tortuga = "true";
			pchar.questTemp.Terrapin = "hardcore";
			pchar.questTemp.Sharlie.DelTerGuard = "true"; // убираем пиратскую эскадру
		break;
		
		case "pirate_town":
            dialog.text = "Risolvere il problema? Hai idea di quello che hai fatto? Comunque, portami un milione di pesos e convincerò i ragazzi a dimenticare il tuo atto. Se l'idea non ti piace, allora puoi andare all'inferno.";
			if (sti(Pchar.money) >= 1000000)
			{
				link.l1 = "Bene, sono pronto a pagare.";
				link.l1.go = "pirate_town_pay";
			}
			link.l2 = "Addio...";
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
            dialog.text = "Bene! Considerati di nuovo pulito. Ma spero che non farai più queste cose disgustose.";
			link.l1 = "Non lo farò. Troppo costoso per me. Addio...";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -1000000);
			pchar.GenQuest.Piratekill = 0;
		break;
		
		// Addon 2016-1 Jason ------------------------- пиратская линейка --------------------------
		case "Mtraxx":
			if (pchar.Ship.Type == SHIP_NOTUSED)
			{
				dialog.text = "Prima procurati una nave, poi chiedi un lavoro. Un terrestre non ha nulla da fare qui. Sparisci!";
				link.l1 = "Mmm... Capisco.";
				link.l1.go = "exit";
				break;
			}
			if(ChangeCharacterHunterScore(Pchar, "spahunter", 0) > 10)
			{
				dialog.text = "Sei completamente fuori di testa? Metà del mondo spagnolo ti sta inseguendo. Farai più male che bene. Risolvi i tuoi problemi, poi fai domanda. Questo è tutto quello che volevo dire! Vattene da qui!";
				link.l1 = "Mmm... Capisco.";
				link.l1.go = "exit";
				break;
			}
            dialog.text = "Vuoi un po' di azione, eh? Ah-ah! Bene... Ma ti avverto, ragazzo, non troverai pace con me. Se hai paura dell'odore della polvere da sparo o non riesci a far colare il sangue - la porta è dietro di te. Non sopporto i fifoni. Inoltre, non durerai a lungo con me se sei uno spione o un topo che ama rubare la quota di bottino di un compagno. E allora? Sei dentro?";
			link.l1 = "Sono dentro, Marcus. Non ho paura di combattere e non c'è cane che possa accusarmi di essere né un codardo né un ratto.";
			link.l1.go = "Mtraxx_1";
			link.l2 = "Whoa, è troppo difficile per me! Chiedo perdono, Marcus, ma è meglio che me ne vada...";
			link.l2.go = "Mtraxx_exit";
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("LaVega");
		break;
		
		case "Mtraxx_exit":
            DialogExit();
			pchar.questTemp.Mtraxx = "fail";
		break;
		
		case "mtraxx_wait":
            dialog.text = "Cosa, sei ancora qui?";
			if (CheckAttribute(pchar, "questTemp.Mtraxx.SilkTrade") && GetSquadronGoods(pchar, GOOD_SHIPSILK) >= 20)
			{
				link.l2 = "Devo vendere della seta.";
				link.l2.go = "Mtraxx_silktrade";
				link.l1 = "Me ne sto già andando.";
				link.l1.go = "exit";
				break;
			}
			link.l1 = "...";
			link.l1.go = "exit";
		break;
		
		case "Mtraxx_1":
            dialog.text = "Ah-ah, bene-bene, mio coraggioso piccolo pirata, allora discutiamo di affari. La mia fonte a Santo Domingo mi ha informato di un capitano spagnolo così ricco di ambra blu che la sta regalando alle puttane. Hai sentito parlare dell'ambra blu?";
			link.l1 = "Ce l'ho. Una pietra rara e preziosa.";
			link.l1.go = "mtraxx_2";
		break;
		
		case "mtraxx_2":
            dialog.text = "Esattamente. Anche qui, banchieri e gioiellieri pagano un bel prezzo per esso e nella vecchia e cara Europa puoi ottenere dieci volte di più per esso. L'ambra non è una pietra rara nei Caraibi, ma quella blu è una rarità. E ora abbiamo un qualche furbo cane castigliano che si vanta di avere più ambra blu di quanta ambra gialla abbiano insieme i banchieri di Cuba e Hispaniola.";
			link.l1 = "Si possono fidare delle storie di qualche ubriacone spagnolo? Ha trovato tre dobloni e dice a tutti che ha trovato l'El Dorado";
			link.l1.go = "mtraxx_3";
		break;
		
		case "mtraxx_3":
            dialog.text = "Non avrei fatto, ma in realtà stava regalando ambra blu alle puttane. Qualcosa nel suo vantarsi deve essere affidabile. Vai a Santo Domingo e indaga. Se trovi il deposito di ambra blu sarà ancora meglio. Fai questo e posso garantirti una ricompensa e rispetto a La Vega.";
			link.l1 = "E se le tue informazioni non valgono nulla?";
			link.l1.go = "mtraxx_4";
		break;
		
		case "mtraxx_4":
            dialog.text = "Allora dimostrami che quel Castigliano è un bugiardo.";
			link.l1 = "Molto bene. Chi è la tua fonte a Santo Domingo?";
			link.l1.go = "mtraxx_5";
		break;
		
		case "mtraxx_5":
			// belamour legendary edition даем флаг и лизензию ГВИК если отсутствует -->
			bOk = IsCharacterPerkOn(pchar,"FlagSpa") || IsCharacterPerkOn(pchar,"FlagHol");
			if(CheckCharacterItem(pchar, "HolTradeLicence") && GetDaysContinueNationLicence(HOLLAND) >= 60 && bOk) sTemp = ".";
			else 
			{
				if(bOk) 
				{
					if(!CheckCharacterItem(pchar, "HolTradeLicence") || GetDaysContinueNationLicence(HOLLAND) < 60) 
					{
						sTemp = ". Wait a minute, take a trading license for 60 days."; 
						GiveNationLicence(HOLLAND, 60);
					}
				}
				else // нет флага
				{
					if(!CheckCharacterItem(pchar, "HolTradeLicence")) 
					{
						sTemp = ". Wait a minute, take a 60-day trade license and a Spanish flag to land in Santo Domingo. From now on, I recommend getting your own, it will help to fool the simpleton in the trading pelvis. This one will be returned to me.";
						GiveNationLicence(HOLLAND, 60);
						SetCharacterPerk(pchar, "FlagSpa");
						log_info("You have received spanish flag");
						pchar.questTemp.GiveMeSpaFlag = true;
					}
					else // есть лицензия
					{	
						if(GetDaysContinueNationLicence(HOLLAND) < 60) 
						{
							sTemp = ". Wait, how are you going to trade without having the right flag?! Here you go, a 60-day trading license, longer than yours. As well as the Spanish flag for landing in Santo Domingo. From now on, I recommend getting your own, it will help to fool the simpleton in the trading pelvis. This one will be returned to me.";
							GiveNationLicence(HOLLAND, 60);
							SetCharacterPerk(pchar, "FlagSpa");
							log_info("You have received spanish flag");
							pchar.questTemp.GiveMeSpaFlag = true;
						}
						else 
						{
							sTemp = ". Wait, how are you going to trade without having the right flag?! Here, take the Spanish flag for the Santo Domingo landings. From now on, I recommend getting your own, it will help to fool the simpleton in the trading pelvis. This one will be returned to me.";
							SetCharacterPerk(pchar, "FlagSpa");
							log_info("You have received spanish flag");
							pchar.questTemp.GiveMeSpaFlag = true;
						}
					}
				}
			}
			// <-- legendary edition
            dialog.text = "Hai bisogno di una ragazza del bordello di nome Gabriela Chapado. Pronuncia il mio nome e la password - 'Collana d'Ambra'. Ti darà i dettagli. E non perdere tempo - l'informazione è ancora fresca, ma in un giorno o due potrebbe diventare obsoleta"+sTemp;
			link.l1 = "Capito, Marcus. Sto andando a Santo Domingo.";
			link.l1.go = "mtraxx_6";
		break;
		
		case "mtraxx_6":
            DialogExit();
			pchar.questTemp.Mtraxx = "jewelry_1";
			pchar.questTemp.Mtraxx.AffairOfHonor = "true"; // конфликт с делом чести
			pchar.questTemp.ZA.block = true;			// конфликт с квестом "Заносчивый аристократ"
			npchar.dialog.currentnode = "mtraxx_wait";
			AddQuestRecord("Roger_1", "1");
			Mtraxx_JewelryBegin();
			AddMapQuestMarkCity("SantoDomingo", false);
		break;
		
		case "mtraxx_7":
			i = GetCharacterItem(pchar, "jewelry7");
            dialog.text = "Sono già stato informato del tuo arrivo. Dammi un rapporto!";
			link.l1 = "Mi sono occupato di quel amante dell'ambra blu, anche se non è stato facile. Sono riuscito a trovare i suoi depositi e a saccheggiarli. Ti ho portato "+FindRussianQtyString(i)+" pezzi di ambra blu.";
			link.l1.go = "mtraxx_8";
			DelLandQuestMark(characterFromId("Terrax"));
			DelMapQuestMarkCity("LaVega");
		break;
		
		case "mtraxx_8":
			if (sti(pchar.questTemp.Mtraxx.JewQty) > GetCharacterItem(pchar, "jewelry7"))
			{
				PlaySound("interface\important_item.wav");
				Log_Info("You have given "+FindRussianQtyString(GetCharacterItem(pchar, "jewelry7"))+" pieces of blue amber");
				RemoveItems(pchar, "jewelry7", GetCharacterItem(pchar, "jewelry7"));
				dialog.text = "Bene-bene... Figliolo, ti ricordi il mio avvertimento sui pericoli di essere un topo? Cosa mi hai detto allora? Nessun cane può incolparti per questo? Pensi che io sia stupido, ragazzo? Sono perfettamente consapevole che tu abbia saccheggiato "+FindRussianQtyString(sti(pchar.questTemp.Mtraxx.JewQty))+" pezzi di ambra blu sulla Costa delle Zanzare. Ora corri, piccolo ratto, corri, e prega che non ci incontreremo mai più!";
				link.l1 = "Maledizione!";
				link.l1.go = "AngryExitAgainWithOut";
				pchar.questTemp.Mtraxx = "fail";
				npchar.Dialog.currentnode = "First time";
				CloseQuestHeader("Roger_1");
				// belamour legendary edition забрать флаг обратно
				if(CheckAttribute(pchar, "questTemp.GiveMeSpaFlag")) 
				{
					DeleteAttribute(pchar, "questTemp.GiveMeSpaFlag")); 
					DeleteAttribute(pchar,"perks.list.FlagSpa"); 
					log_info("You have given spanish flag");
				}
			}
			else
			{
				PlaySound("interface\important_item.wav");
				Log_Info("You have given "+FindRussianQtyString(GetCharacterItem(pchar, "jewelry7"))+" pieces of blue amber");
				RemoveItems(pchar, "jewelry7", sti(pchar.questTemp.Mtraxx.JewQty));
				dialog.text = "Ben fatto, ragazzo! Ti sei mostrato dal tuo lato migliore: hai affrontato una questione difficile e hai portato tutto ciò che hai saccheggiato. Buon lavoro! Sono contento di non essermi sbagliato su di te.";
				link.l1 = "E che ne sarà della mia parte, Marcus?";
				link.l1.go = "mtraxx_9";
			}
		break;
		
		case "mtraxx_9":
			i = sti(pchar.questTemp.Mtraxx.JewQty)/2;
			PlaySound("interface\important_item.wav");
			Log_Info("You have received "+FindRussianQtyString(i)+" pieces of blue amber");
			TakeNItems(pchar, "jewelry7", i);
			// belamour legendary edition забрать флаг обратно
			if(CheckAttribute(pchar, "questTemp.GiveMeSpaFlag")) 
			{
				DeleteAttribute(pchar, "questTemp.GiveMeSpaFlag")); 
				DeleteAttribute(pchar,"perks.list.FlagSpa"); 
				log_info("You have given spanish flag");
			}
            dialog.text = "Parli come un vero pirata, ah-ah-ah! Metà del bottino è tua. Prendilo.";
			link.l1 = "Grazie, cap. Hai qualcos'altro per me?";
			link.l1.go = "mtraxx_10";
			DeleteAttribute(pchar, "questTemp.Mtraxx.JewQty");
			CloseQuestHeader("Roger_1");
			Achievment_Set("ach_57");
		break;
		
		case "mtraxx_10":
            dialog.text = "Ho sempre incarichi per i ragazzi capaci. C'è una questione delicata di cui voglio che tu ti occupi. C'è una nave ormeggiata a Capsterville, chiamata 'Snake', sotto il comando di Geffrey Brooke, noto anche come Geffrey il Calvo. Lavora per me. Un eccellente combattente, conosce tutto su pistole e lame ma è un completo idiota in ogni altro aspetto della vita. Ma non siamo duri con il Calvo, nessuno è perfetto, ah-ah! \n Quindi. Questo duro ha attaccato un convoglio olandese a nord di Saint Martin e ha catturato una barca piena di sacchi di grano. La cosa è, è riuscito a trovare della seta nascosta tra i sacchi. Un carico davvero grande. Questa merce è estremamente preziosa e rara, gli olandesi la portano dall'Europa solo per le esigenze delle loro forze armate. Questa seta viene utilizzata per vele speciali che aumentano la velocità della nave e la sua capacità di navigare controvento. \n È quasi impossibile da comprare, venderla non è un problema ma è difficile trovare il prezzo giusto. Questi maledetti commercianti riducono sempre il prezzo! So che ci sono persone nei Caraibi pronte a dare un buon prezzo in dobloni per comprare questa seta e il tuo obiettivo è trovare tali persone. \n Cosa? Qualsiasi sciocco può saccheggiare carovane ma il commercio è solo per persone con almeno un segno di esistenza di cervello in un cranio. Sto pensando di vendere seta per navi mensilmente quindi il tuo obiettivo è trovare un acquirente regolare che pagherà almeno venti dobloni d'oro per un rotolo. Hai due mesi per farlo, non posso tenere Geffrey il Calvo a Capsterville per sempre. \n Questo è tutto. Mettiti in rotta per Capsterville e parla con Geffrey prima che venda il carico ai contrabbandieri per un soldo. Ti ho già detto che è un po' 'semplice'.";
			link.l1 = "Mh... Capito. Sono già in viaggio.";
			link.l1.go = "mtraxx_11";
		break;
		
		case "mtraxx_11":
            DialogExit();
			pchar.questTemp.Mtraxx = "silk_1";
			npchar.dialog.currentnode = "mtraxx_wait";
			AddQuestRecord("Roger_2", "1");
			Mtraxx_SilkBegin();
		break;
		
		case "mtraxx_12":
            dialog.text = "Ah! Ecco l'audace capitano "+GetFullName(pchar)+"! Che ne sarà dell'acquirente?";
			if (CheckAttribute(pchar, "questTemp.Mtraxx.SilkLate"))
			{
				link.l1 = "Ho trovato un acquirente per te. È un costruttore di navi di Port Royal. Ha bisogno di seta navale per la sua produzione e sarà in grado di acquistare lotti di cento rotoli ogni mese per 25 dobloni a rotolo. I suoi uomini riceveranno la merce dal 10 al 15, di notte, la posizione è Capo Negril. La parola d'ordine - 'Un mercante di Lione'. Mi ci sono voluti più di due mesi per trovare un tale acquirente, Geffrey deve aver già venduto la seta ai contrabbandieri. Mi dispiace, Marcus.";
				link.l1.go = "mtraxx_15";
			}
			else
			{
				link.l1 = "Ho trovato un acquirente per te. È un costruttore di navi di Port Royal. Ha bisogno di seta marittima per la sua produzione e sarà in grado di acquistare lotti di cento rotoli ogni mese per 25 dobloni a rotolo. I suoi uomini riceveranno la merce dal 10 al 15, di notte, la località è Capo Negril. La parola d'ordine - 'Un mercante di Lione'. Il Calvo Geffrey ha già consegnato il primo lotto in Jamaica.";
				link.l1.go = "mtraxx_13";
			}
		break;
		
		case "mtraxx_13":
            dialog.text = "Questo è fantastico, amico mio! Ben fatto. È difficile trovare un uomo capace di usare sia le mani che la testa. Vieni a vedermi tra 20 giorni per ritirare la tua ricompensa. Bald Geffrey avrà portato il denaro dalla prima transazione entro allora."; // правки прогона 3
			link.l1 = "Molto bene, Marcus. A presto. Spero che avrai un altro lavoro per me.";
			link.l1.go = "mtraxx_14";
		break;
		
		case "mtraxx_14":
            dialog.text = "Lo farò. Ci vediamo dopo.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";
			if (CheckAttribute(pchar, "questTemp.Mtraxx.SilkLate"))
			{
				SetFunctionTimerCondition("Mtraxx_SilkPay", 0, 0, 30, false);
				//SetFunctionTimerCondition("Mtraxx_SilkPayLate", 0, 0, 40, false);
				AddQuestRecord("Roger_2", "23");
			}
			else
			{
				SetFunctionTimerCondition("Mtraxx_SilkPay", 0, 0, 20, false); // правки прогона 3
				//SetFunctionTimerCondition("Mtraxx_SilkPayLate", 0, 0, 30, false);
				AddQuestRecord("Roger_2", "24");
			}
		break;
		
		case "mtraxx_15":
			pchar.quest.Mtraxx_SilkTimeLateAll.over = "yes";
            dialog.text = "Peccato, ma comunque un grande successo. Hai fatto un buon lavoro! Non riceverai la tua parte dal lotto di Geffrey, ma meriti comunque una ricompensa. Vieni a trovarmi tra un mese, avrò venduto il primo lotto al tuo acquirente entro quel tempo, poi ne parleremo.";
			link.l1 = "Molto bene, Marcus. Ci vediamo presto. Spero che avrai un altro lavoro per me.";
			link.l1.go = "mtraxx_14";
		break;
		
		case "mtraxx_16":
			//pchar.quest.Mtraxx_SilkPayLate.over = "yes";
            dialog.text = "Eccoti qua, "+pchar.name+". Parliamo della tua ricompensa.";
			link.l1 = "Mi piacciono chiacchiere così, ah-ah-ah! Sono tutto orecchie.";
			if (CheckAttribute(pchar, "questTemp.Mtraxx.SilkLate")) link.l1.go = "mtraxx_19";
			else link.l1.go = "mtraxx_17";
		break;
		
		case "mtraxx_17":
            dialog.text = "Geffrey il Calvo ha venduto al tuo acquirente il primo lotto di 105 rotoli di seta navale. Pensavo di venderla per venti dobloni a rotolo, quindi penso che sarebbe giusto darti la differenza. Questa è la mia decisione. La tua quota è di 525 dobloni più un bonus - un doblone a rotolo. In totale sono 630 dobloni. Ecco, prendili.";
			link.l1 = "Grazie, Marcus!";
			link.l1.go = "mtraxx_18";
		break;
		
		case "mtraxx_18":
			TakeNItems(pchar, "gold_dublon", 630);
			Log_Info("You have received 630 doubloons");
			PlaySound("interface\important_item.wav");
            dialog.text = "Un'altra cosa. Puoi ottenere un profitto extra da questo.";
			link.l1 = "Interessante... Continua.";
			link.l1.go = "mtraxx_19";
		break;
		
		case "mtraxx_19":
            dialog.text = "Il tuo acquirente vuole più di 100 rotoli di seta da consegnare per i prossimi due mesi. Se ne hai, portami da 20 a 100 rotoli per un prezzo di 24 dobloni. L'offerta sarà valida per due mesi.";
			link.l1 = "Bene! Porterò di più se ne ho.";
			link.l1.go = "mtraxx_20";
			pchar.questTemp.Mtraxx.SilkTrade = "true";
			SetFunctionTimerCondition("Mtraxx_SilkTradeOver", 0, 0, 60, false);
		break;
		
		// торговля шелком
		case "mtraxx_silktrade":
			iTotalTemp = GetSquadronGoods(pchar, GOOD_SHIPSILK);
            dialog.text = "Quanto hai?";
			link.l1 = ""+FindRussianQtyString(iTotalTemp)+".";
			if (iTotalTemp > 100) link.l1.go = "mtraxx_silktrade_2";
			else link.l1.go = "mtraxx_silktrade_1";
		break;
		
		case "mtraxx_silktrade_1":
			RemoveCharacterGoods(pchar, GOOD_SHIPSILK, iTotalTemp);
			TakeNItems(pchar, "gold_dublon", iTotalTemp*24);
            dialog.text = "Molto bene. Prendi l'oro - 24 dobloni per un rotolo come abbiamo concordato.";
			link.l1 = "Grazie!";
			link.l1.go = "mtraxx_silktrade_3";
		break;
		
		case "mtraxx_silktrade_2":
			RemoveCharacterGoods(pchar, GOOD_SHIPSILK, 100);
			TakeNItems(pchar, "gold_dublon", 2400);
            dialog.text = "Prenderò un centinaio di rotoli. Prendi l'oro - 24 dobloni per rotolo come abbiamo concordato.";
			link.l1 = "Grazie!";
			link.l1.go = "mtraxx_silktrade_3";
		break;
		
		case "mtraxx_silktrade_3":
            DialogExit();
			npchar.dialog.currentnode = "First time";
			DeleteAttribute(pchar, "questTemp.Mtraxx.SilkTrade");
		break;
		
		case "mtraxx_20":
            dialog.text = "Parliamo di qualcosa di più urgente, vuoi occuparti di qualcosa di pericoloso?";
			link.l1 = "Certo! Io e i miei uomini siamo pronti a metterci in mare immediatamente.";
			link.l1.go = "mtraxx_24";
		break;
		
		case "mtraxx_22":
            dialog.text = "Per l'amor di Dio, "+pchar.name+", dove diavolo sei stato? Ti ricordi quando ti ho detto di venire a trovarmi? Avevo un lavoro per te e ora è sprecato grazie al tuo eccellente senso del tempo. Mi hai veramente contrariato, ragazzo. Vattene, non lavoro con persone su cui non posso contare.";
			link.l1 = "Beh, merda...";
			link.l1.go = "mtraxx_23";
		break;
		
		case "mtraxx_23":
			DialogExit();
            npchar.dialog.currentnode = "First time";
			CloseQuestHeader("Roger_2");
			pchar.questTemp.Mtraxx = "fail";
		break;
		
		case "mtraxx_24":
			// belamour legendary edition даем флаг и лизензию ГВИК если отсутствует -->
			bOk = IsCharacterPerkOn(pchar,"FlagSpa") || IsCharacterPerkOn(pchar,"FlagHol");
			if(CheckCharacterItem(pchar, "HolTradeLicence") && GetDaysContinueNationLicence(HOLLAND) >= 40 && bOk) sTemp = ".";
			else 
			{
				if(bOk) 
				{
					if(!CheckCharacterItem(pchar, "HolTradeLicence") || GetDaysContinueNationLicence(HOLLAND) < 40) 
					{
						sTemp = ", as well as a trade license for 40 days."; 
						GiveNationLicence(HOLLAND, 40);
					}
				}
				else // нет флага
				{
					if(!CheckCharacterItem(pchar, "HolTradeLicence")) 
					{
						sTemp = ", as well as a trade license for 40 days. Besides, how are you going to fool the bungler in the fort?! You will let me down one day with such sloppiness... Here you go... You will return it back upon arrival. The new generation, pah...";
						GiveNationLicence(HOLLAND, 40);
						SetCharacterPerk(pchar, "FlagSpa");
						log_info("You have received spanish flag");
						pchar.questTemp.GiveMeSpaFlag = true;
					}
					else // есть лицензия
					{	
						if(GetDaysContinueNationLicence(HOLLAND) < 40) 
						{
							sTemp = ". Tell me, how are you going to fool the bungler in the fort?! Your paper won't help you without the right flag. I feel that you will let me down one day with such sloppiness... Here, a trading license for 40 days, more than yours. As well as the Spanish flag for landing in Maracaibo. You will return it upon arrival. The new generation, pah...";
							GiveNationLicence(HOLLAND, 40);
							SetCharacterPerk(pchar, "FlagSpa");
							log_info("You have received spanish flag");
							pchar.questTemp.GiveMeSpaFlag = true;
						}
						else 
						{
							sTemp = ". Tell me, how are you going to fool the bungler in the fort?! Your paper won't help you without the right flag. I feel that you will let me down one day with such sloppiness... Here you go... You will return it back upon arrival. The new generation, pah...";
							SetCharacterPerk(pchar, "FlagSpa");
							log_info("You have received spanish flag");
							pchar.questTemp.GiveMeSpaFlag = true;
						}
					}
				}
			}
			// <-- legendary edition
            dialog.text = "Then listen closely. Two months ago I had an appointment with a captain by the name of Jean Picard, also known as Jean the Handsome. He didn't show up to the meeting and since I was going to discuss serious matters with him, I did some investigation regarding his whereabouts. Turned out our good brave privateer and his brigantine had managed to engage in a fight with a Spanish heavy galleon under command of don Eduardo de Losad and he is a tough son of a bitch. As a result, Jean and what's left of his crew was taken to Maracaibo and sold to a local plantation. This is where he is, busy with honest labor, at the moment.\nYour tasks are: firstsly - investigate the details of his misfortunes, secondly - get him out from plantation alive and bring him here; I really need details of his story. I am assigning a captain of a barquentine called 'Moray' to assist you in this. Captain's name is Paul Chant also known as Pelly the Cutlass. Remember Geffrey? He is almost as dumb as him, but good at fighting too.\nHe will be waiting for you at cape Ragget Point, on Barbados. Find him and his 'Moray' and sail to Maracaibo. Cutlass will follow your orders without asking stupid questions. Actually, he won't be asking questions at all. Just do your job and come back here, I'll be waiting for you. Here is ten thousand pesos for future expenses"+sTemp+". Any questions?";
			link.l1 = "No. Tutto chiaro. In rotta per Barbados.";
			link.l1.go = "mtraxx_25";
		break;
		
		case "mtraxx_25":
			AddMoneyToCharacter(pchar, 10000);
            dialog.text = "Ti auguro buona fortuna allora. Sii veloce, non fare aspettare Cutlass e il povero Jean.";
			link.l1 = "Certo, capo! Sono in viaggio.";
			link.l1.go = "mtraxx_26";
		break;
		
		case "mtraxx_26":
            DialogExit();
			CloseQuestHeader("Roger_2");
			npchar.dialog.currentnode = "mtraxx_wait";
			// belamour legendary edition по пути могут заскочить к Московиту, если рабов нет
			pchar.questTemp.Mtraxx.GiveMeSlaves = "Baster";
			AddQuestRecord("Roger_3", "1");
			AddLandQuestMark(characterFromId("Fadey"), "questmarkmain");
			AddMapQuestMarkCity("baster", false);
			Mtraxx_PlantBegin();
		break;
		
		case "mtraxx_27":
			pchar.quest.Mtraxx_PlantGoHomeOver.over = "yes"; 
            dialog.text = "Bentornato, mio coraggioso corsaro, ah-ah! Hai abbattuto una squadriglia spagnola? Picard mi ha già raccontato. Ben fatto!";
			link.l1 = "Sì, i miei ragazzi li hanno pestati duro quando stavamo veleggiando via da Maracaibo.";
			link.l1.go = "mtraxx_28";
			if (CheckAttribute(pchar, "questTemp.mtraxx_PlantVykup3"))
			{
				dialog.text = "Bentornato, mio coraggioso corsaro, ah-ah! Picard mi ha già raccontato tutto. Ben fatto!";
				link.l1 = "...";
				link.l1.go = "mtraxx_28";
			}
		break;
		
		case "mtraxx_28":
            dialog.text = "Vedo nei tuoi occhi che aspetti la tua ricompensa. Giusto. Jean ti pagherà, dopotutto era la sua vita che cercavamo di salvare lì. Inviagli una fattura ma più tardi - il ragazzo non ha un equipaggio e una nave. È un ragazzino intelligente proprio come te, quindi il suo stato attuale non durerà a lungo.";
			link.l1 = "Mh... Beh... Aspetterò il mio momento. C'è qualche lavoro per me, Marcus? Senza salvare o cercare nessuno?";
			link.l1.go = "mtraxx_29";
		break;
		
		case "mtraxx_29":
            dialog.text = "Stanco di essere la candela più luminosa? Devo deluderti: ho abbastanza brutes senza cervello come Cutlass, userò i tuoi talenti di conseguenza. Avrò un lavoro per te tra un mese, ora dovresti navigare verso Isla Tesoro e vedere Pasquale Lavoisier, è un mercante di Sharptown.\nHa chiesto di mandargli un pirata duro il prima possibile per un affare serio - molto probabilmente quello che vuoi: meno pensieri e più spari. Hai una settimana per mostrarti a lui, quindi non perdere tempo o perderai questa missione. E sii educato, non cercare di ingannarlo, quest'uomo è rispettato tra i Fratelli. Ora vai e ci vediamo tra un mese. Non essere in ritardo!";
			link.l1 = "Bene Marcus. Ci vediamo!";
			link.l1.go = "mtraxx_30";
		break;
		
		case "mtraxx_30":
            DialogExit();
			// belamour legendary edition забрать флаг обратно
			if(CheckAttribute(pchar, "questTemp.GiveMeSpaFlag")) 
			{
				DeleteAttribute(pchar, "questTemp.GiveMeSpaFlag")); 
				DeleteAttribute(pchar,"perks.list.FlagSpa"); 
				log_info("You have given spanish flag");
			}
			CloseQuestHeader("Roger_3");
			npchar.dialog.currentnode = "mtraxx_wait";
			AddQuestRecord("Roger_4", "1");
			pchar.questTemp.Mtraxx = "pasq_start";
			Mtraxx_PasqualeBegin();
			SetFunctionTimerCondition("Mtraxx_PlantFithTaskTimer", 0, 0, 35, false);
			SaveCurrentNpcQuestDateParam(npchar, "task_date");
		break;
		
		case "mtraxx_31":
            dialog.text = "Accidenti! Un morto è tornato! Ti abbiamo già sepolto, ragazzo! Ma sembra che tu sia ancora vivo";
			link.l1 = "Come puoi vedere, Marco...";
			link.l1.go = "mtraxx_32";
		break;
		
		case "mtraxx_32":
            dialog.text = "Allora perché ci hai messo tanto tempo per arrivare da Maracaibo a Hispaniola? Sei fuori dalla mia organizzazione ora, ragazzo. Sono davvero felice di vederti vivo, ma qui non ci sono più lavori per te.";
			link.l1 = "Eh!.. Che peccato...";
			link.l1.go = "mtraxx_33";
		break;
		
		case "mtraxx_33":
            DialogExit();
            npchar.dialog.currentnode = "First time";
			pchar.questTemp.Mtraxx = "fail";
		break;
		
		case "mtraxx_34x":
            DialogExit();
            npchar.dialog.currentnode = "mtraxx_34";
		break;
		
		case "mtraxx_34":
			/*if (GetNpcQuestPastDayParam(npchar, "task_date") >= 35 && !bImCasual) // опоздал
			{
				dialog.text = "Maledizione "+pchar.name+", dove diavolo sei stato?! Ti ho detto di vedermi in un mese! Questo non è l'esercito ma si prevede un minimo di cazzo di disciplina! Vattene, non lavorerò più con te!";
				link.l1 = "Come desideri...";
				link.l1.go = "mtraxx_33";
				break;
			}*/
			if (GetNpcQuestPastDayParam(npchar, "task_date") < 28) // рано пришёл
			{
				dialog.text = ""+pchar.name+", Ti ho detto 'ci vediamo tra un mese'. Non ho tempo da perdere con te ora.";
				link.l1 = "Bene...";
				link.l1.go = "mtraxx_34x";
				break;
			}
			if (pchar.questTemp.Mtraxx == "pasq_angry")
			{
				dialog.text = "Un agente di Lavoisier mi ha detto che l'hai fregato con il suo legno nero. Ti avevo avvertito di non essere un rattoppiante e di essere leale con Pasquale. Hai infranto entrambe le mie regole. Sei un ragazzino furbo, ma questo è inaccettabile. Vattene all'inferno da qui e dimentica la strada per questo posto.";
				link.l1 = "Merda...";
				link.l1.go = "AngryExitAgainWithOut";
				pchar.questTemp.Mtraxx = "fail";
				npchar.dialog.currentnode = "First time";
				CloseQuestHeader("Roger_4");
				break;
			}
			if (pchar.questTemp.Mtraxx == "pasq_fail")
			{
				dialog.text = "Un agente di Lavoisier mi ha detto che l'hai fottuto con il suo legno nero - non hai portato l'intero lotto. Se fosse stato un Stocco senza cervello o un Calvo, forse avrei creduto che non avessero davvero catturato tutto il carico, ma un ragazzo così astuto come te... Hai deciso di ingannare Pasquale? Ti ho chiesto 'non ingannarlo'! Non ho più fiducia in te, e non ho più affari con te. Vattene all'inferno da qui e dimentica la strada per questo posto!";
				link.l1 = "Il tuo Lavoisier è un topo lui stesso!";
				link.l1.go = "AngryExitAgainWithOut";
				pchar.questTemp.Mtraxx = "fail";
				npchar.dialog.currentnode = "First time";
				CloseQuestHeader("Roger_4");
				break;
			}
			if (pchar.questTemp.Mtraxx == "pasq_late" || pchar.questTemp.Mtraxx == "pasq_sink" || pchar.questTemp.Mtraxx == "pasq_esc")
			{
				pchar.questTemp.Mtraxx.CharleePrince = "true"; // атрибут - ГГ известный пират // правки прогона 3
				dialog.text = "Ah! Charlie Prince, un capitano coraggioso! È il tuo nuovo nome a La Vega nel caso non lo sapessi. Allora, ti è piaciuto fare il bruto? No? La Signora Fortuna ti ha voltato le spalle questa volta? È così che vivono i miei agenti senza cervello come Cutlass: oggi fa festa in un bordello, sperperando tutto quello che ha guadagnato, tra una settimana è alla mia porta a mendicare un paio di migliaia per pagare il suo equipaggio pieno di idioti, proprio come lui. Comunque sia. Parliamo di affari?";
				link.l1 = "Certo!";
				link.l1.go = "mtraxx_36";
				break;
			}
            dialog.text = "Ah! Charlie Prince, un coraggioso capitano! Ah-ah! Un agente di Lavoisier mi ha detto che ti sei comportato bene. Sono contento che tu sia riuscito a mostrare un po' di rispetto al nostro profittatore.";
			link.l1 = "Non gli farebbe male essere più generoso...";
			link.l1.go = "mtraxx_35";
		break;
		
		case "mtraxx_35":
			pchar.questTemp.Mtraxx.Pasquale.Continue = "true"; // правки прогона 3
            dialog.text = "Ricordi cosa ho detto riguardo ai bruti senza cervello e agli acquirenti di merci rubate? Giusto. Non accettare mai un lavoro del genere in futuro. Lascialo a Cutlass e gente come lui. Comunque. Parliamo di affari?";
			link.l1 = "Certo!";
			link.l1.go = "mtraxx_36";
		break;
		
		case "mtraxx_36":
            dialog.text = "Bene! Jean Picard sta arrivando qui, ti dirà di più. Tu e Jean lavorerete insieme a questa missione. Inoltre, è la sua occasione per ripagare il suo debito con te... Eccolo!";
			link.l1 = "...";
			link.l1.go = "mtraxx_37";
		break;
		
		case "mtraxx_37":
            DialogExit();
            npchar.dialog.currentnode = "mtraxx_38";
			chrDisableReloadToLocation = true;
			// преобразуем Пикара
			sld = characterFromId("Mrt_Rocur");
			sld.model = "Jan_Pikar";
			SetCharacterPerk(sld, "SwordplayProfessional");
			SetCharacterPerk(sld, "GunProfessional");
			RemoveCharacterEquip(sld, BLADE_ITEM_TYPE);
			RemoveCharacterEquip(sld, GUN_ITEM_TYPE);
			GiveItem2Character(sld, "blade_17");
			EquipCharacterbyItem(sld, "blade_17");
			GiveItem2Character(sld, "pistol6");
			EquipCharacterbyItem(sld, "pistol6");
			TakeNItems(sld, "cartridge", 40);
			LAi_SetCharacterUseBullet(sld, GUN_ITEM_TYPE, "cartridge");
			GiveItem2Character(sld, "cirass7");
			EquipCharacterbyItem(sld, "cirass7");
			sld.dialog.currentnode = "rocur_29";
			sld.greeting = "Rocur_03";
			Characters_RefreshModel(sld);
			LAi_SetCheckMinHP(sld, 10, true, "");
			TakeNItems(sld, "potion2", 7);
			TakeNItems(sld, "potion3", 7);
			TakeNItems(sld, "potion4", 7);
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "mtraxx_38":
            dialog.text = "Il mio ragazzo si unirà alla tua incursione. Si chiama Luka Bayard, meglio noto come Luke Leprechaun. Lui e i suoi uomini sono bucanieri - cacciatori che hanno trascorso la maggior parte della loro vita a cacciare nelle foreste di Hispaniola. Quindi sono maestri nel muoversi attraverso la giungla, aggiungi a loro i tuoi combattenti e considera Merida come tua. Prenderai la terza parte del bottino. Il resto sarà preso da Jean.\nJean, darai il tuo debito a questo coraggioso capitano dalla tua quota, poi porterai quello che resta a me. Risolveremo tra noi poi. Domande? Splendido! Leprechaun ti aspetterà nel nostro porto. Buona fortuna corsari, ah-ah!";
			link.l1 = "...";
			link.l1.go = "mtraxx_39";
		break;
		
		case "mtraxx_39":
            DialogExit();
			CloseQuestHeader("Roger_4");
			npchar.dialog.currentnode = "mtraxx_wait";
			AddQuestRecord("Roger_5", "1");
			pchar.questTemp.Mtraxx = "merida_start";
			Mtraxx_MeridaBegin();
			LAi_SetHuberType(npchar);
			sld = characterFromId("Mrt_Rocur");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "Mtraxx_MeridaAddPicar", 5.0);
			pchar.GenQuest.HunterLongPause = true;
		break;
		
		case "mtraxx_40":
            dialog.text = "Bentornato, mio coraggioso tagliagole! Le voci del tuo raid ci sono già giunte.";
			link.l1 = "Non posso dire che mi piace sentirlo. Queste cose è meglio che rimangano sconosciute...";
			link.l1.go = "mtraxx_41";
		break;
		
		case "mtraxx_41":
            dialog.text = "Fidati di me, non lo sono mai, amico mio. Comunque. Ha Picard estinto il suo debito con te?";
			link.l1 = "Sì.";
			link.l1.go = "mtraxx_42";
		break;
		
		case "mtraxx_42":
            dialog.text = "Molto bene. Luke Leprechaun ha fatto una buona impressione su di te?";
			link.l1 = "L'ha fatto.";
			link.l1.go = "mtraxx_43";
		break;
		
		case "mtraxx_43":
            dialog.text = "Perfetto allora. Tutti sono felici, tutti sono pagati.";
			link.l1 = "Hai un lavoro per me, Marcus?";
			link.l1.go = "mtraxx_44";
			// belamour legendary edition отказ после событий Мериды
			link.l2 = "Sai, Marcus, ho ponderato tutto e questo lavoro non fa per me. Mi dispiace, ma ho già preso una decisione.";
			link.l2.go = "mtraxx_44a";
		break;
		
		case "mtraxx_44":
            dialog.text = "Nessun vero lavoro per ora. Anche se ho un favore personale da chiedere. Interessato?";
			link.l1 = "Certo capo. Che favore?";
			link.l1.go = "mtraxx_45";
		break;
		
		case "mtraxx_45":
            dialog.text = "C'è una pinaccia 'Kittie' vicino alle coste di La Vega. È lì da giorni in attesa di una scorta per Bridgetown. Non c'è modo che la lasci navigare da sola per motivi ovvi. Saresti così gentile da accompagnarla? Avrò un vero lavoro per te quando tornerai. E, ovviamente, denaro per pagarti per questa scorta.";
			link.l1 = "Affare fatto.";
			link.l1.go = "mtraxx_46";
		break;
		
		case "mtraxx_46":
            dialog.text = "Bene! Buona navigazione.";
			link.l1 = "Grazie!";
			link.l1.go = "mtraxx_47";
		break;
		
		case "mtraxx_47":
            DialogExit();
			sld = characterFromId("Mrt_Rocur");
			RemovePassenger(pchar, sld);
			sld = characterFromId("Lepricon");
			RemovePassenger(pchar, sld);
			LAi_SetWarriorType(sld);
			ChangeCharacterAddressGroup(sld, "none", "", "");
			CloseQuestHeader("Roger_5");
			npchar.dialog.currentnode = "mtraxx_wait";
			AddQuestRecord("Roger_6", "1");
			pchar.questTemp.Mtraxx = "ignasio_start";
			sld = characterFromId("Mtr_KittyCap");
			DeleteAttribute(sld, "DontDeskTalk");
			LocatorReloadEnterDisable("LaVega_port", "boat", false);
		break;
		// belamour legendary edition -->
		case "mtraxx_44a":
            dialog.text = "Cosa?! Ti ho tirato fuori dalla strada, ho riempito le tue tasche di ambra e gemme! È così che mi ripaghi?";
			link.l1 = "Merida mi ha mostrato che non sono abbastanza spietato per questo lavoro. Non tanto quanto te e i tuoi uomini. Non essere cattivo.";
			link.l1.go = "mtraxx_45a";
		break;
		
		case "mtraxx_45a":
            dialog.text = "Debole! Beh, sparisci! Vai a lavorare come un mulo sulla merce o, ancora meglio, ubriacati a morte come il resto dei perdenti!";
			link.l1 = "...";
			link.l1.go = "mtraxx_46a";
		break;
		
		case "mtraxx_46a":
            DialogExit();
			sld = characterFromId("Mrt_Rocur");
			RemovePassenger(pchar, sld);
			sld = characterFromId("Lepricon");
			RemovePassenger(pchar, sld);
			LAi_SetWarriorType(sld);
			ChangeCharacterAddressGroup(sld, "none", "", "");
			CloseQuestHeader("Roger_5");
			npchar.dialog.currentnode = "First time";
			Group_DelCharacter("Mtr_Kitty", "Mtr_KittyCap");
			sld = characterFromId("Mtr_KittyCap");
			sld.lifeday = 0;
			LocatorReloadEnterDisable("LaVega_port", "boat", false);
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			pchar.questTemp.Mtraxx = "fail";
			if(CheckAttribute(pchar, "GenQuest.HunterLongPause")) DeleteAttribute(pchar, "GenQuest.HunterLongPause");
			DoQuestReloadToLocation("LaVega_town", "reload", "reload6", ""); // выставим за дверь
		break;
		// <--- legendary edition
		case "mtraxx_48":
			AddMoneyToCharacter(pchar, 10000);
            dialog.text = "Ah, eccoti... Ti stavo già aspettando. Ecco 10.000 per l'escort della 'Kittie'.";
			link.l1 = "Grazie... Ho qualcosa di cui discutere con te, Marcus.";
			link.l1.go = "mtraxx_49";
		break;
		
		case "mtraxx_49":
            dialog.text = "Davvero?! Ah-ah! Sparati!..";
			link.l1 = "Ricordi come Jean Picard è stato ridotto in schiavitù? Prima, ha saccheggiato una carovana olandese insieme a un corsaro britannico e poi lo stesso gli è stato fatto da una pesante galeone spagnola.";
			link.l1.go = "mtraxx_50";
		break;
		
		case "mtraxx_50":
            dialog.text = "Ricorda. E poi?";
			link.l1 = "Sono stato avvicinato a Bridgetown da Ignacio Marco. Lo stesso corsaro portoghese al servizio dell'Inghilterra. Mi ha offerto di saccheggiare una carovana olandese vicino alle coste di un'isola abitata tra Curacao e Trinidad.";
			link.l1.go = "mtraxx_51";
		break;
		
		case "mtraxx_51":
            dialog.text = "Bene-bene... Sei d'accordo?";
			link.l1 = "L'ho fatto. Prima di tutto, è stato un buon affare. In secondo luogo, ho ricordato la storia di Picard e ho deciso di indagare...";
			link.l1.go = "mtraxx_52";
		break;
		
		case "mtraxx_52":
            dialog.text = "Scommetto che l'hai fatto.";
			link.l1 = "Sì. C'era un caravan, abbiamo fatto il lavoro bello e pulito. Poi abbiamo diviso il bottino a terra, ma prima ho mandato in silenzio un guardiano con un cannocchiale su una collina. E ha dato i suoi frutti perché poco dopo è apparsa una squadra spagnola guidata da un pesante galeone.";
			link.l1.go = "mtraxx_53";
		break;
		
		case "mtraxx_53":
            dialog.text = "Il tuo compagno è sicuramente fuggito così gli spagnoli ti hanno inseguito?";
			if (CheckAttribute(pchar, "questTemp.Mtraxx.LosadaSink")) 
			{
				link.l1 = "Esatto. Non gli hanno nemmeno prestato attenzione. Peccato per loro: abbiamo combattuto così duramente contro gli spagnoli che non lo dimenticheranno mai. Questi Castigliani erano buoni combattenti, ma siamo riusciti a far cadere l'intera squadriglia.";
				link.l1.go = "mtraxx_53x";
			}
			else
			{
				link.l1 = "Esattamente. Non gli hanno nemmeno prestato attenzione. Anche se sono riuscito a scappare. Grazie al mio guardiano...";
				link.l1.go = "mtraxx_53y";
			}
		break;
		
		case "mtraxx_53x":
			DeleteAttribute(pchar, "questTemp.Mtraxx.LosadaSink");
            dialog.text = "Ehi! Hai abbattuto uno squadrone di Eduardo de Losad! Sei un Diavolo del Mare, Principe! Scommetto che gli spagnoli hanno già mandato cacciatori al tuo sedere.";
			link.l1 = "Male per loro... Ciononostante dovremmo occuparci di questa feccia Ignacio. Se capisci cosa intendo.";
			link.l1.go = "mtraxx_54";
		break;
		
		case "mtraxx_53y":
            dialog.text = "Eh! Posso solo immaginare la tempesta di merda che è scoppiata quando i Castigliani hanno realizzato che sei scappato da loro! Ben fatto!";
			link.l1 = "Il loro problema, non il mio. Ciononostante dovremmo occuparci di questa feccia di Ignacio. Se capisci cosa intendo.";
			link.l1.go = "mtraxx_54";
		break;
		
		case "mtraxx_54":
            dialog.text = "Me ne occuperò. Dovremmo saperne di più su questo Ignacio Marco. Potrebbe lavorare per qualcuno. Il suo 'interesse' per i miei uomini è sospetto. Che nave possiede?";
			link.l1 = "Una polacca, la 'Torero'. Una nave unica, deve essere un design originale.";
			link.l1.go = "mtraxx_55";
		break;
		
		case "mtraxx_55":
            dialog.text = "Bene, sarà più facile rintracciarla così... Ho capito. E per te, Principe, ho un lavoro. Sei pronto?";
			link.l1 = RandSwear()+"Certo, capo!";
			link.l1.go = "mtraxx_56";
		break;
		
		case "mtraxx_56":
            dialog.text = "Ascolta allora. Un po' di tempo fa abbiamo avuto un curioso pirata nella nostra zona. Si chiama Wulfric Iogansen, noto anche come Lupo Rosso. Un personaggio molto colorato. È arrivato qui dal Nord Europa un paio di anni fa. Questo vichingo non pagava a Levasseur la sua tassa di protezione, non si è fatto amici e è rimasto da solo. Un tipo molto riservato, nessuno è mai uscito vivo dalla sua ciurma. C'erano voci che lui personalmente tagliava la lingua a quelli della sua ciurma che parlavano troppo nelle taverne dei loro raid...\nA differenza della maggior parte dei nostri simili, Wulfric non ha mai sprecato soldi in puttane o bevande. Non ha mai venduto il suo bottino per pochi spiccioli. Non ha mai fidato i banchieri e non ha mai cambiato navi. Aveva una bella corvetta, la 'Freyja' e un equipaggio leale che pagava bene per il servizio e per il silenzio. Credo che stesse progettando di accumulare più oro possibile e poi tornare in Europa e vivere lì come un re.\nNon gli è andata bene grazie ai cacciatori spagnoli. Quest'uomo aveva inflitto danni e perdite colossali alla Spagna, così le spedizioni punitive lo hanno inseguito nelle acque dell'Hispaniola e hanno affondato la 'Freyja' e ucciso tutta la ciurma insieme al Lupo. Circondato in acque basse dalle navi spagnole, il Lupo Rosso ha incontrato la sua morte.\nLa questione è che tutti a La Vega sapevano dei tesori del Lupo e hanno anche trovato una 'Freyja' affondata, ma né i locali né i subacquei indiani hanno trovato alcun tesoro. Non era uno stupido e deve aver avuto un enorme nascondiglio da qualche parte in quel luogo che solo lui e la sua ciurma conoscevano, ma non possiamo chiedere loro per... motivi ovvi. Ma ora viene la parte interessante: ho il suo registro di bordo intatto, che era nascosto in un baule chiuso a chiave sulla sua nave. Non ha indizi ovvi sul tesoro ma tu potresti cercare di trovarli tra le parole. Leggi il registro, scopri dove il vichingo ha nascosto i suoi tesori dopo due anni di rapine nei Caraibi e trovali. Se riesci - due terzi sono tuoi. Sei dentro?";
			link.l1 = "Hm... sembra come cercare un gatto nero in una stanza buia. Dov'è il registro?";
			link.l1.go = "mtraxx_57";
		break;
		
		case "mtraxx_57":
            dialog.text = "Eccolo, prendilo. Buona fortuna!";
			link.l1 = "Grazie, ne avrò bisogno...";
			link.l1.go = "mtraxx_58";
		break;
		
		case "mtraxx_58":
            DialogExit();
			CloseQuestHeader("Roger_6");
			npchar.dialog.currentnode = "mtraxx_wait";
			GiveItem2Character(pchar, "wolfreeks_book");
			AddQuestRecord("Roger_7", "1");
			pchar.questTemp.Mtraxx = "wolfreek_start";
			pchar.questTemp.Mtraxx.Logbook.CanRead = "true";
			pchar.questTemp.Mtraxx.Logbook.Page1 = "true";
			bQuestDisableMapEnter = true;//закрыть карту
			pchar.GenQuest.MapClosedNoBattle = true;
		break;
		
		case "mtraxx_59":
            dialog.text = "Ah, ecco il nostro coraggioso capitano. Che ne è dei tesori del Lupo Rosso?";
			link.l1 = "Sto lavorando su di esso. Ho bisogno del tuo aiuto in questo.";
			link.l1.go = "mtraxx_60";
		break;
		
		case "mtraxx_60":
            dialog.text = "Sono tutto orecchie.";
			link.l1 = "C'è una parola sconosciuta per me scritta diverse volte nel registro di Wulfric 'Gord'. Devo conoscerne il significato per avanzare nelle mie indagini.";
			link.l1.go = "mtraxx_61";
		break;
		
		case "mtraxx_61":
            dialog.text = "Hm... Gord, dici... Non l'ho mai sentito prima d'ora. Molto bene, vediamoci tra una settimana: mi consulterò con alcuni cervelloni che fanno da scrivani sulle navi. Almeno sanno come contare e leggere. Potrebbero darci qualche idea.";
			link.l1 = "Bene Marcus. Ci vediamo in una settimana allora.";
			link.l1.go = "mtraxx_62";
		break;
		
		case "mtraxx_62":
            DialogExit();
			npchar.dialog.currentnode = "mtraxx_wait";
			SetFunctionTimerCondition("Mtraxx_WolfreekTimer", 0, 0, 7, false);
		break;
		
		case "mtraxx_63":
            dialog.text = "Ho una risposta per te. Un furbo mi ha illuminato. Gord è un insediamento fortificato di un jarl libero.";
			link.l1 = "Un jarl libero? Chi è quello?";
			link.l1.go = "mtraxx_64";
		break;
		
		case "mtraxx_64":
            dialog.text = "Una sorta di ammiraglio pirata dei Vichinghi. Ad esempio, io sono un jarl libero e La Vega è il mio gord. Sembra che Lupo Rosso si sia divertito con la storia dei suoi antenati, ah-ah! Queste informazioni ti sono state utili?";
			link.l1 = "Non lo so ancora. Dovrei confrontare le note prima. Gord significa insediamento allora... Grazie Marcus!";
			link.l1.go = "mtraxx_65";
		break;
		
		case "mtraxx_65":
            DialogExit();
			npchar.dialog.currentnode = "mtraxx_wait";
			Mtraxx_WolfreekReadLogbookFourth();
		break;
		
		case "mtraxx_66":
            dialog.text = "Allora? La tua faccia compiaciuta mi dice che hai avuto successo.";
			link.l1 = "Sì. Il tesoro del Lupo Rosso è stato trovato! Non è stato però facile.";
			link.l1.go = "mtraxx_67";
		break;
		
		case "mtraxx_67":
            dialog.text = "Quanto ha accumulato il nostro vichingo?";
			link.l1 = "750.000 pesos e 900 dobloni.";
			link.l1.go = "mtraxx_68";
		break;
		
		case "mtraxx_68":
            dialog.text = "Oho! Hai fatto bene Principe. E la mia parte?";
			if (sti(pchar.money) >= 250000 && PCharDublonsTotal() >= 300) // belamour legendary edition
			{
				link.l1 = "Ecco, prendi questo. Secondo il nostro accordo: 250 000 pesos e 300 dobloni.";
				link.l1.go = "mtraxx_69";
			}
			else
			{
				link.l1 = "Tutti i pesos e i dobloni sono nella mia cabina. Dammi un minuto per portarli qui!";
				link.l1.go = "mtraxx_68_1";
			}
		break;
		
		case "mtraxx_68_1":
            DialogExit();
			npchar.dialog.currentnode = "mtraxx_68_2";
		break;
		
		case "mtraxx_68_2":
            dialog.text = "Hai portato la mia parte?";
			if (sti(pchar.money) >= 250000 && PCharDublonsTotal() >= 300) // belamour legendary edition
			{
				link.l1 = "Ecco, prendi questo. Secondo il nostro accordo: 250 000 pesos e 300 dobloni.";
				link.l1.go = "mtraxx_69";
			}
			else
			{
				link.l1 = "Sì, sì, sono sulla mia strada!";
				link.l1.go = "mtraxx_68_1";
			}
		break;
		
		case "mtraxx_69":
			AddMoneyToCharacter(pchar, -250000);
			RemoveDublonsFromPCharTotal(300); // belamour legendary edition
			PlaySound("interface\important_item.wav");
            dialog.text = "Molto bene. Hai fatto di nuovo un ottimo lavoro. Ben fatto!";
			link.l1 = "Marcus, hai scoperto qualcosa su Ignacio Marco?";
			link.l1.go = "mtraxx_70";
			// mitrokosta возможность отстройки исламоны
			pchar.questTemp.IslaMona = "start";
		break;
		
		case "mtraxx_70":
            dialog.text = "Sì, ma devo verificarlo prima...";
			link.l1 = "Cosa?";
			link.l1.go = "mtraxx_71";
		break;
		
		case "mtraxx_71":
            dialog.text = "Nutro il sospetto che Marco sia collegato a qualcuno... E ho bisogno che tu lo scopra. Naviga verso la Martinica. Lascia la tua nave a Saint Pierre e raggiungi Le Francois attraverso la giungla. Mi è stato detto che il nostro uomo è stato visto lì. Non chiedere ai pirati in giro, guarda e osserva soltanto. Una volta trovato l'uomo, seguitelo e vedi dove andrà o con chi si sta incontrando. Non attaccarlo o la sua nave perché così facendo rovineresti un piano che sto preparando proprio ora! Ti ho avvertito!\nSeguilo e osservalo, torna da me una volta che hai appreso abbastanza. Capisco che le tue mani bramino di strangolare quel bastardo ma mantieni la mente lucida. Ora vai. Hai tre settimane. Buona fortuna.";
			link.l1 = "Sulla mia strada, capo.";
			link.l1.go = "mtraxx_72";
		break;
		
		case "mtraxx_72":
            DialogExit();
			CloseQuestHeader("Roger_7");
			RemoveItems(pchar, "wolfreeks_book", 1);
			npchar.dialog.currentnode = "mtraxx_wait";
			AddQuestRecord("Roger_8", "1");
			pchar.questTemp.Mtraxx = "corrida_start";
			pchar.quest.mtraxx_corrida_martinique.win_condition.l1 = "location";
			pchar.quest.mtraxx_corrida_martinique.win_condition.l1.location = "Martinique";
			pchar.quest.mtraxx_corrida_martinique.function = "Mtraxx_CorridaStart";
			pchar.quest.mtraxx_pasq_continue.win_condition.l1 = "location";
			pchar.quest.mtraxx_pasq_continue.win_condition.l1.location = "LaVega_exittown";
			pchar.quest.mtraxx_pasq_continue.function = "Mtraxx_PasqualeJan";
			bDisableFastReload = true;
			//SaveCurrentNpcQuestDateParam(npchar, "task_date");
		break;
			
		case "mtraxx_73":
			/*if (GetNpcQuestPastDayParam(npchar, "task_date") >= 22) // опоздал
			{
				dialog.text = "Maledetto Principe! Avresti potuto avere vendetta e una somma di denaro infernale se non fossi stato così lento! Non me lo aspettavo da te, ma siccome sei un bravo ragazzo ti perdono. Avrai l'opportunità di riconquistare la tua reputazione ai miei occhi in un mese. Sto radunando tutti per un raid!\nVieni da me tra un mese su una nave singola ma potente. Anche Luke, Cutlass, Geffrey e Jean parteciperanno a questo. Non fare tardi, nemmeno per un giorno!";
				link.l1 = "Capisco, Marcus. Non succederà di nuovo!";
				link.l1.go = "mtraxx_73x";
				break;
			}*/
			dialog.text = "Ottimo tempismo! Fatti avanti e rendicontami, ora.";
			link.l1 = "Ho rintracciato il mio debitore a Le Francois. La sua polacca faceva parte di una squadra composta da una corvetta e una fregata. Marco stesso stava facendo visita a Barbaszon, hanno avuto un incontro a casa sua per due ore, gli altri visitatori sono stati allontanati dalle sue guardie. Poi è uscito di casa con due tizi cupi: uno era roscio e barbuto in un corpetto da reiter, l'altro aveva i baffi e indossava una pesante armatura da trincea. Tutti sono andati al porto e hanno salpato prima che arrivassi a Saint Pierre.";
			link.l1.go = "mtraxx_74";
		break;
		
		/*case "mtraxx_73x":
            DialogExit();
            npchar.dialog.currentnode = "First time";
			pchar.questTemp.Mtraxx = "wait_month";
			AddQuestRecord("Roger_8", "5");
			SetFunctionTimerCondition("Mtraxx_CartahenaTavernPrepare", 0, 0, 1, false); // belamour legendary edition увеличим таймер 
			SetFunctionTimerCondition("Mtraxx_CartahenaPrepare", 0, 0, 1, false);
			SetFunctionTimerCondition("Mtraxx_CartahenaLate", 0, 0, 92, false);
		break;*/
		
		case "mtraxx_74":
            dialog.text = "Va bene. Ora vedo l'intera situazione. Questi due bastardi che hai visto lavorano o per Barbazon o per Jackman. Sono quasi come il mio Calvo e Scimitarra, ma combattono meglio. Il roscio si chiama Prowler, è il capitano del 'Cuttlefish', una corvetta, e il tipo con i baffi è Ghoul, naviga il 'Merciless', una fregata. Per quanto riguarda il nostro amico Ignacio - sta lavorando non solo per i britannici e lo spagnolo don Losad, ma anche per Barbazon. Ecco perché ha cercato di incastrarti e Picard.";
			link.l1 = "Perché?";
			link.l1.go = "mtraxx_75";
		break;
		
		case "mtraxx_75":
            dialog.text = "Ordine di Barbazon. Non lo sapevi ma Jacques non perde mai l'occasione di pisciarmi nella zuppa. Non mi avrebbe mai osteggiato apertamente per ovvi motivi, quindi mi fa inciampare di nascosto. Sapeva che Picard e tu siete miei uomini. Mandare il suo mercenario contro di te è nel suo stile e non ha mandato un idiota, come hai potuto constatare.";
			link.l1 = "Andrò a trovare Barbazon non appena avrò sistemato Marco...";
			link.l1.go = "mtraxx_76";
		break;
		
		case "mtraxx_76":
            dialog.text = "Togliti queste stronzate dalla testa! Non hai nessuna possibilità contro Barbazon in un conflitto aperto. Lui ti fottrebbe facilmente. Lo ripagheremo con i suoi stessi trucchi - colpendo i suoi associati. Pronto a farlo? È un affare sporco.";
			link.l1 = "Sembra il mio tipo di affare!";
			link.l1.go = "mtraxx_77";
		break;
		
		case "mtraxx_77":
            dialog.text = "Ignacio Marco, Prowler, Goul e un altro ragazzo di Barbazon chiamato Joker Jim hanno un piano per catturare una delle navi spagnole della Flotta d'Oro. L'intera operazione è stata progettata da Barbazon stesso ed io sono riuscito a scoprire i dettagli dai miei spie. Un pesante galeone della flotta d'oro si è attardato ad Havana nel cantiere navale, mentre l'intera squadra è partita per la Spagna. Il Galeone è stato riparato e si dirigerà presto verso l'Europa, insieme ad altre due navi. La squadra andrà da Cuba al nord-est, ma non so quale sia la rotta.\nSono stato informato che le navi spagnole stavano per salpare per Santo Domingo, poi lungo le coste di Porto Rico e direttamente nell'oceano. Anche Barbazon lo sa. Tuttavia, poiché Hispaniola può essere aggirata non solo da sud, ma anche da nord, cambiando la rotta, e partendo per l'oceano attraverso Turks, o Isla-Tesoro, senza entrare a Santo Domingo, Jacques ha deciso di giocare sul sicuro e ha mandato l'astuta volpe Ignacio a Cuba.\nMarco ha il compito di ottenere un programma di navigazione del galeone spagnolo che sta per salpare da Cuba e dovrebbe raggiungere il resto della Flotta più tardi. Ha connessioni all'interno degli spagnoli quindi questo compito non sarà un problema per lui. Il resto della banda di Barbazon sta aspettando Marco a Saint Martin che è un luogo ottimale per iniziare a cacciare questo premio. Poiché Marco e gli olandesi non sono molto amici, non sarà in grado di entrare nelle acque di Saint Martin, quindi dovrà inviare ai suoi compagni un messaggio a distanza...";
			link.l1 = "Immagino di sapere cosa devo fare qui...";
			link.l1.go = "mtraxx_78";
		break;
		
		case "mtraxx_78":
            dialog.text = "Mi colpisce come tu sia così intelligente, ma non ho ancora finito. Ho interferito con questo piano con l'aiuto di Gabriela Chapada. La conosci. Insieme abbiamo informato gli spagnoli che l'imboscata dei pirati sarà allestita non lontano da Puerto Rico. Quindi il galeone non navigherà in quella zona, ma invece hanno inviato segretamente uno squadrone di cacciatori di pirati. Hai una serie di compiti. Il primo sarà trovare e catturare il 'Torero'. Immagino che tu sappia cosa fare con il suo capitano.";
			link.l1 = "Certo...";
			link.l1.go = "mtraxx_79";
		break;
		
		case "mtraxx_79":
            dialog.text = "In secondo luogo, dovrai scoprire il vero percorso del galeone dorato spagnolo. Marco deve avere il suo programma. Ottienilo e inviamelo.";
			link.l1 = "Come?";
			link.l1.go = "mtraxx_80";
		break;
		
		case "mtraxx_80":
			GiveItem2Character(pchar, "Dove"); 
            dialog.text = "Per via aerea. Prendi una gabbia... Questo è Spyke, un piccione viaggiatore nato e cresciuto qui, a La Vega. Troverà sempre la strada per tornare qui, anche da Trinidad. Una volta ottenuto il programma, scrivi un biglietto, attaccalo alla sua gamba e liberalo. Spyke volerà da me in poche ore. Abbi cura di lui, Principe!";
			link.l1 = "Certo, capo!";
			link.l1.go = "mtraxx_81";
		break;
		
		case "mtraxx_81":
            dialog.text = "Terzo, salpa per Saint Martin sulla 'Torero'. Solo su di lei! Altrimenti si insospettiranno troppo presto. Manda loro un segnale per salpare verso Puerto Rico dove aspettano gli spagnoli. I loro codici di segnale devono essere nei documenti di Marco. O puoi impararli da lui personalmente.";
			link.l1 = "Capisco. Una mossa astuta inviare gli uomini di Barbazon agli spagnoli, ah-ah!";
			link.l1.go = "mtraxx_82";
		break;
		
		case "mtraxx_82":
            dialog.text = "Esattamente! Gli infliggerò un colpo dalle ombre. Proprio come ha fatto lui. E un'ultima cosa: una volta inviato il segnale, dirigi immediatamente verso il galeone spagnolo e la sua scorta. Non ci sarà tempo da perdere.";
			link.l1 = "Su una polacca? Contro un pesante galeone e altre due navi, e certamente non golette? Mi strapperanno a pezzi!";
			link.l1.go = "mtraxx_83";
		break;
		
		case "mtraxx_83":
            dialog.text = "Smetti di piangere come una bambina! Perché pensi che mi manderai Spyke? Non resterai senza rinforzi. Basta non lasciare che la carovana fugga, non lasciarli arrivare all'oceano. Capito?";
			link.l1 = "Sì, capo.";
			link.l1.go = "mtraxx_84";
		break;
		
		case "mtraxx_84":
            dialog.text = "La tua ricompensa sarà un pesante carico d'oro più la polacca di Marco. Si dice che sia una dannata buona nave. Domande? Capisci la tua missione?";
			link.l1 = "Non sono Cutlass, so cosa fare. Dove dovrei intercettare il 'Torero'?";
			link.l1.go = "mtraxx_85";
		break;
		
		case "mtraxx_85":
            dialog.text = "Mentre stiamo facendo questa chiacchierata, la nave sta navigando rapidamente verso Philipsburg da Cuba. Dovrebbe essere intorno a Tortuga ora o un po' a est da essa. Quindi alza le ancore e naviga verso Saint Martin, cattura il 'Torero' non lontano dall'isola, solo non lasciare che gli uomini di Barbazon vedano la lotta, altrimenti il mio piano è rovinato.";
			link.l1 = "Subito!";
			// belamour legendary edition испанский флаг к выдаче -->
			if(IsCharacterPerkOn(pchar,"FlagSpa")) link.l1.go = "mtraxx_86";
			else link.l1.go = "mtraxx_85f";
		break;
		
		case "mtraxx_85f":
			SetCharacterPerk(pchar, "FlagSpa");
			log_info("You have received a spanish flag");
			pchar.questTemp.GiveMeSpaFlag = true;
            dialog.text = "Che diavolo? Ti spaccherei con un attizzatoio del camino, Principe. Non pensavo che avrei dovuto parlare di cose elementari. Tieni la bandiera spagnola, altrimenti farai fallire tutto, senza nemmeno iniziare. Ridammela. Ora vattene da qui!";
			link.l1 = "Sono già in mare, Capo";
			link.l1.go = "mtraxx_86";
		break;
		// <-- legendary edition
		case "mtraxx_86":
            DialogExit();
			npchar.dialog.currentnode = "mtraxx_wait";
			DeleteAttribute(pchar, "GenQuest.CannotWait");
			AddQuestRecord("Roger_8", "6");
			pchar.questTemp.Mtraxx = "corrida_marko";
			/*pchar.quest.mtraxx_corrida_landtimer.win_condition.l1 = "Timer";
			pchar.quest.mtraxx_corrida_landtimer.win_condition.l1.date.hour  = sti(GetTime()+1);
			pchar.quest.mtraxx_corrida_landtimer.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.mtraxx_corrida_landtimer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.mtraxx_corrida_landtimer.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.mtraxx_corrida_landtimer.function = "Mtraxx_CorridaLandTimer";
			pchar.quest.mtraxx_corrida_checktime.win_condition.l1 = "location";
			pchar.quest.mtraxx_corrida_checktime.win_condition.l1.location = "Hispaniola1";
			pchar.quest.mtraxx_corrida_checktime.function = "Mtraxx_CorridaCheckTime";*/
			pchar.quest.mtraxx_corrida_torero.win_condition.l1 = "Timer";
			pchar.quest.mtraxx_corrida_torero.win_condition.l1.date.hour  = sti(GetTime()+12);
			pchar.quest.mtraxx_corrida_torero.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.mtraxx_corrida_torero.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.mtraxx_corrida_torero.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.mtraxx_corrida_torero.function = "Mtraxx_CorridaToreroOnMap";
			SetFunctionTimerCondition("Mtraxx_CorridaTimeFindTorero", 0, 0, 7, false); // время на перехват Тореро, снимать при потоплении или захвате
		break;
		
		case "mtraxx_87":
            dialog.text = "Allora Principe, hai rovinato tutto, eh?";
			link.l1 = "L'ho fatto. Questa missione era una sfida molto più grande di quanto pensassi. Puoi darmi un discorso infuriante e mostrarmi la porta.";
			link.l1.go = "mtraxx_88";
		break;
		
		case "mtraxx_88": // belamour legendary edition увеличиваем срок
            dialog.text = "Dai, smettila. Succede. Sei un buon corsaro e tutti sbagliamo a volte. Peccato che non abbiamo preso quel oro... ma se non l'abbiamo preso in un posto, dovremmo farlo da un altro, ah-ah! Avrai l'opportunità di riconquistare la tua reputazione: vieni da me tra tre settimane, e preferibilmente su una nave più potente, ma solo su una - saremo un'intera squadra. Sto radunando tutti per una incursione!\nVieni da me tra tre settimane su una nave singola ma potente. Anche Luke, Cutlass, Geffrey e Jean parteciperanno. Non fare tardi!";
			link.l1 = "Non comanderò!";
			link.l1.go = "mtraxx_89";
		break;
		
		case "mtraxx_89":
            DialogExit();
			// belamour legendary edition забрать флаг обратно
			if(CheckAttribute(pchar, "questTemp.GiveMeSpaFlag")) 
			{
				DeleteAttribute(pchar, "questTemp.GiveMeSpaFlag")); 
				DeleteAttribute(pchar,"perks.list.FlagSpa"); 
				log_info("You have given a spanish flag");
			}
			npchar.dialog.currentnode = "First time";
			pchar.questTemp.Mtraxx = "wait_month";
			AddQuestRecord("Roger_8", "22");
			SetFunctionTimerCondition("Mtraxx_CartahenaTavernPrepare", 0, 0, 1, false); // belamour legendary edition увеличим таймер 
			SetFunctionTimerCondition("Mtraxx_CartahenaPrepare", 0, 0, 1, false);
			//SetFunctionTimerCondition("Mtraxx_CartahenaLate", 0, 0, 92, false);
			if (CheckCharacterItem(pchar, "Dove")) RemoveItems(pchar, "Dove", 1);
		break;
		
		case "mtraxx_board":
            dialog.text = "Oho, Ahoy, ragazzo! Non ti aspettavi di vedermi qui, vero? Ah-ah-ah! Abbiamo trovato la carovana spagnola dopo tutto...";
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Corrida.Gold")) // был абордаж
			{
				link.l1 = "Sì capo, ci siamo riusciti, anche se non è stato facile.";
				link.l1.go = "mtraxx_board_1";
			}
			else
			{
				link.l1 = "Sì, ma il galeone d'oro è affondato con tutto il suo oro.";
				link.l1.go = "mtraxx_board_7";
			}
		break;
		
		case "mtraxx_board_1":
			iTotalTemp = GetSquadronGoods(pchar, GOOD_GOLD);
            dialog.text = "Quanto oro abbiamo preso, Principe?";
			if (iTotalTemp < 1) link.l1 = "Eh... Niente.";
			else link.l1 = "Eh... "+iTotalTemp+" in totale!";
			link.l1.go = "mtraxx_board_2";
		break;
		
		case "mtraxx_board_2":
			if (iTotalTemp < 20)
			{
				dialog.text = "Maledizione! Gli spagnoli devono averlo gettato in mare per far sì che non lo prendessimo. Almeno hanno pagato per questo. Così come gli uomini di Barbazon, che è anche una vittoria...";
				link.l1 = "Scusa per l'oro... Cosa succede dopo Marcus? Andiamo a La Vega?";
				link.l1.go = "mtraxx_board_4";
				AddQuestRecord("Roger_8", "18");
				break;
			}
			if (iTotalTemp >= 20 && iTotalTemp < 300)
			{
				dialog.text = "Pietoso. Non compensa nemmeno il mio giro qui. Gli spagnoli devono averlo gettato in mare per impedirci di prenderlo. Almeno hanno pagato per questo. Così come gli uomini di Barbazon, che è anche una vittoria...";
				link.l1 = "Mi dispiace per l'oro... Dividiamolo comunque.";
				link.l1.go = "mtraxx_board_3";
				AddQuestRecord("Roger_8", "19");
				break;
			}
			if (iTotalTemp >= 300 && iTotalTemp < 700)
			{
				dialog.text = "Questo è un misero bottino. A malapena sufficiente a coprire le spese. Gli spagnoli devono aver buttato una parte in mare per non darcela. Almeno hanno pagato per questo. Così come gli uomini di Barbazon, che è anche una vittoria...";
				link.l1 = "Scusa per l'oro... Dividiamolo comunque.";
				link.l1.go = "mtraxx_board_3";
				AddQuestRecord("Roger_8", "19");
				AddCharacterExpToSkill(pchar, "Fortune", 100);
				break;
			}
			if (iTotalTemp >= 700 && iTotalTemp < 1000)
			{
				dialog.text = "Non male, anche se mi aspettavo di meglio. Gli spagnoli devono aver buttato una parte in mare per evitare che noi lo prendessimo. Almeno hanno pagato per questo. Così come gli uomini di Barbazon, che è anche una vittoria...";
				link.l1 = "Dividiamo il premio!";
				link.l1.go = "mtraxx_board_3";
				AddQuestRecord("Roger_8", "20");
				AddCharacterExpToSkill(pchar, "Fortune", 200);
				break;
			}
			dialog.text = "Splendido! Abbiamo ottenuto un bel premio, amico mio! E gli uomini di Barbazon hanno ricevuto ciò che meritavano, ah-ah!";
			link.l1 = "Ehi, è un mucchio d'oro! Dividiamolo!";
			link.l1.go = "mtraxx_board_3";
			AddQuestRecord("Roger_8", "21");
			AddCharacterExpToSkill(pchar, "Fortune", 300);
		break;
		
		case "mtraxx_board_3":
			RemoveCharacterGoods(pchar, GOOD_GOLD, makeint(iTotalTemp/2));
			WaitDate("", 0, 0, 0, 3, 10);
			LAi_Fade("", "");
            dialog.text = "... come facciamo sempre nei Fratelli - una quota equa per ciascuno. Puoi tenere la 'Torero', è il tuo premio.";
			link.l1 = "Cosa c'è dopo Marcus? Stiamo andando a La Vega?";
			link.l1.go = "mtraxx_board_4";
		break;
		
		case "mtraxx_board_4": // belamour legendary edition увеличиваем срок до 3х месяцев
            dialog.text = "Sicuramente sarò a La Vega, ti aspetterò lì per tre settimane. Vieni quando sei pronto. Preferibilmente su una nave più forte, ma solo su una - saremo un intero squadrone. Sto mettendo in marcia tutti i miei uomini. Andranno sotto il mio comando, Jean il Bello, Geoffrey il Calvo, Pelly il Macellaio e Luke il Folletto incluso. Preparati. Ci aspetta una spedizione seria e un bottino piuttosto grande. Scoprirai tutti i dettagli più tardi.";
			link.l1 = "Bene capo! Ci vediamo a La Vega tra tre settimane.";
			link.l1.go = "mtraxx_board_5";
		break;
		
		case "mtraxx_board_5":
            dialog.text = "Addio tagliagole! Ah-ah!";
			link.l1 = "...";
			link.l1.go = "mtraxx_board_6";
		break;
		
		case "mtraxx_board_6":
            DialogExit();
            npchar.dialog.currentnode = "mtraxx_board_6x";
			npchar.DeckDialogNode = "mtraxx_board_6x";
			npchar.DontDeskTalk = true;
			Ship_SetTaskRunAway(SECONDARY_TASK, sti(npchar.index), sti(pchar.index));
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			pchar.quest.mtraxx_corrida_complete.win_condition.l1 = "MapEnter";
			pchar.quest.mtraxx_corrida_complete.function = "Mtraxx_CorridaComplete";
			RemoveItems(pchar, "wolfreeks_book", 1);
			// belamour legendary edition забрать флаг обратно
			if(CheckAttribute(pchar, "questTemp.GiveMeSpaFlag")) 
			{
				DeleteAttribute(pchar, "questTemp.GiveMeSpaFlag")); 
				DeleteAttribute(pchar,"perks.list.FlagSpa"); 
				log_info("You have given spanish flag");
			}
		break;
		
		case "mtraxx_board_6x":
            dialog.text = "C'è altro?";
			link.l1 = "No, non credo. Sto già andando alla mia nave.";
			link.l1.go = "mtraxx_board_6y";
		break;
		
		case "mtraxx_board_6y":
            DialogExit();
			npchar.DeckDialogNode = "mtraxx_board_6x";
		break;
		
		case "mtraxx_board_7":
            dialog.text = "Ehi! E di chi è la colpa, Principe? È stata tua?";
			link.l1 = "Mi dispiace, capo, ma eravamo entrambi abbastanza bravi... Hai fatto un ottimo lavoro anche tu sparando. Bel mirare, a proposito...";
			link.l1.go = "mtraxx_board_8";
		break;
		
		case "mtraxx_board_8":
            dialog.text = "Comunque. La colpa è di entrambi. Non siamo però a mani vuote - gli uomini di Barbazon hanno ottenuto ciò che avevamo per loro, una vittoria di per sé...";
			link.l1 = "Mi dispiace per l'oro... Cosa succede adesso Marcus? Stiamo andando a La Vega?";
			link.l1.go = "mtraxx_board_4";
		break;
		
		case "mtraxx_90x":
            DialogExit();
			npchar.dialog.currentnode = "mtraxx_90";
		break;
		
		case "mtraxx_90":
			pchar.quest.Mtraxx_CartahenaLate.over = "yes";
			if (GetCompanionQuantity(pchar) > 1)
			{
				dialog.text = "Principe, sei diventato scemo? Ti ho detto di portare solo una nave! Vai a liberarti del superfluo e torna il più presto possibile! Ora!";
				link.l1 = "Bene, bene!";
				link.l1.go = "mtraxx_90x";
				break;
			}
			if (RealShips[sti(pchar.Ship.Type)].Type.Merchant) // торговые
			{
				dialog.text = "Principe, hai deciso di essere il mio secondo Stocco? Perché mi hai portato una nave mercantile? Contavo su di te! Vai a portare una decente nave da guerra! Ora!";
				link.l1 = "Bene, bene!";
				link.l1.go = "mtraxx_90x";
				break;
			}
			if (sti(RealShips[sti(pchar.ship.type)].Class) > 3)
			{
				dialog.text = "Principe, mi hai sorpreso. Ti ho detto di portare una nave da guerra! Come pensi di aiutarmi su questa tinozza? Torna qui su una nave di terzo o secondo rango, non meno e non di più! Ora! Non aspetterò nessuno.";
				link.l1 = "Va bene, va bene!";
				link.l1.go = "mtraxx_90x";
				break;
			}
			if (sti(RealShips[sti(pchar.ship.type)].Class) < 2)
			{
				dialog.text = "Principe, perché non porti qui il Sovrano dei Mari? Quando ti ho detto di portare un vascello da guerra, non intendevo portare una cazzo di nave di linea! Torna qui su una nave di terzo o secondo rango! Subito! Non aspetterò nessuno.";
				link.l1 = "Bene, bene!";
				link.l1.go = "mtraxx_90x";
				break;
			}
            dialog.text = "Buon timing, corsaro! Felice di vederti intero! Pronto per un viaggio?";
			link.l1 = "Certo, capo. Sempre pronto.";
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Corrida.Barbazon")) link.l1.go = "mtraxx_91";
			else link.l1.go = "mtraxx_94";
		break;
		
		case "mtraxx_91":
            dialog.text = "A proposito, vuoi sapere della squadra di Barbazon che hai mandato a Puerto-Rico?";
			link.l1 = "Sono completamente usciti dalla mia mente. Certo che voglio. Hanno trovato la loro rovina?";
			link.l1.go = "mtraxx_92";
		break;
		
		case "mtraxx_92":
            dialog.text = "Certo che l'hanno fatto! La nave ammiraglia - la fregata di Joker Jim 'Owl', è stata bruciata fino al suolo. Lo stesso Joker Jim è scomparso senza lasciare traccia. Il Vagabondo e Ghoul sono stati duramente battuti, ma sono riusciti a scappare: il Vagabondo - a Tortuga, sotto la protezione dei cannoni di La Rocha, Ghoul - a Isla Tesoro. Pasquale mi ha detto che Ghoul ha anche arenato la sua nave sugli scogli vicino a Sharptown e se ne è appena liberato. Ora il Maestro Alexus ha molto lavoro da fare, hehe. In generale, gli spagnoli mi hanno un po' deluso. Pensavo che avrebbero ucciso tutti.";
			link.l1 = "Eh. Comunque, abbiamo ancora pisciato negli stivali di Barbazon. Gli abbiamo dato un messaggio.";
			link.l1.go = "mtraxx_93";
		break;
		
		case "mtraxx_93":
            dialog.text = "Vero. Parliamo di affari.";
			link.l1 = "Sono tutto orecchie.";
			link.l1.go = "mtraxx_94";
		break;
		
		case "mtraxx_94":
            dialog.text = "Il mio servizio di intelligence sotto forma del mio buon amico Bernard Vensan ha riferito un enorme mucchio di lingotti d'oro che gli spagnoli hanno depositato a Cartagena. Sotto la sua fortezza, per essere più precisi. Normalmente sarebbe stato attribuito alla Flotta d'Oro della Spagna, ma questa volta è nostro da prendere. Stiamo dirigendo verso il Sud Main per assaltare Cartagena.";
			link.l1 = "Argh! Ho sentito bene? Stiamo per saccheggiare un'intera colonia, con un cazzo di forte?";
			link.l1.go = "mtraxx_95";
			// belamour legendary edition отказ от великого похода
			link.l2 = "Non vado a Cartagena con te, Marcus. Bruciare un'intera città non è la mia storia.";
			link.l2.go = "mtraxx_94a";
		break;
		
		case "mtraxx_95":
            dialog.text = "Hai sentito bene. È esattamente quello che faremo. La mia nave da guerra si occuperà del forte, con il tuo aiuto, ovviamente. Il coraggioso Jeffrey trasporterà le truppe di terra sulla sua nuova nave da guerra rubata agli olandesi. Pelly finalmente si è liberato della sua brigantina malandata e ha ottenuto una corvetta decente, non senza il mio aiuto finanziario, ovviamente. Paul Chant e tu siete responsabili di eliminare la flotta di pattuglia, anche i vostri equipaggi partecipano alla tempesta, e tu, Charles, così buon combattente e capitano, mi aiuterai a distruggere il forte.\nJean Picard non si è presentato, il che è strano visto che la sua corvetta è stata vista a Port Royal. Beh, se non è interessato all'oro spagnolo è un suo problema, quindi che vada al diavolo. Al suo posto, il mio amico Bernard Vensan si unirà al raid. In più, il Leprechaun con i suoi bucanieri assisterà le nostre truppe. Prenderemo l'oro dal forte e il riscatto dalla città. Non lo dimenticheranno, ah-ah!\n Ora, vai a riposare. E unisciti a me e agli altri capitani nella taverna questa sera! Dovremmo bere alla nostra causa! Ordinerò al barista di cacciare tutti gli alcolisti del posto, quindi solo sei di noi e alcune ragazze affascinanti saranno nella taverna. Stasera bevi con i tuoi compagni, e domani mattina guiderai lo squadrone, traccerai il corso. E cerca di portarci a Cartagena il più presto possibile. Tutto chiaro?";
			link.l1 = "Si, si, capo!";
			link.l1.go = "mtraxx_96";
		break;
		
		case "mtraxx_96":
            DialogExit();
			npchar.dialog.currentnode = "mtraxx_wait";
			chrDisableReloadToLocation = true;
			CloseQuestHeader("Roger_8");
			pchar.questTemp.Mtraxx = "cartahena";
			LAi_SetActorType(npchar);
			ChangeCharacterAddressGroup(npchar, "LaVega_townhall", "goto", "goto3");
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Mtraxx_CartahenaReloadInTavern", 10.0);
			pchar.worldmapencountersoff = "1"; // уберем враждебные энкаунтеры
		break;
		// belamour legendary edition -->
		case "mtraxx_94a":
            dialog.text = "Tu... tu... Principe Pazzo! Mi stai tendendo una trappola?! Sai che, al diavolo con te! Avevi l'opportunità di entrare nella Fratellanza, avevi l'opportunità di sfuggire dalle file di tutto questo bestiame inutile. E hai solo vigliaccamente perso questa chance. Vattene con il tuo piagnisteo! Debole! Vedrai ancora una volta - lascerò andare i cani!";
			link.l1 = "...";
			link.l1.go = "mtraxx_95a";
		break;
		
		case "mtraxx_95a":
            DialogExit();
			QuestSetCurrentNode("Terrax", "First time");
			CloseQuestHeader("Roger_8");
			DeleteAttribute(pchar, "questTemp.Mtraxx.Corrida");
			DeleteAttribute(pchar, "questTemp.Mtraxx.InTavern");
			LocatorReloadEnterDisable("LaVega_town", "reload6", true); // закрыть на месяц
			SetFunctionTimerCondition("Mtraxx_CartahenaLateOpen", 0, 0, 30, false);
			Mtraxx_TerraxReset(8);
			DoQuestReloadToLocation("LaVega_town", "reload", "reload6", ""); // выставим за дверь
		break;
		// <-- legendary edition
		case "mtraxx_97":
            dialog.text = "Principe, finalmente! Guardate, ragazzi - abbiamo preparato un regalo per lui, e lui se ne va in giro chissà dove! Sedetevi, stiamo iniziando!\nAllora, coraggiosi corsari! L'oro di Cartagena ci aspetta, ah-ah! E lo avremo, lo giuro su tuono! Ma chi lavora bene deve anche riposare bene! Ecco perché oggi ci divertiremo in questo splendido locale. Servitevi del rum, quanto più ne bevete, tanto meglio! Riempite le vostre tazze fino all'orlo! Al vento del tesoro, al vento della fortuna! Beviamo fino in fondo!\nPer voi, la birra più fine dalle cantine della nostra taverna, e le donne più belle dell'isola, ah-ah-ah!\nE per te, Charles, da noi — un magnifico cappello. Provalo, e non discutere!\nCorsari, cantate la nostra canzone! La nostra preferita!..";
			link.l1 = "";
			link.l1.go = "mtraxx_98";
		break;
		
		case "mtraxx_98":
            DialogExit();
			npchar.dialog.currentnode = "mtraxx_wait";
			LAi_SetSitType(npchar);
			GiveItem2Character(PChar, "hat8");
			EquipCharacterByItem(PChar, "hat8");
			DoQuestCheckDelay("Mtraxx_CartahenaTavernSong", 1.0);
		break;
		
		case "mtraxx_99":
            dialog.text = "È ora di mostrare loro chi siamo, corsari. Leprecauno! Prendi i tuoi uomini e prendi il controllo delle porte della città. Non vogliamo che mandino rinforzi al forte! Colpiscili duramente alle spalle quando ci precipiteremo attraverso i soldati del forte!";
			link.l1 = "";
			link.l1.go = "mtraxx_100";
		break;
		
		case "mtraxx_100":
            dialog.text = "Principe e Paolo! Avete visto lo squadrone militare con tre navi, liberatecene. State alla larga dal forte e non salite a bordo delle loro navi. Non abbiamo né tempo, né posizione per occuparci dei premi. Tutto è chiaro?! Principe, sto parlando soprattutto a te, so della tua dipendenza dall'eroismo, avrai l'opportunità per questo più tardi!\nNon avvicinatevi troppo al forte, liberatevi di queste navi, e tornate! Vi aspetteremo qui. Tutto è chiaro? Ottimo, ah-ah-ah-ah! Ad l'attacco!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_CartahenaSquadronAttack");
		break;
		
		case "mtraxx_101":
            dialog.text = "Allora, la squadra spagnola se n'è andata per sempre. Ora è il momento per il 'Drago Rosso' di fare la sua parte. Trasformeremo il forte di Cartagena in un mucchio di macerie. Sei con me?";
			link.l1 = "Certo!";
			link.l1.go = "mtraxx_102";
		break;
		
		case "mtraxx_102":
            dialog.text = "'Il 'Drago Rosso' è una nave molto robusta con un'artiglieria potente, la tua non le è alla pari. Quindi fai attenzione, non fare l'eroe e stai lontano dai miei cannoni!";
			link.l1 = "...";
			link.l1.go = "mtraxx_103";
		break;
		
		case "mtraxx_103":
            DialogExit();
			
			Weather.Wind.Speed = 16.0;
			pchar.wind.speed = Weather.Wind.Speed;
			fWeatherSpeed = stf(Weather.Wind.Speed);//халява первого выхода
	
			Weather.Wind.Angle = 0.0;
			pchar.wind.angle = Weather.Wind.Angle;
			fWeatherAngle = stf(Weather.Wind.Angle);//халява первого выхода
			
            npchar.dialog.currentnode = "mtraxx_board_6x";
			npchar.DeckDialogNode = "mtraxx_board_6x";
			npchar.DontDeskTalk = true;
			Group_FindOrCreateGroup("Terrax_SeaGroup2");
			Group_DelCharacter("Terrax_SeaGroup", "Jeffry");
			Group_DelCharacter("Terrax_SeaGroup", "Mtr_Vensan");
			Group_AddCharacter("Terrax_SeaGroup2", "Jeffry");
			Group_AddCharacter("Terrax_SeaGroup2", "Mtr_Vensan");
			Group_AddCharacter("Terrax_SeaGroup2", "Pelly");
			Group_SetGroupCommander("Terrax_SeaGroup2", "Jeffry");
			Group_SetTaskNone("Terrax_SeaGroup2");
			Group_LockTask("Terrax_SeaGroup2");
			sld = CharacterFromID("Cartahena Fort Commander");
			LAi_SetImmortal(sld, false);
			Ship_SetTaskAttack(SECONDARY_TASK, sti(npchar.index), sti(sld.index));
			AddQuestRecord("Roger_9", "5");
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			pchar.questTemp.Mtraxx.Cartahena.Fort = "true";
			SetFunctionExitFromLocationCondition("Mtrxtofort", pchar.location, false);
		break;
		
		case "mtraxx_104":
            dialog.text = RandSwear()+"Maledetta lotta! Questo è il momento, i miei coraggiosi corsari! Cartagena è nostra! La resistenza è al tappeto! Audace, Leprechaun! Vieni con me al forte - Bernie deve aver già trovato l'oro. Principe, prendi Cutlass e negozia con il governatore per farci pagare un riscatto di 250.000 pesos! Hanno i soldi, quindi sii persistente. So che puoi.";
			link.l1 = "Eh! Con piacere, capo!";
			link.l1.go = "mtraxx_105";
		break;
		
		case "mtraxx_105":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "gate_back", "Cartahena_fort", "goto", "goto10", "", 5.0);
			sld = CharacterFromID("Jeffry");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "gate_back", "Cartahena_fort", "goto", "goto11", "", 5.0);
			sld = CharacterFromID("Lepricon");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "gate_back", "Cartahena_fort", "goto", "goto12", "", 5.0);
			sld = CharacterFromID("Pelly");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			AddQuestRecord("Roger_9", "6");
			// запрещаем драки в городе, резиденции, форте
			LAi_LocationFightDisable(&Locations[FindLocation("Cartahena_fort")], true);
			LAi_LocationFightDisable(&Locations[FindLocation("Cartahena_town")], true);
			LAi_LocationFightDisable(&Locations[FindLocation("Cartahena_townhall")], true);
			LAi_LocationDisableOfficersGen("Cartahena_townhall", true);
			pchar.quest.mtraxx_cartahena_townhall.win_condition.l1 = "locator";
			pchar.quest.mtraxx_cartahena_townhall.win_condition.l1.location = "Cartahena_town";
			pchar.quest.mtraxx_cartahena_townhall.win_condition.l1.locator_group = "reload";
			pchar.quest.mtraxx_cartahena_townhall.win_condition.l1.locator = "reload3_back";
			pchar.quest.mtraxx_cartahena_townhall.function = "Mtraxx_CartahenaToResidence";
		break;
		
		case "mtraxx_106":
            dialog.text = "Come stai, Principe?";
			link.l1 = "Tutto è splendido. Ho costretto i più ricchi di Cartagena a pagare 350.000 pesos.";
			link.l1.go = "mtraxx_107";
		break;
		
		case "mtraxx_107":
            if (sti(Pchar.money) < 350000)
			{
				dialog.text = "Ah-ah, questo è il mio ragazzo! Ma dov'è il denaro?";
				link.l1 = RandSwear()+"Lo porterò in un attimo!";
				link.l1.go = "mtraxx_107x";
			}
			else
			{
				dialog.text = "Oho, questo è il mio ragazzo! Tu e la Sciabola potete tenere ciascuno 50.000 come bonus per velocità e ingegnosità. Il resto verrà diviso tra tutti noi più tardi.";
				link.l1 = "Eccoti!";
				link.l1.go = "mtraxx_109";
			}
		break;
		
		case "mtraxx_107x":
           DialogExit();
		   npchar.dialog.currentnode = "mtraxx_108";
		break;
		
		case "mtraxx_108":
            if (sti(Pchar.money) < 350000)
			{
				dialog.text = "Allora? Smetti di giocare e porta qui le monete!";
				link.l1 = "Sulla mia strada!";
				link.l1.go = "mtraxx_107x";
			}
			else
			{
				dialog.text = "Ottimo! Tu e la Sciabola potete tenere 50.000 ciascuno come bonus per la velocità e l'ingegno. Il resto sarà diviso tra tutti noi più tardi.";
				link.l1 = "Eccoti qui!";
				link.l1.go = "mtraxx_109";
			}
		break;
		
		case "mtraxx_109":
			AddMoneyToCharacter(pchar, -300000);
            dialog.text = "Devi essere preoccupato per il nostro oro? È stato trovato - 5.000 unità e sta già venendo trasportato sulle nostre navi. La divisione è già stata fatta, gli uomini sono d'accordo, speriamo che Cutlass e tu non obietterete.";
			link.l1 = "Qual è la mia parte?";
			link.l1.go = "mtraxx_110";
		break;
		
		case "mtraxx_110":
            dialog.text = "Dato che l'intera operazione è stata pianificata da me, più il 'Drago Rosso' ha fatto il lavoro più duro occupandosi del forte, io e i miei uomini riceveremo metà del bottino. L'altra metà sarà divisa tra i capitani delle altre quattro navi in base al numero dei loro equipaggi. Tu hai "+GetCrewQuantity(pchar)+" uomini a disposizione, la tua quota è "+sti(pchar.questTemp.Mtraxx.Cartahena.Gold)+" unità d'oro e "+sti(pchar.questTemp.Mtraxx.Cartahena.Money)+" pesos.";
			link.l1 = "Ebbene, se a tutti va bene, allora anche a me!";
			link.l1.go = "mtraxx_111";
		break;
		
		case "mtraxx_111":
            dialog.text = "Splendido. Congratulazioni per questo viaggio di successo, corsari! Qui non c'è più nulla per noi, è ora di tornare a casa. Tutti noi, me compreso, riceviamo un mese di vacanza. Non tu, Principe, però, ho un altro compito per te. Vedi, Janette, una Madame del bordello di Tortuga, si è lamentata di te: ha detto che Charlie Prince non dà molta attenzione e amore al suo stabilimento. Pertanto, ti ordino di navigare verso Tortuga, andare da Janette e sperperare i tuoi bonus lì. Te lo sei meritato. Rendi felice la Madame e le sue ragazze. Non voglio vederti prima che tu ti sia riposato a Tortuga, ah-ah-ah!";
			link.l1 = "Capito, capo. Questo è l'incarico più piacevole che abbia mai ricevuto. Sarà fatto!";
			link.l1.go = "mtraxx_112";
		break;
		
		case "mtraxx_112":
            dialog.text = "Addio, signori! Salite sulle vostre navi e issate le vele! Ci vediamo tutti a La Vega!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_CartahenaFinal");
		break;
		
		// Addon 2016-1 Jason пиратская линейка патч 17/1
		case "mtraxx_113":
            dialog.text = "Cosa?! Jean è ora una puttana degli inglesi, Bold e Cutlass sono spariti, Leprechaun e i suoi uomini sono introvabili! E ora anche tu?!";
			link.l1 = "Marcus, ho preso la mia decisione. Ho fatto un bel po' di soldi, anche tu hai fatto una fortuna su di me. Ma ho finito. Me ne vado.";
			link.l1.go = "mtraxx_114";
		break;
		
		case "mtraxx_114":
            dialog.text = "Tu, proprio come Picard, pensi che puoi avere guadagni migliori da solo? Eh? Pensi di poter fare a meno di me? Ha-ha-ha! Vattene all'inferno, Principe, non ti sto trattenendo. Presto, molto presto vedrai quanto avevi torto e poi tornerai a supplicarmi di riprenderti. E sai una cosa? Non lo farò! Ha-ha! Sparisci dalla mia vista!";
			link.l1 = "...";
			link.l1.go = "mtraxx_115";
		break;
		
		case "mtraxx_115":
            DialogExit();
		    npchar.quest.mtraxx_complete = "true";
		break;
		
		// Jason НСО
		case "patria":
			dialog.text = "Oho! Sei venuto nel posto giusto! Sputa il rospo!";
			link.l1 = "C'è un tizio che non ha paura dei pirati. Non li prende sul serio. Deve essere insegnato una lezione di rispetto. Ricorda, non ucciderlo.";
			link.l1.go = "patria_1";
		break;
		
		case "patria_1":
			dialog.text = "Eh! Non è altri che il vecchio Charles! Scommetto che ti sei cacciato in qualche affare di nuovo! Andiamo ai dettagli, chi è il bersaglio questa volta e cosa dovremmo insegnargli?";
			link.l1 = "Un ospite dall'Europa, un ispettore del Ministero delle Finanze francese - il barone Noel Forget. Vuole stabilire qui una Compagnia di Commercio francese, ma io e un mio stretto amico ci opponiamo. Abbiamo cercato di convincere il Barone, che fare commercio qui sarebbe molto rischioso a causa degli olandesi, degli inglesi e soprattutto dei pirati dopo la sconfitta di Levasseur, ma lui non ha ascoltato. Dobbiamo incutergli paura, farlo sentire sulla sua pelle.";
			link.l1.go = "patria_2";
		break;
		
		case "patria_x":
			dialog.text = "Ah-ah! Sei venuto nel posto giusto! Sputalo fuori!";
			link.l1 = "C'è un tizio che non ha paura dei pirati. Non li prende sul serio. Deve essere insegnato una lezione di rispetto. Ricorda, non ucciderlo.";
			link.l1.go = "patria_x1";
		break;
		
		case "patria_x1":
			dialog.text = "Eh! Perché hai deciso di sfruttare i pirati all'improvviso? Bene, non mi importa finché mi paghi. Andiamo ai dettagli, chi è il bersaglio questa volta e cosa dovremmo insegnargli";
			link.l1 = "Un ospite dall'Europa, un ispettore del Ministero delle Finanze francese - il barone Noel Forget. Vuole stabilire qui una Compagnia di Commercio francese, ma io e un mio stretto amico ci opponiamo. Abbiamo cercato di convincere il Barone, che fare commercio qui sarebbe molto rischioso a causa degli olandesi, degli inglesi e soprattutto dei pirati dopo la sconfitta di Levasseur, ma lui non ha ascoltato. Dobbiamo incutergli paura, farlo sentire sulla sua pelle.";
			link.l1.go = "patria_2";
		break;
		
		case "patria_2":
			dialog.text = "Sì-sì... Un vero barone! Dovremmo assaltare la sua nave?";
			link.l1 = "Ecco il piano: la sua nave partirà presto per Capsterville da Port-au-Prince. Devi intercettare il Barone vicino a Saint Kitts e prenderlo come ostaggio. Sarebbe meglio se non affondassi la nave e evitassi di uccidere uomini. Dopotutto, i francesi sono i nostri amici. Riuscirai a gestire tutto questo?";
			link.l1.go = "patria_3";
		break;
		
		case "patria_3":
			dialog.text = "Ebbene, non posso promettere nulla. Ma ci proverò. Quale nave è?";
			link.l1 = "Una brigantina chiamata 'Favory'.";
			link.l1.go = "patria_4";
		break;
		
		case "patria_4":
			dialog.text = "Una brigantina non è nulla di fronte al mio 'Drago Rosso'. Ce la faremo facilmente con loro. Se si arrendono, lascerò vivere tutti.";
			link.l1 = "Perfetto. Incutile paura e offrigli di arrendersi. Successivamente, manda il Barone nel deposito infestato dai ratti. Cerca di trovare il posto più sporco possibile, ma non tenerlo lì più di un giorno, potrebbe ammalarsi e morire. Poi sistemalo nella cabina, trova e rinchiudilo in un luogo appartato. Vesti alcuni dei tuoi uomini come mercanti francesi catturati e fagli comportare come tali. Per tre giorni di fila, dovrebbero raccontargli tutto su come i pirati spietati li inseguono, li derubano, chiedono riscatti, li torturano... con tutti i dettagli necessari.";
			link.l1.go = "patria_5";
		break;
		
		case "patria_5":
			dialog.text = "Ah-ah-ah! Questo deve essere il lavoro più divertente che abbia mai accettato da molto tempo! Beh, allora, troverò tali attori, ragazzo. Non avere dubbi, dopo le loro storie il tuo Barone si caccerà addosso! Gli mostreranno cicatrici da sciabole e punteruoli riscaldati...";
			link.l1 = "Perfetto! Allora lo costringerai a scrivere una lettera a de Poincy, chiedendo un riscatto. Tre milioni e mezzo per un pezzo grosso non è poi così tanto.";
			link.l1.go = "patria_6";
		break;
		
		case "patria_6":
			dialog.text = "Bene. Cosa faremo dopo?";
			link.l1 = "E poi porterai il Barone a Turks. Lì prenderai il riscatto, e mi darai il Barone. E inoltre dovresti dirgli che tutti i francesi pagheranno per Tortuga e Levasseur e non solo una volta.";
			if (CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax")) link.l1.go = "patria_x7";
			else link.l1.go = "patria_7";
		break;
		
		case "patria_7":
			dialog.text = "Ah-ah-ah! Questo è un trucco infernale! Noi personalmente, beh, sai cosa abbiamo fatto a Levasseur, e ora... ah-ah-ah!.. Bene, ragazzo. Sarà fatto! Quindi dici che la nave arriverà presto?";
			link.l1 = "Presto. Dobbiamo stare in guardia.";
			link.l1.go = "patria_8";
		break;
		
		case "patria_x7":
			dialog.text = "Ha-ha-ha! Questo è un trucco del diavolo! Quanto dovrei farti pagare per questa farsa? Va bene, centomila sigilleranno l'accordo. Dammi i soldi.";
			if (sti(pchar.money) >= 100000) 
			{
				link.l1 = "Prendilo.";
				link.l1.go = "patria_x8";
			}
			else
			{
				link.l1 = "Bene, lo porterò.";
				link.l1.go = "patria_xwait";
			}
		break;
		
		case "patria_xwait":
			DialogExit();
			pchar.questTemp.Patria.Condotier.NeedMoney = "true";
		break;
		
		case "patria_x8":
			AddMoneyToCharacter(pchar, -100000);
			dialog.text = "Perfetto! Dici che la nave arriverà presto?";
			link.l1 = "Presto. Dobbiamo stare in guardia.";
			link.l1.go = "patria_8";
		break;
		
		case "patria_8":
			dialog.text = "Non preoccuparti, non ti deluderò. Me ne occuperò personalmente. Quando sentirai un pettegolezzo che il Barone è stato catturato, vieni da me.";
			link.l1 = "Bene. Le mie grazie, Marcus.";
			link.l1.go = "patria_9";
		break;
		
		case "patria_9":
			DialogExit();
			AddQuestRecord("Patria", "71");
			pchar.questTemp.Patria = "epizode_12_wait";
			pchar.questTemp.Patria.Condotier.Success = "true";
			if (CheckAttribute(pchar, "questTemp.Patria.Saga.Terrax")) LocatorReloadEnterDisable("Pirates_town", "reload3_back", true);
			else LocatorReloadEnterDisable("Lavega_town", "reload6", true);
		break;
		
		case "patria_10":
			dialog.text = "Certo, ragazzo. Come concordato. Racconti spaventosi di malvagi pirati, che massacrano innocenti mercanti francesi, i suoni di una frusta, gemiti e urla. Braciere con carbone e manette bruciate. Proprio come dovrebbe essere.";
			link.l1 = "Ho ho! Fermati! Ho bisogno di lui vivo";
			link.l1.go = "patria_11";
		break;
		
		case "patria_11":
			dialog.text = "Non preoccuparti, vivrà. Ha scritto questa lettera con una mano tremante. Eccola qui.";
			link.l1 = "Cosa c'è scritto lì? Sta implorando Poincy di tirarlo fuori da questo?";
			link.l1.go = "patria_12";
		break;
		
		case "patria_12":
			dialog.text = "Proprio così, ragazzo! Sta implorando, ah!";
			link.l1 = "Butta via questa lettera, o meglio - bruciala. Ci incontreremo a Turks tra una settimana. Deve sembrare come se avessimo bisogno di tempo per raccogliere il riscatto.";
			link.l1.go = "patria_13";
		break;
		
		case "patria_13":
			dialog.text = "Capito. Tra una settimana, golfo del nord a Turks. Non dimenticare di prendere i soldi: deve sembrare bello. Dopo tutto questo, vieni da me, ne parleremo.";
			link.l1 = "Certo, ci vediamo dopo, Marcus!";
			link.l1.go = "patria_14";
		break;
		
		case "patria_14":
			DialogExit();
			AddQuestRecord("Patria", "73");
			pchar.questTemp.Patria = "epizode_12_terks";
			SetFunctionTimerCondition("Patria_CondotierTerks", 0, 0, 7, false);
			SetFunctionTimerCondition("Patria_CondotierTerksOver", 0, 0, 14, false);
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
		break;
		
		case "patria_15":
			pchar.quest.Patria_CondotierTerksOver.over = "yes"; //снять таймер
			dialog.text = "Ehi, mangiarane! Fermati!";
			link.l1 = "Non mi sto muovendo.";
			link.l1.go = "patria_16";
		break;
		
		case "patria_16":
			dialog.text = "Ecco il tuo Barone. Un po' logoro, eh, ma intero. È ancora riconoscibile? Ah-ah-ah!";
			link.l1 = "Sì... in qualche modo.";
			link.l1.go = "patria_17";
		break;
		
		case "patria_17":
			dialog.text = "Perfetto. Ora consegna i soldi o lui è finito! E non cercare di ingannarci, ti abbiamo nel mirino!";
			if (sti(pchar.money) >= 350000)
			{
				link.l1 = "Ecco, prendilo.";
				link.l1.go = "patria_18";
			}
			else
			{
				link.l1 = "Accidenti! L'ho dimenticato sulla nave...";
				link.l1.go = "patria_22";
			}
		break;
		
		case "patria_18":
			AddMoneyToCharacter(pchar, -350000);
			dialog.text = "Ha-ha-ha! Sei un ragazzino astuto, francese. Prendi la tua 'eminenza'. E digli a Poincy che dovrebbe preparare i soldi: dovrai pagare per quello che hai fatto a Levasseur e Tortuga. E i tuoi mercanti ci pagheranno con le loro merci e navi. Ha-ha-ha! Non dimenticarti di portarci ancora più baroni nell'arcipelago, ci fanno guadagnare molto! Ha-ha-ha!";
			link.l1 = "Per favore, vai alla mia barca, Barone.";
			link.l1.go = "patria_19";
		break;
		
		case "patria_19":
			sld = CharacterFromID("Noel");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", 10.0);
			dialog.text = "E non pensare nemmeno di inseguirci, capitano. Sai chi sono. Ho molti più mangiarane prigionieri, e se non torno a casa in tempo, verranno tutti giustiziati. Capito?";
			link.l1 = "Verrà il tempo e ci occuperemo di voi, maledetti blasfemi!";
			link.l1.go = "patria_20";
		break;
		
		case "patria_20":
			dialog.text = "Ah-ah-ah-ah! Certo che lo farai!";
			link.l1 = "...";
			link.l1.go = "patria_21";
		break;
		
		case "patria_21":
			DialogExit();
			LAi_SetPlayerType(pchar);
			AddQuestRecord("Patria", "74");
			LAi_SetActorType(npchar);
			if (CheckAttribute(pchar, "questTemp.Patria.Saga.Terrax"))
			{
				LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "Patria_CondotierDodsonNorm", 10.0);
				Island_SetReloadEnableGlobal("Bermudes", false); // закрыть остров до отвоза барона
			}
			else LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "Patria_CondotierTerraxNorm", 10.0);
			sld = CharacterFromID("Terks_pirat");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", 8.0);
			pchar.questTemp.Patria = "epizode_12_baronalive";
			pchar.questTemp.Patria.DodsonAgain = "true";
			sld = CharacterFromID("Noel");
			AddPassenger(pchar, sld, false);//добавить пассажира
			SetCharacterRemovable(sld, false);
			pchar.quest.Patria_Condotier_toPuancie.win_condition.l1 = "location";
			pchar.quest.Patria_Condotier_toPuancie.win_condition.l1.location = "Charles_town";
			pchar.quest.Patria_Condotier_toPuancie.function = "Patria_CondotierEnCapstervil";
			// Теркс в норму
			LAi_LocationFightDisable(&Locations[FindLocation("Shore56")], false);
			LAi_LocationDisableOfficersGen("Shore56", false);
		break;
		
		case "patria_22":
			dialog.text = "Stai scherzando con me?! È qualche tipo di trucco?!";
			link.l1 = "Un momento, lo porto...";
			link.l1.go = "patria_23";
		break;
		
		case "patria_23":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("Terks_pirat");
			LAi_SetActorType(sld);
			LAi_ActorAnimation(sld, "Shot", "Patria_CondotierBaronDie", 1.0);
		break;
		
		case "patria_24":
			dialog.text = "";
			link.l1 = "Argh, Marcus, cosa ha fatto il tuo stupido!";
			if (CheckAttribute(pchar, "questTemp.Patria.Saga.Terrax")) link.l1.go = "patria_25";
			else link.l1.go = "patria_x25";
		break;
		
		case "patria_25":
			dialog.text = "Charles, cosa stavi facendo? Dov'è il denaro? Non ho detto ai miei ragazzi che non era vero... e così questo idiota ha deciso che volevi ingannarci...";
			link.l1 = "È un disastro! Il Barone è morto... Cosa farà ora de Poincy?";
			link.l1.go = "patria_26";
		break;
		
		case "patria_x25":
			dialog.text = "Charles, cosa stavi facendo? Dov'è il denaro? Non ho detto ai miei ragazzi che questo non era vero... e quindi questo idiota ha deciso che volevi ingannarli...";
			link.l1 = "È un disastro! Il Barone è morto... Cosa farà ora de Poincy?";
			link.l1.go = "patria_x26";
		break;
		
		case "patria_x26":
			dialog.text = "Ebbene ragazzo, è colpa tua, spero tu lo capisca. Forse è per il meglio, un uomo morto non può fare del male.";
			link.l1 = "Che idiota che sono! Ho rovinato tutto. Va bene, andrò da Poincy... Perdonami per essere stato un idiota, Marcus, ci vediamo.";
			link.l1.go = "patria_28";
		break;
		
		case "patria_26":
			dialog.text = "Ebbene ragazzo, è colpa tua, spero tu lo capisca. Forse è per il meglio.";
			link.l1 = "Che idiota sono! Ho rovinato tutto. Va bene, andrò a Poincy... Perdonami per essere stato uno sciocco, Marcus, ci vediamo.";
			link.l1.go = "patria_27";
		break;
		
		case "patria_27":
			dialog.text = "Hai bisogno di riposarti, stai perdendo il tuo tocco. Vieni da me qualche volta, ti procurerò del rum e delle belle ragazze.";
			link.l1 = "Grazie, ti farò visita quando posso.";
			link.l1.go = "patria_28";
		break;
		
		case "patria_28":
			DialogExit();
			AddQuestRecord("Patria", "75");
			LAi_SetActorType(npchar);
			if (CheckAttribute(pchar, "questTemp.Patria.Saga.Terrax")) LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "Patria_CondotierDodsonNorm", 10.0);
			else LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "Patria_CondotierTerraxNorm", 10.0);
			sld = CharacterFromID("Terks_pirat");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", 8.0);
			pchar.questTemp.Patria = "epizode_12_barondie";
			// Теркс в норму
			LAi_LocationFightDisable(&Locations[FindLocation("Shore56")], false);
			LAi_LocationDisableOfficersGen("Shore56", false);
		break;
		
		case "patria_29":
			dialog.text = "Sei il benvenuto, ragazzo. Per me questo è stato il divertimento più grande che ho avuto quest'anno! Abbiamo riso tanto, io e i miei ragazzi! Quindi vorrei ringraziarti per questo. Ecco i tuoi soldi.";
			link.l1 = "Dovresti tenere una parte per la tua performance.";
			link.l1.go = "patria_30";
		break;
		
		case "patria_x29":
			AddMoneyToCharacter(pchar, 350000);
			dialog.text = "Prendi i tuoi soldi, 'complottista'. Ha-ha! È stato divertente.";
			link.l1 = "Grazie per il tuo aiuto, Marcus. Buona fortuna!";
			link.l1.go = "patria_32";
		break;
		
		case "patria_30":
			AddMoneyToCharacter(pchar, 350000);
			dialog.text = "Dimenticalo. L'ho fatto per il bene della nostra amicizia. I Fratelli della Costa ti devono molto di più, ma tu non hai chiesto nemmeno un solo doblone.";
			link.l1 = "Prendi comunque almeno cinquantamila per i servizi e i risarcimenti. Grazie, Marcus!";
			link.l1.go = "patria_31";
		break;
		
		case "patria_31":
			AddMoneyToCharacter(pchar, -50000);
			dialog.text = "Prego. Charles, vieni a trovarmi quando hai un po' di tempo!";
			link.l1 = "Con piacere!";
			link.l1.go = "patria_32";
		break;
		
		case "patria_32":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.Patria.DodsonAgain");
		break;
		
		case "patria_33":
			dialog.text = "Arrivi con una settimana di ritardo! Non ho detto ai miei ragazzi che questa non era una vera... Hanno rifiutato di aspettare oltre e hanno deciso di farla finita con il tuo Barone!";
			link.l1 = "Che idiota che sono! Ho rovinato tutto! Cosa dirò a Poincy?";
			link.l1.go = "patria_34";
		break;
		
		case "patria_x33":
			dialog.text = "Arrivi con una settimana di ritardo! Non ho detto ai miei ragazzi che questo non era vero... Hanno rifiutato di aspettare più a lungo e hanno deciso di farla finita con il tuo Barone!";
			link.l1 = "Che idiota che sono! Ho rovinato tutto! Cosa dirò a Poincy?";
			link.l1.go = "patria_x34";
		break;
		
		case "patria_34":
			dialog.text = "Ebbene, ragazzo, è colpa tua, spero tu lo capisca. Forse, sarà meglio per te.";
			link.l1 = "Bene, andrò a Poincy... Perdonami per essere stato uno sciocco, Marcus, ci vediamo..";
			link.l1.go = "patria_35";
		break;
		
		case "patria_x34":
			dialog.text = "Ti sei cacciato in questo pasticcio, è colpa tua.";
			link.l1 = "Arrivederci, immagino...";
			link.l1.go = "patria_36";
		break;
		
		case "patria_35":
			dialog.text = "Hai bisogno di riposare, stai perdendo il tuo tocco. Vieni da me qualche volta, ti procurerò del rum e belle donzelle.";
			link.l1 = "Grazie, ti farò visita quando posso.";
			link.l1.go = "patria_36";
		break;
		
		case "patria_36":
			DialogExit();
			AddQuestRecord("Patria", "75");
			pchar.questTemp.Patria = "epizode_12_barondie";
			DeleteAttribute(pchar, "questTemp.Patria.DodsonFail");
		break;
		
		// Rebbebion, квест "Путеводная звезда"
		case "PZ1":
			DelLandQuestMark(npchar);
			
			if (pchar.questTemp.Mtraxx == "full_complete")
			{
				dialog.text = "È stato un po', Principe.";
				link.l1 = "Non sono sicuro che questo nome mi abbia portato altro che sfortuna, Marcus.";
				link.l1.go = "PZ_Prince1";
			}
			else
			{
				dialog.text = "De Maure! Cosa ti porta qui?";
				link.l1 = "Ciao, Marcus. Volevo chiederti qualcosa.";
				link.l1.go = "PZ_DeMaure1";
			}
		break;
		
		case "PZ_Prince1":
			dialog.text = "Vedo che è il contrario. Cosa ti porta qui?";
			link.l1 = "Hai sentito parlare del nuovo bordello a Tortuga?";
			link.l1.go = "PZ2";
		break;
		
		case "PZ_DeMaure1":
			dialog.text = "Allora per tutti i mezzi, chiedi. Sai che non mi piacciono le formalità, quindi vai al sodo.";
			link.l1 = "Hai sentito parlare del nuovo bordello a Tortuga?";
			link.l1.go = "PZ2";
		break;
		
		case "PZ2":
			dialog.text = "Sei ubriaco? Che tipo di domanda è questa? Non sprecare il mio tempo se è di quello che volevi veramente parlare.";
			link.l1 = "Immagino tu non abbia sentito? È aperto un nuovo bordello lì - molto costoso, dove lavorano solo le ragazze più belle, sane e ben vestite.";
			link.l1.go = "PZ3";
		break;
		
		case "PZ3":
			dialog.text = "Oh, quello! Certo che ho sentito - chi non l'ha fatto?";
			link.l1 = "Ebbene, l'ho scoperto solo l'altro giorno.";
			link.l1.go = "PZ4";
		break;
		
		case "PZ4":
			dialog.text = "Ah-ah-ah-ah, birbante, sarò dannato! Ma ancora, perché lo stai discutendo con me? Perché non provi prima con Hawks? Ehi ehi. Anche se... ti sei già divertito lì?";
			if (CheckAttribute(pchar, "questTemp.PZ.EliteWhoreFucked"))
			{
				link.l1 = "Ce l'ho. Accettano solo dobloni, tra l'altro.";
				link.l1.go = "PZ_Fucked1";
			}
			else
			{
				link.l1 = "Ho visitato il posto, ma non ho usufruito dei servizi. Comunque...";
				link.l1.go = "PZ_NoFucked1";
			}
		break;
		
		case "PZ_Fucked1":
			dialog.text = "Allora sei venuto a pavoneggiarti! Ah, che birbante.";
			link.l1 = "Veramente, no. Volevo davvero chiederti qualcosa, Marcus.";
			link.l1.go = "PZ5";
		break;
		
		case "PZ_NoFucked1":
			dialog.text = "Non l'hai fatto?! Sei un idiota, De Maure. Se fossi in te...";
			link.l1 = "Avresti iniziato una vera e propria depravazione, lo so. Ma non è esattamente quello di cui volevo parlare con te.";
			link.l1.go = "PZ5";
		break;
		
		case "PZ5":
			dialog.text = "Cosa vuoi? Dai, non farmi stare in ansia.";
			link.l1 = "Sto cercando il proprietario di quel posto. Mi è stato detto che voleva incontrarti e offrirti un'opportunità di investimento nel suo commercio. Non puoi sbagliarti - è cinese.";
			link.l1.go = "PZ6";
		break;
		
		case "PZ6":
			dialog.text = "Ah ah. No, non ho avuto il piacere di incontrare donne cinesi ultimamente. Ma non mi dispiacerebbe incontrarla e investire nel suo business. Dopotutto, non si può semplicemente entrare nel territorio di Levasseur, e come suddito del tuo re, sarebbe costretto a sparare con le sue navi costiere alla mia 'Drago' non appena la vede.";
			link.l1 = "Sembra che stia considerando prima Port-au-Prince...";
			link.l1.go = "PZ7";
		break;
		
		case "PZ7":
			dialog.text = "Pensi così? È un errore. Anche se de Mussac ha più soldi di me, cosa che dubito, non può permettersi di destinare parte del budget della città a un bordello, non importa quanto oro porti.";
			link.l1 = "Buon punto. Chiaramente non ha ponderato questa sua ambizione.";
			link.l1.go = "PZ8";
		break;
		
		case "PZ8":
			dialog.text = "Sai, mi sono sempre chiesto come fanno gli altri bordelli a rimanere a galla. Non è la capacità di una donna di pensare e, soprattutto, di governare - segna le mie parole.";
			link.l1 = "Ebbene, ti sbagli su questo. Grazie per il tuo tempo, Marcus! Se la incontro prima io, le dirò che sarai lieto di vederla.";
			link.l1.go = "Exit";
			
			AddQuestRecord("PZ", "32");
			
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