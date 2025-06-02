//Jason общий диалог уличных матросов
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	string sTemp;
	int iTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	// вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Citizen\" + NPChar.City + "_Citizen.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (npchar.quest.meeting == "0")
			{
				if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && CheckAttribute(npchar, "quest.crew"))//найм в команду
				{
					dialog.text = "Good day, "+GetAddress_Form(NPChar)+". I am aware that you are a captain of your own ship. I've got a deal for you.";
					link.l1 = "I am listening, "+GetAddress_FormToNPC(NPChar)+". What kind of deal?";
					link.l1.go = "crew";
					link.l2 = "Sorry, "+GetAddress_FormToNPC(NPChar)+", but I am in a hurry.";
					link.l2.go = "exit";
					npchar.quest.meeting = "1";
					DeleteAttribute(npchar, "talker"); //снимаем говорилку
					break;
				}
				dialog.text = LinkRandPhrase("Hey, captain! What do you want from a common sailor?","Good day, sir. How can I help you?","Good day, sir. Do you want anything?");
				link.l1 = "Glad to meet you, mate! My name is "+GetFullName(pchar)+". Got a minute to talk?";
				link.l1.go = "question";
				link.l2 = RandPhraseSimple("I've got a question for you.", "I need some information about this colony.");
				link.l2.go = "quests";//(перессылка в файл города)
				link.l3 = "Just wanted to say hi. See you!";
				link.l3.go = "exit";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "You again, sir? What else do you want?";
				link.l1 = "Got a minute to talk?";
				link.l1.go = "question";
				link.l2 = RandPhraseSimple("I've got a question for you.", "I need some information about this colony.");
				link.l2.go = "quests";//(перессылка в файл города)
				link.l3 = "No, pal, it's nothing. Good luck!";
				link.l3.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;

		case "question":
			dialog.text = NPCStringReactionRepeat(""+GetFullName(npchar)+" at your service, good sir! What do you want to know?", 
				"Glad to talk with you, captain!", 
				"Well... I suppose I still have some more time to talk...",
                "Unfortunately, I have to go now. Farewell!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Got anything interesting to tell me?", 
				"Got anything interesting to tell me?",
                "Got anything interesting to tell me?", 
				"Sure. Good luck!", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("rumours_sailor", "rumours_sailor", "rumours_sailor", "exit", npchar, Dialog.CurrentNode);
		break;

		case "crew":
			switch (hrand(2))
			{
				case 0: sTemp = "Me and my messmates were put shoreside from our last ship due to various sickness and injuries. But we are all healthy now and want to get back to work as sailors again. Do you want to hire us?"; break;
				case 1: sTemp = "Me and a few of my boys were paid off from a merchantman due to the end of its contract. We have been without a single piece of eight for a long time already so we want to get back to work again. Do you need some skillful sailors for your crew?"; break;
				case 2: sTemp = "Me and my mates just got back from a voyage two weeks ago. The ship's master has dismissed us and we've been having some great fun. But our pockets are empty now so it's time to set sail again. Do you want to hire us, captain?"; break;
			}
			dialog.text = sTemp;
			link.l1 = "Well, I am ready to discuss your proposal. How many of you and what are you good at?";
			link.l1.go = "crew_1";
			link.l2 = "I am sorry, sailor, but I've got enough men already. You should find yourself another captain.";
			link.l2.go = "exit";
		break;
		
		case "crew_1":
			switch (sti(npchar.quest.crew.type))
			{
				case 0: sTemp = "We are the best in working with sails and tackles. Not being overly modest, I'd say that we are professionals at ship handling, so don't worry, we won't let you down even in the strongest storms."; break;
				case 1: sTemp = "Most of all we like to be on the gun deck. Few of us even served on real warships. We can load and fire cannons in the way no one in your crew can. You can count on us in every hard fight!"; break;
				case 2: sTemp = "We're proper good boarders captain, did a few runs on privateers before this. We know the glitter of cutlasses and the smell of gunpowder and blood. That's our calling. It's not easy to defeat us in a hand-to-hand fight so you can always count on our blades, captain!"; break;
			}
			dialog.text = "There are "+sti(npchar.quest.crew.qty)+" of us and we will hire only together. We can perform all basic sailor tasks."+sTemp+"";
			if (GetFreeCrewQuantity(pchar) >= sti(npchar.quest.crew.qty))
			{
				link.l1 = "Sound like the men I'm looking for. What about your advance?";
				link.l1.go = "crew_2";
				link.l2 = "Sorry, sailor, but I need other skills at the moment. You should find yourself another captain.";
				link.l2.go = "exit";
			}
			else
			{
				link.l1 = "Sorry, sailor, but I don't have enough room on my ship. You should find yourself another captain.";
				link.l1.go = "exit";
			}
		break;
		
		case "crew_2":
			iTemp = sti(npchar.quest.crew.money)*sti(npchar.quest.crew.qty);
			dialog.text = ""+FindRussianMoneyString(sti(npchar.quest.crew.money))+" for each. And then the common sailor's wage per month. We won't ask anything excessive, captain.";
			if (sti(pchar.money) >= iTemp)
			{
				link.l1 = "You're hired! Take your coins. Now go to my ship, it is called '"+pchar.ship.name+"', right in the harbor. The boatswain will assign you all hammocks in the crew quarters and get your messes.";
				link.l1.go = "crew_3";
			}
			link.l2 = "Unfortunately, I can't afford to pay for you all. You should find yourself another captain.";
			link.l2.go = "exit";
		break;
		
		case "crew_3":
			iTemp = sti(npchar.quest.crew.money)*sti(npchar.quest.crew.qty);
			AddMoneyToCharacter(pchar, -iTemp);
			dialog.text = "Aye aye, captain! I will gather the lads and we'll be off immediately.";
			link.l1 = "Be quick about it, we sail at a moment's notice.";
			link.l1.go = "crew_4";
		break;
		
		case "crew_4":
			DialogExit();
			AddCharacterCrew(pchar, sti(npchar.quest.crew.qty));
			//увеличиваем опыт
			iTemp = makeint(sti(npchar.quest.crew.qty)*50/sti(pchar.ship.crew.quantity));
			switch (sti(npchar.quest.crew.type))
			{
				case 0: ChangeCrewExp(pchar, "Sailors", iTemp); break;
				case 1: ChangeCrewExp(pchar, "Cannoners", iTemp); break;
				case 2: ChangeCrewExp(pchar, "Soldiers", iTemp); break;
			}
			//увеличиваем мораль
			iTemp = makeint(sti(npchar.quest.crew.qty)/10)+1;
			AddCrewMorale(pchar, iTemp);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 20.0);
			npchar.lifeday = 0;
		break;

		//замечание по обнажённому оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar, "Hey, sheathe your sword, cap. None of us needs problems, right?", "Hey, sheathe your sword, cap. None of us needs problems, right?");
			link.l1 = LinkRandPhrase("Fine.", "As you wish.", "As you say.");
			link.l1.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
