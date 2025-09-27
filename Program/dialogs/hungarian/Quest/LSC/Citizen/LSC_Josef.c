// Джозеф Лодердэйл - английский военный офицер
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
				dialog.text = "Jó napot, uram. Örülök, hogy egy nemes emberrel találkozom.";
				link.l1 = TimeGreeting()+". Igazából olyan közel kerültem a köznéphez, amíg a szigetvilágban voltam, hogy már kezdtem elfelejteni a nemességemet...";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = TimeGreeting()+", "+GetFullName(pchar)+"! Örülök, hogy találkoztunk! Mit fogsz mondani?";
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
			dialog.text = "Ó, és még szerény is vagy! Egy igazi úriember! Azt hiszem, barátok leszünk, te nem olyan vagy, mint az a nagyképû apát... Hadd mutatkozzam be: Josef Loderdale, az angol flotta egykori kapitánya.";
			link.l1 = "Örülök, hogy megismerhetem. "+GetFullName(pchar)+" szolgálatára!";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Elég unalmas itt élni, látogasson el este a kocsmába, megihatunk egy pohár bort és egy érdekes beszélgetést...";
			link.l1 = "Ezt észben tartom, uram. Viszlát!";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Van valami érdekes mondanivalód?", "Történt valami újdonság a szigeten?", "Elmondanád az utolsó pletykákat?");
			link.l2.go = "rumours_LSC";
			link.l3 = "Szeretnék feltenni néhány kérdést a szigetrôl.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;

//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Örömmel válaszolok a kérdéseire, uram...";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Hogy kerültél ide?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Milyen szolgáltatást kaphatok itt?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Mint katonatiszt, mi a véleménye a kalózok itteni uralmáról?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Sok zárt ládát láttam itt, a szigeten. Az emberek nem bíznak egymásban, igaz?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Nincs kérdés. Elnézést...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Katonai kötelességemet teljesítem. Spanyol hadihajó ellen harcoltam, úgy véltük, hogy ez a hajó felelôs az angol kereskedôk kifosztásáért. A harc hosszú volt, majdnem elkaptuk ôket, de a hirtelen jött vihar elrontotta a játékot. Ennek eredményeként mindkét hajó a külsô gyûrûk közelében hajótörést szenvedett\nA szerencsének van humorérzéke, én és a spanyol kapitány túléltük. Talán már találkoztatok vele itt. A neve Lorenzo Solderra, egy ritka söpredék. Vigyázzatok vele.";
			link.l1 = "Megvan. Megfontolom a figyelmeztetésedet...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Ha pihenésre van szükséged - látogass el Sancho kocsmájába. Ô mindig biztosít neked ételt, italt és ágyat. Ha puskaport, lôszert, fegyvereket és egyéb dolgokat szeretnél beszerezni - menj Axel Yosthoz, ô a helyi bolt tulajdonosa. Gyógyszereket Julian testvértôl vehetsz, a templomában szent tárgyakat is árul\nNarwhalsnak van egy nagyon tehetséges kovácsa, akit Schmidtnek hívnak. Azt mondják, hogy kiváló pengéket készít. Van még egy másik tehetséges mesterember is a narwhalok között, de róla nem sikerült többet megtudnom\n És ha kalózokkal vagy klánokkal van gondod, akkor keresd fel Giuseppe Faziót, ô a megfelelô szakember az ilyen ügyekben.";
			link.l1 = "Köszönöm az információt!";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Nem mondhatom, hogy tetszik, de nem tehetek ellene semmit. Elismerem, csak néhány napba telt, amíg a kalózok békét kötöttek és rendet teremtettek a szigeten. Mielôtt a kalózok megérkeztek volna, a klánok rendszeresen harcoltak egymás ellen, és az egyszerû emberek szenvedtek a legtöbbet\nmellesleg nagyon rendesen és tisztességesen árulják az élelmet - a polgárok nagyon alacsony áron jutnak hozzá, ugyanezt nem mondhatom el a klánokról, a kalózok elevenen megnyúzzák ôket bosszúból, amiért háborút indítottak\nIsmerek egy nagyon okos embert a kalózok közül, Layton Dexternek hívják. Ô az, aki a kereskedelmet végzi. Egyszer beszélgettem vele, csodálkozom, hogy egy ilyen tehetséges és jól képzett ember, aki ért a taktikához, a térképészethez és a kereskedelemhez, hogyan csatlakozott a kalózokhoz\nPár nap alatt elkészítette a sziget kiváló térképét. Láttam, szinte minden benne van. Szerintem egy esetleges klánok elleni háborúhoz készítette...";
			link.l1 = "Értem...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
			sld = characterFromId("Dexter");
			sld.quest.map = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Ez a helyes dolog. Azt mondják, hogy régen a tolvajlás normális dolog volt a Szigeten, amíg minden láda új zárat nem kapott. És mégis, még mindig van valaki, aki fel tudja törni a ládák zárját. Bár ô csak rumot és olcsó ékszereket lop, aranyat vagy pénzt soha nem vitt el\nMinden zár egyedi, nincs azonos kulcs - errôl Jurgen Schmidt gondoskodott. Nemcsak pengéket, hanem zárakat és kulcsokat is készít. Nekem azt mondták, hogy a külsô ládákban nem tárolnak értéktárgyakat, a komolyabb tárgyakat mindig a hajók belsejében tartják.";
			link.l1 = "Érdekes...";
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
			link.l1 = LinkRandPhrase("Jól van.", "Ahogy kívánod...", "Ahogy mondod...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "Figyeljen, én a város polgára vagyok, és arra kérem, hogy tartsa vissza a pengéjét.", "Figyelj, a város polgára vagyok, és arra kérnélek, hogy tartsd vissza a pengédet.");
				link.l1 = LinkRandPhrase("Jól van.", "Ahogy kívánod...", "Ahogy mondod...");
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
