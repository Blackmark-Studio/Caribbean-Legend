// Хосе Диос - картограф
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
		case "First time":
			dialog.text = "Do you want something?";
			if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "dios")
			{
				link.l3 = TimeGreeting()+"! Tell me, are you Jose Dios, the cartographer?";
				link.l3.go = "island";
			}
			link.l1 = "No, nothing.";
			link.l1.go = "exit";	
			NextDiag.TempNode = "First time";
		break;
		
		case "island":
			dialog.text = "Yes, that's me. I don't know you, señor. What do you want from me?";
			link.l1 = "My name is "+GetFullName(pchar)+" and I was sent by Jan Svenson. Do you remember him?";
			link.l1.go = "island_1";
		break;
		
		case "island_1":
			dialog.text = "Ah, señor Svenson! Of course I remember him! Come, make yourself comfortable... How is the esteemed Jan doing?";
			link.l1 = "Thanks, he is doing fine. Señor Dios, I need your help. I want to consult with you about a matter which you must be familiar with due to your profession. Jan recommended you as a geography expert of the Caribbean region...";
			link.l1.go = "island_2";
		break;
		
		case "island_2":
			dialog.text = "I am listening, Señor. What do you want to know about the archipelago's geography?";
			link.l1 = "They say there is an island or some other kind of formation northwest of Havana, between Cuba and the Gulf of Mexico. This island has never been plotted on any map. I'd like to know how trustworthy these rumours are.";
			link.l1.go = "island_3";
		break;
		
		case "island_3":
			dialog.text = "Hm... You have asked about something that has been stirring within me for many years. This place you've mentioned has attracted the inquisitive minds of geographers for a long time, but nobody has ever been brave enough to explore that region.";
			link.l1 = "Why?";
			link.l1.go = "island_4";
		break;
		
		case "island_4":
			dialog.text = "The thing is, that place is some sort of natural anomaly. The probability of storms in that region is much higher than anywhere else. Perhaps the reason lies in the cold sea current, but that's just my hypothesis. Many ships have disappeared there, and that alone was enough to make sailors avoid the area; all the main sea routes pass far from that region anyway.";
			link.l1 = "I take it that you don't know the truth either...";
			link.l1.go = "island_5";
		break;
		
		case "island_5":
			dialog.text = "Exactly, Señor. But I have a couple of historical documents and some material evidence, so I have every right to suspect a high probability of that place's existence.";
			link.l1 = "Can you tell me more?";
			link.l1.go = "island_6";
		break;
		
		case "island_6":
			dialog.text = "Certainly. The most important evidence is a historical document containing extracts from the journal of Captain Alvarado, who visited the island in 1620. Quite an interesting story, I assure you!";
			link.l1 = "Captain Alvarado? This is the second time I've heard that name...";
			link.l1.go = "island_7";
		break;
		
		case "island_7":
			dialog.text = "I am not surprised. The story of Captain Alvarado has been part of folklore for years. It changed, became filled with rumours, lies and dreams, so here it is - the legend of the Island of the Abandoned Ships.\nGossip may change, but paper and ink do not; they remain intact for hundreds of years. Here, read this story - perhaps it will help you uncover what you are looking for.";
			link.l1 = "Thanks! Got anything else?";
			link.l1.go = "island_8";
		break;
		
		case "island_8":
			dialog.text = "There is a theory that the bottom of the sea in that area rises high enough to form a vast shoal. And I have already mentioned the current. There is also a large accumulation of seagulls and other sea birds, according to sailors' tales. Alvorado mentioned the names of vessels which were part of Admiral Francisco Betancourt's squadron, a squadron that was lost more than fifty years ago. I doubt that this is just a coincidence...";
			link.l1 = "I will return to my ship and read Alvarado's notes carefully. Thank you for your help, Señor Dios!";
			link.l1.go = "island_9";
		break;
		
		case "island_9":
			dialog.text = "You're welcome. Actually, I didn't help you at all; you haven't got the coordinates of the place, and neither have I. I can't even prove that there is an inhabited island out there. But as far as I understand, you intend to explore this area?\nIf so, then be aware that I will be truly grateful for any information, especially if it is supported by material proof. It seems that you are a wealthy man, but I will find a way to repay you.";
			link.l1 = "Good. Then we have a deal, Señor Dios. Perhaps my notes will be read by someone in the future too... And someone might even write a legend...";
			link.l1.go = "island_10";
		break;
		
		case "island_10":
			dialog.text = "Why not? Señor "+pchar.name+", I see that you are an adventurous man who travels a lot, so I would like to ask you to do something.";
			link.l1 = "Yes? I'm listening.";
			link.l1.go = "island_11";
		break;
		
		case "island_11":
			dialog.text = "You know that I am a cartographer. So, I have been drawing maps of the Caribbean archipelago for two years, compiling the admiral's atlas for the Viceroy's contest of Nueva Granada. But all of my twenty-four maps were stolen from my house in the most brazen way while I was captured by pirates, the very ones Señor Svenson saved me from.\nI am sure that the attack was organised by one of my competitors in order to acquire my maps. It has been a long time, but I have not seen a single map from my set since.";
			link.l1 = "I see. You want me to return your maps.";
			link.l1.go = "island_12";
		break;
		
		case "island_12":
			dialog.text = "Exactly. Perhaps you will find them during your future adventures. They are easy to recognise - my mark is on each and every one of them. I will generously reward you if you miraculously manage to collect all twenty-four maps.";
			link.l1 = "Fine. I will carefully examine every map I find in the archipelago from now on. Well, I have to go now. Thank you for the interesting conversation and for the document.";
			link.l1.go = "island_13";
		break;
		
		case "island_13":
			DialogExit();
			AddQuestRecordInfo("LSC_Alvorado", "1");
			AddQuestRecord("SharkHunt", "4");
			pchar.questTemp.Saga.SharkHunt = "LSC";
			NextDiag.CurrentNode = "Dios";
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
			pchar.questTemp.AdmiralMap = "true";
		break;
		
		case "Dios":
			dialog.text = "A-ah, it is you, señor "+GetFullName(pchar)+"? Got anything interesting to tell me?";
			if (CheckAttribute(pchar, "questTemp.AdmiralMap") && CountAdmiralMapFromCharacter() > 0 && CountAdmiralMapFromCharacter() < 24 && !CheckAttribute(npchar, "quest.mapinfo"))
			{
				link.l3 = TimeGreeting()+"! Señor Dios, please, take a look at the map I've found. It must be one of your maps according to the sign.";
				link.l3.go = "map_info";
			}
			if (CheckAttribute(pchar, "questTemp.AdmiralMap") && CountAdmiralMapFromCharacter() > 23)
			{
				link.l3 = TimeGreeting()+"! Señor Dios, I have good news for you. I was able to collect the complete set of your unique maps, just as you wanted. Here are all twenty-four maps.";
				link.l3.go = "amap";
			}
			if (CheckAttribute(pchar, "questTemp.LSC.Dios")) // был в LSC
			{
				link.l4 = TimeGreeting()+"! Yes, I have. I was at that mystical place we were talking about.";
				link.l4.go = "LSC";
			}
			link.l9 = "Nothing so far, Señor. Just wanted to see how you're doing.";
			link.l9.go = "exit";
			NextDiag.TempNode = "Dios";
		break;
		
		case "map_info":
			dialog.text = "Show me... (taking a look) Of course! This is one of my maps for the admiral's atlas! Captain, I must ask you to find all of them! I know it's almost impossible, but still... I don't want to lose hope.";
			link.l1 = "Don't lose it, Señor. I have found this map, so there is a chance that I will also find the rest. They are still in the Caribbean.";
			link.l1.go = "map_info_1";
		break;
		
		case "map_info_1":
			dialog.text = "Your optimism truly encourages me, Señor captain. Perhaps I will yet have the chance to show Don Juan de Cordova who the best cartographer in the archipelago is!";
			link.l1 = "You will be able to beat all your competing ill-wishers. The maps are truly wonderful... Farewell, Señor!";
			link.l1.go = "exit";
			npchar.quest.mapinfo = "true";
			NextDiag.TempNode = "Dios";
		break;
		
		case "amap":
			Achievment_Set("ach_CL_110");
			dialog.text = "I can't believe my eyes! Have you really found them? All of them?";
			link.l1 = "Yes. It wasn’t easy, but luck did smile on me in this endeavor. Take your cards — they are magnificent, each far superior to any I’ve seen before.";
			link.l1.go = "amap_1";
		break;
		
		case "amap_1":
			RemoveAllAdmiralMap()
			Log_Info("You have given the complete set of admiral's maps");
			PlaySound("interface\important_item.wav");
			dialog.text = "Incredible! This is just too incredible! To be honest, I never believed this moment would come.";
			link.l1 = "Dum spiro, spero, Señor Dios. You may face Don Cordova now. I am sure he will value your talents highly.";
			link.l1.go = "amap_2";
		break;
		
		case "amap_2":
			dialog.text = "You have my thanks, Captain! You don't even realise what a great service you have done for me. And as I promised - I will reward you. I also have a gift for you. I think that as a sailor you will find it very useful.";
			link.l1 = "You have intrigued me, Señor!";
			link.l1.go = "amap_3";
		break;
		
		case "amap_3":
			GiveItem2Character(pchar, "spyglass5"); 
			Log_Info("You have received a ship telescope");
			PlaySound("interface\important_item.wav");
			dialog.text = "Here! This is a ship's telescope of my own design. It is unique, and you won't find another like it anywhere else. The lenses were made in Europe by the most skilled master in Spain. Its case was crafted by a friendly gunsmith. A special tripod will help you aim the device regardless of any rolling. You can see everything you need, whether it's a ship or a fort.";
			link.l1 = "Such a wonderful gift! Thank you, Señor Dios.";
			link.l1.go = "amap_4";
		break;
		
		case "amap_4":
			dialog.text = "Use it, Señor captain. I hope that my telescope will serve you well.";
			link.l1 = "No doubt! I am looking forward to mounting it on the deck of my ship and looking through it.";
			link.l1.go = "amapcopy_01";
		break;
		
		case "amapcopy_01":
			AddCharacterExpToSkill(pchar, "Fortune", 1000);//везение
			AddCharacterExpToSkill(pchar, "Leadership", 1000); // харизма
			AddCharacterExpToSkill(pchar, "Sneak", 300);//скрытность (раз телескоп дали)
			ChangeCharacterComplexReputation(pchar, "nobility", 10);// репутация-известность
			ChangeCharacterComplexReputation(pchar, "authority", 5);// репутация-авторитет
			ChangeCharacterNationReputation(pchar, SPAIN, 20);
			ChangeOfficersLoyality("good_all", 5);
			DeleteAttribute(pchar, "questTemp.AdmiralMap");
			dialog.text = "Besides, since things have turned out this way, I have another small proposition for you.";
			link.l1 = "What is it? I’m listening very carefully.";
			link.l1.go = "best_map";
		break;
		
		case "best_map":
			dialog.text = "It occurred to me that these maps are excellent for an explorer, but they don’t provide everything a sea captain needs. Just think: all the bays, capes, and lagoons are drawn with great precision, but you can’t chart a course between islands using them.";
			link.l1 = "That's true, you can't navigate with them.";
			link.l1.go = "best_map_01";
		break;
		
		case "best_map_01":
			dialog.text = "But I can also make an archipelago map for you! And not the kind you can buy from the Dutch West India Company, but a unique, excellent map.";
			link.l1 = "Thank you, señor Dios, but I don't need such a map. Still, thank you very much for the offer!";
			link.l1.go = "best_map_02";
			link.l2 = "Are you kidding?! Señor Dios, how could I possibly refuse? Just tell me what you require - I won't spare any money or tools!";
			link.l2.go = "best_map_04";
		break;
		
		case "best_map_02":
			dialog.text = "Well, I had to offer. In any case, it was a pleasure doing business with you, señor "+pchar.lastname+"!";
			link.l1 = "Likewise! Good luck to you!";
			link.l1.go = "best_map_03";
		break;
		
		case "best_map_03":
			DeleteAttribute(pchar, "questTemp.AdmiralMapCopy");
			DialogExit();
			NextDiag.CurrentNode = "Dios";
		break;
		
		case "best_map_04":
			dialog.text = "I already have the instruments, thank you. I’ll need a standard map of the archipelago, as well as a compass and a rated chronometer — the map must be precise, otherwise it would be sabotage. And as payment — one chest of doubloons.";
			if(CheckAMapItems())
			{
				link.l1 = "I already have everything you mentioned with me. Here, take it.";
				link.l1.go = "best_map_07";
			}
			link.l2 = "A standard map of the archipelago, a compass, a rated chronometer, and one chest of doubloons. Got it! I’ll deliver them as soon as I can — wait for me!";
			link.l2.go = "best_map_07e";
		break;
		
		case "best_map_07e":
			DialogExit();
			NextDiag.CurrentNode = "best_map_waititems";
		break;
		
		case "best_map_waititems":
			dialog.text = "Greetings, my dear friend! Have you brought the standard map of the archipelago, the compass, the rated chronometer, and the chest of doubloons?";
			link.l1 = "Not yet, Señor Dios. But I will, I promise!";
			link.l1.go = "best_map_07e";
			if(CheckAMapItems())
			{
				link.l2 = "Yes, Señor Dios. Here, everything’s right here — take it.";
				link.l2.go = "best_map_07";
			}
		break;
		
		case "best_map_07":
		    Log_Info("You handed over a regular map of the archipelago, a boussole, a tariffed chronometer, and a chest with doubloons.");
			TakeNItems(pchar,"chest", -1);
			TakeNItems(pchar,"map_normal", -1);
			TakeNItems(pchar,"bussol", -1);
			TakeNItems(pchar,"clock2", -1);
			dialog.text = "Well, then I'll get to work. Come back to me in a week, and I promise you won't regret it!";
			link.l1 = "I have no doubt, Señor. See you in a week!";
			link.l1.go = "best_map_08";
		break;
		
		case "best_map_08":
			SetTimerFunction("AdmAtlas_comlete", 0, 0, 7);
			NextDiag.CurrentNode = "best_map_wait";
			pchar.questTemp.AdmiralAtlas = true;
			DialogExit();
		break;
		
		case "best_map_wait":
			if(CheckAttribute(pchar,"questTemp.AdmiralAtlas") && pchar.questTemp.AdmiralAtlas == "complete")
			{
				dialog.text = "Ah, Señor "+pchar.lastname+", there you are! I'm pleased to inform you that I’ve finished the map of the archipelago! And I dare say, it’s far superior to the one you provided me.";
				link.l1 = "My friend... This map is astonishing! I daresay, it’s a masterpiece! How can I ever thank you for all you've done for me?";
				link.l1.go = "best_map_09";
			}
			else
			{
				dialog.text = "Greetings, Señor! I must apologise, but the map is not ready yet.";
				link.l1 = "Yes, I remember that you needed a week. I just came to check on you.";
				link.l1.go = "best_map_wait_01";
			}
		break;
		
		case "best_map_wait_01":
			NextDiag.CurrentNode = "best_map_wait";
			DialogExit();
		break;
		
		case "best_map_09":
			dialog.text = "Oh, come now, my friend. It was a pleasure to create such a map for a noble captain who can truly appreciate it. Ah, and here is your original chart back as well. May the seas be kind to you!";
			link.l1 = "Thank you so much! You're right — this map is truly priceless to me. Farewell, Señor Dios!";
			link.l1.go = "best_map_10";
		break;
		
		case "best_map_10":
			TakeNItems(pchar,"Map_Best", 1);
			TakeNItems(pchar,"map_normal", 1);
			Log_Info("You received an excellent archipelago map!");
			PlaySound("interface\important_item.wav");
			NextDiag.CurrentNode = "Dios";
			DialogExit();
		break;
		
		case "LSC":
			dialog.text = "Really?! Have you found it? Make yourself comfortable, I think the coming conversation will take a while, am I right?";
			link.l1 = "I really have a lot to tell you about the island. But first, I want you to promise me something. I can see that you are a man of honour, so I am sure that you will keep your word...";
			link.l1.go = "LSC_1";
		break;
		
		case "LSC_1":
			dialog.text = "What are you talking about, Captain?";
			link.l1 = "There are people living there... and they won't be happy if someone meddles in their lives. I don't think that the possible arrival of a 'research' squadron will be welcomed.";
			link.l1.go = "LSC_1_1";
		break;
		
		case "LSC_1_1":
			dialog.text = "";
			link.l1 = "So I want you to give me your word of honour that you won't publish any information which could be used to find the Island within ten years after our conversation. You are welcome to publish any information about the locals, their lives and so on, just don't reveal the location of the island.";
			link.l1.go = "LSC_2";
		break;
		
		case "LSC_2":
			dialog.text = "I agree, Captain. I give you my word as a nobleman that I won't tell anyone either the location of the Island or any information that could harm its inhabitants within the next ten years.";
			link.l1 = "Listen to my story then. Write it down if you like. So, the Island is made up of many wrecked ships whose hulls are lying on a wide shoal...";
			link.l1.go = "LSC_3";
		break;
		
		case "LSC_3":
			DialogExit();
			SetLaunchFrameFormParam("Two hours later...", "LSC_FinalDiosStory", 0, 5);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 2, 10); //крутим время
			RecalculateJumpTable();
		break;
		
		case "LSC_4":
			dialog.text = "Incredible! You have given me very valuable information, Captain! The offspring of Admiral de Betancourt are living on the island! Now we know what happened to his squadron. And there is one less blank spot on the map of the Caribbean archipelago now... Thank you very much for your story, "+pchar.name+"!";
			link.l1 = "Now do you see why I asked you to be so careful when retelling my information?";
			link.l1.go = "LSC_5";
		break;
		
		case "LSC_5":
			dialog.text = "I see. You can be sure that I will keep my word. Tell me... do you have any material possessions from the Island?";
			if (CheckCharacterItem(pchar, "LSC_navigation_map"))
			{
				link.l1 = "I have sailing directions to the Island of Abandoned Ships. Here, take a look. They allow you to navigate a small ship through the reefs and debris and safely land on the Island. It is impossible to reach the Island without these directions.";
				link.l1.go = "LSC_6";
			}
			else
			{
				link.l1 = "Unfortunately, I don't have any.";
				link.l1.go = "LSC_7_1";
			}
		break;
		
		case "LSC_6":
			Log_Info("You have given sailing directions");
			PlaySound("interface\important_item.wav");
			dialog.text = "(looking) Such an excellent document! It was drawn by a man skilled in cartography. Even I couldn't have done it better. Incredible! Captain, why don't you give me these sailing directions? A story is a story, but this paper must be shown to the most famous geographers in the Old World!";
			link.l1 = "Señor Dios, unfortunately, I need this document for myself. As I have said before, it is impossible to pass through the reefs surrounding the island without it. But you can make a copy of the directions if you wish, and I shall be only too glad if you also have them in your possession.";
			link.l1.go = "LSC_10";
			//link.l2 = "Señor Dios, unfortunately, I need this item for myself. As I have said, it is impossible to bypass the reefs around the island without it. I'd sacrifice it in the name of science, but... I am sure you understand.";
			//link.l2.go = "LSC_7";
		break;
		
		case "LSC_7":
			Log_Info("You received sailing directions");
			PlaySound("interface\important_item.wav");
			dialog.text = "Absolutely. It is your right, though it's a pity... Anyway, thank you for your story! You have done a great service for geographers, cartographers, and other curious people.";
			link.l1 = "You're welcome, Señor. Well, I have to go now. Farewell.";
			link.l1.go = "LSC_8";
		break;
		
		case "LSC_7_1":
			dialog.text = "What a pity... Anyway, thank you for your story! You have done a great service for geographers, cartographers, and other curious people.";
			link.l1 = "You're welcome, Señor. Well, I have to go now. Farewell.";
			link.l1.go = "LSC_8";
		break;
		
		case "LSC_8":
			dialog.text = "Sure, "+pchar.name+". You have spared a lot of your time for me. Send my regards to Señor Svenson!";
			link.l1 = "Goodbye, Señor Dios.";
			link.l1.go = "LSC_9";
		break;
		
		case "LSC_9":
			DialogExit();
			NextDiag.CurrentNode = "Dios";
			AddCharacterExpToSkill(pchar, "Fortune", 400);//везение
			AddCharacterExpToSkill(pchar, "Leadership", 500); // харизма
			ChangeCharacterComplexReputation(pchar, "nobility", 5);// репутация-известность
			ChangeCharacterComplexReputation(pchar, "authority", 2);// репутация-авторитет
			ChangeCharacterComplexReputation(pchar, "fame", 3);
			ChangeCharacterNationReputation(pchar, SPAIN, 5);
			DeleteAttribute(pchar, "questTemp.LSC.Dios");
			LAi_SetOwnerType(npchar);
		break;
		
		case "LSC_10":
			Log_Info("You received sailing directions");
			PlaySound("interface\important_item.wav");
			dialog.text = "Thank you so much! That is very kind of you. Give me a moment...";
			link.l1 = "...";
			link.l1.go = "LSC_11";
		break;
		
		case "LSC_11":
			DialogExit();
			SetLaunchFrameFormParam("Two hours later", "", 0.1, 3.0);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 2, 0);
			npchar.dialog.currentnode = "LSC_12";
			LAi_SetActorType(npchar);
			LAi_ActorDialogDelay(npchar, pchar, "", 4.0);
		break;
		
		case "LSC_12":
			//RemoveItems(pchar, "LSC_navigation_map", 1);
			dialog.text = "Thank you very much! That was very kind of you. Now we have not only oral evidence but also material proof... I won't leave you unrewarded, Captain. I have a small gift for you.";
			link.l1 = "What kind of gift?";
			link.l1.go = "LSC_13";
		break;
		
		case "LSC_13":
			sld = characterFromId("Pirates_shipyarder");
			sld.quest.sextant = "true"; // атрибут Алексу на хронометр
			GiveItem2Character(pchar, "sextant1"); 
			PlaySound("interface\important_item.wav");
			dialog.text = "I am fond not only of cartography and geography, but also of mathematics and astronomy. It took me a year of attempts to create a universal tool for determining latitude and longitude. And I've made some progress. Here, take a look:\nThis is my sextant. I designed it myself. The problem is, it doesn't work. It requires an extremely accurate chronometer. Even those made by the best craftsmen produce unacceptable errors over time. Therefore, my tool is worthless for now.\nBut since you travel a lot, perhaps you will find a chronometer accurate enough for the sextant to work. Once you find such a clock, you won't need a Boussole, a compass, an astrolabe, sandglasses, or any other unreliable chronometers—my tool will replace them all.";
			link.l1 = "Thank you, Señor Dios. Let's hope that I will find a chronometer which will make your invention work. I'd like to have such a device... in working condition. Well, I have to go now. Farewell.";
			link.l1.go = "LSC_8";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//--> блок реагирования на попытку залезть в сундук
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("You're "+GetSexPhrase("a thief, I see! Guards, seize him","a thief, I see! Guards, seize her")+"!!!","I can't believe it! I turned away for a second – and you're rifling through my belongings! Stop, thief!!!","Guards! Robbery! Stop the thief!!!");
			link.l1 = "Aaaah, devil!!!";
			link.l1.go = "fight";
		break;
		
		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		//<-- блок реагирования на попытку залезть в сундук
	}
}

bool CheckAMapItems()
{
	return GetCharacterItem(pchar,"chest")      && 
		   GetCharacterItem(pchar,"map_normal") &&
		   GetCharacterFreeItem(pchar,"bussol") &&
		   GetCharacterFreeItem(pchar,"clock2");
}