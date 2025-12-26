// Якоб Джекман
int iBarbazonTotalTemp;
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sLoc;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

// ============================= блок angry ==========>>>>>>>>>>>>>>>>>>>>>>>>>
    if (CheckAttribute(npchar, "angry") && !CheckAttribute(npchar, "angry.ok"))
    {
        npchar.angry.ok = 1;
        if (!CheckAttribute(npchar, "angry.first")) //ловушка первого срабатывания
        {
            NextDiag.TempNode = NextDiag.CurrentNode;
            Dialog.CurrentNode = "AngryExitAgain";
            npchar.angry.first = 1;
        }
        else
        {
            switch (npchar.angry.kind) //сюда расписываем реакцию ангри. В npchar.angry.name пробелы удалены!!!
            {
                case "repeat":
                    if (npchar.angry.name == "Firsttime") Dialog.CurrentNode = "AngryRepeat_1";
                    if (npchar.angry.name == "I_know_you_good") Dialog.CurrentNode = "AngryRepeat_2";
                    if (npchar.angry.name == "pirate_threat")
                    {
                        if (Dialog.CurrentNode == "I_know_you_good") Dialog.CurrentNode = "AngryRepeat_2";
                        else Dialog.CurrentNode = "AngryRepeat_1";
                    }
                break;
            }
        }
    }
