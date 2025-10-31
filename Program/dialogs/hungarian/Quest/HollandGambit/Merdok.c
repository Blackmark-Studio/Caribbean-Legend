// Джон Мердок, он же Йохан ван Мерден, соратник Роденбурга
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sTemp;
	int iTemp;
	bool bOk;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
		if (!CheckAttribute(pchar, "questTemp.HWIC.Self") && LAi_grp_playeralarm > 0)
		{
			dialog.text = "Uram, nagyon rossz idôpontot választott a csevegésre. Az egész helyôrség téged keres. Jobb lenne, ha gyorsan eltûnne...";
			link.l1 = "Ne aggódjon. Nem maradok sokáig.";
			link.l1.go = "exit";
			break;
		}
		// продажа алхимического набора, если провалил гамбит
		if (CheckAttribute(pchar, "questTemp.HWIC.Detector") && !CheckAttribute(npchar, "quest.alchemy"))
		{
			bOk = (findsubstr(pchar.questTemp.HWIC.Detector, "_fail" , 0) != -1) || (pchar.questTemp.HWIC.Detector == "eng_win_half");
			if (bOk)
			{
				dialog.text = "Isten hozta, kapitány. Érdekelné egy érdekes ajánlat? ";
				link.l1 = "Úgy tûnik, mindenféle embernek van ilyen ajánlata, és én kíváncsi ember vagyok. Mi lenne az? ";
				link.l1.go = "alchemy";
				break;
			}
		}
		// Страж Истины
		if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "merdok1")
		{
			dialog.text = "Szép napot. Üdvözlöm a patikámban. Vannak gyógyszereim a legtöbb betegség és gyengeség kezelésére. Mit ajánlhatok önnek?";
			link.l1 = "Figyelj, John, az a hír járja, hogy valaki lakik nálad a második emeleten...";
			link.l1.go = "guardoftruth";
			break;
		}
//-----------------------------------------за Голландию------------------------------------------------
		if (CheckAttribute(pchar, "questTemp.HWIC.Holl"))
		{
			if (pchar.location.from_sea == "SentJons_town" && pchar.questTemp.HWIC.Holl == "toAntigua")
			{
				dialog.text = "Jó napot, uram. Örülök, hogy látom a patikámban. A legtöbb betegségre és gyengeségre van gyógyszerem. Mit ajánlhatok?";
				link.l1 = "Üdvözlöm, Mr. Murdock. Lucas Rodenburg nevében vagyok itt. Azért küldött önhöz, hogy megbeszéljünk egy Richard Fleetwooddal kapcsolatos ügyet.";
				link.l1.go = "Knippel_exit";
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "toAntigua")
			{
				dialog.text = "Jó napot kívánok. Milyen problémája van? Van köhögéscsillapító és hasmenés elleni porom is!";
				link.l1 = "Jó napot, Mr. Murdock. Lucas Rodenburg nevében vagyok itt. Azért küldött önhöz, hogy egy Richard Fleetwooddal kapcsolatos ügyrôl beszéljünk.";
				link.l1.go = "Knippel";
				DelLandQuestMark(npchar);
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "KillMerdok")
			{
				dialog.text = "Ahhh, itt van Rodenburg bérkutyája... Hercule, Longway - kijönnétek ide?\nÖld meg ezt az embert!";
				link.l1 = "Várjon, van receptem!";
				link.l1.go = "Merdok_fight";
				break;
			}
			dialog.text = "Jó napot! Jó napot! Örülök, hogy a patikámban látom. A legtöbb betegségre és betegségre van gyógyszerem. Mit ajánlhatok önnek?";
			link.l1 = "Jelenleg semmit, köszönöm. Egész jól érzem magam.";
			link.l1.go = "exit";
			break;
		}
//----------------------------------------------за Англию---------------------------------------------------
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng") && pchar.questTemp.HWIC.Eng == "MerdokMeeteng")
			{
			dialog.text = "Üdvözlöm, hívatlan vendég. Nem takarja el az arcát maszkkal, és nem úgy néz ki, mint egy rabló. Ezért arra a következtetésre jutottam, hogy valami másra van szüksége egy szegény drogistától. Talán valami hasmenésre?";
			link.l1 = "Üdvözlöm önt is, Johan van Merden. Hercule Tonzag üdvözletét hozom. Látom, ismered ezt a nevet.";
			link.l1.go = "Merdok_talk";
			DelLandQuestMark(npchar);
			break;
			}
//--------------------------------------------против всех--------------------------------------------------
			if (CheckAttribute(pchar, "questTemp.HWIC.Self"))
			{
				if (pchar.questTemp.HWIC.Self == "HuntFleetwood")
				{
					dialog.text = "Á, hát itt vagy. Nos, találkoztál már Hercule-lal? ";
					link.l1 = "Igen, ismerem. Megállapodtunk. John, segíteni fogok Hercule-nak, és több kérdésem is van önhöz Richard Fleetwooddal kapcsolatban.";
					link.l1.go = "About_Fleetwood";
					break;
				}
				if (GetQuestPastDayParam("questTemp.Wait_Fleetwood") > 6 && pchar.questTemp.HWIC.Self == "WaitFleetwood")
				{
					dialog.text = "Helló! Örülök, hogy látlak, " + pchar.name + "!";
					link.l1 = "Helló, John. Találtál valamit Fleetwoodról?";
					link.l1.go = "About_Fleetwood_9";
					pchar.quest.Wait_FleetwoodOver.over = "yes"; //снять таймер
					break;
				}
				if (pchar.questTemp.HWIC.Self == "HWICSelf_fail")
				{
					dialog.text = "Elkéstél. A madár kirepült. Charlie Knippel meglátogatta Willemstadot, és hozott egy lányt Richardnak. Most egy-két nap múlva Angliába hajóznak egy katonai hajórajjal. Fleetwood elment, soha többé nem látod ôt ebben az életben.";
					link.l1 = "A fenébe is. Teljesen megfeledkeztem Richardról, és elvesztettem az idôérzékemet. Viszlát.";
					link.l1.go = "About_Fleetwood_17";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "AbigileOnShip")
				{
					dialog.text = "Üdvözöllek újra, " + pchar.name + "! Most nincs semmi a számodra. Fleetwoodról nincs hír, Charlie Knippel pedig még nem tért vissza Curacaóból...";
					link.l1 = "És soha nem is fog. Sem ô, sem a brigantinja.";
					link.l1.go = "Abigile";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "AbigileInHouse")
				{
					dialog.text = "Á, vendégeink vannak! Helló, Charlie! Jó napot, kisasszony!";
					link.l1 = "Jó napot, John! Engedje meg, hogy bemutassam önnek nôi kísérômet, Richard menyasszonyát, a bájos Abigail Shneurt.";
					link.l1.go = "Abigile_7_1";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "AbigileInRoom")
				{
					dialog.text = "Halkabban... Mit fogsz most csinálni?";
					link.l1 = "Következô? Inkább aludnék egy kicsit, de sajnos erre nincs idô. Kiásom Fleetwoodot a gödörbôl, amelyben rejtôzik, és befejezem Hercule munkáját.";
					link.l1.go = "Abigile_9";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "LetterToFleetwood")
				{
					dialog.text = "Befejezted az írást? Hadd nézzem... Istenem, Charlie, te egy igazi ôrült vagy! Nem gondolod, hogy ezt egy kicsit túlságosan is részletesen írtad? Úgy értem, az a rész Miss Shneur ujjairól, füleirôl és arcáról? Beteges tehetséged van, az biztos. A fenébe is, mindjárt elvesztem az ebédemet!";
					link.l1 = "Csak blöffölök, John. Nem fogom megölni a lányt. Rávehetném, hogy elválassza az ujját... De semmi több. Még kilenc van neki.";
					link.l1.go = "Abigile_15";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "FleetwoodAgree")
				{
					dialog.text = "Jól ment? Látom a szemedben - megcsináltad!";
					link.l1 = "Igen. Fleetwood elfogadta a feltételeimet. A csapda állkapcsa bezárul. Most várunk.";
					link.l1.go = "Abigile_23";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "FleetwoodDied")
				{
					dialog.text = "Ah, üdv újra itt, barátom! Mit tudsz mondani?";
					link.l1 = "Fleetwood halott. Minden a terv szerint ment. Megérkezett a szigetre, ahol én csapdát állítottam a parton. Elég nagy harcot vívott, de ez nem használt neki. Csak egyikünk hagyta el a partot.";
					link.l1.go = "Abigile_27";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "MeetTonzag")
				{
					dialog.text = "Rendben " + pchar.name + ", van egy komoly ajánlatom számodra. A dolog, amirôl beszélni fogok, nagyon veszélyes, de figyelembe véve azt, ahogyan megszabadultál Fleetwoodtól, biztos vagyok benne, hogy meg tudod oldani. Magának... ritka érzéke van a nehéz problémák megoldásához.";
					link.l1 = "Ez hízelgô. Beszéljen tovább.";
					link.l1.go = "Lucas";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "SeekAbiIsland")
				{
					DelLandQuestMark(npchar);
					DelMapQuestMarkCity("SentJons");
					dialog.text = "Üdvözöllek újra, " + pchar.name + "! Van valami jó hír számomra?";
					link.l1 = "John, mostantól kés nélkül alhatsz a párnád alatt. Lucas többé nem jelent veszélyt rád. Letartóztatták és bezárták, és hamarosan Hollandiába küldik, ahol lázadásért, gyilkossági kísérletért és más vétségekért bíróság elé állítják.";
					link.l1.go = "Lucas_10";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "VanbergDestroyed")
				{
					DelLandQuestMark(npchar);
					DelMapQuestMarkCity("SentJons");
					dialog.text = "Örülök, hogy látlak, " + pchar.name + "! Életben vagy - és ez jó dolog. Van valami hír?";
					link.l1 = "Igen, uram. Van Berg örökre eltûnt. Ahogy mondta, lenyomozott engem, és a legkényelmetlenebb pillanatban támadott meg. Van Berg kemény dió volt, de végül megtörtem.";
					link.l1.go = "Final";
					break;
				}
			dialog.text = "Szüksége van még valamire?";
			link.l1 = "Nem, John, semmi. Elmegyek.";
			link.l1.go = "exit";
			break;
			}
			dialog.text = "Jó napot! Jó napot! Örülök, hogy a patikámban látom. A legtöbb betegségre és betegségre van gyógyszerem. Mit ajánlhatok önnek?";
			link.l1 = "Jelenleg semmit, köszönöm. Egész jól érzem magam.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

