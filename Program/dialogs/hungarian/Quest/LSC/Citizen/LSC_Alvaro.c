// Альваро Гомец - капитан
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
				dialog.text = "Ó, egy új arc! Üdvözletem. És mikor érkeztél ide? Nem emlékszem, hogy mostanában történt volna hajótörés.";
				link.l1 = TimeGreeting()+". A nevem "+GetFullName(pchar)+". És a hajóm olyan csendben és gyorsan süllyedt el, hogy senki sem vette észre. És a szigetre is gyorsan és csendben jutottam el. Csak így...";
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
			dialog.text = "Értem. Ó, elfelejtettem bemutatkozni. Bocsásson meg, senor. A nevem Alvaro Gomez, és valaha a saját briggem kapitánya voltam. Eh, most az én szép briggem ott fekszik az alján, közvetlenül a külsô gyûrû mögött... Azóta sok víz lefolyt a híd alatt. Ah, mindegy. Örülök, hogy találkoztunk!";
			link.l1 = "Én is örülök, Senor Gomez.";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Van valami érdekes mondanivalód?", "Történt valami újdonság a szigeten?", "Elmondanád az utolsó pletykákat?");
			link.l2.go = "rumours_LSC";
			link.l3 = "Szeretnék feltenni néhány kérdést a szigetrôl.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Hallgatom, senor.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Azt mondta, hogy ön kapitány volt. Hogy került a szigetre?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Mit tud nekem mondani a szigeti életrôl?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Mondja, a helyiek békében élnek itt, vagy nem? Természetesen nem a klánokról beszélek.";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "És honnan szerzik be a helyiek az ellátmányt?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Nincs kérdés. Elnézést...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Ugyanúgy, mint bárki más. A vihar elkapott, elvesztettem az árbocot és a kormányt. Elragadott minket az áramlat, és a zátonyokhoz vetett. A hajóm még a külsô gyûrûig sem jutott el, és megsemmisült. Csak néhány emberünk maradt életben.";
			link.l1 = "Szomorú történet...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Mit is mondhatnék? Mindenünk megvan, ami a megfelelô élethez szükséges. Bár néha nagyon unalmas itt. És ez a melankólia... Az elsô év volt a legrosszabb, de késôbb megszoktam. Sajnálom szegény feleségemet, Sabrinát, biztosan biztos, hogy meghaltam. Remélem, sikerült újra férjhez mennie\nNe búsulj, majd megszokod. Látogass el a kocsmába, a boltba, a templomba, ismerkedj meg más emberekkel. Ne menj a narválokhoz vagy a rivadókhoz, amíg nem muszáj, ezek trükkös fattyak.";
			link.l1 = "Értem...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Igaz, a veszekedés és a verekedés itt titokban tilos. Ha valakit megfelelô ok nélkül megversz, vagy ne adj' isten megölsz, akkor a végén még elszigetelnek. Még az is lehet, hogy egy éjszaka a tengerbe dobnak. Volt már néhány verekedô a szigeten. Az elsô egyszerûen eltûnt, a második a Tartarosz egyik cellájában halt meg hónapokig tartó börtönbüntetés után... Persze, ez nem jelenti azt, hogy nem tudod megvédeni magad. De a helyiek valójában elég békések. Abbott hivalkodó, de nem agresszív. Kassel egy igazi szemétláda, de tisztán tartja a kezét. Pratt egy volt fegyenc, de ártalmatlan\nKét volt tengerésztiszt van itt - Loderdale és Solderra. Úgy kerültek ide, hogy nem messze tôlünk csatát vívtak. Ironikus módon mindketten túlélték, hogy továbbra is vérszomjas terveket szôjenek egymás ellen.";
			link.l1 = "Megvan...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Természetesen a fogásokból. Minden, más hajókról összegyûjtött ellátmányt Szent Ágostonban tároltak, és mindenki megosztotta ôket egymás között, amíg a kalózok fel nem bukkantak. Most ökölbe szorítják a szigetet, mert övék az ellátmány\nS persze, nekünk is vannak saját készleteink, úgyhogy minden rendben. Mi is lövöldözünk madarakat és halászunk... De a legjobb vadászat egy óriásrák megölésével végzôdik. Nagyon finom és tápláló húsuk van. Bár csak a külsô gyûrûnél lehet ôket látni\nA vadászatukhoz túl kockázatos lemerülni. Volt, aki elég bátor volt ahhoz, hogy a víz alatt vadásszon rájuk. Egy nap ô maga is prédává vált. Azóta senki sem akar ott rákokra vadászni.";
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
			link.l1 = LinkRandPhrase("Jól van.", "Persze.", "Ahogy mondod...");
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
