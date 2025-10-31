
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
			dialog.text = GetSexPhrase("", "Egy nô... és egy kapitány! Most már mindent láttam. Mademoiselle, ön lenyûgözô. Kár, hogy a szépsége ennyi bánatot hozott a francia koronának\n") + "Így végzôdik Poincy minden parancsa. Az egyik a börtönben. A másik - vagy csatlakozik hozzá, vagy ma elesik a csatában.";
			link.l1 = "Egyértelmûen nem vagy itt a helyeden. Miért küldenél egy ilyen okos tisztet és egy ilyen szép hajót egy fejvadász piszkos munkájára?";
			link.l1.go = "FraOff_1";
		break;

        case "FraOff_1":
			dialog.text = "A parancsokat nem lehet megvitatni, azokat végre kell hajtani. Ha minden kapitány eldöntené, hogy melyik parancsot érdemes végrehajtani... nem lenne haditengerészetünk.";
			link.l1 = "Mondja ezt az embereinek.";
			link.l1.go = "FraOff_2";
        break;

        case "FraOff_2":
			dialog.text = "Sarokba szorított, és megpróbálja megtörni a hûségemet és az eskümet. Ez a körülményeket tekintve elég gyenge csapás. Fejezzük ezt be a pengék összecsapásával, ne szavakkal!";
			link.l1 = "(Vezetés) Van egy harmadik út is. Hagyd abba a tiszthez méltatlan piszkos munkát. Csatlakozz hozzám - és én megmutatok neked egy másik világot.";
			link.l1.go = "FraOff_HireCheck";
            link.l2 = "Akkor fegyverbe!";
			link.l2.go = "FraOff_ExitFight";
        break;

        case "FraOff_HireCheck":
            if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 80)
            {
                notification("Képességpróba Sikertelen (80)", SKILL_LEADERSHIP);
                dialog.text = "Az árulókkal mindenhol egyformán bánnak. És én nem leszek az. En garde!";
                link.l1 = "Megvolt az esélyed, de elszalasztottad. En garde!";
                link.l1.go = "FraOff_ExitFight";
                break;
            }
            notification("Képességellenôrzés megfelelt", SKILL_LEADERSHIP);
            dialog.text = "Hûséget esküdtem a koronának, nem pedig a nagyképû, beképzelt bürokratáknak, akik azért küldenek minket a halálba, hogy eltakarják a saját mocskukat. De te... te a királyom ellensége vagy, és ezt nem hagyhatom figyelmen kívül.";
			link.l1 = "Holnap jóvátehetem az országod ellen elkövetett bûneimet - csak ki kell fizetnem a megfelelô közvetítôt. Ez többet mond a feletteseidrôl, mint rólam.";
			link.l1.go = "FraOff_Sucess";
        break;

        case "FraOff_Sucess":
			dialog.text = "Ez igaz. És belefáradtam, hogy ezt elviseljem. Kész vagyok a parancsnoksága alatt szolgálni, ha megígéri, hogy békén hagyja a franciákat.";
			link.l1 = "Nem tudom, kivel keresztezik majd az útjainkat, és nem tudok semmit garantálni. De ígérem, hogy ésszerû leszek. Üdvözlöm a legénységben, tiszt " + NPChar.name + "!"; // своего имени он вообще-то не называл
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
			dialog.text = "Így néz ki tehát a közellenség. Remélem, büszke vagy erre a címre, kalóz. Keményen megdolgozhattál érte\nA Casa de Contratación szerint, a spanyol korona zászlaja alatt közlekedô " + (Statistic_AddValue(PChar, "spa_AbordShip", 0) + Statistic_AddValue(PChar, "spa_KillShip", 0)) + " hajókat lôtted le. És ma az én gyönyörû hajóm is csatlakozik ehhez a listához" + GetSexPhrase(".","\nJaj a spanyol flottának! Szenvedtünk a betegségektôl, a kivételezéstôl, az árulástól... De hogy egy nô legyôzzön minket?");
			link.l1 = " Te vagy az utolsó, aki még áll, a legénységed halott. És te is, csak még nem vetted észre.";
			link.l1.go = "Alonso_1";
			if(Statistic_AddValue(PChar, "spa_AbordShip", 0) + Statistic_AddValue(PChar, "spa_KillShip", 0) < 1)
			{
				Achievment_Set("ach_CL_159")
			}
		break;

		case "Alonso_1":
            dialog.text = "Kár, hogy de Alba nem kapta meg ezt a feladatot. Ô jobban csinálta volna. De azért megpróbálom befejezni a munkát.";
            link.l1 = "Te a hazád igazi fia vagy. Készüljön fel a hôsökkel való találkozásra, senor.";
            link.l1.go = "Alonso_2";
            link.l2 = "A vadászból préda lett. Minden beszéded hiábavaló volt - ez olyan régi, mint az idô.";
            link.l2.go = "Alonso_3";
        break;

        case "Alonso_2":
            ChangeCharacterComplexReputation(PChar, "nobility", 5);
            dialog.text = "Köszönöm a szusszanást, de most a kardom fog beszélni.";
            link.l1 = "Fegyverbe!";
            link.l1.go = "Alonso_ExitFight";
        break;

        case "Alonso_3":
            ChangeCharacterComplexReputation(PChar, "nobility", -5);
            dialog.text = "Köszönöm a szusszanást, de most a kardom fog beszélni.";
            link.l1 = "Készülj a halálra!";
            link.l1.go = "Alonso_ExitFight";
        break;

        case "Alonso_ExitFight":
        	SetCharacterPerk(NPChar, "Rush");
            ActivateCharacterPerk(NPChar, "Rush");
            PlaySound("Ambient\Tavern\glotok_001.wav");
            PlaySound("Types\" + LanguageGetLanguage() + "\warrior03.wav");
            SendMessage(NPChar, "lfffsfff", MSG_CHARACTER_VIEWSTRPOS, 0.0, 0.0, 0.1, XI_ConvertString("Rampage"), 255.0, 30.0, 30.0);
            MakeUnpushable(NPChar, true);
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);
			QuestAboardCabinDialogExitWithBattle(""); 
            AddDialogExitQuest("MainHeroFightModeOn");
			DialogExit();
		break;

