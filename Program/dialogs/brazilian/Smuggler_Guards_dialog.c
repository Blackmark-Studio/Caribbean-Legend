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
			dialog.text = RandPhraseSimple("Parece que você está fazendo algo ilegal aqui.","Em nome de "+NationKingsName(npchar)+", eu ordeno que pare com essa ilegalidade!");
			Link.l1 = "Não, não, oficial. Meus amigos e eu só estamos tomando sol aqui.";
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
			Link.l2 = "Eu faço caridade. Isso é mesmo ilegal?";
			Link.l2.go = "GiveMeSomeMoneyToo";
			Link.l3 = "Saia daqui, soldado. Isso não é da sua conta!";
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
			dialog.text = "Não nos faça de bobos, Capitão "+Pchar.name+"! Ninguém jamais imaginaria que um homem tão positivo e respeitável como você fosse contrabandear.";
			Link.l1 = "Ninguém é perfeito. Mas já me arrependo disso!";
			Link.l1.go = "ThisTimeFree_1";
			Link.l2 = "Vou cortar sua cabeça agora mesmo.";
			Link.l2.go = "ThisTimeFree_fight";				
		break;

		case "ThisTimeFree_1":	
			dialog.snd = "Voice\COGU\COGU003";	
			dialog.text = "Ouvi falar de você, só coisas boas, então vou deixar passar dessa vez, mas não faça de novo. Já esses caras aqui, não posso dizer o mesmo!";
			Link.l1 = "Meu obrigado, oficial. Tenha um bom dia!";
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
			dialog.text = "Pare de mentir!!! Eu não sou cego! Venha conosco, você está preso e suas mercadorias serão confiscadas.";
			Link.l1 = "É melhor eu arrancar suas tripas!";
			Link.l1.go = "ThisTimeFree_fight";
		break;

		case "GiveMeSomeMoneyToo":
            attrName = XI_ConvertString("Chance");
            int iRand = hrand(99, "&Bribe" + PChar.Location);
            int iMoney = PChar.Money;
            int iBaseChance = GetCharacterSkill(PChar, SKILL_SNEAK) + GetCharacterSkill(PChar, SKILL_LEADERSHIP);
			dialog.snd = "Voice\COGU\COGU005";		
			dialog.text = "Sério? Bem, essa atividade é totalmente legal... se a gente receber a nossa parte, claro. E quão generosa é a sua caridade?";
            if (iMoney >= 25000)
            {
                iTemp = iBaseChance > 100 ? 100 : iBaseChance;
                link.l1 = "Para você, oficial, eu tenho 25000 pesos! (" + attrName + " " + iTemp + "%)";
                link.l1.go = iTemp > iRand ? "MoneyAccepted10" : "TryingToGiveBribe";
            }
            if (iMoney >= 12000)
            {
                iTemp = iBaseChance / 2 + 10;
                if (iTemp > 100) iTemp = 100;
                link.l2 = "Que tal 12000 pesos? (" + attrName + " " + iTemp + "%)";
                link.l2.go = iTemp > iRand ? "MoneyAccepted5" : "TryingToGiveBribe";
            }
            if (iMoney >= 5000)
            {
                iTemp = iBaseChance / 2 - 10;
                if (iTemp > 100) iTemp = 100;
                link.l3 = "Acho que 5000 pesos serão suficientes. (" + attrName + " " + iTemp + "%)";
                link.l3.go = iTemp > iRand ? "MoneyAccepted2" : "TryingToGiveBribe";
            }
			link.l4 = StringFromKey("smuggling_3");
			link.l4.go = "ThisTimeFree_fight";
		break;

		case "TryingToGiveBribe":
			dialog.snd = "Voice\COGU\COGU006";
			dialog.text = "Suborno? Não, eu prezo minha honra! Então, poderia nos acompanhar, por favor!";
			Link.l1 = "Droga! Desculpe te decepcionar, mas eu não vou a lugar nenhum!";
			Link.l1.go = "ThisTimeFree_fight";
		break;

		case "MoneyAccepted10":
            AddMoneyToCharacter(PChar, -25000);
			dialog.snd = "Voice\COGU\COGU007";
			dialog.text = "Meu agradecimento pela sua gentileza.";
			Link.l1 = "Sempre ao seu dispor.";
			Link.l1.go = "GettingLostFromHere_exit";
			AddMoneyToCharacter(pchar, -int(int(Pchar.money)/10));
		break;
		
		case "MoneyAccepted5":
            AddMoneyToCharacter(PChar, -12000);
			dialog.snd = "Voice\COGU\COGU007";
			dialog.text = "Meu agradecimento pela sua gentileza.";
			Link.l1 = "Sempre ao seu dispor.";
			Link.l1.go = "GettingLostFromHere_exit";
			AddMoneyToCharacter(pchar, -int(int(Pchar.money)/5));
		break;
		
		case "MoneyAccepted2":
            AddMoneyToCharacter(PChar, -5000);
			dialog.snd = "Voice\COGU\COGU007";
			dialog.text = "Meu agradecimento pela sua gentileza.";
			Link.l1 = "Sempre às suas ordens.";
			Link.l1.go = "GettingLostFromHere_exit";
			AddMoneyToCharacter(pchar, -int(int(Pchar.money)/2));
		break;

		case "GettingLostFromHere":
			dialog.snd = "Voice\COGU\COGU008";
			dialog.text = "Mas... droga! Eu tenho que te prender!";
			Link.l1 = "O quê?! Você ainda está aqui? Cansou da vida?";
			Link.l1.go = "GettingLostFromHere_1";
		break;

		case "GettingLostFromHere_1":
			dialog.snd = "Voice\COGU\COGU009";
			dialog.text = "Eu... eu vou reclamar! Não vou deixar isso passar assim...";
			Link.l1 = "Hã!";
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
			dialog.text = "Filho da...! Maldito cachorro! Esta baía vai ser sua sepultura!";
			Link.l1 = "Venha aqui e tente provar!";
			Link.l1.go = "ThisTimeFree_fight";
		break;
	}
}
