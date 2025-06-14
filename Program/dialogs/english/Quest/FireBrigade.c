
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
    string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
// ГРИФФОНДОР -->
		case "FireBrigade_fra":
			dialog.text = GetSexPhrase("", "A woman... and a captain! Now I've seen everything. Mademoiselle, you are stunning. It's a shame your beauty brought so much sorrow to the Crown of France\n") + "That's how all Poincy's orders end. One in prison. The other—will either join him or fall in battle today.";
			link.l1 = "You're clearly out of place here. Why send such a bright officer and such a fine ship to do a bounty hunter's dirty work?";
			link.l1.go = "FraOff_1";
		break;

        case "FraOff_1":
			dialog.text = "Orders aren't up for discussion, they're to be carried out. If every captain chose which orders were worthy—we wouldn't have the Navy.";
			link.l1 = "Tell that to your men.";
			link.l1.go = "FraOff_2";
        break;

        case "FraOff_2":
			dialog.text = "You've cornered me and are trying to break my loyalties and my oath. That's a low blow, given the circumstances. Let's finish this with the clash of blades, not words!";
			link.l1 = "(Leadership) There's a third way. Stop doing dirty work unworthy of an officer. Join me—and I'll show you a different world.";
			link.l1.go = "FraOff_HireCheck";
            link.l2 = "To arms then!";
			link.l2.go = "FraOff_ExitFight";
        break;

        case "FraOff_HireCheck":
            if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 80)
            {
                notification("Skill Check Failed (80)", SKILL_LEADERSHIP);
                dialog.text = "Traitors are treated the same everywhere. And I won't become one. En garde!";
                link.l1 = "You had your chance, and you missed it. En garde!";
                link.l1.go = "FraOff_ExitFight";
                break;
            }
            notification("Skill Check Passed", SKILL_LEADERSHIP);
            dialog.text = "I swore loyalty to the crown, not to pompous, starched-up bureaucrats sending us to die to cover their own mess. But you—you're an enemy of my king, and I can't ignore that.";
			link.l1 = "I could atone for my sins against your country tomorrow—just need to pay the right middleman. That says more about your superiors than about me.";
			link.l1.go = "FraOff_Sucess";
        break;

        case "FraOff_Sucess":
			dialog.text = "That's true. And I'm tired of putting up with it. I'm ready to serve under your command, if you promise to leave the French alone.";
			link.l1 = "I don't know who our paths will cross with, and I can't guarantee anything. But I promise to be reasonable. Welcome to the crew, Officer " + NPChar.name + "!"; // своего имени он вообще-то не называл
			link.l1.go = "FraOff_Hired";
        break;

        case "FraOff_ExitFight":
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);
			QuestAboardCabinDialogExitWithBattle(""); 
            AddDialogExitQuest("MainHeroFightModeOn");
			DialogExit();	
        break;

        case "FraOff_Hired":
            AddBrigadierOfficer(sld, NPChar);
            DialogExit();
        break;

