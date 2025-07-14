// Жак Барбазон в Ле Франсуа
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sLoc, sTemp;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

//--> -----------------------------------------------блок angry-------------------------------------------------
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
//<-- -------------------------------------------блок angry------------------------------------------------------

	switch(Dialog.CurrentNode)
	{
	// ----------------------------------- Диалог первый - первая встреча---------------------------------------
		case "First time":
            dialog.text = NPCStringReactionRepeat("Hai qualcosa da dirmi? No? Allora vattene da qui!","Credo di essermi spiegato chiaramente, smetti di infastidirmi.","Nonostante mi sia spiegato chiaramente, continui a infastidirmi!","Bene, sto perdendo la pazienza con questa maleducazione.","ripeti",3,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Me ne sto già andando.","Certo, Jacques...","Mi dispiace, Jacques...","Ahi...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			
			if (sti(pchar.GenQuest.Piratekill) > 20)
			{
				dialog.text = RandPhraseSimple("Sei impazzito? Volevi fare il macellaio? Tutti i pirati sono arrabbiati con te, ragazzo, faresti meglio a lasciare questo posto...","Sembra che tu sia impazzito, ragazzo. Volevi allungare un po' le mani? Senza offesa, ma qui non hai nulla da fare. Sparisci!");
				link.l1 = RandPhraseSimple("Ascolta, voglio risolvere la situazione...","Aiutami a risolvere questo problema...");
				link.l1.go = "pirate_town";
				break;
			}
			
		//----------------------------------Сага - искушение Барбазона---------------------------------------
			if (CheckAttribute(pchar, "questTemp.Saga.BarbTemptation") && pchar.questTemp.Saga.BarbTemptation == "begin")
			{
				link.l1 = "Ho bisogno di parlare con te, Jacques... In privato.";
				link.l1.go = "Temptation";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.BarbTemptation") && pchar.questTemp.Saga.BarbTemptation == "give_silk" && GetSquadronGoods(pchar, GOOD_SHIPSILK) >= 60)
			{
				link.l1 = "Vengo da Saint Martin, Jacques...";
				link.l1.go = "Temptation_6";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.BarbTemptation") && pchar.questTemp.Saga.BarbTemptation == "terrax")
			{
				link.l1 = "E quando smetterai di abbaiare e inizierai a parlare come un uomo, Jacques? Non ti aspettavi di vedermi?";
				link.l1.go = "terrax";
			}
			
			//поручение капитана - выкуп
			if (CheckAttribute(pchar, "GenQuest.CaptainComission") && NPChar.city == pchar.GenQuest.CaptainComission.PiratesCity)
			{
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.toMayor"))
				{
					link.l1 = "Sono qui per il vostro prigioniero.";
					link.l1.go = "CapComission1";
					DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
				}
             	
				if (pchar.GenQuest.CaptainComission.PirateShips == "died" || pchar.GenQuest.CaptainComission.PirateShips == "goaway") // лесник. новая проверка. искл. возможность сразу сдать задание,минуя 15 дней.
				{
					link.l1 = "Ciao, Jacques, sono qui per la tua missione.";
					link.l1.go = "CapComission3";
				}
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.RepeatSpeak") && !CheckAttribute(pchar,"GenQuest.CaptainComission.vikupzaplatil")) 
				{ // лесник . второй диалог с проверкой ,если ГГ ещё не принес деньги за выкуп.
					link.l1 = "Sono qui per il vostro prigioniero.";
					link.l1.go = "CapComission6";
				}
			}	
			if (CheckAttribute(pchar, "GenQuest.Marginpassenger") && pchar.GenQuest.Marginpassenger == "cabin")
			{
				link.l1 = "Sentito dire che sei impegnato in affari legati ai prigionieri...";
				link.l1.go = "Marginpassenger";
			}
		break;
			

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

        case "I_know_you_good":
            dialog.text = NPCStringReactionRepeat(GetFullName(pchar)+"! Cosa ti serve questa volta?","Hai dimenticato di dirmi qualcosa? Sto ascoltando.","Quanto durerà questo... Se non hai niente da fare, allora non disturbare gli altri!","Hai chiesto che io sia educato. Ma esigo lo stesso da te!","ripeti",10,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Non è niente. Solo una visita.","Niente...","Bene...","Hai ragione. Mi dispiace.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";

			if (sti(pchar.GenQuest.Piratekill) > 20)
			{
				dialog.text = RandPhraseSimple("Sei pazzo? Volevi fare il macellaio? Tutti i pirati sono arrabbiati con te, ragazzo, sarebbe meglio se te ne andassi da questo posto...","Sembra che tu sia impazzito, ragazzo. Volevi allungare un po' le mani? Senza offesa, ma qui non hai nulla da fare. Sparisci!");
				link.l1 = RandPhraseSimple("Ascolta, voglio risolvere la situazione...","Aiutami a risolvere questo problema...");
				link.l1.go = "pirate_town";
				break;
			}

			//поручение капитана - выкуп
			if (CheckAttribute(pchar, "GenQuest.CaptainComission") && CheckAttribute(pchar,"GenQuest.CaptainComission.toMayor"))
			{
				link.l1 = "Sono qui per il vostro prigioniero.";
				link.l1.go = "CapComission1";
				DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
			}	
			if (pchar.GenQuest.CaptainComission.PirateShips == "died" || pchar.GenQuest.CaptainComission.PirateShips == "goaway")//  правка лесник,новая проверка ,исключающая тут же сдачу задания
			{
				link.l1 = "Ciao, Jacques, riguarda la tua missione.";
				link.l1.go = "CapComission3";
			}
		/*	if(CheckAttribute(pchar,"GenQuest.CaptainComission.RepeatSpeak")) //лишний диалог лесник
			{
				link.l1 = "Sono qui per il vostro prigioniero.";
				link.l1.go = "CapComission6";
			}*/
			if (CheckAttribute(pchar, "GenQuest.Marginpassenger") && pchar.GenQuest.Marginpassenger == "cabin")
			{
				link.l1 = "Ho sentito dire che sei impegnato in affari legati ai prigionieri...";
				link.l1.go = "Marginpassenger";
			}
		break;

//--> -----------------------------------Сага - Искушение Барбазона---------------------------------------------
		case "Temptation":
			dialog.text = "Sai che disturbarmi è rischioso? Va bene, ti sto ascoltando.";
			link.l1 = "Devo un debito. Un debito grosso. Il tempo per pagare è vicino e non ho monete. Gente gentile ha sussurrato che hai un talento per fare piani e sai sempre dove trovare un grosso bottino...";
			link.l1.go = "Temptation_1";
		break;
		
		case "Temptation_1":
			dialog.text = "Ascolta, ragazzo! Io sono Jacques il Gentiluomo solo per coloro che mi sono leali. Per gli altri sono Barbazon e a volte Lucifero in persona. Come potrei sapere che posso fidarmi di te?";
			link.l1 = "Provami. Giuro che non te ne pentirai!";
			link.l1.go = "Temptation_2";
		break;
		
		case "Temptation_2":
			dialog.text = "Hm... Presumo tu sappia cosa fa Jacques l'Umano a quelli che lo ingannano, vero? In ogni caso, non ti confonderò con terribili dettagli. Ho una piccola missione. Se avrai successo, tutti i tuoi problemi finanziari spariranno.";
			link.l1 = "Non dubitare di me, sono stato in molte battaglie e...";
			link.l1.go = "Temptation_3";
		break;
		
		case "Temptation_3":
			dialog.text = "Taci e ascolta! Un paio di settimane fa una pattuglia olandese ha catturato uno dei miei impiegati non lontano da Saint Martin. Stava consegnando della seta olandese a me. È molto rara, gli olandesi la portano qui solo in piccole quantità per le necessità della marina della Compagnia.\nCosì, sono riuscito a sottrarre sei balle di seta e Simon Morel doveva portarmele sulla sua brigantina 'Cane Salato', ma ha incontrato una pattuglia olandese per caso. O non per caso. È quello che ha detto il navigatore di Morel, mi ha raccontato che è stato l'unico sopravvissuto alla lotta.\nMi ha anche dato il registro di bordo di Morel che conferma la storia. Secondo il registro, Morel aveva gettato via la seta durante un tentativo di fuga. È strano, vero? La seta è leggera. Avrebbero dovuto gettare i loro cannoni, comunque non avevano speranze contro la pattuglia.";
			link.l1 = "Qualcosa qui non va proprio.";
			link.l1.go = "Temptation_4";
		break;
		
		case "Temptation_4":
			dialog.text = "Tutto è possibile. Molti uomini coraggiosi lavorano per me e molti meno intelligenti. Nessuna offesa, eh. Devi controllare il luogo dove Morel ha scaricato la merce. È 21 gradi 10' Nord e 61 gradi 30' Ovest secondo il registro del capitano.\nGli olandesi avvolgono la seta attorno a bastoni di sughero, quindi le balle dovrebbero ancora galleggiare sull'acqua. Ci devono essere sei balle. Prendi il largo immediatamente, il tempo è fondamentale.";
			link.l1 = "Sono sulla mia strada!";
			link.l1.go = "Temptation_5";
		break;
		
		case "Temptation_5":
			DialogExit();
			SetFunctionTimerCondition("Saga_BarbTemptationOver", 0, 0, 10, false); // таймер
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			pchar.quest.BarbTemptation.win_condition.l1 = "location";
			pchar.quest.BarbTemptation.win_condition.l1.location = "SentMartin";
			pchar.quest.BarbTemptation.function = "Saga_BarbTemptationBarkas";
			pchar.questTemp.Saga.BarbTemptation = "silk";
			AddQuestRecord("BarbTemptation", "2");
		break;
		
		case "Temptation_6":
			dialog.text = "Ottimo! Hai trovato la mia seta?";
			link.l1 = "Sì, sei di loro come hai detto.";
			link.l1.go = "temptation_wrong";
			if (GetSquadronGoods(pchar, GOOD_SHIPSILK) >= 90)
			{
				link.l2 = "Sì. Ma ce n'erano di più di quanto hai detto, nove, non sei. Li ho portati tutti qui, il tuo compito è capire come sia potuto accadere.";
				link.l2.go = "temptation_right";
			}
		break;
		
		case "temptation_wrong":
			dialog.text = "Risposta sbagliata. Avrebbero dovuto esserci nove balle. E se ne hai trovate sei, allora devi aver trovato anche le restanti. Quindi sei o un topo o solo un idiota pigro. Mi devi tre balle di seta e altre tre come.. 'compensazione morale' per aver cercato di truffarmi.";
			if (GetSquadronGoods(pchar, GOOD_SHIPSILK) >= 120)
			{
				link.l1 = "Che furbo! Me lo ricorderò. Ecco la tua seta e dimentichiamoci del mio errore.";
				link.l1.go = "temptation_wrong_1";
			}
			link.l2 = "Mi hanno detto che c'erano sei balle, non una balla di più. Ti ho dato tutto quello che ho trovato e non me ne frega niente dei tuoi pensieri. Non ho più seta.";
			link.l2.go = "temptation_wrong_2";
		break;
		
		case "temptation_wrong_1":
			RemoveCharacterGoods(pchar, GOOD_SHIPSILK, 120);
			dialog.text = "Bene. Spero che non succeda di nuovo perché voglio darti un compito importante. Quanti soldi vuoi guadagnare?";
			link.l1 = "I soldi sono sempre ben accetti, per ora cinquantamila pesos andrebbero bene.";
			link.l1.go = "junior";
		break;
		
		case "temptation_wrong_2":
			dialog.text = "Oh, così parli ora! Non te la caverai con questa. Ti ho avvertito - non cercare maledettamente di imbrogliarmi! Guardie! C'è un maledetto topo nella residenza!";
			link.l1 = "Merda!";
			link.l1.go = "temptation_wrong_fight";
		break;
		
		case "temptation_wrong_fight":
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetWarriorType(npchar);
			ChangeCharacterAddressGroup(npchar, "LeFransua_townhall", "goto", "goto1");
			LAi_SetImmortal(npchar, true);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			for (i = 1; i <= 3; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("BarbGuard_"+i, "citiz_4"+(i+6), "man", "man", 80, PIRATE, 1, true, "quest"));
				FantomMakeCoolFighter(sld, 80, 100, 100, "blade_21", "pistol4", "bullet", 3000);
				ChangeCharacterAddressGroup(sld, "LeFransua_townhall", "reload", "reload1");
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "temptation_right":
			RemoveCharacterGoods(pchar, GOOD_SHIPSILK, 80);
			dialog.text = "Ottimo lavoro. Ti stavo mettendo alla prova per la tua avidità e hai superato il mio test. Dovevano esserci nove balle. Una di loro è tua. Ora possiamo parlare seriamente. Quanto denaro ti serve?";
			link.l1 = "I soldi sono sempre ben accetti, per ora cinquantamila pesos andrebbero bene.";
			link.l1.go = "junior";
		break;
		
		case "junior":
			dialog.text = "Hai l'opportunità di guadagnare ancora di più. Un uomo serio mi ha chiesto di trovare un tipo affidabile come te per una missione delicata e pericolosa. Quest'uomo è molto ricco e ti ricompenserà di conseguenza se non lo deluderai.";
			link.l1 = "Sono pronto.";
			link.l1.go = "junior_1";
		break;
		
		case "junior_1":
			dialog.text = "Bene. Ascolta ora. Devi trovare il suo agente chiamato 'Knave'. È il capitano del polacco 'Marlin', questo è tutto ciò che so di lui. Lo troverai a Kapsterville. La parola d'ordine è 'la caccia è iniziata'. Ti dirà cosa fare. Non mi devi nulla. Voglio solo aiutarti. Se sarai abbastanza fortunato, ci incontreremo di nuovo.";
			link.l1 = "Grazie per il tuo aiuto. Sono sulla mia strada!";
			link.l1.go = "junior_2";
		break;
		
		case "junior_2":
			DialogExit();
			AddQuestRecord("BarbTemptation", "7");
			Saga_SetJuniorInCharles(); // ставим Валета
			pchar.questTemp.Saga.BarbTemptation = "valet";
		break;
		
		case "terrax":
			dialog.text = "Cosa?! Strapperò via il tuo...";
			link.l1 = "Non lo farai, Barbazon. Vediamo le nostre carte! Lavoro per Jan Svenson. Ho svelato la tua cospirazione con Jackman. So tutto, quello che stavi pianificando e che ruolo avevi anche tu. Jackman e suo fratello sono morti, il primo ha ucciso Blaze Sharp e questo ha deciso il suo destino, il secondo non era abbastanza loquace, temo...";
			link.l1.go = "terrax_1";
		break;
		
		case "terrax_1":
			dialog.text = "Maledizione! Tyrex non mi perdonerà mai per questo, ma io sono ancora..";
			link.l1 = "Non fare nulla di stupido, Jacques. Sapevo che non sarebbe stata una conversazione facile, quindi mi sono preservato. Dai un'occhiata alla finestra... la tua baracca è circondata dai miei moschettieri. La mia gente è tutta intorno al tuo villaggio e c'è un gruppo di forza d'urto proprio fuori dalle porte. Vuoi iniziare un massacro? Abbastanza facile!";
			link.l1.go = "terrax_2";
		break;
		
		case "terrax_2":
			dialog.text = " dannazione a te! Cosa vuoi?";
			link.l1 = "Non mi crederai, Barbazon, ma tutto ciò che voglio è... Pace! Voglio la pace. Ecco perché non dirò a Tyrex del tuo ruolo in questa cospirazione contro di lui. Ma solo se farai ciò che voglio...";
			link.l1.go = "terrax_3";
		break;
		
		case "terrax_3":
			dialog.text = "Cosa vuoi da me? Soldi? Quanto?";
			if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) // Акула жив
			{
				link.l1 = "Oh, no, lascia fare ai tuoi agenti senza cervello. Ho bisogno di qualcosa di diverso. Ho bisogno del tuo voto per Steven Dodson.";
			}
			else
			{
				link.l1 = "Oh, no, lascia fare ai tuoi agenti senza cervello. Ho bisogno di qualcosa di diverso. Ho bisogno del tuo voto per Marcus Tyrex.";
			}
			link.l1.go = "terrax_4";
		break;
		
		case "terrax_4":
			if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "And Steven Dodson is on our side.";
			else sTemp = "";
			dialog.text = "Sul serio? Fammi pensare... e se dico di no?";
			link.l1 = "Allora starai da solo. Assolutamente solo. Svenson, Tyrex e Hawk si metteranno contro di te."+sTemp+"Mostrerò solo loro la lettera del Birbante, il fratello di Jackman, e anche la mia parola sarà fidata. Ora, per quanto tempo pensi, resterai seduto nel tuo posto accogliente dopo questo?";
			link.l1.go = "terrax_5";
		break;
		
		case "terrax_5":
			dialog.text = "Falco? È vivo?!";
			link.l1 = "Lo è. L'ho salvato dalla trappola fatta da Jackman. Quindi il più stretto amico di Jacob sarà il suo nemico di sangue. E mi unirò a loro, ricordatelo, Barbazon.";
			link.l1.go = "terrax_6";
		break;
		
		case "terrax_6":
			dialog.text = "Jackman non è mio amico! Dannazione! Mi avete messo all'angolo!";
			link.l1 = "Sciocchezze. Dai il tuo voto all'uomo di cui ti ho parlato e nulla cambierà per te. Te l'ho già detto, Jacques, voglio la pace. Potrei far sì che tutti i baroni ti odino, ma non lo farò... ancora.";
			link.l1.go = "terrax_7";
		break;
		
		case "terrax_7":
			GiveItem2Character(pchar, "splinter_jb"); // дать осколок
			dialog.text = "Bene. D'accordo. Hai la mia parola. Prendi il mio frammento di pietra, ne hai bisogno, ho ragione?";
			link.l1 = "Esattamente. Sono contento che abbiamo raggiunto un accordo, Jacques. E prendi la lettera del 'Birbante' come un dolce ricordo. O meglio ancora, bruciala, non vorrai che venga trovata. Ah, e un'ultima cosa...";
			link.l1.go = "terrax_8";
		break;
		
		case "terrax_8":
			RemoveItems(pchar, "letter_chad", 1);
			dialog.text = "Un'altra cosa?! Di che altro hai bisogno da me?";
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Corrida.Barbazon"))
			{
				link.l1 = "Lascia che ti ricordi qualcosa. Non molto tempo fa hai mandato il tuo cane Ignacio Marco ad assassinarmi. Sono stato io a ucciderlo. Sono stato io a seppellire il tuo piano di saccheggiare un galeone d'oro spagnolo. Sono stato io a mandare i tuoi amici nell'imboscata spagnola vicino a Saint Martin. Il mio nome è Charlie Prince! Abbiamo finito ora, Jacques, e sii più educato con me, la prossima volta che ci vediamo. Credimi, 'ragazzo', ci incontreremo di nuovo, e più di una volta, immagino.";
				link.l1.go = "terrax_8_1";
			}
			else
			{
				if (!CheckAttribute(pchar, "questTemp.Mtraxx.Corrida.Barbazon") && CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "full_complete_end")
				{
					link.l1 = "Lascia che ti ricordi qualcosa. Non molto tempo fa hai mandato il tuo cane Ignacio Marco ad assassinarmi. Sono stato io a ucciderlo. Sono stato io a seppellire il tuo piano di saccheggiare un galeone d'oro spagnolo. Il mio nome è Charlie Prince! Abbiamo finito ora, Jacques, e sii più gentile con me, la prossima volta che ci vediamo. Credimi, 'ragazzo', ci incontreremo di nuovo, e più di una volta immagino. Non dimenticare, ho ogni barone dei pirati dalla mia parte. Addio, Barbazon...";
					link.l1.go = "terrax_9";
				}
				else
				{
					link.l1 = "Sii più educato con me la prossima volta che ci vediamo. Credimi, 'ragazzo', ci incontreremo di nuovo, e più di una volta immagino. Non dimenticare, ho ogni barone dei pirati dalla mia parte. Addio, Barbazon...";
					link.l1.go = "terrax_9";
				}
			}
		break;
		
		case "terrax_8_1":
			dialog.text = "";
			link.l1 = "Non dimenticare, ho ogni barone pirata dalla mia parte. Addio, Barbazon...";
			link.l1.go = "terrax_9";
		break;
		
		case "terrax_9":
			DialogExit();
			NextDiag.CurrentNode = "I_know_you_good";
			AddQuestRecord("BarbTemptation", "26");
			if (CheckCharacterItem(pchar, "splinter_mt") && CheckCharacterItem(pchar, "splinter_jb") && CheckCharacterItem(pchar, "splinter_zm")) Saga_GiveCalendar();
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("Saga_SGM_"+i);
				LAi_SetCitizenType(sld);
				LAi_SetActorType(sld);
				LAi_ActorFollow(sld, pchar, "", -1);
				sld.lifeday = 0;
			}
			ChangeCharacterComplexReputation(pchar, "fame", 1);
			bDisableFastReload = false;
			LAi_LocationFightDisable(&Locations[FindLocation("LeFransua_town")], false);
		break;

//-----------------------------------Поручение капитана - Выкуп-------------------------------------------------
		case "CapComission1":
			dialog.text = "Ha-ha. Pensi che io abbia solo un prigioniero qui? Nominalo.";
			link.l1 = pchar.GenQuest.CaptainComission.SlaveName+". È qui?";
			link.l1.go = "CapComission2";
			DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
		break;

		case "CapComission2":
			if(CheckAttribute(pchar,"GenQuest.CaptainComission.DaysLeft"))
			{
				dialog.text = "Era. L'ho venduto a quel proprietario di piantagioni da Barbados - colonnello Bishop, quando era qui una settimana fa.";
				link.l1 = "Maledizione...";
				link.l1.go = "CapComission2_1";
			}
			else
			{
				dialog.text = "Ah, finalmente. Stavo pensando di venderlo a quel proprietario di piantagioni di Barbados, sarà qui tra una settimana o due... Hai un riscatto?";
				link.l1 = "Guarda, c'è un piccolo problema... In realtà, non ho molti soldi. Ma sono pronto a lavorare.";
				link.l1.go = "CapComission2_2";
				if(makeint(pchar.money) > 150000)
				{
					link.l2 = "È un bene che tu non lo abbia venduto. Ecco le tue monete - 150.000 pesos. Dove posso prenderlo?";
					link.l2.go = "CapComission2_3";
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
			link.l1 = "Ascolta, per quanto lo hai venduto se non è un segreto?"; 
			link.l1.go = "CapComission2_12";
		break;
		
		case "CapComission2_12":
			dialog.text = "Eh, non lo è. Ma non te lo dirò... Riderai se lo faccio. Ha-ha-ha-ha! Addio.";
			link.l1 = "Arrivederci.";
			link.l1.go = "exit";
			AddQuestRecord("CaptainComission1", "10");
			AddQuestUserData("CaptainComission1", "sName", "Jacques Barbazon");//правка лесник.  в СЖ запись ниже не работает																																				  
			//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			CaptainComission_GenerateManager();
		break;
		
		case "CapComission2_2":
			if(rand(3) == 1)
			{

				dialog.text = "Bene, "+pchar.name+", sai, non funziona così. Torna con i soldi e avrai il tuo deboluccio, ah-ah.";
				link.l1 = "Bene. Ci vediamo.";
				link.l1.go = "CapComission2_4";
			}
			else
			{
				dialog.text = "Bene, bene.. Ho degli affari... Non so nemmeno da dove cominciare. Ho bisogno di affondare un pirata che ha oltrepassato il limite.";
				link.l1 = "Non può semplicemente essere ucciso nella giungla?";
				link.l1.go = "CapComission2_2_1";
			}
		break;

		case "CapComission2_2_1":
			dialog.text = "Non è così che funziona il business, sai... Non ho bisogno della sua morte, devo insegnare a certa gente a evitare di prendere la mia parte del bottino. Ma se finisce a nutrire gli squali, non mi dispiacerà.";
			link.l1 = "Perché non mandi la tua gente a cercarlo?";
			link.l1.go = "CapComission2_2_2";
		break;
		
		case "CapComission2_2_2":
			CaptainComission_GetRandomShore();
			pchar.GenQuest.CaptainComission.ShipName1 = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.GenQuest.CaptainComission.ShipName2 = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.GenQuest.CaptainComission.UnknownPirateName = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);
			sLoc = XI_ConvertString(pchar.GenQuest.CaptainComission.Island + "Dat"); // belamour gen
			dialog.text = "Mm... Beh, "+GetName(NAMETYPE_ORIG,pchar.GenQuest.CaptainComission.UnknownPirateName,NAME_NOM)+" ha convinto alcuni pirati che la loro parte di bottino si trova nel nostro nascondiglio non lontano da "+XI_ConvertString(pchar.GenQuest.CaptainComission.Island.Shore+"Gen")+". Le loro due navi '"+pchar.GenQuest.CaptainComission.ShipName1+"' e '"+pchar.GenQuest.CaptainComission.ShipName2+"' ha levato l'ancora poco tempo fa e navigato verso "+sLoc+". Ora capisci perché non posso fidarmi dei miei uomini per fare quel lavoro?";
			link.l1 = "Lo faccio. Quanto tempo ho?";
			link.l1.go = "CapComission2_2_3";
		break;
		
		case "CapComission2_2_3":
			dialog.text = "Da 12 a 15 giorni non di più, è importante per me se non arriveranno al nascondiglio, o sarà inutile affondarli con un carico prezioso. In quel caso, sarebbe meglio se lo portassero qui...";
			link.l1 = "Bene, sono dentro. Cercherò di prenderli.";
			link.l1.go = "CapComission2_2_4";
		break;
		
		case "CapComission2_2_4":
			AddQuestRecord("CaptainComission1", "24");
			AddQuestUserData("CaptainComission1", "sName", "Jacques Barbazon");//правка
			//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));// в СЖ не работает имя . лесник
			AddQuestUserData("CaptainComission1", "sShipName1", pchar.GenQuest.CaptainComission.ShipName1);
			AddQuestUserData("CaptainComission1", "sShipName2", pchar.GenQuest.CaptainComission.ShipName2);
			AddQuestUserData("CaptainComission1", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.Island.Shore + "Dat")); // belamour gen
			AddQuestUserData("CaptainComission1", "sShoreType", XI_ConvertString(GetIslandByArealName(pchar.GenQuest.CaptainComission.Island) + "Voc")); // belamour gen
			pchar.quest.CapComission_PirateAttack.win_condition.l1 = "location";
            pchar.quest.CapComission_PirateAttack.win_condition.l1.location = pchar.GenQuest.CaptainComission.Island;
            pchar.quest.CapComission_PirateAttack.function = "CaptainComission_GeneratePirateShips"; 
			SetFunctionTimerCondition("CaptainComission_PirateShipsOver", 0, 0, 15, false);
			
			DialogExit();
		break;
		
		case "CapComission2_3":
			dialog.text = "Non preoccuparti. I miei uomini lo consegneranno alla tua nave. E perché ti importa di lui?";
			link.l1 = "Non lo faccio. I suoi parenti mi hanno chiesto di consegnarlo.";
			link.l1.go = "CapComission2_31";
		break;
		
		case "CapComission2_31":
			dialog.text = "Ah, va bene. Quasi mi dispiaceva per aver dato un prezzo così basso per il tuo uomo. Ha-ha-ha-ha! Addio.";
			link.l1 = "Ci vediamo.";
			link.l1.go = "CapComission2_32";
		break;
		
		case "CapComission2_32":
			AddQuestRecord("CaptainComission1", "9");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc")); // belamour gen
			addMoneyToCharacter(pchar, -150000);
			pchar.GenQuest.CaptainComission.vikupzaplatil = true; // новая проверка ,если шарль заплатил выкуп за пленника. лесник																																								
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");	
		break;
		
		case "CapComission2_4":
			if(!CheckAttribute(pchar,"GenQuest.CaptainComission.RepeatSpeak"))
			{
				AddQuestRecord("CaptainComission1", "31");
				AddQuestUserData("CaptainComission1", "sName", "Jacques Barbazon");		// лесник																												  
				//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM)); в СЖ не работает
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
			dialog.text = "Accidenti! Li hai incontrati o no, ora non importa! E quale sarà il tuo prossimo suggerimento?";
			link.l1 = "Forse hai un lavoro più facile per me?";
			link.l1.go = "CapComission4_1";
			link.l2 = "Ascolta, "+NPChar.name+", abbassa il prezzo per il prigioniero...";
			link.l2.go = "CapComission4_2";
		break;
		
		case "CapComission4_1":
			dialog.text = "No.";
			link.l1 = "Allora, addio...";
			link.l1.go = "CapComission4_3";
		break;
		
		case "CapComission4_2":
			dialog.text = "Abbassare il prezzo?! Ho appena perso la mia merce a causa della tua incompetenza! Ed ora potrei alzare il prezzo! Puoi prenderlo per 200.000 pesos se vuoi, o puoi andartene all'inferno da qui.";
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
			AddQuestUserData("CaptainComission1", "sName", "Barbazon"); // лесник																			  
			//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_DAT));// в СЖ не работает
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			DialogExit();
		break;
		
		case "CapComission4_4":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			AddQuestRecord("CaptainComission1", "28");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", "Barbazon"); // правка	// лесник																	  
			//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM)); в сж не работает
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			DialogExit();		
		break;
		
		case "CapComission4_5":
			dialog.text = "Tu puoi prenderti questo deboluccio...";
			link.l1 = "Addio.";
			link.l1.go = "CapComission4_6";
		break;
		
		case "CapComission4_6":
			addMoneyToCharacter(pchar, -200000);
			AddQuestRecord("CaptainComission1", "29");
			AddQuestUserData("CaptainComission1", "sName", "Barbazon"); // правки имени в сж лесник
			//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));//в СЖ не работает // belamour gen : это хорошо, но закомментить нужно было)))
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
			dialog.text = "Hai portato il riscatto"+GetSexPhrase("","ла")+"? Non stavo scherzando quando ho detto che lo avrei venduto ai piantatori.";			
			link.l1 = "Ascolta, "+NPChar.name+", c'è una cosa... Insomma, non ho abbastanza soldi. Ma sono pronto"+GetSexPhrase("","а")+" sbrigati.";
			link.l1.go = "CapComission2_2";
			if(makeint(pchar.money) > 150000)
			{
				link.l2 = "È un bene che non lo hai venduto. Ecco le tue monete - 150000 pesos. Dove posso prenderlo?"link.l2.go ="CapComission2_3";
			}			
		break;*/
		  case "CapComission6":                        // лесник . пусть шарль бабло ищет,или забить на пленника.
			dialog.text = "Hai portato i soldi? Non scherzavo quando ho detto che avrei venduto quell'uomo alla piantagione.";			
			link.l1 = "Non ho i soldi, "+NPChar.name+", ma ci sto lavorando.";
			link.l1.go = "exit";
			if(makeint(pchar.money) > 150000)
			{
				link.l2 = "È bene che tu non l'abbia venduto. Ecco le tue monete - 150.000 pesos. Dove posso prenderlo?"link.l2.go ="CapComission2_3";
			}			
		break;
																																					 																																													  																																															
//--------------------------------------------Похититель------------------------------------------------------
		case "Marginpassenger":
			dialog.text = "E perché ti importa di quello che faccio? Sai, faresti meglio ad andartene...";
			link.l1 = "Tshh, calmati. Ho affari con te. Riguarda il tuo prigioniero.";
			link.l1.go = "Marginpassenger_1";
		break;
		
		case "Marginpassenger_1":
			dialog.text = "Ah, va bene. Chi vuoi riscattare?";
			link.l1 = "Aspetta. Non sono qui per comprare, sono qui per offrirti di comprare un prigioniero. E beh, avrai l'opportunità di ottenere un riscatto per lui.";
			link.l1.go = "Marginpassenger_2";
		break;
		
		case "Marginpassenger_2":
			dialog.text = "Hm. E perché hai bisogno della mia agenzia? Perché non vuoi ottenere i soldi direttamente per te stesso?";
			link.l1 = "È piuttosto rischioso per me. Potrei avere problemi con le autorità.";
			link.l1.go = "Marginpassenger_3";
		break;
		
		case "Marginpassenger_3":
			dialog.text = "Ha-h... va bene allora. Diamo un'occhiata. Chi è il tuo prigioniero?";
			link.l1 = "Questo è "+pchar.GenQuest.Marginpassenger.Text+" "+XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.City+"Gen")+".";
			link.l1.go = "Marginpassenger_4";
		break;
		
		case "Marginpassenger_4":
			int iTemp = makeint(sti(pchar.GenQuest.Marginpassenger.Dublon)*2*stf(pchar.GenQuest.Marginpassenger.Chance))*100;
			dialog.text = "Capisco... sarebbe un bel commercio se non stai mentendo. Suppongo che potrei pagarti per quest'uomo "+iTemp+" pesos o darti qualche informazione interessante al posto. È la tua scelta.";
			link.l1 = "È meglio che prenda i pesos. Ne ho avuto abbastanza di questo affare...";
			link.l1.go = "Marginpassenger_money";
			link.l2 = "Ah! Raccontami di più. Sono sicuro che mi darai qualcosa di interessante.";
			link.l2.go = "Marginpassenger_offer";
		break;
		
		case "Marginpassenger_money":
			dialog.text = "Allora denaro. Prendilo. Ora, non è più un tuo problema. Consegna qui l'oggetto della vendita.";
			link.l1 = "Dovrebbe essere già vicino alle porte della città. Grazie! Mi hai davvero aiutato.";
			link.l1.go = "Marginpassenger_money_1";
		break;
		
		case "Marginpassenger_money_1":
			iTemp = makeint(sti(pchar.GenQuest.Marginpassenger.Dublon)*2*stf(pchar.GenQuest.Marginpassenger.Chance))*100;
			dialog.text = "Prego, portami altro... Ci vediamo!";
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
			pchar.GenQuest.Marginpassenger.Goods = GetRandomGood(FLAG_GOODS_TYPE_EXPORT, FLAG_GOODS_VALUABLE_WOOD);
			pchar.GenQuest.Marginpassenger.GoodsQty = 200+rand(10)*10;
			switch (hrand(1))
			{
				case 0: //бухта на южном мейне
					SelectSouthshore();
					while (!isLocationFreeForQuests(pchar.GenQuest.Marginpassenger.Shore)) SelectSouthshore();
					dialog.text = "È bello fare affari con un uomo intelligente. Ora ascolta: tra qualche giorno "+XI_ConvertString(pchar.GenQuest.Marginpassenger.Shore+"Dat")+" arriverà un' spedizione spagnola dal continente, carica di merci preziose. Aspetteranno una nave destinata a prendere il carico. Se arrivi lì in una settimana, avrai l'opportunità di prendere il carico per te stesso.\nSe fossi in te, sarei già in movimento verso la mia nave. E portami il prigioniero qui.";
					link.l1 = "Grazie! Le merci saranno una bella compensazione per i miei guai. E il mio passeggero dovrebbe già essere vicino alle porte della città. Ti sarà portato.";
					link.l1.go = "Marginpassenger_offer_1";
				break;
				
				case 1: //просто кораблик
					SelectSouthcity();
					pchar.GenQuest.Marginpassenger.ShipName1 = GenerateRandomNameToShip(SPAIN);
					dialog.text = "È bello fare affari con un uomo intelligente. Ora ascolta: tra circa una settimana una brigantina spagnola '"+pchar.GenQuest.Marginpassenger.ShipName1+"' carico di merci preziose salperà da "+XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Southcity+"Gen")+" a "+XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Southcity1+"Gen")+". Se ti affretti, lo prenderai facilmente.\nSei ancora qui? Se fossi in te, sarei già in movimento verso la mia nave. E porta il prigioniero qui.";
					link.l1 = "Grazie! Le merci saranno una bella compensazione per i miei guai. E il mio passeggero dovrebbe essere già vicino alle porte della città. Sarà portato da te.";
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
			AddQuestUserData("Marginpassenger", "sShore", XI_ConvertString(pchar.GenQuest.Marginpassenger.Shore+"Dat"));//лесник - окончание в СЖ // belamour gen
			AddQuestUserData("Marginpassenger", "sName", "Jacques the Kindman"));
			SetFunctionTimerCondition("Marginpassenger_SouthshoreOver", 0, 0, 7, false);
			pchar.quest.Marginpassenger.win_condition.l1 = "location";
			pchar.quest.Marginpassenger.win_condition.l1.location = pchar.GenQuest.Marginpassenger.Shore;
			pchar.quest.Marginpassenger.function = "Marginpassenger_Southshore";
		break;
		
		case "Marginpassenger_offer_2":
			DialogExit();
			AddQuestRecord("Marginpassenger", "16");
			AddQuestUserData("Marginpassenger", "sName", "Jacques the Kindman"));
			AddQuestUserData("Marginpassenger", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Southcity+"Gen"));
			AddQuestUserData("Marginpassenger", "sCity1", XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Southcity1+"Acc")); // лесник - окончание в СЖ
			AddQuestUserData("Marginpassenger", "sShipName", pchar.GenQuest.Marginpassenger.ShipName1);
			SetFunctionTimerCondition("Marginpassenger_SouthshipInWorld", 0, 0, 5+rand(2), false);
		break;
		
