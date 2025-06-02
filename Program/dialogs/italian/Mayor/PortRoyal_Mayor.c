// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Cosa vuoi? Chiedi pure.","Ti sto ascoltando, qual è la domanda?"),"Questa è la seconda volta che provi a chiedere...","Questa è la terza volta che stai cercando di chiedere...","Quando finirà questo?! Sono un uomo impegnato, lavoro su questioni coloniali e tu continui a infastidirmi!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Ho cambiato idea...","Non ora. Luogo e momento sbagliati."),"Vero... Ma più tardi, non ora...","Chiederò... Ma un po' più tardi...","Mi dispiace, "+GetAddress_FormToNPC(NPChar)+"...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "silk_8")
			{
				link.l1 = "Sua Eccellenza, vorrei segnalare un'attività commerciale illegale su quest'isola.";
                link.l1.go = "Mtraxx";
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "silk_12")
			{
				link.l1 = "Vorrei sentire un rapporto sulla tua missione riguardante il contrabbando di tela di seta per vele.";
                link.l1.go = "Mtraxx_4";
			}
			// Jason НСО
			if (CheckAttribute(pchar, "questTemp.Patria") && pchar.questTemp.Patria == "epizode_10_continue" && !CheckAttribute(npchar, "quest.slaveships"))
			{
				link.l1 = "Sono arrivato per conto del Governatore Generale Phillipe de Poincy. Il mio compito è portarti gli schiavi catturati dai Olandesi, è corretto?";
                link.l1.go = "patria_Sl";
			}
			if (CheckAttribute(npchar, "quest.slaveships.wait") && GetSquadronGoods(pchar, GOOD_SLAVES) >= 3000)
			{
				link.l1 = "Ti ho portato gli schiavi, come concordato.";
                link.l1.go = "patria_Sl_2";
			}
			if (CheckAttribute(pchar, "questTemp.Patria") && pchar.questTemp.Patria == "epizode_11_start" && CheckAttribute(pchar, "questTemp.Patria.Curacao.DoilyReady"))
			{
				link.l1 = "Sono arrivato su istruzioni del Governatore Generale Phillipe de Poincy per partecipare a una spedizione congiunta a Curacao contro gli Olandesi.";
                link.l1.go = "patria_Sl_4";
			}
			if (CheckAttribute(pchar, "questTemp.Patria") && pchar.questTemp.Patria == "epizode_11_wait" && GetCompanionQuantity(pchar) < 3)
			{
				link.l1 = "La mia squadra è diminuita, possiamo partire ora.";
                link.l1.go = "patria_Sl_6";
			}
		break;
		
		// Addon 2016-1 Jason пиратская линейка
		case "Mtraxx":
            dialog.text = "Interessante. Sono tutto orecchie.";
			link.l1 = "È di buona fonte che una brigantina olandese 'Utrecht' sotto colori inglesi sta scaricando grandi quantità di tela di seta a Portland Bay da molto tempo. Sono in attività da oltre un anno, durante la notte, tra il 10 e il 15 di ogni mese.";
			link.l1.go = "Mtraxx_1";
		break;
		
		case "Mtraxx_1":
            dialog.text = "Sei sicuro che la tua fonte può essere fidata?";
			link.l1 = "A volte non mi fido nemmeno di me stesso, tuttavia, l'uomo che ha rivelato queste informazioni è affidabile. Inoltre, non aveva motivo di mentire.";
			link.l1.go = "Mtraxx_2";
		break;
		
		case "Mtraxx_2":
			string sTemp = "this";
			if (sti(pchar.questTemp.Mtraxx.month == 1)) sTemp = "next";
            dialog.text = "Molto bene, capitano. Questa è una questione seria e devo agire in base alle informazioni presentate, anche se il tuo informatore ha mentito o si è semplicemente sbagliato. Manderò una pattuglia costiera all'orario specificato, e se le tue informazioni saranno confermate, sarai generosamente ricompensato, tali attività illegali devono essere severamente represse.";
			link.l1 = "Ti vedrò "+sTemp+" il 16 del mese. Sicuramente la situazione si risolverà da sola entro quel tempo.";
			link.l1.go = "Mtraxx_3";
		break;
		
		case "Mtraxx_3":
            DialogExit();
			pchar.questTemp.Mtraxx = "silk_11";
			int month = sti(pchar.questTemp.Mtraxx.month);
			pchar.quest.mtr_silk_smuggler.over = "yes";
			pchar.quest.mtr_silk_smuggler_over.over = "yes";
			DeleteQuestCondition("Mtraxx_SilkCreateSmuggler");
			DeleteQuestCondition("Mtraxx_SilkSmugglerFail");
			pchar.quest.mtr_silk_smuggler_patrol.win_condition.l1 = "Timer";
			pchar.quest.mtr_silk_smuggler_patrol.win_condition.l1.date.hour  = 6;
			pchar.quest.mtr_silk_smuggler_patrol.win_condition.l1.date.day   = 16;
			pchar.quest.mtr_silk_smuggler_patrol.win_condition.l1.date.month = GetAddingDataMonth(0, month, 0);
			pchar.quest.mtr_silk_smuggler_patrol.win_condition.l1.date.year  = GetAddingDataYear(0, month, 0);
			pchar.quest.mtr_silk_smuggler_patrol.function = "Mtraxx_SilkSmugglerPatrol";
			sTemp = "this";
			if (sti(pchar.questTemp.Mtraxx.month == 1)) sTemp = "next";
			AddQuestRecord("Roger_2", "19");
			AddQuestUserData("Roger_2", "sDate", sTemp);
			if (CharacterIsAlive("Mtr_Utreht"))
			{
				sld = CharacterFromID("Mtr_Utreht");
				sld.lifeday = 0;
			}
		break;
		
		case "Mtraxx_4":
            dialog.text = "Le tue informazioni si sono rivelate corrette, capitano. Abbiamo teso un'imboscata ai criminali durante la transazione. L''Utrecht' ha cercato di fuggire e ha combattuto, ma è stata affondata dalla nostra corvetta di pattuglia. Quattro acquirenti hanno resistito all'arresto. Uno è stato ucciso con un colpo, e gli altri tre sono fuggiti nella giungla. Il carico completo di 80 rotoli di seta è stato trasferito al tesoro di Port Royal. Anche se non siamo riusciti a determinare il capo di questa rete, l'uomo morto è non identificato, e gli altri sono fuggiti, dichiaro questa operazione un completo successo. Dubito che questi furfanti avranno il coraggio di ritornare qui mai più.\nHai reso un grande servizio a noi, capitano, con la tua diligenza e indicando i truffatori. Ecco 10.000 pesos come ricompensa.";
			link.l1 = "Molto obbligato, vostra Eccellenza. Sono felice di vedere che tutto è andato secondo i piani e i contrabbandieri hanno ottenuto ciò che meritavano. Con questo, vi lascio, buona giornata.";
			link.l1.go = "Mtraxx_5";
		break;
		
		case "Mtraxx_5":
            DialogExit();
			pchar.questTemp.Mtraxx = "silk_13";
			AddQuestRecord("Roger_2", "20");
			AddMoneyToCharacter(pchar, 10000);
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
			ChangeCharacterNationReputation(pchar, ENGLAND, 5);
			AddCharacterExpToSkill(pchar, "Leadership", 200);
		break;
		
		// Jason НСО
		case "patria_Sl":
			if (GetSquadronGoods(pchar, GOOD_SLAVES) < 500)
			{
				dialog.text = "Questo è preciso. Quanti schiavi hai portato?";
				link.l1 = "Sto ancora lavorando su di esso. Presto tornerò con i risultati.";
				link.l1.go = "patria_Sl_wait";
				break;
			}
			dialog.text = "È preciso. Quanti schiavi hai portato?";
			link.l1 = ""+FindRussianQtyString(GetSquadronGoods(pchar,GOOD_SLAVES))+".";
			if (GetSquadronGoods(pchar, GOOD_SLAVES) >= 3000) link.l1.go = "patria_Sl_2";
			else link.l1.go = "patria_Sl_1";
		break;
		
		case "patria_Sl_wait":
			DialogExit();
			npchar.quest.slaveships.wait = "true";
		break;
		
		case "patria_Sl_1":
			dialog.text = "Hmm, Chevalier ha promesso che non ci sarebbero stati meno di 3000 schiavi";
			link.l1 = "È vero. Questa è colpa mia: alcuni degli schiavi sono stati uccisi dal fuoco di cannoni di una nave nemica, alcuni sono morti per strada. Correggerò il mio errore e tornerò da te. Tutto sarà fatto secondo il contratto.";
			link.l1.go = "patria_Sl_wait";
		break;
		
		case "patria_Sl_2":
			DeleteAttribute(npchar, "quest.slaveships.wait");
			dialog.text = "Eccellente! Con Chevalier de Poincy si può davvero fare affari. Dite al Governatore Generale che la mia squadriglia per l'attacco a Curacao sarà pronta in un mese. Sono sicuro, mi manderà a te per questa campagna, quindi ci vedremo presto, Monsieur de Maure.";
			link.l1 = "Sarei felice di incontrarti di nuovo, Colonnello. E ora permettimi di fare i miei saluti.";
			link.l1.go = "patria_Sl_3";
		break;
		
		case "patria_Sl_3":
			DialogExit();
			npchar.quest.slaveships = "true";
			RemoveCharacterGoods(pchar, GOOD_SLAVES, GetSquadronGoods(pchar, GOOD_SLAVES));
			AddQuestRecord("Patria", "57");
			pchar.questTemp.Patria = "epizode_10_return";
			pchar.quest.Patria_SlaveShipsJamaicaTimeOver.over = "yes"; //снять таймер на доставку рабов
			SetFunctionTimerCondition("Patria_CuracaoDoilyReady", 0, 0, 30, false); // таймер на 1 месяц на готовность эскадры д'Ойли
			SetFunctionTimerCondition("Patria_CuracaoTimeOver", 0, 0, 62, false); // таймер на 2 месяца на туда-обратно к Пуанси
			SaveCurrentQuestDateParam("questTemp.Patria.Curacao.Date"); // запоминаем дату
			// меняем отношение наций
			pchar.questTemp.Patria.Friend = "true";
			LaunchNationLegend();
			DeleteAttribute(pchar, "questTemp.Patria.Friend");
			DoQuestCheckDelay("sea_victory", 0.2);
		break;
		
		case "patria_Sl_4":
			dialog.text = "Non ho dubitato che saresti tu. Ancora meglio! La nostra squadra è pronta. Nave da battaglia di 1° rango e due navi di 4° rango. La dimensione massima dell'intera squadra non deve superare le cinque navi.";
			if (GetCompanionQuantity(pchar) > 2)
			{
				link.l1 = "Allora lascerò le navi extra nei docks e ne terrò solo due. Otterremo cinque navi come risultato.";
				link.l1.go = "patria_Sl_5";
			}
			else
			{
				link.l1 = "Sì, esattamente cinque, e non di più. Dovremmo partire.";
				link.l1.go = "patria_Sl_6";
			}
		break;
		
		case "patria_Sl_5":
			DialogExit();
			pchar.questTemp.Patria = "epizode_11_wait";
		break;
		
		case "patria_Sl_6":
			dialog.text = "Perfetto. Ora ti spiegherò il piano secondo il quale agiremo: forse vorrai cambiare qualcosa o aggiungere qualcosa, poi ne discuteremo.";
			link.l1 = "Sono tutto orecchie, colonnello.";
			link.l1.go = "patria_Sl_7";
		break;
		
		case "patria_Sl_7":
			dialog.text = "Non ha senso catturare Curacao: è la principale colonia olandese nell'arcipelago, e anche se riusciamo a catturare la loro bandiera nella fortezza di Willemstad e issare una inglese o francese, sarà molto difficile mantenere l'isola. Gli olandesi faranno di tutto per riprenderla e la prenderanno di mira con squadroni militari. In generale, non ha senso catturarla poiché non è obbligatorio. Più importante per noi è costringere Steivesant a firmare il trattato con condizioni vantaggiose per noi, e per fare ciò sarà sufficiente distruggere le principali difese nemiche e mettere gli olandesi sotto la minaccia di completa distruzione della colonia di Willemstad.";
			link.l1 = "Di cosa tratterà il trattato?";
			link.l1.go = "patria_Sl_8";
		break;
		
		case "patria_Sl_8":
			dialog.text = "Il trattato è stato composto da me e dal Cavaliere de Poincy. Riguarda vari aspetti del commercio, la fine della 'guerra commerciale' tra la Compagnia e l'Inghilterra, il rifiuto delle pretese di Stuyvesant sull'isola di Sint Maarten e altri punti politici che sono di scarso interesse per te.";
			link.l1 = "Capito.";
			link.l1.go = "patria_Sl_9";
		break;
		
		case "patria_Sl_9":
			dialog.text = "Ecco il piano: prima di tutto, con tutte le forze attaccheremo il forte e lo distruggeremo. Gli olandesi si aspetteranno uno sbarco di truppe, ma non lo faremo, le perdite più grandi si verificano di solito mentre si prende un bastione dal mare. Invece, sbarcheremo squadre d'assalto in due punti dell'isola: a Capo Santa Maria e nella laguna di Blanca, e ci muoveremo via terra fino al cancello della città di Willemstad. Ho ordinato di portare con noi l'artiglieria da campo sulle navi - non ci sono cespugli impenetrabili a Curaçao, e saremo in grado di spostare i cannoni su ruote lungo il terreno senza difficoltà.\nMentre gli olandesi saranno perplessi su ciò che sta succedendo, prenderemo la città sotto mira dalla giungla e bloccheremo qualsiasi possibilità di inviare rinforzi dal forte via terra. Dopodiché, metteremo la città sotto il fuoco dei cannoni. Sicuramente la guarnigione del forte proverà ad attaccare, ma non potranno fare nulla contro i cannoni da campo e i nostri moschettieri, e se i loro cannoni tenuti nel forte saranno ancora funzionanti, non saranno in grado di portarli nella giungla.\nInoltre, le nostre navi simuleranno i preparativi per lo sbarco delle truppe dal mare per incutere paura nei nemici e abbassare il loro morale. Dopo un po' di tempo, quando gli olandesi saranno pienamente consapevoli della loro situazione disperata, chiameremo i parlamentari per negoziati. Che ne pensi, capitano?";
			link.l1 = "Piano brillante! E la cosa migliore è che non perderemo nessun soldato presso le mura del forte.";
			link.l1.go = "patria_Sl_10";
		break;
		
		case "patria_Sl_10":
			dialog.text = "Sono contento che le mie idee ti siano piaciute. Allora muoviamoci!";
			link.l1 = "Andiamo!";
			link.l1.go = "patria_Sl_11";
		break;
		
		case "patria_Sl_11":
			DialogExit();
			chrDisableReloadToLocation = true;
			pchar.questTemp.Patria = "epizode_11_continue";
			AddQuestRecord("Patria", "60");
			pchar.quest.Patria_CuracaoTimeOver.over = "yes"; // снять таймер 2 месяца
			LAi_SetActorType(npchar);
			ChangeCharacterAddressGroup(npchar, "PortRoyal_townhall", "goto", "goto4");
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 7.0);
			Patria_CuracaoSail();
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
