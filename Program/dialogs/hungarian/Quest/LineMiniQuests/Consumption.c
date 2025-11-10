// диалоги по квесту Цена чахотки
void ProcessDialogEvent()
{
	ref sld, NPChar;
	aref Link, NextDiag;
	string sStr;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (pchar.questTemp.Consumption == "final")
			{
				dialog.text = "Kapitány! Hallottam, hogy elmentél a tengerre! Mi történt? Megtudtál valamit? Kérlek, mondd el, köpd ki!";
				if (CheckAttribute(pchar, "questTemp.Consumption.TakeMoney"))
				{//взял деньги
					link.l1 = "Nem, szépségem, ez a rajtaütés Ôkegyelmessége kormányzójának kérésére történt. Nagyon sajnálom, de Angelo az erôd kazamatáiban halt meg - ehhez kétség sem férhet. Álljatok ki! ";
					link.l1.go = "Waitress";
				}
				else
				{//убил Хуана
					if (CheckAttribute(pchar, "questTemp.Consumption.KillJuan"))
					{
						link.l1 = "Igazad volt. Az édesanyádat elrabolták. A parancsnok eladta a foglyokat, mint a marhákat, egy Fogyasztás nevû rabszolga-kereskedônek. De utolértem a hajóját, és most a fenéken fekszik, Angelo bátyád pedig hamarosan partra száll. Sajnos nincs annyi hosszú csónakom, amennyi szükséges lenne ahhoz, hogy minden utast egyszerre szállítsak partra. ";
						link.l1.go = "Waitress_2";
					}
					else
					{//отпустил Хуана
						link.l1 = "Igazad volt. A bátyádat elrabolták. A parancsnok eladta a foglyokat, mint a marhákat, egy Fogyasztás nevû rabszolga-kereskedônek. De utolértem a hajóját, annak ellenére, hogy nem sikerült megölnöm azt a szemetet, Angelo bátyád hamarosan partra száll. Sajnos nincs annyi hosszú csónakom, amennyi szükséges lenne ahhoz, hogy az összes utast egyszerre szállítsam partra. ";
						link.l1.go = "Waitress_2";
					}
					sld = characterFromId("ConAndjelo");
					sld.lifeday = 0;
					RemovePassenger(Pchar, sld);
				}
			}
			else
			{
				dialog.text = "Sikerült megtudnia valamit Angelo sorsáról, kapitány?";
				link.l1 = "Még nem. De azt hiszem, hamarosan lesz hírünk. Csak várnia kell. ";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		case "without_moneysss": // лесник  если Гг нажрался..сволочь:D:D:D
		    dialog.text = "Senor, megígérte, hogy megtalálja a bátyámat... Miért vesztegeted itt az idôt az ivással?";
			link.l1 = "Ohh...Igen, persze...hic... Nyugi, kislány... Jézus irányít...slurp'.... Jézus irányít. Már elmentem...hic...";
			link.l1.go = "exit";
		break;
		
		case "Servant":
			dialog.text = "Jó napot, senor. Mi dolga van itt?";
			link.l1 = "Hoztam egy küldeményt a parancsnok úrnak, de személyesen kell átadnom neki.";
			link.l1.go = "Servant_1";
		break;
		
		case "Servant_1":
			dialog.text = "Akkor keresse meg az erôdben.";
			link.l1 = "Ez a küldemény túl fontos, és nem a katonák' szemének és fülének szól. Lehet, hogy túl korán jöttem, de itt megvárhatom. Higgye el, ez nagyon fontos!";
			link.l1.go = "Servant_2";
		break;
		
		case "Servant_2":
			if (GetSummonSkillFromName(pchar, SKILL_SNEAK) < 40)
			{
				notification("Képességpróba Sikertelen (40)", SKILL_SNEAK);
				dialog.text = "A parancsnok úr általában figyelmeztet engem minden olyan fontos dologról, ami a rutin megváltoztatását igényli... Tudja, valójában figyelmeztetett erre a bizonyos esetre.";
				link.l1 = "És mit mondott?";
				link.l1.go = "Servant_3";
			}
			else
			{
				notification("Képességellenôrzés megfelelt", SKILL_SNEAK);
				dialog.text = "Rendben, hiszek magának. És még inkább hinni fogok magának, amikor a parancsnok úr megérkezik, hogy megerôsítse a szavait. De addig is folyamatosan szemmel tartom magát.";
				link.l1 = "Annyit figyelhetsz, amennyit csak akarsz...";
				link.l1.go = "Servant_4";
			}
		break;
		
		case "Servant_3":
			dialog.text = "Azt mondta, hogy ilyen esetekben hívjam a helyôrséget. De valószínûleg egyedül is boldogulunk. Fiúk! Vágjuk ki!";
			link.l1 = "Bassza meg!";
			link.l1.go = "Servant_fight";
		break;
		
		case "Servant_4":
			DialogExit();
			NextDiag.CurrentNode = "Servant_repeat";
			LAi_SetOwnerType(npchar);
			chrDisableReloadToLocation = false;
		break;
		
		case "Servant_repeat":
			dialog.text = "Mit akarsz még? Úgy döntöttél, hogy átadod az üzenetet nekem?";
			link.l1 = "Nem, megvárom a parancsnokot...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Servant_repeat";
		break;
		
		case "Servant_fight":
			int iRank = sti(pchar.rank)+5;
			int iScl = 15 + 2*sti(pchar.rank);
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			chrDisableReloadToLocation = true;
			for (i=9; i<=11; i++)
			{	
				sld = GetCharacter(NPC_GenerateCharacter("Conservant_"+i, "citiz_"+i, "man", "man", iRank, SPAIN, -1, true, "quest"));
				FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_10", "pistol1", "bullet", iScl*2);
				DeleteAttribute(sld, "SaveItemsForDead");
				DeleteAttribute(sld, "DontClearDead");
				LAi_SetWarriorType(sld);
				ChangeCharacterAddressGroup(sld, "PortSpein_houseF2", "goto", "goto5");
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Consumption_AfterHouseFight");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		//попытка залезть в сундук
		case "Man_FackYou":
			dialog.text = "Te tolvaj vagy! Vagy talán kém? Fiúk, lefelé, gyorsan!";
			link.l1 = "Gah, ördög!";
			link.l1.go = "Servant_fight";
		break;
		
		case "Sergio":
			dialog.text = "Elnézést, beszélhetnék önnel?";
			link.l1 = "Hogy ôszinte legyek, sietek. Mit akar?";
			link.l1.go = "Sergio_1";
		break;
		
		case "Sergio_1":
			dialog.text = "Hallottam, hogy egy Juan nevû emberrôl kérdezôsködik a börtönünkben...";
			link.l1 = "Valóban... megmagyarázná, hogy miért?";
			link.l1.go = "Sergio_2";
		break;
		
		case "Sergio_2":
			dialog.text = "Nyugi, nyugi! Nyugodj meg, és ne nyúlj a kardodhoz! Egy oldalon állunk! Nem tudom, miért érdekel téged a mi problémáink, de ezt meg kell állítani! Nem tudok tovább hallgatni!";
			link.l1 = "Hallgatni? Mirôl? Mit tudsz te a fogyasztásról?";
			link.l1.go = "Sergio_3";
		break;
		
		case "Sergio_3":
			dialog.text = "Sokat tudok, ha nem is mindent, és el fogom magyarázni magam - de nem itt. Találkozzunk este, amikor lekapcsolják a villanyt, orvosi asszisztens vagyok, így elhagyhatom az erôdöt. A városkapun túl találkozunk, és mindent elmondok. Könyörgöm - ne kérdezôsködjön tovább, mielôtt még felkelti a figyelmüket, ha eddig nem tette volna... Most már mennem kell. Ne feledd, éjszaka a városkapun túl.";
			link.l1 = "Rendben, ott leszek. Hé! Várj...";
			link.l1.go = "Sergio_4";
		break;
		
		case "Sergio_4":
			DialogExit();
			AddQuestRecord("Consumption", "8");
			LAi_ActorRunToLocation(npchar, "reload", "gate_back", "none", "", "", "OpenTheDoors", -1);
			pchar.quest.Consumption3.win_condition.l1 = "location";
			pchar.quest.Consumption3.win_condition.l1.location = "PortSpein_Exittown";
			pchar.quest.Consumption3.win_condition.l2 = "Hour";
			pchar.quest.Consumption3.win_condition.l2.start.hour = 0;
			pchar.quest.Consumption3.win_condition.l2.finish.hour = 3;
			pchar.quest.Consumption3.function = "Consumption_MeetSergio";
			pchar.quest.Consumption4.win_condition.l1 = "Timer";
			pchar.quest.Consumption4.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.Consumption4.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Consumption4.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Consumption4.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Consumption4.function = "Consumption_FailSergio";
			locations[FindLocation("PortSpein_Exittown")].DisableEncounters = true; //энкаутеры закрыть
			LAi_LocationDisableOfficersGen("PortSpein_Exittown", true);//офицеров не пускать
		break;
		
		case "Sergio_5":
			dialog.text = "Hála Istennek, hogy itt vagy... Remélem, nem követtek?";
			link.l1 = "Miért? Miért? Túl gyanakvó vagy, talán még jobban, mint a parancsnok úr, úgyhogy jobb, ha nekilátsz a munkának... Mit tud Juanról?";
			link.l1.go = "Sergio_6";
		break;
		
		case "Sergio_6":
			dialog.text = "A nevem Sergio Saldo. Orvosi asszisztensként szolgálok az erôdben és...";
			link.l1 = "";
			link.l1.go = "Sergio_6_1";
		break;
		
		case "Sergio_6_1":
			dialog.text = "";
			link.l1 = "Várj! Hallottad ezt?";
			link.l1.go = "Sergio_7";
			Play3DSound("lomanie_vetki", -33.25, 1.00, 3.73)
		break;
		
		case "Sergio_7":
			dialog.text = "Mi?! Hol?";
			link.l1 = "A francba, nem vagyunk egyedül... Kit hoztál magaddal, te szemétláda?";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Consumption_CreateBandits");
		break;
		
		case "Bandit":
			dialog.text = "Észrevettek minket! Tiéd a doki, enyém a másik!";
			link.l1 = "...";
			link.l1.go = "Bandit_1";
		break;
		
		case "Bandit_1":
			DialogExit();
			sld = characterFromId("Sergio");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			for (i=1; i<=3; i++)
			{	
				sld = characterFromId("Conbandit_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Conbandit_AfterFight");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Sergio_8":
			dialog.text = "Tedd el a kardod, vége van! Most már magad is láttad, hogy engem is meg akartak ölni!";
			link.l1 = "Hát, túlságosan kifinomultnak tûnik a bûnözôi játékhoz - tehát nem vagy velük. Hol is hagytuk abba? Maga börtönorvos, ugye?";
			link.l1.go = "Sergio_9";
		break;
		
		case "Sergio_9":
			dialog.text = "Igen, börtönorvosként szolgálok. Fiatal koromban orvosnak tanultam, és itt nincs sok tanult ember. Ezért tudom én mindenkinél jobban, hogy mi folyik a börtönben!";
			link.l1 = "Mi folyik itt? Mi van a rabokkal? Tudsz valamit arról, hogy hirtelen eltûnnek.";
			link.l1.go = "Sergio_10";
		break;
		
		case "Sergio_10":
			dialog.text = "A parancsnokunk eladja ôket... eladja ôket, mint a marhákat egy Juan nevû rabszolga-kereskedônek. Ô azokat választja ki, akiket nem keresnek - nincsteleneket, matrózokat véletlenszerû hajókról. Aztán hirtelen 'halálra fogyasztják ôket' - a többit kitalálhatjátok...";
			link.l1 = "Ez a Juan mégiscsak egy ember! Mit tud róla?";
			link.l1.go = "Sergio_11";
		break;
		
		case "Sergio_11":
			dialog.text = "Egy kicsit. Régebben a berber kalózokkal együtt Marokkóban végezte a piszkos munkát, szívesen mesél azokról az idôkrôl, amikor meglátogat minket. Onnan kapta a becenevét - Fogyasztás. Nem akarok belegondolni az eredetébe\nMinden hónapban eljön ide, és minden foglyot a fedélzetre visz.";
			link.l1 = "'Fogyasztás!' És még azzal vádoltak, hogy cinikus vagyok! Szóval ezért... Az a szenior parancsnokod egy igazi bunkó!";
			link.l1.go = "Sergio_12";
		break;
		
		case "Sergio_12":
			dialog.text = "Ha jól tudom, szükségük van valakire az elveszett foglyok közül, különben honnan tudnának errôl a történetrôl, igazam van? Ha igen, akkor sietned kellene: ez az utolsó éjszaka ebben a hónapban. Már aláírtam a papírokat, amelyek további három ember halálát állapítják meg, és Juan holnap dél elôtt horgonyt fog vetni, amikor megkapja ôket!";
			link.l1 = "Mit írtál alá? Nem egészen értem...";
			link.l1.go = "Sergio_13";
		break;
		
		case "Sergio_13":
			dialog.text = "Meg kellett tennem - hiszen már hónapok óta ezt csináltam! Ezért jöttem ide, hogy ezt megakadályozzam. Tudja, hogyan halt meg Pinero doktor? Az, aki elôttem kezelte a foglyokat?";
			link.l1 = "Azt hiszem, azt mondták nekem, hogy tüdôvészben halt meg, nem igaz? Szóval, kénytelen vagy belekényszeríteni. Ez logikus - de miért nem lépett senki kapcsolatba a hatóságokkal az üggyel kapcsolatban?";
			link.l1.go = "Sergio_14";
		break;
		
		case "Sergio_14":
			dialog.text = "És ki fog hinni ebben? Nem rendelkezem bizonyítékkal, és azokat a katonákat, akiknek a foglyokat kellene ôrizniük, bôkezûen megfizetik, így még az sem érdekelné ôket, ha embereket adnának el a karibiaknak étkezésként\nSenkit sem érdekelnek a foglyok, és ez egy ász a parancsnok kezében. De ezt meg lehet állítani, legalábbis egy idôre, ha kiiktatják Juant!";
			link.l1 = "Ha jól tudom, ezek a partra szállt fickók az ô emberei voltak, nem? Hogyan találhatom meg?";
			link.l1.go = "Sergio_15";
		break;
		
		case "Sergio_15":
			dialog.text = "Valószínûleg felkeltette valakinek a figyelmét a kérdéseivel... Mondtam, hogy légy óvatosabb! De ez most nem fontos. Nem tudok semmit Juan hajójáról, de a foglyokat mindig a Galera Pointra küldik, ami a sziget északi részén van. Feltételezem, hogy a rabszolgatartó hajójának a közelben kell lennie, és talán utolérheted. A hírnökei ma említették, hogy holnap délben elhajózik.";
			if (!CheckCharacterItem(pchar, "letter_consumption"))
			{
				link.l1 = "Köszönöm, Sergio, igazi tiszt és becsületes ember vagy. Azonnal felhúzom a horgonyt, és megkeresem ezt a mocskos hajót. Vissza kell jutnod az erôdbe, mielôtt keresni kezdenek.";
				link.l1.go = "Sergio_16";
			}
			else
			{
				link.l1 = "Nos, ennyit kell tudnom. Most rögtön fel kell emelnem egy horgonyt, ha nem akarom keresni azt 'Fogyasztás' az egész Újvilágban. Addig is tanulmányozhatod ezt.";
				link.l1.go = "Sergio_17";
			}
		break;
		
		case "Sergio_16":
			dialog.text = "Sok szerencsét, kapitány! Miattam ne aggódj - a legfontosabb, hogy legalább egy idôre megállítsuk ezt az egészet. Sok szerencsét kívánok!";
			link.l1 = "Az ágyúim a legjobb gyógymód a betegségre és az aljasságra. Esküszöm, hogy minden fogoly még hajnal elôtt partra száll - és Juan hajója a tengerfenéken pihen!";
			link.l1.go = "Sergio_19";
		break;
		
		case "Sergio_17":
			RemoveItems(PChar, "letter_consumption", 1);
			Log_Info("Megkaptad a levelet");
			PlaySound("interface\important_item.wav");
			dialog.text = "Mi ez? Itt van az ezredes neve és egy monogram 'J'? Hihetetlen! Honnan szerezted?";
			link.l1 = "Jobb, ha nem tudod, de szerintem a lehetô legjobban fogod használni.";
			link.l1.go = "Sergio_18";
		break;
		
		case "Sergio_18":
			dialog.text = "Úgy lesz, esküszöm mindenre, ami szent! Az ezredes még a hónap vége elôtt akasztófára kerül! Személyesen fogok gondoskodni róla!";
			link.l1 = "Attól tartok, hogy fegyelmi büntetéssel fog végzôdni, ami, ha jól tudom, nem az elsô lesz az életében. Lehet, hogy jobb lenne lelôni azt a kurvát? Ez egy nagyon hatékony orvosság... Most már mennem kell - nem akarok tovább 'Fogyasztás' várni.";
			link.l1.go = "Sergio_19";
		break;
		
		case "Sergio_19":
			DialogExit();
			AddQuestRecord("Consumption", "11");
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1);
			pchar.quest.Consumption5.win_condition.l1 = "location";
			pchar.quest.Consumption5.win_condition.l1.location = "Trinidad";
			pchar.quest.Consumption5.function = "Consumption_CreateJuan";
			pchar.quest.Consumption6.win_condition.l1 = "HardHour";
			pchar.quest.Consumption6.win_condition.l1.hour = 13;
			pchar.quest.Consumption6.function = "Consumption_FailJuan";
			// Сержио теперь наш друг и будет торговать смолами
			SetFunctionTimerCondition("Oil_PrepareSergio", 0, 0, 20, false); // таймер
		break;
		
		// генератор торговли смолами
		case "Sergio_20":
			dialog.text = "Ó, micsoda szerencsés találkozás! Senor "+GetFullName(pchar)+"! Annyira örülök, hogy látom!";
			link.l1 = "Senor Sergio! Nem számítottam rá, hogy találkozunk! Hogy van? Hogy van a jó öreg parancsnok?";
			link.l1.go = "Sergio_21";
		break;
		
		case "Sergio_21":
			dialog.text = "Jól vagyok, a parancsnok úr pedig elment a Los-Teques-i bányákba - kiderült, hogy mocskos mesterkedései Juan Consumptionnal.";
			link.l1 = "Bányák?! A lelkemre esküszöm! Soha nem gondoltam volna, hogy igazságot szolgáltatnak az ügyében...";
			link.l1.go = "Sergio_22";
		break;
		
		case "Sergio_22":
			dialog.text = "Ó, bárcsak így lenne, kapitány... Most helyezték át és lefokozták. Most a helyôrségben szolgál, és még a tiszti rangjától sem fosztották meg. Nos, legalább San Jose megszabadult ettôl a söpredéktôl.";
			link.l1 = "Nos, eddig minden rendben. Bár többet vártam.";
			link.l1.go = "Sergio_23";
		break;
		
		case "Sergio_23":
			dialog.text = "Én is... De felejtsük el a söpredéket - nem érdemli meg, hogy beszéljünk róla. Senor, amint meghallottam, hogy a hajója hamarosan befut a kikötôbe, sietve a mólóhoz siettem. Van egy ajánlatom az ön számára.";
			link.l1 = "Tényleg? Hallgatom.";
			link.l1.go = "Sergio_24";
		break;
		
		case "Sergio_24":
			if (startHeroType == 1) sStr = "Francia";
			if (startHeroType == 2) sStr = "Spanyol";
			if (startHeroType == 3) sStr = "English";
			if (startHeroType == 4) sStr = "English";
			dialog.text = "Kapitány, ön olyan embernek tûnik, akiben meg lehet bízni. Egy másik nagyon fontos dolog, hogy ön " + sStr + " és saját hajója van. Javaslom, kössünk kereskedelmi megállapodást.";
			link.l1 = "Ígéretesnek hangzik! Milyen megállapodást?";
			link.l1.go = "Sergio_25";
		break;
		
		case "Sergio_25":
			dialog.text = "Jobb, ha ezt máshol beszéljük meg - a világítótoronyban, az ôrkunyhóban. Ô régi barátom, és megbízom benne. Jöjjön el ma vagy holnap a San José-i világítótoronyhoz. Ott fogok várni rád. Biztos vagyok benne, hogy nagyon érdekesnek fogja találni az ajánlatomat!";
			link.l1 = "Rendben, Senor Sergio. Ott találkozunk!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Oil_SergioRuntoMayak");
		break;
		
		case "Sergio_26":
			chrDisableReloadToLocation = true;//закрыть локацию
			pchar.quest.Oil_SetSergioToMayakOver.over = "yes"; //снять прерывание
			dialog.text = "Üdvözlöm újra, senor. Hadd magyarázzam el önnek ezt a dolgot. ";
			link.l1 = "Csupa fül vagyok. ";
			link.l1.go = "Sergio_27";
		break;
		
		case "Sergio_27":
			dialog.text = "Mint azt már talán tudják, nemcsak katona, hanem orvos is vagyok. Hogy miért? Mert jól képzett ember vagyok. A mûveltségem megakadályozott abban, hogy itt nôkre és italokra pazaroljam az idômet. Ehelyett több expedíciót is szerveztem, és sikerült nem messze innen egy gyanta lelôhelyet találnom\nEz egy stratégiai fontosságú nyersanyag, ez a sziget az egyetlen hely, ahol megtalálható az a különleges gyanta, amelybôl szilárd és tartós hajókat építenek\nA kormányzó és egy parancsnok utasított, hogy adjam el az összes gyantát a spanyol haditengerészetnek\nA probléma az, hogy a piaci ár felét fizetik nekem, és nem tudom máshol eladni. Ezért felajánlom neked, hogy megveszed tôlem. Ez egy nagyon fontos áru, és nagyon nehéz hozzájutni.";
			link.l1 = "Mik a megállapodásunk feltételei? ";
			link.l1.go = "Sergio_28";
		break;
		
		case "Sergio_28":
			dialog.text = "Számításaim szerint havonta 60 hordót tudok majd begyûjteni anélkül, hogy gyanút keltenék. Kössünk alkut - minden hónap ötödikén meglátogatom ezt a világítótornyot, hogy megigyunk egy italt a barátommal. Gyere és csatlakozz hozzánk, ha meg akarod venni a gyantát. Tíz aranydublon egy hordóért\nFizetsz egy egész tételért, és egyszerre veszed el az egészet. Nincs nyomás, rajtad áll. Szóval, megegyeztünk?";
			link.l1 = "Nekem rohadt jó üzletnek tûnik! Persze, hogy üzlet!";
			link.l1.go = "Sergio_29";
		break;
		
		case "Sergio_29":
			dialog.text = "Csodálatos. Akkor minden hónap ötödikén megiszom egy üveg kanári bort a régi barátommal, az ôrrel, és várunk rád.";
			link.l1 = "Rendben. Csináljuk így.";
			link.l1.go = "Sergio_30";
		break;
		
		case "Sergio_30":
			dialog.text = "Örülök, hogy megegyeztünk. Viszlát, kapitány!";
			link.l1 = "Sok szerencsét a gyantás vállalkozásához, senor!";
			link.l1.go = "Sergio_31";
		break;
		
		case "Sergio_31":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 5);
			pchar.questTemp.OilTrade = "true";
			pchar.quest.Oil_fail.win_condition.l1 = "NPC_Death";
			pchar.quest.Oil_fail.win_condition.l1.character = "Sergio";
			pchar.quest.Oil_fail.function = "Oil_TradeFail";
			AddQuestRecordInfo("Unique_Goods", "4");
		break;
		
		case "oil_trade":
			dialog.text = "Jó napot, kapitány úr! Gondolom, egy adag gyantáért jött.";
			link.l1 = "Így van, Sergio úr. Minden készen áll?";
			link.l1.go = "oil_trade_1";
			link.l2 = "Senor Sergio, nincs kedvem kereskedni. Talán késôbb.";
			link.l2.go = "oil_trade_exit";
		break;
		
		case "oil_trade_exit":
			DialogExit();
			NextDiag.CurrentNode = "oil_trade";
		break;
		
		case "oil_trade_1":
			if (CheckAttribute(pchar, "questTemp.UpgradeOil"))
			{
				dialog.text = "Igen. Van nálad 2550 dublon?";
				if (PCharDublonsTotal() >= 2550)
				{
					link.l1 = "Persze. Tessék.";
					link.l1.go = "oil_trade_2";
				}
				else
				{
					link.l1 = "Sok szerencsét! A hajón felejtettem a pénzt. Azonnal idehozom!";
					link.l1.go = "oil_trade_exit";
				}
			}
			else
			{
				dialog.text = "Igen. Van hatszáz dublona nálad?";
				if (PCharDublonsTotal() >= 600)
				{
					link.l1 = "Persze. Tessék.";
					link.l1.go = "oil_trade_2";
				}
				else
				{
					link.l1 = "Sok szerencsét! A hajón felejtettem a pénzt. Azonnal idehozom!";
					link.l1.go = "oil_trade_exit";
				}
			}
			if(sti(pchar.questTemp.SergioOil) >= 1 && !CheckAttribute(pchar, "questTemp.SergioOilBlock")) // увеличить объём поставок смолами
			{
				link.l4 = "Senor Sergio, szeretnék még több gyantát venni. Tudna adni, mondjuk ötször nagyobb tételeket?";
				link.l4.go = "UpgradeOil";
			}
			if(sti(pchar.questTemp.SergioOil) >= 1 && CheckAttribute(pchar, "questTemp.SergioOilPotom") && PCharDublonsTotal() >= 3000) // увеличить объём поставок смолами, если в первый раз не принесли
			{
				link.l4 = "Tessék, ahogy ígértem, Senor Sergio, háromezer dublont, ahogy kérte. Biztos vagyok benne, hogy az ön elôrelátásával és az én befektetésemmel ez a vállalkozás mindkettônknek jelentôs hasznot fog hozni.";
				link.l4.go = "UpgradeOil_Agreed";
			}
		break;
		
		case "oil_trade_2":
			chrDisableReloadToLocation = true;//закрыть локацию
			if (CheckAttribute(pchar, "questTemp.UpgradeOil")) RemoveDublonsFromPCharTotal(2550);
			else RemoveDublonsFromPCharTotal(600);
			PlaySound("interface\important_item.wav");
			dialog.text = "Öröm önnel üzletelni, kapitány. Az embereim segíteni fognak a hordók berakodásában a hajójára.";
			link.l1 = "Köszönöm!";
			link.l1.go = "oil_trade_3";
		break;
		
		case "oil_trade_3":
			dialog.text = "Az üzlet még mindig áll. Ha újabb adagra van szüksége, jöjjön vissza egy hónap múlva.";
			link.l1 = "Rendben, Sergio. Viszlát.";
			link.l1.go = "oil_trade_4";
		break;
		
		case "oil_trade_4":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 5);
			if (CheckAttribute(pchar, "questTemp.UpgradeOil")) AddCharacterGoods(pchar, GOOD_OIL, 300);
			else AddCharacterGoods(pchar, GOOD_OIL, 60);
			AddCharacterExpToSkill(pchar, "Commerce", 200);
			pchar.questTemp.SergioOil = sti(pchar.questTemp.SergioOil) + 1; // счётчик покупок
		break;
		
		case "UpgradeOil":
			if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) >= 80)
			{
				dialog.text = "Senor"+GetSexPhrase("","ita")+", az Ön vágya, hogy több gyantát vásároljon, bizonyára bizalmat mutat az üzletünk iránt. Van azonban egy bonyolult\nA megnövekedett mennyiséggel együtt jár a szigetországi hatóságok' figyelmének nagyobb kockázata, és az ilyen szállítmányok ellenôrzése embereket és biztonsági intézkedéseket igényel, ami, elismerem, nem olcsó. Ha hajlandó vagy háromezer dublont hozzáadni az árhoz, egyszeri fizetésként, akkor megbízható embereket alkalmazok, akik megvédik a rakományt és megakadályozzák az információ kiszivárgását. Akkor az útvonalunk biztonságosabbá válik, és havonta háromszáz hordó gyantát tudok szállítani. A befektetésed ellentételezéseként, mint nagybani vásárlónak, tizenöt százalékos kedvezményt kínálok neked minden jövôbeli szállítmányra.";
				link.l1 = "Háromezer dublont a szállítmányok biztosítására? Senor Sergio, nem titkolom, ez az ár hihetetlennek tûnik - mintha inkább összeesküvést javasolna az Escorialban, minthogy csak a szurokszállítmányt biztosítsa!";
				link.l1.go = "UpgradeOil_1";
				Notification_Skill(true, 80, SKILL_COMMERCE);
			}
			else
			{
				dialog.text = "Seńor"+GetSexPhrase("","ita")+", nagyra értékelem az érdeklôdését, de az ilyen nagy üzletekben tapasztalatra és óvatosságra van szükség. Hogy ôszinte legyek, az Ön szintje a kereskedelmi ügyekben még nem elég magas ahhoz, hogy ilyen volument kezeljen. Azt tanácsolom, hogy szerezzen egy kicsit több tapasztalatot, és térjen vissza hozzám, amikor készen áll a nagyobb szállítmányokra. Akkor talán alaposan megbeszéljük a dolgot.";
				link.l1 = "Rendben. Késôbb visszatérünk erre a kérdésre.";
				link.l1.go = "oil_trade_exit";
				Notification_Skill(false, 80, SKILL_COMMERCE);
			}
		break;
		
		case "UpgradeOil_1":
			dialog.text = "Senor"+GetSexPhrase("","ita")+", megértem az aggodalmát. De tudja, hogy a biztonság sosem olcsó, különösen az ilyen ritka áruk esetében. Emellett nem csak garantálom, hogy nem szivárog ki, hanem olyan kedvezményt is kínálok, amely idôvel kompenzálja a befektetését. Ez nem egy ésszerû kompromisszum?";
			link.l1 = "Elismerem: a mi üzletünkben a megbízhatóság és a titoktartás költséges, és a kedvezmény némileg vonzóbbá teszi a lehetséges üzletünket. De háromezer dublon mégiscsak túlzó összeg. Talán csökkenthetné egy kicsit?";
			link.l1.go = "UpgradeOil_2";
		break;
		
		case "UpgradeOil_2":
			dialog.text = "Sajnálom, de a félmegoldások elfogadhatatlanok ilyen ügyekben. Vagy teljes védelmet biztosítunk, vagy mindent kockára teszünk. Az összeg nem változik, és csak így tudom garantálni a megbízhatóságot és a titoktartást. Ugye nem akarja, hogy az egész királyi flotta elôbb engem, aztán magát üldözze?";
			if (PCharDublonsTotal() >= 3000)
			{
				link.l1 = "Rendben, Senor Saldo, meggyôzött engem. A biztonság és a megbízhatóság megéri az árát. Háromezer dublont. Tessék, tessék.";
				link.l1.go = "UpgradeOil_Agreed";
			}
			link.l2 = "Senor Saldo, meggyôzött engem ezeknek az intézkedéseknek a szükségességérôl. Háromezer dubloon azonban komoly összeg, és jelenleg nincs nálam. Várnom kell, amíg összegyûjtöm a szükséges összeget.";
			link.l2.go = "UpgradeOil_4";
			link.l3 = "Ennyi pénzért egy egész flottát és az összes katonát meg lehetne vesztegetni a kontinensen, nemhogy ôröket bérelni egy szerény szurokrakományért! Elnézést kérek, de egy ilyen ajánlatba nem tudok belemenni. Hagyjunk mindent úgy, ahogy van, túlzások és további kiadások nélkül.";
			link.l3.go = "UpgradeOil_3";
		break;
		
		case "UpgradeOil_Agreed":
			dialog.text = "Nos akkor, senor, úgy látom, a bizalmunk kölcsönös. Biztos lehet benne: mindent megfelelôen elintézünk. Most pedig a részletekrôl: 300 hordó gyanta, mint mindig, minden hónap 5-én itt a trinidadi világítótoronyban várja Önt. Az egész tételt 2550 dublonnáért vásárolhatja meg.";
			link.l1 = "Kiváló, Senor Sergio. Ne hagyjon cserben.";
			link.l1.go = "UpgradeOil_Agreed_1";
			RemoveDublonsFromPCharTotal(3000);
			AddQuestRecordInfo("Unique_Goods", "4_1");
			pchar.questTemp.UpgradeOil = true;
			pchar.questTemp.SergioOilBlock = true;
			DeleteAttribute(pchar, "questTemp.SergioOilPotom");
		break;
		
		case "UpgradeOil_Agreed_1":
			dialog.text = "Ne legyenek kétségei, seńor"+GetSexPhrase("","ita")+". Minden a legmagasabb szinten lesz megszervezve, és a közös erôfeszítésünk meghozza majd a gyümölcsét.";
			link.l1 = "Viszlát.";
			link.l1.go = "oil_trade_exit";
		break;
		
		case "UpgradeOil_3":
			DialogExit();
			pchar.questTemp.SergioOilBlock = true;
			NextDiag.CurrentNode = "oil_trade";
		break;
		
		case "UpgradeOil_4":
			dialog.text = "Jöjjön, ha megvan a teljes összeg. Örömmel kötök önnel egy új üzletet.";
			link.l1 = "Rendben.";
			link.l1.go = "oil_trade_exit";
			pchar.questTemp.SergioOilBlock = true;
			pchar.questTemp.SergioOilPotom = true;
		break;
	// <-- генератор смол
		
		case "Juan_abordage":
			dialog.text = "Ki a fene vagy te?";
			link.l1 = "Az én nevem "+GetFullName(pchar)+", ami téged illet, Fogyasztás, az ördög vár rád - és hamarosan a lelkedet is megkaparintja!";
			link.l1.go = "Juan_abordage_1";
		break;
		
		case "Juan_abordage_1":
			if (CheckAttribute(pchar, "questTemp.Consumption.House"))
			{
				dialog.text = "Ez a hajó fel fog robbanni - a puskaporos szobában már ég a kanóc -, miért kellene mindkettônknek meghalnia? Tegyük le a kardokat. Neked lesz elég idôd kijutni, én pedig leugrom a hajóról, a Galera Point karnyújtásnyira van innen. Ha aranyra van szükséged, vedd el! Ötszáz dublont, készpénzzel a szögre - és te elfelejtesz engem, én pedig téged! Megegyeztünk?";
				link.l1 = "Arany? Nem a pénzért kezdtem bele ebbe az egészbe, Juan, hanem azért, hogy megöljem a söpredéket, és te vagy a legnagyobb jutalom önmagadban.";
				link.l1.go = "Juan_abordage_2";
				link.l2 = "Ötszáz dublont? Te nevetsz rajtam, Fogyasztás. Szerintem legalább kétszer annyit halmoztál fel itt... Adj egy ezrest most rögtön, és mehetsz a pokolba, különben...";
				link.l2.go = "Juan_abordage_3";
			}
			else
			{
				dialog.text = "A hajó mindjárt felrobban, úgyhogy jó társaságom lesz, mit gondolsz?";
				link.l1 = "Túl sokat beszélsz, Fogyasztás, térj a tárgyra!";
				link.l1.go = "Juan_abordage_5";
			}
		break;
		
		case "Juan_abordage_2":
			dialog.text = "Megállapodhattunk volna... Eh, mindegy!";
			link.l1 = "Elvetted ezeket a szerencsétleneket a cellájukból, és nem tudtak sem ellenállni, sem elszökni. Gyáva vagy, Fogyasztó, és most gyávaként fogsz meghalni.";
			link.l1.go = "Juan_abordage_5";
		break;
		
		case "Juan_abordage_3":
			dialog.text = "Van egy üzleti fogásod, barátom... Tessék - ez minden, amim van. Azért nem túl sok egy életért, ugye?";
			link.l1 = "A te életed egy golyót sem ér, úgy látszik, ez a legjövedelmezôbb alku az életemben. Most pedig tûnj el.";
			link.l1.go = "Juan_abordage_4";
			TakeNItems(pchar, "gold_dublon", 1000);
			Log_Info("Kaptál 1000 dublont.");
			PlaySound("interface\important_item.wav");
			ChangeCharacterComplexReputation(pchar, "nobility", -10);
			OfficersReaction("bad");
			pchar.questTemp.Consumption.TakeMoney = "true"; //атрибут для диалога
		break;
		
		case "Juan_abordage_4":
			DialogExit();
			chrDisableReloadToLocation = true;
			sld = &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)];
			Lai_SetPlayerType(pchar);
			LAi_RemoveCheckMinHP(sld);
			LAi_SetImmortal(sld, true);
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "ConJuan_AfterFight_1", 10.0);
		break;
		
		case "Juan_abordage_5":
			dialog.text = "Kár, hogy nem lesz idôd mindenkit megmenteni és megölni engem, ugye? A kanóc ég, és az idô múlik...";
			link.l1 = "A fenébe! Ki kell vinnem innen az embereket... Tûnj el, söpredék - elôbb-utóbb megkapod, amit megérdemelsz!";
			link.l1.go = "Juan_abordage_4";
			link.l2 = "De azért megpróbálom...";
			link.l2.go = "Juan_abordage_6";
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			OfficersReaction("good");
			sld = GetCharacter(NPC_GenerateCharacter("ConAndjelo", "citiz_9", "man", "man", 5, SPAIN, -1, true, "quest"));
			sld.name = "Angelo";
			sld.lastname = "";
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, false);
		break;
		
		case "Juan_abordage_6":
			//LAi_SetCurHPMax(NPChar);
			//LAi_GetCharacterMaxEnergy(NPChar);			
			QuestAboardCabinDialogExitWithBattle("ConJuan_AfterFight_2"); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.questTemp.Consumption.KillJuan = "true"; //атрибут для диалога
		break;
		
		case "Waitress":
			dialog.text = "Ah... szóhoz sem jutok... Micsoda rémálom!";
			link.l1 = "Sajnos, nem tehettem semmit. Sajnálom, kislány. Viszontlátásra.";
			link.l1.go = "Waitress_1";
		break;
		
		case "Waitress_1":
			DialogExit();
			AddQuestRecord("Consumption", "16");
			AddQuestUserData("Consumption", "sSex", GetSexPhrase("",""));
			Consumption_Close();
		break;
		
		case "Waitress_2":
			dialog.text = "Hihetetlen! Te... tényleg megmentetted ôt? Fogalmam sincs, hogyan köszönjem meg.";
			if (CheckAttribute(npchar, "quest.Consumption.sex"))
			{
				link.l1 = "El tudom képzelni, szépségem. De az én részem az üzletbôl már teljesült - már csak egy apróság van hátra.";
				link.l1.go = "Waitress_3";
			}
			link.l2 = "A kötelesség hívott - és én cselekedtem. Ennyi volt.";
			link.l2.go = "Waitress_5";
			if (CheckAttribute(pchar, "questTemp.Consumption.KillJuan")) AddQuestRecord("Consumption", "18");
			else AddQuestRecord("Consumption", "17");
		break;
		
		case "Waitress_3":
			dialog.text = "Én... ó, Istenem! Igazad van. Neki, ahogy ígértem... Menj fel a szobába - nincs sok idônk.";
			link.l1 = "Akkor siessünk!";
			link.l1.go = "Waitress_4";
		break;
		
		case "Waitress_4"://благодарность натурой
			DialogExit();
			LocatorReloadEnterDisable("PortSpein_tavern", "reload1_back", true); //закрыть таверну
			LocatorReloadEnterDisable("PortSpein_tavern", "reload2_back", false); //открыть комнату
			bDisableFastReload = true;//закрыть переход
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2_back", "PortSpein_tavern_upstairs", "goto", "goto3", "ConsumptionSexWaitress", -1);
			pchar.questTemp.Consumption.Sex = "true";
		break;
		
		case "Waitress_sex":
			dialog.text = "Itt vagyok, bátor caballero! És nézd, mit hoztam magammal.";
			link.l1 = "Nocsak, nocsak, le vagyok nyûgözve, nyissuk ki azt a meggybort! Aztán kinyitunk valami mást... Végül is ez a te szerencsenapod... Ha-ha!";
			link.l1.go = "Waitress_sex_1";
		break;
		
		case "Waitress_sex_1":
			DialogExit();
			DoQuestCheckDelay("PlaySex_1", 0.1);
		break;
		
		case "Waitress_5":
			if (CheckAttribute(pchar, "questTemp.Consumption.KillJuan"))
			{
				dialog.text = "Igazi lovag vagy! Caballero! Tessék - ne vedd sértésnek, de szeretném, ha elfogadnád. Ezt a pénzt Angelo váltságdíjáért gyûjtöttem, de most már nem fontos! Kérlek, ne utasítsd vissza - vedd el!";
				link.l1 = "Nos, emlékezni fogok a szemére, senorita - sokkal szebbek, amikor a boldogság könnyei ragyognak bennük, nem pedig a fájdalomé. Elfogadom az ajándékát. Viszlát, és sok szerencsét neked és Angelónak.";
				link.l1.go = "Waitress_6";
				AddMoneyToCharacter(pchar, 5000);
			}
			else
			{
				dialog.text = "Igazi lovag vagy! Caballero! Elmondom mindenkinek! Mindig emlékezni fogok rád!";
				link.l1 = "Nos, és a szemére is emlékezni fogok, senorita - sokkal szebbek, amikor a boldogság könnyei ragyognak bennük, nem pedig a fájdalomé. Legyen mindig boldog. Viszontlátásra!";
				link.l1.go = "Waitress_6";
			}
		break;
		
		case "Waitress_6":
			DialogExit();
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
			Consumption_Close();
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
