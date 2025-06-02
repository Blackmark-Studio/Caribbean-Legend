// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Quali domande hai?","Come posso aiutarti?"),"Hai provato a farmi una domanda un po' di tempo fa...","Non ho mai incontrato persone con tanta curiosità nel mio cantiere navale o in qualsiasi altro luogo in questa città.","Cosa c'è con tutte queste domande? Il mio lavoro è costruire navi. Occupiamoci di questo.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Ho cambiato idea...","Non ho nulla di cui parlare al momento."),"Uhm, dove se n'è andata la mia memoria...","Mh, beh...","Avanti...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// Addon 2016-1 Jason пиратскаЯ линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx"))
            {
				if (pchar.questTemp.Mtraxx == "silk_2" || pchar.questTemp.Mtraxx == "silk_3")
				{
					link.l1 = "Ho sentito dire che questo cantiere navale si occupa di migliorare la velocità di navigazione della nave. Richiede una tela di seta molto rara. Vorresti... parlarne?";
					link.l1.go = "mtraxx";
				}
			}
			if (CheckAttribute(npchar, "quest.upgradeship")) {
				link.l2 = "Sono da Miss MacArthur, riguardo a...";
				link.l2.go = "helen_upgradeship";
			}
			
			if (CheckAttribute(npchar, "quest.upgradeship.money") && HelenCanUpgrade()) {
				link.l2 = "Inizia la revisione della nave!";
				link.l2.go = "helen_upgradeship_money";
			}
		break;
		
		// Addon 2016-1 Jason пиратскаЯ линейка
		case "mtraxx":
            dialog.text = "Potresti essere più chiaro, giovane uomo? Che cosa ti ha portato esattamente qui? Se vuoi migliorare la tua nave - passiamo subito agli affari.";
			link.l1 = "Non del tutto. Il tipo di servizi che fornisci richiede beni che non sono liberamente disponibili nel negozio. Vorrei offrirti lo stesso tipo di quei materiali di cui potresti aver bisogno.";
			link.l1.go = "mtraxx_1";
		break;
		
		case "mtraxx_1":
            dialog.text = "Beh-beh... Hmm... Sei consapevole che solo le autorità di questa colonia sono autorizzate a gestire tali beni strategici? Sei libero di fornire la tua seta per me da lavorare per migliorare la tua nave, tuttavia, venderla è severamente proibito. Come lo è acquistarla da me - tali attività saranno multate piuttosto pesantemente.";
			link.l1 = "Ebbene, questo non è un negozio, né un ufficio doganale...";
			link.l1.go = "mtraxx_2";
		break;
		
		case "mtraxx_2":
            dialog.text = "Acquisto tutto il tessuto di seta per le vele direttamente dai miei clienti, o compro quantità limitate con un permesso speciale del governatore. Se non hai altre domande, per favore, lasciami tornare al mio lavoro.";
			link.l1 = "Mmm... Va bene. Buona giornata, maestro.";
			link.l1.go = "mtraxx_3";
		break;
		
		case "mtraxx_3":
            DialogExit();
			AddQuestRecord("Roger_2", "5");
			pchar.questTemp.Mtraxx = "silk_4";
		break;
		
		case "helen_upgradeship":
			dialog.text = "Oh, I know! Lucky you, Captain. Is it about a complete overhaul of the ship? We'll take care of everything; our shipyard is on par with those in Plymouth!";
			link.l1 = "Presumo che questo non sarà un servizio gratuito?";
			link.l1.go = "helen_upgradeship_1";
		break;
		
		case "helen_upgradeship_1":
			dialog.text = "Certo, Capitano, tali servizi non possono essere gratuiti, nemmeno per Cromwell! Tuttavia, mantengo la mia parola e prenderò solo soldi - non dovrai contrabbandare merci illegali.";
			link.l1 = "Comprensibile. Quanto?";
			link.l1.go = "helen_upgradeship_2";
		break;
		
		case "helen_upgradeship_2":
			dialog.text = "Dipende dalla grandezza della tua nave ammiraglia, Capitano. Una nave di primo rango ti costerà cinquemila dobloni, e una di quinto rango - solo mille.";
			link.l1 = "Bene, verrò da te una volta presa una decisione.";
			link.l1.go = "exit";
			
			npchar.quest.upgradeship.money = true;
		break;
		
		case "helen_upgradeship_money":
			dialog.text = "Eccellente, ora ho tutto ciò di cui ho bisogno. Allora comincerò a lavorare.";
			link.l1 = "Sto aspettando.";
			link.l1.go = "helen_upgradeship_money_1";
			
			iTemp = GetCharacterShipType(pchar);
			sld = GetRealShip(iTemp);
			iTemp = (7 - sti(sld.class)) * 1000;
			RemoveDublonsFromPCharTotal(iTemp);
		break;
		
		case "helen_upgradeship_money_1":
			AddTimeToCurrent(6, 30);
			dialog.text = "... Immagino che sia tutto... La qualità è garantita.";
			link.l1 = "Grazie! Lo controllerò.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenUpgradeShip2");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

bool HelenCanUpgrade() {
	int shipIndex = GetCharacterShipType(pchar);
	if (shipIndex == SHIP_NOTUSED) {
		return false;
	}
	
	sld = GetRealShip(shipIndex);
	if (sti(sld.class) == 7) {
		return false;
	}
	
	int cost = (7 - sti(sld.class)) * 1000;
	return (PCharDublonsTotal() >= cost);
}
