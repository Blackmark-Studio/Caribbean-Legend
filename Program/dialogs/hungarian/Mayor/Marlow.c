// Захария Марлоу, Чёрный Пастор, Пуэрто-Принсипе, Куба
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sLoc;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

// ------------------------------------------блок angry-----------------------------------------------
    if (CheckAttribute(npchar, "angry") && !CheckAttribute(npchar, "angry.ok"))
    {
        npchar.angry.ok = 1;
        if (!CheckAttribute(npchar, "angry.first")) //ловушка первого срабатывания
        {
            NextDiag.TempNode = NextDiag.CurrentNode;
            Dialog.CurrentNode = "AngryExitAgain";
            npchar.angry.first = 1;
        }
        else
        {
            switch (npchar.angry.kind) //сюда расписываем реакцию ангри. В npchar.angry.name пробелы удалены!!!
            {
                case "repeat":
                    if (npchar.angry.name == "Firsttime") Dialog.CurrentNode = "AngryRepeat_1";
                    if (npchar.angry.name == "I_know_you_good") Dialog.CurrentNode = "AngryRepeat_2";
                break;
            }
        }
    } //<-- блок angry

	switch(Dialog.CurrentNode)
	{
		case "First time":
            dialog.text = NPCStringReactionRepeat("Van valami dolga velem? Ha nem, akkor tûnjön el innen!",
                         "Azt hiszem, világosan fejeztem ki magam.", "Bár világosan fejeztem ki magam, te továbbra is idegesítesz!",
                         "Rendben, kezdek belefáradni ebbe a bunkóságba.", "repeat", 3, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Én máris elmegyek.",
                                               "Természetesen, lelkész úr.",
                                               "Sajnálom, lelkész úr.",
                                               "Oups...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			
			if (sti(pchar.GenQuest.Piratekill) > 20)
			{
				dialog.text = RandPhraseSimple("Megôrültél? Mészárost akartál játszani? Minden kalóz haragszik rád, fiú, jobb, ha elhagyod ezt a helyet.", "Úgy tûnik, hogy megharagudtál, fiú. Kinyújtóztatni akartad a kezed egy kicsit? Ne vedd sértésnek, de nincs itt semmi keresnivalód. Tûnj innen!");
				link.l1 = RandPhraseSimple("Figyelj, én helyre akarom hozni a helyzetet...", "Segítsen megoldani ezt a problémát...");
				link.l1.go = "pirate_town";
				break;
			}
			
			//--> Сага
			if(CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && !CheckAttribute(npchar, "quest.sharkbegin"))
			{
				link.l1 = "Megpróbálom megtalálni Shark Dodson-t. Azt mondják, hogy te vagy az utolsó ember, aki látta ôt. Tudna segíteni ebben?";
				link.l1.go = "Shark";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.BarbTemptation") && pchar.questTemp.Saga.BarbTemptation == "terrax" && CheckCharacterItem(pchar, "witches_hammer"))
			{
				link.l1 = "Miért vagy ilyen goromba? Vagy nem érdekli, hogy megkapja tôlem a kívánt könyvet?";
				link.l1.go = "book";
			}
			//<-- Сага
			//поручение капитана - выкуп
			if (CheckAttribute(pchar, "GenQuest.CaptainComission") && NPChar.city == pchar.GenQuest.CaptainComission.PiratesCity)
			{
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.toMayor"))
				{
					link.l1 = "Beszélni akarok a foglyáról.";
					link.l1.go = "CapComission1";
					DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
				}	
				if (pchar.GenQuest.CaptainComission.PirateShips == "died" || pchar.GenQuest.CaptainComission.PirateShips == "goaway") // лесник. новая проверка. искл. возможность сразу сдать задание,минуя 15 дней.
				{
					link.l1 = "Jó napot, lelkész úr. A küldetésérôl szeretnék beszélni.";
					link.l1.go = "CapComission3";
				}
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.RepeatSpeak") && !CheckAttribute(pchar,"GenQuest.CaptainComission.vikupzaplatil")) 
				{ // лесник . второй диалог с проверкой ,если ГГ ещё не принес деньги за выкуп.
					link.l1 = "Beszélni akarok a foglyáról.";
					link.l1.go = "CapComission6";
				}
			}
		break;
		
		case "shark":
			dialog.text = "Steven Dodson? Nem tudom, hogy a történetem hogyan segíthetne, mert Shark az elmúlt hónapokban eltûnt, és senki sem látta. Bár ez nem meglepô, megölte Blaze Sharpot, és ezzel az ostoba tettével lejáratta a saját nevét. Ellenségévé tett néhány nagyhatalmú korzórt.";
			link.l1 = "Minden okom megvan arra, hogy azt higgyem, Shark ártatlan Sharp halálában. Én nem tudom bizonyítani, talán Shark maga is meg tudja tenni. Mondasz nekem valamit róla?";
			link.l1.go = "shark_1";
		break;
		
		case "shark_1":
			dialog.text = "Néhány hónappal ezelôtt Steven eljött hozzám, és egy nagyon furcsa üzletet ajánlott: egy hónapra otthagyta a fregattját 'Fortune' in gage-ben, cserébe egy élelemmel teli briggért. Aztán vagy visszaadja nekem a fregettet és a pénzt az élelemért, vagy megtartom a fregattját. Eltelt egy hónap - sem Sharknak, sem a briggemnek, sem a pénznek nem volt nyoma.\nMellett hallottam olyan pletykákat, hogy Blaze-t meggyilkolták, és Shark volt a gyanúsított. Mit gondolhattam volna? Helyes! Azt hittem, hogy Steven megmenekült a legrosszabbtól. Eladtam a fregattját egy William Patterson nevû angolnak, aki nagyon elégedett volt, és egy nagy halom dublont fizetett a hajóért.\nEzért teljesen megtérítettem a költségeimet, és nem neheztelek rá. Nem érdekel Sharp halála, nekem a saját problémáim miatt kell aggódnom.";
			link.l1 = "Nem gondolja, hogy ha meg akart volna szökni, nem lett volna szüksége a maga fogdájára? Volt saját hajója, ami százszor jobb, mint bármelyik brigg. Úgy tûnik, Sharknak volt egy terve, de valami rosszul sült el, és nem tért vissza idôben.";
			link.l1.go = "shark_2";
		break;
		
		case "shark_2":
			dialog.text = "Ahogy már mondtam, nem érdekelnek Dodson problémái. Én teljesítettem az alku rám esô részét. Ami a hajót illeti, jobb, ha megkérdezed tôle, miért volt szüksége arra az átkozott briggre. Nem kényszerítettem, hogy elvigye.";
			link.l1 = "Rendben, ne beszéljünk errôl többet. Természetesen igaza van. Mondja, tisztában van azzal, hogy Steven merre tartott a briggjén?";
			link.l1.go = "shark_3";
		break;
		
		case "shark_3":
			dialog.text = "Ki tudja biztosan. De van néhány tippem. Északnyugatra hajózott a Main felé. Tehát vagy a Veszedelmes-öböl, amely az ellenséges indiánjairól ismert, vagy Új-Spanyolország, amely a pápistáiról és az inkvizícióról ismert.\nKétlem, hogy bármelyik helyre elhajózott volna. De azt mondják, hogy van egy különös hely, amit úgy hívnak 'City of Abandoned Ships' kuba északnyugati részén található. Sokan ezt mítosznak tartják, de én nem. Nem azért, mert annyira romantikus ember vagyok, hanem mert vannak valódi emberek, akik ott hajóznak a hosszúhajóikkal. Legalábbis régebben.";
			link.l1 = "És kik ôk?";
			link.l1.go = "shark_4";
		break;
		
		case "shark_4":
			dialog.text = "Kubai kalózok. Barkáikat bikák tetemével megrakodták, és északnyugatra hajóznak. Kicsit késôbb mindig visszatértek, zsebük tele pénzzel vagy ritka és értékes áruval.";
			link.l1 = "Érdekes! Hol találom ezeket a kalózokat?";
			link.l1.go = "shark_5";
		break;
		
		case "shark_5":
			dialog.text = "Miért engem kérdezel? Kutassátok át Kuba erdejét. Még ha meg is találod ôket, nem mondanak neked semmit, miért is fednék fel jó megélhetésük forrását? Úgyhogy ne vesztegesd az idôdet, már régóta nem látta ôket senki, hogy megint ezt csinálják.\nSzintén hallottam néhány feljegyzésrôl, amit Alvarado spanyol tengerész írt, aki maga is járt a szigeten. Szóval kíváncsi vagyok, talán mégiscsak Steven hajózott oda.";
			link.l1 = "Az ismeretlen sziget, ami nincs rajta a térképeken... Nos... Ez nem túl biztató információ.";
			link.l1.go = "shark_6";
		break;
		
		case "shark_6":
			dialog.text = "Már az elején megmondtam, hogy a történetem nem fog segíteni. És miért van szüksége Dodsonra?";
			link.l1 = "Én és az Erdei Ördög ôt akarjuk megválasztani a Parti Testvérek vezetôjének. Ahogy már mondtam, komoly okok szólnak amellett, hogy Blaze-t valaki más ölte meg.";
			link.l1.go = "shark_7";
		break;
		
		case "shark_7":
			dialog.text = "Heh! Gondolom, hogy Jan ôt képviseli? Nos, ismered a törvényt - Dodsonnak minden bárótól kell egy szavazatot kapnia.";
			link.l1 = "Ismerem a törvényt. Akkor a második kérdésem. Dodsonra fogsz szavazni a választáson?";
			link.l1.go = "shark_8";
		break;
		
		case "shark_8":
			dialog.text = "Nos, elôbb neki kellene visszatérnie. Igazából nem érdekel, ki fogja vezetni a Testvériséget, amíg jól végzi a dolgát, és nem zavar engem. Mint mondtam, nekem is vannak saját problémáim. Tudod, hány boszorkány és mágus van a szigetünkön? Nem? Megmondom: egy légió! Emellett Santiagóban és Havannában is rengeteg pápista van.\nApropó, mágusok. Van egy könyv, a címe 'Hammer a boszorkányoknak'. Nagyon szeretném megszerezni, de csak angolul, nem kell latin, német vagy spanyol fordítás, nem ismerem ezeket a nyelveket. Hozzátok el nekem a könyvet, és Dodsonra szavazok.\nTudjátok, hogy Jackman megígérte, hogy én is megtalálom, szóval ha neki sikerül elôbb... akkor ne engem hibáztassatok.";
			link.l1 = "Rendben, megfontolom. Köszönöm, hogy idôt szakítottál rám. Viszlát.";
			link.l1.go = "shark_9";
		break;
		
		case "shark_9":
			DialogExit();
			pchar.questTemp.Saga.SharkHunt = "after_marlow";
			npchar.quest.sharkbegin = "true";
			AddQuestRecord("SharkHunt", "2");
		break;
		
		case "book":
			dialog.text = "A könyv? Gondolom, a 'Hammer a boszorkányoknak'?könyvrôl beszélsz.";
			link.l1 = "Hát persze. Sikerült megtalálnom önnek. Angolul van, ahogy kérte.";
			link.l1.go = "book_1";
		break;
		
		case "book_1":
			dialog.text = "Ha, bocsánat a durva fogadtatásért, pajtás. Nem fordul elô többet... Hadd lássam azt a csodát!";
			link.l1 = "Persze, nézze meg.";
			link.l1.go = "book_2";
		break;
		
		case "book_2":
			RemoveItems(pchar, "witches_hammer", 1); // удалить трактат
			dialog.text = "Végre! Reszkessetek, pokol szolgái! Nem hagylak békén, amíg a kezem nem képes többé lecsapni...";
			link.l1 = "Örülök neked, lelkész úr. És mi lesz a szavazatoddal?";
			link.l1.go = "book_3";
		break;
		
		case "book_3":
			dialog.text = "Ahogy már mondtam 'nem érdekel, hogy ki lesz a vezetô'. biztos vagyok benne, hogy Svenson nem fog méltatlan embert választani. Szóval fogadd el a szavazatomat. Csinálj vele, amit akarsz. Itt az én szilánkom.";
			link.l1 = "Köszönöm, Zakariás. Ott találkozunk!";
			link.l1.go = "book_4";
		break;
		
		case "book_4":
			GiveItem2Character(pchar, "splinter_zm"); // дать осколок
			DialogExit();
			NextDiag.CurrentNode = "I_know_you_good";
			AddQuestRecord("BarbTemptation", "27");
			if (CheckCharacterItem(pchar, "splinter_mt") && CheckCharacterItem(pchar, "splinter_jb") && CheckCharacterItem(pchar, "splinter_zm")) Saga_GiveCalendar();
			ChangeCharacterComplexReputation(pchar, "fame", 1);
		break;

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

        case "I_know_you_good":
            dialog.text = NPCStringReactionRepeat(GetFullName(pchar) + ", örülök, hogy látlak! Mit akarsz?",
                         "Mit szeretnél még?", "Már megint? Ne zavard az embereket, ha nincs semmi dolgod!",
                         "Te egy "+ GetSexPhrase("jó közlegény vagy","jó lány") +", úgyhogy egyelôre élhetsz. De nem akarok veled többet beszélni.", "repeat", 10, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Csak látogatóba jöttem.",
                                               "Semmi...",
                                               "Jól van, lelkész úr, sajnálom...",
                                               "Francba, az én hibám!", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";
			
			if (sti(pchar.GenQuest.Piratekill) > 20)
			{
				dialog.text = RandPhraseSimple("Megôrültél? Mészárost akartál játszani? Minden kalóz haragszik rád, fiú, úgyhogy jobb, ha elmész innen...", "Úgy tûnik, hogy megharagudtál, fiú. Kinyújtóztatni akartad a kezed egy kicsit? Ne vedd sértésnek, de nincs itt semmi keresnivalód. Tûnj innen!");
				link.l1 = RandPhraseSimple("Figyelj, én helyre akarom hozni a helyzetet...", "Segítsen megoldani ezt a problémát...");
				link.l1.go = "pirate_town";
				break;
			}
			//поручение капитана - выкуп
			if (CheckAttribute(pchar, "GenQuest.CaptainComission") && CheckAttribute(pchar,"GenQuest.CaptainComission.toMayor"))
			{
				link.l1 = "A foglyáról van szó.";
				link.l1.go = "CapComission1";
				DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
			}		
			if (CheckAttribute(pchar, "GenQuest.CaptainComission") && CheckAttribute(pchar,"GenQuest.CaptainComission.toMayor"))
			{
				link.l1 = "A foglyáról van szó.";
				link.l1.go = "CapComission1";
				DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
			}	
			if (pchar.GenQuest.CaptainComission.PirateShips == "died" || pchar.GenQuest.CaptainComission.PirateShips == "goaway")//  правка лесник,новая проверка ,исключающая тут же сдачу задания
			{
				link.l1 = "Helló, lelkész úr, a küldetése miatt vagyok itt.";
				link.l1.go = "CapComission3";
			}
			if (CheckAttribute(pchar, "GenQuest.Marginpassenger") && pchar.GenQuest.Marginpassenger == "cabin" && CheckAttribute(pchar, "questTemp.LongHappy"))
			{ // лесник . похититель  ( после ДЛС ДиС ,когда барбазона уже нет)
				link.l1 = "Úgy hallottam, hogy a foglyokkal kapcsolatos üzletet folytatsz...";
				link.l1.go = "Marginpassenger";
			}
		break;
		
	//-----------------------------------Поручение капитана - Выкуп-------------------------------------------------
		case "CapComission1":
			dialog.text = "Ha-ha. Azt hiszed, hogy csak egy foglyom van itt? Nevezd meg.";
			link.l1 = pchar.GenQuest.CaptainComission.SlaveName + ". Itt van?";
			link.l1.go = "CapComission2";
			DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
		break;

		case "CapComission2":
			if(CheckAttribute(pchar,"GenQuest.CaptainComission.DaysLeft"))
			{
				dialog.text = "Itt volt. Eladtam annak a barbadosi ültetvénytulajdonosnak - Bishop ezredesnek, amikor egy hete itt járt.";
				link.l1 = "A fenébe...";
				link.l1.go = "CapComission2_1";
			}
			else
			{
				dialog.text = "Á, végre. Arra gondoltam, hogy eladom annak a barbadosi ültetvényesnek, aki egy-két héten belül itt lesz... Van váltságdíja?";
				link.l1 = "Nézze, van egy kis probléma... Valójában, nincs annyi pénzem. De kész vagyok dolgozni.";
				link.l1.go = "CapComission2_2";
				if(makeint(pchar.money) > 150000)
				{
					link.l2 = "Jó, hogy nem adtad el. Itt vannak az érméi - 150.000 pezó. Hol kaphatom meg?"
					link.l2.go = "CapComission2_3";
				}	
			}
		break;
		
		case "CapComission2_1":
			dialog.text = "Túl lassú voltál... És miért érdekel téged? Csak a rokonaival tárgyaltam.";
			link.l1 = "Ôk kértek meg, hogy jöjjek ide.";
			link.l1.go = "CapComission2_11";
		break;
		
		case "CapComission2_11":
			dialog.text = "Hát, elkéstél. Nem tehetek semmit.";
			link.l1 = "Figyelj, mennyiért adtad el ôt, ha nem titok?"; 
			link.l1.go = "CapComission2_12";
		break;
		
		case "CapComission2_12":
			dialog.text = "Eh, nem az. De nem fogom elmondani... ki fogsz nevetni, ha megteszem. Ha-ha-ha-ha-ha! Viszlát.";
			link.l1 = "Viszlát.";
			link.l1.go = "exit";
			AddQuestRecord("CaptainComission1", "10");
			AddQuestUserData("CaptainComission1", "sName", "Zachary Marlow");//правка лесник.  в СЖ запись ниже не работает																																				  
			//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));																															 
			CaptainComission_GenerateManager();
		break;
		
		case "CapComission2_2":
			if(rand(3) == 1)
			{
				dialog.text = "Nos, " + pchar.name + ", tudod, ez nem így mûködik. Gyere vissza pénzzel, és megkapod a gyengébbik feledet, ha-ha.";
				link.l1 = "Jól van. Viszlát.";
				link.l1.go = "CapComission2_4";
			}
			else
			{
				dialog.text = "Nocsak, nocsak... Van egy üzletem... Még azt sem tudom, hogy kezdjem el. El kell süllyesztenem egy kalózt, aki átlépte a határt.";
				link.l1 = "Nem lehet egyszerûen megölni a dzsungelben?";
				link.l1.go = "CapComission2_2_1";
			}
		break;

		case "CapComission2_2_1":
			dialog.text = "Az üzlet nem így mûködik, tudod... Nem a halálára van szükségem, hanem arra, hogy megtanítsak néhány embert, hogy ne vegyék el a részemet a zsákmányból. De nem fogom megbánni a halálát.";
			link.l1 = "Miért nem küldesz érte saját embereket?";
			link.l1.go = "CapComission2_2_2";
		break;
		
		case "CapComission2_2_2":
			CaptainComission_GetRandomShore();
			pchar.GenQuest.CaptainComission.ShipName1 = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.GenQuest.CaptainComission.ShipName2 = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.GenQuest.CaptainComission.UnknownPirateName = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);
			sLoc = XI_ConvertString(pchar.GenQuest.CaptainComission.Island + "Dat"); // belamour gen
			dialog.text = "Hm... Nos, " + GetName( NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.UnknownPirateName, NAME_NOM) + " meggyôzött néhány kalózt, hogy a zsákmányuk egy részét a mi rejtekhelyünkön tartják, nem messze " + XI_ConvertString(pchar.GenQuest.CaptainComission.Island.Shore + "Gen") + ". Két hajójuk '" + pchar.GenQuest.CaptainComission.ShipName1 + "' és '" + pchar.GenQuest.CaptainComission.ShipName2 + "' nemrég vetett horgonyt és elhajózott " + sLoc + ". Most már érted, miért nem bízhatom az embereimre ezt a munkát?";
			link.l1 = "Én igen. Mennyi idôm van?";
			link.l1.go = "CapComission2_2_3";
		break;
		
		case "CapComission2_2_3":
			dialog.text = "12-15 nap, nem több, nekem az a fontos, hogy ne jussanak el a rejtekhelyre, különben ostobaság lenne elsüllyeszteni ôket az értékes rakománnyal. Ebben az esetben jobb lenne, ha ide hoznák...";
			link.l1 = "Rendben, én benne vagyok. Megpróbálom elkapni ôket.";
			link.l1.go = "CapComission2_2_4";
		break;
		
		case "CapComission2_2_4":
			AddQuestRecord("CaptainComission1", "24");
			AddQuestUserData("CaptainComission1", "sName", "Zachary Marlow");//правка																			   
			//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			AddQuestUserData("CaptainComission1", "sShipName1", pchar.GenQuest.CaptainComission.ShipName1);
			AddQuestUserData("CaptainComission1", "sShipName2", pchar.GenQuest.CaptainComission.ShipName2);
			AddQuestUserData("CaptainComission1", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.Island.Shore + "Dat")); // belamour gen
			AddQuestUserData("CaptainComission1", "sShoreType", XI_ConvertString(GetIslandByArealName(pchar.GenQuest.CaptainComission.Island) + "Voc")); // belamour gen
			pchar.quest.CapComission_PirateAttack.win_condition.l1 = "location";
            pchar.quest.CapComission_PirateAttack.win_condition.l1.location = pchar.GenQuest.CaptainComission.Island;
            pchar.quest.CapComission_PirateAttack.function = "CaptainComission_GeneratePirateShips"; 
			SetFunctionTimerCondition("CaptainComission_PirateShipsOver", 0, 0, 15, false);
			//pchar.GenQuest.CaptainComission.PirateShips = "sdatkwest";	// лесник - заменил проверку для сдачи сразу.
			DialogExit();
		break;
		
		case "CapComission2_3":
			dialog.text = "Ne aggódjatok. Az embereim majd átadják a hajódnak. És miért érdekel téged?";
			link.l1 = "Nem érdekel. A rokonai kértek meg, hogy szállítsam le.";
			link.l1.go = "CapComission2_31";
		break;
		
		case "CapComission2_31":
			dialog.text = "Á, rendben van. Már majdnem megbántam, hogy ilyen alacsony árat adtam az emberedért. Ha-ha-ha-ha-ha-ha. Viszontlátásra.";
			link.l1 = "Viszlát.";
			link.l1.go = "CapComission2_32";
		break;
		
		case "CapComission2_32":
			AddQuestRecord("CaptainComission1", "9");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));	// belamour gen	
			addMoneyToCharacter(pchar, -150000);
			pchar.GenQuest.CaptainComission.vikupzaplatil = true; // новая проверка ,если шарль заплатил выкуп за пленника. лесник																																																			
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");	
		break;
		
		case "CapComission2_4":
			if(!CheckAttribute(pchar,"GenQuest.CaptainComission.RepeatSpeak"))
			{
				AddQuestRecord("CaptainComission1", "31");
				AddQuestUserData("CaptainComission1", "sName", "Zachary Marlow");		// лесник																											 
				//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));// в СЖ не работает
			}	
			pchar.GenQuest.CaptainComission.RepeatSpeak = true;		
			DialogExit();
		break;
		
		case "CapComission3":
			dialog.text = "Szóval, , " + GetFullName(pchar) + ", elsüllyesztetted a haverjaimat? He-he-he-he...";
			if(pchar.GenQuest.CaptainComission.PirateShips == "goaway")
			{
				link.l1 = "Nem. Nem sikerült elkapnom ôket. És nem találkoztam velük, amikor visszatértem.";
				link.l1.go = "CapComission4";
			}
			if(pchar.GenQuest.CaptainComission.PirateShips == "died")	
			{
				link.l1 = "Én igen. Elküldtem ôket, hogy etessék a cápákat.";
				link.l1.go = "CapComission5";
			}
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
		break;
		
		case "CapComission4":
			dialog.text = "A francba! Találkoztál velük vagy sem, most már mindegy! És mi lesz a következô javaslatod?";
			link.l1 = "Talán van egy könnyebb munkád számomra?";
			link.l1.go = "CapComission4_1";
			link.l2 = "Figyelj, "+ NPChar.name +", csökkentsd a fogoly árát...";
			link.l2.go = "CapComission4_2";
		break;
		
		case "CapComission4_1":
			dialog.text = "Nem.";
			link.l1 = "Akkor viszlát...";
			link.l1.go = "CapComission4_3";
		break;
		
		case "CapComission4_2":
			dialog.text = "Hozd le az árat?! Épp most vesztettem el a készletemet a hozzá nem értésed miatt! És most felemelhetem az árat! Elviheted 200.000 pesoért, ha akarod, vagy elhúzhatsz innen a pokolba.";
			link.l1 = "Ez túl drága... Viszlát...";
			link.l1.go = "CapComission4_4";
			if(sti(pchar.money) >= 200000)
			{
				link.l2 = "A francba, vedd el az érméidet.";
				link.l2.go = "CapComission4_5";
			}	
		break;
		
		case "CapComission4_3":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			AddQuestRecord("CaptainComission1", "27");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", "Marlow");		// лесник																								   
			//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_DAT));
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			DialogExit();
		break;
		
		case "CapComission4_4":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			AddQuestRecord("CaptainComission1", "28");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", "Marlow"); // правка	// лесник																											 
			//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			DialogExit();		
		break;
		
		case "CapComission4_5":
			dialog.text = "Elviheted ezt a gyengét...";
			link.l1 = "Ég veled!";
			link.l1.go = "CapComission4_6";
		break;
		
		case "CapComission4_6":
			addMoneyToCharacter(pchar, -200000);
			AddQuestRecord("CaptainComission1", "29");
			AddQuestUserData("CaptainComission1", "sName", "Marlow"); // правки имени в сж лесник																										  
			AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));// в сж не работает
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			pchar.GenQuest.CaptainComission.SlaveAddMoney = true;
			DialogExit();	
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");	
		break;
		
		case "CapComission5":
			dialog.text = "Ho-ho! Szép munka! Fogd a gyengédet és sok szerencsét.";
			link.l1 = "Köszönöm. Viszlát.";
			link.l1.go = "CapComission5_1";
		break;
		
		case "CapComission5_1":
			AddQuestRecord("CaptainComission1", "34");
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			DialogExit();		
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");	
		break;
		
			/*case "CapComission6":    // ЕСЛИ В ПЕРВЫЙ РАЗ ОТКАЗАЛ В ЗАДАНИИ ,ТО ПУСТЬ БАБКИ ИЩЕТ
		     ИНАЧЕ ПОВТОРНАЯ ДАЧА ЗАДАНИЯ ПРЕВРАЩАЕТ КВЕСТ В КАШУ.. лесник
			dialog.text = "Elhozta a váltságdíjat"+ GetSexPhrase("","la") +"? Mert én nem vicceltem, amikor mondta, hogy eladom az ültetvényeseknek.";			
			link.l1 = "Figyelj, "+ NPChar.name +", a helyzet a következô... Amúgy nekem nincs ilyen pénzem. De hajlandó vagyok"+ GetSexPhrase("","és") +" megoldani.";
			link.l1.go = "CapComission2_2";
			if(makeint(pchar.money) > 150000)
			{
				link.l2 = "Jó, hogy nem adtad el. Itt vannak az érméi - 150000 pezó. Hol kaphatom meg?"
				link.l2.go = "CapComission2_3";
			}			
		break;*/
		  case "CapComission6":                        // лесник . пусть шарль бабло ищет,или забить на пленника.
			dialog.text = "Elhoztad a pénzt? Nem vicceltem azzal, hogy eladtam azt az embert az ültetvénynek.";			
			link.l1 = "Nincs rá pénzem, " + NPChar.name + ", de dolgozom rajta.";
			link.l1.go = "exit";
			if(makeint(pchar.money) > 150000)
			{
				link.l2 = "Jó, hogy nem adtad el. Itt vannak az érméi - 150.000 pezó. Hol kaphatom meg?"
				link.l2.go = "CapComission2_3";
			}			
		break;

																																				 																																													  																																															
