// диалог прочих и малозначимых НПС
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	bool bOk;
	int i, n, iTemp;
	string attrL;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	attrL = Dialog.CurrentNode;
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Y a-t-il quelque chose dont vous avez besoin ?";
			link.l1 = "Non, pas maintenant.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// --> матрос на корабле, прибытие в Сен-Пьер
		case "Startsailor":
			dialog.text = "Que diable, terre enfin ! Réveillez-vous, Monsieur... quel que soit votre nom... Nous sommes arrivés !";
			link.l1 = "A-ah! C'est déjà le matin? Quelle est cette maudite chaleur et humidité?";
			link.l1.go = "Startsailor_1";
			link.l2 = "Je dis ! Charles de Maure ! Un noble, vous savez. Comment pouvez-vous même boire par cette chaleur ? Je préférerais de l'eau, parbleu.";
			link.l2.go = "Startsailor_1a";
		break;
		
		case "Startsailor_1":
			dialog.text = "Habituez-vous, Monsieur. C'est le seul temps que nous ayons ici... cela pourrait toujours être pire.";
			link.l1 = "Comment cela pourrait-il empirer !? Je ne porte qu'une chemise en lin et j'ai la sueur qui coule le long de mon dos !";
			link.l1.go = "Startsailor_2";			
		break;
		
		case "Startsailor_2":
			dialog.text = "Vous verrez, haha ! Ça pourrait être la saison des ouragans ! Dépêchez-vous, monsieur. La chaloupe ne va pas vous attendre. Vous ne voulez pas nager jusqu'à la Martinique, n'est-ce pas ?";
			link.l1 = "Donne-moi juste un moment, veux-tu ? Où est mon épée ? Ah, la voilà...";
			link.l1.go = "Startsailor_3";			
		break;
		
		case "Startsailor_3":
			dialog.text = "Vous n'êtes plus en Europe... Soyez prudent, Monsieur. Ce sont des temps troublés. Les rumeurs disent que la Compagnie des Îles d'Amérique a vendu l'île de la Martinique à des fanatiques religieux, des croisés ou quelque chose de ce genre. Je n'ai encore rien remarqué d'inhabituel, du moins en regardant la côte depuis le pont. Mais comme nous avons été absents un moment, beaucoup de choses ont pu changer en mon absence.";
			link.l1 = "Croisés ? Balivernes !";
			link.l1.go = "Startsailor_4";			
		break;
		
		case "Startsailor_4":
			dialog.text = "Que ce soit des balivernes ou non, les rumeurs vont bon train. Nous avons déjà assez de problèmes comme ça. Des cannibales dans la jungle, la fièvre tropicale, des pirates, des bandits dans les ruelles, sans parler des Espagnols et des Anglais...";
			link.l1 = "Oh, c'est reparti... Pour l'instant, le seul ennui que je vois, c'est la chaleur accablante et les moustiques... Très bien, je suis prêt. On y va ?";
			link.l1.go = "Startsailor_5";			
		break;
		
		case "Startsailor_5":
			dialog.text = "Monte sur le pont et embarque dans la chaloupe, Monsieur. Bienvenue aux Caraïbes !";
			link.l1 = " ";
			link.l1.go = "Startsailor_6";			
		break;
		
		case "Startsailor_1a":
			dialog.text = "Il n'y a pas d'autre temps ici, 'Votre Seigneurie'. S'il y a quelque chose, cela ne fait qu'empirer.";
			link.l1 = "Le temps est insupportable, tout comme ma compagnie ces derniers mois. J'espère qu'il y a des gens décents dans l'Archipel.";
			link.l1.go = "Startsailor_2a";
			AddCharacterExpToSkill(pchar, "Leadership", 10);
		break;
		
		case "Startsailor_2a":
			dialog.text = "Eh bien, je pense que nous serons tous ravis de vous voir enfin partir, monsieur. Le bateau vous attend. Ne sautez pas hors de votre culotte de joie. Et n'oubliez pas vos affaires - le navire continue son voyage, et vous pourriez bien les oublier si vous ne le faites pas.";
			link.l1 = "Comme si je les laisserais pour ton plaisir. Pesos, épée - on dirait que je n'ai pas été volé.";
			link.l1.go = "Startsailor_3a";			
		break;
		
		case "Startsailor_3a":
			dialog.text = "Nous sommes des gens honnêtes, bien sûr, mais tu penses juste - garde toujours un œil sur tes affaires, sinon quelqu'un pourrait bien te vider les poches. Comme en vieille Europe. Ou n'importe où, en fait. Mais cet endroit n'est pas comme chez nous. Des fanatiques ont établi une base ici. On dit qu'ils ont secrètement acheté toute l'île. Alors, reste vigilant et ne te fais pas remarquer.";
			link.l1 = "Quelle sottise !";
			link.l1.go = "Startsailor_4a";			
		break;
		
		case "Startsailor_4a":
			dialog.text = "C'est la rumeur. Sois reconnaissant que je me sois donné la peine de partager et de me soucier de ton séjour ici. Sinon, cette délicate rose gasconne pourrait se faner sous notre soleil brûlant. Sornettes ou pas, garde l'esprit clair - nous avons déjà assez de problèmes sans les fanatiques. Des bandits dans les ruelles et la jungle, des pirates en mer, et des cannibales à la peau rouge...";
			link.l1 = "Allons, allons ! Je m'en sortirai. Il fait peut-être un peu chaud pour moi maintenant, mais je suis endurci par le soleil chez moi, contrairement, disons, à ces Normands. Et si quelque chose peut être résolu avec une épée, vous pouvez compter sur moi. Mais les moustiques - ça, c'est un vrai supplice ! Eh bien, toutes mes affaires sont en ordre. Le bateau est prêt, dis-tu ?";
			link.l1.go = "Startsailor_5a";			
		break;
		
		case "Startsailor_5a":
			dialog.text = "Attendant avec impatience. Espérons que vous pourrez vous débrouiller vous-même, monsieur ? Tenez bon, et avec un peu de chance, vous ne vous perdrez pas à partir de là. Oh, et bienvenue dans l'Archipel, héhé.";
			link.l1 = "Oui, merci. Le seul réconfort est que je ne serai pas ici longtemps.";
			link.l1.go = "Startsailor_6";			
		break;
		
		case "Startsailor_6":
			DialogExit();
			AddDialogExitQuestFunction("SharlieTutorial_StartGameInMartinique");
		break;
		// <-- матрос на корабле, прибытие в Сен-Пьер
		
		// горожанин знает Мишеля
		case "Benuatalker":
			DelLandQuestMark(npchar);
			link.l1 = "Excusez-moi, "+GetAddress_FormToNPC(NPChar)+", pourriez-vous me dire où je peux trouver Michel de Monpe? Il doit être quelque part dans votre ville.";
            link.l1.go = "Benuatalker_1";
		break;
		
		case "Benuatalker_1":
			dialog.text = "Hmm... Je vois que tu es arrivé ici récemment, puisque tu poses de telles questions sans crainte... Je te conseille d'arrêter cela, sinon tu auras des ennuis. Et à propos de ta question... Parle à l'Abbé. Tu le trouveras à l'église.";
			link.l1 = "Merci !";
            link.l1.go = "exit";
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			AddDialogExitQuest("Sharlie_SetBenua");
			QuestPointerToLoc("FortFrance_town", "reload", "reload7_back");
		break;
		
		// --> арест в резиденции
		case "Sharlie_arest":
			dialog.text = "Halte! Rendez vos armes immédiatement, Monsieur, et suivez-nous!";
			link.l1 = "Quel diable est-ce?";
			link.l1.go = "Sharlie_arest_1";
			if (CheckCharacterItem(PChar, "knife_03")) pchar.Sharlie.KnifeMonpe = true;
		break;
		
		case "Sharlie_arest_1":
			DialogExit();
			chrDisableReloadToLocation = false;
			DoFunctionReloadToLocation("FortFrance_prison", "goto", "goto9", "Puancie_InJail");
			WaitDate("", 0, 0, 2, 0, 10); //крутим время
			RecalculateJumpTable();
			RemoveAllCharacterItems(PChar, true);
			sld = characterFromId("Puancie");
			sld.dialog.currentnode = "Puancie_Jail"; 
			LAi_SetActorTypeNoGroup(sld);
			ChangeCharacterAddressGroup(sld, "FortFrance_prison", "goto", "goto13");
		break;
		// арест в резиденции
		
		// --> офицер базы
		case "Maltie_officer":
			ref location = &Locations[FindLocation(pchar.location)];
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "begin")
			{
				dialog.text = "Heureux de vous voir, Monsieur de Maure. Quelle est l'occasion ?";
				link.l1 = TimeGreeting()+", officier. Je voudrais parler à mon frère, Michel de Monper. Officieusement, bien sûr. J'essaie de me renseigner sur son service ici dans les Caraïbes.";
				link.l1.go = "spanish";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "think")
			{
				dialog.text = "Comment s'est passé l'interrogatoire ? As-tu trouvé quelque chose d'intéressant ?";
				link.l1 = "Oh oui. Tellement que je vais emmener cet Espagnol avec moi sur mon navire. Il est un témoin important et doit être livré à Saint-Christophe pour un interrogatoire supplémentaire.";
				link.l1.go = "spanish_10";
				break;
			}
			if (!CheckAttribute(location, "first_meeting"))
			{
				dialog.text = "Quelle est votre affaire ici, Monsieur ?";
				link.l1 = "Je suis venu voir mon frère, Michel de Monpe.";
				link.l1.go = "Maltie_officer_1";
				location.first_meeting = true;
			}
			else
			{
				dialog.text = "Monsieur, je dois vous rappeler doucement que vous êtes dans un cantonnement militaire. Comportez-vous en conséquence.";
				link.l1 = "Oui, monsieur. Bien sûr.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Maltie_officer";
			}
			
			if (SandBoxMode)
			{
				dialog.text = "Monsieur, je dois vous rappeler doucement que vous êtes à l'intérieur d'un cantonnement militaire. Comportez-vous en conséquence.";
				link.l1 = "Oui, monsieur. Bien sûr.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Maltie_officer";
			}
		break;
		
		case "Maltie_officer_1":
			DelLandQuestMark(npchar);
			dialog.text = "Michel de Monpe est actuellement sous garde dans l'une de nos casemates, détenu sous l'ordre personnel du Chevalier Philippe de Poincy. Descendez au niveau inférieur. Vous y trouverez les casemates que nous utilisons pour le stockage et les cellules. Je pense que vous saurez vous y retrouver.";
			link.l1 = "Merci!";
			link.l1.go = "exit";
			NextDiag.TempNode = "Maltie_officer";
			QuestPointerToLoc("FortFrance_Dungeon", "quest", "quest1");
		break;
		// офицер базы
		
		// --> солдаты базы
		case "Maltie_soldier":
			dialog.text = "Bonjour, Monsieur. Puis-je vous aider en quoi que ce soit ?";
			link.l1 = "Merci, soldat, mais non, je vais très bien. Continuez.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Maltie_soldier";
		break;
		// --> солдаты базы
		
		// --> мальтиец-проводник
		case "Sharlie_maltie":
			dialog.text = "Merci d'avoir attendu, Monsieur. Alors vous cherchez Michel de Monper ? Vous êtes son frère ?";
			link.l1 = "Oui, c'est exact. Je suis son frère Charles. Je dois le voir tout de suite. Michel est-il en difficulté ?";
			link.l1.go = "Sharlie_maltie_1";			
		break;
		
		case "Sharlie_maltie_1":
			dialog.text = "Malheureusement, il l'est, Monsieur. Michel est enfermé dans l'une des casemates en bas. Le Chevalier de Poincy, le Gouverneur Général des colonies françaises du Nouveau Monde, a personnellement signé l'ordre de son arrestation. Nous avons tous été choqués. Votre frère est un exemple de vertu virile, de discipline et de courage, la fierté de notre Ordre ! Le pire, c'est que nous, ses amis, devons l'enfermer derrière les barreaux et le garder comme un vulgaire criminel ! Nous faisons tout notre possible pour qu'il soit à l'aise, mais... une prison reste une prison.";
			link.l1 = "De quoi est-il accusé? A-t-il commis un crime?";
			link.l1.go = "Sharlie_maltie_1_1";			
		break;
		
		case "Sharlie_maltie_1_1":
			dialog.text = "Le bureau du Gouverneur Général a accusé Michel de détournement! Quelle absurdité! Nous sommes tous convaincus ici que c'est politiquement motivé. Je vais te dire quelque chose en confidence. Michel a participé à certaines actions secrètes au nom de l'Ordre. Peut-être a-t-il découvert plus qu'il n'aurait dû. Ou pire, a-t-il contrarié des hommes puissants. Mais voler de l'argent? Personne n'y croit. C'est un prétexte, pas une vraie raison, un prétexte lâche et ignoble! Mais assez de paroles. Ton frère a hâte de te voir, je suis sûr qu'il te dira tout lui-même.";
			link.l1 = "Bien. Où se trouve votre prison?";
			link.l1.go = "Sharlie_maltie_1_2";
		break;
		
		case "Sharlie_maltie_1_2":
			dialog.text = "Dans notre armurerie souterraine, ici même dans la ville. Suivez-moi. Je vous montrerai le chemin.";
			link.l1 = "...";
			link.l1.go = "Sharlie_maltie_2";
		break;
		
		case "Sharlie_maltie_2":
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "FortFrance_town", "officers", "reload7_1", "Maltie_GoTown", -1);
		break;
		
		case "Sharlie_maltie_3":
			DelLandQuestMark(npchar);
			AddLandQuestMark(characterFromId("Maltie_officer"), "questmarkmain");
			dialog.text = "Nous y voilà. Voici notre base d'opérations - le Chapitre des Caraïbes de l'Ordre des Hospitaliers Militaires de Saint-Jean de Jérusalem, de Rhodes et de Malte. Les casemates sont en dessous de nous. Descendez le couloir en passant par la salle à manger et la chapelle. Les escaliers là-bas vous mèneront au niveau inférieur. Cherchez un couloir bordé de cellules. Vous trouverez votre frère dans l'une près du fond.\nAllez, Charles, et que Dieu soit avec vous. Aidez Michel, s'il vous plaît ! Il est innocent, tout le monde ici est prêt à le jurer.";
			link.l1 = "Tout le but de ma venue dans ce trou à rats est de voir mon frère. J'espère pouvoir le sortir de ce pétrin au moins.";
			link.l1.go = "Sharlie_maltie_4";
		break;
		
		case "Sharlie_maltie_4":
			DialogExit();
			chrDisableReloadToLocation = false;//открыть локацию
			npchar.lifeday = 0;
			LAi_ActorGoToLocator(npchar, "goto", "goto1", "none", -1);
		break;
		
		//belamour cle -->
		case "Sharlie_maltieA":
			dialog.text = "Alors tu cherchais Michel de Monpe? Et tu es son frère?";
			link.l1 = "Oui, c'est exact. Je suis son frère Charles. Je dois le voir immédiatement. Il a eu des ennuis, n'est-ce pas ?";
			link.l1.go = "Sharlie_maltie_1a";			
		break;
		
		case "Sharlie_maltie_1a":
			dialog.text = "Malheureusement, il l'est, Monsieur. Michel est arrêté et enfermé dans notre prison. Le chevalier de Poincy, le gouverneur général des colonies françaises, a lui-même donné et signé les ordres. Nous avons tous été choqués.\nVotre frère est un exemple de virilité, de fermeté et de courage, une fierté de notre Ordre ! Le pire, c'est que nous, ses amis, devons fermer sa cellule et le garder comme un criminel ! Nous faisons tout pour alléger son sort, mais... une prison reste une prison.";
			link.l1 = "Alors, de quoi l'accuse-t-on ? A-t-il commis un crime ?";
			link.l1.go = "Sharlie_maltie_1_1a";			
		break;
		
		case "Sharlie_maltie_1_1a":
			dialog.text = "Balivernes! De pures balivernes! Ils ont accusé Michel de détournement de fonds et de vol de l'argent de l'État. Ridicule! Nous sommes tous convaincus que ce n'est qu'un jeu politique. Michel avait participé à des opérations secrètes de l'Ordre, peut-être en a-t-il appris plus qu'il n'aurait dû.\nOu autre chose. Mais voler de l'argent! Personne n'y croit. Ce n'est qu'un prétexte, pas une raison, un prétexte aussi grossier et stupide! Mais assez de mots. Ton frère a hâte de te voir, je suis sûr qu'il te dira tout lui-même.";
			link.l1 = "Bien. Où se trouve la prison ?";
			link.l1.go = "Sharlie_maltie_1_2a";
		break;
		
		case "Sharlie_maltie_1_2a":
			dialog.text = "C'est situé dans notre base souterraine, ici en ville. Suivez-moi. Je vous montrerai le chemin.";
			link.l1 = "... ";
			link.l1.go = "Sharlie_maltie_2a";
		break;
		
		case "Sharlie_maltie_2a":
			DialogExit();
			//LAi_ActorGoToLocation(npchar, "reload", "reloadPr1", "FortFrance_Dungeon", "reload", "reload1", "", -1);
			Pchar.quest.Sharlie_Maltie.win_condition.l1 = "location";
			Pchar.quest.Sharlie_Maltie.win_condition.l1.location = "FortFrance_town";
			Pchar.quest.Sharlie_Maltie.win_condition = "Maltie_GoBasement";
			QuestPointerDelLoc("FortFrance_prison", "reload", "reload1");
		break;
		//<-- cle
		// мальтиец-проводник
		
		// --> найм матросов
		case "Sharlie_sailor":
			DelLandQuestMark(npchar);
			dialog.text = "Et puis il s’est penché par-dessus bord et en a sorti tant que la mer des Caraïbes en est devenue verte ! Ha-ha-ha !";
			link.l1 = "Alonso ?";
			link.l1.go = "Sharlie_sailor_1";
		break;
		
		case "Sharlie_sailor_1":
			dialog.text = "Oh ! Charles, j’étais justement en train de raconter nos aventures aux gars !";
			link.l1 = "J’ai remarqué. Écoute, Alonso. Je suis devenu capitaine.";
			link.l1.go = "Sharlie_sailor_2";
		break;
		
		case "Sharlie_sailor_2":
			dialog.text = "Déjà ? Je pensais qu’il vous faudrait au moins un mois, ha ha !";
			link.l1 = "Je suis tout à fait sérieux !";
			link.l1.go = "Sharlie_sailor_3";
		break;
		
		case "Sharlie_sailor_3":
			dialog.text = "Si cela ne tenait qu’à moi, je vous suivrais tout de suite. Mais j’ai quarante hommes de l’Ulysse avec moi. Ils m’ont confié leur avenir ; je dois être sûr que vous ne les décevrez pas\n"+
			"Quel genre de navire avez-vous ?";
			link.l1 = "Un navire comme un autre, "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(RealShips[sti(pchar.ship.type)].basetype), "Name")))+". C’est si important ?";
			link.l1.go = "Sharlie_sailor_4";
		break;
		
		case "Sharlie_sailor_4":
			dialog.text = "Vous savez, après l’Ulysse, on préfère éviter les barques ou tartanes. On a déjà vu votre navire, et les gars l’approuvent\n"+
			"Maintenant, parlons argent. Nous demandons 4 800 pesos d’avance. Ensuite, comme d’habitude, on partage. Rien d’exagéré, rassurez-vous. Vous pouvez gérer ?";
			if (sti(Pchar.money) >= 4800)
			{
				link.l1 = "Marché conclu ! Voici votre argent.";
				link.l1.go = "Sharlie_sailor_5";
			}
			link.l2 = "Malheureusement, je n'ai pas autant d'argent sur moi en ce moment.";
			link.l2.go = "Sharlie_sailor_nomoney";
		break;
		
		case "Sharlie_sailor_5":
			if (GetSquadronGoods(pchar, GOOD_FOOD) < 20 || GetSquadronGoods(pchar, GOOD_MEDICAMENT) < 30)
			{
				dialog.text = "As-tu des vivres dans la cale, capitaine ? Et des médicaments ? Non ? Eh bien, ce n'est pas bon. Sors et procure-toi le minimum pour notre voyage, puis reviens et nous parlerons. Va à la boutique et prends ce dont tu as besoin.";
				link.l1 = "Hm. Tu as raison. D'accord, je vais le faire.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Sharlie_sailor_again";
			}
			else
			{
				AddMoneyToCharacter(pchar, -4800);
				dialog.text = "Bah ! Félicitations… capitaine ! Je rassemble les gars et nous allons tout de suite à votre navire.";
				link.l1 = "Heureux de poursuivre notre aventure, Alonso. Préparez le navire à prendre la mer !";
				link.l1.go = "Sharlie_sailor_6";
			}
		break;
		
		case "Sharlie_sailor_6":
			DialogExit();
			LAi_SetStayType(npchar);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(npchar, "Fortfrance_tavern", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "", "", "", "", 5);
			npchar.lifeday = 0;
			SetCrewQuantityOverMax(PChar, 40);
			pchar.Ship.Crew.Morale = 50;
			pchar.Ship.Crew.Exp.Sailors = 50;
			pchar.Ship.Crew.Exp.Cannoners = 50;
			pchar.Ship.Crew.Exp.Soldiers = 50;
			AddQuestRecord("Sharlie", "7");
			pchar.questTemp.Sharlie = "skiper";
			DeleteAttribute(pchar, "GenQuest.CannotWait");//снимаем запрет, если не был снят раньше
			AddLandQuestMark(characterFromId("FortFrance_tavernkeeper"), "questmarkmain");
		break;
		
		case "Sharlie_sailor_nomoney":
			dialog.text = "Eh bien, dès que tu trouveras assez d'argent, reviens. Tu nous trouveras ici à la taverne. De toute façon, il n'y a pas d'autres navires dans le coin. On continuera juste à boire et à dilapider notre argent en putains, harhar !";
			link.l1 = "Je vais essayer de revenir le plus tôt possible.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Sharlie_sailor_again";
		break;
		
		case "Sharlie_sailor_again":
			dialog.text = "Tu es de retour, cap'taine ? Prêt à m'embaucher, moi et mes compagnons de cambuse ? Nos bourses commencent à s'alléger, il nous faut sentir à nouveau la brise marine sur nos visages !";
			if (sti(Pchar.money) < 4800)
			{
				link.l1 = "Pas encore, je prépare encore tout.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Sharlie_sailor_again";
			}
			else
			{
				link.l1 = "Oui. Prenez votre avance. Maintenant vous êtes à mon service.";
				link.l1.go = "Sharlie_sailor_5";
			}
		break;
		// найм матросов
		
		// наводчик на штурмана
		case "skipertalker":
			DelLandQuestMark(npchar);
			dialog.text = LinkRandPhrase("Ahoy capitaine ! Que désirez-vous ?","Bonjour Monsieur. Que puis-je faire pour vous ?","Bonne journée. Que voulez-vous ?");
			link.l1 = RandPhraseSimple("J'ai une question pour toi.","J'ai besoin d'informations sur cette colonie.");
			link.l1.go = "skipertalker_1";
			link.l2 = "Je dis juste bonjour. Au revoir !";
			link.l2.go = "exit";
			NextDiag.TempNode = "skipertalker";
		break;
		
		case "skipertalker_1":
			dialog.text = RandPhraseSimple("Qu'est-ce que c'est ?","Que désirez-vous ?");
			link.l1 = "Écoute, "+GetAddress_FormToNPC(NPChar)+", voilà le truc... Je cherche un navigateur. Peut-être connaissez-vous quelqu'un ici en ville qui conviendrait pour le poste?";
			link.l1.go = "skipertalker_2";
		break;
		
		case "skipertalker_2":
			dialog.text = "Un navigateur ? Hm. Eh bien, j'en connais un... Il y a juste un problème - il est en prison, prison pour dettes. Le pauvre bougre est enfermé dans les casemates depuis près d'un mois maintenant jusqu'à ce qu'il ou quelqu'un d'autre paie ce qu'il doit.";
			link.l1 = "Un débiteur ? Hm... Comment s'appelle-t-il ?";
			link.l1.go = "skipertalker_3";
		break;
		
		case "skipertalker_3":
			dialog.text = "Il s'appelle Folke Deluc. Demande au commandant de la prison si tu veux le voir. Mais je ne pense pas qu'ils le laisseront sortir de là à moins que tu ne paies sa dette, parce que lui, c'est sûr qu'il ne le fera pas, hahaha !";
			link.l1 = "Peut-être bien que oui. Merci pour l'information, ami.";
			link.l1.go = "exit";
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			pchar.questTemp.Sharlie = "jailskiper";
			AddQuestRecord("Sharlie", "8");
			LocatorReloadEnterDisable("Fortfrance_town", "reload_jail", false);
			SetFunctionLocationCondition("FortfranceJailOff_AddQuestMark", "fortfrance_prison", false);
		break;
		
		// --> штурман
		case "Folke":
			dialog.text = "À quoi dois-je un tel honneur, Monsieur ?";
			link.l1 = "Bonjour, Folke. C'est simple, j'ai un navire, mais pas de navigateur. Et j'en ai besoin d'un. Alors j'ai racheté ta dette...";
			link.l1.go = "Folke_1";
		break;
		
		case "Folke_1":
			dialog.text = "Tu veux dire que tu m'as sorti d'ici pour m'enrôler dans ton équipage ?";
			link.l1 = "Exactement. Je pense que tu récupéreras rapidement l'argent que j'ai dépensé pour toi. Eh bien... nous verrons comment cela se passe.";
			link.l1.go = "Folke_2";
		break;
		
		case "Folke_2":
			dialog.text = "Ma gratitude, Monsieur. J'ai attrapé la peste de cette cellule pourrie et humide. Ce serait un grand plaisir de remonter à bord une fois de plus. Ah, la mer...";
			link.l1 = "Je suis heureux que nous soyons parvenus à un accord, Folke. Encore une chose, as-tu d'autres compétences à part diriger un navire ?";
			link.l1.go = "Folke_3";
		break;
		
		case "Folke_3":
			dialog.text = "Un peu de tout, capitaine. J'ai servi à bord d'un corsaire pour la Compagnie néerlandaise des Indes occidentales. J'y ai appris à manier les canons, donc je peux servir comme officier d'artillerie si vous avez besoin de moi. Le commerce et l'abordage sont mes points faibles.";
			link.l1 = "Merci pour le partage, maintenant suivez-moi jusqu'au navire. Je veux que vous observiez l'équipage de votre œil expérimenté pendant qu'ils préparent tout pour le départ. Ensuite, je veux me rendre à la Guadeloupe dès que possible.";
			link.l1.go = "Folke_4";
		break;
		
		case "Folke_4":
			dialog.text = "Oui, capitaine ! Je vous attendrai dans votre cabine. *Utilisez le menu d'action en mer pour accéder à la cabine et aux autres zones du navire*";
			link.l1 = "Merci, Folke. À bord.";
			link.l1.go = "Folke_5";
			Log_Info("You have received amulet 'Merchant's Rosary'");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "obereg_8");
			if(CheckAttribute(pchar,"systeminfo.tutorial.Amulet"))
			{
				DoQuestFunctionDelay("Tutorial_Amulet", 0.1);
			}
		break;
		
		case "Folke_5":
			DialogExit();
			EndQuestMovie();
			chrDisableReloadToLocation = false;//открыть локацию
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			AddQuestRecord("Sharlie", "10");
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			pchar.quest.Sharlie_skiper.win_condition.l1 = "location";
			pchar.quest.Sharlie_skiper.win_condition.l1.location = "My_Cabin_Small";
			pchar.quest.Sharlie_skiper.function = "Sharlie_SkiperTalk";
			//прерывание на засаду пиратов - принудительный квест
			pchar.quest.Sharlie_seabattle.win_condition.l1 = "location";
			pchar.quest.Sharlie_seabattle.win_condition.l1.location = "Fortfrance_town";
			pchar.quest.Sharlie_seabattle.function = "SharlieSeabattle_agent";
			
			pchar.quest.NewGameTip2.win_condition.l1 = "location";
			pchar.quest.NewGameTip2.win_condition.l1.location = "Martinique";
			pchar.quest.NewGameTip2.function = "ShowNewGameTip";
			pchar.quest.NewGameTip2.text = "Your first officer is waiting for you. Use the action menu (ENTER) to go to the cabin.";
		break;
		
		case "Folke_6":
			pchar.GenQuest.StoreGoods.StoreIdx = Fortfrance_STORE;
			pchar.GenQuest.StoreGoods.Starting = true; // заполняем магазин 250912
			dialog.text = "Un joli lougre, capitaine ! Un bon petit navire avec un gréement fin et des bois solides. Avec un navire comme celui-ci, non seulement nous atteindrons la Guadeloupe en toute sécurité, mais nous pourrons même croiser dans tout les Caraïbes si nous le souhaitons.";
			link.l1 = "Excellent. Au moins, je n'ai pas gaspillé mon argent sur une épave qui fuit... As-tu des conseils avant que nous levions l'ancre, Folke?";
			link.l1.go = "Folke_8";
		break;
		
		case "Folke_7":
			dialog.text = "Bon sang, ce sloop fuit comme une passoire, capitaine. Ce sera une affaire serrée pour nous de traverser jusqu'à la Guadeloupe. Si vous voulez arriver à Basse-Terre en un seul morceau, il faudra la faire réparer au chantier naval immédiatement.";
			link.l1 = "Je n'avais pas le choix, c'était le seul navire à vendre ! Et ils m'ont fait payer une jolie somme pour elle. Comme tu le sais, nous n'avons pas le temps de la réparer pour le moment... As-tu des conseils avant que nous prenions la mer ?";
			link.l1.go = "Folke_8";
		break;
		
		bOk = (GetSquadronGoods(pchar, GOOD_BALLS) >= 80) && (GetSquadronGoods(pchar, GOOD_GRAPES) >= 80) && (GetSquadronGoods(pchar, GOOD_KNIPPELS) >= 80) && (GetSquadronGoods(pchar, GOOD_BOMBS) >= 80) && (GetSquadronGoods(pchar, GOOD_POWDER) >= 180);
		case "Folke_8":
			if (bOk)
			{
				dialog.text = "Nous sommes bien approvisionnés en poudre et boulets, capitaine. Cela suffira pour l’instant ; pensez juste à refaire le plein à temps.";
				link.l1 = "Eh bien, cela va sans dire. D'autres commentaires?";
				link.l1.go = "Folke_10";
				if (CheckCharacterItem(PChar, "BoxOfBalls"))
				{
					link.l2 = "Ah ! Merci de me le rappeler. J’ai justement une caisse entière de boulets avec moi !";
					link.l2.go = "Folke_8_1";
				}
			}
			else
			{
				dialog.text = "Nous n'avons pas assez de munitions dans la soute, capitaine. Nous devons avoir au moins cent boulets de canon, boulets ramés et bombes, ainsi que cent sacs de mitraille et deux cents barils de poudre à canon. Achetez le matériel nécessaire, capitaine. Cela ne coûtera pas cher, mais cela nous sauvera la vie si nous sommes attaqués par des pirates ou les Espagnols.";
				link.l1 = "Un investissement digne. Je file chez le marchand.";
				link.l1.go = "Folke_9";
			}
		break;
		
		case "Folke_8_1":
			dialog.text = "...Et depuis combien de temps vous la trimballez ?";
			link.l1 = "Près de deux semaines.";
			link.l1.go = "Folke_8_2";
			TakeItemFromCharacter(pchar, "BoxOfBalls");
			//AddCharacterGoodsSimple(sld, GOOD_BALLS, 10);
		break;
		
		case "Folke_8_2":
			dialog.text = "Mais pourquoi, capitaine ?!";
			link.l1 = "J’aime ramasser tout et n’importe quoi. On ne sait jamais ce qui peut servir.";
			link.l1.go = "Folke_8_3";
		break;
		
		case "Folke_8_3":
			dialog.text = "Tant pis pour vous. Ces boulets ne rentreront jamais dans nos petits canons. Je n’en ai jamais vu d’aussi gros. Un seul enverrait l’Adeline par le fond.";
			link.l1 = "...";
			link.l1.go = "Folke_10";
		break;
		
		case "Folke_9":
			DialogExit();
			NextDiag.CurrentNode = "Folke_goods_1";
			LAi_SetStayType(npchar);
			AddQuestRecord("Sharlie", "12");
		break;
		
		case "Folke_goods_1":
			dialog.text = "As-tu fini d'acheter des munitions, capitaine?";
			if (bOk)
			{
				link.l1 = "Oui, j'en ai. D'autres commentaires?";
				link.l1.go = "Folke_10";
			}
			else
			{
				link.l1 = "Pas maintenant, j'y travaille encore.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Folke_goods_1";
			}
		break;
		
		bOk = (GetSquadronGoods(pchar, GOOD_WEAPON) >= 50);
		case "Folke_10":
			if (bOk)
			{
				dialog.text = "Bien joué, tu as acheté assez d'armes pour ton équipage. Si nous n'avons pas assez d'armes, nous perdrons bien plus d'hommes lors des abordages. Que Dieu nous protège de cela. N'oublie pas de vérifier fréquemment la quantité dans la cale\nC'est prudent de garder quelques armes de plus que nécessaire. Les maudits rats aiment ronger les manches et crosses en bois.";
				link.l1 = "Compris. Je vois que tu veux encore ajouter quelque chose ?";
				link.l1.go = "Folke_11";
			}
			else
			{
				dialog.text = "Nous n'avons pas assez d'armes à bord pour l'équipage. Si nous n'avons pas assez d'armes, nous perdrons bien plus d'hommes lors des abordages. Que Dieu nous en préserve. D'après ce que je comprends, vous avez quarante hommes dans l'équipage\nAchetez assez d'armes pour chacun, ou même achetez-en quelques-unes de plus, cinquante jeux devraient suffire. Il est judicieux de garder quelques armes de plus que nécessaire. Ces maudits rats aiment ronger les manches et crosses en bois.";
				link.l1 = "C'est ce que je vais faire. Je serai bientôt de retour.";
				link.l1.go = "Folke_10_1";
			}
		break;
		
		case "Folke_10_1":
			DialogExit();
			NextDiag.CurrentNode = "Folke_goods_2";
			LAi_SetStayType(npchar);
			AddQuestRecord("Sharlie", "13");
		break;
		
		case "Folke_goods_2":
			dialog.text = "As-tu fini d'acheter les armes, capitaine ?";
			if (bOk)
			{
				link.l1 = "Les armes sont dans la cale. Je vois qu'il y a encore quelque chose que tu veux ajouter ?";
				link.l1.go = "Folke_11";
			}
			else
			{
				link.l1 = "Pas maintenant, j'y travaille encore.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Folke_goods_2";
			}
		break;
		
		bOk = (GetSquadronGoods(pchar, GOOD_FOOD) >= 100) && (GetSquadronGoods(pchar, GOOD_RUM) >= 10);
		case "Folke_11":
			if (bOk)
			{
				dialog.text = "Non, je pense que c'est tout. Nous avons assez de nourriture, tu t'es aussi occupé de rhum pour l'équipage. C'est sage, car il n'y a pas de meilleur remède pour tous les maux qu'un bon petit verre de rhum bien frais après ton quart. Les marins aiment et respectent les capitaines qui leur donnent leur ration quotidienne de rhum. Tu ne veux jamais entendre tes hommes demander : 'Pourquoi le rhum est-il parti ?'";
				link.l1 = "Peut-on mettre les voiles maintenant ?";
				link.l1.go = "Folke_12";
			}
			else
			{
				dialog.text = "Oui. Nourriture et rhum. C'est désastreux si vous n'avez pas assez de vivres à bord. Ayez toujours plus de provisions que vous ne pensez en avoir besoin. Vous ne savez jamais combien de temps un voyage durera - un calme plat ou un vent fort peut ruiner n'importe quel plan. Les hommes se mutineront ou mourront de faim lorsque les provisions seront épuisées\nL'approvisionnement en rhum n'est pas aussi crucial, mais je recommande fortement d'en garder toujours à bord, il n'y a pas de meilleur remède pour tous les maux qu'un bon verre de rhum frais après votre quart. Les marins aiment et respectent les capitaines qui leur donnent leur ration quotidienne de rhum\nAlors allez acheter les provisions dont nous avons besoin - au moins cent caisses de nourriture et dix barils de rhum. Vous ne voulez jamais entendre vos hommes demander : 'Pourquoi le rhum est-il parti ?'";
				link.l1 = "Je suppose que tu as raison. Je vais retourner voir le marchand.";
				link.l1.go = "Folke_11_1";
			}
		break;
		
		case "Folke_11_1":
			DialogExit();
			NextDiag.CurrentNode = "Folke_goods_3";
			LAi_SetStayType(npchar);
			AddQuestRecord("Sharlie", "14");
		break;
		
		case "Folke_goods_3":
			dialog.text = "Avez-vous fini d'acheter notre nourriture et notre rhum, capitaine ?";
			if (bOk)
			{
				link.l1 = "Oui. Pouvons-nous appareiller maintenant?";
				link.l1.go = "Folke_12";
			}
			else
			{
				link.l1 = "Non, j'y travaille encore.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Folke_goods_3";
			}
		break;
		
		case "Folke_12":
			dialog.text = "Oui, cap'taine. Nous pouvons lever l'ancre et mettre le cap au nord vers la Guadeloupe, comme vous le vouliez.";
			// belamour legendary edition -->
			link.l1 = "Bon travail, Folke. Je n'aurais pas réussi sans toi.";
			link.l1.go = "Folke_13";
			link.l2 = "D'accord, mettons-nous au travail, voyons si tu vaux l'argent.";
			link.l2.go = "Folke_13a";
		break;
		
		case "Folke_13a":
			Npchar.loyality = makeint(Npchar.loyality) - 5;
			ChangeCharacterComplexReputation(pchar,"authority", 5);
			dialog.text = "Alors nommez-moi navigateur et j'irai à ma place sur le pont.";
			link.l1 = "... ";
			link.l1.go = "Folke_14";
		break;
		
		case "Folke_13":
			Npchar.loyality = makeint(Npchar.loyality) + 5;
			AddCharacterExpToSkill(pchar, "Leadership", 150);
			// <-- legendary edition
			dialog.text = "Alors, nommez-moi navigateur et j'irai prendre ma place sur le pont.";
			link.l1 = "... ";
			link.l1.go = "Folke_14";
		break;
		
		case "Folke_14":
			DialogExit();
			LAi_SetStayType(npchar);
			LAi_SetImmortal(npchar, false);
			AddQuestRecord("Sharlie", "15");
			pchar.questTemp.Sharlie = "seabattle";//в Ле Франсуа
			DeleteAttribute(pchar, "NoNavyPenalty"); // штрафуем за нехватку навигации
			
			npchar.quest.OfficerPrice = 20;
			npchar.loyality = 30;
			
			// --> копипаста LandEnc_OfficerHired
			AddPassenger(pchar, npchar, false);
			npchar.Payment = true;
			npchar.DontClearDead = true;
			SaveCurrentNpcQuestDateParam(npchar, "HiredDate");
			// <--
			
			pchar.questTemp.HelenDrinking.TakeFolke = true;
			
			DoQuestFunctionDelay("Tutorial_Navigator2", 1.0);
			//DoQuestFunctionDelay("Ngt_FolkeEng", 3.0);
			//NewGameTip("Welcome aboard your new officer! Press F4 to assign him as your Navigator.");
			pchar.questTemp.Sharlie.FolkeWait = true;
			LocatorReloadEnterDisable("My_Cabin_Small", "reload1", true);
			NextDiag.CurrentNode = "Folke_wait";
		break;
		
		case "Folke_wait":
			dialog.text = "Prêt à lever l'ancre, capitaine !";
			link.l1 = "... ";
			
			if (!CheckAttribute(npchar, "navigator")) {
				dialog.text = "Capitaine, faites de moi votre navigateur, sinon nous allons nous échouer en un rien de temps.";
				link.l1 = "Compris, je vais le faire maintenant.";
			}
			
			link.l1.go = "exit";
			NextDiag.TempNode = "Folke_wait";
		break;
	
		// штурман

	// --> пират-обманщик
		case "Seabattle_pirate":
			dialog.text = "Je vous prie de m'excuser. "+GetFullName(pchar)+"?";
			link.l1 = "Correct. Que dois-je pour cette occasion, monsieur ?";
			link.l1.go = "Seabattle_pirate_1";
		break;
		
		case "Seabattle_pirate_1":
			dialog.text = "Permettez-moi de me présenter - "+GetFullName(npchar)+"J'ai été envoyé ici par Cesar Craig. Vous devez le connaître. C'est le propriétaire de la taverne à Le François. Autant qu'il le sache, vous êtes sur le point de partir pour la Guadeloupe. Il aimerait vous offrir de l'argent facile.";
			link.l1 = "Hm... Intéressant ! Et comment Cesar Craig est-il devenu si bien informé ?";
			link.l1.go = "Seabattle_pirate_2";
		break;
		
		case "Seabattle_pirate_2":
			dialog.text = "C'est simple, capitaine. Votre navire est le seul à St. Pierre en ce moment, n'importe qui avec deux oreilles et un oeil sait tout sur qui vous êtes et où vous allez. Ici, dans les colonies, les rumeurs volent plus vite que les mouettes. Alors, êtes-vous intéressé par notre offre ?";
			link.l1 = "Bien sûr. Je ne suis jamais opposé à gagner un peu d'argent.";
			link.l1.go = "Seabattle_pirate_3";
		break;
		
		case "Seabattle_pirate_3":
			dialog.text = "Maintenant on parle, matelot ! Je vois que tu as le nez fin pour les affaires. Voici le marché. Cesar a un besoin urgent de livrer un lot de vin à la Guadeloupe. Deux cents barils, la cale de ton navire peut facilement les contenir. La paye est de dix mille pesos pour un travail facile - Cesar est pressé, et ton navire est le seul dans le port en ce moment. Tu dois convenir que des propositions aussi lucratives sont rares.";
			link.l1 = "Merde, dix mille pesos ? Eh bien, marché conclu !";
			link.l1.go = "Seabattle_pirate_4";
		break;
		
		case "Seabattle_pirate_4":
			dialog.text = "Rends-toi à Le Francois et parle à Cesar. Il s'occupera de tout. Tout ce que tu auras à faire, c'est d'ancrer dans la baie juste à l'extérieur de Le Francois. Ne me laisse pas tomber, camarade, Cesar m'a promis mille pesos si je te convainquais...";
			link.l1 = "Ne t'inquiète pas, considère-moi comme convaincu. Dès que je serai prêt à partir, je mettrai le cap directement sur Le François.";
			link.l1.go = "Seabattle_pirate_5";
		break;
		
		case "Seabattle_pirate_5":
			dialog.text = "Hourra ! Je pars chercher mes mille. Merci, camarade !";
			link.l1 = "De rien...";
			link.l1.go = "Seabattle_pirate_6";
		break;
		
		case "Seabattle_pirate_6":
			DialogExit();
			AddLandQuestMark(characterFromId("LeFransua_tavernkeeper"), "questmarkmain");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "gate_back", "", "", "", "", -1);
			AddQuestRecord("Sharlie", "11");
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			chrDisableReloadToLocation = false;//открыть локацию
			npchar.location = "None";
		break;
	// пират-обманщик

	// офицер Гриффондора
		case "griffondor_officer":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "exit";
		break;

	// командир абордажной роты по защите Сен-Пьера
		case "rosetti":
			PlaySound("Voice\English\EvilPirates01.wav");
			dialog.text = "Capitaine, le groupe d'abordage est formé et prêt ! Nous attendons vos ordres !";
			link.l1 = "Bonjour, ami.";
			link.l1.go = "rosetti_1";
		break;
		
		case "rosetti_1":
			DialogExit();
			bDisableCharacterMenu = true;//лоченые интерфейсы
			ChangeShowIntarface();
			LAi_SetActorType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("DefendSP_soldier_0"));
			PChar = GetMainCharacter();			
			LAi_SetPlayerType(PChar);
			sld = characterFromId("Blaze");
			sld.dialog.filename = "MainHero_dialog.c";
			sld.dialog.currentnode = "SP_defend";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "rosetti_2":
			PlaySound("interface\abordage_wining.wav");
			dialog.text = "Oui, oui, capitaine ! Préparez-vous, les gars, suivez le capitaine ! Hut, un-deux-trois !";
			link.l1 = "";
			link.l1.go = "rosetti_3";
		break;
		
		case "rosetti_3":
			DialogExit();
			PlaySound("interface\abordage_wining.wav");
			bDisableCharacterMenu = false;//лоченые интерфейсы
			ChangeShowIntarface();
			for (i=0; i<=12; i++)
			{
				sld = CharacterFromID("DefendSP_soldier_"+i);
				LAi_SetActorType(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			// прерывание на джунгли перед выходом из города
			pchar.quest.DefendSP_jungle1.win_condition.l1 = "location";
			pchar.quest.DefendSP_jungle1.win_condition.l1.location = "Martinique_jungle_01";
			pchar.quest.DefendSP_jungle1.function = "DefendSP_SpainPatrol";
		break;
		
		case "spain_patrol":
			dialog.text = "Merde, renforts français ! Formez les rangs ! Lorenzo, va au camp et sonne l'alarme ! Crèvez, salauds !";
			link.l1 = "...";
			link.l1.go = "spain_patrol_1";
		break;
		
		case "spain_patrol_1":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			for (i=1; i<=4; i++)
			{
				sld = CharacterFromID("DefendSP_spapatrol_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
				LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
				LAi_group_SetCheck("EnemyFight", "DefendSP_SpaPatrolDie");
				AddDialogExitQuest("MainHeroFightModeOn");
			}
			sld = CharacterFromID("DefendSP_spapatrol_5");
			LAi_ActorRunToLocation(sld, "reload", "reload2_back", "none", "", "", "DefendSP_GateAlarm", -1);
		break;

	// страж истины
		case "spanish":
			dialog.text = "Comprenez-vous que je ne suis pas autorisé à diffuser de telles informations ?";
			link.l1 = "Comprenez-vous que c'est uniquement grâce à mon intervention opportune que St. Pierre n'a pas été ravagée par les Espagnols ? Mon frère a disparu, abandonnant l'Ordre ! Il a dû faire cela pour une raison. Moi, en tant que représentant de Sir Philippe de Poincy, je suis autorisé à enquêter !";
			link.l1.go = "spanish_1";
		break;
		
		case "spanish_1":
			dialog.text = "D'accord, d'accord, Monsieur de Maure. Je vais répondre à vos questions. Calmez-vous d'abord. Maintenant, posez vos questions.";
			link.l1 = "Que s'est-il passé avant que Michel ne soit enfermé sous bonne garde?";
			link.l1.go = "spanish_2";
		break;
		
		case "spanish_2":
			dialog.text = "Michel de Monper négociait avec quelques barons pirates pour organiser un changement de régime à Tortuga.";
			link.l1 = "Je le sais déjà. Quoi d'autre ?";
			link.l1.go = "spanish_3";
		break;
		
		case "spanish_3":
			dialog.text = "Il préparait également une autre opération contre les Espagnols. Pour être précis - la capture d'un navire espagnol avec une cargaison précieuse à bord. Michel devait attirer la cible sous les canons de la légère frégate 'Gryffondor'. Nous n'avons pas vu ni entendu parler de lui pendant un certain temps alors qu'il planifiait cela.\nMais le plan a échoué. Le transport espagnol n'est pas arrivé et Michel lui-même a été retrouvé par des pêcheurs locaux échoué sur les rives de la baie de Le Marin, à moitié mort. Il semble que l'opération ait été un échec.\nLa guerre est la guerre, et les choses tournent mal. C'était un miracle que Michel ait survécu, mais le Chevalier de Poincy est entré dans une rage folle. Il a accusé Michel de détournement de fonds de l'Ordre et l'a fait emprisonner. Bien sûr, nous ne croyions pas un mot de ces accusations. Michel est un homme honnête, un vrai chevalier de l'Ordre. Seul Dieu sait ce qui a mis le Gouverneur Général en colère. Peut-être que le Chevalier de Poincy vous le dira lui-même ?";
			link.l1 = "Peut-être. C'est tout ce que tu sais ?";
			link.l1.go = "spanish_4";
		break;
		
		case "spanish_4":
			dialog.text = "Malheureusement, il n'y a rien de plus à dire. Les détails des opérations de votre frère n'étaient connus que de lui-même et du Chevalier de Poincy. Nous sommes des chevaliers de l'Ordre de Saint-Jean de Malte. Nous exécutons nos ordres.";
			link.l1 = "Si le Chevalier a tant confiance en Michel, c'est qu'il a dû réussir à mener à bien ses plans secrets auparavant. Connaissez-vous des actions réussies que Michel a réalisées ?";
			link.l1.go = "spanish_5";
		break;
		
		case "spanish_5":
			dialog.text = "Très certainement. Cet échec récent de Michel de Monper était aussi son premier échec, c'est pourquoi nous avons été choqués par la réaction du Chevalier. Il y a peu, le 'Gryffindor' a capturé un galion espagnol rempli d'argent grâce à la planification minutieuse de Michel. Cela seul aurait dû compenser des douzaines d'échecs futurs. Et pourtant, votre frère a été arrêté.";
			link.l1 = "Je vois. Avez-vous une idée pourquoi Michel a fui St. Pierre ?";
			link.l1.go = "spanish_6";
		break;
		
		case "spanish_6":
			dialog.text = "Je soupçonne qu'un conflit interpersonnel entre Michel et de Poincy fut la raison de son arrestation. Évidemment, votre frère craint que le Chevalier continue de le persécuter même après sa libération, alors il a pris des mesures de précaution. Et vous savez quoi, Monsieur de Maure - personne ici ne le blâme pour sa décision !\nL'homme avait travaillé courageusement pour le bien de l'Ordre et pourtant ils l'ont jeté dans une cellule fétide pour son tout premier échec, alors qu'il était grièvement blessé ! Un échec qui n'était même pas si grave, personne n'est mort et aucun navire n'a coulé !\nD'ailleurs, cette conversation est strictement officieuse et je ne répéterai pas ce que je viens de dire même sous serment, sommes-nous clairs là-dessus, Monsieur de Maure ?";
			link.l1 = "Oui, monsieur. J'ai déjà oublié que nous avons eu cette conversation. Dites-moi, l'attaque espagnole sur St. Pierre aurait-elle pu être provoquée par l'Ordre pillant les navires espagnols ? Peut-être ce même galion espagnol avec l'argent que vous avez mentionné ? Les Castillans étaient extrêmement zélés à chercher votre base...";
			link.l1.go = "spanish_7";
		break;
		
		case "spanish_7":
			dialog.text = "J'en doute. Très peu de gens connaissent la présence de l'Ordre aux Caraïbes et toutes nos sorties contre les Espagnols ont été soigneusement planifiées. Demandez à l'officier espagnol que nous avons fait prisonnier, il tempère actuellement son fougueux caractère castillan dans nos casemates. Nous l'avons déjà interrogé. L'attaque de Saint-Pierre était un raid ordinaire, organisé par un grand baron espagnol nommé Ramon de Mendoza y Riba dans le but de son propre profit et pour intimider les colonies françaises. Il voulait aussi s'attirer les faveurs de l'Escurial.";
			link.l1 = "Je parlerai à cet Espagnol. Où puis-je le trouver ?";
			link.l1.go = "spanish_8";
		break;
		
		case "spanish_8":
			dialog.text = "En bas, dans la même cellule où votre frère était détenu.";
			link.l1 = "Je connais le chemin. Je serai de retour après avoir interrogé l'Espagnol. Il se peut que j’aie quelques questions supplémentaires.";
			link.l1.go = "spanish_9";
		break;
		
		case "spanish_9":
			DialogExit();
			NextDiag.CurrentNode = "Maltie_officer";
			AddQuestRecord("Guardoftruth", "2");
			pchar.questTemp.Guardoftruth = "prisoner";
			sld = characterFromId("spa_baseprisoner");
			LAi_CharacterEnableDialog(sld);
			chrDisableReloadToLocation = true;//закрыть локацию
		break;
		
		case "spanish_10":
			dialog.text = "Eh bien, n'est-ce pas quelque chose ! Vous comprenez que je ne peux pas libérer ce captif, n'est-ce pas ? Ce vaurien a aidé à mener l'attaque sur St. Pierre !";
			link.l1 = "Officier, ceci est un témoin important. L'attaque sur St. Pierre n'était pas une simple razzia pour le butin. Don Ramon Mendosa cherchait autre chose. Nous devons obtenir un motif définitif. Alors, me remettrez-vous cet Espagnol ou devrai-je demander l'autorisation à de Poincy ?";
			link.l1.go = "spanish_11";
		break;
		
		case "spanish_11":
			dialog.text = "Par le Dieu Tout-Puissant... Très bien, prenez-le. J'étais sur le point de pendre ce salaud de toute façon sur la place de Saint-Pierre comme le pirate ordinaire qu'il est... Maintenant c'est votre problème. Veillez à ce qu'il n'échappe pas à la justice !";
			link.l1 = "Sans aucun doute. Je répondrai de cet Espagnol devant de Poincy. Faites enchaîner ce captif et livrez-le à ma chaloupe au quai de la ville.";
			link.l1.go = "spanish_12";
		break;
		
		case "spanish_12":
			dialog.text = "Très bien, capitaine.";
			link.l1 = "Encore une chose, officier. Le nom de Miguel Dichoso vous dit-il quelque chose ?";
			link.l1.go = "spanish_13";
		break;
		
		case "spanish_13":
			dialog.text = "Non. Je ne l'ai jamais entendu auparavant. Pourquoi demandes-tu?";
			link.l1 = "Êtes-vous sûr? Donc, vous n'avez rencontré personne de ce nom, ni ici dans votre cantonnement, ni au palais du gouverneur, ni nulle part à St. Pierre?";
			link.l1.go = "spanish_14";
		break;
		
		case "spanish_14":
			dialog.text = "Non, je n'en ai pas. Nous n'avons pas une haute opinion des Espagnols d'où je viens.";
			link.l1 = "D'accord. Quoi qu'il en soit, c'était prévisible. Cela aurait été trop facile... Merci, officier ! Vous avez été très utile.";
			link.l1.go = "spanish_15";
		break;
		
		case "spanish_15":
			dialog.text = "Vous êtes le bienvenu... Qu'en pensez-vous, Monsieur de Maure, où se trouve votre frère maintenant ?";
			link.l1 = "Je voudrais bien connaître la réponse à cette question moi-même. Et je le découvrirai... tôt ou tard. Au revoir !";
			link.l1.go = "spanish_16";
		break;
		
		case "spanish_16":
			DialogExit();
			NextDiag.CurrentNode = "Maltie_officer";
			AddQuestRecord("Guardoftruth", "3");
			pchar.questTemp.Guardoftruth = "toship";
			sld = characterFromId("spa_baseprisoner");
			sld.dialog.currentnode = "spa_prisoner_28";
			LAi_CharacterEnableDialog(sld);
		break;
		
	// монах-посланник от Винсенто
		case "monk_vinsento":
			dialog.text = TimeGreeting()+"! Êtes-vous capitaine "+GetFullName(pchar)+"?";
			link.l1 = "Oui, c'est moi. Que puis-je faire pour vous ?";
			link.l1.go = "monk_vinsento_1";
		break;
		
		case "monk_vinsento_1":
			dialog.text = "Salutations, capitaine. J'ai été envoyé à vous par le Père Vincento. J'ai quelque chose pour vous...";
			link.l1 = "Père Vincento ? Je ne travaille plus pour Son Excellence. Pas après qu'il ait envoyé Alonso de Maldonado, l'homme juré de Diego de Montoya, pour me tuer. Vous pouvez transmettre ce message au Révérend Père : il a échoué.";
			link.l1.go = "monk_vinsento_2";
		break;
		
		case "monk_vinsento_2":
			dialog.text = "Attendez, capitaine. Le père Vincento s'attendait à une telle réaction de votre part et m'en a averti. Je vous assure que Son Excellence ne vous veut aucun mal. S'il vous plaît, lisez cette lettre. C'est très, très important.";
			link.l1 = "Le Père Vincento ne me veut aucun mal ? Hm. Peut-être qu'il a également omis de te parler de moi et de Don de Maldonado ? Je vois pourquoi je devrais te croire.";
			link.l1.go = "monk_vinsento_3";
		break;
		
		case "monk_vinsento_3":
			dialog.text = "Prenez cette lettre, capitaine. Lisez-la et prenez votre propre décision. Sachez simplement que le sort de toute la chrétienté est entre vos mains. Ne prenez pas cela à la légère. Que Dieu vous bénisse et guide vos pas sur le chemin de la droiture !";
			link.l1 = "D'accord, donne-moi la lettre.";
			link.l1.go = "monk_vinsento_4";
		break;
		
		case "monk_vinsento_4":
			GiveItem2Character(pchar, "specialletter"); 
			ChangeItemDescribe("specialletter", "itmdescr_specialletter_vinsento");
			sld = ItemsFromID("specialletter");
			sld.text = "Letter_Vincento_last";
			dialog.text = "Voilà. Je prie que vous fassiez le bon choix. Pax vobiscum.";
			link.l1 = "...";
			link.l1.go = "monk_vinsento_5";
		break;
		
		case "monk_vinsento_5":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 30.0);
			ReOpenQuestHeader("Sharlie"); // patch-8
			AddQuestRecord("Sharlie", "40");
			CloseQuestHeader("Ksochitam");
		break;
		
	// падре Адриан
		case "adrian":
			dialog.text = "Salutations, mon fils. Que le Seigneur soit avec vous.";
			link.l1 = "Et avec vous aussi, Père Adrian. Son Excellence a dit que vous pouvez me fournir des amulettes et des remèdes.";
			link.l1.go = "adrian_1";
		break;
		
		case "adrian_1":
			dialog.text = "Oui, bien sûr. J'ai reçu une cargaison spéciale de Santiago rien que pour toi. Voici des amulettes bénies et des potions de guérison. Et pour couronner le tout, une teinture rare et unique d'Ometochtli qui te rendra invincible au combat. Tout cela est pour toi, mon fils. Prends et vois que le Seigneur est bon.";
			link.l1 = "Merci !";
			link.l1.go = "adrian_2";
		break;
		
		case "adrian_2":
			for(i=2; i<=10; i++)
			{
				if (i == 4 || i == 5 || i == 8 || i == 9) continue;
				TakeNItems(pchar, "amulet_"+i, 2);
			}
			TakeNItems(pchar, "potion2", 20);
			TakeNItems(pchar, "potion4", 10);
			TakeNItems(pchar, "potion7", 3);
			TakeNItems(pchar, "berserker_potion", 3);
			dialog.text = "Si vous avez besoin de plus d'herbes médicinales, je peux vous fournir une fiole de chaque chaque jour. Je préparerai autant que vous en aurez besoin.";
			link.l1 = "Vous avez ma gratitude, Père Adrian. Je garderai cela à l'esprit.";
			link.l1.go = "exit";
			link.l2 = "Super. J'en ai besoin tout de suite.";
			link.l2.go = "potion";
			NextDiag.TempNode = "adrian_3";
		break;
		
		case "adrian_3":
			dialog.text = "Que Dieu te bénisse et te garde, mon fils. Que désires-tu ?";
			link.l1 = "Je voudrais acheter quelques potions de guérison.";
			link.l1.go = "potion";
			link.l2 = "Rien pour le moment, je me prépare pour un voyage. Je suis juste passé pour dire bonjour et voir comment tu te portes.";
			link.l2.go = "exit";
			NextDiag.TempNode = "adrian_3";
		break;
		
		case "potion":
			dialog.text = "Bien sûr, mon fils. De quel remède as-tu besoin?";
			if (!CheckAttribute(npchar, "potion1_date") || GetNpcQuestPastDayParam(npchar, "potion1_date") >= 1)
			{
				link.l1 = "Juste un simple remède.";
				link.l1.go = "potion1";
			}
			if (!CheckAttribute(npchar, "potion2_date") || GetNpcQuestPastDayParam(npchar, "potion2_date") >= 1)
			{
				link.l2 = "Un élixir vivifiant.";
				link.l2.go = "potion2";
			}
			if (!CheckAttribute(npchar, "potion3_date") || GetNpcQuestPastDayParam(npchar, "potion3_date") >= 1)
			{
				link.l3 = "Un antidote.";
				link.l3.go = "potion3";
			}
			if (!CheckAttribute(npchar, "potion4_date") || GetNpcQuestPastDayParam(npchar, "potion4_date") >= 1)
			{
				link.l4 = "Un mélange d'herbes.";
				link.l4.go = "potion4";
			}
			link.l5 = "Désolé de vous importuner, père. J'ai changé d'avis.";
			link.l5.go = "exit";
		break;
		
		case "potion1":
			npchar.quest.price = 90;
			npchar.quest.type = 1;
			dialog.text = "Une essence réparatrice ? Cela coûte 90 pesos, mon fils. Pour les matériaux, bien sûr.";
			if (sti(Pchar.money) >= 90)
			{
				link.l1 = "Merci, père.";
				link.l1.go = "potion_pay";
			}
			else
			{
				link.l1 = "Malheureusement, je n'ai pas l'argent... Je reviendrai plus tard.";
				link.l1.go = "exit";
			}
		break;
		
		case "potion2":
			npchar.quest.price = 500;
			npchar.quest.type = 2;
			dialog.text = "Un élixir revitalisant ? 500 pesos, mon fils.";
			if (sti(Pchar.money) >= 500)
			{
				link.l1 = "Merci, père.";
				link.l1.go = "potion_pay";
			}
			else
			{
				link.l1 = "Malheureusement, je n'ai pas l'argent... Je reviendrai plus tard.";
				link.l1.go = "exit";
			}
		break;
		
		case "potion3":
			npchar.quest.price = 200;
			npchar.quest.type = 3;
			dialog.text = "Un antidote ? 200 pesos, mon fils.";
			if (sti(Pchar.money) >= 200)
			{
				link.l1 = "Merci, père.";
				link.l1.go = "potion_pay";
			}
			else
			{
				link.l1 = "Malheureusement, je n'ai pas l'argent... Je reviendrai plus tard.";
				link.l1.go = "exit";
			}
		break;
		
		case "potion4":
			npchar.quest.price = 900;
			npchar.quest.type = 4;
			dialog.text = "Un mélange d'herbes ? 900 pesos, mon fils.";
			if (sti(Pchar.money) >= 900)
			{
				link.l1 = "Merci, père.";
				link.l1.go = "potion_pay";
			}
			else
			{
				link.l1 = "Malheureusement, je n'ai pas l'argent... Je reviendrai plus tard.";
				link.l1.go = "exit";
			}
		break;
		
		case "potion_pay":
			AddMoneyToCharacter(pchar, -sti(npchar.quest.price));
			iTemp = sti(npchar.quest.type);
			GiveItem2Character(pchar, "potion"+iTemp);
			PlaySound("interface\important_item.wav");
			dialog.text = "«'Car je te rétablirai en santé, et je te guérirai de tes blessures, dit le Seigneur.' Voici ton médicament. Dominus vobiscum !»";
			link.l1 = "Merci, Père Adrien.";
			link.l1.go = "exit";
			SaveCurrentNpcQuestDateParam(npchar, "potion"+iTemp+"_date");
			NextDiag.TempNode = "adrian_3";
		break;
		
	// посланец Дичозо
		case "Dichoso_agent":
			dialog.text = "Capitaine "+GetFullName(pchar)+"?";
			link.l1 = "Oui, c'est moi. Que voulez-vous ?";
			link.l1.go = "Dichoso_agent_1";
		break;
		
		case "Dichoso_agent_1":
			dialog.text = "J'ai un message pour vous de la part du capitaine Miguel Dichoso. Il dit que vous le connaissez.";
			link.l1 = "Oui, j'ai entendu parler de lui. Je n'ai jamais eu l'honneur de le rencontrer en personne.";
			link.l1.go = "Dichoso_agent_2";
		break;
		
		case "Dichoso_agent_2":
			dialog.text = "Le capitaine Dichoso aimerait changer cela. Il souhaite vous rencontrer en face-à-face. Il a une offre pour vous concernant une expédition dans les profondeurs du Main espagnol vers la cité indienne perdue de Tayasal. Il m'a dit que votre expérience associée à sa connaissance produira des résultats gratifiants.";
			link.l1 = "Ce furent ses mots exacts ?";
			link.l1.go = "Dichoso_agent_3";
		break;
		
		case "Dichoso_agent_3":
			dialog.text = "Correct. Le capitaine Dichoso vous attendra à Saint-Christophe. Il vous attendra dans la grande crypte du cimetière de Capsterville, afin d'éviter les regards et oreilles indiscrets.";
			link.l1 = "Hm...";
			link.l1.go = "Dichoso_agent_4";
		break;
		
		case "Dichoso_agent_4":
			dialog.text = "Dichoso m'a averti que vous hésiteriez. Il m'a dit de vous offrir des garanties que vous ne serez pas blessé pendant les négociations, quelle que soit votre décision. Il ajoute également que ce que vous avez trouvé sur une certaine île n'était qu'un petit hors-d'oeuvre par rapport à ce que vous trouveriez à Tayasal.";
			link.l1 = "Est-ce bien vrai... c'est fort intriguant. Mais pourquoi le capitaine Dichoso ne viendrait-il pas me rendre visite lui-même ? Pourquoi a-t-il envoyé un tiers ?";
			link.l1.go = "Dichoso_agent_5";
		break;
		
		case "Dichoso_agent_5":
			dialog.text = "Don Dichoso vous a d'abord cherché sur Isla Tesoro, puis ici, et maintenant il est parti pour Saint-Christophe dans l'espoir de vous y trouver. Vous êtes bien un officier de Philippe de Poincy, n'est-ce pas ? Je devais vous attendre ici au cas où vous arriveriez à Blueweld.";
			link.l1 = "Alors tout est clair. Bon, d'accord. Je ne vais pas perdre de temps, je devrais aller à Capsterville.";
			link.l1.go = "Dichoso_agent_6";
		break;
		
		case "Dichoso_agent_6":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "Tieyasal_PrepareDichosoTrap", -1);
		break;
		
	// агент Дичозо
		case "Dichoso_crypt_agent":
			dialog.text = "Eh bien, enfin nous nous rencontrons, capitaine "+GetFullName(pchar)+"...";
			if (CheckAttribute(pchar, "questTemp.Tieyasal.MigelKnow")) 
			{
				link.l1 = "Où est Miguel Dichoso ? Et n'essaie pas de t'en tirer à bon compte. Je sais qui il est vraiment et je pense que toi aussi.";
				link.l1.go = "Dichoso_crypt_agent_2";
			}
			else
			{
				link.l1 = "Je suppose que c'est Miguel Dichoso en chair et en os juste devant moi ?";
				link.l1.go = "Dichoso_crypt_agent_1";
			}
		break;
		
		case "Dichoso_crypt_agent_1":
			dialog.text = "Vous supposez correctement, capitaine. Nous nous poursuivons mutuellement depuis longtemps, n'est-ce pas ?";
			if (CheckAttribute(pchar, "questTemp.Ksochitam.SQCapBookRead")) // прочел журнал Санта-Квитерии
			{
				link.l1 = "Je peux dire que tu mens rien qu'en te regardant, l'ami. Tu n'es pas Dichoso. J'ai lu les journaux de bord du capitaine de la 'Santa Quiteria' et j'ai demandé à droite et à gauche à quoi il ressemblait. Tu ne lui ressembles pas. Tu n'as même pas une cicatrice sur le visage d'un coup de sabre de cavalerie. Allons, même un comédien aurait au moins essayé de la dessiner !";
				link.l1.go = "Dichoso_crypt_agent_2";
			}
			else
			{
				link.l1 = "Exactement. Si je comprends bien, nous sommes ici pour parler de la cité perdue de Tayasal ?";
				link.l1.go = "Dichoso_crypt_agent_7";
			}
		break;
		
		case "Dichoso_crypt_agent_2":
			dialog.text = "Ha ! Pas la peine de continuer cette farce alors. Miguel m'a averti que tu étais un coquin rusé...";
			link.l1 = "Où est Miguel Dichoso ?";
			link.l1.go = "Dichoso_crypt_agent_3";
		break;
		
		case "Dichoso_crypt_agent_3":
			dialog.text = "Il n'est pas ici. Je suis autorisé à vous rencontrer et à vous parler en son nom.";
			link.l1 = "Je ne parlerai pas avec un pion. Je suis ici pour le roi. Où est-il ?!";
			link.l1.go = "Dichoso_crypt_agent_4";
		break;
		
		case "Dichoso_crypt_agent_4":
			dialog.text = "Tu n'es pas un partenaire de conversation agréable, capitaine. Tu as perdu ton calme.";
			link.l1 = "Assez de jeux, je comprends. C'est encore une embuscade. Vous, les gars, devez trouver de nouveaux tours.";
			link.l1.go = "Dichoso_crypt_agent_5";
		break;
		
		case "Dichoso_crypt_agent_5":
			dialog.text = "Ahaha, correct encore, camarade ! Mes hommes t'attendent juste derrière la porte menant aux catacombes. De plus, j'ai des mousquetaires cachés derrière chaque pierre tombale, prêts à tirer. Il n'y a pas d'échappatoire. Aussi répétitif que ce stratagème puisse être, tu es tombé dedans ! Ton désir de voir Tayasal a surpassé ton bon sens !";
			link.l1 = "Tu as choisi un endroit parfait pour un combat, racaille. Je n'aurai pas à aller loin pour t'enterrer, toi et tes amis brigands.";
			link.l1.go = "Dichoso_crypt_agent_6";
		break;
		
		case "Dichoso_crypt_agent_6":
			dialog.text = "Ahah ! J'aime ton esprit ! Tout comme celui de Miguel ! Dis ce que tu veux, vous êtes tous deux taillés dans le même tissu... Je ferai exactement comme il l'a ordonné - je t'enverrai en Enfer le plus vite et le plus indolore possible. Aux armes, les gars !";
			link.l1 = "Des hommes meilleurs que toi ont essayé. Salue le Diable de ma part, vaurien !";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Tieyasal_StartCryptBattle");
		break;
		
		case "Dichoso_crypt_agent_7":
			dialog.text = "Vous voulez vraiment atteindre la ville ? Je comprends, capitaine, mais je ne pense pas que ce soit une bonne idée.";
			link.l1 = "Alors, de quoi sommes-nous ici pour discuter ?";
			link.l1.go = "Dichoso_crypt_agent_8";
		break;
		
		case "Dichoso_crypt_agent_8":
			dialog.text = "Je ne cherche pas à entamer une longue conversation romantique avec toi. Ta présence ici me suffit.";
			link.l1 = "Assez de jeux, je comprends. C'est encore une embuscade. Vous, les gars, devez trouver de nouveaux tours.";
			link.l1.go = "Dichoso_crypt_agent_5";
		break;
		
	// командир абордажников
		case "newcastle_officer":
			dialog.text = "En attente de vos ordres, capitaine !";
			link.l1 = "Nous traversons la jungle jusqu'au cimetière de Capsterville. Une fois sur place, n'entrez pas dans le cimetière lui-même. Prenez des positions de tir juste à l'extérieur de la porte et écoutez attentivement lorsque je vais à l'intérieur. Si vous entendez des combats, précipitez-vous immédiatement.";
			link.l1.go = "newcastle_officer_1";
		break;
		
		case "newcastle_officer_0":
			dialog.text = "En attente de vos ordres, capitaine !";
			link.l1 = "Nous traversons la jungle jusqu'au cimetière de Capsterville. Une fois là-bas, n'entrez pas dans le cimetière lui-même. Prenez position le long du sentier, entourez le cimetière, et écoutez attentivement lorsque j'irai à l'intérieur. Tout ce plan pue l'embuscade. Dès que vous voyez l'ennemi, attaquez immédiatement.";
			link.l1.go = "newcastle_officer_1";
		break;
		
		case "newcastle_officer_1":
			dialog.text = "Oui oui, capitaine !";
			link.l1 = "D'accord. En avant !";
			link.l1.go = "newcastle_officer_2";
		break;
		
		case "newcastle_officer_2":
			DialogExit();
			chrDisableReloadToLocation = false;
			locations[FindLocation("Charles_exittown")].DisableEncounters = true; //энкаутеры закрыть
			locations[FindLocation("Charles_CaveEntrance")].DisableEncounters = true; //энкаутеры закрыть
			for(i=2; i<=4; i++)
			{
				locations[FindLocation("Charles_Jungle_0"+i)].DisableEncounters = true; //энкаутеры закрыть
			}
			LocatorReloadEnterDisable("Shore42", "boat", true);
			for(i=1; i<=iTotalTemp; i++)
			{
				sld = characterFromID("Tieyasal_Oursoldier_"+i);
				LAi_SetActorType(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			// на локацию перед кладбищем
			pchar.quest.Tieyasal_newcastle.win_condition.l1 = "location";
			pchar.quest.Tieyasal_newcastle.win_condition.l1.location = "Charles_exittown";
			pchar.quest.Tieyasal_newcastle.function = "Tieyasal_NewcastleGoJungle";
			// на крипту
			pchar.quest.Tieyasal_graveyard.win_condition.l1 = "location";
			pchar.quest.Tieyasal_graveyard.win_condition.l1.location = "Charles_CryptBig2";
			pchar.quest.Tieyasal_graveyard.function = "Tieyasal_InGraveyardCrypt";
		break;

case "Europe":
			PlaySound("Voice\English\military01.wav");
			dialog.text = "Capitaine Hobart ! Selon les informations de notre espion, des rebelles se cachent dans cette propriété. Vous avez cinq dragons à votre disposition. Fouillez le bâtiment et saisissez tous ceux qui s'y trouvent ! Ne traitez pas ces canailles avec des gants de velours. Vous agissez au nom du Roi !";
			link.l1 = "Oui, monsieur !";
			link.l1.go = "Europe_1";
		break;
		
		case "Europe_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Europe_SharlieFinal_1", 5);
		break;
		
		//Индеец по квесту "Знакомство с индейцами"
		case "ZsI_ListKakao":
			dialog.text = "Tsk ! Fils de la mer !";
			link.l1 = "Euh... quoi? Vous m'adressez la parole?";
			link.l1.go = "ZsI_ListKakao_1";
			sld = characterFromId("Tichingitu");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
		break;
		
		case "ZsI_ListKakao_1":
			dialog.text = "D'accord. Je suis Feuille de Cacao. J'ai affaire avec toi, Fils de la Mer.";
			link.l1 = "Je ne sais pas à quoi ressemble le cacao, ni pourquoi tu portes son nom. Mais soit, dis-moi ce dont tu as besoin, rapidement.";
			link.l1.go = "ZsI_ListKakao_2";
		break;
		
		case "ZsI_ListKakao_2":
			dialog.text = "Tsk ! Tu vas en ville. Achète deux pistolets et deux fois dix de poudre et balles. Donne-les moi. Il y a une récompense. Le Fils de la Mer sera ravi.";
			link.l1 = "Deux pistolets et vingt balles? C'est tout? Pourquoi ne les achètes-tu pas toi-même alors?";
			link.l1.go = "ZsI_ListKakao_3";
		break;
		
		case "ZsI_ListKakao_3":
			dialog.text = "Tu ne comprends pas, visage pâle ? Qui me vendrait une arme à feu ?!";
			if (CheckAttribute(pchar, "questTemp.ZsI_Cannibals"))		//Sinistra Только если проходил квест "Каннибалы"
			{
				link.l1 = "Tu sais, j'ai déjà croisé des gens comme toi en Martinique... Des cannibales. Ils ont kidnappé une fille et deux hommes. Ils ont rôti et mangé l'un des hommes. Si l'un d'eux avait eu un pistolet, nous n'aurions pas cette conversation.";
				link.l1.go = "ZsI_ListKakao_3_1";
			}
			else
			{
				link.l1 = "Et pourquoi as-tu besoin d'une arme à feu, Feuille de Cacao ? Veux-tu tuer quelqu'un ?";
				link.l1.go = "ZsI_ListKakao_3_2";
			}
		break;
		
		case "ZsI_ListKakao_3_1":
			dialog.text = "Oo-ouh ! Feuille de Cacao n'est pas un brigand, mon combat est seulement pour les guerriers de ta tribu. Les Visages-Pâles viennent sur notre terre, nous font esclaves. Feuille de Cacao lui-même se bat. Prendre un esclave. Pas bon, pas mauvais. C'est comme ça que ça se passe. Indien, blanc, pas de différence. Les armes à feu font la différence.";
			link.l1 = "Et pourquoi as-tu besoin d'une arme à feu, Feuille de Cacao ? Veux-tu tuer quelqu'un ?";
			link.l1.go = "ZsI_ListKakao_3_2";
		break;
		
		case "ZsI_ListKakao_3_2":
			dialog.text = "Se battre. Mais à armes égales. Les visages pâles ont des armes à feu, les Indiens non. C'est injuste. Et avoir une arme à feu pour un Indien - c'est une protection contre le traitement injuste, l'humiliation ou l'insulte par les visages pâles.";
			link.l1 = "";
			link.l1.go = "ZsI_ListKakao_4";
		break;
		
		case "ZsI_ListKakao_4":
			StartInstantDialog("Tichingitu", "ZsI_ListKakao_5", "Quest\Sharlie\OtherNPC.c");
		break;
		
		case "ZsI_ListKakao_5":
			dialog.text = "D'accord, Capitaine. Les visages pâles nous méprisent.";
			link.l1 = "J'ai remarqué. En Europe, ils prêchent qu'il faut enseigner la vraie foi aux Indiens, et comment nous travaillons tous ensemble paisiblement dans les plantations...";
			link.l1.go = "ZsI_ListKakao_7";
		break;
		
		case "ZsI_ListKakao_7":
			dialog.text = "Tichingitu ne comprend peut-être pas le capitaine, mais il comprend la feuille de coca. Il cherche à se venger.";
			link.l1 = "On dirait bien... Ne veux-tu pas aussi te venger de nos récents geôliers ?";
			link.l1.go = "ZsI_ListKakao_8";
		break;
		
		case "ZsI_ListKakao_8":
			dialog.text = "Peut-être. Mais Tichingitu ne recourra pas à cela. Tichingitu est avec toi maintenant. Et Tichingitu utilise sa propre tête. Il y aura trop de carnage. Du sang blanc. Du sang indien. Trop de souffrances. Ce n'est pas juste.";
			link.l1 = "Oui, c'est déjà mauvais, et aider Feuille de Cacao à obtenir des armes ne fera qu'empirer les choses... Mais il n'a pas tort. Et j'ai encore un équipage à payer bientôt.";
			link.l1.go = "ZsI_ListKakao_9";
		break;
		
		case "ZsI_ListKakao_9":
			dialog.text = "Utilise ta propre tête, Capitaine.";
			link.l1 = "";
			link.l1.go = "ZsI_ListKakao_10";
		break;
		
		case "ZsI_ListKakao_10":
			StartInstantDialog("ListKakao", "ZsI_ListKakao_11", "Quest\Sharlie\OtherNPC.c");
		break;
		
		case "ZsI_ListKakao_11":
			dialog.text = "Le Fils de la Mer parle beaucoup. On dirait une squaw avec une moustache.";
			link.l1 = "Qui ? Explique-moi cela, Feuille de Cacao. Je suis un visage pâle aussi et tu me demandes des armes pour combattre des visages pâles. N'est-ce pas contradictoire ? Pourquoi t'adresser à moi ?";
			link.l1.go = "ZsI_ListKakao_12";
		break;
		
		case "ZsI_ListKakao_12":
			dialog.text = "J'ai surpris ta conversation avec cet Indien étrangement vêtu. Tu n'es pas comme les autres visages pâles. Tu comprends Tichingitu. Et tu comprends la feuille de coca, j'en suis sûr.";
			link.l1 = "Oh... Que proposeras-tu pour des armes, Feuille de Cacao ?";
			link.l1.go = "ZsI_ListKakao_13";
		break;
		
		case "ZsI_ListKakao_13":
			dialog.text = "Les larmes des dieux. Vous les appelez des perles. Beaucoup de perles.";
			link.l1 = "J'ai pris ma décision, Feuille de Cacao. Attends ici, je vais chez le marchand d'armes. J'achèterai ce dont j'ai besoin et je reviendrai.";
			link.l1.go = "ZsI_ListKakao_Soglasen_5";
			if (sti(pchar.items.pistol1) >= 2 && sti(pchar.items.GunPowder) >= 20 && sti(pchar.items.bullet) >= 20)
			{
				link.l2 = "J'ai pris ma décision, Feuille de Cacao. Il se trouve que j'ai déjà ce dont tu as besoin. Tiens, le voilà.";
				link.l2.go = "ZsI_ListKakao_Soglasen_2";
			}
			link.l3 = "J'ai pris ma décision, Feuille de Cacao. Je ne veux pas attirer d'ennuis inutiles. Tu n'obtiendras pas d'armes à feu de ma part. Passe ton chemin.";
			link.l3.go = "ZsI_ListKakao_Otkaz";
			npchar.LifeDay = 1;
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");
		break;
		
		case "ZsI_ListKakao_Otkaz":
			dialog.text = "Tsk!";
			link.l1 = "";
			link.l1.go = "ZsI_ListKakao_Otkaz_2";
		break;
		
		case "ZsI_ListKakao_Otkaz_2":
			DialogExit();
			
			ChangeIndianRelation(-3.0);
			ChangeCharacterComplexReputation(pchar, "authority", -1);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "ZsI_Mir", -1);
			LAi_SetImmortal(npchar, false);
			LAi_SetHP(npchar, 1.0, 1.0);
			npchar.lifeday = 0;
			PChar.quest.ZsI_Draka.win_condition.l1 = "NPC_Death";
			PChar.quest.ZsI_Draka.win_condition.l1.character = "ListKakao";
			PChar.quest.ZsI_Draka.win_condition = "ZsI_Draka";
			PChar.quest.ZsI_Mir.win_condition.l1 = "ExitFromLocation";
			PChar.quest.ZsI_Mir.win_condition.l1.location = PChar.location;
			PChar.quest.ZsI_Mir.win_condition = "ZsI_Mir";
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			sld = characterFromId("Tichingitu");
			LAi_SetOfficerType(sld);
			sld.Dialog.Filename = "Quest\Sharlie\Tichingitu.c";
			sld.Dialog.CurrentNode = "Tichingitu_officer";
			LaunchTutorial("Fighter", 1);
		break;
		
		case "ZsI_ListKakao_Soglasen_2":
			dialog.text = "Uh-oh ! Le Fils de la Mer a-t-il un mousquet ? Payer un prix fort pour un mousquet !";
			link.l1 = "Non, mais un canon de mon navire ferait-il l'affaire ? Pars maintenant, Feuille de Cacao, avant qu'on ne soit repéré et arrêté.";
			link.l1.go = "ZsI_ListKakao_Soglasen_3";
			AddCharacterExpToSkill(pchar, "Commerce", 50);
			ChangeIndianRelation(3.0);
			AddItems(pchar, "jewelry53", 180);
			Log_Info("You have received 180 small pearls");
			PlaySound("Interface\important_item.wav");
			DeleteAttribute(pchar, "questTemp.ZsI_PokupaemPistolety");
			if (sti(pchar.items.pistol1) >= 2 && sti(pchar.items.GunPowder) >= 20 && sti(pchar.items.bullet) >= 20)
			{
				RemoveCharacterEquip(PChar, GUN_ITEM_TYPE);
				RemoveItems(PChar, "pistol1", 2);
				RemoveItems(PChar, "GunPowder", 20);
				RemoveItems(PChar, "bullet", 20);
			}
		break;
		
		case "ZsI_ListKakao_Soglasen_3":
			dialog.text = "Bon marché ! Fils de la Mer, si tu entres dans la selva, prends une arme à feu. Rencontre un Indien, fais une affaire.";
			link.l1 = "Je m'en souviendrai. Adieu, Feuille de Cacao.";
			link.l1.go = "ZsI_ListKakao_Soglasen_4";
		break;
		
		case "ZsI_ListKakao_Soglasen_4":
			DialogExit();
			
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			npchar.lifeday = 0;
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			
			Return_TichingituOfficer();
			LaunchTutorial("Fighter", 1);
		break;
		
		case "ZsI_ListKakao_Soglasen_5":
			dialog.text = "La feuille de cacao attendra.";
			link.l1 = "Bonjour, mon ami.";
			link.l1.go = "ZsI_ListKakao_Soglasen_6";
		break;
		
		case "ZsI_ListKakao_Soglasen_6":
			DoQuestReloadToLocation("BasTer_town", "reload", "gate_back", "ZsI_TPvGorod");
		break;

		case "ZsI_officer":
			sld = CharacterFromID("Tichingitu");
			if (sld.location == pchar.location && !LAi_IsDead(sld))
			{
				dialog.text = "Bah, on dirait qu'on a un rassemblement de natifs ici!\nTu veux retourner en prison, chien?\nQue fais-tu ici, Monsieur?";
			}
			else
			{
				dialog.text = "Halte! Que faites-vous ici, Monsieur?";
			}
			link.l1 = "";
			link.l1.go = "ZsI_officer_2";
			sld = CharacterFromID("ListKakao");
			LAi_CharacterEnableDialog(sld);
			EndBattleLandInterface();
		break;
		
		case "ZsI_officer_2":
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("ListKakao"));
			dialog.text = "Eh, ordure, attendais-tu cet honnête citoyen ?";
			link.l1 = "";
			link.l1.go = "ZsI_officer_3";
		break;
		
		case "ZsI_officer_3":
			DialogExit();
			StartInstantDialog("ListKakao", "ZsI_officer_4", "Quest\Sharlie\OtherNPC.c");
		break;
		
		case "ZsI_officer_4":
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("ZsI_Patrul_off"));
			dialog.text = "Tous les visages pâles se ressemblent pour moi. Mais je n'ai jamais vu celui-ci. Toi, guerrier, fais ce que tu dois avec moi. Cela devient fatigant. Feuille de Cacao est prêt à affronter les esprits de la forêt.";
			link.l1 = "";
			link.l1.go = "ZsI_officer_5";
		break;
		
		case "ZsI_officer_5":
			DialogExit();
			StartInstantDialog("ZsI_Patrul_off", "ZsI_officer_6", "Quest\Sharlie\OtherNPC.c");
		break;
		
		case "ZsI_officer_6":
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("ListKakao"));
			dialog.text = "L'enfer t'attend, pas les esprits de la forêt.";
			link.l1 = " ";
			link.l1.go = "ZsI_officer_7";
		break;
		
		case "ZsI_officer_7":
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, pchar);
			dialog.text = "Capitaine, vous êtes relevé de vos fonctions. Tenez-vous à l'écart. Protéger la ville est une affaire sérieuse.";
			link.l1 = "Je vois... Mais qu'en est-il de cet Indien ?";
			link.l1.go = "ZsI_officer_8";
		break;
		
		case "ZsI_officer_8":
			dialog.text = "Quel est votre intérêt pour les Indiens, Monsieur ? Bien que... eh bien, oui, vous venez tout juste d'Europe\nComment va Paris ? Écrasent-ils encore les rats de la ville, ou ont-ils commencé à les inviter à la communion ? Vous voyez, ici, nous avons des indigènes au lieu de rats. Ils font des affaires avec les boucaniers, attaquent les bûcherons, ils mangent des gens, bon sang\nIl y a trois jours, un individu brillant avait déjà vendu un mousquet à des gens comme celui-ci. Et devinez quoi ? Ces salauds ont tué tous les soldats de la patrouille, dirigée, soit dit en passant, par mon ami et camarade. Nous avons trouvé le colon-traître et l'avons pendu à sécher au soleil, pour donner l'exemple. Donner des armes à feu aux Indiens ! C'est de la trahison ! Trahison contre la France ! Nous avons suivi ce singe coloré depuis un moment car il est déjà devenu une figure familière lors de divers événements\nEh bien, maintenant il rencontrera sa fin rapide et méritée. Vous pouvez avancer, Capitaine. Ne vous mêlez pas des affaires qui ne vous concernent pas. Vous ne faites pas partie de cette guerre... Pas encore... Ou bien êtes-vous ?!";
			if (IsCharacterPerkOn(Pchar, "Trustworthy"))
			{
				notification("Trustworthy", "Trustworthy");
				link.l1 = " (Fiable) Vous voyez, officier... Je suis le Capitaine Charles de Maure, invité de Fadey le Moscovite. Nous avons un certain intérêt pour cet Indien... alors ne nous mêlons pas de nos devoirs respectifs. D'accord, Lieutenant ?";
				link.l1.go = "ZsI_officer_Mir";
			}
			link.l2 = "Attitudes envers les nouveaux venus, attitudes envers les indigènes... Colons, indigènes... Je ne comprends pas encore bien tout cela, mais en ce moment, Lieutenant, la comparaison ne vous est pas favorable... En garde!";
			link.l2.go = "ZsI_officer_Draka";
			link.l3 = "Tu as raison, Lieutenant, je ne le suis pas. Adieu.";
			link.l3.go = "ZsI_officerKIll";
			StartBattleLandInterface();
		break;
		
		case "ZsI_officer_Mir":
			dialog.text = "Ahem! Compris, Capitaine. Je vous prie de transmettre mes salutations à Monsieur Fadey. Escouade, reprenez la patrouille !";
			link.l1 = "";
			link.l1.go = "ZsI_officer_Mir_2";
		break;
		
		case "ZsI_officer_Mir_2":
			DialogExit();
			
			DeleteAttribute(pchar, "questTemp.CameraDialogMode");
			sld = CharacterFromID("ZsI_Patrul_off");
			LAi_SetActorType(sld);
			sld.lifeday = 0;
			LAi_SetImmortal(sld, true);
			LAi_ActorGoToLocation(sld, "reload", "reload4", "none", "", "", "", -1);
			
			for (i=1; i<=2; i++)
			{
				sld = CharacterFromID("ZsI_Patrul_"+i);
				LAi_SetActorType(sld);
				sld.lifeday = 0;
				LAi_SetImmortal(sld, true);
				LAi_ActorGoToLocation(sld, "reload", "reload4", "none", "", "", "", -1);
			}
			sld = CharacterFromID("ListKakao");
			sld.dialog.filename = "Quest\Sharlie\OtherNPC.c";
			sld.dialog.currentnode = "ZsI_MirFinal";
			LAi_SetActorType(sld);
			LAi_SetActorType(pchar);
			SetActorDialogAny2Pchar(sld.id, "", 0.0, 0.0);
			LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", 2.0);
			LAi_ActorFollow(sld, pchar, "ActorDialog_Any2Pchar", 2.0);
			
			AddCharacterExpToSkill(pchar, "Leadership", 30);
			AddCharacterExpToSkill(pchar, "Fortune", 30);
		break;
		
		case "ZsI_MirFinal":
			dialog.text = "Oh là là !";
			link.l1 = "Ouais, eh bien, même moi je suis surpris que ça ait marché. Voici vos marchandises, Feuille de Cacao.";
			link.l1.go = "ZsI_MirFinal_2";
		break;
		
		case "ZsI_MirFinal_2":
			dialog.text = "Le Fils de la Mer parle bien. Sauver un Indien, c'est une grande affaire ! Grosse récompense !";
			link.l1 = "Wow, c'est tout un butin... Et une pierre avec un trou dedans, et une sorte d'amulette.";
			link.l1.go = "ZsI_MirFinal_3";
			AddItems(pchar, "jewelry53", 180);
			AddItems(pchar, "cannabis1", 3);
			GiveItem2Character(pchar, "indian_10");
			GiveItem2Character(pchar, "talisman11");
			Log_Info("You have received 180 small pearls");
			Log_info("You have received Amulet 'Cascavella'}");
			Log_info("You have received Ward 'Adder stone'");
			Log_info("You have received 3 Datura herbs");
			PlaySound("Interface\important_item.wav");
		break;
		
		case "ZsI_MirFinal_3":
			dialog.text = "Le Fils de la Mer a-t-il un mousquet ? Paye un prix élevé pour un mousquet !";
			link.l1 = "Non, mais un canon de mon navire fera-t-il l'affaire ? Pars maintenant, Feuille de Cacao, avant qu'on ne soit repérés et arrêtés.";
			link.l1.go = "ZsI_MirFinal_4";
		break;
		
		case "ZsI_MirFinal_4":
			dialog.text = "Bonne affaire ! Fils de la mer, si tu entres dans la selva, prends une arme à feu. Rencontre un Indien, fais un marché.";
			link.l1 = "Je m'en souviendrai. Adieu, Feuille de Cacao.";
			link.l1.go = "ZsI_MirFinal_5";
		break;
		
		case "ZsI_MirFinal_5":
			DialogExit();
			
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			npchar.lifeday = 0;
			LAi_LocationFightDisable(&Locations[FindLocation("BasTer_ExitTown")], false);
			LAi_SetPlayerType(pchar);
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
		break;
		
		case "ZsI_officer_Draka":
			DialogExit();
			
			DeleteAttribute(pchar, "questTemp.CameraDialogMode");
			LAi_LocationFightDisable(&Locations[FindLocation("BasTer_ExitTown")], false);
			LAi_SetFightMode(pchar, true);
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			ChangeCharacterComplexReputation(pchar, "authority", -2);	
			ChangeIndianRelation(5.0);
			ChangeCharacterNationReputation(pchar, FRANCE, -10);
			sld = CharacterFromID("ListKakao");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			LAi_SetImmortal(sld, false);
			for (i=1; i<=2; i++)
			{
				sld = CharacterFromID("ZsI_Patrul_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			sld = CharacterFromID("ZsI_Patrul_off");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "ZsI_officer_Draka_3");
		break;
		
		case "ZsI_Final":
			ChangeIndianRelation(5.0);
			dialog.text = "Eh bien! Mauvaise décision, Fils de la Mer. Pourquoi ferais-tu cela?";
			link.l1 = "Ugh... Il y a cinq minutes, ça semblait juste... Maintenant je n'en suis plus si sûr.... J'ai quand même tué les miens. Que suis-je censé faire maintenant ? Et s'ils le découvrent ? Merde ! Merde !";
			link.l1.go = "ZsI_Final_2";
		break;
		
		case "ZsI_Final_2":
			dialog.text = "Maintenant, il y aura un raid. Les soldats tuent tout le monde. Deux patrouilles à ne pas pardonner. Feuille de cacao en fuite. Et toi, Fils de la Mer... pourquoi. Feuille de cacao mourra de toute façon. Les esprits le veulent ainsi.";
			link.l1 = "Oh...  Notre accord tient-il toujours ?";
			link.l1.go = "ZsI_Final_3";
		break;
		
		case "ZsI_Final_3":
			dialog.text = "Mauvaise décision, Fils de la Mer. Mais merci. Grande récompense.";
			link.l1 = "Pas si grand, tout bien considéré...";
			link.l1.go = "ZsI_Final_4";
			AddItems(pchar, "jewelry53", 180);
			AddItems(pchar, "cannabis1", 3);
			GiveItem2Character(pchar, "indian_10");
			GiveItem2Character(pchar, "talisman11");
			Log_Info("You have received 180 small pearls");
			Log_info("You have received Amulet 'Cascavella'}");
			Log_info("You have received Ward 'Adder stone'");
			Log_info("You have received 3 Datura herbs");
			PlaySound("Interface\important_item.wav");
		break;
		
		case "ZsI_Final_4":
			dialog.text = "Fils de la Mer, si tu survis et ensuite vas dans la selva, prends une arme à feu. Rencontre un Indien, sois un marché.";
			link.l1 = "Je garderai cela à l'esprit pour l'avenir. Adieu, Feuille de Cacao.";
			link.l1.go = "ZsI_Final_5";
		break;
		
		case "ZsI_Final_5":
			DialogExit();
			
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			LAi_SetImmortal(npchar, true);
			npchar.lifeday = 0;
		break;
		
		case "ZsI_officerKIll":
			DialogExit();
			
			DeleteAttribute(pchar, "questTemp.CameraDialogMode");
			sld = CharacterFromID("ZsI_Patrul_off");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, CharacterFromID("ListKakao"));
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("ZsI_officerKIll_1", 0.1);
			DoQuestCheckDelay("ZsI_officerKIll_2", 1.3);
			AddItems(pchar, "pistol1", 2);
			AddItems(pchar, "GunPowder", 20);
			AddItems(pchar, "bullet", 20);
		break;
		
		//Торговец Барбье по квесту "Деньги на деревьях"
		case "MOT_Barbie":
			dialog.text = "Salutations, Capitaine Charles de Maure. Mon nom est Charles Barbier. Puis-je avoir un moment de votre temps ?";
			link.l1 = "Capitaine de Maure... En effet, c'est moi ! Continuez, Monsieur Barbier.";
			link.l1.go = "MOT_Barbie_2";
		break;
		
		case "MOT_Barbie_2":
			dialog.text = " Toujours un plaisir de rencontrer un collègue, surtout un avec qui je partage un nom ! J'ai une proposition pour vous, Capitaine. Vous voyez, j'ai besoin d'une escorte jusqu'à Saint-Pierre, et...";
			link.l1 = "Je connais St. Pierre ! Mais ce n'est qu'un voyage de deux jours ! Et je dois avouer que je suis encore assez novice pour le rôle d'escorte. Je n'ai pris le commandement de ce navire que depuis une semaine.";
			link.l1.go = "MOT_Barbie_3";
		break;
		
		case "MOT_Barbie_3":
			dialog.text = "Votre honnêteté est appréciée, Capitaine. Charles, pardonnez mon manque de formalité, mais vous êtes précisément la personne dont j'ai besoin.";
			link.l1 = "Hmm... Je me souviens d'une proposition similaire il n'y a pas longtemps. Cela a mené à une embuscade de pirates près de Le Francois.";
			link.l1.go = "MOT_Barbie_4";
		break;
		
		case "MOT_Barbie_4":
			dialog.text = "J'ai entendu parler de cet incident, c'est pourquoi je vous ai cherché\nPremièrement, je transporte une cargaison assez précieuse, et il y a toujours des prédateurs qui rôdent. Cependant, votre récent triomphe sur ces pirates près de Le Francois donnera à réfléchir aux canailles là-bas\nDeuxièmement, votre association avec Fadey Muscovite est une forte recommandation.";
			link.l1 = "Un argument convaincant, Monsieur. Et quelle compensation proposez-vous pour cette faveur?";
			link.l1.go = "MOT_Barbie_5";
		break;
		
		case "MOT_Barbie_5":
			dialog.text = "Ce n'est pas une faveur, Capitaine, mais une entreprise mutuellement bénéfique ! Je vous paierai quarante pièces d'or pour m'escorter à St. Pierre en temps voulu.";
			if (IsCharacterPerkOn(Pchar, "Trustworthy"))
			{
				notification("Trustworthy", "Trustworthy");
				link.l1 = "Comme je vais dans la direction opposée, Monsieur, je demanderai un paiement d'avance.";
				link.l1.go = "MOT_Barbie_Torg";
			}
			link.l2 = "Pas une mauvaise proposition - je vais dans cette direction de toute façon. Marché conclu !";
			link.l2.go = "MOT_Barbie_Soglasen";
			link.l3 = "Une cargaison précieuse, dites-vous ? Malheureusement, Monsieur, j'ai eu ma dose d'aventures pour l'instant.";
			link.l3.go = "MOT_Barbie_Otkaz";
		break;
		
		case "MOT_Barbie_Torg":
			dialog.text = "Difficile de refuser un jeune homme aussi sérieux, Capitaine. Voici vos quarante doublons. Devons-nous lever l'ancre sans tarder ? Le temps, c'est de l'argent.";
			link.l1 = "Nous ne tarderons pas, Monsieur. Nous mettrons voile sous peu.";
			link.l1.go = "MOT_Barbie_Escadra";
			
			AddItems(pchar, "gold_dublon", 40);
			Log_info("You've received 40 doubloons");
			PlaySound("Interface\important_item.wav");
			AddCharacterExpToSkill(pchar, "Leadership", 20);
			AddCharacterExpToSkill(pchar, "Commerce", 20);
		break;
		
		case "MOT_Barbie_Soglasen":
			dialog.text = "Excellent ! Je me prépare pour le départ immédiatement !";
			link.l3 = "Bonjour, mon ami.";
			link.l3.go = "MOT_Barbie_Escadra";
		break;
		
		case "MOT_Barbie_Otkaz":
			dialog.text = "Je comprends, Capitaine. Je ne m'imposerai pas. Adieu, et bonne journée.";
			link.l3 = "Bonjour, mon ami.";
			link.l3.go = "MOT_Barbie_Otkaz_2";
		break;
		
		case "MOT_Barbie_Otkaz_2":
			DialogExit();
			
			LAi_SetActorType(npchar);
			npchar.lifeday = 0;
			LAi_ActorRunToLocation(npchar, "reload", "reload6_back", "none", "", "", "", -1);
			
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
		break;
		
		case "MOT_Barbie_Escadra":
			DialogExit();
			
			SetQuestHeader("MoneyOnTrees");
			AddQuestRecord("MoneyOnTrees", "1");
			
			FantomMakeCoolSailor(npchar, SHIP_BARKENTINE, "Charles", CANNON_TYPE_CANNON_LBS3, 40, 33, 20);
			npchar.Ship.Mode = "trade";
			SetCharacterRemovable(npchar, false);
			SetCompanionIndex(pchar, -1, sti(npchar.index));
			npchar.CompanionEnemyEnable = true;
			SetCrewQuantity(npchar, 35);
			SetCharacterGoods(npchar, GOOD_ROPES, 30);
			LAi_SetImmortal(npchar, false);
			
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "", "", "", "", -1);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			SetTimerCondition("MOT_ZadanieProvaleno", 0, 0, 14, false);
			PChar.quest.MOT_Zahvatili.win_condition.l1 = "NPC_Death";
			PChar.quest.MOT_Zahvatili.win_condition.l1.character = "SharlieBarbie";
			PChar.quest.MOT_Zahvatili.win_condition = "MOT_Zahvatili";
			PChar.quest.MOT_Dostavili.win_condition.l1 = "location";
			PChar.quest.MOT_Dostavili.win_condition.l1.location = "FortFrance_town";
			PChar.quest.MOT_Dostavili.win_condition = "MOT_Dostavili";
		break;
		
		case "MOT_Barbie_101":
			if (IsCharacterPerkOn(Pchar, "Trustworthy"))
			{
				dialog.text = "Je vous remercie pour votre escorte exemplaire, Capitaine. Je suis ravi que nous n'ayons rencontré aucun incident.";
				link.l1 = "Un plaisir de faire affaire avec vous, Monsieur. Maintenant, si vous voulez bien m'excuser, j'ai beaucoup à faire.";
			}
			else
			{	
				dialog.text = "Je vous remercie pour votre escorte exemplaire, Capitaine. Je suis ravi que nous n'ayons rencontré aucun incident. Voici votre paiement - quarante doublons en entier.";
				link.l1 = "Un plaisir de faire affaire avec vous, Monsieur. Maintenant, si vous voulez bien m'excuser, j'ai beaucoup à faire.";
				AddItems(pchar, "gold_dublon", 40);
				Log_info("You've received 40 doubloons");
				PlaySound("Interface\important_item.wav");
			}
			link.l1.go = "MOT_Barbie_102";
		break;
		
		case "MOT_Barbie_102":
			dialog.text = "Charles...";
			link.l1 = "Oui, Charles ? Tu sembles préoccupé. Y a-t-il quelque chose qui ne va pas ?";
			link.l1.go = "MOT_Barbie_103";
			RemoveCharacterCompanion(pchar, npchar);
			npchar.lifeday = 0;
		break;
		
		case "MOT_Barbie_103":
			dialog.text = "Eh bien, puisque vous êtes une personne fiable et que vous connaissez Fadey... Écoutez, le commerce est une affaire risquée, n'est-ce pas ?";
			link.l1 = "Si tu le dis.";
			link.l1.go = "MOT_Barbie_104";
		break;
		
		case "MOT_Barbie_104":
			dialog.text = "J'ai réussi à acquérir un lot de cordages à bon marché en Guadeloupe de... tu sais. J'avais l'intention de les vendre rapidement à St. Pierre et d'utiliser le produit pour acheter du café à revendre à Willemstad. Cela semblait être un plan judicieux.";
			link.l1 = "Je ne remets pas en cause votre intégrité, Monsieur, mais tout cela semble plutôt douteux. Vous parlez de votre cargaison comme si c'était de l'or. Pendant ce temps, mon navire est rempli de ces cordages et ils ne valent presque rien.";
			link.l1.go = "MOT_Barbie_106";
		break;
		
		case "MOT_Barbie_106":
			dialog.text = "Charles, ces cordages sont de la plus haute qualité, fabriqués à partir du meilleur chanvre et tissés dans les manufactures du Tsar de Moscou. Ils servent des objectifs stratégiques et sont utilisés dans le gréement des navires de guerre. Les Anglais monopolisent les routes commerciales avec la Moscovie, interdisant le commerce libre de tels cordages. Les autres nations rivalisent intensément pour s'assurer l'intégralité de l'approvisionnement disponible pour leurs chantiers navals en Europe également.";
			link.l1 = "Alors, c'est ça la contrebande ?";
			link.l1.go = "MOT_Barbie_107";
		break;
		
		case "MOT_Barbie_107":
			dialog.text = "Yes. Unfortunately, I had a falling out with Santiago smugglers last year. I had nearly forgotten about it, but these individuals maintain close connections and long memories. Here's a piece of advice: avoid incensing them and reneging on deals; it's a situation you won't rectify later.";
			link.l1 = "Merci, mais la contrebande ne m'intéresse pas.";
			link.l1.go = "MOT_Barbie_108";
		break;
		
		case "MOT_Barbie_108":
			dialog.text = "Quel dommage ! Un commerce honnête peut vous rapporter un joli bénéfice, mais vous n'amasserez jamais une richesse substantielle. Néanmoins, je n'ai pas engagé cette conversation plutôt précaire avec vous sans raison. Je vous propose d'acheter une cargaison de cordages auprès de moi. Les contrebandiers locaux fréquentent la taverne et seront des acheteurs avides pour ce chargement. Pensez-y ! Vous récolterez un profit considérable aujourd'hui sans même vous aventurer en haute mer.";
			link.l1 = "Combien demandez-vous pour la cargaison ?";
			link.l1.go = "MOT_Barbie_109";
		break;
		
		case "MOT_Barbie_109":
			dialog.text = "Dix mille pesos. C'est une somme modeste, et revendre les cordages aux contrebandiers rapportera des bénéfices considérables.";
			if (sti(pchar.Money) >= 10000)
			{
				link.l1 = "Je ne me pardonnerais jamais si je laissais passer une occasion pareille. Prends l'argent et assure-toi que les marchandises soient livrées promptement à mon navire.";
				link.l1.go = "MOT_Barbie_ContraSoglasen";
			}
			if (sti(pchar.Money) >= 7000)
			{
				link.l2 = "C'est une entreprise précaire, mon ami. Rencontrons-nous à mi-chemin, d'accord ? J'accepterai vos cordages pour sept mille.";
				link.l2.go = "MOT_Barbie_ContraTorg";
			}
			link.l3 = "C'est une somme considérable, Monsieur. Je compatis à votre situation, mais je ne peux accepter un tel risque.";
			link.l3.go = "MOT_Barbie_ContraOtkaz";
		break;
		
		case "MOT_Barbie_ContraSoglasen":
			dialog.text = "Ma gratitude, Charles ! Vous m'avez épargné de la ruine financière ! Les marchandises seront expédiées rapidement et avec la plus grande prudence\nPermettez-moi de vous offrir un conseil en tant que confrère marchand : une fois que vous avez engagé un bon intendant, procurez-vous du café à Saint-Pierre et vendez-le avec profit à Willemstad. Les capitales locales paient généreusement pour les biens coloniaux, les exportant en Europe pour des bénéfices substantiels. Bonne chance dans vos entreprises, ami !";
			link.l1 = "Adieu, Monsieur.";
			link.l1.go = "MOT_Barbie_ContraSoglasen_2";
			AddCharacterGoodsSimple(pchar, GOOD_ROPES, 30);
			AddMoneyToCharacter(pchar, -10000);
			Log_info("You've received 30 ropes");
			PlaySound("Interface\important_item.wav");
		break;
		
		case "MOT_Barbie_ContraSoglasen_2":
			DialogExit();
			
			AddQuestRecord("MoneyOnTrees", "5");
			CloseQuestHeader("MoneyOnTrees");
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			
			sld = CharacterFromID("SharlieBarbie");
			sld.lifeday = 0;
			LAi_SetCitizenType(sld);
			LAi_CharacterDisableDialog(sld);
			
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
		break;
		
		case "MOT_Barbie_ContraTorg":
			if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) > 30)
			{
				notification("Skill Check Passed", SKILL_COMMERCE);
				dialog.text = "Ma gratitude, Charles ! Vous m'avez épargné de la ruine financière ! Les marchandises seront expédiées rapidement et avec la plus grande prudence\nPermettez-moi de vous offrir un conseil en tant que confrère marchand : une fois que vous aurez engagé un intendant compétent, procurez-vous du café à Saint-Pierre et vendez-le à profit à Willemstad. Les capitaux locaux paient généreusement pour les marchandises coloniales, les exportant vers l'Europe pour des profits substantiels. Bonne chance dans vos entreprises, ami !";
				link.l1 = "Adieu, Monsieur.";
				link.l1.go = "MOT_Barbie_ContraSoglasen_2";
				AddCharacterGoodsSimple(pchar, GOOD_ROPES, 30);
				AddMoneyToCharacter(pchar, -7000);
				Log_info("You've received 30 ropes");
				PlaySound("Interface\important_item.wav");
			}
			else
			{
				notification("Skill Check Failed (31)", SKILL_COMMERCE); 
				dialog.text = "Je ne peux pas, Capitaine. Ma marchandise est sérieuse et mérite un traitement sérieux. La plupart des capitaines libres n'osent pas commercer en biens stratégiques. Malheureusement, marchander est ici injustifié.";
				if (sti(pchar.Money) >= 10000)
				{
					link.l1 = "Je ne me le pardonnerais jamais si je laissais passer une occasion comme celle-ci. Prends l'argent et assure-toi que les marchandises soient livrées promptement à mon navire.";
					link.l1.go = "MOT_Barbie_ContraSoglasen";
				}
				link.l2 = "C'est une somme considérable, Monsieur. Je compatis à votre situation, mais je ne peux accepter un tel risque.";
				link.l2.go = "MOT_Barbie_ContraOtkaz";
			}
		break;
		
		case "MOT_Barbie_ContraOtkaz":
			dialog.text = "Quel dommage ! Adieu, Capitaine.";
			link.l1 = "";
			link.l1.go = "MOT_Barbie_ContraOtkaz_2";
		break;
		
		case "MOT_Barbie_ContraOtkaz_2":
			DialogExit();
			
			AddQuestRecord("MoneyOnTrees", "4");
			CloseQuestHeader("MoneyOnTrees");
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			
			sld = CharacterFromID("SharlieBarbie");
			sld.lifeday = 0;
			LAi_SetCitizenType(sld);
			LAi_CharacterDisableDialog(sld);
			
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
		break;
		
		//Миниквест "Делюк"
		//Матрос Алонсо
		case "Del_Alonso":
			dialog.text = "Problème, capitaine.";
			link.l1 = "Eh bien ?";
			link.l1.go = "Del_Alonso_2";
		break;
		
		case "Del_Alonso_2":
			dialog.text = "Notre navigateur a été arrêté et emmené dans les cachots locaux. Une histoire de dettes, disent-ils.";
			link.l1 = "Quoi, encore ?!";
			link.l1.go = "Del_Alonso_3";
		break;
		
		case "Del_Alonso_3":
			dialog.text = "C'est un sacré fripon, Capitaine.";
			link.l1 = "Quel terrible timing ! Sans navigateur, nous sommes coincés ici. Je vais devoir le tirer d'affaire encore une fois ! Je parlerai au commandant...";
			link.l1.go = "Del_Alonso_4";
		break;
		
		case "Del_Alonso_4":
			dialog.text = "Permission de parler, Capitaine ?";
			link.l1 = "Allez-y.";
			link.l1.go = "Del_Alonso_5";
		break;
		
		case "Del_Alonso_5":
			dialog.text = "Pourquoi se donner tant de mal ? Un homme comme lui n'apportera que des ennuis au navire.";
			link.l1 = "Ai-je le choix ? Il n'y a guère d'autres navigateurs disponibles, donc mes options sont plutôt limitées.";
			link.l1.go = "Del_Alonso_6";
		break;
		
		case "Del_Alonso_6":
			dialog.text = "Vrai, un navigateur de premier ordre est difficile à trouver, mais tu n'as pas encore besoin d'un maître, juste d'un compétent. Ta situation a changé la semaine dernière, tu sais ça, n'est-ce pas ? Plus besoin de racler le fond du tonneau pour trouver des hommes pour ton équipage. Les gens parlent maintenant de comment tu as vaincu ce pirate et des relations que tu as. L'équipage est derrière toi aussi, Capitaine, nous t'aimons bien.";
			link.l1 = "C'est rassurant, Alonso. Et que pense l'équipage de Deluc ?";
			link.l1.go = "Del_Alonso_7";
		break;
		
		case "Del_Alonso_7":
			dialog.text = "Vous apprenez vite, capitaine. L’équipage dit que, même s’il est un bon officier et nous traite bien, il n’en vaut pas la peine. Un grand marchand vient de renvoyer ses officiers – essayez la taverne, vous y trouverez sûrement la bonne personne. Et oubliez Deluc ; c’est l’avis des hommes.";
			link.l1 = "Merci pour le conseil, Alonso. Je savais que je pouvais compter sur toi. Retourne au navire et prends la veille pendant que je règle ça.";
			link.l1.go = "Del_Alonso_8";
		break;
		
		case "Del_Alonso_8":
			dialog.text = "À vos ordres !";
			link.l1 = "...";
			link.l1.go = "Del_Alonso_9";
		break;
		
		case "Del_Alonso_9":
			DialogExit();
			SetQuestHeader("FolkeDeluc");
			AddQuestRecord("FolkeDeluc", "1");
			
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			SetFunctionLocationCondition("FortfranceJailOff_AddQuestMark", "fortfrance_prison", false);
			QuestCloseSeaExit();
			sld = CharacterFromID("Folke");
			sld.Dialog.Filename = "Quest\Sharlie\OtherNPC.c";
			sld.dialog.currentnode = "Del_Folke_1";
			RemovePassenger(pchar, sld);
			LAi_SetStayType(sld);
			ChangeCharacterAddressGroup(sld, "FortFrance_prison", "goto", "goto9");
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			pchar.questTemp.Del_Deluck = true;
			
			sld = GetCharacter(NPC_GenerateCharacter("Del_shturman", "mercen_4", "man", "man", 5, FRANCE, 3, false, "quest"));
			GiveItem2Character(sld, "blade_03");
			EquipCharacterByItem(sld, "blade_03");
			sld.Dialog.Filename = "Quest\Sharlie\OtherNPC.c";
			sld.dialog.currentnode = "Del_shturman";
			LAi_SetSitType(sld);
			sld.greeting = "officer_hire";
			SetSelfSkill(sld, 21, 23, 18, 33, 25);
			SetShipSkill(sld, 25, 10, 8, 6, 35, 11, 13, 25, 14);
			SetSPECIAL(sld, 7, 10, 6, 8, 7, 8, 4);
			sld.rank = 5;
			SetCharacterPerk(sld, "ShipSpeedUp");
			SetCharacterPerk(sld, "HullDamageUp");
			SetCharacterPerk(sld, "BasicDefense");
			//sld.quest.officertype = "navigator";
			FreeSitLocator("FortFrance_tavern", "sit4");
			ChangeCharacterAddressGroup(sld, "FortFrance_tavern", "sit", "sit4");
			AddLandQuestMark(characterFromId("Del_shturman"), "questmarkmain");
		break;
		
		//Делюк
		case "Del_Folke_1":
			DelLandQuestMark(npchar);
			dialog.text = "Capitaine...";
			link.l1 = "J'ai un million de questions, mais je poserai juste celle-ci : comment as-tu réussi à accumuler de nouvelles dettes alors que tu étais avec moi tout ce temps, à m'enseigner la navigation !";
			link.l1.go = "Del_Folke_2";
		break;
		
		case "Del_Folke_2":
			dialog.text = "J'ai honte de l'admettre, Capitaine, mais j'ai emprunté à divers prêteurs bien avant de rejoindre votre équipage. Mon plan était de me faire discret et de travailler sur votre navire jusqu'à ce que je gagne assez pour rembourser toutes mes dettes. Mais j'ai fait l'erreur de quitter le navire ici pour m'impliquer avec une certaine femme ici à St. Pierre, et les soldats m'ont attrapé juste sous son nez. Je n'ai contracté aucune nouvelle dette en Martinique, puisque vous avez payé ma dernière, je le jure !";
			link.l1 = "Vous êtes un imbécile, Deluc, et vous m'avez fait devenir la risée de St. Pierre!";
			link.l1.go = "Del_Folke_3a";
			link.l2 = "Impressionnant, Folke. Merci pour l'anecdote.";
			link.l2.go = "Del_Folke_3b";
		break;
		
		case "Del_Folke_3a":
			AddComplexSelfExpToScill(10, 10, 10, 10);
			dialog.text = "Que ferez-vous, Capitaine ? Pouvez-vous encore me tirer d'affaire ? Trouver un nouveau navigateur ne sera pas facile, vous savez...";
			link.l1 = "Restez ici pour l'instant. Je prendrai une décision. Je pourrais rendre visite au banquier à nouveau.";
			link.l1.go = "Del_Folke_4";
		break;
		
		case "Del_Folke_3b":
			AddCharacterExpToSkill(pchar, "Sailing", 10);//навигация
			AddCharacterExpToSkill(pchar, "Commerce", 10);//торговля
			dialog.text = "Que ferez-vous, Capitaine? Pouvez-vous encore me tirer d'affaire? Trouver un nouveau navigateur ne sera pas facile, vous savez...";
			link.l1 = "Reste ici pour l'instant. Je vais prendre une décision. Je pourrais rendre visite au banquier à nouveau.";
			link.l1.go = "Del_Folke_4";
		break;
		
		case "Del_Folke_4":
			dialog.text = "Ce n'est pas comme si j'avais un endroit où aller...";
			link.l1 = "... ";
			link.l1.go = "Del_Folke_5";
		break;
		
		case "Del_Folke_5":
			DialogExit();
			
			pchar.questTemp.Del_Rostovshik = true;
			LAi_CharacterDisableDialog(npchar);
			AddLandQuestMark(characterFromId("FortFrance_usurer"), "questmarkmain");
		break;
		
		case "Del_Folke_10":
			dialog.text = "Capitaine, merci. Vous avez réglé mes dettes, mais maintenant je vous dois une dette encore plus grande - ma vie. Et je vous en suis vraiment reconnaissant ! Je vous assure, vous ne trouverez pas d'homme plus loyal nulle part dans ce monde !";
			link.l1 = "Je suppose que certaines dettes ne peuvent être remboursées qu'en en contractant d'autres. Retournons au travail, Folke. Il y a fort à faire en mer.";
			link.l1.go = "Del_Folke_11a";
			link.l2 = "N'oublie pas cela, Deluc. La prochaine fois, je te tirerai dessus.";
			link.l2.go = "Del_Folke_11b";
			
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			QuestOpenSeaExit()
			sld = CharacterFromID("Del_shturman");
			sld.lifeday = 0;
			
			sld = CharacterFromID("Del_Ohranik");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload3", "none", "", "", "", -1);
		break;
		
		case "Del_Folke_11a":
			AddCharacterExpToSkill(pchar, "Sailing", 10);//навигация
			AddCharacterExpToSkill(pchar, "Commerce", 10);//торговля
			dialog.text = "Oui, oui, Capitaine !";
			link.l1 = "...";
			link.l1.go = "Del_Folke_12";
		break;
		
		case "Del_Folke_11b":
			AddComplexSelfExpToScill(10, 10, 10, 10);
			dialog.text = "Oui, capitaine !";
			link.l1 = "... ";
			link.l1.go = "Del_Folke_12";
		break;
		
		case "Del_Folke_12":
			DialogExit();
			EndQuestMovie();
			AddQuestRecord("FolkeDeluc", "3");
			CloseQuestHeader("FolkeDeluc");
			
			ChangeCharacterComplexReputation(pchar, "authority", -2);
			AddCrewMorale(Pchar, -30);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "", "", "", "", -1);
			npchar.Dialog.Filename = "Enc_Officer_dialog.c";
			npchar.quest.meeting = true;
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(npchar.id);
			npchar.OfficerWantToGo.DontGo = true;
			npchar.loyality = MAX_LOYALITY;
			AddPassenger(pchar, npchar, false);
			npchar.OfficerImmortal = true;
			npchar.Health.HP       = 60.0; 
			npchar.Health.maxHP    = 60.0;
			SetCharacterPerk(npchar, "ShipEscape");
			npchar.location = "None";
			npchar.Dialog.CurrentNode = "hired";
			npchar.Payment = true;
			SetCharacterPerk(npchar, "ByWorker");
			DeleteAttribute(npchar, "CompanionDisable");
		break;
		
		//Штурман из таверны. Стандартный диалог, но с некоторыми изменениями (обучение найма для новичков)
		case "Del_shturman":
			dialog.text = "Avez-vous besoin d'un officier, capitaine ?";
    		Link.l1 = "Un officier ? Et à quoi es-tu bon ?";
    		Link.l1.go = "Del_Node_2";
			Link.l2 = "Non, j'ai un jeu complet.";
			Link.l2.go = "Exit";
			NextDiag.TempNode = "Del_OnceAgain";
		break;		
		case "Del_Node_2":
			dialog.text = "Je suis le meilleur navigateur de ces eaux. Je m'y connais un peu en médecine. Et je suis prêt à vous rendre service et à vous servir.";
			Link.l1 = "Et combien veux-tu ?";
			Link.l1.go = "Del_price";
			Link.l2 = "Et quel genre de spécialiste es-tu ?";
			Link.l2.go = "Del_ShowParam_exit";
			Link.l3 = "Hélas, j'ai déjà un navigateur.";
			Link.l3.go = "Exit";
		break;		
		case "Del_price":
			dialog.text = "Je pense que nous pouvons nous accorder sur 4000 pesos.";
			Link.l1 = "Est-ce que ce n'est pas un peu trop ?";
			Link.l1.go = "Del_trade";
			Link.l2 = "Je suis d'accord. Considérez-vous comme un membre de l'équipage.";
			Link.l2.go = "Del_hire";
			Link.l3 = "Tu ne vaux pas cet argent.";
			Link.l3.go = "exit";
		break;	
		case "Del_ShowParam_exit":
			NextDiag.TempNode = "Del_OnceAgain";
			NPChar.quest.meeting = true;
			DialogExit();
			
			PChar.SystemInfo.OnlyShowCharacter = true;
            LaunchCharacter(NPChar);
		break;		
		case "Del_OnceAgain":
			NextDiag.TempNode = "Del_OnceAgain";
			dialog.text = "Avez-vous changé d'avis, capitaine ? Décidé qu'un nouveau navigateur ne ferait pas de mal ?";
			// boal -->
			if (FindFreeRandomOfficer() > 0)
			{
                Link.l1 = "Quelque chose comme ça. Combien veux-tu?";
                Link.l1.go = "Del_price";
			}
			Link.l2 = "Et de quoi es-tu capable?";
			Link.l2.go = "Del_ShowParam_exit";
			// boal <--
			Link.l3 = "J'ai un jeu complet. À bientôt.";
			Link.l3.go = "exit";
		break;		
		case "Del_trade":
			if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) > 25)
			{
				dialog.text = "D'accord... Je suppose que je pourrais accepter même 2500 pesos. Qu'en dis-tu ?";
				Link.l1 = "Voilà qui est mieux. Tu es des nôtres.";
				Link.l1.go = "Del_hire";
				pchar.questTemp.Del_SniziliTsenu = true;
			}
			else
			{
				dialog.text = "Je suis désolé, capitaine, mais je vaux exactement ce que j'ai demandé. Si c'est trop pour vous, alors allez trouver quelqu'un d'autre.";
				Link.l1 = "D'accord, je suis d'accord. Je vous emmènerai.";
				Link.l1.go = "Del_hire";				
				Link.l2 = "C'est ce que je vais faire. Adieu.";
				Link.l2.go = "exit";
			}
		break;		
		case "Del_hire":
			if (CheckAttribute(pchar, "questTemp.Del_SniziliTsenu"))
			{
				if (sti(pchar.Money) >= 2500)
				{
					AddMoneyToCharacter(pchar, -2500);
					NextDiag.TempNode = "OnboardSoon";
					dialog.text = "Merci, capitaine. Vous ne regretterez pas votre choix.";
					Link.l1 = "Je l'espère.";
					Link.l1.go = "Del_Exit_hire";
					DeleteAttribute(pchar, "questTemp.Del_SniziliTsenu");
				}
				else
				{
					dialog.text = "Je vois que vous manquez d'argent, capitaine ! Je suis désolé, mais je ne travaille pas à crédit.";
					Link.l1 = "Oh, diable !";
					Link.l1.go = "Exit";								
				}
			}
			else
			{
				if (sti(pchar.Money) >= 4000)
				{
					AddMoneyToCharacter(pchar, -4000);
					NextDiag.TempNode = "Del_OnboardSoon";
					dialog.text = "Merci, capitaine. Vous ne regretterez pas votre choix.";
					Link.l1 = "J'espère bien.";
					Link.l1.go = "Del_Exit_hire";
				}
				else
				{
					dialog.text = "Je vois que vous manquez d'argent, capitaine ! Je suis désolé, mais je ne travaille pas à crédit.";
					Link.l1 = "Oh, diable !";
					Link.l1.go = "Exit";								
				}
			}
		break;
		case "Del_OnboardSoon":			
			NextDiag.TempNode = "Del_OnboardSoon";
			dialog.text = "Je vais juste finir mon verre, capitaine, puis j'irai au navire. Ne t'inquiète pas, je serai là à temps.";
			Link.l1 = "D'accord. Si tu es en retard, je te ferai récurer le pont !";
			Link.l1.go = "Exit";											
		break;
		case "Del_exit_hire":
			npchar.Dialog.Filename = "Enc_Officer_dialog.c";
			npchar.Dialog.CurrentNode = "hired";
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			NPChar.quest.meeting = true;
			npchar.loyality = 18;
			
			ChangeCharacterComplexReputation(pchar, "authority", 2);
			AddCrewMorale(Pchar, 30);
			QuestOpenSeaExit();
			DelLandQuestMark(npchar);
			pchar.quest.FortfranceJailOff_AddQuestMark.over = "yes";
			if (GetCharacterIndex("FortFranceJailOff") != -1)
			{
				DelLandQuestMark(characterFromId("FortFranceJailOff"));
			}
			sld = CharacterFromID("Folke");
			LAi_CharacterDisableDialog(sld);
			DeleteAttribute(pchar, "questTemp.Del_Deluck");
			DeleteAttribute(pchar, "questTemp.Del_DeluckSvoboda");
			DeleteAttribute(pchar, "questTemp.Del_Rostovshik");
			DeleteAttribute(pchar, "questTemp.Del_Rostovshik_repeat");
			pchar.questTemp.Del_DeluckSiditTurma = true;
			AddQuestRecord("FolkeDeluc", "4");
			CloseQuestHeader("FolkeDeluc");
			DialogExit();
		break;
		
		//Квест "Травля крысы"
		//Капитан корабля Хейтер
		case "TK_Kapitan":
			dialog.text = "D'accord, d'accord ! Je me rends, bon sang !";
			link.l1 = "Tu es maintenant mon prisonnier, mais tu te retrouveras bientôt à St. Pierre face à la potence.";
			link.l1.go = "TK_Kapitan_1";
			PChar.quest.TK_Potopil.over = "yes";
		break;
		
		case "TK_Kapitan_1":
			dialog.text = "C'est donc ici... Comment as-tu su où me trouver?";
			link.l1 = "Le Gouverneur m'a personnellement informé de la situation.";
			link.l1.go = "TK_Kapitan_2";
		break;
		
		case "TK_Kapitan_2":
			dialog.text = "Quel salaud ! Il a dû prendre conscience de mes plans et a décidé de m'enculer ouvertement juste devant son repaire pour donner l'exemple à d'autres équipages !";
			link.l1 = "Encore une insulte à son Excellence, et votre voyage à St. Pierre sera rapide et inoubliable.";
			link.l1.go = "TK_Kapitan_3";
		break;
		
		case "TK_Kapitan_3":
			dialog.text = "Eh? Je ne parle pas de votre excellence, mate. Je parle de Jacques le Bonhomme\nBon sang, les rumeurs étaient vraies! Barbazon a compris que je devenais une menace, alors il m'a livré au gouverneur pour m'écarter de son chemin. C'est pourquoi vous aviez ma position exacte - et m'avez attrapé les culottes baissées, ha ha!";
			link.l1 = "Tu es délirant. Le gouverneur de la Martinique ne s'abaisserait pas à traiter avec un chef pirate !";
			link.l1.go = "TK_Kapitan_4";
		break;
		
		case "TK_Kapitan_4":
			dialog.text = "Oui, d'accord. Peut-être pas directement, mais je pense qu'il a conclu un marché avec Barbazon. C'est commode pour lui : un pirate dangereux est pendu, les rapports sont beaux et les 'dépenses pour l'opération militaire' sont justifiées. J'ai servi, vous savez ? Alors je sais comment ça se passe là-bas. Et vous ? Servez-vous dans la garnison ?";
			link.l1 = "Je sers mon pays, et cette conversation est terminée. Bienvenue au cachot.";
			link.l1.go = "TK_Kapitan_5";
		break;
		
		case "TK_Kapitan_5":
			dialog.text = "Attends, mon gars. Je ne suis pas castillan, et je n'étais pas en mer aujourd'hui pour piller les marchands français. J'ai des principes, bon sang ! Faisons un marché, d'accord ?";
			link.l1 = "Tu gaspilles ton souffle, pirate. Dans la cale avec toi.";
			link.l1.go = "TK_Kapitan_7_1";
			link.l2 = "Tu essaies d'échapper à la corde ?";
			link.l2.go = "TK_Kapitan_6";
		break;
		
		case "TK_Kapitan_6":
			dialog.text = "J'avais une piste solide ici, et je te laisserai une part si tu me laisses partir. Ma vie ne vaut que quelques milliers en argent, mais je peux te rapporter bien plus – et sans taxes.";
			if (CheckAttribute(pchar, "questTemp.MOT_SharlyBad"))
			{
				link.l1 = "C'est une offre tentante... Bien que la piraterie ne soit pas exactement mon fort.";
				link.l1.go = "TK_Kapitan_7";
			}
			else
			{
				link.l1 = "Je ne suis pas un pirate !";
				link.l1.go = "TK_Kapitan_7";
			}
		break;
		
		case "TK_Kapitan_7":
			dialog.text = "C'est à toi de décider, camarade. Que tu veuilles être un homme fortuné ou un capitaine sans le sou mais avec des principes. Si tu veux de l'argent réel et la liberté, il faudra toucher à tout un peu. Saisis chaque opportunité.";
			link.l1 = "Vous avez certainement le don des mots...";
			link.l1.go = "TK_Kapitan_8";
			link.l2 = "Hum... Je suppose que je vais vous emmener à Saint-Pierre. Cela semble être la bonne chose à faire.";
			link.l2.go = "TK_Kapitan_7_1";
		break;
		
		case "TK_Kapitan_7_1":
			dialog.text = "Va te faire foutre alors !";
			link.l1 = "...";
			link.l1.go = "TK_Kapitan_Plen";
		break;
		
		case "TK_Kapitan_8":
			dialog.text = "Alors, avons-nous un accord ?";
			link.l1 = "Oui. Dis-moi qui est ton chef, et tu es libre de partir.";
			link.l1.go = "TK_Kapitan_9";
		break;
		
		case "TK_Kapitan_9":
			dialog.text = "Il y a un petit malin d'Anglais du Henry, une barque. Il est sur le point de terminer son petit voyage commercial, transportant des marchandises des plantations françaises à Willemstad pour un joli profit. Il quitte bientôt la Martinique pour Curaçao. C'est un boulot facile - pas d'escorte, et la barque est chargée de valeurs au détriment de ses défenses. Il prend trop de temps, alors des rumeurs commencent à circuler. Mon conseil, camarade ? Ne sois pas timide à la taverne. Quelques verres pour les locaux, et ils dévoileront quelques secrets.";
			link.l1 = "Pourquoi pas d'escorte ?";
			link.l1.go = "TK_Kapitan_10";
		break;
		
		case "TK_Kapitan_10":
			dialog.text = "Comment un Anglais ferait-il autrement pour mener ses affaires discrètement à Curaçao ? C'est la guerre ouverte entre l'Angleterre et les Pays-Bas, et obtenir une licence commerciale est un casse-tête et c'est coûteux.";
			link.l1 = "Mais il n'y a pas de guerre entre la France et l'Angleterre. Quelles sont les conséquences si j'attaque un navire neutre ?";
			link.l1.go = "TK_Kapitan_11";
		break;
		
		case "TK_Kapitan_11":
			dialog.text = "Rien si tu restes discret. L'équipage se vantera certainement de tes exploits au port le plus proche, mais tant que tu ne t'attaques pas régulièrement aux navires anglais ou néerlandais, ça devrait aller. Approche le Henry sous pavillon français. Charge tes canons de mitraille, réduis la distance, lâche le Black, tire quelques volées, et aborde la garce. C'est simple, matelot.";
			link.l1 = "Nous verrons cela. Je tiendrai parole et je te libérerai. Ne me donne pas de raison de le regretter.";
			link.l1.go = "TK_Kapitan_12";
		break;
		
		case "TK_Kapitan_12":
			dialog.text = "Je ne le ferai pas. Bonne chasse, camarade.";
			link.l1 = "... ";
			link.l1.go = "TK_Kapitan_Otpustil";
		break;
		
		case "TK_Kapitan_Plen":
			DialogExit();
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			sld = &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)];
			sld.DontRansackCaptain = true;
			Lai_SetPlayerType(pchar);
			LAi_RemoveCheckMinHP(sld);
			LAi_SetImmortal(sld, true);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			
			sld = GetCharacter(NPC_GenerateCharacter("TK_Heiter2", "mercen_8", "man", "man", sti(PChar.rank), PIRATE, -1, false, "pirate"));
			sld.name = "Daniel";
			sld.lastname = "Montbars";
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, false);
			ChangeCharacterAddressGroup(sld, "My_Deck", "goto", "goto7");
			LAi_SetGroundSitType(sld);
			LAi_CharacterDisableDialog(sld);
			DoQuestCheckDelay("TK_KapitanSidit_1", 0.8);
		break;
		
		case "TK_Kapitan_Otpustil":
			DialogExit();
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			sld = &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)];
			Lai_SetPlayerType(pchar);
			LAi_RemoveCheckMinHP(sld);
			LAi_SetImmortal(sld, true);
			sld.ShipEnemyDisable  = true;
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			LAi_SetCitizenType(sld);
			sld.lifeday = 0;
			LAi_EnableReload();
			Log_SetActiveAction("Reload");
			pchar.questTemp.TK_Otpustil = true;
			AddQuestRecord("TravlyaKrys", "4");
			
			SetTimerCondition("TK_GenrihSpawn", 0, 0, 1, false);	
		break;
		
		//Диего и Гийом за столиком по квесту "Встреча с Диего"
		case "VsD_DiegoAndErnat":
			dialog.text = "... Je m'occuperai de tes problèmes de jeu. Hé ! Ressaisis-toi, homme ! Soit tu te reprends, soit je te secoue pour te faire entendre raison moi-même.";
			link.l1 = "";
			link.l1.go = "VsD_DiegoAndErnat_2";
			sld = CharacterFromID("GiumDyubua");
			LAi_CharacterEnableDialog(sld);
		break;
		
		case "VsD_DiegoAndErnat_2":
			DialogExit();
			StartInstantDialogNoType("GiumDyubua", "VsD_DiegoAndErnat_3", "Quest\Sharlie\OtherNPC.c");
		break;
		
		case "VsD_DiegoAndErnat_3":
			dialog.text = "Monsieur, mes excuses, mais vous êtes un peu gênant.";
			link.l1 = "Oui, bien sûr. Passez une agréable journée, messieurs.";
			link.l1.go = "VsD_DiegoAndErnat_4";
		break;
		
		case "VsD_DiegoAndErnat_4":
			DialogExit();
			sld = CharacterFromID("Diego");
			LAi_CharacterDisableDialog(sld);
			sld = CharacterFromID("GiumDyubua");
			LAi_CharacterDisableDialog(sld);
		break;
		
		//Гийом Дюбуа по квесту "Встреча с Диего"
		case "VsD_GiumDyubua":
			dialog.text = "Capitaine de Maure ! Attendez !";
			link.l1 = "Oui, Lieutenant ?";
			link.l1.go = "VsD_GiumDyubua_2";
			DelLandQuestMark(npchar);
		break;
		
		case "VsD_GiumDyubua_2":
			dialog.text = "J'ai à peine réussi à te suivre. Il y a eu... un petit contretemps, Capitaine. Quel bazar !";
			link.l1 = "Respire et calme-toi, je te prie.";
			link.l1.go = "VsD_GiumDyubua_3";
		break;
		
		case "VsD_GiumDyubua_3":
			dialog.text = "D'accord, d'accord. Écoute, après avoir chargé les canons, y a-t-il encore de la place dans la cale ?";
			link.l1 = "Je suis encore novice en la matière, donc pas entièrement sûr, mais je suppose qu'il devrait y en avoir.";
			link.l1.go = "VsD_GiumDyubua_4";
		break;
		
		case "VsD_GiumDyubua_4":
			dialog.text = "Excellent ! Le Commandement veut soutenir l'opération à Porto Bello par tous les moyens possibles, alors ils ont ordonné la livraison de deux cents mesures supplémentaires de poudre à canon au Belliqueux. Cela peut ne pas sembler beaucoup, mais quelques salves supplémentaires pourraient renverser le cours de la bataille !";
			link.l1 = "Très bien, Lieutenant. Je suis prêt à faire ma part. Chargez la poudre - cela ne me dérange pas du tout.";
			link.l1.go = "VsD_GiumDyubua_5";
		break;
		
		case "VsD_GiumDyubua_5":
			dialog.text = "Merci, Capitaine. Je vais informer notre équipe de chargement immédiatement. Heureusement, ils n'ont pas encore terminé avec le '"+PChar.Ship.Name+"   pas encore. Bonne chance pour ta mission !";
			link.l1 = "Merci, bien que ça ait été assez chaotique jusqu'à présent. Adieu, Lieutenant.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("VsD_GoToCity");
		break;
		
		//Фульк или Алонсо по квесту "Встреча с Диего"
		case "VsD_FolkeAlonso":
			dialog.text = "Jésus, Capitaine! Grâce au ciel, vous êtes indemne!";
			link.l1 = "Que diable s'est-il passé ?! Qu'est-il arrivé à mon navire ?!";
			link.l1.go = "VsD_FolkeAlonso_2";
		break;
		
		case "VsD_FolkeAlonso_2":
			dialog.text = "Je ne sais pas, Capitaine ! Je disais juste adieu à une femme du coin que j'ai rencontrée récemment... Oh merde ! Eugénie !";
			link.l1 = "Elle est morte, "+npchar.name+"Désolé, mais nous devons nous concentrer et voir si un de nos équipage est blessé.";
			link.l1.go = "VsD_FolkeAlonso_3";
		break;
		
		case "VsD_FolkeAlonso_3":
			dialog.text = "Nous nous connaissions à peine... Aaah ! Merde ! Rapport, Capitaine : la plupart de l'équipage était à terre quand l'explosion a eu lieu - heureusement. Les gars profitaient d'une permission à terre avant notre prochain grand voyage. Mais la vigie du navire... Je crains qu'il n'y ait pas de survivants. Regardez autour ! Les débris ont blessé ou tué des gens même ici, sur ce quai ! C'est un miracle que nous soyons indemnes, nous deux.";
			link.l1 = "Qu'en est-il du navire ? Est-elle en bon état ?!";
			link.l1.go = "VsD_FolkeAlonso_4";
		break;
		
		case "VsD_FolkeAlonso_4":
			dialog.text = "Est-elle?! Mes excuses, Capitaine. Difficile à dire avec certitude, mais il semble que l'explosion ait eu lieu sur le pont supérieur, pas en dessous. Je ne vois pas de feux actifs, et il semble que nous ayons échappé à des dommages majeurs.";
			link.l1 = "...";
			link.l1.go = "VsD_FolkeAlonso_5";
			sld = GetCharacter(CreateCharacterClone(CharacterFromID("PortPaxAmmoOff"), 0));
			sld.id = "PortPaxAmmoOff_clone";
			LAi_LoginInCaptureTown(sld, true);
			ChangeCharacterAddressGroup(sld, "PortPax_town", "quest", "quest1");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
		break;
		
		case "VsD_FolkeAlonso_5":
			DialogExit();
			LAi_SetStayType(pchar);
			sld = CharacterFromID("PortPaxAmmoOff_clone");
			sld.dialog.filename = "Quest\Sharlie\OtherNPC.c";
			sld.dialog.currentnode = "VsD_Komendant";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 3, 0);
		break;
		
		case "VsD_Komendant":
			dialog.text = "Que diable, Capitaine?!";
			link.l1 = "Je me pose la même question, Colonel !";
			link.l1.go = "VsD_Komendant_1";
			sld = CharacterFromID("Tichingitu");
			if (sld.location == pchar.location && !LAi_IsDead(sld))
			{
				LAi_SetActorType(sld);
				LAi_ActorGoToLocator(sld, "reload", "reload1", "", -1);
			}
		break;
		
		case "VsD_Komendant_1":
			dialog.text = "Surveillez-vous, de Maure ! Vous avez accepté ce travail de la Marine, vous avez pris des canons lourds - propriété de la Couronne, d'une importance stratégique ! Comprenez-vous l'importance de ces canons pour toute l'opération ?! Votre négligence a mis en péril presque quatre cents hommes et un navire de guerre français ! Vous risquez un procès pour trahison ici !";
			link.l1 = "Calmez-vous, Colonel ! Par miracle, il semble que mon navire ait survécu, et votre précieuse cargaison est pour la plupart intacte... pour la plupart.";
			link.l1.go = "VsD_Komendant_2";
		break;
		
		case "VsD_Komendant_2":
			dialog.text = "Que veux-tu dire, principalement ?!";
			link.l1 = "Je ne peux pas garantir que les deux cents barils de poudre à canon, chargés à la dernière minute par l'un de vos lieutenants, n'ont pas été endommagés. Ils devaient être chargés en dernier, et ce sont probablement eux qui ont explosé.";
			link.l1.go = "VsD_Komendant_3";
		break;
		
		case "VsD_Komendant_3":
			dialog.text = "Qu'est-ce que c'est que ces balivernes, Charles ? Quel lieutenant ? Quelle poudre à canon ? Je n'ai pas donné un tel ordre !";
			link.l1 = "Ce lieutenant devait être de votre garnison. Je ne me suis pas renseigné sur son nom, mais il semblait être au courant de l'opération.";
			link.l1.go = "VsD_Komendant_4";
		break;
		
		case "VsD_Komendant_4":
			dialog.text = "Ah, merde ! Il semble que les Castillans soient enclins à jouer sale aussi... Je vais gérer cette situation fâcheuse, Capitaine. Cependant, vous avez toujours un travail à faire : êtes-vous certain que votre navire est en état de naviguer ?";
			link.l1 = "Elle flotte, mais elle a certainement besoin de réparations importantes.";
			link.l1.go = "VsD_Komendant_5";
			SetMusic("classic_fra_music_day");
		break;
		
		case "VsD_Komendant_5":
			dialog.text = "Pas de temps pour ça, Capitaine. Levez l'ancre immédiatement et accomplissez la mission. Les enjeux sont trop élevés pour tarder.";
			link.l1 = "Ne pouvons-nous pas avoir au moins un jour, pour l'amour du ciel ? Le chantier naval local pourrait effectuer les réparations nécessaires ! Et qu'en est-il de mon équipage ?! Il y a sûrement des pertes !";
			link.l1.go = "VsD_Komendant_6";
			sld = CharacterFromID("Tichingitu");
			if (sld.location == pchar.location && !LAi_IsDead(sld))
			{
				LAi_SetOfficerType(sld);
				sld.Dialog.Filename = "Quest\Sharlie\Tichingitu.c";
				sld.Dialog.CurrentNode = "Tichingitu_officer";
			}
			if (GetCharacterIndex("Folke") != -1 && CheckPassengerInCharacter(pchar, "Folke"))
			{
				sld = CharacterFromID("Folke");
				ChangeCharacterAddressGroup(sld, "none", "", "");
				sld.Dialog.Filename = "Enc_Officer_dialog.c";
				sld.Dialog.CurrentNode = "hired";
			}
			else
			{
				sld = CharacterFromID("Alonso");
				ChangeCharacterAddressGroup(sld, "none", "", "");
			}
		break;
		
		case "VsD_Komendant_6":
			dialog.text = "Au cas où vous ne l'auriez pas remarqué, le chantier naval est en flammes. Nous essayons encore de déterminer si c'est intentionnel ou un résultat secondaire de l'explosion. Je peux seulement vous promettre que vos blessés recevront des soins médicaux, et que la Couronne prendra en charge les frais d'enterrement des morts.";
			link.l1 = "Es-tu sérieux ? C'est le mieux que tu puisses offrir ?";
			link.l1.go = "VsD_Komendant_7";
			sld = CharacterFromID("VsD_Tsyganka");
			ChangeCharacterAddressGroup(sld, "PortPax_town", "reload", "reload5_back");
			LAi_CharacterEnableDialog(sld);
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
		break;
		
		case "VsD_Komendant_7":
			dialog.text = "Capitaine, la France a urgemment besoin de votre aide. Je vous fournirai des planches, et si vous jouez vos cartes intelligemment, votre navire sera presque entièrement réparé d'ici à ce que vous atteigniez la Jamaïque.";
			link.l1 = "Excusez-moi, mais quelles planches? Et pourquoi la Jamaïque?";
			link.l1.go = "VsD_Komendant_8";
			pchar.ship.HP = sti(pchar.ship.HP) / 2;
			pchar.Ship.Crew.Quantity = sti(pchar.ship.Crew.Quantity) - sti(pchar.ship.Crew.Quantity) / 7;
			AddCharacterGoodsSimple(pchar, GOOD_PLANKS, 100);
		break;
		
		case "VsD_Komendant_8":
			dialog.text = "Votre équipage peut effectuer des réparations d'urgence en mer avec les planches - un matériau de réparation principal. Et la Jamaïque est assez proche d'une des routes que vous pouvez emprunter pour Porto Bello. Si vous ne perdez pas de temps, vous pouvez terminer les réparations et recruter un équipage complet là-bas.";
			link.l1 = "Très bien, alors. Je prendrai la mer immédiatement, Colonel.";
			link.l1.go = "VsD_Komendant_9";
			
			sld = CharacterFromID("PortRoyal_shipyarder");
			sld.TrialDelQuestMark = true;
			AddLandQuestMark(sld, "questmarkmain");
			AddMapQuestMarkCity("PortRoyal", false);
		break;
		
		case "VsD_Komendant_9":
			DialogExit();
			LAi_SetStayType(pchar);
			
			sld = CharacterFromID("VsD_Tsyganka");
			sld.dialog.filename = "Quest\Sharlie\OtherNPC.c";
			sld.dialog.currentnode = "VsD_Tsyganka";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 3, 0);
			
			sld = CharacterFromID("PortPaxAmmoOff_clone");
			sld.lifeday = 0;
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "gate_back", "none", "", "", "", -1);
		break;
		
		case "VsD_Tsyganka":
			dialog.text = "Pourquoi tant de hâte, cher?";
			link.l1 = "Chérie, je n'ai pas le temps pour ça maintenant. Ne vois-tu pas ce qui se passe ?";
			link.l1.go = "VsD_Tsyganka_1";
		break;
		
		case "VsD_Tsyganka_1":
			dialog.text = "Oh, les troubles actuels sont terribles, mais je peux voir par ta main que d'autres surgissent à l'horizon.";
			link.l1 = "Tout le monde peut voir cela même sans regarder ma main, qui, je pourrais ajouter, est dans un gant. Très bien, je vais jouer le jeu : quel est le prix pour éviter un désastre de nos jours ?";
			link.l1.go = "VsD_Tsyganka_2";
		break;
		
		case "VsD_Tsyganka_2":
			dialog.text = "Je n'ai pas ce pouvoir, beau gosse. Et même si je l'avais, je ne pourrais pas me le permettre. Mais je peux quand même t'aider... avec ton navire. La demoiselle est dans un état lamentable, mon cher.";
			link.l1 = "Je n'ai jamais connu votre bande de gitans pour avoir des ambitions en menuiserie.";
			link.l1.go = "VsD_Tsyganka_3";
			
			for (i=3; i<=8; i++)
			{				
				sld = CharacterFromID("VsD_MirnyeMan_"+i);
				LAi_SetCitizenType(sld);
			}
			for (i=3; i<=6; i++)
			{				
				sld = CharacterFromID("VsD_MirnyeWoman_"+i);
				LAi_SetCitizenType(sld);
			}
			for (i=1; i<=6; i++)
			{				
				sld = CharacterFromID("VsD_Sold_"+i);
				LAi_SetCitizenType(sld);
			}
			//Возвращаем всё обратно
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			bDisableCharacterMenu = false;
			SetLocationCapturedState("PortPax_town", false);
			Locations[FindLocation("PortPax_town")].locators_radius.quest.quest1 = 1.0;
			Locations[FindLocation("PortPax_town")].locators_radius.patrol.patrol14 = 0.5;
			LocatorReloadEnterDisable("PortPax_ExitTown", "reload2_back", false);
			LocatorReloadEnterDisable("PortPax_ExitTown", "reload1_back", false);
			LAi_LocationFightDisable(&Locations[FindLocation("PortPax_town")], false);
			LAi_LocationFightDisable(&Locations[FindLocation("PortPax_Fort")], false);
			
			for (i=1; i<=5; i++)
			{
				sld = CharacterFromID("VsD_Guard_"+i);
				sld.lifeday = 0;
			}
			//Диего исчезает
			sld = CharacterFromID("Diego");
			LAi_CharacterEnableDialog(sld);
			sld.location = "None";
			//Верфь закрывается
			LocatorReloadEnterDisable("PortPax_Town", "reload5_back", true);
			SetTimerCondition("VsD_VerfOtkryt", 0, 0, 7, false);
			//Труп предателя в джунглях
			PChar.quest.VsD_TrupPredatelya.win_condition.l1 = "location";
			PChar.quest.VsD_TrupPredatelya.win_condition.l1.location = "PortPax_ExitTown";
			PChar.quest.VsD_TrupPredatelya.win_condition = "VsD_TrupPredatelya";
			SetTimerCondition("VsD_TrupPredatelya_3", 0, 0, 60, false);
		break;
		
		case "VsD_Tsyganka_3":
			dialog.text = "Toi, ma chère, tu n'es guère charpentier toi-même. Crois-tu que des planches seules répareront le navire ? Elles ne feront que te lester à moins que tu n'aies un maître charpentier...";
			link.l1 = "Où ?";
			link.l1.go = "VsD_Tsyganka_4";
		break;
		
		case "VsD_Tsyganka_4":
			dialog.text = "Il y a un puissant amulette, vénéré par les locaux. Le bois se plie à sa volonté, et même ceux qui ne connaissent rien à la charpenterie se retrouvent habiles une fois qu'ils le portent. Il est à vous pour seulement mille pesos, cher.";
			if (sti(pchar.Money) >= 1000)
			{
				link.l1 = "Très bien, marché conclu. J'ai besoin de toute l'aide possible.";
				link.l1.go = "VsD_Tsyganka_Da";
			}
			link.l2 = "Je n'ai pas le temps pour tes sorcelleries. Va en paix, sorcière, et ne te mêle pas de mes affaires.";
			link.l2.go = "VsD_Tsyganka_Net";
			npchar.lifeday = 0;
		break;
		
		case "VsD_Tsyganka_Net":
			DialogExit();
			LAi_SetPlayerType(pchar);
			AddQuestRecord("Trial", "7_1");
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "VsD_Tsyganka_Da":
			DialogExit();
			LAi_SetPlayerType(pchar);
			AddQuestRecord("Trial", "7_1");
			AddCharacterExpToSkill(pchar, "Repair", 20);
			AddMoneyToCharacter(pchar, -1000);
			GiveItem2Character(PChar, "obereg_1");
			Log_info("You have received Amulet 'Teredo'");
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);
		break;
		
		//замечание по обнажённому оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar,"Écoute-moi, je suis un citoyen respectueux des lois de cette ville. Je dois te demander de ne pas te promener avec ton épée dégainée comme un brigand.","Monsieur, je vous en prie, la loi est claire : il est interdit aux hommes de se promener avec des armes dégainées à l'intérieur des murs de la ville.");
			link.l1 = LinkRandPhrase("D'accord.","Très bien.","Comme tu veux...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			if (npchar.id == "GigoloMan") NextDiag.TempNode = "GigoloMan";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
