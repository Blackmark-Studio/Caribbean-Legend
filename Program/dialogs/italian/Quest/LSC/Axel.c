// торговец Аксель Йост
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
			if (pchar.questTemp.LSC == "return" && !CheckAttribute(npchar, "quest.return_isl"))
			{
				dialog.text = "Ma guarda un po'..."+GetFullName(pchar)+"! Sei tornato dall'aldilà? Com'è possibile?";
				link.l1 = "La gente non torna dall'aldilà, Axel. È semplice – non sono mai stato morto, ah-ah!";
				link.l1.go = "exit";
				npchar.quest.return_isl = "true";
				break;
			}
			if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
			{
				dialog.text = "Ehi, compare, non farò affari con te finché non sistemi le cose coi Narvali. Non voglio grane. Vai da Fazio, lui saprà cavarsela.";
				link.l1 = "Bene, lo farò subito.";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(pchar, "GenQuest.CitizenConflict") && sti(pchar.GenQuest.CitizenConflict) > 3)
			{
				dialog.text = "Non voglio parlare con te. Attacchi la gente pacifica senza motivo e li provochi a menar le mani. Sparisci dai piedi!";
				link.l1 = "Uhm...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Oh! Una faccia nuova! Cosa ti porta da queste parti? Ma non è affar mio, dopotutto. Lascia che mi presenti: mi chiamo Axel Yost e questa bottega è roba mia. Hai visto qualcosa che ti tenta?";
				link.l1 = TimeGreeting()+". Il mio nome è "+GetFullName(pchar)+". Che mercanzia tieni a bordo, dunque?";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, "+pchar.name+"! Lieto di vederti. Vuoi comprare o vendere qualcosa?";
				// квестовые ветки
				if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "search_mush_1")
				{
					link.l4 = "Ascolta, Axel, hai da vendere un moschetto di quelli buoni? Non una pistola da soldato qualunque, ma qualcosa di preciso e che tiri lontano?";
					link.l4.go = "adolf";
				}
				if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "trader_whiskey")
				{
					link.l4 = "Ascolta, Axel, Chad Kapper ti ha chiesto di procurargli una botte di whiskey? ";
					link.l4.go = "whiskey";
				}
				if (CheckAttribute(npchar, "quest.ole_pearl"))
				{
					link.l5 = "Ascolta, Axel, avrai sentito la mia chiacchierata con quell’imbecille del posto. Che perla voleva? Non ci arrivo.";
					link.l5.go = "ole_pearl";
				}
				link.l1 = "Sì. Facciamo affari, Axel!";
				link.l1.go = "Trade_items";
				link.l2 = LinkRandPhrase("Hai qualche storia interessante da raccontare?","Che novità ci sono state ultimamente sull’Isola Giustizia?","Qualche pettegolezzo?");
				link.l2.go = "rumours_LSC";
				link.l3 = "Non ancora. Volevo solo darti il mio saluto.";
				link.l3.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting":
			dialog.text = "Di tutto un po'. Misture, lame, archibugi, munizioni, corazze, gemme e minerali. Amuleti e talismani stregati. Robaccia e oggetti d’uso quotidiano. La gente mi porta qualsiasi cosa recuperi dai relitti, cose di cui non ha bisogno.\nCosì fai pure lo stesso, se ti va. Ma ti avverto in anticipo: non tratto né provviste né mercanzie navali.";
			link.l1 = "D'accordo, Axel. Vediamo la tua mercanzia.";
			link.l1.go = "Trade_items";
			link.l2 = "Grazie, Axel. Terrò bene a mente. Verrò a cercarti appena avrò bisogno dei tuoi servigi.";
			link.l2.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "Trade_items":
			DialogExit();
			if (!CheckAttribute(npchar, "trade_date") || GetNpcQuestPastDayParam(npchar, "trade_date") >= 5)
			{
				GiveItemToTrader(npchar);
				SaveCurrentNpcQuestDateParam(npchar, "trade_date");
			}
			LaunchItemsTrade(npchar, 0);
		break;
		
		// наводка на Адольфа
		case "adolf":
			dialog.text = "Deve essere uno scherzo, questo. Sei la terza persona che me lo chiede. Non tengo armi del genere qui. Ma qualche mese fa Adolf Barbier cercò di vendermi il suo stutzen da caccia col cannocchiale. Una meraviglia, ti dico. Proprio quello che cerchi.\nMa Barbier voleva una cifra da far tremare i polsi. Ho dovuto rifiutare l'affare.";
			link.l1 = "Interessante! E dove posso rintracciare Barbier?";
			link.l1.go = "adolf_1";
		break;
		
		case "adolf_1":
			dialog.text = "Non ne ho la minima idea. Probabilmente sta vagando da qualche parte. Spesso si fa vedere alla taverna di Sancho, gli piace tracannare qualcosa ogni sera.";
			link.l1 = "Grazie! Credo che lo troverò lì. Dimmi, Axel, chi altri ti ha chiesto del fucile? Hai accennato che c'erano altri curiosi, chi sarebbero costoro?";
			link.l1.go = "adolf_2";
		break;
		
		case "adolf_2":
			dialog.text = "Mary Casper e Marcello, conosciuto anche come il Ciclope. Non saprei proprio perché la ragazza volesse un fucile, ma la nostra Mary la Rossa è una testa calda nota a tutti. Un anno fa comprò montagne di polvere da sparo per fabbricar mine, diceva che voleva stordire i granchi. Ringraziamo il Buon Dio che non gliel’hanno permesso.\nE Marcello invece cercava un fucile per la caccia agli uccelli, l’uomo non ne poteva più del manzo salato. Li ho mandati entrambi da Adolf, ma non so se alla fine gliel’abbia venduto oppure no.\nAnche quel volpone di Giuseppe Fazio si è informato di Adolf di recente. Forse anche lui punta a mettere le mani su quello stutzen.";
			link.l1 = "Eheh, ho un bel po' di rivali. Va bene, andrò a cercare Adolf – speriamo che non abbia già venduto lo schioppo.";
			link.l1.go = "adolf_3";
		break;
		
		case "adolf_3":
			DialogExit();
			pchar.questTemp.Saga.SharkHunt = "search_mush_2"; //флаг на таверну
			AddQuestRecord("SharkHunt", "12");
			sld = characterFromId("LSC_Adolf");
			sld.lifeday = 0; // убираем настоящего Адольфа
		break;
		
		// бусинка для Белого Мальчика - просто инфа
		case "ole_pearl":
			dialog.text = "Tutti lo sanno, signore! Chiede a chiunque di queste perle, così chiama le grosse perle. Dagliene una, e sarai il suo migliore amico.";
			link.l1 = "Ora capisco. Grazie, Axel, non ci sarei mai arrivato da solo.";
			link.l1.go = "exit";
			DeleteAttribute(npchar, "quest.ole_pearl");
		break;
		
		// виски для Акулы
		case "whiskey":
			dialog.text = "Sì, compare, l’ha fatto. Ma dovrò deluderti se speravi di comprare anche tu una botte di Bushmills. Ne avevo soltanto una e Chad se l’è già accaparrata. Posso offrirti del whisky scozzese – buono quanto quello irlandese, anzi, ti dirò che a me piace pure di più.";
			link.l1 = "Forse, più tardi. Chad ti ha comprato qualcos’altro ultimamente?";
			link.l1.go = "whiskey_1";
		break;
		
		case "whiskey_1":
			dialog.text = "No. Era interessato all’arsenico, diceva che al Tartaro ci sono troppi ratti e voleva sterminarli. Io non ne ho più bisogno da quando ho assunto quel babbeo di Olle a pulire la mia bottega, tutti i ratti sono corsi alla taverna del povero Sancho. Non so cosa temano tanto di Olle quei topastri...";
			link.l1 = "Forse, ha dei gatti tra i suoi avi...";
			link.l1.go = "whiskey_2";
		break;
		
		case "whiskey_2":
			dialog.text = "Ah-ah! Forse... Sancho ha dell’arsenico, questo è sicuro.";
			link.l1 = "Capisco. Grazie per le informazioni, allora!";
			link.l1.go = "whiskey_3";
		break;
		
		case "whiskey_3":
			DialogExit();
			AddQuestRecord("SharkHunt", "36");
			pchar.questTemp.Saga.SharkHunt = "barmen_whiskey"; // флаг на таверну - поиск мышьяка
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}
