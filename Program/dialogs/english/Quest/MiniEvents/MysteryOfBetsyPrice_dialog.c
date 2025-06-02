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

		case "Poorman_1":
			if (pchar.sex == "woman")
			{
				dialog.text = "Hey, beauty, how about an exquisite ornament for your lady's collection? A genuine treasure! For you - admiring glances, and for me - a few coins for bread and a sip of rum.";
			}
			else
			{
				dialog.text = "Hey, Cap, how about an exquisite gift for your lady? A genuine treasure! For you - her warm gratitude, and for me - a few coins for bread and a sip of rum.";
			}
			link.l1 = "So that in an hour soldiers would come for me and throw me in prison for theft? Where did you get it, vagrant?";
			link.l1.go = "Poorman_2_fortune";
			link.l2 = "An exquisite gift? And where would someone like you, a homeless man, get such a thing?";
			link.l2.go = "Poorman_2_leadership";
			if (npchar.quest.meeting == "0") npchar.quest.meeting = "1";
		break;

		case "Poorman_2_fortune":
			dialog.text = ""+GetSexPhrase("Cap, I","I")+" found this beautiful pendant with a cameo, honest word! May I sink if I'm lying! It was just lying there, unwanted. I couldn't just leave such beauty in the dirt, could I?";
			link.l1 = "All right. Show me what you've got there.";
			link.l1.go = "Poorman_3";
			link.l2 = "Who would take the word of such a respectable gentleman as yourself? Find someone else who's more gullible.";
			link.l2.go = "Poorman_exit";
			AddCharacterExpToSkill(pchar, "Fortune", 100);
		break;

		case "Poorman_2_leadership":
			dialog.text = ""+GetSexPhrase("Cap, I","I")+" found this beautiful pendant with a cameo, honest word! May I sink if I'm lying! It was just lying there, unwanted. I couldn't just leave such beauty in the dirt, could I?";
			link.l1 = "All right. Show me what you've got there.";
			link.l1.go = "Poorman_3";
			link.l2 = "Who would take the word of such a respectable gentleman as yourself? Find someone else who's more gullible.";
			link.l2.go = "Poorman_exit";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		
		case "Poorman_exit":
			DialogExit();
			AddDialogExitQuestFunction("TBP_PismoVDome");
		break;
		
		case "Poorman_3":
			dialog.text = "Look... it's quite a fine thing! I found it in a flowerbed, by the house with the lantern, near the tavern. But there's been no one there for a long time, so there's no one to return it to.";
			link.l1 = "Curious little trinket. And how much do you want for it?";
			link.l1.go = "Poorman_4";
		break;

		case "Poorman_4":
			dialog.text = "Only a hundred pesos"+GetSexPhrase(", Cap","")+"... mere pennies for someone like you! And for me – a whole week without worrying where to get a piece of bread. Just look at it – what a beauty!";
			if (sti(pchar.Money) >= 100)
			{
				link.l1 = "Alright, here’s your hundred pesos.";
				link.l1.go = "Poorman_5";
			}
			link.l2 = "I think I'll pass. Try your luck with someone else.";
			link.l2.go = "Poorman_exit";
		break;

		case "Poorman_5":
			dialog.text = "Thank you, "+GetAddress_Form(NPChar)+"! Now fortune is sure to smile on you! You're a good person, it's easy to see.";
			link.l1 = "...";
			link.l1.go = "Poorman_exit";
			GiveItem2Character(PChar, "jewelry24");
			pchar.questTemp.TBP_BuyKulon = true;
			pchar.questTemp.TBP_BuyKulonOtdatBetsy = true;
		break;
		
		case "Pirate_1":
			if (pchar.sex == "woman")
			{
				dialog.text = "O-o-oh, who's come to visit us? It seems you didn't get the wrong door, sweetheart... come in, come in! Take off your clothes, make yourself at home.";
				link.l1 = "Well, well... Who do we have here? Aren't you the same scoundrels who left that 'tender' threatening message for Betsy?";
			}
			else
			{
				dialog.text = "And w-w-what kind of squid is this?! Did you get the wrong door, you goat head? Get out of here before I gut you!";
				link.l1 = "Well, well... Who do we have here? Aren't you the same fools who left that nice threatening message for Betsy?";
			}
			link.l1.go = "Pirate_2";
		break;

		case "Pirate_2":
			if (pchar.sex == "woman")
			{
				dialog.text = "Betsy? To hell with that Betsy! What's more interesting is what you're doing here, sweetheart... Since you're here – no need to rush off, we'll find a way to keep you busy...";
			}
			else
			{
				dialog.text = "What the devil Betsy? Don't tempt fate, fool. While you can still leave on your own two feet – leave. Otherwise, we'll have to collect you piece by piece and carry you out in a bucket!";
			}
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_HouseBetsi_2");
		break;

		case "BetsiPrice_1":
			dialog.text = "Help! Help, I beg you!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_HouseBetsi_3");
			locCameraFromToPos(1.40, 1.62, 1.14, false, 2.58, -0.30, -1.64);
		break;
		
		case "Pirate_3":
			dialog.text = "...";
			link.l1 = "And there she is. You're in trouble up to your ears, friend, and if you don't want this to be your last mistake, I advise you to release her. Immediately.";
			link.l1.go = "Pirate_4";
		break;

		case "Pirate_4":
			dialog.text = "Ha! Heard that, Reggie? "+GetSexPhrase("He's","She's")+" even threatening us. "+GetSexPhrase("What a cocky slug","What cocky trash")+". Hey, let's show "+GetSexPhrase("this upstart what color his guts are","this upstart what real pain is")+".";
			link.l1 = "It's your funeral.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_HouseBetsi_4");
		break;

		case "Pirate_5":
			if (!CharacterIsAlive("TBP_Bandit_1"))
			{
				dialog.text = "...";
				link.l1 = "Now release the girl. Or you'll lie beside your friend.";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("TBP_HouseBetsi_6");
			}
			else
			{
				dialog.text = "...";
				link.l1 = "...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Pirate_5";
			}
		break;

		case "BetsiPrice_2":
			dialog.text = "Damned dogs! You thought I would keep quiet?!";
			link.l1 = "...";
			link.l1.go = "BetsiPrice_2_1";
			sld = CharacterFromID("TBP_Bandit_2");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, CharacterFromID("TBP_BetsiPrice"));
			CharacterTurnByChr(npchar, sld);
		break;

		case "BetsiPrice_2_1":
			dialog.text = "And you... You don't seem to be with them. Who are you?";
			link.l1 = "Captain "+GetFullName(pchar)+", at your service.";
			link.l1.go = "BetsiPrice_2_2";
			CharacterTurnByChr(npchar, pchar);
		break;

		case "BetsiPrice_2_2":
			dialog.text = "So, I owe you my life?";
			link.l1 = "Looks that way. But now something else is more important – who are these people and what have you gotten yourself into?";
			link.l1.go = "BetsiPrice_3";
		break;
		
		case "BetsiPrice_3":
			dialog.text = "These people... They were sent by an important English official. Once he was very close to me... and now, as you can see, he wishes my death.";
			link.l1 = "I think I'm starting to understand your story. You were his mistress, but at some point you decided you could use that to your advantage. Wanted to frighten him... tell his family?";
			link.l1.go = "BetsiPrice_4";
		break;

		case "BetsiPrice_4":
			dialog.text = "You're surprisingly close"+GetSexPhrase(" to the truth, handsome"," to the truth, cutie")+"... and at the same time very far from it. If that were the case, I would already be dead by now. Yes, I was his mistress, but it never occurred to me to create family dramas\nIt was all much more complicated: one day I found out that he had found himself a new plaything and decided to get rid of me, leaving me empty-handed. Just throw me away like an unwanted thing. Well, I'm not used to leaving with nothing\nSo I took what really had value – papers that could ruin his life – and fled to the New World. And then I offered a deal: his secrets in exchange for my safety and generous compensation\nThat's why I'm still alive – they need the documents. And I was in no hurry to reveal where they were hidden.";
			link.l1 = "Well, you're not only beautiful, but also devilishly cunning. You played boldly, but let's be honest – this game has already spiraled out of your control. Maybe it's time to think about another option, while there's still a chance to try to exit the game? If they found you here, it's unlikely you'll be able to hide somewhere else. Sooner or later your luck will run out.";
			link.l1.go = "BetsiPrice_5";
		break;

		case "BetsiPrice_5":
			dialog.text = "What are you suggesting? Just give him the documents and be left empty-handed? After everything I've been through?";
			link.l1 = "You do realize that for them you're just a problem that needs to be eliminated. They won't stop until they get what they want. But you still have a choice. Give the documents to that dimwit over there. Let him pass them to his master and assure him that you've given up your intentions and simply want all of this to end.";
			link.l1.go = "BetsiPrice_6";
		break;

		case "BetsiPrice_6":
			dialog.text = "If that's my only chance... Alright, I'm ready to take the risk. I've always kept the documents on me. I sewed them into my corset so I wouldn't be apart from them for even a moment. Hold on, just a second...";
			link.l1 = "...";
			link.l1.go = "BetsiPrice_7";
		break;

		case "BetsiPrice_7":
			dialog.text = "Here, take it. These are all the documents I had. Will you say a few parting words to that creature? You know how to be persuasive, don't you?";
			link.l1 = "I think he's already learned the main lesson. Now we just need to make clear to him what he should do.";
			link.l1.go = "exit";
			notification(StringFromKey("Neutral_15"), "BoxMinus");
			PlaySound("interface\\important_item.wav");
			AddDialogExitQuestFunction("TBP_HouseBetsi_11");
		break;
		
		case "Pirate_6":
			dialog.text = "...";
			link.l1 = "Stand up. And listen to me carefully, bastard. Here are the documents you were sent for. Take them to your master and tell him: if he continues to send killers after Betsy, they will meet the same fate as your friends. Tell him that she is leaving his life forever – and he has no more reason to pursue her. Let him take this as her voluntary step towards reconciliation. I hope he will be reasonable enough for this to end here. Did you understand everything, or do I need to drive this information into your head?";
			link.l1.go = "Pirate_7";
			notification(StringFromKey("Neutral_16"), "BoxMinus");
			PlaySound("interface\\important_item.wav");
		break;

		case "Pirate_7":
			dialog.text = "I understood everything, "+GetAddress_Form(NPChar)+"...";
			link.l1 = "Then get out of here. And don't even think about lingering – if I see you here again, you won't get a second chance.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_HouseBetsi_12");
		break;

		case "BetsiPrice_8":
			dialog.text = "Well, "+GetSexPhrase("my hero","my fury")+", it seems I even forgot to thank you... It's all because of the excitement. It's not every day that you find yourself captive, and then regain freedom thanks to such a brave "+GetSexPhrase("rescuer","rescueress")+". Tell me, is it a habit of yours – rescuing ladies from trouble, or am I just incredibly lucky?";
			link.l1 = "What can I say, Betsy, I have a weakness for dramatic entrances and "+GetSexPhrase("beautiful ladies","all sorts of adventures")+".";
			link.l1.go = "BetsiPrice_9";
		break;

		case "BetsiPrice_9":
			dialog.text = "My name is Miranda. Miranda Bell. I took the name Betsy when I had to disappear – new life, new name, you understand. I fled Europe so hastily that I grabbed only a few coins and a couple of jewels\nThe rest probably went to those bastards who were hunting me. Now instead of luxurious receptions and expensive outfits – a wretched hovel on the outskirts and work in a tavern. I never thought that one day I would be serving rum instead of savoring wine in good company...";
			link.l1 = "Even with all this, you look as if you hold fate in your hands. Perhaps that's where your true talent lies.";
			link.l1.go = "BetsiPrice_10";
		break;

		case "BetsiPrice_10":
			dialog.text = ""+GetSexPhrase("Flatterer. But, you know, it suits you well","You flatter me")+"... After all this, I feel somewhat uneasy. What if they're already waiting for me around the corner? Escort me home, be my "+GetSexPhrase("savior","savioress")+" for a little while longer.";
			link.l1 = "I'm not one to leave things half-finished. So, madam, I am at your service. Let's go.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_ProvodimDoDoma");
		break;

		case "BetsiPrice_11":
			dialog.text = "Here we are. You know, I didn't even ask what wind brought you to that house?";
			link.l1 = "I wasn't there by chance. The tavern keeper seemed seriously upset by your disappearance and asked me to find out what happened. Well, did I have a choice to refuse? Abandoning a lady in distress is an act unworthy of a captain.";
			link.l1.go = "BetsiPrice_12";
			if (CheckAttribute(pchar, "questTemp.TBP_BuyKulonOtdatBetsy") && pchar.questTemp.TBP_BuyKulonOtdatBetsy == true)
            {
			link.l2 = "I wasn't there by chance. This pendant brought me there. Take it.​ The tavern keeper seemed seriously upset by your disappearance and asked me to find out what happened. Well, did I have a choice to refuse? Abandoning a lady in distress is an act unworthy of a captain.";
			link.l2.go = "BetsiPrice_12_otdal_kulon";
			}
		break;
		
		case "BetsiPrice_12":
			dialog.text = "Ah, that's so noble, Captain "+pchar.name+"! Although, I'm sure the tavern keeper was more concerned about his profits than about me. Unfortunately, I can't invite you in today – I need to recover. The time spent in the basement hardly made me more beautiful. But if we don't see each other again – I won't forgive you for that. So come to the tavern tomorrow, I’ll have a... gift for you.";
			link.l1 = "Well, now I have yet another reason to stop by. See you, M... Betsy.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_ProvodimDoDoma_3");
		break;
		
		case "BetsiPrice_12_otdal_kulon":
			dialog.text = "Ah, that's so noble, Captain "+pchar.name+"! Although, I'm sure the tavern keeper was more concerned about his profits than about me. Unfortunately, I can't invite you in today – I need to recover. The time spent in the basement hardly made me more beautiful. But if we don't see each other again – I won't forgive you for that. So come to the tavern tomorrow, I’ll have a... gift for you.";
			link.l1 = "Well, now I have yet another reason to stop by. See you, M... Betsy.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_ProvodimDoDoma_3");
			TakeItemFromCharacter(pchar, "jewelry24");
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
		break;

		case "TBP_Helena_1":
			dialog.text = "Well, well... What a sweet farewell. Who is this disheveled lady? She looks like she's been sitting in a basement for a week, but even that didn’t stop you from devouring her with your eyes, did it, "+pchar.name+"?";
			link.l1 = "It's not what you thought. The girl found herself in a difficult situation, and I helped her get out. That's all.";
			link.l1.go = "TBP_Helena_2";
		break;

		case "TBP_Helena_2":
			dialog.text = "And you, of course, decided to become her knight in shining armor?";
			link.l1 = "You know, I can't stay on the sidelines when someone is in danger.";
			link.l1.go = "TBP_Helena_3";
		break;

		case "TBP_Helena_3":
			dialog.text = "Fine. But next time, "+pchar.name+", be more careful... and don't give me reasons to be jealous.";
			link.l1 = "Of course, darling. Let's get out of here, we still have a lot to do.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_ProvodimDoDoma_5");
		break;

		case "TBP_Mary_1":
			dialog.text = "Well, well... What a sweet farewell. Such care, such tender promises... You even call her by her name so affectionately, alright. Maybe I should disappear for a couple of days too, so you'd search for me with the same eagerness?";
			link.l1 = "Mary, you know you're my talisman, and she... is just a girl who got into trouble.";
			link.l1.go = "TBP_Mary_2";
		break;

		case "TBP_Mary_2":
			dialog.text = "Ah, of course! Just a poor thing who needs a knight! And that look of yours – was that just out of politeness too? You nearly undressed her with your eyes!";
			link.l1 = "Mary, you're exaggerating! Look how I look at you? See the difference? Or will I have to remind you... up close?";
			link.l1.go = "TBP_Mary_3";
		break;

		case "TBP_Mary_3":
			dialog.text = "Alright, "+pchar.name+", you've wriggled out of it this time, alright. But if I see such a scene again...";
			link.l1 = "Then I'll have to remind you again who holds the first and only place in my heart. Come on, dear, we still have a lot to do.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("TBP_ProvodimDoDoma_5");
		break;
		
		case "BetsiPrice_sex_1":

			switch (rand(1))
			{
				case 0:
					dialog.text = "Mmm... You can't imagine the thoughts running through my head when I'm this close to you... And how badly I want to make them real.";
					link.l1 = "Then stop just thinking about it... and show me each and every one.";
					link.l1.go = "exit";
					NextDiag.TempNode = "OS_Matros_again";
				break;

				case 1:
					dialog.text = "Ah, my dear"+GetSexPhrase("","")+"... you have no idea how hard it is for me to stay in control when you're near...";
					link.l1 = "Then enough of this sweet torture... Come to me...";
					link.l1.go = "exit";
					NextDiag.TempNode = "OS_Matros_again";
				break;
			}
			AddDialogExitQuestFunction("TBP_Betsi_sex_3");
		break;

		case "BetsiPrice_sex_2":
			switch (rand(1))
			{
				case 0:
					dialog.text = "Ah, "+GetSexPhrase("my sweet captain","my sweet "+pchar.name+"")+"... I'm still caught in this sweet madness.";
					link.l1 = "Perhaps this madness is worth remembering... or even repeating someday.";
					link.l1.go = "exit";
					NextDiag.TempNode = "OS_Matros_again";
				break;

				case 1:
					dialog.text = "Oh, "+pchar.name+"... If I say it was amazing, you won't get too full of yourself"+GetSexPhrase(", will you?",". will you?")+"?";
					link.l1 = "Only if you promise to say it again... in a whisper.";
					link.l1.go = "exit";
					NextDiag.TempNode = "OS_Matros_again";
				break;
			}
			AddDialogExitQuestFunction("TBP_Betsi_sex_7");
		break;

		
		
		
		
		
		
		
	}
}