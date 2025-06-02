// Рамона Лоцано - горячая испанская сеньорита
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
				dialog.text = "Non voglio scambiare parola con te. Aggredisci gente innocente senza motivo e li provochi alla rissa. Sparisci!";
				link.l1 = "Hmm...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Ehilà, ehilà! Nuovo arrivato? O ti tenevi nascosto nelle stive, visto che è la prima volta che vedo la tua faccia da queste parti?";
				link.l1 = TimeGreeting()+"Nascondersi nelle stive non fa per me. Preferisco il posto del capitano... Sì, sono un nuovo arrivato qui.";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, "+pchar.name+"! "+TimeGreeting()+"! Son lieto di vederti! Che ne dici";
				link.l1 = LinkRandPhrase("Hai qualcosa di curioso da raccontare?","È successo qualcosa di nuovo sull’isola?","Mi racconti gli ultimi pettegolezzi?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Voglio farti qualche domanda sull’isola.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Volevo solo sapere come te la passi. Ci si vede!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Ebbene, allora conosciamoci un po'... capitano. Io sono Ramona Lozano, ma non ti azzardare a chiamarmi signora Lozano, lo detesto. E tu come ti chiami?";
			link.l1 = ""+GetFullName(pchar)+"Piacere di conoscerti, Ramona.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Sei davvero contento o fai solo il gentiluomo, "+GetFullName(pchar)+"Dimmi, sei davvero un capitano o mi stavi solo prendendo in giro?";
			link.l1 = "Oho, quante domande tutte insieme! Posso rispondere con calma, una alla volta? Primo, sono davvero lieto, non capita spesso d’incontrare belle signore da queste parti; secondo, sì, sono capitano, è vero. Ma la mia nave ora giace vicino alle coste del Vecchio Main...";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "Buffo! E com’è possibile, capitano? Tu stai qui, ma la tua nave se ne sta attraccata presso le coste della Terraferma. Non temi che la tua ciurma si disperda e il tuo veliero ti venga soffiato via sotto il naso?";
			link.l1 = "Son giunto fin qui su una barca, per... esplorare, ma tutto è andato storto e mi son ritrovato sulla vostra Isola Giustizia. Poi ci siamo scontrati con dei relitti nel buio, la nave s’è capovolta e voilà! Eccomi qua. La mia nave resterà ad aspettarmi finché vorrò. Dannie Hawk saprà comandare i miei uomini.";
			link.l1.go = "meeting_3";
		break;
		
		case "meeting_3":
			dialog.text = "Dannie Hawk? La Danielle Hawk? Vuoi dirmi che navighi insieme a lei?";
			link.l1 = "La merda galleggia, Dannie mi fa da ufficiale. L'ho lasciata al comando mentre ero disperso... Come la conosci?";
			link.l1.go = "meeting_4";
		break;
		
		case "meeting_4":
			dialog.text = "Ah! Tutti nelle colonie spagnole conoscono la piratessa Danielle Hawk e suo marito, Nathaniel. Sì, proprio tu, señor "+GetFullName(pchar)+", devi essere un tipo tosto... Sei forse un pirata? Non temere, vado d'accordo coi tipi come te. Mi piacciono quelli con la scorza dura.";
			link.l1 = "Beh, non sono proprio un pirata... Al momento sto solo lavorando con Jan Svenson e sto cercando il marito di Dannie, Nathaniel.";
			link.l1.go = "meeting_5";
		break;
		
		case "meeting_5":
			dialog.text = "E adesso vorresti dirmi che non sei un pirata? Al servizio del Diavolo della Foresta, il tuo nostromo è Dannie Hawk e cerchi Nathan Hawk... e scommetto che sei qui per l’ammiraglio, vero?";
			link.l1 = "Ramona, puoi chiamarmi pirata se ti va, mi va benone. Puoi pure dirmi ancora, basta che non mi butti a mollo...";
			link.l1.go = "meeting_6";
		break;
		
		case "meeting_6":
			dialog.text = "Sembra proprio che tu sia uno di quelli tosti, "+pchar.name+" Va bene, devo andarmene. Ci vediamo! Ho la sensazione che potremmo diventare amici... amici molto stretti.";
			link.l1 = "Perché no? Buona fortuna!";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Oh, davvero? Beh, domanda pure, risponderò se posso...";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Come sei arrivato qui?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Di certo, non hai mai tentato di scappare da questo posto...";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Come si tira avanti su questa scialuppa di relitti?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Che ci fai qui? Immagino che il cibo non sia servito per carità, vero?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Nessuna domanda. Perdono...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "È una lunga storia... È tutta colpa del mio patrigno. Quattro anni fa vivevo all’Avana e mai mi sarei aspettato che la mia vita prendesse questa piega. Mia madre morì e io diventai erede legittimo. Non eravamo ricchi, ma avevamo abbastanza denaro per vivere bene. Al mio patrigno non andava giù, così decise di liberarsi di me.\nOvviamente, lo scoprii solo quando due ceffi mi assalirono proprio dietro le porte della città. Quei babbei mi confessarono chi li aveva pagati e perché. Per fortuna non erano assassini di mestiere, altrimenti sarei marcito tra i cespugli con la gola tagliata. Gli sciocchi vollero prima divertirsi un po’.\nQuel giorno il destino mi fu propizio: un capitano come te stava passando vicino alle porte. Vide la scena e spedì quei bastardi dritti all’inferno. Non ebbero scampo. Gli raccontai tutto e mi sfogai un po’... Capì che non avevo dove andare e mi prese a bordo della sua nave, almeno per un po’, poi...\nCredo che sarei rimasto con lui, ma dopo un paio di lune si scontrò con una pattuglia, perse un albero, fu travolto da una burrasca e trovò riposo sul fondo dell’anello esterno. Io, non so come, sopravvissi a tutto e mi unii alla compagnia dell’Isola Giustizia.";
			link.l1 = "Triste storia, non ho parole da aggiungere...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Ma certo che no. Perché è impossibile. Ho visto un uomo che tentò di lasciare questo dannato posto su una scialuppa... Tornò due giorni dopo. Legato a un relitto d'albero per non affogare. Era cianotico e decisamente morto.\nDunque dimmi, "+pchar.name+", che dovrei fare appena scappo da qui? L’Avana è troppo pericolosa per me, il patrigno cercherà di farmi fuori di nuovo. Non ho casa, né soldi. Dove dovrei andare? A battermi nel bordello?";
			link.l1 = "Eppure, desideri tornare nell'arcipelago?";
			link.l1.go = "ansewer_2_1";
		break;
		
		case "ansewer_2_1":
			dialog.text = "E secondo te? Certo che vorrei. Ma è impossibile, e ti ho appena spiegato il perché. Ah, se solo qualcuno potesse sistemare mio patrigno... con una lama affilata o una pallottola, allora forse avrei una speranza di tornare a vivere come la gente normale. Ma chi osi farlo, se il mio patrigno è il compare dell'alcalde dell'Avana? E poi, perché ne parliamo? Da qui non si scappa, amico...";
			link.l1 = "Vedremo. Verrà il momento...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
			// сюда направление на квест
		break;
		
		case "ansewer_3":
			dialog.text = "Vivo come posso. Non c’è altra scelta. I miei amici sono quasi tutti uomini, perché le nostre due bellezze da marito – Gillian e Tanneke – non mi sopportano per il mio carattere, e io non reggo la loro falsa virtù. Natalie era una brava ragazza, ma da quando ha cominciato a stare con quei tonti, la stupidità le si è appiccicata addosso.";
			link.l1 = "Capisco...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Lavoro come le altre ragazze. Il nostro compito principale è assistere gli uomini. Sull’Isola Giustizia c’è tanto da fare per le donne, quindi non mi manca mai da fare. E spesso ricevo regali, qui è consuetudine. Ma non pensare male di me, non sono una sgualdrina. Sono stata cresciuta in una famiglia rispettabile. Semplicemente non faccio finta di essere una santa, come fanno certe altre.";
			link.l1 = "Non ho mai pensato nulla di male su di te...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Che ci fai lì, eh? Ladro!","Guarda un po’! Appena m’ero perso nei miei pensieri, tu hai deciso di frugare nel mio baule!","Hai deciso di mettere il naso nei miei forzieri? Non la passerai liscia, canaglia!");
			link.l1 = "Maledizione!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Cosa?! Hai deciso di frugare nei miei forzieri? Non te la caverai così facilmente!";
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
			dialog.text = LinkRandPhrase("Ascolta, faresti meglio a mettere via quell’arma. Mi mette i nervi a fior di pelle.","Sai, qui non si tollera andare in giro con la lama sguainata. Riponila.","Ascolta, non fare il cavaliere medioevale che corre in giro con la spada sguainata. Mettila via, non fa per te...");
			link.l1 = LinkRandPhrase("D'accordo.","Certo.","Come dici tu...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Ascolta, sono cittadino di questa città e ti chiederei di tenere a bada la tua lama.","Ascolta, sono cittadino di questa città e ti chiederei di tenere a bada la tua lama.");
				link.l1 = LinkRandPhrase("D'accordo.","Certo.","Come dici tu...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Va' piano, compare, con quell'arma in mano. Potrei innervosirmi...","Non mi piace quando gli uomini mi passano davanti con l’arma sguainata. Mi mette i brividi...");
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
