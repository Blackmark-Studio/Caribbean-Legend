int iClockSP4PseudoGlobal = SOUND_INVALID_ID;

void ProcessDialogEvent()
{
	ref NPChar, sld, realShip;
	aref Link, NextDiag, arTmp;
	int i, n, NextMonth, idx;
	string sTemp, sStr, Month, NationName, shipType;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	if (HasSubStr(Dialog.CurrentNode, "chosenIdx/"))
	{
		Dialog.tmpIdx = FindStringAfterChar(Dialog.CurrentNode, "/");
		Dialog.CurrentNode = FindStringBeforeChar(Dialog.CurrentNode, "/");
	}

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
		
		// Диалог с Йоханом
		case "ClockTower_Johan_1":
			dialog.text = "Halte, "+GetTitle(NPChar, true)+". Passage interdit au-delà de ce point.";
			link.l1 = "Pourquoi donc?";
			link.l1.go = "ClockTower_Johan_2";
			DelLandQuestMark(npchar);
		break;

		case "ClockTower_Johan_2":
			dialog.text = "Vous voyez cette tour? Bureau de la Compagnie des Indes occidentales. Département d'enregistrement des navires et archives. Entrée sur rendez-vous uniquement.";
			link.l1 = "Et comment obtient-on un rendez-vous?";
			link.l1.go = "ClockTower_Johan_3";
		break;

		case "ClockTower_Johan_3":
			dialog.text = "Ceux qui ont besoin de savoir le savent. Le mynheer directeur ne travaille pas avec n'importe qui.";
			link.l1 = "«Mynheer directeur?» Qui est-ce?";
			link.l1.go = "ClockTower_Johan_4";
		break;

		case "ClockTower_Johan_4":
			dialog.text = "L'intendant van Doorn. Ce n'est peut-être pas vraiment un directeur, mais tout le monde l'appelle comme ça. Il travaille ici depuis dix ans — il a mis de l'ordre partout. Maintenant, tous les navires des Caraïbes passent par son bureau.";
			link.l1 = "Tous les navires? Même les vaisseaux de guerre?";
			link.l1.go = "ClockTower_Johan_5";
		break;

		case "ClockTower_Johan_5":
			dialog.text = "Seulement les meilleurs navires et les capitaines les plus fortunés. Être client de notre bureau est un grand honneur!";
			link.l1 = "Quel genre de services offrez-vous?";
			link.l1.go = "ClockTower_Johan_6";
		break;

		case "ClockTower_Johan_6":
			dialog.text = "Je ne suis pas au courant des détails — je garde simplement l'entrée. Mais j'ai entendu dire que les gens repartent satisfaits.";
			link.l1 = "Impressionnant.";
			link.l1.go = "ClockTower_Johan_7";
		break;

		case "ClockTower_Johan_7":
			dialog.text = "Et je vais vous dire autre chose. Vous voyez cette horloge? Une merveille européenne — vous n'en trouverez pas de pareille dans notre coin perdu. Le mynheer directeur l'entretient personnellement.";
			link.l1 = "Peut-être pourrions-nous nous arranger?";
			link.l1.go = "ClockTower_Johan_8_1";
			link.l2 = "Il n'y a vraiment rien que je puisse faire pour entrer?";
			link.l2.go = "ClockTower_Johan_8_2";
		break;

		case "ClockTower_Johan_8_1":
			dialog.text = "Je ne prends pas de pots-de-vin!";
			link.l1 = "Excusez-moi. Vous êtes un brave homme. Comment vous appelez-vous?";
			link.l1.go = "ClockTower_Johan_9";
		break;

		case "ClockTower_Johan_9":
			dialog.text = ""+npchar.name+"... Ecoutez... Je comprends que vous n'êtes pas d'ici. Mais ici, il y a de l'ordre. Le mynheer directeur dit toujours : montrez de la faiblesse une fois, et notre tour s'effondre. Vous voulez entrer? Aidez la ville — et on vous remarquera.";
			link.l1 = "Comprendu. Soyez prudent, soldat.";
			link.l1.go = "ClockTower_Johan_11";
		break;

		case "ClockTower_Johan_8_2":
			dialog.text = "Eh bien, je ne sais pas. Le mynheer directeur récompense les amis de Willemstad. Aidez la ville — et on vous remarquera. Je comprends que vous n'êtes pas d'ici. Mais ici, il y a de l'ordre. Le mynheer directeur dit toujours : montrez de la faiblesse une fois, et notre tour s'effondre.";
			link.l1 = "Comprendu. Et comment vous appelez-vous?";
			link.l1.go = "ClockTower_Johan_10";
		break;

		case "ClockTower_Johan_10":
			dialog.text = ""+npchar.name+", "+GetTitle(NPChar, true)+".";
			link.l1 = "Et moi, je suis "+GetTitle(NPChar, false)+" "+GetFullName(pchar)+". Soyez prudent, soldat.";
			link.l1.go = "ClockTower_Johan_11";
		break;
		
		case "ClockTower_Johan_11":
			DialogExit();
			AddDialogExitQuestFunction("ClockTower_Quest_1");
		break;
		
		case "ClockTower_Johan_repeat":
			if (ChangeCharacterNationReputation(pchar, HOLLAND, 0) >= 51)
			{
				dialog.text = ""+UpperFirst(GetTitle(NPChar, true))+"!";
				link.l1 = "Il s'est passé quelque chose ?";
				link.l1.go = "ClockTower_Johan_22";
				Notification_ReputationNation(true, 51, HOLLAND);
			}
			else 
			{
				dialog.text = ""+Greeting(true)+", "+GetTitle(NPChar, true)+". Puis-je vous aider ?";
				link.l1 = "Non, "+npchar.name+". Continue.";
				link.l1.go = "exit";
				NextDiag.TempNode = "ClockTower_Johan_repeat";
				Notification_ReputationNation(false, 51, HOLLAND);
			}
		break;
		
		case "ClockTower_Johan_21":
			dialog.text = ""+UpperFirst(GetTitle(NPChar, true))+"!";
			link.l1 = "Il s'est passé quelque chose ?";
			link.l1.go = "ClockTower_Johan_22";
			DelLandQuestMark(npchar);
		break;

		case "ClockTower_Johan_22":
			dialog.text = "Félicitations. Vous avez un rendez-vous de prévu.";
			link.l1 = "Un rendez-vous ? Avec qui ?";
			link.l1.go = "ClockTower_Johan_23";
		break;

		case "ClockTower_Johan_23":
			dialog.text = "Avec l'adjoint du mynheer directeur. Il a entendu parler de votre aide à la ville et m'a ordonné de vous inviter.";
			link.l1 = "Et le directeur lui-même ?";
			link.l1.go = "ClockTower_Johan_24";
		break;

		case "ClockTower_Johan_24":
			dialog.text = "Euh... Je ne suis pas autorisé à vous en parler. Bonne chance là-dedans, mynheer capitaine.";
			link.l1 = "Merci.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_InvitationToTheTower");
		break;
		
		// Диалог с Маартеном Виссером, заместителем директора
		case "ClockTower_Visser_1":
			dialog.text = "Bienvenue au département d'enregistrement des navires de la CNIOC. "+UpperFirst(GetTitle(NPChar, false))+"?..";
			link.l1 = ""+GetFullName(pchar)+".";
			link.l1.go = "ClockTower_Visser_2";
			DelLandQuestMark(npchar);
		break;

		case "ClockTower_Visser_2":
			dialog.text = ""+GetFullName(NPChar)+", directeur adjoint.\n"+
						 "J'ai entendu dire que vous avez été très utile à Willemstad. Peut-être notre bureau peut-il vous être utile à son tour.";
			link.l1 = "C'est pour cela que je suis ici.";
			link.l1.go = "ClockTower_Visser_3_1";
			link.l2 = "Je suis heureux d'avoir pu rendre service à la capitale de Curaçao.";
			link.l2.go = "ClockTower_Visser_3_2";
		break;

		case "ClockTower_Visser_3_1":
			dialog.text = "N'importe quel capitaine — français, espagnol, néerlandais — peut nous commander un audit de navire. Nous inspectons le gréement, les canons, l'accastillage. Nous trouvons les points faibles, donnons des recommandations.";
			link.l1 = "";
			link.l1.go = "ClockTower_Visser_4";
		break;

		case "ClockTower_Visser_3_2":
			dialog.text = "N'importe quel capitaine — français, espagnol, néerlandais — peut nous commander un audit de navire. Nous inspectons le gréement, les canons, l'accastillage. Nous trouvons les points faibles, donnons des recommandations.";
			link.l1 = "";
			link.l1.go = "ClockTower_Visser_4";
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
		break;

		case "ClockTower_Visser_4":
			dialog.text = "Et si un audit ne suffit pas, nous pouvons aussi procurer de nouveaux documents de bord. En d'autres termes, le travail de notre bureau améliorera votre navire — sans dépenser d'acajou ou de soie précieux.";
			link.l1 = "Comment est-ce possible?";
			link.l1.go = "ClockTower_Visser_4_1";
		break;

		case "ClockTower_Visser_4_1":
			dialog.text = ""+UpperFirst(GetTitle(NPChar, false))+"? Vous n'avez aucune idée du pouvoir de l'endroit où vous êtes entré, et de tout ce qu'un simple trait de plume peut accomplir.";
			link.l1 = "Contre des doublons, je présume?";
			link.l1.go = "ClockTower_Visser_5";
		break;

		case "ClockTower_Visser_5":
			dialog.text = "Naturellement. Nos services ne sont pas bon marché et dépendent de la taille de votre navire. Mais ils sont toujours rentables. Un capitaine qui est passé par nos portes échoue rarement\n"+
						 "Cependant, nous ne prenons pas seulement votre or — nous vous donnons aussi l'occasion d'en gagner. Les pirates se sont tellement multipliés que même dans les Petites Antilles, les capitaines doivent équiper des escadres pour chasser cette vermine. Apportez des preuves d'élimination — et vous recevrez un paiement dans ces mêmes doublons.";
			link.l1 = "Quel genre de preuves?";
			link.l1.go = "ClockTower_Visser_6";
		break;

		case "ClockTower_Visser_6":
			dialog.text = "Les journaux de bord. Même cette racaille doit tenir un semblant de documentation — sinon on ne peut pas vraiment commander ne serait-ce qu'un lougre. Outre le fait que les journaux constituent une preuve absolue de méfaits, ils trouvent toujours une place dans nos archives. Utile pour les litiges d'assurance\n"+
						 "Si nos services vous intéressent, une place s'est libérée dans notre liste de clients — l'un de nos capitaines a récemment mis fin à sa collaboration. Accomplissez le travail — et la place est à vous.";
			link.l1 = "Pourquoi ces complications? Mes doublons ne suffisent-ils pas?";
			link.l1.go = "ClockTower_Visser_7";
		break;

		case "ClockTower_Visser_7":
			dialog.text = ""+UpperFirst(GetTitle(NPChar, false))+", Nous privilégions la qualité, pas la quantité. Chaque client de notre bureau reçoit le meilleur service et l'attention personnelle du mynheer directeur lui-même. Et ce dernier point, croyez-moi, coûte une somme considérable même pour notre compagnie loin d'être pauvre. Puisqu'il n'y a que trente jours dans un mois, nous ne pouvons nous permettre que trente clients.";
			link.l1 = "Que faut-il faire?";
			link.l1.go = "ClockTower_Visser_8";
		break;

		case "ClockTower_Visser_8":
			dialog.text = "Apportez cinq journaux de bord de pirates — cela prouvera votre efficacité. La récompense dépend du degré de dangerosité de leurs propriétaires.";
			link.l1 = "Très bien. Je le ferai.";
			link.l1.go = "ClockTower_Visser_9_1";
			link.l2 = "J'ai besoin d'y réfléchir.";
			link.l2.go = "ClockTower_Visser_9_2";
			link.l3 = "Où est le directeur lui-même?";
			link.l3.go = "ClockTower_Visser_9_3";
		break;

		case "ClockTower_Visser_9_1":
			dialog.text = "Excellent. J'attends les résultats et j'espère une collaboration fructueuse.";
			link.l1 = ""+Goodbye(true)+".";
			link.l1.go = "ClockTower_Visser_13_exit";
		break;

		case "ClockTower_Visser_9_2":
			dialog.text = "Comme vous voulez. L'offre tient toujours. Mais votre place pourrait être prise plus vite que vous ne le pensez.";
			link.l1 = ""+Goodbye(true)+".";
			link.l1.go = "ClockTower_Visser_13_exit";
		break;

		case "ClockTower_Visser_9_3":
			dialog.text = "En mer. Le mynheer van Doorn combine la gestion du bureau avec le commandement du vaisseau amiral.";
			link.l1 = "Comment y parvient-il?";
			link.l1.go = "ClockTower_Visser_10";
		break;

		case "ClockTower_Visser_10":
			dialog.text = "Il travaille dix-huit heures par jour. Dort ici, dans le bureau à l'étage. Il dit que le sommeil est une perte de temps. Quatre heures lui suffisent.";
			link.l1 = "Et le vacarme de ces énormes mécanismes d'horlogerie? Comment peut-on dormir ici?";
			link.l1.go = "ClockTower_Visser_11";
		break;

		case "ClockTower_Visser_11":
			dialog.text = "Vous pourrez lui demander vous-même et peut-être apprendre quelque chose. Il est toujours ravi de parler avec les clients. Nous nous comprenons?";
			link.l1 = "Parfaitement.";
			link.l1.go = "ClockTower_Visser_12";
			link.l2 = "Pas tout à fait...";
			link.l2.go = "ClockTower_Visser_12";
		break;

		case "ClockTower_Visser_12":
			dialog.text = "Bonne journée, "+GetTitle(NPChar, false)+".";
			link.l1 = ""+Goodbye(true)+".";
			link.l1.go = "ClockTower_Visser_13_exit";
		break;

		case "ClockTower_Visser_13_exit":
			DialogExit();
			AddDialogExitQuestFunction("ClockTower_Quest_2");
		break;
		
		// Йохан спрашивает про журналы
		case "ClockTower_Johan_31":
			dialog.text = ""+UpperFirst(GetTitle(NPChar, true))+" ! Avez-vous les journaux avec vous ?";
			link.l1 = "Je vois que tu es bien informé, Johan.";
			link.l1.go = "ClockTower_Johan_32";
			DelLandQuestMark(npchar);
		break;

		case "ClockTower_Johan_32":
			if (!CheckAttribute(npchar, "questTemp.ClockTower_Johan_journal"))
			{
				dialog.text = "Ha ! Ce n'est ni le quai ni les portes de la ville, et je ne suis pas un simple garde en faction, mais un employé de la compagnie.";
				npchar.questTemp.ClockTower_Johan_journal = true;
			}
			else
			{
				dialog.text = ""+UpperFirst(GetTitle(NPChar, true))+" ! Avez-vous les journaux avec vous ?";
			}
			if (ClockTower_JournalsQty() >= 5 || bBettaTestMode)
			{
				link.l1 = "J'ai apporté les journaux. Tu me laisses passer ?";
				link.l1.go = "ClockTower_Johan_33";
			}
			link.l2 = "Une autre fois.";
			link.l2.go = "ClockTower_Johan_34";
		break;

		case "ClockTower_Johan_33":
			dialog.text = "Ravi que ça ait marché ! Allez-y, on vous attend.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_InvitationToTheTower_2");
		break;

		case "ClockTower_Johan_34":
			dialog.text = "Passez une bonne journée, mynheer capitaine.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ClockTower_Johan_32";
		break;
		
		case "ClockTower_Visser_21":
			dialog.text = "Capitaine ! Vous êtes de retour. Avez-vous apporté les journaux ?";
			if (ClockTower_JournalsQty() >= 5 || bBettaTestMode)
			{
				link.l1 = "Oui. Les cinq.";
				link.l1.go = "ClockTower_Visser_22";
				DelLandQuestMark(npchar);
			}
			else
			{
				link.l1 = "Une autre fois.";
				link.l1.go = "exit";
				NextDiag.TempNode = "ClockTower_Visser_21";
			}
		break;

		case "ClockTower_Visser_22":
			dialog.text = "Excellent. Montrez-les moi.\n"+
						"Oui, tout est en ordre. Ce sont des navires pirates authentiques. Bon travail. Vous avez droit à #количество_дублонов doublons.\n"+
						"Je vous en prie, prenez-les. Et signez ici aussi, s'il vous plaît.";
			link.l1 = "Donc je suis sur la liste ?";
			link.l1.go = "ClockTower_Visser_23";
			//RemoveItemsFromPCharTotal("ClockTower_PirateJournal", 5);     
		break;

		case "ClockTower_Visser_23":
			dialog.text = "Presque. D'abord, nous devons remplir les documents. Ça prendra quelques minutes.\n"+
						"Nom complet ?";
			link.l1 = ""+GetFullName(pchar)+".";
			link.l1.go = "ClockTower_Visser_24";
		break;

		case "ClockTower_Visser_24":
			dialog.text = "Nationalité ?";
			link.l1 = ""+NationNameNominative(sti(pchar.baseNation))+".";
			link.l1.go = "ClockTower_Visser_25";
		break;

		case "ClockTower_Visser_25":
			dialog.text = "Nom de votre navire ?";
			link.l1 = ""+PChar.Ship.Name+".";
			link.l1.go = "ClockTower_Visser_26";
		break;

		case "ClockTower_Visser_26":
			shipType = XI_ConvertString(GetShipTypeName(pchar));
			dialog.text = "Type de navire ?";
			link.l1 = ""+shipType+".";
			link.l1.go = "ClockTower_Visser_27";
		break;

		case "ClockTower_Visser_27":
			dialog.text = "Nombre de canons ?";
			link.l1 = ""+GetCannonQuantity(pchar)+".";
			link.l1.go = "ClockTower_Visser_28";
		break;

		case "ClockTower_Visser_28":
			dialog.text = "Taille de l'équipage ?";
			link.l1 = ""+GetMaxCrewQuantity(pchar)+".";
			link.l1.go = "ClockTower_Visser_29";
		break;

		case "ClockTower_Visser_29":
			dialog.text = "Bien. Maintenant signez ici. Et ici. Et ici aussi.";
			link.l1 = "C'est tout ?";
			link.l1.go = "ClockTower_Visser_30";
		break;

		case "ClockTower_Visser_30":
			dialog.text = "Presque. Reste uniquement à vous inscrire au registre. Bien sûr, le mynheer directeur devrait vous rencontrer personnellement d'abord... Mais c'est une formalité — je suis autorisé à accepter de nouveaux clients.\n"+
					"...Mais je m'égare. Permettez-moi de vous familiariser à nouveau avec notre liste de services.\n"+
					"Assurance. Cher, mais aucune escadre navale ne touchera les navires assurés par la compagnie. Vous pourrez garder autant de navires que vous désirez dans les administrations portuaires sans craindre de les perdre durant un siège colonial.\n"+
					"Audit de navire — augmente légèrement toutes les caractéristiques sans dépenser de biens stratégiques. Nous examinerons tout : gréement, cale, quartiers d'équipage. Donnerons des recommandations. Le prix dépend de la taille du navire.\n"+
					"Inscription dans notre registre. Accroît la sécurité du navire dans la région des Caraïbes, de sorte que les chasseurs de primes, les pirates et les militaires réfléchiront à deux fois avant de vous attaquer.\n"+
					"Audit et inscription ne peuvent être effectués qu'une seule fois pour un navire particulier. Alors si vous avez déjà investi, prenez soin de votre navire. Vous n'imaginez pas à quel point ça irrite mes supérieurs quand les capitaines traitent leurs navires négligemment et les changent comme des gants !\n"+
					"Mais je m'égare encore. Maintenant, concernant les services répétables...\n"+
					"Remplacement de documents. Vous savez que les navires peuvent avoir différentes spécialisations. Mais vous ne soupçonnez même pas que cela dépend principalement de la façon dont le navire est documenté. Si vous n'aimez pas que votre navire de guerre soit documenté pour les sièges de forts, vous savez à qui vous adresser.\n"+
					"Bon, quant aux récompenses pour la remise des journaux de bord pirates que vous avez déjà entendu... Plus le pirate est dangereux, plus nous payerons pour son journal.";
			link.l1 = "Impressionnant. Je dois dire, mynheer Visser, que votre bureau est vraiment...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_AmsterdamInTheHarbor");
		break;

		case "ClockTower_Visser_31":
			dialog.text = "'"+GetShipName("Amsterdam")+"' au port ! Le mynheer directeur est de retour !";
			link.l1 = "";
			link.l1.go = "ClockTower_Visser_31_add";
			CharacterTurnByChr(CharacterFromID("ClockTower_Johan_Clone"), CharacterFromID("ClockTower_Visser"));
			ClockTower_AmsterdamInTheHarbor_2();
		break;

		case "ClockTower_Visser_31_add":
			StartInstantDialogNoType("ClockTower_Visser", "ClockTower_Visser_32", "Quest\ShipsPack\ClockTower_dialog.c");
		break;

		case "ClockTower_Visser_32":
			dialog.text = "Quoi ?! Déjà ?! Mais il ne devait revenir que dans trois jours !";
			link.l1 = "...";
			link.l1.go = "ClockTower_Visser_32_add";
		break;

		case "ClockTower_Visser_32_add":
			StartInstantDialog("ClockTower_Johan_clone", "ClockTower_Visser_33", "Quest\ShipsPack\ClockTower_dialog.c");
		break;

		case "ClockTower_Visser_33":
			dialog.text = "Le mynheer directeur est déjà à terre ! Il vient directement ici !";
			link.l1 = "...";
			link.l1.go = "ClockTower_Visser_33_add";
			CharacterTurnByChr(CharacterFromID("ClockTower_Johan_Clone"), CharacterFromID("ClockTower_Visser"));
		break;

		case "ClockTower_Visser_33_add":
			StartInstantDialogNoType("ClockTower_Visser", "ClockTower_Visser_34", "Quest\ShipsPack\ClockTower_dialog.c");
		break;

		case "ClockTower_Visser_34":
			dialog.text = "Mon Dieu... Si il vous voit...";
			link.l1 = "Quel est le problème ? Vous venez de dire que vous êtes autorisé à accepter de nouveaux clients.";
			link.l1.go = "ClockTower_Visser_35";
		break;

		case "ClockTower_Visser_35":
			dialog.text = "Je le suis ! Mais il n'aime pas quand... Peu importe. Capitaine, attendez dehors. À l'entrée. Le mynheer directeur voudra vous parler.";
			link.l1 = "Avec moi ?";
			link.l1.go = "ClockTower_Visser_36";
		break;

		case "ClockTower_Visser_36":
			dialog.text = "Il examine personnellement chaque nouveau client. Toujours. Allez, vite !";
			link.l1 = "Je ne vais pas rendre les doublons pour les journaux !";
			link.l1.go = "ClockTower_Visser_36_1";
			link.l2 = "Dommage, j'aurais aimé rester et écouter.";
			link.l2.go = "ClockTower_Visser_36_2";
		break;

		case "ClockTower_Visser_36_1":
			DialogExit();
			AddCharacterExpToSkill(pchar, "Commerce", 100);
			AddDialogExitQuestFunction("ClockTower_AmsterdamInTheHarbor_Kino_1");
		break;

		case "ClockTower_Visser_36_2":
			DialogExit();
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			AddDialogExitQuestFunction("ClockTower_AmsterdamInTheHarbor_Kino_1");
		break;
		
		// диалог с Йоханом, после того как мы вышли из башни
		case "ClockTower_Johan_41":
			dialog.text = "...";
			link.l1 = "C'était quoi, Johan ?";
			link.l1.go = "ClockTower_Johan_42";
			DelLandQuestMark(npchar);
		break;

		case "ClockTower_Johan_42":
			dialog.text = "Le mynheer directeur est de retour.";
			link.l1 = "Qu'est-ce qu'il y a de si terrible ?";
			link.l1.go = "ClockTower_Johan_43";
		break;

		case "ClockTower_Johan_43":
			dialog.text = "Rien de terrible ! C'est juste que... Le mynheer directeur n'aime pas les surprises. Tout doit se dérouler comme prévu. Et voilà un nouveau client qu'il n'a pas encore vérifié.";
			link.l1 = "Maarten a dit qu'il avait l'autorité pour m'inscrire au registre.";
			link.l1.go = "ClockTower_Johan_44";
		break;

		case "ClockTower_Johan_44":
			dialog.text = "Non, ce n'est pas ça. Le mynheer directeur veut juste... eh bien, il veut tout contrôler lui-même. Chaque petit détail. Il dit que sinon tout s'effondrera. Vous verrez, maintenant il va recommencer à s'inquiéter pour son horloge.";
			link.l1 = "Quoi ?";
			link.l1.go = "ClockTower_Johan_45";
		break;

		case "ClockTower_Johan_45":
			dialog.text = "Mynheer van Doorn, quand il s'énerve, arrête l'horloge et commence à bricoler dedans. Parfois la ville reste sans heure pendant une demi-journée. Et ça arrive...";
			link.l1 = "...";
			link.l1.go = "ClockTower_Johan_45_1";
		break;

		case "ClockTower_Johan_45_1":
			dialog.text = "Oh... Vous entendez ? Ça a commencé.";
			link.l1 = "Le patron est de retour. Routine habituelle.";
			link.l1.go = "ClockTower_Johan_46_1";
			link.l2 = "Je l'entends bien. Ils passent un savon à Maarten.";
			link.l2.go = "ClockTower_Johan_46_2";
			iClockSP4PseudoGlobal = ClockTower_PlaySound_rh2("Location/SP4_quest2");
		break;

		case "ClockTower_Johan_46_1":
			dialog.text = "Malheureusement, c'est devenu habituel.";
			link.l1 = "...";
			link.l1.go = "ClockTower_Johan_47";

			if (iClockSP4PseudoGlobal != SOUND_INVALID_ID)
				SendMessage(Sound, "lll", MSG_SOUND_EVENT_STOP, iClockSP4PseudoGlobal, 0);
			ClockTower_PlaySound_rh2("Location/SP4_quest3");
		break;

		case "ClockTower_Johan_46_2":
			dialog.text = "Vous ne devriez pas dire ça. Ce n'est pas juste, si vous voulez mon avis.";
			link.l1 = "...";
			link.l1.go = "ClockTower_Johan_47";	
			ChangeCharacterComplexReputation(pchar, "nobility", -2);

			if (iClockSP4PseudoGlobal != SOUND_INVALID_ID)
				SendMessage(Sound, "lll", MSG_SOUND_EVENT_STOP, iClockSP4PseudoGlobal, 0);
			ClockTower_PlaySound_rh2("Location/SP4_quest3");
		break;

		case "ClockTower_Johan_47":
			dialog.text = "On dirait que ça s'est calmé. Ils vont vous inviter à entrer bientôt.";
			link.l1 = "Vais-je avoir des ennuis ?";
			link.l1.go = "ClockTower_Johan_48";
		break;

		case "ClockTower_Johan_48":
			dialog.text = "Ne vous inquiétez pas. Vous n'avez rien fait de mal.";
			link.l1 = "C'est rassurant.";
			link.l1.go = "ClockTower_Johan_49";
		break;

		case "ClockTower_Johan_49":
			dialog.text = "Allons donc ! Le mynheer directeur peut être trop strict parfois... Mais il est généreux et poli... Oh, je vous l'avais dit !";
			link.l1 = "...";
			link.l1.go = "ClockTower_Johan_50";
		break;

		case "ClockTower_Johan_50":
			dialog.text = "Oh, je vous l'avais dit !";
			link.l1 = "...";
			link.l1.go = "exit";
			ClockTower_VisserComingTowardsUs();
		break;

		case "ClockTower_Visser_37":
			dialog.text = "Le mynheer directeur vous attend à l'intérieur.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_VisserComingTowardsUs_2");
			DelLandQuestMark(npchar);
		break;
		
		// Первое знакомство с ван Дорном
		case "ClockTower_VanDoorn_1":
			NationName = GetSexPhrase(""+NationNameMan(sti(pchar.baseNation))+"",""+NationNameWoman(sti(pchar.baseNation))+"");
			shipType = LowerFirst(XI_ConvertString(GetShipTypeName(pchar)));
			dialog.text = ""+UpperFirst(GetTitle(NPChar, false))+" "+GetFullName(pchar)+", "+NationName+". Votre navire — '"+PChar.Ship.Name+"', "+shipType+". "+GetCannonQuantity(pchar)+" canons et "+GetMaxCrewQuantity(pchar)+" membres d'équipage.";
			link.l1 = "Tout est correct.";
			link.l1.go = "ClockTower_VanDoorn_2";
			DelLandQuestMark(npchar);
		break;

		case "ClockTower_VanDoorn_2":
			shipType = XI_ConvertString(GetShipTypeName(npchar));
			dialog.text = "C'est injuste que je sache tout de vous alors que vous ne savez rien de moi hormis les ragots de Johan. Hendrik van Doorn. Directeur du département d'enregistrement de la Compagnie néerlandaise des Indes occidentales dans les Caraïbes. Commandant de la frégate Amsterdam. "+shipType+". "+GetCannonQuantity(npchar)+" canons et "+GetMaxCrewQuantity(npchar)+" membres d'équipage.";
			link.l1 = "Ravi de faire votre connaissance.";
			link.l1.go = "ClockTower_VanDoorn_3";
		break;

		case "ClockTower_VanDoorn_3":
			dialog.text = "Vous avez obtenu cinq journaux de bord pirates. Mon adjoint vous a tenu en haute estime, vous a inscrit au registre des clients et vous a familiarisé avec les services de mon bureau.\n"+
						"Mais la décision finale sur l'admission est toujours la mienne. Personnellement. Après un entretien. Maarten pouvait proposer un candidat — rien de plus.";
			link.l1 = "Alors, commençons.";
			link.l1.go = "ClockTower_VanDoorn_4";
		break;

		case "ClockTower_VanDoorn_4":
			if (!CheckAttribute(npchar, "ClockTower_option"))
			{
				dialog.text = "J'ai besoin de capitaines qui combattent efficacement les pirates tout en ayant suffisamment de succès commercial pour se permettre nos services. Répondez-vous à ces critères?";
			}
			else dialog.text = "";
			if (!CheckAttribute(npchar, "ClockTower_option_1") && CheckAttribute(pchar, "questTemp.DiegoDeLanda_Memento"))
			{
				link.l1 = "J'ai détruit Mortimer Grimm. Capitaine du brick Memento.";
				link.l1.go = "ClockTower_VanDoorn_option_1";
			}
			if (!CheckAttribute(npchar, "ClockTower_option_2") && CheckAttribute(pchar, "questTemp.DiegoDeLanda_LadyBeth"))
			{
				link.l2 = "Je crois que votre compagnie a grandement apprécié ma victoire sur Albert Blackwood. Le senau Lady Beth était un adversaire redoutable.";
				link.l2.go = "ClockTower_VanDoorn_option_2";
			}
			if (!CheckAttribute(npchar, "ClockTower_option_3") && CheckAttribute(pchar, "questTemp.DiegoDeLanda_SantaMisericordia"))
			{
				link.l3 = "Fernando de Alamida n'était pas un pirate, mais...";
				link.l3.go = "ClockTower_VanDoorn_option_3";
			}
			if (!CheckAttribute(npchar, "ClockTower_option_4") && CheckAttribute(pchar, "questTemp.KhaelRoa"))
			{
				link.l4 = "J'ai vaincu la terreur de tous ceux qui naviguent. Vous devez le savoir.";
				link.l4.go = "ClockTower_VanDoorn_option_4";
			}
			if (!CheckAttribute(npchar, "ClockTower_option_5") && GetCharacterShipClass(PChar) <= 3)
			{
				link.l5 = "Vous venez juste d'inscrire mon navire au registre. Pensez-vous qu'un capitaine incompétent pourrait l'entretenir?";
				link.l5.go = "ClockTower_VanDoorn_option_5";
			}
			if (!CheckAttribute(npchar, "ClockTower_option_6") && sti(pchar.Money) >= 1000000)
			{
				link.l6 = "Je me débrouille très bien, et l'argent pousse sur les arbres dans les Caraïbes.";
				link.l6.go = "ClockTower_VanDoorn_option_6";
			}
			link.l7 = "Mynheer Visser a déjà vérifié ma compétence. Ne suffit-il pas de l'évaluation de votre propre adjoint?";
			link.l7.go = "ClockTower_VanDoorn_5";
			npchar.ClockTower_option = true;
		break;

		case "ClockTower_VanDoorn_option_1":
			dialog.text = "Grimm? Notre organisation n'a jamais eu de griefs contre Grimm, bien au contraire. Mais celui qui a pris sa place... Je sais qui il était et dans quel but il est venu à l'origine dans les Caraïbes. De telles vilénies n'ont pas de prescription, et je suis content que vous ayez puni le criminel et véritable ennemi de mon pays.";
			link.l1 = "...";
			link.l1.go = "ClockTower_VanDoorn_4";
			npchar.ClockTower_option_1 = true;
		break;

		case "ClockTower_VanDoorn_option_2":
			dialog.text = "Si je me souviens bien du rapport sur l'incident aux Caïmans, vous n'avez pas eu l'occasion de vérifier cela. À mon avis, la situation n'est pas tout à fait claire, mais votre victoire était indéniablement compétente.";
			link.l1 = "...";
			link.l1.go = "ClockTower_VanDoorn_4";
			npchar.ClockTower_option_2 = true;
		break;

		case "ClockTower_VanDoorn_option_3":
			dialog.text = "Mais il aurait pu devenir bien pire, en effet. Un ennemi digne, bien qu'il ait perdu non pas contre vous mais contre ses supérieurs ingrats. Je suis néerlandais, donc je sais de quoi je parle quand il s'agit de la guerre avec la Castille.";
			link.l1 = "...";
			link.l1.go = "ClockTower_VanDoorn_4";
			npchar.ClockTower_option_3 = true;
		break;

		case "ClockTower_VanDoorn_option_4":
			dialog.text = "'"+GetShipName("Flying Heart")+"'. Je suis toujours étonné que les honnêtes gens ne se dispersent pas à la vue de cette monstruosité entrant au port. Bien des choses dans cette histoire me surprennent, capitaine. Mais un jour elle trouvera sa place dans nos livres et perdra tout son mystère. Quant à vous... vous vous êtes immortalisé.";
			link.l1 = "...";
			link.l1.go = "ClockTower_VanDoorn_4";
			npchar.ClockTower_option_4 = true;
		break;

		case "ClockTower_VanDoorn_option_5":
			dialog.text = "Vous seriez surpris. Mais dans votre cas, il n'y a pas de doute, c'est vrai.";
			link.l1 = "...";
			link.l1.go = "ClockTower_VanDoorn_4";
			npchar.ClockTower_option_5 = true;
		break;

		case "ClockTower_VanDoorn_option_6":
			dialog.text = "Et ne valent donc rien. À moins que ce soient des doublons, bien sûr.";
			link.l1 = "...";
			link.l1.go = "ClockTower_VanDoorn_4";
			npchar.ClockTower_option_6 = true;
		break;

		case "ClockTower_VanDoorn_5":
			dialog.text = "\nVous êtes approuvé pour les services du bureau. Bienvenue au registre des clients de la prestigieuse Compagnie néerlandaise des Indes occidentales.";
			link.l1 = "Merci.";
			link.l1.go = "ClockTower_VanDoorn_6";
		break;

		case "ClockTower_VanDoorn_6":
			dialog.text = "C'est une coopération mutuellement bénéfique. Vous obtenez l'accès aux meilleurs services des Caraïbes. Nous gagnons un partenaire fiable.";
			link.l1 = "Bien.";
			link.l1.go = "ClockTower_VanDoorn_7";
		break;

		case "ClockTower_VanDoorn_7":
			dialog.text = "Attendez! Vous entendez ça?";
			link.l1 = "Je n'entends rien.";
			link.l1.go = "ClockTower_VanDoorn_8";
			// sound stops
			i = FindSoundEventId("Location/clocks_mechanism_inside");
			SetSoundEventPauseState(i, true);
			DelEventHandler("NextHour", "Villemstad_BigClock_Above");
		break;

		case "ClockTower_VanDoorn_8":
			dialog.text = "C'est bien le problème! Il a suffi de partir une semaine...";
			link.l1 = "Quelque chose ne va pas?";
			link.l1.go = "ClockTower_VanDoorn_9";
		break;

		case "ClockTower_VanDoorn_9":
			dialog.text = "Avec l'horloge. Je dois vérifier le mécanisme. Mes excuses. C'est... important.";
			link.l1 = "...";
			link.l1.go = "ClockTower_VanDoorn_10";
		break;

		case "ClockTower_VanDoorn_10":
			if (!CheckAttribute(npchar, "ClockTower_question"))
			{
				dialog.text = "Tout semble bien maintenant. Encore mes excuses. Avez-vous des questions?";
				LAi_Fade("", "");
				// sound returns
				i = FindSoundEventId("Location/clocks_mechanism_inside");
				SetSoundEventPauseState(i, false);
				SetEventHandler("NextHour", "Villemstad_BigClock_Above", 0);
			}
			else dialog.text = "D'autres questions?";
			if (!CheckAttribute(npchar, "ClockTower_question_1"))
			{
				link.l1 = "Votre adjoint a expliqué les services du bureau en détail. Comment tout cela est-il possible?";
				link.l1.go = "ClockTower_VanDoorn_question_1";
			}
			if (!CheckAttribute(npchar, "ClockTower_question_2"))
			{
				link.l2 = "Comment combinez-vous deux postes? Capitaine et directeur?";
				link.l2.go = "ClockTower_VanDoorn_question_2";
			}
			if (!CheckAttribute(npchar, "ClockTower_question_3"))
			{
				link.l3 = "Comment travaillez-vous dans de telles conditions? Le vacarme des mécanismes d'horlogerie, l'obscurité et les fenêtres couvertes de lourds rideaux.";
				link.l3.go = "ClockTower_VanDoorn_question_3";
			}
			link.l4 = "Non, merci pour votre temps. Qu'en est-il des services du bureau?";
			link.l4.go = "ClockTower_VanDoorn_11";
			npchar.ClockTower_question = true;
		break;

		case "ClockTower_VanDoorn_question_1":
			dialog.text = "Il n'y a pas de sorcellerie ici, "+GetTitle(NPChar, false)+". La plume et l'encre gouvernent le monde. L'Église enregistre la naissance, le baptême, le mariage et la mort d'une personne. Changez ne serait-ce qu'une ligne — et son destin change. Un navire est un peu plus complexe, mais même dans son cas un trait de plume change beaucoup. Je ne le cache pas, je suis fier de ce que j'ai accompli. Et pourtant je sais que ce pourrait être mieux. Et si nous inscrivions dans les registres non seulement des navires et des gens, mais un monde entier?";
			link.l1 = "...";
			link.l1.go = "ClockTower_VanDoorn_10";
			npchar.ClockTower_question_1 = true;
		break;

		case "ClockTower_VanDoorn_question_2":
			dialog.text = "Parce que quelqu'un doit le faire. Le précédent capitaine de l'Amsterdam est mort au combat contre un groupe d'Antigua. La compagnie n'a trouvé aucun remplaçant digne. Je me suis proposé. J'ai suivi la formation. Passé les examens. Obtenu une commission\n"+
			"Oui, je suis un piètre capitaine. Bien pire que vous — c'est certain. Mais un bon gestionnaire peut commander n'importe quoi, pas seulement un navire. C'est difficile d'apprendre à commander trois personnes. Mais une fois que vous l'avez appris, vous pouvez en commander trois mille. Un bureau, un navire, une ville ou même une vaste compagnie — il n'y a pas de limite, tant que vous trouvez des gens talentueux et leur faites confiance pour vous représenter... Ce dernier point est le plus difficile. Une vraie malédiction.";
			link.l1 = "...";
			link.l1.go = "ClockTower_VanDoorn_10";
			npchar.ClockTower_question_2 = true;
		break;

		case "ClockTower_VanDoorn_question_3":
			dialog.text = "Et il n'y a presque pas d'air à respirer. "+UpperFirst(GetTitle(NPChar, false))+", une personne façonne son propre environnement. Ici rien ni personne ne me distrait, tout est à portée de main et soumis seulement à moi et au temps. Si je le pouvais, je communiquerais avec le monde extérieur uniquement par le papier. Malheureusement, c'est impossible. Et ne le prenez pas personnellement, "+GetTitle(NPChar, false)+". Mieux vaut être seul, mais pas solitaire. Si vous voyez ce que je veux dire.";
			link.l1 = "...";
			link.l1.go = "ClockTower_VanDoorn_10";
			npchar.ClockTower_question_3 = true;
		break;

		case "ClockTower_VanDoorn_11":
			// pchar.quest.ClockTower.date = rand(27)+1;
			if (pchar.quest.ClockTower.date <= GetDataDay())
			{
				NextMonth = GetDataMonth() + 1;
				if (NextMonth == 13) NextMonth = 1;
			}
			else NextMonth = GetDataMonth();
			Month = XI_ConvertString("MonthGen_" + NextMonth);
			dialog.text = "Nous ne recevons que sur rendez-vous. Vous êtes prévu pour... "+pchar.quest.ClockTower.date+" "+month+". Si vous ne venez pas le jour prévu, ce n'est pas grave. Contactez Johan, et il vous communiquera le prochain rendez-vous disponible.";
			link.l1 = "Pourquoi tant de complications?";
			link.l1.go = "ClockTower_VanDoorn_12";
		break;

		case "ClockTower_VanDoorn_12":
			if (pchar.quest.ClockTower.date <= GetDataDay())
			{
				NextMonth = GetDataMonth() + 1;
				if (NextMonth == 13) NextMonth = 1;
			}
			else NextMonth = GetDataMonth();
			Month = XI_ConvertString("MonthGen_" + NextMonth);
			dialog.text = "Notre travail est coûteux parce que nous accomplissons de vrais miracles et apportons grand bénéfice à nos clients. Les conflits d'intérêts sont impossibles, et c'est pourquoi nous consacrons une journée de travail entière aux besoins d'une personne particulière. Votre prochain jour disponible: "+pchar.quest.ClockTower.date+" "+month+"\n"+
			"Si vous voyez Visser... Maarten a agi correctement en proposant votre candidature. Dites-le-lui. C'est un bon adjoint. Qu'il n'en doute pas.";
			link.l1 = "Bien.";
			link.l1.go = "ClockTower_VanDoorn_13";
		break;

		case "ClockTower_VanDoorn_13":
			dialog.text = "Bonne journée, "+GetTitle(NPChar, false)+".";
			link.l1 = ""+Goodbye(true)+".";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_VanDoornInCabinet_3");
		break;
		
		case "ClockTower_Visser_41":
			dialog.text = "Comment ça s'est passé ?";
			link.l1 = "Ça a été une longue journée, mais van Doorn a confirmé votre décision.";
			link.l1.go = "ClockTower_Visser_42";
		break;

		case "ClockTower_Visser_42":
			dialog.text = "Dieu merci. Donc j'ai tout fait correctement.";
			link.l1 = "Il m'a chargé de vous dire que vous êtes un bon adjoint.";
			link.l1.go = "ClockTower_Visser_43";
		break;

		case "ClockTower_Visser_43":
			dialog.text = "Vraiment ? Il... a dit ça ?";
			link.l1 = "Oui. C'est ce qu'il a dit.";
			link.l1.go = "ClockTower_Visser_44";
		break;

		case "ClockTower_Visser_44":
			dialog.text = "Bon sang. Il n'aurait pas dû dire ça. Maintenant je vais me sentir comme un ingrat. Ou peut-être a-t-il prévu tout ça et calculé son coup ?";
			link.l1 = "Mynheer l'adjoint, vous avez soudain cessé d'être vous-même.";
			link.l1.go = "ClockTower_Visser_45";
		break;

		case "ClockTower_Visser_45":
			dialog.text = "Capitaine, je suis un homme d'affaires, et vous aussi, donc je ne vais pas tourner autour du pot.\n"+
						 "Le mynheer directeur ne travaille plus pour nous depuis longtemps.";
			link.l1 = "Comment, pardon ?!";
			link.l1.go = "ClockTower_Visser_46";
		break;

		case "ClockTower_Visser_46":
			dialog.text = "Il est venu ici sous contrat avec un seul objectif — mettre en place le fonctionnement du département d'enregistrement des navires. Il a réussi brillamment, a formé son remplaçant, m'a promu... et c'est tout.";
			link.l1 = "Comment, c'est tout ?";
			link.l1.go = "ClockTower_Visser_47";
		break;

		case "ClockTower_Visser_47":
			dialog.text = "Son contrat a pris fin il y a longtemps. Nous ne savons pas exactement quand, mais nous sommes absolument certains que cet homme n'a plus le droit d'occuper son poste.";
			link.l1 = "Je vois. Les huiles du corps central de ce bâtiment s'inquiètent.";
			link.l1.go = "ClockTower_Visser_48_1";
			link.l2 = "Je vois. Vous êtes fatigué d'attendre qu'il libère sa chaise pour vous.";
			link.l2.go = "ClockTower_Visser_48_2";
		break;

		case "ClockTower_Visser_48_1":
			dialog.text = "Exactement ! Et ils ne peuvent rien y faire !";
			link.l1 = "...";
			link.l1.go = "ClockTower_Visser_49";
		break;

		case "ClockTower_Visser_48_2":
			dialog.text = "Je ne vais pas mentir. Je suis vraiment fatigué. Bon sang, van Doorn m'a promu précisément pour que je le remplace à la fin de son contrat !";
			link.l1 = "...";
			link.l1.go = "ClockTower_Visser_49";
		break;

		case "ClockTower_Visser_49":
			dialog.text = "Et pourtant je ne chercherais jamais à ébranler ce maudit fauteuil sous lui, juste parce que je me sens trompé ! Dieu sait que je suis reconnaissant et j'admire cet homme !";
			link.l1 = "...";
			link.l1.go = "ClockTower_Visser_50";
		break;

		case "ClockTower_Visser_50":
			dialog.text = "Non, mynheer. Van Doorn veut se débarrasser de nos supérieurs communs. Ceux qui sont derrière le mur de la tour — dans le corps central de ce bâtiment ! Mais même eux ne peuvent pas le contrôler !";
			link.l1 = "Qu'y a-t-il de si difficile ? Van Doorn n'est certainement pas plus important que Stuyvesant.";
			link.l1.go = "ClockTower_Visser_51";
		break;

				case "ClockTower_Visser_51":
			dialog.text = "Ce n'est ni un navire ni une cour royale, capitaine. Notre compagnie est un type d'organisation totalement nouveau. On ne peut pas simplement pointer du doigt et renvoyer une personne aussi précieuse.\n"+
						 "Premièrement, personne ne sait où se trouve l'original du contrat de van Doorn. Ergo, il n'y a aucun motif de licenciement. Essayions-nous de le faire, il enverrait une meute d'avocats, et nous finirions par lui devoir de l'argent.\n"+
						 "Deuxièmement, la direction a commis une erreur en donnant à van Doorn la commission pour l'Amsterdam. Bien qu'il soit un médiocre capitaine, il a réuni un équipage — le meilleur de toute la région. Donne-t-il un ordre, et les soldats d'élite de la Compagnie occupent ce bâtiment sans sourciller.\n"+
						 "Troisièmement, sa femme l'adore. Peu importe qu'elle ne l'ait pas vu pendant des années. La propre fille de De Witt est capable de beaucoup pour son mari bien-aimé. Et le Conseil des Dix-sept est contraint de l'accepter.\n"+
						 "Autrement dit, le directoire paiera très généreusement pour votre aide. Et préservera vos privilèges au bureau d'enregistrement des navires.";
			link.l1 = "Impressionnant. Vous êtes vraiment un homme d'affaires, Maarten. Vous me vendez de la trahison avec le même professionnalisme que vous utilisiez encore récemment pour vendre les services de votre bureau.";
			link.l1.go = "ClockTower_Visser_57";
		break;

		case "ClockTower_Visser_57":
			dialog.text = "Ce n'est pas difficile lorsque van Doorn vous a lui-même enseigné l'art de la négociation et que vous croyez sincèrement en ce que vous dites.";
			link.l1 = "Alors, que voulez-vous de moi ?";
			link.l1.go = "ClockTower_Visser_58";
		break;

		case "ClockTower_Visser_58":
			dialog.text = "Quelque chose que seul un étranger peut faire. Entrez dans le bureau la nuit et trouvez-y le contrat original de van Doorn. Je m'assurerai que les portes soient ouvertes.";
			link.l1 = "Pourquoi ne le faites-vous pas vous-même ? Et qu'est-ce qui m'empêche d'aller tout de suite raconter tout ça à votre supérieur ?";
			link.l1.go = "ClockTower_Visser_59";
		break;

		case "ClockTower_Visser_59":
			dialog.text = "Parce que van Doorn a l'habitude de recevoir n'importe qui la nuit, sauf les employés de la compagnie. Personne ne sera surpris de vous voir sortir de cette tour à une heure inhabituelle.";
			link.l1 = "";
			link.l1.go = "ClockTower_Visser_60";
		break;

		case "ClockTower_Visser_60":
			if (pchar.quest.ClockTower.date <= GetDataDay())
			{
				NextMonth = GetDataMonth() + 1;
				if (NextMonth == 13) NextMonth = 1;
			}
			else NextMonth = GetDataMonth();
			Month = XI_ConvertString("MonthGen_" + NextMonth);
			dialog.text = "Quant à votre menace... Vous n'aurez pas accès au directeur maintenant, vous avez rendez-vous un autre jour. "+pchar.quest.ClockTower.date+" "+month+", n'est-ce pas ? D'ici là, l'urgence de la nouvelle aura quelque peu diminué. Et puis, le directeur ne récompense jamais les délateurs. Et protège toujours ses employés.";
			link.l1 = "Pratique pour vous.";
			link.l1.go = "ClockTower_Visser_61";
		break;

		case "ClockTower_Visser_61":
			dialog.text = "Ce n'est pas une trahison, capitaine. Nous voulons simplement respecter le contrat et protéger la compagnie. Et Willemstad, que vous avez tant aidé, d'ailleurs.";
			link.l1 = "Je vais y réfléchir. Mais je ne promets rien.";
			link.l1.go = "ClockTower_Visser_62";
		break;

		case "ClockTower_Visser_62":
			dialog.text = "Je ne vous demande rien de plus, capitaine. Avant tout, vous êtes notre client. Quoi qu'il arrive, je suis très fier d'avoir été celui qui vous a trouvé et inscrit dans le registre du bureau.";
			link.l1 = "...";
			link.l1.go = "ClockTower_Visser_63";
		break;

		case "ClockTower_Visser_63":
			dialog.text = "Vous pourrez toujours me trouver dans le corps central. Bonne journée.";
			link.l1 = "À bientôt.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_Quest_3");
		break;
		
		case "ClockTower_Visser_64":
			dialog.text = "Bonjour, "+GetTitle(NPChar, false)+". Des nouvelles ?";
			link.l1 = "Rien encore.";
			link.l1.go = "exit";
			NextDiag.TempNode = "ClockTower_Visser_64";
		break;
		
		case "ClockTower_Johan_51":
			if (GetHour() >= 6 && GetHour() < 24)
			{
				if (pchar.quest.ClockTower.date <= GetDataDay())
				{
					NextMonth = GetDataMonth() + 1;
					if (NextMonth == 13) NextMonth = 1;
				}
				else NextMonth = GetDataMonth();
				Month = XI_ConvertString("MonthGen_" + NextMonth);
				if (pchar.quest.ClockTower.date == GetDataDay() && CheckAttribute(pchar, "questTemp.ClockTower_NoToday"))
				{
					if (!CheckAttribute(npchar, "ClockTower_repeat"))
					{
						dialog.text = ""+UpperFirst(GetTitle(NPChar, true))+", c'est votre jour aujourd'hui. Je vous en prie, entrez.";
						npchar.ClockTower_repeat = true;
						SetFunctionTimerCondition("ClockTower_GuardianNewDay", 0, 0, 1, false);
						
						ClockTower_RightDay();
					}
					else
					{
						dialog.text = "Bonne journée, "+GetTitle(NPChar, false)+"!";
					}
				}
				else
				{
					if (!CheckAttribute(npchar, "ClockTower_repeat"))
					{
						dialog.text = ""+UpperFirst(GetTitle(NPChar, true))+", on vous attend un autre jour. Nous serons ravis de vous voir : "+pchar.quest.ClockTower.date+" "+month+".";
						npchar.ClockTower_repeat = true;
						SetFunctionTimerCondition("ClockTower_GuardianNewDay", 0, 0, 1, false);
					}
					else
					{
						dialog.text = "Bonne journée, "+GetTitle(NPChar, false)+"!";
					}
				}
				link.l1 = "Merci, Johan.";
				link.l1.go = "exit";
				NextDiag.TempNode = "ClockTower_Johan_51";
			}
			else
			{
				if (!CheckAttribute(npchar, "ClockTower_repeatnight"))
				{	// первая ночная встреча с Йоханом
					dialog.text = ""+UpperFirst(GetTitle(NPChar, true))+", vous arrivez un peu tard. Le bureau est fermé.";
					link.l1 = "Bonjour, "+npchar.name+". J'ai entendu dire qu'il fonctionne même la nuit.";
					link.l1.go = "ClockTower_Johan_52";
					npchar.ClockTower_repeatnight = true;
					SetFunctionTimerCondition("ClockTower_GuardianNewDay", 0, 0, 1, false);
				}
				else
				{
					dialog.text = ""+TimeGreeting()+", "+GetTitle(NPChar, false)+"!";
					link.l1 = "";
					link.l1.go = "ClockTower_Johan_53";
				}
			}
		break;
		
		case "ClockTower_Johan_52":
			dialog.text = "C'est vrai. Toutes sortes de gens viennent. Même des prêtres passent parfois, hé-hé. Mais ils doivent tous passer par moi d'abord. Et je n'ai reçu aucune instruction à votre sujet.";
			link.l1 = "Attends, tu montes la garde ici vingt-quatre heures sur vingt-quatre ? Comment est-ce possible ?";
			link.l1.go = "ClockTower_Johan_53";
		break;

		case "ClockTower_Johan_53":
			if (!CheckAttribute(npchar, "ClockTower_repeatnight_2"))
			{
				dialog.text = "Ouais. Le mynheer directeur vient de l'ordonner. Comment il s'y prend, je ne sais pas, mais j'ai quand même assez de temps pour me reposer et pour le service. Et ils ont augmenté ma solde — je ne peux pas me plaindre !";
				npchar.ClockTower_repeatnight_2 = true;
			}
			else
			{
				dialog.text = "Autre chose ?";
			}
			if (!CheckAttribute(pchar, "questTemp.ClockTower_NightFree"))
			{
				link.l1 = "Tu devrais me laisser passer. Je travaille pour la haute direction de la compagnie.";
				link.l1.go = "ClockTower_Johan_54";
				link.l2 = "(Le tuer)";
				link.l2.go = "ClockTower_Johan_KillHim";
			}
			link.l3 = "Continue comme ça, soldat.";
			link.l3.go = "ClockTower_Johan_NightExit";
		break;

		case "ClockTower_Johan_KillHim":
			DialogExit();
			AddDialogExitQuestFunction("ClockTower_KillToJohan");
		break;

		case "ClockTower_Johan_NightExit":
			DialogExit();
			NextDiag.CurrentNode = "ClockTower_Johan_51";
		break;

		case "ClockTower_Johan_54":
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) >= 80)
			{
				dialog.text = "Euh. Que voulez-vous de moi, mynheer capitaine ? Je ne suis qu'un simple soldat, je ne sais rien.";
				link.l1 = "Tu sais tout, Johan. Ne sois pas si modeste. Les messieurs dans les hauts bureaux n'ont peut-être pas à te rendre compte, mais tu as certainement entendu parler du chat noir entre eux.";
				link.l1.go = "ClockTower_Johan_55";
				Notification_Skill(true, 80, SKILL_LEADERSHIP);
			}
			else
			{
				dialog.text = "Je suis un petit homme, mais je ne passerai pas par-dessus la tête de mon supérieur direct. Mes excuses, mynheer capitaine.";
				link.l1 = "Nous reviendrons à cette conversation.";
				link.l1.go = "ClockTower_Johan_NightExit";
				Notification_Skill(false, 80, SKILL_LEADERSHIP);
			}
		break;

		case "ClockTower_Johan_55":
			Achievment_Set("ach_CL_197");
			dialog.text = "C'est vrai, mynheer capitaine. Le mynheer directeur s'est éternisé. Une tempête se prépare.";
			link.l1 = "Qu'as-tu entendu ?";
			link.l1.go = "ClockTower_Johan_56";
		break;

		case "ClockTower_Johan_56":
			dialog.text = "Tout le monde craint que si ce n'est pas aujourd'hui, ce sera demain qu'il prendra le pouvoir. Il est trop important pour notre trou perdu. Il étouffe tout le monde avec ses inspections, fait passer chaque signature par lui.\nJe vous le dis franchement, et vous l'avez vu vous-même : à chaque fois que l'Amsterdam entre au port, une mauvaise tension monte aussitôt.";
			link.l1 = "Je peux régler ça, mais pour cela tu dois me laisser passer.";
			link.l1.go = "ClockTower_Johan_57";
		break;

		case "ClockTower_Johan_57":
			dialog.text = "Allez-y, mynheer capitaine. Je vous en prie seulement, ne me perdez pas : si le mynheer directeur l'apprend, je perdrai ma tête, et j'ai une famille à nourrir.";
			link.l1 = "Je ferai de mon mieux.";
			link.l1.go = "ClockTower_Johan_58_hint";
		break;

		case "ClockTower_Johan_58_hint":
			ClockTower_AddBook();
			dialog.text = "Vous êtes un homme bon, mynheer capitaine. Peut-être puis-je vous aider : je sais que dans l'un des livres le mynheer directeur garde une clé. À quoi elle sert — je ne sais pas, mais peut-être sera-t-elle utile.";
			link.l1 = "Merci, Johan.";
			link.l1.go = "ClockTower_Johan_NightSuccess";
		break;
		
		case "ClockTower_Johan_NightSuccess":
			DialogExit();
			AddDialogExitQuestFunction("ClockTower_NightFree");
			NextDiag.CurrentNode = "ClockTower_Johan_51";
			// if (sti(pchar.reputation.nobility) < 71) Notification_Reputation(false, 71, "low");
		break;
		
		case "ClockTower_Peter_50":
			dialog.text = "Halte. Vous êtes sur la propriété de la Compagnie néerlandaise des Indes occidentales. Département d'enregistrement des navires et archives. Entrée sur rendez-vous uniquement.";
			link.l1 = "Je suis le "+GetTitle(NPChar, false)+" "+pchar.name+".";
			link.l1.go = "ClockTower_Peter_51";
			DelLandQuestMark(npchar);
		break;
		
		case "ClockTower_Peter_51":
			if (pchar.quest.ClockTower.date <= GetDataDay())
			{
				NextMonth = GetDataMonth() + 1;
				if (NextMonth == 13) NextMonth = 1;
			}
			else NextMonth = GetDataMonth();
			Month = XI_ConvertString("MonthGen_" + NextMonth);
			if (pchar.quest.ClockTower.date == GetDataDay() && CheckAttribute(pchar, "questTemp.ClockTower_NoToday"))
			{
				if (!CheckAttribute(npchar, "ClockTower_repeat"))
				{
					dialog.text = "Vous avez rendez-vous ? Allez-y.";
					npchar.ClockTower_repeat = true;
					SetFunctionTimerCondition("ClockTower_GuardianNewDay", 0, 0, 1, false);
					
					ClockTower_RightDay();
				}
				else
				{
					dialog.text = "...";
				}
			}
			else
			{
				if (!CheckAttribute(npchar, "ClockTower_repeat"))
				{
					dialog.text = "Votre rendez-vous est prévu pour un autre jour : "+pchar.quest.ClockTower.date+" "+month+".";
					npchar.ClockTower_repeat = true;
					SetFunctionTimerCondition("ClockTower_GuardianNewDay", 0, 0, 1, false);
				}
				else
				{
					dialog.text = "...";
				}
			}
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ClockTower_Peter_51";
		break;
		
		case "ClockTower_Visser_71":
			dialog.text = "Bonjour, "+GetTitle(NPChar, false)+". Des nouvelles ?";
			link.l1 = "Oui. Voici le contrat.";
			link.l1.go = "ClockTower_Visser_72";
			DelLandQuestMark(npchar);
		break;

		case "ClockTower_Visser_72":
			dialog.text = "Incroyable... Il a expiré il y a sept ans !";
			link.l1 = "Donc c'est ce qu'il vous fallait ?";
			link.l1.go = "ClockTower_Visser_73";
		break;

		case "ClockTower_Visser_73":
			dialog.text = "Exactement ! Avec ce document la compagnie peut le révoquer légalement. Aucune échappatoire. Aucune excuse. Le temps est écoulé — point final.";
			link.l1 = "Et ensuite ?";
			link.l1.go = "ClockTower_Visser_74";
		break;

		case "ClockTower_Visser_74":
			dialog.text = "J'enverrai le contrat à Amsterdam. Le Conseil des Dix-Sept prendra une décision. On ordonnera à Doorn de rentrer. Il ne pourra pas refuser.";
			link.l1 = "Et s'il refuse quand même ?";
			link.l1.go = "ClockTower_Visser_75";
		break;

		case "ClockTower_Visser_75":
			dialog.text = "Il ne peut pas. Bien qu'il soit marié à la fille d'un actionnaire, le Grand Pensionnaire, même son père n'ira pas contre le Conseil. Et Catharina elle-même... Elle attend depuis dix ans. Si elle apprend qu'il peut rentrer mais refuse — ça la tuera.";
			link.l1 = "Cruel.";
			link.l1.go = "ClockTower_Visser_76";
		break;

		case "ClockTower_Visser_76":
			dialog.text = "Oui. Mais c'est la seule façon. Merci, capitaine. Vous avez accompli un travail important.";
			link.l1 = "...";
			link.l1.go = "ClockTower_Visser_77";
		break;

		case "ClockTower_Visser_77":
			if (CharacterIsAlive("ClockTower_Johan"))
			{
				dialog.text = "Votre récompense — cinq cents doublons. Et je vous donne ma parole : dans deux à trois mois, quand je prendrai le fauteuil de directeur, vous aurez un accès illimité aux services du bureau. Pas de files. Pas de rendez-vous. À tout moment.";
				AddItems(pchar, "gold_dublon", 500);
			}
			else
			{
				dialog.text = "Et vous avez tué Johan. J'ai déjà trahi un homme que j'admire et à qui je dois tout. Maintenant ça aussi.\n"+
							 "Peut-être que sur votre navire les gens sont comme du petit bois, mais la compagnie apprécie ses employés. Et ça me dégoûte d'être complice d'un meurtre.\n"+
							 "Vos doublons iront à la famille de Johan, mais je remplirai la deuxième partie du marché.\n"+
							 "Je vous donne ma parole : dans deux à trois mois, quand je prendrai le fauteuil de directeur, vous aurez un accès illimité aux services du bureau.";
			}
			link.l1 = "Je compte sur votre parole. Bonne journée.";
			link.l1.go = "ClockTower_Visser_78";
		break;

		case "ClockTower_Visser_78":
			DialogExit();
			AddDialogExitQuestFunction("ClockTower_WaitFewMonths");
		break;

		case "ClockTower_Visser_79":
			dialog.text = "Bonjour, "+GetTitle(NPChar, false)+". Toujours pas de nouvelles. Ne vous inquiétez pas, je me souviens de notre accord.";
			link.l1 = "Espérons.";
			link.l1.go = "exit";
			NextDiag.TempNode = "ClockTower_Visser_79";
		break;

		case "ClockTower_Visser_81":
			dialog.text = ""+UpperFirst(GetTitle(NPChar, false))+" ! Entre, entre. Ravi de te voir.";
			link.l1 = "Félicitations pour votre nomination.";
			link.l1.go = "ClockTower_Visser_82";
			DelLandQuestMark(npchar);
		break;

		case "ClockTower_Visser_82":
			dialog.text = "Merci. Le Conseil des Dix-Sept a pris sa décision plus vite que je ne l'attendais. Le contrat s'est avéré une preuve suffisante. Mynheer van Doorn a été relevé de la direction du bureau.";
			link.l1 = "Comment l'a-t-il pris ?";
			link.l1.go = "ClockTower_Visser_83";
		break;

		case "ClockTower_Visser_83":
			dialog.text = "Il sait perdre. Il a simplement rassemblé ses affaires personnelles du bureau et est parti. Bien qu'ait-il vraiment perdu ?\n"+
						 "On lui a gardé son commandement de l'Amsterdam. Sur ce point, la compagnie a certainement fait une erreur. On n'aurait pas dû lui donner ce navire à l'époque.\n"+
						 "On l'a sous-estimé. Espérons que les choses ne tournent pas plus mal à la fin.";
			link.l1 = "Comment cela pourrait-il être pire ?";
			link.l1.go = "ClockTower_Visser_84";
		break;

		case "ClockTower_Visser_84":
			dialog.text = "Mynheer van Doorn sait qui a récupéré le contrat de son bureau.";
			link.l1 = "Comment ?!";
			link.l1.go = "ClockTower_Visser_85";
		break;

		case "ClockTower_Visser_85":
			dialog.text = "Ne me regardez pas comme ça ! Je ne lui ai rien dit. Il l'a compris tout seul.";
			link.l1 = "Et maintenant ?";
			link.l1.go = "ClockTower_Visser_86";
		break;

		case "ClockTower_Visser_86":
			dialog.text = "Maintenant il vous considère comme un ennemi. Mais tant que vous ne représentez aucune menace pour la République des Sept Provinces-Unies, il ne vous touchera pas.\n"+
						 "Van Doorn a toujours su séparer le personnel du professionnel. La question est, le pouvez-vous ?";
			link.l1 = "Et si je ne peux pas ?";
			link.l1.go = "ClockTower_Visser_87";
		break;

		case "ClockTower_Visser_87":
			dialog.text = "Alors il vous trouvera. Et fera son travail. Ne lui donnez pas de raison.";
			link.l1 = "J'essaierai.";
			link.l1.go = "ClockTower_Visser_88";
		break;

		case "ClockTower_Visser_88":
			dialog.text = "Bonne journée à vous, "+GetTitle(NPChar, false)+". N'hésitez pas à utiliser les services de notre... mon bureau à tout moment.";
			link.l1 = ""+Goodbye(true)+".";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_VillemstadStreet");
		break;
		
		case "ClockTower_Johan_61":
			dialog.text = ""+UpperFirst(GetTitle(NPChar, true))+", on vous attend. Mynheer Visser a ordonné de laisser entrer tous les clients librement. Il dit que les anciennes règles étaient trop strictes.";
			link.l1 = "Merci, Johan.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_FreeAccess_2");
			DelLandQuestMark(npchar);
		break;
		
		case "ClockTower_Peter_61":
			dialog.text = "Entrez pendant les heures de bureau. Les rendez-vous ont été abolis.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_FreeAccess_2");
			DelLandQuestMark(npchar);
		break;
		
		case "ClockTower_Helena_1":
			dialog.text = "Tu as une minute ?";
			link.l1 = "Pour toi — toujours.";
			link.l1.go = "ClockTower_Helena_2";
		break;

		case "ClockTower_Helena_2":
			dialog.text = "Ah, si seulement, mon capitaine. Tu as d'autres passions dans la vie. Là maintenant, par exemple, ta jolie tête est occupée par quelqu'un d'autre que moi, n'est-ce pas ?";
			link.l1 = "...";
			link.l1.go = "ClockTower_Helena_3";
		break;

		case "ClockTower_Helena_3":
			dialog.text = "Je le savais. Je connais bien mon homme. Et l'ardeur d'un marin — je la connais encore mieux. Alors dis-moi franchement, mon chéri...\n"+
						 "Combien nous coûtera la capture du navire amiral de l'estimée Compagnie commerciale néerlandaise des Indes occidentales ?";
			link.l1 = "Pour que van Doorn vienne nous chercher lui-même, je devrai devenir un ennemi de Willemstad.";
			link.l1.go = "ClockTower_Helena_4";
		break;

		case "ClockTower_Helena_4":
			dialog.text = "Oh, mon capitaine... Donc c'est ainsi que ce sera. Ce n'est pas la première fois, n'est-ce pas ?";
			link.l1 = "Comme si tu n'approuvais pas.";
			link.l1.go = "ClockTower_Helena_5";
		break;

		case "ClockTower_Helena_5":
			dialog.text = "Je suis tombée amoureuse de toi tel que tu es. Et je serai toujours de ton côté. Rappelle-toi simplement le fardeau de responsabilité que nous... enfin, que tu portes envers tes hommes.";
			link.l1 = "Mais c'est pour ça que nous avons notre Alonso. Lui te le rappellera.";
			link.l1.go = "ClockTower_Helena_6";
		break;

		case "ClockTower_Helena_6":
			dialog.text = "Dès que nous prendrons la mer, mon capitaine.";
			link.l1 = "Ne tardons pas alors, mon amour.";
			link.l1.go = "ClockTower_Girl_End";
		break;
		
		case "ClockTower_Mary_1":
			dialog.text = "Charles ? Je veux te demander quelque chose.";
			link.l1 = "Bien sûr, Mary. Que s'est-il passé ?";
			link.l1.go = "ClockTower_Mary_2";
		break;

		case "ClockTower_Mary_2":
			dialog.text = "Je... je m'inquiète pour toi, tu sais. Je connais ce regard. Tu penses à quelque chose de grave.";
			link.l1 = "N'importe quoi. Je ne me souviens même pas à quoi je pensais. Comment le saurais-tu ?";
			link.l1.go = "ClockTower_Mary_3";
		break;

		case "ClockTower_Mary_3":
			dialog.text = "Je le sais, c'est tout ! J'ai vu cet Amsterdam, tu sais. Un beau navire. Très beau. Mais...\n"+
						 "Tu as déjà tout décidé... Comme avant, n'est-ce pas ?";
			link.l1 = "Van Doorn viendra nous chercher lui-même, mais pour cela je devrai devenir un ennemi de Willemstad.";
			link.l1.go = "ClockTower_Mary_4";
		break;

		case "ClockTower_Mary_4":
			dialog.text = "Est-ce que ça en vaut la peine, Charles ?";
			link.l1 = "Je ne sais pas, Mary.";
			link.l1.go = "ClockTower_Mary_5";
		break;

		case "ClockTower_Mary_5":
			dialog.text = "Je veux que tu sois heureux, tu sais. Mais je vais quand même demander à Alonso d'essayer de te dissuader, d'accord !";
			link.l1 = "Ça lui ressemble bien. Allons-y, mon amour.";
			link.l1.go = "ClockTower_Girl_End";
		break;
		
		case "ClockTower_Girl_End":
			DialogExit();
			AddDialogExitQuestFunction("ClockTower_Girl_DlgExit");
		break;
		
		case "ClockTower_Alonso_1":
			dialog.text = "Cap, on doit parler.";
			link.l1 = "Je t'écoute.";
			link.l1.go = "ClockTower_Alonso_2";
			link.l2 = "Pas maintenant, Alonso.";
			link.l2.go = "ClockTower_Alonso_2";
		break;

		case "ClockTower_Alonso_2":
			dialog.text = "Voilà le truc, cap, mais tu dois m'écouter. C'est, euh, comment dire...\n"+
						 "Une affaire urgente — voilà !\n"+
						 "Alors, un petit oiseau m'a dit que vous avez personnellement viré l'un des directeurs de la compagnie de son siège confortable, et celui-ci nourrit une rancune et nous chasse maintenant sur sa belle frégate.";
			link.l1 = "C'est une grosse exagération.";
			link.l1.go = "ClockTower_Alonso_3";
		break;

		case "ClockTower_Alonso_3":
			dialog.text = "Vous savez comment les gens aiment faire marcher leur langue, cap. Laissez une rumeur mijoter une semaine — et vous entendrez que van Doorn a été séduit par la fille d'un planteur, que l'Amsterdam a un équipage de morts-vivants, et dans la cale se trouvent les trésors de Cortés lui-même.\n"+
						 "Mais ce qui m'intéresse davantage, c'est la situation réelle. Alors, cap, y aura-t-il un combat ou pas ?";
			link.l1 = "...";
			if (CheckPassengerInCharacter(pchar, "Irons")) // Tommy
			{
				link.l1.go = "ClockTower_Alonso_4_1";
			}
			else
			{
				link.l1.go = "ClockTower_Alonso_4_5";
			}
		break;

		case "ClockTower_Alonso_4_1":
			DialogExit();
			AddDialogExitQuestFunction("ClockTower_TommyInCabin");
		break;

		case "ClockTower_Alonso_4_2":
			dialog.text = "Ce qui, soit dit en passant, serait sacrément amusant, je ne discute pas ! Le vaisseau amiral hollandais ! Ha ! J'imagine les têtes de ces mangeurs de fromage quand nous...";
			link.l1 = "...";
			link.l1.go = "ClockTower_Alonso_4_3";
		break;

		case "ClockTower_Alonso_4_3":
			DialogExit();
			AddDialogExitQuestFunction("ClockTower_TommyInCabin_2");
		break;

		case "ClockTower_Alonso_4_4":
			dialog.text = "Tommy, ferme-la.";
			link.l1 = "...";
			link.l1.go = "ClockTower_Alonso_4_5";
		break;

		case "ClockTower_Alonso_4_5":
			dialog.text = "...";
			link.l1 = "S'il doit y avoir un combat, ce ne sera pas de sitôt. Van Doorn ne cherchera pas la vengeance, ce n'est pas ce genre d'homme. D'abord il nous faudra vraiment énerver les Hollandais.";
			link.l1.go = "ClockTower_Alonso_4_6";
			CharacterTurnByChr(npchar, pchar);
		break;

		case "ClockTower_Alonso_4_6":
			dialog.text = "Merci, cap, ça rassurera l'équipage.";
			link.l1 = "Et toi ?";
			link.l1.go = "ClockTower_Alonso_5";
		break;

		case "ClockTower_Alonso_5":
			dialog.text = "Mon souci, c'est de protéger l'équipage. D'eux-mêmes et... de vous, si je peux. Vous ferez ce que vous avez prévu de toute façon.";
			if (CheckPassengerInCharacter(pchar, "Irons")) // Tommy
			{
				link.l1 = "...";
				link.l1.go = "ClockTower_Alonso_5_add";
			}
			else
			{
				link.l1 = "Continue comme ça, Alonso.";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("ClockTower_CuracaoInCabin_4_DlgExit");
			}
		break;

		case "ClockTower_Alonso_5_add":
			StartInstantDialogTurnToNPC("Irons", "ClockTower_Alonso_6", "Quest\ShipsPack\ClockTower_dialog.c", "ClockTower_Alonso");
		break;

		case "ClockTower_Alonso_6":
			dialog.text = "Têtu comme une mule espagnole !";
			link.l1 = "...";
			link.l1.go = "ClockTower_Alonso_6_add";
		break;

		case "ClockTower_Alonso_6_add":
			StartInstantDialogTurnToNPC("ClockTower_Alonso", "ClockTower_Alonso_7", "Quest\ShipsPack\ClockTower_dialog.c", "Irons");
		break;

		case "ClockTower_Alonso_7":
			dialog.text = "Seigneur, pourquoi moi.";
			link.l1 = "...";
			link.l1.go = "ClockTower_Alonso_7_add";
		break;

		case "ClockTower_Alonso_7_add":
			StartInstantDialogTurnToNPC("Irons", "ClockTower_Alonso_8", "Quest\ShipsPack\ClockTower_dialog.c", "ClockTower_Alonso");
		break;

		case "ClockTower_Alonso_8":
			dialog.text = "Tu compliques tout ! Le cap veut un joli navire — on lui offrira un joli navire ! On est un seul équipage !";
			link.l1 = "Continue comme ça, Alonso. Tommy, sors.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_CuracaoInCabin_4_DlgExit");
		break;
		
		// Абордаж Амстердама, перед боем с Ван Дормом
		case "ClockTower_VanDoorn_21":
			NationName = GetSexPhrase(""+NationNameMan(sti(pchar.baseNation))+"",""+NationNameWoman(sti(pchar.baseNation))+"");
			shipType = LowerFirst(XI_ConvertString(GetShipTypeName(pchar)));
			dialog.text = ""+UpperFirst(GetTitle(NPChar, false))+" "+GetFullName(pchar)+", "+NationName+". Votre navire — '"+PChar.Ship.Name+"', "+shipType+". "+GetCannonQuantity(pchar)+" canons et "+GetMaxCrewQuantity(pchar)+" membres d'équipage.";
			link.l1 = "Vous êtes aussi précis que toujours, mynheer directeur.";
			link.l1.go = "ClockTower_VanDoorn_22";
		break;

		case "ClockTower_VanDoorn_22":
			dialog.text = "Ce titre ne m'appartient plus — grâce à vos efforts. Mais ne pensez surtout pas que je vous ai attaqué par mesquine vengeance. Je faisais mon travail.\n"+
						 "Et manifestement j'ai échoué. Je n'aurais pas pu réussir non plus : je vous ai dit une fois que vous êtes un bien meilleur capitaine que moi.";
			link.l1 = "Vous avez pris ce fardeau vous-même ! Votre contrat a expiré il y a sept ans. Qu'est-ce qui vous empêchait de simplement rentrer chez vous ?";
			link.l1.go = "ClockTower_VanDoorn_23";
		break;

		case "ClockTower_VanDoorn_23":
			dialog.text = "Qu'est-ce qui vous empêche de faire la même chose ? Vous connaissez la réponse, capitaine. Vous avez un rêve. Vous n'avez pas d'autre vie. Et si vous lâchez le contrôle — tout s'effondre.\n"+
						 "J'aurais pu instaurer l'ordre dans cette région. Arrêter le cycle sans fin de violence. Si je n'avais pas relâché le contrôle. Si j'avais écrasé ma peur et fait ce qu'il fallait faire depuis longtemps.\n"+
						 "Mais assez de pathétique. Je suis aussi mauvais combattant que capitaine, mais je sais choisir mes hommes. Vous vous êtes fait ma dernière tâche, capitaine. Aujourd'hui le registre du bureau comptera deux capitaines de moins !";
			if (CheckCharacterItem(PChar, "CatharinaLetter"))
			{
				link.l1 = "Vous disiez quelque chose sur la peur. Alors lisez cette lettre.";
				link.l1.go = "ClockTower_VanDoorn_24";
			}
			link.l2 = "Seulement un. Au combat !";
			link.l2.go = "ClockTower_cabinFight";
		break;

		case "ClockTower_VanDoorn_24":
			dialog.text = "De Catharina ?! Comment osez-vous mêler le personnel au professionnel ?!";
			link.l1 = "Comme vous voyez, la lettre est toujours scellée. J'attends.";
			link.l1.go = "ClockTower_VanDoorn_25";
			TakeItemFromCharacter(pchar, "CatharinaLetter");
			pchar.questTemp.ClockTower_GaveCatharinaLetter = true;
		break;

		case "ClockTower_VanDoorn_25":
			dialog.text = "...elle ne peut plus attendre... ira vers un autre... si je ne rentre pas ?!";
			link.l1 = "Vous avez déjà perdu le bureau. Votre équipage est en train de mourir. Êtes-vous prêt à perdre votre famille aussi ?";
			link.l1.go = "ClockTower_VanDoorn_26";
		break;

		case "ClockTower_VanDoorn_26":
			dialog.text = "Pas comme ça. Capitaine, acceptez-vous ma reddition ?";
			link.l1 = "Oui. Débarrassez-moi le plancher.";
			link.l1.go = "ClockTower_VanDoorn_27";
			link.l2 = "Non. C'était la dernière courtoisie pour le condamné. Au combat !";
			link.l2.go = "ClockTower_cabinFight";
		break;

		case "ClockTower_VanDoorn_27":
			dialog.text = "Alors félicitations pour votre victoire, capitaine "+GetFullName(pchar)+". Aujourd'hui le registre comptera seulement un capitaine de moins. Adieu.";
			link.l1 = "...";
			link.l1.go = "ClockTower_cabinPeace";
			GiveItem2Character(PChar, "pistol15");
			RemoveCharacterEquip(npchar, GUN_ITEM_TYPE);
			RemoveCharacterEquip(npchar, GUN_ITEM_TYPE);
			TakeItemFromCharacter(npchar, "pistol15");
		break;
				
		// Финальный диалог с Маартеном
		case "ClockTower_Visser_101":
			dialog.text = ""+UpperFirst(GetTitle(NPChar, false))+" "+GetFullName(pchar)+". Je ne m'attendais pas à ce que vous osiez venir ici.";
			link.l1 = "Pourquoi pas ? Je suis toujours votre client, et j'ai besoin des services du bureau.";
			link.l1.go = "ClockTower_Visser_102";
			DelLandQuestMark(npchar);
		break;

		case "ClockTower_Visser_102":
			dialog.text = "Des services ? DES SERVICES ?! Après ce que vous avez fait ? Vous êtes un ennemi de l'estimée Compagnie néerlandaise des Indes occidentales ! Un autre capitaine prendra votre place de client !";
			link.l1 = "Peu probable. Regardez ce que j'ai trouvé dans les papiers de van Doorn.";
			link.l1.go = "ClockTower_Visser_103";
		break;

		case "ClockTower_Visser_103":
			dialog.text = "...";
			link.l1 = "Votre prédécesseur a jugé indigne de lui d'utiliser ce document — même quand son fauteuil a commencé à vaciller.";
			link.l1.go = "ClockTower_Visser_104";
			TakeItemFromCharacter(pchar, "Visser_Key");
		break;

		case "ClockTower_Visser_104":
			dialog.text = "...";
			link.l1 = "Vous avez eu de la chance d'avoir un tel supérieur. Pour de telles combines, vous auriez fait face à un procès — au mieux.";
			link.l1.go = "ClockTower_Visser_105";
		break;

		case "ClockTower_Visser_105":
			dialog.text = "...";
			link.l1 = "Vous êtes un homme d'affaires. Vous savez où je veux en venir.";
			link.l1.go = "ClockTower_Visser_106";
		break;

		case "ClockTower_Visser_106":
			dialog.text = "Vous... Votre place dans le registre est rétablie.";
			link.l1 = "Ah, Maarten. Vous vouliez prendre la place du directeur, bien qu'il vous ait tout donné. Il vous a sauvé d'un procès et n'a même pas jugé nécessaire de vous en informer.";
			link.l1.go = "ClockTower_Visser_107";
		break;

		case "ClockTower_Visser_107":
			dialog.text = "...";
			link.l1 = "Ce petit péché ne vous laissera jamais monter plus haut et vous laissera vivre dans la peur constante.";
			link.l1.go = "ClockTower_Visser_108";
		break;

		case "ClockTower_Visser_108":
			dialog.text = "...";
			link.l1 = "Maintenant c'est votre tour d'être enchaîné à cet endroit. Mais vous n'aurez certainement pas un adjoint comme celui qu'avait van Doorn.";
			link.l1.go = "ClockTower_Visser_109";
		break;

		case "ClockTower_Visser_109":
			dialog.text = "Assez ! Voulez-vous m'achever complètement ?!";
			link.l1 = "Pas tout à fait. Je veux que vous inscriviez mon nouveau navire dans le registre. Je ne veux aucun malentendu.";
			link.l1.go = "ClockTower_Visser_110";
		break;

		case "ClockTower_Visser_110":
			dialog.text = "Votre navire est l'Amsterdam. Navire amiral de la CNIOC. On ne peut pas simplement le... réenregistrer.";
			link.l1 = "Pourquoi pas ? Le papier supporte tout. N'est-ce pas ainsi que fonctionne votre système ?";
			link.l1.go = "ClockTower_Visser_111";
		break;

		case "ClockTower_Visser_111":
			dialog.text = "Bon Dieu, mais tout a des limites !";
			link.l1 = "Je crois au pouvoir de cet endroit. Vous devriez aussi.";
			link.l1.go = "ClockTower_Visser_112";
		break;

		case "ClockTower_Visser_112":
			dialog.text = "...";
			link.l1 = "...";
			link.l1.go = "ClockTower_Visser_113";
		break;

		case "ClockTower_Visser_113":
			dialog.text = "Nom complet ?";
			link.l1 = ""+GetFullName(pchar)+".";
			link.l1.go = "ClockTower_Visser_114";
		break;

		case "ClockTower_Visser_114":
			dialog.text = "Nationalité ?";
			link.l1 = ""+NationNameNominative(sti(pchar.baseNation))+".";
			link.l1.go = "ClockTower_Visser_115";
		break;

		case "ClockTower_Visser_115":
			dialog.text = "Nom de votre navire ?";
			link.l1 = ""+PChar.Ship.Name+".";
			link.l1.go = "ClockTower_Visser_116";
		break;

		case "ClockTower_Visser_116":
			shipType = XI_ConvertString(GetShipTypeName(pchar));
			dialog.text = "Type de navire ?";
			link.l1 = ""+shipType+".";
			link.l1.go = "ClockTower_Visser_117";
		break;

		case "ClockTower_Visser_117":
			dialog.text = "Nombre de canons ?";
			link.l1 = ""+GetCannonQuantity(pchar)+".";
			link.l1.go = "ClockTower_Visser_118";
		break;

		case "ClockTower_Visser_118":
			dialog.text = "Taille de l'équipage ?";
			link.l1 = ""+GetMaxCrewQuantity(pchar)+".";
			link.l1.go = "ClockTower_Visser_119";
		break;

		case "ClockTower_Visser_119":
			dialog.text = "Bien. Signez maintenant ici. Et ici. Et ici aussi.";
			link.l1 = "C'est tout ?";
			link.l1.go = "ClockTower_Visser_120";
		break;

		case "ClockTower_Visser_120":
			dialog.text = "C'est tout.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_Visser_pausa_1");
		break;

		case "ClockTower_Visser_121":
			dialog.text = "...";
			link.l1 = "Vous avez oublié de dire quelque chose.";
			link.l1.go = "ClockTower_Visser_122";
		break;

		case "ClockTower_Visser_122":
			dialog.text = "\nBienvenue dans le registre des clients de l'estimée Compagnie néerlandaise des Indes occidentales.";
			link.l1 = "À bientôt, mynheer directeur.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_FINAL");
		break;
		

		//------------------Услуги конторы------------------//
		case "ClockTower_OfficeServices":
			if (npchar.id == "ClockTower_VanDoorn")
			{
				dialog.text = ""+UpperFirst(GetTitle(NPChar, false))+" "+pchar.name+". Comment puis-je vous aider aujourd'hui, moi et mon bureau ?";
			}
			if (npchar.id == "ClockTower_Visser")
			{
				if (CharacterIsAlive("ClockTower_VanDoorn"))
				{
					dialog.text = "Ravi de vous voir, "+GetTitle(NPChar, false)+"! Toujours à votre service. Qu'est-ce qui vous intéresse aujourd'hui ?";
				}
				else
				{
					dialog.text = "Alors ? Qu'est-ce qui vous intéresse aujourd'hui ?";
				}
			}
			link.l1 = "Effectuerez-vous un audit de mon navire ? Je veux améliorer ses caractéristiques.";
			link.l1.go = "ClockTower_OfficeServices_audit"; // Аудит
			link.l2 = "Je ne suis pas satisfait de la spécialisation de mon navire. Pouvez-vous produire de nouveaux documents ?";
			link.l2.go = "ClockTower_OfficeServices_changeTrait"; // Смена документов
			link.l3 = "Inscrirez-vous mon navire dans le registre de la compagnie ? Afin que les pirates et les chasseurs de primes réfléchissent à deux fois.";
			link.l3.go = "ClockTower_OfficeServices_buffSpec"; // Занесение в реестр
			if (!CheckAttribute(pchar, "questTemp.ShipInsurance"))
			{
				link.l4 = "Je veux assurer mes navires dans les entrepôts portuaires. Courants et futurs.";
				link.l4.go = "ClockTower_OfficeServices_Insurance"; // Страховка (пропадает после оплаты)
			}
			if(!CheckAttributeEqualTo(npchar, "last_logbook_date", LastSpeakDate()) && ClockTower_JournalsQty() > 0)
			{
				link.l5 = "Acceptez-vous les journaux de bord des capitaines pirates ?";
				link.l5.go = "ClockTower_OfficeServices_logbook"; // Награда за пиратов (раз в сутки)
			}
			link.l6 = "Peut-être une autre fois. Bonne journée.";
			link.l6.go = "ClockTower_OfficeServices_exit"; // Отказ
		break;

		// Аудит
		case "ClockTower_OfficeServices_audit":
			if (!IsShipInPort(npchar.city))
			{
				ClockTower_NoShipInPort(link);
				break;
			}
			n = 0;
			dialog.text = "Le coût dépend de la taille du navire. De quel navire s'agit-il ?";
			for (i = 0; i < COMPANION_MAX; i++)
			{
				idx = GetCompanionIndex(pchar, i);
				if (idx < 0) continue;

				sld = GetCharacter(idx);
				realShip = GetRealShip(GetCharacterShipType(sld));
				if (CheckAttribute(realShip, "tuning.Audit")) continue;
				if (!IsFellowOurCrew(sld)) continue;

				n++;
				sTemp = "l"+n;
				link.(sTemp) = XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName) + " '" + sld.Ship.Name + "'.";
				link.(sTemp).go = Dialog.currentNode + "_chosenIdx/" + idx;
			}

			if (n == 0)
			{
				dialog.text = "Malheureusement, l'audit est un service unique pour chaque navire individuel. Autre chose ?";
				link.l1 = "Alors une autre fois.";
				link.l1.go = "ClockTower_OfficeServices_exit";
			}
		break;

		case "ClockTower_OfficeServices_audit_chosenIdx":
			sld = GetCharacter(sti(Dialog.tmpIdx));
			sTemp = "";
			if (CanUpgradeShip(sld, &sTemp, "Audit"))
			{
				n = GetAuditShipCost(sld);
				dialog.text = "Voyons voir... Cela coûtera " + n + " doublons.";
				if (PCharDublonsTotal() > n)
				{
					link.l1 = "Procédez.";
					link.l1.go = "ClockTower_OfficeServices_audit_upgradeShip";
				}
				link.l2 = "Quoique... faisons-le une autre fois.";
				link.l2.go = "ClockTower_OfficeServices_exit";
			}
			else if (sTemp == "Kaleuche")
			{
				dialog.text = "Je suis contraint de refuser. Selon le registre, votre navire est allé au diable des mers il y a bien des années, et un tel fantôme du passé ne peut être effacé d’un coup de plume. Avant que nous puissions coopérer, vous devrez le restaurer. On dit qu’il y a sur Isla Tesoro un maître prêt à entreprendre un tel travail.";
				link.l1 = "C'est clair, merci.";
				link.l1.go = "ClockTower_OfficeServices_exit";
			}
			else if (sTemp == "alreadyUpgraded")
			{
				dialog.text = "$Le navire a déjà été amélioré.";
				link.l1 = "C'est clair, merci.";
				link.l1.go = "ClockTower_OfficeServices_exit";
			}
		break;

		case "ClockTower_OfficeServices_audit_upgradeShip":
			Achievment_Set("ach_CL_199");
			sld = GetCharacter(sti(Dialog.tmpIdx));
			RemoveDublonsFromPCharTotal(GetAuditShipCost(sld));
			UpgradeShipAudit(sld);
			dialog.text = "Terminé.";
			link.l1 = "Merci.";
			link.l1.go = "ClockTower_OfficeServices_exit";
		break;

		// Улучшение специализации
		case "ClockTower_OfficeServices_buffSpec":
			if (!IsShipInPort(npchar.city))
			{
				ClockTower_NoShipInPort(link);
				break;
			}
			n = 0;
			dialog.text = "Le coût dépend de la taille du navire. De quel navire s'agit-il ?";
			for (i = 0; i < COMPANION_MAX; i++)
			{
				idx = GetCompanionIndex(pchar, i);
				if (idx < 0) continue;

				sld = GetCharacter(idx);
				realShip = GetRealShip(GetCharacterShipType(sld));
				if (CheckAttribute(realShip, "tuning.SpecialityUpgrade")) continue;
				if (!IsFellowOurCrew(sld)) continue;

				n++;
				sTemp = "l"+n;
				link.(sTemp) = XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName) + " '" + sld.Ship.Name + "'.";
				link.(sTemp).go = Dialog.currentNode + "_chosenIdx/" + idx;
			}

			if (n == 0)
			{
				dialog.text = "Malheureusement, l'inscription au registre est un service unique pour chaque navire individuel. Autre chose ?";
				link.l1 = "Alors une autre fois.";
				link.l1.go = "ClockTower_OfficeServices_exit";
			}
		break;

		case "ClockTower_OfficeServices_buffSpec_chosenIdx":
			sld = GetCharacter(sti(Dialog.tmpIdx));
			sTemp = "";
			if (CanUpgradeShip(sld, &sTemp, "SpecialityUpgrade"))
			{
				n = GetSpecialityUpgradeShipCost(sld);
				dialog.text = "Voyons voir... Cela coûtera " + n + " doublons.";
				if (PCharDublonsTotal() > n)
				{
					link.l1 = "Procédez.";
					link.l1.go = "ClockTower_OfficeServices_buffSpec_upgradeShip";
				}
				link.l2 = "Quoique... faisons-le une autre fois.";
				link.l2.go = "ClockTower_OfficeServices_exit";
			}
			else if (sTemp == "Kaleuche")
			{
				dialog.text = "Je suis contraint de refuser. Selon le registre, votre navire est allé au diable des mers il y a bien des années, et un tel fantôme du passé ne peut être effacé d’un coup de plume. Avant que nous puissions coopérer, vous devrez le restaurer. On dit qu’il y a sur Isla Tesoro un maître prêt à entreprendre un tel travail.";
				link.l1 = "C'est clair, merci.";
				link.l1.go = "ClockTower_OfficeServices_exit";
			}
			else if (sTemp == "alreadyUpgraded")
			{
				dialog.text = "$Le navire a déjà été amélioré.";
				link.l1 = "C'est clair, merci.";
				link.l1.go = "ClockTower_OfficeServices_exit";
			}
		break;

		case "ClockTower_OfficeServices_buffSpec_upgradeShip":
			Achievment_Set("ach_CL_199");
			sld = GetCharacter(sti(Dialog.tmpIdx));
			RemoveDublonsFromPCharTotal(GetSpecialityUpgradeShipCost(sld));
			UpgradeShipSpeciality(sld);
			dialog.text = "Terminé.";
			link.l1 = "Merci.";
			link.l1.go = "ClockTower_OfficeServices_exit";
		break;

		// Смена трейта корабля
		case "ClockTower_OfficeServices_changeTrait":
			if (!IsShipInPort(npchar.city))
			{
				ClockTower_NoShipInPort(link);
				break;
			}
			n = 0;
			dialog.text = "Le coût dépend de la taille du navire. De quel navire s'agit-il ?";
			for (i = 0; i < COMPANION_MAX; i++)
			{
				idx = GetCompanionIndex(pchar, i);
				if (idx < 0) continue;

				sld = GetCharacter(idx);
				realShip = GetRealShip(GetCharacterShipType(sld));
				sTemp = "";
				ShipTraitCanBeChanged(sld, &sTemp);
				if (sTemp == "EmptyShip" || sTemp == "QuestCompanion") continue;

				n++;
				sTemp = "l"+n;
				link.(sTemp) = XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName) + " '" + sld.Ship.Name + "'.";
				link.(sTemp).go = Dialog.currentNode + "_chosenIdx/" + idx;
			}

			if (n == 0)
			{
				dialog.text = "Hum. Je ne vois aucun de vos navires dans le port.";
				link.l1 = "Alors une autre fois.";
				link.l1.go = "ClockTower_OfficeServices_exit";
			}
		break;

		case "ClockTower_OfficeServices_changeTrait_chosenIdx":
			sld = GetCharacter(sti(Dialog.tmpIdx));
			sTemp = "";

			if (ShipTraitCanBeChanged(sld, &sTemp))
			{
				n = GetChangeShipTraitCost(sld);
				dialog.text = "Voyons voir... Cela coûtera " + n + " doublons.";
				if (PCharDublonsTotal() > n)
				{
					link.l1 = "Procédez.";
					link.l1.go = "ClockTower_OfficeServices_changeTrait_upgradeShip";
				}
				link.l2 = "Quoique... faisons-le une autre fois.";
				link.l2.go = "ClockTower_OfficeServices_exit";
			}
			else if (sTemp == "QuestSP")
			{
				dialog.text = "Je regrette, mais cela est impossible. Votre navire est un exemplaire unique, entouré de légendes. Un simple trait de plume ne suffira pas. Avant de collaborer, vous devriez le faire restaurer. On dit qu'à Isla Tesoro, il existe un expert capable de s'en charger.";
				link.l1 = "C'est clair, merci.";
				link.l1.go = "ClockTower_OfficeServices_exit";
			}
			else
			{
				dialog.text = "De quelle spécialisation parlez-vous ? Votre navire est universel, sans particularités distinctives.";
				link.l1 = "Content de savoir, merci.";
				link.l1.go = "ClockTower_OfficeServices_exit";
			}
		break;

		case "ClockTower_OfficeServices_changeTrait_upgradeShip":
			sld = GetCharacter(sti(Dialog.tmpIdx));
			NextDiag.CurrentNode = "ClockTower_OfficeServices";
			DialogExit();
			LaunchChangeShipTraitScreen(sld);
		break;

		// Страховка
		case "ClockTower_OfficeServices_Insurance":
			n = GetInsuranceCost();
			dialog.text = "Voyons voir... Cela coûtera " + n + " doublons.";
			if (PCharDublonsTotal() > n)
			{
				link.l1 = "Procédez.";
				link.l1.go = "ClockTower_OfficeServices_Insurance_done";
			}
			link.l2 = "Quoique... faisons-le une autre fois.";
			link.l2.go = "ClockTower_OfficeServices_exit";
		break;

		case "ClockTower_OfficeServices_Insurance_done":
			pchar.questTemp.ShipInsurance = true;
			RemoveDublonsFromPCharTotal(GetInsuranceCost());
			dialog.text = "Terminé.";
			link.l1 = "Merci.";
			link.l1.go = "ClockTower_OfficeServices_exit";
			Achievment_Set("ach_CL_199");
		break;

		// Награда за пиратов
		case "ClockTower_OfficeServices_logbook":
			dialog.text = "Parfaitement exact. La récompense dépend du nombre de journaux et du danger relatif de leurs propriétaires.\n" +
						  "Combien de journaux avez-vous apportés ?";
			link.l1 = "" + ClockTower_JournalsQty();
			link.l1.go = "ClockTower_OfficeServices_logbook_1";
		break;

		case "ClockTower_OfficeServices_logbook_1":
			dialog.text = "La compagnie vous remercie pour votre travail. Vous êtes dû " + JournalsCost() + " doublons. Veuillez les recevoir et signer ici.";
			link.l1 = "Merci.";
			link.l1.go = "ClockTower_OfficeServices_exit";
			npchar.last_logbook_date = LastSpeakDate();
			Achievment_Set("ach_CL_199");
		break;

		case "ClockTower_OfficeServices_exit":
			DialogExit();
			NextDiag.CurrentNode = "ClockTower_OfficeServices";
		break;

		case "ClockTower_cabinFight":
			QuestAboardCabinDialogExitWithBattle("");
			DialogExit();
			ClockTower_CabinFight2();
		break;
		
		case "ClockTower_cabinPeace":
			DialogExit();
			AddDialogExitQuestFunction("ClockTower_cabinPeace");
		break;
	}
}

void ClockTower_NoShipInPort(ref link)
{
	dialog.text = "Je ne vois pas votre vaisseau dans le port.";
	link.l1 = "Alors une autre fois.";
	link.l1.go = "ClockTower_OfficeServices_exit";
}

int ClockTower_PlaySound_rh2(string name)
{
    float x = stf(loadedLocation.locators.reload.houseO2.x);
    float y = stf(loadedLocation.locators.reload.houseO2.y);
    float z = stf(loadedLocation.locators.reload.houseO2.z);
    return SendMessage(Sound, "lslfff", MSG_SOUND_EVENT_PLAY, name, 0, x, y, z);
}
