// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
            dialog.text = RandPhraseSimple("Che tipo di domande?","Cosa vuoi?");
			link.l1 = RandPhraseSimple("Ho cambiato idea.","Non ho nulla da dire ora.");
		    link.l1.go = "exit";
			//Jason, суп из черепахи
			if (CheckAttribute(PChar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "baster" && !CheckAttribute(npchar, "quest.terrapin") && CheckAttribute(PChar, "questTemp.Terrapin.SJ_count"))
			{
				link.l1 = "Cerco il signor Jones. Lo conosci?";
				link.l1.go = "terrapin";
			}
		break;
		
		case "terrapin":
			if (sti(pchar.questTemp.Terrapin.SJ_count) == 5 || rand(9) == 1) // 10% или числом
			{
				dialog.text = "Ci sono molti Jones qui. Il più rinomato che conosco è un aiutante di campo sotto il colonnello Fox, Benjamin Jones. Di solito accoglie i visitatori nel quartier generale del reggimento.";
				link.l1 = "Ha una sorella di nome Molly?";
				link.l1.go = "terrapin_yes";
			}
			else
			{
				dialog.text = LinkRandPhrase("Di quale Jones hai bisogno? Ne conosco almeno una ventina...","Abbiamo troppi Jones' qui. Devi essere più specifico.","Ci sono un sacco di Jones' qui, così come Johnsons o Jacksons. Devi essere più specifico, eh?");
				link.l1 = "Ha una sorella adulta di nome Molly. Mi hanno detto che è una rara bellezza?";
				link.l1.go = "terrapin_no";
			}
			npchar.quest.terrapin = "true";
		break;
		
		case "terrapin_no":
			dialog.text = RandPhraseSimple(LinkRandPhrase("Mh, temo di non poterti aiutare con questo.","No, non lo conosco.","Phah! Se la Molly Jones che conosco io è una rara bellezza allora il Colonnello Fox è un prete di parrocchia."),LinkRandPhrase("Conosco alcune Molly Jones'. Una di loro ha un fratello ma... non è quella che stai cercando. Solo un uomo che ha vissuto con le scimmie la chiamerebbe 'una rara bellezza'.","Mi dispiace, ma tutti i Jones che conosco non hanno sorelle.","Mi dispiace, non posso aiutarti. Chiedi a qualcun altro."));
			link.l1 = "Capisco. Scusa per il disturbo.";
			link.l1.go = "exit";
			pchar.questTemp.Terrapin.SJ_count = sti(pchar.questTemp.Terrapin.SJ_count)+1;
		break;
		
		case "terrapin_yes":
			dialog.text = "Sì, ma sarebbe meglio se fosse suo fratello. Questa robusta probabilmente non troverà uno sposo a causa della sua brutta faccia.";
			link.l1 = "Grazie mille.";
			link.l1.go = "terrapin_yes_1";
		break;
		
		case "terrapin_yes_1":
			DialogExit();
			AddQuestRecord("Terrapin", "2");
			pchar.questTemp.Terrapin.Benjamin = true;
			DeleteAttribute(pchar, "questTemp.Terrapin.SJ_count");
		break;
		
		case "info":
        // заменить на описание неких НПС, по квестам
			dialog.text = "Pensi che io lavori per il servizio segreto di "+NationNameGenitive(sti(NPChar.nation))+"?";
			link.l1 = "Beh... no. Allora addio.";
			link.l1.go = "exit";
			link.l2 = "Altre domande, allora?";
			link.l2.go = "new question";
		break;
		
		case "town":
        // заменить на описание как пройти, по квестам
			dialog.text = "Sembro forse l'ufficio delle indagini? Non lo so, non so nulla.";

            link.l1 = "Sei un vero testa di rapa! Vattene.";
			link.l1.go = "exit";
			link.l2 = "Hai altre domande, allora?";
			link.l2.go = "new question";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
