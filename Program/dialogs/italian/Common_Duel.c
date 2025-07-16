//navy 26.07.06
//генератор дуэлей...
//в диалоге НПС делаем линк с проверкой флага оскорбления... по нему переход на "outraged"
//если НПС сделал что-то ГГ (продажа фальшивки) или ГГ наехал на НПС, вешаем на него флаг.
//для некоторых, например ПГГ, можно делать переход сразу на вызов: "let_s_duel"
void ProcessDuelDialog(ref NPChar, aref Link, aref NextDiag)
{
	int iHour;
	string sLocation;

	//флаг убираем
	DeleteAttribute(NPChar, "Outrage");
    switch (Dialog.CurrentNode)
	{
	case "outraged":
		Dialog.Text = NPCharRepPhrase(NPChar,RandSwear()+RandPhraseSimple("Come osi insultarmi, mascalzone?!","Queste parole ti costeranno caro!"),RandPhraseSimple("Hai insultato il mio onore, "+GetAddress_Form(NPChar)+"! E pagherai per questo.","Come osi? Ritira subito le tue parole!"));

		//это такая засада.. чтобы читали текст :)
		MakeRandomLinkOrderTwo(link, 
					NPCharRepPhrase(pchar, 
				RandPhraseSimple("Ha?! I don't even want to stain my sword with your blood!", "Ha?! I don't even want to stain my sword with your blood!"), 
				RandPhraseSimple("I am always at your service!", "I am not going to choose words while speaking with the rabble!")), "outraged_1",
					NPCharRepPhrase(pchar, RandSwear() + 
				RandPhraseSimple("I didn't mean it!", "I fired up..."), 
				RandPhraseSimple("That was a mistake. I am sorry.", "I took you for someone else, " + GetAddress_FormToNPC(NPChar) + ". Please forgive me.")), "change_mind");
		break;

	case "outraged_1":
		Dialog.Text = NPCharRepPhrase(NPChar,RandPhraseSimple("Ti taglio le orecchie!","Ti strappo il cuore!"),RandPhraseSimple("Spero di sentire le tue scuse o non posso garantire che mi controllerò!","Ti rendi conto di cosa significa... lo fai?"));

		MakeRandomLinkOrderTwo(link,
					NPCharRepPhrase(pchar, RandSwear() + 
				RandPhraseSimple("I hope that your saber is as swift as your tongue!", "My blade will speak for me."), 
				RandPhraseSimple("I challenge you to a duel!", "That's a matter of honor!")), "let_s_duel",
					NPCharRepPhrase(pchar, 
				RandPhraseSimple("I think I am not ready yet!", "Think, we shouldn't get excited! These are words only!"), 
				RandPhraseSimple("I remembered, I am waiting. All blessings...", "Ah! Seems, my ship is sailing already. Bye.")), "change_mind");
		break;

	case "let_s_duel":
		//проверка на начатые дуэли.
		if (CheckAttribute(PChar, "questTemp.duel.Start") && sti(PChar.questTemp.duel.Start))
		{
			Dialog.Text = "Prima, risolvi i tuoi affari con gli altri, poi parleremo.";
			if (PChar.questTemp.duel.enemy == NPChar.id)
			{
				Dialog.Text = "Abbiamo già raggiunto un accordo.";
			}
			link.l1 = RandSwear()+"Oh, come potrei dimenticare...";
			link.l1.go = "exit";
			break
		}
		//может отказаться.
		if (rand(100) < 30)
		{
			Dialog.Text = RandPhraseSimple("Duello?! Vattene, non vali il tempo che sprecerei su di te.","Duello? Non meriti quell'onore! Sparisci!");
			link.l1 = RandPhraseSimple("Bene...","Immagino che posso aspettare...");
			link.l1.go = "exit";
/**/
			//можно дать возможность драться полюбому :)			
			if (rand(100) < 30)
			{
				link.l1 = RandPhraseSimple("Pensi così? Non essere così sicuro, bastardo!!!","Oh davvero?! Vedrò di che colore è il tuo sangue!");
				link.l1.go = "fight_right_now";
			}
/**/
			break;
		}

		//согласен.
		Dialog.Text = RandPhraseSimple("Un duello, dici? Va bene per me. Le nostre armi saranno spade e pistole.","Riesci nemmeno a tenere una spada?");
		link.l1 = RandPhraseSimple("Implorerai pietà, in ginocchio.","Ti strangolerò a mani nude, mascalzone!");
		link.l1.go = "land_duel";
		if (sti(pchar.Ship.Type) != SHIP_NOTUSED && sti(NPChar.Ship.Type) != SHIP_NOTUSED)
		{
			Dialog.Text = RandPhraseSimple(Dialog.Text+"O possiamo salpare e vedere chi è chi!","Lo duello?!! Ah, ti schiaccerò come un insetto! Scegli come vuoi morire!");
			link.l2 = RandPhraseSimple("In mare, sono il migliore che ci sia.","La mia nave affonderà facilmente la tua vecchia tinozza!");
			link.l2.go = "sea_duel";
		}
		link.l3 = "Ho cambiato idea...";
		link.l3.go = "change_mind";
		break;

	//дуэль на подводных лодках :))))
	case "sea_duel":
		Dialog.Text = RandPhraseSimple("Non vedo la tua nave nel porto...","Sparisci finché non trovi almeno una vecchia tinozza di merda!");
		link.l1 = RandPhraseSimple("Mi scuso...","Allora ti sto lasciando.");
		link.l1.go = "exit";
		if (pchar.location.from_sea == GetCurrentTown() + "_town")
		{
			Dialog.Text = "Bene, ti aspetterò all'uscita dalla cala...";
			link.l1 = "Non ti farò aspettare troppo a lungo.";

			pchar.questTemp.Duel.enemy = NPChar.id;
			pchar.questTemp.Duel.Sea_Location = Islands[GetCharacterCurrentIsland(PChar)].id;
			AddDialogExitQuestFunction("Duel_Sea_Prepare");
		}

		break;

	//на суше
	case "land_duel":
		iHour = 1 + rand(2);
		if (GetTime() > 4.0 && GetTime() < 17.0)
		{
//			iHour = MakeInt(18.0 - GetTime()) + rand(2); //раскоментировать для дуэлей только по ночам
		}
		pchar.questTemp.Duel.WaitTime = iHour;
		Dialog.Text = RandSwear()+RandPhraseSimple("Sguaina l'acciaio, vediamo di che colore è il tuo sangue!","Beh, se hai un desiderio di morte...");
		link.l1 = RandPhraseSimple("Dovremmo andare in un posto senza troppi testimoni. Conosco proprio il posto giusto fuori dalle porte della città. Incontriamoci lì in "+iHour+" ore.","Frena i tuoi cavalli. Queste cose si risolvono meglio senza testimoni. Entra "+iHour+"  ore all'ingresso della città.");
		link.l1.go = "fight_off_town";
		link.l2 = RandPhraseSimple("Beh, se vuoi morire così tanto...","Maledizione! Ti aiuterò a vedere l'Inferno con i tuoi stessi occhi!");
		link.l2.go = "fight_right_now";
		link.l3 = "Ho cambiato idea...";
		link.l3.go = "change_mind";

		if (rand(1))
		{
			Dialog.Text = RandSwear()+RandPhraseSimple("Credo che sarebbe meglio passare oltre le porte della città. Ti aspetterò lì in "+pchar.questTemp.Duel.WaitTime+" ore. Non ritardare!","Questo non è il miglior posto per risolvere le dispute. Sarebbe meglio uscire dalla città. In "+pchar.questTemp.Duel.WaitTime+" ore sarò lì.");
			link.l1 = RandPhraseSimple("Non meriti quell'onore! Difenditi!","Non ho tempo! Sguaina l'acciaio!");
			link.l1.go = "fight_right_now";
			link.l2 = RandPhraseSimple("Bene, facciamo una passeggiata.","Hai probabilmente ragione. Incontriamoci oltre le porte.");
			link.l2.go = "fight_off_town_prep";
		}
		break;

	//предложение "пойдём выйдем" рассматривается
	case "fight_off_town":
		Dialog.Text = RandPhraseSimple("Non meriti quell'onore! Difenditi!","Non ho tempo! Proprio qui e ora!");
		link.l1 = RandPhraseSimple("Bene, se vuoi morire così tanto...","Maledizione! Ti aiuterò a vedere l'Inferno con i tuoi stessi occhi!");
		link.l1.go = "fight_right_now";
		if (rand(1))
		{
			Dialog.Text = RandPhraseSimple("Bene, facciamo una passeggiata.","Hai probabilmente ragione. Incontriamoci oltre le porte.");
			link.l1 = RandPhraseSimple("Ti starò aspettando lì.","Non ritardare.");
			link.l1.go = "fight_off_town_prep";
		}
		break;

	//что ж, пойдём выйдем
	case "fight_off_town_prep":
		SaveCurrentQuestDateParam("questTemp.Duel.StartTime");
		PChar.questTemp.duel.Start = true;
		PChar.questTemp.duel.enemy = NPChar.id;
		sLocation = GetCurrentTown();
		if (sLocation != "")
		{
			//где?
			sLocation += "_ExitTown";
			pchar.questTemp.duel.place = sLocation;

			Locations[FindLocation(sLocation)].DisableEncounters = true;
			//приходит ко времени.
			pchar.quest.duel_move_opponent2place.win_condition.l1 = "Location";
			pchar.quest.duel_move_opponent2place.win_condition.l1.location = pchar.questTemp.duel.place;
			pchar.quest.duel_move_opponent2place.function = "Duel_Move_Opponent2Place";
			//на случай, если не дождется, часа вполне достаточно
			SetTimerConditionParam("duel_move_opponentBack", "Duel_Move_OpponentBack", 0, 0, 0, sti(GetTime() + 0.5) + sti(pchar.questTemp.Duel.WaitTime) + 1, false);
			pchar.quest.duel_move_opponentBack.function = "Duel_Move_OpponentBack";
			if (CheckAttribute(NPChar, "CityType"))
			{
				DeleteAttribute(NPChar, "City"); // чтоб не было ругани с нацией
	    		DeleteAttribute(NPChar, "CityType");
				if (!CheckAttribute(NPChar, "PGGAi")) 
				{
					if (!CheckAttribute(NPChar, "LifeDay")) npchar.LifeDay = 0;
					npchar.LifeDay = sti(npchar.LifeDay) + 3; // чтоб до дуэли не помер
				}
    		}
		}
		NextDiag.CurrentNode = "let_s_duel";
		DialogExit();
		break;

	//последнее слово перед боем
	case "talk_off_town":
		Dialog.Text = "Allora, sei pronto?";
		link.l1 = "Sì. Vediamo chi è l'uomo migliore!";
		link.l1.go = "fight_right_now";
		link.l2 = "No, ho deciso di portarti le scuse. Mi sbagliavo, mi sono infuocato.";
		link.l2.go = "change_mind";
		if (rand(100) < 20)
		{
			Dialog.Text = RandPhraseSimple("Ehi, ascolta, ci ho pensato su e ora vedo che avevo torto. Le mie scuse.","Maledizione! È tutta colpa di quel maledetto rum!!! Le mie scuse, "+GetSexPhrase("fratello","sorella")+"!");
			link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("No, solo il tuo sangue può darmi soddisfazione ora!","Tira fuori il tuo acciaio e smetti di piangere come una ragazzina!"),RandPhraseSimple("No! Esigo soddisfazione!","Sei una vergogna per la tua famiglia! Sguaina la tua spada!"));
			link.l1.go = "fight_right_now";
			link.l2 = NPCharRepPhrase(pchar,RandPhraseSimple("Bene, sono d'accordo. Ci siamo un po' agitati.","Chi tiene il conto tra amici!"),RandPhraseSimple("Hai probabilmente ragione. Non dovremmo versare sangue per cose così meschine.","La mia generosità non conosce limiti! Sei perdonato!"));
			link.l2.go = "peace";
		}
		NextDiag.TempNode = npchar.BackUp.DialogNode;
		pchar.questTemp.Duel.End = true;
		break;

	//дуэли быть!
	case "fight_right_now":
		PChar.questTemp.duel.enemy = NPChar.id;
		AddDialogExitQuestFunction("Duel_Prepare_Fight");
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;

	case "fight_right_now_1":	
		PChar.questTemp.duel.enemy = NPChar.id;
		PChar.questTemp.duel.enemyQty = rand(2) + 1;
		AddDialogExitQuestFunction("Duel_Prepare_Fight");
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();	
		break;
		
	//передумал, э... не хорошо ;)
	case "change_mind":
		if (CheckAttribute(pchar, "questTemp.Duel.End")) LAi_SetWarriorType(NPChar);
		Dialog.Text = NPCharRepPhrase(NPChar,RandSwear()+RandPhraseSimple("Allora sparisci!","Allora sparisci, prima che cambi idea."),RandPhraseSimple("In tal caso non ti ritardo più!","Allora è meglio che te ne vada prima che cambi idea."));
		link.l1 = "Sto già andando via...";
		link.l1.go = "peace";
		break;

	case "after_peace":
		Dialog.Text = NPCharRepPhrase(NPChar,RandSwear()+RandPhraseSimple("Vattene!","Sparisci dalla mia vista, prima che cambi idea."),RandPhraseSimple("Posso aiutarti?","Vuoi qualcosa?"));
		link.l1 = "Me ne sto andando.";
		link.l1.go = "peace";
		break;

	//мир и все такое.
	case "peace":
		LAi_SetWarriorType(NPChar);
		NextDiag.CurrentNode = "after_peace";
		DialogExit();
		break;
	}
}
