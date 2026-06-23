void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag, arRld, arDis;
	int i, Qty;
	ref rColony;
	
	int iTest;
	
	bool  ok; // лесник . спецпеременная.

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	iTest = FindColony(NPChar.City);
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	
	if (Dialog.CurrentNode == "SkladMan1") Dialog.CurrentNode = "SkladMan";

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(int(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "exit_GoOut":
			makearef(arRld, Locations[reload_cur_location_index].reload);
    		Qty = GetAttributesNum(arRld);
			for (i=0; i<Qty; i++)
    		{
    			arDis = GetAttributeN(arRld, i);
    			if (arDis.go == npchar.location)
    			{
					arDis.disable = true; //закрываем вход в дом
					break;
    			}
    		}
			DoQuestFunctionDelay("HouseEnc_TimerGoUot", 10.0);
			pchar.questTemp.HouseEncTimer = pchar.location;
			pchar.questTemp.HouseEncTimer.Id = npchar.id;
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "exit_close":
			makearef(arRld, Locations[reload_cur_location_index].reload);
    		Qty = GetAttributesNum(arRld);
			for (i=0; i<Qty; i++)
    		{
    			arDis = GetAttributeN(arRld, i);
    			if (arDis.go == npchar.location)
    			{
					arDis.disable = true; //закрываем вход в дом
					break;
    			}
    		}
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		//--------------------------------- мужик ---------------------------------
		case "HouseMan":
			NextDiag.TempNode = "HouseMan";
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = PCharRepPhrase(LinkRandPhrase("L'alarme est déclenchée dans la ville. Apparemment, il est temps pour moi de prendre les armes aussi...","Les gardes de la ville ne te poursuivent pas, par hasard ? ","Vous ne trouverez aucun abri ici, mais vous risquez de trouver plusieurs pouces d'acier froid entre vos côtes !"),LinkRandPhrase("De quoi as-tu besoin,"+GetSexPhrase("canaille","coquin")+"?! Les gardes de la ville ont déjà trouvé ton odeur, tu n'iras pas loin, "+GetSexPhrase("sale pirate","toi, garce de pirate")+"!","Sale assassin ! Gardes !!!","Je ne te crains pas, "+GetSexPhrase("rampant","garce")+"! Bientôt tu seras pendu dans notre fort, tu n'iras pas loin..."));
				link.l1 = PCharRepPhrase(RandPhraseSimple("Je vois que tu es fatigué de vivre...","Alors il semble qu'il n'y ait pas de vie paisible pour les citoyens de "+XI_ConvertString("Colony"+npchar.city+"Gen")+"!"),RandPhraseSimple("Va en enfer !","Heh, ce seront les dernières secondes de ta vie..."));
				link.l1.go = PCharRepPhrase("exit_setOwner", "fight");
				break;
			}
			if (isBadReputation(pchar, 40))
			{
				if (CheckAttribute(pchar, "questTemp.HouseEncTimer"))
				{
					dialog.text = "Je t'ai prévenu. Et puis tu peux décider par toi-même, si tu veux te mettre en difficulté.";
					link.l1 = "Heh !";
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = "Que faites-vous dans ma maison, gredin?! Vous avez dix secondes pour déguerpir d'ici !";
					link.l1 = LinkRandPhrase("Heh, on dirait qu'ils me connaissent ici aussi !","Ma renommée m'a juste précédé...","Hmm, je vois.");
					link.l1.go = "exit_GoOut";
				}
			}
			else
			{
				if (IsDay())
				{
					dialog.text = NPCStringReactionRepeat("Je suis heureux de vous accueillir chez moi. Avez-vous des affaires avec moi?","Que puis-je faire pour vous ?","Hmm... Que puis-je faire pour toi?","Je suis désolé, mais si vous n'avez pas d'affaires avec moi, veuillez ne pas me déranger...","bloc",1,npchar,Dialog.CurrentNode);
					link.l1 = HeroStringReactionRepeat("Non, juste en train de regarder autour, de rencontrer de nouvelles personnes...","Non, rien de particulier...","Rien...","D'accord, comme tu dis.",npchar,Dialog.CurrentNode);
					link.l1.go = DialogGoNodeRepeat("HouseMan_1", "exit_setOwner", "exit_setOwner", "exit_setOwner", npchar, Dialog.CurrentNode);
				}
				else
				{
					dialog.text = NPCStringReactionRepeat("Je suis désolé, mais la nuit n'est pas le meilleur moment pour les visites, et donc je vous demanderais de quitter ma maison immédiatement!","Je vous ai déjà dit, il est tard. S'il vous plaît, partez.","Je ne veux pas paraître impoli, mais j'insiste pour que vous quittiez ma maison immédiatement !","Sacrebleu, qu'est-ce qui se passe ?! Gardes! Voleurs!","bloc",1,npchar,Dialog.CurrentNode);
					link.l1 = HeroStringReactionRepeat("D'accord, je vois...","Ouais, juste un moment...","D'accord, ne te réjouis juste pas trop.","Quels voleurs ?! Tais-toi !",npchar,Dialog.CurrentNode);
					link.l1.go = DialogGoNodeRepeat("exit_close", "exit_setOwner", "exit_setOwner", "fight", npchar, Dialog.CurrentNode);
				}
			}
		break;

		case "HouseMan_1":
			dialog.text = "Oh, permettez-moi de me présenter - "+GetFullName(npchar)+". Nous sommes très heureux de vous avoir comme notre invité. Dans cette ville, les lois de l'hospitalité sont honorées.";
			link.l1 = GetFullName(pchar)+", si vous voulez bien...";
			link.l1.go = "exit_setOwner";
		break;
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Tu es "+GetSexPhrase("un voleur, je vois! Gardes, arrêtez-le","un voleur, je vois! Gardes, attrapez-la")+"!!!","Je n'arrive pas à y croire! J'ai détourné le regard pour une seconde - et tu fouilles dans mes affaires! Arrêtez un voleur!!!","Gardes! Vol! Arrêtez un voleur!!!");
			link.l1 = "Aaaah, diable!!!";
			link.l1.go = "fight";
		break;
		// --------------------------------- баба ---------------------------------
		case "HouseWoman":
			NextDiag.TempNode = "HouseWoman";
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = PCharRepPhrase(LinkRandPhrase("Je te préviens que mon mari va bientôt rentrer ! Tu ferais mieux de quitter ma maison maintenant !","Je ne pense pas que tu réussisses à t'échapper ! Et sache que mon mari sera bientôt de retour à la maison !","Mon mari sera bientôt à la maison! Vous devez partir tout de suite!"),LinkRandPhrase("Dommage que mon mari ne soit pas à la maison... Sortez ! Maintenant !!!","Sale assassin, sors de ma maison tout de suite ! Gardes !",""+GetSexPhrase("Quel coquin","Quelle saleté")+"... Bientôt mon mari reviendra, et il verra de quelle couleur est ton sang !"));
				link.l1 = PCharRepPhrase(RandPhraseSimple("Oh, votre mari... oooooh...Je tremble...","Heh... Tu sais, demoiselle, ton mari n'est qu'un homme... tu ne voudrais pas qu'il meure à tes pieds, n'est-ce pas?"),RandPhraseSimple("Tais-toi, garce, avant que je ne t'éventre...","Je resterai ici aussi longtemps que je le souhaite. Et tu ferais mieux de la boucler si tu sais ce qui est bon pour toi..."));
				link.l1.go = "exit_setOwner";
				break;
			}
			if (isBadReputation(pchar, 40))
			{
				if (CheckAttribute(pchar, "questTemp.HouseEncTimer"))
				{
					dialog.text = "Je t'ai prévenu. Dégage ou tu le regretteras!";
					link.l1 = "Quelle sotte garce...";
					link.l1.go = "exit";
				}
				else
				{					
					dialog.text = "Que faites-vous dans ma maison, "+GetSexPhrase("canaille","coquin")+"?! Si tu n'es pas parti dans dix secondes, j'appelle les gardes !";
					link.l1 = "Quelle sotte garce...";
					link.l1.go = "exit_GoOut";
				}
			}
			else
			{
				if (IsDay())
				{
					dialog.text = NPCStringReactionRepeat("Je suis ravi de vous voir dans notre maison. Mon nom est "+GetFullName(npchar)+". Que puis-je faire pour vous?","Tu es toujours là ?","Hm, excusez-moi, mais ne pensez-vous pas qu'il est temps pour vous de partir?","Je vous demanderais gentiment de ne pas abuser de notre hospitalité.","bloc",1,npchar,Dialog.CurrentNode);
					link.l1 = HeroStringReactionRepeat(GetFullName(pchar)+" à votre service. Je suis venu ici sans raison particulière, juste pour faire connaissance.","Toujours ici.","Eh bien, je ne sais pas...","D'accord.",npchar,Dialog.CurrentNode);
					link.l1.go = DialogGoNodeRepeat("HouseWoman_1", "exit_setOwner", "exit_setOwner", "exit_setOwner", npchar, Dialog.CurrentNode);
				}
				else
				{
					dialog.text = NPCStringReactionRepeat("Oh là là, pourquoi entres-tu dans ma maison à une telle heure ! Tu m'as vraiment fait peur... S'il te plaît, viens nous rendre visite demain !","S'il vous plaît, quittez notre maison !"+GetSexPhrase("","Je suis une femme mariee !")+"","Je vous demande de quitter notre maison pour la dernière fois !","Mais que se passe-t-il ici?!","bloc",1,npchar,Dialog.CurrentNode);
					link.l1 = HeroStringReactionRepeat("Ne soyez pas effrayé, je ne vous ferai pas de mal.","D'accord, ne te fâche pas autant.","Je pars.","Quoi de neuf ?",npchar,Dialog.CurrentNode);
					link.l1.go = DialogGoNodeRepeat("exit_close", "exit_setOwner", "exit_setOwner", "HouseWoman_2", npchar, Dialog.CurrentNode);
				}
			}
		break;

		case "HouseWoman_1":
			dialog.text = "Nous sommes toujours heureux d'avoir des invités. Ne restez simplement pas trop longtemps,"+GetSexPhrase(", puisque je suis une femme mariee..."," puisque j'ai beaucoup à faire...")+"";
			link.l1 = "Oh, ouais, bien sûr...";
			link.l1.go = "exit_setOwner";
		break;
		case "Woman_FackYou":
			dialog.text = "C'est comme ça alors? Je t'ai accueilli comme mon invité, et tu fouilles dans nos coffres?! Gardes!";
			link.l1 = "Tais-toi, garce !";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(int(npchar.nation), RELATION_ENEMY);
		break;
		case "HouseWoman_2":
			dialog.text = "Je vous ai demandé de quitter notre maison de manière amicale, mais vous n'avez tout simplement pas écouté ! Assez ! À l'aide ! Gardes !";
			link.l1 = "Taisez-vous, femme insensée! Êtes-vous folle?!";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(int(npchar.nation), RELATION_ENEMY);
		break; 
		//--------------------------------- завсклад ---------------------------------		
		case "SkladMan":
			NextDiag.TempNode = "SkladMan";
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase("L'alarme est donnée dans la ville. Apparemment, il est temps pour moi de prendre les armes aussi...","Les gardes de la ville ne te poursuivent pas, par hasard ?","Vous ne trouverez aucun abri ici, mais vous risquez de trouver plusieurs centimètres d'acier froid entre vos côtes!"),LinkRandPhrase("De quoi as-tu besoin,"+GetSexPhrase("canaille","coquin")+"?! Les gardes de la ville ont déjà trouvé votre odeur, vous n'irez pas loin, "+GetSexPhrase("sale pirate","gourgandine")+"!","Sale assassin! Gardes!!!","Je n'ai pas peur de toi, "+GetSexPhrase("rampant","garce")+"! Bientôt tu seras pendu dans notre fort, tu n'iras pas loin..."));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("Je vois que tu es fatigué de vivre...","Donc, il semble qu'il n'y ait pas de vie paisible pour les citoyens de "+XI_ConvertString("Colony"+npchar.city+"Gen")+"!"),RandPhraseSimple("Va en enfer!","Heh, ce seront les dernières secondes de ta vie..."));
				link.l1.go = NPCharRepPhrase(pchar, "exit_setOwner", "fight");
				break;
			}
			//открывание двери верфи по квесту промышленного шпионажа
			if (CheckAttribute(pchar, "questTemp.different.ShipyardsMap") && pchar.questTemp.different.ShipyardsMap == "toTarget" && npchar.city == pchar.questTemp.different.ShipyardsMap.city && locations[reload_cur_location_index].type == "shipyard")
			{
				link.l2 = "Ecoute, mon pote, je veux te parler franchement.";
				link.l2.go = "ShipyardsMap_1";
				pchar.questTemp.different.ShipyardsMap = "toResult";					
			}
			// ugeen --> склад товаров для ГГ				
			if(CheckAttribute(NPChar,"Storage"))
			{
				if(!CheckAttribute(NPChar, "Storage.Speak"))
				{
					link.l7 = DLG_Convert("storageRent", "Dialogs.txt");
					link.l7.go = "storage_rent";
				}
				else
				{
					if(CheckAttribute(NPChar,"Storage.Activate"))
					{
						link.l7 = "Emmène-moi à l'entrepôt. Je veux voir dans quel état il est.";
						link.l7.go = "storage_0";
						link.l8 = "J'ai décidé de quitter l'entrepôt. Je n'en ai plus besoin.";
						link.l8.go = "storage_04";
					}
					else
					{
						link.l7 = "Vous avez mentionné un entrepôt. Est-il toujours vacant?";
						link.l7.go = "storage_01";
					}
				}		
			// <-- ugeen
			}		
			dialog.text = NPCStringReactionRepeat("Bienvenue! Mon nom est "+GetFullName(npchar)+". Ici, je suis en charge, alors ne pense même pas à emporter quoi que ce soit avec toi...","Comportez-vous correctement et gardez à l'esprit que je vous surveille.","Tant que vous ne regardez pas dans les coffres, vous pouvez rester ici. Je m'ennuie tout seul, de toute façon...",RandPhraseSimple("Oh la la, je m'ennuie tellement !","Sapristi, que prendre ? Etre ici est tellement ennuyeux !"),"bloc",3,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("D'accord, ne t'inquiète pas.","Certainement !","Je vois...","Ouais, ça ressemble à un problème.",npchar,Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("exit", "exit", "exit", "exit", npchar, Dialog.CurrentNode);				
		break;
		
		//--------------------------------- Аренда склада ---------------------------------
		case "storage_rent":
			NPChar.Storage.Speak = true;
			dialog.text = "Nous avons une zone appropriée pour un entrepôt. Souhaiteriez-vous le louer à un prix raisonnable? Imaginez, vous auriez votre propre entrepôt pour stocker des marchandises précieuses...";
			link.l1 = "Un entrepôt, dites-vous ? Oui, tentant, en effet ... Est-il suffisamment grand ? Et combien allez-vous facturer pour le loyer ?";
			link.l1.go = "storage_rent1";
		break;
		
		case "storage_rent1":
			NPChar.MoneyForStorage = GetStoragePriceExt(NPChar, pchar); 
			dialog.text = "C'est assez spacieux même pour un entrepôt portuaire, il peut contenir voyons voir ... 50000 quintaux de marchandises. Pour "+FindRussianMoneyString(int(NPChar.MoneyForStorage))+"  par mois, je peux assurer la sécurité de vos marchandises. "+"Cela inclut la protection avec mes hommes, la protection contre l'humidité, et la lutte contre les rats. Que dites-vous? Oh, et la confidentialité aussi, cela va sans dire.";
			link.l1 = "Je le ferai. Puis-je y jeter un coup d'oeil?";	
			link.l1.go = "storage_rent2";
			link.l2 = "C'est trop. Et je parie que c'est inondé et infesté de rats.";
			link.l2.go = "storage_rent3";		
		break;
		
		case "storage_rent2":
			dialog.text = "Certainement, certainement. Mais... j'aurai besoin d'un mois de paiement en avance. ";
			if(int(pchar.money) >= int(NPChar.MoneyForStorage))
			{
				link.l1 = "Vous êtes... assez mercantile, je dois dire. Voici votre argent ... Je vais louer cette remise.";
				link.l1.go = "storage_11";
			}
			else
			{	
				link.l1 = "Vous êtes... assez mercantile, je dois dire. D'accord, je vais chercher l'argent.";
				link.l1.go = "exit";
			}	
		break;
		
		case "storage_rent3":
			dialog.text = "Comme vous voulez. Si vous changez d'avis, faites-le moi savoir. Et gardez à l'esprit, qu'un si beau entrepôt est peu susceptible de rester vacant longtemps...";
			link.l1 = "Aucun problème. Je te ferai savoir si j'en ai besoin.";
			link.l1.go = "exit";
		break;
		
		case "storage_0":
			NPChar.MoneyForStorage = GetNpcQuestPastMonthParam(NPChar, "Storage.Date") * int(NPChar.Storage.MoneyForStorage);
			if(int(NPChar.MoneyForStorage) > 0)
			{
				dialog.text = "Et pour le loyer, tu me dois toujours  "+FindRussianMoneyString(int(NPChar.MoneyForStorage))+".";
				if(int(pchar.money) >= int(NPChar.MoneyForStorage))
				{
					link.l1 = "D'accord, je vais payer le loyer maintenant.";
					link.l1.go = "storage_3";
				}
				else
				{
					link.l1 = "Je reviendrai plus tard.";
					link.l1.go = "exit";
				}
			}		
			else
			{ // лесник . если забыл с собой корабль то никак.
				ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		        if (int(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
				{	
				dialog.text = "Allez-y.";
				link.l1 = "Merci.";
				link.l1.go = "storage_2";
				}
				else
				{
                dialog.text = RandPhraseSimple("Capitaine, où est votre navire? Comment prévoyez-vous de déplacer la cargaison?","Je ne vois pas votre navire amarré au port. Comment comptez-vous exactement le charger ?");
                link.l1 = RandPhraseSimple("Oh.. J'ai totalement oublié ça !","Sacrebleu, c'est vrai !");
			    link.l1.go = "exit";
				break;
                }			
			}
			link.l2 = "Non, j'ai changé d'avis.";
			link.l2.go = "exit"; 						
		break;
		
		case "storage_01":
			dialog.text = "Non, "+GetSexPhrase("monsieur","madame")+", toujours vacant et en attente de vous. Je savais que vous ne refuseriez pas mon offre à la fin.";
			link.l1 = "Très bien. Je vais le louer.";
			link.l1.go = "storage_1";
			link.l2 = "Non, ça vient de me venir à l'esprit...";
			link.l2.go = "exit";
		break;
		
		case "storage_1":
			NPChar.MoneyForStorage = GetStoragePriceExt(NPChar, pchar); 
			dialog.text = "Comme vous devriez vous en souvenir, j'ai besoin d'un mois de paiement d'avance.";
			if(int(pchar.money) >= int(NPChar.MoneyForStorage))
			{
				link.l1 = "Bien sûr, je me souviens. Voici pour toi.";
				link.l1.go = "storage_11";
			}
			else
			{
				link.l1 = "Zut. Très bien, je vais chercher l'argent.";
				link.l1.go = "exit";
			}
		break;
		
		case "storage_11":
			AddMoneyToCharacter(pchar, -int(NPChar.MoneyForStorage));
			NPChar.Storage.MoneyForStorage = NPChar.MoneyForStorage;
			NPChar.Storage.Activate = true;
			Achievment_Set("ach_67"); // ugeen 2016
			SaveCurrentNpcQuestDateParam(NPChar, "Storage.Date");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchStorage(int(rColony.StoreNum));
		break;
				
		case "storage_2":			
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchStorage(int(rColony.StoreNum));
		break;
		
		case "storage_3":			
			AddMoneyToCharacter(pchar, -int(NPChar.MoneyForStorage));
			NPChar.MoneyForStorage = GetStoragePriceExt(NPChar, pchar);
			NPChar.Storage.MoneyForStorage = NPChar.MoneyForStorage;
			SaveCurrentNpcQuestDateParam(NPChar, "Storage.Date");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchStorage(int(rColony.StoreNum));
		break;		

		case "storage_04":
			dialog.text = "Vous partez déjà? Quel dommage, c'est vraiment un excellent endroit à de bonnes conditions. Je vous assure que vous ne trouverez pas une offre comme celle-ci nulle part dans les Caraïbes.";
			link.l1 = "J'ai dit, je le libère. Ou proposez-vous de me faire payer pour stocker de l'air ? Vous pouvez chercher un autre détenteur.";
			link.l1.go = "storage_4";
			link.l2 = "Nulle part dans les Caraïbes, dites-vous ? D'accord, je le garderai pour un moment, alors. Mais le prix de la location, je dois dire, est un peu trop élevé.";
			link.l2.go = "exit";
		break;
		
		case "storage_4":
			NPChar.MoneyForStorage = GetNpcQuestPastMonthParam(NPChar,"Storage.Date") * int(NPChar.Storage.MoneyForStorage);
			if(int(NPChar.MoneyForStorage) > 0)
			{
				dialog.text = "Et pour le loyer, tu me dois encore "+FindRussianMoneyString(int(NPChar.MoneyForStorage))+".";
				if(int(pchar.money) >= int(NPChar.MoneyForStorage))
				{
					link.l1 = "D'accord.";
					link.l1.go = "storage_5";
				}
			}
			else
			{ // лесник . если нет корабля то и товар не забрать
				ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		        if (int(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
				{	
				dialog.text = "Récupérez vos marchandises, et je fermerai l'entrepôt.";
				link.l1 = "D'accord.";
				link.l1.go = "storage_6";
				}
				else
				{
                dialog.text = RandPhraseSimple("Capitaine, où est votre navire? Comment prévoyez-vous de déplacer la cargaison?","Je ne vois pas votre navire amarré au port. Comment comptez-vous exactement le charger ?");
                link.l1 = RandPhraseSimple("Oh.. J'ai complètement oublié ça !","Zut, c'est vrai !");
			    link.l1.go = "exit";
				break;
                }				
			}
		break;
		
		case "storage_5":
			LeaveStorage(NPChar, rColony, int(NPChar.MoneyForStorage));
			DialogExit();
		break;
		
		case "storage_6":
			LeaveStorage(NPChar, rColony);
			DialogExit();
		break;

		//--------------------------------- Аренда склада ---------------------------------
		
		case "ShipyardsMap_1":
			dialog.text = "Heh ! D'accord, parlons.";
			link.l1 = "J'ai besoin de me rendre au chantier naval la nuit, quand il n'y a personne autour.";
			link.l1.go = "ShipyardsMap_2";
		break;
		case "ShipyardsMap_2":
			if (int(pchar.questTemp.different.ShipyardsMap.skladFight))
			{
				dialog.text = "Regardez-vous ! Hé, gardes, nous avons un voleur ici !!!";
				link.l1 = "Quel voleur ? Je voulais juste parler !";
				link.l1.go = "fight";
				AddCharacterExpToSkill(pchar, "FencingL", 5);
				AddCharacterExpToSkill(pchar, "FencingS", 5);
				AddCharacterExpToSkill(pchar, "FencingH", 5);
				ChangeCharacterComplexReputation(pchar,"nobility", -1);
			}
			else
			{
				dialog.text = "Wow ! Regardez-vous, "+GetSexPhrase("camarade","demoiselle")+". Venir à l'entrepôt du chantier naval avec une telle demande !";
				link.l1 = "J'ai besoin d'aller à la cale sèche elle-même. Je me fiche éperdument de votre entrepôt.";
				link.l1.go = "ShipyardsMap_3";
				AddCharacterExpToSkill(pchar, "Fortune", 10);
			}
		break;
		case "ShipyardsMap_3":
			dialog.text = "Mais pourquoi en avez-vous besoin ?";
			link.l1 = "Il y a un besoin. Et je suis prêt à payer pour cela...";
			link.l1.go = "ShipyardsMap_4";
		break;
		case "ShipyardsMap_4":
			dialog.text = "Hmm, c'est mieux ... D'accord! Glisse-moi "+FindRussianMoneyString(int(pchar.questTemp.different.ShipyardsMap.sklad)*1000)+", et je laisserai la porte du chantier naval ouverte pendant le jour suivant.";
			link.l1 = "C'est trop cher. Je vais devoir m'en passer, alors...";
			link.l1.go = "exit";
			if (int(pchar.money) >= (int(pchar.questTemp.different.ShipyardsMap.sklad)*1000))
			{
				link.l2 = "D'accord, je suis d'accord. Prenez votre argent et faites ce que nous avons convenu.";
				link.l2.go = "ShipyardsMap_5";
			}
		break;
		case "ShipyardsMap_5":
			dialog.text = "Ne t'inquiète pas, ce sera fait.";
			link.l1 = "J'espère bien...";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -int(pchar.questTemp.different.ShipyardsMap.sklad)*1000);
			AddQuestRecord("ShipyardsMap", "5");
			AddQuestUserData("ShipyardsMap", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			//снимаем close_for_night
			string  sName;
			int location_index = FindLocation(npchar.city + "_town");
    		makearef(arRld, Locations[location_index].reload);
    		Qty = GetAttributesNum(arRld);
    		for (int a=0; a<Qty; a++)
    		{
    			arDis = GetAttributeN(arRld, a);
				sName = arDis.go;
    			if (findsubstr(sName, "_shipyard" , 0) != -1)
    			{
					DeleteAttribute(arDis, "close_for_night");
					break;
    			}
    		}
			LocatorReloadEnterDisable(npchar.city + "_shipyard", "reload2", true);
			//ставим таймер на возврат close_for_night
			SetTimerFunction("ShipyardsMap_returnCFN", 0, 0, 2);
		break;

	}
}
