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
			
			dialog.text = GetFullName(PChar)+"! "+"Śledziliśmy cię już od dłuższego czasu, i w końcu cię dopadliśmy.";
			Link.l1 = "Kim jesteście i czego ode mnie chcecie?";
			Link.l1.go = "meeting"; 
			
			PChar.GenQuest.HunterStart = true;
		break;

		case "meeting":
			dialog.text = XI_ConvertString(Nations[sti(NPChar.nation)].Name)+" zaoferowała przyzwoitą nagrodę za Twoją głowę. Musimy Cię dostarczyć do jednej z należących do niej kolonii i dostaniemy zapłatę, bez względu na to, czy dotrzesz tam żywy lub martwy.";
			Link.l1 = "Słuchaj, zapłacę ci, jeśli mnie zostawisz w spokoju.";
			Link.l1.go = "Cost_Head"; 
            // boal 08.04.04 -->
            if (GetSummonSkillFromNameToOld(PChar, SKILL_SNEAK) > 2 || bBettaTestMode)
            {
    			TempChar = characterFromID("Bug Fixer");
    			SetRandomNameToCharacter(TempChar);
    			Link.l2 = ""+GetSexPhrase("Przepraszam, ale chyba się pomyliłeś. Ja jestem "+GetFullName(TempChar)+" - jestem dobrze znanym kupcem na tych ziemiach.","Przepraszam, ale mylisz się. Jestem tylko prostą dziewczyną, a mój ojciec to "+GetFullName(TempChar)+" - jest dobrze znanym kupcem na tych ziemiach.")+".";
    			Link.l2.go = "lier";
			}
            Link.l3 = "Dobrze więc, spróbuj swojego szczęścia, jeśli tak chcesz.";
			Link.l3.go = "battle";
		break;
        
        case "lier":
            if (GetSummonSkillFromName(pchar, SKILL_SNEAK) > rand(150) || bBettaTestMode)
            {
                dialog.text = "Och! Najwyraźniej się pomyliliśmy. Proszę, wybacz za zamieszanie, "+GetAddress_Form(NPChar)+".";
                Link.l1 = "Nic się nie stało, nie martw się tym...";
                Link.l1.go = "lier_2";
                AddCharacterExpToSkill(pchar, SKILL_SNEAK, 100);
            }
            else
            {
                dialog.text = "Myslę, że próbujesz nas oszukać!";
                Link.l1 = "Słuchaj, zapłacę ci, jeśli zostawisz mnie w spokoju.";
			    Link.l1.go = "Cost_Head";
			    Link.l2 = "Dobrze więc, spróbuj swojego szczęścia, jeśli tak chcesz.";
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
			dialog.text = "Myslę, że "+PChar.HunterCost+" pesos będzie nam pasować.";
            if(makeint(Pchar.money) < sti(PChar.HunterCost))
            {
                Link.l1 = "Ale ja nie mam tylu pieniędzy.";
                Link.l1.go = "NoMoney";
            }else{
                Link.l1 = "Oto twoje pieniądze, weź je i znikaj.";
                Link.l1.go = "Cost_Head2";
                Link.l2 = "Nie. Takie łachudry jak Wy niczego nie dostaną... Chyba wolę jednak posłać Was wszystkich do piachu!";
                Link.l2.go = "battle";
            }
		break;

        case "NoMoney":
			dialog.text = "W takim razie nie mamy o czym rozmawiać!";
			Link.l1 = "Żywcem mnie nie weźmiecie, psy.";
			Link.l1.go = "battle"; 
		break;
		
		case "TreasureHunter":
			dialog.text = "Zaczekaj, "+GetSexPhrase("koleżko","panienko")+"... Myślę, że masz coś interesującego przy sobie. Przyjaciele powinni dzielić się znalezionymi skarbami, nie sądzisz?";
            Link.l1 = "Słuchaj, zapłacę ci, ale zostawisz mnie w spokoju.";
			Link.l1.go = "Cost_Head";
            // boal 08.04.04 -->
            if (GetSummonSkillFromNameToOld(PChar, SKILL_SNEAK) > 3)
            {
    			TempChar = characterFromID("Bug Fixer");
    			SetRandomNameToCharacter(TempChar);
    			Link.l2 = ""+GetSexPhrase("Przepraszam, ale chyba się mylisz. Jestem "+GetFullName(TempChar)+"- jestem tylko tutejszym mieszkańcem, a na pewno nie poszukiwacz skarbów.","Przepraszam, ale pomyliliście się. Jestem tylko prostą dziewczyną, a na pewno nie poszukiwaczką skarbów. A mój ojciec to "+GetFullName(TempChar)+" - powszechnie znany mieszkaniec tych ziemiach")+"!";
    			Link.l2.go = "TreasureHunterLier";
			}
            Link.l3 = "Cóż, wygląda na to, że trzeba pozbawić was czerepów.";
			Link.l3.go = "battle";
		break;
		
		case "TreasureHunterLier":
            if (GetSummonSkillFromName(pchar, SKILL_SNEAK) > rand(150))
            {
                dialog.text = "Och! Musiało dojść do pomyłki, proszę nam wybaczyć, "+GetAddress_Form(NPChar)+".";
                Link.l1 = "Nic się nie stało, nie martw się...";
                Link.l1.go = "lier_2";
                AddCharacterExpToSkill(pchar, SKILL_SNEAK, 100);
            }
            else
            {
                dialog.text = "Myslę, że próbujesz mnie oszukać!";
			    Link.l1 = "Wtedy posłuchaj pieśni mojego ostrza.";
			    Link.l1.go = "battle";
			    AddCharacterExpToSkill(pchar, SKILL_SNEAK, 50);
            }
        break;
		
		case "TreasureCaptain":
			dialog.text = LinkRandPhrase("Masz moją mapę skarbów! Myślę, koleżko, że musisz oddać wszystko, co zabrałeś...","Och, oponent! Nie uciekniesz daleko! Jesteś spowolniony ciężarem moich skarbów...","Hej, w końcu cię złapałem! Wszystkie skarby w tej jaskini należą do mnie, rozumiesz? Teraz, opróżnij swoje kieszenie!");
			Link.l1 = LinkRandPhrase("Czas, abyś spotkał się z moim ostrzem!","Twoje skarby? Chciałeś powiedzieć, że były twoje, bo teraz są moje!","Wolę wypruć Ci flaki moim ostrzem, kolego.","Pocałuj mnie w dupe, kanalio!");
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
			dialog.text = LinkRandPhrase("Cóż, pułkownik miał rację, skarb był ukryty w tej jaskini... Opróżnij swoje kieszenie!","Wreszcie cię dopadliśmy, po całym tym przeprawianiu się przez te przeklęte dżungle, wśród cierni i bagien. Teraz, miernoto, oddasz nam wszystko...","Hej! Skarby tego pirata należą do nas, więc zabieraj swoje brudne ręce!");
			Link.l1 = LinkRandPhrase("Zdecydowanie ciężko było się tego spodziewać po oficerze! Ale dobrze, dam Ci zasłużoną lekcję...","Popatrz na niego - brudny pirat w mundurze oficera...","Rzeczywiście żołnierze i piraci nie różnią się od siebie aż tak bardzo w dzisiejszych czasach...");
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
			dialog.text = "I oto nadchodzi nasze złoto. Przynajmniej nie musieliśmy czekać na próżno.";
			link.l1 = RandPhraseSimple("O czym mówicie, panowie? Jestem przedstawicielem Holenderskiej Kompanii Zachodnioindyjskiej i jestem tu tylko przejazdem! Zatrzymałem się tu, aby podziwiać widok na wybrzeże!","Obawiam się, że pomyliłeś mnie z kimś innym. Jestem "+GetSexPhrase("Francua Marie Paganel, ","Maria-Teresa, ")+" - botanik. Zbieram próbki lokalnej flory. Chcesz zobaczyć moją kolekcję liści juki? Mam tu kilka interesujących!");
			link.l1.go = "ReasonToFast_THunter_2";
			link.l2 = "Czego chcesz?! Trzymaj się ode mnie z daleka!";
			link.l2.go = "ReasonToFast_THunter_2";
		break;
		
		case "ReasonToFast_THunter_2":
			ReasonToFast_ClearTreasureBox(pchar.questTemp.ReasonToFast.Treasure.Location);
			dialog.text = "O nie, "+GetSexPhrase("mój drogi przyjacielu","moja droga przyjaciółko")+". To nie zadziała. Wiemy, że posiadasz mapę "+GetName(pchar.questTemp.ReasonToFast.mapIdx,pchar.questTemp.ReasonToFast.map,NAME_GEN)+". A on był tak skąpy, że jego skrzynie z pewnością pękają od środka, pełne monet. Nie zamierzamy wyjść z pustymi rękami.";
			link.l1 = "Masz rację. Skrzynie były rzeczywiście pełne. Ale ich nie dostaniesz. Możesz spróbować odwiedzić tamtą jaskinię, kilka worków powinno tam jeszcze być.";
			link.l1.go = "ReasonToFast_THunter_3";
			if(ReasonToFast_CheckTreasureQty("icollection", sti(pchar.questTemp.ReasonToFast.p8)) >= sti(pchar.questTemp.ReasonToFast.p8) 
				&& ReasonToFast_CheckTreasureQty("Chest", sti(pchar.questTemp.ReasonToFast.p7)) >= sti(pchar.questTemp.ReasonToFast.p7))
			{
				link.l2 = "Masz rację. Zatrzymaj swój skarb. Pamiętaj jednak, że nie przyniesie ci szczęścia, ponieważ jest splamiony krwią.";
				link.l2.go = "ReasonToFast_THunter_4";
			}	
		break;
		
		case "ReasonToFast_THunter_3":
			dialog.text = ""+GetSexPhrase("Heh, kapitanie, jesteś zbyt młody, aby umierać, czyż nie...","Heh, dziewczyno, jesteś zbyt młoda, aby umierać, czyż nie...")+"...";
			link.l1 = "Właściwie, to nie zamierzam umierać!";
			link.l1.go = "ReasonToFastTHunter_Fight";
		break;
		
		case "ReasonToFast_THunter_4":
			dialog.text = "W końcu brzmisz rozsądnie!";
			link.l1 = "Idź do diabła - Ty i wszystkie te skarby...";
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
			dialog.text = "Hej,"+GetSexPhrase("kolego","panienko")+"! "+GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_NOM)+" powiedział, że masz coś dla nas.";
			link.l1 = "O czym ty mówisz?";
			link.l1.go = "ReasonToFast_HunterShore11";
			pchar.quest.ReasonToFast_SetHunterPort_1.over = "yes";
			pchar.quest.ReasonToFast_SetHunterPort_2.over = "yes";
		break;

		case "ReasonToFast_HunterShore11":
			if(pchar.questTemp.ReasonToFast == "GetMap") 
			{
				dialog.text = "Mapa "+GetName(pchar.questTemp.ReasonToFast.mapIdx,pchar.questTemp.ReasonToFast.map,NAME_GEN);
				link.l1 = "Weź to i pozdrów "+GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_DAT)+". Powiedz mu, że niedługo się spotkamy...";
				link.l1.go = "ReasonToFast_HunterShore12_1";
				link.l2 = GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_NOM)+"jest w błędzie, jeśli myśli, że będę dla niego nadstawiać karku.";
				link.l2.go = "ReasonToFast_HunterShore23";
			}
			if(pchar.questTemp.ReasonToFast == "LakeyExitSuccess")
			{
				dialog.text = "Biżuteria skradziona gubernatorowi.";
				if(ReasonToFast_CheckTreasureQty("icollection", sti(pchar.questTemp.ReasonToFast.p8)) >= sti(pchar.questTemp.ReasonToFast.p8) 
					&& ReasonToFast_CheckTreasureQty("Chest", sti(pchar.questTemp.ReasonToFast.p7)) >= sti(pchar.questTemp.ReasonToFast.p7))
				{
					link.l1 = "Weź ją i pozdrów "+GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_DAT)+". Powiedz mu, że niedługo się spotkamy...";
					link.l1.go = "ReasonToFast_HunterShore12_2";
				}	
				link.l2 = GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_NOM)+"jest w błędzie, jeśli myśli, że będę dla niego nadstawiać karku.";
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
			dialog.text = "Hej,"+GetSexPhrase("kolego","panienko")+"! "+GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_GEN)+" ma kilka pytań do ciebie.";
			link.l1 = "A dlaczego sam ich nie zada?";
			link.l1.go = "ReasonToFast_HunterShore21";
			chrDisableReloadToLocation = false;
		break;
		
		case "ReasonToFast_HunterShore21":
			dialog.text = "Nie według jego rangi. Zrujnowałeś naszą operację i straciliśmy "+sti(pchar.questTemp.ReasonToFast.p10)+" pesos przez ciebie. Więc teraz masz dług do spłacenia.";
			link.l1 = "Weź to i przywitaj się z "+GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_DAT)+". Powiedz mu, że niedługo się spotkamy...";
			link.l1.go = "ReasonToFast_HunterShore22";
			link.l2 = GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_NOM)+" jest w błędzie, jeśli myśli, że będę dla niego nadstawiać karku.";
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
				dialog.text = "Och, nie masz tylu pieniędzy!? Cóż, dokonałeś wyboru...";
				link.l1 = "Od dawna...";
				link.l1.go = "ReasonToFastTHunter_Fight";	
				if(pchar.questTemp.ReasonToFast == "LakeyExitSuccess" || pchar.questTemp.ReasonToFast == "LakeyExitFail")
				{
					pchar.quest.ReasonToFast_SetPirateShip.win_condition.l1 = "MapEnter";
					pchar.quest.ReasonToFast_SetPirateShip.function = "ReasonToFast_PreparePirateShip";
				}
			}
		break;
		
		case "ReasonToFast_HunterShore23":
			dialog.text = "Cóż, dokonałeś wyboru...";
			link.l1 = "Od dawna...";
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
