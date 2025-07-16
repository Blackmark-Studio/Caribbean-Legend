void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Un insecte. Assurez-vous de le signaler aux développeurs.";
			link.l1 = "D'accord";
			link.l1.go = "exit";
		break;
		
		//разговор на палубе
		case "MarginCap":
			dialog.text = "Salutations, capitaine. Voulez-vous quelque chose de moi ?";
			link.l1 = "Oui. Exactement, "+GetAddress_FormToNPC(NPChar)+" . Il y a un passager sur votre navire qui m'intéresse beaucoup. Son nom est "+pchar.GenQuest.Marginpassenger.q1Name+"Je veux que votre passager devienne mon passager. Si cela vous convient, alors nous nous séparerons et ne nous reverrons jamais.";
			link.l1.go = "MarginCap_1";
		break;
	
		case "MarginCap_1":
			dialog.text = "Ah bon ? Et que se passera-t-il si je dis non ?";
			link.l1 = "Alors je devrai te faire reconsidérer ta décision avec quelques volées de mes canons, qui sont pointés dans ta direction à cet instant même. Ne tente pas ta chance, "+GetAddress_FormToNPC(NPChar)+".";
			link.l1.go = "MarginCap_2";
		break;
		
		case "MarginCap_2":
			int MCparam = (7-sti(RealShips[sti(pchar.ship.type)].Class))*100+sti(pchar.ship.Crew.Morale)+sti(pchar.Ship.Crew.Exp.Sailors)+sti(pchar.Ship.Crew.Exp.Cannoners)+sti(pchar.Ship.Crew.Exp.Soldiers);
			int NPCparam = (7-sti(RealShips[sti(npchar.ship.type)].Class))*100+sti(npchar.ship.Crew.Morale)+sti(npchar.Ship.Crew.Exp.Sailors)+sti(npchar.Ship.Crew.Exp.Cannoners)+sti(npchar.Ship.Crew.Exp.Soldiers);
			if (MCparam > NPCparam)//отдаст сам
			{
				dialog.text = "Je n'ai donc pas le choix. Le sort de mon équipage m'est plus précieux que celui d'un seul homme. Mais tu ne t'en tireras pas comme ça ! Je ne l'oublierai pas !";
				link.l1 = "Calme-toi, et epargne-toi une crise de coeur... Amene-moi mon nouveau passager !";
				link.l1.go = "MarginCap_3";
			}
			else
			{
				dialog.text = "Vous feriez mieux de quitter mon navire, monsieur, tant que je vous y autorise encore. N'essayez pas de m'effrayer. Et n'osez pas attaquer mon bateau, sinon vous serez repoussé sur-le-champ. Sortez, tant que je suis encore de bonne humeur !";
				link.l1 = "Je t'ai prévenu. Je suis en route. A bientôt, "+GetAddress_FormToNPC(NPChar)+" !";
				link.l1.go = "MarginCap_4";
			}
		break;
	
		case "MarginCap_3":
			DialogExit();
			npchar.Dialog.CurrentNode = "MarginCap_repeat";
			//отдаем пассажира
			sld = GetCharacter(NPC_GenerateCharacter("MarginPass", pchar.GenQuest.Marginpassenger.model, pchar.GenQuest.Marginpassenger.sex, pchar.GenQuest.Marginpassenger.ani, 2, sti(pchar.GenQuest.Marginpassenger.Nation), -1, true, "quest"));
			sld.Dialog.Filename = "Quest\Marginpassenger.c";
			sld.Dialog.currentnode = "MarginPass";
			sld.name = pchar.GenQuest.Marginpassenger.q1Name;
			sld.lastname = "";
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(sld, pchar.location, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			Map_ReleaseQuestEncounter(npchar.id);
			npchar.Abordage.Enable = false; // запрет абордажа
			npchar.ShipEnemyDisable = true;
			npchar.AlwaysFriend = true;
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), -1);
		break;
		
		case "MarginCap_4":
			DialogExit();
			NextDiag.CurrentNode = "MarginCap_repeat";
			pchar.GenQuest.Marginpassenger.Mustboarding = "true";
			AddQuestRecord("Marginpassenger", "5");
			AddQuestUserData("Marginpassenger", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Marginpassenger.ShipType), "Name")+"Acc")));
			AddQuestUserData("Marginpassenger", "sShipName", pchar.GenQuest.Marginpassenger.ShipName);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), -1);
		break;
		
		case "MarginCap_repeat":
			dialog.text = "Nous avons déjà eu une conversation, tu te souviens ? Eloigne-toi de mon navire !";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "MarginCap_repeat";
		break;
		
		case "MarginCap_abordage":
			if (CheckAttribute(pchar, "GenQuest.Marginpassenger.Mustboarding"))
			{
				dialog.text = "Argh, salaud ! Brule en enfer pour tes actes !";
				link.l1 = "Je vous ai proposé de me livrer le passager pacifiquement... et vous avez rejeté mon offre. Maintenant, vous êtes seul à blâmer !";
				link.l1.go = "MarginCap_abordage_1";
			}
			else
			{
				dialog.text = "Argh, salaud ! Pourquoi as-tu attaqué le navire pacifique ? Nous n'avons ni or ni marchandises précieuses !";
				link.l1 = "Mais tu as une personne de valeur à bord..."+pchar.GenQuest.Marginpassenger.q1Name+"Je veux ton passager.";
				link.l1.go = "MarginCap_abordage_2";
			}
		break;
		
		case "MarginCap_abordage_1":
			dialog.text = "Toi... tu es le sale pirate !";
			link.l1 = "Moins de bavardage, mon ami...";
			link.l1.go = "MarginCap_abordage_3";
		break;
		
		case "MarginCap_abordage_2":
			dialog.text = "Et c'est pour cela que tu as commis un massacre sur mon navire ? Beaucoup d'hommes sont morts ! Pirate !";
			link.l1 = "Moins de bavardage, mon ami...";
			link.l1.go = "MarginCap_abordage_3";
		break;
		
		case "MarginCap_abordage_3":
			DialogExit();
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "Marginpassenger_GivePrisoner");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "MarginNeed":
			dialog.text = "Que veux-tu, "+GetAddress_Form(NPChar)+"?";
			link.l1 = "Es-tu "+pchar.GenQuest.Marginpassenger.q2Name+"?";
			link.l1.go = "MarginNeed_1";
		break;
		
		case "MarginNeed_1":
			dialog.text = "Oui, c'est moi. Voulez-vous soumettre une demande ? Alors vous devriez savoir que...";
			link.l1 = "Attendez un instant, monsieur. J'ai une sorte de requête un peu différente... Connaissez-vous quelqu'un nommé "+pchar.GenQuest.Marginpassenger.q1Name+"?";
			link.l1.go = "MarginNeed_2";
		break;
		
		case "MarginNeed_2":
			switch (pchar.GenQuest.Marginpassenger.sex)
			{
				case "woman":
					dialog.text = "Oui, je la connais... Bien sûr que je la connais ! Qu'y a-t-il ?";
					link.l1 = "Elle s'était mise dans une histoire des plus désagréables : son navire a été capturé par des pirates. Heureusement, j'ai eu l'occasion de monter à bord de leur navire et de sauver cette pauvre âme. Elle m'a dit votre nom et me voici.";
					link.l1.go = "MarginNeed_woman";
				break;
				case "man":
					dialog.text = "Oui, je connais très bien cet homme. Quel est le problème ?";
					link.l1 = "Il s'était retrouvé dans une histoire des plus désagréables : son navire avait été capturé par des pirates. Heureusement, j'ai eu l'occasion de monter à bord de leur navire et de sauver ce prisonnier. Il m'a dit votre nom et me voici.";
					link.l1.go = "MarginNeed_man";
				break;
			}
		break;
		
		case "MarginNeed_woman":
			dialog.text = "Oh mon dieu ! Où est-elle maintenant ? Pourquoi ne l'as-tu pas amenée ici ?";
			link.l1 = "Elle est en sécurité. Et en ce qui concerne ta question... ce n'est pas si simple. J'aurais pu la ramener chez elle moi-même, mais je peux te donner cette opportunité. Pour une modeste somme bien sûr.";
			link.l1.go = "MarginNeed_woman_1";
		break;
		
		case "MarginNeed_woman_1":
			dialog.text = "Hm... Je ne comprends pas...";
			link.l1 = "Pourquoi ne le fais-tu pas? Tu me paies en or, je te donnerai la fille et tu pourras utiliser cette situation à ton avantage... Tu veux l'épouser, n'est-ce pas? Et moi, je réparerai mon navire avec ces pièces, elle a été endommagée durant ce combat avec les pirates.";
			link.l1.go = "MarginNeed_money";
		break;
		
		case "MarginNeed_man":
			dialog.text = "Oh mon dieu ! Où est-il maintenant ? Pourquoi ne l'as-tu pas amené ici ?";
			link.l1 = "Il est en sécurité. Et concernant votre question... ce n'est pas si simple. J'aurais pu le ramener chez lui moi-même, mais je peux vous donner cette opportunité, étant donné que vous avez vos propres intérêts dans sa famille. Pour une modeste somme bien sûr.";
			link.l1.go = "MarginNeed_man_1";
		break;
		
		case "MarginNeed_man_1":
			dialog.text = "Hum... Je ne comprends pas...";
			link.l1 = "Pourquoi ne le fais-tu pas? Tu me paies en or, je te rendrai ton ami et tu pourras utiliser cette situation à ton avantage. J'ai quelques informations, tu sais... Je réparerai mon navire avec ces pièces, elle a été endommagée pendant ce combat avec les pirates.";
			link.l1.go = "MarginNeed_money";
		break;
		
		case "MarginNeed_money":
			dialog.text = "Eh bien, eh bien... et combien voulez-vous ?";
			link.l1 = "Considerez que je veux des doublons, pas des pesos.";
			link.l1.go = "MarginNeed_money_1";
		break;
		
		case "MarginNeed_money_1":
			dialog.text = "Très bien, très bien... Combien de doublons veux-tu ?";
			Link.l1.edit = 1;			
			link.l1 = "";
			link.l1.go = "MarginNeed_money_2";
		break;
		
		case "MarginNeed_money_2":
		iTemp = sti(dialogEditStrings[1]);
		int iSum = makeint(sti(pchar.GenQuest.Marginpassenger.Dublon)*5*stf(pchar.GenQuest.Marginpassenger.Chance));
		if (iTemp <= 0)
		{
			dialog.text = "Très drôle. Bien, faisons semblant que ta blague était amusante. Adieu !";
			link.l1 = "Hm...";
			link.l1.go = "MarginNeed_exit";
			break;
		}
		if (iTemp > 0 && iTemp <= iSum)
		{
			if (hrand(2) > 1) // Addon-2016 Jason уменьшаем раздачу дублонов
			{
				dialog.text = "Bien, je suis d'accord. Je possede la somme requise. Où est "+pchar.GenQuest.Marginpassenger.q1Name+"?";
				link.l1 = "Il doit être sur le quai maintenant. Donc tu peux aller chercher le passager.";
				link.l1.go = "MarginNeed_dublon";
			}
			else
			{
				dialog.text = "Je suis désolé, mais je n'ai pas autant de doublons. Est-ce que des pesos feront l'affaire ?";
				link.l1 = "Je veux des doublons, mais je suppose que le maître de navire acceptera des pesos... Donne-les moi.";
				link.l1.go = "MarginNeed_peso";
				link.l2 = "Non, j'ai besoin de doublons seulement.";
				link.l2.go = "MarginNeed_dublon_exit";
			}
			break;
		}
		if (iTemp > iSum && iTemp < 1000)
		{
			dialog.text = "Malheureusement, je n'ai pas une telle somme. Donc je ne peux pas accepter votre proposition même avec tout mon désir de le faire.";
			link.l1 = "Hm...";
			link.l1.go = "MarginNeed_exit";
			break;
		}
		if (iTemp > 1000 && iTemp < 3000)
		{
			dialog.text = "Monsieur, comprenez-vous seulement de quoi vous parlez ? Etes-vous conscient que cette somme est trop énorme ? Foutez le camp d'ici !";
			link.l1 = "Hm...";
			link.l1.go = "MarginNeed_exit";
			break;
		}
			dialog.text = "Eh bien... Monsieur, vous devez aller chez le médecin et immédiatement. Il semble que vous ayez une très forte fièvre ou... en tout cas, vous avez besoin d'un médecin. Et je suis trop occupé. Adieu !";
			link.l1 = "Hm...";
			link.l1.go = "MarginNeed_exit";
		break;
		
		case "MarginNeed_dublon":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			npchar.lifeday = 0;
			sld = characterFromId("MarginPass");
			RemovePassenger(Pchar, sld);
			sld.lifeday = 0;
			iTemp = sti(dialogEditStrings[1]);
			TakeNItems(pchar, "gold_dublon", iTemp);
			AddQuestRecord("Marginpassenger", "9");
			AddQuestUserData("Marginpassenger", "sSum", iTemp);
			CloseQuestHeader("Marginpassenger");
			DeleteAttribute(Pchar, "GenQuest.Marginpassenger");
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
		break;
		
		case "MarginNeed_peso":
			dialog.text = "Voilà, la somme entière en pesos, exactement ce que vous avez demandé... Où est "+pchar.GenQuest.Marginpassenger.q1Name+"?";
			link.l1 = "Il doit être sur le quai maintenant. Alors tu peux aller chercher le passager..";
			link.l1.go = "MarginNeed_peso_1";
		break;
		
		case "MarginNeed_peso_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			npchar.lifeday = 0;
			sld = characterFromId("MarginPass");
			RemovePassenger(Pchar, sld);
			sld.lifeday = 0;
			iTemp = sti(dialogEditStrings[1])*100;
			AddMoneyToCharacter(pchar, iTemp);
			AddQuestRecord("Marginpassenger", "10");
			AddQuestUserData("Marginpassenger", "sSum", FindRussianMoneyString(iTemp));
			CloseQuestHeader("Marginpassenger");
			DeleteAttribute(Pchar, "GenQuest.Marginpassenger");
			AddCharacterExpToSkill(pchar, "Fortune", 80);//везение
		break;
		
		case "MarginNeed_dublon_exit":
			dialog.text = "Je ne peux donc pas accepter votre proposition, même si j'en ai le désir. Adieu !";
			link.l1 = "Hm...";
			link.l1.go = "MarginNeed_exit";
		break;
		
		case "MarginNeed_exit":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			AddQuestRecord("Marginpassenger", "11");
			AddQuestUserData("Marginpassenger", "sName2", pchar.GenQuest.Marginpassenger.q2Name);
			AddQuestUserData("Marginpassenger", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.City));
			// belamour gen: Добряку недолго осталось -->
			if(CheckAttribute(pchar, "questTemp.LongHappy"))
			{
				AddQuestUserData("Marginpassenger", "sBaron", "to Puerto Principe, to the Black Pastor");
			}
			else
			{
				AddQuestUserData("Marginpassenger", "sBaron", "to Le Francois, to Kindly Jacques");
			}
			// <-- belamour gen
			pchar.GenQuest.Marginpassenger = "cabin";
		break;
		
		case "MarginPass":
			dialog.text = "Que se passe-t-il ici ?!";
			link.l1 = "C'est très simple, "+NPCharSexPhrase(NPChar,"pote","fille")+"Vous êtes maintenant mon cher passager. Un passager gardé. Ne tentez pas de résister ou vous finirez dans la cale.";
			link.l1.go = "MarginPass_1";
		break;
		
		case "MarginPass_1":
			dialog.text = "Voulez-vous dire que je suis votre prisonnier?";
			link.l1 = "Oh, non. Bien sûr que non. Pas un prisonnier, mais un cher invité. Un invité très précieux...";
			link.l1.go = "MarginPass_2";
		break;
		
		case "MarginPass_2":
			dialog.text = "Toi... tu paieras pour tes actions !";
			link.l1 = "Tu as tort encore une fois,"+NPCharSexPhrase(NPChar,", l'ami",", cher")+"Je ne paierai pas, mais je serai payé. Assez parlé, va dans ta cabine !";
			link.l1.go = "MarginPass_3";
		break;
		
		case "MarginPass_3":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "", "", "none", "", "", "", 1.0);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			pchar.quest.Marginpassenger_InWorldOver.over = "yes"; //снять прерывание
			pchar.quest.Marginpassenger_Sink.over = "yes"; //снять прерывание
			pchar.GenQuest.Marginpassenger = "take";
			if (rand(2) == 1) pchar.GenQuest.Marginpassenger.lose = "true";
			else Marginpassenger_CreateNeedman();
			if (CheckAttribute(pchar, "GenQuest.Marginpassenger.Boarding")) AddQuestRecord("Marginpassenger", "6");
			else AddQuestRecord("Marginpassenger", "4");
			AddQuestUserData("Marginpassenger", "sName1", pchar.GenQuest.Marginpassenger.q1Name);
			AddQuestUserData("Marginpassenger", "sShipName", pchar.GenQuest.Marginpassenger.ShipName);
			AddQuestUserData("Marginpassenger", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Marginpassenger.ShipType), "Name")+"Acc")));
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
