// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("All the rumours of "+GetCityName(npchar.city)+" at your service. What would you like to know?","We were just talking about that. You must have forgotten...","This is the third time today you've brought up that question...","You're repeating the same things like a parrot...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("You know, "+NPChar.name+", maybe next time.","Right, I've forgotten for some reason...","Yes, it really is the third time...","Yup...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "portprince")
			{
				link.l1 = "Tell me, has a galleon by the name of 'Santa Margarita' stopped by your colony lately? Perhaps as the prize of a privateer?";
                link.l1.go = "guardoftruth";
			}
			//--> Украденное воспоминание
			if (CheckAttribute(pchar, "questTemp.UV_DialogCitizen"))
			{
				link.l1 = "Has Tristan Renier been through here recently?";
				link.l1.go = "UV_DialogTavern";
			}
			//<-- Украденное воспоминание
		break;
		
		case "guardoftruth":
			dialog.text = "Mate, it's pretty rare for anyone to stop by our colony with prizes, and we haven't seen a galleon by that name. Hispaniola is a wild island and we're a small colony. It's quiet here. We trade with the buccaneers in the highlands for cowhides and dried beef. Privateers don't usually linger; we don't have any brothels here, and the Spanish are close by. Go search for your galleon somewhere else.";
			link.l1 = "I see. Thanks for the advice!";
			link.l1.go = "exit";
			AddQuestRecord("Guardoftruth", "7");
			pchar.questTemp.Guardoftruth = "tortuga";
		break;
		
		//--> Украденное воспоминание
		case "UV_DialogTavern":
			dialog.text = "Renier? Aye, not only has he been here, but the man hasn't left. He's taken a room.";
			link.l1 = "Fortune smiles upon me! My business with the good captain brooks no delay—his privacy must yield to necessity. Which room might I find him in?";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("UV_GoldSeagull_RoomInTavern");
			DelLandQuestMark(npchar);
		break;
		//<-- Украденное воспоминание

	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
