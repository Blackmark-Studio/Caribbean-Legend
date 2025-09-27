void ProcessDialogEvent()
{
	ref NPChar, TempChar, sld;
	aref Link, Diag;
	
	int i, iTemp;
	string sTemp, sTemp1;
	string sGroup;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		// -----------------------------------Диалог первый - первая встреча
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
		break;

		case "First time":
			chrDisableReloadToLocation = false;
			//Lai_SetPlayerType(pchar);
			
			dialog.text = GetFullName(PChar) + "! "+"Már régóta kerestünk téged, és végre a miénk vagy.";
			Link.l1 = "Ki vagy te és mit akarsz tôlem?";
			Link.l1.go = "meeting"; 
			
			PChar.GenQuest.HunterStart = true;
		break;

		case "meeting":
			dialog.text = XI_ConvertString(Nations[sti(NPChar.nation)].Name) + " tisztességes vérdíjat tûztek ki a fejedre, el kell juttatnunk téged bármelyik kolóniájára, és megkapjuk a pénzt, mindegy, hogy élve vagy halva.";
			Link.l1 = "Figyelj, fizetek neked, ha békén hagysz.";
			Link.l1.go = "Cost_Head"; 
            // boal 08.04.04 -->
            if (GetSummonSkillFromNameToOld(PChar, SKILL_SNEAK) > 2 || bBettaTestMode)
            {
    			TempChar = characterFromID("Bug Fixer");
    			SetRandomNameToCharacter(TempChar);
    			Link.l2 = ""+ GetSexPhrase("Elnézést, de biztos téved. Én vagyok "+ GetFullName(TempChar) + " - egy jól ismert kereskedô ezeken a földeken.","Elnézést, de biztos téved. Én csak egy egyszerû lány vagyok, és az apám "+ GetFullName(TempChar) + " - egy jól ismert kereskedô ezeken a földeken.") +".";
    			Link.l2.go = "lier";
			}
            Link.l3 = "Rendben, kipróbálhatod a szerencsédet, ha úgy kívánod.";
			Link.l3.go = "battle";
		break;
        
        case "lier":
            if (GetSummonSkillFromName(pchar, SKILL_SNEAK) > rand(150) || bBettaTestMode)
            {
                dialog.text = "Ó! Lehet, hogy valóban tévedünk. Kérem, bocsásson meg nekünk, "+ GetAddress_Form(NPChar) + ".";
                Link.l1 = "Megesik az ilyesmi, ne aggódjatok emiatt...";
                Link.l1.go = "lier_2";
                AddCharacterExpToSkill(pchar, SKILL_SNEAK, 100);
            }
            else
            {
                dialog.text = "Szerintem hazudik!";
                Link.l1 = "Figyelj, fizetek neked, ha békén hagysz.";
			    Link.l1.go = "Cost_Head";
			    Link.l2 = "Rendben, kipróbálhatod a szerencsédet, ha úgy kívánod.";
			    Link.l2.go = "battle";
			    AddCharacterExpToSkill(pchar, SKILL_SNEAK, 50);
            }
            
        break;
        
        case "lier_2":
            AddDialogExitQuest("GoAway_Hunters_Land");
            DialogExit();
        break;
        // boal <--
        
        case "battle":
            AddDialogExitQuest("Battle_Hunters_Land");    // BOAL Весь код я перенес сюда по всем нациям, просто не переименовал
            DialogExit();
        break;

        case "Cost_Head2":
            AddMoneyToCharacter(pchar, -sti(PChar.HunterCost));

            AddDialogExitQuest("GoAway_Hunters_Land"); 
            DialogExit();
        break;

        case "Cost_Head":
			dialog.text = "Azt hiszem, a " + PChar.HunterCost + " pezó megfelel nekünk.";
            if(makeint(Pchar.money) < sti(PChar.HunterCost))
            {
                Link.l1 = "De nekem nincs ennyi pénzem.";
                Link.l1.go = "NoMoney";
            }else{
                Link.l1 = "Itt a pénzed, vedd el és tûnj el.";
                Link.l1.go = "Cost_Head2";
                Link.l2 = "Egy ilyen összeget adni egy ilyen gazembernek, mint te... Azt hiszem, inkább kibelezlek titeket itt helyben!";
                Link.l2.go = "battle";
            }
		break;

        case "NoMoney":
			dialog.text = "Ebben az esetben a beszélgetésünknek vége!";
			Link.l1 = "Soha nem kaptok el élve.";
			Link.l1.go = "battle"; 
		break;
		
		case "TreasureHunter":
			dialog.text = "Várj, "+ GetSexPhrase("pajtás","lass") +"... Szerintem valami érdekes van nálad. A barátoknak meg kell osztaniuk egymással a talált kincseket, nem gondolod?";
            Link.l1 = "Figyelj, fizetek neked, ha békén hagysz.";
			Link.l1.go = "Cost_Head";
            // boal 08.04.04 -->
            if (GetSummonSkillFromNameToOld(PChar, SKILL_SNEAK) > 3)
            {
    			TempChar = characterFromID("Bug Fixer");
    			SetRandomNameToCharacter(TempChar);
    			Link.l2 = ""+ GetSexPhrase("Elnézést, de biztos téved. Én "+ GetFullName(TempChar) + " vagyok - jól ismert polgár ezeken a földeken, de biztosan nem kincskeresô.","Elnézést, de biztos téved. Én csak egy egyszerû lány vagyok, és nem kincskeresô. Az apám pedig "+ GetFullName(TempChar) + " - közismert polgár ezeken a földeken") +"!";
    			Link.l2.go = "TreasureHunterLier";
			}
            Link.l3 = "Nos, úgy tûnik, itt az ideje, hogy a fejek elváljanak a testüktôl.";
			Link.l3.go = "battle";
		break;
		
		case "TreasureHunterLier":
            if (GetSummonSkillFromName(pchar, SKILL_SNEAK) > rand(150))
            {
                dialog.text = "Ó! Akkor valóban tévedhetünk. Kérem, bocsásson meg nekünk, "+ GetAddress_Form(NPChar)+".";
                Link.l1 = "Megtörténik, ne aggódjatok emiatt...";
                Link.l1.go = "lier_2";
                AddCharacterExpToSkill(pchar, SKILL_SNEAK, 100);
            }
            else
            {
                dialog.text = "Szerintem hazudik!";
			    Link.l1 = "Akkor hallgassátok a pengém dalát.";
			    Link.l1.go = "battle";
			    AddCharacterExpToSkill(pchar, SKILL_SNEAK, 50);
            }
        break;
		
		case "TreasureCaptain":
			dialog.text = LinkRandPhrase("Szóval te vagy az, aki elvitte a kincses térképemet! Azt hiszem, haver, itt az ideje, hogy visszaadj mindent, amit elvettél...","Ó, egy rivális! Nem jutsz messzire, lelassít a kincseim súlya...","Huh, végre utolértelek! Minden kincs ebben a barlangban az enyém, érted? Most pedig ürítsd ki a zsebeidet, haver!");
			Link.l1 = LinkRandPhrase("Itt az ideje, hogy találkozz a pengémmel, haver!","A kincseid? Úgy értetted, hogy a tieid voltak, 'mert most már az enyémek!","Inkább kiürítem a gyomrod a pengémmel, haver.");
			Link.l1.go = "TreasureCaptain_fight"; 
		break;
		
		case "TreasureCaptain_fight":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться // patch-6
			for(i=1; i<=4; i++)
			{
				sld = characterFromId("Treasure_sailor_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "TreasureOfficer":
			dialog.text = LinkRandPhrase("Tehát az ezredesnek igaza volt, a kincs ebben a barlangban volt elrejtve... Ürítsd ki a zsebeidet, tengerész!","Szóval végre utolértünk téged, miután végigjártuk az átkozott dzsungeleket a tövisek és mocsarak között. Most pedig, te szemétláda, mindent átadsz nekünk...","Hé, tengerész! Annak a kalóznak a kincsei a miénk, úgyhogy vedd el tôlük a mocskos kezed!");
			Link.l1 = LinkRandPhrase("Bizonyára nem ezt vártam egy katonatiszttôl! De rendben, akkor is megtanítom a leckét...","Nézzétek csak, egy kalóz tiszti egyenruhában...","Valóban, a katonák és a kalózok nem sokban különböznek manapság...");
			Link.l1.go = "TreasureOfficer_fight"; 
		break;
		
		case "TreasureOfficer_fight":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться // patch-6
			for(i=1; i<=4; i++)
			{
				sld = characterFromId("Treasure_soldier_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		// генератор "A reason to hurry"
		case "ReasonToFast_THunter_1":
			if(CheckAttribute(pchar,"GenQuest.CannotWait"))	DeleteAttribute(pchar, "GenQuest.CannotWait");
			dialog.text = "És itt jön az aranyunk. Legalább nem volt hiábavaló a várakozásunk.";
			link.l1 = RandPhraseSimple("Mirôl beszélnek, uraim? Én a Holland Nyugat-indiai Társaság képviselôje vagyok, és csak átutazóban vagyok itt! Azért álltam meg, hogy megcsodáljam a partra nyíló kilátást!","Attól tartok, összetévesztettek valakivel. Én "+ GetSexPhrase("Francua Marie Paganel, ","Maria-Theresa, ") +"természettudós vagyok. Itt gyûjtöm a helyi flóra mintáit. Akarod megnézni a yucca levelekbôl álló gyûjteményemet? Több nagyon érdekes példányom is van!");
			link.l1.go = "ReasonToFast_THunter_2";
			link.l2 = "Mit szeretnél? Ne állj az utamba!";
			link.l2.go = "ReasonToFast_THunter_2";
		break;
		
		case "ReasonToFast_THunter_2":
			ReasonToFast_ClearTreasureBox(pchar.questTemp.ReasonToFast.Treasure.Location);
			dialog.text = "Jaj ne, " + GetSexPhrase("kedves barátom","szép lányom") + ". Ez nem fog mûködni. Biztosan tudjuk, hogy a " + GetName( pchar.questTemp.ReasonToFast.mapIdx, pchar.questTemp.ReasonToFast.map, NAME_GEN) +"térkép a tiéd volt. És olyan zsugori volt, hogy a pénzzel teli ládái belülrôl törtek szét. Szóval nem fogunk üres kézzel távozni.";
			link.l1 = "Igazad van. A ládák valóban tele voltak. De nem fogjátok megkapni ôket. Megpróbálhatod meglátogatni azt a barlangot, pár lyukas vödörnek még ott kell lennie.";
			link.l1.go = "ReasonToFast_THunter_3";
			if(ReasonToFast_CheckTreasureQty("icollection", sti(pchar.questTemp.ReasonToFast.p8)) >= sti(pchar.questTemp.ReasonToFast.p8) 
				&& ReasonToFast_CheckTreasureQty("Chest", sti(pchar.questTemp.ReasonToFast.p7)) >= sti(pchar.questTemp.ReasonToFast.p7))
			{
				link.l2 = "Igazad van. Megkaphatod a kincsedet. Csak azt tartsd észben, hogy nem leszel boldog tôle, hiszen vérrel van bemocskolva.";
				link.l2.go = "ReasonToFast_THunter_4";
			}	
		break;
		
		case "ReasonToFast_THunter_3":
			dialog.text = ""+ GetSexPhrase("Kapitány, maga túl fiatal a halálhoz, nem igaz...","Heh, kislány, túl fiatal vagy a halálhoz, nem igaz...") +"...";
			link.l1 = "Valójában nem fogok meghalni!";
			link.l1.go = "ReasonToFastTHunter_Fight";
		break;
		
		case "ReasonToFast_THunter_4":
			dialog.text = "Ezek egy értelmes ember szavai!";
			link.l1 = "Átok rád és az összes kincsedre...";
			link.l1.go = "ReasonToFast_THunter_GoAway";
		break;
		
		case "ReasonToFast_THunter_GoAway":			
			iTemp = ReasonToFast_CheckTreasureQty("icollection", sti(pchar.questTemp.ReasonToFast.p8));
			if(iTemp > 0) 
			{
				ReasonToFast_GetTreasure("icollection", iTemp );
				Log_Info(XI_ConvertString("Te adod a tárgyat."));
				PlayStereoSound("interface\important_item.wav");
			}	
			
			iTemp = ReasonToFast_CheckTreasureQty("Chest", sti(pchar.questTemp.ReasonToFast.p7));
			if(iTemp > 0) 
			{
				ReasonToFast_GetTreasure("Chest", iTemp);
				Log_Info(XI_ConvertString("Te adod a tárgyat."));
				PlayStereoSound("interface\important_item.wav");
			}	
			if(pchar.questTemp.ReasonToFast == "GetTreasure")
			{
				AddQuestRecord("ReasonToFast", "24");
				AddQuestUserData("ReasonToFast", "sName", GetName( pchar.questTemp.ReasonToFast.mapIdx, pchar.questTemp.ReasonToFast.map, NAME_GEN));
				CloseQuestHeader("ReasonToFast");	
			}
			DialogExit();	
			AddDialogExitQuest("ReasonToFast_GoAway_Hunters_Land");
		break;
		
		case "ReasonToFastTHunter_Fight":
			sGroup = "LAND_HUNTER";
			sTemp = "LandHunter0";
			iTemp = sti(pchar.HunterCost.Qty);
			chrDisableReloadToLocation = true;
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			for(i = 1; i <= iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, sGroup);
			}
			
			LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(sGroup, "OpenTheDoors"); 
			LAi_group_SetCheck(sGroup, "ReasonToFast_TrHuntersDied");	
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "ReasonToFast_HunterShore1":
			dialog.text = "Hé,"+ GetSexPhrase("haver","lass") +"! " + GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_NOM) + " azt mondta, hogy van valamid számunkra.";
			link.l1 = "Hogy érti ezt?";
			link.l1.go = "ReasonToFast_HunterShore11";
			pchar.quest.ReasonToFast_SetHunterPort_1.over = "yes";
			pchar.quest.ReasonToFast_SetHunterPort_2.over = "yes";
		break;

		case "ReasonToFast_HunterShore11":
			if(pchar.questTemp.ReasonToFast == "GetMap") 
			{
				dialog.text = "Egy térképet " + GetName( pchar.questTemp.ReasonToFast.mapIdx, pchar.questTemp.ReasonToFast.map, NAME_GEN);
				link.l1 = "Fogd és köszönj a " + GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_DAT) + ". Mondd meg neki, hogy hamarosan találkozunk...";
				link.l1.go = "ReasonToFast_HunterShore12_1";
				link.l2 = GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_NOM) + " nagyot téved, ha azt hiszi, hogy gesztenyét húzok neki a tûzbôl.";
				link.l2.go = "ReasonToFast_HunterShore23";
			}
			if(pchar.questTemp.ReasonToFast == "LakeyExitSuccess")
			{
				dialog.text = "Ékszerek, amiket a kormányzótól loptál.";
				if(ReasonToFast_CheckTreasureQty("icollection", sti(pchar.questTemp.ReasonToFast.p8)) >= sti(pchar.questTemp.ReasonToFast.p8) 
					&& ReasonToFast_CheckTreasureQty("Chest", sti(pchar.questTemp.ReasonToFast.p7)) >= sti(pchar.questTemp.ReasonToFast.p7))
				{
					link.l1 = "Fogd és köszönj a " + GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_DAT) + ". Mondd meg neki, hogy hamarosan találkozunk...";
					link.l1.go = "ReasonToFast_HunterShore12_2";
				}	
				link.l2 = GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_NOM) + " nagyot téved, ha azt hiszi, hogy gesztenyét húzok neki a tûzbôl.";
				link.l2.go = "ReasonToFast_HunterShore23";				
			}
			pchar.quest.ReasonToFast_SetHunterPort_1.over = "yes";
			pchar.quest.ReasonToFast_SetHunterPort_2.over = "yes";
			chrDisableReloadToLocation = false;
		break;
		
		case "ReasonToFast_HunterShore12_1":
			TakeNItems(pchar, "mapQuest", -1); 
			AddQuestRecord("ReasonToFast", "20");
			AddQuestUserData("ReasonToFast", "sText", "egy térképet.");
			AddQuestUserData("ReasonToFast", "sName", GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_GEN));
			CloseQuestHeader("ReasonToFast");
			DialogExit();	
			AddDialogExitQuest("ReasonToFast_GoAway_Hunters_Land");
		break;
		
		case "ReasonToFast_HunterShore12_2":
			iTemp = ReasonToFast_CheckTreasureQty("icollection", sti(pchar.questTemp.ReasonToFast.p8));
			if(iTemp > 0) 
			{
				ReasonToFast_GetTreasure("icollection", iTemp );
				Log_Info(XI_ConvertString("Te adod a tárgyat."));
				PlayStereoSound("interface\important_item.wav");
			}	
			
			iTemp = ReasonToFast_CheckTreasureQty("Chest", sti(pchar.questTemp.ReasonToFast.p7));
			if(iTemp > 0) 
			{
				ReasonToFast_GetTreasure("Chest", iTemp);
				Log_Info(XI_ConvertString("Te adod a tárgyat."));
				PlayStereoSound("interface\important_item.wav");
			}			
			AddQuestRecord("ReasonToFast", "20");
			AddQuestUserData("ReasonToFast", "sText", "kincsek");
			AddQuestUserData("ReasonToFast", "sName", GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_GEN));
			CloseQuestHeader("ReasonToFast");
			DialogExit();	
			ReasonToFast_ClearTreasureBox(pchar.questTemp.ReasonToFast.city + "_townhall");
			ReasonToFast_ClearTreasureBox(pchar.questTemp.ReasonToFast.LakeyLocation);
			AddDialogExitQuest("ReasonToFast_GoAway_Hunters_Land");
		break;
		
		case "ReasonToFast_HunterShore2":
			dialog.text = "Hé,"+ GetSexPhrase("haver","lass") +"! " + GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_GEN) + " több kérdésed is van.";
			link.l1 = "És miért ne kérdezné meg ôket egyedül?";
			link.l1.go = "ReasonToFast_HunterShore21";
			chrDisableReloadToLocation = false;
		break;
		
		case "ReasonToFast_HunterShore21":
			dialog.text = "Nem a rangja szerint. Tönkretetted az akciónkat, és miattad vesztettünk " + sti(pchar.questTemp.ReasonToFast.p10) + " pezót. Szóval most már van egy adósságod, amit meg kell fizetned.";
			link.l1 = "Fogd és köszönj a " + GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_DAT) + ". Mondd meg neki, hogy hamarosan találkozunk...";
			link.l1.go = "ReasonToFast_HunterShore22";
			link.l2 = GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_NOM) + " nagyot téved, ha azt hiszi, hogy gesztenyét húzok neki a tûzbôl.";
			link.l2.go = "ReasonToFast_HunterShore23";
		break;
		
		case "ReasonToFast_HunterShore22":
			if(makeint(pchar.money) >= sti(pchar.questTemp.ReasonToFast.p10))
			{
				AddMoneyToCharacter(pchar, -makeint(sti(pchar.questTemp.ReasonToFast.p10)));
				AddQuestRecord("ReasonToFast", "20");
				AddQuestUserData("ReasonToFast", "sText", "pénz");
				AddQuestUserData("ReasonToFast", "sName", GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_GEN));
				DialogExit();	
				AddDialogExitQuest("ReasonToFast_GoAway_Hunters_Land");
			}
			else
			{
				dialog.text = "Ó, neked nincs ennyi pénzed! Nos, döntöttél... ";
				link.l1 = "Már régen...";
				link.l1.go = "ReasonToFastTHunter_Fight";	
				if(pchar.questTemp.ReasonToFast == "LakeyExitSuccess" || pchar.questTemp.ReasonToFast == "LakeyExitFail")
				{
					pchar.quest.ReasonToFast_SetPirateShip.win_condition.l1 = "MapEnter";
					pchar.quest.ReasonToFast_SetPirateShip.function = "ReasonToFast_PreparePirateShip";
				}
			}
		break;
		
		case "ReasonToFast_HunterShore23":
			dialog.text = "Nos, döntöttél...";
			link.l1 = "Már régen...";
			link.l1.go = "ReasonToFastTHunter_Fight";
			if(pchar.questTemp.ReasonToFast == "LakeyExitSuccess" || pchar.questTemp.ReasonToFast == "LakeyExitFail")
			{
				pchar.quest.ReasonToFast_SetPirateShip.win_condition.l1 = "MapEnter";
				pchar.quest.ReasonToFast_SetPirateShip.function = "ReasonToFast_PreparePirateShip";
			}
		break;
		// генератор "A reason to hurry"
	}
}

string GetLocHunterName()
{
	int nLoc = FindLocation(Pchar.location);
	int nFile = LanguageOpenFile("LocLables.txt");
	string ret = "";
	
	if(nFile >= 0) 
	{
		if (CheckAttribute(&locations[nLoc],"islandId"))
		{
			if (locations[nLoc].islandId != "Mein")
			{
				ret = "island of " + LanguageConvertString(nFile, locations[nLoc].islandId);
			}
			else
			{
				ret = "mainland of ";
			}
		}
		//
        if (CheckAttribute(&locations[nLoc],"fastreload"))
		{
			ret += " (" +LanguageConvertString(nFile, locations[nLoc].fastreload + " Town") + ")";
		}
		//ret += LanguageConvertString(nFile, locations[nLoc].id.label);
		LanguageCloseFile( nFile );
	}
	return ret;	
}
