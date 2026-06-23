// Ричард Флитвуд - английский капитан
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng"))
			{
				if (pchar.questTemp.HWIC.Eng == "Start_main")
				{
					dialog.text = "Salutations, capitaine ! Ne te laisse pas distraire par mon apparence, je vais bien, presque aveugle, mais je vais bien. Permets-moi de me présenter, je suis Richard Fleetwood.";
					link.l1 = "Bonjour, c'est un plaisir de vous rencontrer, je suis capitaine "+GetFullName(pchar)+".";
					link.l1.go = "First_Task";
					DelLandQuestMark(npchar);
					break;
				}
				if (pchar.questTemp.HWIC.Eng == "GotoPortoffice")
				{
					if (int(Pchar.Ship.Type) != SHIP_NOTUSED)
					{
						dialog.text = "Je vous ai demandé d'amarrer votre navire. M'écoutez-vous seulement ?";
						link.l1 = "Bien sûr, je m'en occupe.";
						link.l1.go = "exit";
					}
					else
					{
						dialog.text = "Alors, vous êtes ici encore. Prenez le commandement du 'Valkyrie' - mon équipage est averti des détails - et naviguez vers Bridgetown. Visitez chaque personne d'intérêt dans la ville et répandez les rumeurs dont nous avons parlé. Ensuite, soyez prêt pour l'attaque du bâtard. Ne changez pas de navire et ne formez pas d'escadre, il soupçonnerait un piège sinon et ne se montrerait pas. Vous devez aborder son navire et le livrer à St. John's. Il est impératif que vous localisiez le journal de bord du pirate, car c'est la seule preuve que nous aurons jamais de l'implication de Lucas Rodenburg. Je suis sûr que vous vous en sortirez. Bon vent, capitaine.";
						link.l1 = "Gratitude! Je ferai le travail selon notre plan.";
						link.l1.go = "First_Task_3";
						DelLandQuestMark(npchar);
						DelMapQuestMarkCity("SentJons");
					}
					break;
				}
				if (pchar.questTemp.HWIC.Eng == "MirageTake")//а вот теперь начинается перебор кораблей
				{
					pchar.quest.ToAntiguaMirageOver.over = "yes"; //снять таймер
					int iMir = 0;
					int iVal = 0;
					for(i = 0; i < COMPANION_MAX; i++)
					{
						iTemp = GetCompanionIndex(PChar, i);
						if(iTemp > 0)
						{
							sld = GetCharacter(iTemp);
							pchar.questTemp.HWIC.Eng.CompanionIndex = sld.Index;
							if(int(RealShips[int(sld.ship.type)].basetype) == SHIP_MIRAGE)
							{
							iMir = 1;
							RealShips[int(sld.Ship.Type)].ship.upgrades.hull = 1;//чистый корпус
							SetShipSailsFromFile(sld, "ships/parus_silk.tga");
							SetSailsColor(sld, 0);//белый хлопковый парус
							DeleteAttribute(sld, "ship.sails");//починить паруса
							DeleteAttribute(sld, "ship.masts");//вернуть мачты
							}
							if(int(RealShips[int(sld.ship.type)].basetype) == SHIP_VALCIRIA) iVal = 1;
						}
					}//установили признак наличия кораблей в эскадре.
					if (iMir == 1 && iVal == 0)//потеряли Валькирию
					{
						dialog.text = "Vous êtes de retour, capitaine... Je sais déjà tout de votre voyage.";
						link.l1 = "Vraiment ? Alors tu dois savoir que...";
						link.l1.go = "Fleetwood_lostVal";
						DelLandQuestMark(npchar);
						DelMapQuestMarkCity("SentJons");
						break;
					}
					if (iMir == 0 && iVal == 1)//потеряли Мираж
					{
						dialog.text = "Vous êtes de retour, capitaine... Je sais déjà tout de votre voyage.";
						link.l1 = "Vraiment ? Alors vous devez savoir que...";
						link.l1.go = "Fleetwood_lostMir";
						DelLandQuestMark(npchar);
						DelMapQuestMarkCity("SentJons");
						break;
					}
					if (iMir == 0 && iVal == 0)//а это вообще плохо
					{
						dialog.text = "Vous êtes de retour, capitaine... Je sais déjà tout de votre voyage.";
						link.l1 = "Vraiment? Alors tu dois savoir que...";
						link.l1.go = "Fleetwood_lostFull";
						DelLandQuestMark(npchar);
						DelMapQuestMarkCity("SentJons");
						break;
					}
						dialog.text = "Vous êtes de retour, capitaine... Je sais déjà tout sur votre voyage.";
						link.l1 = "Vraiment ? Alors, tu dois savoir que...";
					link.l1.go = "Fleetwood_complete";
					DelLandQuestMark(npchar);
					DelMapQuestMarkCity("SentJons");
					break;
				}
				if (pchar.questTemp.HWIC.Eng == "toAntigua")
				{
					dialog.text = "Salutations, mon ami ! Heureux de te voir ! As-tu Abigail sur ton navire ?";
					link.l1 = "Malheureusement, je ne le peux pas, Richard. Elle a refusé de me suivre, car son départ serait un coup dur pour son père qui a déjà perdu chaque pièce. J'ai décidé de m'occuper du problème et de trouver l'argent de Salomon et cette île...";
					link.l1.go = "Fleetwood_LastTask";
					DelLandQuestMark(npchar);
					DelMapQuestMarkCity("SentJons");
					break;
				}
				dialog.text = "Autre chose, capitaine ?";
				link.l1 = "Non, je pars déjà.";
				link.l1.go = "exit";		
				NextDiag.TempNode = "First time";
			}
				dialog.text = "Autre chose, capitaine ?";
				link.l1 = "Non, je m'en vais déjà.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Fleetwood_abordage":
			PlaySound("Voice\English\hambit\Richard Flitwood-03.wav");
			dialog.text = "Maudit pirate ! Tu as gagné le combat à l'abordage, mais je remplirai mon devoir quand même. J'ai arrangé l'ignition de la chambre à poudre et mon navire explosera bientôt avec ton 'Navire Fantôme'. Tu ne couleras plus un seul navire anglais. Je mourrai avec honneur !";
			link.l1 = "Je suis désolé de te décevoir mais tu te trompes, Fleetwood. Il n'y a pas de pirates sur mon navire, je me suis déjà occupé d'eux. J'avais besoin de toi et ce navire a servi de joli piège.\nAssez de paroles aimables, je dois encore te tuer et m'enfuir de ta baignoire en flammes !";
			link.l1.go = "Fleetwood_abordage_1";
		break;
		
		case "Fleetwood_abordage_1":
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);			
			QuestAboardCabinDialogExitWithBattle("PrepareToBoom"); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.questTemp.HWIC.Holl = "FleetwoodCapture";
			pchar.GenQuest.Detonation = true; // patch-4
		break;
		
		case "First_Task":
			dialog.text = "Charlie m'a déjà informé de votre interception réussie de la caravane commerciale ennemie. Je suis heureux de vous rencontrer, l'Angleterre a besoin de capitaines aussi courageux. Maintenant, permettez-moi de vous dire quelque chose d'une grande importance.";
			link.l1 = "Je vous écoute, Monsieur Fleetwood.";
			link.l1.go = "First_Task_1";			
		break;
		
		case "First_Task_1":
			dialog.text = "Un pirate a commis des actes de violence à travers l'archipel, se faisant passer pour le 'Hollandais volant', un navire fantôme légendaire. Il prétend être le 'Hollandais volant', un navire fantôme légendaire. Je suis sûr qu'il est Néerlandais, mais il ne peut pas voler. Je tends à croire qu'il s'agit d'un mercenaire de Lucas Rodenburg, vice-directeur de la Compagnie néerlandaise des Indes occidentales.\nRodenburg a déclaré une guerre commerciale dans l'ombre contre l'Angleterre - ce 'vaisseau fantôme' attaque uniquement les navires marchands sous pavillon anglais. Il est vital pour la compagnie d'affaiblir notre influence dans cette région sans mener une véritable guerre.\nJe poursuis ce vaisseau fantôme depuis un moment, mais son capitaine est un marin très expérimenté et son navire est rapide et insaisissable.\nPuisqu'il est impossible d'attraper le chacal en combat ouvert, nous devrions agir avec ruse et la récente tentative d'attentat contre ma vie nous rendra un grand service. Qu'en pensez-vous, capitaine ? Avez-vous peur ?";
			link.l1 = "Pas question. Je serais ravi de vous aider à traquer et couler ce salaud. Vous alliez me demander de faire cela, n'est-ce pas ?";
			link.l1.go = "First_Task_2";	
		break;
		
		case "First_Task_2":
			dialog.text = "Tu as raison. Maintenant, discutons des détails. Mes hommes vont répandre la rumeur que je suis presque mort et que j'ai vendu mon navire, le 'Valkyrie', à toi. Ensuite, nous continuerons notre petite tromperie. Tu feras semblant d'être un marchand qui a acheté la brigantine de moi et s'est débarrassé de la plupart des canons.\nPar conséquent, ta tâche est de naviguer vers la Barbade et de dire à tout le monde là-bas que tes cales sont remplies de cargaison précieuse et que tes poches sont pleines de pièces. Fais-leur savoir que tu vas bientôt appareiller. Joue le rôle d'un marchand avide, simple mais riche.\nNotre maudit Hollandais obtient ses informations sur les navires marchands par Bridgetown. On ne sait pas exactement qui lui fournit ces informations. Tout le monde est suspect - d'un marchand local à un gouverneur, bien que cette dernière possibilité soit assez terrifiante.\nPrends le commandement de mon 'Valkyrie' et de son équipage. Mais d'abord, tu devrais laisser tous tes navires ici, j'ai déjà parlé au maître du port local, cela coûtera 10 000 pesos par mois pour ton navire amiral.\nUne fois que c'est fait, reviens vers moi et je ferai les arrangements nécessaires. Ah, capitaine, n'oublie pas de prendre ta part pour avoir capturé la caravane d'argent et les dix mille pour le maître du port, l'argent est dans la commode.";
			link.l1 = "J'ai compris, Monsieur Fleetwood. Je vais voir le maître de port.";
			link.l1.go = "exit";	
			pchar.questTemp.HWIC.Eng = "GotoPortoffice";
			bDisableFastReload = false;//откроем быстрый переход
			DeleteAttribute(pchar, "questTemp.HWIC.CanTake");//иные варианты более невозможны
			AddLandQuestMark(characterFromId("SentJons_PortMan"), "questmarkmain");
		break;
		
		case "First_Task_3":
			DialogExit();
			pchar.questTemp.HWIC.TakeQuestShip = "true";//все ПУ недоступны для стоянки до поры, также корабль нельзя продать
			pchar.questTemp.HWIC.EngEquip = "true"; //форма солдат
			pchar.questTemp.HWIC.Eng = "GotoBridgetown";
			GetValckiriaToCharacter(pchar);
			pchar.quest.Knippel_Officer.win_condition.l1 = "location";
			pchar.quest.Knippel_Officer.win_condition.l1.location = "SentJons_houseSP3";
			pchar.quest.Knippel_Officer.function = "KnippelToOfficer";
			pchar.questTemp.HWIC.Eng.BridgeCounter = 0;//счетчик посещений неписей Бриджтауна по квесту
			AddQuestRecord("Holl_Gambit", "2-5");
			AddMapQuestMarkCity("Bridgetown", false);
			AddLandQuestMark(characterFromId("Bridgetown_trader"), "questmarkmain");
			AddLandQuestMark(characterFromId("Bridgetown_shipyarder"), "questmarkmain");
			AddLandQuestMark(characterFromId("Bridgetown_Mayor"), "questmarkmain");
			AddLandQuestMark(characterFromId("Bridgetown_tavernkeeper"), "questmarkmain");
			AddLandQuestMark(characterFromId("Bridgetown_usurer"), "questmarkmain");
			AddLandQuestMark(characterFromId("Bridgetown_PortMan"), "questmarkmain");
			AddLandQuestMark(characterFromId("Bridgetown_Hostess"), "questmarkmain");
		break;
		
		//изымаем корабль
		case "Fleetwood_lostMir":
			dialog.text = "Oui, je suis au courant que vous avez échoué dans votre mission de capturer le navire pirate. Tous mes plans sont ruinés. Je vous retire la 'Valkyrie'. Vous pouvez partir maintenant, je n'ai plus besoin de vos services.";
			link.l1 = "Je suis tellement désolé pour cela. Adieu, Monsieur Fleetwood.";
			link.l1.go = "Fleetwood_RemoveShip";
			pchar.questTemp.HWIC.Eng.ShipType = SHIP_VALCIRIA;
		break;
		
		case "Fleetwood_lostVal":
			dialog.text = "Oui, je suis au courant que tu as perdu 'Valkyrie'. C'était des plus inacceptables... Je vais prendre possession du vaisseau pirate capturé. Tu peux partir maintenant, je n'ai plus besoin de tes services.";
			link.l1 = "Je suis vraiment désolé pour cela. Adieu, Monsieur Fleetwood.";
			link.l1.go = "Fleetwood_RemoveShip";
			pchar.questTemp.HWIC.Eng.ShipType = SHIP_MIRAGE;
		break;
		
		case "Fleetwood_lostFull":
			dialog.text = "Oui, je sais que tu es un rare embrouilleur et gaffeur. Tu n'as pas capturé le navire pirate et tu as perdu ma 'Walkyrie'. Je suis vraiment déçu de toi. Sors d'ici !";
			link.l1 = "Je suis vraiment désolé pour cela. Adieu, Monsieur Fleetwood.";
			link.l1.go = "exit";
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex("Knippel");
			AddDialogExitQuestFunction("LandEnc_OfficerFired");//Книппеля из офицеров
			sld = characterFromId("Knippel");
			ChangeCharacterAddressGroup(sld, "SentJons_houseH1", "goto", "goto1");//Книппеля домой
			pchar.questTemp.HWIC.Eng = "end";
			CloseQuestHeader("Holl_Gambit");
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");//ПУ откроем
			DeleteAttribute(pchar, "questTemp.HWIC.EngEquip");
			pchar.questTemp.HWIC.Detector = "eng_fail";
			AddSimpleRumourCity("They say that you have failed some secret assignment of Richard Fleetwood. Well, you have got nothing to do on Antigua now...", "SentJons", 20, 3, "");
		break;
		
		case "Fleetwood_RemoveShip":
			DialogExit();
			AddDialogExitQuestFunction("Fleetwood_RemoveShip");
			pchar.questTemp.HWIC.Eng = "end";
			CloseQuestHeader("Holl_Gambit");
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");//ПУ откроем
			DeleteAttribute(pchar, "questTemp.HWIC.EngEquip");
			pchar.questTemp.HWIC.Detector = "eng_fail";
			AddSimpleRumourCity("They say that you have failed some secret assignment of Richard Fleetwood. Well, you have got nothing to do on Antigua now...", "SentJons", 20, 3, "");
		break;
		
		case "Fleetwood_complete":
			pchar.questTemp.HWIC.Eng.ShipType = SHIP_VALCIRIA;
			AddDialogExitQuestFunction("Fleetwood_RemoveShip");	
			if (CheckCharacterItem(pchar, "JacobJournal"))//проверяем журнал
			{
				dialog.text = "Oui, je suis au courant que tu as réussi notre plan. Tu as éliminé le vilain pirate et capturé son navire. Quel est son vrai nom ?";
				link.l1 = "Mirage";
				link.l1.go = "Abigile";
			}
			else//нет журнала - нет продолжения квеста
			{
				dialog.text = "Oui, je suis au courant que tu as réussi notre plan. Tu as éliminé le vil pirate et capturé son navire. Je reprendrais mon 'Valkyrie'. Tu peux garder le vaisseau pirate comme trophée. Cela servira également de... compensation. Ton navire ancré dans le port a brûlé lorsque l'incendie sur les quais a commencé à se propager. Je m'excuse pour le désagrément, "+pchar.name+"... J'espère que le vaisseau fantôme te servira mieux.\nJ'ai ordonné que ton nouveau navire soit nettoyé de la saleté tenace et des algues. Ils habilleront aussi ta beauté de nouvelles voiles en meilleur coton.\nEnfin, je te prie d'accepter ta récompense de 100 000 pesos et cet outil de navigation. J'ai toujours voulu l'offrir à un marin digne et tu as fait un travail admirable là-bas ! Eh bien, le moment est venu de dire adieu, j'ai terminé mes affaires ici et je devrais retourner en Europe. Bonne fortune à toi, capitaine !";
				link.l1 = "À toi aussi, Richard !";
				link.l1.go = "exit";
				LocatorReloadEnterDisable("SentJons_houseSP3", "reload2", true);//закроем Флитвуда в комнате и пусть там сидит
				pchar.questTemp.HWIC.Eng = "end";
				pchar.questTemp.HWIC.Detector = "eng_win_half";
				CloseQuestHeader("Holl_Gambit");
			}
			AddMoneyToCharacter(pchar, 100000);
			GiveItem2Character(pchar, "bussol");
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");//ПУ откроем
			DeleteAttribute(pchar, "questTemp.HWIC.EngEquip");
			AddSimpleRumourCity("They say that you and Richard Fleetwood has planned some military operation and you have personally destroyed that elusive pirate who has been robbing our trade ships. You are a real hero, captain!", "SentJons", 20, 3, "");
		break;
		
		case "Abigile":
			dialog.text = "Mirage ? Un nom fort approprié, je dirais... Je vais reprendre ma 'Valkyrie' et donc, vous pouvez garder le navire pirate comme prix. Cela servira également de compensation. Votre navire ancré dans le port a brûlé lorsque le feu sur les quais a commencé à se propager. Je suis désolé, "+pchar.name+"... J'espère que le vaisseau fantôme te servira mieux.\nJ'ai ordonné de nettoyer ton nouveau navire de cette saleté tenace et de ces algues. Ils habilleront aussi ta beauté de nouvelles voiles en coton de la meilleure qualité.\nEnfin, accepte ta récompense de 100 000 pesos et cet outil de navigation, j'ai toujours voulu le remettre à un marin digne... Tu as fait un bon travail là-bas et je suis fier de toi ! As-tu le journal de bord du bâtard ?";
			link.l1 = "Oui, bien sûr. Le voilà, prends-le. Je veux te demander quelque chose, y a-t-il un... Asiatique parmi les mercenaires de Lucas Rodenburg ?";
			link.l1.go = "Abigile_1";			
		break;
		
		case "Abigile_1":
			RemoveItems(PChar, "JacobJournal", 1);
			dialog.text = "Oui, il y en a un. Le Chinois Longway, capitaine de son navire privé 'Meifeng'. As-tu lu cela dans le journal de bord du pirate ? Voyons voir...(lisant) Eh bien, eh bien. Comme je m'y attendais, Lucas Rodenburg était derrière tout cela ! Bon, peu importe, cela ne nous concerne plus maintenant... Notre gouverneur général s'occupera de ce salaud. Lucas Rodenburg devra assumer la responsabilité de tout ce qu'il a fait !";
			link.l1 = "Hum, intéressant, et comment le gouverneur-général anglais pourra-t-il 'traiter' avec un sujet des Pays-Bas ?";
			link.l1.go = "Abigile_2";			
		break;
		
		case "Abigile_2":
			dialog.text = "Il y a toujours des ficelles politiques à tirer, mon cher ami... La Hollande devra admettre qu'elle a commencé la guerre commerciale contre l'Angleterre, mais il est peu probable qu'elle le fasse. Au lieu de cela, ils blâmeront Rodenburg pour tout. Lucas pourrait perdre sa position, ou peut-être pas. Quoi qu'il en soit, sa carrière subira un lourd coup.\nCependant, ce n'est pas notre affaire pour le moment, capitaine. Vous avez bien accompli votre part du travail. C'est pourquoi j'ai une autre affaire très délicate pour vous.";
			link.l1 = "Je t'écoute, Richard. Qui sera le prochain ennemi de la couronne anglaise à être détruit cette fois-ci ?";
			link.l1.go = "Abigile_3";			
		break;
		
		case "Abigile_3":
			dialog.text = "Non, cette fois je veux te demander de t'occuper d'une affaire plus personnelle et paisible. Permets-moi de te raconter une courte histoire qui, soit dit en passant, concerne ton 'Mirage'.";
			link.l1 = "Continue.";
			link.l1.go = "Abigile_4";			
		break;
		
		case "Abigile_4":
			dialog.text = "J'étais en raid, chassant le navire fantôme un mois avant que vous et moi ne nous rencontrions. C'était au sud de la Martinique, non loin de la longitude 64 dg. 41'. Nous avons entendu un combat au loin, mais le vent était trop faible, donc nous n'avons pas pu y arriver à temps. Une flûte anglaise a été coulée par un navire fantôme près d'une petite île qui n'est même pas sur la carte. \nJe n'ai pas réussi à attraper le pirate et j'ai décidé de visiter cette île, espérant trouver des survivants. Et je les ai trouvés. Un couple de réfugiés juifs, père et fille. La fille s'appelait Abigail et elle était magnifique ! Un miracle vivant... Je les ai pris à bord et les ai livrés à Curaçao, bien que son père, Solomon, ne m'ait pas montré beaucoup de sympathie. \nD'après ce que j'ai compris, il pensait que j'étais le pirate qui avait coulé leur navire, le vieil homme ne connaît pas grand-chose aux navires et aux différences entre eux. Pendant ce petit voyage, Abigail et moi sommes devenus amis, ou, pour être complètement honnête, nous sommes tombés amoureux l'un de l'autre. N'est-ce pas une histoire ? \nEt j'ai récemment découvert que ce salaud de Rodenburg courtisait mon Abigail depuis un moment, imaginez ça ! J'allais l'emmener ici, une fois que j'aurais résolu le problème concernant l'argent perdu de son père, il avait caché chaque pièce qu'il possédait sur cette île, que j'ai mentionnée. Je n'ai pas réussi à trouver son emplacement. Nous ne pouvons plus attendre. \nPuisque ma santé ne me permet toujours pas de prendre la mer moi-même, je vous demande d'aller à Willemstad, de trouver Abigail et de l'amener ici. Mentionnez mon nom et elle vous fera confiance.";
			link.l1 = "Je ne vois aucun problème dans cette affaire. Je suis prêt à mettre les voiles maintenant.";
			link.l1.go = "Abigile_5";			
		break;
		
		case "Abigile_5":
			PlaySound("Voice\English\hambit\Richard Flitwood-02.wav");
			dialog.text = "Excellent! Je suis ravi de pouvoir compter sur vous, "+pchar.name+"Votre travail sera bien rémunéré, ne vous inquiétez pas pour cela.";
			link.l1 = "Je ne te ferai pas attendre trop longtemps. À bientôt, Richard !";
			link.l1.go = "Abigile_6";			
		break;
		
		case "Abigile_6":
			DialogExit();
			npchar.greeting = "fleetwood_2";
			LocatorReloadEnterDisable("Villemstad_town", "houseSP2", false);//откроем дом Аби
			LocatorReloadEnterDisable("Villemstad_houseSp2", "reload2", true);//закроем спальню Аби
			AddQuestRecord("Holl_Gambit", "2-16");
			pchar.questTemp.HWIC.Eng = "toAbigile";
			sld = characterFromId("Bridgetown_tavernkeeper");
			sld.model = "barmen_3";
			sld.name = "Harry";
			sld.lastname = "Fletcher";//перерисуем бармена Бриджтауна
			sld.greeting = "barmen_1";
			sld = characterFromId("Solomon");
			sld.greeting = "solomon_2";
			AddLandQuestMark(sld, "questmarkmain");
			AddMapQuestMarkCity("Villemstad", false);
		break;
		
		case "Fleetwood_LastTask":
			dialog.text = "Bonjour, mon ami."+pchar.name+", avez-vous vraiment décidé de trouver l'île ? Je suis impressionné par votre générosité. L'avez-vous trouvée ?";
			link.l1 = "Oui, je l'ai fait. Malheureusement, c'est là que commencent les mauvaises nouvelles. Je me suis échappé de cet endroit maudit de justesse... Je tremble encore rien qu'à y penser...";
			link.l1.go = "Fleetwood_LastTask_1";
		break;
		
		case "Fleetwood_LastTask_1":
			dialog.text = "Qu'est-il arrivé là-bas ? Dis-moi, mon ami, ne me laisse pas en haleine !";
			link.l1 = "Je suis arrivé sur l'île et me suis dirigé vers la grotte où Salomon avait probablement caché son coffre. Il était vraiment là. Mais quand je l'ai touché, une puissance inconnue m'a projeté en l'air. J'ai entendu une explosion et j'ai été jeté à terre à trois mètres du coffre...";
			link.l1.go = "Fleetwood_LastTask_2";
		break;
		
		case "Fleetwood_LastTask_2":
			dialog.text = "Incroyable !";
			link.l1 = "Je l'ai à peine survécu - j'ai quelques éraflures douloureuses. Quand je reprenais conscience, des bruits effrayants bourdonnaient dans ma tête et cette horrible créature est apparue directement du sol... oh, Dieu, ce monstre !";
			link.l1.go = "Fleetwood_LastTask_3";
		break;
		
		case "Fleetwood_LastTask_3":
			dialog.text = ""+pchar.name+"...  ";
			link.l1 = "Richard, je ne suis pas fou. Cela s'est vraiment passé, bien que j'aie du mal à y croire moi-même. C'était un cadavre complètement desséché et peint d'un Indien avec un tas de plumes sur la tête. Ce monstre a marmonné quelque chose, puis a sorti une énorme massue indienne et m'a attaqué !";
			link.l1.go = "Fleetwood_LastTask_4";
		break;
		
		case "Fleetwood_LastTask_4":
			dialog.text = "Bonjour, mon ami.";
			link.l1 = "Bon Dieu... Je ne comprends toujours pas comment j'ai pu venir à bout de cette chose... Je l'ai frappée tant de fois qu'il aurait suffi pour tuer une douzaine d'hommes et elle tenait toujours debout... Après avoir repris mon souffle, j'ai ouvert ce maudit coffre... Il n'y avait pas d'argent dedans, mais il y avait autre chose à la place. Regarde, un objet très intrigant !";
			link.l1.go = "Fleetwood_LastTask_5";
		break;
		
		case "Fleetwood_LastTask_5":
			RemoveItems(PChar, "GastonHead", 1);
			dialog.text = "B-r-r... terrible..."+pchar.name+", attends... c'est bien lui ! C'est la tête du salaud qui a essayé de me tuer en me rendant aveugle avec du poivre !";
			link.l1 = "Tu le connais? Il s'appelle Gaston, le barman de Bridgetown et un partisan de van Berg, le capitaine du navire fantôme. Je l'ai reconnu immédiatement mais je ne sais pas qui l'a tué ni comment sa tête coupée s'est retrouvée dans le coffre de Salomon sur l'île inconnue!";
			link.l1.go = "Fleetwood_LastTask_6";
		break;
		
		case "Fleetwood_LastTask_6":
			dialog.text = "Tu as raison, c'est une histoire vraiment lugubre et obscure. Mystique...";
			link.l1 = "Exactement. Il n'y avait aucun intérêt à retourner auprès d'Abigail en raison de l'absence d'argent. Je suis donc ici pour vous en parler. Peut-être que vous, Richard, comprendrez quelque chose dans ce gâchis...";
			link.l1.go = "Fleetwood_LastTask_7";
		break;
		
		case "Fleetwood_LastTask_7":
			dialog.text = "Moi? Je n'y comprends rien ici tout comme toi... Mais je peux te dire une chose avec certitude - j'ai un mauvais pressentiment à ce sujet..."+pchar.name+", écoute-moi maintenant. Va et vérifie Bridgetown pour être sûr que... Gaston est parti pour de bon. Ensuite, je te demande de venir à la Lagune Blanca de Curaçao dans 20 jours. Charlie Knippel t'y attendra. Je vais collecter de l'argent pour le père d'Abigail. Je le donnerai à Charlie, et tu le porteras à Solomon et livreras Abigail à Antigua. Cette fois, il n'y aura pas d'obstacles, tu dois comprendre cela. Va, mon ami !";
			link.l1 = "Très bien, Richard. Je vais mettre les voiles immédiatement.";
			link.l1.go = "Fleetwood_LastTask_8";
		break;
		
		case "Fleetwood_LastTask_8":
			DialogExit();
			pchar.questTemp.HWIC.Eng = "toBarbados";
			AddQuestRecord("Holl_Gambit", "2-21");
			SetFunctionTimerCondition("HWICEng_toBarbadosOver", 0, 0, 20, false);//чтобы не тянули
			AddSimpleRumourCity("Oh, captain, I have heard that Richard Fleetwood really admires you. Trust me, his praise costs a lot. You must be a very important person...", "SentJons", 20, 3, "");
			AddMapQuestMarkCity("Bridgetown", false);
			AddLandQuestMark(characterFromId("Bridgetown_tavernkeeper"), "questmarkmain");
		break;
		
