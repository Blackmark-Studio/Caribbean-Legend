// Ришард Шамбон - контрабандист
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	float locx, locy, locz;

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
			// --> кольцо
			if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "find" && CheckAttribute(npchar, "quest.answer_2") && GetNpcQuestPastDayParam(npchar, "quest_date") >= 3 && !CheckAttribute(npchar, "quest.ring"))
			{
				dialog.text = "Ó! Hát itt vagy, haver. Én meg arra gondoltam, hogy egyedül találom meg magát. Szükségem van rád, barátom.";
				link.l1 = "Ma gyanúsan barátságos vagy, Richard. Nos, én hallgatlak.";
				link.l1.go = "ring";
				break;
			}
			// <-- кольцо
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Mit akarsz? Hogy ôszinte legyek, ma nem vagyok jó hangulatban. Igazából már el is felejtettem, mikor voltam utoljára ilyen hangulatban.";
				link.l1 = "Tényleg ennyire rossz a helyzet, haver?";
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
			dialog.text = "Rossz? Nem, nem rossz. Csak nem vagyok jó hangulatban. Szóval, mit akartál?";
			link.l1 = "Csak meg akartalak ismerni. Új vagyok itt, úgyhogy csak sétálgatok a szigeten, és ismerkedem az emberekkel.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "Tényleg? Igen. Akkor jó. Richard Shambon vagyok. Réges-régen értékes árukkal kereskedtem, és némelyikük illegális volt, de az elmúlt kilenc évben hajóroncsokat dögönyöztem, roncsokat kerestem, és azokat élelmiszerre és aranyra cseréltem.";
			link.l1 = "És én vagyok "+GetFullName(pchar)+", egy kapitány...";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "A volt kapitányra gondolsz, ha-ha?";
			link.l1 = "Nos, valójában a hajóm most Blueweldben van. Én pedig egy tartánon hajózom ide.";
			link.l1.go = "meeting_3";
		break;
		
		case "meeting_3":
			dialog.text = "Tényleg? Az lehetetlen! És hol van most a tartánja?";
			link.l1 = "Hm... az alján.";
			link.l1.go = "meeting_4";
		break;
		
		case "meeting_4":
			dialog.text = "A-ah... És én még azt hittem... Mindegy, haver, jobb, ha iszom egy kis rumot...";
			link.l1 = "Sok szerencsét hozzá. Jó volt beszélgetni veled. Viszlát!";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Van valami érdekes mondanivalód?", "Történt valami újdonság a szigeten?", "Elmondanád az utolsó pletykákat?");
			link.l2.go = "rumours_LSC";
			link.l3 = "Szeretnék feltenni néhány kérdést a szigetrôl.";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
		// Кольцо
		case "ring":
			dialog.text = "És más voltam korábban? Ugyan már, voltak rossz napjaim, mindenkinek vannak néha! Mondd csak, azt pletykálják a Szigeten, hogy kiváló harcos vagy. Igaz ez?";
			link.l1 = "Nem tudom, mit mondanak, de tudom, hogyan kell bánni a karddal, ha ezt kérdezed.";
			link.l1.go = "ring_1";
			npchar.quest.ring = "true";
		break;
		
		case "ring_1":
			dialog.text = "Megvan. Látom, hogy a pletykák igazak voltak... Figyelj, "+pchar.name+", emlékszel, hogy meséltem neked a külsô gyûrûrôl? És az értékes dolgokról, amiket ott találhatsz?";
			link.l1 = "Ti mindannyian szerettek arról a gyûrûrôl beszélni... És mindannyian ugyanazt mondjátok.";
			link.l1.go = "ring_2";
		break;
		
		case "ring_2":
			dialog.text = "Mi mást lehetne még mondani, ha-ha! Jól van. Rátérek a lényegre. (leereszti a hangját) Találtam egy érintetlen hajót a külsô gyûrûnél, jó állapotban van, ami elég ritka\nA hajó nagy, egy pinnace. Nemrég hajtották ide, körülbelül két hónapja, vagy még kevesebb. Mások még nem találták meg, így van esély arra, hogy jó pénzt keressünk a raktér és a kabinok kifosztásával.";
			link.l1 = "Szép, örülök neked. De mi közöm nekem ehhez? Meg akarsz kérni, hogy menjek veled oda?";
			link.l1.go = "ring_3";
		break;
		
		case "ring_3":
			dialog.text = "Pontosan! Figyeljetek. A pinace íja megsérült. Azok az átkozott rákok egy lyukon keresztül bejutottak, és egy átkozott fészket építettek benne. Beosonni, amíg ott vannak, nem megoldás, és fogalmam sincs, hogyan másszak fel a felsô fedélzetre\nSoha nem voltam jó harcos, és évek óta nem nyúltam pengéhez, úgyhogy egyedül nem fogom tudni megölni a lényeket. Ezért jöttem hozzád.";
			link.l1 = "Szóval azt javaslod, hogy öljem meg az összes rákot a hajóban, igaz?";
			link.l1.go = "ring_4";
		break;
		
		case "ring_4":
			dialog.text = "Igen. Megegyeztünk. Én megmutatom az utat a hajóhoz, te pedig megölöd a rákokat. Megosztjuk a zsákmányt, amit ott találunk. Ez egy tisztességes alku - én megtaláltam a hajót, te pedig megtisztítod.";
			link.l1 = "Nem, haver, nem érdekel. Nem az én stílusom, hogy egy félig elsüllyedt hajóban harcoljak a rákokkal néhány kétes trófeáért. Keress magadnak egy másik kockázatos fiút, aki kihúzza neked a gesztenyét a tûzbôl.";
			link.l1.go = "ring_exit";
			link.l2 = "Érdekes... Már régóta gondolkodtam azon, hogy megnézem a külsô gyûrût. Megegyeztünk! Megölöm a rákokat.";
			link.l2.go = "ring_5";
		break;
		
		case "ring_exit":
			dialog.text = "Kár... Hibát követtél el. A külsô gyûrû hajóiban rengeteg szaftos dolog van... És senki sem járt még azon a hajón. Rendben, ez a te kívánságod. Viszontlátásra...";
			link.l1 = "Viszlát, haver...";
			link.l1.go = "exit";
		break;
		
		case "ring_5":
			dialog.text = "Örülök, hogy igazam volt veled kapcsolatban, barátom. Van egy olyan érzésem, hogy sok érdekes dolgot fogunk találni benne...";
			link.l1 = "Majd meglátjuk. Tudod, hány rák van benne?";
			link.l1.go = "ring_6";
		break;
		
		case "ring_6":
			dialog.text = "Azt hiszem, négy vagy öt... Hát, átlagosan.";
			link.l1 = "Nekem megfelel. Mikor megyünk?";
			link.l1.go = "ring_7";
		break;
		
		case "ring_7":
			dialog.text = "Menjünk oda holnap, fel kell készülnünk. Szerezzünk ellenszert Julian testvértôl, a rákok állkapcsa mérgezô. Óvatosságra intünk. Találkozzunk holnap reggel nyolc órakor a 'oblique fedélzeten'. Tudod, hol van?";
			link.l1 = "Nem tudom. Magyarázza meg.";
			link.l1.go = "ring_8";
		break;
		
		case "ring_8":
			dialog.text = "A 'San Augustine'. mögött egy régi hajó roncsa van, az orra a víz alatt van, a hátsó része pedig a magasba emelkedik. Ezért hívják a 'ferdülô fedélzetnek'. oda csak úszva lehet eljutni. Csak kezdj el úszni a híd alatti helyrôl, és fordulj meg a 'San Augustine'. bármelyik oldaláról, onnan együtt úszunk.";
			link.l1 = "Rendben. Holnap találkozunk!";
			link.l1.go = "ring_9";
		break;
		
		case "ring_repeat":
			dialog.text = "8 óránál, 'ferde fedélzet'....";
			link.l1 = "Igen, igen, emlékszem rá...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ring_repeat";
		break;
		
		case "ring_9":
			DialogExit();
			NextDiag.CurrentNode = "ring_repeat";
			pchar.quest.LSC_Ring_Start.win_condition.l1 = "Timer";
			pchar.quest.LSC_Ring_Start.win_condition.l1.date.hour  = 7.0;
			pchar.quest.LSC_Ring_Start.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.LSC_Ring_Start.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.LSC_Ring_Start.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.LSC_Ring_Start.function = "LSC_RingStart"; // готовы
			pchar.quest.LSC_Ring_Over.win_condition.l1 = "Timer";
			pchar.quest.LSC_Ring_Over.win_condition.l1.date.hour  = 10.0;
			pchar.quest.LSC_Ring_Over.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.LSC_Ring_Over.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.LSC_Ring_Over.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.LSC_Ring_Over.function = "LSC_RingOver"; // опоздание
			AddQuestRecord("LSC_Ring", "1");
		break;
		
		case "ring_10":
			dialog.text = "Aha, itt vagy, haver. Készen állsz egy kis rák salátát készíteni?";
			link.l1 = "Persze!";
			link.l1.go = "ring_11";
		break;
		
		case "ring_11":
			dialog.text = "Nagyon jó. Most fordítsd a fejed a külsô gyûrû felé és nézd meg. Látod, hogy két hajóroncs áll ki a vízbôl?";
			link.l1 = "Hm... Igen, készen állok.";
			link.l1.go = "ring_12";
		break;
		
		case "ring_12":
			dialog.text = "Most nézz közéjük a külsô gyûrû felé. Látod a gályát, aminek az orra felhúzva van? Éppen felénk tart. Nézzétek meg alaposan.";
			link.l1 = "...";
			link.l1.go = "ring_look";
		break;
		
		case "ring_look":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorTurnToLocator(pchar, "reload", "reload_ring");
			DoQuestCheckDelay("LSC_RingTalkLook", 6.0);
		break;
		
		case "ring_13":
			dialog.text = "";
			link.l1 = "Azt hiszem, látom... Igen!";
			link.l1.go = "ring_13a";
		break;
		
		case "ring_13a":
			dialog.text = "Ez a célpontunk. Ússz egyenesen és ne fordulj meg. Megmutatom a visszaútvonalat, amikor elérjük a külsô gyûrût. A raktér bejárata a hajó orrán lévô lyuk. Tudjátok, hogy addig nem megyek be oda, amíg nem öltök meg minden rákot.";
			link.l1 = " Igen, tegnap megegyeztünk, emlékszem. Te megmutatod a hajót, én pedig megölöm a rákokat. Ússzunk?";
			link.l1.go = "ring_14";
		break;
		
		case "ring_14":
			dialog.text = "Persze! Megyek utánad.";
			link.l1 = "...";
			link.l1.go = "ring_swim";
		break;
		
		case "ring_swim":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			LAi_SetImmortal(npchar, true);
			pchar.quest.LSC_Ring_enter.win_condition.l1 = "locator";
			pchar.quest.LSC_Ring_enter.win_condition.l1.location = "LostShipsCity_town";
			pchar.quest.LSC_Ring_enter.win_condition.l1.locator_group = "reload";
			pchar.quest.LSC_Ring_enter.win_condition.l1.locator = "reload_ring";
			pchar.quest.LSC_Ring_enter.function = "LSC_RingEnter";
			LSC_RingSetItems(); // раскладка итемзов
			AddQuestRecord("LSC_Ring", "3");
		break;
		
		case "ring_15":
			dialog.text = "Heh, szép munka! Megölted ezt a sok mocskot!";
			link.l1 = "Emlékszem, hogy valaki mesélt nekem 'négy vagy öt' rákról... Emlékeztess, ki tette ezt?";
			link.l1.go = "ring_16";
		break;
		
		case "ring_16":
			dialog.text = "Pajtás, én nem mentem be a raktérbe, hogy megszámoljam ôket rendesen. Csak benéztem a lyukon. Nem állt szándékomban hazudni neked.";
			link.l1 = "Mindegy. Nézzük meg a raktérben...";
			link.l1.go = "ring_17";
		break;
		
		case "ring_17":
			dialog.text = "Persze! Ezért vagyunk itt, igaz?";
			link.l1 = "Pontosan! Ne vesztegessük az idônket...";
			link.l1.go = "ring_18";
		break;
		
		case "ring_18":
			DialogExit();
			NextDiag.CurrentNode = "ring_wait";
			LAi_SetWarriorType(npchar);
			LAi_warrior_DialogEnable(npchar, true);
			LAi_group_MoveCharacter(npchar, "TMP_FRIEND");
			DoQuestCheckDelay("LSC_RingDialog", 60.0); // 1 минуту на пошариться
			npchar.quest.diagnode = "ring_19";
			AddQuestRecord("LSC_Ring", "4");
		break;
		
		case "ring_wait":
			dialog.text = "Várj egy kicsit, haver, még nem néztem meg minden helyet, amit akartam. Keress jobban, talán találsz még értékeket.";
			link.l1 = "Rendben...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ring_wait";
		break;
		
		case "ring_19":
			dialog.text = "Semmi különös. Kár, hogy itt nincsenek értékes dolgok. Van élelem a hordókban és kopra a ládákban. Találtam egy ládát drága borral is. És nálad mi van?";
			link.l1 = "Semmi érdekes. Néhány láda elég értékes, de a többi kukoricahús és kopra, ahogy mondtad.";
			link.l1.go = "ring_20";
		break;
		
		case "ring_20":
			dialog.text = "Nem elég... Menjünk fel az emeletre, és nézzük meg a felsô fedélzetet és a kabinokat.";
			link.l1 = "Gyerünk, menjünk.";
			link.l1.go = "ring_21";
		break;
		
		case "ring_21":
			DialogExit();
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("ExternalRingInside", "reload1", true);
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			pchar.quest.LSC_Ring_deck.win_condition.l1 = "ExitFromLocation";
			pchar.quest.LSC_Ring_deck.win_condition.l1.location = pchar.location;
			pchar.quest.LSC_Ring_deck.win_condition = "LSC_RingEnterDeck";
			for (i=1; i<=3; i++)
			{
				sld = ItemsFromID("purse"+i);
				sld.shown = true;
				sld.startLocation = "ExternalRingDeck";
				sld.startLocator = "item"+i;
			}
		break;
		
		case "ring_22":
			dialog.text = "A francba! Ezt nézd meg! Az átkozott rákok mocskai eljutottak a fedélzetre! És hogy sikerült nekik ez a trükk?!";
			link.l1 = "Ne légy gyáva! Maradj itt, ne mozdulj, és ne hívd fel magadra a figyelmüket! Azonnal elintézem azokat a lényeket...";
			link.l1.go = "ring_23";
		break;
		
		case "ring_23":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocator(npchar, "reload", "reload1", "", -1);
		break;
		
		case "ring_24":
			dialog.text = "Huh! Szóval igazak voltak a mesék a vívótudásodról! Ha egyedül lennék itt, átugranék a fedélzeten...";
			link.l1 = "Figyelj, és hogyan lettél csempész a múltban, huh? Vagy mindenki elôl menekültél?";
			link.l1.go = "ring_25";
		break;
		
		case "ring_25":
			dialog.text = "Elôször is, fiatalabb, erôsebb és vakmerôbb voltam. Másodszor, nem azért vagyok zsoldos, hogy háborúkat vívjak - csempész vagyok, és mindig igyekszünk elkerülni a vérontást. Harmadszor, én mindig is a vitorlák és a kormányrúd, nem pedig a pengék és a pisztolyok híve voltam. És végül, az itt eltöltött évek puhává tettek\nSzóval ne hibáztassanak. Nézzük meg a felsô fedélzetet. Úgy néz ki, mintha a hajó komoly harcban vett volna részt - nézd meg a sérüléseket...";
			link.l1 = "Igazad van. A hajó határozottan heves tûz alatt állt. Rendben, keressünk valami érdekeset.";
			link.l1.go = "ring_26";
		break;
		
		case "ring_26":
			dialog.text = "Hát persze. És meg kell találnunk a bejáratokat a belsô helyiségekbe.";
			link.l1 = "Rendben, ne vesztegessük az idôt. Hívjatok, ha láttok egy rákot.";
			link.l1.go = "ring_27";
		break;
		
		case "ring_27":
			DialogExit();
			NextDiag.CurrentNode = "ring_wait";
			LAi_SetWarriorType(npchar);
			LAi_warrior_DialogEnable(npchar, true);
			LAi_group_MoveCharacter(npchar, "TMP_FRIEND");
			DoQuestCheckDelay("LSC_RingDialog", 80.0); // 1.3 минуты на пошариться
			npchar.quest.diagnode = "ring_28";
			AddQuestRecord("LSC_Ring", "5");
		break;
		
		case "ring_28":
			dialog.text = "Megint semmi értékeset... Találtam néhány érdekes apróságot, és ennyi. De nem baj, a fedélzeteken általában nincsenek értékes nyalánkságok. A legjobbaknak a kabinokban kell lenniük. Ott van a kapitányi kabinok bejárata. Nézzük meg.";
			link.l1 = "Legyünk óvatosak, ki tudja, mi vár ott ránk. Talán jobb lenne, ha én mennék be oda elôször?";
			link.l1.go = "ring_29";
		break;
		
		case "ring_29":
			dialog.text = "Gyerünk, "+pchar.name+". Nem bújok többé a hátad mögé. Kár, az biztos...";
			link.l1 = "Akkor menjünk...";
			link.l1.go = "ring_30";
		break;
		
		case "ring_30":
			DialogExit();
			chrDisableReloadToLocation = true;
			LocatorReloadEnterDisable("ExternalRingDeck", "reload2", false);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2", "ExternalRingCabin1", "reload", "reload1", "OpenTheDoors", -1);
			pchar.quest.LSC_Ring_cabin.win_condition.l1 = "location";
			pchar.quest.LSC_Ring_cabin.win_condition.l1.location = "ExternalRingCabin1";
			pchar.quest.LSC_Ring_cabin.win_condition = "LSC_RingEnterCabin";
			sld = ItemsFromID("RingCapBook"); // кладем журнал 'Санта-Люсии'
			sld.shown = true;
			sld.startLocation = "ExternalRingCabin1";
			sld.startLocator = "item1";
		break;
		
		case "ring_31":
			dialog.text = "Úgy tûnik, szerencsém volt - se rákok, se más mocsok nincs itt. És most felforgatjuk ezt a kunyhót, basszus, esküszöm, hogy kezdek dühös lenni. Csak két kibaszott tucatnyi dublont és néhány apróságot találtam!";
			link.l1 = "Nyugodj meg. Igazad volt, minden értéktárgyat mindig a kapitányi kabinban rejtünk el. Lássuk, mi van itt!";
			link.l1.go = "ring_32";
		break;
		
		case "ring_32":
			DialogExit();
			NextDiag.CurrentNode = "ring_wait";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "goto", "goto2", "LSC_RingSetToBarman", -1);
			DoQuestCheckDelay("LSC_RingDialog", 30.0); // 30 сек на пошариться
			npchar.quest.diagnode = "ring_33";
		break;
		
		case "ring_33":
			dialog.text = "Ha-ha! Ahogy gondoltam! Ismerem a kereskedôk szokásait, szeretnek titkos rejtekhelyeket csinálni, és oda rejteni a hajó kincstárát! Ennek a hajónak a kapitánya egy ravasz gazember volt, de engem nem lehet ilyen könnyen átverni! Nézd, mit találtam! Nélkülem soha nem találnátok meg!";
			link.l1 = "Mutasd meg!";
			link.l1.go = "ring_34";
		break;
		
		case "ring_34":
			dialog.text = "Negyvenezer pezó, két láda tele dublonnal, egy csomag smaragd és egy csomó ékszer! A tulajdonos elég gazdag volt... Rendben, legalább ez meghálálja a fáradozásunkat, bár arra számítottam, hogy több cuccot kapok. Osszuk meg igazságosan.";
			link.l1 = "Kitûnô, Richard. Legalább szereztünk egy kis pénzt!";
			link.l1.go = "ring_35";
		break;
		
		case "ring_35":
			TakeNItems(pchar, "jewelry4", 25);
			TakeNItems(pchar, "chest", 1);
			TakeNItems(pchar, "icollection", 1);
			AddMoneyToCharacter(pchar, 20000);
			Log_Info("Kaptál egy ládát dublonnal");
			Log_Info("Kaptál 25 smaragdot");
			Log_Info("Kaptál egy ékszergyûjteményt");
			PlaySound("interface\important_item.wav");
			dialog.text = "Nos, és tartsuk meg magunknak, amit a fedélzeten találtunk. Rendben van ez így? Találtatok valami hasznosat a ládákban és a szekrényekben?";
			link.l1 = "Néhány indián holmit, amuletteket, papírokat és így tovább.";
			link.l1.go = "ring_36";
		break;
		
		case "ring_36":
			dialog.text = "Tartsátok meg magatoknak. Végül is te végezted a legkockázatosabb munkát.";
			if (CheckAttribute(pchar, "questTemp.LSC.Ring.ReadCapBook")) // прочел журнал
			{
				link.l1 = "Rendben. És találtam még valamit, amit egy ilyen kincsvadász, mint te, hasznosnak találhat. Itt egy kapitányi napló hevert az asztalon. A történet, ami benne van, nagyon szomorú... de valamilyen módon érint minket. A raktérben van egy doboz elrejtve, ami tele van arannyal! Olvassátok el!";
				link.l1.go = "ring_41";
			}
			else
			{
				if (CheckCharacterItem(pchar, "RingCapBook")) // взял журнал
				{
					link.l1 = "Rendben. De találtam még valamit - a kapitány naplóját.";
					link.l1.go = "ring_38";
				}
				else
				{
					link.l1 = "Rendben, egyetértek az ilyen feltételekkel, ha-ha. Szóval, itt az ideje visszatérni?";
					link.l1.go = "ring_37";
				}
			}
		break;
		
		case "ring_37":
			dialog.text = "Igen. Ne beszélj senkinek a hajóról, ez a mi titkunk marad. Persze, nincs szükségünk koprára, de az ellátmány hasznos lesz számunkra. Nem kell többé az admirálistól vásárolnunk.";
			link.l1 = "Rendben, egyetértek. Remélem, hogy mások nem találják meg a hajót hamarosan. Gyerünk, menjünk!";
			link.l1.go = "ring_cabin_exit";
		break;
		
		case "ring_38":
			dialog.text = "Olvastad?";
			link.l1 = "Még nem...";
			link.l1.go = "ring_39";
		break;
		
		case "ring_39":
			dialog.text = "Akkor olvassuk el! Fontos információkat tudhatunk meg belôle. Az is érdekes lesz, hogy hogyan került ide. Olvassátok el!";
			link.l1 = "Hm. Rendben, most elolvasom...";
			link.l1.go = "ring_40";
		break;
		
		case "ring_40":
			DialogExit();
			NextDiag.CurrentNode = "book_wait";
			LAi_SetWarriorType(npchar);
			LAi_warrior_DialogEnable(npchar, true);
			LAi_group_MoveCharacter(npchar, "TMP_FRIEND");
		break;
		
		case "book_wait":
			dialog.text = "Elolvastad? Mi van benne?";
			if (CheckAttribute(pchar, "questTemp.LSC.Ring.ReadCapBook")) // прочел журнал
			{
				link.l1 = "Nos, akkor figyelj... A történet nagyon szomorú... de valamilyen módon érint minket. A kincskeresô képességeid talán segíthetnek nekünk. Van egy elrejtett, arannyal teli doboz a raktérben! Olvasd el!";
				link.l1.go = "ring_41";
			}
			else
			{
				link.l1 = "Várj egy kicsit. Elolvasom és elmondom...";
				link.l1.go = "exit";
				NextDiag.TempNode = "book_wait";
			}
		break;
		
		case "ring_41":
			dialog.text = "Tényleg? "+pchar.name+", én... nos, nem olvasok olyan jól. Mondd el, hogy mi van ott részletesen leírva, hm?";
			link.l1 = "Röviden: ez a pinnacé a Karib-tengeren kelt át a Dél-Fôszigetrôl Új-Spanyolországba. A kapitány feleségül vette egy alsó Orinoco törzs indián hercegnôjét. A nô elmondta neki, hogy a népe hol áldozott...";
			link.l1.go = "ring_42";
		break;
		
		case "ring_42":
			dialog.text = "";
			link.l1 = "Az aranyrögök voltak az áldozataik. Persze, bátor kapitányunk az elsôtiszt és a szállásmester segítségével kirabolta ezt az aranyraktárat. A raktérbe tették, az egyik ládába, és koprával fedték le...";
			link.l1.go = "ring_43";
		break;
		
		case "ring_43":
			dialog.text = "";
			link.l1 = "De úgy tûnik, hogy az indiánok szent helyének kirablását megbüntették. A hajó holtvágányra került, a vízkészletek fogytán voltak, lázjárvány tört ki, és kalózok támadtak a hajóra. A tengerészek az indiai lányt, a kapitány feleségét hibáztatták, és követelték, hogy dobják ki a fedélzetre. Természetesen a kapitány ezt visszautasította, és a legénység zendülésbe kezdett...";
			link.l1.go = "ring_44";
		break;
		
		case "ring_44":
			dialog.text = "";
			link.l1 = "A kapitány elvesztette a harcot. Az utolsó feljegyzések szerint - az indiai lánnyal bezárkózott a kabinba, és megpróbálta lelôni a feldühödött matrózokat, akik betörték az ajtót. És vihar közeledett feléjük... úgy tûnik, ez hozta ide a hajót. A történet vége egyértelmû: a lányt lelôtték, a kapitányt pedig biztosan megölték a lázadók.";
			link.l1.go = "ring_45";
		break;
		
		case "ring_45":
			dialog.text = "Hm. Ez tényleg egy szomorú történet. De nem viccelsz velem? Van egy doboz arany a raktérben? Nem hiszek a fülemnek! Melyik az? Menjünk oda! Minden bálát, minden hordót megnézek!";
			link.l1 = "Gyerünk, menjünk! Én is alig várom, hogy elkezdhessem a keresést.";
			link.l1.go = "ring_seek_gold";
		break;
		
		case "ring_cabin_exit":
			DialogExit();
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("ExternalRingInside", "reload1", false); // открываем выход
			LocatorReloadEnterDisable("LostShipsCity_town", "reload_ring", false); // открываем вход // patch-2
			DoQuestReloadToLocation("ExternalRingDeck", "reload", "reload2", "LSC_RingFinalStage");
			sld = ItemsFromID("RingCapBook");
			sld.shown = false; // убираем журнал
			AddQuestRecord("LSC_Ring", "6");
		break;
		
		case "ring_seek_gold":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			// ставим прерывание на локатор
			pchar.quest.LSC_Ring_gold.win_condition.l1 = "locator";
			pchar.quest.LSC_Ring_gold.win_condition.l1.location = "ExternalRingInside";
			pchar.quest.LSC_Ring_gold.win_condition.l1.locator_group = "quest";
			pchar.quest.LSC_Ring_gold.win_condition.l1.locator = "gold";
			pchar.quest.LSC_Ring_gold.win_condition = "LSC_RingFindGold";
			// подменяем состав бокса
			pchar.GenQuestBox.ExternalRingInside = true;
			pchar.GenQuestBox.ExternalRingInside.box1.items.jewelry5 = 2522;
			AddQuestRecord("LSC_Ring", "7");
		break;
		
		case "ring_46":
			dialog.text = "Ha-ha! Megtaláltuk! Tényleg létezik! Nézzétek azt a hatalmas kupacot! Az egész láda! Ötezer rög van benne, nem kevesebb! Soha nem láttam még ennyi aranyat!";
			link.l1 = "Gratulálok, partner. Úgy tûnik, hogy a vállalkozásunk sikeresen véget ért... Mit fogunk csinálni ezzel a sok arannyal?";
			link.l1.go = "ring_47";
		break;
		
		case "ring_47":
			dialog.text = "Hogy érted ezt? Felezzük el!";
			link.l1 = "Persze, hogy el fogjuk. Hol akarod tartani? Itt hagyjátok?";
			link.l1.go = "ring_48";
		break;
		
		case "ring_48":
			dialog.text = "Ha! Biztosan elrejtem az aranyat a rejtekhelyeimen, és soha senki nem fogja megtalálni. A rejtegetés az, amihez jól értek! Mozgassuk meg az arany felét ebben a hordóban, az lenne az én részem. Elviszem napnyugta elôtt.\nA részeddel azt csinálsz, amit akarsz. De jobb lenne, ha a saját rejtekhelyetekre is átraknátok. Ne engem hibáztassatok, ha eltûnik az aranyatok. Én becsületes ember vagyok, a magam becsületes módján, és nem merem elvenni a részedet. De mások, azok, akik késôbb idejönnek... ôk talán megtalálják.";
			link.l1 = "Rendben. Majd én eldöntöm, hogy mit csinálok az aranyammal. Tegyük a te részedet egy hordóba...";
			link.l1.go = "ring_49";
		break;
		
		case "ring_49":
			DialogExit();
			SetLaunchFrameFormParam("Két órával késôbb..."+ NewStr() +"Az aranyat megosztották!", "", 0, 5);//табличка
			WaitDate("", 0, 0, 0, 2, 10);
			LaunchFrameForm();
			RecalculateJumpTable();
			sld = characterFromId("LSC_Rishard");
			sld.quest.diagnode = "ring_50";
			DoQuestCheckDelay("LSC_RingDialog", 5.0);
		break;
		
		case "ring_50":
			dialog.text = "Kész... Köszönöm, "+pchar.name+", hogy eljöttél velem. Nélküled nem tudnám megcsinálni. Most már meg kellene fontolnom egy tartán építését... hogy elhajózzak innen... Á, mindegy. Majd késôbb elgondolkodom rajta\nMég van egy kis dolgom - biztonságos helyre kell vinnem az aranyat. Isten veled, barátom, kívánom, hogy bölcsen használd fel a vágásodat!";
			link.l1 = "Viszlát, Richard. Csodálatos nap volt a mai. Viszlát!";
			link.l1.go = "ring_51";
		break;
		
		case "ring_51":
			DialogExit();
			LocatorReloadEnterDisable("ExternalRingInside", "reload1", false); // открываем выход
			LocatorReloadEnterDisable("LostShipsCity_town", "reload_ring", false); // открываем вход
			DoQuestCheckDelay("LSC_RingFinalStage", 0.5);
			DeleteAttribute(pchar, "questTemp.LSC.Ring.ReadCapBook");
			AddQuestRecord("LSC_Ring", "8");
		break;
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "Kérdések? Ó, rendben, ha tényleg szükséged van rá...";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "Hogy kerültél ide?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "El akarod hagyni a szigetet?";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "Gondoltál már arra, hogy csatlakozz valamelyik klánhoz? Például a Narwhals-hoz?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "Igaz, hogy a külsô gyûrûben sok érdekes dolgot lehet találni?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "Nincs kérdés. Elnézést...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "Tíz éven át én és a társaim egy jól felszerelt tartánon hajóztunk Kubából a szigetre. Titokban tartottuk a Sziget helyét - bikatetemeket szállítottunk, és a friss húst árucikkekért és aranyért adtuk el a helyi hajórakodóknak\nJó idôk! Az ellátással itt mindig gond volt, fôleg kenyérrel és sózott marhahússal, így a szaftos, fûszeres húsért fizettek nekünk, ami Európában egy vagyonba kerül! Minden egyes hajóúton annyi pénzt kerestem, hogy Tortuga összes kurváját megvehettem volna\nDe mindennek vége van, így volt ez a mi elégedett életünk is. Az idôjárás elromlott - a viharok erôsödtek, így a szigetre hajózás sokkal veszélyesebbé vált. Néhány társam otthagyta az üzletet, de én és egy tucat bátor ember\nvégül a Szigettôl két mérföldnyire egy zátonyra vetett minket. Még mindig nem értem, hogyan sikerült átúsznom a viharos tengeren. Így kerültem azok közé, akikkel a múltban kereskedtem.";
			link.l1 = "Érdekes történet...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "Ha! Elmegyek innen, a fenébe is! De majd késôbb. Mit csinálnék Kubában? Nincsenek már barátaim, és a zsebem üres. Rögtön elkezdek építeni egy hajót, miután a külsô gyûrûnél találok egy hajót értékes rakománnyal vagy egy halom dublont.";
			link.l1 = "Értem...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
			SaveCurrentNpcQuestDateParam(npchar, "quest_date");
		break;
		
		case "ansewer_3":
			dialog.text = "És miért is tenném? Hogy minden harmadik nap ôrködjek, mint egy idióta, és távol tartsam az embereket a San Gabrieltôl? És nem szeretnek új embereket felvenni. Ôk helyi ôslakosok... És a négerek ugyanilyenek. Nem, jobb lesz, ha magamra maradok.";
			link.l1 = "Értem...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "Persze! Ez az, ami a szigetet és a helyieket még mindig élôvé teszi. Tudod, mikor vannak itt bulik? Amikor egy új hajó érkezik. De mindegy is, a külsô gyûrûnél rengeteg érintetlen hajó van, tele arannyal és áruval\nA probléma az, hogy a külsô gyûrût szinte lehetetlen felfedezni, a dolgok rendetlenek odakint, ha belegabalyodsz, megcsúszol vagy csúnyán elesel - olyan lyukban találhatod magad, amit nem tudsz magadtól elhagyni. Akkor végeztél. Sokan meghaltak így.";
			link.l1 = "Hm... Érdekes.";
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