// ЭЛЬ КАСАДОР -->
		case "FireBrigade_spa":
            // to_do: чек нуля?
			dialog.text = "So this is what public enemy looks like. I hope you're proud of that title, pirate. You must have worked hard to earn it\nAccording to the Casa de Contratación, you've taken down " + (Statistic_AddValue(PChar, "spa_AbordShip", 0) + Statistic_AddValue(PChar, "spa_KillShip", 0)) + " ships flying the Spanish Crown's flag. And today, my beautiful ship will join that list" + GetSexPhrase(".","\nWoe to the Spanish fleet! We've suffered from disease, favoritism, treachery... But to be bested by a woman?");
			link.l1 = " You're the last one standing, your crew is dead. And you are too, you just haven't realized it yet.";
			link.l1.go = "Alonso_1";
			if(Statistic_AddValue(PChar, "spa_AbordShip", 0) + Statistic_AddValue(PChar, "spa_KillShip", 0) < 1)
			{
				Achievment_Set("ach_CL_159")
			}
		break;

		case "Alonso_1":
            dialog.text = "It's a shame de Alba didn't get this assignment. He would've done better. But I'll try to finish the job anyway.";
            link.l1 = "You're a true son of your homeland. Prepare to meet its heroes, señor.";
            link.l1.go = "Alonso_2";
            link.l2 = "The hunter became the prey. All your speeches were for nothing—it's as old as time.";
            link.l2.go = "Alonso_3";
        break;

        case "Alonso_2":
            ChangeCharacterComplexReputation(PChar, "nobility", 5);
            dialog.text = "Thanks for the breather, but now my sword will do the talking.";
            link.l1 = "To arms!";
            link.l1.go = "Alonso_ExitFight";
        break;

        case "Alonso_3":
            ChangeCharacterComplexReputation(PChar, "nobility", -5);
            dialog.text = "Thanks for the breather, but now my sword will do the talking.";
            link.l1 = "Prepare to die!";
            link.l1.go = "Alonso_ExitFight";
        break;

        case "Alonso_ExitFight":
        	SetCharacterPerk(NPChar, "Rush");
            ActivateCharacterPerk(NPChar, "Rush");
            PlaySound("Ambient\Tavern\glotok_001.wav");
            PlaySound("Types\" + LanguageGetLanguage() + "\warrior03.wav");
            SendMessage(NPChar, "lfffsfff", MSG_CHARACTER_VIEWSTRPOS, 0.0, 0.0, 0.1, XI_ConvertString("Rampage"), 255.0, 30.0, 30.0);
            NPChar.Unpushable = "";
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);
			QuestAboardCabinDialogExitWithBattle(""); 
            AddDialogExitQuest("MainHeroFightModeOn");
			DialogExit();
		break;

