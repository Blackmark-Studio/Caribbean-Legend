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
		Dialog.Text = NPCharRepPhrase(NPChar,RandSwear()+RandPhraseSimple("Comment oses-tu m'insulter, vaurien?!","Ces mots te coûteront cher !"),RandPhraseSimple("Vous avez insulté mon honneur, "+GetAddress_Form(NPChar)+"! Et tu paieras pour ça.","Comment osez-vous? Reprenez vos paroles immediatement!"));

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
		Dialog.Text = NPCharRepPhrase(NPChar,RandPhraseSimple("Je vais te couper les oreilles !","Je vais t'arracher le coeur !"),RandPhraseSimple("J'espère que j'entendrai vos excuses ou je ne peux pas garantir que je me contrôlerai !","Réalisez-vous ce que cela signifie... le faites-vous?"));

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
		if (CheckAttribute(PChar, "questTemp.duel.Start") && int(PChar.questTemp.duel.Start))
		{
			Dialog.Text = "D'abord, tu règles tes affaires avec les autres, puis nous parlerons.";
			if (PChar.questTemp.duel.enemy == NPChar.id)
			{
				Dialog.Text = "Nous avons déjà conclu un accord.";
			}
			link.l1 = RandSwear()+"Oh, comment pourrais-je oublier...";
			link.l1.go = "exit";
			break
		}
		//может отказаться.
		if (rand(100) < 30)
		{
			Dialog.Text = RandPhraseSimple("Duel?! Dégage, tu ne vaux pas la peine de perdre du temps avec toi.","Duel? Tu ne mérites pas cet honneur! Dégage!");
			link.l1 = RandPhraseSimple("D'accord...","Je suppose que je peux attendre...");
			link.l1.go = "exit";
/**/
			//можно дать возможность драться полюбому :)			
			if (rand(100) < 30)
			{
				link.l1 = RandPhraseSimple("Penses-tu donc? Ne sois pas si sûr, bâtard!!!","Ah vraiment ?! Je vais voir de quelle couleur est ton sang !");
				link.l1.go = "fight_right_now";
			}
/**/
			break;
		}

		//согласен.
		Dialog.Text = RandPhraseSimple("Le duel, dites-vous ? Cela me convient. Les épées et les pistolets seront nos armes.","Peux-tu même tenir une épée?");
		link.l1 = RandPhraseSimple("Tu supplieras pour la miséricorde, à genoux.","Je vais t'étrangler avec mes mains nues, espèce de vaurien!");
		link.l1.go = "land_duel";
		if (int(pchar.Ship.Type) != SHIP_NOTUSED && int(NPChar.Ship.Type) != SHIP_NOTUSED)
		{
			Dialog.Text = RandPhraseSimple(Dialog.Text+" Ou nous pouvons prendre le large et voir qui est qui!","Le duel ?!! Ha, je vais t'écraser comme un insecte ! Choisis comment tu veux mourir !");
			link.l2 = RandPhraseSimple("En mer, je suis le meilleur là-bas.","Mon navire coulera facilement votre vieille baignoire!");
			link.l2.go = "sea_duel";
		}
		link.l3 = "J'ai changé d'avis...";
		link.l3.go = "change_mind";
		break;

	//дуэль на подводных лодках :))))
	case "sea_duel":
		Dialog.Text = RandPhraseSimple("Je ne vois pas votre navire dans le port...","Dégage jusqu'à ce que tu trouves une vieille baignoire pourrie au moins !");
		link.l1 = RandPhraseSimple("Ma faute...","Alors je te quitte.");
		link.l1.go = "exit";
		if (pchar.location.from_sea == GetCurrentTown() + "_town")
		{
			Dialog.Text = "D'accord, je t'attendrai à la sortie de la crique...";
			link.l1 = "Je ne vous ferai pas attendre trop longtemps.";

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
//			iHour = int(18.0 - GetTime()) + rand(2); //раскоментировать для дуэлей только по ночам
		}
		pchar.questTemp.Duel.WaitTime = iHour;
		Dialog.Text = RandSwear()+RandPhraseSimple("Dégage ton acier, et voyons de quelle couleur est ton sang !","Eh bien, si tu as un désir de mort...");
		link.l1 = RandPhraseSimple("Nous ferions mieux d'aller quelque part sans trop de témoins. Je connais justement l'endroit parfait passé les portes de la ville. Retrouvons-nous là-bas dans "+iHour+" heures.","Retenez vos chevaux. De telles choses sont mieux réglées sans témoins. Entrez "+iHour+"  heures à l'entrée de la ville.");
		link.l1.go = "fight_off_town";
		link.l2 = RandPhraseSimple("Eh bien, si tu veux tant mourir...","Maudite soit! Je vais t'aider à voir l'Enfer de tes propres yeux!");
		link.l2.go = "fight_right_now";
		link.l3 = "J'ai changé d'avis...";
		link.l3.go = "change_mind";

		if (rand(1))
		{
			Dialog.Text = RandSwear()+RandPhraseSimple("Je pense qu'il vaudrait mieux passer par les portes de la ville. Je t'attendrai là-bas dans "+pchar.questTemp.Duel.WaitTime+" heures. Ne tardez pas !","Ce n'est pas le meilleur endroit pour régler des différends. Nous ferions mieux de sortir de la ville. En "+pchar.questTemp.Duel.WaitTime+" heures je serai là.");
			link.l1 = RandPhraseSimple("Tu ne mérites pas cet honneur ! Défends-toi !","Je n'ai pas de temps! Dégaîne l'acier!");
			link.l1.go = "fight_right_now";
			link.l2 = RandPhraseSimple("D'accord, allons faire une promenade.","Tu as probablement raison. Rencontrons-nous après les portes.");
			link.l2.go = "fight_off_town_prep";
		}
		break;

	//предложение "пойдём выйдем" рассматривается
	case "fight_off_town":
		Dialog.Text = RandPhraseSimple("Tu ne mérites pas cet honneur! Défends-toi!","Je n'ai pas de temps! Juste ici et maintenant!");
		link.l1 = RandPhraseSimple("Eh bien, si tu veux tant mourir...","Maudits! Je t'aiderai à voir l'Enfer de tes propres yeux!");
		link.l1.go = "fight_right_now";
		if (rand(1))
		{
			Dialog.Text = RandPhraseSimple("D'accord, faisons une promenade.","Vous avez probablement raison. Retrouvons-nous après les portes.");
			link.l1 = RandPhraseSimple("Je t'attendrai là-bas.","Ne tarde pas.");
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
			SetTimerConditionParam("duel_move_opponentBack", "Duel_Move_OpponentBack", 0, 0, 0, int(GetTime() + 0.5) + int(pchar.questTemp.Duel.WaitTime) + 1, false);
			pchar.quest.duel_move_opponentBack.function = "Duel_Move_OpponentBack";
			if (CheckAttribute(NPChar, "CityType"))
			{
				DeleteAttribute(NPChar, "City"); // чтоб не было ругани с нацией
	    		DeleteAttribute(NPChar, "CityType");
				if (!CheckAttribute(NPChar, "PGGAi")) 
				{
					if (!CheckAttribute(NPChar, "LifeDay")) npchar.LifeDay = 0;
					npchar.LifeDay = int(npchar.LifeDay) + 3; // чтоб до дуэли не помер
				}
    		}
		}
		NextDiag.CurrentNode = "let_s_duel";
		DialogExit();
		break;

	//последнее слово перед боем
	case "talk_off_town":
		Dialog.Text = "Alors, êtes-vous prêt?";
		link.l1 = "Ouais. Voyons voir qui est le meilleur homme !";
		link.l1.go = "fight_right_now";
		link.l2 = "Non, j'ai décidé de vous apporter les excuses. J'avais tort, je me suis enflammé.";
		link.l2.go = "change_mind";
		if (rand(100) < 20)
		{
			Dialog.Text = RandPhraseSimple("Écoute, j'ai réfléchi et je vois maintenant que j'avais tort. Mes excuses.","Nom de Dieu! C'est à cause de ce foutu rhum!!! Mes excuses, "+GetSexPhrase("frère","sœur")+"!");
			link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("Non, seul ton sang peut me donner satisfaction maintenant !","Dégaîne ton épée et arrête d'être une telle pleurnicheuse!"),RandPhraseSimple("Non! Je demande satisfaction!","Tu es une honte pour ta famille! Dégaîne ton épée!"));
			link.l1.go = "fight_right_now";
			link.l2 = NPCharRepPhrase(pchar,RandPhraseSimple("D'accord, je suis d'accord. Nous nous sommes un peu échauffés.","Qui compte les points entre amis !"),RandPhraseSimple("Tu as probablement raison. Nous ne devrions pas verser du sang pour des choses si mesquines.","Ma générosité ne connaît pas de limites! Tu es pardonné!"));
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
		Dialog.Text = NPCharRepPhrase(NPChar,RandSwear()+RandPhraseSimple("Alors va-t'en !","Perds-toi alors, avant que je change d'avis."),RandPhraseSimple("Dans ce cas, je ne vous retiens plus !","Alors tu ferais mieux de partir avant que je ne change d'avis."));
		link.l1 = "Je m'en vais déjà...";
		link.l1.go = "peace";
		break;

	case "after_peace":
		Dialog.Text = NPCharRepPhrase(NPChar,RandSwear()+RandPhraseSimple("Dégage !","Disparais de ma vue, avant que je ne change d'avis."),RandPhraseSimple("Puis-je vous aider?","Voulez-vous quelque chose?"));
		link.l1 = "Je m'en vais.";
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
