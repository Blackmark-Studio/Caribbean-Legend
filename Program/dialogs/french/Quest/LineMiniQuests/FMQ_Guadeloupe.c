// Addon-2016 Jason, французские миниквесты (ФМК) Гваделупа
void ProcessDialogEvent()
{
	ref sld, NPChar;
	aref Link, NextDiag;
	int i;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Un bogue évident. Informez-en les développeurs.";
			link.l1 = "Oh, je le ferai.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		// квестодатель
		case "citizen":
			DelMapQuestMarkCity("Baster");
			LAi_SetImmortal(npchar, false);
			LAi_RemoveLoginTime(npchar);
			dialog.text = "Salutations, capitaine ! J'ai une proposition d'affaire que vous trouverez très intéressante.";
			link.l1 = "Allez-y, monsieur.";
			link.l1.go = "citizen_1";
		break;
		
		case "citizen_1":
			dialog.text = "Je veux louer votre navire pour un travail de transport de la Guadeloupe au Continent espagnol.";
			link.l1 = "Tu veux y naviguer en tant que passager ?";
			link.l1.go = "citizen_2";
			link.l2 = "Les Indes espagnoles ? Je vais passer. Nous ne sommes pas vraiment amis avec les Espagnols. Je te suggère de trouver un autre imbécile.";
			link.l2.go = "citizen_no";
		break;
		
		case "citizen_no":
			dialog.text = "Comme vous dites, capitaine, bien que ce ne soit pas un voyage à haut risque. Adieu.";
			link.l1 = "Adieu.";
			link.l1.go = "citizen_exit";
		break;
		
		case "citizen_no_1":
			dialog.text = "Comme vous voulez, capitaine. Adieu !";
			link.l1 = "Adieu.";
			link.l1.go = "citizen_exit";
		break;
		
		case "citizen_exit":
			DialogExit();
			chrDisableReloadToLocation = false;
			npchar.lifeday = 0;
			DelLandQuestMark(npchar); // Rebbebion, снять марку
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 20.0);
		break;
		
		case "citizen_2":
			dialog.text = "Pas tout à fait, monsieur. Un passager est un homme dépendant de la volonté d'un capitaine. Je veux vous engager, vous, votre équipage et votre navire, afin de me rendre, avec deux amis à moi, à Panama.";
			link.l1 = "Vers Panama ? Comment ? Tu veux naviguer autour de tout le continent ?";
			link.l1.go = "citizen_3";
		break;
		
		case "citizen_3":
			dialog.text = "Ha-ha-ha ! Bonne blague, capitaine. Bien sûr que non. Tout ce que vous avez à faire, c'est de nous livrer à la Baie des Moustiques qui n'est pas loin de Portobello. Nous nous rendrons à Panama par nos propres moyens, ce ne sera pas notre première excursion dans la jungle.";
			link.l1 = "Qu'en est-il du paiement ?";
			link.l1.go = "citizen_4";
		break;
		
		case "citizen_4":
			dialog.text = "Deux coffres de doublons. Trois cents pièces. Vous en recevrez un en avance une fois à bord. Le deuxième coffre sera à vous dès que nous aurons atteint notre destination.";
			link.l1 = "Une récompense sérieuse pour un travail si facile. Où est l'arnaque, mon bonhomme ?";
			link.l1.go = "citizen_5";
		break;
		
		case "citizen_5":
			dialog.text = "Capitaine, le temps c'est de l'argent, mes amis et moi nous n'en avons pas. Nous devons prendre la mer ce soir et nous devons y être dans dix jours. Ce sera notre deuxième mandat. Alors, êtes-vous des nôtres ?";
			link.l1 = "Marché conclu !";
			link.l1.go = "citizen_6";
			link.l2 = "Je suis désolé, monsieur, mais votre proposition me semble bien trop suspecte. Trouvez-vous un autre imbécile.";
			link.l2.go = "citizen_no_1";
		break;
		
		case "citizen_6":
			dialog.text = "Splendide. Mes amis sont dans les jungles en ce moment, je vais leur faire savoir notre accord. Vous nous trouverez à la plage de Capster ce soir à dix heures. Ne soyez pas en retard, Capitaine !";
			link.l1 = "D'accord. Capster Beach, ce soir, dix heures.";
			link.l1.go = "citizen_7";
		break;
		
		case "citizen_7":
			dialog.text = "Un instant, capitaine, nous ne nous sommes même pas présentés. Mon nom est Bertrand Pinette. Et vous êtes...";
			link.l1 = ""+GetFullName(pchar)+". Capitaine "+GetFullName(pchar)+"À bientôt, monsieur Pinette.";
			link.l1.go = "citizen_8";
		break;
		
		case "citizen_8":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "gate_back", "none", "", "", "OpenTheDoors", 20.0);
			AddQuestRecord("FMQ_Guadeloupe", "1");
			pchar.quest.FMQG_Capster.win_condition.l1 = "Hour";
			pchar.quest.FMQG_Capster.win_condition.l1.start.hour = 22.00;
			pchar.quest.FMQG_Capster.win_condition.l1.finish.hour = 23.99;
			pchar.quest.FMQG_Capster.win_condition.l2 = "Ship_location";
			pchar.quest.FMQG_Capster.win_condition.l2.location = "Shore29";
			pchar.quest.FMQG_Capster.win_condition.l3 = "location";
			pchar.quest.FMQG_Capster.win_condition.l3.location = "Shore29";
			pchar.quest.FMQG_Capster.function = "FMQG_CapsterBeach";
			SetFunctionTimerCondition("FMQG_StartLate", 0, 0, 1, false);
			pchar.questTemp.FMQG = "begin";
			pchar.GenQuest.SmugglersBlock = "baster_tavern";
			DelLandQuestMark(npchar); // Rebbebion, снять марку
		break;
		
		case "citizen_9":
			DelLandQuestMark(npchar);
			dialog.text = "Capitaine "+GetFullName(pchar)+", te voilà. Sommes-nous prêts à partir?";
			link.l1 = "Oui. Bienvenue à bord.";
			link.l1.go = "citizen_10";
		break;
		
		case "citizen_10":
			dialog.text = "Très bien. Acceptez votre avance - un coffre rempli de doublons. Et souvenez-vous - vous n'avez que dix jours pour nous amener à destination. Pas un jour de plus !";
			link.l1 = "Je me souviens des termes. Ne t'inquiète pas, nous y serons à temps. Prenez place.";
			link.l1.go = "citizen_11";
		break;
		
		case "citizen_11":
			DialogExit();
			GiveItem2Character(pchar, "chest");
			log_info("You have received a chest full of doubloons");
			PlaySound("interface\important_item.wav");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "officers", "sea_1", "none", "", "", "FMQG_OnBoard", 20.0);
			for (i=2; i<=3; i++)
			{
				sld = characterFromId("FMQG_pass_"+i);
				LAi_ActorRunToLocation(sld, "officers", "sea_"+i, "none", "", "", "", 10.0);
			}
			pchar.quest.FMQG_SailStart.win_condition.l1 = "location";
			pchar.quest.FMQG_SailStart.win_condition.l1.location = "Guadeloupe";
			pchar.quest.FMQG_SailStart.function = "FMQG_SailingStart";
			if(bImCasual)
			{
				NewGameTip("Exploration mode: quest duration doubled");
				SetFunctionTimerCondition("FMQG_SailingLate", 0, 0, 20, false);
				SetFunctionTimerCondition("FMQG_MutiniActivate", 0, 0, 40, false);
			}
			else
			{
				SetFunctionTimerCondition("FMQG_SailingLate", 0, 0, 10, false);
				SetFunctionTimerCondition("FMQG_MutiniActivate", 0, 0, 20, false);
			}
			pchar.questTemp.FMQG = "sail";
			DeleteAttribute(pchar, "GenQuest.SmugglersBlock");
		break;
		
		case "citizen_12":
			dialog.text = "Alors, Capitaine, vous avez entièrement rempli votre part du marché. C'est à mon tour maintenant. Acceptez ce coffre avec notre plus profonde gratitude.";
			link.l1 = "Un plaisir de faire affaire avec vous, monsieur.";
			link.l1.go = "citizen_13";
		break;
		
		case "citizen_13":
			GiveItem2Character(pchar, "chest");
			log_info("You have received a chest full of doubloons");
			PlaySound("interface\important_item.wav");
			AddCharacterExpToSkill(pchar, "Sailing", 200);//навигация
			AddCharacterExpToSkill(pchar, "Leadership", 200);//авторитет
			AddCharacterExpToSkill(pchar, "Sneak", 100);//скрытность
			dialog.text = "De même. Adieu, capitaine "+GetFullName(pchar)+".";
			link.l1 = "Adieu !";
			link.l1.go = "citizen_14";
		break;
		
		case "citizen_14":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 20.0);
			for (i=2; i<=3; i++)
			{
				sld = characterFromId("FMQG_pass_"+i);
				LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", 10.0);
				sld.lifeday = 0;
			}
			AddQuestRecord("FMQ_Guadeloupe", "6");
			CloseQuestHeader("FMQ_Guadeloupe");
			pchar.questTemp.FMQG = "pause";
			pchar.quest.FMQG_Continue.win_condition.l1 = "Ship_location";
			pchar.quest.FMQG_Continue.win_condition.l1.location = "Baster_town";
			pchar.quest.FMQG_Continue.win_condition.l2 = "location";
			pchar.quest.FMQG_Continue.win_condition.l2.location = "Baster_town";
			pchar.quest.FMQG_Continue.function = "FMQG_BasterContinue";
			/* pchar.quest.FMQG_Block1.win_condition.l1 = "Rank";
			pchar.quest.FMQG_Block1.win_condition.l1.value = 13;
			pchar.quest.FMQG_Block1.win_condition.l1.operation = ">=";
			pchar.quest.FMQG_Block1.function = "FMQG_Block"; */
			//SetFunctionTimerCondition("FMQG_Block", 0, 0, 90, false);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);	// лесник - открыть оружие снова.
			AddMapQuestMarkCity("baster", false);
		break;
		
		case "citizen_12a":
			dialog.text = "Alors, Capitaine, nous voilà. Vous n'avez rempli que la moitié de votre part du marché, donc je ferai de même. Gardez votre avance comme paiement complet. J'espère que vous ne vous y opposerez pas, c'était de votre faute après tout.";
			link.l1 = "Je n'aime pas ça, mais j'admets que tu as raison. Séparons-nous maintenant.";
			link.l1.go = "citizen_13a";
		break;
		
		case "citizen_13a":
			AddCharacterExpToSkill(pchar, "Sailing", 50);//навигация
			AddCharacterExpToSkill(pchar, "Leadership", 50);//авторитет
			AddCharacterExpToSkill(pchar, "Sneak", 50);//скрытность
			dialog.text = "Enfin, merci pour le service, capitaine "+GetFullName(pchar)+"Adieu !";
			link.l1 = "Adieu.";
			link.l1.go = "citizen_14";
		break;
		
		case "citizen_15":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("bridgetown");
			dialog.text = "Oh ! Quelle rencontre ! "+TimeGreeting()+", "+GetFullName(pchar)+"! Mais comment ?";
			link.l1 = TimeGreeting()+", monsieur Pinette. Ce n'était pas facile de vous trouver.";
			link.l1.go = "citizen_16";
		break;
		
		case "citizen_16":
			sld = characterFromId("Baster_usurer");
			dialog.text = "Et quelle en est la raison, capitaine ?";
			link.l1 = "Mon bon monsieur, il y a un homme nommé "+GetFullName(sld)+" et il est très impatient de vous voir. Je suppose que vous savez pourquoi.";
			link.l1.go = "citizen_17";
		break;
		
		case "citizen_17":
			sld = characterFromId("Baster_usurer");
			dialog.text = "Bien sûr que oui, mais vous, mon cher Capitaine, devez également savoir que je ne suis pas pressé de voir monsieur "+GetFullName(sld)+" du tout. Es-tu son chasseur de primes ? Je ne comprends tout simplement pas.";
			link.l1 = "Hélas, mais c'est ce que je suis pour le moment et je n'en suis pas heureux. J'ai fait une erreur et maintenant monsieur "+GetFullName(sld)+", maudit soit-il, m'a présenté un choix. C'est soit ton retour glorieux en Guadeloupe, soit c'est mon cul en tant que complice dans ta petite entreprise de libérer don Carlos de Milyar. Cela me fera mal, tu le sais.";
			link.l1.go = "citizen_18";
		break;
		
		case "citizen_18":
			sld = characterFromId("Baster_usurer");
			dialog.text = "Ah, ce salaud ! C'est une manière bien pécheresse de faire chanter les gens !.. Alors, Capitaine, qu'allez-vous faire ? Allez-vous faire un choix ou allez-vous laisser quelqu'un comme ça vous faire chanter ?";
			link.l1 = "Et que penses-tu ? Je crois que tu viens avec moi à Basse-Terre.";
			link.l1.go = "citizen_19";
			link.l2 = "Ai-je le choix ici ?";
			link.l2.go = "citizen_25";
		break;
		
		case "citizen_19":
			dialog.text = "Oh, je dois vous décevoir, Capitaine. Je n'ai aucune envie de monter à bord de votre magnifique navire. Vous n'obtiendrez rien par la force ici, l'endroit est entouré de gardes et je crierai à l'aide si vous montrez la moindre intention violente. Bien sûr, vous pouvez essayer de me poignarder, mais notre bon ami ne recevra pas de pièces d'un cadavre froid. Donc, la manière la plus intelligente pour vous en ce moment - est de me laisser tranquille. Je vous permettrai de partir indemne.";
			link.l1 = "Crois-tu vraiment que je vais simplement m'en aller après tout ce qui s'est passé ? Tu m'as entraîné dans ce foutoir, salaud, il est temps de payer !";
			link.l1.go = "citizen_20";
			link.l2 = "Tu as raison, je suppose. J'aime l'idée de te poignarder, mais c'est inutile. Ne te fais même pas l'illusion que c'est la fin. Je pars maintenant pour Basse-Terre où j'informerai notre bon ami de ta localisation. Et ensuite, il enverra des hommes masqués à ta poursuite.";
			link.l2.go = "citizen_21";
		break;
		
		case "citizen_20":
			dialog.text = "A-ah! Soldats! À l'aide!!!";
			link.l1 = "... ";
			link.l1.go = "citizen_fight";
		break;
		
		case "citizen_21":
			dialog.text = "Mais bien sûr. Dites à votre patron de tenir ses hommes masqués en laisse - je deviens très populaire ces jours-ci. Adieu, Capitaine.";
			link.l1 = "...";
			link.l1.go = "citizen_22";
		break;
		
		case "citizen_22":
			DialogExit();
			LAi_SetActorType(npchar);
			AddQuestRecord("FMQ_Guadeloupe", "19");
			pchar.quest.FMQG_Mayak.win_condition.l1 = "location";
			pchar.quest.FMQG_Mayak.win_condition.l1.location = "Mayak2";
			pchar.quest.FMQG_Mayak.function = "FMQG_Lighthouse";
		break;
		
		case "citizen_23":
			DelLandQuestMark(npchar);
			dialog.text = "Attendez ! Je me rends ! Je me rends !";
			link.l1 = "Exactement ! Maintenant, laisse tomber ton arme et marche vers le navire !";
			link.l1.go = "citizen_24";
		break;
		
		case "citizen_24":
			DialogExit();
			chrDisableReloadToLocation = false;
			RemoveAllCharacterItems(npchar, true);
			DoQuestReloadToLocation("Mayak2", "goto", "goto1", "FMQG_OnLighthouse");
		break;
		
		case "citizen_25":
			dialog.text = "Il y a toujours un choix, capitaine. Si je comprends bien, vous ne me chasseriez pas s'il n'y avait pas de menaces de ce banquier ?";
			link.l1 = "Exactement.";
			link.l1.go = "citizen_26";
		break;
		
		case "citizen_26":
			dialog.text = "Bien. Alors je vais t'organiser un moyen solide de lui fermer la bouche. Écrivons une lettre que tu remettras à ton employeur. Dis-lui que s'il commence à parler, le gouverneur de la Guadeloupe apprendra qui a planifié et investi dans la disparition du Courage - une chaloupe courrier en mission pour transporter une grande cargaison de diamants.";
			link.l1 = "Hm. Je crois que je commence à comprendre, monsieur Pinette.";
			link.l1.go = "citizen_27";
		break;
		
		case "citizen_27":
			dialog.text = "Content que vous soyez aussi avisé, Capitaine. De Lion clouera personnellement la tête de l'avare rusé aux portes de la ville s'il apprend la vérité derrière la disparition du Courage. Dans cette lettre que je suis sur le point d'écrire, vous trouverez des preuves qui calmeront le maître chanteur. Donnez-moi une minute pour prendre ma plume.";
			link.l1 = "D'accord...";
			link.l1.go = "citizen_28";
		break;
		
		case "citizen_28":
			LAi_Fade("", "");
			GiveItem2Character(pchar, "letter_baker");
			ChangeItemDescribe("letter_baker", "itmdescr_letter_pinett");
			dialog.text = " (écriture) Tiens, prends-le. Il y a deux lettres similaires dans ce paquet. Donne-en une au banquier, qu'il en profite. Garde l'autre pour toi et cache-la bien.";
			link.l1 = " L'information est-elle fiable ?";
			link.l1.go = "citizen_29";
		break;
		
		case "citizen_29":
			sld = characterFromId("Baster_usurer");
			AddLandQuestMark(sld, "questmarkmain");
			AddMapQuestMarkCity("Baster", false);
			dialog.text = "Je peux le jurer, vous m'avez aidé et maintenant je vais vous aider. Soyez assuré, le maître chanteur vous laissera tranquille une fois qu'il aura lu ce testament. Ah, oui... Encore une chose, capitaine. Puisque nous avons réglé cela pacifiquement... J'ai une cachette et je vous dirai où la trouver si vous me promettez de vous tenir à l'écart de mes opérations à l'avenir. Ils ne me laisseront jamais poser le pied sur la Guadeloupe de toute façon.";
			link.l1 = "Si la lettre fonctionne comme prévu, alors je peux te le promettre.";
			link.l1.go = "citizen_30";
		break;
		
		case "citizen_30":
			dialog.text = "C'est donc un accord. Cherchez parmi les rochers à l'intérieur de la grotte de Guadeloupe. Que cela vous serve de modeste compensation pour vos ennuis. Bon vent, capitaine.";
			link.l1 = "De même pour vous, monsieur Pinette.";
			link.l1.go = "citizen_31";
		break;
		
		case "citizen_31":
			DialogExit();
			pchar.questTemp.FMQG = "letter";
			AddQuestRecord("FMQ_Guadeloupe", "24");
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 1;
		break;
		
		case "citizen_fight":
			chrDisableReloadToLocation = true;
			LAi_group_Delete("EnemyFight");
			DialogExit();
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			AddDialogExitQuest("MainHeroFightModeOn");
			DoQuestFunctionDelay("FMQG_PlantationGuards", 3.0);
			pchar.questTemp.FMQG = "fail";
			AddQuestRecord("FMQ_Guadeloupe", "18");
			CloseQuestHeader("FMQ_Guadeloupe");
		break;
		
		// вестовой к ростовщику
		case "cureer":
			DelMapQuestMarkCity("baster");
			LAi_SetImmortal(npchar, false);
			DelLandQuestMark(npchar);
			npchar.lifeday = 0;
			dialog.text = "Salutations, monsieur ! Vous êtes capitaine "+GetFullName(pchar)+", n'est-ce pas ?";
			link.l1 = "Correct. Que puis-je faire pour vous ?";
			link.l1.go = "cureer_1";
		break;
		
		case "cureer_1":
			sld = characterFromId("BasTer_usurer");
			dialog.text = "Monsieur "+GetFullName(pchar)+", le propriétaire de la banque de Basse-Terre vous demande de lui rendre visite dès que possible. Il m'a ordonné de vérifier notre bureau du port chaque jour pour m'assurer que votre arrivée ne soit pas manquée.";
			link.l1 = "Intéressant, et pourquoi serait-il si impatient de me voir ?";
			link.l1.go = "cureer_2";
		break;
		
		case "cureer_2":
			dialog.text = "Monsieur "+GetFullName(sld)+" te dira personnellement pourquoi. J'espère que tu n'ignoreras pas son invitation.";
			link.l1 = "Hm.. Bien. Ces banquiers sont un peuple puissant et ils ne perdent jamais de temps avec les petits poissons. Je vais aller voir cet homme dès que possible.";
			link.l1.go = "cureer_3";
		break;
		
		case "cureer_3":
			dialog.text = "Merci, Capitaine. Adieu!";
			link.l1 = "Adieu.";
			link.l1.go = "cureer_4";
		break;
		
		case "cureer_4":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 10.0);
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("Baster_town", "reload1_back", true);
			LocatorReloadEnterDisable("Baster_town", "reload2_back", true);
			LocatorReloadEnterDisable("Baster_town", "gate_back", true);//закрыть выходы из города
			pchar.questTemp.FMQG = "continue";
			pchar.quest.FMQG_Block.over = "yes";
			pchar.quest.FMQG_Block1.over = "yes";
			AddLandQuestMark(characterFromId("Baster_usurer"), "questmarkmain");
		break;
		
		// Жан Дено
		case "Juan":
			dialog.text = "Argh ! Espèce de vermine ! Impossible que ce soit une rencontre fortuite...";
			link.l1 = "En effet, Jean... oh pardon, je voulais dire Juan. Je t'ai retrouvé. Maintenant, aurais-tu l'amabilité de te déplacer à l'intérieur de ma cale ? Détends-toi un peu, et nous discuterons.";
			link.l1.go = "Juan_1";			
		break;
		
		case "Juan_1":
			DialogExit();
			Lai_SetPlayerType(pchar);
			DeleteAttribute(npchar, "DontRansackCaptain");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 3.0);
			pchar.questTemp.FMQG.Prisoner = GetFullName(npchar);
			pchar.GenQuest.LastQuestPrisonerIdx = SetCharToPrisoner(npchar);
			AddQuestRecord("FMQ_Guadeloupe", "14");
			pchar.questTemp.FMQG = "juan_capture";
			DoQuestCheckDelay("LAi_ReloadBoarding", 3.5);
		break;
		
		case "Juan_2":
			dialog.text = "";
			link.l1 = "J'ai rempli ma part du marché. Maintenant c'est ton tour. Tire et garde à l'esprit les conséquences du mensonge.";
			link.l1.go = "Juan_3";
		break;
		
		case "Juan_3":
			dialog.text = "Vous trouverez Bertrand Pinette à la Barbade, à la plantation principale, pour être plus précis. Il avait l'intention de poursuivre ses opérations là-bas. Le surveillant de la plantation est un ami à lui.";
			link.l1 = "Quel genre d'opérations ?";
			link.l1.go = "Juan_4";
		break;
		
		case "Juan_4":
			dialog.text = "Comme il avait fait à la Guadeloupe. Commerce à moitié légal, contrebande, esclaves. Je pense qu'il vise à faire du commerce d'esclaves et de sucre, pourquoi aurait-il déménagé vers une plantation sinon ?";
			link.l1 = "Je vois. A-t-il des protecteurs parmi les autorités anglaises ?";
			link.l1.go = "Juan_5";
		break;
		
		case "Juan_5":
			dialog.text = "Je suppose. Un personnage curieux, celui-là. Il a toujours des amis partout.";
			link.l1 = "Quelque chose d'autre ?";
			link.l1.go = "Juan_6";
		break;
		
		case "Juan_6":
			dialog.text = "Comme quoi? Rusé et intelligent, il sait toujours des choses, il a toujours un atout dans sa manche. Je n'ai pas eu beaucoup de temps pour en apprendre davantage sur lui.";
			link.l1 = "Compris. Très bien, je dois naviguer jusqu'à Bridgetown. Tu es libre de partir, don Juan. Ne pense même pas à prévenir Pinette. Si je ne le trouve pas là-bas, c'est ton cul qui est en jeu à nouveau.";
			link.l1.go = "Juan_7";
		break;
		
		case "Juan_7":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 10.0);
			npchar.lifeday = 0;
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			pchar.questTemp.FMQG = "headhunter_pinett";
			AddQuestRecord("FMQ_Guadeloupe", "17");
			// Пинетта - в Бриджтаун
			sld = characterFromId("FMQG_pass_1");
			ChangeCharacterAddressGroup(sld, "Bridgetown_Plantation_F2", "goto", "goto1");
			sld.Dialog.currentnode = "citizen_15";
			LAi_SetStayType(sld);
			AddLandQuestMark(sld, "questmarkmain");
			AddMapQuestMarkCity("bridgetown", false);
		break;
		
		case "killer":
			dialog.text = "Je suis désolé, l'ami. Rien de personnel. Tu en sais trop, c'est ça ton problème.";
			link.l1 = "... ";
			link.l1.go = "killer_1";
		break;
		
		case "killer_1":
			DialogExit();
			AddLandQuestMark(characterFromId("Baster_usurer"), "questmarkmain");
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false); // правки релиза								  
			LAi_group_Delete("EnemyFight");
			int n = 2;
			if (MOD_SKILL_ENEMY_RATE > 6) n = 3;
			for (i=1; i<=n; i++)
			{
				sld = characterFromId("FMQG_killer_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "FMQG_KillersDestroy");
			LAi_SetFightMode(pchar, true);
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
