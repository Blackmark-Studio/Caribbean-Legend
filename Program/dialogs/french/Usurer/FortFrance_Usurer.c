// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Quelles questions avez-vous?","Comment puis-je vous aider ?"),"Vous avez essayé de me poser cette question il n'y a pas longtemps...","Ouais, laissez-moi deviner... Encore en train de tourner en rond ?","Ecoutez, je m'occupe des finances ici, je ne réponds pas aux questions...","bloc",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("J'ai changé d'avis...","Je n'ai rien à dire pour le moment."),"Oumph, où est passée ma mémoire...","Vous l'avez deviné, je suis désolé...","Je comprends...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			/* //--> Бремя гасконца
			if (CheckAttribute(pchar, "questTemp.Sharlie.Junglejew") && !CheckAttribute(npchar, "quest.junglejew"))
			{
				link.l1 = "Jetez un œil à ces boucles d'oreilles, monsieur. Je les ai trouvées dans la poche d'un bandit dans la jungle. C’est clairement l'œuvre d'un fin joaillier qui, j'en suis sûr, ne vient pas de cette contrée sauvage. Qu'en dites-vous ?";
                link.l1.go = "Sharlie_junglejew";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "bankskiper")
			{
				link.l1 = "Je sais que vous avez un débiteur du nom de Folke Deluc. Dites-moi, à quel point est-il en... retard de paiement ?";
                link.l1.go = "Sharlie";
			}	
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "bankskipermoney")
			{
				link.l1 = "Je suis ici à propos de la dette de Folke Deluc.";
                link.l1.go = "Sharlie_repeat";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "bankskipercaptive")
			{
				link.l1 = "J'ai terminé votre mission, monsieur. Voici votre... ami espagnol.";
                link.l1.go = "Sharlie_14";
			}
			//<-- Бремя гасконца */
			
			//--> Миниквест "Делюк" (Делюк снова попал в тюрьму)
			if (CheckAttribute(pchar, "questTemp.Del_Rostovshik"))
			{
				link.l1 = "Je suis ici au sujet de...";
                link.l1.go = "Del_Deluck";
			}
			if (CheckAttribute(pchar, "questTemp.Del_Rostovshik_repeat"))
			{
				dialog.text = "As-tu apporté 100 doublons ?";
				if (PCharDublonsTotal() >= 100)
				{
					link.l1 = "Voici votre argent pour mon officier...";
					link.l1.go = "Del_Deluck_5";
				}
				link.l2 = "Non, je réfléchis encore.";
				link.l2.go = "exit";
			}
			//<-- Миниквест "Делюк"
		break;
		
		case "Sharlie":
			DelLandQuestMark(npchar);
			dialog.text = "Et pourquoi cela vous intéresse-t-il, puis-je vous demander?";
			link.l1 = "J'ai besoin que cet homme soit libre, pas derrière les barreaux. Et d'après ce qu'on m'a dit, tant que cette dette ne vous sera pas remboursée, il ne sera pas libéré. Je suis intéressé à régler cette dette.";
			link.l1.go = "Sharlie_1";
		break;
		
		case "Sharlie_1":
			dialog.text = "Aha, cela change tout. Je suis également intéressé par le retour de mon argent... Ce Folke Deluc est un drôle de type. Il a emprunté une somme relativement petite - cinq mille pesos. Il ne voulait tout simplement pas la rendre et a commencé à se cacher. Finalement, les intérêts ont atteint le montant de la dette initiale et il s'est retrouvé derrière les barreaux.";
			link.l1 = "Il s'ensuit que sa dette s'élève actuellement à dix mille ?";
			link.l1.go = "Sharlie_2";
		break;
		
		case "Sharlie_2":
			dialog.text = "Dix mille quatre cent cinquante pesos exactement, monsieur. Donc, sa liberté est fixée à ce montant. Vous êtes prêt à me le payer ? Je suis un peu surpris...";
			if (sti(pchar.money) >= 10450)
			{
				link.l1 = "Ne soyez pas surpris. Voici l'argent.";
				link.l1.go = "Sharlie_3";
			}
			link.l2 = "Hm... Une somme considérable en effet. Écoutez, monsieur, peut-être devrions-nous essayer de conclure un marché ? Par exemple, vous avez quelque chose dont je pourrais m'occuper et vous pourriez évaluer ma faveur à ces dix mille cinq cents...";
			if (CheckAttribute(pchar, "questTemp.Sharlie.FastStart")) link.l2.go = "Sharlie_5x";
			else link.l2.go = "Sharlie_5"; // Addon 2016-1 Jason пиратскаЯ линейка 1
		break;
		
		case "Sharlie_3":
			AddMoneyToCharacter(pchar, -10450);
			dialog.text = "Oui, il semble que vous ayez vraiment besoin de ce marin si vous êtes prêt à débourser une telle somme d'argent pour lui. Quoi qu'il en soit, cela ne me regarde pas, n'est-ce pas monsieur ? Voici son billet de dette, maintenant vous avez droit à sa dette et avez le droit de lui demander de l'argent. Eh bien, et bien sûr, demander sa libération de prison.";
			link.l1 = "C'est exactement ce que je voulais. Adieu, "+npchar.name+" !";
			link.l1.go = "Sharlie_4";
		break;
		
		case "Sharlie_4":
			DialogExit();
			Log_Info("You have received a bill of debt");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "letter_open");
			ChangeItemDescribe("letter_open", "itmdescr_letter_open_usurer");
			pchar.questTemp.Sharlie = "freeskiper";
			AddLandQuestMark(characterFromId("FortFranceJailOff"), "questmarkmain");
		break;
		
		case "Sharlie_5x": // Addon 2016-1 Jason пиратскаЯ линейка 1
			dialog.text = "Une faveur? Hélas, je n'ai nul besoin de tes faveurs. Du moins pour l'instant.";
			link.l1 = "Hélas. Je devrais alors apporter l'argent pour Folke. Adieu !";
			link.l1.go = "exit";
			pchar.questTemp.Sharlie = "bankskipermoney";
		break;
		
		case "Sharlie_5":
			dialog.text = "Faveur ? Hm... Vous savez, monsieur, j'aurais donné une réponse négative si vous étiez venu hier, mais maintenant... oui, j'ai quelque chose qui doit être réglé, mais je vous avertis que c'est assez dangereux.";
			link.l1 = " Dangereux pour quoi ? ";
			link.l1.go = "Sharlie_6";
		break;
		
		case "Sharlie_6":
			dialog.text = "Pour ta précieuse vie, bien sûr. Alors réfléchis-y, avant d'accepter et décide si tu es prêt à faire quelque chose comme ça ou non.";
			link.l1 = "Monsieur, le danger ne m'est pas étranger. J'ai déjà été dans des situations périlleuses tant de fois. Alors, passons aux détails. Tant que cela n'implique pas de neutraliser toute la garnison du fort à moi seul, peut-être que je pourrai accomplir ce à quoi vous faites allusion de manière si mystérieuse.";
			link.l1.go = "Sharlie_7";
		break;
		
		case "Sharlie_7":
			dialog.text = "Très bien. Écoute donc. Ce soir, plusieurs pirates et un prisonnier quitteront la tanière pirate de Le Francois et se rendront à la crique de Le Marin. Le prisonnier est un officier espagnol, et un grand expert en ingénierie de fortifications. Les Britanniques ont l'intention de l'utiliser à leurs propres fins, alors ils enverront un navire de guerre pour récupérer l'homme de la crique.\nL'officier est un vieil ami à moi et je ne veux pas qu'il finisse comme captif anglais. Je ne peux pas demander aux autorités locales de m'aider parce que nous sommes en guerre avec l'Espagne. Si j'avais plus de temps, j'engagerais des hommes capables de reprendre l'espagnol... désolé, de reprendre mon ami, mais hélas !\nTu es le seul homme à qui je peux confier cette tâche. Tu dois te rendre à la crique de Le Marin et... persuader les pirates de te remettre le prisonnier. Je doute qu'ils montrent beaucoup de coopération, donc c'est à toi de jouer.";
			link.l1 = "Combien de pirates seront dans le convoi ?";
			link.l1.go = "Sharlie_8";
		break;
		
		case "Sharlie_8":
			dialog.text = "Je ne sais pas. Peut-être deux personnes, peut-être trois ou quatre. Alors, que diriez-vous ?";
			link.l1 = "Je t'ai déjà dit que 'le danger ne m'est point étranger' et je sais de quel côté tenir une épée.";
			link.l1.go = "Sharlie_10";
			link.l2 = "Hm. Vous avez raison, c'est dangereux. Je n'attaquerai pas un équipage de pirates tout seul.";
			link.l2.go = "Sharlie_9";
		break;
		
		case "Sharlie_9":
			dialog.text = "C'est votre decision. Si vous pensez que vous n'etes pas a la hauteur pour ce travail, alors vous feriez mieux de refuser tout de suite. Ensuite, j'attendrai l'argent de la dette de Deluc.";
			link.l1 = "Très bien. J'apporterai l'argent pour lui. À plus tard !";
			link.l1.go = "exit";
			pchar.questTemp.Sharlie = "bankskipermoney";
		break;
		
		case "Sharlie_10":
			dialog.text = "Très bien. Heureux de l'apprendre. Alors, vous devriez aller à l'anse de Le Marin, les pirates y seront de sept heures du soir à quatre heures du matin. Ne les manquez pas ! Et n'osez même pas utiliser un navire ! De telles actions les effraieraient, allez-y à pied à travers la jungle !\nAmenez-moi le prisonnier lorsque vous le trouverez, je laisserai la porte ouverte. Je vous recommande d'attendre jusqu'à une heure du matin avant de retourner en ville car vous devez éviter l'attention des gardes. Soyez prudent et bonne chance !";
			link.l1 = "Merci ! J'aurai certainement besoin d'un peu de chance...";
			if (CheckAttribute(pchar,"equip."+GUN_ITEM_TYPE)) link.l1.go = "Sharlie_13";
			else link.l1.go = "Sharlie_11";
		break;
		
		case "Sharlie_11":
			dialog.text = "Attendez une minute ! Je vois que vous n'avez même pas de pistolet. Prenez l'un des miens. J'ai aussi plusieurs balles pour lui. Je pense que cela vous sera utile.";
			link.l1 = "Oui, cela sera certainement utile. Merci, monsieur.";
			link.l1.go = "Sharlie_12";
		break;
		
		case "Sharlie_12":
			Log_Info("You have received a combat pistol");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "pistol1");
			TakeNItems(pchar, "bullet", 20);
			TakeNItems(pchar, "gunpowder", 20);
			dialog.text = "Et maintenant, allez, que Dieu vous aide !";
			link.l1 = "...";
			link.l1.go = "Sharlie_13";
		break;
		
		case "Sharlie_13":
			DialogExit();
			pchar.quest.Sharlie_captive_Tut.win_condition.l1 = "location";
			pchar.quest.Sharlie_captive_Tut.win_condition.l1.location = "Shore39";
			pchar.quest.Sharlie_captive_Tut.function = "Tutorial_Rest_Delay";
			pchar.quest.Sharlie_captive.win_condition.l1 = "HardHour";
			pchar.quest.Sharlie_captive.win_condition.l1.hour = 19.00;
			pchar.quest.Sharlie_captive.function = "Captive_Timer";
			SetFunctionTimerCondition("Captive_CreatePiratesOver", 0, 0, 1, false);
			AddQuestRecord("SharlieD", "1");
			pchar.questTemp.Sharlie = "bankskiperfight";
			pchar.questTemp.Sharlie.Captive = "true";
			pchar.questTemp.Sharlie.Captive.Name = GetFullName(npchar);
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			// Rebbebion, новые марки до места назначения
			QuestPointerToLoc("fortfrance_town", "reload", "gate_back");
			QuestPointerToLoc("fortfrance_exittown", "reload", "reload1_back");
			QuestPointerToLoc("martinique_jungle_01", "reload", "reload1_back");
			QuestPointerToLoc("martinique_jungle_02", "reload", "reload2_back");
			QuestPointerToLoc("martinique_jungle_03", "reload", "reload2_back");
		break;
		
		case "Sharlie_14":
			pchar.quest.Sharlie_captive1.over = "yes";
			pchar.quest.Sharlie_captive2.over = "yes";
			pchar.quest.Sharlie_captive3.over = "yes";
			// Rebbebion, новые марки до места назначения
			QuestPointerDelLoc("shore39", "reload", "reload1_back");
			QuestPointerDelLoc("martinique_jungle_03", "reload", "reload2_back");
			QuestPointerDelLoc("martinique_jungle_02", "reload", "reload2_back");
			QuestPointerDelLoc("martinique_jungle_01", "reload", "reload1_back");
			QuestPointerDelLoc("fortfrance_exittown", "reload", "reload1_back");
			QuestPointerDelLoc("fortfrance_town", "reload", "reload8_back");
			DelLandQuestMark(npchar);
			ref sld = characterFromId("CaptiveSpain");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload2", "none", "", "", "", 5.0);
			sld.lifeday = 0;
			SetNationRelation2MainCharacter(FRANCE, RELATION_FRIEND);
			DeleteAttribute(pchar, "questTemp.Sharlie.Captive");
			dialog.text = "Magnifique ! Je suis très heureux que tu aies pu gérer cela avec succès. Je suppose que je n'ai pas besoin de connaître les détails de l'opération, n'est-ce pas ?  Alors, mon cher invité espagnol peut maintenant se sentir en sécurité dans ma maison...";
			link.l1 = "Qu'en est-il de la dette de Folke Deluc ?";
			link.l1.go = "Sharlie_15";
		break;
		
		case "Sharlie_15":
			dialog.text = "Bien sûr, oui. Prenez son billet de dette, maintenant vous avez droit à sa dette et le droit de lui demander de l'argent. Eh bien, et bien sûr, demandez sa libération de prison. Ai-je tout fait comme promis ?";
			link.l1 = "Oui, monsieur. Tout est rigoureusement conforme à l'accord. Maintenant, permettez-moi de prendre congé.";
			link.l1.go = "Sharlie_4";
			AddQuestRecord("SharlieD", "7");
			CloseQuestHeader("SharlieD");
			DeleteAttribute(pchar, "questTemp.Sharlie.Captive");
		break;
		
		case "Sharlie_repeat":
			dialog.text = "Alors, êtes-vous prêt à payer sa dette ?";
			if (sti(pchar.money) >= 10450)
			{
				link.l1 = "Oui. Voici l'argent.";
				link.l1.go = "Sharlie_3";
			}
			link.l2 = "Malheureusement, je n'ai pas encore réuni la somme requise...";
			link.l2.go = "exit";
		break;
		
		case "Sharlie_junglejew":
			dialog.text = "Hm. Il semble que vous ayez raison, ce sont des boucles d'oreilles coûteuses et elles ont sûrement été fabriquées dans l'Ancien Monde... Que puis-je dire ? Je vous en donnerai trente... non, même trente-cinq doublons d'or. Prenez l'argent, vous ne les vendrez pas plus cher.";
			link.l1 = "Trente-cinq doublons ? Ce n'est pas un mauvais prix. Je suis d'accord. Tenez, voici.";
			link.l1.go = "Sharlie_junglejew_1";
			link.l2 = "Non. Je pense que je vais garder ces boucles d'oreilles pour moi.";
			link.l2.go = "exit";
			npchar.quest.junglejew = "true";
		break;
		
		case "Sharlie_junglejew_1":
			DialogExit();
			PlaySound("interface\important_item.wav");
			Log_Info("You've given the earrings");
			RemoveItems(pchar, "jewelry25", 1);
			TakeNItems(pchar, "gold_dublon", 35);
			AddQuestRecord("SharlieE", "3");
			CloseQuestHeader("SharlieE");
			DeleteAttribute(pchar, "questTemp.Sharlie.Junglejew");
			if(!CheckAttribute(pchar, "questTemp.Sharlie.Pardon"))
			{
				DelLandQuestMark(characterFromId("FortFrance_Mayor"));
			}
		break;
		
		//--> Миниквест "Делюк"
		case "Del_Deluck":
			DeleteAttribute(pchar, "questTemp.Del_Rostovshik");
			dialog.text = "Je sais, je sais, Capitaine. Votre navigateur semble avoir accumulé des dettes dans presque toutes les colonies françaises. À vrai dire, j'en étais conscient depuis longtemps. J'ai vérifié avec mes collègues, une procédure standard, vous voyez...";
			link.l1 = "Et vous n'avez pas jugé que c'était assez important pour m'en informer lors de notre arrangement précédent ?";
			link.l1.go = "Del_Deluck_2";
		break;
		
		case "Del_Deluck_2":
			dialog.text = "Pourquoi ? A l'époque, je m'inquiétais principalement de la dette de Deluc envers moi, qui, soit dit en passant, était la plus importante. Une fois que vous l'avez réglée, j'ai rapidement informé mes collègues... Nous avons une vaste flotte de courriers professionnels, donc il ne m'a pas fallu longtemps avant d'amasser une pile de factures de Deluc sur mon bureau.";
			link.l1 = "Je vois... Vous les avez achetés en sachant que j'ai un intérêt vital en lui et les moyens de payer... C'est de l'extorsion, Monsieur.";
			link.l1.go = "Del_Deluck_3";
		break;
		
		case "Del_Deluck_3":
			dialog.text = "C'est juste des affaires, Capitaine ! La dette totale de Deluc s'élève à cent doublons, et les intérêts s'accumulent... Êtes-vous prêt à la racheter ?";
			link.l1 = "Je ne suis pas encore prêt à répondre, mais j'y réfléchirai. Adieu !";
			link.l1.go = "Del_Deluck_4";
		break;
		
		case "Del_Deluck_4":
			DialogExit();
			
			pchar.questTemp.Del_Rostovshik_repeat = true;
			sld = CharacterFromID("Tichingitu");
			if (sld.location == pchar.location && !LAi_IsDead(sld))
			{
				sld.Dialog.Filename = "Quest\Sharlie\Tichingitu.c";
				sld.dialog.currentnode = "Del_Deluck";
				LAi_SetActorType(sld);
				LAi_ActorDialogDelay(sld, pchar, "", 0.0);
			}
		break;
		
		case "Del_Deluck_5":
			dialog.text = "Excellent ! Vous savez ce qu'il faut faire ensuite - comme la dernière fois. Voici les documents - présentez-les au commandant de la prison. Ce fut un plaisir de faire affaire avec vous, Capitaine.";
			link.l1 = "Il y a peu de choses à apprécier dans cette situation. Adieu.";
			link.l1.go = "exit";
			RemoveItems(pchar, "gold_dublon", 100);
			DeleteAttribute(pchar, "questTemp.Del_Rostovshik_repeat");
			Log_Info("You have received a bill of debt");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "letter_open");
			ChangeItemDescribe("letter_open", "itmdescr_letter_open_usurer");
			pchar.questTemp.Del_DeluckSvoboda = true;
			AddLandQuestMark(characterFromId("FortFranceJailOff"), "questmarkmain");
			DelLandQuestMark(npchar);
		break;
		//<-- Миниквест "Делюк"
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
