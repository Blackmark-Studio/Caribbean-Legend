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
			
			dialog.text = GetFullName(PChar)+"! "+"Faz tempo que estamos te procurando, e finalmente você é nosso.";
			Link.l1 = "Quem é você e o que quer de mim?";
			Link.l1.go = "meeting"; 
			
			PChar.GenQuest.HunterStart = true;
		break;

		case "meeting":
			dialog.text = XI_ConvertString(Nations[sti(NPChar.nation)].Name)+" colocaram uma boa recompensa pela sua cabeça, temos que te entregar em qualquer uma das colônias deles e vamos receber, esteja você vivo ou morto.";
			Link.l1 = "Escuta, eu te pago se me deixar em paz.";
			Link.l1.go = "Cost_Head"; 
            // boal 08.04.04 -->
            if (GetSummonSkillFromNameToOld(PChar, SKILL_SNEAK) > 2 || bBettaTestMode)
            {
    			TempChar = characterFromID("Bug Fixer");
    			SetRandomNameToCharacter(TempChar);
    			Link.l2 = ""+GetSexPhrase("Com licença, mas você deve estar enganado. Eu sou "+GetFullName(TempChar)+" - um comerciante muito conhecido nessas terras.","Com licença, mas você deve estar enganado. Eu sou apenas uma garota simples, e meu pai é "+GetFullName(TempChar)+" - um comerciante bem conhecido nessas terras.")+".";
    			Link.l2.go = "lier";
			}
            Link.l3 = "Certo, você pode tentar a sorte, se assim desejar.";
			Link.l3.go = "battle";
		break;
        
        case "lier":
            if (GetSummonSkillFromName(pchar, SKILL_SNEAK) > rand(150) || bBettaTestMode)
            {
                dialog.text = "Oh! Podemos mesmo estar enganados. Por favor, nos perdoe, "+GetAddress_Form(NPChar)+".";
                Link.l1 = "Acontece, não se preocupe com isso...";
                Link.l1.go = "lier_2";
                AddCharacterExpToSkill(pchar, SKILL_SNEAK, 100);
            }
            else
            {
                dialog.text = "Acho que você está mentindo!";
                Link.l1 = "Escuta, eu te pago se me deixar em paz.";
			    Link.l1.go = "Cost_Head";
			    Link.l2 = "Certo, pode tentar a sorte, se assim desejar.";
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
			dialog.text = "Acho que "+PChar.HunterCost+" pesos vão servir muito bem para nós.";
            if(makeint(Pchar.money) < sti(PChar.HunterCost))
            {
                Link.l1 = "Mas eu não tenho esse tipo de dinheiro.";
                Link.l1.go = "NoMoney";
            }else{
                Link.l1 = "Aqui está o seu dinheiro, pega e desaparece.";
                Link.l1.go = "Cost_Head2";
                Link.l2 = "Dar uma quantia dessas para canalhas como vocês... Acho que prefiro abrir todos vocês aqui mesmo!";
                Link.l2.go = "battle";
            }
		break;

        case "NoMoney":
			dialog.text = "Nesse caso, nossa conversa acabou!";
			Link.l1 = "Você nunca vai me pegar vivo.";
			Link.l1.go = "battle"; 
		break;
		
		case "TreasureHunter":
			dialog.text = "Espere, "+GetSexPhrase("companheiro","moça")+"... Acho que você tem algo interessante com você. Amigos deveriam compartilhar os tesouros que encontram entre si, não acha?";
            Link.l1 = "Olha, eu te pago se me deixar em paz.";
			Link.l1.go = "Cost_Head";
            // boal 08.04.04 -->
            if (GetSummonSkillFromNameToOld(PChar, SKILL_SNEAK) > 3)
            {
    			TempChar = characterFromID("Bug Fixer");
    			SetRandomNameToCharacter(TempChar);
    			Link.l2 = ""+GetSexPhrase("Com licença, mas você deve estar enganado. Eu sou "+GetFullName(TempChar)+" - um cidadão bem conhecido por estas terras, mas certamente não um caçador de tesouros.","Com licença, mas você deve estar enganado. Sou apenas uma garota simples, não uma caçadora de tesouros. E meu pai é "+GetFullName(TempChar)+" - um cidadão bem conhecido por estas bandas")+"!";
    			Link.l2.go = "TreasureHunterLier";
			}
            Link.l3 = "Bem, parece que chegou a hora de suas cabeças se separarem de seus corpos.";
			Link.l3.go = "battle";
		break;
		
		case "TreasureHunterLier":
            if (GetSummonSkillFromName(pchar, SKILL_SNEAK) > rand(150))
            {
                dialog.text = "Oh! Então talvez estejamos mesmo enganados. Por favor, nos perdoe, "+GetAddress_Form(NPChar)+".";
                Link.l1 = "Acontece, não se preocupe com isso...";
                Link.l1.go = "lier_2";
                AddCharacterExpToSkill(pchar, SKILL_SNEAK, 100);
            }
            else
            {
                dialog.text = "Acho que você está mentindo!";
			    Link.l1 = "Então ouça a canção da minha lâmina.";
			    Link.l1.go = "battle";
			    AddCharacterExpToSkill(pchar, SKILL_SNEAK, 50);
            }
        break;
		
		case "TreasureCaptain":
			dialog.text = LinkRandPhrase("Então foi você quem pegou meu mapa do tesouro! Acho que está na hora de devolver tudo o que você levou...","Oh, um rival! Você não vai longe, carregando o peso dos meus tesouros...","Ah, finalmente te encontrei! Todos os tesouros desta caverna são meus, entendeu? Agora, esvazie os bolsos, camarada!");
			Link.l1 = LinkRandPhrase("Chegou a hora de você conhecer minha lâmina, camarada!","Seus tesouros? Você quis dizer que eram seus, porque agora são meus!","Eu prefiro abrir suas tripas com minha lâmina, camarada.");
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
			dialog.text = LinkRandPhrase("Então, o coronel estava certo, o tesouro estava escondido nesta caverna... Esvazie os bolsos, marinheiro!","Então finalmente te alcançamos depois de toda essa perseguição por essas malditas selvas, espinhos e pântanos. Agora, desgraçado, você vai nos entregar tudo...","Ei, marinheiro! Esses tesouros do pirata são nossos, então tire suas mãos imundas daí!");
			Link.l1 = LinkRandPhrase("Com certeza, eu não esperava isso de um oficial do exército! Mas tudo bem, vou te dar uma lição mesmo assim...","Olha só pra ele, um pirata vestindo uniforme de oficial...","De fato, soldados e piratas não são tão diferentes hoje em dia...");
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
			dialog.text = "E aí vem o nosso ouro. Pelo menos a espera não foi em vão.";
			link.l1 = RandPhraseSimple("Do que estão falando, senhores? Sou representante da Companhia Holandesa das Índias Ocidentais e só estou de passagem por aqui! Parei apenas para admirar a vista da costa!","Receio que você me confundiu com outra pessoa. Eu sou "+GetSexPhrase("Francua Marie Paganel, ","Maria-Theresa, ")+"um naturalista. Estou coletando amostras da flora local aqui. Quer dar uma olhada na minha coleção de folhas de mandioca? Tenho algumas bem interessantes!");
			link.l1.go = "ReasonToFast_THunter_2";
			link.l2 = "O que você quer?! Fique fora do meu caminho!";
			link.l2.go = "ReasonToFast_THunter_2";
		break;
		
		case "ReasonToFast_THunter_2":
			ReasonToFast_ClearTreasureBox(pchar.questTemp.ReasonToFast.Treasure.Location);
			dialog.text = "Ah não, "+GetSexPhrase("meu querido amigo","minha garota bonita")+". Isso não vai funcionar. Sabemos com certeza que você era o dono do mapa de "+GetName(pchar.questTemp.ReasonToFast.mapIdx,pchar.questTemp.ReasonToFast.map,NAME_GEN)+". E ele era tão avarento que seus baús estavam quase explodindo de tanto dinheiro. Então não vamos sair de mãos vazias.";
			link.l1 = "Você está certo. Os baús estavam realmente cheios. Mas você não vai ficar com eles. Pode até tentar visitar aquela caverna, deve ter uns baldes furados por lá ainda.";
			link.l1.go = "ReasonToFast_THunter_3";
			if(ReasonToFast_CheckTreasureQty("icollection", sti(pchar.questTemp.ReasonToFast.p8)) >= sti(pchar.questTemp.ReasonToFast.p8) 
				&& ReasonToFast_CheckTreasureQty("Chest", sti(pchar.questTemp.ReasonToFast.p7)) >= sti(pchar.questTemp.ReasonToFast.p7))
			{
				link.l2 = "Você está certo. Pode ficar com o seu tesouro. Só lembre que ele não vai te trazer felicidade, pois está manchado de sangue.";
				link.l2.go = "ReasonToFast_THunter_4";
			}	
		break;
		
		case "ReasonToFast_THunter_3":
			dialog.text = ""+GetSexPhrase("Hein, capitão, você é jovem demais pra morrer, não é...","Heh, garota, você é jovem demais pra morrer, não é...")+"...";
			link.l1 = "Na verdade, eu não vou morrer!";
			link.l1.go = "ReasonToFastTHunter_Fight";
		break;
		
		case "ReasonToFast_THunter_4":
			dialog.text = "Agora sim, essas são as palavras de alguém sensato!";
			link.l1 = "Maldito seja você e todos esses tesouros...";
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
			dialog.text = "Ei,"+GetSexPhrase("companheiro","moça")+"! "+GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_NOM)+" disseram que você tinha algo para nós.";
			link.l1 = "O que você quer dizer?";
			link.l1.go = "ReasonToFast_HunterShore11";
			pchar.quest.ReasonToFast_SetHunterPort_1.over = "yes";
			pchar.quest.ReasonToFast_SetHunterPort_2.over = "yes";
		break;

		case "ReasonToFast_HunterShore11":
			if(pchar.questTemp.ReasonToFast == "GetMap") 
			{
				dialog.text = "Um mapa de "+GetName(pchar.questTemp.ReasonToFast.mapIdx,pchar.questTemp.ReasonToFast.map,NAME_GEN);
				link.l1 = "Pegue isso e mande um alô para "+GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_DAT)+". Diga a ele que em breve nos encontraremos...";
				link.l1.go = "ReasonToFast_HunterShore12_1";
				link.l2 = GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_NOM)+" está redondamente enganado se acha que vou tirar as castanhas do fogo por ele.";
				link.l2.go = "ReasonToFast_HunterShore23";
			}
			if(pchar.questTemp.ReasonToFast == "LakeyExitSuccess")
			{
				dialog.text = "Joias que você roubou do governador.";
				if(ReasonToFast_CheckTreasureQty("icollection", sti(pchar.questTemp.ReasonToFast.p8)) >= sti(pchar.questTemp.ReasonToFast.p8) 
					&& ReasonToFast_CheckTreasureQty("Chest", sti(pchar.questTemp.ReasonToFast.p7)) >= sti(pchar.questTemp.ReasonToFast.p7))
				{
					link.l1 = "Pegue isso e mande lembranças para "+GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_DAT)+". Diga a ele que em breve nos encontraremos...";
					link.l1.go = "ReasonToFast_HunterShore12_2";
				}	
				link.l2 = GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_NOM)+" está muito enganado se acha que vou tirar as castanhas do fogo por ele.";
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
			dialog.text = "Ei,"+GetSexPhrase("companheiro","moça")+"! "+GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_GEN)+" tem várias perguntas para você.";
			link.l1 = "E por que ele mesmo não perguntaria a eles?";
			link.l1.go = "ReasonToFast_HunterShore21";
			chrDisableReloadToLocation = false;
		break;
		
		case "ReasonToFast_HunterShore21":
			dialog.text = "Não de acordo com o posto dele. Você arruinou nossa operação e nós perdemos "+sti(pchar.questTemp.ReasonToFast.p10)+" pesos por sua culpa. Agora você tem uma dívida a pagar.";
			link.l1 = "Pegue isso e mande um alô para "+GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_DAT)+". Diga a ele que em breve nos encontraremos...";
			link.l1.go = "ReasonToFast_HunterShore22";
			link.l2 = GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_NOM)+" está muito enganado se acha que vou tirar as castanhas do fogo por ele.";
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
				dialog.text = "Ah, você não tem esse tipo de dinheiro! Bem, você fez sua escolha... ";
				link.l1 = "Há muito tempo...";
				link.l1.go = "ReasonToFastTHunter_Fight";	
				if(pchar.questTemp.ReasonToFast == "LakeyExitSuccess" || pchar.questTemp.ReasonToFast == "LakeyExitFail")
				{
					pchar.quest.ReasonToFast_SetPirateShip.win_condition.l1 = "MapEnter";
					pchar.quest.ReasonToFast_SetPirateShip.function = "ReasonToFast_PreparePirateShip";
				}
			}
		break;
		
		case "ReasonToFast_HunterShore23":
			dialog.text = "Bem, você fez sua escolha...";
			link.l1 = "Há muito tempo...";
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
