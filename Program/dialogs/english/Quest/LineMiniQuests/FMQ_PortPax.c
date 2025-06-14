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
			dialog.text = "You are free to go for now, captain. I can see what happened here, we will summon you in case we have questions.";
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
			link.l1 = "Thank you officer, I heard a woman screaming for help and saw this gentleman being attacked by two scoundrels. I tried to save the poor man but, alas, I was too late. The bastards killed him!";
			link.l1.go = "officer_6";
		break;
		
		case "officer_6":
			dialog.text = "Damn my eyes... He's a Spaniard! Why would he be here? Hm. And who are you then, sir?";
			link.l1 = ""+GetFullName(pchar)+". Captain "+GetFullName(pchar)+".";
			link.l1.go = "officer_7";
		break;
		
		case "officer_7":
			dialog.text = "Captain, you are free to go for now. Your words match the witness'. We will call you if need be.";
			link.l1 = "Very well...";
			link.l1.go = "officer_8";
		break;
		
		case "officer_8":
			DialogExit();
			DoQuestReloadToLocation("Portpax_town", "reload", "reload4", "");
		break;
		
		case "noble":
			dialog.text = "Allow me to explain everything, senor! My name is Don Domingo Ortiz Albalate from Santo Domingo. I came to Port-au-Prence on an invite from a young senorita and made a stop in this taberna waiting for the appointed meeting. While I was minding my own business I was attacked by these two maldita ladrones. I would be supping with the angels right now if it wasn't for this Buen Samaritano who happened by.";
			link.l1 = "Don Domingo Ortiz Albalate? You are Spanish?";
			link.l1.go = "noble_1";
		break;
		
		case "noble_1":
			dialog.text = "As Spanish as Rey Felipe himself, ha! I would also like to point out that my papers are in buen orden. I am noble de Espana, not some pirata sucia!";
			link.l1 = "Don Domingo, our sincerest apologies for this unfortunate incident! Please come with us for some questions and a bottle of wine at the garrison. We'll take care of everything. As for you...";
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
			dialog.text = "Senor Capitan! Senor Capitan! I swear by Santiago and the Blessed Virgin you are a noble man, and a true son of Castile always rewards such nobility! I'd like to see you rewarded later when I will finish my business here. Please, honor me with a visit to my humble house in Santo Domingo! It's close to the city gates. I will lay out a feast for you, my buen caballero Carlos! Remember my name, it's Don Domingo Ortiz Albalate!";
			link.l1 = "...";
			link.l1.go = "noble_4";
		break;
		
		case "noble_4":
			DialogExit();
			AddMapQuestMarkCity("santodomingo", true);
			DoQuestReloadToLocation("Portpax_town", "reload", "reload4", "FMQP_AfterFightInTown");
		break;
		
		case "noble_5":
			dialog.text = "Capitan "+GetFullName(pchar)+"?! Oh Madre de Dios! What a disaster! This is a massacre! What happened here, buen amigo? Who are these men?";
			link.l1 = "Glad to see you, Don Domingo. These are... I came here to pay you a visit. See that guy over there? That's Ugo, your servant and he...";
			link.l1.go = "noble_6";
		break;
		
		case "noble_6":
			dialog.text = "Ugo?! Oh, no, you were tricked capitan!";
			link.l1 = "I get it, seems to happen a lot to me. Three scoundrels broke into your home, murdered your loyal man Ugo - I found his corpse already upstairs - and then set up an ambush for you. My arrival wasn't a part of their plan. They didn't survive our meeting.";
			link.l1.go = "noble_7";
		break;
		
		case "noble_7":
			dialog.text = "Santa Maria, ora pro nobis! You play your sword like the fencing masters of Toledo! It's good that you are on my side! Oh, my poor Ugo! He raised me since I was a child and now... to be murdered by maldita canallas!";
			link.l1 = "Don Domingo, it looks like you aren't out of danger. Your man Ugo knew something, read this note. I've found it on a table.";
			link.l1.go = "noble_8";
		break;
		
		case "noble_8":
			ChangeItemDescribe("letter_parol", "itmdescr_letter_parol");
			RemoveItems(pchar, "letter_parol", 1);
			dialog.text = "Give me it... (reading) That can not be... oh, no! This is unbelievable! Tio Luis... But...";
			link.l1 = "Any hint as to who did this?";
			link.l1.go = "noble_9";
		break;
		
		case "noble_9":
			dialog.text = "Only suspicions... dreadful suspicions mi amigo! How could my mother's brother do such a thing?";
			link.l1 = "Would you mind filling me in? I am sorry, Don Domingo but in my experience relatives are often the worst enemies a man can have...";
			link.l1.go = "noble_10";
		break;
		
		case "noble_10":
			dialog.text = "Si, you are correct, Carlos! I will tell you everything! You have saved me twice already and it seems that you are the only man I can trust right now! But let's leave this awful place, it makes me sick. I must notify the alcalde about this mess, they will take care of poor Ugo. How about we have some wine in the local taberna to calm our nerves?";
			link.l1 = "Your nerves certainly need it more than mine, lead the way senor!";
			link.l1.go = "noble_11";
		break;
		
		case "noble_11":
			DialogExit();
			chrDisableReloadToLocation = false;
			DoQuestReloadToLocation("Santodomingo_tavern", "sit", "sit_base2", "FMQP_InSantoDomingoTavern");
		break;
		
		case "noble_12":
			LAi_SetSitType(pchar);
			dialog.text = "So, my friend, allow me to tell you an...abridged form of my family history. My mother, Dona Isabella Ortiz, married my father, ek Marquis Ricardo Albalate, and took his family name according to custom. Her brother, Luis Ortiz, was a garrison commander in the colonies, but after my mother's marriage he was appointed by my father to be manager of a sugar plantation not far from Portobello\nThis was a huge and wealthy plantation, very profitable indeed. After the tragic death of my parents at sea a few years ago, I as their only son inherited everything including the plantation. My uncle has kept his position and I was happy enough with the rent he paid me. He was always on time with his payments.";
			link.l1 = "So you think your uncle...";
			link.l1.go = "noble_13";
		break;
		
		case "noble_13":
			dialog.text = "Yes. At present, he is nothing but a renter. I own the plantation, not him. But! If anything happens to me - it will become his property.";
			link.l1 = "You know, Domingo, I knew men who would murder all their relatives in cold blood for a prize much less juicy than that.";
			link.l1.go = "noble_14";
		break;
		
		case "noble_14":
			dialog.text = "You clearly need to keep better company, Carlos. My dear Ugo mentioned my uncle's papers in his last note... This is a direct clue. Oh, I don't want to believe this! But... my cousin, Margarita Ortiz, who lives in Spain was betrothed not long ago. Might it be the cause my good capitan?";
			link.l1 = "Your doting uncle might suddenly need some money...";
			link.l1.go = "noble_15";
		break;
		
		case "noble_15":
			dialog.text = "Money?! But of course... but don't forget the title of marquis! That would make my cousin a proper match to her future husband! Jesu Christo! How stupid I was!";
			link.l1 = "That title of nobility has more value than the sugar plantation.";
			link.l1.go = "noble_16";
		break;
		
		case "noble_16":
			dialog.text = "Wait my friend! I just remembered that this wasn't the first attempt on my life! I had an encounter with a beggar in the street a few weeks ago! The drunk canalla offended me in a manner I couldn't ignore. He turned out to be a damn good fencer, he drew steel and even managed to wound me with a rapier before I killed him.";
			link.l1 = "And how the hell did you end up in a tavern at Port-au-Prince? You mentioned some young senorita?";
			link.l1.go = "noble_17";
		break;
		
		case "noble_17":
			dialog.text = "(turning red) Sir...Yes captain, there was a young and pretty senorita on the scene... now I see that she was just the bait for the trap. Bastards, bastards are everywhere, can't trust anyone! Poor Ugo... he is dead now.";
			link.l1 = "You should do something about it, Domingo. How about fleeing to Spain?";
			link.l1.go = "noble_18";
		break;
		
		case "noble_18":
			dialog.text = "To Spain? And leave my plantation to that scoundrel? Capitan, I am Marquis Domingo Ortiz Albalate!";
			link.l1 = "But...";
			link.l1.go = "noble_19";
		break;
		
		case "noble_19":
			dialog.text = "My friend Carlos, may I ask for your help? With Ugo being dead I have no people by my side I can trust. You've saved me twice already! Twice! I owe you a great deal, I am forever in your debt and yet I dare ask you for another favor. I swear by the Blessing Mother, I will make it worth your while!";
			link.l1 = "Very well, you are a good man for a Spaniard. What can I do for you, Domingo?";
			link.l1.go = "noble_20";
		break;
		
		case "noble_20":
			dialog.text = "Let's go to my plantation in Portabello! I know that my uncle is in Cartagena at the moment. Ugo mentioned some papers, so let's check Don Luis Ortiz's books and documents! We might find something which will help us to drag his foul conspiracy out into the open. It's quite a distance to Portobello but I'll pay you in full for the voyage!";
			link.l1 = "It would be absurd to reject you at this point, Don Domingo. I'm in too deep to back out now.";
			link.l1.go = "noble_21";
		break;
		
		case "noble_21":
			AddMoneyToCharacter(pchar, 20000);
			dialog.text = "Gracias a Dios, I knew you would help me out, amigo! Here, take these twenty thousand pesos as payment for the voyage to Portobello. When do we set sail? We must hurry before my uncle returns from Cartagena!";
			link.l1 = "Let's waste no time then.";
			if (CheckCharacterItem(pchar, "HolTradeLicence") && GetDaysContinueNationLicence(HOLLAND) >= 20) link.l1.go = "noble_22";
			else link.l1.go = "noble_22x";
		break;
		
		case "noble_22x":
			GiveNationLicence(HOLLAND, 20);
			dialog.text = "Here's a Dutch West Indian Company license. It has a twenty day expiration, let's just put your name in it. Done. This should help us avoid any trouble with the Costa Garda.";
			link.l1 = "Excelente!";
			link.l1.go = "noble_22";
		break;
		
		case "noble_22":
			dialog.text = "Am I now allowed to come on board your ship, my friend?";
			link.l1 = "Consider yourself an honored guest. As soon as we get the right wind - we set sail.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQP_OnBoard");
			AddMapQuestMarkCity("portobello", true);
		break;
		
		case "noble_23":
			dialog.text = "So Capitan Carlos, here we are. Now we should find my uncle's house and check what's inside.";
			link.l1 = "Don Domingo, should we expect any problems with the guard?";
			link.l1.go = "noble_24";
		break;
		
		case "noble_24":
			dialog.text = "No. Although... hm. There is a chance that Luis has turned them against me. At any rate, discretion is always the better part of valor. Let's find the house we need.";
			link.l1 = "Don't you know it already? It's your plantation.";
			link.l1.go = "noble_25";
		break;
		
		case "noble_25":
			dialog.text = "Hm.. To be completely honest, the last time I was here, I was only eight years old. Yet I intend to fix this as soon as possible!";
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
			dialog.text = "What do you have here, my friend?";
			link.l1 = "Take a look, Don Domingo. Looks like accounting records. This might be interesting.";
			link.l1.go = "noble_28";
		break;
		
		case "noble_28":
			ChangeItemDescribe("Almanac", "itmdescr_Almanac");
			RemoveItems(pchar, "Almanac", 1);
			dialog.text = "(reading) Hm... Yeah. Look at this... Ay caramba! One hundred thousand pesos! And another one hundred and fifty thousand! And here... (turning over pages) Uncle Luis!";
			link.l1 = "Anything of interest?";
			link.l1.go = "noble_29";
		break;
		
		case "noble_29":
			dialog.text = "Anything of interest! My precious uncle had an income five times bigger than he was telling me! Thief! Embezzler!";
			link.l1 = "Can't say I am surprised. You can't put complete trust in anyone without checking the actual state of business from time to time. That's just common sense.";
			link.l1.go = "noble_30";
		break;
		
		case "noble_30":
			dialog.text = "Common sense to common men, perhaps. My upbringing has blinded me to such deception in gentlemen that I thought honorable! You are right as always, Carlos! My own uncle is stealing from me! Mierda! This is my fault but I will fix this. I own this plantation and my uncle has been relieved of duty as of today! He is no one! I will see him keelhauled!";
			link.l1 = "Don Domingo... Don't you think that your uncle might disagree with such a decision?";
			link.l1.go = "noble_31";
		break;
		
		case "noble_31":
			dialog.text = "I don't give a damn whether he agrees or not! I am marquee Domingo Ortiz Albalate and Luis Ortiz is nothing but a renter, and a former renter at that! And he...";
			link.l1 = "Calm yourself, senor. You are an unfamiliar face here and I'm a Frenchman sailing under a Dutch license with a...checkered past with the Spanish counterpiracy patrols. As for your uncle, he practically owns this town. Think of the guards and the local governor. You think they will choose your side?";
			link.l1.go = "noble_32";
		break;
		
		case "noble_32":
			dialog.text = "You strike the point with a rapier... Maybe... No. Spanish soldiers will never dare to raise a hand on a nobleman! My uncle can challenge me if he dares!";
			link.l1 = "Still, I suggest going another path. How about the court of law?";
			link.l1.go = "noble_33";
		break;
		
		case "noble_33":
			dialog.text = "Ha! You are right, Carlos. Let us go speak to the proper authorities. My uncle made a mistake by writing down exact details in his notes about his dealings with smugglers. He bought slaves from them for very cheap. These books will do us a great service, I doubt that the bastard will be able to harm me in any way while sitting in the dungeons. Let's go my friend! To Portobello!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQP_PrepareUncle");
		break;
		
		case "noble_34":
			//PlaySound("Voice\English\LE\Domingo\Domingo_04.wav");
			dialog.text = "This is nothing but a filthy and insolent lie! How dare him to spoil the good name of my parents with his unworthy tongue! Damn him, I will make him pay for this! Draw your sword, you assassin!";
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
			dialog.text = "Uncle Luis is in the proper place reserved for his soul - in hell... Carlos, you were sent to me by my guardian angel! I am glad you didn't trust the word of this scoundrel. To be honest, I feared that you will just leave me here alone to fight this canalla\nYes senor, I am not perfect myself but this... this filthy lie about me hiring pirates to murder my own parents! To blame me of this... this! Bah! A well deserved fate.";
			link.l1 = "Glad we made it, Don Domingo. What now? I hope we haven't run afoul of Spanish law.";
			link.l1.go = "noble_37";
		break;
		
		case "noble_37":
			dialog.text = "With the law? Ha-ha! No Carlos, I will show this fine accounting book with all my uncle's smuggling operations in it. Do not forget about the several attempts on my life, we've got a great number of witnesses after his last try just now. Don't worry about it, mi buen amigo. This is my town, it's time to show them all!";
			link.l1 = "Please move cautiously, senor. Let them think better of you than they had thought about your late uncle.";
			link.l1.go = "noble_38";
		break;
		
		case "noble_38":
			dialog.text = "That's the plan, capitan. But I will show no mercy to anyone who dares to oppose me. Let me express my sincere gratitude for you, Carlos! Please, go to the taberna, take a rest, have a cup or two. I'd be glad to join you, but you were right. It's time to grow wiser and take control over the plantation myself. Come see me here tomorrow, capitan!";
			link.l1 = "Very well, Don Domingo. See you tomorrow.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQP_PlantatonPause");
		break;
		
		case "noble_39":
			DelLandQuestMark(npchar);
			PlaySound("VOICE\English\LE\Domingo\Domingo_05.wav");
			dialog.text = "Ah, here you are my good friend!";
			link.l1 = "How are you doing, don Domingo? How is your plantation?";
			link.l1.go = "noble_40";
		break;
		
		case "noble_40":
			dialog.text = "Plantation's great, can't say the same about the money - turns out that my dear uncle had been transferring all the money to the bank of Cartagena. It will take a lot of lawyers' time to get my gold back. But it's alright, I can do that. Don't be sad captain, I will keep my promises to reward you for your nobility, honesty and friendship!";
			link.l1 = "Never had a thought about a reward when I was fighting on your side, senor...";
			link.l1.go = "noble_41";
		break;
		
		case "noble_41":
			dialog.text = "I know that, captain, and this says a lot about your character! Any good deed must be rewarded. So, although I don't have money at the moment, I will give orders to load your vessel with goods of my plantation. I mean coffee, a great batch of it. You will be able to sell it with a great profit I am sure.";
			link.l1 = "Oh! This is nice..";
			link.l1.go = "noble_42";
		break;
		
		case "noble_42":
			dialog.text = "Moreover, I have a few items of small value for me, but of great value for any sailor like yourself. A fine spyglass and three amulets. Please accept these, it's all yours now.";
			link.l1 = "Gratitude!";
			link.l1.go = "noble_43";
		break;
		
		case "noble_43":
			Log_Info("You have received a good spyglass");
			Log_Info("You have received three amulets");
			PlaySound("interface\important_item.wav");
			dialog.text = "Finally, I gift you with my rapier as a token of my immeasurable gratitude to you. She served me well, now let her serve you even better. Look at her and remember your good Spanish friend - marquee Domingo Albalate!";
			link.l1 = "Thank you so much, senor! I didn't expect...";
			link.l1.go = "noble_44";
		break;
		
		case "noble_44":
			Log_Info("You have received the Smallsword");
			PlaySound("interface\important_item.wav");
			RemoveCharacterEquip(npchar, BLADE_ITEM_TYPE);
			dialog.text = "And now, alas, I have to say my farewells. I should go to Portobello to see the governor and then to Cartagena... To sum up, my carefree existence is over, time to live as a grown up man.";
			link.l1 = "Well, you are much smarter now...";
			link.l1.go = "noble_45";
		break;
		
		case "noble_45":
			dialog.text = "That's true. It was a pleasure, my friend! Come visit me sometime. Godspeed in the sea!";
			link.l1 = "Same to you in your plantation business, don Domingo!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQP_ReceiveReward");
		break;
		
		case "noble_46":
			PlaySound("Voice\English\YoungMan02.wav");
			dialog.text = "Eh, we are late senor! What a pity, my good old uncle has already made a decent cleaning job among his papers. Looks like he was told him about Santo-Domingo and he took precaution measures... But I am not going to leave it like that! I should to see the governor of Portobello to initiate a legal procedure versus my uncle. I had enough of him managing my wealth.";
			link.l1 = "Good decision.";
			link.l1.go = "noble_47";
		break;
		
		case "noble_47":
			dialog.text = "I want to thank you, captain! It was a pleasure! I gift you with my rapier as token of my gratitude to you. She served me well, now let her serve you even better. Look at her and remember your good Spanish friend - marquee Domingo Albalate!";
			link.l1 = "Thank you so much senor! I didn't expect...";
			link.l1.go = "noble_48";
		break;
		
		case "noble_48":
			Log_Info("You have received the Smallsword");
			PlaySound("interface\important_item.wav");
			RemoveCharacterEquip(npchar, BLADE_ITEM_TYPE);
			GiveItem2Character(pchar, GetGeneratedItem("blade_16")); // belamour legendary edition используем GetGeneratedItem иначе пачка одинаковых клинков из первой части массива
			dialog.text = "And now, alas, I have to say my farewells. I should go to Portobello. My carefree existence is over, time to live as a grown up man. Godspeed in the sea!";
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
			dialog.text = "Looks like I made it in time. My carefree nephew and his guardian angel Capitan "+GetFullName(pchar)+". Don't look so surprised Frenchman, I know who you are.";
			link.l1 = "Luis Ortiz?";
			link.l1.go = "uncle_1";
		break;
		
		case "uncle_1":
			dialog.text = "You are correct, captain, but you have everything else wrong. You should not poke your nose into other men's family matters. You even have no idea who you are protecting. My dissolute nephew Domingo is a worthless rake, the number one visitor to every tavern and brothel who screws or at least tries to screw every girl on the horizon. I pay him his rent every month and he wastes it in days always demanding more and more. Again and again. His constant unworthy behavior made his mother and my sister go mad\nI heard rumors that this naughty boy even hired and directed some English privateers to a certain ship of Marquis Ricardo Albalate which they sank along with that worthy man and my dear sister. Domingo wanted our family money so much that he would kill for it... Sadly, I failed to dig out enough evidence to send this scoundrel to the gallows.";
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
			dialog.text = "Typical. Yelling, banging of swords and cups, full of sound and fury, signifying nothing. How much did he pay you, capitan, for your protection?";
			link.l1 = "As far as I understand, after you've failed to dig out any evidence against your nephew you started to send assassins after him. Sounds like a simple lawsuit would have sufficed.";
			link.l1.go = "uncle_4";
		break;
		
		case "uncle_4":
			dialog.text = "You speak lies. Domingo here has made a limitless amount of enemies. He's left a trail of jilted lovers and cuckholded husbands in his wake. I wonder how he even managed to survive this long! Ask him, how many weddings has he ruined? How many insulted fiances has he wounded or killed?";
			link.l1 = "His servant Ugo...";
			link.l1.go = "uncle_5";
		break;
		
		case "uncle_5":
			dialog.text = "Ah Ugo! The worst rogue of them all! Ugo loved his rake of a master. All his master's crimes were nothing but a child's prank to him. Remember, Frenchman, family business is for the family only. Those who poke and pry will find themselves in hot water.";
			link.l1 = "Now you're threatening me.";
			link.l1.go = "uncle_6";
		break;
		
		case "uncle_6":
			int icpy = GetOfficersQuantity(pchar);
			iTotalTemp = 10000+10000*icpy;
			dialog.text = "Not a threat, capitan, a promise. Look here boy, you've come a long way, but since I take you as a deluded victim and not as an enemy, hear my simple and generous offer: walk away. I don't want to spill blood here. We don't need your help solving our family matters. I am even ready to compensate the troubles that you've gone through because of my idiot nephew - "+FindRussianMoneyString(iTotalTemp)+" pieces of eight. Take it and leave us in one piece. Reject my offer and we'll send you back to your ship in thin slices.";
			link.l1 = "'Family first' is what I always say. None of my business then, hand the money over and 'vaya con Dios.'";
			link.l1.go = "uncle_7";
			link.l2 = "Your story stinks worse than your plantation's fertilizer. Don Domingo may be no saint, but you senor are a devil!";
			link.l2.go = "uncle_8";
		break;
		
		case "uncle_7":
			AddMoneyToCharacter(pchar, iTotalTemp);
			dialog.text = "I knew you were a reasonable man. Take your money and adios capitan. Try not to rummage through others' dirty laundry in the future - they never appreciate it.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQP_UncleExit");
		break;
		
		case "uncle_8":
			dialog.text = "A devil? Well, I'll take pleasure in sending you to hell!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQP_UncleFight");
		break;
		
		case "ugo":
			pchar.quest.FMQP_SantoDomingoOver.over = "yes";
			PlaySound("Voice\English\Serve_senior.wav");
			dialog.text = TimeGreeting()+" senor. How can I be of service?";
			link.l1 = "Greetings. Beg pardon, but is this Senor Domingo Albalate's residence?";
			link.l1.go = "ugo_1";
		break;
		
		case "ugo_1":
			dialog.text = "Si, this is the Albalate home. It's modest yet comfortable. My name is Ugo, I serve the young master. Are you here for him?";
			link.l1 = "Si, senor. Don Domingo invited me to his place not long ago. He was very persuasive. May I see him?";
			link.l1.go = "ugo_2";
		break;
		
		case "ugo_2":
			dialog.text = "Alas, my good caballero, Don Domingo is not home right now. Personally, I'd like to know myself where to find that naughty boy... eh, beg pardon, young senor. May I ask what you need from him?";
			link.l1 = "Well... I helped Don Domingo by chance. He was attacked by some two scoundrels in a tavern of Port-au-Prince. I assisted your master in defending himself from those... how did he call them... maldita canalla. Don Domingo invited me to pay him a visit here after he was through with the investigation. I thought it all should be settled by now already, so I expected to see him home.";
			link.l1.go = "ugo_3";
		break;
		
		case "ugo_3":
			dialog.text = "Madre de Dios! What dreadful stories you telling here! I must see the commandant immediately - to warn him about the dangers Don Domingo is facing right now! Senor, you must go and I should hurry!";
			link.l1 = "Take it easy, Ugo. Your young master's safe. He mentioned that his papers are in order, they were supposed to release him already, that's why I am here. I believe we should see him soon.";
			link.l1.go = "ugo_4";
		break;
		
		case "ugo_4":
			dialog.text = "Oh! How could you? My young master, that naive boy - and in the hands of those frog eating French?! Not to mention ladrones threatening his life? No, I must see the commandant! Sir, please go!";
			link.l1 = "Fine fine, don't be so pushy. I am leaving.";
			link.l1.go = "ugo_exit";
			link.l2 = "Senor, why so nervous? I told you already that there is no danger to your master. Let me stay here and wait for Senor Domingo's arrival, I am very tired from my long voyage and would appreciate your hospitality. I would like some cool fresh water and a hot bath to rinse out the salt breeze from my throat. Then you can go to the local garrison and do whatever you want.";
			link.l2.go = "ugo_5";
		break;
		
		case "ugo_exit":
			DialogExit();
			LocatorReloadEnterDisable("Santodomingo_town", "houseSp4", true);
			DoQuestReloadToLocation("SantoDomingo_town", "reload", "houseSp4", "FMQP_SDMFail");
		break;
		
		case "ugo_5":
			dialog.text = "Senor, leave this house at once!";
			link.l1 = "Ugo, I really doubt that a servant is allowed to talk to a gentleman caller in this manner. I also doubt that Don Domingo would approve of such treatment to a man who saved his life!";
			link.l1.go = "ugo_6";
		break;
		
		case "ugo_6":
			dialog.text = "Oh really? (calling upstairs) Lads, come on down, we've got a problem!";
			link.l1 = "What the fuck?";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQP_SantoDomingoFight");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
