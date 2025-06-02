// Куранай - индеец
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
				dialog.text = "Non voglio parlare con te. Assali civili innocenti senza motivo e li provochi a menar le mani. Sparisci!";
				link.l1 = "Hm...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Cosa desidera il fratello bianco?";
				link.l1 = TimeGreeting()+" Fratello bianco? Dimmi, perché voi indiani ci chiamate o fratelli bianchi o cani dalla faccia pallida, eh?";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, "+GetFullName(pchar)+"! "+TimeGreeting()+"Vuoi qualcosa?";
				link.l1 = LinkRandPhrase("Hai qualcosa di curioso da raccontare?","È successo qualcosa di nuovo sull’isola?","Mi racconterai gli ultimi pettegolezzi?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Vorrei farti alcune domande su quest'isola.";
				link.l2.go = "int_quests"; //информационный блок
				if (CheckAttribute(npchar, "quest.answer_2"))
				{
					link.l3 = "Mostrami cosa sei riuscito a trovare. Magari ci potrei comprare qualcosa...";
					link.l3.go = "trade";
				}
				link.l5 = "Volevo solo sapere come te la passi. A presto!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Viviamo tutti in pace qui, fratello bianco. Curanai non chiama fratello bianco il muso pallido cane. Non tutti i musi pallidi sono cani. Posso chiamare più d’un indiano cane dalla pelle rossa.";
			link.l1 = "Hm. Immagino tu sia un filosofo...";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "I Curanai non capiscono te, fratello bianco. Che vuol dire filosofo?";
			link.l1 = "Non importa, fratello dalla pelle rossa. Mi piace il tuo modo di ragionare. Dici che ti chiami Curanai? Io sono "+GetFullName(pchar)+". Lieto d’incontrarti.";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "Curanai lieto di conoscere il nome del fratello bianco.";
			link.l1 = "Va bene. Ci si vede in giro!";
			link.l1.go = "exit";
			link.l3 = "Vorrei farti alcune domande sull’isola.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
		case "trade":
			DialogExit();
			if (!CheckAttribute(npchar, "trade_date") || GetNpcQuestPastDayParam(npchar, "trade_date") >= 4)
			{
				GiveItemToTrader(npchar);
				SaveCurrentNpcQuestDateParam(npchar, "trade_date");
			}
			LaunchItemsTrade(npchar, 0);
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Chiedi, fratello dalla pelle chiara, Curanai risponde.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Come sei finito qui?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Cosa fai sull'Isola Giustizia?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Vuoi tornare a casa?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Vivi in pace sull’Isola Giustizia? Succede mai che qui scoppino risse o litigi?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Nessuna domanda. Perdona...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Io e diversi guerrieri della mia tribù decidemmo di salpare verso una piccola isola vicino alle nostre terre, visibile nei giorni limpidi. Costruimmo una zattera di bambù e una vela. Ma la tempesta ci colse all’improvviso e ci trascinò in mare aperto. Non ci rendemmo conto di quanto in fretta la nostra terra e l’isola svanirono\nNavigammo per mare molte, moltissime notti e giorni. Tutti i miei fratelli morirono di sete e fame. Rimasi solo – gli spiriti ebbero pietà di Curanai e spinsero la zattera su quest’isola. Sopravvissi.";
			link.l1 = "Già... Una storia triste.";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Curanai pesca. Curanai colpisce i pesci con l’arpione. Raramente-raremente prende un grosso granchio. Allora Curanai è felice – il granchio è buono, molto buono. Una sola chela basta per diversi giorni. E Curanai si tuffa anche sul fondo in un posto. Nessun granchio grosso lì. Curanai raccoglie pietra gialla, pietra blu, pietra nera e perle. Grandi e piccole. Poi Curanai le vende ai visi pallidi.";
			link.l1 = "Capisco...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Curanai vorrebbe tornare a casa. Ma dov’è la mia casa? Curanai non sa dov’è il suo villaggio, né come ci si arriva.";
			link.l1 = "Hm. Che posso dire...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "I Narvali e i Rivados si azzuffano spesso fra loro. Noi viviamo in pace, non facciamo male a nessuno. A volte i visi pallidi bevono acqua di fuoco e bestemmiano, ma omicidi non ce ne sono. Ci sono due guerrieri-capitani, uno odia l’altro. Un giorno, uno finirà per uccidere l’altro. Curanai lo sa.";
			link.l1 = "Capisco...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Che fai lì, eh? Ladro!","Guarda un po’! M’è bastato perdermi nei miei pensieri, che tu già frughi nel mio forziere!","Hai deciso di ficcare il naso nei miei forzieri? Non la passerai liscia, canaglia!");
			link.l1 = "Maledizione!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Cosa?! Hai deciso di frugare nei miei forzieri? Non la passerai liscia, maledetto!";
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
			dialog.text = LinkRandPhrase("Ascolta, faresti meglio a mettere via la tua arma. Mi mette a disagio.","Sai, qui non si tollera chi gira con la lama sguainata. Riponila.","Ascolta, non fare il cavaliere medievale che corre in giro con la spada sguainata. Mettila via, non fa per te...");
			link.l1 = LinkRandPhrase("Va bene.","Certo.","Come vuoi tu...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Ascolta, sono cittadino di questa città e ti chiederei di tenere a bada la tua lama.","Ascolta, sono cittadino di questa città e ti chiederei di tenere a bada la lama.");
				link.l1 = LinkRandPhrase("Va bene.","Allora, sia come sia.","Come dite voi...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Attento, amico, a correre con l’arma in pugno. Potrei innervosirmi...","Non mi piace quando gli uomini mi passano davanti con l’arma sguainata. Mi mette i brividi...");
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
