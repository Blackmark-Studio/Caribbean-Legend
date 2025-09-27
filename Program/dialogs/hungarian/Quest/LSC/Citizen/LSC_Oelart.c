// Оеларт Котеел - канонир
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
				dialog.text = "Jó napot, mynheer! Tetszik az idôjárás?";
				link.l1 = TimeGreeting()+". Én minden idôjárást jól érzek, kivéve a viharokat a nyílt tengeren...";
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
			dialog.text = "Hidd el, én is így érzem. Még sosem láttalak... a nevem Oelart Koteel, és ágyúmester voltam a Holland hadihajón.";
			link.l1 = ""+GetFullName(pchar)+". Igen, újonnan jöttem ide. Igazából csak most érkeztem.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Én is újonc vagyok, kevesebb mint egy éve vagyok itt. És nagyon remélem, hogy nem maradok itt túl sokáig, bár mindenki próbál rábeszélni az ellenkezôjére. Örülök, hogy találkoztunk!";
			link.l1 = "Örülök, hogy megismerhetlek, "+npchar.name+"...";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Van valami érdekes mondanivalód?", "Történt valami újdonság a szigeten?", "Elmondanád az utolsó pletykákat?");
			link.l2.go = "rumours_LSC";
			link.l3 = "Szeretnék feltenni néhány kérdést a szigetrôl.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Hallgatlak.";
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
				link.l3 = "Gondoltál már arra, hogyan alakult ki a sziget?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Meglátogattad már a klán hajóit?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Nincs kérdés. Elnézést...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Elég banális. Harcoltunk egy angol schoonerrel, és majdnem megnyertük a csatát. Elmenekültek, ezért üldözôbe vettük ôket. Eltelt egy nap, közel voltunk ahhoz, hogy utolérjük ôket, de ôk lelôtték a fôárbocunkat, és persze sikerült elmenekülniük\nMinket pedig majdnem elsüllyesztett egy erôs szélvihar, aztán sodort minket az áramlat, és végül a hajónkat egy zátonyra vetette a külsô gyûrû közelében. Csak nagyon keveseknek sikerült túlélniük...";
			link.l1 = "Értem...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Ez az én álmom. El sem tudjátok képzelni, hogyan untam meg ezt a helyet. De hogyan hagyhatnám el? Fogalmam sincs. Itt nincsenek hajók, és nincs lehetôségem újat építeni. Öngyilkosság lenne egy kis hajón hajózni.";
			link.l1 = "Értem...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "A hajók szerint körülbelül száz éves lehet. De van rá esély, hogy a külsô gyûrû miatt régebbi is lehet. Fentrôl lefelé hajókból áll, talán az idôsebb hajók mélyen a víz alatt vannak\nAm ami a sziget kialakulását illeti... Szerintem az áramlatok és a viharok hozták ide a haldokló hajókat, így jött létre a mesterséges zátony. Erre épült rá a külsô gyûrû\nA belsô hajók, amelyeken élünk... vagy ôk voltak a legelsôk, vagy valahogy sikerült átjutniuk a külsô gyûrûn. Könnyen lehet, hogy az Admirális és kalózai mégiscsak eljutottak hozzánk a briggjükön.";
			link.l1 = "Érdekes...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Meglátogattam Rivadost. Fekete Eddynek egyszer konzultációra volt szüksége a hajóágyúkkal kapcsolatban, és most már fogalmam sincs, miért. Szóval az egyik fekete srác megtalált és megadta a jelszót. Meglátogattam a 'Protector' és 'Velasco'. Az ôrök kemények, úgyhogy jelszó nélkül meg se próbáld kijátszani ôket.";
			link.l1 = "Értem...";
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
				link.l1 = LinkRandPhrase("Jól van.", "Rendben.", "Ahogy mondod...");
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
