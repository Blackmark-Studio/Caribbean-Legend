// диалоги прочих НПС по квесту LSC
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Kérsz valamit?";
			link.l1 = "Nem, ez semmiség.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		//-----------------------------------бандосы Акулы в трюме с припасами--------------------------------------
		case "PantryGuard":
			dialog.text = "Hó, hó, ezt nézzétek, fiúk! Ki jött meglátogatni minket! Egy tolvaj, aki az emberek ládáit fosztogatja! Gyertek ide! És te, pajtás, meg se próbálj hülyét játszani, és vedd elô a pengédet - ilyen közelrôl nem fogom elvéteni... Chad nagyon fog örülni, hogy lát téged!";
			link.l1 = "De én... Én csak most értem ide!";
			link.l1.go = "PantryGuard_1";
		break;
		
		case "PantryGuard_1":
			dialog.text = "Igazad van, ha-ha! Most kerültél igazán nagy zûrzavarba, haver... És nem fogod megúszni. Most pedig adjátok le a fegyvert és kövessetek engem! A ketrec a 'Tartarus' a ketrecben már oly régóta vár rád, tolvaj!";
			link.l1 = "...";
			link.l1.go = "PantryGuard_2";
		break;
		
		case "PantryGuard_2":
			DialogExit();
			chrDisableReloadToLocation = false;
			SetLaunchFrameFormParam("Néhány órával késôbb...", "", 0, 3);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 7, 10); //крутим время
			RecalculateJumpTable();
			DoQuestFunctionDelay("LSC_GotoPrison", 3.0);
		break;
		
		case "CommonGuard":
			dialog.text = "Ne próbálj meg innen ellopni semmit! Én majd vigyázok rád.";
			link.l1 = "Nagyon szívesen látlak.";
			link.l1.go = "exit";
			NextDiag.TempNode = "CommonGuard";
		break;
		
		case "ChadGuard":
			dialog.text = "Menj és tedd azt, amit Chad mondott neked! Ne beszéljetek túl sokat!";
			link.l1 = "Igen, úton vagyok...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ChadGuard";
		break;
		
		case "ChadGuard_Attack":
			dialog.text = "Hé! Mi a fenét csinálsz ott? Szemétláda! Most már végeztél!";
			link.l1 = "...";
			link.l1.go = "ChadGuard_Attack_1";
		break;
		
		case "ChadGuard_Attack_1":
			DialogExit();
			sld = characterFromId("Chimiset");
			LAi_SetActorType(sld);
			LAi_ActorAnimation(sld, "afraid", "", -1);
			for(i = 1; i <= 3; i++)
			{				
				sld = CharacterFromID("ChadGuard_"+i);
				LAi_RemoveCheckMinHP(sld);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			sld = characterFromId("Capper");
			LAi_SetWarriorType(sld);
			ChangeCharacterAddressGroup(sld, "Tartarusprison", "goto", "goto8");
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "LSC_ChadGuard_Die");
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.GenQuest.Notsearchbody = true; // запрет обыска трупов
		break;
		
		// ----------------------------------Марчелло Циклоп--------------------------------
		// если ждали в каюте
		case "Cabin":
			dialog.text = "Hé, mi a faszt keresel itt, az isten verje meg? Hol van Barbier?";
			link.l1 = "A barátunk, Adolfo... beteg. Nem tudott eljönni a találkozóra, ezért megkért, hogy üljek egy kicsit a kabinjában és várjak rád.";
			link.l1.go = "Cabin_1";
		break;
		
		case "Cabin_A":
			dialog.text = "Hé, mi a faszt keresel itt, az isten verje meg?";
			link.l1 = "Adolfo barátunk... beteg. Nem tudott eljönni a találkozóra, ezért megkért, hogy én legyek helyette. Hogy úgy mondjam.";
			link.l1.go = "Cabin_1";
		break;
		
		case "Cabin_1":
			dialog.text = "Furcsán hangzik... ma reggel még jól volt, most meg beteg.";
			link.l1 = "Nos, tudod, hogy történnek a dolgok. A hirtelen jött láz...";
			link.l1.go = "Cabin_2";
		break;
		
		case "Cabin_2":
			dialog.text = "Ó, nem tetszik az arcod. Hazudik. Barbier soha nem bízná másra ezt a találkozót. Beszélj, te szemétláda, ki vagy te, és mit tettél vele?";
			link.l1 = "Tudod, te sem vagy egy szép arc. Már mondtam neked, hogy Barbier beteg. Lassan gondolkodó típus vagy, vagy ismételjem magam? Neki kellett volna átadnia a kulcsot, és...";
			link.l1.go = "Cabin_3";
		break;
		
		case "Cabin_3":
			DialogExit();
			sld = characterFromId("Mary");
			LAi_SetActorType(sld);
			LAi_CharacterEnableDialog(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		// на Церес Смити - спасаем Мэри
		case "mary":
			dialog.text = "A francba! Lenyomoztál engem...";
			link.l1 = "Igen, te szemétláda! Nem fogsz kezet emelni rá! Készülj a halálra!";
			link.l1.go = "mary_1";
		break;
		
		case "mary_1":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			DialogExit();
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "LSC_KillCyclop_CS");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		// посланник от Акулы по варианту N
		case "SharkCureer":
			dialog.text = "Ön "+GetFullName(pchar)+"?";
			link.l1 = "Igen, én vagyok. Mi a baj?";
			link.l1.go = "SharkCureer_1";
		break;
		
		case "SharkCureer_1":
			dialog.text = "Cápa küldött engem. Arra kéri, hogy minél hamarabb találkozzon vele. Valami fontosat szeretne mondani.";
			link.l1 = "Mi ez a sietség?... Rendben, azonnal a San Agustinba megyek.";
			link.l1.go = "SharkCureer_2";
		break;
		
		case "SharkCureer_2":
			// сюда можно поставить таймер на гибель Акулы, если не придёт до конца суток
			DialogExit();
			LAi_SetActorType(npchar);
			npchar.lifeday = 0;
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			sld = characterFromId("Dodson");
			sld.dialog.currentnode = "entrance_20"; // ноду Акуле
		break;
		
		// посланник от Акулы по варианту M
		case "SharkCureer_3":
			dialog.text = "Ön "+GetFullName(pchar)+"?";
			link.l1 = "Igen, én vagyok. Mi a baj?";
			link.l1.go = "SharkCureer_4";
		break;
		
		case "SharkCureer_4":
			if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie"))
			{
				dialog.text = "Belefáradtam, hogy kereslek... A Cápa és Layton Dexter. Arra kérik, hogy azonnal találkozzon velük. Nagyon fontos dologról van szó, úgyhogy siessen.";
				link.l1 = "Tényleg? Rendben, azonnal a San Agustinba megyek.";
				link.l1.go = "SharkCureer_6";
			}
			else
			{
				dialog.text = "Uh, belefáradtam a keresésedbe... Layton Dexter admirális kéri, hogy azonnal találkozzon vele. Nagyon fontos dologról van szó, úgyhogy siessen.";
				link.l1 = "Admirális?";
				link.l1.go = "SharkCureer_5";
			}
		break;
		
		case "SharkCureer_5":
			dialog.text = "Igen, uram. Mivel ô a második számú parancsnok, a Cápa halála után ô lett az admirálisunk.";
			link.l1 = "Értem. Rendben, azonnal a San Agustinba megyek.";
			link.l1.go = "SharkCureer_6";
		break;
		
		case "SharkCureer_6":
			DialogExit();
			LAi_SetActorType(npchar);
			npchar.lifeday = 0;
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
		break;
		
		// тюремщик вместо Каппера
		case "Prisonboss":
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Á, hát itt vagy... Emlékszem rád, te vagy az utolsó ember, aki beszélt Chimiset-el. Megölted ôt?";
				link.l1 = "Hagyd ezt a baromságot! Pontosan tudod, hogy nem én voltam. Szerintem te tudod, ki a gyilkos.";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Eh, olyan unalmas egész nap itt maradni! Ha hoznál rumot és kártyát, haver, akkor játszhatnánk egy kicsit...";
				link.l1 = "Sajnálom, haver, de erre nincs idôm. Talán késôbb.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Prisonboss";
		break;
		
		case "meeting":
			dialog.text = "Van néhány sejtésem, igen, de nincsenek tényeim. Senki sem látta a fekete fickó halálát. A szigeten mindenfelé pletykálják, hogy mi, Shark emberei vagyunk a felelôsek, és azt mondják, hogy valami újonc tette ezt az admirális parancsára. Látod most? Szóval ne menjetek Rivadosra, fôleg most ne. Túlságosan dühösek.";
			link.l1 = "Jól van, rendben. Megvan.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Prisonboss";
		break;
		
		case "Prisonboss_M":
			dialog.text = "Eh, olyan unalmas egész nap itt maradni! Ha hoznál rumot és kártyát, haver, akkor játszhatnánk egy kicsit...";
			link.l1 = "Sajnálom, haver, de erre nincs idôm. Talán késôbb.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Prisonboss_M";
		break;
		
		// заместитель Акселя в магазине
		case "AxelHelper":
			dialog.text = "Mit akarsz, haver?";
			link.l1 = "Hm. És mi dolgod van itt? Hol van Axel?";
			link.l1.go = "AxelHelper_1";
		break;
		
		case "AxelHelper_1":
			dialog.text = "Axel elfoglalt. Találkozója van Donald Greenspen-nel, és a nap végéig vele marad. Szóval, ha vásárolni akarsz valamit - beszélj vele holnap reggel. És én vigyázok a boltra, úgyhogy ne próbálj meg ellopni semmit...";
			link.l1 = "Értem. És miért pont ma csinálja? Rendben, holnap reggel idejövök.";
			link.l1.go = "exit";
			NextDiag.TempNode = "AxelHelper_2";
		break;
		
		case "AxelHelper_2":
			dialog.text = NPCStringReactionRepeat("Már mindent elmondtam neked. Gyere ide holnap.", 
				"Ne zavarj, haver. Tûnj el!", 
				"Ne dühíts fel, te barom!",
				"Tûnj el!!!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Jól van.", 
				"Megvan, megvan.",
				"Pofa be...", 
				"Mi?!", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);
		break;
		
		// мать Белого Мальчика - Агнес Кристиансен
		case "agnes":
			dialog.text = "Mit akarsz, mynheer?";
			link.l1 = "Hm... Sajnálom, úrnôm. Bocsássa meg szemtelenségemet és rossz modoromat, de szeretnék kérdezni valamit: ismer egy Ole Christiansen nevû férfit?";
			link.l1.go = "agnes_1";
		break;
		
		case "agnes_1":
			dialog.text = "Ismételje meg újra, amit mondott... Ole Christiansen? Ole?!";
			link.l1 = "Igen. Fehér fiúnak is hívják a különleges hajszíne miatt. Ismeri ôt?";
			link.l1.go = "agnes_2";
		break;
		
		case "agnes_2":
			dialog.text = "Ismerem ôt?! Ô a fiam, és már egy évtizede eltûnt! Tudja, hogy hol van, mynheer? Mondja meg, hol van, mi történt vele?!";
			link.l1 = "Nyugodj meg, úrnôm, ne aggódj így. Jól van. A hajómon van. Csak le kell szállnia és idejönnie.";
			link.l1.go = "agnes_3";
		break;
		
		case "agnes_3":
			dialog.text = "Ó... Úgy tûnik, az Úr végre meghallgatta az imáimat! El sem tudod képzelni, mennyire aggódtam, amikor elhibázta! És ez az én hibám volt, és csakis az én hibám! Hol találtad meg? Ô nem egy közönséges gyerek... nos, biztosan tudod, mirôl beszélek.";
			link.l1 = "Tudom. Igen, ô különleges. És nem változott. Úgy tûnik, hogy még mindig gyerek. Egy szigeten találtam rá. Véletlenül találkoztunk egymással. Egy fehér gyöngyöt kért tôlem... a fenébe!... Egy gyöngyöt.";
			link.l1.go = "agnes_4";
		break;
		
		case "agnes_4":
			dialog.text = "Egy gyöngyöt? Ó, Istenem! A gyöngy volt az oka, hogy a fiam eltûnt! Az egész annak az átkozott nyakláncnak köszönhetô!";
			link.l1 = "Igaz, hogy Ole... elment otthonról, mert elszakította a gyöngynyakláncodat?... Nyugodj meg, úrnôm, ne sírj!";
			link.l1.go = "agnes_5";
		break;
		
		case "agnes_5":
			dialog.text = "Igen, ez igaz. Ole elszakította a nyakláncomat a mólónál, és az összes gyöngy a vízbe esett. Annyira szidalmaztam ôt, és a néhai férjem... megbüntette. Ole másnap eltûnt. El sem tudod képzelni, mennyire hibáztattam magam ezért!";
			link.l1 = "Ole évek óta gyöngyöket gyûjtött. Ô fehér gyöngyöknek hívja ôket. Mindet összegyûjtötte neked, és megkért, hogy vigyem el hozzád. A piros tetejû házon kívül semmi részletet nem tudtam. De végül sikerült megtalálnom téged.";
			link.l1.go = "agnes_6";
		break;
		
		case "agnes_6":
			dialog.text = "Gyöngyöket gyûjt?! Ó, Istenem! Olyan bûnös vagyok szegény fiammal szemben! Én... és ô gyöngyöket gyûjtött! Gyöngyöket gyûjt.";
			link.l1 = "Azt hiszem, jobb, ha hívom a fiát, úrnôm. Annyira vágyott rá, hogy láthassa önt. Azt mondta, hogy örülni fog a gyöngyöknek. De azt hiszem, hogy nem a gyöngyök miatt lesz boldog...";
			link.l1.go = "agnes_7";
		break;
		
		case "agnes_7":
			dialog.text = "Mynheer... lennél szíves... Hozd el nekem az Ole-t. Meg akarom ölelni és bocsánatot kérni tôle...";
			link.l1 = "Persze, úrnôm. Azonnal ide fogják hozni.";
			link.l1.go = "agnes_8";
		break;
		
		case "agnes_8":
			DialogExit();
			SetLaunchFrameFormParam("Egy órával késôbb", "", 0, 5);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 10); //крутим время
			RecalculateJumpTable();
			DoQuestFunctionDelay("LSC_OleGoHome", 5.0);
		break;
		
		case "agnes_9":
			dialog.text = "";
			link.l1 = "Nos, úrnôm, itt van a fia, Ole Christiansen. Felismeri ôt?";
			link.l1.go = "agnes_10";
		break;
		
		case "agnes_10": // перекидываем pchar
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorTurnToCharacter(pchar, characterFromID("Agnes"));
			ChangeShowIntarface();
			SetMainCharacterIndex(GetCharacterIndex("Agnes"));
			PChar = GetMainCharacter();			
			LAi_SetPlayerType(PChar);
			sld = characterFromId("Ole");
			sld.dialog.currentnode = "home";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "agnes_11":
			dialog.text = "Mynheer... Sajnálom, nem kérdeztem a nevét... "+pchar.name+"?";
			link.l1 = ""+GetFullName(pchar)+", úrnô. Kapitány "+GetFullName(pchar)+".";
			link.l1.go = "agnes_12";
		break;
		
		case "agnes_12":
			dialog.text = "Kapitány, el sem tudja képzelni, mennyire hálás vagyok a fiamért! Ön segített neki és idehozta. Újra életre keltettél! Mindent megteszek a fiamért, megadom neki minden szeretetemet, ami az elmúlt években hiányzott neki.";
			link.l1 = "Örülök neked, úrnôm. És Ole-nak is. Ô egy jó fiú, és segített nekem a nehéz helyzetben. Jó szíve van. Ismerek egy embert, akit Ole mentett meg a haláltól.";
			link.l1.go = "agnes_13";
		break;
		
		case "agnes_13":
			dialog.text = "Mynheer, ragaszkodom hozzá, hogy holnap vagy bármikor, amikor csak idôd engedi, gyere ide. Szeretném megköszönni a fiamért. Ebben a pillanatban egy kicsit... nos, tudod...";
			link.l1 = "Tudom, úrnôm.";
			link.l1.go = "agnes_14";
		break;
		
		case "agnes_14":
			dialog.text = "Jöjjön vissza holnap. Megjutalmazlak téged minden jóért, amit a fiammal és velem tettél.";
			link.l1 = "Jól van. Biztosan meglátogatom!";
			link.l1.go = "agnes_15";
		break;
		
		case "agnes_15":
			DialogExit();
			bDisableCharacterMenu = false;//лоченые интерфейсы
			chrDisableReloadToLocation = false;//открыть локацию
			LAi_SetOwnerType(npchar);
			LocatorReloadEnterDisable("Marigo_town", "houseSp2", true);
			NextDiag.CurrentNode = "agnes_16";
			pchar.quest.LSC_Ole_return.win_condition.l1 = "Timer";
			pchar.quest.LSC_Ole_return.win_condition.l1.date.hour  = 8.0;
			pchar.quest.LSC_Ole_return.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.LSC_Ole_return.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.LSC_Ole_return.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.LSC_Ole_return.function = "LSC_OleAgnesRegard";
			// удаляем Оле из пассажиров
			sld = characterFromId("Ole");
			RemovePassenger(Pchar, sld);
			DeleteAttribute(pchar, "GenQuest.Ole");
			DoQuestReloadToLocation("Marigo_town", "reload", "houseSp2", "");
		break;
		
		case "agnes_16":
			dialog.text = "Ah, itt vagy, mynheer "+GetFullName(pchar)+"! Gyere, ülj le...";
			link.l1 = "Köszönöm! Hogy van Ole?";
			link.l1.go = "agnes_17";
		break;
		
		case "agnes_17":
			dialog.text = "Ó, el sem tudod képzelni, mit tettél! Olyan látvány voltál, hogy az anyai szívnek fájt a szíve... Tartozom neked, és örökké imádkozni fogok érted.";
			link.l1 = "Elpirultam, úrnôm...";
			link.l1.go = "agnes_18";
		break;
		
		case "agnes_18":
			dialog.text = "Mindig is tudtam, hogy a szerénység az, ami nemes embereket nemessé tesz... Készítettem ajándékokat azért, amit tettél. Igen-igen! És ne merészeld visszautasítani! Tessék, fogd ezt... Elôször is, itt van egy láda tele dublonnal. Másodszor, fogd ezt a varázslatos amulettet, szkarabeusznak hívják\nA férjemé volt, és biztos vagyok benne, hogy örült volna, ha megtudja, hogy a kincse egy ilyen nemes kapitányé lesz, aki visszaadta nekem a fiamat. A férjem ács volt, azt szokta mondani, hogy a szkarabeusz felgyorsítja a munkáját\nremélem, hogy ez a gyûrû jó szolgálatot tesz majd neked. Kétségtelenül megérdemli, hogy viselje! És végül, fogd a szabószerszámaimat. Ez egy remek készlet. Sok jó dolgot tudsz majd belôle készíteni.";
			link.l1 = "Ó! Ezek igazán értékes ajándékok minden kapitánynak! Köszönöm, úrnôm.";
			link.l1.go = "agnes_19";
		break;
		
		case "agnes_19":
			PlaySound("interface\important_item.wav");
			Log_Info("Kaptál egy ládát dublonnal");
			Log_Info("Megkaptad a 'Skarabeusz' amulettet.");
			Log_Info("Kaptál egy ruhakészletet");
			GiveItem2Character(pchar, "chest");
			GiveItem2Character(pchar, "talisman7");
			GiveItem2Character(pchar, "tailor_tool");
			dialog.text = "És szeretném, ha tudnád, hogy a házam ajtaja mindig nyitva áll elôtted, bármikor. Mindig találsz itt ételt, egy üveg finom bort és bármi mást, amit csak akarsz.";
			link.l1 = "Köszönöm a kedves szavakat, úrnôm. Örömmel látom majd, ha újra ellátogatok ebbe a városba.";
			link.l1.go = "agnes_20";
		break;
		
		case "agnes_20":
			dialog.text = "Ne mulassza el eljönni!";
			link.l1 = "És most mennem kell. Viszontlátásra és sok szerencsét!";
			link.l1.go = "agnes_21";
		break;
		
		case "agnes_21":
			DialogExit();
			NextDiag.CurrentNode = "agnes_22";
			AddCharacterExpToSkill(pchar, "Fortune", 350);
			AddCharacterExpToSkill(pchar, "Leadership", 500);
			ChangeCharacterComplexReputation(pchar, "nobility", 10);
			ChangeCharacterComplexReputation(pchar, "authority", 4);
		break;
		
		case "agnes_22":
			dialog.text = "Ah, kapitány "+GetFullName(pchar)+"! Annyira örülök, hogy látlak! Gyere, ülj le, felszolgálok neked egy italt...";
			link.l1 = "Köszönöm! Csak üdvözölni akartalak, és tudni akartam, hogy hogy vagy. Örülök, hogy te és Ole jól vagytok.";
			link.l1.go = "exit";
			NextDiag.TempNode = "agnes_22";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
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
	}
}
