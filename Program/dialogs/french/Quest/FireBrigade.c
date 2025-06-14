
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
			dialog.text = GetSexPhrase("", "Une femme... et capitaine ! J’ai tout vu maintenant. Mademoiselle, vous êtes ravissante. Dommage que votre beauté ait causé tant de malheur à la Couronne de France\n") + "Voilà comment finissent tous les ordres de Poincy. L’un en prison. L’autre—soit il le rejoint, soit il tombe aujourd’hui au combat.";
			link.l1 = "Tu n’as rien à faire ici. Pourquoi envoyer un officier aussi brillant et un si beau navire pour faire le sale boulot d’un chasseur de primes ?";
			link.l1.go = "FraOff_1";
		break;

        case "FraOff_1":
			dialog.text = "Les ordres ne se discutent pas, ils s’exécutent. Si chaque capitaine choisissait les ordres qui valent la peine—on n’aurait plus de marine.";
			link.l1 = "Dis ça à tes hommes.";
			link.l1.go = "FraOff_2";
        break;

        case "FraOff_2":
			dialog.text = "Tu m’as acculé et tu essaies de briser ma loyauté et mon serment. C’est bas, vu les circonstances. Finissons-en à l’épée, pas avec des mots !";
			link.l1 = "(Charisme) Il y a une troisième voie. Arrête de faire le sale boulot indigne d’un officier. Rejoins-moi—je te montrerai un autre monde.";
			link.l1.go = "FraOff_HireCheck";
            link.l2 = "Alors, aux armes !";
			link.l2.go = "FraOff_ExitFight";
        break;

        case "FraOff_HireCheck":
            if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 80)
            {
                notification("Compétence insuffisante (80)", SKILL_LEADERSHIP);
                dialog.text = "Les traîtres sont traités de la même façon partout. Et je n’en serai pas un. En garde !";
                link.l1 = "Tu as eu ta chance, et tu l’as ratée. En garde !";
                link.l1.go = "FraOff_ExitFight";
                break;
            }
            notification("Vérification réussie", SKILL_LEADERSHIP);
            dialog.text = "J’ai juré fidélité à la couronne, pas à des bureaucrates prétentieux qui nous envoient mourir pour couvrir leurs propres erreurs. Mais toi—tu es l’ennemi de mon roi, et je ne peux pas l’ignorer.";
			link.l1 = "Je pourrais racheter mes fautes envers ton pays dès demain—il suffit de payer le bon intermédiaire. Ça en dit plus sur tes supérieurs que sur moi.";
			link.l1.go = "FraOff_Sucess";
        break;

        case "FraOff_Sucess":
			dialog.text = "C’est vrai. Et j’en ai assez de supporter tout ça. Je suis prêt à servir sous tes ordres, si tu promets de laisser les Français tranquilles.";
			link.l1 = "Je ne sais pas qui nous croiserons, et je ne peux rien promettre. Mais je promets d’être raisonnable. Bienvenue dans l’équipage, officier " + NPChar.name + "!"; // своего имени он вообще-то не называл
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
			dialog.text = "Voilà donc à quoi ressemble l’ennemi public. J’espère que tu es fier de ce titre, pirate. Tu l’as bien mérité\nD’après la Casa de Contratación, tu as coulé " + (Statistic_AddValue(PChar, "spa_AbordShip", 0) + Statistic_AddValue(PChar, "spa_KillShip", 0)) + " navires sous pavillon espagnol. Et aujourd’hui, mon beau navire rejoindra cette liste" + GetSexPhrase(".","\nMalheur à la flotte espagnole ! Nous avons enduré maladies, favoritisme, trahisons... Mais être vaincus par une femme ?");
			link.l1 = "Tu es le dernier debout, ton équipage est mort. Et toi aussi, tu ne le sais juste pas encore.";
			link.l1.go = "Alonso_1";
			if(Statistic_AddValue(PChar, "spa_AbordShip", 0) + Statistic_AddValue(PChar, "spa_KillShip", 0) < 1)
			{
				Achievment_Set("ach_CL_159")
			}
		break;

		case "Alonso_1":
			dialog.text = "Dommage que ce ne soit pas de Alba qui ait eu cette mission. Il s’en serait mieux sorti. Mais je vais essayer de finir le travail.";
			link.l1 = "Tu es un vrai fils de ta patrie. Prépare-toi à rencontrer ses héros, señor.";
			link.l1.go = "Alonso_2";
			link.l2 = "Le chasseur est devenu la proie. Tous tes discours n’ont servi à rien—c’est aussi vieux que le monde.";
			link.l2.go = "Alonso_3";
		break;

		case "Alonso_2":
            ChangeCharacterComplexReputation(PChar, "nobility", 5);
			dialog.text = "Merci pour ce répit, mais maintenant c’est mon épée qui va parler.";
			link.l1 = "Aux armes !";
			link.l1.go = "Alonso_ExitFight";
		break;

        case "Alonso_3":
            ChangeCharacterComplexReputation(PChar, "nobility", -5);
			dialog.text = "Merci pour ce répit, mais maintenant c’est mon épée qui va parler.";
			link.l1 = "Prépare-toi à mourir !";
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
            dialog.text = GetSexPhrase(PChar.Name + " ! Ton nom revient si souvent dans les rapports que j’ai l’impression qu’on se connaît depuis toujours", "Mademoiselle McArthur ! Votre patron sait-il ce que vous faites ? Bah, peu importe. Je suis sûr qu’il sera mon prochain contrat") + "\nTu as de la chance : mes chefs adorent envoyer des ordres urgents qui contredisent les précédents. Si je n’étais pas occupé à nettoyer l’ancienne équipe d’Antigua... Enfin, bref. Tu me distrais de mon vrai travail.";
			link.l1 = "Toi aussi, tu me distrais.";
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
            dialog.text = "Boulet ramé à l’arrière, j’ai failli rater ça ! Si mes vieux os étaient un peu plus vifs, j’aurais envoyé ce salaud chez le diable moi-même. Merci, capitaine. Et merci aussi de la part de mon défunt patron.";
			link.l1 = "Qui es-tu ? Un prisonnier ? C’est mon équipage qui t’a libéré ?";
			link.l1.go = "Kneepel_1";	
		break;

        case "Kneepel_1":
            dialog.text = "Charlie Knippel en personne. Le meilleur canonnier de la marine anglaise !";
			link.l1 = "Courtney a dit qu’il a mis longtemps à te retrouver. Qu’est-ce qui s’est passé ?";
			link.l1.go = "Kneepel_2";	
		break;

        case "Kneepel_2":
            dialog.text = "Pendant de nombreuses années, j’ai servi un brave capitaine anglais nommé Richard Fleetwood. On a mené beaucoup de batailles ensemble, par vraie passion pour la marine anglaise. Mais un jour, tout a changé\nLes chefs de Londres nous ont utilisés comme des pions. On a attaqué les nôtres. On a sali nos uniformes en nettoyant les erreurs des autres. Et maintenant, c’est notre tour...";
			link.l1 = "Je ne juge pas. La vie est compliquée, surtout quand on n’est pas maître de son destin.";
			link.l1.go = "Kneepel_2_good";
            link.l2 = "Tu dirais que les ombres des vieux péchés t’ont finalement rattrapé ?";
			link.l2.go = "Kneepel_2_bad";
		break;

        case "Kneepel_2_good":
            dialog.text = "Je ne regrette pas d’avoir servi mon pays. C’est juste... ça fait mal, capitaine. Surtout pour mon patron et sa pauvre femme.";
			link.l1 = "Et maintenant ?";
			link.l1.go = "Kneepel_3";	
		break;

        case "Kneepel_2_bad":
            TEV.NoKneepel = "";
            dialog.text = "Pas la peine de me piquer... On a déjà payé le prix fort pour nos fautes.";
			link.l1 = "Et maintenant ?";
			link.l1.go = "Kneepel_3";	
		break;

        case "Kneepel_3":
            dialog.text = "Maintenant je suis un homme sans nom ni patrie. Je pourrais aller n’importe où, mais pour l’instant il n’y a nulle part où aller. Et personne avec qui aller. On a besoin de canonniers partout, mais tous les navires n’ont pas de canons.";
			link.l1 = "Viens avec moi. Je ne peux pas dire que j’ai eu la meilleure relation avec la marine anglaise, mais j’en respecte les meilleurs.";
            if(!CheckAttribute(&TEV, "NoKneepel"))
                link.l1.go = "Kneepel_3_good";
            else
                link.l1.go = "Kneepel_3_bad";
            link.l2 = "J’ai des canons. Si tu es vraiment aussi bon, il y aura toujours une place pour un vrai pro dans mon équipage.";
			link.l2.go = "Kneepel_3_bad";
		break;

        case "Kneepel_3_good":
            dialog.text = "La potence m’attend chez moi, pareil chez les Espagnols et les Hollandais, et les Français ne me plaisent pas. Mais toi, on dirait que tu as besoin d’un bon canonnier. J’en suis, capitaine. J’irai à la cabine dès que possible. Passe me voir un de ces jours, on trinquera au boulet ramé.";
			link.l1 = "Bienvenue à bord.";
			link.l1.go = "Kneepel_Hired";	
		break;

        case "Kneepel_3_bad":
            dialog.text = "Non, merci. Je préfère réquisitionner une chaloupe et disparaître dans le trou le plus profond de l’archipel. Merci de m’avoir sauvé, capitaine, et adieu.";
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
            npchar.quest.meeting = true;
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
			dialog.text = "Tu n’es pas celui qui devait arriver ici. Meifeng est le croc de la Compagnie. Mon escadron est la lame qui punit. Tu les as brisés. Seul. Ça... n’arrive pas souvent.";
			link.l1 = "Ils t’ont envoyé après moi comme si j’étais une bête. Et j’ai combattu—comme une bête acculée. Quand il faut se battre ou mourir, l’esprit devient clair. Au final, il ne reste qu’une question : Est-ce que j’atteindrai la cabine de la légendaire xebec—ou pas.";
			link.l1.go = "Longway_1";
		break;

		case "Longway_1":
			dialog.text = GetSexPhrase("", "Étrange—de voir une femme dans un tel combat. Dans l’Empire du Milieu, les femmes ne commandent pas de flottes. Mais tu n’es pas moins capable. Peut-être même plus redoutable.\n") + "Tu savais qui commandait ? Tu m’attendais ?";
			link.l1 = "Oui. Meifeng est un navire chargé d’histoire. Quand j’ai croisé la route des Hollandais, je savais qu’un jour ou l’autre ils t’enverraient après moi. Ça aurait été une fin honorable... mais regarde comment ça s’est terminé.";
			link.l1.go = "Longway_2";
		break;

		case "Longway_2":
			dialog.text = "Connaître son ennemi et soi-même, c’est la clé de la victoire. Tu as fait ton choix. Tu as affronté mon escadron à tes conditions. Tu étais prêt à mourir. Mais tu as gagné. Maintenant, ma vie est entre tes mains. Pourquoi ne pas en finir ?";
			link.l1 = "(Charisme) Parce que je ne vois pas l’intérêt de couler un capitaine légendaire juste pour les ambitions de la Compagnie. J’ai été à ta place—un pion. J’ai servi les intérêts des autres, obéi aux ordres des autres. Je t’offre ce que j’ai moi-même choisi un jour : la liberté.";
            if (GetSummonSkillFromName(PChar, SKILL_LEADERSHIP) >= 50)
                link.l1.go = "Longway_Success";
            else
                link.l1.go = "Longway_Failed";
            link.l2 = "Parce que chaque capitaine mérite le dernier mot. En garde !";
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
            notification("Compétence insuffisante (50)", SKILL_LEADERSHIP);
			dialog.text = "La liberté n’est pas quelque chose qu’on donne. C’est quelque chose qu’on prend. Et tous ceux qui parlent de choix ne peuvent pas l’offrir. Il y a des chemins qu’on ne peut pas éviter. Il y a des ordres qu’on ne peut pas laisser inachevés. Mon chemin est ici. Mon ordre est de tenir jusqu’au bout.";
			link.l1 = "Alors tu choisis la mort ?";
			link.l1.go = "Longway_Failed_over";
		break;

		case "Longway_Failed_over":
			dialog.text = "Non. Je choisis de rester moi-même.";
			link.l1 = "En garde !";
			link.l1.go = "Longway_ExitFight";
		break;

		case "Longway_Success":
            notification("Vérification réussie", SKILL_LEADERSHIP);
			dialog.text = "Tu n’es pas comme Rodenburg. Pour lui, je n’étais qu’un outil. Pour toi, je suis un égal. Se sacrifier n’est pas une vertu. Je suis prêt à entendre tes conditions.";
			link.l1 = "C’est simple. Sois mon navigateur sur mon vaisseau amiral. Ou, si tu préfères, tu auras ton propre navire et tu navigueras sous mon pavillon. Tu n’auras plus à nettoyer les sales affaires de la Compagnie ni à cacher leurs squelettes dans le placard. Je suis libre—et je t’offre de partager cette liberté avec moi.";
			link.l1.go = "Longway_Success_over";
		break;

		case "Longway_Success_over":
			dialog.text = "J’en ai vu beaucoup : du sang, de l’or, des trahisons. La Compagnie paie—mais ne respecte pas. Elle te donne un navire—mais te garde enchaîné. Toi... tu donnes un choix. Si tu tiens parole—Longwei ne sera plus un chasseur aux ordres des autres. Il sera un homme. Un capitaine. Ou—aux côtés d’un capitaine qui sait où aller.";
			link.l1 = "Bienvenue dans l’équipage, navigateur Longwei.";
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
