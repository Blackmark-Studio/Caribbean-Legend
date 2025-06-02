// Джозеф Лодердэйл - английский военный офицер
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
				dialog.text = "Non voglio parlare con te. Attacchi povera gente innocente senza motivo e li provochi a menar le mani. Sparisci dai miei occhi!";
				link.l1 = "Hmm...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Buon dì, signore. Mi rallegra incontrare un uomo nobile in questo luogo.";
				link.l1 = TimeGreeting()+" In verità, stando così vicino alla gente comune durante la mia permanenza all’Arcipelago, ho quasi iniziato a scordarmi della mia nobiltà...";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = TimeGreeting()+", "+GetFullName(pchar)+"! Lieto d'incontrarti! Cosa vuoi dire?";
				link.l1 = LinkRandPhrase("Hai qualche storia da raccontare, forestiero?","È successo qualcosa di nuovo sull’isola?","Mi racconterai gli ultimi pettegolezzi?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Vorrei farti qualche domanda su quest’isola.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Volevo solo sapere come te la passi. Ci si rivede!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Oh, e siete pure modesto! Un vero gentiluomo! Credo che diverremo amici, non siete come quell'abbate borioso... Permettetemi di presentarmi – Josef Loderdale, già capitano della flotta navale inglese.";
			link.l1 = "Felice d’incontrarti. "+GetFullName(pchar)+" al vostro servizio!";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "È piuttosto noioso vivere qui, quindi passa in taverna stasera: potremo bere un bicchiere di vino e scambiare due chiacchiere interessanti...";
			link.l1 = "Terrò a mente, signore. A presto!";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Hai qualcosa d’interessante da raccontare?","È successo qualcosa di nuovo sull’isola?","Mi racconterai gli ultimi pettegolezzi?");
			link.l2.go = "rumours_LSC";
			link.l3 = "Vorrei farti qualche domanda sull'isola.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;

//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Sarebbe un piacere rispondere alle vostre domande, signore...";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Come sei giunto fin qua?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Che tipo di servigio si trova qui?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Essendo tu un ufficiale militare, qual è il tuo pensiero sul dominio dei pirati da queste parti?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Ho visto un sacco di scrigni chiusi a chiave qui, sull’Isola Giustizia. La gente non si fida l’uno dell’altro, vero?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Nessuna domanda. Perdona...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Facevo il mio dovere militare. Combattevo contro una corvetta da guerra spagnola, pensavamo fosse la nave che assaliva i mercanti inglesi. La battaglia fu lunga, quasi li avevamo presi, ma una tempesta improvvisa ha rovinato tutto. Così, entrambe le navi sono naufragate vicino agli anelli esterni.\nLa sorte ha il suo scherzoso gusto: io e il capitano spagnolo siamo sopravvissuti. Forse l’hai già incontrato qui. Si chiama Lorenzo Solderra, una vera carogna. Guardati da lui.";
			link.l1 = "Capito. Terrò a mente il tuo avvertimento...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Se hai bisogno di riposare – vai alla taverna di Sancho. Ti darà sempre da mangiare, da bere e un letto dove buttarti. Se invece vuoi polvere da sparo, munizioni, armi o altre robacce – cerca Axel Yost, che tiene il negozio qui sull’isola. Le medicine puoi prenderle da fratello Giuliano: vende anche reliquie e oggetti sacri nella sua chiesa.\nI Narvali hanno un fabbro di gran talento, Schmidt lo chiamano. Pare forgia lame che tagliano come l’abisso. Tra i Narvali c’è pure un altro artigiano d’ingegno, ma non sono riuscito a saperne di più.\n E se ti capiterà di avere grane con pirati o clan, allora parla con Giuseppe Fazio: è l’uomo giusto per certe faccende.";
			link.l1 = "Grazie per le informazioni!";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Non posso dire che mi piaccia, ma non ci posso far nulla. Ammetto che ai pirati è bastato qualche giorno per portare la pace e mettere ordine sull’Isola Giustizia. Prima del loro arrivo, i clan si scannavano a vicenda e la povera gente ci rimetteva sempre di più.\nInoltre, vendono il cibo in modo pulito e giusto – la gente comune lo prende quasi per nulla, mentre ai clan lo fanno pagare a peso d’oro, per vendicarsi di chi ha scatenato la guerra.\nConosco un pirata molto sveglio, si chiama Layton Dexter. È lui che si occupa dei commerci. Ho parlato una volta con lui, e mi chiedo ancora come un uomo così accorto e istruito, che sa di tattiche, carte e mercanzie, sia finito a far vita di pirata.\nGli sono bastati pochi giorni per tracciare una mappa eccellente dell’Isola. L’ho vista: c’è segnato quasi tutto. Credo che l’abbia preparata in vista di una possibile guerra coi clan...";
			link.l1 = "Capisco...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
			sld = characterFromId("Dexter");
			sld.quest.map = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "È giusto così. Si racconta che, un tempo, rubare fosse cosa comune sull’Isola Giustizia, finché ogni forziere non ebbe una nuova serratura. Eppure, qualcuno che sa scassinare i forzieri ancora c’è. Ma ruba solo rum e gingilli da quattro soldi, mai oro o monete.\nOgni serratura è unica, nessuna chiave si assomiglia – Jurgen Schmidt se n’è assicurato. Non forgia solo lame, ma anche serrature e chiavi. M’han detto che nei forzieri fuori non troverai nulla di prezioso, le cose serie restano sempre dentro le navi.";
			link.l1 = "Interessante...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Che stai facendo lì, eh? Ladro!","Guarda un po’! Appena mi sono perso nei miei pensieri, tu subito a frugare nel mio forziere!","Hai deciso di frugare nei miei forzieri? Non te la caverai così facilmente!");
			link.l1 = "Merda!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Cosa?! Hai deciso di ficcare il naso nei miei forzieri? Non la passerai liscia!";
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
			dialog.text = LinkRandPhrase("Ascolta, faresti meglio a mettere via quell’arma. Mi mette a disagio.","Sai, qui non si tollera chi va in giro con la lama sguainata. Riponila.","Ascolta, non fare il paladino con la spada sguainata che corre qua e là. Mettila via, non è roba tua...");
			link.l1 = LinkRandPhrase("Bene.","Come desideri...","Come dici tu...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Ascolta, sono un cittadino della città e ti chiederei di tenere a bada la tua lama.","Ascolta, sono cittadino di questa città e ti chiederei di tenere la lama a bada.");
				link.l1 = LinkRandPhrase("Va bene.","Come desideri...","Come desideri...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Attento, compare, a correre armato. Potrei innervosirmi...","Non mi piace quando gli uomini mi passano davanti con l’arma sguainata. Mi fa tremare il sangue...");
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
