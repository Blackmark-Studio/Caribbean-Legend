// посредник-дипломат кланов Джузеппе Фацио
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int iTemp;
	string sTemp;
	float locx, locy, locz;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Bonjour, bonjour... Es-tu nouveau ici ? Je ne me souviens pas de ton visage. Permets-moi de me présenter - je suis Giuseppe Fazio, spécialiste en résolution de problèmes sur cette petite île.";
				link.l1 = TimeGreeting()+". Mon nom est "+GetFullName(pchar)+"Vous avez raison, je suis nouveau ici. Pardonnez ma curiosité - mais quel genre de problèmes résolvez-vous ?";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, toi encore, cher "+pchar.name+" ! Qu'est-ce qui vous amène dans ma modeste demeure ?";
				if (CheckAttribute(pchar, "GenQuest.NarvalConflict") || CheckAttribute(pchar, "GenQuest.RivadosConflict") || CheckAttribute(pchar, "GenQuest.SharkConflict"))
				{
					link.l10 = "Fazio, j'ai un sérieux conflit avec un clan. Je dois résoudre ce problème.";
					link.l10.go = "conflict";
				}
				// --> квестовые ветки
				if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "search_mush_3")
				{
					link.l4 = "Giuseppe, je cherche un homme du nom d'Adolf Barbier. On m'a dit que tu avais bu avec lui à la taverne récemment...";
					link.l4.go = "adolf";
				}
				if (CheckAttribute(pchar, "questTemp.LSC.Drink") && pchar.questTemp.LSC.Drink == "begin")
				{
					link.l5 = "Giuseppe, on dit que tu es complètement résistant aux boissons. Peu importe combien tu bois, tu restes debout.";
					link.l5.go = "drink";
				}
				if (CheckAttribute(pchar, "questTemp.LSC.Drink") && PCharDublonsTotal() >= 100 && pchar.questTemp.LSC.Drink == "wait")
				{
					link.l5 = "Je suis prêt à jouer à votre jeu. Voici ma mise.";
					link.l5.go = "drink_4";
				}
				// <-- квестовые ветки
				if (CheckAttribute(npchar, "quest.parol"))
				{
					link.l1 = "Je veux connaître le mot de passe actuel des clans pour entrer dans leurs territoires.";
					link.l1.go = "parol_choice";
				}
				link.l2 = LinkRandPhrase("As-tu quelque chose d'intéressant à raconter ?","Y a-t-il eu du nouveau sur l'île ?","Me raconteras-tu les derniers potins ?");
				link.l2.go = "rumours_LSC";
				link.l3 = "Rien de spécial, Giuseppe. Je voulais juste te voir.";
				link.l3.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting":
			dialog.text = "De toutes sortes, ma chère, de toutes sortes. Par exemple, je joue les entremetteurs entre l'amiral et les clans. Comme vous le savez peut-être déjà, les Rivados, les Narvals et l'amiral sont des ennemis jurés. J'agis comme médiateur lorsque les choses se compliquent.\nDe plus, je fais souvent office de partie neutre lorsque l'amiral vend des provisions aux clans. Mais ce n'est qu'une petite partie de mes affaires. Donc, si vous avez des ennuis avec les Rivados ou les Narvals, n'hésitez pas à me demander de l'aide, nous verrons ce qui peut être fait.";
			link.l1 = "D'accord. J'y réfléchirai.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		// пароли
		case "parol_choice":
			dialog.text = "Quel clan ?";
			link.l1 = "Narvals.";
			link.l1.go = "parol_nrv";
			link.l2 = "Rivados.";
			link.l2.go = "parol_rvd";
		break;
		
		case "parol_nrv":
			dialog.text = "Tu veux voir Donald Greenspen, n'est-ce pas ?";
			link.l1 = "D'accord. Alors, connais-tu le mot de passe ?";
			link.l1.go = "parol";
			pchar.questTemp.LSC.parol = "Narwals";
			sTotalTemp = sNrvParol;
		break;
		
		case "parol_rvd":
			dialog.text = "Vous voulez voir Black Eddie, n'est-ce pas ?";
			link.l1 = "Quelque chose comme ça. Alors, connais-tu le mot de passe ?";
			link.l1.go = "parol";
			pchar.questTemp.LSC.parol = "Rivados";
			sTotalTemp = sRvdParol;
		break;
		
		case "parol":
			if (!CheckAttribute(npchar, "quest.parolrules"))
			{
				dialog.text = "Bien sûr ! Mais laissez-moi vous donner quelques détails d'abord. Les mots de passe ne contiennent qu'un seul mot et changent chaque semaine. Chaque septième, quatorzième, vingt et unième et vingt-huitième jour du mois\nAlors surveillez la date actuelle pour éviter toute erreur. Enfin, comme vous devez le comprendre, ce n'est pas une œuvre de charité. Cinquante doublons pour un mot de passe. N'oubliez pas, uniquement des doublons.";
				link.l1 = "Cinquante doublons ? C'est une somme énorme !";
				link.l1.go = "parol_1";
			}
			else
			{
				dialog.text = "Bien sûr, mon garçon. Tu connais le prix. As-tu cinquante doublons?";
				if (PCharDublonsTotal() >= 50)
				{
					link.l1 = "Oui. Prends tes pieces.";
					link.l1.go = "parol_pay";
				}
				link.l2 = "Malheureusement, je ne sais pas. Peut-être plus tard...";
				link.l2.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "parol_1":
			dialog.text = "Eh bien, mon garçon, calme-toi. Ne sois pas avide, fais-moi confiance : je connais le véritable prix de mes renseignements. Tu ne vas pas simplement te promener autour des navires de "+pchar.questTemp.LSC.parol+" n'est-ce pas ? C'est exact. Alors, tu dois être prêt à perdre quelques pièces... Alors, es-tu prêt à payer cinquante doublons ?";
			if (PCharDublonsTotal() >= 50)
			{
				link.l1 = "Oui. Prenez vos piastres.";
				link.l1.go = "parol_pay";
			}
			link.l2 = "Malheureusement, je n'ai pas autant d'argent. Peut-être plus tard...";
			link.l2.go = "exit";
			NextDiag.TempNode = "First time";
			npchar.quest.parolrules = "true";
		break;
		
		case "parol_pay":
			RemoveDublonsFromPCharTotal(50);
			dialog.text = "Parfait ! C'est un plaisir de faire affaire avec vous. Le mot de passe actuel pour "+pchar.questTemp.LSC.parol+" est : '"+sTotalTemp+"Souviens-t'en bien et ne fais pas d'erreur ou je ne donnerai pas une seule pièce pour ta vie.";
			link.l1 = "Je sais, je sais... Merci !";
			link.l1.go = "exit";
			AddQuestRecord("LSC", "parol");
			AddQuestUserData("LSC", "sText", pchar.questTemp.LSC.parol);
			AddQuestUserData("LSC", "sParol", sTotalTemp);
			if (pchar.questTemp.LSC.parol == "Rivados") pchar.questTemp.LSC.RParol_bye = "true";
			else pchar.questTemp.LSC.NParol_bye = "true";
		break;
		
		case "adolf":
			dialog.text = "Ah, mais bien sûr, mon bon vieux Adolfo ! Oui, j'ai eu une conversation avec lui. Voyez-vous, ma chère, j'étais ravi de récupérer mon argent, l'argent que je pensais ne jamais revoir ! Adolfo avait emprunté une grosse somme en mettant en garantie son fusil exceptionnel et il avait des difficultés à me rendre mon argent\nJ'avais perdu tout espoir de les récupérer et j'étais sur le point de vendre ce stutzen à notre bien-aimé Axel Yost. Mais soudain, le cher Adolfo m'a rapporté mon or ! Il s'est avéré qu'il avait réussi à obtenir assez de pièces non seulement pour racheter son stutzen, mais aussi pour acheter une cabine de Sessile Gallard à la proue du 'Santa Florentina' !\nBien sûr, c'est bien mieux que de vivre dans une cale à moitié immergée\nAinsi, Adolfo a récupéré son fusil, un nouveau chez-lui et moi mon argent. Comment pourrais-je refuser de boire un verre avec lui, surtout quand c'est lui qui paie ?";
			link.l1 = "Ah, bien sûr ! Tu avais beaucoup de raisons de boire. Et gratuitement... Merci, Giuseppe, tu m'as beaucoup aidé. Maintenant, je sais où trouver Adolf.";
			link.l1.go = "adolf_1";
		break;
		
		case "adolf_1":
			dialog.text = "C'est toujours un plaisir, cher. Mais ne cherche pas Adolfo dans sa cabine avant que le soir ne tombe, il est très occupé, à courir pour ses affaires... Oui, et viens me voir plus souvent, pour discuter !";
			link.l1 = "Je t'inviterai quand j'aurai ma propre cabine... Adieu et bonne chance !";
			link.l1.go = "adolf_2";
		break;
		
		case "adolf_2":
			DialogExit();
			LSC_CreateAdolfClone(); // заменяем Адольфа клоном
			pchar.questTemp.Saga.SharkHunt = "search_mush_4"; //флаг на Адольфа в каюте
			AddQuestRecord("SharkHunt", "14");
		break;
		
		case "whiskey":
			switch (sti(npchar.quest.poisonnode))
			{
				case 1: // у себя
					dialog.text = "Ah? Pourquoi envahissez-vous mon territoire comme s'il y avait un incendie? Pour qui vous prenez-vous??";
					link.l1 = "Ta justice... empoisonneur !";
					link.l1.go = "whiskey_1";
				break;
				
				case 2: // на Эве
					dialog.text = "Épargne-moi ! Je le jure, ils m'ont forcé ! Ils ont mis un pistolet contre ma...";
					link.l1 = "Ferme-la. Je le sais. Où est le dernier salaud ? Où est Marcello Cyclope ?!";
					link.l1.go = "whiskey_3";
					SetFunctionTimerCondition("LSC_FacioReturn", 0, 0, 1, false); // вертаем на место Фацио через сутки
				break;
				
				case 3: // у Акулы
					dialog.text = "Je le jure, ils m'ont forcé ! J'ai déjà tout dit à l'amiral ! Je ne pouvais pas leur résister, ils auraient...";
					link.l1 = "Ferme-la. Je le sais. Où est le dernier salaud ? Où est Marcello Cyclope ?!";
					link.l1.go = "whiskey_3";
					SetFunctionTimerCondition("LSC_FacioReturn", 0, 0, 1, false); // вертаем на место Фацио через сутки
				break;
			}
		break;
		
		case "whiskey_1":
			dialog.text = "Qu... qu'avez-vous dit ?";
			link.l1 = "Je sais tout, salaud. Tu as travaillé avec Chad Kapper. Tu as apporté un tonneau de rhum empoisonné à l'amiral. Maintenant prie, pauvre fumier...";
			link.l1.go = "whiskey_2";
		break;
		
		case "whiskey_2":
			dialog.text = "Attendez ! Arrêtez ! Épargnez-moi ! Je le jure, ils m'ont forcé ! Ils avaient un pistolet contre mon...";
			link.l1 = "Tais-toi. Je le sais. Où est le dernier salaud ? Où est Marcello Cyclope ?!";
			link.l1.go = "whiskey_3";
		break;
		
		case "whiskey_3":
			dialog.text = "Je... Je... Je ne sais pas!";
			link.l1 = "Tu mens, raclure ! Je le vois. Où est Cyclope ?";
			if (pchar.questTemp.LSC.Mary == "die") link.l1.go = "whiskey_10"; // ушел на Флерон
			else link.l1.go = "whiskey_4";
		break;
		
		case "whiskey_4":
			dialog.text = "Il... il a reçu un ordre de Kapper et est parti. Je ne sais pas où il est !";
			link.l1 = "Encore des mensonges. Tu sais tout. Ne sois pas lâche, sale créature - Kapper est mort et il ne te fera plus de mal. Mais si tu ne me dis pas où est Marcello - je t'égorgerai comme un cochon tout de suite ! Qu'est-ce que Chad a ordonné au Cyclope ?";
			link.l1.go = "whiskey_5";
		break;
		
		case "whiskey_5":
			dialog.text = "Il l'a envoyé pour tuer... Mary la Rouge.";
			link.l1 = "Quoi ?! Parle maintenant, comment compte-t-il faire cela ? Il est impossible d'entrer dans sa cabine ! Comment prévoit-il de la tuer ?!";
			link.l1.go = "whiskey_6";
		break;
		
		case "whiskey_6":
			dialog.text = "Il entrera dans la cabine de Jurgen pendant que le forgeron est dehors. Ensuite, il se dirigera vers le fond de la cale, la traversera et atteindra la cabine de Mary. \nEnsuite, il n'aura plus qu'à attendre que la fille tourne le dos ou s'endorme. C'est ce que Chad m'a dit. Je ne sais rien de plus, je le jure !";
			link.l1 = "Ça suffira. Quand est-il parti ? Quand, je vous le demande, Cyclope est-il allé à la 'Forge de Cérès' ?";
			link.l1.go = "whiskey_7";
		break;
		
		case "whiskey_7":
			dialog.text = "Il doit déjà être dans la cabine de Jurgen... ou en train de descendre dans la cale...";
			link.l1 = "Merde! Je n'ai pas le temps de nager autour de l'Île! Dis-moi le mot de passe pour les navires des Narvals! Parle, et si tu me mens, je resterai vivant de toute façon, mais toi, tu mourras à coup sûr!";
			link.l1.go = "whiskey_8";
		break;
		
		case "whiskey_8":
			dialog.text = "'"+sNrvParol+"...";
			link.l1 = "D'accord. Maintenant, priez pour que la fille survive.";
			link.l1.go = "whiskey_9";
		break;
		
		case "whiskey_9":
			DialogExit();
			chrDisableReloadToLocation = false;//открыть локацию
			NextDiag.CurrentNode = "whiskey_repeat";
			pchar.quest.LSC_RescueMary.win_condition.l1 = "location";
			pchar.quest.LSC_RescueMary.win_condition.l1.location = "LostShipsCity_town";
			pchar.quest.LSC_RescueMary.function = "LSC_RescueMary";
			AddQuestRecord("SharkHunt", "46");
			AddQuestUserData("SharkHunt", "sParol", sNrvParol);
			pchar.questTemp.LSC.NParol_bye = "true";
		break;
		
		case "whiskey_repeat":
			dialog.text = "Je t'ai déjà dit tout ce que je savais ! Je le jure !";
			link.l1 = "... ";
			link.l1.go = "exit";
			NextDiag.TempNode = "whiskey_repeat";
		break;
		
		case "whiskey_10":
			dialog.text = "Il... Il est quelque part à l'intérieur du 'Fleron'. Chad lui a ordonné de s'y cacher et d'attendre ses prochaines instructions.";
			link.l1 = "Je vois. Cela a intérêt à être la vérité...";
			link.l1.go = "whiskey_11";
		break;
		
		case "whiskey_11":
			DialogExit();
			chrDisableReloadToLocation = false;//открыть локацию
			pchar.quest.LSC_FindCyclop.win_condition.l1 = "location";
			pchar.quest.LSC_FindCyclop.win_condition.l1.location = "FleuronTavern";
			pchar.quest.LSC_FindCyclop.function = "LSC_SetCyclop_Fl";
			NextDiag.CurrentNode = "whiskey_repeat";
			AddQuestRecord("SharkHunt", "51");
			
		break;
		
		// --> конфликты
		case "conflict":
			dialog.text = "Vraiment ? Eh bien, mon garçon, quel clan te cause des soucis ?";
			if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
			{
				link.l1 = "Narvals.";
				link.l1.go = "narval";
				npchar.quest.clan = "narval";
			}
			if (CheckAttribute(pchar, "GenQuest.RivadosConflict"))
			{
				link.l2 = "Rivados.";
				link.l2.go = "rivados";
				npchar.quest.clan = "rivados";
			}
			if (CheckAttribute(pchar, "GenQuest.SharkConflict"))
			{
				link.l3 = "Pirates de l'amiral.";
				link.l3.go = "shark";
				npchar.quest.clan = "shark";
			}
			link.l4 = "Il n'y a rien de tel. Je plaisantais, Giuseppe, je vais bien.";
			link.l4.go = "exit";
		break;
		
		case "narval":
			npchar.quest.price = sti(pchar.GenQuest.NarvalConflict)*50;
			if (sti(pchar.GenQuest.NarvalConflict) < 3) dialog.text = "Eh bien, ce n'est pas vraiment un conflit, juste un petit malentendu, he-he. "+sti(npchar.quest.price)+"  doublons et votre problème sera résolu en un jour.";
			else
			{
				if (sti(pchar.GenQuest.NarvalConflict) >= 3 && sti(pchar.GenQuest.NarvalConflict) < 10) dialog.text = "Bien sûr, j'en ai entendu parler. Tu as semé une belle pagaille, ma chère. Mais il y a une échappatoire. "+sti(npchar.quest.price)+" doubloons et votre problème sera résolu en un jour.";
				else dialog.text = "L'Île entière est au courant du massacre que tu as commis. Ce ne sera pas facile de t'aider, mais il y a une chance."+sti(npchar.quest.price)+" doubloons et je vais tenter de résoudre ton problème.";
			}
			if (PCharDublonsTotal() >= sti(npchar.quest.price))
			{
				link.l1 = "Tiens, prends tes écus et débrouille-toi avec ça.";
				link.l1.go = "pay";
			}
			link.l2 = "Malheureusement, je n'ai pas assez de doublons avec moi en ce moment. Mais je les apporterai plus tard, et nous parlerons à nouveau.";
			link.l2.go = "exit";
		break;
		
		case "rivados":
			npchar.quest.price = sti(pchar.GenQuest.RivadosConflict)*50;
			if (sti(pchar.GenQuest.RivadosConflict) < 3) dialog.text = "Eh bien, ce n'est pas vraiment un conflit, juste un petit malentendu, héhé. "+sti(npchar.quest.price)+"  doublons et votre problème sera résolu en un jour.";
			else
			{
				if (sti(pchar.GenQuest.RivadosConflict) >= 3 && sti(pchar.GenQuest.RivadosConflict) < 10) dialog.text = "Bien sûr, j'en ai entendu parler. Tu as fait un joli désordre, ma chère. Mais il y a une issue. "+sti(npchar.quest.price)+"  doublons et votre problème sera résolu en un jour.";
				else dialog.text = "Tout l'île est au courant du massacre que tu as commis. Ce ne sera pas facile de t'aider, mais il y a une chance."+sti(npchar.quest.price)+" doublons et j'essaierai de résoudre votre problème.";
			}
			if (PCharDublonsTotal() >= sti(npchar.quest.price))
			{
				link.l1 = "Tiens, prends tes pièces et débrouille-toi avec ça.";
				link.l1.go = "pay";
			}
			link.l2 = "Malheureusement, je n'ai pas assez de doublons avec moi en ce moment. Mais je les apporterai plus tard, et nous parlerons à nouveau.";
			link.l2.go = "exit";
		break;
		
		case "shark":
			npchar.quest.price = sti(pchar.GenQuest.SharkConflict)*50;
			if (sti(pchar.GenQuest.SharkConflict) < 3) dialog.text = "Eh bien, ce n'est pas vraiment un conflit, juste un petit malentendu, hé-hé. "+sti(npchar.quest.price)+" doubloons et votre problème sera résolu en un jour.";
			else
			{
				if (sti(pchar.GenQuest.SharkConflict) >= 3 && sti(pchar.GenQuest.SharkConflict) < 10) dialog.text = "Bien sûr, j'en ai entendu parler. Tu as fait un sacré bazar, ma chère. Mais il y a une issue."+sti(npchar.quest.price)+" doubloons et votre problème sera résolu en un jour.";
				else dialog.text = "Tout L'Île Justice est au courant du massacre que tu as commis. Ce ne sera pas facile de t'aider, mais il y a une chance."+sti(npchar.quest.price)+" doublons et j'essaierai de résoudre votre problème.";
			}
			if (PCharDublonsTotal() >= sti(npchar.quest.price))
			{
				link.l1 = "Tiens, prends tes pièces et débrouille-toi avec ça.";
				link.l1.go = "pay";
			}
			link.l2 = "Malheureusement, je n'ai pas assez de doublons avec moi pour l'instant. Mais je les apporterai plus tard, et nous parlerons à nouveau.";
			link.l2.go = "exit";
		break;
		
		case "pay":
			RemoveDublonsFromPCharTotal(sti(npchar.quest.price));
			PlaySound("interface\important_item.wav");
			Log_Info("You have given "+sti(npchar.quest.price)+" doubloons");
			dialog.text = "Splendide. Maintenant, prends un siège et repose-toi. Tu ferais mieux de rester dans ma cabine jusqu'à ce que je résolve ton problème. Je ne veux pas que tu l'empire encore, mon cher.";
			link.l1 = "Très bien...";
			link.l1.go = "peace";
		break;
		
		case "peace":
			DialogExit();
			GetCharacterPos(pchar, &locx, &locy, &locz);
			pchar.locx = locx;
			pchar.locy = locy;
			pchar.locz = locz;
			SetLaunchFrameFormParam("One day later..."+ NewStr() +"Fazio has dealt with the conflict", "Reload_To_Location", 0.1, 5.0);
			SetLaunchFrameReloadLocationParam(pchar.location, "goto", LAi_FindNearestFreeLocator2Pchar("goto"), "LocTeleport");
			WaitDate("", 0, 0, 1, 3, 10); //крутим время
			LaunchFrameForm();
			RefreshLandTime();
			RecalculateJumpTable();
			Whr_UpdateWeather();
			switch (npchar.quest.clan)
			{
				case "narval":
					DeleteAttribute(pchar, "GenQuest.NarvalConflict"); // мирим
					if (CheckAttribute(pchar, "questTemp.LSC.nrv_friend") || !CheckAttribute(pchar, "questTemp.LSC.rvd_friend")) LocatorReloadEnterDisable("LostShipsCity_town", "reload48", false);//открыть вход к Дональду
					LAi_group_SetRelation("LSC_NARVAL", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
				break;
				
				case "rivados":
					DeleteAttribute(pchar, "GenQuest.RivadosConflict"); // мирим
					if (CheckAttribute(pchar, "questTemp.LSC.rvd_friend") || !CheckAttribute(pchar, "questTemp.LSC.nrv_friend")) LocatorReloadEnterDisable("LostShipsCity_town", "reload33", false);//открыть вход к Эдди
					LAi_group_SetRelation("LSC_RIVADOS", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
				break;
				
				case "shark":
					DeleteAttribute(pchar, "GenQuest.SharkConflict"); // мирим
					LSC_OpenSanAvgustinDoors(); // открыть сан-августин
					LSC_OpenTartarusDoors(); // открыть тартарус
					LAi_group_SetRelation("LSC_SHARK", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
				break;
			}
			DeleteAttribute(npchar, "quest.clan");
			DeleteAttribute(npchar, "quest.price");
		break;
		
		// --> пей до дна
		case "drink":
			dialog.text = "Allez, mon garçon ! Ils mentent tous, ha-ha. Ma tête est juste un peu plus dure que la moyenne, mais je suis un être humain tout comme toi, donc je me saoule aussi avec du rhum. Les gens boivent du rhum pour se saouler, c'est son seul but. As-tu déjà pensé à cela, cher ?";
			link.l1 = "Très vrai.";
			link.l1.go = "drink_1";
		break;
		
		case "drink_1":
			dialog.text = "Veux-tu jouer à un jeu amusant avec moi? Ça s'appelle 'boire jusqu'à la lie!', ha-ha! Je suis sûr que tu en as déjà entendu parler. Ai-je raison?";
			link.l1 = "Ouais, il y avait des murmures à ce sujet... Je dirais 'visage sur la table'.";
			link.l1.go = "drink_2";
		break;
		
		case "drink_2":
			dialog.text = "Ha-ha-ha, mon cher garçon, tu as fait rire le vieil homme, que puis-je dire de plus ! 'La tête sur la table !' Je m'en souviendrai... Alors, que dis-tu ? Jouons pour cent doublons ?";
			link.l1 = "Cent doublons ?";
			link.l1.go = "drink_3";
		break;
		
		case "drink_3":
			dialog.text = "Oui, et le perdant paie pour les boissons. Marché conclu ?";
			if (PCharDublonsTotal() >= 100)
			{
				link.l1 = "Oui, marché conclu. Voici ma mise.";
				link.l1.go = "drink_4";
			}
			link.l2 = "Hm. Je n'ai pas tant de doublons que ça.";
			link.l2.go = "drink_wait";
		break;
		
		case "drink_wait":
			dialog.text = "Eh bien, viens me voir quand tu les auras, et nous jouerons !";
			link.l1 = "D'accord...";
			link.l1.go = "exit";
			pchar.questTemp.LSC.Drink = "wait";
		break;
		
		case "drink_4":
			RemoveDublonsFromPCharTotal(100);
			Log_Info("You have given 100 doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "Excellent, mon cher ! Alors rejoins-moi à vingt-et-une heures à la taverne de Sancho ! Oui, ta mise restera avec moi si tu es en retard, c'est l'une des règles. Mais tu ne seras pas en retard, mon garçon, n'est-ce pas ?";
			link.l1 = "Bien sûr, Giuseppe. Prépare-toi pour une bagarre de bouteilles !";
			link.l1.go = "drink_5";
		break;
		
		case "drink_5":
			dialog.text = "Et toi, et toi, ma chère ! Visage sur la table ! Ha-ha !";
			link.l1 = "À neuf heures à la taverne !";
			link.l1.go = "drink_6";
		break;
		
		case "drink_6":
			DialogExit();
			pchar.questTemp.LSC.Drink = "start";
			pchar.quest.LSC_DrinkOver.over = "yes"; //снять таймер
			pchar.quest.LSC_Drink.win_condition.l1 = "Timer";
			pchar.quest.LSC_Drink.win_condition.l1.date.hour  = 21.0;
			pchar.quest.LSC_Drink.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.LSC_Drink.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.LSC_Drink.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.LSC_Drink.function = "LSC_DrinkPrepare";
			pchar.quest.LSC_Drink_Over.win_condition.l1 = "Timer";
			pchar.quest.LSC_Drink_Over.win_condition.l1.date.hour  = 23.0;
			pchar.quest.LSC_Drink_Over.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.LSC_Drink_Over.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.LSC_Drink_Over.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.LSC_Drink_Over.function = "LSC_DrinkDelete";
			AddQuestRecord("LSC_Drink", "2");
		break;
		
		case "drink_8":
			dialog.text = "Eh bien, ma chère, es-tu prête à embrasser la table, hé-hé ? Le bon Sancho nous a déjà apporté du rhum. Pas besoin de te rappeler les règles, je suppose ? Elles sont assez simples : nous buvons la même bouteille jusqu'à ce que l'un de nous tombe.\nOui, nous pouvons parler, nous devons parler ! Parler avec des gens respectables est formidable, n'est-ce pas ? Et si tu gagnes, tu pourras recevoir ton prix de Sancho. Prête ?";
			link.l1 = "Je dirais oui. Commençons, Giuseppe !";
			link.l1.go = "drink_9";
		break;
		
		case "drink_9":
			DialogExit();
			pchar.questTemp.LSC.Drink = "go";
			pchar.quest.LSC_Drink_Over.over = "yes"; //снять таймер
			ChangeCharacterAddressGroup(pchar, "FleuronTavern", "quest", "sit1");
			LAi_SetActorType(pchar);
			LAi_ActorSetSitMode(pchar);
			ChangeCharacterAddressGroup(npchar, "FleuronTavern", "quest", "sit2");
			LAi_SetActorType(npchar);
			LAi_ActorSetSitMode(npchar);
			DoQuestFunctionDelay("LSC_DrinkGo", 0.6);
		break;
		
		case "drunk":
			dialog.text = "Quinze homm-mes sur le maort... hic ! Ahaha ! Yo-ho-ho-kha... Et... bouteille...";
			link.l1 = "Glorieux...";
			link.l1.go = "exit";
			NextDiag.TempNode = "drunk";
		break;
		// <-- пей до дна
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}
