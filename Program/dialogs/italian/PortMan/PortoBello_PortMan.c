// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	int i,n;
	string month;
	
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Che tipo di domande?","Cosa vuoi, "+GetAddress_Form(NPChar)+"?"),"Hai già cercato di farmi una domanda "+GetAddress_Form(NPChar)+"...","Hai parlato di qualche problema per la terza volta oggi...","Guarda, se non hai nulla da dirmi riguardo alle questioni del porto, allora non disturbarmi con le tue domande.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Ho cambiato idea.","Non ho nulla di cui parlare."),"Non importa.","Certo, già la terza volta...","Mi dispiace, ma per ora non mi interessano gli affari del porto.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.Slavetrader == "FindRatPortobello_1")
            {
                link.l1 = "Buon giorno a voi. Vorrei sapere dove si trova il Capitano Francois Gontier. Ho una questione importante.";
                link.l1.go = "Portobello_ratP_1";
            }
			// belamour legengary edition на пару с Акулой -->
			if(CheckAttribute(pchar,"questTemp.SharkGoldFleet"))
			{
				if(pchar.questTemp.SharkGoldFleet == "toPBPortOffice" || pchar.questTemp.SharkGoldFleet == "KillCurier")
				{
					link.l1 = "Sono un mercante, vengo da Caracas, e il tuo collega dell'autorità portuale locale mi ha chiesto di darti un po' di corrispondenza ...";
					link.l1.go = "SharkGoldFleet";
				}
				if(pchar.questTemp.SharkGoldFleet == "MoneySpeak")
				{
					link.l1 = "Sì, sono per il pagamento.";
					link.l1.go = "SharkGoldFleet_11";
				}
			}
			//<-- на пару с Акулой
		break;

		case "Portobello_ratP_1":
			dialog.text = "Una questione importante dici? Vediamo. Beh... Francois Gontier, nella corvetta '"+pchar.questTemp.Slavetrader.ShipName+"'... Secondo le mie note, il Signor Gontier stava dirigendosi verso la Giamaica.";
			link.l1 = "Grazie! Hai aiutato molto!";
			link.l1.go = "exit";
			pchar.questTemp.Slavetrader = "FindRatJamaica";
			AddQuestRecord("Slavetrader", "21_3");
			AddQuestUserData("Slavetrader", "sShip", pchar.questTemp.Slavetrader.ShipName);
		break;
		// на пару с Акулой -->
		case "SharkGoldFleet":
			if(!bImCasual) pchar.quest.SharkGoldFleetToPB10.over = "yes"; 
			RemoveItems(PChar, "letter_1", 1);
			ChangeItemDescribe("letter_1", "itmdescr_letter_1");
			dialog.text = "Ah, bene, finalmente! Sei un mercante, dici? Di nuovo, stanno cercando di risparmiare sui corrieri e rimandare la spedizione fino all'ultimo maledetto... Sì, certo! È vero. Ed è così che dovrei equipaggiare la squadra con loro in un simile lasso di tempo?...";
			link.l1 = "Sembra irresponsabile...";
			link.l1.go = "SharkGoldFleet_01";
		break;
		
		case "SharkGoldFleet_01":
			dialog.text = "È un modo di dirlo! Beh, va bene, cosa fare. Ci vedremo in tempo... Sto parlando del mio, non ci fare caso. Ascolta, per caso stai tornando indietro?";
			link.l1 = "Beh, in realtà, stavo per vendere merci qui, e poi - sì, tornare a Caracas ...";
			link.l1.go = "SharkGoldFleet_02";
		break;
		
		case "SharkGoldFleet_02":
			dialog.text = "Benissimo! Ora scriverò loro una risposta e ti chiederò di rispedirla. Quindi... Consegnala, per favore, entro dieci giorni, altrimenti non avranno tempo per fare nulla in tempo... E dichiara il tuo nome.";
			if(pchar.questTemp.SharkGoldFleet == "KillCurier")
			{
				link.l1 = "Il mio nome è "+GetFullName(pchar)+".";
				link.l1.go = "SharkGoldFleet_03";
			}
			else
			{
				link.l1 = "Il mio nome è Andreas Garcia.";
				link.l1.go = "SharkGoldFleet_09";
			}
		break;
		
		case "SharkGoldFleet_03":
			TakeNItems(pchar, "letter_2", 1);
			ChangeItemDescribe("letter_2", "itmdescr_letter_SharkGoldFleet_2");
			dialog.text = "Aspetta un attimo... Registrato. Ecco a te. Ricorda: dieci giorni! Nel frattempo, leggerò più in dettaglio ciò che mi hai portato.";
			link.l1 = "Sì, mi ricordo. Addio!";
			link.l1.go = "SharkGoldFleet_04";
		break;

		case "SharkGoldFleet_04":
			dialog.text = "Aspetta un minuto... Non capisco... Ancora una volta, come hai detto che ti chiami?";
			link.l1 = "Io?.. Beh... Perché è così importante?";
			link.l1.go = "SharkGoldFleet_05";
		break;
		
		case "SharkGoldFleet_05":
			n = GetAddingDataDay(0,0,21);
			if(n<21) i = GetAddingDataMonth(0,1,0);
			else i = GetDataMonth();
			month = XI_ConvertString("target_month_" + i);
			pchar.questTemp.SharkGoldFleet.Date = ""+n+" "+month+"";
			SetFunctionTimerCondition("SharkGoldFleet1269fail", 0, 0, 22, false);
			SetFunctionTimerCondition("SGF_FleetTime", 0, 0, 21, false);
			if(!bImCasual) SetFunctionTimerCondition("SharkGoldFleetToCPO10", 0, 0, 10, false);
			else NewGameTip("Exploration mode: timer is disabled.");
			dialog.text = "È molto importante! Dice... Quindi... "+n+" "+month+"... No, non è questo... 12, 50, 69, 55... Ma dove si trova... Ah, eccolo! La lettera deve essere consegnata dal Capitano "+pchar.questTemp.SharkGoldFleet.CurierName+" "+pchar.questTemp.SharkGoldFleet.Curierlastname+". E hai detto che il tuo nome è... "+GetFullName(pchar)+"?";
			link.l1 = "Deve essere stato un errore...";
			link.l1.go = "SharkGoldFleet_06";
		break;
		
		case "SharkGoldFleet_06":
			DeleteAttribute(pchar,"questTemp.SharkGoldFleet.CurierName");
			DeleteAttribute(pchar,"questTemp.SharkGoldFleet.Curierlastname");
			dialog.text = "No, non ci può essere alcun errore. Ridammi la lettera che ti ho dato. Devo capire questa situazione!";
			link.l1 = "Avanti... Lo consegnerò, tutto andrà bene.";
			link.l1.go = "SharkGoldFleet_07";
		break;
		
		case "SharkGoldFleet_07":
			dialog.text = "No! Restituiscimi la lettera! Guardie!!!";
			link.l1 = "Ah vuoi fare questo nel modo difficile, eh?";
			link.l1.go = "SharkGoldFleet_08";
		break;
		
		case "SharkGoldFleet_08":
			DialogExit();
			pchar.questTemp.SharkGoldFleet = "DifficultVar";
			if (CheckCharacterItem(pchar, "HolTradeLicence"))
			{
				TakeNationLicence(HOLLAND);
				log_info("Trading license cancelled!");
			}
			for (i=1; i<=2; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("Sold"+i, "sold_" + NationShortName(SPAIN) + "_" + (rand(1) + 1), "man", "man", sti(pchar.rank), SPAIN, 0, true, "soldier"));
				SetFantomParamFromRank(sld, sti(pchar.rank), true);         
				ChangeCharacterAddressGroup(sld, pchar.location, "goto",  "goto3");
				LAi_SetWarriorType(sld); 
				LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
				LAi_group_Attack(sld, Pchar);
			}
			LAi_group_Attack(NPChar, Pchar);
			SetNationRelation2MainCharacter(SPAIN, RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
			SetFunctionExitFromLocationCondition("SharkGoldFleetExitPO", pchar.location, false);
		break; 
		
		case "SharkGoldFleet_09":
			dialog.text = "Aspetta un minuto... Ecco fatto. Allora scriverò il tuo nome in una lettera di risposta. Ecco a te. Ricorda: hai dieci giorni! Nel frattempo, leggerò con più attenzione ciò che mi hai portato.";
			link.l1 = "Sì, mi ricordo. Addio!";
			link.l1.go = "SharkGoldFleet_10";
		break;
		
		case "SharkGoldFleet_10":
			DialogExit();
			pchar.questTemp.SharkGoldFleet = "MoneySpeak";
			TakeNItems(pchar, "letter_2", 1);
			ChangeItemDescribe("letter_2", "itmdescr_letter_SharkGoldFleet_2");
			AddQuestRecord("SharkGoldFleet", "17");
			chrDisableReloadToLocation = true;
			bDisableFastReload = true;
		break;
		
		case "SharkGoldFleet_11":
			dialog.text = "Pagamento?..";
			link.l1 = "A Caracas, il tuo collega mi ha detto che avresti pagato per la consegna della lettera.";
			link.l1.go = "SharkGoldFleet_12";
		break;
		
		case "SharkGoldFleet_12":
			dialog.text = "No, beh, sono completamente pazzi lì! Ora devo pagare per loro!";
			link.l1 = "...";
			link.l1.go = "SharkGoldFleet_13";
		break;
		
		case "SharkGoldFleet_13":
			dialog.text = "E quanto ti hanno promesso?";
			link.l1 = "Cinque mila pesos.";
			link.l1.go = "SharkGoldFleet_14";
			link.l2 = "Diecimila pesos.";
			link.l2.go = "SharkGoldFleet_15";
		break;
		
		case "SharkGoldFleet_14":
			pchar.questTemp.SharkGoldFleet = 5000;
			dialog.text = "Sembra che abbiano deciso di vivere a mie spese... Non solo non vogliono spendere soldi per i corrieri, affidando tali casi a navi mercantili di passaggio, ma mi appendono anche le spese! Scriverò un reclamo contro di loro a Havana!";
			link.l1 = "Capisco la vostra indignazione, signore, ma cosa dovrei fare?";
			link.l1.go = "SharkGoldFleet_16";
		break;
		
		case "SharkGoldFleet_15":
			pchar.questTemp.SharkGoldFleet = 10000;
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			ChangeOfficersLoyality("bad", 1);
			dialog.text = "Sembra che abbiano deciso di vivere a mie spese... Non solo non vogliono spendere soldi per i corrieri, affidando tali casi a navi mercantili di passaggio, ma appioppano anche le spese su di me! Scriverò un reclamo contro di loro a L'Avana!";
			link.l1 = "Capisco la vostra indignazione, signore, ma cosa dovrei fare?";
			link.l1.go = "SharkGoldFleet_16";
		break;
		
		case "SharkGoldFleet_16":
			dialog.text = "Argh, non sei tu da biasimare per l'avidità degli ufficiali della Nuova Spagna a Caracas. Ma semplicemente non ho con me quella somma adesso. E il budget dovrebbe arrivare solo domani... Aspetta qui, per favore, vado dal prestanome ora - e torno subito.";
			link.l1 = "...";
			link.l1.go = "SharkGoldFleet_17";
		break;
		
		case "SharkGoldFleet_17":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorTurnToLocator(pchar, "reload", "reload1");
			LAi_SetStayType(npchar);
			ChangeCharacterAddressGroup(npchar, pchar.location, "goto", "goto2");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "reload", "reload1","SGF_toUsurer", -1);
		break;
		
		case "SharkGoldFleet_18":
			AddMoneyToCharacter(pchar, makeint(pchar.questTemp.SharkGoldFleet));
			n = GetAddingDataDay(0,0,21);
			if(n<21) i = GetAddingDataMonth(0,1,0);
			else i = GetDataMonth();
			month = XI_ConvertString("target_month_" + i);
			pchar.questTemp.SharkGoldFleet.Date = ""+n+" "+month+"";
			SetFunctionTimerCondition("SharkGoldFleet1269fail", 0, 0, 22, false);
			SetFunctionTimerCondition("SGF_FleetTime", 0, 0, 21, false);
			if(!bImCasual) SetFunctionTimerCondition("SharkGoldFleetToCPO10", 0, 0, 10, false);
			else NewGameTip("Exploration mode: timer is disabled.");
			AddQuestRecord("SharkGoldFleet", "18");
			AddQuestUserData("SharkGoldFleet", "date", pchar.questTemp.SharkGoldFleet.Date);
			LAi_SetHuberType(npchar);
			Lai_SetPlayerType(pchar);
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			dialog.text = "Mi dispiace per l'attesa. Ecco i tuoi "+makeint(pchar.questTemp.SharkGoldFleet)+" pezzi di otto. E in questo caso, pagheranno loro stessi per la risposta a Caracas. Dimmi che l'ho fatto.";
			link.l1 = "Bene, lo passerò. Grazie e buona fortuna!";
			link.l1.go = "exit";
			pchar.questTemp.SharkGoldFleet = "LightVar";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
