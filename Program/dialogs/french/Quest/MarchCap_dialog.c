void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp, iQty;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Un bogue. Assurez-vous de le dire aux développeurs.";
			link.l1 = "D'accord.";
			link.l1.go = "exit";
		break;
		
		//разговор на палубе
		case "MarchCap":
			pchar.quest.MarchCapOver.over = "yes"; //снять прерывание
			dialog.text = "Vous y voilà, capitaine. Discutons des détails de mon offre. Vous comprendrez pourquoi je ne voulais pas en parler en public.";
			link.l1 = "Continuez, monsieur. J'écoute.";
			link.l1.go = "MarchCap_1";
		break;
		
		case "MarchCap_1":
			pchar.GenQuest.MarchCap.Goods = SelectMarchCapGoods1();//целевой товар
			switch (rand(2))
			{
				case 0: //конвой у острова, установка параметров
					pchar.GenQuest.MarchCap.Island = GetRandomIslandId();
					while(pchar.GenQuest.MarchCap.Island == pchar.GenQuest.MarchCap.Startisland)
					{
						pchar.GenQuest.MarchCap.Island = GetRandomIslandId();
					}
					pchar.GenQuest.MarchCap.Island.Shore = GetIslandRandomShoreId(pchar.GenQuest.MarchCap.Island);
					while(pchar.GenQuest.MarchCap.Island.Shore == "")
					{
						pchar.GenQuest.MarchCap.Island = GetRandomIslandId();
						pchar.GenQuest.MarchCap.Island.Shore = GetIslandRandomShoreId(pchar.GenQuest.MarchCap.Island);
						if (!isLocationFreeForQuests(pchar.GenQuest.MarchCap.Island) || !isLocationFreeForQuests(pchar.GenQuest.MarchCap.Island.Shore)) pchar.GenQuest.MarchCap.Island.Shore = "";
					}
					pchar.GenQuest.MarchCap.DaysQty = GetMaxDaysFromIsland2Island(pchar.GenQuest.MarchCap.Startisland, pchar.GenQuest.MarchCap.Island)+3;
					dialog.text = "J'ai réussi à découvrir que dans "+FindRussianDaysString(sti(pchar.GenQuest.MarchCap.DaysQty))+" un petit convoi de commerce sous le pavillon de "+NationNameGenitive(sti(pchar.GenQuest.MarchCap.Nation))+", deux navires marchands et un navire de garde, navigueront près de "+XI_ConvertString(pchar.GenQuest.MarchCap.Island.Shore+"Gen")+", ce n'est pas loin de "+XI_ConvertString(pchar.GenQuest.MarchCap.Island+"Gen")+"Les marchands ont beaucoup de "+GetGoodsNameAlt(sti(pchar.GenQuest.MarchCap.Goods))+" dans leurs cales. Ce serait idiot de ne pas utiliser cette information, capitaine\nVous et moi pouvons facilement nous occuper des gardes et prendre la cargaison pour nous-mêmes. Alors, vous êtes partant ?";
					link.l1 = "Ça sonne tentant. Je dirais oui !";
					link.l1.go = "MarchCap_1_1";
					link.l2 = "Quelques-uns"+GetGoodsNameAlt(sti(pchar.GenQuest.MarchCap.Goods))+" n'est pas suffisant pour moi pour gâcher mes relations avec "+NationNameAblative(sti(pchar.GenQuest.MarchCap.Nation))+"Non, je ne vais pas faire cela ! Adieu, monsieur, et n'essayez même pas de m'arrêter !";
					link.l2.go = "MarchCap_exit";
				break;
				
				case 1: //энкаунтер на глобалке, установка параметров
					pchar.GenQuest.MarchCap.Startcity = SelectAnyColony(pchar.GenQuest.MarchCap.basecity);
					pchar.GenQuest.MarchCap.Finishcity = SelectAnyColony2(pchar.GenQuest.MarchCap.basecity, pchar.GenQuest.MarchCap.Startcity);
					pchar.GenQuest.MarchCap.DaysQty = 5+hrand(5);
					dialog.text = "J'ai réussi à découvrir que dans "+FindRussianDaysString(sti(pchar.GenQuest.MarchCap.DaysQty))+" un petit convoi marchand sous le pavillon de "+NationNameGenitive(sti(pchar.GenQuest.MarchCap.Nation))+", deux navires marchands et un navire de garde, vont partir de "+XI_ConvertString("Colony"+pchar.GenQuest.MarchCap.Startcity+"Gén")+" à "+XI_ConvertString("Colony"+pchar.GenQuest.MarchCap.Finishcity+"Acc")+" Les marchands ont beaucoup de "+GetGoodsNameAlt(sti(pchar.GenQuest.MarchCap.Goods))+" dans leurs cales. Ce serait idiot de ne pas utiliser cette information, capitaine.\nVous et moi pouvons facilement nous occuper des gardes et prendre la cargaison pour nous. Le plus difficile est de les trouver en pleine mer entre ces deux colonies. Alors, vous êtes partant ?";
					link.l1 = "Cela semble tentant. Je dirais oui!";
					link.l1.go = "MarchCap_2_1";
					link.l2 = "Certain "+GetGoodsNameAlt(sti(pchar.GenQuest.MarchCap.Goods))+" n'est pas suffisant pour que je gache mes relations avec "+NationNameAblative(sti(pchar.GenQuest.MarchCap.Nation))+"Non, je ne vais pas faire cela ! Adieu, monsieur, et n'essayez même pas de m'arrêter !";
					link.l2.go = "MarchCap_exit";
				break;
				
				case 2: //одиночный пиратский кулсейлор у бухты, установка параметров
					pchar.GenQuest.MarchCap.Goods = GOOD_GOLD + hrand(makeint(GOOD_SILVER - GOOD_GOLD));
					pchar.GenQuest.MarchCap.GoodsQty = sti(pchar.rank)*50+170+rand(30);
					if (sti(pchar.GenQuest.MarchCap.GoodsQty) > 1600) pchar.GenQuest.MarchCap.GoodsQty = 1500+rand(100);
					pchar.GenQuest.MarchCap.Island = GetRandomIslandId();
					while(pchar.GenQuest.MarchCap.Island == pchar.GenQuest.MarchCap.Startisland)
					{
						pchar.GenQuest.MarchCap.Island = GetRandomIslandId();
					}
					pchar.GenQuest.MarchCap.Island.Shore = GetIslandRandomShoreId(pchar.GenQuest.MarchCap.Island);
					while(pchar.GenQuest.MarchCap.Island.Shore == "")
					{
						pchar.GenQuest.MarchCap.Island = GetRandomIslandId();
						pchar.GenQuest.MarchCap.Island.Shore = GetIslandRandomShoreId(pchar.GenQuest.MarchCap.Island);
						if (!isLocationFreeForQuests(pchar.GenQuest.MarchCap.Island) || !isLocationFreeForQuests(pchar.GenQuest.MarchCap.Island.Shore)) pchar.GenQuest.MarchCap.Island.Shore = "";
					}
					pchar.GenQuest.MarchCap.DaysQty = GetMaxDaysFromIsland2Island(pchar.GenQuest.MarchCap.Startisland, pchar.GenQuest.MarchCap.Island)+1;
					pchar.GenQuest.MarchCap.PirateName = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);//пират
					pchar.GenQuest.MarchCap.ShipType = SelectPirateShipType();
					pchar.GenQuest.MarchCap.Cannon = SelectLevelCannonParameter(sti(pchar.GenQuest.MarchCap.ShipType));
					dialog.text = "On m'a informé d'un pirate nommé "+GetName(NAMETYPE_ORIG,pchar.GenQuest.MarchCap.PirateName,NAME_NOM)+"Ce bandit a récemment chapardé "+RandPhraseSimple(RandPhraseSimple("Anglais","Français"),RandPhraseSimple("Espagnol","Neerlandais"))+" et a chargé sa cale de "+GetGoodsNameAlt(sti(pchar.GenQuest.MarchCap.Goods))+". Mais, quel dommage, son navire "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.MarchCap.ShipType),"Nom")+"Accord"))+" fut gravement endommagé, il dut donc prendre le temps de la réparer.\nIl est actuellement à "+XI_ConvertString(pchar.GenQuest.MarchCap.Island.Shore+"Général")+" de "+XI_ConvertString(pchar.GenQuest.MarchCap.Island+"Gen")+". Je pense que cela prendra environ "+FindRussianDaysString(sti(pchar.GenQuest.MarchCap.DaysQty))+" pour qu'il répare les mâts et les trous dans la coque. Nous pouvons y arriver à temps si nous nous dépêchons et que tout le monde "+GetGoodsNameAlt(sti(pchar.GenQuest.MarchCap.Goods))+" sera à nous\nJe ne pourrai pas affronter ce pirate seul, c'est un très bon marin et combattant, mais à deux, nous pourrons le défier avec succès malgré son expérience. Alors, tu es partant ou pas?";
					link.l1 = "Ça semble tentant. Je dirais oui !";
					link.l1.go = "MarchCap_3_1";
					link.l2 = "Hm. Il semblerait que ce prix soit hors de portée non seulement pour toi mais pour nous deux. Non, je ne vais pas faire cela, adieu, monsieur, et n'essayez même pas de m'arrêter !";
					link.l2.go = "MarchCap_exit";
				break;
			}
		break;
		
		case "MarchCap_1_1":
			dialog.text = "Je savais que je pouvais compter sur toi ! Ne perdons pas une seule minute. Va à ton navire et prends la tête, je te suivrai. Il est temps de prendre la mer !";
			link.l1 = "Ordre de lever l'ancre, capitaine !";
			link.l1.go = "MarchCap_1_2";
		break;
		
		case "MarchCap_1_2":
			DialogExit();
			NextDiag.CurrentNode = "MarchCap_repeat";
			Group_DelCharacter("MarchGroup", "MarchCap");
			SetCompanionIndex(pchar, -1, sti(npchar.index));
			npchar.loyality = MAX_LOYALITY;
			SetCharacterRemovable(npchar, false);
			Character_SetAbordageEnable(npchar, false);
			npchar.Tasks.CanBoarding = false; // запрет идти на абордаж // Addon 2016-1 Jason Пиратская линейка
			pchar.quest.MarchCap1_1.win_condition.l1 = "Timer";
			pchar.quest.MarchCap1_1.win_condition.l1.date.hour  = sti(GetTime()+rand(10));
			pchar.quest.MarchCap1_1.win_condition.l1.date.day   = GetAddingDataDay(0, 0, sti(pchar.GenQuest.MarchCap.DaysQty));
			pchar.quest.MarchCap1_1.win_condition.l1.date.month = GetAddingDataMonth(0, 0, sti(pchar.GenQuest.MarchCap.DaysQty));
			pchar.quest.MarchCap1_1.win_condition.l1.date.year  = GetAddingDataYear(0, 0, sti(pchar.GenQuest.MarchCap.DaysQty));
			pchar.quest.MarchCap1_1.win_condition.l2 = "location";
			pchar.quest.MarchCap1_1.win_condition.l2.location = pchar.GenQuest.MarchCap.Island;
			pchar.quest.MarchCap1_1.function = "MarchCap1_CreateConvoy";
			SetFunctionTimerCondition("MarchCap_Attack_Over", 0, 0, sti(pchar.GenQuest.MarchCap.DaysQty)+2, false); //таймер на нахождение
			pchar.quest.MarchCap1_fail.win_condition.l1 = "NPC_Death";
			pchar.quest.MarchCap1_fail.win_condition.l1.character = "MarchCap";
			pchar.quest.MarchCap1_fail.function = "MarchCap_fail";
			ReOpenQuestHeader("MarchCap");
			AddQuestRecord("MarchCap", "1");
			AddQuestUserData("MarchCap", "sShore", XI_ConvertString(pchar.GenQuest.MarchCap.Island.Shore+"Gen"));
			AddQuestUserData("MarchCap", "sIsland", XI_ConvertString(pchar.GenQuest.MarchCap.Island+"Gen"));
			AddQuestUserData("MarchCap", "sDays", FindRussianDaysString(sti(pchar.GenQuest.MarchCap.DaysQty)));
			AddQuestUserData("MarchCap", "sGoods", GetGoodsNameAlt(sti(pchar.GenQuest.MarchCap.Goods)));
			AddQuestUserData("MarchCap", "sName", GetFullName(npchar));
		break;
		
		case "MarchCap_TimeOver":
			dialog.text = "Et pourquoi me suis-je embarqué avec vous, capitaine ? Nous avons perdu un prix si précieux à cause de vous ! Je ferais mieux de naviguer seul la prochaine fois...";
			link.l1 = "Ta faute, pas la mienne. Adieu.";
			link.l1.go = "MarchCap_Talk_exit";
			pchar.GenQuest.MarchCap = "late";
		break;
		
		case "MarchCap_Talk_exit":
			pchar.quest.MarchCap1_fail2.over = "yes"; //снять прерывание
			pchar.quest.MarchCap1_fail1.over = "yes"; //снять прерывание
			pchar.quest.MarchCap1_fail.over = "yes"; //снять прерывание
			DialogExit();
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 10.0);
			DeleteAttribute(npchar, "AlwaysFriend");
			npchar.DontDeskTalk = true;
			if (CheckAttribute(pchar, "GenQuest.MarchCap.Deck"))
			{
				PChar.quest.Munity = "Deads";
				LAi_LocationFightDisable(&Locations[FindLocation("Ship_deck")], false);
			}
			else
			{
				LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
				chrDisableReloadToLocation = false;
			}
			RemoveCharacterCompanion(pchar, npchar);
			npchar.location = pchar.location;
			if (pchar.GenQuest.MarchCap == "late") AddQuestRecord("MarchCap", "2");
			if (pchar.GenQuest.MarchCap == "bad") AddQuestRecord("MarchCap", "5");
			if (pchar.GenQuest.MarchCap == "poor" || pchar.GenQuest.MarchCap == "good" || pchar.GenQuest.MarchCap == "exellent")
			{
				iQty = makeint(GetSquadronGoods(pchar, sti(pchar.GenQuest.MarchCap.Goods))-sti(pchar.GenQuest.MarchCap.StartGoodsQty));
				iTemp = iQty-sti(pchar.GenQuest.MarchCap.CapPart);
				RemoveCharacterGoods(pchar, sti(pchar.GenQuest.MarchCap.Goods), iQty);
				AddCharacterGoods(pchar, sti(pchar.GenQuest.MarchCap.Goods), iTemp);
				if (pchar.GenQuest.MarchCap == "poor") AddQuestRecord("MarchCap", "6");
				if (pchar.GenQuest.MarchCap == "good") AddQuestRecord("MarchCap", "7");
				if (pchar.GenQuest.MarchCap == "exellent") AddQuestRecord("MarchCap", "8");
			}
			AddQuestUserData("MarchCap", "sName", GetFullName(npchar));
			CloseQuestHeader("MarchCap");
			DeleteAttribute(pchar, "GenQuest.MarchCap");
		break;
		
		case "MarchCap_AfterBattle":
			iTemp = makeint(GetSquadronGoods(pchar, sti(pchar.GenQuest.MarchCap.Goods))-sti(pchar.GenQuest.MarchCap.StartGoodsQty))*sti(Goods[sti(pchar.GenQuest.MarchCap.Goods)].Weight);
			iQty = makeint(GetSquadronGoods(pchar, sti(pchar.GenQuest.MarchCap.Goods))-sti(pchar.GenQuest.MarchCap.StartGoodsQty));
			pchar.GenQuest.MarchCap.CapPart = iQty/sti(pchar.GenQuest.MarchCap.Parts);
			if (iTemp < 50)
			{
				dialog.text = "Tu es vraiment un raté, capitaine ! On n'a rien eu ! Et tout ça, c'est à cause de toi ! Tu es la raison de notre échec, que le diable t'emporte !";
				link.l1 = "Suis-je? Regarde-toi! Tu ne m'as pas aidé dans la bataille! J'ai juste perdu mon temps avec toi... Sors de mon navire!";
				link.l1.go = "MarchCap_Talk_exit";
				pchar.GenQuest.MarchCap = "bad";
				break;
			}
			if (iTemp > 50 && iTemp < 500)
			{
				dialog.text = "Eh bien, ce raid n'a pas été aussi réussi que je l'espérais, notre prise est vraiment modeste... Qu'importe, capitaine, partageons ces miettes et disons-nous adieu.";
				link.l1 = "Si tu m'avais aidé au lieu de compter les oiseaux dans le ciel, le raid aurait été un succès... Prends ta part - "+FindRussianQtyString(sti(pchar.GenQuest.MarchCap.CapPart))+" et va te faire foutre !";
				link.l1.go = "MarchCap_Talk_exit";
				pchar.GenQuest.MarchCap = "poor";
				break;
			}
			if (iTemp > 500 && iTemp < 1500)
			{
				dialog.text = "Bien joué, capitaine ! Comme je l'ai dit - il était plutôt facile de vider les cales de ces marchands, ha-ha... Le butin est "+FindRussianQtyString(iQty)+" pièces. Ma part est "+FindRussianQtyString(sti(pchar.GenQuest.MarchCap.CapPart))+".";
				link.l1 = "C'est correct, "+npchar.name+"Je n'ai aucune objection. Les chaloupes sont en train d'être chargées en ce moment. Peut-être que nous ferons une autre razzia ensemble à l'avenir ? Tu sembles être un compagnon convenable pour moi.";
				link.l1.go = "MarchCap_Talk_exit";
				pchar.GenQuest.MarchCap = "good";
				break;
			}
			dialog.text = "Excellent, capitaine ! Comme je l'ai dit - il était relativement facile de vider les cales de ces marchands, ha-ha... La prise est énorme, bien plus que ce que j'avais espéré. C'est "+FindRussianQtyString(iQty)+" pièces. Ma part est "+FindRussianQtyString(sti(pchar.GenQuest.MarchCap.CapPart))+".";
			link.l1 = "C'est correct, "+npchar.name+". Je n'ai pas d'objections. Les chaloupes sont en cours de chargement en ce moment. Peut-être ferons-nous un autre raid ensemble à l'avenir ? Vous semblez être un compagnon convenable pour moi.";
			link.l1.go = "MarchCap_Deck_continue";
			pchar.GenQuest.MarchCap = "exellent";
		break;
		
		//если будет время - здесь создаем еще одного клона с уникальным ИД для продолжения квеста
		case "MarchCap_Deck_continue":
			dialog.text = "Il y a une possibilité, capitaine. Je vous trouverai si je reçois un autre indice profitable que je ne pourrai pas exploiter seul. Vous semblez être un compagnon de bataille fiable pour moi aussi.";
			link.l1 = "Chouette ! Adieu, capitaine. Bonne chance !";
			link.l1.go = "MarchCap_Talk_exit";
		break;
		
		case "MarchCap_2_1":
			dialog.text = "Je savais que je pouvais compter sur toi! Ne perdons pas une seule minute. Va à ton navire et prends les commandes, je suivrai. Il est temps de prendre la mer!";
			link.l1 = "Ordre de lever l'ancre, capitaine.";
			link.l1.go = "MarchCap_2_2";
		break;
		
		case "MarchCap_2_2":
			DialogExit();
			NextDiag.CurrentNode = "MarchCap_repeat";
			Group_DelCharacter("MarchGroup", "MarchCap");
			SetCompanionIndex(pchar, -1, sti(npchar.index));
			npchar.loyality = MAX_LOYALITY;
			SetCharacterRemovable(npchar, false);
			Character_SetAbordageEnable(npchar, false);
			npchar.Tasks.CanBoarding = false; // запрет идти на абордаж // Addon 2016-1 Jason Пиратская линейка
			pchar.quest.MarchCap1_1.win_condition.l1 = "Timer";
			pchar.quest.MarchCap1_1.win_condition.l1.date.hour  = sti(GetTime()+rand(10));
			pchar.quest.MarchCap1_1.win_condition.l1.date.day   = GetAddingDataDay(0, 0, sti(pchar.GenQuest.MarchCap.DaysQty));
			pchar.quest.MarchCap1_1.win_condition.l1.date.month = GetAddingDataMonth(0, 0, sti(pchar.GenQuest.MarchCap.DaysQty));
			pchar.quest.MarchCap1_1.win_condition.l1.date.year  = GetAddingDataYear(0, 0, sti(pchar.GenQuest.MarchCap.DaysQty));
			pchar.quest.MarchCap1_1.function = "MarchCap2_CreateConvoy";
			pchar.GenQuest.MarchCap.WdmEnc = "true";
			pchar.quest.MarchCap1_fail.win_condition.l1 = "NPC_Death";
			pchar.quest.MarchCap1_fail.win_condition.l1.character = "MarchCap";
			pchar.quest.MarchCap1_fail.function = "MarchCap_fail";
			ReOpenQuestHeader("MarchCap");
			AddQuestRecord("MarchCap", "10");
			AddQuestUserData("MarchCap", "sCity1", XI_ConvertString("Colony"+pchar.GenQuest.MarchCap.Startcity+"Gen"));
			AddQuestUserData("MarchCap", "sCity2", XI_ConvertString("Colony"+pchar.GenQuest.MarchCap.Finishcity+"Acc"));
			AddQuestUserData("MarchCap", "sDays", FindRussianDaysString(sti(pchar.GenQuest.MarchCap.DaysQty)));
			AddQuestUserData("MarchCap", "sGoods", GetGoodsNameAlt(sti(pchar.GenQuest.MarchCap.Goods)));
			AddQuestUserData("MarchCap", "sName", GetFullName(npchar));
		break;
		
		case "MarchCap_3_1":
			dialog.text = "Je savais que je pouvais compter sur toi ! Ne perdons pas une seule minute. Va à ton navire et mène-moi. Il est temps de lever l'ancre !";
			link.l1 = "Ordre de lever l'ancre, capitaine.";
			link.l1.go = "MarchCap_3_2";
		break;
		
		case "MarchCap_3_2":
			DialogExit();
			NextDiag.CurrentNode = "MarchCap_repeat";
			Group_DelCharacter("MarchGroup", "MarchCap");
			SetCompanionIndex(pchar, -1, sti(npchar.index));
			npchar.loyality = MAX_LOYALITY;
			SetCharacterRemovable(npchar, false);
			Character_SetAbordageEnable(npchar, false);
			npchar.Tasks.CanBoarding = false; // запрет идти на абордаж // Addon 2016-1 Jason Пиратская линейка
			pchar.quest.MarchCap1_1.win_condition.l1 = "location";
			pchar.quest.MarchCap1_1.win_condition.l1.location = pchar.GenQuest.MarchCap.Island;
			pchar.quest.MarchCap1_1.function = "MarchCap3_CreatePirate";
			SetFunctionTimerCondition("MarchCap_Attack_Over", 0, 0, sti(pchar.GenQuest.MarchCap.DaysQty), false); //таймер
			pchar.quest.MarchCap1_fail.win_condition.l1 = "NPC_Death";
			pchar.quest.MarchCap1_fail.win_condition.l1.character = "MarchCap";
			pchar.quest.MarchCap1_fail.function = "MarchCap_fail";
			pchar.GenQuest.MarchCap.Pirate = "true";
			ReOpenQuestHeader("MarchCap");
			AddQuestRecord("MarchCap", "11");
			AddQuestUserData("MarchCap", "sShore", XI_ConvertString(pchar.GenQuest.MarchCap.Island.Shore+"Gen"));
			AddQuestUserData("MarchCap", "sIsland", XI_ConvertString(pchar.GenQuest.MarchCap.Island+"Gen"));
			AddQuestUserData("MarchCap", "sDays", FindRussianDaysString(sti(pchar.GenQuest.MarchCap.DaysQty)));
			AddQuestUserData("MarchCap", "sGoods", GetGoodsNameAlt(sti(pchar.GenQuest.MarchCap.Goods)));
			AddQuestUserData("MarchCap", "sName", GetFullName(npchar));
			AddQuestUserData("MarchCap", "sName1", GetName(NAMETYPE_ORIG, pchar.GenQuest.MarchCap.PirateName, NAME_NOM));
		break;
		
		case "MarchCap_DieHard":
			dialog.text = "Tu es un lâche, maudit sois-tu ! Tu viens de fuir le champ de bataille !";
			link.l1 = "Et que crois-tu que j'étais censé faire ? Laisser ce pirate couler mon navire ? Pas question, je préfère être un lâche vivant qu'un idiot mort !";
			link.l1.go = "MarchCap_DieHard_1";
		break;
		
		case "MarchCap_DieHard_1":
			dialog.text = "Et pourquoi me suis-je impliqué avec vous, capitaine? J'aurais dû trouver un homme qui ne craint pas les sabres lors des abordages!";
			link.l1 = " Maintenant, je vous demande de quitter mon navire - je dois la réparer.";
			link.l1.go = "MarchCap_Talk_exit";
		break;
		
		case "MarchCap_AfterBattleGold":
			iTemp = makeint(GetSquadronGoods(pchar, sti(pchar.GenQuest.MarchCap.Goods))-sti(pchar.GenQuest.MarchCap.StartGoodsQty))*sti(Goods[sti(pchar.GenQuest.MarchCap.Goods)].Weight);
			iQty = makeint(GetSquadronGoods(pchar, sti(pchar.GenQuest.MarchCap.Goods))-sti(pchar.GenQuest.MarchCap.StartGoodsQty));
			pchar.GenQuest.MarchCap.CapPart = iQty/sti(pchar.GenQuest.MarchCap.Parts);
			if (iTemp < 10)
			{
				dialog.text = "Tu es un tel perdant, capitaine ! Nous n'avons pas récupéré une seule parcelle de notre butin ! Et tout cela à cause de toi ! Tu es la raison de notre échec, maudit sois-tu !";
				link.l1 = "Suis-je? Regarde-toi ! Tu ne m'as pas aidé dans la bataille ! J'ai juste perdu mon temps avec toi... Sors de mon navire !";
				link.l1.go = "MarchCap_Talk_exit";
				pchar.GenQuest.MarchCap = "bad";
				break;
			}
			if (iTemp > 10 && iTemp < 100)
			{
				dialog.text = "Eh bien, ce raid n'a pas été aussi réussi que je l'avais espéré, notre butin est vraiment modeste... Qu'importe, capitaine, partageons ces miettes et disons-nous adieu.";
				link.l1 = "Si tu m'aidais au lieu de compter les oiseaux dans le ciel, le raid aurait été un succès... Prends ta part - "+FindRussianQtyString(sti(pchar.GenQuest.MarchCap.CapPart))+" et fiche le camp !";
				link.l1.go = "MarchCap_Talk_exit";
				pchar.GenQuest.MarchCap = "poor";
				break;
			}
			if (iTemp > 100 && iTemp < 500)
			{
				dialog.text = "Bien joué, capitaine ! Le butin est "+FindRussianQtyString(iQty)+"  pieces. Ma part est "+FindRussianQtyString(sti(pchar.GenQuest.MarchCap.CapPart))+".";
				link.l1 = "C'est correct, "+npchar.name+"Je n'ai pas d'objections. Les chaloupes sont en cours de chargement à l'instant. Peut-être que nous nous rencontrerons à nouveau...";
				link.l1.go = "MarchCap_Talk_exit";
				pchar.GenQuest.MarchCap = "good";
				break;
			}
			dialog.text = "Splendide, capitaine ! Comme je l'ai dit - c'était plutôt facile, ha-ha... Le butin est énorme, bien plus que je ne l'avais espéré. Il est "+FindRussianQtyString(iQty)+" pieces. Ma part est "+FindRussianQtyString(sti(pchar.GenQuest.MarchCap.CapPart))+".";
			link.l1 = "C'est correct, "+npchar.name+". Je n'ai pas d'objections. Les chaloupes sont en train d'être chargées en ce moment. Peut-être ferons-nous un autre raid ensemble à l'avenir ? Vous semblez être un compagnon approprié pour moi.";
			link.l1.go = "MarchCap_Deck_continue";
			pchar.GenQuest.MarchCap = "exellent";
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "MarchCap_repeat":
			dialog.text = ""+GetAddress_Form(NPChar)+", va à ton navire. Nous n'avons pas le temps de bavarder. Mettons les voiles !";
			link.l1 = "Oui, oui, bien sûr, tu as raison.";
			link.l1.go = "exit";
			NextDiag.TempNode = "MarchCap_repeat";
		break;
		
		case "MarchCap_exit":
			dialog.text = "Hm... Je ne vais pas le faire. Dégage ! Je le ferai moi-même !";
			link.l1 = "Eh bien, eh bien, bon voyage alors...";
			link.l1.go = "MarchCap_DeckExit";
		break;
		
		case "MarchCap_DeckExit":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			DeleteAttribute(npchar, "AlwaysFriend");
			npchar.DontDeskTalk = true;
			DeleteAttribute(pchar, "GenQuest.MarchCap");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

int SelectMarchCapGoods1()
{
	int iGoods;
	switch (hrand(5))
	{
		case 0: iGoods = GOOD_EBONY; break;
		case 1: iGoods = GOOD_MAHOGANY; break;
		case 2: iGoods = GOOD_CINNAMON; break;
		case 3: iGoods = GOOD_COFFEE; break;
		case 4: iGoods = GOOD_CHOCOLATE; break;
		case 5: iGoods = GOOD_TOBACCO; break;
	}
	return iGoods;
}

int SelectPirateShipType()
{
	int iClass = 6;
	int iRank = sti(pchar.rank);
	
	if(iRank < 6) iClass = 6;
	if(iRank >= 6 && iRank < 12) iClass = 5;
	if(iRank >= 12 && iRank < 21) iClass = 4;
	if(iRank >= 21 && iRank < 30) iClass = 4 - rand(1);
	if(iRank >= 30) iClass = 2;
	
	return GetRandomShipType(GetClassFlag(iClass), FLAG_SHIP_TYPE_ANY - FLAG_SHIP_TYPE_MERCHANT, FLAG_SHIP_NATION_ANY);
}
