// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    ref sld;
    int i, tempQty, chComp, iShip, iBaseType;
    string tempStr;
    switch (Dialog.CurrentNode)
	{
		case "quests":
			//Португалец
			if (CheckAttribute(pchar, "questTemp.Portugal.Villemstad") && pchar.location == "villemstad_townhall")
			{
				dialog.text = RandPhraseSimple("Che tipo di domande?","Cosa desideri?");
				link.l1 = "So che la Compagnia Olandese delle Indie Occidentali ha messo una buona taglia sulla testa del famoso pirata - Bartolomeo il Portoghese. Sono riuscito a catturarlo. Attualmente si trova nella stiva della mia nave e sono pronto a consegnarlo alle autorità.";
				link.l1.go = "Portugal";
				break;
			}
            dialog.text = RandPhraseSimple("Che tipo di domande?","Di cosa hai bisogno?");
			link.l1 = RandPhraseSimple("Nulla di importante, Signore.","Non ho nulla da dire, mi scuso.");
		    link.l1.go = "exit";
		break;
		
		case "work_1":  // работа на благо короны - линейка нации
			if (CheckAttribute(npchar, "notQuestLine"))
			{
                dialog.text = "Sfortunatamente non posso considerarti per un lavoro. Non sei qualcuno con cui voglio lavorare al momento. Addio.";
                link.l1 = "Non puoi essere serio .. ma molto bene.";
                link.l1.go = "exit";
				break;
			}                   
		break;
		
		//Португалец
		case "Portugal":
			dialog.text = "Bart il Portoghese?! Lo avete? Vivo?";
			link.l1 = "So che non hai bisogno che lui muoia. È vivo. Ho dovuto fare un sacco di sforzi per mantenerlo in vita!";
			link.l1.go = "Portugal_1";
		break;
		
		case "Portugal_1":
			dialog.text = "Eccellente! Ora ci dirà tutto... Mynheer, prepara il prigioniero per il trasferimento. Invieremo immediatamente una barca militare alla tua nave. ";
			link.l1 = "Mi piacerebbe parlare della mia ricompensa prima, Mynheer...Se non le dispiace.";
			link.l1.go = "Portugal_2";
		break;
		
		case "Portugal_2":
			dialog.text = "Non preoccuparti della tua ricompensa, capitano. La riceverai. Abbiamo assegnato un prezzo per la testa di Bartolomeo il Portoghese - mille e cinquecento dobloni. Tenente! Porta al capitano la sua ricompensa!";
			link.l1 = "Mh... Sembra che Hugo mi abbia mentito su due mila dobloni... Va bene così.";
			link.l1.go = "Portugal_3";
		break;
		
		case "Portugal_3":
			TakeNItems(pchar, "gold_dublon", 1500);
			Log_Info("You have received 1500 doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "E ora, capitano, sareste così gentile da trasferire il portoghese alla Compagnia. Non vediamo l'ora di parlare con lui.";
			link.l1 = "Certo, signore, mandate la barca alla mia nave.";
			link.l1.go = "Portugal_4";
		break;
		
		case "Portugal_4":
			DialogExit();
			DoQuestReloadToLocation("Villemstad_town", "reload", "reload1", "Portugal_Final");
			DeleteAttribute(pchar, "questTemp.Portugal.Villemstad");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
