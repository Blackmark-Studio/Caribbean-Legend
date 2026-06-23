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
			dialog.text = RandPhraseSimple("Es scheint, dass Sie hier etwas Illegales tun.","Im Namen von "+NationKingsName(npchar)+", ich befehle dir, diese Gesetzesübertretung zu stoppen!");
			Link.l1 = "Nein-nein, Offizier. Ich und meine Kumpels sonnen uns nur hier.";
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
			Link.l2 = "Ich tue Wohltätigkeit. Ist das wirklich illegal?";
			// belamour legendary edition включим обаяние ГГ, если оно есть
			if(CheckCharacterPerk(pchar, "Trustworthy"))
			{
				Link.l2.go = "GiveMeSomeMoneyToo";
			}
			else
			{
				if(int(Pchar.rank) >= 4 && GetSummonSkillFromNameToOld(Pchar, SKILL_COMMERCE) >= 5)
				{
					Link.l2.go = "GiveMeSomeMoneyToo";
				}
				else
				{
				Link.l2.go = "TryingToGiveBribe";
				}
			}
			Link.l3 = "Verzieh dich von hier, Soldat. Das geht dich nichts an!";
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
			dialog.text = "Mach uns nicht zu Narren, Kapitän "+Pchar.name+"! Niemand würde jemals erwarten, dass so ein positiver und respektabler Mann wie du schmuggeln würde.";
			Link.l1 = "Niemand ist perfekt. Aber ich bereue es schon!";
			Link.l1.go = "ThisTimeFree_1";
			Link.l2 = "Ich werde dir jetzt den Kopf abschneiden.";
			Link.l2.go = "ThisTimeFree_fight";				
		break;

		case "ThisTimeFree_1":	
			dialog.snd = "Voice\COGU\COGU003";	
			dialog.text = "Ich habe von Ihnen gehört, nur positive Dinge, also lasse ich Sie dieses Mal gehen, aber tun Sie es nicht noch einmal. Kann das gleiche über diese Burschen allerdings nicht sagen!";
			Link.l1 = "Mein Dank, Offizier. Haben Sie einen schönen Tag!";
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
			dialog.text = "Hör auf zu lügen!!! Ich bin nicht blind! Folge uns, du bist verhaftet und deine Waren werden konfisziert.";
			Link.l1 = "Ich sollte besser deine Eingeweide rausreißen!";
			Link.l1.go = "ThisTimeFree_fight";
		break;

		case "GiveMeSomeMoneyToo":	
			dialog.snd = "Voice\COGU\COGU005";		
			dialog.text = "Wirklich? Nun, diese Aktivität ist völlig legal... wenn wir natürlich unseren Teil bekommen würden. Und wie großzügig sind Sie?";
			Link.l1 = "Ich denke, dass"+int(int(Pchar.money)/10)+" Pesos werden genug sein.";
			if(int(Pchar.rank)*1000 <= int(int(Pchar.money)/10))
			{
				Link.l1.go = "MoneyAccepted10";
			}
			else
			{
				Link.l1.go = "TryingToGiveBribe";
			}

			Link.l2 = "Wie wäre es mit "+int(int(Pchar.money)/5)+" Pesos?";
			if(int(Pchar.rank)*1000 <= int(int(Pchar.money)/5))
			{
				Link.l2.go = "MoneyAccepted5";
			}
			else
			{
				Link.l2.go = "TryingToGiveBribe";
			}

			Link.l3 = "Für Sie, Offizier, habe ich "+int(int(Pchar.money)/2)+" Pesos!";
			if(int(Pchar.rank)*1000 <= int(int(Pchar.money)/2))
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
			dialog.text = "Eine Bestechung? Nein, meine Ehre ist mir wichtig! Also, würden Sie bitte so freundlich sein, uns zu folgen!";
			Link.l1 = "Verdammt! Es tut mir leid, dich zu enttäuschen, aber ich gehe nirgendwo hin!";
			Link.l1.go = "ThisTimeFree_fight";
		break;

		case "MoneyAccepted10":
			dialog.snd = "Voice\COGU\COGU007";
			dialog.text = "Mein Dank für Eure Wohltätigkeit.";
			Link.l1 = "Immer zu Ihren Diensten.";
			Link.l1.go = "GettingLostFromHere_exit";
			AddMoneyToCharacter(pchar, -int(int(Pchar.money)/10));
		break;
		
		case "MoneyAccepted5":
			dialog.snd = "Voice\COGU\COGU007";
			dialog.text = "Mein Dank für Ihre Wohltätigkeit.";
			Link.l1 = "Immer zu Euren Diensten.";
			Link.l1.go = "GettingLostFromHere_exit";
			AddMoneyToCharacter(pchar, -int(int(Pchar.money)/5));
		break;
		
		case "MoneyAccepted2":
			dialog.snd = "Voice\COGU\COGU007";
			dialog.text = "Meine Dankbarkeit für Ihre Nächstenliebe.";
			Link.l1 = "Immer zu Ihren Diensten.";
			Link.l1.go = "GettingLostFromHere_exit";
			AddMoneyToCharacter(pchar, -int(int(Pchar.money)/2));
		break;

		case "GettingLostFromHere":
			dialog.snd = "Voice\COGU\COGU008";
			dialog.text = "Aber... verdammt! Ich muss dich verhaften!";
			Link.l1 = "Was?! Du bist immer noch hier? Lebensmüde?";
			Link.l1.go = "GettingLostFromHere_1";
		break;

		case "GettingLostFromHere_1":
			dialog.snd = "Voice\COGU\COGU009";
			dialog.text = "Ich... Ich werde mich beschweren! Ich werde das nicht einfach so hinnehmen....";
			Link.l1 = "Hä!";
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
			dialog.text = "Sohn einer ...! Verdammter Hund! Diese Bucht wird dein Grab!";
			Link.l1 = "Komm her und versuche das zu beweisen!";
			Link.l1.go = "ThisTimeFree_fight";
		break;
	}
}
