// Альберт Локсли - адвокат
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, n;
    string sTemp, attrLoc;
	
    attrLoc = Dialog.CurrentNode;
	int iSumm = 0;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	if (findsubstr(attrLoc, "RelationTo_" , 0) != -1)
	{
		i = findsubstr(attrLoc, "_" , 0);
		npchar.quest.relation = strcut(attrLoc, i+1, strlen(attrLoc)-1); // индех в конце
		// проверка на уже договор
		attrLoc = "RelationAgent" + GetNationNameByType(sti(npchar.quest.relation));
		if (CheckAttribute(Pchar, "GenQuest." + attrLoc) && sti(Pchar.GenQuest.(attrLoc)) == true)
		{
			Dialog.CurrentNode = "RelationYet";
		}
		else
		{
			Dialog.CurrentNode = "RelationAny_Done";
			npchar.quest.relation.summ = CalculateRelationLoyerSum(sti(npchar.quest.relation));
		}
	}
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Je m'appelle Albert Loxley et je suis avocat. Je défends les intérêts de mes clients lors des procès. Mes services sont coûteux, mais ils en valent la peine, je vous l'assure.";
				if(SandBoxMode)
				{					
					if (ChangeCharacterNationReputation(pchar, ENGLAND, 0) < 0)
					{
						link.l1 = "Je suis en difficulté avec les autorités anglaises.";
						link.l1.go = "RelationTo_0";
					}
					
					if (ChangeCharacterNationReputation(pchar, FRANCE, 0) < 0)
					{
						link.l2 = "Je suis en difficulté avec les autorités françaises.";
						link.l2.go = "RelationTo_1";
					}
					if (ChangeCharacterNationReputation(pchar, SPAIN, 0) < 0)
					{
						link.l3 = "Je suis en difficulté avec les autorités espagnoles.";
						link.l3.go = "RelationTo_2";
					}

					if (ChangeCharacterNationReputation(pchar, HOLLAND, 0) < 0)
					{
						link.l4 = "Je suis en difficulté avec les autorités néerlandaises.";
						link.l4.go = "RelationTo_3";
					}
					if (ChangeContrabandRelation(pchar, 0) <= 5)
					{
						Link.l5 = "Je me suis querellé avec les contrebandiers.";
						Link.l5.go = "contraband";
					}
					Link.l7 = "Merci mais, heureusement, je n'ai pas besoin des services d'un avocat pour l'instant.";
					Link.l7.go = "exit";
					NextDiag.TempNode = "Loxly";
					npchar.quest.meeting = "1";
				}
				link.l1 = "Merci mais, heureusement, je n'ai pas encore besoin des services d'un avocat.";
				link.l1.go = "exit";
				npchar.quest.meeting = "1";
				if (CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "loxly")
				{
					link.l1 = "J'ai besoin de vos services. Je suis un délégué autorisé d'une jeune dame nommée Helen McArthur, elle est la petite-fille du célèbre Nicolas Sharp. Elle est l'unique héritière légale après la mort de sa mère et de son oncle. Elle a tous les droits sur Isla Tesoro selon le testament de son oncle. Combien demanderiez-vous pour aider Helen à devenir la légitime maîtresse de l'île ?";
					link.l1.go = "saga";
				}
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.Saga"))
				{
					if (pchar.questTemp.Saga == "loxly") // первое обращение по саге
					{
						dialog.text = "Avez-vous besoin de mes services, monsieur ? Vous serez satisfait, je vous l'assure.";
						link.l1 = "Oui, j'ai besoin d'eux. Je suis un délégué autorisé d'une jeune demoiselle nommée Helen McArthur, elle est la petite-fille du célèbre Nicolas Sharp. Elle est la seule héritière légale après la mort de sa mère et de son oncle. Elle a tous les droits sur Isla Tesoro selon le testament de son oncle. Combien demanderiez-vous pour aider Helen à devenir la maîtresse légitime de l'île ?";
						link.l1.go = "saga";
						break;
					}
					if (pchar.questTemp.Saga == "bakaut")
					{
						dialog.text = "Monsieur, je ne suis pas encore familier avec les matières de votre affaire. Je vous prie de revenir plus tard, comme je vous l'ai déjà dit.";
						link.l1 = "Très bien.";
						link.l1.go = "exit";
						break;
					}
					if (pchar.questTemp.Saga == "molligan" || pchar.questTemp.Saga == "sellbakaut")
					{ // если не выполнил до конца квест по бакауту
						dialog.text = "Monseigneur, malheureusement, j'ai besoin de plus de temps pour rassembler tous les papiers nécessaires dans les archives. Je ne suis pas encore prêt. Je vous prie de revenir plus tard.";
						link.l1 = "Très bien.";
						link.l1.go = "exit";
						break;
					}
					if (pchar.questTemp.Saga == "removebakaut") // с бакаутом разобрались
					{
						// четвертая проверка времени
						if (CheckAttribute(pchar, "questTemp.Saga.Late"))
						{
							RemoveItems(pchar, "map_sharp_full", 1);
							dialog.text = "Monsieur, pourquoi avez-vous travaillé si lentement ?! C'en est fini pour votre principal. La période de validation du testament a expiré et Isla Tesoro appartient désormais à l'Angleterre. Elle deviendra bientôt une base militaire."link.l1 ="Ouah ! Il semble que tous mes efforts ont été vains...";
							link.l1.go = "saga_l3";
						}
						else
						{
							dialog.text = "Ah, vous voilà, Monsieur. Je me suis familiarisé avec les matériaux, il est donc temps pour un paiement anticipé. Avez-vous apporté les doublons avec vous ?";
							if(CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold")) {n = 1000;}
							else {n = 450;}
							if (PCharDublonsTotal() >= n)
							{
								link.l1 = "Oui, je les ai. Voici vos doublons.";
								link.l1.go = "saga_5";
							}
							else
							{
								link.l1 = "Pardonnez-moi pour ma mauvaise mémoire, je les ai laissés dans un coffre sur mon navire. Je les apporterai tout de suite.";
								link.l1.go = "exit";
							}
						}
						break;
					}
					if (pchar.questTemp.Saga == "shadow")
					{
						// пятая проверка времени
						if (CheckAttribute(pchar, "questTemp.Saga.Late"))
						{
							dialog.text = "Monsieur, pourquoi avez-vous travaillé si lentement ?! Tout est fini pour votre principal. Le délai de validation du testament a expiré et Isla Tesoro appartient désormais à l'Angleterre. Cela deviendra bientôt une base militaire."link.l1 ="Ouah ! Il semble que tous mes efforts aient été vains...";
							link.l1.go = "saga_l3";
						}
						else
						{
							dialog.text = "Monseigneur, avez-vous pu trouver quelque chose qui puisse prouver la filiation de votre principal ?";
							if (!CheckCharacterItem(pchar, "Letter_beatriss"))
							{
								link.l1 = "Pas encore. Mais j'y travaille.";
								link.l1.go = "exit";
							}
							else
							{
								link.l1 = "Oui. J'ai vraiment des preuves exhaustives.";
								link.l1.go = "saga_14";
							}
						}
						break;
					}
					if (pchar.questTemp.Saga == "court" && GetNpcQuestPastDayParam(npchar, "court_date") >= 1 && IsOfficer(characterFromId("Helena")))
					{
						 // запрет сохранения чтобы ленку не заграбастали себе умники всякие с ГК-  лесник
						InterfaceStates.Buttons.Save.enable = false;//запретить сохраняться																																			   
						dialog.text = "A-ah, vous voilà, Monsieur. Heureux de vous voir. Je dois admettre, je vous attends depuis un bon moment. Est-ce votre principal?";
						link.l1 = "Oui. Permettez-moi de vous présenter Helen McArthur.";
						link.l1.go = "saga_26";
						break;
					}
					dialog.text = "Avez-vous besoin de mes services, Monsieur ? Vous serez satisfait, je vous l'assure.";
					link.l1 = "Merci, mais je n'en ai pas besoin pour l'instant.";
					link.l1.go = "exit";
				}
				if (CheckAttribute(npchar, "quest.waitgold"))
				{
					dialog.text = "Bonjour, Monsieur. Je suppose que vous avez apporté mon paiement ?";
					if (PCharDublonsTotal() >= 450)
					{
						link.l1 = "Oui, je les ai. Voici vos doublons.";
						link.l1.go = "saga_36";
					}
					link.l2 = "Vous savez, Monsieur Loxley, je pensais... Ce que je veux dire, c'est que 900 doublons, c'est plus que suffisant pour votre travail.";
					link.l2.go = "saga_38";
					link.l3 = "Je me souviens, Monsieur Loxley. Je l'apporterai un peu plus tard...";
					link.l3.go = "exit";
					break;
				}
				dialog.text = "Avez-vous besoin de mes services, monsieur ? Vous serez satisfait, je vous l'assure.";
				link.l1 = "Merci, mais je n'en ai pas besoin pour l'instant.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "saga":
			// третья проверка времени. Отбираем Элен, чистим квестовый лут, даем флаг на Свенсона, вызываем перемены
			if (CheckAttribute(pchar, "questTemp.Saga.Late"))
			{
				RemoveItems(pchar, "map_sharp_full", 1);
				dialog.text = "Monseigneur, vous avez dû passer trop de temps en mer. Isla Tesoro est désormais une base militaire de la Marine anglaise ! Oui, le testament de Sharp existe mais il a expiré et Isla Tesoro est devenue propriété de la couronne anglaise. Hélas !"link.l1 ="Wow ! Il semble que tous mes efforts ont été vains...";
				link.l1.go = "saga_l3";
			}
			else
			{
				dialog.text = "La dame prétend posséder toute l'île ? Hm... Il semble que ce ne sera pas une affaire facile. Isla Tesoro est déjà presque une colonie anglaise...";
				link.l1 = "Pas encore. Selon le testament, l'homme ou la femme qui montre les deux parties de la carte deviendra le propriétaire de l'Isla Tesoro. Nous avons les deux parties de la carte de Sharp qui est la principale preuve d'héritage.";
				link.l1.go = "saga_1";
			}
		break;
		
		case "saga_1":
			dialog.text = "Nicolas Sharp... Eh bien, eh bien. Je dois visiter les archives et me familiariser avec les documents concernant Isla Tesoro. As-tu la carte avec toi ?";
			link.l1 = "Je l'ai, mais je ne te le donnerai qu'après que nous ayons signé un contrat. Alors, qu'en est-il du prix pour tes services ?";
			link.l1.go = "saga_2";
		break;
		
		case "saga_2":
			sTemp = "";
			if(CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold")) sTemp = " Your esteemed involvement won't go unnoticed either. Cartagena... There will be questions.";
			dialog.text = "Comme je l'ai dit - ce ne sera pas facile. Vous devez prouver le droit de propriété d'une île entière, pas d'une vieille barque ou d'une cabane. De plus, Nicolas Sharp était un pirate et aider les pirates ou leurs proches coûte cher."+sTemp;
			link.l1 = "Tu vas me donner un chiffre exact ?";
			link.l1.go = "saga_3";
		break;
		
		case "saga_3":
			sTemp = "four hundred and fifty";
			if(CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold")) sTemp = "one thousand";
			dialog.text = "Monsieur, la somme finale sera déterminée lors du procès. Je ne sais toujours pas à quel point cela sera problématique. Mais je suis prêt à estimer un acompte - "+sTemp+"doublons. Cette somme d'or devra être payée à nouveau une ou deux fois, selon la réussite de notre affaire.\nApportez-moi l'argent dans une semaine, j'ai besoin de temps pour vérifier les archives et me préparer. Ensuite, nous conclurons un accord. Marché conclu ?";
			link.l1 = "Ils vous ont recommandé comme le meilleur avocat de l'archipel, alors nous avons un accord. À la semaine prochaine !";
			link.l1.go = "saga_4";
		break;
		
		case "saga_4":
			DialogExit();
			pchar.questTemp.Saga = "bakaut"; // обновляем флаг
			AddQuestRecord("Testament", "2");
			if(CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold")) AddQuestUserData("Testament", "sMoney", "1000");
			else AddQuestUserData("Testament", "sMoney", "450");
			
			if (pchar.questTemp.HelenDrinking.Result != "no_visit") {
				bDisableFastReload = true;
				SetFunctionLocationCondition("HelenDrinking_PortRoyalDialog", "PortRoyal_town", false);
			}
		break;
		
		case "saga_5":
			if(CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold"))
			{
				RemoveDublonsFromPCharTotal(1000);
				//Log_Info("You have given 1450 doubloons");
			}
			else
			{
				RemoveDublonsFromPCharTotal(450);
				//Log_Info("You have given 450 doubloons");
			}
			PlaySound("interface\important_item.wav");
			dialog.text = "Très bien. Je suis prêt à prendre votre affaire en main et à représenter vos intérêts au tribunal. Passons maintenant aux choses sérieuses. J'ai bien travaillé dans les archives et j'ai parlé avec des personnes importantes. L'affaire de l'héritage de Sharp ne va pas être facile. Heureusement que vous avez acquis les deux morceaux de la carte. Mais cela pourrait ne pas suffire.\nLe colonel Doyle a de grands projets pour Isla Tesoro, puisqu'il n'a pas réussi à prendre le contrôle de la Tortue. Elle a des défenses naturelles et pourrait servir de future base militaire dans cette région.";
			link.l1 = "Mais Helene a tous les droits sur l'île selon la loi d'Angleterre !";
			link.l1.go = "saga_6";
		break;
		
		case "saga_6":
			dialog.text = "Vous ne savez peut-être pas que feu Sharp a ajouté une clause à son testament. Un héritier ou des héritiers doivent porter son nom de famille. Et si je me souviens bien, votre fille a un autre nom de famille. Vous avez dit que c'était McArthur, n'est-ce pas ?";
			link.l1 = "C'est le nom de famille de son beau-père, mais Hélène a tous les droits de porter Sharp comme son nom de famille, car elle est la fille de feue Béatrice Sharp, la fille de Nicolas.";
			link.l1.go = "saga_7";
		break;
		
		case "saga_7":
			dialog.text = "Splendide ! Mais qui peut confirmer cela sous serment ? Les parents adoptifs d'Helen connaissaient-ils Beatrice Sharp ?";
			link.l1 = "Autant que je comprenne, il ne l'était pas. Monsieur McArthur la considérait comme la fille de Gladys et Gladys n'était qu'une connaissance du père de la fille.";
			link.l1.go = "saga_8";
		break;
		
		case "saga_8":
			dialog.text = "C'est bien dommage. Voyez-vous, je n'ai trouvé aucune mention dans les archives que Beatrice Sharp ait jamais eu de descendance. Il est possible qu'il n'y ait aucune note officielle concernant la naissance de l'enfant. N'importe qui peut se prétendre petit-enfant de Sharp et revendiquer le droit de porter son nom.";
			link.l1 = "Mais seule Hélène a la carte complète !";
			link.l1.go = "saga_9";
		break;
		
		case "saga_9":
			dialog.text = "C'est son atout majeur et cela pourrait suffire si les autorités locales n'avaient pas leurs propres plans pour Isla Tesoro. Un document avec l'écriture de Béatrice et sa signature est dans les archives. Nous devons trouver un document écrit par elle qui prouverait la naissance de sa fille, la fille qui a été donnée à cette Gladys... eh, quel était son nom de famille ?";
			link.l1 = "Chandler. Gladys Chandler de Belize.";
			link.l1.go = "saga_10";
		break;
		
		case "saga_10":
			dialog.text = "Exactement. Avez-vous l'opportunité de trouver quelque chose comme ça ?";
			link.l1 = "J'en doute. Trop d'années ont passé. Selon la légende, le capitaine Butcher lui-même pourrait être le père d'Helen. Peut-être que l'ex-bourreau de St. John's peut nous en dire quelque chose. C'était le dernier homme à avoir vu son père vivant.";
			link.l1.go = "saga_11";
		break;
		
		case "saga_11":
			dialog.text = "Hm. Il était vraiment un homme divertissant. Autant que je me souvienne, son nom était Raymond Baker. J'ai eu la chance de discuter avec lui une fois. C'est un homme intelligent et bien éduqué. Eh bien, essayez de trouver quelque chose à Antigua et je vais continuer mes recherches dans les archives, peut-être que je trouverai quelque chose d'utile.";
			link.l1 = "Bien. Ça me convient.";
			link.l1.go = "saga_12";
		break;
		
		case "saga_12":
			dialog.text = "Donne-moi la carte de Sharp et dépêche-toi, parle à Baker, peut-être que tu pourras trouver des documents avec son aide. Tu pourrais même trouver des preuves de sa naissance.";
			link.l1 = "Eh, j'aimerais bien pouvoir. Bien, à plus, Monsieur Loxley.";
			link.l1.go = "saga_13";
		break;
		
		case "saga_13":
			DialogExit();
			RemoveItems(pchar, "map_sharp_full", 1);
			pchar.questTemp.Saga = "shadow";
			pchar.questTemp.Saga.Shadows = "sentjons";
			AddQuestRecord("Shadows", "1");
		break;
		
		case "saga_14":
			dialog.text = "Vraiment ? Voyons voir ces preuves.";
			link.l1 = "C'est une lettre privée écrite par Beatrice Sharp à son frère. Il est écrit ici qu'elle a donné naissance à une fille et que son père était en fait Lawrence Beltrope. La fille a été envoyée chez une jeune veuve nommée Gladys Chandler. Lawrence Beltrope est également connu sous le nom de capitaine Boucher. Tenez, prenez la lettre...";
			link.l1.go = "saga_15";
		break;
		
		case "saga_15":
			RemoveItems(pchar, "Letter_beatriss", 1);
			dialog.text = "";
			link.l1 = "Gladys est prête à le confirmer sous serment. Elle est également prête à confirmer que le père s'était présenté comme le capitaine Boucher.";
			link.l1.go = "saga_16";
		break;
		
		case "saga_16":
			if (CheckAttribute(pchar, "questTemp.Saga.Beltrop_die")) // Белтроп убит
			{
				dialog.text = "Minute ! Le capitaine Butcher, le méchant pirate et meurtrier de sujets anglais, a été pendu dans le fort de Saint-Jean il y a vingt ans. Et Lawrence Beltrope, un proche ami de Richard Doyle, est tragiquement décédé il n'y a pas longtemps. Et surtout, Doyle voulait faire de lui le nouveau gouverneur de Sharptown !";
				link.l1 = "Ha ! Bien sûr, personne ne sait cela... J'ai un témoignage écrit de Raymond Baker, l'ancien bourreau de St. John's, affirmant qu'il a été obligé sous la menace d'une mort certaine de simuler l'exécution de Butcher ! Tenez, jetez un œil...";
				link.l1.go = "saga_17";
			}
			else
			{
				dialog.text = "Attendez une minute ! Le capitaine Boucher, le redoutable pirate et meurtrier de sujets anglais a été pendu dans le fort de St. John's il y a vingt ans. Et Lawrence Beltrope est vivant et réside dans l'une des plus belles demeures de Port Royal. Et surtout, Doyle veut en faire le nouveau gouverneur de Sharptown !";
				link.l1 = "Ha! Bien sûr, personne ne sait cela... J'ai un témoignage écrit de Raymond Baker, l'ancien bourreau de St. John's, qu'il a été forcé sous la menace d'une mort certaine de simuler l'exécution de Butcher ! Tenez, regardez...";
				link.l1.go = "saga_17";
			}
		break;
		
		case "saga_17":
			RemoveItems(pchar, "letter_baker", 1);
			dialog.text = "Hum. Eh bien, eh bien...";
			link.l1 = "N'est-ce pas très habile ? Le capitaine Boucher a réussi à rester en vie et est retourné en Angleterre. Il a repris son nom de Lawrence Beltrope et est revenu ici incognito.";
			if (CheckAttribute(pchar, "questTemp.Saga.Beltrop_die")) link.l1.go = "saga_18";
			else link.l1.go = "saga_22";
		break;
		
		case "saga_18":
			dialog.text = "Mais cela... Cela change tout ! Publier la lettre de Béatrice montrera que tout ce temps, le gouverneur militaire cachait le pirate fugitif Boucher, qui aurait dû être arrêté sur-le-champ et qui aurait dû comparaître devant le tribunal pour ses crimes passés !\nEt le témoignage de Baker détruira complètement toutes les raisons contre cela ! C'est formidable ! Avec un tel atout en main, nous battrons Doyle à plate couture !";
			link.l1 = "Je suis content. Je compte sur toi pour cette épreuve. Dis-moi aussi, comment est mort Lawrence Beltrope ?";
			link.l1.go = "saga_19";
		break;
		
		case "saga_19":
			dialog.text = "C'est une histoire sinistre, Monsieur. Il a été retrouvé dans sa propre chambre avec un visage tordu. Il est trop difficile d'imaginer ce qui a pu effrayer cet homme intrépide à ce point. On dit qu'il était couvert de givre. Son corps était rempli de blessures déchirantes et effrayantes, mais pas une seule goutte de sang sur le sol ! Imaginez-vous ! Pas une seule goutte !";
			link.l1 = "Oui, cela semble tout droit sorti d'un cauchemar. Il semble qu'il ait été assassiné... Mais qui aurait pu faire cela ?";
			link.l1.go = "saga_20";
		break;
		
		case "saga_20":
			dialog.text = "Il est inconnu. C'est trop embrouillé... Le médecin de la garnison a dit que ses blessures n'étaient pas mortelles. Beltrope est mort de peur, de douleur ou d'autre chose. Quoi qu'il en soit, c'est une mort mystique.";
			link.l1 = "Je vois... Et quand le procès commencera-t-il ?";
			link.l1.go = "saga_21";
		break;
		
		case "saga_21":
			dialog.text = "Tout dépend de vous, Monsieur. Je soumettrai tous les documents au tribunal dès que vous me paierez la seconde partie de mes honoraires - 450 doublons. Helen obtiendra ses droits une semaine après cela.";
			if (PCharDublonsTotal() >= 450)
			{
				link.l1 = "Très bien. Voici vos doublons.";
				link.l1.go = "saga_24";
			}
			else
			{
				link.l1 = "Oui, bien sûr. Je vous apporterai la somme dont vous avez besoin.";
				link.l1.go = "exit";
				NextDiag.TempNode = "saga_23";
			}
		break;
		
		case "saga_23":
			// шестая проверка времени
			if (CheckAttribute(pchar, "questTemp.Saga.Late"))
			{
				dialog.text = "Monsieur, vous m'avez abasourdi ! Vous avez fait tant de choses, l'île était presque entre nos mains mais tout est fini maintenant à cause de votre retard avec mon paiement ! Le testament a expiré et Isla Tesoro appartient maintenant à la couronne anglaise. Ce sera une base militaire."link.l1 ="Ouah ! Il semble que tous mes efforts ont été vains...";
				link.l1.go = "saga_l3";
			}
			else
			{
				dialog.text = "Avez-vous apporté la deuxième partie de mes honoraires, Monsieur ?";
				if (PCharDublonsTotal() >= 450)
				{
					link.l1 = "Oui, bien sûr. Voici vos doublons.";
					link.l1.go = "saga_24";
				}
				else
				{
					link.l1 = "Excusez-moi pour ma mauvaise mémoire, je les ai laissés dans un coffre sur mon navire. Je les apporterai tout de suite.";
					link.l1.go = "exit";
					NextDiag.TempNode = "saga_23";
				}
			}
		break;
		
		case "saga_22":
			dialog.text = "Mais ça... ça change tout ! Publier la lettre de Beatrice signifiera que Lawrence Beltrope doit être arrêté immédiatement et comparaître en justice pour ses crimes passés !\nEt le témoignage de Baker détruira complètement toutes les raisons contre cela ! C'est formidable ! Avec un tel atout en main, nous battrons Doyle à plate couture !";
			link.l1 = "Je suis très content. Quand commencera le procès ?";
			link.l1.go = "saga_21";
		break;
		
		case "saga_24":
			RemoveDublonsFromPCharTotal(450);
			//Log_Info("You have given 450 doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "Excellent, Monsieur. Un plaisir de faire affaire avec vous. Maintenant, voici l'accord. Revenez ici demain. Oui-oui, vous avez bien entendu - demain ! Après tout, je suis le meilleur avocat de l'archipel et j'ai des relations.\nAmenez votre cliente, le procès n'aura pas lieu sans elle. Ne soyez pas en retard et ne quittez pas la ville. Et prenez la dernière partie du paiement avec vous si vous le pouvez, je suis absolument certain de notre victoire.";
			link.l1 = "Bien. Nous serons à votre bureau demain, Monsieur Loxley.";
			link.l1.go = "saga_25";
		break;
		
		case "saga_25":
			DialogExit();
			SaveCurrentNpcQuestDateParam(npchar, "court_date");
			pchar.questTemp.Saga = "court"; // обновляем флаг
			AddQuestRecord("Testament", "10");
			NextDiag.CurrentNode = "First time";
			// закрываем выходы из города
			LocatorReloadEnterDisable("PortRoyal_town", "reload1_back", true);
			//LocatorReloadEnterDisable("PortRoyal_town", "reload2_back", true);// лесник там нет этого пирса
			LocatorReloadEnterDisable("PortRoyal_town", "gate_back", true);
			//pchar.GenQuest.CannotWait = true;//запрет ожидания
			// снимаем общий таймер Саги!
			pchar.quest.Saga_TimeOver.over = "yes";
		break;
		
		case "saga_26":
			dialog.text = "MacArthur ? Non, c'est Sharp ! Eh bien, suivez-moi maintenant !";
			link.l1 = "...";
			link.l1.go = "saga_27";
		break;
		
		case "saga_27":
			DialogExit();
			ChangeCharacterAddressGroup(npchar, pchar.location, "goto", "goto10");
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			sld = characterFromId("Helena");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(npchar, "reload", "reload1", "Saga_CourtGo", -1);
			LAi_ActorFollow(pchar, npchar, "", -1);
			LAi_ActorFollow(sld, npchar, "", -1);
			NextDiag.CurrentNode = "saga_28";
			// открываем выходы из города
			//LocatorReloadEnterDisable("PortRoyal_town", "reload1_back", false); // лесник рано 
			//LocatorReloadEnterDisable("PortRoyal_town", "reload2_back", false);
			//LocatorReloadEnterDisable("PortRoyal_town", "gate_back", false);
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
		break;
		
		case "saga_28":
			dialog.text = "Permettez-moi de vous féliciter, Monsieur, ainsi que votre principale. Elle est maintenant la souveraine légitime de l'Ile Tesoro. Cela mérite bien de boire un peu de champagne !";
			link.l1 = "Absolument, Monsieur Loxley. Votre discours était des plus excellents. Je pensais que le colonel Doyle allait avoir une crise cardiaque quand vous avez dit à la cour que Lawrence Beltrop est le capitaine Boucher.";
			link.l1.go = "saga_29";
		break;
		
		case "saga_29":
			dialog.text = "Oui, monsieur Doyle devra dire adieu à son rêve d'une base militaire sur Isla Tesoro. Et que peut-il faire ? La loi est la loi et elle est écrite pour tout le monde, même pour le respecté colonel.";
			if (CheckAttribute(pchar, "questTemp.Saga.Beltrop_die"))
			{
				link.l1 = "Tous les papiers sont-ils en règle et confirment-ils le droit d'Helen à l'île ?";
				link.l1.go = "saga_30";
			}
			else
			{
				link.l1 = "J'ai entendu dire que le juge a ordonné l'arrestation de Lawrence Beltrop. Je suppose qu'il va être pendu ?";
				link.l1.go = "saga_34";
			}
		break;
		
		case "saga_30":
			dialog.text = "Bien sûr, Monsieur. J'ai vérifié chaque virgule. Vous pouvez être sûr qu'ils sont en ordre.";
			link.l1 = "Très bien...";
			link.l1.go = "saga_31";
		break;
		
		case "saga_31":
			dialog.text = "Eh bien, mon travail est terminé. L'affaire était délicate mais nous l'avons gagnée ensemble. Maintenant, Monsieur, il ne vous reste plus qu'à me payer la dernière partie de mes honoraires. Pas de pression, je me rends compte que vous devez être occupé. Mais je crois que vous trouverez le temps de m'apporter les derniers 450 doublons d'ici une semaine.\nDe plus, un client comme vous peut toujours compter sur des réductions substantielles. Je peux beaucoup vous aider, j'ai des relations dans toutes les capitales de l'archipel, même dans les hostiles, donc tout problème juridique que vous rencontrez peut être réglé.";
			link.l1 = "Excellent. Maintenant je sais à qui demander.";
			link.l1.go = "saga_32";
		break;
		
		case "saga_32":
			dialog.text = "Je vous garantis une issue positive même dans les situations les plus difficiles.";
			link.l1 = "Bien. Je dois y aller maintenant, Helen et moi avons beaucoup à faire.";
			link.l1.go = "saga_33";
		break;
		
		case "saga_33":
			dialog.text = "Adieu, Monsieur.";
			link.l1 = "Adieu, Monsieur Loxley.";
			link.l1.go = "saga_35";
		break;
		
		case "saga_34":
			dialog.text = "Je suppose que oui, c'est le capitaine Boucher, un pirate et bandit. Bien qu'il ne soit pas à Port Royal maintenant. Il a eu la chance de partir, s'enfonçant dans les terres de l'île. Mais la chasse a commencé et il sera certainement attrapé.";
			link.l1 = "Je vois... Les papiers sont-ils en ordre ?";
			link.l1.go = "saga_30";
		break;
		
		case "saga_35":
			DialogExit();
			SetFunctionTimerCondition("Saga_RemainGoldLoxly", 0, 0, 10, false); // таймер на оплату услуг
			DoQuestReloadToLocation("PortRoyal_town", "quest", "quest3", "Saga_HelenaIslaTesoro");
			npchar.quest.waitgold = "true";
			pchar.questTemp.Saga = "lastpages";
			NextDiag.CurrentNode = "First time";
		break;
		
		case "saga_36":
			RemoveDublonsFromPCharTotal(450);
			//Log_Info("You have given 450 doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "Splendide ! Ce fut un plaisir de faire affaire avec vous, Monsieur ! Désormais, vous pouvez solliciter mon aide pour n'importe quelle affaire et bénéficier d'une réduction. Ennuis avec la loi, prime sur votre tête... Vous êtes le bienvenu. Je serai toujours heureux de vous voir.";
			link.l1 = "Il vaudrait mieux que je reste à l'écart des ennuis mais... les choses arrivent. Merci et adieu, Monsieur Loxley.";
			link.l1.go = "saga_37";
		break;
		
		case "saga_37":
			DialogExit();
			pchar.quest.Saga_RemainGoldLoxly.over = "yes"; //снять таймер
			NextDiag.CurrentNode = "Loxly"; // услуги адвоката
		break;
		
		case "saga_38":
			dialog.text = "Que voulez-vous dire, Monsieur ? Allez-vous rompre les termes de notre accord ?";
			link.l1 = "Exactement. J'ai fait la plupart du travail. Tu ne peux même pas imaginer ce que j'ai dû faire pour obtenir les preuves. Et toi, tu as simplement pris ces papiers et es allé au tribunal. Neuf cents doublons, c'est plus que suffisant, j'en suis certain.";
			link.l1.go = "saga_39";
		break;
		
		case "saga_39":
			dialog.text = "Vous parlez comme un pirate, Monsieur ! Eh bien, je ne deviendrai pas pauvre en perdant quatre cent cinquante doublons mais vous ne deviendrez pas riche non plus. En fait, vous venez de perdre bien plus ! Et peut-être perdrez-vous encore quelque chose à l'avenir... Quittez ma maison immédiatement et ne vous montrez plus jamais ici !";
			link.l1 = "Et je vais le faire. Adieu, Monsieur Loxley.";
			link.l1.go = "exit";
			NextDiag.TempNode = "saga_40";
			pchar.quest.Saga_RemainGoldLoxly.over = "yes"; //снять таймер
			LocatorReloadEnterDisable("PortRoyal_town", "houseSp4", true); // закроем вход к Локсли
			ChangeCharacterNationReputation(pchar, ENGLAND, -10);
		break;
		
		case "saga_40":
			dialog.text = "Je ne veux pas te parler. Dégage ou j'appelle les gardes !";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "saga_40";
		break;
		
		// провалы Саги
		case "saga_l3":
			dialog.text = "Monsieur, nous aurions gagné votre affaire si vous étiez venu me voir plus tôt. Le testament a expiré. Je suis désolé.";
			link.l1 = "Eh, je suis encore plus désolé ! Eh bien, adieu, Monsieur Loxley.";
			link.l1.go = "saga_l3_1";
			// Элен - к разговору
			sld = characterFromId("Helena");
			sld.quest.talk = "late_l3";
		break;
		
		case "saga_l3_1":
			DialogExit();
			pchar.quest.Saga_Late_3.win_condition.l1 = "Location_Type";
			pchar.quest.Saga_Late_3.win_condition.l1.location_type = "town";
			pchar.quest.Saga_Late_3.function = "Saga_HelenaTalk";
			Saga_ChangesIslatesoro(); // вызов перестановки на Исла-Тесоро
			pchar.questTemp.Saga = "late_l3"; // для Свенсона
		break;
		
	//-------------------------------------- адвокатские услуги ------------------------------------------------
		case "Loxly":
			dialog.text = TimeGreeting()+", Monsieur. Heureux de vous voir. Avez-vous besoin de mes services ?";
			link.l1 = "Oui. C'est pourquoi je suis ici.";
			link.l1.go = "loxly_1";
			link.l2 = "Non, heureusement je n'en ai pas besoin pour le moment. Je voulais juste te saluer.";
			link.l2.go = "exit";
			NextDiag.TempNode = "Loxly";
		break;
		
		case "loxly_1":
			dialog.text = "Je suis prêt à vous écouter. De quel genre d'aide avez-vous besoin ?";
			if (ChangeCharacterNationReputation(pchar, ENGLAND, 0) < 0)
			{
				link.l1 = "Je suis en difficulté avec les autorités anglaises.";
				link.l1.go = "RelationTo_0";
			}
			
			if (ChangeCharacterNationReputation(pchar, FRANCE, 0) < 0)
			{
				link.l2 = "Je suis en difficulté avec les autorités françaises.";
				link.l2.go = "RelationTo_1";
			}
			if (ChangeCharacterNationReputation(pchar, SPAIN, 0) < 0)
			{
				link.l3 = "Je suis en difficulté avec les autorités espagnoles.";
				link.l3.go = "RelationTo_2";
			}

			if (ChangeCharacterNationReputation(pchar, HOLLAND, 0) < 0)
			{
				link.l4 = "Je suis en difficulté avec les autorités néerlandaises.";
				link.l4.go = "RelationTo_3";
			}
			if (ChangeContrabandRelation(pchar, 0) <= 5)
            {
                Link.l5 = "Je me suis querellé avec les contrebandiers.";
				Link.l5.go = "contraband";
            }
			Link.l7 = "Je suis désolé, j'ai changé d'avis...";
			Link.l7.go = "exit";
			NextDiag.TempNode = "Loxly";
		break;
		
		case "RelationYet": // уже оплачено
			dialog.text = "Je travaille déjà sur votre affaire. Tout ira bien, je vous l'assure.";
			Link.l1 = "Merci. Je vais attendre.";
			Link.l1.go = "exit";
			NextDiag.TempNode = "Loxly";
		break;
		
		// --> снятие НЗГ
		case "RelationAny_Done":
			iSumm = sti(npchar.quest.relation.summ);
			int iRate = abs(ChangeCharacterNationReputation(pchar, sti(npchar.quest.relation), 0));
			if (iRate <= 10) sTemp = "Well, I wouldn't call that trouble. Just a little problem. I will settle the affair at once";
			if (iRate > 10 && iRate <= 30) sTemp = "Yes, your reputation is slightly spoiled but I don't see anything critical. I will settle the affair at once";
			if (iRate > 30 && iRate <= 60) sTemp = "Yes, you went down the wrong path with the authorities. It won't be easy but I am sure that I will be able to settle your disagreements without a hitch";
			if (iRate > 60 && iRate <= 90) sTemp = "And how did you do that, Sir? Your troubles are not just serious, they are really serious. The authorities are very eager to get you. I will have to put a lot of effort into settling your disagreements";
			if (iRate > 90) sTemp = "Well... The situation is catastrophic - you are claimed to be the most bitter enemy. It will be tough but I am the best lawyer in the Caribbean after all, so I will settle your disagreements";
			dialog.text = ""+sTemp+" avec "+XI_ConvertString(Nations[sti(npchar.quest.relation)].Name+"Abl")+". Cela te coûtera "+FindRussianMoneyString(iSumm)+".";
			if(sti(pchar.money) >= iSumm)
			{
				link.l1 = "Très bien, Monsieur Loxley, je suis d'accord. Voici votre argent et essayez de régler les choses dès que possible.";
				link.l1.go = "relation";
			}
			link.l2 = "Je n'ai pas la somme que vous demandez pour l'instant. Je reviendrai plus tard !";
			link.l2.go = "exit";
			NextDiag.TempNode = "Loxly";
		break;

		case "relation":
			dialog.text = "Ce fut un plaisir de faire affaire avec vous, Monsieur. Vous pouvez respirer à nouveau, votre problème disparaîtra dans les deux semaines. Veuillez éviter toute confrontation avec "+XI_ConvertString(Nations[sti(npchar.quest.relation)].Name+"Abl")+", pendant que je suis en pleine négociation.";
			link.l1 = "Bien, je prendrai en compte votre avertissement. Merci et adieu !";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -sti(npchar.quest.relation.summ));
			ChangeNationRelationFromRelationAgent(npchar);
			attrLoc = "RelationAgent" + GetNationNameByType(sti(npchar.quest.relation));
            Pchar.GenQuest.(attrLoc) = true;
			Pchar.GenQuest.(attrLoc).loyer = "true";
			NextDiag.TempNode = "Loxly";
		break;
		// <-- снятие НЗГ
		
		case "contraband":
			npchar.quest.contrasum = makeint(0.3*stf(Pchar.rank)/stf(Pchar.reputation.nobility)*60000);
			dialog.Text = "Et pourquoi as-tu fait cela ? Les contrebandiers sont de bons gars, ils sont honnêtes à leur manière. Nous avons tous besoin de vivre et de manger... Bon, ce n'est pas grave et cela ne te coûtera que "+FindRussianMoneyString(sti(npchar.quest.contrasum))+".";
			if(sti(Pchar.money) >= sti(npchar.quest.contrasum))
			{
				Link.l1 = "Très bien, Monsieur Loxley, je suis d'accord. Voici votre argent et essayez de régler les choses dès que possible.";
				Link.l1.go = "Contraband_Agreed";
			}
			Link.l2 = "Je n'ai pas la somme que vous demandez pour le moment. Je reviendrai plus tard !";
			Link.l2.go = "exit";
		break;
		
		case "Contraband_Agreed":
			dialog.Text = "Excellent, je règlerai votre problème. Ils voudront bientôt faire affaire avec vous à nouveau.";
			Link.l1 = "Merci !";
			Link.l1.go = "exit";
			ChangeContrabandRelation(pchar, GetIntByCondition(HasShipTrait(pchar, "trait23"), 25, 40));
			AddMoneyToCharacter(pchar, -sti(npchar.quest.contrasum));
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