//--------------------------------------------Похититель------------------------------------------------------
		case "Marginpassenger":
			dialog.text = "És miért érdekel téged, hogy mit csinálok? Tudod, jobb lenne, ha elmennél...";
			link.l1 = "Tshh, nyugodj meg. Van egy üzletem veled. A foglyodról van szó.";
			link.l1.go = "Marginpassenger_1";
		break;
		
		case "Marginpassenger_1":
			dialog.text = "Á, rendben. Kiért akar váltságdíjat kérni?";
			link.l1 = "Várjon. Nem azért jöttem, hogy kivásároljam, hanem azért, hogy felajánljam, hogy megvehet egy foglyot. Nos, és lesz lehetôsége váltságdíjat kérni érte.";
			link.l1.go = "Marginpassenger_2";
		break;
		
		case "Marginpassenger_2":
			dialog.text = "Hm. És miért van szüksége az ügynökségemre? Miért nem akarsz pénzt szerezni magadnak?";
			link.l1 = "Az elég kockázatos lenne számomra. Lehet, hogy gondjaim lesznek a hatóságokkal.";
			link.l1.go = "Marginpassenger_3";
		break;
		
		case "Marginpassenger_3":
			dialog.text = "Ha-h... akkor rendben. Nézzük meg. Ki a foglya?";
			link.l1 = "Ez a "+pchar.GenQuest.Marginpassenger.Text+" "+XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.City+"Gen")+".";
			link.l1.go = "Marginpassenger_4";
		break;
		
		case "Marginpassenger_4":
			int iTemp = makeint(sti(pchar.GenQuest.Marginpassenger.Dublon)*2*stf(pchar.GenQuest.Marginpassenger.Chance))*100;
			dialog.text = "Értem... ez egy jó üzlet lenne, ha nem hazudik. Gondolom, hogy fizethetek neked ezért az emberért "+iTemp+" pezót, vagy adhatok helyette valami érdekes információt. A választás a tiéd.";
			link.l1 = "Inkább a pezót választom. Elegem van ebbôl az üzletbôl...";
			link.l1.go = "Marginpassenger_money";
			link.l2 = "Ha! Mesélj még. Biztos vagyok benne, hogy valami érdekeset fogsz mondani.";
			link.l2.go = "Marginpassenger_offer";
		break;
		
		case "Marginpassenger_money":
			dialog.text = "Akkor pénzt. Fogd ôket. Ez nem a te problémád. Hozza ide az eladás tárgyát.";
			link.l1 = "Már a város kapujának közelében kell lennie. Köszönöm. Nagyon sokat segítettél nekem.";
			link.l1.go = "Marginpassenger_money_1";
		break;
		
		case "Marginpassenger_money_1":
			iTemp = makeint(sti(pchar.GenQuest.Marginpassenger.Dublon)*2*stf(pchar.GenQuest.Marginpassenger.Chance))*100;
			dialog.text = "Szívesen, hozzon még... Viszlát!";
			link.l1 = "Sok szerencsét...";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, iTemp);
			sld = characterFromId("MarginPass");
			RemovePassenger(Pchar, sld);
			sld.lifeday = 0;
			AddQuestRecord("Marginpassenger", "12");
			AddQuestUserData("Marginpassenger", "sSum", iTemp);
			CloseQuestHeader("Marginpassenger");
			DeleteAttribute(Pchar, "GenQuest.Marginpassenger");
		break;
		
		case "Marginpassenger_offer":
			pchar.GenQuest.Marginpassenger.Goods = GOOD_EBONY + rand(makeint(GOOD_MAHOGANY - GOOD_EBONY));
			pchar.GenQuest.Marginpassenger.GoodsQty = 200+rand(10)*10;
			switch (hrand(1))
			{
				case 0: //бухта на южном мейне
					SelectSouthshore();
					while (!isLocationFreeForQuests(pchar.GenQuest.Marginpassenger.Shore)) SelectSouthshore();
					dialog.text = "Jó egy okos emberrel üzletelni. Most figyelj: néhány nap múlva a " + XI_ConvertString(pchar.GenQuest.Marginpassenger.Shore+"Dat") + " egy spanyol expedíció érkezik Mainból, értékes árukkal megrakodva. Várni fognak egy hajóra, amelynek elvileg a rakományt kell átvennie. Ha egy héten belül odaérsz, akkor lesz esélyed, hogy magadhoz vedd a rakományt.\nA te helyedben én már indulnék is a hajómhoz. És idehoznám a foglyot.";
					link.l1 = "Köszönöm. Köszönöm. Az áru szép kárpótlás lesz a fáradozásaimért. Az utasomnak pedig már a város kapujának közelében kell lennie. El fogjuk hozni hozzád.";
					link.l1.go = "Marginpassenger_offer_1";
				break;
				
				case 1: //просто кораблик
					SelectSouthcity();
					pchar.GenQuest.Marginpassenger.ShipName1 = GenerateRandomNameToShip(SPAIN);
					dialog.text = "Jó egy okos emberrel üzletelni. Most figyelj: körülbelül egy hét múlva egy spanyol brigantin '"+pchar.GenQuest.Marginpassenger.ShipName1+"' értékes árukkal megrakodva "+XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Southcity+"Gen")+" elhajózik "+XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Southcity1+"Gen")+". Ha sietsz, könnyen elkaphatod.\nMég mindig itt vagy? A helyedben én már elindultam volna a hajóm felé. És idehoznám a foglyot.";
					link.l1 = "Köszönöm. Köszönöm. Az áru szép kárpótlás lesz a fáradozásaimért. Az utasomnak pedig már a város kapujának közelében kell lennie. El fogjuk hozni hozzád.";
					link.l1.go = "Marginpassenger_offer_2";
				break;
			}
			sld = characterFromId("MarginPass");
			RemovePassenger(Pchar, sld);
			sld.lifeday = 0;
			pchar.GenQuest.Marginpassenger = "final";
		break;
		
		case "Marginpassenger_offer_1":
			DialogExit();
			AddQuestRecord("Marginpassenger", "13");
			AddQuestUserData("Marginpassenger", "sShore", XI_ConvertString(pchar.GenQuest.Marginpassenger.Shore+"Dat"));//лесник - окончание в СЖ // belamour gen: Abl - это к Залив"ом", нужен дательный
			AddQuestUserData("Marginpassenger", "sName", "Zachary Marlow")); // belamour gen : как-то странно, наводку даёт Захар, а в сж Добряк дефолтом
			SetFunctionTimerCondition("Marginpassenger_SouthshoreOver", 0, 0, 7, false);
			pchar.quest.Marginpassenger.win_condition.l1 = "location";
			pchar.quest.Marginpassenger.win_condition.l1.location = pchar.GenQuest.Marginpassenger.Shore;
			pchar.quest.Marginpassenger.function = "Marginpassenger_Southshore";
		break;
		
		case "Marginpassenger_offer_2":
			DialogExit();
			AddQuestRecord("Marginpassenger", "16");
			AddQuestUserData("Marginpassenger", "sName", "Zachary Marlow")); // belamour gen 
			AddQuestUserData("Marginpassenger", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Southcity+"Gen"));
			AddQuestUserData("Marginpassenger", "sCity1", XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Southcity1+"Acc")); // лесник - окончание в СЖ
			AddQuestUserData("Marginpassenger", "sShipName", pchar.GenQuest.Marginpassenger.ShipName1);
			SetFunctionTimerCondition("Marginpassenger_SouthshipInWorld", 0, 0, 5+rand(2), false);
		break;
		
		// ============== Грабеж среди бела дня, попытка залезть в сундуки =========================
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Rablás!!! Ez elfogadhatatlan! Készülj fel, "+ GetSexPhrase("fiú","lány") +"...", "Hé, mi a fenét csinálsz ott?! Azt hitted, hogy kirabolhatsz? Végeztél...", "Várj, mi a fene? Vedd le a kezed! Kiderült, hogy te egy tolvaj vagy! Vége a sornak, te szemétláda...");
			link.l1 = LinkRandPhrase("A francba!", "Carramba!!", "A francba!!");
			link.l1.go = "PL_Q3_fight";
		break;
					
		// ======================== блок нод angry ===============>>>>>>>>>>>>>>>
		case "AngryRepeat_1":
            dialog.text = RandPhraseSimple(""+ GetSexPhrase("Tûnj el ","Tûnj el") +" innen!", "Takarodj az otthonomból!");
			link.l1 = "Oups...";
		    link.l1.go = "AngryExitAgainWithOut";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся через 10 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "Ne zavarj az olcsó beszédeddel. Legközelebb nem fog tetszeni az eredmény...";
        			link.l1 = "Megvan.";
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
            }
    	break;
		
		case "AngryRepeat_2":
            dialog.text = RandPhraseSimple("Vége, nincs beszéd.", "Nem akarok veled többet beszélni, úgyhogy jobb, ha nem zavarsz.");
			link.l1 = RandPhraseSimple("Ahogy kívánod...", "Hm, akkor jó...");
		    link.l1.go = "AngryExitAgain";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся через 10 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "Remélem, hogy több tiszteletet fogsz mutatni, és nem leszel többé bunkó?";
        			link.l1 = "Biztos lehet benne, lelkész úr, hogy el fogok.";
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
            }
    	break;
		
		case "AngryExitAgain":
            DialogExit();
            DeleteAttribute(npchar, "angry.ok");
		break;
		
		case "AngryExitAgainWithOut":
            DialogExit();
            DeleteAttribute(npchar, "angry.ok");
            DoReloadCharacterToLocation("Puertoprincipe_town","reload","reload6");
		break;
		// <<<<<<<<<<<<============= блок нод angry =============================
		case "pirate_town":
            dialog.text = "Megoldja a problémát? Van fogalmad róla, hogy mit tettél? Mindegy, hozzon nekem egy millió pezót, és ráveszem a fiúkat, hogy felejtsék el a tettét. Ha nem tetszik az ötlet, akkor mehetsz a pokolba.";
			if (sti(Pchar.money) >= 1000000)
			{
				link.l1 = "Rendben, kész vagyok fizetni.";
				link.l1.go = "pirate_town_pay";
			}
			link.l2 = "Megvan. Elmegyek.";
			link.l2.go = "pirate_town_exit";
		break;
		
		case "pirate_town_exit":
			DialogExit();
            bDisableFastReload = true;//закрыть переход
			pchar.quest.pirate_in_town.win_condition.l1 = "ExitFromLocation";
			pchar.quest.pirate_in_town.win_condition.l1.location = pchar.location;
			pchar.quest.pirate_in_town.function = "TownPirate_battle";
		break;
		
		case "pirate_town_pay":
            dialog.text = "Jól van. Tekintsd magad újra tisztának. De remélem, hogy nem fogsz többé ilyen undorító dolgokat csinálni.";
			link.l1 = "Nem fogok. Túl drága nekem. Viszlát...";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -1000000);
			pchar.GenQuest.Piratekill = 0;
		break;
	}
}

