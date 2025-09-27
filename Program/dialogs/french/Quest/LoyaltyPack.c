void ProcessDialogEvent()
{
	ref NPChar, sld, rItm, rItem;
	aref Link, NextDiag, rType;
	int i, n;
	string sTemp, sStr, sStr2, sGun, sBullet, attrL;
	
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
			dialog.text = "Что вам надо?";
			link.l1 = "Ничего.";
			link.l1.go = "exit";
		break;
		
		case "Alonso":
			NextDiag.TempNode = "Alonso";
			
			if (GetDLCenabled(DLC_APPID_1))
			{
				if(CheckAttributeEqualTo(pchar, "questTemp.LoyaltyPack.FirstStage", "ready"))
				{
					dialog.text = "Permission de parler, cap'taine ?";
					link.l1 = "Plus tard, Alonso.";
					link.l1.go = "exit";
					link.l2 = "Je vous écoute.";
					link.l2.go = "Alonso_1";
					break;
				}
				if(CheckAttributeEqualTo(pchar, "questTemp.LoyaltyPack.SecondStage", "ready"))
				{
					dialog.text = "Permission de parler, cap'taine ?";
					link.l1 = "Plus tard, Alonso.";
					link.l1.go = "exit";
					link.l2 = "Je vous écoute.";
					link.l2.go = "Alonso_Lvl_8_Start";
					break;
				}
				if(CheckAttributeEqualTo(pchar, "questTemp.LoyaltyPack.ThirdStage", "ready"))
				{
					dialog.text = "Permission de parler, cap'taine ?";
					link.l1 = "Plus tard, Alonso.";
					link.l1.go = "exit";
					link.l2 = "Je vous écoute.";
					link.l2.go = "Alonso_Lvl_12_Start";
					break;
				}
				if(CheckAttributeEqualTo(pchar, "questTemp.LoyaltyPack.FourthStage", "ready"))
				{
					dialog.text = "Permission de parler, cap'taine ?";
					link.l1 = "Plus tard, Alonso.";
					link.l1.go = "exit";
					link.l2 = "Je vous écoute.";
					link.l2.go = "Alonso_Lvl_16_Start";
					break;
				}
			}
			
			dialog.text = "Rien à signaler, cap'taine.";
			link.l1 = "Continuez, Alonso.";
			link.l1.go = "exit";
		break;
		
		case "Alonso_1":
			DelLandQuestMark(npchar);
			dialog.text = "Comment vous en sortez-vous ?";
			link.l1 = "Qu'est-ce que tu veux dire ?";
			link.l1.go = "Alonso_2";
		break;
		
		// Основная развилка стадии 1
        case "Alonso_2":
            dialog.text = "Voilà des mois que vous sillonnez ces eaux caribéennes, alors que certains ne survivent pas une semaine ici. L'équipage vous respecte, c'est certain, mais moi ? Je m'inquiète pour votre avenir.\n"+
                          "Partagez vos pensées, faites cette faveur à l'équipage. Où va le "+pchar.ship.name+" ?";
                          
            link.l1 = "Je n'ai pas de plan. Je veux d'abord explorer ces eaux. L'aventure nous trouvera d'elle-même.";
            link.l1.go = "Alonso_Choice_1";
            
            link.l2 = "Ces eaux sont pleines de prédateurs, Alonso. Et le "+pchar.ship.name+" est le plus petit d'entre eux. Pour l'instant.";
            link.l2.go = "Alonso_Choice_2";
            
            link.l3 = "J'aime gagner de l'argent. De préférence légalement. Mais on verra bien comment ça se passe.";
            link.l3.go = "Alonso_Choice_3";
			
            if (!SandBoxMode)
            {
                link.l4 = "Tu sais bien. Après cette conversation mémorable sur l'Ulysse, tout s'est compliqué…";
                link.l4.go = "Alonso_Choice_4";
            }
        break;
        
        case "Alonso_Choice_1":
            dialog.text = "Voilà la liberté ! L'essentiel, c'est d'avoir de quoi entretenir le navire et garder quelque chose dans les coffres pour les mauvais jours.\n"+
                          "Où que vous mènent l'humeur, la quête ou la carte au trésor - prenez des passagers, du fret, n'importe quel petit boulot sur votre route.\n"+
                          "Un peu de petit commerce ne fait pas de mal non plus - achetez bon marché là où c'est évident, vendez où vous pouvez.\n"+
                          "Et si vous croisez un marchand solitaire en chemin… Hé. Vous avez raison, cap'taine. L'aventure nous trouvera effectivement.";
            
            AddCharacterExpToSkill(pchar, SKILL_LEADERSHIP, 50);
            AddCharacterExpToSkill(pchar, SKILL_GRAPPLING, 50);
            AddCharacterExpToSkill(pchar, SKILL_COMMERCE, 50);
            
            link.l1 = "Merci pour le bon conseil, Alonso.";
            link.l1.go = "Alonso_Common_End";
        break;
        
        case "Alonso_Choice_2":
            dialog.text = "Affaire rentable, si le navire le permet. Trouvez les marchands isolés et montrez-leur ce que 'l'avare paie deux fois' veut vraiment dire.\n"+
                          "Malheureusement pour vous, un autre dicton entre en jeu : 'Rien ne reste caché éternellement'. Il y a toujours une langue bien pendue dans l'équipage qui racontera vos exploits au premier port.\n"+
                          "Alors soit vous pillez tous les pavillons un peu, soit vous choisissez votre ennemi pour la vie.\n"+
                          "Enfin, je m'emballe peut-être. Si ça devient vraiment chaud, il y a un avocat à Port-Royal qui règle tous les problèmes avec les autorités pour quelques pièces sonnantes. Appelons ça la taxe pirate, hé hé !";
            
            AddCharacterExpToSkill(pchar, SKILL_GRAPPLING, 50);
            AddCharacterExpToSkill(pchar, SKILL_ACCURACY, 50);
            ChangeCharacterComplexReputation(pchar, "nobility", -1);
            
            link.l1 = "Merci pour le bon conseil, Alonso.";
            link.l1.go = "Alonso_Common_End";
        break;
        
        case "Alonso_Choice_3":
            dialog.text = "Euh, là je ne peux pas vous aider, cap'taine. Il vous faut un vrai navire marchand : une barquantine, ou mieux, un trois-mâts barque. Je vais sûrement le regretter, mais prenez des canons légers ou jetez-les carrément.\n"+
                          "Prenez des contrats de fret chez les marchands, commercez pour votre compte en route et transportez des passagers.\n"+
                          "Quand vous aurez assez économisé, investissez dans des boutiques et des banques. Croyez-moi, cap'taine - un jour votre argent fera de l'argent, et vous pourrez vous offrir un grand navire avec deux cents gars à bord.\n"+
                          "Que d'ailleurs, ce n'est pas vous qui paierez, mais votre affaire.";
            
            AddCharacterExpToSkill(pchar, SKILL_COMMERCE, 50);
            AddCharacterExpToSkill(pchar, SKILL_SAILING, 50);
            ChangeCharacterComplexReputation(pchar, "nobility", 1);
            
            link.l1 = "Merci pour le bon conseil, Alonso.";
            link.l1.go = "Alonso_Common_End";
        break;
        
        case "Alonso_Choice_4":
            dialog.text = "Je vois les choses autrement, cap'taine. Sur l'Ulysse, vous n'étiez qu'un passager - ces pauvres âmes n'ont aucun contrôle sur leur destin. Maintenant vous êtes capitaine qui a gagné son chapeau, ce qui veut dire que vous pouvez résoudre n'importe quel problème. Je vous l'ai déjà dit - il n'y a pas de statut plus élevé dans notre monde.\n"+
                          "Mon instinct me dit que cette épopée avec votre frère va durer des années, alors occupez-vous d'abord de vous. Monsieur Michel ne va nulle part, hé hé…\n"+
                          "Vous n'êtes pas le seul à avoir des problèmes dans les Caraïbes. C'est le moment parfait pour aider les autres tout en gagnant de l'argent, de l'équipement et des contacts. Vous apprendrez tout ce dont vous aurez besoin pour cette affaire de famille en chemin…";
            
            AddCharacterExpToSkill(pchar, SKILL_LEADERSHIP, 100);
            ChangeCharacterComplexReputation(pchar, "nobility", 1);
            
            link.l1 = "Merci pour le bon conseil, Alonso.";
            link.l1.go = "Alonso_Common_End";
        break;
		
        case "Alonso_Common_End":
            dialog.text = "Ne vous limitez pas à un seul rôle, cap'taine. Faites seulement ce que vous voulez. Prenez tout et ne rendez rien. Tout ira bien.";
            link.l1 = "Et merci aussi pour les paroles de sagesse.";
            link.l1.go = "Alonso_Common_End_2";
        break;
        
        case "Alonso_Common_End_2":
            dialog.text = "Euh, c'est pour ça que vous me payez, cap'taine. Vous pensez que l'équipage suit vos ordres juste pour leur maigre solde ?\n"+
                          "Des dizaines d'hommes entassés dans un espace confiné, sans savoir quand ils reverront la terre, ou même s'ils la reverront. Et couler un navire ? Un jeu d'enfant.";
            link.l1 = "Oui, oui, je connais ce discours, Alonso. Qu'est-ce que tu disais sur les navires ?";
            link.l1.go = "Alonso_Common_End_3";
        break;
        
        case "Alonso_Common_End_3":
            dialog.text = "Hé ! Un navire, c'est une prison, un camp militaire et un monastère tout en un. Un rassemblement d'hommes, en somme. Alors les problèmes se règlent soit par la parole, soit par le fouet. Dans votre cas, le second, hé hé, n'est pas une option, alors j'ai voulu qu'on cause un peu. Pour vous faciliter les choses, quoi.";
            link.l1 = "As-tu déjà été en prison ? Dans l'armée ? Dans un monastère, Dieu nous en préserve ? Et d'ailleurs, Alonso, parle-moi de toi. Je ne sais presque rien sur toi.";
            link.l1.go = "Alonso_Story_1";
        break;
        
        // История Алонсо
        case "Alonso_Story_1":
            dialog.text = "Eh bien, les monastères, j'ai évité, je ne vais pas mentir. Cependant, j'ai servi dans la Sainte Inquisition une fois…";
            link.l1 = "Comment diable est-ce arrivé ?";
            link.l1.go = "Alonso_Story_2";
        break;
        
        case "Alonso_Story_2":
            dialog.text = "Oh ! C'était comme ça. J'ai tiré ma charge comme mercenaire dans la guerre européenne. Le diable sait comment ça a commencé ou qui se battait contre qui. Tout ce qu'on savait, c'est que la guerre durait depuis trente ans et quel commandant payait à peu près régulièrement. Ça, c'était une aventure !\n"+
                          "C'était en '42… ou était-ce en '41 ? Peu importe. Deux compagnies, toutes deux au service de l'Empereur, se sont rencontrées dans une forêt. Dans le brouillard. Et ont commencé à se massacrer ! Trois jours de carnage !";
            link.l1 = "Comment est-ce possible ?";
            link.l1.go = "Alonso_Story_3";
        break;
        
        case "Alonso_Story_3":
            dialog.text = "Essayez de distinguer ami d'ennemi dans ce brouillard. En plus, on n'avait pas été payés depuis trois mois, alors tout le monde pensait au butin.\n"+
                          "On s'est entretués à moitié. Quand on s'en est rendu compte, c'était trop tard. C'est là que j'ai rencontré ce Moscovite. Grand comme un ours, mais un cœur d'or !";
            link.l1 = "Et ensuite ?";
            link.l1.go = "Alonso_Story_4";
        break;
        
        case "Alonso_Story_4":
            dialog.text = "Vous savez comment c'est à la guerre ? Le premier à rapporter est le héros. Alors on s'est dit - autant tirer profit de ce désastre !\n"+
                          "On s'est mis d'accord avec les gars, on est allés voir le payeur, on a rapporté une 'glorieuse bataille'. Les morts n'ont plus touché de solde, les survivants ont été payés, mon ami et moi on a eu des primes, et le commandant sa part.";
            link.l1 = "Alors tu es riche, Alonso.";
            link.l1.go = "Alonso_Story_5";
        break;
        
        case "Alonso_Story_5":
            dialog.text = "Ha ! On a passé une semaine à boire du vin et jouer aux cartes. Heureusement, mon nouvel ami du lointain royaume de Moscou avait un faible pour les pièces rares, sinon j'aurais fini en prison pour dettes. Il m'a acheté un trophée : un magnifique pistolet à trois canons, et à bon prix. Il n'a pas profité de mon malheur.";
            link.l1 = "Une histoire fantastique, Alonso. J'ai l'impression que tu viens de l'inventer.";
            link.l1.go = "Alonso_Gift";
        break;
        
        // Вручение подарка
        case "Alonso_Gift":
            dialog.text = "Vous me blessez, cap'taine. Tenez, prenez ce petit cadeau.";
            link.l1 = "Qu'est-ce que c'est ?";
            link.l1.go = "Alonso_Gift_2";
        break;
        
        case "Alonso_Gift_2":
            // Выдаем Берендейку
            GiveItem2Character(pchar, "talisman20");
			SetAlchemyRecipeKnown("talisman20");
            
            dialog.text = "Une bandoulière pour le combat au mousquet. Dans la patrie de mon ami moscovite, tout le monde en porte. C'est ce qu'il disait.\n"+
                          "Qu'elle vous serve bien, cap'taine. Considérez ça comme un cadeau de l'équipage.";
            link.l1 = "Inattendu ! Merci, Alonso. Alors, ce service dans l'Inquisition ?";
            link.l1.go = "Alonso_Escape";
        break;
        
        case "Alonso_Escape":
            PlaySound("ambient\SEA\Ship_bell_Two.wav");
            dialog.text = "Euh…\n"+
                          "Les cloches sonnent, cap'taine ! Il est temps de retourner au travail. On continuera une autre fois.";
            link.l1 = "On continuera certainement cette conversation. Merci pour le cadeau !";
            link.l1.go = "exit";
            
			AddDialogExitQuestFunction("LoyaltyPack_FirstStage_DlgExit");
        break;
		
		// (Уровень 8) - Продолжаем историю
        case "Alonso_Lvl_8_Start":
			DelLandQuestMark(npchar);
			dialog.text = "Vous avez beaucoup accompli depuis notre dernière conversation, et personne - ni l'équipage, ni moi - ne doute plus de vos talents.";
			link.l1 = "Il y avait des doutes ?";
			link.l1.go = "Alonso_Lvl_8_1";
        break;

        case "Alonso_Lvl_8_1":
            dialog.text = "Bien sûr qu'il y en avait. On est des gens simples - habitués à se préparer au pire. Profitez de votre liberté, cap'taine. Continuez comme ça et vous verrez un tout autre côté des Caraïbes.";
            link.l1 = "Ravi de l'entendre. Maintenant, parle-moi de ton service dans l'Inquisition. La dernière fois, tu as commencé avec une histoire d'armée et tu as fini avec elle aussi.";
            link.l1.go = "Alonso_Lvl_8_2";
        break;

        case "Alonso_Lvl_8_2":
            dialog.text = "Qu'y a-t-il à raconter ? Après ce massacre insensé mais très rentable dans la forêt, le Moscovite et moi sommes devenus inséparables et avons monté pas mal d'autres coups.\n"+
                          "Je me souviens qu'on a décidé de piller un convoi impérial une fois. Les éclaireurs disaient qu'ils transportaient des trophées, de l'or, des armes...";
            link.l1 = "Et alors, vous avez réussi ?";
            link.l1.go = "Alonso_Lvl_8_3";
        break;

        case "Alonso_Lvl_8_3":
            dialog.text = "Un jeu d'enfant. On a attaqué des deux côtés, dispersé les gardes, ouvert les chariots - et trouvé du chou ! Du chou pourri et puant pour une garnison ! Mais vous savez quoi ? On n'avait pas bouffé depuis une semaine, alors même ça nous a réjouis !";
            link.l1 = "Comme si la nourriture sur mon navire était meilleure.";
            link.l1.go = "Alonso_Lvl_8_4";
        break;

        case "Alonso_Lvl_8_4":
            dialog.text = "Bon, maintenant j'y suis habitué. Mais à l'époque... Après une semaine à se nourrir sur le terrain, on aurait rongé l'écorce des arbres !\n"+
                          "Mais mon ami n'a pas perdu courage. Il a sorti sa flasque avec sa mixture spéciale - recette moscovite, qu'il disait. On s'en fichait, pourvu que ce ne soit pas du vinaigre ! Après quelques gorgées, même ce chou avait un goût de festin !";
            link.l1 = "Dégoûtant.";
            link.l1.go = "Alonso_Lvl_8_5";
        break;

        case "Alonso_Lvl_8_5":
            dialog.text = "Ce qui est dégoûtant, c'est l'état de nos tonneaux d'eau, mais cette gnôle moscovite m'a sauvé la vie ce jour-là.";
            link.l1 = "Comment ça ?";
            link.l1.go = "Alonso_Lvl_8_6";
        break;

        case "Alonso_Lvl_8_6":
            dialog.text = "On s'est soûlés comme des polonais là, dans la boue de la route avec des choux qui flottaient. Bon, de fil en aiguille, je me suis disputé avec un petit noble. Un Allemand, tout propret et pompeux. Trop bien pour boire avec nous, il nettoyait juste son mousquet en lançant des piques.\n"+
                          "Donc on est là, assis, à noyer notre chagrin au-dessus du chou. Et il commence à nous faire la leçon sur la sagesse militaire. Que nos fidèles sabres et piques seront bientôt oubliés, mais la baïonnette - voilà l'avenir et la clé de tout.\n"+
                          "Alors je me suis disputé avec lui, et on s'est mis d'accord pour se battre à mort - à la baïonnette, rien que ça. Ne me demandez pas comment c'est arrivé, je ne m'en souviens pas moi-même.\n"+
                          "Mais on n'avait que deux baïonnettes dans toute la compagnie. Une appartenait à ce petit officier, l'autre à Fox, un Anglais. J'ai emprunté son fusil et j'ai battu l'Allemand à mort avec, puis j'ai filé.";
            link.l1 = "Mais tu étais affamé et ivre.";
            link.l1.go = "Alonso_Lvl_8_7";
        break;

        case "Alonso_Lvl_8_7":
            dialog.text = "J'ai compris plus tard que la mixture de mon ami stabilise vraiment la main quand on se bat avec un lourd mousquet. Donc maintenant je suis plus enclin à être d'accord avec les idées de l'Allemand mort.";
            link.l1 = "Et quel rapport avec ton service dans l'Inquisition ?";
            link.l1.go = "Alonso_Lvl_8_Gift";
        break;

        case "Alonso_Lvl_8_Gift":
            dialog.text = "Vous ne me croyez pas encore, cap'taine ! Tenez, prenez ça.";
            link.l1 = "Une bouteille et un bout de papier ?";
            link.l1.go = "Alonso_Lvl_8_Gift_2";
        break;

        case "Alonso_Lvl_8_Gift_2":
            // Даём игроку настойку и рецепт
            GiveItem2Character(pchar, "vodka");
            SetAlchemyRecipeKnown("vodka");

            dialog.text = "C'est la mixture dont je vous parlais. Et la recette. Au cas où ça vous plairait, hé hé.";
            link.l1 = "Désolé, mon ami, mais des gribouillis et une mixture trouble ne…";
            link.l1.go = "Alonso_Lvl_8_Gift_3";
        break;

        case "Alonso_Lvl_8_Gift_3":
            // Даём игроку мушкет с багинетом
            GiveItem2Character(pchar, "mushket10");

            dialog.text = "D'accord, d'accord, cap'taine. J'allais vous l'offrir de toute façon. Ce genre d'arme ne me va pas, mais vous la trouverez utile. Les baïonnettes sont des bêtes rares. Mais une fois que vous saurez vous en servir, vous oublierez les sabres.";
            link.l1 = "Attends, c'est le mousquet de cet officier impérial ? Celui que tu as tué ?";
            link.l1.go = "Alonso_Lvl_8_Gift_4";
        break;

        case "Alonso_Lvl_8_Gift_4":
			PlaySound("ambient\SEA\Ship_bell_Two.wav");
            dialog.text = "Le même. Comme vous pouvez voir, je vous ai dit la vérité, cap'taine.";
            link.l1 = "Mais ce n'est pas ce que j'ai demandé.";
            link.l1.go = "Alonso_Lvl_8_Escape";
        break;

        case "Alonso_Lvl_8_Escape":
            dialog.text = "Les cloches sonnent, cap'taine ! Il est temps de retourner au travail. On continuera une autre fois.";
            link.l1 = "On continuera certainement cette conversation. Merci pour le mousquet !";
            link.l1.go = "exit";
			AddDialogExitQuestFunction("LoyaltyPack_SecondStage_DlgExit");
        break;

        // (Уровень 12)
        case "Alonso_Lvl_12_Start":
			DelLandQuestMark(npchar);
			dialog.text = "Capitaine, concernant les nouvelles recrues...";
			link.l1 = "Il s'est passé quelque chose ?";
			link.l1.go = "Alonso_Lvl_12_1";
        break;

        case "Alonso_Lvl_12_1":
            dialog.text = "Je voulais vous signaler qu'au souper, une des recrues a mentionné qu'il voulait spécifiquement s'engager sur votre navire.";
            link.l1 = "Et qu'est-ce que ça signifie exactement ?";
            link.l1.go = "Alonso_Lvl_12_2";
        break;

        case "Alonso_Lvl_12_2":
            dialog.text = "Que bientôt il pourrait y en avoir d'autres comme lui. Vous avez un nom maintenant, cap'taine.";
            link.l1 = "Drôle que je ne sache toujours pas ce qui se cache derrière ton nom. Tu n'as jamais fini cette histoire sur l'Inquisition.";
            link.l1.go = "Alonso_Lvl_12_3";
        break;

        case "Alonso_Lvl_12_3":
            dialog.text = "Oh, où en étais-je... Ah oui ! On s'est lancés comme fournisseurs militaires. La guerre touchait à sa fin, fallait penser à l'avenir. Et mon ami avait toujours la tête pleine de projets d'avenir.";
            link.l1 = "C'est un sacré bond de carrière. Il n'y a pas si longtemps, vous vous soûliez près d'un chariot pillé plein de choux.";
            link.l1.go = "Alonso_Lvl_12_4";
        break;

        case "Alonso_Lvl_12_4":
            dialog.text = "Et alors ? On a reçu une commande de cent casques pour un régiment. Avec une belle avance aussi. On était contents, on est allés fêter ça... On a joué aux cartes.\n"+
                          "Au matin on se réveille --- l'avance a disparu, l'armée part dans deux jours, et on n'a pas un seul casque !";
            link.l1 = "Et qu'est-ce que vous avez fait ?";
            link.l1.go = "Alonso_Lvl_12_5";
        break;

        case "Alonso_Lvl_12_5":
            dialog.text = "On est allés sur le champ de bataille récent, on a ramassé les chapeaux des morts. Puis on a cloué des bouts de métal, attaché des plaques... Ça avait l'air ridicule, mais ça marchait ! Ça pouvait sauver d'un coup de sabre. Enfin, au moins une fois. Aussi bon qu'un casque, non ?!";
            link.l1 = "Le quartier-maître a-t-il apprécié votre ingéniosité ?";
            link.l1.go = "Alonso_Lvl_12_6";
        break;

        case "Alonso_Lvl_12_6":
            dialog.text = "Il nous a envoyés au tribunal pour détournement et fraude. Mais vous savez quoi ? Les soldats ont dit après que ces chapeaux leur avaient sauvé la vie plus d'une fois. Et la nôtre aussi, en fin de compte.";
            link.l1 = "Comment ça ?";
            link.l1.go = "Alonso_Lvl_12_7";
        break;

        case "Alonso_Lvl_12_7":
            dialog.text = "Eh bien, on s'est retrouvés tous les deux en prison. Et notre compagnie a été envoyée en mission. Je ne sais pas où ni contre qui, et eux non plus probablement. Ils ne sont jamais revenus.\n"+
                          "...\n"+
                          "Pardon, cap'taine. On continuera une autre fois. Prenez ce chapeau et les instructions. Je l'ai fabriqué hier pour vous remonter le moral... Mais je me suis juste attristé pour rien.";
            link.l1 = "Bien sûr, Alonso. Merci pour le cadeau.";
            link.l1.go = "Alonso_Lvl_12_Gift";
        break;

        case "Alonso_Lvl_12_Gift":
            // Даём игроку шляпу
            GiveItem2Character(pchar, "hat10");
            SetAlchemyRecipeKnown("Hat10");

            DialogExit();
			AddDialogExitQuestFunction("LoyaltyPack_ThirdStage_DlgExit");
        break;

        // (Уровень 16) - Финальный
        case "Alonso_Lvl_16_Start":
			DelLandQuestMark(npchar);
			dialog.text = "Capitaine, je voulais juste vous signaler que votre équipage est reçu comme des rois dans les tavernes et les bordels. Servir sous votre pavillon, ça compte de nos jours !";
			link.l1 = "Merci, Alonso... Dommage que je ne voie pas encore beaucoup de ce \"traitement royal\" pour moi-même.";
			link.l1.go = "Alonso_Lvl_16_1";
        break;

        case "Alonso_Lvl_16_1":
            dialog.text = "Ça viendra bientôt. Les Caraïbes sont un gâteau partagé entre quelques douzaines de capitaines. Bientôt vous aurez votre place à cette table et prendrez votre part.\n"+
                          "Et qui sait ? Peut-être serez-vous la légende des Caraïbes qui prendra tout le gâteau.";
            link.l1 = "Alors, tu vas finir ton histoire ? On s'était arrêtés au moment où tu t'es retrouvé en prison.";
            link.l1.go = "Alonso_Lvl_16_2";
        break;

        case "Alonso_Lvl_16_2":
            dialog.text = "Ha ! L'affaire des grands voleurs de chapeaux. Un Moscovite et un Portugais dans une cellule minuscule quelque part en Flandre. En attente de sentence. La mort, naturellement.\n"+
                          "Un gentleman important nous a sauvés - c'était l'ambassadeur moscovite ! Un vieil ami de Fadey. Il était de passage, a entendu parler de notre malheur, nous a rachetés !";
            link.l1 = "Fadey ? LE Fadey ? Et tu n'as rien dit ?!";
            link.l1.go = "Alonso_Lvl_16_3";
        break;

        case "Alonso_Lvl_16_3":
            dialog.text = "Ouais. C'est là qu'on s'est séparés : lui est retourné à Moscou, soit pour combattre les Polonais, soit pour de grosses affaires. Moi j'ai encore traîné dans le vieux pays, et me voilà.";
            link.l1 = "Impressionnant, Alonso. Tout ce temps et tu as réussi à me raconter tout sauf sur toi-même. Étrange qu'un gars malin comme toi ait laissé échapper cette histoire d'Inquisition.";
            link.l1.go = "Alonso_Lvl_16_4";
        break;

        case "Alonso_Lvl_16_4":
            dialog.text = "Et j'ai dit la pure vérité, cap'taine ! Vous ne me croyez pas - demandez à Fadey lui-même. Il n'est pas difficile à trouver à Basse-Terre.";
            link.l1 = "Peut-être que je le ferai. Et mon cadeau alors ?";
            link.l1.go = "Alonso_Lvl_16_5";
        break;

        case "Alonso_Lvl_16_5":
            dialog.text = "Hein ?";
            link.l1 = "Tu m'as fait un cadeau à la fin de chaque histoire.";
            link.l1.go = "Alonso_Lvl_16_Escape";
        break;

        case "Alonso_Lvl_16_Escape":
			PlaySound("ambient\SEA\Ship_bell_Two.wav");
            dialog.text = "Vous entendez ? Les cloches sonnent. Il est temps de travailler.";
            link.l1 = "Continuez, Alonso.";
            link.l1.go = "exit";
			AddDialogExitQuestFunction("LoyaltyPack_FourthStage_DlgExit");
        break;
	}
} 