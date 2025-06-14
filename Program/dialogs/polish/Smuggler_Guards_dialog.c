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
			dialog.text = RandPhraseSimple("Wygląda na to, że robisz tu coś nielegalnego.","W imię "+NationKingsName(npchar)+", Nakazuję Ci przerwać te bezprawne czyny!");
			Link.l1 = "Nie, nie, oficerze. Ja i moi koledzy tylko zażywamy kąpieli słonecznej.";
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
			Link.l2 = "Praktykuję dobroczynność. Czy to naprawdę jest nielegalne?";
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
			Link.l3 = "Zjeżdżaj stąd, żołnierzu. To nie twoja sprawa!";
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
			dialog.text = "Nie rób z nas głupców, kapitanie "+Pchar.name+"! Nikt by nigdy nie przypuszczał, że taki pozytywny i szanowany człowiek jak ty będzie powiązany z przemytem.";
			Link.l1 = "Nikt nie jest doskonały. Ale już żałuję!";
			Link.l1.go = "ThisTimeFree_1";
			Link.l2 = "Taki już jest świat, oficerze. A teraz wybacz, ale nie moge ci pozwolić stąd odejść.";
			Link.l2.go = "ThisTimeFree_fight";				
		break;

		case "ThisTimeFree_1":	
			dialog.snd = "Voice\COGU\COGU003";	
			dialog.text = "Słyszałem o tobie, tylko pozytywne rzeczy, więc tym razem cię puszcze, ale nie rób tego ponownie. Nie mogę powiedzieć tego samego o tych gościach!";
			Link.l1 = "Dziękuję, oficerze. Miłego dnia!";
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
			dialog.text = "Przestań kłamać!!! Nie jestem ślepy! Idziesz z nami, jesteś aresztowany, a twoje towary zostaną skonfiskowane.";
			Link.l1 = "Nie po to zabezpieczałem ten ładunek przez tyle czasu, żeby go teraz stracić! Wole wypruć wam wszystkim flaki!";
			Link.l1.go = "ThisTimeFree_fight";
		break;

		case "GiveMeSomeMoneyToo":	
			dialog.snd = "Voice\COGU\COGU005";		
			dialog.text = "Naprawdę? Cóż, ta aktywność jest całkowicie legalna... jeśli oczywiście dostaniemy naszą część. I jak wielka jest twoja hojność?";
			Link.l1 = "Myslę, że"+makeint(sti(Pchar.money)/10)+" pesos będzie wystarczające.";
			if(makeint(Pchar.rank)*1000 <= makeint(sti(Pchar.money)/10))
			{
				Link.l1.go = "MoneyAccepted10";
			}
			else
			{
				Link.l1.go = "TryingToGiveBribe";
			}

			Link.l2 = "Co powiesz na "+makeint(sti(Pchar.money)/5)+" pesos?";
			if(makeint(Pchar.rank)*1000 <= makeint(sti(Pchar.money)/5))
			{
				Link.l2.go = "MoneyAccepted5";
			}
			else
			{
				Link.l2.go = "TryingToGiveBribe";
			}

			Link.l3 = "Dla ciebie, oficerze, mam "+makeint(sti(Pchar.money)/2)+" pesos!";
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
			dialog.text = "Łapówka? Nie, ja dbam o mój honor! Więc, czy byłbyś tak uprzejmy iść z nami!";
			Link.l1 = "Cholera! Przykro mi cię rozczarować, ale nigdzie nie ide!";
			Link.l1.go = "ThisTimeFree_fight";
		break;

		case "MoneyAccepted10":
			dialog.snd = "Voice\COGU\COGU007";
			dialog.text = "Moja wdzięczność za twoją hojność.";
			Link.l1 = "Do usług.";
			Link.l1.go = "GettingLostFromHere_exit";
			AddMoneyToCharacter(pchar, -makeint(sti(Pchar.money)/10));
		break;
		
		case "MoneyAccepted5":
			dialog.snd = "Voice\COGU\COGU007";
			dialog.text = "Moja wdzięczność za twoją hojność.";
			Link.l1 = "Do usług.";
			Link.l1.go = "GettingLostFromHere_exit";
			AddMoneyToCharacter(pchar, -makeint(sti(Pchar.money)/5));
		break;
		
		case "MoneyAccepted2":
			dialog.snd = "Voice\COGU\COGU007";
			dialog.text = "Moja wdzięczność za twoją hojność.";
			Link.l1 = "Do usług.";
			Link.l1.go = "GettingLostFromHere_exit";
			AddMoneyToCharacter(pchar, -makeint(sti(Pchar.money)/2));
		break;

		case "GettingLostFromHere":
			dialog.snd = "Voice\COGU\COGU008";
			dialog.text = "Ale... cholera! Muszę cię aresztować!";
			Link.l1 = "Co?! Wciąż tu jesteś? Zmęczony życiem?";
			Link.l1.go = "GettingLostFromHere_1";
		break;

		case "GettingLostFromHere_1":
			dialog.snd = "Voice\COGU\COGU009";
			dialog.text = "Ja... Ja się poskarżę! Nie pozwolę tak na to zostawić....";
			Link.l1 = "Hej, wracaj tu!";
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
			dialog.text = "Ty su...! Cholerny psie! Ta zatoka stanie się twoim grobem!";
			Link.l1 = "W takim razie chodź i udowodnij mi to!";
			Link.l1.go = "ThisTimeFree_fight";
		break;
	}
}
