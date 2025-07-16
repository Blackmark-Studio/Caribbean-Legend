// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
            dialog.text = RandPhraseSimple("Qual tipo di domande?","Cosa vuoi?");
			link.l1 = RandPhraseSimple("Mi sono ravveduto.","Non ho nulla da dire ora.");
		    link.l1.go = "exit";
		break;
		
		case "info":
			dialog.text = LinkRandPhrase("Di chi sei interessato?","Chi intendi?","Ebbene, chi è?");
			if (CheckAttribute(pchar, "questTemp.Saga"))
			{
				link.l1 = "Voglio saperne di più su Jan Svenson.";
				link.l1.go = "svenson";
			}
			link.l2 = "Cambiamo argomento...";
			link.l2.go = "new question";
		break;
		
		case "town":
			dialog.text = LinkRandPhrase("Dove vuoi andare?","Cosa stai cercando?","Di cosa hai bisogno esattamente?");
			if (CheckAttribute(pchar, "questTemp.Saga"))
			{
				link.l1 = "Dove si trova la casa di Jan Svenson?";
				link.l1.go = "svenson_house";
			}
			link.l2 = "Cambiamo argomento...";
			link.l2.go = "new question";
		break;
		
		case "svenson":
			dialog.text = RandPhraseSimple("Oh, il nostro Jan Svenson è una persona molto importante. In passato era il pirata più audace del Western Main e anche ora non ha ancora iniziato a arrugginire, ah! Ma quei giorni sono finiti, non è più attivo come prima. Possiede una villa e vive lì con la sua giovane moglie ed è sempre un ospite gradito alla residenza del governatore. Molti ospiti vengono da Jan, per lo più pirati.","Jan Svenson è una leggenda della Western Main! Diavolo della Foresta, così lo chiamavano gli spagnoli quando li cacciava da qui. Un tempo era un famoso corsaro, ma ora è un rispettato cittadino della nostra colonia\nAnche se continua a fare qualche 'affare' sul lato, ma non più con le sue mani. Raramente lascia casa sua da quando ha sposato una giovane bellezza.");
			link.l1 = "Grazie mille.";
			link.l1.go = "exit";
		break;
		
		case "svenson_house":
			dialog.text = RandPhraseSimple("Vai dritto dal molo fino a quando vedi la piazza, la casa sulla destra vicino alla fontana è la villa di Svenson.","Vai al molo attraverso la piazza dalla residenza del governatore, la casa sulla sinistra vicino alla fontana è la villa di Svenson.");
			link.l1 = "Grazie mille.";
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