// <<<<<<<<<<<<<<<<<<<<<<======= блок angry ===================================
// ============================================================================

	switch(Dialog.CurrentNode)
	{
		// ----------------------------------- Диалог первый - первая встреча
		case "First time":
            if (sti(pchar.GenQuest.Piratekill) > 20)
			{
				dialog.text = RandPhraseSimple("Es-tu fou? Tu voulais jouer au boucher? Tous les pirates sont en colère contre toi, garçon, tu ferais mieux de quitter cet endroit...","Il semble que tu sois devenu fou, garçon. Tu voulais te dégourdir un peu les mains ? Sans vouloir t'offenser, mais tu n'as rien à faire ici. Dégage !");
				link.l1 = RandPhraseSimple("Ecoute, je veux arranger la situation...","Aidez-moi à résoudre ce problème...");
				link.l1.go = "pirate_town";
				break;
			}
			
			link.l0 = ""+npchar.name+", je voudrais" + GetSexPhrase("","e") + " discuter de ma sécurité en mer. Les gars de la Fraternité de la Côte s'intéressent un peu trop à ma modeste personne. Tu pourrais les calmer un peu ?";
			link.l0.go = "pirate_threat";
			
			dialog.text = NPCStringReactionRepeat("As-tu quelque chose à me dire ? Non ? Alors dégage d'ici !",
						"Je pense avoir été clair, cesse de m'importuner.","Bien que je me sois fait comprendre, tu continues à m'agacer !",
						"D'accord, je commence à en avoir marre de cette grossièreté.","répéter",3,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Je pars déjà.",
						"D'accord, "+npchar.name+"...",
						"Désolé, "+npchar.name+"...",
						"Aïe...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";

			//--> Сага
			if(CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "maruntown")
			{
				link.l1 = "Où puis-je trouver Jimmy Higgins ?";
				link.l1.go = "Saga_Jimmy";
			}	
			if(CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "jackman")
			{
				link.l1 = "Moi encore, Jackman. Ils disent que tu cherches des gens disparus...";
				link.l1.go = "Saga_search";
			}	
			//<-- Сага

			//поручение капитана - выкуп
			if (CheckAttribute(pchar, "GenQuest.CaptainComission") && NPChar.city == pchar.GenQuest.CaptainComission.PiratesCity)
			{
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.toMayor"))
				{
					link.l1 = "C'est à propos de votre prisonnier.";
					link.l1.go = "CapComission1";
					DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
				}	
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.PirateShips"))
				{
					link.l1 = "Salut, Jackman. A propos de ta mission...";
					link.l1.go = "CapComission3";
				}
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.RepeatSpeak"))
				{
					link.l1 = "C'est à propos de votre prisonnier.";
					link.l1.go = "CapComission6";
				}
			}	
		break;

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

        case "I_know_you_good":
            if (sti(pchar.GenQuest.Piratekill) > 20)
			{
				dialog.text = RandPhraseSimple("Es-tu fou? Tu voulais jouer au boucher? Tous les pirates sont en colère contre toi, garçon, tu ferais mieux de quitter cet endroit...");
				link.l1 = RandPhraseSimple("Ecoute, je veux arranger la situation...","Aidez-moi à résoudre ce problème...");
				link.l1.go = "pirate_town";
				break;
			}
			
			link.l0 = "Jacques, je voudrais" + GetSexPhrase("","e") + " discuter de ma sécurité en mer. Les gars de la Fraternité de la Côte s'intéressent un peu trop à ma modeste personne. Tu pourrais les calmer un peu ?";
			link.l0.go = "pirate_threat";
			
			dialog.text = NPCStringReactionRepeat("As-tu quelque chose à me dire ? Non ? Alors dégage d'ici !",
						"Je pense avoir été clair, cesse de m'importuner.","Bien que je me sois fait comprendre, tu continues à m'agacer !",
						"D'accord, je commence à en avoir marre de cette grossièreté.","répéter",3,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Je pars déjà.",
						"D'accord, Jacques...",
						"Désolé, Jacques...",
						"Aïe...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";

			//поручение капитана - выкуп
			if (CheckAttribute(pchar, "GenQuest.CaptainComission") && CheckAttribute(pchar,"GenQuest.CaptainComission.toMayor"))
			{
				link.l1 = "C'est à propos de votre prisonnier.";
				link.l1.go = "CapComission1";
				DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
			}				
		break;

//-----------------------------------------пиратская сага----------------------------------------------------
		case "Saga_Jimmy":
			dialog.text = "Vraiment ! Quelqu'un a besoin de ce fainéant ! Il boit du rhum tout seul dans sa cabane depuis plusieurs jours déjà. Je ne te conseille pas de lui rendre visite. Ce n'est pas un homme agréable, même quand il est à jeun...";
			link.l1 = "C'est bon, je ne suis pas non plus un saint. Où est sa cahute ?";
			link.l1.go = "Saga_Jimmy_1";
		break;
		
		case "Saga_Jimmy_1":
			dialog.text = "C'est juste devant la taverne. Il a choisi un bon endroit pour des courses rapides pour boire un coup.";
			link.l1 = "Merci !";
			link.l1.go = "Saga_Jimmy_2";
		break;
		
		case "Saga_Jimmy_2":
			DialogExit();
			pchar.quest.Saga_createJimmy.win_condition.l1 = "location";
			pchar.quest.Saga_createJimmy.win_condition.l1.location = "FortOrange_House1";
			pchar.quest.Saga_createJimmy.function = "Saga_CreateJimmy";
			pchar.questTemp.Saga = "jimmy";
		break;
		
		case "Saga_search":
			dialog.text = "Et qui t'a dit ça ? Ce pochard de Higgins ? As-tu découvert quelque chose à propos de Gladys Chandler ou Henry le Bourreau ?";
			link.l1 = "Rien de spécial, vraiment, mais je veux savoir quelque chose de précis sur ce Pendu.";
			link.l1.go = "Saga_search_1";
		break;
		
		case "Saga_search_1":
			dialog.text = "Il n'y a rien à savoir. Peu s'en souviennent maintenant, mais il y a vingt ans, Henry était très populaire parmi les catins de Bridgetown à Tortuga. Tu paries ! Un maître d'équipage du 'Neptune', sous le commandement du capitaine Boucher lui-même ! Il doit être vraiment vieux maintenant s'il est encore en vie, bien sûr.\nLes chances sont faibles, mais tu sais, rien n'est impossible. Je paierai vingt mille pesos pour n'importe quelle information à son sujet, le double si tu me l'amènes en vie.";
			link.l1 = "Combien paieras-tu pour Gladys et sa fille ?";
			link.l1.go = "Saga_search_2";
		break;
		
		case "Saga_search_2":
			dialog.text = "Oh, elle n'est pas sa fille. Si tu ramènes cette fille vivante, je te paierai une poignée de doublons. Gladys ne m'intéresse pas. Des questions ?";
			link.l1 = "J'aimerais bien savoir la raison de tout ce tapage mais je ne demanderai pas. On dirait que ça pourrait écourter ma biographie.";
			link.l1.go = "Saga_search_3";
		break;
		
		case "Saga_search_3":
			dialog.text = "Peut-être... Ces secrets ne vous concernent pas. Moins vous en savez, plus longtemps vous vivrez. N'essayez plus de me poser de telles questions, car je commence à soupçonner qu'il y a quelque chose de louche chez vous. Dégagez avant que je ne change d'avis.";
			link.l1 = "À la prochaine, baron !";
			link.l1.go = "Saga_search_4";
		break;
		
		case "Saga_search_4":
			DialogExit();
			AddQuestRecord("Saga", "6");
			if (CheckAttribute(pchar, "questTemp.Saga.Jimmysecret"))
			{
				AddQuestUserData("Saga", "sText", "To Antigua now. The corvette must be boarded.");
				DeleteAttribute(pchar, "questTemp.Saga.Jimmysecret");
			}
			pchar.quest.Saga_createDonovan.win_condition.l1 = "location";
			pchar.quest.Saga_createDonovan.win_condition.l1.location = "Antigua";
			pchar.quest.Saga_createDonovan.function = "Saga_createDonovan";
			pchar.questTemp.Saga = "donovan";
		break;
		
		// абордаж, в каюте
		case "Jackman_abordage":
			dialog.text = "Ha ! Nous nous rencontrons à nouveau, capitaine "+GetFullName(pchar)+". J'admets, tu es un adversaire digne, malgré tes tentatives de te faire passer pour un simplet à Maroon-Town. J'ai découvert quelque chose à ton sujet, tes intrigues avec la Compagnie néerlandaise des Indes occidentales ont été révélées... Je comprends maintenant quel genre de personne tu es.";
			link.l1 = "Je connais ton genre aussi, Jacob. Alors ne nous faisons pas d'illusions.";
			link.l1.go = "Jackman_abordage_1";
		break;
		
		case "Jackman_abordage_1":
			dialog.text = "Et comment tu m'as dupé avec 'Marlin' ! Je suppose que mon pauvre frère est mort...";
			link.l1 = "Je suppose que tu veux te venger pour lui? Mais j'ai aussi une longue liste pour toi. Pour le Nathaniel acculé, sa femme, sa frégate, le Requin calomnié, Blaze Sharp...";
			link.l1.go = "Jackman_abordage_2";
		break;
		
		case "Jackman_abordage_2":
			dialog.text = "Blaze ? Je ne l'ai pas tué.";
			link.l1 = "Même si c'est vrai, le reste de ma liste suffit. J'en ai assez de ton nom. Assez de paroles, Jackman ! Nos lames parleront !";
			link.l1.go = "Jackman_abordage_3";
		break;
		
		case "Jackman_abordage_3":
			dialog.text = "Quel imbécile véhément... Maudit sois-tu ! Maintenant tu ferais mieux de tenir bon ! Jacob Jackman n'a jamais été vaincu ! Carpacho, tu arrives juste à temps ! Viens ici !";
			link.l1 = "...";
			link.l1.go = "Jackman_abordage_4";
		break;
		
		case "Jackman_abordage_4":
			DialogExit();
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "Saga_AfterJackmanBoarding");
			AddDialogExitQuest("MainHeroFightModeOn");
			// подкрепление
			int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+12;
			int iScl = 30 + 2*sti(pchar.rank);
			sld = GetCharacter(NPC_GenerateCharacter("Saga_JackmanCabinHelper", "citiz_58", "man", "man", iRank, sti(npchar.nation), 0, true, "quest"));
			FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_21", "pistol4", "bullet", iScl*2+100);
			LAi_SetCheckMinHP(sld, 150, true, "Saga_DannyHurryHelp");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_BRDENEMY);
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
			sld = characterFromId("Danielle");
			RemovePassenger(Pchar, sld);
		break;

		//*************************** Генератор "Captain's offer - Ransom" **********************
		case "CapComission1":
			dialog.text = "Ha-ha. Tu penses que je n'ai qu'un seul prisonnier ici ? Nomme-le.";
			link.l1 = pchar.GenQuest.CaptainComission.SlaveName+"Est-il ici ?";
			link.l1.go = "CapComission2";
			DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
		break;

		case "CapComission2":
			if(CheckAttribute(pchar,"GenQuest.CaptainComission.DaysLeft"))
			{
				dialog.text = "Il l'était. Je l'ai vendu à ce propriétaire de plantation de la Barbade - le colonel Bishop, quand il était ici il y a une semaine.";
				link.l1 = "Merde...";
				link.l1.go = "CapComission2_1";
			}
			else
			{
				dialog.text = "Ah, enfin. Je pensais le vendre à ce propriétaire de plantation de la Barbade, il sera ici dans une semaine ou deux... As-tu une rançon ?";
				link.l1 = "Ecoute, il y a un petit problème... En fait, je n'ai pas autant d'argent. Mais je suis prêt à travailler.";
				link.l1.go = "CapComission2_2";
				if(makeint(pchar.money) > 150000)
				{
					link.l2 = "C'est bien que tu ne l'aies pas vendu. Voici tes pièces - 150.000 pesos. Où puis-je le trouver?"link.l2.go ="CommissionCapitaine2_3";
				}	
			}
		break;
		
		case "CapComission2_1":
			dialog.text = "Tu étais trop lent... Et pourquoi te soucies-tu de lui ? Je n'ai négocié qu'avec ses proches.";
			link.l1 = "Ils m'ont demandé de venir ici.";
			link.l1.go = "CapComission2_11";
		break;
		
		case "CapComission2_11":
			dialog.text = "Eh bien, tu es en retard. Je ne peux rien faire.";
			link.l1 = "Ecoute, pour combien l'as-tu vendu si ce n'est pas un secret ?"; 
			link.l1.go = "CapComission2_12";
		break;
		
		case "CapComission2_12":
			dialog.text = "Eh, ce n'est pas le cas. Mais je ne te le dirai pas... Tu riras si je le fais. Ha-ha-ha-ha ! Adieu.";
			link.l1 = "À plus tard...";
			link.l1.go = "exit";
			AddQuestRecord("CaptainComission1", "10");
			AddQuestUserData("CaptainComission1", "sName", "Jackman")); // belamour gen
			//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			CaptainComission_GenerateManager();
		break;
		
		case "CapComission2_2":
			if(rand(1) == 0)
			{
				dialog.text = "Eh bien, eh bien.. J'ai des affaires... Je ne sais même pas par où commencer. J'ai besoin de couler un pirate qui a dépassé les bornes.";
				link.l1 = "Ne peut-il tout simplement pas être tué dans la jungle ?";
				link.l1.go = "CapComission2_2_1";
			}
			else
			{
				dialog.text = "Eh bien, "+pchar.name+", tu sais, ça ne marche pas comme ça. Reviens avec l'argent et tu récupéreras ton maigrichon, ha-ha.";
				link.l1 = "D'accord. À plus tard.";
				link.l1.go = "CapComission2_4";
			}
		break;

		case "CapComission2_2_1":
			dialog.text = "Ce n'est pas ainsi que les affaires fonctionnent, tu sais... Je n'ai pas besoin de sa mort, j'ai besoin d'apprendre à quelques-uns à rester à l'écart de ma part du butin. Mais s'il va nourrir les requins, je ne serai pas contrarié.";
			link.l1 = "Pourquoi n'envoies-tu pas tes propres hommes après lui ?";
			link.l1.go = "CapComission2_2_2";
		break;
		
		case "CapComission2_2_2":
			CaptainComission_GetRandomShore();
			pchar.GenQuest.CaptainComission.ShipName1 = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.GenQuest.CaptainComission.ShipName2 = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.GenQuest.CaptainComission.UnknownPirateName = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);
			sLoc = XI_ConvertString(pchar.GenQuest.CaptainComission.Island + "Abl");
			dialog.text = "Hm... Eh bien, "+GetName(NAMETYPE_ORIG,pchar.GenQuest.CaptainComission.UnknownPirateName,NAME_NOM)+" a convaincu quelques pirates que leur part de butin est gardée dans notre cachette non loin de "+XI_ConvertString(pchar.GenQuest.CaptainComission.Island.Shore+"Gén")+". Leurs deux navires '"+pchar.GenQuest.CaptainComission.ShipName1+"' et '"+pchar.GenQuest.CaptainComission.ShipName2+"' levé les ancres il n'y a pas longtemps et a navigué vers "+sLoc+"Maintenant tu vois pourquoi je ne peux pas faire confiance à mes hommes pour ce boulot-là ?";
			link.l1 = "Je le fais. Combien de temps ai-je?";
			link.l1.go = "CapComission2_2_3";
		break;
		
		case "CapComission2_2_3":
			dialog.text = "12 à 15 jours, pas plus, je suppose. Je ne veux pas qu'ils atteignent la cachette, sinon ce serait absurde de les couler avec une cargaison précieuse. Dans ce cas, il vaudrait mieux qu'ils l'apportent ici...";
			link.l1 = "D'accord, je suis partant. Je vais essayer de les attraper.";
			link.l1.go = "CapComission2_2_4";
		break;
		
		case "CapComission2_2_4":
			AddQuestRecord("CaptainComission1", "24");
			AddQuestUserData("CaptainComission1", "sName", "Jackman")); // belamour gen
			//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			AddQuestUserData("CaptainComission1", "sShipName1", pchar.GenQuest.CaptainComission.ShipName1);
			AddQuestUserData("CaptainComission1", "sShipName2", pchar.GenQuest.CaptainComission.ShipName2);
			AddQuestUserData("CaptainComission1", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.Island.Shore + "Dat")); // belamour gen
			AddQuestUserData("CaptainComission1", "sShoreType", XI_ConvertString(GetIslandByArealName(pchar.GenQuest.CaptainComission.Island) + "Voc")); // belamour gen
			pchar.quest.CapComission_PirateAttack.win_condition.l1 = "location";
            pchar.quest.CapComission_PirateAttack.win_condition.l1.location = pchar.GenQuest.CaptainComission.Island;
            pchar.quest.CapComission_PirateAttack.function = "CaptainComission_GeneratePirateShips"; 
			SetFunctionTimerCondition("CaptainComission_PirateShipsOver", 0, 0, 15, false);
			pchar.GenQuest.CaptainComission.PirateShips = "goaway";	
			DialogExit();
		break;
		
		case "CapComission2_3":
			dialog.text = "Ne t'inquiète pas. Mes hommes le livreront à ton navire. Et pourquoi te soucies-tu de lui ?";
			link.l1 = "Je ne le fais pas. Ses proches m'ont demandé de le livrer.";
			link.l1.go = "CapComission2_31";
		break;
		
		case "CapComission2_31":
			dialog.text = "Ah, c'est bon. J'étais presque désolé d'avoir donné un prix si bas pour ton homme. Ha-ha-ha-ha. Adieu.";
			link.l1 = "À plus tard.";
			link.l1.go = "CapComission2_32";
		break;
		
		case "CapComission2_32":
			AddQuestRecord("CaptainComission1", "9");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));	// belamour gen		
			addMoneyToCharacter(pchar, -150000);
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");	
		break;
		
		case "CapComission2_4":
			if(!CheckAttribute(pchar,"GenQuest.CaptainComission.RepeatSpeak"))
			{
				AddQuestRecord("CaptainComission1", "31");
				AddQuestUserData("CaptainComission1", "sName", "Jackman"); // belamour gen
				//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			}	
			pchar.GenQuest.CaptainComission.RepeatSpeak = true;		
			DialogExit();
		break;
		
		case "CapComission3":
			dialog.text = "Alors, , "+GetFullName(pchar)+", as-tu coulé mon compagnon ? Ha-ha-ha...";
			if(pchar.GenQuest.CaptainComission.PirateShips == "goaway")
			{
				link.l1 = "Non. Je n'ai pas réussi à les attraper. Et je ne les ai pas rencontrés à leur retour.";
				link.l1.go = "CapComission4";
			}
			if(pchar.GenQuest.CaptainComission.PirateShips == "died")	
			{
				link.l1 = "Je l'ai fait. Je les ai envoyés nourrir les requins.";
				link.l1.go = "CapComission5";
			}
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
		break;
		
		case "CapComission4":
			dialog.text = "Nom de Dieu ! Que tu les aies rencontrés ou non, ça n'a plus d'importance maintenant ! Et quelle sera ta prochaine suggestion ?";
			link.l1 = "Peut-être avez-vous un boulot plus facile pour moi ?";
			link.l1.go = "CapComission4_1";
			link.l2 = "Ecoute, Jackman, baisse le prix pour le prisonnier...";
			link.l2.go = "CapComission4_2";
		break;
		
		case "CapComission4_1":
			dialog.text = "Non.";
			link.l1 = "Adieu alors...";
			link.l1.go = "CapComission4_3";
		break;
		
		case "CapComission4_2":
			dialog.text = "Faire baisser le prix ? Je viens de perdre mon magot à cause de ton incompétence ! Et maintenant je peux augmenter le prix ! Tu peux le prendre pour 200,000 pesos si tu veux, ou tu peux déguerpir d'ici.";
			link.l1 = "C’est trop cher... Adieu...";
			link.l1.go = "CapComission4_4";
			if(sti(pchar.money) >= 200000)
			{
				link.l2 = "Merde, prends tes pièces.";
				link.l2.go = "CapComission4_5";
			}	
		break;
		
		case "CapComission4_3":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			AddQuestRecord("CaptainComission1", "27");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_DAT));
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			DialogExit();
		break;
		
		case "CapComission4_4":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			AddQuestRecord("CaptainComission1", "28");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			DialogExit();		
		break;
		
		case "CapComission4_5":
			dialog.text = "Très bien, tu peux prendre ce faible...";
			link.l1 = "Adieu.";
			link.l1.go = "CapComission4_6";
		break;
		
		case "CapComission4_6":
			addMoneyToCharacter(pchar, -200000);
			AddQuestRecord("CaptainComission1", "29");
			AddQuestUserData("CaptainComission1", "sName", "Jackman"); // belamour gen
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc")); // belamour gen
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			pchar.GenQuest.CaptainComission.SlaveAddMoney = true;
			DialogExit();	
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");	
		break;
		
		case "CapComission5":
			dialog.text = "Ho-ho ! Bien joué ! Prends ton gringalet et bonne chance.";
			link.l1 = "Merci. Adieu.";
			link.l1.go = "CapComission5_1";
		break;
		
		case "CapComission5_1":
			AddQuestRecord("CaptainComission1", "34");
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc")); // belamour gen
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			DialogExit();		
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");	
		break;
		
		case "CapComission6":
			dialog.text = "As-tu apporté l'argent, Charles? Je ne plaisantais pas à propos de vendre l'homme à la plantation.";			
			link.l1 = "Écoute, "+NPChar.name+", il y a un problème... Je n'ai pas autant d'argent. Mais je suis prêt à travailler.";
			link.l1.go = "CapComission2_2";
			if(makeint(pchar.money) > 150000)
			{
				link.l2 = "C'est bien que tu ne l'aies pas vendu. Voici tes pièces - 150 000 pesos. Où puis-je le récupérer ?"link.l2.go ="CapComission2_3";
			}			
		break;
		
		// ============== Грабеж среди бела дня, попытка залезть в сундуки =========================
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Vol à la tire !!! Cela est inacceptable ! Prépare-toi, "+GetSexPhrase("garçon","fille")+"...","Hé, qu'est-ce que tu fous là ?! Tu pensais pouvoir me voler ? T'es fini...","Attends, qu'est-ce que c'est que ce bordel? Retire tes mains! Il s'avère que tu es un voleur! Fin de la route, salaud...");
			link.l1 = LinkRandPhrase("Merde !","Carramba!!","Sacré nom d'un chien !!");
			link.l1.go = "PL_Q3_fight";
		break;
					
		// ======================== блок нод angry ===============>>>>>>>>>>>>>>>
		case "AngryRepeat_1":
            dialog.text = RandPhraseSimple("Va-t'en d'ici !","Sors de chez moi !");
			link.l1 = "Oups...";
		    link.l1.go = "AngryExitAgainWithOut";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся с Джекменом через 10 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "Ne me dérange pas avec tes bavardages bon marché. La prochaine fois, tu n'aimeras pas le résultat...";
        			link.l1 = "Je l'ai.";
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
            }
    	break;
		case "AngryRepeat_2":
            dialog.text = "C'est fini, pas de parlote.""Je ne veux plus te parler, alors tu ferais mieux de ne pas me déranger.";
			link.l1 = RandPhraseSimple("Comme tu veux...","Très bien alors...");
		    link.l1.go = "AngryExitAgain";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся с Джекменом через 10 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "J'espère que vous montrerez plus de respect et cesserez d'être impoli ? Sinon, je devrai vous tuer. Ce serait très désagréable.";
        			link.l1 = "Tu peux en être sûr, Jackman, je le ferai.";
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
            }
    	break;
		case "AngryExitAgain":
            DialogExit();
            DeleteAttribute(npchar, "angry.ok");
		break;
		case "AngryExitAgainWithOut":
            DialogExit();
            DeleteAttribute(npchar, "angry.ok");
            DoReloadCharacterToLocation("Fortorange_town","reload","reload6");
		break;
		// <<<<<<<<<<<<============= блок нод angry =============================
		case "pirate_town":
            dialog.text = "Résoudre le problème ? Comprends-tu ce que tu as fait ? Quoi qu'il en soit, apporte-moi un million de pesos et je persuaderai les gars d'oublier tes 'exploits'. Si l'idée ne te plaît pas, tu peux aller au diable.";
			if (sti(Pchar.money) >= 1000000)
			{
				link.l1 = "D'accord, je suis prêt à payer.";
				link.l1.go = "pirate_town_pay";
			}
			link.l2 = "Compris. Je m'en vais.";
			link.l2.go = "pirate_town_exit";
		break;
		
		case "pirate_town_exit":
			DialogExit();
            bDisableFastReload = true;//закрыть переход
			pchar.quest.pirate_in_town.win_condition.l1 = "ExitFromLocation";
			pchar.quest.pirate_in_town.win_condition.l1.location = pchar.location;
			pchar.quest.pirate_in_town.function = "TownPirate_battle";
		break;
		
		case "pirate_town_pay":
            dialog.text = "Bien ! Considérez-vous de nouveau propre. Mais j'espère que vous ne ferez plus de choses aussi dégoûtantes.";
			link.l1 = "Je ne le ferai pas. Bien trop cher pour moi. Adieu...";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -1000000);
			pchar.GenQuest.Piratekill = 0;
		break;
		
		case "pirate_threat":
			if (GetNpcQuestPastDayWOInit(NPChar, "ThreatTalk") == 0)
			{
				dialog.text = NPCStringReactionRepeat("On a déjà parlé de ça aujourd'hui.",
				                                      "Je n’ai pas été assez clair ?",
				                                      "Ton insistance commence à m’agacer.",
				                                      "Ça suffit maintenant. Dégage d’ici !",
				                                      "repeat", 3, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Une autre fois, peut-être...",
				                                   "Bien sûr, "+npchar.name+"...",
				                                   "Désolé, "+npchar.name+"...",
				                                   "Aïe...", npchar, Dialog.CurrentNode);
				link.l1.go = "exit";
				break;
			}
			if (iGPThreat != 0)
			{
				iBarbazonTotalTemp = 10 * iGPThreatRate;
				dialog.text = "Ha ! Les gars de notre fraternité te mettent la pression, hein, " + GetSexPhrase("pote", "ma fille") + " ? Je peux les calmer un moment. Mais ça va te coûter un joli paquet. " + FindRussianDublonString(iBarbazonTotalTemp) + " sur la table, et on est d'accord.";
				if (PCharDublonsTotal() > iBarbazonTotalTemp)
				{
					if (iGPThreat < 5) link.l0 = "Évidemment, voilà ton argent.";
					else link.l0 = "On dirait que je n’ai pas le choix. Voilà ton argent.";
					link.l0.go = "pirate_threat_pay";
				}
				link.l1 = "Je repasserai plus tard...";
				link.l1.go = "exit";
			}
			else
			{
				SaveCurrentNpcQuestDateParam(NPChar, "ThreatTalk");
				if (NextDiag.TempNode != "I_know_you_good")
					dialog.text = "T’as perdu la tête" + GetSexPhrase("", " ma fille") + " ? Nos gars te fuient comme la peste. Alors fiche le camp et arrête de me casser les pieds.";
				else
					dialog.text = "De quoi tu parles, " + GetSexPhrase("pote", "ma fille") + " ? Tu es une vraie plaie — même les chiens le sentent. Personne ne veut avoir affaire à toi.";
				link.l1 = "Je vois...";
				link.l1.go = "exit";
			}
		break;

		case "pirate_threat_pay":
			iGPThreatRate = 0;
			iGPThreat = 0;
			SaveCurrentNpcQuestDateParam(NPChar, "ThreatTalk");
			RemoveDublonsFromPCharTotal(iBarbazonTotalTemp);
			DialogExit();
			PiratesDecreaseNotif("");
		break;
	}
}
