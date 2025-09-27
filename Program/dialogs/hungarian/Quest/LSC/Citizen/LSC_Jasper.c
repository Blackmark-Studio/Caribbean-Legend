// Джаспер Пратт - каторжник
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
				dialog.text = "Jó napot, uram. Kér valamit?";
				link.l1 = TimeGreeting()+". Az én nevem "+GetFullName(pchar)+", és mi a tiéd? Én egy új vagyok itt...";
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
			dialog.text = "Én? Én vagyok Jasper, a volt fegyenc. Ezért néznek rám az emberek ferde szemmel. Ah, a pokolba velük, már megszoktam...";
			link.l1 = "Nem érdekel, hogy ki voltál, az számít, hogy ki vagy most.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Kár, hogy nem mindenki gondolkodik úgy, mint maga, uram.";
			link.l1 = "Nos, én a liberális hozzáállásomról vagyok ismert...";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "Örülök neked. Ne aggódjon, a múltam ellenére nem jelentek veszélyt a Sziget lakóinak pénztárcájára és ládájára. Örülök, hogy végre békében élhetek.";
			link.l1 = "Örülök, hogy megismertelek, Jasper. Viszlát!"
			link.l1.go = "kilépés";
			link.l2 = LinkRandPhrase("Van valami érdekes mondanivalód?", "Történt valami újdonság a szigeten?", "Elmondanád az utolsó pletykákat?");
			link.l2.go = "rumours_LSC";
			link.l3 = "Szeretnék feltenni néhány kérdést a szigetrôl.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Igen, persze. Válaszolni fogok, ha tudok. Kérdezz!";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Hogyan lettél a sziget lakója?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Szereted ezt a helyet?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Említette, hogy az emberek ferde szemmel néznek önre. Ez a múltad miatt van?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Ez a sziget elég érdekes, nem gondolod?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Nincs kérdés. Elnézést...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Elszöktem a kubai ültetvényrôl. Öten voltunk, és úgy döntöttünk, hogy jobb meghalni, mint tovább törni a hátunkat a verésért. Sikerült becsapnunk az ôröket és eltûnnünk a dzsungelben, majd elértük a partot és építettünk egy tutajt\nTortugára akartunk jutni, de a sors másképp döntött. Egyikünk sem tudott navigálni, így eltévedtünk. Aztán a víz elfolyik... Erre nem akarok emlékezni. Ennek eredményeként én voltam az, aki elérte a szigetet és túlélte.";
			link.l1 = "Értem...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Tudod, ez nekem megfelel. Azok után, amin az ültetvényen keresztülmentem, ez a hely olyan számomra, mint a mennyország. Nincs szükségem sok mindenre... Egy kis étel, víz és egy pohár rum minden este. Itt senki sem zavar, és nem is fogom elhagyni ezt a helyet. Itt fogok meghalni, ha eljön az idôm.";
			link.l1 = "Értem...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "A helyzet az, hogy a sziget egy titokzatos tolvaj játszótere. A zárak nem jelentenek számára problémát. Leginkább az admirálisok szobáiban lóg. Bár a ládáinkat sem hagyja érintetlenül. Senki sem tudja, ki ez a tolvaj, ezért olyan emberekre gyanakodnak, akiknek... hm, bûnözôi múltjuk van\nA tolvaj azonban kicsit furcsa: elôször is csak szeszesitalos üvegeket és néhány csecsebecsét visz el, értékes tárgyakat soha nem visz el. Vicces, nem?";
			link.l1 = "Megvan...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Igen, egyetértek. Sokat úsztam a Sziget belsô hajói körül. Nagyon kevés kijárat van a vízbôl. San Augustin, a híd helye. Gloria, a ledôlt árboc. Ha közel úszol Fenix platformjához, majd Ceres Smitie körül, akkor eljutsz Mary Casper kabinjához a hajó orránál\nA Tartarusban lévô hasadék a börtönhöz vezet. A San Augustine orrában van egy lyuk, bejuthatsz az admirális raktárába, de ez nem tanácsos út. A Tartarus legalsó ajtaja gyakran zárva van, ezt ne feledd\n És persze bejuthatsz Fernandába, ez a magányos és szétszakadt fuvola. Azt mondják, hogy senki sem lakik ott, de én gyakran veszek észre fényeket a kabinban, és néha furcsa részeg énekeket és kiáltásokat hallok.";
			link.l1 = "Érdekes... Még jobban fel kell fedeznem ezt a helyet.";
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
			link.l1 = LinkRandPhrase("Jól van.", "Akkor mindegy.", "Ahogy mondod...");
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
