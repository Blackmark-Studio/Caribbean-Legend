// Брат Шарля, Мишель де Монпе, он же Дичозо, он же воплощение Кукулькана, он же главный злодей
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (pchar.questTemp.Sharlie == "takeknife")
			{
				dialog.text = "Bienvenue, Charles le Voyageur ! J'ai entendu parler de comment tu as vaincu ces pirates sur la côte Est de la Martinique. Maintenant, je suis absolument certain que je ne me suis pas trompé à ton sujet, frère.";
				link.l1 = "Fils de pute m'ont pris dans un piège. Mais ils nous ont sous-estimés. Mon navigateur, mon équipage et moi avons pris le dessus. Bien que je doive admettre, cher frère, au début... les choses semblaient sombres.";
				link.l1.go = "trial";//промежуточная стадия
				break;
			}
			if (pchar.questTemp.Sharlie == "gambitstage")
			{
				bool bFMQM = CheckAttribute(pchar,"questTemp.FMQM") && pchar.questTemp.FMQM != "fail" && pchar.questTemp.FMQM != "end";
				bool bFMQN = CheckAttribute(pchar,"questTemp.FMQN") && pchar.questTemp.FMQN != "fail" && pchar.questTemp.FMQN != "end";
				bool bFMQT = CheckAttribute(pchar,"questTemp.FMQT") && pchar.questTemp.FMQT != "fail" && pchar.questTemp.FMQT != "end";
				bool bFMQP = CheckAttribute(pchar,"questTemp.FMQP") && pchar.questTemp.FMQP != "fail" && pchar.questTemp.FMQP != "end";
				bool bFMQG = CheckAttribute(pchar,"questTemp.FMQG") && pchar.questTemp.FMQG != "fail" && pchar.questTemp.FMQG != "end";
				bool bFMQL = CheckAttribute(pchar,"questTemp.FMQL") && pchar.questTemp.FMQL != "fail" && pchar.questTemp.FMQL != "end";
				if(bFMQM || bFMQN || bFMQT || bFMQP || bFMQG || bFMQL)
				{
					if (sti(pchar.rank) < 12)
					{
						dialog.text = "Salutations, frère ! J'apprécie ton zèle sincère pour me tirer d'ici, mais tu n'es pas encore prêt pour l'étape suivante. Mon plan requiert un capitaine expérimenté. Continue d'explorer les Caraïbes, gagne des prix et apprends ! Quand tu seras prêt, nous continuerons.";
						link.l1 = "Eh bien, quoi que tu dises, frère. C'est toi qui es assis ici, pas moi.";
						link.l1.go = "exit";
					} 
					else 
					{
						dialog.text = "Ravi de te voir, mon frère. N'oublie pas tes engagements envers les autres. Dès que tu seras libre, je t'attendrai - j'ai des idées pour notre prochaine étape !";
						link.l1 = "D'accord, frère. Je prendrai du temps pour mes engagements, mais je reviendrai bientôt !";
						link.l1.go = "exit";
					}
					break;
				}
				if (sti(pchar.rank) < 12)
				{
					Log_info("Level 12 is required");
					dialog.text = "Charles le Navigateur ! J'ai entendu parler de tes aventures ! Tu es presque prêt pour la prochaine étape de mon plan. Reviens dès que tu auras acquis un peu plus d'expérience.";
					if (sti(pchar.rank) < 7)
					{
						dialog.text = "Salutations, frère ! J'apprécie ton zèle sincère pour me tirer d'ici, mais tu n'es pas encore prêt pour la prochaine étape. Mon plan requiert un capitaine expérimenté. Continue d'explorer les Caraïbes, gagne des prix et apprends ! Quand tu seras prêt, nous continuerons.";
					} 
					else 
					{
						if (sti(pchar.rank) < 10)
						{
							dialog.text = "Heureux de te voir, frère ! J'ai entendu dire que tu fais des progrès ! Mais tu n'es pas encore prêt pour la prochaine étape de mon plan. Continue ce que tu faisais et reviens me voir quand tu seras prêt.";
						}
					}
					link.l1 = "Eh bien, quoi que tu dises, frère. C'est toi qui es assis ici, pas moi.";
					link.l1.go = "exit";
					if(sti(pchar.rank) > 8)
					{
						link.l2 = "Je ne crois pas, frère. Peut-être que tu t'es déjà installé dans cette cage, mais je n'ai pas l'intention d'y rester longtemps - notre père ne peut pas attendre éternellement. Crache le morceau.";
						link.l2.go = "gambitA";
					}
					break;
				}
				else
				{
					dialog.text = "Bonjour, Charles. Ta vue réchauffe mon cœur : tu changes certainement en bien.";
					link.l1 = "Vraiment ? Et comment expliques-tu cela ?";
					link.l1.go = "gambit";//переход на Гамбит
					break;
				}
			}
			if (!CheckAttribute(npchar, "quest.givelink_saga") && CheckAttribute(pchar, "questTemp.HWIC.Detector"))//признак, что Гамбит пройден или провален
			{
				dialog.text = "Je vois. Je vois que tu as des nouvelles pour moi, Charles ! Eh bien, que se passe-t-il ? J'espère que ce n'est rien de sinistre ?";
				link.l1 = "J'ai suivi le conseil que tu m'as donné la dernière fois...";
				link.l1.go = "saga";//переход на Сагу
				DelLandQuestMark(npchar);
				DelMapQuestMarkCity("FortFrance");
				break;
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Fail1") && CheckAttribute(pchar, "questTemp.HWIC.Fail2") && CheckAttribute(pchar, "questTemp.HWIC.Fail3"))//признак, что Гамбит провален по всем трем вариантам
			{
				dialog.text = "Enfin, te voilà... Quelles nouvelles, cher frère ?";
				link.l1 = "J'ai suivi le conseil que tu m'as donné la dernière fois...";
				link.l1.go = "gambit_fale";
				DelLandQuestMark(npchar);
				DelMapQuestMarkCity("FortFrance");
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "mishelle")//Сага готова к старту
			{
				dialog.text = "Ravi de te voir, Charles ! As-tu vu le Chevalier de Poincy ? Comment s'est passée ta rencontre ?";
				link.l1 = "Oui, cher frère. Nous nous sommes rencontrés. Et j'ai deux nouvelles pour toi, bonnes et mauvaises. Je vais commencer par la bonne. Je me suis occupé de ta dette envers de Poincy. La mauvaise nouvelle, c'est qu'il ne te libérera pas tant que je n'aurai pas rempli ta promesse de régler les choses avec quelque hérétique...";
				link.l1.go = "saga_5";
				DelLandQuestMark(npchar);
				DelMapQuestMarkCity("FortFrance");
				break;
			}
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "fail" && !CheckAttribute(pchar, "questTemp.Mtraxx.CharleePrince")) // пиратская линейка провалена или пройдена не полностью
			{
				dialog.text = "Comment t'en es-tu sorti à La Vega, frère ?";
				link.l1 = "Rien de quoi se vanter, vraiment. Tyrex est un personnage haut en couleur mais ses manières de faire des affaires ne me conviennent tout simplement pas.";
				link.l1.go = "saga_17e";
				DelLandQuestMark(npchar);
				DelMapQuestMarkCity("FortFrance");
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "fail" && CheckAttribute(pchar, "questTemp.Mtraxx.CharleePrince")) // пиратская линейка провалена или пройдена не полностью, но дальше 4 квеста
			{
				dialog.text = "Comment t'es-tu débrouillé à La Vega, frère ? J'ai entendu des rumeurs et pour être tout à fait honnête, elles ne me rendent pas heureux... Charlie Prince.";
				link.l1 = "Je pense savoir de quoi parlaient ces rumeurs. Mais tout cela appartient au passé. Je ne travaille plus avec Tyrex, ce boulot est devenu trop sale à mon goût.";
				link.l1.go = "saga_17f";
				DelLandQuestMark(npchar);
				DelMapQuestMarkCity("FortFrance");
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "full_complete") // пиратская линейка пройдена полностью
			{
				dialog.text = "Eh bien, salutations... Corsaire Charlie Prince. Dis-moi, Charles, comment as-tu pu tomber si bas? Je n'arrive pas à y croire. Mon frère qui faisait une grimace dégoûtée quand j'ai mentionné une fois le pillage d'un galion marchand espagnol est maintenant l'un des pirates les plus recherchés et dangereux de cette région! Même moi, enfoncé jusqu'au cou dans la merde, je rougis chaque fois que ton infamie parvient à mes oreilles. J'ai maudit le jour où je t'ai envoyé à La Vega. Quelle honte! Un noble français a rejoint les pirates et est devenu le pire d'entre eux en si peu de temps! Et maintenant, frère? Cherches-tu un poste de baron pirate?";
				link.l1 = "Non. J'en ai fini avec la piraterie une fois pour toutes.";
				link.l1.go = "saga_17g";
				DelLandQuestMark(npchar);
				DelMapQuestMarkCity("FortFrance");
				break;
			}
			
			dialog.text = "Quoi d'autre, Charles? Je pense que nous avons tout discuté. Le temps, c'est de l'argent, cher frère - hâte-toi!";
			link.l1 = "Oui, oui, j'y vais...";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("Fortfrance");
		break;
		
		case "Mishelle_prisoner":
			DelLandQuestMark(npchar);
			DelLandQuestMark(characterFromId("Maltie_officer"));
			QuestPointerDelLoc("FortFrance_Dungeon", "quest", "quest1");
			SetCurrentTime(13, 30);
			dialog.text = "Charles!.. Heureux de te voir, frère ! Je comprends, bien sûr, que ce sera difficile à croire pour toi, mais je suis sacrément content que tu sois là...";
			link.l1 = "Ha ! Regardez-le ! Il est content ! Alors que tu te pavanes avec ton 'Ordre', Charles était la honte de la famille, un artiste minable, vivant de l'argent des courtisanes, et un 'chevalier' de cour, hein ? Mais maintenant que tes propres camarades t'ont cloué derrière les barreaux, tu es 'heureux comme un poisson dans l'eau' de voir ton frère bon à rien !";
			link.l1.go = "Mishelle_prisoner_1";			
		break;
		
		case "Mishelle_prisoner_1":
			dialog.text = "Charles, tu...";
			link.l1 = "Je n'en ai pas encore fini ! Pourquoi n'as-tu rien rapporté de ta situation en France ?! As-tu été privé du droit de correspondre ?! Notre père est devenu complètement malade d'inquiétude à ton sujet ! Et il m'a demandé de découvrir au moins quelque chose sur ton sort !..";
			link.l1.go = "Mishelle_prisoner_1a";
		break;
		
		case "Mishelle_prisoner_1a":
			dialog.text = "Charles, en quels mots dirais-je à notre père ce qui m'est arrivé ? Que lui écrirais-je ? Non, frère, aussi difficile que cela soit, il vaut mieux que notre père ne sache encore rien. Et cela serait inutile de t'écrire - tu es toujours à des adresses différentes à Paris... Comment m'as-tu trouvé ?..";
			link.l1 = "A la supplication de mon père, je suis allé à Malte. Là-bas, j'ai reçu des informations de votre ami le chevalier de La Brignais. Il m'a écrit au sujet de vos problèmes et que vous êtes probablement quelque part en Martinique. Puis je suis retourné en France et j'ai rendu visite à mon père. Et après tout cela, je suis allé dans ce trou infernal sous une chaleur accablante où les moustiques vous mâchouillent littéralement jusqu'à la mort...";
			link.l1.go = "Mishelle_prisoner_1b";
		break;
		
		case "Mishelle_prisoner_1b":
			dialog.text = "Avez-vous raconté tout cela à votre père ?";
			link.l1 = "Non. Et le chevalier de La Brignais n'a pas répondu à ses lettres, craignant les tristes conséquences... Le père ne sait toujours rien de ton sort. J'ai décidé de te trouver et de découvrir la vérité. Pour que tu saches, je suis venu à la Martinique non pas pour toi, mais pour notre pauvre père !";
			link.l1.go = "Mishelle_prisoner_2";
		break;
		
		case "Mishelle_prisoner_2":
			dialog.text = "Vraiment ? Charles, depuis quand te soucies-tu de ta famille ? Soyons honnêtes, frère, tout le monde à Paris sait qui est ton père. Tu portes peut-être le nom de famille de Maure, mais tu ne veux pas que le nom de Monpe soit déshonoré.\nCar dans ce cas, tu ne pourrais pas utiliser ta lignée pour raconter à tout le monde des histoires fictives sur tes exploits héroïques, n'est-ce pas ? Les portes des meilleures maisons de Paris te seront fermées et elles ne te laisseront pas approcher à moins d'un mile du Louvre.\nCrois-tu vraiment que tes courtisanes et maîtresses, dont tu cocus les maris pendant qu'ils se battent sur le champ de bataille pour notre patrie, seront heureuses de tromper leurs seigneurs et maîtres avec le frère d'un criminel d'État comme moi ?\nJe suppose que tu es arrivé ici directement du lit de quelque jeune fille mariée, ai-je raison ? Charles, qu'est-ce qui ne va pas avec ton visage ? Ai-je touché un nerf ?";
			link.l1 = "Toi... Toi !..";
			link.l1.go = "Mishelle_prisoner_3";
		break;
		
		case "Mishelle_prisoner_3":
			dialog.text = "D'accord, frère. Nous avons échangé des piques, cela suffit. Je reconnais que je ne suis pas parfait. Mais toi non plus, tu n'es pas un ange. Charles, ce n'est vraiment pas le moment de se quereller. Nous avons tous les deux le même objectif, sauver l'honneur et la dignité de la famille Monper... peu importe nos motivations. Frère, pour une fois dans nos vies, remplaçons l'animosité par la paix. Marché conclu ?";
			link.l1 = "Essayons... Mais peux-tu m'expliquer de quoi on t'accuse ?";
			link.l1.go = "Mishelle_prisoner_4";
		break;
		
		case "Mishelle_prisoner_4":
			dialog.text = "Officiellement, cela semble concerner la dépense de l'argent de la Société. En réalité, c'est bien plus profond.";
			link.l1 = "Alors, tu as détourné l'argent de ton organisation ? Eh bien, eh bien...";
			link.l1.go = "Mishelle_prisoner_5";
		break;
		
		case "Mishelle_prisoner_5":
			dialog.text = "Je t'ai dit que c'étaient les accusations officielles. Je n'ai pas pris un seul louis d'or. Voici comment cela s'est passé... tu vois, je ne peux pas tout t'expliquer en détail tant que je suis derrière les barreaux. Je n'ai pas le droit moral de divulguer les secrets de notre Société.";
			link.l1 = "S'il te plaît, essaie d'expliquer, cher frère. J'ai le droit de savoir, ne crois-tu pas?";
			link.l1.go = "Mishelle_prisoner_6";
		break;
		
		case "Mishelle_prisoner_6":
			dialog.text = "D'accord. J'avais reçu de l'argent pour une opération très dangereuse et délicate qui était censée changer l'équilibre politique dans les Caraïbes. J'agissais sous les ordres directs de Philippe de Poincy, qui est le gouverneur général des colonies françaises. Mais l'opération a échoué malgré tous mes efforts. \nDe Poincy a eu une crise de colère parce que tous ses plans audacieux sont tombés à l'eau. Il a personnellement signé l'ordre de mon arrestation et s'est assuré qu'il soit exécuté. Il est ensuite venu ici et a déclaré qu'il m'accuserait de malversation et de trahison contre l'Ordre, si mes proches ou moi ne remboursions pas l'argent dépensé pour l'opération.";
			link.l1 = "Voilà une belle affaire. Où est-il, cet argent que, si j'ai bien compris, notre famille doit payer pour tes frasques?";
			link.l1.go = "Mishelle_prisoner_7";
		break;
		
		case "Mishelle_prisoner_7":
			dialog.text = "Il a été dépensé pour préparer l'opération. Pots-de-vin, organisation d'expéditions, achat de toutes sortes de marchandises et d'équipements. J'ai eu des dépenses assez conséquentes. Comme je l'ai dit - je n'ai pas pris un sou.";
			link.l1 = "Et quelle est la somme qui est demandée?";
			link.l1.go = "Mishelle_prisoner_8";
		break;
		
		case "Mishelle_prisoner_8":
			dialog.text = "Un million.";
			link.l1 = "Merde ! Tu plaisantes, non ?!";
			link.l1.go = "Mishelle_prisoner_9";
		break;
		
		case "Mishelle_prisoner_9":
			dialog.text = "Ai-je l'air de quelqu'un d'humeur à plaisanter ? Non, cher frère, c'est la triste vérité. Nous allons devoir livrer un million de pesos à de Poincy.";
			link.l1 = "Mais bon sang! Notre famille n'a pas du tout ce genre d'argent! Nous ne pourrions pas réunir autant en vingt ans!";
			link.l1.go = "Mishelle_prisoner_10";
		break;
		
		case "Mishelle_prisoner_10":
			dialog.text = "Si je n'étais pas derrière les barreaux et restreint par mes obligations envers la Société, je pourrais le faire en six mois à un an, un an et demi au maximum. Charles, c'est le Nouveau Monde. Tout est différent ici. Un homme motivé et ambitieux peut se faire une fortune ici sans y consacrer toute sa vie comme en Europe.";
			link.l1 = "Un million en six mois ?! Es-tu fou ? Si tu en es si sûr, pourquoi ne le dis-tu pas à ton de Poincy ? Laisse-le te libérer. Fais de ton mieux...";
			link.l1.go = "Mishelle_prisoner_11";
		break;
		
		case "Mishelle_prisoner_11":
			dialog.text = "Oh, ne raconte pas de bêtises, Charles ! Il n'y a pas moyen que Poincy me libère de cette cellule. Si c'était si simple, je ne te demanderais pas ton aide.";
			link.l1 = "Donc c'est moi qui dois trouver l'argent pour ta liberté?!";
			link.l1.go = "Mishelle_prisoner_12";
		break;
		
		case "Mishelle_prisoner_12":
			dialog.text = "Pas seulement ma liberté. Ou as-tu oublié? Reprenons notre conversation sur les palais, les bals et le sexe avec des putains nobles? Oui, Charles, c'est toi qui dois le faire. Si, bien sûr, tu veux continuer à mener ta vie frivole à Paris comme avant. Ça te plairait, n'est-ce pas, frère?";
			link.l1 = "Mais bon sang, où diable suis-je censé le trouver ? Tu connais quelques vieux bois par ici où poussent des louis d'or à la place des feuilles ?";
			link.l1.go = "Mishelle_prisoner_13";
		break;
		
		case "Mishelle_prisoner_13":
			dialog.text = "Le Nouveau Monde entier représente un bosquet d'arbres à argent, et pourtant les gens sont trop paresseux pour lever leurs têtes stupides et tendre la main vers les branches. Ne t'inquiète pas, Charles, tu t'en sortiras très bien. Je te connais depuis notre enfance et je ne perdrais jamais mon temps à convaincre notre père de t'envoyer ici si je te pensais stupide ou paresseux.\nMalgré tes défauts que j'ai mentionnés auparavant, tu es courageux, ambitieux, intelligent, tu as la langue bien pendue et tu sais manier la rapière, ce qui est une compétence extrêmement importante à connaître ici...";
			link.l1 = "Merci beaucoup. Mon cher frère a-t-il vraiment daigné me faire des éloges ? Et moi qui pensais n'être qu'un pitoyable artiste, un courtisan...";
			link.l1.go = "Mishelle_prisoner_14";
		break;
		
		case "Mishelle_prisoner_14":
			dialog.text = "Arrête tes conneries. Avons-nous un accord, ou pas ?";
			link.l1 = "Désolé, frère. C'est sorti tout seul. Je ne suis juste pas habitué à entendre ces mots de ta part. C'est comme une catin de rue prêchant sur le salut d'une âme.";
			link.l1.go = "Mishelle_prisoner_15";
		break;
		
		case "Mishelle_prisoner_15":
			dialog.text = "Allons-y, frère. Comme je l'ai dit, tu as tout ce qu'il faut pour réussir ici. Non seulement cela, mais tu n'es pas seul. Je t'aiderai avec des conseils sur ce qu'il faut faire et comment le faire correctement. Écoute-moi et nous triompherons. Crois-moi, tu ne trouveras personne pour remplacer mon expérience. Es-tu prêt à arrêter de jacasser et enfin aller droit au but ?";
			link.l1 = "Oui, il semble que je vais rester ici un moment... Très bien. Je suis tout ouïe, Michel.";
			link.l1.go = "Mishelle_prisoner_16";
		break;
		
		case "Mishelle_prisoner_16":
			dialog.text = "Oui, frère, tu vas rester ici un moment. C'est bien que tu puisses le voir maintenant. Donc, si une courtisane attend ton retour à Paris, je te conseille de l'oublier. Mais ne t'en fais pas, les filles locales ont leurs propres charmes. Cependant, elles aiment les vrais hommes, forts et audacieux, même rudes. Alors si tu comptes te taper une fille de la colonie, ne compte pas sur la poésie, les discussions sur la peinture ou les balades sous la lune. Elles n'approuveront pas.";
			link.l1 = "D'accord, frère. As-tu été frappé par un coup de vent de fanfaronnade ? Allons droit au but. Je suis prêt à écouter tes conseils, mais pas tes viles insinuations.";
			link.l1.go = "Mishelle_prisoner_17";
		break;
		
		case "Mishelle_prisoner_17":
			dialog.text = "Splendide. Pour que vous ayez la moindre chance de succès, il vous faut posséder un navire. Les Caraïbes sont un archipel. Vous savez cela, n'est-ce pas ? La vie est étroitement liée à la mer. Un homme avec son propre navire a un horizon infini de possibilités de gains.";
			link.l1 = "Mais je ne suis pas marin !";
			link.l1.go = "Mishelle_prisoner_18";
		break;
		
		case "Mishelle_prisoner_18":
			dialog.text = "Alors, il est temps d'en devenir un. De toute façon, tu n'as pas d'autre choix. Tu n'as pas pensé à devenir employé de bureau portuaire ou à t'inscrire à la garnison, n'est-ce pas ? Non ? Alors tu seras capitaine.";
			link.l1 = "Quel retournement de situation dans ma carrière ! Et où vais-je donc trouver un navire ?";
			link.l1.go = "Mishelle_prisoner_19";
		break;
		
		case "Mishelle_prisoner_19":
			dialog.text = "Il y a un excellent lougre qui attend à notre chantier naval local. Il n'est pas grand, mais c'est un bateau très confortable, parfait pour faire les premiers pas dans l'arène d'un marin. Ce lougre a été construit juste pour moi. J'ai versé un acompte de cinq mille pesos pour le navire avec l'aide de mes amis. Rendez-vous chez le constructeur naval et dites-lui que Michel de Monper vous envoie. Il comprendra pourquoi vous êtes là.";
			link.l1 = "Le navire ne coûte que cinq mille ? C'est un peu bizarre...";
			link.l1.go = "Mishelle_prisoner_20";
		break;
		
		case "Mishelle_prisoner_20":
			dialog.text = "Frère, m'écoutes-tu ? Cinq mille, c'est juste pour l'acompte. Le prix du lougre est d'environ vingt mille pesos. Donc tu devras gagner le reste de l'argent toi-même. En plus de cela, il te faudra de l'argent pour engager un équipage et un navigateur.";
			link.l1 = "Superbe! Et comment l'obtiendrai-je?";
			link.l1.go = "Mishelle_prisoner_21";
		break;
		
		case "Mishelle_prisoner_21":
			dialog.text = "Aucune grande surprise là-dedans. Gagne-le. Comment autrement ? L'argent se trouve derrière chaque buisson ici, tu dois juste savoir où regarder et ne pas craindre l'adversité. Promène-toi dans les différents établissements par ici. Parle avec les gens du coin. Tu es sûr de trouver du travail. Mais fais attention, il y a beaucoup plus d'escrocs que de gens honnêtes. Si tu n'es pas un homme honnête, tu peux essayer de voler quelque chose de précieux dans les maisons.";
			link.l1 = "Mais nous sommes de la noblesse, n'est-ce pas ?";
			link.l1.go = "Mishelle_prisoner_22";
		break;
		
		case "Mishelle_prisoner_22":
			dialog.text = "Les titres ne valent rien ici. Travaille, bats-toi, vole comme tout le monde. Une fois que tu as acheté un bateau, engage un équipage. Tu ne pourras pas diriger le bateau toi-même au début, donc tu auras besoin d'un navigateur. Tu peux parler de tout ça avec le propriétaire de la taverne, il t'aidera. Et assure-toi de ne pas te perdre, bien sûr. Quand tu prends la mer, mets le cap directement sur la Guadeloupe...";
			link.l1 = "Qu'est-ce que c'est? Une ville?";
			link.l1.go = "Mishelle_prisoner_23";
		break;
		
		case "Mishelle_prisoner_23":
			dialog.text = "C'est une île à presque deux jours d'ici. Essaye d'acquérir une carte de l'archipel dès que possible et apprends-la comme le 'Notre Père' pour ne pas passer pour un idiot devant tout le monde qui sait faire la différence entre une ville et une île. Tu devras naviguer beaucoup autour de l'archipel, alors prépare-toi à l'avance.";
			link.l1 = "Hm. Très bien. Alors, que dois-je faire sur cette, euh... Guadeloupe ?";
			link.l1.go = "Mishelle_prisoner_24";
		break;
		
		case "Mishelle_prisoner_24":
			dialog.text = "Trouve un homme là-bas du nom de 'Fadey'. Il a sa propre maison non loin de la jetée. Dis-lui que tu me connais et demande-lui de rembourser sa dette - il m'a bien plumé dans une partie de cartes. L'argent que tu recevras t'aidera à prendre ton envol. Utilise-le pour te lancer.";
			link.l1 = "Que veux-tu dire par 'mettre les choses en marche' ?";
			link.l1.go = "Mishelle_prisoner_25";
		break;
		
		case "Mishelle_prisoner_25":
			dialog.text = "Je veux dire, utilise cet argent pour en gagner encore plus, et ainsi de suite. En commerçant par exemple. Nous reviendrons à cette conversation plus tard. Maintenant, tu devrais t'occuper du navire, naviguer vers la Guadeloupe, trouver ce gros Moscovite et récupérer la dette de lui.\nPas littéralement, bien sûr, Fadey est un homme très respecté en Guadeloupe et un ami du gouverneur local lui-même. Donc, il n'y a pas de raison de se quereller. Au contraire, essaie de te lier d'amitié avec lui. Reviens me voir dès que tu auras l'argent. Compris, frère ?";
			link.l1 = "Je vois. Oh, pourquoi...Qu'ai-je fait pour mériter ce châtiment...";
			link.l1.go = "Mishelle_prisoner_26";
		break;
		
		case "Mishelle_prisoner_26":
			dialog.text = "Ne t'afflige pas, Charles. Accepte-le comme un mal inévitable, ou... comme une bonne chose. Plus tard, tu remercieras le destin que ta vie ait pris ce genre de tournant. Toi, frère, tu as enfin l'occasion de faire quelque chose pour prouver que tu es un véritable homme. Tu pourrais même devenir un être humain respectable...";
			link.l1 = "Ce foutu truc encore ?";
			link.l1.go = "Mishelle_prisoner_27";
			link.l2 = "Frère, je n'ai pas le temps pour ça. Je veux passer la partie ennuyeuse et partir immédiatement en haute mer. Plus tôt j'aurai un navire, plus tôt tu seras sorti de ce trou à rats. Ou préfères-tu rester ici plus longtemps ?";
			link.l2.go = "Mishelle_prisoner_29"; // Addon 2016-1 Jason пиратская линейка 1
		break;
		
		case "Mishelle_prisoner_27":
			dialog.text = "Non, non. Ne le prends pas mal... Très bien Charles, ne perds pas de temps. Tu sais ce que tu dois faire. Je t'attendrai venant de Guadeloupe en tant que capitaine de ton propre navire avec l'argent de Fadey. Bonne chance, frère. Je compte sur toi.";
			link.l1 = "Je vais essayer de ne pas te décevoir. D'accord, Michel. À la prochaine fois !";
			link.l1.go = "Mishelle_prisoner_28";
		break;
		
		case "Mishelle_prisoner_28":
			DialogExit();
			pchar.questTemp.Sharlie = "ship";//флаг на старт мини-квестов для сбора денег
			//LocatorReloadEnterDisable("Fortfrance_town", "reload5_back", false);//откроем верфь
			LocatorReloadEnterDisable("Fortfrance_town", "reload4_back", true);// таверна закр
			if(!bHardcoreGame) LocatorReloadEnterDisable("Fortfrance_town", "reload7_back", true);// ЦЕРКОВЬ закр
			LocatorReloadEnterDisable("Fortfrance_town", "reload8_back", true);// ростовщик закр
			LocatorReloadEnterDisable("Fortfrance_town", "reload9_back", true);// бордель закр
			LocatorReloadEnterDisable("Fortfrance_town", "reload91", true);// бордель закр
			LocatorReloadEnterDisable("Fortfrance_town", "reload_jail", true);// тюрьма закр
			bDisableFastReload = false;//open быстрый переход
			SaveCurrentQuestDateParam("questTemp.Sharlie_ship");//запомним дату
			NextDiag.CurrentNode = "First time";
			AddQuestRecord("Sharlie", "5");
			//Sharlie_CreateGigoloMan();//мини-квесты на бордель и на джунгли
			AddLandQuestMark(characterFromId("FortFrance_tavernkeeper"), "questmarkmain");
			AddLandQuestMark(characterFromId("FortFrance_trader"), "questmarkmain");
			AddLandQuestMark(characterFromId("FortFrance_PortMan"), "questmarkmain");
			if(CheckAttribute(pchar, "questTemp.Sharlie.Pardon"))
			{
				AddLandQuestMark(characterFromId("FortFrance_Mayor"), "questmarkmain");
				QuestPointerToLoc("Fortfrance_town", "reload", "reload3_back");
			}
			QuestPointerToLoc("Fortfrance_town", "reload", "reload6_back");
			/*pchar.quest.CreateGigoloMan.win_condition.l1 = "Hour";
			pchar.quest.CreateGigoloMan.win_condition.l1.start.hour = 17.00;
			pchar.quest.CreateGigoloMan.win_condition.l1.finish.hour = 18.00;
			pchar.quest.CreateGigoloMan.function = "Sharlie_CreateGigoloMan";*/
			/* pchar.quest.SharlieremoveLocks.win_condition.l1 = "HardHour";
			pchar.quest.SharlieremoveLocks.win_condition.l1.hour = 23;
			pchar.quest.SharlieremoveLocks.win_condition.l2 = "location";
			pchar.quest.SharlieremoveLocks.win_condition.l2.location = "FortFrance_Town";
			pchar.quest.SharlieremoveLocks.function = "Sharlie_removeLocks"; */
			//устанавливаем прерывание на джунгли
			pchar.quest.Jungle_jew.win_condition.l1 = "location";
			pchar.quest.Jungle_jew.win_condition.l1.location = "Martinique_jungle_01";
			pchar.quest.Jungle_jew.function = "Junglejew_CreateIndians";
			
			ref location = &Locations[FindLocation(pchar.location)];
			location.first_meeting = true;
			npchar.greeting = "mishelle_3";
			// на гида
			if (GetCharacterIndex("Guide") != -1)
			{
				pchar.quest.Guide_next.win_condition.l1 = "location";
				pchar.quest.Guide_next.win_condition.l1.location = "Fortfrance_town";
				pchar.quest.Guide_next.win_condition = "Guide_next";
			}
		break;
		
		case "Mishelle_prisoner_29": // Addon 2016-1 Jason пиратская линейка 1
			dialog.text = "Heh ! Cette 'partie ennuyeuse' pourrait bien te sauver la vie un jour... Peu importe. Il y a un moyen facile d'obtenir l'argent tout de suite.\nVa à l'église locale et parle à l'Abbé Benoit. C'est un vieil ami de notre père. Explique-lui la situation, tombe à genoux et supplie-le de te prêter assez de pièces pour acheter un navire.";
			link.l1 = "Beaucoup mieux maintenant ! En route vers l'abbé.";
			link.l1.go = "Mishelle_prisoner_31";
			link.l2 = "Veux-tu que je commence par augmenter encore davantage tes dettes ? Tu me prends pour un idiot, frère ? Je vois bien que tu ne peux pas m'aider du tout dans cette affaire. Tout cela repose donc sur moi.";
			link.l2.go = "Mishelle_prisoner_30";
		break;
		
		case "Mishelle_prisoner_30":
			dialog.text = "Wow ! On dirait que je ne me suis pas trompé sur toi, frère. J'attends avec impatience ton retour de la Guadeloupe en tant que capitaine de ton propre navire avec l'argent de Fadey. Bon vent !";
			link.l1 = "À plus tard. Amuse-toi bien ici.";
			link.l1.go = "Mishelle_prisoner_28";
		break;
		
		case "Mishelle_prisoner_31":
			DialogExit();
			AddLandQuestMark(characterFromId("Benua"), "questmarkmain");
			pchar.questTemp.Sharlie = "ship_fast"; // ускоренный старт
			pchar.questTemp.Sharlie.FastStart = "true";
			LocatorReloadEnterDisable("Fortfrance_town", "reload5_back", false);//откроем верфь
			SaveCurrentQuestDateParam("questTemp.Sharlie_ship");//запомним дату
			NextDiag.CurrentNode = "First time";
			AddQuestRecord("Sharlie", "5-1");
			location = &Locations[FindLocation(pchar.location)];
			location.first_meeting = true;
			npchar.greeting = "mishelle_3";
			// на гида
			if (GetCharacterIndex("Guide") != -1)
			{
				pchar.quest.Guide_next.win_condition.l1 = "location";
				pchar.quest.Guide_next.win_condition.l1.location = "Fortfrance_town";
				pchar.quest.Guide_next.win_condition = "Guide_next";
			}
			//DeleteAttribute(pchar, "GenQuest.CannotWait");
			Sharlie_removeLocks("");
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "First time";
		break;
		
		case "trial":
			DelLandQuestMark(npchar);
			dialog.text = "Essayes-tu de dire que c'était effrayant ? Ne te crispe pas, frère. Tout va bien. Je ne me sentais pas vraiment comme un héros lors de ma première bataille maritime non plus. Balivernes. Dans un mois ou deux, de telles rencontres te sembleront aussi banales qu'un jour ordinaire... As-tu rendu visite à Fadey ?";
			link.l1 = "J'ai... Mais avec ce genre de succès... Pourquoi me suis-je même embêté ?";
			link.l1.go = "trial_1";
		break;
		
		case "trial_1":
			dialog.text = "Hm. Pourquoi cela ?";
			link.l1 = "Parce qu'il est sur la paille. Il a été volé récemment et il a ses propres problèmes d'argent. Il m'a offert un poignard de sa collection à la place. Il a dit qu'il a de la valeur et que sa valeur dépasse celle de toute la dette. Alors, je l'ai pris...";
			link.l1.go = "trial_2";
		break;
		
		case "trial_2":
			dialog.text = "Fadey ? Sur les rochers ? Problèmes d'argent ? Ha-ha-ha ! Tu m'as bien fait rire, cher frère ! Ce sacré Moscovite t'a percé à jour et t'a reconnu comme un novice dès le début et... ah ce salaud ! Montre-moi la dague que le vieux t'a donnée en échange de sa dette.";
			if (CheckCharacterItem(pchar, "knife_01"))
			{
				link.l1 = "Voilà...";
				link.l1.go = "trial_3";
				PlaySound("interface\important_item.wav");
			}
			else
			{
				link.l1 = "Je ne l'ai pas sur moi. A l'œil nu, c'est juste une dague ordinaire. Fadey m'a dit qu'elle est enchantée par un chaman indien et qu'on l'appelle la Griffe du Chef.";
				link.l1.go = "trial_4";
			}
		break;
		
		case "trial_3":
			PlaySound("interface\important_item.wav");
			dialog.text = "Hm. Eh bien, voyons voir... Dieu jugera cet ours grassouillet. Des bric-à-brac comme ça, Charles, tu pourrais en acheter dans n'importe quelle boutique locale. Il t'a bien eu, profitant de ton manque d'expérience... Tiens, reprends ce morceau d'acier. Garde-le comme souvenir. Tu pourras le suspendre au-dessus de ton lit dans ta cabine.";
			link.l1 = "Salaud ! Oh, peu importe... Je retournerai le voir en Guadeloupe et secouer ce foutu chaudron !";
			link.l1.go = "trial_5";
		break;
		
		case "trial_4":
			dialog.text = "Enchanté par un chaman ? Griffe du chef ? Ouais... tout est clair. Dieu jugera cet ours grassouillet. Des trucs comme ça, Charles, tu pourrais en acheter dans n'importe quelle boutique locale. Il t'a filé un beau bobard, profitant de ton manque d'expérience... Il a essayé de me raconter des contes de fées et je l'ai remis à sa place. Alors, tu peux accrocher cette griffe dans ta cabine au-dessus de ton lit comme souvenir... Si tu ne l'as pas encore jetée à la poubelle.";
			link.l1 = "Enfoiré ! Oh, qu'importe... Je retournerai le voir en Guadeloupe et secouer ce sale brûlot !";
			link.l1.go = "trial_5";
		break;
		
		case "trial_5":
			dialog.text = "Calme-toi, cher frère, détends-toi. Pas besoin de ça à moins que tu ne veuilles passer quelques mois dans une cellule de prison à Basse-Terre. As-tu oublié ce que je t'ai dit ? Ce gros ours est un ami de Claude Francois de Lyon, le gouverneur de la Guadeloupe. Dès que je quitte cet endroit, je vais aller lui parler... cœur à cœur. Il ne va nulle part.";
			link.l1 = "D'accord. Tu ferais mieux de t'occuper de lui... On dirait que je vais me retrouver sans les fonds de départ promis ?";
			link.l1.go = "trial_6";
		break;
		
		case "trial_6":
			dialog.text = "On dirait bien, Charles. Mais garde la tête haute. Celui qui a un navire et une tête sur les épaules ne peut pas se tromper aux Caraïbes. Et tu as les deux, n'est-ce pas ?";
			link.l1 = "Que sous-entendez-vous ? J'ai fait une bêtise avec ce poignard, alors que devrais-je...";
			link.l1.go = "trial_7";
		break;
		
		case "trial_7":
			dialog.text = "Calme-toi, cher frère ! Pourquoi es-tu si nerveux tout d'un coup ? Reste calme, tu vivras plus longtemps. Je n'insinue rien. Je n'avais même pas ces pensées !";
			link.l1 = "Désolé, Michel. C'est juste que je suis un peu... enfin, essaie de me comprendre aussi !";
			link.l1.go = "trial_8";
		break;
		
		case "trial_8":
			dialog.text = "Je comprends. Et je veux vraiment vous aider ! Alors écoutez bien. Vous devez acquérir un peu d'expérience et au moins économiser un peu d'argent avant de vous lancer dans des affaires plus sérieuses. Se précipiter dans des aventures sans la préparation nécessaire est un pur suicide. Je ne veux pas que cet endroit vous écrase déjà.";
			link.l1 = "Très inspirant. Sur quelles sortes d'aventures t'étends-tu, Michel ? J'ai perdu le fil de tes divagations pour une raison quelconque.";
			link.l1.go = "trial_9";
		break;
		
		case "trial_9":
			dialog.text = "Frère, permets-moi de te rappeler que je, ou plus précisément, nous, devons à de Poincy un million de pesos. Penses-tu vraiment que tu peux les gagner honnêtement ? Bien sûr, tu peux commercer pour cette somme, c'est possible si la chance te sourit, mais le commerce aux Caraïbes n'est pas non plus une activité paisible. Les aventures te trouveront d'elles-mêmes même si tu ne veux pas y participer, la question est - seras-tu prêt pour elles quand le moment viendra ? Il vaut mieux frapper le premier. Si vis pacem, para bellum, Charles...";
			link.l1 = "Encore avec tes mots raffinés ? Parle français, je te prie...";
			link.l1.go = "trial_10";
		break;
		
		case "trial_10":
			dialog.text = "C'est du latin, cher frère. J'ai dit, 'Si tu veux la paix, prépare la guerre'. Prends cette phrase comme une mentalité de leadership vers l'action. Tu peux l'écrire dans ton journal de bord et la relire chaque matin après la prière. Il y a beaucoup de choses que tu dois apprendre et encore beaucoup à maîtriser...";
			link.l1 = "D'accord, ça suffit. Je me suis lassé de vos articles scientifiques. Allons droit au but.";
			link.l1.go = "trial_11";
		break;
		
		case "trial_11":
			dialog.text = "Je suis précis, c'est juste que tu ne suis pas encore. Très bien. D'abord, tu dois te familiariser avec l'archipel et t'habituer à ta nouvelle vie en tant que capitaine d'un navire. Tu devras travailler dur pour assurer ton bien-être et un salaire pour ton équipage. Il y a beaucoup de façons de gagner de l'argent.\nPrendre des cargaisons et des passagers à bord est le plus simple. Les marchands dans les magasins peuvent te donner des contrats de fret et les passagers te solliciteront eux-mêmes dans les rues. Tu devrais aussi envisager de vérifier les bureaux du port, avoir un lougre ou tout autre navire rapide te permettra de gagner de bons revenus en tant que courrier.\nLes maîtres de port te fourniront des contrats de fret très rentables une fois que tu auras un navire plus grand. Parle avec les gens, ne te vante pas de ta lignée, sois amical et tout ira bien. Visite les gouverneurs des colonies, ils offrent souvent du travail bien payé.\nTu peux essayer le commerce, mais dans ce cas, tu devrais engager un intendant décent. Fais attention en mer, évite les escadrons militaires espagnols et les navires de guerre. Si tu rencontres un seul marchand espagnol ou un convoi non protégé, tu peux essayer de les capturer.";
			link.l1 = "Quoi ?! Michel, ai-je perdu l'ouïe ? Suggères-tu que je prenne la vie d'un pirate ? Toi, la fierté de la Société, un serviteur de Dieu et de la Trinité, proposes-tu un tel mode de vie à moi ?";
			link.l1.go = "trial_12";
		break;
		
		case "trial_12":
			dialog.text = "Oh, Charles... Je te conseille de te débarrasser de ta fastidiosité une fois pour toutes, elle n'est pas appréciée ici. Et à propos de l'Ordre... ne sois pas naïf, frère. Peut-être qu'en Europe le Louvre et l'Escorial sont en paix d'une certaine manière, mais ici, c'est la guerre. Tout raider espagnol n'hésitera pas à piller ton navire et à te pendre ainsi que ton équipage pour sécher à la vergue.\nPar conséquent, personne ne te blâmera pour avoir pillé un navire marchand d'une nation hostile, je te l'assure. Et avec une lettre de marque, tu obtiendras même le soutien officiel des autorités...";
			link.l1 = "Je commence à comprendre les principes de ta vie. Tout comme je comprends les méthodes par lesquelles tu pourrais apparemment 'gagner' un million en six mois.";
			link.l1.go = "trial_13";
		break;
		
		case "trial_13":
			dialog.text = "Et tu devras utiliser ces méthodes, Charles. Après tout, elles sont soutenues par les autorités en place, ouvertement ou à huis clos. Même si tu te contentes de commercer, un jour tu seras contraint de combattre des pirates ou des pillards espagnols, car pour eux, tu es le butin.\nIl est dans ton intérêt de oublier tes anciennes conceptions de la vie. Fais-moi confiance, frère, tu peux faire beaucoup de choses sans perdre la face, mais aussi gagner la faveur des autorités et l'amour du peuple.";
			link.l1 = "Tu ne cesses de me surprendre, Michel. Maintenant, tu me dis de devenir pirate. Quelle est la prochaine étape ?";
			link.l1.go = "trial_14";
		break;
		
		case "trial_14":
			dialog.text = "Ne dramatise pas trop, Charles. C'est vraiment simple : chasser ou être chassé. C'est toute la philosophie. Je préfère la première et j'aimerais que tu suives mon exemple. Et je ne te dis pas de devenir un pirate, mais de t'engager dans une action militaire contre une nation hostile et seulement quand il y a une bonne raison pour cela.";
			link.l1 = "Un bénéfice, tu veux dire ?";
			link.l1.go = "trial_15";
		break;
		
		// Rebbebion, небольшое изменение диалога
		case "trial_15":
			dialog.text = "Tu vois, tu comprends, frère. Mais assez de mots. Il est temps de te mettre à l'épreuve. Viens me voir seulement quand tu te sens prêt. Gagne un peu d'argent honnête, trouve-toi un meilleur navire, découvre l'archipel et améliore tes compétences.\nMais sache-le, si tu passes les prochains mois dans les tavernes et les bordels sans rien apprendre d'utile... ne reviens même pas. Sommes-nous clairs, Charles ?";
			link.l1 = "Ne t'inquiète pas. Je ne suis pas venu ici pour me divertir... Qu'est-ce qui vient après ça ?";
			link.l1.go = "trial_16";
		break;
		
		case "trial_16":
			dialog.text = "Plus tard, je te dirai quoi faire après cela. J'ai déjà élaboré un plan. Un brillant avenir t'attend, Charles, si tu suis précisément mes conseils et recommandations.";
			link.l1 = "Je préférerais mon modeste passé à un avenir si brillant et grand...";
			link.l1.go = "trial_17";
		break;
		
		case "trial_17":
			dialog.text = "Crois-moi, frère, tu riras de ton passé sans valeur et remercieras le destin de t'en avoir sauvé. Sois optimiste et positif. Tu adoreras cette vie. Tu verras. \nOh, une chose de plus : rends visite à notre ami commun Fadey et demande-lui de te trouver un travail. L'ours a de bonnes connexions, je suis sûr qu'il te trouvera quelque chose. Ne traîne pas ou tu pourrais manquer une opportunité. Et s'il te plaît, ne me déçois pas.";
			link.l1 = "Encore des leçons de morale... Seigneur, quand tout cela prendra-t-il fin ? Très bien, Michel... Puis-je reprendre ma route ?";
			link.l1.go = "trial_18";
		break;
		
		case "trial_18":
			dialog.text = "Attends. Quelques conseils tactiques supplémentaires. Si tu te mets à dos une nation et deviens hors-la-loi, rends-toi à l'église locale et parle à l'abbé Benoît. Dis-lui que je t'ai envoyé. Il a des connexions à la fois dans la société papiste et calviniste et m'a beaucoup aidé dans de telles affaires plus d'une fois. Mais sache que cela n'est ni facile ni bon marché, alors essaie d'éviter de te faire des ennemis.\nAttends, encore une chose ! Nous sommes nobles, mais il est insensé d'avoir une aversion pour l'artisanat de nos propres mains, surtout ici. Tu peux fabriquer beaucoup d'objets utiles, à condition d'avoir les outils et les composants nécessaires... Dis-moi, frère, comment charges-tu l'une de tes pistolets ?";
			link.l1 = "Hm. Comme d'habitude, une balle et une charnière de poudre à canon.";
			link.l1.go = "trial_19";
		break;
		
		case "trial_19":
			dialog.text = "Ha ! Je ne m'attendais pas à entendre autre chose.";
			link.l1 = "Connais-tu une autre manière, cher frère ?";
			link.l1.go = "trial_20";
		break;
		
		case "trial_20":
			dialog.text = "Bien sûr. Mais peu le font en raison de l'ignorance et de la vieille paresse. En passant quelques heures de votre temps, vous pourriez fabriquer des cartouches en papier avec de la poudre à canon et des balles. Les utiliser réduit de moitié le temps de rechargement du pistolet. Impressionné ?";
			link.l1 = "Hm. Je suppose que oui. C'est intéressant.";
			link.l1.go = "trial_21";
		break;
		
		case "trial_21":
			pchar.alchemy.known = 1;
			AddQuestRecordInfo("Recipe", "cartridge");
			SetAlchemyRecipeKnown("cartridge");
			dialog.text = "Prends ces instructions de fabrication pour des coquilles en papier, étudie-les pendant ton temps libre, et ne sois pas trop paresseux pour appliquer tes nouvelles connaissances. Attends, frère. N'oublie pas de passer voir notre cher gouverneur.";
			link.l1 = "Y a-t-il une occasion ?";
			link.l1.go = "trial_22";
		break;
		
		// Rebbebion, намёк на "Травлю крысы"
		case "trial_22":
			dialog.text = "C'est toujours bon de rester en contact avec les gouverneurs, surtout s'ils ont emprisonné vos proches sur leurs îles.";
			link.l1 = "Parlez-moi de lui.";
			link.l1.go = "trial_23";
		break;
		
		case "trial_23":
			dialog.text = "Tout le monde ne peut pas s'accrocher au trône de la Martinique. Les intérêts de l'Ordre, de la Couronne, des pirates... et un noble ne doit pas oublier ses propres intérêts. Si Parquet n'était pas si laxiste et tenté par le péché, il pourrait même amener Poincy à le prendre au sérieux.";
			link.l1 = "Et à quoi pourrais-je bien lui servir ?";
			link.l1.go = "trial_24";
		break;
		
		case "trial_24":
			dialog.text = "Les fonctionnaires ont toujours du travail pour les capitaines libres. Ils paient avec parcimonie, cependant, et uniquement lorsque cela concerne les intérêts publics, pas personnels. Dans tous les cas, il n'y a pas de meilleure façon dans les Caraïbes de rehausser l'honneur et d'améliorer les relations nationales qu'en travaillant pour les gouverneurs. Saisissez l'instant, d'autant plus que Parquet rencontre quelques ennuis en ce moment. Quels ennuis ?";
			link.l1 = "Quel genre de problème ?";
			link.l1.go = "trial_25";
		break;
		
		case "trial_25":
			dialog.text = "Je suis désolé, frère. Les intérêts de l'Ordre sont en jeu. Je dirai seulement que nous ne sommes pas les seuls à avoir besoin de moyens rapides pour s'enrichir.";
			link.l1 = "Tu es encore énigmatique... Bon, je passerai quand j'aurai le temps.";
			link.l1.go = "trial_26";
		break;
		
		case "trial_26":
			dialog.text = "Va maintenant. Bonne chance, frère !";
			link.l1 = "Merci... À plus tard, Michel.";
			link.l1.go = "trial_27";
		break;
		
		case "trial_27":
			TakeNItems(pchar, "bullet", 5);
			TakeNItems(pchar, "gunpowder", 5);
			DialogExit();
			NextDiag.TempNode = "First time";
			pchar.questTemp.Sharlie = "trial";
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			pchar.questTemp.Trial = "begin"; // старт промежуточной линейки
			SetFunctionTimerCondition("Sharlie_TrialOver", 0, 0, 24, false); // таймер
			AddMapQuestMarkCity("Baster", false);
			AddLandQuestMark(characterFromId("Fadey"), "questmarkmain");
			AddQuestRecord("Sharlie", "19");
			// открываем все острова
			for (i=0; i<MAX_ISLANDS; i++)
			{				
				if (!CheckAttribute(&Islands[i], "hidden")) Island_SetReloadEnableGlobal(Islands[i].id, true);
			}
			DeleteAttribute(pchar, "questTemp.Sharlie.Lock"); //снимаем блокировку
			LocatorReloadEnterDisable("FortFrance_store", "reload2", false); // откроем склад магазина
			sld = characterFromId("Benua");
			sld.quest.help = "true";
			npchar.greeting = "mishelle_3";
			i = FindIsland("Martinique");
			Islands[i].EffectRadius = 5000;
			// Addon-2016 Jason, французские миниквесты (ФМК)
			pchar.quest.Sharlie_FMQ.win_condition.l1 = "Rank";
			pchar.quest.Sharlie_FMQ.win_condition.l1.value = 4;
			pchar.quest.Sharlie_FMQ.win_condition.l1.operation = ">=";
			pchar.quest.Sharlie_FMQ.function = "FMQ_SetConditions";
			// Sinistra - миниквест "Делюк"
			PChar.quest.Del_Alonso.win_condition.l1 = "location";
			PChar.quest.Del_Alonso.win_condition.l1.location = "FortFrance_town";
			PChar.quest.Del_Alonso.win_condition = "Del_Alonso";
			// при достижении уровня даём флаг на квест "Голландский Гамбит"
			pchar.quest.Sharlie_GambitStage_level_9.win_condition.l1 = "Rank";
			pchar.quest.Sharlie_GambitStage_level_9.win_condition.l1.value = 9;
			pchar.quest.Sharlie_GambitStage_level_9.win_condition.l1.operation = ">=";
			pchar.quest.Sharlie_GambitStage_level_9.function = "Sharlie_GambitStage_level_9";
			pchar.quest.Sharlie_GambitStage_level_12.win_condition.l1 = "Rank";
			pchar.quest.Sharlie_GambitStage_level_12.win_condition.l1.value = 12;
			pchar.quest.Sharlie_GambitStage_level_12.win_condition.l1.operation = ">=";
			pchar.quest.Sharlie_GambitStage_level_12.function = "Sharlie_GambitStage_level_12";
			//маркер на контрабандиста по квесту "Деньги на деревьях"
			AddLandQuestMark(characterFromId("FortFrance_Smuggler"), "questmarkmain");
			PChar.quest.MOT_UbratMarku.win_condition.l1 = "MapEnter";
			PChar.quest.MOT_UbratMarku.win_condition = "MOT_UbratMarku";
			// Sinistra - Старт квеста "Травля крысы"
			pchar.questTemp.TK_TravlyaKrys = true;
			AddLandQuestMark(characterFromId("FortFrance_Mayor"), "questmarkmain");
			SetTimerCondition("TK_Timer", 0, 0, 30, false);
			//маркер на торговца БасТера по квесту "Бесчестный конкурент"
			AddLandQuestMark(characterFromId("BasTer_trader"), "questmarkmain");
		break;
		
		case "gambitA":
			dialog.text = "Alors, fais comme tu veux. Je crois en toi, frère. Quand je te regarde maintenant, je sais juste que tu changes pour le mieux.";
			link.l1 = "Tu ne dis pas. Comment ça?";
			link.l1.go = "gambit";
		break;
		
		case "gambit":
			dialog.text = "Je le vois, cher frère. Je vois ta démarche et l'expression sur ton visage. Enfin, le masque du jeune garçon vaniteux, qui m'a littéralement rendu fou, s'est détaché de toi. Ta nouvelle vie t'a visiblement bien profité désormais.";
			if (sti(pchar.money) >= 1000000)
			{
				link.l1 = "Je ne comprends pas, frère, ce que je dois penser de tes paroles, si ce sont des éloges ou des insultes. Mais je te dirai la vérité : je ne suis pas intéressé par ce que tu penses de moi de là-bas. J'ai rassemblé le million nécessaire pour rembourser ta dette, donc tu seras bientôt libre. Où puis-je trouver de Poincy ?";
				link.l1.go = "gambit_1_1";
			}
			else
			{
				link.l1 = "Je ne comprends pas, frère, ce que je dois faire de tes mots, si c'est des louanges ou des insultes. Mais je te dirai la vérité : je ne suis pas intéressé par ce que tu penses de moi de là-bas. J'ai une mer, pas un tas, de choses à gérer et je n'ai pas le temps de me disputer avec toi ici et de couper les cheveux en quatre. As-tu quelque chose de pertinent à dire ? Sinon, je vais reprendre ma route...";
				link.l1.go = "gambit_1";
			}
			DelLandQuestMark(npchar);
			DeleteQuestCondition("Sharlie_GambitStage_level_9");
			DeleteQuestCondition("Sharlie_GambitStage_level_12");
			// уберем маркеры, если ФМК не стали проходить
			DelMapQuestMarkCity("Baster");
			DelMapQuestMarkCity("Fortfrance");
			DelMapQuestMarkCity("Charles");
			DelMapQuestMarkCity("Tortuga");
			DelMapQuestMarkCity("Portpax");
			
			if(CharacterIsAlive("FMQG_pass_1"))
			{
				sld = CharacterFromID("FMQG_pass_1");
				LAi_SetImmortal(sld, false);
				sld.lifeday = 0;
			}
			if(CharacterIsAlive("FMQM_carpenter"))
			{
				sld = CharacterFromID("FMQM_carpenter");
				LAi_SetImmortal(sld, false);
				sld.lifeday = 0;
			}
			if(CharacterIsAlive("FMQN_seafox_1"))
			{
				sld = CharacterFromID("FMQN_seafox_1");
				LAi_SetImmortal(sld, false);
				sld.lifeday = 0;
			}
			if(CharacterIsAlive("FMQT_girl"))
			{
				sld = CharacterFromID("FMQT_girl");
				LAi_SetImmortal(sld, false);
				sld.lifeday = 0;
			}
			if(CheckAttribute(pchar, "questTemp.FMQP") && pchar.questTemp.FMQP == "begin") 
			{
				DeleteAttribute(pchar, "questTemp.FMQP");
				sld = CharacterFromID("PortPax_waitress");
				DelLandQuestMark(sld);
			}
			if(CharacterIsAlive("FMQG_cureer"))
			{
				sld = CharacterFromID("FMQG_cureer");
				LAi_SetImmortal(sld, false);
				sld.lifeday = 0;
			}
			if(CharacterIsAlive("Guide_y"))
			{
				sld = CharacterFromID("Guide_y");
				LAi_SetImmortal(sld, false);
				sld.lifeday = 0;
			}
		break;
		
		case "gambit_1_1":
			dialog.text = "Vous avez réussi à réunir un million ? Bon travail, Charles, tout simplement impeccable ! Mais Philippe de Poincy, malheureusement, n'est plus à sa résidence, il est parti pour des affaires de la Société en expédition secrète. Alors vous devrez patienter un peu avant de lui rendre visite.";
			link.l1 = "Que diable et vos affaires secrètes ! Je pensais en avoir fini avec tout cela et rentrer chez moi, et maintenant...";
			link.l1.go = "gambit_1_2";
		break;
		
		case "gambit_1_2":
			dialog.text = "Et maintenant, tu t'es ouvert à l'opportunité de faire beaucoup plus d'argent et pas seulement ça. Frère, le fait que tu aies amassé la somme demandée par le vieux renard est incroyable, mais je ne serais pas si confiant et si calme... De Poincy est une véritable anguille glissante, et il a montré beaucoup d'intérêt pour ta modeste personne, et...";
			link.l1 = "Et maintenant, tu as peur qu'un million ne soit pas suffisant pour lui ?! Ou bien as-tu omis quelque chose la dernière fois ?";
			link.l1.go = "gambit_1_3";
		break;
		
		case "gambit_1_3":
			dialog.text = "Je n'ai peur de rien, mais je dois te prévenir que Poincy n'est pas un homme simple. Pendant son absence, tu as l'occasion de te forger une réputation, afin de pouvoir lui parler d'égal à égal, et non comme un seigneur à un serviteur. Ainsi, je t'exhorte vivement à suivre mon plan, que je vais t'exposer dès maintenant.";
			link.l1 = "D'accord. Inutile de pleurer sur le lait renversé. Je vais tenir le coup dans ce trou à rats un peu plus longtemps. De Poincy ne va pas naviguer éternellement. Mets-moi au courant de ton plan.";
			link.l1.go = "gambit_2";
		break;
		
		case "gambit_1":
			dialog.text = "Oh ! Une réponse louable. Je suis heureux, Charles, que tu sois devenu un homme. Cependant, ne sois pas si sévère envers ton frère. Certes, j'ai quelque chose à te dire. J'attendais avec impatience notre prochaine rencontre et j'ai déjà élaboré un plan pour ce que tu feras ensuite.";
			link.l1 = "Bien. Alors, mets-moi au courant.";
			link.l1.go = "gambit_2";
		break;
		
		case "gambit_2":
			dialog.text = "Regarde. Bien sûr, l'argent joue un grand rôle aux Caraïbes, comme partout ailleurs, mais l'argent ne peut pas tout résoudre. Un homme prospère ne doit pas seulement avoir une bourse bien garnie, mais aussi des relations étendues et variées, et pas avec des vauriens, mais avec des gens qui comptent dans ce monde.\nPeu importe leur nationalité ou leur origine. Les relations ouvrent des portes qui ne peuvent pas être ouvertes avec de l'argent seul. La combinaison de 'argent plus relations' donne à un homme la chose la plus précieuse au monde - le pouvoir.\nTu devrais envisager d'établir de telles relations et tu ne pourras pas le faire en te contentant de faire des jobs de fret, de commercer, de pirater mineur ou même de gagner les faveurs des gouverneurs.";
			link.l1 = "Qu'est-ce que tu proposes ?";
			link.l1.go = "gambit_3";
		break;
		
		case "gambit_3":
			dialog.text = "Il n'y a pas tant d'organisations puissantes dans les Caraïbes. L'une d'elles est la Compagnie néerlandaise des Indes occidentales. Tu peux les rejoindre. Leur siège est à Willemstad, sur Curaçao. La Compagnie recrute souvent des capitaines tiers et offre des contrats spéciaux à long terme aux plus utiles d'entre eux.\nSi tu as de la chance, tu pourrais y faire une carrière décente. J'ai entendu dire qu'ils rencontrent actuellement de sérieux problèmes - quelque corsaire anglais a pris les armes contre la Compagnie et coule constamment leurs navires. Ils ne peuvent rien faire contre lui, il est officier de marine, ce qui le rend trop coriace pour eux.\nOn dit qu'il est d'une manière ou d'une autre lié aux services secrets militaires britanniques et que ce sont des gens très sérieux. Donc, peut-être que prendre le parti de ce capitaine sera encore plus profitable pour toi, mais le problème est que je ne connais pas son nom, je sais seulement que son port d'attache est à Antigua.\nTu pourrais naviguer là-bas et te renseigner. J'ai aussi entendu parler d'une organisation étrange qui participe également à ce conflit anglo-néerlandais, mais je ne sais pas de quel côté elle est. Tout ce que je sais, c'est que les pistes mènent à la Barbade, à Bridgetown...";
			link.l1 = "Alors tu proposes que je m'engage au service des Hollandais ou que je parte à la recherche d'un capitaine douteux ou d'une 'organisation' encore plus douteuse ?";
			link.l1.go = "gambit_4";
		break;
		
		case "gambit_4":
			dialog.text = "Le choix t'appartient. Dans tous les cas, tu n'auras pas d'autre moyen de te mêler rapidement aux gens qui décident du sort des autres aux Caraïbes et qui possèdent un pouvoir considérable. J'espère que tu n'as pas en tête que deux ou trois faveurs pour le gouverneur te feront entrer directement dans la marine royale.";
			link.l1 = "Tu sais, cher frère. Je n'espérais pas vraiment une carrière militaire dans la marine française. Dieu m'en garde de finir comme toi, coincé dans une cellule pour une tâche que je n'ai pas réussie à accomplir... Très bien, j'ai compris. Je pense que je trouverai le Quartier Général de la Compagnie Néerlandaise sans trop d'embûches, mais je n'ai aucune idée de comment chercher le reste des parties.";
			link.l1.go = "gambit_5";			
		break;
		
		case "gambit_5":
			dialog.text = "Quant au corsaire anglais, vous pouvez vous renseigner à Saint John's, Antigua. Quelqu'un pourra sûrement vous renseigner. Dites-leur que vous cherchez du travail avec la flotte anglaise. Quant à 'la troisième force', vous pouvez en parler aux gens de Bridgetown. Quelqu'un là-bas doit sûrement être lié à cette organisation.";
			link.l1 = "Leur travail sera-t-il au moins rémunéré ? La Compagnie, ce corsaire... Ou est-ce que tout cela sera uniquement pour les 'relations' ?";
			link.l1.go = "gambit_6";			
		break;
		
		case "gambit_6":
			dialog.text = "Charles, tu me surprends. La Compagnie néerlandaise des Indes occidentales opère avec des sommes qu'un roi envierait. Le corsaire, dont je t'ai parlé, a pillé tant de navires néerlandais qu'il doit déjà être débordant de richesses. Et les gens de 'l'organisation' n'ont pas seulement beaucoup d'argent. Ils ont une sacrée montagne d'argent.\nTravailler pour eux te garantira toujours une part de gâteau. Des gens comme eux jouent toujours gros. Et si tu es malin, tu peux toujours jouer ton propre jeu et gagner encore plus.";
			link.l1 = "D'accord. Je vais y réfléchir et décider quelle est ma meilleure option. Avez-vous d'autres instructions ?";
			link.l1.go = "gambit_7";
		break;
		
		case "gambit_7":
			dialog.text = "Oui. Tu devrais apprendre à utiliser les instruments de navigation. Hélas, beaucoup de navigateurs ne savent s'orienter qu'avec la boussole et les étoiles et ne peuvent pas estimer les coordonnées. Et c'est crucial.\nAlors. Utilise une boussole pour estimer la latitude. C'est un outil assez rare et tu ne le trouveras pas en magasin, mais tu peux le fabriquer toi-même en utilisant deux objets courants - une boussole et un astrolabe. Tiens, prends les instructions.\nEstimer la longitude est un peu plus délicat. Tu auras besoin d'un chronomètre évalué. Tu peux en fabriquer un à partir d'un chronomètre de navire commun en l'ajustant avec un sablier. Le problème, c'est qu'un tel outil fonctionne efficacement seulement pendant un mois avant de devenir trop inadmissible à cause des erreurs.\nUn chronomètre nécessite toujours d'être réinitialisé. Les sabliers peuvent être achetés au bureau de la Compagnie néerlandaise des Indes occidentales. J'ai aussi acheté des chronomètres là-bas. Tiens, prends ces instructions.";
			link.l1 = "Merci. Je vais me mettre à étudier immédiatement.";
			link.l1.go = "gambit_8";
		break;
		
		case "gambit_8":
			AddQuestRecordInfo("Recipe", "bussol");
			SetAlchemyRecipeKnown("bussol");
			AddQuestRecordInfo("Recipe", "clock2");
			SetAlchemyRecipeKnown("clock2");
			dialog.text = "Essayez d'acquérir tous ces outils dès que possible. Tous les capitaines expérimentés et respectés opèrent avec latitude et longitude. Vous serez considéré comme un novice en navigation jusqu'à ce que vous sachiez ce que ces chiffres signifient.\nEh bien, revenez vous vanter dès que vous aurez du succès dans les affaires dont nous avons récemment discuté. Bon vent, Charles !";
			link.l1 = "Merci, cher frère. Je sens que cela sera sûrement utile !";
			link.l1.go = "gambit_9";
		break;
		
		case "gambit_9":
			DialogExit();
			NextDiag.CurrentNode = "First time";
			pchar.questTemp.Sharlie = "gambit";//флаг на Голландский Гамбит
			pchar.questTemp.HWIC.CanTake = "true"; //Голландский Гамбит доступен для взятия
			AddQuestRecord("Sharlie", "20");
			npchar.greeting = "mishelle_3";
			AddMapQuestMarkCity("Bridgetown", false);
			AddMapQuestMarkCity("Villemstad", false);
			AddMapQuestMarkCity("SentJons", false);
			AddLandQuestMark(characterFromId("Bridgetown_tavernkeeper"), "questmarkmain");
			AddLandQuestMark(characterFromId("Lucas"), "questmarkmain");
			AddLandQuestMark(characterFromId("Knippel"), "questmarkmain");
			// Rebbebion, убираем марки
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("Fortfrance");
		break;
		
		case "gambit_fale":
			dialog.text = "Et de quoi as-tu à te vanter ?";
			link.l1 = "Rien pour l'instant. J'ai trouvé les trois organisations et essayé de travailler avec elles, mais comme un cigare, tout a éclaté en fumée littéralement dès la première étape. C'est comme si le destin était truqué contre moi...";
			link.l1.go = "gambit_fale_1";			
		break;
		
		case "gambit_fale_1":
			dialog.text = "Alors, les rumeurs sont vraies alors... Cher frère, le destin n'est pas truqué contre toi. C'est ce qu'on appelle un esprit obtus et des mains malhonnêtes. Tu m'as déçu. Retourne en France, il n'y a plus rien à faire pour toi ici.";
			link.l1 = "Mais comment...";
			link.l1.go = "gambit_fale_2";			
		break;
		
		case "gambit_fale_2":
			dialog.text = "Ce n'est plus ton affaire. Je m'en occuperai moi-même. J'ai d'autres personnes plus aptes à m'aider à résoudre mon problème. J'avais peur qu'en te confiant cela, je sois retenu ici jusqu'à la fin de mes jours. Quoi qu'il en soit. Va-t'en d'ici, retourne à tes courtisanes.";
			link.l1 = "D'accord, va en enfer...";
			link.l1.go = "gambit_fale_3";
		break;
		
		case "gambit_fale_3":
			DialogExit();
			NextDiag.CurrentNode = "gambit_fale_4";
			npchar.lifeday = 30;
		break;
		
		case "gambit_fale_4":
			dialog.text = "Je n'ai rien à te dire. Va-t'en.";
			link.l1 = "... ";
			link.l1.go = "exit";
			NextDiag.TempNode = "gambit_fale_4";
		break;
		
		case "saga":
			switch(pchar.questTemp.HWIC.Detector)
			{
				case "holl_win": sTemp = "I've entered service with the Dutch West India Company and become a special tasks agent and close friend of the vice administrator of the Company, Lucas Rodenburg. I managed to carry out several serious missions, in particular, I liquidated the actual English privateer. In addition, I've now got my own personal home on Antigua and my pockets are chinking with money."; break;
				
				case "holl_fail": sTemp = "I've entered service with the Dutch West India Company, however matters have gone modestly, I've failed an important task, and was compelled to a dishonorable discharge with nothing."; break;
				
				case "eng_win": sTemp = "I've found the actual English privateer, Richard Fleetwood, and carried out several important tasks in the name of the English navy, in particular, I liquidated the pirate 'ghost ship' and did away with Lucas Rodenburg himself, vice administrator of the Company. In addition, I've now got my own personal home on Antigua and my pockets are chinking with money."; break;
				
				case "eng_win_half": sTemp = "I've found the actual English privateer, Richard Fleetwood, and carried out several important tasks in the name of the English navy, in particular, I liquidated the pirate 'ghost ship'. Of course, Fleetwood departed to England and my service with him is over, but still..."; break;
				
				case "eng_fail": sTemp = "I've entered service with the English privateer from Antigua, however matters have gone modestly, I've failed an important task, and was compelled to a dishonorable discharge with nothing."; break;
				
				case "self_win": sTemp = "I've discovered the 'secret organization' on Barbados, started rolling some game of my own, and achieved quite a bit: I did away with that English privateer, Richard Fleetwood, put Lucas Rodenburg, the vice administrator of the Company, behind bars, become a close friend of governor Matthias Beck and the company's director Peter Stuyvesant. In addition, I've now got my own personal home on Antigua and my pockets are chinking with money."; break;
				
				case "self_fail": sTemp = "I've discovered the 'secret organization' on Barbados, started rolling some game of my own, however it all went down in dust at the moment of truth..."; break;
			}
			dialog.text = "Et alors ? Allons, cher frère, ne fais pas durer le suspense. Quelle est la bonne nouvelle ? Quelques rumeurs sont venues jusqu'à moi à propos de ton zèle ardent, mais je voulais l'entendre de ta bouche.";
			link.l1 = sTemp;
			link.l1.go = "saga_1";
		break;
		
		case "saga_1":
			if (pchar.questTemp.HWIC.Detector == "holl_win" || pchar.questTemp.HWIC.Detector == "eng_win" || pchar.questTemp.HWIC.Detector == "self_win")
			{
				dialog.text = "Excellent ! Beau travail, Charles ! Je n'ai pas douté de toi un seul instant ! Tu iras loin, cher frère... Te rendre utile ainsi et nouer des relations avec des gens si importants, bien sûr, je ne m'y attendais pas. Félicitations !";
			}
			else
			{
				dialog.text = "Ne sois pas contrarié, Charles. Si ça n'a pas marché, tu n'y peux rien. Nous utiliserons d'autres moyens pour obtenir les résultats dont nous avons besoin.";
			}
			link.l1 = "Que faisons-nous maintenant, Michel ? Est-il temps de rendre visite au Chevalier de Poincy ? Je me sens tout à fait prêt pour une conversation avec lui.";
			link.l1.go = "saga_2";	
		break;
		
		case "saga_2":
			dialog.text = "As-tu déjà réussi à rassembler la somme requise d'un million de pesos ?";
			if (sti(pchar.money) >= 1000000)
			{
				link.l1 = "Oui, je possède actuellement la somme requise.";
				link.l1.go = "saga_3_1";
			}
			else
			{
				link.l1 = "Non, je n'ai pas encore cette somme d'argent.";
				link.l1.go = "saga_3_2";
			}
		break;
		
		case "saga_3_1":
			dialog.text = "Excellent ! Alors je ne resterai pas longtemps dans cette casemate... Mets le cap sur Capsterville, c'est sur Saint-Christophe, et demande une audience avec de Poincy. Il devrait être au palais du gouverneur où il réside. Au-delà de ça, juge selon la situation et souviens-toi : Poincy est rusé, très rusé... J'ai un mauvais pressentiment que toute cette affaire ne va pas se dérouler aussi facilement. Va, frère, et sois prudent !";
			link.l1 = "Je garderai tes précautions à l'esprit, Michel. Ne t'en fais pas, je ne suis pas né de la dernière pluie non plus. Je file voir le vieux renard. À plus tard !";
			link.l1.go = "saga_4";			
		break;
		
		case "saga_3_2":
			dialog.text = "Aucune utilité de parler à de Poincy alors. Il ne te laissera même pas entrer. Rassemble l'argent, mon frère, tu es déjà assez expérimenté, donc ça ne devrait pas poser de problème. Navigue vers Capsterville à Saint-Christophe dès que tu l'as.\nLe Chevalier doit être dans son palais de gouverneur. Demande une audience et ils te laisseront entrer. Ensuite, vois par toi-même et fais attention : Poincy est rusé, très rusé... Quelque chose me dit que cette histoire ne finira pas comme ça.";
			link.l1 = "Je garderai tes précautions à l'esprit, Michel. Ne t'inquiète pas, je ne suis pas né de la dernière pluie non plus. Dès que j'aurai réuni l'argent, j'irai directement voir le vieux renard. À plus tard !";
			link.l1.go = "saga_4";			
		break;
		
		case "saga_4":
			DialogExit();
			AddMapQuestMarkCity("Charles", false);
			AddLandQuestMark(characterFromId("Puancie"), "questmarkmain");
			npchar.quest.givelink_saga = "true";
			NextDiag.TempNode = "First time";
			pchar.questTemp.Sharlie = "saga";//флаг на Пиратскую Сагу
		break;
		
		case "saga_5":
			dialog.text = "Nom d'un tonneau! C'est exactement ce que je craignais. Poincy te suit de près depuis longtemps, Charles. Voilà pourquoi il s'intéresse tant à toi! Tu t'es fait une sacrée réputation dans les Caraïbes et il a donc décidé de t'utiliser pour accomplir des missions qui ont échoué...";
			link.l1 = "J'ai l'impression, Michel, que tu étais bien au courant et que tu ne voulais tout simplement pas m'en informer avant. Tout se déroule trop facilement... L'argent d'abord, maintenant ton travail... Cela n'arrive pas par hasard.";
			link.l1.go = "saga_6";
		break;
		
		case "saga_6":
			dialog.text = "Charles, ne cherche pas un message secret là où il n'y en a pas. Si seulement tu avais donné l'argent à Poincy dès le premier jour de ton arrivée... Eh bien, je veux dire, disons si tu l'avais. Le Chevalier ne t'aurait rien demandé d'autre. Mais maintenant qu'il s'intéresse à toi et qu'il a vu avec quelle facilité tu t'es installé ici et ce que tu as été capable d'accomplir, il a décidé d'exploiter tes talents.";
			link.l1 = "D'accord... parce que tes talents ne lui sont plus satisfaisants, n'est-ce pas ? Merde ! Très bien. Je vois que je suis dans une impasse ici. Qui est cet hérétique ? Comment puis-je le trouver ?";
			link.l1.go = "saga_7";
		break;
		
		case "saga_7":
			dialog.text = "Pas besoin de le chercher ! Il ne quitte jamais Tortuga et reste sous la protection du bastion qu'il a construit et des hordes de huguenots loyaux, qui servent comme soldats dans sa garnison. Par conséquent, chaque soldat lui est loyal. Poincy voulait dire Francois Levasseur, le gouverneur de Tortuga.\nLes Espagnols ne peuvent toujours pas l'en déloger et de Poincy croyait sérieusement que je serais capable de le faire seul sans aucun soutien de la marine, uniquement parce que déclencher une guerre civile serait une fausse manoeuvre politique due à la proximité de la garnison de Saint-Domingue.\nLe vieux salaud est trop préoccupé par sa carrière sans tache et sa retraite prochaine pour risquer tout cela. Néanmoins, Levasseur est allé trop loin et représente un danger pour la couronne.\nDe Poincy, qui a lui-même nommé Levasseur à son poste actuel, considère ce redoutable huguenot comme un ennemi personnel et est impatient de le remplacer par le Chevalier de Fontenay, mon supérieur immédiat sous le commandement de qui je suis arrivé ici de Malte.";
			link.l1 = "Glorieux ! D'abord, faire un million, puis assassiner le gouverneur de la Tortue. Quelle sera ma prochaine mission ? Organiser un complot à l'Escurial ? Merde ! Je ne suis pas surpris que tu aies foiré ce truc. Éliminer le gouverneur n'est pas comme pincer des marchands espagnols. J'espère que tu avais un plan en tête quand tu as juré de tirer les marrons du feu ?";
			link.l1.go = "saga_8";
		break;
		
		case "saga_8":
			dialog.text = "Pour être tout à fait honnête, je n'avais aucun plan puisque j'allais de toute façon quitter le service et retourner à notre manoir familial en cas de succès de ma périlleuse entreprise. Personnellement, je me fiche éperdument des problèmes de de Poincy.\nSûrement, il serait devenu beaucoup plus flexible dès qu'il aurait vu l'or indien... Eh bien, actuellement il détient tous les atouts contre nous. Je suppose que je resterai ici tant que Levasseur est le gouverneur de Tortuga.";
			link.l1 = "Et pourquoi les Maltais dirigés par de Fontenay, avec leur regard sur le siège du gouverneur, ne chargeraient-ils pas eux-mêmes Tortuga ?";
			link.l1.go = "saga_9";
		break;
		
		case "saga_9":
			dialog.text = "Imaginez cela. L'ordre déclare la guerre à Louis. Ne soyez pas absurde ! Un tel scandale n'est pas envisageable. Seul un individu privé peut capturer la Tortue. Un pirate, ou un aventurier catholique comme vous.\nAprès cela, il pourra remettre l'île sous le contrôle du nouveau gouverneur que de Poincy enverra. Un tel acte paraîtra formidable du point de vue des grands décideurs politiques.";
			link.l1 = "Alors, cela vaut-il la peine de négocier avec des pirates ?";
			link.l1.go = "saga_10";
		break;
		
		case "saga_10":
			dialog.text = "Le problème, c'est que Levasseur a de l'autorité parmi beaucoup de pirates de la Fraternité et au-delà. Il leur permet de se cacher derrière les batteries de la Tortue et de vendre librement ce qu'ils ont pillé contre une part du butin.\nIl partageait avec de Poincy, mais il ne partage plus. Les navires pirates protégeront la Tortue et sa garnison, ce qui rend l'assaut du fort encore plus difficile.";
			link.l1 = "Penses-tu que cette affaire est une cause perdue?";
			link.l1.go = "saga_11";
		break;
		
		case "saga_11":
			dialog.text = "Il y a toujours une solution, petit frère. Elle n'est simplement pas toujours visible à la surface. Tous les pirates ne sont pas sympathiques envers les huguenots de la Tortue. Je connais au moins deux pirates influents qui considèrent Levasseur comme un traître et une ordure. Je parle de Steven Dodson, également connu sous le nom de Requin, et du légendaire baron de la Baie des Moustiques, Jan Svenson.\nJe ne sais pas où trouver le Requin, j'ai entendu des rumeurs selon lesquelles quelque chose s'est passé et il a dû quitter sa base à Isla Tesoro. Mais tu peux toujours trouver Svenson à Blueweld. Il est une figure importante là-bas.";
			link.l1 = "Supposes-tu que ce... Svenson m'aidera ?";
			link.l1.go = "saga_12";
		break;
		
		case "saga_12":
			dialog.text = "Il le fera si tu l'aides. Les choses ne vont pas très bien pour lui en ce moment et l'homme pourrait avoir besoin de gens loyaux et talentueux. Tu devras d'abord prouver ton utilité avant d'avoir une conversation sérieuse. Tu trouveras un moyen de le faire quand tu seras là-bas. Il m'est difficile de donner des conseils d'ici.\nJe suppose que tu as décidé de continuer, Charles, puisque tu continues à poser des questions ?";
			link.l1 = "Tu vois, Michel, je viens de donner un tas de mon propre argent à de Poincy. Je l'ai amassé à travers le sang, la sueur et les larmes ! Je ne suis pas sûr que tu aurais risqué même un seul louis d'or pour moi si tu étais à ma place.";
			link.l1.go = "saga_13";
		break;
		
		case "saga_13":
			dialog.text = "Charles...";
			link.l1 = "Ne m'interromps pas ! Ce serait stupide de retourner vers père les mains vides. Le problème n'est toujours pas résolu, tu es derrière les barreaux et sous la menace d'être accusé de trahison envers la Société. Poincy n'hésiterait pas à ternir le nom de Monper, si je ne m'acquitte pas de sa 'demande'. Cela se voyait sur son visage. Donc je vais partir à Blueweld pour trouver un moyen d'approcher Svenson. En attendant, réfléchis à ce que tu as 'oublié' de me dire. Par exemple, c'est la première fois que j'entends parler de toi d'un or indien que tu devais apporter à de Poincy.";
			link.l1.go = "saga_14";
		break;
		
		case "saga_14":
			dialog.text = "Il y a des choses qui devraient rester cachées. Tu as raison, je ne t'ai pas tout dit. Peut-être qu'un jour je te dirai plus, mais pas avant que tu ne t'occupes de Levasseur, ce serait un savoir inutile pour le moment.\nJe n'ai aucun doute que ton attention touchante pour moi est causée seulement par le désir de sauver l'honneur de notre famille. En me sauvant, tu te sauves toi-même en premier lieu, et en second lieu, la possibilité de visiter les meilleures maisons de Paris. Ai-je tort?";
			link.l1 = "J'ai bien peur que ce ne soit plus le cas, frère. Tu avais raison. Ces derniers mois passés dans les Caraïbes ont transformé chaque fibre de mon être et toute ma vision du monde. Et je suis sûr que c'est pour le mieux. Je n'ai plus vraiment besoin de ces salons parisiens et je pourrai me débrouiller sans le nom de Monpe un jour. De Maure n'est pas pire...";
			link.l1.go = "saga_15";
		break;
		
		case "saga_15":
			dialog.text = "... ";
			link.l1 = "Et maintenant, la seule chose qui me blesse vraiment, c'est que ta honte laissera une marque sur notre vieux père. Il ne connaît pas le véritable statu quo ni ce qui se passe réellement ici. De plus, comme tu l'as justement dit, le patrimoine doit être restauré de son état funeste. Et le million payé pour ta liberté a considérablement allégé ma trésorerie, donc il faudra clairement la renflouer.";
			link.l1.go = "saga_16";
		break;
		
		case "saga_16":
			dialog.text = "Tu as parfaitement saisi toutes les leçons de la vie, Charles. Je suis vraiment heureux pour toi. Et je suis content que tu aies décidé de répondre à la demande de Poincy au lieu de rentrer en France. J'espère que tout se passera bien pour toi et que tu pourras accomplir ce que je n'ai pas pu faire moi-même.";
			link.l1 = "J'ai bien peur de ne pas avoir le choix. Depuis mon premier jour aux Caraïbes, je fais tout seul. À plus tard, Michel. Je pense que notre prochaine rencontre inclura l'ordre de ta libération.";
			link.l1.go = "saga_17a";

		break;
		
		// Addon 2016-1 Jason Пиратская линейка
		case "saga_17a":
            dialog.text = "Attends une minute ! Avant d'aller voir Jan Svenson, assure-toi de rendre visite à Marcus Tyrex - Il est le Gardien du Code. Il règne sur La Vega à Hispaniola. Il a une autorité sans limites parmi les pirates et les Espagnols le craignent à en mourir.";
			link.l1 = "Pourrait-il m'aider avec notre affaire ?";
			link.l1.go = "saga_17b";
		break;
		
		case "saga_17b":
            dialog.text = "Je doute. Je ne peux vraiment pas dire de quel côté il est, il est probable qu'il ne se soucie que de lui-même. Tu auras besoin du Requin et de Svenson de toute façon, mais en ce moment - Tyrex est le pirate le plus puissant ici. Ils l'ont élu Gardien du Code pour une raison. Tu ne devrais pas ignorer une figure aussi importante. Cela pourrait être utile de mieux connaître les pirates avant de rencontrer Svenson. Tu pourrais même te faire un nom parmi eux...";
			link.l1 = "Et encore une fois, nous revenons au jargon des pirates. Pas moyen d'y échapper, hein ? Très bien. Je vais lui rendre visite.";
			link.l1.go = "saga_17c";
		break;
		
		case "saga_17c":
            dialog.text = "Être un pirate et faire des affaires avec eux, c'est un jeu totalement différent, frère. J'espère que tu verras la différence. Va à La Vega et demande un travail à Tyrex. Si vous ne vous entendez pas - qu'il aille au diable et reviens me voir.";
			link.l1 = "Très bien, Michel. À plus tard!..";
			link.l1.go = "saga_17d";
		break;
		
		case "saga_17d":
            DialogExit();
			AddQuestRecord("Sharlie", "22");
			npchar.greeting = "mishelle_3";
			pchar.questTemp.Mtraxx = "to_lavega";
			pchar.questTemp.Saga = "pirate_line";
			AddLandQuestMark(characterFromId("Terrax"), "questmarkmain");
			AddMapQuestMarkCity("LaVega", false);
		break;
		
		case "saga_17e":
            dialog.text = "Au moins, tu as essayé. Tu as eu l'opportunité de te 'familiariser' avec un baron pirate infâme. Peu importe. Va voir Jan Svenson, il est à Blueweld. Essaie de le faire devenir ton allié ou notre affaire avec Levasseur se transformera en bain de sang.";
			link.l1 = "Très bien. Je suis en route.";
			link.l1.go = "saga_17";
			pchar.questTemp.Mtraxx = "fail_end";
		break;
		
		case "saga_17f":
            dialog.text = "Je suis content que tu te sois arrêté, frère. Je t'ai dit une fois que c'est un jeu totalement différent - être pirate et faire des affaires avec eux. Et tu as perdu ton chemin. J'espère que tu ne feras pas la même erreur avec le Requin et Svenson. Fais le travail mais garde tes distances avec eux. Après tout, tu es un noble français, alors sois au-dessus d'eux. Maintenant, va voir Jan Svenson, il est à Blueweld. Essaie de le faire ton allié ou notre affaire avec Levasseur se transformera en bain de sang.";
			link.l1 = "Très bien. Je suis en route.";
			link.l1.go = "saga_17";
			pchar.questTemp.Mtraxx = "fail_end";
		break;
		
		case "saga_17g":
            dialog.text = "Je suis très heureux de l'entendre, si vous dites la vérité. Mais puis-je vraiment faire confiance à la parole d'un pirate qui brûle des villes, même si elles sont espagnoles, et qui assassine des civils, y compris des femmes ?";
			// belamour legendary edition -->
			if(CheckAttribute(pchar, "questTemp.Mtraxx.Retribution.Choice"))
			{
				if(pchar.questTemp.Mtraxx.Retribution.Choice == "good")
				{
			link.l1 = "Arrête... Je suis vraiment désolé pour ce que j'ai fait pendant mon temps avec Tyrex. J'ai vu l'enfer de mes propres yeux, frère... Non, c'est fini ! J'en ai fini avec la piraterie et jamais plus je ne mettrai le pied à La Vega. Je ferai tout ce qu'il faut pour restaurer mon bon nom.";
			link.l1.go = "saga_17gx";
				}
				if(pchar.questTemp.Mtraxx.Retribution.Choice == "bad")
				{
					link.l1 = "Crois-le ou non. C'est toi qui es derrière les barreaux, pas moi.";
					link.l1.go = "saga_17gxa";
				}
			}
			else //заглушка
			{
				link.l1 = "Arrête ça... Je me repens vraiment des abominations que j'ai commises en travaillant avec Tyrex. J'ai vu l'enfer de mes propres yeux, frère ! .. Non, mon passé de pirate est terminé ! Je ne suis plus à La Vega. Je prendrai toutes les mesures pour restaurer mon bon nom.";
				link.l1.go = "saga_17gx";
			}
		break;
		
		case "saga_17gxa":
            dialog.text = "Oh, frère... Ne fâche pas Dieu... J'espère que cela ne se reproduise pas avec Svenson et Shark. Fais des choses, mais garde tes distances et souviens-toi quel genre de personnes ils sont. Il n'est pas convenable pour un noble français de devenir comme eux. Sois au-dessus. Maintenant, va voir Jan Swenson à Blueweld et essaie de trouver un moyen d'approcher le vieux corsaire. Sans lui, il ne sera pas possible de résoudre le problème avec Levasseur avec peu de sang versé.";
			link.l1 = "Très bien. Je ne tarderai pas.";
			link.l1.go = "saga_17";
			pchar.questTemp.Mtraxx = "full_complete_end";
		break;

		case "saga_17gx":
            dialog.text = "Tu devras y mettre beaucoup d'efforts, frère. Te souviens-tu de ce que je t'avais dit jadis ? Qu'être pirate et faire affaire avec eux, c'est un tout autre jeu. Tu... Laisse tomber, j'espère que tu ne feras pas la même erreur avec le Requin et Svenson. Fais le travail, mais garde tes distances avec eux. Tu es un noble français après tout, alors sois au-dessus d'eux. Maintenant, va voir Jan Svenson, il est à Blueweld. Essaie de le faire devenir ton allié, ou notre accord avec Levasseur se transformera en bain de sang.";
			link.l1 = "Très bien. Je suis en route.";
			link.l1.go = "saga_17";
			pchar.questTemp.Mtraxx = "full_complete_end";
		break;
		
		case "saga_17":
			DialogExit();
			AddQuestRecord("Sharlie", "22_1");
			pchar.questTemp.Saga = "blueveld";
			LocatorReloadEnterDisable("SantaCatalina_houseS1", "reload2", true); // закрыть кабинет Свенсона
			npchar.greeting = "mishelle_3";
			if(CheckAttribute(pchar, "questTemp.Mtraxx.CharleePrince"))
			{
				DeleteAttribute(pchar, "questTemp.Mtraxx.CharleePrince");
				SetFunctionTimerCondition("DelCharleePrince", 1, 0, 0, false);
			}
			AddMapQuestMarkCity("SantaCatalina", false);
			AddLandQuestMark(characterFromId("SantaCatalina_tavernkeeper"), "questmarkmain");
			AddLandQuestMark(characterFromId("JS_girl"), "questmarkmain");
		break;
		
		case "Base_fight":
			dialog.text = "Ce n'est pas le bon moment pour bavarder, frère ! L'ennemi est dans notre refuge !";
			link.l1 = "... ";
			link.l1.go = "exit";
			NextDiag.TempNode = "Base_fight";
		break;
		
		case "Base_afterfight":
			sTemp = "";
			// belamour legendary edition фикс проверки мундира с мушкетом
			if(IsUniformEquip()) sTemp = "I see you've become a captain of the navy... I didn't see that coming to be honest. I truly congratulate you!";
			dialog.text = "Tu arrives juste à temps, cher frère ! Je suis tellement heureux de te voir ! Ces maudits Castillans ont déjà complètement pris le contrôle de Saint-Pierre. Je pensais que nous étions fichus pour de bon !"+sTemp+"";
			link.l1 = "Nous ne sommes pas tirés d'affaire, la ville est dégagée mais les salauds sont retranchés au fort et il y a une énorme escadre menée par un vaisseau de guerre. Mais j'ai une nouvelle fort agréable à t'annoncer : Michel, tu es libre !";
			link.l1.go = "Base_afterfight_1";
		break;
		
		case "Base_afterfight_1":
			dialog.text = "Je n'en crois pas mes oreilles ! Est-ce possible ? La liberté ?!";
			link.l1 = "Levasseur est mort, Tortuga est maintenant dirigée par ton ancien commandant, et le vieux renard Poincy a retiré toutes ses accusations contre toi. Désormais, rien ne menace notre bon nom.";
			link.l1.go = "Base_afterfight_2";
		break;
		
		case "Base_afterfight_2":
			dialog.text = "J'ai douté jusqu'à la dernière minute... Tu m'as surpris, Charles, et réussi là où j'ai subi un fiasco désastreux.";
			link.l1 = "Audaces fortuna juvat, frère... Comme tu peux le voir, je connais aussi le latin maintenant. Où est la clé de ta cellule ?";
			link.l1.go = "Base_afterfight_3";
		break;
		
		case "Base_afterfight_3":
			dialog.text = "La clef de mon casemate devrait être sur le bureau de l'officier de service. Cherche-les là. Peut-être qu'elles sont tombées par terre et ont glissé quelque part...";
			link.l1 = "Je vais les trouver et je reviendrai !";
			link.l1.go = "Base_afterfight_4";			
		break;
		
		case "Base_afterfight_4":
			DialogExit();
			pchar.questTemp.Sharlie.DefendSP.SeekKey = true;
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "Base_afterfight_6":
			dialog.text = "Enfin la liberté ! Oh, combien de temps j'ai attendu !";
			link.l1 = "Tu ne peux même pas imaginer combien de temps j'ai attendu cet instant... Michel, avons-nous des gens capables de se battre ?";
			link.l1.go = "Base_afterfight_7";			
		break;
		
		case "Base_afterfight_7":
			dialog.text = "Qu'as-tu en tête, Charles ?";
			link.l1 = "La menace espagnole ne s'est pas encore dissipée. Je veux les déloger du fort, puis unir nos forces pour attaquer l'escadre à la fois par terre et par mer ! En utilisant les canons du bastion, je pourrai me mesurer au vaisseau de guerre !";
			link.l1.go = "Base_afterfight_8";			
		break;
		
		case "Base_afterfight_8":
			dialog.text = "Nous avons des hommes. Un grand nombre de chevaliers est parti pour protéger le palais du gouverneur. Nous pourrons certainement trouver quelqu'un en ville... Je rassemblerai tous les hommes que je peux trouver. À bientôt au-delà des portes de la ville !";
			link.l1 = "... -> ";
			link.l1.go = "Base_afterfight_9";			
		break;
		
		case "Base_afterfight_9":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_SetImmortal(npchar, false);
			LAi_SetCheckMinHP(npchar, 10, true, ""); // скрытое бессмертие
			LAi_SetHP(npchar, 500, 500);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 30.0);
			pchar.quest.DefendSP_base2.win_condition.l1 = "location";
			pchar.quest.DefendSP_base2.win_condition.l1.location = "FortFrance_Town";
			pchar.quest.DefendSP_base2.function = "DefendSP_CloseTown";
			AddQuestRecord("Sharlie", "36");
		break;
		
		case "Fort_attack":
			dialog.text = "Le voilà, frère, notre armée. Tous les gens que j'ai pu trouver. Pas beaucoup en termes de nombre, mais nous nous battrons pour notre patrie ! Nous expulserons ces foutus intrus hors du fort ! L'effet de surprise nous aidera - ils ne s'attendent pas à notre attaque. En avant !";
			link.l1 = "Dulce et decorum est pro patria mori! En avant !";
			link.l1.go = "Fort_attack_1";
		break;
		
		case "Fort_attack_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			for (i=1; i<=7; i++)
			{
				sld = CharacterFromID("DefendSP_frafort_"+i);
				LAi_SetActorType(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
			}
			chrDisableReloadToLocation = false;//открыть локацию
			LocatorReloadEnterDisable("FortFrance_Exittown", "reload2_back", false);
			LocatorReloadEnterDisable("FortFrance_Exittown", "reload1_back", true);
			LocatorReloadEnterDisable("FortFrance_Exittown", "reload3", true);
			pchar.quest.DefendSP_fort2.win_condition.l1 = "location";
			pchar.quest.DefendSP_fort2.win_condition.l1.location = "FortFrance_fort";
			pchar.quest.DefendSP_fort2.function = "DefendSP_FortBattle";
			locations[FindLocation("FortFrance_fort")].QuestCapture = true;
		break;
		
		case "Fort_attack_2":
			dialog.text = "C'est fait, frère ! Le fort est à nous !";
			link.l1 = "C'est dommage qu'il ait pris un tel coup dans la bataille contre l'escadron espagnol... mais il est encore tout à fait capable de mener une bataille.";
			link.l1.go = "Fort_attack_3";			
		break;
		
		case "Fort_attack_3":
			dialog.text = "Je jouerai mon rôle. Nous chargerons les canons et infligerons un coup lourd à l'ennemi ! Mais seulement après avoir vu votre escadre approcher, sinon le vaisseau de ligne nous réduira rapidement en sciure.";
			link.l1 = "Rassemble les gens, Michel ! Je retourne immédiatement à la côte !";
			link.l1.go = "Fort_attack_4";			
		break;
		
		case "Fort_attack_4":
			dialog.text = "Charles, souviens-toi : la partie la plus dangereuse de l'escadron est le vaisseau de ligne ! Essaie de l'éliminer en premier. Nous concentrerons également le feu sur elle avec ce qui reste de la batterie du fort.";
			link.l1 = "D'accord, frère. Peut-être devrais-je la capturer.";
			link.l1.go = "Fort_attack_5";			
		break;
		
		case "Fort_attack_5":
			dialog.text = "À en juger par les circonstances, je ne suis pas celui qui devrait vous enseigner. Maintenant, nous devrions arrêter de perdre notre temps !";
			link.l1 = "...";
			link.l1.go = "Fort_attack_6";			
		break;
		
		case "Fort_attack_6":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1);
			LocatorReloadEnterDisable("FortFrance_Exittown", "reload1_back", false);
			LocatorReloadEnterDisable("FortFrance_Exittown", "reload3", false);
			LocatorReloadEnterDisable("Shore38", "boat", false); // выпустить в море
			// закрываем городские заведения
			for (i=3; i<=10; i++)
			{
				LocatorReloadEnterDisable("FortFrance_town", "reload"+i+"_back", true);
			}
			LocatorReloadEnterDisable("FortFrance_town", "reload91", true);
			LocatorReloadEnterDisable("FortFrance_town", "reload_jail", true);
			pchar.quest.DefendSP_fort3.win_condition.l1 = "location";
			pchar.quest.DefendSP_fort3.win_condition.l1.location = "shore38";
			pchar.quest.DefendSP_fort3.function = "DefendSP_BeforeSeaBattle";
			pchar.quest.DefendSP_sea1.win_condition.l1 = "location";
			pchar.quest.DefendSP_sea1.win_condition.l1.location = "Martinique";
			pchar.quest.DefendSP_sea1.function = "DefendSP_SeaBattle";
			AddQuestRecord("Sharlie", "37");
		break;
		
		case "Victory":
			dialog.text = "Gloria victorieuse ! Félicitations pour ta victoire, frère ! Tu étais formidable ! Les Espagnols sont complètement anéantis !";
			link.l1 = "J'espère que cela leur apprendra à y réfléchir à deux fois avant d'attaquer les colonies françaises.";
			link.l1.go = "Victory_1";			
		break;
		
		case "Victory_1":
			dialog.text = "Maintenant dis-moi, Charles : que vaut ta vie passée... comparée à celle-ci ?";
			link.l1 = "Ne me le rappelle pas...";
			link.l1.go = "Victory_2";			
		break;
		
		case "Victory_2":
			dialog.text = "Te souviens-tu de ce que je t'ai dit lors de notre première rencontre ici ? 'Tu aimeras cette vie', c'est ça ! Oui, et un immense merci à toi, frère, pour ton aide. Sans toi, je n'aurais probablement jamais réussi à échapper aux confins de cette base souterraine.";
			link.l1 = "N'en parle pas, Michel. Tu es mon frère après tout, et j'étais obligé de t'aider.";
			link.l1.go = "Victory_3";			
		break;
		
		case "Victory_3":
			dialog.text = "Regarde-toi, frère, je suis impressionné : tant de force dans les yeux, de confiance dans les mouvements, de prestance dans la posture... où est passé ce fichu artiste et bouffon de cour ? En effet ! Tu as dépassé mes attentes les plus audacieuses, à vrai dire, je n'aurais jamais pensé que tu deviendrais... ça.\nCela me fait même... un peu peur. Parce que tu ne reculeras devant rien pour atteindre ton objectif. Tu es bon, trop bon...";
			link.l1 = "Pour une raison quelconque, j'ai de nouveau du mal à te comprendre. Es-tu encore mécontent de moi ?";
			link.l1.go = "Victory_4";			
		break;
		
		case "Victory_4":
			dialog.text = "Non ! De quoi parlez-vous ?... Pas du tout ! Je ne faisais que canaliser mon excitation.";
			link.l1 = "D'accord. Alors, que vas-tu faire ensuite, frère ? Continueras-tu à servir la Société ? Ou retourneras-tu à notre patrimoine ? Oui, et j'ai presque oublié : tu as promis de me parler d'une chose.";
			link.l1.go = "Victory_5";			
		break;
		
		case "Victory_5":
			dialog.text = "À propos de quoi exactement ?";
			link.l1 = "À propos de ton service pour de Poincy. À propos d'un certain or indien que tu devais lui apporter. À propos de tout ce qui a précédé ton emprisonnement. Il y a beaucoup de choses que tu n'as pas réussi à me dire, Michel, me laissant pratiquement dans le noir. Alors...";
			link.l1.go = "Victory_6";			
		break;
		
		case "Victory_6":
			dialog.text = "Frère, je me souviens parfaitement de ce que j'ai dit. Je te dirai tout. Mais pas au milieu d'une ville en flammes !\nNous avons tous les deux beaucoup de choses à faire maintenant. Tu dois organiser ton escadron, le réparer et préparer à nouveau les navires. Moi et le gouverneur allons organiser et calmer les habitants.\nNous discuterons de tout demain matin avec un verre de bon vin français. Fais-moi confiance, frère, j'ai un grand plan. Un vraiment grand. Mais pas maintenant. Va voir l'abbé Benoit demain à neuf heures du matin. Je passerai la nuit chez lui, c'est un vieil ami à moi.";
			link.l1 = "D'accord, Michel. C'est réglé alors. J'attendrai avec impatience notre conversation de demain.";
			link.l1.go = "Victory_7";			
		break;
		
		case "Victory_6A":
			dialog.text = "Dialogue 28.";
			link.l1 = "Très bien, Michel. C'est réglé alors. J'attends avec impatience notre conversation de demain.";
			link.l1.go = "Victory_7";
		break;
		
		case "Victory_7":
			dialog.text = "Inutile de dire adieu, Charles !";
			link.l1 = "...";
			link.l1.go = "Victory_8";			
		break;
		
		case "Victory_8":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload3_back", "none", "", "", "DefendSP_OpenExit", -1);
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			AddQuestRecord("Sharlie", "39");
			pchar.quest.DefendSP_final.win_condition.l1 = "Timer";
			pchar.quest.DefendSP_final.win_condition.l1.date.hour  = 9;
			pchar.quest.DefendSP_final.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.DefendSP_final.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.DefendSP_final.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.DefendSP_final.function = "DefendSP_finaltalk";
			// раздача экспы
			ChangeCharacterNationReputation(pchar, FRANCE, 30);
			ChangeCharacterComplexReputation(pchar, "nobility", 10);
			ChangeCharacterComplexReputation(pchar, "authority", 10);
			ChangeCharacterComplexReputation(pchar, "fame", 15);
			ChangeOfficersLoyality("good_all", 10);
			AddComplexSeaExpToScill(500, 500, 500, 500, 500, 500, 0);
			AddComplexSelfExpToScill(300, 300, 300, 300);
			AddCharacterExpToSkill(pchar, "Leadership", 2000);
			AddCharacterExpToSkill(pchar, "Fortune", 1000);
			AddSimpleRumour("All those residing in the French colony owe you, Captain. Defending Saint-Pierre from the vile attack of the Spanish is quite a feat!", FRANCE, 30, 15);
			AddSimpleRumour("It's an honor for me to speak with the brave Captain that has beaten a bunch of Spanish invaders hollow!", FRANCE, 30, 15);
			AddSimpleRumour("The French colonists may sleep in peace, while brave naval officers such as you are at the King's service!", FRANCE, 30, 15);
			AddSimpleRumourCity("We are all forever indebted to you, Captain! You have saved our colony from devastation!", "FortFrance", 30, 15, "");
			AddSimpleRumourCity("You are a brave and astute naval officer. All those residing in Saint-Pierre are praying for you, know that!", "FortFrance", 30, 15, "");
			AddSimpleRumourCity("You are the pride and joy of our nation and the hero of Saint-Pierre. We will never forget that!", "FortFrance", 30, 15, "");
			npchar.greeting = "mishelle_0";
		break;
		
		case "kukulkan":
			PlaySound("Voice\English\sharlie\mishelle-04.wav");
			dialog.text = " Alors, nous nous rencontrons à nouveau, "+pchar.name+"Malgré mes avertissements, tu as continué à me chercher et tes recherches t'ont mené bien loin...";
			link.l1 = "Michel ?... Pour une raison quelconque, cela ne me surprend pas. Miguel Dichoso est-il revenu à Tayasal pour un autre tas de trésors ? Hm-hm-hm. Oui, j'ai cherché à te rencontrer, cher frère. Je mourais d'envie de jeter un œil dans tes yeux sans vergogne. En plus de cela, ta tentative d'assassinat sur moi dans la crypte du cimetière a été la cerise sur le gâteau. Mais d'abord, dis-moi, comment devrais-je t'appeler ? Michel de Monper ou Miguel Dichoso ?";
			link.l1.go = "kukulkan_1";			
		break;
		
		case "kukulkan_1":
			dialog.text = "Ces noms n'ont plus d'importance, "+pchar.name+"C'est du passé, qui disparaîtra bientôt même de l'histoire elle-même. C'est maintenant le moment de vérité, vers lequel je me suis dirigé lentement pendant le long quart de siècle depuis que j'ai mis le pied à terre pour la première fois...";
			link.l1 = "Quoi ?!! Cela... cela ne peut être !!!";
			link.l1.go = "kukulkan_2";			
		break;
		
		case "kukulkan_2":
			dialog.text = "Oui, "+pchar.name+"Je vois à ton visage que tu comprends qui je suis, mais tu n'y crois pas. Je suis celui que tu as aspiré à rencontrer ces derniers mois. Celui avec qui le représentant de ton Dieu, l'Inquisiteur de Santiago, t'a béni pour le combat.";
			link.l1 = "Kukulcan ?!";
			link.l1.go = "kukulkan_change";			
		break;
		
		case "kukulkan_change":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Kanek");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.7);
		break;
		
		case "kukulkan_3":
			dialog.text = "Je suis d'accord, "+pchar.name+", qu'il est difficile à croire. La vie est plus compliquée et plus surprenante que n'importe quel conte de fées...";
			link.l1 = "J'étais prêt à tout, mais... mon frère !";
			link.l1.go = "kukulkan_4";			
		break;
		
		case "kukulkan_4":
			dialog.text = "Frère ? Seulement par le sang de père. Nous avons des mères différentes, "+pchar.name+". Sache que ma mère était la fille de Kanek, nommée Shochikezhal. Elle a été enlevée par des corsaires français sous le commandement du célèbre Nicolas Gotier après avoir imprudemment quitté Tayasal. Ils avaient décidé de l'asservir. Un homme nommé Serge Benoit était parmi eux.\nHonteux de l'acte de son capitaine, il l'a quitté, a pris le voile et maintenant tu le connais comme l'abbé Benoit. Henri de Monper, notre père, était alors officier de marine. Il a acheté Shochikezhal et l'a emmenée en France où elle m'a donné naissance. À peu près au même moment où tu es né aussi, "+pchar.name+". Ta mère est morte en te donnant naissance et notre père a déclaré que son épouse légitime avait donné naissance à des jumeaux.\nShochikezhal, ma mère, était devenue nourrice pour nous deux. Tu as été nourri avec le lait d'une femme indienne du peuple Itza, "+pchar.name+"! Plus tard, ta grand-mère du côté de ta mère a décidé de te prendre en charge pour te donner une éducation et tu as reçu le nom de ta mère - de Maure.";
			link.l1 = "Comment as-tu découvert tout cela ?!";
			link.l1.go = "kukulkan_5";			
		break;
		
		case "kukulkan_5":
			dialog.text = "Ne penserais-tu pas, frère, que je sais plus que les gens ordinaires ? De plus, notre père m'a beaucoup raconté et je suis au courant de beaucoup de choses... C'est comme on dit, au gré du vent.";
			link.l1 = "Maintenant tout est clair... Et qu'est-il arrivé à ta mère ? Pourquoi ne l'ai-je jamais vue ?";
			link.l1.go = "kukulkan_6";			
		break;
		
		case "kukulkan_6":
			dialog.text = "Elle est morte en sauvant ma vie. Un peu plus d'un an après ma naissance, j'ai failli mourir à cause d'une maladie. Ma mère, la fille d'un prêtre Itza, a réalisé pour moi une cérémonie secrète de guérison maya. Je me suis rétabli, mais cette cérémonie a été accompagnée de quelques... effets secondaires destructeurs sous forme de tonnerre, d'éclairs et d'un ouragan tropical. Shochikezhal a été dénoncée et accusée de sorcellerie et brûlée sur le bûcher de l'Inquisition...";
			link.l1 = "Et tu t'es amélioré...";
			link.l1.go = "kukulkan_7";			
		break;
		
		case "kukulkan_7":
			dialog.text = "En plus de me guérir, ce rituel m'a également conféré d'autres capacités, en plus d'ouvrir une connexion avec le monde des dieux. Et tu connais déjà le reste. Comme tu le sais déjà, je porterai la lumière du savoir et de l'expérience de la race blanche dans le passé et la transmettrai au peuple Maya. L'histoire sera réécrite et vous, les blancs, ne dominerez pas ce monde. Je m'en assurerai.";
			link.l1 = "Alors toute votre vie, étudier à la meilleure académie navale, servir dans l'armée et dans l'Ordre de Malte n'était en gros qu'une accumulation d'expérience militaire ?";
			link.l1.go = "kukulkan_8";			
		break;
		
		case "kukulkan_8":
			dialog.text = "Exactement. Quand j'ai réalisé que j'en savais assez, j'ai arrangé pour être envoyé dans les Caraïbes. J'ai convaincu le Chevalier de Poincy de créer une base en Martinique. Ensuite, je devais me rendre à Tayasal. Ce n'était pas vraiment une tâche simple pour moi, car ce vaisseau physique reste mortel et les portails dans les Caraïbes ne fonctionnaient pas correctement.";
			link.l1 = "Et tu es devenu Miguel Dichoso...";
			link.l1.go = "kukulkan_9";			
		break;
		
		case "kukulkan_9":
			dialog.text = " Cher frère, j'ai obtenu ce surnom sur les champs de bataille d'Europe. J'y ai aussi rencontré Ramon de Mendoza y Riba. Tu penses que la vie est faite de hasards ? Non, pas du tout, chaque hasard est une régularité inconnue. Beaucoup de choses ont été faites pour mon retour à Tayasal. J'ai dû vivre deux vies. Michel de Monper et Miguel Dichoso. J'ai aussi dû m'assurer que les gens croient qu'ils sont des personnes différentes.\nJ'ai dû pirater, tout comme toi, au service de de Poincy pour gagner sa confiance, sa faveur et son argent. J'ai dû assassiner Blaze Sharp, l'un des chefs des pirates, en faveur de Ramon de Mendoza, afin d'obtenir des soldats pour l'expédition.\nJ'ai dû tenter à la fois de Poincy et de Mendoza avec des récits des trésors de Tayasal. J'avais reçu sept cent cinquante mille pièces d'argent de la trésorerie de de Poincy et vendu la frégate militaire espagnole au pirate Dodson. Et puis l'expédition a eu lieu. Je suis retourné à Tayasal seulement pour subir un échec...";
			link.l1 = "Je comprends... Alors que tu n'étais qu'un garçon de cinq ans courant après les papillons dans le domaine de notre père, Kanek le grand prêtre, effrayé par l'invasion de Don Alonso de Maldonado à Tayasal, a soigneusement caché le masque de Kukulcan, si vital pour voyager dans le passé... je te prie de m'excuser, je voulais dire TON masque.";
			link.l1.go = "kukulkan_10";			
		break;
		
		case "kukulkan_10":
			dialog.text = "Oui, Kanek s'est surpassé là-bas. Il a exécuté le rituel le plus difficile, un rituel que même les anciens n'osaient pas accomplir. Il a caché le masque sur l'île déserte nouvellement créée et a réussi à perdre la clé de Ksocheatem - le soi-disant Gardien de la Vérité.\nJe devais jouer intelligemment. Le rituel empêchait tout navire transportant des objets protégés du trésor de Taysal de quitter les Caraïbes en jetant de tels navires sur les rivages de Ksocheatem. J'avais l'intention d'utiliser cela. J'ai pris suffisamment de trésors pour apaiser Mendoza. J'ai également pris un objet spécial protégé par le rituel.\nUn navire avec cet objet à bord serait condamné à être livré directement à Ksocheatem, directement à mon masque. Alors je suis allé en mer et ai fait savoir à Mendoza que j'existais.";
			link.l1 = " Alors, tu as quitté Tayasal tout seul ?";
			link.l1.go = "kukulkan_11";			
		break;
		
		case "kukulkan_11":
			dialog.text = "Tu veux dire sans les soldats de Mendoza ? Bien sûr. Tous les Espagnols ont été tués ici, à Tayasal. Les Itzas ont eux-mêmes apporté les trésors à la côte et j'ai dit à Mendoza que les soldats avaient été pris en embuscade par les Miskitos. Il m'a cru puisqu'il ne s'intéressait qu'à l'or et non aux gens.\nJe prévoyais de mettre le navire avec les trésors sous les canons du 'Gryffondor', mais tout s'est passé bien mieux : le baron a décidé d'envoyer les trésors en Espagne sous ma garde. C'était le meilleur résultat possible, je n'avais qu'à attendre que le navire traverse la frontière invisible des Caraïbes.\nCependant, il s'est avéré que le capitaine avait des ordres différents. J'ai découvert qu'une unité spéciale de bordée devait se mutiner dès que nous atteindrions l'océan Atlantique, tuant l'équipage et tous les officiers. Le capitaine avait pour ordre de rendre l'or indien à Mendoza par la suite.\nUn si bel exemplaire de la race blanche, n'est-ce pas, frère ? J'ai dû prendre le risque, je ne savais pas quand la mutinerie devait avoir lieu. Mais tout s'est déroulé selon le plan : la tempête nous a frappés dès que la 'Santa Quiteria' a atteint le côté est de l'île de Trinidad et Tobago. La frégate a été emportée de nouveau vers les Caraïbes en direction de Ksocheatem.\nJ'ai alors subi le plus grand échec de ma vie - une vague m'a emporté du navire et je me suis retrouvé à Le Marin Cove en Martinique quelques jours plus tard. Des pêcheurs m'ont trouvé et m'ont emmené à Le Francois. Mais les hommes de de Poincy m'ont capturé alors que je revenais à la vie chez Cesar Craig. Le 'Gryffondor' n'a pas trouvé la 'Santa Quiteria' à l'endroit que j'avais défini. Le chevalier de Poincy est devenu furieux dès qu'il a appris que l'or indien était parti avec l'argent pris dans le trésor de l'Ordre et ses propres économies.\nIl m'a fait arrêter. Il ne pouvait pas me tuer cependant, il ne le voulait pas. Il voulait de l'or. De l'or ! C'est la seule chose que ton peuple veut et à laquelle il tient ! Vous ferez n'importe quoi pour l'obtenir... J'étais dans une position terrible : je n'avais pas de masque sur moi et j'étais laissé à pourrir dans une cellule sans une seule pièce dans mes poches.\nC'est alors que je t'ai convoqué. Oui-oui, cher frère, tu étais censé me libérer, pour que je puisse faire ce pour quoi je suis né. Et tu as fait un travail extraordinaire. Il semble que le lait d'Itza que tu as tété t'a fait du bien.";
			link.l1 = "Ce qui m'intéresse, c'est sur quoi tu comptais lorsque tu t'es échappé de Saint-Pierre alors? Quel était ton plan?";
			link.l1.go = "kukulkan_12";			
		break;
		
		case "kukulkan_12":
			PlaySound("Voice\English\sharlie\mishelle-05.wav");
			dialog.text = "Tu étais mon plan depuis le début, frère. Kukulcan peut lire dans le cœur des gens. La lettre que je t'ai laissée chez l'Abbé était censée te faire agir. J'avais raison à ton sujet. Je suivais tes progrès depuis ta première rencontre avec l'Inquisiteur de Santiago. Tu as tout fait pour moi. Tu as façonné le Gardien de la Vérité. Tu as éliminé les concurrents. Tu as trouvé Ksocheatem.\nJ'étais là, te suivant. Bien que je ne m'attendais pas à ce que tu entres dans Tayasal. Tu as dépassé toutes mes attentes. Et avec ton aide, je ferai ce pour quoi je suis né. La raison pour laquelle je suis né en chair mortelle.";
			link.l1 = "Il y a juste un petit hic dans ton raisonnement, cher frère. Tu ne possèdes pas ton masque et tu n'es rien sans lui. Je l'ai. Et je ne brûle pas d'envie de te le donner. Je préférerais le réduire en miettes plutôt que de le laisser finir entre tes mains.";
			if (CheckCharacterItem(pchar, "mask_true")) link.l1.go = "kukulkan_13";	
			else link.l1.go = "kukulkan_14";			
		break;
		
		case "kukulkan_13":
			dialog.text = "Tu ne peux pas changer ce qui est prédéterminé par le destin. Je ne te permettrai pas d'endommager mon artefact. Je le sens... Il est avec toi. Et tu es ici, dans mon temple, sous toute ma puissance ! Tu ne quitteras jamais cet endroit. Il est temps pour ton ultime épreuve, cher frère, de voir quelle est ta valeur dans un combat contre Kukulcan !";
			link.l1 = "Je suppose que ton corps mortel peut encore saigner !";
			link.l1.go = "kukulkan_fight";		
		break;
		
		case "kukulkan_14":
			dialog.text = "Ha ! Je te plains, Charles. C'est vraiment triste. Mais tu mérites une chance de combattre un Dieu. Même si c'est inutile. Je te le dirai plus tard, si tu survis au premier acte.";
			link.l1 = "Je suppose que ton corps mortel peut encore saigner !";
			link.l1.go = "kukulkan_fight";			
		break;
		
		case "kukulkan_fight":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorTurnToLocator(pchar, "item", "button04");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocator(npchar, "quest", "defend1", "", -1);
			sld = characterFromId("Kanek");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocator(sld, "quest", "defend2", "", -1);
			DoQuestFunctionDelay("Tieyasal_TempleFightGuard", 3.0);
		break;
		
		case "kukulkan_twice": // развилка финалов - есть настоящая маска или нет
			if (CheckCharacterItem(pchar, "mask_true"))
			{
				dialog.text = "";
				link.l1 = "Il semble que vos pouvoirs vous quittent, grand Kukulcan... Vous êtes peut-être fort, mais votre corps est toujours mortel !";
				link.l1.go = "kukulkan_win";
			}
			else
			{
				dialog.text = "Je pense que cela suffira pour le divertissement. Vous êtes vraiment un maître d'épée et un grand combattant, j'oserais même dire le plus grand guerrier de votre temps, mais cette bataille, vous l'avez perdue, "+pchar.name+"I need to find my brother.";
				link.l1 = "Nous sommes juste...";
				link.l1.go = "kukulkan_fail";
			}
		break;
		
		case "kukulkan_fail":
			DialogExit();
			SetMusic("music_teleport");
			LAi_SetActorType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "attack_force_1", "Tieyasal_KukulkanKick", 1.0);
			LaunchBlast(npchar);
			PlaySound("Sea Battles\udar_metal_003.wav");
		break;
		
		case "kukulkan_fail_1":
			dialog.text = "Assez, cher frère. Tu ne peux résister à la puissance de Kukulcan quand il est uni à son artefact ! Je t'ai permis de rester en vie si longtemps juste pour voir ce que tu as réellement pu accomplir.";
			link.l1 = "Putain... Ce dernier coup... Mais de quel artefact parles-tu ? Le masque ? Il est avec moi !";
			link.l1.go = "kukulkan_fail_2";
		break;
		
		case "kukulkan_fail_2":
			dialog.text = "Pauvre, pauvre Capitaine "+GetFullName(pchar)+"... Vous êtes venu jusqu'ici, avez survécu à tous les dangers, abattu de nombreux ennemis les plus puissants pour finalement être vaincu à la fin !.. Le masque de jade que vous avez trouvé dans la boîte en métal près des épaves de la 'Santa Quiteria' sur Ksocheatem est un faux ! Ce n'est qu'un ancien masque du trésor de Taysal. CE N'EST PAS LE MASQUE DE KUKULCAN !.\nJe l'avais personnellement pris d'ici après ma malheureuse expédition, il est gardé par le rituel ancien. Ce masque était la raison pour laquelle la tempête avait emporté la Santa Quiteria vers Ksocheatem. Il avait aussi un second but. Il était censé tromper quiconque y venait pour mon véritable artefact.";
			link.l1 = "Mais... Où était donc le véritable masque ?! J'ai cherché partout dans Ksocheatem !..";
			link.l1.go = "kukulkan_fail_3";
		break;
		
		case "kukulkan_fail_3":
			dialog.text = "Tu n'as pas, "+pchar.name+". Mon artefact était situé de l'autre côté de l'île par rapport à la 'Santa Quiteria', dans un sanctuaire soigneusement gardé. La route y mène à travers des cavernes souterraines. C'est compliqué à trouver et pas évident pour l'œil inexquis d'un mortel. Le voilà ! Jette un bon coup d'œil dessus, un dernier coup d'œil...";
			link.l1 = "Ça ne peut pas être !";
			link.l1.go = "kukulkan_fail_4";
		break;
		
		case "kukulkan_fail_4":
			dialog.text = "Tu as survécu et remporté beaucoup de batailles, frère. Mais celle-ci, tu l'as perdue, "+pchar.name+"... ";
			link.l1 = "Et maintenant ?";
			link.l1.go = "kukulkan_fail_5";
		break;
		
		case "kukulkan_fail_5":
			dialog.text = "Je voyagerai directement au dixième siècle, sept siècles en arrière. Cela suffira à la civilisation maya pour atteindre une puissance militaire et scientifique inébranlable sur la race blanche.";
			link.l1 = "Et qu'adviendra-t-il de notre monde? Disparaîtra-t-il?";
			link.l1.go = "kukulkan_fail_6";
		break;
		
		case "kukulkan_fail_6":
			dialog.text = "Non. Cela changera. Peut-être qu'il y aura une place pour toi, mais tu ne te souviendras de rien de ce qui s'est passé dans ce monde. Certains de ceux qui sont nés ici ne naîtront jamais là-bas, l'inverse est également vrai. Les morts reviendront à la vie et les vivants mourront, d'une manière ou d'une autre, chacun renaîtra. Suum cuique, à chacun son dû, "+pchar.name+"Ne crains rien, petit frère. Tu ne réaliseras jamais ce qui s'est passé et tu embrasseras naturellement la nouvelle réalité. Seul moi, Kukulcan, garderai les souvenirs... Mais assez parlé ! Kanek a déjà tout préparé pour le rituel. Tu me suivras, "+GetFullName(pchar)+", et tu seras témoin des derniers instants de l'existence de cette réalité que tu étais si avide de préserver.";
			link.l1 = "... ";
			link.l1.go = "kukulkan_fail_7";
		break;
		
		case "kukulkan_fail_7":
			DialogExit();
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("Tieyasal_Fail_ReloadTown", 2.0);
		break;
		
		case "kukulkan_fail_8":
			dialog.text = "Les portes du temps se sont ouvertes ! Réjouissez-vous, mes enfants, car vous êtes si proches de la grandeur ! Nous créerons le nouveau monde, un monde sans place pour les pâles envahisseurs !\nAdieu, "+pchar.name+", et sois prêt à accepter ton nouveau destin, quel qu'il soit. Suum cuique!";
			link.l1 = "... ";
			link.l1.go = "kukulkan_fail_9";
		break;
		
		case "kukulkan_fail_9":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "goto", "kukulkan", "", -1);
			DoQuestCheckDelay("Tieyasal_Fail_TeleportStart", 4.0);
		break;
		
		case "kukulkan_win":
			dialog.text = "Cette bataille n'est pas encore terminée, mortel. Tu es considérablement épuisé et j'ai des renforts en route ! Tu me rendras mon artefact. Sinon je le prendrai sur ton cadavre, cela ne fait aucune différence pour moi...";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Tieyasal_PrepareToWinBattle");
		break;
		
		case "kukulkan_win_1":
			dialog.text = "Urakan ! Je t'ordonne de tuer cet homme immédiatement !";
			link.l1 = "...";
			link.l1.go = "kukulkan_win_2";
		break;
		
		case "kukulkan_win_2":
			dialog.text = "Urakan ! Ne m'as-tu pas entendu ? Je répète : je t'ordonne, ainsi qu'à tes guerriers, de capturer et tuer cet homme !";
			link.l1 = "...";
			link.l1.go = "kukulkan_win_3";
		break;
		
		case "kukulkan_win_3":
			dialog.text = "Urakan ! Que diable ? Kanek ! Répète mon ordre à ton foutu fils !!!";
			link.l1 = "...";
			link.l1.go = "kukulkan_win_4";
		break;
		
		case "kukulkan_win_4":
			DialogExit();
			sld = characterFromId("Kanek");
			sld.dialog.currentnode = "kanek_2";
			LAi_SetActorType(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;
		
		case "kukulkan_win_5":
			dialog.text = "Tu trahis ton peuple, Urakan ! Tu as fléchi face à de telles transformations éminentes ! Guerriers, je vous ordonne de capturer et de mettre à mort non seulement cet homme qui se prétend mon frère, mais aussi Urakan le traître !";
			link.l1 = "Guerriers, au nom de Cavil et Hurakan, je vous ordonne de rester où vous êtes, si vous tenez à votre vie ! Aucun de vous ne survivra à un combat contre Cavil ! Que les dieux décident eux-mêmes lequel d'entre eux est le plus fort sur Terre !";
			link.l1.go = "kukulkan_win_6";
		break;
		
		case "kukulkan_win_6":
			DialogExit();
			LAi_SetActorType(PChar);
			LAi_ActorTurnToCharacter(PChar, characterFromID("Mishelle"));
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			PChar = GetMainCharacter();
			LAi_SetPlayerType(PChar);
			sld = characterFromId("Mishelle");
			sld.dialog.currentnode = "kukulkan_win_7";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.8);
		break;
		
		case "kukulkan_win_7":
			dialog.text = "";
			link.l1 = "Cette journée devient de mieux en mieux. Tu ne t'attendais pas à une telle tournure des événements, n'est-ce pas, frère? Les dieux doivent décider eux-mêmes qui d'entre eux est vraiment le plus fort. Et chacun recevra ce qu'il mérite, Michel. Suum cuique! À chacun son dû...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Tieyasal_WinBattleStart");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
