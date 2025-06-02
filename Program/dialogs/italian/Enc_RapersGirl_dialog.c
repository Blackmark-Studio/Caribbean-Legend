void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, Diag;
	int i, iRnd, iRnd1;
	string sTemp, sGems;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "exit_1":
			AddDialogExitQuest("LandEnc_RapersTalk");
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();			
		break;
		
		case "exit":
			LAi_SetCitizenTypeNoGroup(NPChar);
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
		break;

		case "Begin_1":
			LAi_RemoveCheckMinHP(npchar);
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_type_actor_Reset(sld);
			}
			dialog.text = RandPhraseSimple(""+GetSexPhrase("Capitano","Signora")+"! Per favore, sii misericordioso! Proteggimi, ti supplico!","Aiuto! "+GetSexPhrase("Sconosciuto","Giovane signora")+", salvami, ti prego!");
			link.l1 = LinkRandPhrase("Cosa è successo?","Cosa c'è?",RandPhraseSimple("Qual è il problema?","Cosa sta succedendo?"));
			link.l1.go = "Begin_11";
		break;

		case "Begin_2":
			LAi_RemoveCheckMinHP(NPChar);
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_type_actor_Reset(sld);
			}
			dialog.text = RandPhraseSimple(""+GetSexPhrase("Capitano! Capitano","Ragazza! Ragazza")+", per favore, resisti!","Tieni duro, "+GetSexPhrase("Capitano","signorina")+"! Per favore.");
			link.l1 = LinkRandPhrase("Cosa è successo?","Come va?",RandPhraseSimple("Qual è il problema?","Cosa sta succedendo?"));
			link.l1.go = "Begin_21";
		break;

		case "Begin_3":
			LAi_RemoveCheckMinHP(NPChar);
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_type_actor_Reset(sld);
			}
			dialog.text = "Oh, m"+GetSexPhrase("sorella","iss")+"! Per favore, aiuta una povera ragazza, ti supplico! Queste persone vogliono farmi qualcosa di terribile!";
			link.l1 = LinkRandPhrase("Cosa è successo?","Cosa c'è?",RandPhraseSimple("Qual è il problema?","Cosa sta succedendo?"));
			link.l1.go = "Begin_31";
		break;
		
		case "Begin_11":
			dialog.text = RandPhraseSimple("Questi malviventi stanno per violentarmi! Per tutto ciò che è buono, non lasciarli!","Per l'amor di Dio, proteggimi da questi mostri! Stanno per disonorarmi!");
			link.l1 = "Smetti di panico"+GetSexPhrase(", bellezza","")+". Cosa è successo qui?";
			link.l1.go = "exit_1";
		break;

		case "Begin_21":
			dialog.text = RandPhraseSimple("Stupratori mi stanno inseguendo!"+GetSexPhrase("Ti alzeresti in difesa dell'onore di una signora?","")+"","Capitano, "+GetSexPhrase("sii un uomo","sei anche una donna")+" non salveresti una ragazza dal disonore!");
			link.l1 = "Smetti di panico"+GetSexPhrase(", bellezza","")+". Cosa è successo qui?";
			link.l1.go = "exit_1";
		break;
		
		case "Begin_31":
			dialog.text = "Mi stanno inseguendo! I banditi! Dì loro di lasciarmi in pace!";
			link.l1 = "Smettila di panico"+GetSexPhrase(", bellezza","")+". Cosa è successo qui?";
			link.l1.go = "exit_1";
		break;
		
		case "First time":
			LAi_RemoveCheckMinHP(npchar);
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_type_actor_Reset(sld);
			}
			dialog.text = LinkRandPhrase("Aiuto! Aiuto! Mi stanno inseguendo! Salvami!","Aaah! Aiuto, "+GetSexPhrase("estraneo","signorina")+"! Salvami da questi mascalzoni!","Mostra misericordia e proteggimi da questi mascalzoni! Per favore!");
			Link.l1 = LinkRandPhrase("Cosa sta succedendo?","Che succede?","Cosa è successo?");
			Link.l1.go = "Node_2";			
		break;        

		case "Node_2":
			dialog.text = LinkRandPhrase("Loro... loro stanno per violentarmi! Per tutto ciò che è buono, non lasciare che lo facciano! Per favore!","Queste bestie... stanno pianificando qualcosa di orribile... Proteggimi da loro, per favore!","Nel nome del nostro Signore, salvami da queste bestie lussuriose! Vogliono disonorarmi!");
			Link.l1 = "Diciamo tutto, allora.";
			Link.l1.go = "exit_1";			
		break;

		case "ThanksForHelp":
			if(pchar.GenQuest.EncGirl == "Begin_11")
			{
				if(rand(1) == 0)
				{
					dialog.text = RandPhraseSimple("Grazie, "+GetSexPhrase("Capitano","signorina")+". Ero così spaventato!","Grazie per avermi salvato! Ti sono così grato!");
					link.l1 = "Bene, "+GetSexPhrase("bellezza","caro")+", calmati, è tutto nel passato.";
					link.l1.go = "Node_11";
				}
				else
				{
					dialog.text = "Oh, grazie, "+GetSexPhrase("nobile signore! Sei un vero gentiluomo!","signora! Mi avete salvato!")+"";
					link.l1 = "Non potevo fare altrimenti.";
					link.l1.go = "Node_12";
				}
			}
			if(pchar.GenQuest.EncGirl == "Begin_22")
			{
				if(rand(1) == 0)
				{
					dialog.text = "Oh, grazie, "+GetSexPhrase("nobile uomo! Sei un vero gentiluomo!","straniero! Mi hai salvato!")+"";
					link.l1 = "Non potevo fare altrimenti.";
					link.l1.go = "Node_12";	
				}
				else
				{
					dialog.text = "Cosa hai fatto? Perché li hai uccisi?! Ora mi cercheranno! Mio Dio, cosa ho fatto per meritare questo!";
					link.l1 = "Ecco la gratitudine!";
					link.l1.go = "Node_22";
				}
			}
			if(pchar.GenQuest.EncGirl == "Begin_33")
			{
				dialog.text = "Cosa hai fatto, "+GetSexPhrase("capitano","signorina")+"?! Perché li hai uccisi? Erano stati effettivamente mandati da mio padre... Oh Dio, ora mi ucciderà di sicuro...";
				link.l1 = "Ecco le notizie! E che pensavi gridando che eri inseguito dai banditi?!";
				link.l1.go = "Node_31";
			}
		break;
		
		case "Node_11":
			Diag.TempNode = "Node_1Next";
			addMoneyToCharacter(pchar, makeint((sti(pchar.rank))*25 + frand(2)*500));
			dialog.text = "Ho un po' di soldi, per favore, accettali come segno della mia gratitudine. Ora dirò a tutti, "+GetSexPhrase("che uomo buono e nobile sei","che donna buona e nobile sei")+".";
			link.l1 = "Certo che lo farai. Grazie... Ora torna semplicemente a casa.";
			link.l1.go = "exit";
			pchar.GenQuest.EncGirl = "close";
			sGlobalTemp = "Saved_CangGirl";
			Diag.CurrentNode = Diag.TempNode;
		break;
		
		case "Node_12":
			dialog.text = "Non riesco ancora a rimettermi. Potresti per favore portare "+GetSexPhrase("una signora","io")+" al insediamento di "+XI_ConvertString("Colony"+pchar.GenQuest.EncGirl.city)+"? Sai, ora mi sembra di vedere stupratori dietro ogni cespuglio.";
			link.l1 = RandPhraseSimple("Non preoccuparti così tanto, davvero... Bene, andiamo.","Sei proprio un codardo, non è vero? Va bene, ti ci porterò io.");
			link.l1.go = "Node_121Next";
			link.l2 = "Mi dispiace, cara, ma semplicemente non ho tempo, sono troppo occupato.";
			link.l2.go = "Node_3End";
		break;
						
		case "Node_22":
			dialog.text = "Pensavo che li avresti solo spaventati! Ora devi portarmi alla taverna nell'insediamento di "+XI_ConvertString("Colony"+pchar.GenQuest.EncGirl.city)+", non ho nessun altro a parte te a cui potrei chiedere aiuto.";
			link.l1 = "Oh, dannazione! Bene, andiamo. Basta non restare indietro.";
			link.l1.go = "Node_122Next";
			link.l2 = "No, è tutto, "+GetSexPhrase("bellezza","caro")+"! Ne ho avuto abbastanza di sorprese per oggi. Cerca qualcun altro per aiutarti.";
			link.l2.go = "Node_3End";
		break;
		
		case "Node_31":
			dialog.text = "E cosa dovevo fare?! Mio padre vuole che mi sposi il figlio dell'usuraio, quel molliccio... solo perché suo padre ha un mucchio di soldi nei suoi forzieri! Ma io amo un altro uomo! Portami da lui, per favore...";
			link.l1 = "Che peso che sei! Va bene, andiamo. Non posso proprio lasciarti qui, vero?.. Qual è il nome del tuo prescelto, dove dovrei portarti?";
			link.l1.go = "Node_32";
			link.l2 = "No, è tutto, "+GetSexPhrase("bellezza","caro")+"! Ne ho avuto abbastanza di sorprese per oggi. Cerca qualcun altro per aiutarti.";
			link.l2.go = "Node_3End";
		break;
		
		case "Node_32":
			pchar.GenQuest.EncGirl.sLoverId = GenerateRandomName(sti(npchar.nation), "man"); 
			dialog.text = "Il suo nome è "+pchar.GenQuest.EncGirl.sLoverId+", è un novizio. Al momento si trova nell'insediamento di "+XI_ConvertString("Colony"+pchar.GenQuest.EncGirl.city)+", ho provato a trovare un lavoro lì, ma sono tempi duri. Tutti parlano di una crisi... E ora per me non c'è più modo di tornare a casa, comunque.";
			link.l1 = "Una crisi? Ah... Per un vero pirata, una crisi è quando c'è una carovana commerciale all'orizzonte, ma non c'è vento per gonfiare le vele...";
			link.l1.go = "Node_12Next";
		break;
		
		case "Node_12Next":
			pchar.quest.LandEnc_RapersBadExit.over = "yes";
			Diag.TempNode = "Node_12End";
			Diag.CurrentNode = Diag.TempNode;
			pchar.GenQuest.EncGirl = "FindLover";
			pchar.GenQuest.EncGirl.MeetSoldiers = 2;
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			DialogExit();
		break;
		
		case "Node_121Next":
			pchar.quest.LandEnc_RapersBadExit.over = "yes";
			Diag.TempNode = "Node_253";
			pchar.GenQuest.EncGirl = "FindCoins";
			pchar.GenQuest.EncGirl.MeetSoldiers = 1;
			Diag.CurrentNode = Diag.TempNode;
			pchar.quest.EncGirl_DeliveBack.win_condition.l1 = "location";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_town";
			pchar.quest.EncGirl_DeliveBack.function = "EncGirl_DeliveBack";
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			DialogExit();
		break;
		
		case "Node_122Next":
			pchar.quest.LandEnc_RapersBadExit.over = "yes";
			Diag.TempNode = "Node_12End";
			pchar.GenQuest.EncGirl = "HorseToTavern";
			pchar.GenQuest.EncGirl.MeetSoldiers = 1;
			Diag.CurrentNode = Diag.TempNode;
			pchar.quest.EncGirl_DeliveBack.win_condition.l1 = "location";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_tavern";
			pchar.quest.EncGirl_DeliveBack.function = "EncGirl_DeliveBack";		
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			DialogExit();
		break;
		
		case "Node_12End":
			Diag.TempNode = "Node_12End";
			dialog.text = RandPhraseSimple("Sai, "+GetSexPhrase("capitano","signorina")+"? Ero così spaventato che le mie gambe sono ancora un po' tremolanti.","Oh, lo sai, ero così spaventato. È fantastico che Dio ti abbia mandato sulla mia strada.");
			link.l1 = RandPhraseSimple("Grazie a Dio sei ancora vivo.","Non prendertela a cuore. È bene che sia finita così, sai.");
			link.l1.go = "exit";
		break;
		
		case "Node_1Next":
			dialog.text = RandPhraseSimple("Grazie, "+GetSexPhrase("capitano","signorina")+", ancora una volta. Davvero, ti sono così debitore.","Grazie mille, "+GetSexPhrase("capitano","signorina")+". Non ho idea di cosa farei senza il tuo aiuto.");
			link.l1 = RandPhraseSimple("Questa dovrebbe essere una lezione per te. Bene, buona fortuna...","La prossima volta dovresti essere più attento... Ora, corri a casa, ho cose da fare.");
			link.l1.go = "Node_1End";
			link.l2 = "Come potresti essere così imprudente? Perché sei andato nella giungla da solo?";
			link.l2.go = "Node_13";
		break;
		
		case "Node_1End":
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			pchar.GenQuest.EncGirl = "close";
			sGlobalTemp = "Saved_CangGirl";
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_3End":
			Diag.TempNode = "Node_3Final";
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			pchar.GenQuest.EncGirl = "close";
			sGlobalTemp = "Saved_CangGirl";
			ChangeCharacterComplexReputation(pchar,"nobility", -3);
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
		break;
		
		case "Node_3Final":
			Diag.TempNode = "Node_3Final";
			dialog.text = RandPhraseSimple("Hai cambiato idea?","Capitano, è fantastico che tu abbia cambiato idea!");
			link.l1 = RandPhraseSimple("No-no, tesoro, passo.","Non nutrire false speranze...");
			link.l1.go = "exit";
		break;
		
		case "Node_13":
			if(pchar.GenQuest.EncGirl == "FindCoins") 
			{
				pchar.quest.LandEnc_RapersBadExit.win_condition.l1 = "ExitFromLocation";
				pchar.quest.LandEnc_RapersBadExit.win_condition.l1.location = pchar.location;
				pchar.quest.LandEnc_RapersBadExit.win_condition = "LandEnc_RapersBadExit";
			}
			pchar.GenQuest.EncGirl = "Begin_11";
			switch(sti(pchar.GenQuest.EncGirl.variant))
			{
				case 0:
					if(rand(1) == 0)
					{
						dialog.text = "Probabilmente riderai di me, ma... stavo raccogliendo una pozione d'amore... Una strega mi ha detto che c'è una radice che può aiutare nelle questioni d'amore.";
						link.l1 = "Mio Dio! Che "+GetSexPhrase("cosa stanno pensando queste donne","stavi pensando di")+"?! A quanto pare, ne hai raccolti un bel po', c'era un bel numero di pretendenti che ti inseguivano, ho avuto un bel da fare a tenerli tutti a bada. Ha-ha-ha-ha... Addio.";
						link.l1.go = "Node_1End";
					}
					else
					{
						dialog.text = "Sono solo uscito per una passeggiata per raccogliere alcune erbe e prendere un po' d'aria fresca. A quanto pare, non era il momento migliore per passeggiare.";
						link.l1 = "Che negligenza?! Grazie a Dio che sono arrivato in tempo. Beh, buona fortuna a te.";
						link.l1.go = "Node_1End";
					}
				break;
				case 1:
					dialog.text = "La mia padrona ha perso le perle della sua collana da qualche parte qui, quando era in passeggiata. Quando è tornata a casa, ha urlato contro di me e mi ha ordinato di uscire e raccoglierle. Lei ha detto, 'Non osare mostrare il tuo viso qui fino a quando non le hai raccolte tutte!', E io nemmeno so il posto esatto. Inoltre, come diavolo dovrei trovarle in questa erba alta? Le perle sono così piccole... Quindi, sto solo vagando qui senza la minima idea di cosa dovrei fare...";
					link.l1 = "E che tipo di collana era? Forse, sarebbe più facile semplicemente comprarne una nuova piuttosto che vagare nella giungla? Quante perle ha perso la tua padrona?";
					link.l1.go = "Node_131";
				break;
				case 2:
					dialog.text = "Mio padre defunto mi ha lasciato una mappa, e i suoi compagni volevano prenderla da me. Mentre era vivo, tutti tremavano di paura davanti a lui, ma appena l'ho sepolto, sono iniziati tempi difficili. Prima hanno cercato di comprare questa mappa da me, ma ho rifiutato, e così hanno iniziato a intimidirmi.";
					link.l1 = "E perché non l'hai semplicemente venduto? Cos'ha di così speciale questa mappa, che le bande di pirati la stanno cercando?";
					link.l1.go = "Node_132";
				break;
			}	
		break;
		
		case "Node_131":
			pchar.GenQuest.EncGirl.SmallCoins = rand(25) + 20;
			pchar.GenQuest.EncGirl.BigCoins = rand(15) + 5;
			dialog.text = "Quella collana era composta da perle selezionate, quelle non possono essere comprate a buon mercato. C'erano "+sti(pchar.GenQuest.EncGirl.BigCoins)+" grandi perle e "+sti(pchar.GenQuest.EncGirl.SmallCoins)+" quelli più piccoli. Se quelle perle fossero trovate, potremmo commissionare un altro collana come quella.";
			link.l1 = "Sicuramente non sarà un lavoro facile... Beh, se la tua padrona ti ha dato un ordine, allora non c'è molto che tu possa fare. Cerca di trovare le perle. Buona fortuna.";
			link.l1.go = "Node_131End";
			link.l2 = "È inutile. Sarebbe più facile trovare un ago in un pagliaio che le perle in questa erba fitta. Per non parlare del fatto che non conosci nemmeno il posto dove sono state perse le perle...";
			link.l2.go = "Node_133";
		break;
		
		case "Node_131End":
			Diag.TempNode = "Node_12End";
			pchar.GenQuest.EncGirl = "close";
			sGlobalTemp = "Saved_CangGirl";
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			pchar.quest.LandEnc_RapersBadExit.win_condition.l1 = "ExitFromLocation";
			pchar.quest.LandEnc_RapersBadExit.win_condition.l1.location = pchar.location;
			pchar.quest.LandEnc_RapersBadExit.win_condition = "LandEnc_RapersBadExit";
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_132":
			pchar.GenQuest.EncGirl.mapOwner = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1); 
			dialog.text = "Mio padre ha segnato un posto dove aveva nascosto il suo tesoro. Hai sentito parlare del famoso pirata "+GetName(NAMETYPE_ORIG,pchar.GenQuest.EncGirl.mapOwner,NAME_VOC)+"?";
			link.l1 = "No, non ne ho mai sentito parlare.";
			link.l1.go = "Node_132_1";
		break;
		
		case "Node_132_1":
			dialog.text = "Bè, "+GetName(NAMETYPE_ORIG,pchar.GenQuest.EncGirl.mapOwner,NAME_NOM)+" era mio padre. Tutti avevano paura di lui, nessuno osava dire una parola. Ora sono diventati sfacciati, naturalmente. Quando ho rifiutato di vendere loro la mappa, hanno affermato che anche loro dovevano avere la loro parte del tesoro. Volevo nascondere la mappa, ma mi hanno rintracciato comunque...";
			link.l1 = "E perché lo nasconderesti, in primo luogo? Fretta una nave e vai, rivendica il tuo tesoro. Tuo padre non lo avrebbe nascosto per niente.";
			link.l1.go = "Node_132_2";
		break;
		
		case "Node_132_2":
			dialog.text = "Più facile a dirsi che a farsi. Non ho soldi per affittare una nave, e... ho paura... Come dovrei scavare tutto, portarlo alla nave... E dove porterei il tesoro dopo? Sarei una preda facile per chiunque lungo il cammino...";
			link.l1 = "È un buon punto... Va bene, vai avanti e nascondi la tua mappa, allora. Ricorda solo di posizionarla bene.";
			link.l1.go = "Node_132_2End";
			if(GetCharacterItem(pchar, "map_full") == 0)
			{
				link.l2 = "Hmm... Probabilmente è vero. Ancora di più, avresti dovuto venderlo.";
				link.l2.go = "Node_132_3";
			}
			link.l3 = "Hai provato a trovare un compagno?";
			link.l3.go = "Node_132_8";	
		break;
		
		case "Node_132_2End":
			Diag.TempNode = "Node_12End";
			pchar.GenQuest.EncGirl = "close";
			sGlobalTemp = "Saved_CangGirl";
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_132_3":
			dialog.text = "Mi dispiace perdere una tale opportunità... Papà mi ha parlato dei tesori che aveva nascosto lì. Nessuno mi pagherebbe tanto...";
			link.l1 = "Ebbene, non venderlo a un prezzo troppo basso. E, comunque, l'oro non vale la tua vita. Per non parlare del fatto che questo è il modo più facile per te, ti basta raccogliere i tuoi soldi e liberarti di tutti i problemi...";
			link.l1.go = "Node_132_4";
		break;
		
		case "Node_132_4":
			pchar.GenQuest.EncGirl.mapPrice = 20000 + 500 * sti(pchar.rank);
			dialog.text = "Questo suona allettante... E quanto puoi offrirmi per questo?";
			link.l1 = "Non credo che possa valere più di "+sti(pchar.GenQuest.EncGirl.mapPrice)+" pesos.";
			link.l1.go = "Node_132_5";
		break;
		
		case "Node_132_5":
			if((GetSummonSkillFromName(pchar, SKILL_COMMERCE) + GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) + GetSummonSkillFromName(pchar, SKILL_FORTUNE)) > (rand(220) + 100) && (makeint(pchar.money) >= sti(pchar.GenQuest.EncGirl.mapPrice)))
			{
				dialog.text = "Eh, essere una donna non è facile... Va bene, sono d'accordo. Finalmente questo incubo sarà finito... Forse, è meglio che questa mappa sia tua,"+GetSexPhrase("un nobile gentiluomo","")+", che a quei furfanti.";
				link.l1 = "Bene. Ecco i tuoi soldi... cerca solo di non spenderli tutti in una volta.";
				link.l1.go = "Node_132_6";
			}
			else
			{
				dialog.text = "No, "+GetSexPhrase("capitano","signorina")+". Non lo venderò. Sposerò un bravo uomo e poi rivendicheremo insieme il tesoro.";
				link.l1 = "Bè, spetta a te decidere. Il tuo pezzo di carta non vale comunque di più.";
				link.l1.go = "Node_132_2End";
			}	
		break;
		
		case "Node_132_6":
			AddMoneyToCharacter(pchar, -makeint(sti(pchar.GenQuest.EncGirl.mapPrice))); 
			ref rMap = ItemsFromID("map_full"); // mitrokosta фикс пустой карты
			FillMapForTreasure(rMap);
			GiveItem2Character(pchar, "map_full");
			Diag.TempNode = "Node_12End";
			pchar.GenQuest.EncGirl = "close";
			sGlobalTemp = "Saved_CangGirl";
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_132_8":
			dialog.text = "E dove li troverò? I giovani non sono affidabili, e non si preoccupano tanto dei tesori quanto, di altre cose. E temo quelli più vecchi, tutti mi ricordano gli amici di mio padre. Così astuti e traditori, non sapresti mai cosa aspettarti da loro.";
			link.l1 = "Ah-ah-ah... Va bene, ma mi porterai con te?";
			link.l1.go = "Node_132_9";
		break;
		
		case "Node_132_9":
			dialog.text = "Tu? E andresti? Ma allora dovrai riportarmi qui, al insediamento di "+XI_ConvertString("Colony"+pchar.GenQuest.EncGirl.city)+", va bene?";
			link.l1 = "Bene, ti do la mia parola. Mostrami solo la via.";
			link.l1.go = "Node_132_10";
		break;
		
		case "Node_132_10":
			EncGirl_GenQuest_GetChestPlaceName();
			dialog.text = "Il tesoro è nascosto nella grotta su "+XI_ConvertString(pchar.GenQuest.EncGirl.islandId+"Acc")+", dobbiamo approdare a "+XI_ConvertString(pchar.GenQuest.EncGirl.shoreId+"Gen")+", il posto dove mi mostrerò... Ma non dimenticare, otterrai solo la metà!";
			link.l1 = "Va bene, non ti ingannerò, lo prometto. Seguimi e non indietreggiare.";
			link.l1.go = "Node_132_11";
		break;
		
		case "Node_132_11":
			ReOpenQuestHeader("JungleGirl");
			AddQuestRecord("JungleGirl", "4");
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
			AddQuestUserData("JungleGirl", "sPirateName", GetName( NAMETYPE_ORIG, pchar.GenQuest.EncGirl.mapOwner, NAME_GEN));
			AddQuestUserData("JungleGirl", "sTreasureLoc", XI_ConvertString(pchar.GenQuest.EncGirl.islandId));
			AddQuestUserData("JungleGirl", "sShore", XI_ConvertString(pchar.GenQuest.EncGirl.shoreId + "Gen"));
			AddQuestUserData("JungleGirl", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city));
			pchar.quest.EncGirl_Death.win_condition.l1 = "NPC_Death";
			pchar.quest.EncGirl_Death.win_condition.l1.character = npchar.id;
			pchar.quest.EncGirl_Death.function = "EncGirl_Death";
			pchar.quest.EncGirl_FindChest.win_condition.l1 = "location";
			pchar.quest.EncGirl_FindChest.win_condition.l1.location = pchar.GenQuest.EncGirl.placeId;
			pchar.quest.EncGirl_FindChest.function = "EncGirl_FindChest";
			SetFunctionExitFromLocationCondition("EncGirl_AddPassenger", pchar.location, false);
			SetFunctionLocationCondition("EncGirl_DialogAtShore", pchar.GenQuest.EncGirl.shoreId, false);
			Diag.TempNode = "Node_12End";
			pchar.GenQuest.EncGirl = "GetChest";
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_132_11_1":
			dialog.text = "Capitano, ora dobbiamo trovare la grotta.";
			link.l1 = "Bene, diamo un'occhiata adesso.";
			link.l1.go = "exit";
			Diag.TempNode = "Node_132_11_2";
			Diag.CurrentNode = Diag.TempNode;
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
		break;
		
		case "Node_132_11_2":
			Diag.TempNode = "Node_132_11_2";
			dialog.text = "Capitano, dobbiamo trovare la grotta.";
			link.l1 = "Bene, diamo un'occhiata ora.";
			link.l1.go = "exit";
		break;
		
		case "Node_132_12":
			dialog.text = "Eccolo! L'ho trovato! Proprio come diceva mio padre! Un enorme mucchio di tesoro! La metà è tua, come concordato.";
			link.l1 = "Vedi? Non è stato difficile, quindi non c'era nulla da temere.";
			link.l1.go = "Node_132_13";
		break;
		
		case "Node_132_13":
			dialog.text = "Ah-ah-ah! Sono ricco ora! Prenderai la tua parte ora?";
			link.l1 = "Immagino.";
			link.l1.go = "Node_132_15";
		break;
		
		case "Node_132_15":
			dialog.text = "Allora prendilo e per favore aiutami a portare tutte quelle cose alla nave. Ti ricordi ancora che mi hai promesso di riportarmi a casa?";
			link.l1 = "Non ho dimenticato! Certo, ti porterò.";
			link.l1.go = "Node_132_16";
		break;
		
		case "Node_132_16":
			pchar.quest.EncGirl_DeathSimple.over = "yes";
			PChar.quest.EncGirl_DialogAtShore.over = "yes";// лесник . снял прерывание  , если не с той бухты зашёл.		
			LAi_LocationDisableMonstersGen(pchar.location, false);
			chrDisableReloadToLocation = false;
			Log_Info("You have received your share of the treasure");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "icollection", 1+hrand(1));
			TakeNItems(pchar, "chest", 2+hrand(6));
			TakeNItems(pchar, "jewelry1", 30+hrand(15));
			TakeNItems(pchar, "jewelry2", 30+hrand(15));
			TakeNItems(pchar, "jewelry3", 30+hrand(15));
			TakeNItems(pchar, "jewelry4", 30+hrand(15));
			TakeNItems(pchar, "jewelry5", 30+rand(10));
			TakeNItems(pchar, "jewelry6", 10+rand(10));
			TakeNItems(pchar, "jewelry42", 20+rand(10));
			TakeNItems(pchar, "jewelry44", 30+rand(10));
			TakeNItems(pchar, "jewelry46", 50+rand(20));
			AddQuestRecord("JungleGirl", "6");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl", "sPirateName", GetName( NAMETYPE_ORIG, pchar.GenQuest.EncGirl.mapOwner, NAME_GEN));
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
			AddQuestUserData("JungleGirl", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city));		
			pchar.GenQuest.EncGirl = "ChestGetted";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1 = "location";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_town";
			pchar.quest.EncGirl_DeliveBack.function = "EncGirl_DeliveBack";
			pchar.quest.EncGirl_DeathAgain.win_condition.l1 = "NPC_Death";
			pchar.quest.EncGirl_DeathAgain.win_condition.l1.character = npchar.id;
			pchar.quest.EncGirl_DeathAgain.function = "EncGirl_DeathAgain";
			Diag.TempNode = "Node_132_17";
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			pchar.quest.EncGirl_AddPassenger.win_condition.l1 = "location";// лесник на корабль девицу. 
			pchar.quest.EncGirl_AddPassenger.win_condition.l1.location = pchar.location.from_sea;
			pchar.quest.EncGirl_AddPassenger.function = "EncGirl_AddPassenger";
		break;
		
		case "Node_132_17":
			Diag.TempNode = "Node_132_17";
			dialog.text = "Essere ricco è semplicemente fantastico! Mi sento così diverso ora."; 
			link.l1 = "Sono contento per te.";
			link.l1.go = "exit";
		break;
		
		case "Node_132_18":
			dialog.text = "Bene, capitano. Il mio viaggio è finito ora. Grazie per il tuo aiuto.";
			link.l1 = "Prego... Allora, cosa hai in mente di fare con le tue nuove ricchezze? Comprare una piantagione con schiavi?";
			link.l1.go = "Node_132_19";
		break;
		
		case "Node_132_19":
			dialog.text = "Non lo so, non ho ancora deciso. Forse, mi trasferirò in Europa...";
			link.l1 = "Bene, allora! Buona fortuna a te.";
			link.l1.go = "Node_132_20";
		break;
		
		case "Node_132_20":
			dialog.text = "Aspetta... Questo monile era tra i tesori di mio padre. Non mi serve, ma potrebbe piacerti. Per favore, accettalo come mia personale gratitudine per ciò che hai fatto per me. Questo è dalla mia parte, ah-ah-ah!";
			link.l1 = "Wow, ora questo è davvero un bel regalo. Grazie"+GetSexPhrase(", bellezza","")+". Trova un bello sposo per te, lo farai...";
			link.l1.go = "Node_132_21";
		break;
		
		case "Node_132_21":
			chrDisableReloadToLocation = false;		
			RemovePassenger(pchar, npchar);			
			GiveItem2Character(pchar, pchar.GenQuest.EncGirl.item); 
			AddQuestRecord("JungleGirl", "8");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
			CloseQuestHeader("JungleGirl");
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
            LAi_SetActorType(npchar); // отправил восвояси чтоб не стояла. лесник.
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1.0);
            pchar.quest.EncGirl_EnterToSea.over = "yes";// лесник . снял прерывание  , если не с той бухты зашёл.	
            PChar.quest.EncGirl_DialogAtShore.over = "yes";// лесник . снял прерывание  , если не с той бухты зашёл.						
		break;
		
		case "Node_133":
			dialog.text = "Ma cosa posso fare? Non posso ignorare gli ordini della mia padrona, mi scuoierebbe viva.";
			link.l1 = "Aspettami nella chiesa del insediamento di "+XI_ConvertString("Colony"+pchar.GenQuest.EncGirl.city)+", ti porterò le perle per fare una nuova collana.";
			link.l1.go = "Node_133_1";
			if(sti(pchar.money) >= 15000)
			{
				link.l2 = "Ecco. Prendi questi 15000 pesos. Dovrebbe essere più che sufficiente per selezionare le perle per la collana, o per comprarne una nuova.";
				link.l2.go = "Node_135";
			}							
		break;
		
		case "Node_133_1":
			pchar.GenQuest.EncGirl = "GetCoins";
			pchar.quest.EncGirl_Coins.win_condition.l1 = "ExitFromLocation";
			pchar.quest.EncGirl_Coins.win_condition.l1.location = pchar.location;
			pchar.quest.EncGirl_Coins.function = "EncGirl_toChurch";
			pchar.quest.EncGirl_GetCoins.win_condition.l1 = "Timer";
			pchar.quest.EncGirl_GetCoins.win_condition.l1.date.day = GetAddingDataDay(0, 0, 10);
			pchar.quest.EncGirl_GetCoins.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 10);
			pchar.quest.EncGirl_GetCoins.win_condition.l1.date.year = GetAddingDataYear(0, 0, 10);
			pchar.quest.EncGirl_GetCoins.function = "EncGirl_GenQuest_GetCoins";	
            sTemp = LAi_FindNearestFreeLocator2Pchar("reload");// лесник - девица убегает если ГГ сказал ждать в цервки
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);			
			Diag.TempNode = "Node_134"; 
			Diag.CurrentNode = Diag.TempNode;
			ReOpenQuestHeader("JungleGirl");
			AddQuestRecord("JungleGirl", "1"); 
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("","")); 
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name); 
			AddQuestUserData("JungleGirl", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city));
			AddQuestUserData("JungleGirl", "sText1", sti(pchar.GenQuest.EncGirl.BigCoins)); 
			AddQuestUserData("JungleGirl", "sText2", sti(pchar.GenQuest.EncGirl.SmallCoins)); 		
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_134":
			dialog.text = RandPhraseSimple(""+GetSexPhrase("Capitano","Giovane signora")+", sono così felice di rivederti! Sei riuscito a raccogliere le perle per la collana?","Ciao, capitano! Mi hai portato le perle? Sai, la mia padrona sta diventando così nervosa...");
			if (GetCharacterItem(pchar, "jewelry52") >= sti(pchar.GenQuest.EncGirl.BigCoins) && GetCharacterItem(pchar, "jewelry53") >= sti(pchar.GenQuest.EncGirl.SmallCoins))
			{
				link.l1 = "Sì. Ecco le tue perle. Portale alla tua padrona e dille di stare più attenta la prossima volta.";
				link.l1.go = "Node_134_1";
			}
			else
			{
				link.l1 = "Non ancora. Non è così facile, sai... Ma li porterò, aspetta solo.";
				link.l1.go = "Node_134_2";
			}	
		break;
		
		case "Node_134_1":
			TakeNItems(pchar, "jewelry52", -sti(pchar.GenQuest.EncGirl.BigCoins)); 
			TakeNItems(pchar, "jewelry53", -sti(pchar.GenQuest.EncGirl.SmallCoins)); 
			pchar.quest.EncGirl_GetCoins.over = "yes";
			pchar.quest.EncGirl_DeathSimple.over = "yes";
			dialog.text = "Oh, "+GetSexPhrase("Capitano","signorina")+", sono così felice di averti incontrato! Come segno della mia gratitudine per tutto quello che hai fatto per me, voglio darti questo monile e queste gemme. Spero davvero che tu li trovi utili.";
			link.l1 = "Caspita! Beh, grazie anche a te"+GetSexPhrase(", bellezza","")+", non me l'aspettavo... Addio, e sii felice.";
			link.l1.go = "Node_134_End";
		break;
		
		case "Node_134_2":
			dialog.text = "Oh, "+GetSexPhrase("capitano","signorina")+", conto su di te.";
			link.l1 = "...";
			link.l1.go = "exit";
			LAi_SetStayType(NPChar);
		break;
		
		case "Node_134_End":
			GiveItem2Character(pchar, pchar.GenQuest.EncGirl.item); 
			TakeNItems(pchar, "jewelry1", 15+hrand(8));
			AddQuestRecord("JungleGirl", "2");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name); 
			CloseQuestHeader("JungleGirl");
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
		break;
		
		case "Node_135":
			addMoneyToCharacter(pchar, -15000);
			ChangeCharacterComplexReputation(pchar,"nobility", 10);
			dialog.text = "Oh, "+GetSexPhrase("capitano","signorina")+", mi hai aiutato per la seconda volta oggi. Grazie mille. Non dimenticherò mai la tua gentilezza.";
			link.l1 = "Prego. Di 'ciao' alla tua padrona...";
			link.l1.go = "Node_135End";
		break;
		
		case "Node_135End":
			pchar.quest.LandEnc_RapersBadExit.over = "yes";
			NPChar.lifeDay = 0;
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();		
			AddDialogExitQuest("pchar_back_to_player");			
		break;	
		
		case "ThanksForSave":
			if (npchar.city == "Bridgetown" || npchar.city == "Charles" || npchar.city == "FortFrance" || npchar.city == "Marigo" || npchar.city == "Panama" || npchar.city == "PortRoyal" || npchar.city == "SantoDomingo" || npchar.city == "Tortuga") 
			{
				if(CheckAttribute(pchar, "GenQuest.EncGirl.Horse")) 
				{
					iRnd = 2;
					pchar.GenQuest.EncGirl.BrothelCity = true;
				}	
				else
				{	
					iRnd = 1;
				}	
			}
			else
			{
				iRnd = 1;
			}
			switch(rand(iRnd))
			{
				case 0:
					dialog.text = RandPhraseSimple("Non avresti dovuto dar loro alcun denaro. Stavano mentendo.","Non credergli. Sono bugiardi. E non avresti dovuto dar loro alcun denaro.");
					link.l1 = "Dovevo ucciderli?";
					link.l1.go = "Node_200";
				break;
				case 1:
					dialog.text = "Oh, che nobile gesto! Ho capito subito che tu eri "+GetSexPhrase("un vero gentiluomo","una nobile signora")+"! Per favore, accetta la mia più sincera gratitudine. Spero che tu non abbia creduto a quello che dicevano questi furfanti?";
					link.l1 = "Non importa. Una ragazza e una banda di monelli nella giungla, è così naturale...";
					link.l1.go = "Node_210";
					link.l2 = "Di cosa stai parlando, "+GetSexPhrase("bellezza","caro")+"? Come potrei?";
					link.l2.go = "Node_211";
				break;
				case 2:
					dialog.text = "Grazie, capitano. Mi dispiace coinvolgerti in questo spiacevole affare, ma semplicemente non avevo altra scelta.";
					link.l1 = "Beh, vedo che anche tu sei bello impantanato. Come siamo arrivati a questo?";
					link.l1.go = "Node_220";		
				break;
			}
		break;
		
		case "Node_200":
			if(rand(1) == 0)
			{
				dialog.text = "Forse... Non mi lasceranno mai in pace ora.";
				link.l1 = "Oh, dai! Basta andare a casa, non hai più nulla da temere ora.";
				link.l1.go = "Node_200End";
				link.l2 = "Caspita! Perché hai una tale avversione per gli uomini?";
				link.l2.go = "Node_201";
			}
			else
			{
				dialog.text = "Certo che no! Ma non mi lasceranno in pace, comunque. Potresti portarmi alla colonia di "+XI_ConvertString("Colony"+pchar.GenQuest.EncGirl.city)+", per favore?";
				link.l1 = "Basta tornare a casa, non ti toccheranno. Dovrebbero andare alla taverna adesso per sperperare i loro soldi facili.";
				link.l1.go = "Node_200End";
				link.l2 = RandPhraseSimple("Non preoccuparti così tanto, davvero... Bene, andiamo.","Sei un tale codardo, vero? Va bene, ti ci porterò..");
				link.l2.go = "Node_121Next";
			}
		break;
		
		case "Node_201":
			dialog.text = "Oh no, cosa stai dicendo? Conosco questi mascalzoni fin troppo bene. Sono ex compagni di mio padre. Stanno cercando di localizzare il posto dove aveva nascosto i suoi tesori.";
			link.l1 = "E qual è il problema con tuo padre?";
			link.l1.go = "Node_202";
		break;
		
		case "Node_202":
			dialog.text = "Era un tempo il capitano di una nave pirata. Di recente è morto... Tutti erano così cortesi durante il funerale, ma con il passare del tempo, lo hanno dimenticato, e poco dopo anche il loro onore e onestà. È un bene che li avessi notati. Non appena scoprono dove sono i tesori, sono spacciato.";
			link.l1 = "È una storia triste. Quindi, hai intenzione di continuare a nasconderti da loro?";
			link.l1.go = "Node_203";
		break;
		
		case "Node_203":
			dialog.text = "Non posso tenere i gioielli a casa, non ho nessuno che mi protegga. Quindi vado di notte nella grotta, quando finiscono i soldi...\nPortami, per favore, alla grotta, e ti darò i soldi che hai dato a loro ... Penso che i pirati non rischierebbero di seguirci mentre sei con me.";
			link.l1 = "Mi dispiace, cara, ma ho piani diversi. Collezionerai il tuo tesoro un'altra volta.";
			link.l1.go = "Node_200End";
			link.l2 = "Bene, andiamo, se non hai paura di me.";
			link.l2.go = "Node_204";
		break;
		
		case "Node_204":
			dialog.text = "Sai, per qualche motivo, non lo sono...";
			link.l1 = "Bene, questa è una buona cosa.";
			link.l1.go = "Node_205";
		break;
		
		case "Node_205":
			Diag.TempNode = "Node_206";
			EncGirl_GenerateChest(npchar);
			Diag.CurrentNode = Diag.TempNode;
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			DialogExit();
		break;
		
		case "Node_206":
			Diag.TempNode = "Node_206";
			dialog.text = "Capitano, mi hai promesso di portarmi alla grotta.";
			link.l1 = "Andiamo...";
			link.l1.go = "exit";
		break;
		
		case "Node_207":
			dialog.text = "Bene, capitano, ho preso quanto mi serviva. Ora possiamo tornare.";
			link.l1 = "I tuoi amici non sono nei paraggi, vedo.";
			link.l1.go = "Node_208";
		break;
		
		case "Node_208":
			dialog.text = "Grazie a Dio. Non ho bisogno di altri guai... Ecco, prendi questi lingotti... dovrebbero bastare a coprire le tue spese. Vai da solo, io prenderò una strada diversa...";
			link.l1 = "Bene, buona fortuna a te, se non hai paura.";
			link.l1.go = "Node_209";
		break;
		
		case "Node_209":
			LAi_LocationDisableMonstersGen(pchar.location, false);
			i = makeint(sti(pchar.GenQuest.EncGirl.price)/100.0);
			TakeNItems(pchar, "jewelry6", i);
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			npchar.lifeDay = 0;
			pchar.quest.EncGirl_RapersExit.win_condition.l1 = "ExitFromLocation";
			pchar.quest.EncGirl_RapersExit.win_condition.l1.location = pchar.location;
			pchar.quest.EncGirl_RapersExit.function = "EncGirl_MeetRapers";
			DialogExit();
		break;
		
		case "Node_200End":
			pchar.quest.LandEnc_RapersBadExit.over = "yes";
			AddDialogExitQuestFunction("EncGirl_GirlGoAway");
			DialogExit();
		break;
		
		case "Node_210":
			dialog.text = "Mmm, "+GetSexPhrase("capitano","signorina")+", non mi piace la tua ironia.";
			link.l1 = "Sei pronto per andare, "+GetSexPhrase("bellezza","caro")+". E faresti meglio a sbrigarti a raggiungere la città, prima che ti diano di nuovo la caccia.";
			link.l1.go = "Node_1End";
		break;
		
		case "Node_211":
			dialog.text = "Ero così agitato! Potresti per favore portarmi alla taverna nell'insediamento di "+XI_ConvertString("Colony"+pchar.GenQuest.EncGirl.city)+"? Altrimenti, temo, mi inseguiranno di nuovo.";
			link.l1 = "Forse, hai ragione. Andiamo...";
			link.l1.go = "Node_122Next";
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
		break;
		
		case "Node_220":
			dialog.text = "Oh, capitano, è una lunga storia, e non sono sicuro che la troveresti interessante. Anche se... Non potrei comunque farlo senza il tuo aiuto ora. Potresti per favore portarmi alla taverna nell'insediamento di "+XI_ConvertString("Colony"+pchar.GenQuest.EncGirl.city)+"? Ho paura che semplicemente non mi lasceranno in pace.";
			link.l1 = "Scusa, cara, non ho tempo per questo. Ho cose da fare.";
			link.l1.go = "Node_221";
			link.l2 = "Perché sei così segreto?";
			link.l2.go = "Node_222";
		break;
		
		case "Node_221":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			AddDialogExitQuestFunction("EncGirl_GirlGoAway");
			DialogExit();
		break;
		
		case "Node_222":
			dialog.text = "E come posso non essere riservato, se tutti cercano di trarre profitto dalla mia sfortuna?";
			link.l1 = "Bene, allora...";
			link.l1.go = "Node_223";
		break;
		
		case "Node_223":
			Diag.TempNode = "Node_224";
			pchar.GenQuest.EncGirl = "HorseToTavern";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1 = "location";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_tavern";
			pchar.quest.EncGirl_DeliveBack.function = "EncGirl_DeliveBack";		
			Diag.CurrentNode = Diag.TempNode;
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			DialogExit();		
		break;
		
		case "Node_224":
			dialog.text = "Capitano, mi avete promesso di portarmi alla taverna nel insediamento di "+XI_ConvertString("Colony"+pchar.GenQuest.EncGirl.city)+".";
			link.l1 = RandPhraseSimple("Mi ricordo.","Non preoccuparti, ci vediamo lì.");
			link.l1.go = "exit";
		break;
		
		case "Node_225":
			chrDisableReloadToLocation = false;
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") || CheckAttribute(pchar, "questTemp.LSC.Mary_officer"))
			{
				if (CheckAttribute(pchar, "GenQuest.EncGirl.BrothelCity") && sti(pchar.rank) > 15)
				{
					dialog.text = "C'è troppa gente lì. Andiamo in camera privata. Ho bisogno di dirti qualcosa.";
					link.l1 = LinkRandPhrase("Ho già fatto troppo per te, quindi ora ti dico addio.","Non dovresti abusare del mio favore. Ci vediamo, tesoro.","Non ho bisogno delle tue storie d'ora in poi, puoi capire tutto da solo.");
					link.l1.go = "Node_226";
					link.l2 = "Mmm, va bene. Prenderò le chiavi dal barista allora.";
					link.l2.go = "Node_227";
				}
				else
				{
					dialog.text = "Grazie mille per il tuo aiuto, capitano. Non lo dimenticherò.";
					link.l1 = "Oh, non disturbarti. Cerca solo di essere più attento in futuro.";
					link.l1.go = "Node_226_1";
				}
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.FMQP") && pchar.questTemp.FMQP == "begin") // Addon-2016 Jason, французские миниквесты (ФМК)
				{
					dialog.text = "Grazie mille per il tuo aiuto, capitano. Non lo dimenticherò.";
					link.l1 = "Oh, non disturbarti. Cerca solo di essere più attento in futuro.";
					link.l1.go = "Node_226_1";
				}
				else
				{
					dialog.text = "C'è troppa gente lì. Andiamo nella stanza privata. Ho bisogno di dirti qualcosa.";
					link.l1 = LinkRandPhrase("Ho già fatto troppo per te, quindi ora addio.","Non dovresti abusare del mio favore. Ci vediamo, tesoro.","Non ho bisogno delle tue storie d'ora in poi, puoi capire tutto da solo.");
					link.l1.go = "Node_226";
					link.l2 = "Mmm, va bene. Prenderò le chiavi dal barista allora.";
					link.l2.go = "Node_227";
				}
			}
		break;
		
		case "Node_226":
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			npchar.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();		
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_226_1":
			ChangeCharacterComplexReputation(pchar,"nobility", 3);
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			npchar.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();		
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_227":
			pchar.GenQuest.EncGirl = "EncGirl_ToTavern";
			pchar.quest.EncGirl_inRoom.win_condition.l1 = "location";
			pchar.quest.EncGirl_inRoom.win_condition.l1.location = npchar.city + "_tavern_upstairs";
			pchar.quest.EncGirl_inRoom.function = "EncGirl_SpeakInRoom";
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_228":
			if(CheckAttribute(pchar, "GenQuest.EncGirl.Horse") && CheckAttribute(pchar,"GenQuest.EncGirl.BrothelCity") && sti(pchar.rank) > 15) // душещипательная история о невинной девочке попавшей в бордель
			{
				DeleteAttribute(pchar, "GenQuest.EncGirl.BrothelCity");
				dialog.text = "Allora vuoi ancora ascoltare la mia storia?";
				link.l1 = "Mmm... Credo sia ora per me di andare. Addio!";
				link.l1.go = "Node_232";
				link.l2 = "Allora, sputalo fuori.";
				link.l2.go = "Node_233";	
			}
			else						
			{
				dialog.text = "Oh, mio nobile salvatore, finalmente posso ringraziarti in quel modo che solo una donna può ringraziare. Quando ti ho visto nella giungla, tutto è cambiato dentro di me. Ho dimenticato gli stupratori e le affilate foglie di palma che mi sferzavano sulle guance. Ho dimenticato dove correre, perché correre... Vedevo solo te. E desideravo solo te... E dopo quello che hai fatto per me...";
				link.l1 = "Caspita! Che carattere! I tuoi inseguitori sapevano sicuramente chi inseguire...";
				link.l1.go = "Node_229"; // ГГ допрыгался - щас его попросту трахнут
				link.l2 = "Ascolta, bellezza, capisco perfettamente, ma per favore, tieni a freno il tuo temperamento.";
				link.l2.go = "Node_230"; // Послал в пешее эротическое путешествие
			}
		break;
		
		case "Node_229":
			dialog.text = "Vieni da me ora, mio eroe...";
			link.l1 = "Oh, tesoro...";
			link.l1.go = "exit";
			pchar.GenQuest.EncGirl = "EncGirl_facking";
			DoQuestCheckDelay("PlaySex_1", 3.0);
		break;
		
		case "Node_230":
			dialog.text = "Oh! Come... Come osi?! Che bastardo! Una ragazza ti ha ringraziato con tutto il suo cuore e anima, e tu...";
			link.l1 = "Beh, se non avessi flirtato tanto e fatto il filo al primo uomo che hai incontrato, sicuramente avresti avuto meno problemi. Non ho più intenzione di salvare tali civettuole nella giungla...";
			link.l1.go = "Node_231";
		break;
		
		case "Node_231":
			dialog.text = "Non ho mai sentito tali parole da nessuno prima! E non le perdonerò! Ancora mi ricorderai!";
			link.l1 = "Vai già, capito? E cerca di rimetterti in sesto, a meno che tu non voglia essere salvato di nuovo...";
			link.l1.go = "Node_231_1";
		break;
		
		case "Node_231_1":
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", sTemp, "none", "", "","", -1.0);
			npchar.lifeDay = 0;
			DoQuestFunctionDelay("EncGirl_SetBerglar", 5.0);
			DialogExit();		
		break;
		
		case "Node_232":
			ChangeCharacterComplexReputation(pchar,"nobility", -3);
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			npchar.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
		break;
		
		case "Node_233":
			pchar.GenQuest.EncGirl.Parents_City = GetQuestNationsCity(sti(pchar.GenQuest.EncGirl.nation));
			dialog.text = "La mia famiglia vive nel insediamento di "+XI_ConvertString("Colony"+pchar.GenQuest.EncGirl.Parents_City)+". Sono arrivata qui per caso, sulla nave, sulla quale il mio sposo mi stava portando dai suoi genitori, ma è stata catturata dai pirati. La nave è stata portata via, e i passeggeri sono sbarcati nella baia non lontano da qui. Il mio sposo è stato ucciso durante l'abbordaggio della nave, ed io ero gravemente malata durante il passaggio attraverso la giungla\nLa padrona del bordello locale mi ha curato, e quando mi sono rimessa in piedi, ha richiesto di lavorare per ripagare il denaro speso per il trattamento. Ero una prostituta ma non piacevo alla Madame, e così la padrona mi ha venduto a dei banditi per guadagnare almeno un po' di soldi. L'altra parte della storia la conosci tu.";
			link.l1 = "Allora smetti e torna a casa! Perché permetti loro di trattarti come uno schiavo?!";
			link.l1.go = "Node_234";
		break;
		
		case "Node_234":
			dialog.text = "Non posso! Tutte le mie cose: vestiti decenti, soldi, documenti... Sono tutti nel bordello nella mia borsa da viaggio. L'ho nascosta nella sala degli incontri. E mentre sono vestita così, tutti i marinai del porto mi inseguiranno. E chi mi porterà a bordo senza documenti o soldi? E ora non posso nemmeno mostrare il mio viso in città, o sarò gettata dietro le sbarre...";
			link.l1 = "Non dovrebbe essere un problema. Andiamo. Ti accompagno a casa io stesso.";
			link.l1.go = "Node_235";
			link.l2 = "Aspetta qui. Ti porterò la tua borsa da viaggio.";
			link.l2.go = "Node_236";													
			if(sti(pchar.money) >= 5000) 
			{
				link.l3 = "A chi importano i tuoi documenti? Quanti soldi ti servono per tornare a casa?";
				link.l3.go = "Node_237";							
			}			
		break;
		
		case "Node_235":
			dialog.text = "Oh, grazie, capitano... Ma... sai, non ho nulla con cui pagarti.";
			link.l1 = "Di quale pagamento stai parlando? Andiamo prima che ci trovino...";
			link.l1.go = "Node_240";				
		break;
		
		case "Node_240":
			ReOpenQuestHeader("JungleGirl");
			AddQuestRecord("JungleGirl", "20");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.Parents_City));
			AddQuestUserData("JungleGirl", "sBrothelCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city + "Gen"));
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
		
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			OfficersReaction("bad");
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 3.0);
			pchar.quest.EncGirl_DeliveToParents.win_condition.l1 = "location";
			pchar.quest.EncGirl_DeliveToParents.win_condition.l1.location = pchar.GenQuest.EncGirl.Parents_City + "_town";
			pchar.quest.EncGirl_DeliveToParents.function = "EncGirl_DeliveToParents";
			DialogExit(); 		
		break;
		
		case "Node_236":
			dialog.text = "Oh, capitano, sai, non oserei mai chiedere...";
			link.l1 = "Non avere paura. Tornerò presto.";
			link.l1.go = "Node_239";				
		break;		
		
		case "Node_239":
			ReOpenQuestHeader("JungleGirl");
			AddQuestRecord("JungleGirl", "21");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);

			pchar.quest.EncGirl_GenerateBag.win_condition.l1 = "location";
			if(GetSummonSkillFromName(pchar, SKILL_FORTUNE) > rand(100))
			{
				pchar.GenQuest.EncGirl = "Bag_BrothelRoomUp";
				pchar.quest.EncGirl_GenerateBag.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_Brothel_room";
			}
			else
			{
				pchar.GenQuest.EncGirl = "Bag_BrothelRoom";
				pchar.quest.EncGirl_GenerateBag.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_SecBrRoom";
			}
			pchar.quest.EncGirl_GenerateBag.function = "EncGirl_GenerateLeatherBag";

			pchar.quest.EncGirl_GetBagFail.win_condition.l1 = "Timer";
			pchar.quest.EncGirl_GetBagFail.win_condition.l1.date.day = GetAddingDataDay(0, 0, 1);
			pchar.quest.EncGirl_GetBagFail.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.EncGirl_GetBagFail.win_condition.l1.date.year = GetAddingDataYear(0, 0, 1);
			pchar.quest.EncGirl_GetBagFail.function = "EncGirl_GenQuest_GetBag";
						
			pchar.quest.EncGirl_ExitRoom.win_condition.l1 = "ExitFromLocation";
			pchar.quest.EncGirl_ExitRoom.win_condition.l1.location = pchar.location;
			pchar.quest.EncGirl_ExitRoom.function = "EncGirl_ExitTavernRoom";

			AddDialogExitQuest("OpenTheDoors");
			DialogExit();
		break;
		
		case "Node_240_1":
			pchar.quest.EncGirl_GetBagFail.over = "yes";
			dialog.text = "Oh, già mi stavo preoccupando che potesse essere successo qualcosa a te.";
			if(CheckCharacterItem(pchar, "leather_bag"))
			{
				link.l1 = "Cosa potrebbe mai succedere? Ecco, prendi le tue cose.";
				link.l1.go = "Node_241";
			}	
			else
			{
				link.l1 = "Ascolta, non ho trovato nulla lì. Sei sicuro di aver lasciato la tua borsa da viaggio nella sala degli appuntamenti?";
				link.l1.go = "Node_242";			
			}	
		break;
		
		case "Node_241":
			TakeNItems(pchar, "leather_bag", -1);
			dialog.text = "Grazie, "+GetSexPhrase("nobile capitano","ragazza nobile")+". Non dimenticherò mai quello che hai fatto per me. Non ho molto, ma per favore accetta questo amuleto. Forse, è stato quel gingillo che mi ha salvato la vita durante l'attacco dei pirati.";
			link.l1 = "Grazie e buon viaggio! Addio ora...";
			link.l1.go = "Node_243";
		break;
		
		case "Node_242":
			dialog.text = "Hanno davvero trovato la mia borsa?";
			if(sti(pchar.money) >= 5000)
			{
				link.l1 = "Quanti soldi ti servono per tornare a casa?";
				link.l1.go = "Node_237";
			}
			link.l2 = "Forse l'hanno fatto. Comunque, le nostre strade si dividono qui adesso. Addio!";
			link.l2.go = "Node_244";
		break;
		
		case "Node_243":
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1.0);
			npchar.lifeDay = 0;
			TakeNItems(pchar, pchar.GenQuest.EncGirl.item, 1);
			AddQuestRecord("JungleGirl", "23");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl", "sSex1", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
			CloseQuestHeader("JungleGirl");
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
		break;
		
		case "Node_244":
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1.0);
			npchar.lifeDay = 0;
			AddQuestRecord("JungleGirl", "23");
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
			CloseQuestHeader("JungleGirl");
			ChangeCharacterComplexReputation(pchar,"nobility", -5);
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
		break;
		
		case "Node_245":
			dialog.text = "Grazie, capitano. Sai, è difficile credere che sono finalmente a casa. Per favore, vieni con me, ti presenterò ai miei genitori.";
			link.l1 = "Ascolta, "+GetSexPhrase("bellezza","caro")+", davvero non ho tempo per questo. Forse un'altra volta?";
			link.l1.go = "Node_246";
		break;
		
		case "Node_246":
			dialog.text = "Che peccato... Bene, addio allora, e che il Signore ti protegga. Non ho nulla con cui ripagarti, ma per favore accetta questo amuleto.";
			link.l1 = "Grazie! Corri a casa ora, rendi felici i tuoi genitori!";
			link.l1.go = "Node_247";
		break;
		
		case "Node_247":
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);		
			TakeNItems(pchar, pchar.GenQuest.EncGirl.item, 1);
			AddQuestRecord("JungleGirl", "24");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl","sName", pchar.GenQuest.EncGirl.name);
			AddQuestUserData("JungleGirl","sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.Parents_City));
			CloseQuestHeader("JungleGirl");
			npchar.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();			
		break;
		
		case "Node_248":
		break;
		
		case "Node_237":
			dialog.text = "Ebbene, non lo so... Forse, dovrò aspettare un passaggio. Ma non posso chiederti soldi.";
			if(makeint(pchar.money)>=5000)
			{
				link.l1 = "Capisco. Bene, prendi 5000 pesos. Dovrebbe essere sufficiente.";
				link.l1.go = "Node_237_1";
			}
			if(makeint(pchar.money)>=25000)
			{
				link.l2 = "Capisco. Bene, prendi 25000 pesos e torna a casa.";
				link.l2.go = "Node_237_2";
			}
			if(makeint(pchar.money)>=35000)
			{
				link.l3 = "Capisco. Bene, prendi 35000 pesos. Dovrebbe essere abbastanza per comprare la miglior cabina sulla nave.";
				link.l3.go = "Node_237_3";
			}
		break;
		
		case "Node_237_1":
			AddMoneyToCharacter(pchar, -5000);
			ChangeCharacterComplexReputation(pchar,"nobility", -5);
			dialog.text = "Grazie, "+GetSexPhrase("nobile capitano","nobile ragazza")+". Non dimenticherò mai quello che hai fatto per me.";
			link.l1 = "Buon viaggio, allora. Addio...";
			link.l1.go = "Node_238";
			pchar.GenQuest.EncGirl = "EncGirlFack_GetMoney";
		break;
		
		case "Node_237_2":
			AddMoneyToCharacter(pchar, -25000);
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			dialog.text = "Grazie, "+GetSexPhrase("nobile capitano","ragazza nobile")+". Non dimenticherò mai quello che hai fatto per me.";
			link.l1 = "Buon viaggio, allora. Addio...";
			link.l1.go = "Node_238";
		break;
		
		case "Node_237_3":
			AddMoneyToCharacter(pchar, -35000);
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
			dialog.text = "Grazie, "+GetSexPhrase("nobile capitano","ragazza nobile")+". Non dimenticherò mai quello che hai fatto per me.";
			link.l1 = "Buon viaggio, allora. Addio...";
			link.l1.go = "Node_238";
		break;
		
		case "Node_238":
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1.0);
			npchar.lifeDay = 0;
			if(pchar.GenQuest.EncGirl == "EncGirlFack_GetMoney") 
			{
				AddSimpleRumour(RandPhraseSimple("Have you heard? A whore was trying to sneak on board of a ship without documents, but she was caught and taken back to the brothel. They say she owed the madam quite a sum.",  
				"Have you heard? A whore without documents was caught at the port. They say she had cleaned out madam's coffers before attempting to flee from the brothel. I say, that source of filth and thievery must have been closed off long ago. Our kids are even seeing this and what can they learn from such an example?"), sti(pchar.GenQuest.EncGirl.nation), 3, 1);
			}
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
		break;
		
		case "Node_250":
			dialog.text = "Non rovinare la mia vita, capitano! Mio padre vuole che io sposi il figlio dell'usuraio, quel lurido mollica... solo perché suo padre ha un mucchio di denaro nei suoi forzieri! Beh, preferirei restare nella giungla per essere divorata dalle belve selvagge piuttosto che prendere una condanna a vita con lui!";
			link.l1 = "Qual è il problema con il tuo matrimonio, "+GetSexPhrase("bellezza","caro")+"? Trattieni colui che cerca di sposarti e sii felice. Dopo un po' di tempo, sarai felice di sposare quel mammoletto, ma potrebbe essere troppo tardi...";
			link.l1.go = "Node_251";
		break;
		
		case "Node_251":
			pchar.GenQuest.EncGirl.sLoverId = GenerateRandomName(sti(npchar.nation), "man"); 
			dialog.text = "No! No, capitano, amo "+pchar.GenQuest.EncGirl.sLoverId+" e non sposerò nessun altro uomo! E mio padre non vuole sentire nulla! Dice che "+XI_ConvertString("Colony"+pchar.GenQuest.EncGirl.city)+" è solo un visitatore qui, quindi non troverà mai un lavoro qui, ed è destinato a morire in povertà, e io con lui! E andrei con lui fino alla fine del mondo, solo per stare al suo fianco! Portami da lui, ti prego!";
			link.l1 = "Bene, andiamo. Immagino che capirò cosa fare con te...";
			link.l1.go = "Node_252";
		break;
		
		case "Node_252":
			Diag.TempNode = "Node_253";
			ReOpenQuestHeader("JungleGirl");
			AddQuestRecord("JungleGirl", "9");
			AddQuestUserData("JungleGirl","sText", pchar.GenQuest.EncGirl.FatherGen);
			AddQuestUserData("JungleGirl","sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city));
			AddQuestUserData("JungleGirl", "sLover", pchar.GenQuest.EncGirl.sLoverId); 
			pchar.GenQuest.EncGirl.MeetSoldiers = 2;
			Diag.CurrentNode = Diag.TempNode;
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			DialogExit();
		break;
		
		case "Node_253":
			Diag.TempNode = "Node_253";
			dialog.text = "Capitano, hai promesso di portarmi alla colonia di "+XI_ConvertString("Colony"+pchar.GenQuest.EncGirl.city)+".";
			link.l1 = RandPhraseSimple("Ricordo.","Non preoccuparti, ti ci porterò.");
			link.l1.go = "exit";			
		break;
		
		case "Node_260":
			chrDisableReloadToLocation = false;
			if(rand(1) == 0)
			{
				dialog.text = RandPhraseSimple("Grazie, "+GetSexPhrase("capitano","signorina")+", ancora una volta. Davvero, ti sono tanto indebitato.","Grazie mille, "+GetSexPhrase("capitano","signorina")+". Non ho idea di cosa farei senza il tuo aiuto.");
				link.l1 = RandPhraseSimple("Questa dovrebbe essere una lezione per te. Bene, in bocca al lupo...","La prossima volta dovresti fare più attenzione... Ora torna a casa, ho cose da fare.");
				link.l1.go = "Node_260End";
				link.l2 = "Come potresti essere così imprudente? Perché sei andato nella giungla da solo?";
				link.l2.go = "Node_13";
			}
			else
			{
				dialog.text = "Oh, "+GetSexPhrase("capitano","signorina")+", davvero non ho idea di come ringraziarti.";
				link.l1 = "Non è stato niente. Sempre felice di aiutare...";
				link.l1.go = "Node_261";
			}
		break;
		
		case "Node_260End":
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "","OpenTheDoors", -1.0);
			npchar.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");			
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_261":
			dialog.text = "Potresti portarmi alla taverna? Devo aspettare mia zia e riposarmi un po', questa 'avventura' ha prosciugato tutte le mie energie...";
			link.l1 = "No, "+GetSexPhrase("bellezza","caro")+", questo è certamente abbastanza per me. Ho molto da fare.";
			link.l1.go = "Node_262";
			link.l2 = ""+GetSexPhrase("Oh, donne! C'è qualcosa che possono fare senza l'aiuto di un uomo?","Perché sei così indifeso?")+"Andiamo...";
			link.l2.go = "Node_263";
		break;
		
		case "Node_262":
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", sTemp, "none", "", "", "", -1.0);
			npchar.lifeday = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
		
		case "Node_263":
			Diag.TempNode = "Node_224";
			pchar.GenQuest.EncGirl = "HorseToTavern";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1 = "location";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_tavern";
			pchar.quest.EncGirl_DeliveBack.function = "EncGirl_DeliveBack";					
			Diag.CurrentNode = Diag.TempNode;
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");			
		break;
				
		case "ThanksForHelp_1":
			Diag.TempNode = "ThanksAgain";
			if(makeint(Pchar.reputation.nobility) >= 80)
			{
				dialog.text = "Ho del denaro... Per favore, accettalo come segno della mia gratitudine!";
				Link.l1 = "Grazie. Cerca di essere più attento la prossima volta.";
				Link.l1.go = "exit";
			}
			else 
			{
				if(hrand(1) == 0)
				{
					dialog.text = "Dirò a tutti che mi hai salvato! Fate sapere a tutti, "+GetSexPhrase("che uomo coraggioso e valoroso sei","che donna coraggiosa e audace sei")+"!";
					Link.l1 = "Grazie. E ora dovresti tornare a casa.";
					Link.l1.go = "exit";
				}
				else
				{
					addMoneyToCharacter(Pchar, makeint(PChar.rank)*100);
					dialog.text = "Ho un po' di soldi... Per favore, accettali come segno della mia gratitudine!";
					Link.l1 = "Grazie. Cerca di stare più attento la prossima volta.";
					Link.l1.go = "exit";
				}
			}
		break;

		case "ThanksAgain":
            Diag.TempNode = "ThanksAgain";
            dialog.text = "Dirò a tutti che mi hai salvato! Fatelo sapere a tutti, "+GetSexPhrase("che uomo coraggioso e valoroso sei","che donna coraggiosa e valorosa sei")+"!";
			Link.l1 = "Grazie. E ora dovresti tornare a casa.";
			Link.l1.go = "exit";
		break;
	}
}
