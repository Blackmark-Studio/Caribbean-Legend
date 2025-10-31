// Антонио Бетанкур - потомок Франциско Бетанкура
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
				dialog.text = "Helló, helló... Mit akarsz, barátom?";
				link.l1 = TimeGreeting()+". A nevem "+GetFullName(pchar)+". És csak azt akartam tudni, hogy ki vagy. Nézd, én nemrég érkeztem, sétálok a városban és beszélgetek az emberekkel.";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, "+GetFullName(pchar)+"! "+TimeGreeting()+"! Ezúttal mit akarsz?";
				if(CheckAttribute(pchar, "questTemp.LSC.Betancur"))
				{
					link.l4 = "Antonio, azt mondják, hogy jól ismered a sziget történetét. Van egy kérdésem hozzád ezzel kapcsolatban.";
					link.l4.go = "dolly";
				}
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
			dialog.text = "Nagyszerû. És jól fogod csinálni, mert mi itt mindannyian egy nagy család vagyunk. Kivéve persze a narválokat és a mocskos rivadókat. A nevem Antonio, Antonio Betancourt. Francisco Betancourt unokája vagyok, ha ez a név mond neked valamit.";
			link.l1 = "Francisco Betancourt? Hallottam már ezt a nevet... Ah, persze! Dios mesélt róla, és olvastam róla Alvarado feljegyzéseiben...";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Fogalmam sincs, ki ez a ti Diosotok, de Alvarado kapitány régen meglátogatott minket. Személyesen láttam ôt gyerekkoromban. Elhajózott a szigetrôl, és errôl írt a kézirataiban. Francisco Betancourt pedig egy spanyol admirális volt, a katonai század parancsnoka\nÔ kezdte el a hely történetét annak a ténynek köszönhetôen, hogy minden Rivados a Tartaroszról, a század zászlóshajójáról származó fekete rabszolgák leszármazottja. A narválok az elsô fehér telepesek, a Tartarus, a San Augustine és a San Geronimo legénységének tagjainak gyermekei.";
			link.l1 = "Hihetetlen! Szóval itt születtél?";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "Pontosan. Egyenes ági leszármazottja vagyok egy olyan embernek, aki gyakorlatilag elfoglalta a szigetet.";
			link.l1 = "Értem. Örülök, hogy találkoztunk, Antonio. Viszlát, Antonio.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		// квестовая часть
		case "dolly":
			dialog.text = "Hm... Persze, barátom, kérdezz csak. Természetesen válaszolok a kérdéseidre, de csak akkor, ha tudom a válaszokat.";
			link.l1 = "Mondd csak, emlékszel arra az idôre, amikor a San Geronimo gálya még itt volt?";
			link.l1.go = "dolly_1";
		break;
		
		case "dolly_1":
			dialog.text = "Persze, hogy emlékszem. Az egy nagyon különleges hajó volt. Volt ott egy érdekes indián szobor, és ezek a mocskos pogány Rivadosok áldozati áldozatokat mutattak be.";
			link.l1 = "És hogy csinálták ezt? Elvették az emberek szívét, mint a maják? Vagy fejeket vágtak le?";
			link.l1.go = "dolly_2";
		break;
		
		case "dolly_2":
			dialog.text = "Nem... Ez egy nagyon különleges szobor volt - magába rántotta az áldozatokat, és azok örökre eltûntek. Az ördög eszköze... Hála Istennek, elsüllyedt a hajóval együtt, és soha többé nem fog kárt tenni. Elég érdekes, hogy az áldozatokat mindig ugyanabban az idôben, reggelente végezték. A szobor a felkelô nap fényében arannyá változott\nAkkor a vademberek áldozatokat hoztak, többnyire a narválokat, akiket elfogtak.";
			link.l1 = "Érdekes! És próbálta már valaki feltárni, hogyan mûködik a szobor?";
			link.l1.go = "dolly_3";
		break;
		
		case "dolly_3":
			dialog.text = "Persze, hogy nem! Elôször is, a Rivadók a sajátjaikon kívül senkit sem engedtek a San Geronimo közelébe, másodszor pedig egy becsületes katolikusnak távolságot kell tartania az ördögi cselekedetektôl.";
			link.l1 = "Megvan. Látom, hogy nem kedveled Rivadost. Igazam van?";
			link.l1.go = "dolly_4";
		break;
		
		case "dolly_4":
			dialog.text = "Tényleg? Utálom azokat a mocskos pogányokat! Ha nem tudnád, a nagyapám annak a hajónak a kapitánya volt, ahol a négerek a vezérükkel, Rivadossal együtt fellázadtak. Helyesen cselekedett, hogy az úgynevezett vezetôjüket a raktérben rohadni hagyták. Volt egy gyönyörû kulcsom is a Szent Anna kincstárból\nNem tudja senki, hol található a kincstár, talán a tenger fenekén, ahol rákok vannak, de a kulcs édes emlék volt számomra, és mégis ellopták! Biztos vagyok benne, hogy a feketék tették. Biztosan a kincseskamrát próbálják megtalálni. Kétlem, hogy sikerrel járnak, túl régen volt már, ha-ha! Söpredék...";
			link.l1 = "Értem. Köszönöm az érdekes történetet!";
			link.l1.go = "dolly_5";
		break;
		
		case "dolly_5":
			dialog.text = "Szívesen, mindig szívesen beszélgetek!";
			link.l1 = "Ég veled!";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.LSC.Betancur");
			AddQuestRecord("LSC", "16");
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Hallgatlak, haver.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Szóval a Szigeten kívül mást nem láttál még életedben?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "Te itt születtél... És miért nem vagy a Narvál klán tagja? Azt hittem, hogy minden fehér ôslakos narvál...";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "És mit csinálsz a Szigeten?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Mondd csak, akartad valaha is elhagyni a Szigetet egy idôre? Látni a világot...";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Nincs kérdés. Elnézést...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Úgy tûnik, igen. De ne higgye, hogy idióta vagy szûklátókörû vagyok. Nagyapámtól remek könyvtárat örököltem, apám pedig kiváló nevelést biztosított számomra. Ismerem az ókori történelmet, a földrajzot, a csillagászatot, tudok angolul, franciául, spanyolul és még latinul is\nSok tengerész, aki mindenhol megfordult, kevesebbet tud, mint én. Bár ezeken a hajóroncsokon kívül semmit sem láttam, gondolatban jártam Európában, Kínában és Indiában...";
			link.l1 = "Értem...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Ez nem igaz, bár kilencven százalékban igazad van. De én nem vagyok narvál, és nem is akarok közéjük tartozni. Milyen céllal? Hogy órákig ôrködjek, mint egy bolond, vagy hogy Rivadókkal harcoljak? Szó sem lehet róla, kímélj meg ettôl. Én más vagyok. Inkább önállóan élek és könyveket olvasok.";
			link.l1 = "Értem...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "Apám tisztességes örökséget hagyott rám, és gondosan költöm. Így nem kell régi hajóroncsok körül ólálkodnom, hogy ékszereket találjak, amiket élelemre cserélhetek. Nem hiszek a régi hajókban rejlô nagy kincsekben\nAz egyetlen kincs, amit ismerek, a Szent Anna kincstár. Az egy nagy vasláda. De még senkinek sem sikerült megtalálnia\nMeg fogom írni a sziget részletes történetét a helyi történetek alapján. Mit gondoltok - próbálkozzak?";
			link.l1 = "Biztos vagyok benne. Ismerek legalább egy embert a szigetvilágban, aki sok aranyat fizetne egy ilyen könyvért. Szóval itt a lehetôség...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Néha elgondolkodom rajta. Talán ha idejönne az a hajó, amelyik képes megbirkózni az árral és túlélni a viharokat, akkor megkockáztatnám. Nagyon várom már, hogy lássam a dolgokat, amiket olyan érdekesen leírtak a könyveimben! De ezek egyelôre csak álmok...";
			link.l1 = "Az álmok valóra válnak. Csak higgy bennük...";
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
