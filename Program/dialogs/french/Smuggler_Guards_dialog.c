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
			dialog.text = RandPhraseSimple("Il semble que vous commettez quelque chose d'illégal ici.","Au nom de "+NationKingsName(npchar)+", je vous ordonne d'arrêter cette violation de la loi !");
			Link.l1 = "Non-non, officier. Moi et mes compagnons ne faisons que prendre le soleil ici.";
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
			Link.l2 = "Je fais de la charité. Est-ce vraiment illégal?";
			Link.l2.go = "GiveMeSomeMoneyToo";
			Link.l3 = "Éloignez-vous d'ici, soldat. Ce n'est pas votre affaire!";
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
			dialog.text = "Ne nous faites pas passer pour des imbéciles, capitaine "+Pchar.name+"! Personne ne s'attendrait jamais à ce qu'un homme aussi positif et respectable que vous fasse de la contrebande.";
			Link.l1 = "Personne n'est parfait. Mais je regrette déjà!";
			Link.l1.go = "ThisTimeFree_1";
			Link.l2 = "Je vais te couper la tête tout de suite.";
			Link.l2.go = "ThisTimeFree_fight";				
		break;

		case "ThisTimeFree_1":	
			dialog.snd = "Voice\COGU\COGU003";	
			dialog.text = "J'ai entendu parler de toi, seulement des choses positives alors je te laisserai partir cette fois mais ne le fais plus. Je ne peux pas en dire autant de ces gars-là par contre!";
			Link.l1 = "Mes remerciements, officier. Passez une bonne journée!";
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
			dialog.text = "Arrête de mentir !!! Je ne suis pas aveugle ! Suis-nous, tu es arrêté et tes biens sont confisqués.";
			Link.l1 = "Je ferais mieux de t'éventrer !";
			Link.l1.go = "ThisTimeFree_fight";
		break;

		case "GiveMeSomeMoneyToo":
            attrName = XI_ConvertString("Chance");
            int iRand = hrand(99, "&Bribe" + PChar.Location);
            int iMoney = PChar.Money;
            int iBaseChance = GetCharacterSkill(PChar, SKILL_SNEAK) + GetCharacterSkill(PChar, SKILL_LEADERSHIP);
			dialog.snd = "Voice\COGU\COGU005";		
			dialog.text = "Vraiment? Eh bien, cette activité est complètement légale... si nous obtenions notre part bien sûr. Et combien est grande votre charité?";
            if (iMoney >= 25000)
            {
                iTemp = iBaseChance > 100 ? 100 : iBaseChance;
                link.l1 = "Pour vous, officier, j'ai 25000 pesos! (" + attrName + " " + iTemp + "%)";
                link.l1.go = iTemp > iRand ? "MoneyAccepted10" : "TryingToGiveBribe";
            }
            if (iMoney >= 12000)
            {
                iTemp = iBaseChance / 2 + 10;
                if (iTemp > 100) iTemp = 100;
                link.l2 = "Et si 12000 pesos? (" + attrName + " " + iTemp + "%)";
                link.l2.go = iTemp > iRand ? "MoneyAccepted5" : "TryingToGiveBribe";
            }
            if (iMoney >= 5000)
            {
                iTemp = iBaseChance / 2 - 10;
                if (iTemp > 100) iTemp = 100;
                link.l3 = "Je pense que 5000 pesos seront suffisants. (" + attrName + " " + iTemp + "%)";
                link.l3.go = iTemp > iRand ? "MoneyAccepted2" : "TryingToGiveBribe";
            }
			link.l4 = StringFromKey("smuggling_3");
			link.l4.go = "ThisTimeFree_fight";
		break;

		case "TryingToGiveBribe":
			dialog.snd = "Voice\COGU\COGU006";
			dialog.text = "Un pot-de-vin? Non, j'ai mon honneur! Alors, voudriez-vous bien nous suivre!";
			Link.l1 = "Zut ! Désolé de vous décevoir, mais je ne vais nulle part !";
			Link.l1.go = "ThisTimeFree_fight";
		break;

		case "MoneyAccepted10":
            AddMoneyToCharacter(PChar, -25000);
			dialog.snd = "Voice\COGU\COGU007";
			dialog.text = "Ma gratitude pour votre charité.";
			Link.l1 = "Toujours à votre service.";
			Link.l1.go = "GettingLostFromHere_exit";
			AddMoneyToCharacter(pchar, -int(int(Pchar.money)/10));
		break;
		
		case "MoneyAccepted5":
            AddMoneyToCharacter(PChar, -12000);
			dialog.snd = "Voice\COGU\COGU007";
			dialog.text = "Ma gratitude pour votre charité.";
			Link.l1 = "Toujours à votre service.";
			Link.l1.go = "GettingLostFromHere_exit";
			AddMoneyToCharacter(pchar, -int(int(Pchar.money)/5));
		break;
		
		case "MoneyAccepted2":
            AddMoneyToCharacter(PChar, -5000);
			dialog.snd = "Voice\COGU\COGU007";
			dialog.text = "Ma gratitude pour votre charité.";
			Link.l1 = "Toujours à votre service.";
			Link.l1.go = "GettingLostFromHere_exit";
			AddMoneyToCharacter(pchar, -int(int(Pchar.money)/2));
		break;

		case "GettingLostFromHere":
			dialog.snd = "Voice\COGU\COGU008";
			dialog.text = "Mais... sacrebleu! Je dois vous arrêter!";
			Link.l1 = "Quoi?! Tu es toujours ici? Trop fatigué de la vie?";
			Link.l1.go = "GettingLostFromHere_1";
		break;

		case "GettingLostFromHere_1":
			dialog.snd = "Voice\COGU\COGU009";
			dialog.text = "Je... Je vais me plaindre! Je ne vais pas laisser passer ça comme ça....";
			Link.l1 = "Hein!";
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
			dialog.text = "Fils de ...! Maudit chien! Cette baie deviendra ta tombe!";
			Link.l1 = "Viens ici et essaie de le prouver!";
			Link.l1.go = "ThisTimeFree_fight";
		break;
	}
}
