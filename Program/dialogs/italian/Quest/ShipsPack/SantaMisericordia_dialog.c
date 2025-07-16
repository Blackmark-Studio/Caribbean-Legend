void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag, arTmp;
	int i, n;
	string sTemp, sStr;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			dialog.text = "Cosa volete?";
			link.l1 = "Niente.";
			link.l1.go = "exit";
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Alamida_church":
			dialog.text = "...e dello Spirito Santo. Amen.";
			link.l1 = "Raramente vedo soldati nelle chiese.";
			link.l1.go = "Alamida_church_2";
		break;
		
		case "Alamida_church_2":
			dialog.text = "Molti pensano che fede e spada non possano andare insieme. Ma non è forse vero che un chirurgo taglia per guarire? E un padre, non punisce forse per proteggere?";
			link.l1 = "Sembra proprio una scusa, giusto?";
			link.l1.go = "Alamida_church_3";
			link.l2 = "C’è saggezza in questo. A volte la crudeltà è necessaria.";
			link.l2.go = "Alamida_church_4";
		break;
		
		case "Alamida_church_3":
			dialog.text = "Ti sbagli. Non è una giustificazione, è comprensione. Quando ho iniziato a servire, ogni morte mi pesava... Ma poi... ho aperto gli occhi. 'La crudeltà è la forma più alta dell’amore supremo.'";
			link.l1 = "Ti lascio alle tue preghiere.";
			link.l1.go = "Alamida_church_5";
		break;
		
		case "Alamida_church_4":
			dialog.text = "Sì... sì! È proprio quello che ha detto lui, colui che mi ha instradato su questa via. 'La misericordia senza la forza è inutile, come una spada senza mano.'";
			link.l1 = "Ti lascio alle tue preghiere.";
			link.l1.go = "Alamida_church_5";
		break;
		
		case "Alamida_church_5":
			dialog.text = "Prega per tutti noi. Per ciò che facciamo... e per ciò che ancora dovremo fare.";
			link.l1 = "...";
			link.l1.go = "Alamida_exit";
		break;
		
		case "Alamida_guber":
			dialog.text = "Sette percento di ammanco. L’ultima volta era cinque. Crescono come erbacce in un giardino abbandonato...";
			link.l1 = "C’è un nuovo governatore in città, giusto?";
			link.l1.go = "Alamida_guber_2";
		break;
		
		case "Alamida_guber_2":
			dialog.text = "Cosa? Ah, no. Sua Eccellenza è laggiù, in quell’angolo. Io sono don Fernando de Alamida, ispettore reale.";
			link.l1 = "Deve essere un lavoro duro.";
			link.l1.go = "Alamida_guber_3";
		break;
		
		case "Alamida_guber_3":
			dialog.text = "Sai qual è la parte più difficile nel combattere la corruzione? I colpevoli non sono per forza persone malvagie. Hanno figli, una famiglia. E ogni volta devi ricordarti: il veleno resta veleno, anche se servito in una coppa d’oro.";
			link.l1 = "Ma si può davvero giudicare così severamente? Siamo tutti umani, giusto?";
			link.l1.go = "Alamida_guber_4";
			link.l2 = "Sei troppo tenero. Solo la galera potrà raddrizzarli.";
			link.l2.go = "Alamida_guber_5";
		break;
		
		case "Alamida_guber_4":
			dialog.text = "La misericordia verso il lupo è crudeltà verso le pecore. Così diceva... un uomo saggio. E con ogni giorno che passa, comprendo sempre di più la sua saggezza.";
			link.l1 = "Non ti trattengo più dal tuo lavoro, giusto?";
			link.l1.go = "Alamida_guber_6";
		break;
		
		case "Alamida_guber_5":
			dialog.text = "Hm. Sai, la pensavo anch’io così una volta. Ma la prigione è troppo semplice. Serve qualcosa di più... una purificazione.";
			link.l1 = "Non ti disturberò oltre mentre lavori, giusto?";
			link.l1.go = "Alamida_guber_6";
		break;
		
		case "Alamida_guber_6":
			dialog.text = "Sì. Le scartoffie non aspettano. Anche se, a volte, mi pare che dietro ogni cifra qui si nasconda il destino di qualcuno.";
			link.l1 = "...";
			link.l1.go = "Alamida_exit";
		break;
		
		case "Alamida_city":
			dialog.text = "Ascolto con attenzione, giusto?"+GetAddress_Form(NPChar)+" ? Che cosa ti ha spinto ad avvicinarti così, per strada, giusto?";
			link.l1 = "Ti distingui da tutti gli altri.";
			link.l1.go = "Alamida_city_2";
		break;
		
		case "Alamida_city_2":
			dialog.text = "Don Fernando de Alamida, ispettore reale. Sei il primo curioso che incontro oggi. Tutti si nascondono, tutti mi temono. Eppure chi è onesto non ha nulla da temere. Che cosa ci dice questo, giusto?";
			link.l1 = "Che la tua fama li spaventa?";
			link.l1.go = "Alamida_city_3";
			link.l2 = "Che di gente onesta ce n’è poca, giusto?";
			link.l2.go = "Alamida_city_4";
		break;
		
		case "Alamida_city_3":
			dialog.text = "Davvero divertente. L’ho pensato anch’io. Finché non ho capito che la paura purifica. Quando un uomo teme, diventa più sincero. Più vicino alla sua vera natura. Più vicino a Dio.";
			link.l1 = "Pensiero interessante. Devo andare. Buona giornata, don Fernando.";
			link.l1.go = "Alamida_city_5";
		break;
		
		case "Alamida_city_4":
			dialog.text = "Interessante... Hai la stessa testa di qualcuno che conoscevo. Peccato che non tutti riescano a digerire questa verità.";
			link.l1 = "Pensiero interessante. Devo andare. Buona giornata, don Fernando.";
			link.l1.go = "Alamida_city_5";
		break;
		
		case "Alamida_city_5":
			dialog.text = "Bene? Sì, forse. Purché sia giusto, giusto?";
			link.l1 = "...";
			link.l1.go = "Alamida_exit";
		break;
		
		case "Alamida_exit":
			DialogExit();
			
			sld = CharacterFromID("SantaMisericordia_clone_church");
			sld.dialog.filename = "Quest\ShipsPack\SantaMisericordia_dialog.c";
			sld.dialog.currentnode = "Alamida_repeat";
			sld = CharacterFromID("SantaMisericordia_clone_city");
			sld.dialog.filename = "Quest\ShipsPack\SantaMisericordia_dialog.c";
			sld.dialog.currentnode = "Alamida_repeat";
			sld = CharacterFromID("SantaMisericordia_clone_guber");
			sld.dialog.filename = "Quest\ShipsPack\SantaMisericordia_dialog.c";
			sld.dialog.currentnode = "Alamida_repeat";
		break;
		
		case "Alamida_repeat":
			dialog.text = "Altro, capitano?";
			link.l1 = "No, don Fernando, solo un saluto, niente di più.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Alamida_repeat";
		break;
		
		case "Alamida_abordage":
			if (startHeroType == 4)
			{
				dialog.text = "Una donzella armata di spada? Non avrei mai pensato di vedere una cosa simile in vita mia. E tu chi saresti, señorita, per osare attaccare la 'Santa Misericordia'?";
				link.l1 = "Capitano Hellen McArthur. E quello sguardo sorpreso che hai in faccia lo conosco fin troppo bene.";
				link.l1.go = "Alamida_HelenaCaptain";
			}
			else
			{
				dialog.text = "Come osi?! Attaccare la 'Santa Misericordia'?! Una nave che porta la volontà del re e... Beh. Orsù, dimmi – perché? Perché hai scelto questa follia?";
				link.l1 = "Sono una piratessa. E il tuo galeone dev’essere pieno zeppo di tesori, giusto?";
				link.l1.go = "Alamida_abordage_Gold";
				link.l2 = "Che nave magnifica... Devo averla, a ogni costo.";
				link.l2.go = "Alamida_abordage_Ship";
				link.l3 = "Sono un nemico della tua patria, don Fernando.";
				link.l3.go = "Alamida_abordage_Hater";
				link.l4 = "Così, tanto per fare. Perché no, giusto?";
				link.l4.go = "Alamida_abordage_Prikol";
			}
		break;
		
		case "Alamida_HelenaCaptain":
			dialog.text = "Come assomigli alla Vergine Maria, protettrice della nostra nave... Ugualmente bella. Ma Lei protegge i giusti, mentre tu...";
			link.l1 = "Sono qui per la tua nave. E i complimenti non ti salveranno, don Fernando.";
			link.l1.go = "Alamida_HelenaCaptain_2";
		break;
		
		case "Alamida_HelenaCaptain_2":
			dialog.text = "Che peccato. Dovrò insegnarti l’umiltà a modo mio. Con la forza, visto che non c’è altro modo.";
			link.l1 = "...";
			link.l1.go = "Alamida_abordage_SecondRound";
		break;
		
		case "Alamida_abordage_Gold":
			dialog.text = "Ah sì. Ma certo. L’oro. Sempre l’oro. Il veleno che corrode l’anima. Per lui morirete tutti.";
			link.l1 = "Non fare tanto dramma. È solo questione d’affari.";
			link.l1.go = "Alamida_abordage_Gold_2";
		break;
		
		case "Alamida_abordage_Gold_2":
			dialog.text = "Ogni moneta nella stiva è il prezzo che i peccatori han pagato per la loro redenzione. La vuoi? Allora condividi il loro destino.";
			link.l1 = "...";
			link.l1.go = "Alamida_abordage_SecondRound";
		break;
		
		case "Alamida_abordage_Ship":
			dialog.text = "In molti hanno bramato la 'Santa Misericordia'. La sua bellezza ha mandato in rovina più d’un capitano.";
			link.l1 = "Allora sarò il primo a reclamarlo.";
			link.l1.go = "Alamida_abordage_Ship_2";
		break;
		
		case "Alamida_abordage_Ship_2":
			dialog.text = "La misericordia senza forza non vale nulla, come una spada senza mano. Questa lezione la imparerai oggi.";
			link.l1 = "...";
			link.l1.go = "Alamida_abordage_SecondRound";
		break;
		
		case "Alamida_abordage_Hater":
			dialog.text = "Allora è così. Un altro che rosica per la grandezza dell’Impero.";
			link.l1 = "Quale grandezza? È la tua rigidità che tiene questo mondo incatenato.";
			link.l1.go = "Alamida_abordage_Hater_2";
		break;
		
		case "Alamida_abordage_Hater_2":
			dialog.text = "Non mentire a te stesso. La paura della Spagna ti rende più sincero. Più vicino alla tua vera natura. Lo scoprirai presto da solo.";
			link.l1 = "...";
			link.l1.go = "Alamida_abordage_SecondRound";
		break;
		
		case "Alamida_abordage_Prikol":
			dialog.text = "Pazzo. Oppure sei stato mandato da me come prova, giusto?";
			link.l1 = "Non tutto ha bisogno di una ragione, señor.";
			link.l1.go = "Alamida_abordage_Prikol_2";
		break;
		
		case "Alamida_abordage_Prikol_2":
			dialog.text = "Ha detto che tipi come te sono i più pericolosi. Ma questo mi renderà ancora più temibile in battaglia.";
			link.l1 = "...";
			link.l1.go = "Alamida_abordage_SecondRound";
		break;
		
		case "Alamida_abordage_SecondRound":
			DialogExit();
			
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			LAi_SetImmortal(npchar, false);
			LAi_SetCurHPMax(npchar);
			LAi_GetCharacterMaxEnergy(npchar);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_BRDENEMY);
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, false);
			LAi_SetCheckMinHP(npchar, 1, true, "SantaMisericordia_TrirdRound");
		break;
		
		case "Alamida_abordage_TrirdRound":
			if (startHeroType == 4)
			{
				dialog.text = "Che forza d’animo... Che volontà...";
				link.l1 = "Sorpreso, giusto?";
			}
			else
			{
				dialog.text = "Niente male. Era da tempo che non trovavo un degno avversario.";
				link.l1 = "Non ti lascerò nemmeno il tempo di riprendere fiato.";
			}
			link.l1.go = "Alamida_abordage_TrirdRound_2";
		break;
		
		case "Alamida_abordage_TrirdRound_2":
			if (startHeroType == 4)
			{
				dialog.text = "Mi avevano avvertito... di una simile prova. Di una bellezza capace di far vacillare anche la fede di un guerriero.";
				link.l1 = "Devi sempre complicare tutto così tanto, don Fernando, giusto?";
			}
			else
			{
				dialog.text = "Il Signore dona forza a chi serve una causa giusta. Però... a volte non so più bene cosa sto servendo.";
				link.l1 = "Hai dei dubbi, giusto?";
			}
			link.l1.go = "Alamida_abordage_TrirdRound_3";
		break;
		
		case "Alamida_abordage_TrirdRound_3":
			if (startHeroType == 4)
			{
				dialog.text = "Semplice? No... Ci dev’essere un senso più profondo. Questa è una prova. Non posso sbagliarmi.";
			}
			else
			{
				dialog.text = "No. Mi ha insegnato a non dubitare mai. Mai.";
			}
			link.l1 = "...";
			link.l1.go = "Alamida_abordage_TrirdRound_4";
		break;
		
		case "Alamida_abordage_TrirdRound_4":
			DialogExit();
			
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			LAi_SetImmortal(npchar, false);
			LAi_SetCurHPMax(npchar);
			LAi_GetCharacterMaxEnergy(npchar);
			npchar.MultiFighter = 2.5;
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_BRDENEMY);
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, false);
			LAi_SetCheckMinHP(npchar, 1, true, "SantaMisericordia_Molitva");
			
			PlaySound("Ambient\Tavern\glotok_001.wav");
			PlaySound("Ambient\Horror\Fear_breath_01.wav");
		break;
		
		case "Alamida_abordage_Molitva":
			dialog.text = "Aspetta... Aspetta. Hai vinto tu. Sono ferito, sto dissanguandomi. Lasciami pregare prima di morire.";
			link.l1 = "Va bene.";
			link.l1.go = "Alamida_abordage_Molitva_2";
		break;
		
		case "Alamida_abordage_Molitva_2":
			if (startHeroType == 4)
			{
				dialog.text = "Signore... perdona i miei peccati e donami forza in quest’ora di prova. Benedici le anime dei miei compagni caduti. Marinai fedeli, sono morti credendo di portare giustizia.\nPadre, ho cercato di vivere secondo i tuoi insegnamenti, di combattere l’ingiustizia. Ma tuo figlio ha macchiato l’onore della famiglia Alamida. Perdonami.\nPatria... ti ho giurato fedeltà e onore. Ma il mio fervore, la mia collera... sono diventato ciò che volevo distruggere.\nDiego... Forse ha mentito? Per tutto questo tempo... Guai a me, se è così.\nE benedici questa donna, Signore. Forse nella tua ultima misericordia l’hai mandata a me... perché potessi vedere quanto mi sono smarrito. Amen.";
			}
			else
			{
				dialog.text = "Signore... perdona i miei peccati e dammi forza in quest’ora di prova. Benedici le anime dei miei compagni caduti. Fedeli marinai, sono morti credendo di portare giustizia.\nPadre, ho cercato di vivere secondo i tuoi insegnamenti, di combattere l’ingiustizia. Ma tuo figlio ha macchiato l’onore della famiglia Alamida. Perdonami.\nPatria... ho giurato di servirti con lealtà e onore. Ma il mio fervore, la mia rabbia... sono diventato ciò che volevo combattere.\nDiego... Forse ha mentito? Per tutto questo tempo... Guai a me, se fosse così.\nSanta Vergine Maria, prega Dio per noi e concedici la tua misericordia. Amen.";
			}
			link.l1 = "Non ti riconosco, don Fernando. Sembri proprio un altro uomo adesso. E di chi stavi parlando, giusto?";
			link.l1.go = "Alamida_abordage_Molitva_3";
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "Church_Stay_1", "", 5.0);
		break;
		
		case "Alamida_BitvaEnd":
			DialogExit();
			
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "SantaMisericordia_CanLeaveCauta", 5);
		break;
			
		case "Alamida_abordage_Molitva_3":
			DialogExit();
			
			LAi_SetPlayerType(pchar);
			LAi_SetImmortal(npchar, false);
			LAi_KillCharacter(npchar);
			
			DoQuestFunctionDelay("Alamida_abordage_OfficerPodhodit", 2.0);
		break;
		
		//Элен
		case "Alamida_Helena":
			dialog.text = "Mio capitano, congratulazioni! Che battaglia furiosa. Quel capitano aveva mano ferma, eccome se l'aveva. Ma tu... tu hai dimostrato di essere persino migliore. Quanto sono fiera di te...";
			link.l1 = "Grazie, amore mio. Ti sei fatto male, giusto?";
			link.l1.go = "Alamida_Helena_2";
		break;
		
		case "Alamida_Helena_2":
			dialog.text = "No, no. Anche se, per un attimo, ho pensato che fossimo davvero nei guai – sia prima dell’abbordaggio che mentre lo facevamo. E tu, tutto bene, giusto?";
			link.l1 = "Sto bene, grazie ancora. Vai a riposarti in cabina, ti raggiungo tra poco, giusto?";
			link.l1.go = "Alamida_BitvaEnd";
		break;
		
		//Мэри
		case "Alamida_Mary":
			dialog.text = "Charles, tutto bene? Sono arrivata appena ho potuto, giusto.";
			link.l1 = "Sto bene, grazie caro. Anche se è stata davvero una faticaccia, giusto?";
			link.l1.go = "Alamida_Mary_2";
		break;
		
		case "Alamida_Mary_2":
			dialog.text = "Sono contenta! Ma... Senti, Charles? Perché abbiamo assalito questa gente? Il Signore non ci perdonerà mai, no. Questa nave... pareva un gran tempio. Quando l’ho vista, il cuore mi è balzato in petto, proprio come la prima volta che ho visto una vera chiesa, non solo nei libri. E adesso sanguina, giusto?";
			link.l1 = "Mary... Lo sai che le apparenze ingannano. Sotto la maschera della devozione si nascondono quelli che spillano monete ai poveri creduloni – proprio come te. Capisci, giusto?";
			link.l1.go = "Alamida_Mary_3";
		break;
		
		case "Alamida_Mary_3":
			dialog.text = "Io... io ti credo, Charles. Giusto? Solo... doniamo almeno un po' dell’oro che abbiamo trovato qui a chi ne ha davvero bisogno? Mi farebbe sentire meglio il cuore.";
			link.l1 = "Lo faremo, Mary. Promesso. Ora raccogli le idee e cerca di calmarti. È tutto finito, giusto?";
			link.l1.go = "Alamida_BitvaEnd";
		break;
		
		//Томми
		case "Alamida_Tommi":
			dialog.text = "Ahah, complimenti per la vittoria, capitano! Così si fa affari, davvero! Un bottino del genere su questo galeone!..";
			link.l1 = "Oggi il tuo sorriso è ancora più largo del solito, Tommy.";
			link.l1.go = "Alamida_Tommi_2";
		break;
		
		case "Alamida_Tommi_2":
			dialog.text = "Puoi scommetterci! Che bottino, eh. E che battaglia! Mi ha fatto pensare ai giorni della Rivoluzione. E poi... eh eh.";
			link.l1 = "Che c’è, Tommy? Dai, sputa il rospo, giusto?";
			link.l1.go = "Alamida_Tommi_3";
		break;
		
		case "Alamida_Tommi_3":
			dialog.text = "Hanno conciato tutta la nave come una cattedrale galleggiante. E hanno radunato oro da ogni dove. Veri papisti fanatici! Una vergogna, roba da ridere.";
			link.l1 = "Questa è una nave del tesoro, Tommy. Non una nave di preghiere.";
			link.l1.go = "Alamida_Tommi_4";
		break;
		
		case "Alamida_Tommi_4":
			dialog.text = "Non cambia molto per noi. In ogni caso, mi è piaciuto dare una bella lezione a quei don e papisti! Non li reggo proprio. Mi sono divertito un mondo oggi, ah-ah-ah!";
			link.l1 = "Non cambi mai! Giusto, puoi andare. Qui è tutto sotto controllo.";
			link.l1.go = "Alamida_BitvaEnd";
		break;
		
		//Тичингиту
		case "Alamida_Tichingitu":
			if (startHeroType == 1)
			{
				dialog.text = "Capitano Charles, abbiamo vinto la battaglia. È stata una lotta dura. Perfino Tichingitu ha faticato, e io sono uno dei migliori guerrieri del villaggio.";
				link.l1 = "Vero, amico mio. Erano davvero avversari degni.";
			}
			if (startHeroType == 2)
			{
				dialog.text = "Señor de Montoya, la nave è nostra.";
				link.l1 = "Molto bene, Tichingitu. Ho appena finito anch’io qui.";
			}
			if (startHeroType == 3)
			{
				dialog.text = "Capitano Paterson, l’ultima resistenza è stata schiacciata a bordo.";
				link.l1 = "Sei in ritardo, Tich! La prossima volta resta vicino a me. Non che non potessi cavarmela da sola, giusto...";
			}
			if (startHeroType == 4)
			{
				dialog.text = "Capitano McArthur, tutto a posto, giusto?";
				link.l1 = "Sì, Tichingitu, sto bene, grazie per avermelo chiesto. E smettila di dubitare del tuo capitano – me la sono cavata alla grande da sola, giusto?";
			}
			link.l1.go = "Alamida_Tichingitu_2";
		break;
		
		case "Alamida_Tichingitu_2":
			if (startHeroType == 1)
			{
				dialog.text = "Gli spiriti me lo dicono durante la battaglia. E mi chiedono perché li ammazzo. Ora lo domando anch’io a te. Tichingitu vede nei loro occhi che non sono ancora dei canaglie. Non ancora.";
				link.l1 = "Ah, che vuoi che ti dica? Non ho una risposta, Tichingitu.";
			}
			if (startHeroType == 2)
			{
				dialog.text = "Voglio chiederti una cosa, Capitano de Montoya.";
				link.l1 = "Ascolto, giusto?";
			}
			if (startHeroType == 3)
			{
				dialog.text = "Tichingitu vuole chiederti una cosa, Capitano William, se permetti.";
				link.l1 = "Concesso.";
			}
			if (startHeroType == 4)
			{
				dialog.text = "Non ho dubbi, ma mi preoccupo per te, capitano.";
				link.l1 = "Va bene, va bene. Vedo nei tuoi occhi che vuoi chiedermi qualcos’altro, giusto?";
			}
			link.l1.go = "Alamida_Tichingitu_3";
		break;
		
		case "Alamida_Tichingitu_3":
			if (startHeroType == 1)
			{
				dialog.text = "Hmm, come dici tu, capitano. Abbiamo finito qui, giusto?";
				link.l1 = "Sì. Darò ancora un'occhiata in giro, poi raggiungerò gli altri.";
				link.l1.go = "Alamida_BitvaEnd";
			}
			if (startHeroType == 2)
			{
				dialog.text = "Queste persone, non sono della tua stessa tribù? Non sono spagnoli? Perché hai deciso di attaccare?";
				link.l1 = "È vero. Ma anche le tribù indiane non si fanno la guerra tra loro? O non ci sono litigi e faide all'interno della stessa tribù, giusto?";
				link.l1.go = "Alamida_Tichingitu_4";
			}
			if (startHeroType == 3)
			{
				dialog.text = "Questa nave pare una chiesa. Non ti piacciono le chiese e il dio bianco, giusto?";
				link.l1 = "Affatto. Ma è solo per bellezza, capisci? Questa è una nave del tesoro. Anche se dubito che tu possa capire – ho sentito che la tua gente nemmeno sa cosa siano le tasse. Beati voi, dannati fortunati.";
				link.l1.go = "Alamida_Tichingitu_4";
			}
			if (startHeroType == 4)
			{
				dialog.text = "Sì. Sii sincero. Capitano MacArthur, perché attacchiamo questa chiesa galleggiante?";
				link.l1 = "Chiesa galleggiante, ah-ah-ah! No, no. Questa è una nave del tesoro. Hmm, vedo che non hai afferrato bene. Beh, trasportavano oro. Immagino già quanto sarà fiero Jan quando gli dirò che ho sconfitto Fernando de Alamida!";
				link.l1.go = "Alamida_Tichingitu_4";
			}
		break;
		
		case "Alamida_Tichingitu_4":
			if (startHeroType == 2)
			{
				dialog.text = "Mm, hai ragione, capitano. Ma con gli indiani succede meno che coi bianchi.";
				link.l1 = "Forse. Beh, quest'uomo stava... dandomi fastidio, giusto?";
				link.l1.go = "Alamida_Tichingitu_5";
			}
			if (startHeroType == 3)
			{
				dialog.text = "Sii onesto, Maskogi non hanno né castelli né tasse.";
				link.l1 = "Esatto. Puoi andare, ormai sei già in ritardo. Più tardi decideremo che farne di questo bellissimo galeone. Non amo queste carrette, ma diavolo, che splendore.";
				link.l1.go = "Alamida_BitvaEnd";
			}
			if (startHeroType == 4)
			{
				dialog.text = "Tichingitu è anche lui fiero di te, capitano. E ti fa i complimenti per aver vinto questa battaglia così dura.";
				link.l1 = "Grazie. Ora passiamo a spartire il bottino.";
				link.l1.go = "Alamida_BitvaEnd";
			}
		break;
		
		case "Alamida_Tichingitu_5":
			dialog.text = "Ti stai impicciando, Señor de Montoya?";
			link.l1 = "Esatto. Questo arcipelago è troppo piccolo per tutti e due. E qui sono molto più utile al nostro regno. Ricorda la Foglia di Cacao – ha fatto più danni che benefici ai suoi fratelli. Qui vale lo stesso.";
			link.l1.go = "Alamida_Tichingitu_6";
		break;
		
		case "Alamida_Tichingitu_6":
			dialog.text = "Ora capisco. Tichingitu può andare, capitano?";
			link.l1 = "Sì, vai pure. Tra poco vi raggiungo anch’io, giusto?";
			link.l1.go = "Alamida_BitvaEnd";
		break;
		
		//замечение по обнажённому оружию
		case "CitizenNotBlade":
			dialog.text = LinkRandPhrase("Ehi, che succede con tutto questo sventolare di armi?! Mettila via subito, giusto?","Ti ordino di riporre subito la tua arma!","Ehi, "+GetAddress_Form(NPChar)+", smettila di spaventare la gente! Rimetti via la tua arma.");
			link.l1 = LinkRandPhrase("Va bene, lo metto via... giusto?","Già fatto.","Come dici tu, giusto?");
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Al diavolo te!","Penso proprio che lo userò, giusto?","La metterò via quando sarà il momento giusto.");
			link.l2.go = "fight";
		break;
		
	}
} 