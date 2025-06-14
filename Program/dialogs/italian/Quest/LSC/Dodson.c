// Акула: Стивен Додсон
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			// Jason НСО
			if(CheckAttribute(pchar, "questTemp.Patria.DodsonFail"))
			{
				dialog.text = "Charles, che diavolo!";
				link.l1 = "Steven, c’è stato un imprevisto. Non sono riuscito né a venire né ad avvisarti della mia assenza...";
				link.l1.go = "patria_33";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.DodsonAgain"))
			{
				dialog.text = "Felice di vederti, compare! Come posso darti una mano? ";
				link.l1 = "Felice di vederti anch’io. Volevo ringraziarti per lo spettacolo orchestrato alla perfezione!";
				link.l1.go = "patria_29";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Saga.Shark") && pchar.questTemp.Patria == "epizode_12_pirates")
			{
				dialog.text = "Felice di vederti, compare! Che posso fare per te?";
				link.l1 = "Ho una proposta per te. Roba da pirati, capisci!";
				link.l1.go = "patria";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Saga.Shark") && pchar.questTemp.Patria == "epizode_12_talk")
			{
				dialog.text = "Ecco il nostro cliente! Il lavoro è fatto, il tuo barone siede ora in una prigione ben sorvegliata. Forse vorresti dargli un’occhiata, eh-eh?!";
				link.l1 = "Avrò tutto il tempo del mondo per farlo, ah-ah. Lo trattano bene?";
				link.l1.go = "patria_10";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Tieyasal") && pchar.questTemp.Tieyasal == "begin" && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				dialog.text = "Felice di vederti, compare! In che posso esserti utile?";
				link.l1 = "Sono tornato a chiederti aiuto.";
				link.l1.go = "tieyasal";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Guardoftruth.Archy") && pchar.questTemp.Guardoftruth.Archy == "islatesoro")
			{
				dialog.text = "Felice di vederti, compare! Dimmi pure, come posso darti una mano?";
				link.l1 = "Steven, ho qualcosa per te.";
				link.l1.go = "guardoftruth";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Saga.Shadows") && pchar.questTemp.Saga.Shadows == "islatesoro")
			{
				dialog.text = "Felice di vederti, compare! Dimmi pure, come posso darti una mano?";
				link.l1 = "Steven, devo chiederti una cosa. Forse non ti piacerà, ma ho bisogno del tuo aiuto.";
				link.l1.go = "shadows";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "islatesoro")
			{
				dialog.text = "Ah, eccoti qua, "+pchar.name+". Mi aspettavo il tuo arrivo. Il Diavolo della Foresta mi ha parlato dei tuoi guai con Tortuga...";
				link.l1 = "Mi ha anche detto che avevi già trovato una soluzione. È vero?";
				link.l1.go = "terrapin";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Terrapin.Catherina") && pchar.questTemp.Terrapin == "tortuga")
			{
				dialog.text = "Come ce la passiamo, "+pchar.name+"?";
				link.l1 = "Segreti ovunque... Ho bisogno del tuo consiglio, Steven.";
				link.l1.go = "terrapin_8";
				break;
			}
			// belamour legendary edition хвастовство "Фортуной"
			if(CheckShipTypeInSquadron(SHIP_FRIGATE_L) > 0 && !CheckAttribute(pchar,"questTemp.SharkFrigate"))
			{
				link.l2 = "Sì, voglio mostrarti una cosa... Ti va di venire con me al molo?";
				link.l2.go = "check_out_my_frigate";
			}
			
			// belamour legendary edition на пару с Акулой
			if(CheckAttribute(pchar,"questTemp.SharkGoldFleet") && pchar.questTemp.SharkGoldFleet == "toDodson")
			{
				dialog.text = "Ah, mio buon amico "+GetFullName(pchar)+"Avanti, che piacere vederti! Che vento ti porta fin qui?";
				link.l1 = "Ciao, Steven! Eccomi come promesso. La tua nave è pronta?";
				link.l1.go = "SharkGoldFleet";
				break;
			}
			if(CheckAttribute(pchar,"questTemp.SharkGoldFleet") && pchar.questTemp.SharkGoldFleet == "RUinDeal")
			{
				link.l2 = "Allora, come va con i tuoi affari? Non hai ancora mollato quella faccenda della 'Flotta d’Oro'?";
				link.l2.go = "SharkGoldFleet_10";
			}
			dialog.text = "Ah, mio compare "+GetFullName(pchar)+"Entra pure, che piacere vederti! Cos'è che ti porta qui?";
			link.l1 = "Sì, sono passato all’Isola Tesoro per affari, e ho pensato di fermarmi qui un momento.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		// --------------------------------------вариант R-----------------------------------------------
		case "Chad_die":
			dialog.text = "Ah! Immagino tu sia il nostro visitatore notturno, eh? Mi hanno avvisato di questo imprevisto troppo tardi. Ho frugato tra le tue cose e ho trovato una lettera dal Diavolo della Foresta. Dannazione, sembrava ancora impregnato dell’odore delle giungle di Main... Dimmi, il tuo nome è "+GetFullName(pchar)+" Non ti stupire, l’ho letto nella lettera. Mi chiamo Steven Dodson. O semplicemente Squalo. Lo Squalo. Credo che tu abbia già sentito parlare di me. Al momento ricopro la carica di ammiraglio in questa città, o isola, comunque la si voglia chiamare.\nTi chiedo scusa per le azioni dei miei uomini ieri notte. Ho dato io l’ordine di catturare chiunque si intrufolasse nella stiva. Troppi furfanti tra i Narvali e i Rivados.\nChad ti ha lasciato andare, suppongo? Strano. Proprio ora stavo per mandargli l’ordine di liberarti. Dov’è la tua nave? Spero che stia bene?";
			link.l1 = "Chad? Per quel che ho capito, il tuo nostromo non mi avrebbe mai lasciato uscire vivo dalla prigione. Ho fatto tutto da solo, e ho liberato pure un nero di questi... Rivados.";
			link.l1.go = "Chad_die_1";
		break;
		
		case "Chad_die_1":
			dialog.text = "Mi stai raccontando cose davvero intriganti, compare. E come hai fatto a uscire dal 'Tartaro'? Pare proprio che dovrò farmi una bella chiacchierata con Chad e i suoi carcerieri...";
			link.l1 = "Non ci parlerai mai più. Non proferiranno mai più parola, temo. Chad mi ha minacciato di tenermi in gabbia per l’eternità. Mi ha accusato d’essere un Rivados e ha preteso che glielo dimostrassi ammazzando il mago nero Chimiset...";
			link.l1.go = "Chad_die_2";
		break;
		
		case "Chad_die_2":
			dialog.text = "Che diamine?! Che follia sconsiderata! Ci serve Chimiset vivo, e Chad lo sapeva benissimo! E perché mai avrebbe dovuto pensare che tu fossi dei Rivados, se sono tutti neri? Che diavolo sta tramando, maledetto lui?";
			link.l1 = "Sta tramando qualcosa che di certo non ti piacerà, Steven. Chad mi ha dato un machete e mi ha mandato di sotto a far fuori Chimiset. Ma il vecchio Nero mi ha detto una cosa importante, e ho capito che se ammazzo Chimiset, il prossimo sarò io...";
			link.l1.go = "Chad_die_3";
		break;
		
		case "Chad_die_3":
			dialog.text = "";
			link.l1 = "Invece di far fuori il vecchio, ho scassinato uno scrigno di munizioni e ho incrociato le lame con Chad e la sua ciurma. Ora capisci perché non puoi più parlare con loro? Sono tutti crepati.";
			link.l1.go = "Chad_die_4";
		break;
		
		case "Chad_die_4":
			dialog.text = "Maledizione! Le notizie si fanno sempre più spaventose! E che diavolo dovrei fare con tutto questo casino?";
			link.l1 = "Ascoltami, Steve. Chimiset mi ha detto che Chad aveva stretto un accordo con alcuni Narvali – l’altro clan, se ho capito bene. Chad stava pianificando di farti fuori e prendere il tuo posto. I Narvali fremono per vederti stecchito, convinti che tu abbia ucciso il loro capo Allen... o Alan, non ricordo bene.";
			link.l1.go = "Chad_die_5";
		break;
		
		case "Chad_die_5":
			dialog.text = "Stronzate! Non ho ucciso Alan! È stato qualcun altro, forse pure quei Narvali. Secondo me, il loro attuale capo – Donald Greenspen – ha fatto fuori Alan!";
			link.l1 = "No. Chad l'ha ammazzato. Chimiset aveva visto tutto — ecco perché volevano farlo fuori anche lui. Chad però non ha voluto sporcarsi le mani, per qualche motivo... Pare temesse una maledizione, o roba simile. Così ha deciso di affidare il lavoro a me.";
			link.l1.go = "Chad_die_6";
		break;
		
		case "Chad_die_6":
			dialog.text = "Non ci posso credere... Chad ha ucciso Alan? Ma perché?";
			link.l1 = "Per lasciarti tutta la colpa addosso e farti passare per nemico dei Narvali. Suppongo sia stato lui a spargere le voci, altrimenti perché i Narvali dovrebbero prendersela solo con te? Steven, stanno tramando per ammazzarti. E la colpa ricadrebbe sui Rivados – non ho idea di come vogliano metterla in scena, però. Chimiset me l’ha raccontato.";
			link.l1.go = "Chad_die_7";
		break;
		
		case "Chad_die_7":
			dialog.text = "";
			link.l1 = "Inoltre, ho trovato questa lettera nel baule di Chad. Leggila. Pare essere una prova concreta, sebbene indiretta.";
			link.l1.go = "Chad_die_8";
		break;
		
		case "Chad_die_8":
			RemoveItems(pchar, "letter_chad", 1);
			dialog.text = "...(leggendo)... eh! Non mi stupisce affatto il tradimento di Chad. Quel figlio di puttana ha sempre bramato il comando su quest’isola. Ma i Narvali! Davvero pensano che sia stato io a far fuori Alan! Mi costeranno il doppio per il vitto, ora\nTanto avevo già in mente di liberare Chimiset, è ora di far pace con loro. Mi hai proprio spiazzato, compare, a dire il vero...";
			link.l1 = "Capisco, Steven. Nemmeno a me va a genio, mi son ritrovato impantanato in una faccenda politica da quando ho messo piede sull’Isola Giustizia. Ero venuto solo per cercare te e Nathaniel Hawk...";
			link.l1.go = "Chad_die_9";
		break;
		
		// ноды пересечения
		case "Chad_die_9":
			dialog.text = "Cosa? Hawk? Non sta forse in Giamaica? È un barone di Maroon Town, che diavolo ci farebbe qui?";
			link.l1 = "No. Ora comanda Jackman. Ho scoperto che Hawk è arrivato lì come me – passando dal portale di Kukulcan.";
			link.l1.go = "Chad_die_10";
		break;
		
		case "Chad_die_10":
			dialog.text = "Che diavolo sta succedendo? Quale portale? E ancora non hai risposto – dove si trova la tua nave?";
			link.l1 = "Non c’è nessuna nave. Capisco, Steve, che sia dura da credere, ma sono davvero arrivato qui grazie a quell’idolo indiano dalla Terraferma... non mi guardare così – non sono impazzito! Nemmeno io so come sia possibile, eppure è vero!";
			link.l1.go = "Chad_die_11";
		break;
		
		case "Chad_die_11":
			dialog.text = "";
			link.l1 = "Lo sciamano del villaggio Miskito ha visto Nathaniel Hawk, mentre fuggiva dai suoi inseguitori, correre verso l'idolo indigeno, conosciuto come la statua di Kukulcan, e sparire all'improvviso. Questo sciamano mi ha raccontato che anche lui era stato su quest'Isola, e che ci era arrivato nello stesso modo, passando attraverso la statua...";
			link.l1.go = "Chad_die_12";
		break;
		
		case "Chad_die_12":
			dialog.text = "";
			link.l1 = "Cerco Nathan, ecco perché ho dovuto seguire le sue orme. Sono arrivato alla statua a mezzanotte, proprio come mi aveva detto lo sciamano. Non ci crederai, ma quella notte la cima della statua di pietra brillava d’oro, e una luce misteriosa ardeva sopra di essa!";
			link.l1.go = "Chad_die_13";
		break;
		
		case "Chad_die_13":
			dialog.text = "";
			link.l1 = "Non appena ho toccato la statua, un cerchio di luce s'è formato attorno all'idolo, le fiamme sono divampate, e poi sono stato risucchiato dentro la statua. Mi sono ritrovato qui, nella stiva della tua nave, sotto, vicino alla prua, proprio alla breccia...";
			link.l1.go = "Chad_die_14";
		break;
		
		case "Chad_die_14":
			dialog.text = "";
			link.l1 = "Son sopravvissuto a stento, solo grazie allo stregone che mi aveva dato una pozione speciale. Alla fine fui assalito da una creatura - un granchio gigante. Spero che adesso tu voglia darmi un po' di fiducia?";
			link.l1.go = "Chad_die_15";
		break;
		
		case "Chad_die_15":
			dialog.text = "Intendi la parte sul granchio? Su quello ti credo. Ce ne sono a mucchi di quelle bestiacce intorno all’isola. Li attiriamo con un pesce morto, così spesso fanno la guardia alla nostra porta sul retro. Mette una paura del diavolo ai ladri. E per quello che hai detto dell’idolo – non sono ancora fuori di testa... Ma non scarterò la tua storia, qui la gente bisbiglia di certe cose da decine d’anni, e anch’io ho visto stranezze tanto tempo fa sulle navi dei Rivados... lasciamo perdere.";
			link.l1 = "Giuro che è tutta verità.";
			link.l1.go = "Chad_die_16";
		break;
		
		case "Chad_die_16":
			dialog.text = "Bene. Sia così. Dimmi, perché mi stavi cercando, me e Nathan? Nella lettera di Jan, dicevi che volevi farmi diventare il capo della Fratellanza della Costa?";
			link.l1 = "Esatto. Molte cose sono cambiate dopo la tua sparizione e quella di Hawk. Jackman sta provando a prendersi il comando fra i pirati. Ha in testa di diventare il loro capo, e ci riuscirà, se io e Jan non gli mettiamo i bastoni tra le ruote.";
			link.l1.go = "Chad_die_17";
		break;
		
		case "Chad_die_17":
			dialog.text = "";
			link.l1 = "Jackman sta giocando una partita seria e sanguinosa. Son certo che sia stato lui a organizzare l'agguato e la caccia a Nathaniel. E credo anche che abbia ucciso Blaze. Renderti capo dei Fratelli della Costa è l’unico modo per fermarlo.";
			link.l1.go = "Chad_die_18";
		break;
		
		case "Chad_die_18":
			dialog.text = "Ascolta, sarei ben felice, ma prima dobbiamo lasciare quest’isola maledetta. Ne ho abbastanza, credimi. Tanto più che posso lasciare qui Dexter a gestire gli affari mentre sono via. Non pensavo restare così a lungo, ma la mia nave è stata bruciata durante una battaglia coi clan.\nNon attraverserò quei portali neanche morto, non provarci nemmeno: mi serve una nave, punto e basta.";
			link.l1 = "Non posso... Steven, lo sciamano Miskito mi ha detto che su quest’Isola c’è una statua di Kukulcan. Sembra un semplice idolo di pietra. Sai dove potrei trovarla?";
			link.l1.go = "Chad_die_19";
		break;
		
		case "Chad_die_19":
			dialog.text = "Non ne ho idea. Non ho mai visto statue del genere. Chiedi a qualcun altro.";
			link.l1 = "Vedi, se trovo questa statua, potrò lasciare quest’isola senza bisogno d’una nave. Ormai il viaggio non mi fa più paura. E poi tornerei qui da uomo libero, e ti porterei via con me.";
			if (pchar.questTemp.LSC == "entrance" || pchar.questTemp.LSC == "mary") link.l1.go = "entrance_4";
			else link.l1.go = "Chad_die_20";
		break;
		// ноды пересечения
		
		case "Chad_die_20":
			dialog.text = "Capisco, ma non posso aiutarti. E poi, tutta questa storia dell’assassinio mi turba assai. Chad è morto, ma dubito che i Narvali rinunceranno ai loro piani. Non intendo passare i miei giorni aspettando una pallottola nella schiena. Visto che ti servo vivo e ormai sei dentro fino al collo, ti propongo di indagare su questa cospirazione.\nSei nuovo sull’isola, dunque hai un vantaggio. Trova i complici di Chad e portameli, o sbattili all’inferno dove li trovi, poco mi importa. Parla con Chimiset, il vecchio nero sa più di quanto ci abbia già detto.\nStai in guardia con i Narvali, non varcare i loro confini senza la parola d’ordine. Le cambiano ogni settimana.\nQuando la minaccia sarà eliminata, ti darò la rotta e tutte le informazioni che ti servono per lasciare l’isola.\nOra vai, trova i colpevoli. Riporta l’ordine. Farò in modo che ti ripuliscano la galera dopo. E ci serve pure un nuovo carceriere. E a me serve rum, il mal di mare oggi è forte.";
			link.l1 = "Va bene, Steven. Facciamolo allora...";
			link.l1.go = "Chad_die_21";
		break;
		
		case "Chad_die_21":
			DialogExit();
			NextDiag.CurrentNode = "Total_wait";
			pchar.questTemp.LSC.rvd_friend = "true"; //флаг на проход по кораблям ривадос
			pchar.rvd_friend = true; // ривадосы не будут останавливать где просят пароль
			sld = characterFromId("Chimiset");
			sld.dialog.currentnode = "Friend"; //ноду Чимисету
			pchar.quest.LSC_Eddy.win_condition.l1 = "location";
			pchar.quest.LSC_Eddy.win_condition.l1.location = "ProtectorFisher";
			pchar.quest.LSC_Eddy.function = "LSC_EddyTalk"; //на разговор с Эдди
			AddQuestRecord("SharkHunt", "10");
			sld = characterFromId("Facio");
			sld.quest.parol = true;
			for (i=7; i<=12; i++)
			{
				sld = CharacterFromID("RivadosSold_"+i);
				LAi_SetWarriorType(sld);
				LAi_warrior_SetStay(sld, true);
			}
			for (i=4; i<=8; i++)
			{
				sld = CharacterFromID("RivadosProt_"+i);
				LAi_SetWarriorType(sld);
				LAi_warrior_SetStay(sld, true);
			}
			AddSimpleRumourCityTip("Just imagine: someone has killed the admiral's jailer, Chad Kapper. Impossible! No doubt, that was the Rivados wizard's job...", "LostShipsCity", 7, 2, "LSC", "");
			AddSimpleRumourCityTip("I heard that Chad Kapper is dead. There was no official statement; his body was never found, either. Perhaps, the admiral had simply given him a secret mission?", "LostShipsCity", 7, 2, "LSC", "");
			AddSimpleRumourCityTip("I don't see our jailer Chad Kapper. Some people say that he was killed and some disagree. Anyway, no one has seen him dead.", "LostShipsCity", 7, 2, "LSC", "");
			AddSimpleRumourCityTip("They say that the admiral has doubled provision prices for Narwhals! That pirate is truly reckless!", "LostShipsCity", 7, 3, "LSC", "");
		break;
		
			case "Mary_Die":
			dialog.text = "Ebbene, che porti con te, "+pchar.name+"   Qualche novità sui Narvali?";
			link.l1 = "Sì. Sarai lieto di sapere, Steve, che la congiura è stata smascherata e i cospiratori sono marciti al creatore. Ho tutte le prove.";
			link.l1.go = "Mary_Die_1";
		break;
		
		case "Mary_Die_1":
			if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt.TownAttack")) dialog.text = "Così pensavo, quando ho sentito sparare... Racconta, ti ascolto.";
			else dialog.text = "Così, eh? Mi rallegra sul serio sentirlo! Raccontami tutto, son tutto orecchi.";
			link.l1 = "È stato tutto architettato dal tuo nostromo, Chad Kapper. Ha fatto fuori Alan Milrow nelle segrete della 'Tartarus', e metteva in giro voci sulla tua complicità. Credo che i Narvali fossero davvero furibondi, e per la fidanzata di Alan, la Rossa Mary, è stato un colpo davvero duro...";
			link.l1.go = "Mary_Die_2";
		break;
		
		case "Mary_Die_2":
			dialog.text = "";
			link.l1 = "Mary era smaniosa di vendetta e Chad Kapper ne ha approfittato per i propri scopi. Hanno tramato un piano scaltro per attentare alla tua vita. Qui tutti sanno che ogni sera ti fai una passeggiata a poppa della 'San Augustine'.";
			link.l1.go = "Mary_Die_3";
		break;
		
		case "Mary_Die_3":
			dialog.text = "Ehi! Forse è tempo di rivedere le mie abitudini... Vai pure.";
			link.l1 = "Avevano bisogno di un moschetto a lunga gittata e preciso per portare avanti il loro piano, così un certo Adolf Barbier gliene procurò uno. Ma il suo stutzen era finito al banco dei pegni di Giuseppe Fazio, così Mary e Chad gli diedero abbastanza monete per riscattarlo. Adolf lo recuperò...";
			link.l1.go = "Mary_Die_4";
		break;
		
		case "Mary_Die_4":
			dialog.text = "";
			link.l1 = "Hanno assoldato Marcello il Ciclope, un ex cacciatore reale, per farti fuori. Doveva ricevere il fucile e spararti a sangue freddo. Poi Mary avrebbe eliminato lui, usando il suo cadavere e il fucile come prova che i Rivados erano dietro all’attacco. Marcello il Ciclope è un mulatto, sai...";
			link.l1.go = "Mary_Die_5";
		break;
		
		case "Mary_Die_5":
			dialog.text = "Che furfante astuto!";
			link.l1 = "Dopo di ciò, i Narvali e i pirati avrebbero assaltato i Rivados e li avrebbero annientati. Chad sarebbe diventato ammiraglio e Mary la sua amante. Forse, però, le avrebbe tagliato la gola, ché sapeva troppe cose. Molto probabile...";
			if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt.TownAttack")) link.l1.go = "Mary_Die_6a";
			else link.l1.go = "Mary_Die_6";
		break;
		
		case "Mary_Die_6":
			dialog.text = "";
			link.l1 = "Comunque, ormai è finita. Adolf non era abbastanza loquace, così ho dovuto farlo fuori proprio nella sua cabina. Poi ho dovuto occuparmi anche di Mary e Ciclope, venuti a prendere lo stutzen da Adolf. Hanno capito subito chi ero, e mi sono saltati addosso all’istante.";
			link.l1.go = "Mary_Die_7";
		break;
		
		case "Mary_Die_7":
			dialog.text = "Quindi stanno sdraiati dentro la 'Santa Florentina', giusto?";
			link.l1 = "Sì. Tutti e tre.";
			link.l1.go = "Mary_Die_8";
		break;
		
		case "Mary_Die_8":
			dialog.text = "È bene che nessun testimone sia stato coinvolto in questo casino. Penserò io ai corpi. Hai fatto un buon lavoro, "+pchar.name+"Ah! Fossi stato nella mia ciurma, t’avrei fatto mio nostromo senza pensarci due volte.";
			link.l1 = "Grazie per una risposta così calorosa! E, infine, dai un'occhiata a queste lettere. Le ho prese dai corpi del Ciclope e della povera Mary...";
			link.l1.go = "Mary_Die_9";
			AddSimpleRumourCityTip("Have you heard that? Our squabbler and madcap Red Mary has disappeared. I won't be surprised if she is dead...", "LostShipsCity", 10, 1, "LSC", "");
			AddSimpleRumourCityTip("They say that Red Mary has disappeared. Have you heard about it?", "LostShipsCity", 10, 1, "LSC", "");
			AddSimpleRumourCityTip("Mary Casper has vanished. Some people say that she is still inside her cabin but I don't believe it. It's been too long since there last was light in it.", "LostShipsCity", 10, 1, "LSC", "");
			AddSimpleRumourCityTip("They say that Red Mary was murdered. Poor girl! Yes, she had tough character, but everybody loved her. Who could have done such a terrible thing?", "LostShipsCity", 10, 1, "LSC", "");
		break;
		
		case "Mary_Die_6a":
			dialog.text = "";
			link.l1 = "Comunque, ormai è finita. Adolf non era per niente loquace, e ho dovuto fargli la pelle proprio nella sua cabina. Ho dovuto sistemare anche Mary e il Ciclope, che erano venuti a prendere lo stutzen da Adolf. Hanno capito subito chi fossi, e mi sono saltati addosso senza pensarci due volte.";
			link.l1.go = "Mary_Die_7a";
		break;
		
		case "Mary_Die_7a":
			dialog.text = "Peccato che tu abbia scatenato una rissa sull’‘Eva’. Ora i Narvali sanno che sei il colpevole per la morte dei loro uomini, azioni simili non gioveranno alla tua reputazione. Lo stesso vale per la mia. Non andarli a trovare finché non avrai rimediato a questa faccenda.\nIn generale, però, te la sei cavata bene, "+pchar.name+"Ah! Fossi stato nella mia ciurma, ti avrei fatto subito mio nostromo.";
			link.l1 = "Grazie per una risposta così calorosa! E, infine, dai un'occhiata a queste lettere. Le ho prese dai corpi del Ciclope e della povera Mary...";
			link.l1.go = "Mary_Die_9";
			AddSimpleRumourCityTip("Such a massacre you have performed here! Narwhals won't forget about it!", "LostShipsCity", 5, 2, "LSC", "");
			AddSimpleRumourCityTip("I understand killing Cyclops and two Narwhal bandits... But the girl, why have you killed the girl? Poor Mary...", "LostShipsCity", 7, 5, "LSC", "");
		break;
		
		case "Mary_Die_9":
			RemoveItems(pchar, "letter_chad", 1);
			RemoveItems(pchar, "letter_chad_1", 1);
			dialog.text = "Povera Mary? Ti fa pena quella sgualdrina?";
			link.l1 = "Lo sono davvero. Vedi, Chad l’ha ingannata e si è servito di lei. Non ha saputo dominare i suoi sentimenti e il suo temperamento focoso... ed eccola, dove l’ha portata tutto ciò.";
			link.l1.go = "Mary_Die_10";
		break;
		
		case "Mary_Die_10":
			TakeNItems(pchar, "gold_dublon", 500);
			Log_Info("You have received 500 doubloons");
			PlaySound("interface\important_item.wav");
			CloseQuestHeader("SharkHunt");
			bDisableFastReload = false; // belamour legendary edition
			dialog.text = "Ebbene, vai a trovare fratello Giuliano e accendi una candela... Io però non lo farò mai. Va bene, lasciamo perdere. Ti sono riconoscente, "+pchar.name+", per il tuo aiuto. Ora puoi contare sul mio appoggio. Desidero ricompensarti per l’ottimo lavoro. Ecco, prendi cinquecento dobloni.";
			link.l1 = "Bene, grazie!";
			link.l1.go = "LSC_navy";
			AddSimpleRumourCityTip("They say that the admiral respects you, mister...", "LostShipsCity", 15, 2, "LSC", "");
			AddSimpleRumourCityTip("They say that you are the admiral's loyal friend. Is that true?", "LostShipsCity", 15, 2, "LSC", "");
		break;
		
		// ----------------------------------------вариант N---------------------------------------------------
		case "entrance":
			dialog.text = "Cosa vuoi? Non mi pare d’averti mai visto prima...";
			link.l1 = "Certo che no, non ci siamo mai incontrati prima, e sono arrivato qui da poco. Saluti, Steven. Che fortuna sfacciata! Alla fine ti ho trovato, ti cercavo, anche se mai avrei pensato di trovarti proprio qui!";
			link.l1.go = "entrance_1";
		break;
		
		case "entrance_1":
			dialog.text = "Aspetta, amico, stai calmo. Cerchi proprio me? Non mi piace per niente. Perché, diavolo, mi stavi cercando?";
			link.l1 = "Capisco. Proviamoci di nuovo allora. Tieni, prendi questa lettera. È stata scritta da Jan Svenson per te. Suppongo che ogni tuo sospetto svanirà dopo che l’avrai letta.";
			link.l1.go = "entrance_2";
		break;
		
		case "entrance_2":
			RemoveItems(pchar, "letter_svenson", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "(leggendo)... Mh. Questo spiega molte cose. E io che pensavo volessi darmi una nota nera per la morte di Blaze. Sai, di recente sono in tanti a volerlo fare. Hai lasciato la tua nave sull'anello esterno? E come hai fatto a sapere che mi trovavi qui?";
			link.l1 = "Non l'ho fatto. È stato puro colpo di fortuna. E riguardo a Blaze... Io e Jan pensiamo che tu non sia colpevole della sua morte.";
			link.l1.go = "entrance_3";
		break;
		
		case "entrance_3":
			dialog.text = "E hai ragione. Non sono io. Qualcuno cerca di darmi la colpa, è vero. Ma non l’ho ucciso io.";
			link.l1 = "Questo è buono. Curioso, son venuto fin qui cercando Nathaniel Hawk, e invece mi imbatto in te, ahah!";
			link.l1.go = "Chad_die_9";
		break;
		
		case "entrance_4":
			dialog.text = "Capisco, ma non posso aiutarti. Devi parlarne coi vecchi lupi di questa Isola. Vai dal mago Rivados, Chimiset. Quel vecchio moro sa molto più di quanto lascia intendere.";
			link.l1 = "E dove posso trovare questo stregone?";
			if (pchar.questTemp.LSC == "mary") link.l1.go = "mary";
			else link.l1.go = "entrance_5";
		break;
		
		case "entrance_5":
			dialog.text = "Nella mia prigione, sulla 'Tartaro'. Avevo già deciso di liberarlo, è tempo di migliorare i rapporti con i Rivados. Giusto! Vai alla prigione, di' a Chad Kapper, il carceriere, che ho ordinato di rilasciare Chimiset. Spiega al moro perché ti mando io, digli che lo lascerò andare se avrà lingua sciolta. Sono certo che questo lo farà cantare.";
			link.l1 = "Uhm... Sono nuovo da queste parti. Dove si trova la prigione?";
			link.l1.go = "entrance_6";
		break;
		
		case "entrance_6":
			dialog.text = "Tieni bene a mente: lascia la mia dimora, attraversa il ponte, gira a sinistra, passa attraverso la fregata Carolina fino al galeone Gloria e arriverai all'Esmeralda. Cerca l'insegna del negozio ed entra dalle porte sotto di essa. Passa dalla porta nella prua della nave e raggiungerai il Tartaro.\nFa' attenzione all'Esmeralda: è proprietà del clan dei Narvali, anche se altri possono mettervi piede. Non incrociare i loro combattenti e tieniti lontano dai guai.";
			link.l1 = "Chi sono questi Rivados e Narvali?";
			link.l1.go = "entrance_7";
		break;
		
		case "entrance_7":
			dialog.text = "I clan vivono qui da tempi immemori. Sono la discendenza dei primi coloni. I Narvali sono perlopiù inglesi, olandesi e francesi; i Rivados sono tutti negri. Ogni clan ha il suo capo, possiedono diverse navi e non lasciano entrare estranei nei loro territori. \nPer visitarli devi conoscere le parole d’ordine. Le cambiano ogni settimana.";
			link.l1 = "D'accordo. Me ne occuperò io. Mi lasceranno entrare nella prigione?";
			link.l1.go = "entrance_8";
		break;
		
		case "entrance_8":
			dialog.text = "Lo faranno. Ecco la chiave, così Chad saprà che ti mando io. Prendila.";
			link.l1 = "Va bene. Allora parlerò con quel... Chimiset e poi tornerò con le novità.";
			link.l1.go = "entrance_9";
		break;
		
		case "entrance_9":
			DialogExit();
			GiveItem2Character(pchar, "key_capper");
			NextDiag.CurrentNode = "Total_wait";
			sld = characterFromId("Chimiset");
			sld.dialog.currentnode = "prisoner"; //даем ноду Чимисету
			sld.quest.chimiset_die = "true";
			ChangeCharacterAddressGroup(sld, "Tartarusprison", "quest", "prison2"); // в закрытую клетку
			LAi_SetGroundSitTypeNoGroup(sld);
			sld = characterFromId("Capper");
			sld.dialog.currentnode = "prisoner"; //даем ноду Капперу
			LAi_LocationFightDisable(&Locations[FindLocation("Tartarusprison")], true);//запретить драться
			// прерывания на локаторы тартаруса
			pchar.quest.LSC_TartarusEntrance1.win_condition.l1 = "locator";
			pchar.quest.LSC_TartarusEntrance1.win_condition.l1.location = "LostShipsCity_town";
			pchar.quest.LSC_TartarusEntrance1.win_condition.l1.locator_group = "reload";
			pchar.quest.LSC_TartarusEntrance1.win_condition.l1.locator = "reload51";
			pchar.quest.LSC_TartarusEntrance1.win_condition.l2 = "item";
			pchar.quest.LSC_TartarusEntrance1.win_condition.l2.item = "key_capper";
			pchar.quest.LSC_TartarusEntrance1.function = "LSC_TartarusEntrance1_Open";
			pchar.quest.LSC_TartarusEntrance2.win_condition.l1 = "locator";
			pchar.quest.LSC_TartarusEntrance2.win_condition.l1.location = "LostShipsCity_town";
			pchar.quest.LSC_TartarusEntrance2.win_condition.l1.locator_group = "reload";
			pchar.quest.LSC_TartarusEntrance2.win_condition.l1.locator = "reload52";
			pchar.quest.LSC_TartarusEntrance2.win_condition.l2 = "item";
			pchar.quest.LSC_TartarusEntrance2.win_condition.l2.item = "key_capper";
			pchar.quest.LSC_TartarusEntrance2.function = "LSC_TartarusEntrance2_Open";
			AddQuestRecord("SharkHunt", "19");
		break;
		
		case "entrance_10":
			dialog.text = "Allora, sei mai stato sul 'Tartarus'?";
			link.l1 = "Sì. Ho trasmesso i tuoi ordini a Chad e ho parlato col moro.";
			link.l1.go = "entrance_11";
		break;
		
		case "entrance_11":
			dialog.text = "Il mago ti ha sussurrato qualcosa di curioso?";
			link.l1 = "Oh, sì. Mi disse dove trovare l’idolo di teletrasporto di Kukulcan. Era sulla nave ‘San Geronimo’, affondata nei bassi fondali vicino al territorio dei Narvali.";
			link.l1.go = "entrance_12";
		break;
		
		case "entrance_12":
			dialog.text = "Ah-ah-ah, magnifico! Quindi il tuo 'portale' ora sta sul fondo del mare? Beh, compare, temo che tu sia in trappola su quest’isola. Allora, unisciti a me e ai miei uomini...";
			link.l1 = " Troverò il modo di raggiungere l'idolo. Una via la troverò, ora. Chimiset mi ha detto che non dovresti fidarti di Kapper, perché l'ha visto coi suoi occhi ammazzare Alan Milrow, il capo dei Narvali, quello Chad.";
			link.l1.go = "entrance_13";
		break;
		
		case "entrance_13":
			dialog.text = "Cosa?! Chad ha ucciso Alan? Quel mago è completamente fuori di testa! Non può essere vero!";
			link.l1 = "Sai, Steve, Chimiset è davvero spaventato. Non credo proprio che mi abbia mentito.";
			link.l1.go = "entrance_14";
		break;
		
		case "entrance_14":
			dialog.text = "Maledizione, questa sì che è una brutta notizia! L’assassinio di Alan ha già macchiato la mia reputazione tra i Narvali – alcuni pensano che sia stato io a farlo, e ora salta fuori che uno dei miei ufficiali potrebbe averlo davvero commesso!";
			link.l1 = "Sembra che la gente ami scaricare su di te colpe che non ti appartengono...";
			link.l1.go = "entrance_15";
		break;
		
		case "entrance_15":
			dialog.text = "Già, è una faccenda inquietante...";
			link.l1 = "E ora, la 'migliore' notizia per te – il vecchio mi ha confidato d’aver origliato varie chiacchiere e capito che alcuni dei tuoi uomini tramano per ammazzarti. Svelerà i dettagli solo dopo che l’avrai liberato, e solo a quattr’occhi.";
			link.l1.go = "entrance_16";
		break;
		
		case "entrance_16":
			dialog.text = "Magnifico! E tutto questo per colpa tua! Senza offesa, sto solo scherzando. La testa mi gira: Chad ha fatto fuori Alan, i miei uomini tramano per farmi la pelle... Il vecchio moro ti ha raccontato qualcosa in dettaglio?";
			link.l1 = "No. Teme troppo Chad, per quel che ho capito io.";
			link.l1.go = "entrance_17";
		break;
		
		case "entrance_17":
			dialog.text = "Va bene. Dirò a Rivados che voglio incontrare Chimiset. Vedremo cosa mi risponderà. E riguardo al tentativo... d’accordo, starò in guardia. Allora, che farai adesso, "+pchar.name+"?";
			link.l1 = "Niente di particolare, per ora. Farò un giro sull’Isola Giustizia e conoscerò i suoi abitanti – magari mi verrà in mente un modo per filarmela da qui. Prima però devo trovare Nathan Hawk, è per lui che sono sbarcato in queste acque.";
			link.l1.go = "entrance_18";
		break;
		
		case "entrance_18":
			dialog.text = "Capisco. Non scordarti di passare da me quando troverai un modo per lasciare quest’isola: ti darò le rotte per navigare, senza di esse qui non tornerai più. E avrò da raccontarti altre cose importanti.";
			link.l1 = "Va bene. Verrò senz’altro a trovarti, Steve!";
			link.l1.go = "entrance_19";
		break;
		
		case "entrance_19":
			DialogExit();
			NextDiag.CurrentNode = "Total_wait";
			sld = characterFromId("Facio");
			sld.quest.parol = true;
			// прерывание на вызов к Акуле
			pchar.quest.LSC_GotoShark.win_condition.l1 = "Timer";
			pchar.quest.LSC_GotoShark.win_condition.l1.date.hour  = 9.00;
			pchar.quest.LSC_GotoShark.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.LSC_GotoShark.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.LSC_GotoShark.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.LSC_GotoShark.win_condition.l2 = "location";
			pchar.quest.LSC_GotoShark.win_condition.l2.location = "LostShipsCity_town";
			pchar.quest.LSC_GotoShark.function = "LSC_GotoShark";
			AddQuestRecord("SharkHunt", "21");
		break;
		
		case "entrance_20":
			dialog.text = "È bene che tu sia arrivato, "+pchar.name+". Ti stavo aspettando. Cattive notizie. Chimiset è morto, Chad Kapper è sparito senza lasciare traccia.";
			link.l1 = "Maledizione... Sono certo che Chad abbia fatto fuori Chimiset! Il vecchio moro tremava a ragion veduta.";
			link.l1.go = "entrance_21";
		break;
		
		case "entrance_21":
			dialog.text = "Non ne dubito affatto. Dannazione, la situazione peggiora di ora in ora. Avevo quasi stretto un patto solido con Eddie il Nero e adesso questo. Addio amicizia coi Rivados.\nSanno che hai parlato con Chimiset prima che tirasse le cuoia, e ora ti considerano uno dei miei. Quindi tieniti lontano da loro.";
			link.l1 = "Già, che peccato...";
			link.l1.go = "entrance_22";
		break;
		
		case "entrance_22":
			dialog.text = "Ti ho chiamato qui non solo per ascoltare le novità. Ho ricevuto una lettera dal nostro mediatore e diplomatico, Giuseppe Fazio: mi invita a raggiungerlo nella sua cabina in Carolina, a mezzanotte. Dice anche che devo andare da solo, perché la mia vita è in gioco e non ci si può fidare di nessuno.\nHa senso, Chimiset ci ha avvertiti che ho un traditore vicino. Ma puzza di trappola... da solo, a mezzanotte... Di solito quel grassone viene da me in persona. Comunque sia, ho intenzione di chiederti aiuto.\nTecnicamente, tu non sei uno dei miei uomini e sei appena arrivato sull’isola. Jan ti ha descritto come uno sveglio, coraggioso, con una buona mano con la spada. Voglio che tu mi scorti all’incontro, a mezzanotte...";
			link.l1 = "Non c'è bisogno che me lo chieda, Steven. Ci sto. Neanche a me piace quest'invito – puzza di trappola.";
			link.l1.go = "entrance_23";
		break;
		
		case "entrance_23":
			dialog.text = "Forse mi sbaglio e non c’è nessuna trappola, ma meglio stare all’erta. Mi rincuora che tu abbia accettato. Vieni sul ponte della 'San Augustine' a mezzanotte, e andremo a trovare Fazio, la sua vecchia carretta non è lontana da qui.";
			link.l1 = "Affare fatto. Sarò sul ponte della 'San Augustine' a mezzanotte, ben armato.";
			link.l1.go = "entrance_24";
		break;
		
		case "entrance_24":
			DialogExit();
			NextDiag.CurrentNode = "Total_wait";
			pchar.quest.LSC_GotoShark.win_condition.l1 = "Timer";
			SetFunctionTimerCondition("LSC_MeetingSharkAugustine", 0, 0, 1, false); // таймер
			AddQuestRecord("SharkHunt", "22");
		break;
		
		case "caroline":
			dialog.text = "Felice di vederti, "+pchar.name+"Non perdiamo tempo, vediamo cosa ha da raccontarci quel grassone di Fazio. Seguimi!";
			link.l1 = "Andiamo, Steve. Tieni l’arma a portata di mano...";
			link.l1.go = "caroline_1";
		break;
		
		case "caroline_1":
			DialogExit();
			sld = characterFromId("Dodson");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload25", "CarolineBank", "barmen", "bar2", "LSC_CarolineOpen", -1);
		break;
		
		case "caroline_2":
			dialog.text = "E dove diavolo s’è cacciato quel maledetto grassone? Dov’è andato? Siamo suoi ospiti e non ci degna nemmeno d’un saluto. Lo vedi tu, "+pchar.name+"Forse dovremmo frugare nei suoi forzieri, magari s’è rintanato lì dentro...";
			link.l1 = "Non riuscirà mai ad aprire nessun forziere al mondo, comunque. Silenzio! Steven! Sento rumore là fuori...";
			link.l1.go = "caroline_3";
		break;
		
		case "caroline_3":
			dialog.text = "Accidenti! Hai ragione. Pare proprio che siamo nei guai."+pchar.name+".";
			link.l1 = "...";
			link.l1.go = "caroline_4";
		break;
		
		case "caroline_4":
			DialogExit();
			LAi_SetPlayerType(pchar);
			// запускаем Мэри, Чада и нарвалов - будет лютое рубилово
			sld = characterFromId("Capper");
			sld.cirassId = Items_FindItemIdx("cirass1");
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "CarolineBank", "reload", "reload3");
			sld = characterFromId("Mary");
			sld.greeting = "mary_4";
			int iScl = MOD_SKILL_ENEMY_RATE*10 + 2*sti(pchar.rank);
			LAi_SetHP(sld, 250+iScl, 250+iScl); // усилим
			sld.dialog.currentnode = "caroline";
			ChangeCharacterAddressGroup(sld, "CarolineBank", "reload", "reload2");
			LAi_SetActorType(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;
		
		case "caroline_5":
			dialog.text = "Argh! Ce l’abbiamo fatta... A dir la verità, pensavo fossimo già condannati alla fossa.";
			link.l1 = "Ne ho viste di peggiori, credimi. Ma questi maledetti ci hanno dato filo da torcere. Chimiset aveva ragione ad avvertirci: Chad è un traditore. Chi era la ragazza che li guidava?";
			link.l1.go = "caroline_6";
		break;
		
		case "caroline_6":
			dialog.text = "Si chiama Mary Casper, ma tutti la conoscono come Mary la Rossa, la vecchia fiamma del defunto Alan Milrow. Capisco perché Chad sia venuto qui, voleva prendere il mio posto, ma che ci faceva lei su quest’isola maledetta?";
			link.l1 = "È tutto chiaro come il sole. Hai detto che era la sua amante, le sue intenzioni son cristalline – vendetta. Povera ragazza, non sapeva d’esser nella stessa ciurma del boia del suo innamorato.";
			link.l1.go = "caroline_7";
		break;
		
		case "caroline_7":
			dialog.text = "Ha senso. Ebbene, ora pagheranno per tutto! Smetterò di vender loro provviste e viveri – che crepino di fame. I miei uomini sanno resistere a qualsiasi assedio; se i Narvali provano a prendere d’assalto il San Augustine, li abbatteremo come cani.\nSi pentiranno amaramente d’aver tramato contro di me in modo così meschino. Inchioderò il culo grasso di Fazio al muro dietro la mia sedia!";
			link.l1 = "Aspetta, Steve. Non è poi così semplice. Dammi un giorno e cercherò di far luce su questo pasticcio. Son certo che Chad sia l’unico colpevole. Ha fatto fuori Milrow, ha messo in giro la voce che fossi stato tu, ha usato la donna di Alan...";
			link.l1.go = "caroline_8";
		break;
		
		case "caroline_8":
			dialog.text = "Va bene. Indaga pure. Forse non abbiamo ancora scovato tutti i cospiratori. E io andrò a bermi un po’ di rum. E, "+pchar.name+"Ti sono debitore. Puoi contare su di me per qualsiasi cosa. Se fossi stato nella mia ciurma, ti avrei fatto nostromo.";
			link.l1 = "Grazie per una risposta così entusiasta! Lavoreremo insieme comunque, quando diventerai capo dei Fratelli della Costa. Vai a riposarti un po', intanto io darò un'occhiata a questa cabina, magari troverò qualcosa di utile.";
			link.l1.go = "caroline_9";
		break;
		
		case "caroline_9":
			dialog.text = "Bene. Manderò i miei uomini qui a ripulire prima dell’alba – non vogliamo spaventare la gente con dei cadaveri in giro. Beh, stanotte i granchi faranno la festa! Ci si vede!";
			link.l1 = "Ci si rivede...";
			link.l1.go = "caroline_10";
		break;
		
		case "caroline_10":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "SanAugustineResidence", "sit", "sit1", "LSC_SharkReturnSit", 10.0);
			AddQuestRecord("SharkHunt", "24");
		break;
		
		case "narval":
			dialog.text = "Ebbene, "+pchar.name+", suppongo che la tua indagine abbia dato i suoi frutti?";
			link.l1 = "Si può dire così. I Narvali non hanno preso parte al tentato omicidio. Tranne Mary e quei furfanti che ci hanno accolto sulla 'Carolina'. Penso sia stata lei a sobillarli contro di noi. Fazio è stato costretto a inviarti l’invito. Ho trovato la lettera nella sua cabina, che spiega molte cose. Leggila.";
			link.l1.go = "narval_1";
		break;
		
		case "narval_1":
			RemoveItems(pchar, "letter_chad_1", 1);
			dialog.text = "(leggendo)... Mh. Sembra proprio uno della razza di Fazio. Certo, cosa mai poteva fare contro Chad... pensava solo a salvarsi la pellaccia. Pare che la colpa sia tutta del mio nostromo...";
			link.l1 = "Ora lo vedi con i tuoi occhi. Le intenzioni sono limpide, e sappiamo perché Chad ha fatto fuori Chimiset e Alan. Kapper voleva diventare l’ammiraglio dell’isola. Ho incontrato il capo dei Narvali – Donald Greenspen. Ha giurato che né lui né alcuno dei suoi uomini tramavano contro di te.";
			link.l1.go = "narval_2";
		break;
		
		case "narval_2":
			dialog.text = "Ti fidi di lui?";
			link.l1 = "Certo che sì. Donald laverà il tuo nome dalle accuse per la morte di Alan. È pronto a venirti a trovare di persona e portarti le sue scuse ufficiali. Anche tu sei stato incolpato senza motivo, ricordi?";
			link.l1.go = "narval_3";
		break;
		
		case "narval_3":
			dialog.text = "D'accordo, dichiarare guerra sarebbe un tantino esagerato. Non siamo messi così bene da spargere sangue a caso. E poi, pare che siano stati solo pochi furfanti, mica tutto il clan.\nDici che Donald è pronto a chiedere scusa? Benissimo, sfruttiamo la cosa per sistemare i rapporti coi Narvali, tanto i Rivados li abbiamo persi comunque.";
			link.l1 = "Hai ragione, Steven. Ora è proprio il momento adatto.";
			link.l1.go = "narval_4";
		break;
		
		case "narval_4":
			dialog.text = "Bene. Di' a Donald che sono pronto a riceverlo e a fare pace.";
			link.l1 = "Sto arrivando.";
			link.l1.go = "narval_5";
		break;
		
		case "narval_5":
			dialog.text = "Aspetta, "+pchar.name+". Hai fatto un buon lavoro e voglio ricompensarti con monete pregiate. Tieni, prendi questi cinquecento dobloni.";
			link.l1 = "Grazie, compare!";
			link.l1.go = "LSC_navy";
			TakeNItems(pchar, "gold_dublon", 500);
			Log_Info("You have received 500 doubloons");
			PlaySound("interface\important_item.wav");
			AddQuestRecord("SharkHunt", "27");
			pchar.questTemp.Saga.SharkHunt = "find"; //флаг - покушение предотвращено
			sld = characterFromId("Grinspy");
			sld.dialog.currentnode = "shark_16"; // ноду Дональду Гринспи
			SetFunctionTimerCondition("LSC_FacioReturn", 0, 0, 1, false); // вертаем на место Фацио через сутки
			AddSimpleRumourCityTip("They say that admiral respects you, mister...", "LostShipsCity", 15, 2, "LSC", "");
			AddSimpleRumourCityTip("They say that you are the admiral's loyal friend. Is that true?", "LostShipsCity", 15, 2, "LSC", "");
		break;
		
		// ----------------------------------------вариант M----------------------------------------------------
		case "mary":
			dialog.text = "Nella mia prigione 'Tartaro'. Puoi andarci a vederlo. Ti darò la chiave e Chad Kapper non ti metterà bastoni tra le ruote...";
			link.l1 = "Aspetta, Steven. Credo che non dovrei andare ancora da Chad Kapper...";
			link.l1.go = "mary_1";
		break;
		
		case "mary_1":
			dialog.text = "E perché mai non dovresti? Che c’è, non ti sta simpatico?";
			link.l1 = "In verità, sei proprio tu quello che non gli va a genio. Ho brutte notizie per te. Chad Kapper sta tramando un attentato alla tua vita.";
			link.l1.go = "mary_2";
		break;
		
		case "mary_2":
			dialog.text = "Cosa?! Spiegati. Chi l'ha detto?";
			link.l1 = "Lascia che ti racconti tutta la storia. Così sarà meglio.";
			link.l1.go = "mary_3";
		break;
		
		case "mary_3":
			dialog.text = "Ebbene, raccontami allora...";
			link.l1 = "Dopo essermi ritrovato nella stiva allagata, sono uscito attraverso il buco e ho nuotato tra i relitti per trovare un posto sicuro. Alla fine, sono salito su una vecchia flûte e sono entrato nella nave. C’era una rissa tra una ragazza con la giacca rossa e due omaccioni...";
			if (pchar.questTemp.LSC.Mary == "alive") link.l1.go = "mary_4"; // Мэри жива
			else link.l1.go = "mary_15";
		break;
		
		case "mary_4":
			dialog.text = "Ehi, pare che la Rossa Mary abbia finalmente fatto incazzare qualcuno.";
			link.l1 = "L’ho aiutata e abbiamo fatto fuori quei bastardi. Dopo ci siamo fatti una chiacchierata interessante... Dimmi, Steve, chi diavolo sono questi Narvali e Rivados? Lei continuava a ripetere quei nomi, e io ero troppo impacciato per chiederle che significassero davvero.";
			link.l1.go = "mary_5";
		break;
		
		case "mary_5":
			dialog.text = "I gruppi di abitanti locali che vivono qui da molto tempo. Sono i discendenti dei primissimi coloni dell’Isola Giustizia. I Narvali sono perlopiù inglesi, olandesi e francesi, mentre i Rivados sono tutti neri. Questi clan hanno i propri capi, alcune navi ciascuno, e non lasciano forestieri mettere piede nei loro territori. Se vuoi visitare le navi di un clan, dovrai conoscere le loro parole d’ordine. Le cambiano ogni settimana.";
			link.l1 = "Capisco ora. Immagino che Mary sia coi Narvali?";
			link.l1.go = "mary_6";
		break;
		
		case "mary_6":
			dialog.text = "Sì, quella fanciulla così espressiva viene dal loro clan. Allora, che ti ha raccontato?";
			link.l1 = "Chad Kapper ha ucciso Alan Milrow, l’amante di lei, che era stato catturato da te. Dopo, ha sparso voci sul tuo coinvolgimento in questa faccenda. Chad ha ingannato Mary e ha cercato di sfruttare la sua sete di vendetta.";
			link.l1.go = "mary_7";
		break;
		
		case "mary_7":
			dialog.text = "Maledizione! Ha ucciso Alan? Ma perché? Per scaricare la colpa su di me?";
			link.l1 = "Per rendere i Narvali ostili verso di te e guadagnarsi la loro fiducia. L’ultimo scopo di Kapper è eliminarti e prendersi il tuo posto. Mary ha rifiutato di partecipare al suo piano e di diventare la sua amante – per questo ha ordinato ai Narvali di farla fuori.";
			link.l1.go = "mary_8";
		break;
		
		case "mary_8":
			dialog.text = "Te l'ha detto lei?";
			link.l1 = "Sì. E non sembrava proprio che mentisse. Inoltre, mi ha dato una lettera da parte di Chad Kapper. L’ho già letta, quindi anche tu dovresti farlo.";
			link.l1.go = "mary_9";
		break;
		
		case "mary_9":
			RemoveItems(pchar, "letter_chad_1", 1);
			dialog.text = "Hm. Sì, questi sono gli scritti di Chad. Riconosco fin troppo bene la sua calligrafia da contadino (leggendo) Maledizione! Incredibile! Figlio di una baldracca! Traditore! Giuro che lo impiccherò con le sue stesse budella! Layton! Raduna cinque uomini! Anzi, Layton, aspetta, annullato!\nFaremo le cose con astuzia. Avevo già pensato di stringere rapporti migliori coi Rivados, questa è la nostra occasione. Il loro stregone Chimiset è rinchiuso nel Tartaro. Una prigione. Lasceremo che i Rivados liberino da soli il loro uomo e, nel trambusto, faranno fuori il traditore.\nLayton! Vai al Tartaro e togli tutte le nostre guardie dal ponte superiore!"+pchar.name+", anche tu prenderai parte a questa faccenda e sto per affidarti un incarico di grande importanza. Trova il capo dei Rivados, Eddie il Nero, e tratta con lui...";
			link.l1 = "Io? Hmm. Ma non conosco anima viva qui!";
			link.l1.go = "mary_10";
		break;
		
		case "mary_10":
			dialog.text = "So you will get to know some people soon - actually you will get to know the very first man of the entire Rivados clan. You are the most suitable candidate to perform the diplomatic part of my plan. My pirates won't be able to come through Rivados territories easily; also I don't have men with decent oratory skills.";
			link.l1 = "E va bene. Ci sto. Cosa devo fare?";
			link.l1.go = "mary_11";
		break;
		
		case "mary_11":
			GiveItem2Character(pchar, "key_capper");
			Log_Info("You have received 50 doubloons");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "gold_dublon", 50);
			dialog.text = "Prendi questa chiave. Apre ogni porta sul 'Tartaro'. Prendi anche questi cinquanta dobloni. Prima dovresti andare alla 'Carolina', comprare una parola d’ordine per accedere nel territorio dei Rivados. Parla con Fazio, fa da mediatore per noi, la parola costa cinquanta dobloni. Poi dovresti andare dal 'Protettore'.\nÈ la dimora di Eddie il Nero. Digli che Chad Kapper si è messo coi Narvali, non ubbidisce più ai miei ordini e sta per far fuori Chimiset. Dagli la chiave, dì che raduni un buon branco dei suoi e attacchi il 'Tartaro'.\nCosì faremo fuori due piccioni con una fava: i Rivados ci vedranno come loro alleati e Kapper creperà per mano dei Negri. Non posso dire di invidiarlo, quel povero diavolo. Capito?";
			if (pchar.questTemp.LSC.Mary == "alive")// Мэри жива
			{
				link.l1 = "Capisco – ma dove posso trovare 'Protettore' e 'Carolina'?";
				link.l1.go = "mary_12";
			}
			else
			{
				link.l1 = "Ascolta, Steve, spiegami chi sono questi Rivados e Narvali. Ne parli sempre, ma io ancora non capisco chi diavolo siano.";
				link.l1.go = "mary_12_1";
			}
		break;
		
		case "mary_12_1":
			dialog.text = "I Narvali e i Rivados sono le ciurme locali. Stanno qui da tempi immemori, discendenti dei primi che naufragarono su questa dannata isola. I Narvali son perlopiù inglesi, olandesi e francesi, mentre i Rivados son tutti negri. Ogni ciurma ha il suo capo, ognuno possiede qualche vascello e non lasciano piede straniero mettere nelle loro acque.\nPer visitarli, devi conoscere le parole d’ordine. Le cambiano ogni maledetta settimana.";
			link.l1 = "Adesso capisco. Dimmi - dove posso trovare la 'Protector' e la 'Carolina'?";
			link.l1.go = "mary_12";
		break;
		
		case "mary_12":
			dialog.text = "Facile come bere un bicchiere d’acqua. Esci dalla mia dimora, attraversa il ponte e gira a sinistra. Quella sarà Carolina. Trovare il Protector è un po’ più complicato: dopo il ponte, vai a destra e prendi le tavole fino a Santa Florentina. Lì troverai i soldati dei Rivados. Ti chiederanno una parola d’ordine. Dilla forte e chiaro. Poi entra nella Fury e dal ponte di poppa sali a bordo del Protector.";
			link.l1 = "Ebbene, ora capisco. Credo che non sentirò la loro mancanza.";
			link.l1.go = "mary_13";
		break;
		
		case "mary_13":
			dialog.text = "Ebbene, allora. Mettiti all’opera, compare!";
			link.l1 = "Ci vediamo!";
			link.l1.go = "mary_14";
		break;
		
		case "mary_14":
			DialogExit();
			NextDiag.CurrentNode = "dodson_warwait";
			AddQuestRecord("SharkHunt", "32");
			sld = characterFromId("Eddy");
			sld.dialog.currentnode = "capper"; // ноду Эдди
			sld = characterFromId("Facio");
			sld.quest.parol = true;
			pchar.questTemp.LSC = "mary_go"; //меняем флаг
		break;
		
		case "dodson_warwait":
			dialog.text = "Sei ancora qui? Vai subito dai Rivados!";
			link.l1 = "Sto arrivando!";
			link.l1.go = "exit";
			NextDiag.TempNode = "dodson_warwait";
		break;
		
		case "mary_15":
			dialog.text = "Heh, pare che la Rossa Mary abbia finalmente fatto incazzare qualcuno.";
			link.l1 = "Sì. Ha fatto infuriare quel bastardo di Chad Kapper. Mi sono buttato nella mischia, ma, ahimè, non sono riuscito a salvare la ragazza: uno degli assalitori l'ha sventrata con la sciabola.";
			link.l1.go = "mary_16";
		break;
		
		case "mary_16":
			dialog.text = "Mi dispiace per lei, certo, ma è stata tutta colpa sua, senza dubbio. Mary ha sempre cercato rogne. E Chad Kapper? Quello sarebbe il mio nostromo, in effetti.";
			link.l1 = "Il tuo nostromo? Eh-eh... Tieni, guarda questa lettera. L’ho trovata addosso alla ragazza. Ora vedrai chi ha ordinato di farla fuori e perché. Kapper sta tramando un attentato contro di te.";
			link.l1.go = "mary_9";
		break;
		
		// Каппер сбежал
		case "Chad_escape":
			dialog.text = "Dove sei stato per così tanto tempo? Ho sentito dire che i Rivados hanno liberato il loro stregone...";
			link.l1 = "Mi tenevano prigioniero sulla 'Protettore' per garantirsi protezione da un agguato. Hanno liberato Chimiset, sì, ma Chad è riuscito a svignarsela.";
			link.l1.go = "Chad_escape_1";
		break;
		
		case "Chad_escape_1":
			dialog.text = "Maledizione! Mai fidarsi dei neri, dicono... Non sono stati capaci neanche di un compito così semplice! Che vadano all'inferno quei Rivados!";
			link.l1 = "Chad si è nascosto tra i Narvali...";
			link.l1.go = "Chad_escape_2";
		break;
		
		case "Chad_escape_2":
			dialog.text = "Certo che sì! Non è uno sprovveduto, ha capito che i Rivados non sarebbero mai entrati nel Tartaro senza il mio aiuto. Ora si nasconderà e colpirà dalle ombre. Layton! Rafforza i posti di guardia! Tenete gli occhi ben aperti, sempre! Pagherò una fortuna a chi mi porterà la testa di Kapper!";
			link.l1 = "Va bene, Steven. Devo rifletterci su. Forse riuscirò a rintracciare quel furfante di Chad. Ci vediamo.";
			link.l1.go = "Chad_escape_3";
			NextDiag.TempNode = "Total_wait";
		break;
		
		case "Chad_escape_3":
			DialogExit();
			if (pchar.questTemp.LSC.Mary == "alive") 
			{
				pchar.questTemp.Saga.SharkHunt = "mary_whiskey"; // к Мэри
				AddQuestRecord("SharkHunt", "34");
			}
			else
			{ // не уберег Мэри - допетривай сам, куда идти
				pchar.questTemp.Saga.SharkHunt = "trader_whiskey"; // флаг на магазин - поиск виски
			}
			NextDiag.CurrentNode = "Total_wait";
			// добавим немного атмосферы - уберем Акселя до утра
			sld = characterFromId("Axel");
			LAi_SetStayType(sld);
			ChangeCharacterAddressGroup(sld, "EsmeraldaStoreBig", "goto", "goto5");
			sld = GetCharacter(NPC_GenerateCharacter("AxelHelper", "citiz_52", "man", "man", 35, PIRATE, 1, true, "quest"));
			FantomMakeCoolFighter(sld, 35, 100, 100, "blade_21", "pistol4", "bullet", 200);
			sld.dialog.Filename = "Quest\LSC\OtherNPC.c";
			sld.dialog.currentnode = "AxelHelper";
			LAi_SetOwnerType(sld);
			ChangeCharacterAddressGroup(sld, "EsmeraldaStoreBig", "barmen", "stay");
			LAi_group_MoveCharacter(sld, "LSC_NARVAL");
			SetFunctionTimerCondition("LSC_AxelReturnStore", 0, 0, 1, false); // таймер на возврат Акселя
		break;
		
		case "whiskey":
			dialog.text = "Che è successo, "+pchar.name+"? Sembri che il diavolo stesso ti stia alle calcagna.";
			link.l1 = "Ti hanno portato una botte di whiskey?";
			link.l1.go = "whiskey_1";
		break;
		
		case "whiskey_1":
			dialog.text = "Quale barile?";
			link.l1 = "TI HANNO PORTATO UNA BOTTE DI WHISKY?!";
			link.l1.go = "whiskey_2";
		break;
		
		case "whiskey_2":
			dialog.text = "Perché urli così, compare? No, non l'hanno fatto. Cos'hai che non va?";
			link.l1 = "Ringrazio il cielo d’esser arrivato in tempo... Chad Kapper s’è comprato una botte di Bushmills da Axel Yost...";
			link.l1.go = "whiskey_3";
		break;
		
		case "whiskey_3":
			dialog.text = "Bushmills? Questo è il mio preferito! Non ne bevo da secoli!";
			link.l1 = "Sì, sì. E anche Kapper lo sa. Ha pure chiesto al suo compare, Marcello il Ciclope, di comprare dell’arsenico da Sancho Carpentero. Capisci dove voglio arrivare?";
			link.l1.go = "whiskey_4";
		break;
		
		case "whiskey_4":
			dialog.text = "Pensi davvero che voglia avvelenarmi?";
			link.l1 = "Senza dubbio! Ecco perché mi sono affrettato tanto. Se ti portano una botte di whiskey, non toccarla. È avvelenata.";
			link.l1.go = "whiskey_5";
		break;
		
		case "whiskey_5":
			dialog.text = "Ehi, grazie dell’avvertimento! Starò all’erta. Aspetta, dove te ne vai adesso?";
			link.l1 = "Devo trovare Kapper e Cyclops. Ho un'idea di dove possano essere. Ci si vede!";
			link.l1.go = "whiskey_6";
		break;
		
		case "whiskey_6":
			DialogExit();
			pchar.questTemp.LSC.Dodson_warning = "true"; // Акула предупрежден
			LAi_CharacterDisableDialog(npchar);//запрещаем диалог
			AddQuestRecord("SharkHunt", "45");
		break;
		
		case "whiskey_7":
			dialog.text = "Ah! Mi fa piacere vederti, compare! Pare proprio che ti debba la vita.";
			link.l1 = "Hanno portato del whiskey?";
			link.l1.go = "whiskey_8";
		break;
		
		case "whiskey_8":
			dialog.text = "Ce l’hanno! Bushmills, proprio come hai detto tu. Il nostro caro Fazio è stato così gentile... L’ho messo ai ferri per far luce sulla faccenda...";
			link.l1 = "Si è confessato?";
			link.l1.go = "whiskey_9";
		break;
		
		case "whiskey_9":
			dialog.text = "Sì. Dice che Kapper l’ha costretto. Aveva paura e... mi ha portato la botte come dono dai Narvali.";
			link.l1 = "Kapper è morto. L’ho fatto fuori io, insieme ai suoi amici Narvali. Ora resta solo quell’altro bastardo – Cíclope Marcello... Sono certo che quel maiale grasso sa dove si nasconde. Lascia che lo stringa un po’ per la gola!";
			link.l1.go = "whiskey_10";
		break;
		
		case "whiskey_10":
			dialog.text = "Certo. Ma cerca di non ammazzarlo, il nostro povero Fazio è già mezzo morto.";
			link.l1 = " Sarò delicato... molto delicato, maledizione! ";
			link.l1.go = "whiskey_11";
		break;
		
		case "whiskey_11":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);//запрещаем диалог
			chrDisableReloadToLocation = true;//закрыть локацию
			sld = CharacterFromID("Facio");
			LAi_CharacterEnableDialog(sld);
		break;
		
		case "poison":
			pchar.questTemp.LSC.Dodson_poison = "true"; // разговор состоялся
			dialog.text = "Argh... "+pchar.name+", amico, qualcosa in me va davvero storto..";
			link.l1 = "Steven! Hai tracannato il rum? Maledizione, davvero te lo sei scolato?!";
			link.l1.go = "poison_1";
		break;
		
		case "poison_1":
			dialog.text = "Sì... Questo è il miglior whiskey irlandese... Giuseppe Fazio me l'ha portato oggi. Diceva che era un dono dal capo dei Narvali... un segno di tregua... ah, che dolore... Pare proprio che sia la mia fine.";
			link.l1 = "Maledizione! Il whiskey era avvelenato con arsenico! Chad Kapper e Marcello Cyclops sono stati loro a farlo!";
			link.l1.go = "poison_2";
		break;
		
		case "poison_2":
			dialog.text = "Argh... il nostromo mi ha preso, maledizione!";
			if (CheckCharacterItem(pchar, "ultimate_potion"))
			{
				link.l1 = "Non morirai! Mi senti? Non morirai! Presto, prendi questa fiaschetta. Questa è la pozione curativa più potente al mondo, guarisce ogni cosa. Bevila... subito!";
				link.l1.go = "poison_3";
			}
			else
			{
				link.l1 = "Steven!";
				link.l1.go = "dodson_poison";
			}
		break;
		
		case "dodson_poison": // Акула умирает
			DialogExit();
			LAi_SetImmortal(npchar, false);
			LAi_KillCharacter(npchar);
			SetFunctionTimerCondition("LSC_SetDexterAdmiral", 0, 0, 1, false); // через день Декстера в адмиралы
			if (CheckAttribute(pchar, "questTemp.LSC.CapperDie_Aeva"))
			{
				AddQuestRecord("SharkHunt", "41");
				sld = CharacterFromID("Facio");
				sld.dialog.currentnode = "whiskey";
				sld.greeting = "facio_2";
				sld.quest.poisonnode = 1;
			}
			else AddQuestRecord("SharkHunt", "42");
			pchar.questTemp.Saga.DodsonDie = "true"; // атрибут Саге что Акула погиб
		break;
		
		case "poison_3":
			RemoveItems(pchar, "ultimate_potion", 1);
			Log_Info("Comanche potion was used");
			Log_Info("Poison was cured!");
			PlaySound("interface\notebook.wav");
			dialog.text = "Oh... "+pchar.name+", mi ha davvero aiutato. Sto ancora un po’ male, ma il dolore è quasi svanito...";
			link.l1 = "Questa pozione annienta perfino i veleni più micidiali. Bevila tutta! Sì...";
			link.l1.go = "poison_4";
		break;
		
		case "poison_4":
			LAi_SetStayType(npchar);
			dialog.text = "Un miracolo... Ora sto bene. Grazie, amico, non lo dimenticherò mai...";
			if (CheckAttribute(pchar, "questTemp.LSC.CapperDie_Aeva"))
			{
				link.l1 = "Faresti meglio a riposarti adesso. Hai la faccia di uno che ha visto la morte in faccia. Quel bastardo di Kapper non ci darà più fastidio – ci ho pensato io, e pure a qualche Narvalo. Ora resta solo Marcello il Ciclope. Hai detto che è stato Fazio a portarti il whiskey, vero?";
				link.l1.go = "poison_5";
			}
			else
			{
				link.l1 = "Faresti meglio a riposare adesso. Hai l'aspetto di uno che ha già un piede nella fossa. Hai detto che Fazio ti ha portato il whiskey, vero?";
				link.l1.go = "poison_7";
			}
		break;
		
		case "poison_5":
			dialog.text = "Sì. Avrei proprio dovuto notare la sua faccia pallida e le mani tremanti...";
			link.l1 = "Pare che sia stato costretto a farlo. Va bene, andrò a trovare quel maiale grasso e mi farò dire ciò che mi serve. Sono certo che sa quello che cerco. Guarisci presto!";
			link.l1.go = "poison_6";
		break;
		
		case "poison_6":
			DialogExit();
			sld = CharacterFromID("Facio");
			sld.dialog.currentnode = "whiskey";
			sld.greeting = "facio_2";
			sld.quest.poisonnode = 1;
			LAi_CharacterDisableDialog(npchar);//запрещаем диалог
			AddQuestRecord("SharkHunt", "40");
		break;
		
		case "poison_7":
			dialog.text = "Sì. Avrei davvero dovuto notare il suo viso pallido e le mani tremanti...";
			link.l1 = "Pare che sia stato costretto a farlo. Va bene, prima o poi metterò le mani su quel maiale grasso, ma adesso devo occuparmi di Kapper e Ciclope. So dove si nascondono. Stammi bene!";
			link.l1.go = "poison_8";
		break;
		
		case "poison_8":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);//запрещаем диалог
			AddQuestRecord("SharkHunt", "43");
		break;
		
		case "clear":
			dialog.text = "Cosa dici, "+pchar.name+"?  So già che hai avuto a che fare con Kapper sulla 'Eva'. E non hai nemmeno ripulito là, ah-ha! A dire il vero, ti ammiro! Ammazzare Chad e i suoi uomini, che impresa! Sì, Jan ha fatto bene a lodarti.";
			link.l1 = "Non solo ho sistemato quella canaglia di Kapper, ma ho pure sventato un attentato alla tua vita. Stavano per avvelenarti, Steven, ma ho fermato quei maledetti prima che ci riuscissero.";
			link.l1.go = "clear_1";
		break;
		
		case "clear_1":
			dialog.text = "Avvelenarmi? Ma in che modo?";
			link.l1 = "Chad ha comprato una botte di whiskey Bushmills irlandese da Axel...";
			link.l1.go = "clear_2";
		break;
		
		case "clear_2":
			dialog.text = "Bushmills? Questo è il mio preferito! Non lo assaporo da secoli!";
			link.l1 = "Sì-sì. E anche Kapper lo sa, eccome. Ha pure chiesto al suo compare, Marcello il Ciclope, di comprare dell’arsenico da Sancho Carpentero. Poi lui e i suoi compari hanno preso Fazio e sono scesi nella stiva dell’‘Eva’. Voleva avvelenare il rum e costringere Fazio a portartelo come dono dai Narvali.";
			link.l1.go = "clear_3";
		break;
		
		case "clear_3":
			dialog.text = "Ah! Certo, mi sarei scolato una pinta di quel whiskey senza pensarci due volte...";
			if (CheckCharacterItem(pchar, "cask_whisky"))
			{
				link.l1 = "Chad contava proprio su questo. Ma ha fallito – non ha nemmeno fatto in tempo a metterci l’arsenico. Già, e mi sono portato la botte con me. Puoi tenerla, è un regalo.";
				link.l1.go = "clear_4";
			}
			else
			{
				link.l1 = "Chad ci contava, ma ha fallito - non ha nemmeno avuto il tempo di metterci l’arsenico.";
				link.l1.go = "clear_7";
			}
		break;
	
		case "clear_4":
			RemoveItems(pchar, "cask_whisky", 1);
			PlaySound("interface\notebook.wav");
			dialog.text = "Mostrami... "+pchar.name+", questo è un vero Bushmills! Il miglior whiskey d’Irlanda! Argh, sognavo questa roba da anni! Tu, tu... Maledizione! Hai fatto fuori Chad e hai trovato un whiskey così squisito!\nTi darò uno dei miei talismani migliori. Questo è il Martello di Thor, dura in eterno. Il tuo cannoniere lo adorerà!";
			link.l1 = "Grazie! Anche io ne sono davvero lieto.";
			link.l1.go = "clear_5";
		break;
		
		case "clear_5":
			GiveItem2Character(pchar, "talisman3"); 
			PlaySound("interface\notebook.wav");
			Log_Info("You have received a 'Thor's hammer' amulet");
			dialog.text = "Non vedo l’ora di tracannare una pinta di questo magnifico whiskey... "+pchar.name+", stanotte festeggeremo! E tu vieni a trovarmi domani. Nel frattempo, rifletterò sulle tue parole e sulle azioni di Chad...";
			link.l1 = "Va bene, Steven, non ti disturbo più dal... tuo riposo, ah-ah!";
			link.l1.go = "clear_6";
			AddQuestRecord("SharkHunt", "53");
		break;
		
		case "clear_6":
			DialogExit();
			NextDiag.CurrentNode = "Total_wait";
			DeleteAttribute(pchar, "questTemp.LSC.Whiskey_clear");
			if (CheckAttribute(pchar, "questTemp.LSC.CyclopDie"))
			{
				SetFunctionTimerCondition("LSC_WhiskeyStoryFinal_1", 0, 0, 1, false); // адмирал зовет
				DeleteAttribute(pchar, "questTemp.LSC.CyclopDie");
			}
		break;
		
		case "clear_7":
			dialog.text = "Mi hai detto qualcosa di molto importante. Rifletterò sulle tue parole e sulle azioni di Chad... poi ti farò chiamare.";
			link.l1 = "Va bene, Steven. Starò ad aspettarti!";
			link.l1.go = "clear_6";
			AddQuestRecord("SharkHunt", "54");
		break;
		
		case "whyskey_final":
			dialog.text = "Ah, eccoti qui, "+pchar.name+". Ora che siamo tutti qui, possiamo iniziare. Ho convocato te e Layton per discutere la situazione e decidere cosa fare coi Narvali.";
			link.l1 = "Che vuoi dire – che fare coi Narvali?";
			link.l1.go = "whyskey_final_1";
		break;
		
		case "whyskey_final_1":
			dialog.text = "Un attentato alla mia vita è stato ordito da Chad, che aveva il sostegno diretto dei Narvali. Lo riconosco come un atto di palese aggressione. Considerando che abbiamo un'alleanza temporanea con i Rivados, propongo quanto segue:\nStringiamo un patto con i Rivados, prepariamo un'operazione e spazziamo via il clan dei Narvali una volta per tutte. Ne ho abbastanza del loro comportamento brigantesco. Tu, "+pchar.name+", toccherà ancora una volta a te fare da diplomatico\nParla con Eddie il Nero e Chimiset, convincili a unirsi a noi nella battaglia contro il nostro nemico comune. Credo che ti ascolteranno, pensano che tu sia dei loro\nDexter preparerà un piano d’attacco, conosce ogni anfratto dell’Isola Giustizia. Layton, hai già qualche idea?";
			link.l1 = "";
			link.l1.go = "whyskey_final_2";
		break;
		
		case "whyskey_final_2": // перекидываем ноду Декстеру
			DialogExit();
			sld = characterFromId("Dexter");
			sld.greeting = "";
			LAi_SetActorType(sld);
			LAi_ActorSetHuberMode(sld);
			LAi_CharacterEnableDialog(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;
		
		case "whyskey_final_3":
			dialog.text = "Un'idea saggia. Costretti a rifugiarsi sulla San Gabriel, i Narvali forse non si arrenderanno subito ai nostri uomini – ma senza provviste moriranno in fretta, o saranno costretti a tentare un assalto disperato. Che ne dici, "+pchar.name+"?";
			link.l1 = "Che vuoi che dica... Dico che dichiarare guerra ai Narvali è una mossa politica da veri sprovveduti.";
			link.l1.go = "whyskey_final_4";
		break;
		
		case "whyskey_final_4":
			dialog.text = "E tu dici ciò dopo aver fatto fuori tutti gli uomini di Chad? Non scordare che erano tutti Narvali!";
			link.l1 = "Non tutti loro. Uno dei primi di quei bastardi, Marcello il Ciclope, non era un Narvalo. In verità, era fedele ai Rivados e forse stava pensando di unirsi a loro. Dopotutto, è un mulatto. Secondo me i Narvali non c’entrano col tentato omicidio contro di te – solo una manciata di furfanti arruolati da Kapper.";
			link.l1.go = "whyskey_final_5";
		break;
		
		case "whyskey_final_5":
			dialog.text = "E che proponi? Facciamo finta di niente?";
			link.l1 = "Ti consiglio di lasciarmi nel mio ruolo di diplomatico – ma questa volta tratterò io stesso col capo dei Narvali, Donald. Inoltre, lascia che ti esponga la mia opinione su cosa potrebbe accadere se attaccassimo i Narvali.";
			link.l1.go = "whyskey_final_6";
		break;
		
		case "whyskey_final_6":
			dialog.text = "Avanti.";
			link.l1 = "Per quel che vedo, la pace sull’Isola Giustizia resiste solo grazie alla rivalità tra due clan che si equivalgono in forza. I tuoi uomini sono la terza lama, e possono dare il colpo decisivo a uno dei due. Ma sia i Rivados che i Narvali sono ossi duri: chi vincerà, pagherà caro il trionfo, in ogni caso.";
			link.l1.go = "whyskey_final_7";
		break;
		
		case "whyskey_final_7":
			dialog.text = "";
			link.l1 = "Il prezzo per annientare i Narvali sarà pagato con molte vite dei tuoi uomini e di quelli dei Rivados. Inoltre, Layton ha detto che l’assedio di San Gabriel durerà a lungo, e potremmo anche trovarci di fronte all’aggressione dei Rivados se perdiamo troppi uomini...";
			link.l1.go = "whyskey_final_8";
		break;
		
		case "whyskey_final_8":
			dialog.text = "";
			link.l1 = "Non scordare che tutte e due le fazioni bramano il dominio sull’Isola Giustizia, e fino a poco fa ti erano nemiche. A parer mio, un massacro sarebbe una vera sciagura per la povera gente comune.";
			link.l1.go = "whyskey_final_9";
		break;
		
		case "whyskey_final_9":
			dialog.text = "Hm. Le tue parole suonano sagge, ma non mi hai ancora convinto.";
			link.l1 = "Anch’io devo lasciare l’Isola in qualche modo, quindi devo raggiungere la statua di Kukulcan in fondo al mare. I Rivados non possono aiutarmi – forse i Narvali sì? Combatterli non mi servirà comunque a nulla.";
			link.l1.go = "whyskey_final_10";
		break;
		
		case "whyskey_final_10":
			if (pchar.questTemp.LSC.Mary != "die") sTemp = "Ha! And I guess that there is one more reason why you don't want to make Narwhals our enemies. That red-haired girl of Ceres Smithy, right, friend? Am I right? Don't worry about her, "+pchar.name+", since you care about her this much - we will take her in the safe place before fighting starts.\n";
			else sTemp = "";
			dialog.text = ""+sTemp+" Ma sia pure, se tanta è la tua risolutezza. Va’ a parlare con Donald Greenspen, il capo dei Narvali. La sua dimora sta sul retro dell’Esmeralda. Vediamo un po’ che storie tirerà fuori quel furfante.";
			link.l1 = "Bene. Sono in cammino.";
			link.l1.go = "whyskey_final_11";
		break;
		
		case "whyskey_final_11":
			DialogExit();
			sld = characterFromId("Grinspy");
			sld.dialog.currentnode = "negotiations"; // ноду Гринспи
			sld = characterFromId("Dexter");
			LAi_SetHuberType(sld);
			LAi_SetHuberType(npchar);
			NextDiag.CurrentNode = "negotiations_wait";
			pchar.questTemp.LSC.Donald_enter = "true";
			AddQuestRecord("SharkHunt", "55");
		break;
		
		case "negotiations_wait":
			dialog.text = "Va' da Donald, compare, e fagli lucidare gli stivali, ah-ah! Io ti aspetto qui.";
			link.l1 = "Sto arrivando.";
			link.l1.go = "exit";
			NextDiag.TempNode = "negotiations_wait";
		break;
		
		case "peace":
			dialog.text = "Allora, hai parlato con Donald? Vediamo che sì...";
			link.l1 = "Sì. Non ha ordinato ai suoi uomini di farti del male. Tutti i Narvali che hanno partecipato al tentato agguato sono stati reclutati da Chad Kapper. È molto contrariato e ci assicura che i Narvali non hanno intenzioni ostili nei tuoi confronti. È pronto a portarti le sue scuse personali per questo attentato alla tua vita e per averti sospettato dell’omicidio di Alan.";
			link.l1.go = "peace_1";
		break;
		
		case "peace_1":
			dialog.text = "È pronto a venire qui e sputare tutte queste parole?";
			link.l1 = "Ha giurato sulla Bibbia.";
			link.l1.go = "peace_2";
		break;
		
		case "peace_2":
			dialog.text = "Eheheh, forse andrà bene così. Pare che l’unico mascalzone da incolpare sia il mio ex nostromo.";
			link.l1 = "Ne sono assolutamente certo, Steven. Non abbiamo bisogno di questa guerra. Nessuno la desidera.";
			link.l1.go = "peace_3";
		break;
		
		case "peace_3":
			dialog.text = "Bene! D'accordo. Sono pronto ad accogliere Donald con le sue scuse, ma che si sbrighi, per mille tempeste. Vai a dirglielo tu.";
			link.l1 = "Subito, Steven.";
			link.l1.go = "peace_4";
		break;
		
		case "peace_4":
			if (pchar.questTemp.LSC.Mary == "alive") sTemp = "Take your Mary there and live your lives together, there is plenty of free space.";
			else sTemp = "";
			dialog.text = "Aspetta! "+pchar.name+", Sono davvero lieto che tu sia approdato qui, sull’Isola. Jan ti tiene in grande considerazione, ma tu hai superato ogni aspettativa. Se fossi stato tra la mia ciurma... anzi, ti offro il posto di Kapper, finché resterai qui. Comanderai la mia guarnigione sulla ‘Tartaro’. "+sTemp+".";
			if (pchar.questTemp.LSC.Mary == "alive") link.l1 = "No, Steven, grazie tante, ma non ho intenzione di restare qui a lungo. Trova qualcun altro per questo. E per quanto riguarda Mary – andiamo bene sulla 'Fucina di Cerere'.";
			else link.l1 = "No, Steven, grazie di cuore, ma non resterò qui a lungo. Trova qualcun altro per questo.";
			link.l1.go = "peace_5";
		break;
		
		case "peace_5":
			TakeNItems(pchar, "gold_dublon", 500);
			Log_Info("You have received 500 doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "Come vuoi, amico. Così sia. Ti prego, accetta questo dono da parte mia. Credo che queste cinquecento dobloni ti torneranno utili.";
			link.l1 = "Grazie!";
			link.l1.go = "LSC_navy";
			AddQuestRecord("SharkHunt", "57");
			pchar.questTemp.Saga.SharkHunt = "find"; //флаг - покушение предотвращено
			sld = characterFromId("Grinspy");
			sld.dialog.currentnode = "negotiations_17"; // ноду Дональду Гринспи
			AddSimpleRumourCityTip("They say that admiral respects you, mister...", "LostShipsCity", 15, 2, "LSC", "");
			AddSimpleRumourCityTip("They say that you are the admiral's loyal friend. Is that true?", "LostShipsCity", 15, 2, "LSC", "");
		break;
		
		case "LSC_navy":
			dialog.text = "Parliamo dei nostri affari... Prendi queste istruzioni di navigazione. Usale per tornare qui in barca e intero.\nSenza di esse, non riuscirai a trovare il passaggio fra scogli e tempeste che circondano l’Isola Giustizia, e la tua nave finirà come tutte le altre relitte qui. Ricorda che devi usare un vascello piuttosto piccolo per superare i banchi: un lugger, una goletta, una brigantina o una brig... Quarta classe, niente di più grande.\nIl tuo scopo è lasciare questo posto con queste istruzioni in tasca e poi tornare a prendermi via mare. Quando sarò di nuovo a bordo, mi unirò a te e a Svenson nei vostri giochi. Non so proprio come tu possa lasciare l’isola, però. Solo tu puoi cavartela in questa faccenda, e forse quel tuo Kukulcan...";
			link.l1 = "Buffo, ma in verità conto proprio sul suo aiuto. Grazie per le dritte sulla navigazione, Steven. Troverò ancora la via per lasciare quest’isola.";
			link.l1.go = "LSC_navy_1";
		break;
		
		case "LSC_navy_1":
			GiveItem2Character(pchar, "LSC_navigation_map");
			dialog.text = "Ti auguro buona fortuna, allora. Sbrigati, se puoi, le mie scorte si stanno svuotando in fretta, e presto non resterà più nulla da mangiare. Sai bene di cosa sono capaci uomini affamati e armati, vero?";
			link.l1 = "Sì, ora devo andare. A presto!";
			link.l1.go = "exit";
			NextDiag.TempNode = "Dodson_wait";
			AddQuestRecord("LSC", "5");
			// убираем квестовые предметы
			sld = ItemsFromID("key_capper");
			sld.price = 10;
			if (CheckCharacterItem(pchar, "letter_chad")) RemoveItems(pchar, "letter_chad", 1);
		break;
		
		case "Dodson_wait":
			dialog.text = "Hai scoperto la via per lasciare l’isola, "+pchar.name+"?";
			link.l1 = "Non ancora, Steven. Ci sto ancora lavorando.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Dodson_wait";
		break;
		
		// --> информационный блок
		case "Total_wait":
			dialog.text = "Ebbene, che porti con te, "+pchar.name+"Hai sentito qualche novità interessante?";
			
			if (!CheckAttribute(npchar, "quest.items") && CheckAttribute(npchar, "quest.takeitems"))
			{
				link.l1 = "Steven, vorrei chiederti di restituirmi i miei averi sequestrati.";
				link.l1.go = "Items";
			}
			if (!CheckAttribute(npchar, "quest.story"))
			{
				link.l2 = "Steven, raccontami di più di quest'isola.";
				link.l2.go = "Story_island";
			}
			if (!CheckAttribute(npchar, "quest.natan"))
			{
				link.l3 = "Sei sicuro che Hawk non sia sull’isola? È passato dal portale, dunque dev’esserci per forza.";
				link.l3.go = "Natan";
			}
			if (!CheckAttribute(npchar, "quest.whiteboy"))
			{
				link.l4 = "Conosci un uomo chiamato Ragazzo Bianco?";
				link.l4.go = "Whiteboy";
			}
			if (!CheckAttribute(npchar, "quest.ships"))
			{
				link.l5 = "Quali territori qui appartengono ai Narvali e ai Rivados?";
				link.l5.go = "ships";
			}
			if (!CheckAttribute(npchar, "quest.parol"))
			{
				link.l6 = "Come posso scoprire le parole d’ordine per salire a bordo delle navi dei clan?";
				link.l6.go = "parol";
			}
			if (!CheckAttribute(npchar, "quest.map"))
			{
				link.l7 = "Ascolta, esiste forse una mappa dell’Isola?";
				link.l7.go = "map";
			}
			if (!CheckAttribute(npchar, "quest.blade"))
			{
				link.l8 = "Hai una spada così singolare. Non ne ho mai vista una simile prima d’ora...";
				link.l8.go = "blade";
			}
			link.l9 = "Nessuna domanda per ora. Ma forse ne avrò presto...";
			link.l9.go = "exit";
			NextDiag.TempNode = "Total_wait";
		break;
		
		case "Items":
			dialog.text = "Ah, sì, certo! Me ne ero proprio dimenticato... Le tue cose stanno di sopra, nel baule. Puoi prenderle. Layton non ti fermerà.";
			link.l1 = "Grazie!";
			link.l1.go = "exit";
			npchar.quest.items = "true";
			NextDiag.TempNode = "Total_wait";
			ref location = &Locations[FindLocation(pchar.location)];
			DeleteAttribute(location, "private1.key");
			for (i=1; i<=10; i++) // можно лезть в сундук
			{
				sld = characterFromId("SharkSoldInside_"+i);
				DeleteAttribute(sld, "watchBoxes");
			}
		break;
		
		case "Story_island":
			dialog.text = "Quest'Isola dev'essere assai antica. Ho visto vecchie caravelle nell'anello esterno, hanno più di cent'anni. Esiste grazie a bassifondi estesi e una corrente poderosa che trascina qui i relitti. Da molto si vive su questa Isola. C'è chi c'è nato e mai l'ha lasciata. \nI clan vennero fuori subito dopo che la spedizione di de Betancourt finì qui. A proposito, la San Augustine e la Tartarus facevano parte di quella spedizione. La Tartarus portava nelle stive un gran numero di schiavi neri. Furono loro a fondare il clan dei Rivados, in onore di Pedro Rivados, il loro capo. Quell'uomo scatenò una rivolta e tentò di prendere la Tartarus, ma fallirono. Lo condannarono a una morte lenta.\nGli schiavi qui ottennero la libertà e subito si opposero al resto dei locali. Le loro pretese di dominio e le tradizioni africane spinsero la maggior parte dei cristiani a unirsi, formando il clan dei Narvali.\nIl clan Narvalo aveva tra le sue fila mercenari, soldati, ufficiali e avventurieri, raccoglievano provviste e mettevano su un piccolo esercito di professionisti, pronti a combattere i Rivados contando sul vantaggio del numero. Da allora i Narvali sono diventati molto selettivi nell'accogliere nuovi membri, e i Rivados hanno ridotto le loro ambizioni. Ora puoi vedere coi tuoi occhi dove ci ha portato tutto ciò.";
			link.l1 = "C’erano dei legami fra l’Isola e il mondo di fuori?";
			link.l1.go = "Story_island_1";
		break;
		
		case "Story_island_1":
			dialog.text = "Non ci sono stati contatti negli ultimi dieci anni. Un tempo la gente del posto commerciava con Cuba, scambiando oro e beni preziosi per un po’ di viveri. Ma ora non lo fanno più.";
			link.l1 = "Hm. Pare dunque che tanto Svenson quanto il Pastore Nero avessero ragione... E perché non hanno lasciato l’Isola, quando ancora ne avevano la ventura?";
			link.l1.go = "Story_island_2";
		break;
		
		case "Story_island_2":
			dialog.text = "Qualcuno ci ha provato, ma la maggior parte ha scelto di restare. Molti hanno trovato casa qui, altri sono nati sull’isola. Non vogliono tornare indietro. Questo posto, per loro, è assai più accogliente... E poi, c’è chi ha troppa paura di sfidare la zona delle tempeste con vecchie carrette. Quanto ai Rivados – non hanno altra scelta che restare qui.";
			link.l1 = "E perché sei venuto qui? Hai lasciato la tua splendida fregata per scegliere una briggantina...";
			link.l1.go = "Story_island_3";
		break;
		
		case "Story_island_3":
			dialog.text = "Mi hanno incolpato dell’omicidio di Blaze Sharp. Non ho la minima idea del perché. Qualcuno di certo gioca sporco. I miei nemici sono aumentati in fretta, così ho dovuto lasciare Isla Tesoro e rifugiarmi qui. Conoscevo l’Isola Giustizia da molto tempo. Ho dovuto abbandonare la mia fregata, troppo grossa per passare tra gli scogli locali.\nAppena arrivato, i Narvali e i Rivados mi sono piombati addosso. Non hanno gradito la mia presenza. Nel cuore della notte si sono avvicinati su scialuppe e hanno dato fuoco alla mia nave. Abbiamo fatto a pezzi le loro bagnarole con cannoni e moschetti. Ma il fuoco ha fatto il suo: il mio brigantino è andato in cenere.\nAccecati dalla rabbia, siamo sbarcati sull’Isola, abbiamo preso d’assalto San Agostino e gli abbiamo insegnato come combattono i corsari. Non hanno retto la pressione e ben presto hanno dato le spalle come codardi. Abbiamo catturato San Agostino, e scoperto che quei babbei la usavano come magazzino viveri. Ora devono comprarli da me... al prezzo che dico io.\nAbbiamo preso anche i loro capi: il capo dei Narvali, Alan Milrow, e la guida spirituale dei Rivados, Chimiset. Layton ha passato i giorni seguenti a esplorare la zona, poi abbiamo attaccato Tartaro – il loro tallone d’Achille.\nOra controlliamo due di queste navi e i clan dovranno abituarsi alla nostra presenza. Al momento, c’è una specie di pace qui. Quanto agli altri abitanti, pare che l’idea di una terza forza non gli dispiaccia.";
			link.l1 = "Ora capisco. Grazie per avermi raccontato la storia!";
			link.l1.go = "exit";
			npchar.quest.story = "true";
			NextDiag.TempNode = "Total_wait";
		break;
		
		case "Natan":
			dialog.text = "Non posso dirlo con certezza, ma qui non l’ho visto di sicuro. Né per strada, né alla taverna, né sulle navi del clan. Sei il primo a dirmi che Hawk dovrebbe aggirarsi da queste parti. Ma come ti ho già detto – ne dubito assai.";
			link.l1 = "Capisco...";
			link.l1.go = "exit";
			npchar.quest.natan = "true";
			NextDiag.TempNode = "Total_wait";
		break;
		
		case "Whiteboy":
			dialog.text = "Ragazzo bianco? Mh... No, non ne ho mai sentito parlare prima. Ma non vuol dire che non sia qui. Non ho certo bisogno di conoscere tutta la feccia locale, sei d’accordo?";
			link.l1 = "Lo so. Va bene, chiederò a qualcun altro.";
			link.l1.go = "exit";
			npchar.quest.whiteboy = "true";
			NextDiag.TempNode = "Total_wait";
		break;
		
		case "ships":
			dialog.text = "L'Isola è spartita tra i Narvali, i Rivados e la mia ciurma. C'è pure una zona neutrale. Io tengo San Augustine e il Tartaro\nI Rivados occupano il Protettore, che è la loro dimora, la Furia - la caserma, Velasco - il magazzino. Gli stranieri non passano, serve una parola d'ordine per entrare lì\nI Narvali hanno una flotta di navi sotto mano. L'Esmeralda è la residenza del loro capo e una bottega. Poi c'è il cosiddetto 'Centro delle Scienze San Gabriel' e la piattaforma Fenice. E infine la Fucina di Cerere - la loro officina. Ogni nave, tranne l'Esmeralda, è vietata agli estranei: se non dai la parola giusta, resti fuori\nLe altre navi sono considerate neutrali, lì dentro vivono i paesani. La taverna di Sancho si trova sulla caravella Fleron e frate Giuliano regge la chiesa locale nel galeone Gloria.";
			link.l1 = "Grazie per l’informazione!";
			link.l1.go = "exit";
			npchar.quest.ships = "true";
			NextDiag.TempNode = "Total_wait";
			AddQuestRecord("LSC", "2");
		break;
		
		case "parol":
			dialog.text = "In realtà, danno le parole solo a chi gli va a genio. Ahimè, tu non sei uno di quelli. Ma non fa gran differenza. Vai a una vecchia fregata che chiamano Carolinea. Lì vive quel cane grasso e furbo di Giuseppe Fazio. È una specie di diplomatico, qui. Non so che mestiere facesse prima di restare incagliato, ma ha del talento.\nFa affari con tutti. I clan lo usano come uomo di mezzo. Avido come un avvoltoio. Si mangerebbe pure le ossa per un doblone, ma non lo dà mai a vedere. Chiedigli la parola d’ordine di adesso, ma sappi che dovrai pagare.";
			link.l1 = "Grazie! Me lo terrò a mente.";
			link.l1.go = "exit";
			npchar.quest.parol = "true";
			NextDiag.TempNode = "Total_wait";
			AddQuestRecord("LSC", "3");
		break;
		
		case "map":
			dialog.text = "Dexter ne possiede una. È il mio secondo al comando. Ha disegnato una mappa dettagliata appena siamo approdati qui. Sali di sopra e parlaci, se ti serve.";
			link.l1 = "Capito. Grazie!";
			link.l1.go = "exit";
			npchar.quest.map = "true";
			NextDiag.TempNode = "Total_wait";
			sld = characterFromId("Dexter");
			sld.quest.map = "true";
		break;
		
		case "blade":
			dialog.text = "Ah! Una spada larga d’alto pregio. Una lama particolare, unica... Un trofeo preso da Alan Milrow, il capoclan dei Narvali. Così l’ho chiamata. Jurgen, il mastro armaiolo narvalo, l’ha forgiata con un metallo straordinario che pescarono sul fondo del mare.   Non arrugginisce, non perde mai il filo e taglia tutto e tutti in un colpo solo. Questa lama mi dà molta soddisfazione, e non intendo certo separarmene.";
			link.l1 = "Mi domando, Jurgen sarebbe capace di forgiare un'altra spada così? Pagando bene, s'intende...";
			link.l1.go = "blade_1";
		break;
		
		case "blade_1":
			dialog.text = "Beh, potrebbe farne un’altra, su questo non c’è dubbio. Ma non lo farà. Jurgen è un Narvalo, fedele al suo clan e non alzerà mai un dito per un forestiero. E poi, ti servirebbe un ferro molto particolare per forgiare una seconda spada. Questo ferro si trova solo sul fondo – e chi diavolo ci arriva, laggiù? Quindi lascia perdere.";
			link.l1 = "Capisco. Che peccato.";
			link.l1.go = "exit";
			npchar.quest.blade = "true";
			NextDiag.TempNode = "Total_wait";
			if (CheckAttribute(pchar, "questTemp.LSC.Mary") && pchar.questTemp.LSC.Mary == "alive")
			{
				sld = characterFromId("Schmidt");
				sld.quest.narval_blade = "begin"; // возможность сделать 'Нарвал' для Мэри
			}
		break;
		// <-- информационный блок
		
		case "return":
			chrDisableReloadToLocation = true;//закрыть локацию
			dialog.text = "Ah, ho visto le tue vele all’orizzonte, "+pchar.name+"Felice di vederti, compare! Com’è andato il viaggio?";
			link.l1 = "Andava bene.";
			link.l1.go = "return_1";
		break;
		
		case "return_1":
			dialog.text = "Bene. Allora, sono pronto a salire sulla tua nave e salpare verso Jan Svenson. Layton resterà qui come ammiraglio, ha già preso possesso della poltrona, ah-ah! Pare proprio che non abbia intenzione di lasciare l’Isola Giustizia, gli piace questo posto.";
			link.l1 = "Hai detto una volta che se la sta cavando davvero bene.";
			link.l1.go = "return_2";
		break;
		
		case "return_2":
			dialog.text = "Sì, di certo lo è. Bene, sono pronto. Andiamo?";
			link.l1 = "Sali sulla mia nave, Steven. Salperemo appena avrò sbrigato le mie faccende qui.";
			link.l1.go = "return_3";
		break;
		
		case "return_3":
			dialog.text = "Affare fatto! Eh, era troppo che non sentivo il ponte d’una nave decente sotto i miei piedi!";
			link.l1 = "...";
			link.l1.go = "return_4";
		break;
		
		case "return_4":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "LSC_SetDodsonPassenger", -1);
		break;
		
		case "return_5":
			dialog.text = "Eccoci qua, amico. Bene, io vado a trovare Svenson. Anche tu dovresti parlarci e discutere dei nostri piani futuri. Ah-ah! Ci attendono giorni infuocati, eh?";
			link.l1 = "Senza dubbio. Ci vediamo, Steven!";
			link.l1.go = "return_6";
		break;
		
		case "return_6":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "houseS1", "none", "", "", "OpenTheDoors", -1);
			sld = ItemsFromID("LSC_navigation_map");
			sld.price = 1000; // лоцию можно выкладывать 270912
			sld = ItemsFromID("keys_skel");
			sld.price = 3000; // отмычки можно выкладывать 270912 
			pchar.questTemp.LSC.Dios = "true"; // можно отдать лоцию Диосу
			CloseQuestHeader("LSC"); // 280313
		break;
		
		// Тени прошлого
		case "shadows":
			dialog.text = "Certo, farò quel che posso! Su, parla.";
			link.l1 = "Steve, guarda un po'... Un dente di squalo. Non dirmi che ti è sconosciuto!";
			link.l1.go = "shadows_1";
		break;
		
		case "shadows_1":
			RemoveItems(pchar, "shark_teeth", 1);
			dialog.text = "Ah! Sei furbo! Sì, è il mio dente. Beh, è il dente di uno squalo che ho abbattuto per far colpo su una bella signora. Da quel giorno mi chiamano Squalo. Pochi riescono a farlo sott'acqua con una semplice sciabola, ma all'epoca ero giovane e sventato, e Beatrice Sharp era la più bella di tutte le Antille... Come sei riuscito ad averlo?";
			link.l1 = "Me l’ha dato il vecchio boia di St. John. Con questa lama, un uomo venne fatto a pezzi. Si chiamava... Joshua Leadbeater.";
			link.l1.go = "shadows_2";
		break;
		
		case "shadows_2":
			dialog.text = "Sì, l’ho fatto. Gli ho tagliato la gola con questo dente. Ero sconvolto dalla morte di Beatrice e credevo che Leadbeater fosse l’unico colpevole ancora in vita. Ho letto i fogli che ho trovato addosso a lui dopo. Beh, aveva tutte le ragioni per vendicarsi.\nLa sorella di Blaze si trovava solo nel posto sbagliato al momento sbagliato. Non si può dare la colpa a Mask per la sua morte, non la voleva, lui cercava solo il Macellaio. Rimpiango di averlo ucciso. La verità è che quella strega di Jessica ha orchestrato tutto.";
			link.l1 = "Hai messo in salvo quei documenti?";
			link.l1.go = "shadows_3";
		break;
		
		case "shadows_3":
			dialog.text = "Perché mai dovrei? Ovviamente no, non ne avevo bisogno. Ma posso raccontarti perché Maschera inseguiva il Macellaio, se hai tempo.";
			link.l1 = "Lo so. Sappi che non è solo curiosità la mia, sono davvero interessato. Son persino pronto a mettere la tua storia nero su bianco.";
			link.l1.go = "shadows_4";
		break;
		
		case "shadows_4":
			dialog.text = "Lo so, non perdi mai tempo. Ascolta allora. Joshua Leadbeater era un semplice capitano della Marina Britannica e comandava la fregata 'Neptune', che poi è diventata leggenda...";
			link.l1 = "...";
			link.l1.go = "shadows_5";
		break;
		
		case "shadows_5":
			DialogExit();
			SetLaunchFrameFormParam("One hour later...", "Saga_FinalLedbitterStory", 0, 4);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 10); //крутим время
			RecalculateJumpTable();
		break;
		
		case "shadows_6":
			AddQuestRecordInfo("Mask", "1");
			dialog.text = "... Tuttavia Leadbeater sopravvisse e fu salvato da una nave di passaggio. Le sue ferite gli sfigurarono il volto, e da allora indossa una maschera. Trovare e punire il responsabile di tutte le sue disgrazie divenne lo scopo della sua vita.";
			link.l1 = "Capisco... L’ho annotato. Credo che dovrei leggerlo per ricordare cosa ho raccolto. È una storia assai mesta. Hai visto quella Jessica?";
			link.l1.go = "shadows_7";
		break;
		
		case "shadows_7":
			dialog.text = "Certo! Lei accompagnò il Macellaio in tutti i suoi viaggi, finché lui non la scaricò per Beatrice. Jess non gliel'ha mai perdonata. La chiamavano il talismano del Macellaio, perché la sorte gli arrideva finché lei gli stava accanto.   Che tu ci creda o no, appena se ne liberò a Barbados, gli affari andarono a rotoli, i bottini si fecero miseri e il 'Neptune' divenne ospite fisso nei cantieri di Isla Tesoro. Anche se, a dirla tutta, il Macellaio passava più tempo in cabina con Beatrice che sulla tolda di comando.   Beatrice era diversa da Jessica, non aveva il sangue caldo per l’avventura e la guerra, anche se Nicolas le insegnò a tirare di spada e a governare la nave. Sì, sognava la vita di mare, ma non aveva il cuore temprato. Il 'Neptune' del Macellaio non era il suo posto. Alla fine, lei l’ha uccisa.";
			link.l1 = "E che mi dici di Jessica?";
			link.l1.go = "shadows_8";
		break;
		
		case "shadows_8":
			dialog.text = "Oh, lei era davvero qualcosa. Ogni marinaio della 'Neptune' obbediva ai suoi ordini, e non solo perché era la donna del capitano. Jess aveva imparato l’arte della spada e della navigazione, le fatiche del Macellaio non erano andate sprecate. Era tosta, temeraria, e per di più belloccia. Un mucchio di uomini volevano infilarsi nel suo letto, ma lei desiderava solo il Macellaio; dar fastidio a Jess era proprio da pazzi – molti hanno sentito le conseguenze sulla propria pelle, e per i più insistenti le sue lezioni di scherma sono state le ultime in vita loro. Jess possedeva una spada veramente unica, l’unica del suo genere nei Caraibi – non so proprio dove l’avesse trovata. Una lama a onde di fuoco. Nessuno può afferrare quella lama: anche solo sfiorarla lascia una ferita maledetta. Jess era avventuriera non per nascita, ma per destino. Ah, se vuoi sapere di più su di lei, puoi parlare con un tuo vecchio conoscente: lui saprà raccontarti molto più di quanto possa fare io.";
			link.l1 = "Davvero? E chi sarebbe costui?";
			link.l1.go = "shadows_9";
		break;
		
		case "shadows_9":
			dialog.text = "Jan Svenson. Il Diavolo della Foresta non lo ammetterà mai, ma aveva mire su Jessica. Era quel periodo in cui si era già preso il Main Occidentale e la sua fama faceva rodere d’invidia, così la tigre gli era alla pari\nQuando il Macellaio si sbarazzò di Jess, Jan cominciò a farsi vedere a Barbados con una frequenza sospetta, facendo tremare la guarnigione inglese. Come sai, Jessica era figlia di un piantatore di Bridgetown\nInsomma, i suoi progetti erano cosa nota tra chi conta, ma nessuno osava fiatare: ora magari Jan si gratta la pancia a Blueweld, ma allora una parola storta e finivi male\nAlla fine, tra loro non funzionò. Jess non poteva sopportare il modo in cui il Macellaio la trattava e si prese la rivincita un anno dopo, col favore della Maschera. Quella vendetta fu una rovina per tutti: per il Macellaio, per Beatrice, per la Maschera e per lei stessa. Sono crepati tutti.";
			link.l1 = "Non tutti. Il Macellaio è ancora vivo.";
			link.l1.go = "shadows_10";
		break;
		
		case "shadows_10":
			dialog.text = "Cosa? Ho capito male? È ancora vivo?!";
			link.l1 = "Sì. Il Capitano Butcher non fu impiccato. Avrebbe dovuto, dannazione, ma se la cavò grazie a Jacob Jackman e Henry il Boia, che misero paura al carnefice. Era tutta una messinscena. Ho le prove.";
			link.l1.go = "shadows_11";
		break;
		
		case "shadows_11":
			dialog.text = "Impossibile! E dove si trova adesso?";
			link.l1 = "Lo chiamano Lawrence Beltrope e vive a Port Royal. Resta comunque un tipo pericoloso. Jackman, che ha seminato tanto scompiglio tra i Fratelli della Costa, agiva ai suoi ordini.";
			link.l1.go = "shadows_12";
		break;
		
		case "shadows_12":
			dialog.text = "Maledizione! Dopo tanto tempo il quartiermastro aveva ritrovato il suo capitano! Dici Beltrope... aspetta! Ora capisco perché tra le carte di Blaze c’era quella strana nota d’interrogatorio... Pare che anche Blaze avesse scoperto qualcosa su Macellaio-Beltrope...";
			link.l1 = "Di che diavolo vai cianciando?";
			link.l1.go = "shadows_13";
		break;
		
		case "shadows_13":
			dialog.text = "Dopo essermi sistemato qui, ho rovistato tra le carte del vecchio Blaze. Ho trovato il verbale di un interrogatorio di certo Samuel Brooks. Parlava a lungo delle scorribande di Thomas Beltrope, noto bucaniere e intimo di Nicolas Sharp. Pare fosse il padre del Macellaio.";
			link.l1 = "Interessante. Pare che i figli di Sharp e Beltrope abbiano seguito le orme dei loro genitori...";
			link.l1.go = "shadows_14";
		break;
		
		case "shadows_14":
			dialog.text = "Par proprio di sì... Ma dimmi, compare, che t’importa così tanto delle gesta degli scomparsi? Quali sono i tuoi pensieri?";
			link.l1 = "Mi servono dei documenti che attestino che Helen McArthur è figlia di Beatrice Sharp e che ha pieno diritto a portare questo cognome. Non m'importa che sia anche una Beltrope.";
			link.l1.go = "shadows_15";
		break;
		
		case "shadows_15":
			dialog.text = "Non c'è traccia di Helen McArthur né tra le carte di Leadbeater né negli archivi di Blaze. Strano che Beatrice non abbia mai detto a Blaze della nascita della sua nipote. Non è da lei.";
			link.l1 = "Ascolta, forse c’è qualcos’altro nei documenti di Sharp? Ho bisogno di ogni dettaglio!";
			link.l1.go = "shadows_16";
		break;
		
		case "shadows_16":
			dialog.text = "Hm, suppongo di sì. Secondo gli appunti di Blaze, stava cercando l'isola dove sua sorella era morta. Ci sono dei documenti sulla spedizione punitiva di Leadbeater. Niente di interessante, a parte qualche cifra di latitudine.\nQuesta parallela attraversa il Mare dei Caraibi nella sua parte settentrionale. Ma non c'è traccia della longitudine. Ovviamente, le ricerche di Blaze sono andate a vuoto, non immagini nemmeno quanti isolotti ci siano a quella latitudine.";
			link.l1 = "E che sarebbe?";
			link.l1.go = "shadows_17";
		break;
		
		case "shadows_17":
			dialog.text = "Vediamo un po'... eccolo: latitudine 21 gradi 32' Nord. Non so proprio come possa aiutarti.";
			link.l1 = "Andrà così. Va bene, Steven, grazie davvero per la tua schiettezza. Ci si rivede!";
			link.l1.go = "shadows_18";
		break;
		
		case "shadows_18":
			DialogExit();
			pchar.questTemp.Saga.Shadows = "jessika";
			AddQuestRecord("Shadows", "6");
			LAi_SetHuberType(npchar);
			NextDiag.CurrentNode = "First time";
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
			pchar.questTemp.AlexClock = "dodson"; // 280912
		break;
		
		// суп из черепахи
		case "terrapin":
			dialog.text = "Potresti dirlo. Ora, parlando di Tortuga\nL'isola si chiama così perché sembra proprio una tartaruga. Levasseur ha rinforzato il guscio per dodici anni - il forte La Roche. Un assalto frontale è una follia, i cannoni pesanti del forte non lasciano scampo. Quindi, cucinare questa bellezza non sarà affare semplice. Gli spagnoli ci provano da una vita, mai riusciti.";
			link.l1 = "Ecco perché sono andato da Svenson. Allora, qual è il tuo piano? Forza, Steven!";
			link.l1.go = "terrapin_1";
		break;
		
		case "terrapin_1":
			dialog.text = "I miei uomini hanno fatto un buon lavoro a Tortuga nelle ultime settimane, e hanno raccolto parecchie notizie interessanti. Dunque ho buone nuove per te, compare! Pare che non dovrai affrontare i cannoni di La Roche, perché non siamo gli unici stanchi di Levasseur. Tra i suoi stessi sodali, c’è chi lo vuole morto quanto noi.";
			link.l1 = "Avanti...";
			link.l1.go = "terrapin_2";
		break;
		
		case "terrapin_2":
			dialog.text = "Si sa che Levasseur ha un debole per le giovani colone. Spariscono dopo che lui si è divertito con loro. Il principale fornitore di schiavi a Tortuga si chiama Robert Marten, comandante del galeone Voltigeur. Il suo compare, Henri Thibaut, nipote di Levasseur, sceglie le ragazze bianche più belle direttamente al porto per il suo protettore. Non molto tempo fa, Marten ha messo le mani su una splendida ragazza di una brigantina inglese. Si chiama Molly Jones. L’ha consegnata non a Levasseur, ma al nipote, di notte, in qualche grotta segreta di Tortuga. All’equipaggio è stato detto che la ragazza è morta d’infarto e che il 'corpo' è stato gettato a mare. Pare che i nostri compari abbiano deciso di tenersi il bel bocconcino. Se Levasseur viene a sapere di Molly, quei due avranno seri guai.";
			link.l1 = "E come possiamo fidarci di queste informazioni? È chiaro come il sole che entrambi sanno di maneggiare fuoco vivo...";
			link.l1.go = "terrapin_3";
		break;
		
		case "terrapin_3":
			dialog.text = "Vero. Ma ogni catena ha il suo anello debole. E ne ho trovato uno per te. Tre giorni fa, un ex marinaio della 'Voltigeur', di nome Fernand Lucas, ha bevuto troppo e ha spifferato un sacco di cose interessanti nella taverna di Basse-Terre\nPare che Molly Jones gli abbia chiesto di mandare a chiamare suo fratello a St John's per chiedere aiuto. Ma Lucas non è mai arrivato a destinazione, è scappato dal suo capitano e ora si scola il coraggio nel rum in Guadalupa\nAntigua non è un porto sicuro per i pirati francesi. Ricordalo! Il colonnello Fox è pronto a impiccarli a ogni palma dell'isola, dopo che sua moglie è caduta per mano di un corsaro francese. E i suoi marines feroci eseguiranno ogni suo ordine senza batter ciglio.";
			link.l1 = "Non comprendo ancora come questo si leghi ai nostri affari... Parliamo dei nostri ragazzi, Marten e Thibaut. Qual era il senso di rischiare tanto? Il fascino di quella donna era davvero così potente, o quei mercanti di schiavi hanno mostrato clemenza?";
			link.l1.go = "terrapin_4";
		break;
		
		case "terrapin_4":
			dialog.text = "Conosco bene quella canaglia di Marten. Se sta rischiando il collo, vuol dire che c'è d'oro in ballo o che teme per la sua pellaccia. Non so cosa c'entri la nostra prigioniera con tutto questo.\nForse Robert spera di ricavare un bel riscatto per lei, anche se ne dubito: sembrava più una servetta che altro. Oppure... Ah! Mi domando chi mai potrebbe far tremare Marten più di Levasseur!";
			link.l1 = "E perché credi che la signorina Jones sia ancora tenuta nascosta al governatore? Forse hanno già ottenuto da lei ciò che volevano e l’hanno consegnata a Levasseur? Allora, hai forse qualche dettaglio concreto su questo Thibaut?";
			link.l1.go = "terrapin_5";
		break;
		
		case "terrapin_5":
			dialog.text = "Non so molto di quell’uomo. So solo che lo zio si fida abbastanza di quel cucciolo da farne il suo erede. Ha ancora una ragazza, altrimenti a che бы gli servirebbero tutte queste trame?\nNon si capisce dove tengano la ragazza né perché Thibaut lasci che Marten prenda il comando. C’è un mistero qui, che potrebbe aiutarci a vincere questa partita senza dover assaltare Tortuga. Sei francese, quindi immagino che sia di tuo gusto.\nMa devi sbrigarti, le chiacchiere da ubriaco di Lucas potrebbero già essere arrivate alle orecchie degli agenti di Marten e Levasseur, e puoi immaginare le conseguenze!";
			link.l1 = "Capisco. Quindi, Thibaut è l’erede di Levasseur? E nasconde una schiava allo zio? Maledizione, immagino che il ragazzo non veda l’ora che lo zio crepi!";
			link.l1.go = "terrapin_6";
		break;
		
		case "terrapin_6":
			dialog.text = "Vero. A sentire Lucas, questa Molly è una bellezza rara, il nostro coraggioso Thibaut potrebbe pure innamorarsene. Sai bene cosa la gente sia capace di fare per amore. Vai a Basse-Terre\ntrova quell’idiota ubriaco e falla parlare. Inoltre, dovresti scoprire tutto il possibile su Molly e suo fratello. Magari ti conviene passare prima per Antigua, Molly ci ha mandato Lucas per qualche ragione. Ma quale sarà questa ragione?";
			link.l1 = "Capisco. Non perdiamo tempo. Ti ringrazio, Steven.";
			link.l1.go = "terrapin_7";
		break;
		
		case "terrapin_7":
			DialogExit();
			AddMapQuestMarkCity("SentJons", true);
			AddMapQuestMarkCity("BasTer", true);
			AddQuestRecord("Terrapin", "1");
			pchar.questTemp.Terrapin = "baster";
			pchar.questTemp.Terrapin.SJ_count = 0;
			// прячем Фокса
			sld = characterFromId("Fox");	
			ChangeCharacterAddressGroup(sld, "none", "", "");
			// садим в таверну Робера Мартэна
			float fMft = MOD_SKILL_ENEMY_RATE/10;
			sld = GetCharacter(NPC_GenerateCharacter("Rober", "Marten", "man", "man", 30, FRANCE, -1, true, "quest"));
			FantomMakeCoolSailor(sld, SHIP_GALEON_L, "Voltigeur", CANNON_TYPE_CANNON_LBS20, 90, 90, 90);
			FantomMakeCoolFighter(sld, 30, 80, 80, "blade_19", "pistol5", "bullet", 150);
			sld.name = "Rober";
			sld.lastname = "Marten";
			sld.dialog.FileName = "Quest\Sharlie\Terrapin.c";
			sld.dialog.currentnode = "Rober";
			sld.greeting = "pirat_common";
			TakeNItems(sld, "potion2", 1);
			TakeNItems(sld, "potion3", 2);
			SetCharacterPerk(sld, "Energaiser");
			SetCharacterPerk(sld, "BasicDefense");
			SetCharacterPerk(sld, "AdvancedDefense");
			SetCharacterPerk(sld, "CriticalHit");
			SetCharacterPerk(sld, "Tireless");
			SetCharacterPerk(sld, "HardHitter");
			SetCharacterPerk(sld, "Sliding");
			SetCharacterPerk(sld, "BladeDancer");
			SetCharacterPerk(sld, "SwordplayProfessional");
			SetCharacterPerk(sld, "Gunman");
			SetCharacterPerk(sld, "GunProfessional");
			SetCharacterPerk(sld, "MusketsShoot");
			SetCharacterPerk(sld, "LongRangeGrappling");
			SetCharacterPerk(sld, "GrapplingProfessional");
			SetCharacterPerk(sld, "HullDamageUp");
			SetCharacterPerk(sld, "SailsDamageUp");
			SetCharacterPerk(sld, "CrewDamageUp");
			SetCharacterPerk(sld, "CriticalShoot");
			SetCharacterPerk(sld, "LongRangeShoot");
			SetCharacterPerk(sld, "BasicBattleState");
			SetCharacterPerk(sld, "AdvancedBattleState");
			SetCharacterPerk(sld, "ShipDefenseProfessional");
			SetCharacterPerk(sld, "ShipSpeedUp");
			SetCharacterPerk(sld, "ShipTurnRateUp");
			SetCharacterPerk(sld, "WindCatcher");
			SetCharacterPerk(sld, "SailsMan");
			SetCharacterPerk(sld, "Doctor1");
			SetCharacterPerk(sld, "Doctor2");
			sld.MultiFighter = 1.0+fMft; // мультифайтер
			LAi_SetSitType(sld);
			UpgradeShipParameter(sld, "SpeedRate");//апгрейдить скорость
			UpgradeShipParameter(sld, "TurnRate");//манёвренность
			FreeSitLocator("Baster_tavern", "sit1");
			ChangeCharacterAddressGroup(sld, "Baster_tavern", "sit", "sit1");
			if(bImCasual)
			{
				NewGameTip("Exploration mode: quest duration doubled");
				SetFunctionTimerCondition("Terrapin_LateBaster", 0, 0, 20, false); // таймер
			}
			else SetFunctionTimerCondition("Terrapin_LateBaster", 0, 0, 10, false); // таймер
			
			// Квест "Погасшая Звезда" провалена, всё удаляем
			if (GetCharacterIndex("Longway") != -1 && CheckPassengerInCharacter(pchar, "Longway"))
			{
				CloseQuestHeader("PZ");
				DeleteAttribute(pchar, "questTemp.PZ_Etap5_Start");
				DeleteAttribute(pchar, "questTemp.PZ_Etap4_Start");
				DeleteQuestCondition("PZ_Etap5_Start");
				DeleteQuestCondition("PZ_LongwayCapstervilleDialog");
				DeleteQuestCondition("PZ_OhotaNaZvezdu_Kapstervil");
				DeleteQuestCondition("PZ_OhotaNaZvezdu_Yamaika");
				DeleteQuestCondition("PZ_Beliz_PoterpKrushenie");
				pchar.questTemp.PZ_ProvalFinal = true;
			}
		break;
		
		case "terrapin_8":
			dialog.text = "Avanti!";
			link.l1 = "Ho trovato il fratello di Molly a San Giovanni. È il servitore di Fox. Ma c’è qualcosa di strano. Sua sorella Molly è una megera famosa, brutta come la fame e alta più o meno come te. Fa la domestica per la figlia di Fox, Catherine, e fino a poco tempo fa stava in Inghilterra con lei...";
			link.l1.go = "terrapin_9";
		break;
		
		case "terrapin_9":
			dialog.text = "";
			link.l1 = "Quanto a Catherine, sì, è famosa per la sua bellezza e aveva intenzione di andare a trovare suo padre per il suo compleanno, ma arrivò in ritardo a causa del ritardo dello squadrone a Londra...";
			link.l1.go = "terrapin_10";
		break;
		
		case "terrapin_10":
			dialog.text = "";
			link.l1 = "Suo padre, che ha preso molto male la morte della moglie per mano di un corsaro francese, le ha severamente proibito di lasciare l’Inghilterra da sola su una nave. Quindi Molly Jones non può essere la prigioniera di Thibaut. Allora chi è lei?";
			link.l1.go = "terrapin_11";
		break;
		
		case "terrapin_11":
			dialog.text = "Hm... Dannazione se lo so. Forse è un’altra Molly Jones, non quella di cui chiedi tu. Però... troppe coincidenze. Non credo sia solo un caso! Ho dei sospetti confusi ma... su quest’isola accadono cose assai strane!";
			link.l1 = "Cosa vuoi dire? Dimmi tutto!";
			link.l1.go = "terrapin_12";
		break;
		
		case "terrapin_12":
			dialog.text = "E se la figlia avesse disubbidito agli ordini del padre e salpato senza scorta? Il mese scorso le tempeste furono feroci, l'Albatro potrebbe essersi danneggiato ed essere diventato facile preda per Marten. Sospetto che Catherine non abbia dato il suo vero nome, dovresti capire il perché, e ora la tengono a Tortuga sotto il nome di Molly.\nSai bene che destino l'aspetta se il suo vero nome venisse scoperto. Ora tutto comincia ad avere un senso!";
			link.l1 = "Maledizione! Non ci avrei mai pensato! Molly... Catherine... Ma tutto si incastra!";
			link.l1.go = "terrapin_13";
		break;
		
		case "terrapin_13":
			dialog.text = "Ecco di che parlo, compare. Non so se abbiamo ragione, ma...";
			link.l1 = "Ma questo cambia tutto! Forse dovremmo chiedere aiuto agli inglesi? Lasciar che le baionette dei marines ci faccian strada!";
			link.l1.go = "terrapin_14";
		break;
		
		case "terrapin_14":
			dialog.text = "Calmati, "+pchar.name+"! Abbiamo bisogno di prove più solide. Non possiamo esserne certi. La vera Catherine potrebbe trovarsi a Londra, in attesa che uno squadrone salpi. Gli inglesi hanno già i loro guai, non rischieranno un attacco a La Roche. Ma se i nostri sospetti sono fondati e il colonnello Fox scoprirà cos'è successo a sua figlia...\n Organizzerà un blocco intorno all'isola e aspetterà l'arrivo dello squadrone. Poi attaccherà la città. Le volpi di mare sono una forza temibile nel corpo a corpo. Son certo che isserebbe la bandiera inglese sulle rovine di Tortuga in tre giorni. Vuoi davvero questo?";
			link.l1 = "No, non è il nostro costume. Ora capisco di quale riscatto parla Marten.";
			link.l1.go = "terrapin_15";
		break;
		
		case "terrapin_15":
			dialog.text = "Dobbiamo agire con cautela. Non siamo nemmeno certi che Marten conosca la vera identità della vera Molly. Ricattare il colonnello Fox sarebbe pura follia, roba da suicidio. Soprattutto ora che la squadriglia di Cromwell è in arrivo da un momento all’altro.\nSe Catherine muore, perdiamo anche noi. La nostra Confraternita non ha alcun interesse a far infuriare ancora di più il colonnello Fox. Quell’uomo può scatenare un mare di guai. Se Catherine dovrà morire, che almeno non sia per mano nostra, e solo dopo che avrà giocato la sua parte in questa nostra partita.\nMa molto meglio sarebbe consegnare la povera ragazza a suo padre. Il suo salvatore sarà ricompensato, se non in questa vita, allora nell’altra.";
			link.l1 = "Per la misericordia del Signore... Steven, sei un genio! Salpo subito per Tortuga! Scoprirò chi è questa Molly Jones! Maledizione, sono certo che si tratta di Catie Fox!";
			link.l1.go = "terrapin_16";
		break;
		
		case "terrapin_16":
			dialog.text = "Forse... Non perdere tempo, "+pchar.name+". E se avevo ragione - assicurati che resti in vita.";
			link.l1 = "Farò quel che posso. Ci si vede!";
			link.l1.go = "terrapin_17";
		break;
		
		case "terrapin_17":
			DialogExit();
			AddQuestRecord("Terrapin", "7");
			pchar.questTemp.Terrapin = "tortuga1";
			pchar.questTemp.Terrapin.Room_close = "true": // не пускать в комнату таверны
		break;
		
		case "guardoftruth":
			dialog.text = "Ahoy! Sputa il rospo, compare! Qui risolviamo ogni maledetto guaio, parola di pirata!";
			link.l1 = "Vado subito al sodo, allora. Conosci Miguel Dichoso?";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "Lo conosco. Quel don spagnolo mi vendette una nave magnifica – una fregata. Ah, che vascello era, immaginatelo solo...";
			link.l1 = "Lascia indovinare, scafo unico, sedici nodi di velocità massima? 'Santa Quiteria'?";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "Hai ragione sullo scafo e la velocità, ma il nome era un altro – 'San Martin'. Gli ho dato un sacco di dobloni, era tutto ciò che possedevo. Tutti i miei risparmi sono finiti nelle tasche di quel furfante.";
			link.l1 = "Sei sicuro che si chiamasse San Martin e non Santa Quiteria? E quando l’hai comprata? E perché lo chiami canaglia?";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "Quante domande! Risponderò a tutte, con ordine: sono certo che si trattasse della San Martin. Io stesso aiutai gli uomini di Alexus a levare dal timone quella tavola col nome papista. La battezzai 'Fortuna' – un nome assai più degno per una tale principessa.\nL’ho comprata poco prima che Blaze Sharp venisse ammazzato, nell’inverno del 1654. Perché chiamavo Miguel così? Perché quel figlio di puttana fu capace di portar via la nave dalla base militare spagnola di Providence. Mettemmo su un bello spettacolo per gli spagnoli, proprio davanti al forte di San Juan. Dovetti sacrificare due lugri già mezzi morti per rendere la cosa più credibile: bruciammo e affondammo le barche, simulando una battaglia con la fregata. E quando calò la notte, portammo la San Martin fino all’Isola Tesoro... Io ottenni la nave e Dichoso prese il denaro. Disse ai suoi superiori che la fregata era stata affondata in uno scontro coi pirati, e il comandante di San Juan confermò la storia.";
			link.l1 = "Dunque, è così che i don spagnoli si riempiono le tasche! Che furfante! Dimmi, è davvero accaduto nell’inverno del 1654? O forse in primavera? E la fregata, l’ha sferzata la tempesta?";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			dialog.text = "In inverno... Maledizione, non ne sono affatto certo – forse era primavera, pure. Davvero non ricordo. La fregata non aveva un graffio, era tutta nuova. Pareva appena varata. Quando ci ripenso, mi vien da piangere dalla rabbia...";
			link.l1 = "Perché? Già, e dov'è ora la tua splendida fregata?";
			link.l1.go = "guardoftruth_5";
		break;
		
		case "guardoftruth_5":
			dialog.text = "Perché lei mi ha lasciato. Mi hanno incastrato, hanno messo il mio talismano sul cadavere di Blaze e sparso la voce che fossi io l’assassino. Poi ho sentito che Marcus Tyrex, il nostro custode del codice, voleva marchiarmi di nero. Così ho deciso di filarmela da quel vespaio per un po’ sull’Isola Giustizia, dove poi mi hai trovato tu. \nNon potevo arrivarci con una fregata, così l’ho impegnata al Parroco Nero in cambio di una brigantina carica di viveri; non avevo granché monete dopo quel losco affare con Dichoso. Speravo di vendere i viveri e tornare a Isla Tesoro in un mesetto o due... Beh, il resto lo sai già.";
			link.l1 = "E il Pastore Nero non t’ha aspettato, così l’ha venduta";
			link.l1.go = "guardoftruth_6";
		break;
		
		case "guardoftruth_6":
			dialog.text = "Proprio così. Fu comprata da un inglese, o meglio, da uno scozzese, William Paterson. Potrei anche provare a riprendere la ragazza, certo, ma quel montanaro è un osso duro, un capitano della Marina Reale e gran compare del colonnello Fox. E poi, faceva affari con Jackman proprio come tu li facevi con Svenson.\nLo scozzese ha uno squadrone... al diavolo, non rivedrò più la mia nave.";
			link.l1 = "Capisco. Ma sai dove si trova ora quel Dichoso?";
			link.l1.go = "guardoftruth_7";
		break;
		
		case "guardoftruth_7":
			dialog.text = "Non ne ho la minima idea. Non l’ho più visto da quando ho acquistato la mia Fortuna.";
			link.l1 = "E perché Miguel non l'ha offerta a qualcun altro? Che mi dici di Tyrex, Barbazon, Sharp? O magari Paterson?";
			link.l1.go = "guardoftruth_8";
		break;
		
		case "guardoftruth_8":
			dialog.text = "Non ne ho la minima idea. Paterson non c’era quella volta, per quel che ricordo. Zachariah, Jacques e Marcus non avrebbero mai acconsentito e io... io ci tenevo proprio a quella fregata!";
			link.l1 = "Capisco che... non ci capisco un’acca. Enigmi dappertutto...";
			link.l1.go = "guardoftruth_9";
		break;
		
		case "guardoftruth_9":
			dialog.text = "Scavi ancora nel passato? Quale isola vuoi conquistare stavolta? Ah-ah-ah!";
			link.l1 = "C'è un'isola... Ma ancora non so come arrivarci. Va bene, Steven, grazie delle tue dritte! Addio!";
			link.l1.go = "guardoftruth_10";
		break;
		
		case "guardoftruth_10":
			dialog.text = "Buona fortuna, "+pchar.name+"!";
			link.l1 = "...";
			link.l1.go = "guardoftruth_11";
		break;
		
		case "guardoftruth_11":
			DialogExit();
			AddQuestRecord("Guardoftruth", "60");
			pchar.questTemp.Guardoftruth.Archy = "guadeloupe";
			// маленькая развлекуха
			pchar.quest.GuardOT_cabinattack.win_condition.l1 = "EnterToSea";
			pchar.quest.GuardOT_cabinattack.function = "GuardOT_PrepareCreateBandosInCabin";
		break;
		
		case "tieyasal":
			dialog.text = "E son lieto d’aiutarti, come sempre. Che t’ha portato qui stavolta, "+pchar.name+"?";
			link.l1 = "Si tratta ancora del tuo vecchio amico Miguel Dichoso. So che l'hanno visto di nuovo sull'Isola Tesoro. Non puoi aiutarmi a rintracciarlo?";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "Oh, amico, in verità non lo sapevo. Non l’ho visto da queste parti. Non l’ho più incrociato da quando gli ho comprato la 'Fortuna'. E dimmi, che te ne fai di quel don spagnolo?";
			link.l1 = "Mi serve. Miguel conosce la rotta per una vecchia città indiana. Ho una gran voglia di arrivarci.";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			dialog.text = "Come sempre, amico mio, ti vai a ficcare nei guai. Ahimè, non posso aiutarti. Ti consiglio di girare per il villaggio e parlare con la gente, magari qualcuno l’ha visto. Qui è un uomo ben noto, sai.";
			link.l1 = "Ehi, Steven, puoi almeno dirmi che aspetto ha?";
			link.l1.go = "tieyasal_3";
		break;
		
		case "tieyasal_3":
			dialog.text = "Beh, ha venticinque, forse ventotto anni, più o meno la tua altezza, occhi scuri, senza parrucca. Porta una cicatrice di sciabola sulla guancia destra.";
			link.l1 = "Hm. Sai, qui ci sono parecchi che risponderebbero a quella descrizione.";
			link.l1.go = "tieyasal_4";
		break;
		
		case "tieyasal_4":
			dialog.text = "Non ci sono altri particolari su di lui. È sicuro di sé, insolente e tremendamente pericoloso. Di lui correvano molte voci...";
			link.l1 = "Capisco. Va bene, farò un giro di domande su di lui. Buona fortuna, Steven!";
			link.l1.go = "tieyasal_5";
		break;
		
		case "tieyasal_5":
			DialogExit();
			AddQuestRecord("Tieyasal", "2");
			npchar.quest.tieyasal = "true";
		break;
		
		// Jason НСО
		case "patria":
			dialog.text = "Oho! Sei arrivato nel posto giusto! Sputa il rospo!";
			link.l1 = "C'è un tipo che non teme i pirati. Li prende alla leggera. Serve dargli una lezione di rispetto. Ricorda, non ucciderlo.";
			link.l1.go = "patria_1";
		break;
		
		case "patria_1":
			dialog.text = "Ah! Ma guarda chi si vede, il vecchio Charles in carne e ossa! Scommetto che ti sei cacciato di nuovo in qualche pasticcio! Su, raccontami tutto: chi è la preda stavolta e che lezione gli dobbiamo impartire?";
			link.l1 = "Un ospite dall’Europa, un ispettore del Ministero delle Finanze francese – il barone Noel Forget. Vorrebbe mettere su una Compagnia Commerciale Francese qui, ma io e un caro compare ci opponiamo. Abbiamo provato a far capire al Barone che trafficare qui è un azzardo: olandesi, inglesi, e soprattutto quei cani di pirati da quando Levasseur è caduto... ma non ci ha dato ascolto. Bisogna fargli provare la paura sulla propria pelle, così forse capirà.";
			link.l1.go = "patria_2";
		break;
		
		case "patria_2":
			dialog.text = "Sì-sì... Un vero barone!.. Assalteremo la sua nave?";
			link.l1 = "Ecco il piano: la sua nave salperà presto da Port-au-Prince verso Capsterville. Devi intercettare il Barone dopo la sua partenza e prenderlo in ostaggio. Sarebbe meglio non affondare la nave e risparmiare l’equipaggio. In fondo, i francesi sono nostri alleati. Te la senti di farcela?";
			link.l1.go = "patria_3";
		break;
		
		case "patria_3":
			dialog.text = "Ebbene, non posso promettere nulla. Ma ci proverò. Di quale nave si tratta?";
			link.l1 = "Una brigantina chiamata 'Favory'.";
			link.l1.go = "patria_4";
		break;
		
		case "patria_4":
			dialog.text = "Una brigantina non può reggere il confronto con la mia fregata. Li spazzeremo via senza fatica. Se si arrenderanno, risparmierò la vita a tutti.";
			link.l1 = "Perfetto. Incuti timore e offri loro la resa. Poi, manda il Barone nella stiva piena di ratti. Cerca il posto più lurido che trovi, ma non lasciarlo lì più di un giorno, altrimenti potrebbe prender qualche malanno e crepare. Poi mettilo in cabina, portalo all’Isola Tesoro e rinchiudilo in qualche posto appartato. Vesti alcuni dei tuoi uomini da mercanti francesi prigionieri e fagli recitare la parte. Per tre giorni filati, dovranno raccontargli di come i pirati spietati li inseguono, li depredano, chiedono riscatti, li torturano... tutto nei minimi dettagli.";
			link.l1.go = "patria_5";
		break;
		
		case "patria_5":
			dialog.text = "Ah-ah-ah! Questa dev’essere la faccenda più spassosa che mi sia mai capitata da un bel pezzo! Ebbene sì, troverò certi attori, compare. Nessun dubbio: dopo le loro storie, il tuo barone si farà sotto addosso! Gli mostreranno cicatrici di sciabole e aste roventi...";
			link.l1 = "Colpito nel segno. Poi lo costringerai a scrivere una lettera a Poincy, chiedendo un riscatto. Trecentocinquantamila per un pesce grosso del genere non sono poi così tanti.";
			link.l1.go = "patria_6";
		break;
		
		case "patria_6":
			dialog.text = "Bene. Che faremo adesso?";
			link.l1 = "E allora porterai il Barone a Turks. Là prenderai il riscatto, e mi consegnerai il Barone. E dovrai pure dire che tutti i francesi pagheranno per Tortuga e Levasseur.";
			link.l1.go = "patria_7";
		break;
		
		case "patria_7":
			dialog.text = "Ah-ah-ah! Che diavolo di scherzo! Noi, beh, sai cosa abbiamo fatto a Levasseur, e ora... ah-ah-ah!.. Va bene, compare. Si farà! Dici che la nave arriverà presto?";
			link.l1 = "Presto. Dobbiamo stare all’erta.";
			link.l1.go = "patria_8";
		break;
		
		case "patria_8":
			dialog.text = "Non ti preoccupare , non ti deluderò. Me ne occuperò di persona. Quando sentirai dire che questo barone è stato catturato, vieni da me.";
			link.l1 = "Bene. Ti ringrazio, Steven.";
			link.l1.go = "patria_9";
		break;
		
		case "patria_9":
			DialogExit();
			AddQuestRecord("Patria", "70");
			pchar.questTemp.Patria = "epizode_12_wait";
			pchar.questTemp.Patria.Condotier.Success = "true";
			LocatorReloadEnterDisable("Pirates_town", "reload3_back", true);
		break;
		
		case "patria_10":
			dialog.text = "Ma certo, compare. Come pattuito. Racconti da far rizzare i peli su pirati malvagi, che fanno a pezzi poveri mercanti francesi... Frustate, lamenti e urla. Un braciere acceso, manette arroventate. Proprio come ci si aspetta, eh.";
			link.l1 = "Ehi, frena i cavalli! Mi serve vivo, quello.";
			link.l1.go = "patria_11";
		break;
		
		case "patria_11":
			dialog.text = "Non temere, resterà in vita. Ha scritto quella lettera con mano tremante. Eccola qui.";
			link.l1 = "Cosa c’è scritto lì? Sta forse implorando Poincy di tirarlo fuori da questo guaio?";
			link.l1.go = "patria_12";
		break;
		
		case "patria_12":
			dialog.text = "Proprio così, compare! Sta implorando!";
			link.l1 = "Butta via questa lettera, o meglio ancora - bruciala. Ci vediamo a Turks tra una settimana. Deve sembrare che ci serva tempo per raccogliere il riscatto.";
			link.l1.go = "patria_13";
		break;
		
		case "patria_13":
			dialog.text = "Inteso. Fra una settimana, nel golfo del nord. Non scordarti la grana: dev’essere tutto in bella mostra. Poi vieni da me, sistemeremo la faccenda.";
			link.l1 = "Certo, scommetto che perfino un riccio di mare l’avrebbe capito. A presto!";
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
			dialog.text = "Ehi, mangia-rane! Fermo là!";
			link.l1 = "Non mi muovo.";
			link.l1.go = "patria_16";
		break;
		
		case "patria_16":
			dialog.text = "Ecco il tuo barone. Un po' malconcio, ma tutto d’un pezzo. È lui?";
			link.l1 = "Sì.";
			link.l1.go = "patria_17";
		break;
		
		case "patria_17":
			dialog.text = "Perfetto. Ora, consegna il denaro o lui è spacciato! E non provare a fregarci, ti teniamo nel mirino!";
			if (sti(pchar.money) >= 350000)
			{
				link.l1 = "Ecco.";
				link.l1.go = "patria_18";
			}
			else
			{
				link.l1 = "Maledizione! L'ho lasciato sulla nave...";
				link.l1.go = "patria_22";
			}
		break;
		
		case "patria_18":
			AddMoneyToCharacter(pchar, -350000);
			dialog.text = "Ah-ah-ah! Sei sveglio, ragazzino, francese. Prendi la tua santità. E di’ a Poincy che si prepari a sborsare: tutti i bastardi francesi dovranno pagare per quello che avete fatto a Levasseur e a Tortuga. E i vostri mercanti ci pagheranno con le loro merci e le loro navi. Ah-ah-ah! E non dimenticare di portarci altri baroni nell’arcipelago, ci riempiono le tasche! Ah-ah-ah!";
			link.l1 = "Per favore, vai alla mia barca, Barone.";
			link.l1.go = "patria_19";
		break;
		
		case "patria_19":
			sld = CharacterFromID("Noel");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", 10.0);
			dialog.text = "E non ti azzardare nemmeno a inseguirci, capitano. Sai bene chi sono. Ho altri ranocchi prigionieri, e se non torno a casa in tempo, i miei uomini li faranno fuori tutti. Capito?";
			link.l1 = "Verrà il tempo e ci occuperemo di voi, maledetti bestemmiatori!";
			link.l1.go = "patria_20";
		break;
		
		case "patria_20":
			dialog.text = "Ah-ah-ah-ah!";
			link.l1 = "...";
			link.l1.go = "patria_21";
		break;
		
		case "patria_21":
			DialogExit();
			LAi_SetPlayerType(pchar);
			AddQuestRecord("Patria", "74");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "Patria_CondotierDodsonNorm", 10.0);
			sld = CharacterFromID("Terks_pirat");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", 8.0);
			pchar.questTemp.Patria = "epizode_12_baronalive";
			pchar.questTemp.Patria.DodsonAgain = "true";
			Island_SetReloadEnableGlobal("Bermudes", false); // закрыть остров до отвоза барона
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
			dialog.text = "Stai prendendo per il culo me?";
			link.l1 = "Un attimo, vado a prenderlo...";
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
			link.l1 = "Argh, Steven, che diavolo ha combinato il tuo sciocco!";
			link.l1.go = "patria_25";
		break;
		
		case "patria_25":
			dialog.text = "Charles, che diavolo stavi facendo? Dov'è il denaro? Non ho detto ai miei ragazzi che fosse una messinscena... e così questo babbeo s'è convinto che volevi fregarli...";
			link.l1 = "Che disgrazia! Il Barone è morto... E adesso che farà Poincy?";
			link.l1.go = "patria_26";
		break;
		
		case "patria_26":
			dialog.text = "Ebbene, compare, la colpa è tua, spero che tu lo capisca. Forse, alla fine, ti tornerà pure a vantaggio.";
			link.l1 = "Che stolto che sono! Ho rovinato tutto. Va bene, me ne andrò a Poincy... Perdonami per la mia stupidità, Steven, ci si vede.";
			link.l1.go = "patria_27";
		break;
		
		case "patria_27":
			dialog.text = "Devi riposare, stai perdendo la mano. Vieni da me quando vuoi, ti procuro del rum e qualche bella fanciulla.";
			link.l1 = "Grazie, verrò a farti visita quando potrò.";
			link.l1.go = "patria_28";
		break;
		
		case "patria_28":
			DialogExit();
			AddQuestRecord("Patria", "75");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "Patria_CondotierDodsonNorm", 10.0);
			sld = CharacterFromID("Terks_pirat");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", 8.0);
			pchar.questTemp.Patria = "epizode_12_barondie";
			// Теркс в норму
			LAi_LocationFightDisable(&Locations[FindLocation("Shore56")], false);
			LAi_LocationDisableOfficersGen("Shore56", false);
		break;
		
		case "patria_29":
			dialog.text = "Di nulla, compare. Per me è stato lo spasso più grande di quest’anno! Abbiamo riso a crepapelle, io e i miei ragazzi!.. Quindi ti ringrazio anch’io. Ecco il tuo denaro.";
			link.l1 = "Dovresti tenerti una parte per te.";
			link.l1.go = "patria_30";
		break;
		
		case "patria_30":
			AddMoneyToCharacter(pchar, 350000);
			dialog.text = "Lascia stare. L’ho fatto per l’amicizia che ci lega. La Fratellanza della Costa ti deve ben di più, eppure non hai chiesto neanche un doblone.";
			link.l1 = "Prendi comunque almeno cinquantamila per i servigi e come risarcimento. Grazie, Steven! Son lieto d'averti incontrato, allora, su quella stramba Isola Giustizia perduta fra i relitti.";
			link.l1.go = "patria_31";
		break;
		
		case "patria_31":
			AddMoneyToCharacter(pchar, -50000);
			dialog.text = "E anch'io. Charles, vieni a trovarmi quando avrai un momento!";
			link.l1 = "Con piacere!";
			link.l1.go = "patria_32";
		break;
		
		case "patria_32":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.Patria.DodsonAgain");
		break;
		
		case "patria_33":
			dialog.text = "Sei in ritardo di una settimana! Non ho detto ai miei ragazzi che tutto questo era una farsa... ! Non volevano più aspettare, e hanno deciso di farla finita col tuo barone!";
			link.l1 = "Che sciocco che sono! Ho rovinato tutto! E adesso cosa racconterò a Poincy?";
			link.l1.go = "patria_34";
		break;
		
		case "patria_34":
			dialog.text = "Ebbene, compare, la colpa è tutta tua, spero tu lo capisca. Forse, in fin dei conti, sarà persino meglio per te.";
			link.l1 = "D'accordo, andrò a Poincy... Perdonami per la mia stoltezza, Steven, ci vediamo...";
			link.l1.go = "patria_35";
		break;
		
		case "patria_35":
			dialog.text = "Devi riposare, stai perdendo la mano. Vieni da me qualche volta, ti procuro del rum e belle fanciulle";
			link.l1 = "Grazie, verrò a farti visita quando potrò.";
			link.l1.go = "patria_36";
		break;
		
		case "patria_36":
			DialogExit();
			AddQuestRecord("Patria", "75");
			pchar.questTemp.Patria = "epizode_12_barondie";
			DeleteAttribute(pchar, "questTemp.Patria.DodsonFail");
		break;
		// belamour legendary edition хвастаемся Фортуной
		case "check_out_my_frigate":
			dialog.text = "Interessante, m’incuriosisci. Su, facciamo due passi.";
			link.l1 = "...";
			link.l1.go = "check_out_my_frigate_01";
		break;
		
		case "check_out_my_frigate_01":
			DialogExit();
			chrDisableReloadToLocation = true;
			bDisableFastReload = true;
			DoQuestReloadToLocation("pirates_town", "reload", "reload3_back", "SharkFrigateToTown");
			pchar.questTemp.SharkFrigate = true;
		break;
		
		case "check_out_my_frigate_02":
			dialog.text = "Per mille balene! Non ci credo! È davvero lei? Dimmi, è proprio lei? Questa è la ‘Fortuna’?!";
			link.l1 = "Sì, amico mio, non sono i tuoi occhi a tradirti. È proprio lei. Ti mancava, eh?";
			link.l1.go = "check_out_my_frigate_03";
		break;
		
		case "check_out_my_frigate_03":
			dialog.text = "Ah ah ah, non ci posso credere! Mille diavoli! Ma dove diavolo l’hai pescata, questa?";
			link.l1 = "Da un certo scozzese di nome William Paterson. Sì, sì, proprio quello che l’ha preso dal Parroco Nero.";
			link.l1.go = "check_out_my_frigate_04";
		break;
		
		case "check_out_my_frigate_04":
			dialog.text = "Per mille balene... E che, ti ha venduto la 'Fortuna'? Una nave così splendida? Dopo che l’avevi già comprata?";
			link.l1 = "Hehe, beh, quasi. Diciamo così: non ci siamo proprio andati d'accordo, e mi sono preso la nave come risarcimento per le spese che ho dovuto affrontare per colpa della nostra lite. Tanto lui una nave non gli serve più.";
			link.l1.go = "check_out_my_frigate_05";
		break;
		
		case "check_out_my_frigate_05":
			dialog.text = "Mi sorprendi sempre di più... Quello è un capitano di ventura al servizio dell’Inghilterra. La sua squadra della colonia può saccheggiare a piacimento. Persino io non ho mai osato rompere i denti contro di lui. E come hai fatto a metterlo alla prova? Sei riuscito a strappare la 'Fortuna' dalla sua squadra?";
			link.l1 = "No, lo squadrone è affondato. In verità, non fu cosa da poco. La battaglia fu aspra, ma si svolse lontano da ogni anima viva, e solo i miei marinai e ufficiali ne furono testimoni. In sostanza, non temo la caccia dei maledetti inglesi. William Paterson... quello è semplicemente sparito in qualche sua solita scorribanda...";
			link.l1.go = "check_out_my_frigate_06";
		break;
		
		case "check_out_my_frigate_06":
			dialog.text = "Ah... Ormai avevo perso la speranza di riveder la mia rondinella. Beh, spero che questa nave ti sia leale compagna. Davvero contento per te, compare!";
			link.l1 = "Cosa? Non ti serve più? Volevo solo restituirlo al suo vero padrone...";
			link.l1.go = "check_out_my_frigate_07";
		break;
		
		case "check_out_my_frigate_07":
			if(CheckAttribute(pchar, "questTemp.SharkGoldFleet"))
			{
				dialog.text = "Ah-ah-ah, amico mio, tieni per te la 'Fortuna'. Primo, ne sei il legittimo padrone. Te la sei guadagnata onestamente in battaglia. Non sta bene abbandonare la nave dopo tutto ciò. E poi, ormai ho già una nuova imbarcazione. Quando acquistai la 'Fortuna', non pensavo che un giorno l’avrei mai cambiata con altro. Ma, siccome non mi aspettavo più di rivederla, ho commissionato un nuovo vascello ad Alexus. E sai... Maledizione se non è un capolavoro. Ho sentito, e in questa faccenda non sei stato certo all’oscuro, ah ah!";
			}
			else
			{
				dialog.text = "Ah-ah-ah, amico mio, tieni pure la 'Fortuna' per te. Primo, sei tu il suo vero padrone. Te la sei guadagnata onestamente in battaglia. Non si abbandona una nave così, dopo tutto questo. E poi, stanno già costruendo una nuova nave per me. Certo, quando ho comprato la 'Fortuna', mai avrei pensato di cambiarla con un'altra. Ma, visto che non pensavo più di rivederla, ho ordinato una nuova fregata da Alexus. E non vedo l’ora di poter calcare il suo ponte.";
			}
			link.l1 = "Ebbene, allora non mi resta che tenermi questa splendida nave per me, Steven!";
			link.l1.go = "check_out_my_frigate_08";
		break;
		
		case "check_out_my_frigate_08":
			dialog.text = "Esattamente. L’unica cosa che ti chiedo è di prenderti cura della 'Fortuna'. Fidati, una nave così non la troverai in nessun altro mare. È unica. E ci sono affezionato, come a un ricordo caro. Mi rincuorerebbe sapere che è posseduta da un amico, non da un qualche furfante.";
			link.l1 = "Va bene, Steven. Ti prometto che proteggerò la 'Fortuna'.";
			link.l1.go = "check_out_my_frigate_09";
		break;
		
		case "check_out_my_frigate_09":
			dialog.text = "Sì, e un’ultima faccenda...";
			link.l1 = "Ascolto.";
			link.l1.go = "check_out_my_frigate_10";
		break;
		
		case "check_out_my_frigate_10":
			dialog.text = "Dal momento che ora possiedi la 'Fortuna', vorrei proporti un affare.";
			link.l1 = "Ti sto ascoltando con la massima attenzione.";
			link.l1.go = "check_out_my_frigate_11";
		break;
		
		case "check_out_my_frigate_11":
			if(!CheckAttribute(pchar, "questTemp.SharkGoldFleet.KGBB"))
			{
				dialog.text = "Come ti dicevo, Alexus sta costruendo per me una nuova fregata. Certo, dubito che supererà la 'Fortuna' in velocità, ma non sarà poi tanto da meno. E per certe faccende servono proprio un paio di navi potenti e svelte. Forse potrei cavarmela da solo, ma due vascelli sono tutta un'altra storia.";
				link.l1 = "Bene. E che razza d'affari sarebbero questi?";
				link.l1.go = "check_out_my_frigate_12";
			}
			else
			{
				dialog.text = "Come ti dicevo, Alexus mi ha costruito di recente una nuova fregata. Certo, dubito che possa battere la 'Fortuna' in velocità, ma non sarà di certo molto inferiore. E proprio adesso ho bisogno di un paio di navi potenti, ma allo stesso tempo veloci. Potrei anche cavarmela da solo, ma in due è tutta un’altra storia.";
				link.l1 = "Bene.   E di che affare si tratta, dunque?";
				link.l1.go = "check_out_my_frigate_13";
			}
		break;
		// Фрегат Акулы не построен
		case "check_out_my_frigate_12":
			dialog.text = "È troppo presto per parlarne, perché non so ancora quando la mia nuova nave sarà varata. Alexus pare abbia dei grattacapi a procurarsi i materiali. A proposito, se ti capita l’occasione, potresti dargli una mano. Son certo che ti ricompenserà a dovere: gli ho lasciato un bell’anticipo. Quando avrà recuperato tutto, penso che nel giro d’un mese la mia nave sarà pronta. Allora ti aspetto. Ma assicurati di salire a bordo della ‘Fortuna’ e prepararla per tempo, poi il tempo sarà tiranno! Ah, e bada che gli spagnoli non abbiano voglia di vedere la tua testa su un piatto d’argento. Tutti i dettagli te li dirò poi.";
			link.l1 = "Bene, chiederò al nostro costruttore di navi di che aiuto possa aver bisogno. Poi riprenderemo la nostra conversazione, tra un mese dopo che avrò aiutato Alexus, quando tu solcherai di nuovo i mari.";
			link.l1.go = "check_out_my_frigate_14";
		break;
		
		// Фрегат Акулы построен
		case "check_out_my_frigate_13":
			dialog.text = "È troppo presto per parlarne, la mia nave non ha ancora lasciato gli scali. Devo ancora equipaggiarla. Quindi ti aspetto non prima di un mese. Ma assicurati di salire a bordo della 'Fortuna' e prepararla in anticipo, così risparmieremo tempo! Ah, e guarda che gli spagnoli non abbiano voglia di vedere la tua testa servita su un vassoio d'argento. Ti spiegherò tutto nei dettagli più avanti.";
			link.l1 = "Bene, allora riprenderemo il discorso più tardi, quando sarai di nuovo sotto vela.";
			link.l1.go = "check_out_my_frigate_14";
		break;
		
		case "check_out_my_frigate_14":
			dialog.text = "Ebbene, va bene. Ora me ne vado alla residenza, se non ti dispiace. Le faccende, come si suol dire, non aspettano.";
			link.l1 = "A presto, Squalo! Non dico addio.";
			link.l1.go = "check_out_my_frigate_15";
		break;
		
		case "check_out_my_frigate_15":
			DialogExit();
			sld = characterFromId("Dodson");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "reload", "reload3_back","SharkFrigateEnd", -1);
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		// belamour legendary edition на пару с Акулой
		case "SharkGoldFleet":
			if(sti(RealShips[sti(pchar.ship.type)].basetype) != SHIP_FRIGATE_L)
			{
				dialog.text = "La mia è pronta, e la tua? Ti avevo detto di venire sulla 'Fortuna'. Non so dove tu l’abbia lasciata, ma è una pazzia rischiare un azzardo simile su un’altra nave. Dunque t’aspetto a bordo di quella di cui s’era detto. E non tirare troppo la corda.";
				link.l1 = "Maledizione, me ne sono completamente dimenticato, lurido bastardo! Aspetta: torno subito sulla nave giusta.";
				link.l1.go = "exit";
				break;
			}
			if(GetCompanionQuantity(pchar) > 1)
			{
				dialog.text = "Charles, ti avevo detto di venire senza flotta. Per quello che devo discutere con te, navi in più non servono proprio a nulla. Porta via la tua flottiglia e torna da solo.";
				link.l1 = "Sì, me ne sono completamente dimenticato. Aspetta: torno presto, e senza una squadriglia.";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "Ah, eccoti qui, amico! Finalmente! Cominciavo quasi a preoccuparmi. La mia nave è quasi pronta. Ora l’ho mandata da Tirax: deve montarle i cannoni da trentadue, quelli presi dal galeone pesante catturato il mese scorso. L’ho già portata fino ai Turchi e ritorno, e devo dire che Alexus ha fatto un lavoro coi fiocchi. A proposito, non ho ancora scelto un nome degno per lei, anche se qualche idea ce l’ho. Vuoi aiutarmi a decidere?";
			link.l1 = "Ma certo che ti aiuto! Come chiami la nave, così solcherà il mare, vero? Che nomi hai in mente?";
			link.l1.go = "SharkGoldFleet_01";
		break;
		
		case "SharkGoldFleet_01":
			dialog.text = "Finora ho scelto tre vie.";
			link.l1 = "...";
			link.l1.go = "SharkGoldFleet_02";
		break;
		
		case "SharkGoldFleet_02":
			dialog.text = "La prima opzione è 'Fantasma'. La fregata è veloce e potente, e con quel nome, tutti gli avari da L'Avana a Cumaná tremeranno solo a sentirlo pronunciare!";
			link.l1 = "Eh già, e dovresti pure spuntare e sparire tra la nebbia così che i marinai si facciano il segno della croce, ah ah! Bel nome, mi garba.";
			link.l1.go = "SharkGoldFleet_03";
		break;
		
		case "SharkGoldFleet_03":
			dialog.text = "Anche a me piace. La seconda scelta è 'Squalo'. E allora? Perché non dare un soprannome anche alla mia nave? Così saremo omonimi, eh!";
			link.l1 = "C’è uno Squalo sulla ‘Squalo’... Ironico. Ma così tutti sapranno di chi è la nave.";
			link.l1.go = "SharkGoldFleet_04";
		break;
		
		case "SharkGoldFleet_04":
			dialog.text = "Anch’io sto più o meno così. E la terza opzione è ‘Tempesta’. Fare in modo che nessuno osi nemmeno avvicinarsi alla mia nave, ah ah ah!";
			link.l1 = "Perché potresti beccarti una scarica di palle di cannone di traverso? Eh, niente male.";
			link.l1.go = "SharkGoldFleet_05";
		break;
		
		case "SharkGoldFleet_05":
			dialog.text = "Proprio così! Ma ora non riesco a scegliere tra questi tre nomi. Dai, aiutami tu. Come preferisci.";
			link.l1 = "Propongo di chiamarla 'Fantasma'. Così tutti i mercanti isserebbero la bandiera bianca appena vi scorgono all’orizzonte!";
			link.l1.go = "SharkGoldFleet_05f";
			link.l2 = "Mi piace il nome 'Squalo'. Tutti dovrebbero sapere che questa nave non è di qualche pivello, ma del capo in persona dei Fratelli della Costa!";
			link.l2.go = "SharkGoldFleet_05a";
			link.l3 = "Penso che 'Flurry' sia un nome adatto. Qualunque guerriero, corsaro o mercante dovrebbe sapere cosa gli capiterà se decide di sfidare questa nave.";
			link.l3.go = "SharkGoldFleet_05s";
		break;
		
		case "SharkGoldFleet_05f":
			pchar.questTemp.SharkGoldFleet.KGBB = "Phantom";
			dialog.text = "Guarda te – persino i soldati inizieranno a fare lo stesso, ah! Dunque, è deciso. Tieni la brocca, amico. Beviamo alla mia nuova nave. Alla 'Fantasma!'";
			link.l1 = " Per 'Fantasma!'";
			link.l1.go = "SharkGoldFleet_06";
		break;
		
		case "SharkGoldFleet_05a":
			pchar.questTemp.SharkGoldFleet.KGBB = "Shark";
			dialog.text = "E che ci pensino tre volte prima di incrociare la mia rotta! Allora, è deciso. Tieni la tazza, compare. Beviamo alla mia nuova nave. Per la 'Squalo'!";
			link.l1 = "Per lo Squalo!";
			link.l1.go = "SharkGoldFleet_06";
		break;
		
		case "SharkGoldFleet_05s":
			pchar.questTemp.SharkGoldFleet.KGBB = "Flurry";
			dialog.text = "E se lui osa ancora provarci, una tempesta tale gli si abbatterà addosso che perfino gli uragani tropicali parran una brezza! Così sia. Tieni la tazza, compare. Beviamo alla mia nuova nave. Alla 'Burrasca!'";
			link.l1 = "Per il 'Turbine!'";
			link.l1.go = "SharkGoldFleet_06";
		break;
		
		case "SharkGoldFleet_06":
			dialog.text = "E che questa nave serva con lealtà, senza mai assaporare l'amarezza della sconfitta! Bene, ora veniamo al sodo.";
			link.l1 = "Ti ascolto con attenzione.";
			link.l1.go = "SharkGoldFleet_07";
		break;
		
		case "SharkGoldFleet_07":
			dialog.text = "Dimmi, Charles, sai cos’è la 'Flotta d’Oro'?";
			link.l1 = "Ah-ah! .. Mi stavo già strozzando col rum. Steven, non dirmi che sei su due fregate per assaltare il convoglio più armato dei Caraibi.";
			link.l1.go = "SharkGoldFleet_08";
		break;
		
		case "SharkGoldFleet_08":
			dialog.text = "Beh, no, certo che non sono uno che cerca la morte. Non andremo certo a depredare tutto il convoglio. Ma da qui possiamo arraffare qualcosina, eh.";
			link.l1 = "Steven, ti chiedo perdono, davvero, ma non sono pronto per questo. Sì, gli spagnoli ci brucerebbero vivi se ci infilassimo nella loro flotta! Vai avanti senza di me.";
			link.l1.go = "SharkGoldFleet_09";
			link.l2 = "Bene, dove non siamo svaniti... Sono pronto a farmi avanti!";
			link.l2.go = "SharkGoldFleet_11";
		break;
		
		case "SharkGoldFleet_09":
			pchar.questTemp.SharkGoldFleet = "RUinDeal";
			dialog.text = "Argh! Che peccato. Sono troppo sconsiderato senza di te. Va bene, non insisto più, ma pensaci su, d’accordo? Se mai dovessi cambiare idea, fammelo sapere, ti prego.";
			link.l1 = "Se lo faccio, allora certo. Perdona, Steven.";
			link.l1.go = "exit";
		break;
		
		case "SharkGoldFleet_10":
			dialog.text = "Imprese del genere non si mollano mai! E tu, dunque? Hai forse cambiato idea?";
			link.l1 = "No, amico, mi spiace, ma passo ancora.";
			link.l1.go = "exit";
			link.l2 = "Va bene, dove non siamo svaniti... Sono pronto a buttarmi nella mischia!";
			link.l2.go = "SharkGoldFleet_11";
		break;
		
		case "SharkGoldFleet_11":
			if(sti(RealShips[sti(pchar.ship.type)].basetype) != SHIP_FRIGATE_L)
			{
				dialog.text = "Forse tu sei pronto, ma la tua nave non lo è. Ti avevo detto di venire sulla 'Fortuna'. Non so dove l’hai lasciata, ma rischiare tutto su un’altra nave sarebbe pura follia. Dunque t’aspetto a bordo di quella su cui ci siamo messi d’accordo. E non farti prendere dalla smania.";
				link.l1 = "Maledizione, me ne sono completamente scordato, somaro! Aspetta: torno subito sulla nave giusta.";
				link.l1.go = "exit";
				break;
			}
			if(GetCompanionQuantity(pchar) > 1)
			{
				dialog.text = "Ma no: non sei pronto, Charles. Ti avevo detto di venire senza una squadra. Per l’affare che ho in mente con te, navi di troppo non servono affatto. Porta la tua flotta altrove e poi torna.";
				link.l1 = "Sì, me ne sono completamente dimenticato. Aspetta: torno presto, senza una squadriglia.";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "Mille diavoli, è proprio quello che volevo sentire! Allora, ti propongo di ghermire insieme un boccone dal convoglio. Tanta roba da spartire...";
			link.l1 = "Rubare, dici? Senza farsi beccare dalle navi di ronda?";
			link.l1.go = "SharkGoldFleet_12";
		break;
		
		case "SharkGoldFleet_12":
			dialog.text = "Esatto. Senti, come forse già sai, la 'Flotta d'Oro' si raduna a Porto Bello e da lì salpa verso L'Avana. Dopo L'Avana, intercettarla è fiato sprecato: attraversa l’Atlantico scortata da tanta canaglieria armata che solo un babbeo spererebbe di metterci sopra il naso. Durante il passaggio da Porto Bello a L’Avana la musica non cambia molto. Certo, puoi provarci, ma ti serve una squadra capace di sbriciolare fortezze come fossero noci. Però è a Porto Bello che si ritrovano bastimenti da tutta Main, e lì non sono più tanto protetti.";
			link.l1 = "Solo che adesso il tempo del passaggio e i nomi di quelle navi sono segreti stretti. Non resteremo a bighellonare nei paraggi di Porto Bello per mezzo anno ad abbordare ogni galeone spagnolo che va al porto.";
			link.l1.go = "SharkGoldFleet_13";
		break;
		
		case "SharkGoldFleet_13":
			dialog.text = "Certo che no. Da Cartagena, per esempio, le navi vanno da sole, e, come hai ben detto, solo Dio sa che razza di navi siano e quando partiranno. Ma da Caracas, vicino a una miniera spagnola e lontana da Porto Bello, le navi non sono mai proprio da sole.";
			link.l1 = "Com'è che non è del tutto solo?";
			link.l1.go = "SharkGoldFleet_14";
		break;
		
		case "SharkGoldFleet_14":
			dialog.text = "Sono riuscito a scoprire che una nave carica di merci parte da Caracas da sola o con poca scorta, ma da qualche parte alla longitudine del Golfo di Maracaibo la incontrano navi da guerra spagnole per garantirle la sicurezza fino in fondo. Dimmi, secondo te, come fanno a sapere quando e chi devono incontrare là?";
			link.l1 = "Devono aver sentito qualche voce...";
			link.l1.go = "SharkGoldFleet_15";
		break;
		
		case "SharkGoldFleet_15":
			dialog.text = "D'accordo. Prima che la nave ammiraglia salpi, una nave corriera parte da Caracas verso Porto Bello, portando notizie sul luogo e la data dell'incontro, e pure il nome del vascello spagnolo. Poi fa ritorno e riporta la conferma che la nave sarà accolta al momento e nel posto giusto. Solo dopo questo, la nostra preda con te salpa da Caracas.";
			link.l1 = "Ma se intercettiamo il corriere, la nave a Caracas non riceverà mai la conferma e non mollerà gli ormeggi. Hai qualche trovata per questo? E poi, come diamine acciufferemo il corriere stesso? Non sappiamo nemmeno quando metterà piede fuori dall’Isola.";
			link.l1.go = "SharkGoldFleet_16";
		break;
		
		case "SharkGoldFleet_16":
			dialog.text = "E qui c’è un piccolo inghippo. Gli spagnoli, si sa, per queste faccende usano spesso golette-corridore, ma è un bel rischio: troppo facile che il primo pirata incontrato li faccia sparire. Così si può aspettare una vita prima che la nave parta. Se capita l’occasione, allora affidano le istruzioni a bastimenti robusti e veloci – mercantili, per dire, o corsari che seguono la rotta giusta. \nCome se fosse una lettera sigillata. E poi, costa molto meno che mandar su una goletta-corridore apposta. E agli avidi funzionari spagnoli piace risparmiare qualche doblone mentre si riempiono le tasche, eh eh.";
			link.l1 = "Credo di capire! Devo forse diventare anch'io un mercante di tal fatta?";
			link.l1.go = "SharkGoldFleet_17";
		break;
		
		case "SharkGoldFleet_17":
			dialog.text = "Esattamente! E ci è andata bene: sono riuscito a scoprire da una fonte fidata che a Caracas stanno proprio cercando un corriere del genere per spedirlo con una lettera nelle prossime tre settimane. E tu guarda caso hai una nave potente e veloce, per giunta costruita dagli spagnoli! Procurati una licenza GVIK, così sembri più credibile – falla subito per sei mesi, compra a Caracas una carico di merce che possa rivendere con profitto a Porto Bello, poi vai dal capo locale dell’Autorità Portuale e chiedi se c’è qualcosa da trasportare lungo la rotta. \nSe l’Autorità Portuale fa domande, presentati come spagnolo. E bada bene – non ti azzardare a portare con te uno squadrone. Non dobbiamo attirare troppa attenzione, altrimenti tutta l’impresa va in malora.";
			link.l1 = "E dai documenti che mi daranno, scoprirò la data e il luogo dell’incontro tra la nave e il convoglio?";
			link.l1.go = "SharkGoldFleet_18";
		break;
		
		case "SharkGoldFleet_18":
			dialog.text = "Non è così semplice. Te lo dico io: i documenti sono sigillati. E tu non puoi aprirli da solo. Li apriranno all'autorità portuale di Porto Bello, poi scriveranno una risposta e, se sarai tanto gentile da dire che torni a Caracas, ti chiederanno di portarglieli. Anche la risposta, ovviamente, sarà sigillata.";
			link.l1 = "E come farò allora a scoprire dove e quando si terrà l’incontro?";
			link.l1.go = "SharkGoldFleet_19";
		break;
		
		case "SharkGoldFleet_19":
			dialog.text = "Dovrai far lavorare l'ingegno e sbirciare in qualche modo... Magari quando aprono i documenti a Porto Bello e scrivono la risposta. Oppure potresti semplicemente sottrarli quando ti consegnano la conferma, quella che poi dovrai portare a Caracas. Ma non è una gran trovata: da lì in poi tutto potrebbe andare a rotoli.";
			link.l1 = "È difficile, certo... Ma credo di potercela fare.";
			link.l1.go = "SharkGoldFleet_20";
		break;
		
		case "SharkGoldFleet_20":
			dialog.text = "Io, invece, riprenderò la mia nave da Marcus e ti aspetterò all’àncora al largo di Capo Santa Maria a Curaçao. Quando avrai finito, raggiungimi. Intercettiamo la nave alle coordinate indicate e poi ce la filiamo subito, al diavolo tutto il resto. Ora capisci perché servono navi potenti, ma veloci? Non ho alcuna voglia di incrociare le spade con lo squadrone militare spagnolo. Dovrai seminarli tu.";
			link.l1 = "Capisco. Allora mi muovo. Incontriamoci a Capo Santa Maria!";
			link.l1.go = "SharkGoldFleet_21";
		break;
		
		case "SharkGoldFleet_21":
			dialog.text = "Giusto, ci vediamo là. Ebbene, in bocca al lupo, compare! Che il destino favorisca i nostri affari.";
			link.l1 = "Lo spero anch’io. In ogni caso, me ne vado.";
			link.l1.go = "SharkGoldFleet_22";
		break;
		
		case "SharkGoldFleet_22":
			DialogExit();
			AddQuestRecord("SharkGoldFleet", "1");
			pchar.questTemp.SharkGoldFleet = "start";
			SetFunctionExitFromLocationCondition("SharkGoldFleetStart", pchar.location, false);
			if(!bImCasual) SetFunctionTimerCondition("SharkGoldFleet21", 0, 0, 21, false);
			if(!bImCasual) SetFunctionTimerCondition("SharkGoldFleet30", 0, 0, 30, false);
			else NewGameTip("Exploration mode: timer is disabled.");
		break;
		// провал
		case "SharkGoldFleet_23":
			dialog.text = "Maledetto Charles! Pensavo che non ti avrei mai più rivisto! Dove diavolo sei stato? Ti aspettavo dove avevamo stabilito, ma tu niente. E di te, nessuna notizia.";
			link.l1 = "Mi dispiace, Steven. Non sono riuscito a portare a termine il mio compito.";
			link.l1.go = "SharkGoldFleet_24";
		break;
		
		case "SharkGoldFleet_24":
			NextDiag.CurrentNode = "First time";
			dialog.text = "Ah, si sono persi un bel pesce... Su, non ti crucciare. La fortuna girerà alla prossima.";
			link.l1 = "Speriamo.";
			link.l1.go = "exit";
		break;
		
		case "SharkGoldFleet_25":
			if(GetCompanionQuantity(pchar) > 1)
			{
				dialog.text = pchar.name+", che diavolo? Ti avevo detto di venire senza flottiglia! Capisci: non ci serve zavorra, altrimenti tutta l’impresa va a fondo! Non so che ti sia preso, ma così non va. Spedisci subito la tua carovana dove vuoi e torna con una sola nave. Ti aspetto qui.";
				link.l1 = "Sì, ho solo pensato che fosse più probabile... Va bene, ti capisco. Aspetta qui: torno subito!";
				link.l1.go = "exit";
				NextDiag.TempNode = "SharkGoldFleet_25";
				break;
			}
			if(sti(RealShips[sti(pchar.ship.type)].basetype) != SHIP_FRIGATE_L)
			{
				dialog.text = pchar.name+", che diamine? Ti avevo detto di stare sulla 'Fortuna'! Capisci: ci servono due navi veloci e potenti, altrimenti tutta l’operazione potrebbe andare a rotoli! Non so cosa ti sia saltato in mente, ma così non va. Cambia subito quella carretta con la 'Fortuna' e torna qui. Ti aspetto.";
				link.l1 = "Sì, ho solo pensato che questa nave fosse migliore... Va bene, ho capito. Aspetta qui: torno subito!";
				link.l1.go = "exit";
				NextDiag.TempNode = "SharkGoldFleet_25";
				break;
			} 
			dialog.text = "Eccoti qua, amico mio! Allora, che ne pensi del mio bel gioiello?";
			link.l1 = "Che fregata magnifica, Steven! Non la rifiuterei mai...";
			link.l1.go = "SharkGoldFleet_26";
		break;
		
		case "SharkGoldFleet_26":
			dialog.text = "No, ora hai la 'Fortuna', ahah! Su, raccontami com’è andata.";
			if(pchar.questTemp.SharkGoldFleet == "LightVarToShark")
			{
				link.l1 = "Tutto filò liscio come l’olio: son riuscito a farmi passare per un mercante onesto e affidabile. Ho portato i documenti a Porto Bello, dove ho distratto il capo del porto per cinque minuti e mi sono riscritto data e coordinate dell’incontro tra le navi col carico e lo squadrone della marina.";
				link.l1.go = "SharkGoldFleet_27";
			}
			else
			{
				link.l1 = "Ci sono state alcune piccole complicazioni. La lettera fu spedita a Porto Bello tramite corriere. L’ho intercettata, consegnata al destinatario e addirittura ricevuto una risposta, ma il capo della dogana ha capito che non ero io colui che doveva portare i documenti. Ho dovuto farmi largo a suon di spada per scappare. Ma sono riuscito a scoprire data e coordinate dell’incontro tra la nave col carico e lo squadrone militare, e ho consegnato la risposta a Caracas, quindi la merce ci sta aspettando!";
				link.l1.go = "SharkGoldFleet_30";
			}
		break;
		
		case "SharkGoldFleet_27":
			dialog.text = "Aspetta un attimo. Hai detto 'navi'?";
			link.l1 = "Sì, Squalo! Saranno in due!";
			link.l1.go = "SharkGoldFleet_28";
		break;
		
		case "SharkGoldFleet_28":
			dialog.text = "Ah-ah-ah, sì, faremo il colpo grosso! Ebbene, il mio bestione è pronto a battezzarsi col fuoco. Ma non ha ancora assaggiato la battaglia, quindi lascia che sia tu a guidare lo scontro. Per ora, mi unirò alla tua squadra.";
			link.l1 = "Devo forse comandare Steven Dodson in persona, capo dei Fratelli della Costa? Affare fatto!";
			link.l1.go = "SharkGoldFleet_29";
		break;
		
		case "SharkGoldFleet_29":
			NextDiag.TempNode = "SharkGoldFleet_33";
			pchar.questTemp.SharkGoldFleet.talk = true;
			AddQuestRecord("SharkGoldFleet", "22");
			AddQuestUserData("SharkGoldFleet", "date", pchar.questTemp.SharkGoldFleet.Date);
			SGF_SharkCompanion();
			pchar.quest.SGF_SharkDelGroup1.win_condition.l1 = "ExitFromSea";
			pchar.quest.SGF_SharkDelGroup1.function = "SGF_SharkDelGroup";
			if(bImCasual)
			{
				pchar.GenQuest.SeaHunter2Pause = true;
				SeaHunter_Delete();
			}
			dialog.text = "Non montar troppo la testa: è solo perché combatterò sulla mia nave per la prima volta. E bada di avere ufficiali liberi per le navi preda. Perché le loro stive saranno colme, e nessuno dei miei uomini saprà governare la nave da solo... Va bene, bando alle chiacchiere. Il bottino ci aspetta!";
			link.l1 = "Proprio così! Sto andando alla mia nave.";
			link.l1.go = "exit";
		break;
		
		case "SharkGoldFleet_30":
			dialog.text = "Sì, hai ereditato... Allora dobbiamo prepararci al fatto che la squadra arriverà laggiù prima del tempo pattuito, e dovremo combattere contro tutti in una volta sola.";
			link.l1 = "Perché dici così?";
			link.l1.go = "SharkGoldFleet_31";
		break;
		
		case "SharkGoldFleet_31":
			dialog.text = "E ti spremi le meningi. A Porto Bello sanno che la nave col carico salperà di certo da Caracas, perché hai portato là la lettera di ritorno. Ma ormai ti sei scoperto, quindi faranno di tutto per impedirci d’intercettare quella nave. Scommetterei che lo squadrone arriverà prima di noi. È così che mi muoverei anch’io. Prepariamoci a una battaglia dura, niente ritirate tardive.";
			link.l1 = "Non temere, compagno. Tu ed io siamo due lupi di mare, queste tempeste non ci piegano!";
			link.l1.go = "SharkGoldFleet_32";
		break;
		
		case "SharkGoldFleet_32":
			dialog.text = "La tua verità. Ebbene, la mia bestia è pronta a battezzarsi col fuoco. Ma non ha ancora assaggiato il sangue della battaglia, quindi lascia che sia tu a guidare lo scontro. Intanto, mi unirò alla tua squadra.";
			link.l1 = "Son io a dover comandare Stephen Dodson in persona, capo dei Fratelli della Costa? Che affare!";
			link.l1.go = "SharkGoldFleet_29";
		break;
		
		case "SharkGoldFleet_33":
			NextDiag.TempNode = "SharkGoldFleet_33";
			dialog.text = "Niente tempo per ciance, "+pchar.name+"Avanti, andiamo a fare bottino!";
			link.l1 = "E che la sorte ci assista!";
			link.l1.go = "exit";
		break;
		// делим добычу на берегу
		case "SharkGoldFleet_34":
			if(makeint(pchar.questTemp.SharkGoldFleet) > 74)
			{
				dialog.text = "Mille diavoli! Gran bel lavoro, Charles! Il bottino si è rivelato molto più ricco di quanto pensassi all’inizio! Credo proprio che questa traversata sia valsa la pena.";
				link.l1 = "Sono d’accordo con te, Steven! Oggi è senz’altro il nostro giorno, per mille squali!";
				link.l1.go = "SharkGoldFleet_35";
			}
			else
			{
				if(makeint(pchar.questTemp.SharkGoldFleet) > 24)
				{
					dialog.text = "Bel lavoro, amico. Però dobbiamo ammettere che ci siamo lasciati sfuggire parecchia preda.";
					link.l1 = "Sono d’accordo, Steven, potremmo fare di meglio. Ma quel che c’è non è poi così male!";
					link.l1.go = "SharkGoldFleet_35";
				}
				else
				{
					dialog.text = "Maledizione! Era proprio una gran trovata... E invece, le spese di questa spedizione pesano più dei bottini. Charles, ti avevo dato il comando, e sei riuscito a mandare tutto in malora!";
					link.l1 = "Non dire nulla... Son dannatamente furibondo anch’io. Quanta preda ci è sfuggita di mano!..";
					link.l1.go = "SharkGoldFleet_37";
				}
			}
		break;
		
		case "SharkGoldFleet_35":
			dialog.text = "Ebbene, abbiamo fatto entrambi un buon lavoro. Io ho architettato il piano e raccolto le informazioni sul corriere, tu invece l’hai messo in pratica con destrezza. E ci siamo battuti ad armi pari per la nostra preda. Perciò ti propongo di spartirla secondo le leggi della Fratellanza della Costa: in parti uguali!";
			link.l1 = "Lo faremo!";
			link.l1.go = "SharkGoldFleet_36";
		break;
		
		case "SharkGoldFleet_36":
			dialog.text = "Ebbene, ora salpo verso Isla Tesoro. Devo rimettere in sesto la nave e festeggiare come si deve il primo viaggio riuscito sul mio nuovo vascello. Buona fortuna, compare! Sempre lieto di vederti alla mia dimora!";
			link.l1 = "Sono lieto che i nostri affari si siano rivelati così fruttuosi. Verrò senz'altro a trovarti, prima o poi. Buona fortuna!";
			link.l1.go = "SharkGoldFleet_39";
		break;
		
		case "SharkGoldFleet_37":
			dialog.text = "Va bene, tieniti tutto per te. Sempre che sia rimasto qualcosa. Di questi piccoletti non me ne importa un accidente. In fondo, è colpa mia che t'ho trascinato in questo pasticcio.";
			link.l1 = "Sì, anche colpa mia... Perdono, Steven.";
			link.l1.go = "SharkGoldFleet_38";
		break;
		
		case "SharkGoldFleet_38":
			dialog.text = "Non scusarti, ti devo ancora la vita, e non lo dimenticherò. Ora salpo per Isla Tesoro. Dobbiamo rimettere in sesto la nave e darle una lavata... Anche se, che ci sarebbe più da lavare... Buona fortuna, compare! Sarai sempre il benvenuto nella mia dimora!";
			link.l1 = "Va bene, tutto può succedere, le sconfitte capitano. L’importante è che siamo vivi. Verrò senz’altro a trovarti, compare! Buona fortuna!";
			link.l1.go = "SharkGoldFleet_39";
		break;
		
		case "SharkGoldFleet_39":
			if(makeint(pchar.questTemp.SharkGoldFleet) > 74)
			{
				AddQuestRecord("SharkGoldFleet", "34");	
				ChangeCharacterComplexReputation(pchar, "fame", 10);
				ChangeCharacterComplexReputation(pchar, "authority", 5);
				ChangeOfficersLoyality("good_all", 2);
				AddComplexSeaExpToScill(150, 150, 150, 150, 150, 150, 0);
				AddCharacterExpToSkill(pchar, "Leadership", 300);
				AddCharacterExpToSkill(PChar, "Fortune", 300);
				AddCharacterExpToSkill(PChar, "Sneak", 300);
			}
			else
			{
				if(makeint(pchar.questTemp.SharkGoldFleet) > 24)
				{
					AddQuestRecord("SharkGoldFleet", "35");
					ChangeCharacterComplexReputation(pchar, "fame", 1);
					ChangeCharacterComplexReputation(pchar, "authority", 1);
					AddComplexSeaExpToScill(50, 50, 50, 50, 50, 50, 0);
					AddCharacterExpToSkill(pchar, "Leadership", 200);
					AddCharacterExpToSkill(PChar, "Fortune", 200);
					AddCharacterExpToSkill(PChar, "Sneak", 200);
				}
				else
				{
					AddQuestRecord("SharkGoldFleet", "36");
					AddCharacterExpToSkill(pchar, "Leadership", 100);
					AddCharacterExpToSkill(PChar, "Fortune", 100);
					AddCharacterExpToSkill(PChar, "Sneak", 100);
				}
			}
			if(makeint(pchar.questTemp.SharkGoldFleet) > 24)
			{
				if(GetSquadronGoods(pchar, GOOD_GOLD)>0)
				{
					RemoveCharacterGoods(pchar, GOOD_GOLD, sti(makeint(pchar.questTemp.SharkGoldFleet.Gold)/2));
				}
				if(GetSquadronGoods(pchar, GOOD_SILVER)>0)
				{
					RemoveCharacterGoods(pchar, GOOD_SILVER, sti(makeint(pchar.questTemp.SharkGoldFleet.Silver)/2));
				}
				if(GetSquadronGoods(pchar, GOOD_SANDAL)>0)
				{
					RemoveCharacterGoods(pchar, GOOD_SANDAL, sti(makeint(pchar.questTemp.SharkGoldFleet.Sandal)/2));
				}
				if(GetSquadronGoods(pchar, GOOD_SHIPSILK)>0)
				{
					RemoveCharacterGoods(pchar, GOOD_SHIPSILK, sti(makeint(pchar.questTemp.SharkGoldFleet.Silk)/2));
				}
				if(GetSquadronGoods(pchar, GOOD_ROPES)>0)
				{
					RemoveCharacterGoods(pchar, GOOD_ROPES, sti(makeint(pchar.questTemp.SharkGoldFleet.Ropes)/2));
				}
				if(GetSquadronGoods(pchar, GOOD_OIL)>0)
				{
					RemoveCharacterGoods(pchar, GOOD_OIL, sti(makeint(pchar.questTemp.SharkGoldFleet.Gold)/2));
				}
			}
			SGF_GoodSwimReturn();
			SGF_DelAllSubAttributes(); // убираем все лишнее, чтобы не болталось
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "sea", "none", "", "", "SGF_SharkToIT", -1);
			CloseQuestHeader("SharkGoldFleet");
			DialogExit();
		break;
	}
}