void SelectSouthshore()
{
	switch (rand(6))
	{
		case 0: pchar.GenQuest.Marginpassenger.Shore = "part37"; break;
		case 1: pchar.GenQuest.Marginpassenger.Shore = "parton47"; break;
		case 2: pchar.GenQuest.Marginpassenger.Shore = "part48"; break;
		case 3: pchar.GenQuest.Marginpassenger.Shore = "part25"; break;
		case 4: pchar.GenQuest.Marginpassenger.Shore = "part21"; break;
		case 5: pchar.GenQuest.Marginpassenger.Shore = "shore20"; break;
		case 6: pchar.GenQuest.Marginpassenger.Shore = "parton19"; break;
	}
}

void SelectSouthcity()
{
	switch (hrand(2))
	{
		case 0: 
			pchar.GenQuest.Marginpassenger.Southcity = "Maracaibo";
			pchar.GenQuest.Marginpassenger.Southcity1 = "Havana"; 
		break;
		
		case 1:
			pchar.GenQuest.Marginpassenger.Southcity = "Cartahena";
			pchar.GenQuest.Marginpassenger.Southcity1 = "Santiago"; 
		break;
		
		case 2:
			pchar.GenQuest.Marginpassenger.Southcity = "Portobello";
			pchar.GenQuest.Marginpassenger.Southcity1 = "Santodomingo"; 
		break;
	}
}
