
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
			dialog.text = GetSexPhrase("", "Kobieta... i kapitan! Teraz widziałem już wszystko. Mademoiselle, jest pani zachwycająca. Szkoda, że pani uroda przyniosła tyle nieszczęścia Koronie Francji\n") + "Tak kończą się wszystkie rozkazy Poincy’ego. Jeden w więzieniu. Drugi—albo do niego dołączy, albo dziś zginie w walce.";
			link.l1 = "Wyraźnie nie pasujesz do tego miejsca. Po co wysyłać takiego oficera i taki piękny okręt do brudnej roboty łowcy głów?";
			link.l1.go = "FraOff_1";
		break;

        case "FraOff_1":
			dialog.text = "Rozkazy się nie dyskutuje, tylko wykonuje. Gdyby każdy kapitan wybierał, które rozkazy są warte—nie mielibyśmy floty.";
			link.l1 = "Powiedz to swoim ludziom.";
			link.l1.go = "FraOff_2";
        break;

        case "FraOff_2":
			dialog.text = "Zapędziłeś mnie w kozi róg i próbujesz złamać moją lojalność i przysięgę. To niskie, biorąc pod uwagę okoliczności. Zakończmy to starciem szabel, nie słowami!";
			link.l1 = "(Dowodzenie) Jest jeszcze trzecia droga. Przestań robić brudną robotę, niegodną oficera. Dołącz do mnie—pokażę ci inny świat.";
			link.l1.go = "FraOff_HireCheck";
            link.l2 = "No to do broni!";
			link.l2.go = "FraOff_ExitFight";
        break;

        case "FraOff_HireCheck":
            if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 80)
            {
                notification("Za mało rozwinięta umiejętność (80)", SKILL_LEADERSHIP);
                dialog.text = "Zdrajców wszędzie traktuje się tak samo. I ja nim nie będę.";
                link.l1 = "Miałeś swoją szansę i ją zmarnowałeś. Do broni!";
                link.l1.go = "FraOff_ExitFight";
                break;
            }
            notification("Test zaliczony", SKILL_LEADERSHIP);
            dialog.text = "Przysięgałem wierność koronie, a nie nadętym biurokratom, którzy wysyłają nas na śmierć, by ukryć własne błędy. Ale ty—jesteś wrogiem mojego króla i nie mogę tego zignorować.";
			link.l1 = "Mógłbym odkupić swoje winy wobec twojego kraju choćby jutro—wystarczy zapłacić odpowiedniemu pośrednikowi. To więcej mówi o twoich przełożonych niż o mnie.";
			link.l1.go = "FraOff_Sucess";
        break;

        case "FraOff_Sucess":
			dialog.text = "To prawda. I mam już dość tego wszystkiego. Jestem gotów służyć pod twoim dowództwem, jeśli obiecasz zostawić Francuzów w spokoju.";
			link.l1 = "Nie wiem, kogo spotkamy na drodze, i niczego nie mogę obiecać. Ale obiecuję być rozsądny. Witaj na pokładzie, oficerze " + NPChar.name + "!"; // своего имени он вообще-то не называл
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
			dialog.text = "A więc tak wygląda wróg publiczny. Mam nadzieję, że jesteś dumny z tego tytułu, piracie. Musiałeś się nieźle napracować, żeby na niego zasłużyć\nWedług Casa de Contratación masz na koncie " + (Statistic_AddValue(PChar, "spa_AbordShip", 0) + Statistic_AddValue(PChar, "spa_KillShip", 0)) + " statków pod banderą hiszpańskiej Korony. I dziś mój piękny okręt dołączy do tej listy" + GetSexPhrase(".","\nBiada hiszpańskiej flocie! Przetrwaliśmy choroby, kumoterstwo, zdradę... Ale żeby pokonała nas kobieta?");
			link.l1 = "Zostałeś sam, twoja załoga nie żyje. Ty też już nie żyjesz, tylko jeszcze o tym nie wiesz.";
			link.l1.go = "Alonso_1";
			if(Statistic_AddValue(PChar, "spa_AbordShip", 0) + Statistic_AddValue(PChar, "spa_KillShip", 0) < 1)
			{
				Achievment_Set("ach_CL_159")
			}
		break;

		case "Alonso_1":
			dialog.text = "Szkoda, że to nie de Alba dostał to zadanie. Poradziłby sobie lepiej. Ale spróbuję dokończyć robotę.";
			link.l1 = "Jesteś prawdziwym synem swojej ojczyzny. Przygotuj się na spotkanie z jej bohaterami, señor.";
			link.l1.go = "Alonso_2";
			link.l2 = "Myśliwy stał się zwierzyną. Wszystkie twoje przemowy na nic—stare jak świat.";
			link.l2.go = "Alonso_3";
		break;

		case "Alonso_2":
            ChangeCharacterComplexReputation(PChar, "nobility", 5);
			dialog.text = "Dzięki za tę przerwę, ale teraz przemówi moja szpada.";
			link.l1 = "Do broni!";
			link.l1.go = "Alonso_ExitFight";
		break;

        case "Alonso_3":
            ChangeCharacterComplexReputation(PChar, "nobility", -5);
			dialog.text = "Dzięki za tę przerwę, ale teraz przemówi moja szpada.";
			link.l1 = "Przygotuj się na śmierć!";
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
            dialog.text = GetSexPhrase(PChar.Name + "! Twoje imię pojawia się w raportach tak często, że mam wrażenie, jakbyśmy znali się od lat", "Panno McArthur! Czy pani patron wie, czym się pani zajmuje? Ach, nieważne. Jestem pewien, że będzie moim następnym zleceniem") + "\nMasz szczęście: moi szefowie uwielbiają wydawać pilne rozkazy, które przeczą poprzednim. Gdybym nie był zajęty sprzątaniem starej ekipy z Antigui... No, dość. Odciągasz mnie od prawdziwej roboty.";
			link.l1 = "Ty też mnie rozpraszasz.";
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
            dialog.text = "Kula łańcuchowa na rufie, prawie to przegapiłem! Gdyby moje stare kości były trochę szybsze, sam posłałbym tego drania do diabła. Dzięki, kapitanie. I od mojego zmarłego patrona też dziękuję!";
			link.l1 = "Kim jesteś? Więzień? To moja załoga cię uwolniła?";
			link.l1.go = "Kneepel_1";	
		break;

        case "Kneepel_1":
            dialog.text = "Charlie Knippel we własnej osobie. Najlepszy artylerzysta w angielskiej marynarce!";
			link.l1 = "Courtney mówił, że długo cię szukał. O co chodziło?";
			link.l1.go = "Kneepel_2";	
		break;

        case "Kneepel_2":
            dialog.text = "Przez wiele lat służyłem dzielnemu angielskiemu kapitanowi Richardowi Fleetwoodowi. Stoczyliśmy razem wiele bitew, z prawdziwej pasji do angielskiej floty. Ale pewnego dnia wszystko się zmieniło\nLondyńscy przełożeni potraktowali nas jak pionki. Zaatakowaliśmy swoich. Pobrudziliśmy mundury, sprzątając po innych. Teraz przyszła nasza kolej...";
			link.l1 = "Nie oceniam. Życie jest skomplikowane, zwłaszcza gdy nie jest się panem własnego losu..";
			link.l1.go = "Kneepel_2_good";
            link.l2 = "Można powiedzieć, że dopadły cię cienie dawnych grzechów?";
			link.l2.go = "Kneepel_2_bad";
		break;

        case "Kneepel_2_good":
            dialog.text = "Nie żałuję, że służyłem ojczyźnie. Po prostu... to boli, kapitanie. Zwłaszcza ze względu na patrona i jego biedną żonę.";
			link.l1 = "I co teraz?";
			link.l1.go = "Kneepel_3";	
		break;

        case "Kneepel_2_bad":
            TEV.NoKneepel = "";
            dialog.text = "Daruj sobie docinki... Za swoje grzechy już zapłaciliśmy!";
			link.l1 = "I co teraz?";
			link.l1.go = "Kneepel_3";	
		break;

        case "Kneepel_3":
            dialog.text = "Teraz jestem człowiekiem bez imienia i ojczyzny. Mógłbym pójść gdziekolwiek, ale na razie nie mam dokąd. I z kim. Artylerzyści są potrzebni wszędzie, ale nie każdy okręt ma działa.";
			link.l1 = "Dołącz do mnie. Nie powiem, że mam najlepsze relacje z angielską flotą, ale szanuję jej najlepszych ludzi.";
            if(!CheckAttribute(&TEV, "NoKneepel"))
                link.l1.go = "Kneepel_3_good";
            else
                link.l1.go = "Kneepel_3_bad";
            link.l2 = "Mam działa. Jeśli naprawdę jesteś taki dobry, zawsze znajdzie się miejsce dla prawdziwego fachowca w mojej załodze.";
			link.l2.go = "Kneepel_3_bad";
		break;

        case "Kneepel_3_good":
            dialog.text = "W domu czeka na mnie stryczek, u Hiszpanów i Holendrów też, a Francuzów nie lubię. Ale tobie, jak widać, brakuje dobrego artylerzysty. Wchodzę, kapitanie. Przy najbliższej okazji pójdę do kajuty. Wpadnij kiedyś, pogadamy przy kulach łańcuchowych.";
			link.l1 = "Witamy na pokładzie.";
			link.l1.go = "Kneepel_Hired";	
		break;

        case "Kneepel_3_bad":
            dialog.text = "Nie, dzięki. Wolę zarekwirować szalupę i zniknąć w najgłębszym zakątku archipelagu. Dzięki za ratunek, kapitanie, i żegnaj.";
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
			dialog.text = "Nie jesteś tym, kto miał tu dotrzeć. Meifeng to kieł Kompanii. Mój szwadron to karzące ostrze. Pokonałeś ich. Sam. To... rzadko się zdarza.";
			link.l1 = "Wysłali cię za mną jak za zwierzem. Walczyłem—jak osaczony zwierz. Gdy trzeba walczyć albo zginąć, myśli się prościej. Na końcu zostaje tylko jedno pytanie: Czy dotrę do kajuty legendarnej szebeki—czy nie..";
			link.l1.go = "Longway_1";
		break;

		case "Longway_1":
			dialog.text = GetSexPhrase("", "Dziwnie—widzieć kobietę w takiej walce. W Państwie Środka kobiety nie dowodzą flotą. Ale ty nie jesteś gorsza. Może nawet bardziej budzisz respekt\n") + "Wiedziałaś, kto dowodzi? Czekałaś na mnie?";
			link.l1 = "Tak. Meifeng to statek z historią. Gdy podpadłem Holendrom, wiedziałem, że prędzej czy później wyślą cię po moją głowę. To byłby zaszczytny koniec... ale zobacz, jak się wszystko potoczyło.";
			link.l1.go = "Longway_2";
		break;

		case "Longway_2":
			dialog.text = "Poznanie wroga i siebie to klucz do zwycięstwa. Podjęłaś decyzję. Stanęłaś naprzeciw mojego szwadronu na własnych warunkach. Byłaś gotowa umrzeć. Ale wygrałaś. Teraz moje życie jest w twoich rękach. Dlaczego nie kończysz?";
			link.l1 = "(Dowodzenie) Bo nie widzę sensu w zatapianiu legendarnego kapitana tylko dla ambicji Kompanii. Byłem na twoim miejscu—pionkiem. Służyłem cudzym interesom, wykonywałem cudze rozkazy. Proponuję ci to, co sam kiedyś wybrałem: wolność.";
            if (GetSummonSkillFromName(PChar, SKILL_LEADERSHIP) >= 50)
                link.l1.go = "Longway_Success";
            else
                link.l1.go = "Longway_Failed";
            link.l2 = "Bo każdy kapitan zasługuje na ostatnie słowo. Do broni!";
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
            notification("Za mało rozwinięta umiejętność (50)", SKILL_LEADERSHIP);
			dialog.text = "Wolność to nie coś, co się dostaje. To coś, co się bierze. I nie każdy, kto mówi o wyborze, potrafi go dać. Są drogi, których nie da się ominąć. Są rozkazy, których nie można zostawić niewykonanych. Moja droga jest tutaj. Mój rozkaz—to wytrwać do końca.";
			link.l1 = "Więc wybierasz śmierć?";
			link.l1.go = "Longway_Failed_over";
		break;

		case "Longway_Failed_over":
			dialog.text = "Nie. Wybieram pozostać sobą.";
			link.l1 = "Do broni!";
			link.l1.go = "Longway_ExitFight";
		break;

		case "Longway_Success":
            notification("Test zaliczony", SKILL_LEADERSHIP);
			dialog.text = "Nie jesteś jak Rodenburg. On widział we mnie narzędzie. Ty—równego sobie. Poświęcenie nie jest cnotą. Jestem gotów wysłuchać twoich warunków.";
			link.l1 = "To proste. Bądź moim nawigatorem na moim okręcie flagowym. Albo, jeśli wolisz, dostaniesz własny statek i popłyniesz pod moją banderą. Nie będziesz już musiał sprzątać po Kompanii ani ukrywać ich szkieletów w szafie. Jestem wolny—a tobie proponuję tę wolność razem ze mną.";
			link.l1.go = "Longway_Success_over";
		break;

		case "Longway_Success_over":
			dialog.text = "Wiele widziałem: krew, złoto, zdradę. Kompania płaci—ale nie szanuje. Daje statek—ale trzyma na łańcuchu. Ty... dajesz wybór. Jeśli dotrzymasz słowa—Longwei nie będzie już łowcą na cudze zlecenie. Będzie człowiekiem. Kapitanem. Albo—obok kapitana, który wie, dokąd płynąć.";
			link.l1 = "Witaj w załodze, nawigatorze Longwei.";
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
