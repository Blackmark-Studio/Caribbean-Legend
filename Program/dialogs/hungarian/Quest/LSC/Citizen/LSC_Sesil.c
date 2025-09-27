// Сесил Галард - бабулька
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
				dialog.text = "Kérsz valamit, fiatalember?";
				link.l1 = TimeGreeting()+". Hadd mutatkozzam be - "+GetFullName(pchar)+". Újonnan érkezett vagyok.";
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
			dialog.text = "A-ah, szóval megismerkedsz a szigetünkkel és a lakóival, igazam van?";
			link.l1 = "Pontosan, asszonyom...";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Halard. Cecille Halard.";
			link.l1 = "Örülök, hogy megismerhetem, Halard kisasszony! Örvendek.";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "Az enyém is... És hogy került ide, fiatalember? Nem emlékszem, hogy mostanában hajótörést szenvedett volna...";
			link.l1 = "Egy bárkán hajtottak ide a Mainból... de az elsüllyedt a Sziget partjai közelében. Így maradtam hajó nélkül.";
			link.l1.go = "meeting_3";
		break;
		
		case "meeting_3":
			dialog.text = "Egy bárka? Nehéz elhinni... Ebben az esetben tényleg szerencsés vagy, hogy egy ilyen kádon elhajóztál egészen a szigetig és nem estél bele egy viharba. A viharok a szigeten belül ritkán fordulnak elô, de odakint fenyegetnek, méghozzá nagyon hirtelen\nSzóval tekintse magát szerencsésnek, és szokja meg a helyi életmódot! Nem akarlak elkeseríteni, de ide eljutni könnyû, de elhagyni a szigetet szinte lehetetlen. Ne higgyétek, hogy zsörtölôdöm, az elmúlt tíz évben senkinek sem sikerült élve elhagynia a Szigetet.";
			link.l1 = "És mégis megpróbálok egy kicsit optimistább lenni. Örülök, hogy találkoztunk és találkozunk!";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Igen, fiatalember?";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "És hogy került ide, asszonyom?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Már régóta itt él, ugye?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Mit tudsz mondani a helyiekrôl?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Tudna mesélni nekem érdekes emberekrôl, akik itt élnek?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Nincs kérdés. Elnézést...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Olyan régen volt, ezért nem is emlékszem igazán, hogyan történt. Hajótörés és ennyi...";
			link.l1 = "Értem...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Néha azt hiszem, hogy itt születtem... De ez persze nem igaz. Életem második felében itt éltem. És ez hosszú volt. És itt fogok meghalni, mert nem fogom elhagyni ezt a helyet.";
			link.l1 = "Értem...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "És nem sok mindent tudok mondani, fiatalember... minden más. Mindenki itt van - fehér, fekete, indián, volt rabszolgák és nemesek, állami elítéltek és katonák. És korábban többen voltak. Mindenkinek megvan a maga története és a maga szokásai. Valaki nem törôdik vele, de valaki más mégis nagyon szeretne visszatérni. Így élünk mi...";
			link.l1 = "Érdekes...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "A legérdekesebb emberek itt: a narvál mechanikus feltaláló, Herr Schmidt - narvál fegyverkovács, Sancho Carpentero - a bennszülött csapos. És most itt van az admirális is a helyettesével.";
			link.l1 = "Megfontolom, hogy...";
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
