// Сесил Галард - бабулька
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
				dialog.text = "Non voglio parlare con te. Assali civili innocenti senza motivo e li provochi a menar le mani. Sparisci dai miei occhi!";
				link.l1 = "Hmm...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Desideri qualcosa, giovanotto?";
				link.l1 = TimeGreeting()+" Lascia che mi presenti - "+GetFullName(pchar)+". Sono un nuovo arrivato.";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, "+GetFullName(pchar)+"! "+TimeGreeting()+"Desideri qualcosa?";
				link.l1 = LinkRandPhrase("Hai qualcosa d’interessante da raccontare?","È successo qualcosa di nuovo sull’Isola Giustizia?","Mi racconterai gli ultimi pettegolezzi?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Vorrei farti alcune domande sull’isola.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Volevo solo sapere come te la passi. Ci si vede!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "A-ah, dunque stai facendo conoscenza con la nostra Isola Giustizia e la sua stramba ciurma, dico bene?";
			link.l1 = "Esattamente, signora?..";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Halard. Cecille Halard.";
			link.l1 = "Piacere d’incontrarvi, signora Halard! È un vero onore.";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "Anche la mia... E tu come sei arrivato qui, giovanotto? Non ricordo nessun naufragio recente...";
			link.l1 = "Mi hanno portato qui dalla Terraferma su una barca... ma è affondata proprio vicino alle rive dell’Isola Giustizia. Così sono rimasto senza nave.";
			link.l1.go = "meeting_3";
		break;
		
		case "meeting_3":
			dialog.text = "Una barca? Mi pare difficile crederci... Se è così, sei davvero fortunato ad essere arrivato fino all’Isola su quella carretta senza finire inghiottito da una tempesta. Le tempeste sono rare qui dentro, ma là fuori sono bestie feroci, ti colpiscono senza preavviso.\nDunque, ringrazia la sorte e abituati alle nostre strane abitudini! Non voglio buttarti giù, ma arrivare qua è uno scherzo rispetto ad andarsene: lascia stare i sogni, lasciare l’Isola è quasi una chimera. Non pensare che mi lamenti: da dieci anni nessuno è riuscito a scappare di qui vivo.";
			link.l1 = "Eppur cercherò d’esser un po’ più fiducioso. Lieto d’averti incontrato, spero di rivederti in giro!";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Sì, giovanotto?";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "E come sei arrivata qui, signora?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Vivi qui da tanto tempo, vero?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Che mi dici della gente del posto?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Puoi raccontarmi delle persone interessanti che vivono qui?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Nessuna domanda. Perdona...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Fu tanto tempo fa, dunque non ricordo davvero come sia successo. Naufragio, e poi basta...";
			link.l1 = "Capisco...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "A volte mi pare d’esser nato su quest’isola... Ma non è vero, ovviamente. Vivo qui da tutta la seconda metà della mia vita. E fu lunga, quella vita. E qui morirò, ché non ho alcuna voglia di lasciare questo posto.";
			link.l1 = "Capisco...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "E non c’è molto che possa dirti, giovanotto... qui siamo tutti diversi. Su quest’isola trovi di tutto – bianchi, neri, indiani, ex schiavi e nobili, galeotti e soldati. E prima ce n’erano ancora di più. Ognuno ha la sua storia e le sue abitudini. C’è chi se n’è fatto una ragione, e chi invece sogna ancora di tornare a casa. Così si tira avanti...";
			link.l1 = "Interessante...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "La gente più interessante qui sono: il meccanico-inventore dei Narvali, Herr Schmidt – armaiolo narvalo, Sancho Carpentero – l’oste indigeno. E adesso abbiamo pure l’ammiraglio con il suo secondo.";
			link.l1 = "Ci rifletterò su...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Cosa fai laggiù, eh? Ladro!","Ma guarda un po’! Appena m’ero perso nei miei pensieri, tu già frugavi nel mio baule!","Hai deciso di curiosare nei miei forzieri? Non te la caverai liscia, furfante!");
			link.l1 = "Maledizione!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Cosa?! Hai deciso di frugare nei miei forzieri? Non te la caverai così facilmente!";
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
			dialog.text = LinkRandPhrase("Ascolta, faresti meglio a mettere via quell’arma. Mi mette inquietudine.","Sai, qui non si tollera andare in giro con la lama sguainata. Riponila.","Ascolta, non fare il cavaliere medievale che corre in giro con la spada sguainata. Mettila via, non è roba per te...");
			link.l1 = LinkRandPhrase("Va bene.","Certo.","Come dite voi...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Ascolta, sono cittadino di questa città e ti chiederei di tenere a bada la tua lama.","Ascolta, sono un cittadino di questa città e ti chiederei di tenere a bada la tua lama.");
				link.l1 = LinkRandPhrase("Va bene.","Certo.","Come dici tu...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Fa' attenzione, compare, a correre in giro con l’arma sguainata. Potrei innervosirmi...","Non mi piace quando gli uomini camminano davanti a me con l’arma sfoderata. Mi mette paura...");
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
