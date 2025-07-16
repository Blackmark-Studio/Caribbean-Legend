void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, n, iTemp;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	bool ok;
    int iTest;
    ref rColony;
    string sFrom_sea = "";
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "exit";
		break;
		
		//вестовой
		case "Regata_Cureer":
			dialog.text = "Bonjour. Etes-vous capitaine "+GetFullName(pchar)+"?";
			link.l1 = "Oui, c'est moi. Et quel est l'affaire ?";
			link.l1.go = "Regata_Cureer_1";
		break;
		
		case "Regata_Cureer_1":
			dialog.text = "J'ai une lettre pour vous de la part du gouverneur de la Jamaïque, monsieur Edward Doily.";
			link.l1 = "Ouah ! Je ne m'attendais pas à ça... Et que veut le gouverneur de moi ?";
			link.l1.go = "Regata_Cureer_2";
		break;
		
		case "Regata_Cureer_2":
			dialog.text = "Lisez la lettre, monsieur. En bref, on vous propose de participer à la régate, une course à travers tout l'archipel. Les rumeurs sur vos compétences navales et votre vitesse remarquable en navigation n'ont pas passé inaperçues.";
			link.l1 = "Incroyable ! Eh bien, je... je vais y réfléchir.";
			link.l1.go = "Regata_Cureer_3";
			GiveItem2Character(pchar, "letter_open");
			ChangeItemDescribe("letter_open", "itmdescr_letter_open_Regata");
			AddQuestRecordInfo("RegataLetter", "1");
		break;
		
		case "Regata_Cureer_3":
			if (Pchar.BaseNation == SPAIN || Pchar.BaseNation == HOLLAND)
			{
				dialog.text = "Je dois également vous fournir un accès gratuit au port de Port Royal. Voici une licence pour 30 jours. Maintenant, ma mission est terminée. Adieu, capitaine.";
				link.l1 = "Merci. Le permis est le bienvenu. Adieu !";
				link.l1.go = "Cureer_exit";
				GiveNationLicence(HOLLAND, 30);
			}
			else
			{
				dialog.text = "Bien. Maintenant, ma mission est accomplie. Adieu, capitaine.";
				link.l1 = "Adieu !";
				link.l1.go = "Cureer_exit";
			}
		break;
		
		case "Cureer_exit":
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", -1);
			pchar.questTemp.Regata.ToPortRoyal = "true";
			SetQuestHeader("Regata");
			AddQuestRecord("Regata", "1");
		break;
		
		//распорядитель регаты
		case "Regata_Head":
			if (CheckAttribute(pchar, "questTemp.Regata.Begin"))
			{
				dialog.text = "Bonjour. Vous participez à la régate, je suppose ?";
				link.l1 = "Précisément, monsieur. Je me nomme "+GetFullName(pchar)+". J'ai reçu l'invitation.";
				link.l1.go = "Regata_Head_1";
			}
			else
			{
				dialog.text = "Vous désirez quelque chose, monsieur ?";
				link.l1 = "Non, ce n'est rien. Je pars déjà.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Regata_Head";
			}
		break;
		
		case "Regata_Head_1":
			iTest = FindColony("PortRoyal"); 
			if (iTest != -1)
			{
				rColony = GetColonyByIndex(iTest);
			}
			ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
			if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)//проверка на наличие корабля в порту
			{
				dialog.text = "Je suis heureux de vous rencontrer, capitaine "+GetFullName(pchar)+". Commençons alors. Vous êtes déjà au courant des bases grâce à la lettre, n'est-ce pas ? Uniquement des lougres, et elle doit être le seul navire de votre escadron pour participer à la régate. Avez-vous rempli ces conditions ?";
				// belamour legendary edition допускаем курьерский люггер 
				ok = sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_LUGGER || sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_CAREERLUGGER;
				if((GetCompanionQuantity(pchar) > 1) || !ok)
				{
					link.l1 = "Pas encore. Je vais le faire maintenant et je reviendrai bientôt.";
					link.l1.go = "exit";
					NextDiag.TempNode = "Regata_Head_repeat";
				}
				else
				{
					link.l1 = "Oui, j'ai.";
					link.l1.go = "Regata_Head_2";
				}
			}
			else
			{
				dialog.text = "Vous êtes venu participer à la régate, mais où est votre navire, capitaine ?";
				link.l1 = "Excusez-moi, monsieur. Je vais amener mon navire au port immédiatement.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Regata_Head_repeat";
			}
		break;
		
		case "Regata_Head_repeat":
			if (CheckAttribute(pchar, "questTemp.Regata.Begin"))
			{
				iTest = FindColony("PortRoyal"); 
				if (iTest != -1)
				{
					rColony = GetColonyByIndex(iTest);
				}
				ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
				if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)//проверка на наличие корабля в порту
				{
					ok = sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_LUGGER || sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_CAREERLUGGER;
					dialog.text = "Ah, c'est encore vous. Avez-vous tout fait pour remplir les conditions de la régate ?";
					// belamour legendary edition допускаем курьерский люггер 
					if ((GetCompanionQuantity(pchar) > 1) || !ok)
					{
						link.l1 = "Pas encore. Je vais le faire maintenant et je reviendrai bientôt.";
						link.l1.go = "exit";
						NextDiag.TempNode = "Regata_Head_repeat";
					}
					else
					{
						link.l1 = "Oui, j'ai.";
						link.l1.go = "Regata_Head_2";
					}
				}
				else
				{
					dialog.text = "Capitaine, nous n'avons rien à discuter tant que je ne vois pas votre navire en rade. Me comprenez-vous ou dois-je me répéter ?";
					link.l1 = "Excusez-moi, monsieur. Je vais amener mon navire au port immédiatement.";
					link.l1.go = "exit";
					NextDiag.TempNode = "Regata_Head_repeat";
				}
			}
			else
			{
				dialog.text = "Vous desirez quelque chose, monsieur ?";
				link.l1 = "Non... c'est rien. Je pars déjà.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Regata_Head";
			}
		break;
		
		case "Regata_Head_2":
			dialog.text = "Très bien. Maintenant, le point suivant. Quel est le nom de votre navire?";
			link.l1 = "'"+pchar.Ship.Name+" '.";
			link.l1.go = "Regata_Head_3";
		break;
		
		case "Regata_Head_3":
			dialog.text = "Puisque la régate est organisée par les autorités anglaises et en raison des règles établies, le nom de votre navire doit être changé pour la durée de l'événement. Ne vous inquiétez pas, cela concerne chaque participant.";
			link.l1 = "Ils disent que c'est un mauvais présage de changer le nom de son navire.";
			link.l1.go = "Regata_Head_4";
		break;
		
		case "Regata_Head_4":
			dialog.text = "Vous pouvez changer le nom après la régate. Ainsi, votre lougre portera le nom 'Sainte Catherine'.";
			link.l1 = "Je comprends, monsieur, je changerai le nom.";
			link.l1.go = "Regata_Head_5";
			pchar.Ship.Name = "Saint Catherine";
		break;
		
		case "Regata_Head_5":
			dialog.text = "Maintenant, parlons de la régate elle-même. Écoutez attentivement. Je vous fournirai également un document avec les règles.\nLa régate commence et se termine à Port Royal. Il y a cinq points que vous devrez atteindre.\nLe premier est de Port Royal à Belize, Côte Ouest\nLe deuxième est de Belize à Port-au-Prince, Hispaniola\nLe troisième est de Port-au-Prince à St. John's, Antigua\nLe quatrième est de St. John's à Bridgetown, Barbade\nEt le dernier est de Bridgetown à Port Royal\nEst-ce clair ?";
			link.l1 = "Clair comme de l'eau de roche, monsieur.";
			link.l1.go = "Regata_Head_6";
		break;
		
		case "Regata_Head_6":
			dialog.text = "Splendide. Vous devez vous enregistrer à chaque bureau portuaire des villes suivantes : Belize, Port-au-Prince, St.John's, Bridgetown. Vous serez disqualifié si vous manquez l'une de ces villes ou si vous brisez la bonne séquence.\nLes bureaux resteront ouverts vingt-quatre heures pendant le déroulement de la régate. Frappez à la porte et ils vous laisseront entrer.";
			link.l1 = "Compris.";
			link.l1.go = "Regata_Head_7";
		break;
		
		case "Regata_Head_7":
			dialog.text = "Il est interdit de changer de navire et d'ajouter plus de navires à votre escadre. Cela sera vérifié dans chaque ville, tenez-en compte.";
			link.l1 = "Je vais y réfléchir. Qui est normalement considéré comme un vainqueur et pouvons-nous parler des prix ?";
			link.l1.go = "Regata_Head_8";
		break;
		
		case "Regata_Head_8":
			dialog.text = "Il n'y a qu'un seul vainqueur dans la régate - le capitaine dont le navire sera le premier à atteindre Port-Royal. Le prix est très précieux. Le vainqueur recevra une grosse somme - 250 000 pesos. De plus, il se verra offrir un ensemble de cadeaux précieux.";
			link.l1 = "Alors, les perdants n'obtiennent rien ?";
			link.l1.go = "Regata_Head_9";
		break;
		
		case "Regata_Head_9":
			dialog.text = "Exactement. De plus, beaucoup de riches et de pauvres citoyens des colonies anglaises parient sur le vainqueur de la régate. Vous pouvez aussi parier sur... vous-même. En général, chaque capitaine le fait. Si vous gagnez, vous gagnerez encore plus et n'oubliez pas la motivation. Habituellement, j'accepte les paris\nPariez-vous sur votre victoire ?";
			link.l1 = "Ha ! Bien sûr que je le suis. Combien puis-je parier ?";
			link.l1.go = "Regata_rate";
			link.l2 = "Je vais y réfléchir. Peut-être que je parierai.";
			link.l2.go = "Regata_Head_10";
		break;
		
		case "Regata_Head_10":
			if (CheckAttribute(pchar, "questTemp.Regata.Begin"))
			{
				dialog.text = "Reflechissez si vous voulez. Vous avez un peu de temps avant que la regate ne commence.";
				link.l1 = "D'accord. Quand cela commence-t-il ?";
				link.l1.go = "Regata_Head_11";
				DeleteAttribute(pchar, "questTemp.Regata.Rate");
				pchar.questTemp.Regata.Ratenext = "true";
			}
			else
			{
				dialog.text = "Réfléchis si tu veux. Tu as un peu de temps avant que la régate commence.";
				link.l1 = "Très bien.";
				link.l1.go = "exit";
			}
		break;
		
		case "Regata_Head_11":
			CreateRegataAdversaries();
			dialog.text = "Dans trois jours, à midi. Venez sur le quai, et ne soyez pas en retard. Vous aurez cinq concurrents.\n"+pchar.questTemp.Regata.AdversaryName.a+", du "+pchar.questTemp.Regata.AdversaryShipName.a+"\n"+pchar.questTemp.Regata.AdversaryName.b+", du "+pchar.questTemp.Regata.AdversaryShipName.b+"\n"+pchar.questTemp.Regata.AdversaryName.c+", du "+pchar.questTemp.Regata.AdversaryShipName.c+"\n"+pchar.questTemp.Regata.AdversaryName.d+", du "+pchar.questTemp.Regata.AdversaryShipName.d+"\n"+pchar.questTemp.Regata.AdversaryName.e+", du "+pchar.questTemp.Regata.AdversaryShipName.e+"\nTous sont des capitaines chevronnés. Eh bien, apparemment c'est tout. Prends le règlement au cas où. À bientôt au départ!";
			link.l1 = "Adieu, monsieur.";
			if (Pchar.BaseNation == SPAIN || Pchar.BaseNation == HOLLAND) link.l1.go = "Regata_Head_13";
			else link.l1.go = "Regata_Head_12";
		break;
		
		case "Regata_Head_12":
			DialogExit();
			pchar.quest.RegataToPortRoyalTimeOver.over = "yes";//снять таймер
			SetFunctionTimerCondition("Regata_SetTime", 0, 0, 3, false);
			pchar.quest.Regata_Lost.win_condition.l1 = "Timer";
			pchar.quest.Regata_Lost.win_condition.l1.date.hour  = 13.0;
			pchar.quest.Regata_Lost.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 3);
			pchar.quest.Regata_Lost.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 3);
			pchar.quest.Regata_Lost.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 3);
			pchar.quest.Regata_Lost.function = "Regata_Lost";
			pchar.quest.Regata_Start.win_condition.l1 = "Timer";
			pchar.quest.Regata_Start.win_condition.l1.date.hour  = 12.0;
			pchar.quest.Regata_Start.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 3);
			pchar.quest.Regata_Start.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 3);
			pchar.quest.Regata_Start.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 3);
			pchar.quest.Regata_Start.win_condition.l2 = "locator";
			pchar.quest.Regata_Start.win_condition.l2.location = "Portroyal_town";
			pchar.quest.Regata_Start.win_condition.l2.locator_group = "reload";
			pchar.quest.Regata_Start.win_condition.l2.locator = "reload1_back";
			pchar.quest.Regata_Start.function = "Regata_Start";
			AddQuestRecordInfo("RegataRules", "1");
			NextDiag.CurrentNode = "Regata_Prepare";
			DeleteAttribute(pchar, "questTemp.Regata.Begin");
			pchar.questTemp.Regata.Prepare = "true";
			AddQuestRecord("Regata", "2");
		break;
		
		case "Regata_Head_13":
			dialog.text = "Attendez ! Je vous donnerai la licence de 30 jours pour visiter les ports anglais et français. La régate ne durera pas plus d'un mois. S'il vous plaît, prenez-la.";
			link.l1 = "Merci !";
			link.l1.go = "Regata_Head_12";
			GiveNationLicence(HOLLAND, 30);
		break;
		
		case "Regata_rate":
			dialog.text = "Combien paries-tu?";
			link.l1 = "";
			Link.l1.edit = 4;
			link.l1.go = "Regata_rate_1";
			link.l2 = "Je suppose que j'ai encore besoin de temps pour réfléchir.";
			link.l2.go = "Regata_Head_10";
		break;
		
		case "Regata_rate_1":
			int iQty = sti(dialogEditStrings[4]);
			pchar.questTemp.Regata.Rate = sti(iQty);
			if (iQty < 10000)
			{
				dialog.text = "Monsieur, ce n'est point drôle, ni amusant. Je ne travaillerai pas pour une somme si dérisoire.";
				link.l1 = "Pardonnez-moi... Réexaminons la mise.";
				link.l1.go = "Regata_rate";
				break;
			}
			if (iQty > 100000)
			{
				dialog.text = "Monsieur, je ne peux accepter de tels enjeux en raison des règles de la régate. Réduisez-les à une valeur raisonnable.";
				link.l1 = "C'est dommage. Réfléchissons à nouveau sur la somme.";
				link.l1.go = "Regata_rate";
				break;
			}
			dialog.text = ""+iQty+"? C'est un bon enjeu. Je suis prêt à l'accepter. Votre argent, monsieur ?";
			if (makeint(Pchar.money) >= sti(pchar.questTemp.Regata.Rate))
			{
				link.l1 = "S'il vous plaît, prenez-le.";
				link.l1.go = "Regata_rate_2";
			}
			link.l2 = "Je n'ai pas assez de pieces maintenant. Je viendrai te voir plus tard et nous miserons. Et j'y reflechirai davantage, peut-etre que je reconsidererai la somme.";
			link.l2.go = "Regata_Head_10";
		break;
		
		case "Regata_rate_2":
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.Regata.Rate));
			pchar.questTemp.Regata.Advantage = sti(pchar.questTemp.Regata.Rate)*(1.5+frand(1.5)); // dlc
			dialog.text = "Splendide ! Maintenant, tout ce que vous avez à faire est d'être le premier et le prix sera à vous. Sa valeur finale pourrait varier, tout dépend de combien de personnes miseront sur vous à la fin.";
			if (!CheckAttribute(pchar, "questTemp.Regata.Ratenext"))
			{
				link.l1 = "Je vois. Quand commence la régate ?";
				link.l1.go = "Regata_Head_11";
			}
			else
			{
				link.l1 = "Je vois. J'attendrai le début. À bientôt !";
				link.l1.go = "exit";
				DeleteAttribute(pchar, "questTemp.Regata.Ratenext");
				NextDiag.TempNode = "Regata_Prepare";
			}
		break;
		
		case "Regata_Prepare":
			dialog.text = "Ah vous êtes ici encore, capitaine "+GetFullName(pchar)+"? Que veux-tu ?";
			if (!CheckAttribute(pchar, "questTemp.Regata.Rate"))
			{
				link.l1 = "Je veux parier sur ma victoire.";
				link.l1.go = "Regata_rate";
			}
			link.l2 = "Non, ce n'est rien. Je voulais juste te saluer.";
			link.l2.go = "exit";
			NextDiag.TempNode = "Regata_Prepare";
		break;
		
		//старт регаты
		case "Regata_CitMan":
			dialog.text = RandPhraseSimple(LinkRandPhrase("Capitaine, es-tu un novice? Laisse-moi te dire que tu devrais être prudent. Tes concurrents pourraient te réserver quelques surprises très désagréables...","Capitaine, j'ai misé sur vous. Ne me décevez pas!","Capitaine, les habitants des ports de la régate pourraient vous proposer d'acheter quelque chose. Cela peut souvent être vraiment utile. Prenez cela en compte."),LinkRandPhrase("Bon voyage, capitaine !","Capitaine, faites attention, les Castillans chassent souvent les luggers des participants dans les eaux espagnoles.","J'ai entendu dire que des personnages louches proposent souvent leurs 'services' aux capitaines de régate. C'est à vous de décider d'accepter ou non leurs offres."));
			link.l1 = "Oui, oui, bien sûr... merci, je suppose.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Regata_CitMan";
		break;
		
		case "Regata_CitWom":
			dialog.text = LinkRandPhrase("Capitaine, mon mari et moi avons parié dix mille sur votre victoire. Ne nous laissez pas tomber ! Je prierai pour vous !","Capitaine ! Je vous souhaite bonne chance !","Hum... tu es un capitaine si brave et courageux...");
			link.l1 = "D'accord, mon ami.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Regata_CitWom";
		break;
		
		case "Regata_CitHorse":
			dialog.text = LinkRandPhrase("Hey, marin ! Salue la beauté ! Je t'attendrai à ton retour !","Eh, marin salé ! Madame a dit qu'elle me donnerait en prix au gagnant de la régate gratuitement... Essaye de gagner, tu es si beau !","N'oubliez pas de nous rendre visite quand vous serez de retour, beau gosse, nous vous ferons plaisir selon les plus hauts standards !");
			link.l1 = "Eh bien, ah... J'y réfléchirai, merci !";
			link.l1.go = "exit";
			NextDiag.TempNode = "Regata_CitHorse";
		break;
		
		case "Regata_Prepare_1":
			if (sti(environment.time) < 12.0)
			{
				dialog.text = "Capitaine, la régate commence à midi. Vous pouvez vous reposer maintenant, nous préparons la fête. Revenez à midi, vos concurrents feront de même.";
				link.l1 = "Très bien, monsieur ! J'attendrai le début...";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Vous voilà, capitaine.";
				link.l1 = "Moi et mon equipage sommes prets, monsieur! J'attends le depart...";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Regata_Prepare_1";
		break;
		
		case "Regata_Start":
			dialog.text = "Alors, messieurs, nous y voilà. J'annonce le début de la régate. Vous connaissez les règles. Celui qui reviendra ici le premier sera acclamé comme vainqueur. Mesdames et messieurs, souhaitons bonne chance à nos courageux capitaines !\nMessieurs ! Êtes-vous prêts ? Prêts ! À vos marques ! Partez !";
			link.l1 = "D'accord...";
			link.l1.go = "Regata_Start_1";
		break;
		
		case "Regata_Start_1":
			DialogExit();
			PlaySound("people fight\mushketshot.wav");
			log_info("The regatta has started! Get aboard! Head to Belize!");
			for (i=1; i <=5; i++)
			{
				sld = characterFromId("Regata_Cap_F"+i);
				LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "", -1);
			}
			Island_SetReloadEnableGlobal("Jamaica", false);//на остров нельзя
			SetFunctionTimerCondition("ReturnJamaicaNorm", 0, 0, 1, false);//таймер на возврат нормы
			LocatorReloadEnterDisable("Portroyal_town", "reload1_back", false);//откроем выход в море
			DeleteAttribute(pchar, "questTemp.Regata.Prepare");
			pchar.questTemp.Regata.Go = "true";
			pchar.questTemp.Regata.Town = "Beliz";
			pchar.quest.Regata_PU.win_condition.l1 = "locator";
			pchar.quest.Regata_PU.win_condition.l1.location = "Beliz_town";
			pchar.quest.Regata_PU.win_condition.l1.locator_group = "reload";
			pchar.quest.Regata_PU.win_condition.l1.locator = "reload10_back";
			pchar.quest.Regata_PU.win_condition.l2 = "Night";
			pchar.quest.Regata_PU.function = "RegataPU_Open";//вход в ПУ ночью
			//ситуации
			pchar.quest.Regata_ShYarder.win_condition.l1 = "location";
			pchar.quest.Regata_ShYarder.win_condition.l1.location = "Beliz_town";
			pchar.quest.Regata_ShYarder.function = "RegataShipyarder";
			sld = characterFromId("Beliz_shipyarder");
			LAi_RemoveLoginTime(sld);
			AddQuestRecord("Regata", "3");
		break;
		//старт регаты
		
		//верфист с парусами
		case "Regata_Shipyarder":
			dialog.text = "Salutations, capitaine ! On m'a informé que vous participez à la régate des Caraïbes.";
			link.l1 = "Il est vrai. Les nouvelles se répandent vraiment à travers l'archipel plus vite qu'un vent.";
			link.l1.go = "Regata_Shipyarder_1";
		break;
		
		case "Regata_Shipyarder_1":
			dialog.text = "Ils le font, capitaine. J'ai une proposition pour vous. Cela concerne votre navire et la régate.";
			link.l1 = "Eh ! Intéressant. Je vous écoute, monsieur.";
			link.l1.go = "Regata_Shipyarder_2";
		break;
		
		case "Regata_Shipyarder_2":
			dialog.text = "J'ai un jeu de voiles parfaites pour un lougre, elles sont faites du meilleur coton. Ces voiles augmenteront l'accélération de votre navire et vous donneront un avantage de temps sur vos adversaires\nJe suis prêt à vous les vendre, c'est-à-dire, si vous voulez les acheter.";
			link.l1 = "Combien voulez-vous pour ces voiles ?";
			link.l1.go = "Regata_Shipyarder_3";
		break;
		
		case "Regata_Shipyarder_3":
			dialog.text = "Seulement 15 000 pesos. Vous devez admettre que c'est un prix très modeste pour une... situation comme celle-ci.";
			if (makeint(Pchar.money) >= 15000)
			{
				link.l1 = "Je suis d'accord. J'achete ces nouvelles voiles pour mon lougre. Tenez, prenez votre argent monsieur. Auriez-vous la gentillesse de les livrer à mon navire pendant que je m'enregistre.";
				link.l1.go = "Regata_Shipyarder_4";
			}
			link.l2 = "Je n'ai pas une telle somme. Donc je ne pourrai pas acheter vos voiles.";
			link.l2.go = "Regata_Shipyarder_exit";
		break;
		
		case "Regata_Shipyarder_4":
			AddMoneyToCharacter(pchar, -15000);
			dialog.text = "Ce sera fait, monsieur. Mes hommes n'attendent que le signal, et je vous promets que vous ne le regretterez pas. De plus, ces voiles sont joliment colorées en bleu. Votre beauté l'appréciera.";
			link.l1 = "D'accord alors ! Eh bien, je dois y aller et toi, occupe-toi des voiles.";
			link.l1.go = "Shipyarder_exit";
			for (i=1; i <=5; i++)
			{
				if (i==1) sTemp = "a";
				if (i==2) sTemp = "b";
				if (i==3) sTemp = "c";
				if (i==4) sTemp = "d";
				if (i==5) sTemp = "e";
				pchar.questTemp.Regata.AdversarySecondTransition.Time.(sTemp) = sti(pchar.questTemp.Regata.AdversarySecondTransition.Time.(sTemp))+12;//выиграл 12 часов у всех
				log_testinfo(FindRussianDaysString(pchar.questTemp.Regata.AdversarySecondTransition.Time.(sTemp)));
			}
			RealShips[sti(Pchar.Ship.Type)].ship.upgrades.sails = 3;
			SetSailsColor(Pchar, 5);
			AddQuestRecord("Regata", "28");
		break;
		
		case "Regata_Shipyarder_exit":
			dialog.text = "Quel dommage. Eh bien, c'est ton choix. Adieu, capitaine.";
			link.l1 = "Adieu!";
			link.l1.go = "Shipyarder_exit";
			pchar.questTemp.Regata.AdversarySecondTransition.Time.d = sti(pchar.questTemp.Regata.AdversarySecondTransition.Time.d)-16;//четвертый соперник выиграл 16 часов
			log_testinfo(FindRussianDaysString(pchar.questTemp.Regata.AdversarySecondTransition.Time.e));
			AddQuestRecord("Regata", "29");
		break;
		
		case "Shipyarder_exit":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload5_back", "Beliz_Shipyard", "sit", "sit1", "ReturnRegataSYNorm", 5);
		break;
		//верфист с парусами
		
		//контрики с пушками
		case "Regata_Contra":
			dialog.text = "Bonjour, capitaine "+GetFullName(pchar)+". Nous devons vous parler... en fait, c'est juste une... proposition d'affaires.";
			link.l1 = "Hum. Intéressant, et comment sais-tu qui je suis ?";
			link.l1.go = "Regata_Contra_1";
		break;
		
		case "Regata_Contra_1":
			dialog.text = "Que puis-je dire, on m'a toujours dit que j'avais un don... Ha-ha, eh bien la Régate bat son plein et vous y participez, vous êtes un capitaine célèbre !";
			link.l1 = "Je vois. Eh bien, dis ce que tu penses.";
			link.l1.go = "Regata_Contra_2";
		break;
		
		case "Regata_Contra_2":
			if (sti(pchar.questTemp.Regata.Index != 1))
			{
				sTemp = pchar.questTemp.Regata.ContraIndex;
				dialog.text = "Nous savons qu'il y a encore un participant devant vous - "+pchar.questTemp.Regata.AdversaryName.(sTemp)+" de la "+pchar.questTemp.Regata.AdversaryShipName.(sTemp)+". Il a quitté le port il n'y a pas longtemps et bientôt il passera par le cap des Gonaives.";
			}
			else
			{
				dialog.text = "Nous savons qu'il y a encore un participant juste derrière vous - "+pchar.questTemp.Regata.AdversaryName.b+" de la "+pchar.questTemp.Regata.AdversaryShipName.b+". Il sera ici dans quelques heures.";
			}
			link.l1 = "Hmm... vous êtes très bien informé.";
			link.l1.go = "Regata_Contra_3";
		break;
		
		case "Regata_Contra_3":
			if (sti(pchar.questTemp.Regata.Index != 1)) sTemp = "letting you pass ahead of him and take his position";
			else sTemp = "therefore you will be taking a lead for a long time";
			dialog.text = "Absolument. Maintenant, allons droit au but. Nous vous offrons notre aide contre votre argent. Nous avons placé quatre canons de notre navire au cap derrière la baie de Gonaives. Tout navire de régate doit le contourner\nLes canons sont chargés de boulets à chaînes. Si nous faisons affaire, je dirai à nos amis canonniers de ruiner les voiles de votre concurrent, afin qu'il soit obligé de perdre du temps à les réparer, "+sTemp+".";
			link.l1 = "Combien veux-tu pour ce service ?";
			link.l1.go = "Regata_Contra_4";
			link.l2 = "Non. Je ne vais pas utiliser de tels moyens pour gagner. Vous vous êtes trompés à mon sujet. Adieu, messieurs.";
			link.l2.go = "Regata_Contra_exit";
		break;
		
		case "Regata_Contra_exit":
			dialog.text = "Eh bien capitaine, c'est votre choix. Adieu.";
			link.l1 = "Merci pour l'information sur le cap. Je l'éviterai.";
			link.l1.go = "Contra_exit";
			AddQuestRecord("Regata", "31");
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
		break;
		
		case "Regata_Contra_4":
			if (sti(pchar.questTemp.Regata.Index != 1)) iTemp = 50000;
			else iTemp = 30000;
			dialog.text = "Pas grand-chose. Seulement "+iTemp+" pesos. Et un de vos concurrents perdra presque deux jours à cause de... un accident, ha-ha!";
			if (makeint(Pchar.money) >= iTemp)
			{
				link.l1 = "Heh ! Tu parles avec sagesse, mon ami ! Je paie. Mais quelles garanties ai-je que tu feras ton travail ? Et que tu ne tireras pas sur mon navire quand je passerai le cap ?";
				link.l1.go = "Regata_Contra_5";
			}
			link.l2 = "Je n'ai pas une telle somme. Donc, je ne pourrai pas utiliser vos services.";
			link.l2.go = "Regata_Contra_exit";
		break;
		
		case "Regata_Contra_5":
			dialog.text = "Capitaine je vous en prie, nous sommes des contrebandiers, pas des pirates. Nous sommes tous des hommes honnêtes... à notre manière. Vous avez dû utiliser nos services auparavant, n'est-ce pas ? Vous avez ma parole. Vous pouvez compter dessus.";
			link.l1 = "Assez juste, très bien prends ton argent.";
			link.l1.go = "Regata_Contra_6";
		break;
		
		case "Regata_Contra_6":
			AddQuestRecord("Regata", "30");
			ChangeCharacterComplexReputation(pchar, "nobility", -3);
			dialog.text = "Tu seras ravi par cette affaire, capitaine. Et je vais en informer mes canonniers immédiatement. Bonne chance !";
			link.l1 = "Toi de même...";
			link.l1.go = "Contra_exit";
			if (sti(pchar.questTemp.Regata.Index != 1))
			{
				AddMoneyToCharacter(pchar, -50000);
				sTemp = pchar.questTemp.Regata.ContraIndex;
				pchar.questTemp.Regata.AdversaryThirdTransition.Time.(sTemp) = sti(pchar.questTemp.Regata.AdversaryThirdTransition.Time.(sTemp))+48;//задержка на 48 часов
				log_testinfo(FindRussianDaysString(pchar.questTemp.Regata.AdversaryThirdTransition.Time.(sTemp)));
			}
			else
			{
				AddMoneyToCharacter(pchar, -30000);
				pchar.questTemp.Regata.AdversaryThirdTransition.Time.b = sti(pchar.questTemp.Regata.AdversaryThirdTransition.Time.b)+36;//задержка на 36 часов
				log_testinfo(FindRussianDaysString(pchar.questTemp.Regata.AdversaryThirdTransition.Time.b));
			}
		break;
		
		case "Contra_exit":
			DialogExit();
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("RegataContra_"+i);
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "quest", "quest2", "none", "", "", "", 10.0);
			}
		break;
		//контрики с пушками
		
		//падре
		case "Regata_Padre":
			pchar.questTemp.Regata.BranderName = GenerateRandomNameToShip(ENGLAND);
			dialog.text = "Bonne journée à vous, mon fils. Je tiens à vous saluer et à vous demander humblement : voulez-vous contribuer au trésor de la paroisse en tant que loyal serviteur de l'Angleterre et de notre grand Seigneur ?";
			link.l1 = "Mon père, les gens font la charité par l'appel de leur âme, non par contrainte. Je commence à penser que tout le monde dans l'archipel a décidé de dépouiller les capitaines de la régate...";
			link.l1.go = "Regata_Padre_exit";
			link.l2 = "Bien sûr, saint père. Combien serait suffisant ?";
			link.l2.go = "Regata_Padre_1";
		break;
		
		case "Regata_Padre_1":
			dialog.text = "Autant que te le permettront ton désir et tes possibilités, mon fils. Notre paroisse sera reconnaissante pour la moindre somme.";
			Link.l1.edit = 4;			
			link.l1 = "";
			link.l1.go = "Regata_Padre_2";
		break;
		
		case "Regata_Padre_2":
			iTemp = sti(dialogEditStrings[4]);
			if (iTemp <= 0 || sti(pchar.money) < iTemp)
			{
				dialog.text = "C'est une mauvaise attitude, mon fils. Nous avons tous des péchés, n'oublie pas ton âme. Tu devras te présenter devant notre Créateur... et peut-être bientôt.";
				link.l1 = "Je n'ai pas besoin de vos sermons, saint père. Adieu.";
				link.l1.go = "Padre_exit";
				ChangeCharacterComplexReputation(pchar, "nobility", -3);
				AddQuestRecord("Regata", "35");
				break;
			}
			if (iTemp > 0 && iTemp <= 1000)//ничего не скажет
			{
				dialog.text = "Notre paroisse et moi vous remercions pour ce modeste présent.";
				link.l1 = "Vous êtes le bienvenu, saint père.";
				link.l1.go = "Padre_exit";
				AddMoneyToCharacter(pchar, -iTemp);
				AddQuestRecord("Regata", "35");
			}
			if (iTemp > 1000 && iTemp <= 5000)//1 категория - намекнет
			{
				dialog.text = "Notre paroisse et moi vous remercions pour ce don. Et je veux vous avertir, mon fils, que certains hommes pécheurs ont l'intention de vous nuire. Soyez prudent en mer !";
				link.l1 = "Mon père, chaque jour des gens complotent contre moi... Mais merci de vous soucier de mon sort.";
				link.l1.go = "Padre_exit";
				AddMoneyToCharacter(pchar, -iTemp);
				AddQuestRecord("Regata", "34");
				AddQuestUserData("Regata", "sMoney", iTemp);
			}
			if (iTemp > 5000 && iTemp <= 10000)//2 категория - скажет
			{
				dialog.text = "Je vous remercie au nom de notre paroisse pour ce précieux cadeau. En retour, je veux vous avertir que de très mauvaises gens complotent contre vous. J'ai entendu dire que ces vils apostats vont couler votre navire ici même dans ce port\nIls ont déjà préparé un navire rempli de poudre pour cet acte malveillant. Faites attention, mon fils, ces âmes perdues sont sérieuses quant à leurs intentions viles... Que Dieu vous bénisse !";
				link.l1 = "Merci, saint père. Je serai attentif.";
				link.l1.go = "Padre_exit";
				AddMoneyToCharacter(pchar, -iTemp);
				AddQuestRecord("Regata", "33");
				AddQuestUserData("Regata", "sMoney", iTemp);
			}
			if (iTemp > 10000)//3 категория - расскажет полностью
			{
				dialog.text = "Tu es très généreux, mon fils. Une modestie d'un humble serviteur de Dieu ne me permet pas d'accepter la somme entière que tu es prêt à donner pour le bien de notre église. Je prendrai seulement 10 000 pesos\nEn retour, je veux te prévenir que de mauvaises gens complotent contre toi. J'ai entendu dire que ces vils apostats vont couler ton navire ici même dans ce port\nIls ont préparé un lougre plein de poudre à canon nommé '"+pchar.questTemp.Regata.BranderName+"', elle navigue sous pavillon anglais pour s'approcher de toi sans éveiller de soupçons. Sois prudent, mon fils, ces âmes perdues sont sérieuses dans leurs intentions viles.\nDétruis-les, je te donne l'absolution pour ce péché. Que Dieu te bénisse ! Je prierai pour toi, mon fils.";
				link.l1 = "Merci, saint père. Si ces salauds osent faire quelque chose de mauvais, je les enverrai directement en enfer !";
				link.l1.go = "Padre_exit";
				AddMoneyToCharacter(pchar, -10000);
				ChangeCharacterComplexReputation(pchar, "nobility", 2);
				AddQuestRecord("Regata", "32");
				AddQuestUserData("Regata", "sText", pchar.questTemp.Regata.BranderName);
			}
		break;
		
		case "Regata_Padre_exit":
			dialog.text = "N' sois point en colère, mon fils. La colère est un péché. C'est ton droit de ne point faire la charité. Va en paix, mon fils.";
			link.l1 = "Adieu, saint père.";
			link.l1.go = "Padre_exit";
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			AddQuestRecord("Regata", "35");					  
		break;
		
		case "Padre_exit":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload7_back", "SentJons_church", "barmen", "stay", "ReturnRegataPadreNorm", 5);
		break;
		
		case "Regata_Spyglass":
			dialog.text = "Bonne journée à vous, capitaine ! Mon nom est "+npchar.name+" et j'aimerais...";
			link.l1 = "... m'offrir quelque chose... Ai-je raison, jeune demoiselle ?";
			link.l1.go = "Regata_Spyglass_1";
		break;
		
		case "Regata_Spyglass_1":
			dialog.text = "Bien sûr, capitaine ! Et pourquoi êtes-vous si surpris ? Vous êtes un beau marin et vous participez à la régate, bien sûr tout le monde est prêt à vous vendre des articles navals utiles.";
			link.l1 = "Bien, beauté, tu marques un point. Qu'as-tu pour moi ?";
			link.l1.go = "Regata_Spyglass_2";
		break;
		
		case "Regata_Spyglass_2":
			if(hrand(11) > 10)//отличная труба
			{
				pchar.questTemp.Regata.Spy = "spyglass4";
				sTemp = "an excellent spyglass";
				pchar.questTemp.Regata.SpyPrice = 20000;
				pchar.questTemp.Regata.SpyIndex = 12;//выигрыш - 12 часов
			}
			else
			{
				if(hrand(11) < 6)//обычная труба
				{
					pchar.questTemp.Regata.Spy = "spyglass2";
					sTemp = "an ordinary spyglass";
					pchar.questTemp.Regata.SpyPrice = 1800;
					pchar.questTemp.Regata.SpyIndex = 4;//выигрыш - 4 часа
				}
				else//хорошая труба - как пригодится
				{
					pchar.questTemp.Regata.Spy = "spyglass3";
					sTemp = "a good spyglass";
					pchar.questTemp.Regata.SpyPrice = 10000;
					pchar.questTemp.Regata.SpyIndex = 8;//выигрыш - 8 часов
				}
			}
			dialog.text = "Tiens, regarde. Je l'ai hérité de mon père. Lui aussi était marin comme toi, et il avait beaucoup de trucs de navigation. Je n'en ai pas besoin, mais tu le trouveras sûrement utile. Je ne demande que "+FindRussianMoneyString(sti(pchar.questTemp.Regata.SpyPrice))+" pour cela.";
			if (sti(pchar.money) >= sti(pchar.questTemp.Regata.SpyPrice))
			{
				link.l1 = "Eh bien, eh bien..."+sTemp+" ! Intéressant ! Je dis, je te l'achèterai. Pour tes jolis yeux. Alors, tu veux "+FindRussianMoneyString(sti(pchar.questTemp.Regata.SpyPrice))+" pour cela ? S'il vous plaît, prenez votre argent.";
				link.l1.go = "Regata_Spyglass_3";
			}
			link.l2 = "Hm..."+sTemp+"? Non, ma fille, je suis désolé, mais je n'en ai pas besoin. J'ai déjà une très belle longue-vue à moi. Alors... hélas !";
			link.l2.go = "Regata_Spyglass_exit";
		break;
		
		case "Regata_Spyglass_3":
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.Regata.SpyPrice));
			GiveItem2Character(pchar, pchar.questTemp.Regata.Spy);
			dialog.text = "Merci, capitaine. J'espere que cela vous servira bien. Je suis heureux que vous l'ayez trouve utile. Bonne chance pour la regate !";
			link.l1 = "Merci, "+npchar.name+"Adieu !";
			link.l1.go = "Spyglass_exit";
			for (i=1; i <=5; i++)
			{
				if (i==1) sTemp = "a";
				if (i==2) sTemp = "b";
				if (i==3) sTemp = "c";
				if (i==4) sTemp = "d";
				if (i==5) sTemp = "e";
				pchar.questTemp.Regata.AdversaryFourthTransition.Time.(sTemp) = sti(pchar.questTemp.Regata.AdversaryFourthTransition.Time.(sTemp))+sti(pchar.questTemp.Regata.SpyIndex);//купил трубу - выиграл время
				log_testinfo(FindRussianDaysString(pchar.questTemp.Regata.AdversaryFourthTransition.Time.(sTemp)));
			}
		break;
		
		case "Regata_Spyglass_exit":
			dialog.text = "Quel dommage, capitaine. J'espérais que cela vous serait utile. Eh bien, je vais essayer de le vendre à quelqu'un d'autre. Adieu !";
			link.l1 = "Adieu, "+npchar.name+".";
			link.l1.go = "Spyglass_exit";
			pchar.questTemp.Regata.AdversaryFourthTransition.Time.c = sti(pchar.questTemp.Regata.AdversaryFourthTransition.Time.c)-sti(pchar.questTemp.Regata.SpyIndex);//третий соперник выиграл время
		break;
		
		case "Spyglass_exit":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 10);
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
		break;
		
		case "Regata_SiegeOfficer":
			dialog.text = "Salutations, capitaine. Ne participez-vous pas à la régate ? Ai-je raison ?";
			link.l1 = "Oui. Et quel est l'accord, officier ?";
			link.l1.go = "Regata_SiegeOfficer_1";
		break;
		
		case "Regata_SiegeOfficer_1":
			dialog.text = "Vous devez déjà savoir que notre colonie est assiégée par les Espagnols. C'est pourquoi notre gouverneur souhaite vous parler. Auriez-vous l'amabilité de lui rendre visite ? En ce moment, la situation est très urgente.";
			link.l1 = "Hm... Très bien, j'irai voir son Excellence immédiatement, bien que je ne comprenne vraiment pas comment je peux être impliqué dans les opérations militaires.";
			link.l1.go = "Regata_SiegeOfficer_2";
		break;
		
		case "Regata_SiegeOfficer_2":
			dialog.text = "Vous êtes impliqué, capitaine. Ne perdons pas de temps et allons à la résidence. Suivez-moi.";
			link.l1.go = "Regata_SiegeOfficer_3";
		break;
		
		case "Regata_SiegeOfficer_3":
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "Bridgetown_townhall", "goto", "governor1", "RegataSiegeHover", -1);
		break;
		
		case "Regata_SiegeOfficer_4":
			dialog.text = "Capitaine! Je suis prêt à envoyer les civils sur votre navire. Partons-nous maintenant?";
			link.l1 = "Oui, bien sûr. Nous allons appareiller immédiatement. Dites aux gens de monter dans les chaloupes.";
			link.l1.go = "Regata_SiegeOfficer_5";
		break;
		
		case "Regata_SiegeOfficer_5":
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "RegataSiegeOpen", -1);
			for (i=1; i <=9; i++)
			{
				sld = characterFromId("RegataBridgWom_"+i);
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "quest", "quest1", "none", "", "", "", 30);
			}
		break;
		
		case "Regata_SiegeOfficer_6":
			dialog.text = "Nous l'avons fait... On dirait que ce sloop était un éclaireur de l'escadre et que ces salauds castillans faisaient du repérage. Capitaine, s'il vous plaît, aidez-moi à amener les femmes dans les cavernes, il est possible qu'il y ait d'autres détachements espagnols.";
			link.l1 = "Très bien. Allons-y !";
			link.l1.go = "Regata_SiegeOfficer_7";
		break;
		
		case "Regata_SiegeOfficer_7":
			DialogExit();
			sld = characterFromId("SiegeOfficer");
			LAi_ActorFollowEverywhere(sld, "", -1);
			pchar.quest.Regata_Siege3.win_condition.l1 = "location";
			pchar.quest.Regata_Siege3.win_condition.l1.location = "Barbados_cave";
			pchar.quest.Regata_Siege3.function = "RegataBarbadosCave";
		break;
		
		case "Regata_SiegeOfficer_8":
			dialog.text = "Gratitude pour votre aide, capitaine ! Si ce n'était pas pour vous et votre courage... Vous êtes un vrai héros, vous avez mené à bien cette opération malgré tous les dangers et vos propres intérêts. J'ai réfléchi à comment vous récompenser... et il y a un moyen d'améliorer vos chances dans la régate.";
			link.l1 = "Intéressant. Quel est ce chemin ?";
			link.l1.go = "Regata_skiper";
		break;
		
		case "Regata_Hovernor":
			dialog.text = "Salutations, capitaine "+GetFullName(pchar)+" . C'est bien que vous soyez venu. Notre ville a besoin de votre aide.";
			link.l1 = "Monsieur, si vous parlez de l'escadre espagnole qui attaque votre colonie en ce moment, alors je n'ai aucune idée de comment je peux vous aider. Je commande un lougre, pas un vaisseau de ligne...";
			link.l1.go = "Regata_Hovernor_1";
		break;
		
		case "Regata_Hovernor_1":
			dialog.text = "Ecoutez-moi, capitaine, et vous comprendrez. Nous sommes dans un sérieux pétrin. La ville est assiégée par les Espagnols. Une bataille décisive avec le fort est sur le point de commencer. De plus, quelques centaines d'Espagnols ont déjà débarqué et bloqué toutes les issues de la ville, maintenant ils peuvent nous attaquer par la mer et la terre.\nLa garnison du fort se prépare à défendre la ville contre l'escadre et il n'y a pas assez de soldats dans la colonie elle-même. Tout homme capable de manier une arme est mobilisé, mais qu'en est-il des autres?\nIl y a cent âmes de femmes à Bridgetown. Pouvez-vous imaginer ce qui leur arrivera si nous échouons à protéger notre colonie? Je crois que vous comprenez.";
			link.l1 = "Monsieur, je vous comprends, mais, encore une fois, comment puis-je vous aider ? Que voulez-vous de moi ? Combattre des navires de ligne ou m'engager avec mon équipage dans la milice de la ville ?";
			link.l1.go = "Regata_Hovernor_2";
		break;
		
		case "Regata_Hovernor_2":
			switch (sti(Pchar.BaseNation))
			{
				case ENGLAND: sTemp = "You are English , help us to save English citizens and what is important - women!" break;
				case FRANCE: sTemp = "You are French, so you basically are our ally, help us to save English citizens and what is more important - women!" break;
				case SPAIN: sTemp = "I know that you are Spanish and these are your people in the sea, so I know that I am already asking for a lot, but these women are innocent and have nothing to do with this battle. So please I beg of you, help them!" break;
				case HOLLAND: sTemp = "I know that you are Dutch and our nations are at war, but you are participating in the English regatta under the English flag. Don't you think that it is right to fight for innocent and peaceful people, for women? Please captain, help them!" break;
			}
			dialog.text = "Ni l'un ni l'autre. Je vous demande seulement une chose. Emmenez les femmes et les enfants loin d'ici sur votre navire. Ils ne sont pas nombreux, environ une centaine. Emmenez-les au Cap Harrison avec le lieutenant Mahony, il s'assurera qu'ils sont en sécurité dans la grotte\nJe suis sûr que les Espagnols ne les chercheront pas. Je n'ai pas de navires à disposition, tout ce que nous avions a été coulé par l'escadron espagnol. Vous êtes mon dernier espoir. Vous pouvez les emmener au cap en un seul voyage, même si votre vaisseau sera surchargé. Les vaisseaux de ligne ne vous suivront pas.\nJe ne peux demander à personne d'autre de le faire."+sTemp+"";
			link.l1 = "Monsieur, je suis désolé mais mon navire est déjà surchargé et il ne pourra pas accueillir autant de personnes même pour deux voyages. Un boulet de canon tombé au hasard à proximité enverrait mon navire et vos femmes au fond de la mer. Pardonnez-moi, mais je ne peux vous aider.";
			link.l1.go = "Regata_Hovernor_exit";
			link.l2 = "Très bien, monsieur. Je vais vous aider. L'honneur du marin m'oblige à le faire.";
			link.l2.go = "Regata_Hovernor_3";
		break;
		
		case "Regata_Hovernor_3":
			dialog.text = "Je suis heureux que vous ayez accepté. Vous êtes un véritable soldat. Le lieutenant Mahony amènera les femmes et les enfants sur votre navire. Bon vent, Capitaine !";
			link.l1 = "Merci, monsieur. Ne perdons pas de temps !";
			link.l1.go = "Regata_Hovernor_4";
		break;
		
		case "Regata_Hovernor_wait":
			dialog.text = "Dépêche-toi, capitaine. Le temps presse.";
			link.l1 = "Je navigue déjà !";
			link.l1.go = "exit";
			NextDiag.TempNode = "Regata_Hovernor_wait";
		break;
		
		case "Regata_Hovernor_exit":
			dialog.text = "C'est incroyable. Tu ne vas même pas essayer ? Eh bien, tu es dans ton droit. Je ne peux rien exiger de toi. Si tu étais juste un capitaine ordinaire, je confisquerais ton navire pour le bien de cent femmes, mais tu participes à la régate, et donc tu es sous la protection du gouverneur-général des colonies anglaises\nJ'espérais que ta conscience prendrait le dessus, mais j'avais tort. Va, et que Dieu ait pitié de ton âme !";
			link.l1 = "Adieu, monsieur.";
			link.l1.go = "Hovernor_exit";
		break;
		
		case "Hovernor_exit":
			DialogExit();
			pchar.quest.Regata_TH.over = "yes"; // belamour снять прерывание
			pchar.questTemp.Regata.AdversaryFifthTransition.Time.e = sti(pchar.questTemp.Regata.AdversaryFifthTransition.Time.e)-36;//пятый противник выиграл 36 часов
			ChangeCharacterComplexReputation(pchar, "nobility", -8);
			ChangeCharacterNationReputation(pchar, ENGLAND, -5);
			//вертаем губера в норму
			npchar.Dialog.Filename = "Common_Mayor.c";
			npchar.dialog.currentnode = "First time";
			//удаляем лейтенанта
			sld = characterFromId("SiegeOfficer");
			sld.lifeday = 0;
			//открываем ворота и выход в море
			bDisableFastReload = false;
			LocatorReloadEnterDisable("Bridgetown_town", "reload1_back", false);
			LocatorReloadEnterDisable("Bridgetown_town", "reload2_back", false);
			LocatorReloadEnterDisable("Bridgetown_town", "gate1_back", false);
			LocatorReloadEnterDisable("Bridgetown_town", "gate_back", false);
			LocatorReloadEnterDisable("Bridgetown_Exittown", "reload3", false);
			//остров в норму
			n = FindIsland("Barbados");	
			DeleteAttribute(Islands[n], "DontSetShipInPort");
			//осаду снимем через 5 дней
			SetFunctionTimerCondition("RegataSiegeDelete", 0, 0, 5, false);
			for (i=1; i <=9; i++)//девок счистим
			{
				sld = characterFromId("RegataBridgWom_"+i);
				sld.lifeday = 0; // patch-7
				LAi_CharacterDisableDialog(sld);
			}
			AddQuestRecord("Regata", "38");
			AddQuestUserData("Regata", "sName", GetFullName(npchar));
		break;
		
		case "Regata_Hovernor_4":
			DialogExit();
			pchar.quest.Regata_TH.over = "yes"; // belamour снять прерывание
			NextDiag.CurrentNode = "Regata_Hovernor_wait";
			sld = characterFromId("SiegeOfficer");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload2", "Bridgetown_town", "goto", "goto4", "", 10);
			pchar.quest.Regata_evacuation.win_condition.l1 = "location";
			pchar.quest.Regata_evacuation.win_condition.l1.location = "Bridgetown_town";
			pchar.quest.Regata_evacuation.function = "RegataSiegeEvacuation";
			AddQuestRecord("Regata", "36");
			AddQuestUserData("Regata", "sName", GetFullName(npchar));
		break;
		
		case "Regata_BridgWom":
			dialog.text = "Les Espagnols sont sur nous ! Dieu, aide-nous !";
			link.l1 = "... ";
			link.l1.go = "exit";
			NextDiag.TempNode = "Regata_BridgWom";
		break;
		
		case "Regata_BridgWom_1":
			dialog.text = "Le lieutenant Mahony est mort... cela doit être un cauchemar. C'était un officier courageux. Capitaine, pourriez-vous nous emmener à une caverne ? Emmenez-nous simplement là-bas et nous nous débrouillerons.";
			link.l1 = "D'accord. Suivez-moi !";
			link.l1.go = "Regata_BridgWom_2";
		break;
		
		case "Regata_BridgWom_2":
			DialogExit();
			for (i=1; i <=9; i++)
			{
				sld = characterFromId("RegataBridgWom_"+i);
				LAi_SetActorType(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
			}
			pchar.quest.Regata_Siege3.win_condition.l1 = "location";
			pchar.quest.Regata_Siege3.win_condition.l1.location = "Barbados_cave";
			pchar.quest.Regata_Siege3.function = "RegataBarbadosCave";
		break;
		
		case "Regata_BridgWom_3":
			dialog.text = "Nous y voilà... merci, capitaine ! Vous venez de nous sauver tous ! J'ai réfléchi à comment vous récompenser... il y a un moyen d'améliorer vos chances lors de la régate.";
			link.l1 = "Continue.";
			link.l1.go = "Regata_skiper";
		break;
		
		case "Regata_skiper":
			pchar.questTemp.Regata.Name = GetFullName(npchar);
			dialog.text = "Te diriges-tu vers Port Royal ? Le chemin le plus court passe par Curacao. Retourne à Bridgetown. Trouve un homme nommé Woodrow Dougherty, c'est un vieux loup de mer et un navigateur expérimenté. Il connaît parfaitement la zone entre la Barbade et la Jamaïque, il te sera d'une grande aide.\nCela te fera gagner un temps précieux dont tu as désespérément besoin pour triompher. Trouve cet homme dans l'église locale et dis-lui que "+GetFullName(npchar)+" - vous a envoyé, il ne vous refusera pas. Emmenez-le à Port Royal, il allait y naviguer de toute façon.";
			link.l1 = "Très bien ! Un bon navigateur me sera utile. Adieu.";
			link.l1.go = "Regata_skiper_1";
		break;
		
		case "Regata_skiper_1":
			dialog.text = "Adieu, capitaine ! Bonne chance !";
			link.l1 = "Peut-être, nous nous reverrons...";
			link.l1.go = "Regata_skiper_2";
		break;
		
		case "Regata_skiper_2":
			DialogExit();
			AddQuestRecord("Regata", "37");
			ChangeCharacterComplexReputation(pchar, "nobility", 10);
			ChangeCharacterNationReputation(pchar, ENGLAND, 10);
			LAi_SetStayType(npchar);
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0; // patch-8
			for (i=1; i <=9; i++)
			{
				sld = characterFromId("RegataBridgWom_"+i);
				LAi_SetStayType(sld);
				LAi_CharacterDisableDialog(sld);
				sld.lifeday = 0; // patch-8
			}
			//вертаем губера в норму
			sld = characterFromId("Bridgetown_Mayor");
			sld.Dialog.Filename = "Common_Mayor.c";
			sld.dialog.currentnode = "First time";
			//открываем ворота и выход в море
			LocatorReloadEnterDisable("Shore4", "boat", false);
			LocatorReloadEnterDisable("Bridgetown_town", "gate1_back", false);
			LocatorReloadEnterDisable("Bridgetown_town", "gate_back", false);
			LocatorReloadEnterDisable("Bridgetown_Exittown", "reload3", false);
			LocatorReloadEnterDisable("Barbados_cave", "reload1", false);
			bQuestDisableMapEnter = false;
			//осаду снимем через 5 дней
			SetFunctionTimerCondition("RegataSiegeDelete", 0, 0, 5, false);
			RegataSiegeSkiper();//поставим Вудро в церковь
		break;
		
		case "Regata_SiegeSkiper":
			dialog.text = "Bonne journée. Vous voulez quelque chose ?";
			link.l1 = "Votre nom est Woodrow Dougherty, ai-je raison ?";
			link.l1.go = "Regata_SiegeSkiper_1";
		break;
		
		case "Regata_SiegeSkiper_1":
			dialog.text = "Vous avez raison. Comment puis-je vous être utile ?";
			link.l1 = "Je sais que tu es un navigateur chevronné et que tu connais bien les eaux entre la Barbade et Curaçao. Je sais aussi que tu veux te rendre à Port Royal. Je participe à la régate et il ne reste qu'une dernière étape - Port Royal. Je veux te demander de rejoindre mon équipage en tant que navigateur pour ce dernier voyage.";
			link.l1.go = "Regata_SiegeSkiper_2";
		break;
		
		case "Regata_SiegeSkiper_2":
			dialog.text = "Intéressant... Et pourquoi penses-tu que je rejoindrai ton équipage ?";
			link.l1 = "Eh bien, parce que j'ai entendu parler de vous de "+pchar.questTemp.Regata.Name+"avec toutes les garanties que tu ne diras pas non. Et à cause de mon aide à Bridgetown en ce moment critique...";
			link.l1.go = "Regata_SiegeSkiper_3";
		break;
		
		case "Regata_SiegeSkiper_3"://а тут - как уж свезет
			if(hrand(2) != 2)
			{
				dialog.text = "Depuis "+pchar.questTemp.Regata.Name+" ? Je comprends maintenant, bien sûr. D'accord, capitaine, je vais vous aider à naviguer le chemin le plus court jusqu'à Port Royal. Allez-vous lever l'ancre maintenant ?";
				link.l1 = "Oui.";
				link.l1.go = "Regata_SiegeSkiper_4";
			}
			else
			{
				dialog.text = ""+pchar.questTemp.Regata.Name+"? Je vois. Mais, capitaine, je ne peux pas quitter ma ville en ces temps si dangereux. Vous devez me comprendre en tant que soldat qui nous a fourni une aide désintéressée\nJe ne veux pas que les gens chuchotent dans mon dos que le vieux Woodrow a fui à l'approche de la bataille finale contre les Espagnols. Je resterai. Ne gardez pas de rancune, capitaine.";
				link.l1 = "Et c'est ton dernier mot? Mais j'ai aidé ta colonie...";
				link.l1.go = "Regata_SiegeSkiper_6";
			}
		break;
		
		case "Regata_SiegeSkiper_4":
			dialog.text = "N'perdons pas de temps alors. Laissez-moi juste emballer mes affaires et je serai à votre disposition.";
			link.l1 = "Mes marins vous attendront sur le quai et vous conduiront à la 'Sainte Catherine'. Merci, Woodrow !";
			link.l1.go = "SiegeSkiper_hire";
		break;
		
		case "Regata_SiegeSkiper_6":
			dialog.text = "Capitaine, la régate est un sport et le siège espagnol de ma maison est une vie. Je ne vais nulle part avec vous. Et je me répète, vous devez me comprendre - l'honneur et le devoir signifient encore quelque chose dans ce monde. C'est mon dernier mot et je ne vais pas le changer\nCependant, je peux vous donner un conseil pour y parvenir rapidement par la route la plus sûre, naviguez vers le nord-ouest en direction de la Dominique et de là, faites route vers la Martinique ou la Guadeloupe, à vous de voir et selon le vent. Ensuite, naviguez directement vers Port-Royal, ou vous pourriez passer par Curaçao que je ne recommanderais pas, mais si vous êtes en bons termes avec les Hollandais, alors allez-y.";
			link.l1 = "Eh bien, merci... mais je suis déçu. Adieu, Woodrow.";
			link.l1.go = "SiegeSkiper_exit";
		break;
		
		case "SiegeSkiper_exit":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 10.0);
			npchar.lifeday = 0;
		break;
		
		case "SiegeSkiper_hire":
			chrDisableReloadToLocation = true;//закрыть локацию
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 10.0);
			npchar.quest.OfficerPrice = sti(pchar.rank)*500;
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(npchar.id);
			npchar.OfficerWantToGo.DontGo = true; //не пытаться уйти
			npchar.loyality = 25;
			npchar.Dialog.Filename = "Enc_Officer_dialog.c";
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			NextDiag.CurrentNode = NextDiag.TempNode;
			//пересчитываем время пятого перехода
			for (i=1; i <=5; i++)
			{
				if (i==1) sTemp = "a";
				if (i==2) sTemp = "b";
				if (i==3) sTemp = "c";
				if (i==4) sTemp = "d";
				if (i==5) sTemp = "e";
				pchar.questTemp.Regata.AdversaryFifthTransition.Time.(sTemp) = sti(pchar.questTemp.Regata.AdversaryFifthTransition.Time.(sTemp))+18+(rand(18));//выигрыш до 1.5 суток
				log_testinfo(FindRussianDaysString(pchar.questTemp.Regata.AdversaryFourthTransition.Time.(sTemp)));
			}
			SetFunctionTimerCondition("SiegeSkiperOver", 0, 0, 15, false);//чтобы не присвоил офицера
			DialogExit();
		break;
		
		case "Regata_Finish":
		iTest = FindColony("Portroyal"); 
		if (iTest != -1)
		{
			rColony = GetColonyByIndex(iTest);
			sFrom_sea = rColony.from_sea;
		}
		ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)//проверка на наличие корабля в порту
		{
			//снимаем запреты
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			bool bRegLugger = sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_LUGGER || sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_CAREERLUGGER;
			if (CheckAttribute(pchar, "questTemp.Regata.Breach") || !CheckAttribute(pchar, "questTemp.Regata.Bridgetown") || GetCompanionQuantity(pchar) > 1 || !bRegLugger || pchar.Ship.Name != "Saint Catherine")
			{
				dialog.text = "Vous avez enfreint les règles de la régate à la toute dernière étape. Votre résultat a été disqualifié. Je n'ai rien de plus à vous dire, capitaine.";
				link.l1 = "Eh...qu'est-ce que c'est que ce bordel ! Eh bien, il n'y a rien à faire alors, tu étais trop attentif. Adieu !";
				link.l1.go = "exit";
				npchar.lifeday = 1;
				DeleteAttribute(pchar, "questTemp.Regata");
				AddQuestRecord("Regata", "45");
				CloseQuestHeader("Regata");
			}
			else
			{
				n=1;
				for (i=1; i <=5; i++)
				{
					if (i==1) sTemp = "a";
					if (i==2) sTemp = "b";
					if (i==3) sTemp = "c";
					if (i==4) sTemp = "d";
					if (i==5) sTemp = "e";
					if (pchar.questTemp.Regata.AdversaryFifthTransition.Time.(sTemp) < sti(pchar.questTemp.Regata.FifthTransitionTime)) n++;
					pchar.questTemp.Regata.Result = n;//место в регате
				}
				if (n==1)
				{
					dialog.text = "Capitaine "+GetFullName(pchar)+", mes félicitations ! Cela a pris "+sti(pchar.questTemp.Regata.FifthTransitionTime)+" heures pour vous de finir la régate et vous avez laissé tous vos adversaires loin derrière. C'est un résultat remarquable !";
					link.l1 = "Merci pour vos aimables paroles, monsieur !";
					link.l1.go = "First_result";
				}
				else
				{
					if (n==6)
					{
						dialog.text = "Capitaine, hélas mais votre résultat est le pire, vous avez dépensé "+sti(pchar.questTemp.Regata.FifthTransitionTime)+" heures. Ne sois pas triste, tu avais vraiment des adversaires coriaces.";
						link.l1 = "Je ne suis pas triste, monsieur. Je suis heureux d'avoir participé à la régate et d'avoir mis mes compétences à l'épreuve.";
						link.l1.go = "Other_result";
						AddQuestRecord("Regata", "44");
						CloseQuestHeader("Regata");
					}
					else
					{
          				dialog.text = "Capitaine, vous êtes dans "+n+"ème place. Félicitations pour ce résultat réussi, vous avez montré un temps digne - "+sti(pchar.questTemp.Regata.FifthTransitionTime)+"heures. Félicitations malgré ta défaite !";
						link.l1 = "C'est en ordre, monsieur. Je suis heureux d'avoir montré un bon résultat dans cette rude compétition.";
						link.l1.go = "Other_result";
						if (n==2) AddQuestRecord("Regata", "40");
						if (n==3) AddQuestRecord("Regata", "41");
						if (n==4) AddQuestRecord("Regata", "42");
						if (n==5) AddQuestRecord("Regata", "43");
						CloseQuestHeader("Regata");
					}
				}
			}
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex("SiegeSkiper");
			sld = &Characters[sti(Pchar.questTemp.FiringOfficerIDX)];
			CheckForReleaseOfficer(sti(Pchar.questTemp.FiringOfficerIDX));
			RemovePassenger(Pchar, sld);
			DeleteAttribute(sld, "Payment");
			DeleteAttribute(Pchar, "questTemp.FiringOfficerIDX");//удаляем из офицеров
			log_info("Woodrow Dougherty has landed");
			pchar.quest.SiegeSkiperOver.over = "yes"; //снять таймер
		}
		else
		{
			dialog.text = "Monsieur, laissez-moi vous demander quelque chose - où est votre navire ? Je ne le vois pas...";
			link.l1 = "Je suis désolé, monsieur. Je la conduirai au port immédiatement.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Regata_Finish";
		}
		break;
		
		case "First_result":
			if (CheckAttribute(pchar, "questTemp.Regata.Rate")) sTemp = "Come and see me in my office. I will give you your prize for your stake.";
			else sTemp = "And if you had made a stake on your victory as I offered you to, you would have gotten an extra prize too.";
			dialog.text = "Visitez le gouverneur-général demain et il vous donnera vos 250 000 pesos et des cadeaux précieux. "+sTemp+" Ne quittez pas la ville, selon les traditions les prix seront remis au trésor de la ville au cas où le gagnant ne les prendrait pas dans un délai d'une semaine.";
			link.l1 = "Je l'ai compris, monsieur. Je lui rendrai visite demain !";
			link.l1.go = "First_result_1";
		break;
		
		case "First_result_1":
			DialogExit();
			//npchar.lifeday = 7;
			Achievment_Set("ach_09");
			npchar.dialog.currentnode = "Other_result_repeat";
			pchar.questTemp.Regata.Win = "true";
			pchar.quest.Regata_Final.win_condition.l1 = "Timer";
			pchar.quest.Regata_Final.win_condition.l1.date.hour  = 6.0;
			pchar.quest.Regata_Final.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Regata_Final.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Regata_Final.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Regata_Final.function = "RegataFinal";
			SetFunctionTimerCondition("RegataFinalOver", 0, 0, 8, false);//таймер не снимаем - через 8 дней подчистится все автоматически
			// слухи
			AddSimpleRumour("Ah, you are the legendary captain, the winner of the regatta! It's such a pleasure to see you in flesh!", ENGLAND, 60, 10);
			AddSimpleRumour("Ha, look at this, a master of wind and waves, the winner of the regatta! You have my respect...", ENGLAND, 60, 10);
			AddSimpleRumour("Oh, a great sailor, a king of the wind and the sea, the winner of regatta has visited our city! We are glad to see you, captain!", ENGLAND, 60, 10);
			AddSimpleRumour("Oh, yes I was lucky to chat with a living legend, the captain who is capable of crossing the archipelago in three days even facing a headwind! My respects, captain!", ENGLAND, 60, 10);
			AddSimpleRumour("Ah, so you are the legendary captain, the winner of the regatta! Pleasure to see you!", FRANCE, 60, 10);
			AddSimpleRumour("Ha, aren't you the master of wind and waves, the winner of the regatta! You have my respects...", FRANCE, 60, 10);
			AddSimpleRumour("Oh, a great sailor, a king of the wind and the sea, the winner of regatta has visited our city! We are glad to see you, captain!", FRANCE, 60, 10);
			AddSimpleRumour("Oh, yes I was lucky to chat with a living legend, the captain capable of crossing the archipelago in three days even facing a headwind! My respects, captain!", FRANCE, 60, 10);
			// экспа
			AddComplexSeaExpToScill(2000, 300, 300, 0, 500, 500, 0);
			AddCharacterExpToSkill(pchar, "Leadership", 2000);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 1000);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 300);//скрытность
			ChangeCharacterComplexReputation(pchar, "authority", 10);
			ChangeCharacterComplexReputation(pchar, "fame", 15);
			ChangeOfficersLoyality("good_all", 3);
			AddQuestRecord("Regata", "39");
			CloseQuestHeader("Regata");
		break;
		
		case "Other_result":
			dialog.text = "C'est bon d'entendre une reponse honorable. Bonne chance, capitaine!";
			link.l1 = "Adieu, monsieur.";
			link.l1.go = "Other_result_1";
		break;
		
		case "Other_result_1":
			DialogExit();
			npchar.dialog.currentnode = "Other_result_repeat";
			SetFunctionTimerCondition("RegataFinalOver", 0, 0, 1, false);
			// экспа
			AddComplexSeaExpToScill(500, 100, 100, 0, 100, 100, 0);
			AddCharacterExpToSkill(pchar, "Leadership", 200);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 100);//скрытность
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterComplexReputation(pchar, "fame", 1);
		break;
		
		case "Other_result_repeat":
			dialog.text = "Vous voulez autre chose, capitaine ?";
			link.l1 = "Non... ce n'est rien.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Other_result_repeat";
		break;
		
		case "Give_advantage":
			dialog.text = "Ah, te voilà, monsieur "+GetFullName(pchar)+"Content de te voir. Es-tu là pour ton prix? Il est prêt pour toi.";
			link.l1 = "C'est bon à entendre ! Quelle est la taille de mon prix supplémentaire ?";
			link.l1.go = "Give_advantage_1";
		break;
		
		case "Give_advantage_1":
			dialog.text = "Compte tenu de tous les enjeux, votre prix final est "+FindRussianMoneyString(makeint(pchar.questTemp.Regata.Advantage))+".  Je vous en prie, prenez-le. Félicitations !";
			link.l1 = "Merci !";
			link.l1.go = "Give_advantage_2";
		break;
		
		case "Give_advantage_2":
			AddMoneyToCharacter(pchar, makeint(pchar.questTemp.Regata.Advantage));
			dialog.text = "Bien sûr, ta popularité parmi les citoyens de Port Royal a grandi. Je pense que tu peux le constater... mais hélas, la mémoire du peuple est courte. Alors baigne-toi dans la gloire tant qu'elle est encore si éclatante !";
			link.l1 = "Vous parlez des choses les plus agréables, monsieur... Eh bien, voyons ce que c'est que de se baigner dans la gloire. Adieu ! Ce fut un plaisir.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Other_result_repeat";
		break;
		
		case "Regata_CitMan_1":
			if (CheckAttribute(pchar, "questTemp.Regata"))
			{
				if (CheckAttribute(pchar, "questTemp.Regata.Result"))
				{
					if (sti(pchar.questTemp.Regata.Result) == 1)
					{
						dialog.text = "Félicitations pour votre victoire, capitaine ! Un résultat excellent !";
						link.l1 = "Merci !";
						link.l1.go = "exit";
					}
					else
					{
						dialog.text = "Ne sois pas triste, capitaine. Il n'est pas facile de gagner la régate, y participer est déjà un privilège!";
						link.l1 = "Ne vous inquiétez pas pour moi. Je suis satisfait de mon résultat.";
						link.l1.go = "exit";
					}
				}
				else
				{
					dialog.text = "Heureux de vous voir, capitaine ! Vous devriez vous enregistrer en parlant au sieur Stevenson.";
					link.l1 = "Je vois. Je suis en route vers lui !";
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "Ah, capitaine, pourquoi as-tu échoué ainsi et à la toute dernière étape !";
				link.l1 = "Oui, si stupide de ma part...";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Regata_CitMan_1";
		break;
		
		case "Regata_CitWom_1":
			if (CheckAttribute(pchar, "questTemp.Regata"))
			{
				if (CheckAttribute(pchar, "questTemp.Regata.Result"))
				{
					if (sti(pchar.questTemp.Regata.Result) == 1)
					{
						dialog.text = "Félicitations pour votre victoire, capitaine ! Un résultat excellent !";
						link.l1 = "Merci!";
						link.l1.go = "exit";
					}
					else
					{
						dialog.text = "Ne sois pas triste, capitaine. Il n'est pas facile de remporter la régate, y participer est déjà un privilège !";
						link.l1 = "Ne t'inquiète pas pour moi. Je suis satisfait de mon résultat.";
						link.l1.go = "exit";
					}
				}
				else
				{
					dialog.text = "Ravi de vous voir, capitaine ! Vous devriez vous enregistrer en parlant à sir Stevenson.";
					link.l1 = "Je vois. Je suis en route !";
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "Ah, capitaine, pourquoi as-tu échoué ainsi et à la toute dernière étape !";
				link.l1 = "Oui, si stupide de ma part...";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Regata_CitWom_1";
		break;
		
		case "Regata_CitHorse_1":
			if (CheckAttribute(pchar, "questTemp.Regata"))
			{
				if (CheckAttribute(pchar, "questTemp.Regata.Result"))
				{
					if (sti(pchar.questTemp.Regata.Result) == 1)
					{
						dialog.text = "Félicitations pour ta victoire, capitaine ! Un résultat excellent !";
						link.l1 = "Merci!";
						link.l1.go = "exit";
					}
					else
					{
						dialog.text = "Ne sois pas triste, capitaine. Ce n'est pas facile de gagner la régate, y participer est déjà un privilège !";
						link.l1 = "Ne t'inquiète pas pour moi. Je suis satisfait de mon résultat.";
						link.l1.go = "exit";
					}
				}
				else
				{
					dialog.text = "Ravi de vous voir, capitaine ! Vous devriez vous enregistrer en parlant à sir Stevenson.";
					link.l1 = "Je vois. Je suis en route !";
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "Ah, capitaine, pourquoi as-tu échoué ainsi et à la toute dernière étape !";
				link.l1 = "Oui, si bête de ma part...";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Regata_CitHorse_1";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

void CreateRegataAdversaries()
{
	string sTemp;
	for (int i=0; i<=4; i++)
	{
	if (i==0) sTemp = "a";
	if (i==1) sTemp = "b";
	if (i==2) sTemp = "c";
	if (i==3) sTemp = "d";
	if (i==4) sTemp = "e";
	pchar.questTemp.Regata.AdversaryName.(sTemp) = GenerateRandomName_Generator(i, "man");
	pchar.questTemp.Regata.AdversaryShipName.(sTemp) = GenerateRandomNameToShip(ENGLAND);
	pchar.questTemp.Regata.AdversarySpeed.(sTemp) = 0.4+frand(0.9);
	log_testinfo(FindRussianDaysString(stf(pchar.questTemp.Regata.AdversarySpeed.(sTemp))));
	}
}
