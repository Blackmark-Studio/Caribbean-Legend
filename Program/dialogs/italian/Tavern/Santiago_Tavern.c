// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Quali domande hai?","Come posso aiutarti, "+GetAddress_Form(NPChar)+"?"),"Hai cercato di farmi una domanda poco tempo fa, "+GetAddress_Form(NPChar)+"...","Per tutto il giorno, questa è la terza volta che parli di qualche domanda...","Altre domande, presumo?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Ho cambiato idea...","Non ho niente di cui parlare al momento."),"Uh, dove se n'è andata la mia memoria...","Sì, è davvero la terza volta...","No, quali domande?...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// Jason Долго и счастливо
			if (CheckAttribute(pchar, "questTemp.LongHappy.Santiago"))
			{
				link.l1 = "Ho sentito che i santi padri sono arrivati qui da una colonia francese con qualche delegazione, per concordare qualcosa? Probabilmente, per scambiare prigionieri dopo quel bagno di sangue in Martinica?";
				link.l1.go = "LH_tavern";
			}
		break;
		
		// Jason Долго и счастливо
		case "LH_tavern":
			dialog.text = "No signore, quella storia è stata risolta molto tempo fa senza alcun chierico. Vedi, tu vivi completamente sotto un albero di palma, dato che non hai sentito che Papa Innocenzo X con il Cardinale Mazarin hanno finalmente raggiunto un accordo. L'Europa con le sue guerre è una cosa, ma tutti i cristiani dovrebbero combattere insieme contro l'oscurità pagana alla fine del mondo\nE sì, i mangiatori di rane sono venuti da noi. Ma semplicemente non sono riusciti a mettersi d'accordo su nulla - il nostro ospite onorato siede in una villa del governatore, sotto la guardia, beve caffè e riscalda un seggio. Quasi un mese ormai! La gente ha chiacchierato, ha parlato a lungo e si è abituata - guarda, l'abate francese serve un servizio di preghiera la sera in chiesa. Quasi come uno spettacolo ahah!";
			link.l1 = "Interessante! Dovrei dare un'occhiata a quel francese, almeno è più divertente che fissare una canna.";
			link.l1.go = "LH_tavern_1";
		break;
		
		case "LH_tavern_1":
			DialogExit();
			LongHappy_SantiagoBenua();
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
