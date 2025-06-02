// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Che tipo di domande?","Cosa vuoi, "+GetAddress_Form(NPChar)+"?"),"Hai già cercato di farmi una domanda "+GetAddress_Form(NPChar)+"...","Hai parlato della stessa questione per la terza volta oggi...","Guarda, se non hai nulla da dirmi riguardo agli affari del porto, non disturbarmi con le tue domande.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Mi sono ricreduto.","Non ho nulla di cui parlare."),"Non importa.","Infatti, già la terza volta...","Mi dispiace, ma per ora non mi interessano gli affari del porto.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//Цена чахотки
			if (!CheckAttribute(npchar, "quest.Consumption") && CheckAttribute(pchar, "questTemp.Consumption.AskJuan"))
			{
				link.l1 = "Dimmi, il nome 'Juan' ti dice qualcosa?";
				link.l1.go = "Consumption";
			}
			if (!CheckAttribute(npchar, "quest.Guardoftruth") && CheckAttribute(pchar, "questTemp.Guardoftruth.Trinidad") && pchar.questTemp.Guardoftruth.Trinidad == "begin")
			{
				link.l1 = "Signore, c'era una fregata qui sotto il comando di Miguel Dichoso nell'aprile 1654. È scomparso da allora. Non ricordi nulla al riguardo? Forse, Dichoso era qui e ha registrato la sua nave...";
				link.l1.go = "guardoftruth";
			}
		break;
		
		//Цена чахотки
		case "Consumption":
			dialog.text = "Juan? Solo questo? Signore, sei ubriaco o stai giocando uno scherzo stupido con me? Riesci a ricordare un cognome o almeno, il nome della sua nave? Questa è una colonia spagnola, per l'amor di Dio. Sai quanti Juan abbiamo qui? Non sarò in grado di aiutarti senza alcun dettaglio.";
			link.l1 = "Capisco. Scusa per il disturbo...";
			link.l1.go = "exit";
			pchar.questTemp.Consumption.AskJuan = sti(pchar.questTemp.Consumption.AskJuan)+1;
			if(sti(pchar.questTemp.Consumption.AskJuan) == 3)
			{
				pchar.quest.Consumption2.win_condition.l1 = "location";
				pchar.quest.Consumption2.win_condition.l1.location = "PortSpein_town";
				pchar.quest.Consumption2.function = "Consumption_CreateSergio";
			}
			npchar.quest.Consumption = "true";
		break;
		
		case "guardoftruth":
			dialog.text = "Diamo un'occhiata alle mie note... ah ha! Sì, il Capitano Miguel Dichoso era qui nell'aprile 1654, sulla fregata 'Santa-Quiteria'. Si è registrato proveniente dalla colonia San-Andres, Providence. Stava andando a Cadice, Spagna. Ha salpato il 14 aprile, 1654. Questo è tutto quello che ho.";
			link.l1 = "Vai in Europa in barca? Capisco. Grazie per l'informazione!";
			link.l1.go = "exit";
			npchar.quest.guardoftruth = "true";
			AddQuestRecord("Guardoftruth", "39");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
