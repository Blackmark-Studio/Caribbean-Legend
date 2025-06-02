// Оеларт Котеел - канонир
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
				dialog.text = "Non voglio parlare con te. Attacchi civili innocenti senza motivo e li provochi a menar le mani. Sparisci dai miei occhi!";
				link.l1 = "Hmm...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Buon dì, signore! Vi garba questo tempo?";
				link.l1 = TimeGreeting()+" . Mi va bene qualsiasi tempo, tranne le tempeste in mare aperto... ";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, "+GetFullName(pchar)+"! "+TimeGreeting()+"Che ti serve, forestiero?";
				link.l1 = LinkRandPhrase("Hai qualcosa di curioso da raccontare?","È successo qualcosa di nuovo sull’isola?","Mi racconterai gli ultimi pettegolezzi?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Vorrei farti qualche domanda sull'isola.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Volevo solo sapere come te la passi. Ci si vede!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Credimi, provo lo stesso. Non ti ho mai visto prima... il mio nome è Oelart Koteel e fui maestro cannoniere su una nave da guerra olandese.";
			link.l1 = ""+GetFullName(pchar)+"Sì, sono appena arrivato qui. In verità, sono sbarcato proprio ora.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Anch’io sono un novellino, non metto piede qui da nemmeno un anno. E spero proprio di non restarci troppo, anche se tutti cercano di convincermi del contrario. Piacere di conoscerti!";
			link.l1 = "Piacere di conoscerti anch’io, "+npchar.name+"...";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Hai qualcosa di curioso da raccontare?","Ci sono novità sull'isola?","Mi racconti le ultime chiacchiere?");
			link.l2.go = "rumours_LSC";
			link.l3 = "Vorrei farti qualche domanda sull’isola.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Ascolto.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Come sei finito qui?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Vuoi abbandonare l’Isola Giustizia?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Ti sei mai chiesto come sia nata l’Isola Giustizia?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Sei mai salito a bordo delle navi del clan?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Nessuna domanda. Perdona...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Abbastanza banale. Abbiamo ingaggiato uno schooner inglese e quasi vinto lo scontro. Sono scappati, così li abbiamo inseguiti. Passato un giorno, eravamo vicini ad acciuffarli, ma ci hanno abbattuto l’albero maestro e, naturalmente, sono riusciti a svignarsela.\nQuanto a noi, quasi affondammo in una burrasca furiosa, poi la corrente ci trascinò e alla fine la nostra nave fu sbattuta sugli scogli vicino all’anello esterno. Pochissimi sono riusciti a sopravvivere...";
			link.l1 = "Capisco...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Questo è il mio sogno. Non immagini quanto mi sia stufato di questo posto. Ma come potrei lasciarlo? Non ne ho la minima idea. Qui non ci sono navi, e non c’è modo di costruirne una nuova. Salpare su una barchetta sarebbe puro suicidio.";
			link.l1 = "Capisco...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Secondo le navi, ha circa cent’anni. Ma potrebbe essere più antica, per via dell’anello esterno. È fatta di vascelli, dalla cima fino alle profondità; forse quelli più vecchi giacciono sepolti sotto il mare.\nQuanto alla formazione dell’Isola... credo che correnti e tempeste abbiano trascinato qui i relitti, creando così una secca artificiale. Su di essa si è poi costruito l’anello esterno.\nLe navi interne, su cui viviamo... o sono state le prime, o sono riuscite in qualche modo a superare l’anello esterno. È probabile: l’Ammiraglio e i suoi pirati sono arrivati qui col loro brigantino, dopotutto.";
			link.l1 = "Interessante...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Son stato dai Rivados. Il vecchio Eddy il Nero voleva un parere sui cannoni di bordo e non so proprio perché. Così uno dei loro mi ha trovato e passato la parola d’ordine. Ho fatto visita al loro ‘Protettore’ e a quel Velasco. Le guardie son mastini: senza parola d’ordine, nemmeno provarci.";
			link.l1 = "Capisco...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Che stai combinando lì, eh? Ladro!","Guarda un po’! Mi basta distrarmi un attimo, e tu già frughi nel mio baule!","Hai deciso di frugare tra i miei forzieri? Non la passerai liscia, furfante!");
			link.l1 = "Merda!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Cosa?! Hai deciso di frugare nei miei forzieri? Non la passerai liscia, canaglia!";
			link.l1 = "Stolta ragazza!";
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
			dialog.text = LinkRandPhrase("Ascolta, faresti meglio a mettere via quell’arma. Mi mette agitazione.","Sai, qui non è tollerato andare in giro con la lama sguainata. Riponila.","Ascolta, lascia stare il cavaliere coi sogni di gloria e la spada sguainata. Mettila via, non è roba per te...");
			link.l1 = LinkRandPhrase("Bene.","D'accordo.","Come dite voi...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Ascolta, sono cittadino di questa città e ti chiederei di tenere a bada la tua lama.","Ascolta, sono cittadino di questa città, ti chiederei di tenere a bada la tua lama.");
				link.l1 = LinkRandPhrase("Va bene.","D'accordo.","Come dite voi...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Fa' attenzione, compare, a correre in giro con l’arma in pugno. Potrei innervosirmi...","Non mi piace quando gli uomini camminano davanti a me con l’arma sguainata. Mi mette i brividi...");
				link.l1 = RandPhraseSimple("Capito.","La porto via.");
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
