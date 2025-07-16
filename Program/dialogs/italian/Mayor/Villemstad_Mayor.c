// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Cosa vuoi? Chiedi pure.","Sto ascoltando, qual è la domanda?"),"Questa è la seconda volta che cerchi di chiedere...","Questa è la terza volta che provi a chiedere...","Quando finirà tutto questo?! Sono un uomo impegnato, lavoro su questioni della colonia e tu continui a infastidirmi!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Ho cambiato idea, mi dispiace.","Non ora. Luogo e momento sbagliati."),"È vero, non ho nulla da dire ora, mi dispiace.","Chiederò, più tardi.","Mi dispiace, "+GetAddress_FormToNPC(NPChar)+"...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//Португалец
			if (CheckAttribute(pchar, "questTemp.Portugal.Villemstad"))
			{
				link.l1 = "So che la Compagnia Olandese delle Indie Occidentali ha messo una taglia sulla testa di un certo pirata - Bartolomeo il Portoghese. Sono riuscito a catturarlo. Attualmente è nella mia stiva e sono pronto a consegnarlo alle autorità.";
                link.l1.go = "Portugeze";
			}
		break;

		case "Cupture_after":
            dialog.text = RandPhraseSimple("Hai già preso tutto. Cosa vuoi ancora?","C'è qualcosa che non hai preso?");
            link.l1 = RandPhraseSimple("Solo dando un'occhiata in giro...","Solo un controllo, potrei aver dimenticato di prendere qualcosa...");
            link.l1.go = "exit";
            NextDiag.TempNode = "Cupture_after";
		break;
		
		//Португалец
		case "Portugeze":
			dialog.text = "Bart il Portoghese?! Lo avete, vivo?!";
			link.l1 = "So che non ti serve a nulla morto. È vivo e, dannati siano gli dei, ho dovuto trattenere me stesso per mantenerlo in vita!";
			link.l1.go = "Portugeze_1";
		break;
		
		case "Portugeze_1":
			dialog.text = "Eccellente! Ora ci dirà tutto... Mynheer, prepara il prigioniero per il trasferimento. Invieremo immediatamente una barca militare alla tua nave. ";
			link.l1 = "Vorrei parlare prima della mia ricompensa, Mynheer, se non le dispiace.";
			link.l1.go = "Portugeze_2";
		break;
		
		case "Portugeze_2":
			dialog.text = "Non preoccuparti della tua ricompensa, Signore. La riceverai. Abbiamo fissato un prezzo per la testa di Bartolomeo il Portoghese - mille e cinquecento dobloni. Tenente! Porta al capitano la sua ricompensa!";
			link.l1 = "Hm... Hugo mi ha detto che erano duemila dobloni... Va bene allora.";
			link.l1.go = "Portugeze_3";
		break;
		
		case "Portugeze_3":
			TakeNItems(pchar, "gold_dublon", 1500);
			Log_Info("You have received 1500 doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "E ora, Signore, sarebbe così gentile da trasferire il portoghese alla Compagnia? Siamo così ansiosi di parlare con lui.";
			link.l1 = "Certo, Mynheer, manda la barca alla mia nave.";
			link.l1.go = "Portugeze_4";
		break;
		
		case "Portugeze_4":
			DialogExit();
			DoQuestReloadToLocation("Villemstad_town", "reload", "reload1", "Portugal_Final");
			DeleteAttribute(pchar, "questTemp.Portugal.Villemstad");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
