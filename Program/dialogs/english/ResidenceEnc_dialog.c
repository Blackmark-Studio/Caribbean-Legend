void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag, arRld, arDis;
	int i, Qty;

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

		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		//--------------------------------- леди в резиденции ---------------------------------
		case "ResWoman":
			NextDiag.TempNode = "ResWoman";
			if (LAi_grp_playeralarm <= 0 && CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o2") && !CheckAttribute(pchar, "questTemp.ChickenGod.Tasks.o2.Done") && !CheckAttribute(npchar, "quest.chickengod") && sti(npchar.nation) == SPAIN) {
				link.chickengod = "Senora, please excuse me, but I was asked to tell you that you have... a date inside an old pagan pyramid.";
				link.chickengod.go = "chickengod";
			}
			if (isBadReputation(pchar, 30))
			{
				dialog.text = LinkRandPhrase("Jesus! Such a despicable man in my chambers! Get away from here or I will call the guards!","This can't be happening... Who let this rat into my house? Get out of here, you bastard! You have no business here! Go away!","Such strange times have come. Rats are getting into my bedroom! Go away!");
				link.l1 = RandPhraseSimple("Easy there...","Watch your mouth...");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = LinkRandPhrase("What are you doing in my bedroom? Get out of here!","What a shame! I ask you to leave this place immediately!","Excuse me, sir, but you haven't been invited here. Please, leave my room!");
				link.l1 = RandPhraseSimple("Pardon me... I am leaving.","Sorry, wrong door. I have to go.");
				link.l1.go = "exit";
			}
		break;
		case "Woman_FackYou":
			dialog.text = "Oh, what was that?! I'm such a fool! Walking around, didn't see a thing... Guards!!!";
			link.l1 = "Shut up!";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
		break;
		//--------------------------------- слуга в резиденции ---------------------------------
		case "ResMan":
			NextDiag.TempNode = "ResMan";
			if (isBadReputation(pchar, 30))
			{
				dialog.text = LinkRandPhrase("Get away from here, rat!","Get away from the governor's estate immediately, rat!","I don't care what you're doing at the governor's house of "+XI_ConvertString("Colony"+npchar.city+"Gen")+"But my advice is, get lost now!");
				link.l1 = RandPhraseSimple("Take it easy, pal...","Watch your words!");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = LinkRandPhrase("Greetings! I am the governor's servant. My name is "+GetFullName(NPChar)+".","I watch over this place, "+GetAddress_Form(NPChar)+".","You know, "+GetAddress_Form(NPChar)+", our governor is a good man and pays us well...");
				link.l1 = RandPhraseSimple("Nice.","Hm, very well...");
				link.l1.go = "exit";
			}
		break;
		case "Man_FackYou":
			dialog.text = "So you decided to rob the governor?! Guards, seize the thief!!";
			link.l1 = "Shut your mouth!";
			link.l1.go = "fight";
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
		break;
		//--------------------------------- солдат в резиденции ---------------------------------
		case "ResGuard":
			NextDiag.TempNode = "ResGuard";
			if (isBadReputation(pchar, 30))
			{
				dialog.text = LinkRandPhrase("You'd better get out of here, "+GetSexPhrase("pal","girl")+"...","Go away!","Missed the door, "+GetSexPhrase("pal","girl")+"? ? This estate belongs to the governor of "+XI_ConvertString("Colony"+npchar.city+"Gen")+".");
				link.l1 = RandPhraseSimple("I'll leave when I want!","It's none of your business...");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = LinkRandPhrase("Today, I was ordered to serve here. Nice place...","I protect the estate of "+GetAddress_Form(NPChar)+".","My orders are to protect the governor's estate.");
				link.l1 = RandPhraseSimple("Good luck, then...","Hmm, I see...");
				link.l1.go = "exit";
			}
		break;
		
		case "chickengod":
			pchar.questTemp.ChickenGod.Tasks.o2.Counter = sti(pchar.questTemp.ChickenGod.Tasks.o2.Counter) + 1;
			if (sti(pchar.questTemp.ChickenGod.Tasks.o2.Counter) >= 3) {
				dialog.text = "Ah, yes. Finally! I'm ready to go with you, captain.";
				link.l1 = "Just like that? Señora, are you sure this is what you want?";
				link.l1.go = "chickengod_accept";
			} else {
				sld = CharacterFromID(npchar.city + "_Mayor");
				dialog.text = "What?! Are you drunk, señor? What an idiotic joke! Please go away, I beg of you! "+sld.name+"! Guards! Help!";
				link.l1 = "Shit, time to go.";
				link.l1.go = "chickengod_decline";
			}
			npchar.quest.chickengod = true;
		break;
		
		case "chickengod_accept":
			dialog.text = "Well, of course! Ah, Señor Aruba and I have been in an epistolary relationship for a long time!";
			link.l1 = "Since that's the case, please come aboard!";
			link.l1.go = "chickengod_accept_take";
			link.l2 = "No, señora, that will not do. My honour will not allow a woman to be put at risk, and you have clearly been misled!";
			link.l2.go = "chickengod_accept_nottake";
		break;
		
		case "chickengod_accept_take":
			DialogExit();
			
			pchar.questTemp.ChickenGod.Tasks.o2.Done = true;
			pchar.questTemp.ChickenGod.Tasks.o2.Lady = npchar.id;
			AddDialogExitQuestFunction("ChickenGod_TakeLady");
		break;
		
		case "chickengod_accept_nottake":
			dialog.text = "In that case, my dear captain, take your rustic sense of honour and shove it up your arse! I'll wait for another messenger, someone not as narrow-minded as you!";
			link.l1 = "Charming!";
			link.l1.go = "exit";
			
			pchar.questTemp.ChickenGod.Tasks.o2.Done = true;
			SetFunctionTimerCondition("ChickenGod_NotTakeLadyConsequence", 0, 1, 0, false);
		break;
		
		case "chickengod_decline":
			DialogExit();
			
			AddDialogExitQuestFunction("ChickenGod_LadyRefuse");
		break;
		
	}
}
