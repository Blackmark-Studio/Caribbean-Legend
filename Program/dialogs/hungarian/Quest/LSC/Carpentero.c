// Санчо Карпентеро - бармен
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "GenQuest.CitizenConflict") && sti(pchar.GenQuest.CitizenConflict) > 3)
			{
				dialog.text = "Nem akarok veled beszélgetni. Ok nélkül békés emberekre támadtok, és harcra provokáljátok ôket. Tûnjetek el a kocsmámból!";
				link.l1 = "Hm...";
				link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.LSC == "return" && !CheckAttribute(npchar, "quest.return_isl"))
			{
				dialog.text = ""+pchar.name+"! Annyira örülök, hogy látlak! Tudtam, tudtam, hogy a pletykák hazugságok! A fenébe is, most már feltétlenül inni kell rá!";
				link.l1 = "Hát akkor igyunk, pajtás! Én is rohadtul örülök, hogy látlak!";
				link.l1.go = "exit";
				npchar.quest.return_isl = "true";
				break;
			}
			// пей до дна
			if (CheckAttribute(npchar, "quest.drink") && npchar.quest.drink == "fail")
			{
				dialog.text = ""+pchar.name+", Sajnálom a kudarcodat. Kevesen képesek a kövér embert túlhajtani. Hogy van a fejed?";
				link.l1 = "Igen, haver, jó erôs rumod van. Tartozom neked az italokért... mennyivel?";
				link.l1.go = "drunk_fail";
				break;
			}
			if (CheckAttribute(npchar, "quest.drink") && npchar.quest.drink == "win")
			{
				dialog.text = "Megverted Fazio-t, "+pchar.name+"! Meglepôdtem, csak kevesen tudták lekörözni. Tessék, itt van a kétszáz dublonod.";
				link.l1 = "Köszönöm a kedves szavakat, haver!";
				link.l1.go = "drunk_win";
				break;
			}
			// крабовый салат
			if (CheckAttribute(npchar, "quest.crab") && npchar.quest.crab == "begin")
			{
				dialog.text = ""+pchar.name+"? Azt mondják, hogy egy narvál szerelô által készített ruhában merültél a mélybe. Igaz ez, vagy csak pletykák, mint mindig?";
				link.l1 = "Ez igaz, haver. Tényleg lemerültem.";
				link.l1.go = "crab";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Üdvözlöm az új embert a kocsmámban! Üdvözöllek! A kocsmámban mindig találsz italokat, a borkészleteim tele vannak, bár az ételekrôl nem mondhatom el ugyanezt, ha-ha... Vicceltem. A nevem Sancho Carpentero és én vagyok a tulajdonos.";
				link.l1 = TimeGreeting()+", Sancho. A nevem "+GetFullName(pchar)+". Örülök, hogy találkoztunk.";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, barátom "+pchar.name+"! Örülök, hogy látlak a kocsmámban! Kérsz valamit inni?";
				// квестовые ветки
				if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "search_mush_1" && !CheckAttribute(npchar, "quest.mushket"))
				{
					link.l6 = "Figyelj, Sancho, nem tudod, hol tudok szerezni egy jó muskétát? Nem egy alkalmi katona fegyverét, hanem valami pontosat, vadászatra talán?";
					link.l6.go = "mushket";
				}
				if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "search_mush_2")
				{
					link.l6 = "Figyelj, Sancho, lenne néhány kérdésem hozzád. Egy Adolf Barbier nevû embert keresek. Azt mondják, hogy gyakran jár errefelé...";
					link.l6.go = "adolf";
				}
				if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "barmen_whiskey")
				{
					link.l6 = "Figyelj, Sancho, azt mondják, hogy Chad Kapper vett tôled arzént...";
					link.l6.go = "whiskey";
				}
				if (CheckCharacterItem(pchar, "talisman1") && CheckAttribute(npchar, "quest.rat"))
				{
					link.l7 = "Sancho, akarod, hogy mutassak neked valami érdekeset? Ez az a denevérmaszk, amit annyira szerettél volna megszerezni?";
					link.l7.go = "rat";
				}
				if (CheckCharacterItem(pchar, "talisman1") && CheckAttribute(npchar, "quest.ratmoney") && PCharDublonsTotal() >= 1)
				{
					if (PCharDublonsTotal() >= sti(npchar.quest.ratmoney))
					{
						if(!CheckAttribute(npchar, "quest.ratmoneyagain")) ChangeCharacterComplexReputation(pchar, "fame", 5);
						link.l7 = "Sancho, a cuirassomért jöttem. Itt a pénz.";
						link.l7.go = "rat_3";
					}
					else
					{
						npchar.quest.ratmoneyagain = true;
						link.l7 = "Sancho, a cuirassomért jöttem. Itt a pénz.";
						link.l7.go = "rat_take_money_not_all";
					}
				}
				if (makeint(pchar.money) >= 25)
				{
					link.l1 = "Adj egy kis rumot, Sancho.";
					link.l1.go = "drink";
				}
				if (makeint(pchar.money) >= 20)
				{
					link.l2 = "Itt akarok maradni.";
					link.l2.go = "room";
				}
				if (stf(environment.time) >= 6.0 && stf(environment.time) <= 18.0 && makeint(pchar.money) >= 300)
				{
					link.l9 = "Unatkozom... Sancho, egy üveg borral akarom tölteni az idôt itt estig...";
					link.l9.go = "drink_sit";
				}
				link.l3 = LinkRandPhrase("Van valami érdekes mondanivalód?", "Mi történt mostanában a szigeten?", "Bármilyen pletyka?");
				link.l3.go = "rumours_LSC";
				if (CheckAttribute(npchar, "quest.crab") && npchar.quest.crab == "current" && CheckCharacterItem(pchar, "crab_pincers"))
				{
					link.l10 = "Sancho, el akarok adni neked rákkarmokat.";
					link.l10.go = "crab_trade";
				}
				link.l4 = "Sancho, szeretnék kérdezni valamit a szigetrôl.";
				link.l4.go = "int_quests"; //информационный блок
				link.l5 = "Nem, haver. Csak meg akartam nézni, hogy vagy itt.";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting":
			dialog.text = "Én is. Remélem, hogy legalább minden második nap vagy akár minden este találkozunk, ha-ha! Ôszintén örülök minden látogatónak a kocsmámban.";
			if (makeint(pchar.money) >= 25)
			{
				link.l1 = "Adj egy kis rumot, Sancho.";
				link.l1.go = "drink";
			}
			if (makeint(pchar.money) >= 20)
			{
				link.l2 = "Itt akarok maradni.";
				link.l2.go = "room";
			}
			link.l3 = "Sancho, szeretnék kérdezni valamit a szigetrôl.";
			link.l3.go = "int_quests"; //информационный блок
			link.l4 = "Viszlát, Sancho!";
			link.l4.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "mushket":
			dialog.text = "Nem, barátom, nem tudok segíteni. Tudod, a söröspoharak és borosüvegek specialistája vagyok - de a muskétáké nem, ha-ha! Menj be a boltba, úgy hallottam, hogy Axel néha érdekes fegyvereket árul. Talán ott megtalálod, amire szükséged van.";
			link.l1 = "Köszönöm a tanácsot.";
			link.l1.go = "exit";
			npchar.quest.mushket = "true";
		break;
		
		case "adolf":
			dialog.text = "Adolf? Igen, idônként meglátogat, bár az utóbbi napokban nem láttam. Azóta hiányzik, mióta elbeszélgetett azzal a kövér emberrel, Giuseppével.";
			link.l1 = "Giuseppe? Giuseppe Fazio-ra gondol?";
			link.l1.go = "adolf_1";
		break;
		
		case "adolf_1":
			dialog.text = "Ha, haver, csak egy Giuseppe van a szigeten - Giuseppe Fazio. Igen, ô az. Néhány órán át ültek, rumot ittak, és nagyon élénken beszélgettek.";
			link.l1 = "Veszekedtek?";
			link.l1.go = "adolf_2";
		break;
		
		case "adolf_2":
			dialog.text = "Nem. Úgy tûnt, mintha régi cimborák lennének. Nézze, csak látogassa meg Faziót a 'Caroline' és kérdezze meg Adolfról.";
			link.l1 = "Rendben, megteszem.";
			link.l1.go = "adolf_3";
		break;
		
		case "adolf_3":
			dialog.text = "Ez minden? Azt mondta, hogy lenne néhány kérdése...";
			link.l1 = "Igen. Mondja, ki az a Vörös Mária és Marcello Küklopsz?";
			link.l1.go = "adolf_4";
		break;
		
		case "adolf_4":
			dialog.text = "Red Mary az egyik narvál. Fiatal és gyönyörû lány, de teljesen vad, igen. Tudja használni a pengét és a kézifegyvert, mint bármelyik férfi. Régen Alan Milrow, a Narwhal klán volt vezetôjének barátnôje volt, mielôtt az admirális megölte\nAlan halála keményen megviselte, legtöbbször sír és átkozódik Sharkkal a kabinjában a 'Ceres Smithy'.... De majd túlteszi magát rajta, az élet mégiscsak folytatódik\nNem sokat tudok Marcellóról, csak párszor láttam. Gyanús fickó. Azt mondják, hogy királyi vadász volt, egy harcban elvesztette a szemét, és elment hajózni, mint fedélzeti tiszt\nKalózok, úgy tûnik, haragszik rájuk. Nem meglepô, tekintve, hogy korábban kereskedelmi hajókra szállt fel.";
			link.l1 = "Értem. Köszönöm szépen, Sancho, sokat segítettél!";
			link.l1.go = "adolf_5";
		break;
		
		case "adolf_5":
			dialog.text = "Szívesen, pajtás, gyere el hozzám máskor is, és megiszunk együtt egy sört...";
			link.l1 = "Persze!";
			link.l1.go = "adolf_6";
		break;
		
		case "adolf_6":
			DialogExit();
			pchar.questTemp.Saga.SharkHunt = "search_mush_3"; //флаг на Джузеппе
			AddQuestRecord("SharkHunt", "13");
		break;
		
		// виски для Акулы
		case "whiskey":
			dialog.text = "Kapper? Nem. Mostanában nem járt a kocsmában. Marcello Küklopsz negyedórával ezelôtt vett egy flaska arzént - ôt is gyötrik a patkányok. Tökéletesen megértem ôt... Átkozott patkányok.";
			link.l1 = "Marcello Cyclops?!";
			link.l1.go = "whiskey_1";
		break;
		
		case "whiskey_1":
			dialog.text = "Nos, igen. Ez furcsa?";
			link.l1 = "Nem, persze, hogy nem! Már napok óta keresem ôt, és kiderült, hogy nemrég járt itt. Meg tudná mondani, hová ment?";
			link.l1.go = "whiskey_2";
		break;
		
		case "whiskey_2":
			dialog.text = "Adolf Barbierrel volt, aki a 'Santa Florentinában'. lakik, talán oda tartottak.";
			link.l1 = "Köszönjük!";
			link.l1.go = "whiskey_3";
		break;
		
		case "whiskey_3":
			dialog.text = "Ha szüksége van egy kis arzénre, akkor húsz dublonért eladhatok egy üveggel.";
			link.l1 = "Rendben. Majd késôbb megbeszéljük, Sancho. Viszlát!";
			link.l1.go = "whiskey_4";
		break;
		
		case "whiskey_4":
			DialogExit();
			pchar.questTemp.Saga.SharkHunt = "whiskey_poison"; // флаг - виски травят
			AddQuestRecord("SharkHunt", "37");
			sld = CharacterFromID("LSC_Adolf");
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "SantaFlorentinaShipInside4", "goto", "goto2");
			sld = CharacterFromID("Dodson");
			sld.dialog.currentnode = "whiskey"; // ноду Акуле
			// важный момент! От дальнейшего поведения геймера зависит результат
			pchar.quest.LSC_Whiskeypoison_SF.win_condition.l1 = "location";
			pchar.quest.LSC_Whiskeypoison_SF.win_condition.l1.location = "SantaFlorentinaShipInside4";
			pchar.quest.LSC_Whiskeypoison_SF.function = "LSC_WhiskeyPoison_SF"; // прерывание на Санта-Флорентину
			pchar.quest.LSC_Whiskeypoison_AE.win_condition.l1 = "location";
			pchar.quest.LSC_Whiskeypoison_AE.win_condition.l1.location = "AvaShipInside3";
			pchar.quest.LSC_Whiskeypoison_AE.function = "LSC_WhiskeyPoison_AE"; // прерывание на Эву
			pchar.quest.LSC_Whiskeypoison_exit.win_condition.l1 = "location";
			pchar.quest.LSC_Whiskeypoison_exit.win_condition.l1.location = "LostShipsCity_town";
			pchar.quest.LSC_Whiskeypoison_exit.function = "LSC_Whiskeypoison_exit"; // прерывание на выход из таверны
			// закрываем вход к Фацио
			LocatorReloadEnterDisable("LostShipsCity_town", "reload20", true);
			LocatorReloadEnterDisable("LostShipsCity_town", "reload24", true);
		break;
		
		// пей до дна
		case "drunk_fail":
			dialog.text = "Gyerünk, haver! Nem tartozol nekem semmivel.  Már elvesztettél száz dublont. Hiba volt Fazióval üzletelni...";
			if (sti(pchar.money) >= 500)
			{
				link.l1 = "Nem, nem, Sancho! Köszönöm, és kérem, vegye el ezt az ötszáz pezót. Ez fedezi az italok árát, ha jól emlékszem. Nem akarok az adósod lenni.";
				AddMoneyToCharacter(pchar, -500);
			}
			else link.l1 = "Eh, köszönöm, Sancho. Igazad van.";
			link.l1.go = "exit";
			DeleteAttribute(npchar, "quest.drink");
		break;
		
		case "drunk_win":
			DialogExit();
			TakeNItems(pchar, "gold_dublon", 200);
			Log_Info("Kaptál 200 dublont.");
			PlaySound("interface\important_item.wav");
			DeleteAttribute(npchar, "quest.drink");
		break;
		
		// крабовый салат
		case "crab":
			dialog.text = "Hm... akkor van egy ajánlatom számodra. Láttál ott óriásrákokat?";
			link.l1 = "Láttam-e rákokat? Hordaszámra voltak ott! És milyen javaslatról beszélsz?";
			link.l1.go = "crab_1";
		break;
		
		case "crab_1":
			dialog.text = "Ha megölsz néhány rákot, feltétlenül hozd el nekem a karmokat. Jól megfizetlek dublonokban - öt érmét adok mindegyikért. Axel Yost nem fog ennyit fizetni, hidd el nekem. Nem kérem, hogy rákokra vadásszatok ezért a feladatért - de ha akadna néhány, kérlek, ezt tartsátok észben...";
			link.l1 = "Miért karom? Mi a helyzet a rák többi részével? Mit csinálsz azokkal?";
			link.l1.go = "crab_2";
		break;
		
		case "crab_2":
			dialog.text = "Miért karom? Mert a hús nagy része rajtuk van. A rákok lábain nem sok hús van, és a testüket szilárd páncél borítja. A rákhús itt csemege, kitûnô íze van, és nagyon tápláló\nEgyedi receptem is van hozzá, ezért öt dublont fizetek neked minden egyes csípésért.";
			link.l1 = "Rendben. Ezt észben tartom.";
			link.l1.go = "crab_3";
		break;
		
		case "crab_3":
			DialogExit();
			npchar.quest.crab = "current";
		break;
		
		case "crab_trade":
			iTotalTemp = GetCharacterItem(pchar, "crab_pincers")
			dialog.text = "Pompás! Hány darab van belôle?";
			link.l1 = ""+FindRussianQtyString(iTotalTemp)+".";
			link.l1.go = "crab_trade_1";
			link.l2 = "Meggondoltam magam.";
			link.l2.go = "exit";
		break;
		
		case "crab_trade_1":
			dialog.text = "Megegyeztünk. Tessék, itt vannak a dubloonok - "+FindRussianQtyString(iTotalTemp*5)+". Kösz, haver, ha lesz még, hozd el nekem.";
			link.l1 = "Persze, barátom.";
			link.l1.go = "crab_trade_2";
		break;
		
		case "crab_trade_2":
			DialogExit();
			RemoveItems(pchar, "crab_pincers", iTotalTemp);
			TakeNItems(pchar, "gold_dublon", iTotalTemp*5);
			PlaySound("interface\important_item.wav");
			Log_Info("Kaptál "+iTotalTemp*5+" dublont.");
		break;
		
		// крыс
		case "rat":
			dialog.text = "Mi van?! Mutasd meg! Hadd lássam!";
			link.l1 = "Persze.";
			link.l1.go = "rat_1";
		break;
		
		case "rat_1":
			PlaySound("interface\important_item.wav");
			dialog.text = "Ez az... Tényleg az! Pontosan olyan, mint a képen, amit egy tengerész rajzolt nekem! Barátom, biztos van valami oka, hogy ezt elhoztad nekem, mit akarsz érte? Mennyit?";
			link.l1 = "Persze, hogy okkal hoztam neked. De a jutalomért mit tudsz ajánlani? Ha jól emlékszem, királyi jutalmat ígértél nekem ezért a dologért...";
			link.l1.go = "rat_2";
			link.l2 = "Sajnálom, haver, ez nem eladó. Nekem magamnak kell. Csak biztos akartam lenni benne, hogy ez az a talizmán, amirôl beszéltél.";
			link.l2.go = "rat_exit";
		break;
		
		case "rat_exit":
			PlaySound("interface\important_item.wav");
			dialog.text = "Eh, milyen kár... Igen, fiam, ez pontosan az a talizmán. Szerencsés ördög! Most már a patkányok nem fognak több gondot okozni neked. Nekem pedig arzénnel kell majd irtanom ôket...";
			link.l1 = "Sajnálom, hogy ugratlak, Sancho. Még soha nem láttam ilyet, ezért szükségem volt egy konzultációra. Bocsáss meg.";
			link.l1.go = "exit";
			DeleteAttribute(npchar, "quest.rat");
		break;
		
		case "rat_2":
			dialog.text = "Ezért,"+pchar.name+", felajánlom Önnek a lehetôséget, hogy megvásárolja a legjobb és legértékesebb tárgyat, amivel rendelkezem. Kiváló csere lenne ez a bûbáj, különösen egy olyan bátor harcosnak, mint te. Hadd hozzam el neked.\nNézd meg: itt van egy egyedi, pompás milánói Cuirass, aprólékosan megmunkálva! Kivételes védelmet nyújt a harcban, korlátlan mozgást tesz lehetôvé, ráadásul könnyû és kényelmes. Az ilyen minôségû páncélok ritkaságszámba mennek mind a Karib-tengeren, mind Európában.\nEgy spanyol hadihajó kapitányi kabinjában bukkantam erre a cuirassra néhány évvel ezelôtt, és pontosan egy ilyen alkalomra ôriztem meg. Kétezer aranypénzért és a Patkányistenért hajlandó vagyok eladni neked!";
			link.l1 = "Hmm... Ez egy kiváló öltözet! Azt hiszem, ez a csere megfelel nekem. Majd kitalálom a patkány helyzetet, de egy másik ilyen cuirass-t találni szinte lehetetlen lenne. Még sosem láttam ehhez hasonlót. Valóban, ez egy egyedülálló páncél.";
			link.l1.go = "rat_yes";
			link.l2 = "Mennyibe kerül? Sancho, a patkányaid már megharaptak párszor ma reggel? Hogy érted, hogy kétezer? Tudod egyáltalán, hogy mibe került, hogy megszerezzem neked ezt a bálványt? Dobd le az árat most azonnal!";
			link.l2.go = "rat_torg";
			link.l3 = "Mennyi?! Te egy cápa vagy, ugye tudod, Sancho? 'Vásárlási lehetôség!' Ha! Ennyi pénzért olyan páncélt rendelhetnék magamnak a szárazföldön, ami eltereli a golyókat és ráadásul gyógyít is! És mire kell ennyi arany? Hogy Jurgen öntse neked a saját szobrodat, és teljes magasságban kiállítsa 'San Agustin'?";
			link.l3.go = "rat_no";
		break;
		
		case "rat_yes":
			dialog.text = "Örülök, hogy a fedélzeten vagy, barátom. Köszönöm, hogy nem feledkeztél meg a problémámról! Szóval, várom a dublonjaimat. A páncél várni fog rád.";
			link.l1 = "Hamarosan átviszem ôket!";
			link.l1.go = "rat_yes_1";
		break;
		
		case "rat_yes_1":
			DialogExit();
			DeleteAttribute(npchar, "quest.rat");
			npchar.quest.ratmoney = 2000;
		break;
		
		case "rat_torg":
			if(GetSummonSkillFromName(pchar, SKILL_COMMERCE) < 60)
			{
				Notification_Skill(false, 60, SKILL_COMMERCE);
				dialog.text = ""+pchar.name+", más körülmények között ötezret kérnék. Maga az admirális is érdeklôdést mutatott, és nem egyedül, higgye el. Ne siessenek a döntéssel. A páncélok addig várnak rád, ameddig szükséged van rá. Én csak neked adom el.";
				link.l1 = "Majd meggondolom, Sancho. Hosszan és alaposan átgondolom.";
				link.l1.go = "rat_yes_1";
				AddCharacterExpToSkill(pchar, "Commerce", 400);
			}
			else
			{
				Notification_Skill(true, 60, SKILL_COMMERCE);
				dialog.text = ""+pchar.name+", más körülmények között ötezret kérnék. Maga az admirális is érdeklôdést mutatott, és nem ô az egyetlen, higgye el nekem. Rendben, levonok ötszázat, tekintve, hogy nem feledkeztél meg rólam és a problémámról. Úgy tûnik, volt néhány kaland az út során.";
				link.l1 = "Így már jobb. De még mindig nem értem, miért kellene többet fizetnem az ugyanolyan egyedi tárgyak kereskedelmében. Talán neked kéne fizetned nekem, nem Sancho?";
				link.l1.go = "rat_yes_1500";
				AddCharacterExpToSkill(pchar, "Commerce", 100);
			}
		break;
		
		case "rat_yes_1500":
			if(GetSummonSkillFromName(pchar, SKILL_COMMERCE) < 90)
			{
				Notification_Skill(false, 90, SKILL_COMMERCE);
				dialog.text = "Nem, "+pchar.name+", nem fog megtörténni. A patkányokat el tudom intézni méreggel, de ez a páncél egy nap megmentheti az életed. És úgy fogsz kinézni benne, mint egy olasz herceg. Ezerötszáz, ez az utolsó ajánlatom. Gondolja át nyugodtan, és majd szóljon nekem. A páncél addig vár rád, amíg szükséged van rá, csak neked adom el.";
				link.l1 = "Sancho, ha nem te lennél az egyetlen kocsmáros ebben a sivár temetôben... Meggondolom az ajánlatodat.";
				link.l1.go = "rat_yes_1500exit";
				AddCharacterExpToSkill(pchar, "Commerce", 600);
			}
			else
			{
				Notification_Skill(true, 90, SKILL_COMMERCE);
				dialog.text = "Ahhoz képest, hogy katonai kapitány és kalóz, te aztán tudsz tárgyalni! Emlékszel Jostra? Egyszer sikerült neki kedvezményesen megvennie az összes arzénemet, miközben a patkányok már kínoztak. Rendben, "+pchar.name+", te nyertél. Lecsapok még ötszázat neked! De ez az utolsó ajánlatom!";
				link.l1 = "Ez még mindig úgy érzem, mintha átverés lenne, de legalább most már nem fogom magam tipikus bajba jutott kislánynak érezni a dzsungelben. Várj a pénzre, hamarosan hozom.";
				link.l1.go = "rat_yes_1000exit";
				AddCharacterExpToSkill(pchar, "Commerce", 200);
			}
		break;
		
		case "rat_no":
			dialog.text = "Nyugodj meg, "+pchar.name+". Valaki mástól ötezret követelnék! Maga az admirális is érdeklôdést mutatott, és nem egyedül van, hidd el. A páncél addig vár rád, ameddig szükséges. Ez is benne van a bálvány árában.";
			link.l1 = "Micsoda megtiszteltetés! Törölgesse csak tovább a szemüvegét, én pedig máris indulok. Kétezer!";
			link.l1.go = "rat_yes_1";
		break;
		
		case "rat_yes_1500exit":
			DialogExit();
			DeleteAttribute(npchar, "quest.rat");
			npchar.quest.ratmoney = 1500;
		break;
		
		case "rat_yes_1000exit":
			Achievment_SetStat(106, 1);
			DialogExit();
			DeleteAttribute(npchar, "quest.rat");
			npchar.quest.ratmoney = 1000;
		break;
		case "rat_3":
			dialog.text = "Kész! Örülök, hogy beleegyeztél, haver. Köszönöm, hogy nem felejtetted el a problémámat! Fogd a mellvértet, és szolgáljon jól a csatában.";
			link.l1 = "Tessék, vidd a talizmánt is - úgy tûnik, sötét napok jönnek a kocsmád patkányaira!";
			link.l1.go = "rat_4";
		break;
		
		case "rat_4":
			DialogExit();
			GiveItem2Character(pchar, "cirass4");
			RemoveItems(pchar, "talisman1", 1);
			RemoveDublonsFromPCharTotal(sti(npchar.quest.ratmoney));
			Log_Info("Elajándékoztad a talizmánt 'Patkányok istene...'");
			Log_Info("Kaptál egy milánói páncélt");
			Log_Info("Adtál... "+FindRussianDublonString(sti(npchar.quest.ratmoney))+"");
			PlaySound("interface\important_item.wav");
			DeleteAttribute(npchar, "quest.ratmoney");
			if(CheckAttribute(npchar, "quest.ratmoneyagain"))
				DeleteAttribute(npchar, "quest.ratmoneyagain");
		break;
		
		case "rat_take_money_not_all":
			npchar.quest.ratmoney = sti(npchar.quest.ratmoney) - PCharDublonsTotal();
			Log_Info("Adtál... "+FindRussianDublonString(PCharDublonsTotal())+"");
			RemoveDublonsFromPCharTotal(PCharDublonsTotal());
			PlaySound("interface\important_item.wav");
			dialog.text = "Még mindig félsz tôlem "+FindRussianDublonString(sti(npchar.quest.ratmoney))+", "+pchar.name+".";
			link.l1 = "Ne emlékeztess rá!";
			link.l1.go = "exit";
		break;
		
		//--> информационный блок
		case "int_quests":
			dialog.text = "Hallgatlak.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Mi ez a hely? Tudnál többet mondani róla?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Hogyan hagyhatom el a szigetet?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Mit kell tudnom a szigetrôl?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "És te hogy vagy itt? Milyen a kocsmád?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Nekem nincsenek kérdéseim...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Ez a hely? Hát, úgy hívják, hogy az Igazság Szigete, az Elhagyott Hajók Szigete, vagy az Elhagyott Hajók Városa - de mi csak Szigetnek hívjuk. Hajókból' roncsokból alakult ki, amelyek a zátonyok között egy zátonyon rekedtek. A Sziget középsô része lakott terület, a külsô gyûrû lakatlan. Tíz éve nincs kapcsolat a külvilággal.";
			link.l1 = "Megvan...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Építs egy hosszú csónakot vagy tutajt. De ez nem fog jól végzôdni számodra. A sziget körül anomáliás viharzóna van, a külsô gyûrûn nem fogsz átjutni anélkül, hogy életed kockáztatnád. Ráadásul a szigetet erôs áramlás keringeti\nSzükséged van egy csapatra, hogy akár csak csekély esélyed legyen a túlélésre. És nagyon kevés helybéli hajlandó elhagyni ezt a helyet. Még kevesebben hajlandóak kockázatot vállalni. Az emberek szeretnek itt élni. Kérdezzen körül, ha nem hisz nekem.";
			link.l1 = "Értem...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Elôször is, ne feledje, hogy a szigeten több korlátozott terület is van. Két klán - a narválok és a rivadók - már régóta élnek itt, harcolnak egymással, és félelmet nem ismerve védik a sajátjuknak tekintett területeket. Próbáld meg hívatlanul meglátogatni ôket, és halott ember vagy\nAz aktuális jelszót kell tudnod, ha be akarsz lépni a területükre. Ne aggódj, ha véletlenül kerülsz oda, az ôrök többször figyelmeztetnek, mielôtt lövöldözni kezdenének.";
			link.l1 = "Ezt majd észben tartom...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Tudod, barátom, minden rendben van. Régebben ételekkel és italokkal dolgoztam: Régen szakácsként dolgoztam Európában, voltam intendáns egy helyôrségben, kocsmáros és szakács egy hajón; így az elsô dolog, amit itt csináltam, egy kocsma alapítása volt\nszeretem a munkámat, és az életem furcsán kielégítô. Az emberek barátságosak itt, többnyire. Legalábbis nem ölik egymást gyakran. A klánok nem zavarják a tevékenységemet. Mindent összevetve, ez a legjobb hely az életemben. Itt szabad vagyok, és senki sem mondja meg, hogy mit csináljak\nAz egyetlen dolog, ami az ôrületbe kerget, azok a patkányok. Kínoznak, megeszik az élelmiszereimet és tönkreteszik az edényeimet. Nehezen szabadulok meg tôlük.";
			link.l1 = "Patkányok? Igen, mindenkinek gondot okoznak...";
			link.l1.go = "ansewer_4_1";
		break;
		
		case "ansewer_4_1":
			dialog.text = "Sajnos én vagyok itt a legszerencsétlenebb ember, ha patkányokról van szó. Más hajókat nem terrorizálnak ennyire a patkányok, és Axel Yostnak valahogy sikerült egyszer és mindenkorra leszámolnia velük. Ami engem illet, itt patkányok seregei mászkálnak. Eh, azt mondták nekem, hogy van egy különleges amulett, a Patkányisten.\nÚgy néz ki, mint egy denevér arcmaszk. Azt mondják, hogy ez az amulett szarrá ijeszti a patkányokat. Gondolom, valaki eladta Axelnek ezt az amulettet, minden szemetet, amit a külsô gyûrûn talál, megvásárol és újra elad\nKívánom, bárcsak valaki elhozná nekem az amulettet, királyi jutalmat ajánlok fel annak a személynek!";
			link.l1 = "Érdekes...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
			npchar.quest.rat = "true";
		break;
		//<-- информационный блок
		
		//--> выпивка
		case "drink":
			if (CheckAttribute(pchar, "questTemp.Rum") && sti(pchar.questTemp.Rum) > 4)
			{
				dialog.text = ""+pchar.name+", úgy gondolom, hogy abba kellene hagynod. Isten ments, hogy bajba kerülj, vagy átesel a tengerbe, hogy rákok legyenek' meal... Errefelé nem jó ötlet túl sokat inni, sokan meghaltak emiatt.";
				link.l1 = "Hm... Azt hiszem, igazad van, Sancho - már így is eleget ittam. Köszönöm az aggodalmadat!";			
				link.l1.go = "exit";
			}
			else
			{
				AddMoneyToCharacter(pchar, -25);
				if(!IsEquipCharacterByArtefact(pchar, "totem_01"))
				{
					if (CheckAttribute(pchar, "questTemp.Rum"))
					{
						pchar.questTemp.Rum = sti(pchar.questTemp.Rum) + 1;
					}
					else pchar.questTemp.Rum = 1;
				}
				else 
				{
					if(CheckAttribute(pchar, "questTemp.Rum")) DeleteAttribute(pchar, "questTemp.Rum");
				}				
				WaitDate("",0,0,0, 0, 30);
				
				dialog.text = "Szívesen, haver. Csak huszonöt pezó a legjobb rumomért!";
				link.l1 = RandPhraseSimple(LinkRandPhrase("Nos, egészségedre és a kocsmád jólétére, pajtás!","Nos, azoknak, akik a tengeren vannak!","Jót a szigetetek lakóinak!"), LinkRandPhrase("Nos, a Szigetre, és maradjon meg örökké!","Nos, legyen a szél mindig kedvezô minden tettünkben!","Nos, a szerencsére, a boldogságra és... a nôkre!"));		
				link.l1.go = "drink_1";
			}
		break;
		
		case "drink_1":
			DialogExit();
			LAi_Fade("", "");
			if (CheckAttribute(pchar, "questTemp.Rum"))
			{
				if (sti(pchar.questTemp.Rum) < 3) LAi_AlcoholSetDrunk(pchar, 51, 5600);
				else LAi_AlcoholSetDrunk(pchar, 71, sti(pchar.questTemp.Rum)*2800);
			}
		break;
		
		case "drink_sit":
			if (chrDisableReloadToLocation || pchar.questTemp.Saga.SharkHunt == "barmen_whiskey" || pchar.questTemp.Saga.SharkHunt == "whiskey_poison") //идёт квест
			{
				dialog.text = "Nem hiszem, hogy jó ötlet lenne most inni. Bízz bennem...";
				link.l1 = "Rendben.";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LSC.MaryBye") || CheckAttribute(pchar, "questTemp.LSC.MaryWait")) // подружился с Мэри
			{
				dialog.text = "Heh, te egy furcsa ember vagy... Nincs senkid, akivel elüthetnéd az idôt itt, a Szigeten? Haver, Mary megöl, ha hagyom, hogy itt maradj és egyedül rúgj be. Gyertek ide este, és szórakozzatok együtt hajnalig, ha akarjátok.";
				link.l1 = "Rendben...";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Semmi gond, haver. Mindössze háromszáz pezóért kap egy finom üveg "+LinkRandPhrase("spanyol","olasz","francia")+" bort - és addig szórakozik, amíg csak akar.";
				link.l1 = "Köszönjük!";
				link.l1.go = "drink_sit_1";
			}
		break;
		
		case "drink_sit_1":
			DialogExit();
			sld = ItemsFromID("potionrum");
			sld.shown = true;
			sld.startLocation = "FleuronTavern";
			sld.startLocator = "bottle";
			DoQuestReloadToLocation("FleuronTavern", "quest", "sit2", "LSC_DrinkSit");
		break;
		//<-- выпивка
		
		//--> сон в таверне
		case "room":
   			if (chrDisableReloadToLocation || pchar.questTemp.Saga.SharkHunt == "barmen_whiskey" || pchar.questTemp.Saga.SharkHunt == "whiskey_poison") //идёт квест
			{
				dialog.text = "Nem hiszem, hogy most aludnod kéne. Bízz bennem...";
				link.l1 = "Rendben.";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LSC.MaryBye") || CheckAttribute(pchar, "questTemp.LSC.MaryWait")) // подружился с Мэри
			{
				if(!isDay())
				{
					dialog.text = "Soha nem találkoztam még ilyen furcsa emberrel. Egy gyönyörû lány várja ôt a 'Ceres kovácsmûhelyben' és a kocsmában fogja tölteni az éjszakát. Ne is gondolja, hogy hagyom, hogy itt aludjon. Mary ezért meg fog ölni.";
					link.l1 = "Rendben...";
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = "Pihenhetsz az emeleten estig. De nem hagyom, hogy itt töltsd az éjszakát - Mary ezért megölne. Sajnálom...";
					link.l1 = "Jól van. Itt maradok estig...";
					link.l1.go = "hall_night_wait";
					link.l2 = "Rendben... Megoldom alvás nélkül is.";
					link.l2.go = "exit";
				}
				break;
			}
			dialog.text = "Alhatsz az emeleti ágyban, csak húsz pezóért. Mikor ébresszelek fel?";
			if(!isDay())
			{
				link.l1 = "Reggel.";
				link.l1.go = "hall_day_wait";
			}
			else
			{
				link.l1 = "Mielôtt besötétedik.";
				link.l1.go = "hall_night_wait";
				link.l2 = "Másnap reggel.";
				link.l2.go = "hall_day_wait";
			}
			link.l3 = "Meggondoltam magam. Nem akarok aludni.";
			link.l3.go = "exit";
		break;
		
		case "hall_night_wait":
			AddMoneyToCharacter(pchar, -20);
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			TavernWaitDate_LSC("wait_night");
		break;
		
		case "hall_day_wait":
			AddMoneyToCharacter(pchar, -20);
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			TavernWaitDate_LSC("wait_day");
		break;
		//<-- сон в таверне
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}
