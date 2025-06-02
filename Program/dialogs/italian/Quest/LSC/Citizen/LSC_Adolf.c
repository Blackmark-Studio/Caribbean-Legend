// Адольф Барбье - авантюрист
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "GenQuest.CitizenConflict") && sti(pchar.GenQuest.CitizenConflict) > 3)
			{
				dialog.text = "Non voglio parlare con te. Assali povera gente senza motivo e li costringi a battersi. Vattene, canaglia!";
				link.l1 = "Hm...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Ciao, ciao... Non ti ho mai visto prima d’ora. Sei arrivato di recente?";
				link.l1 = "Intendi dire qui sull’Isola, di recente? Sì, hai ragione. Il mio nome è "+GetFullName(pchar)+", un marinaio e un avventuriero.";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, "+GetFullName(pchar)+"! "+TimeGreeting()+" ! Vuoi qualcosa? ";
				link.l1 = LinkRandPhrase("Hai qualcosa di curioso da raccontare?","È successo qualcosa di nuovo sull'isola?","Mi racconti gli ultimi pettegolezzi?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Vorrei chiederti alcune cose sull'isola.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Volevo solo sapere come te la passi. Ci vediamo!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Ah, proprio come me. Non sono marinaio, ma la mia sete d’avventure mi ha portato fin qui. Ora devo marcire in questo cimitero di navi come tutti gli altri. Ah, a proposito, il mio nome è Adolf Barbier.";
			link.l1 = "È stato un piacere conoscerti, Adolf. Arrivederci.";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Hai qualcosa di curioso da raccontare?","È successo qualcosa di nuovo sull’isola?","Mi racconterai gli ultimi pettegolezzi?");
			link.l2.go = "rumours_LSC";
			link.l3 = "Vorrei farti alcune domande su quest'isola.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
		//----------------------------------Адольф Барбье----------------------------------------
		case "Adolf":
			dialog.text = "Perché diavolo sei entrato nei miei alloggi senza il mio permesso?";
			link.l1 = "Stai mancando di rispetto al tuo ospite, Adolf. E ho degli affari da proporti.";
			link.l1.go = "Adolf_1";
		break;
		
		case "Adolf_1":
			dialog.text = "Non faccio affari con chi non conosco! Fuori dai piedi!";
			link.l1 = "Così, senza tante cerimonie? Fai affari coi Narvali, ma con me no? Che peccato...";
			link.l1.go = "Adolf_2";
		break;
		
		case "Adolf_2":
			dialog.text = "Di che vaneggi, buffone? Che affari hai coi Narvali? Questa è l’ultima occasione per levarti dai piedi, o sarò io stesso a gettarti in mare!";
			link.l1 = "Non hai fegato per farlo, 'maestro del lancio'... Ora dammi retta. Dov’è l’archibugio che vuoi usare per sparare all’ammiraglio? Me lo dici di tua sponte o devo essere più convincente?";
			link.l1.go = "Adolf_3";
		break;
		
		case "Adolf_3":
			dialog.text = "Cosa? Che stutzen? Quale ammiraglio? Sei impazzito, compare? Ho già venduto il mio stutzen e non ce l'ho più. E non sono affari tuoi a chi l’ho dato. Non me ne frega un accidente di cosa ci faranno. E non ho intenzione di sparare a nessuno – né ad ammiragli, né a generali. Hai capito, lurido cane?";
			link.l1 = "Capisco solo che sei un bugiardo e un assassino, Adolf. So che non l’hai venduta ma riscattata. So pure che hai intascato una bella somma per saldare i tuoi debiti e comprarti questa baracca...";
			link.l1.go = "Adolf_4";
		break;
		
		case "Adolf_4":
			dialog.text = "Questo è il mio denaro, brutto ceffo! Me lo sono guadagnato! E ho venduto pure il mio stutzen!";
			link.l1 = "Tu menti, Adolf. Sei stato ingaggiato dai Narvali per sparare all’ammiraglio. Ti hanno dato monete per riscattare il tuo stutzen. Hanno pagato pure questo posto. Lo sai meglio di me che il bompresso oltre questa porta è l’unico punto dell’isola da cui si può colpire il balcone posteriore della residenza dello Squalo.";
			link.l1.go = "Adolf_5";
		break;
		
		case "Adolf_5":
			dialog.text = "Sei fuori di testa, bastardo! Devi essere rinchiuso subito! Ho aspettato questa cabina per mezzo anno prima che Sessile se ne andasse da qui...";
			link.l1 = "Basta. Perquisirò te e la tua cabina, troverò il fucile e qualche altra prova, ne sono certo. Poi andremo insieme dallo Squalo. Sarà lieto di guardarti dritto negli occhi.";
			link.l1.go = "Adolf_6";
		break;
		
		case "Adolf_6":
			dialog.text = "Ah, sei proprio un bastardo malato! Piuttosto crepo, che lasciare che qualche canaglia fuori di testa metta le mani sulle mie cose!";
			link.l1 = "Allora li toccherò senza chiederti il permesso...";
			link.l1.go = "Adolf_7";
		break;
		
		case "Adolf_7":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetWarriorType(npchar);
			ChangeCharacterAddressGroup(npchar, pchar.location, "barmen", "stay");
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_SetImmortal(npchar, false);
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "LSC_AdolfDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
	case "int_quests":
			dialog.text = "Ebbene, parliamo un po'. Che cosa vuoi sapere?";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Come sei arrivato qui?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Cosa puoi raccontarmi dei clan locali?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Hai già perlustrato l'anello esterno dei vascelli?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "L’isola ha qualche legame con Cuba o la Terraferma?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Nessuna domanda. Perdonami...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Mi era capitato tra le mani il manoscritto di un marinaio, Alvarado, uno spagnolo. Descriveva l’Isola con una miriade di dettagli. Nominava alcune navi curiose: San Augustine, San Geronimo e Tartarus. Tutte facevano parte dello squadrone di de Betancourt, svanite più di cinquant’anni or sono.\nMi sono messo a indagare su quell’impresa. Così ho scoperto che c’era una quarta nave chiamata Santa Anna che trasportava il tesoro dello squadrone – una montagna di dobloni! E nei loro stive giaceva pure dell’oro grezzo. Decisi di trovare l’Isola.\nMi accordai con un capitano che conoscevo e salpammo sulla sua goletta. Immagino si capisca come andò a finire. Abbiamo trovato l’Isola, le navi di Betancourt, persino un suo discendente – vive qui, si chiama Antonio de Betancourt. Ma non sono riuscito a lasciare questo posto.\nGli scogli hanno fatto a pezzi la goletta, il mio compagno ha tirato le cuoia e io, assieme ad altri poveri diavoli sopravvissuti, sono arrivato qui. La beffa peggiore è che non ho trovato ciò che cercavo – né il tesoro della Santa Anna, né l’oro grezzo.";
			link.l1 = "Ho letto anch'io gli appunti di Alvarado. Storia affascinante.";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "I Rivados sono dannati pagani, gentaglia senza Dio. Son figli di schiavi negri, portati qui da de Betancourt dall'Africa. Hanno imparato a brandire spade e moschetti dai bianchi, ma restano selvaggi fino al midollo.\nI Narvali sono brava gente, astuti e combattenti valorosi. Hanno tra loro artigiani sopraffini. Ne conosco parecchi, forse un giorno mi unirò al loro clan.\nI pirati sono una spina nel fianco, maledetti loro. Non li abbiamo chiamati, ma sono arrivati, ci hanno preso le scorte e ora hanno la sfacciataggine di venderci il nostro stesso cibo! Mascalzoni, eh? Peccato che non possiamo cacciarli e dobbiamo sopportare la loro presenza.";
			link.l1 = "Interessante...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Certo. Un uomo deve pur guadagnarsi da vivere. Maledetti pirati, vogliono oro, pesos o qualche altra bagattella in cambio del cibo. A noi del posto vendono a prezzo più basso che ai clan, ma non è certo beneficenza. Per fortuna, all’anello esterno ci sono ancora abbastanza relitti da depredare, molti non sono mai stati toccati da nessuno dopo il naufragio.\nÈ un passatempo interessante, ma rischioso: puoi finire nella stiva allagata, spezzarti l’osso del collo, restare impigliato tra le gomene, farti schiacciare da qualche trave o imbatterti in granchi giganti – spesso si intrufolano nelle stive laggiù.";
			link.l1 = "Capisco...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Ahimè, no. Dicono che bucaniere e contrabbandieri da Cuba venivano qui molto tempo fa – scambiavano provviste per oro e mercanzie. Anche i Narvali visitavano gli insediamenti. Ma ormai è storia. Nessuno rischierebbe di salpare su scialuppe fragili e minute. Le tempeste le fanno a pezzi in un soffio, e qui di navi migliori non ne abbiamo.";
			link.l1 = "Capisco...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Che ci fai là, eh? Ladro!","Guarda un po’! Appena mi sono perso nei miei pensieri, tu già frugavi nel mio baule!","Hai deciso di frugare nei miei forzieri? Non te la caverai così facilmente!");
			link.l1 = "Merda!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Cosa?! Hai pensato di frugare nei miei forzieri? Non la passerai liscia!";
			link.l1 = "Ragazza sciocca!";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//замечание по обнажённому оружию
		case "LSCNotBlade":
			dialog.text = LinkRandPhrase("Ascolta, faresti meglio a mettere via quell’arma. Mi mette a disagio.","Sai, qui non è ben visto andare in giro con la lama sguainata. Rimettila via.","Ascolta, lascia stare il cavaliere medievale che corre in giro brandendo la spada. Mettila via, non fa per te...");
			link.l1 = LinkRandPhrase("Va bene.","Va bene.","Come dici tu...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Ascolta, sono cittadino della città e ti chiederei di abbassare la lama.","Ascolta, sono cittadino di questa città e ti chiederei di tenere a bada la tua lama.");
				link.l1 = LinkRandPhrase("Bene.","Va bene.","Come dici tu...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Sta’ attento, compare, a correre in giro con l’arma sguainata. Mi fai venire i nervi...","Non mi piace quando gli uomini mi passano davanti con l’arma sguainata. Mi fa venire i brividi...");
				link.l1 = RandPhraseSimple("Capito.","Lo sto portando via.");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;
// <-- специальные реакции
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
