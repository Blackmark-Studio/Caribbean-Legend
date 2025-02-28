// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
            dialog.text = RandPhraseSimple("Welche Art von Fragen?","Was willst du?");
			link.l1 = RandPhraseSimple("Ich habe meine Meinung geändert.","Ich habe jetzt nichts zu sagen.");
		    link.l1.go = "exit";
			//Jason, суп из черепахи
			if (CheckAttribute(PChar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "baster" && !CheckAttribute(npchar, "quest.terrapin") && CheckAttribute(PChar, "questTemp.Terrapin.SJ_count"))
			{
				link.l1 = "Ich suche Herrn Jones. Kennen Sie ihn?";
				link.l1.go = "terrapin";
			}
		break;
		
		case "terrapin":
			if (sti(pchar.questTemp.Terrapin.SJ_count) == 5 || rand(9) == 1) // 10% или числом
			{
				dialog.text = "Es gibt hier viele Jones'. Der bekannteste, den ich kenne, ist ein Adjutant unter Oberst Fox, Benjamin Jones. Er begrüßt normalerweise Besucher im Hauptquartier des Regiments.";
				link.l1 = "Hat er eine Schwester namens Molly?";
				link.l1.go = "terrapin_yes";
			}
			else
			{
				dialog.text = LinkRandPhrase("Welchen Jones brauchen Sie? Ich kenne mindestens zwei Dutzend von ihnen...","Wir haben hier zu viele Jones'. Sie müssen spezifischer sein.","Es gibt hier viele Jones', sowie Johnsons oder Jacksons. Sie müssen genauer sein, aye?");
				link.l1 = "Er hat eine erwachsene Schwester namens Molly. Mir wurde gesagt, dass sie eine seltene Schönheit ist?";
				link.l1.go = "terrapin_no";
			}
			npchar.quest.terrapin = "true";
		break;
		
		case "terrapin_no":
			dialog.text = RandPhraseSimple(LinkRandPhrase("Hm, ich fürchte, ich kann Ihnen damit nicht helfen.","Nein, ich kenne ihn nicht.","Phah! Wenn die Molly Jones, die ich kenne, eine seltene Schönheit ist, dann ist Oberst Fox ein Pfarrer."),LinkRandPhrase("Ich kenne ein paar Molly Jones'. Eine von ihnen hat einen Bruder, aber... sie ist nicht die, die du suchst. Nur ein Mann, der mit Affen gelebt hat, würde sie 'eine seltene Schönheit' nennen.","Es tut mir leid, aber alle Jones', die ich kenne, haben keine Schwestern.","Es tut mir leid, ich kann Ihnen nicht helfen. Fragen Sie jemand anderen."));
			link.l1 = "Ich verstehe. Entschuldigung für die Unannehmlichkeiten.";
			link.l1.go = "exit";
			pchar.questTemp.Terrapin.SJ_count = sti(pchar.questTemp.Terrapin.SJ_count)+1;
		break;
		
		case "terrapin_yes":
			dialog.text = "Ja, aber sie wäre besser dran als sein Bruder. Diese kräftige Frau wird sich wegen ihres hässlichen Gesichts wahrscheinlich keinen Bräutigam finden.";
			link.l1 = "Mein Dank.";
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
			dialog.text = "Glaubst du, ich arbeite für den Geheimdienst von "+NationNameGenitive(sti(NPChar.nation))+"?";
			link.l1 = "Nun... nein. Lebewohl dann.";
			link.l1.go = "exit";
			link.l2 = "Gibt es noch eine andere Frage?";
			link.l2.go = "new question";
		break;
		
		case "town":
        // заменить на описание как пройти, по квестам
			dialog.text = "Sehe ich aus wie das Untersuchungsbüro? Ich weiß nicht, weiß gar nichts.";

            link.l1 = "Du bist so ein verwirrter Kopf! Verschwinde.";
			link.l1.go = "exit";
			link.l2 = "Gibt es noch eine andere Frage?";
			link.l2.go = "new question";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
