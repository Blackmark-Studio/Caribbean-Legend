// полковник Фокс - бравый командир морской пехоты 'морские лисы'.
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "questTemp.Terrapin_KathyReward"))
			{
				dialog.text = "Cosa desidera, Signore? Oh... mio... aspetta! Sei il capitano francese che ha salvato mia figlia dalle sporche mani dei servi di Levasseur!";
				link.l1 = "Vedo che Catherine ti ha già parlato di me...";
				link.l1.go = "terrapin";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth.Usurer") && !CheckAttribute(npchar, "quest.utensil"))
			{
				dialog.text = "Cosa desidera, Signore?";
				link.l1 = "Buongiorno, Colonnello. Sono venuto da lei per una questione 'insolita'. Potrebbe riservarmi un po' di tempo?";
				link.l1.go = "guardoftruth";
				break;
			}
			// Addon-2016 Jason, французские миниквесты (ФМК) Сент-Кристофер
			if (CheckAttribute(pchar, "questTemp.FMQN") && pchar.questTemp.FMQN == "eng_reward")
			{
				dialog.text = "Se ho capito bene, sei il Capitano francese che ha assistito i miei uomini nella loro missione a Sint-Maarten?"+TimeGreeting()+"!";
				link.l1 = TimeGreeting()+", Colonnello. Sì, sarei io.";
				link.l1.go = "FMQN";
				break;
			}
			dialog.text = "Cosa vuole, Signore?";
			link.l1 = "Nulla, Colonel. Prendo congedo.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "guardoftruth":
			dialog.text = "Allora sputalo fuori già, dato che sei già arrivato così lontano...";
			link.l1 = "Di recente hai abbordato uno Schooner sotto il comando di Rollie il Capo, un pirata olandese, e hai portato il Capitano qui, a St. John's.";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "Capitano? Oh, non farmi ridere! Questo fetente criminale non ha diritto di essere chiamato con questo rango onorabile. Ho catturato un maledetto pirata, il capo di un branco di lupi, che ha saccheggiato e ucciso commercianti e mercanti inglesi. E mi sono assicurato che lui e i suoi degenerati ricevessero ciò che meritavano - l'intera St. John's ha assistito alla loro impiccagione sul molo!";
			link.l1 = "Immagino che non potrò interrogare questo canaglia allora... Colonnello, forse potresti aiutarmi? Il pirata aveva qualcosa in suo possesso che non gli apparteneva - l'incensiere d'oro. Hai trovato qualcosa su di lui che assomiglia a quello?";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "No, lo abbiamo perquisito e quel birbante non possedeva alcun bene, inoltre, tutto era sicuramente preso da onesti commercianti! E riguardo la tua preoccupazione... hmm no, non l'abbiamo trovato. E cosa potrebbe mai fare un incensiere su una nave pirata? Pensi davvero che ci fosse un prete tra loro?";
			link.l1 = "No, non lo faccio. Rollie il Cap l'ha comprato dall'usuraio a Willemstad, che a sua volta l'aveva comprato da un altro pirata. L'incensiere è bello e costoso, e sto cercando di restituirlo ai legittimi proprietari. Suppongo che Rollie avesse gli occhi puntati su di esso come una gazza.";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "In verità, Rollie aveva stive vuote e alcune casse con dobloni quando abbiamo abbordato e catturato la sua nave. Nient'altro che spazzatura. Nessun oggetto di valore, nessun turibolo d'oro. Mi ricorderei di un oggetto così inadatto per un pirata.\nSospetto che quel maledetto pirata abbia nascosto i suoi risparmi a Dominica. Siamo persino sbarcati lì e abbiamo cercato la zona, ma non abbiamo trovato nulla. Ma non ci siamo fermati sull'isola o esplorato le sue profondità a causa di un gran numero di selvaggi lì.";
			link.l1 = "Mh... Il pirata avrebbe potuto nascondere l'incensiere con il resto delle sue cose rubate da qualche parte a Dominica... Peccato. Hai interrogato il pirata, prima dell'esecuzione?";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			dialog.text = "L'ho fatto... e lui ha iniziato a ridere in faccia a me. Ma non mi importava davvero dei suoi nascondigli. Rollie il Cap è stato impiccato e questa è la cosa più importante.";
			link.l1 = "Capisco. Grazie per il tuo racconto e il tuo tempo, Colonnello. Addio...";
			link.l1.go = "guardoftruth_5";
		break;
		
		case "guardoftruth_5":
			DialogExit();
			npchar.quest.utensil = "true";
			AddQuestRecord("Guardoftruth", "24");
			Island_SetReloadEnableGlobal("Dominica", true);//patch-7
			// заполняем сундук
			pchar.GenQuestBox.Shore27 = true;
			pchar.GenQuestBox.Shore27.box1.money = 30000;
			pchar.GenQuestBox.Shore27.box1.items.gold_dublon = 100;
			pchar.GenQuestBox.Shore27.box1.items.chest = 1;
			pchar.GenQuestBox.Shore27.box1.items.icollection = 1;
			pchar.GenQuestBox.Shore27.box1.items.jewelry40 = 15;
			pchar.GenQuestBox.Shore27.box1.items.jewelry41 = 22;
			pchar.GenQuestBox.Shore27.box1.items.jewelry42 = 8;
			pchar.GenQuestBox.Shore27.box1.items.jewelry43 = 20;
			pchar.GenQuestBox.Shore27.box1.items.jewelry44 = 33;
			pchar.GenQuestBox.Shore27.box1.items.jewelry45 = 16;
			pchar.GenQuestBox.Shore27.box1.items.jewelry46 = 58;
			pchar.GenQuestBox.Shore27.box1.items.jewelry35 = 1; // кадило
			pchar.quest.GuardOT_finddominicachest.win_condition.l1 = "item";
			pchar.quest.GuardOT_finddominicachest.win_condition.l1.item = "jewelry35";
			pchar.quest.GuardOT_finddominicachest.function = "GuardOT_DominicaChest";
		break;
		
		case "terrapin":
			dialog.text = "Diverse volte, capitano! Il tuo onorevole e coraggioso gesto era difficilmente prevedibile da un francese. Ti devo la mia gratitudine, come soldato e come padre. Non c'è niente di più prezioso per me in questo mondo intero che mia figlia...";
			link.l1 = "Sono contento di poter essere stato d'aiuto, e spero che con le mie azioni cambierete la vostra opinione sui francesi, nel tempo.";
			link.l1.go = "terrapin_1";
		break;
		
		case "terrapin_1":
			dialog.text = "La presenza di un signore tanto onorevole e generoso come te, che ha rischiato la propria vita per una sconosciuta fanciulla inglese, causerà un essenziale riscaldamento delle mie relazioni con i tuoi compatrioti!";
			link.l1 = "Ci sono persone oneste tra i ratti in ogni nazione, colonnello...";
			link.l1.go = "terrapin_2";
		break;
		
		case "terrapin_2":
			dialog.text = "E hai dimostrato proprio questo! Una ricompensa ti aspetta, capitano. Naturalmente, la vita di una figlia non ha prezzo, ma Jonathan Fox paga sempre i suoi debiti, lo giuro! Sei un vero soldato, quindi, il mio regalo per te è un regalo da soldato. Guarda qui.\nQuesto è un trombone, un eccellente moschetto da marina, può essere usato con una mano. Puoi caricarlo con frecce speciali che perforeranno sempre anche la corazza più resistente. Spara anche mitraglia e la sua solida costruzione ti permette di caricarlo con cariche di chiodi. Prendilo, ora è tuo.";
			link.l1 = "Un dono così eccellente per un soldato, ti ringrazio, Colonnello!";
			link.l1.go = "terrapin_3";
		break;
		
		case "terrapin_3":
			Log_Info("You have received a blunderbuss");
			Log_Info("You have received 10 arrows");
			Log_Info("You have received 10 charges of nails");
			Log_Info("You have received instructions for creating the harpoon arrows");
			Log_Info("You have received instructions for creating the charge of nails");
			GiveItem2Character(pchar, "pistol8");
			TakeNItems(pchar, "harpoon", 10);
			TakeNItems(pchar, "GunEchin", 10);
			GiveItem2Character(pchar, "recipe_harpoon"); 
			GiveItem2Character(pchar, "recipe_GunEchin"); 
			PlaySound("interface\important_item.wav");
			dialog.text = "Ti consegno anche una piccola partita di munizioni e le istruzioni per la loro creazione. Sarebbe un peccato se non usassi il suo potere al massimo!";
			link.l1 = "Grazie, Colonnello. Non rifiuterò un tale dono, ma voglio che tu sappia che non ho salvato Catherine per un premio. Semplicemente non avrei potuto lasciare che una ragazza indifesa subisse alcun danno.";
			link.l1.go = "terrapin_4";
		break;
		
		case "terrapin_4":
			dialog.text = "Lo so, capitano. Questo ti onora doppiamente. Catherine era davvero rapita da te e non è un compito facile fare una buona impressione su di lei. Ancora una volta, ti dobbiamo la nostra gratitudine per averla salvata. Ti devo!";
			link.l1 = "Beh, ti ringrazio per il dono, Colonnello. Manda i miei migliori saluti a Catherine, e spero che la prossima volta ascolterà suo padre.";
			link.l1.go = "terrapin_5";
		break;
		
		case "terrapin_5":
			dialog.text = "Lo farò, Capitano! Addio, e buon viaggio!";
			link.l1 = "Addio, Colonnello.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Terrapin_KathyReward");
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			ChangeCharacterComplexReputation(pchar, "fame", 5);
			ChangeCharacterNationReputation(pchar, ENGLAND, 20);
		break;
		
		// Addon-2016 Jason, французские миниквесты (ФМК) Сент-Кристофер
		case "FMQN":
			DelLandQuestMark(npchar);
			dialog.text = "Ho letto il rapporto. Le tue azioni sono state valutate molto positivamente, quindi devi essere ricompensato. Trentamila pesos per i servizi di spedizione e armi per l'eroismo in guerra. Accetta questa spada e questo archibugio. Ora sono tutti tuoi!";
			link.l1 = "Grazie, Signore.";
			link.l1.go = "FMQN_1";
		break;
		
		case "FMQN_1":
			dialog.text = "Certo, Capitano. Sei anche ricompensato con l'amore e il rispetto delle colonie britanniche, delle autorità e personalmente mio. Grazie per non aver abbandonato i miei uomini e per averli aiutati nella loro missione!";
			link.l1 = "Un piacere, Colonnello...";
			link.l1.go = "FMQN_2";
		break;
		
		case "FMQN_2":
			dialog.text = "Ora, mi scusi, ho altre faccende di cui occuparmi. Dio vi assista, Capitano.";
			link.l1 = "Arrivederci, Signore.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQN_EnglandComplete");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
