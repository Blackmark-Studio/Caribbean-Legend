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
			
			dialog.text = GetFullName(PChar)+"! "+"Nous vous avons traqué pendant un bon moment, et enfin vous êtes à nous.";
			Link.l1 = "Qui êtes-vous et que voulez-vous de moi?";
			Link.l1.go = "meeting"; 
			
			PChar.GenQuest.HunterStart = true;
		break;

		case "meeting":
			dialog.text = XI_ConvertString(Nations[sti(NPChar.nation)].Name)+" a placé une prime décente pour ta tête, nous devons te livrer à l'une de ses colonies et nous serons payés, peu importe que tu sois mort ou vivant.";
			Link.l1 = "Écoute, je te paierai si tu me laisses tranquille.";
			Link.l1.go = "Cost_Head"; 
            // boal 08.04.04 -->
            if (GetSummonSkillFromNameToOld(PChar, SKILL_SNEAK) > 2 || bBettaTestMode)
            {
    			TempChar = characterFromID("Bug Fixer");
    			SetRandomNameToCharacter(TempChar);
    			Link.l2 = ""+GetSexPhrase("Excusez-moi, mais vous devez vous tromper. Je suis "+GetFullName(TempChar)+" - un marchand bien connu dans ces terres.","Excusez-moi, mais vous devez vous tromper. Je suis juste une simple fille, et mon père est "+GetFullName(TempChar)+"- un marchand bien connu en ces terres.")+".";
    			Link.l2.go = "lier";
			}
            Link.l3 = "D'accord, tu peux tenter ta chance, si tu le désires.";
			Link.l3.go = "battle";
		break;
        
        case "lier":
            if (GetSummonSkillFromName(pchar, SKILL_SNEAK) > rand(150) || bBettaTestMode)
            {
                dialog.text = "Oh! Nous pourrions en effet nous tromper. S'il vous plaît, pardonnez-nous, "+GetAddress_Form(NPChar)+".";
                Link.l1 = "Cela arrive, ne t'en fais pas...";
                Link.l1.go = "lier_2";
                AddCharacterExpToSkill(pchar, SKILL_SNEAK, 100);
            }
            else
            {
                dialog.text = "Je pense que tu mens !";
                Link.l1 = "Écoute, je te paierai si tu me laisses tranquille.";
			    Link.l1.go = "Cost_Head";
			    Link.l2 = "D'accord, vous pouvez tenter votre chance, si vous le désirez.";
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
			dialog.text = "Je pense que "+PChar.HunterCost+" pesos nous conviendra parfaitement.";
            if(makeint(Pchar.money) < sti(PChar.HunterCost))
            {
                Link.l1 = "Mais je n'ai pas une telle somme d'argent.";
                Link.l1.go = "NoMoney";
            }else{
                Link.l1 = "Voici votre argent, prenez-le et perdez-vous.";
                Link.l1.go = "Cost_Head2";
                Link.l2 = "Donner une telle somme à des canailles comme vous... Je préfère vous éventrer tous ici même !";
                Link.l2.go = "battle";
            }
		break;

        case "NoMoney":
			dialog.text = "Dans ce cas, notre conversation est terminée !";
			Link.l1 = "Vous ne m'aurez jamais vivant.";
			Link.l1.go = "battle"; 
		break;
		
		case "TreasureHunter":
			dialog.text = "Attendez, "+GetSexPhrase("camarade","demoiselle")+"... Je pense que vous avez quelque chose d'interessant avec vous. Les amis devraient partager les tresors trouves entre eux, ne pensez-vous pas?";
            Link.l1 = "Ecoute, je te paierai si tu me laisses tranquille.";
			Link.l1.go = "Cost_Head";
            // boal 08.04.04 -->
            if (GetSummonSkillFromNameToOld(PChar, SKILL_SNEAK) > 3)
            {
    			TempChar = characterFromID("Bug Fixer");
    			SetRandomNameToCharacter(TempChar);
    			Link.l2 = ""+GetSexPhrase("Excusez-moi, mais vous devez vous tromper. Je suis "+GetFullName(TempChar)+" - un citoyen bien connu dans ces terres, mais certainement pas un chercheur de trésor.","Excusez-moi, mais vous devez vous tromper. Je ne suis qu'une simple fille et non une chercheuse de trésors. Et mon père est "+GetFullName(TempChar)+" - un citoyen bien connu dans ces terres")+"!";
    			Link.l2.go = "TreasureHunterLier";
			}
            Link.l3 = "Eh bien, il semble qu'il soit temps pour vos têtes de se séparer de leurs corps.";
			Link.l3.go = "battle";
		break;
		
		case "TreasureHunterLier":
            if (GetSummonSkillFromName(pchar, SKILL_SNEAK) > rand(150))
            {
                dialog.text = "Oh! Nous pourrions en effet nous tromper, alors. Veuillez nous pardonner, "+GetAddress_Form(NPChar)+".";
                Link.l1 = "Ça arrive, ne t'en fais pas...";
                Link.l1.go = "lier_2";
                AddCharacterExpToSkill(pchar, SKILL_SNEAK, 100);
            }
            else
            {
                dialog.text = "Je pense que tu mens !";
			    Link.l1 = "Alors écoute la chanson de ma lame.";
			    Link.l1.go = "battle";
			    AddCharacterExpToSkill(pchar, SKILL_SNEAK, 50);
            }
        break;
		
		case "TreasureCaptain":
			dialog.text = LinkRandPhrase("Alors, tu es celui qui a pris ma carte au trésor! Je pense, l'ami, qu'il est temps de rendre tout ce que tu as pris...","Oh, un rival ! Tu n'iras pas loin, tu es ralenti par le poids de mes trésors...","Hein, enfin je t'ai rattrapé! Tous les trésors de cette caverne m'appartiennent, tu comprends? Maintenant, vide tes poches, mon pote!");
			Link.l1 = LinkRandPhrase("C'est le moment pour toi de rencontrer ma lame, camarade!","Vos trésors? Vous vouliez dire qu'ils étaient à vous, car maintenant ils sont à moi!","Je préférerais vider ton estomac avec ma lame, mon pote.");
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
			dialog.text = LinkRandPhrase("Alors, le colonel avait raison, le trésor était caché dans cette grotte... Vide tes poches, marin !","Alors, nous t'avons finalement rattrapé après toute cette chasse à travers toutes ces maudites jungles parmi les épines et les marais. Maintenant, bâtard, tu nous donneras tout...","Hé, marin! Les trésors de ce pirate nous appartiennent, alors éloigne tes mains sales d'eux!");
			Link.l1 = LinkRandPhrase("Certainement, je ne m'attendais pas à cela d'un officier de l'armée ! Mais bon, je vais vous donner une leçon quand même...","Regardez-le, un pirate en uniforme d'officier...","En effet, les soldats et les pirates ne sont pas si différents ces jours-ci...");
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
			dialog.text = "Et voici notre or. Au moins, notre attente n'était pas vaine.";
			link.l1 = RandPhraseSimple("De quoi parlez-vous, messieurs ? Je suis un représentant de la Compagnie néerlandaise des Indes occidentales et je suis juste de passage ici ! Je me suis arrêté pour admirer la vue sur la côte !","Je crains que vous ne m'ayez pris pour quelqu'un d'autre. Je suis "+GetSexPhrase("Francua Marie Paganel, ","Maria-Theresa, ")+"un naturaliste. Je recueille des échantillons de la flore locale ici. Veux-tu jeter un coup d'oeil à ma collection de feuilles de yucca? J'ai plusieurs très intéressantes!");
			link.l1.go = "ReasonToFast_THunter_2";
			link.l2 = "Que voulez-vous?! Restez hors de mon chemin!";
			link.l2.go = "ReasonToFast_THunter_2";
		break;
		
		case "ReasonToFast_THunter_2":
			ReasonToFast_ClearTreasureBox(pchar.questTemp.ReasonToFast.Treasure.Location);
			dialog.text = "Oh non, "+GetSexPhrase("mon cher ami","ma jolie fille")+". Cela ne marchera pas. Nous savons avec certitude que vous possédiez la carte de "+GetName(pchar.questTemp.ReasonToFast.mapIdx,pchar.questTemp.ReasonToFast.map,NAME_GEN)+". Et il était un tel avare que ses coffres craquaient de l'intérieur, pleins d'argent. Donc nous ne partirons pas les mains vides.";
			link.l1 = "Tu as raison. Les coffres étaient effectivement pleins. Mais tu ne les obtiendras pas. Tu peux essayer de visiter cette grotte, il devrait toujours y avoir quelques seaux troués.";
			link.l1.go = "ReasonToFast_THunter_3";
			if(ReasonToFast_CheckTreasureQty("icollection", sti(pchar.questTemp.ReasonToFast.p8)) >= sti(pchar.questTemp.ReasonToFast.p8) 
				&& ReasonToFast_CheckTreasureQty("Chest", sti(pchar.questTemp.ReasonToFast.p7)) >= sti(pchar.questTemp.ReasonToFast.p7))
			{
				link.l2 = "Vous avez raison. Vous pouvez avoir votre trésor. Gardez simplement à l'esprit que cela ne vous rendra pas heureux, car il est taché de sang.";
				link.l2.go = "ReasonToFast_THunter_4";
			}	
		break;
		
		case "ReasonToFast_THunter_3":
			dialog.text = ""+GetSexPhrase("Heh, capitaine, tu es trop jeune pour mourir, n'est-ce pas...","Heh, ma fille, tu es trop jeune pour mourir, n'est-ce pas...")+"...";
			link.l1 = "En fait, je ne vais pas mourir !";
			link.l1.go = "ReasonToFastTHunter_Fight";
		break;
		
		case "ReasonToFast_THunter_4":
			dialog.text = "Voici les paroles d'une personne raisonnable!";
			link.l1 = "Maudis-toi et tous ces trésors...";
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
			dialog.text = "Salut,"+GetSexPhrase("camarade","lass")+"! "+GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_NOM)+" a dit que vous aviez quelque chose pour nous.";
			link.l1 = "Que voulez-vous dire?";
			link.l1.go = "ReasonToFast_HunterShore11";
			pchar.quest.ReasonToFast_SetHunterPort_1.over = "yes";
			pchar.quest.ReasonToFast_SetHunterPort_2.over = "yes";
		break;

		case "ReasonToFast_HunterShore11":
			if(pchar.questTemp.ReasonToFast == "GetMap") 
			{
				dialog.text = "Une carte de "+GetName(pchar.questTemp.ReasonToFast.mapIdx,pchar.questTemp.ReasonToFast.map,NAME_GEN);
				link.l1 = "Prenez-le et dites bonjour à "+GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_DAT)+". Dis-lui que nous nous rencontrerons bientôt...";
				link.l1.go = "ReasonToFast_HunterShore12_1";
				link.l2 = GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_NOM)+"se trompe gravement s'il pense que je vais tirer les marrons du feu pour lui.";
				link.l2.go = "ReasonToFast_HunterShore23";
			}
			if(pchar.questTemp.ReasonToFast == "LakeyExitSuccess")
			{
				dialog.text = "Des bijoux que tu as volés du gouverneur.";
				if(ReasonToFast_CheckTreasureQty("icollection", sti(pchar.questTemp.ReasonToFast.p8)) >= sti(pchar.questTemp.ReasonToFast.p8) 
					&& ReasonToFast_CheckTreasureQty("Chest", sti(pchar.questTemp.ReasonToFast.p7)) >= sti(pchar.questTemp.ReasonToFast.p7))
				{
					link.l1 = "Prends-le et dis bonjour à "+GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_DAT)+". Dis-lui que nous nous rencontrerons bientôt...";
					link.l1.go = "ReasonToFast_HunterShore12_2";
				}	
				link.l2 = GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_NOM)+" se trompe gravement s'il pense que je vais tirer les marrons du feu pour lui.";
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
			dialog.text = "Salut,"+GetSexPhrase("camarade","demoiselle")+"! "+GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_GEN)+" a plusieurs questions pour vous.";
			link.l1 = "Et pourquoi ne leur demanderait-il pas lui-même ?";
			link.l1.go = "ReasonToFast_HunterShore21";
			chrDisableReloadToLocation = false;
		break;
		
		case "ReasonToFast_HunterShore21":
			dialog.text = "Non selon son rang. Vous avez ruiné notre opération et nous avons perdu "+sti(pchar.questTemp.ReasonToFast.p10)+" pesos à cause de toi. Alors maintenant tu as une dette à payer.";
			link.l1 = "Prends-le et dis bonjour à "+GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_DAT)+". Dis-lui que nous nous rencontrerons bientôt...";
			link.l1.go = "ReasonToFast_HunterShore22";
			link.l2 = GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_NOM)+" se trompe gravement s'il pense que je vais sortir les marrons du feu pour lui.";
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
				dialog.text = "Oh, tu n'as pas tant d'argent ! Eh bien, tu as fait ton choix... ";
				link.l1 = "Il y a longtemps...";
				link.l1.go = "ReasonToFastTHunter_Fight";	
				if(pchar.questTemp.ReasonToFast == "LakeyExitSuccess" || pchar.questTemp.ReasonToFast == "LakeyExitFail")
				{
					pchar.quest.ReasonToFast_SetPirateShip.win_condition.l1 = "MapEnter";
					pchar.quest.ReasonToFast_SetPirateShip.function = "ReasonToFast_PreparePirateShip";
				}
			}
		break;
		
		case "ReasonToFast_HunterShore23":
			dialog.text = "Eh bien, tu as fait ton choix...";
			link.l1 = "Il y a longtemps...";
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
