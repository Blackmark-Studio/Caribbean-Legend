// Дугал Эббот - дворянин
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
				dialog.text = "Üdvözletem, uram. Hadd mutatkozzam be - Dougall Abbot. Örülök, hogy egy nemes embert látok itt. Elegem van a helyi parasztokból. Soha nem tudtam volna elképzelni, hogy életem hátralévô részét egyszerû emberek között kell leélnem.";
				link.l1 = TimeGreeting()+". A nevem "+GetFullName(pchar)+". Örülök, hogy találkoztunk. És miért nem szereted a helyieket?";
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
			dialog.text = "Nem ismeri ôket jól. Most érkezett ide? Bár nem emlékszem, hogy mostanában történt volna hajótörés...";
			link.l1 = "Egy kis bárkán jöttem ide...";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Igen, gyakran elôfordul - hajók süllyednek el, és csak néhány túlélô jut el ide a hajójukon' hajókon. Néha hónapokig élnek itt emberek, és soha nem találkozol velük.";
			link.l1 = "Értem. Örülök, hogy megismerhettem, apát úr. Viszlát!";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Van valami érdekes mondanivalód?", "Történt valami újdonság a szigeten?", "Elmondanád a legújabb pletykákat?");
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
				link.l1 = "És hogy kerültél ide?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Mit tudsz mondani a helyiekrôl?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Mit tudsz mondani a klánokról?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "És az idôjárásról? Gyakran vannak itt viharok?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Nincs kérdés. Elnézést...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Öt évvel ezelôtt történt, de még mindig úgy emlékszem rá, mintha tegnap történt volna. Egy szerencsétlen napon úgy döntöttem, hogy a furulyámon elhajózom Port Royalból Belize-be, túl értékes rakomány volt ahhoz, hogy másokra bízzam az üzletet\nA következô napon kezdôdtek a szerencsétlenségek, elôször a csónakosunk berúgott és a fedélzetre esett, aztán majdnem zátonyra futottunk, a végén pedig a navigátorunk hibázott, így rossz irányba hajóztunk\nAztán egy brigg és egy gálya üldözött minket. Megpróbáltunk elmenekülni, de ôk rámenôsek voltak. A gálya lemaradt, de a brigg végül utolért minket\nA gálya túl messze volt onnan, így lövöldözés nélkül felszálltunk a briggra. Azok a spanyol kutyák nem számítottak erre és nyertünk, de a legénységem nagy része meghalt\nPár órával késôbb a vihar elkapott minket, nem tudtunk küzdeni az idôjárással ilyen kevés legénységgel és most látjátok az eredményt. A furulyám valahol a külsô gyûrûnél van, én és a másik három túlélô ide jutottunk.";
			link.l1 = "Megvan...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Söpredék. Mindegyikük. Mindenféle aljas alak. Richard Shambon egy bûnözô, ez az arcára van írva. Kassel? Embereket ölni neki olyan természetes, mint a légzés. Jasper Pratt egy elítélt. Musket egy részeges. Folytassam egyáltalán?\nJosef Loderdale az egyetlen tisztességes ember itt, kivéve téged, ô az angol haditengerészet volt katonája. Két nemes van itt - Antonio Betancourt és Lorenzo Solderra, átkozott spanyol söpredék, még csak egy asztalhoz sem ülök vele.";
			link.l1 = "Értem...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Egy rakás szemétláda és söpredék. De azért nem ártanak nekünk. Jobban érdekli ôket, hogy egymást szurkálják és lövöldözzék. Enélkül nem tudnak élni. Én sem szeretem a kalózokat, de el kell ismernem, hogy békésebbé tették a szigetet, amikor ide érkeztek.";
			link.l1 = "Érdekes...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Soha nem teszik ezt. A Sziget körül gyakran vannak viharok, de ez a hely mindig nyugodt és csendes, talán ez valamiféle varázslat vagy Isten akarata, nem tudom. Egy erôs szél néha eléri ezt a helyet, és ennyi. Az esô sem tud kárt tenni.";
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
