void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Que veux-tu ?";
			link.l1 = "Rien.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
        
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////----------------------------------------- работорговец -----------------------------------------------------
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//--> пинас
		case "TakeShoreCap":
    		dialog.text = "Canaille ! Grande surprise pour toi !";
    		link.l1 = "Quoi ?";
    		link.l1.go = "Node_1";
		break;
		
		case "Node_1":
			dialog.text = "Ha-ha ! Pas d'esclaves ici ! Vous êtes là pour eux, n'est-ce pas ?";
			link.l1 = "Merde. Et je me demandais pourquoi diable il y avait tant de soldats sur une pinasse marchande... Un piège !";
			link.l1.go = "Node_2";
		break;
		
 		case "Node_2":
			dialog.text = "Oui, salaud, c'est un piege. Je ne suis pas un marchand, je suis un officier militaire ! Bien que tu aies gagne le combat, tu n'echapperas pas au jugement !";
			link.l1 = "Et pourquoi donc ? Je vais te finir maintenant, couler ton navire et personne n'en saura rien.";
			link.l1.go = "Node_3";
		break;
		
 		case "Node_3":
			dialog.text = "Tu as tort. Ton affaire avec ce banquier a été révélée. Bientôt, le gouverneur général apprendra ton petit commerce et tu n'échapperas pas à la potence. Mais je te ferai une faveur en te tranchant la gorge ici et maintenant !";
			link.l1 = "Essaie, sale chien du gouverneur !";
			link.l1.go = "Node_4";
		break;
		
 		case "Node_4":
 		    pchar.questTemp.Slavetrader = "TakeShoreCap_end"; //это состояние квеста для проверки у квестодателя
            AddQuestRecord("Slavetrader", "13");
			AddQuestUserData("Slavetrader", "sShipName", pchar.questTemp.Slavetrader.ShipName);
            pchar.quest.Slavetrader_DieHard.over = "yes";
			pchar.quest.Slavetrader_AfterBattle.over = "yes";
			pchar.quest.Slavetrader_ShoreShipsOver.over = "yes";
            Island_SetReloadEnableGlobal(pchar.questTemp.Slavetrader.Island, true);
		    LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);			
			QuestAboardCabinDialogExitWithBattle(""); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Slave_arest":
			dialog.text = ""+GetFullName(pchar)+", au nom de la loi, vous êtes en état d'arrestation ! Rendez vos armes et suivez-nous !";
			link.l1 = "Que se passe-t-il, officier ? Se rendre pour quelles raisons ?";
			link.l1.go = "Slave_arest_1";
		break;
		
		case "Slave_arest_1":
			dialog.text = "Ne fais pas l'imbécile, capitaine ! Tes affaires louches ont été découvertes. Et pour le massacre que tu as commis et pour le navire de "+NationNameGenitive(sti(npchar.nation))+" que tu as coulé, nous te verrons pendu !";
			link.l1 = "Eh bien, puisque tu le dis ainsi... Va te faire foutre !";
			link.l1.go = "Slave_arest_2";
		break;
		
		case "Slave_arest_2":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_SetWarriorTypeNoGroup(npchar);
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
            LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		//--> крыса в доме
		case "Rat_bandos":
			dialog.text = "Eh, que fais-tu ici?!";
    		link.l1 = "Pourquoi êtes-vous si grossier, bon monsieur ? Ce rat de Gontier se cache-t-il quelque part ici, hein ?";
    		link.l1.go = "Node_rat_1";
		break;
			
		case "Node_rat_1":
			dialog.text = "Non, il ne l'est pas ! Sortez !";
			link.l1 = "On dirait que tu mens. Je vais fouiller la maison et je verrai...";
			link.l1.go = "Node_rat_2";
		break;
		
 		case "Node_rat_2":
			dialog.text = "Va te faire foutre ! Francois ! Cours ! Les gars, aidez-moi !";
			link.l1 = "Merde!";
			link.l1.go = "Node_rat_3";
		break;
		
		case "Node_rat_3":
            LAi_SetPlayerType(pchar);
            LAi_SetWarriorType(npchar);
            LAi_group_MoveCharacter(npchar, "EnemyFight");
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Slavetrader_findTortugaRat1");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Rat_lover":
			dialog.text = "Oh ! Ne me violez pas !";
    		link.l1 = "Quoi...? Où est Francois Gontier? Réponds-moi, sale catin, ou tu finiras comme tes camarades!";
    		link.l1.go = "Rat_lover_1";
		break;
			
		case "Rat_lover_1":
			dialog.text = "Non, non, je vous dirai tout ! Il a sauté par la fenêtre et s'est enfui vers son navire.";
    		link.l1 = "Quel navire ? Je sais qu'il n'y a pas son navire dans le port. Ne me mens pas, fille, ou ça va empirer...";
    		link.l1.go = "Rat_lover_2";
		break;
			
		case "Rat_lover_2":
			dialog.text = "Je ne mens pas, je le jure ! Il a dit qu'il a accosté sur une petite île et est arrivé ici sur une chaloupe... Il doit être là-bas ! Ne me faites pas de mal !";
    		link.l1 = "D'accord, il semble que tu dises la vérité. Reste ici et tais-toi. Et essaie de te faire des amis de manière plus astucieuse à l'avenir. Mais, tu sais, je le vois dans tes yeux et ils me disent que tu n'as pas de cervelle.";
    		link.l1.go = "Rat_lover_3";
			pchar.quest.Slavetrader_RatAttack.win_condition.l1 = "location";
            pchar.quest.Slavetrader_RatAttack.win_condition.l1.location = "Tortuga";//отправляем в локацию
            pchar.quest.Slavetrader_RatAttack.function = "Slavetrader_RatCorvette";//создание корвета
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			SetFunctionTimerCondition("Slavetrader_RatCorvetteOver", 0, 0, 1, false);
		break;
			
		case "Rat_lover_3":
 		    LAi_SetPlayerType(pchar);
            SetCharacterRemovable(npchar, false);
            LAi_SetActorType(npchar);
			npchar.lifeday = 0;
			AddQuestRecord("Slavetrader", "21_9");
            DialogExit();
		break;
		
		//--> беглые рабы
		case "Slave_woman":
			dialog.text = "Épargnez-nous ! Pitié ! Nous nous rendons !";
    		link.l1 = "Oh, c'est ainsi? Va dans la cale maintenant! Je tirerai sur quiconque essaie de jouer l'imbecile!";
    		link.l1.go = "exit";
			AddDialogExitQuestFunction("Slavetrader_Slavewoman");
		break;
	//<--работорговец
			
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////----------------------------------------- Генераторы -----------------------------------------------------
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//--> Jason ------------------------ Сомнительное предложение -------------------------------------------	
		int iCGood;
		case "Contraoffer_patrol":
			chrDisableReloadToLocation = false;
			iCGood = sti(pchar.GenQuest.Contraoffer.Trader.Goods);
			pchar.GenQuest.Contraoffer.Trader.PatrolSumm = sti(pchar.GenQuest.Contraoffer.Trader.Summ)/3;
			dialog.text = "Eh bien, eh bien... Qu'avons-nous là ? Ne savez-vous pas que le commerce de marchandises avec et entre des individus non autorisés est interdit dans notre colonie ?";
			link.l1 = "C'est le cas, officier ? Pour être honnête, c'est la première fois que j'en entends parler. Ce décret a été adopté il n'y a pas longtemps, ai-je raison ?";
			link.l1.go = "Contraoffer_patrol_1";
			link.l2 = "Quoi, troc "+GetGoodsNameAlt(iCGood)+"? Je ne vois rien "+GetGoodsNameAlt(iCGood)+" par ici, officier. Je ne vois que ces pièces brillantes... Et il voit la même chose. Pourquoi vous et vos soldats ne jetteriez-vous pas un œil à nos pièces aussi ?";
			link.l2.go = "Contraoffer_patrol_pay1";
		break;
		
		case "Contraoffer_patrol_1":
			if (GetSummonSkillFromName(pchar, SKILL_SNEAK) > hrand(120))
			{
				dialog.text = "Tu ne savais pas, hein ? Hmm... on dirait que tu ne mens pas. Mais néanmoins, tu as enfreint la loi. Je ne t'arrêterai pas, mais je dois te faire payer une amende. Et la cargaison... nous en parlerons avec le deuxième participant de l'affaire.";
				link.l1 = "Et combien coûte cette amende ?";
				link.l1.go = "Contraoffer_patrol_pay2";
			}
			else
			{
				dialog.text = "Ne fais pas l'imbécile, capitaine ! Tout le monde le sait déjà, et depuis longtemps je pourrais ajouter. Je vous arrête tous les deux pour contrebande et votre cargaison doit être confisquée.";
				link.l1 = "Je n'aime pas les casemates, officier. J'aime la mer ouverte... et je vais y naviguer maintenant. Mais il semble que je devrai le faire seulement par-dessus ton cadavre.";
				link.l1.go = "Contraoffer_patrol_fight";
				link.l2 = "Je n'ai pas le choix, je dois me rendre. Mais je n'avais vraiment aucune idée !";
				link.l2.go = "Contraoffer_patrol_jail";
			}
		break;
		
		case "Contraoffer_patrol_pay1":
			iCGood = sti(pchar.GenQuest.Contraoffer.Trader.Goods);
			if (GetSummonSkillFromName(pchar, SKILL_FORTUNE) > hrand(120))
			{
				dialog.text = "Maintenant, tu parles... Voyons tes pièces... Je crois avoir entendu un nombre assez précis - "+FindRussianMoneyString(sti(pchar.GenQuest.Contraoffer.Trader.Summ))+". Puisque nous avons maintenant trois participants, j'aimerais obtenir "+FindRussianMoneyString(sti(pchar.GenQuest.Contraoffer.Trader.PatrolSumm))+". Cela vient de toi et la même chose de ton ami.";
				link.l1 = "Bien sûr, officier. Voici mes pièces brillantes, ou, je suis désolé, vos pièces brillantes - vous venez de les laisser tomber accidentellement sur la plage... Et il n'y a pas "+GetGoodsNameAlt(iCGood)+" ici, ha-ha, comme je te l'ai dit.";
				link.l1.go = "Contraoffer_patrol_complete1";
				link.l2 = "Ho! Tu es trop avide, officier. Ta mère ne t’a-t-elle pas appris que la cupidité n’est pas une vertu ? Je suppose qu’il serait moins cher pour moi de te régler ton compte avec ma lame.";
				link.l2.go = "Contraoffer_patrol_fight";
			}
			else
			{
				dialog.text = "Tu plaisantes, capitaine ? Veux-tu me proposer un pot-de-vin ? Tu es en état d'arrestation ! Emparez-vous de lui !";
				link.l1 = "Eh bien, si tu ne veux pas jeter un oeil à mon argent, alors jette un oeil à mon épée !";
				link.l1.go = "Contraoffer_patrol_fight";
				link.l2 = "Je n'ai pas le choix, je dois me rendre. Mais je n'avais vraiment aucune idée !";
				link.l2.go = "Contraoffer_patrol_jail";
			}
		break;
		
		case "Contraoffer_patrol_complete1":
			dialog.text = "Oui, il semble que vous ayez raison... Rien d'intéressant ici à part quelques gentilshommes et mes pièces brillantes. Vous êtes libre de partir, capitaine, et nous aurons une discussion avec votre partenaire.";
			link.l1 = "Au revoir, officier. Ne lui fais pas de mal.";
			link.l1.go = "Contraoffer_patrol_complete";
		break;
		
		case "Contraoffer_patrol_pay2":
			dialog.text = ""+FindRussianMoneyString(sti(pchar.GenQuest.Contraoffer.Trader.PatrolSumm))+"Remerciez ma bonne humeur.";
			link.l1 = "Merci, officier. Je n'avais vraiment aucune idée... Tenez, je suis prêt à payer mon amende.";
			link.l1.go = "Contraoffer_patrol_complete2";
			link.l2 = "Je suppose que vous n'etes pas tres honnete non plus, officier. Votre amende est trop elevee. Je suppose que je vais aider cette colonie en la sauvant de votre presence.";
			link.l2.go = "Contraoffer_patrol_fight";
		break;
		
		case "Contraoffer_patrol_complete2":
			dialog.text = "Très bien. Vous pouvez partir maintenant. Et je vous conseille d'étudier les lois locales afin d'éviter des situations comme celle-ci à l'avenir. Allez-y maintenant, nous devons nous occuper du second participant de ce commerce, il était au courant de tout, c'est certain.";
			link.l1 = "Eh bien, dans ce cas, bonne journée à vous, officier.";
			link.l1.go = "Contraoffer_patrol_complete";
		break;
		
		case "Contraoffer_patrol_complete":
			AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Contraoffer.Trader.PatrolSumm));
			AddQuestRecord("Contraoffer", "6");
			CloseQuestHeader("Contraoffer");
			LAi_CharacterDisableDialog(npchar);
			DialogExit();
		break;
		
		case "Contraoffer_patrol_fight":
			AddQuestRecord("Contraoffer", "7");
			CloseQuestHeader("Contraoffer");
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), -5);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_SetWarriorTypeNoGroup(npchar);
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
            LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Contraoffer_patrol_jail":
			dialog.text = "Le commandant s'occupera de vous. Suivez-moi !";
			link.l1 = "...";
			link.l1.go = "Contraoffer_patrol_jail_exit";
		break;
		
		case "Contraoffer_patrol_jail_exit":
			GoToPrison(pchar.GenQuest.Contraoffer.Trader.City, sti(pchar.GenQuest.Contraoffer.Trader.Summ), 7);
			DialogExit();
			AddQuestRecord("Contraoffer", "8");
			CloseQuestHeader("Contraoffer");
			pchar.GenQuest.Contraoffer.Jail = "true";
		break;
	//<-- Сомнительное предложение	
		
	//Jason --> ----------------------------------- Неудачливый вор --------------------------------------------
		case "Device_poorman":
			dialog.text = "Bonne journée. Voulez-vous quelque chose ?";
			link.l1 = "Je le fais, mon pote. Je suppose que tu es mon gars. C'est toi qui as volé "+pchar.GenQuest.Device.Shipyarder.Type+"  du chantier naval local ? Tout mène à vous, alors pas de contestation.";
			link.l1.go = "Device_poorman_1";
		break;
		
		case "Device_poorman_1":
			switch (sti(pchar.GenQuest.Device.Shipyarder.Chance3))
			{
				case 0://выбросил
				if (sti(pchar.GenQuest.Device.Shipyarder.Chance2) != 1)
				{
					dialog.text = "Je vous en supplie, monseigneur ! Oui, j'ai volé cette chose étrange de l'arsenal. Mais je n'ai pas réussi à la vendre, personne n'a besoin d'un tel objet. Alors je m'en suis débarrassé. Epargnez-moi, bon monsieur, blâmez ma faim, pas moi... Je n'oserais jamais voler quoi que ce soit autrement !";
					link.l1 = "C'est un probleme... Et je n'ai pas besoin de toi non plus. Je dois trouver cela "+pchar.GenQuest.Device.Shipyarder.Type+"Où l'as-tu jeté ?";
					link.l1.go = "Device_poorman_0_1";
				}
				else //просто отдаст
				{
					dialog.text = "Je vous en supplie, monseigneur ! Oui, j'ai volé cette chose étrange du chantier naval. Mais je n'ai pas réussi à la vendre, personne n'a besoin d'un tel objet. Je vous la donnerai. Tenez, prenez-la, mais ne me faites pas de mal et n'appelez pas les soldats !";
					link.l1 = "Très bien, tu peux vivre, vaurien. Je n'ai pas besoin de ta peau, j'ai besoin de cet instrument. Donne-le-moi immédiatement et fiche le camp !";
					link.l1.go = "Device_poorman_0_2";
				}
				break;
				case 1://упирается, хитрый или храбрый
					dialog.text = "Que veux-tu dire ? Qu'est-ce que "+pchar.GenQuest.Device.Shipyarder.Type+" ? Je ne comprends pas ! ";
					link.l1 = "Tu l'auras quand je te fouillerai, toi ou ton cadavre ! Donne-le-moi maintenant !";
					link.l1.go = "Device_poorman_1_1";
				break;
				case 2://трусливый
					dialog.text = "Oh... Qu'est-ce que le "+pchar.GenQuest.Device.Shipyarder.Type+"? Moi... et qu'est-ce que c'est ?";
					link.l1 = "N'essaie pas de faire l'idiot ou de t'enfuir, je te rattraperai de toute façon. Laisse-moi juste fouiller tes poches...";
					link.l1.go = "Device_poorman_2_1";
				break;
			}
		break;
		
		case "Device_poorman_0_1"://идем на поиски
			dialog.text = "Derrière les portes de la ville, non loin des jungles. Je vous en supplie, bon monsieur ! Si vous avez vraiment besoin de cette chose, vous pouvez la récupérer vous-même. Elle doit encore être là-bas, j'en suis sûr.";
			link.l1 = "Je devrais te forcer à le trouver et me l'apporter, mais je crains que je passerais plus de temps à te chercher qu'à le "+pchar.GenQuest.Device.Shipyarder.Type+"Je le ferai moi-même. Mais je te trouverai si tu m'as menti !";
			link.l1.go = "exit";
			AddQuestRecord("Device", "3");
			string sCity = pchar.GenQuest.Device.Shipyarder.City + "_ExitTown";
			ref rItm = ItemsFromID("Tool");
			rItm.shown = true;
			rItm.startLocation = sCity;
			rItm.startLocator = "item" + (rand(14)+1);
			Log_TestInfo("Device is at the locator " + rItm.startLocator);
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "Device_poorman_0_2"://получили девайс
			dialog.text = "Tiens, prends-le. Merci, gentil monsieur !";
			link.l1 = "Eh bien, cela doit être ce que je cherchais... ha ! Vous êtes libre de partir maintenant. Allez. Et soyez prudent la prochaine fois.";
			link.l1.go = "exit";
			TakeNItems(pchar, "Tool", 1);
			Log_Info("You have received the stolen instrument");
			PlaySound("interface\important_item.wav");
			AddQuestRecord("Device", "4");
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "Device_poorman_1_1":
			pchar.GenQuest.Device.Shipyarder.Poorsumm = 1000+hrand(1000);
			dialog.text = "Ecoute, parles-tu de cet instrument ? Il m'appartient et je ne l'ai pas volé ! Et je ne vais pas te le donner gratuitement. Si tu veux l'obtenir, paie-moi "+FindRussianMoneyString(sti(pchar.GenQuest.Device.Shipyarder.Poorsumm))+".";
			if (sti(pchar.money) >= sti(pchar.GenQuest.Device.Shipyarder.Poorsumm))
			{
				link.l1 = "Hm... D'accord. Je vais te payer. Voici tes pieces et donne-moi l'instrument !";
				link.l1.go = "Device_poorman_1_2";
			}
			link.l2 = "Oh, vraiment? Pensais-tu vraiment que je te ferai confiance, misérable voleur? Donne le "+pchar.GenQuest.Device.Shipyarder.Type+" à moi maintenant ou j'appellerai les gardes, afin que nous puissions aller ensemble au chantier naval et décider à qui appartient réellement cet instrument.";
			link.l2.go = "Device_poorman_1_3";
			link.l3 = "Es-tu stupide, ou quoi? Ecoute, salaud, tu as deux options: soit tu me donnes le "+pchar.GenQuest.Device.Shipyarder.Type+"ou je te poignarde et prends l'instrument de ton cadavre !";
			link.l3.go = "Device_poorman_1_4";
		break;
		
		case "Device_poorman_1_2":
			dialog.text = "Bonne affaire, capitaine ! Je suppose que nous allons tous tirer nos profits, hé-hé... prends-le.";
			link.l1 = "Moins de bavardage, voleur ! Ne pense pas que tu m'as dupé, je veux juste le faire pacifiquement et avec moins de problèmes. Ces pièces ne te feront de toute façon aucun bien. Déguerpis !";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Device.Shipyarder.Poorsumm));
			TakeNItems(pchar, "Tool", 1);
			Log_Info("You have received the stolen instrument");
			PlaySound("interface\important_item.wav");
			AddQuestRecord("Device", "5");
			AddQuestUserData("Device", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Device.Shipyarder.Poorsumm)));
			AddQuestUserData("Device", "sName", pchar.GenQuest.Device.Shipyarder.Type);
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "Device_poorman_1_3":
			if (sti(pchar.GenQuest.Device.Shipyarder.Chance2) == 0)//если мы в городе
			{
				dialog.text = "Non ! Ne sonnez pas l'alarme ! Je... je vais vous donner cet fichu instrument. Tenez, prenez-le !";
				link.l1 = "C'est bien mieux maintenant! Déguerpissez! Ou vous finirez pendu à la potence, ce n'est qu'une question de temps.";
				link.l1.go = "exit_device";
			}
			else//храбрый попался
			{
				dialog.text = "Quels gardes, cap'? Il n'y a que toi et moi ici. Tu discutes trop, alors je vais devoir te calmer... avec ma lame.";
				link.l1 = "Tu oses me menacer, racaille ?!";
				link.l1.go = "Device_poorman_fight";
			}
		break;
		
		case "Device_poorman_1_4":
			if (sti(pchar.GenQuest.Device.Shipyarder.Chance2) == 0)//если мы в городе
			{
				dialog.text = "Ah ! Aidez-moi ! Assassin !";
				link.l1 = "Arrête là, chien!";
			link.l1.go = "exit";
				sld = characterFromId("Device_poorman");
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", -1);
				sld.lifeday = 0;
				AddQuestRecord("Device", "7");
				CloseQuestHeader("Device");
				DeleteAttribute(pchar, "GenQuest.Device.Shipyarder");
			}
			else//храбрый попался
			{
				dialog.text = "Eh bien, voyons qui poignardera qui, capitaine !";
				link.l1 = "Tu oses me menacer, vermine ?!";
				link.l1.go = "Device_poorman_fight";
			}
		break;
		
		case "Device_poorman_2_1":
			dialog.text = "Vous cherchez ? Je vous en prie, bon sire !";
			link.l1 = "Ecoute bien, soit tu me remets paisiblement ce que tu viens de voler au chantier naval, soit je te conduis au bureau du commandant. De toute façon, tu me donneras cet objet, mais d'abord tes talons seront brûlés au fer rouge. Peut-être te pendront-ils même après cela. A toi de choisir.";
			link.l1.go = "Device_poorman_2_2";
			link.l2 = "Donne-moi ce que tu as volé immédiatement, salaud, ou je te finirai là où tu te tiens !";
			link.l2.go = "Device_poorman_2_3";
		break;
		
		case "Device_poorman_2_2":
			if (sti(pchar.GenQuest.Device.Shipyarder.Chance1) < 2)//тут уж как повезёт
			{
				dialog.text = "Eh bien, il te faudra d'abord m'attraper si tu veux m'emmener au bureau du commandant ...";
				link.l1 = "Halte-là, chien !";
				link.l1.go = "exit";
				AddQuestRecord("Device", "7");
				sld = characterFromId("Device_poorman");
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", -1);
				sld.lifeday = 0;
				CloseQuestHeader("Device");
				DeleteAttribute(pchar, "GenQuest.Device.Shipyarder");
			}
			else
			{
				dialog.text = "Non, ne m'emmenez pas au bureau du commandant ! Je le donnerai moi-même ! Tenez, prenez-le, vous devez chercher cette chose. Personne ne l'achèterait de toute façon...";
				link.l1 = "Eh, je suppose que je pourrais quand même te mener au fort... Très bien, donne-moi l'outil et va-t'en !";
				link.l1.go = "exit_device";
			}
		break;
		
		case "Device_poorman_2_3"://напугали
			dialog.text = "Aïe ! Ne me blesse pas, je te donnerai tout ce que j'ai ! Tiens, prends-le !";
			link.l1 = "Ah, tu parles enfin! Déguerpis, je te livrerai au commandant si jamais je te revois dans cette ville. Adieu!";
			link.l1.go = "exit_device";
		break;
		
		case "exit_device":
			npchar.lifeday = 0;
			TakeNItems(pchar, "Tool", 1);
			Log_Info("You have received the stolen instrument");
			PlaySound("interface\important_item.wav");
			AddQuestRecord("Device", "6");
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "Device_poorman_fight":
			chrDisableReloadToLocation = true;
			sld = characterFromId("Device_poorman");
			TakeNItems(sld, "Tool", 1);
			sld.SaveItemsForDead = true; // сохранять на трупе вещи
            sld.DontClearDead = true; // не убирать труп через 200с
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
			AddQuestRecord("Device", "8");
			AddComplexSelfExpToScill(30, 30, 30, 50);
		break;
	//<-- Неудачливый вор
