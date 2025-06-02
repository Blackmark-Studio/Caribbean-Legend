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
			
			dialog.text = GetFullName(PChar)+"! "+"Ti stiamo inseguendo da molto tempo, e finalmente sei nostro.";
			Link.l1 = "Chi sei e cosa vuoi da me?";
			Link.l1.go = "meeting"; 
			
			PChar.GenQuest.HunterStart = true;
		break;

		case "meeting":
			dialog.text = XI_ConvertString(Nations[sti(NPChar.nation)].Name)+" ha messo una bella taglia sulla tua testa, dobbiamo consegnarti a una delle sue colonie e ci pagheranno, non importa se sei morto o vivo.";
			Link.l1 = "Ascolta, ti pagherò se mi lasci in pace.";
			Link.l1.go = "Cost_Head"; 
            // boal 08.04.04 -->
            if (GetSummonSkillFromNameToOld(PChar, SKILL_SNEAK) > 2 || bBettaTestMode)
            {
    			TempChar = characterFromID("Bug Fixer");
    			SetRandomNameToCharacter(TempChar);
    			Link.l2 = ""+GetSexPhrase("Mi scusi, ma devi esserti sbagliato. Io sono "+GetFullName(TempChar)+" - un mercante ben noto in queste terre.","Mi scusi, ma devi essere confuso. Sono solo una semplice ragazza, e mio padre è "+GetFullName(TempChar)+"- un mercante ben conosciuto in queste terre.")+".";
    			Link.l2.go = "lier";
			}
            Link.l3 = "Bene, puoi tentare la fortuna, se così desideri.";
			Link.l3.go = "battle";
		break;
        
        case "lier":
            if (GetSummonSkillFromName(pchar, SKILL_SNEAK) > rand(150) || bBettaTestMode)
            {
                dialog.text = "Oh! Potremmo davvero esserci sbagliati. Per favore, perdonaci, "+GetAddress_Form(NPChar)+".";
                Link.l1 = "Succede, non preoccuparti...";
                Link.l1.go = "lier_2";
                AddCharacterExpToSkill(pchar, SKILL_SNEAK, 100);
            }
            else
            {
                dialog.text = "Credo che tu stia mentendo!";
                Link.l1 = "Ascolta, ti pagherò se mi lasci in pace.";
			    Link.l1.go = "Cost_Head";
			    Link.l2 = "Bene, puoi provare la tua fortuna, se lo desideri.";
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
			dialog.text = "Credo che "+PChar.HunterCost+" pesos ci andranno benissimo.";
            if(makeint(Pchar.money) < sti(PChar.HunterCost))
            {
                Link.l1 = "Ma non ho questi soldi.";
                Link.l1.go = "NoMoney";
            }else{
                Link.l1 = "Ecco i tuoi soldi, prendili e sparisci.";
                Link.l1.go = "Cost_Head2";
                Link.l2 = "Dare una somma del genere a canaglie come voi... Credo che preferirei sventrarvi tutti qui sul posto!";
                Link.l2.go = "battle";
            }
		break;

        case "NoMoney":
			dialog.text = "In quel caso, la nostra conversazione è finita!";
			Link.l1 = "Non mi prenderai mai vivo.";
			Link.l1.go = "battle"; 
		break;
		
		case "TreasureHunter":
			dialog.text = "Aspetta, "+GetSexPhrase("compagno","ragazza")+"... Credo che tu abbia qualcosa di interessante con te. Gli amici dovrebbero condividere i tesori trovati tra di loro, non pensi anche tu?";
            Link.l1 = "Ascolta, ti pagherò se mi lasci in pace.";
			Link.l1.go = "Cost_Head";
            // boal 08.04.04 -->
            if (GetSummonSkillFromNameToOld(PChar, SKILL_SNEAK) > 3)
            {
    			TempChar = characterFromID("Bug Fixer");
    			SetRandomNameToCharacter(TempChar);
    			Link.l2 = ""+GetSexPhrase("Mi scusi, ma devi sbagliarti. Io sono "+GetFullName(TempChar)+" - un cittadino ben noto in queste terre, ma certamente non un cercatore di tesori.","Scusami, ma devi sbagliarti. Sono solo una semplice ragazza e non una cercatrice di tesori. E mio padre è "+GetFullName(TempChar)+" - un cittadino ben noto in queste terre")+"!";
    			Link.l2.go = "TreasureHunterLier";
			}
            Link.l3 = "Ebbene, sembra che sia giunto il momento per le vostre teste di separarsi dai loro corpi.";
			Link.l3.go = "battle";
		break;
		
		case "TreasureHunterLier":
            if (GetSummonSkillFromName(pchar, SKILL_SNEAK) > rand(150))
            {
                dialog.text = "Oh! Potremmo davvero esserci sbagliati, allora. Perdonaci, "+GetAddress_Form(NPChar)+".";
                Link.l1 = "Succede, non preoccuparti...";
                Link.l1.go = "lier_2";
                AddCharacterExpToSkill(pchar, SKILL_SNEAK, 100);
            }
            else
            {
                dialog.text = "Credo che tu stia mentendo!";
			    Link.l1 = "Allora ascolta il canto della mia lama.";
			    Link.l1.go = "battle";
			    AddCharacterExpToSkill(pchar, SKILL_SNEAK, 50);
            }
        break;
		
		case "TreasureCaptain":
			dialog.text = LinkRandPhrase("Allora sei tu quello che ha preso la mia mappa del tesoro! Penso, amico, che sia ora di restituire tutto quello che hai preso...","Oh, un rivale! Non arriverai lontano, sei rallentato dal peso dei miei tesori...","Eh, finalmente ti ho raggiunto! Tutti i tesori in questa caverna appartengono a me, capisci? Ora, svuota le tue tasche, amico!");
			Link.l1 = LinkRandPhrase("È ora che tu conosca la mia lama, compagno!","I tuoi tesori? Volevi dire che erano tuoi, perché ora sono miei!","Preferirei svuotare il tuo stomaco con la mia lama, amico.");
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
			dialog.text = LinkRandPhrase("Allora, il colonnello aveva ragione, il tesoro era nascosto in questa grotta... Svota le tasche, marinaio!","Allora finalmente ti abbiamo catturato dopo tutto questo inseguimento attraverso tutte queste maledette giungle tra spine e paludi. Ora, bastardo, ci darai tutto...","Ehi, marinaio! I tesori di quel pirata appartengono a noi, quindi togli le tue sporche mani da loro!");
			Link.l1 = LinkRandPhrase("Certo, non me l'aspettavo da un ufficiale dell'esercito! Ma va bene, ti insegnarò comunque una lezione...","Guardalo, un pirata in uniforme da ufficiale...","Infatti, soldati e pirati non sono poi così diversi di questi tempi...");
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
			dialog.text = "Ecco arrivare il nostro oro. Almeno la nostra attesa non è stata invano.";
			link.l1 = RandPhraseSimple("Di cosa state parlando, signori? Sono un rappresentante della Compagnia Olandese delle Indie Occidentali e sto solo passando di qui! Mi sono fermato per ammirare la vista della costa!","Temere, mi avete confuso con qualcun altro. Io sono "+GetSexPhrase("Francua Marie Paganel, ","Maria-Teresa, ")+"un naturalista. Sto raccogliendo campioni della flora locale qui. Vuoi dare un'occhiata alla mia collezione di foglie di yucca? Ne ho alcune davvero interessanti!");
			link.l1.go = "ReasonToFast_THunter_2";
			link.l2 = "Cosa vuoi?! Stai fuori dal mio cammino!";
			link.l2.go = "ReasonToFast_THunter_2";
		break;
		
		case "ReasonToFast_THunter_2":
			ReasonToFast_ClearTreasureBox(pchar.questTemp.ReasonToFast.Treasure.Location);
			dialog.text = "Oh no, "+GetSexPhrase("mio caro amico","la mia bella ragazza")+". Non funzionerà. Sappiamo con certezza che possedevi la mappa di "+GetName(pchar.questTemp.ReasonToFast.mapIdx,pchar.questTemp.ReasonToFast.map,NAME_GEN)+". E lui era così avaro che i suoi forzieri scoppiavano dall'interno pieni di soldi. Quindi non ce ne andremo a mani vuote.";
			link.l1 = "Hai ragione. I forzieri erano davvero pieni. Ma non li avrai. Potresti provare a visitare quella grotta, dovrebbero ancora esserci un paio di secchi forati.";
			link.l1.go = "ReasonToFast_THunter_3";
			if(ReasonToFast_CheckTreasureQty("icollection", sti(pchar.questTemp.ReasonToFast.p8)) >= sti(pchar.questTemp.ReasonToFast.p8) 
				&& ReasonToFast_CheckTreasureQty("Chest", sti(pchar.questTemp.ReasonToFast.p7)) >= sti(pchar.questTemp.ReasonToFast.p7))
			{
				link.l2 = "Hai ragione. Puoi avere il tuo tesoro. Tieni solo a mente che non ti renderà felice, poiché è macchiato di sangue.";
				link.l2.go = "ReasonToFast_THunter_4";
			}	
		break;
		
		case "ReasonToFast_THunter_3":
			dialog.text = ""+GetSexPhrase("Eh, capitano, sei troppo giovane per morire, non è vero...","Ehi, ragazza, sei troppo giovane per morire, non è vero...")+"...";
			link.l1 = "Infatti, non ho intenzione di morire!";
			link.l1.go = "ReasonToFastTHunter_Fight";
		break;
		
		case "ReasonToFast_THunter_4":
			dialog.text = "Ora queste sono le parole di una persona ragionevole!";
			link.l1 = "Maledizione a te e a tutti quei tesori...";
			link.l1.go = "ReasonToFast_THunter_GoAway";
		break;
		
		case "ReasonToFast_THunter_GoAway":			
			iTemp = ReasonToFast_CheckTreasureQty("icollection", sti(pchar.questTemp.ReasonToFast.p8));
			if(iTemp > 0) 
			{
				ReasonToFast_GetTreasure("icollection", iTemp );
				Log_Info(XI_ConvertString("You give item"));
				PlayStereoSound("interface\important_item.wav");
			}	
			
			iTemp = ReasonToFast_CheckTreasureQty("Chest", sti(pchar.questTemp.ReasonToFast.p7));
			if(iTemp > 0) 
			{
				ReasonToFast_GetTreasure("Chest", iTemp);
				Log_Info(XI_ConvertString("You give item"));
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
			dialog.text = "Ehi,"+GetSexPhrase("compagno","ragazza")+"! "+GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_NOM)+" ha detto che avevi qualcosa per noi.";
			link.l1 = "Cosa intendi?";
			link.l1.go = "ReasonToFast_HunterShore11";
			pchar.quest.ReasonToFast_SetHunterPort_1.over = "yes";
			pchar.quest.ReasonToFast_SetHunterPort_2.over = "yes";
		break;

		case "ReasonToFast_HunterShore11":
			if(pchar.questTemp.ReasonToFast == "GetMap") 
			{
				dialog.text = "Una mappa di "+GetName(pchar.questTemp.ReasonToFast.mapIdx,pchar.questTemp.ReasonToFast.map,NAME_GEN);
				link.l1 = "Prendilo e saluta "+GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_DAT)+". Digli che ci incontreremo presto...";
				link.l1.go = "ReasonToFast_HunterShore12_1";
				link.l2 = GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_NOM)+" è gravemente in errore se pensa che tirerò le castagne dal fuoco per lui.";
				link.l2.go = "ReasonToFast_HunterShore23";
			}
			if(pchar.questTemp.ReasonToFast == "LakeyExitSuccess")
			{
				dialog.text = "Gioielli che hai rubato dal governatore.";
				if(ReasonToFast_CheckTreasureQty("icollection", sti(pchar.questTemp.ReasonToFast.p8)) >= sti(pchar.questTemp.ReasonToFast.p8) 
					&& ReasonToFast_CheckTreasureQty("Chest", sti(pchar.questTemp.ReasonToFast.p7)) >= sti(pchar.questTemp.ReasonToFast.p7))
				{
					link.l1 = "Prendilo e saluta "+GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_DAT)+". Dìgli che ci incontreremo presto...";
					link.l1.go = "ReasonToFast_HunterShore12_2";
				}	
				link.l2 = GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_NOM)+" è gravemente in errore se pensa che tirerò le castagne dal fuoco per lui.";
				link.l2.go = "ReasonToFast_HunterShore23";				
			}
			pchar.quest.ReasonToFast_SetHunterPort_1.over = "yes";
			pchar.quest.ReasonToFast_SetHunterPort_2.over = "yes";
			chrDisableReloadToLocation = false;
		break;
		
		case "ReasonToFast_HunterShore12_1":
			TakeNItems(pchar, "mapQuest", -1); 
			AddQuestRecord("ReasonToFast", "20");
			AddQuestUserData("ReasonToFast", "sText", "a map of");
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
				Log_Info(XI_ConvertString("You give item"));
				PlayStereoSound("interface\important_item.wav");
			}	
			
			iTemp = ReasonToFast_CheckTreasureQty("Chest", sti(pchar.questTemp.ReasonToFast.p7));
			if(iTemp > 0) 
			{
				ReasonToFast_GetTreasure("Chest", iTemp);
				Log_Info(XI_ConvertString("You give item"));
				PlayStereoSound("interface\important_item.wav");
			}			
			AddQuestRecord("ReasonToFast", "20");
			AddQuestUserData("ReasonToFast", "sText", "treasures");
			AddQuestUserData("ReasonToFast", "sName", GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_GEN));
			CloseQuestHeader("ReasonToFast");
			DialogExit();	
			ReasonToFast_ClearTreasureBox(pchar.questTemp.ReasonToFast.city + "_townhall");
			ReasonToFast_ClearTreasureBox(pchar.questTemp.ReasonToFast.LakeyLocation);
			AddDialogExitQuest("ReasonToFast_GoAway_Hunters_Land");
		break;
		
		case "ReasonToFast_HunterShore2":
			dialog.text = "Ehi,"+GetSexPhrase("compagno","ragazza")+"! "+GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_GEN)+" ha diverse domande per te.";
			link.l1 = "E perché non dovrebbe chiederlo da solo?";
			link.l1.go = "ReasonToFast_HunterShore21";
			chrDisableReloadToLocation = false;
		break;
		
		case "ReasonToFast_HunterShore21":
			dialog.text = "Non secondo il suo rango. Hai rovinato la nostra operazione e abbiamo perso "+sti(pchar.questTemp.ReasonToFast.p10)+" pesos a causa tua. Quindi ora hai un debito da pagare.";
			link.l1 = "Prendilo e saluta "+GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_DAT)+". Dìgli che ci incontreremo presto...";
			link.l1.go = "ReasonToFast_HunterShore22";
			link.l2 = GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_NOM)+" è gravemente in errore se pensa che tirerò le castagne dal fuoco per lui.";
			link.l2.go = "ReasonToFast_HunterShore23";
		break;
		
		case "ReasonToFast_HunterShore22":
			if(makeint(pchar.money) >= sti(pchar.questTemp.ReasonToFast.p10))
			{
				AddMoneyToCharacter(pchar, -makeint(sti(pchar.questTemp.ReasonToFast.p10)));
				AddQuestRecord("ReasonToFast", "20");
				AddQuestUserData("ReasonToFast", "sText", "money");
				AddQuestUserData("ReasonToFast", "sName", GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_GEN));
				DialogExit();	
				AddDialogExitQuest("ReasonToFast_GoAway_Hunters_Land");
			}
			else
			{
				dialog.text = "Oh, non hai così tanti soldi! Beh, hai fatto la tua scelta... ";
				link.l1 = "Molto tempo fa...";
				link.l1.go = "ReasonToFastTHunter_Fight";	
				if(pchar.questTemp.ReasonToFast == "LakeyExitSuccess" || pchar.questTemp.ReasonToFast == "LakeyExitFail")
				{
					pchar.quest.ReasonToFast_SetPirateShip.win_condition.l1 = "MapEnter";
					pchar.quest.ReasonToFast_SetPirateShip.function = "ReasonToFast_PreparePirateShip";
				}
			}
		break;
		
		case "ReasonToFast_HunterShore23":
			dialog.text = "Ebbene, hai fatto la tua scelta...";
			link.l1 = "Molto tempo fa...";
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
