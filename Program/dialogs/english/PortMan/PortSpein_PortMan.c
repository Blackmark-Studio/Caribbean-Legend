// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What kind of questions?","What do you want, "+GetAddress_Form(NPChar)+"?"),"You've already tried to ask me a question "+GetAddress_Form(NPChar)+"...","You've brought up that question for the third time today...","Look, if you have nothing to tell me about the port's affairs then don't bother me with your questions.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I have changed my mind.","I've got nothing to talk about."),"Never mind.","Indeed, the third time already...","Sorry, but I'm not interested in the port's affairs for now.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//Цена чахотки
			if (!CheckAttribute(npchar, "quest.Consumption") && CheckAttribute(pchar, "questTemp.Consumption.AskJuan"))
			{
				link.l1 = "Tell me, does the name 'Juan' mean anything to you?";
				link.l1.go = "Consumption";
			}
			if (!CheckAttribute(npchar, "quest.Guardoftruth") && CheckAttribute(pchar, "questTemp.Guardoftruth.Trinidad") && pchar.questTemp.Guardoftruth.Trinidad == "begin")
			{
				link.l1 = "Señor, there was a frigate here under the command of Miguel Dichoso in April 1654. He disappeared then. Don't you remember anything about it? Perhaps Dichoso was here and registered his ship...";
				link.l1.go = "guardoftruth";
			}
		break;
		
		//Цена чахотки
		case "Consumption":
			dialog.text = "Juan? That's all? Señor, are you drunk or playing a stupid joke on me? Can you remember a surname or at least the name of his ship? This is a Spanish colony, for God's sake. Do you know how many Juans we have running around here? I won't be able to help you without any details.";
			link.l1 = "I see. Sorry to bother you...";
			link.l1.go = "exit";
			pchar.questTemp.Consumption.AskJuan = sti(pchar.questTemp.Consumption.AskJuan)+1;
			if(sti(pchar.questTemp.Consumption.AskJuan) == 3)
			{
				pchar.quest.Consumption2.win_condition.l1 = "location";
				pchar.quest.Consumption2.win_condition.l1.location = "PortSpein_town";
				pchar.quest.Consumption2.function = "Consumption_CreateSergio";
			}
			npchar.quest.Consumption = "true";
		break;
		
		case "guardoftruth":
			dialog.text = "Let's see my notes... ah ha! Yes, Captain Miguel Dichoso was here in April 1654, on the frigate 'Santa-Quiteria'. He registered himself as coming from the colony of San-Andres, Providence. He was heading to Cadiz, Spain. Sailed off on April 14th, 1654. That's all I have.";
			link.l1 = "Sailing to Europe? I see. Thank you for that!";
			link.l1.go = "exit";
			npchar.quest.guardoftruth = "true";
			AddQuestRecord("Guardoftruth", "39");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
