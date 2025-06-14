void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag, arTmp;
	int i, n;
	string sTemp, sStr;
	
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
			dialog.text = "Que voulez-vous ?";
			link.l1 = "Rien.";
			link.l1.go = "exit";
		break;

		// Диалог с Алонсо после успешного абордажа
		case "Memento_MortimerGrimDead_Alonso_1":
			dialog.text = "Cap’, la journée est à nous. L’avant-garde termine le nettoyage du pont inférieur. Aucun prisonnier... Oh ! Je vois que vous n’avez pas fait dans la dentelle non plus.";
			link.l1 = "Je m’attendais à un discours pompeux de sa part. Mais non, il s’est jeté directement au combat.";
			link.l1.go = "Memento_MortimerGrimDead_Alonso_2";
			Achievment_Set("ach_CL_154");
		break;

		case "Memento_MortimerGrimDead_Alonso_2":
			dialog.text = "Permission de parler ?";
			link.l1 = "Je vous écoute.";
			link.l1.go = "Memento_MortimerGrimDead_Alonso_3";
			link.l2 = "Non, on a terminé ici.";
			link.l2.go = "Memento_MortimerGrimDead_Alonso_end";
		break;

		case "Memento_MortimerGrimDead_Alonso_3":
			dialog.text = "Pourquoi les avons-nous attaqués ? Cette goélette ne nous menaçait en rien, elle ne transportait rien d’important. Il y avait bien des rumeurs sur Grim, mais seuls les marchands d’esclaves le craignaient. Vous avez tué un paquet de gens aujourd’hui – et pour quoi, au juste ?";
			if (sti(pchar.questTemp.ISawDiegoDeLanda) >= 2)
			{
				link.l1 = "...";
				link.l1.go = "Memento_MortimerGrimDead_Alonso_4";
			}
			else
			{
				link.l1 = "Tu parles au nom de l’équipage, là ?";
				link.l1.go = "Memento_MortimerGrimDead_Alonso_5";
			}
		break;
		
		case "Memento_MortimerGrimDead_Alonso_4":
			dialog.text = "Et ce n’est pas la première fois...";
			link.l1 = "Tu parles au nom de l’équipage, là ?";
			link.l1.go = "Memento_MortimerGrimDead_Alonso_5";
		break;

		case "Memento_MortimerGrimDead_Alonso_5":
			dialog.text = "Non. Croyez-moi, si l’équipage commençait à se poser ce genre de questions, ça voudrait dire que je fais mal mon boulot, et vous seriez déjà un homme mort.\n"+
			"Heureusement pour vous, cette sanglante aventure a rapporté gros. Les poches de chaque marin de ce navire débordaient de doublons !\n"+
			"Pas de cargaison précieuse, cela dit – juste quelques babioles indigènes et des amulettes lugubres. Mais les hommes se sont bien servis. Grim devait bien les payer.\n"+
			"J’espère que vous n’allez pas revendiquer votre part de cet or, cap’ ?";
			link.l1 = "Non, Alonso. Merci de m’avoir mis au courant.";
			link.l1.go = "Memento_MortimerGrimDead_Alonso_6";
			link.l2 = "Si, je la veux. Assure-toi que ma part arrive dans ma cabine.";
			link.l2.go = "Memento_MortimerGrimDead_Alonso_7";
		break;

		case "Memento_MortimerGrimDead_Alonso_6":
			dialog.text = "Je suis toujours de votre côté, cap’. Au fait, que comptez-vous faire du 'Memento' ?";
			link.l1 = "Le prendre comme prise – que voulez-vous que je fasse d’autre ?";
			link.l1.go = "Memento_MortimerGrimDead_Alonso_8";
			link.l2 = "Je ne sais pas encore.";
			link.l2.go = "Memento_MortimerGrimDead_Alonso_8";
		break;

		case "Memento_MortimerGrimDead_Alonso_7":
			dialog.text = "Je suis toujours de votre côté, cap’. Au fait, que comptez-vous faire du 'Memento' ?";
			link.l1 = "Le prendre comme prise – que voulez-vous que je fasse d’autre ?";
			link.l1.go = "Memento_MortimerGrimDead_Alonso_8";
			link.l2 = "Je ne sais pas encore.";
			link.l2.go = "Memento_MortimerGrimDead_Alonso_8";
			AddCrewMorale(Pchar, -10);
			AddItems(Pchar, "gold_dublon", 500);
		break;

		case "Memento_MortimerGrimDead_Alonso_8":
			dialog.text = "Mauvaise idée. Ce navire est couvert de symboles indigènes. Et puis, il a une mauvaise réputation – certains disent qu’il a survécu à une épidémie monstrueuse, et que seuls les morts ne dansaient pas sur ses ponts.\n"+
			"Et je ne parle même pas du squelette à la poupe : tant qu’un idiot n’aura pas volé ce crâne par bravade, personne d’autre que moi n’osera monter la garde à l’arrière.";
			link.l1 = "Bien reçu, Alonso. Retourne à ton poste.";
			link.l1.go = "Memento_MortimerGrimDead_Alonso_9";
		break;

		case "Memento_MortimerGrimDead_Alonso_9":
			dialog.text = "Bien reçu, cap’.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrimDead_Alonso_end";
		break;
		
		case "Memento_MortimerGrimDead_Alonso_end":
			DialogExit();
			AddDialogExitQuestFunction("Memento_MortimerGrimDead_Alonso_2");
		break;
		
		// Диалог с Алонсо в первую ночь
		case "Memento_Dich_EtapOne_Alonso_1":
			dialog.text = "Capitaine, excusez-moi de vous déranger à cette heure.";
			link.l1 = "Fais ton rapport, Alonso.";
			link.l1.go = "Memento_Dich_EtapOne_Alonso_2";
			if (CheckAttribute(pchar, "questTemp.Memento_Dich_EtapTwo"))
			{
				dialog.text = "Capitaine ? Que faites-vous ici ? Vous avez dormi ici ?";
				link.l1 = "Ce n’est pas important.";
				link.l1.go = "Memento_Dich_EtapTwo_Alonso_2";
				link.l2 = "Ma cabine est... inconfortable.";
				link.l2.go = "Memento_Dich_EtapTwo_Alonso_2";
			}
		break;

		case "Memento_Dich_EtapOne_Alonso_2":
			dialog.text = "Notre situation est mauvaise. Le moral de l’équipage est au plus bas ! Les hommes parlent ouvertement d’une malédiction sur le navire. Ils se plaignent de visions nocturnes.";
			link.l1 = "Quelles visions exactement ?";
			link.l1.go = "Memento_Dich_EtapOne_Alonso_3";
		break;

		case "Memento_Dich_EtapOne_Alonso_3":
			dialog.text = "Des cauchemars, apparemment. Mais le pire, c’est qu’un de nos hommes est mort de fièvre. Un jeune gars, costaud, et pourtant il a brûlé en quelques heures.";
			if (sti(pchar.Fellows.Passengers.doctor) == sti(sld.index))
			{
				link.l1 = "C’est au médecin d’en juger. "+sld.name+" sait ce qu’il fait.";
				link.l1.go = "Memento_Dich_EtapOne_Alonso_4";
			}
			else
			{
				link.l1 = "C’est impossible. Maintiens la discipline, Alonso. C’est ton travail.";
				link.l1.go = "Memento_Dich_EtapOne_Alonso_4";
			}
		break;

		case "Memento_Dich_EtapOne_Alonso_4":
			dialog.text = "Bien reçu !";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Memento_Dich_EtapOne_End");
		break;
		
		// Диалог с Алонсо во вторую ночь
		case "Memento_Dich_EtapTwo_Alonso_2":
			dialog.text = "Je comprends. Beaucoup dans l’équipage dorment ensemble maintenant – ils ont peur de rester seuls. Comme si c’était même possible d’être seul sur ce navire…";
			link.l1 = "Comme tu vois, je n’ai pas réussi. Que s’est-il passé ?";
			link.l1.go = "Memento_Dich_EtapTwo_Alonso_3";
		break;

		case "Memento_Dich_EtapTwo_Alonso_3":
			dialog.text = "Une bagarre – José a poignardé Marcel. Il criait qu’il 'apportait la peste'.";
			link.l1 = "La situation a empiré ?";
			link.l1.go = "Memento_Dich_EtapTwo_Alonso_4";
		break;

		case "Memento_Dich_EtapTwo_Alonso_4":
			if (sti(pchar.Fellows.Passengers.doctor) == sti(sld.index))
			{
				dialog.text = ""sld.name+" vous en a déjà parlé ce matin. Nous avons perdu onze hommes. Que fait-on ?";
			}
			else
			{
				dialog.text = "Encore onze morts. Que fait-on ?";
			}
			link.l1 = "Je vais prendre une décision.";
			link.l1.go = "Memento_Dich_EtapTwo_Alonso_5";
		break;

		case "Memento_Dich_EtapTwo_Alonso_5":
			dialog.text = "J’espère bien, capitaine. Que fait-on de José ? Le meurtre, ce n’est pas rien.";
			link.l1 = "Pendez-le après les cloches. Montrons que la situation est sous contrôle.";
			link.l1.go = "Memento_Dich_EtapTwo_Alonso_6";
			link.l2 = "Trente coups de fouet. S’il survit, c’est que Dieu l’a voulu.";
			link.l2.go = "Memento_Dich_EtapTwo_Alonso_7";
		break;

		case "Memento_Dich_EtapTwo_Alonso_6":
			dialog.text = "Bien reçu !";
			link.l1 = "...";
			link.l1.go = "exit";
			SetCrewQuantity(pchar, GetCrewQuantity(pchar) - 1);
			AddDialogExitQuestFunction("Memento_Dich_EtapTwo_End");
		break;

		case "Memento_Dich_EtapTwo_Alonso_7":
			dialog.text = "Bien reçu !";
			link.l1 = "...";
			link.l1.go = "exit";
			AddCrewMorale(Pchar, -10);
			AddDialogExitQuestFunction("Memento_Dich_EtapTwo_End");
		break;
		
		// Диалог с Алонсо в третью ночь
		case "Memento_Dich_EtapThree_AlonsoPrizrak_1":
			dialog.text = "Capitaine ! Branle-bas !! Vous devez immédiatement descendre au pont inférieur !";
			link.l1 = "Que se passe-t-il ?";
			link.l1.go = "Memento_Dich_EtapThree_AlonsoPrizrak_2";
		break;
		
		case "Memento_Dich_EtapThree_AlonsoPrizrak_2":
			dialog.text = "Vous feriez mieux de voir ça par vous-même. Suivez-moi, vite !";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Memento_Dich_EtapThree_Paluba_4_1");
		break;
		
		// Уже утром
		case "Memento_Dich_EtapThree_Alonso_1":
			dialog.text = "Bonjour, capitaine !";
			link.l1 = "Hein ?!";
			link.l1.go = "Memento_Dich_EtapThree_Alonso_2";
		break;
		
		case "Memento_Dich_EtapThree_Alonso_2":
			dialog.text = "Euh... Vous avez mauvaise mine. Mauvaise nuit ? Bon, j’ai de bonnes nouvelles. L’épidémie est terminée. En fait, elle n’a jamais existé.";
			link.l1 = "Comment ça ?";
			link.l1.go = "Memento_Dich_EtapThree_Alonso_3";
		break;
		
		case "Memento_Dich_EtapThree_Alonso_3":
			dialog.text = "L’équipage s’est affolé, influencé par des rumeurs idiotes sur un navire maudit. Le pouvoir de l’autosuggestion est terrible, je vous assure. Il a déjà coulé plus d’un navire.";
			link.l1 = "Mais des gens sont morts !";
			link.l1.go = "Memento_Dich_EtapThree_Alonso_4";
		break;
		
		case "Memento_Dich_EtapThree_Alonso_4":
			dialog.text = "Des combats, des blessures infectées, de la viande salée avariée — les réalités de la mer. Si nous ne nous étions pas monté la tête avec ces histoires de navires maudits, on aurait peut-être perdu deux hommes de moins.\n"+
			"Le squelette à la poupe n’a pas aidé non plus. Heureusement, un... plaisantin lui a volé son chapeau cette nuit.\n"+
			"Et comme la foudre n’a pas frappé le navire pour ce sacrilège, les gars se sont un peu détendus et ont commencé à planifier comment s’amuser avec le squelette. Par exemple...";
			link.l1 = "Personne ne touche au squelette !";
			link.l1.go = "Memento_Dich_EtapThree_Alonso_5";
		break;
		
		case "Memento_Dich_EtapThree_Alonso_5":
			dialog.text = "Euh... Eh bien, si vous tenez tant à lui, on le laissera tranquille. Bonne journée, capitaine.\n"+
			"Au fait, joli chapeau ! Il vous va bien. L’ancien propriétaire avait une plus petite tête.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Memento_Dich_EtapThree_End");
		break;
		
		// Диалоги с командой Мементо
		case "Memento_Sailor_1":
			if (!CheckAttribute(npchar, "talked"))
			{
				dialog.text = "Salutations, capitaine. Vous devriez vous adresser au capitaine Grim.";
				link.l1 = "Désolé, matelot, mais tu te fais remarquer ici.";
				link.l1.go = "Memento_Sailor_1_1";
				npchar.talked = true;
			}
			else
			{
				dialog.text = "Quelque chose d’autre, capitaine ?";
				link.l1 = "Non, rien.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Memento_Sailor_1";
		break;
		
		case "Memento_Sailor_1_1":
			dialog.text = "Je vois ce que vous voulez dire, capitaine. J’ai servi sous un capitaine libre — comme vous. Il cherchait des trésors, commerçait, transportait des cargaisons. Puis il a voulu s’en prendre à quelques marchands — et ça s’est mal fini. Les survivants ont été pendus pour piraterie.";
			link.l1 = "Et le capitaine Grim vous a racheté ?";
			link.l1.go = "Memento_Sailor_1_2";
		break;
		
		case "Memento_Sailor_1_2":
			dialog.text = "Tous ensemble, comme une cargaison. Un matelot expérimenté est toujours utile, et le capitaine Grim ne recrute pas dans les tavernes... Mais il nous nourrit et nous paie bien. En échange, on sert — et on tire au sort.";
			link.l1 = "Tirer au sort ?";
			link.l1.go = "Memento_Sailor_1_3";
		break;
		
		case "Memento_Sailor_1_3":
			dialog.text = "Pardon, nous ne devrions pas parler de ça.";
			link.l1 = "Pourquoi ne partez-vous pas alors ?";
			link.l1.go = "Memento_Sailor_1_4";
		break;
		
		case "Memento_Sailor_1_4":
			dialog.text = "Où irions-nous ? Au moins ici, il y a une chance. Peut-être qu’on aura de la chance. Chaque navire a son tirage. Le capitaine Grim a le sien, vous avez le vôtre. Nous ne sommes pas des hommes, juste des numéros dans un registre de bord.";
			link.l1 = "Sur mon navire, les règles sont différentes.";
			link.l1.go = "Memento_Sailor_1_5";
		break;
		
		case "Memento_Sailor_1_5":
			dialog.text = "Comme vous voudrez, capitaine. Bonne journée à vous.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Memento_Sailor_1";
		break;
		
				case "Memento_Sailor_2":
			if (!CheckAttribute(npchar, "talked"))
			{
				dialog.text = "Ça faisait longtemps qu’on n’avait pas eu de visiteurs à bord de notre fier navire !";
				link.l1 = "Tu es marin ? On dirait pas.";
				link.l1.go = "Memento_Sailor_2_1";
				npchar.talked = true;
			}
			else
			{
				dialog.text = "Autre chose, capitaine ?";
				link.l1 = "Non.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Memento_Sailor_2";
		break;
		
		case "Memento_Sailor_2_1":
			dialog.text = "Ha ! Le capitaine m’a racheté directement depuis une cellule. J’allais être pendu à Port-Royal : j’ai poignardé un gars — un jeunot, qui récitait toujours ses foutus poèmes. Il l’a bien mérité, l’enflure.";
			link.l1 = "Tu as eu de la chance, on dirait.";
			link.l1.go = "Memento_Sailor_2_2";
		break;
		
		case "Memento_Sailor_2_2":
			dialog.text = "Plutôt, ouais ! Le capitaine est généreux, mais parfois, faut participer à ses... jeux.";
			link.l1 = "Quels jeux ?";
			link.l1.go = "Memento_Sailor_2_3";
		break;
		
		case "Memento_Sailor_2_3":
			dialog.text = "Une fois par semaine, on tire des bâtons : le plus court — tu fais un boulot hyper dangereux ou tu sautes carrément par-dessus bord. C’est marrant, en quelque sorte. Pas pour tout le monde, bien sûr, mais le capitaine dit : seuls les dignes survivent.";
			link.l1 = "Dignes de quoi ?";
			link.l1.go = "Memento_Sailor_2_4";
		break;
		
		case "Memento_Sailor_2_4":
			dialog.text = "J’en sais rien. Le capitaine aime les beaux discours, il parle comme un prêtre : «Ce n’est qu’en rencontrant la mort qu’on apprend à vivre vraiment !»\n"+
			"(il crache)";
			link.l1 = "Cracher sur le pont, c’est le fouet. Tu te comportes comme un bandit, pas un marin. Adieu.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Memento_Sailor_2";
		break;

		case "Memento_Sailor_3":
			if (!CheckAttribute(npchar, "talked"))
			{
				dialog.text = "Bonjour, capitaine.";
				link.l1 = "Comment as-tu fini ici ?";
				link.l1.go = "Memento_Sailor_3_1";
				npchar.talked = true;
			}
			else
			{
				dialog.text = "Autre chose, capitaine ?";
				link.l1 = "Non.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Memento_Sailor_3";
		break;
		
		case "Memento_Sailor_3_1":
			dialog.text = "Le capitaine Grim a pris un navire négrier sur lequel j'étais. J’étais malade, en train de mourir dans la cale... je me souviens de peu de choses. Quand je me suis réveillé, j’étais déjà ici, sur le 'Memento'.";
			link.l1 = "Et qu’est-il arrivé aux autres esclaves ?";
			link.l1.go = "Memento_Sailor_3_2";
		break;

		case "Memento_Sailor_3_2":
			dialog.text = "Je ne sais pas. Le capitaine dit qu’il les a tous libérés, mais j’étais le seul à être amené sur le navire. Les autres se sont sans doute dispersés sur les îles ou sont morts de leurs blessures. Je ne me souviens pas bien de ce jour.";
			link.l1 = "Mais tu es libre, maintenant.";
			link.l1.go = "Memento_Sailor_3_3";
		break;

		case "Memento_Sailor_3_3":
			dialog.text = "Libre ? Personne ne l’est ici. Le capitaine donne de l’or, nourrit, habille, mais en échange, il exige une loyauté totale — et il impose ce tirage au sort effroyable.";
			link.l1 = "Un tirage au sort ?";
			link.l1.go = "Memento_Sailor_3_4";
		break;

		case "Memento_Sailor_3_4":
			dialog.text = "Chaque semaine, quelqu’un tire le bâton le plus court et part pour une mission dangereuse, d’où tous ne reviennent pas. Le capitaine dit que c’est ainsi que les vivants se distinguent des morts.";
			link.l1 = "Et vous tolérez cela ?";
			link.l1.go = "Memento_Sailor_3_5";
		break;

		case "Memento_Sailor_3_5":
			dialog.text = "Chacun espère que la chance sera de son côté. Le capitaine a une clé pour chacun : la peur de retourner à la potence, la soif d’or, le besoin de rembourser une dette pour une vie sauvée. Moi, tout cela ne m’intéresse pas. Je n’ai pas besoin d’argent, et quelle dette pourrait-on avoir pour ce dont on ne se souvient même pas ?";
			link.l1 = "Tu n’as pas peur de parler aussi ouvertement ?";
			link.l1.go = "Memento_Sailor_3_6";
		break;

		case "Memento_Sailor_3_6":
			dialog.text = "Qu’est-ce qu’ils pourraient me faire ? C’est un navire de morts, capitaine, et moi, j’y suis à ma place. Mais vous... non.";
			link.l1 = "Comme tu veux. Adieu.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Memento_Sailor_3";
		break;

		case "Memento_Sailor_4":
			if (!CheckAttribute(npchar, "talked"))
			{
				dialog.text = "Bienvenue à bord du 'Memento', capitaine.";
				link.l1 = "Un soldat espagnol sur un navire pirate ? Voilà qui est inhabituel.";
				link.l1.go = "Memento_Sailor_4_1";
				npchar.talked = true;
			}
			else
			{
				dialog.text = "Autre chose, capitaine ?";
				link.l1 = "Non.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Memento_Sailor_4";
		break;
		
				case "Memento_Sailor_4_1":
			dialog.text = "Déserteur. Le capitaine Grim m’a racheté directement de la potence sur la place de San José. Il a payé cher — un sac entier de doublons pour ma peau poussiéreuse.";
			link.l1 = "Et pourquoi étiez-vous condamné ?";
			link.l1.go = "Memento_Sailor_4_2";
		break;
		
		case "Memento_Sailor_4_2":
			dialog.text = "L’officier Saldo nous avait envoyés garder des ouvriers dans la jungle, où la moitié meurt de la fièvre en une semaine. J’ai décidé que ma vie valait plus. Et maintenant... je sers celui qui l’a payée en pièces sonnantes.";
			link.l1 = "Vous ne regrettez pas ?";
			link.l1.go = "Memento_Sailor_4_3";
		break;
		
		case "Memento_Sailor_4_3":
			dialog.text = "La corde peut tourner longtemps... Le capitaine est généreux envers ceux qui lui sont fidèles. Mais parfois, il organise d’étranges épreuves — un tirage au sort. Tout le monde n’a pas de chance.";
			link.l1 = "Un tirage au sort ?";
			link.l1.go = "Memento_Sailor_4_4";
		break;
		
		case "Memento_Sailor_4_4":
			dialog.text = "Vous savez, certains doivent monter aux mâts en pleine tempête, d’autres sont envoyés à l’avant-garde. Le capitaine dit que c’est pour tester notre préparation. À quoi, je l’ignore, mais j’espère avoir de la chance.";
			link.l1 = "Bonne chance... je suppose.";
			link.l1.go = "Memento_Sailor_4_5";
		break;
		
		case "Memento_Sailor_4_5":
			dialog.text = "Merci, capitaine. La mort poursuit chacun de nous.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Memento_Sailor_4";
		break;

		/*case "Memento_Sailor_5":
			if (!CheckAttribute(npchar, "talked"))
			{
				dialog.text = "Диалог 5";
				link.l1 = "Диалог 5";
				link.l1.go = "exit";
				npchar.talked = true;
			}
			else
			{
				dialog.text = "Что-нибудь ещё, капитан?";
				link.l1 = "Ничего.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Memento_Sailor_5";
		break;*/
		
		case "Memento_MortimerGrim_1":
			if (!CheckAttribute(npchar, "talked"))
			{
				dialog.text = "Bienvenue à bord du 'Memento', collègue. Je m'appelle Mortimer Grim.";
				link.l1 = "Capitaine "+GetFullName(pchar)+". Merci de votre accueil...";
				link.l1.go = "Memento_MortimerGrim_2";
				npchar.talked = true;
			}
			else
			{
				dialog.text = "De quoi voulez-vous encore parler ?";
				if (!CheckAttribute(npchar, "SharlieTutorial_question_1"))
				{
					link.l1 = "Votre lame est extraordinaire, capitaine.";
					link.l1.go = "Memento_MortimerGrim_question_1_1";
				}
				if (!CheckAttribute(npchar, "SharlieTutorial_question_2"))
				{
					link.l2 = "Votre longue-vue va parfaitement avec le squelette.";
					link.l2.go = "Memento_MortimerGrim_question_2_1";
				}
				if (!CheckAttribute(npchar, "SharlieTutorial_question_3"))
				{
					link.l3 = "Je dois dire que votre équipage est très hétéroclite.";
					link.l3.go = "Memento_MortimerGrim_question_3_1";
				}
				link.l4 = "Rien... collègue. Bon vent.";
				link.l4.go = "exit";
				NextDiag.TempNode = "Memento_MortimerGrim_1";
			}
		break;
		
				case "Memento_MortimerGrim_2":
			dialog.text = "Les Caraïbes sont généreuses avec ceux qui se précipitent vers l’échafaud — je le sais bien.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_3";
		break;
		
		case "Memento_MortimerGrim_3":
			dialog.text = "Oui ? Vous vouliez poser une question ?";
			link.l1 = "Il y a un squelette suspendu derrière vous.";
			link.l1.go = "Memento_MortimerGrim_4";
			link.l2 = "Le vent est bon aujourd’hui, non ? Et le temps aussi.";
			link.l2.go = "Memento_MortimerGrim_5";
		break;
		
		case "Memento_MortimerGrim_4":
			dialog.text = "Quel squelette ? Derrière moi, il n’y a que la mer bleue des Caraïbes.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_6";
		break;
		
		case "Memento_MortimerGrim_5":
			dialog.text = "Je suis d’accord, collègue. Si seulement chaque jour était comme ça !";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_6";
		break;
		
		case "Memento_MortimerGrim_6":
			dialog.text = "Ha ha ha ! Cette blague ne vieillit jamais ! N’ayez pas peur : le vieux Yorick, comme ce navire, est un souvenir de ma vie passée. Au sens propre, bien sûr.";
			link.l1 = "'Au sens propre'?";
			link.l1.go = "Memento_MortimerGrim_7";
		break;
		
		case "Memento_MortimerGrim_7":
			dialog.text = "Collègue, avez-vous peur de la mort ? Ce n’est pas une menace, je suis sincèrement curieux.";
			link.l1 = "Bien sûr. Ceux qui disent le contraire mentent.";
			link.l1.go = "Memento_MortimerGrim_8_leadership";
			link.l2 = "Non. Nous y passerons tous un jour.";
			link.l2.go = "Memento_MortimerGrim_8_weapon";
			link.l3 = "Et vous ?";
			link.l3.go = "Memento_MortimerGrim_8_sneak";
		break;
		
		case "Memento_MortimerGrim_8_leadership":
			dialog.text = "Ah ! La mort est la mère de toutes les peurs. Solitude, obscurité, punition — ce ne sont que ses masques.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_9";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		
		case "Memento_MortimerGrim_8_weapon":
			dialog.text = "Ah ! La mort est la mère de toutes les peurs. Solitude, obscurité, punition — ce ne sont que ses masques.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_9";
			AddComplexSelfExpToScill(100, 100, 100, 100);
		break;
		
		case "Memento_MortimerGrim_8_sneak":
			dialog.text = "Ah ! La mort est la mère de toutes les peurs. Solitude, obscurité, punition — ce ne sont que ses masques.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_9";
			AddCharacterExpToSkill(pchar, "Sneak", 100);
		break;
		
		case "Memento_MortimerGrim_9":
			dialog.text = "Pas besoin d’aller loin : regardez le vieux Yorick — un tas d’os avec une lanterne dans les côtes, et il a réussi à faire frémir même un capitaine aussi redoutable que vous !";
			if (startHeroType == 4)
			{
				dialog.text = "Pas besoin d’aller loin : regardez le vieux Yorick — un tas d’os avec une lanterne dans les côtes, et même la courageuse Hélène, fille du grand Sean MacArthur, a eu des sueurs froides !";
			}
			link.l1 = "De beaux discours, mais vous ne m’avez pas dit quoi en faire.";
			link.l1.go = "Memento_MortimerGrim_10";
		break;
		
		case "Memento_MortimerGrim_10":
			dialog.text = "Moi, je sais. Mais mon remède ne convient pas à tout le monde. Vous pourrez toujours l’essayer plus tard. Mais d’abord, dites-moi ce que vous en pensez.";
			link.l1 = "La Bible dit que la mort n’existe pas.";
			link.l1.go = "Memento_MortimerGrim_11_1";
			link.l2 = "Si je commence à avoir peur, c’en est fini du navire.";
			link.l2.go = "Memento_MortimerGrim_11_2";
			link.l3 = "La réponse s’est noyée au fond d’une bouteille de rhum.";
			link.l3.go = "Memento_MortimerGrim_11_3";
		break;
		
		case "Memento_MortimerGrim_11_1":
			dialog.text = "C’est vrai. La seule chose sur laquelle je suis d’accord avec ce livre.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_12";
		break;
		
		case "Memento_MortimerGrim_11_2":
			dialog.text = "Louable. Mais vous vous inquiétez pour rien : la mort n’existe pas.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_12";
		break;
		
		case "Memento_MortimerGrim_11_3":
			dialog.text = "Yo-ho-ho ! Un cynique. Mais même sans rhum, je vous le dis : la mort n'existe pas.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_12";
		break;

		case "Memento_MortimerGrim_12":
			dialog.text = "C’est simple : la vraie vie commence seulement lorsque vous triomphez de la mort. J’y suis allé, au-delà du voile, et croyez-moi, je n’ai vraiment commencé à vivre qu’après.";
			link.l1 = "Pardon ?";
			link.l1.go = "Memento_MortimerGrim_13";
		break;

		case "Memento_MortimerGrim_13":
			dialog.text = "Peu importe, collègue.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_1";
		break;

		case "Memento_MortimerGrim_question_1_1":
			dialog.text = "Heureux que vous l'ayez remarqué, collègue ! Je ne suis pas un poseur, mais quel genre de pirate serais-je sans un sabre effrayant ?";
			link.l1 = "Est-ce vraiment important ?";
			link.l1.go = "Memento_MortimerGrim_question_1_2";
		break;

		case "Memento_MortimerGrim_question_1_2":
			dialog.text = "Bien sûr ! La seule fois où j’ai significativement allégé la caisse du navire pour des raisons personnelles, c’était pour cette lame. Deux mille doublons d’or, collègue ! Bon sang, si je pouvais ressusciter une seconde fois, ce serait pour le prix de cette arme !\n"+
			"L’arme est excellente, cela dit. Mais il lui manque encore quelque chose...";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_1";
			npchar.SharlieTutorial_question_1 = true;
		break;

		case "Memento_MortimerGrim_question_2_1":
			dialog.text = "Un cadeau d’un homme. Un excellent interlocuteur, qui comprenait la mort mieux que quiconque — et avec beaucoup d’imagination, comme vous pouvez le voir.";
			link.l1 = "C’est lugubre.";
			link.l1.go = "Memento_MortimerGrim_question_2_2";
		break;

		case "Memento_MortimerGrim_question_2_2":
			dialog.text = "Memento mori, collègue.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_1";
			npchar.SharlieTutorial_question_2 = true;
		break;

		case "Memento_MortimerGrim_question_3_1":
			dialog.text = "Mon équipage a bien plus en commun que le vôtre... Tous ont été délivrés par moi de la potence ou des chaînes, chacun a senti le souffle de la mort. Ce sentiment unit les gens mieux que le sang ou le drapeau.";
			link.l1 = "On dirait que vous ne recrutez pas dans les tavernes ?";
			link.l1.go = "Memento_MortimerGrim_question_3_2";
		break;

		case "Memento_MortimerGrim_question_3_2":
			dialog.text = "Vous seriez surpris de voir combien d’anciens esclaves et condamnés rejoignent volontiers l’équipage : échanger la cale d’un négrier ou l’échafaud contre le pont du Memento ? Mon navire compte aujourd’hui 178 âmes — toutes m’en sont redevables.";
			link.l1 = "Mais il faut bien payer l’équipage et entretenir le navire. La gratitude ne suffit pas.";
			link.l1.go = "Memento_MortimerGrim_question_3_3";
		break;

		case "Memento_MortimerGrim_question_3_3":
			dialog.text = "Je suis un pirate prospère, collègue. Un véritable 'hostis humanitatis'. C’est ainsi que m’appelleraient les vrais ennemis de l’humanité — les trafiquants d’esclaves et les couronnes royales. La seule différence entre eux, c’est le nom.\n"+
			"Heureusement, ils ont beaucoup d’or. Les pièces extraites des coffres des négriers servent à sauver ceux que la couronne condamne. Le reste revient à l’équipage — et moi, je n’ai besoin de rien. À quoi bon l’or pour les morts ? Ils comprendront bientôt...";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_1";
			npchar.SharlieTutorial_question_3 = true;
		break;
		
		// Диалог с Алонсо
		case "Memento_Alonso_phantom_11":
			dialog.text = "Voilà où nous en sommes, capitaine. Dans une belle merde.";
			link.l1 = "Qu'est-ce que c'est que ça ?!";
			link.l1.go = "Memento_Alonso_phantom_12";
		break;

		case "Memento_Alonso_phantom_12":
			dialog.text = "Il ne reste que vous. La maladie a emporté tout le monde. Vous nous avez trahis.";
			link.l1 = "C’est impossible !";
			link.l1.go = "Memento_Alonso_phantom_13";
		break;

		case "Memento_Alonso_phantom_13":
			dialog.text = "Vous nous avez conduits sur un navire maudit.";
			link.l1 = "...";
			link.l1.go = "Memento_Alonso_phantom_14";
		break;

		case "Memento_Alonso_phantom_14":
			dialog.text = "Vous avez condamné tout l’équipage à mort !";
			link.l1 = "Alonso, qu’est-ce qui t’arrive ?!";
			link.l1.go = "Memento_Alonso_phantom_15";
			npchar.model = "skel1";
			npchar.model.animation = "skeleton";
			npchar.sex = "skeleton";
			Characters_RefreshModel(npchar);
			SetMusic("classic_music_retribution_1");
		break;
		
		case "Memento_Alonso_phantom_15":
			dialog.text = "Mortui vivos docent.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Memento_Dich_EtapThree_Paluba_6");
		break;
		
		// Диалог с Гримом
		
		case "Memento_MortimerGrim_phantom_11":
			dialog.text = "Pourquoi vous vous êtes arrêté, collègue ? Vous avez changé d’avis ? Alors pourquoi avez-vous attaqué ?";
			link.l1 = "Grimm ? Mais tu es mort !";
			link.l1.go = "Memento_MortimerGrim_phantom_12";
		break;

		case "Memento_MortimerGrim_phantom_12":
			dialog.text = "Ha ! Ce qui est mort ne peut pas mourir. Et puis, tu vas un peu vite en besogne : tu as peut-être gagné l'abordage, mais survivras-tu ? C’est ce qu’on va voir !";
			link.l1 = "Ce combat est terminé depuis des semaines ! Tu es mort !";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Memento_Dich_EtapThree_Paluba_11");
		break;

		case "Memento_MortimerGrim_phantom_21":
			dialog.text = "Voilà, c’est fini. Félicitations pour ta victoire.";
			link.l1 = "Grimm ?";
			link.l1.go = "Memento_MortimerGrim_phantom_22";
			LAi_UseAtidoteBottle(pchar);
		break;

		case "Memento_MortimerGrim_phantom_22":
			dialog.text = "Tu sais, je suis content. Sincèrement content que tu m’aies tué. Pour de bon.";
			link.l1 = "De quoi parles-tu ?";
			link.l1.go = "Memento_MortimerGrim_phantom_23";
		break;

		case "Memento_MortimerGrim_phantom_23":
			dialog.text = "Je suis un lâche, collègue. Un lâche ordinaire et pitoyable qui a eu peur de la mort — comme des milliers d’hommes avant moi. Quand l’équipage est mort de la peste… et que c’était ma faute, j’ai perdu la raison. Un mois à dériver seul sur un navire de morts.";
			link.l1 = "Que s’est-il vraiment passé ?";
			link.l1.go = "Memento_MortimerGrim_phantom_24";
		break;

		case "Memento_MortimerGrim_phantom_24":
			dialog.text = "Je n’ai pas su affronter la mort. Au lieu de l’accepter, de survivre et d’en tirer une leçon, j’ai encore plus paniqué. Et pour étouffer cette peur… j’ai obligé les autres à traverser ce que j’avais vécu.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_phantom_25";
		break;

		case "Memento_MortimerGrim_phantom_25":
			dialog.text = "Merci, collègue. De m’avoir libéré de cette… existence. Maintenant, je sais vraiment qu’il n’y a pas de mort. Et je n’ai plus peur. Je n’ai plus personne à blâmer ni à asservir.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_phantom_26";
		break;

		case "Memento_MortimerGrim_phantom_26":
			dialog.text = "Ne sépare pas le ‘Memento’ de son capitaine. Mortimer… Le capitaine Mortimer était un homme bien. Retrouve-le à la Dominique. Et le navire… il t’acceptera.";
			link.l1 = "...";
			link.l1.go = "Memento_MortimerGrim_phantom_27";
		break;

		case "Memento_MortimerGrim_phantom_27":
			dialog.text = "Mortui vivos docent, collègue. Les morts enseignent aux vivants. Adieu.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Memento_Dich_EtapThree_Paluba_13");
		break;
		
	}
} 