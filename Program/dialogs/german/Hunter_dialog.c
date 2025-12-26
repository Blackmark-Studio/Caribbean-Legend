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
			
			dialog.text = GetFullName(PChar)+"! "+"Wir haben dich schon lange verfolgt, und endlich gehörst du uns.";
			Link.l1 = "Wer bist du und was willst du von mir?";
			Link.l1.go = "meeting"; 
			
			PChar.GenQuest.HunterStart = true;
		break;

		case "meeting":
			dialog.text = XI_ConvertString(Nations[sti(NPChar.nation)].Name)+" hat ein anständiges Kopfgeld für deinen Kopf ausgesetzt, wir müssen dich in eine seiner Kolonien liefern und wir werden bezahlt, egal ob du tot oder lebendig bist.";
			Link.l1 = "Hör zu, ich werde dich bezahlen, wenn du mich in Ruhe lässt.";
			Link.l1.go = "Cost_Head"; 
            // boal 08.04.04 -->
            if (GetSummonSkillFromNameToOld(PChar, SKILL_SNEAK) > 2 || bBettaTestMode)
            {
    			TempChar = characterFromID("Bug Fixer");
    			SetRandomNameToCharacter(TempChar);
    			Link.l2 = ""+GetSexPhrase("Entschuldigung, aber Sie müssen sich irren. Ich bin "+GetFullName(TempChar)+" - ein bekannter Kaufmann in diesen Gegenden.","Entschuldigung, aber Sie müssen sich irren. Ich bin nur ein einfaches Mädchen und mein Vater ist "+GetFullName(TempChar)+" - ein bekannter Kaufmann in diesen Landen.")+".";
    			Link.l2.go = "lier";
			}
            Link.l3 = "Gut, du kannst dein Glück versuchen, wenn du es so wünschst.";
			Link.l3.go = "battle";
		break;
        
        case "lier":
            if (GetSummonSkillFromName(pchar, SKILL_SNEAK) > rand(150) || bBettaTestMode)
            {
                dialog.text = "Oh! Wir könnten uns tatsächlich irren. Bitte, verzeih uns, "+GetAddress_Form(NPChar)+".";
                Link.l1 = "Es passiert, mach dir keine Sorgen darüber...";
                Link.l1.go = "lier_2";
                AddCharacterExpToSkill(pchar, SKILL_SNEAK, 100);
            }
            else
            {
                dialog.text = "Ich glaube, du lügst!";
                Link.l1 = "Hör zu, ich werde dich bezahlen, wenn du mich in Ruhe lässt.";
			    Link.l1.go = "Cost_Head";
			    Link.l2 = "Gut, du kannst dein Glück versuchen, wenn du es wünschst.";
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
			dialog.text = "Ich denke, dass "+PChar.HunterCost+" Pesos werden uns gut passen.";
            if(makeint(Pchar.money) < sti(PChar.HunterCost))
            {
                Link.l1 = "Aber ich habe solches Geld nicht.";
                Link.l1.go = "NoMoney";
            }else{
                Link.l1 = "Hier ist dein Geld, nimm es und verschwinde.";
                Link.l1.go = "Cost_Head2";
                Link.l2 = "So eine Summe an Halunken wie euch zu geben... Ich glaube, ich würde euch lieber alle gleich hier aufschlitzen!";
                Link.l2.go = "battle";
            }
		break;

        case "NoMoney":
			dialog.text = "In diesem Fall ist unser Gespräch vorbei!";
			Link.l1 = "Du wirst mich nie lebendig kriegen.";
			Link.l1.go = "battle"; 
		break;
		
		case "TreasureHunter":
			dialog.text = "Halte an, "+GetSexPhrase("Kumpel","Fräulein")+"... Ich denke, du hast etwas Interessantes bei dir. Freunde sollten die gefundenen Schätze miteinander teilen, meinst du nicht auch?";
            Link.l1 = "Hör zu, ich werde dich bezahlen, wenn du mich in Ruhe lässt.";
			Link.l1.go = "Cost_Head";
            // boal 08.04.04 -->
            if (GetSummonSkillFromNameToOld(PChar, SKILL_SNEAK) > 3)
            {
    			TempChar = characterFromID("Bug Fixer");
    			SetRandomNameToCharacter(TempChar);
    			Link.l2 = ""+GetSexPhrase("Entschuldigen Sie, aber Sie müssen sich irren. Ich bin "+GetFullName(TempChar)+" - ein bekannter Bürger in diesen Landen, aber sicherlich kein Schatzsucher.","Entschuldigen Sie, aber Sie müssen sich irren. Ich bin nur ein einfaches Mädchen und kein Schatzsucher. Und mein Vater ist "+GetFullName(TempChar)+" - ein bekannter Bürger in diesen Landen")+"!";
    			Link.l2.go = "TreasureHunterLier";
			}
            Link.l3 = "Nun, es scheint, dass es Zeit ist, dass eure Köpfe sich von ihren Körpern trennen.";
			Link.l3.go = "battle";
		break;
		
		case "TreasureHunterLier":
            if (GetSummonSkillFromName(pchar, SKILL_SNEAK) > rand(150))
            {
                dialog.text = "Oh! Dann könnten wir uns tatsächlich geirrt haben. Bitte verzeih uns, "+GetAddress_Form(NPChar)+".";
                Link.l1 = "Es passiert, mach dir keine Sorgen...";
                Link.l1.go = "lier_2";
                AddCharacterExpToSkill(pchar, SKILL_SNEAK, 100);
            }
            else
            {
                dialog.text = "Ich glaube, dass du lügst!";
			    Link.l1 = "Dann hör auf das Lied meiner Klinge.";
			    Link.l1.go = "battle";
			    AddCharacterExpToSkill(pchar, SKILL_SNEAK, 50);
            }
        break;
		
		case "TreasureCaptain":
			dialog.text = LinkRandPhrase("Also bist du derjenige, der meine Schatzkarte genommen hat! Ich denke, Kumpel, es ist Zeit, alles zurückzugeben, was du genommen hast...","Oh, ein Rivale! Du wirst nicht weit kommen, du wirst durch das Gewicht meiner Schätze verlangsamt...","Huh, endlich habe ich dich eingeholt! Alle Schätze in dieser Höhle gehören mir, kapierst du das? Jetzt leere deine Taschen, Kumpel!");
			Link.l1 = LinkRandPhrase("Es ist Zeit für dich, meine Klinge zu treffen, Kumpel!","Deine Schätze? Du meintest, sie waren deine, denn jetzt sind sie mein!","Ich würde lieber deinen Magen mit meiner Klinge leeren, Kumpel.");
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
			dialog.text = LinkRandPhrase("Also, der Oberst hatte recht, der Schatz war in dieser Höhle versteckt... Leere deine Taschen, Seemann!","Also haben wir dich endlich erwischt, nachdem wir dich durch all diese verfluchten Dschungel, Dornen und Sümpfe verfolgt haben. Jetzt, du Bastard, wirst du uns alles geben...","He, Seemann! Die Schätze dieses Piraten gehören uns, also nimm deine schmutzigen Hände davon weg!");
			Link.l1 = LinkRandPhrase("Nun, das habe ich nicht von einem Armeeoffizier erwartet! Aber gut, ich werde dir trotzdem eine Lektion erteilen...","Schau ihn an, ein Pirat in einer Offiziersuniform...","Tatsächlich sind Soldaten und Piraten heutzutage nicht mehr so unterschiedlich...");
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
			dialog.text = "Und hier kommt unser Gold. Zumindest war unser Warten nicht umsonst.";
			link.l1 = RandPhraseSimple("Wovon reden Sie, Herren? Ich bin ein Vertreter der Niederländischen Westindien-Kompanie und bin nur auf der Durchreise hier! Ich habe angehalten, um die Aussicht auf die Küste zu bewundern!","Ich fürchte, Sie haben mich mit jemand anderem verwechselt. Ich bin "+GetSexPhrase("Francua Marie Paganel, ","Maria-Theresa, ")+"ein Naturforscher. Ich sammle hier Proben der einheimischen Flora. Möchtest du dir meine Sammlung von Yucca-Blättern ansehen? Ich habe einige sehr interessante!");
			link.l1.go = "ReasonToFast_THunter_2";
			link.l2 = "Was willst du?! Bleib mir aus dem Weg!";
			link.l2.go = "ReasonToFast_THunter_2";
		break;
		
		case "ReasonToFast_THunter_2":
			ReasonToFast_ClearTreasureBox(pchar.questTemp.ReasonToFast.Treasure.Location);
			dialog.text = "Ach nein, "+GetSexPhrase("mein lieber Freund","mein hübsches Mädchen")+". Das wird nicht funktionieren. Wir wissen mit Sicherheit, dass du die Karte besessen hast von "+GetName(pchar.questTemp.ReasonToFast.mapIdx,pchar.questTemp.ReasonToFast.map,NAME_GEN)+". Und er war so ein Geizhals, dass seine Truhen von innen voller Geld platzten. Also werden wir nicht mit leeren Händen gehen.";
			link.l1 = "Du hast recht. Die Truhen waren tatsächlich voll. Aber du wirst sie nicht bekommen. Du kannst versuchen, diese Höhle zu besuchen, ein paar löchrige Eimer sollten noch dort sein.";
			link.l1.go = "ReasonToFast_THunter_3";
			if(ReasonToFast_CheckTreasureQty("icollection", sti(pchar.questTemp.ReasonToFast.p8)) >= sti(pchar.questTemp.ReasonToFast.p8) 
				&& ReasonToFast_CheckTreasureQty("Chest", sti(pchar.questTemp.ReasonToFast.p7)) >= sti(pchar.questTemp.ReasonToFast.p7))
			{
				link.l2 = "Du hast recht. Du kannst deinen Schatz haben. Behalte nur im Hinterkopf, dass er dich nicht glücklich machen wird, da er mit Blut befleckt ist.";
				link.l2.go = "ReasonToFast_THunter_4";
			}	
		break;
		
		case "ReasonToFast_THunter_3":
			dialog.text = ""+GetSexPhrase("Heh, Kapitän, du bist zu jung zum Sterben, oder...","Heh, Mädchen, du bist zu jung zum Sterben, nicht wahr...")+"..., Freund.";
			link.l1 = "Eigentlich werde ich nicht sterben!";
			link.l1.go = "ReasonToFastTHunter_Fight";
		break;
		
		case "ReasonToFast_THunter_4":
			dialog.text = "Nun, das sind die Worte eines vernünftigen Menschen!";
			link.l1 = "Verflucht bist du und all diese Schätze...";
			link.l1.go = "ReasonToFast_THunter_GoAway";
		break;
		
		case "ReasonToFast_THunter_GoAway":			
			iTemp = ReasonToFast_CheckTreasureQty("icollection", sti(pchar.questTemp.ReasonToFast.p8));
			if(iTemp > 0) 
			{
				ReasonToFast_GetTreasure("icollection", iTemp );
				Log_Info(XI_ConvertString("Du hast ein Item gegeben"));
				PlayStereoSound("interface\important_item.wav");
			}	
			
			iTemp = ReasonToFast_CheckTreasureQty("Chest", sti(pchar.questTemp.ReasonToFast.p7));
			if(iTemp > 0) 
			{
				ReasonToFast_GetTreasure("Chest", iTemp);
				Log_Info(XI_ConvertString("Du hast ein Item gegeben"));
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
			dialog.text = "Hallo,"+GetSexPhrase("Kumpel","Fräulein")+"! "+GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_NOM)+" sagte, dass du etwas für uns hast.";
			link.l1 = "Was meinst du?";
			link.l1.go = "ReasonToFast_HunterShore11";
			pchar.quest.ReasonToFast_SetHunterPort_1.over = "yes";
			pchar.quest.ReasonToFast_SetHunterPort_2.over = "yes";
		break;

		case "ReasonToFast_HunterShore11":
			if(pchar.questTemp.ReasonToFast == "GetMap") 
			{
				dialog.text = "Eine Karte von "+GetName(pchar.questTemp.ReasonToFast.mapIdx,pchar.questTemp.ReasonToFast.map,NAME_GEN);
				link.l1 = "Nimm es und sag hallo zu "+GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_DAT)+". Sag ihm, dass wir uns bald treffen werden...";
				link.l1.go = "ReasonToFast_HunterShore12_1";
				link.l2 = GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_NOM)+" ist schwer getäuscht, wenn er denkt, dass ich die Kastanien aus dem Feuer für ihn ziehen werde.";
				link.l2.go = "ReasonToFast_HunterShore23";
			}
			if(pchar.questTemp.ReasonToFast == "LakeyExitSuccess")
			{
				dialog.text = "Schmuck, den du dem Gouverneur gestohlen hast.";
				if(ReasonToFast_CheckTreasureQty("icollection", sti(pchar.questTemp.ReasonToFast.p8)) >= sti(pchar.questTemp.ReasonToFast.p8) 
					&& ReasonToFast_CheckTreasureQty("Chest", sti(pchar.questTemp.ReasonToFast.p7)) >= sti(pchar.questTemp.ReasonToFast.p7))
				{
					link.l1 = "Nimm es und sag hallo zu "+GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_DAT)+". Sag ihm, dass wir uns bald treffen werden...";
					link.l1.go = "ReasonToFast_HunterShore12_2";
				}	
				link.l2 = GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_NOM)+" ist schwer im Irrtum, wenn er denkt, dass ich für ihn die Kastanien aus dem Feuer holen werde.";
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
				Log_Info(XI_ConvertString("Du hast ein Item gegeben"));
				PlayStereoSound("interface\important_item.wav");
			}	
			
			iTemp = ReasonToFast_CheckTreasureQty("Chest", sti(pchar.questTemp.ReasonToFast.p7));
			if(iTemp > 0) 
			{
				ReasonToFast_GetTreasure("Chest", iTemp);
				Log_Info(XI_ConvertString("Du hast ein Item gegeben"));
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
			dialog.text = "Hallo,"+GetSexPhrase("Kumpel","Fräulein")+"! "+GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_GEN)+" hat einige Fragen an Sie.";
			link.l1 = "Und warum würde er sie nicht selbst fragen?";
			link.l1.go = "ReasonToFast_HunterShore21";
			chrDisableReloadToLocation = false;
		break;
		
		case "ReasonToFast_HunterShore21":
			dialog.text = "Nicht seinem Rang entsprechend. Sie haben unsere Operation ruiniert und wir haben "+sti(pchar.questTemp.ReasonToFast.p10)+" Pesos verloren wegen dir. Also hast du jetzt eine Schuld zu begleichen.";
			link.l1 = "Nimm es und grüße "+GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_DAT)+". Sag ihm, dass wir uns bald treffen werden...";
			link.l1.go = "ReasonToFast_HunterShore22";
			link.l2 = GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_NOM)+" ist schwer getäuscht, wenn er denkt, dass ich für ihn Kastanien aus dem Feuer ziehen werde.";
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
				dialog.text = "Oh, du hast nicht so viel Geld! Nun, du hast deine Wahl getroffen... ";
				link.l1 = "Vor langer Zeit...";
				link.l1.go = "ReasonToFastTHunter_Fight";	
				if(pchar.questTemp.ReasonToFast == "LakeyExitSuccess" || pchar.questTemp.ReasonToFast == "LakeyExitFail")
				{
					pchar.quest.ReasonToFast_SetPirateShip.win_condition.l1 = "MapEnter";
					pchar.quest.ReasonToFast_SetPirateShip.function = "ReasonToFast_PreparePirateShip";
				}
			}
		break;
		
		case "ReasonToFast_HunterShore23":
			dialog.text = "Nun, du hast deine Wahl getroffen...";
			link.l1 = "Vor langer Zeit...";
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
	string ret = "";

	if (CheckAttribute(&locations[nLoc],"islandId"))
	{
		if (locations[nLoc].islandId != "Mein")
		{
			ret = "island of " + GetIslandNameByID(locations[nLoc].islandId);
		}
		else
		{
			ret = "mainland of ";
		}
	}
	//
	if (CheckAttribute(&locations[nLoc],"fastreload"))
	{
		ret += " (" +GetCityName(locations[nLoc].fastreload) + ")";
	}

	return ret;	
}
