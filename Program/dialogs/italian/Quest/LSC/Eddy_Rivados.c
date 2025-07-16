// лидер клана ривадос - Чёрный Эдди
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
			dialog.text = "Che ci fai sul territorio dei Rivados, uomo bianco?";
			link.l1 = "Sto solo facendo conoscenza con la gente del posto. Perdonami se ti ho dato disturbo.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "Friend":
			dialog.text = "Sono lieto di accogliere un amico dei Rivados e un uomo d’onore! Chimiset mi ha raccontato ciò che hai fatto per lui. Tutti noi Rivados, me compreso, ti siamo debitori ora. Permettimi di presentarmi: Edward Black, detto anche Eddie il Nero, capo della banda dei Rivados.";
			link.l1 = ""+GetFullName(pchar)+"Anche se credo che Chimiset t’abbia già parlato di me. Aveva promesso di raccontarti...";
			link.l1.go = "Friend_1";
		break;
		
		case "Friend_1":
			dialog.text = "E così è stato. Ora puoi visitare le nostre navi liberamente. Le sentinelle non ti fermeranno e saremo lieti di vederti. Fa' attenzione coi Narvali, avranno già saputo che hai salvato Chimiset, e questo non gli piacerà, essendo nostri nemici.";
			link.l1 = "Ci rifletterò su. Grazie per l’accoglienza calorosa, Eddie! Ora, se non ti dispiace, vorrei parlare con Chimiset.";
			link.l1.go = "Friend_2";
		break;
		
		case "Friend_2":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "goto", "goto1", "LSC_EddyStay", -1);
			AddSimpleRumourCityTip("They say that you are a close friend of Black Eddie, the head of Rivados. How did you do this?", "LostShipsCity", 10, 1, "LSC", "");
			AddSimpleRumourCityTip("Rivados claim you as their friend. How'd you do it?", "LostShipsCity", 10, 1, "LSC", "");
			AddSimpleRumourCityTip("They say that the Narwhals have a price on your head. Are you scared?", "LostShipsCity", 10, 1, "LSC", "");
		break;
		
		// --> информационный блок
		case "Total_info": // стал другом
			if (pchar.questTemp.LSC == "return" && !CheckAttribute(npchar, "quest.return_isl"))
			{
				dialog.text = "Fratello bianco? Vivo? Ne sono lieto! Allora, i Narvali hanno mentito quando dissero a tutti che eri affogato...";
				link.l1 = "Sono lieto di vederti anch’io, Eddie. Le voci sulla mia morte erano solo frottole.";
				link.l1.go = "exit";
				npchar.quest.return_isl = "true";
				break;
			}
			dialog.text = "Felice di vederti, "+pchar.name+"   Qualche novità?";
			if (!CheckAttribute(npchar, "quest.natan"))
			{
				link.l1 = "Eddie, conosci forse un uomo di nome Nathaniel Hawk? Deve trovarsi qui, per quanto ne so.";
				link.l1.go = "natan";
			}
			if (!CheckAttribute(npchar, "quest.rivados"))
			{
				link.l2 = "Dimmi di più sulla banda dei Rivados.";
				link.l2.go = "rivados";
			}
			link.l9 = "Niente di che, davvero. Volevo solo salutarti.";
			link.l9.go = "exit";
		break;
		
		case "natan":
			dialog.text = "Nathaniel Hawk? No, non conosco quest’uomo. Non si trova né sulle navi dei Rivados, né in territorio neutrale. Dei Narvali invece non posso dir lo stesso, da loro non ci spingiamo mai.";
			link.l1 = "Capisco...";
			link.l1.go = "exit";
			npchar.quest.natan = "true";
			NextDiag.TempNode = "Total_info";
		break;
		
		case "rivados":
			dialog.text = "La banda dei Rivados fu fondata molti anni fa. Fu il primo clan di questa Città delle Navi Abbandonate. Più di cinquant’anni or sono, la spedizione dell’Ammiraglio Betancourt salpò dalla costa occidentale d’Africa con alcune grandi navi negriere. Le stive del Tartarus erano cariche di centinaia di schiavi neri destinati alle piantagioni dei Caraibi. Tra quegli schiavi c’era un uomo chiamato Pedro Rivados, che alcuni preti portoghesi avevano istruito nelle arti della lettura e della scrittura.\nRiuscì a liberare alcune decine di compagni dalle catene e diede inizio a una rivolta. Ahimè, gli altri schiavi non gli si unirono. L’insurrezione fu sedata. I negrieri legarono mani e piedi a Rivados e lo lasciarono nella stiva a morire di fame e sete. Dopo pochi giorni, però, il tempo girò al peggio e la squadra di Betancourt fu travolta da una tempesta furiosa.\nDopo giorni di lotta con l’oceano, solo la ‘San Augustine’ e il ‘Tartarus’, le uniche due navi ancora intatte, finirono intrappolate nel mezzo di quest’Isola. In quegli eventi morirono molti uomini, neri e bianchi, ma molti altri sopravvissero. Gli ex schiavi iniziarono una nuova vita insieme e si chiamarono Rivados in onore di Pedro Rivados, il liberatore.";
			link.l1 = "Una storia davvero intrigante... Ti ringrazio!";
			link.l1.go = "exit";
			npchar.quest.rivados = "true";
			NextDiag.TempNode = "Total_info";
		break;
		// <-- информационный блок
		
		case "capper":
			dialog.text = "Cosa cerchi nelle terre dei Rivados, uomo bianco?";
			link.l1 = "Il mio nome è "+GetFullName(pchar)+" e son qui per ordine dell’Ammiraglio Dodson. Devo parlare con Eddie il Nero. Se ho capito bene, sei tu.";
			link.l1.go = "capper_1";
		break;
		
		case "capper_1":
			dialog.text = "Sì, sono Edward Black, detto anche Eddie il Nero. Dimmi pure, che cosa vuole da me l’ammiraglio?";
			link.l1 = "Sull'‘Tartarus’ c’è un uomo chiamato Chimiset. L’ammiraglio è disposto a liberarlo.";
			link.l1.go = "capper_2";
		break;
		
		case "capper_2":
			dialog.text = "Questa è davvero un’ottima notizia. Chimiset è la nostra guida spirituale, e tutti i Rivados sentono la sua mancanza. Ma immagino che l’ammiraglio voglia qualcosa in cambio della sua libertà, vero?";
			link.l1 = "Niente. Vuole solo liberarlo come segno di buona volontà. Ma c’è un intoppo...";
			link.l1.go = "capper_3";
		break;
		
		case "capper_3":
			dialog.text = "Avanti, uomo bianco.";
			link.l1 = "L'ex nostromo dell'ammiraglio, l'attuale carceriere Chad Kapper, s'è unito ai Narvali, s'è dato alla macchia e ormai sfugge al giogo dell'ammiraglio. Sappiamo che Chad trama l'assassinio di Chimiset. L'ammiraglio non vuole che ciò accada. Ti proponiamo un'azione congiunta per farla finita col traditore e per liberare il tuo uomo.";
			link.l1.go = "capper_4";
		break;
		
		case "capper_4":
			dialog.text = "Le tue parole suonano un po’ strane, ma continua pure. Chimiset è nei guai?";
			link.l1 = "Sì. Chad sta tramando per ucciderlo. Kapper userà i Narvali per impadronirsi della Città. Dobbiamo muoverci in fretta se vogliamo salvare Chimiset, finché Chad non sospetta nulla. L’Ammiraglio ha richiamato tutte le guardie dal ‘Tartarus’, il passaggio è libero. Ecco la chiave che apre la porta della prigione. Prendila.";
			link.l1.go = "capper_5";
		break;
		
		case "capper_5":
			RemoveItems(pchar, "key_capper", 1);
			dialog.text = "";
			link.l1 = "Raduna i tuoi uomini, vai al Tartaro e libera Chimiset. Tutte le carte sono in mano tua.";
			link.l1.go = "capper_6";
		break;
		
		case "capper_6":
			dialog.text = "Sa di trappola... E se fosse un agguato? E se l’ammiraglio volesse far fuori i Rivados? Perché non se la vede con Kapper in persona?";
			link.l1 = "Dodson ha detto che t’importa della vita di Chimiset... Ha già fatto il suo: ecco la chiave e le guardie se ne sono andate. Devi solo entrare, sistemare Chad e liberare il tuo uomo. Ti do la mia parola: nessuna trappola, stavolta. Ah, e un’ultima cosa: l’ammiraglio vuole la testa di Chad in cambio della vita e libertà di Chimiset. Abbiamo un patto?";
			link.l1.go = "capper_7";
		break;
		
		case "capper_7":
			dialog.text = "La vita di Chimiset vale più dell’oro per i Rivados. Ci sposteremo subito sulla ‘Tartarus’. Ma tu resterai qui come nostro ostaggio. Se dovesse esserci un agguato, sentirai sulla pelle la furia dei Rivados!\nZikomo! Rimani vicino alla porta e sorveglia il nostro ospite. Non farlo uscire. Sarò io stesso a guidare l’assalto alla ‘Tartarus’!";
			link.l1 = "Buona fortuna, Eddie. E ricorda: voglio la testa di Chad Kapper!";
			link.l1.go = "capper_8";
		break;
		
		case "capper_8":
			DialogExit();
			chrDisableReloadToLocation = true;//закрыть локацию
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "LSC_ZikomoNearDoor", 10.0);
			NextDiag.CurrentNode = "chimiset";
		break;
		
		case "chimiset":
			dialog.text = "Chimiset è stato liberato! Non mentivi, uomo bianco, sono pronto a chiamarti amico dei Rivados!";
			link.l1 = "Sono lieto. Chad Kapper è crepato?";
			link.l1.go = "chimiset_1";
		break;
		
		case "chimiset_1":
			dialog.text = "Devo chiederti perdono, amico bianco: hai fatto tutto ciò che potevi per noi, ma ti abbiamo deluso... ti ho deluso io! Quel dannato Kapper è scappato. Aveva due Narvali con sé. Li abbiamo fatti fuori, ma il lurido carceriere s'è immerso e s'è dileguato dalla porta bassa verso i territori dei Narvali.";
			link.l1 = "Malasorte... Non sapevi che c'erano due uscite dal 'Tartaro'?";
			link.l1.go = "chimiset_2";
		break;
		
		case "chimiset_2":
			dialog.text = "Non ci abbiamo pensato. Siamo entrati all’assalto dall’ingresso principale...";
			link.l1 = "Peccato. Contavo di mettere le mani sulla sua testa. Davvero un peccato. Ora continuerà a tramare contro di noi.";
			link.l1.go = "chimiset_3";
		break;
		
		case "chimiset_3":
			dialog.text = "Ammetto la mia colpa. Ma non potevamo inseguirlo sulle navi nemiche. Al posto della testa di Chad, avrai la nostra amicizia e rispetto. Da ora in poi, potrai visitare liberamente il nostro territorio. La saggezza di Chimiset ti tornerà utile, parlaci se ti serve qualcosa. Parlagli pure se ne hai bisogno. E riferisci all’ammiraglio che ho apprezzato il suo gesto.";
			link.l1 = "D’accordo.";
			link.l1.go = "chimiset_4";
		break;
		
		case "chimiset_4":
			dialog.text = "Aspetta! Abbiamo perso Chad, ma ho trovato alcuni fogli sulla sua scrivania, che stava studiando quando siamo arrivati. Eccoli qui. Potrebbero tornarti utili, fratello bianco.";
			link.l1 = "Ah! Forse... Chad mette troppa fede nella carta...";
			link.l1.go = "chimiset_5";
		break;
		
		case "chimiset_5":
			dialog.text = "Sarai sempre un ospite gradito qui, amico bianco. Tutti i Rivados ne saranno avvisati. Buona fortuna!";
			link.l1 = "Anche a te, Eddie...";
			link.l1.go = "chimiset_6";
		break;
		
		case "chimiset_6":
			DialogExit();
			LAi_ActorGoToLocator(npchar, "goto", "goto1", "LSC_EddyStay", -1);
			sld = CharacterFromID("Zikomo");
            LAi_SetWarriorType(sld);
			LAi_warrior_SetStay(sld, true);
			LAi_warrior_DialogEnable(sld, true);
			GiveItem2Character(pchar, "letter_chad");
			ChangeItemDescribe("letter_chad", "itmdescr_letter_aeva");
			GiveItem2Character(pchar, "letter_chad_1");
			ChangeItemDescribe("letter_chad_1", "itmdescr_letter_axel");
			pchar.questTemp.LSC.rvd_friend = "true"; //флаг на проход по кораблям ривадос
			pchar.rvd_friend = true; // ривадосы не будут останавливать где просят пароль
			pchar.questTemp.Saga.SharkHunt = "dodson_whiskey"; // к Акуле
			sld = CharacterFromID("Dodson");
			sld.dialog.currentnode = "Chad_escape"; // ноду Акуле
			AddQuestRecord("SharkHunt", "33");
			LocatorReloadEnterDisable("LostShipsCity_town", "reload48", true); // закрыть вход к Дональду Гринспи
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
			AddSimpleRumourCityTip("Have you heard the latest news? The Rivados' insolence is out of control, they have attacked the admiral's prison and released their wizard!", "LostShipsCity", 3, 2, "LSC", "");
			AddSimpleRumourCityTip("Just think about it - those uppity Rivados dared to attack the 'Tartarus'! They say that the jailer, Chad Kapper, has escaped to the Narwhals...", "LostShipsCity", 3, 2, "LSC", "");
			AddSimpleRumourCityTip("This is the height of impudence, isn't it? Attacking a military facility of the admiral! Aye, looks like Black Eddie is getting stronger...", "LostShipsCity", 3, 2, "LSC", "");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}
