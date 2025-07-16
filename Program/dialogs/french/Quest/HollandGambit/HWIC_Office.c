// НПС офиса ГВИК
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Vous désirez quelque chose ?";
			link.l1 = "Non.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// офицер
		case "HWIC_officer":
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = "Alarme ! L'ennemi est là ! Aux armes !";
				link.l1 = "Nom de Dieu!";
				link.l1.go = "fight";
				break;
			}
			if (ChangeCharacterHunterScore(Pchar, "holhunter", 0) > 12)
			{
				dialog.text = "Toi là-bas, halte ! Ton visage m'est familier... bien sûr ! Tu es recherché pour tes crimes ! Les gars, attrapez-le !";
				link.l1 = "Merde !";
				link.l1.go = "fight";
				break;
			}
			chrDisableReloadToLocation = true;
			if (CheckAttribute(pchar, "questTemp.HWIC.CanTake") && !CheckAttribute(pchar, "questTemp.HWIC.CanTake.Holl") && !CheckAttribute(pchar, "questTemp.HWIC.Eng") && !CheckAttribute(pchar, "questTemp.HWIC.Self"))
			{
				dialog.text = "Bienvenue à la Compagnie néerlandaise des Indes occidentales. Parlez vite, le temps c'est de l'argent.";
				link.l1 = "Je suis ici pour des affaires de commerce. Licences, instruments de navigation, et ainsi de suite...";
				link.l1.go = "HWIC_officer_3";
				link.l2 = "Je veux offrir mes services à la Compagnie. En échange d'or bien sûr. Recrutez-vous ?";
				link.l2.go = "HWIC_officer_1";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng"))
			{
				dialog.text = "Bienvenue à la Compagnie néerlandaise des Indes occidentales. Parle vite, le temps c'est de l'argent.";
				link.l1 = "Je suis désolé, il semble que je me sois trompé. Je m'en vais.";
				link.l1.go = "HWIC_officer_exit";
				link.l2 = "Je suis ici pour des affaires de commerce. Licences, instruments de navigation, et ainsi de suite...";
				link.l2.go = "HWIC_officer_3";
				break;
			}
			dialog.text = "Parle vite, le temps c'est de l'argent.";
			link.l1 = "Je suis ici pour des affaires de commerce. Licences, instruments de navigation et ainsi de suite...";
			link.l1.go = "HWIC_officer_3";
			link.l2 = "Je veux offrir mes services à la Compagnie. En échange d'or, bien sûr. Recrutez-vous ?";
			link.l2.go = "HWIC_officer_2";
		break;
		
		case "HWIC_officer_1":
			dialog.text = "Puis monte au bureau de Mynheer Rodenburg.";
			link.l1 = "Merci, je suis en route.";
			link.l1.go = "HWIC_officer_exit";
			// belamour legendary edition переехали по другому адресу
			LocatorReloadEnterDisable("GVIK", "reload2", false);//кабинет откроем
		break;
		
		case "HWIC_officer_2":
			dialog.text = "La Compagnie n'embauche pas pour le moment.";
			link.l1 = "C'est bien dommage. Désolé de t'avoir dérangé.";
			link.l1.go = "HWIC_officer_exit";
		break;
		
		case "HWIC_officer_3":
			dialog.text = "Parlez à Mynheer Gerritz. Sa table est sur votre gauche en entrant. Il fait affaire avec des capitaines sous contrat.";
			link.l1 = "Merci, officier...";
			link.l1.go = "HWIC_officer_exit";
		break;
		
		case "HWIC_officer_exit":
			DialogExit();
			// belamour legendary edition переехали
			LAi_ActorGoToLocation(npchar, "soldiers", "soldier3", "GVIK", "soldiers", "soldier3", "", 5);
			DoQuestCheckDelay("ReturnTalkerToOfficer", 5.0); // 140313
			NextDiag.TempNode = "HWIC_officer";
		break;
		
		// солдаты
		case "HWIC_soldier":
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = "Alarme ! L'ennemi est là ! Aux armes !";
				link.l1 = "Nom d'un chien !";
				link.l1.go = "fight";
				break;
			}
			if (ChangeCharacterHunterScore(Pchar, "holhunter", 0) > 12)
			{
				dialog.text = "Aha ! Je pense savoir qui tu es... Mais bien sûr ! Tu es recherché pour tes crimes ! Les gars, attrapez-le !";
				link.l1 = "Sacré bleu !";
				link.l1.go = "fight";
				break;
			}
			dialog.text = "Parlez à nos officiers ou à Mynheer Gerritz. Je n'ai rien à vous dire. Je suis de service.";
			link.l1 = "Votre discipline est admirable.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "HWIC_soldier";
		break;
		
		// клерки
		case "HWIC_clerk":
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = "Alarme ! L'ennemi est là ! Soldats !";
				link.l1 = "Satané !";
				link.l1.go = "fight";
				break;
			}
			dialog.text = "Parlez avec Mynheer Gerritz.";
			link.l1 = "Très bien, j'ai compris.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "HWIC_clerk";
		break;
		
		// главный клерк - минхер Герритц
		case "HWIC_headclerk":
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = "À l'alarme ! L'ennemi est là ! Soldats, attrapez-le !";
				link.l1 = "Sacré bleu!";
				link.l1.go = "fight";
				break;
			}
			if (ChangeCharacterHunterScore(Pchar, "holhunter", 0) > 12)
			{
				dialog.text = "Hm. Je pense qu'il y a quelque chose qui cloche chez vous... Mais bien sûr ! Vous êtes recherché pour vos nombreux crimes contre la Hollande ! Soldats, prenez-le !";
				link.l1 = "Merde !";
				link.l1.go = "fight";
				break;
			}
			dialog.text = "Vous désirez quelque chose, monsieur ?";
			if (!CheckCharacterItem(pchar, "HolTradeLicence"))
			{
				link.l1 = "Je veux acheter une licence commerciale de la Compagnie néerlandaise des Indes occidentales.";
				link.l1.go = "licence";	
			}
			if (!CheckAttribute(npchar, "quest.trade"))
			{
				link.l2 = "J'ai entendu dire qu'il est possible d'acheter ici des instruments de navigation et d'autres articles utiles. Est-ce vrai ?";
				link.l2.go = "trade";	
			}
			else
			{
				link.l2 = "Que vends-tu aujourd'hui ?";
				link.l2.go = "trade_1";	
			}
			if (CheckCharacterItem(pchar, "Cromvel_depeshe"))
			{
				link.l3 = "J'ai un document intéressant pour vous, mynheer. Jetez un œil aux premières lignes. Il concerne la survie de la République et les profits de la Compagnie. Les coordonnées d'une certaine rencontre y sont également. Je vous les vendrai si cela vous intéresse. Pour un prix généreux, bien sûr.";
				link.l3.go = "depeshe";	
			}
			// калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche.Garpiya") && pchar.questTemp.Caleuche.Garpiya == "gwik")
			{
				link.l4 = "Un capitaine du nom de Reginald Jackson doit travailler pour vous. Il navigue sur un chébec appelé 'Harpy'. Pourriez-vous me dire comment je peux le trouver ? J'ai des affaires importantes avec lui.";
				link.l4.go = "caleuche";	
			}
			// Sinistra Путеводная звезда
			if (CheckAttribute(pchar, "questTemp.PZ_RazgovorGerrits"))
			{
				link.l4 = "Je dois voir Monsieur Rodenburg de toute urgence. C'est d'une importance capitale. Où est-il ?";
				link.l4.go = "PZ_RazgovorGerrits_1";
			}
			link.l9 = "Non, ce n'est rien.";
			link.l9.go = "exit";			
			NextDiag.TempNode = "HWIC_headclerk";
		break;
		
		// торговые лицензии
		case "licence":
			if (!CheckAttribute(npchar, "quest.licence"))
			{
				dialog.text = "Eh bien, vous êtes libre de l'acheter. Mais je dois vous avertir que la Compagnie tient à sa réputation de stricte neutralité, par conséquent il est interdit d'attaquer tout navire marchand de n'importe quelle nation tant que vous détenez cette licence\nSi nous découvrons qu'un tel acte a été commis - nous annulerons votre licence. De plus, si vous entrez en conflit avec les Néerlandais ou la Compagnie pour quelque raison que ce soit, votre licence sera également annulée. Sommes-nous clairs ?";
				link.l1 = "Clair comme de l'eau de roche. Je m'en souviendrai.";
				link.l1.go = "licence_0";
				npchar.quest.licence = true;
			}
			else
			{
				dialog.text = "Vous êtes le bienvenu pour acheter une licence. Alors, combien de jours ?";
				link.l1.edit = 6;
				link.l1 = "";	
				link.l1.go = "licence_1";
			}
		break;
		
		case "licence_0":
			dialog.text = "Le permis accorde un passage libre vers n'importe quel port de n'importe quelle nation, il montre vos intentions pacifiques et explique votre but - commercer. Mais il ne vous aidera pas si vous avez des problèmes avec la loi. Ils vous le prendront simplement dans ce cas. Souvenez-vous, \nN'oubliez pas de hisser un pavillon amical avant d'entrer dans un port. Les patrouilles et les canonniers des forts préfèrent tirer d'abord et poser des questions ensuite\nLa durée minimale pour le permis est de vingt jours et la durée maximale est de six mois ou 180 jours\nAh, j'ai presque oublié... Selon nos estimées traditions, toutes les transactions impliquant des permis se paient en doublons. Maintenant, discutons des termes. Combien de temps souhaitez-vous que le permis dure ?";
			link.l1.edit = 6;
			link.l1 = "Bonjour, mon ami.";	
			link.l1.go = "licence_1";
			link.l2 = "Je suis désolé, mais je dois y réfléchir encore un peu. À plus tard.";	
			link.l2.go = "exit";
		break;
		
		case "licence_1":
			float fQty = stf(dialogEditStrings[6]);
			npchar.quest.lcc_summ = makeint(sqrt(fQty)*10)*7;
			if (fQty < 1)
			{
				dialog.text = "Monsieur, s'il vous plaît, parlez plus clairement. Je ne vous ai pas bien entendu. Alors, pour combien de temps?";
				link.l1 = "Laissez-moi réfléchir...";
				link.l1.go = "licence_r";
				break;
			}
			if (fQty > 0 && fQty < 20)
			{
				dialog.text = "Le terme minimum pour la licence est de vingt jours. Alors? Vingt jours ou plus?";
				link.l1 = "Laisse-moi réfléchir...";
				link.l1.go = "licence_r";
				break;
			}
			if (fQty > 180)
			{
				dialog.text = "La durée maximale de la licence est de six mois. Cent quatre-vingts jours ou moins ?";
				link.l1 = "Laisse-moi réfléchir...";
				link.l1.go = "licence_r";
				break;
			}
			dialog.text = "Pour "+FindRussianDaysString(sti(fQty))+"? Très bien. Cela vous coûtera "+FindRussianDublonString(sti(npchar.quest.lcc_summ))+"Ces conditions sont-elles acceptables ?";
			if (PCharDublonsTotal() >= sti(npchar.quest.lcc_summ))
			{
				link.l1 = "Oui, je le suis.";
				link.l1.go = "licence_2";
			}
			link.l2 = "Malheureusement, je n'ai pas autant d'argent sur moi maintenant. Je reviendrai plus tard pour la licence.";
			link.l2.go = "exit";
		break;
		
		case "licence_r":
			dialog.text = "Bonjour, mon ami.";
			link.l1.edit = 6;
			link.l1 = "Bonjour, mon ami.";	
			link.l1.go = "licence_1";
			link.l2 = "Je suis désolé, mais je dois encore réfléchir. Je te verrai plus tard.";	
			link.l2.go = "exit";
		break;
		
		case "licence_2":
			int iQty = sti(dialogEditStrings[6]);
			RemoveDublonsFromPCharTotal(sti(npchar.quest.lcc_summ));
			GiveNationLicence(HOLLAND, iQty);
			// belamour legendary edition на пару с Акулой
			if(CheckAttribute(pchar,"questTemp.SharkGoldFleet") && pchar.questTemp.SharkGoldFleet == "start")
			{
				if(iQty < 180) 
				{
					Log_info("Quest: 'Together with the Shark' - your license is less than 180 days");
				}
				else 
				{
					pchar.questTemp.SharkGoldFleet.LicenceOk = true;
					AddQuestRecord("SharkGoldFleet", "2");
				}
				pchar.questTemp.SharkGoldFleet = "afterGvik";
			}
			dialog.text = "Attends une minute... Laisse-moi mettre un signe et un cachet ici... scellé et terminé. Prends ton document.";
			link.l1 = "Merci ! Adieu, monsieur.";
			link.l1.go = "exit";
		break;
		
		case "trade":
			dialog.text = "En effet, nous le faisons. Vous pouvez acheter ici des outils de navigation tels que des compas, des astrolabes, des chronomètres et des sabliers. Mais nous n'avons pas toujours un stock complet prêt à être acheté, sauf peut-être les sabliers. Nos contractants et capitaines achètent les autres outils très rapidement. Donc, si vous n'avez pas trouvé ce dont vous avez besoin, revenez nous voir dans une semaine lorsque nous aurons réapprovisionné.\nNous vendons également des cartes et des longues-vues. Voulez-vous voir ce que nous avons ?";
			link.l1 = "Oui, s'il vous plaît.";
			link.l1.go = "trade_1";
			npchar.quest.trade = "true";
		break;
		
		case "trade_1":
			DialogExit();
			if (!CheckAttribute(npchar, "trade_date") || GetNpcQuestPastDayParam(npchar, "trade_date") >= 7)
			{
				GiveItemToTrader(npchar);
				SaveCurrentNpcQuestDateParam(npchar, "trade_date");
			}
			LaunchItemsTrade(npchar, 0);
		break;
		
		// депеша Кромвеля
		case "depeshe":
			dialog.text = "Hm, montre-moi...(lisant) Eh bien, eh bien... L'appétit de Cromwell grandit. Maudit soit-il ! Ces chiens puritains n'ont-ils pas versé assez de sang sur leur propre île sans apporter leur saleté ici !? Où as-tu eu cette dépêche ?";
			link.l1 = "Je l'ai pris à un courrier anglais. Alors, aimeriez-vous l'acheter ?";
			link.l1.go = "depeshe_1";
		break;
		
		case "depeshe_1":
			dialog.text = "Oui. Peter Stuyvesant sera vraiment ravi de le lire, j'en suis sûr. Et il prendra des mesures efficaces pour l'arrêter... Je peux payer avec des doublons d'or ou je peux vous faire une licence pour une durée de six mois. Que préférez-vous ?";
			link.l1 = "Je choisis l'or.";
			link.l1.go = "depeshe_dublon";
			link.l2 = "Je veux la licence.";
			link.l2.go = "depeshe_licence";
		break;
		
		case "depeshe_dublon":
			TakeNItems(pchar, "gold_dublon", 700);
			Log_Info("You have received 700 doubloons");
			dialog.text = "Très bien. Voici vos sept cents doublons. Une belle récompense pour un service bien rendu.";
			link.l1 = "Voici votre dépêche.";
			link.l1.go = "depeshe_exit";
		break;
		
		case "depeshe_licence":
			if (CheckCharacterItem(pchar, "HolTradeLicence")) TakeNationLicence(HOLLAND);
			GiveNationLicence(HOLLAND, 180);
			dialog.text = "Bien. Voici votre licence pour une durée de six mois.";
			link.l1 = "Merci ! Et voici votre dépêche.";
			link.l1.go = "depeshe_exit";
		break;
		
		case "depeshe_exit":
			RemoveItems(pchar, "Cromvel_depeshe", 1);
			pchar.quest.Terrapin_CromvelScuadron.over = "yes"; //снять прерывание
			ChangeCharacterNationReputation(pchar, HOLLAND, 15);
			ChangeCharacterComplexReputation(pchar, "authority", 3);
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			dialog.text = "Bedankt. Il est bon que vous ayez montré votre conscience et votre loyauté envers la République. Je parlerai à Matthias Beck et Peter Stuyvesant de votre bonne action.";
			link.l1 = "Bon à savoir. Adieu !";
			link.l1.go = "exit";
		break;
		
		// Sinistra Путеводная звезда
		case "PZ_RazgovorGerrits_1":
			dialog.text = "J'ai bien peur qu'il soit déjà parti pour le Vieux Monde avec la famille Schneur. Je crois qu'il vous en a parlé.";
			link.l1 = "C'est exact, il l'a fait. Mais j'espérais qu'il aurait pu être retardé par quelques affaires récentes dans l'Archipel. Dis-moi, Gerritz, quelqu'un dans la Compagnie garde-t-il le contact avec Monsieur Rodenburg ? Peut-être via des navires de courrier ?";
			link.l1.go = "PZ_RazgovorGerrits_2";
		break;
		
		case "PZ_RazgovorGerrits_2":
			dialog.text = "Pas du tout - avant de partir, il nous a demandé de ne jamais le déranger - il a dit qu'il commençait une nouvelle vie meilleure.";
			link.l1 = "Espérons que nos vies s'amélioreront aussi. Adieu.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.PZ_RazgovorGerrits");
		break;
		
		// калеуче
		case "caleuche":
			dialog.text = "Laissez-moi vérifier les registres du manifeste...Ikema, Immerzeel, Jacobs...Jackson, le voilà. Hmm, le Kapitein Reginald Jackson effectue actuellement des opérations de transport régulières entre Port Royal et Philipsburg. Cherchez-le sur cette route. Maintenant kapitein, je dois vous avertir à l'avance - si vous complotez quelque méfait, vous feriez mieux de vous abstenir, car ce Kapitein Jackson est sous notre protection. Nous comprenons-nous, mynheer ?";
			link.l1 = "J'ai simplement des affaires avec lui. Un commerce ordinaire. Je n'ai pas l'intention de lui faire du mal d'aucune manière.";
			link.l1.go = "caleuche_1";
		break;
		
		case "caleuche_1":
			dialog.text = "Excellent. Le capitaine Jackson ne reste généralement pas longtemps à Port Royal ou à Philipsburg. Le temps, c'est de l'argent après tout. Une fois que son navire est déchargé et rechargé, il prend généralement la mer immédiatement. Vous aurez plus de chance de le rencontrer le long des routes maritimes.";
			link.l1 = "Merci !";
			link.l1.go = "caleuche_2";
		break;
		
		case "caleuche_2":
			DialogExit();
			pchar.questTemp.Caleuche.Garpiya = "capitan";
			pchar.questTemp.Garpiya = "to_portroyal";
			AddQuestRecord("Caleuche", "19");
			DoQuestFunctionDelay("Caleuche_CreateGarpiyaInWorld", 1.0);
		break;
		
		// новый босс ГВИК
		case "HWIC_Boss":
			if(CheckAttribute(pchar,"questTemp.HWIC.Detector") && (pchar.questTemp.HWIC.Detector == "holl_win"))
			{
				if (!CheckAttribute(npchar, "quest.silk_info") && sti(pchar.reputation.nobility) > 60)
				{
					dialog.text = "Aha, Capitaine "+GetFullName(pchar)+" ! C'est bien que vous soyez venu ici. J'ai une proposition d'affaire pour vous.";
					link.l1 = "Intéressant ! Je vous écoute, monsieur.";
					link.l1.go = "silk_info";
					break;
				}
			}
			dialog.text = "Bonne journée, Kapitein "+GetFullName(pchar)+"! Comment puis-je vous être utile ?";
			if(CheckAttribute(pchar,"questTemp.HWIC.Detector") && (pchar.questTemp.HWIC.Detector == "holl_win"))
			{
				if(CheckAttribute(npchar, "quest.silk")) // торговля шелком
				{
					if (GetDataDay() == 1 || GetDataDay() == 15)
					{
						link.l1 = "Concernant cette soie de navire...";
						link.l1.go = "trade_silk";
					}
				}
			}
			link.l2 = "Bonne journée. Non, je n'ai besoin de rien, je voulais juste dire bonjour.";
			link.l2.go = "exit";			
			NextDiag.TempNode = "HWIC_Boss";
		break;
		
		case "silk_info":
			dialog.text = "J'ai récemment établi des connexions commerciales avec un marchand de Lyon pour approvisionner les Caraïbes en soie de navire. En avez-vous entendu parler? Les meilleures voiles du monde sont faites de cette soie, donc cela doit vous intéresser.";
			link.l1 = "Foudroye-moi, aye c'est une musique à mes oreilles. Quels sont tes conditions ?";
			link.l1.go = "silk_info_1";
		break;
		
		case "silk_info_1":
			dialog.text = "Petites mais régulières livraisons. Je peux vous réserver trente rouleaux toutes les deux semaines. Le coût d'un rouleau est de vingt doublons. Faisons ainsi : je vous réserverai trente rouleaux chaque premier et quinzième jour du mois. Si vous ne venez pas les chercher alors, je les vends à un autre client.";
			link.l1 = "Aucune obligation alors ?";
			link.l1.go = "silk_info_2";
		break;
		
		case "silk_info_2":
			dialog.text = "Précisément, kapitein. Achetez la soie si vous le souhaitez. Vous payez pour tout le lot - six cents doublons. J'espère que vous serez un client régulier.";
			link.l1 = "Merci pour votre proposition, mynheer. Marché conclu.";
			link.l1.go = "exit";
			NextDiag.TempNode = "HWIC_Boss";
			npchar.quest.silk_info = "true";
			npchar.quest.silk = "true";
			AddQuestRecordInfo("Unique_Goods", "3");
		break;
		
		// торговля шелком
		case "trade_silk":
			if (CheckAttribute(pchar, "questTemp.UpgradeSilk"))
			{
				dialog.text = "Bien sûr, kapitein. Votre soie vous attend. Êtes-vous prêt à payer pour elle ?";
				if (PCharDublonsTotal() >= 2550)
				{
					link.l1 = "Bien sûr ! Tenez, prenez 2550 doublons.";
					link.l1.go = "trade_silk_1";
				}
				else
				{
					link.l1 = "Mille sabords, j'ai oublié l'argent sur mon navire. Je l'apporte dans une seconde !";
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "Bien sûr, kapitein. Votre soie vous attend. Êtes-vous prêt à payer pour elle ?";
				if (PCharDublonsTotal() >= 600)
				{
					link.l1 = "Bien sûr ! Tenez, prenez six cents doublons.";
					link.l1.go = "trade_silk_1";
				}
				else
				{
					link.l1 = "Mille sabords, j'ai oublié l'argent sur mon navire. Je l'apporte dans une seconde !";
					link.l1.go = "exit";
				}
			}
			if(sti(pchar.questTemp.GVIKSilk) >= 1 && !CheckAttribute(pchar, "questTemp.GVIKSilkBlock")) // увеличить объём поставок шёлка
			{
				link.l4 = "Mijnheer "+npchar.name+", je voudrais discuter de la possibilité d'augmenter les livraisons de soie.";
				link.l4.go = "UpgradeSilk";
			}
			if(sti(pchar.questTemp.GVIKSilk) >= 1 && CheckAttribute(pchar, "questTemp.GVIKSilkPotom") && PCharDublonsTotal() >= 3000) // увеличить объём поставок шёлка, если в первый раз не принесли
			{
				link.l4 = "J'ai apporté vos doublons, Mijnheer "+npchar.name+". Veuillez les accepter.";
				link.l4.go = "UpgradeSilk_Agreed";
			}
			NextDiag.TempNode = "HWIC_Boss";
		break;
		
		case "trade_silk_1":
			RemoveDublonsFromPCharTotal(600);
			Log_Info("You have given 600 doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "Ce fut un plaisir de faire affaire avec vous, kapitein. Votre soie sera livrée à votre navire par chaloupe.";
			link.l1 = "Merci !";
			link.l1.go = "trade_silk_2";
		break;
		
		case "trade_silk_2":
			dialog.text = "J'espère te revoir bientôt. Reviens encore.";
			link.l1 = "Bien sûr. À bientôt !";
			link.l1.go = "exit";
			AddCharacterGoods(pchar, GOOD_SHIPSILK, 30);
			DeleteAttribute(npchar, "quest.silk");
			SetFunctionTimerCondition("Silk_TraderAttrReturn", 0, 0, 1, false); // таймер
			AddCharacterExpToSkill(pchar, "Commerce", 150);
			NextDiag.TempNode = "HWIC_Boss";
		break;
		
		case "UpgradeSilk": //
			if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) >= 80)
			{
				dialog.text = "J'apprécie votre approche commerciale et je suis prêt à examiner votre demande. Nous pourrions peut-être augmenter le volume, disons, cinq fois. Cependant, l'organisation de telles fournitures nécessitera des ressources importantes. Nous devrons agrandir l'espace de stockage, renforcer la sécurité et assurer des voies de livraison fiables. Comme cela vous profite également, je suggère que nous partagions ces dépenses entre nous.";
				link.l1 = "Tout cela semble raisonnable. Quel montant considérez-vous nécessaire pour couvrir ces dépenses ?";
				link.l1.go = "UpgradeSilk_1";
				notification("Skill Check Passed", SKILL_COMMERCE);
			}
			else
			{
				dialog.text = "Je comprends votre intérêt à augmenter les approvisionnements, cependant à ce stade, il m'est difficile d'accepter de tels changements. Je ne doute pas de votre aspiration au développement, mais ce genre de transaction nécessite beaucoup plus d'expérience dans les affaires commerciales et de confiance dans vos propres actions. Je vous suggère d'accroître vos connaissances dans l'art de la négociation, puis de revenir me voir avec une proposition plus précise. Quand vous serez prêt, je serai heureux de renforcer notre coopération.";
				link.l1 = "Hmm... Bien. Je reviendrai à cette conversation plus tard.";
				link.l1.go = "exit";
				notification("Skill Check Failed (80)", SKILL_COMMERCE);
			}
			NextDiag.TempNode = "HWIC_Boss";
		break;
		
		case "UpgradeSilk_1":
			dialog.text = "Compte tenu de toutes les nuances, votre part des dépenses sera de trois mille doublons d'or. Ces fonds nous permettront d'organiser les mesures nécessaires sans délai.";
			link.l1 = "Mijnheer "+npchar.name+", trois mille doublons ? Est-ce une plaisanterie ? Je suis venu"+GetSexPhrase("","e")+" vous voir avec une proposition honnête, et vous voulez que je paie une somme aussi exorbitante pour l'organisation des approvisionnements ?";
			link.l1.go = "UpgradeSilk_2";
		break;
		
		case "UpgradeSilk_2":
			dialog.text = "Je vous demande de me comprendre correctement. Je n'essaie pas de vous tromper. Cet argent est le montant qui nous permettra d'assurer le bon ordre dans l'organisation des approvisionnements. Il ne s'agit pas seulement d'agrandir les entrepôts et d'assurer la sécurité, mais aussi de garantir la livraison des marchandises sans retards ni pertes, malgré toute l'imprévisibilité de cette affaire. Ce sont des dépenses standard pour de tels volumes. Au final, vos investissements se justifieront, et vous recevrez les marchandises en bon état et à temps.";
			link.l1 = "Vos explications sont quelque peu rassurantes, mijnheer. Mais ce montant reste tout de même trop élevé. Je suis prêt"+GetSexPhrase("","e")+" à accepter vos conditions si vous baissez le prix à au moins deux mille cinq cents doublons. Je suis sûr"+GetSexPhrase("","e")+" que cela sera suffisant pour organiser les approvisionnements et respecter toutes les mesures de sécurité.";
			link.l1.go = "UpgradeSilk_3";
		break;
		
		case "UpgradeSilk_3":
			dialog.text = "Je comprends, le montant est important, mais comme je l'ai déjà dit, il est nécessaire pour la bonne exécution du travail. Je ne peux pas le réduire, car cela compromettrait tous nos efforts. Cependant, pour que vous ne vous sentiez pas trompé"+GetSexPhrase("","e")+", je suis prêt à vous offrir une remise de quinze pour cent sur toutes les fournitures futures. Cela, j'espère, vous permettra de compenser les dépenses.";
			if (PCharDublonsTotal() >= 3000)
			{
				link.l1 = "Hmm, une remise de quinze pour cent est, bien sûr, un pas en avant. D'accord. Je suis prêt"+GetSexPhrase("","e")+" à accepter votre offre, même si le prix me semble extrêmement élevé. J'espère que notre coopération répondra à mes attentes. Voici votre argent.";
				link.l1.go = "UpgradeSilk_Agreed";
			}
			link.l2 = "Mijnheer "+npchar.name+", votre offre ne me laisse pas le choix. Que ce soit trois mille doublons, bien que ce soit une somme considérable. Cependant, je ne peux pas tout payer d'un coup maintenant. Je reviendrai dès que j'aurai l'argent.";
			link.l2.go = "UpgradeSilk_5";
			link.l3 = "Une remise de quinze pour cent ? Mijnheer "+npchar.name+", ce n'est pas ce à quoi je m'attendais. Ce montant n'est pas seulement des dépenses, c'est un vol pur et simple ! Mais je n'ai pas l'intention de rompre les relations commerciales avec vous. Nous reviendrons aux conditions précédentes - 30 rouleaux de soie à 20 doublons chacun.";
			link.l3.go = "UpgradeSilk_4";
		break;
		
		case "UpgradeSilk_Agreed":
			dialog.text = "Je suis heureux que vous ayez accepté, "+pchar.name+". Maintenant, concernant les détails : 150 rouleaux de soie à 17 doublons chacun. Total - 2550 doublons pour tout le lot. Vous pourrez récupérer les marchandises comme d'habitude - les 1er et 15 de chaque mois. Je pense que cette affaire apportera un bon profit aux deux parties.";
			link.l1 = "Отлично! Вот это - уже неплохой размах. Всего доброго, минхер. Скоро увидимся.";
			link.l1.go = "exit";
			NextDiag.TempNode = "HWIC_Boss";
			RemoveDublonsFromPCharTotal(3000);
			AddQuestRecordInfo("Unique_Goods", "3_1");
			pchar.questTemp.UpgradeSilk = true;
			pchar.questTemp.GVIKSilkBlock = true;
			DeleteAttribute(pchar, "questTemp.GVIKSilkPotom");
		break;
		
		case "UpgradeSilk_4":
			dialog.text = "Ce n'est qu'une approche commerciale, et non un vol, comme cela aurait pu vous sembler. Mais comme vous voudrez. Venez comme d'habitude, les 1er et 15, pour un lot de soie, je serai heureux de conclure une nouvelle affaire";
			link.l1 = "Certainement, mijnheer. Au revoir.";
			link.l1.go = "exit";
			pchar.questTemp.GVIKSilkBlock = true;
			NextDiag.TempNode = "HWIC_Boss";
		break;
		
		case "UpgradeSilk_5":
			dialog.text = "Je suis heureux que vous ayez pris la bonne décision. Dès que vous apporterez l'argent, nous discuterons de tous les détails de l'affaire et procéderons à sa mise en œuvre.";
			link.l1 = "Au revoir, Mijnheer "+npchar.name+". À bientôt, dès que j'aurai rassemblé la somme nécessaire.";
			link.l1.go = "exit";
			pchar.questTemp.GVIKSilkBlock = true;
			pchar.questTemp.GVIKSilkPotom = true;
			NextDiag.TempNode = "HWIC_Boss";
		break;
		
		case "fight":
			DialogExit();
			sld = characterFromId("HWIC_officer");
			LAi_SetGuardianTypeNoGroup(sld);
			LAi_group_Attack(sld, Pchar);
			for (i=1; i<=6; i++)
			{	
				sld = characterFromId("HWIC_sold_"+i);
				LAi_group_Attack(sld, Pchar);
			}
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
