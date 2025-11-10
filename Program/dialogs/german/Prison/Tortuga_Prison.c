// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
 	switch(Dialog.CurrentNode)
	{
        case "quests":
            dialog.text = "Sprechen Sie, ich höre zu";
			link.l1 = "Ich habe mich geirrt. Lebewohl.";
			link.l1.go = "Exit";
		break;
		
		case "tonzag_bail":
			NextDiag.TempNode = "First_officer";
		
			dialog.text = "Welchen Zweck hat Ihr Besuch in Tortuga, Kapitän?";
			link.l1 = "Ich bitte Sie! Helfen Sie meinem Kameraden, und ich werde all Ihre Fragen beantworten!";
			link.l1.go = "tonzag_bail_a";
			link.l2 = "Sie sind eine so wichtige Person und Sie kommen hier ohne jede Bewachung an, direkt nachdem das ganze Gefängnis einen Schuss gehört hat?!";
			link.l2.go = "tonzag_bail_b";
		break;
		
		case "tonzag_bail_a":
			dialog.text = "Während du deine Antwort verzögerst, verblutet er. Ich wiederhole die Frage.";
			link.l1 = "";
			link.l1.go = "tonzag_bail_1";
		break;
		
		case "tonzag_bail_b":
			dialog.text = "Ich weiß genug über das, was passiert ist. Ich wiederhole die Frage.";
			link.l1 = "";
			link.l1.go = "tonzag_bail_1";
		break;
		
		case "tonzag_bail_1":
			dialog.text = "Letzte Chance, Kapitän.";
			link.l1 = "Ich erfülle die Aufgabe, die mir vom Generalgouverneur gegeben wurde!";
			link.l1.go = "tonzag_bail_truth";
			link.l2 = "Sie wissen sehr gut, dass ich Kapitän meines eigenen Schiffes bin und vertraglich arbeite. Und ich besuche Ihre schöne Insel ein paar Mal im Jahr!";
			link.l2.go = "tonzag_bail_lies";
		break;
		
		case "tonzag_bail_truth":
			dialog.text = "Ich hatte meine Vermutungen, war mir aber nicht ganz sicher. Du hast Glück, dass vor ein paar Tagen ein wichtiges Treffen in Capsterville stattfand. Einige sehr einflussreiche Personen haben eine Einigung erzielt. Daher bist du nicht länger mein Feind.";
			link.l1 = "Werden Sie uns helfen?";
			link.l1.go = "tonzag_bail_truth_1";
			
			AddDialogExitQuestFunction("Tonzag_GetOut");
		break;
		
		case "tonzag_bail_truth_1":
			dialog.text = "Ich werde dich sofort freilassen. Dein Kamerad wird auf das Schiff verlegt und erhält Behandlung.";
			link.l1 = "Danke dir...";
			link.l1.go = "tonzag_bail_truth_2";
		break;
		
		case "tonzag_bail_truth_2":
			dialog.text = "Du hast beinahe Schiffbruch erlitten, Charles! Verlasse und kehre mindestens einen Monat nicht nach Tortuga zurück. Lass den Staub sich legen und die Köpfe abkühlen.";
			link.l1 = "Ich werde das tun. Auf Wiedersehen!";
			link.l1.go = "exit";
			link.l2 = "Werden Sie mir gar nichts erklären? Nicht mal ein bisschen? ...";
			link.l2.go = "tonzag_bail_truth_3";
		break;
		
		case "tonzag_bail_truth_3":
			dialog.text = "Jemand hat Sie gemeldet. Angeblich sind Sie ein fanatischer Katholik, der auf unsere schöne Insel gekommen ist, um ihren ehrenwerten Gouverneur bösartig zu töten.";
			link.l1 = "Ich bin kein Fanatiker!";
			link.l1.go = "tonzag_bail_truth_4";
		break;
		
		case "tonzag_bail_truth_4":
			dialog.text = "Es ist geschickt geschrieben, glaub mir. Ich bin gut in solchen Dingen - die besten Verleumdungen enthalten zumindest ein Körnchen Wahrheit in ihnen.";
			link.l1 = "Wer hat den Bericht geschrieben?";
			link.l1.go = "tonzag_bail_truth_a";
			link.l2 = "Wer hat den Mörder ins Gefängnis gelassen?";
			link.l2.go = "tonzag_bail_truth_b";
		break;
		
		case "tonzag_bail_truth_a":
			dialog.text = "Jemand, der wollte, dass du ein paar Tage im Gefängnis eingesperrt bist, statt dich sofort auf den Foltertisch der Hugenotten im Keller von La Roche zu schicken.\nGenug, Charles. Geh. Kümmere dich erst um das, was du vor dir hast, und danach... nun, du verstehst mich!";
			link.l1 = "Ja. Das werde ich. Auf Wiedersehen, Kommandant.";
			link.l1.go = "exit";
		break;
		
		case "tonzag_bail_truth_b":
			dialog.text = "Ich habe es getan.";
			link.l1 = "Du solltest besser einen anderen holen, bevor ich hier weggehe.";
			link.l1.go = "tonzag_bail_truth_b_threat";
			link.l2 = "Ich bin ganz Ohr, Kommandant.";
			link.l2.go = "tonzag_bail_truth_b_charm";
		break;
		
		case "tonzag_bail_truth_b_threat":
			AddComplexSelfExpToScill(100, 100, 100, 100);
		
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 60) {
				dialog.text = "Ich bin nicht verpflichtet, Ihnen, Charles, irgendetwas zu erklären. Seien Sie froh, dass Sie in meinen Händen gelandet sind und nicht in denen meines unmittelbaren Vorgesetzten. Und seien Sie froh, dass Ihr Chef derjenige sein wird, der mich für all diese Störungen entschädigt, und nicht Sie.";
				link.l1 = "Riiiiiiight... Sie kennen meinen Chef nicht so gut wie ich. Auf Wiedersehen, Kommandant.";
				link.l1.go = "exit";
				
				Notification_Skill(false, 60, SKILL_LEADERSHIP);
				AddQuestRecord("Tonzag", "3.1");
			} else {
				dialog.text = "Weißt du was? Ich glaube, ich werde es dir sagen. Eine großzügige, steuerfreie Spende wurde an den besonderen Garnisonspensionsfonds gemacht. Als Dankeschön durfte der Spender zur schnellen und gesetzlichen Hinrichtung eines berüchtigten Verbrechers beitragen!";
				link.l1 = "Mein Offizier?";
				link.l1.go = "tonzag_bail_truth_b_1";
				link.l2 = "Mein Freund?";
				link.l2.go = "tonzag_bail_truth_b_1";
				
				Notification_Skill(true, 60, SKILL_LEADERSHIP);
			}
		break;
		
		case "tonzag_bail_truth_b_charm":
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 60) {
				dialog.text = "Ich bin nicht verpflichtet, Ihnen etwas zu erklären, Charles. Seien Sie froh, dass Sie in meinen Händen gelandet sind und nicht in den Händen meines direkten Vorgesetzten. Und seien Sie froh, dass Ihr Boss derjenige sein wird, der mich für all diese Störungen entschädigt, und nicht Sie.";
				link.l1 = "Jaaaaaaa... Du kennst meinen Boss nicht so gut wie ich. Auf Wiedersehen, Kommandant.";
				link.l1.go = "exit";
				
				Notification_Skill(false, 60, SKILL_LEADERSHIP);
				AddQuestRecord("Tonzag", "3.1");
			} else {
				dialog.text = "Weißt du was? Ich glaube, ich werde es dir sagen. Eine großzügige, steuerfreie Spende wurde an den speziellen Garnisonsrentenfonds gemacht. Als Dankeschön durfte der Spender zur schnellen und rechtmäßigen Hinrichtung eines berüchtigten Verbrechers beitragen!";
				link.l1 = "Mein Offizier?";
				link.l1.go = "tonzag_bail_truth_b_1";
				link.l2 = "Mein Freund?";
				link.l2.go = "tonzag_bail_truth_b_1";
				
				Notification_Skill(true, 60, SKILL_LEADERSHIP);
			}
		break;
		
		case "tonzag_bail_truth_b_1":
			dialog.text = "Verlass uns, Charles. Und nimm diesen Abschaum mit dir. Deine Wahl der Gefährten... ist enttäuschend.";
			link.l1 = "Erzähl mir zumindest, wo ich deinen... Wohltäter finde?";
			link.l1.go = "tonzag_bail_truth_b_2";
		break;
		
		case "tonzag_bail_truth_b_2":
			dialog.text = "Auf dem Festland. Auf Wiedersehen, Charles.";
			link.l1 = "";
			link.l1.go = "exit";
			
			pchar.questTemp.TonzagQuest.KnowMain = true;
			AddQuestRecord("Tonzag", "3.2");
		break;
		
		case "tonzag_bail_lies":
			dialog.text = "Es wurde eine Anzeige gegen Sie erstattet. Eine sehr üble. Kapitän, Sie wurden ganz klar hereingelegt, aber... Ich bin völlig in meiner Befugnis, Sie hier für ein paar weitere Wochen zu behalten und Ihren Freund sterben zu lassen. Es sei denn...";
			link.l1 = "Wie viel?";
			link.l1.go = "tonzag_bail_lies_a";
			link.l2 = "Wer hat mich hereingelegt? Haben Sie den Mörder ins Gefängnis gelassen?";
			link.l2.go = "tonzag_bail_lies_b";
			
			AddDialogExitQuestFunction("Tonzag_Bailed");
		break;
		
		case "tonzag_bail_lies_a":
			pchar.questTemp.TonzagQuest.Bail = 500;
			dialog.text = "Bitte hinterlegen Sie fünfhundert Dublonen in den Pensionsfonds der Tortuga-Garnison beim örtlichen Geldverleiher.";
			if (CheckAttribute(pchar, "questTemp.FMQT") && pchar.questTemp.FMQT == "end") {
				pchar.questTemp.TonzagQuest.Bail = 600;
				dialog.text = dialog.text+" Und lassen Sie uns weitere hundert Dublonen für die alten Ärger hinzufügen, die Sie verursacht haben, indem Sie sich mit einer hochrangigen Dame auf dieser Insel eingelassen haben.";
			}
			link.l1 = "Mach verdammt nochmal diese Tür auf!";
			link.l1.go = "exit";
			
			AddQuestRecord("Tonzag", "3.3");
		break;
		
		case "tonzag_bail_lies_b":
			pchar.questTemp.TonzagQuest.Bail = 500;
			dialog.text = "Sie haben bereits zu viel meiner Zeit in Anspruch genommen. Gehen Sie zum Geldverleiher und zahlen Sie fünfhundert Dublonen in den Pensionsfonds der Garnison von Tortuga ein.";
			if (CheckAttribute(pchar, "questTemp.FMQT") && pchar.questTemp.FMQT == "end") {
				pchar.questTemp.TonzagQuest.Bail = 600;
				dialog.text = dialog.text+" Und fügen wir noch einhundert Dublonen für die alten Schwierigkeiten hinzu, die Sie verursacht haben, indem Sie sich mit einer hochrangigen Dame auf dieser Insel eingelassen haben.";
			}
			link.l1 = "Mach diese verdammte Tür schon auf!";
			link.l1.go = "exit";
			
			AddQuestRecord("Tonzag", "3.3");
		break;
		
		case "tonzag_bailed":
			dialog.text = "";
			link.l1 = "Die Mittel sind eingezahlt. Wo ist Hercule?";
			link.l1.go = "tonzag_bailed_1";
		break;
		
		case "tonzag_bailed_1":
			dialog.text = "Wir haben ihm Erste Hilfe geleistet und ihn zu Ihrem Schiff geschickt. Der Schurke ist zäh, höchstwahrscheinlich wird er es überstehen. Lebewohl, Kapitän, und lassen Sie sich eine Weile nicht auf unserer Insel blicken!";
			link.l1 = "Nun, nach solch einem Empfang werde ich mich gut von hier fernhalten! Auf Wiedersehen, Kommandant.";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "First time";
			AddDialogExitQuestFunction("Tonzag_GetOut");
		break;
		
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
