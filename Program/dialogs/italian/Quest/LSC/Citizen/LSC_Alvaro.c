// Альваро Гомец - капитан
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
				dialog.text = "Non voglio parlare con te. Attacchi civili innocenti senza motivo e li provochi a combattere. Sparisci dalla mia vista!";
				link.l1 = "Hm...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Oh, una faccia nuova! Saluti. E quand’è che sei sbarcato? Non ricordo nessun naufragio recente.";
				link.l1 = TimeGreeting()+". Il mio nome è "+GetFullName(pchar)+". E la mia nave è affondata così silenziosa e rapida che nessuno se n’è accorto. E sono arrivato all’Isola Giustizia altrettanto in fretta e senza rumore. Proprio così...";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, "+GetFullName(pchar)+"! "+TimeGreeting()+" ! Desideri qualcosa?";
				link.l1 = LinkRandPhrase("Hai qualcosa di curioso da raccontare?","È successo qualcosa di nuovo sull’Isola Giustizia?","Mi racconti gli ultimi pettegolezzi?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Vorrei farti alcune domande sull'isola.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Volevo solo sapere come te la passi. A presto!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Capisco, ah, mi sono scordato di presentarmi. Perdonami, señor. Mi chiamo Alvaro Gomez, un tempo ero capitano di una mia bricca. Eh, ora la mia splendida nave giace sul fondo, proprio dietro l’anello esterno... Da allora, tanta acqua è passata sotto i ponti. Bah, fa niente. Lieto d’incontrarti!";
			link.l1 = "Felice di fare la vostra conoscenza, señor Gomez.";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Hai qualcosa di curioso da raccontare?","È successo qualcosa di nuovo sull’isola?","Mi racconterai gli ultimi pettegolezzi?");
			link.l2.go = "rumours_LSC";
			link.l3 = "Vorrei farti alcune domande sull'isola.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Ascolto, signore.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Hai detto d’esser stato capitano. Come sei finito sull’isola?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Che mi racconti della vita su quest’isola?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Dimmi, la gente del posto qui vive in pace oppure no? Non parlo certo dei clan, sia chiaro.";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "E da dove si procurano i viveri, questi isolani?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Nessuna domanda. Perdono...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Come tutti gli altri, del resto. La tempesta m’ha ghermito, ho perso l’albero e il timone. La corrente ci ha trascinati e ci ha scaraventato sugli scogli. La mia nave non è nemmeno arrivata all’anello esterno: s’è sfasciata tutta. Solo pochi dei miei sono sopravvissuti.";
			link.l1 = "Triste storia...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Che posso dire? Qui abbiamo tutto ciò che serve per vivere decentemente. Anche se, a volte, la noia diventa una bestia feroce. E quella malinconia... Il primo anno è stato un vero supplizio, poi ci ho fatto il callo. Povera mia moglie Sabrina, chissà cosa pensa, sicuramente mi crede morto. Spero con tutto il cuore che sia riuscita a risposarsi.\nNon ti crucciare, ti abituerai anche tu. Vai alla taverna, al negozio, alla chiesa, conosci la gente del posto. Ma evita i Narvali e i Rivados finché puoi: sono canaglie furbe, quelle.";
			link.l1 = "Capisco...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Vero, risse e zuffe sono segretamente vietate qui. Se picchi qualcuno senza un valido motivo o, Dio non voglia, uccidi, finirai isolato. Potrebbero perfino gettarti in mare una notte. Già ce n'erano alcuni rissosi sull’Isola: il primo sparì nel nulla, il secondo crepò nella cella del Tartaro dopo mesi di reclusione.\Certo, non vuol dire che tu non possa difenderti. Ma la gente del posto è davvero pacifica. Abbott è uno spaccone, ma non aggressivo. Kassel è un vero mascalzone, ma si tiene le mani pulite. Pratt è un ex galeotto, ma innocuo.\Abbiamo due ex ufficiali di marina qui – Loderdale e Solderra. Sono finiti qui dopo uno scontro non lontano. Ironia della sorte, sono sopravvissuti entrambi solo per continuare a tramare l’uno contro l’altro.";
			link.l1 = "Capito...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Dalle stive, naturalmente. Tutte le provviste, raccolte dalle altre navi, venivano tenute a Sant'Agostino e poi spartite tra tutti, finché non sono arrivati quei dannati pirati. Ora tengono l’Isola Giustizia stretta nel pugno, perché controllano le scorte.\nCerto, abbiamo le nostre riserve nascoste, quindi ce la caviamo. Cacciamo uccelli, peschiamo... Ma la caccia migliore è quando si abbatte un granchio gigante. Hanno una carne saporita e che ti rimette in piedi. Peccato che si vedano solo all’anello esterno dell’isola.\nTuffarsi per cacciarli è una pazzia. C’era uno che aveva fegato a sufficienza per inseguirli sott’acqua. Un giorno, fu lui stesso la preda. Da allora, nessuno osa più andare a caccia di granchi laggiù.";
			link.l1 = "Interessante...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Che diavolo fai lì, eh? Ladro!","Guarda un po’! Appena m’ero perso nei miei pensieri, tu hai deciso di ficcare il naso nel mio baule!","Hai deciso di frugare nei miei forzieri? Non la passerai liscia, canaglia!");
			link.l1 = "Maledizione!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Cosa?! Hai deciso di frugare tra i miei scrigni? Non la passerai liscia, maledetto!";
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
			dialog.text = LinkRandPhrase("Ascolta, faresti meglio a mettere via quell’arma. Mi mette inquietudine.","Sai, qui non tolleriamo chi va in giro con la lama sguainata. Mettila via.","Ascolta, non fare il cavaliere medievale che corre in giro con la spada. Mettila via, non fa per te...");
			link.l1 = LinkRandPhrase("Va bene.","Certo.","Come dici tu...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Ascolta, sono cittadino di questa città e ti chiederei di tenere a bada la tua lama.","Ascolta, sono cittadino di questa città e ti chiederei di tenere a bada la tua lama.");
				link.l1 = LinkRandPhrase("Bene.","Allora, sia come vuoi.","Come dici tu...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Sta' attento, compare, a correre in giro con l’arma in pugno. Potrei agitarmi...","Non mi piace quando gli uomini camminano davanti a me con l’arma sguainata. Mi mette i brividi...");
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
