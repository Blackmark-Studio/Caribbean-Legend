// Жаклин Тьюрам - торговый капитан
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
				dialog.text = "Jó napot, uram. Ön új itt, ugye?";
				link.l1 = TimeGreeting()+". Igen, azt hiszem, én vagyok itt a legújabb. A nevem "+GetFullName(pchar)+". És mi a tiéd?";
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
			dialog.text = "Jacqueline Turam. Két évvel ezelôtt tisztességes és gazdag kereskedô voltam, a saját furulyám tulajdonosa és kapitánya. Sajnos, most olyan szegény vagyok, mint egy templom egere, és nem reménykedhetek abban, hogy a helyzetem valahogy megváltozik\nNéhány embernek szerencséje van itt - ékszereket, aranyat, kincsekkel teli hajókat találnak, de én nem tartozom közéjük. Csak egy ládát találtam, amiben dublónok és néhány csecsebecse van\nEz legalább elég arra, hogy élelmet vegyek, így nem halok éhen... Örülök, hogy megismerhetem, uram, nem bánom, ha beszélgetünk...";
			link.l1 = "Én is örülök a találkozásnak, Jacqueline. Viszlát!";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Van valami érdekes mondanivalód?", "Történt valami újdonság a szigeten?", "Elmondanád az utolsó pletykákat?");
			link.l2.go = "rumours_LSC";
			link.l3 = "Szeretnék feltenni néhány kérdést a szigetrôl.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Csupa fül vagyok.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Hogy kerültél ide?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Mivel foglalkozik itt?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Mondja, látom, hogy vannak lányok és nôk a szigeten...";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Vissza akarsz menni a nagyvilágba?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Semmiség.";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Akarod hallani a történetemet? Igen, persze. Mint már tudod, kereskedelmi kapitány voltam. Egy nap elhajóztam Tortugából Belize-be a jó öreg furulyámon. A raktereim tele voltak fekete fával és kakaóval, minden pénzemet elköltöttem a rakományra\nEgy emberrel nagyon jövedelmezô üzletet kötöttem, rendkívül magas áron akarta megvenni a rakományomat. Egy vagyont kereshetnék ezen az üzleten. Minden jól ment, egyetlen felhô sem volt az égen, a hajóm olyan gyors volt, mint egy madár. Nem számítottunk bajra\nKuba közelében hajóztam, távol maradtam a spanyol ôrjáratoktól, de hirtelen megtámadott minket egy kalózgálya. Mit kerestek ott - spanyol terület közepén? Megpróbáltunk elmenekülni, de nem sikerült, a gálya meglepôen gyors volt\nA kalózok üldözôbe vettek minket és megtámadtak. A coulevrinjeik tele voltak szôlôlövedékkel, az elsô saláta súlyosan megrongálta a legénységemet, és demoralizálta azt. Jó kis harcot akartam vívni velük, de a saját legénységem és tisztjeim megállítottak. Megadtuk magunkat\nA kalózok gyorsan elvették a rakományunkat és eldobták az ágyúkat. Azt hittem, ez a vég. A rakomány elvesztése súlyos csapás volt, de még mindig pénzt kereshetek a teherhajókon, és egy nap újra lábra állhatok\nDe másképp alakult. A kalózfattyak tüzet nyitottak a védtelen fuvolámra. Tökéletes lôcélpont voltunk\nMég most is emlékszem a nevetésükre... A gálya elhajózott, mi pedig a roncsokat tartva vergôdtünk. Aztán jött egy erôs szélvihar hullámokkal, és azóta sem láttam senkit a legénységembôl. Sikerült egy árbocrészhez kötnöm magam, és a felszínen maradnom\na cápatámadásról szóló extra részletektôl megkíméllek. Valamilyen örökkévalóságig tartó idô után egy tengeri áramlat hozott ide. Így maradtam életben.";
			link.l1 = "Igen, ez tényleg egy szomorú történet.";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Úgy élek, mint a többi helybéli - csak élek. A külsô gyûrûnél értéktárgyakat keresek, és élelemre cserélem ôket. Arról álmodom, hogy megtalálom egy indiai király kincsekkel teli ládáját... Vagy legalább egy gályát spanyol arannyal, he-he. Ne nagyon figyeljetek oda, csak én\nálmodom arról, hogy valami mást eszem, mint kukoricás marhahúst és halat. Eh, volt itt egy ember, aki azokra az óriás rákokra vadászott. Öt dublont fizettem egy karomért, és több napig táplálkoztam belôle\nKár, hogy a vadász meghalt... bár nem mondhatom, hogy nem számítottam rá - az ilyenekre vadászni nagyon veszélyes tevékenység.";
			link.l1 = "Értem...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Értem, mire célozgatsz. Igen, a szerelem és az intrikák léteznek itt. És miért ne lennének? A férfi a nônek van teremtve és a nô is a férfinak. A természet. Megpróbálhatod Gilliannal és Tanneke-vel. Fiatalok, csinosak, és nem bánják az udvarlást\nMegtaláltam magamnak egy nôt - Natalia. Pincérnô Sancho kocsmájában. Nagyszerû lány, én mondom neked. Azt hiszem, ô az egyetlen oka annak, hogy nem vesztettem el az eszemet az itt töltött elsô hónapok alatt. Sokat segített, és most együtt vagyunk.";
			link.l1 = "Hm... Megvan!";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Jó kérdés. Természetesen szeretném. De ha belegondolok... Megtörtem. Mindent a rakományba fektettem, és a hajóm elsüllyedt. Semmi sem maradt az élethez. Az egyetlen lehetôségem a pénzkeresésre az, hogy a Holland Nyugat-indiai Társaságnak dolgozom, ha persze felvesznek\nHa csak lenne elég pénzem, hogy vegyek egy szkúnert és elég ellátmányt... Szóval jobb, ha a szigeten maradok. Legalább nem kell itt hajnaltól hajnalig dolgoznom egy darab kenyérért.";
			link.l1 = "Értem...";
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
