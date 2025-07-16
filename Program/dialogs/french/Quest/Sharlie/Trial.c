// диалоги НПС по квесту 'Карибские нравы'
void ProcessDialogEvent()
{
	ref NPChar, sld, rColony;
	aref Link, NextDiag;
	int iTemp;
	bool bOk;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Que veux-tu ?";
			link.l1 = "Non, rien.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// Жерар Лекруа
		case "lecrua":
			pchar.quest.Trial_LineOver.over = "yes"; //снять таймер
			dialog.text = "Bon après-midi. Vous devez être "+GetFullName(pchar)+"?";
			link.l1 = "Vous avez raison, Monsieur LeCroix. Capitaine "+GetFullName(pchar)+"à votre service. Fadey le Moscovite vous a recommandé à moi...";
			link.l1.go = "lecrua_1";
			DelLandQuestMark(npchar);
		break;
		
		case "lecrua_1":
			iTemp = FindColony("Baster");
			rColony = GetColonyByIndex(iTemp);
			bOk = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
			dialog.text = "Oui, oui. Mon cher ami Fadey vous a décrit, vous et votre situation, en détail. Je savais que c'était vous dès que je vous ai vu à l'entrée. Dites-moi capitaine, quel type de navire avez-vous ?";
			if(sti(pchar.ship.type) == SHIP_NOTUSED || !bOk)
			{
				link.l1 = "Ah...Je n'ai pas de navire pour le moment, monsieur...";
				link.l1.go = "lecrua_noship";
			}
			else
			{
				link.l1 = "J'ai un "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(RealShips[sti(pchar.ship.type)].basetype),"Nom")))+", son nom est "+pchar.ship.name+".";
				if (6-sti(RealShips[sti(pchar.ship.type)].Class) < 0) link.l1.go = "lecrua_badship";
				else link.l1.go = "lecrua_2";
			}
		break;
		
		case "lecrua_noship":
			dialog.text = "Ha ! Eh bien, quel genre de capitaine es-tu donc si tu n'as pas de navire ? Je suis désolé, monsieur, mais dans ce cas, je n'ai pas de travail à vous offrir. Tout de bon, transmettez mes salutations à Fadey !";
			link.l1 = "Hm...";
			link.l1.go = "lecrua_exit";
			sTotalTemp = "I don't have a ship at the moment";
		break;
		
		case "lecrua_badship":
			dialog.text = "Eh bien, cela ne va tout simplement pas. Ce n'est pas un navire, monsieur, c'est un bateau ! Hélas, monsieur, vous ne convenez pas au rôle. Passez le bonjour à Fadey de ma part, bonne journée !";
			link.l1 = "Hm...";
			link.l1.go = "lecrua_exit";
			sTotalTemp = "My ship wasn't big enough for him";
		break;
		
		case "lecrua_exit":
			DialogExit();
			npchar.lifeday = 0;
			NextDiag.CurrentNode = "lecrua_repeat";
			AddQuestRecord("Trial", "3");
			AddQuestUserData("Trial", "sText", sTotalTemp);
			CloseQuestHeader("Trial");
			DeleteAttribute(pchar, "questTemp.Trial");
			pchar.questTemp.TrialEnd = true;
		break;
		
		case "lecrua_repeat":
			dialog.text = "Vous et moi avons déjà discuté de tout, monsieur. N'est-ce pas ?";
			link.l1 = "Oui, Monsieur LeCroix... Je suis en route.";
			link.l1.go = "exit";
			NextDiag.TempNode = "lecrua_repeat";
		break;
		
		case "lecrua_2":
			dialog.text = "Excellent. Dans ce cas, vous êtes un bon parti pour moi. Êtes-vous prêt à prendre la mer immédiatement?";
			link.l1 = "Oui, monsieur, je suis prêt. Que dois-je faire ?";
			link.l1.go = "lecrua_3";
		break;
		
		case "lecrua_3":
			sld = characterFromId("BasTer_trader");
			dialog.text = "Vous devez livrer un petit lot de poudre à canon et de bombes à Port-au-Prince, sur l'Hispaniola française. Le commandant l'attend depuis un moment, alors ne perdez pas de temps, il vous reste environ dix jours\nRespecté "+GetFullName(sld)+" s'occupera de le livrer et de le charger sur votre navire. Le commandant vous paiera cinq mille pièces de huit pour ce travail.";
			link.l1 = "Et c'est tout le travail ?";
			link.l1.go = "lecrua_4";
		break;
		
		case "lecrua_4":
			dialog.text = "Oh, en aucun cas, monsieur. Le commandant vous expliquera le véritable travail lorsque vous apporterez les munitions. Ce fret n'est qu'un petit apéritif du travail qui vous attend. Mais ne craignez rien, si vous faites bien le travail, vous gagnerez beaucoup d'argent.";
			link.l1 = "Vous avez toute mon attention, monsieur. Mon navire est prêt à embarquer la cargaison.";
			link.l1.go = "lecrua_5";
		break;
		
		case "lecrua_5":
			dialog.text = "Ne perdons pas de temps alors, capitaine ! Rejoignez votre navire et préparez-vous à appareiller.";
			link.l1 = "J'y vais !";
			link.l1.go = "lecrua_6";
		break;
		
		case "lecrua_6":
			DialogExit();
			NextDiag.CurrentNode = "lecrua_repeat";
			AddQuestRecord("Trial", "4");
			pchar.questTemp.Trial = "fraht";
			AddMapQuestMarkCity("PortPax", false);
			// belamour legendary edition халява по чекбоксу
			if(!bImCasual) SetFunctionTimerCondition("Trial_FrahtFail", 0, 0, 17, false); // таймер
			else NewGameTip("Exploration mode: timer is disabled.");
			SetFunctionTimerCondition("Trial_LecruaHide", 0, 0, 1, false); // таймер
			// груз
			SetCharacterGoods(pchar, GOOD_BOMBS, GetCargoGoods(pchar, GOOD_BOMBS)+2500);
			SetCharacterGoods(pchar, GOOD_POWDER, GetCargoGoods(pchar, GOOD_POWDER)+2500);
			// Sinistra Пасхалка с Диего
			pchar.quest.VsD_DiegoNachalo.win_condition.l1 = "Ship_location";
			pchar.quest.VsD_DiegoNachalo.win_condition.l1.location = "PortPax_town";
			PChar.quest.VsD_DiegoNachalo.win_condition = "VsD_DiegoNachalo";
			
			// отключить все враждебные энкаунтеры на глобальной карте
			pchar.worldmapencountersoff = "1";
			SetFunctionTimerCondition("DelNavigatorNoShow", 0, 0, 180, false);
			pchar.systeminfo.tutorial.navigatorTrial = true;
		break;
		
		// Флориан Шоке
		case "florian_deck":
			if(!bImCasual) pchar.quest.Trial_CannonFail.over = "yes"; // belamour legendary edition снять таймер
			DelMapQuestMarkShore("shore47");
			DelLandQuestMark(npchar);
			sld = CharacterFromID("PortRoyal_shipyarder");
			if(CheckAttribute(sld, "TrialDelQuestMark"))
			{
				DeleteAttribute(sld, "TrialDelQuestMark");
				DelLandQuestMark(sld);
				DelMapQuestMarkCity("PortRoyal");
			}
			dialog.text = "Que puis-je faire pour vous, monsieur ?";
			link.l1 = "Bon après-midi, capitaine. Vous êtes Florian Shoke, je présume ?";
			link.l1.go = "florian_deck_1";
		break;
		
		case "florian_deck_1":
			dialog.text = "Je le suis. Et vous êtes le navire postal de Port-au-Prince, si je ne me trompe pas ?";
			link.l1 = "Oui, j'ai quinze canons pour vous. La date limite était serrée, j'ai à peine réussi...";
			link.l1.go = "florian_deck_2";
		break;
		
		case "florian_deck_2":
			if (GetSquadronGoods(pchar, GOOD_CANNON_24) < 15)
			{
				dialog.text = "Hm. Étrange sens de l'humour que vous avez, monsieur ! Pour une raison quelconque, je ne vois pas quinze canons être déchargés de votre navire...";
				link.l1 = "Eh bien, voyez-vous, nous avons eu une fuite et avons dû jeter une partie de la cargaison par-dessus bord...";
				link.l1.go = "florian_deck_fail";
			}
			else
			{
				dialog.text = "Heureux de vous voir, capitaine ?..";
				link.l1 = ""+GetFullName(pchar)+". Capitaine "+GetFullName(pchar)+".";
				link.l1.go = "florian_deck_3";
			}
		break;
		
		case "florian_deck_3":
			dialog.text = "Enchanté de faire votre connaissance. Ne perdons pas de temps et montons ces canons à bord. Ça ne va pas être facile, alors j'aurai besoin de vos hommes pour m'aider.";
			link.l1 = "On s'en sortira. Toi là-bas, mets en place le palan sur la vergue !";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Trial_TakeCannons");
		break;
		
		case "florian_deck_fail":
			dialog.text = "Espèce d'idiot ! Si tu ne peux même pas gérer cette tâche simple, tu es sûr de couler lors de la prochaine tempête. Retourne à ton navire, capitaine, et fais quelque chose que tu sais mieux faire comme livrer des fleurs aux dames nobles. Mieux encore, retourne en Europe et laisse le Nouveau Monde aux vrais hommes. Bonne journée, monsieur !";
			link.l1 = "Mais...";
			link.l1.go = "florian_deck_fail_1";
		break;
		
		case "florian_deck_fail_1":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.DontDeskTalk = true; 
			RemoveCharacterGoods(pchar, GOOD_CANNON_24, GetCargoGoods(pchar, GOOD_CANNON_24));
			SetFunctionTimerCondition("Trial_RemoveFlorian", 0, 0, 1, false);
			sld = characterFromId("Lecrua");
			sld.lifeday = 0;
			AddQuestRecord("Trial", "10");
			CloseQuestHeader("Trial");
			DeleteAttribute(pchar, "questTemp.Trial");
			pchar.questTemp.TrialEnd = true;
			ChangeCharacterNationReputation(pchar, FRANCE, -3);
		break;
		
		case "florian_deck_4":
			dialog.text = "Ouf, ce fut un travail assoiffant ! Je vous remercie pour le service, capitaine ! Prenez votre récompense, deux cents doublons.";
			link.l1 = "Merci !";
			link.l1.go = "florian_deck_5";
		break;
		
		case "florian_deck_5":
			TakeNItems(pchar, "gold_dublon", 200);
			Log_Info("You've received 200 doubloons.");
			PlaySound("interface\important_item.wav");
			dialog.text = "Mais ce n'est pas tout, capitaine. Voudriez-vous gagner encore deux cent cinquante doubles escudos d'or ?";
			link.l1 = "Ça semble prometteur, mais ça dépend de ce que vous allez me demander de faire pour cela, monsieur.";
			link.l1.go = "florian_deck_6";
		break;
		
		case "florian_deck_6":
			dialog.text = "Je ne vais pas te mentir, c'est dangereux. Comme tu le sais peut-être déjà, je suis en embuscade pour un lourd galion espagnol avec une cargaison précieuse. Le navire a été mis en cale sèche pour réparation. Selon mes sources, il devait lever l'ancre hier, mais cela ne s'est pas produit.\nDe plus, mon agent à Portobello n'est pas arrivé au point de rendez-vous pour livrer les mises à jour que j'attendais. Je soupçonne que les Espagnols l'ont arrêté. Je te paierai pour te faufiler à Portobello et découvrir deux choses : pourquoi le galion est toujours là et ce qui est arrivé à mon agent. Es-tu partant ?";
			link.l1 = "J'ai bien peur de ne pas avoir la formation adéquate pour une telle opération. Je suis un gentilhomme, pas un espion. Je pourrais bien me retrouver dans le pétrin moi-même et je ne pourrai pas vous aider.";
			link.l1.go = "florian_deck_bye";
			link.l2 = "Ça semble dangereux, mais lucratif. Je vais prendre le risque. Quel est le nom de votre homme et comment s'appelle le galion ?";
			link.l2.go = "florian_deck_7";
		break;
		
		case "florian_deck_bye":
			dialog.text = "Eh bien, ne te crois-tu pas supérieur ? Je te comprends. Adieu alors, capitaine, merci encore pour ton aide !";
			link.l1 = "Tous mes voeux, Monsieur Shoke.";
			link.l1.go = "florian_deck_bye_1";
		break;
		
		case "florian_deck_bye_1":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.DontDeskTalk = true; 
			SetFunctionTimerCondition("Trial_RemoveFlorian", 0, 0, 1, false);
			sld = characterFromId("Lecrua");
			sld.lifeday = 0;
			AddQuestRecord("Trial", "11");
			CloseQuestHeader("Trial");
			DeleteAttribute(pchar, "questTemp.Trial");
			pchar.questTemp.TrialEnd = true;
		break;
		
		case "florian_deck_7":
			dialog.text = "Oui, écoutez bien alors. Mon homme s'appelle Sylvan Laforet, mais à Portobello, il se fait appeler Jaime Silicio, un marchand. Le galion s'appelle 'Alacantara'. Je vous conseille de passer par les portes de la ville la nuit, à travers la jungle. Les gardes de Portobello sont très méfiants de nos jours, sans parler que la disparition de Sylvan ne présage rien de bon pour sa survie. Vous avez deux jours avant que je doive partir d'ici avant que les patrouilles espagnoles ne nous trouvent. Bonne chance, monsieur !";
			link.l1 = "À bientôt, Monsieur Shoke...";
			link.l1.go = "florian_deck_8";
		break;
		
		case "florian_deck_8":
			bQuestDisableMapEnter = true;//закрыть карту
			pchar.GenQuest.MapClosedNoBattle = true; // доступно ожидание и sailto
			DialogExit();
			npchar.DeckDialogNode = "florian_deck_repeat";
			NextDiag.CurrentNode = "florian_deck_repeat";
			pchar.questTemp.Trial = "spy";
			AddQuestRecord("Trial", "12");
			// belamour legendary edition -->
			if(!bImCasual) 
			{
				pchar.quest.trial_spy_over.win_condition.l1 = "Timer";
				pchar.quest.trial_spy_over.win_condition.l1.date.hour  = sti(GetTime() + 2);
				pchar.quest.trial_spy_over.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 2);
				pchar.quest.trial_spy_over.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 2);
				pchar.quest.trial_spy_over.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 2);
				pchar.quest.trial_spy_over.function = "Trial_SpyTimeOver";
			}
			else NewGameTip("Exploration mode: timer is disabled.");
			// <-- legendary edition
			//Log_Info("You have received amulet 'Gypsy's fan'");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "obereg_4");
			pchar.quest.NewGameTip5.win_condition.l1 = "location";
			pchar.quest.NewGameTip5.win_condition.l1.location = "PortoBello_town";
			pchar.quest.NewGameTip5.function = "ShowNewGameTip";
			pchar.quest.NewGameTip5.text = "Guards are less suspicious when you walk at slow pace!";
			
			pchar.quest.Trial_CreatHabitue.win_condition.l1 = "location";
			pchar.quest.Trial_CreatHabitue.win_condition.l1.location = "PortoBello_tavern";
			pchar.quest.Trial_CreatHabitue.function = "Trial_CreatHabitue";
			
			pchar.quest.Tutorial_stealth.win_condition.l1 = "location";
			pchar.quest.Tutorial_stealth.win_condition.l1.location = "PortoBello_ExitTown";
			pchar.quest.Tutorial_stealth.function = "Tutorial_stealth";
			
			QuestPointerToLoc("shore47", "reload", "reload1_back");
			QuestPointerToLoc("PortoBello_Jungle_02", "reload", "reload1_back");
			QuestPointerToLoc("PortoBello_Jungle_01", "reload", "reload3_back");
			QuestPointerToLoc("PortoBello_ExitTown", "reload", "reload4");
			QuestPointerToLoc("PortoBello_Town", "reload", "reload41_back");
			QuestPointerToLoc("PortoBello_Town", "reload", "reload4_back");
		break;
		
		case "florian_deck_repeat":
			dialog.text = "Nous avons discuté de tout, capitaine, n'est-ce pas ?";
			link.l1 = "Oui. Je suis en route.";
			link.l1.go = "exit";
			NextDiag.TempNode = "florian_deck_repeat";
		break;
		
		case "florian_failspy":
			pchar.quest.trial_spy_over.over = "yes"; //снять прерывание
			dialog.text = "Comment avancent les choses, capitaine ? Qu'avez-vous réussi à découvrir ?";
			link.l1 = "Les choses vont mal, Monsieur Shoke. Je ne suis pas vraiment un espion, ils m'ont découvert très rapidement. J'ai dû fuir la ville après avoir combattu quelques gardes. La seule chose que j'ai réussi à découvrir, c'est que votre homme, Sylvain Laforet, a été arrêté et est détenu en prison.";
			link.l1.go = "florian_failspy_1";
		break;
		
		case "florian_failspy_1":
			dialog.text = "Bon sang ! Ce n'est pas bon... As-tu découvert quelque chose à propos du galion ?";
			link.l1 = "Non, je ne l'ai pas fait.";
			link.l1.go = "florian_failspy_2";
		break;
		
		case "florian_failspy_2":
			dialog.text = "Merde. J'ai vraiment besoin d'informations à ce sujet. Mais ce butin est trop gras pour être abandonné ! Quoi qu'il en soit, je vais essayer d'envoyer un autre éclaireur là-bas... Capitaine, je vous demande de ne pas me quitter pour l'instant. J'aurai peut-être besoin de votre aide. Voulez-vous attendre jusqu'à demain pendant que je cherche des informations sur l'Alacantara ?";
			link.l1 = "Bien sûr, j'attendrai ! J'aimerais rattraper cet échec.";
			link.l1.go = "florian_9";
			link.l2 = "Je ne pense pas. Apparemment, je suis trop mauvais à ces jeux. Je rentre chez moi.";
			link.l2.go = "florian_failspy_3";
		break;
		
		case "florian_failspy_3":
			dialog.text = "Eh bien, c'est ton choix. Bonne chance, capitaine.";
			link.l1 = "Adieu, Monsieur Shoke.";
			link.l1.go = "florian_failspy_4";
		break;
		
		case "florian_failspy_4":
			DialogExit();
			bQuestDisableMapEnter = false;
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			LAi_CharacterDisableDialog(npchar);
			npchar.DontDeskTalk = true; 
			SetFunctionTimerCondition("Trial_RemoveFlorian", 0, 0, 1, false);
			sld = characterFromId("Lecrua");
			sld.lifeday = 0;
			CloseQuestHeader("Trial");
			DeleteAttribute(pchar, "questTemp.Trial");
			pchar.questTemp.TrialEnd = true;
		break;
		
		case "florian_failspy_5":
			pchar.quest.trial_spy_over.over = "yes"; //снять прерывание
			dialog.text = "Comment vont les choses, capitaine ? Qu'avez-vous réussi à découvrir ?";
			link.l1 = "Les choses vont mal, Monsieur Shoke. Je ne suis pas vraiment un espion, ils m'ont découvert très rapidement. La seule chose que j'ai réussi à découvrir, c'est que votre homme, Sylvan Laforet, a été arrêté et est détenu quelque part.";
			link.l1.go = "florian_failspy_1";
		break;
		
		case "florian_9":
			dialog.text = "Alors, dirigez-vous vers votre navire, capitaine. Demain, à peu près à la même heure, ou un peu plus tard, vous devrez me rendre visite. Peut-être qu'à ce moment-là, j'aurai découvert quelque chose. Ne mettez pas pied à terre, attendez-moi sur votre navire !";
			link.l1 = "D'accord. Je le ferai.";
			link.l1.go = "florian_10";
		break;
		
		case "florian_10":
			dialog.text = "Et capitaine, prenez cette bourse. Vos efforts n'ont pas été complètement vains après tout. Au moins, nous savons ce qui est arrivé au pauvre vieux Sylvan...";
			link.l1 = "... ";
			link.l1.go = "florian_11";
		break;
		
		case "florian_11":
			DialogExit();
			Island_SetReloadEnableGlobal("Portobello", false);//закрыть остров	
			npchar.DeckDialogNode = "florian_deck_wait";
			NextDiag.CurrentNode = "florian_deck_wait";
			pchar.questTemp.Trial = "spy_wait";
			pchar.quest.Trial_spyfail_wait.win_condition.l1 = "Timer";
			pchar.quest.Trial_spyfail_wait.win_condition.l1.date.hour  = sti(GetTime()+rand(12));
			pchar.quest.Trial_spyfail_wait.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Trial_spyfail_wait.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Trial_spyfail_wait.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Trial_spyfail_wait.function = "Trial_Spyfail_NextStage";
			TakeNItems(pchar, "purse2", 1);
			Log_Info("You've received a purse of doubloons");
		break;
		
		case "florian_deck_wait":
			dialog.text = "Capitaine, je n'ai pas de nouvelles pour le moment. Nous attendons toujours...";
			link.l1 = "D'accord...";
			link.l1.go = "exit";
			NextDiag.TempNode = "florian_deck_wait";
		break;
		
		case "florian_12":
			pchar.quest.trial_spy_over.over = "yes"; //снять прерывание
			dialog.text = "Comment avancent les choses, capitaine ? Qu'avez-vous réussi à découvrir ?";
			link.l1 = "C'est fait. Votre homme, Sylvan Laforet, a été arrêté et est détenu en prison. C'en est fini pour lui.";
			link.l1.go = "florian_13";
			DelLandQuestMark(npchar);
			QuestPointerDelLoc("PortoBello_Town", "reload", "gate_back");
			QuestPointerDelLoc("PortoBello_ExitTown", "reload", "reload1_back");
			QuestPointerDelLoc("PortoBello_Jungle_01", "reload", "reload2_back");
			QuestPointerDelLoc("PortoBello_Jungle_02", "reload", "reload3_back");
			QuestPointerDelLoc("shore47", "reload", "boat");
		break;
		
		case "florian_13":
			dialog.text = "Nom de Dieu ! C'est affreux... As-tu appris quelque chose sur le galion ?";
			link.l1 = "Oui. Elle est en préparation pour embarquer depuis un moment déjà, mais le gouverneur de Portobello a l'intention de la maintenir au quai. Actuellement, il attend l'arrivée d'une barquentin nommée 'Puebla' en provenance de Carthagène avec une cargaison de poudre à canon pour l''Alcantara'. Selon un marin du galion, ils n'en ont pas assez et le gouverneur craint les pirates.";
			link.l1.go = "florian_14";
		break;
		
		case "florian_14":
			dialog.text = "Comme c'est intéressant !";
			link.l1 = "Mais si Puebla n'arrive pas dans trois jours, alors l'Alacantara cessera d'attendre et lèvera l'ancre.";
			link.l1.go = "florian_15";
		break;
		
		case "florian_15":
			dialog.text = "Excellent travail, Capitaine "+GetFullName(pchar)+" ! Je suis très satisfait ! Tenez, prenez votre récompense. Vous l'avez amplement méritée !";
			link.l1 = "Merci ! Avez-vous d'autres missions pour moi ?";
			link.l1.go = "florian_16";
		break;
		
		case "florian_16":
			TakeNItems(pchar, "gold_dublon", 250);
			Log_Info("You've received 250 doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "Tu lis dans mes pensées, "+GetFullName(pchar)+"! Oui, bon sang! Puisqu'Alacantara est à court de poudre à canon, je peux la laisser naviguer en haute mer et ensuite la forcer à s'engager dans un combat naval prolongé, dans lequel leur poudre s'épuisera avant la nôtre, haha!\nVous devez vous assurer que la barquentin de ravitaillement Puebla n'arrive jamais à Portobello. Je ne peux pas naviguer près de la côte, les patrouilles remarqueront facilement ma frégate et me chasseront avant que je puisse intercepter Alacantara.\nVous pouvez vous occuper de Puebla vous-même. Trouvez-la et débarrassez-vous d'elle. Coulez-la ou prenez-la comme prix, je m'en fiche. Empêchez-la simplement d'arriver ici!\nSi vous réussissez, allez à Guadeloupe et voyez Gerard LeCroix, je crois que vous le connaissez déjà, n'est-ce pas? Il vous paiera la somme que vous méritez.";
			link.l1 = "Marché conclu ! Je serai en route pour couper le Puebla !";
			link.l1.go = "florian_19";
			link.l2 = "Attendez un peu, Monsieur Choquet. Le fait est que je suis encore ... disons simplement, pas particulièrement habitué aux batailles navales. Et vous êtes le capitaine d'une frégate, vous avez évidemment plus d'une bataille navale derrière vous. Si cela ne vous dérange pas, vous pourriez... Comment devrais-je le dire...";
			link.l2.go = "florian_guide_01";
		break;
		
		case "florian_17":
			dialog.text = "Content que tu sois là, capitaine. Je viens de recevoir des informations de mon espion et j'ai une mission importante pour toi.";
			link.l1 = "Je suis tout ouïe.";
			link.l1.go = "florian_18";
		break;
		
		case "florian_18":
			dialog.text = "L'Alacantara est prête à prendre la mer, mais le capitaine du galion attend que la barquentin 'Puebla' arrive de Cartagena chargée de munitions. Apparemment, l'Alacantara n'a pas assez de poudre à canon, donc les Espagnols ne sont pas encore prêts à partir. Mais la patience du capitaine a ses limites et si la Puebla n'arrive pas dans trois jours, alors le galion quittera Portobello sans elle.\nL'Alacantara est à court de poudre à canon, je peux la laisser naviguer en haute mer et ensuite la forcer à s'engager dans un long combat naval, dans lequel leur poudre sera épuisée avant la nôtre. Votre objectif est d'intercepter la Puebla et de la détruire. Coulez-la ou prenez-la comme prise, cela m'est égal. Empêchez simplement cette barquentin de ravitaillement d'arriver ici !\nSi vous réussissez, allez à la Guadeloupe et voyez Gérard LeCroix, je crois que vous le connaissez déjà, n'est-ce pas ? Il vous paiera la monnaie que vous méritez.";
			link.l1 = "D'accord ! Je vais m'en aller couper la Puebla !";
			link.l1.go = "florian_19";
			link.l2 = "Attendez un peu, Monsieur Choquet. Le fait est que je suis encore... Disons simplement, pas particulièrement habitué aux batailles navales. Et vous êtes le capitaine d'une frégate, vous avez évidemment plus d'une bataille navale à votre actif. Si cela ne vous dérange pas, vous pourriez... Comment dire...";
			link.l2.go = "florian_guide_01";
		break;
		
		case "florian_19":
			DialogExit();
			Island_SetReloadEnableGlobal("Portobello", true); // открыть остров
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			LAi_CharacterDisableDialog(npchar);
			npchar.DontDeskTalk = true; 
			SetFunctionTimerCondition("Trial_RemoveFlorian", 0, 0, 1, false);
			Trial_CreatePueblaBarqueInWorld();
			pchar.questTemp.Trial = "puebla";
			AddQuestRecord("Trial", "19");
		break;
		// belamour legendary edition дополнительное обучение -->
		case "florian_guide_01":
			dialog.text = "Vous aimeriez que je vous donne une leçon sur les tactiques de combat naval ? Avec plaisir, capitaine ! D'autant plus que c'est dans mon propre intérêt : je veux être sûr que vous intercepterez avec succès le 'Puebla'.";
			link.l1 = "Non, je ne le pensais pas. Très bien, oublie ça : je suis sûr que je n'aurai aucun problème à intercepter une barquentin.";
			link.l1.go = "florian_19";
			link.l2 = "Oui, c'est exactement ce que je voulais dire. Je suis sûr que de nouvelles connaissances ne me feront pas de mal.";
			link.l2.go = "florian_guide_02";
		break;
		
		case "florian_guide_02":
			dialog.text = "Donc, la première chose à retenir est que la moitié de la bataille est gagnée ou perdue avant même qu'elle ne commence. Beaucoup dépend de la préparation de vous et de votre navire.";
			link.l1 = "character";
			link.l1.go = "florian_guide_03";
		break;
		
		case "florian_guide_03":
			dialog.text = "Tout d'abord, assurez-vous que votre navire est réparé. Si vous avez des trous dans la coque, il ne sera pas difficile pour l'ennemi de vous envoyer par le fond. Et si vous avez des haillons à la place des voiles, cela limite très significativement votre mobilité. L'ennemi peut facilement s'échapper si l'équilibre des forces n'est pas en sa faveur ou pire, vous rattraper et vous imposer une bataille désavantageuse - ou même vous aborder immédiatement. De plus, avec des voiles déchirées, vous aurez du mal à prendre le dessus au vent, c'est-à-dire à vous mettre au vent de votre adversaire là où vous voulez être.";
			link.l1 = "Le vent en poupe, compris. Autre chose ?";
			link.l1.go = "florian_guide_04";
		break;
		
		case "florian_guide_04":
			dialog.text = "Assure-toi d'avoir assez d'hommes. Même le navire le plus puissant avec des canons de 42 livres devient inutile si tu n'as qu'un canonnier pour recharger trois canons et qu'il n'y a simplement personne pour contrôler les voiles. En général, je monterais immédiatement à l'abordage d'un tel navire et le saisirais.";
			link.l1 = "Assez d'hommes, compris.";
			link.l1.go = "florian_guide_05";
		break;
		
		case "florian_guide_05":
			dialog.text = "De plus, surveille tes canons : ils s'useront et exploseront avec le temps. Avec le temps, l'état des fûts se détériore, et si tes canons commencent à exploser en plein milieu d'une bataille, cela peut très mal se terminer pour toi. Je n'ai pas eu de chance du tout : le lot de canons avec lequel j'ai navigué s'est avéré avoir plusieurs défauts de coulée. Si tu n'avais pas apporté de remplacement à temps, j'aurais simplement abandonné l'opération, car le Militant serait bien inférieur à l'Alcantara en puissance de feu. Les outils doivent être changés à temps.";
			link.l1 = "Maintenant je comprends pourquoi c'était si important !";
			link.l1.go = "florian_guide_06";
		break;
		
		case "florian_guide_06":
			dialog.text = "En plus des canons, garde aussi un œil sur la quantité de munitions. Alcantara tombera entre mes mains à cause de cela. Si elle a peu de poudre à canon, elle ne pourra pas mener une longue bataille - elle doit immédiatement passer au combat rapproché. Et je jouerai là-dessus : ma frégate est plus rapide, un lourd galion ne pourra pas s'en échapper. Mais je n'ai pas besoin non plus de m'approcher : j'imposerai un duel d'artillerie à longue portée et ensuite, quand la poudre sur l'Alcantara sera épuisée, je me rapprocherai, la criblerai de mitraille, et l'aborderai.";
			link.l1 = "Situation désespérée...";
			link.l1.go = "florian_guide_07";
		break;
		
		case "florian_guide_07":
			dialog.text = "Exactement. Surveille ta poudre et tes munitions. Si tu manques de boulets - et tu ne pourras probablement pas couler un navire ennemi. Si tu manques de mitraille, tu ne peux pas espérer un abordage si tu es en infériorité numérique. Si tu n'as pas de chainshot ou de knipples, tu ne pourras pas rattraper l'ennemi ou t'échapper s'il est plus rapide. Tous les types de munitions sont importants.";
			link.l1 = "Enseignant, merci.";
			link.l1.go = "florian_guide_08";
		break;
		
		case "florian_guide_08":
			dialog.text = "Et enfin, en fonction du type et de la taille de votre navire et de celui de l'ennemi, utilisez les tactiques appropriées. Il y a un compromis en mer entre la puissance de feu et la vitesse. Sur un grand navire lent, il ne sert à rien de poursuivre une goélette ou une corvette pour l'aborder - vous ne la rattraperez pas sans d'abord l'affaiblir avec des boulets ramés. Dans de tels cas, il est plus sage de la détruire à distance et de fouiller les débris. Si vous devez toujours aborder un tel navire, il est préférable d'utiliser un navire rapide et maniable.";
			link.l1 = "...";
			link.l1.go = "florian_guide_09";
		break;
		
		case "florian_guide_09":
			dialog.text = "En même temps, ne va pas te mesurer à un vaisseau de ligne avec une goélette. Une bordée d'un monstre comme ça réduira en éclats la coque des petits navires. Utilise ton avantage en vitesse et manœuvrabilité, abats ses mâts et son gréement, puis rapproche-toi et ratisse ses ponts à la mitraille si tu dois encore l'aborder. Si tu dois la couler... ce ne sera pas une tâche facile, mais c'est possible. Tu peux l'aborder et ensuite faire exploser sa soute à poudre, mais il n'est jamais honteux de fuir. Un bon capitaine sauvera son navire et son équipage d'une mort certaine au lieu d'un héroïsme excessif. Souviens-toi, discrétion et prudence sont souvent la meilleure part de la vaillance.";
			link.l1 = "Merci beaucoup, Monsieur Choquet !";
			link.l1.go = "florian_guide_10";
		break;
		
		case "florian_guide_10":
			AddCharacterSkillDontClearExp(pchar, SKILL_CANNONS, 1);
			AddCharacterSkillDontClearExp(pchar, SKILL_ACCURACY, 1);
			//Log_info(XI_ConvertString("Experience Bonus")+": +1 "+XI_ConvertString(SKILL_CANNONS));
			notification(XI_ConvertString("Experience Bonus")+": +1 ", SKILL_CANNONS);
			//Log_info(XI_ConvertString("Experience Bonus")+": +1 "+XI_ConvertString(SKILL_ACCURACY));
			notification(XI_ConvertString("Experience Bonus")+": +1 ",SKILL_ACCURACY);
			dialog.text = "Ravi de vous aider, capitaine. J'espère que ces connaissances vous seront utiles à l'avenir.";
			link.l1 = "Je suis sûr que cela aidera. Nous partons intercepter le 'Puebla!'";
			link.l1.go = "florian_19";
		break;
		// <-- legendary edition дополнительное обучение

		// испанский офицер в таверне
		case "tavern_officer":
			dialog.text = "C'est un accent inhabituel que vous avez là, senor. Ou devrais-je dire 'monsieur'? Voulez-vous voir Jaime Silicio? Peut-être pourriez-vous partager la même cellule. Emmenez-le, les gars !";
			link.l1 = "Eh bien, si mon accent ne te plaît pas, peut-être que je peux te présenter à l'escrime française !";
			link.l1.go = "tavern_officer_1";
		break;
		
		case "tavern_officer_1":
			DialogExit();
			chrDisableReloadToLocation = true;//закрыть локацию
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_SetWarriorTypeNoGroup(npchar);
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
            LAi_group_SetCheck("EnemyFight", "Trial_AfterTavernFight");
			AddDialogExitQuest("MainHeroFightModeOn");
			SetNationRelation2MainCharacter(SPAIN, RELATION_ENEMY);
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}
