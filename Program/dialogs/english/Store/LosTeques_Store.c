void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sLoc;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase("There's been an alarm raised in the town. Everyone's looking for you! I wouldn't wait around here for too long if I were you.","The whole town guard is scouring the town trying to find you. I'm not an idiot and I'm not going to talk to you!","Run, mate, before the soldiers make mincemeat out of you..."),LinkRandPhrase("What do you want, scoundrel?! The town guard is on your tail right now. You won't get far, filthy pirate!","Get out of my house, murderer! Guards!!","I'm not afraid of you, scamp! Soon they'll hang you, you won't get away..."));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("Heh, I'm not too worried about the alarm...","They have no chance of catching me."),RandPhraseSimple("Shut your pie hole, "+GetWorkTypeOfMan(npchar,"")+", or I'll cut out your bloody tongue!","Heh, "+GetWorkTypeOfMan(npchar,"")+", you want to hunt a pirate too! Listen, pal, keep calm and you'll live..."));
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = TimeGreeting()+"! I've never seen you before, señor. Dare I assume you're a captain... Did I guess right? My name is "+GetFullName(npchar)+", and my store is at your service. Gold, silver, and much more to pique the interest of a curious man.";
				Link.l1 = "I see. I'm "+GetFullName(pchar)+". Pleased to meet you, "+npchar.name+".";
				Link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = TimeGreeting()+", señor! I'm glad to see you again in my store. Would you like to acquire some gold nuggets? Or perhaps you'd be interested in minerals today?";
				link.l1 = "Show me your merchandise, "+npchar.name+".";
				link.l1.go = "trade";
				link.l4 = "No, I don't need anything, "+npchar.name+". I just stopped by to say hello to you.";
				link.l4.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting":
			dialog.text = "As am I, señor. Will you have a look at my merchandise? I'm sure I have something that will be of interest to you.";
			link.l1 = "This is my first time here and I'd like to find out a little more about this settlement.";
			link.l1.go = "info";
			link.l2 = "Then show me what you have for sale.";
			link.l2.go = "trade";
		break;
		
		case "info":
			dialog.text = "Our small town was built thanks to the gold mine. They extract gold ore, silver, and golden nuggets. Sometimes even gems. We used to have only a garrison here until friendly Indians and some white settlers joined us\nIgnacio Ortega built a tavern and made our lives a bit cheerier. All kinds of adventurers visit this place with the foolish intention of robbing us. We don't have a court here, so their numbers dropped after we hanged several idiots right in the middle of town\nGold ore is sent to the ships under the protection of soldiers and friendly Indians; nuggets, however, you can buy right here in this store\nBesides, I sometimes have very interesting minerals to offer, so visit me when you have time, I always resupply my stock.";
			link.l1 = "Thank you for the interesting story! I'll keep it in mind.";			
			link.l1.go = "exit";
		break;
		
		case "trade":
			DialogExit();
			if (!CheckAttribute(npchar, "trade_date") || GetNpcQuestPastDayParam(npchar, "trade_date") >= 10)
			{
				GiveItemToTrader(npchar);
				SaveCurrentNpcQuestDateParam(npchar, "trade_date");
			}
			LaunchItemsTrade(npchar, 0);
		break;

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

		// ============== Грабеж среди бела дня, попытка залезть в сундуки =========================
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Robbery in broad daylight!!! What's going on here?! Wait, hold on, friend...","Hey, what are you doing there?! Trying to rob me? Now you're screwed...","Wait, what the hell are you doing? Turns out you're a thief! Consider this the end of the line, bastard...");
			link.l1 = LinkRandPhrase("Devil!!","Caramba!!","Ah, shit!");
			link.l1.go = "fight_owner";
		break;
		
		case "fight_owner": // лесник . выход из диалога . если копался в сундуках. 
			LAi_SetOwnerTypeNoGroup(NPChar);
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			NextDiag.CurrentNode = "First time";
			DialogExit();
		break;
	}
}
