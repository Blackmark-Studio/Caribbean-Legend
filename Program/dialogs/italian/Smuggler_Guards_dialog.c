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
			dialog.text = RandPhraseSimple("Sembra che stai commettendo qualcosa di illegale qui.","Nel nome di "+NationKingsName(npchar)+", ti ordino di smettere questa illegalità!");
			Link.l1 = "No-no, ufficiale. Io e i miei compagni stiamo solo prendendo il sole qui.";
			// belamour legendary edition включим обаяние ГГ, если оно есть
			if(CheckCharacterPerk(pchar, "Trustworthy"))
			{
				Link.l1.go = "ThisTimeFree";
			}
			else
			{
				if (makeint(pchar.reputation.nobility) >= 70 && GetSummonSkillFromNameToOld(Pchar, SKILL_LEADERSHIP) >= 5)
				{
					Link.l1.go = "ThisTimeFree";
				}
				else
				{
				Link.l1.go = "IDontBelieveYou";
				}
			}
			Link.l2 = "Faccio beneficenza. È davvero illegale?";
			// belamour legendary edition включим обаяние ГГ, если оно есть
			if(CheckCharacterPerk(pchar, "Trustworthy"))
			{
				Link.l2.go = "GiveMeSomeMoneyToo";
			}
			else
			{
				if(makeint(Pchar.rank) >= 4 && GetSummonSkillFromNameToOld(Pchar, SKILL_COMMERCE) >= 5)
				{
					Link.l2.go = "GiveMeSomeMoneyToo";
				}
				else
				{
				Link.l2.go = "TryingToGiveBribe";
				}
			}
			Link.l3 = "Allontanati da qui, soldato. Non sono affari tuoi!";
			if(makeint(pchar.reputation.nobility) <= 25 && FencingSkills)
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
			dialog.text = "Non prenderci per imbecilli, capitano "+Pchar.name+"! Nessuno si aspetterebbe mai che un uomo così positivo e rispettabile come te si occupi di contrabbando.";
			Link.l1 = "Nessuno è perfetto. Ma già me ne pento!";
			Link.l1.go = "ThisTimeFree_1";
			Link.l2 = "Sto per tagliarti la testa proprio ora.";
			Link.l2.go = "ThisTimeFree_fight";				
		break;

		case "ThisTimeFree_1":	
			dialog.snd = "Voice\COGU\COGU003";	
			dialog.text = "Ho sentito parlare di te, solo cose positive quindi ti lascio andare questa volta ma non farlo di nuovo. Non posso dire lo stesso di questi signori però!";
			Link.l1 = "Grazie mille, ufficiale. Buona giornata!";
			Link.l1.go = "ThisTimeFree_exit";
		break;

		case "ThisTimeFree_fight":	
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться 130313
			ChangeCharacterNationReputation(pchar, sti(NPChar.Nation), -1);
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = NPC_Meeting;
			DialogExit();
			for (i = 1; i <= sti(Pchar.quest.contraband.SoldierQty); i++)
			{
    			attrName = "SoldierIDX"+i;
				sld = GetCharacter(sti(Pchar.quest.contraband.(attrName)));
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
			for (i = 1; i <= sti(Pchar.quest.contraband.SoldierQty); i++)
			{
    			attrName = "SoldierIDX"+i;
				sld = GetCharacter(sti(Pchar.quest.contraband.(attrName)));
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
			dialog.text = "Smettila di mentire!!! Non sono cieco! Seguici, sei arrestato e le tue merci sono confiscate.";
			Link.l1 = "È meglio se ti strappo le budella!";
			Link.l1.go = "ThisTimeFree_fight";
		break;

		case "GiveMeSomeMoneyToo":	
			dialog.snd = "Voice\COGU\COGU005";		
			dialog.text = "Davvero? Beh, questa attività è completamente legale... se ottenessimo la nostra parte, ovviamente. E quanto grande è la tua carità?";
			Link.l1 = "Credo che"+makeint(sti(Pchar.money)/10)+" pesos saranno sufficienti.";
			if(makeint(Pchar.rank)*1000 <= makeint(sti(Pchar.money)/10))
			{
				Link.l1.go = "MoneyAccepted10";
			}
			else
			{
				Link.l1.go = "TryingToGiveBribe";
			}

			Link.l2 = "E che ne dici "+makeint(sti(Pchar.money)/5)+" pesos?";
			if(makeint(Pchar.rank)*1000 <= makeint(sti(Pchar.money)/5))
			{
				Link.l2.go = "MoneyAccepted5";
			}
			else
			{
				Link.l2.go = "TryingToGiveBribe";
			}

			Link.l3 = "Per te, ufficiale, ho "+makeint(sti(Pchar.money)/2)+" pesos!";
			if(makeint(Pchar.rank)*1000 <= makeint(sti(Pchar.money)/2))
			{
				Link.l3.go = "MoneyAccepted2";
			}
			else
			{
				Link.l3.go = "TryingToGiveBribe";
			}
		break;

		case "TryingToGiveBribe":
			dialog.snd = "Voice\COGU\COGU006";
			dialog.text = "Una tangente? No, tengo al mio onore! Quindi, ci seguirebbe gentilmente!";
			Link.l1 = "Cavolo! Mi dispiace deluderti, ma non vado da nessuna parte!";
			Link.l1.go = "ThisTimeFree_fight";
		break;

		case "MoneyAccepted10":
			dialog.snd = "Voice\COGU\COGU007";
			dialog.text = "La mia gratitudine per la tua carità.";
			Link.l1 = "Sempre al tuo servizio.";
			Link.l1.go = "GettingLostFromHere_exit";
			AddMoneyToCharacter(pchar, -makeint(sti(Pchar.money)/10));
		break;
		
		case "MoneyAccepted5":
			dialog.snd = "Voice\COGU\COGU007";
			dialog.text = "La mia gratitudine per la tua carità.";
			Link.l1 = "Sempre al tuo servizio.";
			Link.l1.go = "GettingLostFromHere_exit";
			AddMoneyToCharacter(pchar, -makeint(sti(Pchar.money)/5));
		break;
		
		case "MoneyAccepted2":
			dialog.snd = "Voice\COGU\COGU007";
			dialog.text = "La mia gratitudine per la tua carità.";
			Link.l1 = "Sempre al tuo servizio.";
			Link.l1.go = "GettingLostFromHere_exit";
			AddMoneyToCharacter(pchar, -makeint(sti(Pchar.money)/2));
		break;

		case "GettingLostFromHere":
			dialog.snd = "Voice\COGU\COGU008";
			dialog.text = "Ma... dannazione! Devo arrestarti!";
			Link.l1 = "Cosa?! Sei ancora qui? Troppo stanco della vita?";
			Link.l1.go = "GettingLostFromHere_1";
		break;

		case "GettingLostFromHere_1":
			dialog.snd = "Voice\COGU\COGU009";
			dialog.text = "Io... Io mi lamenterò! Non lo lascio correre così....";
			Link.l1 = "Eh!";
			Link.l1.go = "GettingLostFromHere_exit";
		break;

		case "GettingLostFromHere_exit":
			ChangeContrabandRelation(pchar, 10);

			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = NPC_Meeting;
            DialogExit();
            
			StopCoastalGuardPursuit();
			for (i = 1; i <= sti(Pchar.quest.contraband.SoldierQty); i++)
			{
                attrName = "SoldierIDX"+i;
                LAi_SetActorType(&Characters[sti(Pchar.quest.contraband.(attrName))]);
                LAi_ActorRunToLocation(&Characters[sti(Pchar.quest.contraband.(attrName))], "reload", "Reload1", "none", "", "", "", 40);
			}
			LAi_SetPlayerType(Pchar);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться 130313
		break;

		case "howDareYou":
			dialog.snd = "Voice\COGU\COGU010";
			dialog.text = "Figlio di un ...! Dannato cane! Questa baia diventerà la tua tomba!";
			Link.l1 = "Vieni qui e cerca di dimostrarlo!";
			Link.l1.go = "ThisTimeFree_fight";
		break;
	}
}
