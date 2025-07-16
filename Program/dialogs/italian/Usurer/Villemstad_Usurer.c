// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Quali domande avete?","Come posso aiutarti?"),"Hai cercato di farmi quella domanda poco tempo fa...","Sì, lascia che indovini... Ancora una volta giri in tondo?","Ascolta, io gestisco le finanze qui, non rispondo alle domande...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Ho cambiato idea...","Non ho nulla di cui parlare al momento."),"Umph, dove se n'è andata la mia memoria...","L'hai indovinato, mi dispiace...","Capisco...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "utensil" && !CheckAttribute(npchar, "quest.utensil"))
			{
				link.l1 = "Signore, ho un affare un po' insolito. So che un corsaro francese di nome Gaius Marchais vi ha recentemente venduto due oggetti unici: un ostensorio d'oro e un incensiere d'oro. Vorrei acquistarli da voi.";
                link.l1.go = "guardoftruth";
			}
			if (CheckAttribute(npchar, "quest.GOT_chest") && CheckCharacterItem(pchar, "chest"))
			{
				link.l1 = "Vi ho portato un piccolo scrigno di dobloni.";
                link.l1.go = "guardoftruth_3";
			}
		break;
		
		case "guardoftruth":
			dialog.text = "Oh, sì! Mi ricordo di loro, naturalmente! Sì, erano veramente originali e, cosa più importante, costosi. Ma sei troppo in ritardo, capitano, non li ho più. Li ho già venduti.";
			link.l1 = "Incredibile! E a chi interessavano oggetti sacri di quel tipo? Signore, a chi li hai venduti? Mi piacerebbe provare a riacquistarli...";
			link.l1.go = "guardoftruth_1";
			npchar.quest.utensil = "true";
		break;
		
		case "guardoftruth_1":
			dialog.text = "Mm, e perché dovrei darti i nomi dei miei clienti?";
			if (CheckAttribute(pchar, "questTemp.HWIC.Detector") && pchar.questTemp.HWIC.Detector == "self_win")
			{
				link.l1 = "Forse, perché sono un buon amico agli occhi del governatore Matthias Beck e posso chiedere a lui una corrispondente sanzione per te?";
				link.l1.go = "guardoftruth_2_1";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.HWIC.Detector") && pchar.questTemp.HWIC.Detector == "holl_win")
				{
					link.l1 = "Forse, perché ho buoni rapporti con la Compagnia Olandese delle Indie Occidentali e ho reso un grande aiuto a molti coloni olandesi nell'arcipelago?";
					link.l1.go = "guardoftruth_2_2";
				}	
				else
				{
					link.l1 = "Forse perché lo pagherò?";
					link.l1.go = "guardoftruth_2_3";
					npchar.quest.GOT_chest = "true";
				}
			}
		break;
		
		case "guardoftruth_2_1":
			dialog.text = "Ah, certo che sei "+GetFullName(pchar)+", un amico del governatore stesso che ha rivelato la cospirazione criminale di Lucas Rodenburg... Come potrei dimenticarmi di questo? Certo, ti dirò.";
			link.l1 = "Allora, sono tutto orecchie.";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_2_2":
			dialog.text = "Ah, giusto, tu sei "+GetFullName(pchar)+", il grande conquistatore della 'nave fantasma' dei pirati. Come potrei dimenticarlo? Certamente, ti dirò.";
			link.l1 = "Allora, sono tutto orecchie.";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_2_3":
			dialog.text = "Bene, allora. Per un forziere riempito fino all'orlo di dobloni d'oro, suppongo che ti parlerò di coloro che ti hanno superato per effettuare l'acquisto.";
			if (CheckCharacterItem(pchar, "chest"))
			{
				link.l1 = "Ecco, prendi. Sono oggetti molto cari a me...";
				link.l1.go = "guardoftruth_3";
			}
			else
			{
				link.l1 = "Va bene, ti porterò quello che chiedi. Sono oggetti molto cari per me...";
				link.l1.go = "exit";
			}
		break;
		
		case "guardoftruth_3":
			RemoveItems(pchar, "chest", 1);
			Log_Info("You've given a chest of doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "Meraviglioso. In tal caso, sono disposto a condividere alcune informazioni con te.";
			link.l1 = "Sono tutto orecchie.";
			link.l1.go = "guardoftruth_4";
			DeleteAttribute(npchar, "quest.GOT_chest");
		break;
		
		case "guardoftruth_4":
			dialog.text = "L'incensiere d'oro è stato comprato da un uomo di nome Rolande Moses, meglio conosciuto come Rollie il Cappello. Perché questo macellaio avesse bisogno di un prezioso oggetto da chiesa, non riesco a capirlo, ma per qualche motivo ne era indescrivibilmente gioioso... A proposito, dubito che incontrerai lo stesso Rollie.";
			link.l1 = "Perché è così?";
			link.l1.go = "guardoftruth_5";
		break;
		
		case "guardoftruth_5":
			dialog.text = "Perché questo avido ladro di solitari mercanti inglesi è recentemente caduto con la sua goletta direttamente nelle grinfie del Colonnello Fox. Sai chi è?";
			link.l1 = "Certo! Il comandante delle 'volpi di mare' a St. Jones ad Antigua...";
			link.l1.go = "guardoftruth_6";
		break;
		
		case "guardoftruth_6":
			dialog.text = "Ebbene, allora capisci perché non vedremo mai più il povero Rolande. Il colonnello ha sequestrato la sua goletta con tutti i sopravvissuti del suo equipaggio e li ha consegnati a St. Jones dove probabilmente hanno già avuto un cappio stretto attorno al loro collo.";
			link.l1 = "Capisco. E l'ostensorio?";
			link.l1.go = "guardoftruth_7";
		break;
		
		case "guardoftruth_7":
			dialog.text = "L'ostensorio è stato acquisito molto recentemente dalla Signora Belinda de Ribero da Cumana. Una signora molto notabile, parente di Fernando de Villegas stesso, governatore di Cumana. Presumo che volesse portarlo come un dono alla chiesa.";
			link.l1 = "Signora Belinda de Ribero? Posso trovarla a Cumana, giusto?";
			link.l1.go = "guardoftruth_8";
		break;
		
		case "guardoftruth_8":
			dialog.text = "Sicuramente. Lei stessa ha detto che sarebbe andata direttamente a casa da Willemstad.";
			link.l1 = "Bene. Grazie, "+npchar.name+", sei stato di grande aiuto!";
			link.l1.go = "guardoftruth_9";
		break;
		
		case "guardoftruth_9":
			dialog.text = "In qualsiasi momento, mio signore. Visitami di tanto in tanto!";
			link.l1 = "Vi auguro clienti ricchi con portafogli grassi e cervelli magri... Ah-ah!";
			link.l1.go = "guardoftruth_10";
		break;
		
		case "guardoftruth_10":
			DialogExit();
			AddQuestRecord("Guardoftruth", "23");
			pchar.questTemp.Guardoftruth.Usurer = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
