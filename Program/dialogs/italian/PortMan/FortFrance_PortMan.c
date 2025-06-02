// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Che tipo di domande?","Cosa vuoi, "+GetAddress_Form(NPChar)+"?"),"Hai già provato a farmi una domanda "+GetAddress_Form(NPChar)+"...","Hai parlato di qualche domanda per la terza volta oggi...","Guarda, se non hai nulla da dirmi sulle questioni del porto, non disturbarmi con le tue domande.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Ho cambiato idea.","Non ho nulla di cui parlare."),"Mai mente.","Infatti, già la terza volta...","Mi dispiace, ma per ora non mi interessano gli affari del porto.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//--> Бремя гасконца
		if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "ship" && !CheckAttribute(npchar, "quest.RescueDaughter"))
		{
			DelLandQuestMark(npchar);
			link.l1 = "Signore, sto cercando un lavoro. Ma non un lavoro da portiere, qualcosa di più adatto al mio rango. Missione, servizio, con questioni delicate... Prenderò qualsiasi incarico abbiate.";
			link.l1.go = "Sharlie";
		}
		//<-- Бремя гасконца
		
		// Jason „олго и счастливо
		if (CheckAttribute(pchar, "questTemp.LongHappy") && pchar.questTemp.LongHappy == "portman")
		{
			link.l1 = "Mi è stato detto che avevi una lettera per me. Il nome è Capitano Charles de Maure.";
			link.l1.go = "LH_letter";
		}
		break;
		
		case "Sharlie":
			dialog.text = "Aiuto? Eh. Sto bene, grazie a Dio. Ma uno dei miei amici ha davvero bisogno di aiuto ed è urgente. Sta per entrare nella giungla da solo per combattere gli indiani, è pura follia!\nHo cercato di ragionare con lui, l'ho supplicato, ma non ha voluto ascoltare! Si preoccupa troppo per sua figlia ed è pronto a dare la sua vita per lei!";
			link.l1 = "Aspetta, ricominciamo: chi è il tuo amico, dove posso trovarlo, e di che tipo di aiuto ha bisogno?";
			link.l1.go = "Sharlie_1";			
		break;
		
		case "Sharlie_1":
			dialog.text = "Ah, perdonami, sono solo troppo ansioso. Il suo nome è Prosper...Prosper Troubale. È destinato a morire di sicuro! E non posso aiutarlo - non sono un soldato. Sua figlia è scomparsa e lui crede che gli indiani locali siano responsabili\nImmagina, ha intenzione di andare da solo a caccia dei selvaggi indomiti! Lo sminuzzeranno... In questo momento sta comprando un moschetto e si sta preparando a recarsi nella selva!";
			link.l1 = "Sei un pessimo narratore, mascalzone. Dove posso trovare il tuo amico... come si chiama... Prospero?";
			link.l1.go = "Sharlie_2";			
		break;
		
		case "Sharlie_2":
			dialog.text = "Ho appena parlato con lui e stavo cercando di farlo cambiare idea. Non è lontano dalle porte della città, vicino al pozzo, sta controllando il suo moschetto e le munizioni. Vai da lui e fai qualcosa! Se entra nella giungla da solo, non tornerà, ne sono sicuro. I diavoli dalla pelle rossa lo faranno a pezzi...";
			link.l1 = "Smettila di blaterare, sembri una vecchia! Sto andando subito da tuo amico. Spero di poterlo aiutare.";
			link.l1.go = "Sharlie_3";			
		break;
		
		case "Sharlie_3":
			DialogExit();
			AddQuestRecord("SharlieF", "1");
			RescueDaughter_CreateProsper();
			npchar.quest.RescueDaughter = "true";
			QuestPointerDelLoc("fortfrance_town", "reload", "reload10_back");
		break;
		
		// Jason „олго и счастливо
		case "LH_letter":
			dialog.text = "Sì, hai ragione - c'è una busta. Ecco qui, ma prima, devi pagare per la consegna - dodicimila pesos d'argento.";
			if (sti(pchar.money) >= 12000)
			{
				link.l1 = "Ho sempre sospettato che il tuo mestiere fosse originariamente affari di ladri, ma in qualche modo mi è sfuggita la posta, hm. Per favore, ecco i tuoi soldi.";
				link.l1.go = "LH_letter_1";
			}
			else
			{
				link.l1 = "Tornerò un po' più tardi, credo di aver lasciato il mio borsellino alla taverna.";
				link.l1.go = "exit";
			}
		break;
		
		case "LH_letter_1":
			DialogExit();
			AddMoneyToCharacter(pchar, -12000);
			LongHappy_RecibeLetter();
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
