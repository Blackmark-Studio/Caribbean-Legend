// Виктор Кассель - бандит
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
				dialog.text = "Non voglio parlare con te. Assalti civili innocenti senza motivo e li provochi a combattere. Sparisci!";
				link.l1 = "Hm...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Hm... Che vuoi, compare? Se sei qui per chiacchierare, ti deluderò. Non ho né voglia né tempo di parlare.";
				link.l1 = "Peccato... Avevo voglia di fare due chiacchiere. Sono appena arrivato qui e sto ancora conoscendo la gente...";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, "+GetFullName(pchar)+"! Che vuoi, forestiero?";
				link.l1 = LinkRandPhrase("Hai qualcosa di curioso da raccontare?","È successo qualcosa di nuovo sull’Isola Giustizia?","Mi racconterai gli ultimi pettegolezzi?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Vorrei farti alcune domande sull'isola.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Volevo solo sapere come te la passi. A presto!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Un nuovo arrivato? Hm. Va bene allora. Sono Victor Cassel e fareste meglio a non farmi arrabbiare, sia che abbia il broncio sia che sia di buonumore. Non perdo tempo in chiacchiere, tiro un pugno subito a chi mi pressa troppo. ";
			link.l1 = "Ebbene, ed io sono "+GetFullName(pchar)+"Ah, e comunque, so restituire i colpi senza problemi. Ma spero proprio non ce ne sarà bisogno, eh. Non ti romperò le scatole, se sei così poco incline alla compagnia. Addio.";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Hai qualcosa d’interessante da raccontare?","È successo qualcosa di nuovo sull'isola?","Mi racconti gli ultimi pettegolezzi?");
			link.l2.go = "rumours_LSC";
			link.l3 = "Vorrei farti qualche domanda su quest’isola.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Ah sì? E che vuoi che ti dica?";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Come sei arrivato qui?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Com’è la vita da queste parti?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Chi è la persona più... importante qui?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "E dove posso procurarmi delle monete sull'Isola Giustizia?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Nessuna domanda. Perdona...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Mi spiace, amico, ma che t’importa? Son appena arrivato anch’io. Non intendo parlar di quella faccenda, men che meno con uno che non conosco.";
			link.l1 = "Ebbene, mi rincresce...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Sembra una noia mortale. Stancante, insulso e senza senso. Ho deciso di unirmi ai pirati dello Squalo, quei ragazzi valgono la pena. Salirò sulla loro ciurma con gran piacere, ma prima devo... guardarmi un po’ intorno. Son certo che troveranno la via per scappare dall’Isola.";
			link.l1 = "Davvero? Capisco...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = " Ammiraglio, senza dubbio! I pirati tengono Narvali e Rivados nel suo pugno e i clan non osano fiatare. Subito dopo vengono i capi dei clan, Donald Greenspy dei Narvali e Black Eddy dei Rivados. Axel Yost – un mercante dei Narvali – è un uomo di gran peso pure lui. E poi c’è Sancho Carpentero, un bravo ragazzo, quello...";
			link.l1 = "Capisco...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Scrigni. Eh già, prima li devi aprire, qui nessuno si fida di nessuno, così tutti gli scrigni han la serratura. Ti dico una cosa, compare: i gingilli migliori li tengono nascosti nelle stive, sorvegliati dai loro padroni.\nPuoi anche esplorare l’anello esterno, ma prega di non sprofondare nel legno marcio. Oppure puoi dar la caccia ai granchi giganti: la carne delle loro chele si vende a peso d’oro.";
			link.l1 = "Capito...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Cosa stai facendo lì, eh? Ladro!","Guarda un po’! Mentre m’ero perso nei miei pensieri, tu hai deciso di frugarmi nel baule!","Hai deciso di frugare nei miei forzieri? Non la passerai liscia, furfante!");
			link.l1 = "Merda!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Cosa?! Hai deciso di ficcare il naso tra i miei forzieri? Non la passerai liscia!";
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
			dialog.text = LinkRandPhrase("Ascolta, faresti meglio a rimettere via la tua arma. Mi mette a disagio.","Sai, qui non si tollera andare in giro con la lama sguainata. Mettila via.","Ascolta, lascia stare il ruolo di cavaliere medievale che corre in giro con la spada. Mettila via, non fa per te...");
			link.l1 = LinkRandPhrase("Va bene.","Va bene.","Come dici tu...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Ascolta, sono un cittadino della città e ti chiederei di tenere a bada la tua lama.","Ascolta, sono cittadino di questa città e ti chiederei di tenere la lama nel fodero.");
				link.l1 = LinkRandPhrase("Va bene.","Va bene.","Come dici tu...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Va’ piano, compare, con quell’arma in pugno. Potrei innervosirmi...","Non mi piace quando gli uomini mi passano davanti con l’arma in pugno. Mi mette i brividi...");
				link.l1 = RandPhraseSimple("Afferrato.","La sto portando via.");
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
