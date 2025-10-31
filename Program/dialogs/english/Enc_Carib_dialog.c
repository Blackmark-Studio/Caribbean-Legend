void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, Diag;
	int i, iGun, iMush, qty;
	string sGroup, sLink, sText;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);
	int iTemp = sti(npchar.EncQty);
	string sTemp = "Carib" + locations[FindLocation(npchar.location)].index + "_";

	switch(Dialog.CurrentNode)
	{
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();			
		break;
		
		case "First time":
			dialog.text = "Congratulations! This is a bug. Contact Jason and tell him how and where you found this one. Peace!";
			link.l1 = "I will do it immediately!";
			link.l1.go = "exit";
			Diag.TempNode = "First time";
		break;

		case "exit_fight":
			sGroup = "CaribGroup_" + locations[FindLocation(npchar.location)].index;
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_SetWarriorTypeNoGroup(sld);
				LAi_group_MoveCharacter(sld, sGroup);
				LAi_RemoveCheckMinHP(sld);
				LAi_SetImmortal(sld, false);
			}
			LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(sGroup, "LandEnc_CaribAfrer");
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "exit_peace":
			DialogExit();
			sGroup = "CaribGroup_" + locations[FindLocation(npchar.location)].index;
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_SetWarriorTypeNoGroup(sld);
				LAi_group_MoveCharacter(sld, sGroup);
				LAi_SetImmortal(sld, false);
				LAi_CharacterDisableDialog(sld);
			}	
			ChangeIndianRelation(1.00);
		break;
		
		// военные индеи - карибы
		case "war_indian":
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_type_actor_Reset(sld);
				LAi_RemoveCheckMinHP(sld);
				LAi_SetImmortal(sld, false);
			}
			if (sti(pchar.questTemp.Indian.relation) > 79)
			{
				dialog.text = LinkRandPhrase("Hail to you, son of the sea! I've heard about you. You may walk freely on our land.",""+npchar.name+" greets you, pale-faced brother. We are glad to see you as our guest.","I greet you, brave pale-faced warrior! "+npchar.name+" is glad to meet a friend of the Indians. Go in peace!");
				link.l1 = RandPhraseSimple("And hail to you, red-skinned brother! Good hunting to you!","Greetings, brave warrior! May the gods bless you and your family!");
				link.l1.go = "exit_peace";
				if (CheckCaribGuns())
				{
					npchar.quest.count = 0;
					link.l2 = RandPhraseSimple("I have something that might interest you, red-skinned brother. Wanna trade?","I can offer you something interesting to buy, brave warrior. Want to trade?");
					link.l2.go = "war_indian_trade";
				}
			}
			else
			{
				dialog.text = LinkRandPhrase("Stop, paleface! By what right do you walk on my land?","Stop, white man! You are on the land of my forefathers and my land!","Stop, paleface! You do not belong on my land");
				link.l1 = RandPhraseSimple("Your land? Get lost, you red-faced scum!","Look at him - a talking ape! Get lost, now!");
				link.l1.go = "war_indian_1";
				link.l2 = RandPhraseSimple("I've come in peace, red-skinned warrior. We shouldn't fight for nothing.","I am not an enemy to you or your land, warrior. I've come in peace.");
				if (sti(pchar.questTemp.Indian.relation)+(makeint(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP)/3)) > hrand(80)) link.l2.go = "war_indian_2_1";
				else link.l2.go = "war_indian_2_2";
				link.l3 = RandPhraseSimple("I've come to trade with you, not to fight.","I don't fight with Indians. I trade with them.");
				if (sti(pchar.questTemp.Indian.relation)+(makeint(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP)/6)+makeint(GetSummonSkillFromName(pchar, SKILL_FORTUNE)/6)) > hrand(90)) link.l3.go = "war_indian_3_1";
				else link.l3.go = "war_indian_3_2";
			}
		break;
		
		case "war_indian_1":
			dialog.text = RandPhraseSimple("You'll regret the day you were born, pale-faced dog... I'll cut out your heart and roast it over the fire!","I'll make you eat stones, pale-faced dog! We'll laugh as you beg for death on your knees, white cur!");
			link.l1 = RandPhraseSimple("You still can't shut your filthy mouth, you painted scarecrow? I'll drive you back to the jungle you crawled out from!","You dare threaten me, scum?! Well, now you'll climb back up the tree you just came down from!");
			link.l1.go = "exit_fight";
		break;
		
		case "war_indian_2_1":
			dialog.text = RandPhraseSimple("I hear your voice speaks true. We will not bare our axes against you this day. Go in peace, paleface.","Paleface rarely brings peace, but I see in your eyes you speak the truth. Go now.");
			link.l1 = RandPhraseSimple("A wise decision, warrior. Good luck to you.","I am glad we have come to an understanding, warrior.");
			link.l1.go = "exit_peace";
		break;
		
		case "war_indian_2_2":
			dialog.text = RandPhraseSimple("You lie, paleface cur! You came here to kill Indians! Ready for battle, paleface?!","You kill Indians. White tongue is a lying tongue. I cut it off and fry it on the fire!");
			link.l1 = RandPhraseSimple("Well, mate, don't blame me then. God knows, I tried to avoid it...","Well, you asked for it, warrior.");
			link.l1.go = "exit_fight";
		break;
		
		case "war_indian_3_1":
			if (CheckCaribGuns())
			{
				npchar.quest.count = 0;
				dialog.text = "Trade? We need the white man's weapon. The one-handed fire weapon of the pale-faced! For that, we will trade our wares! Do you have a fire weapon to trade?";
				link.l1 = "Hmm. I do. And what will you give me in exchange?";
				link.l1.go = "war_indian_trade";
				link.l2 = "You scoundrel! And then you'll shoot the colonists with my pistols? No, that won't happen! As for you, jackals, I'll cut you all down now...";
				link.l2.go = "exit_fight";
			}
			else
			{
				dialog.text = "You do not have what we want, paleface... You will be our war trophy!";
				link.l1 = "Try if you dare, scarecrow...";
				link.l1.go = "exit_fight";
			}
		break;
		
		case "war_indian_3_2":
			dialog.text = RandPhraseSimple("We do not trade with paleface dogs. We kill and take!","We are not filthy Miskito or Arawaks, we do not trade with palefaces! We kill them and take war trophies!");
			link.l1 = RandPhraseSimple("Well, then try to rob me, scoundrel!","First, you'll have to take my saber from me, you filth!");
			link.l1.go = "exit_fight";
		break;
		
		case "war_indian_trade":
			iGun = 1;
			dialog.text = "You show what you have, and we say what we'll give for it.";
			for (i=6; i>=1; i--)
			{
				if (GetCharacterFreeItem(pchar, "pistol"+i) > 0)
				{
					sLink = "l"+iGun;
					link.(sLink) = "Offer "+XI_ConvertString("pistol"+i)+".";
					link.(sLink).go = "gun_"+i;
					iGun++;				
				}
			}
		break;
		
		case "gun_1":
			npchar.quest.gun = "pistol1";
			if (hrand(1) == 0)
			{
				npchar.quest.item = "potion"+(rand(2)+2);
				iTotalTemp = hrand(1)+1;
				sText = ""+FindRussianQtyString(iTotalTemp)+"  vial of good curative potion";
			}
			else
			{
				npchar.quest.item = "jewelry"+(hrand(9)+14);
				iTotalTemp = hrand(2)+1;
				sText = ""+FindRussianQtyString(iTotalTemp)+" this beautiful stone";
			}
			dialog.text = "Hey-ho! We'll give you for it "+sText+".";
			link.l1 = "Deal!";
			link.l1.go = "war_indian_trade_agree";
			link.l2 = "No. No way.";
			link.l2.go = "war_indian_trade_bad";
		break;
		
		case "gun_2":
			npchar.quest.gun = "pistol2";
			if (hrand(3) < 2)
			{
				npchar.quest.item = "potion"+(rand(2)+2);
				iTotalTemp = hrand(2)+2;
				sText = ""+FindRussianQtyString(iTotalTemp)+" vial of good curative potion";
			}
			else
			{
				npchar.quest.item = "jewelry"+(hrand(3)+1);
				iTotalTemp = hrand(2)+2;
				sText = ""+FindRussianQtyString(iTotalTemp)+" this beautiful stone";
			}
			dialog.text = "Hey-ho! Cunning weapon... We'll give you something for it "+sText+".";
			link.l1 = "Deal!";
			link.l1.go = "war_indian_trade_agree";
			link.l2 = "No. No way.";
			link.l2.go = "war_indian_trade_bad";
		break;
		
		case "gun_3":
			npchar.quest.gun = "pistol3";
			if (hrand(5) < 3)
			{
				qty = rand(1)+2;
				npchar.quest.item = "jewelry5"+qty;
				iTotalTemp = hrand(6)+qty*15;
				sText = ""+FindRussianQtyString(iTotalTemp)+" this beautiful pearl";
			}
			else
			{
				npchar.quest.item = "jewelry"+(hrand(2)+2);
				iTotalTemp = hrand(2)+5;
				sText = ""+FindRussianQtyString(iTotalTemp)+"  this beautiful stone";
			}
			dialog.text = "Hey-ho! Mighty weapon! Kills many, many enemies! We give you for it "+sText+".";
			link.l1 = "Deal!";
			link.l1.go = "war_indian_trade_agree";
			link.l2 = "No. No way.";
			link.l2.go = "war_indian_trade_bad";
		break;
		
		case "gun_4":
			npchar.quest.gun = "pistol4";
			if (hrand(9) < 8)
			{
				qty = rand(1)+1;
				npchar.quest.item = "jewelry"+(qty+4);
				iTotalTemp = hrand(10)+qty*30;
				sText = ""+FindRussianQtyString(iTotalTemp)+" piece of metal which paleface loves more than life";
			}
			else
			{
				npchar.quest.item = "obereg_"+(hrand(10)+1);
				iTotalTemp = 1;
				sText = "this amulet";
			}
			dialog.text = "Hey-ho! A fearsome weapon... We'll give you this for it "+sText+".";
			link.l1 = "Deal!";
			link.l1.go = "war_indian_trade_agree";
			link.l2 = "No. No way.";
			link.l2.go = "war_indian_trade_bad";
		break;
		
		case "gun_5":
			npchar.quest.gun = "pistol5";
			if (hrand(7) < 7)
			{
				if (hrand(10) < 8)
				{
					npchar.quest.item = "jewelry7";
					iTotalTemp = 2+hrand(1);
				}
				else
				{
					npchar.quest.item = "jewelry8";
					iTotalTemp = hrand(4)+10;
				}
				qty = hrand(1)+1;
				npchar.quest.item = "jewelry"+(qty+6);
				if (qty == 1) iTotalTemp = 2;
				else iTotalTemp = hrand(5)+qty*15;
				sText = ""+FindRussianQtyString(iTotalTemp)+" this beautiful and precious petrified tar";
			}
			else
			{
				npchar.quest.item = "indian_"+(hrand(10)+1);
				iTotalTemp = 1;
				sText = "this amulet";
			}
			dialog.text = "Hey-ho! Beautiful and mighty weapon! Killed many, many enemies! We give you for it "+sText+".";
			link.l1 = "Deal!";
			link.l1.go = "war_indian_trade_agree";
			link.l2 = "No. No way.";
			link.l2.go = "war_indian_trade_bad";
		break;
		
		case "gun_6":
			npchar.quest.gun = "pistol6";
			if (hrand(9) < 8)
			{
				qty = rand(1)+1;
				npchar.quest.item = "jewelry"+(qty+4);
				iTotalTemp = hrand(8)+qty*20;
				sText = ""+FindRussianQtyString(iTotalTemp)+" piece of metal which paleface loves more than life";
			}
			else
			{
				npchar.quest.item = "amulet_"+(hrand(10)+1);
				iTotalTemp = 1;
				sText = "this amulet";
			}
			dialog.text = "Hey-ho! Handy weapon... We'll give you something for it "+sText+".";
			link.l1 = "Deal!";
			link.l1.go = "war_indian_trade_agree";
			link.l2 = "No. No way.";
			link.l2.go = "war_indian_trade_bad";
		break;
		
		case "war_indian_trade_agree":
			ChangeIndianRelation(1.00);
			npchar.quest.count = sti(npchar.quest.count)+1;
			TakeNItems(pchar, npchar.quest.item, iTotalTemp);
			RemoveItems(pchar, npchar.quest.gun, 1);
			Log_Info("You have given "+XI_ConvertString(npchar.quest.gun)+"");
			Log_Info("You have received "+XI_ConvertString(npchar.quest.item)+" in amount of "+FindRussianQtyString(iTotalTemp)+"");
			PlaySound("interface\important_item.wav");
			if (sti(npchar.quest.count) > 3+hrand(2));
			{
				dialog.text = "Good. Here are your goods. We won't trade anymore. Come back later. We give more for better fiery weapon. Now go!";
				link.l1 = "Farewell, red-skinned warrior.";
				link.l1.go = "exit_peace";
			}
			else
			{
				dialog.text = "Fine. Here are your goods. Do you have more fiery weapons to trade?";
				if (CheckCaribGuns())
				{
					link.l1 = "I have. Will you buy?";
					link.l1.go = "war_indian_trade";
				}
				link.l2 = "No. Next time I'll bring more.";
				link.l2.go = "war_indian_trade_exit";
			}
		break;
		
		case "war_indian_trade_exit":
			dialog.text = "Bring it. Bring a better fiery weapon and we will give you more for it. Now go!";
			link.l1 = "See you, warrior...";
			link.l1.go = "exit_peace";
		break;
		
		case "war_indian_trade_bad":
			if (sti(pchar.questTemp.Indian.relation) > 79)
			{
				DialogExit();
				sGroup = "CaribGroup_" + locations[FindLocation(npchar.location)].index;
				for(i = 0; i < iTemp; i++)
				{
					sld = CharacterFromID(sTemp + i);
					LAi_SetWarriorTypeNoGroup(sld);
					LAi_group_MoveCharacter(sld, sGroup);
					LAi_SetImmortal(sld, false);
					LAi_CharacterDisableDialog(sld);
				}	
			}
			else
			{
				dialog.text = "Then we take everything for free, paleface!";
				link.l1 = "You may try...";
				link.l1.go = "exit_fight";
			}
		break;
		
		// мирные индеи - мискито
		case "peace_indian":
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_type_actor_Reset(sld);
				LAi_RemoveCheckMinHP(sld);
				LAi_SetImmortal(sld, false);
			}
			dialog.text = LinkRandPhrase("Hail, white man. What do you need in our jungle?","Our jungle is very dangerous. What are you doing here?","What brings you here, brave paleface?");
			link.l1 = RandPhraseSimple("I was just passing by, my red-skinned friend. I believe there's enough room on this path for both of us?","Greetings, son of the jungle! I am here on business, and I don't fight against Indians.");
			link.l1.go = "peace_indian_1";
			link.l2 = RandPhraseSimple("And why do you need to know? Go your own way and stay out of trouble!","Go your own way, red-skinned one. I have no time to talk to you.");
			link.l2.go = "peace_indian_2";
		break;
		
		case "peace_indian_1":
			dialog.text = RandPhraseSimple("We are peaceful people. We are not enemies with white men. Go, but be careful on our land!","I am glad to meet the pale-faced friend of the Indians. Go in peace, son of the sea!");
			link.l1 = RandPhraseSimple("Good luck to you, too, son of the selva...","Farewell, red-skinned friend.");
			link.l1.go = "exit_peace";
		break;
		
		case "peace_indian_2":
			dialog.text = RandPhraseSimple("We are peaceful hunters. But we will not stand for palefaces speaking like that on our land!","We do not fight with white men, but if white men offend us, we answer as our forefathers taught us!");
			link.l1 = RandPhraseSimple("You still can't shut your foul mouth, you painted scarecrow? I'll drive you back to the jungle you crawled out of!","You dare threaten me, scum?! Now you'll climb back up the tree you just came down from!");
			link.l1.go = "exit_fight";
		break;
	}
}
