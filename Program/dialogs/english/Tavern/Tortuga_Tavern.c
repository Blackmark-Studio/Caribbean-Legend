// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("All the rumours of "+GetCityName(npchar.city)+" at your service. What would you like to know?","We were just talking about that. You must have forgotten...","This is the third time today you've brought up this question...","You're repeating the same thing like a parrot...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("You know, "+NPChar.name+", maybe next time.","Right, I've forgotten for some reason...","Yes, it really is the third time...","Yup...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.Slavetrader == "FindRatTortuga") // работорговец
            {
                link.l1 = "Listen, where can I find François Gontier? He was supposed to have arrived at Tortuga already.";
                link.l1.go = "Tortuga_ratT_1";
            }
			// суп из черепахи
			if (CheckAttribute(PChar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "tortuga" && !CheckAttribute(pchar, "questTemp.Tonzag.TerrapinBlock"))
			{
				link.l1 = "I'm looking for Henri Thibaut. Where can I find him?";
				link.l1.go = "terrapin";
			}
			if (CheckAttribute(PChar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "tortuga1" && !CheckAttribute(pchar, "questTemp.Tonzag.TerrapinBlock"))
			{
				link.l1 = "I'm looking for Henri Thibaut. Where can I find him?";
				link.l1.go = "terrapin_2";
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "tortuga")
			{
				link.l1 = "Tell me, has a galleon by the name of 'Santa Margarita' stopped at your colony recently? Perhaps as a privateer prize?";
                link.l1.go = "guardoftruth";
			}
			// Addon 2016-1 Jason Пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Jeweller"))
			{
				link.l1 = "Look, pal, I'm looking for Gaspard Parmentier. Where can I find him?";
                link.l1.go = "mtraxx_jew";
			}
			// Rebbebion, "Путеводная звезда"
			if (CheckAttribute(pchar, "questTemp.PZ.TortugaCitizensAsk") && !CheckAttribute(npchar, "quest.PZ.Ask.Block"))
			{
				link.l1 = "Can you help me out a bit, mate? I'm looking for a man named Joep van der Vink. Do you know him?";
				link.l1.go = "PZ_1";
			}
        break;
        
		case "Tortuga_ratT_1":
			dialog.text = "Francois Gontier? Who is he? I don't know any man by that name.";
			link.l1 = "He's the captain of the corvette '"+pchar.questTemp.Slavetrader.ShipName+"'.";
			link.l1.go = "Tortuga_ratT_2";
        break;
		
		case "Tortuga_ratT_2":
			dialog.text = "I don't have the slightest clue. And no corvette by that name has docked at our port, I can say that for sure.";
			link.l1 = "Fine then, have you seen any outsiders in town lately?";
			link.l1.go = "Tortuga_ratT_3";
        break;
		
		case "Tortuga_ratT_3":
			dialog.text = "Good question! This is a port town, not a village. Strangers come through every day. Though I have heard about five odd lads, they always stay close together and keep their blades ready.\nThe patrol even asked around about them with no result. But I am sure that they didn't arrive here on a corvette, no such vessel was seen around, savvy?";
			link.l1 = "Hm... All right then, I see. Thank you, "+npchar.name+".";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "21_8");
			pchar.questTemp.Slavetrader = "wait1";//затычка
        break;
		
		// суп из черепахи
		case "terrapin":
			DelMapQuestMarkCity("SentJons");
			dialog.text = "Monsieur Thibaut is a famous man on Tortuga. His mansion is located near the port authority. When leaving the tavern, head straight toward the port. Approach the arch leading to the port, turn left at the crossroads and go all the way down to the end of the street where you'll run into a two-story stone building with a red roof. That is Monsieur Thibaut's mansion.";
			link.l1 = "Thank you! I'll go visit him...";
			link.l1.go = "terrapin_1";
		break;
		
		case "terrapin_1":
			DialogExit();
			pchar.questTemp.Terrapin = "house";
			sld = characterFromId("Tibo");
			ChangeCharacterAddressGroup(sld, "Tortuga_houseS2", "barmen", "stay");
			LAi_SetOwnerType(sld);
		break;
		
		case "terrapin_2":
			dialog.text = "Monsieur Thibaut is in high demand today, a messenger from the governor just rushed over here. He was interested too. Is it that hard to find him? He's been renting a room from me on the second floor for quite some time, even though he has a whole mansion to live in. I don't know what he needs it for, but he comes in much more often than he leaves. And he's only there in the evenings.";
			link.l1 = "Maybe he's here right now.";
			link.l1.go = "terrapin_3";
		break;
		
		case "terrapin_3":
			if (stf(environment.time) < 20.0 && stf(environment.time) > 8.0)
			{
				dialog.text = "No. He said he wouldn't be back until eight this evening. You can try looking for him at his mansion, but I don't think you'll find him there. I saw him sailing on a patrol lugger at sea.";
				link.l1 = "Thank you! I'll stop by to see him later.";
				link.l1.go = "terrapin_4";
			}
			else
			{
				dialog.text = "Yes. If you want, you can come up.";
				link.l1 = "Thank you! I'll go visit him...";
				link.l1.go = "terrapin_4";
			}
		break;
		
		case "terrapin_4":
			DialogExit();
			pchar.questTemp.Terrapin = "tavern";
			sld = characterFromId("Tibo");
			sld.dialog.currentnode = "tibo_9";
			LAi_SetLoginTime(sld, 20.0, 8.0);
			ChangeCharacterAddressGroup(sld, "Tortuga_tavern_upstairs", "goto", "goto1");
			LocatorReloadEnterDisable("Tortuga_tavern", "reload2_back", false); // откроем комнату
			LAi_LocationFightDisable(&Locations[FindLocation("Tortuga_tavern_upstairs")], true);//запретить драться
			LAi_SetStayType(sld);
			// Addon 2016-1 Jason Пиратская линейка
			if (GetCharacterIndex("Mary") != -1)
			{
				sld = characterFromId("Mary");
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && !IsOfficer(sld))
				{
					ChangeCharacterAddressGroup(sld, "none", "", "");
				}
			}
			if (GetCharacterIndex("Helena") != -1)
			{
				sld = characterFromId("Helena");
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && !IsOfficer(sld))
				{
					ChangeCharacterAddressGroup(sld, "none", "", "");
				}
			}
		break;
		
		case "guardoftruth":
			dialog.text = "No clue about the ship's name, was it 'Santa Margarita' or 'Castilian Whore', but they brought in a captured Spanish galleon. Captured by a sloop, no less! Now that's some proper fucking sailing right there! Gaius Marchais, its captain, has been bragging for two days in the tavern - his first voyage and such a prize!\nAye, a very heroic deed, to board a galleon filled with church rats without soldiers to guard them. It seems those papist bastards forgot what they say about those who help themselves...";
			link.l1 = "Yes, God helps those who help themselves, that's a Huguenot saying for sure. How do I catch a glimpse of that lucky captain? Is he here, on Tortuga?";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "Ah, who the hell knows. I haven't seen him in my tavern for a long time. As soon as he sobered up he bought a shiny new ship with the prize money and ran around its deck like a madman. I have no idea where Marchais is now. Maybe he's on Tortuga or maybe at sea.";
			link.l1 = "Alright. Well, thanks for the story, mate!";
			link.l1.go = "guardoftruth_2";			
		break;
		
		case "guardoftruth_2":
			dialog.text = "Any time, Monsieur. I'm always happy to help our beloved Captain "+pchar.name+", saviour of St. Pierre! Stop by later!";
			link.l1 = "...";
			link.l1.go = "exit";	
			AddQuestRecord("Guardoftruth", "8");
			pchar.questTemp.Guardoftruth = "tortuga1";
		break;
		
		// Addon 2016-1 Jason Пиратская линейка
		case "mtraxx_jew":
            dialog.text = "Seems like Gaspard is becoming more and more popular among your kind. His house is by the wall. Turn left from the tavern and head towards the port, but don't go there, turn left again, go straight and then turn right. It's a two-storey house.";
			link.l1 = "Thanks!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_WolfreekJewellerHouse");
		break;
		
		case "PZ_1":
			dialog.text = "Never heard of him.";
			link.l1 = "Perhaps he goes by another name. Maybe you've heard of him as the captain of the brig 'Banten'?";
			link.l1.go = "PZ_2";
		break;
		
		case "PZ_2":
			dialog.text = "Never heard of that brig either.";
			link.l1 = "I've heard he was here recently. Perhaps a little silver will refresh your memory?";
			link.l1.go = "PZ_3";
		break;
		
		case "PZ_3":
			npchar.quest.PZ.Ask.Block = true;
			
			dialog.text = "Well, ask yourself where you heard that. I don't mind taking your silver, though.";
			link.l1 = "No silver this time, then. Farewell.";
			link.l1.go = "Exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
