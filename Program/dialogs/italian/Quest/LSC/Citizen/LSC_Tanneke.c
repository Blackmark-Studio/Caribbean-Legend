// Таннеке Эверс - просто девушка
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
				dialog.text = "Non voglio parlare con te. Attacchi civili innocenti senza motivo e li provochi a combattere. Sparisci!";
				link.l1 = "Hm...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Buondì! Ti conosco, forse? Non mi pare di averti già visto, questo è certo...";
				link.l1 = TimeGreeting()+"È vero, sono un... nuovo ospite da queste parti. Il mio nome è "+GetFullName(pchar)+" e sono un capitano.";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, "+GetFullName(pchar)+"! "+TimeGreeting()+" ! Vuoi qualcosa?";
				link.l1 = LinkRandPhrase("Hai qualche storia intrigante da raccontare?","È successo qualcosa di nuovo sull’Isola Giustizia?","Mi racconterai gli ultimi pettegolezzi?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Vorrei farti qualche domanda sull'isola.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Volevo solo sapere come te la passi. A presto!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Sei mai stato un capitano?";
			link.l1 = "Perché dovrei esserlo? Sono ancora un capitano... ah-ah, ho capito! Pensi che la mia nave sia affondata o sfracellata sugli scogli. No. È ancora vicino alle coste del Main Occidentale. Sono arrivato qui su una barca, ma è finita male: ha preso una falla nello scafo ed è sprofondata.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Sei arrivato qui su una barca? E come hai fatto a sopravvivere alla tempesta?";
			link.l1 = "Quale tempesta? Non ricordo nessuna tempesta...";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "Com’è possibile? Una tempesta circonda sempre l’Isola Giustizia. Così dicon tutti, per Giove.";
			link.l1 = "Beh, non proprio, oppure ho avuto la fortuna di sfuggirci. Il mare era assolutamente placido... perdonate l’ardire, ma potrei conoscere il nome di una dama così graziosa?";
			link.l1.go = "meeting_3";
		break;
		
		case "meeting_3":
			dialog.text = "Oh! Perdonami, ho dimenticato di presentarmi... Mi chiamo Tanneke. Piacere di conoscerti.";
			link.l1 = "Piacere mio, Tanneke... È un vero onore.";
			link.l1.go = "meeting_4";
		break;
		
		case "meeting_4":
			dialog.text = "E perché mai hai deciso di approdare sulla nostra Isola su una barca? Ah-ah, ora capisco – la corrente ti ha portato dritto qui. Nessuno conosce l’Isola, e la gente ci finisce sempre per caso.";
			link.l1 = "Non è proprio così. Si sentono voci ben fondate sull’Isola, persino sul suo luogo. Così ho deciso di vederla coi miei occhi...";
			link.l1.go = "meeting_5";
		break;
		
		case "meeting_5":
			dialog.text = "Adesso capisco. Sei proprio come Adolf Barbier, hai letto troppe storie di capitan Alvarado e t’è venuta la voglia di trovare l’oro dell’ammiraglio de Betancourt. Ahimè, capitano, se uno scaltro furfante come Barbier non ci ha messo le mani, dubito che tu abbia più fortuna... E ti dirò, secondo me quell’oro dell’ammiraglio è solo una invenzione: Antonio se l’è inventata per farci credere che suo nonno fosse qualcuno di importante... Beh, ormai resterai con noi. Arrivare fin qui è stato facile, ma andarsene... è quasi impossibile. Uscirne intero, poi, è tutta un’altra storia.";
			link.l1 = "Non è nulla. Credo che riuscirò a cavarmela, e non parlo dell’oro di Betancourt che hai menzionato – lo sento nominare adesso per la prima volta – parlo di lasciare l’Isola. Vivo. È stato un piacere chiacchierare con te, Tanneke. A presto!";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Domanda pure, capitano...";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Come sei arrivato qui?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Hai mai provato a lasciare l’Isola Giustizia?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Come si tira avanti da queste parti?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Le ragazze devono comprare il cibo dall’ammiraglio o glielo danno gratis?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Nessuna domanda. Perdona...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Sono olandese, ma vivevamo a Santiago. I miei genitori mi mandarono a lavorare come serva presso la famiglia del banchiere Geraldi. Li conosci? Tre anni fa uno di loro salpò per la Nuova Spagna su un lugger corriere. Mi dissero di accompagnarlo. Al secondo giorno di viaggio, ci catturò una brigantina sotto bandiera spagnola.\nIl loro ufficiale salì a bordo della nostra nave e scambiò due parole col nostro capitano, che s’infuriò e lo cacciò via. Appena quell’ospite rimise piede sulla sua nave, ci attaccarono. Cercammo di fuggire, ma riuscirono ad abbordarci. Da quel che ho capito, cercavano il mio padrone Geraldi, perché corsero subito nella cabina, lo presero e lo portarono via. Me e i marinai ci rinchiusero in stiva e ci lasciarono là.\nPensavo volessero affondarci, invece si allontanarono. I marinai riuscirono a liberarci, ma il nostro capitano era caduto in battaglia e nessun altro sapeva tenere la rotta. Navigammo a caso per un po’, finché una burrasca ci travolse.\nPoche ore dopo, la nostra barca fu scaraventata sull’anello esterno. Sta ancora lì. Sono stata abbastanza fortunata da sopravvivere a quel pandemonio; all’alba io e pochi altri ‘fortunati’ siamo approdati sull’Isola Giustizia.";
			link.l1 = "Capisco...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "No. E come pensi di farlo, eh? Non ci sono navi pronte a mollare gli ormeggi qui, e buttarsi in mare su una scialuppa equivale a firmarsi la condanna a morte con la propria mano. Come ti dicevo, le tempeste qui sono di casa. Ricordo solo un tentativo di fuga — cinque anime coraggiose misero insieme una barca con vele e remi... Hanno lottato contro la corrente per ore, riuscendo infine a raggiungere il mare aperto. Qualche giorno dopo, uno di loro tornò nell’anello esterno... legato all’albero spezzato e già morto. Da allora, a nessun altro è più venuta voglia di simili bravate.";
			link.l1 = "Capito...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Va tutto bene. Non è peggio che servire quella famiglia d’usurai arroganti. Basta abituarsi a questo posto, poi magari finirai pure per amarlo. E non sono l’unico a pensarla così, sai. E i clan... non mi danno fastidio.";
			link.l1 = "Interessante...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Ma certo che compriamo, capitano. Oh, qui per una ragazza c’è sempre da fare: pulire, cucinare, dare una mano agli altri... non stiamo con le mani in mano, ma nessuno si spezza la schiena. I pirati vendono il cibo a poco prezzo per la gente comune, al contrario dei clan. Così non moriamo di fame.\nAiuto Gillian e Natalie, e loro aiutano me se serve. Siamo amiche. C’è un’altra ragazza sull’Isola, la spagnola. Si chiama Ramona, ma sta quasi sempre per conto suo, e a dire il vero non abbiamo molta voglia di farci amiche con lei.";
			link.l1 = "E perché mai?";
			link.l1.go = "ansewer_4_1";
		break;
		
		case "ansewer_4_1":
			dialog.text = "Beh... diciamo che vediamo la vita in modo diverso. Parla con lei e capirai.";
			link.l1 = "Interessante...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Che ci fai là, eh? Ladro!","Guarda un po’! Appena mi sono perso nei miei pensieri, tu hai già ficcato il naso nel mio baule!","Hai deciso di ficcare il naso nei miei forzieri? Non te la caverai così facilmente!");
			link.l1 = "Maledizione!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Cosa?! Hai deciso di frugare nei miei scrigni? Non la passerai liscia!";
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
			dialog.text = LinkRandPhrase("Ascolta, faresti meglio a mettere via quell’arma. Mi mette a disagio.","Sai, qui non si tollera correre con la lama sguainata. Riponila.","Ascolta, lascia stare il paladino con la spada sguainata. Mettila via, non fa per te...");
			link.l1 = LinkRandPhrase("Bene.","Come desideri...","Come dici tu...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Ascolta, sono cittadino di questa città e ti chiederei di tenere a bada la tua lama.","Ascolta, sono cittadino di questa città, e ti chiederei di tener ferma la lama.");
				link.l1 = LinkRandPhrase("D'accordo.","Come desideri...","Come dici tu...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Attento, compare, a correre in giro armato. Potrei innervosirmi...","Non mi piace quando gli uomini mi passano davanti con l’arma in pugno. Mi mette i brividi...");
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
