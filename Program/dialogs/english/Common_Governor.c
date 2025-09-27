// boal 25/04/04 общий диалог Governor
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Governor\" + NationShortName(sti(NPChar.nation)) + "_Governor.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
    
    ref offref, sld;
    int i, cn;
    int qty;
    int iSumm;
    string attrLoc;

    /// выкуп колонии
    ref CaptGovenor, FortColony;
    int f, colony_money;

    int k = 1000;
    if (CheckAttribute(Nations[sti(NPChar.nation)], "Fort"))
    {
        k = (300 - sti(Nations[sti(NPChar.nation)].Fort)*10);
    }
	bool ok;
	
	attrLoc = Dialog.CurrentNode;
	if (findsubstr(attrLoc, "CityGive_" , 0) != -1)
 	{
        i = findsubstr(attrLoc, "_" , 0);
	 	NPChar.quest.CityIdx = strcut(attrLoc, i+1, strlen(attrLoc)-1); // индех в конце
 	    Dialog.CurrentNode = "ColonyGive";
 	}
 	
	switch (Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOff");
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "First time":
            NextDiag.TempNode = "First time";
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase("You dare show your face at the governor-general's office?! You're insane, indeed...","How did these lazybones let an enemy break into my residence? This is beyond me...","Surely, my guards aren't worth a coin if some tramp is running around in my residence..."),LinkRandPhrase("What do you need, "+GetSexPhrase("creep","stinker")+"?! My soldiers are already on your trail, "+GetSexPhrase("filthy pirate","stinker")+"!",""+GetSexPhrase("Filthy","Filthy")+" Murderer, leave my residence immediately! Guards!","I am not afraid of you, "+GetSexPhrase("scoundrel","rascal")+"! Soon you will be hanged in our fort, you won't get far..."));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("Soldiers aren't worth a damn...","You will never catch me."),RandPhraseSimple("Shut up, mate, or I'll rip out that foul tongue of yours!","I'm telling you, mate: sit quietly or I'll cut off your head and throw it through that door to your guard dogs..."));
				link.l1.go = "fight";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "I've heard that you were very persistent in requesting an audience. My name is "+GetFullName(npchar)+". I am the governor-general of the colonies of "+NationNameGenitive(sti(NPChar.nation))+", deputy of the Crown of "+NationKingsName(npchar)+" in these waters. Now, please be so kind as to tell me, what is the purpose of your visit, "+GetAddress_Form(NPChar)+".";
				link.l1 = "My name is "+GetFullName(pchar)+".";
				link.l1.go = "node_1";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = RandPhraseSimple("Oh, it's you again? Well, what do you want from the governor-general of "+NationNameGenitive(sti(NPChar.nation))+" this time?","And once again, you are distracting me from important affairs of state? What do you want, "+GetAddress_Form(NPChar)+"?");
				link.l1 = "I want to talk to you about working in the name of the Crown of "+NationNameGenitive(sti(NPChar.nation));
				link.l1.go = "work";
				link.l2 = "I need to talk to you about an important matter.";
				link.l2.go = "quests"; // файл нации
				//Jason --> Регата
				if (CheckAttribute(pchar, "questTemp.Regata.ToPortRoyal") && NPChar.location == "Portroyal_townhall")
				{
					link.l3 = "I came by invitation to participate in the regatta. Here's my invitation.";
					link.l3.go = "Regata";
				}
				//<-- Регата
				link.l10 = "I am sorry, but I have some business to attend to.";
				link.l10.go = "exit";
			}
		break;
		
		case "node_1":
			dialog.text = "So what brings you here to distract me from important affairs of state?";
			link.l1 = "I wanted to talk to you about working in the name of the Crown of "+NationNameGenitive(sti(NPChar.nation));
			link.l1.go = "work";
			link.l2 = "I was going to talk to you about an important matter.";
			link.l2.go = "quests";
			//Jason --> Регата
			if (CheckAttribute(pchar, "questTemp.Regata.ToPortRoyal") && NPChar.location == "Portroyal_townhall")
			{
				link.l3 = "I came here to participate in the regatta. Here's my invitation.";
				link.l3.go = "Regata";
			}
			//<-- Регата
			link.l10 = "It is just a courtesy visit, nothing more. "+GetAddress_FormToNPC(NPChar);
			link.l10.go = "node_2";
		break;

		case "node_2":
			dialog.text = "In that case, I would ask you to leave my office and stop distracting me from my work.";
			link.l1 = "Yes, yes, of course. Sorry for bothering you.";
			link.l1.go = "exit";
		break;
		
		case "work":
            dialog.text = "If you are looking for work, talk to the governors of the colonies. They are often in need of smart and brave captains.";
			link.l1 = "I'll keep that in mind. Thank you.";
			link.l1.go = "exit";
		break;
		
		//--> Jason регата
		case "Regata":
			dialog.text = "Oh, splendid, glad to see you, captain! You've arrived just in time – the regatta is about to begin in a few days. Did you read the rules of the regatta in the letter that must have been delivered to you by the messenger?";
			link.l1 = "Yes, sir, I did.";
			link.l1.go = "Regata_1";
			RemoveItems(PChar, "letter_open", 1);//уберем письмо
			TakeNationLicence(HOLLAND);//уберем лицензию
			DeleteAttribute(pchar, "questTemp.Regata.ToPortRoyal"); // patch-5
		break;
		
		case "Regata_1":
			dialog.text = "And have you prepared 50,000 pesos – your entrance fee, which will go towards the prize money?";
			if (makeint(Pchar.money) >= 50000)
			{
				link.l1 = "Yes, of course. Please accept my fee.";
				link.l1.go = "Regata_2";
			}
			link.l2 = "I am a bit short of money at the moment. But I will definitely bring it as soon as I can.";
			link.l2.go = "Regata_nomoney";
		break;
		
		case "Regata_2":
			dialog.text = "Very well. If you win, your money will be returned to you fivefold. Now, you should know how not to break the rules of the regatta.\nDiscuss the details with Henry Stevenson; he should be in the residence's room. Meet with him, he will explain everything.";
			link.l1 = "Alright. I'll do as you say.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -50000);
			pchar.quest.Regata_Guber.win_condition.l1 = "location";
			pchar.quest.Regata_Guber.win_condition.l1.location = "Portroyal_Roomtownhall";
			pchar.quest.Regata_Guber.function = "PrepareToRegataInPortroyal";
			pchar.questTemp.Regata.Begin = "true";
			NextDiag.TempNode = "First time";
		break;
		
		case "Regata_nomoney":
			dialog.text = "Fine, but please don't take too long, captain. The regatta is about to start soon.";
			link.l1 = "I see. I will try to bring you the money before the regatta starts.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Regata_1";
			pchar.questTemp.Regata.nomoney = "true";
		break;
		
		//регата-финал
		case "Regata_Final":
			dialog.text = "And here we have the winner of the regatta! Hello, Captain "+GetFullName(pchar)+"! Allow me to congratulate you on this well-deserved success! The winners of the regatta are always popular in English colonies, and deservedly so.";
			link.l1 = "Thank you, sir!";
			link.l1.go = "Regata_complete";
		break;
		
		case "Regata_complete":
			dialog.text = "Now let's move on to the most pleasant part for you - the award ceremony. The first prize is 250,000 pesos. Here you go!";
			link.l1 = "Thanks!";
			link.l1.go = "Regata_complete_1";
		break;
		
		case "Regata_complete_1":
			AddMoneyToCharacter(pchar, 250000);
			int iGift;
			string sItem1, sItem2, sItem3, sAdd;
			
			iGift = 3;
			switch (iGift)
			{
				case 0:
					sItem1 = "blade_10";//корд
					sItem2 = "cirass6";
					sItem3 = "bussol";
					sAdd = "cord, duelist's vest and boussole";
				break;
				
				case 1:
					sItem1 = "blade_15";//маринера
					sItem2 = "cirass2";//рейтарский панцирь
					sItem3 = "bussol";
					sAdd = "marinera, reiter's armour and boussole";
				break;
				
				case 2:
					sItem1 = "blade_17";//бретта
					sItem2 = "cirass7";//карацена
					sItem3 = "bussol";
					sAdd = "bretta, karacena and boussole";
				break;
				
				case 3://
					sItem1 = "blade_20";//мадонна
					sItem2 = "cirass2";//офицерская кираса
					sItem3 = "bussol";
					sAdd = "'Madonna', officer's cuirass and boussole";
				break;
			}
			GiveItem2Character(pchar, sItem1);
			GiveItem2Character(pchar, sItem2);
			GiveItem2Character(pchar, sItem3);
			dialog.text = "Also, you're eligible for a set of valuable prizes: "+sAdd+". Now it's all yours.";
			link.l1 = "I am very glad, sir! Really, I couldn't have expected it.";
			link.l1.go = "Regata_complete_2";
		break;
		
		case "Regata_complete_2":
			dialog.text = "In the name of all English colonies, I am glad to thank you for participating in the regatta and once again I congratulate you on your victory! If you placed a bet, now is the perfect time to see Sir Henry Stevenson and collect your winnings, if you haven't done so already. Best of luck to you, captain!";
			link.l1 = "Thank you for your kind words, sir! In turn, allow me to thank you for giving me the opportunity to take part in such a grand event. And now, please allow me to bid you farewell and take my leave.";
			link.l1.go = "Regata_complete_3";
		break;
		
		case "Regata_complete_3":
			DialogExit();
			NextDiag.CurrentNode = "First time";
		break;
		//<-- регата
	}
}
