// Дугал Эббот - дворянин
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
				dialog.text = "Non voglio parlare con te. Attacchi povera gente senza motivo, provochi solo risse. Sparisci dai miei occhi!";
				link.l1 = "Hm...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Salute a voi, messere. Permettetemi di presentarmi: Dougall Abbot. È un piacere vedere un uomo di rango da queste parti. Sono stufo di questa plebaglia locale. Giammai avrei pensato di dover passare il resto dei miei giorni tra la gente comune.";
				link.l1 = TimeGreeting()+"... Il mio nome è "+GetFullName(pchar)+"È un piacere incontrarti. E perché non ti stanno simpatici i locali?";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, "+GetFullName(pchar)+"! "+TimeGreeting()+" ! Vuoi qualcosa?";
				link.l1 = LinkRandPhrase("Hai qualcosa di curioso da raccontare?","È successo qualcosa di nuovo sull’isola?","Mi racconterai gli ultimi pettegolezzi?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Vorrei farti qualche domanda sull'isola.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Volevo solo sapere come te la passi. Ci vediamo!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Non li conosci bene. Sei appena sbarcato qui? Però non ricordo nessun naufragio recente...";
			link.l1 = "Sono arrivato qui su una piccola barca...";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Sì, accade spesso – le navi affondano e solo pochi superstiti arrivano qui sulle scialuppe. A volte la gente rimane su quest’isola per mesi e non li incontri mai.";
			link.l1 = "Capisco. È stato un piacere conoscerti, messer Abbot. A presto!";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Hai qualche storia interessante da raccontare?","È successo qualcosa di nuovo sull'isola?","Mi svelerai le ultime chiacchiere del porto?");
			link.l2.go = "rumours_LSC";
			link.l3 = "Vorrei farti alcune domande sull'isola.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Ascolto.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "E come sei arrivato fin qui?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Cosa mi puoi raccontare della gente del posto?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Cosa puoi raccontarmi delle confraternite?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "E del tempo? Le tempeste qui sono frequenti?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Nessuna domanda. Perdona...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Era cinque anni fa, ma lo ricordo come fosse successo ieri. Quel giorno sciagurato decisi di salpare con la mia flûte da Port Royal verso Belize, il carico era troppo prezioso per affidarlo ad altri, capisci?\nIl giorno dopo cominciarono le mie sventure: prima, il nostromo si ubriacò e cadde fuori bordo, poi per poco non finimmo sugli scogli, e alla fine il nostro navigatore sbagliò rotta, così ci ritrovammo a veleggiare verso l’ignoto.\nPoi ci si misero addosso un brigantino e un galeone. Provammo a seminarli, ma erano cocciuti. Il galeone restò indietro, ma il brigantino ci raggiunse infine.\nIl galeone era troppo lontano, così abbordammo il brigantino senza sparare un colpo. Quei cani spagnoli non se lo aspettavano e vincemmo la mischia, ma la maggior parte della mia ciurma finì stecchita.\nPoche ore dopo, fu la tempesta a colpirci. Con così pochi uomini non potevamo reggere il mare, e il risultato lo vedi adesso. La mia flûte sarà da qualche parte sull’anello esterno, io e gli altri tre superstiti siamo arrivati qui.";
			link.l1 = "Capito...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Feccia. Tutti quanti. Gentaglia d’ogni sorta. Richard Shambon è un delinquente, lo si legge in faccia. Kassel? Ammazzare per lui è come respirare. Jasper Pratt è uno scellerato. Musket è un ubriacone. Vuoi che continui?\nJosef Loderdale è l’unico uomo a posto qui, a parte te; ex marina reale inglese. Due nobili stanno qui – Antonio Betancourt e Lorenzo Solderra, spagnoli maledetti, non mi sederei mai a tavola con loro.";
			link.l1 = "Capisco...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Un branco di canaglie e feccia. Però non ci fanno del male. Sono più occupati a pugnalarsi e spararsi tra di loro. Senza risse non sanno stare. Neanche a me piacciono quei pirati, ma devo ammettere che da quando sono arrivati l’Isola è più tranquilla.";
			link.l1 = "Interessante...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Non lo fanno mai. Le tempeste infuriano spesso attorno all’Isola Giustizia, ma qui regna sempre una quiete strana, come se fosse opera di qualche magia... o forse è la mano di Dio, chissà. Al massimo, a volte arriva una folata più forte e tutto finisce lì. Nemmeno la pioggia riesce a farci davvero del male.";
			link.l1 = "Interessante...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Che stai combinando là, eh? Ladro!","Guarda un po’! Appena mi sono perso nei miei pensieri, tu hai pensato bene di rovistare nel mio baule!","Hai deciso di frugare nei miei forzieri? Non la passerai liscia!");
			link.l1 = "Maledizione!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Cosa?! Ti sei messo a frugare nei miei forzieri? Non te la caverai così facilmente!";
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
			dialog.text = LinkRandPhrase("Ascolta, faresti meglio a mettere via quell’arma. Mi mette un certo disagio.","Sai, qui non si tollera girare con la lama sguainata. Riponila.","Ascolta, non fare il paladino con la spada sguainata. Mettila via, non ti dona proprio...");
			link.l1 = LinkRandPhrase("Va bene.","Va bene.","Come dici tu...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Ascolta, sono cittadino di questa città e ti chiederei di tenere a bada la tua lama.","Ascolta, sono un cittadino della città e ti chiederei di tenere a bada la tua lama.");
				link.l1 = LinkRandPhrase("Bene.","Come vuoi, allora.","Come dici tu...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Stai attento, compare, a girare armato. Mi viene facile perdere la calma...","Non mi piace quando gli uomini mi passano davanti con l’arma in pugno. Mi mette i brividi...");
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
