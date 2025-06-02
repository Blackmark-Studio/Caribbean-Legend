#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 25/06/06

	switch(Dialog.CurrentNode)
	{
		case "First time":
			// --> калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche.SeekAmulet") && hrand(1) == 0 && sti(Pchar.money) >= 2000) 
			{
				dialog.text = "Regardez, monsieur, ne voulez-vous pas acheter une petite chose amusante ? C'est pas cher, juste quelques milliers de pesos...";
				link.l1 = "Hmm. Tu as probablement volé ce 'petit truc', et maintenant tu essaies de t'en débarrasser ?";
				link.l1.go = "caleuche";
				break;
			}
			// <-- калеуче
			if (npchar.quest.meeting == "0")
			{
				dialog.text = LinkRandPhrase("Bonjour. Mon nom est "+GetFullName(npchar)+". Je suppose que tu n'es pas ravi de me rencontrer, mais, peut-être, tu te souviendras au moins de mon nom...","Salutations, "+GetAddress_Form(NPChar)+". Mon nom est "+GetFullName(npchar)+".","Mon nom est "+GetFullName(npchar)+", "+GetAddress_Form(NPChar)+". Enchanté de vous rencontrer.");
				link.l1 = RandPhraseSimple("Salutations.","Bonjour.");
				link.l1.go = "First time";
				// карибские нравы
				if (CheckAttribute(pchar, "questTemp.Trial") && pchar.questTemp.Trial == "spy_drink" && pchar.location == "portobello_town")
				{
					link.l2 = "Hey, écoute, tu aimerais gagner quelques milliers de pesos au lieu de ces pitoyables aumônes?";
					link.l2.go = "trial";
				}
				// --> Тайна Бетси Прайс
				if (CheckAttribute(pchar, "questTemp.TBP_BuyKulon3") && pchar.location == "Villemstad_town")
				{
					link.l2 = "Ce pendentif avec une camée... Où l’as-tu trouvé ?";
					link.l2.go = "TBP_Kulon_1";
				}
				// <-- Тайна Бетси Прайс
				npchar.quest.meeting = "1";
			}			
			else
			{
				dialog.text = NPCStringReactionRepeat("Regarde comme je suis tombé bas...","Vivre des aumônes n'est pas facile...","Je donnerais tout pour sortir de cette pauvreté!","Encore toi ?..","bloc",1,npchar,Dialog.CurrentNode);

				link.l1 = HeroStringReactionRepeat("Je vois. Eh bien, ce n'est pas grave.","Bien sûr. Eh bien, tu sais, le plus grand homme de l'histoire était le plus pauvre.","Alors, tu devrais commencer à faire quelque chose, pas rester assis ici toute la journée.","Ah-ha. Je t'agace déjà?",npchar,Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("exit", "exit", "exit", "pester", npchar, Dialog.CurrentNode);
				link.l2 = RandPhraseSimple("De quoi as-tu besoin?","Que voulez-vous ?");
				link.l2.go = "Whants";
				// карибские нравы
				if (CheckAttribute(pchar, "questTemp.Trial") && pchar.questTemp.Trial == "spy_drink" && pchar.location == "portobello_town")
				{
					DelLandQuestMark(npchar);
					link.l2 = "Hé, écoute, tu aimerais gagner quelques milliers de pesos au lieu de ces pathétiques aumônes?";
					link.l2.go = "trial";
				}
				// --> Тайна Бетси Прайс
				if (CheckAttribute(pchar, "questTemp.TBP_BuyKulon3") && pchar.location == "Villemstad_town")
				{
					link.l2 = "Ce pendentif avec une camée... Où l’as-tu trouvé ?";
					link.l2.go = "TBP_Kulon_1";
				}
				// <-- Тайна Бетси Прайс
				link.l3 = LinkRandPhrase("Pouvez-vous me dire quelque chose d'intéressant?","Quoi de neuf en ville ?","Oh, j'aimerais entendre les derniers potins...");
				link.l3.go = "rumours_poor";
			}
			NextDiag.TempNode = "First time";
		break;
		case "pester":
			dialog.text = RandPhraseSimple("Non, pourquoi, déjà agacé? Je ne suis pas particulièrement occupé, comme tu peux le voir...","Ça me fatigue juste. Bien que pauvre, je suis toujours un homme.");
			link.l1 = "Heh, je vois...";
			link.l1.go = "exit";
		break;
		//выходы
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		//милостыня
		case "Whants":
			if (!CheckAttribute(npchar, "wants_date") || GetNpcQuestPastDayParam(npchar, "wants_date") >= 1 || bBettaTestMode)
    		{
				dialog.text = PCharRepPhrase("Hmm, "+GetAddress_Form(NPChar)+", les gens disent beaucoup de choses laides à votre sujet. Mais je continue de croire en les gens - même en ceux comme vous. S'il vous plaît, donnez-moi l'aumône pour du pain et de l'eau, ayez pitié de moi.","Je vous en supplie, "+GetAddress_Form(NPChar)+"! S'il vous plaît, ne vous détournez pas d'un pauvre homme, donnez l'aumône pour un repas...");
				link.l1 = RandPhraseSimple("Je ne te donnerai rien.","Tu y arriveras sans argent.");
				link.l1.go = "exit";
				Link.l2 = "D'accord, et combien avez-vous besoin exactement ?";
				Link.l2.go = "Whants_1";
			}
			else
			{
				dialog.text = PCharRepPhrase("De toi? Rien.","Je n'ai besoin de rien, "+GetAddress_Form(NPChar)+", merci.");
				link.l1 = RandPhraseSimple("Hmm, d'accord.","Apparemment, ta vie n'est pas aussi mauvaise, mon pote.");
				link.l1.go = "exit";
			}
		break;
		case "Whants_1":
			dialog.text = "Je ne rejetterais même pas un maigre sou, "+GetAddress_Form(NPChar)+". Autant que votre bourse et votre miséricorde peuvent donner...";
			Link.l1.edit = 2;			
			link.l1 = "";
			link.l1.go = "Whants_2";
		break;
		case "Whants_2":
			SaveCurrentNpcQuestDateParam(npchar, "wants_date");
			int iTemp = sti(dialogEditStrings[2]);
			if (iTemp <= 0 || sti(pchar.money) < iTemp)
			{
				dialog.text = "Se moquer des faibles et des fatigués est un péché...";
				link.l1 = "Ha-ha-ha! Tu as pensé pour un moment que je te donnerais de l'argent, toi mendiant dérangé?!";
				link.l1.go = "exit";
				ChangeCharacterComplexReputation(pchar,"nobility", -2);
				break;
			}
			if (iTemp > 0 && iTemp <= 100)
			{
				dialog.text = "Merci pour "+FindRussianMoneyString(iTemp)+", "+GetAddress_Form(NPChar)+". Maintenant, je peux acheter du pain avec cet argent...";
				link.l1 = "Voici, vagabond - va te fortifier un peu.";
				link.l1.go = "exit";
				pchar.money = sti(pchar.money) - iTemp;
				Achievment_SetStat(41, 1);
			}
			if (iTemp > 100 && iTemp <= 500)
			{
				dialog.text = "Merci, "+GetAddress_Form(NPChar)+". Je peux maintenant vivre une semaine avec cet argent !";
				link.l1 = "C'était un plaisir d'aider.";
				link.l1.go = "exit";
				OfficersReaction("good");
				pchar.money = sti(pchar.money) - iTemp;
				Achievment_SetStat(41, 1);
			}
			if (iTemp > 500 && iTemp <= 1000)
			{
				dialog.text = "Merci, "+GetAddress_Form(NPChar)+". Je vais raconter à tout le monde votre gentillesse!";
				link.l1 = "Ceci n'est pas vraiment nécessaire.";
				link.l1.go = "exit";
				ChangeCharacterComplexReputation(pchar,"nobility", iTemp/2000.0+0.5);
				pchar.money = sti(pchar.money) - iTemp;
				Achievment_SetStat(41, 1);
			}
			if (iTemp > 1000 && iTemp <= 5000)
			{
				dialog.text = "Merci, respecté "+GetSexPhrase("monsieur","madame")+" "+GetAddress_Form(NPChar)+". Que le Seigneur veille sur toi...";
				link.l1 = "Ouais, Sa protection ne ferait certainement pas de mal!";
				link.l1.go = "exit";
				ChangeCharacterNationReputation(pchar, sti(NPChar.nation), iTemp/10000.0+0.5);
				pchar.money = sti(pchar.money) - iTemp;
				Achievment_SetStat(41, 1);
			}
			if (iTemp > 5000 && iTemp <= 10000)
			{
				dialog.text = "Merci, "+GetSexPhrase("monsieur le plus estimé","dame très estimée")+" "+GetAddress_Form(NPChar)+". Je vous souhaite le meilleur !";
				link.l1 = "Merci, mon pote.";
				link.l1.go = "exit";
				AddCharacterExpToSkill(pchar, "Leadership", iTemp/5000.0);
				AddCharacterExpToSkill(pchar, "Fortune", iTemp/5000.0);
				pchar.money = sti(pchar.money) - iTemp;
				Achievment_SetStat(41, 1);
			}
                 if (iTemp > 10000 && iTemp < 25000)
			{
				dialog.text = "Ecoute, "+GetAddress_Form(NPChar)+", êtes-vous fou ou quoi? Vous me donnez "+FindRussianMoneyString(iTemp)+"! Je ne peux pas accepter un tel argent, il doit sûrement y avoir un piège... Laissez-moi tranquille !";
				link.l1 = "Eh bien, comme vous voulez...";
				link.l1.go = "exit";
			}
                 if (iTemp == 25000)
			{
				dialog.text = "Vingt-cinq mille acceptés ... Cet argent suffira pour Lelya et moi pour toute une année !";
				link.l1 = "Vive cette année d'abord...";
				link.l1.go = "exit";
			}
			if (iTemp > 25000)
			{
				dialog.text = "Ecoute, "+GetAddress_Form(NPChar)+", es-tu fou ou quoi? Tu me donnes "+FindRussianMoneyString(iTemp)+"! Je ne peux pas accepter un tel argent, il doit y avoir un piège... Laisse-moi tranquille !";
				link.l1 = "Eh bien, comme vous voulez...";
				link.l1.go = "exit";
			}
		break;
		
		case "trial":
			DelLandQuestMark(npchar);
			dialog.text = "Une question idiote, senor! Bien sûr, je le ferais! Mais... que devrais-je faire? Vous ne allez certainement pas me donner cet argent juste pour mon beau sourire.";
			link.l1 = "Bien sûr que non. Écoutez maintenant. J'agis au nom du gouverneur lui-même. Sa Grâce soupçonne que quelqu'un au chantier naval sabote délibérément le lancement de 'Alacantara', son galion. Et ses soupçons se sont intensifiés après qu'un espion français a été récemment capturé...";
			link.l1.go = "trial_1";
		break;
		
		case "trial_1":
			dialog.text = "";
			link.l1 = "Sa Grâce a déjà entendu les excuses du charpentier de marine, mais il n'est pas sûr qu'il disait la vérité. Nous devons découvrir qui sabote le travail et pourquoi. Allez aux quais, jetez un œil et demandez aux ouvriers, pourquoi diable 'Alacantara' n'est toujours pas prêt à naviguer...";
			link.l1.go = "trial_2";
		break;
		
		case "trial_2":
			dialog.text = "";
			link.l1 = "Personne ne te soupçonnera, tu pourrais même mettre la main sur un tas de tabac. Quant à moi, personne ne me dira rien. Tout le monde saura pour qui je travaille. Si tu parviens à apprendre quelque chose de valable, tu recevras trois mille pesos. Assez pour abandonner ton 'travail' pendant au moins un mois.";
			link.l1.go = "trial_3";
		break;
		
		case "trial_3":
			dialog.text = "Trois mille pesos? Mais, estimé seigneur...";
			link.l1 = "Tu marchandes avec moi ou quoi ? Oh, et si tu découvres qui est à l'origine de toute cette attente, tu recevras deux mille de plus. Marché conclu ?";
			link.l1.go = "trial_4";
		break;
		
		case "trial_4":
			dialog.text = "D'accord, senor. Cela ne devrait pas être trop difficile - beaucoup de mes vieux copains travaillent sur les quais ces jours-ci. Hé, j'étais aussi un marin il y a longtemps. Comme, il y a dix ans...";
			link.l1 = "Tu pourras me raconter ton histoire de vie plus tard. Retrouve-moi sur le quai la nuit après onze heures. Maintenant, vas-t-en.";
			link.l1.go = "trial_5";
		break;
		
		case "trial_5":
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload5_back", "none", "", "", "OpenTheDoors", 10.0);
			pchar.questTemp.Trial = "spy_poorman";
			pchar.quest.trial_spy_poorman.win_condition.l1 = "Timer";
			pchar.quest.trial_spy_poorman.win_condition.l1.date.hour  = 22.00;
			pchar.quest.trial_spy_poorman.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.trial_spy_poorman.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.trial_spy_poorman.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.trial_spy_poorman.function = "Trial_SetPoormanInPort";
			pchar.quest.Trial_ReturnPoormanNorm.win_condition.l1 = "Timer";
			pchar.quest.Trial_ReturnPoormanNorm.win_condition.l1.date.hour  = 6.00;
			pchar.quest.Trial_ReturnPoormanNorm.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Trial_ReturnPoormanNorm.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Trial_ReturnPoormanNorm.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Trial_ReturnPoormanNorm.win_condition = "Trial_ReturnPoormanNorm";
			//SetTimerCondition("Trial_ReturnPoormanNorm", 0, 0, 1, false);
			AddQuestRecord("Trial", "15");
		break;
		
		case "trial_6":
			dialog.text = "Bonne soirée, senor...";
			link.l1 = "Alors? Avez-vous découvert quelque chose?";
			link.l1.go = "trial_7";
			DelLandQuestMark(npchar);
		break;
		
		case "trial_7":
			dialog.text = "Je l'ai fait, senor, je l'ai fait. Pas sûr de comment tout cela correspond à ce que vous m'avez dit... Avez-vous apporté l'argent ? Cinq mille pesos.";
			if (sti(pchar.money) >= 5000)
			{
				link.l1 = "Ne t'inquiète pas. Voici ton argent. Maintenant crache le morceau.";
				link.l1.go = "trial_8";
			}
			else
			{
				link.l1 = "D'abord l'information, puis l'argent. Allez, ne perds pas mon temps!";
				link.l1.go = "trial_fail";
			}
		break;
		
		case "trial_fail":
			dialog.text = "Vous essayez de me tromper, senor! Si vous ne comptez pas payer - allez demander à quelqu'un d'autre vous-même. Et n'osez même pas penser à atteindre votre épée ou j'appellerai les gardes!";
			link.l1 = "...";
			link.l1.go = "trial_fail_1";
		break;
		
		case "trial_fail_1":
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "OpenTheDoors", 10.0);
			pchar.questTemp.Trial = "spy_fail";
			AddQuestRecord("Trial", "16");
			sld = characterFromId("Florian");
			sld.DeckDialogNode = "florian_failspy_5";
		break;
		
		case "trial_8":
			AddMoneyToCharacter(pchar, -5000);
			dialog.text = "Alors voici comment ça se passe : 'Alcantara' est prêt à partir depuis longtemps, mais il n'a pas été chargé intentionnellement, et par ordre du gouverneur lui-même. Enfin, c'est ce qu'on m'a dit. Et les charpentiers font maintenant toutes sortes de petits travaux différents, qui n'affectent pas le départ du navire. \nTout le monde attend l'arrivée de quelque écorce de Carthagène. Le fait est que 'Alcantara' a, de l'avis de son capitaine, un stock de poudre à canon insuffisant. Donc, le navire est resté ici et a attendu des jours entiers jusqu'à ce que 'Puebla' apporte de la poudre à canon. \nMais tout le monde pense que toute cette attente n'est qu'une perte de temps, donc si 'Puebla' n'arrive pas dans trois jours, 'Alcantara' lèvera l'ancre sans la poudre à canon...";
			link.l1 = "Est-ce vrai? Et qui vous a dit ça? Nom?";
			link.l1.go = "trial_9";
		break;
		
		case "trial_9":
			dialog.text = "L'un des marins de 'Alacantara' - Felipe Dabinho... Mais ce n'est en fait pas du tout un secret, et Son Excellence le gouverneur lui-même avait ordonné...";
			link.l1 = "Je vois. C'est ce que je m'attendais. Des espions français sont dans la ville, mais ces idiots bavardent comme des marchandes, incroyable ! N'importe quel arrivant peut découvrir ce qu'il veut sur les plans de Son Altesse. Oh, ce Felipe Dabinho est dans de sérieux ennuis maintenant ! Et aussi le bosco de l' 'Alacantara' ! C'est de sa faute si son équipage ne sait rien de la discipline !";
			link.l1.go = "trial_10";
			QuestPointerToLoc("PortoBello_Town", "reload", "gate_back");
			QuestPointerToLoc("PortoBello_ExitTown", "reload", "reload1_back");
			QuestPointerToLoc("PortoBello_Jungle_01", "reload", "reload2_back");
			QuestPointerToLoc("PortoBello_Jungle_02", "reload", "reload3_back");
			QuestPointerToLoc("shore47", "reload", "boat");
		break;
		
		case "trial_10":
			dialog.text = "Oh... Alors, tu le savais depuis le début ? Mais pourquoi... Ce n'est pas ma faute ! Tu m'as dit de faire ça !";
			link.l1 = "Ce n'était pas ta faute, tu ne devrais pas t'en inquiéter, personne ne va te punir. Maintenant, nous savons que l'équipage de l' 'Alacantara' peut divulgâcher n'importe quelle information à un ennemi - même ce qui est censé être gardé secret. D'accord, tu peux y aller maintenant. Merci pour ton aide. Va dépenser ton argent.";
			link.l1.go = "trial_11";
			// belamour legendary edition -->
			link.l2 = "Au revoir. (Tue-le)";
			link.l2.go = "trial_11a";
		break;
		
		case "trial_11a":
			DialogExit();
			AddMoneyToCharacter(npchar, 5000);
			npchar.SaveItemsForDead  = true; 
			LAi_SetActorType(pchar);
			// если не надет пистоль или мушкет, то выдадим строевой 
			if(!CheckAttribute(pchar,"equip."+GUN_ITEM_TYPE) || !CheckAttribute(pchar,"equip."+MUSKET_ITEM_TYPE))
			{
				GiveItem2Character(pchar, "pistol1");
				EquipCharacterbyItem(pchar, "pistol1");
			}
			LAi_ActorAnimation(pchar, "Shot", "RIP_Bomzh", 1.0); 
		break;
		
		case "trial_11":
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			AddCharacterExpToSkill(pchar, "Sneak", 50);
			// <-- legendary edition
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "OpenTheDoors", 10.0);
			pchar.questTemp.Trial = "spy_win";
			AddQuestRecord("Trial", "17");
			sld = characterFromId("Florian");
			sld.DeckDialogNode = "florian_12";
			AddLandQuestMark(sld, "questmarkmain");
		break;
		
		// --> калеуче
		case "Caleuche":
			dialog.text = "Excusez-moi, bon monsieur... Je l'ai gagné lors d'un jeu de dés contre un inconnu, je pensais que c'était un amulette de guérison enchantée, mais je m'étais trompé... Il ne guérit pas les maladies, et les marchands du marché n'y sont pas intéressés. Et voilà que vous arrivez - un marin, capitaine, un homme instruit. Jetez un oeil, et vous pourriez le trouver utile.\nPour vous, ces quelques milliers sont une petite somme, mais pour moi, c'est un morceau de pain et une gorgée de rhum pour un mois. Regardez, monsieur...";
			link.l1 = "D'accord, montre...";
			link.l1.go = "Caleuche_1";
		break;
		
		case "Caleuche_1":
			Log_Info("You got a strange amulet");
			PlaySound("interface\important_item.wav");
			dialog.text = "Voici...";
			link.l1 = "Comme ci, comme ça... Chose intéressante, je suis d'accord. Je suis sûr qu'elle a été volée des établissements indiens. D'accord, je vais la prendre. Voici votre argent.";
			link.l1.go = "Caleuche_2";
		break;
		
		case "Caleuche_2":
			AddMoneyToCharacter(pchar, -2000);
			dialog.text = "Merci, monsieur ! J'espère que cette chose vous portera chance ! Que le Seigneur vous protège !";
			link.l1 = "Bonne chance, mon pote. Ne dépense pas tout l'argent d'un coup à la taverne.";
			link.l1.go = "Caleuche_3";
		break;
		
		case "Caleuche_3":
			DialogExit();
			GiveItem2Character(pchar, "kaleuche_amulet1"); 
		break;
		// <-- калеуче
		
		// --> Тайна Бетси Прайс
		case "TBP_Kulon_1":
			dialog.text = "Eh, "+GetAddress_Form(NPChar)+", qu'est-ce que ça peut vous faire, ce vieux bibelot ?";
			link.l1 = "Si je t’envoie mon pied dans la tête maintenant, tu comprendras tout de suite pourquoi ça m’intéresse.";
			link.l1.go = "TBP_Kulon_TO";
			if (CheckAttribute(pchar, "questTemp.TBP_BuyKulon2"))
			{
				link.l2 = "Ce pendentif appartenait à Betsy Price. Alors, où l’as-tu trouvé ?";
				link.l2.go = "TBP_Kulon_leadership";
			}
			DeleteAttribute(pchar, "questTemp.TBP_BuyKulon3");
		break;

		case "TBP_Kulon_TO":
			dialog.text = "Il était dans le parterre près de la maison avec la lanterne, "+GetAddress_Form(NPChar)+". Enfoncé dans la boue par une botte d’homme. Mais plus personne ne vit là depuis longtemps, alors j’ai pensé qu’il n’appartenait à personne...";
			link.l1 = "Hmm...";
			link.l1.go = "exit";
			AddCharacterExpToSkill(pchar, "FencingH", 100);
			DeleteAttribute(pchar, "questTemp.TBP_BuyKulon2");
		break;

		case "TBP_Kulon_leadership":
			dialog.text = "Il était dans le parterre près de la maison avec la lanterne, "+GetAddress_Form(NPChar)+". Enfoncé dans la boue par une botte d’homme. Mais plus personne ne vit là depuis longtemps, alors j’ai pensé qu’il n’appartenait à personne...";
			link.l1 = "Hmm...";
			link.l1.go = "exit";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			DeleteAttribute(pchar, "questTemp.TBP_BuyKulon2");
		break;
		// <-- Тайна Бетси Прайс
	}
}
