void ProcessDialogEvent()
{
	ref NPChar, sld;
	ref arItem;
	aref Link, Diag;
	int i, iShipType, iShipGoods;
	int jewelType;
	string sItemName = "";
	string sItem;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);
	int iTemp = sti(npchar.EncQty);
	string sTemp = "Patrol" + locations[FindLocation(npchar.location)].index + "_";
	string sGroup = "PatrolGroup_" + locations[FindLocation(npchar.location)].index;
	string sTemp1, sTemp2;

	switch(Dialog.CurrentNode)
	{
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();			
		break;

		case "exit_fight":
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, sGroup);
			}
			LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(sGroup, "LandEnc_PatrolAfrer");
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "exit_noFight":
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				sld.Dialog.CurrentNode = "GoodBye";
				sld.greeting = "soldier_common";
				LAi_SetWarriorType(sld);
				LAi_warrior_DialogEnable(sld, true);
				LAi_group_MoveCharacter(sld, sGroup);				
			}
			LAi_group_SetCheck(sGroup, "LandEnc_PatrolAfrer");
			DialogExit();			
		break;

		case "First Time":
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_type_actor_Reset(sld);
				LAi_RemoveCheckMinHP(sld);
			}
			if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
			{
    			if (pchar.nation == npchar.nation)
				{
					dialog.text = RandPhraseSimple("Veja só, parece que esse canalha soou o alarme em "+XI_ConvertString("Colony"+npchar.city+"Dat")+"! Pegue h"+GetSexPhrase("im","er")+"!!","Heh, olha só isso! Vários "+NationNamePeople(sti(pchar.nation))+" conseguir ser inimigos de "+NationNameAblative(sti(npchar.nation))+" Agarrem o canalha!!!");
				}
				else
				{
					dialog.text = RandPhraseSimple("Agente inimigo por perto "+XI_ConvertString("Colony"+npchar.city+"Gen")+"! Pegue h"+GetSexPhrase("im","er")+"!!","Ei, olha, "+NationNamePeople(sti(pchar.nation))+" estão vagando por aí quase em "+XI_ConvertString("Colony"+npchar.city+"Dat")+"! Peguem ele imediatamente!!!");
				}
				link.l1 = RandPhraseSimple("Bem, você pode tentar. Estamos sozinhos aqui...","Heh, ninguém vai te ajudar aqui.");
				link.l1.go = "exit_fight"; 				
			}
			else
			{				
				// belamour legendary edition
				sTemp1 = "";
				if(isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation)) sTemp1 = "Vice Admiral! ";
				if(CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE) sTemp1 = "Your Excellency Governor General! ";
				
				dialog.text = LinkRandPhrase("Permita-me apresentar! Sou um oficial de patrulha de "+XI_ConvertString("Colony"+npchar.city+"Gen")+", estamos procurando por um condenado fugitivo.","Olá, eu sou o chefe desta patrulha. Estamos procurando por um escravo fugitivo de "+XI_ConvertString("Colony"+npchar.city+"Gen")+".","Saudações para você, "+GetAddress_Form(NPChar)+". Meu destacamento está patrulhando o território perto de "+XI_ConvertString("Colony"+npchar.city+"Gen")+".");
				Link.l1 = LinkRandPhrase("Muito bem. Como posso ajudar você?","Muito bem. Posso te ajudar com alguma coisa, "+GetAddress_FormToNPC(NPChar)+"?","Muito bem. Posso fazer algo por você?");
				Link.l1.go = "Node_2";
			}
		break;
		
		case "Node_2":
			dialog.text = RandPhraseSimple("Você viu algo suspeito no distrito?","Você viu alguém agindo de forma suspeita, "+GetAddress_Form(NPChar)+"?");
			Link.l1 = RandPhraseSimple("Não, nada disso.","Não, oficial, tudo parecia calmo.");
			Link.l1.go = "Node_3";		
		break;

		case "Node_3":
			Diag.TempNode = "GoodBye";
			dialog.text = RandPhraseSimple("Certo, então não vou mais te atrasar. Adeus, "+GetAddress_Form(NPChar)+".","Entendi. Adeus, então.");
			Link.l1 = "Boa sorte.";
			Link.l1.go = "exit_noFight";
		break;

		case "GoodBye":
			Diag.TempNode = "GoodBye";
			dialog.text = LinkRandPhrase("Não nos distraia do nosso dever.","Eu gostaria que você nos deixasse a sós!","Ah, é você de novo... Siga seu caminho e não nos incomode.");
			Link.l1 = "Certo.";
			Link.l1.go = "Exit";			
		break;
		
		// генератор "A reason to hurry"
		case "Reason_To_Fast_1":
				if(Pchar.Location == Pchar.location.from_sea)
				{
					dialog.text = "Hum... Nunca te vi antes. Quem é você?";
					link.l1 = "Sou eu quem você está esperando...";
					link.l1.go = "Reason_To_Fast_11";
					link.l2 = "Eu sou o capitão "+GetFullName(pchar)+". Eu gostaria de saber por que você estava com tanta pressa a ponto de quase esquecer as calças no bordel...";
					link.l2.go = "Reason_To_Fast_21";
					link.l3 = "Eu sou o capitão "+GetFullName(pchar)+". Só estou dando uma volta por aqui, sentindo a brisa salgada do mar...";
					link.l3.go = "Reason_To_Fast_31";
				}
				else
				{
					Diag.TempNode = "GoodBye";
					dialog.text = "Você finalmente veio. Achei que nunca mais fosse te ver. E quem é esse sujeito com você?";
					link.l1 = "Que tipo?";
					link.l1.go = "Reason_To_Fast_Hunter";
				} 
		break;
		
		case "Reason_To_Fast_Hunter":
			DialogExit();	
			AddDialogExitQuest("ReasonToFast_MeetHunter");
		break;
		
		case "Reason_To_Fast_11":
			dialog.text = "Você não parece muito alguém em quem eu confiaria "+GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_NOM)+".";
			if(!CheckCharacterItem(pchar,"mapQuest"))
			{
				link.l1 = "Certo, vou contar tudo o que você disse a ele.";
				link.l1.go = "Reason_To_Fast_12";
			}	
			link.l2 = "E quem é este "+GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_NOM)+"?";
			link.l2.go = "Reason_To_Fast_13";
		break;
		
		case "Reason_To_Fast_21":
			dialog.text = "A curiosidade já matou muito mais gente do que gatos...";
			link.l1 = "Ora, ora!";
			link.l1.go = "Reason_To_Fast_ExitFight";
			pchar.questTemp.ReasonToFast = "PatrolAfter";	
		break;
		
		case "Reason_To_Fast_31":
			Diag.TempNode = "Reason_To_Fast_GoodBye";
			dialog.text = "The tide is coming in. You'd better leave the cove; the water here rises to the level of the palm tree.";
			link.l1 = "Sem problema, eu nado bem.";
			link.l1.go = "Reason_To_Fast_GoodBye_0";
			pchar.questTemp.ReasonToFast = "MeetPatrolFail";
		break;
		
		case "Reason_To_Fast_12":
			jewelType = sti(pchar.questTemp.ReasonToFast.p4);
			pchar.questTemp.ReasonToFast.item = "jewelry" + jewelType;
			sItem = "jewelry" + jewelType;
			switch (jewelType)
			{
				case 1:
					sItemName = "amethysts";
				break;
				case 2:
					sItemName = "diamonds";
				break;
				case 3:
					sItemName = "rubies";
				break;
				case 4:
					sItemName = "emeralds";
				break;
			}
			pchar.questTemp.ReasonToFast.jewType = sItemName;
			dialog.text = "Certo, certo. Você tem direito a 30 "+sItemName+" com você?";
			link.l1 = GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_NOM)+" disse que não havia tempo suficiente para juntar tantas gemas. Ele mandou que eu oferecesse dinheiro em vez disso.";
			link.l1.go = "Reason_To_Fast_14";
			if (GetCharacterItem(pchar, pchar.questTemp.ReasonToFast.item) >= 30)
			{
				link.l2 = "Aqui está.";
				link.l2.go = "Reason_To_Fast_15";
			}			
		break;
		
		case "Reason_To_Fast_13":
			dialog.text = "Heh! Você vai descobrir isso no inferno!";
			link.l1 = "Quanta autoconfiança ...";
			link.l1.go = "Reason_To_Fast_ExitFight";
			pchar.questTemp.ReasonToFast = "PatrolAfter";	
		break;
		
		case "Reason_To_Fast_14":
			dialog.text = "Tudo bem, então você me deve "+sti(pchar.questTemp.ReasonToFast.p5)+" pesos, como combinamos.";
			link.l1 = "Isso não é um pouco demais?";
			link.l1.go = "Reason_To_Fast_16";
			if(makeint(pchar.money) >= sti(pchar.questTemp.ReasonToFast.p5))
			{
				link.l2 = "Aqui está.";
				link.l2.go = "Reason_To_Fast_17";
			}	
			link.l3 = "Mas eu não tenho tanto dinheiro comigo!";
			link.l3.go = "Reason_To_Fast_18";	
			AddQuestRecord("ReasonToFast", "9");
			AddQuestUserData("ReasonToFast", "sText", pchar.questTemp.ReasonToFast.jewType);
		break;
		
		case "Reason_To_Fast_15":
			TakeNItems(pchar, pchar.questTemp.ReasonToFast.item, -30); 
			dialog.text = "Está tudo conforme o combinado. Aqui está. Este mapa foi tirado do pirata enforcado, sobre quem "+GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_NOM)+" tinha perguntado.";
			link.l1 = "O acordo está feito!";
			link.l1.go = "Reason_To_Fast_15_1";
		break;
		
		case "Reason_To_Fast_15_1":
			Diag.TempNode = "Reason_To_Fast_GoodBye";
			DialogExit();
			AddQuestRecord("ReasonToFast", "10");
			AddQuestUserData("ReasonToFast", "sName", GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_NOM));
			pchar.questTemp.ReasonToFast = "PatrolSuccess_2";
			GiveItem2Character(pchar, "mapQuest"); 
			arItem = ItemsFromID("mapQuest");
			ReasonToFast_GenerateTreasureMap(arItem);	
			DeleteAttribute(pchar, "questTemp.ReasonToFast.cantSpeakOther");//можем говорить с губером 
			AddDialogExitQuest("pchar_back_to_player");	
			LAi_LocationFightDisable(&locations[FindLocation(pchar.questTemp.ReasonToFast.PatrolLocation)], false);	
		break;
		
		case "Reason_To_Fast_16":
			dialog.text = "Acertamos o valor com "+GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_ABL)+" adiantado. Não gosto nem um pouco disso. Mate h"+GetSexPhrase("im","er")+", rapazes!";
			link.l1 = "Certo, pode tentar!";
			link.l1.go = "Reason_To_Fast_ExitFight";
			pchar.questTemp.ReasonToFast = "PatrolAfter";	
		break;
		
		case "Reason_To_Fast_17":
			pchar.questTemp.ReasonToFast = "PatrolSuccess_1";
			AddMoneyToCharacter(pchar, -makeint(sti(pchar.questTemp.ReasonToFast.p5)));
			pchar.GenQuest.CannotWait = 1; // лочим интерфейс отдыха
			if(CheckAttribute(pchar,"questTemp.ReasonToFast.chain")) DeleteAttribute(pchar,"questTemp.ReasonToFast.chain");
			if(CheckAttribute(pchar,"questTemp.ReasonToFast.ShipName")) DeleteAttribute(pchar,"questTemp.ReasonToFast.ShipName");
			if(CheckAttribute(pchar,"questTemp.ReasonToFast.ShipTypeName")) DeleteAttribute(pchar,"questTemp.ReasonToFast.TypeName");
			switch (sti(pchar.questTemp.ReasonToFast.target))
			{
				case 0: // корабль с товаром
					sTemp1 = generateRandomNameToShip(sti(pchar.questTemp.ReasonToFast.GuardNation));
					iShipType = ReasonToFast_GetVictimShipType();
					iShipGoods = ReasonToFast_GetVictimShipGoods();
					dialog.text = "Excelente! Agora vamos ao que interessa. Interceptamos que "+GetStrSmallRegister(pchar.questTemp.ReasonToFast.ShipTypeName)+" '"+sTemp1+" com uma carga de "+GetGoodsNameAlt(iShipGoods)+", a tripulação já está detida, e a 'carga' ainda está a bordo. A tripulação foi contratada entre os desamparados do porto, e eles só vão chegar ao porto amanhã. Você pode lidar com eles como quiser.";
					link.l1 = "Certo. Vou entregar sua mensagem "+GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_DAT)+".";
					link.l1.go = "Reason_To_Fast_GoodBye_0";
					pchar.questTemp.ReasonToFast.chain = "A0";
					pchar.questTemp.ReasonToFast.ShipName = sTemp1;										
					DeleteAttribute(pchar, "questTemp.ReasonToFast.cantSpeakOther");//можем говорить с губером
					AddQuestRecord("ReasonToFast", "11");
					AddQuestUserData("ReasonToFast", "sShipType", pchar.questTemp.ReasonToFast.ShipTypeName);					
					AddQuestUserData("ReasonToFast", "sShipName", sTemp1);
					AddQuestUserData("ReasonToFast", "sGoodsName", GetGoodsNameAlt(iShipGoods));
					ReasonToFast_GenerateVictimShip(iShipType, iShipGoods);					
				break;

				case 1: // сокровища губернатора
					switch(rand(3))
					{
						case 0:
							sTemp1 = "The governor's daughter dowry is";
						break;
						case 1:
							sTemp1 = "Governor's gifts for the Viceroy are";
						break;
						case 2:
							sTemp1 = "The presents for governor's jubilee are";
						break;
						case 3:
							sTemp1 = "Governors 'pensionary' money is";
						break;
					}
					switch(rand(3))
					{
						case 0:
							sTemp2 = "Cheat";
						break;
						case 1:
							sTemp2 = "Mischief";
						break;
						case 2:
							sTemp2 = "Prank";
						break;
						case 3:
							sTemp2 = "Naughty";
						break;
					}
					pchar.questTemp.ReasonToFast.password = sTemp2;
					sTemp2 = generateRandomNameToShip(sti(pchar.questTemp.ReasonToFast.GuardNation));
					dialog.text = "Excelente! "+sTemp1+" guardado no seu quarto. O navio-correio deve chegar a qualquer momento, mas você ainda deve conseguir. O criado é 'nosso' homem. Senha: '"+pchar.questTemp.ReasonToFast.password+"', reply: '"+sTemp2+"'.";
					link.l1 = "Certo. Vou passar seu recado "+GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_DAT)+".";
					link.l1.go = "Reason_To_Fast_GoodBye_0";
					pchar.questTemp.ReasonToFast.chain = "A1";
					AddQuestRecord("ReasonToFast", "12");
					pchar.questTemp.ReasonToFast.ShipName = sTemp2;
					DeleteAttribute(pchar, "questTemp.ReasonToFast.cantSpeakOther");//можем говорить с губером
					
					pchar.quest.ReasonToFast_ClearLakey.win_condition.l1 = "Timer";
					pchar.quest.ReasonToFast_ClearLakey.win_condition.l1.date.day = GetAddingDataDay(0, 0, 2);
					pchar.quest.ReasonToFast_ClearLakey.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 2);
					pchar.quest.ReasonToFast_ClearLakey.win_condition.l1.date.year = GetAddingDataYear(0, 0, 2);
					pchar.quest.ReasonToFast_ClearLakey.function = "ReasonToFast_ClearLakey";
				break;				
			}
		break;
		
		case "Reason_To_Fast_18":
			if(makeint(pchar.money) >= sti(pchar.questTemp.ReasonToFast.p5))
			{
				dialog.text = "Está tentando me enganar?! Seu cachorro!";
				link.l1 = "Cala a boca, porra!";
				link.l1.go = "Reason_To_Fast_ExitFight";
				pchar.questTemp.ReasonToFast = "PatrolAfter";	
			}
			else
			{
				dialog.text = "Você gastou! O meu! Dinheiro!... Argh.";
				link.l1 = "Merda!";
				link.l1.go = "Reason_To_Fast_ExitFight";
				pchar.questTemp.ReasonToFast = "PatrolAfter";	
			}
		break;

		case "Reason_To_Fast_GoodBye_0":
			LAi_SetPlayerType(pchar);
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				sld.Dialog.CurrentNode = "Reason_To_Fast_GoodBye";
				sld.greeting = "soldier_common";
				LAi_SetWarriorType(sld);
				LAi_warrior_DialogEnable(sld, true);
				LAi_group_MoveCharacter(sld, sGroup);				
			}
			pchar.quest.RemovePatrolFromShore.win_condition.l1          = "ExitFromLocation";
			pchar.quest.RemovePatrolFromShore.win_condition.l1.location = pchar.location; 
            pchar.quest.RemovePatrolFromShore.function    				= "ReasonToFast_DeletePatrolFromShore"; 
			DialogExit();			
		break;
		
		case "Reason_To_Fast_GoodBye":
			Diag.TempNode = "Reason_To_Fast_GoodBye";
			dialog.text = "É melhor você sair da enseada, a maré já está subindo...";
			link.l1 = "Tá bom, tá bom, já tô indo.";
			link.l1.go = "Exit";
		break;
		
		case "Reason_To_Fast_ExitFight":
			pchar.questTemp.ReasonToFast.relation = GetNationRelation2MainCharacter(sti(pchar.questTemp.ReasonToFast.GuardNation));
			SetNationRelation2MainCharacter(sti(pchar.questTemp.ReasonToFast.GuardNation), RELATION_ENEMY); 
			
			pchar.GenQuest.HunterScore2Pause = 1; //НЗГ не начисляются
			pchar.GenQuest.ReputationNotChange = 1; //репутацию не менять
			
			chrDisableReloadToLocation = true;
			LAi_SetPlayerType(pchar);
			LAi_LocationFightDisable(&locations[FindLocation(pchar.questTemp.ReasonToFast.PatrolLocation)], false);	
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, sGroup);
			}
			if(pchar.questTemp.ReasonToFast == "PatrolAngry")
			{
				sld = CharacterFromID("ReasonToFast_Hunter");
				if(sld != -1) 
				{ 
					LAi_SetWarriorType(sld); 
					LAi_group_MoveCharacter(sld, sGroup);
				}
			}			
			LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(sGroup, "OpenTheDoors"); 
			LAi_group_SetCheck(sGroup, "ReasonToFast_PatrolDied");
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Reason_To_Fast_AfterHunter1":
			dialog.text = "Não combinamos que o mensageiro deveria vir sozinho?";
			link.l1 = "Faltou coordenação. O mensageiro se perdeu. Eu sou o substituto.";
			link.l1.go = "Reason_To_Fast_11";
			link.l2 = "E eu vim sozinho, mas não pelo que você está esperando.";
			link.l2.go = "Reason_To_Fast_AfterHunter2";
		break;
		
		case "Reason_To_Fast_AfterHunter2":
			dialog.text = "Então, você me encontrou afinal. Sinto muito pelo que está prestes a acontecer...";
			link.l1 = "Arrgh!";
			link.l1.go = "Reason_To_Fast_ExitFight";
			pchar.questTemp.ReasonToFast = "PatrolAfterHunter";	
		break;
		
		case "Reason_To_Fast_AfterHunter3":
			dialog.text = "Seu desgraçado! Eu quase acreditei nisso! Guardas! Peguem e"+GetSexPhrase("im","er")+"...";
			link.l1 = "Experimentem, seus bastardos!";
			link.l1.go = "Reason_To_Fast_ExitFight";
			pchar.questTemp.ReasonToFast = "PatrolAngry";	
		break;
		// генератор "A reason to hurry"
	}
}
