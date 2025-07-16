// Глэдис МакАртур - приемная мать Элен
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if(pchar.questTemp.Saga == "helena1")
			{
				dialog.text = "Ah, Capitano! Lo sai, ho confessato tutto a Helen. Non puoi capire che peso mi sono levato dal cuore!";
				link.l1 = "Hai fatto tutto ciò che dovevi, signorina McArthur. La ragazza deve conoscere la verità. E sono qui per lei.";
				link.l1.go = "Helena_hire";
			}
			else
			{
				dialog.text = "Saluti, "+pchar.name+"! Felice di vederti! Vuoi un po' di rum?";
				link.l1 = "Grazie, signorina McArthur, ma al momento sono troppo indaffarato.";
				link.l1.go = "exit";			
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "FindHelena":
			dialog.text = "Cosa desiderate, messere?";
			link.l1 = "Sei tu Gladys McArthur?";
			link.l1.go = "FindHelena_1";
		break;
		
		case "FindHelena_1":
			dialog.text = "Sì, sono io. Non mi ricordo di te, giovanotto. Avresti la bontà di spiegarmi cosa vuoi da me?";
			link.l1 = "Mi interessa la storia della scomparsa di vostra figlia, Miss McArthur. Cosa vi ha fatto pensare che sia sparita? Ho sentito dire che Helen aveva una ciurma di tutto rispetto...";
			link.l1.go = "FindHelena_2";
		break;
		
		case "FindHelena_2":
			dialog.text = "Ah, ne sono assolutamente certa! Vede, l’anniversario della morte del mio defunto marito è stato cinque giorni fa. Helen adorava suo padre, non avrebbe mai mancato questa data. Era partita solo per qualche giorno, per ricevere un carico di legno rosso dai nostri amici Miskiti.\nGli indiani rispettano e temono il nostro patrono Jan Svenson, non avrebbero mai osato farle del male. Il signor Svenson ha già parlato con loro. Il legname è stato caricato lo stesso giorno. Da allora, nessuno ha più visto Helen.";
			link.l1 = "Forse i pirati l'hanno assaltata?";
			link.l1.go = "FindHelena_3";
		break;
		
		case "FindHelena_3":
			dialog.text = "Bagianate! Saprai già che il signor Svenson è uno dei cinque baroni dei pirati e siede nel consiglio della Fratellanza della Costa. Qui nessun filibustiere può dar la caccia senza il suo permesso. Forse sarà qualche novellino però...";
			link.l1 = "E che mi dici degli spagnoli? Non è che s’è imbattuta in una pattuglia spagnola?";
			link.l1.go = "FindHelena_4";
		break;
		
		case "FindHelena_4":
			dialog.text = "Non sono tagliato per la politica, ma dicono che le miniere d’oro e d’argento da queste parti sono ormai spolpate, non rimane abbastanza bottino per rischiare le ossa di nobili hidalgo. Perciò qui se ne vedono pochi. Inoltre, gli indiani gli sono ostili.   Un incontro a caso con una pattuglia spagnola non avrebbe potuto finire male per Hélène, dal loro punto di vista non aveva fatto nulla d’illegale. La 'Rainbow' batteva bandiera olandese e tutti i documenti di Hélène erano in regola, compresa la licenza commerciale.";
			link.l1 = "È successo qualcosa di strano prima dell’ultimo suo viaggio? Magari un fatto insolito che vi è sfuggito?";
			link.l1.go = "FindHelena_5";
		break;
		
		case "FindHelena_5":
			dialog.text = "Ah, no! Grazie al cielo, qui viviamo in santa pace. Però, qualche settimana fa, Helen ha ricevuto una lettera da un altro spasimante indesiderato che la supplicava per un appuntamento. È una ragazza graziosa, ma di certo non ricca.\nCosì gli spasimanti non le mancano, anche se nessuno le va a genio e di maritarsi non ne vuole proprio sapere. Ha già preso in giro un bel po’ di gente in questo modo. Leggera e civettuola, proprio come sua madre!";
			link.l1 = "Non mi sembrate proprio il tipo di donna così, signorina McArthur...";
			link.l1.go = "FindHelena_6";
		break;
		
		case "FindHelena_6":
			dialog.text = "Cosa? Ah, lasciamo perdere, sono affranto. Di cosa parlavo? Ah, sì, la lettera. Insomma, quella lettera l’ha scritta Jimmy Higgins. Fa parte della ciurma di Jackman e abita a Maroon Town. Passa spesso da queste parti. Anche Jackman è un barone dei filibustieri, ma il signor Svenson non lo può soffrire, vai a capire perché.";
			link.l1 = "E   Hélène?";
			link.l1.go = "FindHelena_7";
		break;
		
		case "FindHelena_7":
			dialog.text = "Oh, rideva a crepapelle. Solo il giorno prima aveva ricevuto una proposta dal capitano di una corvetta inglese, e persino a lui ha dato picche. E ora questo semplice nostromo da una vecchia carretta di pirati... Ma nemmeno per sogno, la figlia di Sean McArthur pretende un marito ben più degno!";
			link.l1 = "E come si chiamava quel capitano inglese?";
			link.l1.go = "FindHelena_8";
		break;
		
		case "FindHelena_8":
			dialog.text = "Oh, come dovrei saperlo? Veri gentiluomini sono merce rara da queste parti. Scusate, non volevo offendervi. Chiedete a quel Higgins. Dovrebbe ricordarsi il nome. Jimmy voleva battersi a duello con quel capitano per Helen. I suoi compari a stento l’hanno trattenuto. Ma entrambi hanno lasciato Blueweld qualche giorno prima che Helen salpasse.";
			link.l1 = "Bene, grazie per avermi raccontato la tua storia. Farò il possibile per ritrovare la tua amata. Se scoprirò qualcosa, ti avviserò io o il signor Svenson. Spero proprio di ritrovare tua figlia viva e tutta intera.";
			link.l1.go = "FindHelena_9";
		break;
		
		case "FindHelena_9":
			dialog.text = "Vai a cercarla? Che il Signore sia con te, che ti guidi e rafforzi la tua mano! Pregherò per te! Dimmi il tuo nome, uomo d'onore?";
			link.l1 = ""+pchar.name+". "+GetFullName(pchar)+" Spero di tornare presto con buone nuove, signorina McArthur. Addio!";
			link.l1.go = "FindHelena_10";
		break;
		
		case "FindHelena_10":
			DialogExit();
			NextDiag.CurrentNode = "FindHelena_wait";
			AddQuestRecord("Saga", "1");
			pchar.questTemp.Saga = "maruntown";//идем к Джекману
			SetFunctionTimerCondition("Gladis_SetHome", 0, 0, 1, false);
			int iTime = 25-MOD_SKILL_ENEMY_RATE;
			if(bImCasual)
			{
				NewGameTip("Exploration mode: quest duration doubled");
				SetFunctionTimerCondition("Helena_AntiguaOver", 0, 0, iTime*2, false);
			}
			else SetFunctionTimerCondition("Helena_AntiguaOver", 0, 0, iTime, false);
		break;
		
		case "FindHelena_wait":
			dialog.text = "Hai qualche nuova notizia sulla mia povera figlia, "+pchar.name+"?";
			link.l1 = "Mi dispiace, signorina McArthur, per ora non ho novità da riferirle, ma non perda la speranza. Continuerò le ricerche. Anche l’assenza di cattive notizie è una buona notizia, dopotutto.";
			link.l1.go = "exit";
			NextDiag.TempNode = "FindHelena_wait";
		break;
		
		case "Helena_die":
			dialog.text = "Sei arrivato troppo tardi, Capitano. Il corpo della mia povera figlia è stato trovato sulle rive di Antigua. Signore, come l’hanno torturata prima di darle la morte! Non sono riuscito a salvare la mia bella ragazza...";
			link.l1 = "Mi dispiace. Non c'era nulla che potessi fare...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Gladis_exit";
		break;
		
		case "Gladis_exit":
			dialog.text = "Ah, giovanotto, ti prego, lasciami solo con il mio dolore...";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Gladis_exit";
		break;
		
		case "Gladis_regard":
			dialog.text = "Non so nemmeno come ringraziarti, Capitano, per aver salvato mia figlia. Mi ha raccontato ogni cosa e ammiro il tuo coraggio e il tuo onore. Prendi questi dobloni d’oro. Non sono molti, ma te li offro con tutto il cuore. E nemmeno pensare di rifiutare!";
			link.l1 = "Va bene, Gladys, non lo farò. Ma sappi che ho salvato tua figlia non per denaro e spero tu lo comprenda.";
			link.l1.go = "Gladis_regard_1";
			link.l2 = "Tieni questi soldi per te, Gladys. Ne hai più bisogno tu che io.";
			link.l2.go = "Gladis_regard_2";
			sld = characterFromId("Helena");
			LAi_SetStayType(sld);
			AddCharacterExpToSkill(pchar, "Leadership", 50);
			// открыть город
			LocatorReloadEnterDisable("SantaCatalina_town", "reload1_back", false);
			LocatorReloadEnterDisable("SantaCatalina_town", "reload2_back", false);
			LocatorReloadEnterDisable("SantaCatalina_town", "gate_back", false);
		break;
		
		case "Gladis_regard_1":
			TakeNItems(pchar, "gold_dublon", 100);
			dialog.text = "Sono lieto d’aver potuto sdebitarmi, almeno in parte, per la tua nobile azione. Le porte della mia dimora ti saranno sempre spalancate. Helen ed io saremo felici di accoglierti in qualsiasi momento.";
			link.l1 = "Vi ringrazio, signorina McArthur. Verrò a trovarvi, te ed Helen, appena se ne presenterà l’occasione.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Gladis_wait";
		break;
		
		case "Gladis_regard_2":
			dialog.text = "Ah, ti prego... Volevo solo sdebitarmi per il tuo gesto nobile. Sappi che le porte della mia dimora ti saranno sempre spalancate. Helen ed io saremo lieti di accoglierti in ogni momento.";
			link.l1 = "Grazie, signorina McArthur. Verrò a trovarvi insieme a Helen quando se ne presenterà l'occasione.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Gladis_wait";
			pchar.questTemp.Saga.Helena_friend = "true";//атрибут поведения Элен в будущем
		break;
		
		case "Gladis_wait":
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.Dialogs.Gladys")) {
				dialog.text = "Capitano, siete sempre il benvenuto nella nostra dimora! Siete venuto per Helen? Temo che si sia chiusa nella sua stanza – dev’essere sfinita dopo questi ultimi giorni. Non vi preoccupate, le capita di tanto in tanto.";
				link.l1 = "Davvero? Sei sicuro che stia bene?";
				link.l1.go = "after_drinking";
				
				DeleteAttribute(pchar, "questTemp.HelenDrinking.Dialogs.Gladys");
				break;
			}
		
			dialog.text = "Ah, Monsieur de Maure! Son sempre lieto di vedere il salvatore di mia figlia nella mia dimora. Vuoi vedere Hélène? È di sopra, nella sua stanza. Dopo aver perso la 'Rainbow' e quella sua prodigiosa salvezza, evita di uscire. Non l’ho mai vista così scombussolata prima d’ora...";
			link.l1 = "Grazie, signorina McArthur.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Gladis_wait";
		break;
		
		case "Gladis_history":
			dialog.text = "Ah, Monsieur de Maure! Son sempre lieto di accogliere in casa mia il salvatore di mia figlia. Vuoi vedere Hélène?";
			link.l1 = "No. Voglio farti alcune domande e spero davvero nella tua sincerità. La sicurezza di Helen dipende da questo. Questo anello ti dice qualcosa?";
			link.l1.go = "Gladis_history_1";
		break;
		
		case "Gladis_history_1":
			RemoveItems(pchar, "bucher_ring", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "Per mille balene! Questo è... l’anello di suo padre!";
			link.l1 = "Dal signor McArthur?";
			link.l1.go = "Gladis_history_2";
		break;
		
		case "Gladis_history_2":
			dialog.text = "No. Helen è la nostra figliastra, ma lei non lo sa; i suoi genitori sono morti, così ho deciso di prenderla come mia figlia. Sean l’ha adottata, ma nemmeno lui sapeva che non fosse davvero mia figlia.";
			link.l1 = "Allora, chi sono i suoi veri genitori?";
			link.l1.go = "Gladis_history_3";
		break;
		
		case "Gladis_history_3":
			dialog.text = "So che suo padre era un pirata detto 'Macellaio' sulla fregata 'Neptune'. L’ho visto solo due volte. E sua madre era una giovane donna bellissima, capelli rossi, vestita da uomo. Questo è tutto quel che so di lei, tranne che fu una madre pessima.\nIo non avrei mai lasciato una creatura così piccina nelle mani d’altri. Entrambi son morti in modo tragico. E il corriere promesso si presenta vent’anni dopo, ed è proprio te. Ti manda il Macellaio? È ancora tra i vivi?";
			link.l1 = "Calmatevi, signorina Gladys! Non vi è motivo di credere che il Macellaio sia tornato in vita, anche se siete la seconda persona a pensarlo. Ho incontrato poco fa un uomo che avrebbe dovuto mostrarvi questo anello...";
			link.l1.go = "Gladis_history_4";
		break;
		
		case "Gladis_history_4":
			dialog.text = "";
			link.l1 = "Un piccolo incidente gli aveva impedito di farlo in tempo e ne ha sofferto per tutta la vita, perché aveva mancato l’ultimo ordine del suo capitano. È morto non tanto tempo fa e... basta, basta con le brutte notizie. Dimmi, Gladys, la madre di Helen non ha lasciato alcun ricordo alla sua bambina? Qualche piccolo oggetto, forse?";
			link.l1.go = "Gladis_history_5";
		break;
		
		case "Gladis_history_5":
			dialog.text = "Mi ha lasciato uno strano pezzo di una vecchia mappa. Scherzava dicendo che era la sua eredità. Che diavolo potrà mai servire quel pezzo di carta? Io penso fosse solo una burla. Era tutta agitata e fuori di sé. Ma ho conservato questo 'regalo'.\nChissà... Se vuoi, posso dartelo, ma devi promettermi che un giorno mi racconterai tutta la storia.";
			link.l1 = "Certamente, signorina McArthur. Terrò questo rottame con me per un po'. Devo parlare col signor Svenson.";
			link.l1.go = "Gladis_history_6";
		break;
		
		case "Gladis_history_6":
			GiveItem2Character(pchar, "map_half_beatriss"); //половинка карты
			PlaySound("interface\important_item.wav");
			dialog.text = "Ci avete aiutati ancora una volta, Monsieur de Maure! E non so proprio come potrei ringraziarvi. Prendete almeno la pistola di mio marito. Ne andava sempre fiero e diceva che fosse una vera rarità. Da tempo ormai giace qui senza uso. Che possa servirvi! Prendetela, prendetela!";
			link.l1 = "Grazie, Gladys. Questa pistola è davvero eccellente. Ti ringrazio e ti saluto.";
			link.l1.go = "Gladis_history_7";
			if (CheckCharacterItem(pchar, "chest"))
			{
				link.l2 = "Che questa pistola serva ad Helen. Ho già abbastanza ferraglia addosso.";
				link.l2.go = "Gladis_history_8_1";
			}
		break;
		
		case "Gladis_history_7":
			DialogExit();
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "pistol5");
			pchar.questTemp.Saga = "svenson2";
			NextDiag.CurrentNode = "First time";
			DeleteAttribute(pchar, "questTemp.Saga.Helena_friend");
			AddQuestRecord("Saga", "22");
			AddCharacterExpToSkill(pchar, "Leadership", 50);
		break;
		
		case "Gladis_history_8_1":
			dialog.text = "Ma perché continui a rifiutare i miei doni? Mi fai andare in bestia...";
			link.l1 = "Penso che ora riuscirò a renderti felice. Sto per restituirti l'oro che il corriere doveva consegnarti per la degna custodia della figlia del capitano Butcher. Certo, questi dobloni non ripagheranno tutto il tuo affetto e la tua lealtà, ma ti spettano di diritto. Fanne ciò che ti pare.";
			link.l1.go = "Gladis_history_8";
		break;
		
		case "Gladis_history_8":
			dialog.text = "Ah, Capitano! Non so proprio cosa dire... Mai avrei pensato che uomini così... d’onore esistessero davvero! Vai da mia figlia e portale queste buone nuove!";
			link.l1 = "Sto arrivando, signorina McArthur.";
			link.l1.go = "Gladis_history_9";
		break;
		
		case "Gladis_history_9":
			DialogExit();
			RemoveItems(pchar, "chest", 1);
			pchar.questTemp.Saga = "svenson2";
			NextDiag.CurrentNode = "First time";
			AddQuestRecord("Saga", "22");
			sld = characterFromId("Helena");
			GiveItem2Character(sld, "pistol5");
			EquipCharacterbyItem(sld, "pistol5");
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			
			pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) + 1;
		break;
		
		case "Helena_hire":
			dialog.text = "Sei serio? Che vuoi dire?";
			link.l1 = "Su richiesta del signor Svenson, accoglierò Helen a bordo della mia nave come ufficiale. La sua vita è appesa a un filo. Finché io e Jan ci occupiamo di questa faccenda, Helen avrà bisogno di una protezione di ferro. Spero di esserne all’altezza.";
			link.l1.go = "Helena_hire_1";
		break;
		
		case "Helena_hire_1":
			dialog.text = "Ah, che meraviglia! Non avrei mai osato chiederti questo di persona. Sarà la miglior protezione per la mia ragazza. Helen sarà felicissima di tornare a solcare il mare!";
			link.l1 = "Grazie per il complimento, signorina McArthur. Ora devo incontrare la vostra... figlioccia.";
			link.l1.go = "exit";
			LocatorReloadEnterDisable("SantaCatalina_houseSp3", "reload2", false);//открыть спальню Элен
			sld = characterFromId("Helena");
			sld.dialog.currentnode = "Helena_hire";
			pchar.questTemp.Saga = "helena2";
		break;
		
		case "saw_sex":
			dialog.text = "Oh, Dio! La mia piccola!";
			link.l1 = "Gladys, non sai bussare?!";
			link.l1.go = "saw_sex_1";
		break;
		
		case "saw_sex_1":
			dialog.text = "Oh, perdonatemi, giovani! Me ne vado! Helen, ricorda ciò che ti ho detto!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveGladysTalk");
		break;
		
		case "after_drinking":
			dialog.text = "Penso che stavolta si sia solo sfiancata dal troppo lavoro. Mi ha raccontato tutto, Capitano! Grazie per averla aiutata a scegliere una nuova nave ieri!";
			link.l1 = "Eh? Mh, di nulla. Addio, signora MacArthur.";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "Gladis_wait";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}
