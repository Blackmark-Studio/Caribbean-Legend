// Мэри Каспер - взаимная любовь и офицер
void ProcessDialogEvent()
{
	ref NPChar, sld, rItm, rItem;
	aref Link, NextDiag, rType;
	int i;
	int iTime, iAddTime;
	string 	sTemp, sAttr, sGun, sBullet, attrL;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	sAttr = Dialog.CurrentNode;
	if (findsubstr(sAttr, "SetGunBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	NPChar.SetGunBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
 	    Dialog.CurrentNode = "SetGunBullets2";
 	}
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "De quoi as-tu besoin ?";
			link.l1 = "Non, c'est rien.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
	// ---------------------------------покушение на Акулу - вариант R --------------------------------
		// разговор в каюте Адольфа
		case "Cabin":
			dialog.text = "Marcello, je le connais. Il est un ami de Rivados et des pirates. Adolf ne travaillerait jamais avec lui. Sens l'air... perçois-tu l'odeur de la poudre à canon ? Et il y a du sang sur le mur... Il a tué Adolf et essaie maintenant de nous duper ! Il doit travailler pour l'amiral ! Tue-le !";
			link.l1 = "...";
			link.l1.go = "Cabin_fight";
		break;
		
		case "Cabin_fight":
			chrDisableReloadToLocation = true;//закрыть локацию
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			DialogExit();
			sld = characterFromId("Marchello");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt.TownAttack"))
			{
				for (i=1; i<=3; i++)
				{
					sld = characterFromId("CyclopGuard_"+i);
					LAi_SetWarriorType(sld);
					LAi_group_MoveCharacter(sld, "EnemyFight");
				}
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "LSC_CyclopNMaryDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		// на улице
		case "Town":
			dialog.text = "Oh, excusez-moi... Puis-je vous demander de l'aide ?";
			link.l1 = "Hm. Je suis toujours prêt à aider une belle dame. Quel est le problème ?";
			link.l1.go = "Town_1";
		break;
		
		case "Town_1":
			dialog.text = "Tu vois, j'ai acheté un coffre rempli de toutes sortes de pièces métalliques à Sessile Gallard. Elle vit sur l'‘Eva’. Jurgen a promis de me forger une bonne chose, ouais, hein ? Je l'ai acheté, aye, mais je ne peux pas le lui apporter. Quelle folie de ma part !\nPeut-être pourrais-tu m'aider à transporter le coffre de l'‘Eva’ au bloc du Narwhal sur l'‘Esmeralda’ ? S'il te plaît, je te serais très reconnaissante !";
			link.l1 = "Et c'est tout ? Bien sûr, mademoiselle, je vais vous aider. Pas grand-chose comme tracas.";
			link.l1.go = "Town_2";
		break;
		
		case "Town_2":
			dialog.text = "Merci ! Je vais te montrer le coffre.";
			link.l1 = "Milady...";
			link.l1.go = "Town_3";
		break;
		
		case "Town_3":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "reload", "reload41", "LSC_EnterAevaWithMary", -1);
			LAi_ActorFollow(pchar, npchar, "", -1);
		break;
		
		case "Town_4":
			dialog.text = "Et nous y voilà... Maintenant dis-moi, salaud, où est la clé ?!";
			link.l1 = "Wow ! Ha, il semble qu'aucune aide ne soit nécessaire... Mary.";
			link.l1.go = "Town_5";
		break;
		
		case "Town_5":
			dialog.text = "Garçon malin, hein ? Moins de paroles, bon sang ! Où est la clé ? Donne-la moi ou tu le regretteras !";
			link.l1 = "Quelle impolitesse ! Une si mauvaise langue pour une si belle fille. Quelle clé ?";
			link.l1.go = "Town_6";
		break;
		
		case "Town_6":
			dialog.text = "La clef que tu as prise à Adolf Barbier. Et ne le nie pas - On t'a vu quitter sa cabine. Adolf est mort et c'est ton oeuvre... Maintenant, donne-moi la clef !";
			link.l1 = "Alors c'était toi après tout... C'était une erreur, fille, une très grosse erreur !";
			link.l1.go = "Town_7";
		break;
		
		case "Town_7":
			PlaySound("Voice\English\LSC\Mary Casper-04.wav");
			dialog.text = "Qu'as-tu dit ?... Bon sang, tu n'es pas un simple bandit ! Il travaille pour l'amiral ! Abattez-le, les gars !";
			link.l1 = "I think we make a great team, don't you, alright?";
			link.l1.go = "Cabin_fight";
		break;
		
	// ---------------------------------покушение на Акулу - вариант N --------------------------------
		case "caroline":
			dialog.text = "Chad, c’est lui ! Bon sang, il a amené un complice ici ! Les gars, tuez-les tous !";
			link.l1 = "...";
			link.l1.go = "caroline_1";
		break;
		
		case "caroline_1":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			// Акулу к бою
			sld = characterFromId("Dodson");
			LAi_SetImmortal(sld, false);
			LAi_SetWarriorType(sld);
			sld.cirassId = Items_FindItemIdx("cirass1");
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			// устанавливаем 4 толстых нарвалов
			int iRank = 20+MOD_SKILL_ENEMY_RATE*2;
			int iScl = 65;
			for (i=1; i<=4; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("MaryGuard_"+i, "citiz_5"+(i+4), "man", "man", iRank, PIRATE, -1, true, "soldier"));
				if(i == 4) 
				{
					FantomMakeCoolFighter(sld, iRank, iScl, iScl, "topor_07", "pistol11", "bullet", iScl*2);
					sld.DontClearDead = true;
					sld.SaveItemsForDead = true;
				}
				else FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_19", "pistol5", "bullet", iScl*2);
				if (i < 3) ChangeCharacterAddressGroup(sld, "CarolineBank", "reload", "reload3");
				else ChangeCharacterAddressGroup(sld, "CarolineBank", "reload", "reload2");
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			// Мэри и Чада к бою
			sld = characterFromId("Capper");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "LSC_MarynChadDie");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
	// ---------------------------------покушение на Акулу - вариант M --------------------------------
		case "mary":
			dialog.text = "Tu arrives juste à temps... Je n'aurais jamais pu m'occuper d'eux toute seule... Pouah ! Pour être honnête, je pensais que c'en était fini de moi !";
			link.l1 = "Tu t'es battue comme une Valkyrie ! Je n'ai jamais vu une si belle fille se battre avec autant de vigueur...";
			link.l1.go = "mary_1";
		break;
		
		case "mary_1":
			dialog.text = "Ha-ha, tu es un vrai gentleman, n’est-ce pas : à faire des compliments l’épée encore à la main. Merci pour ton aide. Tu m’as sauvé la vie, ouais, hein ? Présente-toi, gentleman, je ne t’ai jamais vu auparavant. Es-tu nouveau ici ?";
			link.l1 = "Mon nom est "+GetFullName(pchar)+", mais les belles dames peuvent m'appeler "+pchar.name+". . Suis-je nouvelle ici ? Hm... Je le suis.";
			link.l1.go = "mary_2";
		break;
		
		case "mary_2":
			dialog.text = "Ça se voit, parce que sinon j’aurais déjà repéré un beau gosse comme toi. Eh bien, moi c’est Mary. Mary Casper, mais tout le monde ici m’appelle Mary la Rousse. C’est parce que je suis rousse, ouais, hein ?";
			link.l1 = "Je suis ravi de te rencontrer, Mary...";
			link.l1.go = "mary_3";
		break;
		
		case "mary_3":
			dialog.text = "Oh, je suis doublement heureuse... considérant que j'aurais été morte sans toi ! Ce salaud de Chad ne bluffait pas. Quel vermine ! Et j'ai été idiote de laisser les portes du bas ouvertes. C'est ainsi que tu es entré, n'est-ce pas ?";
			link.l1 = "Oui. Je nageais autour de l'île en essayant de trouver un endroit pour sortir.";
			link.l1.go = "mary_4";
		break;
		
		case "mary_4":
			dialog.text = "Je vois. Cette porte déverrouillée a failli me tuer. Jurgen lui-même a forgé les serrures pour moi, tu ne peux pas les ouvrir sans la bonne clé et crocheter n'aidera pas. De plus, je ne resterai pas immobile pendant que quelqu'un essaie d'entrer - les quatre canons de mon pistolet laisseront quatre trous dans une porte ou un corps, ha-ha !\nMais ce foutu Chad ne me laissera pas tranquille. Il a déjà envoyé des coupe-jarrets pour me 'persuader' de prendre son parti, il est définitivement sérieux à ce sujet. Si ce n'était pas pour toi, j'aurais dit oui. Je vais devoir rester ici assiégé, "+pchar.name+"Merci le ciel, j'avais prévu cela, j'ai assez de provisions et Jurgen est mon voisin, je ne me suis pas disputée avec lui, ouais, hein ?";
			link.l1 = "Mary, pourquoi ne me dis-tu pas plus au sujet de tes problèmes ? Je vois que tu as besoin de mon aide, mais je n'ai rien compris de ce qui est sorti de tes lèvres.";
			link.l1.go = "mary_5";
		break;
		
		case "mary_5":
			dialog.text = "Oui, j'ai besoin d'aide, ouais, hein ? Je suis seule maintenant. J'ai eu une dispute avec Donald, puis Chad s'est avéré être un scélérat. Oh, je suis désolée, je bavarde encore. Bon, je vais te raconter la situation dans laquelle je me trouve...";
			link.l1 = "Garde à l'esprit que je suis nouveau ici, donc je ne comprends pas encore grand-chose. Qui est ce Chad qui essaie de te 'persuader' ou de te tuer ? Qui est Donald ?";
			link.l1.go = "mary_6";
		break;
		
		case "mary_6":
			dialog.text = "Chad est un pirate de l'équipage de l'amiral Shark Dodson, un geôlier sur le 'Tartarus'...";
			link.l1 = "Attends ! Qu'as-tu dit ? Shark Dodson ? Il est ici ?";
			link.l1.go = "mary_7";
		break;
		
		case "mary_7":
			dialog.text = "Tu as dû arriver cette nuit puisque tu ne sais pas déjà cela. Où d'autre serait Shark, sinon ici ? Mes ennuis ont commencé quand il est arrivé ici il y a plusieurs mois. Bien que, je l'admets, tout cela est la faute des Narvals et des Rivados. Quand Shark est venu ici avec son équipage, il voulait établir une base, mais notre peuple et les Rivados n'aimaient pas du tout l'idée. Ils ont attaqué la goélette de Shark la nuit et l'ont incendiée\nIls n'auraient pas dû ! L'équipage de Shark est plein de démons, pas d'hommes, ouais, hein ? D'abord, ils ont détruit les bateaux hostiles, puis ont débarqué et ont commencé un vrai massacre. Les Narvals se sont retirés et les Rivados se sont enfuis aussi vite qu'ils ont pu. Finalement, les pirates ont capturé San Augustine où se trouvent la plupart des provisions et des fournitures de l'île, puis ils ont pris Tartarus\nShark a emprisonné notre chef Alan Milrow, qui était aussi mon... mon ami proche, et le sorcier Rivados Chimiset. Il les a envoyés pourrir dans les cages de Tartarus comme des bêtes. Il est facile de nager jusqu'à Tartarus d'ici et j'ai réussi à rendre visite à Alan quelques fois. Là, j'ai rencontré Chad Kapper, Shark l'a assigné comme geôlier. J'ai demandé à Chad de libérer Alan, je lui ai promis de l'argent, mais il avait peur de confronter l'amiral\nEt puis Alan a été assassiné en prison. Chad m'a dit que Shark avait fait cela, ouais, hein. Alors je suis allée voir Donald, qui a été élu chef à la place d'Alan, et j'ai exigé d'attaquer les pirates immédiatement, mais il a refusé, disant que ces démons de la mer étaient trop coriaces pour nous. C'est alors que je lui ai dit d'aller se faire foutre\nMon peuple était inutile dans cette affaire, alors j'ai passé un accord avec Kapper, cette ordure voulait prendre la place de Shark. Nous avions un plan - attirer l'amiral hors de sa forteresse vers un endroit douteux et le tuer là-bas. Nous avons aussi trouvé un tireur d'élite avec un bon fusil. Il pourrait tirer sur l'amiral depuis le mât du Fury\nMaintenant, la partie intéressante, c'est que l'avant-dernière nuit je suis allée à Tartarus, je voulais dire quelque chose d'important à Chad concernant notre plan. J'ai nagé jusqu'au bateau et ai accidentellement surpris Chad en train de parler avec deux Narvals. Il s'est avéré que ce n'était pas Shark qui avait tué Alan. Chad l'a fait. Il a ensuite secrètement répandu des rumeurs sur l'implication de l'amiral\nIl l'a assassiné à cause de moi. D'abord, il voulait me prendre pour un jouet dans son lit. Ensuite, il voulait m'utiliser pour se débarrasser de Shark - il savait que je chercherais toujours à me venger. Tu peux imaginer ? Quel lâche !";
			link.l1 = "Ouais, j'ai déjà rencontré des gens comme lui...";
			link.l1.go = "mary_8";
		break;
		
		case "mary_8":
			dialog.text = "Il est pire qu’un vaurien ! Il... je n’ai même pas les mots pour décrire ce monstre ! Je me suis retournée et je suis partie, mais le matin suivant, je l’ai retrouvé et je lui ai dit tout ce que je pensais de lui. Oui, je lui ai dit que je ne veux rien avoir à faire avec son complot contre l’amiral, ouais, hein ?";
			link.l1 = "Et ça ne lui a évidemment pas plu... C'était fait sous le coup de la colère, Mary. Tu devrais être plus prudente.";
			link.l1.go = "mary_9";
		break;
		
		case "mary_9":
			dialog.text = "Je ne peux pas, je ne pouvais pas garder ma bouche fermée. Le salaud a tué Alan et a essayé de m'utiliser pour atteindre ses objectifs sales ! Ordure ! Oui, bien sûr, il s'est mis en colère et a promis que je le regretterais. J'ai dit que je lui couperais les bijoux de famille et que je les donnerais à manger aux crabes !\nIl a menacé d'envoyer ses potes Narwhal après moi si je ne changeais pas d'avis. J'ai ri, je ne pensais pas qu'un Narwhal oserait lever la main sur moi.";
			link.l1 = "Il semble que tu t'es trompé.";
			link.l1.go = "mary_10";
		break;
		
		case "mary_10":
			dialog.text = "Ouais, hein ? "+pchar.name+"J'ai sous-estimé Chad et surestimé moi-même. Il a trouvé les salauds qui oseraient attaquer une fille seule dans sa propre cabine. Et que dois-je faire maintenant ? Je ne peux faire confiance à personne. Je ne peux même pas faire confiance à mes propres gens. Ces deux-là sont des Narvals, je les connaissais tous les deux, ouais, hein. Tant que Chad est vivant - je suis en danger, il enverra d'autres, sans doute. J'ai peur de sortir, le sniper que nous avons trouvé pour assassiner Requin pourrait me tirer dessus depuis le territoire de Rivados et s'échapper facilement. Je ne vais pas aller voir Donald, il n'écoutera pas. L'Amiral ? Je ne peux pas expliquer mon rôle dans les préparatifs de son assassinat ! Il m'enverra pourrir dans les cellules du 'Tartarus', j'en suis sûre ! Merde, je suis piégée. Je vais rester ici avec mes armes chargées jusqu'à ce que les provisions s'épuisent et ensuite... Je n'ai aucune idée de ce qui adviendra de moi !";
			link.l1 = "Eh bien, dans ce cas je n'ai pas d'autre choix que de t'aider, ouais, hein ? Ta situation s'aligne de toute façon avec mes plans ici...";
			link.l1.go = "mary_11";
		break;
		
		case "mary_11":
			dialog.text = "Tu as l'intention de m'aider ? Mais comment ? Tu vas tuer Chad ?";
			link.l1 = "Cette partie du plan, bien sûr.";
			link.l1.go = "mary_12";
		break;
		
		case "mary_12":
			dialog.text = "Ecoute, "+pchar.name+", , J'apprécie tes intentions, mais Chad est hors de ta portée. Il est l'un des amis les plus dignes de confiance de l'amiral et même si tu l'atteins - les pirates de Shark te tueront, ils ne connaissent pas la vérité, ouais, hein ?";
			link.l1 = "Calme-toi. Je devrai parler à Shark de toute façon.";
			link.l1.go = "mary_13";
		break;
		
		case "mary_13":
			dialog.text = "Alors, tu es aussi un pirate ?! Parle-moi de toi, regarde-toi : tu as fait irruption chez moi, tu m'as sauvé la vie, tu as promis d'aider avec ton allure séduisante, et pourtant je ne sais rien de toi !";
			link.l1 = "D'accord... Je ne suis pas un pirate, mais actuellement je travaille avec un certain baron pirate Jan Svenson. Je suis venu ici pour trouver Nathaniel Hawk. As-tu entendu parler de lui ?";
			link.l1.go = "mary_14";
		break;
		
		case "mary_14":
			dialog.text = "Non, qui est-ce ?";
			link.l1 = "Il est un autre pirate célèbre. C'est dommage que tu ne l'aies pas rencontré, il doit être quelque part par ici. Je cherchais aussi Shark, mais je ne m'attendais pas à le trouver ici.";
			link.l1.go = "mary_15";
		break;
		
		case "mary_15":
			dialog.text = "Mais comment es-tu arrivé ici ? Tu as l'air en trop bonne forme pour un survivant d'un naufrage.";
			link.l1 = "Et pourquoi penserais-tu que j'ai fait naufrage ?";
			link.l1.go = "mary_16";
		break;
		
		case "mary_16":
			dialog.text = "Il n'y a que cette voie pour venir ici. Seul le Requin a réussi à y naviguer d'une manière ou d'une autre.";
			link.l1 = "Eh bien, comme tu peux le voir, le Requin n'était pas le seul.";
			link.l1.go = "mary_17";
		break;
		
		case "mary_17":
			dialog.text = "Alors, tu as un navire ? Génial !";
			link.l1 = "Ne t'emballe pas si vite, Mary. Je suis arrivé ici par... sur une barque, mais elle a coulé au fond.";
			link.l1.go = "mary_18";
		break;
		
		case "mary_18":
			dialog.text = "A-ah... Eh bien, comme je l'ai dit - un naufrage. Tu es piégé ici avec nous maintenant, ouais, hein ?";
			link.l1 = "Mary, laisse-moi te raconter mon plan. Tu as mentionné que Chad prévoyait de tuer Shark. J'ai besoin que Shark reste en vie, Jan et moi allons le faire chef des pirates. C'est pourquoi je dois l'avertir, car d'après ton récit, je suis sûr que Chad tentera le coup avec ou sans ton aide.";
			link.l1.go = "mary_19";
		break;
		
		case "mary_19":
			dialog.text = "Aye, probablement. Il a les hommes pour y parvenir...";
			link.l1 = "Ça signifie que mon objectif principal est de gagner la confiance de Shark et de le sauver. Ensuite, je m'occuperai de Chad, officiellement. As-tu des preuves pour démontrer ses intentions ?";
			link.l1.go = "mary_20";
		break;
		
		case "mary_20":
			dialog.text = "J'ai sa lettre qui a été apportée ici par l'un de ces... idiots par terre. Il y a des menaces et des détails que l'amiral pourrait trouver intéressants. Attends ! Et moi alors ? Le Requin découvrira que je travaillais avec Chad !";
			link.l1 = "Mary, vas-tu rester ici éternellement armée de pistolets et cacher ton doux visage à tout le monde ? Penses-tu vraiment que je fais partie de ces idiots qui veulent la mort d'une belle dame ? Montre-moi d'abord la lettre, voyons ce que je peux faire...";
			link.l1.go = "mary_21";
		break;
		
		case "mary_21":
			GiveItem2Character(pchar, "letter_chad_1");
			RemoveItems(npchar, "letter_chad_1", 1);
			dialog.text = "Tiens. Qu'en penses-tu ?";
			link.l1 = "Attends... (lit). Oui, il semble que Chad soit une sorte spéciale de salauds à infester cette Terre. Cette lettre suffira à rendre Shark impatient de passer lui-même la corde autour du cou de Chad. Ne t'inquiète pas, ma dame, je veillerai à ce que Shark ne se doute de rien à ton sujet. Il sera de toute façon trop occupé avec Chad.";
			link.l1.go = "mary_22";
		break;
		
		case "mary_22":
			dialog.text = "Tu vas le faire ? Promets-le-moi, ouais, hein ? Jure que tu ne me trahiras pas !";
			link.l1 = "Mary, je te jure que je ne te trahirai pas. Ne t'inquiète pas pour ça, je ne t'ai pas sauvée juste pour voir ça arriver\nChad ne te laissera pas en paix, c'est sûr, tu en sais trop. Reste ici jusqu'à ce qu'il soit mort.";
			link.l1.go = "mary_23";
		break;
		
		case "mary_23":
			dialog.text = "Ouais, je resterai ici. Je n'ai pas envie d'être abattue par un tireur d'élite ou poignardée dans le dos, ouais, hein ?";
			link.l1 = "Bonne fille. Ferme toutes les portes, y compris celles du bas. Tu n'as qu'une seule clé ?";
			link.l1.go = "mary_24";
		break;
		
		case "mary_24":
			dialog.text = "Non. Il y en a un autre. Tu le veux ?";
			link.l1 = "Oui. Tu me fais confiance, ouais, hein ?";
			link.l1.go = "mary_25";
		break;
		
		case "mary_25":
			dialog.text = "Eh bien, si le gentleman qui vient de me sauver la vie me trahit, il n'y a pas de raison de vivre du tout... Prends-le.";
			link.l1 = "Ne t'inquiète pas, beauté ! Je ne te laisserai pas tomber. Je te retrouverai dès que j'aurai résolu ce bazar. J'espère que cela ne prendra pas trop de temps.";
			link.l1.go = "mary_26";
		break;
		
		case "mary_26":
			GiveItem2Character(pchar, "key_mary");
			dialog.text = "D'accord, je pourrai tenir cet endroit pendant quelques semaines.";
			link.l1 = "Génial. Je ne vais pas perdre de temps alors. Je vais sortir les cadavres et parler à Shark. Il est sur le 'San Augustine', n'est-ce pas ?";
			link.l1.go = "mary_27";
		break;
		
		case "mary_27":
			dialog.text = "Oui, il est toujours là. Et sors par où tu es entré - je ne te laisserai pas mettre le pied sur le pont supérieur du 'Ceres Smithy'.";
			link.l1 = "Intéressant, et pourquoi donc ?";
			link.l1.go = "mary_28";
		break;
		
		case "mary_28":
			dialog.text = "Parce que tu ne pourras pas m'aider si tu meurs. C'est le territoire des Narvals et ils te tueront comme un étranger.";
			link.l1 = "Hum... Compris. Eh bien, Mary, à plus tard. Je reviendrai dès que ce sera sûr.";
			link.l1.go = "mary_29";
		break;
		
		case "mary_29":
			dialog.text = "Tu peux me voir quand tu veux, ça ne me pose aucun problème. (rit)";
			link.l1 = "Adieu, belle demoiselle !";
			link.l1.go = "mary_30";
		break;
		
		case "mary_30":
			DialogExit();
			LAi_SetOwnerType(npchar);
			NextDiag.CurrentNode = "mary_wait";
			npchar.greeting = "mary_3";
			AddQuestRecord("SharkHunt", "31");
			AddQuestRecordInfo("Chad_Mary_letter", "2");
			LocatorReloadEnterDisable("CeresSmithy", "reload6", false);
			LocatorReloadEnterDisable("CeresSmithy", "reload7", false); // открываем выходы
		break;
		
		case "mary_wait":
			dialog.text = "Bonjour, "+pchar.name+", des bonnes nouvelles pour moi ? Tu vas bien, ouais, hein ?";
			if (pchar.questTemp.Saga.SharkHunt == "mary_whiskey")
			{
				link.l1 = "Le problème avec l'amiral est résolu. Il n'a aucun intérêt à te traquer, la trahison de Chad est la seule chose qui le préoccupe.";
				link.l1.go = "letters";
			}
			else
			{
				link.l1 = "Pas encore, Mary. Mais je ferai tout ce que je peux.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "mary_wait";
		break;
		
		case "letters":
			dialog.text = " Oh, Dieu merci ! Merci, je ne l'oublierai pas, ouais, hein ? Au moins, il n'y a pas de menace de l'amiral. Et qu'en est-il de Chad ? Qu'a fait Shark ? ";
			link.l1 = "Nous avons convaincu les Rivados de l'attaquer. Layton Dexter a retiré les gardes du 'Tartarus' et a donné la clé à Black Eddie. Les gars de Black ont libéré leur sorcier Chimiset, mais ils ont échoué à tuer Chad. Ils ont tué deux de ses amis Narval, mais il s'est enfui et se cache quelque part.";
			link.l1.go = "letters_1";
		break;
		
		case "letters_1":
			dialog.text = "Merde ! Cela signifie que je dois être encore plus prudent maintenant...";
			link.l1 = "Calme-toi, Mary. Je suis sûr qu'il a des personnes plus menaçantes dont il doit se soucier. Il sait probablement qui a monté les Rivados pour l'attaquer. Il fera tout pour tuer Shark, pas toi.";
			link.l1.go = "letters_2";
		break;
		
		case "letters_2":
			dialog.text = "Tu crois vraiment cela ? Chad n'est pas du genre à lâcher prise si facilement. Ah, je suis trop fatiguée pour avoir encore peur...";
			link.l1 = "Hm. Je ne pensais pas que tu étais le genre de dame à te laisser effrayer facilement.";
			link.l1.go = "letters_3";
		break;
		
		case "letters_3":
			dialog.text = "Ha ! Suis-je pas ? Je n'ai pas peur de combattre en face à face, mais rester assise à attendre d'être tuée ? Ça me fait très peur, ouais, hein ?"+pchar.name+", ouais, hein ?...";
			link.l1 = "Fais-moi confiance Mary : Kapper a fort à faire avec l'amiral en ce moment... J'ai besoin de tes conseils, ouais, hein ?";
			link.l1.go = "letters_4";
		break;
		
		case "letters_4":
			dialog.text = "Mon conseil ? Quel genre de conseil ?";
			link.l1 = "Eddie a trouvé deux lettres écrites par Chad. Lis-les, peut-être que tu sauras ce qu'il mijote. Après tout, tu étais dans le coup avec Chad...";
			link.l1.go = "letters_5";
		break;
		
		case "letters_5":
			RemoveItems(pchar, "letter_chad", 1);
			RemoveItems(pchar, "letter_chad_1", 1);
			dialog.text = "Donne-les-moi... (lisant). Axel est notre marchand sur 'Esmeralda', ouais, hein ? Chad voulait lui acheter du whisky pour une raison quelconque. Étrange ! Chad ne boit que du rhum, il dit que le whisky est 'la gnôle des paysans'...";
			link.l1 = "Et qu'en est-il de la deuxième lettre ?";
			link.l1.go = "letters_6";
		break;
		
		case "letters_6":
			dialog.text = "Marcello ? Marcello Cyclope, un ancien chasseur royal. C'est la principale raison pour laquelle je refuse de quitter cette cabine.";
			link.l1 = "Est-ce le tireur d'élite que tu as engagé ?";
			link.l1.go = "letters_7";
		break;
		
		case "letters_7":
			dialog.text = "Oui. Marcello peut tirer sur une mouche à douze mètres, malgré qu'il ait un œil en moins, ouais, hein ? Sa mission était d'abattre Shark en utilisant un stutzen à longue portée depuis le beaupré de Santa Florentina, ou la plateforme de Fury...";
			link.l1 = "Il semble donc que Chad ait décidé de se débarrasser de Shark. Mais quel est alors le but d'Eva ? Cecille ? Des boissons ?";
			link.l1.go = "letters_8";
		break;
		
		case "letters_8":
			dialog.text = "Eva est un navire neutre et Cecille est Cecille Halard, une vieille femme drôle qui y vit. Elle s'y est installée il n'y a pas longtemps depuis la Santa Florentina. Orelie Bertine est une amie à elle. Elles vivaient ici ensemble avant même que je ne sois née, ouais, hein ?";
			link.l1 = "Hm. Inepties. Deux grands gaillards se cachent d'une vieille femme pour boire un tonneau de whisky ensemble. Balivernes... Ce n'est pas le meilleur moment pour boire, Chad !";
			link.l1.go = "letters_9";
		break;
		
		case "letters_9":
			dialog.text = "Je t'ai déjà dit qu'il ne boit pas de whisky. Seulement du rhum, quelque chose ne colle pas.";
			link.l1 = "D'accord, peu importe. Sais-tu où trouver Cyclope ?";
			link.l1.go = "letters_10";
		break;
		
		case "letters_10":
			dialog.text = "Non. Il est très réservé. Il tire sur les oiseaux chaque jour à l'anneau extérieur et personne ne sait où il dort. Il visitait souvent Rivados auparavant.";
			link.l1 = "Quelle malchance... Eh bien, je vais aller parler à Axel alors. Peut-être qu'il comprendra mieux la situation. À bientôt, Mary ! Ferme la porte !";
			link.l1.go = "letters_11";
		break;
		
		case "letters_11":
			dialog.text = ""+pchar.name+"Je t'en prie, trouve Chad. Dépêche-toi, je n'ai pas dormi depuis la dernière attaque.";
			link.l1 = "Attends, ma chérie. Je ferai de mon mieux.";
			link.l1.go = "letters_12";
		break;
		
		case "letters_12":
			DialogExit();
			NextDiag.CurrentNode = "mary_wait";
			pchar.questTemp.Saga.SharkHunt = "trader_whiskey"; // флаг на магазин - поиск виски
			AddQuestRecord("SharkHunt", "35");
		break;
		
		case "happy":
			dialog.text = ""+pchar.name+"! Comment est-il arrivé ici ? Est-il venu pour...";
			link.l1 = "Oui, pour te tuer, Mary. Il est venu ici par la cabine de Jurgen et a utilisé une corde pour descendre ici.";
			link.l1.go = "happy_1";
		break;
		
		case "happy_1":
			dialog.text = "Ah ! Je suis vraiment idiote d'avoir oublié ce chemin ! Chad lui a appris, j'en suis sûre, ouais, hein ?";
			link.l1 = "Très probablement. Je l'ai échappé belle. Il te poursuivait.";
			link.l1.go = "happy_2";
		break;
		
		case "happy_2":
			dialog.text = "Et je dormais. Il m'aurait tuée en une seconde... Mais comment as-tu su qu'il était en chemin ici ?";
			link.l1 = "Je l'ai fait... Je viens de le faire, Mary.";
			link.l1.go = "happy_3";
		break;
		
		case "happy_3":
			dialog.text = "Tu m'as encore sauvé, beau gosse. Tu arrives toujours au bon moment, ouais, hein ? Comment fais-tu cela ?";
			link.l1 = "Eh bien, je ne sais pas. Un de mes nombreux talents. Ton siège est terminé - Chad Kapper est mort, tout comme tous ses amis. Cyclope était le dernier de son équipage pourri.";
			link.l1.go = "happy_4";
		break;
		
		case "happy_4":
			dialog.text = "Vraiment ? Est-ce vrai, "+pchar.name+"Tu ne me berces pas d'illusions, hein ?";
			link.l1 = "Pas du tout. Eh, j'ai besoin de repos après les événements des derniers jours...";
			link.l1.go = "happy_5";
		break;
		
		case "happy_5":
			dialog.text = "Je peux enfin respirer librement maintenant ! Merci... Merci beaucoup ! Tu es mon héros, ouais, hein ?";
			link.l1 = "J'adore entendre ça, être ton héros, en fait. Je suis juste heureux que tu sois enfin en sécurité.";
			link.l1.go = "happy_6";
		break;
		
		case "happy_6":
			dialog.text = "Alors ?";
			link.l1 = "Qu'y a-t-il, jolie demoiselle ?";
			link.l1.go = "happy_7";
		break;
		
		case "happy_7":
			dialog.text = "Pourquoi restes-tu planté là ? Allez, gentleman.";
			link.l1 = "Et faire quoi ?";
			link.l1.go = "happy_8";
		break;
		
		case "happy_8":
			dialog.text = "Tu es vraiment un gentleman... Viens ici et prends-moi dans tes bras, embrasse-moi enfin, tu en as envie, je le vois, ouais, hein ?";
			link.l1 = "Mary...";
			link.l1.go = "happy_9";
		break;
		
		case "happy_9":
			DialogExit();
			LAi_Fade("LSC_MaryRomantic_1", "");
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			StartQuestMovie(true, false, true);
			PlayStereoOGG("music_romantic");
			pchar.questTemp.LSC.MaryBye = "true"; // атрибут обязательного прощания перед телепортацией
			LocatorReloadEnterDisable("LostShipsCity_town", "reload62", false);
			LocatorReloadEnterDisable("LostShipsCity_town", "reload63", false); // открываем Церес снаружи
		break;
		
		case "happy_10":
			dialog.text = "Ne me laisse pas...";
			link.l1 = "Je suis ici, Mary, ma chérie...";
			link.l1.go = "happy_11";
		break;
		
		case "happy_11":
			dialog.text = "Tout peut attendre. L'amiral attendra, tes pirates attendront. Cette nuit est rien que pour nous deux, ouais, hein ?!";
			link.l1 = "Bien sûr...";
			link.l1.go = "happy_12";
		break;
		
		case "happy_12":
			dialog.text = "Et toutes les nuits suivantes après cela aussi...";
			link.l1 = "Ouais, hein ?";
			link.l1.go = "happy_13";
		break;
		
		case "happy_13":
			DialogExit();
			LSC_MaryLoveWaitTime();
			SetLaunchFrameFormParam("Next morning...", "", 0, 4);
			LaunchFrameForm();
			DoQuestCheckDelay("LSC_MaryRomantic_5", 4.0);
		break;
		
	// ----------------------------------вместе с Мэри на Церес Смити------------------------------------------
		case "LSC_love":
			if (pchar.questTemp.LSC.Mary == "return") // эта нода важнее даже ругани с нарвалами
			{
				dialog.text = ""+pchar.name+" ! Tu es revenu... sans elle. Donc elle n'a pas pu te prendre à moi !";
				link.l1 = "Mary, tes soupçons étaient déraisonnables. Tu es la seule pour moi. J'étais toujours avec toi dans mes pensées et dans mes rêves.";
				link.l1.go = "adversary_hire_return";
				break;
			}
			if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
			{
				dialog.text = ""+pchar.name+", , pourquoi te bats-tu avec les narvals ? Je vis sur leurs territoires, en fait, je suis l'un d'eux au cas où tu aurais oublié. S'il te plaît, va voir Fazio et fais la paix, je t'en supplie.";
				link.l1 = "D'accord, Mary, je ferai comme tu demandes, ouais, hein ?";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LSC.FindDolly")) // нашёл статую - прощается
			{
				dialog.text = ""+pchar.name+", quelque chose te tracasse. Qu'est-ce qui ne va pas ?";
				link.l1 = "Mary, il faut que je te parle.";
				link.l1.go = "dolly";
				break;
			}
			if (CheckAttribute(npchar, "quest.donald"))
			{
				dialog.text = ""+pchar.name+" ! Tous les narvals parlent de toi !";
				link.l1 = "Vraiment, ma chérie ?";
				link.l1.go = "donald";
				break;
			}
			if (CheckAttribute(npchar, "quest.talisman")) // подарок
			{
				dialog.text = ""+pchar.name+"Ce cimeterre est incroyable ! Merci encore !.. Je veux te faire un cadeau aussi. Bien sûr, il ne se compare pas au tien mais je veux que tu l'acceptes, ouais, hein ?";
				link.l1 = "Mary, la valeur d'un cadeau n'importe pas... Merci, mon amour";
				link.l1.go = "talisman";
				break;
			}
			if (stf(environment.time) >= 5.0 && stf(environment.time) < 10.0) // утро
			{
				dialog.text = "Une journée bien chargée t'attend, "+pchar.name+"Bonne chance !";
				if (CheckAttribute(npchar, "quest.narval_blade"))
				{
					link.l3 = "Mary, nous devons aller voir Jurgen aujourd'hui.";
					link.l3.go = "narval";
				}
				link.l1 = "Merci, Mary ! Je n'en doute pas.";
				link.l1.go = "exit";
				link.l2 = "Non, Mary. Je veux me reposer ici. Ça te va, ouais, hein ?";
				link.l2.go = "rest_morning"; // отдых
			}
			else
			{
				dialog.text = "Eh bien, "+pchar.name+", comment ça va ? Tu cours sur l'île comme d'habitude ?";
				link.l1 = "Oui, Mary. Il y a beaucoup de choses à faire...";
				link.l1.go = "LSC_love_1";
			}
			NextDiag.TempNode = "LSC_love";
		break;
		
		case "LSC_love_1":
			if (stf(environment.time) >= 18.0 && stf(environment.time) < 22.0) //вечер
			{
				dialog.text = "Il est déjà le soir, "+pchar.name+", de quelles choses parles-tu ? Reste ici, prenons quelques verres et détendons-nous, ouais, hein ! Ça peut attendre jusqu'au matin !";
				link.l1 = "(riant) Bien sûr, mon amour, dis-en moins...";
				link.l1.go = "LSC_love_evening";
				if (sti(pchar.money) >= 500)
				{
					link.l2 = "Mary, allons à la taverne aujourd'hui !";
					link.l2.go = "LSC_tavern";
				}
				link.l3 = "Mary, ma chère, je suis très occupé maintenant. Je reviendrai un peu plus tard, ouais, hein ?";
				link.l3.go = "LSC_love_2";
				break;
			}
			if (stf(environment.time) >= 10.0 && stf(environment.time) < 18.0) //день
			{
				dialog.text = "N'oublie pas de me rendre visite ce soir. Et ne pense même pas à m'éviter, ouais, hein !";
				if (CheckAttribute(npchar, "quest.narval_blade"))
				{
					link.l3 = "Mary, nous devons aller voir Jurgen aujourd'hui.";
					link.l3.go = "narval";
				}
				link.l1 = "Bien sûr, Mary, comment pourrais-je ? Je viendrai sûrement te voir, ouais, hein ?";
				link.l1.go = "exit";
				link.l2 = "Non, Mary. Je veux me reposer ici ce soir. Ça te va, ouais, hein ?";
				link.l2.go = "rest_afternoon"; // отдых
				NextDiag.TempNode = "LSC_love";
				break;
			}
			dialog.text = "De quoi parles-tu ? C'est déjà la nuit ! Non, tu n'iras nulle part, tu resteras ici, avec moi, ouais, hein ?";
			link.l1 = "(riant) comme tu veux, chéri...";
			link.l1.go = "LSC_love_night";
			NextDiag.TempNode = "LSC_love";
		break;
		
		case "LSC_love_2":
			dialog.text = "Ne me fais même pas...";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "LSC_love";
		break;
		
		// сходить в таверну
		case "LSC_tavern":
			dialog.text = LinkRandPhrase("Une idée géniale, "+pchar.name+"D'accord, ouais, hein ? Je suis d'accord !","Ouais, allons-y, hein ? "+pchar.name+"Sancho a une belle collection de vins, il y a beaucoup de choix !","Oh, je serais ravi, ouais, hein ? C'est toujours amusant à la taverne de Sancho et il a une grande sélection de vins !");
			link.l1 = "Allons-y !";
			link.l1.go = "LSC_love_tavern";
		break;
		
		// --> отдых
		case "rest_morning":
			dialog.text = "Bien sûr, "+pchar.name+"Bien sûr, repose-toi un peu, ouais, hein ?";
			link.l1 = "Je resterai jusqu'à midi...";
			link.l1.go = "rest_day";
			link.l2 = "Je resterai jusqu'au soir...";
			link.l2.go = "rest_evening";
		break;
		
		case "rest_afternoon":
			dialog.text = "Bien sûr, "+pchar.name+"Bien sûr, repose-toi un peu, ouais, hein ?";
			link.l1 = "Je resterai jusqu'au soir...";
			link.l1.go = "rest_evening";
		break;
		
		case "rest_day":
			DialogExit();
			iTime = sti(environment.time);
			iAddTime = 13 - iTime;
			WaitDate("",0,0,0,iAddtime,5);
			RecalculateJumpTable();
			LAi_Fade("", "");
			if (CheckAttribute(pchar, "questTemp.LSC.MaryBye")) NextDiag.CurrentNode = "LSC_love";
			else NextDiag.CurrentNode = "LSC_love_3";
		break;
		
		case "rest_evening":
			DialogExit();
			iTime = sti(environment.time);
			iAddTime = 18 - iTime;
			WaitDate("",0,0,0,iAddtime,5);
			RecalculateJumpTable();
			LAi_Fade("", "");
			if (CheckAttribute(pchar, "questTemp.LSC.MaryBye")) NextDiag.CurrentNode = "LSC_love";
			else NextDiag.CurrentNode = "LSC_love_3";
		break;
		// <-- отдых
		
	//--> если скоро уходит через портал
		case "LSC_love_3": 
			if (pchar.questTemp.LSC.Mary == "return") // эта нода важнее даже ругани с нарвалами
			{
				dialog.text = ""+pchar.name+"! Tu es revenu... sans elle. Donc il n'a pas pu te prendre loin de moi !";
				link.l1 = "Mary, tes soupçons étaient déraisonnables. Tu es la seule pour moi. J'étais toujours avec toi dans mes pensées et dans mes rêves.";
				link.l1.go = "adversary_hire_return";
				break;
			} // 291112
			if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
			{
				dialog.text = ""+pchar.name+", pourquoi te bats-tu avec des Narvals ? J'habite sur leurs territoires, en fait, je suis l'un d'eux, au cas où tu l'aurais oublié. S'il te plaît, va voir Fazio et fais la paix, je t'en prie.";
				link.l1 = "D'accord, Mary, je ferai comme tu demandes, ouais, hein ?";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(npchar, "quest.talisman")) // подарок
			{
				dialog.text = ""+pchar.name+" ! Ce sabre est incroyable ! Merci encore !.. Je veux te faire un cadeau aussi. Bien sûr, il ne vaut pas le tien en valeur, mais je veux que tu l'acceptes, ouais, hein ?";
				link.l1 = "Mary, la valeur d'un cadeau n'importe pas... Merci, mon amour";
				link.l1.go = "talisman";
				break;
			}
			if (stf(environment.time) >= 5.0 && stf(environment.time) < 10.0) // утро
			{
				dialog.text = "Tu pars déjà, ouais, hein ? "+pchar.name+"Bonne chance et ne m'oublie pas, ouais, hein ?";
				if (CheckAttribute(npchar, "quest.narval_blade"))
				{
					link.l3 = "Mary, nous devrions aller voir Jurgen aujourd'hui.";
					link.l3.go = "narval";
				}
				link.l1 = "Bien sûr, Mary.";
				link.l1.go = "exit";
				link.l2 = "Non, Mary. Je veux me reposer ici. Ça te va, ouais, hein ?";
				link.l2.go = "rest_morning"; // отдых
			}
			else
			{
				dialog.text = "Tu ne vas pas à ton truc de Kukulcan, ouais, hein ? "+pchar.name+"?";
				link.l1 = "Pas encore, je me prépare encore.";
				link.l1.go = "LSC_love_4";
			}
			NextDiag.TempNode = "LSC_love_3";
		break;
		
		case "LSC_love_4":
			if (stf(environment.time) >= 18.0 && stf(environment.time) < 22.0) //вечер
			{
				dialog.text = "Il est déjà le soir, "+pchar.name+"Pourquoi ne restes-tu pas ici ? Je veux être avec toi.";
				link.l1 = "Ouais, hein ? Chéri, je reste...";
				link.l1.go = "LSC_love_evening";
				if (sti(pchar.money) >= 500)
				{
					link.l2 = "Mary, allons à la taverne aujourd'hui !";
					link.l2.go = "LSC_tavern";
				}
				break;
			}
			if (stf(environment.time) >= 10.0 && stf(environment.time) < 18.0) //день
			{
				dialog.text = "Bonne chance et n'oublie pas moi... Viens me voir le soir si tu peux, ouais, hein !";
				if (CheckAttribute(npchar, "quest.narval_blade"))
				{
					link.l3 = "Mary, nous devrions voir Jurgen aujourd'hui.";
					link.l3.go = "narval";
				}
				link.l1 = "Très bien, ma chérie.";
				link.l1.go = "exit";
				link.l2 = "Mary, je veux me reposer ici. Ça te va, ouais, hein ?";
				link.l2.go = "rest_afternoon"; // отдых
				NextDiag.TempNode = "LSC_love_3";
				break;
			}
			dialog.text = "De quoi parles-tu ? C'est la nuit ! Non, tu n'iras nulle part, tu resteras ici, ouais, hein ?";
			link.l1 = "(en riant) Ouais, hein ? Je vais rester...";
			link.l1.go = "LSC_love_night";
			NextDiag.TempNode = "LSC_love_3";
		break;
		// <-- скоро уходит через портал
		
	// --> взаимоотношения - секс и прочее
		case "LSC_love_tavern":
			DialogExit();
			sld = ItemsFromID("potionrum");
			sld.shown = true;
			sld.startLocation = "FleuronTavern";
			sld.startLocator = "bottle";
			DoQuestReloadToLocation("FleuronTavern", "quest", "sit2", "LSC_MaryTavern");
		break;
		
		case "LSC_love_evening":
			DialogExit();
			//if(CheckAttribute(PChar, "IsMushketer")) SetMainCharacterToMushketer("", false);
			LSC_MaryEveneng();
		break;
		
		case "LSC_love_night":
			DialogExit();
			LSC_MaryLove();
		break;
		
		case "LSC_love_morning":
			if (CheckAttribute(npchar, "quest.hire"))
			{
				dialog.text = "Capitaine "+pchar.name+"! L'officier Mary Casper est prête à servir sous votre commandement !";
				link.l1 = "Bien joué, officier ! Je vous ordonne de monter à bord du navire immédiatement. Mais d'abord : embrassez votre capitaine !";
				link.l1.go = "LSC_mary_hire";
			}
			else
			{
				dialog.text = "C'était incroyable, mon amour... Bonjour !";
				link.l1 = "Bonjour, mon chou ! Tu es merveilleux !";
				link.l1.go = "LSC_love_morning_1";
			}
		break;
		
		case "LSC_love_morning_1":
			DialogExit();
			LAi_SetOwnerType(npchar);
			if (CheckAttribute(pchar, "questTemp.LSC.MaryBye")) NextDiag.CurrentNode = "LSC_love";
			else NextDiag.CurrentNode = "LSC_love_3";
		break;
		// <-- взаимоотношения
		
		// стал другом нарвалам
		case "donald":
			dialog.text = "As-tu parlé à Donald ? Est-il vrai que l'amiral voulait s'allier avec Rivados et combattre les Narvals ? Est-il vrai que tu l'en as dissuadé ? Il y aura la paix entre les pirates et les Narvals, n'est-ce pas ?";
			link.l1 = "Oui, Mary. C'est comme ça.";
			link.l1.go = "donald_1";
		break;
		
		case "donald_1":
			dialog.text = ""+pchar.name+", je ne trouve pas les mots... Ils disent aussi que Donald te considère comme un ami. Tu pourrais devenir un des Narwhals, ouais, hein ?";
			link.l1 = "Vois Donald quand tu peux - il veut aussi faire la paix avec toi. Il te demande de lui pardonner pour ses paroles et pour ne pas avoir réussi à te protéger de ces deux salauds.";
			link.l1.go = "donald_2";
		break;
		
		case "donald_2":
			dialog.text = "Au diable Donald ! Bien que je sois contente d'entendre cela, bien sûr. Je le verrai. Mais toi ! Je... non, pas comme ça... Je suis fière de toi, ouais, hein ?";
			link.l1 = "Bon Dieu, Mary... tu es... ah, tu fais battre mon cœur à toute allure !";
			link.l1.go = "exit";
			NextDiag.TempNode = "LSC_love";
			DeleteAttribute(npchar, "quest.donald");
		break;
		
		// ноды прощания
		case "dolly":
			dialog.text = "Parlons ! As-tu des ennuis ?";
			link.l1 = "Non. Mary, te souviens-tu de la nuit où nous nous sommes rencontrés pour la première fois ? Après que nous avons réglé leur compte à ces deux salauds, je t'ai dit que j'étais arrivé ici sur un navire.";
			link.l1.go = "dolly_1";
		break;
		
		case "dolly_1":
			dialog.text = "Je me souviens, ouais. Ta barque a coulé et tu as dû nager jusqu'ici... ouais, hein ?";
			link.l1 = "J'ai menti. Tu m'aurais pris pour un fou si je t'avais dit la vérité à ce moment-là. Il n'y avait pas de barque. J'ai utilisé une force inexplicable d'un dieu indien 'Kukulcan' pour arriver ici.";
			link.l1.go = "dolly_2";
		break;
		
		case "dolly_2":
			dialog.text = ""+pchar.name+"... De quoi parles-tu ? Kukulcan ?";
			link.l1 = "Mary, ma chère, tu dois me croire, car il n'y a rien de rationnel là-dedans, et je ne peux partager cela avec personne d'autre que toi. Nathaniel Hawk a disparu en touchant l'idole indienne, il était pourchassé et cela l'a sauvé...";
			link.l1.go = "dolly_3";
		break;
		
		case "dolly_3":
			dialog.text = "";
			link.l1 = "Je cherchais Nathaniel. J'ai parlé avec un chaman indien et j'ai dû faire la même chose que Hawk. J'ai été téléporté dans la cale du 'San Augustine', je suis sorti par un trou dans sa coque, et le destin m'a amené à toi.";
			link.l1.go = "dolly_4";
		break;
		
		case "dolly_4":
			dialog.text = "Est-ce censé être une histoire drôle de notre première rencontre, que nous raconterons à nos enfants un jour ? Ou as-tu perdu la tête ?";
			link.l1 = "Je suis sérieux, Mary. Je comprends que c'est difficile à croire, et cela doit te sembler fou, mais s'il te plaît, fais-moi confiance.";
			link.l1.go = "dolly_5";
		break;
		
		case "dolly_5":
			dialog.text = "Il semble que les histoires d'Eric étaient vraies...";
			link.l1 = "Qui est Eric ? Et que t'a-t-il dit ?";
			link.l1.go = "dolly_6";
		break;
		
		case "dolly_6":
			dialog.text = "Eric etait l'un des locaux, un vieux marin. Il est deja mort. Quand j'etais gamine, il me racontait des histoires sur une idole d'or, un sanctuaire ou les Rivados sacrifiaient des hommes. Ici, sur l'Ile\nCeux qui y touchaient disparaissaient, et on ne les revoyait jamais. Je pensais que c'etaient juste des contes, destines a effrayer les enfants.";
			link.l1 = "C'est vrai, Mary. Eric ne mentait pas.";
			link.l1.go = "dolly_7";
		break;
		
		case "dolly_7":
			dialog.text = "Heureusement, le navire avec ce terrible idole avait coulé. Je ne l'ai jamais vu de mes propres yeux.";
			link.l1 = "Je l'ai trouvé, reposant au fond.";
			link.l1.go = "dolly_8";
		break;
		
		case "dolly_8":
			dialog.text = "Tu as plongé là-bas ?! Est-ce que ce fichu inventeur Vedecker t’a donné sa combinaison ? Il y a des crabes qui grouillent là-dessous, ouais, hein ! Salaud ! te mettre en danger comme ça !";
			link.l1 = "Mary, ne t'inquiète pas pour moi. Je peux m'occuper des monstres. Ils ne sont pas aussi menaçants qu'on le dit. Je cherche la statue depuis mon premier jour sur cette île et, enfin, je l'ai trouvée.";
			link.l1.go = "dolly_9";
		break;
		
		case "dolly_9":
			dialog.text = "Et que va-t-il se passer maintenant ?";
			link.l1 = "C'est la seule issue pour sortir d'ici. Je suis venue ici par une idole comme celle-ci, et je vais l'utiliser à nouveau pour revenir... Mary ! Tu pleures ? Mary ! Arrête ça !";
			link.l1.go = "dolly_10";
		break;
		
		case "dolly_10":
			if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Shark, ";
			else sTemp = "";
			dialog.text = "Pourquoi devrais-je ? Je vais pleurer, je veux pleurer, ouais, hein... (sanglotant) De telles choses arrivent toujours à mes hommes ! Je serai de nouveau seule !";
			link.l1 = "Que penses-tu qu'il m'arrivera ? Tu crois vraiment que je te laisserais ici ?! Je reviendrai te chercher, à bord d'un navire. Je dois prendre à la fois toi et "+sTemp+"Nathaniel est de retour avec moi. Me suivras-tu dans le monde extérieur ?";
			link.l1.go = "dolly_11";
		break;
		
		case "dolly_11":
			dialog.text = "(en larmes) Bien sûr... Oui, je le ferai... Tu reviendras pour moi, n'est-ce pas ? Comment diable comptes-tu revenir sur l'île ? Seul Shark sait comment naviguer jusqu'ici. Et n'ose pas m'oublier, sinon je te botterai les fesses quand je te retrouverai, ouais, hein ?";
			link.l1 = "Mary, assez avec ces pensées folles ! Bien sûr que je reviendrai pour toi, qui d'autre pourrait faire battre mon coeur de la même manière depuis le jour où je t'ai rencontrée ? Ne t'inquiète pas mon amour, Shark m'a donné les coordonnées et les directions. Je te retrouverai.";
			link.l1.go = "dolly_12";
		break;
		
		case "dolly_12":
			dialog.text = "Tu as dit qu'une statue t'a amené ici directement du continent, mais si cette statue t'emmène ailleurs, en Afrique peut-être ? Que vais-je faire sans toi alors ?!";
			link.l1 = "Kukulcan est un dieu indien, il m'emmènera quelque part dans les Caraïbes ou sur le continent. Il me suffit de trouver un établissement, ensuite il me sera facile de trouver mon navire et mon équipage.";
			link.l1.go = "dolly_13";
		break;
		
		case "dolly_13":
			dialog.text = "(pleure) Promets-moi... non, jure-moi que tu reviendras, ouais, hein !";
			link.l1 = "Mary, ma chère, je te jure que je reviendrai. Et je t'emmènerai loin de cet endroit misérable. Tu n'auras pas à me regretter trop longtemps. Assez de larmes.";
			link.l1.go = "dolly_14";
		break;
		
		case "dolly_14":
			dialog.text = "D'accord, "+pchar.name+" ... ... Reviens vers moi, je t'attendrai, ouais, hein ! Quand vas-tu partir ?";
			link.l1 = "Je ne sais pas encore. Je dois d'abord me préparer, puis je plongerai et toucherai la statue. Ils te diront que je me suis noyé - ne les crois pas. Tout ira bien.";
			link.l1.go = "dolly_15";
		break;
		
		case "dolly_15":
			dialog.text = "Je comprends. "+pchar.name+", chéri, serre-moi dans tes bras... Embrasse-moi...";
			link.l1 = "Mary... Ma chère Mary...";
			link.l1.go = "dolly_16";
		break;
		
		case "dolly_16":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.LSC.MaryBye"); // можно телепортироваться
			DeleteAttribute(pchar, "questTemp.LSC.FindDolly");
			SetMusic("music_romantic");
			SetLaunchFrameFormParam("", "", 0, 15);
			SetLaunchFrameFormPic("loading\inside\kiss.tga");
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 10); //крутим время
			RecalculateJumpTable();
			NextDiag.CurrentNode = "LSC_love_3";
			npchar.greeting = "mary_5"; 
		break;
		
		// дарим Мэри палаш Нарвал
		case "narval":
			dialog.text = "Jurgen ? Pourquoi ?";
			link.l1 = "Tu verras. Cela va être une agréable surprise.";
			link.l1.go = "narval_1";
		break;
		
		case "narval_1":
			dialog.text = "Oh,  comme c'est intéressant ! Agréable ? C'est fantastique, ouais, hein ? Allons-y, avant que je ne meure de curiosité !";
			link.l1 = "Tu vas aimer ça, j'en suis sûr. Allons-y !";
			link.l1.go = "narval_2";
		break;
		
		case "narval_2":
			DialogExit();
			NextDiag.CurrentNode = "narval_wait";
			LocatorReloadEnterDisable("CeresSmithy", "reload6", true);
			LocatorReloadEnterDisable("CeresSmithy", "reload7", true);
			pchar.quest.LSC_PresentMary.win_condition.l1 = "ExitFromLocation";
			pchar.quest.LSC_PresentMary.win_condition.l1.location = pchar.location;
			pchar.quest.LSC_PresentMary.function = "LSC_GotoPresentMary";
		break;
		
		case "narval_wait":
			dialog.text = "Allons-y, "+pchar.name+"!";
			link.l1 = "Bien sûr...";
			link.l1.go = "exit";
			NextDiag.TempNode = "narval_wait";
		break;
		
		case "narval_3":
			dialog.text = "Eh bien, "+pchar.name+", , quelle surprise as-tu pour moi ?";
			link.l1 = "Mary ! Jurgen et moi avons décidé de te faire un cadeau de notre part à tous les deux. C'est une lame unique, une épée large portant le nom de Narval. Il n'existe que deux épées de ce type dans le monde : la première appartenait à Alan Milrow, celle-ci sera la tienne. Elle est faite d'un acier spécial, forgée par le maître de Jurgen, qui ne s'émoussera ni ne rouillera jamais.";
			link.l1.go = "narval_4";
		break;
		
		case "narval_4":
			DialogExit();
			LAi_SetActorType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Schmidt"));
			PChar = GetMainCharacter();			
			LAi_SetPlayerType(PChar);
			sld = characterFromId("Mary");
			sld.dialog.currentnode = "narval_5";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "narval_5":
			dialog.text = "";
			link.l1 = "Notre chère fille... Tous les Narvals savent combien tu as souffert. Je suppose que tu mérites de porter cette épée large, symbole du clan des Narvals. Porte-la avec fierté. Cette lame sera une menace pour tes ennemis et te protégera au combat.";
			link.l1.go = "narval_6";
		break;
		
		case "narval_6":
			PlaySound("interface\important_item.wav");
			sld = characterFromId("Mary");
			RemoveCharacterEquip(sld, BLADE_ITEM_TYPE);
			RemoveItems(sld, "blade_17", 1);
			sTemp = GetBestGeneratedItem("blade_31");
			GiveItem2Character(sld, sTemp);
			EquipCharacterbyItem(sld, sTemp);
			sld = characterFromId("Blaze");
			dialog.text = "Jurgen ? Cela... c'est pour moi ?...";
			link.l1 = "Oui, Mary. "+sld.name+" m'a demandé de le fabriquer pour toi, et a apporté un fer unique du fond de la mer, aucun acier n'égale le poids ni la résistance de ce matériau. J'ai mis mon âme dans cette épée, tout comme je l'avais fait autrefois avec celle d'Alan.";
			link.l1.go = "narval_7";
		break;
		
		case "narval_7":
			dialog.text = "Je ne sais pas quoi dire... Merci, Jurgen ! Merci, ouais, hein ? Je le porterai avec fierté et honorerai la valeur de la lame, je le jure, ouais, hein ! Je ne me suis pas assez entraînée avec des épées larges, mais je vais m'entraîner dur maintenant !";
			link.l1 = "Pour cela, je n'ai aucun doute, petite.";
			link.l1.go = "narval_8";
		break;
		
		case "narval_8":
			DialogExit();
			LAi_SetStayType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			PChar = GetMainCharacter();			
			LAi_SetPlayerType(PChar);
			sld = characterFromId("Mary");
			sld.dialog.currentnode = "narval_9";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "narval_9":
			dialog.text = ""+pchar.name+"... attends, non... Tu es le meilleur homme que j’aie jamais rencontré ! Tu es incroyable, ouais, hein ! Sais-tu combien cela signifie pour moi ? Cette épée est le meilleur cadeau que j’aurais pu recevoir ! Tu as déjà tant fait pour moi, sauvé ma vie deux fois, et pourtant tu ne cesses de me surprendre ! Merci, mon amour !";
			link.l1 = "Ça ne pouvait pas être autrement, Mary. Je continuerai à te surprendre chaque jour, jusqu'à mon dernier souffle ! Ton sourire me réjouit et je suis heureux que le cadeau te plaise.";
			link.l1.go = "narval_10";
		break;
		
		case "narval_10":
			dialog.text = "(ricane) Merci ! Une si merveilleuse lame, ouais, hein ! Il faut une main ferme pour la manier... J'ai hâte de commencer à m'entraîner avec elle !";
			link.l1 = "Je ne vois pas de problème. Dépêche-toi d'aller à ta cabine et essaie ta nouvelle épée large !";
			link.l1.go = "narval_11";
		break;
		
		case "narval_11":
			dialog.text = "C’est ce que je vais faire. Merci encore, gentleman ! "+pchar.name+"... Viens me voir ce soir, quand tu seras prêt... (gloussements)";
			link.l1 = "Bien sûr, milady. Je te verrai ce soir.";
			link.l1.go = "narval_12";
		break;
		
		case "narval_12":
			DialogExit();
			EndQuestMovie();
			sld = characterFromId("Schmidt");
			sld.dialog.currentnode = "Jurgen";
			DeleteAttribute(sld, "quest.narval_blade");
			DeleteAttribute(npchar, "quest.narval_blade");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "CeresSmithy", "goto", "goto10", "LSC_MaryReturnNormal", -1);
			LocatorReloadEnterDisable("CeresSmithy", "reload6", false);
			LocatorReloadEnterDisable("CeresSmithy", "reload7", false); // открываем проход через трюм
			// владение Нарвалом повышает скилл ТО у Мэри и открывает перк тяжелой руки
			SetSelfSkill(npchar, 95, 50, 90, 90, 50);
			SetCharacterPerk(npchar, "HardHitter");
			npchar.quest.talisman = "true";
			npchar.quest.blade31 = "true";
		break;
		
		// Мэри дарит талисман
		case "talisman":
			dialog.text = "Tiens, regarde. Je l'ai trouvé dans l'un des navires de l'anneau extérieur, dans le coffre d'un capitaine. Chaque marin expérimenté dit que cet objet est extrêmement précieux pour un navigateur, il peut protéger un navire des pires tempêtes. Certains étaient même prêts à l'acheter, mais je ne l'ai pas vendu... Je veux que tu aies cet amulette, chéri. Utilise-le pour te garder en sécurité en mer.";
			link.l1 = "Merci, Mary ! Très attentionné de ta part, je t'aime !";
			link.l1.go = "talisman_1";
		break;
		
		case "talisman_1":
			GiveItem2Character(pchar, "talisman2"); 
			PlaySound("interface\important_item.wav");
			Log_Info("You have received a talisman of 'Jonah'");
			dialog.text = "Vraiment ? Tu aimes ça ? Oh, c'est génial ! Je suis tellement contente, ouais, hein ?";
			link.l1 = "C'est un talisman très rare et précieux. Bien sûr que je l'aime ! Merci, chéri !";
			link.l1.go = "talisman_2";
		break;
		
		case "talisman_2":
			DialogExit();
			DeleteAttribute(npchar, "quest.talisman");
		break;
		
	// --------------------------------------вернулся на Остров---------------------------------------------
		case "return":
			dialog.text = ""+pchar.name+"... Tu es de retour. Je t'attendais, je regardais l'horizon chaque jour, ouais, hein ? Tu es revenu vers moi...";
			link.l1 = "Oui, Mary. Je suis ici comme promis. Laisse-moi te serrer dans mes bras, ma chère !";
			link.l1.go = "return_1";
		break;
		
		case "return_1":
			dialog.text = "Ah, "+pchar.name+"... Tu n'imagines même pas ce que j'ai ressenti ! Les narvals parlaient de ta mort, ils disaient que tu t'étais noyé. Ils étaient tous sûrs que tu étais mort. Je continuais à leur dire que tu es vivant... Bien sûr, personne ne me croyait, ils pensaient que j'étais devenue folle après tout ce qui s'est passé.";
			link.l1 = "Mary... Ma chère ! Qu'est-ce qui ne va pas chez toi ? Tu trembles... Tu as froid ?";
			link.l1.go = "return_2";
		break;
		
		case "return_2":
			dialog.text = "Non, je n'ai pas froid. Je suis juste... Je ne veux pas en parler ici. Viens à ma cabine quand tu auras fini. Je veux rester seule avec toi, ouais, hein ? Tu ne vas pas voir l'amiral et Nathaniel maintenant ?";
			link.l1 = "Oui. Je dois parler à Shark et, bien sûr, emmener Danielle à Nathaniel. Cela ne prendra pas trop de temps. Je te verrai bientôt, Mary.";
			link.l1.go = "return_3";
		break;
		
		case "return_3":
			dialog.text = "J'ai hâte de... te voir. Viens dès que possible, ouais, hein ?";
			link.l1 = "D'accord, je te fais confiance, ouais, hein ?";
			link.l1.go = "return_4";
		break;
		
		case "return_4":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload62", "CeresSmithy", "goto", "goto11", "LSC_MaryWaitInCabin", 20.0);
		break;
		
		case "adversary":
			dialog.text = ""+pchar.name+"Enfin. Il faut que nous parlions, ouais, hein ?";
			link.l1 = "Qu'est-ce qui ne va pas, Mary ? Je vois que quelque chose te tracasse ! Qu'est-ce qui s'est passé ?";
			link.l1.go = "adversary_1";
		break;
		
		case "adversary_1":
			dialog.text = "Elle est arrivée... "+pchar.name+", qui est cette catin sur ton navire ?";
			link.l1 = "Qui ? Tu parles de Danielle ? Mais tu connais déj...";
			link.l1.go = "adversary_2";
		break;
		
		case "adversary_2":
			dialog.text = "Non, pas Danielle. Je parle de cette blonde, à peine couverte de vêtements, qui se promène sur le pont de ton navire ! Je l'ai vue à la longue-vue, ouais, hein ?";
			link.l1 = "A-ah ! C'est Helen McArthur. Elle est impliquée dans cette étrange histoire tout comme Danielle. Elle sert comme mon officier. Temporairement, bien sûr.";
			link.l1.go = "adversary_3";
		break;
		
		case "adversary_3":
			dialog.text = "Officier ? Elle est officier ?!";
			link.l1 = "Eh bien, oui. Qu'est-ce qui ne va pas avec ça ?.. Mary, bon sang ! Tu es jalouse !";
			link.l1.go = "adversary_4";
		break;
		
		case "adversary_4":
			dialog.text = "Qu'est-ce que tu pensais ?!... (en larmes) Je t'ai attendu tout ce temps, je n'ai pas dormi à cause de toi, et tu oses revenir ici avec une vieille harpie...";
			link.l1 = "Mary ! Arrête de pleurer ! Qu'est-ce qui ne va pas chez toi ? Tu peux éventrer n'importe quel homme sans hésitation, et pourtant tes yeux sont toujours humides... Mary, ma chère, Helen n'est qu'un officier, servant temporairement jusqu'à ce que justice soit rendue, et que nos objectifs communs soient atteints, rien de plus.";
			link.l1.go = "adversary_5";
		break;
		
		case "adversary_5":
			if (CheckAttribute(npchar, "quest.blade31")) 
			{
				sTemp = "I have been training hard with the broadsword you gave me, and in your absense I have mastered it perfectly.";
				notification("Heavy Weapons +", "Mary");
			}
			else sTemp = "I have been training hard with rapiers and I have mastered them perfectly.";
			dialog.text = "(en sanglotant) Officier... Alors je veux aussi être ton officier, ouais, hein ? Je sais me battre, tu le sais bien !"+sTemp+" Et je tire bien ! Je n'ai peut-être pas de compétences navales mais j'apprends vite, j'ai du talent, ouais, hein ?";
			// проход первый - ГГ либо соглашается, либо нет, отказ ведет к полному разрыву
			link.l1 = "Ouais, hein ? Mary... Je voulais te proposer le poste moi-même. Il n'y a pas de meilleure, plus habile, plus fougueuse fille que toi ! Je te veux à mes côtés !";
			link.l1.go = "adversary_hire";
			link.l2 = "Mary ! Être officier d'abordage est trop dangereux ! Tu ne comprends pas ce que tu demandes. Je ne peux pas risquer ta vie.";
			link.l2.go = "adversary_fail";
		break;
		
		// отказ
		case "adversary_fail":
			dialog.text = "Tu ne peux pas ? Alors cette blonde pouffiasse peut être officier et pas moi ? Tu me mens, "+pchar.name+", tu ne veux simplement pas être avec moi ! (en pleurant) Cette fille est-elle mieux que moi, ouais, hein ?";
			link.l1 = "Mary, tu ne comprends pas !";
			link.l1.go = "adversary_fail_1";
		break;
		
		case "adversary_fail_1":
			dialog.text = "Je le sais ! J'ai vu ses yeux perçants se poser sur toi ! Ce n'est pas juste un officier, ouais, hein ? Je comprends ça (en sanglotant). Bien sûr, je ne peux pas rivaliser avec elle - elle sait diriger un navire...";
			link.l1 = "Mary, mais de quoi parles-tu !";
			link.l1.go = "adversary_fail_2";
		break;
		
		case "adversary_fail_2":
			dialog.text = "C'est fini... (en pleurant) Va-t'en ! Va-t'en retrouver ta catin ! Et moi, je resterai ici... Je ne bougerai pas d'ici ! Rends-moi ma clef !";
			link.l1 = "Mais Mary...";
			link.l1.go = "adversary_fail_3";
		break;
		
		case "adversary_fail_3":
			RemoveItems(pchar, "key_mary", 1);
			dialog.text = "Va-t'en...";
			link.l1 = "...";
			link.l1.go = "adversary_fail_4";
		break;
		
		case "adversary_fail_4": // обидел Мэри - больше от неё ничего не получишь
			DialogExit();
			LAi_CharacterDisableDialog(npchar);//запрет диалога
			for (i=0; i<=3; i++)
			{
				LocatorReloadEnterDisable("LostShipsCity_town", "reload6"+i, true); // закрываем вход к Мэри
			}
			DoQuestReloadToLocation("LostShipsCity_town", "reload", "reload62", "");
			pchar.questTemp.LSC.Mary = "fail";
			AddQuestRecord("LSC", "23");
			bQuestDisableMapEnter = false; //открыть карту
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
		break;
		
		// соглашаемся
		case "adversary_hire":
			// проход второй - смотрим, Элен может стать подругой или нет
			bOk = (CheckAttribute(pchar, "questTemp.HelenDrinking.GaveCutlass")) && (sti(pchar.questTemp.Saga.HelenRelation) >= 6);
			if (bOk || sti(pchar.questTemp.Saga.HelenRelation) >= 5 || CharacterIsAlive("Longway"))
			{
				dialog.text = "Vraiment ? Tu voulais vraiment que je sois ton officier ? Ouais, hein ?"+pchar.name+", bon sang, tu n'imagines pas à quel point je suis heureuse ! Je veux tellement être ton officier... mais pas sur le même navire que ce blondinet !";
				link.l1 = "Mary, mais pourquoi ?!";
				link.l1.go = "adversary_hire_no";
			}
			else
			{
				dialog.text = "Vraiment ? Tu voulais vraiment que je sois ton officier, ouais, hein ? "+pchar.name+", bon sang, tu n'imagines pas à quel point je suis heureuse ! Je te jure, je ne te laisserai pas tomber, tu verras !";
				link.l1 = "Jésus, Mary, chérie, tu es précieuse. Tu pleurais il y a une minute et maintenant ton visage est illuminé ! Et, Mary, tu n’es pas juste un autre officier pour moi. Tu es plus que ça et je doute que tu puisses, de quelque manière que ce soit, me décevoir.";
				link.l1.go = "adversary_hire_yes";
			}
		break;
		
		case "adversary_hire_no": // Мэри не пойдёт, пока не ГГ не расстанется с Элен. Выбирай, кто тебе милее...
			dialog.text = "Tu ne la considères peut-être que comme ton officier, mais je doute qu'elle te voie uniquement comme son capitaine. J'ai vu les regards qu'elle te lançait, je connais ce regard, ouais, hein ! Seule moi peux te lancer ces regards !";
			link.l1 = "Mary, ma chérie, mais je t’ai déjà dit, je n’ai pas de sentiments pour elle, et c’est tout ! Il n’y a rien entre nous ! Je le jure, bon sang ! J’ai besoin de son aide pour régler le bazar chez les Frères de la Côte. Jan Svenson ne m’aidera pas à capturer la Tortuga, si je ne l’aide pas, et j’ai besoin de lui !";
			link.l1.go = "adversary_hire_no_1";
		break;
		
		case "adversary_hire_no_1":
			dialog.text = ""+pchar.name+", mon cher, étreins-moi... Je suis désolée. Je te crois. Mais je ne pourrai pas rester près d'elle et la regarder essayer de flirter avec toi, ouais, hein ! Finalement, je prendrai mon épée et je la couperai en deux !";
			link.l1 = "Ouais, tu peux certainement faire ça... Tu as un sacré tempérament, hein ?";
			link.l1.go = "adversary_hire_no_2";
		break;
		
		case "adversary_hire_no_2":
			dialog.text = "Et si je la tue - tu me quitteras, ouais, hein ? Je ne me le pardonnerais jamais.";
			link.l1 = "Alors, que proposes-tu, Mary ? Que devrais-je faire avec elle ?";
			link.l1.go = "adversary_hire_no_3";
		break;
		
		case "adversary_hire_no_3":
			dialog.text = "Tu as dit qu'elle est un officier temporaire. Je te rejoindrai dès que tu la laisseras à terre. Abandonnée sur quelque île déserte, j'espère (rire) je te suivrai jusqu'au bout du monde, ouais, hein !"+pchar.name+", chéri, est-elle vraiment meilleure que moi ?";
			link.l1 = "Balivernes ! Arrête de parler comme ça, Mary, ma chère, il n'y a pas de femme meilleure que toi !...";
			link.l1.go = "adversary_hire_no_4";
		break;
		
		case "adversary_hire_no_4":
			dialog.text = "Alors prouve-le-moi. Je ne veux pas te partager, "+pchar.name+"Je préfère être seule que de te partager avec une autre, ouais, hein...";
			link.l1 = "Très bien, Mary. Passons un accord. Je ne peux pas me débarrasser d'Helen maintenant, elle est importante pour cette poursuite. Je vais l’aider dans ses problèmes, la faire maîtresse d'Isla Tesoro, la laisser partir, et il ne restera rien entre nous. Avec un peu de chance, cela ne prendra pas plus d’un mois ou deux. M’attendras-tu aussi longtemps ?";
			link.l1.go = "adversary_hire_no_5";
		break;
		
		case "adversary_hire_no_5":
			dialog.text = "Bien sûr, je le ferai, ouais, hein ? C'est ma décision... Si tu reviens vers moi, cela signifie que tu m'as choisie à sa place. Et si tu ne reviens pas... c'est donc mon destin. Je resterai ici et je fonderai mon propre clan. Le clan Casper...";
			link.l1 = "Tu pleures encore ? Mary, voyons. Assez de ces bêtises ! De quoi parles-tu ? Quel clan... Jeune écervelée, bien sûr que je reviendrai, je n’oserais pas te laisser parmi ces vieux navires pourris ! Tu inonderais l'île avec tes larmes, ouais, hein ?";
			link.l1.go = "adversary_hire_no_6";
		break;
		
		case "adversary_hire_no_6":
			dialog.text = "Revient dès que possible alors... "+pchar.name+", chéri, embrasse-moi, s’il te plaît...";
			link.l1 = "Je reviendrai. Je te le promets !"; // ага, а мы посмотрим, обманешь или нет
			link.l1.go = "adversary_hire_no_7";
		break;
		
		case "adversary_hire_no_7":
			DialogExit();
			SetMusic("music_romantic");
			SetLaunchFrameFormParam("", "", 0, 15);
			SetLaunchFrameFormPic("loading\inside\kiss.tga");
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 10); //крутим время
			RecalculateJumpTable();
			NextDiag.CurrentNode = "LSC_love"; // оставляем штучки с Мэри на Острове в силе
			pchar.questTemp.LSC.MaryWait = "true";
			AddQuestRecord("LSC", "22");
			bQuestDisableMapEnter = false; //открыть карту
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
		break;
		
		// повторный разговор после расставания с Элен
		case "adversary_hire_return":
			dialog.text = "Te fous-tu de moi ? "+pchar.name+", tu ne m'as vraiment pas oubliée, ouais, hein ?";
			link.l1 = "Bien sûr ! T'ai-je déjà trompée ? J'ai traversé bien des épreuves pendant notre séparation et je n'ai aucune intention de me séparer de toi à nouveau... mon talisman.";
			link.l1.go = "adversary_hire_yes";
			DeleteAttribute(pchar, "questTemp.LSC.MaryWait");
		break;
		
		case "adversary_hire_yes": // Элен заведомо не друг - Мэри идёт сразу, либо если выбрал Мэри
			dialog.text = "Vraiment ? "+pchar.name+"Je te suivrai toujours ! Je ne te mentirai jamais, je ne te trahirai jamais, je le jure !";
			link.l1 = "Je te crois, ma chère... Moi non plus."; // а куда же ты денешься )
			link.l1.go = "adversary_hire_yes_1";
		break;
		
		case "adversary_hire_yes_1":
			dialog.text = ""+pchar.name+", chéri, serre-moi dans tes bras... Nous serons ensemble, n'est-ce pas ? Dis-moi !";
			link.l1 = "Oui, nous serons ensemble, Mary. Pour toujours, ouais, hein ?";
			link.l1.go = "adversary_hire_yes_2";
		break;
		
		case "adversary_hire_yes_2":
			dialog.text = "Tout comme Danielle et Nathaniel ?";
			link.l1 = "(riant) Oui, tout comme eux, ouais, hein ?";
			link.l1.go = "adversary_hire_yes_3";
		break;
		
		case "adversary_hire_yes_3":
			dialog.text = ""+pchar.name+"... Je t'aime ! Je t'épouserai si tu veux, ouais, hein...";
			link.l1 = "Chère Mary... Bien sûr - nous en parlerons plus tard. Ta vie sur ce cimetière de navires est terminée, sortons d'abord d'ici - bienvenue à bord de mon navire et dans le grand monde, ma chère !";
			link.l1.go = "adversary_hire_yes_4";
		break;
		
		case "adversary_hire_yes_4":
			dialog.text = "Passons notre dernière nuit sur cette île ensemble, sur le 'Ceres Smithy'. Juste nous deux. Seulement toi et moi... Je ne te laisserai aller nulle part avant que le matin arrive, ouais, hein ?";
			link.l1 = "Eh bien, nous ne sommes pas sur mon navire, alors je suivrai ton commandement... Ma chère Mary !";
			link.l1.go = "adversary_hire_yes_5";
		break;
		
		case "adversary_hire_yes_5":
			DialogExit();
			npchar.quest.hire = "true";
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			SetMusic("music_romantic");
			DoQuestCheckDelay("LSC_LastNight_CS", 3.0);
			bQuestDisableMapEnter = false; //открыть карту
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
		break;
		
		case "LSC_mary_hire":
			dialog.text = "D'accord, capitaine !";
			link.l1 = "D'accord, je vais te suivre, ouais, hein ?";
			link.l1.go = "LSC_mary_hire_1";
		break;
		
		case "LSC_mary_hire_1":
			DialogExit();
			DoQuestReloadToLocation("LostShipsCity_town", "reload", "reload62", "LSC_Mary_hire");
			if (pchar.questTemp.LSC.Mary != "return") AddQuestRecord("LSC", "24");
			pchar.questTemp.LSC.Mary = "officer";
			RemoveItems(pchar, "key_mary", 1);
		break;
		
	// --> консультации по морским сражениям
		case "sea_bomb":
			dialog.text = ""+pchar.name+"J'ai une idée...";
			link.l1 = "Ah, tu es un vrai gentleman : à peine as-tu rangé ton sabre dans le fourreau que tu me couvres déjà de compliments. Merci beaucoup pour ton aide. Tu m’as vraiment sauvé, ouais, hein ? Présente-toi, je te vois pour la première fois. Tu es ici depuis longtemps ?"+npchar.name+" ? Ce n'est pas sûr ici et je t'ai ordonné de rester sur le navire...";
			link.l1.go = "sea_bomb_1";
		break;
		
		case "sea_bomb_1":
			dialog.text = ""+pchar.name+", il y a tellement de poudre à canon sur cette vieille barcasse, si elle explose, toute l'île s'envolera dans les cieux. Peu importe où rester maintenant. Écoute-moi juste!";
			link.l1 = "Je t'écoute, fais vite, s'il te plaît.";
			link.l1.go = "sea_bomb_2";
		break;
		
		case "sea_bomb_2":
			dialog.text = "La corvette pirate et la frégate. Ils sont dupés en pensant que nous sommes des leurs... Couteau, ouais, hein ? Cela pourrait être une opportunité pour nous. Prenons quelques barils de poudre à canon, une mèche, et naviguons vers eux.\nQuand ils nous laissent nous approcher, nous allumons la mèche, lançons le baril sur l'un des navires et nous éloignons aussi vite que nous pouvons. Ce doit être une chance parfaite pour voir quelques feux d'artifice... Qu'en penses-tu ?";
			link.l1 = "C'est risqué, mais ton plan pourrait bien fonctionner... Seulement s'ils ne nous reconnaissent pas.";
			link.l1.go = "sea_bomb_3";
		break;
		
		case "sea_bomb_3":
			dialog.text = "Risquons-le, "+pchar.name+"?";
			link.l1 = "D'accord. Allons-y ! Les gars ! Prenez trois barils de poudre à canon ! Nous allons foutre le camp d'ici ! J'adore ton imagination, "+npchar.name+"Je n'aurais jamais eu cette idée moi-même.";
			link.l1.go = "sea_bomb_4";
		break;
		
		case "sea_bomb_4":
			dialog.text = "Je te l'avais dit, j'ai mes talents !";
			link.l1 = "... ";
			link.l1.go = "sea_bomb_5";
		break;
		
		case "sea_bomb_5":
			chrDisableReloadToLocation = false;
			DialogExit();
			LAi_SetOfficerType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			npchar.dialog.currentnode = "Mary_officer";
			pchar.questTemp.Saga.BarbTemptation.Bomb = "true";
			AddQuestRecord("BarbTemptation", "15");
			AddQuestUserData("BarbTemptation", "sName", "Mary");
			pchar.questTemp.Saga.BarbTemptation.adviser = "Mary";
		break;
		
		case "fugas":
			dialog.text = "Oui, bien sûr, chéri. Je suis toujours prête à aider, ouais, hein ? Quel est le problème ?";
			link.l1 = "Le navire de Jackman est à l'anse de Sabo-Matila, la lourde frégate 'Centurion'. Ce navire appartenait autrefois aux Hawkes, donc il doit y avoir des objets importants et des documents dans la cabine de Jackman...nous devons l'aborder.";
			link.l1.go = "fugas_1";
		break;
		
		case "fugas_1":
			dialog.text = "Je vois. Comment comptes-tu faire cela avec notre petit oiseau ? Ils ont plus d'hommes et de canons. J'ai regardé à travers la longue-vue, ouais, hein ?";
			link.l1 = "Tu as raison. Jackman a au moins deux fois plus d'hommes que nous, et tous sont des tueurs habiles et des mercenaires. Ce serait de la folie de monter à l'abordage sans les préparatifs adéquats. Une bataille prolongée en mer n'est pas une option non plus. Donc j'ai pensé à d'autres solutions pour accomplir la tâche.";
			link.l1.go = "fugas_2";
		break;
		
		case "fugas_2":
			dialog.text = ""+pchar.name+", ils ne nous ont pas encore reconnus comme ennemis, tout comme ces idiots de Turks... Nous pouvons essayer notre ruse à nouveau...";
			link.l1 = "Mary, je viens de te dire que nous devons aborder la frégate, la couler n’est pas une option.";
			link.l1.go = "fugas_3";
		break;
		
		case "fugas_3":
			dialog.text = "Je le sais, "+pchar.name+". on ne la coulera pas. Écoute, nous allons prendre quelques tonneaux de rhum vides et les remplir de poudre à canon, de mitraille et de mèches courtes. Ensuite, nous naviguerons plus près de leur frégate et lancerons les explosifs improvisés sur leur pont.";
			link.l1 = "Ha ! Tu penses vraiment que ça va marcher ?";
			link.l1.go = "fugas_4";
		break;
		
		case "fugas_4":
			dialog.text = "Et pourquoi pas ? Leur franc-bord est plus haut que le nôtre mais deux ou trois hommes aidés d'une poulie pourraient hisser et lancer un tonneau bien chargé facilement. On criera - 'Voici du rhum gratuit de Knive ! Et les tonneaux exploseront avant même qu'ils ne puissent réagir.";
			link.l1 = "La mitraille explosante transformera ses meilleurs hommes sur le pont en chair à pâté... Diable, ça semble tentant.";
			link.l1.go = "fugas_5";
		break;
		
		case "fugas_5":
			dialog.text = "Utilisons cinq barils, ouais, hein ?"+pchar.name+", nous avons l'avantage de la surprise. Ils ne se douteront de rien ! Nous devons immédiatement lever l'ancre avant qu'ils ne montent à bord, ouais, hein ?";
			link.l1 = "Eh bien, essayons. Ils ne doivent pas nous identifier avant que nous jetions les tonneaux... Bon sang, ça ne sera pas facile de les approcher. Jackman n'est pas un idiot comme l'était Ghoul.";
			link.l1.go = "fugas_6";
		break;
		
		case "fugas_6":
			dialog.text = "Prenons le risque, "+pchar.name+" ! Ça ne fera pas de mal de toute façon.";
			link.l1 = "Bon point, nous n'avons rien à perdre... Préparez les fougasses !";
			link.l1.go = "fugas_7";
		break;
		
		case "fugas_7":
			dialog.text = "Je le ferai, mon capitaine ! Je les préparerai parfaitement, ouais, hein ?";
			link.l1 = "Eh, ils ne t'ont pas laissé assommer ces crabes sur l'île, alors je te laisse botter le cul de quelques pirates ici, hein... Mary, tu es merveilleuse !";
			link.l1.go = "fugas_8";
		break;
		
		case "fugas_8":
			dialog.text = "Merci, "+pchar.name+"Je ne te laisserai pas tomber, ouais, hein ?";
			link.l1 = "En cela, je n'ai aucun doute. J'espère que nous sommes ceux qui ne te décevront pas en bousillant ton plan... Aux armes !";
			link.l1.go = "fugas_9";
		break;
		
		case "fugas_9":
			DialogExit();
			npchar.dialog.currentnode = "Mary_officer";
			pchar.questTemp.Saga.BarbTemptation.Fugas = "true";
			AddQuestRecord("BarbTemptation", "21");
			DeleteAttribute(npchar, "quest.fugas");
		break;
		// <-- консультации по морским сражениям
		
		// --> суп из черепахи
		case "terrapin_grot":
			dialog.text = "Te voilà ! Ça a pris du temps pour te trouver... C'était incroyable, capitaine ! Je n'ai jamais vu un saut aussi époustouflant auparavant ! Tu es toujours mon héros ! Bien que j'admette, tu m'as presque fait avoir une crise cardiaque\nUn jour tu me tueras avec tes tours, cher... Eh bien maintenant, qui diable serait-elle ? Oh "+pchar.name+"Je te laisse t'échapper un instant, et voilà que je te retrouve entouré de hordes de catins !";
			link.l1 = "Mary, cette 'traînée' est Catherine Fox, fille du colonel Fox, le commandant des Renards de Mer. Nous devons l'emmener à Antigua.";
			link.l1.go = "terrapin_grot_1";
		break;
		
		case "terrapin_grot_1":
			dialog.text = "Oh, vraiment ? Quel délice ! Bon, tu vas me parler d'elle... ce soir, quand nous passerons la nuit ensemble, seuls. Maintenant, allons-y, nous devons nous dépêcher !";
			link.l1 = "Tu es la meilleure, Mary. Que ferais-je sans toi ? Catherine, allez !";
			link.l1.go = "terrapin_grot_2";
		break;
		
		case "terrapin_grot_2":
			DialogExit();
			npchar.dialog.currentnode = "Mary_officer";
			LAi_SetOfficerType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			Terrapin_GotoShip();
		break;
		// <-- суп из черепахи
		
		// --> калеуче
		case "on_coast":
			dialog.text = "Enfin tu es réveillé, mon chéri... Salaud ! Ne me fais plus jamais peur comme ça, ouais, hein ?";
			link.l1 = "Mary... ma chère, que s'est-il passé ? Ma tête éclate...";
			link.l1.go = "on_coast_1";
		break;
		
		case "on_coast_1":
			dialog.text = "Quand nous sommes entrés dans la cabine du capitaine, tu étais étendu sur le sol aussi immobile qu'un cadavre. Mon cœur battait la chamade ! Les gars t'ont ramassé et traîné jusqu'à notre navire - juste à temps, car les morts qui gisaient sur le pont ont commencé à se relever\n Quel cauchemar ! Nous ne pouvions rien faire contre eux ! Nous avons rapidement coupé les amarres et tenté de nous éloigner, mais une bordée de leur navire a gravement endommagé notre vaisseau et nous avons perdu le contrôle. C'étaient de vrais démons, ouais, hein ? Et puis ils ont hissé les voiles et ont disparu en un clin d'œil\nNotre navire s'est échoué, alors nous avons dû fuir vers cette côte avant que la tempête ne la détruise. Beaucoup de braves gens sont morts aujourd'hui, mais le navire a survécu à la fin...";
			link.l1 = "Bon travail, Mary... Que ferais-je sans toi ?";
			link.l1.go = "on_coast_2";
		break;
		
		case "on_coast_2":
			dialog.text = "Peut-être que tu te serais noyée, ou tu serais restée sur ce navire, et les morts t'auraient déchirée... Mes mains tremblent encore !";
			link.l1 = "Merci, mon amour. Depuis combien de temps suis-je inconsciente ?";
			link.l1.go = "on_coast_3";
		break;
		
		case "on_coast_3":
			dialog.text = "Pendant toute une journée. J'ai nettoyé tes blessures, t'ai donné des médicaments et t'ai versé un peu de rhum. Tu devrais vite te rétablir. Et ne t'avise pas de mourir sur moi !";
			link.l1 = "Je promets que je ne mourrai pas cette fois, ma chère. Bien que je ne me sente pas très bien...";
			link.l1.go = "on_coast_4";
		break;
		
		case "on_coast_4":
			dialog.text = "Ça, c'est sûr... Était-ce le 'Hollandais Volant', capitaine ? Pourquoi nous ont-ils attaqués ? Et pourquoi n'ont-ils pas tiré avant d'aborder ?";
			link.l1 = "Leur capitaine avait besoin de l'amulette, celle dont j'ai parlé à Tuttuathapak, le chaman indien. C'est pourquoi ils devaient nous aborder, mais dès que leur capitaine a pris l'amulette, ils n'avaient plus besoin de nous... Quel cauchemar ! Un navire habité par les morts ! Incroyable...";
			link.l1.go = "on_coast_5";
		break;
		
		case "on_coast_5":
			dialog.text = "Ouais, il semble que le 'Hollandais Volant' viendrait pour nous tôt ou tard. Quand j'en aurai l'occasion, j'irai à l'église, allumer une bougie pour notre délivrance miraculeuse, et prier notre Seigneur...";
			link.l1 = "Moi aussi, Mary, je suppose. Je dois retourner à ce village. Faire savoir à Tuttuathapak ce qui s'est passé. Ce navire nous a attaqués à cause de l'amulette ! J'espère que ce diable à la peau rouge a une explication sur la raison pour laquelle ces morts-vivants en avaient besoin en premier lieu.";
			link.l1.go = "on_coast_6";
		break;
		
		case "on_coast_6":
			dialog.text = "D'accord. Mais sois prudent - tes blessures sont à peine guéries, ouais, hein ?";
			link.l1 = "Tu es tout le remède dont j'ai besoin. Et... Mary, je t'aime...";
			link.l1.go = "on_coast_7";
		break;
		
		case "on_coast_7":
			dialog.text = "Je t'aime aussi, ma chérie...";
			link.l1 = "... ";
			link.l1.go = "on_coast_8";
		break;
		
		case "on_coast_8":
			chrDisableReloadToLocation = false;//открыть локацию
			DialogExit();
			npchar.dialog.currentnode = "Mary_officer";
			LAi_SetOfficerType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			AddQuestRecord("Caleuche", "5");
		break;
		// <-- калеуче
		
	// --> Мэри вне LSC
		// секс - Мэри не отказывает никогда
		case "cabin_sex":
			dialog.text = RandPhraseSimple(""+pchar.name+", il n'y a pas de plus grand bonheur pour moi que d'être dans tes bras, ouais, hein... Allons-y !",""+pchar.name+"Ouais, hein ? Je voudrais être avec toi à chaque instant de la journée si c'était possible. Allons-y !");
			link.l1 = RandPhraseSimple("Tu es le meilleur, mon amour...","Tu es merveilleux, mon talisman...");
			link.l1.go = "exit";
			AddDialogExitQuest("cabin_sex_go");
		break;
		
		case "sex_after":
			dialog.text = RandPhraseSimple("Mon cher, tu étais incroyable... tu l'es toujours, ouais, hein ?","C'était génial !");
			link.l1 = RandPhraseSimple("Je suis heureux que tu sois contente, mon amour...","Je t'aime, Mary...");
			link.l1.go = "exit";
			NextDiag.TempNode = "Mary_officer";
			chrDisableReloadToLocation = false;//открыть локацию
			npchar.quest.daily_sex = true;
			DeleteAttribute(npchar, "quest.iwantsex"); // belamour для бесконфликтности квестов							
			SetFunctionTimerCondition("Mary_SexReady", 0, 0, 1, false);
		break;
		
		case "room_sex":
			if (CheckAttribute(pchar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "tavern")
			{
				dialog.text = ""+pchar.name+", il n'y a pas de plus grand bonheur pour moi que d'être dans tes bras, ouais, hein ? Mais ce n'est pas le meilleur moment - nous devons attraper ce vaurien de Thibaut avant qu'il ne s'échappe.";
				link.l1 = "Tu as raison comme toujours, ma fille...";
				link.l1.go = "exit";
				break;
			}
			dialog.text = RandPhraseSimple(""+pchar.name+", il n'y a pas de plus grand bonheur pour moi que d'être dans tes bras, ouais, hein... Allons-y !",""+pchar.name+", j'aimerais être avec toi à chaque instant si c'était possible. Allons-y !");
			link.l1 = RandPhraseSimple("Tu es la meilleure, ma fille...","Tu es merveilleux, mon talisman roux...");
			link.l1.go = "room_sex_go";
		break;
		
		case "room_sex_go":
			DialogExit();
			chrDisableReloadToLocation = true;//закрыть локацию
			if (sti(pchar.money) >= 10) AddMoneyToCharacter(pchar, -10);
			if (npchar.chr_ai.type == "actor")
			{
				LAi_SetOfficerType(npchar);
				LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			}
			if (findsubstr(locations[FindLocation(pchar.location)].id, "tavern_upstairs" , 0) == -1)
			{
			//DoQuestReloadToLocation(pchar.location+"_upstairs", "quest", "quest4", "");
			DoFunctionReloadToLocation(pchar.location+"_upstairs", "quest", "quest4", "GiveKissInRoom");
			ChangeCharacterAddressGroup(npchar, pchar.location+"_upstairs", "quest", "quest3");
			} // patch-8
			//DoQuestCheckDelay("Mary_LoveSex", 2.5);
			NextDiag.CurrentNode = "sex_after";
			npchar.greeting = "mary_hire";
		break;
		
		// требует секса, если давно не давал
		case "givemesex":
			dialog.text = RandPhraseSimple(""+pchar.name+", ça fait trop longtemps qu'on n'a pas fait l'amour... Tu m'as complètement oubliée, ouais, hein ! Chéri, je veux me détendre, prenons une chambre pour la nuit et laissons nos soucis pour un autre jour !",""+pchar.name+", tu as été trop occupé et je commence à penser que tu m’as complètement oubliée ! Chéri, je veux... rester seule avec toi. Prenons une chambre pour la nuit, ouais, hein ?",""+pchar.name+", as-tu perdu la tête ? Je veux passer la nuit avec toi, boire du vin, et me détendre. Tu as été trop occupé en mer et tu m'as complètement oubliée !");
			link.l1 = "Mary, ma chère, de quoi parles-tu – 'complètement oubliée'? Sotte fille... Mais j'ai vraiment été trop occupé, les problèmes qui nécessitent mon attention sont sans fin. Pardonne-moi, mon amour. Allons à l'étage, je suis tout à toi pour la nuit, le monde peut attendre !";
			link.l1.go = "room_sex_go";
		// belamour legendary edition -->
			link.l2 = RandPhraseSimple(RandPhraseSimple("Pas aujourd'hui, cher. J'ai mal à la tête.","Mary, ma douce, comment pourrais-je t'oublier ? Allons, plus tard - nous avons du travail à faire..."),RandPhraseSimple("Tu es toujours dans mes pensées, Mary, mais nous ne pouvons pas nous permettre de nous détendre en ce moment.","Mary "+npchar.lastname+", nous n'avons pas le temps pour des bêtises aujourd'hui"));
			link.l2.go = "room_sex_goNS";
		break;
		
		case "room_sex_goNS":
		if(sti(pchar.reputation.fame) > 60)
		{
			ChangeCharacterComplexReputation(pchar,"authority", 2);
			if (npchar.chr_ai.type == "actor")
			{
				LAi_SetOfficerType(npchar);
				LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			}
			NextDiag.TempNode = "Mary_officer";
			chrDisableReloadToLocation = false;
			npchar.quest.daily_sex = true;
			DeleteAttribute(npchar, "quest.iwantsex"); 
			SetFunctionTimerCondition("Mary_SexReady", 0, 0, 1, false);
			pchar.quest.Mary_giveme_sex.over = "yes"; 
			pchar.quest.Mary_giveme_sex1.over = "yes";
			dialog.text = "Eh bien... Que puis-je dire d'autre... Ouais, capitaine !";
			link.l1 = "Ah, tu es un vrai gentleman : à peine as-tu rangé ton sabre dans le fourreau que tu me couvres déjà de compliments. Merci beaucoup pour ton aide. Tu m’as vraiment sauvé, ouais, hein ? Présente-toi, je te vois pour la première fois. Tu es ici depuis longtemps ?";
			link.l1.go = "exit";
		}
		else
		{
			if(bImCasual) Log_Info("To refuse Mary become more famous");
			ChangeCharacterComplexReputation(pchar,"authority", -2);
			dialog.text = "Charles...";
			link.l1 = "Mary, ma chère, de quoi parles-tu - 'complètement oubliée de moi' ? Petite idiote... Mais j'ai vraiment été occupé, ces problèmes sont sans fin. Pardonne-moi, ma fille. Allons à l'étage, le monde peut attendre !";
			link.l1.go = "room_sex_go";
		}
		break;
		// <-- legendary edition
		// ругается за то, что ходил по борделям, ГГ изворачивается
		case "brothel":
			dialog.text = "Ah, le voilà ! Tu ne m'aimes plus, n'est-ce pas ? Dis-moi !";
			link.l1 = "Quoi ?! Mary, quelles sottises racontes-tu ? Pourquoi penses-tu cela ?";
			link.l1.go = "brothel_1";
		break;
		
		case "brothel_1":
			dialog.text = "Alors pourquoi es-tu allé voir ces trainées, ces putains de bordel ? Je sais que tu l'as fait, ne me mens pas ! Il y a quelque chose qui ne te plaît pas chez moi quand nous faisons l'amour, hein ? (pleurant) Dis-moi...";
			link.l1 = "Mary, Mary... calme-toi, s'il te plaît, ma fille. Oui, je suis allé au bordel quelques fois mais seulement pour affaires. Je ne cherchais pas à m'amuser !";
			link.l1.go = "brothel_2";
		break;
		
		case "brothel_2":
			dialog.text = "Et quels 'affaires' t'ont amené à l'étage dans la chambre de débauche ? (sanglots) Tu mens, "+pchar.name+" !";
			link.l1 = "Mary, ma chère, arrête ça enfin... J'avais vraiment quelques affaires avec la maîtresse du bordel. Et je suis monté quelques fois. La dernière fois pour une affaire personnelle du gouverneur - il m'a demandé de retrouver son alliance. Comment aurais-je pu refuser Son Excellence ?";
			link.l1.go = "brothel_3";
		break;
		
		case "brothel_3":
			dialog.text = "";
			link.l1 = "Et comment pourrais-je expliquer à la maîtresse que j'ai besoin de regarder sous le lit à l'étage ? Je ne pouvais pas. Alors j'ai dû acheter une fille de joie pour la nuit pour être autorisé à monter... La deuxième fois, on m'a dit qu'un marchand avait perdu ses papiers de navire là-bas. J'ai dû payer pour une fille à nouveau, afin de fouiller la chambre, et j'ai été bien payé pour les documents...";
			link.l1.go = "brothel_4";
		break;
		
		case "brothel_4":
			dialog.text = "";
			link.l1 = "Troisième fois que j'aidais le commandant local : j'ai dû interroger les catins au sujet d'un officier de la garnison. Cet officier était suspecté d'espionnage et de connexions avec les pirates. Finalement, nous l'avons attrapé et j'ai reçu une belle récompense...";
			link.l1.go = "brothel_5";
		break;
		
		case "brothel_5":
			dialog.text = "";
			link.l1 = "Tu vois maintenant ? Je te le dis, c'était purement pour affaires. Mary, c'est toi que j'aime et dont j'ai besoin. Tu es la meilleure, je le jure ! Tu crois vraiment que j'irais avec une vulgaire traînée du port alors que je t'ai toi ? Comment peux-tu même penser ça de moi !";
			link.l1.go = "brothel_6";
		break;
		
		case "brothel_6":
			dialog.text = ""+pchar.name+" ... Est-ce que tout cela est vrai ? Es-tu honnête avec moi ? Tu n'as pas été avec eux, ouais, hein ? ";
			link.l1 = "Mary, ma chère, tu es la seule femme que j'aime, c'est vrai. Viens plus près, ma douce. Laisse-moi te serrer dans mes bras... Essuie tes larmes et, s'il te plaît, cesse d'être jalouse ! Je ne fréquenterai plus jamais les bordels, si c'est ce que tu veux !";
			link.l1.go = "brothel_7";
		break;
		
		case "brothel_7":
			dialog.text = "Ouais, c'est ce que je veux!... "+pchar.name+"Je suis jalouse parce que je t'aime... Et je ne veux pas te perdre, ouais, hein ? Tu m'entends ? Je tuerai n'importe quelle garce qui ose s'approcher trop près de toi !";
			link.l1 = "Calme-toi... Il n’est pas nécessaire de tuer qui que ce soit. Et tu ne me perdras pas, je te le promets. Ça va, calme-toi. Tu es ma seule et la meilleure fille du monde... Fais-moi confiance, tu l’es.";
			link.l1.go = "brothel_8";
		break;
		
		case "brothel_8":
			DialogExit();
			SetLaunchFrameFormParam("", "", 0, 5);
			SetLaunchFrameFormPic("loading\inside\kiss.tga");
			LaunchFrameForm();
			pchar.GenQuest.BrothelLock = true; // все, больше не походишь по борделям :)
			DeleteAttribute(pchar, "GenQuest.BrothelCount");
		break;
		
		// на Тайясаль
		case "tieyasal":
			dialog.text = ""+pchar.name+", quelle drôle de question ? Je t'aime. Tu m'as sauvée. Je suis ton talisman roux - penses-tu vraiment que je vais te laisser y aller seul ? N'y compte même pas, ouais, hein ! Je suis avec toi ! Quand partons-nous ?";
			link.l1 = "Tu as raison, ma chère, c'était une question étrange... Je te dirai plus tard quand nous partirons. Nous devons d'abord nous préparer.";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "Je suis prête, mon capitaine ! Je te suivrai jusqu'au bout du monde !";
			link.l1 = "Merci, mon amour...";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			DialogExit();
			AddQuestRecord("Tieyasal", "19");
			npchar.quest.Tieyasal = "teleport";
		break;
		
		// Jason Дороже золота
		case "GoldenGirl":
			pchar.quest.Mary_giveme_sex1.over = "yes"; // fix 22-03-20
			pchar.questTemp.GoldenGirl.MaryBlock = "true"; // fix 22-03-20
			dialog.text = "Quel est tout ce vacarme cette fois, Capitaine ? Espagnols, pirates ou pire ?";
			link.l1 = "C'est pire, Mary, bien pire. Le gouverneur a l'intention de rendre visite à une courtisane extrêmement coûteuse et je suis censé l'accompagner en tant que personne d'intérêt, comme promis à la maîtresse. Des discours ennuyeux, du vin hors de prix et des nobles sans intérêt.";
			link.l1.go = "GoldenGirl_1";
			link.l2 = "Bien au contraire, un fardeau d'une invitation à un événement social, organisé par une dame noble. Son Excellence m'a pris par surprise quand il m'a demandé de l'accompagner, mais pour être honnête, je suis impatient de me changer les idées.";
			link.l2.go = "GoldenGirl_3";
		break;
		
		case "GoldenGirl_1":
			dialog.text = "Vraiment ?! Une courtisane ? Tu dis ça comme si c'était pas grave, hein ? Juste s'amuser un peu avec Son Excellence ? Charles, tu es en train de...";
			link.l1 = "Mary, calme-toi, s'il te plaît ! Ce n'est pas comme si j'y allais pour... ce n'est pas un bordel ! Eh bien, c'est un bordel, mais que le diable m'emporte si je ne suis pas un gentilhomme et un homme de parole. Tu ne me fais vraiment pas confiance ? Le gouverneur m'a seulement demandé un petit service et je dois lui rendre ce service, c'est tout !";
			link.l1.go = "GoldenGirl_2";
		break;
		
		case "GoldenGirl_2":
			dialog.text = "Ouais, j'ai entendu parler de quelques 'nobles' comme ça, hein. Je les ai vus en ta compagnie aussi. La courtisanerie est un besoin quotidien pour eux ! 'Hautes' sociétés, 'divertissement' digne mon cul ! Même un mariage ne les empêche pas de rendre visite à ces... dames. Bon sang, je n'avais aucune idée que tu étais comme eux. On n'est même pas... Allez au diable, vous tous !";
			link.l1 = "Mary, attends ! Merde...";
			link.l1.go = "GoldenGirl_6";
		break;
		
		case "GoldenGirl_3":
			dialog.text = "On a bien mérité des vacances, ouais, hein ? Tu crois qu'ils peuvent supporter de voir une dame vêtue d'un manteau rouge ? Imagine tous les chuchotements dans les coins ? Quelqu'un va sûrement s'évanouir, ce serait amusant, non ?";
			link.l1 = "Mary, ma chère, ce n'est pas le genre de fête où l'on emmène une dame... du moins pas une dame comme toi. Eh bien, c'est un peu compliqué mais laisse-moi t'expliquer...";
			link.l1.go = "GoldenGirl_4";
		break;
		
		case "GoldenGirl_4":
			dialog.text = "Wow, ne te donne pas cette peine. Dis-moi juste franchement : je ne suis pas assez bien pour ces crétins en perruques. Une simple fille, pour s'amuser, hein ? Tu es trop gêné de te montrer avec moi dans les parages ? Pas assez bien pour les soirées chics, n'est-ce pas, honorable monsieur Charles de Maure ?";
			link.l1 = "Non, pas du tout. Tu es incroyable et je me fiche de l'impression que nous faisons sur les gens autour de nous. Le gouverneur essaie de résoudre ses problèmes avec mon aide, comme toujours. Je serai comme un précieux trophée dans la pièce. Un invité intéressant pour impressionner les nobles bons à rien.";
			link.l1.go = "GoldenGirl_5";
		break;
		
		case "GoldenGirl_5":
			dialog.text = "Alors je ne suis pas assez bien pour toi, hein ? Je vois, c'est bon, les nobles sont pour les nobles, les paysans sont pour le simple amusement. Bonne chance avec ta haute société. Je te parlerai quand tu seras de retour sur notre humble terre, ouais, hein ?";
			link.l1 = "Mary, attends ! Merde...";
			link.l1.go = "GoldenGirl_7";
		break;
		
		case "GoldenGirl_6":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "GoldenGirl_GirlExit", 10.0);
			pchar.questTemp.GoldenGirl.Angry1 = "true";
		break;
		
		case "GoldenGirl_7":
			DialogExit();
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "GoldenGirl_GirlExit", 10.0);
			pchar.questTemp.GoldenGirl.Angry2 = "true";
		break;
		
		case "GoldenGirl_10":
			dialog.text = "Bonne chance avec ta haute société. Je te parlerai quand tu seras de retour sur notre humble sol, ouais, hein ?";
			link.l1 = "Mary oh, allez !";
			link.l1.go = "GoldenGirl_11";
		break;
		
		case "GoldenGirl_11":
			DialogExit();
			NextDiag.CurrentNode = "GoldenGirl_10";
		break;
		
		case "GoldenGirl_12":
			dialog.text = "Regarde ça, oui ! Notre capitaine égaré dans la haute société !";
			link.l1 = "...";
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Angry1")) link.l1.go = "GoldenGirl_13";
			else link.l1.go = "GoldenGirl_17";
		break;
		
		case "GoldenGirl_13":
			dialog.text = "Tu as disparu dans le bordel toute la journée et maintenant les gens en ville en parlent. Charles, donne-moi une seule bonne raison pour laquelle je devrais te parler maintenant au lieu de, disons, te montrer le Narwal dans ton... ventre ? Tu ne tiens pas beaucoup à moi, ouais, hein ?!";
			link.l1 = "Mary, je vais tout t'expliquer, mais plus tard. Je dois me préparer et aller à un duel. N'hésite pas à me tuer si je survis à cela. En attendant, prends soin de notre nouveau navire, ouais, hein ? Je l'ai gagné comme prix dans une partie de cartes la nuit dernière.";
			link.l1.go = "GoldenGirl_14";
		break;
		
		case "GoldenGirl_14":
			dialog.text = "Oublie le navire, tu as parlé de duel, non ? Les locaux racontent toutes sortes de foutaises auxquelles je ne prête pas attention. Ils disent que tu es censé te battre contre le fils du roi ou le putain de Pape lui-même. Dis-moi, maintenant, qu'est-ce qui se passe, bordel ?!";
			link.l1 = "Cet homme est un bâtard d'un noble très influent, le comte de Levi Vantadur. C'est lui qui m'a défié en premier lieu, et je dois gagner le duel sans lui faire de mal, pour éviter la colère de son père.";
			link.l1.go = "GoldenGirl_15";
		break;
		
		case "GoldenGirl_15":
			dialog.text = "Pendant que je me tourne les pouces sur la baignoire que tu viens de gagner ? Es-tu devenu fou, Charles ?";
			link.l1 = "Je crains que cela doive être ainsi. Le gouverneur m'a fourni quelques officiers nobles pour être mes seconds afin d'éviter toute confusion par la suite. Je ne peux pas t'emmener, toi ou l'un des gars, pour le bien de l'intégrité officielle du duel. C'est trop sérieux, je suis désolé.";
			link.l1.go = "GoldenGirl_16";
		break;
		
		case "GoldenGirl_16":
			dialog.text = "Tu sais ce que je vais faire maintenant ? Je vais aller sur ce fichu navire et me saouler comme il faut, ouais ! Fais ce que tu veux, mais si ce foutu noble ne parvient pas à te tuer, je te jure que je le ferai moi-même !";
			link.l1 = "Mary, tout ira bien, fais-moi confiance. Maintenant, attends... Merde ! Ça recommence !";
			link.l1.go = "GoldenGirl_21";
		break;
		
		case "GoldenGirl_17":
			dialog.text = "Le voilà !   Nous n'avons reçu aucun mot de toi toute la journée ! Nous étions inquiets en entendant les ragots circulant au marché. Ils disent que tu as parié pour des navires et des femmes, et que tu t'es même battu en duel avec une sorte de prince couronné ou même le Pape lui-même ! Qu'est-ce qui se passe, bordel ?";
			link.l1 = "C'est compliqué, Mary. Cela prendra du temps à expliquer. J'ai réussi à gagner une frégate, cependant. Tu devras t'occuper d'elle pendant que je règle mon différend avec son ancien propriétaire.";
			link.l1.go = "GoldenGirl_18";
		break;
		
		case "GoldenGirl_18":
			dialog.text = "Alors ils avaient raison à propos du duel, ouais, hein ? Qui est ce noble enfoiré ? Pourquoi te bats-tu contre lui ?";
			link.l1 = "Je dois le faire. C'est compliqué, mais en bref : j'ai gagné son navire et sa... dame. Il m'a accusé publiquement de tricherie et m'a défié en duel. Cet homme est le bâtard d'un noble très influent, le Comte de Levi Vantadur. Je devrai faire de mon mieux pour éviter de le blesser.";
			link.l1.go = "GoldenGirl_19";
		break;
		
		case "GoldenGirl_19":
			dialog.text = "Une dame ? Je peux comprendre jouer une goélette aux dés, mais... une femme, vraiment ? Ils disaient vrai dans les rues, hein ? Tu l'admets comme ça ?! Comme si j'étais... l'un de tes marins idiots ?";
			link.l1 = "Merde, Mary, ce n'est pas du tout comme ça ! Il l'a gagnée du gouverneur, je l'ai reprise de lui pour la libérer, c'est tout. Il n'y a rien de plus, je le jure !";
			link.l1.go = "GoldenGirl_20";
		break;
		
		case "GoldenGirl_20":
			dialog.text = "Eh bien, peut-être que c'est normal parmi vous les nobles, mais je ne suis pas comme ça, ouais, hein ! Fais ce que tu veux, dis ce que tu veux... va mourir pour elle si tu veux ! Moi, je vais aller sur ce foutu navire que tu as gagné et me saouler. Je croyais que c'était réel et... que ça durerait pour toujours. Je suppose que j'en attendais trop !";
			link.l1 = "Mary, je me fiche de cette femme ! Attends, s'il te plaît... Merde ! Ça recommence...";
			link.l1.go = "GoldenGirl_21";
		break;
		
		case "GoldenGirl_21":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "GoldenGirl_GirlToFregat", 15.0);
		break;
		
		case "GoldenGirl_24":
			dialog.text = "Charles, tu es venu pour moi, ouais, hein ? Je le savais, je n’en ai jamais douté ! Je suis si heureuse de te voir !";
			link.l1 = "Moi aussi, Mary ! Ça m'a tué, tout ce temps. Dieu merci, tu vas bien, ouais, hein ?";
			link.l1.go = "GoldenGirl_25";
		break;
		
		case "GoldenGirl_25":
			if (pchar.questTemp.GoldenGirl == "alarm_fin")
			{
				dialog.text = "Au fait, qu'as-tu fait exactement pour qu'ils me libèrent si facilement ? Sans une vraie bagarre ou fusillade, ouais, hein ? Oh, et j'ai vu cette belle dame sur le pont quand ils m'ont traînée dehors. Que s'est-il passé, Charles ?";
			}
			else
			{
				dialog.text = "Qu'as-tu fait exactement pour qu'ils me libèrent comme ça ? Pas de combat, pas un coup de feu tiré, ouais, hein ! J'ai vu quelques paons britanniques sur le pont quand ils m'ont sortie. C'était quoi tout ça, Charles ?";
			}
			link.l1 = "Tout ce qui compte, c'est que tu sois de retour avec moi. Je t'ai laissé tomber, Mary. Je suis tellement désolé ! J'espère que tu trouveras dans ton cœur la force de me pardonner ! Je déteste la façon dont nous nous sommes quittés la dernière fois.";
			link.l1.go = "GoldenGirl_26";
		break;
		
		case "GoldenGirl_26":
			dialog.text = "Je l'ai déjà fait. Je suis désolé aussi, ouais, hein ? Si seulement je n'avais pas pris tes affaires avec cette dame aussi personnellement... J'aurais mis une vraie garde cette nuit-là. Ils ne nous auraient jamais abattus si facilement ! C'était tellement stupide de ma part !";
			link.l1 = "Le passé c'est le passé. Je t'aime et je ne te laisserai plus jamais comme ça. Je te le promets !";
			link.l1.go = "GoldenGirl_27";
		break;
		
		case "GoldenGirl_27":
			dialog.text = "Je savais que tu ne m'abandonnerais jamais, ouais, hein ? Désolée d'avoir douté de toi, Charles ! Il semble que je ferais mieux de ne pas savoir ce que tu as fait exactement, hein ? Nous sommes de nouveau ensemble et c'est tout ce qui compte.";
			link.l1 = "Je n'ai aucun secret pour toi. Je te dirai...";
			link.l1.go = "GoldenGirl_28";
		break;
		
		case "GoldenGirl_28":
			DialogExit();
			SetLaunchFrameFormParam("Some time has passed...", "", 0.1, 3.0);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 0);
			npchar.dialog.currentnode = "GoldenGirl_28_1";
			LAi_SetActorType(npchar);
			LAi_ActorDialogDelay(npchar, pchar, "", 4.0);
		break;
		
		case "GoldenGirl_28_1":
			if (pchar.questTemp.GoldenGirl == "alarm_fin")
			{
				dialog.text = "Quelle histoire... je doute que quelqu'un d'autre y croirait, ouais, hein ? Je le savais depuis le début ! Je savais que ta nuit 'ludique' était une affaire louche ! Tous ces paons nobles... des bêtes sans cœur ! Au moins, je ne me suis pas trompée sur toi, je savais que tu étais différent, ouais, hein ?";
				link.l1 = "Je suis sûr que beaucoup de gens là-bas me considèrent bien pire. Un véritable monstre sorti des contes de fées.";
			}
			else
			{
				dialog.text = "Quelle histoire... je doute que quelqu'un d'autre y croie, ouais, hein ? Je le savais depuis le début ! Je savais que ta 'nuit espiègle' était une affaire louche ! Politique, espions, conspi-ra-tions. Et toi, encore une fois, tu nous as tous sauvés, ouais, hein ? Mon héros !";
				link.l1 = "Pas sûr de cela. Il y a de fortes chances que la guerre avec la Grande-Bretagne commence dans quelques semaines. Mais j'ai fait ce qu'il fallait, Mary. Tu comptes plus que tout pour moi.";
			}
			link.l1.go = "GoldenGirl_29";
		break;
		
		case "GoldenGirl_29":
			if (pchar.questTemp.GoldenGirl == "alarm_fin")
			{
				dialog.text = "Je me fiche de ce que pensent les gens, si c'est le cas, tu seras mon monstre, Charles ! Les autres n'ont qu'à pleurer ou à s'occuper de moi ! Souviens-toi que je resterai toujours à tes côtés, ouais, hein ?";
			}
			else
			{
				dialog.text = "Je sais, Charles. Je l'ai toujours su, mais c'est si agréable de t'entendre le dire. Sache ceci - je resterai toujours à tes côtés, ouais, hein ?";
			}
			link.l1 = "Jamais douté de ça, Mary. Allons-y, les gars s'inquiètent. Il est temps de mettre les voiles et de foutre le camp d'ici. Tu es de nouveau à mes côtés, et l'horizon n'ira nulle part tout seul.";
			link.l1.go = "GoldenGirl_30";
		break;
		
		case "GoldenGirl_30":
			dialog.text = "D'accord, Capitaine !";
			link.l1 = "";
			link.l1.go = "GoldenGirl_31";
		break;
		
		case "GoldenGirl_31":
			DialogExit();
			npchar.dialog.currentnode = "Mary_officer";
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "sea", "none", "", "", "GoldenGirl_GirlGoOnBoard", 10.0);
			GoldenGirl_MaryBlockDelete(); // fix 22-03-20
		break;
		
		case "GoldenGirl_32":
			dialog.text = "Charles, est-ce vraiment toi ?! J'avais presque perdu tout espoir, ouais, hein ? Mon Dieu, tu m'as tellement manqué ! S'il te plaît, pardonne-moi, je t'en prie, ouais, hein ?";
			link.l1 = "Non, pardonne-moi, je ne l'ai pas vu venir... Dieu merci, tu es arrivée, Mary ! Je suis si heureux !";
			link.l1.go = "GoldenGirl_33";
		break;
		
		case "GoldenGirl_33":
			dialog.text = "En parlant de pardon - pour être tout à fait honnête, j'hésite entre te tirer dessus ou te serrer dans mes bras. Tu ferais mieux de me dire ce qui se passe, ouais, hein ?";
			link.l1 = "Je t'aime, Mary. C'est tout ce que je voulais te dire.";
			link.l1.go = "GoldenGirl_34";
		break;
		
		case "GoldenGirl_34":
			dialog.text = "Ouais, comme si cela aidait, mais... Bon sang, moi aussi, Charles. Je t'aime aussi, ouais, hein. Dieu merci, enfin, nous sommes ensemble !";
			link.l1 = "Et je ne veux pas passer le temps qu'on a à parler de choses qui n'ont pas d'importance. Viens avec moi et je n'oserai pas te quitter ce soir. Même si le ciel commence à tomber sur cette misérable ville. Je ne te quitterai plus jamais. Jamais.";
			link.l1.go = "GoldenGirl_35";
		break;
		
		case "GoldenGirl_35":
			dialog.text = "Il semble que je ferais mieux de ne pas savoir exactement ce que tu as fait, hein ? Nous sommes de nouveau ensemble et c'est tout ce qui compte.";
			link.l1 = "Je n'ai aucun secret pour toi. Je vais te raconter...";
			link.l1.go = "GoldenGirl_36";
		break;
		
		case "GoldenGirl_36":
			DialogExit();
			SetLaunchFrameFormParam("Some time has passed...", "", 0.1, 3.0);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 0);
			npchar.dialog.currentnode = "GoldenGirl_36_1";
			LAi_SetActorType(npchar);
			LAi_ActorDialogDelay(npchar, pchar, "", 4.0);
		break;
		
		case "GoldenGirl_36_1":
			dialog.text = "Tu veux dire que cette... marquise t’a aidé à me ramener ? Et tu as failli déclencher une guerre entre l’Angleterre et la France, ouais, hein ? Ne te méprends pas - c’est tellement romantique et tout, mais que va-t-il se passer maintenant ? ";
			link.l1 = "Je n'en ai aucune idée, Mary. Nous sommes à nouveau ensemble, le reste n'a pas d'importance. Si ceux au pouvoir échouent à étouffer l'affaire... eh bien, je suis prêt à accomplir mon devoir envers la Couronne.";
			link.l1.go = "GoldenGirl_37";
		break;
		
		case "GoldenGirl_37":
			dialog.text = "Et cette marquise à toi ? L'as-tu ramenée aussi ? Les Portugais ont beaucoup parlé d'elle. Il m'a assuré que tu as tenu tête à ses avances comme le château de la Bastille. Je veux bien le croire, ouais, hein, mais je dois l'entendre de ta bouche !";
			link.l1 = "Il n'y a rien entre madame Botot et moi, Mary. Je l'ai aidée, elle m'a aidé, c'est tout. En parlant de Bartholomew, où est-il ?";
			link.l1.go = "GoldenGirl_38";
		break;
		
		case "GoldenGirl_38":
			dialog.text = "Il est parti, ouais, hein ? Il a mis les voiles immédiatement après m'avoir amenée ici. Je ne mettrais jamais les pieds dans ce foutu bordel, alors il m'a loué une chambre, payée d'avance pour quelques semaines, et il est simplement parti. Oh, j'ai presque oublié, ouais, hein ! J'ai une lettre pour toi !";
			link.l1 = "Une lettre ? De Bartholomew le Portugais ? Voilà qui est nouveau. Je n'aime pas où cela mène...";
			link.l1.go = "GoldenGirl_39";
		break;
		
		case "GoldenGirl_39":
			dialog.text = "Vas-y, lis-le. Je vais voir les gars. Ils étaient probablement inquiets. Est-ce que tout le monde est là ? J'espère que cela ne te dérange pas si nous prenons un verre ou deux en bas. Ne te mets pas dans un autre pétrin, ouais, hein ?";
			link.l1 = "D'accord, mais fais attention avec eux, Mary. Je préfère passer du temps avec toi ce soir, plutôt que de devoir ramener des corps ivres au navire. Dieu, je n'arrive toujours pas à croire que je t'ai retrouvée !";
			link.l1.go = "GoldenGirl_40";
		break;
		
		case "GoldenGirl_40":
			DialogExit();
			npchar.dialog.currentnode = "Mary_officer";
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "GoldenGirl_SPGirlReturn", 10.0);
			GoldenGirl_MaryBlockDelete(); // fix 22-03-20
		break;
		
		// Jason Долго и счастливо
		case "LongHappy":
			RemoveItems(pchar, "potionwine", 2);
			dialog.text = "La plage, toi, moi, et du bon vin - Charles, c'est tellement romantique ! Nous devrions faire ça plus souvent, ouais, hein ?";
			link.l1 = "Ravi que cela te plaise. Je pense que nous prendrons plus de temps l'un pour l'autre à partir de maintenant pour des occasions comme celle-ci.";
			link.l1.go = "LongHappy_1";
		break;
		
		case "LongHappy_1":
			dialog.text = "De quoi parles-tu ? Quelque chose est arrivé au navire, hein ? Pourquoi es-tu à genoux, mon amour ?";
			link.l1 = "Parce que je t'aime, Mary. Tu le sais, je le sais, tout le monde le sait. Alors ici et maintenant, face à la mer et au ciel, je te demande, Mary Casper - de me faire l'honneur de te tenir à mes côtés devant les gens et Dieu pour autant de jours qu'il nous sera donné d'en haut. Moi, Charles de Maure, chevalier de Monper, je te demande - veux-tu devenir ma femme ?";
			link.l1.go = "LongHappy_2";
		break;
		
		case "LongHappy_2":
			if (pchar.location == "Shore36")
			{
				dialog.text = "J'ai rêvé de l'entendre, ouais, hein ? Je... tu connais ma réponse Charles... oh, pardon !";
				link.l1 = "Peu importe, ce n'est que du vin et je n'ai jamais aimé cette chemise...";
				link.l1.go = "LongHappy_3";
			}
			else
			{
				dialog.text = "Charles, bien sûr que oui ! Oui, oui, mille fois oui !!! Toi... cet endroit... rien ne peut me rendre plus heureuse !!! Oh mon dieu, je suis tellement heureuse, ouais, hein ?";
				link.l1 = "Tu m'as rendue heureuse, Mary. Et je veux porter un toast à toi, mon Soleil brûlant des Caraïbes !";
				link.l1.go = "LongHappy_4";
			}
		break;
		
		case "LongHappy_3":
			DialogExit();
			chrDisableReloadToLocation = true;//закрыть локацию
			DoQuestCheckDelay("Mary_LoveSex", 1.0);
			npchar.dialog.currentnode = "LongHappy_5";
			LAi_SetStayType(npchar);
		break;
		
		case "LongHappy_4":
			dialog.text = "À toi, mon capitaine et futur époux, ouais, hein ! Tu es la meilleure chose qui me soit jamais arrivée !";
			link.l1 = "Mais ce n'est que le début - à nous ! Et à notre avenir ensemble ! Il y a tant de choses devant nous !";
			link.l1.go = "LongHappy_6";
		break;
		
		case "LongHappy_5":
			dialog.text = "À ta santé, mon capitaine et futur époux, ouais, hein ! Tu es la meilleure chose qui me soit jamais arrivée !";
			link.l1 = "Mais ce n'est que le début - à nous ! Et à notre avenir ensemble ! Il y a tant de choses devant nous !";
			link.l1.go = "LongHappy_6";
		break;
		
		case "LongHappy_6":
			DialogExit();
			chrDisableReloadToLocation = false;
			npchar.dialog.currentnode = "Mary_officer";
			LongHappy_MarryToSenPierre();
		break;
		
		case "LongHappy_7":
			dialog.text = "Charles, l'Abbé Benoît est encore en Martinique, donc nous pouvons continuer, n'est-ce pas ? Mais je ne porterai pas de robe, même pour une messe, j'espère que tu ne seras pas offensé ?";
			link.l1 = "Mary, je t'aime dans n'importe quelle tenue et... eh bien, tu sais. Tu peux porter ce que tu veux, je m'occuperai de quiconque aura un problème avec ça ! Mais je voulais juste te consulter à propos des invités et de la cérémonie, ouais, hein ?";
			link.l1.go = "LongHappy_8";
		break;
		
		case "LongHappy_8":
			if (LongHappy_CheckSaga())
			{
				dialog.text = "Tu sais, la plupart de ceux qui peuvent sincèrement se réjouir de notre bonheur ne seront même pas autorisés à entrer dans cette ville, encore moins dans l'église, ouais, hein ? Donc - marions-nous ici avec toutes les personnes importantes, comme prévu, et ensuite nous naviguerons vers Isla Tessoro pour célébrer comme il se doit avec de vrais amis ! Qu'en penses-tu, ouais, hein ?";
				link.l1 = "Excellente option ! Alors, faisons-le. Je parlerai à l'abbé Benoit, mais nous devons envoyer des invitations et plus encore...";
				link.l1.go = "LongHappy_9";
			}
			else // Сага провалена по времени или утоплен Центурион
			{
				dialog.text = "Tu sais, je n'ai pas beaucoup d'amis à part nos gars de l'équipage. Alors invite ceux que tu juges nécessaires, et je serai simplement contente de ce qu'il y a, ouais, hein !";
				link.l1 = "Comme tu dis, ma chérie. Je parlerai à l'abbé Benoit et organiserai tout, tu mérites la plus magnifique des cérémonies.";
				link.l1.go = "LongHappy_9a";
			}
		break;
		
		case "LongHappy_9":
			dialog.text = "Ne t'inquiète pas, en bonne épouse, je prendrai une partie des préparatifs sur moi, ouais, hein ? J'écrirai à nos amis et organiserai tout, mais d'abord, dis-moi : comment vois-tu ce mariage ?";
			link.l1 = "Mon idéal, c'est toi, moi et nos amis les plus proches. Après toutes ces figures officielles ici en Martinique, nous voudrons un peu de sincérité.";
			link.l1.go = "LongHappy_10";
			link.l2 = "Nous devons nous souvenir de ce jour. Appelez tout le monde ! Personne ne sera laissé de côté !";
			link.l2.go = "LongHappy_11";
		break;
		
		case "LongHappy_9a":
			dialog.text = "Pour toi, une cérémonie avec un aumônier de navire sur le gaillard arrière, sous le coucher du soleil en mer, suffirait, ouais, hein ? Mais, si c'est ce que tu veux - nous allons fêter ça ! Charles ... je vais pleurer maintenant, serre-moi dans tes bras, ouais, hein ...";
			link.l1 = "Mary...";
			link.l1.go = "LongHappy_9b";
		break;
		
		case "LongHappy_9b":
			dialog.text = "C'est bon, je suis calme, ouais, hein ? Désolée, tout cela est si inhabituel. Mais Charles, en bonne épouse, je vais m'occuper de l'organisation. Nous devons aussi organiser une fête pour les gars, ouais, hein ? Mais il est peu probable que tout l'équipage tienne dans l'église. Je vais m'arranger avec la taverne, mais il nous faudra de la gnôle et de l'argent - tu sais comment les marins aiment faire la fête.";
			link.l1 = "D'accord, c'est ce qu'on va faire. Qu'est-ce que je dois préparer, ouais, hein ?";
			link.l1.go = "LongHappy_9c";
		break;
		
		case "LongHappy_9c":
			pchar.questTemp.LongHappy.MarryMoney = 100000;
			pchar.questTemp.LongHappy.MarryRum = 100;
			if (sti(RealShips[sti(pchar.ship.type)].Class) < 2)
			{
				pchar.questTemp.LongHappy.MarryMoney = 200000;
				pchar.questTemp.LongHappy.MarryRum = 150;
			}
			if (GetCompanionQuantity(pchar) > 1)
			{
				pchar.questTemp.LongHappy.MarryMoney = 300000;
				pchar.questTemp.LongHappy.MarryRum = 200;
			}
			dialog.text = "Je pense, "+sti(pchar.questTemp.LongHappy.MarryMoney)+" pesos suffiront, ouais, hein ? "+sti(pchar.questTemp.LongHappy.MarryRum)+"barils de rhum, il n’y a rien de pire que d’être privé de boissons. Dès que tu auras tout rassemblé, viens à la taverne, je m’occuperai du reste.";
			link.l1 = "D'accord, chéri, je le ferai.";
			link.l1.go = "LongHappy_9d";
		break;
		
		case "LongHappy_9d":
			DialogExit();
			npchar.dialog.currentnode = "Mary_officer";
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "LongHappy_GirlNorm", 5.0);
			AddQuestRecord("LongHappy", "10_1");
			AddQuestUserData("LongHappy", "sName", "Mary");
			LongHappy_MarryGoToBenua();
		break;
		
		case "LongHappy_10":
			pchar.questTemp.LongHappy.SmallMarry = "true";
			dialog.text = "Compris, faisons-le. Mais nous devrons visiter Sharptown et préparer tout. Je pense que cinquante barils de rhum et quelques douzaines de barils de vin feront l'affaire, ouais, hein ? Mais, juste au cas où, j'aurai besoin de trois cent mille pesos.";
			link.l1 = "C'est beaucoup, mais l'occasion le mérite. Je vais trouver un moyen, ne t'inquiète pas. Maintenant, je vais passer voir l'abbé et me rendre à Sharptown.";
			link.l1.go = "LongHappy_12";
		break;
		
		case "LongHappy_11":
			pchar.questTemp.LongHappy.BigMarry = "true";
			dialog.text = "Génial, nous allons rassembler tout le monde, ouais, hein ! Mais nous devrons visiter Sharptown et tout préparer - il nous faudra un galion plein de gnôle ! Je pense qu'une centaine de barils de rhum et cinquante barils de vin feront l'affaire. Mais, juste au cas où, j'ajouterai cinq cent mille pesos. Si la fête se termine rapidement, quel genre de fête est-ce, suis-je dans le vrai ?";
			link.l1 = "Oui, nos amis ne doivent pas mourir de soif - je vais tout obtenir, ne t'inquiète pas ! Maintenant, je vais passer chez l'abbé et me rendre à Sharptown.";
			link.l1.go = "LongHappy_12";
		break;
		
		case "LongHappy_12":
			DialogExit();
			npchar.dialog.currentnode = "Mary_officer";
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "LongHappy_GirlNorm", 5.0);
			AddQuestRecord("LongHappy", "10");
			AddQuestUserData("LongHappy", "sName", "Mary");
			LongHappy_MarryGoToBenua();
		break;
		
		case "LongHappy_13":
			dialog.text = "Tout est prêt, Charles, n'est-ce pas ? Je vais m'occuper du déchargement de la boisson, aller à la taverne locale, rencontrer le baron et remettre les invitations. Attends ici, ouais, hein ?";
			link.l1 = "Tu es à la barre, cher ! Alors je vais juste flâner quelque part. Je n'aurais jamais pensé que préparer des expéditions dans la jungle de Maine serait plus facile qu'un mariage.";
			link.l1.go = "LongHappy_14";
		break;
		
		case "LongHappy_14":
			DialogExit();
			SetLaunchFrameFormParam("Several hours have passed...", "", 0.1, 3.0);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 4, 0);
			LongHappy_IslaTesoroRemoveGoods();
			npchar.dialog.currentnode = "LongHappy_15";
			LAi_SetActorType(npchar);
			LAi_ActorDialogDelay(npchar, pchar, "", 4.0);
		break;
		
		case "LongHappy_15":
			dialog.text = "Nous avons terminé ici, Charles, ouais, hein ? J'ai tout arrangé, crois-moi - ce sera merveilleux ! Une chose est gênante : la taverne locale a brûlé pendant une fête il y a une semaine. Mais elle est presque reconstruite, plus grande et meilleure que l'ancienne, ouais, hein ? Nous devrions tous pouvoir y trouver place.";
			link.l1 = "J'espère vraiment que nous ne brûlerons pas celui-ci. J'aimais vraiment le 'Vieux Pivert' ! Quoi qu'il en soit, nous avons encore beaucoup à faire. Il est temps de mettre les voiles. Et oui, Mary - tu es la meilleure, tu le sais, hein ?";
			link.l1.go = "LongHappy_16";
		break;
		
		case "LongHappy_16":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "LongHappy_GirlNorm", 5.0);
			AddQuestRecord("LongHappy", "12");
			pchar.questTemp.LongHappy = "marry_wait";
			pchar.questTemp.LongHappy.DrinkReady = "true";
		break;
		
		case "LongHappy_17":
			dialog.text = "Alors c'est parti, hein ? Les invités sont arrivés, l'église est prête. Je sais que nous sommes plus proches que bien des époux, et ce ne sont que quelques mots importants dans une belle salle, mais maudit soit-je - dans cette ancienne cité aborigène, j'étais moins inquiète, ouais, hein ?";
			link.l1 = "C'est tout à fait normal, mon amour, tout à fait normal. Moi aussi, je suis nerveux. Je pense que le père Benoit attend déjà, je vais le voir et découvrir quand le service commencera.";
			link.l1.go = "LongHappy_18";
		break;
		
		case "LongHappy_18":
			dialog.text = "D'accord, je vais me promener en ville pendant un moment, veux-tu te préparer, ouais, hein ! Charles, tu comprends bien qu'il n'y a pas de retour en arrière ?";
			link.l1 = "Mary, ma chère, pour moi, il n'y avait plus de retour en arrière depuis notre rencontre. J'ai attendu ce jour de tout mon cœur. Ne t'inquiète pas, tout ira bien.";
			link.l1.go = "LongHappy_19";
		break;
		
		case "LongHappy_19":
			DialogExit();
			pchar.GenQuest.CannotWait = true;//запрет ожидания
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "OpenTheDoors", 5.0);
			AddQuestRecord("LongHappy", "14");
			AddQuestUserData("LongHappy", "sName", "Mary");
		break;
		
		case "LongHappy_20":
			dialog.text = "Oui.";
			link.l1 = "";
			link.l1.go = "LongHappy_21";
		break;
		
		case "LongHappy_21":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_27";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_22":
			dialog.text = "Ouais, hein ?";
			link.l1 = "";
			link.l1.go = "LongHappy_23";
		break;
		
		case "LongHappy_23":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_29";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_24":
			dialog.text = "Oui.";
			link.l1 = "";
			link.l1.go = "LongHappy_25";
		break;
		
		case "LongHappy_25":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_31";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_26":
			dialog.text = "";
			link.l1 = "Moi, Charles Henry de Maure, chevalier de Monper, je te prends, Mary Casper, pour épouse, pour t’aimer et te chérir, dès ce jour, pour le meilleur et pour le pire, pour le riche et pour le pauvre, dans la maladie et la santé, jusqu'à ce que la mort nous sépare. Selon la Sainte Loi de Dieu, en présence de Dieu, je fais ce vœu.";
			link.l1.go = "LongHappy_27";
		break;
		
		case "LongHappy_27":
			dialog.text = "Moi, Mary Casper, je te prends, Charles de Maure, pour être mon époux, pour t'avoir et te chérir, dès ce jour, pour le meilleur et pour le pire, dans la richesse et dans la pauvreté, dans la maladie et dans la santé, jusqu'à ce que la mort nous sépare. Selon la Sainte Loi de Dieu, en présence de Dieu, je fais ce vœu.";
			link.l1 = "";
			link.l1.go = "LongHappy_28";
		break;
		
		case "LongHappy_28":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_33";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_29":
			dialog.text = "Ainsi soit-il.";
			link.l1 = "";
			link.l1.go = "LongHappy_30";
		break;
		
		case "LongHappy_30":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_35";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_31":
			dialog.text = "C'est incroyable, ouais, hein ? Je... je pleure, je suis désolée Charles, je vais... mon nez est devenu rouge, n'est-ce pas ?";
			link.l1 = "Mary de Maure, ma femme, tu es ravissante en ce jour comme tous les autres jours !";
			link.l1.go = "LongHappy_32";
		break;
		
		case "LongHappy_32":
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP")) dialog.text = "Merci, Charles, merci... Tout est si solennel et merveilleux ! C'est le plus beau jour de ma vie, ouais, hein !!! Regarde comme tout le monde est heureux ! Mais, il est temps pour toi de faire le tour des invités et d'accepter les félicitations ! Quand tu auras fini - reviens - allons voir les gars à la taverne.";
			else dialog.text = "Merci, Charles, merci... Tout est si solennel et merveilleux ! C'est le plus beau jour de ma vie, ouais, hein !!! Regarde, comme tout le monde est heureux ! Mais, il est temps pour toi de faire le tour des invités et d'accepter les félicitations ! Quand tu auras terminé, reviens, nous sommes attendus à Sharptown.";
			link.l1 = "Je le ferai tout de suite, ma douce. Un baiser et je pars !";
			link.l1.go = "LongHappy_33";
		break;
		
		case "LongHappy_33":
			DialogExit();
			LongHappy_MarryKiss();
		break;
		
		case "LongHappy_34":
			dialog.text = "Charles, mon amour, as-tu déjà parlé aux invités ?";
			link.l1 = "Pas encore, sois patient, ma douce, je reviendrai bientôt, ouais, hein ?";
			link.l1.go = "LongHappy_34_1";
			link.l2 = "Oui, je n'ai jamais entendu autant de félicitations d'un coup. Et tu sais quoi - la plupart parlaient sincèrement !";
			link.l2.go = "LongHappy_35";
		break;
		
		case "LongHappy_34_1":
			DialogExit();
			npchar.dialog.currentnode = "LongHappy_34";
		break;
		
		case "LongHappy_35":
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP")) 
			{
				dialog.text = "Oui, oui ! On m’a aussi dit tant de choses agréables ! Pas tout le monde, bien sûr, certains sont visiblement surpris par ma tenue, ouais, hein ? Mais je suis tellement heureuse que la moitié des choses que les gens disent me passent au-dessus de la tête. Et en général, tout le monde est si adorable. Charles, les gars à la taverne nous attendent déjà - nous devrions aller les voir. Ils seront ravis de féliciter leur capitaine, ouais, hein ?";
				link.l1 = "Nous partons tout de suite. Mais j'aimerais finir cette journée dans un endroit plus romantique que la chambre de la taverne du port. J'espère, ma femme, que cela ne te dérange pas de passer cette nuit dans notre cabine ? D'autant plus que maintenant il n'y a pas de garde sur le navire...";
			}
			else
			{
				dialog.text = "Oui, oui ! Ils m'ont aussi dit tant de choses agréables ! Pas tout le monde, bien sûr, certains sont clairement surpris par ma tenue, ouais, hein ? Mais je suis si heureuse que la moitié des choses que les gens disent me passent au-dessus de la tête. Et en général, tout le monde est si mignon. Charles ! Mais on nous attend à Sharptown, quand mettons-nous les voiles ?";
				link.l1 = "En ce moment. Nous ne pouvons pas laisser nos invités boire toutes les réserves ! J'espère, ma femme, que cela ne te dérange pas de passer cette nuit dans notre cabine ?";
			}
			link.l1.go = "LongHappy_36";
		break;
		
		case "LongHappy_36":
			dialog.text = "Même dans une cabane sur une île déserte, mais seulement avec toi, bien sûr !";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP")) link.l1 = "Je sais. Je t'aime aussi. Allons-y, avant que les gars ne boivent tout notre rhum et ne mettent le feu à la taverne.";
			else link.l1 = "Je t'aime aussi. Alors - mettons les voiles !";
			link.l1.go = "LongHappy_37";
		break;
		
		case "LongHappy_37":
			DialogExit();
			npchar.dialog.currentnode = "LongHappy_38";
			LongHappy_MarryComplete();
		break;
		
		case "LongHappy_38":
			dialog.text = "Oh mon cher, je suis si heureuse ! Aujourd'hui est une journée magnifique...";
			link.l1 = "";
			link.l1.go = "LongHappy_38_1";
		break;
		
		case "LongHappy_38_1":
			DialogExit();
			npchar.dialog.currentnode = "LongHappy_38";
		break;
		
		case "LongHappy_39":
			dialog.text = "Arrache-lui la tête crasseuse, Charles !";
			link.l1 = "";
			link.l1.go = "LongHappy_40";
		break;
		
		case "LongHappy_40":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Angerran") && CharacterIsAlive("Angerran")) // fix 02-04-20
			{
				sld = characterFromId("Angerran");
				sld.dialog.currentnode = "Shivo_6";
			}
			else 
			{
				sld = characterFromId("LH_Dussak");
				sld.dialog.currentnode = "Dussak_5";
			}
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "LongHappy_41":
			dialog.text = "Je vais bien, ouais, hein ? Comment va Nathan, est-il en vie ?";
			link.l1 = "Tellement de sang... Dannie, respire-t-il ? Je le vois respirer !";
			link.l1.go = "LongHappy_42";
		break;
		
		case "LongHappy_42":
			DialogExit();
			sld = characterFromId("Danielle");
			sld.dialog.currentnode = "Danielle_9";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "LongHappy_43":
			dialog.text = "Plus vite, chéri, ne perds pas de temps !";
			link.l1 = "";
			link.l1.go = "LongHappy_43_1";
		break;
		
		case "LongHappy_43_1":
			DialogExit();
			npchar.dialog.currentnode = "LongHappy_43";
		break;
		
		case "LongHappy_44":
			dialog.text = "On a gagné, ouais, hein ? Pardonne-moi, je suis en retard. On était coincés à l'étage, il y avait une douzaine de ces salauds, alors j'étais un peu occupée !";
			link.l1 = "C'est bon, j'ai géré ça. Je suis content d'avoir pu finir cette histoire avec Jacques... enfin. Il a eu ce qu'il méritait.";
			link.l1.go = "LongHappy_45";
		break;
		
		case "LongHappy_45":
			dialog.text = "Alors termine ici et retourne à Sharptown ! Nous devrions vérifier Nathan, ouais, hein ? Il a risqué sa vie pour nous !";
			link.l1 = "Tu as raison, mon amour. Va, je suis juste derrière toi.";
			if (CheckAttribute(pchar, "questTemp.LongHappy.Terrax.Prisoner")) link.l1.go = "LongHappy_46";
			else link.l1.go = "LongHappy_48";
		break;
		
		case "LongHappy_46":
			dialog.text = "Au fait, chéri, nous avons trouvé Marcus, ouais, hein ? Il était dans la cale, ligoté et inconscient.";
			link.l1 = "Il est vivant ?";
			link.l1.go = "LongHappy_47";
		break;
		
		case "LongHappy_47":
			dialog.text = "Il est blessé, mais il ira bien. Tu ne peux pas abattre notre baron, ouais, hein ! Il vient de se réveiller et il est déjà prêt pour la bataille.";
			link.l1 = "C'est notre bon vieux Marcus ! Eh bien, termine ici et à la côte.";
			link.l1.go = "LongHappy_48";
		break;
		
		case "LongHappy_48":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "LongHappy_BarbExit", -1);
		break;
		
		case "LongHappy_49":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_died") && CheckAttribute(pchar, "questTemp.LongHappy.Jino_died"))
			{
				dialog.text = "Je suis tellement désolée, Charles, ouais, hein ? Je... Je suis allée me promener. J'ai vu que tu étais revenu, j'ai entendu que tout le monde était en liesse après la victoire, mais je... Mais qu'est-ce qui ne va pas chez moi, ouais, hein ?";
				link.l1 = "Tout ira bien, ma belle, tout ira bien. Moi aussi, je suis triste. Mais nous avons gagné, et Jacques Barbazon a payé pour tout ce qu'il a fait.";
				link.l1.go = "LongHappy_50";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.LongHappy.Jino_died"))
				{
					dialog.text = "Je me sens tellement mal pour Gino, Charles, ouais, hein ! Quand je l'ai découvert, je n'y ai pas cru ! Comment vas-tu ?";
					link.l1 = "Je n'arrive pas à y croire non plus... c'est tellement stupide, je n'avais pas imaginé cette journée comme ça.";
				}
				else
				{
					dialog.text = "Nous avons encore gagné, ouais, hein ? Mon mari est un vrai fléau pour les barons rebelles des Frères de la Côte ! Les amis sont vivants et les ennemis sont morts - un cadeau glorieux, ouais, hein ?";
					link.l1 = "Ouais, quelle célébration, mais nous l'avons fait, mon amour. Nous l'avons fait, ouais, hein ?";
				}
				link.l1.go = "LongHappy_50";
			}
		break;
		
		case "LongHappy_50":
			dialog.text = "Tu tiens à peine debout, ouais, hein ? Allez, Dannie nous a trouvé une maison ici en périphérie, je ne veux pas retourner sur le navire maintenant. On va s'asseoir et boire à nos amis tombés. Tout cela est trop dur à supporter la tête froide, ouais, hein.";
			link.l1 = "Oui, Mary, allons-y, ouais, hein ?";
			link.l1.go = "LongHappy_51";
		break;
		
		case "LongHappy_51":
			DialogExit();
			LongHappy_LogBook();
			DoQuestCheckDelay("LongHappy_MarryFinalizing", 0.5);
		break;
		
		case "LongHappy_52":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Jino_died"))
			{
				dialog.text = "Je me sens si mal pour Gino, Charles, ouais, hein ? Quand j'ai appris ça, je n'arrivais pas à y croire ! Comment vas-tu ?";
				link.l1 = "Je n'arrive pas à y croire non plus... c'était tellement stupide, je n'imaginais pas cette journée comme ça.";
			}
			else
			{
				dialog.text = "Désolée pour mon retard, mon cher, ouais, hein ? Je me promenais, puis je t'ai vu approcher et j'ai couru aussi vite que possible ! Dannielle m'a laissée partir quand Gino a dit 'le danger est passé', ouais, hein ! Je suis tellement heureuse que tout aille bien maintenant !";
				link.l1 = "Moi aussi, chéri. Et nous avons gagné. Barbazon est mort, les barons rassemblent ce qui reste de leurs équipages. Le combat est terminé.";
			}
			link.l1.go = "LongHappy_53";
		break;
		
		case "LongHappy_53":
			dialog.text = "Charles, je vois que tu tiens à peine debout, mais personne ne peut trouver Tichingitu.";
			link.l1 = "Jan m'a donné un tuyau... Il me semble que notre sévère maskogue est allé faire la noce. Allons faire un tour à la crique de Sabo-Matila, quelques personnes l'ont vu partir dans cette direction.";
			link.l1.go = "LongHappy_54";
		break;
		
		case "LongHappy_54":
			DialogExit();
			LongHappy_LogBook();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			pchar.quest.longhappy_shoregirl.win_condition.l1 = "location";
			pchar.quest.longhappy_shoregirl.win_condition.l1.location = "Shore_ship1";
			pchar.quest.longhappy_shoregirl.function = "LongHappy_SetShoreGirl";
		break;
		
		case "LongHappy_55":
			dialog.text = "Eh bien, voilà notre indigène sévère, ouais, hein ! Allez, Dannie nous a trouvé une maison ici en périphérie - tu es somnambule à ce stade, Charles, ouais, hein !";
			link.l1 = "Et voilà ... enlève-moi, ma belle squaw. Et que tout cela semble n'être qu'un mauvais rêve demain, ouais, hein ?";
			link.l1.go = "LongHappy_56";
		break;
		
		case "LongHappy_56":
			DialogExit();
			DoQuestCheckDelay("LongHappy_MarryFinalizing", 0.5);
		break;
		
		case "LongHappy_57":
			dialog.text = "Ne te méprends pas, mon mari, à l'église tout était tout simplement luxueux, mais ici l'atmosphère est clairement plus chaleureuse, ouais, hein ! Eh bien, c'est tout, Charles, maintenant que tous les ennuis sont derrière nous, nous pouvons nous détendre.";
			link.l1 = "Eh bien, ce n'est pas tout à fait 'tout', ma femme - notre vie continue ensemble ! On peut dire en général que cela vient juste de commencer aujourd'hui. Alors, allons-y, buvons avec nos gars, et ensuite - eh bien, tu te souviens : la cabine, le vin, et nous...";
			link.l1.go = "LongHappy_58";
		break;
		
		case "LongHappy_58":
			DialogExit(); // телепорт в каюту
			DoQuestReloadToLocation("My_Cabin", "rld", "loc1", "LongHappy_InSPcabin");
		break;
		
		case "LongHappy_59":
			dialog.text = "Mon mari... Cela sonne si doux, ouais, hein ? Maintenant tu es à moi, pour toujours !";
			link.l1 = "Je suis à toi depuis longtemps déjà, et je le serai pour toujours, mon amour...";
			link.l1.go = "LongHappy_60";
		break;
		
		case "LongHappy_60":
			DialogExit();
			DoQuestCheckDelay("Mary_LoveSex", 1.0);
			npchar.dialog.currentnode = "LongHappy_61";
			LAi_SetStayType(npchar);
		break;
		
		case "LongHappy_61":
			dialog.text = "Je suis tellement heureuse, Charles ! Et maintenant, nous devons continuer à avancer, ouais, hein ?";
			link.l1 = "Bien sûr, ma belle ! Côte à côte, ensemble et pour toujours !";
			link.l1.go = "LongHappy_62";
		break;
		
		case "LongHappy_62":
			DialogExit();
			LAi_SetOfficerType(npchar);
			npchar.dialog.currentnode = "Mary_officer";
			DoQuestReloadToLocation("FortFrance_town", "reload", "reload1", "LongHappy_InSPComplete");
		break;
		
		// Jason Исла Мона
		case "IslaMona":
			dialog.text = "J'ai bien peur que cette pandémie ne pèse lourdement sur tes filles, Rodrigo. Occupe-les avec du tricot ou quelque chose !";
			link.l1 = "Cette conversation ne mène clairement nulle part. Nous avons convenu que nous irons à l'église demain. Pour prier... bien sûr.";
			link.l1.go = "IslaMona_1";
		break;
		
		case "IslaMona_1":
			DialogExit();
			LAi_SetOfficerType(npchar);
			npchar.dialog.currentnode = "Mary_officer";
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_church_26";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_2":
			dialog.text = "Je suis fier de toi, mon amour !";
			link.l1 = "";
			link.l1.go = "IslaMona_3";
		break;
		
		case "IslaMona_3":
			DialogExit();
			npchar.dialog.currentnode = "Mary_officer";
			sld = characterFromId("Himenes_companion_1");
			sld.dialog.currentnode = "island_man_2";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_4":
			dialog.text = "Eh bien, Charles...";
			link.l1 = "Qu'est-ce qui te tracasse encore, Mary ?";
			link.l1.go = "IslaMona_5";
		break;
		
		case "IslaMona_5":
			dialog.text = "(rit) Le fait que moi et Alan voulions faire la même chose sur l'île que ce que tu as fait ici";
			link.l1 = "Ton... Alan ?";
			link.l1.go = "IslaMona_6";
		break;
		
		case "IslaMona_6":
			dialog.text = "Oui, un sacré rêveur qu'il était, vous pourriez être de grands amis s'il était en vie !";
			link.l1 = "Eh bien, nos goûts se sont croisés sur une chose, c'est sûr !";
			link.l1.go = "IslaMona_7";
		break;
		
		case "IslaMona_7":
			dialog.text = "Quoi ? Ha-ha-ha ! Arrête ça Charles !\nQuoi qu'il en soit, c'est incroyable, nous avons donné tellement de joie à ces gens !";
			link.l1 = "Nous leur avons donné une chance de bonheur, mais le reste, ils l'ont fait par eux-mêmes. Alors, à quoi penses-tu ?";
			link.l1.go = "IslaMona_8";
		break;
		
		case "IslaMona_8":
			dialog.text = "Viens me trouver plus tard et tu le découvriras, ouais, hein ?";
			link.l1 = "Parbleu, je le ferai !";
			link.l1.go = "IslaMona_9";
		break;
		
		case "IslaMona_9":
			DialogExit();
			LAi_SetOfficerType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			DoQuestFunctionDelay("IslaMona_ChurchReloadToRoom", 0.5);
			ChangeCharacterAddressGroup(npchar, "IslaMona_TwoFloorRoom", "goto", "goto4");
			DoQuestCheckDelay("Mary_LoveSex", 2.0);
			NextDiag.CurrentNode = "sex_after";
			npchar.greeting = "mary_hire";
			pchar.questTemp.IslaMona.Doorlock = "true";
		break;
		
		case "tonzag_jailed":
			dialog.text = "J'aime l'obscurité et les espaces exigus. Cela me calme. Enfin, je peux rassembler mes pensées\nC'est comme si tous les soucis et les ennuis... disparaissaient, ouais ! Ce sentiment me manque vraiment...";
			link.l1 = "Tu dois voir un médecin.";
			link.l1.go = "tonzag_jailed_1";
			link.l2 = "D'accord. C'est comme si tu étais de retour sur le 'Ceres Smithy'.";
			link.l2.go = "tonzag_jailed_2";
			locCameraFromToPos(-15.50, 2.28, -1.23, true, -27.00, -10.60, -22.70);
		break;

		case "tonzag_jailed_1":
			dialog.text = "Hélas, je ne suis pas seul. Dans le silence, dans l'obscurité, et dans la solitude, aye. Ce serait parfait.";
			link.l1 = "Garde ça, Mary Casper.";
			link.l1.go = "exit";
		break;

		case "tonzag_jailed_2":
			dialog.text = "Une fois, un crabe est entré dans mon lit - je l'ai découpé et mangé. Ouais, hein ?";
			link.l1 = "Continue comme ça, Mary Casper.";
			link.l1.go = "exit";
		break;
		
		case "tonzag_aftershot":
			dialog.text = "Salaud masqué ! Aïe ! Aide-moi mon cher - nous devons briser les barreaux !";
			link.l1 = "Silence ! J'essaie de comprendre quoi faire !";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "Mary_officer";
			AddDialogExitQuestFunction("Tonzag_TichingituAfterShot");
		break;
		
		case "tonzag_after_boarding":
			dialog.text = "Chéri, ces diables masqués sont partout ! Ils ont fait une énorme brèche dans la coque et rampent à travers comme ces crabes ! Il faut tous les découper, ouais, hein ?";
			link.l1 = "Mary, stay here, find the senior officer, and take command! Take the ship out of the battle; we won't withstand another boarding!";
			link.l1.go = "tonzag_after_boarding_1";
			DelLandQuestMark(npchar);
		break;
		
		case "tonzag_after_boarding_1":
			dialog.text = "Où cours-tu donc ? Je ne suis pas prête à te laisser partir !";
			link.l1 = "Je dois aider Hercule et notre équipage ! Fais-moi confiance, Mary !";
			link.l1.go = "tonzag_after_boarding_2";
		break;

		case "tonzag_after_boarding_2":
			dialog.text = "Oui oui, ma belle !";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_GoToGunDeck");
		break;
		
		case "tonzag_after_victory":
			dialog.text = "Victoire, aye ! Viens à moi, ma chère ! Je te veux pour une heure ou deux !";
			link.l1 = "Euh...";
			link.l1.go = "tonzag_after_victory_1";
			link.l2 = "Allons-y !";
			link.l2.go = "tonzag_after_victory_1";
		break;

		case "tonzag_after_victory_1":
			dialog.text = "Hey, Hercule ! Je suis tellement contente de te voir, barbe grise !";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_MaryBoardingDialog");
		break;

		case "tonzag_after_victory_2":
			dialog.text = "";
			link.l1 = "Mary, Mary, attends ! J'ai besoin de ton rapport !";
			link.l1.go = "tonzag_after_victory_3";
		break;

		case "tonzag_after_victory_3":
			dialog.text = "Hein ? Eh bien, nous avons gagné, ouais ! Ce satané navire a fui. J'ai fendu le crâne d'un salaud en deux !\nOuf, satanés boutons !";
			link.l1 = "Oh, Mary...";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_ShowFrame");
		break;
		
		case "tonzag_dead":
			dialog.text = "Oh mon Dieu, ne me regarde pas, chéri ! Je vais... ouf !";
			link.l1 = "Tiens bon, ma fille. Je suis là !";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "Mary_officer";
		break;

		//--> ----------------------------------- офицерский блок ------------------------------------------
		case "Mary_officer":
			// если шлялся по борделям - устроит небольшой скандал 
			if (sti(pchar.GenQuest.BrothelCount) >= 3 && LAi_grp_playeralarm == 0)
			{
				dialog.Text = ""+pchar.name+" ! J'ai besoin de te parler, ouais, hein ! Sérieusement !";
				Link.l1 = "Que s'est-il passé, Mary ? Y a-t-il un problème ?";
				Link.l1.go = "brothel";
				break;
			}
			ref rLoc = &Locations[FindLocation(pchar.location)];
			dialog.text = LinkRandPhrase("Je t'écoute, mon cher capitaine !","Oui, "+pchar.name+", je suis tout ouïe !","As-tu une mission pour moi, ouais, hein ? "+pchar.name+"?");
			if (CheckAttribute(pchar, "questTemp.Dolly_Tieyasal") && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				Link.l4 = "Mary, je vais visiter l'ancienne cité indienne de Tayasal. Je ne vais pas te mentir : ce voyage est très dangereux et de plus - il inclut une téléportation à travers l'idole dont je t'ai parlé. Me suivras-tu, ouais, hein ?";
				Link.l4.go = "tieyasal";
			}
			////////////////////////казначей///////////////////////////////////////////////////////////
			// boal отчёт о корабле
			if(CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
			{
			    Link.l11 = "Mary, donne-moi un rapport complet du navire.";
			    Link.l11.go = "QMASTER_1";
				
			    // Warship. Автозакупка товара
				Link.l12 = "Je veux que tu achètes certains produits chaque fois que nous sommes à quai.";
				Link.l12.go = "QMASTER_2";
			}

			if (CheckAttribute(npchar, "quest.fugas"))
			{
				Link.l3 = "Mary, j'ai besoin de tes conseils.";
				Link.l3.go = "fugas";
			}
			Link.l1 = "Mary, j'ai un ordre pour toi...";
            Link.l1.go = "stay_follow";
			if (pchar.location == Get_My_Cabin() && !CheckAttribute(npchar, "quest.daily_sex"))
			{
				Link.l2 = RandPhraseSimple("Mon cher, je te veux tout de suite. Ça te va, ouais, hein ?","Mary, que dirais-tu de... rester ensemble un moment ? Juste nous deux, ouais, hein ?");
				Link.l2.go = "cabin_sex";
			}
			if (rLoc.type == "tavern" && !CheckAttribute(npchar, "quest.daily_sex") && sti(pchar.money) >= 10)
			{
				Link.l2 = RandPhraseSimple("Mary, louons une chambre et restons ensemble ?","Mon amour, je veux rester avec toi en privé... que dirais-tu de louer une chambre et d'oublier tout pendant quelques heures ?");
				Link.l2.go = "room_sex";
			}
			link.l9 = "Ce n'est rien pour l'instant, Mary.";
			link.l9.go = "exit";
			NextDiag.TempNode = "Mary_officer";
		break;
		
		/////////////////////////// ответы для казначея ///////////////////////////////////
		case "QMASTER_1":
			dialog.Text = "Charles, c'est une beauté, ouais, hein ? On a réparé ce tout petit trou sous la ligne de flottaison et séché les voiles. Qu- Qu'est-ce que tu attendais ? Ne me regarde pas comme ça, je n'ai jamais étudié pour être un intendant.";
			Link.l1 = "Désolé, Mary, je n'ai vraiment pas réfléchi.";
			Link.l1.go = "exit";
		break;	

		case "QMASTER_2":
			dialog.text = "Charles, mais je suis prête ! J'ai déjà ma garde-robe et ma lame. Mais merci de demander, c'est vraiment gentil de ta part, ouais, hein ?";
			link.l1 = "Mais je ne... Peu importe, oublie ça, mon cher, tout va bien.";
			link.l1.go = "exit";
		break;

		case "stay_follow":
            dialog.Text = "Ordres ?";
            Link.l1 = "Tiens-toi là !";
            Link.l1.go = "Boal_Stay";
            Link.l2 = "Suis-moi et ne traîne pas !";
            Link.l2.go = "Boal_Follow";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			if(sGun != "")
			{
				rItm = ItemsFromID(sGun);
				if(CheckAttribute(NPChar, "chr_ai.gun.bulletNum") && sti(NPChar.chr_ai.gun.bulletNum) > 1)
				{
					Link.l3 = "Mary, change les munitions pour les armes à feu.";
					Link.l3.go = "SetGunBullets";
				}	
			}		
		break;
		
		case "SetGunBullets":
			Dialog.Text = "Choisir le type de munitions :";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(NPChar.chr_ai.gun.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetConvertStr(rItem.name, "ItemsDescribe.txt");
				Link.(attrL).go = "SetGunBullets1_" + i;
			}
		break;	

		case "SetGunBullets2":
			i = sti(NPChar.SetGunBullets) + 1; 
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(NPChar, GUN_ITEM_TYPE, sBullet);
			LAi_GunSetUnload(NPChar, GUN_ITEM_TYPE);
			NextDiag.CurrentNode = NextDiag.TempNode;
			rItem = ItemsFromID(sBullet);
			notification(GetFullName(NPChar)+" "+XI_ConvertString("AmmoSelectNotif")+GetConvertStr(rItem.name, "ItemsDescribe.txt")+"", "AmmoSelect");
			DeleteAttribute(NPChar,"SetGunBullets");
			DialogExit();
		break;		
		
        case "Boal_Stay":
            Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
            AddDialogExitQuestFunction("LandEnc_OfficerStay");
            dialog.Text = "Aussitôt, mon capitaine !";
            Link.l1 = "Ah, tu es un vrai gentleman : à peine as-tu rangé ton sabre dans le fourreau que tu me couvres déjà de compliments. Merci beaucoup pour ton aide. Tu m’as vraiment sauvé, ouais, hein ? Présente-toi, je te vois pour la première fois. Tu es ici depuis longtemps ?";
            Link.l1.go = "Exit";
            Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
        break;
        
        case "Boal_Follow":
            SetCharacterTask_FollowCharacter(Npchar, PChar);
            dialog.Text = "Aussitôt, mon capitaine !";
            Link.l1 = "Ah, tu es un vrai gentleman : à peine as-tu rangé ton sabre dans le fourreau que tu me couvres déjà de compliments. Merci beaucoup pour ton aide. Tu m’as vraiment sauvé, ouais, hein ? Présente-toi, je te vois pour la première fois. Tu es ici depuis longtemps ?";
            Link.l1.go = "Exit";
        break;
		//<-- ----------------------------------- офицерский блок ----------------------------------------
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
