// Антонио Бетанкур - потомок Франциско Бетанкура
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
				dialog.text = "Non voglio parlare con te. Attacchi povera gente senza motivo e li provochi alla rissa. Sparisci dai miei occhi!";
				link.l1 = "Hm...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Salve, salve... Che desideri, amico?";
				link.l1 = TimeGreeting()+". Mi chiamo "+GetFullName(pchar)+". E volevo solo sapere chi sei tu. Vedi, sono appena sbarcato, mi aggiro per la città e scambio due parole con la gente.";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, "+GetFullName(pchar)+"! "+TimeGreeting()+"! Cosa vuoi stavolta?";
				if(CheckAttribute(pchar, "questTemp.LSC.Betancur"))
				{
					link.l4 = "Antonio, dicono che tu conosca bene la storia dell’Isola. Avrei una domanda per te, se permetti.";
					link.l4.go = "dolly";
				}
				dialog.text = "Ah, "+GetFullName(pchar)+"! "+TimeGreeting()+"! Vuoi qualcosa?";
				link.l1 = LinkRandPhrase("Hai qualcosa di curioso da raccontare?","È successo qualcosa di nuovo sull’isola?","Mi racconterai gli ultimi pettegolezzi?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Vorrei farti qualche domanda sull’isola.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Volevo solo sapere come te la passi. A presto!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Splendido.   E vedrai che ti troverai bene, perché qui siamo tutti una gran famiglia. Tranne quei dannati Narvali e gli sporchi Rivados, ovviamente. Il mio nome è Antonio, Antonio Betancourt. Sono il nipote di Francisco Betancourt, se mai questo nome ti dice qualcosa.";
			link.l1 = "Francisco Betancourt? Questo nome mi suona familiare... Ah, già! Dio me ne parlò e lessi di lui nelle note di Alvarado...";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Non so proprio chi sia questo tuo Dios, ma il capitano Alvarado ci fece visita tanto tempo fa. L'ho visto con i miei occhi quand'ero ragazzino. Salpò dall'Isola Giustizia e ne parlò nei suoi manoscritti. E Francisco Betancourt era un ammiraglio spagnolo, comandante di uno squadrone militare.\nFu lui a dare inizio alla storia di questo luogo, poiché tutti i Rivados sono discendenti degli schiavi neri del Tartaro, la nave ammiraglia. I Narvali invece son figli dei primi coloni bianchi, i membri d'equipaggio del Tartaro, del San Agostino e del San Geronimo.";
			link.l1 = "Incredibile! Dunque sei nato qui?";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "Esatto. Sono il sangue diretto di colui che, in pratica, ha conquistato l’Isola.";
			link.l1 = "Capisco. Lieto di conoscerti, Antonio. A presto.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		// квестовая часть
		case "dolly":
			dialog.text = "Mm... Certo, compare, domanda pure. Risponderò alle tue domande, ovviamente, ma solo se so le risposte.";
			link.l1 = "Dimmi, ti ricordi quando il galeone San Geronimo era ancora tra queste acque?";
			link.l1.go = "dolly_1";
		break;
		
		case "dolly_1":
			dialog.text = "Certo che sì. Era una nave davvero particolare. C’era una strana statua indiana e quei luridi pagani dei Rivados facevano offerte sacrificali.";
			link.l1 = "E come lo facevano, allora? Strappavano il cuore alla gente come i Maya? O preferivano mozzare teste?";
			link.l1.go = "dolly_2";
		break;
		
		case "dolly_2":
			dialog.text = "No... Era una statua molto particolare – inghiottiva le sue vittime e queste sparivano per sempre. Uno strumento del demonio... Per fortuna è affondata insieme alla nave e non farà più male a nessuno. Curioso come i sacrifici avvenissero sempre alla stessa ora del mattino. La statua si trasformava in oro sotto la luce del sole nascente. È allora che i selvaggi conducevano le vittime, per lo più Narvali catturati.";
			link.l1 = "Interessante! E qualcuno ha mai provato a scoprire come funziona quella statua?";
			link.l1.go = "dolly_3";
		break;
		
		case "dolly_3":
			dialog.text = "Ma certo che no! Primo, i Rivados non lasciano avvicinare nessuno a San Geronimo se non i loro, e secondo, un buon cattolico deve star lontano dalle opere del diavolo.";
			link.l1 = "Capisco. Mi sembra che tu non vada d’accordo coi Rivados, sbaglio?";
			link.l1.go = "dolly_4";
		break;
		
		case "dolly_4":
			dialog.text = "Ah sì? Li odio, quei pagani sudici! Se non lo sai, mio nonno era il capitano della nave dove i negri, guidati dal loro Rivados, si ribellarono. Lasciare marcire il loro cosiddetto capo in stiva fu la scelta giusta. Avevo anche una splendida chiave del tesoro di Sant’Anna.\nNessuno sa dove sia quel tesoro, forse giace in fondo al mare tra i granchi, ma quella chiave era un ricordo prezioso... eppure me l’hanno rubata! Son certo che siano stati quei neri. Devono cercare il tesoro, ma dubito che ci riusciranno, dopo tutto questo tempo, ah-ah! Feccia...";
			link.l1 = "Capisco. Grazie per la tua storia intrigante!";
			link.l1.go = "dolly_5";
		break;
		
		case "dolly_5":
			dialog.text = "Benvenuto, fa sempre piacere scambiare quattro chiacchiere!";
			link.l1 = "Addio!";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.LSC.Betancur");
			AddQuestRecord("LSC", "16");
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Ascolto, compare.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = " Dunque, non hai mai visto altro che l’Isola Giustizia in tutta la tua vita? ";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Sei nato qui... E perché non fai parte del clan dei Narvali? Pensavo che tutti i bianchi nativi fossero Narvali...";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "E che cosa fai sull'Isola Giustizia?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Dimmi, hai mai desiderato abbandonare l’Isola, anche solo per un po’? Vedere il mondo là fuori...";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Nessuna domanda. Perdono...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Così pare, sì. Ma non pensare che io sia uno sciocco o un sempliciotto. Ho ereditato una splendida biblioteca da mio nonno e mio padre mi ha dato un’istruzione raffinata. Conosco la storia antica, la geografia, l’astronomia, parlo inglese, francese, spagnolo e persino il latino.\nMolti marinai che hanno visto mezzo mondo sanno meno di me. Anche se non ho mai visto altro che questi relitti, nella mente mia ho viaggiato per l’Europa, la Cina e l’India...";
			link.l1 = "Capisco...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Non è vero, anche se hai quasi ragione. Ma io non sono un Narvalo, né desidero diventarne uno. A che scopo? Fare la vedetta per ore come uno scemo o menar le mani coi Rivados? Piuttosto crepo, risparmiamelo. Io sono d’un’altra pasta. Preferisco vivere per conto mio e perdermi nei libri.";
			link.l1 = "Capisco...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Mio padre mi ha lasciato una discreta eredità e la gestisco con giudizio. Non ho bisogno di aggirarmi tra relitti marci per scambiare quattro gemme con un tozzo di pane. Non credo a quelle storie di grandi tesori nascosti tra le vecchie carcasse.\nL’unico tesoro che valga la pena, per quel che ne so, è il forziere di Sant’Anna. Una gran cassa di ferro... ma nessuno l’ha mai scovata, almeno per ora.\nInoltre, sto pensando di scrivere una cronaca dettagliata dell’Isola Giustizia, raccogliendo le storie della gente. Che ne pensi, dovrei provarci?";
			link.l1 = "Ne sono certo. So almeno di un uomo all'Arcipelago che sborserebbe un sacco d’oro per un libro del genere. Quindi è la tua occasione...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "A volte ci penso. Forse, se arrivasse una nave capace di sfidare queste correnti e sopravvivere alle tempeste, rischierei. Ho una gran voglia di vedere con i miei occhi quelle meraviglie che i miei libri raccontano con tanta passione! Ma, per ora, sono solo sogni...";
			link.l1 = "I sogni si avverano. Devi solo crederci...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Che stai facendo lì, eh? Ladro!","Guarda un po’! Appena m’è venuta voglia di rimirare il vuoto, tu ti sei precipitato a frugare nel mio baule!","Hai deciso di frugare tra i miei forzieri? Non la passerai liscia, mascalzone!");
			link.l1 = "Maledizione!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Cosa?! Ti sei messo a frugare nei miei forzieri? Non la passerai liscia, maledetto!";
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
			dialog.text = LinkRandPhrase("Ascolta, faresti meglio a mettere via la tua arma. Mi mette inquietudine.","Sai, qui non è tollerato andare in giro sguainando la lama. Riponila.","Ascolta, lascia stare il cavaliere medievale che corre con la spada sguainata. Mettila via, non è roba tua...");
			link.l1 = LinkRandPhrase("Bene.","Come desideri...","Come dici tu...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"Ascolta, sono cittadino di questa città e ti chiederei di tener a bada la tua lama.","Ascolta, sono cittadino di questa città e ti chiedo di tenere a bada la tua lama.");
				link.l1 = LinkRandPhrase("Va bene.","Come desideri...","Come dite voi...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Fa' attenzione, compare, a girare con l’arma in pugno. Mi fai venire i nervi...","Non mi piace quando gli uomini passeggiano davanti a me con l’arma sguainata. Mi mette addosso una fifa maledetta...");
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
