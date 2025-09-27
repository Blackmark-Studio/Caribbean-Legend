// Addon-2016 Jason, французские миниквесты (ФМК) Порт-о-Пренс
void ProcessDialogEvent()
{
	ref sld, NPChar;
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
			dialog.text = "An obvious bug. Tell the devs about it.";
			link.l1 = "Oh, I will.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "officer":
			PlaySound("Voice\English\z_arest_02.wav");
			dialog.text = "What the devil is going on here, gentlemen? I heard fighting.";
			link.l1 = "Hello officer, I heard a woman screaming and...";
			link.l1.go = "officer_1";
		break;
		
		case "officer_1":
			DialogExit();
			sld = CharacterFromID("FMQP_noble");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "officer_2":
			dialog.text = "";
			link.l1 = ""+GetFullName(pchar)+". Captain "+GetFullName(pchar)+".";
			link.l1.go = "officer_3";
		break;
		
		case "officer_3":
			dialog.text = "You are free to go for now, captain. I can see what happened here; we will summon you if we have any questions.";
			link.l1 = "Very well...";
			link.l1.go = "officer_4";
		break;
		
		case "officer_4":
			DialogExit();
			sld = CharacterFromID("FMQP_noble");
			sld.Dialog.currentnode = "noble_3";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "officer_5":
			PlaySound("Voice\English\z_arest_02.wav");
			dialog.text = "What the devil is going on here, gentlemen? I heard fighting.";
			link.l1 = "Phew... Officer, I’m here at the request of the tavern maid — she claimed someone was being killed here, and it turned out to be true — those two scoundrels attacked this noble gentleman. Sadly, I couldn’t save him. The bastards finished him off.";
			link.l1.go = "officer_6";
		break;
		
		case "officer_6":
			dialog.text = "Damn my eyes... He's a Spaniard! Why would he be here? Hm. And who are you, then, "+GetAddress_Form(NPChar)+"?";
			link.l1 = ""+GetFullName(pchar)+". Captain "+GetFullName(pchar)+".";
			link.l1.go = "officer_7";
		break;
		
		case "officer_7":
			dialog.text = "Captain, you are free to go for now. Your words match the witness's. We will call you if need be.";
			link.l1 = "Very well...";
			link.l1.go = "officer_8";
		break;
		
		case "officer_8":
			DialogExit();
			DoQuestReloadToLocation("Portpax_town", "reload", "reload4", "");
		break;
		
		case "noble":
			dialog.text = "Let me explain everything, officer! I, Don Domingo Ortiz Albalate from Santo Domingo, came to Port-au-Prince at the invitation of a young lady. While waiting for our meeting, I stayed at the tavern. But no more than two hours passed before dos canallas malditas burst into my room, and if it weren't for the timely help of "+GetSexPhrase("this good señor who appeared","this beautiful señorita who appeared")+", I would have been in serious trouble.";
			link.l1 = "Don Domingo Ortiz Albalate? Are you Spanish?";
			link.l1.go = "noble_1";
		break;
		
		case "noble_1":
			dialog.text = "As Spanish as Rey Felipe himself, ha! I would also like to point out that my papers are in buen orden. I am a noble de España, not some pirata sucia!";
			link.l1 = "Don Domingo, our sincerest apologies for this unfortunate incident! Please come with us for a few questions and a bottle of wine at the garrison. We'll take care of everything. As for you...";
			link.l1.go = "noble_2";
		break;
		
		case "noble_2":
			DialogExit();
			sld = CharacterFromID("FMQP_off");
			sld.Dialog.currentnode = "officer_2";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "noble_3":
			PlaySound("Voice\English\LE\Domingo\Domingo_01.wav");
			dialog.text = ""+UpperFirst(GetAddress_Form(NPChar))+" Capitán! "+UpperFirst(GetAddress_Form(NPChar))+" Capitán! I swear by Santiago and the Blessed Virgin, you are a noble man, and a true son of Castile always rewards such nobility! I'd like to see you rewarded later, when I have finished my business here. Please, honour me with a visit to my humble house in Santo Domingo! It's close to the city gates. I will lay out a feast for you, "+GetSexPhrase("my buen amigo","mi salvadora")+"! Remember my name, it's Don Domingo Ortiz Albalate!";
			link.l1 = "...";
			link.l1.go = "noble_4";
		break;
		
		case "noble_4":
			DialogExit();
			AddMapQuestMarkCity("santodomingo", true);
			DoQuestReloadToLocation("Portpax_town", "reload", "reload4", "FMQP_AfterFightInTown");
		break;
		
		case "noble_5":
			dialog.text = "Captain "+pchar.lastname+"?! Oh Madre de Dios! What a disaster! This is a massacre! What happened here, "+GetSexPhrase("mi buen amigo","mi salvadora")+"? Who are these men?";
			link.l1 = "Glad to see you, Don Domingo. These are... I came here to pay you a visit. See that guy over there? That's Ugo, your servant, and he...";
			link.l1.go = "noble_6";
		break;
		
		case "noble_6":
			dialog.text = "Ugo?! Oh no, you were tricked, capitán!";
			link.l1 = "I get it, seems to happen to me a lot. Three scoundrels broke into your home, murdered your loyal man Ugo – I found his corpse upstairs already – and then set up an ambush for you. My arrival wasn't part of their plan. They didn't survive our meeting.";
			link.l1.go = "noble_7";
		break;
		
		case "noble_7":
			dialog.text = "Santa Maria, ora pro nobis! You wield your sword like the fencing masters of Toledo! It's good that you are on my side! Oh, my poor Ugo! He raised me since I was a child and now... to be murdered by malditas canallas!";
			link.l1 = "Don Domingo, it looks like you aren't out of danger. Your man Ugo knew something, read this note. I found it on a table.";
			link.l1.go = "noble_8";
		break;
		
		case "noble_8":
			ChangeItemDescribe("letter_parol", "itmdescr_letter_parol");
			RemoveItems(pchar, "letter_parol", 1);
			dialog.text = "Give me it... (reading) That cannot be... oh, no! This is unbelievable! Tio Luis... But...";
			link.l1 = "Any hint as to who did this?";
			link.l1.go = "noble_9";
		break;
		
		case "noble_9":
			dialog.text = "Only suspicions... dreadful suspicions, "+GetSexPhrase("mi buen amigo","mi salvadora")+"! How could my mother's brother do such a thing?";
			link.l1 = "Would you mind filling me in? I am sorry, Don Domingo, but in my experience, relatives are often the worst enemies a man can have...";
			link.l1.go = "noble_10";
		break;
		
		case "noble_10":
			dialog.text = "Sí, you are correct, "+GetAddress_Form(NPChar)+"! I will tell you everything! You have saved me twice already and it seems that you are the only man I can trust right now! But let's leave this awful place, it makes me sick. I must notify the alcalde about this mess, they will take care of poor Ugo. How about we have some wine in the local taberna to calm our nerves?";
			link.l1 = "Your nerves certainly need it more than mine, lead the way, señor!";
			link.l1.go = "noble_11";
		break;
		
		case "noble_11":
			DialogExit();
			chrDisableReloadToLocation = false;
			DoQuestReloadToLocation("Santodomingo_tavern", "sit", "sit_base2", "FMQP_InSantoDomingoTavern");
		break;
		
		case "noble_12":
			LAi_SetSitType(pchar);
			dialog.text = "So, my friend, allow me to tell you an...abridged version of my family history. My mother, Doña Isabella Ortiz, married my father, el Marqués Ricardo Albalate, and took his family name according to custom. Her brother, Luis Ortiz, was a garrison commander in the colonies, but after my mother's marriage he was appointed by my father to be manager of a sugar plantation not far from Portobello\nThis was a vast and wealthy plantation, very profitable indeed. After the tragic death of my parents at sea a few years ago, I, as their only son, inherited everything, including the plantation. My uncle has kept his position and I was content enough with the rent he paid me. He was always on time with his payments.";
			link.l1 = "So you think your uncle...";
			link.l1.go = "noble_13";
		break;
		
		case "noble_13":
			dialog.text = "Yes. At present, he is nothing but a tenant. I own the plantation, not him. But! If anything happens to me - it will become his property.";
			link.l1 = "You know, Domingo, I knew men who would murder all their relatives in cold blood for a prize much less tempting than that.";
			link.l1.go = "noble_14";
		break;
		
		case "noble_14":
			dialog.text = "You clearly need to keep better company, Carlos. My dear Ugo mentioned my uncle's papers in his last note... This is a direct clue. Oh, I don't want to believe this! But... my cousin, Margarita Ortiz, who lives in Spain, was betrothed not long ago. Might that be the cause, "+GetAddress_Form(NPChar)+" captain?";
			link.l1 = "Your doting uncle might suddenly need some money...";
			link.l1.go = "noble_15";
		break;
		
		case "noble_15":
			dialog.text = "Money?! But of course... but don't forget the title of marquis! That would make my cousin a proper match for her future husband! Jesu Christo! How stupid I was!";
			link.l1 = "That title of nobility is worth more than the sugar plantation.";
			link.l1.go = "noble_16";
		break;
		
		case "noble_16":
			dialog.text = "Wait a minute! I just remembered that this wasn't the first attempt on my life! I had an encounter with a beggar in the street a few weeks ago! The drunken canalla offended me in a manner I couldn't ignore. He turned out to be a damn good fencer; he drew steel and even managed to wound me with a rapier before I killed him.";
			link.l1 = "And how the hell did you end up in a tavern at Port-au-Prince? You mentioned some young señorita?";
			link.l1.go = "noble_17";
		break;
		
		case "noble_17":
			dialog.text = "(turning red) Sir... Yes, captain, there was a young and pretty señorita at the scene... now I see she was just the bait for the trap. Bastards, bastards everywhere, can't trust anyone! Poor Ugo... he's dead now.";
			link.l1 = "You should do something about it, Domingo. How about fleeing to Spain?";
			link.l1.go = "noble_18";
		break;
		
		case "noble_18":
			dialog.text = "To Spain? And leave my plantation to that scoundrel? Capitan, I am Marquis Domingo Ortiz Albalate!";
			link.l1 = "But...";
			link.l1.go = "noble_19";
		break;
		
		case "noble_19":
			dialog.text = ""+UpperFirst(GetAddress_Form(NPChar))+", may I ask for your help? With Ugo dead, I have no one by my side I can trust. You've saved me twice already! Twice! I owe you a great deal, I am forever in your debt, and yet I dare ask you for another favour. I swear by the Blessed Mother, I will make it worth your while!";
			if (startHeroType == 2)  
			{
				link.l1 = "How may I be of service to you, "+npchar.name+"?";
				link.l1.go = "noble_20";
			}
			else
			{
				link.l1 = "Very well, you are a good man for a Spaniard. What can I do for you, Domingo?";
				link.l1.go = "noble_20";
			}
			
		break;
		
		case "noble_20":
			dialog.text = "Let's go to my plantation in Portobello! I know that my uncle is in Cartagena at the moment. Ugo mentioned some papers, so let's check Don Luis Ortiz's books and documents! We might find something that will help us drag his foul conspiracy out into the open. It's quite a distance to Portobello but I'll pay you in full for the voyage!";
			link.l1 = "It would be absurd to reject you at this point, Don Domingo. I'm in too deep to back out now.";
			link.l1.go = "noble_21";
		break;
		
		case "noble_21":
			AddMoneyToCharacter(pchar, 20000);
			dialog.text = "Gracias a Dios, I knew you would help me out, amigo! Here, take these twenty thousand pesos as payment for the voyage to Portobello. When do we set sail? We must hurry before my uncle returns from Cartagena!";
			link.l1 = "Let's waste no time then.";
			if (startHeroType != 2 && CheckCharacterItem(pchar, "HolTradeLicence") && GetDaysContinueNationLicence(HOLLAND) >= 20 && GetNationRelation2MainCharacter(SPAIN) == RELATION_NEUTRAL) {link.l1.go = "noble_22";}
			else {link.l1.go = "noble_22x";}
		break;
		
		case "noble_22x":
			GiveNationLicence(HOLLAND, 20);
			dialog.text = "Here's a Dutch West India Company license. It has a twenty-day expiration, let's just put your name in it. Done. This should help us avoid any trouble with the Costa Garda.";
			link.l1 = "Excelente!";
			link.l1.go = "noble_22";
		break;
		
		case "noble_22":
			dialog.text = "Am I now allowed to come aboard your ship, captain?";
			link.l1 = "Consider yourself an honoured guest. As soon as we get the right wind - we set sail.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQP_OnBoard");
			AddMapQuestMarkCity("portobello", true);
		break;
		
		case "noble_23":
			dialog.text = "So, Captain Carlos, here we are. Now we should find my uncle's house and see what's inside.";
			link.l1 = "Don Domingo, should we expect any trouble with the guard?";
			link.l1.go = "noble_24";
		break;
		
		case "noble_24":
			dialog.text = "No. Although... hm. There is a chance that Luis has turned them against me. At any rate, discretion is always the better part of valour. Let's find the house we need.";
			link.l1 = "Don't you know it already? It's your plantation.";
			link.l1.go = "noble_25";
		break;
		
		case "noble_25":
			dialog.text = "Hm... To be completely honest, the last time I was here, I was only eight years old. Still, I intend to fix that as soon as possible!";
			link.l1 = "I see. Then let's start looking. Your uncle's house must be the biggest one here.";
			link.l1.go = "noble_26";
		break;
		
		case "noble_26":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			AddQuestRecord("FMQ_Portpax", "7");
		break;
		
		case "noble_27":
			dialog.text = "What do you have here, "+GetAddress_Form(NPChar)+"?";
			link.l1 = "Take a look, Don Domingo. Looks like accounting records. This might be interesting.";
			link.l1.go = "noble_28";
		break;
		
		case "noble_28":
			ChangeItemDescribe("Almanac", "itmdescr_Almanac");
			RemoveItems(pchar, "Almanac", 1);
			dialog.text = "(reading) Hm... Yes. Look at this... Ay caramba! One hundred thousand pesos! And another one hundred and fifty thousand! And here... (turning over pages) Uncle Luis!";
			link.l1 = "Anything of interest?";
			link.l1.go = "noble_29";
		break;
		
		case "noble_29":
			dialog.text = "Anything of interest! My dear uncle had an income five times greater than he told me! Thief! Embezzler!";
			link.l1 = "Can't say I'm surprised. You can't put complete trust in anyone without checking the actual state of affairs from time to time. That's just common sense.";
			link.l1.go = "noble_30";
		break;
		
		case "noble_30":
			dialog.text = "Common sense to common men, perhaps. My upbringing has blinded me to such deception in gentlemen I thought honorable! You are right as always, Carlos! My own uncle is stealing from me! Mierda! This is my fault, but I will fix this. I own this plantation and my uncle has been relieved of duty as of today! He is no one! I will see him keelhauled!";
			link.l1 = "Don Domingo... Don't you think your uncle might object to such a decision?";
			link.l1.go = "noble_31";
		break;
		
		case "noble_31":
			dialog.text = "I don't give a damn whether he agrees or not! I am Marqués Domingo Ortiz Albalate and Luis Ortiz is nothing but a tenant, and a former tenant at that! And he...";
			link.l1 = "Calm yourself, señor. You are an unfamiliar face here and I'm a Frenchman sailing under a Dutch license with a... checkered past with the Spanish counter-piracy patrols. As for your uncle, he practically owns this town. Think of the guards and the local governor. Do you really think they will take your side?";
			link.l1.go = "noble_32";
		break;
		
		case "noble_32":
			dialog.text = "You strike the point with a rapier... Maybe... No. Spanish soldiers would never dare to lay a hand on a nobleman! My uncle can challenge me if he dares!";
			link.l1 = "Still, I suggest taking another path. How about the court of law?";
			link.l1.go = "noble_33";
		break;
		
		case "noble_33":
			dialog.text = "Ha! You are right, Carlos. Let us go speak to the proper authorities. My uncle made a mistake by writing down exact details in his notes about his dealings with smugglers. He bought slaves from them very cheaply. These books will do us a great service. I doubt that the bastard will be able to harm me in any way while sitting in the dungeons. Let's go! To Portobello!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQP_PrepareUncle");
		break;
		
		case "noble_34":
			//PlaySound("Voice\English\LE\Domingo\Domingo_04.wav");
			dialog.text = "This is nothing but a filthy and insolent lie! How dare he sully the good name of my parents with his unworthy tongue! Damn him, I will make him pay for this! Draw your sword, you assassin!";
			link.l1 = "";
			link.l1.go = "noble_35";
		break;
		
		case "noble_35":
			DialogExit();
			sld = CharacterFromID("FMQP_Uncle");
			sld.Dialog.currentnode = "uncle_3";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "noble_36":
			PlaySound("Voice\English\LE\Domingo\Domingo_05.wav");
			dialog.text = "Uncle Luis is in the proper place reserved for his soul - in hell... "+pchar.name+", you were sent to me by my guardian angel! I am glad you didn't trust the word of this scoundrel. To be honest, I feared that you would just leave me here alone to fight this canalla\nYes "+GetAddress_Form(NPChar)+", I am not perfect myself but this... this filthy lie about me hiring pirates to murder my own parents! To blame me for this... this! Bah! A well-deserved fate.";
			link.l1 = "Glad we made it, Don Domingo. What now? I hope we haven't run afoul of Spanish law.";
			link.l1.go = "noble_37";
		break;
		
		case "noble_37":
			dialog.text = "With the law? Ha-ha! No, "+pchar.name+", I will show this fine accounting book with all my uncle's smuggling operations in it. Do not forget about the several attempts on my life; we've got a great number of witnesses after his last try just now. Don't worry about it, "+GetAddress_Form(NPChar)+". This is my town, it's time to show them all!";
			link.l1 = "Please move cautiously, señor. Let them think better of you than they had thought about your late uncle.";
			link.l1.go = "noble_38";
		break;
		
		case "noble_38":
			dialog.text = "That's the plan, capitán. But I will show no mercy to anyone who dares to oppose me. Let me express my sincere gratitude to you, "+pchar.name+"! Please, go to the taberna, take a rest, have a cup or two. I'd be glad to join you, but you were right. It's time to grow wiser and take control of the plantation myself. Come see me here tomorrow, capitán!";
			link.l1 = "Very well, Don Domingo. See you tomorrow.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQP_PlantatonPause");
		break;
		
		case "noble_39":
			DelLandQuestMark(npchar);
			PlaySound("VOICE\English\LE\Domingo\Domingo_05.wav");
			dialog.text = "Ah, here you are, "+GetAddress_Form(NPChar)+"!";
			link.l1 = "How are you doing, don Domingo? How is your plantation?";
			link.l1.go = "noble_40";
		break;
		
		case "noble_40":
			dialog.text = "The plantation's great, can't say the same about the money – turns out my dear uncle had been transferring all the funds to the bank in Cartagena. It will take a lot of lawyers' time to get my gold back. But it's alright, I can manage that. Don't be sad, captain, I will keep my promises to reward you for your nobility, honesty, and friendship!";
			link.l1 = "Never had a thought about a reward when I was fighting on your side, señor...";
			link.l1.go = "noble_41";
		break;
		
		case "noble_41":
			dialog.text = "I know that, captain, and that says a lot about your character! Any good deed must be rewarded. So, although I don't have any money at the moment, I will give orders to load your vessel with goods from my plantation. I mean coffee, a great batch of it. You will be able to sell it for a great profit, I am sure.";
			link.l1 = "Oh! This is nice...";
			link.l1.go = "noble_42";
		break;
		
		case "noble_42":
			dialog.text = "Moreover, I have a few items of little value to me, but of great value to any sailor like yourself. A fine spyglass and three amulets. Please accept these, they're all yours now.";
			link.l1 = "Gratitude!";
			link.l1.go = "noble_43";
		break;
		
		case "noble_43":
			Log_Info("You have received a good spyglass");
			Log_Info("You have received three amulets");
			PlaySound("interface\important_item.wav");
			dialog.text = "Finally, I present you with my rapier as a token of my immeasurable gratitude. She served me well; now let her serve you even better. Look at her and remember your good Spanish friend - marquis Domingo Albalate!";
			link.l1 = "Thank you so much, señor! I didn't expect...";
			link.l1.go = "noble_44";
		break;
		
		case "noble_44":
			Log_Info("You have received the Smallsword");
			PlaySound("interface\important_item.wav");
			RemoveCharacterEquip(npchar, BLADE_ITEM_TYPE);
			dialog.text = "And now, alas, I must bid my farewells. I should go to Portobello to see the governor and then to Cartagena... To sum up, my carefree existence is over, time to live as a grown man.";
			link.l1 = "Well, you are much smarter now...";
			link.l1.go = "noble_45";
		break;
		
		case "noble_45":
			dialog.text = "That's true. It was a pleasure, "+GetAddress_Form(NPChar)+"! Come visit me sometime. Godspeed at sea!";
			link.l1 = "Same to you in your plantation business, don Domingo!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQP_ReceiveReward");
		break;
		
		case "noble_46":
			PlaySound("Voice\English\YoungMan02.wav");
			dialog.text = "Eh, we are late, señor! What a pity, my good old uncle has already done a thorough job cleaning out his papers. Looks like someone told him about Santo Domingo and he took precautions... But I am not going to leave it at that! I should see the governor of Portobello to initiate legal proceedings against my uncle. I have had enough of him managing my wealth.";
			link.l1 = "Good decision.";
			link.l1.go = "noble_47";
		break;
		
		case "noble_47":
			dialog.text = "I want to thank you, captain! It was a pleasure! I present you my rapier as a token of my gratitude. She served me well; now let her serve you even better. Look at her and remember your good Spanish friend – marquis Domingo Albalate!";
			link.l1 = "Thank you so much, señor! I didn't expect...";
			link.l1.go = "noble_48";
		break;
		
		case "noble_48":
			Log_Info("You have received the Smallsword");
			PlaySound("interface\important_item.wav");
			RemoveCharacterEquip(npchar, BLADE_ITEM_TYPE);
			GiveItem2Character(pchar, GetGeneratedItem("blade_16")); // belamour legendary edition используем GetGeneratedItem иначе пачка одинаковых клинков из первой части массива
			dialog.text = "And now, alas, I must bid you farewell. I should go to Portobello. My carefree days are over, time to live as a grown man. Godspeed at sea!";
			link.l1 = "Good luck with your uncle, don Domingo! I am sure you will prevail!";
			link.l1.go = "noble_49";
		break;
		
		case "noble_49":
			DialogExit();
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("PortoBello_Plantation", "reload2_back", false);
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 40.0);
			pchar.questTemp.FMQP = "fail";
			AddQuestRecord("FMQ_Portpax", "13");
			CloseQuestHeader("FMQ_Portpax");
			sld = &Locations[FindLocation("PortoBello_Plantation")];
			sld.soldiers = true;
		break;
		
		case "uncle":
			PlaySound("Voice\English\OliverTrast02.wav");
			if (pchar.sex == "woman") { dialog.text = "Seems I arrived just in time. My wayward nephew and his new flame, Captain "+GetFullName(pchar)+"... Yes, yes, "+GetSexPhrase("young man","señorita")+", don’t be surprised — I’ve made some inquiries about you."; }
			else { dialog.text = "Seems I arrived just in time. My wayward nephew and his guardian angel, Captain "+GetFullName(pchar)+"... Yes, yes, "+GetSexPhrase("young man","señorita")+", don’t be surprised — I’ve made some inquiries about you."; }
			link.l1 = "Luis Ortiz?";
			link.l1.go = "uncle_1";
		break;
		
		case "uncle_1":
			dialog.text = "You are correct, captain, but you have everything else wrong. You should not poke your nose into other men's family matters. You have no idea who you are protecting. My dissolute nephew Domingo is a worthless rake, the number one visitor to every tavern and brothel, who beds or at least tries to bed every girl in sight. I pay his rent every month and he squanders it in days, always demanding more and more. Again and again. His constant unworthy behaviour drove his mother, my sister, mad.\nI heard rumours that this wicked boy even hired and directed some English privateers to a certain ship belonging to Marquis Ricardo Albalate, which they sank along with that worthy man and my dear sister. Domingo wanted our family money so much that he would kill for it... Sadly, I failed to dig up enough evidence to send this scoundrel to the gallows.";
			link.l1 = "";
			link.l1.go = "uncle_2";
		break;
		
		case "uncle_2":
			DialogExit();
			sld = CharacterFromID("FMQP_noble");
			sld.Dialog.currentnode = "noble_34";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "uncle_3":
			if (pchar.sex == "woman") { dialog.text = "My dear nephew, as usual, in his element. So much noise, clashing swords and clinking glasses, but little substance. I don’t know what you see in him, señorita, he is..."; }
			else { dialog.text = "My dear nephew, as usual, in his element. So much noise, clashing swords and clinking glasses, but little substance. I don’t know what it is about him that convinced you to help such an unworthy brat..."; }
			link.l1 = "As far as I understand, after you failed to dig up any evidence against your nephew, you started sending assassins after him. Sounds like a simple lawsuit would have sufficed.";
			link.l1.go = "uncle_4";
		break;
		
		case "uncle_4":
			dialog.text = "You speak lies. Domingo here has made a limitless number of enemies. He's left a trail of jilted lovers and cuckolded husbands in his wake. I wonder how he has even managed to survive this long! Ask him, how many weddings has he ruined? How many insulted fiancés has he wounded or killed?";
			link.l1 = "His servant Ugo...";
			link.l1.go = "uncle_5";
		break;
		
		case "uncle_5":
			dialog.text = "Ah, Ugo! The worst rogue of them all! Ugo loved his rake of a master. All his master's crimes were nothing but a child's prank to him. Remember, "+GetSexPhrase("young man","señorita")+", family business is for the family only. Those who poke and pry will find themselves in hot water.";
			link.l1 = "Now you're threatening me.";
			link.l1.go = "uncle_6";
		break;
		
		case "uncle_6":
			int icpy = GetOfficersQuantity(pchar);
			iTotalTemp = 10000+10000*icpy;
			dialog.text = "Warning. Listen, Captain: "+GetSexPhrase("you’ve gone too far, but ","")+"since I don’t see you as an enemy—just someone misled—I’ll make you an offer: turn around and leave. I don’t want bloodshed. We'll settle our family matters without you. "+GetSexPhrase("I'm ready to compensate you for any costs involving my nephew:","To make things easier for you, I’m ready to pay you:")+" "+FindRussianMoneyString(iTotalTemp)+" in cash. Take it and forget this place. Otherwise, my guards will simply kill you.";
			link.l1 = "'Family first' is what I always say. None of my business then, hand the money over and 'vaya con Dios.'";
			link.l1.go = "uncle_7";
			link.l2 = "Your story stinks worse than your plantation's fertilizer. Don Domingo may be no saint, but you, señor, are a devil!";
			link.l2.go = "uncle_8";
		break;
		
		case "uncle_7":
			AddMoneyToCharacter(pchar, iTotalTemp);
			dialog.text = "I knew you were a reasonable man. Take your money and adios, capitán. Try not to rummage through others' dirty laundry in the future - they never appreciate it.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQP_UncleExit");
		break;
		
		case "uncle_8":
			if (pchar.sex == "woman") {dialog.text = "I see now. You're just like my nephew — a foolish, reckless girl. A perfect match for him. Time to teach you both a lesson!";}
			else {dialog.text = "I see now. You're no different from my nephew — a foolish, arrogant boy! Time to teach you both a lesson!";}
			link.l1.go = "exit";
			AddDialogExitQuest("FMQP_UncleFight");
		break;
		
		case "ugo":
			pchar.quest.FMQP_SantoDomingoOver.over = "yes";
			PlaySound("Voice\English\Serve_senior.wav");
			dialog.text = TimeGreeting()+" "+GetAddress_Form(NPChar)+". How can I be of service?";
			link.l1 = "Greetings. Beg your pardon, but is this Señor Domingo Albalate's residence?";
			link.l1.go = "ugo_1";
		break;
		
		case "ugo_1":
			dialog.text = "Sí, this is the Albalate home. It's modest yet comfortable. My name is Ugo, I serve the young master. Are you here for him?";
			link.l1 = "Sí, señor. Don Domingo invited me to his place not long ago. He was very persuasive. May I see him?";
			link.l1.go = "ugo_2";
		break;
		
		case "ugo_2":
			dialog.text = "Alas, my good "+GetSexPhrase("caballero","señorita")+", Don Domingo is not home right now. Personally, I'd like to know myself where to find that naughty boy... eh, beg pardon, young señor. May I ask what you need from him?";
			link.l1 = "Well... I helped Don Domingo by chance. He was attacked by two scoundrels in a tavern in Port-au-Prince. I assisted your master in defending himself from those... how did he call them... maldita canalla. Don Domingo invited me to pay him a visit here after he was through with the investigation. I thought it all should be settled by now already, so I expected to see him at home.";
			link.l1.go = "ugo_3";
		break;
		
		case "ugo_3":
			dialog.text = "Madre de Dios! What dreadful stories you are telling here! I must see the commandant immediately – to warn him about the dangers Don Domingo is facing right now! "+UpperFirst(GetAddress_Form(NPChar))+", you must go and I should hurry!";
			link.l1 = "Take it easy, Ugo. Your young master is safe. He mentioned that his papers are in order, they were supposed to release him already, that's why I am here. I believe we should see him soon.";
			link.l1.go = "ugo_4";
		break;
		
		case "ugo_4":
			dialog.text = "Oh! How could you? That naive boy - and in the hands of those frog-eating French?! Not to mention ladrones threatening his life? No, I must see the commandant! "+UpperFirst(GetAddress_Form(NPChar))+", please go!";
			link.l1 = "Fine, fine, don't be so pushy. I am leaving.";
			link.l1.go = "ugo_exit";
			link.l2 = "Señor, why so nervous? I told you already that there is no danger to your master. Let me stay here and wait for Señor Domingo's arrival, I am very tired from my long voyage and would appreciate your hospitality. I would like some cool fresh water and a hot bath to rinse the salt breeze from my throat. Then you can go to the local garrison and do whatever you want.";
			link.l2.go = "ugo_5";
		break;
		
		case "ugo_exit":
			DialogExit();
			LocatorReloadEnterDisable("Santodomingo_town", "houseSp4", true);
			DoQuestReloadToLocation("SantoDomingo_town", "reload", "houseSp4", "FMQP_SDMFail");
		break;
		
		case "ugo_5":
			dialog.text = ""+UpperFirst(GetAddress_Form(NPChar))+", leave this house at once!";
			link.l1 = "Ugo, I really doubt that a servant is allowed to speak to a gentleman caller in this manner. I also doubt that Don Domingo would approve of such treatment towards a man who saved his life!";
			link.l1.go = "ugo_6";
		break;
		
		case "ugo_6":
			dialog.text = "Oh really? (calling upstairs) Lads, come on down, we've got a problem!";
			link.l1 = "What the hell?";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQP_SantoDomingoFight");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
