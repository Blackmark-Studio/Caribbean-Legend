// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
            dialog.text = RandPhraseSimple("Was für Fragen?","Was möchten Sie?");
			link.l1 = RandPhraseSimple("Ich habe meine Meinung geändert.","Ich habe im Moment nichts zu sagen.");
		    link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "portprince" && !CheckAttribute(npchar, "quest.Guardoftruth"))
			{
				link.l1 = "Sagen Sie, "+GetAddress_FormToNPC(NPChar)+", hat nicht vor kurzem die Galeone 'Santa Margarita' hier angelegt? Vielleicht als Prisenschiff eines Freibeuters?";
                link.l1.go = "guardoftruth";
			}
		break;
		
		case "info":
        // заменить на описание неких НПС, по квестам
			dialog.text = "Glauben Sie, ich arbeite für den Geheimdienst von "+NationNameGenitive(int(NPChar.nation))+"?";
			link.l1 = "Nun... nein. Dann leben Sie wohl.";
			link.l1.go = "exit";
			link.l2 = "Haben Sie noch eine andere Frage?";
			link.l2.go = "new question";
		break;
		
		case "town":
        // заменить на описание как пройти, по квестам
			dialog.text = "Sehe ich aus wie das Untersuchungsbüro? Ich weiß es nicht, ich weiß gar nichts.";

            link.l1 = "Sie sind so ein Wirrkopf! Verschwinden Sie.";
			link.l1.go = "exit";
			link.l2 = "Haben Sie noch eine andere Frage?";
			link.l2.go = "new question";
		break;
		
		case "guardoftruth":
			dialog.text = LinkRandPhrase("Nein, ich erinnere mich nicht an eine Galeone mit diesem Namen. Wir sehen hier selten so große Schiffe.","Was? Eine Galeone? Hier? Ich habe keine Ahnung.","Nein Sir, dieses Schiff hat hier in letzter Zeit nicht angelegt, zumindest erinnere ich mich nicht daran.");
			link.l1 = LinkRandPhrase("In Ordnung...","Ich verstehe, schade...");
			link.l1.go = "exit";
			npchar.quest.Guardoftruth = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
