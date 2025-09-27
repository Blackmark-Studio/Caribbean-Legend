// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
 	switch(Dialog.CurrentNode)
	{
        case "quests":
            dialog.text = "Speak, I'm listening";
			link.l1 = "I was mistaken. Farewell.";
			link.l1.go = "Exit";
			//Цена чахотки
			if (!CheckAttribute(npchar, "quest.Consumption") && CheckAttribute(pchar, "questTemp.Consumption") && pchar.questTemp.Consumption == "begin")
			{
				link.l1 = "I am informed that there is an epidemic here, am I correct?";
				link.l1.go = "Consumption";
			}
		break;
		
		//--> Цена чахотки
		case "Consumption":
			dialog.text = "You are correct, so avoid visiting the dungeons without a good reason. Why are you interested in this?";
			link.l1 = "Just curious. So if my boys get too drunk, make too much noise and end up here, should I prepare some yellow linen then?";
			link.l1.go = "Consumption_1";
		break;
		
		case "Consumption_1":
			dialog.text = "Alas, señor, I don't get the joke, in case you were joking. The dungeons are damp and cold, as you know the climate. Consumption is a frequent guest in these dungeons. I even have to pay my lads extra to bring food to the chambers. Patrolling there is considered as bad as penal servitude.";
			link.l1 = "I am sorry, I just wanted to know how serious this is?";
			link.l1.go = "Consumption_2";
		break;
		
		case "Consumption_2":
			dialog.text = "Far too serious. We don't even have a physician here; he died of the damn consumption too. Now only a medic from the local garrison examines prisoners once a week. But who cares about these tramps and criminals?\nMost folks think they fully deserved such a fate, and it's hard to argue with that.";
			link.l1 = "My knowledge of medicine is modest, but as far as I know, consumption is dangerous and deadly, but it doesn't kill people in a few days like it does here. Shouldn't victims suffer for months or even years?";
			link.l1.go = "Consumption_3";
		break;
		
		case "Consumption_3":
			dialog.text = "As you have just mentioned, you are not a medic, therefore talking about the disease's characteristics could be just... a made-up lie. I just repeated what our physician had been saying before the disease took him too. So I don't understand your curiosity and cynical behaviour. People die here!";
			link.l1 = "Haven't you just said that they deserved it?";
			link.l1.go = "Consumption_4";
		break;
		
		case "Consumption_4":
			dialog.text = "Enough, señor! I believe that you and I have other matters to attend to than to compete in wit. The door is right behind you.";
			link.l1 = "Fine, forgive my tactlessness, I am leaving already.";
			link.l1.go = "Consumption_5";
		break;
		
		case "Consumption_5":
			DialogExit();
			npchar.quest.Consumption = "true";
			pchar.questTemp.Consumption.Commandant = "true";
			AddQuestRecord("Consumption", "3");
			pchar.quest.Consumption.win_condition.l1 = "location";
			pchar.quest.Consumption.win_condition.l1.location = "PortSpein_houseF2";
			pchar.quest.Consumption.function = "Consumption_CommandantHouse";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
