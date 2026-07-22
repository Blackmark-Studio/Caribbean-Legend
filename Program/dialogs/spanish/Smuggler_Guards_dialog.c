void ProcessDialogEvent() 
{
	ref NPChar;
	aref Link, Diag;
	string NPC_Meeting;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);
	
    int iTemp, i; // нужно для вычислений любых целых (нации)
	string attrName; // любые строки для вычислений
	ref sld;

    switch(Dialog.CurrentNode)
	{
		case "exit":
			StopCoastalGuardPursuit();
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = NPC_Meeting;
			DialogExit();
			LAi_SetPlayerType(Pchar);
		break;

		case "First time":			
			chrDisableReloadToLocation = false;
   			LAi_LockFightMode(pchar, false);
			// Captain Beltrop, 14.02.2021 - правка проверки репутации и навыков владения оружием
			bool FencingSkills = (GetCharacterSkillToOld(Pchar, "FencingL") >= 8) || (GetCharacterSkillToOld(Pchar, "FencingS") >= 8) || (GetCharacterSkillToOld(Pchar, "FencingH") >= 8);
			dialog.text = RandPhraseSimple("Parece que estás cometiendo algo ilegal aquí.","En el nombre de "+NationKingsName(npchar)+", ¡te ordeno que detengas esta infracción de la ley!");
			Link.l1 = "No-no, oficial. Yo y mis compañeros solo estamos tomando el sol aquí.";
			// belamour legendary edition включим обаяние ГГ, если оно есть
			if(CheckCharacterPerk(pchar, "Trustworthy"))
			{
				Link.l1.go = "ThisTimeFree";
			}
			else
			{
				if (int(pchar.reputation.nobility) >= 70 && GetSummonSkillFromNameToOld(Pchar, SKILL_LEADERSHIP) >= 5)
				{
					Link.l1.go = "ThisTimeFree";
				}
				else
				{
				Link.l1.go = "IDontBelieveYou";
				}
			}
			Link.l2 = "Hago caridad. ¿Es eso realmente ilegal?";
			Link.l2.go = "GiveMeSomeMoneyToo";
			Link.l3 = "¡Aléjate de aquí, soldado. ¡No es asunto tuyo!";
			if(int(pchar.reputation.nobility) <= 25 && FencingSkills)
			{
				Link.l3.go = "GettingLostFromHere";
			}
			else
			{
				Link.l3.go = "howDareYou";
			}
		break;

		case "ThisTimeFree":
			dialog.snd = "Voice\COGU\COGU002";		
			dialog.text = "No nos hagas tontos, capitán "+Pchar.name+"¡Nadie esperaría jamás que un hombre tan positivo y respetable como tú se dedicara al contrabando!";
			Link.l1 = "Nadie es perfecto. ¡Pero ya me arrepiento!";
			Link.l1.go = "ThisTimeFree_1";
			Link.l2 = "Voy a cortarte la cabeza ahora mismo.";
			Link.l2.go = "ThisTimeFree_fight";				
		break;

		case "ThisTimeFree_1":	
			dialog.snd = "Voice\COGU\COGU003";	
			dialog.text = "He oído hablar de ti, solo cosas positivas así que te dejaré ir esta vez pero no lo hagas de nuevo. ¡No puedo decir lo mismo de estos compañeros, sin embargo!";
			Link.l1 = "Mi agradecimiento, oficial. ¡Que tengas un buen día!";
			Link.l1.go = "ThisTimeFree_exit";
		break;

		case "ThisTimeFree_fight":	
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться 130313
			ChangeCharacterNationReputation(pchar, int(NPChar.Nation), -1);
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = NPC_Meeting;
			DialogExit();
			for (i = 1; i <= int(Pchar.quest.contraband.SoldierQty); i++)
			{
    			attrName = "SoldierIDX"+i;
				sld = GetCharacter(int(Pchar.quest.contraband.(attrName)));
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "CoastalGuards");
            }
			
			LAi_group_SetRelation(pchar.GenQuest.Smugglers_Group, "CoastalGuards", LAI_GROUP_ENEMY);
			LAi_group_SetHearRadius("CoastalGuards", 100.0);
			LAi_group_SetHearRadius(pchar.GenQuest.Smugglers_Group, 100.0);
			LAi_group_FightGroups("CoastalGuards", pchar.GenQuest.Smugglers_Group, true);
			LAi_group_SetRelation("CoastalGuards", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("CoastalGuards", LAI_GROUP_PLAYER, true);
            LAi_SetFightMode(Pchar, true);
		break;

		case "ThisTimeFree_exit":
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = NPC_Meeting;
			
            DialogExit();
			StopCoastalGuardPursuit();
			ChangeContrabandRelation(pchar, -30);
			for (i = 1; i <= int(Pchar.quest.contraband.SoldierQty); i++)
			{
    			attrName = "SoldierIDX"+i;
				sld = GetCharacter(int(Pchar.quest.contraband.(attrName)));
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "CoastalGuards");
            }
			LAi_group_SetRelation(pchar.GenQuest.Smugglers_Group, "CoastalGuards", LAI_GROUP_ENEMY);			
			LAi_group_FightGroups(pchar.GenQuest.Smugglers_Group, "CoastalGuards", true);
			LAi_SetPlayerType(Pchar);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться 130313
		break;

		case "IDontBelieveYou":
			dialog.snd = "Voice\COGU\COGU004";
			dialog.text = "¡¡¡Deja de mentir!!! ¡No soy ciego! Síguenos, estás arrestado y tus bienes son confiscados.";
			Link.l1 = "¡Será mejor que te arranque las tripas!";
			Link.l1.go = "ThisTimeFree_fight";
		break;

		case "GiveMeSomeMoneyToo":
            attrName = XI_ConvertString("Chance");
            int iRand = hrand(99, "&Bribe" + PChar.Location);
            int iMoney = PChar.Money;
            int iBaseChance = GetCharacterSkill(PChar, SKILL_SNEAK) + GetCharacterSkill(PChar, SKILL_LEADERSHIP);
			dialog.snd = "Voice\COGU\COGU005";		
			dialog.text = "¿De verdad? Bueno, esta actividad es completamente legal... si obtuviésemos nuestra parte, por supuesto. ¿Y cuán grande es tu caridad?";
            if (iMoney >= 25000)
            {
                iTemp = iBaseChance > 100 ? 100 : iBaseChance;
                link.l1 = "¡Para usted, oficial, tengo 25000 pesos! (" + attrName + " " + iTemp + "%)";
                link.l1.go = iTemp > iRand ? "MoneyAccepted10" : "TryingToGiveBribe";
            }
            if (iMoney >= 12000)
            {
                iTemp = iBaseChance / 2 + 10;
                if (iTemp > 100) iTemp = 100;
                link.l2 = "¿Qué tal 12000 pesos? (" + attrName + " " + iTemp + "%)";
                link.l2.go = iTemp > iRand ? "MoneyAccepted5" : "TryingToGiveBribe";
            }
            if (iMoney >= 5000)
            {
                iTemp = iBaseChance / 2 - 10;
                if (iTemp > 100) iTemp = 100;
                link.l3 = "Creo que 5000 pesos serán suficientes. (" + attrName + " " + iTemp + "%)";
                link.l3.go = iTemp > iRand ? "MoneyAccepted2" : "TryingToGiveBribe";
            }
			link.l4 = StringFromKey("smuggling_3");
			link.l4.go = "ThisTimeFree_fight";
		break;

		case "TryingToGiveBribe":
			dialog.snd = "Voice\COGU\COGU006";
			dialog.text = "¿Un soborno? ¡No, me importa mi honor! Entonces, ¿nos seguirías amablemente?";
			Link.l1 = "¡Maldita sea! Lo siento por decepcionarte, ¡pero no voy a ir a ninguna parte!";
			Link.l1.go = "ThisTimeFree_fight";
		break;

		case "MoneyAccepted10":
            AddMoneyToCharacter(PChar, -25000);
			dialog.snd = "Voice\COGU\COGU007";
			dialog.text = "Mi gratitud por tu caridad.";
			Link.l1 = "Siempre a su servicio.";
			Link.l1.go = "GettingLostFromHere_exit";
			AddMoneyToCharacter(pchar, -int(int(Pchar.money)/10));
		break;
		
		case "MoneyAccepted5":
            AddMoneyToCharacter(PChar, -12000);
			dialog.snd = "Voice\COGU\COGU007";
			dialog.text = "Mi gratitud por tu caridad.";
			Link.l1 = "Siempre a su servicio.";
			Link.l1.go = "GettingLostFromHere_exit";
			AddMoneyToCharacter(pchar, -int(int(Pchar.money)/5));
		break;
		
		case "MoneyAccepted2":
            AddMoneyToCharacter(PChar, -5000);
			dialog.snd = "Voice\COGU\COGU007";
			dialog.text = "Mi gratitud por tu caridad.";
			Link.l1 = "Siempre a su servicio.";
			Link.l1.go = "GettingLostFromHere_exit";
			AddMoneyToCharacter(pchar, -int(int(Pchar.money)/2));
		break;

		case "GettingLostFromHere":
			dialog.snd = "Voice\COGU\COGU008";
			dialog.text = "¡Pero... maldita sea! ¡Tengo que arrestarte!";
			Link.l1 = "¿¡Qué?! ¿Todavía estás aquí? ¿Demasiado cansado de la vida?";
			Link.l1.go = "GettingLostFromHere_1";
		break;

		case "GettingLostFromHere_1":
			dialog.snd = "Voice\COGU\COGU009";
			dialog.text = "¡...Yo... Yo me quejaré! ¡No lo dejaré pasar así como así....";
			Link.l1 = "¡Eh!";
			Link.l1.go = "GettingLostFromHere_exit";
		break;

		case "GettingLostFromHere_exit":
			ChangeContrabandRelation(pchar, 10);

			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = NPC_Meeting;
            DialogExit();
            
			StopCoastalGuardPursuit();
			for (i = 1; i <= int(Pchar.quest.contraband.SoldierQty); i++)
			{
                attrName = "SoldierIDX"+i;
                LAi_SetActorType(&Characters[int(Pchar.quest.contraband.(attrName))]);
                LAi_ActorRunToLocation(&Characters[int(Pchar.quest.contraband.(attrName))], "reload", "Reload1", "none", "", "", "", 40);
			}
			LAi_SetPlayerType(Pchar);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться 130313
		break;

		case "howDareYou":
			dialog.snd = "Voice\COGU\COGU010";
			dialog.text = "¡Hijo de...! ¡Maldito perro! ¡Esta bahía se convertirá en tu tumba!";
			Link.l1 = "¡Ven aquí e intenta probar eso!";
			Link.l1.go = "ThisTimeFree_fight";
		break;
	}
}
