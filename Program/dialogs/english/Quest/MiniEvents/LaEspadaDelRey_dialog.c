void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
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
			dialog.text = "What do you want?";
			link.l1 = "Nothing.";
			link.l1.go = "exit";
		break;
		
		case "LEDR_Gonsalo_1":
			if (pchar.sex == "man")
			{
				dialog.text = "Hey, lad! You look like a brave sailor, and I bet you can handle yourself in a fight. Would you help me with a little raid somewhere, eh?";
			}
			else
			{
				dialog.text = "Hey, beautiful! I can see you’re not the timid type if you’ve come here. How about helping me out with a little raid somewhere, eh?";
			}
			link.l1 = "I suppose you're the old man looking for a guide to the ancient ship?";
			link.l1.go = "LEDR_Gonsalo_2";
			DelLandQuestMark(npchar);
		break;
		
		case "LEDR_Gonsalo_2":
			dialog.text = "Heh... So, rumors travel faster than the wind. Yes, that's me. Gonzalo Peralta – the only one still alive from the wreck of 'La Espada del Rey.'";
			link.l1 = "And I'm a captain "+GetFullName(pchar)+". Do you want to take another look at your vessel?";
			link.l1.go = "LEDR_Gonsalo_3";
		break;

		case "LEDR_Gonsalo_3":
			dialog.text = "Yes. You see, lately I’ve been haunted by the same nightmare over and over. But that’s not even the worst part... Believe it or not, every morning, as soon as the nightmare ends, I wake up and... there’s a damn skeleton standing right in front of me...";
			link.l1 = "They told me you tell this fantasy to everyone.";
			link.l1.go = "LEDR_Gonsalo_4";
		break;

		case "LEDR_Gonsalo_4":
			dialog.text = "A fantasy? Heh... I wish it were just that. A couple of months ago, I was living a quiet life, as any retired old sailor should. But now that bag of bones shows up every morning, stares at me, lets out a bloodcurdling scream... blast it, any boatswain would have his blood run cold... and then he charges into battle. And you know what? Each time, his attacks grow fiercer. That's exactly why I want to get to the ship as soon as possible—I can't shake the feeling that there's something I need to find there.";
			link.l1 = "Hmm... Quite the business. And what do you hope to find there after all this time?";
			link.l1.go = "LEDR_Gonsalo_5";
		break;
		
		case "LEDR_Gonsalo_5":
			dialog.text = "I don't know, Captain, I just don't know... But I'm drawn to that ship, like an old boat in a storm. My dream, that skeleton, and this strange feeling... By the sea, they're connected somehow. I just can't figure out how.";
			link.l1 = "What exactly happens in your dream? Is it somehow connected to the natives?";
			link.l1.go = "LEDR_Gonsalo_6";
			link.l2 = "So, you see visions at night and fight a skeleton in the morning? Maybe it’s not the ship, maybe you just need to see a doctor. I’m not going to indulge your wild imagination. Go find another fool to believe your nonsense.";
			link.l2.go = "LEDR_Gonsalo_6_end";
		break;
		
		case "LEDR_Gonsalo_6_end":
			DialogExit();
			AddDialogExitQuestFunction("LEDR_End");
		break;
		
		case "LEDR_Gonsalo_6":
			dialog.text = "Connected? You bet I am, blast it... In that dream, I'm with my dead crew aboard the 'La Espada del Rey'. We're... raiding Carib villages on Hispaniola, killing everyone in our path—men, women, children. Those who fight back, and even those who fall to their knees, begging for mercy. We burn their settlements one after another. The Indians' arrows and clubs against us are like a leaky tartane against a war galleon. The Caribs, desperate, beg for parley, and then...";
			link.l1 = "Good Lord! So you took part in all that lawlessness? You don't need help, you need a hempen necktie!";
			link.l1.go = "LEDR_Gonsalo_7";
		break;
		
		case "LEDR_Gonsalo_7":
			dialog.text = "No! No, damn it, that's not true, do you understand?! I have no idea why I'm dreaming about all this... but I swear by all that's holy, neither I nor my crew ever took part in such atrocities!";
			link.l1 = "You'd better hope that's true. Go on.";
			link.l1.go = "LEDR_Gonsalo_8";
		break;

		case "LEDR_Gonsalo_8":
			dialog.text = "The Caribs requested negotiations, and the captain agreed. He invited all of them into one of those huts we had taken. The chiefs came—two dozen at least, led by their queen, Anacaona. But the captain himself didn’t go inside... none of us did. As soon as the last chief entered, the door was slammed shut and barred with beams. And then... damn it... they set it on fire. Only the queen was spared, but not for long. They made her watch as her people burned alive... And then they hanged her from a tree.";
			link.l1 = "And this happens every night? The same dream, over and over again? You know, I wouldn't be surprised if, after all that, the skeleton is just a figment of your fevered imagination...";
			link.l1.go = "LEDR_Gonsalo_9";
		break;

		case "LEDR_Gonsalo_9":
			dialog.text = "That's not all. The surviving Caribs fled to Cuba, found support among the local tribes, and soon gathered into a single army under some chief. Atuey—that was his name, I think. They followed him as their last hope. But we slaughtered them all without much trouble. Atuey was captured and prepared for execution. When they tied him to the cross, ready to burn him, a monk offered him the true faith—said it would ease his suffering and grant him entry to paradise. Atuey asked the monk if paradise was open to Spaniards. And when the monk replied that, of course, it was open to good Spaniards, the cacique answered without hesitation that, in that case, he wanted not paradise, but hell—so he wouldn't have to share a home with such cruel people. After that, he said a few more words in his own language, and the pyre was lit. He didn't make a single sound as the flames took hold of his flesh. By the sea, I swear, I wouldn't want to witness such a thing in real life. My dream always ends the same way: the captain sits, unmoving. Only a candle nearby smokes, and he keeps leafing through some battered journal. Slowly, as if every word weighs a fortune, mumbling something under his breath. Even in my dreams, "+GetSexPhrase("guy","girl")+", I understand – it's a sign. Time to reach for my blade, for he's already on the attack.\nHelp me put an end to this nightmare, Captain. Come with me to the bay. I won't go there alone – I'm running low on powder. But before you answer, I should warn you: I can't pay you. If I could, there'd already be a line of helpers out the door. So all I can do is hope for the help of a fellow sailor.";
			link.l1 = "All right, fine. If going to the ship will help you get rid of those dreams and other visions, I'll help you. Come aboard. As soon as I finish my business, we'll head to the bay.";
			link.l1.go = "LEDR_Gonsalo_10";
		break;
		
		case "LEDR_Gonsalo_10":
			DialogExit();
			AddDialogExitQuestFunction("LEDR_1");
			AddQuestRecord("LEDR", "2");
			AddQuestUserData("LEDR", "sSex", GetSexPhrase("ся","ась"));
		break;
		
		case "LEDR_Gonsalo_11":
			if (GetHour() >= 7 && GetHour() <= 19)
			{
				dialog.text = "Here it is... Once the pride of the Spanish merchant fleet, and now just a heap of rotten planks barely holding together.";
				link.l1 = "It's not often you see such a giant brought down—lying there on the shore. How did it end up here?";
				link.l1.go = "LEDR_Gonsalo_12";
				link.l2 = "Then let's take a look around. Maybe you'll actually manage to find something here.";
				link.l2.go = "LEDR_Gonsalo_20_1";
				DelLandQuestMark(npchar);
			}
			else
			{
				dialog.text = "I don't want to seem ungrateful or cowardly... but I don't feel safe here right now. Let's come back when the sun rises.";
				link.l1 = "Alright, friend, if you say so.";
				link.l1.go = "exit";
				NextDiag.TempNode = "LEDR_Gonsalo_11";
			}
		break;
		
		case "LEDR_Gonsalo_12":
			dialog.text = "We set sail from Santiago, bound for Seville. We didn’t have much cargo, but we did have one passenger—a big shot, a bishop himself. To be honest, the crew wasn’t thrilled about this voyage... but when did anyone ever ask us?\nWe never made it to the open ocean. Near Turks, a pirate brig attacked us—fast, nimble, armed to the teeth. Not some ragged lot, but real sea wolves. At first, the captain wanted to run—he didn’t want to risk the bishop’s life. But with the wind as it was, we couldn’t turn back, and a storm was blowing in from the south. So there was no choice—the fight began.";
			link.l1 = "To be caught between two fires is a miserable fate. And what happened next?";
			link.l1.go = "LEDR_Gonsalo_13";
			AddCharacterExpToSkill(pchar, "Sailing", 200);
		break;

		case "LEDR_Gonsalo_13":
			dialog.text = "The fight didn’t last long. We managed to take down their foremast, but the pirates gave as good as they got—a stray cannonball snapped our tiller rope, and, as if the devil himself willed it, the ship froze, bow facing the oncoming storm. It was closing in so fast that the pirates—may a chain shot rip their mainsail—chose to run, vanishing into one of the Turks’ coves. And all we could do was wait for the storm to swallow us whole. The captain ordered the sails lowered and the tiller rope replaced, but it was already too late.";
			link.l1 = "So, the storm caught you near Turks, dragged you all the way here, and finally tossed you ashore?";
			link.l1.go = "LEDR_Gonsalo_14";
		break;

		case "LEDR_Gonsalo_14":
			dialog.text = "That's exactly how it happened. The ship was pure chaos. The wind tore the rigging apart, masts crashed down one after another, smashing the deck and crushing people. If you didn't have time to tie yourself down, you were swept overboard; if you did, you were crushed by the wreckage. It was no better below deck—cannons, crates, cannonballs flew back and forth like demons, grinding up everything in their path. When we were finally thrown ashore, I was unconscious. I came to on the sand. Boatswain Sergio found me. He had two others with him.";
			link.l1 = "Not much, for such a large ship.";
			link.l1.go = "LEDR_Gonsalo_15";
		break;

		case "LEDR_Gonsalo_15":
			dialog.text = "Ah, captain... There were so many bodies... We knew right away: we couldn't stay there. The waves could have dragged off the ship, and us with it. Nearby, we found a cave—there, exhausted, we fell asleep the moment we touched the ground. When I woke up, there was no sign of Sergio or the other two in the cave.\nI searched the whole beach, but by thunder, they were nowhere to be found. I couldn't get back on the ship alone, so I decided to head inland. That's how I made it to Sharptown, where, in my own foolishness, I made a mess of things.\nI wanted to find out anything about the survivors, so I started telling everyone what had happened to us. But those scoundrels weren't interested in me or the crew—they only cared about the loot they could snatch from the ship. Word spread quickly across the island, and soon crowds of those ladrons were swarming over there.";
			link.l1 = "So, you still don't know what happened to those people?";
			link.l1.go = "LEDR_Gonsalo_16";
		break;

		case "LEDR_Gonsalo_16":
			dialog.text = "Going back to the ship was far too dangerous. Anyone who dared to sneak in for loot could end up fighting over the spoils and put a bullet in whoever happened to be nearby… by accident. Or maybe—not by accident at all. By the sea, I spent a whole week holed up in the tavern, questioning everyone who’d been to the bay. But no one had heard a thing about my crew, or what became of them. In the end, I had to accept it: looks like I’m the only one who survived that damned storm. Maybe fate just favored me more than the others. Or maybe… it was all thanks to the charm that young Captain Eugenio de la Torre once gave me. I always kept it close. And, damn it, it seems it really did bring me luck.";
			link.l1 = "And where is he now? Seems it doesn't protect him from skeletons, huh...";
			link.l1.go = "LEDR_Gonsalo_17";
		break;

		case "LEDR_Gonsalo_17":
			dialog.text = "It was torn from my neck while we were repairing the wellhead in my yard. A log struck my neck, and the amulet fell into the water. The well was already full, and no one would bother scooping it out for the sake of a single trinket.";
			link.l1 = "And from that moment on, you started having nightmares?";
			link.l1.go = "LEDR_Gonsalo_18";
		break;

		case "LEDR_Gonsalo_18":
			dialog.text = "Blistering barnacles! I never thought about it, but that's exactly what happened! As soon as we finished building the well, the nightmares began.";
			link.l1 = "Funny coincidence. Well, now you're here, just like you wanted. So, what do you plan to do next?";
			link.l1.go = "LEDR_Gonsalo_19";
		break;

		case "LEDR_Gonsalo_19":
			dialog.text = "I don't know, Captain... I don't know. Let's look around first – the feeling that there's something I need to find here has only grown stronger.";
			link.l1 = "Alright. I hope we didn't come here for nothing.";
			link.l1.go = "LEDR_Gonsalo_20";
		break;
		
		case "LEDR_Gonsalo_20":
			DialogExit();
			AddDialogExitQuestFunction("LEDR_3");
		break;
		
		case "LEDR_Gonsalo_20_1":
			DialogExit();
			AddDialogExitQuestFunction("LEDR_3");
			pchar.questTemp.LEDR_NoStory = true;
		break;
		
		case "LEDR_Gonsalo_21":
			dialog.text = "Listen... This feeling just keeps getting stronger. It's like I'm one step away from something I have to find. I need to get on that ship. I swear by the sea, there's something there that will explain why that damned skeleton won't leave me alone.";
			link.l1 = "So, maybe you weren't so eager to get here for nothing? Did you stash something valuable on the ship and now you've come back for your treasure?";
			link.l1.go = "LEDR_Gonsalo_22";
		break;

		case "LEDR_Gonsalo_22":
			dialog.text = "What nonsense is that? Do you really think I’d drag myself all the way across the archipelago for a couple of doubloons after forty years? If you’d ever had to meet that skeleton even once, such thoughts would never cross your mind.";
			link.l1 = "Alright, alright, calm down. And how exactly are you planning to get on the ship?";
			link.l1.go = "LEDR_Gonsalo_23";
		break;

		case "LEDR_Gonsalo_23":
			dialog.text = "There's a hidden door at the stern. The captain cut it out himself—in case a boarding goes against us. Thunder take me, I can't haul my old carcass through there alone, but with two of us...";
			link.l1 = "All right, lead the way and let’s get this over with.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LEDR_5");
		break;
		
		case "LEDR_Gonsalo_24":
			DelLandQuestMark(npchar);
			dialog.text = "Cannonball to my neck, what a mess! Lucky for me these ones weren’t as vicious as the one that shows up every morning. So, do you believe me now?";
			link.l1 = "After a show like that, it’s hard *not* to. You alright?";
			link.l1.go = "LEDR_Gonsalo_24_1";
		break;

		case "LEDR_Gonsalo_24_1":
			dialog.text = "I think so. Damn undead... my legs gave out like snapped masts.";
			link.l1 = "Well, if you’re in one piece, no point sitting around. Give me your hand, I’ll help you up.";
			link.l1.go = "LEDR_Gonsalo_24_2";
		break;

		case "LEDR_Gonsalo_24_2":
			CharacterTurnByChr(npchar, CharacterFromID("blaze"));
			dialog.text = "...";
			link.l1 = "That’s better. Looks like we’re not the first ones who knew how to get in here.";
			link.l1.go = "LEDR_Gonsalo_25";
			LAi_Fade("LEDR_GonsaloStay", "");
		break;

		case "LEDR_Gonsalo_25":
			dialog.text = "Looks like these are my men. The ones who survived the storm... I recognized Sergio's vest—or what's left of it, anyway. So they came back—either to look for survivors or to bury the dead. But it seems that same evil finished them off.";
			link.l1 = "It's strange that only scraps of the vest remain. Nothing else.";
			link.l1.go = "LEDR_Gonsalo_26";
		break;

		case "LEDR_Gonsalo_26":
			if(CheckAttribute(pchar, "questTemp.LEDR_NoStory"))
			{
			dialog.text = "Not even a trace of our passenger’s cassock — the bishop's — remains. Judging by the key clenched in that poor soul’s hand, that must be him. He never let go of that thing, not for a second. Seems he wasn’t any luckier than the others. By the sea, these undead weren’t just wandering around for fun. Something’s keeping them here... or they’re guarding something.";
			DeleteAttribute(pchar, "LEDR_NoStory");
			}
			else
			{
			dialog.text = "Not even a trace of the bishop’s cassock remains. Judging by the key clenched in that poor soul’s hand, that must be him. He never let go of that thing, not for a second. Seems he wasn’t any luckier than the others. By the sea, these undead weren’t just wandering around for fun. Something’s keeping them here... or they’re guarding something.";
			}
			link.l1 = "Now I’ve got the feeling we’re supposed to find something here. Let’s get this over with — I’ve got no desire to stay a second longer than we have to.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LEDR_8");
		break;
		
		case "LEDR_Gonsalo_27":
			dialog.text = "So, captain, did you manage to find anything?";
			link.l1 = "Looks like this was the bishop's chest. I found there's something in it. Take a look.";
			link.l1.go = "LEDR_Gonsalo_28";
		break;

		case "LEDR_Gonsalo_28":
			dialog.text = "Velasquez... Thunder strike me... I’ve seen this journal in my dreams! This is the very one the captain was leafing through before he...";
			link.l1 = "...";
			link.l1.go = "LEDR_Gonsalo_29";
		break;

		case "LEDR_Gonsalo_29":
			dialog.text = "Devil, it feels like he’s burning my hands!";
			link.l1 = "Burns your hands? Oh, come on, it's just an old journal. Or do you really believe there's some dark power in it?";
			link.l1.go = "LEDR_Gonsalo_30";
		break;

		case "LEDR_Gonsalo_30":
			dialog.text = "I swear by all the saints, I'm not joking! That damned journal feels like it's burning in my hands. It must be destroyed! Tear it apart, burn it, drown it—anything! No, wait... Better to burn it. Yes, burn it, so that not even ashes remain!";
			link.l1 = "As you wish. Then let's go ashore, light a fire, and send this chronicle of misdeeds into the flames.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LEDR_10");
		break;
		
		case "LEDR_Gonsalo_31":
			dialog.text = "Well, that's it... Feels like a weight's been lifted off my chest.";
			link.l1 = "Do you think it's all over now?";
			link.l1.go = "LEDR_Gonsalo_32";
			TakeItemFromCharacter(pchar, "LEDR_book");
		break;

		case "LEDR_Gonsalo_32":
			dialog.text = "Who knows... But I swear by the sea, I haven't felt this light in ages. It's as if an old debt has finally been forgiven. Still... I wish I'd never seen that cursed journal. Or learned what was written inside.";
			link.l1 = "No wonder you had such dreams. Even though you weren't involved in all of this, you're the only living person who was in any way connected to the journal.";
			link.l1.go = "LEDR_Gonsalo_33";
		break;
		
		case "LEDR_Gonsalo_33":
			dialog.text = "Neither gold nor faith can justify what people did under Velasquez's command. And I'm glad that everything that could remind us of it has burned. Such things should never fall into the hands of those who might be tempted to follow their example.";
			link.l1 = "Velasquez is just one of many. Who knows how many more such diaries are circulating in old Europe, fueling the greed and impunity of new conquerors? One thing is certain—this one will poison no one else. By the way, the bishop’s chest held not only the diary, but also a fair stash of doubloons—three hundred in all. Half of them are rightfully yours.";
			link.l1.go = "LEDR_Gonsalo_34_share";
			link.l2 = "Velasquez has paid for his sins, and if anyone chooses to follow in his footsteps, they will meet the same fate. Sooner or later, fate gives everyone what they deserve.";
			link.l2.go = "LEDR_Gonsalo_34_silence";
		break;
		
		case "LEDR_Gonsalo_34_share":
			dialog.text = "If that's the case - I won't say no. Everyone needs money, and I need it now more than ever. No one's going to take me on as a sailor anymore - I'm too old for that. So thank you, Captain, for not turning me away, like the others.";
			link.l1 = "I'll admit, at first your story sounded like the ramblings of a madman. But you told it so convincingly that, whether you want to or not, you can't help but start to believe. Still, the appearance of those undead natives caught me off guard.";
			link.l1.go = "LEDR_Gonsalo_35_1";
			link.l2 = "I just wanted to see if you were out of your mind. You know, it's not that easy to believe stories like that.";
			link.l2.go = "LEDR_Gonsalo_35_2";
			RemoveDublonsFromPCharTotal(150);
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			npchar.quest.LEDR_share = true;
		break;
		
		case "LEDR_Gonsalo_34_silence":
			dialog.text = "I want to believe that... But by the sea, I've seen too many who fortune favored, no matter how dark their deeds. Maybe their reckoning will come—just not here, but in the devil's own cauldron. And thank you, Captain. For not turning away, for listening, for seeing me off. That means a great deal, you know.";
			link.l1 = "I'll admit, at first your story sounded like the ramblings of a madman. But you told it so convincingly that, whether you want to or not, you can't help but start to believe. Still, the appearance of those undead Indians caught me off guard.";
			link.l1.go = "LEDR_Gonsalo_35_1";
			link.l2 = "I just wanted to see if you were out of your mind. You know, it’s not easy to believe stories like that.";
			link.l2.go = "LEDR_Gonsalo_35_2";
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
		break;

		case "LEDR_Gonsalo_35_1":
			dialog.text = "Now you know how I felt when I first saw those undead. I hope they're gone for good... Otherwise, I doubt I'll survive another encounter like that.";
			link.l1 = "Well, since we're done here, it's time to get out of this place. Get aboard, I'll drop you off at the port of Sharptown.";
			link.l1.go = "LEDR_Gonsalo_36";
			AddCharacterExpToSkill(pchar, "leadership", 100);
		break;

		case "LEDR_Gonsalo_35_2":
			dialog.text = "Now you know how I felt when I first saw those undead. I hope they're gone for good... Otherwise, I doubt I'll survive another encounter like that.";
			link.l1 = "Well, since we're done here, it's time to get out of this place. Get aboard, I'll drop you off at Sharptown port.";
			link.l1.go = "LEDR_Gonsalo_36";
			AddCharacterExpToSkill(pchar, "Fortune", 100);
		break;
		
		case "LEDR_Gonsalo_36":
			DialogExit();
			AddDialogExitQuestFunction("LEDR_12");
		break;
		
		case "LEDR_Gonsalo_37":
			dialog.text = "Thank you once again, Captain "+GetFullName(pchar)+". By the sea, that strange feeling is gone, and I hope it took its damned bag of bones with it. How about we have a drink, eh?";
			link.l1 = "Thank you for the invitation, Gonzalo, but I've got my hands full right now. Maybe another time. Have a drink for both of us.";
			link.l1.go = "LEDR_Gonsalo_38";
		break;
		
		case "LEDR_Gonsalo_38":
			if (CheckAttribute(npchar, "quest.LEDR_share"))
			{
				dialog.text = "I understand. But let me tell you this, Captain: after all we've been through together, I can't just leave without saying thank you. It wouldn't be right. Here, take this. In my youth, I chased after treasure more than once, I swear by the sea. But now my health isn't what it used to be, and my back gives me trouble. But you—you're young, a seasoned sailor. You'll find it with ease. Good luck to you, "+GetFullName(pchar)+", fair winds and seven feet under the keel.";
				link.l1 = "Thank you, Gonzalo. Good luck to you too, farewell.";
				AddMapPart();
			}
			else
			{
				dialog.text = "Well then, it’s time to say goodbye. Fair winds and safe travels, Captain "+GetFullName(pchar)+"!";
				link.l1 = "Farewell, Gonzalo.";
			}
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LEDR_14");
		break;
		
		
		
	}
}