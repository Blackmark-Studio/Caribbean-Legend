// boal 25/04/04 общий диалог солдат форта
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;	

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	// belamour legendary edition в квестах не используется, да, и лишний раз игроков не нужно заставлять по кейсам бегать. Квесты пишите в коммоне
    /* // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Fort\" + NPChar.City + "_Fort.c";
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
				dialog.text = RandPhraseSimple("Egy kém! Add le a fegyvered és kövess engem!", "Egy ellenséges ügynök! Elfogni "+ GetSexPhrase("ôt","ôt") +"!");
				link.l1 = RandPhraseSimple("Pofa be, puhány!", "Cseszd meg!");
				link.l1.go = "fight"; 
			}
			else
			{
				// eddy. проверяем, не казачок ли. -->
				if (GetRelation2BaseNation(sti(npchar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
				{
					dialog.text = RandPhraseSimple("Ki vagy te, és mit keresel itt?", "Maradj nyugton! Ki vagy te? Milyen okból próbálsz bejutni az erôdbe?");
					//==> по лицензии
					if (CheckNationLicence(HOLLAND))
					{
						link.l1 = "Biztos úr, nekem van " + GetRusNameNationLicence(sti(npchar.nation)) + ", tehát jogi alapon vagyok itt. Tessék, kérem, nézze meg...";
						link.l1.go = "LicenceOk";
					}
					else
					{
						//==> по флагу
						// заглушка на пирата
						if (sti(pchar.nation) == PIRATE)
						{
    						dialog.text = RandPhraseSimple("Kalóz van az erôdben?! Ragadd meg"+ GetSexPhrase("ôt","ôt") +"!", "Ez egy kalóz, aki szimatol valamit az erôdünkben! A börtönbe!!!");
							link.l1 = RandPhraseSimple("Igen, kalóz vagyok, most mi lesz?", "Heh, kapj el, ha tudsz...");
							link.l1.go = "fight"; 
							break;
						}
						if (findsubstr(pchar.location.from_sea, "_town" , 0) != -1) //если причалил в городе
						{
							link.l1 = "Nem látod a " + NationNameGenitive(sti(pchar.nation)) + " zászlót a hajóm árbocán?!";
						}
						else //если причалил не в городе
						{
							link.l1 = "Horgonyt vetettem a " + XI_ConvertString(GetIslandByCityName(npchar.city)+"Gen") + " közelében a" + NationNameGenitive(sti(pchar.nation)) + "zászló alatt ! Szükséged van még valamire?";
						}
						// belamour legendary edition вызываюий доверие даёт возможность обмануть стражу
						if(sti(pchar.reputation.fame) < 41 && CheckCharacterPerk(pchar, "Trustworthy"))
						{
							notification("Megbízható", "Trustworthy");
							link.l1.go = "NotPegYou";
						}
						else
						{
							if (GetSummonSkillFromName(pchar, SKILL_SNEAK) < (10+rand(50)+rand(50)))
							{
								notification("Képességellenôrzés sikertelen", SKILL_SNEAK);
								link.l1.go = "PegYou";
							}
							else
							{
								link.l1.go = "NotPegYou";
							}
						}
					}
				}
				// <-- eddy. проверяем, не казачок ли.
				else
				{
					if (sti(NPChar.nation) == PIRATE)
					{
						if (sti(rColony.HeroOwn)) // наш горожанин
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
					}
					
					//Jason --> мини-квест Дефицитный товар
					if (!CheckAttribute(pchar, "questTemp.Sharlie.FastStart") && sti(pchar.rank) < 4 && !CheckAttribute(pchar, "questTemp.Wine") && npchar.location.group == "soldiers")
					{// Addon 2016-1 Jason пиратская линейка
						string wineCity = "FortFrance";
						if(SandboxMode)
						{
							if(CheckAttribute(pchar,"HeroParam.ToCityId"))
							{
								wineCity = pchar.HeroParam.ToCityId;	
							}
						}
						if(GetCityNameByIsland(LoadedLocation.islandId) ==  wineCity && npchar.location.locator == "protector1")
						{
							dialog.text = "Hé, haver! Megtennél nekem egy kis szívességet?";
							link.l1 = "Attól függ, mit kell tenni.";
							link.l1.go = "Wine_soldier";
							link.l2 = "Erre most nincs idôm.";
							link.l2.go = "exit";
							pchar.questTemp.Wine = "true";
							DelLandQuestMark(npchar);
							break;
						}
						if(StartHeroType == 2)
						{
							if(LoadedLocation.id == "Santiago_fort")
							{
								dialog.text = "Hé, haver! Megtennél nekem egy kis szívességet?";
								link.l1 = "Attól függ, mit kell tenni.";
								link.l1.go = "Wine_soldier";
								link.l2 = "Erre most nincs idôm.";
								link.l2.go = "exit";
								pchar.questTemp.Wine = "true";
								DelLandQuestMark(npchar);
								break;
							}
						}
					}
					// <-- мини-квест Дефицитный товар
					
					//belamour legendary edition диалоги, если герой имеет звания и заслуги перед отечеством -->
					
					// Шарль де Мор генерал-губернатор французских колоний
					if(CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE)
					{
						switch(rand(2))
						{
							case 0: 
							dialog.text = "Ôexcellenciája, fôkormányzó úr! Mit szolgálhatok fel?";
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
							link.l1 = "Nyugodjon meg, katona, nincs szükségem a jelentésére. Jelentsen a fônökének.";
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
							link.l1 = "Nem, pajtás, maradj türelemmel...";
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
					/* link.l3 = "Н-да... ясно. Я вот что "+ GetSexPhrase("хотел","хотела") +" спросить...";
					link.l3.go = "quests";//(перессылка в файл города) */
				}
			}
		break;
		
		//Jason --> мини-квест Дефицитный товар
		case "Wine_soldier":
			dialog.text = "Tudja, nagyon szeretnék egy kis bort... De nem azt a helyi, rothadt gyümölcsökbôl készült moslékot, amit hordónként két pezóért árulnak - egy üveg igazi európai bort akarok. A városban a kereskedôknél lehet kapni. Elég drága, de én teljes egészében kifizetem, sôt még háromszáz pezót is adok hozzá. Szóval, hoznál nekem is belôle?";
			link.l1 = "És miért nem tudsz magadnak szerezni? Nem kell túlfizetned, csak várd meg, amíg felmentenek a posztod alól, és menj érte. Mi a bökkenô?";
			link.l1.go = "Wine_soldier_1";
		break;
		
		case "Wine_soldier_1":
			dialog.text = "Nincs csapda. Csak nem hagyhatom el az erôdöt, hogy a városba menjek, amíg nem kapom meg a szabadságomat, ami nem mostanában fog megtörténni. Különben is, a parancsnokunk szigorúan megtiltotta az ivást az erôdben, csessze meg! Szóval, segítenél egy katonának?";
			link.l1 = "Nos, miért ne? Hozom neked azt a bort, úgyis van egy kis szabadidôm.";
			link.l1.go = "Wine_soldier_2";
			link.l2 = "Sajnálom, pajtás, de nem tehetem. Keress valaki mást, aki segít neked.";
			link.l2.go = "exit";
		break;
		
		case "Wine_soldier_2":
			dialog.text = "Remek! Köszönöm szépen! Ma ôrségben vagyok, úgyhogy gyere holnap. Az erôd tetején találsz majd, ott odacsúsztathatod nekem az üveget, hogy senki ne vegye észre...";
			link.l1 = "Rendben. Várj meg, holnap meglátogatlak.";
			link.l1.go = "exit";
			pchar.questTemp.Wine.id = npchar.ID;
			pchar.questTemp.Wine.SName = GetFullName(npchar);
			pchar.questTemp.Wine.bottle = "true";
			npchar.lifeday = 5;
			SetFunctionTimerCondition("Wine_Exchange", 0, 0, 1, false);
			pchar.questTemp.Wine.City = GetCityNameByIsland(LoadedLocation.islandId);
			if(StartHeroType == 2) pchar.questTemp.Wine.City = "Santiago";
			Log_TestInfo(pchar.questTemp.Wine.City);
			SaveCurrentQuestDateParam("questTemp.Wine_bottle");
			AddQuestRecord("Wine", "0");
			SetFunctionLocationCondition("WineTraderQM", pchar.questTemp.Wine.City+"_town", 0);
		break;
		// <-- мини-квест Дефицитный товар
		
		//============================== ноды на разборки при распознавании =========================
		case "PegYou":
			dialog.text = RandPhraseSimple("Nekem úgy tûnik, hogy ez valami trükk. Beszéljünk a parancsnokkal, "+ GetSexPhrase("pajtás","drága") +", és derítsük ki az egészet...", "Hmm... Valami azt súgja, hogy nem az vagy, akinek kiadod magad... Add le a fegyvered " + GetAddress_Form(npchar) + ", és kövess engem a további nyomozáshoz!");
			link.l1 = RandPhraseSimple("Cseszd meg!", "Amikor két vasárnap jön egy héten...");
			link.l1.go = "fight";
			if (sti(pchar.questTemp.stels.landFort) != GetDataDay())
			{
				AddCharacterExpToSkill(pchar, SKILL_SNEAK, 40);
				pchar.questTemp.stels.landFort = GetDataDay();
			}
		break;
		case "NotPegYou":
			dialog.text = RandPhraseSimple("Ó, értem... Úgy tûnik, minden rendben van, szabadon távozhat, " + GetAddress_Form(pchar) + ".", "Egy kicsit elfáradhattam az ôrségben... Úgy tûnik, minden rendben van, " + GetAddress_Form(pchar) + ", sajnálom.");
			link.l1 = "Semmi gond!";
			link.l1.go = "exit";
			if (sti(pchar.questTemp.stels.landFort) != GetDataDay())
			{
				AddCharacterExpToSkill(pchar, SKILL_SNEAK, 80);
				pchar.questTemp.stels.landFort = GetDataDay();
			}
		break;
		case "LicenceOk":
			iTemp = GetDaysContinueNationLicence(HOLLAND);
			if (ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 0) <= -12)
			{
				dialog.text = "Most jut eszembe! Micsoda szemtelenség! Idejönni egy kereskedô álcája alatt! A képeid minden barakkban ki vannak függesztve, te szemétláda! Ezúttal nem úszod meg! Fogjátok el!";
				link.l1 = RandPhraseSimple("Arrgh!...", "Nos, te kérted...");
				link.l1.go = "fight";	
				TakeNationLicence(HOLLAND);
				break;
			}
			if (findsubstr(pchar.location.from_sea, "_town" , 0) == -1) //если причалил не в городе
			{
				dialog.text = "Ide jöttél kereskedni? Megkérdezhetem, hogyan? Hol van a hajód? Tudod, ez az egész nagyon gyanúsnak tûnik, és kénytelen vagyok itt tartani téged, amíg ki nem derítjük az egészet. Adja át a fegyverét és kövessen!";
				link.l1 = RandPhraseSimple("Cseszd meg!", "Amikor két vasárnap jön egy héten...");
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
				link.l1 = "Köszönöm, a lehetô leghamarabb megteszem.";
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
				dialog.text = LinkRandPhrase("Nos, minden rendben van. A licenc érvényes " + FindRussianDaysString(iTemp) + ". Átmehet.", "Minden tiszta, "+GetAddress_Form(npchar)+". Szabadon ki-be járhatsz a városban, a jogosítványod érvényes  " + FindRussianDaysString(iTemp) + ". Elnézést a zavarásért.", "Minden rendben van, " + GetAddress_Form(npchar) + ", nem tartom tovább itt.");
				link.l1 = RandPhraseSimple("Kiváló. Üdvözlettel.", "Köszönöm, biztos úr.");
				link.l1.go = "exit";
			}
		break;

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
			dialog.text = LinkRandPhrase("Mi a fenéért rohangálsz itt egy felnyílt pengével? Azonnal tedd el a fegyvered!", "Megparancsolom, hogy azonnal tegye hüvelybe a fegyverét!", "Hé, "+ GetSexPhrase("pajtás","lány") +", ne ijesztgesse a népet! Tedd hüvelybe a fegyvered!");
			link.l1 = LinkRandPhrase("Jól van.", "Rendben.", "Ahogy mondod...");
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Cseszd meg!", "Nem árt az álmodozás...", "Amikor két vasárnap jön egy héten.");
			link.l2.go = "fight";
			npchar.greeting = "soldier_common";
			NextDiag.TempNode = "First Time";
		break;
	}
}
