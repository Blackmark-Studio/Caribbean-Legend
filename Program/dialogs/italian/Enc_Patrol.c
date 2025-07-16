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
					dialog.text = RandPhraseSimple("Oh guarda, sembra, questa canaglia ha dato l'allarme in "+XI_ConvertString("Colony"+npchar.city+"Dat")+"! Prendi h"+GetSexPhrase("sono","eh")+"!!","Ehi, guarda questo! Diversi "+NationNamePeople(sti(pchar.nation))+" riesci a essere nemici con "+NationNameAblative(sti(npchar.nation))+"! Afferra quel mascalzone!!!");
				}
				else
				{
					dialog.text = RandPhraseSimple("Agente nemico vicino "+XI_ConvertString("Colony"+npchar.city+"Gen")+"! Prendi h"+GetSexPhrase("sono","er")+"!!","Ehi, guarda, "+NationNamePeople(sti(pchar.nation))+" stanno girando quasi in "+XI_ConvertString("Colony"+npchar.city+"Dat")+"! Afferratelo subito!!!");
				}
				link.l1 = RandPhraseSimple("Bene, puoi provare. Siamo soli qui...","Eh, qui nessuno ti darà una mano.");
				link.l1.go = "exit_fight"; 				
			}
			else
			{				
				// belamour legendary edition
				sTemp1 = "";
				if(isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation)) sTemp1 = "Vice Admiral! ";
				if(CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE) sTemp1 = "Your Excellency Governor General! ";
				
				dialog.text = LinkRandPhrase("Permettimi di presentarmi! Sono un ufficiale di pattuglia da "+XI_ConvertString("Colony"+npchar.city+"Gen")+", stiamo cercando un evaso.","Ciao, sono il capo di questa pattuglia. Stiamo cercando uno schiavo fuggito da "+XI_ConvertString("Colony"+npchar.city+"Gen")+".","Saluti a te, "+GetAddress_Form(NPChar)+". Il mio distaccamento sta pattugliando il territorio vicino "+XI_ConvertString("Colony"+npchar.city+"Gen")+".");
				Link.l1 = LinkRandPhrase("Molto bene. Come posso aiutarti?","Molto bene. Posso aiutarti in qualche modo, "+GetAddress_FormToNPC(NPChar)+"?","Molto bene. C'è qualcosa che posso fare per te?");
				Link.l1.go = "Node_2";
			}
		break;
		
		case "Node_2":
			dialog.text = RandPhraseSimple("Hai notato qualcosa di sospetto nel quartiere?","Hai incontrato qualcuno che sembrava sospetto, "+GetAddress_Form(NPChar)+"?");
			Link.l1 = RandPhraseSimple("No, niente di simile.","No, ufficiale, tutto sembrava calmo.");
			Link.l1.go = "Node_3";		
		break;

		case "Node_3":
			Diag.TempNode = "GoodBye";
			dialog.text = RandPhraseSimple("Bene, non ti tratterrò più a lungo. Addio, "+GetAddress_Form(NPChar)+".","Capisco. Addio, allora.");
			Link.l1 = "Buona fortuna.";
			Link.l1.go = "exit_noFight";
		break;

		case "GoodBye":
			Diag.TempNode = "GoodBye";
			dialog.text = LinkRandPhrase("Non distrarci dal nostro dovere.","Vorrei che ci lasciaste in pace!","Oh, sei tu di nuovo ... Vai per la tua strada e non disturbare noi.");
			Link.l1 = "Bene.";
			Link.l1.go = "Exit";			
		break;
		
		// генератор "A reason to hurry"
		case "Reason_To_Fast_1":
				if(Pchar.Location == Pchar.location.from_sea)
				{
					dialog.text = "Mmm... Non ti ho mai visto prima. Chi sei?";
					link.l1 = "Sono quello che stai aspettando...";
					link.l1.go = "Reason_To_Fast_11";
					link.l2 = "Sono il capitano "+GetFullName(pchar)+". Vorrei sapere perché avresti tanta fretta da quasi dimenticare i tuoi pantaloni nel bordello...";
					link.l2.go = "Reason_To_Fast_21";
					link.l3 = "Sono il capitano "+GetFullName(pchar)+". Sto solo facendo una passeggiata qui, respirando la salmastra brezza marina...";
					link.l3.go = "Reason_To_Fast_31";
				}
				else
				{
					Diag.TempNode = "GoodBye";
					dialog.text = "Sei finalmente arrivato. Pensavo non ti avrei mai più visto. E chi è quel tipo con te?";
					link.l1 = "Che tipo?";
					link.l1.go = "Reason_To_Fast_Hunter";
				} 
		break;
		
		case "Reason_To_Fast_Hunter":
			DialogExit();	
			AddDialogExitQuest("ReasonToFast_MeetHunter");
		break;
		
		case "Reason_To_Fast_11":
			dialog.text = "Non sembri proprio una persona di cui mi fiderei "+GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_NOM)+".";
			if(!CheckCharacterItem(pchar,"mapQuest"))
			{
				link.l1 = "Bene, gli dirò tutto quello che hai detto.";
				link.l1.go = "Reason_To_Fast_12";
			}	
			link.l2 = "E chi è questo "+GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_NOM)+"?";
			link.l2.go = "Reason_To_Fast_13";
		break;
		
		case "Reason_To_Fast_21":
			dialog.text = "La curiosità ha ucciso molte più persone che gatti...";
			link.l1 = "Bene-bene!";
			link.l1.go = "Reason_To_Fast_ExitFight";
			pchar.questTemp.ReasonToFast = "PatrolAfter";	
		break;
		
		case "Reason_To_Fast_31":
			Diag.TempNode = "Reason_To_Fast_GoodBye";
			dialog.text = "La marea sta arrivando. Sarebbe meglio che lasciassi la baia, l'acqua qui sale al livello della palma.";
			link.l1 = "Nessun problema, sono un buon nuotatore.";
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
			dialog.text = "Bene, bene. Sono promessi 30 "+sItemName+" con te?";
			link.l1 = GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_NOM)+" ha detto che non c'era abbastanza tempo per raccogliere così tante gemme. Mi ha ordinato di offrire denaro al loro posto.";
			link.l1.go = "Reason_To_Fast_14";
			if (GetCharacterItem(pchar, pchar.questTemp.ReasonToFast.item) >= 30)
			{
				link.l2 = "Eccoti.";
				link.l2.go = "Reason_To_Fast_15";
			}			
		break;
		
		case "Reason_To_Fast_13":
			dialog.text = "Eh! Lo saprai all'inferno!";
			link.l1 = "Che sicurezza in se stessi ...";
			link.l1.go = "Reason_To_Fast_ExitFight";
			pchar.questTemp.ReasonToFast = "PatrolAfter";	
		break;
		
		case "Reason_To_Fast_14":
			dialog.text = "Bene, allora mi devi "+sti(pchar.questTemp.ReasonToFast.p5)+" pesos, come avevamo concordato.";
			link.l1 = "Non è un po' troppo?";
			link.l1.go = "Reason_To_Fast_16";
			if(makeint(pchar.money) >= sti(pchar.questTemp.ReasonToFast.p5))
			{
				link.l2 = "Eccoti.";
				link.l2.go = "Reason_To_Fast_17";
			}	
			link.l3 = "Ma non ho così tanti soldi con me!";
			link.l3.go = "Reason_To_Fast_18";	
			AddQuestRecord("ReasonToFast", "9");
			AddQuestUserData("ReasonToFast", "sText", pchar.questTemp.ReasonToFast.jewType);
		break;
		
		case "Reason_To_Fast_15":
			TakeNItems(pchar, pchar.questTemp.ReasonToFast.item, -30); 
			dialog.text = "Tutto è in conformità con l'accordo. Ecco a te. Questa mappa è stata presa dal pirata impiccato, di cui "+GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_NOM)+" aveva chiesto.";
			link.l1 = "L'affare è fatto!";
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
			dialog.text = "Abbiamo saldato il conto con "+GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_ABL)+" in anticipo. Non mi piace per niente. Uccidi h"+GetSexPhrase("sono","er")+", ragazzi!";
			link.l1 = "Bene, puoi provare!";
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
					dialog.text = "Eccellente! Ora passiamo ai fatti. Abbiamo intercettato quello "+GetStrSmallRegister(pchar.questTemp.ReasonToFast.ShipTypeName)+" '"+sTemp1+"' con un carico di "+GetGoodsNameAlt(iShipGoods)+", l'equipaggio è già detenuto e il 'carico' è ancora a bordo. L'equipaggio è stato assunto tra i disperati del porto e non arriveranno in porto fino a domani. Puoi gestirli come vuoi.";
					link.l1 = "Bene. Riporterò le tue parole "+GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_DAT)+".";
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
					dialog.text = "Eccellente! "+sTemp1+" conservato nel suo boudoir. La nave corriere arriverà da un giorno all'altro, ma dovresti ancora farcela. Il lacchè è 'nostro' uomo. Password: '"+pchar.questTemp.ReasonToFast.password+"', risposta: '"+sTemp2+"'.'";
					link.l1 = "Bene. Passerò il tuo messaggio "+GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_DAT)+".";
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
				dialog.text = "Stai cercando di ingannarmi?! Sei un cane!";
				link.l1 = "Chiudi quella cazzo di bocca!";
				link.l1.go = "Reason_To_Fast_ExitFight";
				pchar.questTemp.ReasonToFast = "PatrolAfter";	
			}
			else
			{
				dialog.text = "Hai bevuto via! I! Miei! Soldi!... Argh.";
				link.l1 = "Cazzo!";
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
			dialog.text = "È meglio che lasci la baia, la marea sta già arrivando...";
			link.l1 = "Sì, sì, me ne sto andando.";
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
			dialog.text = "Non abbiamo concordato che il messaggero deve essere solo?";
			link.l1 = "Mancanza di coordinazione. Il messaggero ha perso la sua strada. Io sono il sostituto.";
			link.l1.go = "Reason_To_Fast_11";
			link.l2 = "E sono venuto da solo, ma non per quello che stavi aspettando.";
			link.l2.go = "Reason_To_Fast_AfterHunter2";
		break;
		
		case "Reason_To_Fast_AfterHunter2":
			dialog.text = "Allora, mi hai rintracciato dopo tutto, mi dispiace per quello che accadrà...";
			link.l1 = "Arrgh!";
			link.l1.go = "Reason_To_Fast_ExitFight";
			pchar.questTemp.ReasonToFast = "PatrolAfterHunter";	
		break;
		
		case "Reason_To_Fast_AfterHunter3":
			dialog.text = "Pezzo di merda! Ci ho quasi creduto! Guardie! Prendetelo"+GetSexPhrase("im","eh")+"...";
			link.l1 = "Provateci, bastardi!";
			link.l1.go = "Reason_To_Fast_ExitFight";
			pchar.questTemp.ReasonToFast = "PatrolAngry";	
		break;
		// генератор "A reason to hurry"
	}
}
