// Лоренцо Сольдерра - испанский военный офицер
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sTemp;

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
				dialog.text = "Non voglio parlare con te. Assali gente innocente senza motivo e li provochi a menar le mani. Sparisci!";
				link.l1 = "Uhm...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Hm, sei francese? Non credo che abbiamo molto da dirci, noi due.";
				link.l1 = "Interessante, e perché no? Credo che qui sull’Isola Giustizia si possa benissimo dimenticare le vecchie inimicizie tra nazioni...";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, "+GetFullName(pchar)+"! "+TimeGreeting()+" ! Desideri qualcosa?";
				link.l1 = LinkRandPhrase("Hai qualcosa di curioso da raccontare?","È successo qualcosa di nuovo sull'isola?","Mi racconterai gli ultimi pettegolezzi?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Vorrei farti alcune domande su quest’isola.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Volevo solo sapere come te la passi. A presto!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "E non lo credo proprio. Sono un ufficiale della marina e non voglio aver nulla a che fare con i nemici di Escorial né in Europa, né nell’arcipelago, né qui, né altrove. Prosegui per la tua strada, signore!";
			link.l1 = "Eh. Come desideri...";
			link.l1.go = "exit";
			NextDiag.TempNode = "meeting_no";
		break;
		
		case "meeting_no":
			dialog.text = "Pensavo che fosse chiaro: non parlo con i nemici della Spagna!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "meeting_no";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Ascolto.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Nessuna domanda. Perdona...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Che stai facendo lì, eh? Ladro!","Guarda un po’! Appena m’hai visto perso nei miei pensieri, t’è venuta voglia di rovistare nel mio baule!","Hai deciso di frugare nei miei forzieri? Non la passerai liscia, maledetto!");
			link.l1 = "Maledizione!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Cosa?! Hai deciso di frugare nei miei scrigni? Non te la caverai così facilmente!";
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
			dialog.text = LinkRandPhrase("Ascolta, sarebbe meglio che mettessi via la tua arma. Mi mette a disagio.","Sai, qui non è ben visto andarsene in giro con la lama sguainata. Riponila.","Ascolta, non fare il cavaliere medievale che corre brandendo la spada. Mettila via, non è roba tua...");
			link.l1 = LinkRandPhrase("D’accordo.","D'accordo.","Come dici tu...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Ascolta, sono cittadino della città e ti chiederei di tenere a bada la tua lama.","Ascolta, sono un cittadino di questa città e ti chiederei di tenere a bada la tua lama.");
				link.l1 = LinkRandPhrase("Va bene.","D’accordo.","Come dici tu...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Sta' attento, compare, a correre con l’arma in mano. Mi fai venire i nervi...","Non mi piace quando gli uomini camminano davanti a me con l’arma sguainata. Mi mette i brividi...");
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
