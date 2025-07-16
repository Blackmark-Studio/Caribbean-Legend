// Лайонел Маскетт - мещанин
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
				dialog.text = "Non voglio parlare con te. Assalti gente innocente senza motivo e li provochi a menare le mani. Sparisci dai piedi!";
				link.l1 = "Hmm...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Salute, "+GetAddress_Form(NPChar)+". Sei nuovo da queste parti?";
				link.l1 = TimeGreeting()+". Il mio nome è "+GetFullName(pchar)+"Sì, sono io.";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, "+GetFullName(pchar)+"! "+TimeGreeting()+" ! Vuoi qualcosa?";
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
			dialog.text = "Il mio nome è Lionell. Piacere di conoscerti. Come sei arrivato su questa dannata isola?";
			link.l1 = "Su una barca... Ho sentito dire che c'era una base di contrabbandieri e ho pensato di esplorarla... Esplorata. La barca è affondata e ora sono qui.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Pensano davvero che l’Isola sia un covo di contrabbandieri?";
			link.l1 = "Ebbene, non ufficialmente. La maggior parte non crede nemmeno che tu esista.";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "Seriamente... E perché mai dovrebbero? In verità, non esistiamo affatto. Da qui non si sfugge. Dicono che un tempo c’era un passaggio verso Cuba... Ma io non lo rammento, e vivo su questa dannata isola da quasi otto anni.";
			link.l1 = "Capisco. È stato un piacere scambiare due parole con voi. A presto!";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Hai qualcosa di curioso da raccontare?","È successo qualcosa di nuovo sull’isola?","Mi svelerai le ultime dicerie?");
			link.l2.go = "rumours_LSC";
			link.l3 = "Vorrei farti alcune domande sull’isola.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Ascolto.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Come mai sei finito qui?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Vorresti tornare sulla terraferma?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "E che fanno le anime perdute qui, sull’Isola Giustizia?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "E dove trovate tutto qui? Cibo, stoffe, bevande?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Nessuna domanda. Perdona...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Questa sì che è una storia stramba. Questa Isola Giustizia è l’unico posto dei Caraibi che io abbia mai visto. Quando la sorte mi voltò le spalle, m’imbarcai su un mercantile dall’Inghilterra vecchia. Cercavo lavoro a Belize, volevo fare lo scribacchino nell’ufficio del porto. Ma a Belize non ci siamo mai arrivati.\nNon sono marinaio io, quindi non so i dettagli. Una tempesta ci colpì e il giorno dopo la nostra nave era sfracellata sugli scogli. Quel colpo tremendo, le urla... non li scorderò mai.\nQualcuno urlò che c’era una falla nello scafo, la gente cominciò a gettarsi in mare. Io... io non so nuotare. Così rimasi a bordo. Ironia della sorte, fu proprio quello a salvarmi la pelle. La nave resse e la tempesta si placò all’alba.\nFeci l’unica cosa sensata prima di lasciare la nave. Presi un po’ di cibo, mi costruì una zattera e mi lasciai portare dal mare calmo fino all’anello esterno. Così sopravvissi, l’unico di tutto l’equipaggio.";
			link.l1 = "Capisco...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Era il mio unico sogno nei primi due anni qui. Ma adesso... Cosa rende l’Isola peggiore di qualsiasi altro posto al mondo? Certo, niente pascoli verdi né pecore, ma c’è il mare che incanta e un cielo notturno punteggiato di stelle splendide. Mangio a sazietà, indosso panni decenti che in Inghilterra non mi sarei mai potuto permettere. Ho una schiera di compagni.\nNo, signore, non desidero lasciare questo posto. Cosa mi aspetterebbe là fuori? Un lavoro dietro la scrivania sotto le urla d’un padrone per trecento pesos la settimana? Giammai! Qui ho trovato tutto ciò che cercavo, non m’importa d’altro.";
			link.l1 = "Capito. Felice per te!";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Quello che più gli aggrada. I clan si sfidano alla guerra, i pirati trafficano viveri, Axel Yost compra e vende mercanzie, Sancho Carpentero versa da bere e rallegra la compagnia, frate Julian prega, celebra la Messa e dispensa medicamenti. Loderdale e Solderra tramano l’uno contro l’altro, l’Abate si fa gonfiare d’orgoglio, Jillian e Tanneke sognano il vero amore...";
			link.l1 = "Interessante...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Dalle navi, amico mio, dalle navi. L’attività preferita di quasi tutti qui è rovistare i relitti dell’anello esterno e recuperare quello che si trova a bordo. Lì puoi scovare di tutto: armi, medicine, spezie e rum. Un mucchio di navi resta ancora inesplorato. La corrente porta spesso qui un’altra povera anima...";
			link.l1 = "Interessante...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Cosa fai lì, eh? Ladro!","Ma guarda un po’! Appena mi sono perso nei miei pensieri, tu hai deciso di frugare nel mio baule!","Hai deciso di frugare nei miei forzieri? Non la passerai liscia, maledetto!");
			link.l1 = "Maledizione!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Cosa?! Hai deciso di frugare nei miei forzieri? Non la passerai liscia, dannato!";
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
			dialog.text = LinkRandPhrase("Ascolta, faresti meglio a mettere via la tua arma. Mi mette a disagio.","Sai, qui non si tollera andare in giro con la lama sguainata. Rimettila al posto tuo.","Ascolta, non fare il cavaliere medievale che corre in giro brandendo la spada. Mettila via, non fa per te...");
			link.l1 = LinkRandPhrase("Va bene.","D'accordo.","Come dici tu...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Ascolta, sono cittadino di questa città e ti chiederei di tenere a bada la tua lama.","Ascolta, sono cittadino di questa città e ti chiederei di tenere a bada la tua lama.");
				link.l1 = LinkRandPhrase("Bene.","D'accordo.","Come dici tu...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Sta attento, compare, a correre con quell’arma in mano. Potrei innervosirmi...","Non mi piace quando gli uomini mi passano davanti con l’arma sguainata. Mi mette i brividi...");
				link.l1 = RandPhraseSimple("Capito.","Me lo sto portando via.");
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
