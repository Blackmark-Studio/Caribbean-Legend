// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Que voulez-vous ? Demandez, je vous prie.","Je vous écoute, quelle est la question ?"),"C'est la deuxième fois que vous essayez de demander...","C'est la troisième fois que vous essayez de demander...","Quand cela va-t-il finir ?! Je suis un homme occupé, travaillant sur les affaires de la colonie et vous me dérangez encore !","bloc",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("J'ai changé d'avis...","Pas maintenant. Mauvais endroit et mauvais moment."),"Vrai... Mais plus tard, pas maintenant...","Je demanderai... Mais un peu plus tard...","Je suis désolé, "+GetAddress_FormToNPC(NPChar)+"...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "silk_8")
			{
				link.l1 = "Votre Excellence, je voudrais signaler une activité commerciale illégale sur cette île.";
                link.l1.go = "Mtraxx";
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "silk_12")
			{
				link.l1 = "Je souhaiterais entendre un rapport sur votre mission concernant la contrebande de voiles en soie.";
                link.l1.go = "Mtraxx_4";
			}
			// Jason НСО
			if (CheckAttribute(pchar, "questTemp.Patria") && pchar.questTemp.Patria == "epizode_10_continue" && !CheckAttribute(npchar, "quest.slaveships"))
			{
				link.l1 = "Je suis arrivé de la part du Gouverneur Général Phillipe de Poincy. Mon travail est de vous amener les esclaves capturés aux Néerlandais, c'est bien cela ?";
                link.l1.go = "patria_Sl";
			}
			if (CheckAttribute(npchar, "quest.slaveships.wait") && GetSquadronGoods(pchar, GOOD_SLAVES) >= 3000)
			{
				link.l1 = "Je vous ai amené les esclaves, comme convenu.";
                link.l1.go = "patria_Sl_2";
			}
			if (CheckAttribute(pchar, "questTemp.Patria") && pchar.questTemp.Patria == "epizode_11_start" && CheckAttribute(pchar, "questTemp.Patria.Curacao.DoilyReady"))
			{
				link.l1 = "Je suis arrivé sur les instructions du Gouverneur Général Phillipe de Poincy pour participer à une expédition conjointe à Curaçao contre les Hollandais.";
                link.l1.go = "patria_Sl_4";
			}
			if (CheckAttribute(pchar, "questTemp.Patria") && pchar.questTemp.Patria == "epizode_11_wait" && GetCompanionQuantity(pchar) < 3)
			{
				link.l1 = "Mon escadron a été diminué, nous pouvons partir maintenant.";
                link.l1.go = "patria_Sl_6";
			}
		break;
		
		// Addon 2016-1 Jason пиратская линейка
		case "Mtraxx":
            dialog.text = "Intéressant. Je suis tout ouïe.";
			link.l1 = "J'ai de bonnes sources qui me disent qu'une brigantine hollandaise, le 'Utrecht', sous pavillon anglais, décharge de grandes quantités de toile de voile en soie dans la baie de Portland depuis longtemps. Ils opèrent depuis plus d'un an, pendant la nuit, entre le 10 et le 15 de chaque mois.";
			link.l1.go = "Mtraxx_1";
		break;
		
		case "Mtraxx_1":
            dialog.text = "Es-tu sûr que ta source est fiable ?";
			link.l1 = "Parfois, je ne me fais même pas confiance, cependant, un homme qui a divulgué cette information est fiable. De plus, il n'avait aucune raison de mentir.";
			link.l1.go = "Mtraxx_2";
		break;
		
		case "Mtraxx_2":
			string sTemp = "this";
			if (int(pchar.questTemp.Mtraxx.month == 1)) sTemp = "next";
            dialog.text = "Très bien, capitaine. C'est une affaire sérieuse et je dois agir sur les informations présentées, même si votre informateur a menti ou s'est simplement trompé. J'enverrai une patrouille côtière à l'heure spécifiée, et si vos informations sont confirmées, vous serez généreusement récompensé, de telles activités illégales doivent être sévèrement réprimées.";
			link.l1 = "Je te verrai "+sTemp+" mois le 16. La situation se résoudra sûrement d'elle-même d'ici là.";
			link.l1.go = "Mtraxx_3";
		break;
		
		case "Mtraxx_3":
            DialogExit();
			pchar.questTemp.Mtraxx = "silk_11";
			int month = int(pchar.questTemp.Mtraxx.month);
			pchar.quest.mtr_silk_smuggler.over = "yes";
			pchar.quest.mtr_silk_smuggler_over.over = "yes";
			DeleteQuestCondition("Mtraxx_SilkCreateSmuggler");
			DeleteQuestCondition("Mtraxx_SilkSmugglerFail");
			pchar.quest.mtr_silk_smuggler_patrol.win_condition.l1 = "Timer";
			pchar.quest.mtr_silk_smuggler_patrol.win_condition.l1.date.hour  = 6;
			pchar.quest.mtr_silk_smuggler_patrol.win_condition.l1.date.day   = 16;
			pchar.quest.mtr_silk_smuggler_patrol.win_condition.l1.date.month = GetAddingDataMonth(0, month, 0);
			pchar.quest.mtr_silk_smuggler_patrol.win_condition.l1.date.year  = GetAddingDataYear(0, month, 0);
			pchar.quest.mtr_silk_smuggler_patrol.function = "Mtraxx_SilkSmugglerPatrol";
			sTemp = "this";
			if (int(pchar.questTemp.Mtraxx.month == 1)) sTemp = "next";
			AddQuestRecord("Roger_2", "19");
			AddQuestUserData("Roger_2", "sDate", sTemp);
			if (CharacterIsAlive("Mtr_Utreht"))
			{
				sld = CharacterFromID("Mtr_Utreht");
				sld.lifeday = 0;
			}
		break;
		
		case "Mtraxx_4":
            dialog.text = "Vos informations se sont avérées correctes, capitaine. Nous avons tendu une embuscade aux criminels pendant la transaction. L''Utrecht' a tenté de s'échapper et a combattu, mais a été coulé par notre corvette de patrouille. Quatre acheteurs ont résisté à l'arrestation. L'un a été tué d'une balle, et les trois autres se sont enfuis dans la jungle. La cargaison complète de 80 rouleaux de soie a été transférée au trésor de Port Royal. Bien que nous ayons échoué à identifier le chef de ce réseau, l'homme mort est non identifié, et les autres ont fui, je déclare cette opération un succès complet. Je doute que ces vauriens osent jamais revenir ici.\nVous nous avez rendu un grand service, capitaine, en étant diligent et en signalant les escrocs. Voici 10.000 pesos pour votre récompense.";
			link.l1 = "Très obligé, Votre Excellence. Je suis heureux de voir que tout s'est déroulé comme prévu et que les contrebandiers ont eu ce qu'ils méritaient. Sur ce, je vous laisse, passez une bonne journée.";
			link.l1.go = "Mtraxx_5";
		break;
		
		case "Mtraxx_5":
            DialogExit();
			pchar.questTemp.Mtraxx = "silk_13";
			AddQuestRecord("Roger_2", "20");
			AddMoneyToCharacter(pchar, 10000);
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
			ChangeCharacterNationReputation(pchar, ENGLAND, 5);
			AddCharacterExpToSkill(pchar, "Leadership", 200);
		break;
		
		// Jason НСО
		case "patria_Sl":
			if (GetSquadronGoods(pchar, GOOD_SLAVES) < 500)
			{
				dialog.text = "C'est exact. Combien d'esclaves as-tu apporté ?";
				link.l1 = "Je travaille toujours dessus. Je reviendrai bientôt avec les résultats.";
				link.l1.go = "patria_Sl_wait";
				break;
			}
			dialog.text = "C'est exact. Combien d'esclaves as-tu amené ?";
			link.l1 = ""+FindRussianQtyString(GetSquadronGoods(pchar,GOOD_SLAVES))+".";
			if (GetSquadronGoods(pchar, GOOD_SLAVES) >= 3000) link.l1.go = "patria_Sl_2";
			else link.l1.go = "patria_Sl_1";
		break;
		
		case "patria_Sl_wait":
			DialogExit();
			npchar.quest.slaveships.wait = "true";
		break;
		
		case "patria_Sl_1":
			dialog.text = "Hum, le Chevalier avait promis qu'il y aurait pas moins de 3000 esclaves";
			link.l1 = "C'est exact. C'est ma faute : certains des esclaves ont été tués sous le feu de canon d'un navire ennemi, d'autres sont morts en chemin. Je corrigerai mon erreur et reviendrai vers vous. Tout sera fait selon le contrat.";
			link.l1.go = "patria_Sl_wait";
		break;
		
		case "patria_Sl_2":
			DeleteAttribute(npchar, "quest.slaveships.wait");
			dialog.text = "Excellent ! Avec le Chevalier de Poincy, on peut vraiment faire des affaires. Dites au Gouverneur général que mon escadre pour l'attaque de Curaçao sera prête dans un mois. Je suis sûr qu'il vous enverra pour cette campagne à moi, donc je vous verrai bientôt, Monsieur de Maure.";
			link.l1 = "Je serais ravi de vous revoir, Colonel. Et maintenant, permettez-moi de vous faire mes adieux.";
			link.l1.go = "patria_Sl_3";
		break;
		
		case "patria_Sl_3":
			DialogExit();
			npchar.quest.slaveships = "true";
			RemoveCharacterGoods(pchar, GOOD_SLAVES, GetSquadronGoods(pchar, GOOD_SLAVES));
			AddQuestRecord("Patria", "57");
			pchar.questTemp.Patria = "epizode_10_return";
			pchar.quest.Patria_SlaveShipsJamaicaTimeOver.over = "yes"; //снять таймер на доставку рабов
			SetFunctionTimerCondition("Patria_CuracaoDoilyReady", 0, 0, 30, false); // таймер на 1 месяц на готовность эскадры д'Ойли
			SetFunctionTimerCondition("Patria_CuracaoTimeOver", 0, 0, 62, false); // таймер на 2 месяца на туда-обратно к Пуанси
			SaveCurrentQuestDateParam("questTemp.Patria.Curacao.Date"); // запоминаем дату
			// меняем отношение наций
			pchar.questTemp.Patria.Friend = "true";
			LaunchNationLegend();
			DeleteAttribute(pchar, "questTemp.Patria.Friend");
			DoQuestCheckDelay("sea_victory", 0.2);
		break;
		
		case "patria_Sl_4":
			dialog.text = "Je ne doutais pas que ce serait vous. Encore mieux ! Notre escadre est prête. Un vaisseau de 1er rang et deux navires de 4e rang. La taille maximale de l'ensemble de l'escadre ne doit pas dépasser cinq navires.";
			if (GetCompanionQuantity(pchar) > 2)
			{
				link.l1 = "Alors je laisserai les navires supplémentaires au port et je ne garderai que deux. Nous aurons cinq navires au total.";
				link.l1.go = "patria_Sl_5";
			}
			else
			{
				link.l1 = "Oui, exactement cinq, pas plus. Nous devrions partir.";
				link.l1.go = "patria_Sl_6";
			}
		break;
		
		case "patria_Sl_5":
			DialogExit();
			pchar.questTemp.Patria = "epizode_11_wait";
		break;
		
		case "patria_Sl_6":
			dialog.text = "Parfait. Maintenant, je vais vous expliquer le plan selon lequel nous allons agir : peut-être voudrez-vous changer quelque chose ou ajouter quelque chose, alors nous en discuterons.";
			link.l1 = "Je suis tout ouïe, colonel.";
			link.l1.go = "patria_Sl_7";
		break;
		
		case "patria_Sl_7":
			dialog.text = "Il n'est pas utile de capturer Curaçao : c'est la principale colonie néerlandaise de l'archipel, et même si nous capturons leur drapeau dans le fort de Willemstad et hissons un drapeau anglais ou français, il sera très difficile de conserver l'île. Les Néerlandais feront tout pour la récupérer et la cibler avec des escadrons militaires. En général, il n'y a pas de raison de la capturer puisqu'il n'est pas obligatoire. Plus important pour nous est de forcer Steivesant à signer le traité à des conditions qui nous sont bénéfiques, et pour cela il suffira de détruire les principales défenses ennemies et de mettre les Néerlandais sous la menace de la destruction complète de la colonie de Willemstad.";
			link.l1 = "De quoi traitera le traité ?";
			link.l1.go = "patria_Sl_8";
		break;
		
		case "patria_Sl_8":
			dialog.text = "Le traité a été rédigé par moi et le Chevalier de Poincy. Il concerne divers aspects du commerce, la fin de la 'guerre commerciale' entre la Compagnie et l'Angleterre, le refus des revendications de Stuyvesant sur l'île de Sint Maarten et d'autres points politiques qui vous intéressent peu.";
			link.l1 = "Compris.";
			link.l1.go = "patria_Sl_9";
		break;
		
		case "patria_Sl_9":
			dialog.text = "Voici le plan : d'abord, avec toutes nos forces, nous attaquerons le fort et le détruirons. Les Néerlandais s'attendront à un débarquement de troupes, mais nous ne le ferons pas, les plus grandes pertes sont généralement subies lors de la prise d'un bastion depuis la mer. Au lieu de cela, nous débarquerons des équipes d'assaut à deux endroits sur l'île : au cap Santa Maria et à la lagune de Blanca, et nous avancerons par voie terrestre jusqu'à la porte de la ville de Willemstad. J'ai ordonné d'emporter de l'artillerie de campagne avec nous sur les navires - il n'y a pas de broussailles difficiles d'accès à Curaçao, et nous pourrons rouler les canons sur roues le long du sol sans aucune difficulté.\nTandis que les Néerlandais seront perplexes quant à ce qui se passe, nous prendrons la ville sous la vue de la jungle et bloquerons toute opportunité d'envoyer des renforts du fort par voie terrestre. Après cela, nous placerons la ville sous le feu des canons. Assurément, la garnison du fort tentera d'attaquer, mais ils ne pourront rien contre les canons de campagne et nos mousquetaires, et si leurs canons maintenus dans le fort sont encore fonctionnels, ils ne pourront pas les amener dans la jungle.\nDe plus, nos navires simuleront des préparatifs de débarquement de troupes depuis la mer pour effrayer les ennemis et abaisser leur moral. Après un certain temps, lorsque les Néerlandais seront pleinement conscients de leur situation désespérée, nous convoquerons les parlementaires pour des négociations. Qu'en pensez-vous, capitaine?";
			link.l1 = "Plan brillant ! Et le meilleur, c'est que nous ne perdrons aucun soldat près des murs du fort.";
			link.l1.go = "patria_Sl_10";
		break;
		
		case "patria_Sl_10":
			dialog.text = "Je suis heureux que vous ayez aimé mes idées. Allons-y alors !";
			link.l1 = "Allons-y !";
			link.l1.go = "patria_Sl_11";
		break;
		
		case "patria_Sl_11":
			DialogExit();
			chrDisableReloadToLocation = true;
			pchar.questTemp.Patria = "epizode_11_continue";
			AddQuestRecord("Patria", "60");
			pchar.quest.Patria_CuracaoTimeOver.over = "yes"; // снять таймер 2 месяца
			LAi_SetActorType(npchar);
			ChangeCharacterAddressGroup(npchar, "PortRoyal_townhall", "goto", "goto4");
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 7.0);
			Patria_CuracaoSail();
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
