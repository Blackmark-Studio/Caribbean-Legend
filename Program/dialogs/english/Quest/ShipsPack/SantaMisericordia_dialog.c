void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag, arTmp;
	int i, n;
	string sTemp, sStr;
	
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
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Alamida_church":
			dialog.text = "...and of the Holy Spirit. Amen.";
			link.l1 = "I rarely see military men in churches.";
			link.l1.go = "Alamida_church_2";
		break;
		
		case "Alamida_church_2":
			dialog.text = "Many believe that faith and sword are incompatible. But doesn't a surgeon cut to heal? Doesn't a father punish to protect?";
			link.l1 = "Sounds like justification.";
			link.l1.go = "Alamida_church_3";
			link.l2 = "There's wisdom in that. Sometimes cruelty is necessary.";
			link.l2.go = "Alamida_church_4";
		break;
		
		case "Alamida_church_3":
			dialog.text = "You're mistaken. This isn't justification - it's understanding. When I first started my service, each death was... difficult. But then... my eyes were opened. 'Cruelty is the manifestation of supreme love.'";
			link.l1 = "I'll leave you to your prayers.";
			link.l1.go = "Alamida_church_5";
		break;
		
		case "Alamida_church_4":
			dialog.text = "Yes... yes! That's exactly what he said, the one who guided me on this path. 'Mercy without strength is useless, like a sword without a hand.'";
			link.l1 = "I'll leave you to your prayers.";
			link.l1.go = "Alamida_church_5";
		break;
		
		case "Alamida_church_5":
			dialog.text = "Pray for us all. For what we do... and what we must yet do.";
			link.l1 = "...";
			link.l1.go = "Alamida_exit";
		break;
		
		case "Alamida_guber":
			dialog.text = "Seven percent shortfall. Last time it was five. Growing like weeds in an abandoned garden...";
			link.l1 = "Is there a new governor in town?";
			link.l1.go = "Alamida_guber_2";
		break;
		
		case "Alamida_guber_2":
			dialog.text = "What? Ah, no. His Excellency is there, in the corner. I am don Fernando de Alamida, royal inspector.";
			link.l1 = "Must be difficult work.";
			link.l1.go = "Alamida_guber_3";
		break;
		
		case "Alamida_guber_3":
			dialog.text = "You know what's the hardest part about fighting corruption? The guilty aren't necessarily bad people. They have children, families. And each time you must remind yourself: poison remains poison, even when served in a golden cup.";
			link.l1 = "But can one judge so harshly? We're all human...";
			link.l1.go = "Alamida_guber_4";
			link.l2 = "You're too soft. Only prison will reform them.";
			link.l2.go = "Alamida_guber_5";
		break;
		
		case "Alamida_guber_4":
			dialog.text = "Mercy to the wolf is cruelty to the sheep. So said... a wise man. And with each passing day, I understand his wisdom more and more.";
			link.l1 = "I won't distract you from your work any longer.";
			link.l1.go = "Alamida_guber_6";
		break;
		
		case "Alamida_guber_5":
			dialog.text = "Hm. You know, I used to think the same way. But prison is too simple. Something more is needed... Purification.";
			link.l1 = "I won't distract you from your work any longer.";
			link.l1.go = "Alamida_guber_6";
		break;
		
		case "Alamida_guber_6":
			dialog.text = "Yes. The papers won't wait. Though sometimes it seems to me that behind each number here hides someone's fate.";
			link.l1 = "...";
			link.l1.go = "Alamida_exit";
		break;
		
		case "Alamida_city":
			dialog.text = "I'm listening carefully, "+GetAddress_Form(NPChar)+"? What made you approach me just like this, on the street?";
			link.l1 = "You stand out from the rest.";
			link.l1.go = "Alamida_city_2";
		break;
		
		case "Alamida_city_2":
			dialog.text = "Don Fernando de Alamida, royal inspector. You're the first such curious one today. Everyone hides, everyone fears me. Yet an honest person has nothing to fear. What does that tell us?";
			link.l1 = "That your reputation frightens them?";
			link.l1.go = "Alamida_city_3";
			link.l2 = "That honest people are few?";
			link.l2.go = "Alamida_city_4";
		break;
		
		case "Alamida_city_3":
			dialog.text = "Amusing. I thought so too. Until I understood - fear purifies. When a person is afraid, they become more honest. Closer to their true nature. To God.";
			link.l1 = "Interesting thought. I must go. Good day, don Fernando.";
			link.l1.go = "Alamida_city_5";
		break;
		
		case "Alamida_city_4":
			dialog.text = "Interesting... You reason just like someone I knew. Pity not everyone can accept this truth.";
			link.l1 = "Interesting thought. I must go. Good day, don Fernando.";
			link.l1.go = "Alamida_city_5";
		break;
		
		case "Alamida_city_5":
			dialog.text = "Good? Yes, perhaps. As long as it is righteous.";
			link.l1 = "...";
			link.l1.go = "Alamida_exit";
		break;
		
		case "Alamida_exit":
			DialogExit();
			
			sld = CharacterFromID("SantaMisericordia_clone_church");
			sld.dialog.filename = "Quest\ShipsPack\SantaMisericordia_dialog.c";
			sld.dialog.currentnode = "Alamida_repeat";
			sld = CharacterFromID("SantaMisericordia_clone_city");
			sld.dialog.filename = "Quest\ShipsPack\SantaMisericordia_dialog.c";
			sld.dialog.currentnode = "Alamida_repeat";
			sld = CharacterFromID("SantaMisericordia_clone_guber");
			sld.dialog.filename = "Quest\ShipsPack\SantaMisericordia_dialog.c";
			sld.dialog.currentnode = "Alamida_repeat";
		break;
		
		case "Alamida_repeat":
			dialog.text = "Anything else, Captain?";
			link.l1 = "No, don Fernando, just saying hello, nothing more.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Alamida_repeat";
		break;
		
		case "Alamida_abordage":
			if (startHeroType == 4)
			{
				dialog.text = "A maiden with a sword? Well, I never thought I'd live to see such a sight. And who might you be, señorita, to dare attack the 'Holy Mercy'?";
				link.l1 = "Captain Hellen McArthur. And that look of surprise on your face is one I know well.";
				link.l1.go = "Alamida_HelenaCaptain";
			}
			else
			{
				dialog.text = "How dare you?! Attack the 'Holy Mercy'?! A ship that carries the will of the king and... Well. Since you're here, tell me - why? Why did you choose this madness?";
				link.l1 = "I'm a pirate. And your galleon is surely full of treasures.";
				link.l1.go = "Alamida_abordage_Gold";
				link.l2 = "Such a beautiful ship... I must possess it.";
				link.l2.go = "Alamida_abordage_Ship";
				link.l3 = "I am an enemy of your country, don Fernando.";
				link.l3.go = "Alamida_abordage_Hater";
				link.l4 = "Just because. Why not?";
				link.l4.go = "Alamida_abordage_Prikol";
			}
		break;
		
		case "Alamida_HelenaCaptain":
			dialog.text = "How you resemble the Virgin Mary, protector of our ship... Just as beautiful. But She protects the righteous, while you...";
			link.l1 = "I've come for your ship. And compliments won't help here, don Fernando.";
			link.l1.go = "Alamida_HelenaCaptain_2";
		break;
		
		case "Alamida_HelenaCaptain_2":
			dialog.text = "How sad. I'll have to teach you humility then. By force, since there's no other way.";
			link.l1 = "...";
			link.l1.go = "Alamida_abordage_SecondRound";
		break;
		
		case "Alamida_abordage_Gold":
			dialog.text = "Ah yes. Of course. Gold. Always gold. The poison that corrodes souls. For it you shall die.";
			link.l1 = "Don't be so dramatic. This is just business.";
			link.l1.go = "Alamida_abordage_Gold_2";
		break;
		
		case "Alamida_abordage_Gold_2":
			dialog.text = "Every coin in the hold is sinners' payment for purification. You want it? Then share their fate.";
			link.l1 = "...";
			link.l1.go = "Alamida_abordage_SecondRound";
		break;
		
		case "Alamida_abordage_Ship":
			dialog.text = "Many have coveted the 'Holy Mercy'. Its beauty has been the doom of many a captain.";
			link.l1 = "Then I shall be the first to claim it.";
			link.l1.go = "Alamida_abordage_Ship_2";
		break;
		
		case "Alamida_abordage_Ship_2":
			dialog.text = "Mercy without strength is useless, like a sword without a hand. This lesson you shall learn today.";
			link.l1 = "...";
			link.l1.go = "Alamida_abordage_SecondRound";
		break;
		
		case "Alamida_abordage_Hater":
			dialog.text = "So that's it. Another jealous of Empire's greatness.";
			link.l1 = "What greatness? Your rigid ways are holding this world back.";
			link.l1.go = "Alamida_abordage_Hater_2";
		break;
		
		case "Alamida_abordage_Hater_2":
			dialog.text = "Don't lie to yourself. Fear of Spain makes you more honest. Closer to your true nature. You'll see for yourself now.";
			link.l1 = "...";
			link.l1.go = "Alamida_abordage_SecondRound";
		break;
		
		case "Alamida_abordage_Prikol":
			dialog.text = "Madman. Or perhaps you were sent to me as a test?";
			link.l1 = "Not everything needs a reason, señor.";
			link.l1.go = "Alamida_abordage_Prikol_2";
		break;
		
		case "Alamida_abordage_Prikol_2":
			dialog.text = "He said people like you are the most dangerous. But this will only strengthen my hand in battle.";
			link.l1 = "...";
			link.l1.go = "Alamida_abordage_SecondRound";
		break;
		
		case "Alamida_abordage_SecondRound":
			DialogExit();
			
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			LAi_SetImmortal(npchar, false);
			LAi_SetCurHPMax(npchar);
			LAi_GetCharacterMaxEnergy(npchar);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_BRDENEMY);
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, false);
			LAi_SetCheckMinHP(npchar, 1, true, "SantaMisericordia_TrirdRound");
		break;
		
		case "Alamida_abordage_TrirdRound":
			if (startHeroType == 4)
			{
				dialog.text = "Such strength of spirit... Such will...";
				link.l1 = "Surprised?";
			}
			else
			{
				dialog.text = "Not bad. It's been a while since I met a worthy opponent.";
				link.l1 = "I won't give you time to rest.";
			}
			link.l1.go = "Alamida_abordage_TrirdRound_2";
		break;
		
		case "Alamida_abordage_TrirdRound_2":
			if (startHeroType == 4)
			{
				dialog.text = "I was warned... about such a trial. About beauty that could shake a warrior's faith.";
				link.l1 = "Do you always complicate simple things so much, don Fernando?";
			}
			else
			{
				dialog.text = "The Lord gives strength to those who serve a righteous cause. Though... sometimes I'm no longer sure what I serve.";
				link.l1 = "Having doubts?";
			}
			link.l1.go = "Alamida_abordage_TrirdRound_3";
		break;
		
		case "Alamida_abordage_TrirdRound_3":
			if (startHeroType == 4)
			{
				dialog.text = "Simple? No... There must be a higher meaning. This is a test. I cannot be wrong.";
			}
			else
			{
				dialog.text = "No. He taught me not to doubt. Never.";
			}
			link.l1 = "...";
			link.l1.go = "Alamida_abordage_TrirdRound_4";
		break;
		
		case "Alamida_abordage_TrirdRound_4":
			DialogExit();
			
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			LAi_SetImmortal(npchar, false);
			LAi_SetCurHPMax(npchar);
			LAi_GetCharacterMaxEnergy(npchar);
			npchar.MultiFighter = 2.5;
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_BRDENEMY);
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, false);
			LAi_SetCheckMinHP(npchar, 1, true, "SantaMisericordia_Molitva");
			
			PlaySound("Ambient\Tavern\glotok_001.wav");
			PlaySound("Ambient\Horror\Fear_breath_01.wav");
		break;
		
		case "Alamida_abordage_Molitva":
			dialog.text = "Wait... Wait. You've won. I'm wounded, bleeding out. Allow me to pray before death.";
			link.l1 = "Very well.";
			link.l1.go = "Alamida_abordage_Molitva_2";
		break;
		
		case "Alamida_abordage_Molitva_2":
			if (startHeroType == 4)
			{
				dialog.text = "Lord... forgive me my sins and give me strength in this hour of trial. Bless the souls of my fallen comrades. Faithful sailors, they died believing they carried justice\nFather, I tried to live by your teachings, to fight injustice. But your son has stained the honor of the Alamida family. Forgive me\nMotherland... I swore to serve you faithfully and truly. But my fervor, my anger... I became what I sought to fight against\nDiego... Perhaps he lied? All this time... Woe to me if so\nAnd bless this woman, Lord. Perhaps in your final mercy you sent her to me... so that I might see how far I had strayed. Amen.";
			}
			else
			{
				dialog.text = "Lord... forgive me my sins and give me strength in this hour of trial. Bless the souls of my fallen comrades. Faithful sailors, they died believing they carried justice\nFather, I tried to live by your teachings, to fight injustice. But your son has stained the honor of the Alamida family. Forgive me\nMotherland... I swore to serve you faithfully and truly. But my fervor, my anger... I became what I sought to fight against\nDiego... Perhaps he lied? All this time... Woe to me if so\nHoly Virgin Mary, pray to God for us and grant us your mercy. Amen.";
			}
			link.l1 = "I don't recognize you, don Fernando. You seem like a different person now. And who were you talking about?";
			link.l1.go = "Alamida_abordage_Molitva_3";
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "Church_Stay_1", "", 5.0);
		break;
		
		case "Alamida_BitvaEnd":
			DialogExit();
			
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "SantaMisericordia_CanLeaveCauta", 5);
		break;
			
		case "Alamida_abordage_Molitva_3":
			DialogExit();
			
			LAi_SetPlayerType(pchar);
			LAi_SetImmortal(npchar, false);
			LAi_KillCharacter(npchar);
			
			DoQuestFunctionDelay("Alamida_abordage_OfficerPodhodit", 2.0);
		break;
		
		//Элен
		case "Alamida_Helena":
			dialog.text = "My captain, congratulations! What a fierce battle. That captain was skilled, oh so skilled. But you... you proved even better. How proud I am of you...";
			link.l1 = "Thank you, my love. Are you hurt?";
			link.l1.go = "Alamida_Helena_2";
		break;
		
		case "Alamida_Helena_2":
			dialog.text = "No, no. Though I thought we were on the edge a couple of times - both before boarding and during it. And you, are you alright?";
			link.l1 = "I'm fine, thank you again. Go rest in the cabin, I'll join you soon.";
			link.l1.go = "Alamida_BitvaEnd";
		break;
		
		//Мэри
		case "Alamida_Mary":
			dialog.text = "Charles, are you alright? I came as soon as I could, alright.";
			link.l1 = "I'm alright, thank you, dear. Though it was quite a struggle.";
			link.l1.go = "Alamida_Mary_2";
		break;
		
		case "Alamida_Mary_2":
			dialog.text = "I'm glad! But... Listen, Charles? Why did we attack these people? The Lord won't forgive us this, no. This ship... like a great temple. When I saw it, my heart trembled, just like when I saw a real church for the first time, not just in books. And now it bleeds!";
			link.l1 = "Mary... You know appearances can be deceiving. And behind the mask of piety were those who took money from simple believers - just like you. Understand?";
			link.l1.go = "Alamida_Mary_3";
		break;
		
		case "Alamida_Mary_3":
			dialog.text = "I... I believe you, Charles. Alright. Only... let's donate at least some of the gold we found here to those who truly need it? It would ease my heart.";
			link.l1 = "We'll do that, Mary. I promise. Now gather your thoughts and try to calm down. It's all over.";
			link.l1.go = "Alamida_BitvaEnd";
		break;
		
		//Томми
		case "Alamida_Tommi":
			dialog.text = "Ha, well, congratulations on your victory, captain! Now that's what I call business! Such a haul on this galleon!..";
			link.l1 = "Your grin is even wider than usual today, Tommy.";
			link.l1.go = "Alamida_Tommi_2";
		break;
		
		case "Alamida_Tommi_2":
			dialog.text = "You bet! Such spoils. And what a fight. Reminded me of the Revolution. And also... heh.";
			link.l1 = "What is it, Tommy? Come on, speak up.";
			link.l1.go = "Alamida_Tommi_3";
		break;
		
		case "Alamida_Tommi_3":
			dialog.text = "How they've decked out the whole ship like a floating cathedral. And gathered so much gold from everywhere. True papist holy rollers! Disgrace and laughable.";
			link.l1 = "This is a treasury ship, Tommy. Not a church ship.";
			link.l1.go = "Alamida_Tommi_4";
		break;
		
		case "Alamida_Tommi_4":
			dialog.text = "Not much difference in our case. Either way, I was glad to teach those dons and papists a good lesson! Can't stand either of them. I thoroughly enjoyed this day, ha-ha-ha!";
			link.l1 = "You never change! Alright, dismissed. Everything's under control here.";
			link.l1.go = "Alamida_BitvaEnd";
		break;
		
		//Тичингиту
		case "Alamida_Tichingitu":
			if (startHeroType == 1)
			{
				dialog.text = "Captain Charles, we win victory. This be difficult fight. Even Tichingitu find it hard, and me be one of best warrior in village.";
				link.l1 = "True, my friend. They were worthy opponents indeed.";
			}
			if (startHeroType == 2)
			{
				dialog.text = "Señor de Montoya, ship be ours.";
				link.l1 = "Very good, Tichingitu. I just finished here too.";
			}
			if (startHeroType == 3)
			{
				dialog.text = "Captain Paterson, last resistance crushed on ship.";
				link.l1 = "You're late, Tich! Next time better stick with me. Not that I couldn't handle it alone, mind you...";
			}
			if (startHeroType == 4)
			{
				dialog.text = "Captain McArthur, you be alright?";
				link.l1 = "Yes, Tichingitu, I'm fine, thank you for asking. And stop doubting your captain - I handled it perfectly well on my own.";
			}
			link.l1.go = "Alamida_Tichingitu_2";
		break;
		
		case "Alamida_Tichingitu_2":
			if (startHeroType == 1)
			{
				dialog.text = "Spirits tell me this during fight. And ask why me kill them. Now me ask you same thing. Tichingitu see in their eyes, they not be villains. Not yet.";
				link.l1 = "Ah, what can I tell you? I don't have an answer, Tichingitu.";
			}
			if (startHeroType == 2)
			{
				dialog.text = "Me want ask you question, Captain de Montoya.";
				link.l1 = "I'm listening.";
			}
			if (startHeroType == 3)
			{
				dialog.text = "Tichingitu want ask you question, Captain William, if you allow.";
				link.l1 = "Granted.";
			}
			if (startHeroType == 4)
			{
				dialog.text = "Me not doubt, me worry for you, captain.";
				link.l1 = "Alright, alright. I can see in your eyes that you want to ask me something else.";
			}
			link.l1.go = "Alamida_Tichingitu_3";
		break;
		
		case "Alamida_Tichingitu_3":
			if (startHeroType == 1)
			{
				dialog.text = "Hmm, as you say, captain. We finish here?";
				link.l1 = "Yes. I'll look around a bit more, then join the others.";
				link.l1.go = "Alamida_BitvaEnd";
			}
			if (startHeroType == 2)
			{
				dialog.text = "These people, they not be from same tribe as you? They not be Spanish? Why you decide attack?";
				link.l1 = "That's true. But don't Indian tribes fight each other too? Or aren't there quarrels and feuds within one tribe?";
				link.l1.go = "Alamida_Tichingitu_4";
			}
			if (startHeroType == 3)
			{
				dialog.text = "This ship look like church. You hate church and white god?";
				link.l1 = "Not at all. But it's just decoration, you see? This is a treasury ship. Though you wouldn't understand - I heard your people don't even know what taxes are. Lucky devils.";
				link.l1.go = "Alamida_Tichingitu_4";
			}
			if (startHeroType == 4)
			{
				dialog.text = "Yes. Be true. Captain MacArthur, why we attack this floating church?";
				link.l1 = "Floating church, ha-ha-ha! No, no. This is a treasury ship. Hmm, I see you don't quite understand. Well, they were carrying gold. I can imagine how proud Jan will be when I tell him I defeated Fernando de Alamida!";
				link.l1.go = "Alamida_Tichingitu_4";
			}
		break;
		
		case "Alamida_Tichingitu_4":
			if (startHeroType == 2)
			{
				dialog.text = "Hmm, you be right, captain. But with Indians this happen less than with white man.";
				link.l1 = "Perhaps. Well, this man was... interfering with me.";
				link.l1.go = "Alamida_Tichingitu_5";
			}
			if (startHeroType == 3)
			{
				dialog.text = "Be true, Maskogi have no castles and taxes.";
				link.l1 = "Exactly. You can go, you're late anyway. Later we'll decide what to do with this beautiful galleon. I don't like these tubs, but damn, she's a beauty.";
				link.l1.go = "Alamida_BitvaEnd";
			}
			if (startHeroType == 4)
			{
				dialog.text = "Tichingitu also proud of you, captain. And congratulate on victory in this hard fight.";
				link.l1 = "Thank you. Now let's get to dividing the spoils.";
				link.l1.go = "Alamida_BitvaEnd";
			}
		break;
		
		case "Alamida_Tichingitu_5":
			dialog.text = "Interfering, Señor de Montoya?";
			link.l1 = "Exactly. This Archipelago is too small for both of us. And I am of far more use to our state here. Remember Cocoa Leaf - he did more harm than good to his brothers. Same here.";
			link.l1.go = "Alamida_Tichingitu_6";
		break;
		
		case "Alamida_Tichingitu_6":
			dialog.text = "Now me understand. Tichingitu may go, captain?";
			link.l1 = "Yes, go. I'll join you all soon too.";
			link.l1.go = "Alamida_BitvaEnd";
		break;
		
		//замечение по обнажённому оружию
		case "CitizenNotBlade":
			dialog.text = LinkRandPhrase("Hey, what's the deal with all that weapon swinging?! Put it away this instant!", "I order you to put away your weapon at once!", "Hey, " + GetAddress_Form(NPChar) + ", stop scaring the people! Put away your weapon.");
			link.l1 = LinkRandPhrase("Alright, I'll put it away...", "Already done.", "As you say...");
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Screw you!", "I guess I'm gonna use it!", "I'll put it away when the time is right.");
			link.l2.go = "fight";
		break;
		
	}
} 