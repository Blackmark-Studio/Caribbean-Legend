// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Welche Art von Fragen?","Was willst du, "+GetAddress_Form(NPChar)+"?"),"Du hast bereits versucht, mir eine Frage zu stellen "+GetAddress_Form(NPChar)+"...","Sie sprechen heute zum dritten Mal über eine Frage...","Schau, wenn du mir nichts über die Hafenangelegenheiten zu erzählen hast, dann belästige mich nicht mit deinen Fragen.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Ich habe meine Meinung geändert.","Ich habe nichts zu besprechen."),"Macht nichts.","Tatsächlich, schon das dritte Mal...","Es tut mir leid, aber ich interessiere mich momentan nicht für die Angelegenheiten des Hafens.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//--> Бремя гасконца
		if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "ship" && !CheckAttribute(npchar, "quest.RescueDaughter"))
		{
			DelLandQuestMark(npchar);
			link.l1 = "Herr, ich suche eine Arbeit. Aber keine Hafenarbeiterstelle, etwas mehr passend zu meinem Rang. Mission, Dienst, mit heiklen Angelegenheiten... Ich nehme jede Aufgabe an, die Sie haben.";
			link.l1.go = "Sharlie";
		}
		//<-- Бремя гасконца
		
		// Jason „олго и счастливо
		if (CheckAttribute(pchar, "questTemp.LongHappy") && pchar.questTemp.LongHappy == "portman")
		{
			link.l1 = "Ich habe gehört, Sie hätten einen Brief für mich. Der Name ist Kapitän Charles de Maure.";
			link.l1.go = "LH_letter";
		}
		//--> Эпилог
		if (CheckAttribute(pchar, "questTemp.SharlieEpilog_PU_Ulysse"))
		{
			link.l1 = "Ich habe gehört, die Pinasse '"+GetShipName("Ulysse")+"' wurde kürzlich versteigert. Stimmt das?";
			link.l1.go = "SharlieEpilog_PU_Ulysse_1";
		}
		//<-- Эпилог
		break;
		
		case "Sharlie":
			dialog.text = "Hilfe? Hm. Mir geht es gut, Gott sei Dank. Aber einer meiner Freunde braucht wirklich dringend Hilfe. Er will alleine in den Dschungel gehen, um gegen die Indianer zu kämpfen, das ist absoluter Wahnsinn!\nIch versuchte, ihm Vernunft beizubringen, flehte ihn an, aber er hörte nicht zu! Er sorgt sich zu sehr um seine Tochter und ist bereit, sein Leben für sie zu geben!";
			link.l1 = "Warte mal, lass uns von vorne anfangen: Wer ist dein Freund, wo kann ich ihn finden und welche Art von Hilfe benötigt er?";
			link.l1.go = "Sharlie_1";			
		break;
		
		case "Sharlie_1":
			dialog.text = "Ach, entschuldigen Sie mich, ich bin einfach zu besorgt. Sein Name ist Prosper...Prosper Troubale. Er wird sicher sterben! Und ich kann ihm nicht helfen - ich bin kein Soldat. Seine Tochter ist verschwunden und er glaubt, dass die einheimischen Indianer dafür verantwortlich sind\nStell dir vor, er plant, alleine gegen die wilden Barbaren vorzugehen! Sie werden ihn in Stücke schneiden... In diesem Moment kauft er ein Musket und bereitet sich darauf vor, in den Dschungel zu gehen!";
			link.l1 = "Sie sind ein elender Geschichtenerzähler, Bursche. Wo kann ich Ihren Freund finden... wie war sein Name... Prosper?";
			link.l1.go = "Sharlie_2";			
		break;
		
		case "Sharlie_2":
			dialog.text = "Ich habe gerade mit ihm gesprochen und versucht, ihn umzustimmen. Er ist nicht weit von den Stadttoren entfernt, am Brunnen, und prüft seine Muskete und Munition. Geh zu ihm und tu etwas! Wenn er alleine in den Dschungel geht, wird er nicht zurückkommen, da bin ich sicher. Die rothäutigen Teufel werden ihn in Stücke reißen...";
			link.l1 = "Hör auf zu faseln, du klingst wie eine alte Frau! Ich gehe sofort zu deinem Freund. Ich hoffe, dass ich ihm helfen kann.";
			link.l1.go = "Sharlie_3";			
		break;
		
		case "Sharlie_3":
			DialogExit();
			AddQuestRecord("SharlieF", "1");
			RescueDaughter_CreateProsper();
			npchar.quest.RescueDaughter = "true";
			QuestPointerDelLoc("fortfrance_town", "reload", "reload10_back");
		break;
		
		// Jason „олго и счастливо
		case "LH_letter":
			dialog.text = "Ja, du hast recht - es gibt einen Umschlag. Hier ist er, aber zuerst musst du für die Lieferung bezahlen - zwölftausend Silberpesos.";
			if (sti(pchar.money) >= 12000)
			{
				link.l1 = "Ich habe schon immer vermutet, dass Ihr Handel ursprünglich ein Diebesgeschäft war, aber irgendwie habe ich die Post verpasst, hm. Bitte, hier ist Ihr Geld.";
				link.l1.go = "LH_letter_1";
			}
			else
			{
				link.l1 = "Ich komme später zurück, ich glaube, ich habe meinen Geldbeutel in der Taverne gelassen.";
				link.l1.go = "exit";
			}
		break;
		
		case "LH_letter_1":
			DialogExit();
			AddMoneyToCharacter(pchar, -12000);
			LongHappy_RecibeLetter();
		break;
		
		//--> Эпилог
		case "SharlieEpilog_PU_Ulysse_1":
			dialog.text = "Stimmt genau. Der Besitzer des Schiffs hat sich in Versicherungsschulden verstrickt und es zur Auktion freigegeben. Nur sind Sie ein wenig zu spät – die Versteigerung ist schon vorbei, und der neue Eigentümer erledigt gerade den Papierkram.";
			link.l1 = "Können Sie mir sagen, wo ich ihn finden kann? Ich muss mit ihm sprechen.";
			link.l1.go = "SharlieEpilog_PU_Ulysse_2";
			DelLandQuestMark(npchar);
			SharlieEpilog_SpawnPikar();
		break;
		
		case "SharlieEpilog_PU_Ulysse_2":
			dialog.text = "Warum ihn suchen? Drehen Sie sich um – er steht direkt hinter Ihnen.";
			link.l1 = "...";
			link.l1.go = "exit";			
		break;
		//<-- Эпилог
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
