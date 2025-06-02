void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
        case "First time":
			dialog.text = "What do you need?";
			link.l1 = "Nothing.";
			link.l1.go = "exit";
		break;
		
		// Родриго Хименес
		case "Himenes_exit":
			dialog.text = "Anything else, Captain?";
			link.l1 = "Nothing for now...";
			link.l1.go = "Himenes_exit_1";
		break;
		
		case "Himenes_exit_1":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_exit";
		break;
		
		case "Himenes":
			dialog.text = "Ha-ha-ha! Senor Hesucristo! Glory to Santiago the Protector! Glory to the Virgin Mary! We are saved! Ha-ha-ha!";
			link.l1 = "Spaniards! To arms!";
			link.l1.go = "Himenes_1_1";
			link.l2 = "Hello. I understand you're having problems? Who are you?";
			link.l2.go = "Himenes_2";
		break;
		
		case "Himenes_1_1":
			AddComplexSelfExpToScill(100, 100, 100, 100);
			dialog.text = "Ha-ha-ha-ha-ha-ha-ha-ha!";
			link.l1 = "Fine-alright, calm down. It's just a habit.";
			link.l1.go = "Himenes_2";
		break;
		
		case "Himenes_2":
			dialog.text = "Ha-ha! Senor, my name is Rodrigo Jimenez. I am a surveyor and, by fate's will, el jefe of these unfortunate people.";
			link.l1.go = "Himenes_3";
		break;
		
		case "Himenes_3":
			dialog.text = "We... were landed here. But, senor, we are not criminals! Ha-ha-ha-ha!";
			link.l1 = "What's funny?";
			link.l1.go = "Himenes_4";
		break;
		
		case "Himenes_4":
			dialog.text = "Ah... I apologize, senor! It's all my affliction, since childhood I laugh when I'm very nervous. Ha.";
			link.l1 = "And you were chosen as the leader?.. Fine. People don't just land on uninhabited islands for no reason, senor. Care to explain? I'm giving you only one chance.";
			link.l1.go = "Himenes_5";
		break;
		
		case "Himenes_5":
			string nationManName[4];
			nationManName[0] = "English";
			nationManName[1] = "French";
			nationManName[2] = "If you are seeing this, it's a bug";
			nationManName[3] = "Spaniard";
			dialog.text = "Sorry, I'm afraid I didn't catch your name, sir. Are you English?";
			link.l1 = nationManName[sti(pchar.BaseNation)] + ". Is that so important? Let's not worry about my name for now.";
			link.l1.go = "Himenes_6";
		break;
		
		case "Himenes_6":
			dialog.text = "Indeed, being recognized as heretics by the Catholic Spanish Church, we must appear before the righteous court of the Holy Inquisition. That's why your nationality is so important to us. A Spanish captain would be obliged to surrender us to the local authorities. We wouldn't survive such a thing again! Ha-ha!";
			if (sti(pchar.BaseNation) == SPAIN) dialog.text = "Ha-ha-ha-ha-ha-ha! Such is our luck, well, there is nothing for us to lose anyways. " + dialog.text;
			link.l1 = "Well, fortunately for you, the affairs of the Inquisition don't concern me. So what? Are you pagans?";
			link.l1.go = "Himenes_7";
		break;
		
		case "Himenes_7":
			dialog.text = "No, I swear to you! Our community was engaged in crafts and trade in the glorious city of Cadiz for fifty years. Everything was going well, we even acquired a ship and a license for trading with the colonies of our Empire. Now I understand that back then we crossed some line and were completely unprepared for our new competitors... and their methods.";
			link.l1 = "You didn't share commerce with someone in Europe and, as a result, the entire community got stuck on a deserted island in the Caribbean? And here I thought I had life problems...";
			link.l1.go = "Himenes_8";
		break;
		
		case "Himenes_8":
			dialog.text = "Unfortunately, that's the case. Our community was founded by Jews who converted to the new faith and were granted the opportunity to return home to Spain. This ancient history was enough for accusations and official scrutiny.";
			link.l1 = "And so you ran...";
			link.l1.go = "Himenes_9";
		break;
		
		case "Himenes_9":
			dialog.text = "Yes! Ha-ha-ha! On our own ship! We were heading to Curacao to build a new home and a new business. However, we underestimated the persistence of the Inquisition and paid dearly for it. Their courier intercepted us not far from here and ordered the captain to return us home...";
			link.l1 = "Damn!";
			link.l1.go = "Himenes_10";
		break;
		
		case "Himenes_10":
			dialog.text = "There's more! Ha! Our captain didn't want to bother taking us back across the Atlantic or releasing us under his responsibility at the nearest port. And, making a truly Solomon-like decision, he gave us food, landed us here, and that was that.";
			link.l1 = "A tragic story indeed, no doubt about it. Let's summarize: you can't go home, friendly colonies will report you, and foreign ports won't welcome you either - there's no end to the war in this region. What are your plans?";
			link.l1.go = "Himenes_11";
		break;
		
		case "Himenes_11":
			dialog.text = "You've painted such a bleak picture, sir, that I'm at a loss for words. It's as if there's no better place for us than this island.";
			link.l1 = "I don't think so, there is a better island.";
			link.l1.go = "Himenes_12";
		break;
		
		case "Himenes_12":
			dialog.text = "Really? Is it Spanish?";
			link.l1 = "It's mine. By fate, I inherited a former pirate hideout on an uninhabited island. Now it's my base, and I want to expand it, explore the island, and if possible, build a factory there..";
			link.l1.go = "Himenes_13";
		break;
		
		case "Himenes_13":
			dialog.text = "Are you a pirate?";
			link.l1 = "Yes.";
			link.l1.go = "Himenes_14_1";
			link.l2 = "No.";
			link.l2.go = "Himenes_14_2";
		break;
		
		case "Himenes_14_1":
			dialog.text = "New World! Indeed, we are here. Back home, they say pirates are real demons and not even human. Eating children, raping women, and peeling the skin off good Catholics. Is that true?";
			link.l1 = "It depends on the day of the week. Let's discuss this another time. I'm looking for people. Hardworking and capable individuals willing to live far from civilization for several years. Would you be interested in something like that?";
			link.l1.go = "Himenes_15";
		break;
		
		case "Himenes_14_2":
			dialog.text = "Too bad, since I'm already a criminal, I'd like to see at least one pirate.";
			link.l1 = "Perhaps you'll have such an opportunity again. Let's discuss it another time. I'm looking for hardworking and capable individuals willing to live far from civilization for several years. Would you be interested in something like that?";
			link.l1.go = "Himenes_15";
		break;
		
		case "Himenes_15":
			dialog.text = "We have no other way out. But that's actually not a bad option. We'll accept it if you allow us to live and work in peace. And promise to send us home one day! Give us your word, sir, and tell us your name..";
			link.l1 = "I, Captain "+GetFullName(pchar)+", give you my word. ?";
			link.l1.go = "Himenes_16";
		break;
		
		case "Himenes_16":
			dialog.text = "Ha-ha! We are saved! So be it! We are several families, about 30 people. All are literate, trained in crafts and commerce.";
			link.l1 = "Fate has decided... Please come aboard!";
			link.l1.go = "Himenes_17";
		break;
		
		case "Himenes_17":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "goto", "goto1", "none", "", "", "", 10.0);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			IslaMona_TerksHimenesOnBoard();
		break;
		
		case "Himenes_18":
			dialog.text = "Nice to meet you, Senor Rodgar. It seems we'll have to live and work together for a long time... Goodness, how do you stand this heat?";
			link.l1 = "";
			link.l1.go = "Himenes_19";
		break;
		
		case "Himenes_19":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_14";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Himenes_20":
			dialog.text = "If you don't mind, I'll step in: Captain, give us a day to settle in and quickly inspect the inventory and land. I'm sure Senor Rodgar has plenty of ideas about what to do with this patch of land. I think we'll make a good team.";
			link.l1 = "You don't really have a choice, Hymenese. Ha-ha.!";
			link.l1.go = "Himenes_21";
		break;
		
		case "Himenes_21":
			dialog.text = "Ha-ha-ha-ha-ha-ha!";
			link.l1 = "";
			link.l1.go = "Himenes_22";
		break;
		
		case "Himenes_22":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_16";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Himenes_23":
			dialog.text = "Yes, Captain?";
			link.l1 = "Hymenese, any good news for me?";
			link.l1.go = "Himenes_24";
		break;
		
		case "Himenes_24":
			dialog.text = "Captain, this is a nightmare. Your house is not bad, of course. But otherwise... It's impossible to live in these huts, surrounded by overgrowth, and Senor Rodgar doesn't even know what's happening at the other end of the island!! Unbelievable! Ha-ha!";
			link.l1 = "Are you nervous or are you actually laughing about this right now?";
			link.l1.go = "Himenes_25";
		break;
		
		case "Himenes_25":
			dialog.text = "Of course, it's funny! What were they doing all these years? First of all, we need to finish building a couple of houses and fix these huts to an acceptable condition. People need to live decently to work diligently. Also, I'll ask the pirates to conduct a full reconnaissance of the island. Perhaps this place is rich not only in rocks and sand. When everything is done, I'll be able to tell you exactly what to do with this land.";
			link.l1 = "Sounds great! What is required of me?";
			link.l1.go = "Himenes_26";
		break;
		
		case "Himenes_26":
			AddQuestRecordInfo("IslaMonaData", "1");
			dialog.text = "Materials for houses, furniture, and temporary shelters. I've calculated everything. Here, take the list.";
			link.l1 = "Impressive...";
			link.l1.go = "Himenes_27";
		break;
		
		case "Himenes_27":
			dialog.text = "Really? Sir, we've built cathedrals! Now that's impressive....";
			link.l1 = "I'm inclined to believe you! Just don't accidentally build a cathedral here. Will I have to haul much material here every time?";
			link.l1.go = "Himenes_28";
		break;
		
		case "Himenes_28":
			dialog.text = "No, these materials will sustain us for a while, but we'll still need to bring in some things later on. If you want to try to avoid such troubles in the future, bring twice as many materials.";
			link.l1 = "Well, you convinced me. I'll see what I can do. Any deadlines?";
			link.l1.go = "Himenes_29";
		break;
		
		case "Himenes_29":
			dialog.text = "No, sir. But I kindly ask you not to delay - this is the work that needs to be done to move things forward. And people need somewhere to live too. Load the materials into the warehouse and don't forget to inform me when everything is ready. Oh, I almost forgot! Talk to Mr. Rodgar about exploring the island.";
			link.l1 = "Agreed!";
			link.l1.go = "Himenes_30";
		break;
		
		case "Himenes_30":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_exit";
			pchar.questTemp.IslaMona = "stalk";
			AddQuestRecord("IslaMona", "6");
		break;
		
		case "Himenes_31":
			dialog.text = "Aye, Captain?";
			if (IslaMona_CheckBuild()) // привез товары на стройку
			{
				link.l1 = "Hello, Hymenez. Check the warehouse.";
				link.l1.go = "Himenes_32_1";
			}
			else // не привез товары на стройку
			{
				link.l1 = "Hello, Hymenez. My men have scoured the entire island. What do you say?";
				if (CheckAttribute(pchar, "questTemp.IslaMona.Food")) link.l1.go = "Himenes_32_2"; // привез еду и лекарства
				else link.l1.go = "Himenes_32_3";
			}
		break;
		
		case "Himenes_32_1":
			IslaMona_RemoveBuild(); // сразу удаляем товары со склада
			dialog.text = "You've handled this responsibility with flying colors! If you're ever in Cadiz, come work for me as a storekeeper!";
			link.l1 = "I'm on my way! Tell me, compadre, what are you going to do now?";
			if (CheckAttribute(pchar, "questTemp.IslaMona.Food")) link.l1.go = "Himenes_34_1"; // привез еду и лекарства
			else link.l1.go = "Himenes_34_2";
		break;
		
		case "Himenes_32_2":
			dialog.text = "Senor Captain, let us first deal with housing and supplies. We will make plans afterward. I await the goods from your list at the warehouse.";
			link.l1 = "Alright, I understand. First, we need to build houses and tidy up this place. The goods will be here soon.";
			link.l1.go = "Himenes_33";
		break;
		
		case "Himenes_32_3":
			dialog.text = "Captain, let us first deal with housing and supplies. We can make plans later. I am waiting for the goods from your list at the warehouse. And your pirate friend also awaits provisions and medicine.";
			link.l1 = "Alright, I understand. First, we need to build houses and tidy up this place. The goods will be here soon. And for my pirate friend too.";
			link.l1.go = "Himenes_33";
		break;
		
		case "Himenes_33":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_31";
		break;
		
		case "Himenes_34_1":
			dialog.text = "Give us six months, Captain, and you won't recognize this place.";
			link.l1 = "Are you saying that in six months there will be neither you, nor the settlement, nor the materials here? See you later!";
			link.l1.go = "Himenes_37"; // все выполнил
		break;
		
		case "Himenes_34_2":
			dialog.text = "We will start working as soon as you settle your business with this bandit. He requested provisions and medicine from you, and I agree with him - it's a reasonable demand.";
			link.l1 = "I will convey your words to him.";
			link.l1.go = "Himenes_35";
			AddQuestRecord("IslaMona", "11");
		break;
		
		case "Himenes_35":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_36";
		break;
		
		case "Himenes_36":
			dialog.text = "Well, Captain? Did you do everything your pirate asked?";
			if (CheckAttribute(pchar, "questTemp.IslaMona.Food"))
			{
				link.l1 = "I have resolved all issues with Rodgar. Island reconnaissance has begun, provisions and medicine are in the warehouse. Now it's your turn.";
				link.l1.go = "Himenes_34_1";
			}
			else
			{
				link.l1 = "Don't worry, we'll figure it out. I'm dealing with this.";
				link.l1.go = "Himenes_35";
			}
		break;
		
		case "Himenes_37":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_exit";
			DeleteAttribute(pchar, "questTemp.IslaMona.Food");
			pchar.questTemp.IslaMona = "build";
			AddQuestRecord("IslaMona", "12");
			SetFunctionTimerCondition("IslaMona_BuildDone", 0, 0, 180, false);
		break;
		
		case "Himenes_38":
			dialog.text = "Senor Captain! What do you think? Ha-ha-ha?";
			link.l1 = "It's much nicer. Report, Himenes!";
			link.l1.go = "Himenes_39";
		break;
		
		case "Himenes_39":
			dialog.text = "Now you can actually live here! We cleaned up and rebuilt all the houses, except yours, of course. Not very luxurious, but not worse than in our Belize.";
			link.l1 = "Belize has long belonged to England, Himenes.";
			link.l1.go = "Himenes_40";
		break;
		
		case "Himenes_40":
			dialog.text = "I'm not sure if the houses know about it, Captain, ha-ha!";
			link.l1 = "Now you have a place to live, and the settlement looks human. What's next?";
			link.l1.go = "Himenes_41";
		break;
		
		case "Himenes_41":
			dialog.text = "Look around, talk to Senior Janssen, and come back to me. We'll discuss the results of the island reconnaissance and our plans.";
			link.l1 = "Since when did you start calling Rodgar that? Weren't you constantly in disagreement?";
			link.l1.go = "Himenes_42";
		break;
		
		case "Himenes_42":
			dialog.text = "And we still have them. But we have to build working relationships somehow.";
			link.l1 = "Thank you, Rodrigo. I'll be back soon.";
			link.l1.go = "Himenes_43";
		break;
		
		case "Himenes_43":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload6", "none", "", "", "", 10.0); // возможно будет иной локатор в новой локации
			pchar.questTemp.IslaMona = "village";
		break;
		
		case "Himenes_44":
			dialog.text = "Captain. Senor Janssen.";
			link.l1 = "Come on, tell me about the results of the island reconnaissance.";
			link.l1.go = "Himenes_45";
		break;
		
		case "Himenes_45":
			dialog.text = "Yes, Captain. Some places I inspected personally with our prospector. Well, what can I say... Isla Mona is a poor, tiny, and quite uninteresting island. There is very little space for construction, the landscape is difficult, steep, and there is almost no fertile land. Three beaches, one flooded cave, dense thickets, a couple of parrots, a herd of goats, and us...";
			link.l1 = "Are you serious? Are you saying that the most valuable asset on this island is a herd of goats?";
			link.l1.go = "Himenes_46";
		break;
		
		case "Himenes_46":
			dialog.text = "Ha-ha-ha-ha! I would ask, Senor! Ha-ha! You didn't let me finish!";
			link.l1 = "";
			link.l1.go = "Himenes_47";
		break;
		
		case "Himenes_47":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_38";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_48":
			dialog.text = "";
			link.l1 = "Fine, alright, calm down and continue. You know, I've invested a lot in this place.";
			link.l1.go = "Himenes_49";
		break;
		
		case "Himenes_49":
			dialog.text = "And not in vain! There is enough fresh water in the cave, there is enough soil to grow fruit-bearing trees, and goats can be bred. With fishing and efforts from your comrades, the food issue will be resolved very quickly.";
			link.l1 = "So, you won't need to bring more food here? Not bad. I hoped that this place could live without my constant care. Let's continue.";
			link.l1.go = "Himenes_50";
		break;
		
		case "Himenes_50":
			dialog.text = "You are right about everything, Senor. But that's not all the news! Firstly, Senor Rodgar has come up with the idea of ​​building a tavern. I don't know what it will give you, but this rogue is up to something.";
			link.l1 = "He wants to get drunk, that's what!";
			link.l1.go = "Himenes_51";
		break;
		
		case "Himenes_51":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_40";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_52":
			dialog.text = "Secondly, Governor's Bay turned out to be much deeper than we originally thought. We can build a full-fledged pier.";
			link.l1 = "I don't quite understand how it will benefit me, but that's already good news. That isn't all, I hope?";
			link.l1.go = "Himenes_53";
		break;
		
		case "Himenes_53":
			dialog.text = "We found a grove of bacote trees. An ideal place for a factory.";
			link.l1 = "You're making me happy, Rodrigo! Indeed, excellent news!";
			link.l1.go = "Himenes_54";
		break;
		
		case "Himenes_54":
			dialog.text = "That's all for now, senor. We might have more ideas in the future. You understand, the best ideas come while working! What would you like to ask about?";
			link.l1 = "Tell me about bacote. It sounds promising.";
			link.l1.go = "Himenes_55";
		break;
		
		case "Himenes_55":
			dialog.text = "In my estimation, a small factory will be able to extract this valuable wood for several years. The reserves are modest, but the resource is strategic. We can clear a site in the center of the island and build a house with a warehouse there. That's a start. Besides construction materials, we will also need about 15 sets of handcuffs and muskets.";
			link.l1 = "And why do we need handcuffs? And why exactly fifteen?";
			link.l1.go = "Himenes_56";
		break;
		
		case "Himenes_56":
			dialog.text = "It's hard labor, senor. I would even say, it's slave labor.";
			link.l1 = "I understand. He-he...";
			link.l1.go = "Himenes_57_1";
			link.l2 = "Have you gone mad? I won't become a slave owner!";
			link.l2.go = "Himenes_57_2";
		break;
		
		case "Himenes_57_1":
			dialog.text = "";
			link.l1 = "And why do we need a musket? And why only one?";
			link.l1.go = "Himenes_59";
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
		break;
		
		case "Himenes_57_2":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_42";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
		break;
		
		case "Himenes_58":
			dialog.text = "I agree with the pirate, senor. I don't understand you, captain. The whole economy of this region is based on slave labor, and it will remain so for many years to come. How are we any better?";
			link.l1 = "I will make a decision. Meanwhile, tell me why you need a musket? And why exactly one?";
			link.l1.go = "Himenes_59";
		break;
		
		case "Himenes_59":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_44";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_60":
			dialog.text = "Of course, the factory will require maintenance. With its construction, this island will have an economy with you as its main trading partner. We will feed the slaves ourselves, but you will have to pay for security and production out of your own pocket. Settlers will take a hundred doubloons and five bottles of wine for each batch. For security matters, negotiate with Senor Janssen.";
			link.l1 = "";
			link.l1.go = "Himenes_61";
		break;
		
		case "Himenes_61":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_46";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_62":
			dialog.text = "forty measures each month. And the gold is for the future. One day you will take us from here, remember your promise? Any work must be paid for, and with your doubloons, we will pay hunters and craftsmen for their work in the settlement. Thus, we will have trade, and with it - civilization!";
			link.l1 = "That's the spirit! Alright! For now, everything sounds convincing enough...";
			link.l1.go = "Himenes_63";
		break;
		
		case "Himenes_63":
			dialog.text = "What else interests you?";
			link.l1 = "So, what's the story with the tavern? Why not build a theater?";
			link.l1.go = "Himenes_64";
		break;
		
		case "Himenes_64":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_48";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_65":
			dialog.text = "Captain, I warned him that you wouldn't like the idea of the house. But it's the only option. You have the biggest house in... ahem, the town, we'll rebuild the first floor into a hall, set up tables and a kitchen. We'll store drinks and food in the caves under the house. We have people to cook and play music. The second floor will remain yours, and we won't touch it. We'll move all your things from the first floor upstairs ourselves.";
			link.l1 = "Alright. So what exactly will the tavern give us?";
			link.l1.go = "Himenes_66";
		break;
		
		case "Himenes_66":
			dialog.text = "We'll get some cultural life, and you'll have the opportunity to have about three hundred people in reserve right in the heart of the Caribbean.";
			link.l1 = "Interesting... I'll think about it.";
			link.l1.go = "Himenes_67";
		break;
		
		case "Himenes_67":
			dialog.text = "What else interests you?";
			link.l1 = "Well, what about the pier?";
			link.l1.go = "Himenes_68";
		break;
		
		case "Himenes_68":
			dialog.text = "It's simple. We'll clear Governor's Bay of reefs, install signaling lighting, and build a pier. Senor Janssen claims that you'll be able to shelter three ships in the bay, or one first-class ship. And it will be more pleasant for you to return here, not dragging the dinghy along the beach every time.";
			link.l1 = "That would be nice.";
			link.l1.go = "Himenes_69";
		break;
		
		case "Himenes_69":
			dialog.text = "What would you like to know?";
			link.l1 = "That's all for now. I'll be back when I decide what to build.";
			link.l1.go = "Himenes_70";
		break;
		
		case "Himenes_70":
			dialog.text = "Senor Captain, take this document. I took the liberty of writing down all the details so as not to repeat them a dozen times. Study it, bring materials, and set the task.";
			link.l1 = "Thank you, Rodrigo.";
			link.l1.go = "Himenes_71";
		break;
		
		case "Himenes_71":
			DialogExit();
			IslaMona_HouseDialogFin();
		break;
		
		case "Himenes_72": // нода Хименеса строителя и управляющего факторией
			if (CheckAttribute(pchar, "questTemp.IslaMona.RecordPart")) // после защиты Исла Моны - нужно еще 10 рабов
			{
				dialog.text = "Senor Captain, we need 10 slaves to work in the factory - I told you, haven't you forgotten?";
				if (GetSquadronGoods(pchar, GOOD_SLAVES) >= 10)
				{
					link.l1 = "Already delivered. Unload them and start production.";
					link.l1.go = "Himenes_plantation_12";
				}
				else
				{
					link.l1 = "My memory is intact. I'll bring them soon.";
					link.l1.go = "Himenes_plantation_14";
				}
				break;
			}
			dialog.text = "So, Senor Captain, what do you say?";
			if (!CheckAttribute(pchar, "questTemp.IslaMona.Harbour"))
			{
				link.l1 = "I want a clean bay and a safe pier. It will be the base for my fleet.";
				link.l1.go = "Himenes_harbour";
			}
			if (!CheckAttribute(pchar, "questTemp.IslaMona.Tavern"))
			{
				link.l2 = "Go ahead and build the tavern. Everyone will appreciate it, and I'll be able to keep a reserve here.";
				link.l2.go = "Himenes_tavern";
			}
			if (!CheckAttribute(pchar, "questTemp.IslaMona.Plantation"))
			{
				link.l3 = "Start building the plantation. It's time to recoup the investments.";
				link.l3.go = "Himenes_plantation";
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona.Plantation.Slave") && IslaMona_CheckSlave())
			{
				link.l4 = "Rodrigo, the especially valuable specialists and equipment have been delivered to the factory. You can start working.";
				link.l4.go = "Himenes_plantation_7";
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona.Factory.Part") && sti(pchar.questTemp.IslaMona.Factory.Part) > 0)
			{
				link.l4 = "Rodrigo, I've come for my ironwood.";
				link.l4.go = "Himenes_bacaut";
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona.Harbour") && pchar.questTemp.IslaMona.Harbour == "done" && CheckAttribute(pchar, "questTemp.IslaMona.Tavern") && pchar.questTemp.IslaMona.Tavern == "done" && CheckAttribute(pchar, "questTemp.IslaMona.Factory") && !CheckAttribute(pchar, "questTemp.IslaMona.Church"))
			{
				link.l5 = "Rodrigo, have we finished our great construction?";
				link.l5.go = "Himenes_church";
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona.Church") && pchar.questTemp.IslaMona.Church == "start" && IslaMona_CheckChurch())
			{
				link.l5 = "Rodrigo, let's build your church.";
				link.l5.go = "Himenes_church_10";
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona.Church") && pchar.questTemp.IslaMona.Church == "Wait_candles" && IslaMona_CheckCandles())
			{
				link.l5 = "Rodrigo, I brought your church items.";
				link.l5.go = "Himenes_church_10_3";
			}
			link.l10 = "Nothing for now...";
			link.l10.go = "Himenes_73";
		break;
		
		case "Himenes_harbour":
			if (IslaMona_CheckHarbour())
			{
				dialog.text = "Materials are available, everything is ready. Construction will take 4 months.";
				link.l1 = "You're not in a hurry, are you! Well, good luck, Rodrigo.";
				link.l1.go = "Himenes_harbour_1";
			}
			else
			{
				dialog.text = "I'm afraid there are not enough materials in the warehouse. Please, check the list again.";
				link.l1 = "I'll take care of it.";
				link.l1.go = "Himenes_73";
			}
		break;
		
		case "Himenes_tavern":
			if (IslaMona_CheckTavern())
			{
				dialog.text = "Materials are available, everything is ready. Construction will take 3 months.";
				link.l1 = "You're not in a hurry, are you! Well, good luck, Rodrigo.";
				link.l1.go = "Himenes_tavern_1";
			}
			else
			{
				dialog.text = "I'm afraid there are not enough materials in the warehouse. Please, check the list again.";
				link.l1 = "I'll take care of it.";
				link.l1.go = "Himenes_73";
			}
		break;
		
		case "Himenes_plantation":
			if (IslaMona_CheckPlantation())
			{
				dialog.text = "Materials are available, everything is ready. Construction will take 6 months.";
				link.l1 = "You're not in a hurry, are you! Good luck, Rodrigo.";
				link.l1.go = "Himenes_plantation_1";
			}
			else
			{
				dialog.text = "I'm afraid there are not enough materials in the warehouse. Please, check the list again.";
				link.l1 = "I'll take care of it.";
				link.l1.go = "Himenes_73";
			}
		break;
		
		case "Himenes_73":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
		break;
		
		case "Himenes_harbour_1":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
			IslaMona_RemoveHarbour();
			pchar.questTemp.IslaMona.Harbour = "true";
			SetFunctionTimerCondition("IslaMona_BuildHarbour", 0, 0, 120, false);
		break;
		
		case "Himenes_harbour_2":
			dialog.text = "Welcome, Captain. How do you like your new port?";
			if (stf(environment.time) > 22.0 || stf(environment.time) < 5.0)
			{
				link.l1 = "It's dark, Rodrigo! We nearly crashed your praised pier! Well done for lighting it up at least!";
				link.l1.go = "Himenes_harbour_3";
			}
			else
			{
				link.l1 = "Not bad, Rodrigo! Seems like a small thing, but it's nice to walk along these planks to the shore. And the bay became easier to navigate. So, I guess now I can accommodate more ships in this little bay?";
				link.l1.go = "Himenes_harbour_4";
			}
		break;
		
		case "Himenes_harbour_3":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_51";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_harbour_4":
			sld = characterFromId("Islamona_carpenter");
			sld.portman.info = "true"; // если вдруг до сих пор не говорил об условиях стоянки
			pchar.questTemp.IslaMona.Harbour = "done"; // флаг - пристань построена и сдана
			dialog.text = "Yes, Captain. I must say, there's a certain pride about it. Feel free to let me know how you'd like to continue our big construction project.";
			if (CheckAttribute(pchar, "questTemp.IslaMona.Plantation") && pchar.questTemp.IslaMona.Plantation == "complete") // если пересеклось со сдачей фактории
			{
				link.l1 = "Speaking of construction. My factory should also be completed by now. Right, Rodrigo?";
				link.l1.go = "Himenes_plantation_2";
			}
			else
			{
				link.l1 = "...";
				link.l1.go = "Himenes_harbour_5";
			}
		break;
		
		case "Himenes_harbour_5":
			DialogExit();
			IslaMona_HarbourClear();
		break;
		
		case "Himenes_tavern_1":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
			IslaMona_RemoveTavern();
			pchar.questTemp.IslaMona.Tavern = "true";
			SetFunctionTimerCondition("IslaMona_BuildTavern", 0, 0, 90, false);
		break;
		
		case "Himenes_tavern_2":
			dialog.text = "H-hic! Cap! We're celebrating here!";
			link.l1 = "Rodgar. Rodrigo. Oh, damn!";
			link.l1.go = "Himenes_tavern_3";
		break;
		
		case "Himenes_tavern_3":
			dialog.text = "What's the matter, c-c-captain? Do you not like the color of the walls?";
			link.l1 = "Just now did I realize that you two share the same name! Ha-ha-ha! A Spaniard and a pirate, with the same name, built a tavern on a deserted island and drinking together as if the Indian gods will devour everyone and end the world by sunrise! Ha-ha! I'm with you!";
			link.l1.go = "Himenes_tavern_4";
		break;
		
		case "Himenes_tavern_4":
			dialog.text = "Ha-ha-ha! So true! Score!";
			link.l1 = "Score!";
			link.l1.go = "Himenes_tavern_5";
		break;
		
		case "Himenes_tavern_5":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
			IslaMona_ReloadTavern();
		break;
		
		case "Himenes_plantation_1":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
			IslaMona_RemovePlantation();
			pchar.questTemp.IslaMona.Plantation = "true";
			SetFunctionTimerCondition("IslaMona_BuildPlantation", 0, 0, 180, false);
		break;
		
		case "Himenes_plantation_2":
			dialog.text = "Everything is ready. Shall we go? Let me show you your factory.";
			link.l1 = "Lead the way.";
			link.l1.go = "Himenes_plantation_3";
		break;
		
		case "Himenes_plantation_3":
			DialogExit();
			pchar.questTemp.IslaMona.Plantation.Harbour = "true"; // наложилась сдача пристани и фактории
			IslaMona_PlantationGo();
		break;
		
		case "Himenes_plantation_4":
			dialog.text = "Captain, almost everything is ready to start operations. Housing for workers, warehouse for raw materials, processing area - a worthy factory has been built. We've already marked the most promising trees for logging in the jungle. Bring fifteen workers and the agreed inventory - 15 shackles and muskets, and we'll start working.";
			link.l1 = "We? You mean the slaves?";
			link.l1.go = "Himenes_plantation_5";
		break;
		
		case "Himenes_plantation_5":
			dialog.text = "Ha! Slav... Slaves will cut, settlers will process, and pirates will guard. Everyone will have work - you've embarked on a serious enterprise, Captain.";
			link.l1 = "Almost like the promised land, huh. Wait for the goods, it's time for me to go hunting.";
			link.l1.go = "Himenes_plantation_6";
		break;
		
		case "Himenes_plantation_6":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
			pchar.questTemp.IslaMona.Plantation.Slave = "true"; // привезти рабов, кандалы и мушкет для запуска фактории
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2", "IslaMona_factoria_residence", "sit", "sit1", "IslaMona_PlantationHouse", -1);
			sld = characterFromId("Islamona_carpenter");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", 5);
			pchar.questTemp.IslaMona.Plantation = "done"; // флаг - фактория построена и сдана
		break;
		
		case "Himenes_plantation_7":
			dialog.text = "A sad fate... They'll never leave this place.";
			link.l1 = "Rodgar... I mean, Rodrigo! Firstly, they might leave. And secondly, if you met someone else on Terks, your fate wouldn't be any better.";
			link.l1.go = "Himenes_plantation_8";
		break;
		
		case "Himenes_plantation_8":
			dialog.text = "I know that very well, Captain. And I don't forget it. Let me tell you about the operation of this factory. Starting next month, on the fifteenth day, we'll deliver forty logs of processed bacout. Of course, you don't have to come for each delivery every month - all batches will be stored and waiting for you right here, at the factory.";
			link.l1 = "So, I can pick up several batches at once?";
			link.l1.go = "Himenes_plantation_9";
		break;
		
		case "Himenes_plantation_9":
			dialog.text = "Within reason, of course - don't stay away for too long. People won't work for years without pay, not knowing if their only customer is still alive or not. I think we'll deliver six batches before suspending operations.";
			link.l1 = "Do I have to pick up all the goods at once? What about the price, remind me?";
			link.l1.go = "Himenes_plantation_10";
		break;
		
		case "Himenes_plantation_10":
			dialog.text = "Yes, all at once. The price of a standard bacout log is ten doubloons. In addition, for each batch, you'll have to give five bottles of good rum and the same number of wine bottles. Rodgar claims you won't find such prices anywhere else in the world.";
			link.l1 = "Indeed, I agree! Thanks, Rodrigo. Let's get to work!";
			link.l1.go = "Himenes_plantation_11";
		break;
		
		case "Himenes_plantation_11":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
			DeleteAttribute(pchar, "questTemp.IslaMona.Plantation.Slave");
			AddQuestRecordInfo("Unique_Goods", "5");
			IslaMona_RemoveSlave();
		break;
		
		case "Himenes_plantation_12":
			dialog.text = "Excellent! Now we'll start work again!";
			link.l1 = "Good.";
			link.l1.go = "Himenes_plantation_13";
		break;
		
		case "Himenes_plantation_13":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
			IslaMona_FactoryReActivar(); // запустить факторию
		break;
		
		case "Himenes_plantation_14":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
		break;
		
		case "Himenes_bacaut":
			dialog.text = "Of course, captain, take it. We have the following batches ready for the next date: "+sti(pchar.questTemp.IslaMona.Factory.Part)+", that's "+sti(pchar.questTemp.IslaMona.Factory.Goods)+" logs. Therefore, you owe us "+sti(pchar.questTemp.IslaMona.Factory.Dublon)+" doubloons, "+sti(pchar.questTemp.IslaMona.Factory.Bottle)+" bottles of rum, and "+sti(pchar.questTemp.IslaMona.Factory.Bottle)+" bottles of wine, do you have all that?";
			if (PCharDublonsTotal() >= sti(pchar.questTemp.IslaMona.Factory.Dublon) && PCharItemsTotal("potionrum") >= sti(pchar.questTemp.IslaMona.Factory.Bottle) && PCharItemsTotal("potionwine") >= sti(pchar.questTemp.IslaMona.Factory.Bottle))
			{
				link.l1 = "Of course. Here is your payment.";
				link.l1.go = "Himenes_bacaut_1";
			}
			else
			{
				link.l1 = "It seems I don't have everything. I'll bring it right away.";
				link.l1.go = "Himenes_73";
			}
		break;
		
		case "Himenes_bacaut_1":
			if (IslaMona_CheckBacautSpace())
			{
				dialog.text = "Excellent. We'll transport the bacout from the factory to your warehouse, from where you can pick it up whenever you want.";
				link.l1 = "Great. Prepare the next batch.";
				link.l1.go = "Himenes_bacaut_2";
			}
			else
			{
				dialog.text = "Hold on, captain! Your warehouse is full - we won't be able to load all the harvested bacout there. Clear some space in the warehouse - then come back to me.";
				link.l1 = "Fine, I'll take care of it.";
				link.l1.go = "Himenes_73";
			}
		break;
		
		case "Himenes_bacaut_2":
			dialog.text = "Of course, captain!";
			link.l1 = "...";
			link.l1.go = "Himenes_73";
			IslaMona_FactoryTrade();
		break;
		
		case "Himenes_church":
			dialog.text = "Ha! Captain, I'm afraid building anything else would be unnecessary folly and extravagance. Unless...";
			link.l1 = "Unless what?";
			link.l1.go = "Himenes_church_1";
		break;
		
		case "Himenes_church_1":
			dialog.text = "Captain, it's awkward for me to ask about this... You've already invested a huge sum in this place!";
			link.l1 = "A brothel?";
			link.l1.go = "Himenes_church_2_1";
			link.l2 = "A church?";
			link.l2.go = "Himenes_church_2_2";
		break;
		
		case "Himenes_church_2_1":
			ChangeCharacterComplexReputation(pchar, "nobility", -3);
			AddCharacterExpToSkill(pchar, "Leadership", 200);
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			dialog.text = "I swear by Saint Santiago, that wouldn't be bad! But on the first night, our women would burn it down. Along with us. No, captain, I'm talking about a church. Yes, we have decent housing and pay, the sea and entertainment, families and friends. But still, something is missing, you understand?";
			link.l1 = "I can imagine.";
			link.l1.go = "Himenes_church_3";
		break;
		
		case "Himenes_church_2_2":
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
			AddCharacterExpToSkill(pchar, "Defence", 500);
			dialog.text = "You see through me, captain. Yes, we have decent housing and pay, the sea and entertainment, families and friends. But still, something is missing, you understand?";
			link.l1 = "I can imagine.";
			link.l1.go = "Himenes_church_3";
		break;
		
		case "Himenes_church_3":
			dialog.text = "Exactly. We can't build the House of God without your help. Such a place must be special, it must be out of this world. And therefore, it should be expensive. We'll need candles, gold ingots, amber, and, of course, construction materials, and not cheap ones. It won't bring you any profit, so I dare not ask.";
			link.l1 = "So, do you need to bring a priest here?";
			link.l1.go = "Himenes_church_4";
		break;
		
		case "Himenes_church_4":
			dialog.text = "No.";
			link.l1 = "Do you already have a priest among you?";
			link.l1.go = "Himenes_church_5";
		break;
		
		case "Himenes_church_5":
			dialog.text = "No, captain. And I think you already understand everything.";
			link.l1 = "So, did the holy fathers from the Inquisition have a reason to persecute you? Are you heretics?";
			link.l1.go = "Himenes_church_6";
		break;
		
		case "Himenes_church_6":
			dialog.text = "By canonical laws, we are the worst of heretics. We don't believe that communicating with God necessarily requires an intermediary from this world.";
			link.l1 = "From this world?";
			link.l1.go = "Himenes_church_7";
		break;
		
		case "Himenes_church_7":
			dialog.text = "Captain, we are not Satanists, and our community is not a sect. We are Christians, like you, but we look at things with a very broad view. Too broad, according to some very educated and worthy people. If you ever find a place in your heart for openness and understanding, then I will tell you more. But for now, just take this list. Just in case.";
			link.l1 = "You should have told me about this earlier, Rodrigo. I don't want to come back one fine day and see a witch's Sabbath or the birth of a new faith on my land! While you wait - I will make a decision.";
			link.l1.go = "Himenes_church_8_1";
			link.l2 = "Impressive list. I'm beginning to understand why the holy fathers need so much money! I'll think about your offer, Rodrigo, and make a decision.";
			link.l2.go = "Himenes_church_8_2";
		break;
		
		case "Himenes_church_8_1":
			ChangeCharacterComplexReputation(pchar, "nobility", -3);
			dialog.text = "";
			link.l1 = "If it's positive, I'll bring all the goods from your list to the warehouse, and I'll lay out the treasures for you on the table.";
			link.l1.go = "Himenes_church_9";
		break;
		
		case "Himenes_church_8_2":
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
			dialog.text = "";
			link.l1 = "If it's positive, I'll bring all the goods from your list to the warehouse, and I'll lay out the treasures for you on the table.";
			link.l1.go = "Himenes_church_9";
		break;
		
		case "Himenes_church_9":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
			pchar.questTemp.IslaMona.Church = "start";
			AddQuestRecord("IslaMona", "14");
			AddQuestRecordInfo("IslaMonaData", "3");
		break;
		
		case "Himenes_church_10":
			dialog.text = "On behalf of our entire community, I thank you, captain. You won't regret this, I swear!";
			link.l1 = "I'll only regret it if you build something completely shabby.";
			link.l1.go = "Himenes_church_10_1";
		break;
		
		case "Himenes_church_10_1":
			dialog.text = "Captain, all building materials are in stock! We will begin construction once you bring the listed luxury items. They'll be used for jewelry and ritual tools. Again, thank you very much, Captain! Muchas gracias!";
			link.l1 = "You're welcome!";
			link.l1.go = "Himenes_church_10_2";
		break;
		
		case "Himenes_church_10_2":
			DialogExit();
			IslaMona_RemoveChurch();
			npchar.dialog.currentnode = "Himenes_72";
			pchar.questTemp.IslaMona.Church = "Wait_candles";
			pchar.questTemp.IslamonaChurch.GoldNugget = 50;
			pchar.questTemp.IslamonaChurch.Candle = 100;
			pchar.questTemp.IslamonaChurch.Amber = 30;
			pchar.questTemp.IslamonaChurch.BlueAmber = 1;
		break;
		
		case "Himenes_church_10_3":
			IslaMona_RemoveCandles();
			string sAdd = "";
			if(CheckAttribute(pchar, "questTemp.IslamonaChurch.Candle"))
			{
				sAdd += " "+sti(pchar.questTemp.IslamonaChurch.Candle)+ " candles,"
			}
			if(CheckAttribute(pchar, "questTemp.IslamonaChurch.Amber"))
			{
				sAdd += " "+sti(pchar.questTemp.IslamonaChurch.Amber)+ " amber,"
			}
			if(CheckAttribute(pchar, "questTemp.IslamonaChurch.GoldNugget"))
			{
				sAdd += " "+ sti(pchar.questTemp.IslamonaChurch.GoldNugget) + " ingots,"
			}
			if(CheckAttribute(pchar, "questTemp.IslamonaChurch.BlueAmber"))
			{
				sAdd += " and one blue amber"
			}
			if(sAdd == "")
			{
				dialog.text = "Muchisimas gracias, captain! Everything is ready, we are starting construction. Come back in a couple of months for the first service. Oh, and one more thing, the grapes are ripe! We'll make homemade wine, have a celebration, and feast in your honor!";
				link.l1 = "I think we all deserve a celebration. I'll be back in two months.";
				link.l1.go = "Himenes_church_12";
			}
			else
			{
				dialog.text = "Captain, there are still "+sAdd+" left.";
				link.l1 = "Sure, just give some more time please. Honestly, if it weren't for the candles, I'd think you were going to bury a treasure.";
				link.l1.go = "Himenes_church_11";
			}
		break;
		
		case "Himenes_church_11":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
		break;
		
		case "Himenes_church_12":
			DialogExit();
			npchar.dialog.currentnode = "Himenes_72";
			pchar.questTemp.IslaMona.Church = "build";
			AddQuestRecord("IslaMona", "15");
			//IslaMona_RemoveChurch();
			SetFunctionTimerCondition("IslaMona_ChurchComplete", 0, 0, 60, false);
		break;
		
		case "Himenes_church_13":
			dialog.text = "Ha-ha-ha-ha-ha-ha-ha-ha-ha-ha-ha!";
			link.l1 = "And here I thought you had rid yourself of that idiotic habit.";
			link.l1.go = "Himenes_church_14";
		break;
		
		case "Himenes_church_14":
			sld = characterFromId("Islamona_carpenter");
			i = sti(sld.crew.qty);
			if (i >= 50) sTemp = "that we won't have to sit here for weeks waiting for events to unfold.";
			else sTemp = "that not everyone will have to participate in the battle.";
			dialog.text = "Ha-ha-ha-ha-ha... ha. I thought so too, captain! Rodgar is right, your presence already means, "+sTemp+"";
			link.l1 = "I already know what happened. Are there any casualties?";
			if (GetCharacterIndex("Mirabella") != -1) link.l1.go = "Himenes_church_15";
			else link.l1.go = "Himenes_church_16";
		break;
		
		case "Himenes_church_15":
			DialogExit();
			sld = characterFromId("Mirabella"); 
			sld.dialog.currentnode = "mirabelle_44";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_church_16":
			dialog.text = "Don't worry so much, Rodgar. It's not your fault, the fusiliers arrived too quickly. We wouldn't have been able to keep them behind our lines anyway, and there was no time to put them all to the sword.";
			link.l1 = "What about the Spaniards?";
			link.l1.go = "Himenes_church_17";
		break;
		
		case "Himenes_church_17":
			sld = characterFromId("Islamona_carpenter");
			i = sti(sld.crew.qty);
			if (CheckAttribute(pchar, "questTemp.IslaMona.Defend.Force")) // решил проблему самостоятельно
			{
				dialog.text = "Only three of them made it to us, and only one survived. The captain himself! Apparently, a very serious military sailor. But he can't help us yet - he'll have to stay in bed for at least a couple more days. By the way, captain, we heard gunshots and judging by your appearance, you did too.";
				link.l1 = "You could say that. The uninvited guests clearly didn't expect such an unexpected visit and were thrown back into the sea.";
				link.l1.go = "Himenes_church_20";
			}
			else
			{
				dialog.text = "Only three of them made it to us, and only one survived. The captain himself! Apparently, a very serious military sailor. But he can't help us yet - he'll have to stay in bed for at least a couple more days.";
				if (i >= 50) 
				{
					link.l1 = "Last time, I left quite a few of my people here on guard duty, so there should be a lot more of you than fusiliers. Why didn't you just throw them all back into the sea at once?";
					link.l1.go = "Himenes_church_17_1";
				}
				else 
				{
					link.l1 = "Fine, let's solve this problem. The plan is this: I'll lure them out for an open assault, and right now. There's no point in delaying. Get ready with buckshot and muskets, pirates at the gates, the rest stay at home - and sit tight.";
					link.l1.go = "Himenes_church_18";
				}
			}
		break;
		
		case "Himenes_church_17_1":
			dialog.text = "Cap, they're all professional soldiers, with a commander. And we don't even have proper weapons. Yes, of course, we could have overwhelmed them with numbers, but we would have lost at least twice as many people, and every person is precious and needed here.";
			link.l1 = "Fine, let's solve this problem. The plan is this: I'll lure them out for an open assault, and right now. There's no point in delaying. Get ready with buckshot and muskets, pirates at the gates, the rest stay at home - and sit tight.";
			link.l1.go = "Himenes_church_18";
		break;
		
		case "Himenes_church_18":
			dialog.text = "Captain, we're ready to fight!";
			link.l1 = "I know, Rodrigo. But you didn't let me finish: if even one enemy manages to break through the gates, you must all rush at him from all sides. And in battle, your chances of getting a bullet or a shard are diminishing. Any more questions?";
			link.l1.go = "Himenes_church_19";
		break;
		
		case "Himenes_church_19":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_68";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_church_20":
			dialog.text = "Well done! It's unpleasant, of course, that such an unfortunate fate befell your compatriots. But I'm grateful that once again you've taken our side.";
			link.l1 = "It wasn't easy, Rodrigo. Normal people will call it betrayal, and they'll be right.";
			link.l1.go = "Himenes_church_20_1";
			link.l2 = "This is my land, Rodrigo. It needs to be defended always and no matter who from.";
			link.l2.go = "Himenes_church_20_2";
		break;
		
		case "Himenes_church_20a":
			dialog.text = "Yes, old Rodrigo didn't expect, when he left Cadiz, that such adventures awaited him in the New World.";
			link.l1 = "Don't tell me. Sometimes I still have exactly the same thoughts.";
			link.l1.go = "Himenes_church_20b";
		break;
		
		case "Himenes_church_20b":
			dialog.text = "It's unpleasant, of course, that such an unfortunate fate befell your compatriots. But I'm grateful that once again you've taken our side.";
			link.l1 = "It wasn't easy, Rodrigo. Normal people will call it betrayal, and they'll be right.";
			link.l1.go = "Himenes_church_20_1";
			link.l2 = "This is my land, Rodrigo. It needs to be defended always and no matter who from.";
			link.l2.go = "Himenes_church_20_2";
		break;
		
		case "Himenes_church_20_1":
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			dialog.text = "I understand, captain. Allow me then to give you a brief overview of the situation in our settlement during your absence.";
			link.l1 = "Really? Hold on... Captain?";
			link.l1.go = "Himenes_church_21";
		break;
		
		case "Himenes_church_20_2":
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
			dialog.text = "I understand, captain. Allow me then to give you a brief overview of the situation in our settlement during your absence.";
			link.l1 = "Really? Hold on... Captain?";
			link.l1.go = "Himenes_church_21";
		break;
		
		case "Himenes_church_21":
			dialog.text = "Didn't mean to offend. It's just that Rodgar says that word so deliciously that I wanted to try it too. Very... Pirate-like.";
			link.l1 = "No problem, just surprised. So what happened here?";
			link.l1.go = "Himenes_church_22";
		break;
		
		case "Himenes_church_22":
			dialog.text = "Firstly, we built the church. It'll take a minute, come in. There's something to see. You've done a great deed, captain. It may not seem like it to you, but being able to communicate with God is very, very important for us. From this day on, we call Isla Mona our hogar.";
			link.l1 = "Hogar, dulce hogar? I'll definitely take a look. Did I carry all those candles for nothing?";
			link.l1.go = "Himenes_church_23";
		break;
		
		case "Himenes_church_23":
			dialog.text = "Not for nothing! Secondly, the factory was ruined - we lost all the workforce. You'll have to bring a new batch of slaves. Fortunately, after reassessing the efficiency of the work, we concluded that ten slaves will be more than enough. So, less hassle for you.";
			link.l1 = "Alright. Anything else?";
			link.l1.go = "Himenes_church_24";
		break;
		
		case "Himenes_church_24":
			dialog.text = "Everything's ready for the celebration. Well, almost: we need to clean up here, bury the bodies of those unfortunate souls... So come to the church tomorrow and we'll begin.";
			link.l1 = "To the church? Strange place to start the party. Are you planning to propose, Rodrigo?";
			link.l1.go = "Himenes_church_25";
		break;
		
		case "Himenes_church_25":
			dialog.text = "Ha-ha! No, captain, although some of our girls wouldn't mind. We don't mind if you do.";
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1 && IsOfficer(characterFromId("Mary")))
			{
				link.l1 = "";
				link.l1.go = "Himenes_church_25_1";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1 && IsOfficer(characterFromId("Helena")))
				{
					link.l1 = "";
					link.l1.go = "Himenes_church_25_2";
				}
				else
				{
					link.l1 = "Agreed, we'll come to the church tomorrow. To pray, of course.";
					if (CheckAttribute(pchar, "questTemp.IslaMona.Defend.Common") || CheckAttribute(pchar, "questTemp.IslaMona.Defend.Force")) link.l1.go = "Himenes_church_28";
					else link.l1.go = "Himenes_church_26";
				}
			}
		break;
		
		case "Himenes_church_25_1":
			DialogExit();
			sld = characterFromId("Mary");
			sld.dialog.currentnode = "IslaMona";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_church_25_2":
			DialogExit();
			sld = characterFromId("Helena");
			sld.dialog.currentnode = "IslaMona";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_church_26":
			dialog.text = "And one more thing, captain. Before the celebration, go and deal with the prisoner first. The decision must be made, and I understand it will be unpleasant anyway.";
			link.l1 = "Alright. I'll go right now.";
			link.l1.go = "Himenes_church_27";
		break;
		
		case "Himenes_church_27":
			DialogExit();
			DoQuestReloadToLocation("IslaMona_factoria", "reload", "reload1", "IslaMona_DefFraPrisoner"); /// ОПРЕДЕЛИТЬ ЛОКАТОР
		break;
		
		case "Himenes_church_28":
			DialogExit();
			WaitDate("", 0, 0, 0, 3, 5); //крутим время
			RefreshLandTime();
			RecalculateJumpTable();
			Whr_UpdateWeather();
			IslaMona_DefBattleLightClear();
			DoQuestReloadToLocation("IslaMona_town", "quest", "detector1", "");
		break;
		
		case "Himenes_church_29":
			dialog.text = "Everyone's here! Senor, we don't know what you initially wanted from this place and how you see it for yourself now. For us, it was first a forced refuge, and now it has become a real home. Your sailors, pirates, and runaway Spanish heretics live here. In any other place on earth, we would have already cut each other's throats. But here we are friends, work, and enjoy life. Isla Mona is not the final point on the map of this world for any of us, but perhaps here we will spend the happiest and most fruitful years of our lives. And this is your merit, your land, and your people. Muchas gracias, "+pchar.name+"!";
			link.l1 = "";
			link.l1.go = "Himenes_church_30";
			locCameraFromToPos(-4.11, 1.55, 1.09, true, -4.55, -0.20, 3.08);
		break;
		
		case "Himenes_church_30":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_86";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.0);
		break;
		
		case "Himenes_church_31":
			dialog.text = "Alright, alright. Captain, we've gathered gifts for you - a multitude of useful and simply pleasant things. Some we brought with us, and some we made ourselves. Accept this gift with a pure heart, and the rest we'll give you with our hard work.";
			link.l1 = "Thank you... I didn't expect this. So few bright moments and simple humanity in my odyssey... It means a lot to me, believe me.";
			link.l1.go = "Himenes_church_32";
			locCameraFromToPos(-4.11, 1.55, 1.09, true, -4.55, -0.20, 3.08);
		break;
		
		case "Himenes_church_32":
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "GunEchin", 10);
			TakeNItems(pchar, "slave_01", 10);
			TakeNItems(pchar, "grenade", 10);
			TakeNItems(pchar, "obereg_7", 1);
			TakeNItems(pchar, "purse3", 1);
			TakeNItems(pchar, "jewelry47", 1);
			TakeNItems(pchar, "jewelry52", 1);
			TakeNItems(pchar, "berserker_potion", 1);
			TakeNItems(pchar, "potion5", 10);
			TakeNItems(pchar, "cannabis7", 1);
			dialog.text = "And now - back to work!";
			link.l1 = "No, now it's - to the tavern! Rodrigo, let's go!";
			link.l1.go = "Himenes_church_33_1";
			link.l2 = "Yes, let's savor this wonderful moment a little longer.";
			link.l2.go = "Himenes_church_33_2";
		break;
		
		case "Himenes_church_33_1":
			DialogExit();
			DoQuestReloadToLocation("IslaMona_Town", "sit", "sit_base2", "IslaMona_ChurchToTavern"); /// ОПРЕДЕЛИТЬ ЛОКАТОР
		break;
		
		case "Himenes_church_33_2":
			DialogExit();
			LAi_SetActorType(pchar);
			ChangeShowIntarface();
			ResetSound();
			SetMusic("music_terrain");
			InterfaceStates.Buttons.Save.enable = false;
			bDisableCharacterMenu = true;
			pchar.GenQuest.FrameLockEsc = true;
			locCameraRotateAroundHero(0.0, 1.5, 0.0, 0.005, 0.0, 1.5, 0.0, 10000);
			Pchar.FuncCameraFly = "";
			DoQuestCheckDelay("IslaMona_ChurchTavernExit", 45.0);
		break;
		
		case "Himenes_74":
			dialog.text = "Ha-ha! Hic!";
			link.l1 = "By the way, I see you've almost stopped wildly laughing about everything and nothing. The fresh air of the Caribbean?";
			link.l1.go = "Himenes_75";
		break;
		
		case "Himenes_75":
			dialog.text = "More like Rodgar's corrupting influence. Watching him, I learned to mandar todo al carajo.";
			link.l1 = "";
			link.l1.go = "Himenes_76";
		break;
		
		case "Himenes_76":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_90";
			LAi_ActorSetSitMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_77":
			dialog.text = "I know many respectable people from there.";
			link.l1 = "";
			link.l1.go = "Himenes_78";
		break;
		
		case "Himenes_78":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_93";
			LAi_ActorSetSitMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_79":
			dialog.text = "Nope, I'd rather keep drinking rum and glaring at you.";
			link.l1 = "";
			link.l1.go = "Himenes_80";
		break;
		
		case "Himenes_80":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_96";
			LAi_ActorSetSitMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Himenes_81":
			dialog.text = "Captain! Hic!";
			link.l1 = "Hello to you too, Rodrigo. Had an eventful evening, I see?";
			link.l1.go = "Himenes_82";
		break;
		
		case "Himenes_82":
			dialog.text = "Better... don't ask. A month... won't be drinking. Oh. I have news! The captain...came to his senses.";
			link.l1 = "The only surviving Spaniard?";
			link.l1.go = "Himenes_83";
		break;
		
		case "Himenes_83":
			dialog.text = "Hic! Ouch! Yeah, they placed him in the factoria, in a house under guard.";
			link.l1 = "Right. I'll go to him. Take care not to overdo it.";
			link.l1.go = "Himenes_84";
		break;
		
		case "Himenes_84":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 10); /// ОН ИДЕТ НА ВЫХОД, ПОСТАВИТЬ ПРАВИЛЬНЫЙ ЛОКАТОР
			IslaMona_ChurchSetHispanos();
		break;
		
		case "Himenes_85":
			dialog.text = "I took a swim, and everything's as good as new! We'll live and work. I'll try to make the factoria work for as long as possible. Well, and do repairs, minor construction work. Maybe even decide about children with mine.";
			link.l1 = "Happy for all of you! It was a very nervous, costly... and wonderful adventure, and I'm glad it worked out for us. Good luck to everyone, and to those of us setting sail, even more luck!";
			link.l1.go = "Himenes_86";
		break;
		
		case "Himenes_86":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "IslaMona_Final", -1);
			sld = characterFromId("Islamona_carpenter");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", -1);
		break;
		
		// солдат в бухте
		case "Capral":
			dialog.text = "Halt! Corporal "+GetFullName(npchar)+". You have landed in a combat zone! Immediately identify yourself and state the purpose of your presence here!";
			if (CheckCharacterItem(pchar, "patent_fra"))
			{
				link.l1 = "Corporal, stand down! "+GetFullName(pchar)+", captain of the French Navy. I order you to escort me to your senior officer. Carry out the order!";
				link.l1.go = "Capral_1";
			}
			else
			{
				link.l1 = ""+GetFullName(pchar)+", captain of the ship named '"+pchar.ship.name+"'. Arrived on this island entirely by chance - for possible repairs and to replenish fresh water supplies.";
				link.l1.go = "Capral_3";
			}
		break;
		
		case "Capral_1":
			if(IsUniformEquip())
			{
				dialog.text = "Yes, sir, Captain! Please follow me. I just beg you, be careful! This island is swarming with bandits.";
				link.l1 = "";
			}
			else
			{
				dialog.text = "I beg your pardon, Captain. You're not in uniform, so I am obliged to check your officer's patent.";
				link.l1 = "See. Satisfied? Now - hurry to carry out the order, corporal!";
			}
			link.l1.go = "Capral_2";
		break;
		
		case "Capral_2":
			DialogExit();
			AddQuestRecord("IslaMona", "16");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "IslaMona_DefReloadFactory", 20.0);
		break;
		
		case "Capral_3":
			dialog.text = "You will have to come with me, Captain. Our senior officer will speak with you. From this moment on, your ship is considered temporarily requisitioned for the needs of the French Navy. Immediately notify the current watch and follow me.";
			link.l1 = "Requisition the ship Charle Prince? I don't think so!";
			link.l1.go = "Capral_5";
			link.l2 = "Looks like I don't have a choice. I'll do as you say.";
			link.l2.go = "Capral_4";
		break;
		
		case "Capral_4":
			DialogExit();
			AddQuestRecord("IslaMona", "18");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "IslaMona_DefReloadFactory", 5.0);
		break;
		
		case "Capral_5":
			DialogExit();
			DoQuestFunctionDelay("IslaMona_DefKillCapral", 1.0);
		break;
		
		case "Capral_6":
			if (CheckCharacterItem(pchar, "patent_fra"))
			{
				dialog.text = "Mr. Captain, the path to the enemy camp is to our right. I'll escort you.";
				link.l1 = "Stand down, Corporal. I'd rather go alone.";
			}
			else
			{
				dialog.text = "Captain, the path to the enemy camp is to our right. You won't get lost.";
				link.l1 = "Thank you for your concern.";
			}
			link.l1.go = "Capral_7";
		break;
		
		case "Capral_7":
			DialogExit();
			chrDisableReloadToLocation = false;
			IslaMona_DefGotoMarch();
			pchar.quest.islamona_def_killslaves.win_condition.l1 = "location";
			pchar.quest.islamona_def_killslaves.win_condition.l1.location = "IslaMona_town";
			pchar.quest.islamona_def_killslaves.function = "IslaMona_DefKillSlaves";
		break;
		
		case "FraOfficer":
			if (CheckCharacterItem(pchar, "patent_fra"))
			{
				dialog.text = "Captain "+GetFullName(pchar)+"! Thank God! Allow me to introduce myself - Lieutenant "+GetFullName(npchar)+". A great admirer of yours! I don't know what you're doing on this miserable piece of land, but you're just in time!\nI must say, Captain, you have become very popular among our officer corps. Although many are annoyed by your... 'special' style of service, everyone agrees that your patent makes our fleet stronger. We are currently in a completely stalemate situation, so the assistance of someone like you will be difficult to overestimate!";
				link.l1 = "What can I do? And what's going on here?";
				link.l1.go = "FraOfficer_1";
			}
			else
			{
				dialog.text = "Captain "+GetFullName(pchar)+". Your name has been mentioned several times in the fleet reports. And always in a very dubious light. However, now you have a chance to interrupt this less honorable trend and serve the motherland.";
				link.l1 = "What can I do? And what's going on here?";
				link.l1.go = "FraOfficer_8";
			}
		break;
		
		case "FraOfficer_1":
			dialog.text = "We were on the 'Warrior', a routine mission - hunting down particularly bold Spanish raiders. The case is generally very simple: the spy provides the area and data on the target, and you catch it from under the horizon. There's nothing special to tell, and it all ended very badly: the Spaniards found us first and attacked, despite the fact that they were on a corvette themselves. If we had something more serious, we wouldn't have gone to the bottom with us... but at least we managed to blow up their whole hull. Only my squad survived. The Castilians, however, also had someone survive. But not for long, haha!";
			if (CheckAttribute(pchar, "questTemp.IslamonaSpaOfficer"))
			{
				link.l1 = "The frigate 'Warrior'? Captain Shocke died?";
				link.l1.go = "FraOfficer_1_1";
			}
			else
			{
				link.l1 = "";
				link.l1.go = "FraOfficer_2";
			}
		break;
		
		case "FraOfficer_1_1":
			dialog.text = "I am not surprised that you asked about him, Captain. I heard about your involvement in intercepting the 'Alcantara'. A great feat, even then you laid the foundation for your patent! Commander Shocke didn't die, quite the opposite! He was promoted, and at his request, sent to serve in the Mediterranean. We can only envy him in a situation like ours now. So, actually, about our situation...";
			link.l1 = "";
			link.l1.go = "FraOfficer_2";
		break;
		
		case "FraOfficer_2":
			dialog.text = "We found a settlement on the island - quite a populated bandit's den for - just listen - pirates and Spaniards. Unbelievable! You know, usually these bastards only cut and hang each other, but here - behold: in the very center of the archipelago, they work together like a family to extract buccaneer's wood. Have you seen the pier they've built for themselves? Guests don't come to this breed on rowboats. Our task is extremely clear: with your help, we capture the settlement, take the buccaneer's wood and prisoners, and you take everyone to Capsterburg. Meanwhile, the authorities will figure things out for themselves... And while they're figuring it out, we'll deal with the buccaneer's wood and celebrate properly with other officers from my home squadron!";
			link.l1 = "What prevented you from taking the settlement on your own by this time?";
			link.l1.go = "FraOfficer_3";
		break;
		
		case "FraOfficer_3":
			sld = characterFromId("Islamona_carpenter");
			i = sti(sld.crew.qty);
			if (i >= 50) sTemp = "There are probably many more bandits than us - we saw tents on the shore. And besides tents, they also have a wall, gates, cannon!";
			else sTemp = "There are probably not so many bandits, otherwise they would have kicked us out of here already, but they still have a wall, gates, cannon and plenty of time!";
			dialog.text = "What prevented us?! We only have twelve fusiliers and seven sailors. All tired and worn out. We saved only five muskets, with only one cartridge each at best! "+sTemp+"";
			link.l1 = "But do you have a plan?";
			link.l1.go = "FraOfficer_4";
		break;
		
		case "FraOfficer_4":
			dialog.text = "Listen, we didn't waste time. First of all, we took over this factory, thus capturing some food and water supplies, and most importantly - a full warehouse of buccaneer's wood and more than a dozen slaves! We wouldn't have been able to guard the slaves anyway, so we immediately conducted reconnaissance by combat, sending them to attack their former masters under the cover of our muskets. That's how we found out that the bandits have a weapon in stock.";
			link.l1 = "Do I understand correctly that now you want to send me and my men to deal with this weapon instead of the slaves?";
			link.l1.go = "FraOfficer_5";
		break;
		
		case "FraOfficer_5":
			dialog.text = "No, but you can go to the bandits as a parley. Your arrival means their lair is exposed, and now the soldiers of the king have a ship and reinforcement. Well, while they're hanging ears and assessing the depth of their depth, you'll get as close to the gun as possible, throw a hand grenade under it, and don't let yourself be killed until our people and your people approach. If you're not sure you can handle it, try sending one of your men instead of yourself.";
			link.l1 = "Let me first go to them without a bomb and offer them to surrender. I'll look around, understand their mood and strengths, sow doubt in their souls. If they don't surrender, then I'll go to them again, but with a bomb.";
			if (CheckCharacterItem(pchar, "patent_fra")) link.l1.go = "FraOfficer_6";
			else link.l1.go = "FraOfficer_6_1";
		break;
		
		case "FraOfficer_6":
			GiveItem2Character(pchar, "grenade");
			//Log_Info("Вы получили гранату");
			PlaySound("interface\important_item.wav");
			dialog.text = "... and by that time, they'll already be used to you, so it'll be easier to carry out the sabotage! Clever! Well, I didn't expect anything else from you, Captain. Proceed when you're ready. But still, here... It might come in handy.";
			link.l1 = "";
			link.l1.go = "FraOfficer_7";
		break;
		
		case "FraOfficer_6_1":
			dialog.text = "... and by that time, they'll already be used to you, so it'll be easier to carry out the sabotage. That's what we'll do. Carry on!";
			link.l1 = "";
			link.l1.go = "FraOfficer_7";
		break;
		
		case "FraOfficer_7":
			DialogExit();
			AddQuestRecord("IslaMona", "19");
			chrDisableReloadToLocation = false;
			pchar.quest.islamona_def_goout.win_condition.l1 = "location";
			pchar.quest.islamona_def_goout.win_condition.l1.location = "IslaMona_Jungle_01";
			pchar.quest.islamona_def_goout.function = "IslaMona_DefCapralTalk";
		break;
		
		case "FraOfficer_8":
			dialog.text = "There was a prolonged battle with the Spaniards in this area. Both ships went down, and the survivors ended up here. Mostly French, but some of our enemies managed to survive as well. And you don't need to know more, sorry, Captain. Secret information, you understand.";
			link.l1 = "Understood.";
			link.l1.go = "FraOfficer_9";
		break;
		
		case "FraOfficer_9":
			dialog.text = "We found a settlement on the island - quite a populated bandit's den for - just listen - pirates and Spaniards. Unbelievable! You know, usually these bastards only cut and hang each other, but here - behold: in the very center of the archipelago, they work together like a family to extract buccaneer's wood. Have you seen the pier they've built for themselves? Guests don't come to this breed on rowboats. Our task is extremely clear: with your help, we capture the settlement, take the buccaneer's wood and prisoners, and you take everyone to Capsterburg. Meanwhile, the authorities will figure things out for themselves... And while they're figuring it out, I might even be ready to give you the opportunity to take some valuable timber for your needs.";
			link.l1 = "What prevented you from taking the settlement on your own by this time?";
			link.l1.go = "FraOfficer_3";
		break;
		
		case "FraOfficer_10":
			dialog.text = "Here you are! Any news?";
			link.l1 = "Is this an honorary guard?";
			link.l1.go = "FraOfficer_11";
		break;
		
		case "FraOfficer_11":
			dialog.text = "Obviously, a decision will be made shortly about our further actions. I wouldn't want to search for my people all over the island to issue new orders.";
			if (CheckCharacterItem(pchar, "patent_fra"))
			{
				link.l1 = "Excellent initiative! You'll have your orders. I've conducted reconnaissance: the enemy is weak, and the cannon is out of ammunition. I order you to attack the bandit's lair immediately, Lieutenant. Stop nursing your hands. Just another day in the fleet. Execute!";
				link.l1.go = "FraOfficer_12";
			}
			else
			{
				link.l1 = "In my opinion, you could have taken them right after the 'slave' reconnaissance by force. Their defense is laughable, just a couple of serious fighters. No need to overthink - we could have been drinking trophy wine while sitting on a mountain of ironwood.";
				link.l1.go = "FraOfficer_14";
			}
		break;
		
		case "FraOfficer_12":
			dialog.text = "Affirmative, Captain!";
			link.l1 = "...";
			link.l1.go = "FraOfficer_13";
		break;
		
		case "FraOfficer_13":
			DialogExit();
			ChangeCharacterComplexReputation(pchar, "nobility", -25);
			AddQuestRecord("IslaMona", "22");
			IslaMona_DefAttackLight();
		break;
		
		case "FraOfficer_14":
			dialog.text = "And are these the results of your reconnaissance? I understand that it might be strange to expect too much from a non-military person, but I need facts! Facts, Captain, not your opinion!";
			link.l1 = "You offend me, Lieutenant. Reporting!";
			link.l1.go = "FraOfficer_15";
		break;
		
		case "FraOfficer_15":
			dialog.text = "";
			link.l1 = "Right now, there's a surviving captain of a Spanish ship you sank with you. An experienced commander who will soon recover. If you delay, he'll recover and organize defense by the book of military science, and then we'll have a tough time. We need to hurry - I repeat, they are weak and demoralized.";
			link.l1.go = "FraOfficer_15_1";
			link.l2 = "Reinforcements are coming soon - to take the buccaneer's wood. I don't think it's a bluff: you saw the docks and a pile of ready-to-deliver goods in the factory warehouse yourself. We need to hurry - I repeat, they are weak and demoralized. If you delay, you'll wait for the arrival of a pirate ship.";
			link.l2.go = "FraOfficer_15_2";
			link.l3 = "Nearly half of the inhabitants of this hole are women. You've been fighting not even against militia: there have been no more than a dozen fighters against you all this time. They are weak and demoralized.";
			link.l3.go = "FraOfficer_15_3";
			link.l4 = "The cannon is out of ammunition. I've seen enough guns in my lifetime and can tell when a crew is ready to fire and when it's not. Without their artillery, they're nothing but poor warriors; they are weak and demoralized.";
			link.l4.go = "FraOfficer_15_4";
			link.l5 = "Think about the trophies and glory, Lieutenant! A solo victory over a Spanish raider, capturing a bandit's nest and a unique source of buccaneer's wood - all of this calls for commanding your own ship! I repeat, they are weak and demoralized, it's time to crush them!";
			link.l5.go = "FraOfficer_15_5";
		break;
		
		case "FraOfficer_15_1":
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) >= 80)
			{
				notification("Skill Check Passed", SKILL_LEADERSHIP);
				dialog.text = "Thank you, Captain. This is valuable information, and you were right, there's no need to delay here. My men are all here, we are strong, trained, and ready. Everything will be over in half an hour. Captain, please prepare to receive people, prisoners, and cargo on your ship. We won't linger here for long.";
				link.l1 = "Everything is ready, Lieutenant. We were only waiting for you. See you later!";
				link.l1.go = "FraOfficer_16";
			}
			else
			{
				notification("Skill Check Failed (80)", SKILL_LEADERSHIP);
				dialog.text = "Thank you, Captain. This is valuable information. In that case, head to the dock and prepare your boarding team. We'll storm the bandit's nest together and immediately. The best of my and your men will lead the vanguard - they will be the ones to capture the gates. We'll discuss the rest after inspecting our forces together. Don't let me and your country down, "+GetFullName(pchar)+".";
				link.l1 = "...So be it. See you later, Lieutenant.";
				link.l1.go = "FraOfficer_17";
			}
		break;
		
		case "FraOfficer_15_2":
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) >= 60 && sti(pchar.reputation.nobility) > 41)
			{
				notification("Reputation Check Passed", "None");
				notification("Skill Check Passed", SKILL_LEADERSHIP);
				dialog.text = "Thank you, Captain. This is valuable information, and you were right, there's no need to delay here. My men are all here, we are strong, trained, and ready. Everything will be over in half an hour. Captain, please prepare to receive people, prisoners, and cargo on your ship. We won't linger here for long.";
				link.l1 = "Everything is ready, Lieutenant. We were only waiting for you. See you later!";
				link.l1.go = "FraOfficer_16";
			}
			else
			{
				notification("Reputation Too Low! ("+XI_ConvertString(GetReputationName(42))+")", "None");
				notification("Skill Check Failed (60)", SKILL_LEADERSHIP);
				dialog.text = "Thank you, Captain. This is valuable information. In that case, head to the dock and prepare your boarding team. We'll storm the bandit's nest together and immediately. The best of my and your men will lead the vanguard - they will be the ones to capture the gates. We'll discuss the rest after inspecting our forces together. Don't let me and your country down, "+GetFullName(pchar)+".";
				link.l1 = "...So be it. See you later, Lieutenant.";
				link.l1.go = "FraOfficer_17";
			}
		break;
		
		case "FraOfficer_15_3":
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) >= 70 && sti(pchar.reputation.nobility) > 41)
			{
				notification("Reputation Check Passed", "None");
				notification("Skill Check Passed", SKILL_LEADERSHIP);
				dialog.text = "Thank you, Captain. This is valuable information, and you were right, there's no need to delay here. My men are all here, we are strong, trained, and ready. Everything will be over in half an hour. Captain, please prepare to receive people, prisoners, and cargo on your ship. We won't linger here for long.";
				link.l1 = "Everything is ready, Lieutenant. We were only waiting for you. See you later!";
				link.l1.go = "FraOfficer_16";
			}
			else
			{
				notification("Reputation Too Low! ("+XI_ConvertString(GetReputationName(42))+")", "None");
				notification("Skill Check Failed (70)", SKILL_LEADERSHIP);
				dialog.text = "Thank you, Captain. This is valuable information. In that case, head to the dock and prepare your boarding team. We'll storm the bandit's nest together and immediately. The best of my and your men will lead the vanguard - they will be the ones to capture the gates. We'll discuss the rest after inspecting our forces together. Don't let me and your country down, "+GetFullName(pchar)+".";
				link.l1 = "...So be it. See you later, Lieutenant.";
				link.l1.go = "FraOfficer_17";
			}
		break;
		
		case "FraOfficer_15_4":
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) >= 60 && sti(pchar.reputation.nobility) > 41)
			{
				notification("Reputation Check Passed", "None");
				notification("Skill Check Passed", SKILL_LEADERSHIP);
				dialog.text = "Thank you, Captain. This is valuable information, and you were right, there's no need to delay here. My men are all here, we are strong, trained, and ready. Everything will be over in half an hour. Captain, please prepare to receive people, prisoners, and cargo on your ship. We won't linger here for long.";
				link.l1 = "Everything is ready, Lieutenant. We were only waiting for you. See you later!";
				link.l1.go = "FraOfficer_16";
			}
			else
			{
				notification("Reputation Too Low! ("+XI_ConvertString(GetReputationName(42))+")", "None");
				notification("Skill Check Failed (60)", SKILL_LEADERSHIP);
				dialog.text = "Thank you, Captain. This is valuable information. In that case, head to the dock and prepare your boarding team. We'll storm the bandit's nest together and immediately. The best of my and your men will lead the vanguard - they will be the ones to capture the gates. We'll discuss the rest after inspecting our forces together. Don't let me and your country down, "+GetFullName(pchar)+".";
				link.l1 = "...So be it. See you later, Lieutenant.";
				link.l1.go = "FraOfficer_17";
			}
		break;
		
		case "FraOfficer_15_5":
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) >= 90)
			{
				notification("Skill Check Passed", SKILL_LEADERSHIP);
				dialog.text = "Thank you, Captain. This is valuable information, and you were right, there's no need to delay here. My men are all here, we are strong, trained, and ready. Everything will be over in half an hour. Captain, please prepare to receive people, prisoners, and cargo on your ship. We won't linger here for long.";
				link.l1 = "Everything is ready, Lieutenant. We were only waiting for you. See you later!";
				link.l1.go = "FraOfficer_16";
			}
			else
			{
				notification("Skill Check Failed (90)", SKILL_LEADERSHIP);
				dialog.text = "Thank you, Captain. This is valuable information. In that case, head to the dock and prepare your boarding team. We'll storm the bandit's nest together and immediately. The best of my and your men will lead the vanguard - they will be the ones to capture the gates. We'll discuss the rest after inspecting our forces together. Don't let me and your country down, "+GetFullName(pchar)+".";
				link.l1 = "...So be it. See you later, Lieutenant.";
				link.l1.go = "FraOfficer_17";
			}
		break;
		
		case "FraOfficer_16": // французы атакуют сами
			DialogExit();
			ChangeCharacterComplexReputation(pchar, "nobility", -10);
			ChangeCharacterComplexReputation(pchar, "authority", 5);
			AddQuestRecord("IslaMona", "24");
			IslaMona_DefAttackLight();
		break;
		
		case "FraOfficer_17": // совместная атака
			DialogExit();
			ChangeCharacterComplexReputation(pchar, "nobility", -7);
			AddQuestRecord("IslaMona", "23");
			IslaMona_DefAttackCommon();
		break;
		
		case "FraOfficer_18":
			if (CheckCharacterItem(pchar, "patent_fra")) dialog.text = "And I, idiot, admired you! A-agh! The pride of France, Captain " + GetFullName(pchar) + "!! You are unworthy of your patent!!!";
			else dialog.text = ""+GetFullName(pchar)+", scum, traitor, and cursed pirate! I should have guessed that this wretched den is your stinking domain! France neither forgets nor forgives men like you!";
			link.l1 = "";
			link.l1.go = "FraOfficer_19";
		break;
		
		case "FraOfficer_19":
			DialogExit();
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_75";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "FraOfficer_20":
			dialog.text = "Are you ready, Captain? Your squad looks worthy!";
			link.l1 = "Thank you, Lieutenant. Shall we begin?";
			link.l1.go = "FraOfficer_21";
		break;
		
		case "FraOfficer_21":
			dialog.text = "Yes, let's proceed immediately!";
			link.l1 = "...";
			link.l1.go = "FraOfficer_22";
		break;
		
		case "FraOfficer_22":
			DialogExit();
			IslaMona_DefAttackCommonRun();
		break;
		
		// обиженный пират
		case "Pirate":
			dialog.text = "Ha! " + GetFullName(pchar) + "! What a meeting. Hey, grab him! This bastard owns everything here! This is his island!";
			link.l1 = "What a day this is...";
			link.l1.go = "Pirate_1";
		break;
		
		case "Pirate_1":
			DialogExit();
			IslaMona_DefCheckJungleFight();
		break;
		
		// Алонсо
		case "Alonso":
			dialog.text = "Cap'n, what are the orders? There's a signal to stand by and send the boarding party.";
			link.l1 = "The order stands. Boys, follow me, we need to clear our home from unwanted guests. The prize is mine, all the trophies are yours!";
			link.l1.go = "Alonso_1";
		break;
		
		case "Alonso_1":
			dialog.text = "Hoorah!";
			link.l1 = "To battle!";
			link.l1.go = "Alonso_2";
		break;
		
		case "Alonso_2":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_CharacterDisableDialog(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			for (i=1; i<=5; i++) 
			{
				sld = characterFromId("IM_our_soldier_"+i);
				LAi_SetActorType(sld);
				LAi_CharacterDisableDialog(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona.Defend.Common"))
			{
				pchar.quest.islamona_attack_common1.win_condition.l1 = "location";
				pchar.quest.islamona_attack_common1.win_condition.l1.location = "IslaMona_Jungle_01";
				pchar.quest.islamona_attack_common1.function = "IslaMona_DefAttackCommonPrepare";
			}
			else
			{
				LocatorReloadEnterDisable("IslaMona_Jungle_01", "reload3_back", true);
				LocatorReloadEnterDisable("IslaMona_Jungle_01", "reload1_back", true);
				pchar.quest.islamona_attack_force.win_condition.l1 = "location";
				pchar.quest.islamona_attack_force.win_condition.l1.location = "IslaMona_factoria";
				pchar.quest.islamona_attack_force.function = "IslaMona_DefAttackForce";
			}
		break;
		
		// испанский офицер
		case "SpaOfficer":
			dialog.text = "Greetings, senor. Are you the owner of this land? Allow me to introduce myself, Grand Francisco de Alba, former captain of the 'Perro Marino' corvette.";
			link.l1 = "Yes, this is my land. I am " + GetFullName(pchar) + ", captain of the ship '" + pchar.ship.name + "'. Grand? We haven't had such distinguished guests here before.";
			link.l1.go = "SpaOfficer_1";
		break;
		
		case "SpaOfficer_1":
			dialog.text = "Oh, Monsieur " + GetFullName(pchar) + "! Your name is well known. You see, lately your name has been popping up so often in the Casa de Contratacion reports that I was seriously expecting orders to deal with you.";
			link.l1 = "Deal with me?";
			link.l1.go = "SpaOfficer_2";
		break;
		
		case "SpaOfficer_2":
			dialog.text = "I think there's no point in pretending. My job is to seek and destroy enemies of Spain and King Philip on all the seas of the globe.";
			link.l1 = "It's fortunate that such orders haven't come yet. You are obviously a very skilled naval officer.";
			link.l1.go = "SpaOfficer_3";
		break;
		
		case "SpaOfficer_3":
			dialog.text = "The fact that I am now a half-dead prisoner on a tiny island teeming with pirates and my fellow countrymen on the run only confirms your conclusion, ha-ha! It was a very dangerous affair, but orders are orders. We almost succeeded! It's deeply regrettable for my men - I knew them all by name, we served together for many years. But my country will have to shed more of its sons' blood to maintain its imperial status. Our family knows this better than most.";
			if (CheckAttribute(pchar, "questTemp.IslamonaSpaOfficer"))
			{
				link.l1 = "";
				link.l1.go = "SpaOfficer_4";
			}
			else
			{
				link.l1 = "Let's get back to more pressing matters for now. What am I to do with you, Grand?";
				link.l1.go = "SpaOfficer_5";
			}
		break;
		
		case "SpaOfficer_4":
			dialog.text = "By the way, Monsieur de Mor, the 'Warrior' - that little ship was familiar to you, wasn't it? Your audacious operation in Porto Bello did not go unnoticed. Bold, even suicidal. You needed money badly, am I right? Ha!";
			link.l1 = "You know a lot about me, Grand. But let's move on to your fate.";
			link.l1.go = "SpaOfficer_5";
		break;
		
		case "SpaOfficer_5":
			dialog.text = "What's there to think about? As in any good story, you have three options: kill me, leave me here, or set me free. If you set me free, I give you the word of the de Alba family that I will never tell anyone about this place and your involvement in my misadventures. Moreover, I will be your debtor, and until that debt is repaid, I will never fight against you.";
			link.l1 = "I can't risk it, Grand.";
			link.l1.go = "SpaOfficer_6";
			link.l2 = "You will spend some time here. You will live and work on equal terms with your compatriots.";
			link.l2.go = "SpaOfficer_7";
			link.l3 = "Welcome aboard my ship, Grand. I will disembark you at the Santiago lighthouse when the time comes. I hope you will keep your word.";
			link.l3.go = "SpaOfficer_8";
		break;
		
		case "SpaOfficer_6":
			dialog.text = "I understand, senor. Well, in any case, I am already dead in that battle together with my men. It's a good ending.";
			link.l1 = "";
			link.l1.go = "SpaOfficer_6_1";
		break;
		
		case "SpaOfficer_6_1":
			DialogExit();
			DoQuestFunctionDelay("IslaMona_KillSpanish", 1.0);
		break;
		
		case "SpaOfficer_7":
			dialog.text = "I admit, I don't like being half-hearted. But there is no dishonor in being a prisoner, so I accept your gift of life and will live in peace with these kind and apparently very happy people. Nevertheless, if I ever leave this place, I will owe you nothing.";
			link.l1 = "";
			link.l1.go = "SpaOfficer_7_1";
		break;
		
		case "SpaOfficer_7_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 10.0);
			AddQuestRecord("IslaMona", "27");
			IslaMona_FinalPrepare();
		break;
		
		case "SpaOfficer_8":
			dialog.text = "I give you my word and the word of the de Alba family! See you on the ship!";
			link.l1 = "";
			link.l1.go = "SpaOfficer_8_1";
		break;
		
		case "SpaOfficer_8_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 3.0);
			AddQuestRecord("IslaMona", "28");
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			ChangeCharacterComplexReputation(pchar, "nobility", 6);
			pchar.quest.islamona_final_mayak.win_condition.l1 = "location";
			pchar.quest.islamona_final_mayak.win_condition.l1.location = "Mayak9";
			pchar.quest.islamona_final_mayak.function = "IslaMona_FinalMayakSpanish";
			pchar.questTemp.IslaMona.Mayak = "true";
			IslaMona_FinalPrepare();
		break;
		
		case "SpaOfficer_9":
			dialog.text = "Captain " + GetFullName(pchar) + "! You saved my life and brought me back to my own. I understand how difficult it was to take such a risk - I would never have dared to do such a thing. I owe you, senor. I give you my word that I will never tell anyone about the circumstances of that ill-fated battle. When you return to the Old World, be sure to find me; you will always be welcome at our family estate in Madrid. For now, take this...";
			link.l1 = "A piece of a map?";
			link.l1.go = "SpaOfficer_10";
		break;
		
		case "SpaOfficer_10":
			AddMapPart();
			dialog.text = "That's all I had of value with me. I have no doubt you will find the other piece easily. Farewell! And good luck to you, my friend.";
			link.l1 = "Farewell, Grand. Remember your word, and good luck to you!";
			link.l1.go = "SpaOfficer_11";
		break;
		
		case "SpaOfficer_11":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 10.0);
			pchar.questTemp.IslaMona.Mayak = "done";
			ChangeCharacterNationReputation(pchar, SPAIN, 20);
			AddQuestRecord("IslaMona", "29");
			CloseQuestHeader("IslaMona");
		break;
		
		// Диалоги обитателей Исламоны
		// мужское население
		case "island_man":
			dialog.text = LinkRandPhrase("Greetings! How are you, Captain? Things are going well for us.","Working for the community is the greatest joy!","Your island is wonderful, Captain, and we'll do everything for its prosperity.");
			link.l1 = LinkRandPhrase("Nice to hear that.","Glad to hear everything's fine.","I admire your enthusiasm, amigo.");
			link.l1.go = "island_man_1";
			if(CheckAttribute(pchar,"questTemp.IslaMona.TownStage"))
			{
				switch(sti(pchar.questTemp.IslaMona.TownStage))
				{
					case 0:
						dialog.text = RandPhraseSimple(RandPhraseSimple("Don't take it as impudence, senor, but living here is impossible.","Anything is better than sitting in the Inquisition's cells..."),
						                               RandPhraseSimple("Thank you for saving us, Captain.","Are these... pirates your friends?"));
						link.l1 = "...";
						link.l1.go = "island_man_1";
					break;
					
					case 1:
						dialog.text = RandPhraseSimple(RandPhraseSimple("It's not bad here! Just a bit boring.","Captain, nice to see you. Drop by sometime!"),
						                               RandPhraseSimple("Someone found skulls on the beach and brought them to the morning meeting. Is it always like this here?","I'll tell you a secret, Senor Himenes obviously benefits from the fresh air and safety of this place."));
						link.l1 = "...";
						link.l1.go = "island_man_1";
					break;
					
					case 2:
						dialog.text = RandPhraseSimple(RandPhraseSimple("It's not bad here! Just a bit boring.","Captain, nice to see you. Drop by sometime!"),
						                               RandPhraseSimple("Someone found skulls on the beach and brought them to the morning meeting. Is it always like this here?","I'll tell you a secret, Senor Himenes obviously benefits from the fresh air and safety of this place."));
						link.l1 = "...";
						link.l1.go = "island_man_1";
					break;
					
					case 3:
						dialog.text = RandPhraseSimple(RandPhraseSimple("God bless you, Captain!","Once a week, we hold performances on the beach and in the tavern. Drop by sometime."),
						                               RandPhraseSimple("Your sailors are constantly bringing us all sorts of trinkets in exchange for fresh food. Thank you for encouraging this.","It's amazing how this place hasn't been discovered yet. I hope it stays that way."));
						link.l1 = "...";
						link.l1.go = "island_man_1";
					break;
				}
			}
		break;
		
		case "island_man_1":
			DialogExit();
			npchar.dialog.currentnode = "island_man";
		break;
		
		case "island_man_2":
			dialog.text = "Thank you, senor. Thanks to you, we've seen the real New World. God bless you!";
			link.l1 = "";
			link.l1.go = "island_man_3";
			locCameraFromToPos(1.64, 1.58, -5.11, false, 2.66, 0.20, -5.74);
		break;
		
		case "island_man_3":
			DialogExit();
			npchar.dialog.currentnode = "island_man";
			sld = characterFromId("Himenes_companion_12");
			sld.dialog.currentnode = "island_woman_2";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.0);
		break;
		
		// женское население
		case "island_woman":
			dialog.text = LinkRandPhrase("Safety and peace - that's what I like here!","A wonderful paradise! Well, almost...","We're happy to find a new home here, after so many hardships.");
			link.l1 = LinkRandPhrase("I'm happy for you and your community.","Yes, I also like this little island.","It's nice to know that you're satisfied.");
			link.l1.go = "island_woman_1";
			if(CheckAttribute(pchar,"questTemp.IslaMona.TownStage"))
			{
				switch(sti(pchar.questTemp.IslaMona.TownStage))
				{
					case 0:
						dialog.text = LinkRandPhrase("Oh... Hello.","Senor, who are those... rough men with weapons?","Thank you for saving us, Captain.");
						link.l1 = "...";
						link.l1.go = "island_woman_1";
					break;
					
					case 1:
						dialog.text = LinkRandPhrase("Our men did a great job - the houses are excellent. But we also worked hard!","Senor Captain, don't worry: the women of our small clan are not afraid of difficulties and temporary discomfort.","Such air here! And the sea! You feel closer to God!");
						link.l1 = "...";
						link.l1.go = "island_woman_1";
					break;
					
					case 2:
						dialog.text = LinkRandPhrase("Our men did a great job - the houses are excellent. But we also worked hard!","Senor Captain, don't worry: the women of our small clan are not afraid of difficulties and temporary discomfort.","Such air here! And the sea! You feel closer to God!");
						link.l1 = "...";
						link.l1.go = "island_woman_1";
					break;
					
					case 3:
						dialog.text = LinkRandPhrase("Come back more often, Senor Captain. I'm always happy to see you.","Senor Rodgar is an amazing storyteller. You can listen to him talk forever!","Hehe. They say someone from our group is already expecting an addition to the family. Life goes on even on Isla Mona!");
						link.l1 = "...";
						link.l1.go = "island_woman_1";
					break;
				}
			}
		break;
		
		case "island_woman_1":
			DialogExit();
			npchar.dialog.currentnode = "island_woman";
		break;
		
		case "island_woman_2":
			dialog.text = "You... Muchas gracias, senor! Come by more often...";
			link.l1 = "";
			link.l1.go = "island_woman_3";
			locCameraFromToPos(-1.86, 1.18, 4.51, true, -1.49, 0.20, 6.13);
		break;
		
		case "island_woman_3":
			DialogExit();
			npchar.dialog.currentnode = "island_woman";
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_church_31";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.0);
		break;
		
		// пираты Родгара
		case "fort_pirate":
			if(npchar.location == "islamona_factoria")
			{
				dialog.text = dialog.text = RandPhraseSimple(RandPhraseSimple("Everything's fine, Cap!","Slaves under control, don't worry."),
						                                 RandPhraseSimple("You don't have to worry, mutiny is excluded.","Thank you for the rum! We'll get to work!"));
			}
			else
			{
				dialog.text = dialog.text = RandPhraseSimple(RandPhraseSimple("Spaniards? We didn't expect this from you.","Now we have to walk all the way to the beach just to sleep in peace!"),
						                                 RandPhraseSimple("Why did you decide on all this - eh, Cap?","The boss trusted you then - and he didn't go wrong. We'll believe in you again."));
			}
			link.l1 = "...";
			link.l1.go = "fort_pirate_1";
		break;
		
		case "fort_pirate_1":
			DialogExit();
			npchar.dialog.currentnode = "fort_pirate";
		break;
		
		// посетители таверны
		case "citizen_tavern":
			dialog.text = LinkRandPhrase("After back-breaking labor, it's not a sin to have a drink or two...","I'm almost done and heading home; the wife must be waiting...","Ah, it's nice to relax in our tavern after work! We're all grateful to you, captain!");
			link.l1 = LinkRandPhrase("Enjoy your drink, compadre, ha-ha!","Relax, mate, just don't overdo it, or the wife will scold you, ha-ha!","Take it easy, pal, life is not all about work!");
			link.l1.go = "citizen_tavern_1";
		break;
		
		case "citizen_tavern_1":
			DialogExit();
			npchar.dialog.currentnode = "citizen_tavern";
		break;
		
		case "sailor_tavern":
			if (GetCharacterIndex("Mirabella") != -1) sTemp = "Who's that pretty mulatto woman living here?";
				else sTemp = "Captain, nice place you got here!";
			dialog.text = RandPhraseSimple(RandPhraseSimple("Captain, nice place you got here!", "Imagine if we were to suddenly find ourselves devoid of rum. You'd surely procure more, right?"), RandPhraseSimple("I've dreamed of a vacation like this for a long time. I'd love a whorehouse though... just a wild thought, Cap.", sTemp));
			link.l1 = "...";
			link.l1.go = "sailor_tavern_1";
		break;
		
		case "sailor_tavern_1":
			DialogExit();
			npchar.dialog.currentnode = "sailor_tavern";
		break;
		
		case "sailor_town":
			dialog.text = RandPhraseSimple(RandPhraseSimple("Thanks for the vacation, Captain.", "Nice place you've built up here - you have a knack for keeping things in order, Captain."), RandPhraseSimple("Fresh food, booze, solid ground underfoot. It's a dream.", "I'd like to stay here a little longer."));
			link.l1 = "...";
			link.l1.go = "sailor_town_1";
		break;
		
		case "sailor_town_1":
			DialogExit();
			npchar.dialog.currentnode = "sailor_town";
		break;
		
		// рабы
		case "slave":
			dialog.text = RandPhraseSimple(RandPhraseSimple("I'm so tired - I can barely stand.", "No more strength to live like this!"), RandPhraseSimple("This work is too hard for me.", "The overseers left no living cell on my skin!"));				
			link.l1 = "";
			link.l1.go = "slave_1";
		break;
		
		case "slave_1":
			DialogExit();
			npchar.dialog.currentnode = "slave";
		break;
		
		// энкауниеры в домах
		case "HouseMan":
			dialog.text = LinkRandPhrase("Can I help you with something, captain?","Come in, have some local paella. Just, for God's sake, don't ask what it's made of!","Welcome, captain. How do you like it here?");
			link.l1 = "...";
			link.l1.go = "HouseMan_1";
		break;
		
		case "HouseMan_1":
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			npchar.dialog.currentnode = "HouseMan";
		break;
		
		case "HouseWoman":
			dialog.text = LinkRandPhrase("Senor, welcome!","Hello, captain. Will you stay?","Are you here for me? Please, come in, just ignore the mess, senor.");
			link.l1 = "...";
			link.l1.go = "HouseWoman_1";
		break;
		case "HouseWoman_1":
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			npchar.dialog.currentnode = "HouseWoman";
		break;
	}
}