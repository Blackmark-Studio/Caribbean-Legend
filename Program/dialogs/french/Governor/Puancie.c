// Филипп де Пуанси - генерал-губернатор французских колоний
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "questTemp.Terrapin_KathyFox"))
			{
				dialog.text = "Salutations, "+pchar.name+". Come in; I've already been informed.";
				link.l1 = "Informé?  Il doit y avoir une erreur, Votre Excellence. Je suis venu vous informer de la réussite de votre mission, mais je vois que vous n'êtes pas dans les meilleures dispositions.";
				link.l1.go = "PZ_PoincyAngry1";
				DeleteAttribute(pchar, "questTemp.Terrapin");
				DeleteAttribute(pchar, "questTemp.Terrapin_KathyFox");
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "done")
			{
				dialog.text = "Content de vous voir, "+pchar.name+"On m'a informé de vos exploits et, surtout, vous avez réussi votre mission ! Vous vous êtes montré sous votre meilleur jour et je suis ravi de ne pas m'être trompé à votre sujet.";
				link.l1 = "Puis-je recevoir un ordre écrit de votre part pour libérer mon frère dès maintenant ?";
				link.l1.go = "serve";
				AddCharacterExpToSkill(pchar, "Sneak", 500);
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.Hardcore_Tortuga") && CheckAttribute(pchar, "questTemp.Sharlie.LevasserDied"))
			{
				dialog.text = "Ravi de vous voir, "+pchar.name+"J'ai entendu parler de vos exploits et surtout, votre mission est accomplie ! Cependant, je dois dire que je m'attendais à une idée plus astucieuse qu'une attaque frontale. Quel dommage pour les soldats français morts.\nMais la guerre est la guerre, il y a toujours des pertes. Vous avez rempli votre devoir, et je suis heureux d'avoir eu raison à votre sujet.";
				link.l1 = "Puis-je recevoir un ordre écrit de votre part pour libérer mon frère dès maintenant ?";
				link.l1.go = "serve";
				DeleteAttribute(pchar, "questTemp.Sharlie.Hardcore_Tortuga");
				DeleteAttribute(pchar, "questTemp.Sharlie.LevasserDied");
				break;
			}
			// Jason НСО 
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && GetCharacterIndex("Noel") == -1 && pchar.questTemp.Patria != "epizode_12_barondie" && pchar.questTemp.Patria != "epizode_12_baronfail" && pchar.questTemp.Patria != "epizode_12_baronkilled" && pchar.questTemp.Patria != "fail" && pchar.questTemp.Patria != "end")
			{
				if (CheckCharacterItem(pchar, "patent_fra"))
				{
					dialog.text = "Ravi de te voir, Charles. Tout d'abord, permets-moi de te féliciter pour avoir réussi la tâche complexe de protéger la colonie de Saint-Pierre des envahisseurs espagnols. Travail brillant, mon ami !";
					link.l1 = "Merci, Chevalier.";
					link.l1.go = "patria";
					Patria_SetInspector();
				}
				else
				{
					dialog.text = "Ravi de vous voir, Charles. Tout d'abord, permettez-moi de vous féliciter pour avoir réussi à accomplir la tâche complexe de protéger la colonie de Saint-Pierre des envahisseurs espagnols. Travail brillant, mon ami ! Je vous présente une autre opportunité de coopérer avec la Marine. La France a cruellement besoin d'officiers comme vous. J'espère que cette fois, vous serez plus raisonnable... Prenez le brevet, Capitaine Charles de Maure !";
					link.l1 = "Merci, Chevalier. Je suis heureux d'aider le pays et impatient de continuer à le servir !";
					link.l1.go = "patria";
					if (!CheckCharacterItem(pchar, "suit1")) GiveItem2Character(pchar, "suit1");
					GiveItem2Character(pchar, "patent_fra");
					EquipCharacterbyItem(pchar, "patent_fra");
					Items[sti(pchar.EquipedPatentId)].TitulCur = 2; 
					Items[sti(pchar.EquipedPatentId)].TitulCurNext = 0;
					ChangeCharacterNationReputation(pchar, FRANCE, 100);
					Patria_SetInspector();
				}
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Patria") && pchar.questTemp.Patria != "fail" && pchar.questTemp.Patria != "end")
			{
				if (!CheckCharacterItem(pchar, "patent_fra"))
				{
					dialog.text = "Charles, tu me déçois. En conséquence de tes actions imprudentes, tu as perdu ton brevet et ton rang dans la Marine Royale. Il n'y a plus de place pour une quelconque coopération. Congédié.";
					link.l1 = "Hmm...";
					link.l1.go = "patria_patentfail";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_1_return")
				{
					dialog.text = "Ravi de te voir, Charles. Rapporte !";
					if (CheckAttribute(pchar, "questTemp.Patria.Ecliaton_Fail"))
					{
						link.l1 = "Le travail est fait, la rançon de la colonie de San Jose est reçue. Mais il y a de mauvaises nouvelles : dans la bataille, le fort 'Eclatant' a été coulé. J'avais averti le capitaine de faire attention, mais il ne m'a pas écouté, et...";
						link.l1.go = "patria_8_1";
					}
					else
					{
						link.l1 = "Le travail est fait, la rançon de la colonie de San Jose est reçue.";
						link.l1.go = "patria_8";
					}
					break;
				}
				// belamour legendary edition фикс проверки мундира с мушкетом
				if(!IsUniformEquip())
				{
					dialog.text = "Monsieur, à partir de ce jour, ne pénétrez dans mes salles qu'en uniforme approprié !";
					link.l1 = "... ";
					link.l1.go = "exit";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_2_return" && IsUniformEquip())
				{
					dialog.text = "Baron, capitaine ! Heureux de vous voir !";
					link.l1 = "La mission est accomplie, Chevalier.";
					link.l1.go = "patria_14";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_3_return" && IsUniformEquip())
				{
					dialog.text = TimeGreeting()+", capitaine. Quelles nouvelles apportez-vous ?";
					if (CheckAttribute(pchar, "questTemp.Patria.Ecliaton_Fail"))
					{
						link.l1 = "Les Espagnols avaient prévu une attaque sur Port-au-Prince. À l'extrémité ouest d'Hispaniola, nous avons trouvé une escadre ennemie puissante. Elle a été complètement détruite. Cependant, l'‘Éclatant’ a été coulé.";
						link.l1.go = "patria_26_1";
					}
					else
					{
						link.l1 = "Les Espagnols avaient bien prévu une attaque sur Port-au-Prince. À l'extrémité occidentale d'Hispaniola, nous avons trouvé une escadre ennemie puissante. Elle a été complètement détruite.";
						link.l1.go = "patria_26";
					}
					break;
				}
				if (pchar.questTemp.Patria == "epizode_4_return" && IsUniformEquip())
				{
					dialog.text = TimeGreeting()+", Charles. Comment va Monsieur Stuyvesant?";
					link.l1 = "Tout va bien, Chevalier. La livraison a été réussie, voici la réponse à votre lettre.";
					link.l1.go = "patria_31";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_5_return" && IsUniformEquip())
				{
					dialog.text = "Charles, Baron... Vous êtes déjà de retour ?";
					link.l1 = "...";
					link.l1.go = "patria_36";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_6_return" && IsUniformEquip())
				{
					dialog.text = "Je n'aime pas ta mine renfrognée, Charles. Qu'a dit Stuyvesant, rapporte-moi !";
					if (pchar.questTemp.HWIC.Detector == "holl_win" || pchar.questTemp.HWIC.Detector == "self_win") link.l1 = "Litéralement, il a dit : 'dites au Chevalier qu'il n'est plus en charge de Sint-Maarten. Assez de lui. Et concernant l'inspection de la métropole - qu'il invente quelque chose, ce n'a jamais été difficile pour de Poincy de tout chambouler'. Après avoir annoncé ce message, le monsieur m'a expulsé de la résidence. Ce fut la fin de nos négociations.";
					else link.l1 = "Eh bien, voici ce qu'il a dit : 'votre suzerain a été bien trop gourmand sur Saint-Martin dernièrement, il est donc temps de tempérer sa faim insatiable.' Après cela, il a essayé de m'arrêter. J'ai dû me frayer un chemin jusqu'au navire à la lame. Voilà pour la diplomatie hollandaise.";
					link.l1.go = "patria_43";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_7_go" && IsUniformEquip())
				{
					dialog.text = "Capitaine, nous vous attendions. J'ai expliqué la situation actuelle au baron, et il a pleinement soutenu ma décision. Les Hollandais paieront pour leur arrogance.";
					link.l1 = "C'est donc la guerre ?";
					link.l1.go = "patria_51";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_7_continue" && IsUniformEquip() && pchar.location.from_sea == "Charles_town") // add-7
				{
					Patria_HunterShipChecker();
					if (CheckAttribute(pchar, "questTemp.Patria.Hunter.GiveShip"))
					{
						dialog.text = "Alors, mon ami, je vois que tu as capturé le navire des Indes orientales avec les marchandises. Excellent !";
						link.l1 = "Je te confie un navire, donne des ordres aux officiers du port, Chevalier.";
						link.l1.go = "patria_55";
					}
					else
					{
						dialog.text = "As-tu des questions, Charles ?";
						link.l1 = "Pas pour le moment, Monsieur. Je vais y aller alors...";
						link.l1.go = "exit";
					}
					break;
				}
				if (pchar.questTemp.Patria == "epizode_8" && IsUniformEquip())
				{
					dialog.text = "Enfin, vous êtes arrivé, Capitaine ! Il y a une urgence à Saint-Christophe !";
					link.l1 = "Une escadre hostile ?";
					link.l1.go = "patria_59";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_8_wait" && IsUniformEquip() && GetCompanionQuantity(pchar) < COMPANION_MAX)
				{
					dialog.text = "Es-tu prêt à prendre notre cotre courrier ?";
					link.l1 = "Je le suis.";
					link.l1.go = "patria_64";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_8_return")
				{
					dialog.text = "Capitaine de Maure, Seigneur Doily ! Heureux de vous voir ! Toute la ville a assisté à la leçon que vous avez donnée aux vauriens espagnols-hollandais qui convoitaient notre colonie !";
					link.l1 = "C'était mon devoir, Chevalier.";
					link.l1.go = "patria_66";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_9_start" && IsUniformEquip())
				{
					dialog.text = TimeGreeting()+", Charles. Commençons, voulez-vous ?";
					link.l1 = "Bien sûr, Chevalier. C'est pourquoi je suis ici.";
					link.l1.go = "patria_69";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_9_return" && IsUniformEquip())
				{
					dialog.text = "Je suis heureux d'accueillir dans mon bureau le vice-amiral de la Marine royale de France ! Oui, mon ami, tu ne t'es pas trompé : j'ai personnellement signé l'ordre de ta nomination. Formellement, il doit encore être approuvé en France, mais tu ne dois même pas douter que cela arrivera. Félicitations !";
					link.l1 = "Je sers ma nation !";
					link.l1.go = "patria_76";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_10_return" && IsUniformEquip())
				{
					if (GetQuestPastDayParam("questTemp.Patria.Curacao.Date") < 30) sTemp = "will be ready soon and"; // в зависимости от времени сколько добирался
					else sTemp = "is ready and";
					dialog.text = "Avez-vous réussi dans vos entreprises ? Le colonel Doily était-il satisfait ?";
					link.l1 = "Tout s'est déroulé parfaitement, Chevalier. La caravane de Stuyvesant a été capturée, tous les esclaves ont été amenés en Jamaïque, l'escadre du colonel "+sTemp+" en route pour Curaçao.";
					link.l1.go = "patria_81";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_11_return" && IsUniformEquip())
				{
					dialog.text = "Gloire aux vainqueurs ! Félicitations, félicitations, mon ami ! Vous ne cessez de m'étonner.";
					link.l1 = "Merci, Chevalier. Stuyvestant a été puni et est prêt à payer des indemnités, la paix est rétablie, Saint-Martin appartient désormais uniquement à la France.";
					link.l1.go = "patria_85";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_12_continue")
				{
					dialog.text = "Alors, mon ami, je suis heureux de te revoir. As-tu bien reposé?";
					link.l1 = "Oui, Chevalier. C'était une pause bien nécessaire... Vous avez mentionné une affaire délicate ?";
					link.l1.go = "patria_88";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_12_baronalive")
				{
					dialog.text = "Mon ami, tu dois être un sorcier ! Tu as réussi un exploit ! Notre baron ne veut plus créer une Compagnie de Commerce ici.";
					link.l1 = "Je crois que son seul désir en ce moment est de retourner à Paris.";
					link.l1.go = "patria_103";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_12_barondie")
				{
					dialog.text = "Charles, as-tu entendu parler du baron ? Il a été capturé par des pirates...";
					link.l1 = "Oui, Chevalier. Hélas, le baron est mort. Je le sais avec certitude.";
					link.l1.go = "patria_112";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_12_baronfail")
				{
					dialog.text = "Charles, comment va votre progression ? On m'a dit que le baron est monté à bord de votre navire...";
					link.l1 = "Oui, Chevalier. Il était à bord, je travaillais sur lui, mais... il est mort de la fièvre.";
					link.l1.go = "patria_x112";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_12_baronkilled")
				{
					dialog.text = "Charles, comment progressez-vous ? On m'a dit que le baron est monté à bord de votre navire...";
					link.l1 = "Oui, Chevalier. Il était à bord, je m'en occupais, mais... il est mort au combat.";
					link.l1.go = "patria_y112";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_12_baronwin")
				{
					dialog.text = "Mon ami, tu dois être un sorcier ! Tu as réussi un exploit ! Notre baron ne veut plus créer une Compagnie de Commerce ici.";
					link.l1 = "Il se dirige probablement vers Paris maintenant.";
					link.l1.go = "patria_117";
					break;
				}
				dialog.text = "Avez-vous des questions, Charles ?";
				link.l1 = "Pas en ce moment, monsieur. Je vais donc y aller...";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "Que voulez-vous? Monsieur?";
			link.l1 = "Rien de sérieux, juste une visite de courtoisie. Je m'en vais maintenant...";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// в тюрьме при старте игры
		case "Puancie_Jail":
			dialog.text = "Bonne journée à vous, Charles. Permettez-moi de me présenter : je suis Philippe de Poincy et je...";
			link.l1 = "Pourquoi diable m'avez-vous mis en prison ? C'est inapproprié ! Je suis un noble français et...";
			link.l1.go = "Puancie_Jail_1";			
			// belamour legendary edition -->
			link.l2 = "Bon... après-midi ? Bonne blague, Monsieur. Comment savez-vous qui je suis ?";
			link.l2.go = "Puancie_Jail_1a";	
		break;
		
		case "Puancie_Jail_1a":
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			AddCharacterExpToSkill(pchar, "Leadership", 40);
			dialog.text = "Jeune homme, je vous demande de ne pas m'interrompre! Vous parlez au Gouverneur Général des colonies françaises de l'archipel des Caraïbes! Je pardonnerai votre ton insolent seulement parce que vous ne pouviez pas savoir qui se tenait devant vous. Mais je vous recommanderais d'être plus réservé.";
			link.l1 = "Hmm... Je suis désolé, Votre Grâce.";
			link.l1.go = "Puancie_Jail_2";
		break;
		
		case "Puancie_Jail_1":
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			AddCharacterExpToSkill(pchar, "FencingL", 10);
			AddCharacterExpToSkill(pchar, "FencingS", 10);
			AddCharacterExpToSkill(pchar, "FencingH", 10);
			AddCharacterExpToSkill(pchar, "Pistol", 10);
			// <-- legendary edition
			dialog.text = "Ecoutez-moi, jeune homme, et ne m'interrompez pas ! Vous parlez avec le Gouverneur Général des colonies françaises dans l'archipel des Caraïbes ! Je pardonnerai votre ton seulement à cause de votre ignorance sur la personne à qui vous vous adressiez. Mais je vous recommande de vous montrer plus réservé à l'avenir.";
			link.l1 = "Hm... pardonnez-moi, votre Excellence.";
			link.l1.go = "Puancie_Jail_2";			
		break;
		
		case "Puancie_Jail_2":
			dialog.text = "Mieux. Maintenant, concernant votre question précédente - vous avez été considéré - par erreur - comme un espion espagnol et mis en état d'arrestation jusqu'à ce que votre statut soit clarifié. Ces maudits Castillans sont devenus plus actifs récemment, c'est pourquoi j'ai ordonné de détenir toutes les personnes suspectes.\nMais nous savons maintenant qui vous êtes - vous êtes vraiment Charles de Maure, un frère de Michel de Monper, et je suis personnellement descendu ici pour vous libérer. Et vous me criez dessus comme un petit garçon !";
			link.l1 = "Excusez-moi encore, Votre Excellence. Suis-je libre maintenant ?";
			link.l1.go = "Puancie_Jail_3";			
		break;
		
		case "Puancie_Jail_3":
			dialog.text = "Oui, vous l'êtes. Mais je veux vous parler en privé avant qu'un sergent n'ouvre votre cellule. Savez-vous que votre frère, l'un des plus valeureux guerriers de l'Ordre de Malte, a été arrêté et mis sous garde ?";
			link.l1 = "Je savais seulement que mon frère avait des ennuis et qu'il avait besoin d'aide. C'est pourquoi je suis venu ici de Paris.";
			link.l1.go = "Puancie_Jail_4";			
		break;
		
		case "Puancie_Jail_4":
			dialog.text = "Ravi de l'entendre. Je veux que vous sachiez que monsieur de Monper est dans un sérieux pétrin. J'ai toutes les raisons de le soupçonner d'abus de pouvoir, de détournement de biens et de faux témoignage. Mais vous pouvez l'aider.";
			link.l1 = "Monsieur, pourriez-vous m'en dire plus? Je ne comprends pas, Michel était la fierté de l'Ordre et...";
			link.l1.go = "Puancie_Jail_5";			
		break;
		
		case "Puancie_Jail_5":
			dialog.text = "Je le pensais aussi. Nous le pensions tous ! Mais ses récentes actions nous ont rendus... incertains quant à sa loyauté envers l'Ordre, alors il a été mis en état d'arrestation. Michel te donnera lui-même les détails. Il t'expliquera comment tu pourrais l'aider à s'occuper des accusations et à éviter la disgrâce.";
			link.l1 = "Où est mon frère maintenant ? Vous m'avez dit qu'il est en prison, mais je ne l'ai pas vu dans les parages...";
			link.l1.go = "Puancie_Jail_6";			
		break;
		
		case "Puancie_Jail_6":
			dialog.text = "Ai-je dit emprisonné, jeune homme? Ecoutez-vous même?! J'ai dit qu'il est en état d'arrestation! Ce n'est pas la même chose. Michel de Monper est retenu en état d'arrestation dans la base souterraine de Saint Pierre qui est une propriété de l'Ordre de Malte.\nJe vous permets de visiter la base sans aucune limitation, et de parler avec votre frère aussi souvent que vous le jugez nécessaire. Les Officiers et soldats de l'Ordre sont au courant de mes instructions et ils ne vous arrêteront pas.";
			link.l1 = "Où est cette base souterraine?";
			link.l1.go = "Puancie_Jail_7";			
		break;
		
		case "Puancie_Jail_7":
			dialog.text = "C'est ici, à Saint Pierre bien sûr. Trouvez la prison locale et entrez par la porte avec les symboles de l'Ordre. Descendez à la casemate au deuxième niveau du sous-sol. Monsieur Monper y sera. Mais ne vous inquiétez pas : en sortant de la prison, vous serez accueilli et escorté jusqu'à votre frère - j'ai tout prévu... Voilà. J'espère que nous nous reverrons, Charles. Sergent !";
			link.l1 = "Veuillez attendre, votre Excellence ! Et qu'en est-il de mes... affaires ? Mon épée et le reste ?";
			link.l1.go = "Puancie_Jail_8";			
		break;
		
		case "Puancie_Jail_8":
			dialog.text = "Vos biens ont été confisqués pour rembourser la dette de votre frère. Adieu, Monsieur de Maure.";
			link.l1 = "Nom de... ";
			link.l1.go = "Puancie_Jail_9";			
		break;
		
		case "Puancie_Jail_9":
			DialogExit();
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Sharlie_GoFromPrison", 3.5);
			NextDiag.CurrentNode = "First time";
			locCameraFromToPos(-11.09, 0.65, 3.05, true, -12.59, 0.09, -4.66);
		break;
		
		// возвращаем деньги
		case "saga":
			bDisableFastReload = false;
			LocatorReloadEnterDisable("Charles_townhall", "reload1_back", false);
			dialog.text = "Ah, Charles de Maure en personne ! Heureux de te voir. Je suppose que tu es venu ici pour discuter du sort de ton frère avec moi ?";
			link.l1 = "Je suis prêt à rembourser ce que Michel de Monper doit à l'Ordre et personnellement à vous.";
			if (sti(pchar.money) >= 1000000) link.l1.go = "saga_1";
			else link.l1.go = "saga_exit";			
		break;
		
		case "saga_exit":
			dialog.text = "Hm.. Mais où est l'argent ? Tu as un drôle de sens de l'humour, jeune homme, et je ne le comprends pas.";
			link.l1 = "Pardonnez-moi, Chevalier. J'ai oublié de l'argent dans mon coffre sur le navire. Je reviendrai bientôt.";
			link.l1.go = "exit";
			NextDiag.TempNode = "saga_repeat";	
		break;
		
		case "saga_repeat":
			dialog.text = "As-tu apporté l'argent, Charles ?";
			if (sti(pchar.money) >= 1000000)
			{
				link.l1 = "Bien sûr ! J'espère que cette somme couvrira entièrement toutes vos dépenses.";
				link.l1.go = "saga_1";
			}
			else
			{
				link.l1 = "Pas encore...";
				link.l1.go = "exit";
				NextDiag.TempNode = "saga_repeat";
			}		
		break;
		
		case "saga_1":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("Charles");
			AddMoneyToCharacter(pchar, -1000000);
			dialog.text = "Splendide ! Je les prendrai de vous. Vous vous êtes montré sous votre meilleur jour, Charles !";
			link.l1 = "Quand recevrai-je un ordre pour la libération de Michel de Monpe?";
			link.l1.go = "saga_2";			
		break;
		
		case "saga_2":
			dialog.text = "N'ayez pas hâte, jeune homme. Je ne peux qu'admirer que vous remboursiez les dettes et protégiez votre famille en mettant votre propre vie en danger. C'est une noblesse rare de nos jours... Mais l'argent n'est pas le principal dans cette triste histoire. Votre frère a obtenu une telle somme à condition d'accomplir une mission très délicate.\nMichel de Monper, en bon catholique, avait juré sur le Livre qu'il trouverait un moyen de punir un hérétique insolent et de rétablir la justice qu'il a violée pour la gloire de l'Ordre et de la Sainte Église...";
			link.l1 = "Mais il ne pourra pas tenir parole sous arrestation ! Si vous le libérez, nous serons capables d'accomplir la mission bien plus rapidement que si je devais la faire tout seul.";
			link.l1.go = "saga_3";			
		break;
		
		case "saga_3":
			dialog.text = "Voyez-vous, mon ami, votre frère m'a donné une forte raison de ne pas faire confiance à sa décence. Il n'y a aucune garantie qu'il ne s'échappera pas et ne rompra pas son serment. Donc, si vous voulez lever toutes les accusations contre lui, accomplissez le serment vous-même. Monsieur de Monper vous expliquera les détails.";
			link.l1 = "Hm... Je ne m'attendais pas à cela. Mais tu ne me laisses pas d'autre choix. Je prendrai ma décision finale après avoir parlé avec mon frère.";
			link.l1.go = "saga_4";			
		break;
		
		case "saga_4":
			dialog.text = "Je commence à vraiment t'apprécier, Charles. Un jour, peut-être, nous deviendrons amis. Quoi qu'il en soit, voici mon dernier terme pour libérer ton frère. Je te donne ma parole que la réputation de ta famille ne sera pas ternie si tu fais ce que ton frère n'a pas fait. Et tu pourras compter sur mon amitié à l'avenir.";
			link.l1 = "Je vous ai parfaitement compris. Adieu !";
			link.l1.go = "saga_5";			
		break;
		
		case "saga_5":
			DialogExit();
			pchar.questTemp.Saga = "mishelle";//Сага - старт
			AddQuestRecord("Sharlie", "21");
			NextDiag.CurrentNode = "First time";
			AddMapQuestMarkCity("FortFrance", false);
			AddLandQuestMark(characterFromId("Mishelle"), "questmarkmain");
		break;
		
		case "serve":
			dialog.text = "Ne t'inquiète pas, "+pchar.name+", Je tiendrai parole. Ton frère sera libéré et toutes les accusations seront levées contre lui. La réputation de ta famille n'est plus en danger maintenant. Je dirais que c'est tout grâce à tes mérites et seulement les tiens. Ton père peut être fier d'avoir élevé un tel fils.";
			link.l1 = "Merci pour ces aimables paroles, Chevalier. Puis-je partir pour la Martinique immédiatement ?";
			link.l1.go = "serve_1";	
			Island_SetReloadEnableGlobal("Tortuga", true);
			CloseQuestHeader("Terrapin");
			SetFunctionTimerCondition("Terrapin_SetFontene", 0, 0, 5, false); // таймер
		break;
		
		case "serve_1":
			dialog.text = "Attends un peu, mon ami. J'espère que je peux t'appeler mon ami, n'est-ce pas? Je veux exprimer ma gratitude personnellement. J'observe tes progrès depuis ton arrivée ici et je suis au courant de la plupart de tes exploits. Tu t'es fait un nom dans les Caraïbes et, sans aucun doute, tu es également bien connu et respecté dans certaines sections particulières de la société. La France a besoin de gens comme toi\nCapitaine"+GetFullName(pchar)+"Par le pouvoir qui m'est conféré par Sa Majesté, le Roi de France, j'ai l'honneur de vous offrir un brevet de capitaine de la Marine Royale et de placer sous votre commandement le navire de la marine française, une frégate légère 'Gryffondor' !\nSon ancien capitaine de Fontenot sera gouverneur de Tortuga grâce à vous et la meilleure frégate légère des Caraïbes a besoin d'un capitaine. Acceptez-vous cette offre ?";
			link.l1 = "Intéressant. Qu'est-ce que j'en tire en retour ?";
			link.l1.go = "serve_2";		
		break;
		
		case "serve_2":
			dialog.text = "Juste un peu. Un dixième de votre prise et accomplir des missions délicates parfois. J'attends votre décision.";
			link.l1 = "Personne ne rejetterait une telle offre, Votre Excellence ! C'est un honneur de servir ma nation !";
			link.l1.go = "serve_3";
			link.l2 = "Veuillez excuser mon manque de modestie, mais je dois refuser votre offre pour l'instant. Les affaires familiales pourraient exiger un retour immédiat à la patrie.";
			link.l2.go = "serve_no";
			InterfaceStates.Buttons.Save.enable = true;
		break;
		
		case "serve_no":
			ChangeCharacterComplexReputation(pchar, "fame", 7);
			dialog.text = "Hélas. J'espérais que vous accepteriez... Mais, néanmoins, je suis forcé de vous demander une faveur de plus, en réalité c'est aussi dans votre intérêt. La Martinique est attaquée. Il y a de lourds combats dans le port et dans la ville elle-même.\nHélas, je n'ai personne à envoyer là-bas pour aider la garnison sauf vous. Je vous demande, en tant que patriote de votre patrie, de repousser l'assaut par tous les moyens nécessaires. J'espère que vous avez suffisamment de ressources pour cela.\nDe plus, votre frère est toujours là-bas, vous pouvez sauver sa vie.";
			link.l1 = "Mon frère est en danger ? Je suis en route !";
			link.l1.go = "serve_exit";			
		break;
		
		case "serve_3":
			dialog.text = "Telles paroles honorables ! Paroles d'un véritable soldat et fils loyal de la Patrie ! Félicitations, monsieur "+GetFullName(pchar)+"Vous êtes promu au rang de commandant des forces navales de France. Acceptez cet uniforme de ma part. Portez-le fièrement et soyez-en digne !";
			link.l1 = "Je sers ma nation !";
			link.l1.go = "serve_4";	
			locCameraFromToPos(-2.63, 2.20, -4.96, true, 2.64, 0.22, -4.96);
			npchar.greeting = "puancie_1";			
		break;
		
		case "serve_4":
			dialog.text = "La corvette lourde 'Gryffondor' est maintenant sous votre commandement. A partir de ce moment, ce navire d'exception vous appartient. Utilisez ses hautes qualités pour la gloire de Sa Majesté et pour renforcer l'influence française sur l'archipel des Caraïbes !";
			link.l1 = "Tout de suite !";
			link.l1.go = "serve_5";
			LAi_Fade("SharlePutsSuit", "");
		break;
		
		case "serve_5":
			if (GetCompanionQuantity(pchar) > 4)
			{
				dialog.text = "Mais votre escadre est déjà trop grande, alors revenez chercher le 'Gryffondor' lorsque vous vous serez débarrassé d'un navire.";
				link.l1 = "D'accord. Je ferai cela.";
				link.l1.go = "serve_wait";		
			}
			else
			{
				dialog.text = "En plus du navire, vous obtiendrez son capitaine en exercice et l'équipage. Si vous le souhaitez, vous pouvez le garder sous votre commandement ou le débarquer du navire et nous lui trouverons un autre poste.";
				link.l1 = "Compris !";
				link.l1.go = "serve_6";
			}
		break;
		
		case "serve_6":
			dialog.text = "Mais j'ai de mauvaises nouvelles pour vous, capitaine. Je viens d'être informé que la Martinique est attaquée. Il y a de violents combats dans le port et dans la ville elle-même.\nHélas, je n'ai personne à envoyer là-bas pour aider la garnison, sauf vous. Voici votre première mission :\n Protégez Saint-Pierre ! De plus, votre frère est toujours là-bas, vous pouvez sauver sa vie.";
			link.l1 = "Mon frère est en danger ? Je suis en route !";
			link.l1.go = "serve_7";
		break;
		
		case "serve_7":
			DialogExit();
			locCameraTarget(PChar);
			locCameraFollow();
			CreateGriffondor();
			sld = characterFromId("GriffOfficer");
			SetCharacterRemovable(sld, true);
			SetCompanionIndex(pchar, -1, sti(sld.index));
			sld.loyality = MAX_LOYALITY;
			NextDiag.CurrentNode = "First time";
			DeleteAttribute(pchar, "questTemp.Terrapin");
			pchar.questTemp.Sharlie = "senpierbattle";
			pchar.questTemp.Sharlie.DefendSP = "true";
			AddQuestRecord("Sharlie", "24");
			pchar.quest.DefendSP_prepare.win_condition.l1 = "location";
			pchar.quest.DefendSP_prepare.win_condition.l1.location = "Martinique";
			pchar.quest.DefendSP_prepare.function = "DefendSP_PrepareMartinique";
			AddCharacterExpToSkill(pchar, "Leadership", 2000);
			AddCharacterExpToSkill(pchar, "Fortune", 500);
		break;
		
		case "serve_wait":
			DialogExit();
			NextDiag.CurrentNode = "serve_shipcheck";
		break;
		
		case "serve_shipcheck":
			dialog.text = "Es-tu prêt à prendre le commandement du 'Gryffondor' ?";
			if (GetCompanionQuantity(pchar) > 4)
			{
				link.l1 = "Pas encore, je repositionne mes navires dans l'escadre...";
				link.l1.go = "exit";
			}
			else
			{
				link.l1 = "Je le suis.";
				link.l1.go = "serve_5a";
			}
			NextDiag.TempNode = "serve_wait";
		break;
		
		case "serve_5a":
			dialog.text = "Splendide ! Avec le navire, vous obtiendrez son capitaine par intérim et l'équipage. Si vous le souhaitez, vous pouvez le garder sous votre commandement ou le débarquer du navire et nous lui trouverons un autre poste.";
			link.l1 = "Compris !";
			link.l1.go = "serve_6";
		break;
		
		case "serve_exit":
			DialogExit();
			NextDiag.CurrentNode = "First time";
			DeleteAttribute(pchar, "questTemp.Terrapin");
			pchar.questTemp.Sharlie = "senpierbattle";
			pchar.questTemp.Sharlie.DefendSP = "true";
			AddQuestRecord("Sharlie", "23");
			pchar.quest.DefendSP_prepare.win_condition.l1 = "location";
			pchar.quest.DefendSP_prepare.win_condition.l1.location = "Martinique";
			pchar.quest.DefendSP_prepare.function = "DefendSP_PrepareMartinique";
			AddCharacterExpToSkill(pchar, "Leadership", 1000);
			AddCharacterExpToSkill(pchar, "Fortune", 250);
		break;
		
		// Jason НСО
		case "patria":
			if (CheckAttribute(pchar, "questTemp.Mtraxx.CharleePrince")) DeleteAttribute(pchar, "questTemp.Mtraxx.CharleePrince"); // Rebbebion, удалить команду пиратов на всякий
			dialog.text = "Et ce n'est que le début, Monsieur ! Je suis sûr que vous irez loin, avec de tels talents militaires ! Et j'ai déjà une autre tâche pour un excellent officier naval, avec qui, j'en suis sûr, vous vous débrouillerez tout aussi bien. De plus, elle est directement liée à votre mission précédente.";
			link.l1 = "Je suis tout ouïe, monsieur";
			link.l1.go = "patria_1";
		break;
		
		case "patria_1":
			dialog.text = "Mais permettez-moi d'abord de vous présenter la personne qui est entrée dans mon bureau. Voici le Baron Noel Forget, membre honoraire de la Compagnie des Indes Occidentales Françaises. Arrivé à l'archipel pour inspecter nos colonies afin d'élargir l'organisation des plantations de canne à sucre et d'autres cultures, ainsi que pour explorer la possibilité de développer des liens commerciaux dans notre région. De Paris, il est prescrit de lui donner toutes sortes de soutien et d'assistance dans ces affaires, ce que nous ferons sans aucun doute. Baron, je vous présente Monsieur Charles de Maure, l'un des capitaines les plus talentueux au service de la France...";
			link.l1 = "Bonjour, mon ami.";
			link.l1.go = "patria_2";
		break;
		
		case "patria_2":
			DialogExit();
			sld = characterFromId("Noel");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "patria_3":
			dialog.text = "Alors, Charles, pendant que le baron et moi inspectons Saint-Christophe, je vous assigne la tâche suivante. Personne ne peut attaquer les colonies françaises et s'en tirer à bon compte, et les Espagnols, bien qu'ils aient déjà reçu une leçon pour l'agression sur la Martinique, doivent répondre de leurs crimes avec leurs bourses et compenser les dommages causés à la colonie.\nAvec le baron français, une puissante escadre est arrivée, composée d'un puissant navire de 66 canons, 'Eclatant'. Le capitaine du navire est un marin expérimenté, mais aux Caraïbes pour la première fois, il est donc sous votre commandement. Avec 'Eclatant', vous vous rendrez sur les côtes de l'île espagnole de Trinidad, et demanderez aux Espagnols une compensation monétaire de trois cent mille pesos pour l'attaque sur Saint-Pierre.";
			link.l1 = "Chevalier, croyez-vous sincèrement que les Espagnols vont accepter ?";
			link.l1.go = "patria_4";
		break;
		
		case "patria_4":
			dialog.text = "J'en suis sûr - après que l''Eclatant' et votre escadre aient réduit en miettes le Fort San Jose. Débarquer des troupes et s'emparer de la ville, en perdant des soldats, je pense, ne sera pas nécessaire. Attaquez sans avertissement, détruisez le fort, puis signalez au commandant que vous voulez fixer les conditions. Dans cette situation, les Espagnols n'auront nulle part où aller, et ils préféreront payer. Que feriez-vous si vous agissiez à la place du gouverneur de la ville laissée sans protection ?";
			link.l1 = "Hmm, cela semble raisonnable, Chevalier.";
			link.l1.go = "patria_5";
		break;
		
		case "patria_5":
			dialog.text = "Est-ce clair ce que vous avez à faire ?";
			link.l1 = "Oui, votre Grâce.";
			link.l1.go = "patria_6";
		break;
		
		case "patria_6":
			// belamour legendary edition фикс проверки мундира с мушкетом
			if(IsUniformEquip())
			{
				dialog.text = " Alors, allez-y. Voici une lettre pour le Capitaine de 'Eclatant' avec la confirmation de votre autorité. Ce navire d'exception avec un équipage bien entraîné est maintenant à votre disposition. Charles, et n'oubliez pas que vous servez maintenant la France, et pour bien communiquer avec des officiels comme moi, il est conseillé de porter un uniforme. Il vous va parfaitement. Bonne chance, Capitaine de Maure !";
			}
			else
			{
				dialog.text = " Alors, au travail. Voici une lettre pour le capitaine de 'Eclatant' confirmant votre autorité. Ce magnifique navire avec un équipage bien entraîné est maintenant à votre disposition. Oh et Charles : mets un uniforme de capitaine, je te l'ordonne ! Premièrement, il n'est pas digne pour un officier de la Marine Royale Française de ressembler à un marchand ou à un corsaire, et deuxièmement, ton uniforme te va à merveille. Exécute cela sur-le-champ, Capitaine de Maure !";
			}
			link.l1 = "Bonjour, mon ami.";
			link.l1.go = "patria_7";
		break;
		
		case "patria_7":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			LAi_SetHuberType(npchar);
			AddQuestRecord("Patria", "1");
			pchar.questTemp.Patria = "epizode_1";
			Patria_SetEcliaton();
			pchar.questTemp.GoldenGirl_Block = true;	// Запрещаем квест Дороже Золота
		break;
		
		case "patria_8_1":
			if (sti(pchar.money) >= 300000) AddMoneyToCharacter(pchar, -300000);
			else pchar.questTemp.Patria.NoMoney = "true";
			dialog.text = "‘Eclatant’ a coulé ? Charles, c'est un désastre ! Que va dire le ministre maintenant ? Tu m'as déçu, Charles ! J'étais sûr que je pouvais compter sur ton expérience, et toi... Hélas, mais tu seras tenu responsable de cela. Je vais rédiger un rapport, et tu ferais mieux de disparaître un moment. Ton service dans la Marine Royale est terminé.";
			link.l1 = "Hmm... Je suis désolé, Monsieur. Il semblerait qu'il soit vraiment préférable pour moi de disparaître pendant un mois ou deux, jusqu'à ce que le ministre apaise sa colère. Adieu, et encore une fois je suis vraiment désolé de vous avoir laissé tomber.";
			link.l1.go = "patria_8_2";
		break;
		
		case "patria_8_2":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			pchar.questTemp.Patria = "fail";
			AddQuestRecord("Patria", "8");
			CloseQuestHeader("Patria");
			DeleteAttribute(pchar, "questTemp.GoldenGirl_Block");	// Разрешаем квест Дороже Золота
			RemoveItems(pchar, "patent_fra", 1);
			if (CheckAttribute(pchar, "questTemp.Patria.NoMoney"))
			{
				ChangeCharacterComplexReputation(pchar, "nobility", -20);
				ChangeCharacterNationReputation(pchar, FRANCE, -30);
				DeleteAttribute(pchar, "questTemp.Patria.NoMoney");
			}
			else
			{
				ChangeCharacterComplexReputation(pchar, "nobility", -5);
				ChangeCharacterNationReputation(pchar, FRANCE, -5);
			}
			pchar.quest.Patria_SanJoseReturnOver.over = "yes"; // снять таймер
		break;
		
		case "patria_8":
			if (sti(pchar.money) >= 300000)
			{
				dialog.text = "Parfait !";
				link.l1 = "Voici, veuillez prendre ces trois cent mille.";
				link.l1.go = "patria_9";
			}
			else
			{
				dialog.text = "Parfait, mais où est l'argent, Charles ?";
				link.l1 = "Eh bien, Dans le coffre du navire, je le livrerai dans un instant !";
				link.l1.go = "patria_8_3";
			}
		break;
		
		case "patria_8_3":
			DialogExit();
			npchar.dialog.currentnode = "patria_8_4";
		break;
		
		case "patria_8_4":
			dialog.text = "Alors, Charles, as-tu apporté la rançon de Trinidad ?";
			if (sti(pchar.money) >= 300000)
			{
				link.l1 = "Oui, Monsieur. Le voici.";
				link.l1.go = "patria_9";
			}
			else
			{
				link.l1 = "Je l'apporterai dans un instant !";
				link.l1.go = "patria_8_3";
			}
		break;
		
		case "patria_9":
			AddMoneyToCharacter(pchar, -300000);
			dialog.text = "Je suis satisfait de toi, Charles, tu ne déçois jamais. La tâche n'était pas facile, et tu reçois une somme de 50 000 pesos sur le montant de la rançon en guise de récompense. Prends-la, elle est toute à toi.";
			link.l1 = "Mes remerciements, Chevalier.";
			link.l1.go = "patria_10";
		break;
		
		case "patria_10":
			AddMoneyToCharacter(pchar, 50000);
			dialog.text = "Il y a déjà une nouvelle tâche pour vous. Monsieur Forget a terminé l'inspection à Saint-Christophe et souhaite maintenant visiter nos colonies du nord. Je vous demande d'emmener le baron à la Tortue et à Hispaniola, de l'aider de toutes les manières dans ses affaires et de satisfaire ses demandes. Est-ce clair, Charles ?";
			link.l1 = "Bien sûr, Chevalier.";
			link.l1.go = "patria_11";
		break;
		
		case "patria_11":
			dialog.text = "Le Baron manque de temps, donc je vous demande de ne pas vous laisser distraire par d'autres affaires et de ne pas retarder le voyage de plus de deux mois.";
			link.l1 = "Bien sûr, Monsieur. Le voyage entre les îles ne prend pas tant de temps, à moins que les affaires de Monsieur Forget dans les colonies ne soient chronophages.";
			link.l1.go = "patria_12";
		break;
		
		case "patria_12":
			dialog.text = "Parfait. Alors le Baron voyagera sur votre navire. Offrez-lui la meilleure cabine qui soit.";
			link.l1 = "Bien sûr, Chevalier !";
			if(IsUniformEquip()) link.l1.go = "patria_13";
			else link.l1.go = "patria_13_1";
		break;
		
		case "patria_13_1":
			dialog.text = "Et encore une chose, Charles : Vous êtes encore sans votre uniforme d'officier ! C'est votre dernier avertissement. À partir de ce moment, je vous demande de venir me voir uniquement en uniforme, sinon je ne vous écouterai pas. Vous êtes en service, et la discipline doit être tout, surtout dans l'apparence d'un officier de la marine !";
			link.l1 = " Pardonnez-moi, Chevalier. Cela ne se reproduira plus.";
			link.l1.go = "patria_13";
		break;
		
		case "patria_13":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			AddQuestRecord("Patria", "9");
			pchar.questTemp.Patria = "epizode_2";
			Patria_VisiterBegin();
			pchar.quest.Patria_SanJoseReturnOver.over = "yes"; // снять таймер
			ChangeCharacterNationReputation(pchar, FRANCE, 10);
			ChangeCharacterComplexReputation(pchar, "nobility", 3); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 3);
			ChangeCharacterComplexReputation(pchar, "fame", 3);
		break;
		
		case "patria_14":
			sld = characterFromId("Noel");
			ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto4");
			dialog.text = "Je n'avais aucun doute que votre voyage serait couronné de succès. Des nouvelles de la Tortue ou de Port-au-Prince ?";
			link.l1 = "...";
			link.l1.go = "patria_15";
		break;
		
		case "patria_15":
			DialogExit(); // переключение на инспектора
			LAi_SetActorType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Noel"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Puancie");
			sld.dialog.currentnode = "patria_16";
			LAi_SetActorType(sld);
			LAi_ActorSetHuberMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
			bDisableCharacterMenu = true;//лоченые интерфейсы
		break;
		
		case "patria_16":
			dialog.text = "";
			link.l1 = "Oui, Chevalier, j'apporte des nouvelles mais elles ne sont guère agréables. Premièrement, le Gouverneur de Port-au-Prince est sûr que les Espagnols préparent une attaque sur la colonie et pour cela ils rassemblent une escadre militaire sur... em-m, comment cela s'appelle... sur Santiago, oui. Et cela ne semble pas être une rumeur. Je crois que nous ne pouvons ignorer cette affaire, d'autant plus que les plantations de Port-au-Prince sont parmi les meilleures que j'aie jamais vues.";
			link.l1.go = "patria_17";
		break;
		
		case "patria_17":
			dialog.text = "Les Espagnols préparent-ils une attaque contre Port-au-Prince? Hmm... Très bien. Nous vous donnerons des instructions pour vous occuper de ce capitaine Charles de Maure. 'Éclatant' vient d'être réparé, équipé et prêt à prendre la mer...";
			link.l1 = "Et une autre chose, Monsieur : à Paris, l'île de Saint-Martin, qui se trouve au nord d'ici, est considérée comme une colonie française, mais le Capitaine Charles de Maure m'a dit que les Hollandais y ont le contrôle. Est-ce vrai, Chevalier ?";
			link.l1.go = "patria_18";
		break;
		
		case "patria_18":
			dialog.text = "Hmm... C'est vrai dans une certaine mesure. Saint-Martin est une colonie française. Cependant, Baron, d'un point de vue économique, cette île est absolument inutile - la superficie est petite, le sol y est pauvre, maigre, l'eau douce est rare, et celle qui est dans les puits est boueuse et amère. On m'a même dit que l'eau de pluie y était récoltée pour boire.\nPar conséquent, Saint-Martin a été transféré à la Compagnie néerlandaise des Indes occidentales pour un bail à long terme, qui l'utilise comme point de transit nord pour les navires de la Compagnie de la région vers la métropole. Les Néerlandais ont agrandi la colonie de Phillipsburg là-bas, construit un fort et un port, et pour ceux qui sont arrivés dans l'archipel relativement récemment, comme le capitaine Charles de Maure, Saint-Martin semble être une colonie néerlandaise.";
			link.l1 = "Mais de jure, l'île nous appartient ?";
			link.l1.go = "patria_19";
		break;
		
		case "patria_19":
			dialog.text = "Bien sûr. Mais comme je l'ai dit, il est plus rentable d'obtenir de l'argent pour le loyer que d'utiliser ses ressources rares.";
			link.l1 = "Il me semble que cette île serait très utile pour la Compagnie française des Indes occidentales lorsqu'elle apparaîtra dans les Caraïbes. Le sens de ce que vous venez d'annoncer - le poste avancé du nord sur la route vers l'Europe. Je dois visiter cette colonie, et il est très probable que la location de l'île aux Néerlandais sera interrompue.";
			link.l1.go = "patria_20";
		break;
		
		case "patria_20":
			dialog.text = "Tout d'abord, il te faut envoyer une requête à Willemstad, au directeur de la Compagnie néerlandaise des Indes occidentales, la Monnaie de Peter Stuyvesant. Il doit donner son autorisation pour l'inspection de l'île - après tout, les Hollandais y sont depuis longtemps.";
			link.l1 = "Alors nous devons envoyer un courrier à Willemstad.";
			link.l1.go = "patria_21";
		break;
		
		case "patria_21":
			dialog.text = "Le problème est que, Monsieur Stuyvesant est rarement présent à Willemstad, il voyage constamment et s'occupe des affaires de la Compagnie sur son galion...";
			link.l1 = "Mais au moins, parfois, il est présent là-bas, je suppose ? Quoi qu'il en soit, les Hollandais sont obligés de garantir l'inspection de l'île à ses propriétaires légitimes. Pourquoi ne pas envoyer une lettre au Gouverneur de Philipsburg ?";
			link.l1.go = "patria_22";
		break;
		
		case "patria_22":
			dialog.text = "Le sieur Martin Thomas, avec tout le respect qui lui est dû, n'est qu'un simple employé, la véritable gestion est assurée par la Compagnie. Baron, je vais résoudre ce problème, ne vous inquiétez pas, cela prendra un peu de temps.";
			link.l1 = "Eh bien, j'ai tout le temps devant moi. Après tout, nous devons encore visiter les colonies du sud, la Guadeloupe et la Martinique. Quel dommage que le Capitaine Charles de Maure ne m'accompagne pas cette fois - il doit une fois de plus se rendre à Hispaniola...";
			link.l1.go = "patria_23";
		break;
		
		case "patria_23":
			DialogExit();
			LAi_SetActorType(pchar); // 17-add
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			bDisableCharacterMenu = false;//лоченые интерфейсы
			sld = characterFromId("Puancie");
			sld.dialog.currentnode = "patria_24";
			LAi_SetActorType(sld);
			LAi_ActorSetHuberMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
			ChangeCharacterNationReputation(pchar, FRANCE, 10);
		break;
		
		case "patria_24":
			dialog.text = "Oui, oui, nous retardons notre cher capitaine avec nos conversations ennuyeuses ! Charles, emmène l'Éclatant à l'escadron, avance vers Hispaniola et découvre toute menace réelle pour Port-au-Prince de la part des Espagnols. S'il y en a, alors occupe-t'en. Cependant, ce n'est pas à moi de t'apprendre, tu sais tout mieux que moi. Si tu ne trouves rien, alors tu ne devrais pas perdre ton temps, j'ai besoin de toi ici. Je t'attends avec le rapport au plus tard dans un mois. Bonne chance, mon ami !";
			link.l1 = "Merci, Chevalier. Je vais mettre les voiles sur-le-champ.";
			if (ChangeCharacterHunterScore(pchar, "holhunter", 0) > 10) link.l1.go = "patria_25_1";
			else link.l1.go = "patria_25_2";
		break;
		
		case "patria_25_1":
			dialog.text = "Et une chose de plus, Charles : j'ai entendu dire que vous aviez des problèmes avec les autorités néerlandaises ? S'il vous plaît, réglez cette question dès que possible, dans un avenir proche vous devrez visiter leurs colonies. Comme vous le comprenez, cela serait impossible sous le feu des forts.";
			link.l1 = "Très bien, Monsieur, ce sera fait.";
			link.l1.go = "patria_25";
		break;
		
		case "patria_25_2":
			dialog.text = "Et une chose de plus, Charles : je te préviens : évite tout conflit avec les Hollandais. Dans un avenir proche, tu devras visiter leurs colonies. Comme tu le comprends, cela serait impossible sous le feu des forts...";
			link.l1 = "Très bien, Monsieur. Pas de querelles avec les Hollandais.";
			link.l1.go = "patria_25";
		break;
		
		case "patria_25":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			LAi_SetHuberType(npchar);
			AddQuestRecord("Patria", "15");
			pchar.questTemp.Patria = "epizode_3";
			Patria_PortPaxBegin();
			ChangeCharacterComplexReputation(pchar, "nobility", 1); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterComplexReputation(pchar, "fame", 1);
		break;
		
		case "patria_26_1":
			dialog.text = "« Eclatant » a coulé ? Charles, c'est un désastre ! Que dira le ministre maintenant ? Tu m'as déçu, Charles ! J'étais sûr que je pouvais compter sur ton expérience, et toi... Hélas, mais tu devras en répondre. Je vais rédiger un rapport, et tu ferais mieux de disparaître un moment. Ton service dans la Marine Royale est terminé.";
			link.l1 = "Hmm ... Je suis désolé, Monsieur. Il semble vraiment préférable pour moi de disparaître pendant un mois ou deux, jusqu'à ce que le ministre apaise sa colère. Au revoir, et encore une fois, je suis vraiment désolé de vous laisser tomber.";
			link.l1.go = "patria_26_2";
		break;
		
		case "patria_26_2":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			pchar.questTemp.Patria = "fail";
			AddQuestRecord("Patria", "19");
			CloseQuestHeader("Patria");
			DeleteAttribute(pchar, "questTemp.GoldenGirl_Block");	// Разрешаем квест Дороже Золота
			RemoveItems(pchar, "patent_fra", 1);
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
			ChangeCharacterNationReputation(pchar, FRANCE, -5);
			pchar.quest.Patria_PortPaxOver.over = "yes"; // снять таймер
		break;
		
		case "patria_26":
			dialog.text = "Excellent ! Tant que nous aurons des capitaines dans notre marine comme vous, nous ne devrions pas craindre les ruses des Castillans. J'enverrai demain un courrier à Port-au-Prince avec une dépêche et un courrier de France, et en même temps je laisserai entendre dans une lettre personnelle à Monsieur Jeremy Deschamps du Mussaca qu'il serait bien de vous remercier pour le service, ainsi je peux m'assurer que vous, Charles, recevrez une récompense bien méritée.\nEt maintenant passons à votre prochaine mission. Oui, mon ami, j'ai une nouvelle mission pour vous, cependant cette fois-ci, ce n'est pas une mission militaire mais très délicate, et j'aimerais que vous la réalisiez.";
			link.l1 = "Je suis tout ouïe, Chevalier.";
			link.l1.go = "patria_27";
		break;
		
		case "patria_27":
			dialog.text = "Je suppose que vous vous souvenez de ma discussion avec Monsieur Forget à propos de Saint-Martin ? Nous devons assurer le baron que la colonie a été inspectée, et vous irez à Curaçao, à Willemstad, voir le directeur de la Compagnie, Peter Stuyvesant. Il est là en ce moment, et y sera pour trois semaines encore. De plus, vous devrez escorter le fluyt avec les marchandises de la Compagnie jusqu'à Curaçao et remettre à Mynheer Stuyvesant une lettre de ma part.";
			link.l1 = "Sont-ce là toutes les tâches ?";
			link.l1.go = "patria_28";
		break;
		
		case "patria_28":
			dialog.text = "Oui, capitaine. Informez-moi de la réponse de Mynheer Stuyvesant. Nous devrions être juste à temps avant que Monsieur Forget ne revienne de son voyage à la Martinique et à la Guadeloupe, et il pourra enfin visiter Saint-Martin, qu'il souhaite vraiment visiter.";
			link.l1 = "Très bien. Puis-je partir ?";
			link.l1.go = "patria_29";
		break;
		
		case "patria_29":
			dialog.text = "Vous pouvez, Charles. Ne tardez pas trop, le baron n'aime pas attendre. Et en rendant visite à Peter Stuyvesant, assurez-vous de porter votre uniforme ! Tout doit paraître officiel, si vous voyez ce que je veux dire.";
			link.l1 = "Bien sûr, Chevalier. Au revoir !";
			link.l1.go = "patria_30";
		break;
		
		case "patria_30":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			AddQuestRecord("Patria", "20");
			pchar.questTemp.Patria = "epizode_4";
			Patria_CureerBegin();
			pchar.quest.Patria_PortPaxOver.over = "yes"; // снять таймер
			GiveItem2Character(pchar, "Reserve_item_01");
			ChangeItemDescribe("Reserve_item_01", "itmdescr_Reserve_item_01_1");
			ChangeCharacterNationReputation(pchar, FRANCE, 10);
			ChangeCharacterComplexReputation(pchar, "nobility", 5); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 5);
			ChangeCharacterComplexReputation(pchar, "fame", 5);
		break;
		
		case "patria_31":
			RemoveItems(pchar, "Reserve_item_01", 1);
			dialog.text = "Merci, capitaine, donnez-le moi... (lisant)... Eh bien, excellent ! Peter Stuyvesant dit que le Baron Forget pourra visiter Saint Martin pour inspection et que le gouverneur de Philipsburg en sera informé et coopérera. Je pense qu'après la visite, le baron prendra la bonne décision - laisser l'île être louée aux Hollandais.\nEt maintenant, la nouvelle la plus réconfortante, capitaine ! J'ai quelques choses à vous dire. Premièrement : compte tenu de toutes vos accomplissements militaires, vous êtes élevé au rang de 'Commodore'. Acceptez mes félicitations, Monsieur !";
			link.l1 = "Je sers la France !";
			link.l1.go = "patria_32";
		break;
		
		case "patria_32":
			dialog.text = "Et deuxièmement : le gouverneur de Port-au-Prince nous a envoyé un navire marchand rempli de marchandises pour vous : 500 grands sacs de café et 500 autres sacs de cacao. C'est toute la récolte des plantations à Hispaniola, celles que vous avez protégées des raids espagnols. De plus, une cargaison particulièrement précieuse vous était destinée - 50 unités de bois de gaïac. Je ne pense pas avoir besoin de vous expliquer ce que c'est. Vos biens sont entreposés à la boutique de Capsterville, et vous pouvez aller les récupérer chez le marchand à tout moment.";
			link.l1 = "Merci, Chevalier ! Nouvelles fantastiques !";
			link.l1.go = "patria_33";
		break;
		
		case "patria_33":
			dialog.text = "Et maintenant, pour votre prochaine tâche : le baron Forget reviendra à Saint-Christophe d'un jour à l'autre. Vous l'emmènerez à Saint-Martin et vous assurerez qu'il soit bien gardé. Et, pour ainsi dire, vous observerez de près ce qui se passera à Philipsburg, puis vous me ferez un rapport. Ne quittez pas la ville, capitaine, dès l'arrivée du baron - mon pion vous trouvera et vous informera.";
			link.l1 = "Tout est clair. Puis-je partir ?";
			link.l1.go = "patria_34";
		break;
		
		case "patria_34":
			dialog.text = "Vous pouvez. Quelques jours de repos à terre vous feront du bien et seront utiles.";
			link.l1 = "...";
			link.l1.go = "patria_35";
		break;
		
		case "patria_35":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			AddQuestRecord("Patria", "25");
			pchar.questTemp.Patria = "epizode_5";
			pchar.quest.Patria_CureerBackOver.over = "yes"; // снять таймер
			Items[sti(pchar.EquipedPatentId)].TitulCur = 4; 
        	Items[sti(pchar.EquipedPatentId)].TitulCurNext = 0;
			pchar.quest.Patria_SanMartin_wait.win_condition.l1 = "Timer";
			pchar.quest.Patria_SanMartin_wait.win_condition.l1.date.hour  = 8+rand(2);
			pchar.quest.Patria_SanMartin_wait.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1+rand(1));
			pchar.quest.Patria_SanMartin_wait.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1+rand(1));
			pchar.quest.Patria_SanMartin_wait.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1+rand(1));
			pchar.quest.Patria_SanMartin_wait.win_condition.l2 = "Location_Type";
			pchar.quest.Patria_SanMartin_wait.win_condition.l2.location_type = "town";
			pchar.quest.Patria_SanMartin_wait.function = "Patria_SanMartinBaron";
			pchar.questTemp.Patria.Goods = "true"; // товары-призы
			bQuestDisableMapEnter = true;//закрыть карту
			pchar.GenQuest.MapClosedNoBattle = true;
			ChangeCharacterComplexReputation(pchar, "nobility", 1); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterComplexReputation(pchar, "fame", 1);
		break;
		
		case "patria_36":
			DialogExit(); // переключение на инспектора
			LAi_SetActorType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Noel"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Puancie");
			sld.dialog.currentnode = "patria_37";
			LAi_SetActorType(sld);
			LAi_ActorSetHuberMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
			bDisableCharacterMenu = true;//лоченые интерфейсы
		break;
		
		case "patria_37":
			dialog.text = " ";
			link.l1 = "Oui, Chevalier, de retour déjà ! Vos amis hollandais près de Saint-Martin nous ont accueillis avec le feu des canons du fort et nous ont attaqués avec une escadre de trois navires. Ce n'est que grâce aux compétences du capitaine Charles de Maure et de son équipage que nous avons réussi à nous échapper ! Il semble que Mynheer Peter Stuyvesant ne souhaite pas vraiment voir les envoyés du roi de France à Philipsburg, qu'en pensez-vous, Chevalier ?";
			link.l1.go = "patria_38";
		break;
		
		case "patria_38":
			dialog.text = "Quoi ?! Voici une lettre de Stuyvesant avec sa signature personnelle, où il garantit...";
			link.l1 = "Mais le commandant du fort de Philipsburg a évidemment reçu une lettre différente de Stuyvesant, lui disant de tirer à volonté et de nous tendre une embuscade avec une escadre ! Était-ce un accident, Chevalier ?! Non ! Ils nous attendaient clairement là-bas ! Avec des boulets de canon et de la mitraille !";
			link.l1.go = "patria_39";
		break;
		
		case "patria_39":
			dialog.text = "Baron, je vous en prie... Je m'occuperai de cela. Nous enverrons immédiatement notre cher capitaine, Charles de Maure, à Curaçao encore une fois pour rencontrer Stuyvesant. Le capitaine a une longue expérience dans la gestion des situations délicates... Et maintenant, je demanderai aux serviteurs de préparer un bain et un bon déjeuner pour vous.";
			link.l1 = "...";
			link.l1.go = "patria_40";
		break;
		
		case "patria_40":
			DialogExit();
			LAi_SetActorType(pchar); // 14-add
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			bDisableCharacterMenu = false;//лоченые интерфейсы
			sld = characterFromId("Puancie");
			sld.dialog.currentnode = "patria_41";
			LAi_SetActorType(sld);
			LAi_ActorSetHuberMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "patria_41":
			dialog.text = "Charles, mon ami, tu dois te hâter vers Willemstad. Peut-être que Stuyvesant s'y trouve encore. Sinon - découvre où il est et trouve-le. Lors de la rencontre, parle-lui de l'incident et exige une explication. Je compte sur ton expérience et ton autorité, et je te confie la tâche de mener les négociations. Puis, sans perdre une seule minute, reviens et fais-moi rapport des résultats de la réunion.";
			link.l1 = "La tâche est claire, Chevalier. Je vais préparer le navire et partir immédiatement.";
			link.l1.go = "patria_42";
		break;
		
		case "patria_42":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			LAi_SetHuberType(npchar);
			AddQuestRecord("Patria", "29");
			pchar.questTemp.Patria = "epizode_6";
			Patria_DiplomatBegin();
			ChangeCharacterComplexReputation(pchar, "nobility", 3); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 3);
			ChangeCharacterComplexReputation(pchar, "fame", 3);
		break;
		
		case "patria_43":
			dialog.text = "Je n'arrive pas à y croire...";
			link.l1 = "De plus, sur le chemin du retour, j'ai été attaqué par une escadre de la marine hollandaise. Expliquez-moi, je vous prie, Chevalier, que se passe-t-il ici ?";
			link.l1.go = "patria_44";
		break;
		
		case "patria_44":
			dialog.text = "Mon ami, je suis conscient de votre perspicacité, donc je ne vous cacherai rien. La seule chose que je vous demanderai - ce que vous entendrez ne doit pas quitter cette pièce. Le promettez-vous?";
			link.l1 = "Bien sûr, Chevalier.";
			link.l1.go = "patria_45";
		break;
		
		case "patria_45":
			dialog.text = "Très bien. Je suis certain qu'une grande carrière dans la marine française t'attend. Avec mon aide, bien sûr, tu pourras atteindre le grade de vice-amiral ! Mais je m'égare... Et maintenant, parlons des Néerlandais et de Saint-Martin.\nBien avant ton arrivée à Saint-Martin, de grands gisements de sel y avaient été découverts. Au début, personne ne s'en souciait, mais ensuite les Espagnols de Cuba et d'Hispaniola y ont montré un grand intérêt - pour saler les carcasses de taureaux. Comme tu le comprends sans doute, nous ne pouvons pas commercer directement avec l'Espagne, donc...";
			link.l1 = "...vous avez créé un 'négociateur' sous la forme de la Compagnie néerlandaise des Indes occidentales...";
			link.l1.go = "patria_46";
		break;
		
		case "patria_46":
			dialog.text = "Précisément ! Tu réfléchis vite - et avec précision, Charles ! Et maintenant, sachant qu'il y a une inspection venant de Paris, Stuyvesant a décidé de prendre audacieusement l'affaire du sel en main, comptant sur le fait que nous ne sommes pas empressés de parler à tout le monde de notre accord avec les Espagnols. Mais c'est là qu'il s'est trompé. Personne n'ose prendre quelque chose des mains du Gouverneur Général français sans punition ! Et nous allons lui montrer cela.";
			link.l1 = "Si je comprends bien, le Baron Forget ne peut pas être au courant de cela...";
			link.l1.go = "patria_47";
		break;
		
		case "patria_47":
			dialog.text = "Mon ami, tu as absolument raison, le baron n'a pas besoin de connaître les détails. Il s'est déjà passé assez de choses : une tentative d'attentat contre la vie du représentant du roi de France, l'attaque sur les navires de la mission diplomatique, c'est-à-dire sur toi, et surtout : l'annexion de facto de l'île de Saint-Martin ! Cela suffit pour justifier une action militaire contre les Hollandais.";
			link.l1 = "Guerre?!";
			link.l1.go = "patria_48";
		break;
		
		case "patria_48":
			dialog.text = "Exactement ! Mon ami, la position de vice-amiral n'est pas si loin pour vous, comprenez-vous ? Imaginez-vous aux pourparlers au Louvre en uniforme d'amiral, et Louis XIV lui-même acceptera un tel hôte honorable... Nous devons remettre les Hollandais à leur place ! Stuyvesant regrettera ce qu'il a fait. Êtes-vous d'accord ?";
			link.l1 = "Je suis d'accord, Chevalier. Les Hollandais doivent répondre de leurs actions scandaleuses et ignobles.";
			link.l1.go = "patria_49";
		break;
		
		case "patria_49":
			dialog.text = "Excellent. Je notifierai le baron de notre décision et enverrai aussitôt des courriers aux colonies françaises ! Et vous, mon ami, vous pouvez vous reposer après une longue route, et je vous prie de me rendre visite demain après neuf heures du matin. Je préparerai une mission de combat pour vous.";
			link.l1 = "Très bien, Monsieur. Permettez-moi de m'excuser.";
			link.l1.go = "patria_50";
		break;
		
		case "patria_50":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			LAi_SetHuberType(npchar);
			AddQuestRecord("Patria", "33");
			pchar.questTemp.Patria = "epizode_7";
			Patria_HunterBegin();
			pchar.quest.Patria_DiplomatTimeOver.over = "yes"; // снять таймер
			ChangeCharacterComplexReputation(pchar, "nobility", 1); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterComplexReputation(pchar, "fame", 1);
		break;
		
		case "patria_51":
			dialog.text = "Je ne l'appellerais pas une guerre, c'est plutôt forcer la paix en fait. Et si Stuyvesant change d'avis, cela ne fera que nous rendre plus heureux. C'est pourquoi nous devons maintenant lui montrer qu'en tentant de revendiquer l'île de Saint-Martin, il perdra beaucoup plus qu'il ne gagnera. C'est là que vous intervenez, Charles.";
			link.l1 = "Je vous écoute.";
			link.l1.go = "patria_52";
		break;
		
		case "patria_52":
			dialog.text = "Saint Martin est une base de transbordement pour les navires néerlandais se rendant en Europe. Les navires de la Compagnie séjournent régulièrement dans la baie de Philipsburg. Jusqu'à présent, les eaux étaient assez sûres pour eux. Jusqu'à présent, Capitaine!.. Vous partirez pour les côtes de Saint Martin et vous les patrouillerez en capturant les navires marchands de la Compagnie.\nPour transporter des marchandises précieuses, la Compagnie utilise les Indiamans - des navires robustes, bien armés avec de grands cales. Ceux-ci seront vos cibles. Capturez cinq de ces navires avec leurs cargaisons et rapportez-les comme prises à Casterville. Ensuite, nous continuerons les négociations avec Stuyvesant, et peut-être qu'après avoir compté les pertes, il changera d'avis.";
			link.l1 = "La tâche est claire. Puis-je y aller ?";
			link.l1.go = "patria_53";
		// belamour legendary edition -->
			link.l2 = "Monsieur, je suis contraint de demander, mais pourriez-vous participer au financement de cette opération. Ce seront des mois de navigation, de réparations constantes et de pertes...";
			link.l2.go = "patria_53a";
		break;
		
		case "patria_53a":
			AddMoneyToCharacter(pchar, 20000);
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			dialog.text = "J'ai bien peur que nos réserves soient épuisées, Charles. L'entretien de l'Ecliaton et les combats nous ont déjà coûté la moitié du budget annuel des colonies françaises. Maintenant, c'est tout ce que je peux te donner. Pense aux récompenses futures, Charles ! Un grand avenir t'attend !";
			link.l1 = "Oui, monsieur !";
			link.l1.go = "patria_54";
		break;
		// <-- legendary edtion
		case "patria_53":
			dialog.text = "Va, mon ami, et que la chance accompagne chacun de tes pas.";
			link.l1 = "...";
			link.l1.go = "patria_54";
		break;
		
		case "patria_54":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			AddQuestRecord("Patria", "34");
			pchar.questTemp.Patria = "epizode_7_continue";
			Patria_HunterContinue();
		break;
		
		case "patria_55":
			pchar.questTemp.Patria.Hunter = sti(pchar.questTemp.Patria.Hunter)+1;
			if (sti(pchar.questTemp.Patria.Hunter) > 4) // все собрал
			{
				dialog.text = "Vous avez accompli la tâche, capitaine. Merci pour votre excellent service ! Vous devriez recevoir une part des revenus de la vente des trophées - deux cent mille pesos.";
				link.l1 = "Ravi de l'entendre, Monsieur !";
				link.l1.go = "patria_57";
			}
			else
			{
				dialog.text = "Alors, tu n'as que "+FindRussianQtyString(5-sti(pchar.questTemp.Patria.Hunter))+"Les navires hollandais sont partis pour amener à notre port.";
				link.l1 = "Oui, Chevalier !";
				link.l1.go = "patria_56";
			}
		break;
		
		case "patria_56":
			DialogExit();
			AddQuestRecord("Patria", "35");
			AddQuestUserData("Patria", "sQty", 5-sti(pchar.questTemp.Patria.Hunter));
			DeleteAttribute(pchar, "questTemp.Patria.Hunter.GiveShip");
		break;
		
		// belamour legendary edition -->
		case "patria_57":
			AddMoneyToCharacter(pchar, 200000);
			dialog.text = "Et ce n'est pas tout. J'ai réfléchi un peu l'autre jour... Charles, tu as vraiment fait beaucoup pour la France. L'élimination, en toute franchise, du traître Levasseur, la défense de Saint-Pierre contre l'attaque sournoise de l'Espagne, la défaite réussie du fort de la colonie de San Jose et la réception d'une indemnité des Espagnols en punition pour leur audacieuse ruse... Et après cela, tu as personnellement accompagné le représentant de la couronne française, arrivé d'Europe, et tu as même sauvé sa vie en échappant à une embuscade hollandaise dans les eaux de Philipsburg !";
			link.l1 = "Monsieur, vraiment, vous me faites rougir... Je ne fais que mon devoir.";
			link.l1.go = "patria_57_1";
		break;
		
		case "patria_57_1":
			PlaySound("interface\important_item.wav");
			dialog.text = "Vous êtes modeste comme toujours, mon ami. Et maintenant, lors de l'exécution de la prochaine tâche de forcer la Hollande à la paix, vous ne m'avez encore une fois pas déçu. Vous n'avez pas peur de ce mot - le héros de la nation ! En tant que gouverneur général des colonies françaises dans l'archipel, j'ai avec moi plusieurs copies de la plus haute distinction de France et ... Mais, d'ailleurs, je vous prie de lire ce document.";
			link.l1 = "Pour service exceptionnel rendu à la France... au nom de Sa Majesté le Roi de France... décerner à un officier de marine au service de la France, le capitaine Charles de Maure, fils d'Henri de Montpe... Chevalier, vous plaisantez ?";
			link.l1.go = "patria_57_2";
		break;
		
		case "patria_57_2":
			dialog.text = "Pas du tout, mon ami. J'ai l'honneur de te récompenser comme il se doit en te remettant la plus haute distinction de France - l'Ordre de Saint-Louis ! Chaque citoyen de notre pays doit connaître son héros ! Et Saint-Pierre te doit beaucoup ! Tu mérites cet Ordre, Charles.";
			link.l1 = "Vraiment, je ne sais pas quoi dire... Merci, Gouverneur Général ! Je jure de continuer à servir la France avec fierté et de ne pas reculer face à l'ennemi !";
			link.l1.go = "patria_57_3";
		break;
		
		case "patria_57_3":
			GiveItem2Character(pchar, "talisman9");
			Log_Info("You've received the Order of Saint Louis! You are the hero of the nation!");
			PlaySound("interface\important_item.wav");
			DoQuestCheckDelay("sea_victory", 0.5);
			dialog.text = "Paroles d'un véritable officier ! Je suis vraiment fier de toi, Charles. Maintenant, repose-toi un peu. Tu le mérites. En attendant, je m'occuperai des négociations avec Stuyvesant - peut-être a-t-il déjà compris qu'il est beaucoup plus désavantageux pour lui d'être en inimitié avec nous que d'être ami. Ne quitte pas la ville, j'aurai besoin de toi dans deux jours.";
			link.l1 = "Très bien, Monsieur. J'attendrai de plus amples instructions.";
			link.l1.go = "patria_58";
		break;
		// <-- legendary edtion
		case "patria_58":
			DialogExit();
			AddQuestRecord("Patria", "36");
			pchar.questTemp.Patria = "epizode_7_end";
			pchar.quest.Patria_siege_begin.win_condition.l1 = "Timer";
			pchar.quest.Patria_siege_begin.win_condition.l1.date.hour  = 9.00;
			pchar.quest.Patria_siege_begin.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 2);
			pchar.quest.Patria_siege_begin.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 2);
			pchar.quest.Patria_siege_begin.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 2);
			pchar.quest.Patria_siege_begin.win_condition.l2 = "location";
			pchar.quest.Patria_siege_begin.win_condition.l2.location = "Charles_town";
			pchar.quest.Patria_siege_begin.function = "Patria_SiegeBegin";
			bQuestDisableMapEnter = true;//закрыть карту
			pchar.GenQuest.MapClosedNoBattle = true;
			ChangeCharacterNationReputation(pchar, FRANCE, 15);
			ChangeCharacterComplexReputation(pchar, "nobility", 5); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 5);
			ChangeCharacterComplexReputation(pchar, "fame", 5);
		break;
		
		case "patria_59":
			dialog.text = "Oui. Il semble que Stuyvesant ait commencé à répondre par une action militaire en alliance avec l'Espagne. Une escadre conjointe néerlandaise-espagnole a assiégé Saint-Christophe. Les forts de sentinelle me rapportent chaque heure chacun de leurs mouvements.";
			link.l1 = "Un siège ?";
			link.l1.go = "patria_60";
		break;
		
		case "patria_60":
			dialog.text = "Évidemment. Ils n'ont pas lancé d'assaut direct, et c'est en fait une bonne chose. Nous devons agir rapidement, capitaine, tant que l'ennemi n'a pas encore réussi à bloquer toute l'île.";
			link.l1 = "Que devons-nous faire ?";
			link.l1.go = "patria_61";
		break;
		
		case "patria_61":
			dialog.text = "À Saint-Jones, sur Antigua, est basée l'escadre de la Marine anglaise du Colonel Doily. En ce moment, il rend visite à Sir Jonathan Fox. Vous devez passer par les navires ennemis et atteindre Antigua. Là, vous rencontrerez le Colonel, lui remettrez ma lettre et lui demanderez de l'aide.";
			link.l1 = "Penses-tu que le Colonel acceptera de nous aider ?";
			link.l1.go = "patria_62";
		break;
		
		case "patria_62":
			dialog.text = "Je l'espère. La lettre devrait le convaincre que la récompense pour son aide sera assez conséquente... De plus, nous devons envoyer une lettre au capitaine de l''Eclatant', actuellement près des côtes de la Guadeloupe, il doit se hâter vers Saint-Christophe. La puissance de feu de l''Eclatant' nous aidera considérablement dans la bataille. Comme tu ne peux pas être à deux endroits à la fois, notre courrier lougre rejoindra ton escadron - tu dois le faire passer indemne à travers le cercle d'ennemis, et il partira pour la Guadeloupe, avant que l''Eclatant' ne se dirige vers le Sud...";
			link.l1 = "Je vois. Traversez le siège, escortez le cotre courrier et dépêchez-vous de rejoindre Colonel Doily à Saint-Jones avec votre lettre.";
			link.l1.go = "patria_63";
		break;
		
		case "patria_63":
			dialog.text = "Précisément. Êtes-vous prêt à accepter un autre navire dans votre escadron ?";
			if (GetCompanionQuantity(pchar) > 4)
			{
				link.l1 = "Je me débarrasserai d'un navire et reviendrai vers vous.";
				link.l1.go = "patria_63_1";
			}
			else
			{
				link.l1 = "Oui.";
				link.l1.go = "patria_64";
			}
		break;
		
		case "patria_63_1":
			DialogExit();
			pchar.questTemp.Patria = "epizode_8_wait";
		break;
		
		case "patria_64":
			dialog.text = "Excellent. Prenez la lettre, la chaloupe est prête et n'attend que vos ordres.";
			link.l1 = "Ne perdons pas de temps, Chevalier !";
			link.l1.go = "patria_65";
		break;
		
		case "patria_65":
			DialogExit();
			AddQuestRecord("Patria", "38");
			pchar.questTemp.Patria = "epizode_8_continue";
			GiveItem2Character(pchar, "Reserve_item_01");
			ChangeItemDescribe("Reserve_item_01", "itmdescr_Reserve_item_01_3");
			Patria_SiegeCreateSquadron();
		break;
		
		case "patria_66":
			dialog.text = "Oui-oui, mon ami, je connais toute votre modestie. Vous êtes un véritable officier ! Et vous recevrez une récompense, je vous l'assure ! Je suppose qu'après la rude bataille, vous aurez besoin d'un peu de repos ? Vous avez une semaine entière. Venez dans ma chambre pour discuter dans sept jours - la ville préparera une récompense pour son héros.";
			link.l1 = "Oui, Monsieur. Puis-je y aller ?";
			link.l1.go = "patria_67";
		break;
		
		case "patria_67":
			dialog.text = "Va et repose-toi bien. Plus tard, nous devrons nous occuper des affaires sérieuses - Comme tu peux le voir, une paix avec les Néerlandais est impossible en ce moment. Pour l'instant, le colonel et moi discuterons de quelques questions importantes.";
			link.l1 = "Alors nous nous retrouverons dans une semaine, Chevalier.";
			link.l1.go = "patria_68";
		break;
		
		case "patria_68":
			DialogExit();
			AddQuestRecord("Patria", "45");
			pchar.questTemp.Patria = "epizode_8_end";
			Patria_SiegeEnd();
			ChangeCharacterNationReputation(pchar, FRANCE, 20);
			ChangeCharacterComplexReputation(pchar, "nobility", 10); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 10);
			ChangeCharacterComplexReputation(pchar, "fame", 10);
		break;
		
		case "patria_69":
			pchar.quest.Patria_BastionTimeOver.over = "yes"; //снять таймер
			dialog.text = "Nous avons eu une discussion avec le Colonel Doily et il a accepté de m'aider. L'Angleterre nous aidera dans la guerre contre les Hollandais. Vous et moi devons riposter et rétablir la justice - l'île de Saint-Martin doit revenir à la France. J'assigne cette tâche au meilleur capitaine de la marine - vous, Charles de Maure ! L'ennemi ne s'est pas encore remis de la défaite de leur escadron, nous attaquerons Philipsburg et le prendrons.\nLa bataille ne sera pas facile. D'abord, nous devons détruire le fort, puis briser la défense de la garnison...(chuchotant) Vous devrez également faire une marche forcée à travers la jungle jusqu'au dépôt de sel dont je vous ai parlé, et tuer les ennemis qui y sont campés...";
			link.l1 = "La tâche est assez ardue, Chevalier...";
			link.l1.go = "patria_70";
		break;
		
		case "patria_70":
			dialog.text = "Je vous comprends parfaitement, mon ami. Votre escadre sera renforcée. Les gouverneurs de Basse-Terre et de Saint-Pierre devraient avoir préparé chacun un navire - une frégate - à présent. Vous n'aurez qu'à visiter la Guadeloupe et la Martinique et prendre ces frégates sous votre commandement. Si, bien sûr, vous les voulez vous-même - je n'insisterai pas sur votre choix de navires. Je vous accorde également une subvention sous forme de 20 000 pesos pour acheter des provisions et de l'équipement pour votre vaisseau amiral. Tenez, prenez-les...";
			link.l1 = "Très bien, Monsieur.";
			if (CheckAttribute(pchar, "questTemp.Patria.Ecliaton_Fail")) link.l1.go = "patria_71";
			else link.l1.go = "patria_71_1";
		break;
		
		case "patria_71_1":
			dialog.text = "Aussi, comme d'habitude, le navire 'Eclatant' est sous votre commandement. Il a été réparé et équipé, attendant dans la rade, et après avoir parlé au capitaine, vous pourrez le prendre à tout moment.";
			link.l1 = "Excellent !";
			link.l1.go = "patria_71";
			pchar.questTemp.Patria.Ecliaton_Bastion = "true";
			sld = characterFromId("Ecliaton_Cap");
			sld.dialog.currentnode = "ecliaton_cap_7";
			sld.DeckDialogNode = "ecliaton_cap_7";
		break;
		
		case "patria_71":
			AddMoneyToCharacter(pchar, 20000);
			dialog.text = "Nous ne pouvons pas perdre de temps, capitaine. Mes espions m'ont informé que les Hollandais comprennent le danger pour Saint Martin, et ils ont l'intention de renforcer ses défenses. Mais vous avez encore deux mois. Vous devez terminer la tâche à temps !";
			link.l1 = "Je vais... (chuchotant) Où est le dépôt de sel de Saint-Martin ? Il n'est indiqué sur aucune carte de l'île...";
			link.l1.go = "patria_72";
		break;
		
		case "patria_72":
			dialog.text = "(chuchotant) Lorsque tu assailliras la ville, interroge le vice-roi de Philipsburg, Mynheer Martin Thomas, il te le dira. Ce Hollandais est un lâche et ne te résistera pas, je te le garantis.";
			link.l1 = "Je vois. Puis-je partir ?";
			link.l1.go = "patria_73";
		break;
		
		case "patria_73":
			dialog.text = "Attends une minute, Charles. Tu n'as pas encore reçu ta récompense pour avoir sauvé Saint-Christophe. Prends ces coffres d'or de la part des habitants de la ville, ainsi que notre gratitude la plus sincère, que nulle somme d'argent ne saurait exprimer !";
			link.l1 = "Merci, Monsieur !";
			link.l1.go = "patria_74";
		break;
		
		case "patria_74":
			TakeNItems(pchar, "chest", 10);
			Log_Info("You've received 10 chests of doublons");
			PlaySound("interface\important_item.wav");
			dialog.text = "Maintenant, vous pouvez y aller. Bonne chance, capitaine ! Nous attendons tous votre victoire !";
			link.l1 = "Adieu, Chevalier.";
			link.l1.go = "patria_75";
		break;
		
		case "patria_75":
			DialogExit();
			sTemp = "";
			if (CheckAttribute(pchar, "questTemp.Patria.Ecliaton_Bastion")) sTemp = "The warship 'Eclatant' will also be under my command.";
			AddQuestRecord("Patria", "48");
			AddQuestUserData("Patria", "sText", sTemp);
			pchar.questTemp.Patria = "epizode_9_continue";
			SetFunctionTimerCondition("Patria_BastionSturmTimeOver", 0, 0, 62, false);
			// вернуть Синт-Маартен в норму
			int n = FindIsland("SentMartin");
			Islands[n].reload.l1.radius = 600.0;
			LocatorReloadEnterDisable("Marigo_ExitTown", "reload3", false); // открыть городские ворота
			sld = CharacterFromID("Marigo Fort Commander");
			LAi_SetImmortal(sld, false);
			Character_SetAbordageEnable(sld, true);
			// атрибут квестовой высадки десанта
			pchar.TempPerks.QuestTroopers = true;
		break;
		
		case "patria_76":
			dialog.text = "Qui aurait cru il y a seulement un an que tu serais promu au rang de vice-amiral, mon ami ? Je ne peux qu'imaginer à quel point ton père sera fier quand la nouvelle atteindra la France !";
			link.l1 = "Mon cher père en sera des plus ravi.";
			link.l1.go = "patria_77";
		break;
		
		case "patria_77":
			dialog.text = "Vous avez mérité votre place dans la flotte ! Saint-Martin a été rendu à la France, Stuyvesant a appris une leçon difficile. Ce fut une grande victoire ! Mais nous ne devons pas nous arrêter, nous ne pouvons pas laisser les Hollandais se reposer une minute. Ils seront tenus responsables de leur trahison ! Le colonel Doily est actuellement à Port-Royal, préparant son escadron naval : nous allons briser l'échine de notre ennemi en frappant Curacao. Mais cela viendra plus tard, pour l'instant nous devons faire d'une pierre deux coups, Charles. \nLa Compagnie n'a pas gagné toute sa richesse incommensurable par le commerce. La principale source de revenus des Hollandais dans la région est le travail des esclaves dans leurs plantations. Si tu ne le sais pas, Charles : la Hollande est la plus grande nation possédant et commerçant des esclaves. Les Indiens de l'Est transportant l'‘ivoire noir’ viennent régulièrement à Curacao depuis l'Afrique de l'Ouest. Et il se trouve que je sais quelque chose à ce sujet, malheureusement pour Stuyvesant. \nEn ce moment, deux Indiens de l'Est hollandais naviguent vers les Caraïbes depuis la Guinée. Leurs cales sont pleines de prisonniers noirs. Dans dix jours ou à peu près, la caravane naviguera autour de l'île de Trinité en direction de Curacao. Votre tâche est de trouver la caravane et de capturer ces deux Indiamen et leur cargaison. Vous devez détruire les navires d'escorte et amener les esclaves à notre allié, le colonel Doily, en Jamaïque. C'est très important Charles, de cette façon nous gagnerons sa confiance... J'espère que vous comprenez. \nJe suis désolé de ne pas vous laisser de temps pour vous reposer, mais cette tâche est importante et délicate, et je ne peux la confier qu'à vous.";
			link.l1 = "Le service n'est pas du gâteau, Chevalier. Je le sais mieux que quiconque. Je préparerai mon navire et partirai dès que possible.";
			link.l1.go = "patria_78";
		break;
		
		case "patria_78":
			dialog.text = "Je vous souhaite bon vent et bon voyage, vice-amiral. Et quand vous reviendrez à Saint-Christophe, notre ami commun, Monsieur Noel Forget, aura terminé son inspection de Philipsburg, et je m'assurerai qu'une partie des trophées qu'ils prendront aux Hollandais vous sera attribuée personnellement.";
			link.l1 = "Je vous en serai des plus reconnaissant, Chevalier. Puis-je y aller ?";
			link.l1.go = "patria_79";
		break;
		
		case "patria_79":
			dialog.text = "Va. Bonne chance à toi, mon ami !";
			link.l1 = "...";
			link.l1.go = "patria_80";
		break;
		
		case "patria_80":
			DialogExit();
			Items[sti(pchar.EquipedPatentId)].TitulCur = 5; 
        	Items[sti(pchar.EquipedPatentId)].TitulCurNext = 0;
			pchar.questTemp.Patria = "epizode_10_start";
			AddQuestRecord("Patria", "52");
			Patria_SlaveShipsStart();
			ChangeCharacterNationReputation(pchar, FRANCE, 15);
			ChangeCharacterComplexReputation(pchar, "nobility", 10); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 10);
			ChangeCharacterComplexReputation(pchar, "fame", 10);
		break;
		
		case "patria_81":
			dialog.text = "Excellent ! Vous ne connaissez pas le mot 'impossible', Charles. Je pensais que votre frère était le meilleur officier de marine des Caraïbes, mais il a beaucoup à apprendre de vous, si vous me permettez cette comparaison grossière. Je pense que vous savez déjà qui ira voir notre cher colonel pour participer à l'assaut sur Willemstad.";
			link.l1 = "Absolument pas, Monsieur ! Comment aurais-je pu savoir !";
			link.l1.go = "patria_82";
		break;
		
		case "patria_82":
			dialog.text = "Ah, votre fameux sens de l'humour, mon cher ami ! Ha-hah ! Bien sûr, ce sera vous, vice-amiral. Le plus digne de tous. Êtes-vous prêt ?";
			link.l1 = "Bien sûr, Chevalier. Tout ce dont j'ai besoin, c'est de quelques réparations, de l'équipement - et je suis prêt à partir.";
			if (CheckAttribute(pchar, "questTemp.Patria.Ecliaton_Fail")) link.l1.go = "patria_83";
			else link.l1.go = "patria_83_1";
		break;
		
		case "patria_83_1":
			dialog.text = "N'oublie pas de prendre le 'Eclatant' sous ton commandement. Il a été réparé et équipé, t'attendant aux docks. Le Marquis Hubert Dassier commence déjà à s'impatienter et veut partir à une autre bataille avec toi.";
			link.l1 = "Parfait. Un puissant navire avec des couleuvrines à longue portée est exactement ce dont j'ai besoin pour bombarder le fort.";
			link.l1.go = "patria_83";
			pchar.questTemp.Patria.Ecliaton_Curacao = "true";
			sld = characterFromId("Ecliaton_Cap");
			sld.dialog.currentnode = "ecliaton_cap_11";
			sld.DeckDialogNode = "ecliaton_cap_11";
		break;
		
		case "patria_83":
			dialog.text = "Attends une minute, Charles. Notre ami, le Baron Forget, t’a apporté des nouvelles de Saint-Martin.";
			link.l1 = "...";
			link.l1.go = "patria_84";
		break;
		
		case "patria_84":
			DialogExit();
			sld = characterFromId("Noel");
			sld.dialog.currentnode = "noel_25";
			sld.greeting = "noel_3";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.5);
			ChangeCharacterComplexReputation(pchar, "nobility", 2); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 2);
			ChangeCharacterComplexReputation(pchar, "fame", 2);
		break;
		
		case "patria_85":
			dialog.text = "J'ai des nouvelles pour vous de Paris. Votre nomination au poste de vice-amiral a été signée par le Roi. Vous recevrez les papiers pertinents. Alors, je vous félicite !";
			link.l1 = "Merci, Monsieur ! Heureux de servir la France et le Roi !";
			link.l1.go = "patria_coat";
		break;
		
		case "patria_coat":
			dialog.text = "Et moi, comme toujours, je suis très heureux d'entendre ces mots de votre part. Charles, peut-être aimeriez-vous partager un peu de vin avec moi ? Apporté directement de Paris, vous ne trouverez pas ce genre ici à un jour de chevauchée !";
			link.l1 = "Merci, chevalier, mais je pense que je vais décliner. Je dois retourner au navire plus tard, et il ne conviendrait pas que le vice-amiral de France soit debout ivre sur le gaillard arrière.";
			link.l1.go = "patria_coat_01";
			link.l2 = "Eh bien, pourquoi pas ? Ce n'est pas tous les jours que j'ai l'occasion de partager un verre avec le gouverneur général lui-même !";
			link.l2.go = "patria_coat_02";
		break;
		
		case "patria_coat_01":
			dialog.text = "Eh bien, vous pourriez prendre une pause, pas besoin de retourner au navire immédiatement. Mais c'est votre souhait, et je le respecte. Très bien, passons directement aux affaires.";
			link.l1 = "Je vous écoute attentivement.";
			link.l1.go = "patria_coat_13";
		break;
		
		case "patria_coat_02":
			dialog.text = "Et tous les gouverneurs-généraux n'ont pas la chance d'avoir comme vice-amiral non seulement le meilleur officier de marine, mais aussi un ami avec qui il peut s'asseoir à la même table et boire du vin venu d'une lointaine patrie !";
			link.l1 = "Pour la France !";
			link.l1.go = "patria_coat_03";
			link.l2 = "À votre santé, chevalier !";
			link.l2.go = "patria_coat_04";
		break;
		
		case "patria_coat_03":
			dialog.text = "Et pour le roi !";
			link.l1 = "... ";
			link.l1.go = "patria_coat_05";
		break;
		
		case "patria_coat_04":
			dialog.text = "Et à la vôtre, Charles !";
			link.l1 = "...";
			link.l1.go = "patria_coat_05";
		break;
		
		case "patria_coat_05":
			LAi_Fade("", "");
			if(LAi_GetCharacterHP(pchar) == LAi_GetCharacterMaxHP(pchar))
			pchar.chr_ai.hp = stf(pchar.chr_ai.hp) - 1.0;
			GiveItem2Character(pchar, "potionwine");
			DoCharacterUsedItem(pchar, "potionwine");
			npchar.dialog.currentnode = "patria_coat_06";
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorSetHuberMode(npchar);
			LAi_ActorDialogDelay(npchar, pchar, "", 1.2);
		break;
		
		case "patria_coat_06":
			dialog.text = "Hm, du vin exquis ! N'est-ce pas ?";
			link.l1 = "Oui, tu avais raison. Cela me rappelle le vin qu'ils font chez nous en Gascogne...";
			link.l1.go = "patria_coat_07";
		break;
		
		case "patria_coat_07":
			dialog.text = "Tu es un peu à côté, mon ami - c'est Bordeaux. Néanmoins, je suis sûr que le vin de Gascogne est tout aussi bon !";
			link.l1 = "Je pense que je commence à en oublier le goût... Combien de temps s'est écoulé depuis que j'ai quitté la France ? Un an ? Deux ?";
			link.l1.go = "patria_coat_08";
		break;
		
		case "patria_coat_08":
			dialog.text = "Ah, Charles, on dirait que nous nous sommes rencontrés récemment... et pas dans les circonstances les plus agréables. Pardonnez-moi de mentionner cela, mais si quelqu'un m'avait dit à l'époque que dans la cellule de prison devant moi se tenait mon futur bras droit dans les colonies françaises, j'aurais probablement éclaté de rire.";
			link.l1 = "Inscrutables sont les voies du Seigneur.";
			link.l1.go = "patria_coat_09";
		break;
		
		case "patria_coat_09":
			dialog.text = "Excusez-moi, qu'avez-vous dit ?";
			link.l1 = "C'est du latin, chevalier. Les voies du Seigneur sont impénétrables. Nul ne sait ce que la vie nous réserve.";
			link.l1.go = "patria_coat_10";
		break;
		
		case "patria_coat_10":
			dialog.text = "Tu ne cesses de m'étonner, Charles. Regarde-toi - je n'avais aucune idée que tu pouvais aussi parler latin. Mais d'un autre côté, dans une certaine mesure, nous forgeons notre propre destin, n'est-ce pas ?";
			link.l1 = "Je crois que les deux sont vrais. Seul le Seigneur sait ce qui nous attend. Mais il récompense les persévérants.";
			link.l1.go = "patria_coat_11";
		break;
		
		case "patria_coat_11":
			dialog.text = "Je ne pourrais pas être plus d'accord. Je me souviens, par exemple, de vous avoir remis la commission d'un officier de marine et de vous avoir donné cet uniforme. Et maintenant, devant moi, se tient un vice-amiral, rien de moins !";
			link.l1 = "Le temps file, chevalier.";
			link.l1.go = "patria_coat_12";
		break;
		
		case "patria_coat_12":
			dialog.text = "Indeed... And even on your uniform, I see the cuts left by sabers; some cuts have been stitched, and some are clearly fresh. This needs to be corrected.";
			link.l1 = "Qu'avez-vous en tête, Monsieur le Gouverneur-Général ?";
			link.l1.go = "patria_coat_13";
		break;
		
		case "patria_coat_13":
			dialog.text = "En plus de votre nouvelle position de vice-amiral de la flotte française dans l'archipel des Caraïbes, j'ai un autre cadeau pour vous.";
			link.l1 = "Vous me faites rougir, chevalier. Quel cadeau ?";
			link.l1.go = "patria_coat_14";
		break;
		
		case "patria_coat_14":
			dialog.text = "Je me suis arrangé avec mon tailleur personnel - le meilleur des colonies françaises ! - pour qu'il te couse un uniforme digne de ton rang. Ne t'inquiète pas pour le paiement, j'ai pris soin de tout.";
			link.l1 = "Je suis vraiment reconnaissant ! Je ne manquerai pas de rendre visite à votre tailleur. Où puis-je le trouver ?";
			link.l1.go = "patria_coat_15";
		break;
		
		case "patria_coat_15":
			dialog.text = "Il devrait être au bureau du port en ce moment - un nouveau navire courrier vient d'arriver du continent avec de petits colis. Notre tailleur commande toujours des matériaux difficiles à trouver ici.";
			link.l1 = "Je vais alors me rendre au bureau du port. Merci encore, monsieur !";
			link.l1.go = "patria_86";
		break;
		
		case "patria_86":
			dialog.text = "Et maintenant, je suis sûr que vous aurez besoin de bien vous reposer. Je vous donne un mois, et assurez-vous de bien le passer. Pas de travail, pas de soucis. Laissez tout le travail à vos officiers et reposez-vous bien. Vous pouvez utiliser les chambres dans ma résidence. Les domestiques rendront vos vacances des plus confortables. Nous nous reverrons dans un mois - et j'aurai une affaire délicate à discuter avec vous.";
			link.l1 = "Très bien, Chevalier. Adieu !";
			link.l1.go = "patria_87";
		break;
		
		case "patria_87":
			npchar.dialog.currentnode = "First time";
			LAi_Fade("","");
			LAi_SetHuberType(npchar);
			DialogExit();
			AddQuestRecord("Patria", "65"); // далее коллизия Пуанси-Инспектор-Шарль
			pchar.questTemp.Patria = "epizode_12_start";
			ChangeCharacterNationReputation(pchar, FRANCE, 15);
			SetFunctionLocationCondition("Patria_Tailor", "Charles_PortOffice", false)
			Patria_CondotierStart();
			ChangeCharacterComplexReputation(pchar, "nobility", 15); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 15);
			ChangeCharacterComplexReputation(pchar, "fame", 15);
		break;
		
		case "patria_88":
			dialog.text = "Oui, Charles. Je pensais m'en charger moi-même, mais... hélas, je dois encore une fois faire appel à vos talents. Mais d'abord, je dois vous donner quelque chose : trois cent mille pesos et cinq coffres de doublons. C'est une grande partie de la contribution que Stuyvesant m'a versée selon l'accord. Je suppose que vous avez mérité tout cela, puisque vous avez fait la majeure partie du travail. Acceptez-le. Êtes-vous satisfait, mon ami ?";
			link.l1 = "L'argent n'a jamais fait de mal à personne, Monsieur, j'ai bien appris cette leçon.";
			link.l1.go = "patria_89";
		break;
		
		case "patria_89":
			AddMoneyToCharacter(pchar, 300000); 
			TakeNItems(pchar, "chest", 5);
			dialog.text = "Ah, vice-amiral, j'espère que vous n'êtes pas offensé par ce qui s'est passé dans le passé?.. Vous êtes maintenant un héros de votre nation, le saviez-vous? Comment vous sentez-vous dans cette nouvelle position? Souvenez-vous : de nombreux officiers dignes passent des décennies à gravir les échelons, mais sans une main expérimentée... ils restent au poste de commandant. Mais vous, mon ami, avez une capacité unique à toujours accomplir l'impossible! Et vous avez un ami haut placé, qui est aussi votre protecteur, donc si vous avez des problèmes à l'avenir, je serai là pour vous aider.";
			link.l1 = "Merci pour ces aimables paroles, votre Excellence. J'ai l'impression d'avoir accompli presque tout dans cette région. Avec votre aide, bien sûr. Je suppose que je peux maintenant m'occuper de mes propres affaires en paix ? Je dois penser à ma famille.";
			link.l1.go = "patria_90";
		break;
		
		case "patria_90":
			dialog.text = "Tu veux te marier, Charles ? Ah-ha-ha ! Montre du doigt n'importe quelle belle femme à Paris - et elle sera à toi sur-le-champ ! Mais, hélas, cela devra attendre. J'ai besoin de toi ici, mon ami, du moins pour le moment.";
			link.l1 = "Il semble que la France soit plus forte que jamais dans l'archipel. Une alliance avec les Anglais, une trêve avec la Compagnie. Il ne reste plus de... 'Levasseurs' problématiques. N'est-ce pas ?";
			link.l1.go = "patria_91";
		break;
		
		case "patria_91":
			dialog.text = "Les nations, tout comme les gens, désirent toujours plus, peu importe combien elles ont... Et nous avons en effet un nouveau 'Levasseur', vice-amiral...";
			link.l1 = "Vraiment ? Et qui est-ce ?";
			link.l1.go = "patria_92";
		break;
		
		case "patria_92":
			dialog.text = "C'est notre ancien ami commun, le Baron Noel Forget. Te souviens-tu pourquoi il est venu ici ?";
			link.l1 = "Hmm... Vous avez mentionné quelque chose à propos de la Compagnie de commerce des Indes occidentales. Paris a décidé de créer la même organisation que les Hollandais ?";
			link.l1.go = "patria_93";
		break;
		
		case "patria_93":
			dialog.text = "Précisément. Semblable à la Compagnie hollandaise. Mais en créer une à partir de zéro est très difficile. Vous voyez, Stuyvesant avait des décennies de commerce avec différents continents à son actif, un réseau d'agents développé et une puissante flotte de navires marchands. La France n'a pas cela, et, si vous ne le saviez pas, Charles, le Roi connaît actuellement un grave manque de fonds. Ils souhaitent résoudre la situation financière de la métropole en orientant le commerce ici, mais ils ne comprennent pas ce à quoi nous devrons faire face.\nLa rivalité avec les Anglais et les Hollandais, les ambitions territoriales des Espagnols, la piraterie qui fleurit comme jamais auparavant. Chaque flûte de commerce a besoin d'être escortée par un navire de guerre, sinon elle risque de ne jamais arriver à destination. Et nous n'avons pas une puissante flotte comme celle des Indes orientales des Hollandais, ni les puissants galions comme ceux des Espagnols.";
			link.l1 = "Mais avez-vous expliqué tout cela au baron? A propos des pirates aussi?";
			link.l1.go = "patria_94";
		break;
		
		case "patria_94":
			dialog.text = "Bien sûr que je l'ai fait. Et à propos de l'expulsion des pirates de la Tortue après ta mission pour éliminer Levasseur, que les pirates n'ont pas oubliée et nous en voudront toujours. J'ai organisé des réunions avec diverses personnes qui ont confirmé mes inquiétudes, mais hélas, cela n'a eu aucun effet sur le baron. Il a été envoyé ici par les ministres, et il leur doit... C'est comme ça.";
			link.l1 = "Hm...";
			link.l1.go = "patria_95";
		break;
		
		case "patria_95":
			dialog.text = "Et ne cachons pas le fait qu'une compagnie de commerce dans l'Archipel, sous contrôle direct de Paris... vous et moi, vice-amiral... nous n'en avons pas besoin ici.";
			link.l1 = "Je comprends.";
			link.l1.go = "patria_96";
		break;
		
		case "patria_96":
			dialog.text = "Voyez-vous, mon ami, je suis extrêmement honnête avec vous... Ainsi, j'espérais de tout cœur que Monsieur Forget changerait d'avis sur la création de cette compagnie commerciale, mais... cela ne s'est pas produit. J'ai épuisé toute mon influence sur le baron, et maintenant vous devez entrer dans la partie.";
			link.l1 = "Hmm... Comme avec Levasseur ?";
			link.l1.go = "patria_97";
		break;
		
		case "patria_97":
			dialog.text = "« Oh mon dieu non, pour qui me prends-tu, Charles ? Le baron est une figure influente, un ami du ministre des Finances ! Et puis, l'éliminer physiquement ne servira à rien : un nouveau politicien sera simplement envoyé de Paris. Nous devons détruire l'idée même d'organiser une telle compagnie dès le départ, comprends-tu, Charles ? Pour que le baron retourne en France et rapporte que ce serait financièrement risqué, insensé... »";
			link.l1 = "Avez-vous une idée, Monsieur ?";
			link.l1.go = "patria_98";
		break;
		
		case "patria_98":
			dialog.text = "Hélas, non, Charles. J'ai tout essayé. Je l'ai effrayé avec le manque de navires et d'argent, les Hollandais, les pirates... Aucun effet.";
			link.l1 = "Il semble que nous ayons besoin de quelque chose de plus sérieux que de simples mots. Hm... Des pirates, dites-vous ?";
			link.l1.go = "patria_99";
		break;
		
		case "patria_99":
			dialog.text = "Je vois que tu as une idée, mon ami ? Je n'en doutais pas. Tu as un esprit brillant. Convaincs ce baron, et je veillerai à ce que ton père ait assez d'argent pour remplir toute ta maison de richesses dignes du Louvre. Je te le promets, Charles.";
			link.l1 = "Très bien, Chevalier. La tâche est claire.";
			link.l1.go = "patria_100";
		break;
		
		case "patria_100":
			dialog.text = "Je te le jure, Charles, tu ne le regretteras pas si tu réussis. Tu peux en être sûr. T'ai-je déjà trahi, mon ami ?";
			link.l1 = "Absolument pas, Monsieur. Où puis-je trouver le Baron ?";
			link.l1.go = "patria_101";
		break;
		
		case "patria_101":
			dialog.text = "En ce moment, il est à Port-au-Prince. Il trouve les champs et vallées sans fin d'Hispaniola très charmants, a-t-il dit...";
			link.l1 = "Parfait. Maintenant, permettez-moi de m'excuser.";
			link.l1.go = "patria_102";
		break;
		
		case "patria_102":
			DialogExit();
			AddQuestRecord("Patria", "67");
			pchar.questTemp.Patria = "epizode_12_pirates";
			Patria_CondotierSail();
		break;
		
		case "patria_103":
			dialog.text = "Précisément cela. Le baron m'a tout raconté. Après tout ce qu'il a traversé... Cependant, vous pouvez expliquer les choses clairement, comme personne d'autre, vice-amiral ! Je devrais apprendre cela de vous !";
			link.l1 = "J'ai beaucoup appris de vous, Chevalier.";
			link.l1.go = "patria_104";
		break;
		
		case "patria_104":
			dialog.text = "Mon ami, je te dois une fière chandelle. Je t'assure que ton cher père aura tout ce dont il a besoin ou aura jamais besoin dans sa vie, et ta maison familiale sera la meilleure de la province... et l'une des meilleures de France. De plus, je te paierai 100 000 pesos - j'espère que cela couvrira ta dette avec les pirates...";
			link.l1 = "C'est charmant à entendre, Monsieur !";
			link.l1.go = "patria_105add";
		break;
		
		case "patria_105add":
			AddMoneyToCharacter(pchar, 100000); 
			dialog.text = "J'ai également préparé un présent spécial pour vous. Je suis sûr que vous comprendrez la valeur de cet objet et la sincérité de ma gratitude pour votre service loyal ! Donc, Vice-amiral Charles de Maure, je vous offre mon épée cérémoniale personnelle de l'Ordre de Malte ! Cette arme précieuse ira parfaitement avec votre uniforme, j'imagine ! Si vous décidez de retourner à Paris, le Baron Noel Forget s'est engagé à vous présenter au Roi - vous devriez vous rendre à lui en pleine parade : portant votre uniforme et brandissant cette excellente lame ! Encore plus de glorieuses opportunités de carrière dans la marine française vous attendent !";
			link.l1 = "Cette épée est inégalée dans sa beauté ! Merci, Monsieur, je ne mérite vraiment pas cet honneur...";
			link.l1.go = "patria_105";
		break;
		
		case "patria_105":
			ref itm = ItemsFromID("blade_36");
			itm.picIndex = 16;
			itm.picTexture = "ITEMS_17";
			itm.price = 10000;
			itm.Weight = 3.0;
			itm.lenght = 1.05;
			itm.curve = 1.0;
			itm.Balance = 1.9;
			GiveItem2Character(pchar, "blade_36");
			Log_Info("You've received the Maltese Sword");
			PlaySound("interface\important_item.wav");
			dialog.text = "Tu le fais ! Et pendant que tu es ici, de grands changements t'attendent. De bons changements. Vice-Amiral Charles de Maure, je te nomme Gouverneur de Saint-Martin !";
			link.l1 = "Ah ! Ai-je bien entendu ?";
			link.l1.go = "patria_106";
		break;
		
		case "patria_106":
			ChangeCharacterComplexReputation(pchar, "nobility", 12); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 12);
			ChangeCharacterComplexReputation(pchar, "fame", 12);
			dialog.text = "Oui, mon ami. Vous êtes maintenant le gouverneur de Saint-Martin, que vous avez protégé avec tant de diligence.";
			link.l1 = "Chevalier, permettez-moi de refuser cet honneur. Je ne souhaite pas être lié à cette pauvre île ! Et toutes ces affaires domestiques... Ce n'est pas ce que j'étais destiné à faire !";
			link.l1.go = "patria_107";
		break;
		
		case "patria_107":
			dialog.text = "Je n'accepte pas le refus. Mon ami, n'aie crainte : tu vivras comme avant. Toutes les choses ennuyeuses seront gérées par l'actuel gouverneur intérimaire. Tu seras le gouverneur de facto. Charles, ne comprends-tu pas pourquoi tu as été spécifiquement nommé pour gouverner Saint-Martin ? C'est le moment idéal pour cela, quand personne ne posera de questions. J'ai besoin que l'un de MES hommes soit le gouverneur là-bas, tu vois ce que je veux dire ?";
			link.l1 = "La mine de sel ?";
			link.l1.go = "patria_108";
		break;
		
		case "patria_108":
			dialog.text = "Bien sûr ! Et la deuxième bonne nouvelle : à partir de maintenant, le 15 de chaque mois, vous recevrez une part des bénéfices de la mine, ainsi que du commerce de Doily. Votre revenu passif sera de 100 000 pesos par mois.";
			link.l1 = "Ha ! Je suis ravi de l'entendre ! Merci, Chevalier. Eh bien, si je ne suis pas obligé de rester là, j'accepte le poste de gouverneur. Et que se passera-t-il si je décide de naviguer vers la France ?";
			link.l1.go = "patria_109";
		break;
		
		case "patria_109":
			dialog.text = "Quand tu décideras - tu partiras, et moi, bien que très déçu, je te trouverai un remplaçant. Mais ce n'est pas tout. J'ai ici une lettre de ton père. Jette un œil.";
			link.l1 = "De la part de mon père ? Je suis ravi !.. Très bien, Monsieur, marché conclu. Puis-je partir maintenant ? Je souhaite lire la lettre... Pas de nouvelles tâches pour moi ?";
			link.l1.go = "patria_110";
		break;
		
		case "patria_110":
			dialog.text = "Pas maintenant, Gouverneur, mais si je trouve du travail, je saurai où vous trouver. Bonne chance, Charles!";
			link.l1 = "Et à vous, Chevalier !";
			if (pchar.questTemp.Patria == "epizode_12_baronwin") link.l1.go = "patria_119";
			else link.l1.go = "patria_111";
		break;
		
		case "patria_111":
			DialogExit();
			AddQuestRecord("Patria", "77");
			CloseQuestHeader("Patria");
			DeleteAttribute(pchar, "questTemp.GoldenGirl_Block");	// Разрешаем квест Дороже Золота
			pchar.questTemp.Patria = "end"; // конец линейки
			pchar.questTemp.Patria.Governor = "true"; // Шарль губернатор
			AddQuestRecordInfo("Sharlie_Father_1", "1");
			sld = CharacterFromID(pchar.questTemp.Patria.SpanishID);
			SetCharacterRemovable(sld, true);
		break;
		
		case "patria_112":
			dialog.text = "Bon sang, quel désastre ! Maintenant, nous avons encore plus de problèmes à gérer. Es-tu responsable de cela, Charles ? Dis-moi la vérité. Était-ce un accident ?";
			link.l1 = "Eh bien, quelque chose a mal tourné...";
			link.l1.go = "patria_113";
		break;
		
		case "patria_x112":
			dialog.text = "« Nom de Dieu, quel désastre ! Maintenant, nous avons plus de problèmes à gérer. Le Baron a choisi un bien mauvais endroit pour mourir ! Es-tu sûr que tu ne l'as pas aidé à quitter ce monde ? »";
			link.l1 = "Que dites-vous, Chevalier ?! Bien sûr que non !";
			link.l1.go = "patria_x113";
		break;
		
		case "patria_y112":
			dialog.text = "Nom de Dieu, quel désastre ! Maintenant, nous avons encore plus de problèmes à gérer. Es-tu sûr de ne pas l'avoir aidé à quitter ce monde ?";
			link.l1 = "Que dites-vous, Chevalier ?! Bien sûr que non !";
			link.l1.go = "patria_y113";
		break;
		
		case "patria_x113":
			dialog.text = "D'accord. Eh bien, mon ami, peut-être que tout n'est pas perdu. Une fièvre est une fièvre, n'est-ce pas ? Et jusqu'à ce qu'un nouvel inspecteur du ministère arrive, nous allons nettoyer ce bazar ici et attendre nos invités bien armés... Et maintenant, Charles, nous devons couper tous nos contacts. J'espère que tu comprends pourquoi ?";
			link.l1 = "Bien sûr.";
			link.l1.go = "patria_114";
		break;
		
		case "patria_y113":
			dialog.text = "D'accord. Eh bien, mon ami, peut-être que tout n'est pas perdu. Des batailles dans les Caraïbes, on peut s'y attendre, n'est-ce pas? Et jusqu'à ce qu'un nouvel inspecteur du ministère arrive, nous allons nettoyer ce bazar ici et attendre nos invités bien armés... Et maintenant, Charles, nous devons fermer tous nos contacts. J'espère que tu comprends pourquoi?";
			link.l1 = "Bien sûr.";
			link.l1.go = "patria_114";
		break;
		
		case "patria_113":
			dialog.text = "D'accord. Eh bien, mon ami, peut-être que tout n'est pas perdu. Les pirates sont des pirates, n'est-ce pas ? Et jusqu'à ce qu'un nouvel inspecteur du ministère arrive, nous allons nettoyer ce gâchis ici et attendre nos invités bien armés... Et maintenant, Charles, nous devons clore tous nos contacts. J'espère que tu comprends pourquoi ?";
			link.l1 = "Bien sûr.";
			link.l1.go = "patria_114";
		break;
		
		case "patria_114":
			dialog.text = "En tout cas, mon ami, tu as fait tout ce que tu pouvais. Et c’est mieux que rien. Je suis content que le destin nous ait réunis. Tu peux garder ton poste, et je suis sûr qu'une grande carrière t'attend en France. Et, je pense qu'il est temps pour toi de retourner à Paris. Voici, une lettre de ton père. Prends-la.";
			link.l1 = "Mon père? C'est des plus bienvenus!.. Très bien, Monsieur, je comprends. Pas de contacts, discrétion totale, et dès que possible - aller à Paris. Puis-je partir maintenant? Je souhaite lire la lettre...";
			link.l1.go = "patria_115";
		break;
		
		case "patria_115":
			dialog.text = "Va, Charles. Bonne chance !";
			link.l1 = "Et à vous, Chevalier !";
			link.l1.go = "patria_116";
		break;
		
		case "patria_116":
			DialogExit();
			AddQuestRecord("Patria", "78");
			CloseQuestHeader("Patria");
			DeleteAttribute(pchar, "questTemp.GoldenGirl_Block");	// Разрешаем квест Дороже Золота
			pchar.questTemp.Patria = "end"; // конец линейки
			AddQuestRecordInfo("Sharlie_Father_1", "1");
			sld = CharacterFromID(pchar.questTemp.Patria.SpanishID);
			SetCharacterRemovable(sld, true);
		break;
		
		case "patria_117":
			dialog.text = "Précisément. Vous savez expliquer les choses comme personne d'autre, vice-amiral ! Je devrais apprendre cela de vous !!";
			link.l1 = "J'ai beaucoup appris de vous, Chevalier.";
			link.l1.go = "patria_118";
		break;
		
		case "patria_118":
			dialog.text = "Mon ami, je vous dois une fière chandelle. Je vous assure que votre cher père aura tout ce dont il a besoin ou pourrait jamais avoir besoin dans sa vie, et votre maison familiale sera la meilleure de la province... et une des meilleures en France. De plus, je vous payerai 100 000 pesos - j'espère que cela couvrira vos frais de voyage et vous permettra de prendre un repos bien mérité.";
			link.l1 = "Voilà qui est agréable à entendre, Monsieur !";
			link.l1.go = "patria_105add";
		break;
		
		case "patria_119":
			DialogExit();
			AddQuestRecord("Patria", "87");
			pchar.questTemp.Patria = "europe";
			pchar.questTemp.Patria.Governor = "true"; // Шарль губернатор
			AddQuestRecordInfo("Sharlie_Father_1", "1");
			SetFunctionTimerCondition("Patria_EuropeTime", 0, 0, 175+rand(10), false); // таймер
		break;
		
		case "patria_prison":
			dialog.text = "Comment as-tu pu, Charles ! Comment as-tu pu me faire ça ?!";
			link.l1 = "Hem...";
			link.l1.go = "patria_prison_1";
		break;
		
		case "patria_prison_1":
			dialog.text = "Je sais que c'était toi ! C'est toi qui as fait ça ! Ne le nie pas ! Sans ton aide, le Baron Forget n'aurait jamais obtenu ni les rapports du directeur de la mine, ni l'emplacement de la mine, ni même les documents de Peter Stuyvesant. Ton nom n'a pas été mentionné là-bas, mais laisse-moi te dire, je sais avec certitude : c'était toi. Pourquoi, Charles ?.. Réponds-moi simplement... Pourquoi ? Michel ? Un million de pesos ? Levasseur ? Ou peut-être la position de Gouverneur Général ?";
			// belamour legendary edition -->
			link.l1 = "Te souviens-tu de notre première rencontre, Chevalier ? Comment tu m'as remis à ma place ? Comment tu m'as extorqué un million de pesos ? Je souhaitais juste qu'un jour nous puissions échanger nos rôles. Je n'ai plus rien à te dire.";
			link.l1.go = "patria_prison_2";
			link.l2 = "Pour Levasseur. Une dette d'un million, je peux encore comprendre. J'ai travaillé, j'ai tué, j'ai gagné, j'ai volé, mais je vous ai compensé pour tous les dégâts. Et cela ne vous suffisait pas. Vous, Chevalier, m'avez envoyé en mission-suicide contre la couronne pour renforcer encore plus votre pouvoir personnel ! Votre trahison exigeait une réponse. Et vous l'avez eue !";
			link.l2.go = "patria_prison_2";
			link.l3 = "Ambition, Chevalier. Dans ce monde nouveau et étrange, j'avais déjà presque tout accompli. Le poste de gouverneur général me semblait un objectif digne. J'ai beaucoup appris de vous. Adieu !";
			link.l3.go = "patria_prison_2";
			link.l4 = "Je ne sais pas moi-même, pour être honnête. Peut-être parce que je suis impressionné par le baron et son service fidèle à notre pays ? Quoi qu'il en soit, vous aurez maintenant suffisamment de temps pour réfléchir à cette question pour moi. Adieu !";
			link.l4.go = "patria_prison_2";
			// <-- legendary edition
		break;
		
		case "patria_prison_2":
			DialogExit();
			chrDisableReloadToLocation = false;
			bDisableFastReload = true;//закрыть переход
			LAi_SetActorType(npchar);
			SetFunctionTimerCondition("Patria_EuropePuancieClear", 0, 0, 5, false); // таймер
			pchar.quest.Patria_Europe_final.win_condition.l1 = "location";
			pchar.quest.Patria_Europe_final.win_condition.l1.location = "Charles_town";
			pchar.quest.Patria_Europe_final.function = "Patria_EuropeFinal";
		break;
		
		case "patria_patentfail":
			DialogExit();
			pchar.questTemp.Patria = "fail";
			CloseQuestHeader("Patria");
			DeleteAttribute(pchar, "questTemp.GoldenGirl_Block");	// Разрешаем квест Дороже Золота
			// убрать Эклятон, если есть
			if (CheckAttribute(pchar, "questTemp.Patria.Ecliaton"))
			{
				sld = characterFromId("Ecliaton_Cap");
				RemoveCharacterCompanion(pchar, sld);
				sld.lifeday = 0;
				DeleteAttribute(pchar, "questTemp.Patria.Ecliaton");
			}
		break;
		
		// Rebbebion, квест "Путеводная звезда"
		case "PZ_1":
			SetTimerCondition("PZ_NormanBackToStreets", 0, 0, 1, false);	//Вовзращаем Акулу или Тиракса в Шарптаун
			// ставим сразу прерывание, чтобы потом по тысячу раз не копировать
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
			{
				if (CheckAttribute(pchar, "questTemp.PZ.LongwayMayfang") || CheckAttribute(pchar, "questTemp.PZ.LongwayTorero") || CheckAttribute(pchar, "questTemp.PZ.LongwayElCasador"))
				{
					PChar.quest.PZ_AfterPoincyLongwayDialog.win_condition.l1 = "location";
					PChar.quest.PZ_AfterPoincyLongwayDialog.win_condition.l1.location = "Charles_town";
					PChar.quest.PZ_AfterPoincyLongwayDialog.win_condition = "PZ_AfterPoincyLongwayDialog";
				}
			}
			
			if (!CheckAttribute(pchar, "questTemp.PZ_ChangShinMertva")) 
			{
				dialog.text = "Bon de vous voir, Charles. J'ai entendu parler de vos exploits. Travail brillant !";
				if (CheckAttribute(pchar, "questTemp.PZ_LevasserPlenen"))
				{
					link.l1 = "Ce n'est pas tout, Votre Excellence.";
					link.l1.go = "PZ_2";
				}
				else
				{
					link.l1 = "Puis-je obtenir un ordre écrit de votre part pour que mon frère soit libéré sur-le-champ ?";
					link.l1.go = "serve";
				}
			}
			else 
			{
				dialog.text = "Greetings, Charles. Come in; I've already been informed.";
				link.l1 = "Informé ? Il doit y avoir une erreur, Votre Excellence. Je suis venu annoncer la réussite de votre mission, mais je vois que vous n'êtes pas dans votre meilleur état d'esprit.";
				link.l1.go = "PZ_PoincyAngry1";
			}
			DelLandQuestMark(npchar);
			DeleteAttribute(pchar, "questTemp.PZ_LongwayNelzyaOtdatArube");
		break;
					
		case "PZ_2":
			dialog.text = "Vraiment? Que voulez-vous dire, Capitaine?";
			link.l1 = "J'ai réussi à capturer Levasseur vivant et à l'amener à vous. Dès que nous aurons terminé, je donnerai l'ordre de le faire venir à vous.";
			link.l1.go = "PZ_3";
		break;
		
		case "PZ_3":
			dialog.text = "Je n'aurais jamais pensé qu'une telle chose était possible ! Vraiment, un travail brillant, Charles ! Je doute que même votre illustre frère aurait pu faire mieux. Votre père serait fier de vous, mon ami.";
			link.l1 = "Merci pour vos aimables paroles, Monsieur Philippe.";
			link.l1.go = "exit";
			npchar.greeting = "";
			AddDialogExitQuest("PZ_LevasserVGostyahUPuansie");
		break;
		
		case "PZ_5":
			dialog.text = "Très bien, Charles. Je suis satisfait de vous.";
			link.l1 = "Puis-je obtenir un ordre écrit de vous pour que mon frère soit libéré de détention immédiatement ?";
			link.l1.go = "serve";
			LAi_SetHuberType(npchar);
		break;
		
		case "PZ_PoincyAngry1":
			dialog.text = "Peut-être aurais-je dû considérer que tu n'es pas ton frère - pas un militaire, pas un agent secret, et pas encore expérimenté dans les opérations délicates. Tu n'aurais pas dû te battre ouvertement avec des soldats dans les rues de Tortuga. Il y aura des enquêtes, et sur moi aussi. De la part de gens sérieux, comme tu le comprends.";
			link.l1 = "Je vous demande pardon, Chevalier. Comme vous le savez, Levasseur n'aurait pas cédé sans se battre.";
			link.l1.go = "PZ_PoincyAngry2";
		break;
		
		case "PZ_PoincyAngry2":
			dialog.text = "Vrai, mais... peu importe. Pas mal pour une première opération. Je rapporterai qu'il a attaqué l'Auditeur Royal et son escorte lors d'une inspection officielle.";
			if (CheckAttribute(pchar, "questTemp.PZ_LevasserPlenen"))
			{
				link.l1 = "Votre Excellence, si cela vous aide, je peux vous amener Levasseur. Mes hommes et moi avons eu la chance de le capturer dans un endroit isolé après que ses sbires aient tenté de nous arrêter dans les rues.";
				link.l1.go = "PZ_PoincyAngry3";
			}
			else
			{
				link.l1 = "Puis-je obtenir un ordre écrit de votre part pour que mon frère soit libéré immédiatement ?";
				link.l1.go = "serve";
			}
		break;
				
		case "PZ_PoincyAngry3":
			dialog.text = "Qu'as-tu dit, Charles ? Dis-le encore.";
			link.l1 = "François Levasseur est dans ma cale en ce moment, prêt à être remis à vous, Monsieur Philippe.";
			link.l1.go = "PZ_PoincyAngry4";
		break;
		
		case "PZ_PoincyAngry4":
			dialog.text = "Oubliez tout ce que j'ai dit auparavant. J'ai certainement réagi de manière excessive. Travail brillant. Je ne suis pas sûr que même votre illustre frère aurait pu réussir cela.";
			link.l1 = "Merci, Chevalier.";
			link.l1.go = "PZ_PoincyAngry5";
		break;
		
		case "PZ_PoincyAngry5":
			dialog.text = "Vous avez beaucoup de promesses, mon ami. J'aimerais que vos talents soient utilisés plus souvent pour le bien du pays. Mais s'il vous plaît, essayez d'être plus... discret à l'avenir. Notre travail nécessite généralement une approche délicate. Ah oui, et une chose de plus.";
			link.l1 = "Oui, Votre Seigneurie ?";
			link.l1.go = "exit";
			npchar.greeting = "";
			AddDialogExitQuest("PZ_LevasserVGostyahUPuansie");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
