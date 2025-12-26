void ProcessDialogEvent()
{
	ref NPChar, sld, rItm, rItem;
	aref Link, NextDiag, rType;
	int i, n;
	string sTemp, sStr, sStr2, sGun, sBullet, attrL;
	
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
			dialog.text = "Что вам надо?";
			link.l1 = "Ничего.";
			link.l1.go = "exit";
		break;
		
		case "Alonso":
			NextDiag.TempNode = "Alonso";
			
			// --> Эпилог
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_FarewellOfficers") && !CheckAttribute(npchar, "quest.SharlieEpilog_FarewellOfficers"))
			{
				dialog.text = "...";
				Link.l1 = "Alonso, I need to talk to you.";
				Link.l1.go = "SharlieEpilog_Alonso_1";
				break;
			}
			// эпилог <--
			
			if (GetDLCenabled(DLC_APPID_1))
			{
				if(CheckAttributeEqualTo(pchar, "questTemp.LoyaltyPack.FirstStage", "ready"))
				{
					dialog.text = "Permission to speak, cap?";
					link.l1 = "Later, Alonso.";
					link.l1.go = "exit";
					link.l2 = "Go ahead.";
					link.l2.go = "Alonso_1";
					break;
				}
				if(CheckAttributeEqualTo(pchar, "questTemp.LoyaltyPack.SecondStage", "ready"))
				{
					dialog.text = "Permission to speak, cap?";
					link.l1 = "Later, Alonso.";
					link.l1.go = "exit";
					link.l2 = "Go ahead.";
					link.l2.go = "Alonso_Lvl_8_Start";
					break;
				}
				if(CheckAttributeEqualTo(pchar, "questTemp.LoyaltyPack.ThirdStage", "ready"))
				{
					dialog.text = "Permission to speak, cap?";
					link.l1 = "Later, Alonso.";
					link.l1.go = "exit";
					link.l2 = "Go ahead.";
					link.l2.go = "Alonso_Lvl_12_Start";
					break;
				}
				if(CheckAttributeEqualTo(pchar, "questTemp.LoyaltyPack.FourthStage", "ready"))
				{
					dialog.text = "Permission to speak, cap?";
					link.l1 = "Later, Alonso.";
					link.l1.go = "exit";
					link.l2 = "Go ahead.";
					link.l2.go = "Alonso_Lvl_16_Start";
					break;
				}
			}
			
			dialog.text = " Nothing to report, cap.";
			link.l1 = "As you were, Alonso.";
			link.l1.go = "exit";
		break;
		
		case "Alonso_1":
			DelLandQuestMark(npchar);
			dialog.text = "How are you holding up?";
			link.l1 = "What do you mean?";
			link.l1.go = "Alonso_2";
		break;
		
		// Основная развилка стадии 1
        case "Alonso_2":
            dialog.text = "You've been sailing these Caribbean waters for months now, while some don't last a week out here. The crew respects you, that's for certain, but me? I worry about what lies ahead for you.\n"+
                          "Share your thoughts with us, cap. Do the crew a favor. Where's the "+pchar.ship.name+" headed?";
                          
            link.l1 = "I don't have a plan. Want to get the lay of the land first. Adventure will find us on its own.";
            link.l1.go = "Alonso_Choice_1";
            
            link.l2 = "These waters are full of predators, Alonso. And the "+pchar.ship.name+" is the smallest of them. For now.";
            link.l2.go = "Alonso_Choice_2";
            
            link.l3 = "I like making money. Preferably legally. But we'll see how that goes.";
            link.l3.go = "Alonso_Choice_3";
			
            if (!SandBoxMode)
            {
                link.l4 = "You know the story. After that memorable conversation on the Ulysses, everything just got more complicated...";
                link.l4.go = "Alonso_Choice_4";
            }
        break;
        
        case "Alonso_Choice_1":
            dialog.text = "Now that's freedom! Just make sure you've got enough to maintain the ship and keep something in the coffers for a rainy day.\n"+
                          "Wherever your mood, quest, or treasure map takes you - pick up passenger runs, cargo hauls, any odd job that comes your way.\n"+
                          "Won't hurt to dabble in small trade either - buy low where it's obvious, sell where you can.\n"+
                          "And if you spot a lonely merchant vessel along the way... Heh. As you have said, cap. Adventure will find us indeed.";
            
            AddCharacterExpToSkill(pchar, SKILL_LEADERSHIP, 50);
            AddCharacterExpToSkill(pchar, SKILL_GRAPPLING, 50);
            AddCharacterExpToSkill(pchar, SKILL_COMMERCE, 50);
            
            link.l1 = "Thanks for the good advice, Alonso.";
            link.l1.go = "Alonso_Common_End";
        break;
        
        case "Alonso_Choice_2":
            dialog.text = "Profitable business, if your ship can handle it. Find the lone merchants and show them what 'penny wise, pound foolish' really means.\n"+
                          "Unfortunately for you, there's another saying that comes into play: 'Truth will out.' There's always some loose tongue in the crew who'll blab about your exploits at the first port.\n"+
                          "So either rob everyone a little, or pick your enemy flag for life.\n"+
                          "Though I may be getting ahead of myself. If things get really tight, there's a lawyer in Port Royal who'll smooth things over with the authorities for the right price. Call it a piracy tax, heh-heh!";
            
            AddCharacterExpToSkill(pchar, SKILL_GRAPPLING, 50);
            AddCharacterExpToSkill(pchar, SKILL_ACCURACY, 50);
            ChangeCharacterComplexReputation(pchar, "nobility", -1);
            
            link.l1 = "Thanks for the good advice, Alonso.";
            link.l1.go = "Alonso_Common_End";
        break;
        
        case "Alonso_Choice_3":
            dialog.text = "Eh, can't help you much there, cap. You'll need a proper merchant vessel - a barquentine, or better yet, a barque. I'll probably regret saying this, but you'd best mount lighter guns or toss artillery altogether.\n"+
                          "Take cargo contracts from shop owners, trade on your own account along the way, and ferry passengers.\n"+
                          "Once you've saved enough, invest in shops and banks. Mark my words, cap - one day your money will start making money, and you'll afford a proper ship with a couple hundred lads aboard.\n"+
                          "Which, by the way, your business will pay for, not you.";
            
            AddCharacterExpToSkill(pchar, SKILL_COMMERCE, 50);
            AddCharacterExpToSkill(pchar, SKILL_SAILING, 50);
            ChangeCharacterComplexReputation(pchar, "nobility", 1);
            
            link.l1 = "Thanks for the good advice, Alonso.";
            link.l1.go = "Alonso_Common_End";
        break;
        
        case "Alonso_Choice_4":
            dialog.text = "I see it differently, cap. On the Ulysses you were just a passenger - those poor souls have no control over their fate. Now you're a captain who's earned his hat, which means you can solve any problem. I told you before - there's no higher station in our world.\n"+
                          "My gut tells me this saga with your brother will drag on for years, so take care of yourself first. Monsieur Michel isn't going anywhere, heh-heh...\n"+
                          "You're not the only one with problems in the Caribbean. Perfect time to help others while earning coin, gear, and connections. You'll learn everything you'll need for this family business along the way...";
            
            AddCharacterExpToSkill(pchar, SKILL_LEADERSHIP, 100);
            ChangeCharacterComplexReputation(pchar, "nobility", 1);
            
            link.l1 = "Thanks for the good advice, Alonso.";
            link.l1.go = "Alonso_Common_End";
        break;
		
        case "Alonso_Common_End":
            dialog.text = "Don't box yourself into one role, cap. Do what you want, when you want. Take everything and give nothing back. You'll do just fine.";
            link.l1 = "And thanks for the wisdom too.";
            link.l1.go = "Alonso_Common_End_2";
        break;
        
        case "Alonso_Common_End_2":
            dialog.text = "Eh, that's what you pay me for, cap. You think the crew follows your orders just for their meager wages?\n"+
                          "Dozens of men crammed in tight quarters, never knowing when they'll see land again, or if they will at all. And murdering a ship? Too easy.";
            link.l1 = "Yes, yes, I've heard this speech before, Alonso. What was that you were saying about ships?";
            link.l1.go = "Alonso_Common_End_3";
        break;
        
        case "Alonso_Common_End_3":
            dialog.text = "Heh! A ship is a prison, an army camp, and a monastery all rolled into one. A gathering of men, in short. So problems get solved either with words or with the lash. In your case, the latter's, heh-heh, not an option, so I figured we'd have ourselves a chat. Make things easier for you, like.";
            link.l1 = "Have you ever actually been in prison? The army? A monastery, God forbid? Come to think of it, Alonso, tell me about yourself. I barely know anything about you.";
            link.l1.go = "Alonso_Story_1";
        break;
        
        // История Алонсо
        case "Alonso_Story_1":
            dialog.text = "Well, monasteries I've avoided, I won't lie. Though I did serve in the Holy Inquisition once...";
            link.l1 = "How in God's name did that happen?";
            link.l1.go = "Alonso_Story_2";
        break;
        
        case "Alonso_Story_2":
            dialog.text = "Oh! It went like this. I was pulling my weight as a mercenary in the European war. Devil knows how it started or who was fighting whom. All we knew was the war had been going on thirty years and which commanders paid somewhat regularly. Now that was an adventure!\n"+
                          "This was in '42... or was it '41? Doesn't matter. Two companies, both in the Emperor's service, met in a forest. In the fog. And started hacking each other to pieces! Three days of slaughter!";
            link.l1 = "How's that possible?";
            link.l1.go = "Alonso_Story_3";
        break;
        
        case "Alonso_Story_3":
            dialog.text = "Try telling friend from foe in that fog. Besides, we hadn't been paid in three months, so everyone was thinking about loot.\n"+
                          "We killed half of each other. By the time we figured it out, it was too late. That's when I met this Muscovite. Big as a bear, but with a heart of gold!";
            link.l1 = "What happened next?";
            link.l1.go = "Alonso_Story_4";
        break;
        
        case "Alonso_Story_4":
            dialog.text = "You know how it is in war? First to report is the hero. So we figured - might as well turn this disaster to our advantage!\n"+
                          "Got the lads together, went to the paymaster, reported a 'glorious battle.' Dead men's wages got cut, survivors got paid, me and my friend got bonuses, and the commander got his share.";
            link.l1 = "So you're rich then, Alonso.";
            link.l1.go = "Alonso_Story_5";
        break;
        
        case "Alonso_Story_5":
            dialog.text = "Ha! We spent a week drinking wine and playing cards. Lucky for me, my new friend from snowy Muscovy had a weakness for rare trinkets, or I'd have ended up in debtor's prison. Bought a trophy off me - a magnificent three-barreled pistol, and at a good price too. Didn't take advantage of my misfortune.";
            link.l1 = "That's quite a tale, Alonso. Sounds to me like you just made it up.";
            link.l1.go = "Alonso_Gift";
        break;
        
        // Вручение подарка
        case "Alonso_Gift":
            dialog.text = "You wound me, cap. Here, take this little gift.";
            link.l1 = "What is it?";
            link.l1.go = "Alonso_Gift_2";
        break;
        
        case "Alonso_Gift_2":
            // Выдаем Берендейку
            GiveItem2Character(pchar, "talisman20");
			SetAlchemyRecipeKnown("talisman20");
            
            dialog.text = "A bandolier for musket fighting. Everyone wears these in my Muscovite friend's homeland. Or so he said.\n"+
                          "May it serve you well, cap. Consider it a gift from the crew.";
            link.l1 = "Unexpected! Thank you, Alonso. So what about that service in the Inquisition?";
            link.l1.go = "Alonso_Escape";
        break;
        
        case "Alonso_Escape":
            PlaySound("ambient\SEA\Ship_bell_Two.wav");
            dialog.text = "Eh...\n"+
                          "The bells are ringing, cap! Time to get back to work. We'll continue another time.";
            link.l1 = "We'll definitely continue this conversation. Thanks for the gift!";
            link.l1.go = "exit";
            
			AddDialogExitQuestFunction("LoyaltyPack_FirstStage_DlgExit");
        break;
		
		// (Level 8) - Continuing the story
        case "Alonso_Lvl_8_Start":
			DelLandQuestMark(npchar);
			dialog.text = "You've accomplished much since we last spoke, and no one - not the crew, not me - doubts your talents anymore.";
			link.l1 = "There were doubts?";
			link.l1.go = "Alonso_Lvl_8_1";
        break;

        case "Alonso_Lvl_8_1":
            dialog.text = "Of course there were. We're simple folk - we prepare for the worst. Enjoy your freedom, cap. Keep this up and you'll see a whole different side of the Caribbean.";
            link.l1 = "Good to hear. Now tell me about your service in the Inquisition. Last time you started with some army tale and ended with it too.";
            link.l1.go = "Alonso_Lvl_8_2";
        break;

        case "Alonso_Lvl_8_2":
            dialog.text = "What's to tell? After that senseless but very profitable forest massacre, me and the Muscovite became thick as thieves and pulled quite a few more schemes.\n"+
                          "I remember we decided to raid an imperial supply train once. Scouts said they were hauling trophies, gold, weapons...";
            link.l1 = "So did you pull it off?";
            link.l1.go = "Alonso_Lvl_8_3";
        break;

        case "Alonso_Lvl_8_3":
            dialog.text = "Easy as pie. Hit them from both sides, scattered the guards, opened the wagons - and found cabbage! Rotten, stinking cabbage for some garrison! But you know what? We hadn't eaten in a week, so we were happy even for that!";
            link.l1 = "As if the food on my ship is any better.";
            link.l1.go = "Alonso_Lvl_8_4";
        break;

        case "Alonso_Lvl_8_4":
            dialog.text = "Well, I'm used to it now. But back then... After a week of foraging, you'd gnaw bark off trees!\n"+
                          "But my friend didn't lose heart. Pulled out a flask of his special brew - Muscovite recipe, he said. We didn't care what it was, long as it wasn't vinegar! After a few swigs, even that cabbage tasted like a feast!";
            link.l1 = "Disgusting.";
            link.l1.go = "Alonso_Lvl_8_5";
        break;

        case "Alonso_Lvl_8_5":
            dialog.text = "What's disgusting is the state of our water barrels, but that Muscovite rotgut saved my life that day.";
            link.l1 = "How so?";
            link.l1.go = "Alonso_Lvl_8_6";
        break;

        case "Alonso_Lvl_8_6":
            dialog.text = "We got blind drunk right there in the road mud with cabbage floating around us. Well, one thing led to another, and I got into an argument with some nobleman. German fellow, all prim and proper. Too good to drink with us, just sat there cleaning his musket and making snide remarks.\n"+
                          "So we're sitting there, drowning our sorrows over cabbage. And he starts lecturing us about military wisdom. Says our trusted swords and pikes will soon be forgotten, but the bayonet - now that's the future and the key to everything.\n"+
                          "So I argued with him, and somehow we agreed to fight to the death - with bayonets, no less. Don't ask me how it happened, I don't remember myself.\n"+
                          "But there were only two bayonets in our whole company. One belonged to that little officer, the other to Fox, an Englishman. I borrowed his fusil and beat the German to death with it, then made myself scarce.";
            link.l1 = "But you were hungry and drunk.";
            link.l1.go = "Alonso_Lvl_8_7";
        break;

        case "Alonso_Lvl_8_7":
            dialog.text = "I figured out later that my friend's brew really steadies your hand when you're swinging a heavy musket around. So now I am more inclined to agree with the dead German's ideas.";
            link.l1 = "And how does this relate to your service in the Inquisition?";
            link.l1.go = "Alonso_Lvl_8_Gift";
        break;

        case "Alonso_Lvl_8_Gift":
            dialog.text = "You don't believe me again, cap! Here, take this.";
            link.l1 = "A bottle and a piece of paper?";
            link.l1.go = "Alonso_Lvl_8_Gift_2";
        break;

        case "Alonso_Lvl_8_Gift_2":
            // Даём игроку настойку и рецепт
            GiveItem2Character(pchar, "vodka");
            SetAlchemyRecipeKnown("vodka");

            dialog.text = "That's the brew I was telling you about. And the recipe. In case you take a liking to it, heh-heh.";
            link.l1 = "Sorry, my friend, but scribbles and some murky concoction don't...";
            link.l1.go = "Alonso_Lvl_8_Gift_3";
        break;

        case "Alonso_Lvl_8_Gift_3":
            // Даём игроку мушкет с багинетом
            GiveItem2Character(pchar, "mushket10");

            dialog.text = "Alright, alright, cap. I was going to give you this anyway. This kind of weapon doesn't suit me, but you'll find it useful. Bayonets are rare beasts. But once you learn to use one, you'll forget all about swinging sabers.";
            link.l1 = "Wait, is this the very musket from that imperial officer? The one you killed?";
            link.l1.go = "Alonso_Lvl_8_Gift_4";
        break;

        case "Alonso_Lvl_8_Gift_4":
			PlaySound("ambient\SEA\Ship_bell_Two.wav");
            dialog.text = "The very same. As you can see, I told you the truth, cap.";
            link.l1 = "But that's not what I asked about.";
            link.l1.go = "Alonso_Lvl_8_Escape";
        break;

        case "Alonso_Lvl_8_Escape":
            dialog.text = "The bells are ringing, cap! Time to get back to work. We'll continue another time.";
            link.l1 = "We'll definitely continue this conversation. Thanks for the musket!";
            link.l1.go = "exit";
			AddDialogExitQuestFunction("LoyaltyPack_SecondStage_DlgExit");
        break;

        // (Уровень 12)
        case "Alonso_Lvl_12_Start":
			DelLandQuestMark(npchar);
			dialog.text = "Captain, regarding the new recruits...";
			link.l1 = "Did something happen?";
			link.l1.go = "Alonso_Lvl_12_1";
        break;

        case "Alonso_Lvl_12_1":
            dialog.text = "I wanted to report that at this evening's mass, one of the recruits mentioned he specifically wanted to sign on to your ship.";
            link.l1 = "And what does that mean exactly?";
            link.l1.go = "Alonso_Lvl_12_2";
        break;

        case "Alonso_Lvl_12_2":
            dialog.text = "That soon there might be more like him. You've got a name now, cap.";
            link.l1 = "Funny that I still don't know what's behind your name. You never actually finished that story about the Inquisition.";
            link.l1.go = "Alonso_Lvl_12_3";
        break;

        case "Alonso_Lvl_12_3":
            dialog.text = "Oh, where was I... Right! And then we went to pursue a career military suppliers. The war was winding down, had to think about the future. And my friend's head was always big with thoughts about the future.";
            link.l1 = "That's quite a career leap. Not long ago you were getting drunk by a ransacked wagon full of cabbage.";
            link.l1.go = "Alonso_Lvl_12_4";
        break;

        case "Alonso_Lvl_12_4":
            dialog.text = "Wait, it gets better. We got an order for a hundred helmets for some regiment. Got a swell advance payment too. So we celebrated... Played cards and such.\n"+
                          "Wake up in the morning --- the money is gone, army marches out in two days, and we still have a hundred helmets to provide!";
            link.l1 = "So what did you do?";
            link.l1.go = "Alonso_Lvl_12_5";
        break;

        case "Alonso_Lvl_12_5":
            dialog.text = "Went to the fresh battlefield, gathered hats from the dead. Then nailed on various bits of metal, attached plates... Looked ridiculous, but it worked! Definitely could save you from a saber hit. Well, at least once for sure. Good as any helmet, right?!";
            link.l1 = "Did the quartermaster appreciate your ingenuity?";
            link.l1.go = "Alonso_Lvl_12_6";
        break;

        case "Alonso_Lvl_12_6":
            dialog.text = "Sent us to tribunal for embezzlement and fraud. But you know what? We got word later, that those hats saved lives more than once. And ours too, as it turned out.";
            link.l1 = "How so?";
            link.l1.go = "Alonso_Lvl_12_7";
        break;

        case "Alonso_Lvl_12_7":
            dialog.text = "Well, we both got thrown in prison. And our company got sent on a mission. Don't know where or against whom, and they probably didn't know either. They never returned.\n"+
                          "...\n"+
                          "Sorry, cap. We'll continue another time. Take this hat and instructions. Made it yesterday to cheer you up... But just made myself sad for nothing.";
            link.l1 = "Of course, Alonso. Thank you for the gift.";
            link.l1.go = "Alonso_Lvl_12_Gift";
        break;

        case "Alonso_Lvl_12_Gift":
            // Даём игроку шляпу
            GiveItem2Character(pchar, "hat10");
            SetAlchemyRecipeKnown("Hat10");

            DialogExit();
			AddDialogExitQuestFunction("LoyaltyPack_ThirdStage_DlgExit");
        break;

        // (Уровень 16) - Финальный
        case "Alonso_Lvl_16_Start":
			DelLandQuestMark(npchar);
			dialog.text = "Captain, just wanted to report that your crew gets the royal treatment in taverns and brothels now. Serving under your flag means something these days!";
			link.l1 = "Thanks, Alonso... Shame I'm not seeing much of that royal treatment myself yet.";
			link.l1.go = "Alonso_Lvl_16_1";
        break;

        case "Alonso_Lvl_16_1":
            dialog.text = "You will soon enough. The Caribbean is a pie divided among a few dozen captains. Soon you'll have a seat at that table and grab your slice.\n"+
                          "And who knows? Maybe you'll be the Caribbean legend who takes the whole pie.";
            link.l1 = "So will you finish your story? We left off where you got thrown in prison.";
            link.l1.go = "Alonso_Lvl_16_2";
        break;

        case "Alonso_Lvl_16_2":
            dialog.text = "Ha! The case of the great hat thieves. A Muscovite and a Portuguese in a tiny cell somewhere in Flanders. Awaiting sentence. Hanging, naturally.\n"+
                          "Some important gentleman saved us - turned out to be a Muscovite ambassador! Old friend of Fadey's. Was passing through, heard about our predicament, bought our freedom!";
            link.l1 = "Fadey? THE Fadey? And you kept quiet about this?!";
            link.l1.go = "Alonso_Lvl_16_3";
        break;

        case "Alonso_Lvl_16_3":
            dialog.text = "Yep. That's where we parted ways - he went back to his Moscow, either to fight the Poles or handle some big business. I knocked around the old country a bit more, and here I am.";
            link.l1 = "Impressive, Alonso. All this time and you've managed to tell me everything except about yourself. Strange how a clever fellow like you let slip about the Inquisition.";
            link.l1.go = "Alonso_Lvl_16_4";
        break;

        case "Alonso_Lvl_16_4":
            dialog.text = "And I told you the pure truth, cap! Don't believe me - ask Fadey himself. He's not hard to find in Basse-Terre.";
            link.l1 = "Maybe I will. So where's my gift?";
            link.l1.go = "Alonso_Lvl_16_5";
        break;

        case "Alonso_Lvl_16_5":
            dialog.text = "Eh?";
            link.l1 = "You gave me a gift at the end of every story.";
            link.l1.go = "Alonso_Lvl_16_Escape";
        break;

        case "Alonso_Lvl_16_Escape":
			PlaySound("ambient\SEA\Ship_bell_Two.wav");
            dialog.text = "Hear that? The bells are ringing. Time to get to work.";
            link.l1 = "As you were, Alonso.";
            link.l1.go = "exit";
			AddDialogExitQuestFunction("LoyaltyPack_FourthStage_DlgExit");
        break;
		
		// --> Эпилог
		case "SharlieEpilog_Alonso_1":
			dialog.text = "Is this about Floran? I already told him that...";
			link.l1 = "No, buddy, it's a completely different matter. I've decided to sail to Europe. For an indefinite period.";
			link.l1.go = "SharlieEpilog_Alonso_2";
		break;

		case "SharlieEpilog_Alonso_2":
			if (GetCompanionQuantity(pchar) <= 1) sStr = "our ship";
			else sStr = "our ships";
			dialog.text = "No problem, cap. The ship is sturdy, the crew is seasoned, we just need some provisions...";
			link.l1 = "I'll be sailing on someone else's ship. As a passenger. You'll need to dock "+sStr+" at the port authority and disband the crew. And decide: stay here and join another crew, or come with me to France — as a friend.";
			link.l1.go = "SharlieEpilog_Alonso_3";
		break;

		case "SharlieEpilog_Alonso_3":
			dialog.text = "...";
			link.l1 = "By the way, totally unrelated: (whispering) I know a couple of babes in Bordeaux... You won't find sorceresses like that in the Caribbean. They’re into guys like you, and if you start telling them about our battles...";
			link.l1.go = "SharlieEpilog_Alonso_4";
		break;

		case "SharlieEpilog_Alonso_4":
			dialog.text = "Well, if it’s for the babes… I’m in. Heh-heh. But why not on our ship? And why as a passenger? The lads might grumble a bit, but they'd follow you to heaven or hell.";
			link.l1 = "When I first arrived here, I couldn’t picture myself as a sailor. And now I can’t imagine any other life. I want to see if I can handle not being a captain anymore... and maybe leaving behind raiding convoys and life at sea.";
			link.l1.go = "SharlieEpilog_Alonso_nothing";
			link.l2 = "Long story. I’ll tell you at the tavern — over a mug of rum. And invite the crew. Let’s throw a grand farewell party. Here, take this — hand out a month’s pay as severance.";
			link.l2.go = "SharlieEpilog_Alonso_salary";
		break;
		
		case "SharlieEpilog_Alonso_nothing":
			dialog.text = "You can’t escape fate, cap. If you’re meant to be a captain till your dying day — so be it.";
			link.l1 = "We’ll see, "+npchar.name+", we’ll see. But for now — time to get things moving. We set sail in two weeks. You’ll never guess which ship...";
			link.l1.go = "SharlieEpilog_Alonso_5";
		break;
		
		case "SharlieEpilog_Alonso_salary":
			dialog.text = "Now that’s more like it! That'll make breaking the news to them a lot easier.";
			link.l1 = "You’ll never guess which ship...";
			link.l1.go = "SharlieEpilog_Alonso_5";
			salary = GetSalaryForShip(PChar);
			AddMoneyToCharacter(pchar, - sti(npchar.quest.OfficerPrice));
		break;

		case "SharlieEpilog_Alonso_5":
			dialog.text = "Don’t keep me in suspense, cap.";
			link.l1 = "On the pinnace '"+GetShipName("Ulysse")+"'.";
			link.l1.go = "SharlieEpilog_Alonso_6";
		break;

		case "SharlieEpilog_Alonso_6":
			dialog.text = "No way... We're sailing out on the very ship we once arrived on? I can’t believe it...";
			link.l1 = "That’s the one, "+npchar.name+". I’ll tell you how I found it later — at the tavern, over a mug of rum. Right now, we’ve got work to do.";
			link.l1.go = "SharlieEpilog_Alonso_7";
		break;

		case "SharlieEpilog_Alonso_7":
			dialog.text = "Aye aye, cap... Man... I’ll miss the lads. They’re like family to me. But what can you do...";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Alonso";
			npchar.quest.SharlieEpilog_FarewellOfficers = true;
			AddDialogExitQuestFunction("SharlieEpilog_Alonso_exit");
		break;

		// эпилог <--
	}
} 