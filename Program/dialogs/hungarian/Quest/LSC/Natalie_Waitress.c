// официантка Наталия Бушелл
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
			if (pchar.questTemp.LSC == "return" && !CheckAttribute(npchar, "quest.return_isl"))
			{
				dialog.text = "Ó! És azt mondták, hogy megfulladtál... Hazugok!";
				link.l1 = "Hát persze! Hah! Jól vagyok!";
				link.l1.go = "exit";
				npchar.quest.return_isl = "true";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Jó napot, "+GetAddress_Form(NPChar)+"! Elôször vagy itt? Még nem láttalak... Remélem, hogy gyakrabban látogat majd el hozzánk, a Sancho kiváló italválasztékot tud kínálni. Igen, és a nevem Nathalie, és én segítek Sanchonak a kocsma ügyeiben.";
				link.l1 = TimeGreeting()+". A nevem "+GetFullName(pchar)+". Örülök, hogy találkoztunk. És korábban nem láthattál. Nemrég jöttem ide.";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, "+GetFullName(pchar)+"! "+TimeGreeting()+"! Akarsz valamit?";
				link.l1 = LinkRandPhrase("Van valami érdekes mondanivalód?", "Történt valami újdonság a szigeten?", "Elmondanád a legújabb pletykákat?");
				link.l1.go = "rumours_LSC";
				link.l2 = "Szeretnék feltenni néhány kérdést a szigetrôl.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "Csak tudni akartam, hogy vagy. Viszlát!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Mostanában? Egy másik hajó is lezuhant? Nem hallottam semmit... Vagy ön nem az árboc roncsain érkezett ide, mint Turam úr? Ó, bocsássa meg a kíváncsiságomat, a nôk természete, tudja.";
			link.l1 = "Nem, semmi baj, Nathalie. Egy bárkán érkeztem ide, de az elsüllyedt. Örülök, hogy találkoztunk. Viszlát!";
			link.l1.go = "exit";
			link.l2 = "Nem, semmi baj. Csak fel akartam tenni néhány kérdést a szigetrôl.";
			link.l2.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Hallgatlak.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "A tavernában dolgozik. Mit tudsz mondani a tulajdonosról?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "És hogy kerültél ide?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Hány ember él itt?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Soha nem lepôdsz meg, ha új arcokat látsz itt?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Nem kérdezek semmit. Ha megbocsátanak...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Csak pozitív dolgokat,  "+GetAddress_Form(NPChar)+". A Sancho mindig nagy választékban kínálja az italokat - a régi boroktól az egyszerû sörökig és a rumig. Néhány évvel ezelôtt hatalmas készletet talált évjáratos borokból. Sancho két hónapot töltött azzal, hogy dobozokat cipelt palackokkal a raktárába\nés most már jól el vagyunk látva borral, amibôl csak a kormányzók engedhettek meg maguknak ennyit a szigetországban. A rum sem jelent problémát. Sancho nemcsak itallal, hanem friss hírekkel, egy jó tanáccsal és egy meleg ággyal is el tud látni, ahol eltölthetünk egy éjszakát.";
			link.l1 = "Értem...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Ó, ez egy szomorú történet. Hét évvel ezelôtt megszöktem az udvarlómmal a szülôi házból, és úgy döntöttünk, hogy Santiagóból Belize-be költözünk. A navigátor hibázott a Main közelében, így rossz irányba, észak felé hajóztunk, és viharba kerültünk. A hajónk nem messze a külsô gyûrûtôl elsüllyedt\nAz udvarlóm aznap meghalt, ahogyan a többiek többsége is. Én és a túlélôk új életet kezdtünk itt, a Szigeten.";
			link.l1 = "Szomorú történet...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Elég sokan. A rivadók és a narválok klánjai nagy számban vannak jelen, évtizedek óta itt élnek. Közönséges emberekbôl nincs túl sok, de a kocsma minden este tele van. Alig gyôzöm felszolgálni az italokat.";
			link.l1 = "Tényleg? Érdekes.";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "És miért is kellene? Nagyon sok új arc jön nagyon gyakran. Azt sem tudom, hányan élünk itt. Van, hogy elôször látok egy embert, és azt mondja, hogy már egy éve itt él.";
			link.l1 = "Nos...";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Mit csinálsz ott, mi? Tolvaj!", "Csak nézd meg ezt! Amint elmerültem az elmélkedésben, úgy döntöttél, hogy megnézed a mellkasomat!", "Úgy döntöttél, hogy megnézed a ládámat? Ezt nem úszod meg!");
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
			dialog.text = LinkRandPhrase("Figyeljen, jobb, ha elveszi a fegyvereit. Ideges leszek tôle.", "Tudod, a pengével való rohangálást itt nem tolerálják. Vigyétek el.", "Figyelj, ne játszd a fegyverrel rohangáló középkori lovagot. Vidd el, nem illik hozzád...");
			link.l1 = LinkRandPhrase("Jól van.", "Rendben.", "Ahogy mondod...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "Figyeljen, én a város polgára vagyok, és arra kérem, hogy tegye hüvelybe a pengéjét.", "Figyelj, a város polgára vagyok, és arra kérlek, hogy tedd hüvelybe a pengédet.");
				link.l1 = LinkRandPhrase("Jól van.", "Rendben.", "Ahogy mondod...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, "Légy óvatos, haver, amikor fegyverrel futsz. Ideges tudok lenni...", "Nem szeretem, ha az emberek fegyverrel a kezükben sétálnak elôttem. Megijeszt...");
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
