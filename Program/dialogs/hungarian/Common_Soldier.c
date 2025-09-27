// boal 25/04/04 общий диалог солдат
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;	

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	int DeceptionChance  = 0;
	int DeceptionPenalty  = 0;
	if(CheckAttribute(pchar,"StealtDeceptionPenalty")) DeceptionPenalty = sti(pchar.StealtDeceptionPenalty);
	
	DeceptionChance = sti(GetSummonSkillFromName(pchar, SKILL_SNEAK)*100/110);
	if(DeceptionChance - DeceptionPenalty > 50) DeceptionChance -= DeceptionPenalty;
	if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE) 
	{
		DeceptionChance = sti(GetSummonSkillFromName(pchar, SKILL_SNEAK)*100/310);
		if(DeceptionChance - DeceptionPenalty > 50) DeceptionChance -= DeceptionPenalty;
	}
	if(sti(pchar.reputation.fame) < 41 && CheckCharacterPerk(pchar, "Trustworthy"))
	{
		DeceptionChance = 100;
		if(DeceptionChance - DeceptionPenalty > 50) DeceptionChance -= DeceptionPenalty;
	}
	if(DeceptionChance > 90) DeceptionChance = 90;
	// belamour legendary edition в квестах не используется, да, и лишний раз игроков не нужно заставлять по кейсам бегать. Квесты пишите в коммоне
    /* // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Soldier\" + NPChar.City + "_Soldier.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <-- */
    int iTest, iTemp;
	string sTemp;
    iTest = FindColony(NPChar.City); // город
    ref rColony;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			sTemp = npchar.location;
			if (findsubstr(sTemp, "_townhall" , 0) != -1) AddDialogExitQuest("MainHeroFightModeOff");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "First time":			
            NextDiag.TempNode = "First time";
			if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
			{
				// заглушка на пирата
				if (sti(pchar.nation) == PIRATE)
				{
    				dialog.text = RandPhraseSimple("Kalózok a városban?! Nem hiszem el... Elfogni "+ GetSexPhrase("ôt","ôt") +"!!!", "Ez egy kalóz! Elfoglalni "+ GetSexPhrase("ôt","ôt") +"!!!");
					link.l1 = RandPhraseSimple("Kalóz vagyok, és akkor mi van?", "Heh, megpróbálhatod...");
					link.l1.go = "fight"; 
					break;
				}
				else
				{
					if (DeceptionChance > (10+rand(150)+rand(150)))
					{
						dialog.text = RandPhraseSimple("Ki vagy te, és mit keresel itt?", "Állj meg ott! Ki vagy te és milyen jogon próbálsz bejönni a városba?");
						link.l2 = "Horgonyt vetettem a " + XI_ConvertString(GetIslandByCityName(npchar.city)+"Gen") + " közelében a " + NationNameGenitive(sti(npchar.nation)) + "zászló alatt. Mit nem értesz?(A megtévesztés valószínûsége "+DeceptionChance+"%%)";
						link.l1.go = "NotPegYou";
					}
					else
					{
						dialog.text = RandPhraseSimple("Egy kém! Add le a fegyvered és kövess engem!", "Egy ellenséges ügynök! Elfogni "+ GetSexPhrase("ôt","ôt") +"!");
						link.l1 = RandPhraseSimple("Pofa be, puhány!", "Baszd meg!");
						link.l1.go = "fight"; 
					}
				}
			}
			else
			{
				// eddy. проверяем, не казачок ли. -->
				if (GetNationRelation(sti(NPChar.nation), GetBaseHeroNation()) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
				{
					// грамота Винсенто
					if(CheckAttribute(pchar, "questTemp.Guardoftruth") && CheckCharacterItem(pchar, "VerifyPaper") && npchar.city == "santiago")
					{
						dialog.text = RandPhraseSimple("Ki vagy te, és mit keresel itt?", "Állj meg ott! Ki vagy te, és milyen jogon akarsz bejönni a városba?");
						link.l1 = "Nézd ezt a papírt, katona. Az inkvizítor, Vincento atya engedélyével vagyok itt.";
						link.l1.go = "vincento"; 
						break;
					}
					if(CheckAttribute(pchar, "questTemp.Guardoftruth.Trinidad") && CheckCharacterItem(pchar, "VerifyPaper") && npchar.city == "portspein")
					{
						dialog.text = RandPhraseSimple("Ki vagy te, és mit keresel itt?", "Állj meg ott! Ki vagy te és milyen jogon próbálsz bejönni a városba?");
						link.l1 = "Nézd ezt a papírt, katona. Az inkvizítor, Vincento atya engedélyével vagyok itt.";
						link.l1.go = "vincento"; 
						break;
					}
					if (PChar.location == "Maracaibo_Plantation")
					{
						dialog.text = LinkRandPhrase("Viselkedjetek, és ne zavarjátok a rabszolgákat.", "Gyerünk, mozgás!", "Á, te vagy az. Menj csak, már tájékoztattak minket rólad.");
						link.l1 = "...";
						link.l1.go = "exit";
						break;
					}
					dialog.text = RandPhraseSimple("Ki vagy te, és mit keresel itt?", "Állj meg ott! Ki vagy te és milyen jogon próbálsz bejönni a városba?");
					//==> по лицензии
					if (CheckNationLicence(HOLLAND))
					{
						link.l1 = "Biztos úr, nekem van " + GetRusNameNationLicence(HOLLAND) + ", tehát jogi alapon vagyok itt. Tessék, kérem, nézze meg...";
						link.l1.go = "LicenceOk";
						if (findsubstr(pchar.location.from_sea, "_town" , 0) != -1) //если причалил в городе
						{
							link.l2 = "Nem látjátok a " + NationNameGenitive(sti(pchar.nation)) + "zászlót a hajóm árbocán?! (A megtévesztés valószínûsége "+DeceptionChance+"%%)";
						}
						else //если причалил не в городе
						{
							link.l2 = "Horgonyt vetettem a " + XI_ConvertString(GetIslandByCityName(npchar.city)+"Gen") + " közelében a " + NationNameGenitive(sti(pchar.nation)) + "zászló alatt. Mit nem értesz? (Tévesztés valószínûsége "+DeceptionChance+"%%)";
						}
						if (DeceptionChance < (10+rand(50)+rand(50)))
						{
							link.l2.go = "PegYou";
						}
						else
						{
							link.l2.go = "NotPegYou";
						}
					}
					else
					{
						//==> по флагу
						// заглушка на пирата
						if (sti(pchar.nation) == PIRATE)
						{
    						dialog.text = RandPhraseSimple("Kalózok a városban?! Nem hiszem el... Fogjátok el!", "Ez egy kalóz! Fogjátok el!");
							link.l1 = RandPhraseSimple("Igen, kalóz vagyok - és most mi lesz?", "Heh, kapj el, ha tudsz...");
							link.l1.go = "fight"; 
							break;
						}
						if (findsubstr(pchar.location.from_sea, "_town" , 0) != -1) //если причалил в городе
						{
							link.l1 = "Nem látjátok a " + NationNameGenitive(sti(pchar.nation)) + " zászlót a hajón?! (A megtévesztés valószínûsége "+DeceptionChance+"%%)";
						}
						else //если причалил не в городе
						{
							link.l1 = "Horgonyt vetettem a " + XI_ConvertString(GetIslandByCityName(npchar.city)+"Gen") + " közelében a " + NationNameGenitive(sti(pchar.nation)) + "zászló alatt. Mit nem értesz? (A megtévesztés valószínûsége "+DeceptionChance+"%%)";
						}
						if (DeceptionChance < (10+rand(50)+rand(50)))
						{
							link.l1.go = "PegYou";
						}
						else
						{
							link.l1.go = "NotPegYou";
						}
					}
				}
				// <-- eddy. проверяем, не казачок ли.
				else
				{
					if (sti(NPChar.nation) == PIRATE)
					{
						if (sti(rColony.HeroOwn) == true) // наш горожанин
						{
			         		switch (rand(10))
							{
								case 0:
									dialog.text = "Ó, kapitány, olyan jól éreztük magunkat veled a tengeren! Annyi hajót süllyesztettünk el együtt a parancsnokságod alatt! És itt...";
									link.l1 = "És itt, barátom, bájos hölgyeken gyönyörködhetsz, a tengeren nem fogod látni ôket.";
									link.l1.go = "exit";
								break;

								case 1:
									dialog.text = "Kapitány, mivel érdemeltük ezt ki?! Nem vagyunk szárazföldi patkányok, ugye?";
									link.l1 = "Csendet, tengerész! A posztja nagyon fontos és tiszteletbeli, úgyhogy hagyja abba a nyafogást.";
									link.l1.go = "exit";
								break;

								case 2:
									dialog.text = "Mi folyik a tengeren, kapitány? Látjuk még valaha?";
									link.l1 = "Hát persze, tengerész! Amint felmentik a szolgálat alól, mehet a mólóra, és élvezheti a tengert, amennyire csak akarja.";
									link.l1.go = "exit";
								break;

								case 3:
									dialog.text = "Panaszkodni szeretnék, kapitány úr: mindannyiunknak hiányzik a tenger. Mindannyiunknak teljesen elege van ebbôl a szárazföldi szolgálatból!";
									link.l1 = "Már belefáradtam ebbe a nyafogásba! Van itt is elég rum! Szolgáljatok ott, ahová a kapitány úr helyezett benneteket, különben valakit felakasztanak, hogy példát statuáljanak a többieknek.";
									link.l1.go = "exit";
								break;

								case 4:
									dialog.text = "Megmondom neked bizalmasan, kapitány, az új kormányzó egy vesztegetô és sikkasztó. De ez igazán nem az én dolgom...";
									link.l1 = "Pontosan, Kormányzó. A te dolgod az, hogy a helyeden állj és vigyázz a rendre. És a kormányzó felakasztása az én dolgom. Szép munka!";
									link.l1.go = "exit";
								break;

								case 5:
									dialog.text = "Köszönjük, hogy nem feledkezett meg rólunk, kapitány! Tûzön-vízen át is követnénk!";
									link.l1 = "Ismerem a fajtátokat, gazemberek! Ti csak az aranyat szeretitek. Ma este buli lesz a kocsmában, az italokat én állom. Ne felejtsetek el megjelenni.";
									link.l1.go = "exit";
								break;

								case 6:
									dialog.text = "Heh, kapitány! Gondolj csak bele, lehet egy korzsair tényleg a rend ôre?! Olyan régen volt már, hogy utoljára az igazi üzletben voltunk!";
									link.l1 = "Nincs idô a lazításra, korzír! Ellenséges armadák söpörnek a szigeteinkhez közeli vizeken, és bármikor készen kell állnunk egy vérfürdôre.";
									link.l1.go = "exit";
								break;

								case 7:
									dialog.text = "Kapitány, úgy hallottam, hogy a Korona egy másik századot küldött felénk?";
									link.l1 = "Természetesen, korzsair. Amíg mi élünk, nem lesz béke számunkra. És még a pokolban is ördögökkel fogunk harcolni!";
									link.l1.go = "exit";
								break;

								case 8:
									dialog.text = "Yo-ho-ho! A fenébe, ez aztán a tegnapi erôs pia volt, kapitány! Kár, hogy nem voltál ott.";
									link.l1 = "Nem nagy ügy, majd pótolom. És nem irigyellek titeket, srácok.";
									link.l1.go = "exit";
								break;

								case 9:
									dialog.text = "Megmondom neked bizalmasan, kapitány, 'mert mindig jól bántál velünk, tegnap egy nagyon kedves csajjal jól éreztük magunkat...";
									link.l1 = "Heh, kalóz, egy hurokra tényleg szükséged van!";
									link.l1.go = "exit";
								break;

								case 10:
									dialog.text = "Kapitány! Kérem, mentsen fel ettôl az átkozott kötelességtôl! Egyszerûen nem tudom tovább játszani a rendfenntartó szerepét.";
									link.l1 = "Az éjszakai ôrség egy hajón sem könnyû. Barátom, a kötelesség az kötelesség, bármi és bárhol is legyen az.";
									link.l1.go = "exit";
								break;
							}
							// belamour legendary edition в квестах не используется, да, и лишний раз игроков не нужно заставлять по кейсам бегать. Квесты пишите в коммоне
							/* link.l2 = RandPhraseSimple("Van fontos dolog!", "Van egy ügyem a számodra.");
							link.l2.go = "quests";//(перессылка в файл города) */
							break;
						}
						else
						{ // пираты, не наши
							if (sti(pchar.GenQuest.Piratekill) > 20)
							{
								dialog.text = RandPhraseSimple("Riadó! Fegyveres beteg pszichopata van itt!", "Fegyverbe, fegyverbe! Valami ôrült fattyú van itt!");
								link.l1 = RandPhraseSimple("Huh? Mi az?", "Uh, miért csinálod ezt?");
								link.l1.go = "pirate_fight";
							}
							else
							{
							    /* dialog.text = LinkRandPhrase(RandPhraseSimple("Van valami dolga velem, kapitány?", "Üzleti úton vagyok, ha kell valami - kérdezzen, nem késlekedik."), RandPhraseSimple("Kapitány úr, nagyon elfoglalt vagyok, így hogy keressen más beszélgetôpartnert.", "Valami nem így, kapitány úr? Ha nincs kérdés, akkor engedjen át."), "Utat, kapitány úr, sietek.");
							link.l1 = LinkRandPhrase("Bocs haver, én "+ GetSexPhrase("kaptam","kaptam") +" ", "OK, csináld a saját dolgod.", "Nem, semmi.");
							link.l1.go = "exit";
							link.l2 = LinkRandPhrase(RandPhraseSimple("Van egy ügyem a számodra.", "Van egy ügyem a számodra."), RandPhraseSimple("Látom, sietsz. Egy kérdés és szabad lesz.", "Én "+ GetSexPhrase("akartam","akartam") +" kérdezni valamit."), "az üzleted várhat. Ezt kérdezem "+ GetSexPhrase("akartam","akartam") +".");
							    link.l2.go = "quests";//(перессылка в файл города) */
								
								//Экку Korsar - что-то они больно вежливые для пиратов были...
								dialog.text = RandPhraseSimple("Mit akarsz? Menj el.", "Ne állja el az utat, álljon hátrébb.");
					            link.l1 = RandPhraseSimple("Tudod? Ne ugass!", "Csökkentsd a buzgalmadat. Nem fogom gyorsan lehûteni!");
					            link.l1.go = "exit";
						    	/* link.l2 = LinkRandPhrase(RandPhraseSimple("Van egy ügyem a számodra.", "Van egy ügyem a számodra."), RandPhraseSimple("Látom, sietsz. Egy kérdés és szabad lesz.", "Én "+ GetSexPhrase("akartam","akartam") +" kérdezni valamit."), "az üzleted várhat. Ezt kérdezem "+ GetSexPhrase("akartam","akartam") +".");
							link.l2.go = "quests";//(перессылка в файл города) */
							}
							break;
						}
					}
					else
					{ //если негодяй, имеющий НЗГ к дружественной или нейтральной нации
						if (ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 0) <= -15)
						{
							dialog.text = RandPhraseSimple("Csak nézd meg  "+ GetSexPhrase("ezt a gazembert! Meg merte mutatni az arcát","annak a gazembernek! Meg merte mutatni az arcát") +" a " + XI_ConvertString("Colony" + npchar.city)+ ". Ragadja meg "+ GetSexPhrase("ôt","ôt") +"!!!", "Ha, felismertelek, "+ GetSexPhrase("gazember","gazember") +"! Fogjátok meg "+ GetSexPhrase("ôt","ôt") +"!!!");
							link.l1 = RandPhraseSimple("Argh!...", "Nos, te kérted...");
							link.l1.go = "fight";
							break;						
						}
					}

					// --> девица в джунглях
					if(rand(2) == 1 && CheckAttribute(pchar,"GenQuest.EncGirl") && CheckAttribute(pchar,"GenQuest.EncGirl.MeetSoldiers"))
					{
						if(sti(pchar.GenQuest.EncGirl.MeetSoldiers) == 1)	
						{
							dialog.text = "Nézd csak, ki van ott! Maga Lady " + pchar.GenQuest.EncGirl.name + " tisztelt meg minket a jelenlétével! Vajon hogy merészelted? Már kerestünk téged! Kérem, menjen a tömlöcbe - a cellája készen áll és várja önt. ";
							link.l1 = "Micsoda marhaságot beszélsz!? Én és az én "+ GetSexPhrase("cavalier","társam") +" a dzsungelben sétáltunk, virágot szedtünk. Hagyjatok békén! Hol van ezeknek a mardekárosoknak a jó modora?! Amint meglátnak egy vonzó lányt, rögtön nyaggatni kezdik! "+ GetSexPhrase("Kedvesem, kérlek, mondd meg ezeknek a tökfejeknek, hogy tûnjenek el, és hagyjanak békén egy becsületes nôt!","Drágám, kérlek, mondd meg azoknak a tökfejeknek...") +"!";
							link.l1.go = "GirlEnc_1";
						}
						if(sti(pchar.GenQuest.EncGirl.MeetSoldiers) == 2)	
						{
							dialog.text = "Ó, hát itt vagy, szépségem! Apád az egész helyôrséget felhívatta, hogy megtaláljanak és hazahozzanak.";
							link.l1 = "Tûnjetek el! Tudom, hová megyek, és nincs szükségem a segítségedre! Kapitány, mondja meg nekik, hogy vegyék le rólam a kezüket.";
							link.l1.go = "GirlEnc_2";						
						}
						DeleteAttribute(pchar,"GenQuest.EncGirl.MeetSoldiers");
					}
					// <-- девица в джунглях

					// --> belamour ночной приключенец
					if(CheckAttribute(pchar,"GenQuest.NightAdventureSolNum") && npchar.index == pchar.GenQuest.NightAdventureSolNum)
					{
						dialog.text = "Egy katona élete menetrendszerû - ôrségben áll, járôrözik ... Mit akarsz, "+ GetAddress_Form(NPChar) + "?";
						link.l1 = "Figyelj, veled verekedett itt nemrég egy részeges? Nos, bár, úgy tûnik, igen, veled...";
						link.l1.go = "NightAdventure_CitizenHomieSolder";
						break;
					}
					// <-- ночной приключенец
					
					//belamour legendary edition диалоги, если герой имеет звания и заслуги перед отечеством -->
					
					// Шарль де Мор генерал-губернатор французских колоний
					if(CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE)
					{
						switch(rand(2))
						{
							case 0: 
							dialog.text = "Ôexcellenciája, fôkormányzó úr! Hogy szolgálhatok?";
							link.l1 = "Nincs szükségem semmire, köszönöm.";
							link.l1.go = "exit";
							break;

							case 1:
								dialog.text = "Ez nagy megtiszteltetés számomra, fôkormányzó úr! Miben segíthetek?";
								link.l1 = "Végezze lelkiismeretesen a szolgálatát - ennél többet nem kérek Öntôl.";
								link.l1.go = "exit";
							break;

							case 2: 
								dialog.text = "Örülök, hogy látom, excellenciás uram! Mit tehet egy szerény katona a gyarmataink fôkormányzójának?";
								link.l1 = "Személy szerint nincs szükségem önre. Szolgáljon csak tovább.";
								link.l1.go = "exit";
							break;
						}
						break;
					}
					// Вице-адмирал на службе нации узнается без мундира
					if(isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation))
					{
						switch(rand(2))
						{
							case 0: 
							dialog.text = "Admirális-helyettes, excellenciás uram! Engedje meg, hogy jelentse: az ôrségem alatt...";
							link.l1 = "Nyugodjon meg, katona, nincs szükségem a jelentésére. Jelentkezzen a tisztjénél.";
							link.l1.go = "exit";
							break;

							case 1:
								dialog.text = "Örülök, hogy látom, admirális-helyettes! Segíthetek valamiben?";
								link.l1 = "Nem, csak ellenôriztem, mennyire figyelmes. Örülök, hogy felismert.";
								link.l1.go = "exit";
							break;

							case 2: 
								dialog.text = "Admirális-helyettes úr, ez megtiszteltetés számomra! Mit tehetek önért?";
								link.l1 = "Szolgáld ki " + NationNameGenitive(sti(npchar.nation)) + ", katona! Ez a legjobb dolog, amit tehetsz.";
								link.l1.go = "exit";
							break;
						}
						break;
					}
					// Офицер с патентом
					if(IsOfficerFullEquip() && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation))
					{
						switch(rand(2))
						{
							case 0: 
							dialog.text = "Üdvözletem, kapitány! Ha bármilyen utasítása van számomra, akkor elnézését kérem: bár a " + NationNameGenitive(sti(npchar.nation)) + "szolgálatában állok, csak a parancsnoknak és a kormányzónak tartozom felelôsséggel."; 
							link.l1 = "A tisztjeim és a legénységem az én vezetésemnek tartozik felelôsséggel. Tegye a kötelességét, katona.";
							link.l1.go = "exit";
							break;

							case 1:
								dialog.text = "Kapitány, elvinne engem, hogy a hajóján szolgáljak? Ugyanaz a szolgálat a " + NationNameGenitive(sti(npchar.nation)) + ", de én jobban szeretem a tengert."; 
								link.l1 = "Szükség van rád ott, ahová kijelöltek, úgyhogy végezd a szolgálatodat becsülettel. Csukd be a szemed egy pillanatra, és elvisznek a tengerre.";
								link.l1.go = "exit";
							break;

							case 2: 
								dialog.text = "Ó, szerencséd van: te vagy a hajó kapitánya a " + NationNameGenitive(sti(npchar.nation)) + "szolgálatában álló ... Én meg itt ragadtam egész nap."; 
								link.l1 = "Azt hiszed, csak úgy megérkeztem a Karib-tengerre, és egy héttel késôbb lettem kapitány? Ez mind évek kemény munkája...";
								link.l1.go = "exit";
							break;
						}
						break;
					}
					// <-- legendary edition
					switch (rand(10))
					{
						case 0: ////////////////////////////////////////
							dialog.text = "Hát nem érted? Szolgálatban vagyok. Ne zavarj!";
							link.l1 = "Jól van, jól van...";
							link.l1.go = "exit";
						break;

						case 1:
							dialog.text = "Valami gyanús tevékenységrôl akarsz beszélni nekem?";
							link.l1 = "Nem, egyáltalán nem, és egyébként is kapitány vagyok. Látom, már nem figyelsz rám. Viszlát. Viszlát.";
							link.l1.go = "exit";
						break;

						case 2: ///////////////////////////////////////////
							dialog.text = "Ez egy katonai létesítmény, úgyhogy ne csapjon túl nagy zajt.";
							link.l1 = "Rendben, ezt észben tartom.";
							link.l1.go = "exit";
						break;

						case 3:
							dialog.text = "Ilyen szép idôben, és nekem itt kell állnom. A városban legalább vannak lányok, és mi van itt? Csak patkányok vannak itt.";
							link.l1 = ""+ GetSexPhrase("Együttérzek, de nem tudok segíteni - végül is ez a kötelességed.","Hé! Mi a baj velem? Nem vagyok lány?") +"";
							link.l1.go = "exit";
						break;

						case 4: ///////////////////////////////////////////
							dialog.text = "Ha szeretsz beszélgetni, keress valaki mást. Nekem itt rendet kell tartanom, és nincs idôm olcsó beszédre.";
							link.l1 = "Ó, nem, csak ellenôrzöm, hogy életben vagy-e még. Úgy álltál, mint egy szobor.";
							link.l1.go = "exit";
						break;

						case 5: ////////////////////////////////////////////
							dialog.text = "Valószínûleg azt hiszed, hogy a helyôrségi munkanapok sétagaloppok? Egyáltalán nem! Ez egy kemény és fontos munka. Emlékszem, egyszer... ";
							link.l1 = "Ezt a történetet majd máskor meséli el nekem. Most egy kicsit sietek.";
							link.l1.go = "exit";
						break;

						case 6: ////////////////////////////////////////////
							dialog.text = "Óvatosan, egy erôdben vagy! Légy csendben, mint egy egér!";
							link.l1 = "Ahogy mondod, katona.";
							link.l1.go = "exit";
						break;

						case 7:
							dialog.text = "Hé! Van véletlenül egy kis víz? Szomjan halok.";
							link.l1 = "Nem, barátom, legyen türelmes...";
							link.l1.go = "exit";
						break;

						case 8://///////////////////////////////////////////
							dialog.text = "Milyen unalmas a helyôrségi élet, csak ilyen parasztok vannak körülötted! A városi helyôrségben biztosan jobb idôk járnak...";
							link.l1 = "És ezt nevezed te 'ügyeletnek'? Így biztos, hogy egy kém elszökik melletted!";
							link.l1.go = "exit";
						break;

						case 9://///////////////////////////////////////////
							dialog.text = ""+ GetSexPhrase("Erôs fickónak tûnsz, nem igaz? Szeretnél jelentkezni az erôd helyôrségébe? Tágas barakkjaink vannak, napi kétszeri étkezés és ingyen pia.","Ó, ifjú hölgy, el sem tudja képzelni, milyen kellemes egy ilyen kedves leánykával találkozni ebben a túlvilági hátországban!") +"";
							link.l1 = ""+ GetSexPhrase("Ez kétségtelenül csábító, de mégis vissza kell utasítanom. Ez a sok laktanyai gyakorlat nem nekem való.","Köszönöm a bókot, katona.") +".";
							link.l1.go = "exit";
						break;

						case 10:
							dialog.text = "Ez az istenverte hôség... Boldogan lemondanék a fél életemrôl, hogy visszamehessek Európába.";
							link.l1 = "Igen, látom, hogy az egészséged nem alkalmas a helyi éghajlatra.";
							link.l1.go = "exit";
						break;

					}
					// belamour legendary edition в квестах не используется, да, и лишний раз игроков не нужно заставлять по кейсам бегать. Квесты пишите в коммоне
					/* link.l3 = "Минуту. Я вот что спросить "+ GetSexPhrase("хотел","хотела") +"...";
					link.l3.go = "quests";//(перессылка в файл города) */				
				}
			}
		break;
		//============================== ноды на разборки при распознавании =========================
		case "PegYou":
			dialog.text = RandPhraseSimple("Nekem úgy tûnik, hogy ez valami trükk. Beszéljünk a parancsnokkal, "+ GetSexPhrase("pajtás","drága") +", és derítsük ki az egészet...", "Hmm... Valami azt súgja, hogy nem az vagy, akinek kiadod magad... Add le a fegyvered " + GetAddress_Form(npchar) + ", és kövess engem a további nyomozáshoz!");
			link.l1 = RandPhraseSimple("Cseszd meg!", "Amikor két vasárnap jön egy héten...");
			link.l1.go = "fight";
			if (!CheckAttribute(pchar,"questTemp.stels.landSolder") || sti(pchar.questTemp.stels.landSolder) != GetDataDay())
			{
				AddCharacterExpToSkill(pchar, SKILL_SNEAK, 40);
				pchar.questTemp.stels.landSolder = GetDataDay();
			}
		break;
		
		case "NotPegYou":
			dialog.text = RandPhraseSimple("Ó, értem... Úgy tûnik, minden rendben van, szabadon távozhat, " + GetAddress_Form(pchar) + ".", "Egy kicsit elfáradhattam az ôrségben... Úgy tûnik, minden rendben van, " + GetAddress_Form(pchar) + ", sajnálom.");
			link.l1 = "Semmi gond!";
			link.l1.go = "exit";
			if (!CheckAttribute(pchar,"questTemp.stels.landSolder") || sti(pchar.questTemp.stels.landSolder) != GetDataDay())
			{
				AddCharacterExpToSkill(pchar, SKILL_SNEAK, 80);
				pchar.questTemp.stels.landSolder = GetDataDay();
			}
		break;
		
		case "vincento":
			dialog.text = RandPhraseSimple("Ó, értem... Úgy tûnik, minden rendben van, szabadon távozhat, " + GetAddress_Form(pchar) + ".", "Lássuk csak... Nos, úgy tûnik, minden rendben van, " + GetAddress_Form(pchar) + ", sajnálom.");
			link.l1 = "Ez majd megtanít téged!";
			link.l1.go = "exit";
		break;
		
		case "LicenceOk":
			iTemp = GetDaysContinueNationLicence(HOLLAND);
			if (ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 0) <= -12)
			{
				dialog.text = "Most jut eszembe! Micsoda szemtelenség! Idejönni egy kereskedô álcája alatt! A képeid minden barakkban ki vannak függesztve, te szemétláda! Ezúttal nem úszod meg! Fogjátok el!";
				link.l1 = RandPhraseSimple("Arrgh!...", "Nos, te akartad...");
				link.l1.go = "fight";	
				TakeNationLicence(HOLLAND);
				break;
			}
			if (pchar.location != "LosTeques_town" && findsubstr(pchar.location.from_sea, "_town" , 0) == -1) //если причалил не в городе 300912
			{
				dialog.text = "Ide jöttél kereskedni? Megkérdezhetem, hogyan? Hol van a hajód? Tudod, ez az egész nagyon gyanúsnak tûnik, és kénytelen vagyok itt tartani téged, amíg ki nem derítjük az egészet. Adja át a fegyverét és kövessen!";
				link.l1 = RandPhraseSimple("Baszd meg!", "Amikor két vasárnap jön egy héten...");
				link.l1.go = "fight";	
				TakeNationLicence(HOLLAND);
				break;
			}
			if (iTemp == -1)
			{
				dialog.text = "Az engedélyét be kell vonni, mivel lejárt, és emiatt nem érvényes. Adja le a fegyverét és kövessen a további nyomozáshoz!";
				link.l1 = RandPhraseSimple("Cseszd meg!", "Amikor két vasárnap jön egy héten...");
				link.l1.go = "fight";	
				TakeNationLicence(HOLLAND);
				break;
			}
			if (iTemp == 0)
			{
				dialog.text = "Hmm... Minden rendben van. Mégis, meg kell jegyeznem, hogy a jogosítványa ma lejár. Ezúttal átengedem, de akkor is új engedélyt kell szereznie.";
				link.l1 = "Köszönöm, a lehetô leghamarabb szerzek egy újat.";
				link.l1.go = "exit";			
			}
			if (iTemp > 0 && iTemp <= 10)
			{
				dialog.text = "Hmm... Minden rendben van. Mégis, meg kell jegyeznem, hogy az engedélye hamarosan lejár. Még mindig csak a " + FindRussianDaysString(iTemp) + ". Szóval ezt tartsa észben, " + GetAddress_Form(npchar) + ".";
				link.l1 = "Köszönöm, a lehetô leghamarabb szerzek egy újat.";
				link.l1.go = "exit";			
			}
			if (iTemp > 10)
			{
				dialog.text = LinkRandPhrase("Nos, minden rendben van. Az Ön engedélye még egy " + FindRussianDaysString(iTemp) + ". Átmehet.", "Minden tiszta, "+GetAddress_Form(npchar)+". Szabadon járhatsz ki és be a városba, a jogosítványod még egy " + FindRussianDaysString(iTemp) + "évig érvényes. Elnézést a zavarásért.", "Minden rendben van, " + GetAddress_Form(npchar) + ", nem tartom tovább itt.");
				link.l1 = RandPhraseSimple("Kiváló. Üdvözlettel.", "Köszönöm, biztos úr.");
				link.l1.go = "exit";
			}
		break;
		//============================== ноды маяка Порт Рояля =========================
		case "PortRoyal_Mayak":
			dialog.text = RandPhraseSimple("Hé, haver, ne törj össze semmit a világítótoronyban.", "Ez a világítótorony egy nagyon fontos városi objektum. Légy óvatos!");
			link.l1 = RandPhraseSimple("Rendben, ne aggódj.", "Rendben, ne aggódj.");
			link.l1.go = "exit";
			NextDiag.TempNode = "PortRoyal_Mayak";
		break;
		case "PortRoyal_Gans":
			dialog.text = LinkRandPhrase("Ne menjen az ágyúk közelébe - ez egy katonai létesítmény!", "Idegenek nem mehetnek az ágyúk közelébe!", "Ha észreveszem, hogy az ágyúk közelében lézengsz, véged van!");
			link.l1 = RandPhraseSimple("Megvan.", "Rendben, megvan.");
			link.l1.go = "exit";
			NextDiag.TempNode = "PortRoyal_Gans";
		break;

		// --> генератор "A damsel in the jungle"
		case "GirlEnc_1":
			dialog.text = "És ki vagy te, kapitány? Nem vagy véletlenül a település leghírhedtebb tolvajának a bûntársa?";
			link.l1 = "Kit nevezett az elôbb bûntársnak?! Megôrültél a napszúrástól, vagy mi?! Hé, vedd el a mancsodat a lánytól!";
			link.l1.go = "GirlEnc_11";
			link.l2 = "Tulajdonképpen én "+ GetSexPhrase("megismertem ôt","megismertem ôt") +" nemrég...";
			link.l2.go = "GirlEnc_12";
		break;

		case "GirlEnc_11":
			dialog.text = ""+ GetSexPhrase("Uram","Miss") +", parancsunk van arra, hogy ôrizetbe vegyük és a tömlöcbe vigyük. És ha azt hiszi, hogy megállíthat minket, akkor téved.";
			link.l1 = "Lássuk csak...";
			link.l1.go = "GirlEnc_11End";
		break;

		case "GirlEnc_11End":
			DialogExit();
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			sld = CharacterFromID("CangGirl");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1.0);
			sld.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");		
		break;
		
		case "GirlEnc_12":
			dialog.text = "Ó, tényleg? Ebben az esetben azt tanácsolnám, hogy nézze meg a zsebeit. Az a hölgy egy profi, tudja.";
			link.l1 = "Köszönöm, úgy lesz. Hogy csinálhattam ekkora hülyét magamból...";
			link.l1.go = "GirlEnc_12End";		
		break;		
		
		case "GirlEnc_12End":
			pchar.money = sti(pchar.money) - makeint(sti(pchar.money)/20);
			NextDiag.CurrentNode = NextDiag.TempNode;
			sld = CharacterFromID("CangGirl");
			LAi_SetActorType(sld);
			LAi_ActorStay(sld);
			LAi_CharacterDisableDialog(sld);
			sld.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
		break;
		
		case "GirlEnc_2":
			dialog.text = ""+ GetSexPhrase("Uram","Miss") +", parancsunk van, hogy keressük meg azt a hölgyet, és vigyük az apjához.";
			link.l1 = "Nos, a parancs az parancs... Akkor rajta!";
			link.l1.go = "GirlEnc_2End";
			link.l2 = "Túl késô, mert már az apjához viszem.";
			link.l2.go = "GirlEnc_21";
		break;
		
		case "GirlEnc_2End":
			NextDiag.CurrentNode = NextDiag.TempNode;
			sld = CharacterFromID("CangGirl");
			LAi_SetActorType(sld);
			LAi_ActorStay(sld);
			LAi_CharacterDisableDialog(sld);
			sld.lifeDay = 0;	
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			AddQuestRecord("JungleGirl", "11");	
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));	
			CloseQuestHeader("JungleGirl");
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();			
		break;
		
		case "GirlEnc_21":
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
			if(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < rand(100))
			{
				dialog.text = "Kapitány, parancsunk van, és ha azt hiszi, hogy megállíthat minket, akkor téved.";
				link.l1 = "Lássuk csak...";
				link.l1.go = "GirlEnc_21End";
			}
			else
			{
				dialog.text = "Heh, "+ GetSexPhrase("szerencsés ember vagy","szerencsés lány vagy") +". Az apja bôkezû jutalmat ígért annak, aki visszahozza hozzá.";
				link.l1 = "Ne ess kétségbe - még sok jutalom vár rád.";
				link.l1.go = "exit";			 
			}
		break;
		
		case "GirlEnc_21End":
			DialogExit();
			AddQuestRecord("JungleGirl", "12");
			AddQuestUserData("JungleGirl","sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city));
			CloseQuestHeader("JungleGirl");
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			sld = CharacterFromID("CangGirl");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1.0);
			sld.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");				
		break;
		// <-- генератор "A damsel in the jungle"
		// --> belamour ночной приключенец
		case "NightAdventure_CitizenHomieSolder":
			dialog.text = "Igen, velem. Hadd üljön rács mögött, gondolkodjon el a viselkedésén. És ha azért jöttél, hogy megfenyegess érte, akkor higgy nekem: Még az erôd parancsnokát is el tudom érni.";
			link.l1 = "Igen, nem fenyegetôzni jöttem, hanem megkérni, hogy vonja vissza a követeléseit. Tudja, ô egy régi ismerôsöm, csak berúgott, de egy részegnek, tudja, térdig ér a tenger ...";
			link.l1.go = "NightAdventure_CitizenHomieSolder_1";
		break;
		
		case "NightAdventure_CitizenHomieSolder_1":
			dialog.text = "Vagyis, hogy szolgálat közben monoklit adott nekem, és most engedjék el? Miért történt ez?";
			link.l1 = "Mit szólna ötszáz pezóhoz bocsánatkérésként a viselkedéséért?";
			link.l1.go = "NightAdventure_CitizenHomieSolder_2";
		break;
		
		case "NightAdventure_CitizenHomieSolder_2":
			dialog.text = "Gondolod, hogy így van? Megsértette a becsületemet, és azt hiszi, hogy ezt ötszáz pezóért meg lehet bocsátani? Gondolja, hogy a becsületem megvásárolható?";
			link.l1 = "...";
			link.l1.go = "NightAdventure_CitizenHomieSolder_3";
		break;
			
		case "NightAdventure_CitizenHomieSolder_3":
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_CitizenHomieSolderNM")
			{
				DeleteAttribute(pchar,"GenQuest.NightAdventureSolNum");
				pchar.quest.NightAdventure_SeaExit.over = "yes";
				pchar.quest.NightAdventure_JungleExit.over = "yes";
				SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
				dialog.text = "Nem, kapitány, minden tisztességes. Megérdemelte. És arra kérem, hogy ne vonja el többé a figyelmemet a szolgálatomról.";
				link.l1 = "Nos, igaza van.";
				link.l1.go = "exit";
			}
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_CitizenHomieSolderGM")
			{
				dialog.text = "Ezer. És egy pesóval sem kevesebb.";
				link.l1 = "Nem, talán nem vagyok hajlandó ennyit fizetni egy horzsolásért.";
				link.l1.go = "NightAdventure_CitizenHomieSolder_3NM";
				if (sti(pchar.money) >= 1000)
				{
					link.l2 = "Ó... Rendben, várjon. Itt van egy toll és egy pergamen, azonnal. Írja meg, hogy visszavon minden követelését a barátommal szemben.";
					link.l2.go = "NightAdventure_CitizenHomieSolder_3GM";
				}
			}
		break;
		
		case "NightAdventure_CitizenHomieSolder_3NM":
			DeleteAttribute(pchar,"GenQuest.NightAdventureSolNum");
			pchar.quest.NightAdventure_SeaExit.over = "yes";
			pchar.quest.NightAdventure_JungleExit.over = "yes";
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
			dialog.text = "Aztán megkérem, hogy ne vonja el többé a figyelmemet a szolgálatomról.";
			link.l1 = "Nem fogom.";
			link.l1.go = "exit";
		break;
		
		case "NightAdventure_CitizenHomieSolder_3GM":
			DeleteAttribute(pchar,"GenQuest.NightAdventureSolNum");
			pchar.GenQuest.NightAdventureToPrisoner = true;
			AddMoneyToCharacter(pchar, -1000);
			dialog.text = "Tessék, tessék.";
			link.l1 = "Sok szerencsét a munkához.";
			link.l1.go = "exit";
		break;
		// <-- ночной приключенец
		
		//замечение по обнажённому оружию
		case "SoldierNotBlade":
			// belamour legendary edition если у герой офицер нации -->
			if(IsOfficerFullEquip())
			{
			dialog.text = "Kapitány, kérem, tegye el a fegyvereit: a városunkban tilos elôvenni ôket.";
			link.l1 = LinkRandPhrase("Rendben, elrakom...", "Már megtettem.", "Ahogy mondod...");
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Cseszd meg!", "Azt hiszem, használni fogom!", "Majd elrakom, ha eljön az ideje.");
			link.l2.go = "fight";
			npchar.greeting = "soldier_common";
			NextDiag.TempNode = "First Time";
		break;
			}
			// <-- legendary edition
			dialog.text = LinkRandPhrase("Hé, mi ez a sok fegyverforgatás?! Azonnal tedd el!", "Megparancsolom, hogy azonnal tegye el a fegyverét!", "Hé, " + GetAddress_Form(NPChar) + ", ne ijesztgesse az embereket! Tegye el a fegyvert!");
			link.l1 = LinkRandPhrase("Rendben, elrakom...", "Már megtettem.", "Ahogy mondod...");
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Cseszd meg!", "Azt hiszem, használni fogom!", "Majd elrakom, ha eljön az ideje.");
			link.l2.go = "fight";
			npchar.greeting = "soldier_common";
			NextDiag.TempNode = "First Time";
		break;

		case "pirate_fight":
			DialogExit();
			SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			LAi_group_Attack(NPChar, Pchar);
			DoQuestFunctionDelay("TownPirate_battle", 0.5);
		break;
	}
}
