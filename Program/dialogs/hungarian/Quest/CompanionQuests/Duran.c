void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, n;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			dialog.text = "Mit akarsz?";
			link.l1 = "Semmi.";
			link.l1.go = "exit";
		break;
		
		case "SKD_DomAnri":
			dialog.text = "Üdvözletem az otthonomban, uraim. Mit tehetek önökért?";
			link.l1 = "Levasseur üdvözletét küldi, monsieur.";
			link.l1.go = "SKD_DomAnri_2";
			StartQuestMovie(true, false, true);
		break;
		
		case "SKD_DomAnri_2":
			dialog.text = "Szóval így áll a dolog... Alicia! Hagyjon magunkra, kérem. Ezeknek az uraknak dolguk van velem.";
			link.l1 = "";
			link.l1.go = "SKD_DomAnri_2_1";
			CharacterTurnToLoc(npchar, "goto", "goto1");
		break;
		case "SKD_DomAnri_2_1":
			StartInstantDialog("SKD_Alisia", "SKD_DomAnri_3", "Quest\CompanionQuests\Duran.c");
		break;
		
		case "SKD_DomAnri_3":
			dialog.text = "De...";
			link.l1 = "";
			link.l1.go = "SKD_DomAnri_3_1";
			CharacterTurnToLoc(npchar, "barmen", "stay");
		break;
		case "SKD_DomAnri_3_1":
			StartInstantDialog("SKD_Anri", "SKD_DomAnri_4", "Quest\CompanionQuests\Duran.c");
		break;
		
		case "SKD_DomAnri_4":
			dialog.text = "Szeretlek, drágám. Akkor menjetek!";
			link.l1 = "";
			link.l1.go = "SKD_DomAnri_5";
			CharacterTurnToLoc(npchar, "goto", "goto1");
		break;
		
		case "SKD_DomAnri_5":
			DialogExit();
			locCameraFromToPos(3.47, 2.41, 0.10, false, -1.05, 0.20, -0.07);
			
			sld = CharacterFromID("SKD_Anri");
			CharacterTurnByLoc(sld, "barmen", "stay");
			
			sld = CharacterFromID("SKD_Alisia");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload2", "", "", "", "", -1);
			sld.location = "None";
			sld.lifeday = 0;
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("SKD_DomAnri_2", 4.0);
		break;
		
		case "SKD_DomAnri_6":
			dialog.text = "Csodálatos tettek, Uram! Megérte mindent elveszíteni, hogy megtaláld életed szerelmét a világ végén! Uraim, a tiétek vagyok. Gondolom, nem tudunk megegyezni?";
			link.l1 = "";
			link.l1.go = "SKD_DomAnri_6_1";
		break;
		case "SKD_DomAnri_6_1":
			StartInstantDialog("Duran", "SKD_DomAnri_7", "Quest\CompanionQuests\Duran.c");
		break;
		
		case "SKD_DomAnri_7":
			dialog.text = "Nem, és ne is próbálj meg kegyelmet kérni.";
			link.l1 = "";
			link.l1.go = "SKD_DomAnri_7_1";
			CharacterTurnToLoc(npchar, "barmen", "stay");
			locCameraFromToPos(-0.52, 1.47, 0.76, false, -2.52, 0.20, 0.99);
		break;
		case "SKD_DomAnri_7_1":
			StartInstantDialog("SKD_Anri", "SKD_DomAnri_8", "Quest\CompanionQuests\Duran.c");
		break;
		
		case "SKD_DomAnri_8":
			dialog.text = "A Rend lovagjához nem illik kegyelmet kérni.";
			link.l1 = "De egy volt lovagnak igen.";
			link.l1.go = "SKD_DomAnri_9";
		break;
		
		case "SKD_DomAnri_9":
			dialog.text = "A bürokratáknak nem lenne annyi tintájuk, hogy elvegyék tôlem ezt a címet.";
			link.l1 = "Ebben az esetben, bizonyítsa be.  De elôbb elégítse ki a kíváncsiságomat: Ön a korona árulója? Máskülönben nem értem, miért akarta Levasseur annyira az életét.";
			link.l1.go = "SKD_DomAnri_10";
		break;
		
		case "SKD_DomAnri_10":
			dialog.text = "Hûséges vagyok az eskümhöz, uram, úgyhogy ne irigyelje ezt tôlem. Csak annyit mondok, hogy a korona árulója küldött, hogy likvidáljak egy másik árulót. És addig fogja ezt újra és újra megtenni, amíg egy nálam alkalmasabb Testvér nem lesz sikeres. Elég a beszédbôl. Uraim, csatába!";
			link.l1 = "...";
			link.l1.go = "SKD_DomAnri_11";
		break;
		
		case "SKD_DomAnri_11":
			DialogExit();
			EndQuestMovie();
			
			sld = CharacterFromID("Duran");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
			LAi_SetFightMode(pchar, true);
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "SKD_DomAnri_6");
		break;
		
		case "SKD_DomAnri_12":
			dialog.text = "Ah-ah! Ó, köszönöm, kapitány. Kemény ördög volt. Kizárt, hogy én magam legyôztem volna.";
			link.l1 = "Valahogy nem érzem magam túl boldognak a gyôzelem miatt. Gondolom, itt végeztünk?";
			link.l1.go = "SKD_DomAnri_13";
		break;
		
		case "SKD_DomAnri_13":
			dialog.text = "Nem egészen, elôbb ki kell takarítanunk és ki kell iktatnunk a lányt, aki olyan gyorsan felszaladt a második emeletre.";
			link.l1 = "Nem tudtam volna legyôzni ôt. Állj le! Elment az eszed, Claude? Nem vagyok hentes!";
			link.l1.go = "SKD_DomAnri_14";
		break;
		
		case "SKD_DomAnri_14":
			dialog.text = "Nem kell tenned semmit, Cap. Különben is, az egész a te hibád: nem kellett volna megemlítened neki Levasseur-t.";
			link.l1 = "Ez ostobaság, és ezt te is tudod. És ha még egy artikulálatlan dorgálást merészelsz tenni nekem, nem úszod meg.";
			link.l1.go = "SKD_DomAnri_15";
		break;
		
		case "SKD_DomAnri_15":
			dialog.text = "Heh! Az én hibám, kapitány. Igaz, Levasseur parancsa világosan kimondta, hogy nem csak a lovagot, hanem az összes társát is ki kell iktatni. Az összeset, érti? Ezekkel az emberekkel nem lehet viccelni, és a követeléseiket komolyan kell venni. Ne akadályozzon meg a munkámban, kapitány. Még egy utolsó piszkos munka, és akkor a végsôkig veled leszek, esküszöm!";
			if (IsCharacterPerkOn(pchar, "Trustworthy") && sti(pchar.reputation.nobility) > 70)
			{
				notification("Reputáció ellenôrzés átment", "None");
				notification("Megbízható", "Trustworthy");
				link.l1 = "(megbízható) (becsület) Egyszer azt mondtad, hogy arra rendeltettél, hogy magasan repüljek, és te örömmel járultál hozzá ehhez.";
				link.l1.go = "SKD_DomAnri_VD";
			}
			else
			{
				notification("Túl alacsony a hírneve! ("+XI_ConvertString(GetReputationName(71))+")", "None");
				notification("A képességek ellenôrzése sikertelen.", "Trustworthy");
			}
			link.l2 = "A pokolba veled! Végezd el a piszkos munkát. Elfogadom az esküdet, és jobb, ha halálosan komolyan veszed. Megértjük egymást?";
			link.l2.go = "SKD_DomAnri_DuranDruzhba";
			link.l3 = "Ilyen áron nem, Claude. Nem hagyom, hogy megöld azt a lányt.";
			link.l3.go = "SKD_DomAnri_DuranDraka";
		break;
		
		case "SKD_DomAnri_DuranDraka":
			dialog.text = "Heh! Azt hiszem, az volt a sorsunk, hogy megöljük egymást, mi, Cap?";
			link.l1 = "Azt hiszem, igen. Folytassuk ott, ahol Tortugában abbahagytuk, rendben?";
			link.l1.go = "SKD_DomAnri_DuranDraka_2";
		break;
		
		case "SKD_DomAnri_DuranDraka_2":
			DialogExit();
			LAi_SetCurHPMax(npchar);
			LAi_GetCharacterMaxEnergy(npchar);
			
			RemovePassenger(pchar, npchar);
			npchar.SaveItemsForDead = true;
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			
			LAi_SetFightMode(pchar, true);
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "SKD_DomAnri_DuranDraka");
		break;
		
		case "SKD_DomAnri_DuranDruzhba":
			dialog.text = "Igenis, kapitány!";
			link.l1 = "...";
			link.l1.go = "SKD_DomAnri_DuranDruzhba_2";
		break;
		
		case "SKD_DomAnri_DuranDruzhba_2":
			DialogExit();
			
			LocatorReloadEnterDisable("PortRoyal_houseSp1", "reload2", true);
			sld = CharacterFromID("Duran");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload2", "none", "", "", "", -1);
			chrDisableReloadToLocation = false;
			LAi_LocationDisableOfficersGen("PortRoyal_town", true);
			
			PChar.quest.SKD_DomAnri_DuranDruzhba.win_condition.l1 = "location";
			PChar.quest.SKD_DomAnri_DuranDruzhba.win_condition.l1.location = "PortRoyal_town";
			PChar.quest.SKD_DomAnri_DuranDruzhba.win_condition = "SKD_DomAnri_DuranDruzhba";
		break;
		
		case "SKD_DomAnri_DuranDruzhba_3":
			dialog.text = "Megtörtént, Kapitány. Meglepett engem...";
			link.l1 = "Nem akarok hallani róla. Megtartottam a szavam. Most te jössz.";
			link.l1.go = "SKD_DomAnri_DuranDruzhba_4";
		break;
		
		case "SKD_DomAnri_DuranDruzhba_4":
			dialog.text = "Az arany egy dolog, de a saját bôröd kockáztatása egy egyszerû zsoldosért sokkal többet ér. A végsôkig veled vagyok, kapitány.";
			link.l1 = "Ebben az esetben végeztünk.";
			link.l1.go = "SKD_DomAnri_DuranDruzhba_5";
		break;
		
		case "SKD_DomAnri_DuranDruzhba_5":
			dialog.text = "Igenis, uram.";
			link.l1 = "...";
			link.l1.go = "SKD_DomAnri_DuranDruzhba_6";
		break;
		
		case "SKD_DomAnri_DuranDruzhba_6":
			DialogExit();
			
			EndQuestMovie();
			locCameraTarget(PChar);
			locCameraFollow();
			LAi_LocationDisableOfficersGen("PortRoyal_town", false);
			chrDisableReloadToLocation = false;
			AddQuestRecord("TheFormerKnight", "3");
			CloseQuestHeader("TheFormerKnight");
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			
			sld = CharacterFromID("Duran");	//Клод Дюран становится постоянным офицером
			sld.OfficerWantToGo.DontGo = true;
			sld.loyality = MAX_LOYALITY;
			LAi_SetOfficerType(sld);
			sld.Dialog.Filename = "Enc_Officer_dialog.c";
			sld.Dialog.CurrentNode = "hired";
			sld.OfficerImmortal = true;
			sld.Health.HP       = 60.0;
			sld.Health.maxHP    = 60.0;
			SetCharacterPerk(sld, "ShipEscape");
			
			pchar.questTemp.SKD_DuranDruzhba = true;
			pchar.questTemp.SKD_DevushkaUbita = true;
			sld.reputation = sti(sld.reputation) - 15;
			OfficersFollow();
		break;
		
		case "SKD_DomAnri_VD":
			dialog.text = "Igen. Mire akarsz kilyukadni, kapitány?";
			link.l1 = "Bizonyítsa be, hogy azok a szavak nem üres fecsegés voltak. Ki akarsz érdemelni egy helyet a csapatomban? Részesedést a jövôbeni zsákmányból? Kövesd a parancsaimat. Ne nyúlj a lányhoz. Ne nyúlj a lányhoz! Mert ha nem teszed, örökre hentes leszel, és nekem nincs helyem az ilyen embereknek.";
			link.l1.go = "SKD_DomAnri_VD_2";
		break;
		
		case "SKD_DomAnri_VD_2":
			dialog.text = "Ez már a második alkalom, hogy te és én halálos harcot vívunk, Cap\nÉs ismét te nyersz, hála a nyelvvakarás képességének! Ha ha! Te mondtad! Hát, a pokolba a lánnyal. Végül is egy állat vagyok. Engedélyt kérek, hogy csatlakozzak a legénységhez?";
			link.l1 = "Isten hozott, Claude. Ezúttal tényleg.";
			link.l1.go = "SKD_DomAnri_VD_3";
		break;
		
		case "SKD_DomAnri_VD_3":
			dialog.text = "Igenis, kapitány!";
			link.l1 = "...";
			link.l1.go = "SKD_DomAnri_VD_4";
		break;
		
		case "SKD_DomAnri_VD_4":
			DialogExit();
			AddQuestRecord("TheFormerKnight", "2");
			CloseQuestHeader("TheFormerKnight");
			chrDisableReloadToLocation = false;
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			LocatorReloadEnterDisable("PortRoyal_houseSp1", "reload2", true);
			
			sld = CharacterFromID("Duran");	//Клод Дюран становится постоянным офицером
			sld.OfficerWantToGo.DontGo = true;
			sld.loyality = MAX_LOYALITY;
			LAi_SetOfficerType(sld);
			sld.Dialog.Filename = "Enc_Officer_dialog.c";
			sld.Dialog.CurrentNode = "hired";
			sld.OfficerImmortal = true;
			sld.Health.HP       = 60.0;
			sld.Health.maxHP    = 60.0;
			SetCharacterPerk(sld, "ShipEscape");
			
			pchar.questTemp.SKD_DuranDruzhba = true;
			sld.reputation = 60;
			OfficersFollow();
		break;
		
		case "SKD_KlodDuran":
			dialog.text = "Valami közbejött, kapitány.";
			Link.l1 = "Hadd találjam ki: megint felmondással fenyegetôzöl és fizetésemelést követelsz?";
			Link.l1.go = "SKD_KlodDuran_1";
		break;
		
		case "SKD_KlodDuran_1":
			dialog.text = "Heh! Ezúttal nem... Ne aggódjon, kapitány, amíg fizet, addig a magáé vagyok... természetesen az ésszerûség határain belül. Csak így maradnak életben a zsoldos testvéreink. És még a legjobbaknak is csekély fizetést adnak.";
			link.l1 = "Miért nem térünk rögtön az üzletre?";
			link.l1.go = "SKD_KlodDuran_2";
		break;
		
		case "SKD_KlodDuran_2":
			dialog.text = "Emlékszel arra a ribancra Tortugáról?";
			link.l1 = "Marceline? A kormányzó felesége? Egy ilyen nôt nem lehet elfelejteni.";
			link.l1.go = "SKD_KlodDuran_3";
		break;
		
		case "SKD_KlodDuran_3":
			dialog.text = "Nem véletlenül jöttem Levasseur házába. Volt dolgom azzal a gazemberrel és eretnekkel.";
			link.l1 = "Elég furcsa, hogy ilyen becsmérlôen beszélsz a hatalmasokról, Claude.";
			link.l1.go = "SKD_KlodDuran_4";
		break;
		
		case "SKD_KlodDuran_4":
			dialog.text = "Huh? Heh! Levasseur az ördög! Sokkal rosszabb, mint a kalózok, akik belôle táplálkoznak!";
			link.l1 = "Te magad mondtad, hogy üzleteltél vele. Nem képmutató ez egy kicsit?";
			link.l1.go = "SKD_KlodDuran_5";
		break;
		
		case "SKD_KlodDuran_5":
			dialog.text = "Nem vagyok angyal, Cap, és abból élek, hogy megölöm, akit csak akarnak. Ezért értékelsz engem annyira, nem igaz? De még a magamfajta férfiakat is kirázza a hideg a pletykák hallatán, hogy mit mûvelnek a nôkkel Tortugán Levasseur rejtekhelyén!";
			link.l1 = "A pletykák nem érdekelnek. Ez az ember nemesember és a király szolgája, és tiszteletet érdemel.";
			link.l1.go = "SKD_KlodDuran_6";
		break;
		
		case "SKD_KlodDuran_6":
			dialog.text = "Szóval kiraboltad a király szolgáját és megdugtad a feleségét? Heh! Ahogy akarod, kapitány. Térjünk a lényegre. Ôexcellenciája utasított, hogy keressek és öljek meg egy embert. Elég rutinszerû megbízás, még ha nem is gyakran jön ilyen magas rangú személytôl, ráadásul személyesen.";
			link.l1 = "És maga mit akar? Hogy engedjem el, hogy megtartsa a szavát, és megölje ezt az embert?";
			link.l1.go = "SKD_KlodDuran_7";
		break;
		
		case "SKD_KlodDuran_7":
			dialog.text = "Azt akarom, hogy segítsen nekem, kapitány. Amikor a dolgok rosszra fordultak számomra Tortugán, beleegyeztem, hogy csatlakozom a szolgálatodhoz, de nem nyugszom, amíg nem végzek a feladattal. Levasseur megölne, ha megtudná. Mellesleg, szakszerûtlen lenne befejezetlenül hagyni egy munkát.";
			link.l1 = "Az is profi dolog, ha az ügyfél feleségével van viszonya? Nagyon furcsa öntôl ilyen kérést hallani, különösen, ha visszaemlékszünk beszélgetésünk elejére, ahol elég pontosan jellemezte kapcsolatunk lényegét. Vért aranyért, mi?";
			link.l1.go = "SKD_KlodDuran_8";
		break;
		
		case "SKD_KlodDuran_8":
			dialog.text = "Ha segítesz nekem, nem csak a kardomat kapod meg, hanem a hûségemet is. Azonnal látom, hogy magasra hivatott vagy, kapitány. Örömmel segítek, hogy ez megtörténjen.";
			link.l1 = "Bevallom, jobban örülnék, ha egy olyan ember vigyázna rám, mint te. Hol találjuk a célpontját?";
			link.l1.go = "SKD_KlodDuran_10";
			link.l2 = "A szablyád egyelôre elég lesz. Nem vagyok bérgyilkos. Pihenj, tiszt úr!";
			link.l2.go = "SKD_KlodDuran_9";
		break;
		
		case "SKD_KlodDuran_9":
			dialog.text = "Igenis, kapitány. Úgyis megérte megkérdezni.";
			link.l1 = "...";
			link.l1.go = "SKD_KlodDuran_9_1";
		break;
		
		case "SKD_KlodDuran_9_1":
			DialogExit();
			chrDisableReloadToLocation = false;
			npchar.loyality = makeint(npchar.loyality) + 10;
			ReturnOfficer_Duran();
		break;
		
		case "SKD_KlodDuran_10":
			dialog.text = "Heh! Ez a probléma, kapitány. Csak annyit tudok, hogy a Máltai Lovagrend egykori lovagja, aki valahol angol területen menekül. Nemesi származású ember, tehát nem egy viskóban fog élni.";
			link.l1 = "A Máltai Lovagrend lovagja?";
			link.l1.go = "SKD_KlodDuran_11";
		break;
		
		case "SKD_KlodDuran_11":
			dialog.text = "Egy volt lovag. Igen, és már ezerszer megbántam, hogy elvállaltam ezt a munkát. A lovagok úgy harcolnak, mint az ördögök, úgyhogy garantálom, hogy komoly próbatétel lesz a kardforgató képességed.";
			link.l1 = "Nem tetszik, de próbáljuk meg. Tehát: nem szegény ember, nemes és az angoloknál bujkál? Levasseur nem mondta, hogy miért kell vele foglalkozni?";
			link.l1.go = "SKD_KlodDuran_12";
		break;
		
		case "SKD_KlodDuran_12":
			dialog.text = "Persze, hogy nem fog! De nyilván politikai okokból, különben katonákat küldött volna.";
			link.l1 = "Megpróbálom, de nem ígérhetek semmit.";
			link.l1.go = "SKD_KlodDuran_13";
		break;
		
		case "SKD_KlodDuran_13":
			dialog.text = "Köszönöm, kapitány.";
			link.l1 = "...";
			link.l1.go = "SKD_KlodDuran_14";
		break;
		
		case "SKD_KlodDuran_14":
			DialogExit();
			SetQuestHeader("TheFormerKnight");
			AddQuestRecord("TheFormerKnight", "1");
			chrDisableReloadToLocation = false;
			npchar.loyality = makeint(npchar.loyality) + 15;
			ReturnOfficer_Duran();
			PChar.quest.SKD_DomAnri.win_condition.l1 = "location";
			PChar.quest.SKD_DomAnri.win_condition.l1.location = "PortRoyal_houseSp1";
			PChar.quest.SKD_DomAnri.win_condition = "SKD_DomAnri";
			pchar.GenQuestBox.PortRoyal_houseSp1.box1.items.chest = 1;
		break;
		
	}
} 