// ХИМЕРА -->
        case "FireBrigade_eng":
            // to_do: ты-вы у элен
            dialog.text = GetSexPhrase(PChar.Name + "! Your name pops up in the reports so often, I feel like we've known each other for ages", "Miss McArthur! Does your patron know what you're up to? Ah, never mind. I'm sure he'll be my next job anyway") + "\nYou're lucky: my bosses love sending urgent orders that contradict the last ones. If I weren't busy cleaning up the old crew from Antigua... Well, never mind. Enough. You're distracting me from real work.";
			link.l1 = "You're distracting me too.";
			link.l1.go = "Cortny_ExitFight";
		break;

        case "Cortny_ExitFight":
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);
			QuestAboardCabinDialogExitWithBattle("KnippelAppearance");
            AddDialogExitQuest("MainHeroFightModeOn");
			DialogExit();	
		break;

        case "Kneepel":
            dialog.text = "Chainshot to my stern, I almost missed it! If my old bones were a bit quicker, I'd have sent that bastard to the sea devil myself. Thank you, Cap. And thanks from my late patron too!";
			link.l1 = "Who are you? A prisoner? Did my crew free you?";
			link.l1.go = "Kneepel_1";	
		break;

        case "Kneepel_1":
            dialog.text = "Charlie Knippel in the flesh. The best gunner in the English navy!";
			link.l1 = "Courtney said he spent a long time tracking you down. What's the story?";
			link.l1.go = "Kneepel_2";	
		break;

        case "Kneepel_2":
            dialog.text = "For many years I served a brave English captain named Richard Fleetwood. We fought many battles together, serving our true passion—the English Navy. But one day, everything changed\nThe London brass used us as pawns. We attacked our own. Dirtied our uniforms cleaning up after others. And now it's our turn...";
			link.l1 = "No judgment here. Life's complicated, especially when you're not your own master.";
			link.l1.go = "Kneepel_2_good";
            link.l2 = "So, would you say the shadows of old sins finally caught up with you?";
			link.l2.go = "Kneepel_2_bad";
		break;

        case "Kneepel_2_good":
            dialog.text = "I don't regret serving my country. It's just... it stings, Cap. Especially for my patron and his poor wife.";
			link.l1 = "What now?";
			link.l1.go = "Kneepel_3";	
		break;

        case "Kneepel_2_bad":
            TEV.NoKneepel = "";
            dialog.text = "No need for the jabs... We've already paid the price for our sins in full!";
			link.l1 = "What now?";
			link.l1.go = "Kneepel_3";	
		break;

        case "Kneepel_3":
            dialog.text = "Now I'm a man with no name and no homeland. I could go anywhere, but for now, there's nowhere to go. And no one to go with. Gunners are needed everywhere, but not every ship has cannons.";
			link.l1 = "Join me. I can't say I've had the best relationship with the English fleet, but I respect its finest.";
            if(!CheckAttribute(&TEV, "NoKneepel"))
                link.l1.go = "Kneepel_3_good";
            else
                link.l1.go = "Kneepel_3_bad";
            link.l2 = "I've got cannons. If you're really that good, there's always a place for a true professional on my crew.";
			link.l2.go = "Kneepel_3_bad";
		break;

        case "Kneepel_3_good":
            dialog.text = "There's a noose waiting for me at home, same with the Spanish and Dutch, and I don't care for the French. But you, it seems, need a good gunner. I'm in, Captain. I'll head to the cabin at the first chance. Drop by sometime, we'll have a chat over some shot.";
			link.l1 = "Welcome aboard.";
			link.l1.go = "Kneepel_Hired";	
		break;

        case "Kneepel_3_bad":
            dialog.text = "No way. I'd rather commandeer a boat and disappear into the deepest hole in the archipelago. Thanks for the rescue, Captain, and goodbye.";
			link.l1 = "...";
			link.l1.go = "Kneepel_Escape";	
		break;

        case "Kneepel_Escape":
            DeleteAttribute(&TEV, "NoKneepel");
            DeleteAttribute(&TEV, "boardingReloadFreeze");
            NPChar.lifeday = 0;
            LAi_SetActorTypeNoGroup(NPChar);
            LAi_ActorRunToLocation(NPChar, "reload", "reload1", "none", "", "", "", -1.0);
            PostEvent("LAi_event_boarding_EnableReload", 5000);
            DialogExit();
		break;

        case "Kneepel_Hired":
            DeleteAttribute(&TEV, "NoKneepel");
            DeleteAttribute(&TEV, "boardingReloadFreeze");
            NPChar.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
            NPChar.Dialog.CurrentNode = "Knippel_officer";
            NPChar.quest.OfficerPrice = sti(PChar.rank)*200; // Артефакт
            NPChar.quest.meeting = true;
            NPChar.OfficerImmortal = true;
            NPChar.Health.HP    = 60.0;
            NPChar.Health.maxHP = 60.0;
            NPChar.OfficerWantToGo.DontGo = true;
            NPChar.loyality = MAX_LOYALITY;
            NPChar.Payment = true;
            NPChar.DontClearDead = true; 
            SaveCurrentNpcQuestDateParam(NPChar, "HiredDate");
            AddPassenger(pchar, NPChar, false);
            SetCharacterRemovable(NPChar, true);
            LAi_SetActorTypeNoGroup(NPChar);
            LAi_ActorGoToLocation(NPChar, "reload", "reload1", "none", "", "", "", -1.0);
            PostEvent("LAi_event_boarding_EnableReload", 5000);
            DialogExit();
		break;

