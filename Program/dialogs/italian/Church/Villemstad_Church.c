// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Che tipo di domande, "+GetSexPhrase("mio figlio","mia figlia")+"?","Fai pure, sto ascoltando..."),"Ascolto, parla ora, "+GetSexPhrase("mio figlio","mia figlia")+"...","Per la terza volta, "+GetSexPhrase("mio figlio","mia figlia")+", chiedi ciò di cui hai bisogno.","Un religioso ha molto lavoro e tu mi stai distrarrendo, "+GetSexPhrase("mio figlio","mia figlia")+"...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Ho cambiato idea...","Non in questo momento, padre..."),"Non ho nulla da dire, mi scuso.","Chiederò, ma più tardi. Perdonami, padre.","Perdonami, santo padre...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "priest")
			{
				link.l1 = "Mi scusi, padre, uno dei chierici della vostra parrocchia mi ha chiesto di indagare sulla casa in cui Joachim Merriman affittava una stanza...";
				link.l1.go = "caleuche";
			}
		break;
		
		// калеуче
		case "caleuche":
			dialog.text = "Allora? Sei stato lì, mio figlio?";
			link.l1 = "L'ho fatto. Ma onestamente, sarebbe stato meglio se non l'avessi fatto. Sono stato attaccato da uno scheletro con un'ascia enorme nella stanza superiore. Sono riuscito a uscire vittorioso, anche se certamente non è stato facile.";
			link.l1.go = "caleuche_1";
		break;
		
		case "caleuche_1":
			dialog.text = "Mio Signore, abbi pietà delle nostre anime! I miei peggiori timori si sono avverati!";
			link.l1 = "Non è tutto, padre. Quando finalmente l'ho abbattuto, ha urlato e sembrava una donna. Tra le ossa ho trovato dei gioielli, quindi è sicuro supporre che fosse la locandiera scomparsa.";
			link.l1.go = "caleuche_2";
		break;
		
		case "caleuche_2":
			dialog.text = "(si fa il segno della croce)... Povero servo di Dio, che il Signore metta la sua anima in pace...";
			link.l1 = "Sembra che Merriman sia davvero un stregone. Non ho idea di come si possa trasformare un uomo vivente in un abominio del genere.";
			link.l1.go = "caleuche_3";
		break;
		
		case "caleuche_3":
			dialog.text = "Joachim Merriman è un stregone molto temibile, mio figlio. Lo conoscevo in Europa, ma all'epoca non era capace di fare nulla del genere. Qui, nei Caraibi, è riuscito a mettere le mani su qualcosa che gli ha dato poteri sovrannaturali.";
			link.l1 = "Conosceva Merriman, Padre?";
			link.l1.go = "caleuche_4";
		break;
		
		case "caleuche_4":
			dialog.text = "That I did. Back then I was just a humble priest in one of Lisbon's parishes. Joachim Merriman was a wealthy nobleman, and at some point he became interested in old manuscripts and scrolls brought by sailors from distant lands. He also began to study alchemy, but after some time he went into seclusion.\nPeople saw flashes of light in his house; sometimes they could also smell something strange. Then they saw him in the cemetery at nights. Once they saw him digging out a fresh corpse and bringing it to his home. And when patience ran out, local father superior contacted the Inquisition.\nWhen the guards breached the door of Merriman's house, Joachim was not there - he had escaped through a secret passage. They found a lab in the basement, and even the seasoned soldiers were shocked and sickened by what they saw. Whole rotting and dismembered bodies, human and animal skeletons, strange things... Fear and hatred for Merriman was so significant that his house was demolished in an instant.\nMerriman disappeared without a trace. The Inquisition began to search for him, sentencing him in his absence to burn at a stake as a dangerous warlock. But they never found him. And now, after all these years, I saw him again on the streets of Willemstad.";
			link.l1 = "Perché non hai detto nulla agli inquisitori?";
			link.l1.go = "caleuche_5";
		break;
		
		case "caleuche_5":
			dialog.text = "Mio figlio, non sai che la nostra chiesa è in conflitto con l'Inquisizione? Preferirei stare alla larga da Padre Vincento e i suoi teppisti.";
			link.l1 = "Capisco. Padre, credo di sapere da dove Merriman ha tratto il suo potere. Si è impadronito di un antico manufatto, un teschio di giada di Yum Cimil, un antico dio della morte adorato dagli indiani della tribù Chavin.";
			link.l1.go = "caleuche_6";
		break;
		
		case "caleuche_6":
			dialog.text = "Eh, Merriman era noto per eseguire rituali stregoneri e esperimenti su cadaveri, quindi potrebbe essere davvero vero. Ringrazio Dio che quest'uomo terribile ha lasciato Willemstad e che tu hai distrutto i semi diabolici che ha cercato di piantare qui. Siamo fortemente in debito con te, mio figlio. Per favore accetta questi oggetti santificati come tua ricompensa.";
			link.l1 = "Grazie, Padre";
			link.l1.go = "caleuche_7";
		break;
		
		case "caleuche_7":
			Log_Info("You have received church amulets");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "amulet_2"); 
			GiveItem2Character(pchar, "amulet_6"); 
			GiveItem2Character(pchar, "amulet_8"); 
			GiveItem2Character(pchar, "amulet_10"); 
			ref sld = characterFromId("Havana_Priest");
			dialog.text = "Ma quella non fu la fine dei nostri problemi, mio figlio. Di recente, ho ricevuto una lettera da "+sld.name+", padre superiore della chiesa di L'Avana. Porta notizie terribili. In una grotta, nella giungla di Cuba, i cacciatori hanno visto abomini orribili, i morti che camminano. E tutto ciò è ancora più fastidioso considerando il fatto che di recente, delle persone sono scomparse dopo essere entrate nella giungla.";
			link.l1 = "Mmm... stai suggerendo che anche questo è opera di Merriman?";
			if (CheckCharacterItem(pchar, "HolTradeLicence") && GetDaysContinueNationLicence(HOLLAND) >= 30) link.l1.go = "caleuche_8_1";
			else link.l1.go = "caleuche_8";
		break;
		
		case "caleuche_8":
			sld = characterFromId("Havana_Priest");
			dialog.text = "Non so cosa pensare, mio figlio. Ma se quel stregone nero è diventato così potente, tutti gli abitanti dell'arcipelago sono in grave pericolo. Solo Dio sa cosa potrebbe avere in mente questo servo del diavolo\nSpero davvero che Padre "+sld.name+"era sbagliato, ma comunque - per favore vai a L'Avana e parla con lui. Ho preparato per te una licenza di commercio, valida per un mese. Con essa, potrai entrare nel porto de L'Avana senza alcuna difficoltà.";
			link.l1 = "Bene, Padre. Me ne andrò a L'Avana.";
			link.l1.go = "caleuche_9";
			npchar.quest.givelicence = true;
		break;
		
		case "caleuche_8_1":
			sld = characterFromId("Havana_Priest");
			dialog.text = "Non so cosa pensare, mio figlio. Ma se quel stregone nero è diventato così potente, tutti gli abitanti dell'arcipelago sono in grave pericolo. Solo Dio sa cosa potrebbe avere in mente questo servo dei diavoli.\nSpero vivamente che Padre "+sld.name+"era sbagliato, ma non importa - ti chiedo di viaggiare a L'Avana e parlare con lui.";
			link.l1 = "Certo, Padre. Mi dirigerò verso L'Avana immediatamente.";
			link.l1.go = "caleuche_9";
		break;
		
		case "caleuche_9":
			dialog.text = "Sono lieto che tu sia un vero figlio della Chiesa. Prego per la tua salute e il tuo benessere giorno e notte. Vai con la mia benedizione. Possa il Signore rafforzarti nella tua lotta contro questi poteri empî.";
			link.l1 = "Grazie e addio, Padre.";
			link.l1.go = "caleuche_10";
		break;
		
		case "caleuche_10":
			DialogExit();
			AddQuestRecord("Caleuche", "26");
			AddCharacterMaxHealth(pchar, 1);
			if (CheckAttribute(npchar, "quest.givelicence")) GiveNationLicence(HOLLAND, 30);
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterComplexReputation(pchar, "fame", 3);
			ChangeCharacterNationReputation(pchar, HOLLAND, 5);
			AddCharacterExpToSkill(pchar, "Leadership", 300);
			pchar.questTemp.Caleuche = "havana";
			Caleuche_PrepareCubaGrot();
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
