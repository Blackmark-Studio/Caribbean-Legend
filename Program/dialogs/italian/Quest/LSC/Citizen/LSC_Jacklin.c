// Жаклин Тьюрам - торговый капитан
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
				dialog.text = "Non voglio parlare con te. Attacchi civili innocenti senza motivo e li provochi a menar le mani. Sparisci dai piedi!";
				link.l1 = "Hm...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Buon dì, messere. Sei nuovo qui, vero?";
				link.l1 = TimeGreeting()+"Sì, suppongo d'essere il più nuovo qui. Il mio nome è "+GetFullName(pchar)+" . E qual è il tuo?";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, "+GetFullName(pchar)+"! "+TimeGreeting()+" ! Vuoi qualcosa?";
				link.l1 = LinkRandPhrase("Hai qualcosa di intrigante da raccontare?","È successo qualcosa di nuovo sull’isola?","Mi racconterai gli ultimi pettegolezzi?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Vorrei farti qualche domanda sull’isola.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Volevo solo sapere come te la passi. Ci si vede!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Jacqueline Turam. Due anni addietro ero una mercantessa rispettabile e benestante, padrona e capitana della mia flûte. Ahimè, ora son povera come un topo in chiesa e non nutro speranza che la sorte mi sorrida mai\nC’è chi qui ha fortuna—chi trova gioielli, oro, navi cariche di tesori—ma io non sono tra quelli. Io ho trovato soltanto uno scrigno di dobloni e qualche cianfrusaglia\nAlmeno bastano per comprarmi da mangiare e non morir di fame... Lieto d’incontrarvi, messere, non mi dispiace affatto scambiare due parole...";
			link.l1 = "Felice d’incontrarti anch’io, Jacqueline. A presto!";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Hai qualche storia interessante da raccontare?","È successo qualcosa di nuovo sull'isola?","Mi racconterai gli ultimi pettegolezzi?");
			link.l2.go = "rumours_LSC";
			link.l3 = "Voglio farti qualche domanda sull’isola.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Sono tutto orecchi.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Come sei giunto fin qui?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Cosa fai qui, forestiero?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Dimmi, vedo che sull’Isola ci sono fanciulle e donne...";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Vuoi tornare laggiù, nel vasto mondo?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Non è nulla.";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Vuoi ascoltare la mia storia? Va bene. Come già sai, ero un capitano mercantile. Un giorno partii da Tortuga per Belize con il mio vecchio flauto fedele. Le stive erano colme di legno nero e cacao, avevo speso fino all'ultimo doblone per quel carico.\nAvevo combinato un affare d’oro con un tizio, voleva comprarmi tutto a un prezzo da usuraio. Potevo arricchirmi su quel colpo. Tutto filava liscio, non una nuvola in cielo, la mia nave filava come una rondine. Niente lasciava presagire tempesta.\nVeleggiavo vicino a Cuba, girando largo dalle pattuglie spagnole, quando d’improvviso ci assaltò un galeone di filibustieri. Che ci facevano quei cani laggiù, in pieno territorio spagnolo? Cercammo di scappare, ma fu inutile, quel galeone andava come il vento.\nI pirati si lanciarono all’arrembaggio. Le loro colubrine sputavano mitraglia, la prima bordata fece strage tra i miei uomini e li gettò nello sconforto. Volevo difendere la nave, ma i miei stessi ufficiali e marinai mi fermarono. Ci arrendemmo.\nI filibustieri presero il carico in un lampo e gettarono i nostri cannoni a mare. Credevo fosse la fine. Perdere il carico era un colpo duro, ma avrei potuto rifarmi con altri viaggi e, un giorno, rialzarmi.\nIl destino invece volle altro. Quei maledetti pirati aprirono il fuoco sulla mia povera nave disarmata. Eravamo bersagli perfetti.\nSento ancora le loro risate... Il galeone sparì e noi restammo a boccheggiare tra i relitti. Poi si levò una burrasca con onde nere e da allora non ho più visto anima viva del mio equipaggio. Riuscii a legarmi a un pezzo d’albero e a restare a galla.\nTi risparmio i dettagli sull’attacco degli squali. Dopo un tempo che pareva eterno, la corrente mi ha trascinato qui. È così che sono sopravvissuto.";
			link.l1 = "Sì, è davvero una storia triste.";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Vivo come gli altri isolani – semplicemente vivo. Cerco qualche cosa di prezioso nella parte esterna e lo scambio per un tozzo di pane. Sogno di trovare un forziere d’un re indiano pieno di tesori... O almeno un galeone carico d’oro spagnolo, ahah. Non badarci troppo, sono solo io\nSogno di mangiare qualcosa che non sia sempre carne salata o pesce. Eh, c’era un tipo qui che cacciava quei granchi giganti. Gli davo cinque dobloni per una chela e ci campavo diversi giorni\nPeccato che il cacciatore sia passato a miglior vita... anche se non posso dire che fosse una sorpresa – dare la caccia a quelle bestie è una follia.";
			link.l1 = "Capisco...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Capisco dove vuoi arrivare. Sì, amori e intrighi non mancano qui. E perché mai dovrebbero? L’uomo è fatto per la donna, e la donna per l’uomo. Natura, capitano. Se vuoi provarci, fatti avanti con Gillian o Tanneke. Sono giovani, belle e non si tirano indietro davanti a una corte.\nIo invece ho già trovato la mia fortuna: Natalia. Fa la cameriera alla taverna di Sancho. Una gran donna, credimi. Forse è solo grazie a lei che non sono impazzito nei primi mesi su questa dannata isola. Mi ha aiutato molto e ora siamo insieme.";
			link.l1 = "Hmm... Ci sono arrivato!";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Domanda saggia. Mi piacerebbe, certo. Ma a pensarci bene... sono a pezzi. Ho investito tutto nel carico e la mia nave è affondata. Non mi è rimasto nulla per campare. L’unica speranza di guadagnare qualcosa è lavorare per la Compagnia Olandese delle Indie Occidentali, se mai mi prendessero, ovvio.\nSe solo avessi abbastanza monete per comprare una goletta e viveri a sufficienza... Ma tanto vale restare sull’Isola. Almeno qui non devo sgobbare da mattina a notte solo per un tozzo di pane.";
			link.l1 = "Capisco...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Che fai laggiù, eh? Ladro!","Guarda un po’! Appena mi sono perso nei miei pensieri, tu hai pensato bene di frugare nel mio forziere!","Hai deciso di curiosare fra i miei forzieri? Non la passerai liscia, canaglia!");
			link.l1 = "Maledizione!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Cosa?! Hai deciso di frugare nei miei forzieri? Non ci riuscirai, maledetto!";
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
			dialog.text = LinkRandPhrase("Ascolta, faresti meglio a mettere via quell’arma. Mi mette a disagio.","Sai, qui non si tollera correre con la lama sguainata. Riponila.","Ascolta, non fare il cavaliere d’altri tempi che corre brandendo la spada. Mettila via, non fa proprio per te...");
			link.l1 = LinkRandPhrase("Bene.","D’accordo.","Come dici tu...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Ascolta, sono cittadino di questa città e ti chiederei di tenere a bada la tua lama.","Ascolta, sono un cittadino della città e ti chiederei di tenere a bada la tua lama.");
				link.l1 = LinkRandPhrase("Va bene.","E sia, allora.","Come dici tu...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Attento, compare, a correre in giro con l’arma sfoderata. Mi fai venire i nervi...","Non mi piace quando gli uomini mi passano davanti con l’arma sguainata. Mi mette i brividi...");
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
