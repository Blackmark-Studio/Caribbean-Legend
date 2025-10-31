// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("Go ahead, what do you want?","We were just talking about that. You must have forgotten...","This is the third time today you've brought up that question...","Listen, this is a store. People buy things here. Don't disturb me!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("You know, "+NPChar.name+", maybe next time.","Right, I've forgotten for some reason...","Yes, it really is the third time...","Hm, I won't...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//Jason --> Португалец
			if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "Findcloves" && !CheckAttribute(npchar, "quest.Portugal"))
			{
   				link.l1 = "Listen, I need some fancy clothes. Expensive ones, I want to look like a proper nobleman. Do you have anything of the sort?";
				link.l1.go = "Portugal_cloves";
			}
			//<-- Португалец
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "maarten")
			{
				link.l1 = "A galleon named 'Admirable' recently brought you a cargo of hides. Do you recall that?";
                link.l1.go = "guardoftruth";
			}
		break;
		
		//Jason --> Португалец
		case "Portugal_cloves":
			dialog.text = "Noble clothes? Sure, I've got a set lying here: trousers, a jerkin, a silk shirt, and boots. It costs 20,000 pesos. The clothes are of very high quality, they're comfortable, and have a remarkable look, so I won't take any less for them.";
			if (sti(pchar.money) >= 20000)
			{
				link.l1 = "Great! Hand it over.";
				link.l1.go = "Portugal_cloves_1";
			}
			link.l2 = "Hm... I don't have that much money at the moment.";
			link.l2.go = "Portugal_cloves_nomoney";
		break;
		
		case "Portugal_cloves_nomoney":
			dialog.text = "Then come back when you have the money.";
			link.l1 = "All right. I'll be back!";
			link.l1.go = "exit";
		break;
		
		case "Portugal_cloves_1":
			AddMoneyToCharacter(pchar, -20000);
			GiveItem2Character(pchar, "suit_1");
			Log_Info("You've received expensive clothing");
			PlaySound("interface\important_item.wav");
			dialog.text = "Here you are.";
			link.l1 = "Thank you!";
			link.l1.go = "exit";
			npchar.quest.Portugal = "true";
			sld = characterFromId("PortugalDoctor");
			sld.dialog.currentnode = "Portugal_doctor_4";
			DelLandQuestMark(characterFromId("Marigo_trader"));
			AddLandQuestMark(characterFromId("PortugalDoctor"), "questmarkmain");
			QuestPointerDelLoc("marigo_town", "reload", "reload6_back");
			QuestPointerToLoc("marigo_town", "reload", "houseF1");
		break;
		//<-- Португалец
		case "guardoftruth":
			dialog.text = "Yes. He arrived on time, unloaded the merchandise, and I paid for it as we had agreed. Why are you asking?";
			link.l1 = "The captain of that ship is Gaius Marchais, an old acquaintance of mine. So I'm trying to find him. Would you be able to tell me what he did after that? Perhaps you provided him with some additional freight, or he mentioned where he was headed?";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "Nothing of that. I didn't offer him any freight; he didn't even ask for it. He didn't share his plans for the future with me. I don't even remember all the details, do you know how many people have come in and out of here since that time? He unloaded and sailed off and that's all I can say about him.";
			link.l1 = "All right. Well, thanks anyway. All the best!";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			DialogExit();
			AddQuestRecord("Guardoftruth", "11");
			pchar.questTemp.Guardoftruth = "maarten1";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}
