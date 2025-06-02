// диалоги НПС по квесту НСО
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
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
			dialog.text = "What are you looking for?";
			link.l1 = "Nothing.";
			link.l1.go = "exit";
		break;
		
		// инспектор Ноэль Форже
		case "noel":
			dialog.text = "Nice to meet you, captain!";
			link.l1 = "I'm glad to meet you too, monsieur Forget. It's a rare occasion to meet a guest from the metropolis here in the wilderness...";
			link.l1.go = "noel_1";
		break;
		
		case "noel_1":
			DialogExit();
			sld = characterFromId("Puancie");
			sld.dialog.currentnode = "patria_3";
			LAi_SetActorType(sld);
			LAi_ActorSetSitMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "noel_2":
			dialog.text = "I'm pleased that during this journey I will be on your ship, captain. Chevalier de Poincy told me a lot of interesting stories about you. I'm sure that after the dinner in the messroom we will have plenty of topics to discuss about. A glass of wine could also come in handy.";
			link.l1 = "I'm all in for a cosy talk, especially when I'm full. I'd be glad to be your companion, Baron. ";
			link.l1.go = "noel_3";
		break;
		
		case "noel_3":
			dialog.text = "Perfect. When we go to a colony, I'd ask you to gide me to the governor, and I'll personally explain to him what needs to be done. You'll just wait until I finish my affairs. Deal?";
			link.l1 = "Aye, monsieur Forget. Welcome aboard!";
			link.l1.go = "noel_4";
		break;
		
		case "noel_4":
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 12.0);
		break;
		
		case "noel_5":
			dialog.text = "Tortuga is a small colony captain. I estimate that it will take me about three days to inspect all I need on this Island.";
			link.l1 = "Understood, Baron. So in three days time I'll come here to pick you up. Good luck!";
			link.l1.go = "noel_6";
		break;
		
		case "noel_6":
			DialogExit();
			DoQuestReloadToLocation("Tortuga_town", "reload", "reload3", "Patria_VisiterTortuga");
		break;
		
		case "noel_7":
			dialog.text = "My work on Tortuga is done, it's time to raise the anchor.";
			link.l1 = "Understood, Baron. We will be underway immediately.";
			link.l1.go = "noel_8";
		break;
		
		case "noel_8":
			DialogExit();
			Patria_VisiterTortugaSail();
		break;
		
		case "noel_9":
			dialog.text = "Yes-yes, we will definitely report on this in Capsterville. The threat of such an important colony being conquered... unthinkable, I will personally make sure that Chevalier de Poincy takes strict and ruthless measures! Captain, I will remain for a week on this island, there are a lot of plantations here, it will take some time.";
			link.l1 = "Got it, Baron. I will be waiting for you by the governors palace in seven days. Have fun and don't overwork yourself!";
			link.l1.go = "noel_10";
		break;
		
		case "noel_10":
			DialogExit();
			DoQuestReloadToLocation("PortPax_town", "reload", "reload3", "Patria_VisiterPortPax");
		break;
		
		case "noel_11":
			dialog.text = "There you are, captain. My work on Hipaniola is done, It's time to raise the anchor.";
			link.l1 = "Understood, Baron. We will be underway immediately.";
			link.l1.go = "noel_12";
		break;
		
		case "noel_12":
			DialogExit();
			Patria_VisiterPortPaxSail();
		break;
		
		case "noel_13":
			dialog.text = "Captain, this island seems familiar to me. Isn't it Saint Christopher?";
			link.l1 = "Yes, baron, precisely. We are almost there.";
			link.l1.go = "noel_14";
		break;
		
		case "noel_14":
			dialog.text = "Almost there?! Weren't we supposed to visit Saint-Martin too? It also belongs to the French colonies.";
			link.l1 = "You mean Sint Maarten? It's a Dutch colony, monsieur Forget.";
			link.l1.go = "noel_15";
		break;
		
		case "noel_15":
			dialog.text = "Is it? In Paris it was considered to be French. How come?";
			link.l1 = "No idea, Baron. Ever since I first set foot in the archipelago, Sint Maarten was a Dutch colony. Perhaps I don't know something. You should consider talking to Chevalier de Poincy on this matter.";
			link.l1.go = "noel_16";
		break;
		
		case "noel_16":
			dialog.text = "Fine, captain, so be it. We are almost at Capsterville anyway.";
			link.l1 = "...";
			link.l1.go = "noel_17";
		break;
		
		case "noel_17":
			DialogExit();
			Island_SetReloadEnableGlobal("Nevis", true);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 5.0);
			pchar.quest.Patria_visiter_fin.win_condition.l1 = "location";
			pchar.quest.Patria_visiter_fin.win_condition.l1.location = "Charles_Roomtownhall";
			pchar.quest.Patria_visiter_fin.function = "Patria_VisiterFin";
			pchar.questTemp.Patria = "epizode_2_return";
		break;
		
		case "noel_18":
			dialog.text = TimeGreeting()+", captain. I'm glad to see you. I have heard that you were promoted, please accept my congratulations! To tell you the truth, you really are one of the most sensible and gifted officers in de Poincy's service.";
			link.l1 = "Thank you, monsieur.";
			link.l1.go = "noel_19";
		break;
		
		case "noel_19":
			dialog.text = "Finally, there is only one colony left then, Saint-Martin. To be honest, I've grown tired of these trips. I'll be glad to finish this inspection and start arranging the next French West-Indies trade campaign. Are we ready to call away the anchor?";
			link.l1 = "Aye, Baron. Get on board.";
			link.l1.go = "noel_20";
		break;
		
		case "noel_20":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Patria_SanMartinBaron", 5.0);
		break;
		
		case "noel_21":
			dialog.text = "Captain, could you tell me what just happened? Does this mean a war? Why in the hell's name were we almost sunk by the Dutch?";
			link.l1 = "Baron, I don't understand anything myself! This must be some kind of misunderstanding, no doubt.";
			link.l1.go = "noel_22";
		break;
		
		case "noel_22":
			dialog.text = "Captain, I can bet that this 'misunderstanding' has a name! Peter Stuyvesant, so called 'renter' of Saint-Martin and a partner of our dear Chevalier de Poincy!";
			link.l1 = "I have no idea, Baron. We better hurry to the Capsterville and report on this matter to the Governor General.";
			link.l1.go = "noel_23";
		break;
		
		case "noel_23":
			dialog.text = "Without a doubt, that's exactly what we will do! And I will demand explanations! I knew that renting an island to the Dutch was a big mistake! Let's leave this place as quick as we can captain, before someone decides to chase us!";
			link.l1 = "Precisely, monsieur ...";
			link.l1.go = "noel_24";
		break;
		
		case "noel_24":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Patria_SanMartinBack", 5.0);
		break;
		
		case "noel_25":
			dialog.text = "Monsieur, first let me congratulate you on your promotion! I eagerly supported the decision of monseigneur de Poincy to grant you the rank of Vice Admiral. You deserve this title! Now, I have recently returned from Saint-Martin. At the warehouses of Philipsburg, we conducted a revision, all Dutch goods were confiscated and now belong to the treasury of France. You, as the commander of a combat operation, have been granted a share of the trophies. I agree with the Chevalier that this is fair. Your goods have been transferred to the warehouse of the St. Christopher store, and you can pick them up whenever you want.";
			link.l1 = "Thank you, Baron. Let the goods stay there for a while. Upon my return from Curacao, I will take them.";
			link.l1.go = "noel_26";
		break;
		
		case "noel_26":
			dialog.text = "Good luck in your next campaign, Vice Admiral! I am confident that you will return with victory and justly punish this scoundrel Stuyvesant.";
			link.l1 = "...";
			link.l1.go = "noel_27";
		break;
		
		case "noel_27":
			DialogExit();
			pchar.questTemp.Patria = "epizode_11_start";
			AddQuestRecord("Patria", "58");
			pchar.questTemp.Patria.GoodsSM = "true";
		break;
		
		case "noel_28":
			dialog.text = "Who do we have here! Vice Admiral Charles de Maure! Glad to see you! What's your business in Port-au-Prince?";
			link.l1 = "I'm pleased to meet you too, Baron. I'm here because of my duty, I had to pay monsieur Jeremy Deschamps du Mussaca a visit of politeness...";
			link.l1.go = "noel_29";
		break;
		
		case "noel_29":
			dialog.text = "This encounter is very fortunate indeed, because I have been waiting for a long time to meet with you personally. I want to talk to you, but not here.";
			link.l1 = "Let's go to the tavern then, shall we?";
			link.l1.go = "noel_30";
		break;
		
		case "noel_30":
			DialogExit();
			FreeSitLocator("PortPax_tavern", "sit_base1");
			DoQuestReloadToLocation("PortPax_tavern", "sit", "sit_base1", "Patria_CondotierTavern");
		break;
		
		case "noel_31":
			LAi_SetSitType(pchar);
			dialog.text = "There are no unwanted ears here, we can talk safely...";
			link.l1 = "I'm all ears, Baron.";
			link.l1.go = "noel_32";
		break;
		
		case "noel_32":
			dialog.text = "Vice Admiral, you seem to be a man of honour. Such a valiant naval officer just has to be like that...";
			link.l1 = "Hmm... I don't think I fully understand you, monsieur...";
			link.l1.go = "noel_33";
		break;
		
		case "noel_33":
			dialog.text = "Monsieur de Maure, I wanted to ask you: what do you think of your liege, Governor General Philippe de Poincy?";
			link.l1 = "Officer's duty is not to think about his commander, but to follow his orders.";
			link.l1.go = "noel_34";
		break;
		
		case "noel_34":
			dialog.text = "Oh, leave it, Vice Admiral, we're not in the barracks, and not in the de Poincy's hall. I will say it this way: don't you think, that monsieur de Poincy... abuses his power? I still can't forget how we almost went down the drain under the Fort guns of Saint-Martin. I am sure that the treachery of the Dutch had a reason.";
			link.l1 = "They wanted to conquer the island.";
			link.l1.go = "noel_35";
		break;
		
		case "noel_35":
			dialog.text = "Yes, yes, but why exactly at the same moment when I decided to inspect it? Why not a month earlier? Or two months later? I do not believe that this was coincidence, monseigneur. Don't you have any suspicions? We both had our lives at the stake there.";
			link.l1 = "I risk my life every day, monseigneur Forget. I think you understand that...";
			link.l1.go = "noel_36";
		break;
		
		case "noel_36":
			dialog.text = "Your courage is beyond doubt. But that's not what I wanted to say. You see... When I was doing my job on the Saint-Martin that was liberated by you, I repeatedly heard whisperings from locals about some mine in the depths of the island. I tried to ask people about it, but they just acted foolish. They were afraid... It was obvious that I didn't seem very trustwothy, but this only strengthened my suspicions: could this misterious mine be the reason for all this, Monsieur de Maure? Wars are waged because of gold, am I right?";
			link.l1 = "There are numerous mines in the archipelago. Most of them are exhauseted and became worthless. I know of one major operating gold mine, it is owned by the Spaniards on South Main. But I've never heard of gold mining on Saint-Martin.";
			link.l1.go = "noel_37";
		break;
		
		case "noel_37":
			dialog.text = "You are skilled in the art of speechcraft, Vice Admiral! I understand: you do not trust me. I'm new here... Monsieur de Maure, but I'm an infulential person in Paris. The Minister of Finance is my close friend. I visit the King regularly. My authority is much greater than the authority of Philippe de Poincy, formally, of course, because here the Governor General is the most entitled person. But truth be told, here, in the colonies, the rule of the stongest is the only rule.";
			link.l1 = "I completely agree with you there.";
			link.l1.go = "noel_38";
		break;
		
		case "noel_38":
			dialog.text = "But not in Paris. There, the most influencial people are the King and the Minister of Finance... my close friend. Monsieur de Maure, you are a brilliant military man, but I believe that Phillip de Poincy is using you for his own personal purposes. You are intelligent, so you must have suspicions. You can trust me. I guarantee you complete anonimity and support of the authorities of Paris. I swear by my title.";
			link.l1 = "***REMAIN LOYAL TO POINCY***";
			link.l1.go = "noel_39"; // развилка
			link.l2 = "***SIDE WITH BARON FORGET***";
			link.l2.go = "noel_53";
		break;
		
		case "noel_39":
			dialog.text = "";
			link.l1 = "I understand you, Monsieur Forger. To a man unfamiliar with local mindsets, de Poincy's actions may indeed seem strange. When I first arrived at the Archipelago, I was literally shocked by what was happening here. I still remember the very first words I was told: 'If you meet an unprotected Spanish ship, you can try to board it.' Betrayal, treachery, deception - they are present here at every step. Piracy, pillaging, robbery...";
			link.l1.go = "noel_40";
		break;
		
		case "noel_40":
			dialog.text = "";
			link.l1 = "We are at peace with Spain in Europe. But here we are fierce enemies. The Dutch today seem friendly and harmless, and tomorrow the Company official confiscates your goods just because they suddenly announced it was banned from importation even though you could not know it. The English officer is openly pirating, sinking the Company's ships, and the Company hires a cutthroat who disguises as a ghost ship, and terrifies British traders...";
			link.l1.go = "noel_41";
		break;
		
		case "noel_41":
			dialog.text = "";
			link.l1 = "In this wolf's den, we sometimes have to make strange decisions that are not quite obvious to someone unfamiliar with all this. And what seems suspicious to you is in fact the only correct action. It is difficult to sit on several chairs at once and still manage to send profits to the parent state. Chevalier de Poincy copes with this perfectly, he is an experienced manager and visionary politician. Of course, he can make mistakes, but we all make them at some point in our lives...";
			link.l1.go = "noel_42";
		break;
		
		case "noel_42":
			dialog.text = "";
			link.l1 = "And you need to reckon with everything and everyone. With the ambitions of the Spaniards who believe that the whole New World belongs to them, with the greed of the Dutch traders, with cold prudence and ruthless brutality of the English. And even with pirates.";
			link.l1.go = "noel_43";
		break;
		
		case "noel_43":
			dialog.text = "With pirates?!";
			link.l1 = "Yes, you heard right. The Dutch and the British are actively cooperating with pirates... unofficially, of course. The Brethren of the Coast is a serious force that can challenge any nation in the region, they are in constant conflict with everyone they encounter and no one is capable of stopping them. The only thing that makes them slightly less dangerous is the fact that they are scattered and act on their own behalf. Did you know that the former governor of Tortuga, Levasseur, actually created a state in the state, relying completely on pirates?";
			link.l1.go = "noel_44";
		break;
		
		case "noel_44":
			dialog.text = "I believe I've heard something about it...";
			link.l1 = "A few powerful privateer ships that protected the island were constantly docked in the port of Tortuga. Levasseur betrayed France, becoming a sort of local authority. And now, after the destruction of the pirate nest on Tortuga together with their master, the pirates are awfully angry at the French...";
			link.l1.go = "noel_45";
		break;
		
		case "noel_45":
			dialog.text = "You don't say!";
			link.l1 = "Yes. We had to do it otherwise Tortuga would be lost to us, although the result we got was not the best. No trading French ship can feel safe in the Caribbean now. The Spaniards, who also do not have agreements with pirate barons, at least have a fleets of strong galleons and powerful military warships capable of repelling the filibusters. Like the Dutch with their East Indians and Xebecs. But we can not boast of such a thing, alas. And French pirates often rob French merchants.";
			link.l1.go = "noel_46";
		break;
		
		case "noel_46":
			dialog.text = "This is madness! Is there no way to put an end to this?";
			link.l1 = "Many have tried. In the end, instead of fighting, they buy their loyalty with gold. Issue privateer patents, I mean.";
			link.l1.go = "noel_47";
		break;
		
		case "noel_47":
			dialog.text = "Hmm...";
			link.l1 = "So speaking from experience French trading company here on the Archipelago would be a very bad idea. Do you understand now what difficulties you will have to face? How many bastards want to get their share of income here? And they are not going to let go of it easily. And pirates, they are capable of unthinkable things, call them crazy if you want but they almost always achieve their dirty goals? In order to protect merchant ships, you would have to maintain a massive military fleet, but will that be profitable from a financial standpoint?";
			link.l1.go = "noel_48";
		break;
		
		case "noel_48":
			dialog.text = "But French traders manage here somehow?";
			link.l1 = "Exactly, somehow. Especially now, when Levasseur's pirate fortress on Tortuga has been siezed...";
			link.l1.go = "noel_49";
		break;
		
		case "noel_49":
			dialog.text = "Your words fall in line with what de Poincy said.";
			link.l1 = "It's the truth. That's how it is here in the archipelago, it always was.";
			link.l1.go = "noel_50";
		break;
		
		case "noel_50":
			dialog.text = "You're so eager in what you say. Even I did not know a lot of this and, you are right: I still don't. I guess my suspicions of Poincy were invalid. You opened my eyes. I thank you, Vice Admiral. But the French minister is counting on the creation of the Company. The King needs the money...";
			link.l1 = "I understand. But please take what I just said into consideration, if the creation of the French West Indies is unavoidable, then please make sure that we have a strong military fleet to protect it.";
			link.l1.go = "noel_51";
		break;
		
		case "noel_51":
			dialog.text = "Your grace is truly admirable, Vice Admiral! Such a noble temper! I'm not surprised that you've been here so long and did not hurry back home. But we will see each other again: I will return here in half a year. The French Trading Company shall rise. And with pirates, I think you're exaggerating a bit. All in all, we do have warships and brave captains, such as you.";
			link.l1 = "I am sorry Baron but I am just one man, and beside me France has only one strong ship in archipelago 'Eclatant', it won't be enough, we will lose a lot more than we will gain... Eh whenever, it is what it is, I guess we will think of something in the meantime... When will you be heading off to France?";
			link.l1.go = "noel_52";
		break;
		
		case "noel_52":
			dialog.text = "In two weeks I will return to Saint Christopher, and from there I'll be heading home. Monsieur de Poincy gave me a good ship - a brig called 'Favory' and a glorious captain. The ship is fast and the captain is experienced, but, of course, I was safer with you. I remember our travels through the archipelago, Vice Admiral, it was truly a wonderful experience.";
			link.l1 = "Thank you for your kind words, Baron. Well, I guess it's time for us part...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Patria_CondotierToPirates");
		break;
		
		case "noel_53":
			dialog.text = "";
			link.l1 = "Here everyone uses each other. Chevalier used me in his doings long before I became an officer of the navy.";
			link.l1.go = "noel_54";
		break;
		
		case "noel_54":
			dialog.text = "And is it acceptable? What do you think?";
			link.l1 = "No. But the Chevalier left me with no choice: either follow his orders, or my brother would remain behind bars until the end of his days, and the good name of my family would be ruined.";
			link.l1.go = "noel_55";
		break;
		
		case "noel_55":
			dialog.text = "Horrible! This is straight up terrorism! Did he have any reason for such threats?";
			link.l1 = "My brother had the misfortune of being his entrusted man. Just like I am now.";
			link.l1.go = "noel_56";
		break;
		
		case "noel_56":
			dialog.text = "Where is your brother now?";
			link.l1 = "I managed to free him but I lost him the very next day, he chose to not serve under anyone anymore.";
			link.l1.go = "noel_57";
		break;
		
		case "noel_57":
			dialog.text = "I knew that Poincy was not who he said he was! Wolf in sheep's skin! Vice Admiral, you can trust me. I am a man of honour. And I will save you from this yoke of your 'patron' if we can find tangible evidence of his criminal activities. Do you know anything about this dull story with Stuyvesant? Speak openly, and don't worry you are only a military man, and you were obliged to carry out your orders.";
			link.l1 = "I know. There indeed is a mine at Saint-Martin. Only they get there not gold, but salt. It is in great demand from the Spaniards. Poincy could not trade with the Spaniards directly, so Stuyvesant acted as a middleman.";
			link.l1.go = "noel_58";
		break;
		
		case "noel_58":
			dialog.text = "So Poincy and Stuyvesant are business partners?";
			link.l1 = "Used to be. After you expressed a desire to inspect the Saint-Martin, the Stuyvesant decided to knock Poincy out of the game, taking all the profits from the salt mine himself. Poincy could not tell anyone... But Stuyvesant miscalculated, as we can see.";
			link.l1.go = "noel_59";
		break;
		
		case "noel_59":
			dialog.text = "Do you think that the mine continues to operate?";
			link.l1 = "I'm sure of it. It seems that Poincy has a new trade ally now. It's no one other that Colonel Doily himself.";
			link.l1.go = "noel_60";
		break;
		
		case "noel_60":
			dialog.text = "Can we present any evidence to the ministry?";
			link.l1 = "Hmm. During the storming of the mine, which, by the way, was conducted by Spaniards, not the Dutch, we captured the owner. He is still on my ship. You can talk to him. There is a chance that in exchange for freedom he will tell a lot of interesting things.";
			link.l1.go = "noel_61";
		break;
		
		case "noel_61":
			dialog.text = "Let's go to your ship immediately. Order your prisoner to be delivered to your cabin. I will have a talk with him.";
			link.l1 = "Fine, let's go.";
			link.l1.go = "exit";
			npchar.greeting = "noel_4";
			AddDialogExitQuestFunction("Patria_CondotierToCabin");
		break;
		
		case "noel_62":
			dialog.text = "Great, Vice Admiral. I'll have a talk with him. Stay here, please.";
			link.l1 = "Of course...";
			link.l1.go = "noel_63";
		break;
		
		case "noel_63":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "rld", "aloc1", "", -1);
			DoQuestFunctionDelay("Patria_CondotierInCabinTalk", 3.0);
		break;
		
		case "noel_64":
			dialog.text = "I wrote down all the evidence of your captive, and he signed under them. Now we must fulfill what I promised to him, whenever there is a convenient opportunity stop by Cartagena and let him disembark. But you yourself heard everything\nNow what a scoundrel our Poincy is! Rented an island to the Dutch, conducted illegal activities there and allowed the Spaniards to go there and manage the mine! I'm afraid to imagine how much money the King's treasury is missing because of his selfishness!";
			link.l1 = "Will that evidence be enough to charge Poincy?";
			link.l1.go = "noel_65";
		break;
		
		case "noel_65":
			dialog.text = "Unfortunately, I'm afraid it won't. The evidence is very important, but it's not enough. But I don't want you to be involved in all this for reasons we both understand.";
			link.l1 = "The Spaniard agreed to testify before your commission when it arrives here.";
			link.l1.go = "noel_66";
		break;
		
		case "noel_66":
			dialog.text = "This will happen no sooner than in six months, and who knows what will become of this Spaniard, and will we be able to find him later in Cartagena... We need to have even more valuable evidence. Namely - a proof that the mine continues its secret activities and still fills the pockets of our dear governor-general.";
			link.l1 = "So you're suggesting that we travel to Saint-Martin?";
			link.l1.go = "noel_67";
		break;
		
		case "noel_67":
			dialog.text = "Yes. Do you know how to get to the mine?";
			link.l1 = "I do.";
			link.l1.go = "noel_68";
		break;
		
		case "noel_68":
			dialog.text = "Then, at night, you and I will sneak in there, quietly, so that no one will see, and we will check what is going on there.";
			link.l1 = "Very good.";
			link.l1.go = "noel_69";
		break;
		
		case "noel_69":
			dialog.text = "But what about the Chevalier, huh? Now I understand why he hinted to me with such courage that the creation of the French Trading Company on the Archipelago would be unprofitable... Of course, it would be very unprofitable for him!";
			link.l1 = "Since we are now allies, Baron, I will tell you all the truth, Poincy asked me... to convince you that you to not create the Trade Company here.";
			link.l1.go = "noel_70";
		break;
		
		case "noel_70":
			dialog.text = "So that's how it is! I hope that at least he didn't ask you to eliminate me with a sword or a pistol?";
			link.l1 = "No. You had to be convinced is some other way.";
			link.l1.go = "noel_71";
		break;
		
		case "noel_71":
			dialog.text = "Poincy will pay for this, but now we need to immediately sail to Saint-Martin. Spaniard will be delivered to Main after. We're leaving, Vice Admiral!";
			link.l1 = "It will seem a bit strange that you will be leaving the island on my ship, don't you think?";
			link.l1.go = "noel_72";
		break;
		
		case "noel_72":
			dialog.text = "Don't think so. Weren't you supposed to convince me? That's exactly what you did, haha! Yes, before sailing to Europe, I'll tell the Chevalier that I agree with his points and the Trading Company won't be created. Let him live in blissful peace of a lie, for now... Let's go!";
			link.l1 = "...";
			link.l1.go = "noel_73";
		break;
		
		case "noel_73":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Patria_CondotierToSMartin", 5.0);
		break;
		
		case "noel_74":
			dialog.text = "Lead the way, Vice Admiral. The night will conceal us with it's shroud of darkness.";
			link.l1 = "Follow me...";
			link.l1.go = "noel_75";
		break;
		
		case "noel_75":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			pchar.quest.Patria_Condotier_inMine.win_condition.l1 = "location";
			pchar.quest.Patria_Condotier_inMine.win_condition.l1.location = "Location_reserve_03";
			pchar.quest.Patria_Condotier_inMine.function = "Patria_CondotierInMine";
		break;
		
		case "noel_76":
			dialog.text = "(whispering) I saw it! I saw it! Did you see it? Redcoats! Those are english soldiers!";
			link.l1 = "I told you - Poincy now conducts business with colonel Doily.";
			link.l1.go = "noel_77";
		break;
		
		case "noel_77":
			dialog.text = "You were right. I've seen enough. Now let's get out of here as fast as we can before we're spotted!";
			link.l1 = "Agreed...";
			link.l1.go = "noel_78";
		break;
		
		case "noel_78":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			LAi_ActorRunToLocator(pchar, "reload", "reload2_back", "Patria_CondotierToBeach", -1);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
		break;
		
		case "noel_79":
			dialog.text = "You see what the 'commercial projects' of our dear Chevalier lead to! The English behave like hosts on a French island! This is outrageous!";
			link.l1 = "We need to move, or someone will most definitely come here. We can't afford to be recognised.";
			link.l1.go = "noel_80";
		break;
		
		case "noel_80":
			dialog.text = "Vice Admiral, I've been thinking all the time during our travel to Saint-Martin, and I decided on something: can you arrange me a meeting with Peter Stuyvesant?";
			link.l1 = "With Stuyvesant? But why?";
			link.l1.go = "noel_81";
		break;
		
		case "noel_81":
			dialog.text = "A former business partner might have some serious clues, and some serious proofs of Chevaliers' involvement. I'm sure that Stuyvesant is not very happy with Poincy and will seek revenge, especially after these recent events...";
			link.l1 = "I believe so, Baron. I personally will not dare to go to the Stuyvesant's palace. It is too risky for me, after everything I have done to them...";
			link.l1.go = "noel_82";
		break;
		
		case "noel_82":
			dialog.text = "I already thought about it. We will go to Curacao, disembark in a bay far from the city and send our captive Spaniard from the mine with a letter to Stuyvesant. I will not mention you there, instead I will inform him that I'm leading an investigation against Poincy or something along the lines. I think the Dutchman will come for the rendezvous.";
			link.l1 = "Hmm. I don't think that this is a good idea. The Stuyvesant is not a fool, he takes what he can he might even try to imprison you and demand a huge ransom, but if we make him believe that all that happened was because of Poincy he might side with us. Well, if you are so determined, let's give it a try.";
			link.l1.go = "noel_83";
		break;
		
		case "noel_83":
			DialogExit();
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("Shore40", "reload1_back", false);
			LocatorReloadEnterDisable("Shore40", "boat", false);
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_LocationDisableOfficersGen("shore40", false);
			LAi_LocationDisableOfficersGen("Location_reserve_01", false);
			LAi_LocationDisableOfficersGen("Location_reserve_03", false);
			pchar.quest.Patria_CondotierCuracao.win_condition.l1 = "location";
			pchar.quest.Patria_CondotierCuracao.win_condition.l1.location = "shore22";
			pchar.quest.Patria_CondotierCuracao.function = "Patria_CondotierOnCuracao";
			AddQuestRecord("Patria", "81");
		break;
		
		case "noel_84":
			dialog.text = "Monsieur de Maure, please forgive my foolishness. You were right about Stuyvesant. I should have guessed that only an even bigger scoundrel could have challenged de Poincy!";
			link.l1 = "Hah! A million... Poincy wanted a million, Stuyvesant wants a million... Seems like we're going in circles...";
			link.l1.go = "noel_85";
		break;
		
		case "noel_85":
			dialog.text = "What are you talking about Vice Admiral?";
			link.l1 = "When I arrived to the Carribean, Poincy wanted me to pay a million as a ransom for my brother.";
			link.l1.go = "noel_86";
		break;
		
		case "noel_86":
			dialog.text = "And you paid that much?";
			link.l1 = "I earned it and I paid it. Not in a month, of course. Truth be told, I was just a landlubber back then. Still Chevalier didn't let Michel go.";
			link.l1.go = "noel_87";
		break;
		
		case "noel_87":
			dialog.text = "And after that you enlisted to work for Poincy? I honestly don't understand you.";
			link.l1 = "I enlisted to serve the France and those I love, I bow to no one else except the king.";
			link.l1.go = "noel_88";
		break;
		
		case "noel_88":
			dialog.text = "Excuse me, Monsieur de Maure. Of course, you serve the France and the King! Poincy will answer for everything! Including all the pain that he caused to you.";
			link.l1 = "Very well Baron, I'll find a million that I can spare. Get on board... I will solve this problem.";
			link.l1.go = "noel_89";
		break;
		
		case "noel_89":
			DialogExit();
			//chrDisableReloadToLocation = false; //17-add
			LAi_LocationFightDisable(&Locations[FindLocation("shore22")], false);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "sea", "none", "", "", "", 10.0);
			pchar.questTemp.Patria = "epizode_12_stivesant";
			AddQuestRecord("Patria", "83");
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			SetFunctionTimerCondition("Patria_CondotierStivesantTimeOver", 0, 0, 30, false); // таймер на месяц
		break;
		
		case "noel_90":
			dialog.text = "You wanted to meet me, Vice Admiral?";
			link.l1 = "Yes. I had a meeting with Stuyvesant. Here is his ledger.";
			link.l1.go = "noel_91";
		break;
		
		case "noel_91":
			RemoveItems(pchar, "Reserve_item_01", 1);
			dialog.text = "I don't believe it! Hmm, let's see... (reading)";
			link.l1 = "...";
			link.l1.go = "noel_92";
		break;
		
		case "noel_92":
			LAi_Fade("", "");
			dialog.text = "This is it! Our dear Chevalier is doomed. As soon as all this accounting will be seen by the Minister of Finance... I can't even imagine what will happen to him. We won't even have to look for the Spaniard from Cartagena. Monsieur de Maure, did you really pay million for this book?";
			link.l1 = "I did. If I tried anything else France could lose it's colonies in the Caribbean due to a civil war, which I could win, but what kind of an admiral would I be if I fought my own people.";
			link.l1.go = "noel_93";
		break;
		
		case "noel_93":
			dialog.text = "You truly are worthy of your name. I swear to you Vice Admiral that you will get it back. I am sure that we will find a hefty sum of money in Poincy's chests and his usurers. I only ask you to wait six months until I return from Europe with a commission.";
			link.l1 = "And don't forget to bring a regiment of well trained and armed soldiers. And a ship like 'Eclatant'. I also believe that the captain of 'Eclatant' will take our side when the time comes.";
			link.l1.go = "noel_94";
		break;
		
		case "noel_94":
			dialog.text = "Don't doubt it, he is also an honorable man. I realized moral values play a major role in the making of your own decisions. You did a great job, that you trusted me and exposed this state criminal. Now take me to Capsterville, where I will report to Poincy about the success of your mission - you managed to convince me and I will abandon the idea of creating the trading company. Perhaps Poincy will even reward you for this - take the reward with a clear conscience and do not worry about anything, you of all people deserved it. You will not be dragged into this, and your name will not be stained with misdeeds of your superior, in fact I will say all the best things about you when I meet with the king. Baron Forget is a man of honor and a man of his word.";
			link.l1 = "I'm glad, baron. Let's set out!";
			link.l1.go = "noel_95";
		break;
		
		case "noel_95":
			DialogExit();
			chrDisableReloadToLocation = false;
			bQuestDisableMapEnter = false;//открыть карту
			Island_SetReloadEnableGlobal("Curacao", true);
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 5.0);
			pchar.questTemp.Patria = "epizode_12_baronwin";
			AddQuestRecord("Patria", "85");
			pchar.quest.Patria_CondotierBaron_win.win_condition.l1 = "location";
			pchar.quest.Patria_CondotierBaron_win.win_condition.l1.location = "Charles_town";
			pchar.quest.Patria_CondotierBaron_win.function = "Patria_CondotierBaronWin";
		break;
		
		case "noel_96":
			dialog.text = "So, Vice Admiral, we have finally arrived. Your mission is over, now it's up to me. Go conduct your own affairs, defend the interests of France, as you have done before. In about six months, this vile story will come to an end. I'll send the courier to find you when you will be needed. Farewell, Monsieur de Maure, I was very lucky to meet an honorable man here! The minister and the King will hear of you, that I promise. And they will hear all the best.";
			link.l1 = "Thank you, Baron. Bon Voyage!";
			link.l1.go = "noel_97";
		break;
		
		case "noel_97":
			DialogExit();
			AddQuestRecord("Patria", "86");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload3_back", "none", "", "", "OpenTheDoors", 15.0);
			SetFunctionTimerCondition("Patria_CondotierPuancieFinal", 0, 0, 1, false); // таймер
		break;
		
		case "noel_98":
			dialog.text = "Glad to see you, Vice Admiral. I am here again, as promised. And with me - the first assistant of Minister of Finance, Baron Olivier Bourdin.";
			link.l1 = "Where's Chevalier de Poincy?";
			link.l1.go = "noel_99";
		break;
		
		case "noel_99":
			dialog.text = "Where he's supposed to be, in prison. He was arrested and will be brought to France for investigation and a trial. Given his position, he will certainly avoid the execution, but he can't avoid a huge fine, demotion and, probably, imprisonment.";
			link.l1 = "Was the arrest peaceful?";
			link.l1.go = "noel_100";
		break;
		
		case "noel_100":
			dialog.text = "Not really. The Chevalier had here, in the residence, a whole guard of loyal soldiers. But we were ready for such escalation in advance.";
			link.l1 = "Well then, I congratulate you, baron! Perhaps now you will deal with the French trading Company?";
			link.l1.go = "noel_101";
		break;
		
		case "noel_101":
			dialog.text = "Me? Yes. His grace monsieur Bourdin - will go back to France together with Chevalier de Poincy. And you, vice-admiral, should also expect some changes. Now you have a new position. His grace will tell you more.";
			link.l1 = "...";
			link.l1.go = "noel_102";
		break;
		
		case "noel_102":
			DialogExit();
			LAi_SetActorType(npchar);
			sld = characterFromId("Finansist");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "noel_103":
			dialog.text = "Monsieur de Maure! Wait a minute!";
			link.l1 = "Yes, Baron. I'm listening.";
			link.l1.go = "noel_104";
		break;
		
		case "noel_104":
			dialog.text = "As for the million that you paid to the Stuyvesant... I did not tell the ministry about this, so as to... avoid questions, like how a French officer came into possession of so much money. This may have been harmful to you since they would likely ask you to increase the Kings' treasury with your own.";
			link.l1 = "I understand, thank you.";
			link.l1.go = "noel_105";
		break;
		
		case "noel_105":
			dialog.text = "All the money that was found in possession of Poincy in Casterville was confiscated by baron Bourdin. But, as it turns out, Poincy also had a stash that the English moneylenders were hiding for him. I will talk to him about returning the investments, and then I will find a way to compensate you.";
			link.l1 = "I'm afraid it won't be easy for you to take something from the hands of the English moneylenders.";
			link.l1.go = "noel_106";
		break;
		
		case "noel_106":
			dialog.text = "I agree. But we will work on it, and I will keep you updated on the results.";
			link.l1 = "As you wish.";
			link.l1.go = "noel_107";
		break;
		
		case "noel_107":
			dialog.text = "Vice-admiral, you aren't looking so good, or is it just me? You've only just received the highest position in the colonies!";
			link.l1 = "No-no, not at all... It's just that everything happened so unexpectedly, and I'm a bit lost.";
			link.l1.go = "noel_108";
		break;
		
		case "noel_108":
			dialog.text = "Don't worry. You will get used to your new position. And besides, you were quite successful at being the governor of Saint-Martin for half a year, so it will be nothing new to you.";
			link.l1 = "Oh, I'm sure I'll get used to it. I've been in worse situations during my time here in the Caribbean. I guess I'll manage this one as well.";
			link.l1.go = "noel_109";
		break;
		
		case "noel_109":
			// belamour legendary edition -->
			dialog.text = "Well, fine. In addition, I have one more surprise for you. I'm sure you'll like it. But first I ask you to go back to the residence. I think someone is waiting for us there.";
			link.l1 = "You have intrigued me, Monsieur Forget. Well, let's go back.";
			link.l1.go = "noel_110";
		break;
		
		case "noel_110":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "ToEcliatonAward", -1);
			LAi_SetActorType(pchar);
			LAi_ActorFollow(pchar, npchar, "", -1);
		break;
		
		case "noel_111":
			dialog.text = "It's all right, Marquis. A real captain should always take care of his ship first, right? Charles, do you remember Marquis Hubert Dassier, captain of the battleship 'Eclatant'?";
			link.l1 = "Of course I remember! If not for him I wouldn't be alive today. The strongest friendship between naval officers comes from battles that are fought side by side. And Monsieur Dassier turned out to be an incredibly experienced captain.";
			link.l1.go = "noel_112";
		break;
		
		case "noel_112":
			DialogExit();
			sld = characterFromId("Ecliaton_Cap");
			sld.dialog.currentnode = "ecliaton_cap_17";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "noel_113":
			dialog.text = "Vice Admiral, I have the honor to inform you of the following. In addition to your appointment as an Acting Governor-General of the French colonies in the archipelago, I also raised the issue of your flagship.";
			link.l1 = "Flagship?";
			link.l1.go = "noel_114";
		break;
		
		case "noel_114":
			dialog.text = "Exactly. As far as I know, when you entered the service of France, you were given the light frigate 'Gryffondor' at your disposal. This is a wonderful ship no doubt, but still it is only for an officer, and not for a vice admiral and now, a governor general. You are the face of France here. And your flagship should be appropriate. So we have decided that the ship that went through its first battles here in the Caribbean to be added in your squadron...";
			link.l1 = "Monsieur Forget, are you trying to say...";
			link.l1.go = "noel_115";
		break;
		
		case "noel_115":
			dialog.text = "From now on, the pride of the French Navy, the 66-gun warship 'Eclatant' is at your disposal! This decision is approved by the king!";
			link.l1 = "But Baron, I can't just take...";
			link.l1.go = "noel_116";
		break;
		
		case "noel_116":
			dialog.text = "You can, Charles. This is not to be discussed. In France, the 'Eclatant' was upgraded a bit specifically for you, because, as it turned out, there are no such big naval battles in the Caribbean as in Europe, and therefore the requirements for individual ships are higher. Here everything is decided by the characteristics of the vessel and the experience of its captain. The 'Eclatant' had its hull strengthened, increased deadweight and the crew size, slightly re-equipped the sailing rig to enable it to take sharper courses, and also completely replaced all the cannons with forty-second caliber, these are the strongest cannons that we have.";
			link.l1 = "Yes, now this ship is simply the master of the seas... But Monsieur Forget, because the captain of this ship is Marquis Hubert Dassier. I can't take it from him...";
			link.l1.go = "noel_117";
		break;
		
		case "noel_117":
			dialog.text = "It's just that I haven't told you yet that the Marquis himself has expressed a strong desire to serve under your command... Monsieur Dassier?";
			link.l1 = "...";
			link.l1.go = "noel_118";
		break;
		
		case "noel_118":
			DialogExit();
			sld = characterFromId("Ecliaton_Cap");
			sld.dialog.currentnode = "ecliaton_cap_19";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "noel_119":
			dialog.text = "Yes, Monsieur Dassier, I believe we will not detain you any longer.";
			link.l1 = "...";
			link.l1.go = "noel_120";
		break;
		
		case "noel_120":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorTurnToLocator(pchar, "reload", "reload1");
			sld = characterFromId("Ecliaton_Cap");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "reload", "reload1", "EcliatonAwardNoelTalk", -1);
		break;
		
		case "noel_121":
			dialog.text = "Between us, Charles, I would strongly advise you to leave the Marquis in your service. I assure you, you will not find such an experienced captain.";
			link.l1 = "Believe me, baron, I had the honor to see this personally during the fighting against Spain and Holland. Monsieur Dassier is indeed an excellent combat officer, and also my friend.";
			link.l1.go = "noel_122";
		break;
		
		case "noel_122":
			dialog.text = "Well, now allow me to take my leave, Your Grace, Governor-General! Things do cannot wait: the work of creating a trading company is on the first day of its creation. See you soon!";
			link.l1 = "Good luck, Monsieur Forget. And good luck with your trading endeavors!";
			link.l1.go = "noel_123";
		break;
		
		case "noel_123":
			DialogExit();
			// ставим Эклятон после апгрейда в Европе
			sld = characterFromId("Ecliaton_Cap");
			sld.dialog.currentnode = "ecliaton_cap_24";
			sld.DeckDialogNode = "ecliaton_cap_24";
			sld.Ship.Type = GenerateShipExt(SHIP_ECLIATON, true, sld);
			SetBaseShipData(sld);
			sld.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS42;
			UpgradeShipFull(sld);
			/* UpgradeShipParameter(sld, "SpeedRate");
			UpgradeShipParameter(sld, "TurnRate");
			UpgradeShipParameter(sld, "WindAgainstSpeed");
			UpgradeShipParameter(sld, "HP");
			UpgradeShipParameter(sld, "MaxCrew");
			sld.ship.HP = 11880; */
			sld.Ship.name = "Ecliaton";
			SetCrewQuantityFull(sld);
			AddCrewMorale(sld, 100);
			ChangeCrewExp(sld, "Sailors", 100);
			ChangeCrewExp(sld, "Cannoners", 100);
			ChangeCrewExp(sld, "Soldiers", 100);
			SetCharacterGoods(sld, GOOD_BALLS, 6000);
			SetCharacterGoods(sld, GOOD_GRAPES, 2000);
			SetCharacterGoods(sld, GOOD_KNIPPELS, 2000);
			SetCharacterGoods(sld, GOOD_BOMBS, 5000);
			SetCharacterGoods(sld, GOOD_FOOD, 4000);
			SetCharacterGoods(sld, GOOD_POWDER, 12000);
			SetCharacterGoods(sld, GOOD_WEAPON, 900);
			SetCharacterGoods(sld, GOOD_MEDICAMENT, 900);
			SetCharacterGoods(sld, GOOD_RUM, 200);
			SetCharacterGoods(sld, GOOD_PLANKS, 100);
			SetCharacterGoods(sld, GOOD_SAILCLOTH, 100);
			Group_AddCharacter("Ecliaton_group", "Ecliaton_Cap");
			Group_SetGroupCommander("Ecliaton_group", "Ecliaton_Cap");
			Group_SetAddress("Ecliaton_group", "Nevis", "quest_ships", "quest_ship_1");
			Group_SetTaskNone("Ecliaton_group");
			Group_LockTask("Ecliaton_group");
			
			bDisableFastReload = false;//открыть переход
			bQuestDisableMapEnter = false;//открыть карту
			AddQuestRecord("Patria", "90");
			CloseQuestHeader("Patria");
			DeleteAttribute(pchar, "questTemp.GoldenGirl_Block");	// Разрешаем квест Дороже Золота
			pchar.questTemp.Patria = "end"; // конец линейки
			pchar.questTemp.Patria.GenGovernor = "true"; // Шарль генерал-губернатор
			ChangeCharacterAddressGroup(npchar, "none", "", "");
			DoQuestReloadToLocation("Charles_Town", "reload", "reload3", "OpenTheDoors");
		break;
		// <-- legendary edition
		
		case "noel_final":
			dialog.text = "Allow me to express my sincerest appreciation for you, vice-admiral! You have saved my life by freeing me from those damned pirates. I thank you, as well as Philippe de Poincy. I must admit, I was absolutely wrong in my judgement of him, and I ask you to forgive me for that. You and the Chevalier were right: the French trading Company will have a lot of troubles here, and it looks like we will only lose money here\nOnly experienced people, like Poincy, and such brave soldiers as you, can withstand these wolves that live on every island here. I need to go to the palace, and after that I will leave to Europe as soon as possible, and forget this nightmare.";
			link.l1 = "I'm glad everything ended well, Baron. Goodbye!";
			link.l1.go = "noel_final_1";
		break;
		
		case "noel_final_1":
			DialogExit();
			AddQuestRecord("Patria", "76");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload3_back", "none", "", "", "OpenTheDoors", 15.0);
			SetFunctionTimerCondition("Patria_CondotierPuancieFinal", 0, 0, 1, false); // таймер
		break;
		
		// капитан Эклятона
		case "ecliaton_cap":
			dialog.text = TimeGreeting()+", monsieur. What brings you onto the deck of the 'Eclatant'?";
			link.l1 = TimeGreeting()+", monsieur. Allow me to introduce myself - Captain Charles de Maure, I come from the Governor General of the French colonies in the Archipelago, Chevalier de Poincy. I was ordered to take your ship into my squadron and under my command. Here is the letter...";
			// belamour legendary edition фикс проверки мундира с мушкетом
			if(IsUniformEquip()) link.l1.go = "ecliaton_cap_1";
			else link.l1.go = "ecliaton_cap_no";
		break;
		
		case "ecliaton_cap_no":
			dialog.text = "It's some sort of mistake, monsieur. You are standing on a ship-of-the-line of the French navy, and I only listen to orders issued by those who are in service to the Royal navy. And you do not seem to have any signs or belonging to that fleet. Perhaps, you mistake our ship for another one.";
			link.l1 = "But...";
			link.l1.go = "ecliaton_cap_no_1";
		break;
		
		case "ecliaton_cap_no_1":
			DialogExit();
			npchar.dialog.currentnode = "ecliaton_cap_no_2";
		break;
		
		case "ecliaton_cap_no_2":
			if(IsUniformEquip())
			{
				dialog.text = "Huh, I didn't even recognize you in this uniform, Captain. Well then, let me see your letter, I wish to look through the contents.";
				link.l1 = "Here.";
				link.l1.go = "ecliaton_cap_1";
			}
			else
			{
				dialog.text = "We've already discussed everything, monseigneur...";
				link.l1 = "Hmm...";
				link.l1.go = "ecliaton_cap_no_1";
			}
		break;
		
		case "ecliaton_cap_1":
			RemoveItems(pchar, "Reserve_item_01", 1);
			dialog.text = "Well, let's see... (reading) Interesting. So, me and my ship are to be under your command, Captain de Maure?";
			link.l1 = "That is the order of the Governor General.";
			link.l1.go = "ecliaton_cap_2";
		break;
		
		case "ecliaton_cap_2":
			dialog.text = "Yes-yes, orders are not to be questioned. Very well. Let me introduce myself: I am Marquis Hubert Dassier, Captain of the 66-cannon ship-of-the-line of the French navy named 'Eclatant', along with this well-trained crew, and I swear on my honour, it is one of the best ships that France has ever had.";
			link.l1 = "Glad to hear it, as the task we were assigned by the Governor General will require good knowledge of navigation and artillery.";
			link.l1.go = "ecliaton_cap_3";
		break;
		
		case "ecliaton_cap_3":
			dialog.text = "Will you tell me the details of this upcoming operation?";
			link.l1 = "Of course. We will be moving to the Spanish island of Trinidad, located about a week's travel South-East from here. We will abruptly attack the fort guarding the San Jose colony and run it into the ground. Then, we will talk with the Spanish about our compensation for the recent attack on the French settlement of Saint-Pierre.";
			link.l1.go = "ecliaton_cap_4";
		break;
		
		case "ecliaton_cap_4":
			dialog.text = "I see. When will we depart?";
			link.l1 = "As soon as possible. We have to complete this task in a month, so we have more than enough time.";
			if (GetCompanionQuantity(pchar) > 4) link.l1.go = "ecliaton_cap_5_1";
			else link.l1.go = "ecliaton_cap_5";
		break;
		
		case "ecliaton_cap_5":
			dialog.text = "Alright, Captain de Maure. We will depart on your command.";
			link.l1 = "";
			link.l1.go = "ecliaton_cap_6";
		break;
		
		case "ecliaton_cap_6":
			DialogExit();
			npchar.dialog.currentnode = "ecliaton_cap_wait";
			npchar.DeckDialogNode = "ecliaton_cap_wait";
			Patria_AddEcliaton();
		break;
		
		case "ecliaton_cap_wait":
			dialog.text = "Do you have any orders, or perhaps questions, Captain de Maure?";
			link.l1 = "Not yet...";
			link.l1.go = "ecliaton_cap_wait_1";
		break;
		
		case "ecliaton_cap_wait_1":
			DialogExit();
			npchar.dialog.currentnode = "ecliaton_cap_wait";
			npchar.DeckDialogNode = "ecliaton_cap_wait";
		break;
		
		case "ecliaton_cap_5_1":
			dialog.text = "But, Captain de Maure, first you have to make your squadron smaller - my ship cannot join you, or it will be too largeof a squadron.";
			link.l1 = "Huh. You're right. I will leave one ship here in the harbour.";
			link.l1.go = "ecliaton_cap_5_2";
		break;
		
		case "ecliaton_cap_5_2":
			DialogExit();
			npchar.dialog.currentnode = "ecliaton_cap_5_3";
		break;
		
		case "ecliaton_cap_5_3":
			if (GetCompanionQuantity(pchar) > 4)
			{
				dialog.text = "Haven't you yet made your squadron smaller, monsieur?";
				link.l1 = "Yes-yes, I remember, I'm working on it.";
				link.l1.go = "ecliaton_cap_5_2";
			}
			else
			{
				dialog.text = "So, the 'Eclatant' is ready to join your squadron, monsieur.";
				link.l1 = "Then I will go to my ship, and you should prepare to enter the sea.";
				link.l1.go = "ecliaton_cap_5";
			}
		break;
		
		case "ecliaton_cap_7":
			dialog.text = "Greetings, Commodore. Do we have another battle ahead of us?";
			link.l1 = "Indeed we do. Once again we will join forces. We are going to storm Philipsburg. The Governor General has tasked us with clearing out the Dutch from Saint-Martin.";
			link.l1.go = "ecliaton_cap_9";
			link.l2 = "We do Captain, but a bit later. I will tell you when. The 'Eclatant' has to be ready to enter the sea at any minute.";
			link.l2.go = "ecliaton_cap_8";
		break;
		
		case "ecliaton_cap_8":
			DialogExit();
			npchar.dialog.currentnode = "ecliaton_cap_7";
			npchar.DeckDialogNode = "ecliaton_cap_7";
		break;
		
		case "ecliaton_cap_9":
			dialog.text = "Everything is clear. It will be a hard mission, monseigneur. As far as I have heard the fort of Philipsburg has a lot of cannons.";
			link.l1 = "I'm sure of it my friend, but we will manage. Prepare to enter the sea, we are departing soon.";
			link.l1.go = "ecliaton_cap_10";
		break;
		
		case "ecliaton_cap_10":
			DialogExit();
			npchar.dialog.currentnode = "ecliaton_cap_wait";
			npchar.DeckDialogNode = "ecliaton_cap_wait";
			Patria_BastionAddEcliaton();
		break;
		
		case "ecliaton_cap_11":
			dialog.text = "Glad to see you on the deck of the 'Eclatant', vice-admiral! What are your orders?";
			link.l1 = "Prepare the 'Eclatant' for the departure. First, we will sail to the coast of Jamaica, and then, together with Colonel D'Oyley's squadron, we shall attack Curacao.";
			link.l1.go = "ecliaton_cap_13";
			link.l2 = "There will be orders, Captain, but later. I will tell you when. The 'Eclatant' has to be ready to enter the sea at any minute.";
			link.l2.go = "ecliaton_cap_12";
		break;
		
		case "ecliaton_cap_12":
			DialogExit();
			npchar.dialog.currentnode = "ecliaton_cap_11";
			npchar.DeckDialogNode = "ecliaton_cap_11";
		break;
		
		case "ecliaton_cap_13":
			dialog.text = "The 'Eclatant' and its crew are ready, Vice Admiral!";
			link.l1 = "Excellent. Then we depart immmediately.";
			link.l1.go = "ecliaton_cap_14";
		break;
		
		case "ecliaton_cap_14":
			DialogExit();
			npchar.dialog.currentnode = "ecliaton_cap_wait";
			npchar.DeckDialogNode = "ecliaton_cap_wait";
			Patria_CuracaoAddEcliaton();
		break;
		
		// belamour legendary edition -->
		case "ecliaton_cap_15":
			dialog.text = "Excuse me gentlemen, I couldn't join you earlier I was preoccupied with giving the orders on the ship. I already thought that I was quite late, because I did not find you at the residence, and therefore I was going to return to the ship...";
			link.l1 = "...";
			link.l1.go = "ecliaton_cap_16";
		break;
		
		case "ecliaton_cap_16":
			DialogExit();
			Lai_SetPlayerType(pchar);
			sld = characterFromId("Noel");
			sld.dialog.currentnode = "noel_111";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "ecliaton_cap_17":
			dialog.text = "It was an honor for me to fight alongside you, Monsieur de Maure! I must say that I rarely meet such competent and skillful officers such as you. I'm sure I myself could not have dealt with the fort of that Spanish colony in Trinidad so quickly!";
			link.l1 = "You underestimate yourself, Monsieur Dassier. We dealt with it together.";
			link.l1.go = "ecliaton_cap_18";
		break;
		
		case "ecliaton_cap_18":
			DialogExit();
			sld = characterFromId("Noel");
			sld.dialog.currentnode = "noel_113";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "ecliaton_cap_19":
			dialog.text = "That's right. Although I am a marquis, I am still a sailor. For me, the Caribbean archipelago is new, unexplored and full of new adventures. Last time I was here for only a few months, but when I returned to Europe, I started missing this place. I would like to serve our Fatherland here. And you are a very talented and experienced captain, you managed to win my sincere respect and my friendship. I would be honored to serve under your command, Vice Admiral!";
			link.l1 = "Well, I can't and what's more! - I don't want to refuse you, Monsieur Dassier!";
			link.l1.go = "ecliaton_cap_20";
		break;
		
		case "ecliaton_cap_20":
			dialog.text = "I also understand that the Eclatant is now your flagship, so I will understand perfectly if you decide to take command of it personally. In that case, you can leave me as your officer, give me another ship, or simply relieve me of my duties - Monsieur Forget kindly promised me that then he would find me a worthy position in the fleet of the French West India Company.";
			link.l1 = "I can assure you my friend, that it won't come to that. You are one of the best captains that I have ever met, and with you by my side we will be unstoppable.";
			link.l1.go = "ecliaton_cap_21";
		break;
		
		case "ecliaton_cap_21":
			dialog.text = "Thank you for such a flattering assessment of my abilities. And one more thing, Vice Admiral. I don't know the size of your squadron at the moment, so just in case, I'll be waiting for you on the captain's bridge of the Eclatant in the pier of Capsterville. As soon as you decide to take the ship under your command - just let me know.";
			link.l1 = "Very well, Monsieur Dassier.";
			link.l1.go = "ecliaton_cap_22";
		break;
		
		case "ecliaton_cap_22":
			dialog.text = "Then I ask for a permission to bow out. Vice Admiral, Baron...";
			link.l1 = "See you soon, Monsieur Dassier.";
			link.l1.go = "ecliaton_cap_23";
		break;
		
		case "ecliaton_cap_23":
			DialogExit();
			sld = characterFromId("Noel");
			sld.dialog.currentnode = "noel_119";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
	
		case "ecliaton_cap_24":
			dialog.text = "Vice Admiral, welcome aboard. Would you like to take Eclatant under your command?";
			if (GetCompanionQuantity(pchar) > 4)
			{
				
				link.l1 = "Not yet, Marquis. Wait for orders.";
				link.l1.go = "ecliaton_cap_24_1";
			}
			else
			{
				link.l1 = "Yes, Marquis, I ask you to join my squadron. This beautiful ship will be a symbol of the greatness and power of France in the Caribbean!";
				link.l1.go = "ecliaton_cap_25";
			}
		break;
		
		case "ecliaton_cap_24_1":
			DialogExit();
			npchar.dialog.currentnode = "ecliaton_cap_24";
			npchar.DeckDialogNode = "ecliaton_cap_24";
		break;
		
		case "ecliaton_cap_25":
			dialog.text = "I couldn't agree more, your Excellency!";
			link.l1 = "... Now, let's see what we are truly capable of!";
			link.l1.go = "ecliaton_cap_26";
		break;
		
		case "ecliaton_cap_26":
			DialogExit();
			DeleteAttribute(npchar, "ShipHideImmortal");
			SetCharacterRemovable(npchar, true);
			npchar.CompanionEnemyEnable = true; 
			npchar.Dialog.Filename = "Enc_Officer_dialog.c";
			npchar.Dialog.CurrentNode = "hired";
			npchar.DeckDialogNode = "hired";
			SetCompanionIndex(pchar, -1, sti(npchar.index));
			npchar.Payment = true;
			npchar.loyality = MAX_LOYALITY;
			npchar.OfficerWantToGo.DontGo = true;
			
			// удаление группы Эклятона, иначе клон-призрак
			pchar.quest.Patria_EcliatonDelGroup.win_condition.l1 = "ExitFromSea";
			pchar.quest.Patria_EcliatonDelGroup.function = "Patria_EcliatonDelGroup";
		break;
		// <-- legendary edition
		
		// д'Ойли на Антигуа
		case "doily":
			if (CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "end" && colonies[FindColony("Pirates")].nation == PIRATE)
			{
				PlaySound("Voice\English\LE\Doily\Edvard_Doily_01.wav");
				dialog.text = "Oh, what an acquaintance! Isn't it Captain Charles de Maure himself?! I've heard, you now have a position in the French navy. What a surprise, considering who you were, let's say, 'working' for previously...";
				link.l1 = "Greetings, sir. Are you talking about the affair with Isla Tesoro? Oh, but it wasn't me who wrote the English laws, according to which the island was passed down to the heir of the explorer who found it, according to his will. So, I am not guilty of that, I only helped Miss Sharp to get what was hers by rights.";
				link.l1.go = "doily_1";
			}
			else
			{
				dialog.text = TimeGreeting()+", Captain. I suppose, the representative of the French navy has arrived at Antigua with an important goal in mind?";
				link.l1 = "Indeed, sir. I was sent here by the Governor General of the French colonies, Philippe de Poincy. Saint-Christopher has been besieged by the Spanish and Dutch navy squadrons. The Chevalier asks for help from you and sir Jonathan Fox as well. Here is his letter for you, colonel.";
				link.l1.go = "doily_3";
			}
		break;
		
		case "doily_1":
			dialog.text = "I'm wondering, Captain, how much money did you make off of this? I suppose, quite a lot, since you've managed to pay for the services of the rogue Loxley, which are not cheap at all. I'm sure, the pirate barons pay you deductions regularly for keeping the island in their possession. We both know perfectly well that Helen Sharp is only a mask.";
			link.l1 = "Colonel, we both also know that the pirate barons mostly operate in the interests of England, not officially, mind you... Without them, it would be quite hard to resist the hegemony of the Spanish in the region, wouldn't you agree? So, from the point of view of the politicians, the fact that the Brethren of the Coast has kept the island to themselves, was perhaps, even more profitable then if Isla Tesoro had become an English naval base...";
			link.l1.go = "doily_2";
		break;
		
		case "doily_2":
			dialog.text = "This is arguably true, Captain, but... be that as it is. You've arrived at Antigua with some important goal, I suppose? Perhaps it has to do with the fact that the relations of two former allies - France and Holland, have worsened considerably?";
			link.l1 = "Quite right. I was sent by the governor-general of the French colonies, Philippe de Poincy. Saint-Christopher has been besieged by the Spanish and Dutch navy. The Chevalier asks for your help. Here is his letter to you, colonel.";
			link.l1.go = "doily_3";
		break;
		
		case "doily_3":
			RemoveItems(pchar, "Reserve_item_01", 1);
			dialog.text = "Let me see... (reading)";
			link.l1 = "";
			link.l1.go = "doily_3_1";
		break;
		
		case "doily_3_1":
			LAi_Fade("", "");
			dialog.text = "Hmm... very intriguing! Captain, your commander knows how to pique my interest, it isn't that unusual for people to call him a cunning fox. We should have done this long ago, instead of trying to befriend the Dutch. As we know very well what the Dutch Company and their Director stand for. Well then, I think that in this situation we really shouldn't deny helping to the besieged Casterville, and we have more than enough troops to allow it.\nWhat are the numbers and types of ships in their squadrons, Captain?";
			link.l1 = "I've counted six ships: one eighty-cannon ship-of-the-line of the third rank and five ships of the fourth. They might also have frigates and galleons.";
			link.l1.go = "doily_4";
		break;
		
		case "doily_4":
			dialog.text = "Hmm... We can put forward our squadron, consisting of a hundred-cannon ship of the first rank, two ships of the fourth and a heavy frigate, against theirs.";
			if (!CheckAttribute(pchar, "questTemp.Patria.FailLugger"))
			{
				link.l1 = "Sir, we also have a 66-cannon warship, the 'Eclatant', sailing to the help of Saint-Christopher defense from the coast of Guadeloupe.";
				link.l1.go = "doily_5";
			}
			else
			{
				link.l1 = "A ship of the first rank will be of great help in the upcoming battle.";
				link.l1.go = "doily_5_1";
			}
		break;
		
		case "doily_5":
			dialog.text = "Perfect. In that case, we are well above our enemies' firing capability. The victory shall be ours.";
			link.l1 = "And let us not forget of my own ship, sir. I am not going to miss such a battle, don't even consider it.";
			link.l1.go = "doily_6";
		break;
		
		case "doily_5_1":
			dialog.text = "That is true. Including the help from the fort of Casterville, the victory shall be ours.";
			link.l1 = "And let us not forget of my own ship, sir. I am not going to miss such a battle, don't even consider it.";
			link.l1.go = "doily_6";
		break;
		
		case "doily_6":
			dialog.text = "Of course, monsieur de Maure. Whatever the case may be, tales of your talents in sailing can be heard throughout the archipelago. Your flagship will lead the squadron.";
			if (GetCompanionQuantity(pchar) > 1)
			{
				link.l1 = "I will put the rest of the ships from my squadron on hold, then come back to you, and we will rush to the help of the besieged.";
				link.l1.go = "doily_7_1";
			}
			else
			{
				link.l1 = "I will prepare my ship shortly, and we will rush to the help of the besieged.";
				link.l1.go = "doily_8";
			}
		break;
		
		case "doily_7_1":
			DialogExit();
			npchar.dialog.currentnode = "doily_7_2";
		break;
		
		case "doily_7_2":
			dialog.text = "So, are you ready for departure?";
			if (GetCompanionQuantity(pchar) > 1)
			{
				link.l1 = "Wait just a little bit, sir.";
				link.l1.go = "doily_7_1";
			}
			else
			{
				link.l1 = "Yes, sir.";
				link.l1.go = "doily_8";
			}
		break;
		
		case "doily_8":
			dialog.text = "Then let us begin, and may God help us!";
			link.l1 = "...";
			link.l1.go = "doily_9";
		break;
		
		case "doily_9":
			DialogExit();
			npchar.dialog.currentnode = "doily_10";
			chrDisableReloadToLocation = true;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", -1);
			AddQuestRecord("Patria", "42");
			Patria_SiegeAddEngSquadron();
		break;
		
		case "doily_10":
			dialog.text = "Do you have any further questions, sir?";
			link.l1 = "No, colonel...";
			link.l1.go = "doily_11";
		break;
		
		case "doily_11":
			DialogExit();
			npchar.dialog.currentnode = "doily_10";
			npchar.DeckDialogNode = "doily_10";
		break;
		
		case "doily_12":
			PlaySound("Voice\English\LE\Doily\Edvard_Doily_02.wav");
			dialog.text = "Get the letter for the Stuyvesant, sir. If you're not aware of who I am, let me introduce myself: Colonel Edward Doily, governor of Port-Royal and commander of this expedition!\nTo tell you the truth, I have a great urge to run the bandit hideout known as Willemstad into the ground. The most vile, two-faced and despicable organisation in the Caribbean, known as the Dutch West-Indies trading Company who think that all trade in the Archipelago is exclusively their right, and who hire the likes of Jacob van Berg and other pirates to capture and sink the ships of English merchants...";
			link.l1 = "...";
			link.l1.go = "doily_13";
		break;
		
		case "doily_13":
			dialog.text = "I am here to put an end to these outrageous acts, and, luckily for you, I propose a diplomatic way. For now... But if the director of this abominable organisation doesn't arrive here for the talks, I will run his business into the ground. After we storm the city, I will leave only cinders behind, and any powder that we find, we will put into the basement of your fort, and blow it up. The same fate will await your plantations, and the Stuyvesant himself will hang on the yardarm of my flagship...";
			link.l1 = "...";
			link.l1.go = "doily_14";
		break;
		
		case "doily_14":
			dialog.text = "You will need more than a year to rebuild your colony, and then you will have no time for your schemes and plots. Tell your 'Mynheer Director' everything that I've just said, and don't think these are jokes and empty promises. I've run out of patience, so you must understand me perfectly. Do you understand, Officer?!";
			link.l1 = "Everything is perfectly clear, sir Colonel.";
			link.l1.go = "doily_15";
		break;
		
		case "doily_15":
			dialog.text = "Great. Then leave. I give you exactly one day to think this over. If after twenty-four hours Peter Stuyvesant will not be standing here like you are right now, let him blame that on himself.";
			link.l1 = "...";
			link.l1.go = "doily_16";
		break;
		
		case "doily_16":
			DialogExit();
			LAi_SetStayType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			bDisableCharacterMenu = false;//лоченые интерфейсы
			sld = characterFromId("Doily_land");
			sld.dialog.currentnode = "doily_17";
			LAi_SetActorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "doily_17":
			dialog.text = "I think that ratchet dog Stuyvesant will come here. And if not - he can only blame himself!";
			link.l1 = "...";
			link.l1.go = "doily_17_1";
		break;
		
		case "doily_17_1":
			DialogExit();
			npchar.dialog.currentnode = "doily_17";
			AddQuestRecord("Patria", "63");
			Patria_CuracaoParlamenterGo();
		break;
		
		case "doily_18": // д'Ойли на берегу
			dialog.text = "You've done a good job with the fort, monsieur de Maure. Now we will approach the city gates by land. I will take the cannons from here, the path here is shorter and easier, and you will disembark the company of your marines on the Santa-Maria Cape and move to Willemstad. If you meet enemies on the way, you know what to do. Nobody can be left behind us.";
			link.l1 = "Of course, colonel. I will meet you at the gates!";
			link.l1.go = "doily_19";
		break;
		
		case "doily_19":
			DialogExit();
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			AddQuestRecord("Patria", "61");
			npchar.dialog.currentnode = "doily_10";
			Patria_CuracaoGotoMarch();
		break;
		
		case "doily_20":
			dialog.text = "Well then, it seems like our mission has ended quite successfully. Congratulations, Captain! Oh, excuse me - Vice Admiral! Let's go back on the ships. I will tell my men to stand guard - that fool Stuyvesant will likely not risk attacking us while we retreat, but it won't hurt to be careful.";
			link.l1 = "I'm sure the Dutch will not dare break a treaty that was just signed.";
			link.l1.go = "doily_21";
		break;
		
		case "doily_21":
			dialog.text = "It was a pleasure working with you, monsieur de Maure. I think we will meet once again in Port-Royal or Capsterville.";
			link.l1 = "Without a doubt, colonel. Now, let's tell our men to retreat.";
			link.l1.go = "doily_22";
		break;
		
		case "doily_22":
			DialogExit();
			AddQuestRecord("Patria", "64");
			Patria_CuracaoClear();
		break;
		
		case "doily_23":
			dialog.text = "It seems, the Dutch have finally learned that they have no way to approach us from the fort by that narrow path under our artillery fire. And the ones stuck in the city will likely not risk a sortie, unless they are completely mad. Now we will sow some panic: let's bomb the city with our cannons. The men on my ship will see it and they'll make it look like they're preparing to disembark. After an hour or two, Stuyvesant will shit his pants and will be ready to send the truce envoys.";
			link.l1 = "Everything is going according to our plan, colonel! Let's do it!";
			link.l1.go = "doily_24";
		break;
		
		case "doily_24":
			DialogExit();
			Patria_CuracaoTownBombing();
		break;
		
		// голландский парламентёр под стенами Виллемстада
		case "holoff":
			dialog.text = "I've arrived here to begin the negotiations. What are your demands?";
			link.l1 = "We demand a meeting with the Company's Director, Peter Stuyvesant. Specifically, we want to talk about the fact that due to his company's fault, as well as his own, Willemstad is currently under threat of destruction.";
			link.l1.go = "holoff_1";
		break;
		
		case "holoff_1":
			dialog.text = "Very well, I'll tell mynheer Stuyvesant about this, and we will arrange a safe route into the city for your delegation...";
			link.l1 = "And what about a safe exit?";
			link.l1.go = "holoff_2";
		break;
		
		case "holoff_2":
			dialog.text = "I don't understand, mynheer?";
			link.l1 = "I said: will you arrange a safe exit from the city for us? I'm not sure about that. I'm afraid, mynheer Stuyvesant may just decide to take our envoys into captivity. For this reason, I invite mynheer Stuyvesant to appear right here for the negotiations.";
			link.l1.go = "holoff_3";
		break;
		
		case "holoff_3":
			dialog.text = "But...";
			link.l1 = "Officer, we dictate the conditions here. Your fleet is destroyed, the garrison cut off from the city, and we will penetrate Willemstad's defense like a fregate penetrates a rowboat if we decide to storm the city. Now, you will receive a letter for mynheer Stuyvesant, and you will give it to him along with our invitation...";
			link.l1.go = "holoff_4";
		break;
		
		case "holoff_4": // перекидываем pchar на офицера и говорим с д'Ойли
			DialogExit();
			LAi_SetActorType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Curacao_parlamenter_1"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Doily_land");
			sld.dialog.currentnode = "doily_12";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
			bDisableCharacterMenu = true;//лоченые интерфейсы
		break;
		
		// офицер-испанец на маяке Тринидада
		case "SanJoseSpanish":
			dialog.text = "So, Captain, you've called the truce envoys because you wanted to dictate your demands?";
			link.l1 = "You are absolutely correct, senor. Let me briefly explain to you my reason for arriving in Trinidad - this is our answer for your recent attack on Saint-Pierre. You've damaged the city considerably, and now you will be forced to compensate it. The price of compensation is three hundred thousand Peso. And that is not so much, considering the vile acts your soldiers have committed on Martinique.";
			link.l1.go = "SanJoseSpanish_1";
		break;
		
		case "SanJoseSpanish_1":
			dialog.text = "Excuse me, senor, but what does San Jose have to do with Saint-Pierre? Why does our colony have to pay?";
			link.l1 = "Because the attackers were Spanish, not Dutch or English. Then you will put the bill on Providence for Don de Mendosa, along with my sincerest greetings. As you understand, in case you refuse to pay the compensation, I will order my men to disembark, and then San Jose will lose much more. I'm sure your colony's governor will make the right decision. You have one day to respond. I wish you all the best, senores.";
			link.l1.go = "SanJoseSpanish_2";
		break;
		
		case "SanJoseSpanish_2":
			DialogExit();
			npchar.dialog.currentnode = "SanJoseSpanish_3";
			Patria_SanJoseMayakSpanishGo();
		break;
		
		case "SanJoseSpanish_3":
			dialog.text = "";
			link.l1 = "So, as I understand, the governor has made the right decision?";
			link.l1.go = "SanJoseSpanish_4";
		break;
		
		case "SanJoseSpanish_4":
			AddMoneyToCharacter(pchar, 300000);
			dialog.text = "Get your three hundred thousand and get out of our colony.";
			link.l1 = "Excellent, senores. I assure you - this was the best way. I hope this will discourage the Don de Mendosa and others from attacking our colonies. Don't forget to send the message to Providence and him personally. I wish you well, gentlemen.";
			link.l1.go = "SanJoseSpanish_5";
		break;
		
		case "SanJoseSpanish_5":
			DialogExit();
			Patria_SanJoseMayakSpanishFin();
		break;
		
		// вестовой на 5 задание
		case "fraofficer":
			dialog.text = "Captain Charles de Maure, allow me to report: Chevalier Philippe de Poincy wanted to notify you that Baron Noel Forget is ready to depart for Saint-Martin and will await you on the pier.";
			link.l1 = "Excellent! Thank you, monsieur.";
			link.l1.go = "fraofficer_1";
		break;
		
		case "fraofficer_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "", 10.0);
			Patria_SanMartinSetBaron();
		break;
		
		case "fraofficer_2":
			dialog.text = "Captain Charles de Maure! The Governor General is calling for you right now. A mighty enemy squadron has appeared at the coast of Saint-Christopher!";
			link.l1 = "Then let us waste no time!";
			link.l1.go = "fraofficer_3";
		break;
		
		case "fraofficer_3":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "", 10.0);
			chrDisableReloadToLocation = false;
			Patria_SiegeHovernor();
		break;
		
		// патруль у рудника
		case "engofficer":
			dialog.text = "Who are you? What are you doing here?";
			link.l1 = "Uhh...";
			link.l1.go = "engofficer_1";
		break;
		
		case "engofficer_1":
			dialog.text = "No strangers are allowed to enter here! Who are you, spies? I'll bring you to the commandant's office, they'll deal with you.";
			link.l1 = "But we can't go to the commandant's office...";
			link.l1.go = "engofficer_2";
		break;
		
		case "engofficer_2":
			dialog.text = "If you won't go yourself - we'll just have to drag you by force! Hand over you weapons!";
			link.l1 = "No deal...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Patria_CondotierBeachFight");
		break;
		
		// бывший управляющий рудника
		case "miner":
			dialog.text = "";
			link.l1 = "So, is everything clear?";
			link.l1.go = "miner_1";
		break;
		
		case "miner_1":
			dialog.text = "Yes, monsieur. The letter is to be handed personally to mynheer Peter Stuyvesant or Mathias Beck.";
			link.l1 = "I'm sure you won't have trouble finding a ship from Willemstad to Cartagena. We gave you all the necessary funds to pay for the trip and for accommodation. And in case you need to - you will confirm your reports in front of the French commission half a year from now?";
			link.l1.go = "miner_2";
		break;
		
		case "miner_2":
			dialog.text = "Monsieur, I'm loyal to my word.";
			link.l1 = "Very well. Then I wish you luck. This path leads to Willemstad, follow it. It's not far from here.";
			link.l1.go = "miner_3";
		break;
		
		case "miner_3":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "Patria_CondotierOnCuracaoWait", 15.0);
			AddQuestRecord("Patria", "82");
			ReleasePrisoner(npchar);
		break;
		
		// курьер в Капстервиль
		case "cureer":
			dialog.text = "Vice-admiral Charles de Maure, right?";
			link.l1 = "Precisely. Who do I have the honour of speaking with?";
			link.l1.go = "cureer_1";
		break;
		
		case "cureer_1":
			dialog.text = "I have a message to you from Baron Noel Forget. He told you to come to the governor's palace at Casterville as soon as possible.";
			link.l1 = "Oh! Great news! Thank you, I will depart immediately!";
			link.l1.go = "cureer_2";
		break;
		
		case "cureer_2":
			DialogExit();
			chrDisableReloadToLocation = false;
			Patria_EuropePrepare();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 10.0);
		break;
		
		case "burden":
			dialog.text = "Greetings, vice-admiral. Baron Forget told me stories about you. A lot of stories. I give you my sincerest thanks for your loyal and brilliant service for the good of France in the colonies, as well as for your help in uncovering the schemes of the swindler de Poincy. Now, me and the Minister of Finance will deal with him personally, and you will take the place of your former commander. At least, for the time being.";
			link.l1 = "But...";
			link.l1.go = "burden_1";
		break;
		
		case "burden_1":
			dialog.text = "No 'buts', vice-admiral! This decision has already been made and approved by the King. I have here an order signed by him personally about assigning you as the de facto Governor General of the French colonies in the Archipelago. We have no better candidates for this position. Your outstanding experience in warfare, your knowledge of the region and the people that are responsible for everything here, your skills and talents are all worthy of this high and respectable position. If I may be honest with you, I expect that after some time you will be assigned to this position once again, without the 'de facto' part.";
			link.l1 = "But I dreamed of going back to Paris...";
			link.l1.go = "burden_2";
		break;
		
		case "burden_2":
			dialog.text = "France needs you here! The Minister of Finance is gathering a navy in Europe right now, and our presence here, in the Archipelago, will also not go unnoticed. Your main task will be to strengthen and fortify the colonies and increase the military power of our fleet, while Baron Forget and the French West-Indies trade Company will focus on the trading and domestic development! And who else, if not you, can help prepare the French navy?\nSo, start working, Governor General! I know you don't like sitting in a room all day, but your task doesn't even require it!";
			link.l1 = "At once, your Grace! Orders are not to be questioned!";
			link.l1.go = "burden_3";
		break;
		
		case "burden_3":
			dialog.text = "I'm glad you've understood me correctly. And I will also ask you to pay a visit to the Chevalier de Poincy: he insisted on meeting you. We can't deny him such pleasure before his departure for Paris, can we? You will find him in the prison.";
			link.l1 = "Very well, your Grace...";
			link.l1.go = "burden_4";
		break;
		
		case "burden_4":
			DialogExit();
			DoQuestReloadToLocation("Charles_prison", "goto", "goto19", "Patria_EuropePuancieInPrison");
		break;
		
		// Портной Пуанси Xenon
		case "Tailor":
			dialog.text = "...will stall, you understand? I ordered these materials several months ago!";
			link.l1 = "...";
			link.l1.go = "Tailor_01";
			CharacterTurnByChr(npchar, characterFromId("Charles_PortMan"));
		break;
		
		case "Tailor_01":
			DialogExit();
			sld = characterFromId("Charles_PortMan");
			sld.dialog.currentnode = "Tailor";
			LAi_SetActorType(pchar);
			LAi_ActorDialogNow(pchar, sld, "", -1);
		break;
		
		case "Tailor_02":
			dialog.text = "And how did they prioritize what to carry on the first ship and what on the second?! I'm not just some seamstress from the boondocks - I even have an order from the governor-general, his Excellency chevalier de Poincy!";
			link.l1 = "...";
			link.l1.go = "Tailor_03";
			CharacterTurnByChr(npchar, characterFromId("Charles_PortMan"));
		break;
		
		case "Tailor_03":
			DialogExit();
			Lai_SetPlayerType(pchar);
			sld = characterFromId("Charles_PortMan");
			sld.dialog.currentnode = "Tailor_02";
			LAi_SetActorType(pchar);
			LAi_ActorDialogNow(pchar, sld, "", -1);
		break;
		
		case "Tailor_04":
			dialog.text = "Well, what else can I do now... I'll wait. But know this: I won't be held responsible for unfulfilled orders!";
			link.l1 = "Greetings. I see you've got trouble?";
			link.l1.go = "Tailor_05";
			CharacterTurnByChr(npchar, characterFromId("Charles_PortMan"));
		break;
		
		case "Tailor_05":
			dialog.text = "Trouble? That's putting it mildly! Oh, I think I recognize you... You're the new vice admiral, correct?";
			link.l1 = "Quick on the uptake. That's correct, before you stands the second man in the French colonies, Vice Admiral of the French fleet, Charles de Maure.";
			link.l1.go = "Tailor_06";
			link.l2 = "Drop these formalities, we're not on a ship. And don't worry, I won't call the guards just because you didn't recognize me right away. Just call me Charles de Maure.";
			link.l2.go = "Tailor_07";
			CharacterTurnByChr(npchar, pchar);
		break;
		
		case "Tailor_06":
			AddCharacterExpToSkill(pchar, "Leadership", 300);//харизма
			dialog.text = "Your Excellency, please forgive me for not recognizing you immediately! Yes, you are correct, I've encountered unforeseen circumstances.";
			link.l1 = "And what would those circumstances be? As I understand it, they didn't bring you materials from Paris?";
			link.l1.go = "Tailor_08";
		break;
		
		case "Tailor_07":
			AddCharacterExpToSkill(pchar, "Fortune", 300);//везение
			dialog.text = "Oh, thank you very much. You're right, I've encountered unforeseen circumstances, which is why I didn't immediately realize who was in front of me.";
			link.l1 = "And what would those circumstances be? As I understand it, they didn't bring you materials from Paris?";
			link.l1.go = "Tailor_08";
		break;
		
		case "Tailor_08":
			dialog.text = "Yes, that's correct. I ordered them several months ago. The governor signed the order for your appointment back then and insisted that I prepare all the necessary materials for a new admiral's uniform, confident that it would be approved in the metropolis.";
			link.l1 = "And the materials were not delivered, I presume?";
			link.l1.go = "Tailor_09";
		break;
		
		case "Tailor_09":
			dialog.text = "magine that! I explained how important it was, placed the order... But they got more urgent shipments to take care of! What am I to do? Make my orders a year in advance, hoping they will deign to bring me the materials?";
			link.l1 = "What exactly are you missing? Maybe it can be obtained in the Caribbean?";
			link.l1.go = "Tailor_10";
		break;
		
		case "Tailor_10":
			dialog.text = "Even if it's possible, I have no idea where... You won't find good materials here. Although... I could use your old officer's jacket as a base, if you allow. You probably won't need it once you have an admiral's uniform, right?";
			link.l1 = "If I have an admiral's uniform, then of course, I won't need a simple officer's jacket. What else?";
			link.l1.go = "Tailor_11";
		break;
		
		case "Tailor_11":
			dialog.text = "I need to find cufflinks and a collar for the uniform. Usually, I order them directly from Parisian workshops. Even if they are very basic, I can alter them and give them a more presentable look. Though in that case, I'll need more of them...";
			link.l1 = "Since there are no Parisian workshops in the Caribbean, I'll find you a whole batch of local clothing with detachable collars and cuffs. What else?";
			link.l1.go = "Tailor_12";
		break;
		
		case "Tailor_12":
			dialog.text = "For the finishing touches, I need very high-quality fabrics. I do have a spinner who can make such fabric even from coarse fiber. But for that, I need material - ideally cotton. One bale will be more than enough.";
			link.l1 = "That can be obtained as well. What's next?";
			link.l1.go = "Tailor_13";
		break;
		
		case "Tailor_13":
			dialog.text = "They were supposed to deliver an admiral's tricorne from Paris, but I can make it myself if I have the material. While the tricorne for you was supposed to be a fabric one, leather would be better for the salty winds and scorching sun of the Caribbean. It would last longer.";
			link.l1 = "I'll get you the leather; don't worry. I won't even have to chase bulls through the jungles of Espanola. Is that all?";
			link.l1.go = "Tailor_14";
		break;
		
		case "Tailor_14":
			dialog.text = "They were also supposed to deliver top-quality silk from Lyon. It's light, breathable, easily absorbs moisture, and dries even faster. And most importantly, it doesn't stretch and maintains its shape.";
			link.l1 = "Yes, I understand what silk you're talking about. That might be harder to get in the colonies though.";
			link.l1.go = "Tailor_15";
		break;
		
		case "Tailor_15":
			dialog.text = "That's it for the materials. I've also heard that you were presented with the highest award of France... The Order of Saint Louis should not be worn like some trinket on your belt. It has its place. So, please bring it to me, and I'll sew it on as it should be.";
			link.l1 = "Alright, I'll bring it too. Just don't lose it!";
			link.l1.go = "Tailor_16";
		break;
		
		case "Tailor_16":
			dialog.text = "Certainly not! I'll guard it with my life!";
			link.l1 = "Alright then. If that's all, I'll go get the materials.";
			link.l1.go = "Tailor_17";
		break;
		
		case "Tailor_17":
			dialog.text = "There's one more thing... My tailoring tools have become unusable. I ordered new ones from Paris, but alas... If you could find all the necessary materials and lend me the tools, if you have them - just lend, I'll get new ones later! - I'd immediately start sewing.";
			link.l1 = "Well, what can I do? I'll bring you everything you need. Where can I find you? You won't be waiting for me in the port authority, will you?";
			link.l1.go = "Tailor_18";
		break;
		
		case "Tailor_18":
			dialog.text = "My workshop is located in the building right at the pier - when you go ashore, it will be on your right.";
			link.l1 = "Deal. I'll get you the materials.";
			link.l1.go = "Tailor_19";
		break;
		
		case "Tailor_19":
			DialogExit();
			AddQuestRecord("Patria", "65_1");
			chrDisableReloadToLocation = false;
			ChangeCharacterAddressGroup(npchar, "Charles_houseS3", "barmen", "Stay");
			npchar.dialog.currentnode = "Tailor_20";
			LAi_SetOwnerType(npchar);
			pchar.questTemp.PatriaTailor = true;
		break;
		
		case "Tailor_20":
			dialog.text = "Greetings, vice admiral! Have you brought everything necessary for your new uniform?";
			link.l1 = "Not yet, I haven't had the time. Hold on, I'll get everything.";
			link.l1.go = "Tailor_20_exit";
			if(CheckCoatItems())
			{
				link.l2 = "Yes, I brought everything. Here's my old jacket, the Order, and the tailoring tools. The rest of the materials, my sailors will bring from to your workshop shortly.";
				link.l2.go = "Tailor_21";
			}
		break;
		
		case "Tailor_20_exit":
			npchar.dialog.currentnode = "Tailor_20";
			DialogExit();
		break;
		
		case "Tailor_21":
			RemoveItems(pchar, "talisman9", 1);
			RemoveItems(pchar, "suit1", 1);
			RemoveItems(pchar, "tailor_tool", 1);
			RemoveCharacterGoods(pchar, GOOD_CLOTHES, 1);
			RemoveCharacterGoods(pchar, GOOD_COTTON, 1);
			RemoveCharacterGoods(pchar, GOOD_LEATHER, 1);
			RemoveCharacterGoods(pchar, GOOD_SHIPSILK, 1);
			dialog.text = "Wonderful! To be honest, I didn't think you would be able to obtain all of this. I'm used to working only with fabrics from Paris, but it seems you can make quite decent suits from local materials.";
			link.l1 = "How long until my new uniform is ready?";
			link.l1.go = "Tailor_22";
		break;
		
		case "Tailor_22":
			dialog.text = "Usually, it takes no less than a week, but considering that the clients are the two highest-ranking officials of France in the colonies... Come to me in three days, and I promise you everything will be ready in the best possible way! We don't need to take measurements, I'll do everything based on your old jacket.";
			link.l1 = "Great! I'll be back in three days then.";
			link.l1.go = "Tailor_23";
		break;
		
		case "Tailor_23":
			DialogExit();
			npchar.dialog.currentnode = "Tailor_24";
			SetFunctionTimerCondition("Patria_Tailor_Done", 0, 0, 3, false);
		break;
		
		case "Tailor_24":
			if(CheckAttribute(pchar,"questTemp.PatriaTailorDone"))
			{
				dialog.text = "Vice admiral! It's a pleasure to see you!";
				link.l1 = "Well, I've come for the new uniform, as we agreed.";
				link.l1.go = "Tailor_27";
			}
			else
			{
				dialog.text = "Greetings, vice admiral! I apologize, but your uniform is not ready yet.";
				link.l1 = "Well, can I at least take a little peek at what's happening?";
				link.l1.go = "Tailor_25";
			}
		break;
		
		case "Tailor_25":
			dialog.text = "No, no! Right now, it looks completely unpresentable, and I don't want to disappoint your expectations. Please have patience.";
			link.l1 = "Оk, I'll wait.";
			link.l1.go = "Tailor_26";
		break;
		
		case "Tailor_26":
			DialogExit();
			npchar.dialog.currentnode = "Tailor_24";
		break;
		
		case "Tailor_27":
			dialog.text = "Yes, of course! I must tell you that it turned out no worse than the ones made in Paris! You were right, even in the colonies, you can find suitable material if you know where to look. Just a moment. Here it is! Please, inspect and try it on.";
			link.l1 = "Thank you. Excellent quality! And it fits well.";
			link.l1.go = "Tailor_28";
		break;
		
		case "Tailor_28":
			dialog.text = "Not just well! You can proudly wear this as the vice admiral of France in the colonies! And your Order, as I promised, is now in its proper place, not dangling on your belt.";
			link.l1 = "Good job! When you meet Chevalier de Poincy, you can tell him I am satisfied.";
			link.l1.go = "Tailor_29";
		break;
		
		case "Tailor_29":
			dialog.text = "I will definitely tell him! May the uniform serve you faithfully! Good luck!";
			link.l1 = "Thank you! Goodbye.";
			link.l1.go = "Tailor_30";
		break;
		
		case "Tailor_30":
			DialogExit();
			npchar.dialog.currentnode = "first time";
			npchar.lifeday = 0;
			DeleteAttribute(pchar,"questTemp.PatriaTailorDone");
			DeleteAttribute(pchar, "questTemp.PatriaTailor");
			//if(CheckAttribute (pchar, "IsMushketer")) SetMainCharacterToMushketer("", false);
			RemoveCharacterEquip(pchar, CIRASS_ITEM_TYPE);
			GiveItem2Character(pchar, "suit5");
			EquipCharacterbyItem(pchar, "suit5");
			GiveItem2Character(pchar, "hat5");
			EquipCharacterbyItem(pchar, "hat5");
			AddItems(pchar, "tailor_tool", 1);
			Log_Info("You have received the Vice-Admiral's uniform!");
			AddQuestRecord("Patria", "65_2");
		break;
		
		//belamour legendary edition
		case "BladeUpg":
			string sItem, attrL, attrB;
			ref rItem;
			aref arItems; 
			int i, n, iItemsNum;
			dialog.text = "Which blade would you like to upgrade?";
			
			i = 1;
			makearef(arItems, pchar.items);
			iItemsNum = GetAttributesNum(arItems);
			for(n=0; n<iItemsNum; n++)
			{
				sItem = GetAttributeName(GetAttributeN(arItems, n));
				rItem = ItemsFromID(sItem);
				if(!CheckAttribute(rItem, "groupID")) continue;
				if(rItem.groupID != BLADE_ITEM_TYPE) continue;
				if(rItem.price == 0) continue;
				if(IsEquipCharacterByItem(pchar, rItem.id)) continue;
				if(sItem != "" && rItem.groupID == BLADE_ITEM_TYPE) 
				{
					attrL = "l" + i;
					Link.(attrL) = GetConvertStr(rItem.name, "ItemsDescribe.txt") + ": Attack - " + FloatToString(stf(rItem.attack),1) + ", balance - " + FloatToString(stf(rItem.Balance),1) + ", weight - " + FloatToString(stf(rItem.Weight),1);
					Link.(attrL).go = "bladeindex_"+GetItemIndex(rItem.id);
					i++;
				}
			}
			
			link.l500 = "I've changed my mind";
			link.l500.go = "exit";
		break;
	}
} 

bool CheckCoatItems()
{
	if(GetSquadronGoods(pchar, GOOD_CLOTHES) > 0
	&& GetSquadronGoods(pchar, GOOD_COTTON) > 0
	&& GetSquadronGoods(pchar, GOOD_LEATHER) > 0
	&& GetSquadronGoods(pchar, GOOD_SHIPSILK) > 0
	&& GetCharacterFreeItem(pchar, "talisman9") > 0
	&& GetCharacterFreeItem(pchar, "suit1") > 0
	&& GetCharacterFreeItem(pchar, "tailor_tool") > 0)
	return true;
	
	return false;
}