//---------------------------------------------против всех-----------------------------------------------
		
		case "InTerksShore":
			DelLandQuestMark(npchar);
			pchar.quest.Fleetwood_ShoreOver.over = "yes";//снять таймер
			dialog.text = "Je suppose que tu es le bâtard qui a enlevé mon Abigail. Charlie n'est pas revenu vers moi, donc c'est toi qu'il faut également blâmer.";
			link.l1 = "Vous avez raison, Monsieur Fleetwood. C'est moi. Charlie m'a aidé à gagner la confiance d'Abigail grâce à la lettre que vous lui avez écrite. Mais allons droit au but... Avez-vous apporté l'argent ?";
			link.l1.go = "InTerksShore_1";
		break;
		
		case "InTerksShore_1":
			dialog.text = "Je l'ai. Mais je veux voir Abigail d'abord. Je dois être sûr qu'elle est en vie et intacte, car je ne vais pas faire confiance à la parole d'un salaud.";
			link.l1 = "Ne pensez-vous pas, monsieur, que vous n'êtes pas en position de dicter vos conditions ?";
			link.l1.go = "InTerksShore_2";
			// belamour legendary edition -->
			link.l2 = "Je ne veux plus jouer à ce jeu. Abi restera avec moi, et toi tu restes sur cette plage ! Feu !";
			link.l2.go = "InTerksShore_2a";
		break;

		case "InTerksShore_2a"://массовая драка на необитаемом острове
			AddCharacterExpToSkill(pchar, "FencingL", 60);
			AddCharacterExpToSkill(pchar, "FencingS", 60);
			AddCharacterExpToSkill(pchar, "FencingH", 60);
			AddCharacterExpToSkill(pchar, "Pistol", 60);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешим драться
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			for (i=1; i<=3; i++)//офицеры Флитвуда
			{
				sld = characterFromId("FlOfficer_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			for (i=1; i<=7; i++)//засада Флитвуда
			{
				sld = GetCharacter(NPC_GenerateCharacter("EnemySailor_"+i, "sold_eng_"+i, "man", "man", 18, ENGLAND, -1, false, "soldier"));
				FantomMakeCoolFighter(sld, 18, 30, 30, "blade_19", "pistol2", "bullet", 40);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				if (i >= 1 && i < 3) ChangeCharacterAddressGroup(sld, "Shore56", "goto", "goto2");
				else ChangeCharacterAddressGroup(sld, "Shore56", "goto", "goto9");
			}
			for (i=1; i<=7; i++)//наши - к бою!
			{
				sld = characterFromId("OwrSailor_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "FleetwoodDiedInShore");
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;

		case "InTerksShore_2":
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			AddCharacterExpToSkill(pchar, "Leadership", 120);
			// <-- legendary edition
			dialog.text = "Je comprends cela, mais je ne suis pas non plus un imbécile. Pas de discussion d'argent avant que je ne voie Abigail. Alors quoi ? J'attends.";
			link.l1 = "Bien. Il est temps de mettre cartes sur table, Capitaine Fleetwood. J'ai organisé notre rencontre ici non pas pour l'argent. Eh bien, certes, je voudrais le prendre, mais j'ai besoin de vous d'abord.";
			link.l1.go = "InTerksShore_3";
		break;
		
		case "InTerksShore_3":
			dialog.text = "Moi? Cela devient des plus intéressant... Je pense que je commence à comprendre ce qui se passe vraiment ici. Dis-moi, Abigail est-elle en vie? Elle vit ou l'as-tu assassinée, salaud?";
			link.l1 = "Je suppose que je vais te laisser dans l'ignorance quant à son sort. Une seule chose à savoir - elle n'est pas ici. Elle a bien joué son rôle, tu es ici entre mes mains. L'amour est une chose si merveilleuse... Comment pourrais-je autrement attirer un renard hors de son terrier vers les terrains découverts ? Ha-ha-ha !";
			link.l1.go = "InTerksShore_4";
		break;
		
		case "InTerksShore_4":
			dialog.text = "Ne te réjouis pas trop tôt, vaurien. J'ai organisé un accueil des plus chaleureux pour toi sur cette île et on ne sait pas qui est dans les mains de qui ! Alors prépare-toi, tu as beaucoup de choses à me dire - à propos d'Abigail, de Charlie, tu paieras pour les avoir blessés !";
			link.l1 = "Je tremble déjà de peur ! Il est temps de mettre fin à notre conversation, Monsieur. Préparez-vous à aller en enfer, car il n'y a pas de place pour vous au paradis.";
			link.l1.go = "InTerksShore_5";
		break;
		
		case "InTerksShore_5"://массовая драка на необитаемом острове
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешим драться
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			for (i=1; i<=3; i++)//офицеры Флитвуда
			{
				sld = characterFromId("FlOfficer_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			for (i=1; i<=7; i++)//засада Флитвуда
			{
				sld = GetCharacter(NPC_GenerateCharacter("EnemySailor_"+i, "sold_eng_"+i, "man", "man", 18, ENGLAND, -1, false, "soldier"));
				FantomMakeCoolFighter(sld, 18, 30, 30, "blade_19", "pistol2", "bullet", 40);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				if (i >= 1 && i < 3) ChangeCharacterAddressGroup(sld, "Shore56", "goto", "goto2");
				else ChangeCharacterAddressGroup(sld, "Shore56", "goto", "goto9");
			}
			for (i=1; i<=7; i++)//наши - к бою!
			{
				sld = characterFromId("OwrSailor_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "FleetwoodDiedInShore");
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
	}
}
