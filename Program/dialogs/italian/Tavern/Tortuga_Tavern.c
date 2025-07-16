// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("Tutti i rumors di "+GetCityName(npchar.city)+" al vostro servizio. Cosa vorreste scoprire?","Ne stavamo proprio parlando. Devi averlo dimenticato...","Questa è la terza volta oggi che parli di qualche domanda...","Ripeti sempre le stesse cose come un pappagallo...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Sai, "+NPChar.name+", forse la prossima volta.","Giusto, per qualche motivo ho dimenticato...","Sì, è davvero la terza volta...","Sì...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.Slavetrader == "FindRatTortuga") // работорговец
            {
                link.l1 = "Ascolta, dove posso trovare Francois Gontier? Doveva essere già arrivato a Tortuga.";
                link.l1.go = "Tortuga_ratT_1";
            }
			// суп из черепахи
			if (CheckAttribute(PChar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "tortuga" && !CheckAttribute(pchar, "questTemp.Tonzag.Terrapinblock"))
			{
				link.l1 = "Sto cercando Henri Thibaut. Dove posso trovarlo?";
				link.l1.go = "terrapin";
			}
			if (CheckAttribute(PChar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "tortuga1" && !CheckAttribute(pchar, "questTemp.Tonzag.Terrapinblock"))
			{
				link.l1 = "Sto cercando Henri Thibaut. Dove posso trovarlo?";
				link.l1.go = "terrapin_2";
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "tortuga")
			{
				link.l1 = "Dimmi, una galea chiamata 'Santa Margarita' è approdata di recente nella tua colonia? Forse come bottino di un corsaro?";
                link.l1.go = "guardoftruth";
			}
			// Addon 2016-1 Jason Пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Jeweller"))
			{
				link.l1 = "Guarda amico, sto cercando Gaspard Parmentier. Dove posso trovarlo?";
                link.l1.go = "mtraxx_jew";
			}
			// Rebbebion, "Путеводная звезда"
			if (CheckAttribute(pchar, "questTemp.PZ.TortugaCitizensAsk") && !CheckAttribute(npchar, "quest.PZ.Ask.block"))
			{
				link.l1 = "Potresti aiutarmi un po', amico? Sto cercando un uomo di nome Joep van der Vink. Lo conosci?";
				link.l1.go = "PZ1";
			}
        break;
        
		case "Tortuga_ratT_1":
			dialog.text = "Francois Gontier? Chi è lui? Non conosco nessun uomo con quel nome.";
			link.l1 = "È il capitano della corvetta '"+pchar.questTemp.Slavetrader.ShipName+"'.'";
			link.l1.go = "Tortuga_ratT_2";
        break;
		
		case "Tortuga_ratT_2":
			dialog.text = "Non ho la minima idea, compagno. E nessuna corvetta con quel nome ha attraccato al nostro porto, posso dirlo con certezza.";
			link.l1 = "Bene allora, hai visto degli stranieri in città ultimamente?";
			link.l1.go = "Tortuga_ratT_3";
        break;
		
		case "Tortuga_ratT_3":
			dialog.text = "Buona domanda! Questa è una città portuale, non un villaggio. Ogni giorno passano degli estranei. Però ho sentito parlare di cinque strani ragazzi, stanno sempre vicini e tengono le loro spade pronte\nLa pattuglia ha persino chiesto di loro senza alcun risultato. Ma sono sicuro che non sono arrivati qui su una corvetta, nessuna tale nave è stata vista nei dintorni, capisci?";
			link.l1 = "Mh... Va bene, capisco. Grazie, "+npchar.name+".";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "21_8");
			pchar.questTemp.Slavetrader = "wait1";//затычка
        break;
		
		// суп из черепахи
		case "terrapin":
			DelMapQuestMarkCity("SentJons");
			dialog.text = "Signor Thibaut è un uomo famoso a Tortuga. La sua dimora si trova vicino all'autorità portuale. Quando esci dalla taverna, vai dritto verso il porto. Avvicinati all'arco che conduce al porto, gira a sinistra al bivio e vai tutto dritto fino alla fine della strada dove ti imbatterai in un edificio di pietra a due piani con un tetto rosso. Quella è la dimora del Signor Thibaut.";
			link.l1 = "Grazie! Andrò a fargli visita...";
			link.l1.go = "terrapin_1";
		break;
		
		case "terrapin_1":
			DialogExit();
			pchar.questTemp.Terrapin = "house";
			sld = characterFromId("Tibo");
			ChangeCharacterAddressGroup(sld, "Tortuga_houseS2", "barmen", "stay");
			LAi_SetOwnerType(sld);
		break;
		
		case "terrapin_2":
			dialog.text = "Signor Thibaut è molto richiesto oggi, un messaggero del governatore è appena corso qui. Anche lui era interessato. È così difficile trovarlo? Ha affittato una stanza da me al secondo piano per un bel po' di tempo, nonostante abbia una intera villa in cui vivere. Non so a cosa gli serva, ma entra molto più spesso di quanto esca. E c'è solo di sera.";
			link.l1 = "Forse, lui è qui proprio adesso.";
			link.l1.go = "terrapin_3";
		break;
		
		case "terrapin_3":
			if (stf(environment.time) < 20.0 && stf(environment.time) > 8.0)
			{
				dialog.text = "No. Ha detto che non sarebbe tornato fino alle otto di sera oggi. Puoi provare a cercarlo a casa nella sua villa, ma non penso che lo troverai lì. L'ho visto navigare su una lancia di pattuglia in mare.";
				link.l1 = "Grazie! Passerò a vederlo più tardi.";
				link.l1.go = "terrapin_4";
			}
			else
			{
				dialog.text = "Sì. Se vuoi, puoi salire.";
				link.l1 = "Grazie! Andrò a fargli visita...";
				link.l1.go = "terrapin_4";
			}
		break;
		
		case "terrapin_4":
			DialogExit();
			pchar.questTemp.Terrapin = "tavern";
			sld = characterFromId("Tibo");
			sld.dialog.currentnode = "tibo_9";
			LAi_SetLoginTime(sld, 20.0, 8.0);
			ChangeCharacterAddressGroup(sld, "Tortuga_tavern_upstairs", "goto", "goto1");
			LocatorReloadEnterDisable("Tortuga_tavern", "reload2_back", false); // откроем комнату
			LAi_LocationFightDisable(&Locations[FindLocation("Tortuga_tavern_upstairs")], true);//запретить драться
			LAi_SetStayType(sld);
			// Addon 2016-1 Jason Пиратская линейка
			if (GetCharacterIndex("Mary") != -1)
			{
				sld = characterFromId("Mary");
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && !IsOfficer(sld))
				{
					ChangeCharacterAddressGroup(sld, "none", "", "");
				}
			}
			if (GetCharacterIndex("Helena") != -1)
			{
				sld = characterFromId("Helena");
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && !IsOfficer(sld))
				{
					ChangeCharacterAddressGroup(sld, "none", "", "");
				}
			}
		break;
		
		case "guardoftruth":
			dialog.text = "Non ho idea del nome della nave, era 'Santa Margarita' o 'Castilian Whore' ma hanno portato qui un galeone spagnolo catturato. Catturato da una sloop, niente di meno! Questo sì che è un vero cazzo di navigazione! Gaius Marchais, il suo capitano, si vanta da due giorni in una taverna - il suo primo viaggio e un tale premio!\nSì, molto eroico, salire su un galeone pieno di topi di chiesa senza soldati a proteggerli. Sembra che quei bastardi papisti abbiano dimenticato quello che dicono di quelli che si aiutano da soli...";
			link.l1 = "Sì, Dio aiuta chi si aiuta, questa è sicuramente una frase ugonotta. Come posso dare un'occhiata a quel fortunato capitano? È qui, a Tortuga?";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "Ah, chi diavolo lo sa. Non lo vedo da tempo nella mia taverna. Appena si è ripreso ha comprato una nuova nave lucida con i soldi del premio e ha corso sul suo ponte come un pazzo. Non ho idea di dove sia Marchais ora. Forse è su Tortuga o forse in mare.";
			link.l1 = "Bene. Beh, grazie per la storia, amico!";
			link.l1.go = "guardoftruth_2";			
		break;
		
		case "guardoftruth_2":
			dialog.text = "In qualsiasi momento, Monsieur. Sono sempre felice di aiutare il nostro amato Capitano "+pchar.name+", salvatore di St. Pierre! Passa più tardi!";
			link.l1 = "...";
			link.l1.go = "exit";	
			AddQuestRecord("Guardoftruth", "8");
			pchar.questTemp.Guardoftruth = "tortuga1";
		break;
		
		// Addon 2016-1 Jason Пиратская линейка
		case "mtraxx_jew":
            dialog.text = "Sembra che Gaspard stia diventando sempre più popolare tra i vostri. La sua casa è vicino al muro. Gira a sinistra dalla taverna e vai verso il porto, ma non ci andare, gira di nuovo a sinistra, vai dritto e poi gira a destra. Una casa a due piani.";
			link.l1 = "Grazie!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_WolfreekJewellerHouse");
		break;
		
		case "PZ1":
			dialog.text = "Mai sentito parlare di lui.";
			link.l1 = "Forse si fa chiamare con un altro nome. Forse l'hai sentito come il capitano della brigata 'Banten'?";
			link.l1.go = "PZ2";
		break;
		
		case "PZ2":
			dialog.text = "Mai sentito parlare di quella brigata neanche.";
			link.l1 = "Ho sentito dire che era qui di recente. Forse un po' d'argento rinfrescherà la tua memoria?";
			link.l1.go = "PZ3";
		break;
		
		case "PZ3":
			npchar.quest.PZ.Ask.block = true;
			
			dialog.text = "Bene, chiedi dove hai sentito ciò. Non mi dispiace prendere il tuo argento, però.";
			link.l1 = "Nessun argento questa volta, allora. Arrivederci.";
			link.l1.go = "Exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
