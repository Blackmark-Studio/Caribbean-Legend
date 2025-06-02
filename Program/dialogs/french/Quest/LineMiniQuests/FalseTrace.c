void ProcessDialogEvent()
{
	ref sld, NPChar;
	aref Link, NextDiag;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Bug. Faites-le nous savoir.";
			link.l1 = "Bien sûr !";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "FalseTrace":
			DelMapQuestMarkCity(pchar.questTemp.FalseTrace.StartCity);
			dialog.text = "Bon après-midi, capitaine... ehm... kha-hahrm ! Foutues mines... Permettez-moi de me présenter. Adam Rayner. Je suis un homme simple et je n'aime pas les longs préambules, alors je vais cracher le morceau tout de suite. Voulez-vous gagner beaucoup d'argent ? Je vous propose une petite affaire que nous ne pourrons pas gérer seuls.";
			link.l1 = "Heh! Bon argent? Intéressant. Je t'écoute, Adam.";
			link.l1.go = "FalseTrace_1";
			link.l2 = "Vous savez, je suis désolé, mais vous ne me semblez pas digne de confiance. Donc je ne ferai pas affaire avec vous.";
			link.l2.go = "FalseTrace_exit";
		break;
		
		case "FalseTrace_exit":
			dialog.text = "Fiable ? Ha-ha ! On ne doit pas juger un homme à sa mine. Bon, peu importe. Vous venez de rater une bonne occasion de gagner de l'argent facilement et rapidement. Je trouverai quelqu'un de plus coopératif...";
			link.l1 = "Notre conversation est terminée, monsieur. Adieu !";
			link.l1.go = "FalseTrace_exit_1";
		break;
		
		case "FalseTrace_exit_1":
			DialogExit();
			DelLandQuestMark(npchar);
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
			DeleteAttribute(pchar, "questTemp.FalseTrace");
		break;
		
		case "FalseTrace_1":
			//выбираем целевой пункт
			switch (hrand(2))
			{
				case 0: 
					pchar.questTemp.FalseTrace.DayQty = 18;
					pchar.questTemp.FalseTrace.TargetCity = "Beliz";
					pchar.questTemp.FalseTrace.TargetShore = "Shore8";
				break;
				case 1: 
					pchar.questTemp.FalseTrace.DayQty = 22;
					pchar.questTemp.FalseTrace.TargetCity = "Marigo";
					pchar.questTemp.FalseTrace.TargetShore = "Shore41";
				break;
				case 2: 
					pchar.questTemp.FalseTrace.DayQty = 20;
					pchar.questTemp.FalseTrace.TargetCity = "Santodomingo";
					pchar.questTemp.FalseTrace.TargetShore = "Mayak8";
				break;
			}
			pchar.questTemp.FalseTrace.ShipName = GenerateRandomNameToShip(sti(npchar.nation));
			pchar.questTemp.FalseTrace.Mation = sti(npchar.nation);
			dialog.text = "Kha ! C'est un plaisir de faire affaire avec un esprit aussi vif que le vôtre, Capitaine. Alors, le travail est simple : il y a un flûte rempli d'une belle quantité d'argent et il va bientôt quitter l'un des ports locaux. Un seul navire, sans escorte. Ridicule, n'est-ce pas ? K-kha\n Aussi simple que bonjour. Je vous dis où et quand, vous prenez le butin et je reçois ma part.";
			link.l1 = "Et bien sûr, tu veux le recevoir en espèces immédiatement ?";
			link.l1.go = "FalseTrace_2";
		break;
		
		case "FalseTrace_2":
			dialog.text = "Est-ce que j'ai l'air d'un misérable vaurien, capitaine ? Pas question. Je me joindrai à vous dans ce raid et nous le ferons ensemble. Je ne resterai pas dans la cale pendant le combat, bien au contraire - je vous demande de me mettre dans l'équipe d'abordage en tant qu'officier, temporairement, bien sûr.\nJe connais mon métier, je sais comment poignarder et tirer sur les gens. Alors je risquerai ma peau tout comme vous... khe... kha ! Vous me paierez ma part après que nous aurons capturé le flûte.";
			link.l1 = "Quelle part du butin réclames-tu pour toi-même ?";
			link.l1.go = "FalseTrace_3";
		break;
		
		case "FalseTrace_3":
			dialog.text = "Je ne suis pas un homme avide, capitaine. Ma part est autant que l'on peut charger dans la cale de ma vieille chaloupe et cela représente environ 200 paquets d'argent. Selon mes informations, il y aura pas moins de 2000 paquets d'argent sur le flûte, donc j'obtiendrai la dixième partie. C'est juste, n'est-ce pas ?";
			link.l1 = "Un dixième du butin juste pour des informations ? J'achete de telles informations aux ivrognes pour un verre de rhum dans une taverne locale. Non, nous n'allons pas dans la même direction, ami !";
			link.l1.go = "FalseTrace_4";
			link.l2 = "Hm. Je suppose que je suis d'accord. J'accepte ton offre, Adam. Bienvenue à bord. Maintenant, à propos de ton information : d'où, vers où, heure, nom du navire ?";
			link.l2.go = "FalseTrace_5";
		break;
		
		case "FalseTrace_4":
			dialog.text = "Quel avare tu es, Capitaine ! Dans ce cas, tu n'auras que des clous ! A plus !";
			link.l1 = "Bonne chance ! Trouve un autre simplet pour ton entreprise louche !";
			link.l1.go = "FalseTrace_exit_1";
		break;
		
		case "FalseTrace_5":
			dialog.text = "Le nom du flûte est le "+pchar.questTemp.FalseTrace.ShipName+", elle quitte Carthagene et navigue "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.TargetCity)+"  Nous n'avons pas beaucoup de temps, pourtant. Deux semaines, trois tout au plus. Si nous ne la trouvons pas en trois semaines, c'est fini. ";
			link.l1 = "N'attendons pas plus longtemps, alors ! L'aventure nous appelle !";
			link.l1.go = "FalseTrace_6";
		break;
		
		case "FalseTrace_6":
			DialogExit();
			NextDiag.CurrentNode = "FalseTrace_officer";
			DelLandQuestMark(npchar);
			ChangeCharacterAddressGroup(npchar, pchar.location, "goto", "goto1");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			AddPassenger(pchar, npchar, false);
			AddQuestRecord("FalseTrace", "1");
			AddQuestUserData("FalseTrace", "sCity1", XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.StartCity+"Gen"));
			AddQuestUserData("FalseTrace", "sCity2", XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.TargetCity));
			AddQuestUserData("FalseTrace", "sShip", pchar.questTemp.FalseTrace.ShipName);
			//установим таймер на генерацию энкаунтера
			pchar.quest.False_Trace_2.win_condition.l1 = "Timer";
			pchar.quest.False_Trace_2.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.False_Trace_2.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 2);
			pchar.quest.False_Trace_2.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 2);
			pchar.quest.False_Trace_2.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 2);
			pchar.quest.False_Trace_2.function = "CreateFalseTraceGaleonOnMap";
			SetFunctionTimerCondition("FalseTraceGaleonOver", 0, 0, sti(pchar.questTemp.FalseTrace.DayQty)+2, false);//таймер
		break;
		
		case "FalseTrace_officer":
			dialog.text = "Vouliez-vous quelque chose, capitaine ?";
			link.l1 = "Rien, laisse tomber.";
			link.l1.go = "exit";
			NextDiag.TempNode = "FalseTrace_officer";
		break;
		
		case "FalseTrace_7":
			chrDisableReloadToLocation = true;
			dialog.text = "Vouliez-vous me voir, capitaine ?";
			link.l1 = "Je pense que tu l'as vu venir... Où est l'argent, bon sang? Où est-il? Je te parle! Le capitaine du flûte m'a dit que c'était un navire de ravitaillement! Tu m'as menti!";
			link.l1.go = "FalseTrace_8";
		break;
		
		case "FalseTrace_8":
			dialog.text = "Calmez-vous, Capitaine. Je vais essayer d'expliquer tout.";
			link.l1 = "Bien sûr que tu vas le faire ! Je me suis déjà calmé ! Tu n'es pas pendu à une vergue en ce moment uniquement parce que je n'arrive toujours pas à comprendre tes motivations. Tu as poursuivi ce flûte avec moi, sachant d'avance qu'il n'y avait pas d'argent. Alors, je te prie de t'expliquer.";
			link.l1.go = "FalseTrace_9";
		break;
		
		case "FalseTrace_9":
			dialog.text = "Oui, je t'ai vraiment berné, Capitaine. Mais c'était la seule façon de te convaincre de faire ce dont j'ai besoin, de capturer... khe kha! De capturer ce maudit flûte\nMais je te promets de rembourser ma dette envers toi. Maintenant, laisse-moi te dire pourquoi je l'ai fait. As-tu trouvé une femme sur le flûte? J'ai vu les membres de l'équipage la prendre sur ton navire...";
			link.l1 = "Hm... Alors, tu avais besoin de la fille, hein? Et c'est pour ça que tu m'as forcé à engager une bataille navale et à tuer un tas de gens !?";
			link.l1.go = "FalseTrace_10";
		break;
		
		case "FalseTrace_10":
			dialog.text = "C'est ma femme. Katerine Rayner. Elle s'est enfuie de chez moi il y a trois mois avec ce misérable Capitaine. J'ai fait tous les efforts possibles pour les retrouver, et je l'ai fait. Ils allaient tous les deux "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.TargetCity)+" . Je ne pouvais imaginer une meilleure façon de ramener Katerine et de m'occuper même de ce voleur de femme\nSi je vous disais la vérité, vous partiriez. J'ai donc dû vous raconter une histoire juteuse sur un flûte rempli d'argent.";
			link.l1 = "Hmpf... Ta femme t'a quitté, n'est-ce pas ? Très intéressant !";
			link.l1.go = "FalseTrace_11";
		break;
		
		case "FalseTrace_11":
			dialog.text = "C'est ma femme légitime, je l'aime et personne d'autre n'a le droit d'être avec elle ! Ce vaurien lui a raconté de beaux mensonges sur la romance et toutes ces foutaises quand j'étais... absent. Tu ne connais pas les femmes ? Elle a cru à ces balivernes, la sotte, et s'est enfuie avec lui.";
			link.l1 = "D'accord, écoutez, je ne me soucie pas vraiment de votre vie de famille, alors arrangez cela avec votre femme. Mais vous m'avez parlé de compenser mes frais, n'est-ce pas? Ai-je bien entendu?";
			link.l1.go = "FalseTrace_12";
		break;
		
		case "FalseTrace_12":
			if (pchar.basenation == SPAIN || pchar.basenation == HOLLAND)
			{
				pchar.questTemp.FalseTrace.QuestCity = "Portobello";
				pchar.questTemp.FalseTrace.QuestShore = "Shore48";
			}
			else
			{
				pchar.questTemp.FalseTrace.QuestCity = "SantaCatalina";
				pchar.questTemp.FalseTrace.QuestShore = "Shore54";
			}
			dialog.text = "Oui, vous m'avez bien entendu, capitaine. Un service pour un service. Je n'ai pas d'argent pour le moment, mais si vous nous emmenez, Katerine et moi, à "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity)+", je vous donnerai des informations tout à fait fiables sur où vous pouvez récupérer de l'or sans aucun effort.";
			link.l1 = "Très intéressant. Et pourquoi ne pouvez-vous pas me donner cette information totalement fiable tout de suite ?";
			link.l1.go = "FalseTrace_13";
		break;
		
		case "FalseTrace_13":
			dialog.text = "Parce que je n'ai pas encore cette information. Laissez-moi vous expliquer en détail. Un gentilhomme de fortune nommé Solly l'Œil-de-Lynx - en avez-vous déjà entendu parler ? - il a l'intention de piller des mines d'or non loin de Blueweld. En raison de certains événements, il devra laisser tout son or dans un endroit caché et mettre quelques gardes pour le protéger. L'homme lui-même ira à pied jusqu'à Belize ou à Blueweld pour obtenir un navire. J'ai un agent parmi l'équipage de Solly, il m'attendra à "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity)+". Une fois que nous jetterons l'ancre là-bas, il me dira où Solly cache ses trésors\nTu iras là-bas, élimineras les gardes et prendras tout l'or pour toi. J'allais le faire moi-même, mais étant donné la situation actuelle, je te laisse tout. Pas de frais.";
			link.l1 = "Ton histoire ressemble fort à ta précédente fable sur un flûte chargé d'argent. Tu m'as déjà trompé une fois. Comment peux-tu garantir que tu ne mens pas cette fois-ci ?";
			link.l1.go = "FalseTrace_14";
		break;
		
		case "FalseTrace_14":
			dialog.text = "Je te donne ma parole. Je n'ai pas d'autres garanties. Mais c'est vrai, je le jure khe... kha... maudites mines !";
			link.l1 = "D'accord. Maintenant allez, et je réfléchirai à ce que vous avez dit.";
			link.l1.go = "FalseTrace_15";
		break;
		
		case "FalseTrace_15":
			dialog.text = "N'y pense pas trop longtemps. Solly l'Œil-Plissé reviendra pour ses trésors, comme tu devrais le réaliser. Selon mes calculs, tu n'as que deux semaines pour te rendre à "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity+"Gen")+".";
			link.l1 = "Je garderai cela à l'esprit. Et maintenant, allez aux quartiers de l'équipage et rejoignez les marins. Je pense qu'il vaudrait mieux que vous soyez séparé de votre femme jusqu'à notre arrivée. Vous pouvez y aller maintenant.";
			link.l1.go = "FalseTrace_16";
		break;
		
		case "FalseTrace_16":
			DialogExit();
			LAi_SetActorType(npchar);
			pchar.questTemp.FalseTrace = "TalkCabinWoman";
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "TalkSelf_Quest", 3.0);
			SetFunctionTimerCondition("FalseTraceSollyOver", 0, 0, 15, false);//таймер
			AddQuestRecord("FalseTrace", "5");
			AddQuestUserData("FalseTrace", "sCity", XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity));
		break;
		
		case "FalseTrace_17":
			dialog.text = "Avez-vous fait appel à moi, capitaine ?";
			link.l1 = "Oui. Adam Rayner, je vais vous arrêter et vous emprisonner. Vous m'avez trompé, et je n'ai pas d'autre choix que de vous isoler et de vous livrer aux autorités.";
			link.l1.go = "FalseTrace_18";
		break;
		
		case "FalseTrace_18":
			dialog.text = "Vraiment ? Je m'attendais à ce que vous le fassiez, Capitaine. Surtout après que vous soyez venu à la cale et ayez discuté avec ce vilain voleur de femmes d'autrui. Vous avez décidé que vous étiez de son côté, n'est-ce pas, Capitaine ?";
			link.l1 = "Aucune de tes affaires. Tu m'as utilisé, tu m'as roulé, et maintenant tu essaies encore de me tromper avec des contes absurdes de trésors ! Bosco, emmène-le !";
			link.l1.go = "FalseTrace_19";
		break;
		
		case "FalseTrace_19":
			dialog.text = "Kha, pas si vite, Capitaine... Le contremaître et le reste de votre équipage ne pourront pas entrer ici de sitôt. N'avez-vous pas remarqué que j'ai verrouillé la porte ? Maintenant, nous sommes seuls ici - juste vous et moi. Alors montrez-moi, capitaine, de quoi vous êtes fait !";
			link.l1 = "Vraiment ? Tu crois vraiment que tu as une chance ?! Tu vas le regretter, salaud !";
			link.l1.go = "FalseTrace_20";
		break;
		
		case "FalseTrace_20":
			DialogExit();
			NextDiag.currentnode = "FalseTrace_21";
			chrDisableReloadToLocation = true;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_SetHP(npchar, 100+MOD_SKILL_ENEMY_RATE*35, 100+MOD_SKILL_ENEMY_RATE*35); // belamour с 40 хп боец из него никудышный
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_SetCheckMinHP(npchar, 10.0, true, "FalseTrace_capture");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "FalseTrace_21":
			dialog.text = "";
			link.l1 = "C'est mieux... Posez vos armes, scélérat ! Bosco ! Mettez ce vaurien aux fers et jetez-le dans la cale !";
			link.l1.go = "FalseTrace_22";
		break;
		
		case "FalseTrace_22":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);
			bQuestDisableMapEnter = false;
			RemovePassenger(Pchar, npchar);
			pchar.GenQuest.LastQuestPrisonerIdx = SetCharToPrisoner(npchar);
			SetCharacterRemovable(&characters[sti(pchar.GenQuest.LastQuestPrisonerIdx)], false);
			Pchar.questTemp.FalseTrace.PrisonerAdamIDX = sti(pchar.GenQuest.LastQuestPrisonerIdx);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 3.0);
			LAi_SetPlayerType(pchar);
			RemoveCharacterEquip(npchar, BLADE_ITEM_TYPE);
			RemoveCharacterEquip(npchar, GUN_ITEM_TYPE);
			RemoveCharacterEquip(npchar, CIRASS_ITEM_TYPE);
			sld = &Characters[sti(Pchar.questTemp.FalseTrace.PrisonerIDX)];
			ReleasePrisoner(sld); //освободили пленника
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, false);
			DeleteAttribute(sld, "LifeDay") //постоянный персонаж
			GiveItem2Character(sld, "blade_10");
			EquipCharacterbyItem(sld, "blade_10");
			GiveItem2Character(sld, "pistol1");
			EquipCharacterbyItem(sld, "pistol1");//патроны не даю - все одно для антуражу
			DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
			AddComplexSelfExpToScill(40, 40, 40, 40);
			AddQuestRecord("FalseTrace", "11");
			AddQuestUserData("FalseTrace", "sShore", XI_ConvertString(pchar.questTemp.FalseTrace.TargetShore+"Gen"));
			pchar.questTemp.FalseTrace = "AdamPrisoner";
		break;
		
		case "FalseTrace_23":
			pchar.quest.FalseTraceSollyOver.over = "yes"; //снять таймер
			dialog.text = "Merci, capitaine, pour avoir aidé à ramener ma femme ! Adam Rayner vous est redevable, il ne l'oubliera pas, ha-ha, je le jure sur... kha ! Sacrées mines ! Maintenant, parlons de Solly le Bigleux. Mon homme m'a déjà tout raconté. Solly a laissé tous ses trésors dans une grotte de la baie de San Juan del Norte. Lui-même est à Blueweld maintenant\nVous devriez vous dépêcher, vous n'avez que cinq jours, selon mon ami. Prenez vos hommes avec vous, les bandits de Solly sont coriaces, ils vont vous donner du fil à retordre\nIl est temps de se dire adieu. Merci encore, Capitaine, bon vent !";
			link.l1 = "Bonne chance à toi, Adam. Ne fâche pas ta femme !";
			link.l1.go = "FalseTrace_Remove_exit";
			SetFunctionTimerCondition("FalseTraceBonanzaOver", 0, 0, 5, false);//таймер
			pchar.quest.False_Trace_4.win_condition.l1 = "location";
			pchar.quest.False_Trace_4.win_condition.l1.location = "Shore55";
			pchar.quest.False_Trace_4.function = "FalseTrace_SollyBonanza";
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			AddQuestRecord("FalseTrace", "14");
			AddQuestUserData("FalseTrace", "sCity", XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity));
		break;
		
		case "FalseTrace_24":
			pchar.quest.FalseTraceSollyOver.over = "yes"; //снять таймер
			dialog.text = "Ha ! Pourquoi diable, Capitaine, avons-nous accosté dans cette baie ? Je vous ai dit que mon homme m'attendait au port de "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity+"Général")+" ! Comptez-vous y aller à pied à travers la jungle ?";
			link.l1 = "Mauvaise supposition, Adam. Pensais-tu vraiment que j'allais croire à tes balivernes encore une fois ? Me prends-tu pour un idiot complet ? Cette fois, j'ai passé un accord avec ta femme.";
			link.l1.go = "FalseTrace_25";
		break;
		
		case "FalseTrace_25":
			dialog.text = "Quoi ?! Kha ! Quel genre d'affaire avec ma femme ? Qu'est-ce que tu racontes, espèce de poisson pourri ?!";
			link.l1 = "À cause de tes fausses informations, j'ai capturé un flûte vide et tué son capitaine. Je regrette de l'avoir fait, bien qu'il soit trop tard pour les regrets. Ta femme était amoureuse de ce marin, si j'ai bien compris. C'est pourquoi elle m'a demandé de te tuer. C'est pourquoi nous sommes ici dans cette baie maintenant.";
			link.l1.go = "FalseTrace_26";
		break;
		
		case "FalseTrace_26":
			dialog.text = "Je n'en reviens pas ! Katerine... quelle garce ! Eh bien, tu recevras encore ce que tu mérites... Alors, comment t'a-t-elle promis de te payer, imbécile ? Elle n'a pas un sou, elle a même vendu tous ses bijoux pour s'enfuir avec ce capitaine !";
			link.l1 = "Ce ne sont pas tes affaires, vaurien. Mais il est temps de terminer notre conversation. Je vais t'envoyer en enfer, là où tu aurais dû être depuis longtemps déjà !";
			link.l1.go = "FalseTrace_27";
		break;
		
		case "FalseTrace_27":
			dialog.text = "Voyons voir ce que tu sais faire, hareng pourri !";
			link.l1 = "...";
			link.l1.go = "FalseTrace_28";
		break;
		
		case "FalseTrace_28":
			DialogExit();
			npchar.SaveItemsForDead = true;
			npchar.DontClearDead = true;
			LAi_SetWarriorType(npchar);
			LAi_SetImmortal(npchar, false);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "FalseTrace_AdamDead");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "FalseTrace_abordage":
			dialog.text = "Ah ! Pourquoi diable avez-vous attaqué mon navire, vermine ? Je ne peux pas comprendre...";
			link.l1 = "Ne fais pas semblant d'être un agneau, capitaine. Je sais quel genre de cargaison tu transportes. J'en ai besoin.";
			link.l1.go = "FalseTrace_abordage_1";
		break;
		
		case "FalseTrace_abordage_1":
			dialog.text = "Du fret? Ha-ha! Quel genre de fret vous attendiez-vous à voir ici? Mes cales sont vides!";
			link.l1 = "Qu'as-tu dit, scélérat ! Répète un peu !";
			link.l1.go = "FalseTrace_abordage_2";
		break;
		
		case "FalseTrace_abordage_2":
			dialog.text = "Je le répète - je n'ai aucune cargaison à bord. Ce flûte est un navire de ravitaillement en route vers "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.TargetCity)+" pour prendre une cargaison de boulets de canon et de provisions pour les troupes.";
			link.l1 = "Tu me montes un bateau. Tes cales doivent être pleines d'argent. Et je vais les vérifier, une fois que nous aurons terminé cette conversation...";
			link.l1.go = "FalseTrace_abordage_3";
		break;
		
		case "FalseTrace_abordage_3":
			dialog.text = "Je ne sais pas qui vous a parlé d'argent. Mais c'est un pur non-sens... J'ai perdu contre vous, donc je me rends. Voici mon épée. Maintenant, vous pouvez aller vérifier les cales. Elles sont vides.";
			link.l1 = "Abandonner ? Non ! Je n'ai pas besoin de témoins. Prends ton épée et bats-toi, ou je t'éventrerai comme un mouton.";
			link.l1.go = "FalseTrace_abordage_4";
			link.l2 = "Bien pour toi que tu as fait preuve de raison. Je pense que je pourrai obtenir une rançon pour toi... Hé, les gars - jetez le capitaine dans la cale !";
			link.l2.go = "FalseTrace_abordage_5";
		break;
		
		case "FalseTrace_abordage_4":
			DialogExit();
			pchar.questTemp.FalseTrace.KillCaptain = "true";//атрибут квеста
			Lai_SetPlayerType(pchar);
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "FalseTrace_AfterFight");
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.questTemp.FalseTrace.CapName = GetFullName(npchar);
			ChangeCharacterComplexReputation(pchar, "nobility", -3);
		break;
		
		case "FalseTrace_abordage_5":
			DialogExit();
			pchar.questTemp.FalseTrace.CapPrisoner = "true";//атрибут квеста
			Lai_SetPlayerType(pchar);
			DeleteAttribute(npchar, "DontRansackCaptain");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "FalseTrace_AfterFight", 3.0);
			pchar.GenQuest.LastQuestPrisonerIdx = SetCharToPrisoner(npchar);
			SetCharacterRemovable(&characters[sti(pchar.GenQuest.LastQuestPrisonerIdx)], false);
			pchar.questTemp.FalseTrace.CapName = GetFullName(npchar);
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
		break;
		
		case "FalseTrace_wife":
			dialog.text = "Tu l'as tué, vaurien! Scélérat! Pauvre "+pchar.questTemp.FalseTrace.CapName+" !";
			link.l1 = "Qu'est-ce que c'est ? D'où viens-tu, cher ?";
			link.l1.go = "FalseTrace_wife_1";
		break;
		
		case "FalseTrace_wife_1":
			dialog.text = "Tu brûleras en enfer pour tout ce que tu as fait. Que le diable t'emporte !";
			link.l1 = "Calmez-vous, jeune dame ! Ne tentez pas votre chance en me maudissant - ou je vous enverrai rejoindre votre capitaine !";
			link.l1.go = "FalseTrace_wife_2";
		break;
		
		case "FalseTrace_wife_2":
			dialog.text = "Toi ... tu n'oseras pas lever la main sur une femme !";
			link.l1 = "Je n'aurai même pas besoin de le faire. Je peux te tirer dessus. Ou je te jetterai simplement par-dessus bord, et les requins feront le reste... Maintenant, qu'attends-tu ? Va à mon navire. N'aie pas peur - je ne laisserai personne te faire du mal et je ne te toucherai pas moi-même si tu restes tranquille...";
			link.l1.go = "FalseTrace_wife_3";
		break;
		
		case "FalseTrace_wife_3":
			DialogExit();
			pchar.quest.False_Trace_AfterBattle.over = "yes";
			pchar.quest.FalseTraceGaleonOver.over = "yes";
			if (CheckAttribute(pchar, "questTemp.FalseTrace.CapPrisoner")) AddQuestRecord("FalseTrace", "");
			else AddQuestRecord("FalseTrace", "");
			sld = characterFromId("Mugger");
			DeleteAttribute(sld, "HalfImmortal");
			RemovePassenger(Pchar, sld);
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, false);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 3.0);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			DoQuestCheckDelay("LAi_EnableReload", 4.0);
			bQuestDisableMapEnter = true;
			pchar.questTemp.FalseTrace = "TalkCabin";
			AddQuestRecord("FalseTrace", "4");
		break;
		
		case "FalseTrace_wife_4":
			dialog.text = "Que... que vas-tu lui faire ?";
			link.l1 = "Qu'est-ce que c'est? D'où viens-tu, cher?";
			link.l1.go = "FalseTrace_wife_5";
		break;
		
		case "FalseTrace_wife_5":
			dialog.text = "Pauvre "+pchar.questTemp.FalseTrace.CapName+"! Dis-moi - vas-tu le tuer ? Ne...";
			link.l1 = "Ecoute-moi bien, ma dame - si j'avais voulu le tuer, je l'aurais déjà fait. Il restera dans la cale, et ensuite je le relâcherai ou probablement je demanderai une rançon... la dernière option est plus probable. Et maintenant, sois une bonne fille et monte à bord de mon navire. N'aie pas peur - je ne laisserai personne te faire du mal et je ne te toucherai pas moi-même si tu restes tranquille...";
			link.l1.go = "FalseTrace_wife_3";
		break;
		
		case "FalseTrace_wife_6":
			if (CheckAttribute(pchar, "questTemp.FalseTrace.KillCaptain"))
			{
				dialog.text = "Que veux-tu de moi? Me jeter aux requins, comme tu as dit que tu le ferais? Tu as ruiné ma vie et je...";
				link.l1 = "Allez, ma chère. Personne ne va te jeter nulle part. Je veux juste clarifier la situation, puisque j'ai attaqué ce flûte à cause de toi et non pour une autre raison.";
				link.l1.go = "FalseTrace_wife_7";
			}
			else
			{
				dialog.text = "Que veux-tu de moi? Où est "+pchar.questTemp.FalseTrace.CapName+"Une rançon ? Avez-vous besoin d'une rançon ?";
				link.l1 = "D'accord, madame, cessons ce flot de questions inutiles. Je ne vous ai pas appelée ici pour cela. Un fait a été éclairci, et cela vous intéressera de l'entendre.";
				link.l1.go = "FalseTrace_wife_20";
			}
		break;
		
		case "FalseTrace_wife_7":
			dialog.text = "À cause de moi ? Vous dites que c'est ma faute si vous avez attaqué notre navire et tué mon bien-aimé ? Pauvre "+pchar.questTemp.FalseTrace.CapName+", que vous a-t-il fait ? Vous répondrez devant le Seigneur pour tout ce que vous avez fait...";
			link.l1 = "Le même vieux ragoût ! Devons-nous reprendre notre discussion sur les requins ?";
			link.l1.go = "FalseTrace_wife_8";
		break;
		
		case "FalseTrace_wife_8"://ноды пересечения - старт
			dialog.text = "";
			link.l1 = "Tranquille maintenant ? Parfait. Maintenant, écoute-moi ! J'ai attaqué le navire parce que j'avais des informations qu'il transportait une cargaison décente d'argent. Et j'ai obtenu ces informations de Adam Rayner.";
			link.l1.go = "FalseTrace_wife_9";
		break;
		
		case "FalseTrace_wife_9":
			dialog.text = "Ah! Quoi?! Adam? Où est-il? Est-il ici?";
			link.l1 = "Je vois que tu connais le nom... Katerine. Et, comme tu peux le voir, je sais déjà tout sur toi. Je suppose qu'Adam Rayner est ton époux, n'est-ce pas ?";
			link.l1.go = "FalseTrace_wife_10";
		break;
		
		case "FalseTrace_wife_10":
			dialog.text = "Oui. Je suis la femme de ce monstre. J'étais sous l'illusion que ce cauchemar était enfin terminé... Vous a-t-il engagé pour me rattraper ?";
			link.l1 = "Généralement, c'est ce qui s'est passé. Adam m'a menti à propos de l'argent, pour que je capture le flûte '"+pchar.questTemp.FalseTrace.ShipName+"'. Assurément, il était déterminé à te ramener. Il y a un quart d'heure, il m'a expliqué toutes ses actions.";
			link.l1.go = "FalseTrace_wife_11";
		break;
		
		case "FalseTrace_wife_11":
			dialog.text = "Et... que veut-il ? Que t'a-t-il dit ?";
			link.l1 = "Il veut que sa légitime épouse lui revienne. Il me fournira des informations sur l'or de Solly le Louche en compensation pour m'avoir trompé. Et je vais vous emmener tous les deux à "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity)+".";
			link.l1.go = "FalseTrace_wife_12";
		break;
		
		case "FalseTrace_wife_12":
			dialog.text = "Non... (pleurant) Je ne veux pas retourner chez ce vaurien ! J'ai fait un énorme effort pour m'enfuir et brouiller mes pistes, mais il m'a quand même retrouvée... Scélérat ! Bandit ! Fichu voleur !";
			link.l1 = "Calme-toi, Katerine... Surveille ton langage. C'est ton mari, après tout. Et il a dit qu'il t'aimait.";
			link.l1.go = "FalseTrace_wife_13";
		break;
		
		case "FalseTrace_wife_13":
			dialog.text = "(en pleurant) Mon mari ? Savez-vous qui est mon mari ? C'est un ancien prisonnier, un forçat et maintenant le bandit le plus cruel de "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.StartCity+"Gén")+"! C'est une bête vile et ignoble, et je ne suis pour lui qu'un trou entre les jambes à baiser !";
			link.l1 = "N'avais-tu pas tout vu avant de l'épouser ?";
			link.l1.go = "FalseTrace_wife_14";
		break;
		
		case "FalseTrace_wife_14":
			dialog.text = "Au début, il était différent... Et son passé me semblait si romantique... Mais finalement tout a changé. Et je ne veux même pas le voir, sans parler de vivre avec lui, ne peux-tu pas comprendre cela? Je ne veux pas! Surtout après cette attaque sur le flûte, qu'il a organisée!";
			link.l1 = "Hm... Que devrais-je faire de toi, alors, douce dame ?";
			link.l1.go = "FalseTrace_wife_15";
		break;
		
		case "FalseTrace_wife_15"://ноды пересечения - конец
			if (CheckAttribute(pchar, "questTemp.FalseTrace.KillCaptain"))
			{
				dialog.text = "Que faire ? Je sais quoi faire. Tu es l'instrument du péché, grâce aux actes de mon mari. Tu as tué un homme innocent, le seul homme qui m'a bien traitée. Expie tes péchés, capitaine. Tue Adam. Juste devant mes yeux. Je veux voir cette ordure mourir, je veux cracher sur son cadavre\nQuand il sera mort, je te dirai où il cache ses trésors. Cet idiot ivre m'en a parlé une fois, ha-ha, il ne s'en souvient même pas !";
				link.l1 = "Hé ! Vous êtes une femme cruelle, Katerine, à ce que je vois !";
				link.l1.go = "FalseTrace_wife_16";
			}
			else
			{
				dialog.text = ""+pchar.questTemp.FalseTrace.CapName+"... Le capitaine du flûte. Vous l'avez enfermé. Parlez-lui, je vous en prie ! Il vous offrira quelque chose pour nos vies et notre liberté ! Il trouvera une idée ! Je... Je ne veux pas retourner chez Adam, à partir de maintenant "+pchar.questTemp.FalseTrace.CapName+" est mon mari ! Je vous en supplie - ne me ramenez pas à Adam, à ce monstre !";
				link.l1 = "Hm. Intéressant. Et que peut bien m'offrir mon prisonnier ? Je peux obtenir une rançon pour lui des autorités, et j'aurai aussi l'or de Solly le Louche...";
				link.l1.go = "FalseTrace_wife_21";
			}
		break;
		
		case "FalseTrace_wife_16":
			dialog.text = "Regarde qui parle de cruauté. Navigue vers "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity)+", fais ce qu'Adam t'a dit, mais ne débarque pas au port, va plutôt à la baie la plus proche. Nous serons trois à y aller et tu tueras ce salaud\nUne fois que ce sera fait, je te parlerai de la cachette. Je le jure, je ne mens pas. Je crois que tu as plus confiance en mes mots qu'en ceux d'Adam, il t'a déjà dupé, n'est-ce pas ? Que diras-tu, capitaine ?";
			link.l1 = "Oui... On dit bien que mari et femme sont du même tonneau. Je te regarde, Katerine, et je vois que tu es la meilleure paire pour Adam... Si tu veux tant le voir mort, tu pourrais aussi bien le poignarder dans son sommeil d'ivrogne... Bosco ! Emmène-la !";
			link.l1.go = "FalseTrace_wife_17";
			link.l2 = "Je hais les vauriens qui tentent de me tromper et de m'utiliser à leurs propres fins. D'accord, Katherine, j'accepte ton offre, car il est clair pour moi qu'Adam ne mérite pas confiance. Mais si tu me trompes également, je te retrouverai même en Europe, je le jure, et je te mettrai une balle dans la tête. Maintenant, dégage. Bosco ! Emmène-la !";
			link.l2.go = "FalseTrace_wife_19";
		break;
		
		case "FalseTrace_wife_17":
			dialog.text = "Tu le regretteras... Je te le jure, je...";
			link.l1 = "Maître d'équipage ! Garde-la et surveille-la tout le temps jusqu'à notre arrivée à "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity+"Gen")+" !";
			link.l1.go = "FalseTrace_wife_18";
		break;
		
		case "FalseTrace_wife_18":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 3.0);
			AddQuestRecord("FalseTrace", "6");
			AddQuestUserData("FalseTrace", "sCity", XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity));
			AddDialogExitQuestFunction("SetCheckForSolly");
			chrDisableReloadToLocation = false;
			bQuestDisableMapEnter = false;
			DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
		break;
		
		case "FalseTrace_wife_19":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 3.0);
			AddQuestRecord("FalseTrace", "7");
			AddQuestUserData("FalseTrace", "sCity", XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity));
			AddDialogExitQuestFunction("SetCheckForKillAdam");
			chrDisableReloadToLocation = false;
			bQuestDisableMapEnter = false;
			DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
		break;
		
		case "FalseTrace_wife_20":
			dialog.text = "Quel fait ? Que vas-tu faire de nous ? Pourquoi as-tu capturé notre navire ?";
			link.l1 = "Me laisseras-tu dire un mot ou dois-je ordonner à mon bosco de te faire taire avec un baillon?!";
			link.l1.go = "FalseTrace_wife_8";
		break;
		
		case "FalseTrace_wife_21":
			dialog.text = "Le trésor de Solly ? Fais-tu vraiment confiance à ce vaurien ? Il te dupera encore, c'est sa façon de faire ! Parle à ton prisonnier !"+pchar.questTemp.FalseTrace.CapName+"est un véritable gentilhomme, il ne rompra pas sa parole et ne vous mentira pas !";
			link.l1 = "Vous ne m'avez pas convaincu, madame. Je n'ai rien à dire à votre capitaine. Je vais obtenir une rançon pour lui et je prendrai l'or de Solly à Adam. Si Adam me trompe encore, je le trouverai même au bout du monde, et il maudira le jour de sa naissance... Bosco ! Emmenez-la !";
			link.l1.go = "FalseTrace_wife_23";
			link.l2 = "Pour vous dire la vérité, je ne fais pas confiance à Adam... Je déteste être manipulé. D'accord, je vais parler à votre capitaine et je verrai ce qu'il peut me dire. Vous pouvez partir maintenant... Bosco ! Emmenez-la !";
			link.l2.go = "FalseTrace_wife_24";
		break;
		
		case "FalseTrace_wife_23":
			dialog.text = "Vous êtes un homme cruel et sans cœur ! Je jure que je...";
			link.l1 = "Maître d'équipage ! Garde-la et surveille-la tout le temps jusqu'à notre arrivée à "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity+"Gen")+" !";
			link.l1.go = "FalseTrace_wife_18";
			SetCharacterRemovable(&characters[sti(pchar.GenQuest.LastQuestPrisonerIdx)], true);
		break;
		
		case "FalseTrace_wife_24":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 3.0);
			AddQuestRecord("FalseTrace", "8");
			chrDisableReloadToLocation = false;
			pchar.questTemp.FalseTrace.Prisoner = "true";
			SetCharacterRemovable(&characters[sti(pchar.GenQuest.LastQuestPrisonerIdx)], true);
		break;
		
		case "FalseTrace_wife_25":
			dialog.text = "C'est fini maintenant... Pauvre "+pchar.questTemp.FalseTrace.CapName+" est vengé, et je peux maintenant respirer librement et me dire veuve...";
			link.l1 = "J'ai accompli ma part du marché, Katerine. Maintenant c'est à ton tour.";
			link.l1.go = "FalseTrace_wife_26";
		break;
		
		case "FalseTrace_wife_26":
			dialog.text = "Bien sûr, capitaine. Mon mari - Dieu merci, maintenant ex-mari - était un bandit, comme vous le savez déjà. Craignant d'éventuelles perquisitions, il ne gardait pas le butin pillé à la maison. Il a organisé une cachette - mais il en a parlé une fois. Pourtant, il l'a cachée d'une manière très astucieuse - il n'y a pas d'accès à cet endroit depuis le rivage.";
			link.l1 = "Très intéressant... Et où est-ce?";
			link.l1.go = "FalseTrace_wife_27";
		break;
		
		case "FalseTrace_wife_27":
			dialog.text = "Sur une petite île près d'Hispaniola. Dans le phare.";
			link.l1 = "Phare de Port-au-Prince ! Il est situé sur l'île !";
			link.l1.go = "FalseTrace_wife_28";
		break;
		
		case "FalseTrace_wife_28":
			dialog.text = "Probablement. Vous pourrez y trouver le butin. Vous verrez. C'est tout. Adieu, Capitaine.";
			link.l1 = "Attends... Pardonne-moi, Katerine, si tu peux. J'espère que la mort de celui responsable de tous tes malheurs te soulagera, en tout cas. Je suis vraiment désolé...";
			link.l1.go = "FalseTrace_wife_29";
		break;
		
		case "FalseTrace_wife_29":
			dialog.text = "Je n'ai pas besoin de tes regrets, Capitaine. Tu as fait ce que je t'ai demandé - et je t'ai dit tout ce que tu voulais savoir. Adieu maintenant, et laisse-moi seul avec mon chagrin...";
			link.l1 = "Adieu, Katerine.";
			link.l1.go = "FalseTrace_wife_30";
		break;
		
		case "FalseTrace_wife_30":
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 15);
			LAi_LocationDisableOfficersGen(pchar.questTemp.FalseTrace.QuestShore, false);//офицеров пускать
			//LAi_LocationDisableOfficersGen("Mayak7", true);//офицеров не пускать
			locations[FindLocation("Mayak7")].DisableEncounters = true;//энкаунтеры закрыть
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			pchar.quest.False_Trace_7.win_condition.l1 = "location";
			pchar.quest.False_Trace_7.win_condition.l1.location = "Mayak7";
			pchar.quest.False_Trace_7.function = "FalseTrace_AdamTreasure";
			AddQuestRecord("FalseTrace", "23");
		break;
		
		case "FalseTrace_wife_31":
			dialog.text = "Scélérat immonde ! Il a réussi à tuer les quatre ! Incroyable !";
			link.l1 = "Tu ne t'attendais pas à un tel retournement, Katerine ? Je suis difficile à tuer. Tu joues bien sur deux tableaux, je dois dire !";
			link.l1.go = "FalseTrace_wife_32";
		break;
		
		case "FalseTrace_wife_32":
			dialog.text = "Tu as assassiné mon homme. Penses-tu vraiment que je te laisserais continuer à respirer ?! Tu pensais que la mort d'Adam m'avait satisfait ? Non ! Tu ne quitteras pas cet endroit. Il y a un navire non loin de cette île, il fera couler ta vieille coque avec toi !\nMaintenant, fais ce que tu veux de moi.";
			link.l1 = "N'ai-je pas dit, ma chère, que tu perdrais la tête si tu me trompais ? Un diable rusé ! Tu seras bien moins dangereux mort. Cette jolie tête va recevoir une balle tout de suite...";
			link.l1.go = "FalseTrace_wife_33";
			link.l2 = "Je te plains, Katerine. Ton désir de vengeance ne t'a apporté aucun bien au final. Je vais te laisser à ton sort - tu resteras sur cette île. Je pense que les pêcheurs locaux te trouveront bientôt et t'amèneront à Hispaniola. Et que le Seigneur nous juge pour tous nos actes...";
			link.l2.go = "FalseTrace_wife_35";
		break;
		
		case "FalseTrace_wife_33":
			dialog.text = "C'est toi qui devrais prier, monstre ! Assassin ! À l'aide ! Putai...";
			link.l1 = "J'en ai assez entendu.";
			link.l1.go = "FalseTrace_wife_34";
		break;
		
		case "FalseTrace_wife_34":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_SetImmortal(npchar, false);
			//  belamour legendary edition если не надет пистоль или мушкет, то выдадим строевой -->
			if(!CheckAttribute(pchar,"equip."+GUN_ITEM_TYPE) || !CheckAttribute(pchar,"equip."+MUSKET_ITEM_TYPE))
			{
				GiveItem2Character(pchar, "pistol1");
				EquipCharacterbyItem(pchar, "pistol1");
			}
			// <-- legendary edition
			LAi_ActorAnimation(pchar, "shot", "FalseTrace_CaterinaKilled", 1.0);
		break;
		
		case "FalseTrace_wife_35":
			dialog.text = "Puisse-tu te noyer ! Que ton navire s'écrase contre les rochers ! Que tu...";
			link.l1 = "Adieu, Katerine.";
			link.l1.go = "FalseTrace_wife_36";
		break;
		
		case "FalseTrace_wife_36":
			DialogExit();
			sld = characterFromID("FalseTraceWife"); 
			sld.lifeday = 0;
			LAi_ActorGoToLocation(npchar, "goto", "goto33", "none", "", "", "", -1);
			LAi_SetPlayerType(pchar);
			chrDisableReloadToLocation = false;
			LAi_LocationDisableOfficersGen("Mayak7", false);//офицеров пускать
			locations[FindLocation("Mayak7")].DisableEncounters = false;//энкаунтеры открыть
			AddQuestRecord("FalseTrace", "25");
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			OfficersReaction("good");
		break;
		
		case "FalseTrace_Bandits":
			dialog.text = "A-ah, voici l'assassin d'Adam ! Katerine avait raison, ce salaud est venu piller la cachette !";
			link.l1 = "Quoi? Katerine? Qui es-tu?";
			link.l1.go = "FalseTrace_Bandits_1";
		break;
		
		case "FalseTrace_Bandits_1":
			dialog.text = "Qui sommes-nous? Nous sommes des amis d'Adam Rayner, qui a été assassiné par toi. Il était le chef de notre confrérie. Maintenant, je suis le chef, mon nom est "+GetFullName(npchar)+", et je te punirai pour avoir tué mon patron et pour la violence que tu as commise contre sa femme.";
			link.l1 = "La violence ? De quoi diable parles-tu ?";
			link.l1.go = "FalseTrace_Bandits_2";
		break;
		
		case "FalseTrace_Bandits_2":
			dialog.text = "Tu as poignardé Adam dans le dos, sale traître, tu as forcé sa femme à te dire où Adam gardait son or et ensuite tu as laissé la pauvre femme mourir sur une rive déserte\nMais elle a survécu, elle nous a demandé de l'aider, de réparer une injustice. Nous t'attendons depuis plusieurs jours. Et te voilà, bâtard !";
			link.l1 = "Ha-ha ! C'est bien le style de Katerine... Maintenant écoute, j'ai tué Adam, c'est vrai, mais je l'ai fait parce que sa femme m'a en fait demandé de le tuer. C'était une vengeance pour la mort de son amant. Elle m'a dit où trouver la cachette pour me rembourser...";
			link.l1.go = "FalseTrace_Bandits_3";
		break;
		
		case "FalseTrace_Bandits_3":
			dialog.text = "Ne calomnie pas la pauvre veuve, racaille! Pourquoi serait-elle venue nous voir alors? Elle nous a proposé de prendre tout l'or pour nous en échange de ta vie. Elle ne veut pas de pièces, elle veut ta mort! Une mort sacrée pour la mort de son mari!\nMais je le jure, elle ne mourra pas dans la pauvreté, c'est aussi vrai que mon nom est "+GetFullName(npchar)+", et que c'est le moment pour toi de mourir, lâche!";
			link.l1 = "Sainte merde, quel discours glorieux. Oh, la voilà, impatiente de voir cette comédie en personne... Messieurs ?";
			link.l1.go = "FalseTrace_Bandits_4";
		break;
		
		case "FalseTrace_Bandits_4":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешим драться
			DialogExit();
			for (i=1; i<=4; i++)
			{
				sld = characterFromId("Adam_bandit_"+i);	
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "FalseTrace_BanditsAfterFight");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "FalseTrace_Remove1":
			dialog.text = "Tu es vraiment un empoté, capitaine ! Perdre un flûte rempli d'argent... J'ai fait une erreur en comptant sur toi. Adieu !";
			link.l1 = "Adieu, Adam.";
			link.l1.go = "FalseTrace_Remove2";
		break;
		
		case "FalseTrace_Remove2":
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 15);
		break;
		
		case "FalseTrace_Remove_exit":
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "FalseTraceWife_Remove", 15);
		break;
		
		case "FalseTrace_Remove2":
			dialog.text = "Je vous ai prévenu, capitaine, nous n'avions que deux semaines ! A cette heure, Solly l'Œil-Squintant doit avoir déjà emporté tout le butin. Ce n'est pas ma faute si vous êtes un tel brouillon. Adieu !";
			link.l1 = "Ouais, ma faute. Adieu, j'espère que nous ne nous reverrons pas, tu n'es qu'un porte-malheur pour moi.";
			link.l1.go = "FalseTrace_Remove_exit";
		break;
		
		case "FalseTrace_Solly":
			dialog.text = "Hein ! Enfin ! Nous sommes fatigués d'attendre, et ces maudits moustiques... Attends... Et où est Solly ? Je ne comprends pas...";
			link.l1 = "Solly ne viendra pas ici. J'agis en son nom... Alors soit tu me donnes l'or, soit tu es aussi bon que mort.";
			link.l1.go = "FalseTrace_Solly_1";
		break;
		
		case "FalseTrace_Solly_1":
			dialog.text = "Argh ! Nous verrons bien ! A moi, les gars ! Aux armes !";
			link.l1 = "Quelle manière idiote de mourir, venez alors charognards !";
			link.l1.go = "FalseTrace_Solly_2";
			AddDialogExitQuestFunction("FalseTrace_SollyBonanzaAdd");
		break;
		
		case "FalseTrace_Solly_2":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешим драться
			DialogExit();
			for (i=1; i<=6; i++)
			{
				sld = characterFromId("FTEnemy_crew_"+i);	
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "FalseTrace_SollyAfterFight");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "FalseTrace_GoldShip":
			dialog.text = "Vous avez rempli votre part du marché, capitaine. Merci de m'avoir fait confiance. Ne vous inquiétez pas pour Adam, je le livrerai au bon endroit. Il recevra ce qu'il mérite.";
			link.l1 = "Je me fiche d'Adam. Et ta promesse concernant un navire ?";
			link.l1.go = "FalseTrace_GoldShip_1";
		break;
		
		case "FalseTrace_GoldShip_1":
			if (sti(pchar.basenation == HOLLAND) || sti(pchar.basenation == SPAIN))
			{
				pchar.questTemp.FalseTrace.ShipNation = ENGLAND;
				pchar.questTemp.FalseTrace.ShipCity = "PortRoyal";
			}
			else
			{
				pchar.questTemp.FalseTrace.ShipNation = SPAIN;
				pchar.questTemp.FalseTrace.ShipCity = "Maracaibo";
			}
			dialog.text = "Oui, oui, bien sûr. Voyons voir, en comptant à partir d'aujourd'hui... Oui... Dans 12-14 jours à partir de "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.ShipCity+"Gén")+" un lourd galion chargé de minerai d'or mettra le cap sur l'Europe. Il sera protégé par une seule frégate ou corvette\nAlors prépare-toi, c'est un riche butin, mais il a des dents. Cependant, je suis sûr que tu réussiras, tu as écrasé ma résistance assez facilement... Tu dois atteindre "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.ShipCity+"Gén")+" dans deux semaines et préparez une embuscade\nSouvenez-vous que votre cible est un lourd galion avec un seul navire de convoi. C'est tout, je suppose. Le reste est entre vos mains.";
			link.l1 = "Je vois... Eh bien, "+pchar.questTemp.FalseTrace.CapName+"Adieu. Peut-être devrais-je te souhaiter bonne chance et une vie heureuse avec Katerine ? J'espère que vous vous en sortirez bien tous les deux. C'est dommage que nous nous soyons rencontrés dans de si tristes circonstances.";
			link.l1.go = "FalseTrace_GoldShip_2";
		break;
		
		case "FalseTrace_GoldShip_2":
			dialog.text = "Merci, capitaine. Comme je l'ai dit auparavant, vous avez une certaine noblesse. J'espère que vous tirerez la bonne conclusion que les actions honnêtes vous apportent plus de profit que celles déshonorantes. Consacrez-vous à servir votre nation, et vous deviendrez un grand marin de la flotte.";
			link.l1 = "Je vais réfléchir à vos paroles. Eh bien, adieu pour l'instant !";
			link.l1.go = "FalseTrace_GoldShip_3";
		break;
		
		case "FalseTrace_GoldShip_3":
			DialogExit();
			locations[FindLocation(pchar.questTemp.FalseTrace.TargetShore)].DisableEncounters = false; //энкаутеры открыть
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "FalseTraceDouble_Remove", -1);
			pchar.quest.False_Trace_6.win_condition.l1 = "Timer";
			pchar.quest.False_Trace_6.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.False_Trace_6.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 14);
			pchar.quest.False_Trace_6.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 14);
			pchar.quest.False_Trace_6.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 14);
			pchar.quest.False_Trace_6.function = "CreateFalseTraceGoldShipOnMap";
			AddQuestRecord("FalseTrace", "19");
			AddQuestUserData("FalseTrace", "sCity", XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.ShipCity+"Gen"));
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