//---------------------------------------попытка залезть в сундуки --------------------------------------------
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Rapina!!! Questo è inaccettabile! Preparati, "+GetSexPhrase("ragazzo","ragazza")+"...","Ehi, cosa diavolo stai facendo lì?! Pensavi di poter rubare da me? Sei finito... ","Aspetta, che diavolo? Toglimi le mani di dosso! Allora sei un ladro! Fine della corsa, bastardo...");
			link.l1 = LinkRandPhrase("Merda!","Carramba!!","Maledizione!!");
			link.l1.go = "PL_Q3_fight";
		break;
					
// ----------------------------------------------блок нод angry--------------------------------------------------
		case "AngryRepeat_1":
            dialog.text = "Vattene da qui!";
			link.l1 = "Oops...";
		    link.l1.go = "AngryExitAgainWithOut";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся через 10 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "Non infastidirmi con le tue chiacchiere da quattro soldi. La prossima volta, il risultato non ti piacerà...";
        			link.l1 = "L'ho preso.";
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
            }
    	break;
		case "AngryRepeat_2":
            dialog.text = RandPhraseSimple("È finita, niente chiacchiere.","Non voglio più parlarti, quindi sarebbe meglio se non mi disturbassi.");
			link.l1 = RandPhraseSimple("Come desideri...","Mh, va bene allora...");
		    link.l1.go = "AngryExitAgain";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся через 10 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "Spero che mostrerai più rispetto e smetterai di essere maleducato?";
        			link.l1 = "Puoi starne sicuro, Jacques, lo farò.";
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
            DoReloadCharacterToLocation("LeFransua_town","reload","reload6");
		break;
		
		case "pirate_town":
            dialog.text = "Risolvere il problema? Capisci cosa hai fatto? Comunque, portami un milione di pesos e convincerò i ragazzi a dimenticare le tue 'imprese'. Se l'idea non ti piace, allora puoi andare all'inferno.";
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
            dialog.text = "Bene! Considerati di nuovo pulito. Ma spero che non farai più queste cose disgustose.";
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
