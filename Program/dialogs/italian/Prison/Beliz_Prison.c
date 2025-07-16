// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
 	switch(Dialog.CurrentNode)
	{
        case "quests":
            dialog.text = "Parla, sto ascoltando";
			link.l1 = "Mi sono sbagliato. Addio.";
			link.l1.go = "Exit";
			// Калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche.Bandos") && pchar.questTemp.Caleuche.Bandos == "start")
			{
				link.l1 = "Sentii parlare di una banda di ladri e briganti che operano nelle vicinanze di Belize e nella stessa città.";
				link.l1.go = "caleuche";
			}
			if (CheckAttribute(pchar, "questTemp.Caleuche.Bandos") && pchar.questTemp.Caleuche.Bandos == "know" && CheckAttribute(pchar, "questTemp.Caleuche.belizbandos") && GetQuestPastDayParam("questTemp.Caleuche.belizbandos") < 3)
			{
				link.l1 = "Posso darti informazioni sulla banda.";
				link.l1.go = "caleuche_3";
			}
			if (CheckAttribute(pchar, "questTemp.Caleuche.BelizRegard"))
			{
				link.l1 = "Quali notizie sulla banda? Li avete catturati nella grotta?";
				link.l1.go = "caleuche_7";
			}
			// Путеводная звезда ==>
			if (CheckAttribute(pchar, "questTemp.PZ_Beliz_Komendant"))
			{
				link.l1 = "Sembra che tutta la città stia festeggiando la cattura di un pirata. Puoi dirmi di più?";
				link.l1.go = "PZ_Beliz_Komendant_1";
				DeleteAttribute(pchar, "questTemp.PZ_Beliz_Komendant");
			}
			// <== Путеводная звезда
		break;
		
		// Путеводная звезда ==>
		case "PZ_Beliz_Komendant_1":
			dialog.text = "Volentieri! Questo non è un pirata qualsiasi - è quel mascalzone, Matthew Lutter.";
			link.l1 = "Prima o poi la fortuna abbandona tutti.";
			link.l1.go = "PZ_Beliz_Komendant_2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_Beliz_Komendant_2":
			dialog.text = "Non sei inglese, e non sembri un mercante, quindi capisco perché non sei così entusiasta. Lutter ha terrorizzato queste acque per anni, attaccando sia noi che i Dons, ma più spesso noi. È sempre riuscito a sfuggire alle nostre pattuglie costiere, navigando la sua corvetta, il Seagull, che una volta era la nave più veloce dell'Arcipelago. Come sia arrivato a comandare una nave da guerra del genere, solo Dio lo sa.";
			link.l1 = "Allora è vero che ha perso contro un mercante? Su una corvetta? Sembra incredibile.";
			link.l1.go = "PZ_Beliz_Komendant_3";
		break;
		
		case "PZ_Beliz_Komendant_3":
			dialog.text = "Per quanto possa sembrare strano, è vero. Un mercante, e per di più uno spagnolo! La nostra marina potrebbe imparare una cosa o due da lui. Il capitano Sotta, capendo che non c'era scampo, si preparò per la battaglia...";
			link.l1 = "Un personaggio piuttosto insolito, questo Sotta.";
			link.l1.go = "PZ_Beliz_Komendant_4";
		break;
		
		case "PZ_Beliz_Komendant_4":
			dialog.text = "Forse. Ha fatto riallestita la sua nave per trasportare quante più merci possibili, il che ha reso la fuga impossibile. Sapendo che i pirati erano dopo il suo carico, ha fatto finta di essere alla deriva. E poi...";
			link.l1 = "...ha issato le vele al momento giusto?";
			link.l1.go = "PZ_Beliz_Komendant_5";
			if (!CharacterIsHere("Longway"))
			{
				sld = CharacterFromID("Longway");
				ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload1");
				LAi_SetActorType(sld);
				LAi_ActorFollow(sld, pchar, "", -1);
			}
		break;
		
		case "PZ_Beliz_Komendant_5":
			dialog.text = "Ah! No, ha sparato una bordata di mitraglia a bruciapelo mentre Lutter si avvicinava, e poi è salito a bordo del pirata stesso! Quando ha scoperto chi era Lutter, ce lo ha consegnato. Un vero eroe, un uomo d'onore!";
			link.l1 = "Non era solo l'onore a guidarlo - ci deve essere stata una ricompensa per aver catturato il Chiacchierone.";
			link.l1.go = "PZ_Beliz_Komendant_6";
		break;
		
		case "PZ_Beliz_Komendant_6":
			dialog.text = "A volte il profitto coincide con le buone intenzioni. Ma sì, è stato generosamente ricompensato. Sua Grazia lo ha riempito di merci costose come segno di gratitudine della nostra città prima che salpasse.";
			link.l1 = "Vorrei averlo incontrato - Mi piacerebbe stringergli la mano. Dimmi...";
			link.l1.go = "PZ_Beliz_Komendant_7";
		break;
		
		case "PZ_Beliz_Komendant_7":
			StartInstantDialog("Longway", "PZ_Beliz_Komendant_8", "Quest\CompanionQuests\Longway.c");
		break;
		// <== Путеводная звезда
		
		// Калеуче
		case "caleuche":
			dialog.text = "La tua fonte diceva la verità. Questi banditi sono diventati una vera spina nel fianco per noi. Vuoi dirci qualcosa su di loro?";
			link.l1 = "A parte il fatto che mi hanno rubato una cosa importante - nulla di più. Speravo che tu potessi dirmi qualcosa su di loro. Forse, uno di loro è stato catturato ed è ora pronto a testimoniare...";
			link.l1.go = "caleuche_1";
		break;
		
		case "caleuche_1":
			dialog.text = "Mi dispiace deluderti, capitano, ma non ho informazioni su di loro. So solo che si nascondono da qualche parte nella giungla, e hanno complici in città, tutto qui. Ora, se apprendi qualcosa di nuovo su di loro, per favore dimmelo immediatamente.";
			link.l1 = "Bene, ufficiale. Lo farò.";
			link.l1.go = "caleuche_2";
		break;
		
		case "caleuche_2":
			DialogExit();
			AddQuestRecord("Caleuche", "10");
			pchar.questTemp.Caleuche.Bandos = "seek";
		break;
		
		case "caleuche_3":
			string sTime;
			if (GetQuestPastDayParam("questTemp.Caleuche.belizbandos") == 0) sTime = "in three days";
			if (GetQuestPastDayParam("questTemp.Caleuche.belizbandos") == 1) sTime = "on the day after tomorrow";
			if (GetQuestPastDayParam("questTemp.Caleuche.belizbandos") == 2) sTime = "tomorrow";
			dialog.text = "Sei serio, capitano? Parla, sono tutto orecchie.";
			link.l1 = "Ho trovato uno dei loro informatori in città. Mi ha detto che la loro banda si sta preparando per attaccare una nave, che dovrebbe arrivare nella baia di Chetumal. I furfanti si stanno radunando "+sTime+" di notte vicino a una grotta non lontano da Belize. Per arrivarci, basta prendere il sentiero a sinistra al bivio nella giungla.";
			link.l1.go = "caleuche_4";
		break;
		
		case "caleuche_4":
			dialog.text = "Alla grotta? Ottime notizie. Darò l'ordine di preparare un'imboscata per questi furfanti. Se hai capito bene e il tuo informatore diceva la verità, prenderemo questi bastardi, e poi solleciterò il governatore a ricompensarti.";
			link.l1 = "Grazie! Verrò a trovarti, quando sarà finita.";
			link.l1.go = "caleuche_5";
		break;
		
		case "caleuche_5":
			dialog.text = "Bene. Va bene.";
			link.l1 = "A presto, ufficiale.";
			link.l1.go = "caleuche_6";
		break;
		
		case "caleuche_6":
			DialogExit();
			AddQuestRecord("Caleuche", "15");
			pchar.questTemp.Caleuche.Bandos = "comendant";
			pchar.questTemp.Caleuche.BelizChance = hrand(3);
			SetFunctionTimerCondition("Caleuche_BelizRegard", 0, 0, 3, false); // таймер
		break;
		
		case "caleuche_7":
			if (sti(pchar.questTemp.Caleuche.BelizChance) < 3)
			{
				dialog.text = "Abbiamo preparato un caldo benvenuto per i mascalzoni, ah-ah-ah! Se solo avessi potuto vedere le loro facce! Abbiamo preso tutti, incluso il capo! Alcuni hanno tentato di resistere, ma sono stati eliminati dai nostri coraggiosi soldati.";
				link.l1 = "Eccellenti notizie, ufficiale! Ora i cittadini di Belize possono finalmente dormire tranquilli.";
				link.l1.go = "caleuche_12";
			}
			else
			{
				dialog.text = "Hmm... I miei soldati li aspettavano nella grotta per tutta la notte, ma nessuno si è mai presentato. Il sergente era davvero furioso. È un bene che non ti abbia ancora preso.";
				link.l1 = "Maledizione! Non può essere! In quale caverna hai piazzato l'imboscata? Ce ne sono due!";
				link.l1.go = "caleuche_8";
			}
		break;
		
		case "caleuche_8":
			dialog.text = "Dove mi hai detto. A quello a destra al bivio...";
			link.l1 = "È QUELLO A SINISTRA! A sinistra del bivio, imbecilli!";
			link.l1.go = "caleuche_9";
		break;
		
		case "caleuche_9":
			dialog.text = "Ma ricordo perfettamente che hai detto 'a destra'.";
			link.l1 = "Oh mio Dio! A sinistra! Ho detto, A! SINISTRA! Li hai fatti scappare, ed è stata colpa tua!";
			link.l1.go = "caleuche_10";
		break;
		
		case "caleuche_10":
			AddQuestRecord("Caleuche", "16");
			dialog.text = "Allora devi aver borbottato qualcosa sotto i baffi. Senti, ho un'ottima udito, sai.";
			link.l1 = "Bene, ufficiale, non ho intenzione di discutere. Volevo aiutarti, ma non si può aiutare chi non può aiutare se stesso. Addio.";
			link.l1.go = "caleuche_11";
		break;
		
		case "caleuche_11":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.Caleuche.BelizChance");
			DeleteAttribute(pchar, "questTemp.Caleuche.BelizRegard");
		break;
		
		case "caleuche_12":
			dialog.text = "Ho riferito al governatore del tuo ruolo nell'eliminazione della banda. Ha valutato molto positivamente il tuo contributo e mi ha autorizzato a presentarti una ricompensa: un premio in denaro e un trofeo di archibugio.";
			link.l1 = "Grazie!";
			link.l1.go = "caleuche_13";
		break;
		
		case "caleuche_13":
			Log_Info("You have received a chest with doubloons");
			Log_Info("You have received an arquebus");
			PlaySound("interface\important_item.wav");
			AddQuestRecord("Caleuche", "17");
			GiveItem2Character(pchar, "chest"); 
			GiveItem2Character(pchar, "mushket3"); 
			dialog.text = "Grazie per il servizio, capitano! Se solo tutti i nostri cittadini fossero coscienziosi come te, avremmo sconfitto il crimine una volta per tutte molto tempo fa! Buona fortuna a te!";
			link.l1 = "Arrivederci, ufficiale! Buona fortuna nel tuo servizio!";
			link.l1.go = "caleuche_11";
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			ChangeCharacterComplexReputation(pchar, "authority", 3);
			ChangeCharacterComplexReputation(pchar, "fame", 3);
			OfficersReaction("good");
			ChangeCharacterNationReputation(pchar, ENGLAND, 8);
			AddCharacterExpToSkill(pchar, "Leadership", 300);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 200);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 200);//скрытность
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
