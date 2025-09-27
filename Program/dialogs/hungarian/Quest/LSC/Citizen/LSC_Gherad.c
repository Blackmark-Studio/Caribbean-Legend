// Гхерад Смиитс - матрос
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
				dialog.text = "Jó napot, haver, ha-ha! Mit keresel itt?";
				link.l1 = TimeGreeting()+". Ismerem magát?";
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
			dialog.text = "Persze, hogy nem, de ezt könnyû helyrehozni, nem igaz? Gerard Smeets vagyok, matróz, tengerész Rotterdamból. Maga pedig úgy néz ki, mint egy szállásmester...";
			link.l1 = "Valami ilyesmi. A nevem "+GetFullName(pchar)+". Örülök, hogy találkoztunk.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Úgy nézel ki, mint egy hajótulajdonos vagy egy fizetésvezetô... Kétségtelenül jól képzett ember vagy. Örülök, hogy megismerhetem. Hogy került ide?";
			link.l1 = "Úgy döntöttem, hogy felfedezek egy ismeretlen területet. Kubai kalózok mondták, hogy van valami ezen a területen, és úgy döntöttem, hogy megnézem...";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "Te vagy az egyetlen túlélô? Hol süllyedt el a hajód? A gyûrû közelében?";
			link.l1 = "Én vagyok az egyetlen. És a Tartane-om a tenger fenekén van, még a gyûrûig sem jutott el.";
			link.l1.go = "meeting_3";
		break;
		
		case "meeting_3":
			dialog.text = "Értem. Hát, itt ragadtál egy darabig. Látogasd meg Sanchót, hogy kapj egy kis rumot, ez egy jó cselekedet...";
			link.l1 = "Úgy lesz. Viszlát!";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Van valami érdekes mondanivalód?", "Történt valami újdonság a szigeten?", "Elmondanád az utolsó pletykákat?");
			link.l2.go = "rumours_LSC";
			link.l3 = "Szeretnék feltenni néhány kérdést a szigetrôl.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Persze, barátom. Hallgatlak.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Mondd, hogy kerültél ide?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "El akarod hagyni a Szigetet és visszatérni a normális életedhez?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Nem zavarnak a klánok?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Hogyan alakult ki a Sziget, van valami elképzelésed róla?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Nincs kérdés. Elnézést...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Azzal a felfuvalkodott fasszal jöttem ide, akit Abbotnak hívnak. Az ô hajóján szolgáltam. És tudod mit? Az olyan embereknek, mint ô, soha nem szabadna betenniük a lábukat a hajó fedélzetére, mert balszerencsét hoznak. Biztos az ördög vette rá, hogy velünk hajózzon.\nMindössze Jamaikából kellett elhajóznunk Belize-be, gyerekjáték volt. De a rossz sors üldözött minket: a csónakosunk a fedélzetre esett, egy navigátor hibázott, véres spanyolok és a végén még egy vihar is. És most itt vagyunk.";
			link.l1 = "Érdekes...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Bárcsak tudnám, haver. Régebben tudtam, de most már nem. Az élet szép itt, rengeteg rum és bor, jó kaja, nem sok, de mindenképpen jobb, mint az a szar, amit a hajókon ettem\nA Szigeten is élnek jó fiúk. Van kivel vagy inni, vagy beszélgetni. Én szeretek itt lenni. Szóval nem is vagyok benne biztos... Nem, azt hiszem, nem, nem akarok elmenni. Régen dühös és éhes voltam, nézd meg most a hasam, ha-ha!";
			link.l1 = "Nagyszerû! Örülök neked.";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Nem, ôk nem. Csak ne vitatkozz velük, és ne látogasd a területüket engedély nélkül. Ezt nagyon nem szeretik. A narválok jó fiúk, a legtöbbjük itt született, és nem láttak más életet. Sokan közülük nagyon ügyesek, például Jürgen Schmidt. Ô a kovácsmesterség istene!";
			link.l1 = "Értem...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Könnyû, mint a pite. Zátonyok és zátonyok. A külsô gyûrût a tetejétôl az aljáig hajók alkotják. A hajókat elkapja a vihar, nekimennek a zátonyoknak vagy magának a külsô gyûrûnek. Így növekszik a sziget. Bár fogalmam sincs, hogy a belsô hajók miért maradnak a víz felett.";
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
			link.l1 = LinkRandPhrase("Jól van.", "Ahogy kívánod...", "Ahogy mondod...");
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
