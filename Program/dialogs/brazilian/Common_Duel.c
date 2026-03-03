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
		Dialog.Text = NPCharRepPhrase(NPChar,RandSwear()+RandPhraseSimple("Como você ousa me insultar, seu canalha?!","Essas palavras vão te custar caro!"),RandPhraseSimple("Você insultou minha honra, "+GetAddress_Form(NPChar)+"! E você vai pagar por isso.","Como você ousa? Retire o que disse imediatamente!"));

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
		Dialog.Text = NPCharRepPhrase(NPChar,RandPhraseSimple("Vou cortar suas orelhas fora!","Vou arrancar seu coração!"),RandPhraseSimple("Espero ouvir suas desculpas, ou não posso garantir que vou me controlar!","Você tem ideia do que isso significa... tem?"));

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
			Dialog.Text = "Primeiro, resolva seus assuntos com os outros, e depois conversamos.";
			if (PChar.questTemp.duel.enemy == NPChar.id)
			{
				Dialog.Text = "Já chegamos a um acordo.";
			}
			link.l1 = RandSwear()+"Ah, como eu poderia esquecer...";
			link.l1.go = "exit";
			break
		}
		//может отказаться.
		if (rand(100) < 30)
		{
			Dialog.Text = RandPhraseSimple("Duelo?! Cai fora, você não vale o meu tempo.","Duelo? Você não merece essa honra! Cai fora!");
			link.l1 = RandPhraseSimple("Certo...","Acho que posso esperar...");
			link.l1.go = "exit";
/**/
			//можно дать возможность драться полюбому :)			
			if (rand(100) < 30)
			{
				link.l1 = RandPhraseSimple("Você acha mesmo? Não tenha tanta certeza, seu desgraçado!!!","Ah é mesmo?! Vou ver de que cor é o seu sangue!");
				link.l1.go = "fight_right_now";
			}
/**/
			break;
		}

		//согласен.
		Dialog.Text = RandPhraseSimple("O duelo, você diz? Por mim tudo bem. Espadas e pistolas serão nossas armas.","Você ao menos sabe segurar uma espada?");
		link.l1 = RandPhraseSimple("Você vai implorar por misericórdia, de joelhos.","Eu vou te estrangular com as minhas próprias mãos, seu canalha!");
		link.l1.go = "land_duel";
		if (sti(pchar.Ship.Type) != SHIP_NOTUSED && sti(NPChar.Ship.Type) != SHIP_NOTUSED)
		{
			Dialog.Text = RandPhraseSimple(Dialog.Text+" Ou então podemos zarpar e descobrir quem é quem!","O duelo?!! Ha, vou te esmagar como um inseto! Escolha como quer morrer!");
			link.l2 = RandPhraseSimple("No mar, eu sou o melhor que existe por aí.","Meu navio vai afundar seu barco velho com facilidade!");
			link.l2.go = "sea_duel";
		}
		link.l3 = "Mudei de ideia...";
		link.l3.go = "change_mind";
		break;

	//дуэль на подводных лодках :))))
	case "sea_duel":
		Dialog.Text = RandPhraseSimple("Não vejo seu navio no porto...","Vá embora até encontrar pelo menos uma velha canoa caindo aos pedaços!");
		link.l1 = RandPhraseSimple("Foi meu erro...","Então eu estou te deixando.");
		link.l1.go = "exit";
		if (pchar.location.from_sea == GetCurrentTown() + "_town")
		{
			Dialog.Text = "Certo, vou te esperar na saída da enseada...";
			link.l1 = "Não vou te fazer esperar muito.";

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
		Dialog.Text = RandSwear()+RandPhraseSimple("Saque sua lâmina e vamos ver de que cor é o seu sangue!","Bem, se você está com vontade de morrer...");
		link.l1 = RandPhraseSimple("É melhor irmos para um lugar onde não haja muitas testemunhas. Conheço um lugar perfeito além dos portões da cidade. Vamos nos encontrar lá em "+iHour+" horas.","Calma aí. Essas coisas se resolvem melhor sem testemunhas. Entre "+iHour+"  horas até os portões da cidade.");
		link.l1.go = "fight_off_town";
		link.l2 = RandPhraseSimple("Bem, se você quer morrer tanto assim...","Droga! Vou te ajudar a enxergar o Inferno com os próprios olhos!");
		link.l2.go = "fight_right_now";
		link.l3 = "Mudei de ideia...";
		link.l3.go = "change_mind";

		if (rand(1))
		{
			Dialog.Text = RandSwear()+RandPhraseSimple("Acho melhor a gente passar pelos portões da cidade. Vou te esperar lá em "+pchar.questTemp.Duel.WaitTime+" horas. Não demore!","Este não é o melhor lugar para resolver disputas. É melhor sairmos da cidade. Em "+pchar.questTemp.Duel.WaitTime+" horas eu estarei lá.");
			link.l1 = RandPhraseSimple("Você não merece essa honra! Defenda-se!","Não tenho tempo! Saque sua espada!");
			link.l1.go = "fight_right_now";
			link.l2 = RandPhraseSimple("Certo, vamos dar uma volta.","Provavelmente você está certo. Vamos nos encontrar depois dos portões.");
			link.l2.go = "fight_off_town_prep";
		}
		break;

	//предложение "пойдём выйдем" рассматривается
	case "fight_off_town":
		Dialog.Text = RandPhraseSimple("Você não merece essa honra! Defenda-se!","Não tenho tempo! Aqui e agora!");
		link.l1 = RandPhraseSimple("Bem, se você quer morrer tanto assim...","Droga! Vou te ajudar a enxergar o Inferno com os próprios olhos!");
		link.l1.go = "fight_right_now";
		if (rand(1))
		{
			Dialog.Text = RandPhraseSimple("Certo, vamos dar uma volta.","Você provavelmente está certo. Vamos nos encontrar depois dos portões.");
			link.l1 = RandPhraseSimple("Vou te esperar lá.","Não demore.");
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
		Dialog.Text = "Então, está pronto?";
		link.l1 = "É. Vamos ver quem é o melhor homem!";
		link.l1.go = "fight_right_now";
		link.l2 = "Não, decidi vir aqui pedir desculpas a você. Eu estava errado, me exaltei.";
		link.l2.go = "change_mind";
		if (rand(100) < 20)
		{
			Dialog.Text = RandPhraseSimple("Ei, escuta, estive pensando e agora vejo que estava errado. Me desculpe.","Maldição! É tudo culpa desse maldito rum!!! Me desculpe, "+GetSexPhrase("irmão","irmã")+"!");
			link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("Não, só o seu sangue pode me satisfazer agora!","Saque sua espada e pare de choramingar!"),RandPhraseSimple("Não! Exijo satisfação!","Você é uma vergonha para sua família! Saque sua espada!"));
			link.l1.go = "fight_right_now";
			link.l2 = NPCharRepPhrase(pchar,RandPhraseSimple("Certo, eu concordo. A gente se exaltou um pouco.","Quem se importa com pontos entre amigos!"),RandPhraseSimple("Você provavelmente está certo. Não devemos derramar sangue por coisas tão pequenas.","Minha generosidade não tem limites! Você está perdoado!"));
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
		Dialog.Text = NPCharRepPhrase(NPChar,RandSwear()+RandPhraseSimple("Então cai fora!","Então suma daqui, antes que eu mude de ideia."),RandPhraseSimple("Nesse caso, não vou te atrasar mais!","Então é melhor você ir embora antes que eu mude de ideia."));
		link.l1 = "Já estou indo...";
		link.l1.go = "peace";
		break;

	case "after_peace":
		Dialog.Text = NPCharRepPhrase(NPChar,RandSwear()+RandPhraseSimple("Cai fora!","Desapareça da minha frente, antes que eu mude de ideia."),RandPhraseSimple("Posso te ajudar?","Você quer alguma coisa?"));
		link.l1 = "Estou indo embora.";
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
