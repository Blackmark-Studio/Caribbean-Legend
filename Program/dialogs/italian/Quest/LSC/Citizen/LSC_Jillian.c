// Джиллиан Стайнер - просто девушка
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
				dialog.text = "Non voglio parlare con te. Attacchi civili innocenti senza motivo e li provochi a menar le mani. Sparisci!";
				link.l1 = "Hm...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Oh... salve! Mi hai fatto prendere uno spavento. Sei arrivato così silenzioso... Che cosa vuoi?";
				link.l1 = TimeGreeting()+". Il mio nome è "+GetFullName(pchar)+". Sono appena arrivato su quest’isola e sto facendo conoscenza con la gente del posto. Alla fine ho deciso di venire a parlare con una dama così affascinante come te. Qual è il tuo nome?";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, "+GetFullName(pchar)+"! "+TimeGreeting()+" ! Desideri qualcosa?";
				link.l1 = LinkRandPhrase("Hai qualcosa di curioso da raccontare?","È successo qualcosa di nuovo sull’isola?","Mi racconterai gli ultimi pettegolezzi?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Vorrei farti qualche domanda su quest’isola.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Volevo solo sapere come te la passi. Ci si vede!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Mi fai arrossire, signore, ma è comunque un piacere. Grazie per il complimento. Mi chiamo Jillian, Jillian Steiner. Lietissima di fare la tua conoscenza.";
			link.l1 = "Anch’io, Jillian.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Sei nuovo da queste parti? E dimmi, come diavolo ci sei arrivato? Sei sopravvissuto al naufragio?";
			link.l1 = "Ebbene... più o meno così. Navigavo da queste parti su una barca e quasi avevo superato le scogliere, ma sfortunatamente ho urtato i relitti delle navi e la mia barca è affondata. Così sono arrivato a nuoto, con le mie sole forze.";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "Oh! Dunque sei venuto qui di tua spontanea volontà? Incredibile!";
			link.l1 = "Sì, sono proprio così folle. Ho deciso di trovare questa Isola Giustizia, e alla fine l’ho trovata. Anche se ora non ho la minima idea di come uscirne.";
			link.l1.go = "meeting_3";
		break;
		
		case "meeting_3":
			dialog.text = "Sei davvero coraggioso o dannatamente sconsiderato. Navigare fin qui su una barca... Ora vivrai con noi, perché nessuno è riuscito a lasciare questo posto nell’ultimo decennio.";
			link.l1 = "Conservo ancora una speranza. Va bene, Jillian, non ti disturbo più. Ci si rivede in giro!";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Sì, certo, "+pchar.name+". Sto ascoltando.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Come sei arrivato qui?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Vuoi lasciare l’Isola Giustizia?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "E come va la tua giornata? Che combini?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Dici di non essere sposata... Ma possibile che una fanciulla così bella non abbia spasimanti qui?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Nessuna domanda. Perdona...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Navigavo dall’Inghilterra coi miei genitori. Volevamo cominciare una vita nuova, e... una vita nuova l’ho davvero cominciata qui. I miei genitori son morti e io sono sopravvissuto per miracolo. Sono riuscito a raggiungere una nave del cerchio esterno e ci sono rimasto svenuto per un giorno intero, finché un isolano mi ha trovato lì. Fossi rimasto solo, sarei morto di certo.";
			link.l1 = "Capisco...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "E dove dovrei andare? Chi mai avrebbe bisogno di me, e dove? Non ho casa, né marito, né un soldo bucato. Non sono mai stata altrove se non su quest’Isola Giustizia e nei bassifondi di Londra. Pare proprio che il mio destino sia restare qui...";
			link.l1 = "Ne sei proprio sicuro?";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Mi occupo soprattutto di aiutare fratello Giuliano in chiesa. Faccio anche qualche lavoretto semplice nella bottega di Axel. Così mi guadagno le monete. Son pur sempre una ragazza, e andare a rovistare tra i relitti delle navi sull’anello esterno non fa per me.";
			link.l1 = "Certo...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Ih ih... ci sono ammiratori, sì, ma nessuno che valga davvero. Non me ne piace nessuno, e non voglio vivere con un uomo che non mi va. Quelli che mi piacciono manco mi degnano d’uno sguardo. Eh, son solo una povera ragazza qualunque...";
			link.l1 = "È solo l’inizio d’una nuova vita per te...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Che fai laggiù, eh? Ladro!","Guarda un po’! Appena ho perso lo sguardo nei miei pensieri, tu hai già ficcato il naso nel mio baule!","Hai deciso di ficcare il naso nei miei forzieri? Non la passerai liscia!");
			link.l1 = "Merda!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Cosa?! Hai deciso di ficcare il naso nei miei forzieri? Non te la caverai così!";
			link.l1 = "Stolta fanciulla!";
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
			dialog.text = LinkRandPhrase("Ascolta, faresti meglio a rimettere via quell’arma. Mi mette agitazione.","Sai, qui non si tollera andare in giro con la lama sguainata. Riponila.","Ascolta, piantala di fare il cavaliere errante con la spada sguainata. Mettila via, non fa per te...");
			link.l1 = LinkRandPhrase("Va bene.","D'accordo.","Come dici tu...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Ascolta, sono cittadino di questa città e ti chiederei di tenere a bada la tua lama.","Ascolta, sono cittadino di questa città e ti chiederei di tenere a bada la tua lama.");
				link.l1 = LinkRandPhrase("D'accordo.","Come vuoi, allora.","Come dici tu...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Attento, compare, a correre in giro armato. Potrei agitarmi...","Non mi piace quando gli uomini mi passano davanti con l’arma sguainata. Mi mette i brividi...");
				link.l1 = RandPhraseSimple("Capito.","La sto portando via.");
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
