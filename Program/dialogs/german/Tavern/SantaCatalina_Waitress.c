// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Fragen, "+GetAddress_Form(NPChar)+"?","Wie kann ich Ihnen helfen, "+GetAddress_Form(NPChar)+"?"),""+GetSexPhrase("Hm, was ist die große Idee, "+GetAddress_Form(NPChar)+"? ","Wieder mit den seltsamen Fragen? Toots, geh und trink etwas Rum oder so...")+"","Den ganzen Tag über ist das das dritte Mal, dass du von irgendeiner Frage sprichst..."+GetSexPhrase(" Sind das einige Zeichen der Aufmerksamkeit?","")+"","Mehr Fragen, nehme ich an, "+GetAddress_Form(NPChar)+"?","Block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Ich habe meine Meinung geändert","Ich habe im Moment nichts zu besprechen."),"Nein, nein schöne...","Keine Chance, Liebling...","Nein, welche Fragen?...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;

		case "helendrinking":
			dialog.text = "Wie haben Sie geschlafen, Herr? Frau MacArthur hat uns befohlen, Ihren vollen Komfort zu gewährleisten!";
			link.l1 = "Ich hatte einen sehr seltsamen Traum...";
			link.l1.go = "helendrinking_1";
		break;

		case "helendrinking_1":
			dialog.text = "Ach!...";
			link.l1 = "Was ist los, Mademoiselle? Kann ich Ihnen bei etwas helfen?";
			link.l1.go = "helendrinking_2";
		break;

		case "helendrinking_2":
			dialog.text = "Es tut mir leid, Kapitän... Es ist eine Sünde, aber ich kann nicht widerstehen! Ich bin nicht sehr erfahren, aber verweigere dem Mädchen nicht, Kapitän! Du bist so gut aussehend! Ich möchte dir gefallen, dich berühren...";
			link.l1 = "Tatsächlich, voller Komfort... Du bist auch sehr schön! Komm schon, sei nicht schüchtern.";
			link.l1.go = "helendrinking_sex";
			link.l2 = "Es wäre besser, mich gerade jetzt nicht zu berühren, Mademoiselle - Ich stinke nach Rum. Aber du kannst mir einen Gefallen tun - ein Frühstück wäre sehr willkommen!";
			link.l2.go = "helendrinking_nosex";
		break;
		
		case "helendrinking_sex":
			dialog.text = "Ach du meine Güte!";
			link.l1 = "";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "exit";
			
			pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) - 1;
			Notification_Approve(false, "Helena");
			AddDialogExitQuestFunction("HelenDrinking_WaitressSex");
		break;

		case "helendrinking_nosex":
			dialog.text = "Unverschämt!";
			link.l1 = "Kein Frühstück dann?";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "exit";
			
			pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) + 1;
			Notification_Approve(true, "Helena");
			AddDialogExitQuestFunction("HelenDrinking_WaitressNoSex");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
