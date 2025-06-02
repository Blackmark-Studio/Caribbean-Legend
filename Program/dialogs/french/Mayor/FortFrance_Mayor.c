// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Que voulez-vous ? Demandez ce que vous voulez.","Je vous écoute, quelle est la question ?"),"C'est la deuxième fois que vous essayez de demander...","C'est la troisième fois que vous essayez encore de demander...","Quand cela va-t-il finir ?! Je suis un homme occupé, travaillant sur les affaires de la colonie et tu continues à essayer de demander quelque chose !","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("J'ai changé d'avis...","Pas maintenant. Mauvais endroit et moment."),"Vrai... Mais plus tard, pas maintenant...","Je demanderai... Mais un peu plus tard...","Je suis désolé, "+GetAddress_FormToNPC(NPChar)+"...",npchar,Dialog.CurrentNode);			  
			link.l1.go = "exit";
			/* //--> Бремя гасконца
			if (CheckAttribute(pchar, "questTemp.Sharlie.Junglejew"))
			{
				link.l1 = "Monsieur, j'ai trouvé un cadavre de bandit dans la jungle. Il a été tué par les Indiens. Il y avait des boucles d'oreilles sur son corps, on dirait qu'elles ont été apportées d'Europe. Peut-être appartenaient-elles à l'un des nobles de votre ville ?";
                link.l1.go = "Sharlie_junglejew";
			}
			//<-- Бремя гасконца */
			//--> Sinistra, Травля крысы
			if (CheckAttribute(pchar, "questTemp.TK_Potopil"))
			{
				link.l1 = "Votre Excellence, la tâche est accomplie ! Cependant, je regrette de vous informer que le criminel n'a pas survécu à l'affrontement, et par conséquent ne sera pas exécuté.";
                link.l1.go = "TK_Potopil";
			}
			if (CheckAttribute(pchar, "questTemp.TK_Plen"))
			{
				link.l1 = "Votre Excellence, la tâche est accomplie ! Le prisonnier attend son sort dans ma cage.";
                link.l1.go = "TK_Plen";
			}
			//<-- Травля крысы
			// Jason НСО
			if (CheckAttribute(pchar, "questTemp.Patria") && pchar.questTemp.Patria == "epizode_9_continue" && !CheckAttribute(npchar, "quest.frigate"))
			{
				link.l1 = "Je suis arrivé sur ordre du Gouverneur Général Philippe de Poincy pour prendre le commandement de votre frégate armée.";
                link.l1.go = "patria";
			}
			if (CheckAttribute(npchar, "quest.frigate.wait") && GetCompanionQuantity(pchar) < 5)
			{
				link.l1 = "Je suis prêt à intégrer la frégate dans mon escadron.";
                link.l1.go = "patria_2";
			}
			// Jason Дороже золота
			if (CheckAttribute(pchar, "questTemp.GoldenGirl") && pchar.questTemp.GoldenGirl == "message")
			{
				link.l1 = "Je suis arrivé à votre invitation, Monsieur...";
                link.l1.go = "goldengirl";
			}
			if (CheckAttribute(pchar, "questTemp.GoldenGirl") && pchar.questTemp.GoldenGirl == "girl_prisoner")
			{
				link.l1 = "Il y avait un malheureux, Monsieur";
                link.l1.go = "goldengirl_10";
			}
			// andre39966 ===> В плену великого улова.
			if (CheckAttribute(pchar, "questTemp.VPVL_Magor_Dialogue"))
			{
				link.l1 = "Excellence, je suis entré(e) en possession de renseignements concernant un commerce illicite qui doit bientôt se dérouler sur ces rivages. J'ose dire que cette affaire pourrait se révéler digne de votre attention.";
				link.l1.go = "VPVL_Magor_1";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.VPVL_GovernorDialogueAvailable"))
			{
				link.l1 = "Excellence, je viens quérir des nouvelles de ce navire de contrebande dont nous avons discuté.";
				link.l1.go = "VPVL_Magor_4";
			}
			//  <=== В плену великого улова.   
		break;
		
		case "Sharlie_junglejew":
			dialog.text = "Voyons voir ce que vous avez... Incroyable ! C'est tout simplement incroyable, Charles ! Ce sont les boucles d'oreilles de ma femme. Je les lui avais offertes avant de quitter l'Europe pour venir aux colonies. Elles ont disparu il y a quelques mois dans des circonstances mystérieuses. Je savais qu'elles avaient été volées !\nCharles, je suis très heureux que vous soyez venu directement à moi, et que vous n'ayez pas vendu la chose que je tiens tant à cœur aux marchands. Je vous rembourserai pour votre service. Comme j'ai entendu dire que vous allez acheter un navire ? Puisque vous avez décidé de vous lancer dans la navigation, vous aurez sans aucun doute besoin d'une carte de notre archipel. Tenez, prenez-la. Je suis sûr qu'elle vous sera utile !";
			link.l1 = "Merci, votre Grâce !";
			link.l1.go = "Sharlie_junglejew_1";
		break;
		
		case "Sharlie_junglejew_1":
			DialogExit();
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "jewelry25", 1);
			GiveItem2Character(pchar, "map_normal");
			AddQuestRecord("SharlieE", "2");
			CloseQuestHeader("SharlieE");
			DeleteAttribute(pchar, "questTemp.Sharlie.Junglejew");
			if(!CheckAttribute(pchar, "questTemp.Sharlie.Pardon"))
			{
				DelLandQuestMark(npchar);
			}
		break;
		
		//--> Sinistra, Травля крысы
		case "TK_Potopil":
			dialog.text = "C'est bien regrettable, Charles, mais nous devons faire avec la situation présente. Voici ta récompense : cinq mille pesos, après impôts.";
			link.l1 = "Je suis ravi de servir Saint-Pierre et vous personnellement. Bien que la bataille ait été difficile, j'y ai trouvé un certain plaisir.";
			link.l1.go = "TK_Potopil_3";
			link.l2 = "Ce fut une bataille difficile, votre Excellence. Mon navire a subi des dommages importants. Serait-il possible de me dédommager pour mes pertes?";
			link.l2.go = "TK_Potopil_4";
			DeleteAttribute(pchar, "questTemp.TK_Potopil");
			AddCharacterExpToSkill(pchar, "Accuracy", 20);
			AddCharacterExpToSkill(pchar, "Cannons", 20);
			AddCharacterExpToSkill(pchar, "Grappling", 20);
			AddCharacterExpToSkill(pchar, "Defence", 20);
			
			CloseQuestHeader("TravlyaKrys");
		break;
		
		case "TK_Potopil_3":
			dialog.text = "Bravo, Charles ! Je ne doute pas que vous monterez haut dans nos rangs.";
			link.l1 = "Jusqu'à notre prochaine rencontre, votre Excellence.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 5000);
			ChangeCharacterNationReputation(pchar, FRANCE, 5);
		break;
		
		case "TK_Potopil_4":
			dialog.text = "Je dois dire que je suis un peu surpris par votre demande, Charles... Très bien, considérez deux mille pesos de plus de ma part personnellement comme un geste de bonne volonté. Adieu.";
			link.l1 = "Merci, votre Excellence.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 7000);
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			ChangeCharacterNationReputation(pchar, FRANCE, 2);
		break;
		
		case "TK_Plen":
			dialog.text = "Excellent, Charles ! Vous serez ravi d'apprendre que votre succès aidera vos amis Maltais dans une opération délicate... Voici votre récompense : huit mille pesos, après impôts.";
			link.l1 = "Je suis ravi de servir St. Pierre, l'Ordre, et vous personnellement. Bien que le combat ait été difficile, j'y ai trouvé quelque satisfaction.";
			link.l1.go = "TK_Plen_3";
			link.l2 = "Ce fut une bataille ardue, Votre Excellence. Mon navire a subi des dommages considérables. Puis-je demander une compensation pour mes pertes ?";
			link.l2.go = "TK_Plen_4";
			AddCharacterExpToSkill(pchar, "Accuracy", 20);
			AddCharacterExpToSkill(pchar, "Cannons", 20);
			AddCharacterExpToSkill(pchar, "Grappling", 20);
			AddCharacterExpToSkill(pchar, "Defence", 20);
			CloseQuestHeader("TravlyaKrys");
			DeleteAttribute(pchar, "questTemp.TK_Plen");
			sld = CharacterFromID("TK_Heiter2");
			RemovePassenger(pchar, sld);
			sld.lifeday = 0;
		break;
		
		case "TK_Plen_3":
			dialog.text = "Bravo, Charles! Je suis sûr que tu iras loin.";
			link.l1 = "Jusqu'à notre prochaine rencontre, votre Excellence";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 8000);
			ChangeCharacterNationReputation(pchar, FRANCE, 5);
		break;
		
		case "TK_Plen_4":
			dialog.text = "Je suppose que vous l'avez mérité. Gardez deux mille de plus de ma part personnellement en guise de geste de bonne volonté. Merci, mon ami.";
			link.l1 = "Merci, votre Excellence.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 10000);
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			ChangeCharacterNationReputation(pchar, FRANCE, 2);
		break;
		//<-- Травля крысы
		
		// Jason НСО
		case "patria":
			if (GetCompanionQuantity(pchar) > 4)
			{
				dialog.text = "Le navire est prêt, mais vous n'avez pas de place libre pour lui dans votre escadre. Capitaine, réduisez votre escadre et revenez, puis je vous donnerai immédiatement la frégate.";
				link.l1 = "Très bien.";
				link.l1.go = "patria_1";
			}
			else
			{
				dialog.text = "Oui, bien sûr, le navire est prêt à prendre la mer. Son capitaine est au courant et suivra toutes vos ordres.";
				link.l1 = "Alors nous partons. Adieu, Votre Grâce.";
				link.l1.go = "patria_3";
			}
		break;
		
		case "patria_1":
			DialogExit();
			npchar.quest.frigate.wait = "true";
		break;
		
		case "patria_2":
			DeleteAttribute(npchar, "quest.frigate.wait");
			dialog.text = "Excellent. Prépare-toi à accueillir ton nouveau navire. Son capitaine est au courant et suivra tous tes ordres.";
			link.l1 = "Alors nous partons. Adieu, Votre Grâce.";
			link.l1.go = "patria_3";
		break;
		
		case "patria_3":
			DialogExit();
			npchar.quest.frigate = "true";
			Patria_BastionFrigateMrt(); // присоединяем фрегат
		break;
		
		// Jason Дороже золота
		case "goldengirl":
			dialog.text = "Capitaine Charles de Maure, enfin ! Je vous attendais avec impatience ! S'il vous plaît, entrez, rejoignez-moi.";
			link.l1 = "Bonne journée à vous aussi, Votre Excellence. Il y a toujours une raison derrière une telle politesse de votre part. Quelle est-elle cette fois-ci ? Pirates, Espagnols, cannibales peaux-rouges ?";
			link.l1.go = "goldengirl_1";
		break;
		
		case "goldengirl_1":
			dialog.text = "Ne sois pas sarcastique, Capitaine. Ce n'est pas ma faute si nous nous retrouvons toujours dans le pétrin, toi et moi. Mais s'il te plaît, ne t'inquiète pas, il n'y aura pas de fusillade cette fois... probablement.";
			link.l1 = "Tu m'intrigues, continue. Comment puis-je t'aider ?";
			link.l1.go = "goldengirl_2";
		break;
		
		case "goldengirl_2":
			dialog.text = "Tu as déjà entendu parler du fin établissement de Madame Botot ? Pendant le siège, notre... bordel a été réduit en cendres. Un jour, une certaine dame s'est proposée pour le reconstruire.";
			link.l1 = "Un feu dans un bordel et sans moi ? Au fait, ce jour-là, les Espagnols m'ont tiré dessus aussi.";
			link.l1.go = "goldengirl_3";
		break;
		
		case "goldengirl_3":
			dialog.text = "Satané, Charles, qu'est-ce qui ne va pas chez toi aujourd'hui ? Ton esprit est inapproprié ! Même si ce n'est pas une affaire d'État, c'est quand même une affaire importante, pour moi, personnellement ! J'ai besoin de ton aide ! Pour l'amour de Dieu, ressaisis-toi et écoute-moi !";
			link.l1 = "Veuillez me pardonner, Votre Excellence. Je ressens un immense soulagement, c'est tout. Pour être honnête, je suis fatigué de toutes ces batailles et combats constants. Je m'attendais à ce que vous commenciez à m'entraîner dans un autre cercle de violence. Je vous en prie, continuez. Jamais entendu parler de cette Madame Botot.";
			link.l1.go = "goldengirl_4";
		break;
		
		case "goldengirl_4":
			dialog.text = "Oui, cette honorable dame a élevé l'établissement à un tout nouveau niveau. C'est désormais un lieu de haute et noble société, et non plus un trou à rats, comme il l'était auparavant. Un lieu de vices distingués, de vins coûteux et de jeux d'argent sans limites. Vous verrez tout par vous-même !";
			link.l1 = "Votre Excellence, je ne suis pas un prude et votre description était très colorée, mais pourquoi me dites-vous cela ?";
			link.l1.go = "goldengirl_5";
		break;
		
		case "goldengirl_5":
			dialog.text = "Parce que tu es sur la liste, pour quelle autre raison?! Tu vois, je me sens coupable envers la Marquise et j'ai promis de te présenter à elle lors d'une de ses soirées demain. Juliana ne fait pas cela souvent alors sois assez aimable pour te joindre à nous. Pas de bagarres, de tirs ou de poursuites cette fois, je te le promets. Tout sera courtois et digne : vin, belles femmes, cartes et autres plaisirs nobles.";
			link.l1 = "Cartes et putains. Cela fait longtemps, dans une autre vie. Je ne te suis toujours pas cependant. Pourquoi moi ?";
			link.l1.go = "goldengirl_6";
		break;
		
		case "goldengirl_6":
			dialog.text = "Es-tu sourd ? Juliana Botot, elle... collectionne les visages brillants et célèbres. Ils rendent ses fêtes spéciales et rafraîchissantes. Vous vous êtes fait un nom, la Marquise a longtemps attendu pour vous avoir comme invité. Mon faux pas lui a donné une opportunité et je ne la prendrai pas si elle refuse de me recevoir à nouveau. C'est tout ce que j'obtiendrai si je ne vous livre pas à elle !";
			link.l1 = "Votre Excellence, vous êtes un veuf charmant et un gouverneur... Pourquoi vous souciez-vous de l'avis d'une courtisane? C'est à elles de chercher votre bienveillance, pas l'inverse.";
			link.l1.go = "goldengirl_7";
		break;
		
		case "goldengirl_7":
			dialog.text = "La marquise Botot est sous la protection du comte Henry de Levi-Vantadur - qui, par la grâce de Sa Majesté, est le chef des états de la Nouvelle-France en Amérique du Nord. Crois-moi, Charles, personne ici ne veut le contrarier.";
			link.l1 = "Tu m'as presque eu ici - je pensais que c'était seulement une question de luxure et d'amour. Maintenant je vois que c'était de la politique depuis le début. Insignifiant, mais prévisible. Très bien, je vais t'aider. Ce sera doux de revenir aux jours de ma jeunesse, ne serait-ce que pour une nuit.";
			link.l1.go = "goldengirl_8";
		break;
		
		case "goldengirl_8":
			dialog.text = "Capitaine, vous êtes sans doute un homme aguerri, cependant ne prétendez pas être un vieillard. Il ne s'agit pas seulement de politique. J'apprécie la présence de Juliana et je suis reconnaissant pour votre aide. C'est important pour moi personnellement, vraiment. Venez chez la marquise Botot après le crépuscule, demain. Je vous promets que la politique ne gâchera pas la soirée.";
			link.l1 = "Vin, cartes, femmes. Comme au bon vieux temps. Adieu, Votre Excellence !";
			link.l1.go = "goldengirl_9";
		break;
		
		case "goldengirl_9":
			DialogExit();
			bDisableFastReload = true;//закрыть переход
			pchar.quest.GoldenGirl_bronca.win_condition.l1 = "location";
			pchar.quest.GoldenGirl_bronca.win_condition.l1.location = "FortFrance_town";
			pchar.quest.GoldenGirl_bronca.function = "GoldenGirl_GirlAngry";
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			SetFunctionTimerCondition("GoldenGirl_TimeOver", 0, 0, 2, false); // таймер до завтрашней полуночи
			SetFunctionTimerCondition("GoldenGirl_BrothelDoor", 0, 0, 1, false); // таймер на закрытие дверей борделя
			pchar.quest.GoldenGirl_eventstart.win_condition.l1 = "Timer";
			pchar.quest.GoldenGirl_eventstart.win_condition.l1.date.hour  = 21.00;
			pchar.quest.GoldenGirl_eventstart.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.GoldenGirl_eventstart.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.GoldenGirl_eventstart.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.GoldenGirl_eventstart.win_condition.l2 = "location";
			pchar.quest.GoldenGirl_eventstart.win_condition.l2.location = "FortFrance_SecBrRoom"; // возможно закрыть бордель и вход только через боковую комнату
			pchar.quest.GoldenGirl_eventstart.function = "GoldenGirl_Party"; // таймер на начало вечеринки
			pchar.questTemp.GoldenGirl = "brothel";
			AddQuestRecord("GoldenGirl", "2");
		break;
		
		case "goldengirl_10":
			dialog.text = "Charles, que s'est-il passé, tu as l'air d'enfer !";
			link.l1 = "Angerran, foutu, Chievous, Excellence. Il a volé ma frégate la nuit dernière. Il a exécuté mon équipage de prise et a pris la mer dans la brume.";
			link.l1.go = "goldengirl_11";
		break;
		
		case "goldengirl_11":
			dialog.text = "C'est un retournement de situation désagréable, je comprends, mais croyez-moi - un tel résultat est tout à fait satisfaisant. Vous n'êtes pas dans le besoin pressant de navires et d'hommes, tandis que de Levi Vantadur paiera une somme considérable pour dissimuler la vérité derrière un certain duel récent. Ou bien il se souviendra de notre rôle dans sa dissimulation gratuite, ce qui vaut également beaucoup. De Chievous a agi de manière malhonnête deux fois, mais il est loin maintenant alors que nous avons encore de bonnes cartes contre lui.";
			link.l1 = "Trois fois, Votre Excellence. Angerran a avoué sa tricherie pendant notre partie de cartes. Mais il ne me remboursera pas avec de l'argent, si c'est ce que vous entendez. Il a dépassé les bornes. Il y avait une certaine personne sur ce navire ce matin... elle m'est très chère ! Je ne laisserai pas ce salaud lui faire du mal ! Tu entends ça, Jacques, je ne le permettrai pas !";
			link.l1.go = "goldengirl_12";
		break;
		
		case "goldengirl_12":
			dialog.text = "Je crois savoir de qui tu parles - je me souviens t'avoir vu avec une... fille, habillée en homme et armée jusqu'aux dents comme un pirate. Charles, ne fais pas l'idiot ! Tu as eu de la chance, tu as évité de gros ennuis et quoi, tu essaies de t'y replonger encore ? Laisse tomber. De Chievous est en fuite - Dieu merci ! Et pour ce qui est de ta 'copine d'armes', écoute le conseil de ton ami - va voir Julianna et oublie tout ça.";
			link.l1 = "Hors de question, Votre Excellence. Certaines choses dépassent simplement votre compréhension, d'accord ? Maintenant, dites-moi tout ce que vous savez sur ce salaud. Où pourrait-il aller depuis Saint-Pierre ? Et ne tentez pas de me dissuader à nouveau - j'ai emmerdé la Compagnie hollandaise, emmerdé des barons pirates, des gouverneurs-généraux, même la Sainte Inquisition ! Je ne suis pas un homme facile à effrayer. Je la récupérerai, quoi qu'il en coûte !";
			link.l1.go = "goldengirl_13";
		break;
		
		case "goldengirl_13":
			dialog.text = "Charles, avez-vous déjà réfléchi à la question de savoir qui nomme les gouverneur-généraux ? C'est un monde absolument différent ! Vous l'avez à peine effleuré, il est au-delà de votre compréhension, vous êtes comme un enfant dans un dépôt de poudre à canon. Et vous me demandez de vous passer une chandelle allumée. Quant aux gouverneur-généraux : de Poincy lui-même ne contredit jamais le comte ni en matière de monnaie ni en matière de politique. Vice-roi, le terme si populaire parmi les gens du commun, conviendrait parfaitement à Henri de Levi Vantadur.";
			link.l1 = "Et me voilà, ayant l'intention d'écorcher son seul héritier mâle, je sais ce que je risque ici. Maintenant, dis-moi simplement : y a-t-il quelque chose d'utile que tu sais qui pourrait m'aider ?";
			link.l1.go = "goldengirl_14";
		break;
		
		case "goldengirl_14":
			dialog.text = "En d'autres temps, j'aurais considéré ce geste vers ton pistolet comme la fin de notre amitié, Charles. Mais je comprends ton état d'esprit actuel. C'est pourquoi je suis prêt à oublier cela. Je ne sais rien qui puisse t'être utile, la frégate est partie vers l'ouest tôt ce matin. Tu devrais rendre visite à la Marquise... Attends, pas comme ça ! Julianna en sait beaucoup sur ton ennemi et elle a été personnellement... familière avec son père pendant un certain temps. Demande-lui. Contrairement à moi, elle ne t'arrêtera pas.";
			link.l1 = "C'est le plan. À bientôt, Excellence. Merci pour votre temps.";
			link.l1.go = "goldengirl_15";
		break;
		
		case "goldengirl_15":
			DialogExit();
			LocatorReloadEnterDisable("FortFrance_town", "reload9_back", false); 
			LocatorReloadEnterDisable("FortFrance_town", "reload91", false);
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_58";
			LAi_SetOwnerType(sld);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			pchar.questTemp.GoldenGirl = "find_girl";
		break;
		
		// В плену великого улова, andre39966
		case "VPVL_Magor_1":
			dialog.text = "Des marchandises de contrebande, dites-vous ? Hmm... fort intrigant. Je vous prie de m'éclairer sur les détails de votre découverte.";
			link.l1 = "Il y a trois jours, un navire chargé de contrebande devait jeter l'ancre dans la Baie de Le Marin. Le vaisseau a manqué son rendez-vous, mais j'ai de bonnes raisons de croire qu'il accostera bientôt. Peut-être que vos hommes pourraient organiser un accueil approprié pour ces brigands lorsqu'ils arriveront, Excellence.";
			link.l1.go = "VPVL_Magor_2";
			pchar.questTemp.VPVL_DontSpawnSmugglersShip = true; 
			DelLandQuestMark(npchar);
		break;

		case "VPVL_Magor_2":
			dialog.text = "Un navire sans nom transportant une cargaison non identifiée... Et vous présumez que je devrais déployour les forces de Sa Majesté sur la base de renseignements aussi nébuleux ?";
			link.l1 = "Excellence, j'admets que les détails sont rares. Mais je vous prie de me permettre de raconter comment ces renseignements sont entrés en ma possession. (raconte)";
			link.l1.go = "VPVL_Magor_3";
		break;

		case "VPVL_Magor_3":
			dialog.text = "Très bien, nous mettrons vos renseignements à l'épreuve. Si un navire transportant de la contrebande jette effectivement l'ancre au large des côtes de Le Marin, vous, Capitaine, serez généreusement récompensé(e) pour votre service à la Couronne. Revenez me voir dans trois jours. D'ici là, le brouillard de l'incertitude se sera levé.";
			link.l1 = "Parfait. Je reviendrai donc dans trois jours.";
			link.l1.go = "VPVL_Delete_Spawn_Ship";
			AddDialogExitQuest("VPVL_SetGovernorDialogueFlag");
			AddQuestRecord("VPVL", "6");
		break;

		case "VPVL_Magor_4":
			dialog.text = "Ah, Capitaine ! C'est un plaisir de vous recevoir à nouveau. Vos renseignements se sont avérés des plus précieux. Mes hommes ont intercepté le navire exactement là où vous l'aviez indiqué. Voici—cent cinquante doublons espagnols, fraîchement frappés et lourds dans la bourse. Prenez-les avec ma gratitude.";
			link.l1 = "Mes humbles remerciements, Excellence. C'est une bonne fortune que ma parcelle de renseignements ait servi les intérêts de la Couronne. Si l'occasion se présente à nouveau, sachez que mon bras armé et mon œil discernant restent à votre disposition.";
			link.l1.go = "VPVL_Delete_Flag";
			AddItems(PChar, "gold_dublon", 150);
			ChangeCharacterNationReputation(pchar, FRANCE, 5);
			DelLandQuestMark(npchar);
		break;

		case "VPVL_Delete_Flag":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.VPVL_GovernorDialogueAvailable");
			DeleteAttribute(pchar, "questTemp.VPVL_DontSpawnSmugglersShip");
		break;

		case "VPVL_Delete_Spawn_Ship":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.VPVL_Magor_Dialogue");
			AddDialogExitQuest("VPVL_KillCapitanOfSmuggler");
		break;
		// <=== В плену великого улова
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
