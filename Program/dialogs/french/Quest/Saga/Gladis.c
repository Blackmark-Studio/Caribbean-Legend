// Глэдис МакАртур - приемная мать Элен
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if(pchar.questTemp.Saga == "helena1")
			{
				dialog.text = "Ah, Capitaine ! Vous savez, j'ai tout raconté à Hélène. Vous ne pouvez pas imaginer quel poids a été ôté de mon esprit !";
				link.l1 = "Vous avez fait tout ce qu'il fallait, Mademoiselle McArthur. La jeune fille doit connaître la vérité. Et je suis ici à cause d'elle.";
				link.l1.go = "Helena_hire";
			}
			else
			{
				dialog.text = "Salutations, "+pchar.name+"Je suis ravi de te voir ! Tu veux du rhum ?";
				link.l1 = "Merci, Mademoiselle McArthur, mais je suis trop occupé en ce moment.";
				link.l1.go = "exit";			
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "FindHelena":
			dialog.text = "Que voulez-vous, Monsieur ?";
			link.l1 = "Es-tu Gladys McArthur?";
			link.l1.go = "FindHelena_1";
		break;
		
		case "FindHelena_1":
			dialog.text = "Je le suis. Je ne me souviens pas de vous, jeune homme. Alors, voudriez-vous expliquer ce que vous attendez de moi ?";
			link.l1 = "Je suis intéressé par l'histoire de la disparition de votre fille, Mademoiselle McArthur. Qu'est-ce qui vous a fait penser qu'elle avait disparu ? J'ai entendu dire qu'Helen avait un équipage très habile...";
			link.l1.go = "FindHelena_2";
		break;
		
		case "FindHelena_2":
			dialog.text = "Ah, je suis absolument sûre ! Voyez-vous, l'anniversaire de la mort de mon défunt mari était il y a cinq jours. Hélène adorait son père et elle n'aurait jamais manqué cette date. Elle n'était partie que pour quelques jours afin de recevoir une cargaison de bois rouge de la part des Miskitos amicaux. \nLes Indiens respectent et craignent notre patron Jan Svenson, ils ne lui feraient jamais de mal. Monsieur Svenson leur a déjà parlé. Le bois a été chargé le même jour. Personne n'a vu Hélène depuis.";
			link.l1 = "Peut-être que les pirates l'ont attaquée ?";
			link.l1.go = "FindHelena_3";
		break;
		
		case "FindHelena_3":
			dialog.text = "Balivernes ! Vous devez déjà savoir que monsieur Svenson est l'un des cinq barons pirates et un membre du conseil des Frères de la Côte. Aucun pirate n'est autorisé à chasser ici sans sa permission. Cela pourrait être un novice cependant...";
			link.l1 = "Et qu'en est-il des Espagnols ? Aurait-elle pu affronter une patrouille espagnole ?";
			link.l1.go = "FindHelena_4";
		break;
		
		case "FindHelena_4":
			dialog.text = "Je ne suis pas doué pour la politique, mais on dit que les mines d'or et d'argent locales sont complètement épuisées, pas assez de trésors pour risquer la vie de nobles hidalgos. Alors ils sont rares ici. De plus, les Indiens leur sont hostiles.\nUne rencontre fortuite avec une patrouille espagnole n'aurait pas pu mal se terminer pour Hélène, elle n'a rien fait d'illégal de leur point de vue. Le 'Rainbow' arborait un drapeau néerlandais et tous les papiers d'Hélène étaient en règle, y compris une licence commerciale.";
			link.l1 = "Quelque chose de spécial s'est-il passé avant son dernier voyage? Peut-être un événement étrange que vous auriez manqué?";
			link.l1.go = "FindHelena_5";
		break;
		
		case "FindHelena_5":
			dialog.text = "Ah, non ! Dieu merci, nous menons ici des vies paisibles. Cependant, il y a quelques semaines, Hélène a reçu une lettre d'un autre prétendant indésirable la suppliant pour un rendez-vous. C'est une jolie fille, mais pas une riche. Elle a donc beaucoup de prétendants, bien qu'elle n'en aime aucun et qu'elle ne veuille pas se marier. Elle en a déjà berné beaucoup de cette manière. Si frivole, tout comme sa mère l'était !";
			link.l1 = "Vous ne ressemblez pas à ce genre de femme, Mademoiselle McArthur...";
			link.l1.go = "FindHelena_6";
		break;
		
		case "FindHelena_6":
			dialog.text = "Quoi ? Ah, peu importe, j'ai le cœur brisé. Que disais-je ? Ah, oui, la lettre. Bref, cette lettre a été écrite par Jimmy Higgins. C'est un des hommes de Jackman et il vit à Maroon Town. Il visite notre ville assez souvent. Jackman est aussi un baron pirate, mais monsieur Svenson ne l'aime pas, je ne sais pas pourquoi.";
			link.l1 = "Et Helene ?";
			link.l1.go = "FindHelena_7";
		break;
		
		case "FindHelena_7":
			dialog.text = "Oh, elle riait aux éclats. Elle avait reçu une proposition du capitaine d'une corvette anglaise un jour plus tôt et elle l'avait même refusé. Et maintenant ce simple maître d'équipage d'une vieille barque de pirate... Pas une chance, la fille de Sean McArthur exige un époux plus imposant !";
			link.l1 = "Et quel était le nom de ce capitaine anglais ?";
			link.l1.go = "FindHelena_8";
		break;
		
		case "FindHelena_8":
			dialog.text = "Oh, comment saurais-je ? Les vrais gentilshommes sont des invités rares ici. Je suis désolée, je ne voulais pas vous offenser. Demandez à ce Higgins. Il doit se souvenir de son nom. Jimmy essayait de défier ce capitaine en duel pour Helen. Ses amis ont à peine réussi à l'en empêcher. Mais tous deux ont quitté Blueweld quelques jours avant qu'Helen ne prenne la mer.";
			link.l1 = "Eh bien, merci pour votre histoire. Je vais essayer de retrouver votre bien-aimée. Si j'apprends quelque chose, je vous le dirai, à vous ou à monsieur Svenson. J'espère retrouver votre fille vivante et entière.";
			link.l1.go = "FindHelena_9";
		break;
		
		case "FindHelena_9":
			dialog.text = "Allez-vous la chercher ? Que Dieu soit avec vous, qu'il vous guide et fortifie votre main ! Je prierai pour vous ! Dites-moi votre nom, homme honorable ?";
			link.l1 = "Bonjour, ami."+pchar.name+". "+GetFullName(pchar)+"J'espère revenir bientôt avec de bonnes nouvelles, Mademoiselle McArthur. Adieu !";
			link.l1.go = "FindHelena_10";
		break;
		
		case "FindHelena_10":
			DialogExit();
			NextDiag.CurrentNode = "FindHelena_wait";
			AddQuestRecord("Saga", "1");
			pchar.questTemp.Saga = "maruntown";//идем к Джекману
			SetFunctionTimerCondition("Gladis_SetHome", 0, 0, 1, false);
			int iTime = 25-MOD_SKILL_ENEMY_RATE;
			if(bImCasual)
			{
				NewGameTip("Exploration mode: quest duration doubled");
				SetFunctionTimerCondition("Helena_AntiguaOver", 0, 0, iTime*2, false);
			}
			else SetFunctionTimerCondition("Helena_AntiguaOver", 0, 0, iTime, false);
		break;
		
		case "FindHelena_wait":
			dialog.text = "As-tu des nouvelles de ma pauvre fille, "+pchar.name+"?";
			link.l1 = "Je suis désolé, Mademoiselle McArthur, je n'ai rien de nouveau à vous annoncer pour l'instant mais ne désespérez pas. Je continuerai mes recherches. L'absence de mauvaises nouvelles est déjà une bonne nouvelle en soi.";
			link.l1.go = "exit";
			NextDiag.TempNode = "FindHelena_wait";
		break;
		
		case "Helena_die":
			dialog.text = "Vous êtes arrivé trop tard, Capitaine. Le corps de ma pauvre fille a été trouvé sur les rivages d'Antigua. Seigneur, comme ils l'ont même torturée avant sa mort ! J'ai échoué à préserver ma belle fille...";
			link.l1 = "Je suis désolé. Il n'y avait rien que je pouvais faire...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Gladis_exit";
		break;
		
		case "Gladis_exit":
			dialog.text = "Ah, jeune homme, je vous en prie, laissez-moi seul avec mon chagrin...";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Gladis_exit";
		break;
		
		case "Gladis_regard":
			dialog.text = "Je ne sais même pas comment vous remercier, Capitaine, d'avoir sauvé ma fille. Elle m'a tout raconté et j'admire votre bravoure et votre honneur. Tenez, prenez ces doublons d'or. Ce n'est pas grand-chose, mais je vous les offre en toute sincérité. Et n'allez pas songer à refuser !";
			link.l1 = "D'accord, Gladys, je ne le ferai pas. Mais j'ai sauvé ta fille non pas pour des pièces et j'espère que tu le sais.";
			link.l1.go = "Gladis_regard_1";
			link.l2 = "Garde cet argent pour toi, Gladys. Tu en as plus besoin que moi.";
			link.l2.go = "Gladis_regard_2";
			sld = characterFromId("Helena");
			LAi_SetStayType(sld);
			AddCharacterExpToSkill(pchar, "Leadership", 50);
			// открыть город
			LocatorReloadEnterDisable("SantaCatalina_town", "reload1_back", false);
			LocatorReloadEnterDisable("SantaCatalina_town", "reload2_back", false);
			LocatorReloadEnterDisable("SantaCatalina_town", "gate_back", false);
		break;
		
		case "Gladis_regard_1":
			TakeNItems(pchar, "gold_dublon", 100);
			dialog.text = "Je suis heureux d'avoir pu d'une manière ou d'une autre te rendre la pareille pour ton acte honorable. Les portes de ma maison te sont toujours ouvertes. Hélène et moi serons heureux de te voir à tout moment.";
			link.l1 = "Merci, Mademoiselle McArthur. Je vous rendrai visite, vous et Helen, quand l'occasion se présentera.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Gladis_wait";
		break;
		
		case "Gladis_regard_2":
			dialog.text = "Ah, je vous en prie... Je voulais seulement vous rendre la pareille pour votre acte honorable. Sachez que les portes de ma maison vous sont toujours ouvertes. Helen et moi serons ravis de vous voir à tout moment.";
			link.l1 = "Merci, Mademoiselle McArthur. Je viendrai vous voir, vous et Helen, dès que l'occasion se présentera.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Gladis_wait";
			pchar.questTemp.Saga.Helena_friend = "true";//атрибут поведения Элен в будущем
		break;
		
		case "Gladis_wait":
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.Dialogs.Gladys")) {
				dialog.text = "Capitaine, vous êtes toujours le bienvenu chez nous ! Êtes-vous ici pour Helen ? Je crains qu'elle ne se soit enfermée dans sa chambre - elle doit être épuisée des derniers jours. Ne vous inquiétez pas, cela lui arrive parfois.";
				link.l1 = "Vraiment ? Es-tu sûr qu'elle va bien ?";
				link.l1.go = "after_drinking";
				
				DeleteAttribute(pchar, "questTemp.HelenDrinking.Dialogs.Gladys");
				break;
			}
		
			dialog.text = "Ah, Monsieur de Maure ! Je suis toujours heureux de voir le sauveur de ma fille dans ma maison. Voulez-vous voir Hélène ? Elle est à l'étage dans sa chambre. Après la perte de 'Rainbow' et son merveilleux sauvetage, elle évite de sortir. C'est la première fois que je la vois dans un tel état de confusion...";
			link.l1 = "Merci, Mademoiselle McArthur.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Gladis_wait";
		break;
		
		case "Gladis_history":
			dialog.text = "Ah, Monsieur de Maure ! Je suis toujours ravi de voir le sauveur de ma fille chez moi. Voulez-vous voir Helen ?";
			link.l1 = "Non. Je veux te poser quelques questions et j'espère vraiment sur ta franchise. La sécurité d'Helen en dépend. Cette bague te dit-elle quelque chose ?";
			link.l1.go = "Gladis_history_1";
		break;
		
		case "Gladis_history_1":
			RemoveItems(pchar, "bucher_ring", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "Bon Dieu! C'est... la bague de son père!";
			link.l1 = "Chez Monsieur McArthur?";
			link.l1.go = "Gladis_history_2";
		break;
		
		case "Gladis_history_2":
			dialog.text = "Non. Helen est notre belle-fille, mais elle ne le sait pas, ses parents sont morts alors j'ai décidé de l'accueillir comme mon enfant. Sean l'a adoptée, mais même lui ne savait pas qu'elle n'est pas ma fille.";
			link.l1 = "Alors, qui sont ses vrais parents ?";
			link.l1.go = "Gladis_history_3";
		break;
		
		case "Gladis_history_3":
			dialog.text = "Je sais que son père était un pirate appelé 'Boucher' sur la frégate 'Neptune'. Je ne l'ai vu que deux fois. Et sa mère était une belle jeune femme, cheveux roux, habillée en vêtements d'homme. C'est à peu près tout ce que je peux vous dire sur elle, sauf qu'elle était une mauvaise mère.\nJe ne laisserais jamais un tel bébé entre les mains d'étrangers. Ils sont tous deux morts tragiquement. Et le courrier promis s'est montré vingt ans plus tard et s'est avéré être vous. Le Boucher vous a-t-il envoyé ? Est-il vivant ?";
			link.l1 = "Calmez-vous, Mademoiselle Gladys ! Il n'y a aucune raison de suspecter que Boucher ait ressuscité, bien que vous soyez la deuxième personne à avoir cette idée. J'ai récemment rencontré un homme qui était censé vous montrer cette bague...";
			link.l1.go = "Gladis_history_4";
		break;
		
		case "Gladis_history_4":
			dialog.text = "...";
			link.l1 = "Un simple incident l'avait empêché de le faire à temps et il souffrit toute sa vie d'avoir échoué dans la dernière mission de son capitaine. Il est mort il n'y a pas longtemps et... enfin, assez de mauvaises nouvelles. Dis-moi, Gladys, la mère d'Helen n'a-t-elle laissé aucun souvenir à son enfant en mémoire d'elle ? Peut-être une petite chose ?";
			link.l1.go = "Gladis_history_5";
		break;
		
		case "Gladis_history_5":
			dialog.text = "Elle m'a laissé un étrange morceau d'une vieille carte. Elle a plaisanté en disant que c'était son héritage. Que peut bien valoir ce bout de papier ? Je crois que ce n'était qu'une mauvaise plaisanterie. Elle était surexcitée et un peu hors d'elle. Mais j'ai conservé ce 'cadeau'.\nQui sait... Si tu veux, je peux te le donner si tu me promets de me raconter toute l'histoire un jour.";
			link.l1 = "Absolument, Mademoiselle McArthur. Je vais garder ce déchet avec moi pour un moment. J'ai besoin de parler avec monsieur Svenson.";
			link.l1.go = "Gladis_history_6";
		break;
		
		case "Gladis_history_6":
			GiveItem2Character(pchar, "map_half_beatriss"); //половинка карты
			PlaySound("interface\important_item.wav");
			dialog.text = "Vous nous avez encore aidés, Monsieur de Maure ! Et je n'ai aucune idée de comment vous remercier. Prenez au moins le pistolet de mon mari. Il en était toujours fier et m'a dit qu'il est très rare. Il traîne ici depuis longtemps. Qu'il vous serve ! Prenez-le, prenez-le !";
			link.l1 = "Merci, Gladys. Ce pistolet est vraiment excellent. Merci et adieu.";
			link.l1.go = "Gladis_history_7";
			if (CheckCharacterItem(pchar, "chest"))
			{
				link.l2 = "Laisse ce pistolet servir Helen. J'ai assez d'armement.";
				link.l2.go = "Gladis_history_8_1";
			}
		break;
		
		case "Gladis_history_7":
			DialogExit();
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "pistol5");
			pchar.questTemp.Saga = "svenson2";
			NextDiag.CurrentNode = "First time";
			DeleteAttribute(pchar, "questTemp.Saga.Helena_friend");
			AddQuestRecord("Saga", "22");
			AddCharacterExpToSkill(pchar, "Leadership", 50);
		break;
		
		case "Gladis_history_8_1":
			dialog.text = "Mais pourquoi refuses-tu sans cesse mes cadeaux ? Tu me rends triste...";
			link.l1 = "Je pense que je pourrai désormais te rendre heureux. Je vais te rendre l'or que le courrier devait te livrer pour la digne garde de la fille du capitaine Butcher. Certes, ces doublons ne rembourseront pas tout ton amour et ta loyauté, mais ils t'appartiennent de toute façon. Tu peux en faire ce que tu veux.";
			link.l1.go = "Gladis_history_8";
		break;
		
		case "Gladis_history_8":
			dialog.text = "Ah, Capitaine ! Je ne sais pas quoi dire... Je ne pouvais pas imaginer que de tels... hommes honorables existent ! Allez voir ma fille et dites-lui la bonne nouvelle !";
			link.l1 = "Je suis en route, Mademoiselle McArthur.";
			link.l1.go = "Gladis_history_9";
		break;
		
		case "Gladis_history_9":
			DialogExit();
			RemoveItems(pchar, "chest", 1);
			pchar.questTemp.Saga = "svenson2";
			NextDiag.CurrentNode = "First time";
			AddQuestRecord("Saga", "22");
			sld = characterFromId("Helena");
			GiveItem2Character(sld, "pistol5");
			EquipCharacterbyItem(sld, "pistol5");
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			
			pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) + 1;
		break;
		
		case "Helena_hire":
			dialog.text = "Es-tu sérieux ? Que veux-tu dire ?";
			link.l1 = "Selon la demande de monsieur Svenson, je vais employer Helen sur mon navire en tant qu'officier. Elle est en grand danger. Helen aura besoin d'une protection solide pendant que Jan et moi traitons cette affaire. J'espère pouvoir fournir une telle protection.";
			link.l1.go = "Helena_hire_1";
		break;
		
		case "Helena_hire_1":
			dialog.text = "Ah, c'est si bon ! Je n'oserais pas te demander cela moi-même. Ce sera la meilleure protection pour ma fille. Helen sera si heureuse de naviguer à nouveau !";
			link.l1 = "Merci pour votre compliment, Mademoiselle McArthur. Et maintenant, je dois voir votre... belle-fille.";
			link.l1.go = "exit";
			LocatorReloadEnterDisable("SantaCatalina_houseSp3", "reload2", false);//открыть спальню Элен
			sld = characterFromId("Helena");
			sld.dialog.currentnode = "Helena_hire";
			pchar.questTemp.Saga = "helena2";
		break;
		
		case "saw_sex":
			dialog.text = "Oh, mon Dieu ! Ma petite fille !";
			link.l1 = "Gladys, ne sais-tu pas frapper ?!";
			link.l1.go = "saw_sex_1";
		break;
		
		case "saw_sex_1":
			dialog.text = "Oh, pardonnez-moi, jeunes gens ! Je m'en vais ! Hélène, souviens-toi de ce que je t'ai dit !";
			link.l1 = "Bonjour, mon ami.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveGladysTalk");
		break;
		
		case "after_drinking":
			dialog.text = "Je pense que cette fois elle s'est simplement surmenée. Elle m'a tout raconté, Capitaine ! Merci de l'avoir aidée à choisir un nouveau navire hier !";
			link.l1 = "Hein ? Hum, de rien. Au revoir, Mme MacArthur.";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "Gladis_wait";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}
