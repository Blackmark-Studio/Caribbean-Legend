// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
 	switch(Dialog.CurrentNode)
	{
        case "quests":
            dialog.text = "Speak, I'm listening";
			link.l1 = "I was mistaken. Farewell.";
			link.l1.go = "Exit";
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "jewelry_4")
			{
				link.l1 = "Officer, it has come to my attention that an officer of the vessel 'Cantavro' is being held here. Is that correct?";
                link.l1.go = "Mtraxx";
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "jewelry_8")
			{
				link.l1 = "I've come back to inquire about Don Lope again, officer. Have you already received his release orders?";
                link.l1.go = "Mtraxx_5";
			}
		break;
		
		// Addon 2016-1 Jason пиратская линейка
		case "Mtraxx":
            dialog.text = "The officer of 'Cantavro'? Don Lope Montoro? Yes, he is being held here. What's it to you?";
			link.l1 = "I would like permission to visit him.";
			link.l1.go = "Mtraxx_1";
			DelLandQuestMark(npchar);
			AddLandQuestMark(characterFromId("Lope"), "questmarkmain");
		break;
		
		case "Mtraxx_1":
            dialog.text = "I beg your pardon, but on what grounds?";
			link.l1 = "It's just a personal matter. I knew him back in Europe, and was shocked by the news of his imprisonment, and by the gossip that spread throughout the town. I would like to talk to him.";
			link.l1.go = "Mtraxx_2";
		break;
		
		case "Mtraxx_2":
            dialog.text = "Hm...";
			link.l1 = "Officer, perhaps I could... 'thank' you for letting me visit him?";
			link.l1.go = "Mtraxx_3";
		break;
		
		case "Mtraxx_3":
            dialog.text = "There is no need for that. I permit you to meet with Don Montoro. The guards will let you pass.";
			link.l1 = "Thank you!";
			link.l1.go = "Mtraxx_4";
		break;
		
		case "Mtraxx_4":
			DialogExit();
            pchar.questTemp.jailCanMove = true;
			pchar.questTemp.Mtraxx = "jewelry_5";
		break;
		
		case "Mtraxx_5":
            dialog.text = "Indeed, my orders are to deliver Don Lope Montoro to the commandant directly. But I suppose he won't be leaving the cell for a couple of weeks. You can go see him though, while he is still here.";
			link.l1 = "Thank you, officer, that is why I am here.";
			link.l1.go = "Mtraxx_6";
			DelLandQuestMark(npchar);
		break;
		
		case "Mtraxx_6":
            DialogExit();
            pchar.questTemp.jailCanMove = true;
			pchar.questTemp.Mtraxx = "jewelry_9";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
