// Рамона Лоцано - горячая испанская сеньорита
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
				dialog.text = "Nem akarok veled beszélgetni. Ok nélkül békés civileket támadtok meg, és harcra provokáljátok ôket. Tûnjetek el!";
				link.l1 = "Hm...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Helló, helló! Újonc? Vagy a raktérben bujkáltál, hiszen most látom elôször az arcodat errefelé?";
				link.l1 = TimeGreeting()+". A raktérben bujkálás nem az én esetem. Jobban szeretem a kapitány helyét... Igen, újonc vagyok itt.";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, "+pchar.name+"! "+TimeGreeting()+"! Örülök, hogy látlak! Mit szólsz?";
				link.l1 = LinkRandPhrase("Van valami érdekes mondanivalód?", "Történt valami újdonság a szigeten?", "Elmondanád az utolsó pletykákat?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Szeretnék feltenni néhány kérdést a szigetrôl.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Csak tudni akartam, hogy vagy. Viszlát!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Nos, akkor ismerkedjünk meg egymással... kapitány. Ramona Lozano vagyok, de meg se próbáljon Senora Lozanónak hívni, utálom. És magát hogy hívják?";
			link.l1 = ""+GetFullName(pchar)+". Örülök, hogy megismerhetem, Ramona.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Tényleg elégedett vagy csak udvarias vagy, "+GetFullName(pchar)+"? Mondd csak, tényleg kapitány vagy csak vicceltél?";
			link.l1 = "Ó, mennyi kérdés egyszerre! Válaszolhatok rájuk sorrendben? Elôször is, tényleg örülök, nem minden nap találkozom csinos lányokkal, másodszor, kapitány vagyok, ez igaz. De a hajóm most a Nyugati-fô partjainak közelében van...";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "Vicces! És hogy is van ez, kapitány? Ön itt van, de a hajója a Main partjainak közelében van. Nem félsz, hogy a legénységed szétszéled, és a hajódat elveszik tôled?";
			link.l1 = "Egy bárkán hajóztam ide... felfedezôútra, de minden balul sült el, és a ti szigeteteken találtam magam. Aztán nekimentünk valami törmeléknek a sötétben, felborultunk és voilá! Itt vagyok. A hajóm addig vár rám, ameddig csak akarom. Dannie Hawk képes lesz irányítani az embereimet.";
			link.l1.go = "meeting_3";
		break;
		
		case "meeting_3":
			dialog.text = "Dannie Hawk? A Danielle Hawk? Azt akarod mondani, hogy vele lebegsz?";
			link.l1 = "A szar lebeg, Dannie a tisztemként szolgál engem. Ôt hagyták parancsnoknak, amíg én eltûntem... Honnan ismered ôt?";
			link.l1.go = "meeting_4";
		break;
		
		case "meeting_4":
			dialog.text = "Ha! A spanyol kolóniákon mindenki ismeri a kalóz Danielle Hawkot és férjét, Nathanielt. Igen, ön, senor "+GetFullName(pchar)+", biztosan kemény fickó... Akkor maga kalóz? Ne aggódjon, jól kijövök a fajtájával. Szeretem a kemény fickókat.";
			link.l1 = "Nos, én nem igazán vagyok kalóz... Jelenleg Jan Svensonnal dolgozom, és Dannie férjét, Nathanielt keresem.";
			link.l1.go = "meeting_5";
		break;
		
		case "meeting_5":
			dialog.text = "És most azt akarod mondani, hogy nem vagy kalóz? Az Erdei Ördögnek dolgozol, az elsô tiszted Dannie Hawk, és Nathan Hawkot keresed... és biztos vagyok benne, hogy az admirális miatt jöttél ide. Ugye?";
			link.l1 = "Ramona, hívhatsz kalóznak, ha akarsz, nekem megfelel. Hívhatsz horgonynak is, csak ne dobj a vízbe...";
			link.l1.go = "meeting_6";
		break;
		
		case "meeting_6":
			dialog.text = "Úgy tûnik, hogy te az igazán komoly srácok közé tartozol, "+pchar.name+". Rendben, mennem kell. Viszlát! Van egy olyan érzésem, hogy barátok lehetnénk... nagyon közeli barátok.";
			link.l1 = "Miért is ne? Sok szerencsét!";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Ó, tényleg? Nos, kérdezz, válaszolok, ha tudok...";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Hogy kerültél ide?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Biztos nem próbáltál még elszökni innen...";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Hogy élsz itt?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Mit csinálsz itt? Gondolom, az étel nem ingyen van, ugye?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Nincs kérdés. Elnézést...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Ez egy hosszú történet... A mostohaapámat kell hibáztatni. Négy évvel ezelôtt Havannában éltem, és el sem tudtam képzelni, hogyan alakulnak a dolgok számomra. Anyám meghalt, én pedig törvényes örökös voltam. Nem voltunk gazdagok, de rengeteg pénzünk volt, több mint elég a tisztességes megélhetéshez. A mostohaapámnak ez nem tetszett, és úgy döntött, hogy megszabadul tôlem\nAzt persze csak akkor tudtam meg, amikor két felbérelt verôlegény megtámadott közvetlenül a város kapuja mögött. Azok a bolondok maguk mondták el, ki bérelte fel ôket, hogy megöljenek, és miért. Szerencsére nem voltak profik, ha így lenne, már a bokrok között feküdtem volna elvágott torokkal. Az idióták úgy döntöttek, hogy elôbb szórakoznak egy kicsit\nA sors megmentett aznap, egy hozzád hasonló kapitány járt arra a kapu elôtt. Meglátta a mûsort, és azonnal megölte a söpredéket. Esélyük sem volt. Elmondtam neki, hogy mi történt velem és miért. Sírt egy kicsit... Tudta, hogy nincs hova mennem, ezért felvett a hajójára, hogy éljek. Elôször ideiglenesen, majd\nHiszem, hogy vele maradtam volna, de két hónappal késôbb egy ôrjárat ellen harcolt, elvesztette az árbocát, elkapott egy erôs szélvihar, és a külsô gyûrû alján találtam nyugalmat. Mindennek ellenére túléltem, és csatlakoztam a Sziget közösségéhez.";
			link.l1 = "Szomorú történet, nincs mit mondanom...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Természetesen nem. Mert ez lehetetlen. Láttam egy embert, aki megpróbálta elhagyni ezt a helyet egy hosszúhajón... két nap múlva visszatért. Egy árboc roncsához kötve, hogy megmentse magát a fulladástól. Kék volt és teljesen halott\nSzóval mondd meg, "+pchar.name+", mit kellene tennem, amint eljutok innen? Havanna túl veszélyes számomra, a mostohaapa megint megpróbál majd megölni. Nincs házam, nincs pénzem. Hová menjek? A bordélyházba?";
			link.l1 = "Még mindig vissza akarsz menni a szigetvilágba?";
			link.l1.go = "ansewer_2_1";
		break;
		
		case "ansewer_2_1":
			dialog.text = "És mit gondolsz? Persze, akarom. De ez lehetetlen, és épp most mondtam el, hogy miért. Eh, ha valaki elintézné a mostohaapámat... éles acéllal vagy golyóval, akkor lenne némi esélyem, hogy visszatérjek a normális életbe. De ki merné ezt megtenni, ha a mostohaapám a havannai alcalde legjobb barátja? És miért is beszélünk errôl? Innen nincs kiút...";
			link.l1 = "Majd meglátjuk. Eljön majd az idô...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
			// сюда направление на квест
		break;
		
		case "ansewer_3":
			dialog.text = "Valahogy túlélem. Nincs más lehetôség. A barátaim többnyire a férfiak, mert két házasulandó szépségünk - Gillian és Tanneke - nem kedvel engem a jellemem miatt, és rosszul érzem magam a látszatra való tisztességtôl. Natalie rendes lány volt, amíg nem kezdett sok idôt tölteni ezekkel a retardáltakkal, a hülyeség ragályos.";
			link.l1 = "Értem...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Úgy dolgozom, mint a többi lány. Az elsôdleges célunk a férfiak segítése. A szigeten sok munka van a nôknek, így eléggé elfoglalt vagyok. És gyakran kapok ajándékokat, ez itt a szokásos dolog. De ne gondolja rosszul rólam, hogy nem vagyok egy kislány. Jó nevelést kaptam egy rendes családban. Csak nem játszom a szentet, mint valaki más.";
			link.l1 = "Nem gondoltam, hogy bármi rosszat gondolok rólad...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Mit csinálsz ott, ah? Tolvaj!", "Csak nézd meg ezt! Amint elmerültem az elmélkedésben, úgy döntöttél, hogy megnézed a mellkasomat!", "Úgy döntöttél, hogy megnézed a ládámat? Ezt nem úszod meg!");
			link.l1 = "A francba!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Mi?! Úgy döntöttél, hogy megnézed a ládámat? Ezt nem úszod meg!";
			link.l1 = "Ostoba lány!";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//замечание по обнажённому оружию
		case "LSCNotBlade":
			dialog.text = LinkRandPhrase("Figyeljen, jobb, ha elveszi a fegyverét. Ideges leszek tôle.", "Tudod, a pengével való rohangálást itt nem tolerálják. Vidd el.", "Figyelj, ne játszd a középkori lovagot, aki karddal rohangál. Vidd el, nem illik hozzád...");
			link.l1 = LinkRandPhrase("Jól van.", "Persze.", "Ahogy mondod...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "Figyeljen, én a város polgára vagyok, és arra kérem, hogy tartsa vissza a pengéjét.", "Figyelj, a város polgára vagyok, és arra kérnélek, hogy tartsd vissza a pengédet.");
				link.l1 = LinkRandPhrase("Jól van.", "Persze.", "Ahogy mondod...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, "Légy óvatos, haver, amikor fegyverrel futsz. Ideges tudok lenni...", "Nem szeretem, ha a férfiak fegyverrel a kezükben sétálnak elôttem. Megijeszt...");
				link.l1 = RandPhraseSimple("Megvan.", "Elviszem.");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;
// <-- специальные реакции
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