// ХИМЕРА -->
        case "FireBrigade_eng":
            // to_do: ты-вы у элен
            dialog.text = GetSexPhrase(PChar.Name + "! Az Ön neve olyan gyakran felbukkan a jelentésekben, mintha már régóta ismernénk egymást", "Miss McArthur! A pártfogója tudja, hogy mire készül? Á, mindegy. Biztos vagyok benne, hogy úgyis ô lesz a következô munkám") + "\nÖn szerencsés: a fônökeim szeretnek olyan sürgôs parancsokat küldeni, amelyek ellentmondanak az elôzôeknek. Ha nem lennék elfoglalva azzal, hogy eltakarítsam a régi antiguai legénységet... Hát, mindegy. Elég volt. Elvonod a figyelmemet a valódi munkáról.";
			link.l1 = "Te is elvonod a figyelmemet.";
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
            dialog.text = "Lánclövés a tathoz, majdnem elhibáztam! Ha az öreg csontjaim egy kicsit gyorsabbak lennének, én magam küldtem volna a tengeri ördögbe azt a szemetet. Köszönöm, kapitány. És köszönöm a néhai patrónusom nevében is!";
			link.l1 = "Ki vagy te? Fogoly? A legénységem szabadított ki?";
			link.l1.go = "Kneepel_1";	
		break;

        case "Kneepel_1":
            dialog.text = "Charlie Knippel személyesen. Az angol haditengerészet legjobb tüzére!";
			link.l1 = "Courtney azt mondta, sokáig kereste magát. Mi a helyzet?";
			link.l1.go = "Kneepel_2";	
		break;

        case "Kneepel_2":
            dialog.text = "Sok éven át szolgáltam egy Richard Fleetwood nevû bátor angol kapitányt. Sok csatát vívtunk együtt, és szolgáltuk igazi szenvedélyünket, az angol haditengerészetet. De egy nap minden megváltozott\nA londoni fônökök bábuként használtak minket. Mi a sajátjainkat támadtuk meg. Összepiszkítottuk az egyenruhánkat, hogy mások után takarítsunk. És most rajtunk a sor...";
			link.l1 = "Itt nincs ítélkezés. Az élet bonyolult, különösen, ha nem vagy a saját urad.";
			link.l1.go = "Kneepel_2_good";
            link.l2 = "Szóval, azt mondanád, hogy a régi bûnök árnyéka végül utolért téged?";
			link.l2.go = "Kneepel_2_bad";
		break;

        case "Kneepel_2_good":
            dialog.text = "Nem bántam meg, hogy a hazámat szolgáltam. Csak... fáj, kapitány. Különösen a patrónusomnak és szegény feleségének.";
			link.l1 = "És most mi lesz?";
			link.l1.go = "Kneepel_3";	
		break;

        case "Kneepel_2_bad":
            TEV.NoKneepel = "";
            dialog.text = "Nincs szükség a szurkálódásra... Már megfizettük az árat a bûneinkért, teljes egészében!";
			link.l1 = "És most mi lesz?";
			link.l1.go = "Kneepel_3";	
		break;

        case "Kneepel_3":
            dialog.text = "Most már név és haza nélküli ember vagyok. Bárhová mehetnék, de most nincs hová mennem. És senki, akivel mehetnék. Mindenhol szükség van tüzérekre, de nem minden hajónak van ágyúja.";
			link.l1 = "Csatlakozz hozzám. Nem mondhatom, hogy a legjobb kapcsolatom volt az angol flottával, de tisztelem a legjobbjait.";
            if(!CheckAttribute(&TEV, "NoKneepel"))
                link.l1.go = "Kneepel_3_good";
            else
                link.l1.go = "Kneepel_3_bad";
            link.l2 = "Vannak ágyúim. Ha tényleg ilyen jó vagy, mindig van hely egy igazi profinak a legénységemben.";
			link.l2.go = "Kneepel_3_bad";
		break;

        case "Kneepel_3_good":
            dialog.text = "Otthon hurok vár rám, ugyanez a helyzet a spanyolokkal és a hollandokkal, és a franciákkal sem törôdöm. De magának, úgy tûnik, szüksége van egy jó tüzérre. Benne vagyok, kapitány. Az elsô adandó alkalommal a kabinba megyek. Ugorjon be valamikor, és beszélgethetünk egy kis pia mellett.";
			link.l1 = "Isten hozta a fedélzeten.";
			link.l1.go = "Kneepel_Hired";	
		break;

        case "Kneepel_3_bad":
            dialog.text = "Az kizárt. Inkább veszek egy hajót, és eltûnök a szigetvilág legmélyebb bugyraiban. Köszönöm a mentést, kapitány, és viszlát.";
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
			dialog.text = "Nem magának kellett volna idáig eljutnia. Meifeng a Társaság agyara. Az én századom a bosszúálló penge. Mindkettôt összetörted. Ez... nem történhet meg.";
			link.l1 = "Úgy küldtek utánam, mintha egy vadállat lennék. És én harcoltam, mint egy sarokba szorított állat. Amikor harcolni vagy meghalni kell, az elméd kitisztul. A végén már csak egy kérdés maradt: Eljutok-e a legendás Xebec kabinjába - vagy sem.";
			link.l1.go = "Longway_1";
		break;

		case "Longway_1":
			dialog.text = GetSexPhrase("", "Furcsa, hogy egy nô a parancsnok. Ez nem is fordul elô. ") + "Számítottál rám?";
			link.l1 = "Vártál rám? A Meifeng egy nagy múltú hajó. Amikor átkeltem a hollandokon, tudtam, hogy elôbb vagy utóbb utánam küldenek. Becsületes vég lett volna... de nézd meg, hogy alakultak a dolgok.";
			link.l1.go = "Longway_2";
		break;

		case "Longway_2":
			dialog.text = "Az ellenség és önmagad ismerete a gyôzelem kulcsa. Szóval, meghoztad a döntésed. Hogy a saját feltételeid szerint nézz szembe az osztagommal. Kész voltál meghalni. De gyôztél. Most az életem a te kezedben van. Miért nem végzel velem?";
			link.l1 = "(Vezetés) Mert nem látom értelmét, hogy egy legendás kapitányt elsüllyesszünk csak a Cég ambíciói miatt. Voltam már a helyedben - egy bábu. Mások' érdekeit szolgálva, mások' parancsait követve. Azt ajánlom neked, amit egykor magam választottam: a szabadságot.";
            if (GetSummonSkillFromName(PChar, SKILL_LEADERSHIP) >= 50)
                link.l1.go = "Longway_Success";
            else
                link.l1.go = "Longway_Failed";
            link.l2 = "Mert minden kapitány megérdemli az utolsó szót. En garde!";
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
            notification("Képességpróba Sikertelen (50)", SKILL_LEADERSHIP);
			dialog.text = "A szabadságot nem adják. Hanem elvett dolog. És nem mindenki, aki a választásról beszél, képes azt felajánlani. Vannak utak, amiket nem lehet elkerülni. Vannak parancsok, amiket nem hagyhatsz befejezetlenül. Az én utam itt van. Az én parancsom az, hogy a végéig álljak.";
			link.l1 = "Szóval a halált választod?";
			link.l1.go = "Longway_Failed_over";
		break;

		case "Longway_Failed_over":
			dialog.text = "Nem. Azt választom, hogy önmagam maradok.";
			link.l1 = "Akkor harcoljunk!";
			link.l1.go = "Longway_ExitFight";
		break;

		case "Longway_Success":
            notification("Képességellenôrzés megfelelt", SKILL_LEADERSHIP);
			dialog.text = "Te nem olyan vagy, mint Rodenburg. Ô eszköznek tekintett engem. Téged pedig egyenrangúnak. Feláldozni magad nem erény. Kész vagyok meghallgatni a feltételeidet.";
			link.l1 = "Egyszerû. Legyen a navigátorom a zászlóshajómon. Vagy, ha akarod, kapsz egy saját hajót, és az én zászlóm alatt hajózol. Nem kell többé takarítania a Társaság után, vagy rejtegetnie a csontvázaikat a szekrényben. Szabad vagyok - és ezt a szabadságot kínálom neked is.";
			link.l1.go = "Longway_Success_over";
		break;

		case "Longway_Success_over":
			dialog.text = "Sok mindent láttam már: vért, aranyat, árulást. A Cég fizet, de nem tisztel. Hajót ad, de láncra verve tart. Te... választhatsz. Ha megtartod a szavad - Longway többé nem lesz vadász más akaratára. Ember lesz belôle. Egy kapitány. Vagy állj egy kapitány mellé, aki tudja, hova kell hajózni.";
			link.l1 = "Üdvözöllek a legénységben, Longway navigátor...";
			link.l1.go = "Longway_Hired";
		break;

		case "Longway_Hired":
			sld = InitLongwayFP("Longway_FP", NPChar);
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
