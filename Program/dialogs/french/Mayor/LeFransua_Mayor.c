// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Que veux-tu ? Demande.","Je t'écoute, quelle est la question ?"),"C'est la deuxième fois que tu essaies de demander...","C'est la troisième fois que tu essaies de demander...","Quand cela va-t-il finir?! Je suis un homme occupé, travaillant sur les affaires de la colonie et tu continues à me déranger!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("J'ai changé d'avis...","Pas maintenant. Mauvais endroit et mauvais moment."),"C'est vrai... Mais plus tard, pas maintenant...","Je demanderai... Mais un peu plus tard...","Je suis désolé, "+GetAddress_FormToNPC(NPChar)+"...",npchar,Dialog.CurrentNode);			  
			link.l1.go = "exit";

			if (CheckAttribute(pchar, "GenQuest.CaptainComission") && NPChar.city == pchar.GenQuest.CaptainComission.PiratesCity)
			{
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.toMayor"))
				{
					link.l1 = "Je veux parler de ton prisonnier.";
					link.l1.go = "CapComission1";
					DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
				}	
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.PirateShips"))
				{
					link.l1 = "Bonjour "+NPChar.name+", je suis ici à propos de votre prisonnier.";
					link.l1.go = "CapComission3";
				}
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.RepeatSpeak"))
				{
					link.l1 = "Je veux parler de ton prisonnier.";
					link.l1.go = "CapComission6";
				}
			}
			if (CheckAttribute(pchar, "GenQuest.Marginpassenger") && pchar.GenQuest.Marginpassenger == "cabin")
			{
				link.l1 = "J'ai entendu dire que vous étiez engagé dans une affaire liée aux prisonniers...";
				link.l1.go = "Marginpassenger";
			}
		break;
		
		
		case "CapComission1":
			dialog.text = "Ha-ha. Tu penses que je n'ai qu'un seul prisonnier ici ? Nomme-le.";
			link.l1 = pchar.GenQuest.CaptainComission.SlaveName+"Est-il là ?";
			link.l1.go = "CapComission2";
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
				pchar.quest.CaptainComission_SellSlave.over = "yes";
				dialog.text = "Ah, enfin. Je pensais le vendre à ce propriétaire de plantation de la Barbade, il sera ici dans une semaine ou deux... As-tu une rançon ?"+GetSexPhrase("","")+"?";
				link.l1 = "Regarde, "+NPChar.name+" , il y a un petit problème... En fait, je n'ai pas autant d'argent. Mais je suis prêt à travailler.";
				link.l1.go = "CapComission2_2";
				if(makeint(pchar.money) > 150000)
				{
					link.l2 = "C'est bien que tu ne l'aies pas vendu. Voici tes pièces - 150.000 pesos. Où puis-je le trouver ?"link.l2.go ="CapComission2_3";
				}	
			}
		break;
		
		case "CapComission2_1":
			dialog.text = "Tu étais trop lent... Et pourquoi t'en soucies-tu? Je n'ai négocié qu'avec ses proches.";
			link.l1 = "Ils m'ont demandé de venir ici.";
			link.l1.go = "CapComission2_11";
		break;
		
		case "CapComission2_11":
			dialog.text = "Eh bien, tu es en retard. Je ne peux rien faire.";
			link.l1 = "Ecoute, combien l'as-tu vendu si ce n'est pas un secret ?"; 
			link.l1.go = "CapComission2_12";
		break;
		
		case "CapComission2_12":
			dialog.text = "Eh, ce n'est pas ça. Mais je ne te le dirai pas... Tu vas rire si je le fais. Ha-ha-ha-ha ! Adieu.";
			link.l1 = "À plus.";
			link.l1.go = "exit";
			AddQuestRecord("CaptainComission1", "10");
			AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			CaptainComission_GenerateManager();
		break;
		
		case "CapComission2_2":
			if(rand(1) == 0)
			{
				dialog.text = "Eh bien, eh bien.. J'ai une affaire... Je ne sais même pas par où commencer. J'ai besoin de couler un pirate qui est allé trop loin.";
				link.l1 = "Ne peut-il pas simplement être tué dans la jungle ?";
				link.l1.go = "CapComission2_2_1";
			}
			else
			{
				dialog.text = "Eh bien, "+pchar.name+", tu sais, ça ne marche pas comme ça. Reviens avec l'argent et tu récupéreras ton faible, ha-ha.";
				link.l1 = "Bien, adieu alors.";
				link.l1.go = "exit";
				if(!CheckAttribute(pchar,"GenQuest.CaptainComission.RepeatSpeak"))
				{
					AddQuestRecord("CaptainComission1", "31");
					AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
				}	
				pchar.GenQuest.CaptainComission.RepeatSpeak = true;
			}
		break;

		case "CapComission2_2_1":
			dialog.text = "Ce n'est pas comme ça que les affaires fonctionnent, tu sais... Je n'ai pas besoin de sa mort, je dois apprendre à certains à éviter de prendre ma part du butin. Mais s'il va nourrir les requins, je ne serai pas contrarié.";
			link.l1 = "Pourquoi n'envoies-tu pas tes propres hommes après lui ?";
			link.l1.go = "CapComission2_2_2";
		break;
		
		case "CapComission2_2_2":
			CaptainComission_GetRandomShore();
			pchar.GenQuest.CaptainComission.ShipName1 = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.GenQuest.CaptainComission.ShipName2 = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.GenQuest.CaptainComission.UnknownPirateName = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);
			dialog.text = "Hm.. Eh bien "+GetName(NAMETYPE_ORIG,pchar.GenQuest.CaptainComission.UnknownPirateName,NAME_NOM)+"a convaincu quelques pirates que leur part du butin sera gardée dans notre cachette non loin de "+XI_ConvertString(pchar.GenQuest.CaptainComission.Island.Shore+"Gen")+". Leurs deux navires '"+pchar.GenQuest.CaptainComission.ShipName1+"' et '"+pchar.GenQuest.CaptainComission.ShipName2+"'a levé l'ancre il n'y a pas longtemps et a mis les voiles vers "+XI_ConvertString(pchar.GenQuest.CaptainComission.Island+"Abl")+"Maintenant tu vois pourquoi je ne peux pas faire confiance à mes hommes pour ce boulot ?";
			link.l1 = "Je vois. Combien de temps ai-je?";
			link.l1.go = "CapComission2_2_3";
		break;
		
		case "CapComission2_2_3":
			dialog.text = "12 à 15 jours, pas plus. Il est crucial pour moi qu'ils n'atteignent pas la cachette, ce serait absurde de les couler avec une cargaison précieuse. Dans ce cas, il vaudrait mieux qu'ils l'apportent ici...";
			link.l1 = "D'accord, je suis partant. Je vais essayer de les attraper.";
			link.l1.go = "exit";
			AddQuestRecord("CaptainComission1", "24");
			AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			AddQuestUserData("CaptainComission1", "sShipName1", pchar.GenQuest.CaptainComission.ShipName1);
			AddQuestUserData("CaptainComission1", "sShipName2", pchar.GenQuest.CaptainComission.ShipName2);
			AddQuestUserData("CaptainComission1", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.Island.Shore + "Abl"));
			AddQuestUserData("CaptainComission1", "sShoreType", XI_ConvertString(GetIslandByArealName(pchar.GenQuest.CaptainComission.Island) + "Dat"));
			pchar.quest.CapComission_PirateAttack.win_condition.l1 = "location";
            pchar.quest.CapComission_PirateAttack.win_condition.l1.location = pchar.GenQuest.CaptainComission.Island;
            pchar.quest.CapComission_PirateAttack.function = "CaptainComission_GeneratePirateShips"; 
			SetFunctionTimerCondition("CaptainComission_PirateShipsOver", 0, 0, 15, false);	
			pchar.GenQuest.CaptainComission.PirateShips = "goaway";	
		break;
		
		case "CapComission2_3":
			dialog.text = "Ne t'inquiète pas. Mes hommes le livreront à ton navire. Et pourquoi t'en soucies-tu?";
			link.l1 = "Je ne le fais pas. Ses proches m'ont demandé de le livrer.";
			link.l1.go = "CapComission2_31";
		break;
		
		case "CapComission2_31":
			dialog.text = "Ah, c'est bien. J'étais presque désolé d'offrir un prix si bas pour ton homme. Ha-ha-ha-ha. Adieu.";
			link.l1 = "À bientôt.";
			link.l1.go = "exit";
			AddQuestRecord("CaptainComission1", "9");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City));			
			addMoneyToCharacter(pchar, -150000);
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");	
		break;
		
		case "CapComission3":
			dialog.text = "Eh bien, "+GetFullName(pchar)+", as-tu coulé mon pote ? He-he-he...";
			if(pchar.GenQuest.CaptainComission.PirateShips == "goaway")
			{
				link.l1 = "Non. Je n'ai pas réussi à les attraper. Et je ne les ai pas rencontrés à leur retour.";
				link.l1.go = "CapComission4";
			}
			else
			{
				if(pchar.GenQuest.CaptainComission.PirateShips == "died")	
				{
					link.l1 = "Je l'ai fait. Je les ai envoyés nourrir les requins.";
					link.l1.go = "CapComission5";
				}
			}	
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
		break;
		
		case "CapComission4":
			dialog.text = "Merde ! Quoi qu'il en soit, ça n'a pas d'importance maintenant ! Quelle sera ta prochaine suggestion ?";
			link.l1 = "Peut-être que tu as un boulot plus facile pour moi ?";
			link.l1.go = "CapComission4_1";
			link.l2 = "Ecoute, "+NPChar.name+", fais baisser le prix pour le prisonnier...";
			link.l2.go = "CapComission4_2";
		break;
		
		case "CapComission4_1":
			dialog.text = "Non.";
			link.l1 = "Adieu alors...";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			AddQuestRecord("CaptainComission1", "27");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_DAT));
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");			
		break;
		
		case "CapComission4_2":
			dialog.text = "Faire baisser le prix ?! Je viens de perdre mon magot à cause de ton incompétence ! Maintenant, je peux augmenter le prix ! Tu peux le prendre pour 200.000 pesos si tu veux, ou tu peux foutre le camp d'ici !";
			link.l1 = "C'est trop cher... Adieu...";
			link.l1.go = "CapComission4_4";
			if(sti(pchar.money) >= 200000)
			{
				link.l2 = "Merde, très bien, prends ta pièce.";
				link.l2.go = "CapComission4_5";
			}	
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
			dialog.text = "Tu peux prendre ce faible...";
			link.l1 = "Adieu.";
			link.l1.go = "exit";
			addMoneyToCharacter(pchar, -200000);
			AddQuestRecord("CaptainComission1", "29");
			AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			pchar.GenQuest.CaptainComission.SlaveAddMoney = true;
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");	
		break;
				
		case "CapComission5":
			dialog.text = "Ho-ho ! Bien joué ! Prends ton gringalet et bonne chance.";
			link.l1 = "Merci. Adieu.";
			link.l1.go = "exit";
			AddQuestRecord("CaptainComission1", "34");
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");
		break;
				
		case "CapComission6":
			dialog.text = "As-tu apporté l'argent, Charles ? Je ne plaisantais pas en parlant de vendre cet homme à la plantation";			
			link.l1 = "Écoute, "+NPChar.name+", il y a un problème... Je n'ai pas autant d'argent. Mais je suis prêt à travailler.";
			link.l1.go = "CapComission2_2";
			if(makeint(pchar.money) > 150000)
			{
				link.l2 = "C'est bien que tu ne l'aies pas vendu. Voici tes pièces - 150.000 pesos. Où puis-je le trouver ?"link.l2.go ="CapComission2_3";
			}			
		break;
		
		//Захват пассажиров
		case "Marginpassenger":
			dialog.text = "Et pourquoi te soucies-tu de ce que je fais ? Tu sais, tu ferais mieux de t'en aller...";
			link.l1 = "Tshh, calme-toi. J'ai une proposition d'affaire pour toi. Cela concerne ton prisonnier.";
			link.l1.go = "Marginpassenger_1";
		break;
		
		case "Marginpassenger_1":
			dialog.text = "Ah, très bien. Qui veux-tu rançonner ?";
			link.l1 = "Attends. Je ne suis pas ici pour racheter, je suis ici pour te proposer d'acheter un prisonnier. Eh bien, et tu auras l'occasion de recevoir une rançon pour lui.";
			link.l1.go = "Marginpassenger_2";
		break;
		
		case "Marginpassenger_2":
			dialog.text = "Hm. Et pourquoi as-tu besoin de mon intercession? Ne veux-tu pas recevoir l'argent directement pour toi-même?";
			link.l1 = "C'est assez risqué pour moi. Je pourrais avoir des ennuis avec les autorités.";
			link.l1.go = "Marginpassenger_3";
		break;
		
		case "Marginpassenger_3":
			dialog.text = "Ha-h... très bien alors. Jetons un coup d'œil. Qui est ton prisonnier ?";
			link.l1 = "C'est "+pchar.GenQuest.Marginpassenger.Text+" "+XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.City+"Gen")+".";
			link.l1.go = "Marginpassenger_4";
		break;
		
		case "Marginpassenger_4":
			int iTemp = makeint(sti(pchar.GenQuest.Marginpassenger.Dublon)*2*stf(pchar.GenQuest.Marginpassenger.Chance))*100;
			dialog.text = "Je vois. Ce serait un bon marché si tu ne mens pas. Je suppose que je peux te payer pour cet homme, "+iTemp+" pesos, ou te donner quelques informations intéressantes à la place. C'est ton choix.";
			link.l1 = "Je ferais mieux de prendre la piastre. J'en ai assez de cette affaire...";
			link.l1.go = "Marginpassenger_money";
			link.l2 = "Ha! Dis m'en plus. Je suis sûr que tu m'offriras quelque chose d'intéressant.";
			link.l2.go = "Marginpassenger_offer";
		break;
		
		case "Marginpassenger_money":
			dialog.text = "De l'argent alors. Prends-les. Maintenant, ce n'est plus ton problème. Livre le sujet de la vente ici.";
			link.l1 = "Il doit déjà être près des portes de la ville. Merci ! Tu m'as vraiment aidé.";
			link.l1.go = "Marginpassenger_money_1";
		break;
		
		case "Marginpassenger_money_1":
			iTemp = makeint(sti(pchar.GenQuest.Marginpassenger.Dublon)*2*stf(pchar.GenQuest.Marginpassenger.Chance))*100;
			dialog.text = "De rien, apporte-m'en plus... À plus tard !";
			link.l1 = "Bonne chance...";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, iTemp);
			ref sld = characterFromId("MarginPass");
			RemovePassenger(Pchar, sld);
			sld.lifeday = 0;
			AddQuestRecord("Marginpassenger", "12");
			AddQuestUserData("Marginpassenger", "sSum", iTemp);
			CloseQuestHeader("Marginpassenger");
			DeleteAttribute(Pchar, "GenQuest.Marginpassenger");
		break;
		
		case "Marginpassenger_offer":
			pchar.GenQuest.Marginpassenger.Goods = GetRandomGood(FLAG_GOODS_TYPE_EXPORT + FLAG_GOODS_TYPE_UNIQUE, FLAG_GOODS_VALUABLE_WOOD);
			pchar.GenQuest.Marginpassenger.GoodsQty = 200+rand(10)*10;
			switch (hrand(1))
			{
				case 0: //бухта на южном мейне
					SelectSouthshore();
					while (!isLocationFreeForQuests(pchar.GenQuest.Marginpassenger.Shore)) SelectSouthshore();
					dialog.text = "C'est bon de faire affaire avec un homme intelligent. Maintenant, écoute : dans quelques jours à "+XI_ConvertString(pchar.GenQuest.Marginpassenger.Shore+"Ca")+" une expédition espagnole arrivera du continent, chargée de marchandises précieuses. Ils attendront un navire censé prendre la cargaison. Si tu arrives là-bas dans une semaine, tu auras une chance de prendre la cargaison pour toi.\nSi j'étais toi, je serais déjà en train de me diriger vers mon navire. Et amène le prisonnier ici.";
					link.l1 = "Merci ! Les marchandises seront une belle compensation pour mes ennuis. Et mon passager doit déjà être près des portes de la ville. Il sera amené à vous.";
					link.l1.go = "Marginpassenger_offer_1";
				break;
				
				case 1: //просто кораблик
					SelectSouthcity();
					pchar.GenQuest.Marginpassenger.ShipName1 = GenerateRandomNameToShip(SPAIN);
					dialog.text = "C'est bon de faire affaire avec un homme intelligent. Maintenant écoute : dans environ une semaine, un brigantin espagnol '"+pchar.GenQuest.Marginpassenger.ShipName1+"chargé de marchandises précieuses partira de "+XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Southcity+"Gén")+" à "+XI_ConvertString("Colonie"+pchar.GenQuest.Marginpassenger.Southcity1+"Gén")+".  Si tu te dépêches, tu l'attraperas facilement.\nTu es encore là ? Si j'étais toi, je serais déjà en train de me diriger vers mon navire. Et amène le prisonnier ici.";
					link.l1 = "Merci! Les marchandises seront une belle compensation pour mes ennuis. Et mon passager doit être près des portes de la ville. Il sera amené à toi.";
					link.l1.go = "Marginpassenger_offer_2";
				break;
			}
			sld = characterFromId("MarginPass");
			RemovePassenger(Pchar, sld);
			sld.lifeday = 0;
			pchar.GenQuest.Marginpassenger = "final";
		break;
		
		case "Marginpassenger_offer_1":
			DialogExit();
			AddQuestRecord("Marginpassenger", "13");
			AddQuestUserData("Marginpassenger", "sShore", XI_ConvertString(pchar.GenQuest.Marginpassenger.Shore+"Dat"));
			SetFunctionTimerCondition("Marginpassenger_SouthshoreOver", 0, 0, 7, false);
			pchar.quest.Marginpassenger.win_condition.l1 = "location";
			pchar.quest.Marginpassenger.win_condition.l1.location = pchar.GenQuest.Marginpassenger.Shore;
			pchar.quest.Marginpassenger.function = "Marginpassenger_Southshore";
		break;
		
		case "Marginpassenger_offer_2":
			DialogExit();
			AddQuestRecord("Marginpassenger", "16");
			AddQuestUserData("Marginpassenger", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Southcity+"Gen"));
			AddQuestUserData("Marginpassenger", "sCity1", XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Southcity1+"Gen"));
			AddQuestUserData("Marginpassenger", "sShipName", pchar.GenQuest.Marginpassenger.ShipName1);
			SetFunctionTimerCondition("Marginpassenger_SouthshipInWorld", 0, 0, 5+rand(2), false);
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

