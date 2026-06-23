// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = RandPhraseSimple("Was für Fragen?","Was möchten Sie?");
			link.l1 = RandPhraseSimple("Ich habe es mir anders überlegt.","Ich habe im Moment nichts zu sagen.");
			link.l1.go = "exit";
			//Бремя гасконца
			if (CheckAttribute(pchar, "questTemp.Sharlie.Citcount") && !CheckAttribute(npchar, "quest.Sharlie"))
			{
				link.l1 = "Entschuldigen Sie, "+GetAddress_FormToNPC(NPChar)+"können Sie mir sagen, wo ich Michel de Monper finden kann? Ich habe gehört, er ist in der Stadt.";
				link.l1.go = "Sharlie";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "findskiper" && !CheckAttribute(npchar, "quest.Sharlie1"))
			{
				link.l1 = "Einen Moment bitte, "+GetAddress_FormToNPC(NPChar)+", ich möchte Sie etwas fragen... Ich suche einen Navigator für mein Schiff, kennen Sie jemanden?";
				link.l1.go = "Sharlie_1";
			}
			//Бремя гасконца
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
		
		//--> Бремя гасконца
		case "Sharlie":
			if (int(pchar.questTemp.Sharlie.Citcount) == 3)
			{
				dialog.text = "Hmm... Ich vermute, Sie sind erst kürzlich hier angekommen, wenn Sie sich trauen, auf offener Straße solche Fragen zu stellen... Ich rate Ihnen damit aufzuhören, wenn Sie keine Schwierigkeiten wollen. Am besten sprechen Sie mit dem Abt, er kann Ihnen vielleicht 'zur Besinnung verhelfen'. Sie können ihn in der Kirche finden.";
				link.l1 = "Ich verstehe...";
				link.l1.go = "exit";
				AddDialogExitQuest("Sharlie_SetBenua");
				DelLandQuestMark(characterFromId("FortFrance_Mayor"));
			}
			else
			{
				dialog.text = LinkRandPhrase("Nein, ich habe noch nie von ihm gehört.","Ich kann Ihnen nicht helfen, ich muss meine Arbeit erledigen.","Wer? Der Name sagt mir nichts, nein. Ich gehe dann mal.");
				link.l1 = "Ich verstehe... Dann setze ich meinen Weg fort. ";
				link.l1.go = "exit";
				npchar.quest.Sharlie = "true";
			}
		break;
		
		case "Sharlie_1":
			dialog.text = LinkRandPhrase("Nein, ich kenne keine Navigatoren.","Ich muss meine Arbeit erledigen und nein, fragen Sie jemand anderen...","Leider kann ich Ihnen nicht helfen, ich kenne niemanden.");
			link.l1 = "Ich verstehe. Dann werde ich woanders fragen.";
			link.l1.go = "exit";
			npchar.quest.Sharlie1 = "true";
			npchar.dialog.currentnode = "first time";
		break;
		//<-- Бремя Гасконца
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
