// Джаспер Пратт - каторжник
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
				dialog.text = "Non voglio parlare con te. Assalti civili innocenti senza motivo e li provochi alla rissa. Sparisci dalla mia vista!";
				link.l1 = "Hmm...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Buongiorno, signore. Cercate qualcosa?";
				link.l1 = TimeGreeting()+" . Il mio nome è "+GetFullName(pchar)+", e qual è il tuo? Sono appena arrivato su questa dannata isola...";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, "+GetFullName(pchar)+"! "+TimeGreeting()+"Che vuoi, forestiero?";
				link.l1 = LinkRandPhrase("Hai qualcosa di curioso da raccontare?","Ci sono novità sull'isola?","Mi racconti gli ultimi pettegolezzi?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Vorrei farti alcune domande sull’isola.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Volevo solo sapere come te la passi. Ci si vede!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Io? Son Jasper, vecchio galeotto di stato. Ecco perché la gente mi guarda storto. Bah, al diavolo loro, ormai ci ho fatto il callo...";
			link.l1 = "Non mi importa chi fossi, ciò che conta è chi sei ora.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Peccato che non tutti la pensino come voi, signore.";
			link.l1 = "Ebbene, la mia reputazione di spirito libertino mi precede...";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "Felice per te. Non temere, nonostante il mio passato, non sono più un pericolo né per le borse né per i forzieri degli abitanti dell’Isola Giustizia. Son lieto che finalmente mi sia concesso vivere in pace.";
			link.l1 = "Felice d’incontrarti, Jasper. A presto!"link.l1.go ="esci";
			link.l2 = LinkRandPhrase("Hai qualche storia intrigante da raccontare?","È successo qualcosa di nuovo sull’isola?","Mi racconti gli ultimi pettegolezzi?");
			link.l2.go = "rumours_LSC";
			link.l3 = "Vorrei farti qualche domanda sull’isola.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Sì, certo. Se posso, ti risponderò. Chiedi pure.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Come sei diventato un abitante dell’Isola Giustizia?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Ti garba questo posto?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Hai detto che la gente ti guarda di traverso. È per via del tuo passato?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Questa Isola è davvero singolare, non trovi?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Nessuna domanda. Perdona...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Sono fuggito da una piantagione cubiana. Eravamo in cinque e abbiamo deciso che era meglio rischiare la morte piuttosto che continuare a piegare la schiena sotto la frusta. Siamo riusciti a ingannare le guardie e a sparire nella giungla, poi siamo arrivati alla riva e abbiamo costruito una zattera.\nVolevamo raggiungere Tortuga, ma il destino aveva altri piani. Nessuno di noi sapeva navigare, così ci siamo persi. Poi l’acqua è finita... Non voglio ricordare quel momento. Alla fine, sono stato io l’unico a raggiungere l’Isola e sopravvivere.";
			link.l1 = "Capisco...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Sai, a me va bene così. Dopo tutto quello che ho passato sulla piantagione, questo posto mi sembra un paradiso. Non chiedo molto... Un po' di cibo, acqua e un bicchiere di rum ogni sera. Nessuno mi dà fastidio qui e non ho intenzione di andarmene. Morirò qui quando sarà la mia ora.";
			link.l1 = "Capisco...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Vedi, quest’Isola è il terreno di gioco d’un ladro misterioso. Le serrature non lo fermano. Di solito si aggira nelle stanze dell’ammiraglio, ma anche i nostri forzieri non ne escono indenni. Nessuno sa chi sia, così sospettano di chi... ehm, ha un passato poco pulito.\nStrano tipo, però: sgraffigna solo bottiglie di alcol e ninnoli, mai roba di vero valore. Buffo, no?";
			link.l1 = "Capito...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Sì, concordo. Ho nuotato parecchio tra le navi interne dell’Isola Giustizia. Ci sono pochissime uscite dall’acqua. San Augustin, dove sta il ponte. Gloria, l’albero maestro abbattuto. Se nuoti vicino alla piattaforma della Fenix, poi giri attorno alla Ceres Smitie, arrivi alla cabina di Mary Casper, a prua della nave.\nLa spaccatura nel Tartaro ti porta dritto alla prigione. C’è un buco nella prua del San Augustin, da lì puoi entrare nel magazzino dell’ammiraglio, ma non te lo consiglio, amico mio. La porta più bassa del Tartaro è spesso sprangata, tienilo a mente.\n E ovviamente puoi infilarti nella Fernanda, quel flauto solitario e sventrato. Dicono che nessuno ci abiti, ma spesso vedo luci accese nella cabina e a volte sento strane canzoni stonate e grida d’ubriaco.";
			link.l1 = "Curioso... Devo esplorare meglio questo posto.";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Che ci fai laggiù, eh? Ladro!","Guarda un po’! Mi basta distrarmi un attimo, e tu subito ficchi il naso nel mio baule!","Hai deciso di frugare nei miei forzieri? Non la passerai liscia!");
			link.l1 = "Maledizione!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Cosa?! Hai deciso di frugare nei miei forzieri? Non la passerai liscia, lurido cagnaccio!";
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
			dialog.text = LinkRandPhrase("Ascolta, faresti meglio a riporre quell’arma. Mi mette a disagio.","Sai, qui non è tollerato andare in giro con la lama sguainata. Riponila.","Ascolta, non fare la parte del cavaliere medievale che corre in giro con la spada. Mettila via, non ti si addice...");
			link.l1 = LinkRandPhrase("Va bene.","Come vuoi, allora.","Come dite voi...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Ascolta, sono un cittadino di questa città e ti chiederei di tenere la lama nel fodero.","Ascolta, sono cittadino di questa città e ti chiederei di tenere a bada la tua lama.");
				link.l1 = LinkRandPhrase("Va bene.","Come vuoi, allora.","Come dici tu...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Sta' attento, compare, a correre con un'arma in mano. Potrei innervosirmi...","Non mi piace quando gli uomini camminano davanti a me con l’arma sguainata. Mi mette i brividi...");
				link.l1 = RandPhraseSimple("Capito.","Me ne sto andando.");
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
