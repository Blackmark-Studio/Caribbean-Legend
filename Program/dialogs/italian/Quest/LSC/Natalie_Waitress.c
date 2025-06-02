// официантка Наталия Бушелл
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
			if (pchar.questTemp.LSC == "return" && !CheckAttribute(npchar, "quest.return_isl"))
			{
				dialog.text = "Oh! E mi avevano detto che sei affogato... Bugiardi!";
				link.l1 = "Certo che l’hanno fatto! Ah! Sto benone!";
				link.l1.go = "exit";
				npchar.quest.return_isl = "true";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Buona giornata, "+GetAddress_Form(NPChar)+" ! Prima volta qui? Non ti ho mai visto prima... Spero che verrai a trovarci più spesso, Sancho può offrirti una scelta eccellente di bevande. Ah, e mi chiamo Nathalie, aiuto Sancho con le faccende della taverna.";
				link.l1 = TimeGreeting()+" . Il mio nome è "+GetFullName(pchar)+" Lieto di conoscerti. E prima non potevi vedermi. Sono arrivato qui da poco.";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, "+GetFullName(pchar)+"! "+TimeGreeting()+" ! Vuoi qualcosa?";
				link.l1 = LinkRandPhrase("Hai qualcosa di curioso da raccontare?","È successo qualcosa di nuovo sull’isola?","Mi racconterai gli ultimi pettegolezzi?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Vorrei farti alcune domande sull'isola.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Volevo solo sapere come te la passi. Ci si vede!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Di recente? Un'altra nave è finita sugli scogli? Non ho sentito nulla... O forse non sei arrivato qui come monsieur Turam, aggrappato ai resti dell'albero maestro? Oh, perdona la mia curiosità, è la natura delle donne, sai com'è.";
			link.l1 = "No, va tutto bene, Nathalie. Sono arrivato qui su una barca, ma è affondata. È stato un piacere conoscerti. Ci si rivede in giro!";
			link.l1.go = "exit";
			link.l2 = "No, va bene. Volevo solo farti un paio di domande sull’isola.";
			link.l2.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Ascolto, dimmi pure.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Lavori in taverna. Che mi dici del proprietario?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "E come sei finito qui?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Quanta gente vive qui?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Non ti stupisce mai vedere facce nuove da queste parti?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Nessuna domanda. Se volete scusarmi...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Solo cose buone,  "+GetAddress_Form(NPChar)+"Sancho tiene sempre un'ampia scelta di bevande – dai vecchi vini alle birre più semplici, senza scordare il rum. Alcuni anni or sono, ha scovato una stiva intera di vini pregiati e per due mesi ha trascinato casse su casse nella sua bottega.\nOra siamo tanto forniti di vino che solo i governatori dell'arcipelago potevano permettersene così tanto. E di rum non c'è mai penuria. Da Sancho troverai non solo da bere, ma anche notizie fresche, un buon consiglio e un letto caldo dove posare le ossa per la notte.";
			link.l1 = "Capisco...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Oh, questa è una storia triste. Sette anni or sono, scappai di casa con il mio promesso e decidemmo di trasferirci a Belize da Santiago. Ma il navigatore sbagliò rotta vicino a Main, così veleggiammo verso nord invece che sud e fummo ghermiti da una tempesta. La nostra nave affondò non lontano dall'anello esterno.\nIl mio amato morì quel giorno, come quasi tutti gli altri. Io e pochi superstiti abbiamo ricominciato qui, sull'Isola Giustizia.";
			link.l1 = "Storia triste...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Un bel po'. I clan dei Rivados e dei Narvali sono numerosi, vivono qui da decenni. Gente comune non ce n’è molta, ma la taverna è gremita ogni notte. Faccio fatica a star dietro alle bevute.";
			link.l1 = "Davvero? Curioso.";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "E perché dovremmo? Spuntano sempre nuove facce qui. Nemmeno so quanti siamo sull’isola. A volte incontro un uomo per la prima volta, e lui mi racconta che già da un anno si trascina su questa dannata Isola Giustizia.";
			link.l1 = "Ebbene...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Che fai lì, eh? Ladro!","Guarda un po’! Appena m’è venuto da perdermi nei miei pensieri, tu già ficchi il naso nel mio forziere!","Hai deciso di ficcare il naso nei miei forzieri? Non la passerai liscia!");
			link.l1 = "Maledizione!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Cosa?! Hai deciso di rovistare nei miei forzieri? Non la passerai liscia, maledetto!";
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
			dialog.text = LinkRandPhrase("Ascolta, faresti meglio a mettere via le tue armi. Mi mettono a disagio.","Sai, qui non si tollera andare in giro con la lama sguainata. Riponila.","Ascolta, lascia perdere il cavaliere d’altri tempi che va in giro armato. Metti via quell’arnese, non fa per te...");
			link.l1 = LinkRandPhrase("Va bene.","D'accordo.","Come dici tu...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Ascolta, sono cittadino di questa città e ti chiederei di rinfoderare la lama.","Ascolta, sono un cittadino di questa città e ti chiederei di rinfoderare la lama.");
				link.l1 = LinkRandPhrase("Va bene.","D'accordo.","Come dici tu...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Attento, compare, a correre con la lama sguainata. Potrei agitarmi...","Non mi piace quando la gente mi passa davanti con l’arma sguainata. Mi mette i brividi...");
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
