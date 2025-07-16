// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Quali domande hai?","Come posso aiutarti?"),"Hai cercato di farmi una domanda non molto tempo fa...","Nessuno ha fatto domande del genere in un negozio di Tortuga da molto tempo...","Domande, domande e ancora domande...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Ho cambiato idea...","Non ho nulla di cui parlare al momento."),"Uh, dove se n'è andata la mia memoria...","Va bene, quindi è passato molto tempo.","Altre domande, eh...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "tortuga2")
			{
				link.l1 = "Ascolta, devo trovare un certo Gaius Marchais. Mi è stato detto che si è messo in affari con la pirateria e si è rivelato un ottimo negoziatore, acquisendo un eccellente galeone dagli Spagnoli. Ha per caso acquistato da te qualche tipo di merce per il commercio?";
                link.l1.go = "guardoftruth";
			}
		break;
		
		case "guardoftruth":
			dialog.text = "Gaius Marchais? Oh sì, certo che me lo ricordo! Ma non ha comprato nulla. Ha offerto la sua nave per il trasporto. Mi serviva proprio una nave con una stiva spaziosa - un grosso carico di pelli grezze.";
			link.l1 = "E qual era il punto di scarico?";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "Philipsburg, Saint Maarten.";
			link.l1 = "Bene. Grazie, mi hai aiutato tanto!";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "In qualsiasi momento, capitano. Passa dal mio negozio quando vuoi!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddQuestRecord("Guardoftruth", "10");
			pchar.questTemp.Guardoftruth = "maarten";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}
