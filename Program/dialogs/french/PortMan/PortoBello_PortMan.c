// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	int i,n;
	string month;
	
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Quel genre de questions ?","Que veux-tu, "+GetAddress_Form(NPChar)+"?"),"Vous avez déjà essayé de me poser une question "+GetAddress_Form(NPChar)+"... ","Vous avez parlé d'une certaine question pour la troisième fois aujourd'hui...","Écoute, si tu n'as rien à me dire sur les affaires du port, alors ne me dérange pas avec tes questions.","bloc",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("J'ai changé d'avis.","Je n'ai rien à discuter."),"Peu importe.","En effet, déjà la troisième fois...","Désolé, mais je ne suis pas intéressé par les affaires du port pour l'instant.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.Slavetrader == "FindRatPortobello_1")
            {
                link.l1 = "Bonne journée à vous. J'aimerais savoir où se trouve le capitaine François Gontier. J'ai une affaire importante.";
                link.l1.go = "Portobello_ratP_1";
            }
			// belamour legengary edition на пару с Акулой -->
			if(CheckAttribute(pchar,"questTemp.SharkGoldFleet"))
			{
				if(pchar.questTemp.SharkGoldFleet == "toPBPortOffice" || pchar.questTemp.SharkGoldFleet == "KillCurier")
				{
					link.l1 = "Je suis un marchand, je viens de Caracas, et votre collègue de l'autorité portuaire locale m'a demandé de vous remettre quelques correspondances ...";
					link.l1.go = "SharkGoldFleet";
				}
				if(pchar.questTemp.SharkGoldFleet == "MoneySpeak")
				{
					link.l1 = "Oui, je suis là pour le paiement.";
					link.l1.go = "SharkGoldFleet_11";
				}
			}
			//<-- на пару с Акулой
		break;

		case "Portobello_ratP_1":
			dialog.text = "Une affaire importante, dites-vous ? Voyons voir. Eh bien... Francois Gontier, sur la corvette '"+pchar.questTemp.Slavetrader.ShipName+"... Selon mes notes, Senor Gontier se dirigeait vers la Jamaïque.";
			link.l1 = "Merci ! Vous avez beaucoup aidé !";
			link.l1.go = "exit";
			pchar.questTemp.Slavetrader = "FindRatJamaica";
			AddQuestRecord("Slavetrader", "21_3");
			AddQuestUserData("Slavetrader", "sShip", pchar.questTemp.Slavetrader.ShipName);
		break;
		// на пару с Акулой -->
		case "SharkGoldFleet":
			if(!bImCasual) pchar.quest.SharkGoldFleetToPB10.over = "yes"; 
			RemoveItems(PChar, "letter_1", 1);
			ChangeItemDescribe("letter_1", "itmdescr_letter_1");
			dialog.text = "Ah, bien, enfin ! Vous êtes un marchand, dites-vous ? Encore une fois, ils essaient d'économiser sur les courriers et de reporter l'expédition jusqu'à la dernière foutue... Ouais, bon, c'est sûr ! C'est vrai. Et c'est ainsi que je devrais équiper l'escadron avec eux dans un tel délai ?...";
			link.l1 = "On dirait de l'irresponsabilité...";
			link.l1.go = "SharkGoldFleet_01";
		break;
		
		case "SharkGoldFleet_01":
			dialog.text = "C'est une façon de le dire ! Eh bien, d'accord, que faire. Nous vous rencontrerons en temps voulu... Je parle du mien, ne faites pas attention. Écoutez, vous y retournez par hasard ?";
			link.l1 = "Eh bien, en fait, j'allais vendre des marchandises ici, puis - oui, retourner à Caracas ...";
			link.l1.go = "SharkGoldFleet_02";
		break;
		
		case "SharkGoldFleet_02":
			dialog.text = "Superbe ! Maintenant je vais leur écrire une réponse et vous demander de la renvoyer. Alors... Livrez-la, je vous prie, dans les dix jours, sinon ils n'auront pas le temps de faire quoi que ce soit à temps... Et déclinez votre nom.";
			if(pchar.questTemp.SharkGoldFleet == "KillCurier")
			{
				link.l1 = "Mon nom est "+GetFullName(pchar)+".";
				link.l1.go = "SharkGoldFleet_03";
			}
			else
			{
				link.l1 = "Mon nom est Andreas Garcia.";
				link.l1.go = "SharkGoldFleet_09";
			}
		break;
		
		case "SharkGoldFleet_03":
			TakeNItems(pchar, "letter_2", 1);
			ChangeItemDescribe("letter_2", "itmdescr_letter_SharkGoldFleet_2");
			dialog.text = "Attends une minute... Enregistré. Voilà. Souviens-toi : dix jours ! En attendant, je lirai plus en détail ce que tu m'as apporté.";
			link.l1 = "Oui, je me souviens. Adieu !";
			link.l1.go = "SharkGoldFleet_04";
		break;

		case "SharkGoldFleet_04":
			dialog.text = "Attendez une minute... Je ne comprends pas... Encore une fois, comment avez-vous dit que vous vous appeliez ?";
			link.l1 = "Moi?.. Eh bien... Pourquoi est-ce si important?";
			link.l1.go = "SharkGoldFleet_05";
		break;
		
		case "SharkGoldFleet_05":
			n = GetAddingDataDay(0,0,21);
			if(n<21) i = GetAddingDataMonth(0,1,0);
			else i = GetDataMonth();
			month = XI_ConvertString("MonthGen_" + i);
			pchar.questTemp.SharkGoldFleet.Date = ""+n+" "+month+"";
			SetFunctionTimerCondition("SharkGoldFleet1269fail", 0, 0, 22, false);
			SetFunctionTimerCondition("SGF_FleetTime", 0, 0, 21, false);
			if(!bImCasual) SetFunctionTimerCondition("SharkGoldFleetToCPO10", 0, 0, 10, false);
			else NewGameTip("Exploration mode: timer is disabled.");
			dialog.text = "C'est très important ! Il est écrit... Alors... "+n+" "+month+"... Non, ce n'est pas ça... 12, 50, 69, 55... Mais où est-ce... Ah, le voilà ! La lettre doit être livrée par le capitaine "+pchar.questTemp.SharkGoldFleet.CurierName+" "+pchar.questTemp.SharkGoldFleet.Curierlastname+". Et vous avez dit que votre nom est... "+GetFullName(pchar)+"?";
			link.l1 = "Il doit y avoir eu une erreur...";
			link.l1.go = "SharkGoldFleet_06";
		break;
		
		case "SharkGoldFleet_06":
			DeleteAttribute(pchar,"questTemp.SharkGoldFleet.CurierName");
			DeleteAttribute(pchar,"questTemp.SharkGoldFleet.Curierlastname");
			dialog.text = "Non, il ne peut y avoir d'erreur. Rends-moi la lettre que je t'ai donnée. Je dois élucider cela !";
			link.l1 = "Allez... Je le livrerai, tout ira bien.";
			link.l1.go = "SharkGoldFleet_07";
		break;
		
		case "SharkGoldFleet_07":
			dialog.text = "Non ! Rendez-moi la lettre ! Gardes !!!";
			link.l1 = "Ah tu veux la jouer à la dure, hein ?";
			link.l1.go = "SharkGoldFleet_08";
		break;
		
		case "SharkGoldFleet_08":
			DialogExit();
			pchar.questTemp.SharkGoldFleet = "DifficultVar";
			if (CheckCharacterItem(pchar, "HolTradeLicence"))
			{
				TakeNationLicence(HOLLAND);
				log_info("Trading license cancelled!");
			}
			for (i=1; i<=2; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("Sold"+i, "sold_" + NationShortName(SPAIN) + "_" + (rand(1) + 1), "man", "man", sti(pchar.rank), SPAIN, 0, true, "soldier"));
				SetFantomParamFromRank(sld, sti(pchar.rank), true);         
				ChangeCharacterAddressGroup(sld, pchar.location, "goto",  "goto3");
				LAi_SetWarriorType(sld); 
				LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
				LAi_group_Attack(sld, Pchar);
			}
			LAi_group_Attack(NPChar, Pchar);
			SetNationRelation2MainCharacter(SPAIN, RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
			SetFunctionExitFromLocationCondition("SharkGoldFleetExitPO", pchar.location, false);
		break; 
		
		case "SharkGoldFleet_09":
			dialog.text = "Attendez une minute... Voilà. Ensuite, je noterai votre nom dans une lettre de réponse. Tenez, la voilà. N'oubliez pas : vous avez dix jours ! En attendant, je lirai plus en détail ce que vous m'avez apporté.";
			link.l1 = "Oui, je me souviens. Adieu !";
			link.l1.go = "SharkGoldFleet_10";
		break;
		
		case "SharkGoldFleet_10":
			DialogExit();
			pchar.questTemp.SharkGoldFleet = "MoneySpeak";
			TakeNItems(pchar, "letter_2", 1);
			ChangeItemDescribe("letter_2", "itmdescr_letter_SharkGoldFleet_2");
			AddQuestRecord("SharkGoldFleet", "17");
			chrDisableReloadToLocation = true;
			bDisableFastReload = true;
		break;
		
		case "SharkGoldFleet_11":
			dialog.text = "Paiement ?..";
			link.l1 = "À Caracas, votre collègue m'a dit que vous paieriez pour la livraison de la lettre.";
			link.l1.go = "SharkGoldFleet_12";
		break;
		
		case "SharkGoldFleet_12":
			dialog.text = "Non, eh bien, ils sont complètement fous là-bas ! Maintenant je dois payer pour eux !";
			link.l1 = "...";
			link.l1.go = "SharkGoldFleet_13";
		break;
		
		case "SharkGoldFleet_13":
			dialog.text = "Et combien vous ont-ils promis ?";
			link.l1 = "Cinq mille pesos.";
			link.l1.go = "SharkGoldFleet_14";
			link.l2 = "Dix mille pesos.";
			link.l2.go = "SharkGoldFleet_15";
		break;
		
		case "SharkGoldFleet_14":
			pchar.questTemp.SharkGoldFleet = 5000;
			dialog.text = "Apparemment, ils ont décidé de vivre là-bas à mes frais... Non seulement ils ne veulent pas dépenser d'argent pour des courriers, confiant de tels cas à des navires marchands de passage, mais en plus ils me collent les dépenses ! Je vais écrire une plainte contre eux à La Havane !";
			link.l1 = "Je comprends votre indignation, señor, mais que dois-je faire ?";
			link.l1.go = "SharkGoldFleet_16";
		break;
		
		case "SharkGoldFleet_15":
			pchar.questTemp.SharkGoldFleet = 10000;
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			ChangeOfficersLoyality("bad", 1);
			dialog.text = "Apparemment, ils ont décidé de vivre à mes dépens... Non seulement ils ne veulent pas dépenser d'argent pour des courriers, confiant de tels cas à des navires marchands de passage, mais ils me chargent aussi les dépenses ! Je vais écrire une plainte contre eux à La Havane !";
			link.l1 = "Je comprends votre indignation, señor, mais que dois-je faire ?";
			link.l1.go = "SharkGoldFleet_16";
		break;
		
		case "SharkGoldFleet_16":
			dialog.text = "Argh, tu n'es pas à blâmer pour l'avidité des officiels de la Nouvelle-Espagne à Caracas. Mais je n'ai tout simplement pas cette somme d'argent sur moi en ce moment. Et le budget ne devrait arriver que demain... Attends ici, s'il te plaît, je vais aller chez le prêteur sur gages maintenant - et je reviens tout de suite.";
			link.l1 = "Got it! Please provide the text for translation.";
			link.l1.go = "SharkGoldFleet_17";
		break;
		
		case "SharkGoldFleet_17":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorTurnToLocator(pchar, "reload", "reload1");
			LAi_SetStayType(npchar);
			ChangeCharacterAddressGroup(npchar, pchar.location, "goto", "goto2");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "reload", "reload1","SGF_toUsurer", -1);
		break;
		
		case "SharkGoldFleet_18":
			AddMoneyToCharacter(pchar, makeint(pchar.questTemp.SharkGoldFleet));
			n = GetAddingDataDay(0,0,21);
			if(n<21) i = GetAddingDataMonth(0,1,0);
			else i = GetDataMonth();
			month = XI_ConvertString("MonthGen_" + i);
			pchar.questTemp.SharkGoldFleet.Date = ""+n+" "+month+"";
			SetFunctionTimerCondition("SharkGoldFleet1269fail", 0, 0, 22, false);
			SetFunctionTimerCondition("SGF_FleetTime", 0, 0, 21, false);
			if(!bImCasual) SetFunctionTimerCondition("SharkGoldFleetToCPO10", 0, 0, 10, false);
			else NewGameTip("Exploration mode: timer is disabled.");
			AddQuestRecord("SharkGoldFleet", "18");
			AddQuestUserData("SharkGoldFleet", "date", pchar.questTemp.SharkGoldFleet.Date);
			LAi_SetHuberType(npchar);
			Lai_SetPlayerType(pchar);
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			dialog.text = "Je suis désolé pour l'attente. Voici votre "+makeint(pchar.questTemp.SharkGoldFleet)+"pièces de huit. Et dans ce cas, ils paieront eux-mêmes pour la réponse à Caracas. Dites-moi ce que j'ai fait.";
			link.l1 = "Bien, je le transmettrai. Merci et bonne chance !";
			link.l1.go = "exit";
			pchar.questTemp.SharkGoldFleet = "LightVar";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