// МЕЙФЕНГ -->
        case "FireBrigade_hol":
			dialog.text = "You're not the one who was supposed to make it this far. Meifeng is the Company's fang. My squadron is the avenging blade. You broke both. That... doesn't happen.";
			link.l1 = "They sent you after me like I was a beast. And I fought—like a cornered animal. When it's fight or die, your mind gets clear. In the end, there's only one question left: Will I make it to the cabin of the legendary xebec—or not.";
			link.l1.go = "Longway_1";
		break;

		case "Longway_1":
			dialog.text = GetSexPhrase("", "Strange—to see a woman in command. That doesn't happen too. ") + "Were you expecting me?";
			link.l1 = "Yes. Meifeng is a ship with a history. When I crossed the Dutch, I knew sooner or later they'd send you after me. It would've been an honorable end... but look how things turned out.";
			link.l1.go = "Longway_2";
		break;

		case "Longway_2":
			dialog.text = "Knowing your enemy and yourself is the key to victory. So, you made your choice. To face my squadron on your own terms. You were ready to die. But you won. Now my life is in your hands. Why not finish me?";
			link.l1 = "(Leadership) Because I see no point in sinking a legendary captain just for the Company's ambitions. I've been in your place—a pawn. Serving others' interests, following others' orders. I'm offering you what I once chose myself: freedom.";
            if (GetSummonSkillFromName(PChar, SKILL_LEADERSHIP) >= 50)
                link.l1.go = "Longway_Success";
            else
                link.l1.go = "Longway_Failed";
            link.l2 = "Because every captain deserves the last word. En garde!";
			link.l2.go = "Longway_ExitFight";
		break;

		case "Longway_ExitFight":
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);
			QuestAboardCabinDialogExitWithBattle(""); 
            AddDialogExitQuest("MainHeroFightModeOn");
			DialogExit();
		break;

		case "Longway_Failed":
            notification("Skill Check Failed (50)", SKILL_LEADERSHIP);
			dialog.text = "Freedom isn't something given. It's something taken. And not everyone who talks about choice can offer it. There are roads you can't avoid. There are orders you can't leave unfinished. My road is here. My order is to stand to the end.";
			link.l1 = "So you choose death?";
			link.l1.go = "Longway_Failed_over";
		break;

		case "Longway_Failed_over":
			dialog.text = "No. I choose to remain myself.";
			link.l1 = "Then let's fight!";
			link.l1.go = "Longway_ExitFight";
		break;

		case "Longway_Success":
            notification("Skill Check Passed", SKILL_LEADERSHIP);
			dialog.text = "You're not like Rodenburg. He saw me as a tool. You—as an equal. Sacrificing yourself isn't a virtue. I'm ready to hear your terms.";
			link.l1 = "It's simple. Be my navigator on my flagship. Or, if you wish, you'll get your own ship and sail under my flag. You won't have to clean up after the Company or hide their skeletons in the closet anymore. I'm free—and I offer you that freedom with me.";
			link.l1.go = "Longway_Success_over";
		break;

		case "Longway_Success_over":
			dialog.text = "I've seen much: blood, gold, betrayal. The Company pays—but doesn't respect. Gives a ship—but keeps you chained. You... give a choice. If you keep your word—Longway will no longer be a hunter for someone else's will. He'll be a man. A captain. Or—stand beside a captain who knows where to sail.";
			link.l1 = "Welcome to the crew, Navigator Longway..";
			link.l1.go = "Longway_Hired";
		break;

		case "Longway_Hired":
            sld = GetCharacter(NPC_GenerateCharacter("Longway_FP", "Longway", "man", "Longway", 20, HOLLAND, -1, false, "quest"));
			sld.name = StringFromKey("QuestsUtilite_42");
			sld.lastname = StringFromKey("QuestsUtilite_43");
			sld.greeting = "Longway";
			sld.Dialog.Filename = "Quest\HollandGambit\Longway.c";
			sld.Dialog.currentnode = "Longway_officer";
			sld.rank = 20;
			sld.money = 5000;
			SetSelfSkill(sld, 45, 45, 45, 40, 50);
			SetShipSkill(sld, 50, 20, 25, 25, 65, 20, 20, 50, 15);
			SetSPECIAL(sld, 8, 9, 6, 5, 10, 7, 5);
			LAi_SetHP(sld, 250, 250);
			SetCharacterPerk(sld, "Energaiser");
			SetCharacterPerk(sld, "AdvancedDefense");
			SetCharacterPerk(sld, "ShipSpeedUp");
			SetCharacterPerk(sld, "ShipTurnRateUp");
			SetCharacterPerk(sld, "StormProfessional");
			SetCharacterPerk(sld, "WindCatcher");
			SetCharacterPerk(sld, "SailsMan");
			SetCharacterPerk(sld, "SailingProfessional");
            sTemp = GetGeneratedItem("blade_41");
            GiveItem2Character(sld, sTemp);
            EquipCharacterbyItem(sld, sTemp);
            sTemp = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
            if(sTemp != "")
            {
                GiveItem2Character(sld,   sTemp);
                EquipCharacterbyItem(sld, sTemp);
                sTemp = LAi_GetCharacterBulletType(NPChar, GUN_ITEM_TYPE);
                LAi_SetCharacterBulletType(sld, sTemp);
                LAi_SetCharacterUseBullet(sld, GUN_ITEM_TYPE, sTemp);
                sTemp = LAi_GetCharacterGunpowderType(NPChar, GUN_ITEM_TYPE);
                if(sTemp != "") AddItems(sld, sTemp, 30 + rand(20));
            }
			TakeNItems(sld, "potion2", 1);
            sld.quest.meeting = true;
			sld.quest.OfficerPrice = sti(pchar.rank)*200; // Артефакт
			sld.OfficerWantToGo.DontGo = true;
			sld.loyality = MAX_LOYALITY;
			sld.OfficerImmortal = true;
			sld.Health.HP    = 60.0;
			sld.Health.maxHP = 60.0;
            sld.CanTakeMushket = true;
			SetCharacterPerk(sld, "ShipEscape");
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, true);
			sld.Payment = true;
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);

            NPChar.lifeday = 0;
            LAi_group_MoveCharacter(NPChar, LAI_GROUP_PLAYER);
            LAi_SetActorType(NPChar);
            LAi_ActorGoToLocation(NPChar, "reload", "reload1", "none", "", "", "", -1);

            AddDialogExitQuest("pchar_back_to_player");
            PostEvent("LAi_event_boarding_EnableReload", 5000);
            DialogExit();
		break;
	}
}

