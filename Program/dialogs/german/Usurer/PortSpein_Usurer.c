// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Welche Fragen haben Sie?","Wie kann ich Ihnen helfen?"),"Du hast versucht, mir diese Frage vor kurzem zu stellen...","Ja, lass mich raten... Wieder mal im Kreis unterwegs?","Hör zu, ich mache hier die Finanzen, ich beantworte keine Fragen...","Block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Ich habe es mir anders überlegt...","Ich habe im Moment nichts zu besprechen."),"Hmm, wo ist mein Gedächtnis hin...","Sie haben es erraten, es tut mir leid...","Ich verstehe...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//Цена чахотки
			if (!CheckAttribute(npchar, "quest.Consumption") && CheckAttribute(pchar, "questTemp.Consumption.AskJuan"))
			{
				link.l1 = "Hör zu, bedeutet der Name 'Juan' dir irgendwas?";
				link.l1.go = "Consumption";
			}
		break;
		
		//Цена чахотки
		case "Consumption":
			dialog.text = "Ich weiß es nicht. Und ich will es auch nicht wissen. Ich empfehle Ihnen auch nicht, es zu wissen. Und jetzt müssen Sie mich entschuldigen, aber ich habe Geschäfte, zu denen ich zurückkehren muss. Ich nehme an, dass Sie wahrscheinlich auch Geschäfte zu erledigen haben? Also gehen Sie weg und kümmern Sie sich darum.";
			link.l1 = "Gut, in Ordnung. Entschuldigung, dass ich Sie belästigt habe...";
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
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
