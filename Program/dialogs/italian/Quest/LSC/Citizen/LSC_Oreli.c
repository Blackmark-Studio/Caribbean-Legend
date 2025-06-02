// Орели Бертин - просто жительница
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
				dialog.text = "Non voglio parlare con te. Attacchi gente pacifica senza motivo e li provochi alla rissa. Sparisci dalla mia vista!";
				link.l1 = "Hm...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Buondì, signore. Che avete da dire?";
				link.l1 = TimeGreeting()+". Il mio nome è "+GetFullName(pchar)+", Sono nuovo da queste parti, quindi sto cercando di conoscere la gente del posto.";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, "+GetFullName(pchar)+"! "+TimeGreeting()+"Che vuoi, forestiero?";
				link.l1 = LinkRandPhrase("Hai qualcosa di curioso da raccontare?","È successo qualcosa di nuovo sull’isola?","Mi racconti gli ultimi pettegolezzi?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Vorrei farti alcune domande sull’isola.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Volevo solo sapere come te la passi. A presto!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Capisco. Mi chiamo Orelie Bertine. Come sei giunto fin qui?";
			link.l1 = "Diciamo che volevo solo posare gli occhi sulla mistica Isola Giustizia.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Dunque, devi essere uno di quei folli che arrivano qui di propria volontà... Beh, ora avrai tutto il tempo di vedere l’Isola e di gustarti a sazietà la sua ‘giustizia’.";
			link.l1 = "E secondo il tuo sarcasmo, ci sarebbero problemi con la giustizia qui?";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "No, tutto va bene. Ma per qualche motivo ora dobbiamo pagare i pirati per il nostro cibo, che fino a poco tempo fa era gratis per tutti. E quando i clan iniziano a litigare nella nostra parte dell’Isola, dobbiamo rintanarci dentro le navi per non rischiare di prenderci una palla o una coltellata.\nVoglio dire, loro possono fare il diavolo a quattro nei nostri territori, mentre noi non possiamo mettere piede nei loro. Ma va bene così, niente altri guai…";
			link.l1 = "Capisco. Bene, lieto d'averti incontrato. A presto!";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Ascolto.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Vivi su questa maledetta isola da molto tempo?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "C'è qualcosa d'interessante sull'Isola?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Che ne pensi delle confraternite?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "I pirati ti danno fastidio?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Nessuna domanda. Perdonami...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Da moltissimo tempo. Ho perso ormai il conto. Dev’essere diciassette anni… no, forse diciotto… o sono venti? Qual è l’anno corrente?";
			link.l1 = "Capisco... Dunque, sei un vecchio lupo di quest’isola?";
			link.l1.go = "ansewer_1_1";
		break;
		
		case "ansewer_1_1":
			dialog.text = "Più o meno. Ricordo ancora i tempi in cui i filibustieri commerciavano con noi, e i Narvali più audaci e furbi salpavano verso la terraferma per scambiare provviste con mercanzia sottratta alle stive delle navi. Ma ormai qui c’è un bel po’ di gente che non ha mai visto altro luogo che l’Isola, perché ci sono nati. Questi non sono solo veterani: sono veri e propri autoctoni.";
			link.l1 = "Interessante...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Sì, proprio così. Qui tutto è curioso. Fai un giro e vedrai con i tuoi occhi. Nuota attorno al cuore dell’Isola. Passa in taverna, visita una bottega, entra in chiesa. Ma la verità è che tra una settimana questa curiosità svanirà, te lo posso giurare.";
			link.l1 = "Capito...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "E come dovremmo pensare a quei banditi? Io cerco solo di starne alla larga, tutto qui. Almeno i Narvali portano qualche beneficio all’Isola, tra loro ci sono artigiani di gran talento, ma i Rivados sono solo selvaggi e pagani. Vivono ancora secondo le loro leggi africane, come se fossero passati secoli. Bestie. L’unica cosa che hanno imparato è usare le armi da fuoco. Si dice che pratichino ancora riti di cannibalismo!";
			link.l1 = "Che incubo...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "La parte in cui ci vendono il nostro stesso cibo dà un po’ fastidio, ma ai cittadini non fanno alcun male. Anzi, al contrario, hanno portato ordine fra i clan e tengono lontana ogni violenza.\nC’era un cittadino che dava problemi e sventolava la sciabola. Ha persino ferito due altri paesani. I pirati l’hanno portato nel Tartaro per qualche settimana. Ora quell’uomo è calmo, quieto come il mare al tramonto. Non lo vediamo spesso, ormai l’anello esterno è la sua nuova casa...";
			link.l1 = "Capisco...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Che stai facendo laggiù, eh? Ladro!","Guarda un po’! Mi bastava perdermi un attimo nei miei pensieri, ed ecco che ti ficchi subito nel mio forziere!","Hai deciso di frugare nei miei forzieri? Non la passerai liscia!");
			link.l1 = "Maledizione!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Cosa?! Hai deciso di frugare nei miei forzieri? Non la passerai liscia!";
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
			dialog.text = LinkRandPhrase("Ascolta, faresti meglio a mettere via quell’arma. Mi mette agitazione.","Sai, qui non è permesso andare in giro con la lama sguainata. Riponila.","Ascolta, non fare il cavaliere d’altri tempi che va in giro sguainando la spada. Mettila via, non è roba tua...");
			link.l1 = LinkRandPhrase("Bene.","Va bene.","Come dici tu...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Ascolta, sono un cittadino di questa città e ti chiederei di tenere a bada la tua lama.","Ascolta, sono cittadino di questa città e ti chiederei di rinfoderare la lama.");
				link.l1 = LinkRandPhrase("Va bene.","D'accordo.","Come dici tu...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Sta' attento, compare, a correre in giro armato. Potrei innervosirmi...","Non mi va che gli uomini mi passino davanti con l’arma sguainata. Mi mette addosso una fifa...");
				link.l1 = RandPhraseSimple("Capito.","Me lo porto via.");
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