// TO_DO
void AddBrigadierOfficer(ref sld, ref NPChar)
{
    string sTemp = NationShortName(NPChar.nation);
    sld = GetCharacter(NPC_GenerateCharacter("FraBrigadier", NPChar.model, "man", NPChar.model.animation, 30, FRANCE, -1, false, "quest"));
    float num = 1.0;
    switch (MOD_SKILL_ENEMY_RATE)
	{
		case  1: num = 0.5;  break;
		case  2: num = 0.6;  break;
		case  3: num = 0.7;  break;
		case  4: num = 0.8;  break;
		case  5: num = 0.9;  break;
		case  6: num = 1.0;  break;
		case  7: num = 1.1;  break;
		case  8: num = 1.2;  break;
		case  9: num = 1.3;  break;
		case 10: num = 1.5;  break;
	}
    num = stf(NPChar.Rank) / num;
    FantomMakeCoolFighter(sld, MakeInt(num+2), 70, 70, BLADE_LONG, "", "", 100);
    RemoveAllCharacterItems(sld, true);
    GiveItem2Character(sld, NPChar.equip.blade);
    EquipCharacterbyItem(sld, NPChar.equip.blade);
    sTemp = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
    if(sTemp != "")
    {
        GiveItem2Character(sld,   sTemp);
        EquipCharacterbyItem(sld, sTemp);
        sTemp = LAi_GetCharacterBulletType(NPChar, GUN_ITEM_TYPE);
        LAi_SetCharacterBulletType(sld, sTemp);
        LAi_SetCharacterUseBullet(sld, GUN_ITEM_TYPE, sTemp);
        sTemp = LAi_GetCharacterGunpowderType(NPChar, GUN_ITEM_TYPE);
        if(sTemp != "") AddItems(sld, sTemp, 30 + rand(20));
    }
    sld.name = NPChar.name;
    sld.lastname = NPChar.lastname;
    sld.greeting = "officer_hire";
    sld.Dialog.Filename = "Enc_Officer_dialog.c";
    sld.quest.meeting = true;
    sld.quest.OfficerPrice = sti(PChar.rank)*200; // Артефакт
    Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(sld.id);
    sld.OfficerImmortal = true;
    sld.Health.HP    = 60.0;
    sld.Health.maxHP = 60.0;
    sld.OfficerWantToGo.DontGo = true;
    sld.loyality = MAX_LOYALITY;
    AddDialogExitQuest("pchar_back_to_player");
    AddDialogExitQuestFunction("LandEnc_OfficerHired");
    NPChar.lifeday = 0;
    LAi_SetActorType(NPChar);
    LAi_ActorGoToLocation(NPChar, "reload", "reload1", "none", "", "", "", -1);
    PostEvent("LAi_event_boarding_EnableReload", 5000);
}
