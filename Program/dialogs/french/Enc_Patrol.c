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
	int iTemp = int(npchar.EncQty);
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
			if (GetNationRelation2MainCharacter(int(NPChar.nation)) == RELATION_ENEMY && int(NPChar.nation) != PIRATE)
			{
    			if (pchar.nation == npchar.nation)
				{
					dialog.text = RandPhraseSimple("Oh regarde, il semble que ce coquin ait donné l'alarme dans "+XI_ConvertString("Colony"+npchar.city+"Cela")+"! Seize h"+GetSexPhrase("suis","hein")+"!!","Heh, regarde ça ! Plusieurs "+NationNamePeople(int(pchar.nation))+" réussir à être ennemis avec "+NationNameAblative(int(npchar.nation))+"! Attrapez le vaurien!!!");
				}
				else
				{
					dialog.text = RandPhraseSimple("Agent ennemi proche "+XI_ConvertString("Colony"+npchar.city+"Gen")+"! Seize h"+GetSexPhrase("suis","hein")+"!!","Eh bien, regarde, "+NationNamePeople(int(pchar.nation))+" se promènent presque dans "+XI_ConvertString("Colony"+npchar.city+"Cela")+"! Attrapez-le immédiatement!!!");
				}
				link.l1 = RandPhraseSimple("Eh bien, vous pouvez essayer. Nous sommes seuls ici...","Heh, personne ne vous prêtera main forte ici.");
				link.l1.go = "exit_fight"; 				
			}
			else
			{				
				// belamour legendary edition
				sTemp1 = "";
				if(isMainCharacterPatented() && int(Items[int(pchar.EquipedPatentId)].TitulCur) > 4 && npchar.nation == int(Items[int(pchar.EquipedPatentId)].Nation)) sTemp1 = "Vice Admiral! ";
				if(CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE) sTemp1 = "Your Excellency Governor General! ";
				
				dialog.text = LinkRandPhrase("Permettez-moi de me présenter! Je suis un officier de patrouille de "+XI_ConvertString("Colony"+npchar.city+"Gen")+", nous recherchons un prisonnier évadé.","Bonjour, je suis le chef de cette patrouille. Nous recherchons un esclave échappé de "+XI_ConvertString("Colony"+npchar.city+"Gen")+".","Salutations à vous, "+GetAddress_Form(NPChar)+". Mon détachement patrouille le territoire près de "+XI_ConvertString("Colony"+npchar.city+"Gen")+".");
				Link.l1 = LinkRandPhrase("Très bien. Comment puis-je vous aider?","Très bien. Puis-je vous aider avec quelque chose, "+GetAddress_FormToNPC(NPChar)+"?","Très bien. Y a-t-il quelque chose que je peux faire pour vous?");
				Link.l1.go = "Node_2";
			}
		break;
		
		case "Node_2":
			dialog.text = RandPhraseSimple("Avez-vous vu quelque chose de suspect dans le quartier?","Avez-vous rencontré quelqu'un qui semble suspect, "+GetAddress_Form(NPChar)+"?");
			Link.l1 = RandPhraseSimple("Non, rien de tel.","Non, officier, tout semblait calme.");
			Link.l1.go = "Node_3";		
		break;

		case "Node_3":
			Diag.TempNode = "GoodBye";
			dialog.text = RandPhraseSimple("D'accord, je ne vais plus vous retenir. Au revoir, "+GetAddress_Form(NPChar)+".","Je vois. Au revoir, alors.");
			Link.l1 = "Bonne chance.";
			Link.l1.go = "exit_noFight";
		break;

		case "GoodBye":
			Diag.TempNode = "GoodBye";
			dialog.text = LinkRandPhrase("Ne nous détournez pas de notre devoir.","Je voudrais que vous nous laissiez tranquilles !","Oh, c'est toi encore... Va ton propre chemin et ne nous dérange pas.");
			Link.l1 = "D'accord.";
			Link.l1.go = "Exit";			
		break;
		
		// генератор "A reason to hurry"
		case "Reason_To_Fast_1":
				if(Pchar.Location == Pchar.location.from_sea)
				{
					dialog.text = "Hmm... Je ne vous ai jamais vu auparavant. Qui êtes-vous?";
					link.l1 = "Je suis celui que tu attends...";
					link.l1.go = "Reason_To_Fast_11";
					link.l2 = "Je suis capitaine "+GetFullName(pchar)+". Je voudrais savoir pourquoi tu es si pressé que tu as presque oublié ton pantalon dans le bordel...";
					link.l2.go = "Reason_To_Fast_21";
					link.l3 = "Je suis capitaine "+GetFullName(pchar)+". Je me promène juste ici, respirant la brise marine salée...";
					link.l3.go = "Reason_To_Fast_31";
				}
				else
				{
					Diag.TempNode = "GoodBye";
					dialog.text = "Vous êtes enfin arrivé. Je pensais que je ne vous reverrais jamais. Et qui est ce type avec vous?";
					link.l1 = "Quel type?";
					link.l1.go = "Reason_To_Fast_Hunter";
				} 
		break;
		
		case "Reason_To_Fast_Hunter":
			DialogExit();	
			AddDialogExitQuest("ReasonToFast_MeetHunter");
		break;
		
		case "Reason_To_Fast_11":
			dialog.text = "Vous ne ressemblez guère à quelqu'un en qui j'aurais confiance "+GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_NOM)+".";
			if(!CheckCharacterItem(pchar,"mapQuest"))
			{
				link.l1 = "D'accord, je lui dirai tout ce que vous avez dit.";
				link.l1.go = "Reason_To_Fast_12";
			}	
			link.l2 = "Et qui est-ce "+GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_NOM)+"?";
			link.l2.go = "Reason_To_Fast_13";
		break;
		
		case "Reason_To_Fast_21":
			dialog.text = "La curiosité a tué beaucoup plus de gens que de chats...";
			link.l1 = "Eh bien, eh bien !";
			link.l1.go = "Reason_To_Fast_ExitFight";
			pchar.questTemp.ReasonToFast = "PatrolAfter";	
		break;
		
		case "Reason_To_Fast_31":
			Diag.TempNode = "Reason_To_Fast_GoodBye";
			dialog.text = "La marée arrive. Vous feriez mieux de quitter la crique, l'eau ici monte au niveau du palmier.";
			link.l1 = "Aucun problème, je suis un bon nageur.";
			link.l1.go = "Reason_To_Fast_GoodBye_0";
			pchar.questTemp.ReasonToFast = "MeetPatrolFail";
		break;
		
		case "Reason_To_Fast_12":
			jewelType = int(pchar.questTemp.ReasonToFast.p4);
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
			dialog.text = "D'accord, d'accord. On a promis 30 "+sItemName+" avec toi?";
			link.l1 = GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_NOM)+" a dit qu'il n'y avait pas assez de temps pour collecter autant de gemmes. Il m'a ordonné d'offrir de l'argent à la place.";
			link.l1.go = "Reason_To_Fast_14";
			if (GetCharacterItem(pchar, pchar.questTemp.ReasonToFast.item) >= 30)
			{
				link.l2 = "Voici pour vous.";
				link.l2.go = "Reason_To_Fast_15";
			}			
		break;
		
		case "Reason_To_Fast_13":
			dialog.text = "Heh! Tu le sauras en enfer!";
			link.l1 = "Quelle assurance ...";
			link.l1.go = "Reason_To_Fast_ExitFight";
			pchar.questTemp.ReasonToFast = "PatrolAfter";	
		break;
		
		case "Reason_To_Fast_14":
			dialog.text = "D'accord, alors tu me dois "+int(pchar.questTemp.ReasonToFast.p5)+" pesos, comme nous l'avions convenu.";
			link.l1 = "Cela ne fait-il pas un peu trop?";
			link.l1.go = "Reason_To_Fast_16";
			if(int(pchar.money) >= int(pchar.questTemp.ReasonToFast.p5))
			{
				link.l2 = "Voici pour toi.";
				link.l2.go = "Reason_To_Fast_17";
			}	
			link.l3 = "Mais je n'ai pas autant d'argent sur moi !";
			link.l3.go = "Reason_To_Fast_18";	
			AddQuestRecord("ReasonToFast", "9");
			AddQuestUserData("ReasonToFast", "sText", pchar.questTemp.ReasonToFast.jewType);
		break;
		
		case "Reason_To_Fast_15":
			TakeNItems(pchar, pchar.questTemp.ReasonToFast.item, -30); 
			dialog.text = "Tout est conforme à l'accord. Voici. Cette carte a été prise du pirate pendu, à propos de qui "+GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_NOM)+" avait demandé.";
			link.l1 = "L'affaire est conclue!";
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
			dialog.text = "Nous avons réglé la somme avec "+GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_ABL)+" à l'avance. Je n'aime pas ça du tout. Tue h"+GetSexPhrase("je suis","hein")+", les gars !";
			link.l1 = "D'accord, tu peux essayer!";
			link.l1.go = "Reason_To_Fast_ExitFight";
			pchar.questTemp.ReasonToFast = "PatrolAfter";	
		break;
		
		case "Reason_To_Fast_17":
			pchar.questTemp.ReasonToFast = "PatrolSuccess_1";
			AddMoneyToCharacter(pchar, -int(int(pchar.questTemp.ReasonToFast.p5)));
			pchar.GenQuest.CannotWait = 1; // лочим интерфейс отдыха
			if(CheckAttribute(pchar,"questTemp.ReasonToFast.chain")) DeleteAttribute(pchar,"questTemp.ReasonToFast.chain");
			if(CheckAttribute(pchar,"questTemp.ReasonToFast.ShipName")) DeleteAttribute(pchar,"questTemp.ReasonToFast.ShipName");
			if(CheckAttribute(pchar,"questTemp.ReasonToFast.ShipTypeName")) DeleteAttribute(pchar,"questTemp.ReasonToFast.TypeName");
			switch (int(pchar.questTemp.ReasonToFast.target))
			{
				case 0: // корабль с товаром
					sTemp1 = generateRandomNameToShip(int(pchar.questTemp.ReasonToFast.GuardNation));
					iShipType = ReasonToFast_GetVictimShipType();
					iShipGoods = ReasonToFast_GetVictimShipGoods();
					dialog.text = "Excellent ! Maintenant, passons aux affaires. Nous avons intercepté cela "+GetStrSmallRegister(pchar.questTemp.ReasonToFast.ShipTypeName)+" '"+sTemp1+"' avec un chargement de "+GetGoodsNameAlt(iShipGoods)+", l'équipage est déjà détenu, et la 'cargaison' est toujours à bord. L'équipage a été recruté parmi les démunis dans le port, et ils n'entreront pas dans le port avant demain. Vous pouvez faire avec eux ce que vous voulez.";
					link.l1 = "D'accord. Je transmettrai vos paroles "+GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_DAT)+".";
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
					sTemp2 = generateRandomNameToShip(int(pchar.questTemp.ReasonToFast.GuardNation));
					dialog.text = "Excellent ! "+sTemp1+" gardé dans son boudoir. Le navire de courrier arrivera n'importe quel jour maintenant, mais vous devriez toujours gérer. Le laquais est 'notre' homme. Mot de passe: '"+pchar.questTemp.ReasonToFast.password+"', reponse: '"+sTemp2+"'.'";
					link.l1 = "D'accord. Je passerai votre parole "+GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_DAT)+".";
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
			if(int(pchar.money) >= int(pchar.questTemp.ReasonToFast.p5))
			{
				dialog.text = "Essayes-tu de me tromper?! Espèce de chien!";
				link.l1 = "Ferme ta putain de gueule!";
				link.l1.go = "Reason_To_Fast_ExitFight";
				pchar.questTemp.ReasonToFast = "PatrolAfter";	
			}
			else
			{
				dialog.text = "Tu as bu! Mon! Argent!... Argh.";
				link.l1 = "Merde!";
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
			dialog.text = "Tu ferais mieux de quitter la crique, la marée monte déjà...";
			link.l1 = "Oui, oui, je pars.";
			link.l1.go = "Exit";
		break;
		
		case "Reason_To_Fast_ExitFight":
			pchar.questTemp.ReasonToFast.relation = GetNationRelation2MainCharacter(int(pchar.questTemp.ReasonToFast.GuardNation));
			SetNationRelation2MainCharacter(int(pchar.questTemp.ReasonToFast.GuardNation), RELATION_ENEMY);
			
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
			dialog.text = "N'avons-nous pas convenu que le messager doit être seul?";
			link.l1 = "Manque de coordination. Le messager s'est perdu. Je suis le remplaçant.";
			link.l1.go = "Reason_To_Fast_11";
			link.l2 = "Et je suis venu seul, mais pas pour ce que vous attendez.";
			link.l2.go = "Reason_To_Fast_AfterHunter2";
		break;
		
		case "Reason_To_Fast_AfterHunter2":
			dialog.text = "Alors, tu m'as traqué après tout, je suis désolé pour ce qui va arriver...";
			link.l1 = "Arrgh!";
			link.l1.go = "Reason_To_Fast_ExitFight";
			pchar.questTemp.ReasonToFast = "PatrolAfterHunter";	
		break;
		
		case "Reason_To_Fast_AfterHunter3":
			dialog.text = "Espèce de salaud ! J'ai presque cru à ça ! Gardes ! Arrêtez-le"+GetSexPhrase("suis","hein")+"...";
			link.l1 = "Essayez-le, salauds !";
			link.l1.go = "Reason_To_Fast_ExitFight";
			pchar.questTemp.ReasonToFast = "PatrolAngry";	
		break;
		// генератор "A reason to hurry"
	}
}