void SelectSouthshore()
{
	switch (rand(6))
	{
		case 0: pchar.GenQuest.Marginpassenger.Shore = "shore37"; break;
		case 1: pchar.GenQuest.Marginpassenger.Shore = "shore47"; break;
		case 2: pchar.GenQuest.Marginpassenger.Shore = "shore48"; break;
		case 3: pchar.GenQuest.Marginpassenger.Shore = "shore25"; break;
		case 4: pchar.GenQuest.Marginpassenger.Shore = "shore21"; break;
		case 5: pchar.GenQuest.Marginpassenger.Shore = "shore20"; break;
		case 6: pchar.GenQuest.Marginpassenger.Shore = "shore19"; break;
	}
}

void SelectSouthcity()
{
	switch (hrand(2))
	{
		case 0: 
			pchar.GenQuest.Marginpassenger.Southcity = "Maracaibo";
			pchar.GenQuest.Marginpassenger.Southcity1 = "Havana"; 
		break;
		
		case 1:
			pchar.GenQuest.Marginpassenger.Southcity = "Cartahena";
			pchar.GenQuest.Marginpassenger.Southcity1 = "Santiago"; 
		break;
		
		case 2:
			pchar.GenQuest.Marginpassenger.Southcity = "Portobello";
			pchar.GenQuest.Marginpassenger.Southcity1 = "Santodomingo"; 
		break;
	}
}
