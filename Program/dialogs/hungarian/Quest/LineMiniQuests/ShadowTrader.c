// Бесчестный конкурент
void ProcessDialogEvent()
{
	ref sld, NPChar;
	aref Link, NextDiag;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Ez egy bogár. Szólj a fejlesztôknek.";
			link.l1 = "Persze!";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "ShadowGuarder":
			dialog.text = "Mire van szükséged?";
			link.l1 = "Ön "+pchar.questTemp.Shadowtrader.Guardername+"? A helyi kereskedô küldött. Türelmetlenül várja a jelenlétét ebben a pillanatban.";
			link.l1.go = "ShadowGuarder_1";
			DelLandQuestMark(npchar);
		break;
	
		case "ShadowGuarder_1":
			dialog.text = "A-ah, de én itt vártam rá! Azt mondták, hogy egy kocsmába fog jönni! Sajnálom, de azonnal indulok.";
			link.l1 = "Rendben van!";
			link.l1.go = "ShadowGuarder_2";
		break;
	
		case "ShadowGuarder_2":
			DialogExit();
			chrDisableReloadToLocation = true;
			sld = characterFromId("ShadowGuarder");	
			LAi_SetStayType(sld);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(sld, pchar.questTemp.Shadowtrader.City + "_tavern", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1_back", pchar.questTemp.Shadowtrader.City +"_store", "goto", "goto2", "OpenTheDoors", 6);
			pchar.questTemp.Shadowtrader = "begin";
			AddLandQuestMark(characterFromId("BasTer_trader"), "questmarkmain");
		break;
	
		case "ShadowAgent":
			dialog.text = "Jó estét, kapitány. Akarsz valami olcsó árut venni, heh? Kövessetek!";
			link.l1 = "Menj elôre.";
			link.l1.go = "ShadowAgent_1";
		break;
	
		case "ShadowAgent_1":
			DeleteAttribute(pchar, "questTemp.Shadowtrader.SeekTrader");
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "houseS4", "CommonFlamHouse", "barmen", "stay", "Shadow_inRoom", 40);
		break;
	
		case "ShadowTrader":
			dialog.text = "Jó estét, uram. Örülök, hogy egy új ügyféllel találkozom, ha! Hadd mutatkozzam be: " + GetFullName(npchar) + "vagyok. Biztosíthatom, hogy nálam a legolcsóbb az áru a városban.";
			link.l1 = "Végre találkoztunk..." + npchar.name + ". Azt hiszem, csalódást fogok okozni: Nem azért kerestelek, hogy cseréljünk, hanem hogy véget vessünk a mocskos üzletednek. Egy fontos embernek voltál a nyakán. A fájdalom olyan nagy lett, hogy mindenáron le akarja állítani magát... minden eszközzel.";
			link.l1.go = "ShadowTrader_1";
			if (IsCharacterPerkOn(pchar, "Trustworthy"))
			{
				notification("Megbízható", "Trustworthy");
				link.l2 = "Állj meg ott, bûnözô söpredék! Nem tudtad, hogy a kereskedelmi vállalkozás mûködtetéséért adót kell fizetni? Senki sem szegheti meg a törvényt az én felügyeletem alatt! " + GetFullName(npchar) + ", megszegtétek a törvényt és a lopott árutok mostantól elveszett! Fegyveres katonák állnak mögöttem az ajtó elôtt, úgyhogy meg se próbáljon hülyét játszani!";
				link.l2.go = "ShadowTrader_2";
			}
			AddLandQuestMark(characterFromId("BasTer_trader"), "questmarkmain");
		break;
	
		case "ShadowTrader_1":
			dialog.text = "Tényleg? Tényleg? Nem számítottam rá... Ki az ördög vagy te?! Ez egy csapda! Azt hiszem, tudom, ki a felelôs ezért! Bármi áron... fiúk, öljétek meg!";
			link.l1 = "Táncoljunk, gazember!";
			link.l1.go = "ShadowTrader_fight";
			NextDiag.currentnode = "ShadowTrader_6";
		break;
	
	case "ShadowTrader_2":
		dialog.text = "Ó, Istenem... biztos úr, figyeljen! Kössünk egy üzletet. Te egy bölcs és irgalmas ember vagy! Fizetek 5000 darab pesot, és te hagysz minket megszökni a második emeleten keresztül. Az árut is elviszed, szükséged van rá, igaz? Miért lenne szükséged rám? Azonnal elhagyom a várost, és senki sem lát minket többé. Te pedig megkapod a pénzed. Mit gondol, biztos úr?";
		link.l1 = "Tényleg azt hiszed, te szemétláda, hogy egy ilyen jelentéktelen összegért megszegem a kötelességemet?";
		link.l1.go = "ShadowTrader_3";
		break;
	
	case "ShadowTrader_3":
		dialog.text = "Rendben, rendben, biztos úr, vigyen el mindent, amim van - 10,000 pezó. Ez mindenem, esküszöm!";
		link.l1 = "Hm... Ha letartóztatom, az összes pénzét elkobozzuk... Rendben van! Ezt a csempészállomást bezárjuk, és minden árut elkobzunk... Add ide az érmét és tûnj el. Ne mutatkozz itt többet!";
		link.l1.go = "ShadowTrader_4";
		break;
		
	case "ShadowTrader_4":
			dialog.text = "Köszönöm, köszönöm, köszönöm, köszönöm, biztos úr! Itt van a pénze, és nem lát itt többé. Gyerünk, menjünk!";
			link.l1 = "Kifelé, vagy le kell tartóztatnom!";
			link.l1.go = "ShadowTrader_escape";
		break;
	
		case "ShadowTrader_fight":
			LAi_SetPlayerType(pchar);
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("ShadowAgent_"+i);	
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				sld.nation = PIRATE;
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "ShadowTrader_afterfight");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
	
		case "ShadowTrader_escape"://напугали
			AddMoneyToCharacter(pchar, 10000);
			LAi_SetPlayerType(pchar);
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("ShadowAgent_"+i);	
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "reload3", "none", "", "", "", 7.0);
			}
			sld = characterFromID("ShadowTrader"); 
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload3", "none", "", "", "", 7.0);
			DialogExit();
			DoQuestFunctionDelay("ShadowTrader_final", 9.0);
			pchar.questTemp.Shadowtrader.End.Escape = "true";
			AddQuestRecord("Shadowtrader", "8");
			AddCharacterExpToSkill(pchar, "Leadership", 200);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 250);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 300);//скрытность
		break;
	
		case "ShadowTrader_6":
			dialog.text = "Ah! Kegyelem, ne ölj meg! Odaadom neked mindenemet!";
			link.l1 = "A hatóságok elkobozzák az összes vagyonodat. Tényleg azt hiszed, hogy megkegyelmezek neked azok után, ami itt történt?";
			link.l1.go = "ShadowTrader_7";
		break;
	
		case "ShadowTrader_7":
			dialog.text = "I... Neked adom az összes pénzemet és minden vagyonom! Csak engedjetek el! Még ma elhagyom a szigetet, és soha többé nem fogsz itt látni!";
			link.l1 = "Rendben van. Adj nekem mindent, ami nálad van, és tûnj el. És soha többé ne próbálj meg itt üzletelni - legközelebb nem kímélem a szánalmas életedet, te rabló.";
			link.l1.go = "ShadowTrader_free";
			link.l2 = "Kizárt, te szemétláda, nem fogsz megvenni. A te fajtáddal csak hideg acél és forró ólom tud elbánni!";
			link.l2.go = "ShadowTrader_killed";
		break;
		
		case "ShadowTrader_free"://отпустили
			AddMoneyToCharacter(pchar, 20550);
			TakeNItems(pchar, "jewelry1", rand(5));
			TakeNItems(pchar, "jewelry2", rand(20));
			TakeNItems(pchar, "jewelry5", rand(20));
			PlaySound("interface\important_item.wav");
			Log_Info("Kaptál tárgyakat");
			LAi_SetPlayerType(pchar);
			sld = characterFromID("ShadowTrader"); 
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload3", "none", "", "", "", 5.0);
			DialogExit();
			DoQuestFunctionDelay("ShadowTrader_final", 7.0);
			pchar.questTemp.Shadowtrader.End.Free = "true";
			AddQuestRecord("Shadowtrader", "9");
			ChangeCharacterComplexReputation(pchar,"nobility", 5); 
			AddComplexSelfExpToScill(70, 70, 70, 70);
			AddCharacterExpToSkill(pchar, "Leadership", 100);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
		break;
	
		case "ShadowTrader_killed":
			DialogExit();
			LAi_SetImmortal(npchar, false);
			LAi_SetActorType(pchar);
			//  belamour legendary edition если не надет пистоль или мушкет, то выдадим строевой -->
			if(!CheckAttribute(pchar,"equip."+GUN_ITEM_TYPE))
			{
				GiveItem2Character(pchar, "pistol1");
				EquipCharacterbyItem(pchar, "pistol1");
			}
			// <-- legendary edition
			LAi_ActorAnimation(pchar, "Shot", "ShadowTrader_killed_end", 1.3);
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
