void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	bool ok;
    int iTest;
    ref rColony;
    string sFrom_sea = "";
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
		dialog.text = "Bogár. Szólj a fejlesztôknek.";
		link.l1 = "Persze.";
		link.l1.go = "exit";
		break;
		
		case "Avendel_tavern":
			pchar.quest.Portugal_BeginOver.over = "yes";
			dialog.text = "Ó, még egy bátor tengerész! Ismerem a fajtádat, az istenverte szemem máris rád szegezôdött, ha! Kérdezd meg, miért?";
			link.l1 = "Másról kérdezlek, az adósságodról van szó, amivel tartozol a helyi... ööö... létesítmény úrnôjének. Megkért, hogy emlékeztesselek a tartozásodra, javaslom, hogy tegyél valamit, különben holnap az ôrökhöz kell fordulnia, hogy ugyanezt tegyék.";
			link.l1.go = "Avendel_tavern_1";
			DelLandQuestMark(npchar);
		break;
		
		case "Avendel_tavern_1":
			dialog.text = "Helyi... ó, bassza meg! Johanna, ezt nem teheti velem! Biztos vagy benne? Tényleg azt mondta, hogy néhány istenverte érméért elküld a kazamatákba?";
			link.l1 = "Teljesen. Ezt mondta. Azt hiszem, a küldetésemnek vége, viszlát, mynheer Avendell.";
			link.l1.go = "Avendel_tavern_2";
		break;
		
		case "Avendel_tavern_2":
			dialog.text = "Várjon! Kérem, várjon! Úgy nézel ki, mint egy tapasztalt kapitány. Biztos van nálad egy kis pénz, én le vagyok égve, csak a jó öreg csapos tölti meg a poharamat hitelre a régi barátságunk kedvéért. Hallgassa meg a pro... ajánlatomat! Kifizeted az adósságomat, és én vágok neked egy szeletet\nVan egy üzlet... egy nagyon jövedelmezô üzlet, csessz meg engem és a seggemet! Esküszöm az átkozott horgonyomra, csak bízz bennem, kapitány - akárhogy is hívnak!\nVáltozz meg egyetlen kis adósságodért, tízezer pezóért, és esélyed lesz annyi érmét keresni, hogy megveheted az Új-véres-világ összes bordélyházát! Mit szólsz hozzá? Te adsz nekem, én adok neked, ahogy a becsületes emberek szokták...";
			link.l1 = "Egy rongyos fickó, aki kincseket ígér. Kímélj meg ettôl a szarságtól, én nem jótékonykodom a hozzád hasonlókért. Találd meg a pénzt, vagy hamarosan az erôd kazamatáiban fogsz élni. Viszlát!";
			link.l1.go = "Avendel_tavern_3";
			link.l2 = "Egy szeletet? És miért bíznék egy részeges idióta szavában? Képzeletbeli ígéretek miatt?";
			link.l2.go = "Avendel_tavern_4";
		break;
		
		case "Avendel_tavern_3":
			DialogExit();
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
			pchar.questTemp.Portugal = "end";
		break;
		
		case "Avendel_tavern_4":
			dialog.text = "Figyeljen rám, kapitány! Hic, lôjetek agyon, ha hazudok! De igazat mondok! Gondold meg, ha hazugságon kapsz, akkor azzal a szépséggel, amit az öveden hordasz, levágod a belemet! A fenébe is, a markolata ötször annyiba kerül, mint az én nyomorult adósságom! Szóval, mit mondasz? Nincs vesztenivalód!";
			link.l1 = "Elegem van a beszédeidbôl. Viszontlátásra.";
			link.l1.go = "Avendel_tavern_3";
			link.l2 = "Rendben, Hugo... Megkockáztatom, hogy elhiszem azt a badarságot, amit beszélsz. De ne feledd, hogy meg kell gyôznöd engem, és meg kell bizonyosodnod arról, hogy a pénzem nem ment kárba a semmiért, ha visszajövök, különben a te seggedet kockáztatod.";
			link.l2.go = "Avendel_tavern_5";
		break;
		
		case "Avendel_tavern_5":
			dialog.text = "Nincs szükség fenyegetésre, megértem. A szavamat adom, kapitány! Gazdagok leszünk! Jöjjön vissza, ha visszafizette ezt az átkozott adósságot, és beszélgetünk! Igen, beszélni fogunk! Nem hagyunk félre!";
			link.l1 = "Rendben, eltörlöm az adósságodat, de jobb, ha imádkozol, Hugo Avendell, hogy a 'javaslatod' megfeleljen nekem.";
			link.l1.go = "Avendel_tavern_6";
		break;
		
		case "Avendel_tavern_6":
			DialogExit();
			pchar.questTemp.Portugal = "HostressMoney";
			Nextdiag.Currentnode = "Avendel_repeat";
			AddLandQuestMark(characterFromId("Marigo_Hostess"), "questmarkmain");
		break;
		
		case "Avendel_repeat":
			dialog.text = "Kapitány, jöjjön vissza, amilyen gyorsan csak tud - ez az üzlet még elszaladhat.";
			link.l1 = "Igen, igen, hamarosan visszafizetem az adósságát.";
			link.l1.go = "exit";
			Nextdiag.TempNode = "Avendel_repeat";
		break;
		
		case "Avendel_tavern_7":
			pchar.quest.Portugal_BeginOver.over = "yes";
			dialog.text = "Visszajött, kapitány úr! A viharra és az istenverte mennydörgésre, de örülök, hogy látom! Mi lesz az adósságommal?";
			link.l1 = "Én már elintéztem, most rajtad a sor, Hugó. Meséld el a történetedet, és próbáld meg egy kicsit is hihetôvé tenni!";
			link.l1.go = "Avendel_tavern_8";
			DelLandQuestMark(npchar);
		break;
		
		case "Avendel_tavern_8":
			dialog.text = "Ne aggódjon, kapitány! Tudta, hogy fejvadász vagyok? Vagyis... az voltam. Azt hiszem, nem voltam elég szerencsés. Talán maga az Ördög sem volt olyan lúzer, mint én. Mindent elvesztettem az utolsó munkámmal... A legénység elszökött, és el kellett adnom a hajót az adósságok miatt...";
			link.l1 = "A hôsies múltadról már értesültem. Egyenesen a tárgyra, Hugo, ne kérdôjelezd meg a türelmemet.";
			link.l1.go = "Avendel_tavern_9";
		break;
		
		case "Avendel_tavern_9":
			dialog.text = "Igen, igen, kapitány..."+GetFullName(pchar)+", igazam van? Én is tudok valamit rólad. De a fenébe is, ha fontos. Hallottad a portugál Bartolomeo nevét?";
			link.l1 = "Bart a portugál? Persze, hogy hallottam róla. Mindenki hallott róla. Egy kalóz, egy mészáros és egy söpredék, amennyire én tudom. És mi a szerepe a történetedben?";
			link.l1.go = "Avendel_tavern_10";
		break;
		
		case "Avendel_tavern_10":
			dialog.text = "Ô az istenverte fôszereplôje! Az elmúlt másfél évben követtem ôt. A holland társaság nagy vérdíjat tûzött ki a fejére. De kudarcot vallottam, és mindent elvesztettem. És a Társaság nemrég megháromszorozta a vérdíjat érte, élve, de élve, a fenébe is!";
			link.l1 = "Jó okkal, nem könnyû ôt élve elfogni. Különben is, miért érdekelne engem ez, Hugo? Úgy néz ki, hogy megpróbálsz átverni engem!";
			link.l1.go = "Avendel_tavern_11";
		break;
		
		case "Avendel_tavern_11":
			dialog.text = "Nem is akartam, kapitány úr! Tudja, a helyi orvos, Peter Van Stal, egy nagyon kedves ember, adott nekem egy fôzetet, ami meggyógyítja a fejfájásomat! Szóval, a doktor úr majdnem három napig nem volt a házában, és...";
			link.l1 = "Hugó, a türelmem majdnem elfogyott! Megígértem a hölgynek, hogy nem szúrom le a pengémmel, de az öklöm is megteszi! Esküszöm, hogy holnap egyetlen bájital sem lesz képes meggyógyítani a fejedet!";
			link.l1.go = "Avendel_tavern_12";
		break;
		
		case "Avendel_tavern_12":
			dialog.text = "Várjon, kapitány! Kérem! Figyeljen rám, láttam néhány fickót az orvos háza közelében, és felismertem ôket. A 'Albatross', egy fregattról jöttek, az átkozott portugáloktól! És az egyikük a kapitányuk egészségérôl beszélt! Nézd csak, " + pchar.name + ", Bartolomeo itt van, ebben a városban! Pont az orrunk elôtt, vagy megsebesült, vagy beteg, ezért van szükségük egy átkozott orvosra!\nKételkedem benne, hogy a portugálok az egész legénységét idehozták, de egyedül nem kezdhetem el ezt a zûrzavart! Bizonyára te átkozott tudsz bánni az átkozott kardoddal! Vigyél magaddal néhány kemény fickót, és megtaláljuk a patkányt! Aztán elfogjuk, és átadjuk a hatóságoknak!\nÉs kétezer jó aranydublon van a zsebünkben!";
			link.l1 = "Nem, Hugo, elegem van a beszédedbôl. Nem veszek részt ebben a zûrzavarban, még akkor sem, ha igazad van. Viszontlátásra.";
			link.l1.go = "Avendel_tavern_3";
			link.l2 = "Hmm, érdekes. Tudod, hol rejtôzik? Ha sikerül, akkor megbeszélhetjük a részvényeket, de ha igaz, amit mondasz, akkor sietnünk kell!";
			link.l2.go = "Avendel_tavern_13";
		break;
		
		case "Avendel_tavern_13":
			dialog.text = "Nem, nem tudom, hol van, kapitány. Túlságosan megijedtem, hogy lenyomozzam ezeket a fiúkat. Ha a Félszemû meglátott volna... fuh! De együtt, plusz az embereid, átfésülhetjük ezt az egész várost, hívd az embereidet és induljunk! A francba, a holland dublonok már várnak ránk! Ilyen istenverte lehetôség csak egyszer adódik az életben, harapj meg egy heringet!";
			link.l1 = "Dicséretes lelkesedés... Remélem, hogy sikerül elszakadnod az asztaltól, a 'great' bounty hunter. Azonnal keresni fogom, és ha akarod, követhetsz, csak ne zavarj túlságosan.";
			link.l1.go = "Avendel_tavern_14";
		break;
		
		case "Avendel_tavern_14":
			DialogExit();
			SetFunctionTimerCondition("Portugal_DoctorOver", 0, 0, 2, false);
			pchar.quest.Portugal_Guard.win_condition.l1 = "location";
			pchar.quest.Portugal_Guard.win_condition.l1.location = "Marigo_houseF1";
			pchar.quest.Portugal_Guard.function = "CreatePortugalGuard";
			AddQuestRecord("Portugal", "1");
			NextDiag.Currentnode = "Avendel_tavern_repeat";
			QuestPointerToLoc("marigo_town", "reload", "houseF1");
		break;
		
		case "Avendel_tavern_repeat":
			dialog.text = "Igen, igen, kapitány úr, csak hadd fejezzem be az italom, és csatlakozom önhöz... Hol kezdjük?";
			link.l1 = "Hová?! Megyek, veled vagy nélküled.";
			link.l1.go = "exit";
			Nextdiag.TempNode = "Avendel_tavern_repeat";
		break;
		
		case "Portugal_guard":
			dialog.text = "Rossz ház, haver. Tûnj el, most!";
			link.l1 = "Hm. És azt hiszem, hogy ez a megfelelô ház...";
			link.l1.go = "Portugal_guard_1";
		break;
		
		case "Portugal_guard_1":
			dialog.text = "Nos, figyelmeztettelek...";
			link.l1 = "...";
			link.l1.go = "Portugal_guard_2";
		break;
		
		case "Portugal_guard_2":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			for (i=1; i<=3; i++)
			{
			sld = characterFromId("PortugalGuard_"+i);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.quest.Portugal_Doctor.win_condition.l1 = "location";
			pchar.quest.Portugal_Doctor.win_condition.l1.location = "Marigo_RoomHouseF1";
			pchar.quest.Portugal_Doctor.function = "CreatePortugalDoctor";
		break;
		
		case "Bart_lay":
			dialog.text = "Telt házzal, magasan szállva, fiaim... ágyúkat elôkészíteni!... ah-ha-ha... ó, szépségem...";
			link.l1 = "Hmm, szerencsés, hogy életben van...";
			link.l1.go = "exit";
			Nextdiag.TempNode = "Bart_lay";
		break;
		
		case "Portugal_doctor":
			pchar.quest.Portugal_DoctorOver.over = "yes";
			dialog.text = "Ó, Istenem, ki vagy te? Kérlek, tedd le a fegyvert! Itt egy beteg ember van!";
			link.l1 = "Ez a 'ill embere' több embert ölt meg, mint amennyit életében látott, doktor úr. Tûnjön innen!";
			link.l1.go = "Portugal_doctor_1";
		break;
		
		case "Portugal_doctor_1":
			dialog.text = "Ô a betegem, és még állni sem tud! Hát nem látja? Kérem, tegye le a pengét! Könyörgöm!";
			link.l1 = "És mi a baja, a fenébe is!?";
			link.l1.go = "Portugal_doctor_2";
		break;
		
		case "Portugal_doctor_2":
			dialog.text = "Gondolom, az egész a sebe miatt van, egy mérgezett karib fegyvertôl kapott ütés miatt... és az emberek, akik idehozták, azt mondták, hogy ha meghal, én is meghalok! De én mindent megteszek, amit tudok, mondd meg nekik!";
			link.l1 = "Ne aggódjon azok miatt az emberek miatt, doktor. Az embereim majd szemmel tartják a házát, nekem pedig el kell mennem a kormányzóhoz. Gondolom, be fog pisilni az örömtôl. Ne hagyja el ezt a helyet, amíg vissza nem térek, doki.";
			link.l1.go = "Portugal_doctor_3";
		break;
		
		case "Portugal_doctor_3":
			chrDisableReloadToLocation = false;
			DialogExit();
			LAi_SetStayType(npchar);
			Nextdiag.Currentnode = "Doctor_repeat";
			pchar.quest.Avendel_House.win_condition.l1 = "location";
			pchar.quest.Avendel_House.win_condition.l1.location = "Marigo_houseF1";
			pchar.quest.Avendel_House.function = "AvendelInHouse";
		break;
		
		case "Doctor_repeat":
			dialog.text = "Nem megyek el, ne aggódjon emiatt. Adjuk már át a hatóságoknak, és vessünk véget ennek a rémálomnak.";
			link.l1 = "Természetesen, már úton vagyok.";
			link.l1.go = "exit";
			Nextdiag.TempNode = "Doctor_repeat";
		break;
		
		case "Avendel_house":
			dialog.text = "Megcsináltuk, kapitány! Megtaláltuk, és hamarosan gazdagok leszünk, ahogy mondtam! Mi a tervünk?";
			link.l1 = "Remélem, Hugo. Mindenesetre, még nincs vége. Gondolom, el kell mennem a kormányzóhoz, hogy megbeszéljük a jutalmunkat.";
			link.l1.go = "Avendel_house_1";
		break;
		
		case "Avendel_house_1":
			dialog.text = "Nem, nem, nem, kapitány! Ne menjen el ehhez az átkozott Thomashoz! Bízz bennem, ez a gazember elviszi a foglyunkat, és ha szerencsénk van, meghív minket egy csésze kávéra! Ôexcellenciája egy halas típus, úgyhogy ha teljes jutalmat akarsz kapni, akkor Curacaóba kell hajózni! Különben a portugálok elvisznek tôlünk az erôdbe, és elkergetnek minket, mint a koldusokat!";
			link.l1 = "Hát, ha tényleg biztos vagy benne...";
			link.l1.go = "Avendel_house_2";
		break;
		
		case "Avendel_house_2":
			dialog.text = "Igen, kapitány úr, átkozottul biztos vagyok benne! De ne feledd, hogy Bartolomeo emberei valahol a városban lehetnek, és mi sem akarjuk felhívni a helyôrség figyelmét, az rohadtul biztos! El kell döntenünk, hogyan juttatjuk el a portugálokat a hajódhoz, és hogyan tegyük ezt észrevétlenül.";
			link.l1 = "Rendben... Nem akarok harcolni a fregattjával Willemstad felé menet. Van valami ötleted?";
			link.l1.go = "Avendel_house_3";
		break;
		
		case "Avendel_house_3":
			dialog.text = "Igen, van egy. Elôbb találnunk kell neki egy nemesebb öltönyt, aztán berángatjuk a hátsó bejáraton keresztül, mint egy részeg tisztet! Senki sem fogja gyanítani, hogy egy átkozott kalóz, higgyétek el!";
			link.l1 = "Hmm, ebben nem vagyok biztos, de jobb tervünk amúgy sincs még. Megpróbálok szerezni valami szép ruhát az utasunknak. Te maradj itt, és vigyázz Bartra és a dokira.";
			link.l1.go = "Avendel_house_4";
		break;
		
		case "Avendel_house_4":
			DialogExit();
			AddQuestRecord("Portugal", "3");
			LAi_ActorRunToLocation(npchar, "reload", "houseF1", "Marigo_houseF1", "goto", "goto2", "", -1);
			pchar.quest.Portugal_Cloves.win_condition.l1 = "Timer";
			pchar.quest.Portugal_Cloves.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.Portugal_Cloves.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Portugal_Cloves.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Portugal_Cloves.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Portugal_Cloves.function = "PortugalClovesOver";//1 сутки
			pchar.questTemp.Portugal = "Findcloves";
			LAi_SetStayType(npchar);
			npchar.dialog.currentnode = "Avendel_house_guard";
			AddLandQuestMark(characterFromId("Marigo_trader"), "questmarkmain");
			QuestPointerToLoc("marigo_town", "reload", "reload6_back");
		break;
		
		case "Avendel_house_guard":
			dialog.text = "Ne aggódjon, kapitány. A portugál az én megbízható ôrségem alatt áll, he-he-he...";
			link.l1 = "Szeretném hinni, hogy...";
			link.l1.go = "exit";
			Nextdiag.TempNode = "Avendel_house_guard";
		break;
		
		case "Portugal_doctor_4":
			dialog.text = "Nem látom a katonákat, "+GetAddress_Form(NPChar)+". Hol vannak? Azt mondta, hogy letartóztatják, amint elmondja nekik a helyzetet. Akkor miért nincsenek itt a katonák?";
			link.l1 = "Nem lesznek katonák, mynheer Van Stal. Én magam fogom elvégezni a munkát, és a betegét minél hamarabb Curacaóba kell vinnem.";
			link.l1.go = "Portugal_doctor_5";
			DelLandQuestMark(npchar);
		break;
		
		case "Portugal_doctor_5":
			dialog.text = "Kapitány, figyeljen, nem tudom kezelni a sebét, csak a lázát tudom egy kicsit csökkenteni. Többnyire eszméletlen és delíriumban van, nem kétséges, hogy minden beavatkozás nélkül is meg fog halni, és a tengeri hullámzás néhány napon belül végez vele. Adok neked néhány keveréket, ami segíthet...";
			link.l1 = "Nem, doki, maga velünk hajózik. Elôször is, béna vagyok az orvoslásban, másodszor pedig kétlem, hogy itt akarsz maradni, és elmagyarázni a portugál embereinek, hová tûnt a kapitányuk?";
			link.l1.go = "Portugal_doctor_6";
		break;
		
		case "Portugal_doctor_6":
			dialog.text = "...Igen, azt hiszem, igazad van. De tudd, hogy ez a kalóz nagyon ellenálló, láttam már olyan embert, akin csak apró karcolásokat ejtettek az indiai fegyverek, és mindannyian kevesebb, mint három nap alatt meghaltak. És a 'barátai', szerint már egy hete ebben az állapotban van! Mindazonáltal megerôsítem, hogy rövid ideig túl fogja élni egy hajón a nyílt tengeren. Három nap, nem több!\nEnnyi idônk van.";
			link.l1 = "Még a madár sem ér Curacaóba három nap alatt. De azt hiszem, tudom, mit tehetek! Van ez a... barátom, aki Antiguán, St. John's-ban él. Tudja, hogyan kell meggyógyítani az embereket a halálos sebekbôl. Ô az egyetlen ember, aki segíthet nekünk. A célunk egyszerû - oda kell érnünk, mielôtt a portugál meghal. Pakolja össze a holmiját, doki, azonnal kihajózunk, és a betege lesz a következô!";
			link.l1.go = "Portugal_doctor_7";
		break;
		
		case "Portugal_doctor_7":
			DialogExit();
			AddQuestRecord("Portugal", "5");
			pchar.quest.Portugal_Cloves.over = "yes";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			sld = characterFromId("Avendel");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "", -1);
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, false);
			RemoveItems(PChar, "suit_1", 1);
			sld = characterFromId("Portugal");
			sld.model = "Port_B"; //меняем модель
			ChangeCharacterAddressGroup(sld, "My_Deck", "goto", "goto6");
			SetFunctionTimerCondition("Portugal_ToAntiguaOver", 0, 0, 4, false);
			pchar.questTemp.Portugal = "ToAntigua";
			QuestPointerDelLoc("marigo_town", "reload", "houseF1");
			//временно для тестов откроем комнату Джино, потом убрать
			LocatorReloadEnterDisable("SentJons_HouseF3", "reload4", false);
		break;
		
		case "Avendel_goodbye":
			dialog.text = "Milyen kár, kapitány. Vesztettünk, és nem fogjuk látni azt az átkozott aranyat. Viszontlátásra.";
			link.l1 = "Viszlát, Hugo.";
			link.l1.go = "Avendel_goodbye_1";
		break;
		
		case "Avendel_goodbye_1":
			DialogExit();
			chrDisableReloadToLocation = false;//открыть локацию
			npchar.lifeday = 0;
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
		break;
		
		case "Portugal_doctor_9":
			dialog.text = "...";
			link.l1 = "Doki, készítse elô a betegét a leszállásra. A csónak készen áll. Siessetek!";
			link.l1.go = "Portugal_doctor_10";
			DelLandQuestMark(npchar);
		break;
		
		case "Portugal_doctor_10":
			dialog.text = "Úton vagyok, "+GetAddress_Form(NPChar)+".";
			link.l1 = "...";
			link.l1.go = "Portugal_doctor_11";
		break;
		
		case "Portugal_doctor_11":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Portugal_PerenesliVDom1", -1);
			sld = characterFromId("Portugal");
			ChangeCharacterAddressGroup(sld, "SentJons_HouseF3_Room2", "quest", "quest1");
			sld = characterFromId("Jino");
			ChangeCharacterAddressGroup(sld, "SentJons_HouseF3_Room2", "goto", "goto3");
			pchar.quest.Portugal_ToAntiguaOver.over = "yes";//снять таймер
			pchar.questTemp.Portugal = "TreatmentStart";
			pchar.quest.Portugal_Ill.win_condition.l1 = "Timer";
			pchar.quest.Portugal_Ill.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.Portugal_Ill.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 7);
			pchar.quest.Portugal_Ill.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 7);
			pchar.quest.Portugal_Ill.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 7);
			pchar.quest.Portugal_Ill.function = "Portugal_ToAntiguaOver";//не придёт через 7 дня - Португальцу капут
		break;
		
		case "Avendel_Room":
			dialog.text = "Ez a ház bûzlik a kibaszott keverékektôl! Nagy meglepetés lenne, ha a portugálok itt halnának meg, még ennek a szagnak a belélegzése is gyógyít minden betegséget!\nAz ember legénysége pedig a bûznek köszönhetôen könnyen ránk találhat!";
			link.l1 = "Hugo, kímélj meg a vicceidtôl. Kevés embert hagytam az utcán, hogy vigyázzanak a házra, de még egy ôr nem lesz felesleges a vendégünknek. Tartsd rajta a szemed, és próbáld meg abbahagyni a káromkodást, különben Gino megitatja veled valami keverékét, biztos vagyok benne, hogy ezt meg tudja gyógyítani.";
			link.l1.go = "Avendel_Room_1";
		break;
		
		case "Avendel_Room_1":
			dialog.text = "Ne aggódjon, kapitány úr! A legéberebben fogok vigyázni a pénzünkre, akkor sem fog elszökni, ha egészséges lenne! És könyörgöm, kérem, ne keverjen több keveréket!";
			link.l1 = "Látod, lehetsz kedves, ha akarsz. Legyetek résen, nekem mennem kell.";
			link.l1.go = "exit";
			chrDisableReloadToLocation = false;
		break;
		
		case "Avendel_Room_2":
			dialog.text = "Máris indul, kapitány úr? Szép volt! Itt az idô! Láttam néhány gyanús fickót az utcán. Nem úgy néznek ki, mint a portugálok, de valamit keresnek, óvatosnak kell lennünk, kapitány!";
			link.l1 = "Rendben, köszönöm a figyelmeztetést, Hugo. Menjünk a hajóra.";
			link.l1.go = "Avendel_Room_3";
		break;
		
		case "Avendel_Room_3":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			//ставим Португальца
			sld = characterFromId("Portugal");
			ChangeCharacterAddressGroup(sld, "SentJons_HouseF3", "goto", "goto1");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
		break;
		
		case "Portugal_hunter":
			dialog.text = "Kapitány, már túl régóta várunk erre a találkozóra! És ki az ott veled? Maga Bartolomeo, a portugál, úgy tûnik, a Boldog Pierre-nek igaza volt - ô az! Maradjon távol, kapitány, magunkkal visszük, és senkinek sem esik bántódása.";
			link.l1 = "Elnézést uram, de ki a fene maga? El az utamból, vagy egyikôtök sem látja meg a holnapot!";
			link.l1.go = "Portugal_hunter_1";
		break;
		
		case "Portugal_hunter_1":
			dialog.text = "Ó, micsoda fenyegetô fickó, nézzétek csak meg, fiúk! Ha-ha-ha-ha! Figyelj ide, kölyök, ne állj Leo Cord és a pénze közé! Már majdnem fél éve nyomozunk a portugál után, és most végre elkaptuk. Úgyhogy tedd le azt a fogpiszkálót, és tûnj el, amíg még lélegzel! Nem vagyunk mi olyan kapzsiak, a halott ember is megteszi, ha-ha!";
			link.l1 = "Elég volt. Táncoljunk, uraim!";
			link.l1.go = "Portugal_hunter_2";
		break;
		
		case "Portugal_hunter_2":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешим драться
		DialogExit();
		sld = characterFromId("Portugal");
		LAi_group_Register("Bart_Portugal");
		LAi_group_SetRelation("Bart_Portugal", LAI_GROUP_PLAYER, LAI_GROUP_FRIEND);
		LAi_group_MoveCharacter(sld, "Bart_Portugal");
		for (i=1; i<=5; i++)
		{
		sld = characterFromId("PortugalHunter_"+i);
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
		}
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		LAi_group_SetCheck("EnemyFight", "PortugalHunterDied");
		AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Avendel_street":
			sld = characterFromId("Portugal");
			if (LAi_GetCharacterHP(sld) > 0)
			{
				dialog.text = "Tudtam, hogy itt valami nem stimmel! Szép munka, kapitány! De ideje indulni, annak az átkozott Leo Cordnak van itt egy csomó banditája és egy szép hajója! El kell tûnnünk errôl a szigetrôl!";
				link.l1 = "Jó érv, Hugo, és nagyon örülök, hogy nem lôttek golyót a lyukba, ahol elbújtál.";
				link.l1.go = "Avendel_street_1";
			}
			else
			{
				dialog.text = "Milyen kár, kapitány. Vesztettünk, és nem fogjuk látni azt az átkozott aranyat. Viszontlátásra.";
				link.l1 = "Viszlát, Hugo.";
				link.l1.go = "Avendel_goodbye_1";
				sld = characterFromId("PortugalDoctor");
				RemovePassenger(Pchar, sld);
				sld.lifeday = 0;
				RemovePassenger(Pchar, npchar);
				AddQuestRecord("Portugal", "35");
				CloseQuestHeader("Portugal");
				pchar.questTemp.Portugal = "end";
			}
		break;
		
		case "Avendel_street_1":
			dialog.text = "I... Én a hátunkat biztosítottam, kapitány! Jól megvoltatok nélkülem is, de mi lett volna, ha valaki megtámad minket az utca másik oldaláról? Nem lett volna ideje a hajóhoz rohanni.";
			link.l1 = "Talán ezért nem volt sikeres a munkája? Mindegy, elég a dumából, el kell jutnunk a hajóra! Kifutunk az idôbôl!";
			link.l1.go = "Avendel_street_2";
		break;
		
		case "Avendel_street_2":
			DialogExit();
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 10);
			AddQuestRecord("Portugal", "8");
			pchar.quest.Portugal_seahunter.win_condition.l1 = "location";
			pchar.quest.Portugal_seahunter.win_condition.l1.location = "Antigua";
			pchar.quest.Portugal_seahunter.function = "PortugalSeaHunter";
			pchar.quest.Portugal_martinique.win_condition.l1 = "location";
			pchar.quest.Portugal_martinique.win_condition.l1.location = "FortFrance_town";
			pchar.quest.Portugal_martinique.function = "PortugalOnMartinique";
		break;
		
		case "Portugal_doctor_12":
			dialog.text = "Kapitány, a portugál nagyon rosszul érzi magát, meg kell állnunk!";
			link.l1 = "Ezért vagyunk itt, mynheer van Stal, az utunknak már majdnem vége. Ki fogok bérelni egy szobát a kocsmában, és a foglyunk ott marad néhány napig.";
			link.l1.go = "Portugal_doctor_13";
		break;
		
		case "Portugal_doctor_13":
			DialogExit();
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 5);
		break;
		
		case "Portugal_doctor_14":
			dialog.text = "Mynheer kapitány, én fogok vigyázni a portugálra, szüksége van a teljes pihenésre.";
			link.l1 = "Értettem, doki, minden rendben. A fenébe is, meddig vigyázzak erre a kalózra? Ez nem tesz jót neki, nem erre van szüksége! Úgy tûnik, hogy bébiszitternek vettek fel, és... áh, bocsásson meg, doktor úr, ez már túl sok... Késôbb találkozunk.";
			link.l1.go = "Portugal_doctor_15";
		break;
		
		case "Portugal_doctor_15":
			DialogExit();
			AddQuestRecord("Portugal", "15");
			pchar.quest.Portugal_patrol.win_condition.l1 = "location";
			pchar.quest.Portugal_patrol.win_condition.l1.location = "FortFrance_town";
			pchar.quest.Portugal_patrol.function = "CreateFrancePatrol";
		break;
		
		case "Portugal_patrol":
			dialog.text = "Monsieur, ön a "+GetFullName(pchar)+"kapitány, akinek a hajója éppen ma érkezett a kikötônkbe?";
			link.l1 = "Igaza van, miben segíthetek?";
			link.l1.go = "Portugal_patrol_1";
		break;
		
		case "Portugal_patrol_1":
			dialog.text = "Ôexcellenciája Jacques Dille du Parquet, a gyarmatunk kormányzója várja önt. Az ügy sürgôs!";
			link.l1 = "Rendben, monsieur, még ma meglátogatom Ôexcellenciáját.";
			link.l1.go = "Portugal_patrol_2";
		break;
		
		case "Portugal_patrol_2":
			DialogExit();
			chrDisableReloadToLocation = false;//открыть локацию
			pchar.questTemp.Portugal = "MartiniqueGovernor";
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", -1);
			AddQuestRecord("Portugal", "9");
		break;
		
		case "Avendel_seapatrol":
			dialog.text = "Elértük Martinique-ot, kapitány! A pénzünk már nincs olyan messze...";
			link.l1 = "Csak ha a portugálok életben maradnak, amíg Willemstadba érünk. Hugo, nekem a hajóra kell mennem, úgyhogy neked kell vigyáznod a dokira és a betegére.";
			link.l1.go = "Avendel_seapatrol_1";
		break;
		
		case "Avendel_seapatrol_1":
			dialog.text = "A hajóra mész? A hajóra? Miért? Kölcsönadsz néhány embert, hogy segítsenek nekem? Mi van, ha valami történik, amíg távol vagy?";
			link.l1 = "Sajnálom, de nem. Kétlem, hogy itt bármi is fenyegethetné önt. A helyôrség riadóztatva van, és több katona van az utcákon, mint általában, úgyhogy ha valami baj történik, hívd ôket. Láttak egy nagy hajót nem messze ettôl a szigettôl, talán egy kalózhajót. És a kormányzó ôexcellenciája megkért, hogy a hajómmal járôrözve erôsítsem meg a szigetet.";
			link.l1.go = "Avendel_seapatrol_2";
		break;
		
		case "Avendel_seapatrol_2":
			dialog.text = "Egy hajó? Kalózhajó? Lehet, hogy az Albatrosz! Vagy régi barátunk, Leo Cord kollégája!";
			link.l1 = "Vagy talán csak egy közönséges kalózhajó. Mindazonáltal, Hugo, ha ez a hajó a fejünkért jött, akkor jobb, ha a helyi ôrjárattal az oldalamon és a kormányzó aranyáért szembe szállok vele. Sokkal jobb, mintha az út hátralévô részében a hátunk mögött ôrködnénk. Ha azonban ez a riasztás hamis, akkor egyszerûen megkímél attól, hogy néhány napig a kocsmában üljek a seggemen.";
			link.l1.go = "Avendel_seapatrol_3";
		break;
		
		case "Avendel_seapatrol_3":
			dialog.text = "Gondolja meg, kapitány, vajon bölcs dolog-e védtelenül hagyni a gátat... a portugálokat, miközben a fregattja körbecirkálhat? A jutalmunkat kockáztatod azzal, hogy elfogadod a kormányzó díját!";
			link.l1 = "Elég a beszédbôl, Hugo Avendell! Én vagyok itt a kapitány, és a végsô döntés az enyém! Úgyhogy tedd, amit parancsolok. Menj a kocsmába, és tartsd szemmel az orvost és a portugált, amíg vissza nem jövök.";
			link.l1.go = "Avendel_seapatrol_4";
		break;
		
		case "Avendel_seapatrol_4":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 10.0);
			chrDisableReloadToLocation = false;//открыть локацию
			LocatorReloadEnterDisable("Fortfrance_town", "reload4_back", true);//закрыть таверну
		break;
		
		case "Avendel_seapatrol_5":
			dialog.text = "Végre visszatért, kapitány! Attól tartok, rossz híreim vannak - a portugál eltûnt, és a doki is!";
			link.l1 = "Hogyhogy?! És mit csináltál akkor, tökfej?!";
			link.l1.go = "Avendel_seapatrol_6";
		break;
		
		case "Avendel_seapatrol_6":
			dialog.text = "Lefogadom, hogy az a hajó a 'Albatross'. volt, láttam a portugálokat, beléptek a kocsmába, és én... Elfutottam. Sajnálom, de a Félszemû kutyával való találkozás még ennyi pénzért is túl sok volt!";
			link.l1 = "Baszd meg! Legalább azt mondd el, mi történt a kocsmában?";
			link.l1.go = "Avendel_seapatrol_7";
		break;
		
		case "Avendel_seapatrol_7":
			dialog.text = "Mondtam, hogy nem láttam semmit. Elfutottam a konyhán keresztül, amint megláttam Franz Garckét és az embereit... Túl közel volt! Tegnap este történt, és nem tudtam, hogyan tudassam veled...";
			link.l1 = "Igen, maga nagyon bátor és leleményes ember... Rendben, adjunk még egy esélyt, meg fogjuk találni ôket. Túl sokáig mentettem ezt a gazembert, és most már a tulajdonomnak tekintem. Még van egy kis idônk, hogy elkapjuk ôket, úgyhogy induljunk el a kocsmából, talán valaki többet látott a futó sarkadnál. Menj, készülj fel!";
			link.l1.go = "Avendel_seapatrol_8";
		break;
		
		case "Avendel_seapatrol_8":
			DialogExit();
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			chrDisableReloadToLocation = false;
			LAi_ActorFollowEverywhere(npchar, "", -1);
			SetFunctionTimerCondition("MartiniquePortugalOver", 0, 0, 2, false); //таймер
			sld = characterFromId("PortugalDoctor");
			sld.lifeday = 0;//убираем доктора
			RemovePassenger(Pchar, sld);	
			sld = characterFromId("Portugal");
			ChangeCharacterAddressGroup(sld, "none", "", "");//Португальца спрячем
			LocatorReloadEnterDisable("Fortfrance_tavern", "reload2_back", true);//комнату закроем
			AddQuestRecord("Portugal", "12");
		break;
		
		case "Avendel_seapatrol_9":
			dialog.text = "Hallotta, kapitány úr, a Félszemû kutyáról beszélt, nemrég meséltem róla. És az a lisztizáló kasztíliai Hernando Vasquez, a véres Don - Vera Cruz mészárosa, nem is láttam!";
			link.l1 = "Nyugalom, Hugo. Biztos vagyok benne, hogy Bartholomeo még mindig a szigeten van, lehet, hogy jobban lett, de még mindig túl gyenge. És azt hiszem, tudom, hol találom! El fogjuk kapni ôket, nem fogok elállni a jutalmamtól. Ha nem vagy gyáva, akkor kövess engem, még nincs vége.";
			link.l1.go = "Avendel_seapatrol_10";
		break;
		
		case "Avendel_seapatrol_10":
			DialogExit();
			bDisableFastReload = false;//открыть быстрый переход
			pchar.questTemp.Portugal = "PortugalLeFransua";//в Ле Франсуа
			AddQuestRecord("Portugal", "13");
			LAi_LocationDisableOfficersGen("LeFransua_tavern", true);//офицеров не пускать
		break;
		
		case "LeFransua_pirate":
			dialog.text = "Túl sok kérdést teszel fel, kapitány... Várj, nem te vagy az a sunyi fickó Philipsburgból? Túl sokáig menekültél elôlünk, és most nézd - itt vagy...";
			link.l1 = "Kár érted, te szemétláda!";
			link.l1.go = "LeFransua_pirate_1";
		break;
		
		case "LeFransua_pirate_1":
			DialogExit();
			pchar.quest.MartiniquePortugalOver.over = "yes"; //снять таймер
			chrDisableReloadToLocation = true;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			for (i=1; i<=3; i++)
			{
			sld = characterFromId("LeFransuaPirate_"+i);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "LeFransuaAfterFight");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "FranzGarke":
			dialog.text = "... te, nyomorult rákszar, mindent el fogsz mondani nekünk, ebben megbízhatsz bennem, te kibaszott patkány! Akkor majd felakasztunk egy árbocra, ahelyett, hogy a vitorla tetején lennél... És te ki a fene vagy? A fenébe is, ezekben a majmokban nem lehet megbízni! Mindig mindent nekem kell csinálnom...";
			link.l1 = "Zavarom önöket, uraim?";
			link.l1.go = "FranzGarke_1";
		break;
		
		case "FranzGarke_1":
			DialogExit();
			chrDisableReloadToLocation = true;
			sld = characterFromId("FranzGarke");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "LeFransua_PortugalTalk");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Portugal_LFTalk":
			dialog.text = "Tetszik az idôzítésed... Gondolom, meg kell köszönnöm, hogy máig életben tartottak.";
			link.l1 = "Igazad van. A nevem " + GetFullName(pchar) + " és te, portugál, még mindig a foglyom vagy. Úgyhogy ne kérdezzen, mennünk kell.";
			link.l1.go = "Portugal_LFTalk_1";
		break;
		
		case "Portugal_LFTalk_1":
			dialog.text = "Várjon, kapitány... Vasquez sok embere van a városban, nem fognak csak úgy elengedni minket. Adj egy kardot, és sokkal jobb esélyeink lesznek.";
			link.l1 = "Nem vagy jóban a társaiddal, mi? Rendben, egy plusz penge mindig jól jön, fogd a hulla fegyverét, és maradj a közelemben!";
			link.l1.go = "Portugal_LFTalk_2";
			link.l2 = "Ne is gondolj arra, hogy azért adok neked fegyvert, hogy megüthess, ha egyszer hátat fordítok neked! Csak maradj a közelemben.";
			link.l2.go = "Portugal_LFTalk_4";
			pchar.quest.Portugal_LeFransua.win_condition.l1 = "location";
			pchar.quest.Portugal_LeFransua.win_condition.l1.location = "LeFransua_town";
			pchar.quest.Portugal_LeFransua.function = "CreateVaskezsPirates";
			bDisableFastReload = true;//закрыть переход
		break;
		
		case "Portugal_LFTalk_2":
			dialog.text = "Ne aggódjon, kapitány, inkább meghalok, minthogy újra Vasquez kezébe kerüljek.";
			link.l1 = "Nos, a helyzet az, hogy nem akarom, hogy meghalj, még nem. Gyerünk, kifutunk az idôbôl!";
			link.l1.go = "Portugal_LFTalk_3";
		break;
		
		case "Portugal_LFTalk_3":
			DialogExit();
			GiveItem2Character(npchar, "blade_17");
			EquipCharacterbyItem(npchar, "blade_17");
			GiveItem2Character(npchar, "pistol6");
			EquipCharacterbyItem(npchar, "pistol6");
			TakeNItems(npchar, "bullet", 50);
			AddItems(npchar, "gunpowder", 50);
			TakeNItems(npchar, "potion2", 3);
			LAi_SetCharacterUseBullet(npchar, GUN_ITEM_TYPE, "bullet");
			pchar.questTemp.Portugal.Condition1 = "true";
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
		break;
		
		case "Portugal_LFTalk_4":
			dialog.text = "Kár, hogy segítettem volna a Félszemûnek, ha holtan akarnám látni...";
			link.l1 = "De te sem segítettél nekem, úgyhogy fogd be és menj!";
			link.l1.go = "Portugal_LFTalk_5";
		break;
		
		case "Portugal_LFTalk_5":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
		break;
		
		case "Vaskezs_pirate":
			PlaySound("Voice\English\EvilPirates01.wav");
			dialog.text = "A francba! Ôk azok! Öljétek meg mindet!";
			link.l1 = "Már megint itt tartunk... Gyertek, korcsok!";
			link.l1.go = "Vaskezs_pirate_1";
		break;
		
		case "Vaskezs_pirate_1":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешим драться
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.Portugal.Condition1"))
			{
				sld = characterFromId("Portugal");
				LAi_SetImmortal(sld, false);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			for (i=1; i<=9; i++)
			{
				sld = characterFromId("VaskezsPirate_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "VaskezsPiratesDied");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Avendel_LeFransua":
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;//открыть переход
			sld = characterFromId("Portugal");
			if (LAi_GetCharacterHP(sld) > 0)
			{
				dialog.text = "Pompás! Megöltétek a Félszemû kutyát, ezt nevezem én mestermûnek! Hány emberét küldted a pokolba?";
				link.l1 = "Én harcoltam, nem számoltam. És te hol voltál, Hugo?";
				link.l1.go = "Avendel_LeFransua_1";
			}
			else
			{
				dialog.text = "Milyen kár, kapitány. Vesztettünk, és nem fogjuk látni azt az átkozott aranyat. Viszontlátásra.";
				link.l1 = "Viszlát, Hugo.";
				link.l1.go = "Avendel_goodbye_1";
				RemovePassenger(Pchar, npchar);
				CloseQuestHeader("Portugal");
				pchar.questTemp.Portugal = "end";
			}
		break;
		
		case "Avendel_LeFransua_1":
			dialog.text = "Én... biztosítottam a biztonságos visszavonulást... úgymond védtem a hátországunkat.";
			link.l1 = "Hát ennyi volt Hugo Avendell, a gyávaságod minden várakozásomat felülmúlta, van fogalmad róla, milyen kemény volt számunkra ez a harc? Alig bírtuk ki!";
			link.l1.go = "Avendel_LeFransua_2";
		break;
		
		case "Avendel_LeFransua_2":
			dialog.text = "Nyugodjon meg, kapitány... Elismerem, hogy bujkáltam. De ezt a lehetôséget megtaláltam neked! Ne feledjétek, én voltam az, aki elvezetett titeket a portugálokhoz! Nos... tekintettel a méltányos felháborodásodra, csak a jutalom egyharmadába egyezem bele.";
			link.l1 = "Ez egyszerûen dicsôséges! Most alkudozol? Nem, barátom, a te szerepednek ebben az üzletben vége! Elvesztette a pénzét a Saint-Pierre kocsmában. Ott hagytad és elszaladtál, úgyhogy neked most már vége.";
			link.l1.go = "Avendel_LeFransua_3";
		break;
		
		case "Avendel_LeFransua_3":
			dialog.text = "Kapitány, maga nyilvánvalóan túlzásokba esik... Rendben, egy negyedért... egy ötödért! Tíz százalék!";
			link.l1 = "Ne tegye próbára a türelmemet! Tûnjetek el! Nincs szükségem gyávákra a legénységemben, különösen most, amikor az óra ketyeg!";
			link.l1.go = "Avendel_LeFransua_4";
		break;
		
		case "Avendel_LeFransua_4":
			dialog.text = ""+pchar.name+", Nem gondolod, hogy ez egy kicsit igazságtalan?";
			link.l1 = "Ok és okozat, Hugo... Meghoztad a döntésed, úgyhogy viszlát. Vonja le a következtetést, és ne vesse bele magát ilyen kalandokba, ez nyilvánvalóan nem magának való.";
			link.l1.go = "Avendel_LeFransua_5";
		break;
		
		case "Avendel_LeFransua_5":
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", -1);
			sld = characterFromId("Portugal");
			sld.dialog.currentnode = "Portugal_LeFransua";
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			pchar.questTemp.Portugal.GG2 = "true"; // Jason Дороже золота
		break;
		
		case "Portugal_LeFransua":
			dialog.text = "A ballasztot ledobni, kapitány? Ez igaz, ha... Vasquez még mindig szabad, és az Albatroszon rengeteg ember és fegyver van, a finom gatyámat egy régi kendôre teszem fel, hogy Hernando nem hagy minket megszökni.";
			link.l1 = "Nos, úgy tûnik, hogy nekünk kell elmennünk, és magunknak kell üdvözölnünk ôt. Menjen, monsieur portugál, és próbálja meg befogni a száját. A lehetô leghamarabb horgonyt vetünk.";
			link.l1.go = "Portugal_LeFransua_1";
		break;
		
		case "Portugal_LeFransua_1":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_ActorFollowEverywhere(npchar, "", -1);
			pchar.quest.Portugal_LeFransua1.win_condition.l1 = "location";
			pchar.quest.Portugal_LeFransua1.win_condition.l1.location = "Martinique";
			pchar.quest.Portugal_LeFransua1.function = "CreateVaskezsFrigate";
		break;
		
		case "VaskezsHelper_abordage":
			dialog.text = "Mire vársz még, a fenébe is?!";
			link.l1 = "Hol van Hernando Vasquez? Beszélj, és megkímélem az életed.";
			link.l1.go = "VaskezsHelper_abordage_1";
		break;
		
		case "VaskezsHelper_abordage_1":
			dialog.text = "Menj a pokolba a kibaszott kérdéseiddel!";
			link.l1 = "Csak utánad...";
			link.l1.go = "VaskezsHelper_abordage_2";
		break;
		
		case "VaskezsHelper_abordage_2":
			DialogExit();
			QuestAboardCabinDialogExitWithBattle(""); 	
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Portugal_treasure":
			bQuestDisableMapEnter = false;
			if (CheckAttribute(pchar, "questTemp.Portugal.Condition1") && CheckAttribute(pchar, "questTemp.Portugal.Condition2"))
			{
				dialog.text = "És tessék, bátor barátom, végre tisztességesen elbeszélgethetünk! Gratulálok, kapitány - a Félszemû Kutya megölése és a 'Albatrosz' elpusztítása nem volt könnyû feladat! Igazából nagyon sokat tettél azért, hogy megmentetted az életemet... Talán még meg is kellene köszönnöm?";
				link.l1 = "Majd megköszöni nekem, ha majd az akasztófán táncol, vagy bármi mást is készítenek magának Willemstadban.";
				link.l1.go = "Portugal_treasure_6";
			}
			else
			{
				dialog.text = "És itt vagy, bátor barátom, végre beszélgethetünk! Gratulálok, kapitány - a Félszemû Kutya megölése megér egy dicsôséges dalt! Valójában nagyon sokat tettél azért, hogy megmentetted az életemet... Talán még meg is kellene köszönnöm?";
				link.l1 = "Majd megköszöni nekem, ha majd az akasztófán táncol, vagy bármi mást is készítenek magának Willemstadban.";
				link.l1.go = "Portugal_treasure_1";
			}
		break;
		
		case "Portugal_treasure_1":
			dialog.text = "Hihetetlen! Az elmúlt két hétben megmentetted az életemet, hazahoztál, megvédtél a harcokban... és most a halálba akarsz küldeni? Ezt alig tudom elhinni... Igazából már majdnem a barátomnak tekintelek, ha-ha.";
			link.l1 = "Egy kalóz, aki a becsületéért könyörög? Portugál, viccelsz velem? Én csak egy céllal mentettem meg magát - hogy a gyilkos és gazember az igazságszolgáltatás elé álljon!";
			link.l1.go = "Portugal_treasure_2_1";
			link.l2 = "Barátom... ez úgy hangzik, mintha gúnyolódna. De ettôl függetlenül igaza van. Furcsa lenne tôlem, ha ezt tenném, portugál...";
			link.l2.go = "Portugal_treasure_2_2";
		break;
		
		case "Portugal_treasure_2_1":
			dialog.text = "Ó, elég, kapitány. Lefogadom, hogy mindezt csak azért tette, hogy pénzt kapjon, amit a Társaság ígért azért az örömért, hogy élve láthat engem! Ne próbáljon ôszintébb lenni, mint amilyen valójában, uram, nem illik magához.";
			link.l1 = "Csak én magam tudom megítélni. Úgyhogy fejezzük be ezt a beszélgetést. Itt az ideje, hogy elhajózzunk Willemstadba.";
			link.l1.go = "Portugal_treasure_3";
		break;
		
		case "Portugal_treasure_2_2":
			dialog.text = "Úgy tûnik, hogy manapság még mindig találni némi ôszinteséget az emberekben... Kár, hogy a pénz mindig közbeszól, nem igaz, kapitány?";
			link.l1 = "Furcsa ezt hallani a portugál kalózoktól, a bitófára vetett madaraktól. Elengedlek... ne kérdezd, miért, csak tûnj el a fenébe a legelsô kikötôben. És ne feledd, hogy nem leszek ilyen kedves, ha még egyszer találkozunk.";
			link.l1.go = "Portugal_treasure_4";
		break;
		
		case "Portugal_treasure_3":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);//запрет диалога
			pchar.questTemp.Portugal.Villemstad = "true";//сдать губернатору
			AddQuestRecord("Portugal", "21");
		break;
		
		case "Portugal_treasure_4":
			dialog.text = "Tényleg? Szeretném, kapitány! Nem rendelné meg, hogy hozzanak ide egy kis rumot? Tudod, csak hogy megünnepeljük a lovagi tulajdonságaidat, a kapcsolatunkat és a büntetésem elhalasztását?";
			link.l1 = "Ne ûzz gonosz vicceket, az elsô partraszállásig még mindig a foglyom vagy. Viszontlátásra.";
			link.l1.go = "Portugal_treasure_5";
		break;
		
		case "Portugal_treasure_5":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);//запрет диалога
			pchar.quest.Remove_Portugal.win_condition.l1 = "Location_Type";
			pchar.quest.Remove_Portugal.win_condition.l1.location_type = "town";
			pchar.quest.Remove_Portugal.function = "RemovePortugal";
			AddQuestRecord("Portugal", "20");
		break;
		
		case "Portugal_treasure_6":
			dialog.text = "Értem... szóval akkor ez az akasztófa. Ez várható volt. Akkor hallgassa meg, amit mondani fogok, kapitány. Annyira igyekezett életben tartani, hogy késôbb rendesen kivégezhessen, és ezt nagyra értékelem. Gondolom, ostobaság lenne tôlem, ha arra kérném, hogy csak úgy meggondolja magát, igaz? És mit fogsz mondani, ha felajánlok valamit cserébe? Egy üzletet, hogy úgy mondjam, mi?";
			link.l1 = "Nem mondok semmit, portugál. Te egy kalóz és egy fattyú vagy. Felelni fogsz a bûneidért Willemstadban.";
			link.l1.go = "Portugal_treasure_2_1";
			link.l2 = "Alkut? Mit tud ajánlani?";
			link.l2.go = "Portugal_treasure_7";
			link.l3 = "Nincs szükségem az alkura, csak tûnj el a legelsô kikötôben. Ez a te szerencsenapod.";
			link.l3.go = "Portugal_treasure_4";
		break;
		
		case "Portugal_treasure_7":
			dialog.text = "Tudod, az életem ilyen kitartó megmentése a mögötte álló kellemetlen okok ellenére is megérdemel némi hálát. És Bartolomeo, a portugál tud valamit a háláról. Figyelj, egy hónappal azelôtt, hogy találkoztunk, elfoglaltuk a Társaság egyik hajóját. Úgy harcoltak, mint az ördögök az utolsó emberig. De a rakterükben csak ágyúgolyók és patkányok voltak\nA legénységemnek ez nem tetszett, mégis találtam egy nagyon érdekes ládát és papírokat a kapitány kabinjában. Futárhajó volt, mintákat szállított valahol Amazóniában lévô bányákból. Tiszta gyémántok és rubinok, egy igazi vagyon!";
			link.l1 = "Érdekes zsákmány... Most már értem, hogy a Társaság miért érdeklôdik annyira maga iránt, de mi a lényege a történetének?";
			link.l1.go = "Portugal_treasure_8";
		break;
		
		case "Portugal_treasure_8":
			dialog.text = "Elsô tisztjeim, Vazquez és Franz Garcke tartották rendben a legénységet, ezért úgy döntöttem, hogy megragadom a lehetôséget. Elrejtettem elôlük a köveket, és elégettem a papírokat. A hollandok a behajózás során súlyosan megrongálták a kötélzetünket, és a 'Albatros' egy kis sziget északi öblében kellett elfoglalnunk. Egyedül mentem mélyebbre a dzsungelben, míg az egész legénység a fregattot javította\nElástam a köveket, a fedélzeten tartani túl kockázatos volt a körülményekhez képest. A tervem az volt, hogy a legelsô kikötôben megszököm szeretett legénységemtôl, veszek vagy lopok egy kis hajót, és elhajózom a szigetre, felveszem a zsákmányomat, aztán... búcsút mondok a régi életemnek! Európa, egy tisztességes kastély, egy dögös feleség, a többit tudod...";
			link.l1 = "Hadd találjam ki, valami rosszul sült el.";
			link.l1.go = "Portugal_treasure_9";
		break;
		
		case "Portugal_treasure_9":
			dialog.text = "Minden rosszul ment! Az átkozott szigetrôl kiderült, hogy a helyi kannibálok hordájának hazája. Megtámadtak minket, amint visszatértem a partra. El kellett vitorláznunk, amilyen gyorsan csak lehetett, ekkor ért a találat. Azt hittem, hogy csak egy karcolás.\nPár nappal késôbb már félholtan feküdtem a lázban, és nyilván mondtam valamit a kövekrôl. Franz és Vazquez rájöttek, hogy valamit elrejtettem a szigeten, de a pontos helyét nem tudták. Nem tetszett nekik a gondolat, hogy ott bolyongok, és az indiánok állandóan lövöldöznek rájuk. Ezért a rohadékok elhurcoltak a legközelebbi kikötôbe, mivel az orvosunkat megölték a hollandokkal vívott harcunk során, szükségük volt egy új orvosra.\nÍgy kerültem ahhoz az orvoshoz, vissza akartak téríteni az eszméletemhez egy idôre, hogy megkínozhassanak, és megtudják, hol vannak a kövek. Azt hiszem, hogy késôbb felvágtak volna és rákokat etettek volna a szaftos húsommal.";
			link.l1 = "Nem mondhatom, hogy elítélem ôket - próbálták átverni az embereiket. Ezért újra megkérdezem, miért mesélsz nekem errôl?";
			link.l1.go = "Portugal_treasure_10";
		break;
		
		case "Portugal_treasure_10":
			dialog.text = "Ezek a kutyák nem emberek voltak, higgyétek el nekem, most mind a megérdemelt helyükön vannak - a pokolban, ha-ha! A szabadságomért és az életemért fizetségként meg tudom mondani a holland kincsek pontos helyét.";
			link.l1 = "Nem, Bart, az árulásod teljesen meggyôzött az aljasságodról. Willemstad és a törvényes megtorlás vár rád. Nincs alku.";
			link.l1.go = "Portugal_treasure_2_1";
			link.l2 = "És el kéne hinnem, hogy azok a drágakövek valóban léteznek? Mindegy, úgysem veszítek semmit... Az alku volt a történet kezdete, és az alku lesz a vége. Elfogadom a feltételeidet, portugál.";
			link.l2.go = "Portugal_treasure_11";
		break;
		
		case "Portugal_treasure_11":
			dialog.text = "Tekintse ezt szerény hálámnak. Eh, bárcsak tudnám, mennyibe kerül Bartolomeo, a portugál bôre fényes pezóban, ha! Megértem, hogy a céljaid szigorúan gyakorlatiasak voltak, de azért köszönök mindent, kapitány, ha-ha\nTörök, a dzsungel nem messze a partjaitól. Keress egy száraz, görbe fát, ott csak egy ilyen fa van. A ládát közel temettem el hozzá. Szóval ne felejtsetek el ásót vinni. Boldog vadászatot...";
			link.l1 = "Rendben, ezt megjegyzem, és most rögtön felszállhatsz egy hosszúhajóra, és eltûnhetsz a hajóm elôl. Viszontlátásra.";
			link.l1.go = "Portugal_treasure_12";
		break;
		
		case "Portugal_treasure_12":
			dialog.text = "Még egy utolsó dolog, kapitány. Feltételezem, hogy még mindig sok a vadember, de nem csak miattuk kell aggódnia. Vasquez nem volt a 'Albatross', fedélzetén, igaz? A Véres Don túl okos... vigyázz, amíg nem látod felakasztva vagy golyóval a fejében.";
			link.l1 = "Köszönöm a figyelmeztetést, portugál. Most pedig hagyja el a hajómat... ne tegye próbára a türelmemet.";
			link.l1.go = "Portugal_treasure_13";
		break;
		
		case "Portugal_treasure_13":
			DialogExit();
			LAi_SetImmortal(npchar, false);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 2.0);
			AddQuestRecord("Portugal", "23");
			pchar.quest.Portugal_Terks.win_condition.l1 = "location";
			pchar.quest.Portugal_Terks.win_condition.l1.location = "Terks_Jungle_01";
			pchar.quest.Portugal_Terks.function = "CreateHollIndBattle";
		break;
		
		case "Avendel_Marigo":
			pchar.quest.SetAvendelMarigoOver.over = "yes"; //снять таймер
			dialog.text = "Ó, és ki ez! Maga a "+pchar.name+" kapitány! Kérsz egy italt?";
			link.l1 = "Tudod, valójában örülök, hogy újra látlak. De talán túl durva voltam veled Martinique-on.";
			link.l1.go = "Avendel_Marigo_1";
		break;
		
		case "Avendel_Marigo_1":
			dialog.text = "Mindegy, kapitány! Ami történt, megtörtént... De az igazat megvallva, tényleg okot adtam arra, hogy elküldjön... De hé, nem fogja elhinni, ki vendégeskedik ma Phillipsburgben!";
			link.l1 = "Ne mondja, hogy...";
			link.l1.go = "Avendel_Marigo_2";
		break;
		
		case "Avendel_Marigo_2":
			dialog.text = "Nem, nem, kapitány, nem a portugálokról van szó. És nem is valami sebesült fattyú. Ez sokkal jobb! Ez Hernando Vasquez... Maga a véres Don! A helyi kormányzó vendége lesz az utolsó néhány napra.";
			link.l1 = "Vasquez? A kormányzó vendége? Most már értem. Hugo, mesélj még errôl, mi a fene folyik itt?";
			link.l1.go = "Avendel_Marigo_3";
		break;
		
		case "Avendel_Marigo_3":
			pchar.questTemp.Portugal.AvMoney = 10000;
			dialog.text = "Hát, sok mindent tudok... de az utazásunknak köszönhetôen újra csôdbe mentem. Talán ez az információ megér néhány pezót?";
			link.l1 = "Hugo, te még mindig egy zsaroló és gazember vagy! Beszélj, amid van, vegyél 5000 pezót, csak a régi barátságunkért.";
			link.l1.go = "Avendel_Marigo_4_1";
			if (sti(pchar.money) >= 10000)
			{
			link.l2 = "Valahogy nem vagyok meglepve. Tessék, vegyél 10000 pezót, és reméld, hogy az információd ennyibe kerül!";
			link.l2.go = "Avendel_Marigo_4_2";
			}
			link.l3 = "Van egy jobb ajánlatom számodra. Mi lenne, ha csatlakoznál a csapatomhoz? Gondolom, van tehetséged a jövedelmezô üzletek megkötéséhez és megtalálásához, úgyhogy ha eleged van abból, hogy bátor harcosnak tetteted magad - szívesen látlak az én pénzügyôrtisztem pozíciójában.";
			link.l3.go = "Avendel_Marigo_4_3";
		break;
		
		case "Avendel_Marigo_4_1":
			pchar.questTemp.Portugal.AvMoney = 15000;
			dialog.text = "Nem, kapitány, ez nem fog így mûködni! Biztos vagyok benne, hogy nagy összeget csent el azzal az átkozott portugállal. Szóval tekintse ezt a részemnek, ne legyen ilyen kapzsi! 15000 érme és egy pezóval sem kevesebb!";
			if (sti(pchar.money) >= 15000)
			{
			link.l1 = "A pokolba veled, vedd el ôket!";
			link.l1.go = "Avendel_Marigo_4_2";
			}
			link.l2 = "Nos, és még azt mondják, hogy a kapzsiság jó... Nem túl sok ez neked, mi?";
			link.l2.go = "Avendel_Marigo_wait";
		break;
		
		case "Avendel_Marigo_4_2":
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.Portugal.AvMoney));
			dialog.text = "Na, ez az én nyereményem! ... Figyelj, Vasquez velem egy hajón utazott, mégis, amíg én a fedélzeteket takarítottam az út fizetségeként, ô egy kabinban pihent, úgyhogy hála Istennek ritkán láttuk egymást, és nem ismert meg engem. De azonnal elkezdtem követni ezt az ördögöt... Érdekes történet történt vele.";
			link.l1 = "Folytasd csak! Mit keres a kormányzói palotában?";
			link.l1.go = "Avendel_Marigo_5";
		break;
		
		case "Avendel_Marigo_5":
			dialog.text = "Nem sokat tudok, de a helyôrséget már néhány nappal az érkezése után riadóztatták, és a hatalmas hadihajó hirtelen horgonyt vetett, és nagy sietséggel elment, azt hiszem, északnyugatra hajózott. Az egész város találgatásokba és pletykákba merült...";
			link.l1 = "Szóval ez volt az a hajó, amivel találkoztam! Érdekes... Ne térj el a témától, Hugó, folytasd a történeted, kérlek.";
			link.l1.go = "Avendel_Marigo_6";
		break;
		
		case "Avendel_Marigo_6":
			dialog.text = "Nos, mint mondtam, a hajó eltûnt, Vasquez pedig valamiféle vendég lett Martin Thomas kormányzó nálunk. Néha látom ôt a városban, mindig néhány katona társaságában. Nem tudom, hogy a kísérete vagy a konvoja, ha-ha. De csak a rezidensek tudnának többet mondani a Donról.";
			if (CheckAttribute(pchar, "questTemp.Portugal.AvOfficer"))
			{
				link.l1 = "Talán igaza van. De volt egy megállapodásunk, emlékszel? Ne játssza a hôst, menjen a hajómra és várjon a visszatérésemre. Megpróbálok beszélni a vendégszeretô kormányzóval.";
				link.l1.go = "Avendel_hire";
			}
			else
			{
				link.l1 = "Nos, ez érdekes volt. Nagyon sokat segítettél nekem, Hugo. Igya meg a rumot, a többi már nem tartozik magára.";
				link.l1.go = "Avendel_Marigo_del";
			}
			AddDialogExitQuestFunction("InMarigoResidence");
		break;
		
		case "Avendel_Marigo_4_3":
			dialog.text = "Komolyan mondja, kapitány? Mi bajod van? Elüldöztél azzal, hogy fegyvert fogtál az arcomba, és most ilyen javaslatokkal jössz?";
			if (sti(pchar.money) >= 10000)
			{
			link.l1 = "Felejtsd el, nem voltam önmagam, és sajnálom, a kapzsiság felemésztett, azt hiszem. Tessék, vegyél 10000 pezót, és mondd el, mit tudsz Vasquezrôl, sietek.";
			link.l1.go = "Avendel_Marigo_4_2";
			}
			link.l2 = "Talán bocsánatot kellene kérnem ezért a dologért. Te egy szánalmas harcos vagy, de jól bánsz a pénzzel. Megismétlem a javaslatomat, mit szólsz hozzá?";
			link.l2.go = "Avendel_Marigo_7";
		break;
		
		case "Avendel_Marigo_7":
			pchar.questTemp.Portugal.AvMoney = 20000;
			pchar.questTemp.Portugal.AvOfficer = "true";
			dialog.text = "Mit mondhatnék... Beleegyezem, de csak miután megkaptam a részem, kapitány. Tíz százalék, emlékszel? Kétezret kaptál azért a gazemberért, úgyhogy ha arra kérsz, hogy csatlakozzak a legénységedhez, akkor jobb, ha azzal kezded, hogy eltörlöd az adósságodat. Tíz százalék és nincs vita!";
			link.l1 = "Maga egy szélhámos, Hugo. Most nincs nálam ennyi, de hamarosan visszajövök. Maradj itt.";
			link.l1.go = "Avendel_Marigo_wait";
			if (sti(pchar.money) >= 20000)
			{
			link.l2 = "Remélem, hogy igazolni fogod az elvárásaimat azzal az üzleti fogásoddal, ha! Vedd el a részed!";
			link.l2.go = "Avendel_Marigo_4_2";
			}
		break;
		
		case "Avendel_Marigo_wait":
			dialog.text = "A te döntésed, kapitány. Itt maradok egy darabig. Jöjjön vissza, ha meggondolja magát.";
			link.l1 = "Rendben, Hugo.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Avendel_Marigo_repeat";
		break;
		
		case "Avendel_Marigo_repeat":
			dialog.text = "Meggondolta magát, kapitány? Akkor várok a pénzemre.";
			if (sti(pchar.money) >= sti(pchar.questTemp.Portugal.AvMoney))
			{
				link.l1 = "Vedd el az érméidet, te gazember, ha-ha!";
				link.l1.go = "Avendel_Marigo_4_2";
			}
			link.l2 = "Még nincs ennyi pénzem.";
			link.l2.go = "exit";
			NextDiag.TempNode = "Avendel_Marigo_repeat";
		break;
		
		case "Avendel_Marigo_del":
			DialogExit();
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "Avendel_hire":
			DialogExit();
			LAi_SetImmortal(npchar, false); // patch-8
			SetCharacterRemovable(npchar, true);
			npchar.quest.OfficerPrice = sti(pchar.rank)*1000;
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(npchar.id);
			npchar.loyality = 25;
			npchar.dialog.FileName = "Enc_Officer_dialog.c";
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		
		case "Servant":
			//pchar.quest.InMarigoResidenceOver.over = "yes"; //снять таймер
			dialog.text = "Jó napot, kapitány. Kérsz valamit?";
			link.l1 = "Nem, nem, csak arra várok, hogy mikor lesz szabad az én Thomasom? Várok egy közönségre... igen. Mondja, ôexcellenciája tényleg barátjának tekinti a híres kalózt, Hernando Vasquezt?";
			link.l1.go = "Servant_1";
		break;
		
		case "Servant_1":
			dialog.text = "Ne aggódjon, mynheer, bármelyik pillanatban szabad lehet, és persze, hogy nem, mynheer! Ez a bandita megadta magát a hatóságoknak, de valahogy mégsem akasztották fel. Talán azzal vásárolta meg az életét, hogy elárulta a régi bûntársait... Nem vagyok benne biztos. Már napok óta itt van bebörtönözve... Ez egy rémálom volt, mynheer! Az a szörnyeteg emberi alakban a mi kastélyunkban élt!";
			link.l1 = "Ez egy rémálom! Mit mondhatott az a szörnyeteg mynheer Thomasnak, hogy elkerülje az akasztófát? El sem tudom képzelni!";
			link.l1.go = "Servant_2";
		break;
		
		case "Servant_2":
			dialog.text = "Én sem tudom, de titokban elmondhatom, hogy minden szolga örült, amikor ôexcellenciája megszabadult egy ilyen vendégtôl...";
			link.l1 = "Megszabadult tôle? Végre megkapta, amit megérdemelt?";
			link.l1.go = "Servant_3";
		break;
		
		case "Servant_3":
			dialog.text = "Nem egészen. Még nem. Néhány nappal ezelôtt egy katonai briggre szállították, amely Willemstadba hajózott. Látod, mynheer Thomas elvesztette az érdeklôdését a gazember iránt, úgy tûnik, hogy megpróbálta átverni\nSzintén azt mondják, hogy elfogták a volt kapitányát - Bartolomeo a portugál! Gondolj csak bele! Úgy tûnik, a Társaság együtt akarja felakasztani ôket. A madarak azt mondják, hogy a tárgyalás egy hónap múlva lesz, de miért várnánk addig?";
			link.l1 = "A portugál?! Hm... köszönöm, hogy elkísértél, barátom... úgy tûnik, hogy Thomas mynheer most már szabad, búcsúzom.";
			link.l1.go = "Servant_4";
		break;
		
		case "Servant_4":
			DialogExit();
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
			AddQuestRecord("Portugal", "31");
			pchar.questTemp.Portugal = "SeekPortVillemstad";
			//SetFunctionTimerCondition("InMarigoResidenceOver", 0, 0, 30, false);
			colonies[FindColony("Villemstad")].jail = 0;
			sld = characterFromId("Portugal");
			sld.model = "Port_A"; //меняем модель
			sld.dialog.currentnode = "Portugal_free";
			LAi_SetStayType(sld);
			ChangeCharacterAddressGroup(sld, "Villemstad_prison", "goto", "goto9");
			sld = GetCharacter(NPC_GenerateCharacter("PortHolOfficer", "off_hol_4", "man", "man", 35, HOLLAND, 30, true, "soldier"));
			FantomMakeCoolFighter(sld, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+10, 100, 100, "blade_19", "pistol3", "grapeshot", 100);
		
			LAi_CharacterDisableDialog(sld);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "HOLLAND_CITIZENS");
			ChangeCharacterAddressGroup(sld, "Villemstad_prison", "goto", "goto23");
			LAi_LocationDisableOfficersGen("Villemstad_prison", true);//офицеров не пускать
		break;
		
		case "Vaskez":
			dialog.text = "Most már halottak vagytok... mindketten!";
			link.l1 = "...";
			link.l1.go = "Vaskez_1";
		break;
		
		case "Vaskez_1":
			DialogExit();
			LAi_ActorAnimation(npchar, "shot", "VaskezFight", 2.0);
		break;
		
		case "Portugal_free":
			if (LAi_group_GetTarget(pchar) <= 0)
			{
				dialog.text = "Na, erre nem számítottam, kapitány! De nem úgy néz ki, mint egy baráti látogatás, ez a sok vér, zaj és lövöldözés, vagy ez valami ünnepség tûzijátékkal, mi?";
				link.l1 = "Hagyd abba a gonosz vicceidet, portugál. Csak nem tetszik, ahogy kihasználod a szabadságodat, amit tôlem vettél. Túl sok energiát fektettem a szánalmas segged megmentésébe ahhoz, hogy hagyjam, hogy ilyen ostobán elkapjanak rögtön az elválásunk után!";
				link.l1.go = "Portugal_free_1";
				// belamour legendary edition -->
				link.l2 = "Nos, unatkoztam! Ezért jöttem ide, hogy meglátogassalak. Jól érzed magad itt, barátom!";
				link.l2.go = "Portugal_free_1a";
				// <-- legendary edition
			}
			else
			{
				dialog.text = "Légy óvatos, barátom! Eh, kár, hogy nem tudok segíteni!";
				link.l1 = "...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Portugal_free";
			}
		break;
		// belamour legendary edition -->
		case "Portugal_free_1a":
			AddCharacterExpToSkill(pchar, "Fortune", 100);
			dialog.text = "Szóval a nemességet néha nem befolyásolják az érmék, mi? Hah... VIGYÁZZ, PONT MÖGÖTTED!";
			link.l1 = "Agh, már megint ez a szarság!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("CreateErnandoVaskez");
			NextDiag.TempNode = "Portugal_free";
		break;
		
		case "Portugal_free_1":
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		// <-- legendary edition
			dialog.text = "Szóval a nemességet néha nem befolyásolják az érmék, mi? Hah... VIGYÁZZ, PONT MÖGÖTTED!";
			link.l1 = "Agh, már megint ez a szarság!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("CreateErnandoVaskez");
			NextDiag.TempNode = "Portugal_free";
		break;
		
		case "Portugal_free_2":
			dialog.text = "Pedig én figyelmeztettelek, hogy ez a fickó bajkeverô!";
			link.l1 = "Majdnem sikerült hátba lônie! Hogy jutott át?";
			link.l1.go = "Portugal_free_3";
		break;
		
		case "Portugal_free_3":
			dialog.text = "Láttam, hogy volt nála egy zárfeltörô, úgy látszik, valaki adta neki... mindig is voltak kapcsolatai az alsóbb rétegekben. Nos, kapitány, azt hiszem, el kellene hagynunk ezt a helyet, nem gondolja?";
			link.l1 = "Ne mondd ezt! Rendben, siessünk, mielôtt az egész helyôrség ideér. Egy pillanat alatt feltöröm a zárat...";
			link.l1.go = "Portugal_free_4";
		break;
		
		case "Portugal_free_4":
			DialogExit();
			InterfaceStates.Buttons.Save.enable = true;//разрешить сохраняться
			chrDisableReloadToLocation = false;
			DoQuestReloadToLocation("Villemstad_Exittown", "rld", "loc17", "PortugalFree");
		break;
		
		case "Portugal_free_5":
			dialog.text = "Tudja, kapitány, ez a friss levegô... csak azután kezdi értékelni, hogy néhány hetet egy tömlöcben töltött, rögtön azután, hogy a hajóját' a helyi járôrök megtalálták. Gondolom, még mindig tartozom neked a megmentésemért.";
			link.l1 = "Nem szükséges, portugál. Nem vagyok becsületes lovag, én csak... Azt teszem, amit helyesnek és szükségesnek tartok.";
			link.l1.go = "Portugal_free_6";
		break;
		
		case "Portugal_free_6":
			dialog.text = "Ha, és ez egy tökéletes tulajdonság! De ragaszkodom hozzá, tessék, vedd el... ez az egyetlen dolog, amit el tudtam rejteni a börtönben... Igen, jól mondod. Ez az én talizmánom. Mindig szerencsét hozott nekem a tengeren. Te jó tengerész vagy, és te vagy a navigátorod használni fogja tudni, ebben biztos vagyok.";
			link.l1 = "Igen, és elég szerencsés voltál, hogy egyenesen a hollandok kezébe kerültél ezzel a talizmánnal.";
			link.l1.go = "Portugal_free_7";
		break;
		
		case "Portugal_free_7":
			dialog.text = "Hé! Még mindig élek, nem igaz? És csak hogy tudd, már nem vagyok börtönben. Fogja, kapitány, itt az ideje, hogy a talizmán szolgáljon. És még egyszer köszönöm!";
			link.l1 = "Akkor viszlát, portugálok. És kérlek, próbálj meg távol maradni az akasztófától! Csak a kemény munkám kedvéért, ha-ha!";
			link.l1.go = "Portugal_free_8";
		break;
		
		case "Portugal_free_8":
			TakeNItems(pchar, "talisman2", 1);
			Log_Info("Megkaptad a talizmánt");
			PlaySound("interface\important_item.wav");
			DialogExit();
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 10.0);
			npchar.lifeday = 0;
			LAi_LocationDisableOfficersGen("Villemstad_prison", false);//офицеров пускать
			AddQuestRecord("Portugal", "34");
			CloseQuestHeader("Portugal");
			pchar.questTemp.Portugal = "end";
			pchar.questTemp.Portugal.GG1 = "true"; // Jason Дороже золота
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
