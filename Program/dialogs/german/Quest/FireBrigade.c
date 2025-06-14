
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
			dialog.text = GetSexPhrase("", "Eine Frau... und Kapitän! Jetzt habe ich wirklich alles gesehen. Mademoiselle, Sie sind bezaubernd. Schade, dass Ihre Schönheit Frankreichs Krone so viel Leid gebracht hat\n") + "So enden alle Befehle von Poincy. Einer im Gefängnis. Der andere – schließt sich ihm an oder fällt heute im Kampf.";
			link.l1 = "Du bist hier völlig fehl am Platz. Warum schickt man so einen fähigen Offizier und so ein schönes Schiff, um die Drecksarbeit eines Kopfgeldjägers zu machen?";
			link.l1.go = "FraOff_1";
		break;

        case "FraOff_1":
			dialog.text = "Befehle werden nicht diskutiert, sie werden ausgeführt. Wenn jeder Kapitän selbst entscheiden würde, welche Befehle es wert sind – wir hätten keine Marine.";
			link.l1 = "Sag das deinen Männern.";
			link.l1.go = "FraOff_2";
        break;

        case "FraOff_2":
			dialog.text = "Du hast mich in die Enge getrieben und versuchst, meine Loyalität zur Krone zu brechen. Das ist ziemlich niedrig, angesichts der Umstände. Lass uns das mit Klingen klären, nicht mit Worten!";
			link.l1 = "(Charisma) Es gibt einen dritten Weg. Hör auf, Drecksarbeit zu machen, die eines Offiziers nicht würdig ist. Schließ dich mir an – ich zeige dir eine andere Welt.";
			link.l1.go = "FraOff_HireCheck";
            link.l2 = "Dann zu den Waffen!";
			link.l2.go = "FraOff_ExitFight";
        break;

        case "FraOff_HireCheck":
            if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 80)
            {
                notification("Fähigkeit nicht ausreichend entwickelt (80)", SKILL_LEADERSHIP);
                dialog.text = "Verräter werden überall gleich behandelt. Und ich werde keiner werden. Zieh dein Schwert!";
                link.l1 = "Du hattest deine Chance – und sie verpasst. Zieh dein Schwert!";
                link.l1.go = "FraOff_ExitFight";
                break;
            }
            notification("Prüfung bestanden", SKILL_LEADERSHIP);
            dialog.text = "Ich habe der Krone die Treue geschworen, nicht aufgeblasenen Bürokraten, die uns für ihre eigenen Probleme in den Tod schicken. Aber du bist ein Feind meines Königs, und das kann ich nicht ignorieren.";
			link.l1 = "Ich könnte meine Sünden gegen dein Land morgen schon sühnen – man muss nur den richtigen Mittelsmann bezahlen. Das sagt mehr über deine Vorgesetzten als über mich.";
			link.l1.go = "FraOff_Sucess";
        break;

        case "FraOff_Sucess":
			dialog.text = "Das stimmt. Und ich habe es satt, das alles zu ertragen. Ich bin bereit, unter deinem Kommando zu dienen, wenn du versprichst, die Franzosen in Ruhe zu lassen.";
			link.l1 = "Ich weiß nicht, wem wir begegnen werden, und ich kann nichts garantieren. Aber ich verspreche, vernünftig zu sein. Willkommen in der Crew, Offizier " + NPChar.name + "!"; // своего имени он вообще-то не называл
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
			dialog.text = "So sieht also der Feind der Menschheit aus. Bist du stolz auf diesen Titel, Pirat? Du hast hart dafür gearbeitet, ihn zu verdienen\nLaut der Casa de Contratación hast du " + (Statistic_AddValue(PChar, "spa_AbordShip", 0) + Statistic_AddValue(PChar, "spa_KillShip", 0)) + " Schiffe unter spanischer Flagge versenkt. Und heute wird mein schönes Schiff diese Liste ergänzen" + GetSexPhrase(".","\nWehe der spanischen Flotte! Wir haben Krankheiten, Vetternwirtschaft, Verrat ertragen... Aber von einer Frau besiegt zu werden?");
			link.l1 = "Du bist der Letzte, deine Mannschaft ist tot. Und du bist es auch, du hast es nur noch nicht begriffen.";
			link.l1.go = "Alonso_1";
			if(Statistic_AddValue(PChar, "spa_AbordShip", 0) + Statistic_AddValue(PChar, "spa_KillShip", 0) < 1)
			{
				Achievment_Set("ach_CL_159")
			}
		break;

		case "Alonso_1":
			dialog.text = "Schade, dass de Alba diesen Auftrag nicht bekommen hat. Er hätte es besser gemacht. Aber ich werde versuchen, die Arbeit zu beenden.";
			link.l1 = "Du bist ein wahrer Sohn deiner Heimat. Mach dich bereit, ihren Helden zu begegnen, Señor.";
			link.l1.go = "Alonso_2";
			link.l2 = "Der Jäger wurde zur Beute. All deine Reden waren umsonst – so alt wie die Welt.";
			link.l2.go = "Alonso_3";
		break;

		case "Alonso_2":
            ChangeCharacterComplexReputation(PChar, "nobility", 5);
			dialog.text = "Danke für die Verschnaufpause, aber jetzt spricht mein Degen.";
			link.l1 = "Zu den Waffen!";
			link.l1.go = "Alonso_ExitFight";
		break;

        case "Alonso_3":
            ChangeCharacterComplexReputation(PChar, "nobility", -5);
			dialog.text = "Danke für die Verschnaufpause, aber jetzt spricht mein Degen.";
			link.l1 = "Zu den Waffen!";
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
            dialog.text = GetSexPhrase(PChar.Name + "! Ihr Name taucht so oft in den Berichten auf, ich habe das Gefühl, wir kennen uns schon ewig", "Miss McArthur! Weiß Ihr Auftraggeber, was Sie hier treiben? Ach, egal. Ich bin sicher, er wird mein nächster Auftrag") + "\nSie haben Glück: Meine Chefs lieben es, dringende Befehle zu schicken, die den letzten widersprechen. Wenn ich nicht gerade damit beschäftigt wäre, die alte Crew von Antigua aufzuräumen... Aber egal. Genug. Sie lenken mich von der eigentlichen Arbeit ab.";
			link.l1 = "Sie lenken mich auch ab.";
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
            dialog.text = "Kettenkugel achtern, ich hätte es fast verpasst! Wären meine alten Knochen etwas schneller, hätte ich diesen Bastard eigenhändig zum Teufel geschickt. Danke, Käpt’n. Und auch von meinem verstorbenen Patron – danke!";
			link.l1 = "Wer sind Sie? Ein Gefangener? Hat meine Crew Sie befreit?";
			link.l1.go = "Kneepel_1";	
		break;

        case "Kneepel_1":
            dialog.text = "Charlie Knippel persönlich. Der beste Kanonier der englischen Marine!";
			link.l1 = "Courtney meinte, er habe lange gebraucht, Sie zu finden. Was ist passiert?";
			link.l1.go = "Kneepel_2";	
		break;

        case "Kneepel_2":
            dialog.text = "Viele Jahre diente ich einem tapferen englischen Kapitän namens Richard Fleetwood. Wir haben viele Schlachten zusammen geschlagen, aus echter Leidenschaft für die englische Marine. Doch eines Tages änderte sich alles\nDie Londoner Obrigkeit hat uns als Schachfiguren benutzt. Wir griffen unsere eigenen Leute an. Wir haben unsere Uniformen beschmutzt, um die Fehler anderer auszubügeln. Und jetzt sind wir dran...";
			link.l1 = "Kein Urteil von mir. Das Leben ist kompliziert, besonders wenn man nicht sein eigener Herr ist.";
			link.l1.go = "Kneepel_2_good";
            link.l2 = "Würden Sie sagen, die Schatten alter Sünden haben Sie eingeholt?";
			link.l2.go = "Kneepel_2_bad";
		break;

        case "Kneepel_2_good":
            dialog.text = "Ich bereue es nicht, meinem Land gedient zu haben. Es tut nur weh, Käpt’n. Besonders für meinen Patron und seine arme Frau.";
			link.l1 = "Что теперь?";
			link.l1.go = "Kneepel_3";	
		break;

        case "Kneepel_2_bad":
            TEV.NoKneepel = "";
            dialog.text = "Sparen Sie sich die Sticheleien... Wir haben für unsere Sünden schon bezahlt!";
			link.l1 = "Und jetzt?";
			link.l1.go = "Kneepel_3";	
		break;

        case "Kneepel_3":
            dialog.text = "Jetzt bin ich ein Mann ohne Namen und ohne Heimat. Ich könnte überall hingehen, aber im Moment gibt es keinen Ort. Und niemanden. Kanoniere werden überall gebraucht, aber nicht jedes Schiff hat Kanonen.";
			link.l1 = "Kommen Sie zu mir. Ich kann nicht behaupten, dass ich die beste Beziehung zur englischen Marine habe, aber ich respektiere ihre Besten.";
            if(!CheckAttribute(&TEV, "NoKneepel"))
                link.l1.go = "Kneepel_3_good";
            else
                link.l1.go = "Kneepel_3_bad";
            link.l2 = "Ich habe Kanonen. Wenn Sie wirklich so gut sind, findet sich in meiner Crew immer ein Platz für einen echten Profi.";
			link.l2.go = "Kneepel_3_bad";
		break;

        case "Kneepel_3_good":
            dialog.text = "Zu Hause wartet der Strick auf mich, bei den Spaniern und Holländern auch, und die Franzosen mag ich nicht. Aber Sie brauchen offenbar einen guten Kanonier. Ich bin dabei, Käpt’n. Ich gehe bei Gelegenheit in die Kajüte. Kommen Sie mal vorbei, dann stoßen wir mit Kettenkugeln an.";
			link.l1 = "Willkommen an Bord.";
			link.l1.go = "Kneepel_Hired";	
		break;

        case "Kneepel_3_bad":
            dialog.text = "Nein, danke. Ich schnappe mir lieber ein Boot und verschwinde im tiefsten Loch des Archipels. Danke für die Rettung, Käpt’n, und leb wohl.";
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
			dialog.text = "Du bist nicht derjenige, der es hierher schaffen sollte. Meifeng ist der Fang der Kompanie. Mein Geschwader ist die strafende Klinge. Du hast sie gebrochen. Allein. Das passiert nicht oft.";
			link.l1 = "Sie haben mich wie ein Tier gejagt. Und ich habe gekämpft – wie ein in die Enge getriebenes Tier. Wenn es ums Überleben geht, wird der Kopf klar. Am Ende bleibt nur eine Frage: Schaffe ich es bis zur Kabine der legendären Xebeke – oder nicht.";
			link.l1.go = "Longway_1";
		break;

		case "Longway_1":
			dialog.text = GetSexPhrase("", "Seltsam – eine Frau in so einem Kampf zu sehen. Im Reich der Mitte führen Frauen keine Flotten. Aber du bist nicht schlechter. Vielleicht sogar furchteinflößender\n") + "Wusstest du, wer das Kommando hat? Hast du auf mich gewartet?";
			link.l1 = "Ja. Meifeng ist ein Schiff mit Geschichte. Als ich den Holländern in die Quere kam, wusste ich: Früher oder später schicken sie dich. Es wäre ein ehrenvolles Ende gewesen... aber schau, wie es gekommen ist.";
			link.l1.go = "Longway_2";
		break;

		case "Longway_2":
			dialog.text = "Den Feind und sich selbst zu kennen, ist der Schlüssel zum Sieg. Du hast deine Wahl getroffen. Du hast mein Geschwader zu deinen Bedingungen gestellt. Du warst bereit zu sterben. Aber du hast gewonnen. Jetzt liegt mein Leben in deinen Händen. Warum bringst du es nicht zu Ende?";
			link.l1 = "(Charisma) Weil ich keinen Sinn darin sehe, einen legendären Kapitän nur wegen der Kompanie zu versenken. Ich war selbst mal eine Spielfigur. Habe fremden Interessen gedient, fremde Befehle ausgeführt. Ich biete dir das an, was ich selbst einmal gewählt habe: Freiheit.";
            if (GetSummonSkillFromName(PChar, SKILL_LEADERSHIP) >= 50)
                link.l1.go = "Longway_Success";
            else
                link.l1.go = "Longway_Failed";
            link.l2 = "Weil jeder Kapitän das letzte Wort verdient. Zieh dein Schwert!";
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
            notification("Fähigkeit nicht ausreichend entwickelt (50)", SKILL_LEADERSHIP);
			dialog.text = "Freiheit ist nichts, was man bekommt. Sie ist etwas, das man sich nimmt. Und nicht jeder, der von Wahl spricht, kann sie auch bieten. Es gibt Wege, die man gehen muss. Es gibt Befehle, die man nicht unerledigt lassen kann. Mein Weg ist hier. Mein Befehl ist, bis zum Ende zu stehen.";
			link.l1 = "Also wählst du den Tod?";
			link.l1.go = "Longway_Failed_over";
		break;

		case "Longway_Failed_over":
			dialog.text = "Nein. Ich wähle, ich selbst zu bleiben.";
			link.l1 = "Zieh dein Schwert!";
			link.l1.go = "Longway_ExitFight";
		break;

		case "Longway_Success":
            notification("Prüfung bestanden", SKILL_LEADERSHIP);
			dialog.text = "Du bist nicht wie Rodenburg. Für ihn war ich nur ein Werkzeug. Für dich bin ich ein Ebenbürtiger. Sich selbst zu opfern ist keine Tugend. Ich bin bereit, deine Bedingungen zu hören.";
			link.l1 = "Ganz einfach. Sei mein Steuermann auf meinem Flaggschiff. Oder, wenn du willst, bekommst du dein eigenes Schiff und segelst unter meiner Flagge. Du musst nicht mehr die Drecksarbeit der Kompanie machen oder ihre Leichen im Schrank verstecken. Ich bin frei – und biete dir an, diese Freiheit mit mir zu teilen.";
			link.l1.go = "Longway_Success_over";
		break;

		case "Longway_Success_over":
			dialog.text = "Ich habe viel gesehen: Blut, Gold, Verrat. Die Kompanie zahlt – aber sie respektiert nicht. Sie gibt dir ein Schiff – aber hält dich an der Kette. Du... gibst eine Wahl. Wenn du dein Wort hältst – wird Longwei nicht länger ein Jäger im Auftrag anderer sein. Er wird ein Mensch sein. Ein Kapitän. Oder – an der Seite eines Kapitäns, der weiß, wohin er segeln will.";
			link.l1 = "Willkommen in der Crew, Steuermann Longwei.";
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
