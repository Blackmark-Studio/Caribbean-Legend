// диалог протекторов, солдат и мушкетеров кланов LSC
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Que diable veux-tu ?";
			link.l1 = "Non, ce n'est rien.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
//------------------------------------- фразы гардов нарвалов --------------------------------------------
		// пост нарвалов на проход на Сан-Габриэль
		case "Narval_warning":
			if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
			{
				dialog.text = LinkRandPhrase("Les gars, attention, voilà le cinglé ! Aux armes !","L'ennemi est là ! Aux armes !","Ah, tu es un salaud! Maintenant, nous allons te donner une leçon!");
				link.l1 = "Putain !";
				link.l1.go = "check_parol_fight";
				break;
			}
			ref location = &Locations[FindLocation(pchar.location)];
			if (!CheckAttribute(location, "nrv_parolinfo"))
			{
				if (!CheckAttribute(pchar, "questTemp.LSC.nrv_friend")) 
				{
					dialog.text = "Halte, l'ami. Les territoires des Narvals sont devant, l'entrée est interdite aux étrangers. Vous ne pouvez passer que sur invitation. Connaissez-vous le mot de passe ?";
					link.l1 = "Oui.";
					link.l1.go = "Narval_warning_yes";
					link.l2 = "Non.";
					link.l2.go = "Narval_warning_no";
				}
				else // если друг нарвалам
				{
					dialog.text = "A-ah, "+GetFullName(pchar)+"! Bonjour, ami, on nous a prévenus que vous pouvez vous promener librement ici. Bienvenue !";
					link.l1 = "Merci, l'ami !";
					link.l1.go = "exit";
				}
				location.nrv_parolinfo = "true";
			}
			else
			{
				if (!CheckAttribute(pchar, "questTemp.LSC.nrv_friend")) 
				{
					dialog.text = "J'espère que tu n'as pas oublié le mot de passe...";
					link.l1 = "Ne t'inquiète pas...";
					link.l1.go = "exit";
				}
				else // если друг нарвалам
				{
					dialog.text = TimeGreeting()+", "+pchar.name+"! Comment ça va ?";
					link.l1 = "Bien, merci !";
					link.l1.go = "exit";
				}
			}
			NextDiag.TempNode = "Narval_warning_repeat";
			DeleteAttribute(npchar, "protector.CheckAlways");
		break;
		
		case "Narval_warning_yes":
			dialog.text = "Alors va le dire au dur à cuire là-bas. Ne tente pas de le duper, nos gars avec des mousquets savent quoi faire. Donc, si tu prévois des tours - tu ferais mieux de tourner les talons et partir. Maintenant. Je t'ai prévenu.";
			link.l1 = "D'accord, ami. J'ai compris.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Narval_warning_repeat";
		break;
		
		case "Narval_warning_no":
			dialog.text = "Alors tu n'as rien à faire ici si tu ne comptes pas mettre fin à tes jours, bien sûr. Ou tu plaisantes, hein ? Tu te moques de moi ? En fait, ça m'est égal. Descends, mon travail est d'avertir mais pas d'arrêter. Tu ne reviendras pas si tu ne connais pas un mot de passe.";
			link.l1 = "D'accord, mon pote. J'ai compris.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Narval_warning_repeat";
		break;
		
		case "Narval_warning_repeat":
			if (!CheckAttribute(pchar, "questTemp.LSC.nrv_friend")) 
			{
				dialog.text = "Que veux-tu de plus ? Descends au 'San Gabriel' ou va te perdre !";
				link.l1 = "...";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Je suis désolé, "+pchar.name+", mais je suis de service. Ne me dérange pas, l'ami. Circulez !";
				link.l1 = "...";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Narval_warning_repeat";
		break;
		
		case "Narval_parol":
			if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
			{
				dialog.text = LinkRandPhrase("Les gars, attention, voilà le fou ! Aux armes !","L'ennemi est là ! Aux armes !","Ah, tu es un bâtard ! Maintenant, nous allons te donner une leçon !");
				link.l1 = "Putain !";
				link.l1.go = "check_parol_fight";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LSC.nrv_friend")) 
			{
				dialog.text = "Je suis désolé, "+pchar.name+", mais je suis de service. Ne me dérange pas, l'ami. Circulez !";
				link.l1 = "...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Narval_parol";
				break;
			}
			dialog.text = "Restez où vous êtes ! Vous n'êtes pas des nôtres !";
			link.l1 = "Je suis debout, debout.";	
			link.l1.go = "check_parol";
		break;
		
		case "check_parol":
			dialog.text = "Dis un mot de passe et fais-le clairement et fort.";
			sTotalTemp = sNrvParol;
			if (CheckAttribute(pchar, "questTemp.LSC.NParol_bye"))
			{
				link.l1 = StringFromKey("QuestsUtilite_" + (281 + rand(11)));
				link.l1.go = "check_parol_wrong";
				link.l2 = StringFromKey("QuestsUtilite_" + (293 + rand(11)));
				link.l2.go = "check_parol_wrong";
				link.l3 = StringFromKey("QuestsUtilite_" + (305 + rand(11)));
				link.l3.go = "check_parol_wrong";
				link.l4 = StringFromKey("QuestsUtilite_" + (317 + rand(11)));
				link.l4.go = "check_parol_wrong";
				
				switch (rand(3))
				{
					case 0:
						link.l1 = sTotalTemp;
						link.l1.go = "check_parol_1";
					break;

					case 1:
						link.l2 = sTotalTemp;
						link.l2.go = "check_parol_1";
					break;

					case 2:
						link.l3 = sTotalTemp;
						link.l3.go = "check_parol_1";
					break;

					case 3:
						link.l4 = sTotalTemp;
						link.l4.go = "check_parol_1";
					break;
				}
			}
			else
			{
				link.l1 = "Quel mot de passe ? Laisse-moi passer, ou sinon...";
				link.l1.go = "check_parol_wrong";
			}
		break;
		
		case "check_parol_1":
			dialog.text = "Très bien, vous pouvez continuer.";
			link.l1 = "Merci, l'ami...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Narval_parol_repeat";
			LAi_SetGuardianType(NPChar);
			LAi_group_MoveCharacter(NPChar, "LSC_NARVAL");
			pchar.questTemp.LSC.parol_nrv = "true";
		break;
		
		case "Rcheck_parol_wrong":
			dialog.text = "Hm... Les gars ! Nous avons de la compagnie !";
			link.l1 = "Merde !";
			link.l1.go = "check_parol_fight";
		break;
		
		case "check_parol_fight":
			DialogExit();
			LAi_SetGuardianType(NPChar);
			LAi_group_MoveCharacter(NPChar, "LSC_NARVAL");
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "Narval_parol_repeat":
			if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
			{
				dialog.text = LinkRandPhrase("Les gars, attention, voilà le cinglé ! Aux armes !","L'ennemi est là ! Aux armes !","Ah, vous êtes un bâtard ! Maintenant nous allons vous donner une leçon !");
				link.l1 = "Merde !";
				link.l1.go = "check_parol_fight";
				break;
			}
			dialog.text = "Avancez ! Ne restez pas ici !";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Narval_parol_repeat";
		break;
		
		// у резиденции
		case "Narval_residence":
			if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
			{
				dialog.text = LinkRandPhrase("Les gars, attention, voilà le cinglé ! Aux armes !","L'ennemi est là ! Aux armes !","Ah, tu es un bâtard ! Maintenant, nous allons te donner une leçon !");
				link.l1 = "Merde !";
				link.l1.go = "check_parol_fight";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LSC.nrv_friend")) 
			{
				if (stf(environment.time) >= 6.00 && stf(environment.time) < 21.00) // диалог от времени суток. лесник
			    {
					dialog.text = TimeGreeting()+", "+pchar.name+" ! La porte est ouverte, au cas où tu voudrais voir le patron.";
					link.l1 = "D'accord...";
					link.l1.go = "exit";
					NextDiag.TempNode = "Narval_residence";
					DeleteAttribute(npchar, "protector.CheckAlways");
				}
				else
				{
                    dialog.text = TimeGreeting()+", "+pchar.name+" ! Si vous voulez voir le patron, il dort maintenant. Revenez demain matin.";
					link.l1 = "Très bien...";
					link.l1.go = "exit";
					NextDiag.TempNode = "Narval_residence";
					DeleteAttribute(npchar, "protector.CheckAlways");	
                }					
				break;	
			}
			if (!CheckAttribute(pchar, "questTemp.LSC.nrv_friend") && CheckAttribute(pchar, "questTemp.LSC.rvd_friend")) 
			{
				dialog.text = "Les amis des noirs n'ont rien à faire ici. Ordre direct du patron !";
				if (CheckAttribute(pchar, "questTemp.LSC.Donald_enter"))
				{
					link.l1 = "Il devra me recevoir. Vous avez de sacrés ennuis, les gars. Je suis ici par ordre officiel de l'amiral. Alors ouvrez cette foutue porte !";
					link.l1.go = "negotiations";
				}
				else
				{
				link.l1 = "Je ne peux pas dire que j'ai envie de le voir non plus...";
				link.l1.go = "exit";
				}
				NextDiag.TempNode = "Narval_residence";
				DeleteAttribute(npchar, "protector.CheckAlways");
				break;
			}
			if (stf(environment.time) >= 6.00 && stf(environment.time) < 21.00) // лесник . диалог от времени суток .
			{
			dialog.text = "Tu veux voir le patron ? Hm, eh bien, avance alors.";
			link.l1 = "Danke de m'avoir permis de...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Narval_residence";
			DeleteAttribute(npchar, "protector.CheckAlways");
			}
			else
			{
            dialog.text = "Tu veux voir le patron ? Plus de visites aujourd'hui. Reviens demain matin.";
			link.l1 = "D'accord...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Narval_residence";
			DeleteAttribute(npchar, "protector.CheckAlways");
            }			
		break;
		
		case "Narval_soldier":
			if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
			{
				dialog.text = LinkRandPhrase("Les gars, attention, voilà le fou ! Aux armes !"," L'ennemi est là ! Aux armes ! ","Ah, tu es un bâtard ! Maintenant, nous allons te donner une leçon !");
				link.l1 = "Merde !";
				link.l1.go = "check_parol_fight";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LSC.nrv_friend")) 
			{
				dialog.text = TimeGreeting()+", "+pchar.name+" ! Comment ça va ?";
				link.l1 = "Je vais bien, merci...";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Écoute, l'ami, je n'ai pas envie de parler. Dégage...";
				link.l1 = "D'accord.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Narval_soldier";
		break;
		
		case "negotiations":
			dialog.text = "Eh bien, eh bien... Calmez-vous. Vous auriez dû dire dès le départ que vous veniez de l’amiral. Vous voyez, il y a toutes sortes de gens qui rôdent par ici...";
			link.l1 = "Tu vas enfin me laisser passer ? Merci !";
			link.l1.go = "negotiations_1";
		break;
		
		case "negotiations_1":
			DialogExit();
			NextDiag.CurrentNode = "negotiations_2";
			LocatorReloadEnterDisable("LostShipsCity_town", "reload48", false); // открыть вход к Дональду Гринспи
		break;
		
		case "negotiations_2":
			dialog.text = "Avancez, vous êtes autorisé à...";
			link.l1 = "Oh, vraiment ? Je n'arrive pas à y croire.";
			link.l1.go = "exit";
			NextDiag.TempNode = "negotiations_2";
		break;
		
//------------------------------------- фразы гардов ривадос --------------------------------------------
		// пост ривадос на проход на Фурию и Веласко
		case "Rivados_warning":
			if (CheckAttribute(pchar, "GenQuest.RivadosConflict"))
			{
				dialog.text = LinkRandPhrase("Les gars, attention, voilà le psychopathe agressif ! Aux armes !","L'ennemi est là ! Aux armes !","Ah, tu es un sacré salaud ! Maintenant, nous allons te donner une leçon !");
				link.l1 = "Putain !";
				link.l1.go = "Rcheck_parol_fight";
				break;
			}
			location = &Locations[FindLocation(pchar.location)];
			if (!CheckAttribute(location, "rvd_parolinfo"))
			{
				if (!CheckAttribute(pchar, "questTemp.LSC.rvd_friend")) 
				{
					dialog.text = "Arrêtez ! Les territoires derrière moi appartiennent au clan Rivados, aucun étranger comme vous n'est autorisé à passer sans invitation. Connaissez-vous le mot de passe ?";
					link.l1 = "Oui.";
					link.l1.go = "Rivados_warning_yes";
					link.l2 = "Non.";
					link.l2.go = "Rivados_warning_no";
				}
				else // если друг ривадос
				{
					dialog.text = "Ah, "+GetFullName(pchar)+" ! Heureux de vous voir ! On nous a informés que vous pouvez circuler librement ici. Bienvenue !";
					link.l1 = "Merci, ami!";
					link.l1.go = "exit";
				}
				location.rvd_parolinfo = "true";
			}
			else
			{
				if (!CheckAttribute(pchar, "questTemp.LSC.rvd_friend")) 
				{
					dialog.text = "J'espère que tu n'as pas oublié le mot de passe...";
					link.l1 = "Ne t'inquiète pas...";
					link.l1.go = "exit";
				}
				else // если друг ривадос
				{
					dialog.text = TimeGreeting()+", "+pchar.name+" ! Comment ça va ?";
					link.l1 = "Je vais bien, merci...";
					link.l1.go = "exit";
				}
			}
			NextDiag.TempNode = "Rivados_warning_repeat";
			DeleteAttribute(npchar, "protector.CheckAlways");
		break;
		
		case "Rivados_warning_yes":
			dialog.text = "Tu peux y aller alors. Ce gars te demandera un mot de passe. Tu ferais mieux de partir maintenant si tu as l'intention de nous tromper. Je t'ai prévenu.";
			link.l1 = "Très bien, mon pote. J'ai compris.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Rivados_warning_repeat";
		break;
		
		case "Rivados_warning_no":
			dialog.text = "Ho-ho ! Soit tu es très courageux, soit tu es très stupide si tu viens nous rendre visite sans mot de passe. Ou alors tu plaisantes ? Vas-y alors. Je suis là pour avertir, pas pour arrêter. Prends garde si tu ne connais vraiment pas le mot de passe !";
			link.l1 = "D'accord, mon pote. J'ai compris.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Rivados_warning_repeat";
		break;
		
		case "Rivados_warning_repeat":
			if (!CheckAttribute(pchar, "questTemp.LSC.rvd_friend")) 
			{
				dialog.text = "Eh bien, que veux-tu ? Avance ou dégage !";
				link.l1 = "... ";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Je suis désolé, "+pchar.name+", mais je suis de service. Eddie ne veut pas que je parle trop.";
				link.l1 = "... ";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Rivados_warning_repeat";
			DeleteAttribute(npchar, "protector.CheckAlways");
		break;
		
		case "Rivados_parol":
			if (CheckAttribute(pchar, "GenQuest.RivadosConflict"))
			{
				dialog.text = LinkRandPhrase("Les gars, attention, voilà le fou agressif ! Aux armes !","L'ennemi est là ! Aux armes !","Ah, tu es un salaud malade ! Maintenant, nous allons te donner une leçon !");
				link.l1 = "Putain !";
				link.l1.go = "Rcheck_parol_fight";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LSC.rvd_friend")) 
			{
				dialog.text = "Je suis désolé, "+pchar.name+", mais je suis de service. Eddie ne veut pas que je parle trop.";
				link.l1 = "... ";
				link.l1.go = "exit";
				NextDiag.TempNode = "Rivados_parol";
				DeleteAttribute(npchar, "protector.CheckAlways");
				break;
			}
			dialog.text = "Arrêtez-vous là où vous êtes ! Vous n'êtes pas des Rivados !";
			link.l1 = "Je veux passer.";	
			link.l1.go = "Rcheck_parol";
		break;
		
		case "Rcheck_parol":
			dialog.text = "Alors, dis un mot de passe et fais-le haut et fort.";
			sTotalTemp = sRvdParol;
			if (CheckAttribute(pchar, "questTemp.LSC.RParol_bye"))
			{
				link.l1 = StringFromKey("QuestsUtilite_" + (281 + rand(11)));
				link.l1.go = "Rcheck_parol_wrong";

				link.l2 = StringFromKey("QuestsUtilite_" + (293 + rand(11)));
				link.l2.go = "Rcheck_parol_wrong";

				link.l3 = StringFromKey("QuestsUtilite_" + (305 + rand(11)));
				link.l3.go = "Rcheck_parol_wrong";

				link.l4 = StringFromKey("QuestsUtilite_" + (317 + rand(11)));
				link.l4.go = "Rcheck_parol_wrong";
				
				switch (rand(3))
				{
					case 0:
						link.l1 = sTotalTemp;
						link.l1.go = "Rcheck_parol_1";
					break;

					case 1:
						link.l2 = sTotalTemp;
						link.l2.go = "Rcheck_parol_1";
					break;

					case 2:
						link.l3 = sTotalTemp;
						link.l3.go = "Rcheck_parol_1";
					break;

					case 3:
						link.l4 = sTotalTemp;
						link.l4.go = "Rcheck_parol_1";
					break;
				}
			}
			else
			{
				link.l1 = "Quel mot de passe ? Laisse-moi passer, ou sinon...";
				link.l1.go = "Rcheck_parol_wrong";
			}
		break;
		
		case "Rcheck_parol_1":
			dialog.text = "D'accord. Passez votre chemin.";
			link.l1 = "Merci, l'ami...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Rivados_parol_repeat";
			LAi_SetGuardianType(NPChar);
			LAi_group_MoveCharacter(NPChar, "LSC_RIVADOS");
			pchar.questTemp.LSC.parol_rvd = "true";
		break;
		
		case "Rcheck_parol_wrong":
			dialog.text = "Ha-ha! Nous avons un invité ici ! Montrons-lui qui nous sommes !";
			link.l1 = "Merde !";
			link.l1.go = "Rcheck_parol_fight";
		break;
		
		case "Rcheck_parol_fight":
			DialogExit();
			LAi_SetGuardianType(NPChar);
			LAi_group_MoveCharacter(NPChar, "LSC_RIVADOS");
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "Rivados_parol_repeat":
			if (CheckAttribute(pchar, "GenQuest.RivadosConflict"))
			{
				dialog.text = LinkRandPhrase("Les gars, attention, il y a ce psychopathe agressif ! Aux armes !","L'ennemi est là ! Aux armes !","Ah, tu es un salaud malade! Maintenant, nous allons te donner une bonne leçon!");
				link.l1 = "Merde !";
				link.l1.go = "Rcheck_parol_fight";
				break;
			}
			dialog.text = "Ne reste pas là, circule!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Rivados_parol_repeat";
		break;
		
		// у резиденции
		case "Rivados_residence":
			if (CheckAttribute(pchar, "GenQuest.RivadosConflict"))
			{
				dialog.text = LinkRandPhrase("Les gars, attention, voilà le psychopathe agressif ! Aux armes !","L'ennemi est là ! Aux armes !","Ah, tu es un salopard malade ! Maintenant, nous allons te donner une leçon !");
				link.l1 = "Putain !";
				link.l1.go = "Rcheck_parol_fight";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LSC.rvd_friend")) 
			{
				if (stf(environment.time) >= 6.00 && stf(environment.time) < 21.00) // лесник . диалог от времени суток .
				{
				dialog.text = TimeGreeting()+", "+pchar.name+" ! La porte est ouverte, au cas où tu voudrais voir Eddie et Chimiset. Ils seront heureux de te voir.";
				link.l1 = "D'accord...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Rivados_residence";
				DeleteAttribute(npchar, "protector.CheckAlways");
				}
				else // лесник - режим пропуска 
				{	
				dialog.text = TimeGreeting()+", "+pchar.name+" ! Au cas où tu voudrais voir Eddie et Chimiset, ils se reposent déjà. Reviens le matin, ils seront heureux de te voir.";
				link.l1 = "Bien...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Rivados_residence";
				DeleteAttribute(npchar, "protector.CheckAlways");
				}
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LSC.nrv_friend") && !CheckAttribute(pchar, "questTemp.LSC.rvd_friend")) 
			{
				dialog.text = "Il n'y a rien à faire pour les amis des Narvals dans la cabine d'Eddie ! C'est son ordre direct. Fichez le camp !";
				link.l1 = "Je ne voulais pas le voir non plus...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Rivados_residence";
				DeleteAttribute(npchar, "protector.CheckAlways");
				break;
			}
			if (GetCharacterIndex("Chimiset") == -1) // Чимисет убит
			{
				dialog.text = "Il n'y a rien à faire dans la cabine d'Eddie pour vous ! C'est un ordre direct de sa part. Déguerpissez !";
				link.l1 = "Je ne voulais pas le voir non plus...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Rivados_residence";
				DeleteAttribute(npchar, "protector.CheckAlways");
				break;
			}
			if (stf(environment.time) >= 6.00 && stf(environment.time) < 21.00) // лесник . диалог от времени суток .
			{
			dialog.text = "Tu veux voir Eddie ? Très bien, avance, je suppose qu'il te consacrera une minute.";
			link.l1 = "D'accord pour permettre de...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Rivados_residence";
			DeleteAttribute(npchar, "protector.CheckAlways");
			}
			else // лесник режим пропуска.
			{
            dialog.text = "Veux-tu voir Eddie ? Pas de visites aujourd'hui, reviens demain matin et il te consacrera une minute.";
			link.l1 = "D'accord...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Rivados_residence";
			DeleteAttribute(npchar, "protector.CheckAlways");
            }			
		break;
		
		case "Rivados_soldier":
			if (CheckAttribute(pchar, "GenQuest.RivadosConflict"))
			{
				dialog.text = LinkRandPhrase("Les gars, attention, voilà le psychopathe agressif ! Aux armes !","L'ennemi est là ! Aux armes !","Ah, tu es un salaud malade ! Maintenant, nous allons te donner une leçon !");
				link.l1 = "Putain !";
				link.l1.go = "Rcheck_parol_fight";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LSC.rvd_friend")) 
			{
				dialog.text = TimeGreeting()+", "+pchar.name+" ! Comment ça va ? ";
				link.l1 = "Je vais bien, merci...";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Écoute, l'ami, je n'ai pas envie de parler. File d'ici...";
				link.l1 = "D'accord.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Rivados_soldier";
		break;
//------------------------------------- фразы гардов пиратов --------------------------------------------	
		// у склада
		case "Shark_storage":
			if (CheckAttribute(pchar, "GenQuest.SharkConflict"))
			{
				dialog.text = LinkRandPhrase("Les gars, attention, voilà le cinglé armé ! Aux armes !","L'ennemi est là ! Aux armes !","Ah, tu es un bâtard ! Maintenant, nous allons te botter le derrière !");
				link.l1 = "Diable !";
				link.l1.go = "shark_guard_fight";
				break;
			}
			dialog.text = "Halte ! C'est une zone interdite !";
			link.l1 = "Très bien, comme tu dis...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Shark_storage";
		break;
		
		// у резиденции
		case "Shark_residence":
			if (CheckAttribute(pchar, "GenQuest.SharkConflict"))
			{
				dialog.text = LinkRandPhrase("Les gars, attention, voilà le psychopathe armé ! Aux armes !","L'ennemi est ici ! Aux armes !","Ah, tu es un salaud ! Maintenant, nous allons te botter le cul !");
				link.l1 = "Nom d'un chien!";
				link.l1.go = "shark_guard_fight";
				break;
			}
			if (stf(environment.time) >= 6.00 && stf(environment.time) < 21.00)
			{
				if (pchar.questTemp.LSC == "begin" || pchar.questTemp.LSC == "mary") // тока прибыл
				{
					dialog.text = "Halte ! Tu n'es pas des nôtres... Est-ce que le Requin t'attend ou te promènes-tu sans but ?";
					link.l1 = "Requin ? Steve Dodson ?";
					link.l1.go = "first_talk_day";
				}
				else
				{
				dialog.text = "L'amiral vous acceptera. Avancez.";
				link.l1 = "Merci !";
				link.l1.go = "exit";
			}
			}
			else
			{
				if (pchar.questTemp.LSC == "begin" || pchar.questTemp.LSC == "mary") // тока прибыл
				{
					dialog.text = "Où te précipites-tu ? C'est la nuit, ne vois-tu pas ! Ou penses-tu vraiment que l'amiral se réveillera pour te saluer en personne ? Viens le matin.";
					link.l1 = "Comme vous dites. Et où puis-je me reposer ?";
					link.l1.go = "first_talk_night";
				}
			else
			{
				dialog.text = "Il est tard, l'amiral ne reçoit pas maintenant. Revenez demain.";
				link.l1 = "D'accord...";
				link.l1.go = "exit";
			}
			}
			NextDiag.TempNode = "Shark_residence";
		break;
		
		case "Shark_soldier":
			if (CheckAttribute(pchar, "GenQuest.SharkConflict"))
			{
				dialog.text = LinkRandPhrase("Les gars, attention, c'est le psychopathe armé ! Aux armes !","L'ennemi est là ! Aux armes !","Ah, tu es un salaud ! Maintenant, nous allons te botter le cul !");
				link.l1 = "Nom d'un chien !";
				link.l1.go = "shark_guard_fight";
				break;
			}
			dialog.text = "L'amiral ne sera pas content s'il me voit en train de parler. Circulez.";
			link.l1 = "D'accord...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Shark_soldier";
		break;
		
		case "first_talk_night":
			dialog.text = NPCStringReactionRepeat("Es-tu ivre ? Fais demi-tour et traverse le pont, passe devant deux navires, puis tu trouveras un autre pont qui te mènera à la taverne. Dors là-bas.","Essaye-tu de m'énerver ? Je viens de te dire quoi faire. Déguerpis !","Va dormir, face d'ivrogne...","Va-t'en !!","bloc",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Merci, monsieur. Vous pourriez être plus poli, en fait...","Je suis désolé, j'ai oublié...","Je ne suis pas ivre !","Quoi?!",npchar,Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);
		break;
		
		case "first_talk_day":
			dialog.text = "Ne fais pas les yeux ronds, garçon. Tout le monde sait que Steve Requin est notre amiral. As-tu une affaire avec lui ?";
			link.l1 = "Oui, bon sang ! J'ai des affaires avec lui et c'est urgent.";
			link.l1.go = "first_talk_day_1";
		break;
		
		case "first_talk_day_1":
			dialog.text = "Et quel genre d'affaires ?";
			link.l1 = "Je n'en parlerai qu'en privé avec le Requin. Je travaille pour Jan Svenson, le connaissez-vous ?";
			link.l1.go = "first_talk_day_2";
		break;
		
		case "first_talk_day_2":
			dialog.text = "Diable de forêt ? Ha ! La moitié du continent connaît cet homme. Écoute, gamin, ne sois pas têtu. Soit tu t'expliques, soit tu déguerpis avant que je ne me mette en colère. Le Requin a dit de l'épargner des gens inutiles et je ne fais que suivre ses ordres.";
			link.l1 = "D'accord. Tenez, regardez cette lettre, elle est écrite par le Diable des Forêts à Requin.";
			link.l1.go = "first_talk_day_3";
		break;
		
		case "first_talk_day_3":
			PlaySound("interface\important_item.wav");
			dialog.text = "(regardant)... Très bien. Je suppose que Steve trouvera cela intéressant. Passez votre chemin.";
			link.l1 = "Oh, vraiment ? Rends-moi la lettre si ça ne te dérange pas trop, s'il te plaît.";
			if (pchar.questTemp.LSC == "mary") link.l1.go = "first_talk_day_5";
			else link.l1.go = "first_talk_day_4";
		break;
		
		case "first_talk_day_4":
			PlaySound("interface\important_item.wav");
			npchar.dialog.currentnode = "First time";
			DialogExit();
			LSC_OpenSanAvgustinDoors(); // открываем Сан-Августин
			LocatorReloadEnterDisable("LostShipsCity_town", "reload2", true); //закрываем кладовку со стороны моря
			pchar.quest.LSC_entry_pantry.over = "yes"; //снять прерывание на арест
			pchar.quest.LSC_findMary.over = "yes"; //снять прерывание на Мэри
			pchar.questTemp.LSC = "entrance"; //меняем флаг
			sld = characterFromId("Dodson");
			sld.dialog.currentnode = "entrance";
			// закрываем вход к Мэри
			LocatorReloadEnterDisable("LostShipsCity_town", "reload60", true);
			LocatorReloadEnterDisable("LostShipsCity_town", "reload61", true);
		break;
		
		case "first_talk_day_5":
			PlaySound("interface\important_item.wav");
			npchar.dialog.currentnode = "First time";
			DialogExit();
			LSC_OpenSanAvgustinDoors(); // открываем Сан-Августин
			sld = characterFromId("Dodson");
			sld.dialog.currentnode = "entrance";
		break;
		
		case "shark_guard_fight":
			DialogExit();
			LAi_SetGuardianType(NPChar);
			LAi_group_MoveCharacter(NPChar, "LSC_SHARK");
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}
