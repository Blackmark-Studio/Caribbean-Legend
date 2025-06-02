void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag, arTmp;
	int i, n;
	string sTemp, sStr;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			dialog.text = "Que voulez-vous ?";
			link.l1 = "Rien.";
			link.l1.go = "exit";
		break;
		
		// Квест "Путеводная звезда"
		// Этап 0, ПРОЛОГ
		case "PZ_Alonso_1":
			dialog.text = "Je m'excuse d'avoir dérangé vos quartiers, Monseigneur le Capitaine, mais c'est très important.";
			link.l1 = "J'espère que c'est le cas, Alonso. Si chacun de vous commence à débarquer ici comme si c'était son propre espace, nous aurons un problème. Alors, que se passe-t-il ?";
			link.l1.go = "PZ_Alonso_2";
		break;
		
		case "PZ_Alonso_2":
			dialog.text = "Nous avons découvert que votre coffre avait été fouillé.";
			link.l1 = "Quoi ?! Attends... Comment as-tu découvert ça ? Et que faisiez-vous tous dans ma cabine ?";
			link.l1.go = "PZ_Alonso_3";
		break;
		
		case "PZ_Alonso_3":
			dialog.text = "Nous nettoyons vos quartiers de temps en temps quand vous êtes dehors - soit en ville, soit en train de vous reposer sur les couchettes. Vous ne l'avez jamais remarqué ? Ou vous avez juste oublié ?";
			link.l1 = "Oh, c'est vrai. Eh bien, tu peux y aller maintenant.";
			link.l1.go = "PZ_OsmatrivaemKautu";
		break;
		
		case "PZ_Tichingitu_1":
			dialog.text = "Capitaine Charles, regarde ! Quelqu'un fouillait dans ton grand tiroir.";
			link.l1 = "Quoi ? Quand as-tu remarqué cela ? Sais-tu qui c’était ?";
			link.l1.go = "PZ_Tichingitu_2";
		break;
		
		case "PZ_Tichingitu_2":
			dialog.text = "Il n'y a pas longtemps, quand je venais te voir. Les esprits se taisent sur qui cela pourrait être.";
			link.l1 = "C'est une belle touche, Tichingitu. Maintenant, si vous voulez bien m'excuser, je dois vérifier s'il ne manque rien.";
			link.l1.go = "PZ_OsmatrivaemKautu";
		break;
		
		case "PZ_Duran_1":
			dialog.text = "Hé, Capitaine, qu'est-ce que tu regardes ? Quelqu'un a fouillé dans tes affaires. Même moi je l'ai remarqué.";
			link.l1 = "Ce n'était pas vous ? Après tout, je ne vous paie pas aussi généreusement que François.";
			link.l1.go = "PZ_Duran_2";
		break;
		
		case "PZ_Duran_2":
			dialog.text = "Hé, si j'étais le voleur, je ne te le dirais pas, n'est-ce pas ? Je prendrais les objets de valeur et je nettoierais après mon passage. Ce désordre n'est pas mon style.";
			link.l1 = "Je déteste l'admettre, mais tu as raison. Bon, Claude, garde tes piques pour plus tard. Je dois vérifier ce que le voleur a pris.";
			link.l1.go = "PZ_OsmatrivaemKautu";
		break;
		
		case "PZ_Folke_1":
			dialog.text = "Capitaine, j'ai remarqué aujourd'hui que quelqu'un avait fouillé dans votre coffre. Ne l'avez-vous pas remarqué ?";
			link.l1 = "Quoi ? Je ne vérifie pas constamment le coffre, Folke, et je ne suis même pas tout le temps dans la cabine. Dis-moi honnêtement - c'était toi ? As-tu encore fait des bêtises et contracté plus de prêts bancaires la dernière fois que nous étions à terre ?";
			link.l1.go = "PZ_Folke_2";
		break;
		
		case "PZ_Folke_2":
			dialog.text = "Pas du tout, Capitaine. Je n'ai rien à vous dans mes poches ou mon casier. Et je n'en aurai jamais.";
			link.l1 = "Je l'espère bien. Tu peux y aller - je vais vérifier ce qui manque.";
			link.l1.go = "PZ_OsmatrivaemKautu";
		break;
		
		case "PZ_OsmatrivaemKautu":
			DialogExit();
			
			if (npchar.id == "Tichingitu")
			{
				LAi_SetOfficerType(npchar);
				npchar.Dialog.Filename = "Quest\Sharlie\Tichingitu.c";
				npchar.Dialog.CurrentNode = "Tichingitu_officer";
			}
			if (npchar.id == "Duran" || npchar.id == "Folke")
			{
				LAi_SetOfficerType(npchar);
				npchar.Dialog.Filename = "Enc_Officer_dialog.c";
				npchar.Dialog.CurrentNode = "hired";
			}
			ChangeCharacterAddressGroup(npchar, "none", "", "");
			
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "rld", "loc2", "PZ_OsmatrivaemSunduk", -1);
		break;
		
		case "PZ_LigaInJungle_1":
			dialog.text = "Charles de Maure, n'est-ce pas ?";
			link.l1 = "À en juger par ton visage, je dirais que tu connais déjà la réponse. Alors, que veux-tu ?";
			link.l1.go = "PZ_LigaInJungle_2";
		break;
		
		case "PZ_LigaInJungle_2":
			dialog.text = "Ta tête.";
			link.l1 = "Fascinant ! Je dois dire que j'aime comment cette conversation commence. Mais avant d'aller plus loin, pourriez-vous au moins me dire à qui j'ai causé du tort ? Peut-être pouvons-nous négocier.";
			link.l1.go = "PZ_LigaInJungle_3";
		break;
		
		case "PZ_LigaInJungle_3":
			dialog.text = "Nous ne sommes pas des amateurs, Monsieur de Maure. Même si nous vous le disions, cela ne vous aiderait pas - notre employeur a déjà quitté l'Archipel. Vous ne pouvez pas leur nuire ni leur présenter des excuses. Nous avons été payés, et il est temps de tenir notre part du marché.";
			link.l1 = "Si tu as déjà été payé, pourquoi verser plus de sang ?";
			link.l1.go = "PZ_LigaInJungle_4";
		break;
		
		case "PZ_LigaInJungle_4":
			dialog.text = "Nous ne sommes pas des amateurs. Nous tenons à notre réputation.";
			link.l1 = "Je crains que tu ne puisses pas être à la hauteur cette fois-ci.";
			link.l1.go = "PZ_LigaInJungle_5";
		break;
		
		case "PZ_LigaInJungle_5":
			dialog.text = "Nous verrons bien. Fouillez son cadavre quand nous aurons fini ! Brûlez tout ce que vous trouvez !";
			link.l1 = "Brûler quoi ?..";
			link.l1.go = "PZ_LigaInJungle_6";
		break;
		
		case "PZ_LigaInJungle_6":
			DialogExit();
			
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
			LAi_SetFightMode(pchar, true);
			for (i=1; i<=4; i++)
			{
				sld = CharacterFromID("LigaInJungle_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "PZ_LigaInJunglePosleBitvy");
			
			if (CharacterIsHere("Longway"))
			{
				sld = characterFromId("Longway");
				LAi_SetCheckMinHP(sld, 1, true, "");
			}
		break;
		
		case "PZ_Longway_1":
			dialog.text = "Ce que l'homme masqué a dit... Serait-ce...?";
			link.l1 = "Que se passe-t-il, Longway ? Ce n'est pas la première fois que des chasseurs de primes me poursuivent, mais tu sembles inhabituellement préoccupé.";
			link.l1.go = "PZ_Longway_2";
		break;
		
		case "PZ_Longway_2":
			dialog.text = "Longway pense qu'il sait qui a envoyé ces hommes après vous, Monseigneur le Capitaine.";
			link.l1 = "Quelque chose dont je devrais être au courant ?";
			link.l1.go = "PZ_Longway_3";
		break;
		
		case "PZ_Longway_3":
			dialog.text = "C'est la manière de Lord Rodenburg - éliminer ceux qui l'ont aidé mais en savent trop.";
			link.l1 = "Vraiment... Cet homme masqué a dit que son employeur avait récemment quitté l'Archipel. C'est exactement ce que Lucas prévoyait ! Penses-tu que nous devrions nous attendre à d'autres attaques ?";
			link.l1.go = "PZ_Longway_4";
		break;
		
		case "PZ_Longway_4":
			dialog.text = "Il est sage d'être prêt à tout, Monseigneur le Capitaine.";
			link.l1 = "Des paroles sages. Nous le serons. Mais que cherchait Lucas ? Que pensait-il que j'avais ? Des idées, Longway ?";
			link.l1.go = "PZ_Longway_5";
		break;
		
		case "PZ_Longway_5":
			dialog.text = "Mm-mm, non, Longway n'a aucune idee de ce que cela pourrait etre.";
			link.l1 = "C'est dommage. Mais d'accord, sortons d'ici.";
			link.l1.go = "PZ_Longway_6";
		break;
		
		case "PZ_Longway_6":
			DialogExit();
			
			Return_LongwayOfficer();
			
			chrDisableReloadToLocation = false;
			pchar.questTemp.PZ_RazgovorGerrits = true;
			pchar.questTemp.PZ_PodozrenieLucas = true;
		break;
		
		// Этап 1, ВЕРНЫЙ КЛЯТВЕ
		case "PZ_Longway_11":
			dialog.text = "Monseigneur le Capitaine, Longway souhaite vous parler. C'est d'une grande importance.";
			if (CheckAttribute(pchar, "questTemp.PZ_PodozrenieLucas"))
			{
				link.l1 = "Qu'est-ce qui se passe, Longway ? Es-tu inquiet de la façon dont Lucas a dit adieu, ou as-tu découvert quelque chose de nouveau ?";
				link.l1.go = "PZ_Longway_12";
				AddCharacterExpToSkill(pchar, "Sneak", 100);
			}
			else
			{
				link.l1 = "Bien sûr ! Qu'est-ce qui te tracasse ?";
				link.l1.go = "PZ_Longway_13";
			}
		break;
		
		case "PZ_Longway_12":
			dialog.text = "Malheureusement, non.";
			link.l1 = "Alors, qu'est-ce que c'est, Longway ?";
			link.l1.go = "PZ_Longway_13";
		break;
		
		case "PZ_Longway_13":
			dialog.text = "Longway ne peut pas dire. Mais... il souhaite demander la permission de partir.";
			link.l1 = "Partir ? Pour de bon ? Pourquoi, Longway ? En tant que ton capitaine, j'ai le droit de connaître la raison.";
			link.l1.go = "PZ_Longway_14";
		break;
		
		case "PZ_Longway_14":
			dialog.text = "C'est vrai, Monseigneur le Capitaine. Mais Longway n'est ni un ouvrier ni un serviteur. Il est venu aider de son plein gré, et il peut partir de la même manière. Ce ne sera pas pour toujours - il y a une affaire importante à régler. Longway espère revenir une fois que ce sera fait.";
			link.l1 = "Quelle est cette affaire ? Dis-moi - sinon en tant que ton capitaine, alors en tant que quelqu'un qui a traversé beaucoup de choses avec toi.";
			link.l1.go = "PZ_Longway_15";
		break;
		
		case "PZ_Longway_15":
			dialog.text = "Tout ce que Longway peut dire, c'est qu'il a fait un vœu - il y a longtemps. Le moment est venu de le tenir. Sinon... il n'y a aucun sens à la vie de Longway.";
			link.l1 = "Tu as raison, Longway - tu n'es pas un prisonnier, et je ne suis pas un geôlier. Tu es libre de partir. Bon vent.";
			link.l1.go = "PZ_Longway_Otpustit_1";
			link.l2 = "Tu peux partir, mais dis-moi au moins où tu te diriges. Je pourrais aider sans poser trop de questions.";
			link.l2.go = "PZ_Longway_Pomoch_1";
			link.l3 = "J'ai une tâche importante aussi - sauver mon frère. Pour cela, j'ai besoin de chaque homme, y compris toi, Longway. Nous ne pouvons pas le faire sans toi.";
			link.l3.go = "PZ_Longway_NeOtpuskaem_1";
		break;
		
		case "PZ_Longway_NeOtpuskaem_1":
			dialog.text = "N’essaie pas de jouer sur ma pitié ou mon sens du devoir. Je comprends parfaitement. As-tu déjà prêté serment, Monseigneur le Capitaine ?";
			link.l1 = "Bien sûr que je l'ai fait. Alors dis-moi tout tel quel, et mes hommes et moi vous aiderons certainement.";
			link.l1.go = "PZ_Longway_NeOtpuskaem_2";
		break;
		
		case "PZ_Longway_NeOtpuskaem_2":
			dialog.text = "Longway ne peut pas. Juste... pas. C'est un grand mystère, et même pas le mien à partager.";
			link.l1 = "C'est dommage. Je pensais qu'il y avait de la confiance entre nous. Tu ne quittes pas le navire - j'ai tous les officiers de mon côté maintenant.";
			link.l1.go = "PZ_Longway_NeOtpuskaem_3";
			link.l2 = "Tu as raison, Longway - tu n'es pas un prisonnier, et je ne suis pas un geôlier. Tu es libre de partir. Bon vent.";
			link.l2.go = "PZ_Longway_Otpustit_1";
		break;
		
		case "PZ_Longway_NeOtpuskaem_3":
			dialog.text = "Tu ne peux pas faire ça !";
			link.l1 = "Malheureusement, je le peux, Longway. Maintenant, retourne à tes devoirs.";
			link.l1.go = "PZ_Longway_NeOtpuskaem_4";
		break;
		
		case "PZ_Longway_NeOtpuskaem_4":
			DialogExit();
			
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			LAi_SetOfficerType(npchar);
			npchar.Dialog.Filename = "Quest\HollandGambit\Longway.c";
			npchar.Dialog.CurrentNode = "Longway_officer";
			
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			
			PChar.quest.PZ_LongwayUhoditOtNasNavsegda.win_condition.l1 = "MapEnter";
			PChar.quest.PZ_LongwayUhoditOtNasNavsegda.win_condition = "PZ_LongwayUhoditOtNasNavsegda";
		break;
		
		case "PZ_Longway_Otpustit_1":
			dialog.text = "Je ne pensais pas que vous me laisseriez partir si facilement. Merci, Monseigneur le Capitaine.";
			link.l1 = "Ah, ce n'est rien. Mais dis-moi - où puis-je te trouver une fois que tes affaires seront terminées ?";
			link.l1.go = "PZ_Longway_GdeIskat_1";
		break;
		
		case "PZ_Longway_Pomoch_1":
			dialog.text = "Longway ne peut vraiment pas dire, peu importe combien il aimerait pouvoir. Mais il apprécie la volonté du Monseigneur le Capitaine d'aider.";
			link.l1 = "Ainsi soit-il. Où devrais-je te chercher une fois que tu auras tenu ta promesse ?";
			link.l1.go = "PZ_Longway_GdeIskat_1";
			pchar.questTemp.PZ_LongwayGood = true;
		break;
		
		case "PZ_Longway_GdeIskat_1":
			dialog.text = "Je m'attends à terminer mes affaires en un mois. Après cela, Longway t'attendra encore une semaine à la taverne de Basse-Terre.";
			link.l1 = "Eh bien, quoi que tu dises, mon ami. Ce n'est pas un adieu. À bientôt à Basse-Terre.";
			link.l1.go = "PZ_Longway_GdeIskat_2";
		break;
		
		case "PZ_Longway_GdeIskat_2":
			DialogExit();
			
			RemovePassenger(pchar, npchar);
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);
			LAi_SetImmortal(npchar, true);
			npchar.location = "None";
			
			SetQuestHeader("PZ");
			AddQuestRecord("PZ", "1");
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			
			SetTimerCondition("PZ_IshemLongway", 0, 0, 30, false);
		break;
		
		case "PZ_SharliePlennik_BadFinal_1":
			dialog.text = "Eh bien, bonjour, Capitaine.";
			link.l1 = "Je n'aime pas votre sourire en coin, monsieur.";
			link.l1.go = "PZ_SharliePlennik_BadFinal_2";
		break;
		
		case "PZ_SharliePlennik_BadFinal_2":
			dialog.text = "Je suis dévasté. Je suis venu te dire que tu es enfin libre. Mais si tu veux rester plus longtemps dans cette cabine luxueuse, tu es le bienvenu.";
			link.l1 = "Pas du tout. Alors, Longway a été trouvé ? Où est-il ? Dans l'une des cellules ?";
			link.l1.go = "PZ_SharliePlennik_BadFinal_3";
		break;
		
		case "PZ_SharliePlennik_BadFinal_3":
			dialog.text = "Dans un autre monde, en effet - il ne nous adresserait pas la parole et irait directement au combat.";
			link.l1 = "Merde ! Tu aurais pu simplement le capturer.";
			link.l1.go = "PZ_SharliePlennik_BadFinal_4";
		break;
		
		case "PZ_SharliePlennik_BadFinal_4":
			dialog.text = "Il y a des gens qu'il est bien plus facile de tuer que de capturer, tu sais ? Tu devrais être heureux qu'on ne te reproche rien - ton Chinois a provoqué un autre massacre, et il nous a fallu plusieurs unités supplémentaires avec des tireurs d'élite pour s'en occuper.";
			link.l1 = "Oui, en effet. Merci pour cela.";
			link.l1.go = "PZ_SharliePlennik_BadFinal_5";
		break;
		
		case "PZ_SharliePlennik_BadFinal_5":
			dialog.text = "En parlant de ça, comme c'était ton ami, nous avons trouvé quelques papiers sur lui. Nous n'avons pas compris ce que c'était - tu saurais probablement mieux que nous. Il y avait des charabias écrits sur les parties non couvertes de sang.";
			link.l1 = "C'est... Merde. Merci de les avoir ramenés. Au revoir, officier.";
			link.l1.go = "PZ_SharliePlennik_BadFinal_6";
		break;
		
		case "PZ_SharliePlennik_BadFinal_6":
			DialogExit();
			
			LAi_ActorGoToLocator(npchar, "goto", "goto22", "", -1);
			DoQuestCheckDelay("PZ_SharliePlennik_BadFinal_2", 3.0);
		break;
		
		case "PZ_BasTerStop":
			dialog.text = "Venez avec nous, le Commandant souhaite vous parler.";
			link.l1 = "Je suppose que cela a à voir avec ma recherche du Chinois ?";
			link.l1.go = "PZ_BasTerStop_2";
		break;
		
		case "PZ_BasTerStop_2":
			dialog.text = "Vous verrez par vous-même, monsieur.";
			link.l1 = "Suis-je accusé de quelque chose ?";
			link.l1.go = "PZ_BasTerStop_3";
		break;
		
		case "PZ_BasTerStop_3":
			dialog.text = "Pas du tout. Personne n'essaie de vous arrêter ou de vous détenir. Pour l'instant. Quand j'ai dit que le Commandant souhaitait vous parler, je voulais dire exactement cela.";
			link.l1 = "Oh, eh bien...";
			link.l1.go = "PZ_BasTerStop_4";
		break;
		
		case "PZ_BasTerStop_4":
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation("BasTer_town")], false);
			DoQuestReloadToLocation("BasTer_prison", "goto", "goto17", "PZ_BasTer_TurmaPriveli");
		break;
		
		case "PZ_BasTer_OtryadPeshera_1":
			dialog.text = "As-tu des idées ? Cet homme à la peau jaune est mortellement dangereux. Nous ne sommes pas le premier groupe envoyé ici. Les ordres sont les ordres, mais je ne veux pas mourir bêtement en y allant sans un plan solide.";
			if (CheckAttribute(pchar, "questTemp.PZ_OhotnikOtryad"))
			{
				link.l1 = "Il est tout seul là-dedans, et je suis avec vous. Je m'occupe de lui - concentrez-vous à me couvrir. On va y arriver.";
				link.l1.go = "PZ_BasTer_OtryadPeshera_2";
				if (pchar.location.from_sea != "BasTer_Town")
				{
					link.l2 = "J'en ai un. Vous allez tous mourir ici-même.";
					link.l2.go = "PZ_BasTer_OtryadPeshera_Kill_1";
				}
			}
			if (CheckAttribute(pchar, "questTemp.PZ_DrugOtryad"))
			{
				link.l1 = "Ne t'inquiète pas, nous allons juste lui parler.";
				link.l1.go = "PZ_BasTer_OtryadPeshera_2";
				if (pchar.location.from_sea != "BasTer_Town")
				{
					link.l2 = "Je suis désolé, mais vous allez tous mourir aujourd'hui. Et ce ne sera pas de la main d'un Chinois.";
					link.l2.go = "PZ_BasTer_OtryadPeshera_Kill_1";
				}
			}
		break;
		
		case "PZ_BasTer_OtryadPeshera_Kill_1":
			pchar.questTemp.PZ_Podelnik = true;
			if (CheckAttribute(pchar, "questTemp.PZ_OhotnikOtryad"))
			{
				dialog.text = "Alors tu n'es pas un chasseur de primes... Mais même si tu l'es, tu es un ami de ce fichu Chinois !";
				link.l1 = "C'est exact. Je devrais de toute façon me débarrasser de toi - il n'y a aucun intérêt à retarder l'inévitable.";
				link.l1.go = "PZ_BasTer_OtryadPeshera_Kill_2";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_DrugOtryad"))
			{
				dialog.text = "Que veux-tu dire ?! Tu as promis d'aider !";
				link.l1 = "Je pense que tu ne nous aurais pas laissé une issue pacifique de toute façon. Ce n'est rien de personnel.";
				link.l1.go = "PZ_BasTer_OtryadPeshera_Kill_2";
			}
		break;
		
		case "PZ_BasTer_OtryadPeshera_Kill_2":
			DialogExit();
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			chrDisableReloadToLocation = true;
			
			for (i=1; i<=4; i++)
			{
				sld = CharacterFromID("PZ_BasTer_OtryadPeshera"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			sld = CharacterFromID("PZ_BasTer_OtryadPesheraOff");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "PZ_BasTer_OtryadPeshera_Kill_3");
		break;
		
		case "PZ_BasTer_OtryadPeshera_2":
			if (CheckAttribute(pchar, "questTemp.PZ_OhotnikOtryad"))
			{
				dialog.text = "J'aimerais bien le croire.";
				link.l1 = "J'ai affronté pire. Un Chinois ne sera pas notre fin. Allons-y, les gars !";
				link.l1.go = "PZ_BasTer_OtryadPeshera_3";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_DrugOtryad"))
			{
				dialog.text = "Et si la conversation ne se passe pas comme prévu ?";
				link.l1 = "Je détesterais cela, mais alors je devrai me défendre. Allons-y.";
				link.l1.go = "PZ_BasTer_OtryadPeshera_3";
			}
		break;
		
		case "PZ_BasTer_OtryadPeshera_3":
			DialogExit();
			
			DoQuestReloadToLocation("Guadeloupe_CaveEntrance", "reload", "reload2", "PZ_IshemLongway_OtryadUPeshery");
		break;
		
		case "PZ_BasTer_SOtryadom_DialogLongway":
			dialog.text = "Monseigneur le Capitaine?! Longway ne peut pas croire que vous êtes avec eux!";
			link.l1 = "Non, Longway, je suis juste là pour parler ! Ce n'est pas ce que tu crois !";
			link.l1.go = "PZ_BasTer_SOtryadom_DialogLongway_2";
		break;
		
		case "PZ_BasTer_SOtryadom_DialogLongway_2":
			dialog.text = "Alors tu serais venu seul. Tu essaies de baisser ma garde pour m'attaquer avec l'aide de ces soldats !";
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayGood"))
			{
				link.l1 = "Si je pouvais, je le ferais. Je suis la seule raison pour laquelle ils ne t'ont pas encore attaqué. Calme-toi, et parlons-en, d'accord ?";
				link.l1.go = "PZ_BasTer_SOtryadom_DialogLongway_3";
			}
			else
			{
				link.l1 = "Arrête tes conneries ! Si je l'avais voulu, je t'aurais déjà tué. Déposez les armes, et on va discuter. C'est un ordre de votre capitaine.";
				link.l1.go = "PZ_BasTer_SOtryadom_DialogLongway_Bad_1";
			}
		break;
		
		case "PZ_BasTer_SOtryadom_DialogLongway_3":
			dialog.text = "Aye. Longway vous fait confiance, Monseigneur le Capitaine.";
			link.l1 = "Là, c'est mieux. Maintenant, dis-moi...";
			link.l1.go = "PZ_BasTer_SOtryadom_DialogLongway_4";
		break;
		
		case "PZ_BasTer_SOtryadom_DialogLongway_4":
			StartInstantDialog("PZ_BasTer_OtryadPesheraOff", "PZ_BasTer_SOtryadom_DialogLongway_5", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_BasTer_SOtryadom_DialogLongway_5":
			if (CheckAttribute(pchar, "questTemp.PZ_OhotnikOtryad"))
			{
				dialog.text = "Monsieur, que se passe-t-il ? Quelle est cette... réunion émotive ? Vous deviez nous aider à éliminer ce sauvage chinois, n'est-ce pas ?";
				link.l1 = "Je le suis. Je l'emmène avec moi, et tous ces meurtres cesseront. Tu diras au commandant que nous l'avons tué ensemble. Marché conclu ?";
				link.l1.go = "PZ_BasTer_SOtryadomOhotnik_1";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_DrugOtryad"))
			{
				dialog.text = "Bien joué, Capitaine ! Il a déposé ses armes. C'est bon de vous avoir avec nous. Maintenant, emmenons-le chez le commandant.";
				link.l1 = "Pourquoi ferais-je cela ? J'ai payé une amende en or pour les actions de Longway - une amende généreuse. Vos collègues officiers étaient témoins - ils le confirmeront. Le commandant m'a autorisé à emmener mon homme avec moi sur le navire.";
				link.l1.go = "PZ_BasTer_SOtryadomDrug_1";
			}
		break;
		
		case "PZ_BasTer_SOtryadomDrug_1":
			dialog.text = "Le commandant pourrait en avoir assez de cet or ensanglanté, mais pas moi. Certains des hommes qu'il a tués dans cette caverne sanglante étaient mes amis. De plus, je doute qu'il se soucie si nous tuons le Chinois de toute façon.";
			link.l1 = "Tu es sûr de vouloir le savoir ? Et à propos de tes amis qui ont été tués... tu as déjà entendu parler de cette bande de brigands effrontés ? Ça devait être eux.";
			link.l1.go = "PZ_BasTer_SOtryadomDrug_2";
		break;
		
		case "PZ_BasTer_SOtryadomDrug_2":
			StartInstantDialog("Longway", "PZ_BasTer_SOtryadomDrug_3", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_BasTer_SOtryadomDrug_3":
			dialog.text = "";
			link.l1 = "Longway, tu n'as pas tué autant de soldats qu'ils prétendent, n'est-ce pas ?";
			link.l1.go = "PZ_BasTer_SOtryadomDrug_4";
		break;
		
		case "PZ_BasTer_SOtryadomDrug_4":
			dialog.text = "C'est exact, Monseigneur le Capitaine. Longway a vu cette bande. Ils se sont cachés plus profondément dans la grotte pour qu'ils ne le remarquent pas. Et Longway a entendu des sons de conversation, de jurons et de combats entre les bandits et les soldats.";
			link.l1 = "";
			link.l1.go = "PZ_BasTer_SOtryadomDrug_5";
		break;
		
		case "PZ_BasTer_SOtryadomDrug_5":
			StartInstantDialog("PZ_BasTer_OtryadPesheraOff", "PZ_BasTer_SOtryadomDrug_6", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_BasTer_SOtryadomDrug_6":
			dialog.text = "";
			link.l1 = "Tu vois ? Tout s'emboîte. Longway peut avoir un tempérament, mais c'est un homme honnête. Nous partons. Si vous nous touchez, vous déshonorerez votre uniforme. Adieu, messieurs.";
			link.l1.go = "PZ_BasTer_SOtryadomDrug_7";
		break;
		
		case "PZ_BasTer_SOtryadomDrug_7":
			DialogExit();
			
			AddQuestRecord("PZ", "13");
			LAi_LocationFightDisable(&Locations[FindLocation("Guadeloupe_CaveEntrance")], false);
			chrDisableReloadToLocation = false;
			bDisableLandEncounters = false;
			LAi_LocationDisableOfficersGen("Guadeloupe_jungle_02", false);
			LAi_LocationDisableOfficersGen("Guadeloupe_CaveEntrance", false);
			//LAi_LocationDisableOfficersGen("Guadeloupe_Cave", false);
			
			for (i=1; i<=5; i++)
			{
				sld = CharacterFromID("PZ_BasTer_OtryadPeshera"+i);
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "PZ_BasTer_OtryadRazveli", -1);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				LAi_CharacterDisableDialog(sld);
			}
			sld = CharacterFromID("PZ_BasTer_OtryadPesheraOff");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "PZ_BasTer_OtryadRazveli", -1);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			LAi_CharacterDisableDialog(sld);
			
			sld = CharacterFromID("Longway");
			AddPassenger(pchar, sld, false);
			LAi_SetImmortal(sld, false);
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			sld.Dialog.Filename = "Quest\HollandGambit\Longway.c";
			sld.Dialog.CurrentNode = "Longway_officer";
			
			DeleteQuestCondition("PZ_LongwayNelzyaUmeret");
			
			//Продолжение второго этапа
			PChar.quest.PZ_LongwayRazgovorVKaute.win_condition.l1 = "EnterToSea"
			PChar.quest.PZ_LongwayRazgovorVKaute.win_condition = "PZ_LongwayRazgovorVKaute";
		break;
		
		case "PZ_BasTer_SOtryadomOhotnik_1":
			dialog.text = "Aucun moyen, monsieur ! Il a tué un tas de nos hommes, et maintenant vous dites qu'il s'en tirera comme ça ?! Soit vous nous aidez à tuer ce salaud, soit au moins restez en dehors de notre chemin !";
			link.l1 = "J'ai bien peur de devoir intervenir. Je suis désolé, vraiment.";
			link.l1.go = "PZ_BasTer_SOtryadomOhotnik_2";
		break;
		
		case "PZ_BasTer_SOtryadomOhotnik_2":
			DialogExit();
			
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
			LAi_SetFightMode(pchar, true);
			
			sld = CharacterFromID("Longway");
			LAi_SetImmortal(sld, false);
			DeleteAttribute(sld, "OfficerImmortal");
			if(CheckAttribute(sld, "Health.HP")) DeleteAttribute(sld, "Health.HP");
			if(CheckAttribute(sld, "Health.maxHP")) DeleteAttribute(sld, "Health.maxHP");
			sTemp = "RestoreHealth_" + sld.index;
			if(CheckAttribute(PChar, "quest.RestoreHealth_" + sld.index)) PChar.quest.(sTemp).over = "Yes";
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			
			for (i=1; i<=5; i++)
			{
				sld = CharacterFromID("PZ_BasTer_OtryadPeshera"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				LAi_CharacterDisableDialog(sld);
			}
			sld = CharacterFromID("PZ_BasTer_OtryadPesheraOff");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_CharacterDisableDialog(sld);
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "PZ_IshemLongway_Zastupaemsya");
			
			PChar.quest.PZ_LongwayNelzyaUmeret.win_condition.l1 = "NPC_Death";
			PChar.quest.PZ_LongwayNelzyaUmeret.win_condition.l1.character = "Longway";
			PChar.quest.PZ_LongwayNelzyaUmeret.win_condition = "PZ_LongwayNelzyaUmeret";
		break;
		
		case "PZ_BasTer_SOtryadom_DialogLongway_Bad_1":
			dialog.text = "Si tu voulais juste parler, tu ne me demanderais pas de désarmer. Mais un tigre reste un tigre, même avec les griffes rétractées. Tu as dû déjà décider de trahir Longway depuis longtemps - pas besoin de mentir. Défends-toi, Capitaine !";
			link.l1 = "Merde !";
			link.l1.go = "PZ_BasTer_SOtryadom_DialogLongway_Bad_2";
		break;
		
		case "PZ_BasTer_SOtryadom_DialogLongway_Bad_2":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation("Guadeloupe_CaveEntrance")], false);
			LAi_SetFightMode(pchar, true);
			
			for (i=1; i<=5; i++)
			{
				sld = CharacterFromID("PZ_BasTer_OtryadPeshera"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				LAi_CharacterDisableDialog(sld);
			}
			
			sld = CharacterFromID("Longway");
			LAi_SetImmortal(sld, false);
			DeleteAttribute(sld, "OfficerImmortal");
			if(CheckAttribute(sld, "Health.HP")) DeleteAttribute(sld, "Health.HP");
			if(CheckAttribute(sld, "Health.maxHP")) DeleteAttribute(sld, "Health.maxHP");
			sTemp = "RestoreHealth_" + sld.index;
			if(CheckAttribute(PChar, "quest.RestoreHealth_" + sld.index)) PChar.quest.(sTemp).over = "Yes";
			sld.SaveItemsForDead = true;
			sld.DontClearDead = true;
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "PZ_BasTer_MyUbilLongway_BadFinal");
		break;
		
		case "PZ_BasTer_SOtryadom_UbiliLongway":
			if (CheckAttribute(pchar, "questTemp.PZ_OhotnikOtryad"))
			{
				dialog.text = "Je n'arrive pas à croire qu'on s'en soit sorti avec lui ! Mais dis-moi, pourquoi t'a-t-il appelé Capitaine ?";
				link.l1 = "C'est plus compliqué qu'il n'y paraît, camarade. J'avais besoin de rassurer votre commandant. L'important, c'est le résultat, n'est-ce pas ? Et le résultat, c'est que Longway est mort, et je vous ai aidé pour ça.";
				link.l1.go = "PZ_BasTer_SOtryadom_UbiliLongway_2";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_DrugOtryad"))
			{
				dialog.text = " Même ta présence n'a pas aidé - il nous a quand même attaqués. Maudit sauvage...";
				link.l1 = "Tu ne devrais pas parler de lui comme ça. Il nous a attaqués parce qu'il était contrarié et pensait que j'étais avec toi.";
				link.l1.go = "PZ_BasTer_SOtryadom_UbiliLongway_2";
			}
		break;
		
		case "PZ_BasTer_SOtryadom_UbiliLongway_2":
			if (CheckAttribute(pchar, "questTemp.PZ_OhotnikOtryad"))
			{
				dialog.text = "Peut-être. Dans ce cas, adieu, monsieur. Nous dirons nous-mêmes au commandant que le Chinois est enfin mort.";
				link.l1 = "Très bien, merci. Au revoir, les gars.";
				link.l1.go = "PZ_BasTer_SOtryadom_UbiliLongway_3";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_DrugOtryad"))
			{
				dialog.text = "Eh bien, fâché ou non, sauvage ou non, cela ne change rien - il a tué beaucoup des nôtres avant, a versé le sang en premier.";
				link.l1 = "Quelque chose a dû le pousser dans cet état. Mais ne nous attardons pas là-dessus. Je vais y aller, et vous pourrez retourner voir le commandant quand bon vous semblera. Adieu.";
				link.l1.go = "PZ_BasTer_SOtryadom_UbiliLongway_3";
			}
		break;
		
		case "PZ_BasTer_SOtryadom_UbiliLongway_3":
			DialogExit();
			
			LAi_SetWarriorType(npchar);
			LAi_CharacterDisableDialog(npchar);
			ChangeCharacterNationReputation(pchar, FRANCE, 12);
			AddQuestRecord("PZ", "11");
			CloseQuestHeader("PZ");
			
			LAi_LocationDisableOfficersGen("Guadeloupe_jungle_02", false);
			LAi_LocationDisableOfficersGen("Guadeloupe_CaveEntrance", false);
			//LAi_LocationDisableOfficersGen("Guadeloupe_Cave", false);
			chrDisableReloadToLocation = false;
			bDisableLandEncounters = false;
		break;
		
		case "PZ_IshemLongway_SorraKomendant_Dialog":
			dialog.text = "Monseigneur le Capitaine ?";
			link.l1 = "Aye ! Je t'ai cherché partout, Longway. Tu as causé pas mal de remue-ménage en ville. Nous avons beaucoup à discuter, alors retournons immédiatement au navire.";
			link.l1.go = "PZ_IshemLongway_SorraKomendant_Dialog_2";
		break;
		
		case "PZ_IshemLongway_SorraKomendant_Dialog_2":
			dialog.text = "Là-bas !";
			link.l1 = "Je vois que nous avons de la compagnie. On dirait que nous allons être un peu en retard.";
			link.l1.go = "PZ_IshemLongway_SorraKomendant_Dialog_3";
			locCameraFromToPos(-12.27, 1.29, -8.89, true, -3.23, -1.20, -4.77);
			DoQuestCheckDelay("PZ_IshemLongway_SorraKomendant_Dialog_Povernutsya", 1.3);
			
			for (i=1; i<=5; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("PZ_BasTer_OtryadPeshera"+i, "sold_fra_"+(rand(7)+1), "man", "man", sti(pchar.rank), FRANCE, 0, true, "soldier"));
				ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload2");
				LAi_SetActorType(sld);
				LAi_ActorFollow(sld, pchar, "", -1);
				LAi_SetHP(sld, 60.0, 60.0);
			}
		break;
		
		case "PZ_IshemLongway_SorraKomendant_Dialog_3":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation("Guadeloupe_CaveEntrance")], false);
			LAi_SetFightMode(pchar, true);
			
			sld = CharacterFromID("Longway");
			LAi_SetImmortal(sld, false);
			DeleteAttribute(sld, "OfficerImmortal");
			if(CheckAttribute(sld, "Health.HP")) DeleteAttribute(sld, "Health.HP");
			if(CheckAttribute(sld, "Health.maxHP")) DeleteAttribute(sld, "Health.maxHP");
			sTemp = "RestoreHealth_" + sld.index;
			if(CheckAttribute(PChar, "quest.RestoreHealth_" + sld.index)) PChar.quest.(sTemp).over = "Yes";
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			
			for (i=1; i<=5; i++)
			{
				sld = CharacterFromID("PZ_BasTer_OtryadPeshera"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "PZ_IshemLongway_SorraKomendant_Pobeda1");
			
			PChar.quest.PZ_LongwayNelzyaUmeret.win_condition.l1 = "NPC_Death";
			PChar.quest.PZ_LongwayNelzyaUmeret.win_condition.l1.character = "Longway";
			PChar.quest.PZ_LongwayNelzyaUmeret.win_condition = "PZ_LongwayNelzyaUmeret";
		break;
		
		case "PZ_IshemLongway_SorraKomendant_Dialog_4":
			dialog.text = "Encore d'autres arrivent !";
			link.l1 = "Sales obstines - je leur concède ça. Nous sommes trop exposés ici. Allons à la grotte - il sera plus facile de nous défendre.";
			link.l1.go = "PZ_IshemLongway_SorraKomendant_Dialog_5";
		break;
		
		case "PZ_IshemLongway_SorraKomendant_Dialog_5":
			DialogExit();
			pchar.questTemp.PZ_IshemLongway_SorraKomendant = true;
			PlaySound("Interface\MusketFire1.wav");
			PlaySound("Interface\MusketFire1.wav");
			PlaySound("Interface\MusketFire1.wav");
			
			sld = CharacterFromID("Longway");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "Guadeloupe_Cave", "goto", "locator1", "PZ_IshemLongway_VPesheru", -1);
			
			LAi_SetActorType(pchar);
			LAi_ActorRunToLocation(pchar, "reload", "reload1", "Guadeloupe_Cave", "goto", "locator1", "PZ_IshemLongway_VPesheru", -1);
		break;
		
		case "PZ_IshemLongway_SorraKomendant_Dialog_6":
			dialog.text = "Nous ne pouvons pas rester ici éternellement.";
			link.l1 = "Et c'est la première chose que tu veux dire après tout ce qui s'est passé, Longway ? Ne penses-tu pas qu'il est temps d'expliquer ce qui se passe ?";
			link.l1.go = "PZ_IshemLongway_SorraKomendant_Dialog_7";
		break;
		
		case "PZ_IshemLongway_SorraKomendant_Dialog_7":
			dialog.text = "Monseigneur le Capitaine, Longway...";
			link.l1 = "Mais tu as raison - nous ne pouvons pas rester. Allons-y avant qu'une autre escouade n'arrive. Nous parlerons sur le navire une fois que nous aurons levé l'ancre.";
			link.l1.go = "PZ_IshemLongway_SorraKomendant_Dialog_8";
		break;
		
		case "PZ_IshemLongway_SorraKomendant_Dialog_8":
			DoQuestReloadToLocation("Guadeloupe_CaveEntrance", "reload", "reload1", "PZ_IshemLongway_VyhodIsPeshery");
		break;
		
		case "PZ_IshemLongway_Zastupaemsya_1":
			dialog.text = "La ruse et la malveillance de l'homme blanc ne connaissent pas de limites.";
			link.l1 = "Hé, je suis un homme blanc aussi ! De plus, tu as tué leurs amis et camarades soldats - ils ont le droit d'être en colère.";
			link.l1.go = "PZ_IshemLongway_Zastupaemsya_2";
		break;
		
		case "PZ_IshemLongway_Zastupaemsya_2":
			dialog.text = "Les absous-tu, Monseigneur le Capitaine ?";
			link.l1 = "Je t'absous, Longway. Et je t’exhorte à ne pas juger les gens par la couleur de leur peau. Toi mieux que quiconque devrais comprendre cela. Nous avons été interrompus - où en étions-nous...?";
			link.l1.go = "PZ_IshemLongway_Zastupaemsya_3";
		break;
		
		case "PZ_IshemLongway_Zastupaemsya_3":
			dialog.text = "Capitaine ! Derrière vous !";
			link.l1 = "Oh, ils ne vont pas nous laisser avoir une vraie conversation aujourd'hui...";
			link.l1.go = "PZ_IshemLongway_Zastupaemsya_4";
		break;
		
		case "PZ_IshemLongway_Zastupaemsya_4":
			DialogExit();
			LAi_SetCurHPMax(pchar);
			LAi_GetCharacterMaxEnergy(pchar);
			LAi_SetCurHPMax(sld);
			LAi_GetCharacterMaxEnergy(sld);
			
			sld = CharacterFromID("Longway");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			
			for (i=6; i<=10; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("PZ_BasTer_OtryadPeshera"+i, "sold_fra_"+(rand(7)+1), "man", "man", sti(pchar.rank), FRANCE, 0, true, "soldier"));
				ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload2");
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				LAi_SetHP(sld, 60.0, 60.0);
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "PZ_IshemLongway_Zastupaemsya_5");
			
			AddDialogExitQuest("MainHeroFightModeOn"); // Rebbebion, fix
		break;
		
		case "PZ_IshemLongway_Zastupaemsya_6":
			dialog.text = "Clair, Monseigneur le Capitaine.";
			link.l1 = "C'est bien, mais ne traînons pas ici. Toi et moi avons beaucoup à discuter. Suis-moi - nous retournons au navire.";
			link.l1.go = "PZ_IshemLongway_Zastupaemsya_7";
		break;
		
		case "PZ_IshemLongway_Zastupaemsya_7":
			DialogExit();
			
			sld = CharacterFromID("Longway");
			AddPassenger(pchar, sld, false);
			sld.OfficerImmortal = true;
			sld.Health.HP       = 60.0;
			sld.Health.maxHP    = 60.0;
			SetCharacterPerk(sld, "ShipEscape");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			sld.Dialog.Filename = "Quest\HollandGambit\Longway.c";
			sld.Dialog.CurrentNode = "Longway_officer";
			
			LAi_LocationDisableOfficersGen("Guadeloupe_jungle_02", false);
			LAi_LocationDisableOfficersGen("Guadeloupe_CaveEntrance", false);
			//LAi_LocationDisableOfficersGen("Guadeloupe_Cave", false);
			chrDisableReloadToLocation = false;
			bDisableLandEncounters = false;
			AddQuestRecord("PZ", "14");
			DeleteQuestCondition("PZ_LongwayNelzyaUmeret");
			DeleteQuestCondition("PZ_KorablBuhta_BadFinal");
			
			//Продолжение второго этапа
			PChar.quest.PZ_LongwayRazgovorVKaute.win_condition.l1 = "EnterToSea"
			PChar.quest.PZ_LongwayRazgovorVKaute.win_condition = "PZ_LongwayRazgovorVKaute";
		break;
		
		case "PZ_IshemLongway_SrazuNashli_1":
			dialog.text = "Monseigneur le Capitaine, est-ce vraiment vous...?";
			link.l1 = "Oui, Longway. Tout va bien ?";
			link.l1.go = "PZ_IshemLongway_SrazuNashli_2";
		break;
		
		case "PZ_IshemLongway_SrazuNashli_2":
			dialog.text = "Longway va bien. Merci. Mais, Capitaine ! Regardez !";
			link.l1 = "Courez à la grotte, vite ! C'est une bonne position défensive !";
			link.l1.go = "PZ_IshemLongway_SrazuNashli_3";
		break;
		
		case "PZ_IshemLongway_SrazuNashli_3":
			DialogExit();
			PlaySound("Interface\MusketFire1.wav");
			PlaySound("Interface\MusketFire1.wav");
			PlaySound("Interface\MusketFire1.wav");
			
			sld = CharacterFromID("Longway");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "Guadeloupe_Cave", "goto", "locator1", "PZ_IshemLongway_VPesheru", -1);
			
			LAi_SetActorType(pchar);
			LAi_ActorRunToLocation(pchar, "reload", "reload1", "Guadeloupe_Cave", "goto", "locator1", "PZ_IshemLongway_VPesheru", -1);
		break;
		
		case "PZ_IshemLongway_SrazuNashli_4":
			dialog.text = "Longway vérifiera si les soldats arrivent toujours.";
			link.l1 = "Nous irons ensemble - nous ne pouvons pas tenir notre défense contre toute la garnison.";
			link.l1.go = "PZ_IshemLongway_SrazuNashli_5";
		break;
		
		case "PZ_IshemLongway_SrazuNashli_5":
			dialog.text = "Oui, Monseigneur le Capitaine ?";
			link.l1 = "Nous avons beaucoup à discuter. Maintenant, suis-moi - nous devons lever l'ancre immédiatement.";
			link.l1.go = "PZ_IshemLongway_SrazuNashli_6";
		break;
		
		case "PZ_IshemLongway_SrazuNashli_6":
			DoQuestReloadToLocation("Guadeloupe_CaveEntrance", "reload", "reload1", "PZ_IshemLongway_VyhodIsPeshery");
		break;
		
		// Этап 2, СТРАНИЦЫ ИСТОРИИ
		case "PZ_LongwayRazgovorOProshlom":
			dialog.text = "Je vous remercie encore une fois pour votre aide, Monseigneur le Capitaine. Je suis sûr que vous avez beaucoup de questions.";
			link.l1 = "C'est peu dire. Pourquoi as-tu tué ces soldats ? Tu ne tues pas pour le plaisir-je le sais.";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_LongwayRazgovorOProshlom_2":
			dialog.text = "Non, Longway ne le fait pas. Les soldats ont essayé d'arrêter Longway, et la prison n'était pas une option. Ils n'écouteraient pas un Chinois - seul un homme blanc obtient cette courtoisie.";
			link.l1 = "Ils n'écoutent pas toujours les autres Blancs non plus, mais je comprends ton point de vue. Cependant, les massacrer comme du bétail en ville ? Que faisiez-vous à Basse-Terre ?";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_3";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_3":
			dialog.text = "Not only do white people often not listen to me; sometimes they won't even talk. And when they do, it's to call the guards. Longway didn't choose his skin or his eyes, but he's proud of who he is. When soldiers mock and threaten, Longway grows tired... and angry.";
			link.l1 = "Désormais, travaillons ensemble. Les gens me parlent au lieu d'appeler les gardes... généralement. Mais sérieusement, parle-moi de ta mission. Laisse-moi t'aider.";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_4";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_4":
			dialog.text = "Je vous en prie, Monseigneur le Capitaine, comprenez Longway. Il a juré de faire cela seul. Ne le poussez pas. Vous devez bien ça à Longway.";
			link.l1 = "Je suis vraiment reconnaissant, mais j'aurais pu gérer van Merden moi-même à l'époque. Cependant, nous étions quittes dès le début - tu as dit que je t'ai sauvé la face, et tu m'as sauvé la vie. Maintenant je t'ai sauvé à nouveau.";
			if (CheckAttribute(pchar, "questTemp.PZ_NashliArhiv")) link.l1.go = "PZ_LongwayRazgovorOProshlom_5";
			else link.l1.go = "PZ_LongwayRazgovorOProshlom_Grubim_1";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_5":
			dialog.text = "Hmm... tu as raison, Monseigneur le Capitaine. Longway croit que tu es son véritable ami parmi les hommes blancs. Une fois, il l’a cru auparavant, mais il s’est amèrement trompé. Te souviens-tu de John Murdock ? Johan van Merden ?";
			link.l1 = "Comme c'est étrange que vous mentionniez van Merden. Récemment, quelqu'un a arraché quelques pages de son archive juste sous mon nez. Cela avait-il un lien avec votre affaire ? Avez-vous trouvé le voleur ?";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_6";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_6":
			dialog.text = "Je l'ai fait. Le voleur était... Longway. Il est très désolé, Monseigneur le Capitaine. À l'époque, il ne savait pas s'il pouvait vous faire entièrement confiance.";
			if (sti(pchar.reputation.nobility) <= 60)
			{
				link.l1 = "Tu parles d’amitié, mais tu me voles dans le dos ? C’est la première et dernière fois, Longway. Comprends-tu ?";
				link.l1.go = "PZ_LongwayRazgovorOProshlom_Grubim_1";
				notification("Reputation Too Low! ("+XI_ConvertString(GetReputationName(61))+")", "None");
			}
			else
			{
				link.l1 = "Et comment as-tu réussi à faire cela, Longway ?";
				link.l1.go = "PZ_LongwayRazgovorOProshlom_Proshaem_1";
				notification("Reputation Check Passed", "None");
			}
		break;
		
		case "PZ_LongwayRazgovorOProshlom_Grubim_1":
			dialog.text = "Longway comprend. Il le pense vraiment.";
			link.l1 = "J'espère bien. Maintenant, dis-moi comment tu en es arrivé à cette vie - quelle promesse tu as faite, quand et à qui.";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_Grubim_2";
			if (CheckAttribute(pchar, "questTemp.PZ_NashliArhiv")) AddComplexSelfExpToScill(100, 100, 100, 100);
			notification("Longway disapproves", "Longway");
		break;
		
		case "PZ_LongwayRazgovorOProshlom_Grubim_2":
			dialog.text = "Oui, Monseigneur le Capitaine\nLongway recherche la personne vivante la plus importante pour lui - Chang Xing.";
			link.l1 = "Chang Xing-est-il ton meilleur ami ?";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_7";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_Proshaem_1":
			dialog.text = "Grâce à ta gentillesse, le reste de l'équipage s'est rapidement habitué à moi et a commencé à me faire confiance.";
			link.l1 = "Eh bien, je comprends. Pas du genre à recevoir des louanges, mais bon travail, Longway... si tu as nettoyé le bazar que ton intrusion a laissé.";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_Proshaem_2";
			AddComplexLandExpToScill(200, 200, 0);
			pchar.questTemp.PZ_FlagArhiv = true;
			notification("Longway approves", "Longway");
		break;
		
		case "PZ_LongwayRazgovorOProshlom_Proshaem_2":
			dialog.text = "D'accord. Mais nous n'avons pas le temps pour ça.";
			link.l1 = "Je suppose que non. Mais essaie de ne pas refaire ça, d'accord ? Si tu as besoin de quoi que ce soit, demande-moi. Tu peux me faire confiance. Maintenant, parle-moi de ton serment.";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_Proshaem_3";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_Proshaem_3":
			dialog.text = "Bien sûr, Longway est heureux de partager son fardeau avec vous, Monseigneur le Capitaine.\nLongway cherche la personne vivante la plus importante qu'il lui reste - Chang Xing.";
			link.l1 = "Chang Xing - est-il ton meilleur ami ?";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_7";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_7":
			dialog.text = "Chang Xing est ma famille, ma soeur. Elle a disparu il y a des années. Pour la retrouver, Longway cherche ceux qui pourraient savoir où elle se trouve.";
			link.l1 = "Quel rapport cela a-t-il avec les archives de van Merden ? Est-ce lié à la disparition de ta sœur ?";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_8";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_8":
			dialog.text = "C'est ça. Tout est lié. Longway et Johan se sont rencontrés il y a de nombreuses années, dans le pays que vous appelez Formose, bien avant que je ne vienne dans l'Archipel.";
			link.l1 = "Vous vous connaissez depuis tant d'années ? Et van Merden était impliqué ? Quelle histoire ! Quel était son lien avec la disparition de votre sœur ?";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_9";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_9":
			dialog.text = "Il m'a aidé dans ma quête de gens vraiment mauvais - même selon les normes des hommes blancs. Oliveiro Fermentelos, Antoon van Diemen, et Joep van der Vink.";
			link.l1 = "À en juger par leurs noms, l'un est Portugais et les deux autres sont Néerlandais.";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_10";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_10":
			dialog.text = "Oui, c'est correct. Mais la recherche n'a pas réussi. Longway attendait patiemment la guidance céleste. Alors, quand tu as obtenu les archives de van Merden, j'ai décidé de les étudier. Quand j'ai trouvé les premières pages mentionnant Oliveiro, je les ai arrachées et me suis enfui de la cabine.";
			link.l1 = "Tout s'intègre enfin dans l'histoire.";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_11";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_11":
			dialog.text = "Mais l'histoire elle-même ne fait que commencer. Monseigneur le Capitaine, aimeriez-vous connaître la quête de Longway depuis le tout début ? Êtes-vous prêt à vous asseoir et écouter ?";
			link.l1 = "C'est exactement pourquoi je vous ai appelé dans la cabine. Allez-y.";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_12";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_12":
			DialogExit();
			
			SetCurrentTime(12, 00);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			SetMainCharacterIndex(GetCharacterIndex("Longway"));
			PChar = GetMainCharacter();
			LAi_SetPlayerType(PChar);
			DoQuestReloadToLocation("Formosa", "patrol", "patrol1", "PZ_Formosa_Start");
		break;
		
		case "PZ_Formosa_Tavern_1":
			dialog.text = "Les Chinetoques ne sont pas les bienvenus ici. C’est un établissement respectable, pour des gens respectables - pas pour des gens comme vous.";
			link.l1 = "Je n'ai qu'une seule question. Laisse-moi la poser, et je m'en irai.";
			link.l1.go = "PZ_Formosa_Tavern_2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_Formosa_Tavern_2":
			dialog.text = "Apprends d'abord à parler correctement ! Je t'ai dit - les tiens ne sont pas les bienvenus ici.";
			link.l1 = "Où puis-je trouver Oliveiro Fermentelos ? Dis-le-moi, et je serai en route.";
			link.l1.go = "PZ_Formosa_Tavern_3";
		break;
		
		case "PZ_Formosa_Tavern_3":
			dialog.text = "Es-tu sourd aussi ? Ne teste pas ma patience, ou toute cette pièce va bientôt puer les boyaux jaunes.";
			link.l1 = "Mon peuple a vécu ici pendant des milliers d'années. C'est notre île, et nous ne pouvons même pas entrer dans une simple taverne ?";
			link.l1.go = "PZ_Formosa_Tavern_4";
		break;
		
		case "PZ_Formosa_Tavern_4":
			dialog.text = "Oh, vous parlez fort, hein ? Vous pourriez être pendu pour ça. Sortez !";
			link.l1 = "...";
			link.l1.go = "PZ_Formosa_Tavern_5";
		break;
		
		case "PZ_Formosa_Tavern_5":
			DialogExit();
			locCameraSleep(true);
			LAi_CharacterDisableDialog(npchar);
			
			sld = CharacterFromID("PZ_Formosa_smuggler");
			LAi_CharacterEnableDialog(sld);
			//AddLandQuestMark(sld, "questmarkmain");
			LAi_Fade("PZ_Formosa1_9", "");
		break;
		
		case "PZ_Formosa_smuggler_1":
			dialog.text = "J'ai entendu parler de ton gros problème, mon petit ami. Tu n'aurais pas dû être si bruyant - mauvais nom, mauvais endroit.";
			link.l1 = "Tu sais quelque chose sur cet homme ?! Dis-moi !";
			link.l1.go = "PZ_Formosa_smuggler_2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_Formosa_smuggler_2":
			dialog.text = "Calme-toi, camarade.";
			link.l1 = "Mes excuses.";
			link.l1.go = "PZ_Formosa_smuggler_3";
		break;
		
		case "PZ_Formosa_smuggler_3":
			dialog.text = "Je ne veux pas de tes excuses, mais je veux bien ton argent. Peut-être qu’alors je t’aiderai. Je suis Marcelo Schulte. Et toi ? T’as de l’argent, non ?";
			link.l1 = "Je m'appelle Chang Tu. J'ai de l'argent. Est-ce suffisant ?";
			link.l1.go = "PZ_Formosa_smuggler_4";
		break;
		
		case "PZ_Formosa_smuggler_4":
			dialog.text = "(siffle) Escudos, pesos, florins, doublons... et même quelques-unes de ces pièces bizarres que vous avez. Cela fera l'affaire. D'accord, Chung Chung, je vais voir ce que je peux découvrir sur cet homme. Ne t'inquiète pas, je suis ici presque tous les jours, donc ton argent est en sécurité. Repasse tous les jours, et on se croisera sûrement.";
			link.l1 = "J'espère. Je n'ai plus d'argent...";
			link.l1.go = "PZ_Formosa_smuggler_5";
		break;
		
		case "PZ_Formosa_smuggler_5":
			DialogExit();
			LAi_SetStayType(pchar);
			pchar.GenQuest.FrameLockEsc = true;
			SetLaunchFrameFormParam("A few days have passed,"+ NewStr() +"April 4, 1645.", "Reload_To_Location", 0, 4.0);
			SetLaunchFrameReloadLocationParam("Formosa_tavern", "goto", "goto1", "PZ_Formosa_Spustya4Dnya");
			LaunchFrameForm();
		break;
		
		case "PZ_Formosa_smuggler_11":
			dialog.text = "Ah, Chang-Chang ! Tu es déjà là.";
			link.l1 = "C'est Chang Tu.";
			link.l1.go = "PZ_Formosa_smuggler_12";
		break;
		
		case "PZ_Formosa_smuggler_12":
			dialog.text = "Peu importe, camarade.";
			link.l1 = "As-tu découvert où se trouve Oliveiro ?";
			link.l1.go = "PZ_Formosa_smuggler_13";
		break;
		
		case "PZ_Formosa_smuggler_13":
			dialog.text = "Non, pas la moindre idée.";
			link.l1 = "Mon argent !";
			link.l1.go = "PZ_Formosa_smuggler_14";
		break;
		
		case "PZ_Formosa_smuggler_14":
			dialog.text = "N'aie pas la trouille ! Est-ce que j'aurais osé t'approcher à nouveau si je n'avais rien découvert ? Je vais te présenter quelqu'un qui sait. Et t'as de la chance, il adore les gens de ton continent. Il a même des serviteurs assortis, bon sang, même des servantes. Il apprend même votre langue de sauvage. Il s'appelle Johan van Merden. Il t'attendra dans une maison à deux étages près de la résidence.";
			link.l1 = "Je vous remercie.";
			link.l1.go = "PZ_Formosa_smuggler_15";
		break;
		
		case "PZ_Formosa_smuggler_15":
			DialogExit();
			
			locCameraSleep(true);
			LAi_SetActorType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(pchar, "reload", "reload1_back", "PZ_Formosa1_11", -1);
			LAi_ActorGoToLocation(npchar, "goto", "goto3", "", "", "", "", -1);
			npchar.location = "None";
			LocatorReloadEnterDisable("Formosa", "houseSp1", false);
		break;
		
		case "PZ_Formosa_JohanVanMerden_1":
			dialog.text = "Vous êtes Chang Chang, apparemment ? Entrez, ne soyez pas timide.";
			link.l1 = "C'est Chang Tu.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_2";
			DelLandQuestMark(npchar);
			locCameraFromToPos(-1.91, 2.06, -1.75, true, 2.23, -0.85, 0.85);
		break;
		
		case "PZ_Formosa_JohanVanMerden_2":
			dialog.text = "Est-ce vrai ? Mes excuses. Ce Marcelo et son défilé de plaisanteries... Dommage que si peu s'intéressent à ta culture. Et tout cela juste à cause d'une langue différente, et de la forme de tes yeux. Mais tu es intelligent. Contrairement aux gens de couleur, hehehe.";
			link.l1 = "(en mandarin) Alors le contrebandier ne mentait pas - tu es vraiment un homme de culture. Et tu parles vraiment notre langue ?";
			link.l1.go = "PZ_Formosa_JohanVanMerden_2a";
			link.l2 = "Je vous remercie pour vos aimables paroles sur ma culture. Vous devez être Johan van Merden ?";
			link.l2.go = "PZ_Formosa_JohanVanMerden_3";
		break;
		
		case "PZ_Formosa_JohanVanMerden_2a":
			dialog.text = "Oh... Je n'ai compris que quelques mots. J'apprends encore, vous voyez. Pourriez-vous continuer en néerlandais ?";
			link.l1 = "Comme vous voulez. Vous êtes Johan van Merden ?";
			link.l1.go = "PZ_Formosa_JohanVanMerden_3";
		break;
		
		case "PZ_Formosa_JohanVanMerden_3":
			dialog.text = "Oui, Chung Tu, c'est moi. J'ai entendu dire que tu cherchais Oliveiro Fermentelos. Je sais où le trouver, mais d'abord dis-moi, pourquoi le recherches-tu ? Ta réponse déterminera la mienne.";
			link.l1 = "Il... a kidnappé mon dernier et plus cher membre de ma famille - ma sœur, Chang Xing.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_4";
		break;
		
		case "PZ_Formosa_JohanVanMerden_4":
			dialog.text = "Alors, je dois te décevoir, Chang Tu. Il n'y a probablement plus d'espoir pour elle maintenant. Elle a probablement été vendue comme esclave à un riche planteur ou dans un bordel. Dans tous les cas, tu ne pourras pas la sauver.";
			link.l1 = "Je crois que Chang Xing est encore en vie. Oliveiro a jeté son dévolu sur elle. Elle l'a fièrement repoussé. Il l'a kidnappée quand je n'étais pas à la maison. Et... a tué nos parents.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_5";
		break;
		
		case "PZ_Formosa_JohanVanMerden_5":
			dialog.text = "Je... suis désolé. Si tel est le cas, Chang Xing, n'est-ce pas ?-pourrait être encore en vie. Voici ce que nous allons faire : donnez-moi un peu de temps pour découvrir exactement où se trouve Oliveiro en ce moment. Disons une semaine. Je vous reverrai alors. Retrouvez-moi à l'extérieur des portes de la ville-qui sait quels yeux vous suivent ici. Je ne veux pas m'impliquer plus que je ne le fais habituellement, j'espère que vous comprenez.";
			link.l1 = "Je... je suis profondément reconnaissant envers vous, Monseigneur le Capitaine. J'attends avec impatience notre prochaine rencontre.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_6";
		break;
		
		case "PZ_Formosa_JohanVanMerden_6":
			DialogExit();
			LAi_SetStayType(pchar);
			pchar.GenQuest.FrameLockEsc = true;
			SetLaunchFrameFormParam("A week has passed,"+ NewStr() +"April 11, 1645.", "Reload_To_Location", 0, 4.0);
			SetLaunchFrameReloadLocationParam("Formosa_ExitTown", "goto", "goto3", "PZ_Formosa_Spustya7Dney");
			LaunchFrameForm();
		break;
		
		case "PZ_Formosa_JohanVanMerden_11":
			dialog.text = "Bonjour, Chung Tu. Je vois le feu dans tes yeux. J'ai des nouvelles, mais elles ne sont pas bonnes.";
			link.l1 = "Tout renseignement est d'une importance capitale pour moi. Je vous en prie, dites-moi, Monseigneur van Merden.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_12";
		break;
		
		case "PZ_Formosa_JohanVanMerden_12":
			dialog.text = "Aye... Fermentelos est parti pour Batavia il y a environ un mois. C'est le seul indice que j'ai sur lui. La bonne nouvelle, c'est qu'il prévoit d'y rester un moment, donc si tu pars maintenant, tu le rattraperas. La mauvaise nouvelle ? C'est un ami proche du Gouverneur-Général Anthony van Diemen. Tu ne pourras pas l'approcher.";
			link.l1 = "Ces nouvelles suffisent. Mes humbles remerciements à vous, Monseigneur van Merden. Je partirai immédiatement.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_13";
		break;
		
		case "PZ_Formosa_JohanVanMerden_13":
			dialog.text = "Quelque chose me disait que tu dirais cela, alors j'ai décidé d'équilibrer les chances pour toi et Chang Xing. J'ai écrit une lettre à un vieil ami à moi, Oliver Trust. Il possède une boutique à Batavia. Il me doit un service, donc il t'aidera.";
			link.l1 = "Moi... Je ne sais pas quoi dire...";
			link.l1.go = "PZ_Formosa_JohanVanMerden_14";
			//Log_Info("Вы получили письмо");
			PlaySound("interface\important_item.wav");
		break;
		
		case "PZ_Formosa_JohanVanMerden_14":
			dialog.text = "Un simple « merci » suffira. Si tu ne trouves pas Oliveiro en ville, cherche l'Étoile du Matin. Tu pourras toujours le retrouver grâce à son navire. Bonne chance, mon ami - toi et ta sœur en aurez besoin.";
			link.l1 = "Je vous remercie du fond du cœur, Monsieur van Merden.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_15";
		break;
		
		case "PZ_Formosa_JohanVanMerden_15":
			DialogExit();
			LAi_SetStayType(pchar);
			pchar.GenQuest.FrameLockEsc = true;
			SetLaunchFrameFormParam("Batavia,"+ NewStr() +"May 29, 1645.", "Reload_To_Location", 0, 4.0);
			SetLaunchFrameReloadLocationParam("Batavia", "merchant", "mrcActive5", "PZ_Batavia_Puteshestvie");
			LaunchFrameForm();
		break;
		
		case "PZ_OliverTrust_1": //
			dialog.text = "Qui es-tu, et que fais-tu ici ? Je ne fais pas de commerce avec des gens comme toi.";
			link.l1 = "J'ai une lettre pour vous.";
			link.l1.go = "PZ_OliverTrust_2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_OliverTrust_2":
			dialog.text = "Ah, le messager ! Bien que je n'attendais pas de lettres aujourd'hui. Restez ici ! Je vais jeter un coup d'œil.";
			link.l1 = "Es-tu Oliver Trust ? Van Merden m'a envoyé vers toi.";
			link.l1.go = "PZ_OliverTrust_3";
			//Log_Info("Вы отдали письмо");
			PlaySound("interface\important_item.wav");
		break;
		
		case "PZ_OliverTrust_3":
			dialog.text = "Je sais lire, tu sais. Normalement, je te renverrais, mais des gens comme van Merden n'acceptent pas un refus. Enfin, il est temps de régler nos comptes avec van Diemen.";
			link.l1 = "Ma cible est Fermentelos. Et van Diemen ?";
			link.l1.go = "PZ_OliverTrust_4";
		break;
		
		case "PZ_OliverTrust_4":
			dialog.text = "Ce n'est pas ton affaire. Tu devrais être reconnaissant que je t'aide du tout. Maintenant écoute attentivement, avant que je décide que c'est une mauvaise idée. Je connais Fermentelos. Il a été ici pendant un moment, mais il n'est plus ici. Le Morning Star est parti il y a quelques semaines. Dieu sait quand il reviendra. Donc ta cible a changé, et c'est un ami de Fermentelos...";
			link.l1 = "... van Diemen.";
			link.l1.go = "PZ_OliverTrust_5";
		break;
		
		case "PZ_OliverTrust_5":
			dialog.text = "Oui. Tu es au courant de cela aussi ? Je suppose que Johan t'en a parlé ? Oh, van Merden... tu es un sacré audacieux. Mais comme tu sais déjà pour van Diemen, tu connais sa position élevée, n'est-ce pas ? Quel est ton plan maître pour atteindre le Gouverneur-Général ? Pas en prenant d'assaut sa résidence, j'en suis sûr !";
			link.l1 = "Chang Tu est un guerrier habile.";
			link.l1.go = "PZ_OliverTrust_6";
		break;
		
		case "PZ_OliverTrust_6":
			dialog.text = "Un guerrier habile, hein ? Tu te rends compte qu'on est tous embrouillés maintenant ? Et que m'arrive-t-il si tu es capturé ? Je vais devoir t'aider pour ta sécurité et la mienne. En plus de résider dans sa résidence, Van Diemen rend régulièrement visite à la plantation à l'extérieur de la ville et à sa maîtresse Vette.";
			link.l1 = "Tu as mentionné m'aider.";
			link.l1.go = "PZ_OliverTrust_12";
		break;
		
		case "PZ_OliverTrust_12":
			dialog.text = "Je crois que chacun devrait avoir une passion, un passe-temps. Pour ma part, je collectionne les armes rares et coûteuses. Parfois, elles ont une histoire, parfois non, mais elles sont toujours mortelles. Ma collection peut être utile à votre croisade. Alors, dites-moi, où prévoyez-vous de tendre une embuscade à van Diemen ?";
			link.l1 = "(Résidence) Puisque tu as tant de bonnes armes, je prendrai la meilleure lame. Avec elle, Chang Tu sera inégalé parmi les hommes blancs.";
			link.l1.go = "PZ_OliverTrust_resedinsia_1";
			link.l2 = " (Plantation) Je les attaquerai en embuscade sur la route de la plantation - ils n'auront nulle part où fuir.";
			link.l2.go = "PZ_OliverTrust_Plantation1";
			link.l3 = "(Maîtresse) La maîtresse - il n'y aura pas beaucoup de monde là-bas, donc les gardes ne réagiront pas à temps.";
			link.l3.go = "PZ_OliverTrust_lubovnitsa_1";
			SetCharacterPerk(pchar, "Gunman");
			SetCharacterPerk(pchar, "GunProfessional");
			InterfaceStates.Buttons.Save.enable = false;
		break;
		
		// Rebbebion, ну, с Богом...
		case "PZ_OliverTrust_Plantation1":
			pchar.questTemp.PZ_Batavia_plantation_Go = true;
			
			dialog.text = "Bon choix ! Je suis impressionné. Pour en tirer le meilleur parti, il te faudra une bonne arme à feu. Dis-moi, à quelle distance peux-tu viser, Chang Tu ?";
			link.l1 = "Pour être honnête... pas trop loin, je dois m'assurer de ne pas manquer."link.l1.go ="PZ_OliverTrust_Plantation_MediumDistance1";
			link.l2 = "J'attaquerai de loin - mon ennemi ne réalisera même pas d'où je l'ai frappé.";
			link.l2.go = "PZ_OliverTrust_Plantation_FarDistance1";
			notification("Jager Unlocked", "Longway");
			SetCharacterPerk(pchar, "Jager");
		break;
		
		case "PZ_OliverTrust_Plantation_MediumDistance1":
			// делаем Лонгвэя мушкетёром с одновременной выдачей мушкета
			/* pchar.model = "Longway_mush";
			pchar.model.animation = "mushketer"; */
			pchar.model = "Longway";
			pchar.model.animation = "Longway";
			Characters_RefreshModel(pchar);
			GiveItem2Character(pchar, "mushket6"); 
			EquipCharacterByItem(pchar, "mushket6");
			//Log_Info("Вы получили башенный мушкетон");
			PlaySound("interface\important_item.wav");
			
			AddItems(pchar, "grapeshot", 50);
			AddItems(pchar, "gunpowder", 50);
			LAi_SetCharacterUseBullet(pchar, GUN_ITEM_TYPE, "grapeshot");
			
			dialog.text = "Je vois. Dans ce cas, prends ça ! Un tromblon portugais antique, tirant une cartouche de gros calibre. Ils n'en fabriquent plus, même dans le Vieux Monde.";
			link.l1 = "J'en ai vu un quand j'étais enfant...";
			link.l1.go = "PZ_OliverTrust_Plantation_MediumDistance2";
		break;
		
		case "PZ_OliverTrust_Plantation_MediumDistance2":
			dialog.text = "Alors, tu sais comment l'utiliser ?";
			link.l1 = "Non...";
			link.l1.go = "PZ_OliverTrust_Plantation_MediumDistance3";
		break;
		
		case "PZ_OliverTrust_Plantation_MediumDistance3":
			dialog.text = "N'oublie pas, le mécanisme interchangeable est devenu rouillé avec le temps. Pas d'huile ne le réparera - il est cassé pour de bon. Le charger est difficile, alors faisons-le maintenant. Regarde attentivement - utilise un peu de force, comme ça. Mais pas trop fort, sinon tu le casseras.";
			link.l1 = "Comme ça ?";
			link.l1.go = "PZ_OliverTrust_Plantation_MediumDistance4";
		break;
		
		case "PZ_OliverTrust_Plantation_MediumDistance4":
			dialog.text = "Exactement.";
			link.l1 = "Compris. Merci beaucoup !";
			link.l1.go = "PZ_OliverTrust_13";
		break;
		
		case "PZ_OliverTrust_Plantation_FarDistance1":
			// делаем Лонгвэя мушкетёром с одновременной выдачей мушкета
			/* pchar.model = "Longway_mush";
			pchar.model.animation = "mushketer"; */
			pchar.model = "Longway";
			pchar.model.animation = "Longway";
			Characters_RefreshModel(pchar);
			GiveItem2Character(pchar, "mushket2x2"); 
			EquipCharacterByItem(pchar, "mushket2x2");
			//Log_Info("Вы получили двуствольный штуцер");
			PlaySound("interface\important_item.wav");
			
			AddItems(pchar, "cartridge", 50);
			AddItems(pchar, "gunpowder", 50);
			LAi_SetCharacterUseBullet(pchar, GUN_ITEM_TYPE, "cartridge");
			
			dialog.text = "Un vrai chasseur ! Fais attention, c'était un cadeau. C'est l'un de ces rares cas où une arme est à la fois ornée et mortelle. Un fusil de chasse à double canon ! Lourd à porter, facile à utiliser. As-tu déjà compris comment le tirer ?";
			link.l1 = "Compris. Merci beaucoup !";
			link.l1.go = "PZ_OliverTrust_13";
		break;
		
		case "PZ_OliverTrust_lubovnitsa_1":
			dialog.text = "Tu as raison à propos des gardes, mais ne sous-estime pas le danger. Van Diemen ne se déplace jamais en ville sans son bras droit, Joep van der Vink.";
			link.l1 = "Alors, ils sont avec Vette... ?";
			link.l1.go = "PZ_OliverTrust_lubovnitsa_2";
			pchar.questTemp.PZ_Batavia_lubovnitsa_Go = true;
			AddCharacterSkillDontClearExp(pchar, "Sailing", 10);
			AddCharacterSkillDontClearExp(pchar, "Commerce", 10);
			AddCharacterSkillDontClearExp(pchar, "Repair", 10);
			notification("Naval Skills +", "Longway");
			notification("Rat Wolf Unlocked", "Longway");
			SetCharacterPerk(pchar, "RatsWolf");
		break;
		
		case "PZ_OliverTrust_lubovnitsa_2":
			dialog.text = "Quoi ? Ha ! Tu as une sacrée imagination, Chinois ! Antoon est un lâche, et van der Vink est là pour le protéger au cas où quelqu'un viendrait troubler leur “moment privé.”/nJoep porte toujours une armure lourde - impénétrable à la plupart des armes blanches. C'est pourquoi tu auras aussi besoin de quelque chose de spécial. Prends cette rapière. Elle est longue, plus solide que la plupart des autres épées, et pèse comme une bonne lame.";
			link.l1 = "Une rapière pour combattre des ennemis en armure...?";
			link.l1.go = "PZ_OliverTrust_lubovnitsa_3";
			//Log_Info("Вы получили асоледу");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(PChar, "blade_26");
			EquipCharacterByItem(Pchar, "blade_26");
		break;
		
		case "PZ_OliverTrust_lubovnitsa_3":
			dialog.text = "N'attaque pas l'armure elle-même - ce n'est pas une estoc. Frappe les interstices et les points vulnérables, comme l'aine, les aisselles et la gorge. Épuise-le, impose tes conditions. Joep manie aussi une lourde hache, alors n'essaie pas de parer ses coups - esquive-les à la place. Au cas où tu n'arriverais pas à trouver une ouverture, prends ce tromblon. Il est généralement chargé de chevrotine, mais j'ai préparé un jeu de flèches en acier pour toi.";
			link.l1 = "Des flèches pour un mousquet...?";
			link.l1.go = "PZ_OliverTrust_lubovnitsa_4";
			//Log_Info("Вы получили бландербуз");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(PChar, "pistol8");
			EquipCharacterByItem(Pchar, "pistol8");
			AddItems(Pchar, "harpoon", 30);
			AddItems(Pchar, "gunpowder", 30);
			LAi_SetCharacterUseBullet(Pchar, GUN_ITEM_TYPE, "harpoon");
		break;
		
		case "PZ_OliverTrust_lubovnitsa_4":
			dialog.text = "Étrange, n'est-ce pas ? Un mélange d'ancien et de nouveau. Il est conçu pour être utilisé d'une seule main, mais s'il est trop lourd, utilise les deux. Beaucoup le font. Et ici, essaie cette armure en osier. Elle est plus légère que le cuirasse de Joep mais offre toujours une protection décente. Ne laisse pas sa hache porter un coup direct - même une armure milanaise ne tiendrait pas contre une arme comme ça. Tu comprends ?";
			link.l1 = "Oui, je comprends. Merci, M. Confiance !";
			link.l1.go = "PZ_OliverTrust_13";
			//Log_Info("Вы получили кожаный корсет");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(PChar, "cirass5");
			EquipCharacterByItem(Pchar, "cirass5");
		break;
		
		case "PZ_OliverTrust_resedinsia_1":
			dialog.text = "Trop sûr de toi, hein ? Peut-être que je t'ai parlé de ma collection trop tôt. Mais... tu es déjà engagé. Attaquer une résidence en plein jour est un geste audacieux, inattendu. Cette lame devrait convenir à tes besoins. Ce n'est pas la meilleure au monde, mais elle est parfaite pour poignarder, trancher et couper.";
			link.l1 = "Clewang ! Je reconnais cette lame. Les habitants des îles voisines l'utilisent souvent.";
			link.l1.go = "PZ_OliverTrust_resedinsia_2";
			pchar.questTemp.PZ_Batavia_resedinsia_Go = true;
			notification("Duelist Unlocked", "Longway");
			SetCharacterPerk(pchar, "FencingMaster");
			SetCharacterPerk(pchar, "HT1");
		break;
		
		case "PZ_OliverTrust_resedinsia_2":
			dialog.text = "Have you used one before? Good. You'll have little time and many enemies to face. Here, take this as well - a handgun with three barrels, beautifully inlaid. Load it now in front of me; you won't have time for that later. And wear this dueling waistcoat. It's light, it will give you the speed you'll need, and some protection.";
			link.l1 = "Merci, Monseigneur Trust !";
			link.l1.go = "PZ_OliverTrust_13";
			//Log_Info("Вы получили клеванг");
			//Log_Info("Вы получили трёхствольный дробовик");
			//Log_Info("Вы получили жилет бретера");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(PChar, "blade_30");
			EquipCharacterByItem(Pchar, "blade_30");
			GiveItem2Character(PChar, "pistol2");
			EquipCharacterByItem(Pchar, "pistol2");
			GiveItem2Character(PChar, "cirass6");
			EquipCharacterByItem(Pchar, "cirass6");
			AddItems(Pchar, "grapeshot", 50);
			AddItems(Pchar, "gunpowder", 50);
			LAi_SetCharacterUseBullet(Pchar, GUN_ITEM_TYPE, "grapeshot");
		break;
		
		case "PZ_OliverTrust_13":
			dialog.text = "Attends, nous n'avons pas fini. Il est dans notre intérêt commun que tu survives. Prends ce médicament pour soigner tes blessures après la bataille. \nEt cet élixir aussi. Il a un goût et une odeur atroces, mais il élimine tout poison dans ton corps. Joep van der Vink, le garde du corps de Van Diemen, enduit ses armes de cette merde. Sale prétentieux, tu auras donc un avantage.";
			link.l1 = "Je ne sais pas si je pourrai jamais vous remercier suffisamment, Monseigneur le Capitaine...";
			link.l1.go = "PZ_OliverTrust_14";
			//Log_Info("Вы получили 10 лечебных зелий");
			//Log_Info("Вы получили противоядие");
			PlaySound("interface\important_item.wav");
			AddItems(Pchar, "potion1", 10);
			AddItems(Pchar, "potion3", 1);
		break;
		
		case "PZ_OliverTrust_14":
			dialog.text = "Le meilleur remerciement serait de ne pas me dénoncer si tu te fais prendre. Bien que, très probablement, ils te tueront sur-le-champ. Mais si tu survis à ça, dis à Van Diemen qu'il doit sa mort à moi. Peux-tu faire ça ?";
			link.l1 = "Aucun problème. Merci encore, Mynheer Trust. Au revoir !";
			link.l1.go = "PZ_Batavia_NaOhotu";
		break;
		
		case "PZ_Batavia_NaOhotu":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.PZ_Batavia_resedinsia_Go"))
			{
				DoQuestReloadToLocation("Batavia", "reload", "reload1", "PZ_Batavia_BitvaSoStrazhnikami");
			}
			if (CheckAttribute(pchar, "questTemp.PZ_Batavia_lubovnitsa_Go"))
			{
				DoQuestReloadToLocation("Batavia_HouseF3", "reload", "reload1", "PZ_Batavia_BitvaLubovnitsa");
			}
			if (CheckAttribute(pchar, "questTemp.PZ_Batavia_Plantation_Go"))
			{
				/*EndQuestMovie();
				sld = &Locations[FindLocation("Batavia_plantation")];
				sld.locators_radius.quest.detector4 = 3.0;
				PChar.quest.PZ_Batavia_plantation1.win_condition.l1 = "locator";
				PChar.quest.PZ_Batavia_plantation1.win_condition.l1.location = "Batavia_plantation";
				PChar.quest.PZ_Batavia_plantation1.win_condition.l1.locator_group = "quest";
				PChar.quest.PZ_Batavia_plantation1.win_condition.l1.locator = "detector4";
				PChar.quest.PZ_Batavia_plantation1.win_condition = "PZ_Batavia_plantation_selfdialog";*/
				DoQuestReloadToLocation("Batavia_plantation", "quest", "detector2", "PZ_Batavia_plantation_setguards");
			}
		break;
		
		case "PZ_Batavia_BitvaSoStrazhnikami_1":
			dialog.text = "Halte ! Où vas-tu, Chinois ?";
			link.l1 = "À la résidence.";
			link.l1.go = "PZ_Batavia_BitvaSoStrazhnikami_2";
			locCameraFromToPos(-0.44, 7.45, 24.65, true, -1.90, 5.10, 18.50);
		break;
		
		case "PZ_Batavia_BitvaSoStrazhnikami_2":
			dialog.text = "Ça, c'était une question rhétorique, génie. Qu'est-ce qui te fait penser que quelqu'un te laisserait entrer là-dedans ?";
			link.l1 = "J'ai affaire avec Mynheer Van Diemen. Laissez-moi passer, s'il vous plaît.";
			link.l1.go = "PZ_Batavia_BitvaSoStrazhnikami_3";
		break;
		
		case "PZ_Batavia_BitvaSoStrazhnikami_3":
			dialog.text = "Vous connaissez le nom du gouverneur général ? Eh bien... dites-moi quel est votre affaire. Je le transmettrai et vous répondrai avec une réponse.";
			link.l1 = "Ma conversation est uniquement avec Mynheer Van Diemen. Il m'attend. Écartez-vous, ou vous le regretterez.";
			link.l1.go = "PZ_Batavia_BitvaSoStrazhnikami_4";
			locCameraSleep(true);
		break;
		
		case "PZ_Batavia_BitvaSoStrazhnikami_4":
			dialog.text = "Eh bien, eh bien, ne te vante pas, aux yeux étroits. C'est soit à ma manière, soit pas du tout.";
			link.l1 = "Alors, ma voie.";
			link.l1.go = "PZ_Batavia_BitvaSoStrazhnikami_5";
		break;
		
		case "PZ_Batavia_BitvaSoStrazhnikami_5":
			DialogExit();
			LAi_SetActorType(pchar);
			CharacterTurnByChr(pchar, CharacterFromID("PZ_SoldResid_1"));
			LAi_group_MoveCharacter(pchar, LAI_GROUP_PLAYER);
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
			
			sld = CharacterFromID("PZ_SoldResid_1");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
				
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			
			DoQuestCheckDelay("PZ_Batavia_resedinsia_1", 0.9);
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_1":
			dialog.text = "Satané paysan ! Qui t'a engagé ? Je te paierai plus que ça !";
			link.l1 = "Vous, les gens blancs, ne vous souciez que de l'or. Que les dragons maudissent votre espèce. Je suis venu chercher des informations, mais vos gens ne veulent pas me laisser entrer.";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_2";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_2":
			dialog.text = "Que veux-tu?!";
			link.l1 = "Où est-il maintenant, Fermentelos ?";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_3";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_3":
			dialog.text = "Oliveiro ? Mais pourquoi diable le veux-tu ? Je ne te dirai rien !";
			link.l1 = "Il a tué ma famille et enlevé ma soeur. Mon conseil pour vous est de commencer à parler. Pour votre propre bien.";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_4";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_4":
			dialog.text = "Que vas-tu me faire ? Toute la garnison sera bientôt ici.";
			link.l1 = "As-tu entendu parler de Lynchy ? C'est une punition dans ma culture. Cela signifie 'Mort par mille coupures.'";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_5";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_5":
			dialog.text = "Tu n'auras pas le temps de me faire autant de coupures, imbécile !";
			link.l1 = "C'est une figure de style. Le bourreau inflige des coupures, une par une. Ou découpe des morceaux du corps. Nous faisons autant que nous avons le temps de faire - à moins que vous ne commenciez à parler.";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_6";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_6":
			DialogExit();
			
			sld = GetCharacter(NPC_GenerateCharacter("PZ_Sepp", "mercen_26", "man", "man", sti(pchar.rank), HOLLAND, -1, false, "quest"));
			sld.name = "Joep";
			sld.lastname = "van der Vink";
			GiveItem2Character(sld, "topor_04");
			EquipCharacterByItem(sld, "topor_04");
			GiveItem2Character(sld, "pistol3");
			EquipCharacterByItem(sld, "pistol3");
			sld.CantLoot = true;
			LAi_SetHP(sld, 300.0, 300.0);
			ChangeCharacterAddressGroup(sld, "Batavia_townhallRoom", "reload", "reload1");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
			
			LAi_SetStayType(pchar);
			locCameraFromToPos(-3.06, 1.64, -0.43, true, 1.87, -1.20, 2.39);
			DoQuestCheckDelay("PZ_Batavia_BitvaResidensia_7", 2.5);
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_7":
			dialog.text = "A-A-A !!! Arrête ! Arrête, sale brute. Je vais tout te dire, je vais tout te dire. Arrête juste. Joep ! Enfin ! Où diable étais-tu pendant tout ce temps ?!";
			link.l1 = "Quel mauvais timing...";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_8";
			SetCameraDialogMode(npchar);
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_8":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("PZ_Sepp");
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_9";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_9":
			dialog.text = "Antoon ? Il te faut voir un médecin tout de suite. Je t'aiderai à y aller dès que j'aurai fini ici. Toi ! Que fais-tu, espèce de boucher lâche ?!";
			link.l1 = "Boucher Jaune ? J'aime bien ça. Il n'y a qu'une question à laquelle j'ai besoin de réponse, mais personne ne semble prêt à la donner...";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_10";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_10":
			dialog.text = "Quelle question?!";
			link.l1 = "Où est Oliveiro Fermentelos ? Vous ne pouvez pas juste dire cela ?";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_11";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_11":
			dialog.text = "Je me fiche éperdument de Fermentelos ! Qui t'a donné l'argent et les informations ?!";
			link.l1 = "Oliver Trust. Au fait, il voulait que je te dise que tu lui dois ta mort.";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_12";
			
			sld = CharacterFromID("PZ_AntoniOneDimen");
			LAi_ActorSetGroundSitMode(sld);
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_12":
			dialog.text = "La confiance ?! Ha-ha-ha-ha-ha-ha-ha ! Ce grippe-sou, pensant qu'il pourrait se venger juste parce que nous avons pris sa plantation ? Nous prendrons bientôt sa boutique et sa vie, une fois que j'en aurai fini avec toi.";
			link.l1 = "Tu gaspilles mon temps.";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_13";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_13":
			DialogExit();
			LAi_SetFightMode(pchar, true);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			
			PChar.quest.PZ_Batavia_BitvaResidensia_8.win_condition.l1 = "NPC_Death";
			PChar.quest.PZ_Batavia_BitvaResidensia_8.win_condition.l1.character = "PZ_Sepp";
			PChar.quest.PZ_Batavia_BitvaResidensia_8.win_condition = "PZ_Batavia_BitvaResidensia_8";
		break;
		
		case "PZ_Batavia_PlantationSelfDialog":
			dialog.text = "(en mandarin) Alors, cherchons un bon endroit pour une embuscade.";
			if (CheckCharacterItem(pchar, "mushket6"))
			{
				link.l1 = "(en mandarin) Avec cette chose rouillée, je vais devoir m'approcher. Volée rapide - aiguisée et impitoyable. La peur et la panique feront le reste.";
				link.l1.go = "Exit";
			}
			else
			{
				link.l1 = "(en mandarin) Juste ici. Ils ne me verront même pas au début. Les meilleures batailles sont celles qui ne commencent pas... ou qui se terminent rapidement avec peu de sang versé.";
				link.l1.go = "Exit";
			}
			AddDialogExitQuest("MainHeroFightModeOn");
			AddDialogExitQuest("PZ_Batavia_PlantationFight");
		break;
		
		case "PZ_Batavia_PlantationDimen1":
			if (!CharacterIsAlive("PZ_SoldPlantation_1") && !CharacterIsAlive("PZ_SoldPlantation_2") &&  !CharacterIsAlive("PZ_SoldPlantation_3") && !CharacterIsAlive("PZ_SoldPlantation_4") && !CharacterIsAlive("PZ_SoldPlantation_5") && !CharacterIsAlive("PZ_SoldPlantation_6"))
			{
				dialog.text = "Salaud de brute... Esclave en fuite, n'est-ce pas ? Comment as-tu obtenu une telle arme ? Quelqu'un t'a engagé... ?";
				link.l1 = "Pas de temps ! Dis-moi où est Oliveiro Fermentelos - maintenant !";
				link.l1.go = "PZ_Batavia_PlantationDimen2";
			}
			else
			{
				dialog.text = RandSwear()+"";
				link.l1 = "";
				link.l1.go = "exit";
				AddDialogExitQuest("PZ_PlantationDimenSit");
			}
		break;
		
		case "PZ_Batavia_PlantationDimen2":
			dialog.text = "Hehehe, drôle... Il n'y a pas de temps - le sang coule de mon ventre. Brûle en enfer, païen...";
			link.l1 = "Non !!!";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_Batavia_PlantationDimenDead1");
		break;
		
		case "PZ_Batavia_Plantation_DimenDeadSelfDialog":
			dialog.text = "(en mandarin) Pourquoi, pourquoi, pourquoi ?! Comment suis-je censé trouver Fermentelos maintenant ?!";
			link.l1 = "Mais d'abord, je dois me cacher - quelqu'un a dû déjà signaler ce bain de sang...";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_final";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_1":
			dialog.text = "Hic ! Un Chinois ! Je ne m'attendais pas à ce qu'on invite quelqu'un comme toi ici. Tu aimes regarder, hein ? Hehe.";
			link.l1 = "Pourquoi y a-t-il tant de gens ici...? Et qui es-tu ?";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_2";
			SetCameraDialogMode(npchar);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_2":
			dialog.text = "Tu ne me reconnais pas à mes vêtements ? Et surveille ton ton quand tu parles au Gouverneur Général ! Hic !";
			link.l1 = "Alors, vous devez être Mynheer Van Diemen. Je m'excuse pour mon ignorance. Est-ce un carnaval qui se déroule ici ?";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_3";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_3":
			dialog.text = "C'est ça, mon bonhomme, et pas autrement ! Un carnaval en travesti ! Ha-ha-ha ! Pas si mal, paysan ! Je suis sûr que Luthers adorerait porter la robe de Vette, ha ha ha !";
			link.l1 = "Luthers?..";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_4";
			locCameraFromToPos(-4.45, 2.11, 1.53, true, 0.47, -0.30, 2.74);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_4":
			dialog.text = "Ce pitoyable prétexte de mari, qui aime espionner depuis l'armoire pendant que sa chère épouse est mise au lit. Cela ne la dérange pas !";
			link.l1 = "";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_4_1";
			sld = CharacterFromID("PZ_Rubbe");
			CharacterTurnByChr(npchar, sld);
			CharacterTurnByChr(pchar, sld);
			CharacterTurnByChr(CharacterFromID("PZ_Brigitta"), sld);
			DoQuestCheckDelay("PZ_Batavia_BitvaLubovnitsa_4", 2.5);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_4_1":
			Event("QuestDelayExit","sl", "", 0);
			dialog.text = "D'accord, Vette, ma chère ? Heh-heh.";
			link.l1 = "(en mandarin) Que diable se passe-t-il ici...";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_5";
			sld = CharacterFromID("PZ_Rubbe");
			CharacterTurnByChr(npchar, CharacterFromID("PZ_Brigitta"));
			CharacterTurnByChr(pchar, npchar);
			CharacterTurnByChr(CharacterFromID("PZ_Brigitta"), npchar);
			locCameraFromToPos(-2.21, 1.90, 2.26, true, -0.81, -0.40, 4.36);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_5":
			dialog.text = "Hic ! Je ne sais pas ce que tu viens de dire, mais à voir tes yeux et ton ton, tu es d'accord avec moi ! Van Haan est un foutu pervers. Alors, qu'est-ce que tu es ? Un ouvrier ? Vette t'a invité ?";
			link.l1 = "Je...";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_6";
			CharacterTurnByChr(pchar, npchar);
			CharacterTurnByChr(npchar, pchar);
			CharacterTurnByChr(CharacterFromID("PZ_Brigitta"), pchar);
			locCameraFromToPos(-4.45, 2.11, 1.53, true, 0.47, -0.30, 2.74);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_6":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("PZ_Sepp");
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_Batavia_BitvaLubovnitsa_7";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_7":
			dialog.text = "Inviter un ouvrier ici est de trop, même pour Vette. Il est évidemment perdu et n'a rien à faire ici. Hé, toi. Sors d'ici et oublie tout ce que tu as vu. Qui est ton maître ? Nous le contacterons, et vous serez tous deux payés pour votre silence. Tu pourrais même être autorisé à retourner auprès de ta famille sur le continent. Réponds-moi et pars.";
			link.l1 = "En fait, je suis ici pour affaires.";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_8";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_8":
			dialog.text = "Heh, affaires. Seul Mynheer van Diemen fait des “Affaires” ici. Mon travail est de le protéger des gens comme toi. Et Luthers... reste Luthers. Ou... est-ce que Vette t'a vraiment invité ici ?";
			link.l1 = " Non, je suis ici pour...";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_9";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_9":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("PZ_Rubbe");
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_Batavia_BitvaLubovnitsa_10";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_10":
			dialog.text = "Ma chère Vette inviterait-elle vraiment un trouillard ici ?! Dégage d'ici !!!";
			link.l1 = "Le misérable cocu...";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_11";
			link.l2 = "Personne ne te parle. Ferme ta gueule. Ne fais pas semblant d'avoir une queue ou de la dignité.";
			link.l2.go = "PZ_Batavia_BitvaLubovnitsa_12";
			GiveItem2Character(npchar, "blade_06");
			EquipCharacterByItem(npchar, "blade_06");
			LAi_SetActorType(npchar);
			npchar.model.animation = "man";
			Characters_RefreshModel(npchar);
			SetCameraDialogMode(npchar);
			locCameraToPos(-1.88, 1.72, 0.27, false);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_11":
			dialog.text = "Co-co-cocu ?! Non, je l'aime plus que moi-même. Ha, un imbécile chinois comme toi ne comprendrait pas ça !";
			link.l1 = "(en mandarin) Salaud malade.";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_13";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_12":
			dialog.text = "Co-co-coq ?! C'est très bien ! Oui ! Je sais juste que d'autres hommes donnent plus de plaisir à ma chère Vette, c'est tout !";
			link.l1 = "Comme on dit dans mon pays, un homme reste un homme tant qu'il ne lui reste qu'un seul doigt. Si vous étiez un homme, vous comprendriez cela.";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_13";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_13":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("PZ_Brigitta");
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_Batavia_BitvaLubovnitsa_14";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_14":
			dialog.text = "Je ne l'ai pas invité, bien sûr, mais, vous savez, il est plutôt sympathique. Il pourrait rester après votre départ à tous. J'ai déjà essayé avec notre chien, mais je ne l'ai jamais fait avec...";
			link.l1 = "Tais-toi, quand les hommes parlent, catin ! Tu es le seul animal ici. Je suis ici pour affaires. Je cherche Oliveiro Fermentelos. Vous devez être ses amis. Pourriez-vous me dire où il pourrait se trouver, Mynheer Van Diemen ?";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_15";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_15":
			dialog.text = "Antoon, il m’a insultée ! Insultée ! Tu ne vas pas laisser passer ça, hein ?!";
			link.l1 = "... ";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_16";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_16":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("PZ_AntoniOneDimen");
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_Batavia_BitvaLubovnitsa_17";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_17":
			dialog.text = "Hehe, désolé, l'ami, mais la dame est furieuse. Je vais devoir te donner une leçon de bonnes manières. Leçon numéro un.";
			link.l1 = "Mais pouvez-vous m'aider dans ma recherche d'Oliveiro ?";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_18";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_18":
			dialog.text = "Ça ne servira à rien à un travailleur mort.";
			link.l1 = "(en mandarin) Que diable vous emporte tous...";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_19";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_19":
			DialogExit();
			EndQuestMovie();
			InterfaceStates.Buttons.Save.enable = false;
			
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
			LAi_SetFightMode(pchar, true);
			PlaySound("Voice\Russian\hambit\Longway-02.wav");
			
			sld = CharacterFromID("PZ_AntoniOneDimen");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			sld = CharacterFromID("PZ_Sepp");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			sld = CharacterFromID("PZ_Rubbe");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "PZ_Batavia_BitvaLubovnitsa_3");
			
			sld = CharacterFromID("PZ_Brigitta");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload2", "none", "", "", "", -1);
			PlaySound("People Fight\Peace_woman_death_05.wav");
			DoQuestCheckDelay("PZ_Batavia_BitvaLubovnitsa_5", 3.0);	//Нужно ещё раз, а то не бежит
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_21":
			dialog.text = "(en mandarin) Bon sang ! Je n'ai rien appris !";
			link.l1 = "(en mandarin) Je n'oublierai jamais ce jour... Je dois sortir d'ici avant que les gardes n'arrivent. Pas qu'ils se soucient des bruits provenant de cet asile de fous...";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_final";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_14":
			dialog.text = "(en mandarin) Les dieux ont maudit ce jour ! Van Diemen s'est vidé de son sang pendant que je m'occupais de son sbire... !";
			link.l1 = "(en mandarin) Les gardes arrivent. Je vais devoir me battre pour sortir d'ici.";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_final";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_final":
			DialogExit();
			RemoveCharacterEquip(PChar, GUN_ITEM_TYPE);
			RemoveCharacterEquip(PChar, MUSKET_ITEM_TYPE);
			if (CheckAttribute(pchar, "questTemp.PZ_Batavia_resedinsia_Go"))
			{
				TakeItemFromCharacter(pchar, "blade_30");
				TakeItemFromCharacter(pchar, "pistol2");
			}
			if (CheckAttribute(pchar, "questTemp.PZ_Batavia_lubovnitsa_Go"))
			{
				TakeItemFromCharacter(pchar, "blade_26");
				TakeItemFromCharacter(pchar, "pistol8");
			}
			if (CheckAttribute(pchar, "questTemp.PZ_Batavia_Plantation_Go"))
			{
				TakeItemFromCharacter(pchar, "mushket6");
				TakeItemFromCharacter(pchar, "mushket2x2");
			}
			EquipCharacterByItem(Pchar, "blade_11");
			pchar.model = "Longway";
			pchar.model.animation = "Longway";
			Characters_RefreshModel(pchar);
			
			
			SetCurrentTime(2, 30);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			
			pchar.GenQuest.FrameLockEsc = true;
			SetLaunchFrameFormParam("Formosa,"+ NewStr() +"26 July 1645.", "Reload_To_Location", 0, 4.0);
			SetLaunchFrameReloadLocationParam("Formosa", "goto", "goto7", "PZ_Formosa2_Start");
			LaunchFrameForm();
		break;
		
		case "PZ_Formosa_smuggler_21":
			dialog.text = "Oh, c'est Chang Chang ! Que puis-je faire pour t'aider cette fois, mon petit ami ?";
			link.l1 = "C'est Chang Tu... que veux-tu dire ?";
			link.l1.go = "PZ_Formosa_smuggler_22";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_Formosa_smuggler_22":
			dialog.text = "Tu débordes de mépris pour moi, n'est-ce pas ? Tu ne serais pas venu ici si tu n'avais pas besoin de quelque chose.";
			link.l1 = "Savez-vous où se trouve van Merden ? Est-il en ville ? Il n'est pas chez lui. J'ai besoin de lui parler.";
			link.l1.go = "PZ_Formosa_smuggler_23";
		break;
		
		case "PZ_Formosa_smuggler_23":
			dialog.text = "On ne peut pas demander à un homme de rester à la maison toute la journée, en attendant qu'un seul homme à la peau jaune se montre. Il a des affaires sur l'île. Il sera de retour en ville ce soir, alors ne t'inquiète pas, Chang Chang !";
			link.l1 = "Merci. Au revoir.";
			link.l1.go = "PZ_Formosa_smuggler_24";
		break;
		
		case "PZ_Formosa_smuggler_24":
			SetCurrentTime(1, 30);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			DoQuestReloadToLocation("Formosa", "goto", "goto7", "PZ_Formosa2_IshemMerden_3");
		break;
		
		case "PZ_Formosa_bandit_1":
			dialog.text = "Hé, l'œil étroit ! Quelle est la précipitation à cette heure-ci ? Tous les braves gens dorment déjà.";
			link.l1 = "Et toi alors ?";
			link.l1.go = "PZ_Formosa_bandit_2";
		break;
		
		case "PZ_Formosa_bandit_2":
			dialog.text = "Bien dit ! Nous sommes en patrouille ! On raconte qu'il y a un petit bonhomme jaune qui fouine en ville, dérangeant les braves gens qui craignent Dieu.";
			link.l1 = "Qui cela pourrait-il être, je vous prie de me dire ?";
			link.l1.go = "PZ_Formosa_bandit_3";
		break;
		
		case "PZ_Formosa_bandit_3":
			dialog.text = "Assez parlé - il se fait tard et je commence à avoir sommeil.";
			link.l1 = "Bientôt, ton sommeil sera éternel.";
			link.l1.go = "PZ_Formosa_bandit_4";
		break;
		
		case "PZ_Formosa_bandit_4":
			DialogExit();
			EndQuestMovie();
			InterfaceStates.Buttons.Save.enable = false;
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			
			sld = CharacterFromID("PZ_JohanVanMerden");
			ChangeCharacterAddressGroup(sld, PChar.location, "patrol", "patrol7");
			GiveItem2Character(sld, "blade_31");
			EquipCharacterByItem(sld, "blade_31");
			LAi_SetActorType(sld);
			
			for (i=1; i<=3; i++)
			{
				sld = CharacterFromID("PZ_FormosaBandit_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "PZ_Formosa2_IshemMerden_7");
			
			DoQuestCheckDelay("PZ_Formosa2_IshemMerden_6", 10.0);
		break;
		
		case "PZ_Formosa_JohanVanMerden_21":
			dialog.text = "Chang Tu, ça va ?";
			link.l1 = "Mynheer van Merden ! Je vais bien, grâce à votre intervention. Êtes-vous en sécurité ? C'est la question la plus importante.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_22";
		break;
		
		case "PZ_Formosa_JohanVanMerden_22":
			dialog.text = "Vous pensez toujours aux autres, n'est-ce pas ? Nous partageons ce trait. Je ne pouvais pas rester là à ne rien faire en les voyant vous attaquer, même si je savais que vous les géreriez. Pour répondre à votre question, je vais bien, juste un peu fatiguée. Mes jambes sont un peu tremblantes. Allons à l'intérieur, si cela ne vous dérange pas. Nous pourrons parler là-bas.";
			link.l1 = "Bien sûr, Monseigneur van Merden, c'est votre maison après tout.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_23";
		break;
		
		case "PZ_Formosa_JohanVanMerden_23":
			DoQuestReloadToLocation("Formosa_houseSp1", "goto", "goto1", "PZ_Formosa2_IshemMerden_8");
		break;
		
		case "PZ_Formosa_JohanVanMerden_24":
			dialog.text = "Maintenant, nous pouvons parler sans hâte, en paix et tranquillité. Dis-moi, qu'est-ce qui t'amène à moi, Chang Tu ?";
			link.l1 = "Vous avez raison, Monseigneur van Merden. Je viens juste de rentrer de Batavia, et...";
			link.l1.go = "PZ_Formosa_JohanVanMerden_25";
		break;
		
		case "PZ_Formosa_JohanVanMerden_25":
			dialog.text = "Attends. Est-ce le pauvre Chang Xing...?";
			link.l1 = "Non, pas du tout ! J'espère que non. Le ciel garde encore son sort secret pour moi. Et quant à Fermentelos... il n'est pas à Batavia. Van Diemen ne m'a été d'aucune aide.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_26";
		break;
		
		case "PZ_Formosa_JohanVanMerden_26":
			dialog.text = "Il ne le serait pas, car lui et Oliveiro sont de vieux amis. Comme disent les Anglais, amis et complices. Je serais surpris s'il te donnait quelque chose d'utile.";
			link.l1 = "Oui, grâce à vous et à Trust, j'ai acquis de puissants bras. J'ai attaqué Van Diemen pour l'interroger et découvrir où se trouvait Fermentelos. Mais il est mort avant que je puisse apprendre quoi que ce soit...";
			link.l1.go = "PZ_Formosa_JohanVanMerden_28";
		break;
		
		case "PZ_Formosa_JohanVanMerden_28":
			dialog.text = "Impressionnant. Vous avez compris que les gens ne veulent pas toujours partager ce qu'ils savent. Il y a donc d'autres... méthodes de persuasion, dirons-nous. Je pensais que vous aviez peut-être appris la mort de votre sœur, et c'est pour cela que vous vous êtes déchaîné. Mais qu'est-ce qui vous amène à moi maintenant ? Je vous ai dit que je ne savais pas où Fermentelos se rend, à part ses visites occasionnelles à Batavia. Avec Van Diemen parti, cette dernière piste est perdue.";
			link.l1 = "Mais vous connaissez beaucoup de choses et beaucoup de gens. Je pensais que vous pourriez m'aider à nouveau, peut-être vous renseigner sur Fermentelos, comme avant. Vous avez été le premier homme blanc à me traiter bien. Le premier... ami blanc.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_29";
		break;
		
		case "PZ_Formosa_JohanVanMerden_29":
			dialog.text = "C'est... touchant.";
			link.l1 = "Monsieur van Merden, pourquoi souriez-vous...?";
			link.l1.go = "PZ_Formosa_JohanVanMerden_30";
		break;
		
		case "PZ_Formosa_JohanVanMerden_30":
			dialog.text = "Hein ? Oh, je suis désolé, Chang Tu. Je deviens vieux, sentimental et mélancolique avec l'âge. C'est un sourire sincère - je ne pouvais pas le cacher. Je suis heureux que tu me considères comme un ami. Puisque nous sommes amis, j'attends aussi que tu m'aides de temps en temps. En retour, je t'aiderai assurément avec Fermentelos. Ne t'inquiète pas - tu ne marches pas dans un piège.";
			link.l1 = "Hmm, comment t'aider ?";
			link.l1.go = "PZ_Formosa_JohanVanMerden_31";
		break;
		
		case "PZ_Formosa_JohanVanMerden_31":
			dialog.text = "Depuis notre dernière rencontre, j'ai approfondi mon étude de votre langue et de votre culture, en particulier de la médecine. J'aimerais que vous me trouviez de temps en temps certaines plaques reliques. Je vous les paierai généreusement, comme n'importe quel autre travail. Et j'espère que nous pourrons pratiquer nos conversations en chinois de temps en temps. J'ai honte de demander à mes serviteurs, mais un ami...";
			link.l1 = "Chang Tu fera de son mieux, Seigneur van Merden.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_32";
		break;
		
		case "PZ_Formosa_JohanVanMerden_32":
			dialog.text = "Bien. Toi et moi avons un long chemin devant nous, mon ami. Un long chemin. Ha ! Je pense que cela ferait un bon nom de couverture pour toi. Une pratique utile de mon métier. En néerlandais, c'est “Lange Afstand.” Les Anglais disent “Long Way.” Lequel préfères-tu ?";
			link.l1 = "Je préfère la version anglaise. Long. Way. Longway. Cela sonne très bien dans ma langue. Merci de m'avoir écouté, Monseigneur le Capitaine. Longway attendra votre ordre et sera prêt à vous assister et à exécuter vos demandes.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_33";
		break;
		
		case "PZ_Formosa_JohanVanMerden_33":
			DialogExit();
			
			SetCurrentTime(15, 00);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			DeleteAttribute(pchar, "questTemp.lockedMusic");
			
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			PChar = GetMainCharacter();
			LAi_SetPlayerType(PChar);
			
			bQuestDisableMapEnter = true;
			pchar.GenQuest.CabinLock = true;
			QuestToSeaLogin_Launch();
			QuestToSeaLogin_PrepareLoc("Guadeloupe", "Quest_Ships", "Quest_ship_8", false);
			DoQuestCheckDelay("PZ_SegodnyaVremya_2", 5.0);
		break;
		
		// Этап 3, СЛЕД ЗВЕЗДЫ
		case "PZ_Longway_PosleRasskaza":
			dialog.text = "En parlant de l'archive, Monseigneur le Capitaine, l'avez-vous avec vous ? C'est tout ce dont j'ai besoin - je connais le chiffre par cœur.";
			if (CheckCharacterItem(pchar, "MerdokArchive"))
			{
				notification("All Skills +", "Longway");
				AddCharacterExpToSkill(npchar, "Leadership", 50);
				AddCharacterExpToSkill(npchar, "FencingL", 50);
				AddCharacterExpToSkill(npchar, "FencingS", 50);
				AddCharacterExpToSkill(npchar, "FencingH", 50);
				AddCharacterExpToSkill(npchar, "Pistol", 50);
				AddCharacterExpToSkill(npchar, "Fortune", 50);
				AddCharacterExpToSkill(npchar, "Sneak", 50);
				AddCharacterExpToSkill(npchar, "Sailing", 50);
				AddCharacterExpToSkill(npchar, "Accuracy", 50);
				AddCharacterExpToSkill(npchar, "Cannons", 50);
				AddCharacterExpToSkill(npchar, "Grappling", 50);
				AddCharacterExpToSkill(npchar, "Defence", 50);
				AddCharacterExpToSkill(npchar, "Repair", 50);
				AddCharacterExpToSkill(npchar, "Commerce", 50);	
				
				link.l1 = "Oui, je l'ai gardé, pensant que cela pourrait être utile un jour.";
				link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_1";
			}
			else
			{
				link.l1 = "Malheureusement, non. Était-ce votre dernier espoir de retrouver sœur ?";
				link.l1.go = "PZ_Longway_PosleRasskaza_2";
			}
		break;
		
		case "PZ_Longway_PosleRasskaza_2":
			dialog.text = "Longway est très heureux que Monseigneur le Capitaine soit préoccupé. Pour l'instant, il y a encore de l'espoir. J'ai trouvé une nouvelle piste en Guadeloupe.";
			link.l1 = "D'accord, alors. Dis-moi ce qui t'est arrivé là-bas.";
			link.l1.go = "PZ_Longway_PosleRasskaza_3";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_1":
			dialog.text = "C'était une sage décision. Peut-être que nous trouverons quelque chose là-dedans qui pourra nous aider dans notre recherche de Chang Xing.";
			link.l1 = "Ce serait idéal. Étudions-le tout de suite.";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_2";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_2":
			dialog.text = "Oui, étudions-le ensemble. L'année est... 1637. Antoon van Diemen a vendu... vendu...";
			link.l1 = "Des esclaves, n'est-ce pas ?";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_3";
			AddQuestRecordInfo("PZ_ArchiveOneMerden", "1");
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_3":
			dialog.text = "Femmes de mon peuple, vendues à des hommes blancs riches.";
			link.l1 = "C'est terrible.";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_4";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_4":
			dialog.text = "Monseigneur le Capitaine, vous ne semblez pas surpris. Cela ne vous ennuie-t-il pas du tout, le destin de ces femmes ?";
			link.l1 = "Longway, of course it sincerely troubles me. I've seen this filth from the inside. But I've always been an advocate for women... and a bit of a ladies' man, to be honest. It's good you killed van Diemen; he deserved it. Is there anything else?";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_5";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_5":
			dialog.text = "Van Diemen ne travaillait qu'avec ceux en qui il avait une confiance totale - Joep van der Vink, son bras droit, et ce maudit Oliveiro Fermentelos. Et... et...";
			link.l1 = "Qu'y a-t-il ? Tu es devenu pâle, Longway.";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_6";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_6":
			dialog.text = "Johan van Merden...";
			link.l1 = "Je suis vraiment désolé. C'est terrible, mais pourquoi es-tu si choqué ? Plus tôt, tu as dit que tu avais arraché toutes les pages mentionnant Fermentelos. N'as-tu pas trouvé mention de van Merden alors ?";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_7";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_7":
			dialog.text = "Longway était pressé et a dû manquer cet élément important.";
			link.l1 = "Je vois. Quand tu seras prêt, continuons à chercher et trouvons tout ce que nous pouvons utiliser dès maintenant.";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_8";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_8":
			dialog.text = "Il est écrit que Fermentelos envoyait ses hommes capturer des femmes, les échangeait et détruisait les archives. Merden les envoyait ensuite à Batavia, où van der Vink et van Diemen vendaient nos femmes aux hommes blancs. Si seulement je l'avais appris plus tôt...";
			link.l1 = "Alors, finalement, ils ont tous travaillé ensemble. Ne te blâme pas, Longway. Tu ne pouvais pas savoir. L'archive n'est arrivée entre tes mains que récemment. Y a-t-il autre chose ?";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_9";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_9":
			dialog.text = "Oui. Cela fait presque dix ans qu'ils s'y adonnent. Tant de femmes ont perdu leurs familles, leur honneur, leur espoir... Mais ensuite Fermentelos a cessé de travailler avec van Merden. C'est la seule raison pour laquelle il m'a aidé - tout ce qu'il voulait, c'était se débarrasser de son ancien partenaire.";
			link.l1 = "Quels autres détails de leurs sales besognes sont consignés ici ?";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_10";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_10":
			dialog.text = "Encore des pensées sombres de van Merden. Il a découvert que van Diemen le trompait pour de l'argent. Alors, il m'a envoyé à Batavia, espérant que j'y périsse, mais aussi espérant que j'emmène van Diemen avec moi.";
			link.l1 = "Froid. Mais aussi incroyablement intelligent.";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_11";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_11":
			dialog.text = "Ça aurait pu être encore pire. C'est van Merden qui a envoyé ces voyous chez lui pour me tuer. Il n'est intervenu pour aider que quand il a réalisé que je pourrais les vaincre seule.";
			link.l1 = "Il avait tout prévu, sans aucun doute.";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_12";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_12":
			dialog.text = "Après mon retour en vie, il a dû penser que j'avais découvert ses véritables intentions et que je venais pour me venger. Quand nous avons parlé, il avait son arme pointée sous la table. Mais ensuite, je l'ai appelé mon premier ami blanc... il a failli éclater de rire...";
			link.l1 = "C'est affreux, Longway. C'est amer de réaliser que ceux que nous considérions comme des amis se moquaient de nous dans notre dos tout ce temps.";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_13";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_13":
			dialog.text = "Longway a appris quelque chose il y a longtemps, peu avant d'arriver dans cet archipel. J'ai été capturé par les Portugais et ils voulaient me pendre. Seigneur Rodenburg m'a sauvé la vie.";
			link.l1 = "C'est ainsi que tu es entré à son service ? Lucas était aussi à Formosa ?";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_14";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_14":
			dialog.text = "Oui, c'est ça. Et pas seulement lui - Van Berg aussi. Van Merden m'a dit que c'était lui qui avait conseillé à Rodenburg de m'épargner. Mais quelque temps plus tard, Longway a appris d'une source douteuse que c'était en fait Johan qui avait envoyé les Portugais après moi. Je ne l'ai pas cru à l'époque... mais maintenant je réalise que cela pourrait être vrai...";
			link.l1 = "Dégueulasse.";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_15";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_15":
			dialog.text = "Pourtant, des doutes se sont installés dans mon cœur ce jour-là. Alors quand j'ai appris que Monseigneur le Capitaine et van Merden s'étaient affrontés, Longway s'est souvenu de votre gentillesse et a pris votre parti.";
			link.l1 = "C'était la bonne décision, Longway. Heh, il s'avère que tout ce temps, ton premier véritable ami blanc, c'était moi.";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_16";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_16":
			dialog.text = "Il s'avère donc ainsi, Monseigneur le Capitaine. Maintenant je comprends. Van Merden m'a dit que j'étais son ami. Mais en réalité, Longway n'était rien de plus qu'un autre ouvrier pour lui - juste plus utile que la plupart.\nC'est tout. Les autres pages concernent la comptabilité, ainsi que les détails commerciaux entre Van Berg et Rodenburg.";
			link.l1 = "Je vois. Et maintenant il est grand temps que tu me dises ce que tu as fait à la Guadeloupe.";
			link.l1.go = "PZ_Longway_PosleRasskaza_3";
		break;
		
		case "PZ_Longway_PosleRasskaza_3":
			dialog.text = "Je cherchais l'Étoile du Matin. L'une des pages arrachées des archives disait qu'elle a été vue pour la dernière fois près de Saint-Christophe.";
			link.l1 = "Pourquoi là-bas ? Nous avions convenu de nous rencontrer en Guadeloupe, et je t'y ai trouvé.";
			link.l1.go = "PZ_Longway_PosleRasskaza_4";
		break;
		
		case "PZ_Longway_PosleRasskaza_4":
			dialog.text = "Parce que Saint-Christophe est la demeure de Georges Gravel, un des informateurs de van Merden. Georges croit que je travaille encore pour Johan. De plus, Gravel a autrefois commis une grave offense contre van Merden. Et Longway a aidé à la dissimuler.";
			link.l1 = "Et quelle était cette offense ?";
			link.l1.go = "PZ_Longway_PosleRasskaza_5";
		break;
		
		case "PZ_Longway_PosleRasskaza_5":
			dialog.text = "Ce n'est pas important. Ce qui est important, c'est que Georges devait une dette à Longway. Alors, je suis allé à l'église où Gravel travaille comme assistant prêtre. Monseigneur le Capitaine est-il prêt à écouter la suite ? Vous semblez un peu distrait.";
			link.l1 = "Désolé, je me suis laissé distraire. Aye, bien sûr, vas-y, Longway.";
			link.l1.go = "PZ_Longway_PosleRasskaza_6";
		break;
		
		case "PZ_Longway_PosleRasskaza_6":
			DialogExit();
			SetCurrentTime(9, 00);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			SetMainCharacterIndex(GetCharacterIndex("Longway"));
			PChar = GetMainCharacter();
			LAi_SetPlayerType(PChar);
			
			pchar.GenQuest.FrameLockEsc = true;
			SetLaunchFrameFormParam("Capsterville,"+ NewStr() +"St. Christopher Island.", "Reload_To_Location", 0, 4.0);
			SetLaunchFrameReloadLocationParam("Kapstervil", "patrol", "patrol12", "PZ_Kapstervil_Start");
			LaunchFrameForm();
		break;
		
		case "PZ_Zhorzh_1":
			dialog.text = "Bien, tu n'es pas trop en retard. Je ne voudrais pas rester ici plus longtemps que nécessaire, tu sais ! De quoi as-tu besoin cette fois, Longway ?";
			link.l1 = "Changez votre ton, Gravel. L'organisation a besoin de vos services.";
			link.l1.go = "PZ_Zhorzh_2";
		break;
		
		case "PZ_Zhorzh_2":
			dialog.text = "Je dois avouer que je n'ai pas eu de nouvelles d'eux depuis longtemps. M'ont-ils oublié ?";
			link.l1 = "Je peux leur rappeler. Peut-être en racontant à Lord van Merden ce que vous avez fait.";
			link.l1.go = "PZ_Zhorzh_3";
		break;
		
		case "PZ_Zhorzh_3":
			dialog.text = "D'accord, d'accord, pas besoin de se mettre en colère ! Que puis-je faire pour vous ?";
			link.l1 = "J'ai besoin d'informations sur l'Étoile du Matin. Tout ce que tu peux trouver. Plus il y en a, mieux c'est.";
			link.l1.go = "PZ_Zhorzh_4";
		break;
		
		case "PZ_Zhorzh_4":
			dialog.text = "Bien sûr, mais cela prendra du temps ! Deux jours ! Au minimum.";
			link.l1 = "Pourquoi si long ?";
			link.l1.go = "PZ_Zhorzh_5";
		break;
		
		case "PZ_Zhorzh_5":
			dialog.text = "Normalement, il me faudrait prendre de l'argent de la boîte à offrandes pour délier les langues de mes informateurs. Mais nous avons été volés récemment ! Le Père annoncera bien sûr une nouvelle collecte de dons, mais nous devons encore réparer notre toit - il fuit ! Il va falloir beaucoup de dons pour le réparer.";
			link.l1 = "Deux jours. Je ne peux pas rester ici éternellement. Je n'ai pas ce genre de temps. Longway n'est pas connu pour sa patience. Le Seigneur van Merden encore moins. Ou devrais-je te le rappeler, Gravel ?";
			link.l1.go = "PZ_Zhorzh_6";
		break;
		
		case "PZ_Zhorzh_6":
			dialog.text = "Je ne peux pas contrôler ce qui est hors de ma portée ! Je ferai ce que je peux. Cependant, je découvrirais beaucoup plus vite si vous trouviez ces brigands et rameniez nos dons !";
			link.l1 = "Je vais y réfléchir. Commence à chercher. Deux jours. Pas plus. Rendez-vous au même endroit et à la même heure.";
			link.l1.go = "PZ_Zhorzh_7";
		break;
		
		case "PZ_Zhorzh_7":
			DialogExit(); 
			SetCurrentTime(12, 00);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			
			pchar.GenQuest.FrameLockEsc = true;
			SetLaunchFrameFormParam("A Day Later..."+ NewStr() +"In Search of the Church Robbers.", "Reload_To_Location", 0, 4.0);
			SetLaunchFrameReloadLocationParam("Kapstervil_Jungle", "goto", "goto1", "PZ_Kapstervil_Jungle");
			LaunchFrameForm();
		break;
		
		case "PZ_VorugaChurch_1":
			dialog.text = "Eh bien, regarde ça ! Un homme aux yeux étroits sur notre île ! Tu fuis tes maîtres, hein ? De qui te caches-tu, si tu ne me permets de demander ?";
			link.l1 = "Je suis un homme libre.";
			link.l1.go = "PZ_VorugaChurch_2";
		break;
		
		case "PZ_VorugaChurch_2":
			dialog.text = "Ha ! Bien sûr que tu l'es. Mais tu as l'air fort et intelligent, même si tes yeux sont un peu bridés. Tu veux rejoindre notre bande ? Je ne pense pas que tu aies d'autre endroit où aller, de toute façon.";
			link.l1 = "Longway pense que tu es plus intéressé par le voler que par le recruter.";
			link.l1.go = "PZ_VorugaChurch_3";
		break;
		
		case "PZ_VorugaChurch_3":
			dialog.text = "Héhé, considère-toi chanceux. Nous avons récemment pillé une église en ville, tu peux le croire ? Pourquoi ? Parce que voler des voleurs, ce n'est pas vraiment voler.";
			link.l1 = "Je n'avais pas prévu de te traquer, mais je suis content de t'avoir trouvé.";
			link.l1.go = "PZ_VorugaChurch_4";
		break;
		
		case "PZ_VorugaChurch_4":
			dialog.text = "Nous traquer ? Ah, donc tu es un mercenaire, pas un travailleur en fuite. Mauvaise nouvelle pour toi alors.";
			link.l1 = "Exactement.";
			link.l1.go = "PZ_VorugaChurch_5";
		break;
		
		case "PZ_VorugaChurch_5":
			DialogExit();
			EndQuestMovie();
			InterfaceStates.Buttons.Save.enable = false;
			
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			LAi_SetCheckMinHP(npchar, 1, true, "PZ_VorugaChurch_win");
			for (i=11; i<=14; i++)
			{
				sld = CharacterFromID("PZ_KapstervilBandit_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
		break;
		
		case "PZ_VorugaChurch_6":
			if (!CharacterIsAlive("PZ_KapstervilBandit_11") && !CharacterIsAlive("PZ_KapstervilBandit_12") && !CharacterIsAlive("PZ_KapstervilBandit_13"))
			{
				dialog.text = "Merde... Pourquoi ne m'as-tu pas tué tout de suite ? Que veux-tu de moi ? Vas-tu me traîner en prison ?";
				link.l1 = "Je n'ai aucun intérêt pour ça. Dis-moi simplement où tu as caché l'or.";
				link.l1.go = "PZ_VorugaChurch_7";
			}
			else
			{
				dialog.text = RandSwear()+"";
				link.l1 = "";
				link.l1.go = "exit";
				AddDialogExitQuest("PZ_VorugaChurch_win");	
			}
		break;
		
		case "PZ_VorugaChurch_7":
			dialog.text = "Hé... Espèce de salaud à la peau jaune...";
			link.l1 = "La patience de Longway s'épuise. Je vais découvrir la vérité de toute façon. La seule question est combien de temps tu vas souffrir.";
			link.l1.go = "PZ_VorugaChurch_8";
			LAi_group_Delete("EnemyFight");
		break;
		
		case "PZ_VorugaChurch_8":
			dialog.text = "D'accord, d'accord... C'est dans une grotte. Tout est là. L'argent est à toi. Juste... ne me tue pas, d'accord ?";
			link.l1 = "Je n'ai pas dit qu'il n'y aurait pas de souffrances du tout...";
			link.l1.go = "PZ_VorugaChurch_9";
		break;
		
		case "PZ_VorugaChurch_9":
			DialogExit();
			
			LAi_SetActorType(pchar);
			LAi_ActorAnimation(pchar, "Shot", "1", 1.5);
			DoQuestCheckDelay("PZ_VorugaChurch_win_2", 0.9);
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_0":
			StartQuestMovie(true, false, true);
			locCameraFromToPos(2.48, 0.87, 9.26, true, 6.72, -0.85, 6.05);
			dialog.text = "(en mandarin) Voici la cachette des bandits.";
			link.l1 = "";
			link.l1.go = "PZ_Kapstervil_GrotSoldiers_0_1";
			CharacterTurnToLoc(pchar, "box", "box1");
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_0_1":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "goto", "goto2", "PZ_Kapstervil_Grot_1", -1);
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_1":
			dialog.text = "(en mandarin) C'est beaucoup !";
			link.l1 = "";
			link.l1.go = "PZ_Kapstervil_GrotSoldiers_1_1";
			CharacterTurnToLoc(pchar, "box", "box1");
			locCameraFromToPos(6.83, 2.65, 6.62, true, 2.83, -1.00, 7.67);
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_1_1":
			dialog.text = "(en mandarin) J'entends des pas...";
			link.l1 = "Il y a quelqu'un d'autre ici...";
			link.l1.go = "PZ_Kapstervil_GrotSoldiers_2";
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_2":
			DialogExit();
			
			sld = GetCharacter(NPC_GenerateCharacter("PZ_Kapstervil_GrotSoldier_1", "sold_fra_7", "man", "man", 5, FRANCE, -1, true, "soldier"));
			LAi_SetActorType(sld);
			sld.CantLoot = true;
			ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto4");
			TeleportCharacterToPosAy(sld, 4.17, 0.65, -1.42, 0.00);
			
			sld = GetCharacter(NPC_GenerateCharacter("PZ_Kapstervil_GrotSoldier_2", "sold_fra_5", "man", "man", 5, FRANCE, -1, true, "soldier"));
			LAi_SetActorType(sld);
			sld.CantLoot = true;
			ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto4");
			TeleportCharacterToPosAy(sld, 4.10, 0.65, 0.30, 3.00);
			
			LAi_SetStayType(pchar);
			LAi_Fade("PZ_Kapstervil_Grot_2", "");
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_3":
			dialog.text = "Que diable faisons-nous ici ? Il ne reste plus personne - nous avons bien vérifié que tous les voleurs étaient partis.";
			link.l1 = "";
			link.l1.go = "exit";
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("PZ_Kapstervil_GrotSoldier_2"));
			AddDialogExitQuest("PZ_Kapstervil_Grot_4");
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_5":
			dialog.text = "C'est ça, imbécile ! Ils reviendront, et nous leur réserverons un accueil chaleureux.";
			link.l1 = "";
			link.l1.go = "exit";
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("PZ_Kapstervil_GrotSoldier_1"));
			AddDialogExitQuest("PZ_Kapstervil_Grot_5");
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_7":
			dialog.text = "Je vais jeter un coup d'œil, m'assurer que personne ne se cache. De toute façon, je m'ennuie...";
			link.l1 = "";
			link.l1.go = "PZ_Kapstervil_GrotSoldiers_8";
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("PZ_Kapstervil_GrotSoldier_2"));
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_8":
			DialogExit();
			LAi_Fade("PZ_Kapstervil_Grot_5_1", "");
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_9":
			dialog.text = "(en mandarin) Soldats ! Quel malheur... Que suis-je censé faire maintenant ?";
			link.l1 = "(en mandarin) J'ai besoin de cet argent plus que les soldats blancs ! Je ne pars pas sans ça !";
			link.l1.go = "PZ_Kapstervil_GrotSoldiers_10";
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_10":
			DialogExit();
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			
			for (i=1; i<=2; i++)
			{
				sld = CharacterFromID("PZ_Kapstervil_GrotSoldier_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyWithRadius");
				LAi_group_SetRelation("EnemyWithRadius", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
				LAi_group_SetLookRadius("EnemyWithRadius", 6.0);
				LAi_group_SetHearRadius("EnemyWithRadius", 2.0);
				LAi_group_SetSayRadius("EnemyWithRadius", 12.0);
				LAi_group_SetCheck("EnemyWithRadius", "PZ_Kapstervil_Grot_6");
			}
		break;
		
		case "PZ_Zhorzh_11":
			dialog.text = "Ah, monsieur Longway, vous êtes revenu !";
			link.l1 = "Bien sûr. Y avait-il un doute ? As-tu trouvé quelque chose sur l’Étoile du Matin, Georges ?";
			link.l1.go = "PZ_Zhorzh_12";
		break;
		
		case "PZ_Zhorzh_12":
			dialog.text = "Oui, monsieur. C'est un lourd galion, commandé par un Espagnol, ou du moins c'est ce qu'on dit...";
			link.l1 = "Il est Portugais. Vous, les Blancs, vous ne pouvez même pas vous distinguer les uns des autres.";
			link.l1.go = "PZ_Zhorzh_13";
		break;
		
		case "PZ_Zhorzh_13":
			dialog.text = "Oh, bien sûr. Mon erreur. Quoi qu'il en soit, j'ai découvert qu'il a considérablement modifié le galion pour tenter de le faire passer pour un navire marchand, avec des canons de petit calibre et un équipage réduit. Mais il a agrandi la cale, la remplissant à ras bord - il est si lourd qu'il peut à peine naviguer.";
			link.l1 = "Alors il a décidé de commencer une nouvelle vie. Bien. Maintenant, où puis-je le trouver ?";
			link.l1.go = "PZ_Zhorzh_14";
		break;
		
		case "PZ_Zhorzh_14":
			dialog.text = "C'est plus compliqué. Il se déplace constamment entre nos colonies et celles des Anglais, mais seulement parmi les îles du Vent. Cependant, j'ai appris qu'il est en route pour Basse-Terre avec une grande cargaison de vin en ce moment.";
			link.l1 = "Je dois trouver comment y arriver rapidement.";
			link.l1.go = "PZ_Zhorzh_15";
		break;
		
		case "PZ_Zhorzh_15":
			dialog.text = "C'est votre souci, monsieur Longway. J'ai assez de problèmes moi-même... comme réparer ce maudit toit.";
			link.l1 = "En parlant de soucis, j'ai trouvé ces voleurs d'église. Voici votre argent de donation. Réparez le toit - ce n'est pas bien pour votre Dieu d'en être privé.";
			link.l1.go = "PZ_Zhorzh_16";
		break;
		
		case "PZ_Zhorzh_16":
			dialog.text = "Merci beaucoup, monsieur Longway ! Je n'aurais jamais pensé que vous seriez celui qui ferait cela.";
			link.l1 = "Je ne le pensais pas non plus. Mais je devais faire quelque chose pendant ces deux jours.";
			link.l1.go = "PZ_Zhorzh_17";
		break;
		
		case "PZ_Zhorzh_17":
			dialog.text = "Alors, tu dois te rendre à la Guadeloupe ? Je te trouverai un navire qui s'y dirige. Attends-toi à avoir de mes nouvelles bientôt !";
			link.l1 = "Ce serait utile. Merci, Georges.";
			link.l1.go = "PZ_Zhorzh_18";
		break;
		
		case "PZ_Zhorzh_18":
			DialogExit();
			SetCurrentTime(9, 00);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			EndQuestMovie();
			InterfaceStates.Buttons.Save.enable = false;
			
			pchar.GenQuest.FrameLockEsc = true;
			SetLaunchFrameFormParam("The Next Morning..."+ NewStr() +"Capsterville", "Reload_To_Location", 0, 4.0);
			SetLaunchFrameReloadLocationParam("Kapstervil", "goto", "goto19", "PZ_Kapstervil_PoiskZvezda");
			LaunchFrameForm();
		break;
		
		case "PZ_Kapstervil_Kurier_1":
			dialog.text = "Vous devez être une connaissance de Georges ? Il m'a demandé de vous donner ceci.";
			link.l1 = "Une note ? Ma gratitude. Comment savais-tu que c'était pour moi ?";
			link.l1.go = "PZ_Kapstervil_Kurier_2";
		break;
		
		case "PZ_Kapstervil_Kurier_2":
			dialog.text = "Sérieusement ?";
			link.l1 = "Oh, d'accord.";
			link.l1.go = "PZ_Kapstervil_Kurier_3";
		break;
		
		case "PZ_Kapstervil_Kurier_3":
			DialogExit();
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("PZ_Kapstervil_ChitaemPismo", 1.5);
		break;
		
		case "PZ_Kapstervil_ChitaemPismo_Dialog":
			dialog.text = "(Lit la lettre) Monsieur Longway, la pinasse 'Provence' part pour Basse-Terre demain matin. Le capitaine, Mathieu Terugny, se trouve à la taverne. Transmettez mes salutations à monsieur van Merden. - Georges Gravel.";
			link.l1 = "";
			link.l1.go = "PZ_Kapstervil_ChitaemPismo_Dialog_2";
		break;
		
		case "PZ_Kapstervil_ChitaemPismo_Dialog_2":
			DialogExit();
			LAi_RemoveCheckMinHP(pchar);
			chrDisableReloadToLocation = false;
			LAi_SetPlayerType(pchar);
			sld = characterFromId("PZ_Kapstervil_tavernkeeper");
			sld.dialog.currentnode = "PZ_TerunyiTavern1";
			LAi_SetBarmanType(sld);
			AddLandQuestMark(sld, "questmarkmain");
		break;
		
		case "PZ_TerunyiTavern1":
			dialog.text = "Nous ne servons pas de boissons à des gens comme vous ici. Et à moins que je veuille entendre des plaintes à propos des puces, je ne vous louerai pas de chambre non plus.";
			link.l1 = "Je n'ai pas besoin d'un verre ni d'une chambre. Et... Longway n'a pas de puces.";
			link.l1.go = "PZ_TerunyiTavern2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_TerunyiTavern2":
			dialog.text = "Comment diable suis-je censé savoir ? Bon, crache le morceau. Que veux-tu ? Alors dégage.";
			link.l1 = "Je le ferai. Je cherche le Capitaine Mathieu Terugny. Je n'arrive pas à le trouver. Sais-tu où il est ?";
			link.l1.go = "PZ_TerunyiTavern3";
		break;
		
		case "PZ_TerunyiTavern3":
			dialog.text = "Il est occupé à préparer son navire pour appareiller dans le magasin local. C'est bien plus important que de bavarder avec un Chinois comme toi, mais tu ne sembles pas le comprendre.";
			link.l1 = "En fait, j'étais... Peu importe. Ce n'est pas important pour le moment.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_CreateTerunyi");
		break;
		
		case "PZ_Terunyi1":
			dialog.text = "Que veux-tu, Chinois? Ne vois-tu pas que je suis occupé? Je dois préparer mon navire.";
			link.l1 = "Capitaine Mathieu Terugny ?";
			link.l1.go = "PZ_Terunyi2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_Terunyi2":
			dialog.text = "Eh bien, cela vient de cesser d'être drôle. Comment quelqu'un comme toi sait qui je suis ? Quelqu'un t'a envoyé ?";
			link.l1 = "Pas besoin de t'inquiéter. J'ai entendu dire que tu navigues vers Basse-Terre. Peux-tu me prendre comme passager ? Je paierai.";
			link.l1.go = "PZ_Terunyi3";
		break;
		
		case "PZ_Terunyi3":
			dialog.text = "Ça ne fait que s'améliorer. Je me dirige vers St. Pierre, pas Basse-Terre, mais c'est un petit détour. C'est bien, parce que je n'aurai pas à te garder sur le navire plus longtemps que nécessaire. Cinq mille pesos. Nous partons dans trois heures. Paie sur le quai. Même si je suis marchand, il n'y a pas de marchandage. Compris ?";
			link.l1 = "Oui. Merci. À plus tard sur le quai, Capitaine Terugny.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_TeleportToPier");
		break;
		
		case "PZ_Terunyi4":
			dialog.text = "Tu es venu après tout, Chinetoque. Je pensais que tu ne le ferais pas - personne ne donne jamais de l'argent réel à des gens comme toi volontairement.";
			link.l1 = "Cinq mille pesos, comme vous l'avez demandé. Êtes-vous prêt à lever l'ancre ?";
			link.l1.go = "PZ_Terunyi5";
		break;
		
		case "PZ_Terunyi5":
			AddMoneyToCharacter(pchar, -5000);
			
			dialog.text = "Non, non ! C'est moi qui devrais te le demander. Mais je suppose que tu es prêt. Allons-y. Tu rameras le canot. Et ne t'attends pas à une cabine correcte ! Tu es la seule raison pour laquelle nous faisons ce détour.";
			link.l1 = "Je n'ai pas besoin de réconfort. Amenez-moi juste là-bas.";
			link.l1.go = "PZ_Terunyi6";
		break;
		
		case "PZ_Terunyi6":
			DialogExit();
			
			SetCurrentTime(2, 00);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			InterfaceStates.Buttons.Save.enable = true;
			
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			PChar = GetMainCharacter();
			LAi_SetPlayerType(PChar);
			
			QuestToSeaLogin_Launch();
			QuestToSeaLogin_PrepareLoc("Guadeloupe", "Quest_Ships", "Quest_ship_8", false);
			DoQuestCheckDelay("PZ_Flashback_Final_1", 3.5);
		break;
		
		case "PZ_Longway_PosleRasskaza21":
			dialog.text = "...alors Longway n'a pas pu déterminer exactement où se dirige l'Étoile du Matin.";
			link.l1 = "Ouais, je vois comment tu t'es retrouvé dans tout ce bazar.";
			link.l1.go = "PZ_Longway_PosleRasskaza22";
		break;
		
		case "PZ_Longway_PosleRasskaza22":
			if (GetCharacterIndex("Helena") != -1 && CheckPassengerInCharacter(pchar, "Helena")) sStr = "Helena";
			else sStr = "Alonso";
			dialog.text = "J'ai vu un brick dans les eaux de la Guadeloupe. Peut-être que c'était le Banten. Je vais essayer d'en savoir plus. Eh bien, tu peux y aller maintenant, Longway. Apporte-moi "+sStr+".";
			link.l1.go = "PZ_Longway_PosleRasskaza23";
		break;
		
		case "PZ_Longway_PosleRasskaza23":
			DialogExit();
			LAi_SetStayType(pchar);
			LAi_FadeLong("PZ_LongwayUhoditIzKauty", "PZ_HelenaOrAlonso");
		break;
		
		case "PZ_Helena_1":
			if (sti(pchar.questTemp.Saga.HelenRelation) >= 6)
			{
				dialog.text = "Mon Capitaine, tout va bien ? Je suis venue dès que Longway a dit que vous aviez besoin de moi.";
				link.l1 = "J'essaie juste de rassembler les morceaux. Te souviens-tu du nom de cette brigantine que nous avons vue au large de l'île ?";
				link.l1.go = "PZ_Helena_3";
			}
			else
			{
				dialog.text = "Vous vouliez me voir ?";
				link.l1 = "Ouais. Te souviens-tu de la brigantine que nous avons vue récemment ? Découvre son emplacement et son nom.";
				link.l1.go = "PZ_Helena_2";
			}
		break;
		
		case "PZ_Helena_2":
			dialog.text = "Je me souviens, mais pourquoi cet intérêt soudain pour une brigantine ? Découvrir cela pourrait prendre un certain temps.";
			link.l1 = "Helen, fais-le, s'il te plaît. Et oui, je sais que cela pourrait prendre un certain temps. J'attendrai.";
			link.l1.go = "PZ_PoiskBanten";
		break;
		
		case "PZ_Helena_3":
			dialog.text = "Non, je n'ai pas vérifié. Pourquoi ? C'est important ?";
			link.l1 = "Mm-hmm. Peux-tu en savoir plus ? Je dois savoir où ils sont ancrés maintenant, s'ils n'ont pas déjà quitté les eaux de la Guadeloupe.";
			link.l1.go = "PZ_Helena_4";
		break;
		
		case "PZ_Helena_4":
			dialog.text = "Bien sûr. Juste pour te prévenir, cela pourrait prendre un certain temps. Je vais prendre un canot et quelques gars pour aider, ouais, hein, Charles ?";
			link.l1 = "Bien sûr, Hélène, merci. Je vais attendre.";
			link.l1.go = "PZ_PoiskBanten";
		break;
		
		case "PZ_Alonso_11":
			dialog.text = "Monseigneur le Capitaine, vous avez appelé ?";
			link.l1 = "Oui, Alonso. Nous avons croisé une brigantine dans les eaux au large de l'île quand nous sommes retournés chercher Longway. As-tu eu l'occasion de connaître son nom ?";
			link.l1.go = "PZ_Alonso_12";
		break;
		
		case "PZ_Alonso_12":
			dialog.text = "Non, mon travail est de surveiller les nouvelles recrues et de participer à l'avant-garde de l'abordage. En plus, je ne possède pas de longue-vue, et nous n'étions pas si proches.";
			link.l1 = "Vrai. Mais je dois le découvrir malgré tout. Fais-le.";
			link.l1.go = "PZ_Alonso_13";
		break;
		
		case "PZ_Alonso_13":
			dialog.text = "Oui, Capitaine. Je pense que je peux le faire en une demi-journée.";
			link.l1 = "Dépêche-toi. Je t'attendrai.";
			link.l1.go = "PZ_PoiskBanten";
		break;
		
		case "PZ_PoiskBanten":
			DialogExit();
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			LAi_SetStayType(pchar);
			SetLaunchFrameFormParam("Five hours later...", "PZ_PoiskBanten_2", 0, 4.0);
			LaunchFrameForm();
			locCameraSleep(true);
		break;
		
		case "PZ_Helena_5":
			if (sti(pchar.questTemp.Saga.HelenRelation) >= 6)
			{
				dialog.text = "J'ai tout appris. Tout s'est bien passé pendant mon absence, mon capitaine ?";
				link.l1 = "Oui, je vais bien, merci, Helen. Dis-moi.";
				link.l1.go = "PZ_Helena_7";
			}
			else
			{
				dialog.text = "Pfiou, je suis de retour. J'ai trouvé votre brigantin.";
				link.l1 = "Bienvenue. Où se trouve-t-elle et quel est son nom ?";
				link.l1.go = "PZ_Helena_6";
			}
		break;
		
		case "PZ_Helena_6":
			dialog.text = "Le Banten. Ce nom te dit quelque chose, n'est-ce pas ? Elle est au phare maintenant, et quelques-uns de son équipage sont venus à terre. Allons-nous attaquer ce navire ?";
			link.l1 = "Non, nous devons découvrir exactement qui est allé à terre. Nous nous dirigerons vers le phare par voie terrestre. Étant donné que nous avons déjà été retardés, il est grand temps de quitter le port. Nous devrions jeter l'ancre quelque part à l'écart. La plage de Capster serait bien. Dépêchons-nous, Helen.";
			link.l1.go = "PZ_BasTerMayak";
		break;
		
		case "PZ_Helena_7":
			dialog.text = "Eh bien, la brigantine s'appelle le Banten, et elle est ancrée au phare. Certains membres de l'équipage ont débarqué là-bas. Que vas-tu faire ?";
			link.l1 = "Pour le découvrir, nous devrons atteindre le phare sans être remarqués, et nous ne pouvons le faire qu'à pied. Notre navire doit jeter l'ancre en lieu sûr. Que diriez-vous de la plage de Capster ?";
			link.l1.go = "PZ_Helena_8";
		break;
		
		case "PZ_Helena_8":
			dialog.text = "Bonne idée. Charles, veux-tu que je t'accompagne au phare ?";
			link.l1 = "Je vais y réfléchir pendant que nous déplaçons le navire - tu es déjà assez fatigué comme ça.";
			link.l1.go = "PZ_BasTerMayak";
		break;
		
		case "PZ_Alonso_15":
			dialog.text = "Je suis revenu dès que j'ai terminé, Monseigneur le Capitaine.";
			link.l1 = "Très bien. Rapport, Alonso.";
			link.l1.go = "PZ_Alonso_16";
		break;
		
		case "PZ_Alonso_16":
			dialog.text = "La brigantine est encore au large de l'île - près du phare, pour être précis. Le nom à la poupe est Banten. Quelques membres de leur équipage sont allés à terre.";
			link.l1 = "Bon travail, Alonso. Prépare l'équipage à lever l'ancre immédiatement.";
			link.l1.go = "PZ_Alonso_17";
		break;
		
		case "PZ_Alonso_17":
			dialog.text = "Préparez-vous pour l'abordage, aussi ?";
			link.l1 = "Pas encore. Si leur capitaine se dirige vers le phare, il pourrait se cacher dans la ville si nous attaquons en mer. Nous nous dirigerons vers Capster Beach pour sécuriser notre navire, puis nous approcherons du phare à pied.";
			link.l1.go = "PZ_BasTerMayak";
		break;
		
		case "PZ_BasTerMayak":
			DialogExit();
			locCameraSleep(false);
			LAi_SetPlayerType(pchar);
			ChangeCharacterAddressGroup(npchar, "none", "", "");
			chrDisableReloadToLocation = false;
			bDisableCharacterMenu = false;
			bQuestDisableMapEnter = false;
			DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
			Island_SetReloadEnableGlobal("Guadeloupe", true);
			
			AddQuestRecord("PZ", "15");
			PChar.quest.PZ_Banten_PlyazhKapster.win_condition.l1 = "location";
			PChar.quest.PZ_Banten_PlyazhKapster.win_condition.l1.location = "Shore29";
			PChar.quest.PZ_Banten_PlyazhKapster.win_condition = "PZ_Banten_PlyazhKapster";
			
			PChar.quest.PZ_Banten_PlyazhKapster_Proval.win_condition.l1 = "Timer";
			PChar.quest.PZ_Banten_PlyazhKapster_Proval.win_condition.l1.date.hour = sti(GetTime() + 7);
			PChar.quest.PZ_Banten_PlyazhKapster_Proval.win_condition.l1.date.day = GetAddingDataDay(0, 0, 0);
			PChar.quest.PZ_Banten_PlyazhKapster_Proval.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			PChar.quest.PZ_Banten_PlyazhKapster_Proval.win_condition.l1.date.year = GetAddingDataYear(0, 0, 0);
			PChar.quest.PZ_Banten_PlyazhKapster_Proval.win_condition = "PZ_Banten_PlyazhKapster_Proval";
			
			if (GetCharacterIndex("Helena") != -1 && CheckPassengerInCharacter(pchar, "Helena"))
			{
				LAi_SetActorType(npchar);
				LAi_ActorFollow(npchar, pchar, "", -1);
				LAi_SetOfficerType(npchar);
				npchar.Dialog.Filename = "Quest\Saga\Helena.c";
				npchar.Dialog.CurrentNode = "Helena_officer";
			}
		break;
		
		case "PZ_Longway_21":
			dialog.text = "Monseigneur le Capitaine, regardez ! Il y a quelqu'un à l'intérieur du phare.";
			link.l1 = "Bien, nous sommes à l'heure ! Dépêchons-nous et attrapons-les. Alonso aura beaucoup de travail aujourd'hui.";
			link.l1.go = "PZ_Longway_22";
		break;
		
		case "PZ_Longway_22":
			dialog.text = "Mais que se passe-t-il s'ils meurent dans le processus ?";
			link.l1 = "Que suggérez-vous ?";
			link.l1.go = "PZ_Longway_23";
		break;
		
		case "PZ_Longway_23":
			dialog.text = "Nous nous faufilons silencieusement et écoutons d'abord leur conversation.";
			link.l1 = "Je doute que nous puissions faire cela sans être vus depuis la fenêtre. Mais essayons quand même.";
			link.l1.go = "PZ_Longway_24";
		break;
		
		case "PZ_Longway_24":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			LAi_SetOfficerType(npchar);
			npchar.Dialog.Filename = "Quest\HollandGambit\Longway.c";
			npchar.Dialog.CurrentNode = "Longway_officer";
			LAi_SetCheckMinHP(npchar, 1, true, "SkritoeBessmertie");
			PChar.quest.PZ_MayakPodslushivanie.win_condition.l1 = "locator";
			PChar.quest.PZ_MayakPodslushivanie.win_condition.l1.location = "Mayak4";
			PChar.quest.PZ_MayakPodslushivanie.win_condition.l1.locator_group = "goto";
			PChar.quest.PZ_MayakPodslushivanie.win_condition.l1.locator = "goto31";
			PChar.quest.PZ_MayakPodslushivanie.win_condition = "PZ_MayakPodslushivanie";
		break;
		
		case "PZ_MayakPodslushivanie_Dialog_1":
			dialog.text = "Pense à ce que j'ai dit. Réfléchis bien. L'argent n'est pas un problème - dans certaines limites, bien sûr. Mais même cette limite te semblera une montagne d'or - le Chinois doit mourir ! J'ai déjà envoyé des hommes à sa poursuite, mais en vain. Cette fois, cependant, s'ils s'associent avec tes hommes...";
			link.l1 = " ";
			link.l1.go = "PZ_MayakPodslushivanie_Dialog_1_1";
			CharacterTurnByChr(npchar, CharacterFromID("PZ_BasTerJailOff_Clone"));
		break;
		
		case "PZ_MayakPodslushivanie_Dialog_1_1":
			StartInstantDialog("PZ_BasTerJailOff_Clone", "PZ_MayakPodslushivanie_Dialog_2", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_MayakPodslushivanie_Dialog_2":
			dialog.text = "Regarde, on nous observe ! C'est lui ! Lui et son maudit capitaine !";
			link.l1 = "";
			link.l1.go = "PZ_MayakPodslushivanie_Dialog_3";
			CharacterTurnToLoc(npchar, "item", "flower5");
		break;
		
		case "PZ_MayakPodslushivanie_Dialog_3":
			DialogExit();
			EndQuestMovie();
			locCameraSleep(false);
			locCameraToPos(1.52, 18.87, -9.55, true);
			DoQuestCheckDelay("CameraReset", 1.0);
			DeleteAttribute(pchar, "questTemp.NoFast");
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			
			sld = CharacterFromID("PZ_Neznakomets");
			ChangeCharacterAddressGroup(sld, "none", "", "");
			
			sld = CharacterFromID("PZ_BasTerJailOff_Clone");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_SetCheckMinHP(sld, 1, true, "PZ_MayakPodslushivanie_win");
			
			for (i=1; i<=4; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("PZ_Neznakomets_Bandit_"+i, "citiz_" + (rand(9) + 41), "man", "man", sti(pchar.rank), PIRATE, -1, true, "pirate"));
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload2");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
		break;
		
		case "PZ_Mayak_KomendantSidit_1":
			if (!CharacterIsAlive("PZ_Neznakomets_Bandit_1") && !CharacterIsAlive("PZ_Neznakomets_Bandit_2") && !CharacterIsAlive("PZ_Neznakomets_Bandit_3")&& !CharacterIsAlive("PZ_Neznakomets_Bandit_4"))
			{
				dialog.text = "Maudit sois-tu, sale Asiatique... J'ai dû endurer tant de choses à cause de toi. Et maintenant, pour tout cela, je suis sur le point de mourir...";
				link.l1 = "Nous vous conduirons chez notre médecin, Monseigneur le Commandant. Dites-nous simplement à qui vous parliez - c'est très important.";
				link.l1.go = "PZ_Mayak_KomendantSidit_2";
				LAi_group_Delete("EnemyFight");
			}
			else
			{
				dialog.text = RandSwear()+"";
				link.l1 = "";
				link.l1.go = "exit";
				AddDialogExitQuest("PZ_MayakPodslushivanie_win");	
			}
		break;
		
		case "PZ_Mayak_KomendantSidit_2":
			dialog.text = "Son nom... est Joep van der Vink, il... kha...";
			link.l1 = "...";
			link.l1.go = "PZ_Mayak_KomendantSidit_3";
		break;
		
		case "PZ_Mayak_KomendantSidit_3":
			DialogExit();
			LAi_SetImmortal(npchar, false);
			LAi_KillCharacter(npchar);
			DoQuestCheckDelay("PZ_Mayak_Longway", 1.5);
		break;
		
		case "PZ_Longway_25":
			dialog.text = "";
			link.l1 = "Il est mort... Eh bien, au moins nous connaissons le nom. Longway... ?";
			link.l1.go = "PZ_Longway_26";
		break;
		
		case "PZ_Longway_26":
			dialog.text = "Ça ne peut absolument pas être...";
			link.l1 = "Tu as l'air un peu pâle, Longway.";
			link.l1.go = "PZ_Longway_27";
		break;
		
		case "PZ_Longway_27":
			dialog.text = "Longway était assez sûr d'avoir tué van der Vink il y a dix ans\nIls s'échappent ! Leur navire est rapide !";
			link.l1 = "Oui, une brigantine merveilleuse... malheureusement pour nous. Même si nous atteignons notre navire à temps, ils seront partis d'ici que nous levions les voiles et attrapions le vent.";
			link.l1.go = "PZ_Longway_28";
		break;
		
		case "PZ_Longway_28":
			dialog.text = "Ce pourrait être la fin...";
			link.l1 = "Non, Longway. Écoute-moi. S'ils prévoient de rester dans l'Archipel, nous finirons par les croiser tôt ou tard - le monde est petit, et les Caraïbes le sont encore plus. Dès que nous retrouverons leur piste, je laisserai tout tomber et je partirai à leur poursuite. Je te le promets. Tu m'entends ?";
			link.l1.go = "PZ_Longway_29";
		break;
		
		case "PZ_Longway_29":
			dialog.text = "Oui, Monseigneur le Capitaine. Merci.";
			link.l1 = "Gardez la tête haute, Longway. Nous devons nous dépêcher de retourner au navire - la mort du Commandant sera une grande nouvelle très bientôt.";
			link.l1.go = "PZ_Longway_30";
		break;
		
		case "PZ_Longway_30":
			DialogExit();
			
			Return_LongwayOfficer();
			LAi_RemoveCheckMinHP(npchar);
			AddQuestRecord("PZ", "17");
			sld = &Locations[FindLocation("Mayak4")];
			sld.locators_radius.goto.goto31 = 0.5;
			
			chrDisableReloadToLocation = false;
			QuestOpenSeaExit();
			
			pchar.questTemp.PZ_Etap4_Start = true;
		break;
		
		// Этап 4, Обманчивая Звезда
		case "PZ_PoterpKrushenie_1":
			dialog.text = "Monsieur ! Un moment ! Êtes-vous capitaine ?";
			link.l1 = "Peut-être. Comment l'as-tu deviné ? Et que veux-tu ?";
			link.l1.go = "PZ_PoterpKrushenie_2";
		break;
		
		case "PZ_PoterpKrushenie_2":
			dialog.text = "Eh bien, il n'y a rien d'autre que des montagnes et une jungle épaisse par ici - pas de routes vers la ville. Et pourtant, te voilà. Tu n'es pas juste en train de faire du tourisme, n'est-ce pas ?";
			link.l1 = "Bonne observation. Mais tu ne m'as toujours pas dit ce que tu veux.";
			link.l1.go = "PZ_PoterpKrushenie_3";
		break;
		
		case "PZ_PoterpKrushenie_3":
			dialog.text = "Ah, bien ! Capitaine, notre navire s'est échoué juste au large de cette crique. Nous sommes les seuls à avoir survécu...";
			link.l1 = "Je suis désolé. Vous voulez que je vous emmène quelque part, n'est-ce pas ?";
			link.l1.go = "PZ_PoterpKrushenie_4";
		break;
		
		case "PZ_PoterpKrushenie_4":
			dialog.text = "Oui... Nous ne causerons aucun problème, je le jure. Dépose-nous simplement à Belize, et nous nous débrouillerons à partir de là.";
			link.l1 = "Ce n'est pas loin, n'est-ce pas ? Dans ce cas, bienvenue à bord.";
			link.l1.go = "PZ_PoterpKrushenie_5";
			link.l2 = "Je suis désolé, mais je vais dans l'autre sens.";
			link.l2.go = "PZ_PoterpKrushenie_7";
		break;
		
		case "PZ_PoterpKrushenie_5":
			dialog.text = "Merci, Capitaine ! Qui sait combien de temps nous serions restés coincés sans vous.";
			link.l1 = "En effet. Ne perdons pas de temps !";
			link.l1.go = "PZ_PoterpKrushenie_6";
		break;
		
		case "PZ_PoterpKrushenie_6":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
			DeleteAttribute(&locations[FindLocation("Shore9")], "DisableEncounters");
			
			for (i=1; i<=6; i++)
			{
				sld = CharacterFromID("PZ_PoterpKrushenie_"+i);
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "sea", "", "", "", "", -1);
				sld.location = "None";
			}
			
			PChar.quest.PZ_Beliz_PoterpKrushenie.win_condition.l1 = "location";
			PChar.quest.PZ_Beliz_PoterpKrushenie.win_condition.l1.location = "Beliz_town";
			PChar.quest.PZ_Beliz_PoterpKrushenie.win_condition = "PZ_Beliz_PoterpKrushenie";
			AddMapQuestMarkCity("Beliz", false);
			
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			AddCharacterExpToSkill(pchar, "Leadership", 50);
			
			SetTimerCondition("PZ_BelizFail", 0, 0, 30, false);
		break;
		
		case "PZ_PoterpKrushenie_7":
			dialog.text = "Mais Belize est si proche ! Ça ne prendrait sûrement pas longtemps, n'est-ce pas ?";
			link.l1 = "Je suis pressé. Je ne peux pas me permettre de faire des détours.";
			link.l1.go = "PZ_PoterpKrushenie_8";
		break;
		
		case "PZ_PoterpKrushenie_8":
			dialog.text = "Pas même un petit détour ? Juste jusqu'à Belize ? S'il vous plaît, Capitaine, ne nous laissez pas en rade !";
			link.l1 = "D'accord, j'espère ne pas regretter cela. Tous à bord !";
			link.l1.go = "PZ_PoterpKrushenie_6";
			link.l2 = "C'est la vie. Passez une agréable journée, mes amis.";
			link.l2.go = "PZ_PoterpKrushenie_9";
		break;
		
		case "PZ_PoterpKrushenie_9":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
			DeleteAttribute(&locations[FindLocation("Shore9")], "DisableEncounters");
			
			for (i=1; i<=6; i++)
			{
				sld = CharacterFromID("PZ_PoterpKrushenie_"+i);
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "reload1", "", "", "", "", 10);
				sld.location = "None";
			}
			
			PChar.quest.PZ_Beliz_PoterpKrushenie.win_condition.l1 = "location";
			PChar.quest.PZ_Beliz_PoterpKrushenie.win_condition.l1.location = "Beliz_town";
			PChar.quest.PZ_Beliz_PoterpKrushenie.win_condition = "PZ_Beliz_QuestCitizenDialog";
			
			AddMapQuestMarkCity("Beliz", false);
			
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			AddCharacterExpToSkill(pchar, "FencingL", 20);
			AddCharacterExpToSkill(pchar, "FencingS", 20);
			AddCharacterExpToSkill(pchar, "FencingH", 20);
			AddCharacterExpToSkill(pchar, "Pistol", 20);
			
			pchar.questTemp.PZ.Shipwreckers.Decline = true;
			
			SetTimerCondition("PZ_BelizFail", 0, 0, 30, false);
		break;
		
		case "PZ_PoterpKrushenie_11":
			dialog.text = "Merci encore, Capitaine ! Nous ne sommes que de simples marins, donc nous n'avons pas grand-chose à vous offrir.";
			link.l1 = "Eh bien, au moins nous n'avons pas eu à faire un grand détour.";
			link.l1.go = "PZ_PoterpKrushenie_12";
		break;
		
		case "PZ_PoterpKrushenie_12":
			dialog.text = "Nous lèverons un verre à votre santé et allumerons un cierge pour vous à l'église.";
			link.l1 = "C'est mieux que rien. À la vôtre, les gars !";
			link.l1.go = "PZ_PoterpKrushenie_13";
		break;
		
		case "PZ_PoterpKrushenie_13":
			DialogExit();
			for (i=1; i<=6; i++)
			{
				sld = CharacterFromID("PZ_PoterpKrushenie_"+i);
				LAi_SetCitizenType(sld);
				LAi_CharacterDisableDialog(sld);
				sld.lifeday = 0;
				sld.location = "None";
			}
			
			sld = GetCharacter(NPC_GenerateCharacter("PZ_BelizZhitelNovosti", "citiz_4", "man", "man", 1, ENGLAND, 0, false, "quest"));
			ChangeCharacterAddressGroup(sld, pchar.location, "goto",  "goto5");
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_BelizZhitelNovosti_1";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "PZ_BelizZhitelNovosti_1":
			dialog.text = "As-tu entendu ? Ils l'ont enfin attrapé ! Nos eaux sont enfin sûres !";
			link.l1 = "C'est... une bonne nouvelle ? Mais qui ont-ils attrapé ?";
			link.l1.go = "PZ_BelizZhitelNovosti_2";
			DeleteQuestCondition("PZ_BelizFail");
		break;
		
		case "PZ_BelizZhitelNovosti_2":
			dialog.text = "Matthew Lutter, le Sac à Vent en personne !";
			link.l1 = "Je ne suis pas familier - qu'a-t-il fait ?";
			link.l1.go = "PZ_BelizZhitelNovosti_3";
		break;
		
		case "PZ_BelizZhitelNovosti_3":
			dialog.text = "Tu ne sais pas ?! Eh bien, tu n'es clairement pas Anglais, je le vois. C'est un pirate qui nous pille, nous et les Espagnols, depuis des années sur son navire, la Mouette.";
			link.l1 = "Piller à la fois les Anglais et les Espagnols ? C'est inhabituel.";
			link.l1.go = "PZ_BelizZhitelNovosti_4";
		break;
		
		case "PZ_BelizZhitelNovosti_4":
			dialog.text = "En effet. La garde côtière n'a jamais pu l'attraper, mais finalement, il a mordu plus qu'il ne pouvait mâcher - perdu face à un étrange navire marchand, si vous pouvez le croire.";
			link.l1 = "C'est amusant. Qu'est-ce qui était si étrange chez le marchand ?";
			link.l1.go = "PZ_BelizZhitelNovosti_5";
		break;
		
		case "PZ_BelizZhitelNovosti_5":
			dialog.text = "Eh bien, c'était juste un énorme galion maladroit sans escorte ! Mais grâce à son capitaine fou, Lutter chantera sa dernière chanson aujourd'hui - il est sur le point d'être pendu. Vous devriez venir voir !";
			link.l1 = "Je pourrais, mais pour l'instant, j'ai d'autres affaires à régler.";
			link.l1.go = "PZ_BelizZhitelNovosti_6";
		break;
		
		case "PZ_BelizZhitelNovosti_6":
			DialogExit();
			
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			
			sld = CharacterFromID("Longway");
			if (!CharacterIsHere("Longway"))
			{
				ChangeCharacterAddressGroup(sld, PChar.location, "goto", LAi_FindNearestFreeLocator2Pchar("goto"));
			}
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_Longway_31";
		break;
		
		case "PZ_Longway_31":
			dialog.text = "Monseigneur le Capitaine !";
			link.l1 = "Un marchand espagnol qui défait un pirate audacieux... Tu penses comme Longway pense, n'est-ce pas ?";
			link.l1.go = "PZ_Longway_32";
		break;
		
		case "PZ_Longway_32":
			dialog.text = " L'Étoile du Matin... ";
			link.l1 = "Très probablement - il n'y a pas d'autre capitaine marchand comme lui dans tout l'archipel.";
			link.l1.go = "PZ_Longway_33";
		break;
		
		case "PZ_Longway_33":
			dialog.text = "Nous devons le trouver immédiatement !";
			link.l1 = "D'accord. Mais je ne vois pas de lourd galion au port. Essayons de parler au Ventard avant qu'il ne soit pendu. Voyons s'il a mérité ce surnom.";
			link.l1.go = "PZ_Longway_34";
		break;
		
		case "PZ_Longway_34":
			DialogExit();
			Return_LongwayOfficer();
			if (!CheckAttribute(pchar, "questTemp.PZ.Shipwreckers.Decline")) AddQuestRecord("PZ", "18");
			else AddQuestRecord("PZ", "18_1");
			pchar.questTemp.PZ_Beliz_Komendant = true;
			AddLandQuestMarkToPhantom("beliz_prison", "belizJailOff");
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
		break;
		
		case "PZ_Beliz_Komendant_8":
			dialog.text = "Est-il encore en vie ? Pouvons-nous lui parler ?";
			link.l1 = "";
			link.l1.go = "PZ_Beliz_Komendant_9";
			CharacterTurnByChr(npchar, CharacterFromID("BelizJailOff"));
		break;
		
		case "PZ_Beliz_Komendant_9":
			StartInstantDialogNoType("BelizJailOff", "PZ_Beliz_Komendant_10", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_Beliz_Komendant_10":
			dialog.text = "Quoi ? Oh, oui. Il est vivant - l'exécution n'a pas encore eu lieu. Vous pouvez aller lui parler - il est plus bavard que jamais. Mais dernièrement, il raconte des bêtises, parlant surtout à lui-même. Le Fanfaron est devenu fou... J'ai hâte de le pendre, avant que nous ne devenions tous fous à cause de son bavardage interminable.";
			link.l1 = "";
			link.l1.go = "PZ_Beliz_Komendant_11";
		break;
		
		case "PZ_Beliz_Komendant_11":
			StartInstantDialog("Longway", "PZ_Beliz_Komendant_12", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_Beliz_Komendant_12":
			dialog.text = "Je vous remercie.";
			link.l1 = "";
			link.l1.go = "PZ_Beliz_Komendant_13";
			CharacterTurnByChr(npchar, CharacterFromID("BelizJailOff"));
		break;
		
		case "PZ_Beliz_Komendant_13":
			DialogExit();
			pchar.questTemp.jailCanMove = true;
			
			Return_LongwayOfficer();
			
			sld = CharacterFromID("BelizJailOff");
			LAi_SetHuberType(sld);
			sld.Dialog.Filename = "Common_Prison.c";
			sld.Dialog.CurrentNode = "First_officer";
			
			sld = GetCharacter(NPC_GenerateCharacter("PZ_MatthewLutter", "mercen_15", "man", "man", 1, ENGLAND, -1, false, "quest"));
			sld.name = "Matthew";
			sld.lastname = "Lutter";
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_MatthewLutter1";
			ChangeCharacterAddressGroup(sld, "Beliz_prison", "goto", "goto9");
			LAi_SetStayType(sld);
			AddLandQuestMark(sld, "questmarkmain");
		break;
		
		case "PZ_MatthewLutter1":
			dialog.text = "Il a volé mon trésor !";
			link.l1 = "Matthew Lutter ?";
			link.l1.go = "PZ_MatthewLutter2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_MatthewLutter2":
			dialog.text = "Mon trésor lui est maintenant lié, tu sais, LUI ! Il n’y a rien que nous puissions faire ! Que veux-tu ?! Veux-tu nous prendre encore quelque chose ? Il ne reste plus rien ! Elle va mourir ! Ou pire !";
			link.l1 = "Qui va mourir ? Quel trésor ? Peu importe, c'est ta faute - c'est toi qui as attaqué ce galion, pas l'inverse.";
			link.l1.go = "PZ_MatthewLutter3";
		break;
		
		case "PZ_MatthewLutter3":
			dialog.text = "Non ! C'était l'inverse ! Maudit soit cet hidalgo ! C'est à cause de lui que nous sommes dans ce pétrin ! Il est venu droit sur nous et a tiré à bout portant ! Puis il l'a prise de nous !";
			link.l1 = "Vraiment ? Ce n'est pas surprenant. Que peux-tu nous dire de plus sur lui ? Et... qu'a-t-il pris ? Qui est 'elle' ?";
			link.l1.go = "PZ_MatthewLutter5";
		break;
		
		case "PZ_MatthewLutter5":
			dialog.text = "Ah-ah-ah!!! A-A-A-A!!!";
			link.l1 = "Je vois, je perds mon temps...";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_BelizPrisonSoldierDialog");
		break;
		
		case "PZ_BelizPrisonQuestSoldier1":
			dialog.text = "Capitaine, avec votre permission... Lutter ! Dehors ! Fin de la ligne, camarade.";
			link.l1 = "";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_BelizPrisonLongway_UvodyatNaKazn");
		break;
		
		case "PZ_Longway_35":
			dialog.text = "Capitaine, nous devons en savoir plus sur Sotta et Lutter. Allons poser des questions.";
			link.l1 = "Bonne idée, Longway. Nous n'avons pas appris grand-chose de cet homme criard de toute façon.";
			link.l1.go = "PZ_Longway_36";
		break;
		
		case "PZ_Longway_36":
			dialog.text = "Mais il vaut mieux commencer par Sotta.";
			link.l1 = "D'accord, c'est lui que nous cherchons. Allons-y.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_BelizPrisonLongwayBack");
		break;
		
		case "PZ_Longway_37":
			dialog.text = "Ils ne savent rien !";
			link.l1 = "Évidemment. Mais nous en savons assez pour commencer à réfléchir par nous-mêmes. D'après ce que j'ai entendu, Sotta essaiera probablement de vendre ces biens stratégiques qu'il a reçus en récompense, et bientôt.";
			link.l1.go = "PZ_Longway_38";
		break;
		
		case "PZ_Longway_38":
			dialog.text = "Exactement !";
			link.l1 = "Nous devrions l'intercepter sur son chemin à Port Royal ou Capsterville. La seule question est de savoir où il se dirige et où nous devrions l'engager. Ou peut-être le capturerons-nous en pleine mer.";
			link.l1.go = "PZ_Longway_39";
		break;
		
		case "PZ_Longway_39":
			dialog.text = "Non ! Longway voulait dire... Fermentelos est un capitaine chevronné. Un combat en haute mer pourrait tourner en notre défaveur. Nous aurions de meilleures chances en l'embusquant au port.";
			link.l1 = "Tu as raison, je suppose. Peu importe ce qui s'est réellement passé entre Matt et lui, Sotta est dangereux et ne doit pas être sous-estimé.";
			link.l1.go = "PZ_Longway_40";
		break;
		
		case "PZ_Longway_40":
			dialog.text = "Nous ne pouvons pas attendre non plus !";
			link.l1 = "Encore une fois, tu as raison, Longway. Alors levons l'ancre immédiatement, et ensuite nous planifierons notre prochain mouvement.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_LongwayBelizDialogBack");
			DelMapQuestMarkCity("Beliz");
		break;
		
		case "PZ_Longway_41":
			dialog.text = "Monseigneur le Capitaine, l'Étoile du Matin est au port !";
			link.l1 = "Oui, j'ai déjà remarqué.";
			link.l1.go = "PZ_Longway_42";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_Longway_42":
			dialog.text = "Quel est votre plan ?";
			link.l1 = "Je n'ai pas encore décidé. Essayer de les aborder sous les canons du fort serait un suicide. Et même si nous capturons leur lourde galion, nous ne pourrons pas nous échapper avec. As-tu des idées, Longway ?";
			link.l1.go = "PZ_Longway_43";
		break;
		
		case "PZ_Longway_43":
			dialog.text = "Oui. Nous pourrions mouiller dans une crique sûre et approcher le galion à la rame sous le couvert de la nuit.";
			if (CheckAttribute(pchar, "questTemp.PZ_OhotaNaZvezdu_Kapstervil"))
			{
				link.l1 = "Qu'en est-il de Half Moon Bay, Longway ?";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_OhotaNaZvezdu_Yamaika"))
			{
				link.l1 = "Je pense que la crique de Portland conviendrait bien - assez proche et relativement sûre. Qu'en penses-tu ?";
			}
			link.l1.go = "PZ_Longway_44";
		break;
		
		case "PZ_Longway_44":
			dialog.text = "Bon choix.";
			link.l1 = "Génial, c'est réglé. Avons-nous manqué quelque chose ?";
			link.l1.go = "PZ_Longway_45";
		break;
		
		case "PZ_Longway_45":
			dialog.text = "Je ne pense pas, Monseigneur le Capitaine. Nous devons juste être bien préparés.";
			link.l1 = "Absolument.";
			link.l1.go = "PZ_Longway_46";
		break;
		
		case "PZ_Longway_46":
			DialogExit();
			
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar, "GenQuest.CabinLock");
			DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
			bQuestDisableMapEnter = false;
			AddQuestRecord("PZ", "21");
			if (CheckAttribute(pchar, "questTemp.PZ_OhotaNaZvezdu_Kapstervil"))
			{
				AddQuestUserData("PZ", "sText", "Half Moon Bay");
				Island_SetReloadEnableGlobal("Nevis", true);
				
				PChar.quest.PZ_GotovimShlupki_Buhta.win_condition.l1 = "location";
				PChar.quest.PZ_GotovimShlupki_Buhta.win_condition.l1.location = "Shore43";
				PChar.quest.PZ_GotovimShlupki_Buhta.win_condition = "PZ_GotovimShlupki_Buhta";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_OhotaNaZvezdu_Yamaika"))
			{
				AddQuestUserData("PZ", "sText", "Portland Cove");
				Island_SetReloadEnableGlobal("Jamaica", true);
				
				PChar.quest.PZ_GotovimShlupki_Buhta.win_condition.l1 = "location";
				PChar.quest.PZ_GotovimShlupki_Buhta.win_condition.l1.location = "Shore36";
				PChar.quest.PZ_GotovimShlupki_Buhta.win_condition = "PZ_GotovimShlupki_Buhta";
			}
			PChar.quest.PZ_ZvezdaUhodimNaGlobalkru_Proval.win_condition.l1 = "MapEnter";
			PChar.quest.PZ_ZvezdaUhodimNaGlobalkru_Proval.win_condition = "PZ_ZvezdaUhodimNaGlobalkru_Proval";
			
			sld = CharacterFromID("Longway");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
			LAi_SetOfficerType(sld);
			sld.Dialog.Filename = "Quest\HollandGambit\Longway.c";
			sld.Dialog.CurrentNode = "Longway_officer";
		break;
		
		case "PZ_Zvezda_DialogWithCapitan":
			dialog.text = "Qui diable es-tu, que se passe-t-il ? Monsieur Holmes !";
			link.l1 = "Monsieur Holmes ne travaille plus ici. Et nous avons scellé toutes les écoutilles hermétiquement. Alors, nous ne serons pas dérangés pendant un certain temps, Monseigneur Fermentelos.";
			link.l1.go = "PZ_Zvezda_DialogWithCapitan_2";
			SetCameraDialogMode(npchar);
		break;
		
		case "PZ_Zvezda_DialogWithCapitan_2":
			dialog.text = "Quoi ? Fermentelos ? Mon nom est Edgardo Sotta !";
			link.l1 = "Uh-huh, j'ai déjà entendu celle-là. Nous savons que ce n'est pas ton vrai nom, Oliveiro.";
			link.l1.go = "PZ_Zvezda_DialogWithCapitan_3";
		break;
		
		case "PZ_Zvezda_DialogWithCapitan_3":
			dialog.text = "Fermentelos est mort !";
			link.l1 = "À la réflexion, tu sembles vraiment trop jeune. Il est évident que tu ne pouvais pas être le capitaine de l'Étoile du Matin il y a dix ans. Alors, qu'est-il arrivé à Oliveiro ?";
			link.l1.go = "PZ_Zvezda_DialogWithCapitan_4";
		break;
		
		case "PZ_Zvezda_DialogWithCapitan_4":
			dialog.text = "Nous nous sommes débarrassés de lui. C'était juste un autre problème que nous devions régler - tout comme celui qui se tient à côté de toi.";
			link.l1 = "Eh bien, puisque vous n'êtes pas Fermentelos, peut-être pouvez-vous encore répondre à nos questions. Nous cherchons quelqu'un qu'il a pris à mon ami.";
			link.l1.go = "PZ_Zvezda_DialogWithCapitan_5";
		break;
		
		case "PZ_Zvezda_DialogWithCapitan_5":
			dialog.text = "Je ne vais rien te dire ! Il ne me pardonnera jamais pour ça.";
			link.l1 = "En ce moment, tu ferais mieux de te demander si nous te pardonnerons...";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_SottaFight");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "PZ_AnabelleLutter1":
			dialog.text = "Il est enfin mort...";
			link.l1 = "That's right. And who are you, madam? Did he hold you against your will? I sympathize; you must have been through a terrible ordeal...";
			link.l1.go = "PZ_AnabelleLutter2";
			SetCameraDialogMode(npchar);
		break;
		
		case "PZ_AnabelleLutter2":
			dialog.text = "Je suis Annabel Lutter. Et Dieu merci, je n'ai pas eu à endurer beaucoup, mais j'apprécie votre sollicitude, monsieur... ?";
			link.l1 = "Capitaine Charles de Maure. Lutter, tu dis...";
			link.l1.go = "PZ_AnabelleLutter3";
		break;
		
		case "PZ_AnabelleLutter3":
			dialog.text = "Ah, tu as sûrement entendu parler de Matt ? Pauvre imbécile... J'étais sa... compagne.";
			link.l1 = "Je suis désolé pour votre perte, Madame Lutter. Vous êtes maintenant veuve. Quel était votre nom de jeune fille, si ce n'est pas un secret ?";
			link.l1.go = "PZ_AnabelleLutter4";
		break;
		
		case "PZ_AnabelleLutter4":
			dialog.text = "Je n'en ai pas eu. Regardez-moi de plus près. Ma pauvre mère était une esclave à la peau sombre pour les pirates. Personne ne sait qui était mon père, alors ils ne se sont pas donné la peine de me donner un vrai nom.";
			link.l1 = "Pourquoi personne ne t'a touchée alors ? Ne te méprends pas - je suis content que cela ne soit pas arrivé. Mais quand même, c'est... inhabituel.";
			link.l1.go = "PZ_AnabelleLutter5";
		break;
		
		case "PZ_AnabelleLutter5":
			dialog.text = "You're right. But let's call things by their proper names. I'm not a pampered noblewoman; I'm the daughter of a slave. I won't faint from a heavy conversation.";
			link.l1 = "Hum, je ne suis pas non plus du genre à dorloter. Mais vas-y, s'il te plaît. Pourquoi l'équipage n'a-t-il pas touché à la fille de l'esclave ? Tu ne connais pas ton père, et il ne semblait pas s'en soucier.";
			link.l1.go = "PZ_AnabelleLutter6";
		break;
		
		case "PZ_AnabelleLutter6":
			dialog.text = "Je suppose que non. Puisque tu sais pour Matt, sais-tu qu'il a travaillé pour Levasseur pendant un certain temps ?";
			link.l1 = "Oui, j'en ai entendu parler pendant que je cherchais l'Étoile du Matin. Mais quel rapport cela a-t-il ? Dis-moi tout, s'il te plaît.";
			link.l1.go = "PZ_AnabelleLutter7";
		break;
		
		case "PZ_AnabelleLutter7":
			dialog.text = "Tu ne comprends toujours pas, n'est-ce pas ? Apparemment, tu n'as pas entendu parler des... préférences de Levasseur ?";
			link.l1 = "Je ne l'ai pas fait, mais encore une fois, quel rapport avec...?";
			link.l1.go = "PZ_AnabelleLutter8";
		break;
		
		case "PZ_AnabelleLutter8":
			dialog.text = "Oh, je suppose que je vais devoir tout te raconter. Assieds-toi si tu es trop impressionnable, monsieur. Le fait est qu'il couche avec beaucoup de femmes, et...";
			if (pchar.questTemp.FMQT == "end")
			{
				link.l1 = "Sa femme n'est pas loin de lui, et elle couche avec presque n'importe qui.";
				link.l1.go = "PZ_AnabelleLutterKnow1";
			}
			else
			{
				link.l1 = "Oh non.";
				link.l1.go = "PZ_AnabelleLutterDontKnow1";
			}
		break;
		
		case "PZ_AnabelleLutterKnow1":
			dialog.text = " Eh bien, tu sais ce qu'on dit... tel mari, telle femme. Mais non, je suis sûr qu'il est allé bien plus loin que ça.";
			link.l1 = "Et jusqu'où ?";
			link.l1.go = "PZ_AnabelleLutter9";
		break;
		
		case "PZ_AnabelleLutterDontKnow1":
			dialog.text = "Votre sarcasme n'a pas sa place ici, monsieur. Vous n'avez aucune idée de quoi nous parlons.";
			link.l1 = "D'accord, d'accord, je suis désolé. Continuez, je vous en prie.";
			link.l1.go = "PZ_AnabelleLutter9";
		break;
		
		case "PZ_AnabelleLutter9":
			dialog.text = "Ce n'est pas seulement tromper son épouse. Il prend des femmes contre leur gré. Et ce n'est pas juste un abus occasionnel. Il enlève des jeunes filles et les garde dans l'une des caves à vin qu'il possède.";
			link.l1 = "Alors il obtient des filles esclaves régulièrement ? Et tu étais censée être l'une d'elles ?";
			link.l1.go = "PZ_AnabelleLutter10";
		break;
		
		case "PZ_AnabelleLutter10":
			dialog.text = "Tu as raison pour le dernier point. Mais, hélas, pas pour le premier. Il n'a pas besoin d'esclaves. Levasseur est fou - à sa manière, pas comme mon Matt. François veut posséder totalement une femme, corps et âme. Et il ne s'agissait pas d'amour, bien sûr. Il avait besoin de femmes libres pour briser leur volonté. Il prenait plaisir à observer comment leur apparence, leur comportement et leur façon de parler changeaient avec le temps...";
			link.l1 = "Dégoûtant...";
			link.l1.go = "PZ_AnabelleLutter11";
		break;
		
		case "PZ_AnabelleLutter11":
			dialog.text = "Tu te sens déjà un peu mal, non ? Maintenant, imagine ce que c'était pour ces femmes. J'ai entendu parler de tout cela, et pas seulement de Matt. Levasseur avait une fois une noble portugaise...";
			link.l1 = "Tu as détourné le regard et tu es resté silencieux. Dis-nous tout. J'ai vu toutes sortes de choses dans l'Ancien Monde et pendant mon temps dans l'Archipel aussi. Plus rien ne me surprend maintenant.";
			link.l1.go = "PZ_AnabelleLutterWant1";
			link.l2 = "Arrête, je ne veux pas savoir ce qui lui est arrivé. J'espère que ces femmes n'ont pas trop souffert entre ses mains.";
			link.l2.go = "PZ_AnabelleLutter12";
		break;
		
		case "PZ_AnabelleLutterWant1":
			dialog.text = "Mais tu n'as jamais entendu parler de quelque chose comme ça. Et j'espère que tu ne le verras jamais. Elle lui a été amenée encore fière et intacte, même si, comme Matt me l'a dit, les hommes de Levasseur l'ont violée tout le chemin jusqu'à Tortuga après avoir pris le contrôle de la plantation de son mari près de Campeche - il est mort d'une hémorragie après que ces monstres lui ont tiré dans les deux genoux...";
			link.l1 = "Une femme forte... Mais tu as dit que Levasseur ne touchait généralement pas les femmes qu'il voulait pour lui-même.";
			link.l1.go = "PZ_AnabelleLutterWant2";
		break;
		
		case "PZ_AnabelleLutterWant2":
			dialog.text = "Celles qu'il a spécifiquement demandées ont été laissées tranquilles. Mais Señora Leontina était un cadeau. Un cadeau inattendu et agréable pour eux tous. Alors ils se sont laissés aller...";
			link.l1 = "Je vois...";
			link.l1.go = "PZ_AnabelleLutterWant3";
		break;
		
		case "PZ_AnabelleLutterWant3":
			dialog.text = "Je suppose... Matt était devenu l'un des favoris de François. Il a été invité à l'une des soirées secrètes de Levasseur... Pendant le festin, un des pirates s'est plaint qu'il n'y avait pas assez de femmes. Levasseur a ri et puis...";
			link.l1 = "Et ensuite ? Que s'est-il passé ?";
			link.l1.go = "PZ_AnabelleLutterWant4";
		break;
		
		case "PZ_AnabelleLutterWant4":
			dialog.text = "...puis elle a été amenée. En laisse ! Battue, le dos écorché, les yeux bandés et bâillonnée. Quand ils ont enlevé le bâillon, tout ce qu'elle a dit était...";
			link.l1 = "Quelque chose d'horrible, j'imagine. L'a-t-elle maudit de toutes ses forces ?";
			link.l1.go = "PZ_AnabelleLutterWant5";
		break;
		
		case "PZ_AnabelleLutterWant5":
			dialog.text = "Si seulement... Dona Leontina murmura simplement : 'Que souhaite mon maître ?'";
			link.l1 = "Je crois que je vais être malade. Est-ce que Matt t'a dit ce qui lui est arrivé ensuite ?";
			link.l1.go = "PZ_AnabelleLutterWant6";
		break;
		
		case "PZ_AnabelleLutterWant6":
			dialog.text = "Assassinée, bien sûr. Mais pas par les mains de Levasseur. Il l'a jetée comme un chien errant. Un de ses capitaines l'a abattue. Avant de mourir, elle n'a prononcé qu'un seul mot...";
			link.l1 = "Une malédiction ? Une prière ?";
			link.l1.go = "PZ_AnabelleLutterWant7";
		break;
		
		case "PZ_AnabelleLutterWant7":
			dialog.text = "Non. 'Je vous remercie...'";
			link.l1 = "Être reconnaissant pour la mort après tant de tourments... Ce qu'elle a dû endurer... et d'autres comme elle dans le repaire de ce monstre...";
			link.l1.go = "PZ_AnabelleLutter12";
		break;
		
		case "PZ_AnabelleLutter12":
			dialog.text = "Levasseur méprisait particulièrement les esclaves et les femmes à la peau sombre - il disait qu'il n'y avait rien à briser en elles. Elles ne duraient pas longtemps avec lui, et les Indiens non plus - à l'exception de quelques-uns particulièrement têtus. Mais la sauvagerie et la rébellion n'étaient pas la solution non plus - il tuait ceux qui essayaient de lui plaire trop tôt et ceux qui restaient défiants trop longtemps.";
			link.l1 = "C'est horrible... Dis-moi, Levasseur avait-il déjà des femmes asiatiques ?";
			link.l1.go = "PZ_AnabelleLutter13";
		break;
		
		case "PZ_AnabelleLutter13":
			dialog.text = "Non, du moins pas à ma connaissance. Quant à moi... Je t'ai déjà dit qu'il n'aimait pas les femmes à la peau foncée. Alors quand Matt travaillait pour François, il se promenait avec moi ouvertement dans les rues de Tortuga. Il m'a même emmenée à la résidence une fois.";
			link.l1 = "Mais Levasseur voulait quand même te faire l'un de ses esclaves...";
			link.l1.go = "PZ_AnabelleLutter14";
		break;
		
		case "PZ_AnabelleLutter14":
			dialog.text = "Exactement... Je ne sais pas pourquoi il m'aimait tant... Quand Matt l'a su, il a quitté l'île dès qu'on lui a dit. Il n'est jamais revenu à Tortuga. Il était peut-être un peu fou, mais il m'aimait. Il m'appelait son trésor...";
			link.l1 = "Alors c'est ce qu'il voulait dire quand il a dit que Sotta lui a pris son trésor !";
			link.l1.go = "PZ_AnabelleLutter15";
		break;
		
		case "PZ_AnabelleLutter15":
			dialog.text = "Eh bien, il a dit ça ? Oh, Matt... Mais il semble que nous n'étions jamais destinés à vieillir ensemble. Si Levasseur avait des vues sur une femme, il ferait n'importe quoi pour l'avoir, peu importe son origine ou le coût. Sotta était l'un de ses capitaines, et il a fait ce qu'on lui a ordonné.";
			link.l1 = "Je vois. Et que comptes-tu faire maintenant, Annabel ?";
			link.l1.go = "PZ_AnabelleLutter16";
		break;
		
		case "PZ_AnabelleLutter16":
			dialog.text = "Fuir. Quelque part où les hommes de Levasseur ne peuvent pas m'atteindre. Changer de nom. Me déguiser...";
			link.l1 = "J'espère que tu réussiras. Je te souhaite tout le meilleur, Annabel.";
			link.l1.go = "PZ_AnabelleLutter17";
			if (sti(pchar.Money) >= 10000)
			{
				link.l2 = "Il te faudra de l'argent pour organiser ton passage. Prends ceci. Il y a dix mille pesos ici.";
				link.l2.go = "PZ_AnabelleLutter17_Peso";
			}
			if (PCharDublonsTotal() >= 100)
			{
				link.l3 = "Tu auras besoin de plus que juste un peu d'argent. Tout le monde n'est pas prêt à aider une fille à la peau sombre, même une métisse. Tiens, prends une centaine de doublons - trouve un navire et cache-toi.";
				link.l3.go = "PZ_AnabelleLutter17_Dublon";
			}
		break;
		
		case "PZ_AnabelleLutter17":
			dialog.text = "Toi aussi ! Au revoir, Capitaine.";
			link.l1 = "Adieu.";
			link.l1.go = "Exit";
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			AddDialogExitQuest("PZ_AnabelleGo");
		break;
		
		case "PZ_AnabelleLutter17_Peso":
			dialog.text = "Je... je ne sais pas quoi dire. Personne d'autre que Matt ne m'a jamais montré une telle gentillesse.";
			link.l1 = "Peut-être est-ce un signe. Que tu vieilliras heureux quelque part, après tout. Adieu.";
			link.l1.go = "Exit";
			AddMoneyToCharacter(pchar, -10000);
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			AddDialogExitQuest("PZ_AnabelleGo");
		break;
		
		case "PZ_AnabelleLutter17_Dublon":
			dialog.text = "Tu as raison. Merci infiniment pour cela. Je me souviendrai de toi dans mes prières pour le reste de ma vie.";
			link.l1 = "Merci. Bon vent.";
			link.l1.go = "Exit";
			RemoveDublonsFromPCharTotal(100);
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			AddDialogExitQuest("PZ_AnabelleGo");
		break;
		
		case "PZ_Longway_47":
			dialog.text = "Cet homme... Non, ce n'est plus un homme. C'est une bête. Un monstre. Torturer des femmes ainsi...";
			link.l1 = "Je sais ce que tu penses, Longway. Mais tu as entendu - il n'a jamais eu de femme à la peau jaune.";
			link.l1.go = "PZ_Longway_48";
			SetCameraDialogMode(npchar);
		break;
		
		case "PZ_Longway_48":
			dialog.text = "Mais il connaissait tout le groupe ! Van der Vink, Fermentelos, Sotta... Nous venons de le lire dans son journal. Et si ce 'elle' en particulier était... elle ?";
			link.l1 = "Qui sait... Une femme en quête de vengeance contre Fermentelos - c'est facile de comprendre pourquoi tu penserais cela. Mais cela pourrait être n'importe quelle femme dont la vie a été brisée par Oliveiro. Cela n'a pas besoin d'être ta sœur. Cela n'a même pas besoin d'être une femme à la peau jaune.";
			link.l1.go = "PZ_Longway_49";
		break;
		
		case "PZ_Longway_49":
			dialog.text = "Refuses-tu... d'essayer cela, Monseigneur le Capitaine ? À la toute dernière minute... ?";
			link.l1 = "Non, Longway. Mais comment l'imagines-tu ? Il est peu probable que Levasseur réponde à nos questions. Et flairer autour de Tortuga comme ça est trop dangereux.";
			link.l1.go = "PZ_Longway_50";
		break;
		
		case "PZ_Longway_50":
			dialog.text = "Alors, que suggérez-vous ?";
			link.l1 = "Attendons. Nous savons que Levasseur n'aime pas les femmes comme ta sœur. Donc, nous pouvons conserver nos ressources pour l'instant. Patience et force. François est un dur à cuire, surtout à cause de sa 'tortue.' Mais avec l'aide de Svenson, nous pouvons lui parler à nos conditions. Je t'ai promis que je t'aiderais à retrouver ta sœur et j'ai l'intention de tenir parole. Tu me crois, Longway ?";
			link.l1.go = "PZ_Longway_51";
		break;
		
		case "PZ_Longway_51":
			dialog.text = "Hmm... Oui oui, Monseigneur le Capitaine. Mais Longway a encore une demande pour vous.";
			link.l1 = "Qu'est-ce qui se passe ? Tu ne vas pas encore partir en solitaire, n'est-ce pas ? La dernière fois, ça ne s'est pas bien terminé.";
			link.l1.go = "PZ_Longway_52";
		break;
		
		case "PZ_Longway_52":
			dialog.text = "Pas du tout, Monseigneur le Capitaine. Je réalise maintenant qu'un homme comme moi ne peut malheureusement rien faire tout seul dans un monde dirigé par des hommes blancs. Longway vous demande d'accoster à Capsterville et de remettre une note à Georges Gravel, lui demandant de découvrir quoi que ce soit pendant que vous vous préparez.";
			link.l1 = "Une idée sensée, Longway. Nous ferons cela.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_TeleportToShore");
		break;
		
		case "PZ_Longway_53":
			dialog.text = "Monseigneur le Capitaine, Longway a quelque chose à demander...";
			link.l1 = "As-tu oublié d'écrire la lettre ? Tu peux simplement parler à Gravel.";
			link.l1.go = "PZ_Longway_54";
		break;
		
		case "PZ_Longway_54":
			dialog.text = "Non, la lettre est prête. Mais Longway a pensé qu'il valait mieux ne pas se promener seul en ville. Monseigneur le Capitaine... pourriez-vous remettre la lettre à Georges pour moi ? S'il vous plaît ?";
			link.l1 = "J'ai l'air d'un coursier pour toi ? Ou es-tu le capitaine ici ?";
			link.l1.go = "PZ_Longway_55";
		break;
		
		case "PZ_Longway_55":
			dialog.text = "Monseigneur le Capitaine...";
			link.l1 = "Ha ha ha, je plaisante, Longway ! Rappelle-moi où je peux trouver ton Gravel ?";
			link.l1.go = "PZ_Longway_56";
		break;
		
		case "PZ_Longway_56":
			dialog.text = "Il travaille à l'église.";
			link.l1 = "D'accord, je m'en occuperai.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_ToCapstervilleChurch");
			AddLandQuestMark(characterFromId("Charles_Priest"), "questmarkmain");
		break;
		
		// Этап 5
		case "PZ_Mary_Sharptown1":
			dialog.text = "Charles, mon cher Charles, quelque chose ne va pas ? Tu as l'air inquiet et... fatigué, ouais, hein ?";
			link.l1 = "Oh, non, non, Mary, je vais bien. C'est juste... cette quête de Tortuga qui est la mienne. Elle semble être dans une impasse... encore une fois. Et ce testament de Sharp m'a vraiment épuisé, pour l'amour du ciel. Mais peu importe.";
			link.l1.go = "PZ_Mary_Sharptown2";
		break;
		
		case "PZ_Mary_Sharptown2":
			dialog.text = "Quoi ? Quelle quête ? Et quel rapport avec Sharp ? Je ne comprends rien !";
			link.l1 = "Trop de questions, Mary. Ce n'est pas l'endroit pour ce genre de conversations. En discuterons-nous dans la chambre de la taverne ? Juste comme tu aimes, à l'abri des regards et hors de l'esprit. Je te raconterai ce que j'ai fait l'année dernière.";
			link.l1.go = "PZ_Mary_Sharptown3";
		break;
		
		case "PZ_Mary_Sharptown3":
			dialog.text = "D'accord ! Mais sois prévenu : si tu caches quelque chose...";
			link.l1 = "Absolument pas ! Allons-y, nous avons du temps à tuer de toute façon...";
			link.l1.go = "PZ_HelenaMary_Exit";
		break;
		
		case "PZ_Helena_Sharptown1":
			dialog.text = "Comme c'est étrange, n'est-ce pas, Charles ? Je suis censé posséder cette île, mais je n'ai pas du tout l'impression de la posséder.";
			link.l1 = "Tu crois ?";
			link.l1.go = "PZ_Helena_Sharptown2";
		break;
		
		case "PZ_Helena_Sharptown2":
			dialog.text = "Oh, ce sourire... Tu sais comment traiter une fille. Mais qu'est-ce qui ne va pas chez toi ? Ton visage est tout de travers !";
			link.l1 = "Pourquoi ? C'est mon visage habituel, très beau aussi.";
			link.l1.go = "PZ_Helena_Sharptown3";
		break;
		
		case "PZ_Helena_Sharptown3":
			dialog.text = "Charles, je l'entends dans ta voix - tu es abattu ces derniers temps.";
			link.l1 = "J'ai beaucoup à faire, surtout avec Longway. Je suis juste épuisée. Mais il est trop tard pour abandonner, d'autant plus que j'ai fait une promesse à lui et à mon père.";
			link.l1.go = "PZ_Helena_Sharptown4";
		break;
		
		case "PZ_Helena_Sharptown4":
			dialog.text = "Je ne comprends pas... Quel rapport avec Longway ? Et quelles promesses as-tu faites ?";
			link.l1 = "Si nous devons en discuter, faisons-le à la taverne, louons une chambre. Loin des autres.";
			link.l1.go = "PZ_Helena_Sharptown5";
		break;
		
		case "PZ_Helena_Sharptown5":
			dialog.text = "D'accord, allons-y. De toute façon, il n'y a rien d'autre à faire, alors au moins, nous pouvons passer du temps ensemble.";
			link.l1 = "Mène la voie, chérie !";
			link.l1.go = "PZ_HelenaMary_Exit";
		break;
		
		case "PZ_HelenaMary_Exit":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) Return_MaryOfficer();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) Return_HelenaOfficer();
			WaitDate("", 0, 0, 0, 2, 0);
			LAi_SetImmortal(npchar, true);
			ChangeCharacterAddressGroup(npchar, "Pirates_tavern_upstairs", "goto", "goto1");
			DoQuestReloadToLocation("Pirates_tavern_upstairs", "goto", "goto2", "PZ_Etap5_NaverhuTavernBandits");
		break;
		
		case "PZ_Etap5_NaverhuTavernBandits_1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Regarde comme ils dorment tendrement dans les bras l'un de l'autre ! Charmant !";
				link.l1 = " Jaloux ? ";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Debout là-dedans ! Alors, bien dormi, tourtereaux ?";
				link.l1 = "Bien, merci de demander. Et comment avez-vous dormi, messieurs ?";
			}
			link.l1.go = "PZ_Etap5_NaverhuTavernBandits_2";
			locCameraFromToPos(2.34, 1.92, 1.66, true, -1.66, -0.69, -0.02);
		break;
		
		case "PZ_Etap5_NaverhuTavernBandits_2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "C'est une question idiote, tu ne trouves pas ?";
				link.l1 = "C'est vrai. Et c'est une stupidité de ta part. Veux-tu savoir pourquoi ?";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Ils disent que vous avez la langue bien pendue, Charles de Maure.";
				link.l1 = "Et pas seulement ma langue. Tu veux découvrir ? Mais dis-moi, pourquoi n’as-tu pas attaqué pendant que nous dormions ?";
			}
			link.l1.go = "PZ_Etap5_NaverhuTavernBandits_3";
		break;
		
		case "PZ_Etap5_NaverhuTavernBandits_3":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Et pourquoi donc ?";
				link.l1 = "Il ne faut pas mettre Mary en colère le matin. Tu comprendras bientôt pourquoi.";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "C'est simple ! Il fait sombre, vous savez, alors nous ne pouvions pas dire laquelle d'entre vous était la fille.";
				link.l1 = "Salaud.";
			}
			link.l1.go = "PZ_Etap5_NaverhuTavernBandits_4";
		break;
		
		case "PZ_Etap5_NaverhuTavernBandits_4":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Contrairement à toi, je n'ai pas peur des femmes. En parlant de ça - les gars, prenez-la saine et sauve, ou l'Huguenot nous transformera en femmes à la place !";
				link.l1 = "Hu... qui ?";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Au moins, j'ai l'air d'un homme. Les gars, prenez la blonde vivante - le Huguenot l'attend.";
				link.l1 = "Hu... qui?";
			}
			link.l1.go = "PZ_Etap5_NaverhuTavernBandits_5";
		break;
		
		case "PZ_Etap5_NaverhuTavernBandits_5":
			DialogExit();
			LAi_SetFightMode(pchar, true);
			for (i=1; i<=3; i++)
			{
				sld = CharacterFromID("PZ_NaverhuTavernBandits_"+i);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				
				LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
				LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
				LAi_group_SetCheck("EnemyFight", "PZ_Etap5_NaverhuTavernBandits_Win");
			}
		break;
		
		case "PZ_MaryHelena_BitvaNaverhu_1":
			DelLandQuestMark(npchar);
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Qui était-ce, Charles ? Qui diable est ce huguenot ? Est-ce vraiment...?";
				link.l1 = "Il n'y en a qu'une seule, Mary. Et nous ferions mieux de...";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Charles... qu'était-ce cela ? Un huguenot ? Est-ce l'homme auquel je pense ?";
				link.l1 = "J'ai bien peur que oui, Helen. Nous devons...";
			}
			link.l1.go = "PZ_MaryHelena_BitvaNaverhu_2";
		break;
		
		case "PZ_MaryHelena_BitvaNaverhu_2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Entends-tu cela ? Quelqu'un arrive, ouais, hein. Probablement des amis de ces hommes morts.";
				link.l1 = "Alors nous les verrons les rejoindre. Prépare-toi...";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Entends-tu cela ? Des pas.";
				link.l1 = "En effet, je le fais. Reste derrière moi.";
			}
			link.l1.go = "PZ_MaryHelena_BitvaNaverhu_3";
		break;
		
		case "PZ_MaryHelena_BitvaNaverhu_3":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) Return_MaryOfficer();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) Return_HelenaOfficer();
			sld = CharacterFromID("Longway");
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_Longway_61";
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
			RemovePassenger(pchar, sld);
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "PZ_Longway_61":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Monseigneur le Capitaine, madame "+sStr+".";
			link.l1 = "Longway ?! Tu penses pouvoir entrer dans notre chambre comme ça ? Et si nous étions... ?";
			link.l1.go = "PZ_Longway_62";
			
			//заранее создаём заглушку для корабля
			sld = GetCharacter(NPC_GenerateCharacter("PZ_ShipStasis", "citiz_46", "man", "man", sti(pchar.rank), PIRATE, -1, false, "quest"));
			SetSPECIAL(sld, 1, 1, 1, 1, 1, 1, 1);
		break;
		
		case "PZ_Longway_62":
			dialog.text = "Hm, pardonnez-moi, Monseigneur le Capitaine. Je pensais que vous auriez fermé la porte si vous étiez occupé de cette manière. Mais Longway l'a trouvée ouverte.";
			link.l1 = "Brisé, pas ouvert. Mais dis-moi, mon ami, pourquoi es-tu si diablement calme ? Il y a des cadavres sur le sol, nous sommes armés, et tu es...";
			link.l1.go = "PZ_Longway_63";
		break;
		
		case "PZ_Longway_63":
			dialog.text = "Eh bien, j'y suis habitué.";
			link.l1 = "Et tu ne peux pas contester cela, n'est-ce pas ? Mais vraiment, tu n'as pas entendu les bruits de combat en venant ici ? Tu n'as pas vu ces brutes entrer dans la taverne et monter les escaliers juste devant toi ?";
			link.l1.go = "PZ_Longway_64";
		break;
		
		case "PZ_Longway_64":
			dialog.text = "Non, Monseigneur le Capitaine. Je n'ai vu aucun étranger dans le couloir en montant ici.";
			link.l1 = "C'est une coïncidence ridicule. Alors, que veux-tu, Longway ?";
			link.l1.go = "PZ_Longway_65";
		break;
		
		case "PZ_Longway_65":
			dialog.text = "J'ai urgemment besoin d'un navire et d'équipage, Monseigneur le Capitaine.";
			link.l1 = "Quoi ? Pourquoi ? As-tu enfin retrouvé la piste de Chang Xing ? Dans ce cas, allons-y pour elle tout de suite, ensemble.";
			link.l1.go = "PZ_Longway_66";
		break;
		
		case "PZ_Longway_66":
			dialog.text = "Hélas, pas Chang Xing. C'est... Joep van der Vink. Georges Gravel a envoyé un message et je l'ai reçu pendant que je me promenais dans le village, tandis que vous... vous reposiez avec la dame.";
			link.l1 = "Aye, j'ai eu un bon repos, je te le dis. Mais pourquoi devrions-nous nous séparer maintenant, Longway ? Nous avons une sacrée longue liste de tâches importantes à accomplir et de personnes dangereuses à tuer.";
			link.l1.go = "PZ_Longway_67";
		break;
		
		case "PZ_Longway_67":
			dialog.text = "Van der Vink n'est pas aussi dangereux que Levasseur. De plus, je l'ai déjà vaincu une fois. Et je le vaincrai encore. Cette fois, pour m'assurer qu'il est bien mort. Je ne veux pas que nous perdions tous un temps précieux à cause de lui. Tu devrais aller à Tortuga et demander aux personnes importantes tout ce dont nous avons besoin. Je capturerai van der Vink moi-même. Monseigneur le Capitaine, cela ne vaut pas la peine de gaspiller votre temps et j'étais aussi Capitaine autrefois. Je me débrouillerai.";
			link.l1 = "Hmm, tu as raison, Longway. Van der Vink peut ne pas être aussi dangereux, mais le 'Banten' est l'un des navires les plus rapides de l'archipel. Tous les navires ne suffiront pas pour l'attraper. Et qu'en est-il de l'équipage ? Comment comptes-tu rassembler des hommes si rapidement et par toi-même ?";
			link.l1.go = "PZ_Longway_68";
		break;
		
		case "PZ_Longway_68":
			dialog.text = "Je connais l'endroit idéal et j'ai la réputation de la Compagnie là-bas. Ou du moins je peux faire semblant, comme je l'ai fait avec Georges. La Compagnie... Mynheer Rodenburg utilisait leurs services quand il avait un besoin urgent d'hommes de combat, d'équipages professionnels, qui ne posent pas de questions.";
			link.l1 = "Alors, un équipage de navire à louer... Cela a du sens qu'une telle chose existe. Et combien cela coûtera-t-il ?";
			link.l1.go = "PZ_Longway_69";
		break;
		
		case "PZ_Longway_69":
			dialog.text = "Deux mille cinq cents. Tout de suite et maintenant.";
			link.l1 = "Ça y est ? Il en faut plus que ça pour engager un équipage complet de marins réguliers d'une taverne, surtout pour un grand navire. Apparemment, Rodenburg et ses agents ont des prix spéciaux dans des endroits spéciaux.";
			link.l1.go = "PZ_Longway_70";
		break;
		
		case "PZ_Longway_70":
			dialog.text = "Je parlais de doublons, Monseigneur le Capitaine.";
			link.l1 = "QUOI ?!";
			link.l1.go = "PZ_Longway_70_4";
		break;
		
		case "PZ_Longway_70_4":
			dialog.text = "Vous m'avez bien entendu, Monseigneur le Capitaine. C'est important. Je ne demanderais pas une telle somme pour une bagatelle.";
			link.l1 = "Oui, je t'ai entendu, mais je n'arrive toujours pas à y croire. Des prix spéciaux, vraiment. Acceptent-ils des pesos?";
			link.l1.go = "PZ_Longway_70_5";
		break;
		
		case "PZ_Longway_70_5":
			dialog.text = "Oui... des Blancs. Longway pourrait avoir des problèmes avec ça, mais... je pense que je pourrai les convaincre si je demande avec insistance. Il y a toujours un moyen.";
			link.l1 = "Eh bien, c'est quelque chose. Et c'est juste pour l'équipage... Et tu as aussi un navire à rejoindre. Probablement aussi dans un 'endroit spécial' ? J'ai peur de demander combien cela va nous coûter...";
			link.l1.go = "PZ_Longway_70_6";
		break;
		
		case "PZ_Longway_70_6":
			dialog.text = "Pas tout à fait, Monseigneur le Capitaine. L'équipage vient avec son propre navire.";
			link.l1 = "Mais ?";
			link.l1.go = "PZ_Longway_70_7";
		break;
		
		case "PZ_Longway_70_7":
			dialog.text = "La 'Meifeng'. Elle pourrait devenir un facteur décisif - aucun navire dans l'archipel n'est plus rapide qu'elle. Et elle est... était à moi, donc je la connais. Me la prêterez-vous, Monseigneur le Capitaine ?";
			if (PCharDublonsTotal() >= 2500)
			{
				link.l1 = "Tiens. Deux mille cinq cents doublons. Tant que tu me rapporteras la tête de van der Vink sur un plateau d'or massif, ha ha ha ha !";
				link.l1.go = "PZ_Longway_Dublons_1";
			}
			if (sti(pchar.Money) >= 300000)
			{
				link.l2 = "Je n'ai pas autant de doublons sur moi, Longway. Et je doute même d'en avoir autant sur le navire - c'est un tas d'or dont tu parles. Mais des pesos, bien sûr. Trois cent mille, c'est exactement ce qu'il te faut.";
				link.l2.go = "PZ_Longway_Peso_1";
			}
			link.l3 = "Tu sais quoi, Longway... Suggères-tu vraiment que je dépense assez d'argent pour armer une flotte de siège juste pour que tu puisses te battre contre un vulgaire voyou ?!";
			link.l3.go = "PZ_Longway_Otkaz";
		break;
				
		case "PZ_Longway_Dublons_1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) AddQuestUserData("PZ", "sText", "Mary");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) AddQuestUserData("PZ", "sText", "Helen");
			
			dialog.text = "Oh... Longway vous remercie du fond du coeur, Monseigneur le Capitaine ! Mais encore, qu'en est-il du 'Meifeng' ?";
			if (FindCompanionShips(SHIP_MAYFANG))
			{
				link.l1 = "Quoi ? Mon ami, t'es-tu cogné la tête en venant ici ? Elle est dans notre flotte en ce moment !";
				link.l1.go = "PZ_Longway_Mayfang1";
			}
			else
			{
				link.l1 = "Je dois y réfléchir, Longway. Combien de temps avons-nous pour attraper van der Vink ?";
				link.l1.go = "PZ_Longway_NoMayfang1";
			}
			RemoveDublonsFromPCharTotal(2500);
			pchar.questTemp.PZ_FlagShipDublons = true;
			notification("Longway approves", "Longway");
		break;
		
		case "PZ_Longway_Peso_1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) AddQuestUserData("PZ", "sText", "Mary");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) AddQuestUserData("PZ", "sText", "Helen");
			
			dialog.text = "Monseigneur le Capitaine, vous avez fait une petite erreur. Ce serait deux cent cinquante mille pesos.";
			link.l1 = "I did not; it's Charles de Maure's special exchange rate when his friends need help, ha ha. I'm giving you extra so you'll have enough for everything.";
			link.l1.go = "PZ_Longway_Peso_2";
			AddMoneyToCharacter(pchar, -300000);
		break;
		
		case "PZ_Longway_Peso_2":
			dialog.text = "Merci beaucoup, Monseigneur le Capitaine... Mais, qu'en est-il du 'Meifeng' ?";
			if (FindCompanionShips(SHIP_MAYFANG))
			{
				link.l1 = "Et elle ? Mon ami, vous êtes-vous cogné la tête en venant ici ? Elle est dans notre flotte en ce moment !";
				link.l1.go = "PZ_Longway_Mayfang1";
			}
			else
			{
				link.l1 = "Je dois y réfléchir, Longway. Combien de temps avons-nous pour attraper van der Vink ?";
				link.l1.go = "PZ_Longway_NoMayfang1";
			}
		break;
		
		case "PZ_Longway_Otkaz":
			dialog.text = "Il n'y a pas d'autre moyen, Monseigneur le Capitaine, s'il vous plaît, calmez-vous...";
			link.l1 = "Oh, je n'ai pas encore commencé. Voici l'affaire. Cinquante mille pesos. C'est juste assez pour acheter une brigantine au chantier naval, la préparer pour le combat, et même engager un équipage.";
			link.l1.go = "PZ_Longway_Otkaz_2";
			AddMoneyToCharacter(pchar, -50000);
			
			pchar.questTemp.PZ.LongwayBrig = true; // Лонгвэй будет на бриге
			notification("Longway disapproves", "Longway");
		break;
		
		case "PZ_Longway_Otkaz_2":
			dialog.text = "Mais, Monseigneur le Capitaine. Cela peut suffire pour un capitaine blanc ! Tout le monde ne sera pas d'accord pour traiter avec Longway. Ils seront durs en affaires avant de me vendre quoi que ce soit !";
			link.l1 = "Alors, sois persuasif ! Tu es plutôt habile à marchander, à en juger par ta proposition initiale... Es-tu encore là ? Prends cet argent et va-t'en, puisque c'est si urgent comme tu le dis !";
			link.l1.go = "PZ_Longway_Otkaz_3";
		break;
		
		case "PZ_Longway_Otkaz_3":
			dialog.text = "Ouais, monseigneur le capitaine...";
			link.l1 = "Et ne me regarde pas comme ça. Je te verrai plus tard à la Tortue. Bonne chance.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_NeedToTortuga");
			AddQuestRecord("PZ", "58");
		break;
		
		case "PZ_Longway_Mayfang1":
			dialog.text = "Ahem, non, Monseigneur le Capitaine. Bien sûr, je me souviens. Longway demandait juste si vous êtes prêt à me la partager.";
			link.l1 = "Je le suis. Après tout, van der Vink est tout autant impliqué dans les malheurs de ta sœur que les autres personnes sur notre liste. Donc, l'attraper est vraiment important. Je te confie le commandement du Meifeng.";
			link.l1.go = "PZ_Longway_Mayfang2";
		break;
		
		case "PZ_Longway_Mayfang2":
			// если "Мейфенг" у ГГ
			if (FindCompanionShips(SHIP_MAYFANG))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_MAYFANG)
						{
							//pchar.questTemp.PZ.Mayfang.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.PZ.Mayfang.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
			}
			
			pchar.questTemp.PZ.LongwayMayfang = true;
			pchar.questTemp.PZ_FlagShip = true;
			
			dialog.text = "Je n'arrive pas à y croire... Merci, Monseigneur le Capitaine !";
			link.l1 = "Ah, ce n'est rien. Elle était ton navire, je m'en souviendrai toujours. Eh bien, vas-y. Tue ce fils de chien. Je pars pour Tortuga.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_NeedToTortuga");
			AddQuestRecord("PZ", "59");
			notification("Longway approves", "Longway");
		break;
		
		
		case "PZ_Longway_NoMayfang1":
			dialog.text = "Le temps presse, Monseigneur le Capitaine. Nous ne devrions pas le gaspiller - Chang Xing pourrait avoir besoin de notre aide...";
			link.l1 = "Je le sais, Longway. Néanmoins, combien de temps avons-nous exactement pour attraper van der Vink ?";
			link.l1.go = "PZ_Longway_NoMayfang2";
		break;
		
		case "PZ_Longway_NoMayfang2":
			dialog.text = "Quelques mois - il suit cette route régulièrement pendant environ ce temps avant de disparaître pour un moment. C'est sa manière, comme Gravel m'en a informé dans sa lettre.";
			link.l1 = "D'accord. Allons au navire, alors...";
			link.l1.go = "PZ_Longway_NoMayfang3";
		break;
		
		case "PZ_Longway_NoMayfang3":
			dialog.text = "J'ai bien peur que mes préparatifs doivent commencer immédiatement, Monseigneur le Capitaine. Ainsi, nous pourrons commencer tout de suite quand j'aurai le Meifeng. Je dois négocier avec les hommes à l'avance.";
			link.l1 = "Où nous rencontrons-nous ?";
			link.l1.go = "PZ_Longway_NoMayfang4";
		break;
		
		case "PZ_Longway_NoMayfang4":
			AddQuestRecord("PZ", "60");
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) AddQuestUserData("PZ", "sText", "Mary");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) AddQuestUserData("PZ", "sText", "Helen");
			
			i = FindColony("Pirates");
			if (colonies[i].nation != ENGLAND)
			{
				dialog.text = "Juste ici. Mais nous pouvons nous rencontrer au chantier naval pour votre commodité.";
				link.l1 = "Et pourquoi suis-je le seul à ne pas savoir qu'on peut engager un équipage complet de combattants ici pour le bon prix ?";
				link.l1.go = "PZ_Longway_NoMayfangIslaTesoro1";
			}
			else
			{
				dialog.text = "Ces mercenaires avaient un repaire sur l'Isla Tesoro, mais ont été forcés de déménager ici.";
				link.l1 = "Je comprends pourquoi. Alors, où puis-je vous trouver à La Vega ?";
				link.l1.go = "PZ_Longway_NoMayfangLaVega1";
			}
		break;
		
		case "PZ_Longway_NoMayfangIslaTesoro1":
			dialog.text = "Parce que très peu de gens le savent. Et encore moins peuvent se le permettre. Mynheer Rodenburg était leur seul client pendant longtemps.";
			link.l1 = "Je vois. D'accord, Longway. À plus tard.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_LongwayToPiratesShipyard");
		break;
		
		case "PZ_Longway_NoMayfangLaVega1":
			dialog.text = "La taverne, Monseigneur le Capitaine. Où serais-je sinon ?";
			link.l1 = "C'est ça. À plus tard alors, Longway ! Prends soin de toi.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_LongwayToLaVegaTavern");
		break;
		
		case "PZ_Longway_WaitForShip1":
			dialog.text = "Monseigneur le Capitaine, je dois vous informer que l'équipage est prêt. Il reste une dernière affaire à régler. Qu'en est-il du 'Meifeng'?";
			link.l1 = "Jusqu'à présent, je n'ai pas vraiment choisi un navire digne de vous, Longway.";
			link.l1.go = "PZ_Longway_WaitForShip2";
			if ((FindCompanionShips(SHIP_SCHOONER_W)) || (FindCompanionShips(SHIP_BRIG)) || (FindCompanionShips(SHIP_CORVETTE)) || (FindCompanionShips(SHIP_POLACRE)) || (FindCompanionShips(SHIP_XebekVML)) || (FindCompanionShips(SHIP_BRIGANTINE)))
			{
				if (FindCompanionShips(SHIP_SCHOONER_W)) sStr = "War schooner";
				if (FindCompanionShips(SHIP_BRIG)) sStr = "Brig";
				if (FindCompanionShips(SHIP_CORVETTE)) sStr = "Corvette";
				if (FindCompanionShips(SHIP_POLACRE)) sStr = "Polacre";
				if (FindCompanionShips(SHIP_XebekVML)) sStr = "Xebek";
				if (FindCompanionShips(SHIP_BRIGANTINE)) sStr = "Brigantine";
				link.l2 = "'"+sStr+"est à vous.";
				link.l2.go = "PZ_Longway_NoQuestShip1";
			}
			if (FindCompanionShips(SHIP_MAYFANG))
			{
				link.l3 = "Et pour la 'Meifeng' ? Pensais-tu que je la laisserais se perdre ?";
				link.l3.go = "PZ_Longway_Mayfang3";
			}
			if (FindCompanionShips(SHIP_CURSED_FDM))
			{
				link.l4 = "J'ai un... navire spécial pour toi, Longway. Un rapide. Et encore plus mortel que Meifeng. C'est un galion de guerre, le 'Cœur Volant'.";
				link.l4.go = "PZ_Longway_Caleuche1";
			}
			if (FindCompanionShips(SHIP_POLACRE_QUEST))
			{
				link.l5 = "Tu aimes les chebecs, Longway. Et les polacres ? Surtout celle-ci, le 'Torero'. Pas conçue pour les régates, bien sûr, mais elle est plutôt puissante.";
				link.l5.go = "PZ_Longway_Torero1";
			}
			if (FindCompanionShips(SHIP_ELCASADOR))
			{
				link.l6 = "Je dois avouer, je ne pensais pas qu'il y aurait un jour une utilisation digne pour cela. Que penses-tu de ce galion ? Le puissant 'El Casador' !";
				link.l6.go = "PZ_Longway_ElCasador1";
			}
		break;
		
		case "PZ_Longway_NoQuestShip1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			
			// а теперь хором, дети: ненавижу костыли, ненавижу костыли, ненавижу костыли, нена... помогите!!!
			if ((FindCompanionShips(SHIP_SCHOONER_W)) && (!FindCompanionShips(SHIP_BRIG)) && (!FindCompanionShips(SHIP_CORVETTE)) && (!FindCompanionShips(SHIP_POLACRE)) && (!FindCompanionShips(SHIP_XebekVML)) && (!FindCompanionShips(SHIP_BRIGANTINE)))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_SCHOONER_W)
						{
							//pchar.questTemp.PZ.SchoonerW.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.PZ.SchoonerW.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
				
				pchar.questTemp.PZ.LongwaySchoonerW = true;
			}
			if ((!FindCompanionShips(SHIP_SCHOONER_W)) && (FindCompanionShips(SHIP_BRIG)) && (!FindCompanionShips(SHIP_CORVETTE)) && (!FindCompanionShips(SHIP_POLACRE)) && (!FindCompanionShips(SHIP_XebekVML)) && (!FindCompanionShips(SHIP_BRIGANTINE)))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_BRIG)
						{
							//pchar.questTemp.PZ.Brig.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.PZ.Brig.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
				
				pchar.questTemp.PZ.LongwayBrig = true;
			}
			if ((!FindCompanionShips(SHIP_SCHOONER_W)) && (!FindCompanionShips(SHIP_BRIG)) && (FindCompanionShips(SHIP_CORVETTE)) && (!FindCompanionShips(SHIP_POLACRE)) && (!FindCompanionShips(SHIP_XebekVML)) && (!FindCompanionShips(SHIP_BRIGANTINE)))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_CORVETTE)
						{
							//pchar.questTemp.PZ.Corvette.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.PZ.Corvette.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
				
				pchar.questTemp.PZ.LongwayCorvette = true;
			}
			if ((!FindCompanionShips(SHIP_SCHOONER_W)) && (!FindCompanionShips(SHIP_BRIG)) && (!FindCompanionShips(SHIP_CORVETTE)) && (FindCompanionShips(SHIP_POLACRE)) && (!FindCompanionShips(SHIP_XebekVML)) && (!FindCompanionShips(SHIP_BRIGANTINE)))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_POLACRE)
						{
							//pchar.questTemp.PZ.Polacre.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.Polacre.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
				
				pchar.questTemp.PZ.LongwayPolacre = true;
			}
			if ((!FindCompanionShips(SHIP_SCHOONER_W)) && (!FindCompanionShips(SHIP_BRIG)) && (!FindCompanionShips(SHIP_CORVETTE)) && (!FindCompanionShips(SHIP_POLACRE)) && (FindCompanionShips(SHIP_XebekVML)) && (!FindCompanionShips(SHIP_BRIGANTINE)))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_XebekVML)
						{
							//pchar.questTemp.PZ.Xebek.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.PZ.Xebek.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
				
				pchar.questTemp.PZ.LongwayXebek = true;
			}
			if ((!FindCompanionShips(SHIP_SCHOONER_W)) && (!FindCompanionShips(SHIP_BRIG)) && (!FindCompanionShips(SHIP_CORVETTE)) && (!FindCompanionShips(SHIP_POLACRE)) && (!FindCompanionShips(SHIP_XebekVML)) && (FindCompanionShips(SHIP_BRIGANTINE)))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_BRIGANTINE)
						{
							//pchar.questTemp.PZ.Brigantine.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.PZ.Brigantine.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
				
				pchar.questTemp.PZ.LongwayBrigantine = true;
			}
			
			dialog.text = "Ce n'est pas le 'Meifeng', Monseigneur le Capitaine ! Qu'est-il arrivé au Meifeng ?";
			link.l1 = "Longway ! "+sStr+" est en danger ! Et ta sœur aussi ! Et toi, tu râles parce que tu n'as pas un navire comme celui-ci ?! N'importe qui serait heureux d'avoir un navire comme celui-ci ! Prends-la sous ton commandement et montre à van der Vink de quoi tu es capable.";
			link.l1.go = "PZ_Longway_NoQuestShip2";
		break;
		
		case "PZ_Longway_NoQuestShip2":
			dialog.text = "D'accord... J'espère que le Ciel m'enverra la bonne fortune. Tout comme je l'espère pour vous à Tortuga. Adieu, Monseigneur le Capitaine.";
			link.l1 = "J'en suis sûr. Adieu, Longway.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_NeedToTortuga");
			pchar.questTemp.PZ_NoQuestShip = true;
		break;
		
		case "PZ_Longway_Mayfang3":
			// если "Мейфенг" у ГГ
			if (FindCompanionShips(SHIP_MAYFANG))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_MAYFANG)
						{
							//pchar.questTemp.PZ.Mayfang.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.PZ.Mayfang.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
			}
			
			pchar.questTemp.PZ.LongwayMayfang = true;
			pchar.questTemp.PZ_FlagShip = true;
			
			dialog.text = "Hum, non, Monseigneur le Capitaine. Bien sûr, je me souviens. Longway demandait juste si vous êtes prêt à la partager avec moi.";
			link.l1 = "Je le suis. Après tout, van der Vink est tout autant impliqué dans les malheurs de ta sœur que les autres personnes sur notre liste. Donc l'attraper est vraiment important. Je te confie le commandement du 'Meifeng'.";
			link.l1.go = "PZ_Longway_Mayfang4";
		break;
		
		case "PZ_Longway_Mayfang4":
			dialog.text = "Je n'arrive pas à y croire... Merci, Monseigneur le Capitaine !";
			link.l1 = "Ah, ce n'est rien. Elle était autrefois ton navire, je m'en souviendrai toujours. Eh bien, vas-y. Tue ce fils de pute. Je pars pour la Tortue.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_NeedToTortuga");
			notification("Longway approves", "Longway");
		break;
		
		case "PZ_Longway_Caleuche1":
			dialog.text = "Je... je ne peux pas commander ÇA, Monseigneur le Capitaine. Longway tient encore à sa vie, son âme et sa santé mentale.";
			link.l1 = "Ha ha ha, Longway ! Allez, je ne savais pas que tu étais si superstitieux. Mais de toute façon, la malédiction a été levée, donc tu n'as rien à craindre.";
			link.l1.go = "PZ_Longway_Caleuche2";
		break;
		
		case "PZ_Longway_Caleuche2":
			dialog.text = "Ah... mais van der Vink le sait-il ? Il s'enfuira comme un lapin effrayé dès qu'il verra ce navire.";
			link.l1 = "Tu as raison à ce sujet. Très bien, nous te trouverons autre chose.";
			link.l1.go = "PZ_Longway_WaitForShip2";
		break;
		
		case "PZ_Longway_Torero1":
			// если "Тореро" у ГГ
			if (FindCompanionShips(SHIP_POLACRE_QUEST))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_POLACRE_QUEST)
						{
							//pchar.questTemp.PZ.Torero.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.PZ.Torero.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
			}
			
			pchar.questTemp.PZ.LongwayTorero = true;
			if (CheckAttribute(pchar, "questTemp.PZ_FlagShipDublons"))
			{
				pchar.questTemp.PZ_FlagShip = true;
				notification("Longway approves", "Longway");
			}
			
			dialog.text = "Je n'ai jamais navigué sur une polacre en tant que capitaine moi-même. Elle est intéressante, mais la vitesse est la chose la plus importante maintenant, pas la puissance.";
			link.l1 = "C'est vrai, mais c'est une polacre, après tout. Elle n'est peut-être pas aussi rapide que le 'Banten', mais tu peux attraper le vent sous des angles qu'ils ne peuvent pas. Encore plus que le 'Meifeng' elle-même ne l'aurait jamais pu. Alors profite de cela.";
			link.l1.go = "PZ_Longway_Torero2";
		break;
		
		case "PZ_Longway_Torero2":
			dialog.text = "Quand même... le 'Meifeng' était mieux... Dommage que tu l’aies laissée se perdre, Monseigneur le Capitaine. Bonne chance à Tortuga.";
			link.l1 = "Je vous retourne le compliment, Longway. Merci.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_NeedToTortuga");
		break;
		
		case "PZ_Longway_ElCasador1":
			// если "Эль Касадор" у ГГ
			if (FindCompanionShips(SHIP_ELCASADOR))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_ELCASADOR)
						{
							//pchar.questTemp.PZ.ElCasador.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.PZ.ElCasador.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
			}
			
			pchar.questTemp.PZ.LongwayElCasador = true;
			if (CheckAttribute(pchar, "questTemp.PZ_FlagShipDublons"))
			{
				pchar.questTemp.PZ_FlagShip = true;
				notification("Longway approves", "Longway");
			}
			
			dialog.text = "Que ce soit le galion le plus inhabituel de l'Archipel, Monseigneur le Capitaine. Je peux le gérer, mais il est plus lent que le 'Banten'...";
			link.l1 = "Eh bien, tu ne fais pas la course avec Joep lors d'une régate, n'est-ce pas ?";
			link.l1.go = "PZ_Longway_ElCasador2";
		break;
		
		case "PZ_Longway_ElCasador2":
			dialog.text = "Quoi que vous disiez. Mais la 'Meifeng' était meilleure... Dommage que vous l'ayez laissée se perdre, Monseigneur le Capitaine. Bonne chance à Tortuga.";
			link.l1 = "De même, Longway. Je te remercie.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_NeedToTortuga");
		break;
		
		case "PZ_Longway_WaitForShip2":
			NextDiag.TempNode = "PZ_Longway_WaitForShip1";
			
			dialog.text = "J'apprécie votre sollicitude, Monseigneur le Capitaine, mais dépêchons-nous, je vous prie - nous n'avons guère de temps.";
			link.l1 = "Je sais. Mais tu ne veux pas courir après des chimères, n'est-ce pas ? D'accord, je vais te trouver un vrai navire.";
			link.l1.go = "Exit";
		break;
		
		case "PZ_HelenaTortugaCabin_1":
			dialog.text = "Nous y sommes presque, Charles. As-tu décidé par où commencer ? Peut-être qu'il serait judicieux de demander aux gens dans les rues...";
			link.l1 = "Peut-être que oui. Mais pas pour nous - pour moi. Tu resteras à bord, Hélène.";
			link.l1.go = "PZ_HelenaTortugaCabin_2";
		break;
		
		case "PZ_HelenaTortugaCabin_2":
			dialog.text = "Charles, bien sûr, je suis toujours inquiet à propos de ces vauriens et de ce qu'ils ont dit, et il est logique pour moi de rester sous la protection de l'équipage... Mais le fait que tu te diriges seul dans l'antre de la bête ne me rassure pas davantage.";
			link.l1 = "Je comprends. Mais si les choses tournent mal, il est bien plus facile de fuir seul, sachant que tu es en sécurité. C'est un ordre, Hélène. Attends-moi ici et essaie de ne pas trop t'inquiéter.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_TortugaCabin_Exit");
		break;
		
		case "PZ_MaryTortugaCabin_1":
			dialog.text = "Voici Tortuga, Charles, ouais, hein ? J'ai hâte de frapper à quelques portes, demander ce que ce gros âne voulait de moi...";
			link.l1 = "C'est exactement pourquoi tu restes à bord, ma chère.";
			link.l1.go = "PZ_MaryTortugaCabin_2";
			
			pchar.questTemp.MarySexBlock = true;
			pchar.quest.Mary_giveme_sex.over = "yes";
			pchar.quest.Mary_giveme_sex1.over = "yes";
		break;
		
		case "PZ_MaryTortugaCabin_2":
			dialog.text = "Pas question ! Tu crois que je vais te laisser aller à terre tout seul ?";
			link.l1 = "Je pense que si Levasseur décide de terminer ce que ses mercenaires n'ont pas réussi à faire, nous n'aurons aucune chance de riposter. Je ne veux pas le provoquer inutilement, d'autant plus que ma cible n'est pas lui mais Joep van der Vink.";
			link.l1.go = "PZ_MaryTortugaCabin_3";
		break;
		
		case "PZ_MaryTortugaCabin_3":
			dialog.text = "Alors je suis enfermé maintenant, ouais, hein ?";
			link.l1 = "Je ne te donne pas d'ordre, je te le demande, Mary.";
			link.l1.go = "PZ_MaryTortugaCabin_4";
		break;
		
		case "PZ_MaryTortugaCabin_4":
			dialog.text = "Et si quelque chose t'arrivait dans une ruelle de cette île de merde ?";
			link.l1 = "Alors je promets de ne pas jouer les héros. Et savoir que tu es en sécurité m'aidera à courir plus vite. Alors attends-moi sur le navire, et pour l'amour de Dieu, ne descends pas à terre, quoi qu'il arrive.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_TortugaCabin_Exit");
		break;
		
		case "PZ_RobertMartin1":
			chrDisableReloadToLocation = true;
			
			dialog.text = "Qui es-tu ? Je doute que tu aies traversé la plage juste pour discuter.";
			link.l1 = "C'est ça. Charles de Maure. Rober Martene ?";
			link.l1.go = "PZ_RobertMartin2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_RobertMartin2":
			dialog.text = "Le Charles de Maure ? Merde, ne me mêle pas à des affaires louches. Ouais, c'est moi. Alors, qu'est-ce que tu veux ?";
			link.l1 = "On m'a dit que tu es ami avec Joep van der Vink, et...";
			link.l1.go = "PZ_RobertMartin3";
		break;
		
		case "PZ_RobertMartin3":
			dialog.text = "Qui t'a dit ça ? Je vais leur faire cracher leurs tripes. Eh bien, on se connaît, c'est tout. Je ne veux pas d'ennuis parce qu'il t'a contrarié.";
			link.l1 = "Hé hé, tu es rapide à abandonner tes amis...";
			link.l1.go = "PZ_RobertMartin4";
		break;
		
		case "PZ_RobertMartin4":
			dialog.text = "Ne pense pas ça. Je n'ai pas peur de toi. Mais pourquoi se donner la peine ou même la créer ? Je ne connais pas Joep aussi intimement qu'on te l'a dit. Le cherches-tu ?";
			link.l1 = "Ouais, en quelque sorte. Je sais qu'il a déjà quitté la Tortue, mais ça ne ferait pas de mal d'en savoir plus sur lui - où il a été, à qui il a parlé. Peux-tu m'aider ?";
			link.l1.go = "PZ_RobertMartin5";
		break;
		
		case "PZ_RobertMartin5":
			dialog.text = "Ça ne te servirait de toute façon à rien, alors... pourquoi pas ? Il était dans un bordel. Le bordel. Je pense que tu peux te le permettre, alors je te le dis.";
			link.l1 = "Un nouveau bordel ? Un seul ne te suffit plus ?";
			link.l1.go = "PZ_RobertMartin6";
		break;
		
		case "PZ_RobertMartin6":
			dialog.text = "Eh bien, pas vraiment nouveau, mais peu de gens le connaissent. Et seuls quelques-uns peuvent se le permettre. Je suppose que votre temps est venu. Mais soyez averti - seuls les doublons sont acceptés. Glissez de l'argent en argent, et vous recevrez un coup de pied au cul.";
			link.l1 = "Je m'en doutais. Et où disiez-vous que ce bordel se trouve ?";
			link.l1.go = "PZ_RobertMartin7";
		break;
		
		case "PZ_RobertMartin7":
			dialog.text = "Tu vois ce bâtiment avec les colonnes ? C'est celui-là. Et quelle hôtesse ils ont ! La peau jaune, tellement séduisante ! Hein, je vois que tu baves déjà, hein ?";
			link.l1 = "Heh-heh, en quelque sorte. Merci, Rober. Pas d'ennuis pour toi aujourd'hui - tu m'as été d'une grande aide.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_LighthouseMartinGo");
		break;
		
		case "PZ_MaryTortugaCabin_11":
			dialog.text = "Enfin te voilà, Charles ! Je ne savais plus où me mettre, ouais, hein ?";
			link.l1 = "Je ne serai pas long, Mary. J'ai une petite affaire à régler... Je ne te laisserai pas en haleine - c'est l'affaire de Longway. Je dois visiter un bordel local.";
			link.l1.go = "PZ_MaryTortugaCabin_12";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_MaryTortugaCabin_12":
			dialog.text = "Je savais que je n'aurais pas dû te laisser aller à terre seul. Soit tu as oublié de mettre ton chapeau et ta tête a pris un coup de chaud... Soit tu t'es cogné, ouais, hein !";
			link.l1 = "Mary, écoute-moi. Il est possible que la propriétaire de cet établissement soit la sœur de Longway. Pour en être sûr, il faudrait que je la voie, mais c'est tout ce que je ferai. Je ne peux pas le faire sans entrer. Mais je ne veux pas que tu penses quelque chose que tu ne devrais pas.";
			link.l1.go = "PZ_MaryTortugaCabin_13";
		break;
		
		case "PZ_MaryTortugaCabin_13":
			dialog.text = "Es-tu sûr de ne pas me mentir, Charles ?";
			link.l1 = "Mary, regarde ça de cette façon... As-tu déjà entendu parler d'un homme avertissant sa bien-aimée à propos de... ?";
			link.l1.go = "PZ_MaryTortugaCabin_14";
		break;
		
		case "PZ_MaryTortugaCabin_14":
			dialog.text = "Arrête-toi là, Charles, je ne veux même pas y penser. Je crois en toi et je te fais confiance. Et j'espère que tu n'y resteras pas plus longtemps que nécessaire.";
			link.l1 = "Pas une minute de plus, ma chérie, je te le promets. On entre et on sort, tu verras.";
			link.l1.go = "PZ_PredupredilNashuDevushku";
		break;
		
		case "PZ_HelenaTortugaCabin_11":
			dialog.text = "Charles ! Tu es de retour encore plus vite que je ne l'avais prévu. Mais que s'est-il passé ? Tu n'as pas l'air bien... As-tu découvert quelque chose au sujet de Joep van der Vink ?";
			link.l1 = "Pas encore. J'ai appris quelques choses, mais pour aller plus loin... Je dois aller dans un... bordel. Pas pour ce que tu pourrais penser, bien sûr.";
			link.l1.go = "PZ_HelenaTortugaCabin_12";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_HelenaTortugaCabin_12":
			dialog.text = "Un bordel ? Je ne savais pas que ces endroits proposaient autre chose que l’évidence.";
			link.l1 = "J’ai juste besoin de parler à la patronne, c’est tout. Et ce n’est pas un bordel ordinaire. Il paraît que c’est un établissement très coûteux, réservé à la haute société...";
			link.l1.go = "PZ_HelenaTortugaCabin_13";
		break;

		case "PZ_HelenaTortugaCabin_13":
			dialog.text = "Alors c’est parfait pour toi, chéri. Je plaisante. Mais je ne suis pas ravie que tu y ailles. Enfin...";
			link.l1 = "Je te promets que c’est uniquement pour les affaires de Longway. Il est fort possible que la patronne soit sa sœur. Je ne resterai pas longtemps.";
			link.l1.go = "PZ_HelenaTortugaCabin_14";
		break;

		case "PZ_HelenaTortugaCabin_14":
			dialog.text = "Comme tu veux. Tu n’as aucune obligation de me tenir informée de ce genre de choses. Je ne t’ai jamais promis de ne pas coucher avec un autre homme. Et pourtant, je ne le fais pas. Car c’est une évidence pour moi.";
			link.l1 = "Dans d’autres circonstances, je t’aurais emmenée avec moi, mais...";
			link.l1.go = "PZ_HelenaTortugaCabin_15";
		break;

		case "PZ_HelenaTortugaCabin_15":
			dialog.text = "Merci, mais non merci. Charles, ne t’inquiète pas. Je ne suis pas une idiote jalouse. Bon, peut-être jalouse, mais pas idiote. Et je te crois. Quelle idiote je suis !";
			link.l1 = "Merci, Helen. Je reviens tout de suite.";
			link.l1.go = "PZ_PredupredilNashuDevushku";
		break;

		case "PZ_PredupredilNashuDevushku":
			DialogExit();
			LAi_SetActorType(npchar);
			pchar.questTemp.PZ_PredupredilNashuDevushku = true;
		break;
		
		case "PZ_ElitaShluha_1":
			dialog.text = "Oh, un nouveau visage dans notre établissement ? Bienvenue, monsieur. De la nourriture, du vin vieilli, un bain chaud - tout vous attend si vous pouvez vous permettre de passer du temps avec l'un d'entre nous.";
			link.l1 = "Merci pour votre accueil, mademoiselle. Mais ce n'est pas pour cela que je suis ici. Je cherche quelqu'un...";
			link.l1.go = "PZ_ElitaShluha_2";
			
			// Убираем Мартэна с Маяка
			sld = characterFromID("PZ_RobertMartin");
			ChangeCharacterAddressGroup(sld, "none", "", "");
			
			for (i=1; i<=3; i++)
			{
				sld = characterFromID("PZ_MayakPiraty_"+i);
				sld.lifeday = 0;
			}
			
			sld = characterFromID("PZ_RobertMartin_CloneMayakShip");
			sld.lifeday = 0;
			
			locations[FindLocation("Mayak6")].DisableEncounters = false;
			LAi_LocationFightDisable(&Locations[FindLocation("Mayak6")], false);
			RemoveGeometryFromLocation("Mayak6", "smg");
		break;
		
		case "PZ_ElitaShluha_2":
			dialog.text = "It is only with the heart that one can see rightly; what is essential is invisible to the eye.";
			link.l1 = "C'est magnifique. Je n'ai jamais entendu ces mots auparavant.";
			link.l1.go = "PZ_ElitaShluha_3";
		break;
		
		case "PZ_ElitaShluha_3":
			dialog.text = "Nous sommes éduquées ici, pas seulement des poupées. L'hôtesse pense que c'est essentiel pour notre établissement.";
			link.l1 = "L'hôtesse ! C'est elle que je cherche. J'ai entendu dire qu'elle a la peau jaune. Dis-moi, est-ce vrai ? Comment s'appelle-t-elle, d'ailleurs ?";
			link.l1.go = "PZ_ElitaShluha_4";
		break;
		
		case "PZ_ElitaShluha_4":
			dialog.text = "C'est vrai. Mais elle a un meilleur sens des affaires que bien des femmes blanches. Elle s'appelle Belle Etoile. Mais assez parlé.";
			link.l1 = "Assez parlé, dis-tu ? Je suis ici pour parler. Je poserai encore quelques questions, puis je partirai.";
			link.l1.go = "PZ_ElitaShluha_5";
		break;
		
		case "PZ_ElitaShluha_5":
			dialog.text = "Et quel en serait le bénéfice pour l'établissement ? Ils ne paient pas pour les corps ici, mais pour le temps. Tu veux parler ? Tu es le bienvenu. Mais l'argent d'abord. Et nous chuchoterons dans la chambre, à l'abri des oreilles indiscrètes. Je me fiche de ce que nous y ferons - je m'en fiche que nous allumions des bougies et priions. Un client m'a déjà demandé de l'aider à écrire un poème. Un autre pour parler de ses problèmes, m'appelant son bon ami. Et un troisième - juste pour allumer des bougies, pour que...";
			link.l1 = "Eh bien, je ne veux pas savoir - j'ai déjà entendu quelque chose de désagréable récemment. Combien je te dois ?";
			link.l1.go = "PZ_ElitaShluha_6";
		break;
		
		case "PZ_ElitaShluha_6":
			dialog.text = "Deux cent cinquante doublons. Pas de marchandage. Si on se rend compte qu'on a affaire à un imposteur sans le sou, on le jette dehors sans regret. Et s'il est riche mais avare, on augmente le prix - il paiera de toute façon.";
			if (PCharDublonsTotal() >= 250)
			{
				link.l1 = "Voilà, deux cent cinquante pièces d'or.";
				link.l1.go = "PZ_ElitaShluha_7";
			}
			link.l2 = "Ouah, cet endroit est plus cher que ce bordel en Jamaïque. Puis-je revenir plus tard après avoir obtenu l'or ?";
			link.l2.go = "PZ_ElitaShluha_Otkaz_1";
		break;
		
		case "PZ_ElitaShluha_7":
			dialog.text = "Bien. Par où commencerons-nous ? Dîner, avec ou sans bougies, bain, conversation ?";
			link.l1 = "Je n'ai pas beaucoup de temps, alors allons droit à mes questions. Montre le chemin.";
			link.l1.go = "PZ_ElitaShluha_IdemVKomnatu";
			RemoveDublonsFromPCharTotal(250);
		break;
		
		case "PZ_ElitaShluha_Otkaz_1":
			dialog.text = "Bien sûr que tu peux. La patience est l'une des vertus d'une courtisane. Jeter un mendiant dehors est une chose. Laisser un riche gentleman comme toi aller chercher son argent, ou même l'emprunter, c'en est une autre.";
			link.l1 = "Les vertus d'une courtisane... Ironique. Je reviens tout de suite.";
			link.l1.go = "PZ_ElitaShluha_Otkaz_2";
		break;
		
		case "PZ_ElitaShluha_Otkaz_2":
			DialogExit();
			for (i=1; i<=4; i++)
			{
				sld = CharacterFromID("PZ_ElitaShluha_"+i);
				LAi_CharacterDisableDialog(sld);
			}
			LAi_CharacterEnableDialog(npchar);
			npchar.dialog.filename = "Quest\CompanionQuests\Longway.c";
			npchar.dialog.currentnode = "PZ_ElitaShluha_Again";
		break;
		
		case "PZ_ElitaShluha_Again":
			dialog.text = "Bienvenue, monsieur ! Alors, qui êtes-vous ? Un riche gentleman ou un imposteur ?";
			if (PCharDublonsTotal() >= 250)
			{
				link.l1 = "Bien sûr, je suis un riche gentleman, mademoiselle. Voici votre or - tous deux cent cinquante doublons. Pas besoin de les compter.";
				link.l1.go = "PZ_ElitaShluha_Again_1";
			}
			link.l2 = "Je suis encore à court, supporte-moi juste un peu.";
			link.l2.go = "exit";
			NextDiag.TempNode = "PZ_ElitaShluha_Again";
		break;
		
		case "PZ_ElitaShluha_Again_1":
			dialog.text = "Nous ne comptons pas ici. Hmm, certaines des pièces ont l'air tordues et cassées - la maîtresse n'aimera pas ça, mais au moins c'est tout de l'or véritable.";
			link.l1 = "Quelle... personne gracieuse elle est.";
			link.l1.go = "PZ_ElitaShluha_Again_2";
			RemoveDublonsFromPCharTotal(250);
		break;
		
		case "PZ_ElitaShluha_Again_2":
			dialog.text = "C'est ça. Madame Etoile peut être douce et attentionnée, elle peut être stricte, et elle peut être impitoyable. C'est pourquoi nous ne comptons pas, d'ailleurs. La maîtresse n'est pas toujours payée immédiatement, mais elle reçoit toujours son dû. Si ce n'est pas en or, alors c'est en sang. Toute maison de tolérance a besoin de protecteurs et de patrons. Et les nôtres correspondent au statut de l'établissement.";
			link.l1 = "J'ai payé, alors montre-moi le chemin.";
			link.l1.go = "PZ_ElitaShluha_IdemVKomnatu";
		break;
		
		case "PZ_ElitaShluha_IdemVKomnatu":
			DialogExit();
			pchar.PZ_ElitaShluha = npchar.id;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "reload", "reload3", "PZ_ElitaShluha_VKomnate", -1);
			LAi_SetActorType(pchar);
			LAi_ActorFollow(pchar, npchar, "", -1);
			bDisableCharacterMenu = true;
		break;
		
		case "PZ_ElitaShluha_8":
			dialog.text = "Alors, quelles questions avez-vous, monsieur ? Je vais essayer de satisfaire votre... curiosité.";
			link.l1 = "Tu sais ce qui m'intéresse, mademoiselle - ta maîtresse, Madame Etoile.";
			link.l1.go = "PZ_ElitaShluha_9";
		break;
		
		case "PZ_ElitaShluha_9":
			dialog.text = "Que puis-je dire d'elle ? Elle reste un mystère, même pour nous. Bien qu'elle se soucie de notre bien-être, de notre santé et de notre sécurité, elle ne socialise pas et ne se rapproche de personne parmi nous.";
			link.l1 = "Peut-être qu'elle n'aime pas les longues conversations. Dis-moi, parle-t-elle avec un accent ?";
			link.l1.go = "PZ_ElitaShluha_10";
		break;
		
		case "PZ_ElitaShluha_10":
			dialog.text = "Non, qu'est-ce qui te fait penser ça ? Juste parce qu'elle a la peau jaune ? Elle parle un français pur et plusieurs autres langues. Et elle peut tenir une conversation d'une heure sur n'importe quel sujet avec des invités et des parties prenantes potentielles.";
			link.l1 = "Tu ne dis pas. Intéressant... Est-elle ici maintenant ? Si c'est le cas, je vais simplement entrer et la voir pour ne plus gaspiller votre temps vraiment... précieux, afin que vous puissiez retourner à votre travail.";
			link.l1.go = "PZ_ElitaShluha_11";
		break;
		
		case "PZ_ElitaShluha_11":
			dialog.text = "Il n'y a pas grand-chose à retrouver - bien que notre hôtesse ait pour objectif de faire de cet endroit le meilleur de l'Archipel. Un lieu élitiste, où aucun marchand, noble ou simplement personne instruite ne serait honteux de venir - car nous offrons bien plus que nos corps.";
			link.l1 = "Mais elle ne réussit pas très bien, n'est-ce pas ?";
			link.l1.go = "PZ_ElitaShluha_12";
		break;
		
		case "PZ_ElitaShluha_12":
			dialog.text = "Comment dire... Elle nous voit chacun non seulement comme une marchandise, comme dans des établissements plus simples, mais comme un projet. Des vêtements coûteux, des médicaments, de l'éducation - elle investit en chacun de nous. Et si nous étions dans une grande ville du Vieux Monde, elle aurait réussi ! Mais ici... Même un commerçant talentueux ne gagnera rien si les marchandises sont si chères que presque personne ne peut les acheter. Même si nous baissons les prix, nous sommes toujours destinés à faire faillite un jour.";
			link.l1 = "Je suis désolé d'entendre cela. Alors où est votre maîtresse maintenant ?";
			link.l1.go = "PZ_ElitaShluha_13";
		break;
		
		case "PZ_ElitaShluha_13":
			dialog.text = "Nous menons une belle vie ici jusqu'à présent, je peux vous le dire. Cela a un prix : le gagner et se maintenir à ses standards... Quant à la dame, elle est allée à Española pour discuter de la possibilité de nous déplacer tous à Port-au-Prince - après tout, plus de routes commerciales y convergent, et notre commerce ne restera pas inactif et ne subira pas des pertes presque constantes là-bas.";
			link.l1 = "Vraiment ? Levasseur n'a-t-il pas investi dans cet endroit pour en assurer la stabilité ?";
			link.l1.go = "PZ_ElitaShluha_14";
		break;
		
		case "PZ_ElitaShluha_14":
			dialog.text = "Pas trop. Il est venu nous voir et a dit qu'il n'investirait gros que si nous allions chez lui de temps en temps. Mais la dame a refusé catégoriquement. Tellement que Son Excellence a été pris au dépourvu pendant une seconde. Je ne les ai jamais vus comme ça, ni elle ni lui.";
			link.l1 = "Hé hé, regarde ça. Elle semble savoir... Courageuse, très courageuse de sa part.";
			link.l1.go = "PZ_ElitaShluha_15";
		break;
		
		case "PZ_ElitaShluha_15":
			dialog.text = "Sais-tu quoi ? Cependant, puisque nous parlons si bien, je vais te dire quelque chose d'autre, mais c'est un grand secret, alors ne le discute avec personne !";
			link.l1 = "Oh non, mademoiselle. Je vous assure, je ne cherche en aucun cas à nuire à votre dame. S'il vous plaît, continuez.";
			link.l1.go = "PZ_ElitaShluha_16";
		break;
		
		case "PZ_ElitaShluha_16":
			dialog.text = "Je ne sais même pas si tu pourrais lui faire du mal, car Belle Etoile pratique l'escrime tous les jours, et elle n'a aucun adversaire digne dans toute la ville. En plus de Port-au-Prince, elle prévoit de proposer à Marcus Tyrex lui-même d'investir ! Ou plutôt, d'obtenir un prêt de lui. Peux-tu imaginer ?";
			link.l1 = "Oui, et je sens qu'aujourd'hui je vais avoir une conversation très difficile avec une autre femme qui pratique régulièrement l'escrime... Eh bien, merci de l'avoir partagé, mademoiselle. Passez une bonne journée et que vos clients soient généreux.";
			link.l1.go = "PZ_ElitaShluha_17";
		break;
		
		case "PZ_ElitaShluha_17":
			dialog.text = "Merci. Mais pourquoi cette précipitation ? Vous avez payé en entier, et nous n'avons pas parlé si longtemps. De plus, il y a quelque chose de raffiné chez vous, monsieur. Quelque chose de bien plus que les rares riches qui viennent chez nous. Allons-nous vraiment profiter de la compagnie l'un de l'autre ?";
			link.l1 = "Tu sais... mais c’est quoi ce bordel ? Pourquoi est-ce que je fais semblant et je me mens à moi-même comme si je ne voulais pas ça ? Une chance avec une femme comme toi est très rare.";
			link.l1.go = "PZ_ElitaShluha_YesSex";
			link.l2 = "Oh, je regrette de dire non, mademoiselle. Je suis seulement venu ici pour parler. D'ailleurs... quelqu'un m'attend.";
			link.l2.go = "PZ_ElitaShluha_NoSex";
		break;
		
		case "PZ_ElitaShluha_NoSex":
			dialog.text = "Comme si cela avait jamais arrêté quelqu'un. Dans ce cas, vous méritez du respect, monsieur. Je suis très heureux pour votre 'quelqu'un'.";
			link.l1 = "Merci encore, mademoiselle. Adieu.";
			link.l1.go = "PZ_ElitaShluha_NoSex_2";
		break;
		
		case "PZ_ElitaShluha_NoSex_2":
			DialogExit();
			AddQuestRecord("PZ", "30");
			chrDisableReloadToLocation = false;
			bDisableFastReload = true;
			for (i=1; i<=4; i++)
			{
				sld = CharacterFromID("PZ_ElitaShluha_"+i);
				LAi_CharacterDisableDialog(sld);
			}
			npchar.lifeday = 0;
			
			PChar.quest.PZ_TortugaKlemanLebren.win_condition.l1 = "location";
			PChar.quest.PZ_TortugaKlemanLebren.win_condition.l1.location = "Tortuga_town";
			PChar.quest.PZ_TortugaKlemanLebren.win_condition = "PZ_TortugaKlemanLebren";
			DelMapQuestMarkCity("Tortuga");
			AddMapQuestMarkCity("LaVega", false);
			
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1 && !CheckAttribute(pchar, "questTemp.PZ_PredupredilNashuDevushku"))
			{
				setCharacterShipLocation(pchar, "Tortuga_town");
				setWDMPointXZ("Tortuga_town");
			}
		break;
		
		case "PZ_ElitaShluha_YesSex":
			dialog.text = "Merci. Que dirais-tu d'un bain chaud ensemble pour commencer ?";
			link.l1 = "Les deux mains en faveur.";
			link.l1.go = "PZ_ElitaShluha_YesSex_2";
		break;
		
		case "PZ_ElitaShluha_YesSex_2":
			DialogExit();
			LAi_SetStayType(pchar);
			DoQuestCheckDelay("PlaySex_1", 1.0);
			DoQuestCheckDelay("PZ_ElitaShluha_Fuck", 1.0);
		break;
		
		case "PZ_ElitaShluha_After":
			dialog.text = "C'était une expérience magique, monsieur. Je ne pensais pas qu'un homme puisse me surprendre ainsi. Vous savez vraiment comment donner du plaisir à une femme...";
			link.l1 = "Ça dépend de la femme.";
			link.l1.go = "PZ_ElitaShluha_After_2";
		break;
		
		case "PZ_ElitaShluha_After_2":
			dialog.text = "Le regrettes-tu ?";
			link.l1 = "En ce moment, certainement pas. Adieu, mademoiselle.";
			link.l1.go = "PZ_ElitaShluha_After_3";
		break;
		
		case "PZ_ElitaShluha_After_3":
			DialogExit();
			AddQuestRecord("PZ", "30");
			chrDisableReloadToLocation = false;
			bDisableFastReload = true;
			for (i=1; i<=4; i++)
			{
				sld = CharacterFromID("PZ_ElitaShluha_"+i);
				LAi_CharacterDisableDialog(sld);
			}
			npchar.lifeday = 0;
			LAi_SetPlayerType(pchar);
			pchar.questTemp.PZ.EliteWhoreFucked = true; // флаг того, что секс был (понадобится для диалога с Тираксом)
			
			PChar.quest.PZ_TortugaKlemanLebren.win_condition.l1 = "location";
			PChar.quest.PZ_TortugaKlemanLebren.win_condition.l1.location = "Tortuga_town";
			PChar.quest.PZ_TortugaKlemanLebren.win_condition = "PZ_TortugaKlemanLebren";
			DelMapQuestMarkCity("Tortuga");
			AddMapQuestMarkCity("LaVega", false);
			
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1 && !CheckAttribute(pchar, "questTemp.PZ_PredupredilNashuDevushku"))
			{
				setCharacterShipLocation(pchar, "Tortuga_town");
				setWDMPointXZ("Tortuga_town");
			}
		break;
		
		case "PZ_KlemanLebren_1":
			dialog.text = "Regarde où tu vas, frimeur !";
			link.l1 = "Surveille ton langage !";
			link.l1.go = "PZ_KlemanLebren_2";
		break;
		
		case "PZ_KlemanLebren_2":
			dialog.text = "Je regardais où j'allais pendant que tu comptais les corneilles.";
			link.l1 = "Tu aurais pu contourner si tu avais cherché, n'est-ce pas ?";
			link.l1.go = "PZ_KlemanLebren_3";
		break;
		
		case "PZ_KlemanLebren_3":
			dialog.text = "Pourquoi devrais-je te contourner ?!";
			link.l1 = "Je suggère que nous découvrions en dehors de la ville, qui doit quoi et à qui.";
			link.l1.go = "PZ_KlemanLebren_4";
		break;
		
		case "PZ_KlemanLebren_4":
			dialog.text = "Mm-mm, non. J'ignorais que Votre Seigneurie était si dégoûtée par le simple toucher involontaire d'un homme ordinaire.";
			link.l1 = "Répète ?";
			link.l1.go = "PZ_KlemanLebren_5";
		break;
		
		case "PZ_KlemanLebren_5":
			dialog.text = "Hmm, désolé. Ce n'était pas mon intention de vous bousculer.";
			link.l1 = "C'est mieux.";
			link.l1.go = "PZ_KlemanLebren_6";
		break;
		
		case "PZ_KlemanLebren_6":
			DialogExit();
			
			LAi_LocationFightDisable(loadedLocation, false);
			chrDisableReloadToLocation = false;
			
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4", "", "", "", "", -1);
			npchar.location = "None";
			
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				sld = CharacterFromID("Mary");
				DelLandQuestMark(sld);
				if (CheckAttribute(pchar, "questTemp.PZ_PredupredilNashuDevushku"))
				{
					PChar.quest.PZ_TortugaRazgovorVKauteSDevushkoy.win_condition.l1 = "location";
					PChar.quest.PZ_TortugaRazgovorVKauteSDevushkoy.win_condition.l1.location = "Tortuga";
					PChar.quest.PZ_TortugaRazgovorVKauteSDevushkoy.win_condition = "PZ_TortugaRazgovorVKauteSDevushkoy";
				}
				else
				{
					ChangeCharacterAddressGroup(sld, "Tortuga_town", "rld", "loc0");
					sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
					sld.dialog.currentnode = "PZ_MaryRazgovorOBordeli_Bad_1";
					LAi_SetStayType(sld);
					CharacterTurnToLoc(sld, "quest", "quest1");
					sld.talker = 5;
					chrDisableReloadToLocation = true;
					LAi_LocationFightDisable(loadedLocation, true);
				}
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				sld = CharacterFromID("Helena");
				DelLandQuestMark(sld);
				PChar.quest.PZ_TortugaRazgovorVKauteSDevushkoy.win_condition.l1 = "location";
				PChar.quest.PZ_TortugaRazgovorVKauteSDevushkoy.win_condition.l1.location = "Tortuga";
				PChar.quest.PZ_TortugaRazgovorVKauteSDevushkoy.win_condition = "PZ_TortugaRazgovorVKauteSDevushkoy";
			}
		break;
		
		case "PZ_MaryRazgovorOBordeli_Good_1":
			dialog.text = "Si tu avais eu une demi-heure de retard, Charles, j'aurais fait exploser cette tanière immonde avec nos boulets de canon, ouais, hein ! As-tu trouvé ce que tu cherchais ? Est-ce elle, la sœur de Longway ? L'as-tu vue ?";
			link.l1 = "Chut, Mary, ne parle pas comme ça. Non, je n'ai pas eu l'occasion de rencontrer Chang Xing...";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Good_2";
			
			DeleteAttribute(pchar, "questTemp.MarySexBlock");
		break;
		
		case "PZ_MaryRazgovorOBordeli_Good_2":
			dialog.text = "Alors, qu'est-ce qui t'a pris autant de temps, bordel ?! Que faisais-tu là-bas ?";
			link.l1 = "Tu n'as rien à craindre. Dès que j'ai appris tout ce que je pouvais, j'ai quitté cet endroit, comme je te l'avais promis.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Good_3";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Good_3":
			dialog.text = "Crache le morceau, ouais, hein ?";
			link.l1 = "Le propriétaire n'est pas à Tortuga en ce moment. La demande pour ses services est faible ici, car elle emploie des dames bien éduquées en vêtements coûteux, et elles n'acceptent que l'or comme paiement...";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Good_4";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Good_4":
			dialog.text = "As-tu payé ceux-là aussi ?!";
			link.l1 = "Ils ne m'auraient même pas parlé autrement. Avec ce genre d'approche, pas étonnant qu'ils n'aient pas beaucoup de clients. La patronne a décidé de déplacer son commerce à Port-au-Prince, espérant attirer une clientèle plus aisée. Mais elle manque évidemment d'argent puisqu'elle a décidé de solliciter Marcus Tyrex pour un prêt...";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Good_5";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Good_5":
			dialog.text = "Est-ce qu'il la connaît ?";
			link.l1 = "Nous le découvrirons quand nous arriverons à La Vega. Et si nous nous dépêchons et arrêtons de perdre du temps avec des bavardages inutiles, nous attraperons cette femme asiatique, qui qu'elle soit.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Good_6";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Good_6":
			dialog.text = "Il était inutile d'aller dans ce bordel, Charles. Je suis sûr qu'on aurait pu découvrir tout cela à la taverne ou dans les rues si on avait essayé suffisamment fort, ouais, hein ?";
			link.l1 = "La prochaine fois, je t'emmènerai avec moi pour que tu ne remplisses pas ta jolie tête rousse de bêtises, hein ? Maintenant, passons aux choses sérieuses.";
			link.l1.go = "PZ_NaLaVega";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_1":
			dialog.text = "Oh, je vois que je suis un peu en retard, ouais, hein ! Eh bien, attends, vaurien...";
			link.l1 = "Mary, que diable fais-tu ici ?! Je t'ai dit de rester sur le bateau !";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_2";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_2":
			dialog.text = "Alors je ne t'empêcherais pas de t'amuser avec des putains ?! N'ose même pas le nier, Charles ! L'équipage t'a vu là-bas, ouais, hein ?! Comment as-tu pu ?!";
			link.l1 = " C'est ce que je pensais. Je suppose que j'aurais dû les emmener avec moi, pour qu'ils puissent voir ce que je faisais - ou plutôt, ce que je ne faisais pas - et ne pas en faire tout un plat... ";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_3";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_3":
			dialog.text = "Vous accusez nos garçons de mentir ? Après ce que vous avez fait vous-même, espèce de brute ?";
			link.l1 = "Je ne les accuse que d'une stupidité sans égale. Sans comprendre la situation, vous...";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_4";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_4":
			dialog.text = "Oh-oh, Charles, je ne pense pas que toi et tes putains auriez aimé ma compréhension de la situation si j'étais arrivé à ce trou à temps. Mais tu as de la chance - j'ai dû ramer ce putain de bateau tout seul...";
			link.l1 = "Ils disent que le travail physique ardu clarifie l'esprit des pensées inutiles. Mais tu en as encore plein, alors tu rames aussi en retour.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_5";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_5":
			dialog.text = "Je ne bouge pas, ouais, hein ?";
			link.l1 = "Mary, je ne vais pas avoir cette conversation ici devant les hommes de Levasseur. Calme-toi, regarde autour de toi, et juge par toi-même. Ce n'est ni le moment ni l'endroit.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_6";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_6":
			dialog.text = "Au diable avec toi. J'ai encore mes affaires dans la cabine... Mais ne pense pas que je vais ramer à nouveau, d'accord ! Il doit bien rester quelque chose de noble en toi !";
			link.l1 = "Je suis un scélérat et une brute, tu t'en souviens ? Je le prouverai sur le navire, mais je dois d'abord y arriver. Alors tes suppliques sont vaines.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_7";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_7":
			DialogExit();
			LAi_LocationFightDisable(loadedLocation, false);
			
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", Get_My_Cabin(), "rld", "loc1", "OpenTheDoors", -1);
			
			PChar.quest.PZ_TortugaRazgovorVKauteSDevushkoy.win_condition.l1 = "location";
			PChar.quest.PZ_TortugaRazgovorVKauteSDevushkoy.win_condition.l1.location = "Tortuga";
			PChar.quest.PZ_TortugaRazgovorVKauteSDevushkoy.win_condition = "PZ_TortugaRazgovorVKauteSDevushkoy";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_8":
			dialog.text = "Tu fais rire tout l'équipage, ouais, hein ?";
			link.l1 = "Eh bien, peut-être à toi aussi. Ils n'ont pas vu un spectacle comme ça depuis longtemps. Maintenant que ton humeur s'est un peu calmée, laisse-moi te raconter ce qui s'est passé.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_9";
			
			DeleteAttribute(pchar, "questTemp.MarySexBlock");
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_9":
			dialog.text = "Charles, j'ai tout entendu maintenant. J'ai juste une question : n'étais-je pas assez bien pour toi ? Me manque-t-il quelque chose ?";
			link.l1 = "C'est impoli, mais je vais répondre par une question : t'ai-je déjà donné une bonne raison de ne pas me faire confiance ? Hein ? Je ne me souviens pas d'une telle chose. Alors respire un coup et écoute-moi. Je n'ai pas pu découvrir grand-chose sur Joep van der Vink, sauf qu'il était allé dans un bordel. Pas celui près du 'Corbeau Chantant', mais un autre près du quai. Je ne le connaissais pas avant... contrairement, apparemment, à nos marins, qui t'ont mis au courant. Bien qu'ils n'auraient pas été autorisés à y aller...";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_10";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_10":
			dialog.text = "Quel genre de bordel n'accepte pas les marins, ouais, hein ?";
			link.l1 = "Un bordel où travaillent des dames vêtues de soie qui ont plus que de l'air dans la tête. Et leurs services sont payés exclusivement en doublons d'or. Ce n'est pas le caprice de n'importe qui, mais l'ordre de leur mystérieuse maîtresse, Belle Etoile.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_11";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_11":
			dialog.text = "Mystérieux, ouais, hein ?";
			link.l1 = "Ce n'est pas seulement ça. Elle est asiatique.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_12";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_12":
			dialog.text = "Asiatique ? La patronne du bordel à Tortuga ?";
			link.l1 = "Ça pourrait être Chang Xing. C'est pourquoi j'y suis allé - je voulais la voir de mes propres yeux. C'est tout.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_13";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_13":
			dialog.text = "Comment est-elle ?";
			link.l1 = "Je n'en ai aucune idée. Elle n'était pas là, alors j'ai dû discuter avec une autre... étoile.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_14";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_14":
			dialog.text = "Elle était asiatique aussi, ouais, hein ?";
			link.l1 = "Non, elle était blanche. Elle m'a dit que Belle Etoile n'allait pas très bien ces derniers temps, alors elle a décidé de déménager à Port-au-Prince. Cela a du sens, car les gens là-bas seraient plus riches. La madame doit être à court d'argent puisqu'elle a besoin d'un prêt pour ouvrir un commerce à Espanola, qu'elle a l'intention de prendre de Tyrex. Donc, si nous nous dépêchons à La Vega, nous pouvons l'intercepter avant que Marcus ne la rencontre.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_15";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_15":
			dialog.text = "Je m'en fiche pas mal d'elle, de Marcus ou de qui que ce soit d'autre, ouais, hein ? Charles, dis-moi juste une chose - as-tu été avec une des filles de son bordel ?";
			link.l1 = "Je n'ai pas besoin de ça, Mary. Je t'ai, la meilleure fille du monde. Je ne comprends pas pourquoi tu ne réalises pas ça.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_16";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_16":
			dialog.text = "En fait, c'est vraiment facile de découvrir la vérité, ouais, hein ? Si tu n'as été avec personne, tu dois être plein d'énergie en ce moment. C'est ce qu'on va vérifier maintenant, ouais, hein !";
			link.l1 = "Mary, s'il te plaît...";
			link.l1.go = "exit";
			AddDialogExitQuest("cabin_sex_go");
			pchar.questTemp.PZ_MaryRazgovorOBordeli = true;
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_17":
			DeleteAttribute(pchar, "questTemp.PZ_MaryRazgovorOBordeli");
			if (CheckAttribute(pchar, "questTemp.PZ.EliteWhoreFucked"))
			{
				if (IsCharacterPerkOn(pchar, "Medic"))
				{
					notification("Excellent Health", "Medic");
					dialog.text = " (Excellente santé) Ugh... On dirait que tu ne mentais pas, Charles, ouais, hein...";
					link.l1 = "Je n'ai nul besoin de te tromper, ma chère...";
					link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_18";
				}
				else
				{
					notification("Perk check failed", "Medic");
					dialog.text = "Charles, es-tu... es-tu sérieux?! Qu'était-ce que ça?";
					link.l1 = "Oh, cette chaleur ne me fait aucun bien. Ahem.";
					link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_19";
				}
			}
			else
			{
				dialog.text = "Ugh... Il semble que tu ne mentais pas, Charles, ouais, hein...";
				link.l1 = "Je n'ai pas besoin de vous tromper, mon cher...";
				link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_18";
			}
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_18":
			dialog.text = "Mais ce tour en chaloupe, je ne l'oublierai pas de sitôt !";
			link.l1 = "Ha !";
			link.l1.go = "PZ_NaLaVega";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_19":
			dialog.text = "Tu ne t'en es jamais plaint auparavant, n'est-ce pas ?";
			link.l1 = "Tu essaies de courir autour de cette foutue île...";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_20";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_20":
			dialog.text = "Et les bordels, ouais, hein ! As-tu vraiment...";
			link.l1 = "Mary, je suis désolé.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_21";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_21":
			dialog.text = "Quoi ?! Alors tu es...";
			link.l1 = "Je ne suis pas désolée pour ça. Merde. Je veux dire, je n'étais avec personne d'autre que toi, je te l'ai dit. Je n'arrivais juste pas à apaiser mon esprit, c'est tout. C'est dur de faire ça, tu sais, avec les canons de La Roche qui te regardent.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_22";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_22":
			dialog.text = "C'est une belle excuse, Charles. Bon, je vais te croire. Cette fois... Mais sache que je suis toujours furieuse contre toi, ouais !";
			link.l1 = "Je gagnerai ton pardon, je te le promets.";
			link.l1.go = "PZ_NaLaVega";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Good_1":
			dialog.text = "Eh bien, mon beau, dis-moi ce que tu as découvert. Cela valait-il la peine de risquer ma faveur ?";
			link.l1 = "Je ne peux vraiment pas dire si tu plaisantes ou si tu es sérieux. Ça a payé - même si je n'ai pas vu l'hôtesse de mes propres yeux. Elle est asiatique et son nom est Belle Etoile - une étoile merveilleuse. Pas son vrai nom, bien sûr...";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Good_2";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Good_2":
			dialog.text = "Et pour cela, tu devais aller dans un bordel ? Tu n'as pas pu découvrir ça à l'auberge ?";
			link.l1 = "Ils ne parlent pas vraiment de cet endroit en ville. Pourquoi ? C'est une bonne question. Vous pouvez demander à Belle Etoile elle-même - elle est partie pour Espanola.";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Good_3";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Good_3":
			dialog.text = "Ce n'était pas suffisant pour elle, Tortuga ?";
			link.l1 = "Le commerce, apparemment, ne va pas bien ici. Elle n'emploie pas de simples filles du port mais des dames richement vêtues et éduquées.";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Good_4";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Good_4":
			dialog.text = "Et pourquoi feraient-ils cela ?";
			link.l1 = "C'est une autre bonne question. Quoi qu'il en soit, notre petit oiseau a décidé de voler vers Port-au-Prince, le fief de de Mussac. Mais le prêt pour cette entreprise devait être obtenu de nul autre que Tyrex.";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Good_5";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Good_5":
			dialog.text = "Je veux que cette histoire se termine bientôt. Ne perdons pas de temps et mettons le cap sur La Vega.";
			link.l1 = "C'est ce que nous ferons.";
			link.l1.go = "PZ_NaLaVega";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Bad_1":
			dialog.text = "Tu es un homme brave, Charles, je te le concède. Te présenter ici si simplement, avec un visage si impassible, comme si de rien n'était.";
			link.l1 = "Je suppose qu'un des membres d'équipage a bavardé ? Sans aucun contexte, bien sûr. Parce que rien ne s'est vraiment passé - du moins pas ce que tu imagines.";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Bad_2";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Bad_2":
			dialog.text = "Je suis content que tu ne l'aies pas nié, Charles.";
			link.l1 = "Je voulais tout te dire, Helen.";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Bad_3";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Bad_3":
			dialog.text = "Ne le fais pas, Charles. Les détails ne m'intéressent pas beaucoup. Mais les raisons, oui. Dis-moi, y a-t-il quelque chose qui ne va pas chez moi ?";
			link.l1 = "Commençons par les raisons. J'ai découvert qu'il y a deux bordels à Tortuga. L'un est bien connu. L'autre - les gens en ont entendu parler, mais peu veulent en parler. Il appartient à une femme asiatique...";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Bad_4";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Bad_4":
			dialog.text = "Tu improvises au fur et à mesure ?";
			link.l1 = "Pourquoi diable ferais-je cela, Helen ?! Si tu ne me crois pas, ils te le confirmeront sur place !";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Bad_5";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Bad_5":
			dialog.text = "Premièrement, tu m'as dit de ne pas aller à terre, donc je ne peux pas y aller. Deuxièmement, pour qui diable me prends-tu ?! Je ne mettrai pas les pieds dans un endroit pareil ! Troisièmement... continue juste.";
			link.l1 = "Bien. J'ai décidé d'y aller pour voir Madame Étoile de mes propres yeux. C'était ma seule intention, bon sang !";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Bad_6";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Bad_6":
			dialog.text = "Je suppose. L'as-tu rencontrée ?";
			link.l1 = "Non. Elle est partie pour Espanola. Les choses ne vont pas bien pour elle ici, alors elle a décidé de tenter sa chance à Port-au-Prince. Là-bas, les dames en soie, bien éduquées, qui travaillent dans son établissement peuvent lui rapporter plus de profit qu'à Tortuga...";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Bad_7";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Bad_7":
			dialog.text = "Bien habillés et instruits ? Eh bien, ce que la vie peut te réserver. Mais tu devrais les aimer tels qu'ils sont.";
			link.l1 = "Hélène, arrête ça. Je n'ai rien fait pour mériter ta méfiance.";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Bad_8";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Bad_8":
			dialog.text = "Vrai. Si tu avais essayé de me tromper, tu ne serais pas si calme. Mais tu aurais dû me prévenir de tes projets, Charles.";
			link.l1 = "Tu as raison, chérie. Mais j'ai décidé de gagner du temps. Ma faute.";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Bad_9";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Bad_9":
			dialog.text = "D'accord. Que faisons-nous maintenant, traçons-nous une route pour Port-au-Prince ?";
			link.l1 = "La Vega. Ne sois pas surprise, Helen. Madame Belle Etoile ne va pas bien. Elle avait besoin d'un prêt pour déplacer son commerce à Port-au-Prince, alors elle a décidé d'emprunter à Marcus. Si nous nous dépêchons, nous pouvons l'attraper là-bas. Alors ne perdons pas une minute.";
			link.l1.go = "PZ_NaLaVega";
		break;
		
		case "PZ_NaLaVega":
			DialogExit();
			if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) 
			{
				AddLandQuestMark(characterFromId("Terrax"), "questmarkmain");
				QuestSetCurrentNode("Terrax", "PZ1");
			}
			else 
			{
				AddLandQuestMark(characterFromId("Vensan"), "questmarkmain");
				QuestSetCurrentNode("Vensan", "PZ1");
			}
			DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			Island_SetReloadEnableGlobal("Tortuga", true);
			bQuestDisableMapEnter = false;
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				sld = CharacterFromID("Mary");
				AddPassenger(pchar, sld, false);
				Return_MaryOfficer();
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				sld = CharacterFromID("Helena");
				AddPassenger(pchar, sld, false);
				Return_HelenaOfficer();
			}
			if (!CheckAttribute(pchar, "questTemp.PZ_PredupredilNashuDevushku")) AddQuestRecord("PZ", "31");
		break;
		
		case "PZ_KlemanLebren_7":
			dialog.text = "Je n'arrive pas à croire qu'un crétin comme toi et ta bande de vauriens nous aient vaincus !";
			link.l1 = "Toi...";
			link.l1.go = "PZ_KlemanLebren_8";
		break;
		
		case "PZ_KlemanLebren_8":
			dialog.text = "Oh, tu me reconnais ?";
			link.l1 = "Nous sommes-nous rencontrés ?";
			link.l1.go = "PZ_KlemanLebren_9";
		break;
		
		case "PZ_KlemanLebren_9":
			dialog.text = "Quoi ?! Tu te fous de ma gueule ?!";
			link.l1 = "Je ne peux pas me souvenir de tous les rustres que je rencontre. Tu ferais mieux de nous dire qui t’a envoyé pour nous tuer. Ou peut-être voulaient-ils simplement se débarrasser de toi ?";
			link.l1.go = "PZ_KlemanLebren_10";
		break;
		
		case "PZ_KlemanLebren_10":
			dialog.text = "Je ne dirai rien à quelqu'un comme toi. Tu te crois si foutrement supérieur ! Voyons si tu peux encore soutenir ça après notre petit répit ici.";
			link.l1 = "Quel dommage. Tu es répugnant, mais j'aurais pu te déposer sur une autre île. Maintenant, tout ce que je peux faire, c'est t'envoyer de l'autre côté.";
			link.l1.go = "PZ_KlemanLebren_11";
		break;
		
		case "PZ_KlemanLebren_11":
			pchar.questTemp.PZ.HeavyFrigateAbordage = true; // флаг - абордаж был
			
			DialogExit();
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "PZ_Tichingitu_11":
			dialog.text = "Vous m'avez appelé, Capitaine ?";
			link.l1 = "Oui, matelot. Fais le rapport des dégâts.";
			link.l1.go = "PZ_Tichingitu_12";
		break;
		
		case "PZ_Tichingitu_12":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "There's a violent storm. The ship is creaking and cracking; it's wobbling badly.";
			link.l1 = "Oui, j'ai remarqué. Tichingitu, mon ami. Moi et le "+sStr+" je vais aller à terre. Vous restez responsable. Commencez les réparations immédiatement - tant que la tempête ne s'apaise pas, cela ne sert à rien d'aller au chantier naval. De plus, nous ne resterons pas ici longtemps.";
			link.l1.go = "PZ_Tichingitu_13";
		break;
		
		case "PZ_Tichingitu_13":
			dialog.text = "Je vais faire en sorte que tout ait l'air mieux.";
			link.l1 = "Super, merci. Nous allons en ville sans aucun souci alors.";
			link.l1.go = "PZ_Tichingitu_14";
		break;
		
		case "PZ_Tichingitu_14":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "PZ_PoP_Rain_4", -1);
		break;
		
		case "PZ_Matros_1":
			dialog.text = "Monseigneur le Capitaine ? C'est un honneur. Mais vous appelez généralement Alonso dans des moments comme celui-ci. Tout va bien, si je puis me permettre ?";
			link.l1 = "Oui, tout va bien. Mais notre Alonso est plutôt du genre à détruire qu'à réparer quoi que ce soit. Dans tous les sens du terme. Dans quel état est le navire ?";
			link.l1.go = "PZ_Matros_2";
		break;
		
		case "PZ_Matros_2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Alonso vous dirait que c'est minable, même si nous ne descendons pas. Vous avez mentionné des réparations - devrions-nous les commencer ?";
			link.l1 = "Oui, fais ce que tu peux. Mais ne prévois pas de travail à long terme à grande échelle - nous lèverons l'ancre bientôt, juste après que j'aurai terminé mes affaires en ville. Moi et "+sStr+" ne sera pas là, donc en cas de problème, prends toutes les décisions toi-même. Écoute Alonso en tout.";
			link.l1.go = "PZ_Matros_3";
		break;
		
		case "PZ_Matros_3":
			dialog.text = "Comme vous commandez, Monseigneur le Capitaine.";
			link.l1 = "Repos.";
			link.l1.go = "PZ_Matros_4";
		break;
		
		case "PZ_Matros_4":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
			Island_SetReloadEnableGlobal("Hispaniola2", true);
			bQuestDisableMapEnter = false;
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "PZ_PoP_Rain_4", -1);
		break;
		
		case "PZ_AnriTibo_1":
			dialog.text = "Salutations, monsieur ! Bienvenue à Port-au-Prince.";
			link.l1 = "Et bonne journée à vous, monsieur. Qui êtes-vous, et à quoi dois-je cet accueil ? Je ne dirais pas que je suis d'humeur pour une longue conversation sous cette pluie et après une tempête.";
			link.l1.go = "PZ_AnriTibo_2";
			
			sld = GetCharacter(NPC_GenerateCharacter("PZ_PoP_ChangShin", "Mei_Shin", "woman", "towngirl2", 30, FRANCE, 0, false, "quest"));
			FantomMakeCoolFighter(sld, 30, 80, 80, "blade_41", "", "", 0);
			sld.name = "Чанг";
			sld.lastname = "Шин";
			ChangeCharacterAddressGroup(sld, "PortPax_town", "goto", "goto16");
			EquipCharacterByItem(sld, "blade_41");
			GiveItem2Character(sld, "cirass8");
			EquipCharacterByItem(sld, "cirass8");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload8_back", "none", "", "", "", -1);
		break;
		
		case "PZ_AnriTibo_2":
			dialog.text = "Oh, je ne prendrai pas beaucoup de votre temps, Monsieur de Maure.";
			link.l1 = "Vous ai-je déjà rencontré ?";
			link.l1.go = "PZ_AnriTibo_3";
		break;
		
		case "PZ_AnriTibo_3":
			dialog.text = "Oh, non, mais tout l'archipel sait qui vous êtes. Ah, où sont mes manières ! Henri Thibaut, à votre service. Je suis le messager de Sa Seigneurie, Monsieur de Mussac. Dès qu'il a aperçu votre navire, il m'a ordonné de vous offrir le plus chaleureux accueil possible, monsieur.";
			link.l1 = "Eh bien, cela explique beaucoup de choses. Enchanté de vous rencontrer, Monsieur Thibaut.";
			link.l1.go = "PZ_AnriTibo_4";
		break;
		
		case "PZ_AnriTibo_4":
			dialog.text = "Et le plaisir est mutuel, Monsieur de Maure ! Veuillez me suivre, je vous en prie. Il n'est pas convenable qu'un homme de votre stature et sa belle compagne soient confinés dans cette taverne puante. Sa Seigneurie vous a attribué une maison en ville et m'a chargé de vous assister de toutes les manières possibles. Je vous prie de ne pas oublier de transmettre ses meilleurs vœux à Son Excellence Poincy par la suite.";
			link.l1 = "En fait, ma mission est discrète. Vous savez, Monsieur Thibaut, je pense que...";
			link.l1.go = "PZ_AnriTibo_5";
		break;
		
		case "PZ_AnriTibo_5":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) StartInstantDialog("Helena", "PZ_HelenaPortPax1", "Quest\CompanionQuests\Longway.c");
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) StartInstantDialog("Mary", "PZ_MaryPortPax1", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_HelenaPortPax1":
			dialog.text = "Charles. Je te demande rarement quoi que ce soit, encore moins de te déranger, mais pouvons-nous profiter de leur offre ? J'en ai assez d'être trempé par la pluie. J'ai aussi des nausées et des vertiges.";
			link.l1 = "Heh-heh, es-tu sûr que c'est la pluie ?";
			link.l1.go = "PZ_HelenaPortPax2";
		break;
		
		case "PZ_HelenaPortPax2":
			dialog.text = "Mords ta langue, Charles ! Quoi qu'il en soit, je veux me reposer. Sur un grand lit et sans vagues.";
			link.l1 = "D'accord. On va se sécher, faire une pause, et ensuite se remettre au travail.";
			link.l1.go = "PZ_AnriTibo_6";
		break;
		
		case "PZ_MaryPortPax1":
			dialog.text = "Peut-on faire une pause dans cette maison ? Je ne me sens pas bien, et je suis aussi... fatiguée, Charles. Ouais, hein ?";
			link.l1 = "Mary, ma chère, je comprends, mais peut-être devrions-nous aller à la taverne. Tout cela sent mauvais, n'est-ce pas ?";
			link.l1.go = "PZ_MaryPortPax2";
		break;
		
		case "PZ_MaryPortPax2":
			dialog.text = "Que pourrait-il m'arriver ? Ce n'est même pas la Tortue.";
			link.l1 = "C'est ce qui me fait peur.";
			link.l1.go = "PZ_MaryPortPax3";
		break;
		
		case "PZ_MaryPortPax3":
			dialog.text = "S'il te plaît ? Si jamais, je mettrai en place une défense dans la pièce - tout comme... à l'époque, d'accord. Tu me connais mieux que quiconque, Charles, alors tu sais que je peux gérer ça.";
			link.l1 = "D'accord, d'accord. Espérons que cela ne sera pas comme la dernière fois.";
			link.l1.go = "PZ_AnriTibo_6";
		break;
		
		case "PZ_AnriTibo_6":
			StartInstantDialog("Tibo", "PZ_AnriTibo_7", "Quest\CompanionQuests\Longway.c");
			
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) Return_MaryOfficer();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) Return_HelenaOfficer();
		break;
		
		case "PZ_AnriTibo_7":
			dialog.text = "Je savais que vous changeriez d'avis, monsieur ! Concernant vos inquiétudes, je comprends parfaitement. Mais, vous voyez, Son Excellence Poincy et le gouverneur sont de vieux amis, et par conséquent vous êtes un invité bienvenu dans notre ville, Monsieur de Maure !";
			link.l1 = "Oh, eh bien... Eh bien, alors, emmène-nous à la maison alors.";
			link.l1.go = "PZ_AnriTibo_8";
		break;
		
		case "PZ_AnriTibo_8":
			dialog.text = "Certainement, monsieur ! Suivez-moi, s'il vous plaît.";
			link.l1 = "Merci.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_GoToTiboHouse");
		break;
		
		case "PZ_AnriTibo_9":
			dialog.text = "Monsieur, le gouverneur vous attend. Il vous a demandé de le rejoindre dès que possible - il aimerait vous parler en privé.";
			link.l1 = "Le sait-il déjà ?";
			link.l1.go = "PZ_AnriTibo_10";
		break;
		
		case "PZ_AnriTibo_10":
			pchar.questTemp.PZ.PortPaxMayorTalk = true; // флаг для разговора с губернатором
			
			dialog.text = "Bien sûr, il le sait ! C'est pour cela qu'il vous attend. Laissez votre bien-aimée dormir paisiblement pendant que vous allez voir monsieur de Mussac. Une tempête ne va pas arrêter le fameux Charles de Maure, n'est-ce pas ? Mais Sa Seigneurie, comme vous le comprenez, n'a pas beaucoup de temps à perdre entre ses rendez-vous...";
			link.l1 = "Eh bien, c'est vrai, Monsieur Thibaut.";
			link.l1.go = "PZ_AnriTibo_11";
			
			for (i=1; i<=2; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("PZ_PoP_Escort_"+i, "sold_fra_"+(rand(7)+1), "man", "man", sti(pchar.rank), FRANCE, -1, true, "soldier"));
				LAi_SetActorType(sld);
				ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload1");
			}
		break;
		
		case "PZ_AnriTibo_11":
			StartInstantDialog("PZ_PoP_Escort_1", "PZ_AnriTibo_12", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_AnriTibo_12":
			dialog.text = "Nous vous montrerons le chemin, Capitaine.";
			link.l1 = "Oh, alors j’ai même une escorte d'honneur... Eh bien, montre-moi le chemin.";
			link.l1.go = "PZ_AnriTibo_13";
		break;
		
		case "PZ_AnriTibo_13":
			DoQuestReloadToLocation("PortPax_town", "reload", "houseF1", "PZ_PoP_EscortToGuber");
		break;
		
		case "PZ_Longway_71":
			dialog.text = "Monseigneur le Capitaine !";
			link.l1 = "Longway ! Au navire ! Maintenant !";
			link.l1.go = "PZ_Longway_72";
		break;
		
		case "PZ_Longway_72":
			dialog.text = "Mais j'ai vu Chang Xing !";
			link.l1 = "Quoi ?! Où ? Quand ? Est-elle sur ton navire ?";
			link.l1.go = "PZ_Longway_73";
		break;
		
		case "PZ_Longway_73":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Non ! Ici dans la ville, Longway l'a vue de loin. Pas le temps de la rattraper - elle monte à bord d'un galion qui vient de lever l'ancre !";
			link.l1 = "Nous rattraperons le galion ! Mais dis-moi - as-tu vu "+sStr+" quelque part ?";
			link.l1.go = "PZ_Longway_74";
		break;
		
		case "PZ_Longway_74":
			dialog.text = "Non ! Est-ce qu'il s'est passé quelque chose ?";
			link.l1 = "Oui, il s'est passé quelque chose ! Elle est en danger ! As-tu vu le neveu de Levasseur ? Il s'appelle Henri Thibaut ! Un méchant jeune homme maigre avec de longs cheveux et une moustache drôle !";
			link.l1.go = "PZ_Longway_75";
		break;
		
		case "PZ_Longway_75":
			dialog.text = "(en mandarin) Vous n'avez pas besoin de parler de moustaches amusantes, Capitaine... (en français cassé) Je l'ai vu ! Lui et les mercenaires ont aussi embarqué sur le même galion.";
			link.l1 = "Poursuivons-le immédiatement !";
			link.l1.go = "PZ_Longway_76";
		break;
		
		case "PZ_Longway_76":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Votre navire est en piteux état, Monseigneur le Capitaine !";
			link.l1 = "Je m'en fiche ! "+sStr+"La vie de [[[VAR0]]] est en jeu !";
			link.l1.go = "PZ_Longway_77";
		break;
		
		case "PZ_Longway_77":
			if (CheckAttribute(pchar, "questTemp.PZ.LongwayMayfang"))
			{
				dialog.text = "Mon... 'Votre Meifeng' nous guidera à travers !";
				link.l1 = "Oh, elle le fera ! Dépêche-toi !";
				link.l1.go = "PZ_Longway_78";
			}
			else
			{
				dialog.text = "Ne nous jetez pas dans une attaque suicidaire. Utilisez le navire que vous m'avez fourni plus tôt !";
				link.l1 = "Bonne idée, Longway ! Dépêchons-nous !";
				link.l1.go = "PZ_Longway_78";
			}
		break;
		
		case "PZ_Longway_78":
			DialogExit();
			chrDisableReloadToLocation = false;
			Island_SetReloadEnableGlobal("Hispaniola2", false);
			LocatorReloadEnterDisable("PortPax_town", "gate_back", true);
			SetCurrentTime(15, 00);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			pchar.GenQuest.AbordageInStorm = true;	//Разрешить абордаж во время шторма
			SetLocationCapturedState("PortPax_town", false);

			LAi_LoginInCaptureTown(npchar, false);
			AddPassenger(pchar, npchar, false);
			Return_LongwayOfficer();
			
			if (GetCharacterIndex("Tichingitu") != -1)
			{
				sld = characterFromId("Tichingitu");
				AddPassenger(pchar, sld, false);
				Return_TichingituOfficer();
			}
			
			PChar.quest.PZ_PoP_Pogonya.win_condition.l1 = "location";
			PChar.quest.PZ_PoP_Pogonya.win_condition.l1.location = "Hispaniola2";
			PChar.quest.PZ_PoP_Pogonya.win_condition = "PZ_PoP_Pogonya";
			
			/*sld = GetCharacter(NPC_GenerateCharacter("PZ_ShipStasis", "panhandler_6", "man", "man", sti(pchar.rank), PIRATE, -1, false, "quest"));
			SetSPECIAL(sld, 1, 1, 1, 1, 1, 1, 1);
			SeaAI_SwapShipsAttributes(pchar, sld);
			if (CheckAttribute(pchar, "questTemp.PZ.LongwayMayfang"))	//Мейфенг
			{
				pchar.Ship.Type = GenerateShipExt(SHIP_MAYFANG, true, pchar);
				pchar.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS20;
				pchar.Ship.name = "Meifeng";
			}
			if (CheckAttribute(pchar, "questTemp.PZ.LongwayElCasador"))	//Эль Касадор
			{
				pchar.Ship.Type = GenerateShipExt(SHIP_ELCASADOR, true, pchar);
				pchar.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS32;
				pchar.Ship.name = "El Casador";
			}
			if (CheckAttribute(pchar, "questTemp.PZ.LongwayTorero"))	//Тореро
			{
				pchar.Ship.Type = GenerateShipExt(SHIP_POLACRE_QUEST, true, pchar);
				pchar.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS24;
				pchar.Ship.name = "Torero";
			}
			if (CheckAttribute(pchar, "questTemp.PZ.LongwaySchoonerW"))	//Военная шхуна
			{
				pchar.Ship.Type = GenerateShipExt(SHIP_SCHOONER_W, true, pchar);
				pchar.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS12;
				pchar.Ship.name = "Aztec";
			}
			if (CheckAttribute(pchar, "questTemp.PZ.LongwayBrig"))	//Бриг
			{
				pchar.Ship.Type = GenerateShipExt(SHIP_BRIG, true, pchar);
				pchar.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS16;
				pchar.Ship.name = "Aztec";
			}
			if (CheckAttribute(pchar, "questTemp.PZ.LongwayCorvette"))	//Корвет
			{
				pchar.Ship.Type = GenerateShipExt(SHIP_CORVETTE, true, pchar);
				pchar.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS16;
				pchar.Ship.name = "Aztec";
			}
			if (CheckAttribute(pchar, "questTemp.PZ.LongwayPolacre"))	//Полакр
			{
				pchar.Ship.Type = GenerateShipExt(SHIP_POLACRE, true, pchar);
				pchar.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS16;
				pchar.Ship.name = "Aztec";
			}
			if (CheckAttribute(pchar, "questTemp.PZ.LongwayXebek"))	//Шебека
			{
				pchar.Ship.Type = GenerateShipExt(SHIP_XebekVML, true, pchar);
				pchar.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS16;
				pchar.Ship.name = "Aztec";
			}
			if (CheckAttribute(pchar, "questTemp.PZ.LongwayBrigantine"))	//Бригантина
			{
				pchar.Ship.Type = GenerateShipExt(SHIP_BRIGANTINE, true, pchar);
				pchar.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS16;
				pchar.Ship.name = "Aztec";
			}
			SetBaseShipData(pchar);*/
			SeaAI_SwapShipsAttributes(pchar, CharacterFromID("PZ_ShipStasis"));
			AddCharacterGoodsSimple(pchar, GOOD_GRAPES, 300);
			AddCharacterGoodsSimple(pchar, GOOD_BOMBS, 200);
			AddCharacterGoodsSimple(pchar, GOOD_POWDER, 350);
			AddCharacterGoodsSimple(pchar, GOOD_FOOD, 150);
			AddCharacterGoodsSimple(pchar, GOOD_RUM, 50);
			AddCharacterGoodsSimple(pchar, GOOD_FOOD, 700);
			//SetCrewQuantityFull(pchar);
			pchar.ship.HP = sti(pchar.ship.HP) / 2;
			pchar.Ship.Crew.Quantity = sti(pchar.ship.Crew.Quantity) / 2;
			AddCrewMorale(Pchar, 100);
			ChangeCrewExp(pchar, "Sailors", 100);
			ChangeCrewExp(pchar, "Cannoners", 100);
			ChangeCrewExp(pchar, "Soldiers", 100);
			
			//Вражина
			sld = characterFromId("PZ_RobertMartin");
			sld.nation = PIRATE;
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				GiveItem2Character(sld, "blade_31");
				EquipCharacterByItem(sld, "blade_31");
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				GiveItem2Character(sld, "pirate_cutlass");
				EquipCharacterByItem(sld, "pirate_cutlass");
			}
			FantomMakeCoolSailor(sld, SHIP_GALEON_L, "Voltigeur", CANNON_TYPE_CANNON_LBS16, 50, 50, 50);
			sld.AlwaysEnemy = true;
			sld.AlwaysSandbankManeuver = true;
			sld.DontRansackCaptain = true;
			sld.ShipHideImmortal = 800;
			Group_FindOrCreateGroup("PZ_RM_Attack");
			Group_SetType("PZ_RM_Attack", "pirate");
			Group_AddCharacter("PZ_RM_Attack", "PZ_RobertMartin");
			Group_SetGroupCommander("PZ_RM_Attack", "PZ_RobertMartin");
			Group_SetTaskAttack("PZ_RM_Attack", PLAYER_GROUP);
			Group_SetAddress("PZ_RM_Attack", "Hispaniola2", "quest_ships", "Quest_ship_1");
			Ship_SetTaskAttack(SECONDARY_TASK, sti(sld.index), sti(pchar.index));
		break;
		
		case "PZ_RobertMartin_8":
			dialog.text = "Toi encore... Je savais que j'aurais dû refuser et laisser quelqu'un d'autre prendre ta fille.";
			link.l1 = "Où est-elle ?! Dis-le-moi ! Non... Tais-toi. Tu ne parleras que dans la cale, enchaîné ! Tu m'entends ?!";
			link.l1.go = "PZ_RobertMartin_9";
		break;
		
		case "PZ_RobertMartin_9":
			dialog.text = "... ";
			link.l1 = "Son épée. Si tu ne commences pas à chanter tout de suite, je te découpe en morceaux avec.";
			link.l1.go = "PZ_RobertMartin_10";
			/*RemoveAllCharacterItems(npchar, true);
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) GiveItem2Character(pchar, "blade_31");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) GiveItem2Character(pchar, "pirate_cutlass");*/
		break;
		
		case "PZ_RobertMartin_10":
			dialog.text = "Toi... tu as perdu la tête, bon sang !..";
			link.l1 = "Maintenant, tu vas voir mon côté désagréable...";
			link.l1.go = "PZ_RobertMartin_11";
		break;
		
		case "PZ_RobertMartin_11":
			DialogExit();
			LAi_ReloadBoarding();
		break;
		
		case "PZ_RobertMartin_13":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "C'est tout ?";
			link.l1 = "Je te demande encore une fois ! Où est "+sStr+"Où est la femme chinoise ?! Où est Henri Thibaut ?!";
			link.l1.go = "PZ_RobertMartin_14";
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "beatmarten_idle_1", "", 0.3);
		break;
		
		case "PZ_RobertMartin_14":
			dialog.text = "(crache du sang) Tu frappes comme une fille.";
			link.l1 = "Saleté ! Je vais te faire cracher chaque mot !";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_DoprosRobertMartin_Trum_6");
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "beatmarten_idle_1", "", 0.3);
		break;
		
		case "PZ_RobertMartin_16":
			dialog.text = "« Pathétique. Bien que... je vais le dire. Pourquoi pas, ha ha. Ils sont tous sur l'autre navire, en route pour la Tortue. Tu es trop tard. »";
			link.l1 = "Si même un cheveu tombe de sa tête...";
			link.l1.go = "PZ_RobertMartin_17";
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "beatmarten_idle_2", "", 0.3);
			locCameraFromToPos(-2.80, 7.72, 6.77, true, 1.00, 5.13, 7.23);
		break;
		
		case "PZ_RobertMartin_17":
			dialog.text = "Et à qui la faute ?! Tu as tué Edgardo Sotta ! Pour la première fois de sa vie, Levasseur voulait goûter une fille et il ne l’a pas eue tout de suite ! Première fois que notre équipage a échoué à exécuter son ordre direct ! Cet homme peut être aussi effrayant que le diable...";
			link.l1 = "Alors je serai plus effrayant que le diable lui-même et je te ferai vivre un petit enfer personnel si tu ne me dis pas ce que je veux savoir, tu m'entends ?!";
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) link.l1.go = "PZ_RobertMartin_Mary_1";
			else link.l1.go = "PZ_RobertMartin_Helena_1";
			//if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) link.l1.go = "PZ_RobertMartin_Helena_1";
		break;
		
		case "PZ_RobertMartin_Mary_1":
			dialog.text = "Je me fiche de tes peines - je suis un homme mort de toute façon, à en juger par tes yeux de fou. Je te reconnais quand même un certain mérite, de Maure.";
			link.l1 = "Qu'est-ce que tu racontes, bon sang ?";
			link.l1.go = "PZ_RobertMartin_Mary_2";
		break;
		
		case "PZ_RobertMartin_Mary_2":
			dialog.text = "Levasseur aime les blondes. Mais j'ai toujours préféré les rousses, tout comme toi, héhé... Quelle épicée tu as là !";
			link.l1 = "Tu as raison, tu ne survivras pas la journée...";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_DoprosRobertMartin_Trum_7");
		break;
		
		case "PZ_RobertMartin_Helena_1":
			dialog.text = "Je me fiche de ce que tu veux. Mais laisse-moi te dire ce que veut Levasseur - de jolies blondes, ha ha ha ha ha ha ha ha ha ! D'abord, il a sa...";
			link.l1 = "A-AH !";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_DoprosRobertMartin_Trum_7");
		break;
		
		case "PZ_RobertMartin_19":
			dialog.text = "Couiner et tabasser un homme sans défense - pathétique. C'est tout ce que tu sais faire. Tu as perdu, de Maure ! Veux-tu savoir quand tu as vraiment perdu, misérable crétin ?";
			link.l1 = "Éclaire-moi. Mais si je ne suis pas impressionné, tu perdras un doigt. Ou une oreille. Ou ces dents pourries de ta bouche puante. Ou peut-être autre chose. Le choix t'appartient...";
			link.l1.go = "PZ_RobertMartin_20";
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "beatmarten_idle_3", "", 0.3);
			//locCameraFromToPos(-1.75, 14.14, -0.31, true, 1.26, 11.00, -4.00);
			locCameraFromToPos(-2.80, 7.72, 6.77, true, 0.66, 5.00, 8.26);
		break;
		
		case "PZ_RobertMartin_20":
			dialog.text = "Hé hé, j'ai quelque chose que tu n'as pas. Tu crois que Levasseur ne savait pas ce que ce vieux renard de Poincy tramait contre lui ? François sait tout, tout ! Même les barons de la Fraternité n'osent pas le défier. Et toi, petit malin, tu l'as fait. Mais...";
			link.l1 = "Mais quoi?! Ne t'avise surtout pas de faire traîner ça !! Commence à parler, ou je vais commencer à te briser les doigts un par un !";
			link.l1.go = "PZ_RobertMartin_21";
		break;
		
		case "PZ_RobertMartin_21":
			dialog.text = "Ha-ha, brave Capitaine de Maure ! Mais d'accord. Moi, Henri, et la femme à la peau jaune avons décidé qu'il valait mieux te détruire ici. Et en rejeter la faute sur Tyrex, pour que les vieux fous de la Confrérie commencent une autre guerre entre eux ! Ou peut-être de Mussac - il a mis son nez là où il ne fallait pas... Tu sais, tout le monde se moquait de moi pour naviguer sur un galion, mais il a traversé la tempête avec aisance, contrairement à ta merde.";
			link.l1 = "Ça suffit ! Où Levasseur garde-t-il ses victimes ?";
			link.l1.go = "PZ_RobertMartin_22";
		break;
		
		case "PZ_RobertMartin_22":
			dialog.text = "Alors tu connais son endroit secret, le cachot ? Oh oui, c'est le vrai maître du cachot, ha-ha-ha ! Mais peux-tu vraiment le défier ? J'en doute. Tu veux vaincre la bête ? Alors deviens la bête toi-même. Voyons si tu peux me briser comme François brise ces filles. Comme il brisera bientôt la tienne...";
			/*if (!CheckAttribute(pchar, "questTemp.PZ_FlagShip"))
			{
				link.l1 = "Alo-o-on-s-o-o!!!";
				link.l1.go = "PZ_RobertMartin_23";
			}
			else
			{
				link.l1 = "... ";
				link.l1.go = "PZ_LongwayKaznDialog_1";
			}*/
			link.l1 = "Alo-o-on-s-o-o!!!";
			link.l1.go = "PZ_RobertMartin_23";
		break;
		
		case "PZ_RobertMartin_23":
			DialogExit();
			LAi_SetStayType(pchar);
			CharacterTurnByChr(pchar, CharacterFromID("PZ_RobertMartinPlennik"));
			LAi_Fade("PZ_AlonsoKazn", "");
		break;
		
		case "PZ_LongwayKaznDialog_1":
			DialogExit();
			LAi_SetStayType(pchar);
			CharacterTurnByChr(pchar, CharacterFromID("PZ_RobertMartinPlennik"));
			DoQuestCheckDelay("PZ_LongwayKazn_1", 1.0);
		break;
		
		case "PZ_LongwayKaznDialog_2":
			dialog.text = "";
			link.l1 = "Je t'ai dit de ne pas t'en mêler, bon sang !..";
			link.l1.go = "PZ_LongwayKaznDialog_3";
		break;
		
		case "PZ_LongwayKaznDialog_3":
			DialogExit();
			LAi_SetStayType(pchar);
			LAi_Fade("PZ_LongwayKazn_3", "");
		break;
		
		case "PZ_LongwayKaznDialog_4":
			dialog.text = "Permettez-moi, Monseigneur le Capitaine.";
			link.l1 = "Longway? Permettre quoi ?";
			link.l1.go = "PZ_LongwayKaznDialog_5";
		break;
		
		case "PZ_LongwayKaznDialog_5":
			dialog.text = "Les hommes blancs tourmentent le corps. Mon peuple sait qu'il faut d'abord tourmenter une âme misérable, rendre fou par une petite douleur constante. On ne peut pas juste prendre et tourmenter sans préparation. Cela nécessite toujours une approche spéciale. Ici, il faut... Lynchy.";
			link.l1 = "Lynchy ?";
			link.l1.go = "PZ_LongwayKaznDialog_6";
		break;
		
		case "PZ_LongwayKaznDialog_6":
			dialog.text = "Oui, Monseigneur le Capitaine. Mort par mille coupures.";
			link.l1 = "Es-tu fou ?! Tu as perdu la tête ?! De quelle mort parles-tu ?! Je dois d'abord le faire parler !";
			link.l1.go = "PZ_LongwayKaznDialog_7";
		break;
		
		case "PZ_LongwayKaznDialog_7":
			dialog.text = "Longway sait, Monseigneur le Capitaine. Il sait quoi faire. Ce salaud va tout me dire. Donne-moi du temps...";
			link.l1 = "Le temps ? Le temps ?! Très bien... Fais-le. Juste, je t'en prie, arrache-lui tout, absolument tout !";
			link.l1.go = "PZ_LongwayKaznDialog_8";
		break;
		
		case "PZ_LongwayKaznDialog_8":
			DialogExit();
			LAi_SetActorType(npchar);
			CharacterTurnByChr(npchar, CharacterFromID("PZ_RobertMartinPlennik"));
			LAi_SetStayType(pchar);
			CharacterTurnByChr(pchar, CharacterFromID("PZ_RobertMartinPlennik"));
			LAi_FadeToBlackStart();
			DoQuestCheckDelay("PZ_LongwayKazn_4", 1.5);
		break;
		
		case "PZ_LongwayKaznDialog_9":
			dialog.text = "Tuez-moi, tuez-moi juste, s'il vous plaît... Que voulez-vous de plus de moi?!";
			link.l1 = "Rien de plus. Ferme-la et meurs.";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_LongwayKazn_11");
		break;//
		
		case "PZ_LongwayKaznDialog_9_1":
			DialogExit();
			sld = CharacterFromID("PZ_RobertMartinPlennik")
			LAi_SetActorType(pchar);
			LAi_ActorAnimation(pchar, "Shot", "1", 1.5);
			DoQuestCheckDelay("PZ_LongwayKazn_9", 0.9);
		break;
		
		case "PZ_LongwayKaznDialog_10":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorAnimation(pchar, "Shot", "1", 1.5);
			DoQuestCheckDelay("PZ_LongwayKazn_9", 0.9);
		break;
		
		case "PZ_LongwayKaznDialog_11":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Tir précis, Monseigneur le Capitaine. Je vous avais dit que ça marcherait.";
			link.l1 = "Ouais. Bon travail. Alors, direction le cachot. Toutes voiles dehors ! Cap sur Tortuga. Et que Dieu vienne en aide à cette maudite ville si un seul cheveu tombe de "+sStr+" tête...";
			link.l1.go = "PZ_LongwayKaznDialog_12";
		break;
		
		case "PZ_LongwayKaznDialog_12":
			DialogExit();
			ResetSound();
			chrDisableReloadToLocation = false;
			EndQuestMovie();
			DeleteAttribute(pchar, "GenQuest.BlockDialogCamera");
			locCameraTarget(PChar);
			locCameraFollow();
			AddQuestRecord("PZ", "39");
			
			LAi_SetPlayerType(pchar);
			npchar.greeting = "Longway";
			Return_LongwayOfficer();
			
			bQuestDisableMapEnter = false;
			Island_SetReloadEnableGlobal("Hispaniola2", true);
			Island_SetReloadEnableLocal("Hispaniola2", "reload_2", true)
			Island_SetGotoEnableLocal("Hispaniola2", "reload_2", true);
			Island_SetReloadEnableLocal("Hispaniola2", "reload_3", true)
			Island_SetGotoEnableLocal("Hispaniola2", "reload_3", true);
			DeleteAttribute(pchar, "GenQuest.CannotWait");
			DeleteAttribute(pchar,"questTemp.TimeLock");
			LocatorReloadEnterDisable("LaVega_ExitTown", "reload1_back", false);
			LocatorReloadEnterDisable("PortPax_town", "gate_back", false);
			LAi_LocationDisableOfficersGen("PortPax_town", false);
			LAi_LocationFightDisable(&Locations[FindLocation("PortPax_town")], false);
			DeleteAttribute(pchar, "GenQuest.AbordageInStorm");
			
			PChar.quest.PZ_Etap6_Start.win_condition.l1 = "location";
			PChar.quest.PZ_Etap6_Start.win_condition.l1.location = "Tortuga";
			PChar.quest.PZ_Etap6_Start.win_condition = "PZ_Etap6_Start";
			locations[FindLocation("Shore58")].DisableEncounters = true;
			SetTimerCondition("PZ_Etap6_Opozdal", 0, 0, 7, false);
			DelMapQuestMarkCity("PortPax");
			AddMapQuestMarkShore("Shore58", true);
			pchar.questTemp.PZ_FlagMartinInfo = true;
			
			// Компаньон-заглушка входит в состав нашей экскадры
			sld = CharacterFromID("PZ_ShipStasis");
			SetCompanionIndex(pchar, -1, sti(sld.index));
			SetCharacterRemovable(sld, true);
			SetShipRemovable(sld, true);
			sld.Dialog.Filename = "Enc_Officer_dialog.c";
			sld.quest.meeting = true;
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(sld.id);
			sld.OfficerWantToGo.DontGo = true;
			sld.loyality = MAX_LOYALITY;
			sld.Dialog.CurrentNode = "hired";
			sld.Payment = true;
			sld.ship.HP = sti(sld.ship.HP) / 2;
			
			//
			makearef(arTmp, pchar.questTemp.PZ_PoP_More.ShipPos);
			QuestToSeaLogin_Prepare(stf(arTmp.x), stf(arTmp.z), arTmp.Island);
			DeleteAttribute(pchar, "questTemp.PZ_PoP_More.ShipPos");
			QuestToSeaLogin_Launch();
		break;
		
		case "PZ_AlonsoKaznDialog_1":
			dialog.text = "Dios mio... Je ne t'ai jamais vu ni entendu... comme ça, monseigneur le capitaine.";
			link.l1 = "Il est à toi, Alonso ! Vas-y, montre-moi ce que fait la Sainte Inquisition aux huguenots et à leurs sbires... Et je vais regarder... Ensuite, tu pourras faire ce que tu veux de lui.";
			link.l1.go = "PZ_AlonsoKaznDialog_2";
		break;
		
		case "PZ_AlonsoKaznDialog_2":
			dialog.text = "Ouais, ouais, senor Capitaine...";
			link.l1 = "";
			link.l1.go = "PZ_AlonsoKaznDialog_3";
		break;
		
		case "PZ_AlonsoKaznDialog_3":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, CharacterFromID("PZ_RobertMartinPlennik"), "PZ_AlonsoKazn_2", -1);
		break;
		
		case "PZ_AlonsoKaznDialog_4":
			dialog.text = "Ça ne prendra pas longtemps, señor Capitaine...";
			link.l1 = "Fais-le, pour l'amour du ciel !";
			link.l1.go = "PZ_AlonsoKaznDialog_5";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("PZ_RobertMartinPlennik"));
			//LAi_ActorAnimation(npchar, "Barman_idle", "1", 5);
		break;
		
		case "PZ_AlonsoKaznDialog_5":
			DialogExit();
			LAi_SetStayType(pchar);
			LAi_FadeToBlackStart();
			DoQuestCheckDelay("PZ_AlonsoKazn_3", 1.5);
		break;
		
		case "PZ_AlonsoKaznDialog_6":
			dialog.text = "Lève-toi, espèce de merde. Lève-toi, j'ai dit !";
			link.l1 = "Est-il mort ? Mort ?!";
			link.l1.go = "PZ_AlonsoKaznDialog_7";
			CharacterTurnByChr(npchar, CharacterFromID("PZ_RobertMartinPlennik"));
			CharacterTurnByChr(pchar, CharacterFromID("PZ_RobertMartinPlennik"));
		break;
		
		case "PZ_AlonsoKaznDialog_7":
			dialog.text = "On dirait bien, capitaine...";
			link.l1 = "Qu'est-ce que tu as fait, bon sang ?!";
			link.l1.go = "PZ_AlonsoKaznDialog_8";
			CharacterTurnByChr(npchar, pchar);
			CharacterTurnByChr(pchar, npchar);
		break;
		
		case "PZ_AlonsoKaznDialog_8":
			dialog.text = "Qui aurait cru que ce balourd se révélerait être un tel faible ! Il a même souillé ses culottes, ce déchet immonde ! Je serais damné, le feu était superflu...";
			link.l1 = "Toi... Eh bien, jetez-le par-dessus bord aux poissons. Cap sur Tortuga. Si besoin, je la démantèlerai brique par brique - d'abord La Roche, puis... Que Dieu m'aide si je ne la trouve pas vivante...";
			link.l1.go = "PZ_AlonsoKaznDialog_9";
		break;
		
		case "PZ_AlonsoKaznDialog_9":
			DialogExit();
			ResetSound();
			chrDisableReloadToLocation = false;
			EndQuestMovie();
			DeleteAttribute(pchar, "GenQuest.BlockDialogCamera");
			locCameraTarget(PChar);
			locCameraFollow();
			AddQuestRecord("PZ", "38");
			
			LAi_SetPlayerType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "", "", "", "", -1);
			npchar.lifeday = 0;
			npchar.location = "None";
			
			bQuestDisableMapEnter = false;
			Island_SetReloadEnableGlobal("Hispaniola2", true);
			Island_SetReloadEnableLocal("Hispaniola2", "reload_2", true)
			Island_SetGotoEnableLocal("Hispaniola2", "reload_2", true);
			Island_SetReloadEnableLocal("Hispaniola2", "reload_3", true)
			Island_SetGotoEnableLocal("Hispaniola2", "reload_3", true);
			DeleteAttribute(pchar, "GenQuest.CannotWait");
			DeleteAttribute(pchar,"questTemp.TimeLock");
			LocatorReloadEnterDisable("LaVega_ExitTown", "reload1_back", false);
			LocatorReloadEnterDisable("PortPax_town", "gate_back", false);
			LAi_LocationDisableOfficersGen("PortPax_town", false);
			LAi_LocationFightDisable(&Locations[FindLocation("PortPax_town")], false);
			DeleteAttribute(pchar, "GenQuest.AbordageInStorm");
			
			PChar.quest.PZ_Etap6_Start.win_condition.l1 = "location";
			PChar.quest.PZ_Etap6_Start.win_condition.l1.location = "Tortuga";
			PChar.quest.PZ_Etap6_Start.win_condition = "PZ_Etap6_Start";
			locations[FindLocation("Shore58")].DisableEncounters = true;
			SetTimerCondition("PZ_Etap6_Opozdal", 0, 0, 7, false);
			DelMapQuestMarkCity("PortPax");
			AddMapQuestMarkShore("Shore58", true);
			
			// Компаньон-заглушка входит в состав нашей экскадры
			sld = CharacterFromID("PZ_ShipStasis");
			SetCompanionIndex(pchar, -1, sti(sld.index));
			SetCharacterRemovable(sld, true);
			SetShipRemovable(sld, true);
			sld.Dialog.Filename = "Enc_Officer_dialog.c";
			sld.quest.meeting = true;
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(sld.id);
			sld.OfficerWantToGo.DontGo = true;
			sld.loyality = MAX_LOYALITY;
			sld.Dialog.CurrentNode = "hired";
			sld.Payment = true;
			sld.ship.HP = sti(sld.ship.HP) / 2;
			
			//
			makearef(arTmp, pchar.questTemp.PZ_PoP_More.ShipPos);
			QuestToSeaLogin_Prepare(stf(arTmp.x), stf(arTmp.z), arTmp.Island);
			DeleteAttribute(pchar, "questTemp.PZ_PoP_More.ShipPos");
			QuestToSeaLogin_Launch();
		break;
		
		case "PZ_Norman1":
			dialog.text = "Enfin. Ce trône est à moi maintenant. Sur ce rocher, je vais construire...";
			link.l1 = "Putain... Sérieusement ?";
			link.l1.go = "PZ_Norman2";
		break;
		
		case "PZ_Norman2":
			if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Marcus";
			else sTemp = "Shark";
			
			dialog.text = "... mon Église. Je suis maintenant le Pape de Rome. Ne jurez pas dans la Maison de Dieu !";
			link.l1 = "Et ici je pensais... Eh bien, Votre Sainteté, pourriez-vous avoir l'amabilité de dire à vos fidèles où se trouve le "+sTemp+"est maintenant ?";
			link.l1.go = "PZ_Norman3";
		break;
		
		case "PZ_Norman3":
			dialog.text = "Il est parti pour une quête sacrée. Une nouvelle croisade, si tu veux. Il va prendre l'argent des méchants et me l'apporter.";
			link.l1 = "À toi, c'est ça. A-t-il mentionné quand il serait de retour ?";
			link.l1.go = "PZ_Norman4";
		break;
		
		case "PZ_Norman4":
			NextDiag.TempNode = "PZ_NormanBlock";
			
			dialog.text = "Dans un mois. Peut-être un peu plus tard. J'attends son retour, avec le reste de notre troupeau.";
			link.l1 = "Donc il est vraiment en mer. Je ferais mieux de partir avant d'attraper ce que tu as.";
			link.l1.go = "Exit";
		break;
		
		case "PZ_NormanBlock":
			NextDiag.TempNode = "PZ_NormanBlock";
			
			dialog.text = "Je les purifierai tous dans les flammes sacrées...";
			link.l1 = "Votre tête aurait besoin d'un bon nettoyage...";
			link.l1.go = "Exit";
		break;
		
		case "PZ_HelenaIslaTesoro1":
			if (sti(pchar.questTemp.Saga.HelenRelation) >= 6)
			{
				// ох, какой же костыль, м-м-мать...
				sld = characterFromId("Mary");
				if (sld.location != "Pirates_townhall")
				{
					if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "with Marcus";
					else sTemp = "with Steve";
					
					dialog.text = "Charles ! Que puis-je faire pour vous ?";
					link.l1 = "Bonjour, Helen ! Je veux te parler "+sTemp+"Est-il à l'étage ? Ou est-il dans la taverne ?";
					link.l1.go = "PZ_HelenaIslaTesoroGood1";
				}
				else
				{
					if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Marcus";
					else sTemp = "Steve";
					
					dialog.text = "Charles ! Et... Ah, quelle agréable surprise. Que puis-je faire pour vous deux ?";
					link.l1 = "Bonjour, Hélène. Où est "+sTemp+" ?";
					link.l1.go = "PZ_HelenaIslaTesoroGoodMaryHere1";
				}
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Marcus";
				else sTemp = "Shark";
				
				dialog.text = TimeGreeting()+", Charles. Qu'est-ce qui t'amène ici ?";
				link.l1 = TimeGreeting()+", Helen. Je cherche la "+sTemp+" . Savez-vous où il est ?";
				link.l1.go = "PZ_HelenaIslaTesoroBad1";
			}
		break;
		
		case "PZ_HelenaIslaTesoroGood1":
			dialog.text = "Il est sorti, mais je crains qu'il ne soit parti pour longtemps - en mer, pour être précis.";
			link.l1 = "Merde. Quelque chose s'est-il passé ? A-t-il dit quand il reviendrait ?";
			link.l1.go = "PZ_HelenaIslaTesoroGood2";
		break;
		
		case "PZ_HelenaIslaTesoroGood2":
			dialog.text = "Il ne l'a pas fait, mais ce n'est rien de sérieux - il a une bonne piste, comme d'habitude. Il revient généralement dans un mois, deux au maximum. Je sais comment c'est, parfois le pont du navire me manque aussi...";
			link.l1 = "Tu peux toujours prendre la mer. Ce serait agréable de le faire ensemble un jour - toi sur le 'Rainbow', moi sur le...";
			link.l1.go = "PZ_HelenaIslaTesoroGood3";
		break;
		
		case "PZ_HelenaIslaTesoroGood3":
			NextDiag.TempNode = "PZ_HelenaIslaTesoroGoodBlock";
			
			dialog.text = "Ça se pourrait. Mais ta... petite amie pourrait ne pas apprécier. Et je ne veux pas être la troisième roue du carrosse.";
			link.l1 = "Hum, désolé, Helen, je ne voulais pas te vexer. Merci pour la conversation. À plus tard.";
			link.l1.go = "Exit";
		break;
		
		// Синистра, не забудь снять эту заглушку и вернуть дефолтную после этого этапа, плиз
		case "PZ_HelenaIslaTesoroGoodBlock":
			NextDiag.TempNode = "PZ_HelenaIslaTesoroGoodBlock";
			
			if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Marcus";
			else sTemp = "Steve";
			
			dialog.text = "Charles, vous êtes de retour. Y a-t-il autre chose avec laquelle je peux vous aider ?";
			link.l1 = "Non, merci, Hélène. Je voulais juste vérifier si "+sTemp+" s'est montré.";
			link.l1.go = "Exit";
		break;
		
		case "PZ_HelenaIslaTesoroBad1":
			if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Tyrex";
			else sTemp = "Steven";
			
			dialog.text = "Je serais surpris si tu venais me chercher. Quant à "+sTemp+", il est en mer.";
			link.l1 = "Oh, vraiment ? T’a-t-il dit quand il serait de retour ?";
			link.l1.go = "PZ_HelenaIslaTesoroBad2";
		break;
		
		case "PZ_HelenaIslaTesoroBad2":
			NextDiag.TempNode = "PZ_HelenaIslaTesoroBadBlock";
			
			dialog.text = "Apparemment, il est fatigué de gérer ce cloaque et doit se rappeler qu'il est toujours capitaine d'un navire. Pas la première fois. Il revient généralement dans un mois, peut-être un mois et demi.";
			link.l1 = "Merde, alors les barons ne restent pas toujours tranquilles comme ça ? Merci, Helen. Adieu.";
			link.l1.go = "Exit";
		break;
		
		// Синистра, не забудь снять эту заглушку и вернуть дефолтную после этого этапа, плиз
		case "PZ_HelenaIslaTesoroBadBlock":
			NextDiag.TempNode = "PZ_HelenaIslaTesoroBadBlock";
			
			if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Marcus";
			else sTemp = "Steven";
			
			dialog.text = ""+sTemp+"n'est toujours pas revenu, Charles";
			link.l1 = "Je vois, je vérifie juste.";
			link.l1.go = "Exit";
		break;
		
		case "PZ_HelenaIslaTesoroGoodMaryHere1":
			dialog.text = "Il est un homme libre, n'est-ce pas ? Il peut prendre la mer quand il veut.";
			link.l1 = "Bien sûr qu'il le peut. Alors, où est-il ?";
			link.l1.go = "PZ_HelenaIslaTesoroGoodMaryHere2";
		break;
		
		case "PZ_HelenaIslaTesoroGoodMaryHere2":
			NextDiag.TempNode = "PZ_HelenaIslaTesoroGoodMaryHereBlock";
			
			if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Marcus";
			else sTemp = "the Shark";
			
			dialog.text = "Mais Charles, s'il n'est pas sur l'île, alors il est parti piller les Espagnols. Et maintenant, si vous voulez bien m'excuser, j'ai beaucoup à faire. Passez de temps en temps - d'habitude, le "+sTemp+" revient dans environ un mois, parfois un peu plus tard.";
			link.l1 = "Bien, Hélène, merci. Nous resterons occupés.";
			link.l1.go = "Exit";
		break;
		
		// Синистра, не забудь снять эту заглушку и вернуть дефолтную после этого этапа, плиз
		case "PZ_HelenaIslaTesoroGoodMaryHereBlock":
			NextDiag.TempNode = "PZ_HelenaIslaTesoroGoodMaryHereBlock";
			
			dialog.text = "Je ne suis pas d'humeur en ce moment. Peut-être reviens une autre fois, Charles ?";
			link.l1 = "Bien sûr, Hélène. Désolé de te déranger. Prends soin de toi.";
			link.l1.go = "Exit";
		break;
		
		case "PZ_Longway_81":
			if (CheckAttribute(pchar, "questTemp.PZ_FlagMartinInfo"))
			{
				dialog.text = "Nous sommes en position, Monseigneur le Capitaine. Vous souvenez-vous du chemin ?";
				link.l1 = "Bien sûr, Longway. Espérons simplement que nous ne le perdrons pas dans ce maudit donjon...";
				link.l1.go = "PZ_Longway_FlagMartinInfo_1";		//Sinistra
			}
			else
			{
				dialog.text = "Nous sommes en position, Monseigneur le Capitaine. Avez-vous un plan ?";
				link.l1 = "Je suis encore en train de travailler dessus... Pourquoi, as-tu quelque chose en tête ?";
				link.l1.go = "PZ_Longway_NotMartinInfo_1";		//Rebbebion
			}
			DelLandQuestMark(npchar);
			LAi_SetCheckMinHP(npchar, 1, true, "");		//На 6 эпизод даём Лонгвею бессмертие
			
			LocatorReloadEnterDisable("Tortuga_town", "houseS4", false);
		break;
		
		case "PZ_Longway_NotMartinInfo_1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Eh bien, je suppose que si nous nous précipitons vers Chang Xing...";
			link.l1 = "Longway... Je comprends combien tu veux voir ta soeur, mais "+sStr+"est en danger de mort en ce moment, et ce n'est pas qu'une figure de style ! Vous devez comprendre que la sauver est la priorité absolue !";
			link.l1.go = "PZ_Longway_NotMartinInfo_2";
		break;
		
		case "PZ_Longway_NotMartinInfo_2":
			dialog.text = "Monseigneur le Capitaine, je doute que vous compreniez vraiment ce que j'ai traversé pendant ces dix années. Ce que je traverse en ce moment.";
			link.l1 = "Tu sais, d'une certaine manière, oui. Mon frère est retenu en prison. Et bien qu'ils ne lui aient pas encore fait de mal, à tout moment ils pourraient lui faire ce qu'ils veulent.";
			link.l1.go = "PZ_Longway_NotMartinInfo_3";
		break;
		
		case "PZ_Longway_NotMartinInfo_3":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Mais où irais-tu si c'était seulement une dame "+sStr+" qui avait besoin d'être secouru ?";
			if (CheckAttribute(pchar, "questTemp.FMQT.GiveDiamonds") && !CheckAttribute(pchar, "questTemp.FMQT_ObchistilSunduk"))
			{
				link.l1 = "Il y a un endroit... une personne... Mais ne t'en soucie pas, Longway - je dois m'en occuper moi-même.";
				link.l1.go = "PZ_GoMarceline1";
			}
			link.l2 = "En vérité, je ne sais même pas où aller. Si je me mets à fouiner partout sans précaution, j'attirerai l'attention, et alors "+sStr+"est définitivement terminé. Alors... Je ne sais tout simplement pas.";
			link.l2.go = "PZ_GoTogether1";
		break;
		
		case "PZ_GoMarceline1":
			dialog.text = "Quoi ? Pourquoi ?";
			link.l1 = "Ils ne te laisseront pas entrer là-bas - c'est la haute société, bon sang. Alors, j'irai seul. En attendant, tu te rends auprès de ta sœur. Je te rejoindrai dès que possible. Bonne chance, Longway !";
			link.l1.go = "PZ_GoMarceline2";
			RemovePassenger(pchar, npchar);
		break;
		
		case "PZ_GoMarceline2":
			dialog.text = "Oui ! Merci, Monseigneur le Capitaine. Et bonne chance à vous aussi !";
			link.l1 = "Oh, merci - J'en ai vraiment besoin aujourd'hui. Nous en avons tous besoin.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_MarcelineLongwayGo");
		break;
		
		case "PZ_GoTogether1":
			dialog.text = "Monseigneur le Capitaine...";
			link.l1 = "Peu importe. Allons voir ta sœur, Longway. Si nous nous séparons maintenant, nous sommes morts. Dépêchons-nous d'aller chez ta sœur et découvrons où se trouve le repaire de Levasseur. Ensuite, nous partirons de nouveau ensemble - j'ai besoin de toute l'aide possible en ce moment. J'espère que nous ne sommes pas trop tard.";
			link.l1.go = "PZ_GoTogether2";
		break;
		
		case "PZ_GoTogether2":
			dialog.text = "Nous ne serons pas en retard, Monseigneur le Capitaine. Ne tardons plus et ne perdons pas de temps à discuter. Allons chez Chang Xing !";
			link.l1 = "Tu as raison, dépêchons-nous.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_TogetherLongwayGo");
		break;
		
		case "PZ_FrenchSoldier1":
			dialog.text = "Où diable allez-vous ? Savez-vous seulement où mène cette porte ?";
			link.l1 = "Je sais parfaitement. J'y vais pour affaires, pas par curiosité oisive ou pour voler.";
			link.l1.go = "PZ_FrenchSoldier2";
		break;
		
		case "PZ_FrenchSoldier2":
			dialog.text = "Quelle affaire ? Madame Levasseur n'est pas disponible en ce moment. De plus, elle est une femme mariée - ce n'est pas correct que des gens traînent autour de chez elle.";
			link.l1 = "Elle est mariée, d'accord. Mais elle organise des réceptions de temps en temps, hein ? Y compris des privées. C'est l'un de ces moments. Elle m'attend, et je suis pressé.";
			link.l1.go = "PZ_FrenchSoldier3";
		break;
		
		case "PZ_FrenchSoldier3":
			dialog.text = "Elle m'aurait prévenu si c'était le cas.";
			link.l1 = "Je suis un invité un peu spécial - du genre qui n'a pas besoin d'annonces.";
			link.l1.go = "PZ_FrenchSoldier4";
		break;
		
		case "PZ_FrenchSoldier4":
			dialog.text = "Oui, le genre d'invité qui fera que Son Seigneurie ordonnera qu'on me fusille. Ou que la Dame elle-même me fera écorcher.";
			link.l1 = "J'ai déjà été l'invité de Madame Marceline. Je vous assure, il ne vous arrivera rien par la suite, soldat.";
			link.l1.go = "PZ_FrenchSoldier5";
		break;
		
		case "PZ_FrenchSoldier5":
			dialog.text = "Mais bien sûr, rester aveugle et laisser entrer tout le monde - c'est le travail de la garde de la ville.";
			link.l1 = "Je n'ai pas de temps pour ça, espèce de mule têtue...";
			link.l1.go = "Exit";
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddDialogExitQuest("MainHeroFightModeOn");
			AddDialogExitQuest("PZ_FrenchSoldierFight");
		break;
		
		case "PZ_Marceline1":
			dialog.text = "Toi...";
			// начинаем проверять результат прохождения "Почти как дома"
			switch (pchar.questTemp.FMQT.Marceline)
			{
				// поделили алмазы и "охладили трахание, углепластики" (с)
				case "Fuck":
					link.l1 = "Oh, oui, madame. Votre chevalier est ravi de vous revoir. Je vois que vous êtes surprise de me voir. La joie de cette rencontre... n'est-elle pas réciproque ?";
					link.l1.go = "PZ_MarcelineFuck1";
				break;
				
				// поделили алмазы, без трахания и углепластиков
				case "NoFuck":
					link.l1 = "Oui, je l'ai fait. Je réalise que je ne suis peut-être pas l'homme le plus beau ou le plus digne de cette île, comme vous l'avez mentionné lors de notre dernière rencontre, mais au moins vous savez que je suis un homme honnête. Écoutez-moi, madame - je ne prendrai pas beaucoup de votre... temps précieux.";
					link.l1.go = "PZ_MarcelineNoFuck1";
				break;
				
				// "сошлись вот где-то посередине" (с)
				case "Deception":
					link.l1 = "Tais-toi pour l'amour de Dieu, arrête de crier, madame. Je ne suis pas ici pour me venger de vous pour avoir trompé votre chevalier et vous être enfuie avec le trésor du dragon. Et je vous assure, si je voulais vous tuer, je vous tirerais simplement dessus et je filerais aussi vite que possible. Après tout, c'est Tortuga ! Mais je pense que vous savez déjà que cela serait indigne de moi.";
					link.l1.go = "PZ_MarcelineDeception1";
				break;
			}
		break;
		
		case "PZ_MarcelineFuck1":
			dialog.text = "Oh, non ! Je pensais juste que... Eh bien, ça n’a pas d’importance ! Vous voyez, des langues perfides répandent de vilaines rumeurs à mon sujet - une pauvre femme qui, même si elle le voulait, ne pourrait ni nuire à quiconque ni se défendre contre ses ennemis. De plus, cela fait si longtemps... Je pensais que vous veniez à moi avec de mauvaises intentions, et pas avec de bonnes. Je suis heureuse de me tromper. C’est dur de vivre quand on est entourée de malveillants.";
			link.l1 = "Comment pourrais-je ? Même si j'avais entendu quelque chose comme ça, je n'en croirais pas un mot. Mais tu as raison - je ne suis pas venu ici juste pour te voir. Bien que je suis content de l'avoir fait. Je sais que cela semblera inhabituel, mais... cette fois, ton chevalier a besoin de ton aide, madame.";
			link.l1.go = "PZ_Marceline2";
		break;
		
		case "PZ_MarcelineNoFuck1":
			dialog.text = "Et vous êtes bien plus sensible que je ne le pensais. Cependant, vous n'êtes pas sans défaut, Monsieur de Maure - je m'attendais à ce que vous soyez plus... raffiné. En fait... soit vous avez toujours été ainsi, soit l'Archipel vous a déjà corrompu. Vous devriez réapprendre à parler à une dame. Mais vous avez raison - vous êtes un homme honnête, bien que... simple.";
			link.l1 = "Et vous êtes une femme fière et vindicative. Vos yeux, vos mots et... vos actions le révèlent bien. Donc, si quelqu'un peut me comprendre, c'est bien vous. Tout comme je vous ai jadis comprise. Alors ne nous attardons plus sur le passé. Pouvez-vous m'aider, madame ?";
			link.l1.go = "PZ_Marceline2";
		break;
		
		case "PZ_MarcelineDeception1":
			dialog.text = "Oh... Je reconnais que je t'ai mal traité à l'époque. Mais seulement parce que je n'étais pas complètement sûre de toi, rien de plus ! Aurais-tu emporté tous les diamants loin de moi ? Ou amené mon mari ici en disant que tu avais appris de nos serviteurs que j'avais volé de lui, niant ta part dans cela ? Après tout, tout le monde cherche à obtenir ses faveurs, pas une pauvre femme comme moi... Maintenant, je réalise que je me suis trompée à ton sujet. Je te prie d'accepter mes excuses... mon chevalier.";
			link.l1 = "Je ne sais pas maintenant s'ils sont sincères ou non. Mais peu importe. J'ai besoin de votre aide, Madame Marceline. C'est une question de vie ou de mort. S'il vous plaît, ne refusez pas.";
			link.l1.go = "PZ_Marceline2";
		break;
		
		case "PZ_Marceline2":
			dialog.text = "Mon aide...? Je ne suis certainement pas la dernière femme de la ville, mais mon influence n'est pas aussi grande que vous le pensez tous. Je suis une reine qui règne, non pas qui gouverne. Mais je vous écouterai. Que peut faire ma humble personne pour vous ?";
			link.l1 = "Je réalise que c'est un sujet désagréable pour vous, madame, mais je cherche votre mari, et ce, dès que possible. En fait...";
			link.l1.go = "PZ_Marceline3";
		break;
		
		case "PZ_Marceline3":
			dialog.text = "C'est une plaisanterie ? Il n'est pas à la résidence pour le moment ? Alors il est en voyage d'affaires. Je ne peux pas vous aider, Monsieur de Maure.";
			link.l1 = "Tu as détourné le regard. Tu sais. Je sais aussi. Il faut juste que j'y aille. S'il te plaît, ne fais pas semblant que c'est la première fois que tu entends parler du cachot - tu es trop malin pour ne pas savoir.";
			link.l1.go = "PZ_Marceline4";
		break;
		
		case "PZ_Marceline4":
			dialog.text = "Oh, j'ai l'impression que cette conversation va me donner un cheveu gris de plus. Comme si je n'avais pas déjà assez de premières rides. Mais qu'est-ce que tu nous fais, François...";
			link.l1 = "Une mèche grise ne fera qu'ajouter à votre noblesse et n'enlèvera rien à votre beauté. Mais une bonne fille innocente est tombée entre les mains de votre mari. Et maintenant, elle risque de perdre sa beauté, sa santé, et même sa vie!...! Vous savez ce qui arrive à ceux qui sont piégés là-bas. S'il vous plaît, madame. Marceline... Aidez votre chevalier.";
			link.l1.go = "PZ_Marceline5";
		break;
		
		case "PZ_Marceline5":
			dialog.text = "Pas vraiment mon chevalier, n'est-ce pas ? Allez, je ne suis pas stupide. Mais... je vais t'aider, de Maure. Après tout, ça ne pouvait pas durer éternellement. Et un jour, cela aurait été rendu public. Ce qui est important pour moi maintenant, c'est de sortir à temps et de la bonne manière. Et... je ne peux pas te condamner à une souffrance éternelle causée par ce que mon ‘mari' fera à ton... connaissance.";
			link.l1 = "Je ne suis peut-être plus votre chevalier, madame. Mais vous n'avez jamais été ma dame dès le début. Cependant, je vous serai reconnaissant pour le reste de ma vie. Alors, où se trouve cet endroit ?";
			link.l1.go = "PZ_Marceline6";
		break;
		
		case "PZ_Marceline6":
			dialog.text = "Eh bien, je vais te croire sur parole, Charles. Dans les cachots de la ville. Il y a un grand tonneau dans une des impasses, et à côté commence un passage qui mène à la tanière de ce démon. Je n'ai pas regardé à l'intérieur. Je l'ai seulement suivi une fois, il y a longtemps. Et j'ai eu peur quand j'ai entendu les cris inhumains de ces pauvres créatures.";
			link.l1 = "Vous avez sauvé de nombreuses vies aujourd'hui, madame. Non seulement celle de mon cher, mais aussi toutes celles qui auraient pu tomber sous les coups de votre mari à l'avenir. Je vous remercie.";
			link.l1.go = "PZ_Marceline7";
		break;
		
		case "PZ_Marceline7":
			dialog.text = "Ah, laissez-moi avec ces paroles vides, monsieur. Vous m'avez demandé beaucoup. Et j'ai pris un grand risque. Essayez maintenant de faire de votre nouvelle quête dans l'antre du dragon un succès... mon chevalier.";
			link.l1 = "Je ferai de mon mieux. Adieu, Marceline.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_MarcelineOver");
		break;
		
		case "PZ_ElitaShluha_18":
			if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko") && !CheckAttribute(pchar, "questTemp.PZ_DevushkaMertva"))
			{
				dialog.text = "So, you're a bandit, monsieur...? We don't hire new girls like this; we all came here voluntarily. I'm going to have to ask you and your... accomplice to step out. And I'll make sure this girl gets treatment - otherwise, I'll report you to the authorities!";
				link.l1 = "Nous ne sommes pas des bandits. Mais cette fille est à la hauteur de n'importe lequel d'entre eux. Elle ne porte pas une lame pour faire joli. Elle est simplement blessée. Cet homme est un ami à moi et aussi le frère de votre maîtresse. Alors, laissez-nous la voir.";
				link.l1.go = "PZ_ElitaShluha_WithLongwayAndGirl1";
			}
			else
			{
				dialog.text = "Ravi de vous revoir, monsieur ! Mais vous savez que nous n'acceptons pas les invités... de basse classe ici. Même s'ils sont recommandés et payés. Surtout les travailleurs à la peau jaune ou les esclaves nègres. J'ai bien peur que votre ami doive partir.";
				link.l1 = "Ne dis pas ça devant ta maîtresse. Elle a aussi la peau jaune. Et ce n'est pas un travailleur, mais son frère. Tu ne t'opposerais pas à des retrouvailles familiales, n'est-ce pas ?";
				link.l1.go = "PZ_ElitaShluha_WithLongway1";
			}
		break;
		
		case "PZ_ElitaShluha_18_1":
			if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko") && !CheckAttribute(pchar, "questTemp.PZ_DevushkaMertva"))
			{
				dialog.text = "It's getting worse by the hour. First the mad yellow laborer and now you. No, monsieur, we don't pay for the girls who are brought to us by force; they are all here of their own free will.";
				link.l1 = "J'ai sauvé cette fille, et elle ne travaillera jamais dans un endroit qui est indigne d'elle. Une ouvrière, dites-vous ?";
				link.l1.go = "PZ_ElitaShluha_AfterLevasseurWithGirl1";
			}
			else
			{
				dialog.text = "Oh monsieur, quel mauvais timing ! Nous n'acceptons plus de clients aujourd'hui - vous pouvez voir par vous-même ce qui s'est passé ici.";
				link.l1 = "C'est pour cela que je suis ici. C'était un homme à la peau jaune qui a organisé tout ça, n'est-ce pas ?";
				link.l1.go = "PZ_ElitaShluha_AfterLevasseurWithoutGirl1";
			}
		break;
		
		case "PZ_ElitaShluha_AfterLevasseurWithGirl1":
			dialog.text = "Oui, monsieur, un ouvrier ! Nous pouvions à peine comprendre ce qu'il disait ! Ce vaurien a fait irruption et a exigé de voir la dame. Il nous a assuré qu'il était son frère. Nous avons appelé des hommes, mais...";
			link.l1 = "Cela ne représente aucun obstacle pour lui. Que s'est-il passé ensuite ?";
			link.l1.go = "PZ_ElitaShluha_AfterLevasseurWithGirl2";
		break;
		
		case "PZ_ElitaShluha_AfterLevasseurWithGirl2":
			for (i = 1; i <= 4; i++)
			{
				sld = characterFromId("PZ_EliteBrothelMercenary" + i);
				sld.lifeday = 0;
			}
			
			dialog.text = "Il s'est avéré qu'il ne mentait pas. La dame est sortie vers nous et l'a reconnu. En fait, ils sont toujours en train de discuter dans son luxueux domaine.";
			link.l1 = "Qui sait ce qu'il a en tête, pourtant. Nous y allons - nous la sauverons si nous devons. Ne fais pas de remous - cela détruirait la réputation de l'endroit.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_EliteBrothelCreateChangShin");
		break;
		
		case "PZ_ElitaShluha_AfterLevasseurWithoutGirl1":
			dialog.text = "C'est exact, monsieur. Il a dit qu'il était le frère de la dame.";
			link.l1 = "Et tu ne l'as pas laissé entrer...";
			link.l1.go = "PZ_ElitaShluha_AfterLevasseurWithoutGirl2";
		break;
		
		case "PZ_ElitaShluha_AfterLevasseurWithoutGirl2":
			dialog.text = "Bien sûr que non ! La dame est vêtue de manière exquise et parle sans accent, contrairement à cet ouvrier. Nous avons essayé de le chasser, et il a mis à terre tous les gardes, peux-tu imaginer ?!";
			link.l1 = "Je peux facilement imaginer. Et où est-il maintenant ?";
			link.l1.go = "PZ_ElitaShluha_AfterLevasseurWithoutGirl3";
		break;
		
		case "PZ_ElitaShluha_AfterLevasseurWithoutGirl3":
			for (i = 1; i <= 4; i++)
			{
				sld = characterFromId("PZ_EliteBrothelMercenary" + i);
				sld.lifeday = 0;
			}
			
			dialog.text = "Ils continuent à parler de quelque chose, mais nous ne pouvons pas comprendre quoi - probablement dans leur propre langue.";
			link.l1 = "J'irai vers eux. Peut-être que votre dame a besoin d'aide. N'appelez pas les gardes - si cela devient public, plus personne ne viendra jamais frapper à votre porte.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_EliteBrothelCreateChangShin");
		break;
		
		case "PZ_ElitaShluha_WithLongway1":
			dialog.text = "Un frère ? La maîtresse est digne, ce qui est plus que je ne peux dire pour ce ‘frère’ à elle. Pas besoin de lui embrouiller l’esprit ou d’essayer de l’arnaquer avec ce manœuvre. Emmenez-le.";
			link.l1 = "Je t'ai dit qu'ils se sont perdus de vue il y a longtemps. Il est juste moins chanceux. Nous paierons l'établissement nous-mêmes pour notre temps. Avertis la maîtresse maintenant.";
			link.l1.go = "PZ_ElitaShluha_WithLongway2";
		break;
		
		case "PZ_ElitaShluha_WithLongway2":
			dialog.text = "Elle n'a rien à craindre avec toi. Et je n'aime pas ton insistance. Garçons ! Jetez ce travailleur dehors ! Et son maître égaré aussi !";
			link.l1 = "Merde ! Tant d'arrogance pour une courtisane !";
			link.l1.go = "Exit";
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddDialogExitQuest("MainHeroFightModeOn");
			AddDialogExitQuest("PZ_EliteBrothelFight");
		break;
		
		case "PZ_ElitaShluha_WithLongwayAndGirl1":
			dialog.text = "Pas question ! Laisser la maîtresse seule avec toute cette compagnie étrange que vous avez ? Seulement si vous y allez seul, monsieur. Et vos... amis attendront dehors - nous avons un établissement convenable ici.";
			link.l1 = "Pourquoi t'inquiètes-tu pour elle ? Tout le monde sait qu'elle est l'une des meilleures bretteuses de Tortuga. Et mes amis sont plus décents que la plupart des gens de cette ville.";
			link.l1.go = "PZ_ElitaShluha_WithLongwayAndGirl2";
		break;
		
		case "PZ_ElitaShluha_WithLongwayAndGirl2":
			dialog.text = "Garçons ! Il y a un bandit blessé et un sale ouvrier ici ! Ils veulent quelque chose de notre maîtresse ! Occupez-vous d'eux !";
			link.l1 = "Quelle dévotion, bon sang...";
			link.l1.go = "Exit";
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddDialogExitQuest("MainHeroFightModeOn");
			AddDialogExitQuest("PZ_EliteBrothelFight");
		break;
		
		case "PZ_ChangShin1":
			locCameraFromToPos(2.17, 2.32, 0.55, true, -0.92, -0.37, -4.09);
			sld = characterFromId("Longway");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "goto", "goto9", "PZ_LongwayTurnToChangShin", -1);
			
			// итак, снова проверка по результатам прохождения. Лонгвэй с нами, тян ещё в пыточной
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
			{
				dialog.text = "Je suppose que vous êtes Charles de Maure ? Et ceci... Oh.";
				link.l1 = "Et tu dois être Belle Etoile. Ou devrais-je dire Chang Xing ? Et oui, c'est ton frère. Il te cherche depuis plus d'une décennie. Lui et moi avons beaucoup, beaucoup de questions pour toi. Et pas beaucoup de temps.";
				link.l1.go = "PZ_ChangShin_WithLongway1";
			}
			// пришли с Лонгвэем и тян
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom") && CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko"))
			{
				dialog.text = "Mon Dieu, tu as survécu. Tu as un sacré défenseur, même s'il est arrivé un peu en retard. Mieux que celui qui apparemment me considère comme son protecteur et qui se tient maintenant à tes côtés. Le ciel te favorise, ma chère fille.";
				link.l1 = "Je vois que tu sais. C'est encore mieux - pas besoin d'expliquer. Mais dis-moi, pourquoi souris-tu, Chang Xing ? Tu aimes voir les autres filles souffrir, n'est-ce pas ? Après tout, tu les vends.";
				link.l1.go = "PZ_ChangShin_WithLongwayAndGirl1";
			}
			// Лонгвэй с нами, тян на небесах
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom") && CheckAttribute(pchar, "questTemp.PZ_DevushkaMertva"))
			{
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
				dialog.text = "Charles de Maure, n'est-ce pas ? J'ai entendu dire que tu voulais me voir. Alors, qu'est-ce qui te tracasse ? Le service de notre établissement ne t'a pas plu la dernière fois que tu es venu ?";
				link.l1 = "Je viens juste d'un autre de vos établissements, Chang Xing. "+sStr+", mon amant, est mort. Et je sais que tu y as joué un rôle aussi.";
				link.l1.go = "PZ_ChangShin_GirlDied1";
			}
		break;
		
		case "PZ_ChangShin_WithLongway1":
			dialog.text = "Chang Xing... Cela fait longtemps que je n'ai pas entendu ce nom. Cela fait longtemps. Les Blancs... vous êtes toujours pressés. Que diriez-vous d'une réunion de famille tranquille ? Peu m'importe, cependant. J'ai cessé de compter sur les autres il y a des années. Pourquoi ne dis-tu rien, mon frère ? N'es-tu pas heureux de voir ta propre sœur ? Après tout, tu m'as cherché si inlassablement.";
			link.l1 = "Nous avons d'autres affaires urgentes et plus importantes à régler. Parle à ta sœur, Longway. Mais souviens-toi d'où nous devons encore aller. Nous devons nous presser. Et j'ai aussi des questions pour elle.";
			link.l1.go = "PZ_Longway_SisterDialog1";
		break;
		
		case "PZ_Longway_SisterDialog1":
			locCameraFromToPos(0.65, 2.59, -3.06, true, 0.23, 0.34, -5.21);
			
			sld = characterFromId("Longway");
			ChangeCharacterAddressGroup(sld, "Tortuga_brothelElite_room2", "goto", "goto8");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, characterFromId("PZ_ChangShin"));
			
			sld = characterFromId("PZ_ChangShin");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, characterFromId("Longway"));
			
			dialog.text = "(En mandarin) Longway, hein ? Eh bien, à part le nom, tu n'as pas beaucoup changé... Chang Tu.";
			link.l1 = "(En mandarin) Mais tu as beaucoup changé, soeur. Que s'est-il passé ? Ton regard était aussi chaleureux que le soleil de midi. Maintenant, il est froid et n'exprime rien d'autre que le mépris. Et ta voix ? J'aimais te faire rire et écouter ces cloches d'argent sonner... Maintenant elle est plus froide qu'un Goango en hiver. Et tu portes leurs vêtements. Et tu vends les femmes toi-même, bien que tu aies été enlevée par les Fermentelos autrefois.";
			link.l1.go = "PZ_Longway_SisterDialog2";
		break;
		
		case "PZ_Longway_SisterDialog2":
			dialog.text = "Tu viens me faire la leçon, alors que tu as travaillé pour Rodenburg, l'un des plus grands scélérats de l'archipel ? Tu penses que je ne savais pas pour toi ? J'ai toujours su. Ce n'est pas à toi de juger ce que je suis devenu et pourquoi, mon frère aîné égaré.";
			link.l1 = "Alors laisse-moi découvrir, Xing ! Et dis-moi. Si tu savais que j'étais dans l'Archipel, pourquoi n'as-tu pas voulu me rencontrer après toutes ces années ? J'ai consacré toute ma vie à te chercher...";
			link.l1.go = "PZ_Longway_SisterDialog3";
		break;
		
		case "PZ_Longway_SisterDialog3":
			dialog.text = "Parce que ni toi ni le Ciel ne m'avez protégée du plus terrible des destins. Alors j'ai réalisé que personne dans ce monde n'a besoin de qui que ce soit d'autre. Nous ne pouvons compter que sur nous-mêmes. Eh bien, je te le dirai si tu veux savoir. Mais je parlerai dans sa langue. Je suis sûre qu'il aimerait l'entendre aussi. Tu comprends le français, n'est-ce pas, Tu ?";
			link.l1 = "Oui, je parle cette langue.";
			link.l1.go = "PZ_Longway_SisterDialog4";
		break;
		
		case "PZ_Longway_SisterDialog4":
			dialog.text = "Ha ha ha, oh, Ciel ! Ton accent est terrible. Mais ce n'est pas ta faute - la prononciation et l'écriture françaises sont en effet difficiles.";
			link.l1 = "Tu ris différemment maintenant, sœur...";
			link.l1.go = "PZ_ChangShin_WithLongway3";
		break;
		
		/*case "PZ_Longway_SisterDialog5":
			Return_LongwayOfficer();
			
			StartInstantDialog("PZ_ChangShin", "PZ_ChangShin_WithLongway3", "Quest\CompanionQuests\Longway.c");
		break;*/
		
		case "PZ_ChangShin_WithLongway3":
			locCameraFromToPos(2.17, 2.32, 0.55, true, -0.92, -0.37, -4.09);
			sld = characterFromId("Longway");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "goto", "goto9", "PZ_LongwayTurnToChangShin", -1);
			dialog.text = "Mon cher frère veut savoir ce qui m'est arrivé au fil des ans. Je pense qu'il serait bon que tu écoutes aussi - comme tu l'as dit, tu as des questions. Alors ne t'inquiète pas - je vais tout te raconter en français.";
			link.l1 = "Dis-moi seulement l'essentiel - quand Longway m'a raconté sa vie, cela a pris plusieurs heures. Et je suis maintenant pressé.";
			link.l1.go = "PZ_ChangShin_WithLongway4";
		break;
		
		case "PZ_ChangShin_WithLongway4":
			dialog.text = "Tu seras patient. J'ai gardé tout cela pour moi pendant plus d'un an. Et si tu m'interromps, je ne répondrai à aucune de tes questions.";
			link.l1 = "Très bien... Alors continue.";
			link.l1.go = "PZ_ChangShin2";
		break;
		
		case "PZ_ChangShin_WithLongwayAndGirl1":
			dialog.text = "Où sont donc vos bonnes manières, Charles de Maure ? On m'avait dit que vous étiez un homme aux manières excellentes et un modèle de galant homme. Juste des rumeurs, mais en réalité... un flop ? C'est ce que je pensais. Et vous avez tort - je déteste tous les hommes et toutes les femmes également. En fait, je ne fais confiance à personne, je ne m'étonne de rien, je n'attends rien. Je me ferais un plaisir d'écraser vos testicules si je pouvais vous attraper. Mais entendre mon vrai nom après toutes ces années était un peu... rafraîchissant.";
			link.l1 = "Je suis un homme à femmes pour les dames, pas pour les sorcières comme toi. Et de toute façon, que pouvais-tu espérer, sachant que tu es impliquée dans le tourment de la personne qui m'est la plus chère ? Je me contiens à peine de ne pas te faire quelque chose, aussi. Et pas seulement pour lui. Longway est mon ami. Et tu es sa famille. Il te cherche depuis plus de dix ans. Et il mérite de te parler.";
			link.l1.go = "PZ_ChangShin_WithLongwayAndGirl2";
		break;
		
		case "PZ_ChangShin_WithLongwayAndGirl2":
			dialog.text = "Comme c'est sentimental. Et comme c'est triste que ça ne me touche pas. Mais tu ne vas pas t'en tirer aussi facilement maintenant, n'est-ce pas, Tu ? Pas pour t'avoir tué toi et vous tous pour être en retard une fois. Mais savoir... Je suppose que tu mérites de savoir. Tu m'as connu quand je n'étais pas comme ça, frère.";
			link.l1 = "Peu importe ce qui t'est arrivé... tu as toujours eu le choix, Chang Xing.";
			link.l1.go = "PZ_ChangShin_WithLongwayAndGirl3";
		break;
		
		case "PZ_ChangShin_WithLongwayAndGirl3":
			dialog.text = "Tu es encore jeune et tu ne sais pas comment fonctionne le monde, Charles de Maure. Il n'y a qu'un seul véritable choix dans la vie : vivre ou mourir. Je pense qu'il serait bon pour toi de tout savoir, aussi. Alors, je vais raconter mon histoire en français. Tu le parles, n'est-ce pas, toi ?";
			link.l1 = "Avec un accent. Mais il le comprend très bien. Vous pouvez commencer.";
			link.l1.go = "PZ_ChangShin2";
		break;
		
		case "PZ_ChangShin_GirlDied1":
			dialog.text = "Et où étais-tu pendant tout ce temps ? Espanola n'est qu'à un jour ou deux d'ici. Sa mort est aussi de ta faute. Et toi. Tu es en retard de plus d'une décennie. Nos sauveurs, nos protecteurs. Plus tôt une femme apprend à se défendre, mieux c'est. Certaines y arrivent à temps, d'autres pas. Et certains n'ont pas assez de cervelle pour y penser.";
			link.l1 = "Fais attention à chaque mot que tu diras ensuite. Je ne t’ai pas encore déchirée en morceaux juste pour mon ami, ton frère. Tu n’as aucune idée de ce qu’il a traversé pour toi.";
			link.l1.go = "PZ_ChangShin_GirlDied2";
		break;
		
		case "PZ_ChangShin_GirlDied2":
			dialog.text = "Je doute fortement qu'il ait traversé quelque chose ne serait-ce que vaguement similaire à ce que j'ai vécu.";
			link.l1 = "Alors, dis-nous.";
			link.l1.go = "PZ_ChangShin2";
		break;
		
		case "PZ_ChangShin2":
			dialog.text = "Eh bien, que puis-je dire, j'étais jeune, stupide et naïf à l'époque. Et intolérant. T'a-t-il déjà raconté comment j'ai été enlevé par Oliverio Fermentelos après qu'il ait tué mes parents et moi ?";
			link.l1 = "C'est ça.";
			link.l1.go = "PZ_ChangShin3";
		break;
		
		case "PZ_ChangShin3":
			dialog.text = "Il m'a courtisée et m'a avoué ses sentiments, mais je l'ai rejeté. Et c'est là qu'il a massacré notre famille et m'a volée. Et puis...";
			link.l1 = "Je peux deviner.";
			link.l1.go = "PZ_ChangShin4";
		break;
		
		case "PZ_ChangShin4":
			dialog.text = "Je voudrais que tu puisses. Puis il m'a encore avoué ses sentiments, passionné et en larmes, disant que c'était le seul moyen, car ma famille ne me laisserait jamais partir avec lui.";
			link.l1 = "Folie...";
			link.l1.go = "PZ_ChangShin5";
		break;
		
		case "PZ_ChangShin5":
			dialog.text = "Heh, un mot pour décrire toute ma vie depuis lors. Je l'ai rejeté encore une fois. Et ça a continué comme ça pendant un moment. Mais clairement, ça ne pouvait pas durer éternellement, parce que j'étais complètement à sa merci.";
			link.l1 = "Alors c'est arrivé ?";
			link.l1.go = "PZ_ChangShin6";
		break;
		
		case "PZ_ChangShin6":
			dialog.text = "Bien sûr. Il m'a prise de force, brutalement et sans pitié. Non pas que cela gêne les violeurs, mais n'avait-il pas auparavant pleuré en me confessant son grand amour ? Pfft ! L'amour avait apparemment disparu. Et tout cela se répétait chaque jour comme si c'était une routine. Au début, je criais et résistais, mais ensuite j'ai arrêté - à quoi bon de toute façon...";
			link.l1 = "Mais Fermentelos a eu ce qu'il méritait, et tu t'es retrouvé ici. Comment cela est-il arrivé ?";
			link.l1.go = "PZ_ChangShin7";
		break;
		
		case "PZ_ChangShin7":
			dialog.text = "Eh bien, assez vite il en a eu marre de moi. C'est drôle, n'est-ce pas ? Il a tué mes parents et ceux de Tu, m'a volée, m'a déshonorée régulièrement, pour finalement me jeter. Il est venu dans cet Archipel et m'a vendue à Levasseur comme esclave.";
			link.l1 = "Je ne souhaiterais pas cela à mon ennemi. Alors, comment as-tu survécu ? Et fini par être libre en premier lieu ? D'après ce que j'ai entendu, Levasseur ne laisse jamais sortir les femmes de sa cachette. Il s'en débarrasse toujours.";
			link.l1.go = "PZ_ChangShin8";
		break;
		
		case "PZ_ChangShin8":
			dialog.text = "C'est comme ça maintenant. Levasseur était différent alors. Non, il a toujours été un animal. Mais au début, il kidnappait occasionnellement de jeunes colons locaux, les violait dans son sous-sol, et s'en débarrassait presque immédiatement pour éviter de payer leur silence. Rarement les gardait-il plus de quelques jours à cette époque. Avec moi, par contre, c'était différent dès le début.";
			link.l1 = "Parce que tu étais un esclave, n'est-ce pas ?";
			link.l1.go = "PZ_ChangShin9";
		break;
		
		case "PZ_ChangShin9":
			dialog.text = "Exactement. Le principal désir de Levasseur n'était pas seulement le plaisir charnel. Et même pas un sentiment momentané de pouvoir sur ses victimes - après tout, il l'a sur toute l'île. Mais...";
			link.l1 = "... le plaisir de les voir se briser - leur volonté, leur apparence, leur voix, leur comportement.";
			link.l1.go = "PZ_ChangShin10";
		break;
		
		case "PZ_ChangShin10":
			dialog.text = "Oui. Je vois que vous avez fait vos devoirs, Capitaine. Mais à cet égard, je n'étais pas amusante pour lui - Fermentelos m'a amenée déjà brisée. Et Levasseur ne me trouvait pas belle - il n'aime pas les femmes asiatiques. Vous savez, pour une raison quelconque, cela m'a beaucoup affectée - je réalise que je suis attirante, mais je ne pense pas être vraiment belle. Et je ne le crois pas quand les gens me le disent. Même maintenant, quand je fais de l'exercice, porte des soies, et me parfume avec des essences fines. Pas que j'aie besoin de l'approbation de mon bourreau, mais...";
			link.l1 = "Eh bien, je vais répéter ma question - comment as-tu survécu ? Dès qu'il se lasse d'une femme, il s'en débarrasse. Avec toi, il s'est ennuyé dès le début, comme tu le dis.";
			link.l1.go = "PZ_ChangShin11";
		break;
		
		case "PZ_ChangShin11":
			dialog.text = "Je suppose que le fait que je l'aie ennuyé dès le début a eu un effet. Et le fait que j'étais une esclave - je ne pouvais aller nulle part ni dire quoi que ce soit. Les filles esclaves ont été traitées ainsi pendant des milliers d'années. Il a commencé à penser à comment rendre le temps qu'il passait avec moi 'amusant' pour lui.";
			link.l1 = "Je suppose que c'est ainsi que ses addictions sont nées, sous leur forme actuelle.";
			link.l1.go = "PZ_ChangShin12";
		break;
		
		case "PZ_ChangShin12":
			dialog.text = "Exactement. Au début, c'était des coups, des crachats et d'autres humiliations. Et des moqueries - à la fois sur mon apparence personnelle et sur mon origine, mon sang. Et puis sont venues les premières tortures - couteaux, pinces, une poêle... C'est pourquoi je porte des vêtements aussi fermés - tout mon corps est marqué, brûlé et mutilé. Et c'est pourquoi je n'ai plus jamais l'intention de me déshabiller devant un homme. Plus jamais. C'est alors que j'ai enfin compris ce que j'aurais dû comprendre lorsque Fermentelos m'a kidnappée.";
			link.l1 = "Qu'était-ce ?";
			link.l1.go = "PZ_ChangShin13";
		break;
		
		case "PZ_ChangShin13":
			dialog.text = "Que je ne devrais plus être une marionnette impuissante. Au contraire, je devrais contrôler ma vie. Pour moi, c'était le cas qu'une femme ne peut changer sa vie d'une manière ou d'une autre qu'en contrôlant les hommes autour d'elle.";
			link.l1 = "Je ne dirais pas que Levasseur peut être contrôlé.";
			link.l1.go = "PZ_ChangShin14";
		break;
		
		case "PZ_ChangShin14":
			dialog.text = "Et vous n'auriez pas tort. Mais il est possible de l'influencer avec précaution. Levasseur déteste autant l'obéissance totale dès le début que les arguments ou les supplications. Il en va de même pour la flatterie - apparemment, il réalisait à quel point il était vraiment un porc. Cela, je l'ai compris tout de suite, à un prix assez douloureux. Mais, quand il était satisfait de tout après une autre soirée de torture et de violence, il était possible de lui parler doucement. Je ne suis peut-être pas de noble naissance, mais je ne manque pas d'intelligence.";
			link.l1 = "Et de quoi avez-vous parlé ?";
			link.l1.go = "PZ_ChangShin15";
		break;
		
		case "PZ_ChangShin15":
			dialog.text = "J'ai éveillé son intérêt. J'ai suggéré des idées de torture, conseillé quels instruments de torture il vaut mieux éviter, et par lesquels commencer. Au début, il a tout essayé sur moi, bien sûr. Mais ensuite... il a commencé à me respecter, d'une manière tordue. Que se passe-t-il dans sa tête ? J'ai essayé de découvrir comment il en est arrivé là, mais il m'a de nouveau battu à moitié à mort. Puis il a fait venir un médecin personnel.";
			link.l1 = "C'est encore plus étrange et répugnant que ce que j'ai déjà entendu à son sujet.";
			link.l1.go = "PZ_ChangShin16";
		break;
		
		case "PZ_ChangShin16":
			dialog.text = "Il n'exigeait plus que je me donne à lui. Il m'appelait son élève. Mais il disait toujours qu'en tant que son projet, j'étais une déception totale. Je suppose que c'était pour me garder sur mes gardes. Alors il a commencé à m'enseigner l'escrime et les langues. Bien qu'il m'ait gardée au sous-sol, c'était moi, et non sa femme, qui recevait toutes les robes coûteuses.";
			link.l1 = "Un projet, en effet. On peut voir un parallèle évident avec la façon dont tu gères l'endroit.";
			link.l1.go = "PZ_ChangShin17";
		break;
		
		case "PZ_ChangShin17":
			dialog.text = "Je n'avais pas pensé à ça, hmmm. Et je n'aime pas ton parallèle, parce que je ne torture pas mes employées. Et je ne laisse pas mes clients le faire. Même si je déteste ces putains et envie leur beauté. Et je n'ai rien en commun avec ce porc, souviens-toi de ça.";
			link.l1 = "Alors, comment as-tu obtenu ce bordel ?";
			link.l1.go = "PZ_ChangShin18";
		break;
		
		case "PZ_ChangShin18":
			dialog.text = "De Levasseur, bien sûr. Pendant un certain temps, il m’a gardée chez lui. De temps en temps, il me demandait même des conseils sur comment briser telle ou telle fille. Après tout, j’étais spéciale pour lui, même s’il ne l’aurait jamais avoué. J’étais la première. J’ai tout vu.";
			link.l1 = "Qui a appris de qui, encore ?";
			link.l1.go = "PZ_ChangShin19";
		break;
		
		case "PZ_ChangShin19":
			dialog.text = "Je ne suis pas comme ça ! Je hais de toute mon âme ceux qui ont tout reçu sur un plateau d'argent ! Ce n'est pas juste ! Ce bordel était mon idée ! Mes travailleuses sont les filles de marchands, de fonctionnaires et de nobles qui sont parfois tombées entre les mains de Levasseur. Je lui ai demandé de me les donner. La torture et l'humiliation dans une cave secrète, c'est une chose. Mais les activités publiques d'une courtisane pour des gens comme elles, c'est tout autre !";
			link.l1 = "Je ne dirais pas que tes travailleuses ont l'air si humiliées, misérables et brisées.";
			link.l1.go = "PZ_ChangShin20";
		break;
		
		case "PZ_ChangShin20":
			dialog.text = "Parce qu'ils savent ce que Levasseur ou même moi leur ferions s'ils osaient ne serait-ce qu'émettre un son. Mais tu as raison en partie, bien sûr. Le vin, la nourriture, les soies, l'absence de torture quotidienne - beaucoup d'entre eux ont commencé à me voir comme un sauveur. Imbéciles ! Seuls quelques-uns ne sont pas heureux d'être ici. Certains d'entre eux, il les a donnés avec un cœur lourd. Et il riait, disant que je pouvais toujours lui en rendre en échange de résoudre les problèmes d'argent de mon établissement. Mais j'ai toujours dit non. Au moins de cette façon, ils rapporteraient de l'or au lieu de mourir dans la cave pour rien. Ce serait une sortie trop facile pour eux.";
			link.l1 = "Quel dommage que tout le monde ne se soit pas senti humilié, en changeant les cloîtres pires que la Sainte Inquisition pour une cage dorée comme ton bordel...";
			link.l1.go = "PZ_ChangShin21";
		break;
		
		case "PZ_ChangShin21":
			dialog.text = "Tu me juges ? Je ne voulais pas seulement survivre, mais bâtir un commerce prospère. Même si c'était à son insu, Levasseur m'était reconnaissant. Bien que je ne fusse plus esclave, il ne pouvait pas me laisser partir. J'étais encore forcée de travailler pour lui et d'aider ses sbires. Surtout son neveu maigrelet, qui bavait devant moi chaque fois qu'il me voyait. Mais n'osait ni m'attaquer ni me parler mal. Répugnant. Tu sais, même s'il m'appelait une déception, j'étais plus utile que Thibaut et Martene réunis. Je les accompagnais souvent sur ses ordres, comme je l'ai fait alors à Port-au-Prince.";
			link.l1 = "Tout cela explique beaucoup de choses...";
			link.l1.go = "PZ_ChangShin22";
		break;
		
		case "PZ_ChangShin22":
			dialog.text = "C'est ça. Écoutez. Je n'ai pas torturé votre amante. Tout comme je n'ai jamais torturé aucune fille avec ces mains, même si j'ai parfois conseillé Levasseur. Mais tant qu'on en parle...";
			link.l1 = "Quoi ?";
			link.l1.go = "PZ_ChangShin23";
		break;
		
		case "PZ_ChangShin23":
			dialog.text = "Comme vous le savez peut-être aussi, Levasseur exige parfois qu'on lui amène une certaine fille aperçue à Tortuga, puis qui a quitté l'île. Ou quelqu'un le surprendrait en lui amenant une inconnue pour gagner ses faveurs, comme ce fut le cas avec moi. Enlever votre bien-aimée était mon idée.";
			link.l1 = "Qu'as-tu dit...?";
			link.l1.go = "PZ_ChangShin24";
		break;
		
		case "PZ_ChangShin24":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "At first, we were considering capturing that blonde who used be so close to you. But since she is untouchable now, and because we have already promised him a girl, you redhead had to do.";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "I heard rumors about your gorgeous companion who never leaves your side. Considering Levausser's love for blondes, I had very little trouble selling him this idea.";
			dialog.text = "Sotta, son clébard, était censé lui ramener la mulâtresse, la femme de Lutter. Mais tu as tué Sotta, donc - pas de mulâtresse pour le gros bonhomme. Levasseur était furieux. Tout le monde a pris une raclée - Thibaut, Martene, même moi. Je ne sais pas qui m'a mis plus en colère : lui, parce qu'il m'a encore frappé, ou toi, qui en es la cause..."+sStr+"";
			link.l1 = "Donc ce n'est même pas à cause de lui... C'est toi qui as fait ça.";
			link.l1.go = "PZ_ChangShin25";
		break;
		
		case "PZ_ChangShin25":
			dialog.text = "Je n'espère même pas ton pardon, et de plus, je n'en ai pas besoin. Si tu veux du sang, tu auras du sang. Et tu le regretteras amèrement. Mais je ne refuserai pas de la compréhension. Cela pourrait m'être utile pour la première fois en dix longues années. Tout ce que j'ai jamais fait, c'était de faire de mon mieux pour sortir de Tortuga un jour. As-tu des questions pour moi, Charles de Maure ?";
			if (!CheckAttribute(pchar, "questTemp.PZ_FlagShinInfo") && !CheckAttribute(pchar, "questTemp.PZ_FlagMarselinaInfo") && !CheckAttribute(pchar, "questTemp.PZ_FlagMartinInfo"))
			{
				link.l1 = "Mais tu étais impliqué dans l'enlèvement. Et tu sais où Levasseur garde ses victimes. Dis-moi où c'est. Et si le pire n'est pas arrivé - je réfléchirai sérieusement à ne pas me venger de toi.";
				link.l1.go = "PZ_ChangShinDontKnow1";
			}
			else
			{
				link.l1 = "Eh bien, tout cela commence enfin à se concrétiser...";
				link.l1.go = "PZ_ChangShin26";
			}
		break;
		
		case "PZ_ChangShinDontKnow1":
			dialog.text = "Je le sais parce que j'y étais. Et si tu as l'impression que je suis mutuellement et malsainement attaché à lui - alors tu te trompes lourdement. Je serais ravi de voir quelqu'un embrocher ce porc.";
			link.l1 = "Je n'ai pas le temps, Chang Xing. Où est-ce ?";
			link.l1.go = "PZ_ChangShinDontKnow2";
		break;
		
		case "PZ_ChangShinDontKnow2":
			dialog.text = "Tu connais le cachot local sous les rues de la ville ? C'est là que tu vas. Dans une des impasses, il y a un grand tonneau de vin, et à côté commence un passage secret vers sa chambre de plaisir, comme il l'appelle parfois.";
			link.l1 = "Eh bien, tout cela commence enfin à s'assembler...";
			link.l1.go = "PZ_ChangShin26";
		break;
		
		case "PZ_ChangShin26":
			if (CheckAttribute(pchar, "questTemp.PZ_FlagArhiv") && CheckAttribute(pchar, "questTemp.PZ_FlagShip")) StartInstantDialog("Longway", "PZ_Longway_SisterDialog6", "Quest\CompanionQuests\Longway.c");
			else
			{
				dialog.text = "Bien pour toi. Maintenant, sors. Autant que je voulais parler après tant d'années, réaliser que tu connais tous mes secrets, sais ce qui m'a été fait - c'est écœurant. Te voir ne fait que me mettre en colère maintenant. Oh, et Tu reste avec moi.";
				link.l1 = "Pourquoi donc ?";
				link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet1";
			}
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet1":
			dialog.text = "Peut-être parce que je suis de sa famille ? Et parce que je vois comment il est avec toi - un pauvre bougre abattu qui n'a même pas eu le temps d'apprendre pleinement la langue et de commencer à parler correctement. Pourtant, il m'a dit que vous étiez amis. C'est clair comment tu l'as influencé. Au moins, je ferai de lui un homme.";
			link.l1 = "Et es-tu vraiment satisfait de toi-même ? En quoi vas-tu le transformer ? Une créature cruelle et amère qui marchande des vies ?";
			link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet2";
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet2":
			StartInstantDialog("Longway", "PZ_Longway_SisterDialog_Ubezhdaet3", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet3":
			if (CheckAttribute(pchar, "questTemp.PZ_FlagArhiv") || CheckAttribute(pchar, "questTemp.PZ_FlagShip"))
			{
				dialog.text = "Monseigneur le Capitaine, s'il vous plaît, arrêtez. Je vous demande de laisser ma sœur en paix. Et... je resterai avec elle.";
				link.l1 = "Toi... quoi ? Longway... mais pourquoi ? Ne vois-tu pas ce qu'elle est devenue ?";
				link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet4";
			}
			else
			{
				dialog.text = "Es-tu différent ? Tu as changé avec le temps. Pour le pire. Au début, tu étais poli et compréhensif. Mais ensuite, tu es devenu grossier, encore plus que Rodenburg. Et quand j'avais besoin d'un bon navire pour attraper Van der Vink, tu m'as donné une épave !";
				link.l1 = "Longway...";
				link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet8";
			}
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet4":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Une fois, je suis parti en mer et j'ai passé toutes ces années juste pour retrouver et sauver ma sœur. Et maintenant, elle est ici et en sécurité. Ma mission est accomplie. Et... Mon nom est Chang Tu. Longway est le nom que m'a donné le traître Van Merden, au cas où tu aurais oublié. Mais Chang Tu est un homme libre. Le long voyage de Chang Tu est enfin terminé.";
			link.l1 = "Elle te transformera en serviteur comme Rodenburg l'a fait autrefois. Elle te mettra la pression parce que tu es de la famille. Et prendras-tu si facilement le parti de celle qui m'a causé tant de souffrances et "+sStr+" tant de douleur ?";
			link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet5";
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet5":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "En ce moment, c'est toi qui fais pression sur Chang Tu. S'il te plaît, laisse-moi partir. Je suis très fatigué. Tu es un homme bon, Capitaine - le Ciel peut en témoigner. Mais tu n'es pas de ma famille. Elle l'est. Si je ne reste pas, alors toutes ces années auront été vaines. Maintenant, je serai son étoile guide et je raviverai son feu éteint - chaud et réconfortant, sans brûler tout ce qu'il touche.";
			if (CheckAttribute(pchar, "questTemp.PZ_LevasserPobezhden"))
			{
				link.l1 = "Hmm, tu as raison. Je pousse peut-être un peu trop pour l'instant. Eh bien, je t'ai toujours respecté. Je te souhaite des retrouvailles familiales tant attendues avec ta sœur. Mais je te préviens, tu ne trouveras pas la paix avec elle.";
				link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet6";
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko") && !CheckAttribute(pchar, "questTemp.PZ_DevushkaMertva")) 
				{
					pchar.questTemp.PZ_LongwayHochetMira = true;
					link.l1.go = "PZ_Longway_SisterDialog_ReactiaDevushek";
				}
				
			}
			else
			{
				link.l1 = "Tu ne peux pas me quitter maintenant ! J'ai encore besoin de sauver "+sStr+"de Levasseur ! Tu veux que j'y aille seule ? Aide-moi, Longway. Et ensuite, je te laisserai partir. Je te le promets.";
				link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet6";
			}
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet6":
			if (CheckAttribute(pchar, "questTemp.PZ_LevasserPobezhden"))
			{
				dialog.text = "Je peux m'en occuper. Vous n'avez plus à vous inquiéter pour moi. Merci.";
				link.l1 = "Il semble que ta sœur soit en colère que nous ayons décidé de nous séparer pacifiquement.";
			}
			else
			{
				dialog.text = "Vous le comprendrez, Monseigneur le Capitaine. Vous êtes l'homme le plus intelligent que j'aie jamais vu. Vous pouvez facilement vous occuper de ce ver qui n'est habitué qu'à tourmenter les femmes. Je vous en prie, ne me forcez pas. Ma soeur a tant de choses à me dire ! Et... je m'appelle Chang Tu.";
				link.l1 = "Vous réalisez qu'en me quittant maintenant, vous me trahissez ?! Surtout en restant avec elle - la femme qui a tout déclenché !";
			}
			link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet7";
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet7":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			if (CheckAttribute(pchar, "questTemp.PZ_LevasserPobezhden"))
			{
				dialog.text = "Ne craignez rien, Capitaine. Bien qu'elle parle de moi sans respect, je suis le frère aîné et son dernier parent masculin. Vous pouvez partir. Je ne la laisserai pas vous tuer. Adieu.";
				link.l1 = "Adieu... Chang Tu.";
				DeleteAttribute(pchar, "questTemp.PZ_LongwayRyadom");
				AddDialogExitQuest("PZ_BrothelTeleportVZal");	//Мирно разошлись
			}
			else
			{
				dialog.text = "J'ai dit tout ce que j'avais à dire. Adieu, Capitaine. Et bonne chance à vous. Chang Tu sera toujours un homme libre. N'oubliez pas cela.";
				link.l1 = "Et c'est comme ça que je suis récompensé après avoir tout abandonné et t'avoir aidé dans ta quête ? Après ce qu'ils lui font ?"+sStr+" maintenant ?! Tu es un traître, Chang Tu. Et tu mourras en tant que tel, vous deux, bande de salopards !";
				link.l1.go = "exit";
				LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
				AddDialogExitQuest("MainHeroFightModeOn");
				AddDialogExitQuest("PZ_ChangShinAndLongwayFightMe");
			}
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet8":
			dialog.text = "Mon nom est Chang Tu. Longway est mort. Tu l'as tué. Tu n'es plus mon Capitaine. Et maintenant, tu vas mourir. Ma famille trouvera enfin la paix, et notre étoile brillera intensément dans le ciel nocturne.";
			if (IsCharacterPerkOn(pchar, "Trustworthy") && GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) >= 85)
			{
				link.l1 = "(De confiance) (Leadership) Longway... Chang Tu. Arrête. Je sais que je n'ai pas été le capitaine idéal pour toi. Mais veux-tu vraiment me tuer si ardemment pour cela ? Après tout ce que nous avons traversé ? D'abord Rodenburg, maintenant la recherche de ta sœur.";
				link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet9";
				notification("Trustworthy", "Trustworthy");
				notification("Skill Check Passed", SKILL_LEADERSHIP);
			}
			else
			{
				link.l1 = "Longway, je suis ton Capitaine. Pas ta famille et pas une nourrice. Je donne des ordres, sans me demander si je t'ai insulté par inadvertance. Tu fais des demandes comme si nous étions de vieux époux, par Dieu...";
				link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet15";
				if (!IsCharacterPerkOn(pchar, "Trustworthy")) notification("Perk Check Failed", "Trustworthy");
				if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 85) notification("Skill Check Failed (85)", SKILL_LEADERSHIP);
			}
			link.l2 = "Ouais. Je le vois maintenant. Tu n'es qu'une pourriture égoïste qui ne pense qu'à soi... Longway. Tout comme ta sœur. Ma famille survivra aujourd'hui. La tienne - non. Va en enfer !";
			link.l2.go = "PZ_Longway_SisterDialog_Ubezhdaet8_1";
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet8_1":
			DialogExit();
			LAi_SetPlayerType(pchar);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_SetFightMode(pchar, true);
			DoQuestCheckDelay("PZ_ChangShinAndLongwayFightMe", 0.5);
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet9":
			dialog.text = "Si le choix est entre toi et ma famille - je choisis toujours la famille, même si c'est un choix difficile.";
			link.l1 = "Une famille qui n'a même pas levé le petit doigt pendant que tu la cherchais toutes ces années ? Oh, mais voilà que le bon moment est enfin arrivé ! Quant à moi, j'ai tout sacrifié pour t'aider. Toi, qui te tiens juste ici, c'est le résultat de cela. Enfer, je suis plus une famille pour toi qu'elle ne l'est, mon ami !";
			link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet10";
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet10":
			dialog.text = "Vous avez raison. Comme toujours, vous avez raison. Me pardonnerez-vous, Monseigneur le Capitaine ?";
			link.l1 = "Il n'y a rien à pardonner ! Tu as raison sur une chose - je n'ai pas toujours été le Capitaine que tu mérites. Je suppose que cela nous rend quittes maintenant. D'ailleurs, comment préfères-tu que je t'appelle à partir de maintenant ? Longway ? Ou est-ce Chang Tu ?";
			link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet11";
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet11":
			dialog.text = "Que ce soit Longway. Je suis déjà habitué à ce que tu t'adresses à moi ainsi.";
			link.l1 = "Alors, oublions toutes nos divergences, et bienvenue à bord de nouveau, Longway.";
			link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet12";
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet12":
			StartInstantDialog("PZ_ChangShin", "PZ_Longway_SisterDialog_Ubezhdaet13", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet13":
			locCameraFromToPos(2.17, 2.32, 0.55, true, -0.92, -0.37, -4.09);
			dialog.text = "Toi ! Qu'est-ce que tu dis ?! Pourquoi t'es-tu arrêté ?! Tue-le ! Pour lui, tu ne seras toujours qu'un simple ouvrier ! Ta famille, c'est moi et seulement moi !";
			link.l1 = "Elle est tellement en colère, n'est-ce pas, Longway ? Tu n'es plus de sa famille, Xing. Cela s'est terminé lorsque tu as appris l'arrivée de Longway dans l'Archipel et que tu as choisi de l'ignorer. Nous partons.";
			link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet14";
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet14":
			dialog.text = "Je suppose que je n'ai jamais eu de réelle chance d'extirper cette mentalité d'esclave chez lui. Je ne peux pas le sauver. Alors je vous tuerai tous les deux moi-même.";
			link.l1 = "Tu es celui qu'on ne peut pas sauver ici. Tu sais, j'étais trop compréhensif et indulgent avec toi. Mais c'est encore mieux ainsi. Je pense même que Longway a compris à quel point tu es une vipère. Il ne te pleurera pas trop.";
			link.l1.go = "exit";
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddDialogExitQuest("MainHeroFightModeOn");
			AddDialogExitQuest("PZ_ChangShinFightWithLongway");
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet15":
			dialog.text = "Les plaisanteries sont inappropriées maintenant ! Tu caches ta peur et ton échec derrière elles ! Ce qui ne fait que me convaincre davantage. Défends-toi, de Maure ! Car Chang Tu n'a aucune intention de t'épargner.";
			link.l1 = "Je suis désolé que cela se termine ainsi. Mais si c'est ce que tu veux, soit. Dans ce cas, tu n'auras aucune pitié de ma part non plus.";
			link.l1.go = "exit";
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddDialogExitQuest("MainHeroFightModeOn");
			AddDialogExitQuest("PZ_ChangShinAndLongwayFightMe");
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaDevushek":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) StartInstantDialog("Mary", "PZ_Longway_SisterDialog_ReactiaMary", "Quest\CompanionQuests\Longway.c");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) StartInstantDialog("Helena", "PZ_Longway_SisterDialog_ReactiaHelena", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaHelena":
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayHochetMira"))
			{
				dialog.text = "Charles, écoute...";
				link.l1 = "Hélène ?";
			}
			else
			{
				dialog.text = "Charles, Longway, arrêtez...";
				link.l1 = "Helen, tu ferais mieux de te mettre derrière moi maintenant. Je me sentirais plus en sécurité si tu le faisais, au cas où ils nous attaqueraient.";
			}
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaHelena2";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaHelena2":
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayHochetMira"))
			{
				dialog.text = "I'm so tired; I can hardly stand. I just want to get out of here. We're not going to drag Longway back to the ship if he doesn't want to come, are we? I'll be your navigator and first mate, my Captain. Hopefully, your most trusted and beloved too. Besides, he's got a point - we're not his family. She is, for better or worse.";
				link.l1 = "But what about her? She's the reason you were tortured; it was all her idea. And she's the one who kidnapped you.";
			}
			else
			{
				dialog.text = "Mais ils ne le feront pas, n'est-ce pas ? Partons simplement maintenant, c'est tout. Si c'est ce qu'il pense de nous après tout ce que nous avons fait pour lui, cela ne sert à rien d'essayer de le faire changer d'avis. Les actes parlent plus fort que les mots. S'il veut rester avec sa sœur, qu'il le fasse.";
				link.l1 = "Helen, tu as tant souffert à cause d'elle...";
			}
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaHelena3";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaHelena3":
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayHochetMira"))
			{
				dialog.text = "Laisse cette démone avec ses démons. Ils consumeront bientôt son âme. Et les nôtres méritent un bon repos. Allons-y.";
				link.l1 = "Oui. Je suppose que nous devrions. Partons d'ici, mon ange. Et toi - Longway, ou Chang Tu - adieu.";
			}
			else
			{
				dialog.text = "Mais je ne suis pas mort. Et le pire n'est pas arrivé. Je suis ici, avec toi, et c'est ce qui compte. Et Levasseur est mort. Sans lui, elle n'est rien. Son affaire perd de l'argent et coulera bientôt. Et ils couleront avec elle. Allons-y, mon capitaine. Il n'y a plus rien à faire ici.";
				link.l1 = "Je ne vais pas discuter, Helen.";
			}
			AddDialogExitQuest("PZ_BrothelTeleportVZal");		//Мирно разошлись
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaHelena4":
			StartInstantDialog("Helena", "PZ_Longway_SisterDialog_ReactiaHelena5", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaHelena5":
			dialog.text = "Où vas-tu ?";
			link.l1 = "Quoi, surpris que nous ne soyons pas pressés de répandre tes tripes et celles de ta sœur, Longway ? C'est la différence entre nous. Et tu penses toujours que je suis le méchant... Mais d'accord, regarde. Si tu veux me tuer, cela signifie que tu devras aussi tuer Helen. Elle est blessée, blessée. Veux-tu vraiment faire cela ?";
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaHelena6";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaHelena6":
			dialog.text = "Mm-hmm.";
			link.l1 = "Je vois le doute dans tes yeux, même si tu as beaucoup de rancunes contre moi. Mais prenons exemple sur Helen, d'accord ? Personne dans notre équipage n'est plus gentil ou plus clément qu'elle. Nous partons. Et s'il te reste un peu de bonté ou de bon sens, tu ne nous empêchera pas.";
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaHelena7";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaHelena7":
			dialog.text = "Soit. Je m'excuse. Mais tu n'es plus mon Capitaine.";
			link.l1 = "Je m'en remettrai d'une façon ou d'une autre. Je vous souhaite, à toi et à ta sœur, le meilleur, malgré ce qu'elle a fait. Adieu, Longway.";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_BrothelTeleportVZal");		//Мирно разошлись
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaMary":
			dialog.text = "Allez, Charles, il est temps d'écraser cette mutinerie.";
			link.l1 = "Dieu sait que je ne voulais pas faire ça... et je ne le veux toujours pas.";
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaMary2";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaMary2":
			dialog.text = "Tu ne le fais pas ? Charles, écoute-moi. Tu as fait tant de choses pour lui, et qu'as-tu reçu en retour ? Trahison et paroles méchantes, ouais, hein ? Vas-tu vraiment laisser passer ça ?";
			link.l1 = "Je ne veux pas verser le sang de Longway. Je n'ai pas oublié qu'autrefois nous étions amis.";
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaMary3";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaMary3":
			dialog.text = "Au diable des amis comme ça - ils sont pires que des ennemis, ouais, hein ! Charles, regarde-moi. Regarde ce qui m'est arrivé à cause de sa sœur, qui s'est moquée de moi, m'a insultée et humiliée en route vers cette fichue île !";
			link.l1 = "Mary, je comprends - tu es très, très en colère en ce moment...";
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaMary4";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaMary4":
			dialog.text = "Oh non, Charles, je ne suis pas juste en colère, non... Je suis furieuse ! Et pas seulement à cause de ce que ce misérable petit salaud t'a dit ! Regarde-moi encore, Charles - et imagine combien d'autres filles subiront cela si nous n'y mettons pas fin. Ici et maintenant.";
			link.l1 = "Ils ne blesseront plus personne. Levasseur est mort.";
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaMary5";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaMary5":
			dialog.text = "Charles, as-tu vraiment écouté les hérésies qu'elle débitait ? Elle est tout aussi responsable de ce qui s'est passé dans cette cave que ce porc puant. Regarde maintenant Longway - ou quel que soit son nom à présent. Vois à quelle vitesse elle a réussi à l'amener de son côté, ouais ! Qui sait quelles autres idées malades elle mettra dans la tête de ce traître ? Penses-tu que cette démone aura beaucoup de mal à le pousser sur le chemin de Levasseur ? Ne pense pas à ce qu'il est maintenant, Charles. Pense à quel genre de monstre il pourrait devenir dans un an... ou même un mois. Tu sais que j'ai raison, n'est-ce pas ?";
			link.l1 = "Autant que cela me coûte de l'admettre, je n'ai rien pour te contredire, Mary...";
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaMary6";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaMary6":
			StartInstantDialog("PZ_ChangShin", "PZ_Longway_SisterDialog_ReactiaMary7", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaMary7":
			dialog.text = "Ha-ha-ha ! Fascinant, quelle performance. Je n'avais pas ri aussi fort depuis longtemps. Et elle a du cran, je dois lui accorder ça.";
			link.l1 = "Ferme ta gueule, salope.";
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaMary8";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaMary8":
			dialog.text = "Amusant, n'est-ce pas, de Maure ? Je serais ravi de voir Tu te mettre à terre moi-même. Et ici, ta femme est aussi sanguinaire que moi. Très bien. Je ne resterai pas les bras croisés - je me suis entraîné avec Levasseur et quelques-uns des gros poissons de la Tortue. Voyons quel duo sortira vainqueur.";
			link.l1 = "Tu n'as pas eu un très bon professeur. Et tu as énervé Mary. Tu es fini. Même si je n'étais pas là, votre duo n'aurait aucune chance contre elle.";
			link.l1.go = "exit";
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddDialogExitQuest("MainHeroFightModeOn");
			AddDialogExitQuest("PZ_ChangShinAndLongwayFightMe");
		break;
		
		case "PZ_Longway_SisterDialog6":
			dialog.text = "Oui. Enfin. Puis-je parler à ma soeur de nouveau, Monseigneur le Capitaine ? Pas longtemps.";
			link.l1 = "Bien sûr. Fais vite - nous n'avons pas beaucoup de temps.";
			link.l1.go = "PZ_Longway_SisterDialog7";
		break;
		
		case "PZ_Longway_SisterDialog7":
			dialog.text = "Longway fais vite.";
			link.l1 = "Bien.";
			link.l1.go = "PZ_Longway_SisterDialog7_1";
		break;
		
		case "PZ_ChangShin26":
			StartInstantDialog("СhangShin", "PZ_Longway_SisterDialog7_1", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_Longway_SisterDialog7_1":
			locCameraFromToPos(0.65, 2.59, -3.06, true, 0.23, 0.34, -5.21);
			
			sld = characterFromId("Longway");
			ChangeCharacterAddressGroup(sld, "Tortuga_brothelElite_room2", "goto", "goto8");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, characterFromId("PZ_ChangShin"));
			
			sld = characterFromId("PZ_ChangShin");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, characterFromId("Longway"));
			
			dialog.text = "Et qu'est-ce que tu voulais me dire, mon frère ?";
			link.l1 = "Ce Longway est très déçu de toi, Xing.";
			link.l1.go = "PZ_Longway_SisterDialog8";
		break;
		
		case "PZ_Longway_SisterDialog8":
			dialog.text = "(En mandarin) Pourquoi ne parles-tu pas notre langue puisque tu voulais parler encore, Tu ? As-tu honte de lui ? Si j'étais toi, je serais plus gêné par ton accent.";
			link.l1 = "Non. Longway n'a plus de secrets pour Monseigneur le Capitaine. Plus maintenant.";
			link.l1.go = "PZ_Longway_SisterDialog9";
		break;
		
		case "PZ_Longway_SisterDialog9":
			dialog.text = "(en français) D'abord Rodenburg, maintenant de Maure. Il te faut toujours un ‘monsieur.’ Tu n'as rien accompli ici en plus d'une douzaine d'années. Tu n'arrives même pas à apprendre aucune de leurs langues. Et elles sont tellement plus simples que les nôtres ! Si quelqu'un est une déception, c'est bien toi.";
			link.l1 = "Mais je ne fais pas commerce des femmes. Je ne participe pas à leur enlèvement et torture.";
			link.l1.go = "PZ_Longway_SisterDialog10";
		break;
		
		case "PZ_Longway_SisterDialog10":
			dialog.text = "Es-tu sérieux ? Dois-je énumérer les choses que tu as faites pour Rodenburg ? Ce que j'ai fait serait un jeu d'enfant en comparaison.";
			link.l1 = "J'avais un but - te trouver. Mais tu ne voulais même pas me voir. Et quand je t'ai trouvée, j'ai découvert un monstre, pas l'étoile chaleureuse et guide qui illuminait autrefois mon chemin.";
			link.l1.go = "PZ_Longway_SisterDialog11";
		break;
		
		case "PZ_Longway_SisterDialog11":
			dialog.text = "Un monstre ? Eh bien, peut-être que tu as raison. Je ne suis plus la fille joyeuse que tu connaissais. Si j'étais restée ainsi, la vie m'aurait dévorée et recrachée. J'ai dû me forger mes propres dents. Mon étoile s'est éteinte depuis longtemps. Mais je suis toujours ta sœur, Tu.";
			link.l1 = "Non. Tu n'es plus ma soeur.";
			link.l1.go = "PZ_Longway_SisterDialog12";
		break;
		
		case "PZ_Longway_SisterDialog12":
			dialog.text = "Me laisser tomber si facilement après toutes ces années ? Heh... Et qui sait, peut-être que je serais toujours le même si tu étais rentré à temps pour tuer Fermentelos ce jour-là ?";
			link.l1 = "Tu as raison. C'est en partie ma faute aussi. C'est ma responsabilité. Et je vais y mettre fin. Je vais te libérer de ta misère. Mettre fin à cette existence misérable.";
			link.l1.go = "PZ_Longway_SisterDialog13";
		break;
		
		case "PZ_Longway_SisterDialog13":
			dialog.text = "Vas-tu vraiment tuer ta propre sœur, Chung Tu ? Pas que tu réussisses, mais le fait est...";
			link.l1 = "Tu n'es plus ma soeur. Xing est morte il y a dix ans. Et aujourd'hui est le jour où Chung Tu meurt enfin. À partir de maintenant et pour toujours, mon nom est... Longway.";
			link.l1.go = "Exit";
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddDialogExitQuest("MainHeroFightModeOn");
			AddDialogExitQuest("PZ_ChangShinFightWithLongway");
		break;
		
		case "PZ_Longway_FlagMartinInfo_1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "D'abord, nous sauvons Chang Xing.";
			link.l1 = "Quoi ?! Tu ne sembles pas comprendre, mon ami. Ta soeur n'est pas en danger immédiat, mais "+sStr+"est. Et dois-je te rappeler que Chang Xing est tout aussi coupable pour cela que Martene et Thibaut ?";
			link.l1.go = "PZ_Longway_FlagMartinInfo_2";
		break;
		
		case "PZ_Longway_FlagMartinInfo_2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Ce n'est pas vrai ! Elle est...";
			link.l1 = "As-tu la moindre idée de ce que Levasseur pourrait faire à "+sStr+" pendant que nous sommes ici à nous disputer ?";
			link.l1.go = "PZ_Longway_FlagMartinInfo_3";
		break;
		
		case "PZ_Longway_FlagMartinInfo_3":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Mais Chang Xing est tout ce qu'il me reste, Capitaine... Votre famille est encore intacte...";
			link.l1 = +sStr+" peut ne pas être ma femme, mais elle m'est aussi chère que ma propre famille.";
			link.l1.go = "PZ_Longway_FlagMartinInfo_4";
		break;
		
		case "PZ_Longway_FlagMartinInfo_4":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Chang Xing est ma dernière étoile guide, Capitaine. De plus, vous me devez pour avoir obtenu cette confession de Robert Marten.";
			if (CheckAttribute(pchar, "questTemp.PZ_FlagArhiv") && CheckAttribute(pchar, "questTemp.PZ_FlagShip"))
			{
				link.l1 = "Nous partirons à la recherche de ta sœur, je le promets. Mais Levasseur ne l'a pas touchée pendant tout ce temps."+sStr+" est en bien plus grand danger que Chang Xing. Aide-moi à la sauver d'abord, et je te devrai une fière chandelle.";
				link.l1.go = "PZ_Longway_FlagMartinInfo_VD1";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.PZ_FlagArhiv") || CheckAttribute(pchar, "questTemp.PZ_FlagShip"))
				{
					if (IsCharacterPerkOn(pchar, "Trustworthy") && GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) >= 85)
					{
						link.l1 = "(Digne de confiance) (Leadership) Nous irons chercher ta sœur, je te le promets. Mais Levasseur ne l'a pas touchée pendant tout ce temps."+sStr+"est en bien plus grand danger que Chang Xing. Aide-moi à la sauver d’abord, et je te devrai une grosse faveur.";
						link.l1.go = "PZ_Longway_FlagMartinInfo_VD1";
						notification("Trustworthy", "Trustworthy");
						notification("Skill Check Passed", SKILL_LEADERSHIP);
					}
					else
					{
						link.l1 = "Ecoute-moi ! Ta soeur est en sécurité. Mais "+sStr+"est maintenant entre les mains d'un pervers, qui pourrait la torturer en ce moment - ou pire ! Penses-tu que Levasseur laisserait ta sœur posséder un établissement aussi chic s'il la traitait comme les autres pauvres filles dans son cachot ?!";
						link.l1.go = "PZ_Longway_FlagMartinInfo_netVD1";
						if (!IsCharacterPerkOn(pchar, "Trustworthy")) notification("Perk Check Failed", "Trustworthy");
						if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 85) notification("Skill Check Failed (85)", SKILL_LEADERSHIP);
					}
				}
			}
			link.l2 = "Je ne perdrai pas de temps en disputes inutiles. Nous avons chacun nos propres priorités. Séparons-nous à nouveau. Que mon Dieu m'aide et que le vôtre vous assiste.";
			link.l2.go = "PZ_Longway_FlagMartinInfo_Razdelimsya";
			link.l3 = "Tu as raison. Je te dois bien ça. Très bien, fais à ta façon. De toute façon, sans toi, je ne pourrais peut-être pas gérer Levasseur et ses hommes. Mais si quelque chose arrive à "+sStr+"pendant que nous nous occupons de ta sœur...";
			link.l3.go = "PZ_Longway_FlagMartinInfo_IdemKSestreLongweya";
		break;
		
		case "PZ_Longway_FlagMartinInfo_Razdelimsya":
			dialog.text = "Merci de comprendre, Monseigneur le Capitaine. Bonne chance à vous !";
			link.l1 = "Et à vous, Longway.";
			link.l1.go = "PZ_Longway_FlagMartinInfo_SharleOdinVPodzemelie";
		break;
		
		case "PZ_Longway_FlagMartinInfo_IdemKSestreLongweya":
			dialog.text = "Les menaces oisives ne sont que des menaces vides, Monseigneur le Capitaine. Nous devons nous dépêcher, pour arriver à temps pour tout.";
			link.l1 = "J'espère que ton Dieu l'entend. Allons-y !";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_TogetherLongwayGo");
		break;
		
		case "PZ_Longway_FlagMartinInfo_netVD1":
			dialog.text = "Je laisserai passer cela par respect, Monseigneur le Capitaine. Juste cette fois-ci. La prochaine fois, je te frapperai. Je pars à la recherche de ma soeur maintenant, avec ou sans ton approbation.";
			link.l1 = "Je ne vais pas perdre plus de temps à discuter avec toi, Longway. En fin de compte, nous avons tous quelque chose que nous tenons plus cher que tout le reste.";
			link.l1.go = "PZ_Longway_FlagMartinInfo_SharleOdinVPodzemelie";
		break;
		
		case "PZ_Longway_FlagMartinInfo_SharleOdinVPodzemelie":
			pchar.questTemp.PZ_DevushkaRanena_Legko = true;
			LAi_LocationDisableOfficersGen("Tortuga_Cave", true);
			DoQuestReloadToLocation("Tortuga_Cave", "reload", "reload2", "PZ_Etap6TortugaPodzemelie");
		break;
		
		case "PZ_Longway_FlagMartinInfo_VD1":
			dialog.text = "Mm-hmm, d'accord, Monseigneur le Capitaine. Mais alors nous devons nous dépêcher.";
			link.l1 = "D'accord. Merci, Longway.";
			link.l1.go = "PZ_Longway_FlagMartinInfo_VD2";
		break;
		
		case "PZ_Longway_FlagMartinInfo_VD2":
			pchar.questTemp.PZ_LongwayRyadom = true;
			pchar.questTemp.PZ_DevushkaRanena_Legko = true;
			LAi_LocationDisableOfficersGen("Tortuga_Cave", true);
			DoQuestReloadToLocation("Tortuga_Cave", "reload", "reload2", "PZ_Etap6TortugaPodzemelie");
		break;
		
		case "PZ_TortureRoom_Levasser_1":
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
			{
				dialog.text = "Eh bien, eh bien, qui diable avons-nous là... Merde. Charles de Maure et son bâtard aux yeux bridés.";
				link.l1 = "Il n'y a qu'un seul bâtard ici. Si tu veux le voir, regarde dans le miroir, espèce de bâtard huguenot. Ou regarde juste ton neveu. Quoique, il ressemble plus à un rat galeux.";
				link.l1.go = "PZ_TortureRoom_Levasser_2";
			}
			else
			{
				dialog.text = "Je t'ai dit de ne pas me déranger ! Ah, Charles de Maure, hehehe. Quel petit nuisible persistant.";
				link.l1 = "Je suis juste comme ça. Maintenant, ferme ta putain de gueule et...";
				link.l1.go = "PZ_TortureRoom_Levasser_1_1";
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Sredne") || CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Tyazhelo") || CheckAttribute(pchar, "questTemp.PZ_Etap6_Opozdal")) Achievment_Set("ach_CL_130");
			}
			locCameraSleep(true);
			sld = CharacterFromID("Tibo");
			ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto2");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, CharacterFromID("Levasser"));
		break;
		
		case "PZ_TortureRoom_Levasser_1_1":
			dialog.text = "Tu n'es pas sur ton propre navire, chiot ! Il n'y a qu'un seul homme sur cette île, et c'est moi !";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_Etap6TortugaPytochnaya9");
		break;
		
		case "PZ_TortureRoom_Levasser_2":
			StartInstantDialog("Tibo", "PZ_TortureRoom_Levasser_3", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_TortureRoom_Levasser_3":
			dialog.text = "Comment oses-tu, espèce de vermine !";
			link.l1 = "";
			link.l1.go = "PZ_TortureRoom_Levasser_4";
			sld = CharacterFromID("Tibo");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, pchar);
		break;
		
		case "PZ_TortureRoom_Levasser_4":
			StartInstantDialog("Levasser", "PZ_TortureRoom_Levasser_5", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_TortureRoom_Levasser_5":
			dialog.text = "Calme-toi, neveu ! Monsieur de Maure est sur le point de recevoir une leçon de bonnes manières.";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_Etap6TortugaPytochnaya9");
			sld = CharacterFromID("Tibo");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, CharacterFromID("Levasser"));
		break;
		
		case "PZ_TortureRoom_Levasser_6":
			if (!CheckAttribute(pchar, "questTemp.PZ_Etap6_Opozdal"))
			{
				dialog.text = "Je t'ai donné la permission de couiner?!";
			}
			else
			{
				dialog.text = "Où est passé tout ce feu, hein, jolie chose ? Ah, je crois que je comprends...";
			}
			link.l1 = "Laisse-la tranquille, salaud !";
			link.l1.go = "PZ_TortureRoom_Levasser_7";
			LAi_SetActorType(npchar);
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) LAi_ActorTurnToCharacter(npchar, CharacterFromID("Mary"));
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) LAi_ActorTurnToCharacter(npchar, CharacterFromID("Helena"));
		break;
		
		case "PZ_TortureRoom_Levasser_7":
			dialog.text = "Heh-heh-heh... Tu peux crier et m'insulter autant que tu veux, mais je te vois trembler comme une feuille au vent. Je vois la peur dans tes yeux. Toi et Henri avez cela en commun. Sans vouloir t'offenser, neveu.";
			link.l1 = "Tu as raison, c'est la peur. Mais pas de toi, ordure.";
			link.l1.go = "PZ_TortureRoom_Levasser_7_1";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, pchar);
		break;
		
		case "PZ_TortureRoom_Levasser_7_1":
			dialog.text = "Bien sûr, bien sûr. J'ai déjà tout entendu - que tu ne crains personne, de Maure. Elle me l'a dit. 'O-oh, Charles viendra, Charles me sauvera... Charles par-ci, Charles par-là...' Eh bien, Charles est ici. Charles a une place au premier rang. Henri, mets notre invité à l'aise.";
			link.l1 = "";
			link.l1.go = "PZ_TortureRoom_Levasser_8";
		break;
		
		case "PZ_TortureRoom_Levasser_8":
			StartInstantDialog("Tibo", "PZ_TortureRoom_Levasser_9", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_TortureRoom_Levasser_9":
			if (CheckAttribute(pchar, "questTemp.PZ_Etap6_Opozdal"))
			{
				dialog.text = "Ce n'est pas nécessaire, Oncle. J'ai bien peur que tu sois allé un peu trop loin cette fois...";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
				{
					dialog.text = "Oncle, je vais avoir besoin de ton aide pour celle-là...";
				}
				else
				{
					dialog.text = "Dois-je l'achever, Oncle, ou le laisser regarder d'abord ?";
				}
			}
			link.l1 = "";
			link.l1.go = "PZ_TortureRoom_Levasser_10";
			LAi_SetActorType(npchar);
			//LAi_ActorTurnToCharacter(npchar, CharacterFromID("Levasser"));
			LAi_ActorTurnToLocator(npchar, "goto", "goto8");
			locCameraFromToPos(-15.67, 2.57, -1.23, true, -17.49, 1.42, -3.26);
		break;
		
		case "PZ_TortureRoom_Levasser_10":
			StartInstantDialog("Levasser", "PZ_TortureRoom_Levasser_11", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_TortureRoom_Levasser_11":
			if (CheckAttribute(pchar, "questTemp.PZ_Etap6_Opozdal"))
			{
				dialog.text = "Ce n'était pas moi, c'était Monsieur Chevalier Blanc ici qui a mis trop de temps à venir à la rescousse. On dirait que le spectacle est terminé, ha-ha-ha-ha !";
				link.l1 = "Mon Dieu, non...";
				link.l1.go = "exit";
				AddDialogExitQuest("PZ_TortureRoom_Levasser_DevushkaMertva");
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
				{
					dialog.text = "Je le pensais bien. Comment as-tu réussi à vivre jusqu'à cet âge ? Au fait, même question pour toi, de Maure.";
					link.l1 = "Tu n’as aucune idée du nombre de questions que j’ai pour toi, boucher !";
				}
				else
				{
					dialog.text = "J'aurais aimé que notre petite représentation ait un public... Mais je ne pense pas que Monsieur Têtu ici nous fera ce plaisir.";
					link.l1 = "Le seul plaisir que l'on retire de tout cela, c'est moi - en te vidant de tes entrailles, boucher !";
				}
				link.l1.go = "PZ_TortureRoom_Levasser_14";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko"))
			{
				locCameraFromToPos(-16.74, 2.58, -0.51, true, -13.13, -0.72, 2.49);
			}
			if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Sredne"))
			{
				locCameraFromToPos(-18.38, 1.77, 2.73, true, -20.53, 0.01, 0.32);
			}
			if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Tyazhelo"))
			{
				locCameraFromToPos(-16.97, 2.09, 3.98, true, -20.02, -0.17, 2.28);
			}
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("Tibo"));
		break;
		
		case "PZ_TortureRoom_Levasser_12":
			dialog.text = "Allez, vas-y, ramasse-la ! Ha-ha-ha !";
			link.l1 = "Salauds d'animaux, je vous ferai regretter d'être nés !";
			link.l1.go = "PZ_TortureRoom_Levasser_13";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, pchar);
		break;
		
		case "PZ_TortureRoom_Levasser_13":
			DialogExit();
			EndQuestMovie();
			locCameraSleep(false);
			DeleteAttribute(pchar, "GenQuest.BlockDialogCamera");
			LAi_SetPlayerType(pchar);
			locCameraTarget(PChar);
			locCameraFollow();
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
			{
				sld = CharacterFromID("Longway");
				ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto4");
				Return_LongwayOfficer();
				PlaySound("VOICE\Russian\hambit\Longway-02.wav");
			}
			LAi_SetFightMode(pchar, true);
			sld = CharacterFromID("Levasser");
			LAi_group_MoveCharacter(sld, "EnemyFight");
			sld = CharacterFromID("Tibo");
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "PZ_TortureRoom_Levasser_DevushkaMertva5");
		break;
		
		case "PZ_TortureRoom_Levasser_14":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Un boucher ? Je me considère plutôt comme un artiste, un peintre - essaieriez-vous au moins de le voir comme de l'art... Observez. Aimez-vous mon oeuvre ? Vraiment un de mes chefs-d'oeuvre. Pour être tout à fait honnête, je préfère les blondes, mais elle... À la fin, je lui ai pardonné cette vilaine couleur de cheveux. Ce n'était pas juste les cheveux - la fille, c'est du feu ! Je me suis presque brûlé. Elle s'est battue, a mordu, a grogné comme un animal sauvage ! Elle m'a rappelé une sauvage à la peau rouge, avec qui je me suis beaucoup amusé, même si ce n'était pas pour longtemps...";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Boucher ? Je me considère plutôt comme un artiste, un peintre - pourriez-vous au moins essayer de le voir comme de l'art... Observez.\nVoyez-vous, je n'en ai pas encore fini avec elle - il y a encore beaucoup d'espace vide sur cette toile. Non seulement elle est belle, mais elle est aussi dure qu'un roc et froide comme la glace. J'ai même dû transpirer un peu pour la faire crier. Elle a tenu jusqu'à la fin, juste pour ne pas me donner le plaisir d'entendre sa douce voix.";
			}
			link.l1 = "Libère-la maintenant, espèce de dégénéré.";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_Etap6TortugaPytochnaya13");
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, pchar);
		break;
		
		case "PZ_TortureRoom_Levasser_15":
			dialog.text = "Où penses-tu aller ? Ce morceau de viande m'appartient désormais. Tout comme tout ce qui l'entoure - cette ville, cette forteresse... Je suis Tortuga. Et toi et Poincy, ce vieux dindon puant, ne pourrez jamais changer cela.";
			link.l1 = "Levasseur, toi...";
			link.l1.go = "PZ_TortureRoom_Levasser_16";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, pchar);
		break;
		
		case "PZ_TortureRoom_Levasser_16":
			dialog.text = "C'est Signor de René de Buaduflé de Lettre pour vous.";
			link.l1 = "Je m'en fiche. Dégaine ton épée et montre-moi ce que tu vaux dans un combat - contre un homme, pas une fille sans défense.";
			link.l1.go = "PZ_TortureRoom_Levasser_17";
		break;
		
		case "PZ_TortureRoom_Levasser_17":
			dialog.text = "Et quel homme tu es ! Mais tu as raison, moi aussi je suis fatigué de tout ce bavardage. Je veux retourner auprès de... ma dame. Mais je te poserai une dernière question. Comment es-tu arrivé ici ? Qui a révélé l'emplacement de cet endroit ? Seule une poignée de personnes le sait.";
			if (CheckAttribute(pchar, "questTemp.PZ_FlagMartinInfo"))
			{
				link.l1 = "Votre ami commun, Martene, a chanté comme un rossignol. En fait, il a plutôt couiné comme un cochon à l'abattoir...";
				link.l1.go = "PZ_TortureRoom_Levasser_FlagMartinInfo_1";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_FlagMarselinaInfo"))
			{
				link.l2 = "Peut-être vaut-il mieux te le cacher. J'ai peur que cela ne blesse ton ego, Signor de René... quelque chose.";
				link.l2.go = "PZ_TortureRoom_Levasser_FlagMarselinaInfo_1";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_FlagShinInfo"))
			{
				link.l3 = "Une de vos victimes, Levasseur.";
				link.l3.go = "PZ_TortureRoom_Levasser_FlagShinInfo_1";
			}
		break;
		
		case "PZ_TortureRoom_Levasser_FlagShinInfo_1":
			dialog.text = "Menteur, scélérat ! Personne ne quitte ces murs !";
			link.l1 = "Utilise ta mémoire, allez. Il y en avait un. Chang Xing.";
			link.l1.go = "PZ_TortureRoom_Levasser_FlagShinInfo_2";
		break;
		
		case "PZ_TortureRoom_Levasser_FlagShinInfo_2":
			dialog.text = "Aucune chance. Pas elle. Certaines de mes idées ont été inspirées par ce petit démon. Oh-oh, on s'est beaucoup appris mutuellement, hehe. A-t-elle décidé de se racheter à la fin ? J'en doute. Après tout, je l'ai gravé hors d'elle il y a bien longtemps !";
			link.l1 = "Maintenant, je vais te vider goutte à goutte.";
			link.l1.go = "PZ_TortureRoom_Levasser_Bitva";
		break;
		
		case "PZ_TortureRoom_Levasser_FlagMartinInfo_1":
			dialog.text = "Et tu m'appelles un boucher, misérable hypocrite ! Heh-heh... Mais tant qu'il brûle en enfer, je n'ai rien à craindre.";
			link.l1 = "Il vous attend là-bas. Et votre vaurien de neveu aussi. Ne le décevons pas.";
			link.l1.go = "PZ_TortureRoom_Levasser_Bitva";
		break;
		
		case "PZ_TortureRoom_Levasser_FlagMarselinaInfo_1":
			dialog.text = "Que dirais-tu si je faisais un peu plus de mal à ce jouet ? Lui fendre le ventre ou la gorge, et la regarder se vider de son sang pendant que tu essaies de descendre jusqu'à elle...";
			link.l1 = "Tout ce que tu dis, Levasseur, tout ce que tu dis... Ta femme t'envoie ses salutations. Et avec ça, un adieu courbette.";
			link.l1.go = "PZ_TortureRoom_Levasser_FlagMarselinaInfo_2";
		break;
		
		case "PZ_TortureRoom_Levasser_FlagMarselinaInfo_2":
			dialog.text = "QUOI ?! Kha-kha... Putain de Marceline... Espèce de misérable garce, garce, garce, garce !";
			link.l1 = "C'est exact. Vous vous méritez l'un l'autre. Elle a cependant la tête un peu plus sur les épaules. Du moins, à première vue.";
			link.l1.go = "PZ_TortureRoom_Levasser_FlagMarselinaInfo_3";
		break;
		
		case "PZ_TortureRoom_Levasser_FlagMarselinaInfo_3":
			dialog.text = "Je vais planter sa tête de poulet sur une pique. Mais avant ça... oh-oh, il va se passer beaucoup, beaucoup de choses à cette traînée... Je vais même laisser mon nouveau jouet se reposer un peu. Attends ! J'ai une meilleure idée. Je vais la prêter à Henri. Pour un temps, bien sûr.";
			link.l1 = "";
			link.l1.go = "PZ_TortureRoom_Levasser_FlagMarselinaInfo_4";
		break;
		
		case "PZ_TortureRoom_Levasser_FlagMarselinaInfo_4":
			StartInstantDialog("Tibo", "PZ_TortureRoom_Levasser_FlagMarselinaInfo_5", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_TortureRoom_Levasser_FlagMarselinaInfo_5":
			dialog.text = "Vraiment? Merci, Oncle!";
			link.l1 = "";
			link.l1.go = "PZ_TortureRoom_Levasser_FlagMarselinaInfo_6";
			CharacterTurnByChr(npchar, CharacterFromID("Levasser"));
		break;
		
		case "PZ_TortureRoom_Levasser_FlagMarselinaInfo_6":
			StartInstantDialog("Levasser", "PZ_TortureRoom_Levasser_FlagMarselinaInfo_7", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_TortureRoom_Levasser_FlagMarselinaInfo_7":
			dialog.text = "Mérite-le d'abord - donne-moi un coup de main avec celui-là, hein ?";
			link.l1 = "Il est sur le point de craquer.";
			link.l1.go = "PZ_TortureRoom_Levasser_Bitva";
			CharacterTurnByChr(npchar, CharacterFromID("Tibo"));
		break;
		
		case "PZ_TortureRoom_Levasser_Bitva":
			DialogExit();
			EndQuestMovie();
			locCameraSleep(false);
			DeleteAttribute(pchar, "GenQuest.BlockDialogCamera");
			LAi_SetPlayerType(pchar);
			locCameraTarget(PChar);
			locCameraFollow();
			
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
			{
				sld = CharacterFromID("Longway");
				ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto4");
				Return_LongwayOfficer();
				PlaySound("VOICE\Russian\hambit\Longway-02.wav");
			}
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sld = CharacterFromID("Mary");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sld = CharacterFromID("Helena");
			LAi_SetImmortal(sld, true);
			
			LAi_SetFightMode(pchar, true);
			sld = CharacterFromID("Levasser");
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_SetCheckMinHP(sld, 1, true, "PZ_Etap6TortugaPytochnaya19");
			sld = CharacterFromID("Tibo");
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		break;
		
		case "PZ_TortureRoom_Longway_1":
			dialog.text = "Monseigneur le Capitaine... Longway vous présente ses condoléances. Nous avons fait tout ce que nous pouvions.";
			link.l1 = "Pas tout, pas encore assez.";
			link.l1.go = "PZ_TortureRoom_Longway_2";
		break;
		
		case "PZ_TortureRoom_Longway_2":
			dialog.text = "Longway va chercher Chang Xing. Viendras-tu avec moi ?";
			link.l1 = "Ouais, je vais avec toi, Longway. Mais souviens-toi - ta sœur a joué un rôle très actif dans ce spectacle sanglant aussi. Elle va devoir travailler très dur pour me convaincre de l'épargner. Et tu ne l'aideras pas. Maintenant viens, il est temps de mettre fin à cela.";
			link.l1.go = "PZ_TortureRoom_Longway_3";
		break;
		
		case "PZ_TortureRoom_Longway_3":
			DialogExit();
			Return_LongwayOfficer();
			chrDisableReloadToLocation = false;
		break;
		
		case "PZ_TortureRoom_Devushka_1":
			if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko"))
			{
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
				{
					dialog.text = "Charles, je le savais, ouais, hein ! Je savais que tu viendrais ! Tu le fais toujours, n'est-ce pas ?";
					link.l1 = "Je ne voudrais pas tester cela une quatrième fois, Mary... Ces vauriens, ils...";
				}
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
				{
					dialog.text = "Oh, mon Capitaine, vous ne réalisez pas à quel point vous arrivez à temps. Ces... ces monstres...";
					link.l1 = "C'est fini maintenant, Hélène. Ça va, tout est fini. Oh mon Dieu, qu'est-ce qu'ils t'ont fait...";
				}
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
				{
					dialog.text = "Charles, tu es là ! Je le savais, je le savais, ouais, hein ?";
					link.l1 = "Je naviguais toutes voiles dehors, fuyant pour ma vie, Mary. Toi... l'ont-ils fait ?..";
				}
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
				{
					dialog.text = "Mon Capitaine... Vous êtes là... J'avais presque perdu espoir...";
					link.l1 = "Je suis venu aussi vite que j'ai pu, Hélène. Je suis désolé d'avoir mis autant de temps.";
				}
				locCameraFromToPos(-15.32, 1.24, 1.31, true, -14.25, -1.00, -1.50);
			}
			link.l1.go = "PZ_TortureRoom_Devushka_2";
		break;
		
		case "PZ_TortureRoom_Devushka_2":
			if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko"))
			{
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
				{
					dialog.text = "Non, Charles, non. Ils ont essayé, mais je me suis défendue du mieux que j'ai pu. C'est pourquoi ils m'ont battue si violemment... S'il te plaît, Charles, sortons d'ici... ouais, hein ?";
					link.l1 = "Tout de suite, ma chère. Une dernière chose à faire.";
					link.l1.go = "PZ_TortureRoom_Devushka_3";
				}
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
				{
					dialog.text = "Ils ne l'ont pas fait, Charles ! Ils ne l'ont pas fait. Le reste guérira. S'il te plaît, emmène-moi loin d'ici.";
					link.l1 = "Bien sûr, mon cher. Il ne reste plus qu'une chose à faire ici.";
					link.l1.go = "PZ_TortureRoom_Devushka_3";
				}
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
				{
					dialog.text = "Non, Charles, non. Ils ont essayé, mais tu es arrivé juste à temps. Comme à l'époque. Combien de fois est-ce ?";
					link.l1 = "Je n'ai pas tenu le compte, Mary. Et je ne le ferai jamais.";
					link.l1.go = "PZ_TortureRoom_Devushka_2_1";
				}
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
				{
					dialog.text = "Tu es arrivé... juste à temps. Le pire ne s'est pas produit. Maintenant, s'il te plaît, sortons d'ici. N'importe où.";
					link.l1 = "Lève-toi, Hélène. Monte à l'étage. Je dois d'abord m'occuper de ce salaud.";
					link.l1.go = "PZ_TortureRoom_Devushka_3";
				}
			}
		break;
		
		case "PZ_TortureRoom_Devushka_2_1":
			dialog.text = "Et je ne cesserai pas de compter. Maintenant, quittons cet endroit, s'il te plaît.";
			link.l1 = "Bien sûr, ma chère. Il n'y a plus rien à faire ici. Sauf une chose.";
			link.l1.go = "PZ_TortureRoom_Longway_3";
		break;
		
		case "PZ_TortureRoom_Devushka_3":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko")) AddPassenger(pchar, npchar, false);
			LAi_SetPlayerType(pchar);
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) Return_MaryOfficer();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) Return_HelenaOfficer();
		break;
		
		case "PZ_TortureRoom_Levasser_18":
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
			{
				dialog.text = "Alors quoi, kha-kha, tu n'as pas le cran, morveux ? Demande à ton porc au cul jaune de te donner un coup de main...  Ou fais-le toi-même et tu auras une raison de dire à Poincy à quel point tu es courageux.";
				link.l1 = "Je préfère dire à tout le monde quel lâche de merde tu étais à la place.";
			}
			else
			{
				dialog.text = "Quoi, tu veux vraiment me regarder mourir en me vidant de mon sang ? Ça te plaît, hein ? Tu raconteras à ta femme quel héros tu es. Tu vois ce squelette là-haut sur le mur ? La femme du banquier de Santiago... Son homme pensait aussi être un héros, mais il s'est avéré être juste un bon hurleur - quand je l'ai fait tourner sur cette roue...";
				link.l1 = "Je pourrais rouler ta carcasse dessus, ordure, mais j'ai peur que ça ne supporte pas le poids de ton cul.";
			}
			link.l1.go = "PZ_TortureRoom_Levasser_19";
		break;
		
		case "PZ_TortureRoom_Levasser_19":
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
			{
				dialog.text = "Lâche ? Oh, kha-kha, allons...";
				link.l1 = "La cruauté n'est pas l'opposé de la lâcheté. Mais quelqu'un comme toi ne saurait pas faire la différence.";
				link.l1.go = "PZ_TortureRoom_Levasser_20";
			}
			else
			{
				dialog.text = "C'est très malin. Souvenez-vous de mes mots, de Maure : vous mourrez tout comme ce gros bonnet, enroué par vos propres cris et sourd des hurlements de vos...";
				link.l1 = "Brûle en Enfer, ordure.";
				link.l1.go = "exit";
				AddDialogExitQuest("PZ_TortureRoom_Levasser_Mertv1");
			}
		break;
		
		case "PZ_TortureRoom_Levasser_20":
			dialog.text = "D'accord, je ne suis pas vraiment un philosophe, je l'admets. Tu vois ce squelette sur le mur, de Maure ? C'est tout ce qui reste de la femme du banquier de Santiago. Lui aussi aimait bien parler fort, mais tout cela a cessé quand j'ai commencé à enrouler son corps sur cette roue. Il ne restait plus que des cris, qui m'ont presque rendu sourd...";
			link.l1 = "Finissons-en avec cela.";
			link.l1.go = "PZ_TortureRoom_Levasser_21";
		break;
		
		case "PZ_TortureRoom_Levasser_21":
			StartInstantDialog("Longway", "PZ_TortureRoom_Levasser_22", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_TortureRoom_Levasser_22":
			dialog.text = "Attendez un instant, Monseigneur le Capitaine... Ne soyez pas si pressé.";
			link.l1 = "Quel est le problème, Longway ?";
			link.l1.go = "PZ_TortureRoom_Levasser_23";
		break;
		
		case "PZ_TortureRoom_Levasser_23":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Ne le tue pas. Trop simple. Il mérite pire.";
			link.l1 = "Tu es en colère à propos de ta sœur, mon ami. Et je suis furieux de ce qu'il lui a fait "+sStr+"... et ce qu'il a pu lui faire. Mais je ne suis pas un animal comme lui. Je pourrais le brûler avec les braises de ce brasero, lui briser les os sur cette roue... Je pourrais le mettre aux fers et le laisser mourir d'hémorragie. Mais je ne peux pas risquer qu'un de ses sbires le sauve. Je ne peux pas prendre ce risque.";
			link.l1.go = "PZ_TortureRoom_Levasser_24";
		break;
		
		case "PZ_TortureRoom_Levasser_24":
			dialog.text = "Attendez, Monseigneur le Capitaine. Ce n'est pas ce que je voulais dire. Je parle de Poincy.";
			link.l1 = "Et lui alors ?";
			link.l1.go = "PZ_TortureRoom_Levasser_25";
		break;
		
		case "PZ_TortureRoom_Levasser_25":
			dialog.text = "Pense à la récompense qu'il te donnerait si tu lui apportais cet animal vivant. Il te couvrirait de doublons. Et cette vermine préfèrerait mourir ici que de pourrir dans un cachot à Capsterville.";
			link.l1 = "Tu as peut-être raison, Longway. Mais je ne sais pas exactement ce qui s'est passé entre ce salaud et le Chevalier. Crois-moi, je connais cette foule mieux que toi. Si c'est seulement une question d'argent, comme ils disent, ces deux-là pourraient conclure un marché. Poincy pourrait le laisser partir, et une autre salle comme celle-ci pourrait apparaître sur une autre île ou dans l'une des villes du Vieux Monde.";
			link.l1.go = "PZ_TortureRoom_Levasser_26";
			link.l2 = "Pas une mauvaise idée, Longway. Mais je doute que le Chevalier soit aussi généreux... Ce n'est pas vraiment dans sa nature. Mais pour moi, ce n'est pas une question d'argent de toute façon. Relevez-le ! Et soignez ses blessures pour qu'il ne meure pas avant l'heure.";
			link.l2.go = "PZ_TortureRoom_Levasser_28";
		break;
		
		case "PZ_TortureRoom_Levasser_26":
			StartInstantDialogNoType("Levasser", "PZ_TortureRoom_Levasser_27", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_TortureRoom_Levasser_27":
			dialog.text = "Mais d'abord, je viens pour toi. Et ton camarade. Je ne te toucherai pas, homme aux yeux bridés - tu ne vaux pas mon temps.";
			link.l1 = "Tu vois, Longway ? Tout cela doit s'arrêter maintenant. Ici et maintenant.";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_TortureRoom_Levasser_Mertv1");
		break;
		
		case "PZ_TortureRoom_Levasser_28":
			StartInstantDialogNoType("Levasser", "PZ_TortureRoom_Levasser_29", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_TortureRoom_Levasser_29":
			dialog.text = "Attendez une minute, Capitaine, attendez une minute, kha-kha.";
			link.l1 = "Qu'est-ce que c'est, Monsieur ex-gouverneur ?";
			link.l1.go = "PZ_TortureRoom_Levasser_30";
		break;
		
		case "PZ_TortureRoom_Levasser_30":
			dialog.text = "Ma clé est quelque part dans cette pièce. Elle ouvre un coffre dans mon bureau. Il y a deux cent mille en argent et une belle lame. Si cela ne suffit pas, dans la chambre de ma femme, dans la commode, il y a une collection de gemmes précieuses.";
			link.l1 = "Hmm, et que veux-tu en échange ?";
			link.l1.go = "PZ_TortureRoom_Levasser_31";
		break;
		
		case "PZ_TortureRoom_Levasser_31":
			dialog.text = "Une balle. Achève-moi. Ici et maintenant.";
			link.l1 = "Qu'en est-il du Chevalier de Poincy ? J'ai entendu dire que vous êtes de vieux amis... Vous ne voulez pas le voir ?";
			link.l1.go = "PZ_TortureRoom_Levasser_32";
		break;
		
		case "PZ_TortureRoom_Levasser_32":
			dialog.text = "Au diable Poincy ! Alors, tu es d’accord ou pas ?";
			link.l1 = "Pas vraiment, Monsieur de... Je ne veux pas énumérer votre nom complet.";
			link.l1.go = "PZ_TortureRoom_Levasser_33";
		break;
		
		case "PZ_TortureRoom_Levasser_33":
			dialog.text = "Ce n'est pas assez pour toi ? Bien, il y a plus...";
			link.l1 = "Les cris de tes victimes ont dû te rendre sourd, Levasseur. Je t'ai dit, ce n'est pas une question d'argent. Tu as peur de Poincy pour une raison, hein ? Je ne veux même pas savoir ce qu'il te fera. Mais si cela sert un peu de rétribution pour ton... art, qu'il en soit ainsi.";
			link.l1.go = "PZ_TortureRoom_Levasser_34";
			pchar.questTemp.PZ_LevasserPlenen = true;
			pchar.questTemp.PZ_LevasserPobezhden = true;
		break;
		
		case "PZ_TortureRoom_Levasser_34":
			dialog.text = "Alors c'est ce que tu es vraiment, kha-kha... Pas mieux que moi.";
			link.l1 = "Assez. Longway - relève-le !";
			link.l1.go = "PZ_TortureRoom_Levasser_35";
		break;
		
		case "PZ_TortureRoom_Levasser_35":
			DialogExit();
			
			PChar.quest.PZ_TortureRoom_Levasser_ObratnoNaBereg.win_condition.l1 = "locator";
			PChar.quest.PZ_TortureRoom_Levasser_ObratnoNaBereg.win_condition.l1.location = "Tortuga_Torture_room";
			PChar.quest.PZ_TortureRoom_Levasser_ObratnoNaBereg.win_condition.l1.locator_group = "reload";
			PChar.quest.PZ_TortureRoom_Levasser_ObratnoNaBereg.win_condition.l1.locator = "reload1";
			PChar.quest.PZ_TortureRoom_Levasser_ObratnoNaBereg.win_condition = "PZ_TortureRoom_Levasser_ObratnoNaBereg";
			
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) Return_MaryOfficer();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) Return_HelenaOfficer();
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom")) Return_LongwayOfficer();
			sld = CharacterFromID("Levasser");
			sld.location = "None";
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		break;
		
		case "PZ_Etap6_NaBeregu_DevaZdorovaya_1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				if (!CheckAttribute(pchar, "questTemp.PZ_FlagShinInfo"))
				{
					dialog.text = "Notre navire... Je n'aurais jamais pensé être si heureux de la revoir... bon. Enfin, ce cauchemar est terminé.";
				}
				else
				{
					dialog.text = "C'est enfin terminé. Où allons-nous maintenant, Charles ?";
				}
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				if (!CheckAttribute(pchar, "questTemp.PZ_FlagShinInfo"))
				{
					dialog.text = "Je n'arrive pas à croire que tout soit fini... Que faisons-nous maintenant, mon Capitaine ?";
				}
				else
				{
					dialog.text = "Eh bien, c'est tout, mon Capitaine. Que faisons-nous maintenant ?";
				}
			}
			if (!CheckAttribute(pchar, "questTemp.PZ_FlagShinInfo"))
			{
				link.l1 = "Hélas, ce n'est pas encore terminé. Chang Xing... Cette histoire ne se termine vraiment que lorsque j'obtiens mes réponses d'elle.";
				link.l1.go = "PZ_Etap6_NaBeregu_DevaZdorovaya_2";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.PZ_LevasserPlenen"))
				{
					link.l1 = "Mettez le cap sur Capsterville. Il est temps que Monsieur Levasseur devienne une partie de l'histoire.";
				}
				else
				{
					link.l1 = "La mission du Chevalier est accomplie. Je dois lui en faire part. Cependant, je vais omettre certains détails. J'espère seulement qu'il tiendra parole et que Michel sera libéré...";
				}
				link.l1.go = "exit";
				AddDialogExitQuest("PZ_Final_SdaemKvestPuansi");
			}
		break;
		
		case "PZ_Etap6_NaBeregu_DevaZdorovaya_2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Moi aussi, ouais, hein. Alors je viens avec toi. Et n'essaie même pas de discuter avec moi, Charles.";
				link.l1 = "Mary, ma chère, tu as besoin de te reposer. Tu es à deux doigts de t'évanouir...";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Je viendrai avec vous.";
				link.l1 = "Helen, tu as failli mourir des mains de ce démon. Tu tiens à peine debout...";
			}
			link.l1.go = "PZ_Etap6_NaBeregu_DevaZdorovaya_3";
		break;
		
		case "PZ_Etap6_NaBeregu_DevaZdorovaya_3":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "J'ai besoin de toi, Charles. Et tu as besoin de moi. Et si quelqu'un doit s'évanouir ce soir, c'est Chang Xing. Sur le sol de son bordel, avec une balle entre les yeux !";
				link.l1 = "Oui, Levasseur n'a pas réussi à te faire perdre ton esprit combatif. Je te renverrais bien au navire, mais je sais que tu me suivrais quand même...";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Mais je peux encore tenir une lame. Charles, je dois y être. J'ai besoin de comprendre ce qui l'a poussée à le faire. Comprends-tu pourquoi cela m'importe tant ?";
				link.l1 = "Je comprends que tu as besoin de repos et de guérison. Et d'un long repos, d'ailleurs.";
			}
			link.l1.go = "PZ_Etap6_NaBeregu_DevaZdorovaya_4";
		break;
		
		case "PZ_Etap6_NaBeregu_DevaZdorovaya_4":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Tu me connais trop bien, Charles, ouais, hein. Alors, laissons tomber les bavardages et finissons-en.";
				link.l1 = "Fais comme tu veux. Mais reste sur tes gardes. Personne ne sait quelles surprises nous attendent là-bas.";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Ça peut attendre. Tu es venu pour moi, et maintenant je viens avec toi. Que tu le veuilles ou non.";
				link.l1 = "Je vois que tu as encore du cran, Hélène. Bien. Reste derrière moi, et pour l'amour de Dieu, fais attention.";
			}
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_SDevushkoyKShin");
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_1":
			if (!CheckAttribute(pchar, "questTemp.PZ_FlagShinInfo"))
			{
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
				{
					dialog.text = "Notre navire... Je n'arrive pas à croire que je vais y remonter, ouais, hein...";
					link.l1 = "Elle t'attend, Mary. Un bon repas et un lit douillet aussi...";
				}
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
				{
					dialog.text = "Ugh... Je ne pensais pas que j'arriverais jusqu'au bateau sur mes propres jambes.";
					link.l1 = "Tu es la personne la plus résiliente que j'aie jamais connue, Hélène. Maintenant, rentre à l'intérieur et puis au lit...";
				}
				link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_2";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
				{
					dialog.text = "Notre navire... Je n'arrive pas à croire que je vais y remonter, ouais, hein...";
				}
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
				{
					dialog.text = "Ugh... Je ne pensais pas que j'arriverais jusqu'au bateau sur mes deux pieds.";
				}
				if (CheckAttribute(pchar, "questTemp.PZ_LevasserPlenen"))
				{
					link.l1 = "Mets le cap sur Capsterville. Il est temps que Monsieur Levasseur entre dans l'histoire.";
				}
				else
				{
					link.l1 = "La mission du Chevalier est terminée. Je dois lui en faire rapport. Cependant, je vais omettre certains détails. J'espère seulement qu'il tiendra parole et que Michel sera libéré...";
				}
				link.l1.go = "exit";
				AddDialogExitQuest("PZ_Final_SdaemKvestPuansi");
			}
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Et toi, Charles... Pourquoi ce regard ? Tu prépares encore un coup, n'est-ce pas ?";
				link.l1 = "Chang Xing. Je dois aussi la rejoindre.";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Et toi ? Où vas-tu ?";
				link.l1 = "Voir Chang Xing. Elle est le dernier chapitre de ce cauchemar.";
			}
			link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_3";
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_3":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Alors je viens avec toi ! Elle me doit une fière chandelle, ouais, hein ?";
				link.l1 = "Mary, ma chère, tu as à peine atteint le bateau. Et tu ne peux pas tenir une lame en ce moment. Je vais lui faire payer pour ce qu'elle t'a fait, je le jure devant Dieu. Mais je me sentirai bien mieux si tu restes sur le navire, sachant que tu es en sécurité.";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Mon Capitaine, j'aimerais tant aller avec vous... Faites attention, je vous en prie. Qui sait de quoi elle est encore capable ? Elle m'a retenue pendant que ce chiot Thibaut...";
				link.l1 = "Le pire est passé, Helen. Tout sera bientôt terminé, je te le promets.";
			}
			link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_4";
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_4":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
				{
					dialog.text = "Eh bien, au moins Longway te couvrira en mon absence. Mais s'il t'arrive quoi que ce soit, je les enterrerai lui et Chang Xing moi-même !";
					link.l1 = "Tout ira bien. Maintenant, va te reposer. Je serai de retour avant que tu ne t'en rendes compte.";
					link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_7";
				}
				else
				{
					dialog.text = "Où est passé Longway, Charles ?";
					link.l1 = "Il est parti après Chang Xing sans moi. Je n'ai pas pu l'arrêter, mais que pouvais-je faire ?";
					link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_5";
				}
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
				{
					dialog.text = "Eh bien, au moins Longway vient avec toi. C'est un certain réconfort, au moins.";
					link.l1 = "Tu vois ? Pas besoin de s'inquiéter. Je ne serai pas long.";
					link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_7";
				}
				else
				{
					dialog.text = "Où est Longway ? Je viens de réaliser qu'il n'est pas là.";
					link.l1 = "Il est allé voir sa sœur sans moi. Je ne lui en veux pas. Il a attendu trop longtemps pour ce moment.";
					link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_5";
					
				}
			}
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_5":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Charles, j'ai un mauvais pressentiment à ce sujet...";
				link.l1 = "Je sais. Ce cauchemar a duré trop longtemps, et la fin est proche. Le pire est passé.";
				link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_6";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Qui sait ce qu'il a en tête, Charles ? Garde les yeux ouverts, ouais, hein ?";
				link.l1 = "Je le ferai. Je reviendrai bientôt, Helen."link.l1.go ="PZ_Etap6_NaBeregu_DevaBolnaya_7";
			}
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_6":
			dialog.text = "Promets-moi que tu seras prêt à tout.";
			link.l1 = "Je le suis, et je le serai. Je reviendrai bientôt, Mary.";
			link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_7";
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_7":
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom")) StartInstantDialog("Longway", "PZ_Etap6_NaBeregu_DevaBolnaya_8", "Quest\CompanionQuests\Longway.c");
			else
			{
				DialogExit();
				LAi_SetPlayerType(pchar);
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sld = CharacterFromID("Mary");
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sld = CharacterFromID("Helena");
				LAi_ActorRunToLocation(sld, "reload", "sea", "", "", "", "", -1);
				sld.location = "None";
				AddQuestRecord("PZ", "51");
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) AddQuestUserData("PZ", "sText", "Mary");
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) AddQuestUserData("PZ", "sText", "Helen");
				PChar.quest.PZ_Etap6_BrothelPoiskSestry.win_condition.l1 = "location";
				PChar.quest.PZ_Etap6_BrothelPoiskSestry.win_condition.l1.location = "Tortuga_brothelElite";
				PChar.quest.PZ_Etap6_BrothelPoiskSestry.win_condition = "PZ_Etap6_BrothelPoiskSestry";
			}
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_8":
			dialog.text = "Longway vous a aidé, Capitaine. Maintenant, c'est à vous de tenir parole.";
			link.l1 = "Tu as tout entendu, Longway. Allons voir ta sœur.";
			link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_9";
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_9":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Monseigneur le Capitaine, Longway a une dernière requête : laissez Chang Xing s'expliquer. Écoutez-la avant de prendre une décision.";
			link.l1 = "Que s'est-il passé avec "+sStr+" est sur elle. Mais je lui donnerai d'abord une chance de s'expliquer.";
			link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_10";
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_10":
			dialog.text = "Longway fait confiance à votre parole, votre jugement et votre bonté.";
			link.l1 = "Camarade, il n'y a pas de place pour la raison ou la gentillesse dans ce foutu bazar. Et il est grand temps d'y mettre fin.";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_SLongwayKShin");
		break;
		
		case "PZ_LongwayPrishelOdin":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sStr = "Helen";
			if (CheckAttribute(pchar, "questTemp.PZ_DevushkaMertva"))
			{
				dialog.text = "Monseigneur le Capitaine...";
				link.l1 = +sStr+"est mort.";
				link.l1.go = "PZ_LongwayPrishelOdin2";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko"))
				{
					dialog.text = "Capitaine, madame "+sStr+"C'est un plaisir de vous voir. Voici... Chang Xing.";
					link.l1 = "Je l'ai deviné, Longway. Recule. Tu as eu tout le temps de parler à ta sœur. Maintenant, elle doit répondre à "+sStr+" pour avoir aidé les sbires de Levasseur à l'enlever.";
					link.l1.go = "PZ_LongwayPrishelOdin7";
				}
				else
				{
					dialog.text = "Tu es venu... Où est la dame "+sStr+" ? Est-elle... ?";
					link.l1 = "Non, Longway. Dieu merci, non. Je l'ai emmenée sur le navire. Sinon, je ne serais même pas en train d'avoir cette conversation maintenant. Cependant, cela ne va toujours pas être facile ou agréable.";
					link.l1.go = "PZ_LongwayPrishelOdin12";
				}
			}
		break;
		
		case "PZ_LongwayPrishelOdin2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Chang Xing et moi présentons nos condoléances...";
			link.l1 = "Des condoléances de la part de Chang Xing ?! Autant offrir des condoléances au nom de Levasseur, Longway ! Tu sais très bien qu'elle a participé à l'enlèvement de "+sStr+"     avec les autres, ses sbires ! Et maintenant elle est partie...!";
			link.l1.go = "PZ_LongwayPrishelOdin3";
		break;
		
		case "PZ_LongwayPrishelOdin3":
			dialog.text = "Nous... Je comprends ce que vous ressentez en ce moment, Monseigneur le Capitaine.";
			link.l1 = "Oh, vraiment ?";
			link.l1.go = "PZ_LongwayPrishelOdin4";
		break;
		
		case "PZ_LongwayPrishelOdin4":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "J'ai perdu mes parents, comme tu te souviens. Si tu te souviens. De plus, ce n'était pas Chang Xing qui a torturé et tué "+sStr+"Je comprends ta douleur, ta rage. Mais la culpabilité de ma soeur n'est pas aussi grande que la tienne à considérer. S'il te plaît, écoute-moi.";
			link.l1 = "Je me souviens. Je vais écouter ton histoire. Mais fais vite ! Et sache que je ne peux pas laisser quelque chose comme ça impuni !";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_LongwayPrishelOdin_ChangShinNext");
		break;
		
		case "PZ_LongwayPrishelOdin5":
			dialog.text = "Alors je ferais mieux de tout raconter à nouveau, Monsieur de Maure. Notre Tu parle français si mal que tu l'as presque attaqué.";
			link.l1 = "Tu aurais dû la fermer. Je n'allais pas attaquer Longway, mais toi... C'est toi qui es responsable de sa mort.";
			link.l1.go = "PZ_LongwayPrishelOdin6";
			locCameraFromToPos(2.17, 2.32, 0.55, true, -0.92, -0.37, -4.09);
			sld = characterFromId("Longway");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "goto", "goto9", "PZ_LongwayTurnToChangShin", -1);
		break;
		
		case "PZ_LongwayPrishelOdin6":
			dialog.text = "Je pourrais discuter de cela, mais je réalise que je préfère ne pas le faire. Tu parlais de toi comme une personne de respect et de compréhension. Mais est-ce vraiment le cas ? Est-ce que ça a du sens que je commence même à parler ? Ou as-tu déjà pris ta décision ?";
			link.l1 = "Tu sais comment entrer dans la tête de quelqu'un, mademoiselle. Ça ne vaut vraiment pas la peine de discuter maintenant. Mais si tu veux essayer de te justifier... Eh bien, vas-y. Pour l'amour de Longway, je t'écouterai.";
			link.l1.go = "PZ_ChangShin2";
		break;
		
		case "PZ_LongwayPrishelOdin7":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Elle peut tout expliquer, Monseigneur le Capitaine... Ce n'est pas ce que vous pensez... Pas vraiment...";
			link.l1 = "Alors explique-le. Mais pas à moi."+sStr+"Regarde dans ses yeux. Regarde ses bleus et ses blessures. Et dis-lui que ce n'était pas comme ça.";
			link.l1.go = "PZ_LongwayPrishelOdin8";
		break;
		
		case "PZ_LongwayPrishelOdin8":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Mes excuses au nom de Xing, Capitaine...";
			link.l1 = "À en juger par son visage narquois, tu le fais en vain. Elle ne mérite pas tes excuses.";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_LongwayPrishelOdin_ChangShinNext");
		break;
		
		case "PZ_LongwayPrishelOdin9":
			dialog.text = "Vous êtes trop dur avec lui, Monsieur de Maure. Bien que vous soyez probablement habitué à le traiter de cette manière - comme un ouvrier à la peau jaune typique.";
			link.l1 = "Essayez-vous de monter Longway contre moi ? Ça ne marchera pas. Je l'ai toujours traité avec respect, et il le sait. C'est tout ce qui compte. Je réalise que jouer à des jeux est tout ce qu'il vous reste maintenant.";
			link.l1.go = "PZ_LongwayPrishelOdin10";
			locCameraFromToPos(2.17, 2.32, 0.55, true, -0.92, -0.37, -4.09);
			sld = characterFromId("Longway");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "goto", "goto9", "PZ_LongwayTurnToChangShin", -1);
		break;
		
		case "PZ_LongwayPrishelOdin10":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Que veux-tu faire ? Arracher le pauvre Tu à sa famille ? Alors qu'il vient enfin de les retrouver après dix ans ?";
			link.l1 = "Sang ne fait pas toujours une famille. Mais que suggérez-vous que nous fassions ? Laisser ce que vous avez fait à "+sStr+" rester impuni ? Et permettre à Longway de rendre visite de temps en temps à une femme qui trafique d'autres filles sans y penser à deux fois ?";
			link.l1.go = "PZ_LongwayPrishelOdin11";
		break;
		
		case "PZ_LongwayPrishelOdin11":
			dialog.text = "Eh bien, pour commencer, écoute. Contrairement à lui, je peux répéter ce que je viens de lui dire en français parfait. Mon histoire. En te regardant droit dans les yeux, ou même dans les siens. Et tout cela sans l'accent dont tu en as probablement marre à présent. Après tout, qu'avons-nous tous à perdre ?";
			link.l1 = "I'm used to Longway's accent; it's part of who he is to me. I'll listen to you, but only for the sake of my friend. Go on.";
			link.l1.go = "PZ_ChangShin2";
		break;
		
		case "PZ_LongwayPrishelOdin12":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Pourquoi pas, Monseigneur le Capitaine...?";
			link.l1 = "Tu as vraiment besoin de demander ? Elle était impliquée dans l'enlèvement de "+sStr+", n'est-ce pas ?";
			link.l1.go = "PZ_LongwayPrishelOdin13";
		break;
		
		case "PZ_LongwayPrishelOdin13":
			dialog.text = "Je... présente mes excuses sincères. C'est aussi ma faute de ne pas avoir pu sauver ma sœur il y a dix ans, de ne pas l'avoir protégée de tout cela.";
			link.l1 = "Tu ne devrais pas t'excuser pour ceux qui n'ont pas le moindre remords, Longway. As-tu fini ici ? C'est mon tour de lui parler.";
			link.l1.go = "PZ_LongwayPrishelOdin14";
		break;
		
		case "PZ_LongwayPrishelOdin14":
			dialog.text = "Monseigneur le Capitaine, attendez ! Chang Xing n'est pas comme Levasseur. Pas entièrement. Elle me racontera sa vie au cours de ces dix années. Permettez-moi de vous raconter aussi.";
			link.l1 = "D'accord, Longway. Je t'écoute. Beaucoup dépend de ce que tu vas me dire.";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_LongwayPrishelOdin_ChangShinNext");
		break;
		
		case "PZ_LongwayPrishelOdin15":
			dialog.text = "Si c'est toi qui le racontes, on va tous avoir mal à la tête. Permets-moi, Tu. Charles de Maure, je présume ?";
			link.l1 = "D'accord. Et tu es Belle Etoile, aussi connu sous le nom de Chang Xing. Tu as participé à l'enlèvement de mon amour, avec Thibaut et Martene. Et tu souris quand j'en parle. De bons souvenirs ?";
			link.l1.go = "PZ_LongwayPrishelOdin16";
		break;
		
		case "PZ_LongwayPrishelOdin16":
			dialog.text = "C'est idiot de le nier. Mais qu'est-ce que ça change maintenant ? Vas-tu me torturer devant mon frère ? Ou même lui demander de t'aider à me torturer ? Ou vas-tu simplement me tuer ? Ferais-tu vraiment ça pour lui ?";
			link.l1 = "Comme je l'ai dit, malgré tout ce que j'aimerais faire en ce moment, je te parle encore. Ne pousse pas trop. Dis-moi ce que tu lui as dit avant. Et ensuite, nous verrons où nous irons tous à partir de là.";
			link.l1.go = "PZ_ChangShin2";
		break;
		
		case "PZ_Longway_91":
			if (!CheckAttribute(pchar, "questTemp.PZ_LevasserPobezhden"))
			{
				dialog.text = "Je n'arrive toujours pas à croire que Chang Xing se transformerait en... ça.";
				link.l1 = "Les gens changent, Longway. N'importe qui peut être brisé ou voir les dernières gouttes de bonté et de foi effacées d'eux.";
				link.l1.go = "PZ_Longway_ToGirl1";
			}
			else
			{
				dialog.text = "Longway ne peut toujours pas croire que ma sœur est devenue... cela. Pourquoi... pourquoi ? Si seulement j'avais été à la maison ce jour-là...";
				link.l1 = "Ne te torture pas avec des 'et si'. De plus, tu n'es pas resté les bras croisés toutes ces années - tu as vraiment fait de ton mieux pour arranger les choses.";
				link.l1.go = "PZ_Longway_ToShore1";
			}
		break;
		
		case "PZ_Longway_ToGirl1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Eh... Je suppose que c'est ainsi, Monseigneur le Capitaine.";
			link.l1 = "Sortez d'ici. Nous devons encore nettoyer le chaos qu'elle a laissé derrière et sauver le "+sStr+" le plus tôt possible.";
			link.l1.go = "PZ_Longway_ToGirl2";
		break;
		
		case "PZ_Longway_ToGirl2":
			dialog.text = "Aye. Nous devons nous dépêcher - cela a déjà été retardé trop longtemps à cause de moi.";
			link.l1 = "Ce n'est pas ta faute, Longway. Dépêchons-nous !";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_LeaveEliteBrothel");
		break;
		
		case "PZ_Longway_ToShore1":
			dialog.text = "D'accord. Merci pour votre soutien, Monseigneur le Capitaine.";
			link.l1 = "N'en parle pas. Elle ne méritait pas ton dévouement de toute façon - ce n'était pas elle qui te recherchait, même quand elle aurait pu. Ta étoile s'est éteinte depuis longtemps, et elle a cessé d'être ta famille il y a bien longtemps. Nous sommes ta famille maintenant, Longway.";
			link.l1.go = "PZ_Longway_ToShore2";
		break;
		
		case "PZ_Longway_ToShore2":
			dialog.text = "Oui... Alors c'est bien toi. Et j'étais trop aveugle pour le voir tout ce temps.";
			link.l1 = "Mieux vaut tard que jamais. Maintenant, rentrons chez nous - notre navire nous attend.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_LeaveEliteBrothel");
		break;
		
		case "PZ_Mary_91":
			dialog.text = "D'accord. Tu n'as aucune idée à quel point je voulais ça.";
			link.l1 = "Je crois bien. Comment te sens-tu, Mary ? La raison pour laquelle je voulais éviter le bain de sang, c'était parce que je n'étais pas sûr que tu puisses tenir ta lame aussi fermement que d'habitude - l'un d'eux aurait pu prendre l'avantage pendant que j'étais occupé avec un autre.";
			link.l1.go = "PZ_Mary_92";
		break;
		
		case "PZ_Mary_92":
			dialog.text = "Tu me sous-estimes. De plus, la colère est un sacré remède. Je n'avais aucun doute que tu te précipiterais pour me sauver - comme tu le fais toujours, ouais, hein ? Tu sais, Charles... Même si tu m'appelles ton Talisman Rouge, et si tu étais le mien aussi ? Quelque chose d'incroyable se produit toujours quand nous sommes ensemble.";
			link.l1 = "Je suis ton talisman ? Pourquoi pas, j'aime bien cette idée.";
			link.l1.go = "PZ_Mary_93";
		break;
		
		case "PZ_Mary_93":
			dialog.text = "Voilà, tu souris déjà ! Maintenant, sortons de cet endroit dégoûtant - dépêche-toi, vite, ouais, hein ?";
			link.l1 = "Eh-heh, ce bazar m'a vraiment frappé fort. J'aurais aimé que cela puisse se terminer autrement.";
			link.l1.go = "PZ_Mary_94";
		break;
		
		case "PZ_Mary_94":
			dialog.text = "Je ne le pense pas. Il n'y avait aucun moyen de la sauver, Charles. Et elle a entraîné Longway avec elle. Il a fait son choix, et il ne nous a laissé aucun choix. Pense à toutes les personnes que nous avons aidées aujourd'hui.";
			link.l1 = "Encore une fois, je n'ai rien à te contredire, Mary. Et cette fois, je n'en ai même pas envie. Viens, mon Talisman Rouge...";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_LeaveEliteBrothel");
		break;
		
		case "PZ_ElitaShluha_Final1":
			if (CheckAttribute(pchar, "questTemp.PZ_ChangShinMertva"))
			{
				dialog.text = "Que s'est-il passé là-bas, monsieur ? Nous avons entendu des jurons et des cris. Mais nous n'avons pas osé appeler à l'aide avant que ce soit fini.";
				link.l1 = "Et à juste titre. Votre hôtesse est morte. Vous êtes libres de partir. Si j'étais vous, je collecterais le trésor de l'établissement, le partagerais, et fuirais l'île dès que possible. Je sais que vous êtes des dames honorables, pas de simples prostituées, donc vous aurez un avenir au-delà de cet endroit misérable.";
				link.l1.go = "PZ_ElitaShluha_Final2";
			}
			else
			{
				dialog.text = "Oh, c'est vous, monsieur. Savez-vous quand l'hôtesse descend ?";
				link.l1 = "Pas tout de suite. Et je m'écarterais de la porte si j'étais vous. Et ne lui parlez jamais de cette soirée - elle ne partagera rien, et les chats curieux perdent leur vie d'un seul coup. Il semble que votre madame n'aime pas que l'on fouine dans ses secrets.";
				link.l1.go = "PZ_ElitaShluha_Final3";
			}
		break;
		
		case "PZ_ElitaShluha_Final2":
			dialog.text = "Tu l'as tuée ?!";
			link.l1 = "Je l'ai fait. Et si vous tardez ou essayez d'appeler les gardes sur moi, ce serait votre plus grande erreur. Elle n'a jamais été une sainte patronne pour vous - peu importe combien de soie et d'éducation elle vous a données, vous étiez emprisonnées ici, forcées de vous donner à n'importe quel vaurien qu'elle désignait. Je vous souhaite bonne chance pour sortir d'ici. Adieu, mesdames.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_ToTortugaStreets");
		break;
		
		case "PZ_ElitaShluha_Final3":
			dialog.text = "Est-elle vraiment en sécurité ? Peut-on entrer ? Faut-il appeler les gardes ?";
			link.l1 = "Elle ne sera jamais bien. Vous pouvez essayer de lui demander vous-même... à vos risques et périls. Elle parle encore à son frère. Et je ne pense pas qu'ils seront heureux d'être dérangés.";
			link.l1.go = "PZ_ElitaShluha_Final4";
		break;
		
		case "PZ_ElitaShluha_Final4":
			dialog.text = "Je vois... Eh bien, revenez nous voir un de ces jours, monsieur.";
			link.l1 = "Jamais. Adieu, mesdames.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_ToTortugaStreets");
		break;
		
		case "PZ_TortugaSoldier1":
			dialog.text = "Halte ! Des cris et des combats ont été signalés chez Mademoiselle Etoile. La garde pense que vous avez quelque chose à voir avec cela. Remettez vos armes et suivez-nous, monsieur.";
			if (!CheckAttribute(pchar, "questTemp.PZ_DevushkaMertva"))
			{
				link.l1 = "C'est vrai, mais nous n'avons pas commencé la bataille, nous l'avons terminée. Les brutes à gages se sont rebellées à cause des paiements en retard et ont attaqué Madame Etoile pour la voler. Faire confiance aux mercenaires, eh ? Nous avons remporté la victoire, mais malheureusement, elle n'a pas survécu.";
				link.l1.go = "PZ_TortugaSoldier2";
			}
			else
			{
				link.l1 = "J'ai perdu l'amour de ma vie aujourd'hui, alors laissez-moi passer, monsieur l'officier.";
				link.l1.go = "PZ_TortugaSoldierGirlDied1";
			}
		break;
		
		case "PZ_TortugaSoldier2":
			dialog.text = "Tu réalises que nous ne pouvons pas simplement te croire sur parole, n'est-ce pas ? Nous devons te détenir. Et tu auras besoin de témoins parmi les employées féminines. Voyons ce qu'elles ont à dire.";
			link.l1 = "Mon bien-aimé est gravement blessé. Je suis aussi épuisé. Ne pouvez-vous pas simplement nous laisser partir, s'il vous plaît ?";
			link.l1.go = "PZ_TortugaSoldier3";
		break;
		
		case "PZ_TortugaSoldier3":
			dialog.text = "Nous allons essayer de régler cela dès que possible. Maintenant, suivez-nous.";
			link.l1 = "Va au diable...";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_TortugaSoldiersFight");
		break;
		
		case "PZ_TortugaSoldierGirlDied1":
			dialog.text = "Condoléances, monsieur. Et je ne suis pas encore officier, mais... enfin, peu importe. Pourriez-vous venir avec nous et nous raconter ce qui s'est passé là-bas?";
			link.l1 = "Je vais te le dire. Le bordel perdait de l'argent et il n'y avait plus de cash pour payer les mercenaires qui le gardaient. Ils ont décidé de prendre ce qui restait, juste au moment où je m'y trouvais. Madame Etoile et moi les avons repoussés, mais elle est morte de ses blessures. Maintenant, laisse-moi passer enfin.";
			link.l1.go = "PZ_TortugaSoldierGirlDied2";
		break;
		
		case "PZ_TortugaSoldierGirlDied2":
			dialog.text = "J'aimerais bien, mais il y a beaucoup de paperasse à remplir. Et je dois interviewer les dames qui y travaillent. J'ai bien peur que vous deviez rester en ville au moins un jour, même si vous dites la vérité, monsieur.";
			link.l1 = "Va au diable...";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_TortugaSoldiersFight");
		break;
		
		case "PZ_Longway_101":
			dialog.text = "Longway a quelque chose pour vous, Monseigneur le Capitaine.";
			link.l1 = "Comme c'est beau et fantasque. Je n'ai jamais rien vu de tel. Qu'est-ce que c'est ?";
			link.l1.go = "PZ_Longway_102";
			GiveItem2Character(PChar, "talisman14");
			PlaySound("interface\important_item.wav");
		break;
		
		case "PZ_Longway_102":
			dialog.text = "C'est l'amulette de capitaine de ma Patrie. Et, puisque Longway n'est plus capitaine, je te la donne.";
			link.l1 = "Merci, Longway. Avec la mort de van der Vink, tu as obtenu ta revanche sur tous ceux que tu voulais. Je suis heureux que tout se soit bien passé ainsi.";
			link.l1.go = "PZ_Longway_103";
		break;
		
		case "PZ_Longway_103":
			dialog.text = "Si seulement je pouvais convaincre Xing de redevenir une bonne personne...";
			link.l1 = "Elle ne voudrait plus écouter personne, même pas son frère. Tu as fait de ton mieux. Nous l'avons tous fait.";
			link.l1.go = "PZ_Longway_104";
		break;
		
		case "PZ_Longway_104":
			dialog.text = "Oui... Merci beaucoup, Monseigneur le Capitaine. Longway d'être libre, d'avoir un foyer et des amis à nouveau.";
			link.l1 = "Je t'en prie, mon ami. Maintenant, pourquoi ne viens-tu pas avec moi rendre visite à mon frère. Oh, quelle ironie !";
			link.l1.go = "PZ_Longway_105";
		break;
		
		case "PZ_Longway_105":
			DialogExit();
			DeleteAttribute(npchar, "CompanionDisable");//теперь можем и в компаньоны
			chrDisableReloadToLocation = false;
			Return_LongwayOfficer();
		break;
		
		case "PZ_PuansieDialogWithLevasser_1":
			dialog.text = "Nous y revoilà, François. Je vois que la vie t'a laissé des séquelles, héhé.";
			link.l1 = "";
			link.l1.go = "PZ_PuansieDialogWithLevasser_1_1";
			LAi_SetHuberType(npchar);
		break;
		case "PZ_PuansieDialogWithLevasser_1_1":
			StartInstantDialog("Levasser", "PZ_PuansieDialogWithLevasser_2", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_PuansieDialogWithLevasser_2":
			dialog.text = "Poincy, espèce de salaud avide... Tu t'es presque étouffé avec l'or dont tes coffres débordent, et tu n'en as toujours pas assez ?";
			link.l1 = "";
			link.l1.go = "PZ_PuansieDialogWithLevasser_2_1";
			CharacterTurnByChr(npchar, CharacterFromID("Puancie"));
		break;
		case "PZ_PuansieDialogWithLevasser_2_1":
			StartInstantDialogNoType("Puancie", "PZ_PuansieDialogWithLevasser_3", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_PuansieDialogWithLevasser_3":
			//LAi_SetActorType(npchar);
			//LAi_ActorSetHuberMode(npchar);
			dialog.text = "Je partagerai un peu avec toi, François. Tu en auras assez, crois-moi.";
			link.l1 = "";
			link.l1.go = "PZ_PuansieDialogWithLevasser_3_1";
			//LAi_tmpl_SetDialog(npchar, pchar, -1.0);
		break;
		case "PZ_PuansieDialogWithLevasser_3_1":
			StartInstantDialog("Levasser", "PZ_PuansieDialogWithLevasser_4", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_PuansieDialogWithLevasser_4":
			dialog.text = "Qu... qu'entends-tu par là ?";
			link.l1 = "";
			link.l1.go = "PZ_PuansieDialogWithLevasser_4_1";
			CharacterTurnByChr(npchar, CharacterFromID("Puancie"));
		break;
		case "PZ_PuansieDialogWithLevasser_4_1":
			StartInstantDialogNoType("Puancie", "PZ_PuansieDialogWithLevasser_5", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_PuansieDialogWithLevasser_5":
			dialog.text = "";
			link.l1 = "Gouverneur général, allez-vous...";
			link.l1.go = "PZ_PuansieDialogWithLevasser_6";
		break;
		
		case "PZ_PuansieDialogWithLevasser_6":
			dialog.text = "Charles, mon ami, tu as fait ton travail et tu l'as fait brillamment ! Ce qui arrivera à cet homme ne devrait pas te concerner... Cependant, il te sera utile de savoir, Capitaine, au cas où ta tête brillante aurait un jour des idées stupides. Un mauvais cas d'indigestion attend notre ami commun, pour ainsi dire. L'or n'est pas bon pour l'estomac, j'ai entendu... J'espère ne pas avoir besoin d'expliquer davantage.";
			link.l1 = "Non, Gouverneur-Général.";
			link.l1.go = "PZ_PuansieDialogWithLevasser_7";
		break;
		
		case "PZ_PuansieDialogWithLevasser_7":
			dialog.text = "Contrairement à Monsieur François, tu as un grand avenir devant toi, Charles. Les gars, emmenez ce porc en prison !";
			link.l1 = "";
			link.l1.go = "PZ_PuansieDialogWithLevasser_7_1";
		break;
		case "PZ_PuansieDialogWithLevasser_7_1":
			StartInstantDialog("Levasser", "PZ_PuansieDialogWithLevasser_8", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_PuansieDialogWithLevasser_8":
			dialog.text = "Bas les pattes, bande de salauds ! Heureux, de Maure ?! Va te faire foutre ! Vous allez tous brûler en enfer, dans la même poêle que moi !";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_LevasserVGostyahUPuansie3");
			CharacterTurnByChr(npchar, CharacterFromID("Puancie"));
			sld = characterFromID("PZ_SoldFra_1");
			CharacterTurnByChr(sld, CharacterFromID("Levasser"));
			sld = characterFromID("PZ_SoldFra_2");
			CharacterTurnByChr(sld, CharacterFromID("Levasser"));
		break;
		
		case "PZ_Baker_1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Kasper";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Sharp";
			dialog.text = "Eh bien, monsieur. J'ai inspecté mademoiselle "+sStr+"... ";
			link.l1 = "À quel point est-ce grave, Raymond ?";
			link.l1.go = "PZ_Baker_2";
		break;
		
		case "PZ_Baker_2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko"))
				{
					dialog.text = "Rien à craindre, Capitaine. Mary a été gravement blessée, bien sûr, mais dans l'ensemble, tout ira bien. Elle devrait rester alitée quelques jours, et je m'attends à ce qu'elle soit de retour en forme dans une quinzaine de jours.";
					link.l1 = "Je vois. Merci, Raymond. Vous pouvez disposer.";
					link.l1.go = "PZ_Baker_4";
				}
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Sredne"))
				{
					dialog.text = "Mary a pris une sacrée raclée, Capitaine. Des bleus, des coupures... et le choc de tout ça, bien sûr - bien qu'elle essaie de ne pas le montrer.";
					link.l1 = "Elle fait bonne figure, comme toujours. Mais je pense qu'elle réalise qu'il vaut mieux qu'elle reste alitée maintenant. Mais pour combien de temps ?";
					link.l1.go = "PZ_Baker_3";
				}
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Tyazhelo"))
				{
					dialog.text = "Même un soldat professionnel aurait du mal à survivre à ce qu'elle a traversé, Capitaine. Entorses, foulures, contusions - nous avons de la chance que ces salauds ne lui aient pas brisé les os. Ses tendons sont endommagés, cependant, elle ne pourra pas manier une lame pendant au moins un mois.";
					link.l1 = "Au diable la lame. Quand pourra-t-elle se tenir debout ?";
					link.l1.go = "PZ_Baker_3";
				}
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko"))
				{
					dialog.text = "Ne t'inquiète pas, Capitaine. Hellen est blessée, mais pas gravement. Elle devra rester alitée pour l'instant, mais je pense qu'elle se rétablira complètement en quelques semaines.";
					link.l1 = "Je vois. Merci, Raymond. Rompez.";
					link.l1.go = "PZ_Baker_4";
				}
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Sredne"))
				{
					dialog.text = "Elle a pris une sacrée raclée, capitaine. Et les blessures physiques ne sont qu'une partie du diagnostic... Être dans cet endroit terrible lui a rappelé le cauchemar qu'elle a vécu sur l'Arbutus.";
					link.l1 = "Bien sûr... bon sang ! Quand sera-t-elle de nouveau sur pied ?";
					link.l1.go = "PZ_Baker_3";
				}
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Tyazhelo"))
				{
					dialog.text = "Helen marchait sur le fil du rasoir, Capitaine. Je suis surpris qu'elle ait survécu après tout ce qu'elle a traversé. Pas de lacérations internes ni de fractures, mais beaucoup d'entorses et de foulures.";
					link.l1 = "Pauvre petite. Combien de temps prendra sa guérison ?";
					link.l1.go = "PZ_Baker_3";
				}
			}
		break;
		
		case "PZ_Baker_3":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Sredne"))
				{
					dialog.text = "Au moins une semaine, monsieur. Si elle suit mes recommandations, elle devrait être de retour en action dans environ un mois.";
				}
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Tyazhelo"))
				{
					dialog.text = "Pas avant quinze jours, monsieur. Après cela, je lui permettrai de courtes promenades sur le gaillard arrière. Une guérison complète prendra au moins deux mois.";
				}
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Sredne"))
				{
					dialog.text = "Ne la dérangez pas pendant au moins une semaine, je vous le dis, monsieur. La guérison complète prendra environ un mois.";
				}
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Tyazhelo"))
				{
					dialog.text = "She should stay in bed for a fortnight; after that, she may be able to walk around the deck. But don't expect to see her back in action for at least two months.";
				}
			}
			link.l1 = "Je vois. Merci, Raymond. Vous pouvez disposer.";
			link.l1.go = "PZ_Baker_4";
		break;
		
		case "PZ_Baker_4":
			DialogExit();
			sld = CharacterFromID("Baker");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "PZ_RazgovorSVrachom_4", -1);
		break;
		
		case "PZ_DevushkaVstalaSKrovati_Dialog1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "C'est plus difficile que je ne le pensais de me tenir debout après être restée allongée si longtemps, ouais, hein ?";
				link.l1 = "Peut-être que tu ne devrais pas arrêter le repos au lit si brusquement, ma chérie.";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Oh-h, ma tête...";
				link.l1 = "Hélène ! Tu n'es pas levée un peu trop tôt ? Tu tiens à peine debout !";
			}
			link.l1.go = "PZ_DevushkaVstalaSKrovati_Dialog2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_DevushkaVstalaSKrovati_Dialog2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Je préférerais brûler ce foutu lit que d'y mentir à nouveau - au moins jusqu'à ce que j'aie marché de la proue à la poupe et retour !";
				link.l1 = "C'est un lit bien confortable. Et ce n'est pas un mauvais navire non plus. Alors je ne vais pas t'arrêter. Mais je serai là pour m'assurer que tu ne fasses rien de stupide.";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Je vais bien, Capitaine, bien que pas complètement. Je ne suis pas encore prêt à brandir une lame, mais je déteste ce lit de toute mon âme.";
				link.l1 = "Eh bien, une petite promenade sur le pont ne te fera probablement pas de mal. Mais ne pense même pas à t'approcher des câbles !";
			}
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_DevushkaStoitVosstanovlenie");
		break;
		
		case "PZ_DevushkaSnovaOfficer_Sex1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Charles, ne penses-tu pas que tu m'as complètement oubliée ? Rappelle-moi la dernière fois que nous avons partagé une couche, ouais, hein ?";
				link.l1 = "Avant... Ne parlons pas de ça, d'accord, Mary ?";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Mon capitaine, ai-je cessé de vous intéresser en tant que femme ?";
				link.l1 = "C'est inattendu, Hélène. D'habitude, c'est moi qui aborde ce sujet... mais je n'étais pas sûr que tu étais prête après...";
			}
			link.l1.go = "PZ_DevushkaSnovaOfficer_Sex2";
			DelLandQuestMark(npchar);
			pchar.questTemp.PZ_DevushkaSnovaOfficer = true;
			DeleteQuestCondition("PZ_DevushkaSnovaOfficer2");
		break;
		
		case "PZ_DevushkaSnovaOfficer_Sex2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Alors parle de moi au moins, ouais, hein. Ou suis-je devenu désagréable pour toi après que ces deux salauds m'ont tabassée ?";
				link.l1 = "C'est la chose la plus stupide que j'aie jamais entendue. Je ne voulais simplement pas te déranger tant que tu n'étais pas prêt. Et puisque tu l'es...";
				link.l1.go = "PZ_DevushkaSnovaOfficer_Sex3";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "C'est bon, Charles, vraiment. J'essaie juste de ne pas y penser. Et puis, tu m'as sauvé du pire. Alors arrêtons de parler et juste... rattrapons le temps perdu.";
				link.l1 = "C'est une sacrée bonne idée, Helen.";
				link.l1.go = "exit";
				AddDialogExitQuest("cabin_sex_go");
			}
		break;
		
		case "PZ_DevushkaSnovaOfficer_Sex3":
				dialog.text = "Charles, je ne le veux pas, je l'exige, ouais, hein ?";
				link.l1 = "Je n'oserais pas vous refuser...";
				link.l1.go = "exit";
				AddDialogExitQuest("cabin_sex_go");
		break;
		
		case "PZ_DevushkaSnovaOfficer_Dialog1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Charles, nous devons parler, ouais, hein ?";
				link.l1 = "Y a-t-il un problème, Mary ? Tu sembles plutôt anxieuse, et cela ne présage généralement rien de bon.";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Mon capitaine, il y a quelque chose que je dois vous dire.";
				link.l1 = "Ah, vraiment, Hélène ? Je t'écoute.";
			}
			link.l1.go = "PZ_DevushkaSnovaOfficer_Dialog2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_DevushkaSnovaOfficer_Dialog2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "C'est justement ça ! N'est-ce pas une bonne chose que je sois prêt à reprendre mes fonctions d'officier ?";
				link.l1 = "Alors c'est ça. Eh bien, si tu te sens assez fort, ce n'est pas juste bien, c'est merveilleux.";
				link.l1.go = "PZ_DevushkaSnovaOfficer_Dialog3";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Je suis fatiguée que l'équipage me regarde comme si j'étais une vieille femme faible. Je veux retourner à la barre et étendre mes bras en m'exerçant avec une lame...";
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko"))
				{
					link.l1 = "Si tu te sens prêt, je ne m'y opposerai pas, cher. Je vais chercher ton équipement. Et je te laisserai prendre la barre avec plaisir. Mais fais attention lors d'un combat, ouais, hein ?";
					link.l1.go = "PZ_DevushkaSnovaOfficer_Dialog2_1";
				}
				else
				{
					link.l1 = "Tu nous as manqué sur le pont, Hélène. Quant à l'épée, je pense qu'il est temps que tu la récupères.";
					link.l1.go = "PZ_DevushkaSnovaOfficer_Dialog3";
				}
			}
		break;
		
		case "PZ_DevushkaSnovaOfficer_Dialog2_1":
			dialog.text = "Bien sûr, Mon Capitaine, comme vous le dites.";
			link.l1 = "Bien.";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_DevushkaSnovaOfficer3");
		break;
		
		case "PZ_DevushkaSnovaOfficer_Dialog3":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Merveilleux, ouais, hein ? Je suis impatient de m'entraîner avec la lame...";
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko"))
				{
					link.l1 = "Ravi de l'entendre, Mary. Mais ne te jette pas encore dans la mêlée... Mais à qui est-ce que je raconte ça ?";
					link.l1.go = "exit";
					AddDialogExitQuest("PZ_DevushkaSnovaOfficer3");
				}
				else
				{
					link.l1 = "Je suppose que tu seras heureux de voir ce palash de retour dans son fourreau...";
					link.l1.go = "PZ_DevushkaSnovaOfficer_Dialog4";
				}
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Je... je ne sais pas quoi dire, Charles. Je viens juste de réaliser à quel point ce sabre compte pour moi...";
				link.l1 = "Je le savais depuis longtemps, c'est pour cela qu'il vous attendait sain et sauf.";
				link.l1.go = "PZ_DevushkaSnovaOfficer_Dialog4";
				notification("Gave Cutlass of Blaze", "None");
				PlaySound("interface\important_item.wav");
			}
		break;
		
		case "PZ_DevushkaSnovaOfficer_Dialog4":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Mon narval, ouais, hein !!! Charles, tu l'as sauvé ! Je ne suis pas juste heureuse, je suis ravie ! Merci, merci ! J'avais tellement peur qu'il soit resté sur le navire de Martin...";
				link.l1 = "Cette lame appartient à ta main, mon Talisman Rouge. J'ai confiance que tu ne la perdras plus... Eh bien, je ne m'opposerai pas à vos retrouvailles, ha-ha !";
				notification("Gave Narwhal", "None");
				PlaySound("interface\important_item.wav");
				link.l1.go = "exit";
				AddDialogExitQuest("PZ_DevushkaSnovaOfficer3");
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Merci, Charles. Tu sais, c'est probablement pour ça que je t'aime...";
				link.l1 = "Pour ramener des choses perdues ? Ha ha ha ha...";
				link.l1.go = "PZ_DevushkaSnovaOfficer_Dialog5";
			}
		break;
		
		case "PZ_DevushkaSnovaOfficer_Dialog5":
			dialog.text = "Tu ris, mais je suis sérieux.";
			link.l1 = "Je sais, Hélène. Je t'aime aussi, bien que je ne sois toujours pas sûr pourquoi.";
			link.l1.go = "PZ_DevushkaSnovaOfficer_Dialog6";
		break;
		
		case "PZ_DevushkaSnovaOfficer_Dialog6":
			dialog.text = "Peut-être parce que je n'ai pas encore utilisé ce sabre sur toi.";
			link.l1 = "Je me sauverai de cela en me dirigeant vers les bateaux. Je t'attendrai là-bas, Hélène.";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_DevushkaSnovaOfficer3");
		break;
	}
} 