// Лайонел Маскетт - мещанин
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
				dialog.text = "Üdvözlet, "+GetAddress_Form(NPChar)+". Újonnan érkezett vagy?";
				link.l1 = TimeGreeting()+". A nevem "+GetFullName(pchar)+". Igen, én vagyok.";
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
			dialog.text = "A nevem Lionell. Örülök, hogy megismerhetem. Hogy kerültél ide?";
			link.l1 = "Egy bárkán... Hallottam, hogy van itt egy csempész bázis és úgy döntöttem, hogy felfedezem... Felfedeztem. A bárka elsüllyedt és én itt vagyok.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Tényleg csempészbázisként tekintenek a szigetre' ?";
			link.l1 = "Nos, hivatalosan nem. A többség nem is hisz a létezésében.";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "Komolyan... És miért is tennék? Mi valójában nem is létezünk. Nem hagyhatjátok el ezt a helyet. Bár azt mondják, hogy van kapcsolat Kubával... De én erre nem emlékszem, pedig már majdnem nyolc éve itt élek.";
			link.l1 = "Értem. Örülök, hogy beszélhettem önnel. Viszlát!";
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
				link.l2 = "Szeretne visszatérni a szárazföldre?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "És mit csinálnak az emberek itt, a szigeten?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "És honnan szereznek be mindent itt? Élelmiszert, ruhát, italokat?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Nincs kérdés. Elnézést...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Ez egy furcsa történet. Ez a sziget az egyetlen hely az összes karibi közül, amit láttam. Amikor a dolgok rosszra fordultak számomra, elhajóztam egy kereskedelmi hajón a régi Angliából. Belize-ben akartam munkát találni, kikötôi hivatalnok akartam lenni. De soha nem jutottunk el Belize-be\nnem vagyok tengerész, így nem ismerem a részleteket. Történt egy vihar, és másnap a hajónk zátonyra futott. Soha nem fogom elfelejteni azt a szörnyû csapást, a sikoltozást\nvalaki kiabált, hogy lyuk van a hajótestben, az emberek elkezdtek a fedélzetre ugrani. Én... én nem tudok úszni. Így hát maradtam. Ironikus módon ez mentette meg az életemet. A hajó túlélte, és a vihar hajnalban lecsillapodott\nAz egyetlen helyes döntést hoztam, mielôtt elhagytam a hajót. Vettem némi élelmet, építettem egy tutajt, és a békés tengeren keresztül elhajóztam a külsô gyûrûhöz. Így maradtam életben, az egész legénység közül az egyetlen.";
			link.l1 = "Értem...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Az elsô két évben ez volt az egyetlen álmom. De most... Mitôl rosszabb ez a sziget, mint bármely más hely a világon? Igen, nincsenek zöld mezôk birkákkal, de van egy csodálatos tenger és egy gyönyörû csillagokkal teli éjszakai égbolt. Jól táplálkozom, tisztességes ruhát hordok, amit Angliában élve nem engedhettem meg magamnak. Sok barátom van\n Nem, uram, nem akarom elhagyni ezt a helyet. Mi vár rám odakint? Egy íróasztalos munka egy károgó fônök alatt heti háromszáz pezóért? Szó sem lehet róla! Itt mindent megtaláltam, amit kerestem, nincs szükségem másra.";
			link.l1 = "Megvan. Örülök neked!";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Mit szeretnek a legjobban. A klánok háborúznak, a kalózok ellátmányt árulnak, Axel Yost vásárol és árul, Sancho Carpentero italokat szolgál fel és szórakoztatja az embereket, Julian testvér imádkozik, misézik és gyógyszereket árul. Loderdale és Solderra egymás ellen intrikálnak, Apát szereti, ha felfújják, Jillian és Tanneke az igaz szerelemrôl álmodik...";
			link.l1 = "Érdekes...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "A hajókról, barátom, a hajókról. A többség kedvenc elfoglaltsága a külsô gyûrû hajóinak felderítése és a belôlük származó dolgok megszerzése. Ott mindent megtalálsz, fegyvereket, gyógyszereket, fûszereket és rumot. Sok hajó még mindig felderítetlen. A tengeráramlat gyakran hoz ide egy újabb áldozatot...";
			link.l1 = "Érdekes...";
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
