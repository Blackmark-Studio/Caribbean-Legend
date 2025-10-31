void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, Diag;
	int i;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();			
		break;
		//----------------- уничтожение банды ----------------------
		case "DestroyGang_begin":
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false); //боевке можно
			DeleteAttribute(&locations[FindLocation(pchar.GenQuest.DestroyGang.Location)], "DisableEncounters"); //энкаунтеры можно 
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("MayorQuestGang_" + i) == -1) continue;
				sld = CharacterFromID("MayorQuestGang_" + i);
				LAi_type_actor_Reset(sld);
				LAi_RemoveCheckMinHP(sld);
			}
			sTemp = GetFullName(&characters[GetCharacterIndex(pchar.GenQuest.DestroyGang.MayorId)]);
			dialog.text = LinkRandPhrase("Cash on the barell "+ GetSexPhrase("haver","lass") +"! Az én nevem " + GetFullName(npchar) + ", és nem szoktam ellenvetéseket tenni....",
				"Most pedig mutasd meg az erszényedet, "+ GetSexPhrase("pajtás","lass") +", és gyorsan! A nevem  " + GetFullName(npchar) + ", és remélem, hallottál már rólam...",
				"Adj nekem minden értéket, amid van, a pénztárcád tartalmát is elkérem. És siess, a türelem nem az erôsségem. A vérszomjamról nem mondhatom el ugyanezt!");
			Link.l1 = LinkRandPhrase("Heh, szóval te vagy az a híres bandita " + GetFullName(npchar) + ", akirôl a helyi kormányzó " + sTemp + " soha nem áll le beszélni?",
				"Ó, szóval te vagy az a bandita, akit a helyi kormányzó " + sTemp + "levadászott?!", 
				"Örülök"+ GetSexPhrase("","") +" , hogy látlak, " + GetFullName(npchar) + ". A helyi kormányzó, " + sTemp + " csak rólad beszél.");
			Link.l1.go = "DestroyGang_1";
		break;		
		case "DestroyGang_1":
			dialog.text = LinkRandPhrase("Igen, jól ismert vagyok ezeken a földeken, he-he-he... Várj csak, te nem egy másik "+ GetSexPhrase("mocskos kopó vagy","mocskos szuka") +" a kormányzónak, akit a nyomomra küldött?",
				"A kormányzó a jó barátom, ez igaz. És te nem vagy véletlenül "+ GetSexPhrase("egy másik hôs, akit","egy másik hôsnô, akit") +" ô küldött a fejemért?",
				"A kormányzó a legjobb párom, ez nem titok, he-he. De honnan tudod ezt? Talán ô küldte utánam?");
			Link.l1 = LinkRandPhrase("Pontosan, gazember. Készülj a halálra!", "Hát nem vagy te egy gyors észjárású! Rendben, ideje folytatni a likvidálásodat. Elég a beszédbôl.", "Igen, ez vagyok én. Vedd elô a fegyvered, haver! Lássuk, milyen színû a véred.");
			Link.l1.go = "DestroyGang_ExitFight";	
			Link.l2 = LinkRandPhrase("Ó, nem érdekes! Egyáltalán nincs szükségem ilyen gondokra...", "Nem, nem, nem vagyok hôs, semmiképpen sem...", "Nem, nem, én soha! Nincs szükségem bajokra...");
			Link.l2.go = "DestroyGang_2";	
		break;
		case "DestroyGang_2":
			dialog.text = LinkRandPhrase("Így már jobb, "+ GetSexPhrase("haver","lass") +"...És most tûnj el!",
				"És ez egy helyes döntés. Bárcsak tudnád, hány hôst küldtem egy másik világba... Rendben, kevesebb szóval. Tûnj el, "+ GetSexPhrase("szarházi","kurva") +"!",
				"Jó "+ GetSexPhrase("fiú","lány") +"! Nagyon bölcs döntés - nem avatkozni mások ügyeibe... Na jó, tûnj már el, "+ GetSexPhrase("pajtás","lány") +".");
			Link.l1 = "Viszlát és sok szerencsét neked...";
			Link.l1.go = "DestroyGang_ExitAfraid";	
		break;

		case "DestroyGang_ExitAfraid":
			pchar.GenQuest.DestroyGang = "Found"; //флаг нашёл, но струсил
			npchar.money = AddMoneyToCharacter(npchar, sti(pchar.money));
			pchar.money = 0;
			LAi_SetWarriorType(npchar);
			LAi_SetImmortal(npchar, false);
			LAi_SetCheckMinHP(npchar, LAi_GetCharacterHP(npchar)-1, false, "DestroyGang_SuddenAttack");
			for(i = 1; i < 4; i++)
			{
				if (GetCharacterIndex("MayorQuestGang_" + i) == -1) continue;	
				sld = CharacterFromID("MayorQuestGang_" + i);
				LAi_SetActorType(sld);
				LAi_ActorFollow(sld, npchar, "", -1);
				LAi_SetImmortal(sld, true);
				LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, false, "DestroyGang_SuddenAttack");
			}
			DialogExit();
		break;

		case "DestroyGang_ExitFight":
			for(i = 0; i < 4; i++)
			{
				if (GetCharacterIndex("MayorQuestGang_" + i) == -1) continue;
				sld = CharacterFromID("MayorQuestGang_" + i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "DestroyGang_Afrer");
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		// ОЗГ - пассажир
		case "ContraPass_abordage":
			dialog.text = "Arghh, te gazember! Hogy merted megtámadni a hajómat?! Ezért megfizetsz!";
			link.l1 = "Éppen ellenkezôleg, valójában fizetnek érte. Van egy bizonyos ember a fedélzeten, a neve "+pchar.GenQuest.TakePassenger.Name+". Ô az, akire szükségem van.";
			link.l1.go = "ContraPass_abordage_1";
		break;
		
		case "ContraPass_abordage_1":
			dialog.text = "Tudtam, hogy ez a csaló bajt hoz ránk... De nem fogsz ilyen könnyen elkapni! Védd magad, mocskos kalóz!";
			link.l1 = "Neked kell gondolkodnod a védekezésen, te kis kurva.";
			link.l1.go = "ContraPass_abordage_2";
		break;
		
		case "ContraPass_abordage_2":
			DialogExit();
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "ContraPass_GivePrisoner");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Tempsailor":
			dialog.text = "Kapitány, átkutattuk a kabinokat és a rakteret, ahogy parancsoltad. Az a gazember megpróbált elbújni, de megtaláltuk.";
			link.l1 = "Kitûnô! Hol van most?";
			link.l1.go = "Tempsailor_1";
		break;
		
		case "Tempsailor_1":
			dialog.text = "A raktérben, ahogy parancsolta.";
			link.l1 = "Kitûnô! Most pedig szálljunk le errôl a vén kádról. Ideje visszatérni.";
			link.l1.go = "Tempsailor_2";
		break;
		
		case "Tempsailor_2":
			dialog.text = "Azonnal, kapitány!";
			link.l1 = "...";
			link.l1.go = "Tempsailor_3";
		break;
		
		case "Tempsailor_3":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 10.0);
			sld = GetCharacter(NPC_GenerateCharacter("ContraPass", "citiz_"+(rand(9)+11), "man", "man", 10, sti(pchar.GenQuest.TakePassenger.Nation), -1, true, "quest"));
			sld.name = pchar.GenQuest.TakePassenger.Name;
			sld.lastname = "";
			pchar.GenQuest.LastQuestPrisonerIdx = SetCharToPrisoner(sld);
			SetCharacterRemovable(&characters[sti(pchar.GenQuest.LastQuestPrisonerIdx)], false);
			Pchar.GenQuest.TakePassenger.PrisonerIDX = sti(pchar.GenQuest.LastQuestPrisonerIdx);
		break;
		
		case "Fugitive_city": // ходит по городу
			pchar.quest.AllMayorsQuests_Late.over = "yes"; //снимаем общий таймер
			dialog.text = "Mit akar, uram?";
			link.l1 = "Nos, nos... Szóval te vagy "+pchar.GenQuest.FindFugitive.Name+", ugye? Nagyon örülök, hogy látlak...";
			link.l1.go = "Fugitive_city_1";
		break;
		
		case "Fugitive_city_1":
			dialog.text = "Hát, valóban én vagyok az, bár miért örül, hogy lát engem? Furcsának tûnik nekem, mivel még sosem láttam önt... Megmagyarázná?";
			link.l1 = "De természetesen. A "+XI_ConvertString("Colony"+pchar.GenQuest.FindFugitive.Startcity+"Gen")+", a helyi kormányzó parancsára jöttem. Letartóztattak, és ugyanabba a városba kell szállítanom... Ó, és el a kezekkel a szablyádtól! Ne próbálkozz semmi ostobasággal jóember, különben rosszul sül el a dolog!";
			link.l1.go = "Fugitive_city_2";
		break;
		
		case "Fugitive_city_2":
			dialog.text = "Szóval mégiscsak megtaláltál... Uram, hallgasson meg, és talán meggondolja magát. Igen, dezertáltam a helyôrségbôl. De nem tudtam végignézni a hadseregünk leépülését!\nBékés életet akartam, és itt, ebben a faluban találtam meg... Hagyjatok békén, mondjátok meg nekik, hogy nem találtatok meg, vagy hogy kalózokkal együtt a nyílt tengerre szöktem. Cserébe neked adom ezt a borostyánnal teli erszényt. Egy nagyon értékes tárgyat, azt kell mondanom...";
			link.l1 = "Eszébe se jusson megvesztegetni engem, uram! Adja át a fegyverét és kövessen!";
			link.l1.go = "Fugitive_city_fight";
			link.l2 = "Hmm... Rosszra? Csendes és békés élet? Rendben, azt hiszem, valóra tudom váltani a kívánságodat. Hol van a borostyánod?";
			link.l2.go = "Fugitive_city_gift";
		break;
		
		case "Fugitive_city_fight":
			dialog.text = "Akkor húzd ki a pengédet, zsoldos! Nem fogsz ilyen könnyen elkapni!";
			link.l1 = "Rendben, lássuk, mit érsz!";
			link.l1.go = "Fugitive_fight_1";
		break;
		
		case "Fugitive_city_gift":
			TakeNItems(pchar, "jewelry8", 50+hrand(25));
			TakeNItems(pchar, "jewelry7", 2+hrand(5));
			PlaySound("interface\important_item.wav");
			Log_Info("Ön borostyánszínû borostyánt kapott");
			dialog.text = "Tessék... És remélem, hogy soha többé nem látlak sem téged, sem más 'envoys' .";
			link.l1 = "Biztosíthatlak, hogy nem fogsz. Viszlát, uram!";
			link.l1.go = "Fugitive_gift_exit";
		break;
		
		case "Fugitive_gift_exit":
			DialogExit();
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
			pchar.GenQuest.FindFugitive = "Found"; //флаг провалил
			AddQuestRecord("MayorsQuestsList", "12-4");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+pchar.GenQuest.FindFugitive.Startcity));
		break;
		
		case "Fugitive_fight_1":// в городе и бухте
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			Diag.currentnode = "Fugitive_afterfight";
			LAi_SetImmortal(npchar, false);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_SetCheckMinHP(npchar, 10.0, true, "Fugitive_afterfight");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "Fugitive_afterfight":
			dialog.text = "Arrgh! Nyertél, cseszd meg! Megadom magam...";
			link.l1 = "Vigyázzon a nyelvére, uram! És most add ide a szablyádat, kérlek... Kövessetek, és buta trükkök nélkül!";
			link.l1.go = "Fugitive_afterfight_1";
		break;
		
		case "Fugitive_afterfight_1":
			DialogExit();
			RemoveAllCharacterItems(npchar, true);
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			//DeleteAttribute(npchar, "LifeDay");
			npchar.lifeday = 0;
			LAi_SetImmortal(npchar, true);
			pchar.GenQuest.LastQuestPrisonerIdx = SetCharToPrisoner(npchar);
			SetCharacterRemovable(&characters[sti(pchar.GenQuest.LastQuestPrisonerIdx)], false);
			Pchar.GenQuest.FindFugitive.PrisonerIDX = sti(pchar.GenQuest.LastQuestPrisonerIdx);
			pchar.GenQuest.FindFugitive = "Execute"; //флаг выполнил успешно
			pchar.quest.FindFugitive1.win_condition.l1 = "location";
			pchar.quest.FindFugitive1.win_condition.l1.location = pchar.GenQuest.FindFugitive.Startcity+"_townhall";
			pchar.quest.FindFugitive1.function = "FindFugitive_inResidence";
			SetFunctionTimerCondition("FindFugitive_Over", 0, 0, 30, false);
		break;
		
		case "Fugitive_shore": // в бухте
			pchar.quest.AllMayorsQuests_Late.over = "yes"; //снимаем общий таймер
			dialog.text = "Uram, nincs kedvem beszélgetni veled, úgyhogy...";
			link.l1 = "Mindazonáltal beszélnie kell velem. Ön "+pchar.GenQuest.FindFugitive.Name+", ugye? Szerintem nem kéne tagadnod.";
			link.l1.go = "Fugitive_shore_1";
		break;
		
		case "Fugitive_shore_1":
			dialog.text = "És nem fogom letagadni, ez vagyok én. De mit akarsz?";
			link.l1 = "El kell vigyelek a "+XI_ConvertString("Colony"+pchar.GenQuest.FindFugitive.Startcity)+", a helyi kormányzó nagyon szeretne látni téged. Semmi ostoba trükk, kérem! Add át a fegyvered és kövess engem!";
			link.l1.go = "Fugitive_shore_2";
		break;
		
		case "Fugitive_shore_2":
			dialog.text = "Értem... Uram, mielôtt csípôbôl lône, hadd mondjak valamit. Igen, dezertáltam a helyôrségbôl. De okom volt rá. Nem maradhatok a szolgálatban, ez több, mint amit el tudok viselni! Megértettél engem? Nem tehetem!\nBékés életet akarok, és itt, ebben a faluban találtam meg ezt az életet... Hagyjatok békén, mondjátok meg nekik, hogy nem sikerült megtalálnotok, vagy hogy kalózokkal együtt a nyílt tengerre szöktem. Cserébe odaadom a heti gyöngyfogásomat. Ez minden, amim van.";
			link.l1 = "Eszébe se jusson megvesztegetni engem, uram! Adja át a fegyverét és kövessen!";
			link.l1.go = "Fugitive_city_fight";
			link.l2 = "Hmm... Belefáradtál a katonai szolgálatba? Békés életet akarsz? Rendben, azt hiszem, valóra tudom váltani a kívánságodat. Hol vannak a gyöngyeid?";
			link.l2.go = "Fugitive_shore_gift";
		break;
		
		case "Fugitive_shore_gift":
			TakeNItems(pchar, "jewelry52", 100+hrand(40));
			TakeNItems(pchar, "jewelry53", 400+hrand(100));
			PlaySound("interface\important_item.wav");
			Log_Info("Gyöngyöket kaptál");
			dialog.text = "Tessék... És remélem, hogy soha többé nem látlak sem téged, sem más 'envoys' .";
			link.l1 = "Biztosíthatlak, hogy nem fogsz. Viszlát, uram!";
			link.l1.go = "Fugitive_gift_exit";
		break;
		
		case "Fugitive_tavern": // в таверне
			pchar.quest.AllMayorsQuests_Late.over = "yes"; //снимаем общий таймер
			dialog.text = "Ehhh... hic! Uram, én nem keresek társaságot - fôleg nem az önét. Tûnjetek el!";
			link.l1 = "De keresem a társaságát, "+pchar.GenQuest.FindFugitive.Name+"! És a hajóm rakterében megtûrheted a társaságomat. Mi a  "+XI_ConvertString("Colony"+pchar.GenQuest.FindFugitive.Startcity)+", a város kormányzójához megyünk. Szinte már alig várja, hogy láthasson téged.";
			link.l1.go = "Fugitive_tavern_1";
		break;
		
		case "Fugitive_tavern_1":
			dialog.text = "H-Hic!"+RandSwear()+" Szóval mégiscsak levadászott! Figyelj, haver, nem tudod mi történt, nem voltál ott! Nem tudtam ott maradni a szertartáson, egyszerûen nem tudtam! Még mindig minden este berúgok, hogy elfelejtsem ezt\nNézd, kössünk üzletet! Mondd el neki, hogy nem sikerült megtalálnod, vagy hogy kalózokkal együtt a nyílt tengerre szöktem. Cserébe odaadom neked az összes rögöt, amit a helyi barlangban találtam. Ez mindenem, látod, mindent odaadok neked, csak azért, hogy soha ne lássam "+XI_ConvertString("Colony"+pchar.GenQuest.FindFugitive.Startcity)+"...";
			link.l1 = "Eszébe se jusson megvesztegetni engem, uram! Adja át a fegyverét és kövessen!";
			link.l1.go = "Fugitive_tavern_fight";
			link.l2 = "Hmm... Egy kellemetlen történet? Rémálmok vagy rossz lelkiismeret gyötrik? Rendben, azt hiszem, ezzel magadra hagylak. Hol vannak a rögök?";
			link.l2.go = "Fugitive_tavern_gift";
		break;
		
		case "Fugitive_tavern_gift":
			TakeNItems(pchar, "jewelry5", 50+hrand(30));
			TakeNItems(pchar, "jewelry6", 100+hrand(50));
			PlaySound("interface\important_item.wav");
			Log_Info("Kaptál rögöket");
			dialog.text = "Tessék... És remélem, hogy soha többé nem látlak sem téged, sem más 'envoys' .";
			link.l1 = "Biztosíthatlak, hogy nem fogsz. Viszlát, uram!";
			link.l1.go = "Fugitive_gift_exit";
		break;
		
		case "Fugitive_tavern_fight":
			dialog.text = "Akkor húzd ki a pengédet, zsoldos! Nem fogsz ilyen könnyen elkapni!";
			link.l1 = "Rendben, lássuk, mit érsz!";
			link.l1.go = "Fugitive_fight_2";
		break;
		
		case "Fugitive_fight_2":// в таверне
			DialogExit();
			chrDisableReloadToLocation = true;//закрыть локацию
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			LAi_SetImmortal(npchar, false);
			LAi_SetStayType(npchar);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(npchar, pchar.location, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			Diag.currentnode = "Fugitive_afterfight";
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_SetCheckMinHP(npchar, 10.0, true, "Fugitive_afterfight");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
	}
}