//--------------------------------------------за Голландию-----------------------------------------------------
		case "Knippel_exit":
			dialog.text = "Fogalmam sincs, mirôl beszél, uram. Milyen Lucas Rodenburg? Nincs semmi dolgom a hollandokkal. Biztosan tévedett.";
			link.l1 = "Tévedtél. Mynheer Rodenburg küldött magához!";
			link.l1.go = "Knippel_exit_1";
		break;
		
		case "Knippel_exit_1":
			dialog.text = "Hadd mondjam el még egyszer - nem ismerek semmilyen Mynheer Rodenburg nevû embert. Ami a hollandokat illeti, nem üzletelek velük. Csak két dolgot nem tudok elviselni ezen a világon: Az embereket, akik intoleránsak mások kultúrájával szemben, és a hollandokat. Tehát ha nincs szüksége gyógyszerre, kérem, hagyjon engem dolgozni.";
			link.l1 = "Kíváncsibb és kíváncsibb...";
			link.l1.go = "exit";
		break;

		case "Knippel":
			dialog.text = "Nocsak, nocsak... Maga Mynheer Rodenburgból való? Rendben, rendben. Hallgatlak.";
			link.l1 = "Meg kell szerveznem egy találkozót Fleetwood kapitánnyal egy félreesô helyen. Kölcsönvettem a 'Mirage' Jacob van Bergtôl, a holland magánhajóstól, akit Fleetwood úr annyira szeretne elfogni. Szeretném tájékoztatni ôt, hogy a 'Mirage' a közeljövôben kényelmesen kiköt Dominika partjainál. ";
			link.l1.go = "Knippel_1";
		break;
		
		case "Knippel_1":
			dialog.text = "Jákob odaadta neked a hajóját? Hm, szóval most már kell valaki, aki elmondja Mr. Fleetwoodnak, hogy a 'Mirage' hamarosan Dominika partjainál lesz, mivel Richardnak ezt maga nem mondhatja el bizonyos okokból...";
			link.l1 = "Pontosan. Mynheer Rodenburg azt javasolta, hogy forduljak önhöz ezzel az üggyel.";
			link.l1.go = "Knippel_2";
		break;
		
		case "Knippel_2":
			dialog.text = "Ebben az esetben Charlie Knippel a megfelelô ember. Fleetwood hûséges barátja... és kémje. Beszélj vele, és említsd meg neki mindazt, amit Richardnak tudni akarsz. Légy óvatos, Knippel lehet, hogy elég egyszerûnek tûnik, de nem bolond.\nEgy kis kunyhóban találod meg, nem messze a tengerparttól. Ott kell lennie.";
			link.l1 = "Értem. Köszönöm, Mr. Murdock. Viszontlátásra!";
			link.l1.go = "Knippel_3";
		break;
		
		case "Knippel_3":
			DialogExit();
			pchar.questTemp.HWIC.Holl = "toKnippel";
			AddQuestRecord("Holl_Gambit", "1-16");
			AddLandQuestMark(characterFromId("Knippel"), "questmarkmain");
		break;
		
		case "Merdok_fight":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешим драться
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			sld = characterFromId("Tonzag");
			PlaySound("Voice\English\hambit\Ercule Tongzag-04.wav");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			//а вот и китаец нарисовался
			sld = characterFromId("Longway");
			LAi_SetWarriorType(sld);
			FantomMakeCoolFighter(sld, 18, 40, 40, "blade_08", "pistol1", "bullet", 70);
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl.LongwayEnemy"))//враг
			{
				ChangeCharacterAddressGroup(sld, "SentJons_TownCave", "monsters", "monster8");
				LAi_group_MoveCharacter(sld, "EnemyFight");
				PlaySound("Voice\English\hambit\Longway-02.wav");
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl.LongwayFriend"))//друг
			{
				LAi_warrior_DialogEnable(sld, true);
				sld.Dialog.Filename = "Quest\HollandGambit\Longway.c";
				sld.dialog.currentnode = "Longway_hire";
				ChangeCharacterAddressGroup(sld, "SentJons_TownCave", "monsters", "monster8");
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				PlaySound("Voice\English\hambit\Longway-02.wav");
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl.LongwayNeutral")) sld.lifeday = 0;//нейтрал - просто нет
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "Merdok_AfterBattle");
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
//-------------------------------------------------за Англию-----------------------------------------------------
		case "Merdok_talk":
			dialog.text = "Tényleg? Azt hittem, hogy szegény Gaston már jó ideje a pokolban ég.";
			link.l1 = "Lehetséges, de Gastonhoz nem hasonlít senki. Megtaláltam a fejét egy öreg zsidó raktárában a titkos szigeten. De még így is sikerült üdvözletet küldenie neked. Azt is említette, hogy van egy közös ellenségünk: Mr. Rodenburg. Tonzag azt mondta, hogy önnek talán vannak Lucas számára fontos papírjai, amelyekkel elôcsalogathatja ôt curacaói rejtekhelyérôl.";
			link.l1.go = "Merdok_talk_1";			
		break;
		
		case "Merdok_talk_1":
			dialog.text = "Igaza volt. Az én archívumom miatt Rodenburgnak álmatlan éjszakái vannak. Úgy tûnik, hogy csak emiatt lóg még mindig a környéken. A helyzet az, hogy az Egyesült Tartományokban ígértek neki egy könnyû állást a Társaság igazgatói bizottságában. Ha az ebben az archívumban található információk, amelyek sok érdekes dolgot tartalmaznak Lucas múltjáról és jelenérôl, széles körben ismertté válnak, akkor a karrieraspirációi elszállnak. Ebben az esetben a legjobb, amiben reménykedhet, hogy akasztás helyett lefejezik.";
			link.l1 = "Add ide az archívumot, és én gondoskodom az ellenségünkrôl.";
			link.l1.go = "Merdok_talk_2";			
		break;
		
		case "Merdok_talk_2":
			dialog.text = "Biztos bolondnak tartasz. Csak azért vagyok még életben, mert még mindig nálam van. Honnan tudjam, hogy most nem Lucasnak dolgozol?";
			link.l1 = "El kell hinnie a szavamat - vagy meghal.";
			link.l1.go = "Merdok_talk_3";			
		break;
		
		case "Merdok_talk_3":
			PlaySound("Voice\English\hambit\John Mardock-07.wav");
			dialog.text = "Rossz válasz, itt és most meghalsz! Viszlát, gongji!";
			link.l1 = "Oh ho, a kínai megjelenik az árnyékból! Ne aggódjatok, mindkettôtökbôl csinálok chop suey-t!";
			link.l1.go = "Merdok_fightEng";			
		break;
		
		case "Merdok_fightEng":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешим драться
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");	
			sld = characterFromId("Longway");
			FantomMakeCoolFighter(sld, 20, 50, 50, "blade_08", "pistol1", "bullet", 80);
			LAi_SetWarriorType(sld);
			ChangeCharacterAddressGroup(sld, "SentJons_TownCave", "monsters", "monster8");
			PlaySound("Voice\English\hambit\Longway-02.wav");
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "Merdok_AfterBattleEng");
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
//----------------------------------------против всех-------------------------------------------------------
		case "MC_InHouse":
			PlaySound("Voice\English\hambit\John Mardock-02.wav");
			dialog.text = "Végre, újra talpra állsz. Már attól féltem, hogy nem fogsz felébredni.";
			link.l1 = "Mi a...? Ki vagy te? Hol a fenében vagyok? Hogy kerültem oda?";
			link.l1.go = "MC_InHouse_1";	
		break;
		
		case "MC_InHouse_1":
			dialog.text = "Nyugodj meg, ne kérdezz ennyit egyszerre, nem tesz jót neked, ha túlságosan izgatott vagy. A nevem John Murdock, gyógyszerész vagyok itt St. John's-ban. Ön elvesztette az eszméletét a Fleetwood embereivel folytatott harcban. Azt kell mondanom, hogy eléggé megverték önt... Hercule volt az, aki idehozta önt a patikámba, és, nos, a bájitalaimmal és gyógyszereimmel gyógyítottam meg a sebeit.";
			link.l1 = "Hercule? Kicsoda? A férfi, aki az utcán jött segíteni nekem? ";
			link.l1.go = "MC_InHouse_2";			
		break;
		
		case "MC_InHouse_2":
			dialog.text = "Igen. Ô az. Egyébként szeretne beszélni önnel. Találkoznia kell vele a városban. Tudsz még járni? Igen. Éjszaka indulj el - használd a titkos alagutat, ami a házam földszintjén lévô ajtó mögött kezdôdik. Sötétedés elôtt ne menj ki - Fleetwood emberei keresnek téged.";
			link.l1 = "Igenis... Hol van a hajóm?";
			link.l1.go = "MC_InHouse_3";			
		break;
		
		case "MC_InHouse_3":
			if (pchar.Ship.Type == SHIP_NOTUSED)
			{
				dialog.text = "A hajódat lefoglalták, és a legénységed szétszéledt, mert féltek, hogy Fleetwood emberei megölik ôket. Sajnálom, uram.";
				link.l1 = "Bassza meg...";
			}
			else
			{
				dialog.text = "A kikötôben van, a szokásos helyén.";
				link.l1 = "Fúú... ezt jó hallani. Azt hittem, elvesztettem.";
			}
			link.l1.go = "MC_InHouse_4";			
		break;
		
		case "MC_InHouse_4":
			dialog.text = "Találkoznod kéne Hercule-lal. Menj a városba éjszaka a titkos alagúton keresztül. Ô majd felkeres téged. Most pihenj egy kicsit, nekem pedig vissza kell térnem a munkámhoz.";
			link.l1 = "Rendben, John. És... köszönöm a segítséget és a gyógyítást!";
			link.l1.go = "MC_InHouse_5";
		break;
		
		case "MC_InHouse_5":
			NextDiag.CurrentNode = "First time";
			DialogExit();
			npchar.greeting = "merdok_2";
			AddQuestRecord("Holl_Gambit", "3-12");
			pchar.questTemp.HWIC.Self = "MainBegin";//новый флаг квеста
			sld = characterFromId("Bridgetown_tavernkeeper");
			sld.model = "barmen_3";
			sld.greeting = "barmen_1";
			sld.name = "Harry";
			sld.lastname = "Fletcher";//перерисуем бармена Бриджтауна
			LocatorReloadEnterDisable("SentJons_HouseF3", "reload1", true);//закрыть выход из аптеки через дверь
			LocatorReloadEnterDisable("SentJons_HouseF3", "reload2", false);//открыть подземелье из дома
			LocatorReloadEnterDisable("SentJons_TownCave", "reload1_back", false);//открыть дом из подземелья
			pchar.quest.Tonzag_Meeting.win_condition.l1 = "location";
			pchar.quest.Tonzag_Meeting.win_condition.l1.location = "SentJons_town";
			pchar.quest.Tonzag_Meeting.win_condition.l2 = "Night";
			pchar.quest.Tonzag_Meeting.function = "TonzagMeeting";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "SentJons_HouseF3", "goto", "goto1", "MC_TakeCloves", -1);	
		break;
		
		case "About_Fleetwood":
			DelLandQuestMark(npchar);
			dialog.text = "Fleetwood? Mit akarsz tudni róla?";
			link.l1 = "Mindenrôl. Mondj el mindent, amit tudsz. Úgy látom, nem titok ön elôtt, hogy Hercule miért jött Antiguára. Az ô oldalán állok.";
			link.l1.go = "About_Fleetwood_1";
		break;
		
		case "About_Fleetwood_1":
			dialog.text = "Nagyon jó. Richard Fleetwood kapitány a Királyi... úgy értem, a Nemzetközösségi Haditengerészetnél... a fenébe is, folyton elfelejtem, hogy az a fanatikus Cromwell a fônök, és megváltoztatta a nevet. Ettôl függetlenül Fleetwood jó harcos és tapasztalt tengerész. Egy briggnek, a 'Valkyrie' nevû briggnek a parancsnoka - egy kiváló hajó, megemlíteném, elit tengerészekbôl és tengerészgyalogosokból álló legénységgel. Magánháborút folytat az Egyesült Tartományok ellen általában és a Holland Nyugat-indiai Társaság ellen különösen. Számtalan holland kereskedelmi hajót kifosztott, és az egekbe szöktette a biztosítási költségeket. Curacao kormányzója rekordot döntô vérdíjat tûzött ki a fejére.";
			link.l1 = "Hmm... Kicsit szokatlannak tûnik, hogy a 'Commonwealth Navy' tisztje kalózkodni menjen...";
			link.l1.go = "About_Fleetwood_2";
		break;
		
		case "About_Fleetwood_2":
			dialog.text = "Igen, valóban. Kényes kötélen jár. Az angolok hivatalosan nem ismerik el a tetteit, és nem hajlandók semmi közük hozzá, de a színfalak mögött valójában bátorítják ôt. Okom van feltételezni, hogy valahogy kapcsolatban áll az angol kémhálózattal a Karib-tengeren, és azokkal a gazemberekkel nem lehet packázni.";
			link.l1 = "Egy komoly ember... Ez minden? Hercule mesélt nekem az egyik segédjérôl... egy másik Charlie... mi is a neve... Canister? Cannonball?";
			link.l1.go = "About_Fleetwood_3";
		break;
		
		case "About_Fleetwood_3":
			dialog.text = "Knippel? Igen, van egy ilyen fickó. Charlie Knippel az angol haditengerészet tüzérmestere volt, most nyugdíjas.  Most nyugodt életet él a parton. Ô Fleetwood szeme és füle St. John's-ban, úgyhogy vigyázz vele, és eszedbe se jusson kérdôre vonni Richardról - börtönben vagy még rosszabbul jársz.";
			link.l1 = "Értem. Tudsz még valami említésre méltót mondani Fleetwoodról?";
			link.l1.go = "About_Fleetwood_4";
		break;
		
		case "About_Fleetwood_4":
			dialog.text = "Bálvány minden antiguai nônek tizenhat és hatvan között. Úgy tûnik, ez minden róla. Nos, azt hiszem, most már tudja, mi történt vele. Az ágyban marad és nyalogatja a sebeit.";
			link.l1 = "Biztos van néhány gyenge pontja vagy bûne...";
			link.l1.go = "About_Fleetwood_5";
		break;
		
		case "About_Fleetwood_5":
			dialog.text = "Hogy érti ezt?";
			link.l1 = "Hát, talán szeret szerencsejátékozni, vagy sokat iszik, vagy nem tud ellenállni a szebbik nemnek - valami ilyesmi. Házas?";
			link.l1.go = "About_Fleetwood_6";
		break;
		
		case "About_Fleetwood_6":
			dialog.text = "Nem, agglegény. Ami az ön által említett dolgokat illeti - egyikrôl sem ismert.";
			link.l1 = "Értem. De talán mégis van benne valami különleges? Még egy ilyen embernek is kell, hogy legyenek gyenge pontjai!";
			link.l1.go = "About_Fleetwood_7";
		break;
		
		case "About_Fleetwood_7":
			dialog.text = "Nem is tudom. Figyelj, csináljuk így. Jöjjön el hozzám egy hét múlva, és én kivizsgálom Fleetwood magánéletét. Megegyeztünk?";
			link.l1 = "Megegyeztünk. Köszönöm, John! Egy hét múlva itt leszek.";
			link.l1.go = "About_Fleetwood_8";
		break;
		
		case "About_Fleetwood_8":
			DialogExit();
			pchar.questTemp.HWIC.Self = "WaitFleetwood";
			SaveCurrentQuestDateParam("questTemp.Wait_Fleetwood");
			SetFunctionTimerCondition("Wait_FleetwoodQM", 0, 0, 7, false);
			SetFunctionTimerCondition("Wait_FleetwoodOver", 0, 0, 12, false);//чтобы не опаздывал
			LocatorReloadEnterDisable("SentJons_HouseF3", "reload1", false);//открыть выход из аптеки
			AddQuestRecord("Holl_Gambit", "3-14");
		break;
		
		case "About_Fleetwood_9":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("SentJons");
			dialog.text = "Igen, de sajnos nem sokat. És attól tartok, nem sok hasznát veszem.";
			link.l1 = "Köpd ki! Minden apró részlet nagyon fontos, ha valami köze van Fleetwoodhoz.";
			link.l1.go = "About_Fleetwood_10";
		break;
		
		case "About_Fleetwood_10":
			dialog.text = "Nem is olyan régen Richard felvett két zsidó menekültet egy ismeretlen szigetrôl - egy öregembert és a lányát, akik Willemstadba hajóznak. A hajót, amelyen utaztak, kalózok süllyesztették el. Fleetwood titokban, a saját nyakát kockáztatva hozta ôket Curacaóba. Azóta eltelt néhány hónap. Most hûséges kutyáját, Charlie Knippelt küldte Willemstadba...";
			link.l1 = "Hmm... Hogyan kapcsolódik ez össze?";
			link.l1.go = "About_Fleetwood_11";
		break;
		
		case "About_Fleetwood_11":
			dialog.text = "Sikerült megtudnom, hogy Charlie parancsot kapott, hogy szállítson ide egy lányt Willemstadból, egy Abigail Shneur nevû zsidó lányt. Igen, ugyanaz a lány a szigetrôl. Úgy tûnik, Richard beleszeretett, hiszen a legjobb ügynökét küldi érte.\nEz az. Nem tudom, hogy segít-e egyáltalán.";
			link.l1 = "Oh ho ho! Hahaha! Úgy tûnik, a mi megrögzött agglegényünk bedôlt a zsidónô' ravasz bájainak. Ez kiváló munka, John, köszönöm! Most mikor indul Knippel barátunk Curacaóra?";
			link.l1.go = "About_Fleetwood_12";
		break;
		
		case "About_Fleetwood_12":
			dialog.text = "Tegnap indult el.";
			link.l1 = "És melyik hajóval?";
			link.l1.go = "About_Fleetwood_13";
		break;
		
		case "About_Fleetwood_13":
			dialog.text = "Tudtam, hogy ezt fogod kérdezni. Egy brigantinon van, amelyet a Commonwealth - ó, a pokolba is, a 'Királyi Haditengerészet'. nevén 'Zeekalf'.- rendelt.";
			link.l1 = "'Zeekalf'? Ez egy hatalmas holland név egy angol hajónak...ohhh értem.";
			link.l1.go = "About_Fleetwood_14";
		break;
		
		case "About_Fleetwood_14":
			dialog.text = "Gyorsan gondolkodik... Korábbi neve 'Royal Mary', volt, de erre az útra a 'Zeekalf'. nevet kapta, és holland zászló alatt hajózik.";
			link.l1 = "A segítséged felbecsülhetetlen volt, John. Most indulok. Hamarosan visszajövök, és szükségem lesz a szobájára a második emeleten, ahol maga szállt meg, amíg felépültem.";
			link.l1.go = "About_Fleetwood_15";
		break;
		
		case "About_Fleetwood_15":
			dialog.text = "Mire készülsz?";
			link.l1 = "Mindent elmondok, ha visszajöttem. Kívánj szerencsét, John! Viszontlátásra.";
			link.l1.go = "About_Fleetwood_16";
		break;
		
		case "About_Fleetwood_16":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "3-16");
			pchar.questTemp.HWIC.Self = "HuntKnippel";
			if(bImCasual) NewGameTip("Felfedezô mód: az idôzítô nincs kikapcsolva. Tartsd be a határidôt!");
			SetFunctionTimerCondition("HuntKnippelOver", 0, 0, 10, false);
			pchar.quest.Hunt_Knippel.win_condition.l1 = "location";
			pchar.quest.Hunt_Knippel.win_condition.l1.location = "Curacao";
			pchar.quest.Hunt_Knippel.function = "CreateKnippelShip";
			LocatorReloadEnterDisable("SentJons_town", "houseH1", true);//закрыть хижину Чарли
			AddMapQuestMarkIsland("Curacao", true);
		break;
		
		case "About_Fleetwood_17":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "3-15");
			pchar.questTemp.HWIC.Self = "end";
			pchar.questTemp.HWIC.Detector = "self_fail";
			CloseQuestHeader("Holl_Gambit");
		break;
		
		case "Abigile":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("SentJons");
			dialog.text = "Tényleg? Miért vagy ilyen biztos benne?";
			link.l1 = "Mert Charlie a tengerfenéken van, és eteti a halakat. Felszálltam 'Zeekalf' és elküldtem Knippelt a pokolba. Persze elôtte kikérdeztem ôt... Volt nála egy levél, ami lehetôvé tette, hogy Knippelnek adjam ki magam, amikor Abigail zsidónôvel, bátor Richárdunk kedvesével beszéltem.";
			link.l1.go = "Abigile_1";
		break;
		
		case "Abigile_1":
			dialog.text = "Hmm... Ez okos dolog. Szóval azt mondod, hogy...";
			link.l1 = "Igen. Elhoztam a zsidónôt Antiguára. A hajóm fedélzetén van. Most már van egy adu ászom a Fleetwooddal való kártyapartiban! Bármit megtenne érte...";
			link.l1.go = "Abigile_2";
		break;
		
		case "Abigile_2":
			dialog.text = "Biztos benne? Lehet, hogy nem minden olyan egyszerû, mint amilyennek gondolja...";
			link.l1 = "Ó igen, teljesen biztos vagyok benne. A levélbôl rájöttem, hogy Abigail apja a pénz miatt ellenezte a házasságát Richarddal. Tudom, tipikus zsidó após. Így Fleetwood úgy döntött, hogy hozományt fizet az apjának - 200000 pesót! Mondja csak, hány lány ér ennyi pénzt a világon?";
			link.l1.go = "Abigile_3";
		break;
		
		case "Abigile_3":
			dialog.text = "Heh! Biztosan nem egy zsidó nô! Én még életemben nem találkoztam olyan keresztény lánnyal, aki megérte volna, az biztos. " + pchar.name + ", te egy ravasz gazember vagy. Mit fogsz csinálni vele?";
			link.l1 = "Idehozom a zsidó lányt, és a szobádban tartjuk. Azt mondom neki, hogy Richárd elment a tengerre, és még nem tért vissza, így egy hétig a vendégünk lesz. Azt hiszi, hogy én vagyok Charlie Knippel.";
			link.l1.go = "Abigile_4";
		break;
		
		case "Abigile_4":
			dialog.text = "Ez érdekes. Szóval úgy döntöttél, hogy a lányt a házamban tartod? Hmm...";
			link.l1 = "John, ô zsidó. Egy hontalan vándor, akit egy holland gyarmatról hoztak ide. Itt St. John's-ban egy senki, és senki sem ismeri. Nyugodt lehetsz, azt tehetünk, amit akarunk, és ô nem mer majd szólni egy szót sem. Egy fillérje sincs, és egy barátja sincs. És különben sem lesz sokáig a vendégünk. Fleetwoodot vele csalinak fogom kicsalogatni, és azután már nem lesz rá szükség.";
			link.l1.go = "Abigile_5";
		break;
		
		case "Abigile_5":
			dialog.text = "Kezdesz megijeszteni, Charles. Ugye nem fogod kihasználni ezt a lányt? Vagy ugyanarra a végzetre juttatod, mint Knippelt?";
			link.l1 = "Nem, persze, hogy nem. 'Csaló gazember' lehet, de nem vagyok a szép lányok ellensége - sem zsidó, sem keresztény. Vagy a csúnyákkal, ha már itt tartunk. Ha jól viselkedik, elviszem az apjához Willemstadba, miután ennek az egésznek vége. Az öreg zsugori valószínûleg a térdemre borul majd, és megköszöni, hogy megmentettem ôt attól az alattomos angoltól.";
			link.l1.go = "Abigile_6";
			// belamour legendary edition -->
			link.l2 = "Neki is szerepe van ebben a mumifikálásban. Ha a darabnak vége, már nem lesz rá szükségem.";
			link.l2.go = "Abigile_6a";
		break;
		
		case "Abigile_6a":
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			AddCharacterExpToSkill(pchar, "Sneak", 60);
			dialog.text = "Értem, úgyhogy egyelôre nekem kell vigyáznom rá.";
			link.l1 = "Nem ragaszkodom hozzá, pajtás. Ha teljesen ellenzed, akkor maradhat a hajóm fedélzetén. De akkor a biztonság kedvéért be kell vasalnom, és a raktérben kell tartanom a patkányokkal, hogy megvédjem a legénységemtôl. Tudja, újdonság számukra, hogy nôk vannak a fedélzeten. Szégyen lenne így bánni egy ilyen kedves lánnyal.";
			link.l1.go = "Abigile_7";
		break;
		
		case "Abigile_6":
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			AddCharacterExpToSkill(pchar, "Leadership", 60);
			// <-- legendary edition
			dialog.text = "Értem, úgyhogy egyelôre nekem kell vigyáznom rá.";
			link.l1 = "Nem ragaszkodom hozzá, pajtás. Ha teljesen ellenzed, akkor maradhat a hajóm fedélzetén. De akkor a biztonság kedvéért be kell vasalnom, és a raktérben kell tartanom a patkányokkal, hogy megvédjem a legénységemtôl. Tudja, újdonság számukra, hogy nôk vannak a fedélzeten. Szégyen lenne így bánni egy ilyen kedves lánnyal.";
			link.l1.go = "Abigile_7";
		break;
		
		case "Abigile_7":
			dialog.text = "Értem. Rendben, hozza ide. Kötelességem, hogy segítsek a Fleetwood elleni harcban. Hozd ide, és én elôkészítem ôt 'vendégszobába'..";
			link.l1 = "Köszönöm, John. Tudtam, hogy számíthatok rád.";
			link.l1.go = "exit";
			pchar.questTemp.HWIC.Self = "AbigileInCabin";
			DoQuestCheckDelay("SetAbigileToCabin", 1.0); // fix 180812
			AddQuestRecord("Holl_Gambit", "3-24");
			//поставим табурет
			sld = ItemsFromID("lcheer");
			sld.shown = true;
			sld.startLocation = "SentJons_HouseF3";
			sld.startLocator = "goto2";
			AddLandQuestMark(characterFromId("Abigile"), "questmarkmain");
		break;
		
		case "Abigile_7_1":
			DelLandQuestMark(npchar);
			dialog.text = "Ó! Örömömre szolgál. Örömmel üdvözlök egy ilyen fontos és... elegáns hölgyet. Kisasszony, felmenne a második emeletre, kérem? A vacsora várja önt, és az ágy be van vetve. Biztos vagyok benne, hogy egy ilyen hosszú utazás után jól akar majd aludni.";
			link.l1 = "Igen, igen, igen. Abigail biztosan fáradt a hosszú utazás után Willemstadból.";
			link.l1.go = "Abigile_8";
		break;
		
		case "Abigile_8":
			DialogExit();
			sld = characterFromId("Abigile");
			sld.dialog.currentnode = "Abigile_kidnapping_11";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Abigile_9":
			dialog.text = "Van már valami terved?";
			link.l1 = "Igen, van. Írnunk kell egy levelet Richardnak, amelyben váltságdíjat követelünk Abigailért. Szervezzünk találkozót valahol egy lakatlan szigeten - például a törököknél. És ha nem engedelmeskedik, akkor, hogy is mondjam, darabokban küldjük el neki a héber kedvesét.";
			link.l1.go = "Abigile_10";
		break;
		
		case "Abigile_10":
			dialog.text = "Minek ilyen bonyodalmak egy lakatlan szigeten?";
			link.l1 = "Semleges talaj. Az biztonságosabb. Abigailt amúgy sem fogom magammal hozni. Fleetwoodra van szükségem. Antiguán bizonyára csapdát készít elô, de Turkson nem lesz ilyen elônye.";
			link.l1.go = "Abigile_11";
		break;
		
		case "Abigile_11":
			dialog.text = "Ez így is van rendjén. Ki fogja átadni a levelet? Nagyon veszélyes.";
			link.l1 = "Egy idegen. Válassz egy részeget a kocsmából, aki megbízhatónak tûnik. Hajlandóak bármit megtenni, amit kérsz tôlük némi rumos pénzért. Ha Richárd dührohamában megöli, küldünk egy másikat. És Abi egyik ujját is mellékeljük a levélhez. Ettôl sokkal engedékenyebb lesz.";
			link.l1.go = "Abigile_12";
		break;
		
		case "Abigile_12":
			dialog.text = "" + pchar.name + "...";
			link.l1 = "Ne aggódj, John. Biztos vagyok benne, hogy nem fog idáig fajulni a dolog. Csak találnia kell egy futárt, és én azonnal megírom a levelet. Van papírja és tintája?";
			link.l1.go = "Abigile_13";
		break;
		
		case "Abigile_13":
			dialog.text = "Igen, van. És történetesen ismerek egy megfelelô részegest is. Jack Harrisont ajánlom. Minden estéjét a kocsmában tölti, rummal feltankolva. Könnyen megtalálja.";
			link.l1 = "Jó, hozzon tollat és tintát, és megírom a váltságdíjat Richardnak.";
			link.l1.go = "Abigile_14";
		break;
		
		case "Abigile_14":
			DialogExit();
			StartQuestMovie(true, false, true);
			locCameraFromToPos(0.07, 2.57, -2.46, true, -0.08, -0.38, 1.35);
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "goto", "goto2", "MC_writeLetter", -1);
		break;
		
		case "Abigile_15":
			dialog.text = "Mikor adod át neki a levelet? Figyelni fogod a kézbesítést?";
			link.l1 = "Persze, persze. Richard nem bolond, de kétlem, hogy kockáztatna. Legalábbis remélem. Nem akarom bántani a lányt, de ha kell, megteszem. Nos, itt az ideje, hogy megkeressük a részegest, akit említettél. Jack... mi is volt a teljes neve?";
			link.l1.go = "Abigile_20";
		break;
		
		case "Abigile_20":
			dialog.text = "A neve Jack Harrison. Általában esténként szokott a kocsmába járni. Légy óvatos!";
			link.l1 = "Minden rendben lesz. Várjatok meg.";
			link.l1.go = "Abigile_22";
		break;
		
		case "Abigile_22":
			DialogExit();
			LAi_SetOwnerType(npchar);
			pchar.questTemp.HWIC.Self = "LetterToDrunkardGo";
			AddDialogExitQuestFunction("CreateDrunckardInTavern");
			AddQuestRecord("Holl_Gambit", "3-25");
		break;
		
		case "Abigile_23":
			DelLandQuestMark(npchar);
			dialog.text = "Hát, én nem mondanám. Fleetwood ravasz és veszélyes. Ráadásul mesteri kardforgató és tapasztalt tengerész. Nem lesz könnyû préda.";
			link.l1 = "Én már nem vettem a könnyebb utat, amikor a Karib-tengerre jöttem. Nos, John, itt az ideje, hogy elmenjek. Egyébként említetted, hogy a mi bátor Fleetwoodunknak jó hajója van, ugye?";
			link.l1.go = "Abigile_24";
		break;
		
		case "Abigile_24":
			dialog.text = "A legszebb briggje van, amit valaha láttam. És én már láttam jó néhányat.";
			link.l1 = "Az jó. Szeretem a szép hajókat. Ideje horgonyt vetni!";
			link.l1.go = "Abigile_26";
		break;
		
		case "Abigile_26":
			DialogExit();
			pchar.questTemp.HWIC.Self = "FleetwoodToIsland";
			pchar.quest.Fleetwood_meetingShore.win_condition.l1 = "location";
			pchar.quest.Fleetwood_meetingShore.win_condition.l1.location = "Shore56";
			pchar.quest.Fleetwood_meetingShore.function = "InTerksShore";
			AddQuestRecord("Holl_Gambit", "3-28");
			AddMapQuestMarkShore("Shore57", false);
		break;
		
		case "Abigile_27":
			int iVal = 0;
			for(i = 0; i < COMPANION_MAX; i++)
			{
				iTemp = GetCompanionIndex(PChar, i);
				if(iTemp > 0)
				{
				sld = GetCharacter(iTemp);
				if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_VALCIRIA) iVal = 1;
				}
			}//установили признак наличия Валькирии в эскадре.
			if (iVal != 0)
			{
				dialog.text = "Elakadt a szavam! Kiváló kombináció, nagyszerû ötlet és mesteri megvalósítás! Gratulálok, " + pchar.name + "! És a briggjét is sikerült elhoznod nyereményként!";
				link.l1 = "Köszönöm! És hol van Hercule? Szeretném látni ôt. Amikor utoljára találkoztunk, azt mondta, hogy a maga segítségével megtalálom.";
				link.l1.go = "Abigile_28";
			}
			else
			{
				dialog.text = "Kiváló kombináció, nagyszerû ötlet és mesteri megvalósítás! Gratulálok, " + pchar.name + "!";
				link.l1 = "Köszönöm! És hol van Hercule? Szeretném látni ôt. Amikor utoljára találkoztunk, azt mondta, hogy a maga segítségével megtalálom.";
				link.l1.go = "Abigile_28";
			}
		break;
		
		case "Abigile_28":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("SentJons");
			dialog.text = "Bármelyik pillanatban várhatom ôt. A titkos alagúton keresztül kell idejönnie. Te pedig magyarázkodj Abigailnek. Aggódni kezdett Richard távolléte miatt.";
			link.l1 = "Rendben, de nem kéne hazaküldenünk?";
			link.l1.go = "Abigile_29";
		break;
		
		case "Abigile_29":
			dialog.text = "Még nem... Elôbb beszélnem kell veled. De elôbb várd meg Hercule érkezését. Menj és vigasztald Abigailt. Mondj neki egy történetet, találj ki valamit. Aztán gyere az alagsorba. Rendben?";
			link.l1 = "Igenis, John.";
			link.l1.go = "Abigile_30";
		break;
		
		case "Abigile_30":
			DialogExit();
			npchar.greeting = "merdok_4";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "SentJons_TownCave", "item", "berglar1", "", -1);
			pchar.questTemp.HWIC.Self = "AbigileLie";
			sld = characterFromId("Abigile");
			LAi_SetCitizenType(sld);
			AddLandQuestMark(sld, "questmarkmain");
			AddQuestRecord("Holl_Gambit", "3-34");
		break;
		
		case "Lucas":
			DelLandQuestMark(npchar);
			dialog.text = "Nos, eljött az idô, hogy kiterítsük a kártyákat. Ahogy már rájött, én nem csak egy egyszerû gyógyszerész vagyok. Az igazi nevem Johan van Merden, és egészen a közelmúltig a Holland Nyugat-indiai Társaság ügynöke és Lucas Rodenburg alelnök jobbkeze voltam.";
			link.l1 = "Tényleg! Ez érdekes...";
			link.l1.go = "Lucas_1";
		break;
		
		case "Lucas_1":
			dialog.text = "Most már más a helyzet. Lucas ki akar szállni a játékból, és vissza akar térni Hollandiába, ezért el kell temetnie mindent és mindenkit, aki a múltjához kapcsolódik\nAzt hiszem, hogy csak az archívumom miatt lélegzem még mindig, amely minden információt tartalmaz Lucas bûneirôl... mint például a 'szellemhajó' történetét, amely csak egy közönséges kalózhajó, a vakmerô és elvtelen söpredék Jacob van Berg parancsnoksága alatt. Rodenburg bérelte fel a férfit, hogy angol kereskedelmi hajókat fosztogasson és süllyesszen el\nVan Berg a felelôs a Fluyt elsüllyesztéséért is, amelynek fedélzetén Abigail és az apja tartózkodott. Abigail fontos figura ebben a játékban, Rodenburg is a kezét és a szívét akarta, ahogy Fleetwood is, ezért eléggé meglepett, amikor idehozta...";
			link.l1 = "Rodenburg... ez az a vej, akirôl Abigail különc apja beszélt!";
			link.l1.go = "Lucas_2";
		break;
		
		case "Lucas_2":
			dialog.text = "Igen, ezért szeretném, ha egy ideig itt maradna. Ô lehet az utolsó ászom a Rodenburg elleni játékban, bár nem szeretném tovább használni, jó kislány, nem akarom, hogy szenvedjen. Úgy gondolom, hogy Lucas az én archívumomat választaná helyette, ha a választás elé kerülne.\nSzóval, azt javaslom, hogy legyél a szövetségesem a Lucas elleni játékban... szabadulj meg tôle, minden szükséges eszközzel. A jutalom jelentôs lesz.";
			link.l1 = "Hmm... Nem hiszem, hogy nehezebb lenne, mint Fleetwooddal. ";
			link.l1.go = "Lucas_3";
		break;
		
		case "Lucas_3":
			dialog.text = "Nem, tévedsz. Végül is Fleetwood magányos farkas volt, aki egyedül cselekedett. Rodenburg a cég alelnöke. Nagyon befolyásos ember, csak Curacao kormányzójának van nagyobb hatalma. Jacob van Berg az ügynöke, egy nagyon veszélyes ember. Lucas a seggén ül Willemstadban a Cég gárdistáinak védelme alatt, ôk is olyan jók, mint Fleetwood emberei.\nEz nem lesz könnyû.";
			link.l1 = "A játékszabályok ugyanazok - kicsalogatni a tigrist a barlangjából... Már van egy tervem. Mit tudsz még mondani Lucasról?";
			link.l1.go = "Lucas_4";
		break;
		
		case "Lucas_4":
			dialog.text = "Nos, már majdnem mindent elmondtam. Van egy gyors hajója, a 'Meifeng' - Beautiful Wind. A kapitánya egy Longway nevû kínai - Rodenburg esküdt embere. Ô is olyan ellenség, akivel nem szívesen nézne szembe. Lucas' legénységében nincsenek amatôrök. ";
			link.l1 = "Már a kezdetektôl fogva volt egy aduászunk - az archívumod. Ha neki fontosabb az élete, mint a zsidónôé, akkor bármit meg fog tenni, hogy az archívumban lévô információkat titokban tartsa... De... az archívum tényleg létezik, John? Csak blöffölsz?";
			link.l1.go = "Lucas_5";
		break;
		
		case "Lucas_5":
			dialog.text = "Az archívum létezik. És Lucas tud róla. Találtál már valamit?";
			link.l1 = "Igen, találtam. John, ha tényleg a cég ügynöke voltál, akkor tudnod kellene valamit.";
			link.l1.go = "Lucas_6";
		break;
		
		case "Lucas_6":
			dialog.text = "Pontosan mit? Kérdezz engem.";
			link.l1 = "El kell kapnom a cég egyik hajóját. Lehetôleg egy kíséret nélküli hajót - egy futárt vagy valami ilyesmit. Tudsz mondani valamit ezzel kapcsolatban?";
			link.l1.go = "Lucas_7";
		break;
		
		case "Lucas_7":
			dialog.text = "Hm... Nem rendelkezem ilyen információval. Várjon! Biztosan tudom, hogy a Társaságnak havonta egyszer van egy teherhajója a Philipsburg és Willemstad közötti tengerparton. Üzleti papírokat szállít. Ez egy brigantine, a neve 'Hoop'.\nMég ma vagy holnap elhagyja Philipsburgot.";
			link.l1 = "Igen, ez az! Minden, amire szükségem lesz, hogy Szent Kristóf partjaira menjek. A Curacaóba vezetô tengeri út pont itt halad el.";
			link.l1.go = "Lucas_8";
		break;
		
		case "Lucas_8":
			dialog.text = "Sok szerencsét, " + pchar.name + ". Nem kérdezem a terved részleteit. Várni fogom a visszatérésedet!";
			link.l1 = "Minden rendben lesz, John. Vigyázz a zsidónôre, és bánj vele jól!";
			link.l1.go = "Lucas_9";
		break;
		
		case "Lucas_9":
			DialogExit();
			RemoveItems(PChar, "MC_Letter", 1);
			GiveItem2Character(pchar, "MC_Letter");
			ChangeItemDescribe("MC_Letter", "itmdescr_MC_Letter2");
			AddQuestRecordInfo("LetterToLucas", "1");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "SentJons_HouseF3", "goto", "goto1", "MC_TakeCloves", -1);
			pchar.questTemp.HWIC.Self = "LetterToLucas";
			sld = characterFromId("Tonzag");
			sld.dialog.currentnode = "Tonzag_hired";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			AddQuestRecord("Holl_Gambit", "3-36");
			//установим таймер на генерацию энкаунтера
			pchar.quest.HWIC_Cureer.win_condition.l1 = "Timer";
			pchar.quest.HWIC_Cureer.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.HWIC_Cureer.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.HWIC_Cureer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.HWIC_Cureer.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.HWIC_Cureer.function = "CreateHWICCureerOnMap";
			if(bImCasual) NewGameTip("Felfedezô mód: az idôzítô nincs kikapcsolva. Tartsd be a határidôt!");
			SetFunctionTimerCondition("HWICCureerOnMapOver", 0, 0, 16, false);//таймер
		break;
		
		case "Lucas_10":
			dialog.text = "Hihetetlen! Nem hiszek a fülemnek! Hogy történhetett ez?";
			link.l1 = "Elfoglaltam a csomaghajót, és Fleetwood nevében levelet küldtem Lucasnak, amelyben közöltem, hogy birtokomba vettem egy bizonyos irattárat, amely egy szentendrei drogista tulajdona, és hogy hamarosan minden gaztettének bizonyítéka ismert lesz innen Amszterdamig és Londonig. Arra számítottam, hogy vadászni kezd rám, de fordítva történt.";
			link.l1.go = "Lucas_11";
		break;
		
		case "Lucas_11":
			dialog.text = "";
			link.l1 = "Lucas megvádolta Matthias Becket árulással és az angolokkal való üzelmekkel, rács mögé dugta, és a kormányzói palotában foglalt helyet. Valószínûleg likvidálta a brigantin kapitányát. Ezután utasította a Meifeng hûséges kínaiját, hogy süllyessze el a hajót a Társaság igazgatójával, Peter Stuyvesant-tal a fedélzeten!";
			link.l1.go = "Lucas_12";
		break;
		
		case "Lucas_12":
			dialog.text = "Rodenburg könyörtelen ember. De még én sem gondoltam volna, hogy ilyen messzire képes elmenni...";
			link.l1 = "Elfogtam a Meifenget, és kihallgattam Longwayt. Mindent elmondott. Megtaláltam Stuyvesantot, figyelmeztettem Rodenburg szándékairól, és együtt elhajóztunk Willemstadba. Stuyvesant szabadon engedte Becket, és letartóztatta Lucast. Most börtönben van.";
			link.l1.go = "Lucas_13";
		break;
		
		case "Lucas_13":
			dialog.text = "Heh! Igazi tehetséged van, barátom... Karriert kellene csinálnia a Társaság haditengerészeténél vagy politikusként az Egyesült Tartományokban - minden esélye megvan arra, hogy kormányzó legyen! És mit tettél Longway-vel?";
			link.l1 = "Elengedtem. Becsületesen megadta magát, így nem ártottam neki.";
			link.l1.go = "Lucas_14";
		break;
		
		case "Lucas_14":
			dialog.text = "Ez jó. Longway jó ember, nem úgy, mint a korábbi fônöke. Nos, " + pchar.name + ", nagyszerû munkát végeztél! Elôkészítem a jutalmadat, de szükségem lesz egy kis idôre... Addig is...";
			link.l1 = "John, az igazat megvallva, van egy légy a dologban. Longway és Rodenburg is azt mondta, hogy Jacob van Berg vadászik rám. Mennyire rossz ez?";
			link.l1.go = "Lucas_15";
		break;
		
		case "Lucas_15":
			dialog.text = "Jacob van Berg? Charlie, ez komoly. Ô egy könyörtelen kalóz, egy ügyes tengerész és harcos, aki mellett Fleetwood csak egy cicababának tûnik. Egy profi vadász. Ô volt az, aki Rodenburg parancsára elpusztította a hajózást.\nÔ meg fog találni téged, úgyhogy fel kell készülnöd. Magamnak is elôvigyázatosnak kell lennem.";
			link.l1 = "Hogy találom meg ezt a van Berget?";
			link.l1.go = "Lucas_16";
		break;
		
		case "Lucas_16":
			dialog.text = "Nem tudom. Lucas és Longway voltak az egyetlenek, akik tudták, hol találják. Szóval csak óvatosan és készenlétben\nzárom a helyet. Menjetek át a titkos alagúton, ha látni akartok. És vigyétek el a zsidónôt, túl veszélyes itt maradnia.";
			link.l1 = "Ne aggódj, John. Hagyd, hogy megjelenjen, majd én elintézem. Hol van Abigail?";
			link.l1.go = "Lucas_17";
		break;
		
		case "Lucas_17":
			dialog.text = "Elment a templomba. Sajnálom ôt. Mostanában nagyon zaklatott volt.";
			link.l1 = "Nos... ez kellemes meglepetés. Talán rájött, hogy Krisztus a Messiás, akit a népe régóta várt. Nos, itt az ideje, hogy visszavigyük az apjához.";
			link.l1.go = "Lucas_18";
		break;
		
		case "Lucas_18":
			dialog.text = "Látni akart téged. Biztos vagyok benne, hogy meg fog kérni, hogy vigyétek haza.";
			link.l1 = "Abi, mi?";
			link.l1.go = "Lucas_19";
		break;
		
		case "Lucas_19":
			dialog.text = "Nos, be kell vallanom, hogy barátok lettünk. Nem bánom, hogy nálam lakik, és hála Istennek soha nem fogja megtudni, hogy miért hozták ide.";
			link.l1 = "Rendben, John, elmegyek a templomba, hogy találkozzam Abigail-lel. Aztán Willemstadba megyek.";
			link.l1.go = "Lucas_20";
		break;
		
		case "Lucas_20":
			DialogExit();
			sld = characterFromId("Abigile");
			AddLandQuestMark(sld, "questmarkmain");
			ChangeCharacterAddressGroup(sld, "SentJons_church", "goto", "goto1");//Аби - в церковь
			AddQuestRecord("Holl_Gambit", "3-56");
			pchar.questTemp.HWIC.Self = "AbiReturnHome";
			LocatorReloadEnterDisable("SentJons_town", "HouseF3", true);//закрыть аптеку
		break;
		
		case "Final":
			dialog.text = "Te... feltörted a mogyoróit? Ó - egy metafora. Nos, akár van mogyoró, akár nincs, megcsináltad! Gratulálok!";
			link.l1 = "Nem hazudnék neked, heh. Most már fellélegezhetsz, John.";
			link.l1.go = "Final_1";
		break;
		
		case "Final_1":
			dialog.text = "Végre! Azt hiszem, jobb, ha felhagysz ezekkel a politikai játszmákkal és intrikákkal. Most itt az ideje, hogy beszéljünk a munkádért járó jutalmadról.";
			link.l1 = "Hát, azt nagyon értékelném.";
			link.l1.go = "Final_2";
		break;
		
		case "Final_2":
			dialog.text = "Örökre elhagyom a Karib-térséget. Köszönetképpen a segítségedért és azért, hogy megmentettél Rodenburgtól, neked adom a ház és a patikám tulajdonjogát. Mostantól mind a tiéd. Vegye el a kulcsokat.";
			link.l1 = "Ez nagyszerû! Nagyon boldog vagyok. Van egy nagyon kényelmes háza és egy hangulatos pincéje...";
			link.l1.go = "Final_3";
		break;
		
		case "Final_3":
			GiveItem2Character(pchar, "Drugstore_keys");//ключ
			dialog.text = "És kérlek, fogadd el ezt a szerény 100 000 pezó összeget és ezt a muskétát. Egykor hûségesen szolgált engem, és téged is jól fog szolgálni.";
			link.l1 = "Nem utasítom vissza az ilyen ajándékokat!";
			link.l1.go = "Final_4";
			LocatorReloadEnterDisable("SentJons_town", "HouseF3", false);//открыть аптеку
			LocatorReloadEnterDisable("SentJons_HouseF3", "reload3", false); // открыть комнату
			pchar.quest.Jino_Door.win_condition.l1 = "locator";
			pchar.quest.Jino_Door.win_condition.l1.location = "SentJons_HouseF3";
			pchar.quest.Jino_Door.win_condition.l1.locator_group = "reload";
			pchar.quest.Jino_Door.win_condition.l1.locator = "reload4";
			pchar.quest.Jino_Door.function = "OpenRoomDoor";//на локатор комнаты Джино
			Achievment_Set("ach_10");
		break;
		
		case "Final_4":
			AddMoneyToCharacter(pchar, 100000);
			GiveItem2Character(pchar, "mushket2");
			dialog.text = "Az emeleti szobában találsz egy fiatal természetfilozófust. Ô a legjobb patikus, akit ismerek. Ô volt az, aki ezeket a keverékeket készítette, amelyek segítségével pár nap alatt felgyógyultál. Vigyázz a zsebpénzére, és a tudása kamatostul megtéríti minden költségedet.";
			link.l1 = "Az én személyes könyvmolyom? Rendben, majd én gondoskodom róla.";
			link.l1.go = "Final_5";
		break;
		
		case "Final_5":
			dialog.text = "Most el kell búcsúznom. A pincébe megyek, hogy összepakoljam a holmimat. Holnap már nem leszek itt - elhajózom Antiguáról. Örülök, hogy találkoztam veled, és örülök, hogy az én oldalamon álltál, és nem az ellenségeimmel.";
			link.l1 = "Én is örülök, hogy találkoztunk, John. Talán még találkozunk...";
			link.l1.go = "Final_6";
		break;
		
		case "Final_6":
			dialog.text = "Ebben az életben nem, barátom. Össze fogok pakolni. Viszlát, " + pchar.name + "!";
			link.l1 = "Viszlát, John! Sok szerencsét!";
			link.l1.go = "Final_7";
		break;
		
		case "Final_7":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "none", "", "", "", -1);
			npchar.lifeday = 0;
			pchar.questTemp.HWIC.Self = "final";
			AddQuestRecord("Holl_Gambit", "3-64");
			CloseQuestHeader("Holl_Gambit");
			pchar.questTemp.HWIC.Detector = "self_win";
		break;
		
		// Страж Истины
		case "guardoftruth":
			dialog.text = "Ah, jó uram, ne hallgasson ezekre az ostoba beszédekre. Nincs ott senki. Ott van a laboratóriumom, a keverékeket készítik, tudja...";
			link.l1 = "Félre a tréfával, John. Ismerôsen cseng Gino Gvineili neve?";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "Hmm...";
			link.l1 = "Aha! Látom a szemedben - igazam van... Ott lakik, és kinek készíti a gyógynövényeit!";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "Uram, még egyszer mondom - nincs itt senki.";
			link.l1 = "Tegyük félre a kifogásokat, John. Nem fogom bántani az alkimistádat - de ha Vincento atya Santiagóból megtalálja, nem lehetek biztos benne. Az inkvizítor már azt tervezi, hogy elküldi a 'Domini Canes' Antiguába...";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "Mit akarsz tôle?";
			link.l1 = "Csak beszélgetni. Nagyon fontos információi vannak számomra. Ígérem, hogy nem fogom az inkvizícióhoz fordulni, és nem fogom bántani semmilyen módon.";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			dialog.text = "Gino egy kedves fickó. Ne higgy el semmit, amit Vincento atya mondott róla. És ne feledd - ki fogok állni az alkimistámért.";
			link.l1 = "A szavamat adtam. Ez nem elég neked?";
			link.l1.go = "guardoftruth_5";
		break;
		
		case "guardoftruth_5":
			dialog.text = "Akkor menj fel az emeletre. Az ajtó nyitva van. És remélem, hogy hû maradsz a szavadhoz.";
			link.l1 = "Biztos lehetsz benne, hogy így lesz.";
			link.l1.go = "guardoftruth_6";
		break;
		
		case "guardoftruth_6":
			DialogExit();
			pchar.questTemp.Guardoftruth = "jino1";
			AddQuestRecord("Guardoftruth", "36");
			LocatorReloadEnterDisable(pchar.location, "reload4", false);
		break;
		
		// алхимический набор
		case "alchemy":
			dialog.text = "Kapitány, nem szeretne megismerkedni a hermetikus mûvészetekkel? Ez még nagyon hasznos lehet önnek.";
			link.l1 = "Sajnálom, de az én foglalkozásom kissé más. Én kardmarkolatot szoktam tartani a kezemben - nem pedig lombikokat vagy kémcsöveket.";
			link.l1.go = "alchemy_exit";
			link.l2 = "'Több dolog van az égen és a földön, mint amirôl a te filozófiád álmodik.' Hát persze, hogy szeretném. Mire van szükség?";
			link.l2.go = "alchemy_1";
			npchar.quest.alchemy = true;
		break;
		
		case "alchemy_exit":
			dialog.text = "Amit csak akarsz. Csak felajánlottam...";
			link.l1 = "...";
			link.l1.go = "exit";
		break;
		
		case "alchemy_1":
			dialog.text = "Meg kellene tanulnod saját kezûleg keverni a gyógynövényeket. De alkimista készlet nélkül nem fog sikerülni. Nézd meg ezt a táskát. Van benne minden, amire egy kezdô alkimistának szüksége van - kémcsövek, lombikok, egy lepárló, spatulák, üvegcsövek, egy égô és még egy csomó hasonló dolog...";
			link.l1 = "Nagyon érdekes! És mit lehet vele készíteni?";
			link.l1.go = "alchemy_2";
		break;
		
		case "alchemy_2":
			dialog.text = "Nos, az ólmot nem fogod tudni arannyá alakítani, de különbözô receptek szerint keverheted az összetevôket, és így bájitalokat és más hasznos dolgokat kapsz.";
			link.l1 = "Receptek?";
			link.l1.go = "alchemy_3";
		break;
		
		case "alchemy_3":
			dialog.text = "Igaz. Egy bájital vagy tárgy elkészítéséhez ismerned kell a receptet. A recepteket a kereskedôktôl lehet megvásárolni, vagy bárhol megtalálhatók. Miután tanulmányoztál egy receptet, össze kell gyûjtened minden szükséges hozzávalót, és pontosan azt kell csinálnod, ami oda van írva\n Használd az alkímia eszközeidet, keress vagy vegyél mozsarat és mozsárt, keress egy tégelyt, sajnos nem rendelkezem plusz egyel, amit adhatnék neked. Gyógynövények, szeszek, bájitalok, ásványok, szemét - minden megteszi, feltéve, hogy van megfelelô recept és eszköz.";
			link.l1 = "Nagyon érdekes. És mennyit kérsz ezért a készletért?";
			link.l1.go = "alchemy_4";
		break;
		
		case "alchemy_4":
			dialog.text = "Húszezer pezót. Ez egy nagyon jó készlet, és nagyon gyorsan fedezi az árát.";
			link.l1 = "Most gúnyolódsz velem, ugye? Egy táska üvegáruval egy csomagtartó áráért? Nem, kihagyom.";
			link.l1.go = "alchemy_exit";
			if (sti(pchar.money) >= 20000)
			{
				link.l2 = "Egyetértek. Szerintem érdekes lesz megpróbálni valamit saját kezûleg elkészíteni.";
				link.l2.go = "alchemy_5";
			}
		break;
		
		case "alchemy_5":
			AddMoneyToCharacter(pchar, -20000);
			Log_Info("Megkaptad az alkimista készletét.");
			GiveItem2Character(pchar, "alchemy_tool");
			PlaySound("interface\important_item.wav");
			dialog.text = "Nem fogja megbánni ezt a vásárlást, ebben teljesen biztos vagyok. Határozottan kifizetôdôbb, ha magad készíted el a bájitalokat, ahogy szükséged van rájuk, mintha gyógynövényboltokat látogatnál' , hogy darabonként megvásárolj mindent, amire szükséged van. Egyébként sem lehet mindig mindent megvenni, amire szükséged van. ";
			link.l1 = "Tanuljuk meg! Azt hiszem, meg tudom csinálni!";
			link.l1.go = "alchemy_6";
		break;
		
		case "alchemy_6":
			DialogExit();
			PlaySound("interface\notebook.wav");
			Log_Info("Ahhoz, hogy saját gyógynövényeket és amuletteket készíthess, rendelkezned kell az alkímia készséggel!");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//--> блок реагирования на попытку залезть в сундук
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Maga egy "+ GetSexPhrase("tolvaj, uram! Ôrök, vigyétek","tolvaj, lány! Ôrök, vigyétek") +"!!!", "Csak nézd meg ezt! Amint elmerültem az elmélkedésben, úgy döntöttél, hogy megnézed a mellkasomat! Vigyétek a tolvajt!!!", "ôrök! Rablás! Elkapni a tolvajt!!!");
			link.l1 = "A francba!";
			link.l1.go = "exit";
			LAi_group_Attack(NPChar, Pchar);
		break;
		//<-- блок реагирования на попытку залезть в сундук
	}
}
