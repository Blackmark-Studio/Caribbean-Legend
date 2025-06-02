// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
            dialog.text = RandPhraseSimple("Che tipo di domande?","Cosa vuoi?");
			link.l1 = RandPhraseSimple("Ho cambiato idea.","Non ho nulla da dire ora.");
		    link.l1.go = "exit";
		break;
		
		case "info":
			dialog.text = LinkRandPhrase("Di chi sei interessato?","Chi intendi?","Ebbene, chi è?");
			link.l1 = "Voglio saperne di più su Fadey il Moscovita.";
			link.l1.go = "fadey";
			link.l2 = "Nessuno, non importa.";
			link.l2.go = "new question";
		break;
		
		case "town":
			dialog.text = LinkRandPhrase("Dove vuoi andare?","Cosa stai cercando?","Di che cosa hai bisogno esattamente?");
            link.l1 = "Dove si trova la casa di Fadey?";
			link.l1.go = "fadey_house";
			link.l2 = "Parliamo di qualcos'altro...";
			link.l2.go = "new question";
		break;
		
		case "fadey":
			dialog.text = RandPhraseSimple("Ah, un uomo importante. Possiede la fabbrica locale ed è in stretti rapporti con l'alta società di Basse-Terre. Ha un forte accento e gli piace davvero bere... ma non si ubriaca mai.","È un pezzo grosso e amico del governatore. Fadey possiede una fabbrica locale. È venuto da un paese del nord molto, molto lontano da qui... Non conosco nemmeno il nome. Ha mani forti ed è in grado di bere un intero barile di rum senza ubriacarsi.");
			link.l1 = "Grazie mille.";
			link.l1.go = "exit";
		break;
		
		case "fadey_house":
			dialog.text = RandPhraseSimple("Vai dritto dal molo fino a quando vedi la piazza, la casa sulla sinistra è la villa di Fadey.","Vai al molo attraverso la piazza dalla residenza del governatore, la casa sulla destra è la villa di Fadey.");
			link.l1 = "Grazie mille.";
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
