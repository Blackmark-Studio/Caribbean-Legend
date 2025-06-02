// гид
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Want something?";
			link.l1 = "No, nothing.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "guide_0":
			SetAchievement("Test_Ach");
			PlaySound("Voice\English\LE\Greguar\Greguar_01.wav");
			dialog.text = "Pleasure to welcome you to the colonies, sir! Allow me to present myself: "+GetFullName(pchar)+". Are you coming from good old home?";
			link.l1 = "Good day, monsieur. My name is "+GetFullName(pchar)+". Yes, I've just stepped off the ship.";
			link.l1.go = "guide_1";
		break;
		
		case "guide_1":
			DelLandQuestMark(npchar);
			dialog.text = "Spotting a gentleman, I thought I should lend a hand. The New World has its own rules, and not knowing them can be costly. People of rank should stick together. There's plenty of riff-raff here who'd sell you out for a handful of coins\n"+
			"May I show you around and give you the basics?";
			link.l1 = "Very kind of you, monsieur! I'd be glad to.";
			link.l1.go = "guide_2";
			link.l2 = "Thank you, monsieur, but I'll find my own way.";
			link.l2.go = "guide_exit";
		break;
		
		case "guide_exit":
			dialog.text = "As you wish, Monsieur. Anyway, it was nice meeting you. Honorable gentlemen are rare guests here. I wish you the best of luck!";
			link.l1 = "And to you as well, "+GetFullName(npchar)+"!";
			link.l1.go = "guide_exit_1";			
		break;
		
		case "guide_exit_1":
			DialogExit();
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			DoQuestCheckDelay("NgtF3", 1.0);
			QuestPointerToLoc("FortFrance_town", "reload", "reload3_back");
		break;
		
		case "guide_2":
			dialog.text = "Excellent! Caribbean towns follow the same layout. Learn Saint-Pierre and every other port will make sense.";
			link.l1 = "";
			link.l1.go = "guide_tavern";		
		break;
		
		case "guide_tavern":
			dialog.text = "Tavern—the port's hub. Get a bed, rum, gossip, and hire sailors or officers. You can play cards, pick up work, or deal with smugglers and treasure map sellers.";
			link.l1 = "";
			link.l1.go = "guide_market";
			locCameraFromToPos(-2.08, 5.32, 68.88, true, -15.00, 0.90, 55.00);
		break;
		
		case "guide_market":
			dialog.text = "Market. Need supplies? The smith has blades, armor, and shot; the herb-woman sells tonics. Gypsies and monks trade charms, and the junk-dealer offers odds and ends for those who can craft.";
			link.l1 = "";
			link.l1.go = "guide_brothel";
			locCameraFromToPos(-13.58, 4.11, 69.06, true, -45.00, -6.00, 52.00);
		break;
		
		case "guide_brothel":
			dialog.text = "Brothel. Nothing lifts spirits like time with a skilled lady. If your vitality is low, drop in and leave a new man.";
			link.l1 = "";
			link.l1.go = "guide_bank";
			locCameraFromToPos(-2.75, 7.07, 61.10, true, 60.00, -6.60, 42.65);
		break;
		
		case "guide_bank":
			dialog.text = "Bank. Borrow or invest money, swap pesos for doubloons, and it's the best spot to sell jewels.";
			link.l1 = "";
			link.l1.go = "guide_prison";
			locCameraFromToPos(3.07, 7.64, 51.99, true, 45.00, -8.30, 4.50);
		break;
		
		case "guide_prison":
			dialog.text = "Prison. Few real villains inside—mostly drifters. Want a job from them? Talk to the commandant; a small bribe opens the cells.";
			link.l1 = "";
			link.l1.go = "guide_townhall";
			locCameraFromToPos(-50.52, 5.79, 38.60, true, -47.65, 3.95, 33.52);
		break;
		
		case "guide_townhall":
			dialog.text = "Governor's Palace. Merchants and captains come here for serious business. Keep the Governor friendly—his word shapes how his nation treats you.";
			link.l1 = "";
			link.l1.go = "guide_12";
			locCameraFromToPos(3.14, 7.39, 37.55, true, 1.06, 8.45, 14.14);
		break;
		
		case "guide_12":
			dialog.text = "Am I keeping you, my friend?";
			link.l1 = "Monsieur, I'm here to find my brother. They say he's in Saint-Pierre. A man of some importance—surely the Governor knows him…";
			link.l1.go = "guide_13";
			SetCameraDialogMode(npchar);
		break;
		
		case "guide_13":
			dialog.text = "Ah, I see. Our Governor is Jacques Dyel du Parquet. I'm sure he'll see you quickly.";
			link.l1 = "Who else might I ask? I'd rather not bother His Excellency right away.";
			link.l1.go = "guide_14";
		break;
		
		case "guide_14":
			dialog.text = "If your brother is well-known on Martinique, ask the townsfolk—someone will know. And his name?";
			link.l1 = "Michelle de Monper.";
			link.l1.go = "guide_15";
		break;
		
		case "guide_15":
			dialog.text = "I've heard the name, though we've never met. Ask around—or go straight to the Governor. Good luck, monsieur. We'll talk again!";
			link.l1 = "Thank you, "+GetFullName(npchar)+"!";
			link.l1.go = "guide_16";
		break;
		
		case "guide_16":
			DialogExit();
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);//запрет диалога
			LAi_group_MoveCharacter(npchar, "FRANCE_CITIZENS"); // пока идем заниматься Мишелем
			chrDisableReloadToLocation = false;//открыть локацию
			DoQuestCheckDelay("NgtF3", 1.0);
			QuestPointerToLoc("FortFrance_town", "reload", "reload3_back");
		break;
		
		case "guide_21":
			dialog.text = "Ah, it's you again! I hear you've set foot in the Knights' stronghold. Clearly you travel in high circles. Did you find your brother?";
			link.l1 = "Found him… in a way.";
			link.l1.go = "guide_22";
		break;
		
		case "guide_22":
			dialog.text = "Forgive me, but I don't hear much joy in that answer…";
			link.l1 = "True. I'd hoped to sail home on the next ship, but fate laughs at me. I'm stuck here—who knows for how long—and, on top of that, must learn to be a sailor.";
			link.l1.go = "guide_23";
		break;
		
		case "guide_23":
			dialog.text = "I'm not surprised. Word of your trip on the Ulysses has spread. Don't lose heart—owning a ship and the title of captain are no small things. You plan to buy a vessel, yes?";
			link.l1 = "Yes—blast it—I must. But I don't know where the yard is, how to sail, or how to raise the coin. Nothing!";
			link.l1.go = "guide_24";
		break;
		
		case "guide_24":
			dialog.text = "Money I lack, but in every other matter I'm at your service. Shall we continue the tour?";
			link.l1 = "You're right—knowledge is power.";
			link.l1.go = "guide_25";
			link.l2 = "Thank you, monsieur, but I'll manage from here.";
			link.l2.go = "guide_exit_11";
		break;
		
		case "guide_exit_11":
			dialog.text = "A pleasure. For funds, speak with the town's movers—perhaps the store merchant\n"+
			"Good luck, "+pchar.name+"—be bold and you'll manage.";
			link.l1 = "";
			link.l1.go = "guide_exit_12";			
		break;
		
		case "guide_exit_12":
			DialogExit();
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
		break;
		
		case "guide_25":
			dialog.text = "Then follow me! First things first—ships.";
			link.l1 = "";
			link.l1.go = "guide_shipyard";
		break;
		
		case "guide_shipyard":
			dialog.text = "Shipyard. Buy or repair ships here. Mostly small hulls, but a good one shows up now and then. Cannons and fancy sails too.";
			link.l1 = "";
			link.l1.go = "guide_port";
			locCameraFromToPos(-23.25, 7.74, 77.79, true, -27.85, 5.36, 73.65);
		break;
		
		case "guide_port":
			dialog.text = "Pier—your door to the sea. Once you own a ship, your boat waits here. For now, hire a navigator, purser, and cannoneer—they'll make life easier afloat.";
			link.l1 = "";
			link.l1.go = "guide_portoffice";
			locCameraFromToPos(-8.55, 4.06, 91.31, true, 40.00, -8.00, 0.00);
		break;
		
		case "guide_portoffice":
			dialog.text = "Port Office. Moor your ship here or pick up honest work—freight, escort, mail runs. The more jobs you finish, the better the pay.";
			link.l1 = "";
			link.l1.go = "guide_store";
			locCameraFromToPos(48.38, 9.48, 43.95, true, 43.69, 5.47, 48.13);
		break;
		
		case "guide_store":
			dialog.text = "Store. Captains come here for food, rum, medicine, powder, and shot. If it’s missing, find smugglers in the tavern. Without a good purser, trading wastes time and coin.";
			link.l1 = "";
			link.l1.go = "guide_gate";
			locCameraFromToPos(-21.10, 6.60, 45.21, true, -30.00, 3.70, 45.00);
		break;
		
		case "guide_gate":
			dialog.text = "Gates to the wilds. Dangerous, but useful to reach forts, hunt treasure, or cross to another settlement.";
			link.l1 = "";
			link.l1.go = "guide_45";
			locCameraFromToPos(50.58, 5.74, 23.21, true, 100.00, 0.00, 20.00);
			//AddQuestRecordInfo("Guide_OnLand", "1");
		break;
		
		case "guide_45":
			dialog.text = "Not every colony welcomes strangers. If you don’t want to wait for night, raise a different flag at sea, then rely on stealth—or buy a trade licence.";
			link.l1 = "";
			link.l1.go = "guide_46";
		break;
		
		case "guide_46":
			dialog.text = "You listen well, my friend. Care for some fun? A practice duel beyond the gates.";
			link.l1 = "Certainly! Sounds perfect.";
			link.l1.go = "guide_47";
			link.l2 = "Thank you, monsieur, but I’ll take it from here.";
			link.l2.go = "guide_exit_11";
		break;
		
		case "guide_47": // телепортируем за городские ворота
			DialogExit();
			LAi_SetActorType(npchar);
			DoQuestReloadToLocation("FortFrance_ExitTown", "goto", "goto19", "Guide_ExitTown");
		break;
		
		case "guide_49":
			dialog.text = "My friend, I take it you’re no stranger to fencing?";
			link.l1 = "Ha! Einen Entern habe ich schon hinter mir und sogar...";
			link.l1.go = "guide_50";
			if (FindCharacterItemByGroupWithout_knife_03(pchar, BLADE_ITEM_TYPE) == "")
			{
				GiveItem2Character(pchar, "blade_05");
				EquipCharacterByItem(Pchar, "blade_05");
			}
		break;
		
		case "guide_50":
			dialog.text = "Excellent. Shall we?";
			link.l1 = "Let’s dance!";
			link.l1.go = "guide_56";
			npchar.quest.guide_win = 0;
		break;
		
		case "guide_56": // махач
			LAi_SetPlayerType(pchar);
			LAi_SetCurHPMax(pchar); 
			LAi_GetCharacterMaxEnergy(pchar);
			LAi_SetCurHPMax(npchar); 
			LAi_GetCharacterMaxEnergy(npchar);
			LAi_SetImmortal(npchar, false);
			LAi_group_Delete("EnemyFight");
			if (MOD_SKILL_ENEMY_RATE <= 6)	// На первых трёх сложностях Валинье будет ослаблен
			{
				LAi_SetHP(npchar, LAi_GetCharacterMaxHP(npchar) * 0.7, LAi_GetCharacterMaxHP(npchar) * 0.7);
				npchar.rank = 1;
				SetSelfSkill(npchar, 1, 1, 1, 1, 1);
			}
			DialogExit();
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			// ставим проверяльщики
			LAi_SetCheckMinHP(pchar, 1, true, "Guide_HeroFail");
			LAi_SetCheckMinHP(npchar, 1, true, "Guide_HeroWin");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");
			//DoQuestCheckDelay("GuideFight_tutorial", 1.0);
		break;
		
		case "guide_57": // побил гида с первого раза
			dialog.text = "You... you are a man who knows how to hold his sword. Well done, Monsieur. You need more practice, but you have the potential to become a true swordmaster.";
			link.l1 = "Merci beaucoup. What now?";
			link.l1.go = "guide_62"; // нода на выход
			if (MOD_SKILL_ENEMY_RATE >= 6)
			{
				link.l2 = "More practice you say? Are you serious? I'm tired of this patronizing tone ever since I set foot in this miserable place!";				//Пасхалка Корсары 2 для сложности СФ и выше
				link.l2.go = "guide_64";
			}
			AddComplexSelfExpToScill(50, 50, 50, 50);
			AddCharacterExpToSkill(pchar, "Leadership", 80);
		break;
		
		case "guide_58": // побил гида со второго или третьего раза
			dialog.text = "Much better! See, all you need is to concentrate. You need more practice, one day you will become a decent fencer.";
			link.l1 = "Merci beaucoup. What now?";
			link.l1.go = "guide_62"; // нода на выход
			AddComplexSelfExpToScill(20, 20, 20, 20);
			AddCharacterExpToSkill(pchar, "Leadership", 30);
		break;
		
		case "guide_59": // побили первый раз
			dialog.text = "I won, Monsieur. Move faster, parry my stabs, jump back. A rematch?";
			link.l1 = "Oui! No mercy, Monsieur!";
			link.l1.go = "guide_56";
			link.l2 = "No, I had enough. Let's finish the lesson. What now?";
			link.l2.go = "guide_62"; // нода на выход
		break;
		
		case "guide_60": // побили второй раз
			dialog.text = "I won again, "+pchar.name+"! Don't lose your initiative. Catch my hits, feint them. If you see that I am going to hit hard - jump away or parry, don't just guard. Again!";
			link.l1 = "Come, Monsieur, I shall thrash you this time!";
			link.l1.go = "guide_56";
			link.l2 = "No, I've had enough. Let's finish the lesson. What now?";
			link.l2.go = "guide_62"; // нода на выход
		break;
		
		case "guide_61": // побили третий раз
			dialog.text = "You have a lot to learn, "+pchar.name+". Don't worry, you still got a lot of time to master your fencing. But be careful, don't take any chances until you know how to hold a weapon.";
			link.l1 = "I will consider it, Monsieur, but I have to say that you were just too lucky! This blasted heat... the only reason why I didn't beat the hell out of you. Merde, let's end our fencing lesson. What now?";
			link.l1.go = "guide_62"; // нода на выход
		break;
		
		case "guide_62":
			dialog.text = "Now it's time to say farewell, Monsieur. It was a pleasure. I hope that my presentation and training did you some good and will prove useful in the future. Perhaps, we shall meet again one day.\nAnd about the money you need - talk to important people of our city. Visit all the places that I have shown you today and speak to their owners. Ask around. Take a walk to the jungle and to the fort. Find a job or... well, I am not a priest or a judge, check people's houses and see what trinkets you can find in their unlocked chests. Just do it when their backs are turned or the guards will catch you.\nGood luck, "+pchar.name+", I have a strong feeling that you have the spark of true greatness inside you. Do your best to kindle it into a roaring fire!";
			link.l1 = "Merci, Monsieur. The pleasure was mine. Godspeed!";
			link.l1.go = "guide_63";
		break;
		
		case "guide_63":
			LAi_SetCurHPMax(pchar); 
			LAi_GetCharacterMaxEnergy(pchar);
			DialogExit();
			chrDisableReloadToLocation = false;//открыть локацию
			npchar.lifeday = 0;
			DoQuestReloadToLocation("FortFrance_Town", "quest", "quest2", "");
		break;
		
		case "guide_64": // решили убить Валинье
			dialog.text = "Hold your tongue, Monsieur! I won't tolerate such insolence any further. However, I understand your reaction to a new environment, therefore I forgive your outburst this time. But mind your words from now on. Farewell, Monsieur de Maure.";
			link.l1 = "No offense, Monsieur Valinnie. If we were in the Louvre at this moment, you'd watch your tone! It's time to teach a province a final lesson. Defend yourself!";
			link.l1.go = "guide_65";
		break;
		
		case "guide_65":
			DialogExit();
			
			npchar.rank = 25;
			int iHp = MOD_SKILL_ENEMY_RATE*10+300;
			LAi_SetHP(npchar, iHp, iHp);
			SetSelfSkill(npchar, 80, 80, 80, 80, 50);
			SetShipSkill(npchar, 50, 80, 35, 30, 50, 20, 30, 20, 80);
			SetSPECIAL(npchar, 9, 5, 8, 6, 5, 10, 8);
			SetCharacterPerk(npchar, "Energaiser");
			SetCharacterPerk(npchar, "BasicDefense");
			SetCharacterPerk(npchar, "AdvancedDefense");
			SetCharacterPerk(npchar, "CriticalHit");
			SetCharacterPerk(npchar, "Tireless");
			SetCharacterPerk(npchar, "HardHitter");
			SetCharacterPerk(npchar, "Sliding");
			SetCharacterPerk(npchar, "BladeDancer");
			SetCharacterPerk(npchar, "SwordplayProfessional");
			SetCharacterPerk(npchar, "Gunman");
			SetCharacterPerk(npchar, "GunProfessional");
			GiveItem2Character(npchar, "blade_30");
			EquipCharacterbyItem(npchar, "blade_30");
			GiveItem2Character(npchar, "cirass7");
			GiveItem2Character(npchar, "obereg_7");
			GiveItem2Character(npchar, "talisman11");
			AddMoneyToCharacter(npchar, 10000);
			AddItems(npchar, "gold_dublon", 25);
			AddItems(npchar, "bullet", 5);
			AddItems(npchar, "grapeshot", 5);
			AddItems(npchar, "GunPowder", 10);
			TakeItemFromCharacter(npchar, "blade_12");
			npchar.cirassId = Items_FindItemIdx("cirass4");
			LAi_SetCurHPMax(npchar);
			LAi_GetCharacterMaxEnergy(npchar);
			LAi_SetCurHPMax(pchar); 
			LAi_GetCharacterMaxEnergy(pchar);
			LAi_SetImmortal(npchar, false);
			LAi_group_Delete("EnemyFight");
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			npchar.SaveItemsForDead = true;
			npchar.DontClearDead = true;
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "Guide_HeroKill");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

string FindCharacterItemByGroupWithout_knife_03(ref chref, string groupID)
{
	ref refItm;
    string resultItemId;

	resultItemId  = "";
	for(i=TOTAL_ITEMS-1; i>=0; i--)
	{
		refItm = &Items[i];
		if( !CheckAttribute(refItm,"groupID") ) continue;
		if(refItm.groupID!=groupID) continue;
		if( !CheckAttribute(chref,"items."+refItm.id) ) continue;
		if(refItm.id == "knife_03") continue;
		if (groupID == BLADE_ITEM_TYPE)
		{
			resultItemId  = refItm.id;
		}
	}
	
	if (resultItemId != "")
	{
        return resultItemId;
	}

	return "";
}