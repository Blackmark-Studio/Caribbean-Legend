// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Quali domande hai?","Come posso aiutarti, "+GetAddress_Form(NPChar)+"?"),"Hai cercato di farmi una domanda poco tempo fa, "+GetAddress_Form(NPChar)+"...","Per l'intera giornata, questa è la terza volta che parli di qualche domanda...","Altre domande, presumo?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Ho cambiato idea...","Non ho nulla di cui parlare al momento."),"Uffa, dove se n'è andata la mia memoria...","Sì, è davvero la terza volta...","No, quali domande?...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//Jason, Сага, Тени прошлого
			if (CheckAttribute(PChar, "questTemp.Saga.Shadows") && pchar.questTemp.Saga.Shadows == "sentjons")
			{
				link.l1 = "Sto cercando Raymond Baker, un ex boia. Sai se è vivo e dove posso trovarlo?";
				link.l1.go = "baker";
			}
			//Jason, суп из черепахи
			if (CheckAttribute(PChar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "baster" && !CheckAttribute(npchar, "quest.terrapin"))
			{
				link.l1 = "Sto cercando il signor Jones. Puoi aiutarmi nella mia ricerca, amico?";
				link.l1.go = "terrapin";
			}
			// Страж Истины
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "merdok")
			{
				link.l1 = "Ascolta, è arrivato qui in città un alchimista, un medico? È italiano, ha circa trent'anni, si chiama Gino Gvineili. Hai sentito qualcosa a riguardo?";
				link.l1.go = "guardoftruth";
			}
		break;
		
		//Сага, Тени прошлого
		case "baker":
			dialog.text = "Il nostro caro grassone è diventato più popolare del Colonnello Fox! È vivo, il poveretto. Ma non è in città in questo momento. Dopo che Raymond ha scoperto che persone serie come te si interessano a lui, si è sbrigato a vendere la sua baracca per una miseria e se n'è andato con il vento.";
			link.l1 = "Dove è andato con il vento?";
			link.l1.go = "baker_1";
		break;
		
		case "baker_1":
			dialog.text = "Oh, chi lo sa. È andato a fare il medico di bordo sulla prima nave che è passata. Solo che quella nave è tornata proprio oggi e nessuno ha visto Baker sbarcare ancora.";
			link.l1 = "Come posso trovare il capitano?";
			link.l1.go = "baker_2";
		break;
		
		case "baker_2":
			dialog.text = "Perché pensi di doverlo cercare? Sono sicuro che è già ubriaco come al solito nella sua cabina. Il suo secchio che perde si chiama 'Callow Meggy'. Tale è il capitano, tale è il nome...";
			link.l1 = "Grazie per l'aiuto, compagno!";
			link.l1.go = "baker_3";
		break;
		
		case "baker_3":
			DialogExit();
			AddQuestRecord("Shadows", "2");
			pchar.questTemp.Saga.Shadows = "baldmaggy";
			pchar.quest.Saga_ShadowsMaggy.win_condition.l1 = "location";
			pchar.quest.Saga_ShadowsMaggy.win_condition.l1.location = "Antigua";
			pchar.quest.Saga_ShadowsMaggy.function = "Saga_SetBaldMaggy";
		break;
		
		//суп из черепахи
		case "terrapin":
			dialog.text = "Signor Jones? Mi stai prendendo in giro, amico. Sai quanti cazzo di Jones ci sono su quest'isola? Devi essere più specifico di così.";
			link.l1 = "Lui ha una sorella maggiore, Molly. Dicono che sia di una bellezza sorprendente.";
			link.l1.go = "terrapin_1";
		break;
		
		case "terrapin_1":
			dialog.text = "No. Niente del genere mi viene in mente. Mi dispiace, compagno...";
			link.l1 = "Bene, se non lo sai, non lo sai...";
			link.l1.go = "exit";
			npchar.quest.terrapin = "true";
		break;
		
		case "guardoftruth":
			dialog.text = "No, non ho sentito. E abbiamo solo un alchimista in città, il farmacista John Murdock. Ha delle pozioni notevoli - curano qualsiasi malanno.";
			link.l1 = "Pensi che prepari lui stesso queste pozioni?";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "Buona domanda. Me lo chiedo anch'io di tanto in tanto. John non somiglia per niente a un intenditore di bicchieri di medicina, erbe e polveri. Più che altro sembra un ex-soldato, un mercenario... è più vicino alla verità.";
			link.l1 = "Beh, immagino che l'uomo sia troppo qualificato...";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "Forse, lo è. Ma c'è una cosa di cui sono sicuro, qualcuno vive al suo secondo piano. La finestra è costantemente coperta. Anche quando John è al piano di sotto, un suono tintinnante come fiale e bottiglie di vetro, così come l'odore di erbe bollenti, e di notte la luce non si spegne. Ecco perché sospetto che l'abitante di quella stanza sia colui che prepara i medicinali di John per la vendita.";
			link.l1 = "Mh. Osservazione interessante. Grazie, compagno!";
			link.l1.go = "exit";
			pchar.questTemp.Guardoftruth = "merdok1";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