//-------------------------------------------почтовый генератор 2 уровня------------------------------------	
		case "PostGopHunters":
			dialog.text = "Arrête-toi là, l'ami ! Nous avons besoin de ce que tu portes. Donne-le nous et ensuite reprends ton chemin.";
			link.l1 = "De quoi parles-tu donc, bougre ?";
			link.l1.go = "PostGopHunters_1";
			link.l2 = "Ces gueux des rues sont trop insolents de nos jours... Préparez-vous, canailles !";
			link.l2.go = "PostHunters_fight";
		break;
		
		case "PostGopHunters_1":
			dialog.text = "Ne fais pas semblant d'être un imbécile ! Donne-nous le colis et tu vivras. Sinon... nous le prendrons sur ton cadavre !";
			link.l1 = "Les chances sont de votre cote... prenez-le, salauds, je n'ai pas le choix.";
			link.l1.go = "PostGopHunters_2";
			link.l2 = "Eh bien, tu peux essayer !";
			link.l2.go = "PostHunters_fight";
		break;
		
		case "PostGopHunters_2":
			dialog.text = "Surveille ton langage, mon gars... C'est astucieux de ta part de ne pas défier ta chance. La fin aurait été la même, ha-ha ! Tu vivras un moment... À la prochaine.";
			link.l1 = "...";
			link.l1.go = "exit_gophunter";
		break;
		
		case "PostProfHunters":
			dialog.text = "Attends, "+GetAddress_Form(NPChar)+", ne te hâte pas ainsi. J'ai une affaire pour toi.";
			link.l1 = "Quelle affaire ? Je ne te connais pas.";
			link.l1.go = "PostProfHunters_1";
		break;
		
		case "PostProfHunters_1":
			dialog.text = "Je vous connais, capitaine. Maintenant, allons droit au but. Vous venez de recevoir "+pchar.questTemp.WPU.Current.Add+"  dans "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.City+"Gen")+"Ne tente pas de le nier, nous le savons avec certitude - après tout, nous cherchons ce document depuis quelques jours.";
			link.l1 = "Maintenant je vois. Et alors ?";
			link.l1.go = "PostProfHunters_2";
		break;
		
		case "PostProfHunters_2":
			dialog.text = "Donne-moi le paquet et notre brève rencontre s'achève. Ne tente pas de jouer les héros, capitaine, nous avons l'intention d'obtenir ces papiers et nous sommes prêts à combattre la garnison de la ville si nécessaire.\nComme tu peux le comprendre, tu mourras le premier si l'escarmouche doit commencer. Alors donne-nous les documents et nous nous séparerons en amis.";
			link.l1 = "Les chances sont de votre côté... prenez ça, salauds, je n'ai pas d'autre choix.";
			link.l1.go = "PostProfHunters_3";
			link.l2 = "Tu essaies de m'effrayer ? J'ai vu des petits poissons qui se battent plus que tu ne le pourrais jamais ! Fous le camp.";
			link.l2.go = "PostProfHunters_4";
		break;
		
		case "PostProfHunters_3":
			dialog.text = "Je suis heureux que vous ayez été raisonnable, capitaine. Vous vous êtes mis en grand danger en acceptant ce travail. Maintenant, je vais prendre congé, si cela ne vous dérange pas.";
			link.l1 = "...";
			link.l1.go = "exit_profhunter";
		break;
		
		case "PostProfHunters_4":
			dialog.text = "C'était ta décision...";
			link.l1 = "...";
			link.l1.go = "PostHunters_fight";
			TraderHunterOnMap(false);//если деремся - запускаем ДУ вдогонку
		break;
		
		case "PostHunters_fight":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "exit_gophunter":
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			RemoveItems(PChar, pchar.questTemp.WPU.Current.Item, 1);
			for (i=1; i<=4; i++)
			{
				sld = characterFromId("PostHunters"+i);	
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "", 5.0);
			}
			AddQuestRecord("Postcureer", "11");
			AddQuestUserData("Postcureer", "sSex", GetSexPhrase("",""));
			DialogExit();
		break;
		
		case "exit_profhunter":
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			RemoveItems(PChar, pchar.questTemp.WPU.Current.Item, 1);
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("PostHunters"+i);	
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "", 5.0);
			}
			AddQuestRecord("Postcureer", "12");
			AddQuestUserData("Postcureer", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Postcureer", "sSex1", GetSexPhrase("",""));
			pchar.questTemp.WPU.Postcureer.fail = "true";
			DialogExit();
		break;
		
		case "PostAgent":
			bDisableFastReload = true; 
			dialog.text = "Attends, "+GetAddress_Form(NPChar)+", ne te précipite pas ainsi. J'ai un marché pour toi.";
			link.l1 = "Quel affaire ? Parle vite, je suis pressé.";
			link.l1.go = "PostAgent_1";
		break;
		
		case "PostAgent_1":
			dialog.text = "Je sais qui tu es. Et je sais aussi que tu viens de recevoir un "+pchar.questTemp.WPU.Current.Add+" "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.City+"Gen")+". Ces papiers sont la raison pour laquelle je suis si pressé de parler avec vous.";
			link.l1 = "Et je ne veux pas discuter de cette affaire avec des gens que je ne connais pas. Tu veux obtenir ces papiers ? Donne-moi simplement une raison...";
			link.l1.go = "PostAgent_2";
		break;
		
		case "PostAgent_2":
			dialog.text = "Assez, capitaine ! Ai-je l'air d'un brigand ? Je suis un homme d'affaires et je représente les intérêts de "+NationNameGenitive(sti(pchar.questTemp.WPU.Postcureer.EnemyNation))+". Je veux vous offrir une affaire très profitable, mais pas ici. Allons dans la chambre de la taverne et discutons de cette affaire. Cela ne prendra pas beaucoup de votre temps.";
			link.l1 = "C'est bien trop suspect... Je ne ferai aucune affaire avec vous, monsieur ! Dégagez !";
			link.l1.go = "PostAgent_getout";
			link.l2 = "Hm.. Voyons ce que tu peux m'offrir. Mais n'essaie même pas de m'attaquer, ça ne finira pas bien. Allons-y, je te suivrai.";
			link.l2.go = "PostAgent_3";
		break;
		
		case "PostAgent_getout":
			dialog.text = "Vous êtes un homme têtu et insensé, capitaine ! Je vous ai offert une chance de gagner de l'argent facilement. Et vous... vous le regretterez.";
			link.l1 = "Fous le camp !";
			link.l1.go = "PostAgent_getout_exit";
		break;
	
		case "PostAgent_3":
			dialog.text = "Splendide ! Suivez-moi.";
			link.l1 = "... ";
			link.l1.go = "exit";
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			NextDiag.TempNode = "PostAgent_inTavern";
			sld = characterFromId("PostAgent");	
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload4_back", pchar.questTemp.WPU.Postcureer.StartCity +"_tavern_upstairs", "goto", "goto1", "PostAgent_inTavern_Room", -1);
		break;
		
		case "PostAgent_getout_exit":
			bDisableFastReload = false; 
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			sld = characterFromId("PostAgent");	
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", 10);
			pchar.questTemp.WPU.Postcureer.AgentIslandID = GetCharacterCurrentIslandId(pchar);
			pchar.quest.Postcureer_Hunter.win_condition.l1 = "Location";
			pchar.quest.Postcureer_Hunter.win_condition.l1.location = pchar.questTemp.WPU.Postcureer.AgentIslandID;
			pchar.quest.Postcureer_Hunter.function = "PostcureerAgent_ShipAttack";
			AddQuestRecord("Postcureer", "13");
			AddQuestUserData("Postcureer", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Postcureer", "sSex1", GetSexPhrase("",""));
			DialogExit();
		break;
		
		case "PostAgent_inTavern":
			dialog.text = "Maintenant nous pouvons parler librement.";
			link.l1 = "Et quelle est votre proposition ?";
			link.l1.go = "PostAgent_inTavern_1";
		break;
		
		case "PostAgent_inTavern_1":
			dialog.text = "Comme je l'ai dit, tout tourne autour des documents que vous avez reçus au bureau du port. Tout ce dont j'ai besoin, c'est une copie de ceux-ci, c'est tout\nVous garderez l'original, donc ils vous paieront pour le travail. Personne ne saura jamais ce qui s'est passé, d'ailleurs je vous paierai bien.";
			link.l1 = "Excusez-moi... Mais le paquet est scellé. Vous ne pourrez pas faire de copies sans rompre un sceau !";
			link.l1.go = "PostAgent_inTavern_2";
		break;
		
		case "PostAgent_inTavern_2":
			dialog.text = "Je m'attendais à cette question. Je vais devoir briser le sceau, mais ne vous inquiétez pas, je pourrai le restaurer. J'ai bien sûr un cliché en double et de la cire à cacheter. Personne ne remarquera que le paquet a été ouvert.";
			link.l1 = "As-tu un faux cliché de l'administration du port de "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen")+"?";
			link.l1.go = "PostAgent_inTavern_3";
		break;
		
		case "PostAgent_inTavern_3":
			pchar.questTemp.WPU.Postcureer.AgentMoney = sti(pchar.rank)*3500;
			dialog.text = "Pourquoi demandes-tu, capitaine ? Oui, j'en ai un. Penses-tu vraiment que je ne fais que m'amuser ? Je te propose "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.AgentMoney))+" pour avoir une chance de voir ces documents. Alors, me donneras-tu enfin le paquet ? Je t'en prie.";
			link.l1 = "Prends-les, mais j'en ai besoin de retour et scellés !";
			link.l1.go = "PostAgent_inTavern_4";
			link.l2 = "Tu sais, je ne le ferai pas. Je n'aime pas ça.";
			link.l2.go = "PostAgent_inTavern_getout";
		break;
		
		case "PostAgent_inTavern_4":
			dialog.text = "Ne vous inquiétez pas. Je suis un professionnel. Prenez un siège et reposez-vous. Cela prendra environ une heure.";
			link.l1 = "D'accord.";
			link.l1.go = "PostAgent_inTavern_5";
		break;
		
		case "PostAgent_inTavern_5":
			NextDiag.currentnode = "PostAgent_inTavern_6";
			RemoveItems(PChar, pchar.questTemp.WPU.Current.Item, 1);
			pchar.questTemp.WPU.Postcureer.AgentChance = hrand(4);//шанс, что раскроют обман - 20%
			DialogExit();
			AddDialogExitQuest("PostAgent_inTavern_Room_end");
		break;
		
		case "PostAgent_inTavern_getout":
			dialog.text = "Hm... Je ne m'y attendais pas. Tu es trop têtu, capitaine, donc je vais devoir te tuer là où tu te tiens et prendre le colis gratuitement. Prie, car je manie ma lame aussi bien que je manie les faux clichés.";
			link.l1 = "C'est toi qui devrais prier, espion !";
			link.l1.go = "PostAgent_inTavern_fight";
		break;
		
		case "PostAgent_inTavern_6":
			dialog.text = "Fait. Comme je l'ai dit, cela a été fait de la manière la plus précise. Prends le paquet et promis "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.AgentMoney))+" . Et je dois y aller. Bonne chance, capitaine, je suis heureux que nous ayons conclu un accord.";
			link.l1 = "Adieu...";
			link.l1.go = "PostAgent_inTavern_7";
		break;
		
		case "PostAgent_inTavern_7":
			DialogExit();
			bDisableFastReload = false;
			chrDisableReloadToLocation = false; 
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.WPU.Postcureer.AgentMoney));
			GiveItem2Character(pchar, pchar.questTemp.WPU.Current.Item);
			sld = characterFromID("PostAgent");        
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", 2);
			AddQuestRecord("Postcureer", "15");
			AddQuestUserData("Postcureer", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Postcureer", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.AgentMoney)));
		break;
		
		case "PostAgent_inTavern_fight":
			bDisableFastReload = false;
			sld = characterFromID("PostAgent"); 
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
			AddQuestRecord("Postcureer", "16");
		break;
	//<-- почтовый генератор 2 уровня
		
	// --> --------------------------------- эскорт 2 уровень --------------------------------------------------
		case "DisasterCap":
			dialog.text = "Salutations! Oh, je suis tellement content de vous voir!";
			link.l1 = "Bonne journée. Hm, dites-moi, n'êtes-vous pas à la tête du "+pchar.questTemp.WPU.Escort.ShipName+"?";
			link.l1.go = "DisasterCap_1";
		break;
		
		case "DisasterCap_1":
			dialog.text = "Oh ! Et comment as-tu découvert le "+pchar.questTemp.WPU.Escort.ShipName+" ? Oui, je suis son capitaine. Ou je l'étais... Le navire a coulé non loin d'ici.";
			link.l1 = "Ah, alors je vous ai trouvé... Permettez-moi de me présenter - "+GetFullName(pchar)+". Je suis ici à la demande du maître de port de "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen")+"Il m'a brièvement parlé des ennuis de votre caravane et m'a envoyé chercher votre navire.";
			link.l1.go = "DisasterCap_2";
		break;
		
		case "DisasterCap_2":
			dialog.text = "Alors vous êtes capitaine de l'équipe de sauvetage ?";
			link.l1 = "Quelque chose comme ça. Ma tâche était de trouver votre navire ou des preuves de son naufrage ou de son incapacité à naviguer. Malheureusement, je n'ai pas trouvé le navire, mais son capitaine est vivant, c'est une bonne chose, c'est sûr...";
			link.l1.go = "DisasterCap_3";
		break;
		
		case "DisasterCap_3":
			dialog.text = "Oh, je suis désolé, j'ai oublié de me présenter. Je suis "+GetFullName(npchar)+". Sais-tu déjà comment nous avons atterri ici ? La tempête a rendu notre navire incontrôlable\nQuelques jours plus tard, elle a frappé les récifs non loin de cette baie et le vent violent l'a détruite en quelques minutes. Seules quelques douzaines de mes hommes ont survécu. Les autres reposent au fond. Nous prions pour leurs âmes chaque jour...";
			link.l1 = "Acceptez mes condoléances, capitaine "+GetFullName(npchar)+". Je suis tellement désolé.";
			link.l1.go = "DisasterCap_4";
		break;
		
		case "DisasterCap_4":
			dialog.text = "Merci... Les survivants ont installé un camp sur le rivage, espérant obtenir de l'aide. Vous arrivez juste à temps, capitaine ! Les Indiens belliqueux de la région sont au courant de notre présence, nous n'aurons aucune chance contre des centaines d'entre eux s'ils nous attaquent\nIl y a aussi un navire pirate, croisant dans cette zone, il semble qu'ils nous cherchent. Avez-vous rencontré ce pirate, capitaine ?";
			link.l1 = "Non, je n'ai pas.";
			link.l1.go = "DisasterCap_5";
		break;
		
		case "DisasterCap_5":
			dialog.text = "Dieu soit loué pour cela. Il est l'un de ceux qui nous ont attaqués avant cette maudite tempête. Comme une hyène, il est avide de terminer une proie blessée, alors il est arrivé ici, sur cette île.";
			link.l1 = "Je vois. Il est temps de décider de notre prochaine action.";
			link.l1.go = "DisasterCap_6";
		break;
		
		case "DisasterCap_6":
			dialog.text = "Décider de quoi, capitaine ? Embarquons et fuyons cet endroit maudit.";
			link.l1 = "Absolument. Je n'ai pas réussi à sauver le navire, mais au moins je sauverai son équipage. Démantelez votre camp et je vais ordonner d'envoyer des chaloupes ici. Bienvenue à bord !";
			link.l1.go = "DisasterCap_7";
		break;
		
		case "DisasterCap_7":
			PlaySound("people fight\rifle_fire1.wav");
			PlaySound("people fight\player_man_shoot_01.wav");
			dialog.text = "Gratitude, capitaine ! Cela ne prendra pas longtemps. Attends... Que diable ? Argh ! Ces diables à la peau rouge reviennent pour nous ! Alarme ! Aux armes !";
			link.l1 = "... ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("DisasterShipCrew_IndianAttack");
		break;
		
		case "DisasterCap_8":
			dialog.text = "Fuh, nous y sommes arrivés... Vous voyez, capitaine, je vous ai dit que cette baie est l'enfer même. C'est déjà la troisième attaque indienne ! Nous devons quitter cet endroit au plus vite, nous ne survivrons pas à une autre attaque.";
			link.l1 = "Oui, tu as raison. Rassemble toutes les âmes vivantes et monte sur mon navire ! Je vais ordonner qu'on nous envoie des chaloupes immédiatement !";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("DisasterShipCrew_onBoard");
			AddQuestRecord("Escort", "38");
			AddQuestUserData("Escort", "sIsland", XI_ConvertString(pchar.questTemp.WPU.Current.TargetIslandID));
			AddQuestUserData("Escort", "sSName", pchar.questTemp.WPU.Escort.ShipName);
			AddQuestUserData("Escort", "sShore", XI_ConvertString(pchar.questTemp.WPU.Current.TargetIslandID.Shore));
		break;
	// <-- эскорт 2 уровень
		
	//Jason --> -------------------------- Заносчивый аристократ ------------------------------------------------
		case "Badboy":
			dialog.text = "Hic... Que veux-tu de moi ? Dégage, je n'ai aucune envie de te parler.";
			link.l1 = "Es-tu "+pchar.GenQuest.Badboy.Brothel.Name+"?";
			link.l1.go = "Badboy_1";
		break;
		
		case "Badboy_1":
			dialog.text = "Oui, je le suis. Et que me veux-tu ?";
			link.l1 = "C'est assez simple. Il y a quelqu'un dans cette ville qui en a assez de tes tours. Cette personne en a ras-le-bol. Maintenant je te regarde et je vois pourquoi. Ne mets plus jamais les pieds au bordel local ou tu auras des ennuis. Compris ?";
			link.l1.go = "Badboy_2";
		break;
		
		case "Badboy_2":
			switch (sti(pchar.GenQuest.Badboy.Brothel.Type))
			{
				case 0://или напугается, или будет быковать - от авторитета
					if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 30)
					{
						dialog.text = "Argh ! Toi... tu oses me menacer, salaud ? Je vais te clouer sur ma lame et te faire cuire comme un poulet à la broche !";
						link.l1 = "Prépare-toi, enfoiré !";
						link.l1.go = "Badboy_fight_1";
						NextDiag.currentnode = "Badboy_after_fight";
					}
					else
					{
						dialog.text = "Quoi ? Quels tours ? Il n'y avait pas de tours. Je me suis saoulé et j'ai fait la bringue plusieurs fois dans le bordel. Personne n'est parfait... D'accord, d'accord, d'accord... Je n'utiliserai plus jamais leurs services. Satisfait maintenant ? Tu as ma parole.";
						link.l1 = "J'espère que la parole d'honneur signifie quelque chose pour vous et que vous êtes conscient des conséquences en cas de rupture. Gardez cela à l'esprit. Adieu maintenant.";
						link.l1.go = "exit";
						pchar.GenQuest.Badboy.Complete = "true";
						LAi_CharacterDisableDialog(npchar);
						npchar.lifeday = 0;
					}
				break;
				case 1://дуэль за городом
					dialog.text = "Vous êtes un homme si insolent, monsieur ! Je jure que vous allez regretter vos paroles avant le coucher du soleil. Je vous défie ! Je suppose qu'il vaudrait mieux nous battre en privé, quelque part au calme. La jungle fera l'affaire, retrouvez-moi là-bas dans deux heures !";
					link.l1 = "Une excellente idée ! Au moins, il ne serait pas difficile de cacher ton cadavre.";
					link.l1.go = "Badboy_duel";
					NextDiag.currentnode = "Badboy_duel_1";
					break;
				case 2://призовет на помощь дружков
					dialog.text = "Quoi ? Quels tours ? Il n'y avait pas de tours. Je me suis saoulé et j'ai fait la fête plusieurs fois au bordel. Personne n'est parfait... D'accord, d'accord, d'accord... Je n'utiliserai jamais plus leurs services. Satisfait maintenant ? Vous avez ma parole.";
					link.l1 = "J'espère que le mot d'honneur signifie quelque chose pour vous et que vous êtes conscient des conséquences en cas de rupture. Gardez cela à l'esprit. Adieu pour l'instant.";
					link.l1.go = "exit_continue";
					pchar.GenQuest.Badboy.Continue = "true";
					NextDiag.currentnode = "Badboy_friends";
				break;
			}
		break;
		
		case "Badboy_fight_1":
			chrDisableReloadToLocation = true;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			sld = characterFromId("Badboy");
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(sld, pchar.GenQuest.Badboy.Brothel.City + "_tavern", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");
			LAi_SetCheckMinHP(npchar, 10.0, true, "Badboy_capture");
			DialogExit();
		break;
		
		case "Badboy_after_fight":
			dialog.text = "Attends ! Arrête ! Je me rends ! Epargne-moi !";
			link.l1 = "Et c'est ainsi que tu parles maintenant !";
			link.l1.go = "Badboy_after_fight_1";
		break;
		
		case "Badboy_after_fight_1":
			dialog.text = "Je vous en supplie, épargnez-moi ! Je ferai ce que vous demandez ! Je ne remettrai jamais les pieds dans ce bordel !";
			link.l1 = "Cette pose ne convient qu'à une ordure comme toi. J'espère que cela te servira de leçon pour le reste de ta vie. Et tiens-toi correctement dans cette ville.";
			link.l1.go = "Badboy_exit";
			link.l2 = "D'accord, tu ne le feras pas. Tes tromperies prendront fin ici et maintenant.";
			link.l2.go = "Badboy_killed";
			pchar.GenQuest.Badboy.Complete = "true";
		break;
		
		case "Badboy_exit":
			LAi_SetPlayerType(pchar);
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);
			LAi_SetActorType(npchar);
			npchar.lifeday = 0;
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			DialogExit();
		break;
		
		case "Badboy_killed":
		DialogExit();
		LAi_SetImmortal(npchar, false);
			//  belamour legendary edition если не надет пистоль или мушкет, то выдадим строевой -->
			if(!CheckAttribute(pchar,"equip."+GUN_ITEM_TYPE) || !CheckAttribute(pchar,"equip."+MUSKET_ITEM_TYPE))
			{
				GiveItem2Character(pchar, "pistol1");
				EquipCharacterbyItem(pchar, "pistol1");
			}
			// <-- legendary edition
		LAi_ActorAnimation(pchar, "shot", "Badboy_killed_end", 2.2);
		break;
		
		case "Badboy_duel":
			chrDisableReloadToLocation = true;//закрыть локацию
			LAi_LocationDisableOfficersGen(pchar.GenQuest.Badboy.Brothel.City + "_ExitTown", true);//офицеров не пускать
			locations[FindLocation(pchar.GenQuest.Badboy.Brothel.City + "_ExitTown")].DisableEncounters = true; //энкаутеры закроем
			pchar.quest.BadboyDuelTimer.win_condition.l1 = "Timer";
			pchar.quest.BadboyDuelTimer.win_condition.l1.date.hour  = sti(GetTime() + 2);
			pchar.quest.BadboyDuelTimer.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.BadboyDuelTimer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.BadboyDuelTimer.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.BadboyDuelTimer.function = "Badboy_duelstart";
			sld = characterFromId("Badboy");
			LAi_SetActorType(sld);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(sld, pchar.GenQuest.Badboy.Brothel.City + "_tavern", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "OpenTheDoors", -1);
			TakeNItems(sld, "jewelry5", rand(10)); 
			TakeNItems(sld, "jewelry3", rand(10)); 
			TakeNItems(sld, "jewelry1", rand(10)); 
			sld.money = 24560;
			sld.SaveItemsForDead = true; // сохранять на трупе вещи
			sld.DontClearDead = true; // не убирать труп через 200с
			LAi_RemoveLoginTime(sld); //удалить время логина
			SetFunctionTimerCondition("Badboy_duelOver", 0, 0, 1, false);
			DialogExit();
		break;
		
		case "Badboy_duel_1":
			dialog.text = "Il est temps d'aller en enfer, enfoiré ! Prie pour toi-même, mais fais-le vite, je n'ai pas toute la putain de journée...";
			link.l1 = "Moins de parlote, plus de combat, racaille !";
			link.l1.go = "Badboy_duel_2";
		break;
		
		case "Badboy_duel_2":
			chrDisableReloadToLocation = true;
			LAi_SetPlayerType(pchar);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "Badboy_die");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "exit_continue":
			sld = characterFromID("Badboy");        
			LAi_RemoveLoginTime(sld); // patch-6
			LAi_SetActorType(sld);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(sld, pchar.GenQuest.Badboy.Brothel.City + "_tavern", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", -1);
			DialogExit();
		break;		
		
		case "Badboy_friends":
			dialog.text = "Et le voilà, cet insolent salaud ! Montrons-lui à qui appartient cette ville, les gars !";
			link.l1 = "Ah, tu es un tel dégénéré ! Mais je t'ai prévenu. Toi et tes singes serez envoyés droit en enfer dans une minute !";
			link.l1.go = "Badboy_friends_fight";
		break;
		
		case "Badboy_friends_fight":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
			DeleteAttribute(pchar, "GenQuest.Badboy");
		break;
	//Jason <-- Заносчивый аристократ
		
	//Jason --> ------------------------------- Место под солнцем ----------------------------------------------
		case "Sunplace_Store":
			pchar.quest.SunplaceContinue_Over.over = "yes";
			dialog.text = "Salutations. Que veux-tu ?";
			link.l1 = "Ne suis-tu pas "+pchar.GenQuest.Sunplace.Trader.Enemyname+"? Tu ne me croiras pas, ha-ha. Je veux ta tête.";
			link.l1.go = "Sunplace_Store_1";
			link.l2 = "Hm... Non... Ce n'est rien. Il semble que je me sois trompé. Pardonnez-moi de vous avoir dérangé.";
			link.l2.go = "Sunplace_Store_exit";
		break;
		
		case "Sunplace_Store_1":
			dialog.text = "Quelle plaisanterie absurde, monsieur ! Expliquez-vous ou je vais...";
			link.l1 = "Et que comptes-tu faire, misérable hareng ? Tu as joué un mauvais tour à un brave homme et il est vraiment contrarié. Alors prie maintenant et fais-le vite car je suis pressé.";
			link.l1.go = "Sunplace_Store_3";
		break;
		
		case "Sunplace_Store_3":
			dialog.text = "Qu... que faites-vous, monsieur ! A l'aide ! A l'aide, quelqu'un ! Assassin !";
			link.l1 = "Et je pensais que tu passerais tes dernières secondes à prier, au moins tu aurais pu avoir une chance d'atteindre les cieux...";
			link.l1.go = "Sunplace_Store_fight";
		break;
		
		case "Sunplace_Store_exit":
			sld = CharacterFromID("SunplaceTrader");
			sld.lifeday = 0;
			AddQuestRecord("Sunplace", "9");
			CloseQuestHeader("Sunplace");
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Sunplace.Trader");
			NextDiag.currentnode = "Sunplace_Store_repeat";
		break;
		
		case "Sunplace_Store_repeat":
			dialog.text = "Encore toi ? Pourquoi ne me dis-tu pas ce que tu veux ?";
			link.l1 = "C'est rien.";
			link.l1.go = "exit";
		break;
		
		case "Sunplace_Store_fight":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
			sld = CharacterFromID("SunplaceTrader");
			LAi_SetImmortal(sld, false);
			LAi_SetActorType(sld);
			LAi_ActorAfraid(sld, Pchar, true);
			sld = characterFromId(pchar.GenQuest.Sunplace.Trader.CityT + "_trader");
			LAi_group_Attack(sld, Pchar);
			pchar.quest.Kill_SunplaceTrader.win_condition.l1 = "ExitFromLocation";
			pchar.quest.Kill_SunplaceTrader.win_condition.l1.location = pchar.location;
			pchar.quest.Kill_SunplaceTrader.function = "Kill_SunplaceTrader";
		break;
	// <-- место под солнцем
		
	//------------------------------------- киллеры Лиги-------------------------------------------------------
		case "LigaHunters":
			dialog.text = "";
			link.l1 = "Ah?! Quoi? Que diable fais-tu ici, maudit soit-tu? Qui t'a laissé entrer?";
			link.l1.go = "LigaHunters_1";
		break;
		
		case "LigaHunters_1":
			dialog.text = "La ligue a besoin de ta vie, capitaine...";
			link.l1 = "Quoi ? Putain !";
			link.l1.go = "LigaHunters_2";
		break;
		
		case "LigaHunters_2":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("LigaHunter_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "LigaHunters_Dead");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
	// <-- киллеры Лиги
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//замечание по обнажённому оружию от персонажей типа citizen
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
			dialog.text = NPCharSexPhrase(NPChar,"Ecoute, je suis citoyen de cette ville et je te demanderais de rengainer ton épée.","Ecoutez, je suis le citoyen de cette ville et je vous demanderais de rengainer votre lame.");
			link.l1 = LinkRandPhrase("D'accord.","D'accord.","D'accord...");
			link.l1.go = "exit";
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"Fais attention, "+GetSexPhrase("pote","fille")+", en courant avec une arme. Je peux devenir nerveux...","Je n'aime pas quand il y a "+GetSexPhrase("hommes qui","les gens qui")+" marchent devant moi avec leur arme prête. Ça me fait peur...");
				link.l1 = LinkRandPhrase("Je l'ai.","C'est bon.","Ne t'inquiète pas...");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
			if (npchar.id == "Device_poorman") NextDiag.TempNode = "Device_poorman";
		break;
	}
}
