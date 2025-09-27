// Джиллиан Стайнер - просто девушка
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
				dialog.text = "Ó... helló! Megijesztettél. Olyan csendesen jöttél fel... Mit akarsz?";
				link.l1 = TimeGreeting()+". A nevem "+GetFullName(pchar)+". Én egy újonc vagyok itt, és kapok ismeri a helyiek és én végre úgy döntöttem, hogy jöjjön és beszélni az ilyen szép hölgy, mint te. Mi a neved?";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, "+GetFullName(pchar)+"! "+TimeGreeting()+"! Akarsz valamit?";
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
			dialog.text = "Elpirítasz, uram, de azért örülök neki. Köszönöm a bókot. A nevem Jillian, Jillian Steiner. Örülök, hogy megismerhetem.";
			link.l1 = "Én is, Jillian.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Maga új itt? És hogy kerültél ide, mondd el! Túlélted a hajótörést?";
			link.l1 = "Nos... valami ilyesmi. Itt vitorláztam egy bárkán, és majdnem átjutottam a zátonyokon, de sajnos hajókba ütköztem' szemétbe, és a hajóm elsüllyedt. És egyedül úsztam ide.";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "Ó! Szóval önszántadból jöttél ide? Hihetetlen!";
			link.l1 = "Igen, ennyire ôrült vagyok. Elhatároztam, hogy megtalálom az Igazság Szigetét, és végre megtaláltam. Bár nem tudom, hogyan jutok ki onnan.";
			link.l1.go = "meeting_3";
		break;
		
		case "meeting_3":
			dialog.text = "Nagyon bátor vagy, vagy vakmerô. Ide hajózni egy bárkán... Most itt fogsz élni velünk, mert az elmúlt évtizedben senki sem tudta elhagyni ezt a helyet.";
			link.l1 = "Még mindig van remény. Rendben, Jillian, nem zavarlak. Viszlát!";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Igen, persze, "+pchar.name+". Hallgatlak.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Hogy kerültél ide?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "El akarod hagyni a szigetet?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "És hogy telt a napod? Mit csinálsz?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Azt mondtad, hogy nem vagy házas... Egy ilyen csinos lánynak nincsenek itt hódolói?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Nincs kérdés. Elnézést...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Angliából hajózom a szüleimmel. Új életet akartunk kezdeni, és... Itt kezdtem új életet. A szüleim meghaltak, én pedig alig éltem túl. Elértem valami hajót a külsô gyûrûbôl, és egy napig eszméletlenül feküdtem ott, amíg egy helybéli rám nem talált. Ott haltam volna meg, ha nem talál rám.";
			link.l1 = "Értem...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "És hová? Kinek és hol van rám szüksége? Nincs otthonom, nincs férjem és nincs pénzem. Soha sehol máshol nem jártam, csak ezen a szigeten és a londoni nyomornegyedben. Úgy tûnik, az a sorsom, hogy itt éljek...";
			link.l1 = "Biztos vagy benne?";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Leginkább Julian testvérnek segítek a templomban. Valamit könnyebb munkát is végzek Axel boltjában. Így keresem a pénzem. Lány vagyok, és nem tudok a külsô gyûrûn a hajó törmelékein átmászni.";
			link.l1 = "Persze...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Tee-hee... vannak csodálóim, igen, de nem éri meg. Egyiküket sem kedvelem, és nem akarok olyan emberrel élni, akit nem kedvelek. Azok a férfiak, akiket kedvelek, nem vesznek tudomást rólam. Hát, én csak egy közönséges szegény lány vagyok...";
			link.l1 = "Ez csak egy új élet kezdete számodra...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Mit csinálsz ott, ah? Tolvaj!", "Csak nézd meg ezt! Amint elmerültem az elmélkedésben, úgy döntöttél, hogy megnézed a mellkasomat!", "Úgy döntöttél, hogy megnézed a ládámat? Ezt nem úszod meg!");
			link.l1 = "Basszus!";
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
			link.l1 = LinkRandPhrase("Jól van.", "Rendben.", "Ahogy mondod...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "Figyeljen, én a város polgára vagyok, és arra kérem, hogy tartsa vissza a pengéjét.", "Figyelj, a város polgára vagyok, és arra kérnélek, hogy tartsd vissza a pengédet.");
				link.l1 = LinkRandPhrase("Jól van.", "Akkor mindegy.", "Ahogy mondod...");
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
