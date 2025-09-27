void ProcessDialogEvent()
{
	ref sld, NPChar;
	aref Link, NextDiag;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Bogár. Szólj nekünk.";
			link.l1 = "Persze!";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "FalseTrace":
			DelMapQuestMarkCity(pchar.questTemp.FalseTrace.StartCity);
			dialog.text = "Jó napot, kapitány... ehm... kha-hahrm! Kibaszott aknák... Hadd mutatkozzam be. Adam Rayner. Egyszerû ember vagyok, és nem szeretem a hosszú elôszavakat, úgyhogy rögtön ki is köpöm. Szeretne jó pénzt keresni? Egy kis üzletet ajánlok neked, amit mindketten nem tudnánk egyedül megoldani.";
			link.l1 = "Heh! Jó pénzt? Érdekes. Hallgatlak, Adam.";
			link.l1.go = "FalseTrace_1";
			link.l2 = "Tudod, sajnálom, de nem tûnsz megbízhatónak. Úgyhogy nem fogok veled üzletelni.";
			link.l2.go = "FalseTrace_exit";
		break;
		
		case "FalseTrace_exit":
			dialog.text = "Megbízható? Ha-ha! Nem szabad az arcáról megítélni egy embert. Nos, nem érdekes. Épp most szalasztottál el egy jó lehetôséget, hogy könnyen és gyorsan jó pénzt keress. Találok majd valakit, aki együttmûködôbb...";
			link.l1 = "A beszélgetésünknek vége, uram. Viszontlátásra!";
			link.l1.go = "FalseTrace_exit_1";
		break;
		
		case "FalseTrace_exit_1":
			DialogExit();
			DelLandQuestMark(npchar);
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
			DeleteAttribute(pchar, "questTemp.FalseTrace");
		break;
		
		case "FalseTrace_1":
			//выбираем целевой пункт
			switch (hrand(2))
			{
				case 0: 
					pchar.questTemp.FalseTrace.DayQty = 18;
					pchar.questTemp.FalseTrace.TargetCity = "Beliz";
					pchar.questTemp.FalseTrace.TargetShore = "Shore8";
				break;
				case 1: 
					pchar.questTemp.FalseTrace.DayQty = 22;
					pchar.questTemp.FalseTrace.TargetCity = "Marigo";
					pchar.questTemp.FalseTrace.TargetShore = "Shore41";
				break;
				case 2: 
					pchar.questTemp.FalseTrace.DayQty = 20;
					pchar.questTemp.FalseTrace.TargetCity = "Santodomingo";
					pchar.questTemp.FalseTrace.TargetShore = "Mayak8";
				break;
			}
			pchar.questTemp.FalseTrace.ShipName = GenerateRandomNameToShip(sti(npchar.nation));
			pchar.questTemp.FalseTrace.Mation = sti(npchar.nation);
			dialog.text = "Kha! Öröm volt üzletet kötni egy ilyen gyors gondolkodású emberrel, mint ön, kapitány. Szóval, a feladat egyszerû: van egy flotta, tele tisztességes mennyiségû ezüsttel, és hamarosan kihajózik az egyik helyi kikötôbôl. Egyetlen hajó, kíséret nélkül. Butaság, igaz? K-kha\n Könnyû, mint a pite. Én megmondom, hol és mikor, te elviszed a zsákmányt, én pedig megkapom a részem.";
			link.l1 = "És persze készpénzben akarod megkapni most rögtön?";
			link.l1.go = "FalseTrace_2";
		break;
		
		case "FalseTrace_2":
			dialog.text = "Úgy nézek ki, mint egy szánalmas csaló, kapitány? Semmiképp sem. Csatlakozom önhöz ebben a rajtaütésben, és együtt fogjuk csinálni. Nem maradok a raktérben a harc alatt, épp ellenkezôleg - arra kérem, hogy tegyen be a fedélzeti csapatba, mint a tisztje, természetesen ideiglenesen\nTudom a dolgomat, tudom, hogyan kell szúrni és lôni az embereket. Úgyhogy én is kockáztatom a seggemet, mint te... khe... kha! Kifizeted a részemet, miután elfogtuk a bolhát.";
			link.l1 = "Melyik részét követeled magadnak a zsákmányból?";
			link.l1.go = "FalseTrace_3";
		break;
		
		case "FalseTrace_3":
			dialog.text = "Nem vagyok kapzsi ember, kapitány. Az én részem annyi, amennyit a régi hosszú hajóm rakterébe fel lehet pakolni, és ez körülbelül 200 csomag ezüst. Információim szerint nem kevesebb, mint 2000 csomag ezüst lesz a flottán, így a tizedét megkapom. Ez így igazságos, nem gondolja?";
			link.l1 = "A zsákmány tizede csak információért? Ilyen információkat a helyi kocsmában a részegesektôl veszek egy pohár rumért. Nem, mi nem egy irányba megyünk, barátom!";
			link.l1.go = "FalseTrace_4";
			link.l2 = "Hm. Azt hiszem, egyetértek. Elfogadom az ajánlatodat, Ádám. Üdvözöllek a fedélzeten. Most az információidról: honnan, hová, mikor, a hajó neve?";
			link.l2.go = "FalseTrace_5";
		break;
		
		case "FalseTrace_4":
			dialog.text = "Micsoda zsugori vagy, kapitány! Ebben az esetben szart fogsz kapni! Viszlát!";
			link.l1 = "Sok szerencsét! Keress egy másik együgyût a kétes vállalkozásodhoz!";
			link.l1.go = "FalseTrace_exit_1";
		break;
		
		case "FalseTrace_5":
			dialog.text = "A fleut neve a "+pchar.questTemp.FalseTrace.ShipName+", Cartagenából indul és "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.TargetCity)+"vitorlázik. Bár nincs sok idônk. Két hét, legfeljebb három. Ha három héten belül nem találjuk meg, akkor vége.";
			link.l1 = "Akkor ne vesztegessük az idôt! Hív a kaland!";
			link.l1.go = "FalseTrace_6";
		break;
		
		case "FalseTrace_6":
			DialogExit();
			NextDiag.CurrentNode = "FalseTrace_officer";
			DelLandQuestMark(npchar);
			ChangeCharacterAddressGroup(npchar, pchar.location, "goto", "goto1");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			AddPassenger(pchar, npchar, false);
			AddQuestRecord("FalseTrace", "1");
			AddQuestUserData("FalseTrace", "sCity1", XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.StartCity+"Gen"));
			AddQuestUserData("FalseTrace", "sCity2", XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.TargetCity));
			AddQuestUserData("FalseTrace", "sShip", pchar.questTemp.FalseTrace.ShipName);
			//установим таймер на генерацию энкаунтера
			pchar.quest.False_Trace_2.win_condition.l1 = "Timer";
			pchar.quest.False_Trace_2.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.False_Trace_2.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 2);
			pchar.quest.False_Trace_2.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 2);
			pchar.quest.False_Trace_2.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 2);
			pchar.quest.False_Trace_2.function = "CreateFalseTraceGaleonOnMap";
			SetFunctionTimerCondition("FalseTraceGaleonOver", 0, 0, sti(pchar.questTemp.FalseTrace.DayQty)+2, false);//таймер
		break;
		
		case "FalseTrace_officer":
			dialog.text = "Kért valamit, kapitány?";
			link.l1 = "Semmit, nem számít.";
			link.l1.go = "exit";
			NextDiag.TempNode = "FalseTrace_officer";
		break;
		
		case "FalseTrace_7":
			chrDisableReloadToLocation = true;
			dialog.text = "Látni akart, kapitány?";
			link.l1 = "Azt hiszem, tudtad, hogy ez lesz... Hol van az ezüst, a fenébe is? Hol van? Hozzád beszélek! A fleut kapitánya azt mondta nekem, hogy ez egy gyûjtögetô hajó! Hazudtál nekem!";
			link.l1.go = "FalseTrace_8";
		break;
		
		case "FalseTrace_8":
			dialog.text = "Nyugodjon meg, kapitány. Megpróbálok mindent elmagyarázni.";
			link.l1 = "Hát persze, hogy hazudtál! Már megnyugodtam! Jelenleg csak azért nem lógsz a yardarmon, mert még mindig nem értem az indítékaidat. Úgy üldözted velem ezt a fleutot, hogy elôre tudtad, hogy nincs ezüst. Úgyhogy kérlek, magyarázd meg magad!";
			link.l1.go = "FalseTrace_9";
		break;
		
		case "FalseTrace_9":
			dialog.text = "Igen, tényleg átvertem magát, kapitány. De csak így tudtam rávenni, hogy megtegye, amire szükségem van, hogy elfogjam... khe kha! Hogy elfogjam ezt az átkozott fleut\nDe ígérem, hogy visszafizetem az adósságomat. Most pedig hadd mondjam el, miért tettem. Találtál egy nôt a fleuton? Láttam, hogy a legénység felvette ôt a hajódra...";
			link.l1 = "Hm... Szóval szükséged volt a lányra? És ezért kényszerítettél arra, hogy tengeri csatát kezdjek és rengeteg embert öljek meg!?";
			link.l1.go = "FalseTrace_10";
		break;
		
		case "FalseTrace_10":
			dialog.text = "A feleségem az. Katerine Rayner. Három hónappal ezelôtt megszökött tôlem ezzel a szánalmas kapitánnyal. Mindent megtettem, hogy megtaláljam ôket, és sikerült is. Mindketten a "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.TargetCity)+". El sem tudtam volna képzelni jobb módját annak, hogy visszaadjam Katerine-t, és még azzal a feleséglopóval is elbánjak\nHa elmondanám az igazat, elsétálna. Így hát el kellett mesélnem egy szaftos történetet egy ezüsttel teli fleutról.";
			link.l1 = "Hmpf... A feleséged elhagyott, ugye? Nagyon érdekes!";
			link.l1.go = "FalseTrace_11";
		break;
		
		case "FalseTrace_11":
			dialog.text = "Ô a törvényes feleségem, szeretem ôt, és senki másnak nincs joga hozzá! Az a gazember szép hazugságokat mesélt neki a romantikáról és mindenféle szarságról, amikor én... távol voltam. Nem ismered a nôket? Elhitte azt a szemetet, buta lány, és elszökött vele.";
			link.l1 = "Rendben, figyelj, nem igazán érdekel a családi életed, úgyhogy rendezd el a feleségeddel. De azt mondtad, hogy kompenzáld a költségeimet, nem igaz? Jól hallottam?";
			link.l1.go = "FalseTrace_12";
		break;
		
		case "FalseTrace_12":
			if (pchar.basenation == SPAIN || pchar.basenation == HOLLAND)
			{
				pchar.questTemp.FalseTrace.QuestCity = "Portobello";
				pchar.questTemp.FalseTrace.QuestShore = "Shore48";
			}
			else
			{
				pchar.questTemp.FalseTrace.QuestCity = "SantaCatalina";
				pchar.questTemp.FalseTrace.QuestShore = "Shore54";
			}
			dialog.text = "Igen, jól hallotta, kapitány. Szívességet szívességért szívességért. Most nincs pénzem, de ha elvisz Katerine-t és engem a "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity)+", elmondok neked teljesen megbízható információkat, ahol minden erôfeszítés nélkül szerezhetsz némi aranyat.";
			link.l1 = "Nagyon érdekes. És miért nem tudod elmondani nekem ezt a teljesen megbízható információt most azonnal?";
			link.l1.go = "FalseTrace_13";
		break;
		
		case "FalseTrace_13":
			dialog.text = "Mert még nem rendelkezem ezzel az információval. Hadd magyarázzam el részletesen. Egy Squint-eyed Solly nevû szerencsés úriember - hallottál már róla? - néhány aranybányát készül kifosztani Blueweldtôl nem messze\nBizonyos események miatt kénytelen lesz minden aranyát egy eldugott helyen hagyni, és néhány ôrt állítani, hogy megvédjék. Maga a férfi gyalog megy Belize-be vagy Blueweldbe, hogy szerezzen egy hajót\nVan egy ügynököm Solly legénysége között, ô vár engem a "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity)+". Amint ott lehorgonyozunk, el fogja mondani, hol rejtegeti Solly a javait\nMész oda, kiiktatod az ôröket, és minden aranyat magadhoz veszel. Én magam akartam megcsinálni, de a jelenlegi helyzetet figyelembe véve, mindent rád bízok. Nem kell fizetni.";
			link.l1 = "A történeted nagyon hasonlít az elôzô mesédre az ezüsttel teli fleutról. Egyszer már becsaptál engem. Hogyan tudja garantálni, hogy ezúttal nem hazudik?";
			link.l1.go = "FalseTrace_14";
		break;
		
		case "FalseTrace_14":
			dialog.text = "A szavamat adom. Más garanciát nem vállalok. De ez igaz, esküszöm khe... kha... átkozott aknák!";
			link.l1 = "Jól van. Most menj, én pedig átgondolom, amit mondtál.";
			link.l1.go = "FalseTrace_15";
		break;
		
		case "FalseTrace_15":
			dialog.text = "Ne gondolkodj túl sokáig. Hunyorszemû Solly vissza fog térni a kincseiért, ahogy azt neked is észre kell venned. Számításaim szerint mindössze két hetetek van, hogy eljussatok a "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity+"Gen")+".";
			link.l1 = "Ezt szem elôtt tartom. És most menjetek a legénység szállásaira és csatlakozzatok a matrózokhoz. Azt hiszem, jobb lesz, ha a feleségeddel külön maradsz, amíg megérkezünk. Most már mehetsz.";
			link.l1.go = "FalseTrace_16";
		break;
		
		case "FalseTrace_16":
			DialogExit();
			LAi_SetActorType(npchar);
			pchar.questTemp.FalseTrace = "TalkCabinWoman";
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "TalkSelf_Quest", 3.0);
			SetFunctionTimerCondition("FalseTraceSollyOver", 0, 0, 15, false);//таймер
			AddQuestRecord("FalseTrace", "5");
			AddQuestUserData("FalseTrace", "sCity", XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity));
		break;
		
		case "FalseTrace_17":
			dialog.text = "Hívott engem, kapitány?";
			link.l1 = "Igen, uram. Adam Rayner, letartóztatlak és bezárlak. Átvertél, és nincs más választásom, mint hogy elszigeteljelek és átadjalak a hatóságoknak.";
			link.l1.go = "FalseTrace_18";
		break;
		
		case "FalseTrace_18":
			dialog.text = "Tényleg? Igen. Elvártam, hogy ezt tegye, kapitány. Különösen azután, hogy bejött a raktérbe, és elbeszélgetett azzal a mocskos, más feleségeit elrablóval. Úgy döntött, hogy az ô oldalán áll, nem igaz, kapitány?";
			link.l1 = "Semmi közöd hozzá. Kihasználtál, keresztbe tettél nekem, és most megint megpróbálsz becsapni abszurd kincses mesékkel! Bosun, vigye el!";
			link.l1.go = "FalseTrace_19";
		break;
		
		case "FalseTrace_19":
			dialog.text = "Kha, ne olyan gyorsan, kapitány... A bosun és a többi embered nem fog ide egyhamar bejönni. Nem vetted észre, hogy bezártam az ajtót? Most már egyedül vagyunk itt - csak te és én. Szóval mutassa meg, kapitány, mire képes!";
			link.l1 = "Tényleg? Tényleg? Tényleg azt hiszi, hogy van esélye?! Ezt még megbánod, te köcsög!";
			link.l1.go = "FalseTrace_20";
		break;
		
		case "FalseTrace_20":
			DialogExit();
			NextDiag.currentnode = "FalseTrace_21";
			chrDisableReloadToLocation = true;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_SetHP(npchar, 100+MOD_SKILL_ENEMY_RATE*35, 100+MOD_SKILL_ENEMY_RATE*35); // belamour с 40 хп боец из него никудышный
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_SetCheckMinHP(npchar, 10.0, true, "FalseTrace_capture");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "FalseTrace_21":
			dialog.text = "";
			link.l1 = "Így már jobb... Tegye le a fegyvert, gazember! Bosun! Tegyétek vasra ezt a gazembert, és dobjátok a raktérbe!";
			link.l1.go = "FalseTrace_22";
		break;
		
		case "FalseTrace_22":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);
			bQuestDisableMapEnter = false;
			RemovePassenger(Pchar, npchar);
			pchar.GenQuest.LastQuestPrisonerIdx = SetCharToPrisoner(npchar);
			SetCharacterRemovable(&characters[sti(pchar.GenQuest.LastQuestPrisonerIdx)], false);
			Pchar.questTemp.FalseTrace.PrisonerAdamIDX = sti(pchar.GenQuest.LastQuestPrisonerIdx);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 3.0);
			LAi_SetPlayerType(pchar);
			RemoveCharacterEquip(npchar, BLADE_ITEM_TYPE);
			RemoveCharacterEquip(npchar, GUN_ITEM_TYPE);
			RemoveCharacterEquip(npchar, CIRASS_ITEM_TYPE);
			sld = &Characters[sti(Pchar.questTemp.FalseTrace.PrisonerIDX)];
			ReleasePrisoner(sld); //освободили пленника
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, false);
			DeleteAttribute(sld, "LifeDay") //постоянный персонаж
			GiveItem2Character(sld, "blade_10");
			EquipCharacterbyItem(sld, "blade_10");
			GiveItem2Character(sld, "pistol1");
			EquipCharacterbyItem(sld, "pistol1");//патроны не даю - все одно для антуражу
			DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
			AddComplexSelfExpToScill(40, 40, 40, 40);
			AddQuestRecord("FalseTrace", "11");
			AddQuestUserData("FalseTrace", "sShore", XI_ConvertString(pchar.questTemp.FalseTrace.TargetShore+"Gen"));
			pchar.questTemp.FalseTrace = "AdamPrisoner";
		break;
		
		case "FalseTrace_23":
			pchar.quest.FalseTraceSollyOver.over = "yes"; //снять таймер
			dialog.text = "Köszönöm, kapitány, hogy segített visszahozni a feleségemet! Adam Rayner az adósa, nem fogja elfelejteni, ha-ha, esküszöm... kha! Átkozott aknák! Most pedig Squint-eyed Sollyról. Az emberem már minden részletet elmondott. Solly az összes holmiját a San Juan del Norte öböl egyik barlangjában hagyta. Maga az ember most Blueweldben van\nSietned kell, a haverom szerint már csak öt napod van. Vigyétek magatokkal az embereiteket, Solly banditái kemények, adnak majd egy kis meleget\nIdeje búcsút venni. Még egyszer köszönöm, kapitány, Isten éltessen!";
			link.l1 = "Sok szerencsét, Adam. Ne bántsd meg a feleséged!";
			link.l1.go = "FalseTrace_Remove_exit";
			SetFunctionTimerCondition("FalseTraceBonanzaOver", 0, 0, 5, false);//таймер
			pchar.quest.False_Trace_4.win_condition.l1 = "location";
			pchar.quest.False_Trace_4.win_condition.l1.location = "Shore55";
			pchar.quest.False_Trace_4.function = "FalseTrace_SollyBonanza";
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			AddQuestRecord("FalseTrace", "14");
			AddQuestUserData("FalseTrace", "sCity", XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity));
		break;
		
		case "FalseTrace_24":
			pchar.quest.FalseTraceSollyOver.over = "yes"; //снять таймер
			dialog.text = "Ha! Mi az ördögnek mentünk partra ebben az öbölben, kapitány úr? Mondtam, hogy az emberem a "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity+"Gen")+"kikötôben vár rám! Azt tervezi, hogy gyalog megy oda a dzsungeleken keresztül?";
			link.l1 = "Rosszul tippeltél, Adam. Tényleg azt hitted, hogy még egyszer elhiszem a hülyeségeidet? Azt hiszed, hogy teljesen hülye vagyok? Ezúttal alkut kötöttem a feleségeddel.";
			link.l1.go = "FalseTrace_25";
		break;
		
		case "FalseTrace_25":
			dialog.text = "Micsoda?! Kha! Miféle alkut kötöttél a feleségemmel? Mirôl beszélsz, te rohadt hal?!";
			link.l1 = "A hamis információid miatt elfogtam egy üres fleutot, és megöltem a kapitányát. Sajnálom, hogy ezt tettem, bár már túl késô bánni. A feleséged szerelmes volt abba a matrózba, ahogy én megértettem. Ezért kért meg, hogy öljelek meg. Ezért vagyunk most itt ebben az öbölben.";
			link.l1.go = "FalseTrace_26";
		break;
		
		case "FalseTrace_26":
			dialog.text = "Ezt nem hiszem el! Katerine... micsoda ribanc! Nos, megkapod, amit megérdemelsz... Szóval, hogyan ígérte, hogy fizet neked, te bolond? Egy fillérje sincs, még az ékszereit is eladta, hogy elszökhessen azzal a kapitánnyal!";
			link.l1 = "Ez nem a te dolgod, gazember. De itt az ideje, hogy befejezzük a beszélgetésünket. Elküldelek a pokolba, ahol már régóta lenned kellene!";
			link.l1.go = "FalseTrace_27";
		break;
		
		case "FalseTrace_27":
			dialog.text = "Lássuk, mire vagy képes, rohadt hering!";
			link.l1 = "...";
			link.l1.go = "FalseTrace_28";
		break;
		
		case "FalseTrace_28":
			DialogExit();
			npchar.SaveItemsForDead = true;
			npchar.DontClearDead = true;
			LAi_SetWarriorType(npchar);
			LAi_SetImmortal(npchar, false);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "FalseTrace_AdamDead");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "FalseTrace_abordage":
			dialog.text = "Ah! Mi a fenéért támadtad meg a hajómat, te szemétláda? Nem értem...";
			link.l1 = "Ne játssza a bárányt, kapitány! Tudom, hogy milyen rakományt szállítanak. Szükségem van rá.";
			link.l1.go = "FalseTrace_abordage_1";
		break;
		
		case "FalseTrace_abordage_1":
			dialog.text = "Rakomány? Ha-ha! Miféle rakományt vártatok itt látni? A raktér üres!";
			link.l1 = "Mit mondtál, gazember! Gyere vissza!";
			link.l1.go = "FalseTrace_abordage_2";
		break;
		
		case "FalseTrace_abordage_2":
			dialog.text = "Ismétlem - nincs rakomány a fedélzeten. Ez a fleut egy gyûjtôhajó, amely a "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.TargetCity)+" felé tart, hogy ágyúgolyókat és élelmiszert vigyen a csapatoknak.";
			link.l1 = "Maga átveri a szememet. A raktér tele lehet ezüsttel. És meg is fogom nézni, miután befejeztük ezt a beszélgetést...";
			link.l1.go = "FalseTrace_abordage_3";
		break;
		
		case "FalseTrace_abordage_3":
			dialog.text = "Nem tudom, ki beszélt neked az ezüstrôl. De ez teljes képtelenség... Vesztettem ellened, úgyhogy feladom. Itt a kardom. Most már mehetsz és ellenôrizheted a raktárakat. Üresek.";
			link.l1 = "Feladod? Nem! Nincs szükségem tanúkra. Fogd a kardod és harcolj, vagy kibelezlek, mint egy birkát.";
			link.l1.go = "FalseTrace_abordage_4";
			link.l2 = "Jó neked, hogy észhez tértél. Azt hiszem, képes leszek váltságdíjat szerezni érted... Hé, srácok - dobjátok a kapitányt a raktérbe!";
			link.l2.go = "FalseTrace_abordage_5";
		break;
		
		case "FalseTrace_abordage_4":
			DialogExit();
			pchar.questTemp.FalseTrace.KillCaptain = "true";//атрибут квеста
			Lai_SetPlayerType(pchar);
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "FalseTrace_AfterFight");
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.questTemp.FalseTrace.CapName = GetFullName(npchar);
			ChangeCharacterComplexReputation(pchar, "nobility", -3);
		break;
		
		case "FalseTrace_abordage_5":
			DialogExit();
			pchar.questTemp.FalseTrace.CapPrisoner = "true";//атрибут квеста
			Lai_SetPlayerType(pchar);
			DeleteAttribute(npchar, "DontRansackCaptain");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "FalseTrace_AfterFight", 3.0);
			pchar.GenQuest.LastQuestPrisonerIdx = SetCharToPrisoner(npchar);
			SetCharacterRemovable(&characters[sti(pchar.GenQuest.LastQuestPrisonerIdx)], false);
			pchar.questTemp.FalseTrace.CapName = GetFullName(npchar);
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
		break;
		
		case "FalseTrace_wife":
			dialog.text = "Megölted ôt, te gazember! Gazember! Szegény "+pchar.questTemp.FalseTrace.CapName+"!";
			link.l1 = "Ez meg mi? Honnan jöttél, drágám?";
			link.l1.go = "FalseTrace_wife_1";
		break;
		
		case "FalseTrace_wife_1":
			dialog.text = "A pokolban fogsz égni mindazért, amit tettél. Cseszd meg!";
			link.l1 = "Nyugodj meg, ifjú hölgy! Ne próbáld ki a szerencsédet azzal, hogy átkozódsz - vagy egyenesen a kapitányod után küldelek!";
			link.l1.go = "FalseTrace_wife_2";
		break;
		
		case "FalseTrace_wife_2":
			dialog.text = "Te... te nem mersz kezet emelni egy nôre!";
			link.l1 = "Nem is lesz rá szükségem. Le is lôhetlek. Vagy csak kidoblak a fedélzetre, és a cápák elvégzik a többit... Na, mire vársz még? Menj a hajómra. Ne félj - nem hagyom, hogy bárki bántson, és magam sem nyúlok hozzád, ha csendben vagy...";
			link.l1.go = "FalseTrace_wife_3";
		break;
		
		case "FalseTrace_wife_3":
			DialogExit();
			pchar.quest.False_Trace_AfterBattle.over = "yes";
			pchar.quest.FalseTraceGaleonOver.over = "yes";
			if (CheckAttribute(pchar, "questTemp.FalseTrace.CapPrisoner")) AddQuestRecord("FalseTrace", "");
			else AddQuestRecord("FalseTrace", "");
			sld = characterFromId("Mugger");
			DeleteAttribute(sld, "HalfImmortal");
			RemovePassenger(Pchar, sld);
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, false);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 3.0);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			DoQuestCheckDelay("LAi_EnableReload", 4.0);
			bQuestDisableMapEnter = true;
			pchar.questTemp.FalseTrace = "TalkCabin";
			AddQuestRecord("FalseTrace", "4");
		break;
		
		case "FalseTrace_wife_4":
			dialog.text = "Mit... mit fogsz csinálni vele?";
			link.l1 = "Ez meg mi? Honnan jöttél, drágám?";
			link.l1.go = "FalseTrace_wife_5";
		break;
		
		case "FalseTrace_wife_5":
			dialog.text = "Szegény "+pchar.questTemp.FalseTrace.CapName+"! Mondd csak - meg fogod ölni? Ne...";
			link.l1 = "Figyeljen, hölgyem - ha meg akarnám ölni, már megtettem volna. A raktérben marad, és aztán elengedem, vagy valószínûleg váltságdíjat kérek érte... az utóbbi a valószínûbb. És most kérem, legyen jó kislány, és menjen a hajómra. Ne félj - nem hagyom, hogy bárki bántson, és magam sem nyúlok hozzád, ha csendben vagy...";
			link.l1.go = "FalseTrace_wife_3";
		break;
		
		case "FalseTrace_wife_6":
			if (CheckAttribute(pchar, "questTemp.FalseTrace.KillCaptain"))
			{
				dialog.text = "Mit akarsz tôlem? A cápák elé dobsz, ahogy mondtad, hogy megteszed? Tönkretetted az életemet és én...";
				link.l1 = "Gyere, drágám. Senki nem fog sehova sem dobni téged. Csak tisztázni szeretném a helyzetet, mivel miattad támadtam meg ezt a fleutot, és nem más okból.";
				link.l1.go = "FalseTrace_wife_7";
			}
			else
			{
				dialog.text = "Mit akarsz tôlem? Hol van "+pchar.questTemp.FalseTrace.CapName+"? Váltságdíj? Váltságdíjra van szüksége?";
				link.l1 = "Rendben, hölgyem, hagyjuk abba ezt az értelmetlen kérdésáradatot. Nem ezért hívtam ide. Egy tényt tisztáztunk, és érdekes lesz hallania.";
				link.l1.go = "FalseTrace_wife_20";
			}
		break;
		
		case "FalseTrace_wife_7":
			dialog.text = "Miattam? Azt mondod, hogy az én hibám, hogy megtámadtad a hajónkat és megölted a szerelmemet? Szegény "+pchar.questTemp.FalseTrace.CapName+", mit tett veled? Felelni fogsz az Úr elôtt mindazért, amit tettél...";
			link.l1 = "Ugyanaz a régi pörkölt! Visszatérhetnénk a cápás beszélgetésünkhöz?";
			link.l1.go = "FalseTrace_wife_8";
		break;
		
		case "FalseTrace_wife_8"://ноды пересечения - старт
			dialog.text = "";
			link.l1 = "Most már csend van? Remek. Most figyeljetek rám! Azért támadtam meg a hajót, mert információim voltak arról, hogy tisztességes rakományt szállít. És ezt az információt Adam Raynertôl kaptam.";
			link.l1.go = "FalseTrace_wife_9";
		break;
		
		case "FalseTrace_wife_9":
			dialog.text = "Ah! Mi?! Adam? Hol van? Itt van?";
			link.l1 = "Látom, ismeri a nevét... Katerine. És, mint látja, már mindent tudok magáról. Gondolom, Adam Rayner a férje, ugye?";
			link.l1.go = "FalseTrace_wife_10";
		break;
		
		case "FalseTrace_wife_10":
			dialog.text = "Igen. Én ennek a szörnyetegnek a felesége vagyok. Abban az illúzióban éltem, hogy ennek a rémálomnak végre vége... Felbérelte magát, hogy elkapjon?";
			link.l1 = "Általában így alakult. Ádám hazudott nekem a sliverrôl, hogy elkapjam a fleut '"+pchar.questTemp.FalseTrace.ShipName+"'. Határozottan elhatározta, hogy visszahozza magát. Negyedórával ezelôtt elmagyarázta nekem minden tettét.";
			link.l1.go = "FalseTrace_wife_11";
		break;
		
		case "FalseTrace_wife_11":
			dialog.text = "És... mit akar? Mit mondott neked?";
			link.l1 = "Azt akarja, hogy törvényes felesége visszatérjen hozzá. Kárpótlásul azért, hogy becsapott, információt fog adni nekem a kancsal Solly aranyáról. Én pedig mindkettôtöket elviszlek a "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity)+".";
			link.l1.go = "FalseTrace_wife_12";
		break;
		
		case "FalseTrace_wife_12":
			dialog.text = "Nem... (sírva) Nem akarok visszamenni ehhez a gazemberhez! Hatalmas erôfeszítéseket tettem, hogy elmeneküljek elôle és eltüntessem a nyomaimat, de ô mégis megtalált... Gazember! Bandita! Kibaszott tolvaj!";
			link.l1 = "Nyugodjon meg, Katerine... Vigyázzon a nyelvére. Végül is ô a férjed. És azt mondta, hogy szereti magát.";
			link.l1.go = "FalseTrace_wife_13";
		break;
		
		case "FalseTrace_wife_13":
			dialog.text = "(weepingly) My husband? Tudod, hogy ki a férjem? Ô egy volt rab, egy elítélt és most a legkegyetlenebb bandita "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.StartCity+"Gen")+"! Ô egy aljas és mocskos vadállat, én pedig csak egy lyuk vagyok a lábai között, amit meg kell dugni neki!";
			link.l1 = "Nem láttál mindent, mielôtt hozzámentél?";
			link.l1.go = "FalseTrace_wife_14";
		break;
		
		case "FalseTrace_wife_14":
			dialog.text = "Elôször más volt... És a múltja olyan romantikusnak tûnt számomra... De végül minden megváltozott. És nem is akarom látni ôt, nemhogy vele élni, nem érted? Nem akarom! Fôleg a Fleut elleni támadás után, amit ô rendezett!";
			link.l1 = "Hm... Mit csináljak veled, édes hölgyem?";
			link.l1.go = "FalseTrace_wife_15";
		break;
		
		case "FalseTrace_wife_15"://ноды пересечения - конец
			if (CheckAttribute(pchar, "questTemp.FalseTrace.KillCaptain"))
			{
				dialog.text = "Mit tegyünk? Én tudom, mit kell tennem. A férjem tetteinek köszönhetôen a bûn eszköze vagy. Megöltél egy ártatlan embert, az egyetlen embert, aki jól bánt velem. Vezekelj a bûneidért, kapitány. Öld meg Ádámot. A szemem láttára. Látni akarom ezt a söpredéket meghalni, le akarom köpni a holttestét\nHa meghal, elmondom, hol rejtegeti a kincseit. Részeg idióta mesélt nekem egyszer a rejtekhelyérôl, ha-ha, már nem is emlékszik rá!";
				link.l1 = "Heh! Kegyetlen nô vagy, Katerine, ahogy látom!";
				link.l1.go = "FalseTrace_wife_16";
			}
			else
			{
				dialog.text = ""+pchar.questTemp.FalseTrace.CapName+"... A flotta kapitánya. Bezártad ôt. Beszélj vele, könyörgöm! Felajánl valamit az életünkért és a szabadságunkért! Elô fog állni egy ötlettel! I... Nem akarok visszamenni Ádámhoz, mostantól "+pchar.questTemp.FalseTrace.CapName+" a férjem! Könyörgöm - ne vigyél vissza Ádámhoz, ahhoz a szörnyeteghez!";
				link.l1 = "Hm. Érdekes. És mit ajánlhat nekem a foglyom? Váltságdíjat kaphatok érte a hatóságoktól, és megkapom a kancsal Solly aranyát is...";
				link.l1.go = "FalseTrace_wife_21";
			}
		break;
		
		case "FalseTrace_wife_16":
			dialog.text = "Nézd, ki beszél itt kegyetlenségrôl. Hajózz a "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity)+", tedd azt, amit Ádám mondott, csak ne a kikötôben, hanem a legközelebbi öbölben szállj le. Hárman odamegyünk, és te megölöd a fattyút\nHa ez megtörtént, elmondom neked a rejtekhelyet. Esküszöm, nem hazudok. Hiszem, hogy inkább az én szavaimban bízol, mint Adaméban, egyszer már átvert téged, nem igaz? Mit fog mondani, kapitány?";
			link.l1 = "Igen... Nem véletlenül mondják, hogy férj és feleség valóban ugyanabból a fajtából való. Rád nézek, Katerine, és látom, hogy te vagy a legjobb párosítás Ádámhoz... Ha ennyire holtan akarod látni, akkor akár le is szúrhatod részeg álmában... Bosun! Vigyétek el!";
			link.l1.go = "FalseTrace_wife_17";
			link.l2 = "Gyûlölöm a gazembereket, akik megpróbálnak becsapni és a saját céljaikra felhasználni. Rendben, Katherine, elfogadom az ajánlatodat, mivel világos számomra, hogy Adamben nem lehet megbízni. De ha engem is becsapsz, még Európában is megtalállak, esküszöm, és golyót eresztek a fejedbe. Most pedig tûnj el. Bosun! Vigyétek el!";
			link.l2.go = "FalseTrace_wife_19";
		break;
		
		case "FalseTrace_wife_17":
			dialog.text = "Ezt még megbánod... Esküszöm, én...";
			link.l1 = "Csónakmester! Vigyázz rá és tartsd szemmel, amíg meg nem érkezünk a "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity+"Gen")+"!";
			link.l1.go = "FalseTrace_wife_18";
		break;
		
		case "FalseTrace_wife_18":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 3.0);
			AddQuestRecord("FalseTrace", "6");
			AddQuestUserData("FalseTrace", "sCity", XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity));
			AddDialogExitQuestFunction("SetCheckForSolly");
			chrDisableReloadToLocation = false;
			bQuestDisableMapEnter = false;
			DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
		break;
		
		case "FalseTrace_wife_19":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 3.0);
			AddQuestRecord("FalseTrace", "7");
			AddQuestUserData("FalseTrace", "sCity", XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity));
			AddDialogExitQuestFunction("SetCheckForKillAdam");
			chrDisableReloadToLocation = false;
			bQuestDisableMapEnter = false;
			DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
		break;
		
		case "FalseTrace_wife_20":
			dialog.text = "Micsoda? Mit fogsz csinálni velünk? Miért foglaltátok el a hajónkat?";
			link.l1 = "Hagyjatok egy szót is szólni, vagy parancsoljam meg a matrózomnak, hogy hallgattassalak el egy szájkosárral?!";
			link.l1.go = "FalseTrace_wife_8";
		break;
		
		case "FalseTrace_wife_21":
			dialog.text = "Solly aranya? Tényleg megbízol ebben a gazemberben? Megint át fog verni téged, ez csak az ô módszere! Beszélj a foglyoddal!\n"+pchar.questTemp.FalseTrace.CapName+" igazi úriember, nem fogja megszegni a szavát, és nem fog hazudni neked!";
			link.l1 = "Nem gyôzött meg, hölgyem. Nincs mirôl beszélnem a kapitányoddal. Megszerzem érte a váltságdíjat, és megszerzem Solly aranyát Ádámtól. Ha Adam még egyszer becsap engem, még a világ végén is megtalálom, és megátkozza a napot, amikor megszületett... Bosun! Vigyétek el!";
			link.l1.go = "FalseTrace_wife_23";
			link.l2 = "Az igazat megvallva, nem bízom Ádámban... Utálom, ha manipulálnak. Rendben, beszélek a kapitányoddal, és meglátom, mit tud mondani. Most már elmehetsz... Bosun! Vigyék el!";
			link.l2.go = "FalseTrace_wife_24";
		break;
		
		case "FalseTrace_wife_23":
			dialog.text = "Maga egy kegyetlen és szívtelen ember! Esküszöm, hogy...";
			link.l1 = "Csónakmester! Ôrizd és tartsd szemmel egész idô alatt, amíg megérkezünk a "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity+"Gen")+"!";
			link.l1.go = "FalseTrace_wife_18";
			SetCharacterRemovable(&characters[sti(pchar.GenQuest.LastQuestPrisonerIdx)], true);
		break;
		
		case "FalseTrace_wife_24":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 3.0);
			AddQuestRecord("FalseTrace", "8");
			chrDisableReloadToLocation = false;
			pchar.questTemp.FalseTrace.Prisoner = "true";
			SetCharacterRemovable(&characters[sti(pchar.GenQuest.LastQuestPrisonerIdx)], true);
		break;
		
		case "FalseTrace_wife_25":
			dialog.text = "Most már vége... Szegény "+pchar.questTemp.FalseTrace.CapName+" megbosszultam magam, és most már szabadon lélegezhetek, és özvegyasszonynak mondhatom magam...";
			link.l1 = "Teljesítettem az alku rám esô részét, Katerine. Most te jössz.";
			link.l1.go = "FalseTrace_wife_26";
		break;
		
		case "FalseTrace_wife_26":
			dialog.text = "Természetesen, kapitány. A férjem - hála Istennek, most már volt férjem - egy bandita volt, mint azt már tudod. Félve a lehetséges házkutatásoktól, nem tartotta otthon a kifosztott zsákmányt. Szervezett egy rejtekhelyet - de egyszer elkotyogta a dolgot. Mégis, nagyon ügyesen elrejtette - a partról nem lehet megközelíteni azt a helyet.";
			link.l1 = "Nagyon érdekes... És hol van?";
			link.l1.go = "FalseTrace_wife_27";
		break;
		
		case "FalseTrace_wife_27":
			dialog.text = "Egy kis szigeten Hispaniola közelében. A világítótoronyban.";
			link.l1 = "Kikötô-au-Prince világítótorony! A szigeten található!";
			link.l1.go = "FalseTrace_wife_28";
		break;
		
		case "FalseTrace_wife_28":
			dialog.text = "Valószínûleg így van. Ott találod majd a zsákmányt. Látni fogod. Ez minden. Viszlát, kapitány.";
			link.l1 = "Várjatok... Bocsáss meg, Katerine, ha tudsz. Remélem, hogy annak a halála, aki minden szerencsétlenségedért felelôs, mindenképpen megkönnyebbülés lesz. Nagyon sajnálom...";
			link.l1.go = "FalseTrace_wife_29";
		break;
		
		case "FalseTrace_wife_29":
			dialog.text = "Nincs szükségem a sajnálatára, kapitány. Megtette, amire kértem - és elmondtam mindent, amit tudni akart. Most pedig búcsúzzon el, és hagyjon magamra a bánatommal...";
			link.l1 = "Viszlát, Katerine.";
			link.l1.go = "FalseTrace_wife_30";
		break;
		
		case "FalseTrace_wife_30":
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 15);
			LAi_LocationDisableOfficersGen(pchar.questTemp.FalseTrace.QuestShore, false);//офицеров пускать
			//LAi_LocationDisableOfficersGen("Mayak7", true);//офицеров не пускать
			locations[FindLocation("Mayak7")].DisableEncounters = true;//энкаунтеры закрыть
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			pchar.quest.False_Trace_7.win_condition.l1 = "location";
			pchar.quest.False_Trace_7.win_condition.l1.location = "Mayak7";
			pchar.quest.False_Trace_7.function = "FalseTrace_AdamTreasure";
			AddQuestRecord("FalseTrace", "23");
		break;
		
		case "FalseTrace_wife_31":
			dialog.text = "Mocskos gazember! Sikerült mind a négyet megölnie! Hihetetlen!";
			link.l1 = "Nem számítottál ilyen fordulatra, Katerine? Engem nehéz megölni. Elég jól játszod a kettôs játékot, azt kell mondanom!";
			link.l1.go = "FalseTrace_wife_32";
		break;
		
		case "FalseTrace_wife_32":
			dialog.text = "Megölted az emberemet. Tényleg azt hiszed, hogy hagyom, hogy tovább lélegezz?! Azt hitted, hogy Adam halála kielégít engem? Nem! Nem hagyod el ezt a helyet. Van egy hajó nem messze ettôl a szigettôl, el fogja süllyeszteni veled együtt a vén csövedet is!\nMost, csinálj velem, amit akarsz.";
			link.l1 = "Nem megmondtam neked, kedvesem, hogy elveszíted a fejed, ha becsapsz? Ravasz ördög! Holtan sokkal kevésbé leszel veszélyes. Ez a csinos fej máris golyót kap...";
			link.l1.go = "FalseTrace_wife_33";
			link.l2 = "Sajnállak, Katerine. A bosszúvágyad végül nem tett jót neked. A sorsodra hagylak - ezen a szigeten maradsz. Azt hiszem, a helyi halászok hamarosan megtalálnak és Hispaniolára visznek. És az Úr ítéljen meg minket minden tettünkért...";
			link.l2.go = "FalseTrace_wife_35";
		break;
		
		case "FalseTrace_wife_33":
			dialog.text = "Neked kellene imádkoznod, te szörnyeteg! Gyilkos! Segítség! Baszd meg...";
			link.l1 = "Eleget hallottam.";
			link.l1.go = "FalseTrace_wife_34";
		break;
		
		case "FalseTrace_wife_34":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_SetImmortal(npchar, false);
			//  belamour legendary edition если не надет пистоль или мушкет, то выдадим строевой -->
			if(!CheckAttribute(pchar,"equip."+GUN_ITEM_TYPE))
			{
				GiveItem2Character(pchar, "pistol1");
				EquipCharacterbyItem(pchar, "pistol1");
			}
			// <-- legendary edition
			LAi_ActorAnimation(pchar, "shot", "FalseTrace_CaterinaKilled", 1.0);
		break;
		
		case "FalseTrace_wife_35":
			dialog.text = "Fulladj meg! Zuhanjon a hajód a sziklákhoz! Hulljon...";
			link.l1 = "Viszlát, Katerine.";
			link.l1.go = "FalseTrace_wife_36";
		break;
		
		case "FalseTrace_wife_36":
			DialogExit();
			sld = characterFromID("FalseTraceWife"); 
			sld.lifeday = 0;
			LAi_ActorGoToLocation(npchar, "goto", "goto33", "none", "", "", "", -1);
			LAi_SetPlayerType(pchar);
			chrDisableReloadToLocation = false;
			LAi_LocationDisableOfficersGen("Mayak7", false);//офицеров пускать
			locations[FindLocation("Mayak7")].DisableEncounters = false;//энкаунтеры открыть
			AddQuestRecord("FalseTrace", "25");
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			OfficersReaction("good");
		break;
		
		case "FalseTrace_Bandits":
			dialog.text = "Itt van Ádám gyilkosa! Katerine-nek igaza volt, ez a fattyú azért jött, hogy kirabolja a rejtekhelyet!";
			link.l1 = "Micsoda? Katerine? Ki vagy te?";
			link.l1.go = "FalseTrace_Bandits_1";
		break;
		
		case "FalseTrace_Bandits_1":
			dialog.text = "Kik vagyunk mi? Adam Rayner barátai vagyunk, akit maga ölt meg. Ô volt a testvériségünk feje. Most én vagyok a fônök, a nevem "+GetFullName(npchar)+", és megbüntetlek a fônököm megöléséért és a felesége ellen elkövetett erôszakért.";
			link.l1 = "Erôszakért? Mi a fenérôl beszélsz?";
			link.l1.go = "FalseTrace_Bandits_2";
		break;
		
		case "FalseTrace_Bandits_2":
			dialog.text = "Hátba szúrtad Ádámot, te mocskos áruló, kényszerítetted a feleségét, hogy elmondja neked, hol tartja Ádám az aranyát, aztán otthagytad szegény asszonyt meghalni egy sivatagi parton\nDe túlélte, arra kért minket, hogy segítsünk neki, hogy helyrehozzunk egy rosszat. Már napok óta várunk rád. És itt vagy, te szemétláda!";
			link.l1 = "Ha-ha! Határozottan Katerine stílusa... Most figyelj, én öltem meg Ádámot, ez igaz, de azért tettem, mert a felesége valójában megkért, hogy öljem meg. Ez bosszú volt a szeretôje haláláért. Elmondta, hol találom a rejtekhelyet, hogy visszafizesse nekem...";
			link.l1.go = "FalseTrace_Bandits_3";
		break;
		
		case "FalseTrace_Bandits_3":
			dialog.text = "Ne rágalmazd szegény özvegyet, te szemétláda! Akkor miért jött volna hozzánk? Felajánlotta, hogy az életedért cserébe minden aranyat magunkhoz veszünk. Nem érméket akar, hanem a halálodat! Szent halált a férj haláláért!\nDe esküszöm, hogy nem fog szegénységben meghalni, ez olyan igaz, mint a nevem "+GetFullName(npchar)+", és hogy itt az ideje, hogy meghalj, gyáva!";
			link.l1 = "Szent szar, micsoda dicsôséges beszéd. Ó, ott van, alig várja, hogy személyesen nézze meg ezt a komédiát... Uraim?";
			link.l1.go = "FalseTrace_Bandits_4";
		break;
		
		case "FalseTrace_Bandits_4":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешим драться
			DialogExit();
			for (i=1; i<=4; i++)
			{
				sld = characterFromId("Adam_bandit_"+i);	
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "FalseTrace_BanditsAfterFight");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "FalseTrace_Remove1":
			dialog.text = "Maga olyan zavaros, kapitány! Elveszíteni egy ezüsttel teli flottát... Hibát követtem el, amikor számítottam rád. Viszontlátásra!";
			link.l1 = "Isten veled, Adam.";
			link.l1.go = "FalseTrace_Remove2";
		break;
		
		case "FalseTrace_Remove2":
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 15);
		break;
		
		case "FalseTrace_Remove_exit":
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "FalseTraceWife_Remove", 15);
		break;
		
		case "FalseTrace_Remove2":
			dialog.text = "Figyelmeztettelek, kapitány, csak két hetünk volt! Mostanra a kancsal Solly már biztosan elvitte az összes zsákmányt. Nem az én hibám, hogy ilyen suta vagy. Isten veled!";
			link.l1 = "Igen, az én hibám. Isten veled, remélem, nem találkozunk többé, te csak balszerencsét hozol nekem.";
			link.l1.go = "FalseTrace_Remove_exit";
		break;
		
		case "FalseTrace_Solly":
			dialog.text = "Heh! Végre! Belefáradtunk a várakozásba, és ezek az átkozott szúnyogok... Várjatok... És hol van Solly? Nem értem...";
			link.l1 = "Solly nem jön ide. Az ô nevében cselekszem... Szóval vagy ideadod az aranyat, vagy meghalsz.";
			link.l1.go = "FalseTrace_Solly_1";
		break;
		
		case "FalseTrace_Solly_1":
			dialog.text = "Argh! Majd meglátjuk! Rám, fiúk! Fegyverbe!";
			link.l1 = "Micsoda ostoba módja a halálnak, jöjjenek hát a dögevôk!";
			link.l1.go = "FalseTrace_Solly_2";
			AddDialogExitQuestFunction("FalseTrace_SollyBonanzaAdd");
		break;
		
		case "FalseTrace_Solly_2":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешим драться
			DialogExit();
			for (i=1; i<=6; i++)
			{
				sld = characterFromId("FTEnemy_crew_"+i);	
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "FalseTrace_SollyAfterFight");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "FalseTrace_GoldShip":
			dialog.text = "Teljesítetted az alku rád esô részét, kapitány. Köszönöm, hogy bíztál bennem. Ne aggódjatok Adam miatt, a megfelelô helyre fogom szállítani. Meg fogja kapni, amit megérdemel.";
			link.l1 = "Nem érdekel Adam. És mi lesz az ígéreteddel, ami a hajóra vonatkozik?";
			link.l1.go = "FalseTrace_GoldShip_1";
		break;
		
		case "FalseTrace_GoldShip_1":
			if (sti(pchar.basenation == HOLLAND) || sti(pchar.basenation == SPAIN))
			{
				pchar.questTemp.FalseTrace.ShipNation = ENGLAND;
				pchar.questTemp.FalseTrace.ShipCity = "PortRoyal";
			}
			else
			{
				pchar.questTemp.FalseTrace.ShipNation = SPAIN;
				pchar.questTemp.FalseTrace.ShipCity = "Maracaibo";
			}
			dialog.text = "Igen, igen, persze. Lássuk csak, mától számolva... Igen... 12-14 nap múlva a "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.ShipCity+"Gen")+" egy nehéz, aranyérccel megrakott gálya fog kihajózni Európába. Egyetlen fregatt vagy korvett fogja védeni\nSzóval készüljetek fel, gazdag zsákmány, de foga van. Bár biztos vagyok benne, hogy sikerülni fog, az én ellenállásomat elég könnyen szétzúztátok... Két héten belül el kell érned "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.ShipCity+"Gen")+" és csapdát kell készítened\nNe feledd, hogy a célpontod egy nehéz gálya egyetlen konvojhajóval. Azt hiszem, ez az. A többi a te kezedben van.";
			link.l1 = "Értem... Nos, "+pchar.questTemp.FalseTrace.CapName+", viszlát. Talán sok szerencsét és boldog életet kellene kívánnom neked Katerine-nel? Remélem, hogy ti ketten jól megvagytok. Kár, hogy ilyen szomorú körülmények között találkoztunk.";
			link.l1.go = "FalseTrace_GoldShip_2";
		break;
		
		case "FalseTrace_GoldShip_2":
			dialog.text = "Köszönöm, kapitány. Ahogy már mondtam, önben van némi nemesség. Remélem, hogy helyesen következtetsz arra, hogy a becsületes tettek több hasznot hoznak, mint a becstelenek. Szentelje magát a nemzetének szolgálatára, és nagyszerû tengerész lesz belôle.";
			link.l1 = "Gondolkodni fogok a szavaidon. Nos, most már viszlát!";
			link.l1.go = "FalseTrace_GoldShip_3";
		break;
		
		case "FalseTrace_GoldShip_3":
			DialogExit();
			locations[FindLocation(pchar.questTemp.FalseTrace.TargetShore)].DisableEncounters = false; //энкаутеры открыть
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "FalseTraceDouble_Remove", -1);
			pchar.quest.False_Trace_6.win_condition.l1 = "Timer";
			pchar.quest.False_Trace_6.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.False_Trace_6.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 14);
			pchar.quest.False_Trace_6.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 14);
			pchar.quest.False_Trace_6.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 14);
			pchar.quest.False_Trace_6.function = "CreateFalseTraceGoldShipOnMap";
			AddQuestRecord("FalseTrace", "19");
			AddQuestUserData("FalseTrace", "sCity", XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.ShipCity+"Gen"));
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
