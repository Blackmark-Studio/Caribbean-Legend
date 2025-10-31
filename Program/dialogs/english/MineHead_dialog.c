// диалог начальника шахты
void ProcessDialogEvent()
{
	ref NPChar, sld, location;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		location = &Locations[FindLocation(pchar.location)];
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase("You dare to show your face here?! I don't know if you're brave or just stupid...","How did these lazybones let an enemy break into my residence? This is beyond me...","Surely, my guards aren't worth a copper if such bastards are running around here..."),LinkRandPhrase("What do you need?"+GetSexPhrase("scoundrel","stinker")+"?! My soldiers are already on your trail, "+GetSexPhrase(", filthy pirate","")+"!","Dirty murderer, leave my residence immediately! Guards!","I am not afraid of you, "+GetSexPhrase("rat","slut")+"! Soon you will be hanged in our fort, and you won't get far after that..."));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("These soldiers aren't worth a single peso...","They will never get me."),RandPhraseSimple("Shut your mouth, "+GetWorkTypeOfMan(npchar,"")+", or I'll rip out that foul tongue of yours!","I'd suggest you sit quietly, and maybe you'll get through it alive..."));
				link.l1.go = "fight";
				break;
			}
			if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
			{
    			dialog.text = "Enemy in the mine! Alarm!";
				link.l1 = "Aaah, devil!";
				link.l1.go = "fight"; 
				break;
			}	
			dialog.text = LinkRandPhrase(""+TimeGreeting()+", señor. I am "+GetFullName(npchar)+", the mining engineer at the Los-Teques mine. What brings you here?","Hello, señor. What did you want?","Hmm... did you want anything from me, señor? I am listening.");
			if (!CheckAttribute(location, "quest.info"))
			{
				link.l9 = "I am new here, and I would like to learn more about this mine...";
				link.l9.go = "info";
			}
			if (GetSquadronGoods(pchar, GOOD_SLAVES) > 4)
			{
				link.l2 = "I have a cargo in my hold that might interest you. Slaves for your mine, to be exact. Care to haggle?";
				if (!CheckAttribute(location, "quest.slaves")) link.l2.go = "slaves_0";
				else link.l2.go = "slaves";
			}
			link.l1 = "I just came in to say hi, and I'm already leaving.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "info":
			dialog.text = "Los-Teques mine extracts gold for the Spanish Crown. Everything we extract belongs to Spain. Here, we find not only gold, but also silver nuggets and valuable precious stones. We don't sell gold here; everything we extract is delivered to the Old World under a reinforced convoy. But we have two exceptions for gold and silver nuggets. First, you can buy a certain amount of them in our local store from the quartermaster. Sometimes salaries don't arrive on time, so we have to keep some coin savings here for such cases; that is why local trading is allowed. Second, we are constantly in need of manpower, so we exchange nuggets for slaves. Therefore, talk to me if you have something to offer, and we will do business. I believe the rules of conduct in the mine are obvious: don't steal, don't distract the convicts, and don't bother the soldiers, otherwise you won't like the consequences.";
			link.l1 = "Fine, thank you!";			
			link.l1.go = "exit";
			location.quest.info = "true";
		break;
		
		// генератор купли-продажи рабов
		case "slaves_0":
			location.quest.slaves.qty = 200; // стартовая потребность
			dialog.text = "Of course, señor! How many do you have?";
			link.l1 = "I have "+FindRussianQtyString(GetSquadronGoods(pchar,GOOD_SLAVES))+".";
			link.l1.go = "slaves_1";
		break;
		
		case "slaves":
			location.quest.slaves.qty = sti(location.quest.slaves.qty)+GetNpcQuestPastDayParam(location, "slave_date"); // каждый день даёт +1 потребности
			if (sti(location.quest.slaves.qty) > 350) location.quest.slaves.qty = 350; // максимум потребности
			if (sti(location.quest.slaves.qty) < 5)
			{
				dialog.text = "Señor, unfortunately, right now we have no need for more slaves. But the situation can change at any time, so check back in a few weeks or some other time.";
				link.l1 = "Alright, señor, I understand. You don't need them now, but you might need them at some point.";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Of course, señor! How many do you have?";
				link.l1 = "I have "+FindRussianQtyString(GetSquadronGoods(pchar,GOOD_SLAVES))+".";
				link.l1.go = "slaves_1";
			}
		break;
		
		case "slaves_1":
			dialog.text = "For every slave, I am willing to pay you either one gold ingot or two silver ingots. Which do you choose?";
			link.l1 = "Gold ingots.";
			link.l1.go = "slaves_g";
			link.l2 = "Silver ingots.";
			link.l2.go = "slaves_s";
			link.l3 = "I am sorry, señor, but I've just changed my mind. Some other time.";
			link.l3.go = "slaves_exit";
		break;
		
		case "slaves_g":
			location.quest.slaves.type = "gold";
			dialog.text = "Fine. How many slaves are you going to sell me?";
			link.l1 = "";
			link.l1.edit = 6;
			link.l1.go = "slaves_trade";
		break;
		
		case "slaves_s":
			location.quest.slaves.type = "silver";
			dialog.text = "Fine. How many slaves are you going to sell me?";
			link.l1 = "";
			link.l1.edit = 6;
			link.l1.go = "slaves_trade";
		break;
		
		case "slaves_trade":
			iTotalTemp = sti(dialogEditStrings[6]);
			if (iTotalTemp < 1)
			{
				dialog.text = "Señor, I have no time for stupid jokes. If you're in the mood for jesting, go to the tavern!";
				link.l1 = "Hmm...";
				link.l1.go = "slaves_exit";
				break;
			}
			if (iTotalTemp > GetSquadronGoods(pchar, GOOD_SLAVES))
			{
				dialog.text = "Señor, I think you need to rest. Perhaps you're very tired or have suffered a heatstroke. Go to the tavern, get some rest, and then we can continue our bargaining.";
				link.l1 = "Hmm...";
				link.l1.go = "slaves_exit";
				break;
			}
			if (iTotalTemp > sti(location.quest.slaves.qty))
			{
				dialog.text = "Unfortunately, señor, right now we don't need that many slaves. The mine currently requires "+FindRussianQtyString(sti(location.quest.slaves.qty))+". Are you going to sell that many?";
				link.l1 = "Yes, of course!";
				link.l1.go = "slaves_max";
				link.l2 = "Hmm... I suppose I'm not.";
				link.l2.go = "slaves_exit";
				break;
			}
			dialog.text = ""+FindRussianQtyString(iTotalTemp)+"? Excellent. Please give the order to bring them to the town gates. I'll send my men for them.";
			link.l1 = "Don't worry, señor. Your slaves will be delivered to you in time. I will issue all relevant orders immediately.";
			link.l1.go = "slaves_calk";
		break;
		
		case "slaves_max":
			iTotalTemp = sti(location.quest.slaves.qty);
			dialog.text = "Excellent. Please order them to be brought to the town gates. I'll send my men for them.";
			link.l1 = "Don't worry, señor. Your slaves will be delivered to you in time. I will issue all relevant orders immediately.";
			link.l1.go = "slaves_calk";
		break;
		
		case "slaves_calk":
			DialogExit();
			Log_Info("Exchange of slaves for ingots has been completed");
			PlaySound("interface\important_item.wav");
			LAi_Fade("", "");
			WaitDate("",0,0,0,5,10);
			RemoveCharacterGoods(pchar, GOOD_SLAVES, iTotalTemp);
			if (location.quest.slaves.type == "gold") TakeNItems(pchar, "jewelry5", iTotalTemp);
			else TakeNItems(pchar, "jewelry6", iTotalTemp*2);
			DeleteAttribute(location, "slave_date");
			SaveCurrentNpcQuestDateParam(location, "slave_date");
			location.quest.slaves.qty = sti(location.quest.slaves.qty)-iTotalTemp;
		break;
		
		case "slaves_exit":
			DialogExit();
			DeleteAttribute(location, "slave_date");
			SaveCurrentNpcQuestDateParam(location, "slave_date");
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		    LAi_group_Attack(NPChar, Pchar);
			i = GetCharIDXByParam("CityType", "location", Pchar.location); // фантом солдат
			if (i != -1)
			{
			    LAi_group_Attack(&Characters[i], Pchar);
			}
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
