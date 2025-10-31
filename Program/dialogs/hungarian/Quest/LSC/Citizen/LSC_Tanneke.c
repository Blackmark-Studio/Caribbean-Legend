// Таннеке Эверс - просто девушка
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
				dialog.text = "Szép napot! Ismerem magát? Még nem láttam önt, az biztos...";
				link.l1 = TimeGreeting()+". Igaz, én egy új... látogató vagyok itt. A nevem "+GetFullName(pchar)+" és kapitány vagyok.";
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
			dialog.text = "Voltál már kapitány?";
			link.l1 = "Miért voltam az? Még mindig kapitány vagyok...a-ah, értem! Azt hiszed, hogy a hajóm elsüllyedt vagy elpusztult a zátonyok miatt. Nem. A nyugati partok közelében van. És én egy bárkán jutottam el ide, bár rosszul végzôdött, a bárka lyukat kapott a hajótestén és elsüllyedt.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Egy bárkán jött ide? És hogy sikerült túlélnie a vihart?";
			link.l1 = "Milyen vihart? Nem emlékszem semmilyen viharra...";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "De hogyhogy? A sziget körül mindig van vihar. Mindenki ezt mondja.";
			link.l1 = "Hát, nem az, vagy én voltam olyan szerencsés, hogy megúsztam. A tenger teljesen nyugodt volt... Elnézést, megtudhatnám egy ilyen csinos hölgy nevét?";
			link.l1.go = "meeting_3";
		break;
		
		case "meeting_3":
			dialog.text = "Ó! Bocsánat, elfelejtettem bemutatkozni... A nevem Tanneke. Örülök, hogy megismerhetem.";
			link.l1 = "Én is örülök, Tanneke... Örülök, hogy megismerhetem.";
			link.l1.go = "meeting_4";
		break;
		
		case "meeting_4":
			dialog.text = "És miért döntött úgy, hogy egy bárkán érkezik a szigetünkre? A-a, értem már - az áramlat sodorta ide. Senki sem tud a szigetrôl, és az emberek mindig véletlenül kerülnek ide.";
			link.l1 = "Ez nem helyes. Egészen igaz pletykák keringenek a Szigetrôl, beleértve a helyét is. Ezért úgy döntöttem, hogy a saját szememmel fogom látni...";
			link.l1.go = "meeting_5";
		break;
		
		case "meeting_5":
			dialog.text = "Most már értem. Olyan vagy, mint Adolf Barbier, aki túl sokat olvasott Alvarado kapitányról, és úgy döntött, hogy de Betancourt admirális aranyát keresi. Sajnos, kapitány, ha egy olyan ravasz gazembernek, mint Barbier, nem sikerült megtalálnia, akkor kétlem, hogy önnek is sikerülni fog\nAz pedig tényleg úgy gondolom, hogy nincs is admirális aranya, Antonio biztos csak azért találta ki, hogy megmutassa, milyen fontos ember volt a nagyapja... Hát akkor maradj velünk. Idejönni könnyû volt, de elmenni már lehetetlen lehet. Mármint épségben elmenni innen.";
			link.l1 = "Ez semmiség. Azt hiszem, ezt meg fogom tudni oldani, nem a Betancourt aranyára gondolok, amit említettél - most hallok róla elôször -, hanem arra, hogy elhagyom a szigetet. Élve. Öröm volt veled beszélgetni, Tanneke. Viszlát!";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Kérdezzen csak, kapitány...";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Hogy kerültél ide?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Próbálta már valaha is elhagyni a Szigetet?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Hogy élsz itt?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "A lányoknak az admirálistól kell élelmet venniük, vagy ingyen kapják?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Nincs kérdés. Elnézést...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Holland vagyok, de Santiagóban éltünk. A szüleim elküldtek cselédlánynak dolgozni Geraldi bankár családjához. Hallottál már róluk? Három évvel ezelôtt egyikük Új-Spanyolországba hajózott egy futárhajón. Azt mondták, hogy kísérjem el. Az utunk második napján egy spanyol zászló alatt közlekedô brigantin fogott el minket\nA tisztjük feljött a hajónkra, és elbeszélgetett a kapitányunkkal, a kapitány dühös lett, és elzavarta a tisztet. Megtámadtak minket, amint a vendég a hajójára ért. Megpróbáltunk elmenekülni, de sikerült a fedélzetre jutniuk. Amennyire értettem, szükségük volt Geraldi mesteremre, mert berontottak egy kabinba, elfogták és elvitték. Engem és a matrózokat a raktérbe vittek és ott hagytak.\n Azt hittem, hogy elsüllyesztenek minket, de csak elhajóztak. A matrózoknak sikerült elhagyni a raktérbôl, de a kapitányunk meghalt a harcban, és a túlélôk közül senki sem tudta, hogyan kell helyes irányba navigálni. Egy darabig vitorláztunk valahol, amíg az erôs szélvihar el nem vitt minket\n Pár órával késôbb a luggerünket a külsô gyûrûbe dobták. Még mindig ott van. Szerencsém volt, hogy túléltem a zûrzavart, hajnal után én és néhány másik 'szerencsés' ember elértük a szigetet.";
			link.l1 = "Értem...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Nem. És ezt hogy képzeled? Itt nincsenek hajózásra kész hajók, és a hosszúhajó használata olyan, mintha te magad írnád alá a halálos ítéletet. Mint mondtam, itt gyakran vannak viharok. Csak egy próbálkozásra emlékszem, amikor megpróbálták elhagyni ezt a helyet - öt polgár épített egy tisztességes hosszúhajót vitorlákkal és evezôkkel\ntöbb órán át küzdöttek az áramlással, majd végül elérték a nyílt tengert. Néhány nappal késôbb egyikük visszatért a külsô gyûrûbe... egy árboc roncsához kötve és holtan. Ez megölte a többiek vágyát, hogy ilyen bátor dolgokat tegyenek.";
			link.l1 = "Megvan...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Minden rendben van. Nem rosszabb, mint annak az arrogáns uzsorás családnak a szolgája lenni. Csak meg kell szoknod ezt a helyet, és utána talán még meg is szereted. Egyébként nem én vagyok az egyetlen, aki így gondolkodik. És a klánok... nem zavarnak engem.";
			link.l1 = "Érdekes...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Természetesen vásárolunk. Ó, kapitány úr, van elég munka egy lánynak: takarítás, fôzés, mások segítése... nem ülünk tétlenül, de itt senki sem törik a hátát. A kalózok olcsón árulnak élelmiszert a köznépnek, szemben a klánokkal. Így nem halunk éhen\nSegítek Gilliannek és Natalie-nak, és ôk is segítenek nekem, ha kell. Barátok vagyunk. Van még egy lány a szigeten, a spanyol. Ramonának hívják, de ô többnyire egyedül van, és nem igazán akarunk vele barátkozni.";
			link.l1 = "És miért is?";
			link.l1.go = "ansewer_4_1";
		break;
		
		case "ansewer_4_1":
			dialog.text = "Hát... mondjuk úgy, hogy máshogy látjuk az életet. Beszélgessetek vele, és meg fogjátok érteni.";
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
			dialog.text = LinkRandPhrase("Figyeljen, jobb, ha elveszi a fegyverét. Ideges leszek tôle.", "Tudod, a pengével való rohangálást itt nem tolerálják. Vidd el.", "Figyelj, ne játszd a középkori lovagot, aki karddal rohangál. Vedd el, nem illik hozzád...");
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
