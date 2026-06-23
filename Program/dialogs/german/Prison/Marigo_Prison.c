// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
 	switch(Dialog.CurrentNode)
	{
        case "quests":
            dialog.text = "Sprechen Sie, ich höre zu";
			link.l1 = "Ich habe mich geirrt. Lebewohl.";
			link.l1.go = "Exit";
			//искушение барбазона
			if (CheckAttribute(pchar, "questTemp.Saga.BarbTemptation.Prison"))
            { 
                link.l1 = "Sie haben hier Simon Morelle unter Arrest. Er ist ein Schmuggler, dessen Schoner vor nicht allzu langer Zeit von einer Patrouille versenkt wurde. Kann ich ihn sehen?";
                link.l1.go = "BarbTemptation";
				DeleteAttribute(pchar, "questTemp.Saga.BarbTemptation.Prison");
            }
			// Addon-2016 Jason ФМК-Сент-Кристофер
			if (CheckAttribute(PChar, "questTemp.FMQN") && pchar.questTemp.FMQN == "way_div")
			{
				link.l1 = "Offizier, ich wurde hierher geschickt vom Mynheer Gouverneur von Philipsburg. Er bat mich, die Insel und ihre Gewässer auf der Suche nach englischen Spionen zu durchsuchen. Seine Exzellenz hat mir auch gesagt, dass Sie mir nützliche Informationen geben können.";
				link.l1.go = "FMQN";
			}
			if (CheckAttribute(PChar, "questTemp.FMQN") && pchar.questTemp.FMQN == "way_div_2")
			{
				link.l1 = "Offizier, ich habe die vermisste Patrouille gefunden. Ich habe auch die britischen Spione gefunden. Sie sind hier auf der Insel.";
				link.l1.go = "FMQN_3";
			}
			if (CheckAttribute(PChar, "questTemp.FMQN") && pchar.questTemp.FMQN == "hol_peace_rew")
			{
				link.l1 = "Wieder ich, Offizier. Haben Sie die Spione festgenommen?";
				link.l1.go = "FMQN_8";
			}
		break;
		
		//искушение барбазона
		case "BarbTemptation":
			dialog.text = "Und warum brauchen Sie ihn, Herr?";
			link.l1 = "Ich möchte ihm sagen, dass er ein verdammt Bastard und Schurke ist. Ich hoffe, dass es ihm hilft, am Galgen zu stehen.";
			link.l1.go = "BarbTemptation_1";
		break;
		
		case "BarbTemptation_1":
			dialog.text = "Ha-ha! Sie haben Humor, Herr... Nun, zweitausend Pesos und Sie können weitergehen.";
			if(int(Pchar.money) >= 2000)
			{
				link.l1 = "Nimm es, Offizier. Danke!";
				link.l1.go = "BarbTemptation_2";
			}
			link.l2 = "Hm... Weißt du, ich habe es mir anders überlegt. Ich verschwende mein Geld lieber in der Taverne.";
			link.l2.go = "BarbTemptation_4";
		break;
		
		case "BarbTemptation_2":
			AddMoneyToCharacter(pchar, -2000);
			dialog.text = "Bitte sehr... Geh weiter!";
			link.l1 = "...";
			link.l1.go = "exit";
			pchar.questTemp.jailCanMove = true;
		break;
		
		case "BarbTemptation_4":
			dialog.text = "Wie du willst, ein solches Angebot bekommst du das nächste Mal nicht.";
			link.l1 = "Es ist mir sowieso egal. Auf Wiedersehen, Offizier!";
			link.l1.go = "exit";
		break;
		
		// Addon-2016 Jason ФМК-Сент-Кристофер
		case "FMQN":
			DelLandQuestMark(npchar);
			dialog.text = "Nützlich? Ha! Bei näherer Überlegung, warte. Ich habe etwas Nützliches zu erzählen. Eine unserer Patrouillen ist im Dschungel verschwunden. Sie sollten schon längst in ihren Kasernen zurück sein, aber es scheint, dass sie die Gesellschaft von Papageien bevorzugen. Oder es ist wirklich etwas passiert. Wenn du sie bei deiner Suche findest, bitte, sag ihnen, sie sollen eine anständige Rechtfertigung für ihre Verspätung vorbereiten, sonst werden sie die Konsequenzen nicht mögen... Der Kommandeur der Patrouille heißt Jannes Hoffman.";
			link.l1 = "Ist das alles, Offizier?";
			link.l1.go = "FMQN_1";
		break;
		
		case "FMQN_1":
			dialog.text = "Ja, verdammt. Es tut mir leid, aber ich habe nichts weiter zu sagen. Viel Glück, Kapitän.";
			link.l1 = "Danke...";
			link.l1.go = "FMQN_2";
		break;
		
		case "FMQN_2":
			DialogExit();
			pchar.questTemp.FMQN = "way_div_1";
			AddQuestRecord("FMQ_Nevis", "10");
			FMQN_SetSoldiersInCave();
		break;
		
		case "FMQN_3":
			DelLandQuestMark(npchar);
			dialog.text = "Was?! Ich hoffe, du machst keine Witze? Gib mir einen Bericht!";
			link.l1 = "Ich traf eine Patrouille in der Nähe einer Höhle im Dschungel. Sie hielten mich an und fragten, wohin ich unterwegs war und warum, dann ließen sie mich gehen. Verdammt, wenn das nicht die Briten waren, getarnt in holländischen Uniformen! Ich sah auch etwas Merkwürdiges im Dschungel, das aussah wie eine Gruppe nackter Männer, verborgen in den Büschen. Ich gehe davon aus, dass die britische Überfalltruppe deine Patrouille entwaffnet und ihre Uniformen genommen hat.";
			link.l1.go = "FMQN_4";
		break;
		
		case "FMQN_4":
			dialog.text = " Hallo, Freund. ";
			link.l1 = "Wie Sie verstehen, habe ich es nicht gewagt, gegen eine Truppe ausgebildeter Rotröcke zu kämpfen, und so bin ich stattdessen mit einem Bericht zu Ihnen geeilt.";
			link.l1.go = "FMQN_5";
		break;
		
		case "FMQN_5":
			dialog.text = "Nun-nun... Eine Höhle sagst du? Wie viele von ihnen hast du gezählt??";
			link.l1 = "Fünf Männer. Und ja, ich glaube, sie sind in diese Höhle gegangen.";
			link.l1.go = "FMQN_6";
		break;
		
		case "FMQN_6":
			dialog.text = "Ich schicke sofort eine Truppe zur Höhle! Kapitän, wenn die Männer, die Sie getroffen haben, wirklich britische Spione sind, werden Sie eine wohlverdiente Belohnung erhalten. Sie sind frei, sich der Truppe anzuschließen, wenn Sie den Behörden bei der Festnahme dieser Bastarde helfen und eine zusätzliche Belohnung erhalten möchten, das sind schließlich die Befehle des Gouverneurs. Also, kommst du mit?";
			link.l1 = "Nein Offizier, Spione zu jagen ist deine Aufgabe. Stellen Sie sicher, dass Sie das gut bewaffnete Team schicken, diese Abschaum sind zu gefährlich...";
			link.l1.go = "FMQN_7";
			link.l2 = "Ich denke, das kann ich tun. Ihre Männer werden die Spione mit meiner Hilfe schneller finden.";
			link.l2.go = "FMQN_10";
		break;
		
		case "FMQN_7":
			dialog.text = "Ihre Wahl, Kapitän, ich werde Ihren Rat berücksichtigen. Kommen Sie morgen zu mir, um die Ergebnisse unserer Operation zu hören.";
			link.l1 = "Bis morgen.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQN_HollandPeace");
		break;
		
		case "FMQN_8":
			DelLandQuestMark(npchar);
			dialog.text = "Ihre Informationen waren korrekt, Kapitän. Wir haben diese Bastarde in der Höhle gefunden. Sie zeigten keine Absicht, sich zu ergeben und haben den Kampf aufgenommen. Als Ergebnis - wir haben alle von ihnen eliminiert.. Wir haben auch die vermisste Patrouille gefunden. Sie sind wohlauf und am Leben, wenn auch ein bisschen mitgenommen... Danke, Kapitän, im Namen aller guten Bürger von Philipsburg. Ihre Wachsamkeit wird wie versprochen belohnt. Bitte nehmen Sie es.";
			link.l1 = "Danke dir!";
			link.l1.go = "FMQN_9";
		break;
		
		case "FMQN_9":
			AddMoneyToCharacter(pchar, 10000);
			dialog.text = "Sie sind immer ein willkommener Gast auf Sint-Maarten. Jetzt entschuldigen Sie mich bitte, ich habe andere Angelegenheiten zu erledigen.";
			link.l1 = "Auch ich. Lebewohl.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQN_HollandPeaceComplete");
		break;
		
		case "FMQN_10":
			dialog.text = "Sehr gut. Ihre Hilfe wird am meisten geschätzt. Gehen Sie zum Stadttor, das Strafkommando wird dort in einer Stunde versammelt sein.";
			link.l1 = "Ein kleiner Rat, Sie sollten die besten Soldaten, die Sie haben, für diese Mission schicken. Diese Spione sind gefährlich.";
			link.l1.go = "FMQN_11";
		break;
		
		case "FMQN_11":
			dialog.text = "Machen Sie sich keine Sorgen. Ich schicke unsere erfahrensten Soldaten unter dem Kommando von Offizier Hans Shulte - dem Meisterschwertkämpfer von Philipsburg.";
			link.l1 = "Großartig! Dann verschwenden wir keine Zeit.";
			link.l1.go = "exit";
			WaitDate("",0,0,0,1,5);
			AddDialogExitQuestFunction("FMQN_HollandBattle");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
