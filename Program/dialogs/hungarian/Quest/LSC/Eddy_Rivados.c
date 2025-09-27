// лидер клана ривадос - Чёрный Эдди
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Mit csinálsz Rivados' territóriumon, fehér ember?";
			link.l1 = "Csak ismerkedem a helyiekkel. Elnézést, ha zavartalak.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "Friend":
			dialog.text = "Örülök, hogy üdvözölhetem Rivados barátját és jó emberét is! Chimiset elmondta, mit tettél érte. Minden Rivados, beleértve engem is, az adósod. Engedd meg, hogy bemutatkozzam - Edward Black, más néven Fekete Eddie, a Rivados banda feje.";
			link.l1 = ""+GetFullName(pchar)+". Bár azt hiszem, Chimiset már mesélt rólam. Megígérte, hogy elmondja neked...";
			link.l1.go = "Friend_1";
		break;
		
		case "Friend_1":
			dialog.text = "És meg is tette. Most már szabadon látogathatod a hajóinkat. Az ôrök nem fognak megállítani, és mi örülni fogunk, ha látunk. Vigyázz a narválokkal, már biztosan rájöttek, hogy megmentetted Chimisetet, és ez nem fog nekik tetszeni, hiszen ellenségek vagyunk.";
			link.l1 = "Megfontolom. Köszönöm a meleg fogadtatást, Eddie! Most pedig kérem, engedje meg, hogy beszéljek Chimiset-tel.";
			link.l1.go = "Friend_2";
		break;
		
		case "Friend_2":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "goto", "goto1", "LSC_EddyStay", -1);
			AddSimpleRumourCityTip("Azt mondják, hogy ön közeli barátja Fekete Eddie-nek, Rivados vezetôjének. Hogy csinálta ezt?", "LostShipsCity", 10, 1, "LSC", "");
			AddSimpleRumourCityTip("A Rivadosok azt állítják, hogy a barátjuk vagy. Hogy csináltad?", "LostShipsCity", 10, 1, "LSC", "");
			AddSimpleRumourCityTip("Azt mondják, hogy a narválok vérdíjat tûztek ki a fejedre. Megijedtél?", "LostShipsCity", 10, 1, "LSC", "");
		break;
		
		// --> информационный блок
		case "Total_info": // стал другом
			if (pchar.questTemp.LSC == "return" && !CheckAttribute(npchar, "quest.return_isl"))
			{
				dialog.text = "Fehér testvér? Él? Örülök! Szóval a narválok hazudtak, amikor azt mondták, hogy megfulladtál...";
				link.l1 = "Én is örülök, hogy látlak, Eddie. A halálomról szóló pletykák erôsen eltúlzottak.";
				link.l1.go = "exit";
				npchar.quest.return_isl = "true";
				break;
			}
			dialog.text = "Örülök, hogy látlak, "+pchar.name+". Van valami hír?";
			if (!CheckAttribute(npchar, "quest.natan"))
			{
				link.l1 = "Eddie, ismersz egy Nathaniel Hawk nevû embert? Itt kell lennie, amennyire én tudom.";
				link.l1.go = "natan";
			}
			if (!CheckAttribute(npchar, "quest.rivados"))
			{
				link.l2 = "Mesélj még a Rivados bandáról.";
				link.l2.go = "rivados";
			}
			link.l9 = "Semmi különös, tényleg. Csak köszönni akartam.";
			link.l9.go = "exit";
		break;
		
		case "natan":
			dialog.text = "Nathaniel Hawk? Nem, nem ismerem ezt az embert. Nincs sem a Rivados hajóin, sem a semleges területen. Ugyanezt nem mondhatom el a Narvál bandáról, nem látogatjuk ôket.";
			link.l1 = "Értem...";
			link.l1.go = "exit";
			npchar.quest.natan = "true";
			NextDiag.TempNode = "Total_info";
		break;
		
		case "rivados":
			dialog.text = "A Rivados bandát sok évvel ezelôtt alapították. Ez volt a legelsô klán az Elhagyott Hajók Városában. Több mint ötven évvel ezelôtt Betancourt admirális expedíciója több nagy rabszolgahajóval hajózott ide Nyugat-Afrikából. A Tartarus rakterét több száz fekete rabszolga töltötte meg, akiket a karibi ültetvényekre vittek. A rabszolgák között volt egy Pedro Rivados nevû férfi, akit néhány portugál pap megtanított írni és olvasni\nElérte, hogy néhány tucat rabszolgát kiszabadítson a bilincsekbôl, és lázadást szított. Sajnos a többi rabszolga nem csatlakozott hozzá. A lázadást leverték. A rabszolgatartók kézzel-lábbal megkötözték Rivadost, és a hajó rakterében hagyták, hogy éhen és szomjan pusztuljon. Néhány nappal késôbb az idôjárás rosszra fordult, és Betancourt hajóraját hatalmas vihar söpörte el.\nNapokkal késôbb, miután megküzdöttek az idôjárással, a 'San Augustine' és a 'Tartarus', az egyetlen két még ép hajó a sziget közepén rekedt. Rengeteg ember halt meg ezekben az eseményekben, feketén-fehéren, de sokkal többnek sikerült túlélnie. A volt rabszolgák együtt kezdtek új életet, és Pedro Rivados, a felszabadító tiszteletére Rivadosnak nevezték el magukat.";
			link.l1 = "Nagyon érdekes történet... Köszönjük!";
			link.l1.go = "exit";
			npchar.quest.rivados = "true";
			NextDiag.TempNode = "Total_info";
		break;
		// <-- информационный блок
		
		case "capper":
			dialog.text = "Mi szükséged van Rivados' territóriumokra, fehér ember?";
			link.l1 = "A nevem "+GetFullName(pchar)+" és Dodson admirális parancsára vagyok itt. Beszélnem kell Fekete Eddie-vel. Ha jól tudom, ön az.";
			link.l1.go = "capper_1";
		break;
		
		case "capper_1":
			dialog.text = "Igen, Edward Black vagyok, más néven Fekete Eddie. Mondd meg, mit akar tôlem az admirális.";
			link.l1 = "Van egy ember a 'Tartarus' nevû Chimiset. Az admirális hajlandó kiszabadítani ôt.";
			link.l1.go = "capper_2";
		break;
		
		case "capper_2":
			dialog.text = "Ez nagyon jó hír. Chimiset a szellemi vezetônk, és minden Rivadosnak hiányzik. De úgy tudom, hogy az admirális kér valamit a szabadságáért cserébe, igaz?";
			link.l1 = "Semmit. Csak jóakaratból akarja kiszabadítani ôt. De van egy probléma...";
			link.l1.go = "capper_3";
		break;
		
		case "capper_3":
			dialog.text = "Gyerünk, fehér ember.";
			link.l1 = "Az admirális volt hajóskapitánya, a jelenlegi börtönôr, Chad Kapper csatlakozott a Narwhalokhoz, gazemberré vált, és most már nincs az admirális ellenôrzése alatt. Tudjuk, hogy Chad azt tervezi, hogy megöli Chimiset. Az admirális nem akarja, hogy ez megtörténjen. Felajánlunk egy közös akciót az áruló likvidálására és az emberük kiszabadítására.";
			link.l1.go = "capper_4";
		break;
		
		case "capper_4":
			dialog.text = "Kicsit furcsán hangzanak a szavai, de folytassa. Chimiset bajban van?";
			link.l1 = "Igen. Chad azt tervezi, hogy megöli ôt. Kapper a narválokat fogja felhasználni, hogy átvegye a város feletti uralmat. Gyorsan kell cselekednünk, ha meg akarjuk menteni Chimiset, mivel Chad egyelôre nem sejt semmit. Admirális az összes ôrt elvette a 'Tartarus', az átjáró szabad. Itt van a kulcs, amely kinyitja az ajtót a börtön belsejében. Vedd el.";
			link.l1.go = "capper_5";
		break;
		
		case "capper_5":
			RemoveItems(pchar, "key_capper", 1);
			dialog.text = "";
			link.l1 = "Gyûjtsd össze az embereidet, menj a Tartaroszba és szabadítsd ki Chimiset-et. Minden kártya a tiéd.";
			link.l1.go = "capper_6";
		break;
		
		case "capper_6":
			dialog.text = "Csapda szaga van... És mi van, ha csapda van? Mi van, ha az admirális úgy döntött, hogy lecsap a Rivadosra? Miért nem akar maga foglalkozni Kapperrel?";
			link.l1 = "Dodson azt mondta, hogy törôdsz Chimiset életével... Eleget tett: ott a kulcs, és az ôrök eltûntek. Már csak be kell jutnod, elintézni Chad-et és kiszabadítani az emberedet. A szavamat adom, hogy nincs csapda. Igen, és még egy utolsó dolog: az admirális Chad fejét akarja Chimiset életéért és szabadságáért cserébe. Megegyeztünk?";
			link.l1.go = "capper_7";
		break;
		
		case "capper_7":
			dialog.text = "Chimiset életét a Rivadók mérhetetlenül nagyra értékelik. Azonnal a 'Tartarosz' megyünk. De te itt maradsz, mint a túszunk. És ha rajtaütés történik, a Rivadók dühével kell szembenézned!\nZikomo! Maradj az ajtó közelében, és figyeld a vendégünket. Ne engedd ki. Én fogom vezetni a támadást a 'Tartarus' maga ellen!";
			link.l1 = "Sok szerencsét, Eddie. És ne feledd: szükségem van Chad Kapper fejére!";
			link.l1.go = "capper_8";
		break;
		
		case "capper_8":
			DialogExit();
			chrDisableReloadToLocation = true;//закрыть локацию
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "LSC_ZikomoNearDoor", 10.0);
			NextDiag.CurrentNode = "chimiset";
		break;
		
		case "chimiset":
			dialog.text = "Chimiset szabad! Nem hazudtál, fehér ember, készen állok arra, hogy a Rivados barátjának nevezzelek!";
			link.l1 = "Örülök neki. Chad Kapper halott?";
			link.l1.go = "chimiset_1";
		break;
		
		case "chimiset_1":
			dialog.text = "Bocsánatodat kell kérnem, fehér barátom: mindent megtettél értünk, amit tudtál, de mi cserbenhagytunk... Cserbenhagytalak titeket! Az az átkozott Kapper megszökött. Két narvál volt vele. Megöltük ôket, de a mocskos börtönôr elúszott az alsó ajtón át a narválok területére.";
			link.l1 = "Baszd meg... Nem tudtad, hogy két kijárat van a 'Tartarus'?ból?";
			link.l1.go = "chimiset_2";
		break;
		
		case "chimiset_2":
			dialog.text = "Nem gondoltunk rá. A fôbejáraton keresztül támadtunk...";
			link.l1 = "Kár. Számítottam a fejére. Kár érte. Most már tovább fog cselekedni ellenünk.";
			link.l1.go = "chimiset_3";
		break;
		
		case "chimiset_3":
			dialog.text = "Elismerem a bûnömet. De nem követhettük ôt az ellenséges hajókhoz. A barátságunk és a tiszteletünk a tiéd lesz Chad feje helyett. Mostantól szabadon látogathatod a területünket. Chimiset bölcsessége is jó szolgálatot fog tenni nektek, beszéljetek vele, ha bármire szükségetek van. Beszélj vele, ha szükséged van rá. Továbbá, mondd meg az admirálisnak, hogy biztosítom, nagyra értékelem a tettét.";
			link.l1 = "Rendben.";
			link.l1.go = "chimiset_4";
		break;
		
		case "chimiset_4":
			dialog.text = "Várjatok! Elvesztettük Chadot, de találtam néhány papírt az asztalán, amit éppen tanulmányozott, amikor megérkeztünk. Itt vannak. Talán hasznosnak találod ôket, fehér testvér.";
			link.l1 = "Ha! Talán... Chad nagyon bízik a papírban...";
			link.l1.go = "chimiset_5";
		break;
		
		case "chimiset_5":
			dialog.text = "Mindig szívesen látott vendég vagy itt, fehér barátom. Minden rivadost tájékoztatni fogunk róla. Sok szerencsét!";
			link.l1 = "Neked is, Eddie...";
			link.l1.go = "chimiset_6";
		break;
		
		case "chimiset_6":
			DialogExit();
			LAi_ActorGoToLocator(npchar, "goto", "goto1", "LSC_EddyStay", -1);
			sld = CharacterFromID("Zikomo");
            LAi_SetWarriorType(sld);
			LAi_warrior_SetStay(sld, true);
			LAi_warrior_DialogEnable(sld, true);
			GiveItem2Character(pchar, "letter_chad");
			ChangeItemDescribe("letter_chad", "itmdescr_letter_aeva");
			GiveItem2Character(pchar, "letter_chad_1");
			ChangeItemDescribe("letter_chad_1", "itmdescr_letter_axel");
			pchar.questTemp.LSC.rvd_friend = "true"; //флаг на проход по кораблям ривадос
			// // ривадосы не будут останавливать где просят пароль
			pchar.questTemp.Saga.SharkHunt = "dodson_whiskey"; // к Акуле
			sld = CharacterFromID("Dodson");
			sld.dialog.currentnode = "Chad_escape"; // ноду Акуле
			AddQuestRecord("SharkHunt", "33");
			LocatorReloadEnterDisable("LostShipsCity_town", "reload48", true); // закрыть вход к Дональду Гринспи
			for (i=7; i<=12; i++)
			{
				sld = CharacterFromID("RivadosSold_"+i);
				LAi_SetWarriorType(sld);
				LAi_warrior_SetStay(sld, true);
			}
			for (i=4; i<=8; i++)
			{
				sld = CharacterFromID("RivadosProt_"+i);
				LAi_SetWarriorType(sld);
				LAi_warrior_SetStay(sld, true);
			}
			AddSimpleRumourCityTip("Hallotta a legfrissebb híreket? A Rivados' inzolencia elszabadult, megtámadták az admirális börtönét és kiszabadították a varázslójukat!", "LostShipsCity", 3, 2, "LSC", "");
			AddSimpleRumourCityTip("Gondolj csak bele - azok a pimasz rivadók meg merték támadni a 'Tartarus'! Azt mondják, hogy a börtönôr, Chad Kapper megszökött a Narwhalshoz...", "LostShipsCity", 3, 2, "LSC", "");
			AddSimpleRumourCityTip("Ez a szemtelenség csúcsa, nem igaz? Megtámadni az admirális katonai létesítményét! Igen, úgy tûnik, Fekete Eddie egyre erôsebb...", "LostShipsCity", 3, 2, "LSC", "");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}
