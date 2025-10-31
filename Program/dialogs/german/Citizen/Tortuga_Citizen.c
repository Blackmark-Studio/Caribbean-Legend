// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
            dialog.text = RandPhraseSimple("Was für Fragen?","Was möchten Sie?");
			link.l1 = RandPhraseSimple("Ich habe meine Meinung geändert.","Ich habe im Moment nichts zu sagen.");
		    link.l1.go = "exit";
			
			// Rebbebion, "Путеводная звезда"
			if (CheckAttribute(pchar, "questTemp.PZ.TortugaCitizensAsk") && npchar.sex == "man")
			{
				link.l1 = "Sie kennen nicht zufällig einen gewissen Joep van der Vink, oder?";
				link.l1.go = "PZ_1";
			}
		break;
		
		case "info":
        // заменить на описание неких НПС, по квестам
			dialog.text = "Denken Sie, ich arbeite für den Geheimdienst von "+NationNameGenitive(sti(NPChar.nation))+"?";
			link.l1 = "Nun... nein. Dann leben Sie wohl.";
			link.l1.go = "exit";
			link.l2 = "Haben Sie noch eine andere Frage?";
			link.l2.go = "new question";
		break;
		
		case "town":
        // заменить на описание как пройти, по квестам
			dialog.text = "Sehe ich aus wie das Untersuchungsbüro? Ich weiß es nicht, ich weiß nichts.";

            link.l1 = "Sie sind so ein Wirrkopf! Verschwinden Sie.";
			link.l1.go = "exit";
			link.l2 = "Haben Sie noch eine andere Frage?";
			link.l2.go = "new question";
		break;
		
		case "PZ_1":
			dialog.text = "Nun, ich kenne ihn nicht persönlich, aber ich sehe ihn hier von Zeit zu Zeit. Warum fragen Sie?";
			link.l1 = "Ich wurde beauftragt, ihm persönlich ein Paket zu überbringen. Aber niemand will über ihn sprechen, und ich weiß nicht warum. Kennen Sie ihn? Ist er ein schlechter Mensch? Ich würde Ihre ehrliche Meinung schätzen.";
			link.l1.go = "PZ_2";
		break;
		
		case "PZ_2":
			dialog.text = "Wir kennen uns nicht persönlich, also weiß ich fast nichts. Aber er hat einen engen Freund in der Stadt, und sie werden oft zusammen gesehen. Gehen Sie zu ihm - er wird entscheiden, ob er Ihnen mehr erzählt oder nicht. Der Name seines Freundes ist Rober Martene.";
			link.l1 = "Rober Martene, sagen Sie... Und wer ist er? Wo kann ich ihn finden?";
			link.l1.go = "PZ_3";
		break;
		
		case "PZ_3":
			dialog.text = "An verschiedenen Orten, aber jetzt gerade ist er bei unserem Leuchtturm - er repariert seine Galeone nach einem schrecklichen Sturm. Sie heißt 'Voltigeur'.";
			link.l1 = "Vielen Dank! Sie haben keine Ahnung, wie sehr Sie mir geholfen haben.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_CreateRobertMartin");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
