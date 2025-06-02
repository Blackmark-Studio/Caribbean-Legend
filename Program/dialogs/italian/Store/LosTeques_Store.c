void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sLoc;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase("C'è stato un allarme in città. Tutti ti stanno cercando! Se fossi in te, non aspetterei qui troppo a lungo.","L'intera guardia cittadina sta setacciando la città cercando di trovarti. Non sono un idiota e non intendo parlare con te!","Scappa, compagno, prima che i soldati ti riducano in polpette..."),LinkRandPhrase("Cosa ti serve, mascalzone?! La guardia cittadina è sulle tue tracce in questo momento. Non arriverai lontano, sporco pirata!","Esci dalla mia casa, assassino! Guardie!!","Non ho paura di te, mascalzone! Presto ti impiccheranno, non te la caverai..."));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("Eh, non sono troppo preoccupato per l'allarme...","Non hanno alcuna possibilità di prendermi."),RandPhraseSimple("Chiudi il tuo becco, "+GetWorkTypeOfMan(npchar,"")+", o ti taglio quella maledetta lingua!","Eh, "+GetWorkTypeOfMan(npchar,"")+", anche tu vuoi cacciare un pirata! Ascolta, amico, stai calmo e vivrai..."));
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = TimeGreeting()+"! Non ti ho mai visto prima, signore. Oso supporre, sei un capitano... Ho indovinato? Il mio nome è "+GetFullName(npchar)+", e il mio negozio è al vostro servizio. Oro, argento e molto altro per suscitare l'interesse di un uomo curioso.";
				Link.l1 = "Capisco. Io sono "+GetFullName(pchar)+". Piacere di conoscerti, "+npchar.name+".";
				Link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = TimeGreeting()+", signore! Sono felice di rivederti nel mio negozio. Desideri acquistare dei pepite d'oro? O forse oggi potresti essere interessato ai minerali?";
				link.l1 = "Mostrami la tua merce, "+npchar.name+".";
				link.l1.go = "trade";
				link.l4 = "No, non ho bisogno di nulla, "+npchar.name+". Sono passato solo per salutarti.";
				link.l4.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting":
			dialog.text = "Anche io, signore. Desidera dare un'occhiata alla mia merce? Sono sicuro di avere qualcosa che potrebbe interessarla.";
			link.l1 = "È la mia prima volta qui e vorrei saperne di più su questa colonia.";
			link.l1.go = "info";
			link.l2 = "Allora mostrami cosa hai in vendita.";
			link.l2.go = "trade";
		break;
		
		case "info":
			dialog.text = "La nostra piccola città è stata costruita grazie alla miniera d'oro. Estraggono minerale d'oro, argento e pepite d'oro. A volte perfino gemme. Qui avevamo solo una guarnigione fino a quando gli indiani amichevoli e alcuni coloni bianchi si sono uniti a noi\nIgnacio Ortega ha costruito una taverna e ha reso la nostra vita un po' più allegra. Tutti i tipi di avventurieri visitano questo posto con l'intenzione stupida di derubarci. Non abbiamo un tribunale qui, quindi il loro numero è diminuito dopo che abbiamo impiccato diversi idioti proprio nel mezzo della città\nIl minerale d'oro viene inviato alle navi sotto la protezione di soldati e indiani amichevoli, le pepite, invece, le puoi comprare proprio qui, in questo negozio\nInoltre, a volte ho minerali molto interessanti in offerta, quindi visitami quando hai tempo, rifornisco sempre il mio stock.";
			link.l1 = "Grazie per l'interessante storia! La terrò a mente.";			
			link.l1.go = "exit";
		break;
		
		case "trade":
			DialogExit();
			if (!CheckAttribute(npchar, "trade_date") || GetNpcQuestPastDayParam(npchar, "trade_date") >= 10)
			{
				GiveItemToTrader(npchar);
				SaveCurrentNpcQuestDateParam(npchar, "trade_date");
			}
			LaunchItemsTrade(npchar, 0);
		break;

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

		// ============== Грабеж среди бела дня, попытка залезть в сундуки =========================
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Rapina in pieno giorno!!! Che cosa sta succedendo qui?! Aspetta, fermati, amico...","Ehi, cosa stai facendo lì?! Stai cercando di derubarmi? Ora sei nei guai...","Aspetta, cosa diavolo stai facendo? Si scopre che sei un ladro! Considera questa la fine della linea, bastardo...");
			link.l1 = LinkRandPhrase("Dannazione!!","Caramba!!","Ah, merda!");
			link.l1.go = "fight_owner";
		break;
		
		case "fight_owner": // лесник . выход из диалога . если копался в сундуках. 
			LAi_SetOwnerTypeNoGroup(NPChar);
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			NextDiag.CurrentNode = "First time";
			DialogExit();
		break;
	}
}
