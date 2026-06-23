// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Welche Art von Fragen?","Was willst du, "+GetAddress_Form(NPChar)+"?"),"Du hast schon versucht, mir eine Frage zu stellen "+GetAddress_Form(NPChar)+"...","Sie sprechen heute zum dritten Mal über eine Frage...","Schau, wenn du nichts über die Angelegenheiten des Hafens zu berichten hast, dann belästige mich nicht mit deinen Fragen.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Ich habe meine Meinung geändert.","Ich habe nichts zu besprechen."),"Macht nichts.","Tatsächlich, schon das dritte Mal...","Entschuldigung, aber ich interessiere mich momentan nicht für die Angelegenheiten des Hafens.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//Цена чахотки
			if (!CheckAttribute(npchar, "quest.Consumption") && CheckAttribute(pchar, "questTemp.Consumption.AskJuan"))
			{
				link.l1 = "Sag mir, bedeutet der Name 'Juan' dir etwas?";
				link.l1.go = "Consumption";
			}
			if (!CheckAttribute(npchar, "quest.Guardoftruth") && CheckAttribute(pchar, "questTemp.Guardoftruth.Trinidad") && pchar.questTemp.Guardoftruth.Trinidad == "begin")
			{
				link.l1 = "Herr, im April 1654 war hier eine Fregatte unter dem Kommando von Miguel Dichoso. Er ist dann verschwunden. Erinnern Sie sich nicht an etwas? Vielleicht war Dichoso hier und hat sein Schiff registriert...";
				link.l1.go = "guardoftruth";
			}
		break;
		
		//Цена чахотки
		case "Consumption":
			dialog.text = "Juan? Das ist alles? Señor, bist du betrunken oder spielst du einen dummen Scherz mit mir? Kannst du dir einen Nachnamen oder zumindest den Namen seines Schiffes merken? Dies ist eine spanische Kolonie, um Gottes willen. Weißt du, wie viele Juans hier herumlaufen? Ohne Details kann ich dir nicht helfen.";
			link.l1 = "Ich verstehe. Entschuldigung für die Störung...";
			link.l1.go = "exit";
			pchar.questTemp.Consumption.AskJuan = int(pchar.questTemp.Consumption.AskJuan)+1;
			if(int(pchar.questTemp.Consumption.AskJuan) == 3)
			{
				pchar.quest.Consumption2.win_condition.l1 = "location";
				pchar.quest.Consumption2.win_condition.l1.location = "PortSpein_town";
				pchar.quest.Consumption2.function = "Consumption_CreateSergio";
			}
			npchar.quest.Consumption = "true";
		break;
		
		case "guardoftruth":
			dialog.text = "Lassen Sie mich meine Notizen überprüfen... ah ha! Ja, Kapitän Miguel Dichoso war hier im April 1654, auf der Fregatte 'Santa-Quiteria'. Er gab an, aus der Kolonie San-Andres, Providence zu kommen. Er war auf dem Weg nach Cadiz, Spanien. Ausgelaufen am 14. April 1654. Das ist alles, was ich habe.";
			link.l1 = "Segeln nach Europa? Ich verstehe. Danke dafür!";
			link.l1.go = "exit";
			npchar.quest.guardoftruth = "true";
			AddQuestRecord("Guardoftruth", "39");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
