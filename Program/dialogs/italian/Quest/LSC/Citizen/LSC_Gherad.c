// Гхерад Смиитс - матрос
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
				dialog.text = "Non voglio parlare con te. Assali civili innocenti senza motivo e li provochi a combattere. Sparisci dai miei occhi!";
				link.l1 = "Hm...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Buongiorno, compare, ah-ah! Che ci fai da queste parti?";
				link.l1 = TimeGreeting()+". Ti conosco, per caso?";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, "+GetFullName(pchar)+"! "+TimeGreeting()+"Che vuoi, forestiero?";
				link.l1 = LinkRandPhrase("Hai qualcosa di curioso da raccontare?","È successo qualcosa di nuovo sull’Isola Giustizia?","Mi racconti gli ultimi pettegolezzi?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Vorrei farti qualche domanda sull’isola.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Volevo solo sapere come te la passi. Ci vediamo!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Certo che no, ma si può rimediare facilmente, vero? Io sono Gerard Smeets, marinaio, un uomo di mare da Rotterdam. E tu hai proprio l’aria di un nostromo, non meno...";
			link.l1 = "Qualcosa del genere. Il mio nome è "+GetFullName(pchar)+" Piacere di conoscerti.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Somigli più a un armatore o a un contabile... Di certo sei un uomo d’ingegno. Lieto d’averti incontrato. Come sei giunto fin qui?";
			link.l1 = "Ho deciso di esplorare una zona sconosciuta. Dei bucanieri di Cuba mi hanno detto che c’era qualcosa da queste parti e ho pensato di andare a vedere di persona...";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "Sei l’unico sopravvissuto? Dove è affondata la tua nave? Vicino all’anello?";
			link.l1 = "Sono l’unico rimasto. E la mia tartana giace sul fondo del mare, non ha nemmeno raggiunto il cerchio.";
			link.l1.go = "meeting_3";
		break;
		
		case "meeting_3":
			dialog.text = "Capisco. Beh, sei bloccato qui per un po'. Fai visita a Sancho per un po' di rum, è una buona azione...";
			link.l1 = "Lo farò. A rivederci!";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Hai qualcosa di curioso da raccontare?","È successo qualcosa di nuovo sull’isola?","Mi racconti gli ultimi pettegolezzi?");
			link.l2.go = "rumours_LSC";
			link.l3 = "Vorrei farti alcune domande sull'isola.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Certo, amico. Ti sto ascoltando.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Dimmi, come sei giunto fin quaggiù?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Vuoi lasciare l’Isola e tornare alla tua vita normale?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "I clan non ti danno fastidio?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Come si è formata l’Isola Giustizia, hai qualche idea in merito?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Nessuna domanda. Perdona...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Sono arrivato qui con quell’imbecille tronfio di Abbot. Servivo sulla sua nave, sai? Gente come lui non dovrebbe mai mettere piede su un ponte: portano disgrazia. Solo il diavolo poteva farlo salpare con noi. Dovevamo solo andare dalla Giamaica a Belize, una passeggiata. Ma la sfortuna ci dava la caccia: il nostromo caduto fuori bordo, il navigatore che sbaglia rotta, maledetti spagnoli e per finire la tempesta. Ed eccoci qua.";
			link.l1 = "Interessante...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Vorrei saperlo, compare. Un tempo lo sapevo, ora più no. Qui la vita va, c’è rum e vino a fiumi, buon cibo — non tanto, ma meglio di quella sbobba che mangiavo a bordo, per mille balene.\nSull’Isola vivono anche brave persone. Gente con cui bere o scambiare due chiacchiere. Mi piace stare qui. Quindi non so nemmeno io… No, direi proprio che non voglio andarmene. Un tempo ero rabbioso e affamato, guarda la mia pancia ora, ah-ah!";
			link.l1 = "Magnifico! Son lieto per te.";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "No, non lo fanno. Basta che non litighi con loro e non entri nei loro territori senza permesso. Questo proprio non lo sopportano. I Narvali sono brava gente, la maggior parte è nata qui e non ha mai visto altro mondo. Molti di loro sono davvero abili, Jurgen Schmidt per esempio. È un dio della forgia!";
			link.l1 = "Capisco...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Facile come bere un bicchiere d’acqua. Banchi e scogli. L’anello esterno è fatto di navi, dal ponte fino alla chiglia. Le navi vengono trascinate dalla tempesta, sbattono sugli scogli o direttamente sull’anello esterno. Così cresce l’Isola. Ma perché quelle più interne restano a galla... questo non lo capisco proprio.";
			link.l1 = "Capisco...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Che stai facendo lì, eh? Ladro!","Guarda un po’! Appena mi sono perso nei miei pensieri, hai ben pensato di frugare nel mio baule!","Hai deciso di frugare nei miei scrigni? Non la passerai liscia, canaglia!");
			link.l1 = "Maledizione!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Cosa?! Hai deciso di frugare nei miei forzieri? Non te la caverai così facilmente!";
			link.l1 = "Ragazza sventata!";
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
			dialog.text = LinkRandPhrase("Ascolta, faresti meglio a riporre quell’arma. Mi mette a disagio.","Sai, qui non si tollera chi va in giro con la lama sguainata. Mettila via.","Ascolta, lascia perdere la parte del cavaliere errante con la spada. Mettila via, non fa per te...");
			link.l1 = LinkRandPhrase("Va bene.","Come desideri...","Come dici tu...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Ascolta, sono cittadino di questa città e ti chiederei di tenere a bada la tua lama.","Ascolta, sono cittadino di questa città e ti chiederei di tenere a bada la tua lama.");
				link.l1 = LinkRandPhrase("Va bene.","Come vuoi, allora.","Come dici tu...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Sta' attento, compare, a correre in giro armato. Mi fai venire i nervi...","Non mi piace quando gli uomini mi passano davanti con le armi in pugno. Mi mette i brividi...");
				link.l1 = RandPhraseSimple("Capito.","Lo porto via.");
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
