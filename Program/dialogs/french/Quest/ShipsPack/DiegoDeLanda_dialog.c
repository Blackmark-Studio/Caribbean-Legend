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

		//--> Встреча
		case "DiegoDeLanda_Meeting":
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 1)
			{
				dialog.text = "Triste histoire, n'est-ce pas ?";
				link.l1 = "Qui êtes-vous ?";
				link.l1.go = "DiegoDeLanda_Meeting_2";
			}
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 2)
			{
				dialog.text = "Bonjour, capitaine.";
				link.l1 = "Attendez ! Nous nous sommes déjà rencontrés !";
				link.l1.go = "DiegoDeLanda_Meeting_2";
			}
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 3)
			{
				dialog.text = "Un. Deux. Trois.";
				link.l1 = "Mettons fin à cette mascarade. Qui êtes-vous vraiment ?";
				link.l1.go = "DiegoDeLanda_Meeting_Third_2";
			}
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 4)
			{

			}
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 5)
			{

			}
			DelLandQuestMark(npchar);
		break;

		case "DiegoDeLanda_Meeting_2":
			if (CheckAttribute(pchar, "questTemp.DiegoDeLanda_SantaMisericordia"))
			{
				dialog.text = "Savez-vous ce qu'il y a de spécial dans ce caveau ? Deux âmes y reposent, liées... par le sang. Le père et le fils de Alameda. L'un est tombé sous la main des pécheurs, l'autre... hm, a trouvé son chemin vers Dieu.";
				link.l1 = "Le journal de Don Fernando m'a conduit ici.";
				link.l1.go = "DiegoDeLanda_SantaMisericordia_2";
			}
			if (CheckAttribute(pchar, "questTemp.DiegoDeLanda_LadyBeth"))
			{
				dialog.text = "Vous avez vu Madame Bishop ? Un triste destin, n’est-ce pas ? Mais, j’en ai peur, mérité.";
				link.l1 = "Vous connaissez Elizabeth ?";
				link.l1.go = "DiegoDeLanda_LadyBeth_2";
			}
			if (CheckAttribute(pchar, "questTemp.DiegoDeLanda_Memento"))
			{
				dialog.text = "Mortimer Grim.";
				link.l1 = "Vous le connaissiez, bien sûr ?";
				link.l1.go = "DiegoDeLanda_Memento_2";
			}
		break;

		case "DiegoDeLanda_Meeting_Third_2":
			dialog.text = "\nEncore trois. Au compte de six, vous saurez tout.";
			link.l1 = "Si je n’obtiens pas de réponses claires tout de suite, alors je...";
			link.l1.go = "DiegoDeLanda_Meeting_Third_3";
		break;

		case "DiegoDeLanda_Meeting_Third_3":
			dialog.text = "\nVous avancez bien, capitaine. Vous méritez de connaître mon nom. Je m'appelle Diego de Landa.";
			link.l1 = "Êtes-vous vraiment un prêtre ?";
			link.l1.go = "DiegoDeLanda_Meeting_Third_4";
		break;

		case "DiegoDeLanda_Meeting_Third_4":
			dialog.text = "Avant tout, je suis un artiste. Mais ne nous précipitons pas...";
			link.l1 = "...";
			link.l1.go = "DiegoDeLanda_Meeting_2";
		break;
		//<-- Встреча
		
		//--> Святое Милосердие
		case "DiegoDeLanda_SantaMisericordia_2":
			dialog.text = "Ah... Le journal. Une chose étonnante — la parole écrite. Elle est comme... un sentier dans l'obscurité. Elle mène là où l'attend... une révélation. Notre paroisse rendait souvent visite à don Fernando. Surtout pendant la dernière année.";
			link.l1 = "Vous officiez dans la paroisse locale ? Vous connaissiez don Fernando ?";
			link.l1.go = "DiegoDeLanda_SantaMisericordia_3";
		break;

		case "DiegoDeLanda_SantaMisericordia_3":
			dialog.text = "...";
			link.l1 = "...";
			link.l1.go = "DiegoDeLanda_SantaMisericordia_4";
		break;

		case "DiegoDeLanda_SantaMisericordia_4":
			dialog.text = "J’ai... observé son chemin. Et ce livre que vous avez pris... Savez-vous ce qui le rend spécial ?";
			link.l1 = "Il semble ancien.";
			link.l1.go = "DiegoDeLanda_SantaMisericordia_5";
		break;

		case "DiegoDeLanda_SantaMisericordia_5":
			dialog.text = "Ancien ? Oh non. Il est... illuminé. La Bible de don de Alameda l'aîné. Chaque mot est comme un phare dans les ténèbres. Prenez-la. Aidez les frères en Christ et peut-être... elle vous mènera à quelque chose... de plus grand.";
			link.l1 = "...";
			link.l1.go = "DiegoDeLanda_leaving";
		break;
		//<-- Святое Милосердие
		
		//--> Леди Бет
		case "DiegoDeLanda_LadyBeth_2":
			dialog.text = "Oh oui. Pauvre femme. Son mari... n’est pas un homme bon. On dit que ses plantations sont les plus productives de la Barbade. Et les plus cruelles. Savez-vous combien d’esclaves meurent chaque mois? Récemment, il a battu à mort un véritable médecin venu d’Angleterre – un homme de grand savoir et de talent. Mais son sort à elle n’est guère meilleur, croyez-moi.";
			link.l1 = "Vous semblez bien informé.";
			link.l1.go = "DiegoDeLanda_LadyBeth_3";
		break;

		case "DiegoDeLanda_LadyBeth_3":
			dialog.text = "Les gens viennent me voir pour se confesser, capitaine. J'entends ce qu'ils ont peur de dire même à leurs proches. Leurs peurs, leurs péchés... leurs douleurs.";
			link.l1 = "Et vous n’avez pas peur de la persécution? Ce n’est pas facile pour un prêtre catholique sur les terres anglaises.";
			link.l1.go = "DiegoDeLanda_LadyBeth_4";
		break;

		case "DiegoDeLanda_LadyBeth_4":
			dialog.text = "Mes peurs ne sont rien comparées à ce que vous avez laissé derrière cette porte. Et ce livret que vous avez pris à cette pauvre femme… Si la peur avait une forme, elle ressemblerait à cela.\n"+
			"Bonne journée, capitaine.";
			link.l1 = "...";
			link.l1.go = "DiegoDeLanda_leaving";
		break;
		
		//<-- Леди Бет
		
		//--> Мементо
		case "DiegoDeLanda_Memento_2":
			dialog.text = "Tigre ! Tigre ! Peur brûlante\n"+
			"Dans la jungle de la nuit\n"+
			"Quel regard immortel, aimant, créa ton terrible éclat ?\n"+
			"Bien sûr que je le connaissais, capitaine. Mais vous, le connaissiez-vous ?";
			link.l1 = "Je n’ai jamais rencontré un homme au destin plus tragique.";
			link.l1.go = "DiegoDeLanda_Memento_3";
		break;

		case "DiegoDeLanda_Memento_3":
			dialog.text = "Vous en avez rencontré, mais vous ne l’avez pas encore compris.\n"+
			"Alors non, vous ne connaissiez pas Grim. Bien que vous teniez son crâne dans vos mains.";
			link.l1 = "Quoi ?!";
			link.l1.go = "DiegoDeLanda_Memento_4";
		break;

		case "DiegoDeLanda_Memento_4":
			dialog.text = "Ce n’est pas chrétien de traiter un défunt ainsi. Tenez, prenez ce petit guide post mortem. Mon cadeau.\n"+
			"Bonne journée, capitaine.";
			link.l1 = "...";
			link.l1.go = "DiegoDeLanda_leaving";
			SetAlchemyRecipeKnown("blade_SP_3low");	// рецепты от Катласа
			SetAlchemyRecipeKnown("blade_SP_3");
		break;
		
		//<-- Мементо
		
		//--> Прощание
		case "DiegoDeLanda_Leaving":
			DialogExit();
			AddDialogExitQuestFunction("DiegoDeLanda_Leaving");
		break;
		
		case "DiegoDeLanda_Leaving_1":
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 1)
			{
				dialog.text = "Dites-moi... Pourquoi ? C'était dangereux et stupide. Quel est votre feu, capitaine ? Qu'est-ce qui vous pousse ?";
				link.l1 = "Cela ne vous regarde pas.";
				link.l1.go = "DiegoDeLanda_leaving_First_2";
			}
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 2)
			{
				dialog.text = "Le deuxième.";
				link.l1 = "La dernière fois, vous parliez en énigmes. Ce sera encore le cas ?";
				link.l1.go = "DiegoDeLanda_leaving_Second_2";
			}
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 3)
			{
				dialog.text = "...";
				link.l1 = "Attendez, de Landa. Je ne peux pas juste vous laisser partir comme ça.";
				link.l1.go = "DiegoDeLanda_Leaving_Third_2";
			}
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 4)
			{

			}
			if (sti(pchar.questTemp.ISawDiegoDeLanda) == 5)
			{

			}
		break;

		case "DiegoDeLanda_Leaving_First_2": // Первое прощание
			dialog.text = "Je ne comprends pas. Les autres - oui. Mais vous - pas encore.";
			link.l1 = "Les autres ?";
			link.l1.go = "DiegoDeLanda_Leaving_First_3";
		break;

		case "DiegoDeLanda_Leaving_First_3":
			dialog.text = "L’un, par exemple, cherche la justice. Il y en avait un autre... obsédé par les eaux sombres de la mort. Les gens se perdent si facilement dans leurs désirs. N'est-ce pas ?";
			link.l1 = "Vous êtes un drôle de prêtre, mon père.";
			link.l1.go = "DiegoDeLanda_Leaving_First_4";
		break;

		case "DiegoDeLanda_Leaving_First_4":
			dialog.text = "...";
			link.l1 = "Je vais y aller.";
			link.l1.go = "DiegoDeLanda_Leaving_First_5";
		break;

		case "DiegoDeLanda_Leaving_First_5":
			dialog.text = "Bien sûr. Votre travail ne fait que commencer, capitaine.";
			link.l1 = "...";
			link.l1.go = "DiegoDeLanda_Leaving_End";
		break;
		
		case "DiegoDeLanda_leaving_Second_2": // Второе прощание
			dialog.text = "\nUn vrai mystère se tient devant moi. Vous avez déjà rassemblé deux… reliques. Aimez-vous collectionner de telles choses ? Êtes-vous un collectionneur ?";
			link.l1 = "Comment le savez-vous ?";
			link.l1.go = "DiegoDeLanda_leaving_Second_3";
		break;

		case "DiegoDeLanda_leaving_Second_3":
			dialog.text = "Un chasseur de trophées ?";
			link.l1 = "Je répète ma question : comment le savez-vous ?";
			link.l1.go = "DiegoDeLanda_leaving_Second_4";
		break;

		case "DiegoDeLanda_leaving_Second_4":
			dialog.text = "Un amateur de sensations fortes ?";
			link.l1 = "...";
			link.l1.go = "DiegoDeLanda_leaving_Second_5";
		break;

		case "DiegoDeLanda_leaving_Second_5":
			dialog.text = "\nAh. Mais bien sûr. Évidemment. Eh bien, capitaine, je ne vais pas vous retenir.";
			link.l1 = "Attendez, mon père. Vous n’avez toujours pas répondu à ma question.";
			link.l1.go = "DiegoDeLanda_leaving_Second_6";
		break;

		case "DiegoDeLanda_leaving_Second_6":
			dialog.text = "Oh, capitaine. Je ne peux pas. Parfois, les réponses font plus de mal que l'ignorance. Allez en paix. Et gardez votre collection... de trophées. Elle pourrait vous être utile pour le voyage à venir.";
			link.l1 = "...";
			link.l1.go = "DiegoDeLanda_Leaving_End";
		break;

		case "DiegoDeLanda_Leaving_Third_2": // Третье прощание
			dialog.text = "Allons, capitaine. N’êtes-vous pas curieux ? N’est-ce pas amusant ? Avez-vous assez de trophées ?\n"+
			"Voilà votre feu, capitaine. Vous voulez savoir ce qui vient ensuite. Vous aimez les beaux navires et les objets fascinants\n"+
			"Vous ne pouvez tout simplement pas vous empêcher de tous les collectionner.\n"+
			"\n"+
			"Vous pouvez me tirer dessus tout de suite.";
			link.l1 = "Quoi ?";
			link.l1.go = "DiegoDeLanda_Leaving_Third_3";
		break;
		
		case "DiegoDeLanda_Leaving_Third_3":
			dialog.text = "Allez-y. Mais alors vous ne saurez pas tout et vous ne recevrez pas l'ensemble complet de trophées. Les navires, cependant, vous les aurez tous\n"+
			"Bonne journée, capitaine.";
			link.l1 = "(Le laisser partir)";
			link.l1.go = "DiegoDeLanda_Leaving_End";
			link.l2 = "(Tirer)";
			link.l2.go = "DiegoDeLanda_Leaving_Shoot";
		break;
		
		case "DiegoDeLanda_Leaving_End":
			DialogExit();
			AddDialogExitQuestFunction("DiegoDeLanda_Leaving_End");
		break;
		
		case "DiegoDeLanda_Leaving_Shoot":
			DialogExit();
			AddDialogExitQuestFunction("DiegoDeLanda_Leaving_Shoot");
		break;
		
		
		//<-- Прощание
	}
} 