// диалог по городам
// Это мастер тюнинга
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    string 	sTemp;
	int 	amount, iSan, iOil, iSil, iRop;
	int iTemp, iSum; // 280912
	ref 	shTo;
	string 	s1;
	
	int     Matherial1;
	int     Matherial2;
	int     Matherial3;
	int     Matherial4;
	int		HPPrice; 
	
	if ( sti(pchar.Ship.Type) != SHIP_NOTUSED)
	{
		int   	shipCurHP   = sti(RealShips[sti(pchar.Ship.Type)].HP);
		int   	shipBaseHP	= sti(RealShips[sti(pchar.Ship.Type)].BaseHP);
		int   	shipClass   = sti(RealShips[sti(pchar.Ship.Type)].Class);
	}	
 
	switch (Dialog.CurrentNode)
	{		
		// -----------------------------------Диалог первый - первая встреча
		case "First time":  // перехват основного диалога, только один раз
			if(NPChar.quest.meeting == "0")
			{
				Dialog.Text = "Ouf... Quel climat épouvantable... Mon nom est "+GetFullName(npchar)+", et que Dieu me damne, si je ne suis pas le meilleur constructeur naval de ces îles oubliées de Dieu. Mais cette humidité me couche...";
				Link.l1 = pcharrepphrase("Mille requins, il ne me manquait plus que le marmonnement d'un vieil homme. Mon nom est "+GetFullName(pchar)+", je crois que vous avez entendu parler de moi.","Ce n'est pas l'humidité, c'est la vieillesse, monsieur. Mon nom est "+GetFullName(pchar)+", je crois que vous avez entendu parler de moi.");
				Link.l1.go = "node_1";
				npchar.quest.meeting = "1";
			}
			else // нужно, если по квестам будет сброс на  "First time"
			{
				dialog.text = "Oh, toi encore, toujours à parler de tes problèmes... (toussant).";
				link.l1 = pcharrepphrase("Tu as raison, c'est encore moi. Mais parlons affaires tant que tu n'as pas encore rendu ton âme à Dieu.","Votre mémoire vous sert bien, et maintenant, si vous le permettez, passons à des questions plus spécifiques.");
				link.l1.go = "node_3";
				link.l2 = pcharrepphrase("Je suis lassé de tes marmonnements. Adieu.","Il est temps pour moi de partir. Désolé de vous avoir dérangé");
				link.l2.go = "exit";
			}
			NextDiag.TempNode = "Master_Ship";
			Dialog.CurrentNode = "Master_Ship";
		break;
		
		case "Master_Ship":
		//Jason ----------------------------------- Хронометр Алекса ------------------------------------------
			if (CheckAttribute(npchar, "quest.sextant") && CheckAttribute(pchar, "questTemp.AlexClock") && pchar.location == "Pirates_shipyard" && !CheckAttribute(npchar, "quest.clock"))
			{
				dialog.text = "Aha, capitaine "+GetFullName(pchar)+"! Quelle joie que vous soyez passé !";
				Link.l1 = "On dirait que vous avez besoin de moi pour quelque chose, n'est-ce pas ? D'habitude, vous n'êtes pas aussi courtois.";
				Link.l1.go = "clock_begin";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.AlexClock") && pchar.questTemp.AlexClock == "clock" && pchar.location == "Pirates_shipyard")
			{
				dialog.text = "Je vois que vous revenez à moi les mains vides, capitaine ! Que s'est-il passé avec les...invités ?";
				Link.l1 = "Ils sont partis. Je leur ai demandé et ils sont partis.";
				Link.l1.go = "clock_complete";
				break;
			}
		//<-- хронометр Алекса
			dialog.text = "Oh, vous encore, toujours à parler de vos problèmes... (toussant)";
			link.l1 = pcharrepphrase("Tu as raison, c'est encore moi. Mais parlons affaires tant que tu n'as pas encore rendu ton âme à Dieu.","Votre mémoire ne vous fait pas défaut, et maintenant, si vous le permettez, passons à des questions plus précises.");
			link.l1.go = "node_3";
			link.l2 = pcharrepphrase("J'en ai assez de tes marmonnements. Adieu.","Il est temps pour moi de partir. Désolé de vous déranger.");
			link.l2.go = "exit";
			NextDiag.TempNode = "Master_Ship";
		break;

		case "node_1":
			dialog.text = "Les jeunes de nos jours... Vous n'avez jamais de respect. Têtes brûlées, mains dures, que désirez-vous ?";
			link.l1 = pcharrepphrase("C'est exact. Mais tôt ou tard, tout a une fin et il semble que ton heure soit proche...","Quelque chose me dit que durant vos jeunes années, vous n'aviez pas nécessairement beaucoup de respect pour vos aînés non plus. Ai-je raison ?");
			link.l1.go = "node_2";
		break;

		case "node_2":
			dialog.text = "Ne discute pas avec tes aînés, chiot.";
			link.l1 = pcharrepphrase("Doucement, maintenant. Calmez-vous. Ne vous épuisez pas sinon vous risquez une attaque cardiaque. Je ne veux pas être accusé de la mort du meilleur charpentier des Caraïbes. Passons aux affaires.","Je te pardonne pour ton impolitesse, uniquement par respect pour ton âge. Et maintenant, si tu as fini, passons aux affaires.");
			link.l1.go = "node_3";
			link.l2 = pcharrepphrase("D'accord, c'est assez de sermons pour moi ! Adieu !","Je vois que nous n'allons pas être d'accord. Adieu.");
			link.l2.go = "exit";
		break;

		case "node_3":
			dialog.text = "(toussant)... Les gens ne laissent pas un vieillard en paix. Que me veux-tu cette fois, "+GetAddress_Form(NPChar)+"? ";
			link.l1 = pcharrepphrase("J'ai besoin d'utiliser les services du chantier naval.","Je veux utiliser les services du chantier naval.");
			link.l1.go = "shipyard_dlg";
            Link.l2 = "J'ai une question.";
			Link.l2.go = "quests"; //(пересылка в файл города)
			// -->
			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
			{
				link.l3 = "Je voudrais parler de finances.";
				link.l3.go = "LoanForAll";//(перессылка в файл города)
			}
			link.l9 = pcharrepphrase("Merde, j'ai quelques affaires urgentes à régler, adieu.","Il est temps pour moi de partir. Désolé.");
			link.l9.go = "exit";
			NextDiag.TempNode = "Master_Ship";
		break;
		
		case "shipyard_dlg":			
			if((shipBaseHP - shipCurHP > 0) && (shipClass < 7))
			{
				dialog.Text = "Je peux vous proposer une réparation capitale de la charpente de votre coque. Les gens ici ne savent pas construire de bons navires, ils tombent tous en morceaux après un seul tir...";						
				Link.l1 = "Super ! J'ai justement un navire qui a besoin de réparations. Peut-être pourriez-vous jeter un œil à ce que vous pouvez faire ?";
				Link.l1.go = "ship_repair_start";		
			}
			else
			{
				dialog.Text = "Allez, qu'est-ce que tu veux ? Ne harcèle pas un vieil homme...";
			}	
			link.l2 = "Je veux juste utiliser les services du chantier naval.";
			link.l2.go = "shipyard";
			link.l3 = "J'ai besoin d'armes pour le navire.";
			link.l3.go = "Cannons";
			if(RealShips[sti(Pchar.Ship.Type)].BaseType != SHIP_CURSED_FDM)
			{
					link.l4 = "Je veux changer l'apparence de mes voiles.";
					link.l4.go = "SailsGerald";
			}
			if(RealShips[sti(Pchar.Ship.Type)].BaseType == SHIP_CURSED_FDM && !CheckAttribute(npchar, "quest.FDM_hull"))
			{
					link.l50 = "Mon navire est assez... spécial. J'aimerais apporter quelques modifications.";
					link.l50.go = "FDM";
			}
			if(RealShips[sti(Pchar.Ship.Type)].BaseType == SHIP_CURSED_FDM && CheckAttribute(npchar, "quest.FDM_full") && npchar.quest.FDM_full == "cabin" && GetCharacterItem(pchar, "Chest") > 0)
			{
					link.l50 = "J'ai plus de coffres pour la reconstruction de la cabine.";
					link.l50.go = "FDM_cabin_pay";
			}
			// Xenon -->
			if(RealShips[sti(Pchar.Ship.Type)].BaseType == SHIP_CURSED_FDM && CheckAttribute(npchar, "quest.FDM_hull") && npchar.quest.FDM_hull == "hull_waitmoney")
			{
					link.l50 = "Je suis ici pour parler de la reconstruction du navire.";
					link.l50.go = "FDM_hull_givemoney";
			}

			if(RealShips[sti(Pchar.Ship.Type)].BaseType == SHIP_CURSED_FDM && CheckAttribute(npchar, "quest.FDM_hull") && npchar.quest.FDM_hull == "hull_waitmaterials")
			{
					link.l50 = "Je suis ici pour parler de la reconstruction du navire.";
					link.l50.go = "FDM_hull_checkmaterials";
			}
			// <-- Xenon
			link.l9 = pcharrepphrase("Merde, j'ai quelques affaires urgentes à régler, adieu.","Il est temps pour moi de partir. Désolé.");
			Link.l9.go = "ship_tunning_not_now";
		break;
		
		case "ship_repair_again":
			if((shipBaseHP - shipCurHP > 0) && (shipClass < 7))
			{
				dialog.Text = RandPhraseSimple("Ah... vous encore. Vous voulez réparer votre bateau à nouveau ?",RandPhraseSimple("Salutations, à un capitaine célèbre. Quoi, avez-vous besoin d'une autre réparation capitale ?","Bon sang... Pas une minute de paix et de tranquillité. Vous ne laissez pas un vieil homme se concentrer... Encore une réparation ?"));
				Link.l1 = "Oui. Bien sûr. Allons-nous examiner ce que nous pouvons faire ?";
				Link.l1.go = "ship_repair_start";						   
			}
			else
			{
				dialog.Text = "Qu'est-ce qui s'est passé cette fois ? Vous ne voulez tout simplement pas me laisser tranquille...";
			}				
			link.l2 = "Je veux juste utiliser les services du chantier naval.";
			link.l2.go = "shipyard";
			link.l3 = "J'ai besoin d'armes pour le navire.";
			link.l3.go = "Cannons";
			if(RealShips[sti(Pchar.Ship.Type)].BaseType != SHIP_CURSED_FDM)
			{
					link.l31 = "Je veux changer l'apparence de mes voiles.";
					link.l31.go = "SailsGerald";
			}
			if(RealShips[sti(Pchar.Ship.Type)].BaseType == SHIP_CURSED_FDM && !CheckAttribute(npchar, "quest.FDM_hull"))
			{
					link.l50 = "Mon navire est assez... spécial. J'aimerais apporter quelques modifications.";
					link.l50.go = "FDM";
			}
			if(RealShips[sti(Pchar.Ship.Type)].BaseType == SHIP_CURSED_FDM && CheckAttribute(npchar, "quest.FDM_full") && npchar.quest.FDM_full == "cabin" && GetCharacterItem(pchar, "Chest") > 0)
			{
					link.l50 = "J'ai plus de coffres pour la reconstruction de la cabine.";
					link.l50.go = "FDM_cabin_pay";
			}
            Link.l4 = "J'ai une question.";
			Link.l4.go = "quests"; //(пересылка в файл города)
			// -->
			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
			{
				link.l5 = "J'aimerais parler de finances.";
				link.l5.go = "LoanForAll";//(пересылка в файл города)
			}
			Link.l9 = "Non. Je suis satisfait de ce que j'ai.";
			Link.l9.go = "ship_tunning_not_now_2";
		break;
		
		case "ship_tunning_not_now_2":
			dialog.Text = "Oh, je vois que tu es encore en train de réfléchir! Tu iras loin! Reviens quand tu auras décidé ce que tu veux et ne viens pas me déranger avec des balivernes.";
			Link.l1 = RandPhraseSimple("Merci ! Tous mes voeux.","Adieu, maître. Et moins de sarcasme.");
			Link.l1.go = "ship_tunning_not_now";
		break;
		
		case "ship_repair_start":
            if ( sti(Pchar.Ship.Type) == SHIP_NOTUSED || Pchar.location.from_sea != "Pirates_town")
            {
                dialog.Text = "Où est le navire ? Qu'est-ce que c'est que ces simagrées ?!";
			    Link.l1 = "Oui, tu as raison... Je suis... Je m'excuse.";
			    Link.l1.go = "ship_tunning_not_now";
            }
            else
            {
			    if (GetHour() == 13)
			    {
					dialog.Text = "Je suis peut-être un bourreau de travail, mais j'ai aussi une pause déjeuner. Revenez plus tard !";
			        Link.l1 = "D'accord...";
			        Link.l1.go = "ship_tunning_not_now";
			    }
			    else
			    {
                    if( makefloat(shipCurHP)/makefloat(shipBaseHP) < 0.10)
                    {
						dialog.Text = "Fichtre... Votre navire est complètement en ruine. Je ne ferai pas de réparation capitale, ne me le demandez même pas... Si vous étiez venu un peu plus tôt...";
    			        Link.l1 = "D'accord... C'est dommage...";
    			        Link.l1.go = "ship_tunning_not_now";
    			        break;
                    }
					if( makefloat(shipCurHP)/makefloat(shipBaseHP) > 0.95)
                    {
						dialog.Text = "Quel est ce charabia... Votre navire est comme neuf... La coque brille de mille feux. Il n'y a rien à réparer ici.";
						Link.l1 = "D'accord... Eh bien, je reviendrai plus tard...";
    			        Link.l1.go = "ship_tunning_not_now";
    			        break;
					}
                    s1 = "Fine, alright... What do we have here... Aha, " + XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName) + ".";
    			    if (sti(RealShips[sti(Pchar.Ship.Type)].Stolen) == true && !CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning"))
    			    {
    			        s1 = s1 + " Bah! This ship's been in too many hands. Yeah and there are a lot of scuffs. Do you have a corsair patent? Just joking... anyway, back to the matter.";
    			    }
                    dialog.Text = s1;
					Link.l1 = "Voyons voir ce que nous pouvons faire ici.";
    			    Link.l1.go = "ship_repair_HP";		    			    
    			    Link.l2 = "Arrêtez ! J'ai changé d'avis.";
    			    Link.l2.go = "ship_tunning_not_now_2";
			    }
			}
		break;
		
		case "ship_repair_HP":
			HPPrice 	= GetMaterialQtyRepair( pchar, 0 ); 
			Matherial1	= GetMaterialQtyRepair( pchar, 1 );
			Matherial2	= GetMaterialQtyRepair( pchar, 2 );
			Matherial3	= GetMaterialQtyRepair( pchar, 3 );
			Matherial4	= GetMaterialQtyRepair( pchar, 4 );
			
			s1 = "Let's have a look here at what we can do. At the moment, the ship's frame is " + shipCurHP + ". . The highest possible value is " + shipBaseHP;			
			s1 = s1 + ". In order to make a full repair, I need: ironwood - "+ Matherial1 + ", resin - " + Matherial2 + ", ship silk - " + Matherial3 + " ropes - " + Matherial4 + ".";
			s1 = s1 + " For this work I will charge: "+ HPPrice + " doubloons for the labor... My grandchildren have been calling me back to Europe for a long time. I don't want to come back empty-handed you know... So, that'll be all. And oh yes - the money up front.";
            dialog.Text = s1;
			Link.l1 = "Ça me semble bien. J'accepte les conditions. Tout sera livré comme convenu.";
			if(CheckItemMyCabin("gold_dublon") >= HPPrice)
			{
				Link.l1.go = "ship_repair_HP_start_0";
			}
			else
			{
				Link.l1.go = "ship_repair_HP_start";
			}			
			Link.l2 = "Non. Je ne suis pas satisfait de cela.";
			Link.l2.go = "ship_tunning_not_now";
		break;
		
		case "ship_repair_HP_start_0":
			dialog.Text = "Oui... Le paiement... Vous pouvez payer tout de suite ou envoyer un mousse au navire pour récupérer la somme nécessaire... Que souhaitez-vous faire ?";
			link.l1 = "Je paierai tout de suite.";
			link.l1.go = "ship_repair_HP_start";
			link.l2 = "Je vais envoyer un garçon de course. Je crois que j'avais un peu d'or qui traînait dans mes coffres...";
			link.l2.go = "ship_repair_HP_start_1";
		break;
		
		case "ship_repair_HP_start":
			HPPrice 	= GetMaterialQtyRepair( pchar, 0 ); 
			Matherial1	= GetMaterialQtyRepair( pchar, 1 );
			Matherial2	= GetMaterialQtyRepair( pchar, 2 );
			Matherial3	= GetMaterialQtyRepair( pchar, 3 );
			Matherial4	= GetMaterialQtyRepair( pchar, 4 );
		    amount = HPPrice;
		    if(GetCharacterItem(pchar,"gold_dublon") >= amount)
			{
				TakeNItems(pchar,"gold_dublon", -amount);				
			    NPChar.Repair.Money  		= amount;
			    NPChar.Repair.Matherial1 	= Matherial1; 
			    NPChar.Repair.Matherial2    = Matherial2;
				NPChar.Repair.Matherial3 	= Matherial3; 
			    NPChar.Repair.Matherial4    = Matherial4; 				 				
			    NPChar.Repair.ShipType      = Pchar.Ship.Type;
			    NPChar.Repair.ShipName      = RealShips[sti(Pchar.Ship.Type)].BaseName;
				NPChar.Repair.Delta         = shipBaseHP - shipCurHP;
			    			
				NextDiag.TempNode = "ship_repair_HP_again";
                dialog.text = "Splendide. J'attendrai les matériaux.";
			    link.l1 = "Je vais les rassembler...";
			    link.l1.go = "Exit";
			    
			    ReOpenQuestHeader("ShipRepair");
			    AddQuestRecord("ShipRepair", "t1");
				AddQuestUserData("ShipRepair", "sText",  "For capital repairing measures of  " + XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName) +
    " the shipmaster requires: ironwood - " + NPChar.Repair.Matherial1 + ", resin - "+ NPChar.Repair.Matherial2 + ", ship silk - " + NPChar.Repair.Matherial3 + " ropes - " + NPChar.Repair.Matherial4 + 
				". As a deposit we handed in " + NPChar.Repair.Money + " doubloons... He says he's about to take off to Europe. I think that old devil's lying.");
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_not_now";
                dialog.text = RandPhraseSimple("Je ne vois pas l'acompte...","Qu'est-ce que c'est que ce charabia...");
				link.l1 = "Je reviendrai plus tard.";
				link.l1.go = "Exit";								
			}
		break;
		
		case "ship_repair_HP_start_1":
			HPPrice 	= GetMaterialQtyRepair( pchar, 0 ); 
			Matherial1	= GetMaterialQtyRepair( pchar, 1 );
			Matherial2	= GetMaterialQtyRepair( pchar, 2 );
			Matherial3	= GetMaterialQtyRepair( pchar, 3 );
			Matherial4	= GetMaterialQtyRepair( pchar, 4 );
			AddTimeToCurrent(0, 30);
		    amount = HPPrice;
			GetItemMyCabin("gold_dublon", amount);
		    
			NPChar.Repair.Money  		= amount;
			NPChar.Repair.Matherial1 	= Matherial1; 
			NPChar.Repair.Matherial2    = Matherial2; 
			NPChar.Repair.Matherial3 	= Matherial3; 
			NPChar.Repair.Matherial4    = Matherial4; 				 							
			NPChar.Repair.ShipType      = Pchar.Ship.Type;
			NPChar.Repair.ShipName      = RealShips[sti(Pchar.Ship.Type)].BaseName;
			NPChar.Repair.Delta         = shipBaseHP - shipCurHP;
			    			
			NextDiag.TempNode = "ship_repair_HP_again";
			dialog.text = "Splendide. J'attendrai les matériaux.";
			link.l1 = "J'y vais...";
			link.l1.go = "Exit";
			
			ReOpenQuestHeader("ShipRepair");
			AddQuestRecord("ShipRepair", "t1");
			AddQuestUserData("ShipRepair", "sText",  "For capital repairing measures of  " + XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName) +
    " the shipmaster requires: ironwood - " + NPChar.Repair.Matherial1 + ", resin - "+ NPChar.Repair.Matherial2 + ", ship silk - " + NPChar.Repair.Matherial3 + " ropes - " + NPChar.Repair.Matherial4 + 
				". As a deposit we handed in " + NPChar.Repair.Money + " doubloons... He says he's about to take off to Europe. I think that old devil's lying.");
			
		break;
		
		case "ship_repair_HP_again":
		    if (sti(NPChar.Repair.ShipType) == sti(Pchar.Ship.Type) && NPChar.Repair.ShipName == RealShips[sti(Pchar.Ship.Type)].BaseName)
		    {
                NextDiag.TempNode = "ship_repair_HP_again";
				dialog.Text = "Le temps presse. As-tu ce que j'ai demandé ?";
			    Link.l1 = "Oui. J'ai réussi à obtenir quelque chose.";
			    Link.l1.go = "ship_repair_HP_again_2";
			    Link.l2 = "Non. Je suis encore dans mes recherches.";
			    Link.l2.go = "Exit";
			}
			else
			{
			    DeleteAttribute(NPChar, "Repair");
                NextDiag.TempNode = "ship_repair_again";
			    dialog.Text = "Il me semble, monsieur, que vous avez changé de navire depuis notre dernier accord. Nous devrons tout recompter à nouveau...";
			    Link.l1 = "Oui, c'est vrai. Quel dommage que le dépôt soit parti...";
			    Link.l1.go = "Exit";		    
			    AddQuestRecord("ShipRepait", "Lose");
			    CloseQuestHeader("ShipRepair");
			}
		break;
		
		case "ship_repair_HP_again_2":
			checkMatherial_repair(Pchar, NPChar, GOOD_SANDAL, 	1);
			checkMatherial_repair(Pchar, NPChar, GOOD_OIL, 		2);
			checkMatherial_repair(Pchar, NPChar, GOOD_SHIPSILK, 3);
			checkMatherial_repair(Pchar, NPChar, GOOD_ROPES, 	4);
		    if(sti(NPChar.Repair.Matherial1) < 1 && 
			   sti(NPChar.Repair.Matherial2) < 1 &&
			   sti(NPChar.Repair.Matherial3) < 1 &&
			   sti(NPChar.Repair.Matherial4) < 1)
			{
                NextDiag.TempNode = "ship_repair_again";
                dialog.text = "Tout ce dont j'avais besoin. Bien ! Temps de travailler...";
			    link.l1 = "D'accord, j'attendrai.";
			    link.l1.go = "ship_repair_HP_complite";
			}
			else
			{
				NextDiag.TempNode = "ship_repair_HP_again";
				dialog.Text = "Maintenant, ce que tu dois encore m'apporter, c'est : "+sti(NPChar.Repair.Matherial1)+" en bois de fer, "+sti(NPChar.Repair.Matherial2)+"résine, "+NPChar.Repair.Matherial3+"  de soie de navire, "+NPChar.Repair.Matherial4+"cordages.";
				link.l1 = "D'accord.";
				link.l1.go = "Exit";

                AddQuestRecord("ShipRepair", "t1");
				AddQuestUserData("ShipRepair", "sText", "Materials left: ironwood - "+ NPChar.Repair.Matherial1 + ", resin - "+ NPChar.Repair.Matherial2 + ", ship silk - " + NPChar.Repair.Matherial3 + " ropes - " + NPChar.Repair.Matherial4 + ".");
			}
		break;
		
		case "ship_repair_HP_complite":
		    AddTimeToCurrent(6, 30);
		    shTo = &RealShips[sti(Pchar.Ship.Type)];
			shTo.HP = sti(shTo.HP) + sti(NPChar.Repair.Delta);
		    DeleteAttribute(NPChar, "Repair");
			
			pchar.ship.hp = GetCharacterShipBaseHP(pchar);
			DeleteAttribute(pchar, "ship.hulls");
			DeleteAttribute(pchar, "ship.blots");		
			
            NextDiag.TempNode = "node_3";
			dialog.Text = "... Eh bien, c'est tout... Je vous garantis que ce sera assez difficile de démolir ce navire maintenant !";
			Link.l1 = "Merci ! Je préfère ne pas expérimenter, mais je vais te faire confiance.";
			Link.l1.go = "Exit";
			AddQuestRecord("ShipRepair", "End");
			CloseQuestHeader("ShipRepair");
		break;		
		
		///////////////////////////////  квестовые ветки
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Quelles questions avez-vous?","Comment puis-je vous aider ?"),"Tu as essayé de me poser une question il y a un moment...","Je n'ai jamais rencontré des gens avec une telle curiosité dans mon chantier naval ou ailleurs dans cette ville.","Pourquoi toutes ces questions? Mon travail est de construire des navires. Occupons-nous de cela.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("J'ai changé d'avis...","Je n'ai rien à dire pour le moment."),"Oumph, ou donc est passee ma memoire...","Hm, eh bien...","D'accord, laissons-nous...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (!CheckAttribute(npchar, "Step_Door"))
			{
				link.l2 = "Ecoute, j'aimerais passer, mais cette porte est verrouillée...";
				link.l2.go = "Step_Door_1";
			}

			if ((pchar.questTemp.different == "GiveShipLetters") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakAlexus"))
			{
				link.l1 = "Je voudrais proposer un accord.";
				link.l1.go = "Al_ShipLetters_1";// генератор  "Найденные документы"
				pchar.questTemp.different.GiveShipLetters.speakAlexus = true;
			}
			if(CheckAttribute(pchar, "questTemp.AlexClock") && pchar.questTemp.AlexClock == "go") // 280912
			{
				link.l1 = "Je suis ici concernant les matériaux pour la frégate.";
				link.l1.go = "clock";
			}
			if(CheckAttribute(pchar, "questTemp.Tieyasal") && pchar.questTemp.Tieyasal == "begin" && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				link.l1 = "Écoute, "+npchar.name+", avez-vous vu Miguel Dichoso sur l'Isla Tesoro récemment ?";
				link.l1.go = "tieyasal";
			}
		break;
//*************************** Генератор - "Найденные судовые документы" **************
		
		case "Al_ShipLetters_1":
			dialog.text = "Énoncez vos conditions.";
			s1 = "I lucked into finding an absolutely legal ship's documents packet that hasn't been called for search yet.";
			s1 = s1 + "The ship is afloat and it hasn't been excluded from the registry, don't worry. Just a blind fool-owner had the misfortune of losing these papers...";
			link.l1 = s1;
			link.l1.go = "Al_ShipLetters_2";			
		break;
		case "Al_ShipLetters_2":
			s1 = "Let me take a look! It really looks to be freshly filled out. Well, luck is in your favor, sir! ";
			s1 = s1 + "I actually needed a packet just like this. I, in turn, will offer you " + sti(pchar.questTemp.different.GiveShipLetters.price5) + " pesos. What do you say?";
			dialog.text = s1;
			link.l1 = "Véritable générosité royale ! Bien sûr, j'accepte !";
			link.l1.go = "Al_ShipLetters_3";
			link.l2 = "Non, je ne pense pas.";
			link.l2.go = "exit";
		break;
		case "Al_ShipLetters_3":
			TakeItemFromCharacter(pchar, "CaptainBook"); 
			addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price5)); 
			ChangeCharacterComplexReputation(pchar,"nobility", -1); 
			OfficersReaction("bad"); 
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //снимаем таймер 
			AddQuestRecord("GiveShipLetters", "9");			
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit(); 
		break;
		

//*************************** Открывание двери ***************************
 		case "Step_Door_1":
			dialog.text = "C'est exact. Si tu veux passer cette porte, tu dois me payer 20000 pesos. Si tu ne paies pas, je n'ouvrirai pas. Ce n'est pas une soupe populaire ici. Et je ne te conseille pas d'y aller de toute façon. Ce sera mieux pour toi si tu ne le fais pas...";
			if(sti(pchar.money) >= 20000)
			{
    			link.l1 = "Voici ton argent. Ouvre.";
    			link.l1.go = "Step_Door_2";
            }
            else
            {
    			link.l1 = "Je n'ai pas autant d'argent.";
    			link.l1.go = "Step_Door_3";
            }
            link.l2 = "Pas question ! Je ne paierai jamais pour une porte.";
    		link.l2.go = "exit";
		break;
		
 		case "Step_Door_2":
			npchar.Step_Door = true; // fix
			dialog.text = "Entrez. La porte est ouverte. Ne vous embêtez pas à me remercier !";
			link.l1 = "Non, pourquoi pas. Merci, "+npchar.name+"...";
			link.l1.go = "exit";
			LocatorReloadEnterDisable("Pirates_Shipyard", "reload2", false);
            AddMoneyToCharacter(pchar, -20000);
			pchar.quest.CloseBermudesDungeonDoor.win_condition.l1 = "MapEnter";
            pchar.quest.CloseBermudesDungeonDoor.win_condition = "CloseBermudesDungeonDoor";
		break;
		
 		case "Step_Door_3":
			dialog.text = "Eh bien, quand vous l'aurez, revenez. Sinon, ne tentez pas de me convaincre. C'est inutile...";
			link.l1 = "Ouh là, je suis complètement sans voix !";
			link.l1.go = "exit";
		break;
		
	// ------------------------------------------- хронометр Ђлекса ----------------------------------------------// Addon-2016 Jason замена дублонов на песо везде
		case "clock_begin":
			dialog.text = "Allez, ne soyez pas si sévère avec un vieil homme... J'ai vraiment besoin de votre aide, capitaine.";
			link.l1 = "Dis-moi, maître. Que vous est-il arrivé ?";
			link.l1.go = "clock_begin_1";
		break;
		
		case "clock_begin_1":
			sTotalTemp = "Steven Dodson";
			if (pchar.questTemp.Alex.Clock == "terrax") sTotalTemp = "Marcus Tyrex";
			dialog.text = "Notre nouveau chef des Frères de la Côte, "+sTotalTemp+", a commandé un nouveau navire, une frégate. Il a également imposé des tâches assez difficiles : coque renforcée, vitesse rapide et bonne manœuvrabilité, plus des canons du plus gros calibre possible\nJe comprends que le navire d'un amiral, pardon le chef de la confrérie, doit être quelque chose de spécial, mais cela signifie que j'ai besoin de matériaux spéciaux pour le construire. Vous en avez probablement entendu parler. Bois de fer, résine, soie marine et cordages...";
			link.l1 = "Alors racontez cela au chef des Frères. Ou êtes-vous méfiant que "+sTotalTemp+"te coupera la tête pour ça ?";
			link.l1.go = "clock_begin_2";
		break;
		
		case "clock_begin_2":
			dialog.text = "Je lui ai dit... Le fait est que notre nouveau chef n'a ni le temps ni l'occasion de trouver et d'apporter ces matériaux. Vous devez savoir à quel point c'est une rareté. Et je ne pourrai en aucun cas construire une frégate avec les caractéristiques dites sans eux.";
			link.l1 = "Et vous proposez probablement que je doive trouver des matériaux pour le navire ?";
			link.l1.go = "clock_begin_3";
		break;
		
		case "clock_begin_3":
			dialog.text = "Eh bien, oui. Vous êtes un bon ami de notre chef. "+sTotalTemp+" dit lui-même qu'il te doit beaucoup et qu'il exige toutes sortes de respect pour toi... Alors j'ai pensé : puisque tu es son ami, peut-être que tu ne serais pas contre l'aider ? Et en même temps : tu te rends compte dans quelle situation délicate je me trouve ? Tous les matériaux seront payés, "+sTotalTemp+"n'est pas avare avec son or.";
			link.l1 = "Je suis vraiment désolé, maître, mais je ne suis pas moins occupé que "+sTotalTemp+". J'ai bien peur que rassembler les matériaux ne prenne toute une éternité. Alors, tu ferais mieux de demander à quelqu'un d'autre.";
			link.l1.go = "clock_exit";
			link.l2 = "Eh bien, si "+sTotalTemp+"commandé un navire chez vous - alors bien sûr, j'essaierai d'aider. Nous sommes vraiment amis, et les amis doivent s'entraider. De combien de matériaux avez-vous besoin ?";
			link.l2.go = "clock_begin_4";
		break;
		
		case "clock_exit":
			dialog.text = "C'est vraiment dommage. C'est vraiment très dommage. Je comptais sur vous. Eh bien, comme on dit, non c'est non...";
			link.l1 = "... ";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.AlexClock");
		break;
		
		case "clock_begin_4":
			dialog.text = "Il me manque 100 unités de bois de fer, 150 conteneurs de résine, 110 rouleaux de soie de navire et 90 rouleaux de cordes de chanvre. Qu'en penses-tu ? Pourrais-tu me trouver tout cela en quatre mois ? Je ne pense pas avoir plus de temps.";
			link.l1 = "Je peux au moins essayer. Et quant au paiement ?";
			link.l1.go = "clock_begin_5";
		break;
		
		case "clock_begin_5":
			dialog.text = "Voici mes tarifs : bois de fer à 4000 pesos la pièce, résines à 1400 pesos le conteneur, soie à 2500 pesos le rouleau, et cordages à 1500 pesos la bobine. Et si vous m'apportez tout cela, vous recevrez un très joli cadeau de ma part.";
			link.l1 = "Qu'est-ce que c'est, je me demande ?";
			link.l1.go = "clock_begin_6";
		break;
		
		case "clock_begin_6":
			dialog.text = "Apportez-moi d'abord les matériaux. Mais je vous assure : cela vous sera fort utile, et la chose est unique. Il n'y en a pas d'autre dans les Caraïbes, ni dans le monde entier pour le moment. J'espère que cette petite étincelle de curiosité a éveillé votre intérêt pour rassembler les matériaux pour moi.";
			link.l1 = "Eh bien, vous êtes rusé comme un lutin, maître ! Très bien, vous avez conclu un marché.";
			link.l1.go = "clock_begin_7";
		break;
		
		case "clock_begin_7":
			dialog.text = "Je suis très heureux. J'attendrai avec impatience votre retour.";
			link.l1 = "J'espère que cela ne prendra pas trop longtemps...";
			link.l1.go = "clock_begin_8";
		break;
		
		case "clock_begin_8":
			DialogExit();
			pchar.questTemp.AlexClock = "go";
			npchar.quest.clock = "true";
			SetFunctionTimerCondition("AlexClock_Over", 0, 0, 122, false); // таймер
			AddQuestRecord("alex_clock", "1");
			// запоминаем переменные
			pchar.questTemp.AlexClock.Sandal = 100;
			pchar.questTemp.AlexClock.Oil = 150;
			pchar.questTemp.AlexClock.Shipsilk = 110;
			pchar.questTemp.AlexClock.Ropes = 90;
		break;
		
		case "clock":
			dialog.text = "Excellent ! Qu'avez-vous apporté aujourd'hui ?";
			if (GetSquadronGoods(pchar, GOOD_SANDAL) > 0 && !CheckAttribute(npchar, "quest.sandal"))
			{
				iSan = GetSquadronGoods(pchar, GOOD_SANDAL);
				link.l1 = "Bois de fer, en quantité de "+FindRussianQtyString(iSan)+".";
				link.l1.go = "sandal";
			}
			if (GetSquadronGoods(pchar, GOOD_OIL) > 0 && !CheckAttribute(npchar, "quest.oil"))
			{
				iOil = GetSquadronGoods(pchar, GOOD_OIL);
				link.l2 = "Résines, à hauteur de "+FindRussianQtyString(iOil)+".";
				link.l2.go = "oil";
			}
			if (GetSquadronGoods(pchar, GOOD_SHIPSILK) > 0 && !CheckAttribute(npchar, "quest.shipsilk"))
			{
				iSil = GetSquadronGoods(pchar, GOOD_SHIPSILK);
				link.l3 = "Soie de navire, en quantité de "+FindRussianQtyString(iSil)+".";
				link.l3.go = "shipsilk";
			}
			if (GetSquadronGoods(pchar, GOOD_ROPES) > 0 && !CheckAttribute(npchar, "quest.ropes"))
			{
				iRop = GetSquadronGoods(pchar, GOOD_ROPES);
				link.l4 = "Des cordages en chanvre, à hauteur de "+FindRussianQtyString(iRop)+".";
				link.l4.go = "ropes";
			}
			link.l5 = "Rien pour l'instant. Je voulais juste m'assurer que notre accord tient toujours.";
			link.l5.go = "exit";
		break;
		
		case "clock_1":
			if (CheckAttribute(npchar, "quest.sandal") && CheckAttribute(npchar, "quest.oil") && CheckAttribute(npchar, "quest.shipsilk") && CheckAttribute(npchar, "quest.ropes")) // все привез
			{
				dialog.text = "Magnifique ! J'ai tous les matériaux dans la quantité dont j'ai besoin. Merci mille fois pour votre aide, capitaine. Vous m'avez grandement dépanné.";
				link.l1 = "Oui, à tout moment, maître. Je suis également très satisfait : j'ai aidé un ami et j'ai gagné de l'argent. Et maintenant, revenons à notre conversation sur votre objet mystérieux que vous m'avez promis.";
				link.l1.go = "clock_2";
			}
			else
			{
				dialog.text = "Encore des surprises pour moi, capitaine ?";
				link.l1 = "Hélas, c'est tout pour l'instant. Continuez simplement à attendre.";
				link.l1.go = "exit";
				link.l2 = "Oui, j'ai encore une chose...";
				link.l2.go = "clock";
			}
		break;
		
		case "sandal": // бакаут
			amount = sti(pchar.questTemp.AlexClock.Sandal);
			iSan = GetSquadronGoods(pchar, GOOD_SANDAL);
			iTemp = amount-iSan;
			if (iTemp > 0) // ещё не все привез
			{
				iSum = 4000*iSan;
				dialog.text = "Très bien, d'accord. Je vais aussi avoir besoin "+FindRussianQtyString(amount)+"de bois de fer. Vous m'avez apporté "+FindRussianQtyString(iSan)+". . Alors, ce qu'il te reste à m'apporter, c'est "+FindRussianQtyString(iTemp)+". Très bien, au tarif de 4000 pesos par pièce, votre récompense s'élève à "+FindRussianMoneyString(iSum)+"S'il vous plaît, prenez-le.";
				link.l1 = "Merci! Vous aurez le reste bientôt.";
				link.l1.go = "clock_1";
				RemoveCharacterGoods(pchar, GOOD_SANDAL, iSan);
				pchar.questTemp.AlexClock.Sandal = iTemp; // столько осталось довезти
				AddQuestRecord("alex_clock", "2");
				AddQuestUserData("alex_clock", "sGood", "ironwood");
				AddQuestUserData("alex_clock", "sQty", FindRussianQtyString(iTemp));
			}
			else
			{
				iSum = 4000*amount;
				dialog.text = "Très bien, d'accord. Je vais aussi avoir besoin de "+FindRussianQtyString(amount)+"  de bois de fer. Vous m'avez apporté "+FindRussianQtyString(iSan)+". Alors, nous avons réglé l'affaire du bois de fer maintenant ! Très bien, au tarif de 4000 pesos par pièce, votre récompense s'élève à "+FindRussianMoneyString(iSum)+" S'il vous plaît, prenez-le.";
				link.l1 = "Merci !";
				link.l1.go = "clock_1";
				RemoveCharacterGoods(pchar, GOOD_SANDAL, amount);
				npchar.quest.sandal = "true";
				AddQuestRecord("alex_clock", "3");
				AddQuestUserData("alex_clock", "sGood", "ironwood");
			}
			AddMoneyToCharacter(pchar, iSum);
		break;
		
		case "oil": // смолы
			amount = sti(pchar.questTemp.AlexClock.Oil);
			iOil = GetSquadronGoods(pchar, GOOD_OIL);
			iTemp = amount-iOil;
			if (iTemp > 0) // ещё не все привез
			{
				iSum = 1400*iOil;
				dialog.text = "Très bien, d'accord. J'aurai aussi besoin de "+FindRussianQtyString(amount)+" résines. Vous m'avez apporté "+FindRussianQtyString(iOil)+"Alors, ce qu'il te reste à m'apporter, c'est "+FindRussianQtyString(iTemp)+"Très bien, au tarif de 1400 pesos par conteneur, votre récompense s'élève à "+FindRussianMoneyString(iSum)+" S'il vous plaît, prenez-le.";
				link.l1 = "Merci ! Vous aurez le reste bientôt.";
				link.l1.go = "clock_1";
				RemoveCharacterGoods(pchar, GOOD_OIL, iOil);
				pchar.questTemp.AlexClock.Oil = iTemp; // столько осталось довезти
				AddQuestRecord("alex_clock", "2");
				AddQuestUserData("alex_clock", "sGood", "resins");
				AddQuestUserData("alex_clock", "sQty", FindRussianQtyString(iTemp));
			}
			else
			{
				iSum = 1400*amount;
				dialog.text = "D'accord, très bien. J'aurais aussi besoin de "+FindRussianQtyString(amount)+" résines. Vous m'avez apporté "+FindRussianQtyString(iOil)+"Alors, nous avons maintenant pris soin des résines ! Très bien, au tarif de 1400 pesos par conteneur, votre récompense s'élève à "+FindRussianMoneyString(iSum)+"S'il vous plaît, prenez-le.";
				link.l1 = "Merci !";
				link.l1.go = "clock_1";
				RemoveCharacterGoods(pchar, GOOD_OIL, amount);
				npchar.quest.oil = "true";
				AddQuestRecord("alex_clock", "3");
				AddQuestUserData("alex_clock", "sGood", "resins");
			}
			AddMoneyToCharacter(pchar, iSum);
		break;
		
		case "shipsilk": // шёлк
			amount = sti(pchar.questTemp.AlexClock.Shipsilk);
			iSil = GetSquadronGoods(pchar, GOOD_SHIPSILK);
			iTemp = amount-iSil;
			if (iTemp > 0) // ещё не все привез
			{
				iSum = 2600*iSil;
				dialog.text = "D'accord, très bien. Je vais aussi avoir besoin de "+FindRussianQtyString(amount)+" de la soie. Tu m'as apporté "+FindRussianQtyString(iSil)+" Donc, ce qu'il te reste à m'apporter est "+FindRussianQtyString(iTemp)+"  Très bien, au tarif de 2600 pesos par pièce, votre récompense s'élève à "+FindRussianMoneyString(iSum)+" S'il vous plaît, prenez-le.";
				link.l1 = "Merci ! Vous aurez le reste bientôt.";
				link.l1.go = "clock_1";
				RemoveCharacterGoods(pchar, GOOD_SHIPSILK, iSil);
				pchar.questTemp.AlexClock.Shipsilk = iTemp; // столько осталось довезти
				AddQuestRecord("alex_clock", "2");
				AddQuestUserData("alex_clock", "sGood", "silk");
				AddQuestUserData("alex_clock", "sQty", FindRussianQtyString(iTemp));
			}
			else
			{
				iSum = 2600*amount;
				dialog.text = "D'accord, très bien. Je vais aussi avoir besoin "+FindRussianQtyString(amount)+" de la soie. Vous m'avez apporté "+FindRussianQtyString(iSil)+" . Alors, nous avons géré la soie maintenant ! Donc, au taux de 2600 pesos par pièce, votre récompense s'élève à "+FindRussianMoneyString(iSum)+"S'il vous plaît, prenez-le.";
				link.l1 = "Merci !";
				link.l1.go = "clock_1";
				RemoveCharacterGoods(pchar, GOOD_SHIPSILK, amount);
				npchar.quest.shipsilk = "true";
				AddQuestRecord("alex_clock", "3");
				AddQuestUserData("alex_clock", "sGood", "silk");
			}
			AddMoneyToCharacter(pchar, iSum);
		break;
		
		case "ropes": // канаты
			amount = sti(pchar.questTemp.AlexClock.Ropes);
			iRop = GetSquadronGoods(pchar, GOOD_ROPES);
			iTemp = amount-iRop;
			if (iTemp > 0) // ещё не все привез
			{
				iSum = 1500*iRop;
				dialog.text = "D'accord, très bien. Je vais aussi avoir besoin "+FindRussianQtyString(amount)+"cordes. Vous m'avez apporté "+FindRussianQtyString(iRop)+". Alors, ce qui te reste à m'apporter, c'est "+FindRussianQtyString(iTemp)+" . Donc, au tarif de 1500 pesos par pièce, votre récompense s'élève à "+FindRussianMoneyString(iSum)+" S'il vous plaît, prenez-le.";
				link.l1 = "Merci ! Vous aurez le reste bientôt.";
				link.l1.go = "clock_1";
				RemoveCharacterGoods(pchar, GOOD_ROPES, iRop);
				pchar.questTemp.AlexClock.Ropes = iTemp; // столько осталось довезти
				AddQuestRecord("alex_clock", "2");
				AddQuestUserData("alex_clock", "sGood", "ropes");
				AddQuestUserData("alex_clock", "sQty", FindRussianQtyString(iTemp));
			}
			else
			{
				iSum = 1500*amount;
				dialog.text = "Très bien, d'accord. Je vais aussi avoir besoin de "+FindRussianQtyString(amount)+" cordages. Vous m'avez apporté "+FindRussianQtyString(iRop)+". Alors, nous nous sommes déjà occupés des cordages. Très bien, au tarif de 1500 pesos par pièce, votre récompense s'élève à "+FindRussianMoneyString(iSum)+"S'il vous plaît, prenez-le.";
				link.l1 = "Merci !";
				link.l1.go = "clock_1";
				RemoveCharacterGoods(pchar, GOOD_ROPES, amount);
				npchar.quest.ropes = "true";
				AddQuestRecord("alex_clock", "3");
				AddQuestUserData("alex_clock", "sGood", "ropes");
			}
			AddMoneyToCharacter(pchar, iSum);
		break;
		
		case "clock_2":
			dialog.text = "Oui, oui... à propos de mon affaire, bien sûr. M-m-mmm... Hmmm... où ai-je... ahhh...";
			link.l1 = "Qu'y a-t-il, maître ? Vous avez l'air bien inquiet. Quelque chose ne va pas ? Des problèmes quelconques ?";
			link.l1.go = "clock_3";
		break;
		
		case "clock_3":
			dialog.text = "Précisément. Des problèmes. Récents. Maudits soient ces chasseurs de trésors...";
			link.l1 = "Calmez-vous, calmez-vous. Ce n'est pas bon à votre âge de vous inquiéter ainsi. Dieu vous en garde, vous pourriez être à un cheveu. Qui construirait alors la frégate pour le chef de la Fraternité ? Calmez-vous et expliquez-moi qui sont ces chasseurs de trésors ?";
			link.l1.go = "clock_4";
		break;
		
		case "clock_4":
			dialog.text = "Là-bas, près de ma table, il y a une porte. Elle mène directement à une vieille chambre forte. Dans cette chambre forte, dans l'un des coffres au trésor, je garde ma boîte métallique avec les objets qui étaient avec moi lorsque j'ai été aspiré par ce maudit tourbillon il y a vingt ans, et je me suis retrouvé ici...";
			link.l1 = "Quel entonnoir? De quoi parlez-vous?";
			link.l1.go = "clock_5";
		break;
		
		case "clock_5":
			dialog.text = "Ah, désolé pour mes fantaisies. Vieillir n'est pas facile, jeune homme. Pardonne-moi. Mais cela n'a pas d'importance. Ce qui est important, c'est qu'une boîte avec un cadeau pour toi se trouve dans le coffre qui est actuellement dans le donjon occupé par quelques vauriens. Ils ne sont pas des nôtres, ni d'Isla Tesoro. \nDes chasseurs de trésors, quelqu'un a dû leur dire que cet endroit est plein de trésors. Ils n'oseront pas se montrer ici, mais je suis trop effrayé pour leur rendre visite, tu vois? Leurs visages sont...";
			link.l1 = "Je vois. Ouvre ta porte. Je vais chasser tes invités indésirables.";
			link.l1.go = "clock_6";
		break;
		
		case "clock_6":
			dialog.text = "Juste comme ça ? Vous les battrez ? Seul ? Vous n'avez pas peur ? Nous avons toute une colonie qui se battra pour vous si vous le demandez seulement...";
			link.l1 = "Moins de paroles, plus d'action, maître. Ouvrez cette porte et laissez-moi faire le reste. Dans quel coffre gardez-vous vos affaires ?";
			link.l1.go = "clock_7";
		break;
		
		case "clock_7":
			dialog.text = "Juste au bout du couloir se trouve toute une collection de tonneaux en bois vides. Derrière eux, au sol, dans un endroit retiré, se trouve un petit coffre. J'ai cloué un cadenas dessus, donc je doute que ces intrus parviennent à y mettre leurs sales pattes même s'ils le trouvent. Tenez, prenez la clé.";
			link.l1 = "Je suis heureux que vous anticipiez. Attendez ici et ne partez nulle part.";
			link.l1.go = "clock_8";
		break;
		
		case "clock_8":
			DialogExit();
			GiveItem2Character(pchar, "key3"); 
			bDisableFastReload = true;//закрыть переход
			LocatorReloadEnterDisable("Pirates_Shipyard", "reload1_back", true);
			LocatorReloadEnterDisable("Pirates_Shipyard", "reload2", false);
			LAi_LocationDisableOfficersGen("Bermudes_Dungeon", true);//офицеров не пускать
			pchar.quest.Alex_Chest.win_condition.l1 = "location";
			pchar.quest.Alex_Chest.win_condition.l1.location = "Bermudes_Dungeon";
			pchar.quest.Alex_Chest.function = "AlexClock_Chest";
			pchar.quest.AlexClock_Over.over = "yes"; //снять прерывание
			pchar.questTemp.AlexClock = "chest";
			AddQuestRecord("alex_clock", "3");
		break;
		
		case "clock_complete":
			dialog.text = "Ils vous ont simplement écouté et sont partis ?";
			link.l1 = "C'est exact. Ils se sont révélés être des gars polis et sympathiques. Je leur ai expliqué que leur présence effraie le célèbre vieux constructeur de navires et par respect pour votre âge avancé, ils ont quitté les lieux. Vous pouvez y aller sans souci.";
			link.l1.go = "clock_complete_1";
		break;
		
		case "clock_complete_1":
			dialog.text = "Ah-ha, tu te moques d'un vieil homme ! Très bien. Donne-moi ma boîte et je l'ouvrirai pour te donner le dispositif que tu as gagné loyalement.";
			link.l1 = "S'il vous plaît, prenez-le...";
			link.l1.go = "clock_complete_2";
		break;
		
		case "clock_complete_2":
			RemoveItems(pchar, "alexs_chest", 1);
			dialog.text = "Gratitude ! Ouvrons-le. Tenez, prenez ceci. Minuteur mécanique automatique, personne ne fabrique de tels appareils ici et personne ne le fera pendant les trois cents prochaines années... euh, mes excuses, veuillez pardonner le vieil homme. Tout ce que je dis, c'est que cette chose est unique\nElle fait tout le travail elle-même, vous n'aurez pas besoin de stupides sabliers et ainsi de suite. Pas d'erreurs ! Gardez-le simplement à l'abri des coups directs et de l'eau, sinon vous le perdrez. Même un singe peut utiliser ce minuteur.";
			link.l1 = "Regarde ça ! Je n'ai jamais vu quelque chose d'aussi miraculeux de toute ma vie ! Merci, maître.";
			link.l1.go = "clock_complete_3";
		break;
		
		case "clock_complete_3":
			GiveItem2Character(pchar, "clock3");
			Log_Info("You've received an automatic mechanical timer");
			SetAlchemyRecipeKnown("sextant2");
			PlaySound("interface\important_item.wav");
			dialog.text = "Je vous en prie. Maintenant, vous saurez toujours quelle heure il est. Ne me demandez pas où je l'ai obtenu. Je ne vous le dirai pas.";
			link.l1 = "Tout le monde a ses secrets, n'est-ce pas maître ? Très bien... garde tes secrets et je ne me mêlerai pas de tes affaires. Merci pour le cadeau !";
			link.l1.go = "clock_complete_4";
		break;
		
		case "clock_complete_4":
			dialog.text = "Et merci pour votre aide, capitaine. Venez me voir de temps en temps. N'oubliez pas un vieux charpentier de marine.";
			link.l1 = "Comme si je pouvais t'oublier... Quoi qu'il en soit, je ferai certainement cela, Alexus le Maître. Adieu !";
			link.l1.go = "clock_complete_5";
		break;
		
		case "clock_complete_5":
			DialogExit();
			bDisableFastReload = false;
			LocatorReloadEnterDisable("Pirates_Shipyard", "reload2", true);
			LocatorReloadEnterDisable("Pirates_Shipyard", "reload1_back", false);
			LocatorReloadEnterDisable("Bermudes_Dungeon", "reload2_back", false);
			LAi_LocationDisableOfficersGen("Bermudes_Dungeon", false);
			AddQuestRecord("alex_clock", "5");
			CloseQuestHeader("alex_clock");
			DeleteAttribute(pchar, "questTemp.AlexClock");
			// belamour legendary edition на пару с Акулой
			pchar.questTemp.SharkGoldFleet.KGBB = true;
			if(CheckAttribute(pchar,"questTemp.SharkFrigate")) SetTimerCondition("SharkGoldFleet", 0, 0, 30, false);
		break;
	// <-- хронометр Алекса
		
		// город майя
		case "tieyasal":
			dialog.text = "Aha, Miguel ! Mon vieil ami. Je me souviens de lui. Il me posait des questions sur chaque petit détail encore et encore. Mais comment allais-je lui expliquer comment une radio était construite à l'intérieur alors qu'il n'avait même pas vu un simple télégraphe ?";
			link.l1 = "Quoi ?.. De quoi parlez-vous, maître ?";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "Oh, désolé, jeune homme. Ne fais pas trop attention à mes paroles... Notre curieux Michel a satisfait sa curiosité et a disparu. Il y a seulement trois jours, nous avons bavardé.";
			link.l1 = "Où est Miguel en ce moment, si cela ne vous dérange pas que je pose la question?";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			dialog.text = "Qui sait. Peut-être qu'il fait ses affaires à Sharptown ou peut-être qu'il a déjà quitté Isla Tesoro.";
			link.l1 = "Je vois. Merci, maître !";
			link.l1.go = "tieyasal_3";
		break;
		
		case "tieyasal_3":
			DialogExit();
			npchar.quest.tieyasal = "true";
		break;
		
		// Калеуче
		case "FDM":
			if(CheckAttribute(npchar, "quest.FDM_secondtime"))
				dialog.text = "Encore avec ton 'navire fantôme'... Sache ceci - je ne travaille dessus que dans l'espoir qu'il devienne quelque chose de décent. Sinon, je ne l'aurais même pas touché. Je pense que tout le monde en mer partage un avis similaire. Que veux-tu en faire cette fois-ci ?";
			else	
				dialog.text = "Ah, le 'navire fantôme'! Les mères utilisent ton galion pour effrayer les garnements. Et tu as décidé de garder ce maudit vaisseau au lieu de le couler! Les marins tremblent lorsqu'ils voient ton navire à l'horizon... Alors, que veux-tu en faire?";
			if (!CheckAttribute(npchar, "quest.FDM_cabin"))
			{
				link.l1 = "J'aime l'idée des petits lâches qui ont la frousse. Mais l'intérieur me rend triste. As-tu vu la cabine ? On dirait un cercueil. Toute cette moisissure et cette poussière. Je veux la réparer. Pouvez-vous faire cela, maître ?";
				link.l1.go = "FDM_cabin";
			}
			if (!CheckAttribute(npchar, "quest.FDM_sails"))
			{
				link.l2 = "J'en ai assez de ces haillons noirs déchirés. Je l'admets, ils attrapent le vent aussi bien que les voiles ordinaires mais la vue... Dégueulasse. Je veux des voiles blanches comme neige. Vous êtes partant, maître?";
				link.l2.go = "FDM_sails";
			}
			
			if (!CheckAttribute(npchar, "quest.FDM_hull"))
			{
				link.l3 = "Eh bien, je pense qu'il est temps de la transformer en quelque chose de convenable. Le navire est bon, l'équipage y est habitué, mais ce n'est tout simplement pas digne pour un capitaine respectable de naviguer sur un vaisseau qui peut faire peur aux adultes, sans parler des enfants. Je veux le reconstruire complètement pour que les autres capitaines l'envient quand ils voient mon navire, au lieu de se signer. Et à qui d'autre devrais-je m'adresser pour cela, sinon au meilleur constructeur naval de l'archipel ?";
				link.l3.go = "FDM_hull";
			}
		break;
		
		case "FDM_cabin":
			dialog.text = "Pourquoi pas ? Mes mains sont encore habiles. Votre galion est immense, je peux même créer une cabine royale comme celles qu'ils construisent sur les vaisseaux de guerre et les navires de ligne. Ou nous pouvons garder une cabine standard. Le choix vous appartient ?";
			link.l1 = "Construisez la cabine du vaisseau de ligne ! Ils mourront tous de jalousie...";
			link.l1.go = "FDM_cabin_m";
			link.l2 = "Pas de place pour des luxes excessifs. Gardez le standard.";
			link.l2.go = "FDM_cabin_s";
		break;
		
		case "FDM_cabin_m":
			dialog.text = "D'accord. Dix coffres de doublons et ce sera fait en cinq jours.";
			link.l1 = "Marché conclu !";
			link.l1.go = "FDM_cabin_m1";
			link.l2 = "Dix coffres ? Mille cinq cents doublons ? Hm, j'ai besoin de temps pour réfléchir à de telles dépenses...";
			link.l2.go = "exit";
		break;
		
		case "FDM_cabin_s":
			dialog.text = "D'accord. Sept coffres de doublons et ce sera fait en cinq jours.";
			link.l1 = "Marché conclu !";
			link.l1.go = "FDM_cabin_s1";
			link.l2 = "Sept coffres ? Plus de mille doublons ? Hm, j'ai besoin de temps pour réfléchir à de telles dépenses...";
			link.l2.go = "exit";
		break;
		
		case "FDM_cabin_m1":
			iTemp = GetCharacterItem(pchar, "Chest");
			npchar.quest.FDM_cabin = 10;
			npchar.quest.FDM_cabin.type = "Cabin_Huge";
			dialog.text = "Bien, j'attendrai le paiement.";
			if (iTemp > 0)
			{
				link.l1 = "J'ai des coffres avec moi. Voyons voir. Ici, "+FindRussianQtyString(iTemp)+".";
				link.l1.go = "FDM_cabin_pay";
			}
			else
			{
				link.l1 = "Je dois aller mettre des pièces dans les coffres.";
				link.l1.go = "FDM_cabin_wait";
			}
		break;
		
		case "FDM_cabin_s1":
			iTemp = GetCharacterItem(pchar, "Chest");
			npchar.quest.FDM_cabin = 7;
			npchar.quest.FDM_cabin.type = "Cabin";
			dialog.text = "Bien, j'attendrai le paiement.";
			if (iTemp > 0)
			{
				link.l1 = "J'ai des coffres avec moi. Voyons voir. Ici, "+FindRussianQtyString(iTemp)+".";
				link.l1.go = "FDM_cabin_pay";
			}
			else
			{
				link.l1 = "Je dois aller mettre des pieces dans les coffres.";
				link.l1.go = "FDM_cabin_wait";
			}
		break;
		
		case "FDM_cabin_wait":
			DialogExit();
			npchar.quest.FDM_full = "cabin";
		break;
		
		case "FDM_cabin_pay":
			iTemp = GetCharacterItem(pchar, "Chest");
			amount = sti(npchar.quest.FDM_cabin)-iTemp;
			Log_Info("You have given chests to Master Alexus");
			PlaySound("interface\important_item.wav");
			if (amount <= 0) // всё принес
			{
				RemoveItems(pchar, "chest", sti(npchar.quest.FDM_cabin));
				dialog.text = "Alors, tu devais m'apporter "+FindRussianQtyString(sti(npchar.quest.FDM_cabin))+" coffres, vous avez apporté "+FindRussianQtyString(iTemp)+"J'ai le paiement. Maintenant, c'est à mon tour. Va te promener. Ne t'inquiète pas, je ferai de mon mieux.";
				link.l1 = "Bien...";
				link.l1.go = "FDM_cabin_do";
			}
			else
			{
				RemoveItems(pchar, "chest", iTemp);
				dialog.text = "Alors, tu devais m'apporter "+FindRussianQtyString(sti(npchar.quest.FDM_cabin))+" coffres, vous avez apporté "+FindRussianQtyString(iTemp)+". "+FindRussianQtyString(amount)+" coffres restants.";
				link.l1 = "Très bien, maître.";
				link.l1.go = "FDM_cabin_wait";
				npchar.quest.FDM_cabin = amount;
			}
		break;
		
		case "FDM_cabin_do":
			DialogExit();
			SetLaunchFrameFormParam("Five days later..."+ NewStr() +"Master Alexus has done his job", "", 0, 5);
			WaitDate("", 0, 0, 5, 0, 10); //крутим время
			LaunchFrameForm();
			RefreshLandTime();
			RecalculateJumpTable();
			Whr_UpdateWeather();
			shTo = &RealShips[sti(Pchar.Ship.Type)];
			shTo.CabinType = npchar.quest.FDM_cabin.type;
			if (CheckAttribute(npchar, "quest.FDM_sails")) npchar.quest.FDM_full = "done";
			else DeleteAttribute(npchar, "quest.FDM_full");
		break;
		
		case "FDM_sails":
			dialog.text = "Bien sûr, je peux faire ça ! Eh bien, eh bien... Cela signifie que nous devons jeter tous les vieux chiffons sales et installer de nouvelles voiles propres en coton. Il y a beaucoup de travail à faire ici. Cent mille pesos pour le travail et les matériaux. Marché conclu ?";
			if (sti(Pchar.money) >= 100000)
			{
				link.l1 = "Bien sûr, cela me convient. Marché conclu !";
				link.l1.go = "FDM_sails_do";
			}
			link.l2 = "Hm. Je suppose que je dois y réfléchir...";
			link.l2.go = "exit";
		break;
		
		case "FDM_sails_do":
			AddMoneyToCharacter(pchar, -100000);
			dialog.text = "Bien. J'ai les pièces, il est temps de faire mon travail. Promenez-vous jusqu'à ce que ce soit fait et ne vous inquiétez pas.";
			link.l1 = "Bien...";
			link.l1.go = "FDM_sails_done";
		break;
		
		case "FDM_sails_done":
			DialogExit();
			SetLaunchFrameFormParam("Two days later..."+ NewStr() +"Master Alexus has done his job", "", 0, 5);
			WaitDate("", 0, 0, 2, 0, 10); //крутим время
			LaunchFrameForm();
			RefreshLandTime();
			RecalculateJumpTable();
			Whr_UpdateWeather();
			SetShipSailsFromFile(pchar, "ships/parus_silk.tga");
			SetSailsColor(pchar, 0);//белый хлопковый парус
			npchar.quest.FDM_sails = "true";
			if (CheckAttribute(npchar, "quest.FDM_cabin")) npchar.quest.FDM_full = "done";
		break;
		//--> Xenon
		case "FDM_hull":
			dialog.text = "Eh bien, je suis enfin content d'entendre ça. Et c'est vrai - tu sembles être un bon gars, mais tu navigues sur je ne sais quoi. Mais laisse-moi te prévenir d'emblée, ce travail ne prendra pas que quelques heures, et cela te coûtera une jolie somme. ";
			link.l1 = "D'accord, peux-tu etre un peu plus precis ?";
			link.l1.go = "FDM_hull_01";
		break;

		case "FDM_hull_01":
			dialog.text = "D'accord, calculons... Pour une révision complète de la coque du navire, j'aurai besoin de 150 unités de bois de fer, 130 cordages, 170 rouleaux de soie de navire, et 200 barils de résine. Je prendrai 250 mille pesos pour tout cela. Et ne me regarde pas comme ça - la plupart de cet argent ira de toute façon au travail ! Après tout, nous ne reconstruisons pas une tartane.";
			link.l1 = "Je ne pense pas. Je ne suis pas prêt à transporter une telle quantité de matériaux tout en payant un quart de million pour le travail. Je suppose que je vais continuer à naviguer dessus tel quel.";
			link.l1.go = "FDM_hull_thinking";
			link.l2 = "Eh, que ne ferions-nous pas pour notre navire...Très bien, c'est un marché.";
			link.l2.go = "FDM_hull_02";
		break;

		case "FDM_hull_02":
			dialog.text = "Bien, moins de paroles, plus d'action. J'attendrai l'argent de ta part pour pouvoir commencer à acheter tout ce dont j'ai besoin. Une fois que j'aurai l'argent, tu pourras commencer à m'apporter les matériaux. Et je me mettrai à travailler sur ton navire.";
			if(sti(pchar.money) >= 250000)
			{
    			link.l1 = "Eh bien, l'argent n'est pas un problème. Je l'ai sur moi. Tenez, maître.";
    			link.l1.go = "FDM_hull_waitmaterials";
            }
            else
            {
    			link.l1 = "Pour l'instant, je n'ai pas cette somme d'argent. Attendez un peu, je vais vous l'apporter.";
    			link.l1.go = "FDM_hull_waitmoney";
            }
		break;

		case "FDM_hull_waitmaterials":
			addMoneyToCharacter(pchar, -250000);
			npchar.quest.FDMsandal = 0;
			npchar.quest.FDMoil = 0;
			npchar.quest.FDMshipsilk = 0;
			npchar.quest.FDMropes = 0;
			AddQuestRecord("renovate_fdm", "1");

			npchar.quest.FDM_hull = "hull_waitmaterials";
			dialog.text = "Pas peur de te promener dans une colonie de pirates avec une telle somme, hehe ? Bon, je plaisante, ce sont tous des gens honnêtes, à leur manière. Maintenant, j'attends les matériaux. Pour rappel, tu devras apporter un total de 150 bois de fer, 130 rouleaux de cordages, 170 rouleaux de soie de navire, et 200 barils de résine.";
			link.l1 = "Tiens bon, je t'apporterai tes matériaux.";
			link.l1.go = "exit";
		break;

		case "FDM_hull_checkmaterials":
			dialog.text = "Très bien ! Qu'est-ce que vous m'apportez aujourd'hui ?";
			if (GetSquadronGoods(pchar, GOOD_SANDAL) > 0 && sti(npchar.quest.FDMsandal) < 150)
			{
				iSan = GetSquadronGoods(pchar, GOOD_SANDAL);
				link.l1 = "Bois de fer en quantité de "+FindRussianQtyString(iSan)+".";
				link.l1.go = "FDM_sandal";
			}
			if (GetSquadronGoods(pchar, GOOD_OIL) > 0 && sti(npchar.quest.FDMoil) < 200)
			{
				iOil = GetSquadronGoods(pchar, GOOD_OIL);
				link.l2 = "Résine en quantité de "+FindRussianQtyString(iOil)+".";
				link.l2.go = "FDM_oil";
			}
			if (GetSquadronGoods(pchar, GOOD_SHIPSILK) > 0 && sti(npchar.quest.FDMshipsilk) < 170)
			{
				iSil = GetSquadronGoods(pchar, GOOD_SHIPSILK);
				link.l3 = "Envoyer de la soie à hauteur de "+FindRussianQtyString(iSil)+".";
				link.l3.go = "FDM_shipsilk";
			}
			if (GetSquadronGoods(pchar, GOOD_ROPES) > 0 && sti(npchar.quest.FDMropes) < 130)
			{
				iRop = GetSquadronGoods(pchar, GOOD_ROPES);
				link.l4 = "Cordages en quantité de "+FindRussianQtyString(iRop)+".";
				link.l4.go = "FDM_ropes";
			} 
			link.l5 = "Rien encore. Je voulais juste m'assurer que l'affaire tient toujours.";
			link.l5.go = "exit";
		break;

		case "FDM_hull_checkmaterials_1":
			if (sti(npchar.quest.FDMsandal) > 149 && sti(npchar.quest.FDMoil) > 199 && sti(npchar.quest.FDMshipsilk) > 169 && sti(npchar.quest.FDMropes) > 129)
			{
				dialog.text = "Magnifique ! Tous les matériaux sont comptabilisés. Maintenant, laissez-moi vous débarrasser de ce monstre. Enfin, il aura l'aspect qu'il mérite.";
				link.l1 = "D'accord, assez de grognements, maître. J'attends impatiemment le résultat.";
				link.l1.go = "FDM_hull_building";
			}
			else
			{
				dialog.text = "As-tu autre chose pour égayer ma journée, Capitaine ?";
				link.l1 = "Hélas, c'est tout pour l'instant.";
				link.l1.go = "exit";
				link.l2 = "Oui, j'ai autre chose pour vous...";
				link.l2.go = "FDM_hull_checkmaterials";
			}
		break;

		case "FDM_sandal": // бакаут
			amount = 150 - sti(npchar.quest.FDMsandal);
			iSan = GetSquadronGoods(pchar, GOOD_SANDAL);
			iTemp = amount-iSan;
			if (iTemp > 0) 
			{
				dialog.text = "Voyons voir... J'ai besoin de "+FindRussianQtyString(amount)+"de bois de fer. Vous avez apporté "+FindRussianQtyString(iSan)+". de bois de fer. Par conséquent, vous devez encore m'apporter "+FindRussianQtyString(iTemp)+".";
				link.l1 = "Merci ! Je vous apporterai le reste bientôt.";
				link.l1.go = "FDM_hull_checkmaterials_1";
				RemoveCharacterGoods(pchar, GOOD_SANDAL, iSan);
				npchar.quest.FDMsandal = sti(npchar.quest.FDMsandal) + iSan;
				AddQuestRecord("renovate_fdm", "2");
				AddQuestUserData("renovate_fdm", "sGood", "ironwood");
				AddQuestUserData("renovate_fdm", "sQty", FindRussianQtyString(iTemp));
			}
			else
			{
				dialog.text = "Voyons voir... J'ai encore besoin de "+FindRussianQtyString(amount)+"de bois de fer. Vous m'avez apporté "+FindRussianQtyString(iSan)+" Par conséquent, nous avons terminé avec le bois de fer !";
				link.l1 = "Merci !";
				link.l1.go = "FDM_hull_checkmaterials_1";
				RemoveCharacterGoods(pchar, GOOD_SANDAL, amount);
				npchar.quest.FDMsandal = sti(npchar.quest.FDMsandal) + amount;
				AddQuestRecord("renovate_fdm", "3");
				AddQuestUserData("renovate_fdm", "sGood", "ironwood"); 
			}
		break;

		case "FDM_oil": // смолы
			amount = 200 - sti(npchar.quest.FDMoil);
			iOil = GetSquadronGoods(pchar, GOOD_OIL);
			iTemp = amount-iOil;
			if (iTemp > 0) 
			{
				dialog.text = "Voyons voir... J'ai besoin de "+FindRussianQtyString(amount)+" de résine. Vous avez apporté "+FindRussianQtyString(iOil)+" Par conséquent, vous devez encore m'apporter "+FindRussianQtyString(iTemp)+".";
				link.l1 = "Merci ! Je vous apporterai le reste bientôt.";
				link.l1.go = "FDM_hull_checkmaterials_1";
				RemoveCharacterGoods(pchar, GOOD_OIL, iOil);
				npchar.quest.FDMoil = sti(npchar.quest.FDMoil) + iOil;
				AddQuestRecord("renovate_fdm", "2");
				AddQuestUserData("renovate_fdm", "sGood", "resin");
				AddQuestUserData("renovate_fdm", "sQty", FindRussianQtyString(iTemp));
			}
			else
			{
				dialog.text = "Voyons voir... J'ai encore besoin de "+FindRussianQtyString(amount)+" de résine. Vous m'avez apporté "+FindRussianQtyString(iOil)+"Par conséquent, nous avons terminé avec la résine !";
				link.l1 = "Merci !";
				link.l1.go = "FDM_hull_checkmaterials_1";
				RemoveCharacterGoods(pchar, GOOD_OIL, amount);
				npchar.quest.FDMoil = makeint(npchar.quest.FDMoil) + amount;
				AddQuestRecord("renovate_fdm", "3");
				AddQuestUserData("renovate_fdm", "sGood", "resin");
			}
		break;

		case "FDM_shipsilk": // шёлк
			amount = 170 - sti(npchar.quest.FDMshipsilk);
			iSil = GetSquadronGoods(pchar, GOOD_SHIPSILK);
			iTemp = amount-iSil;
			if (iTemp > 0) 
			{
				dialog.text = "Voyons voir... J'ai besoin de "+FindRussianQtyString(amount)+" de soie de navire. Vous avez apporté "+FindRussianQtyString(iSil)+" Par conséquent, il vous faut encore m'apporter "+FindRussianQtyString(iTemp)+".";
				link.l1 = "Merci ! Je vous apporterai le reste bientôt";
				link.l1.go = "FDM_hull_checkmaterials_1";
				RemoveCharacterGoods(pchar, GOOD_SHIPSILK, iSil);
				npchar.quest.FDMshipsilk = sti(npchar.quest.FDMshipsilk) + iSil;
				AddQuestRecord("renovate_fdm", "2");
				AddQuestUserData("renovate_fdm", "sGood", "ship silk");
				AddQuestUserData("renovate_fdm", "sQty", FindRussianQtyString(iTemp));
			}
			else
			{
				dialog.text = "Voyons voir... J'ai encore besoin de "+FindRussianQtyString(amount)+" de soie de navire. Par conséquent, il vous reste à me rapporter "+FindRussianQtyString(iSil)+"Par conséquent, nous avons terminé avec la soie de navire";
				link.l1 = "Merci !";
				link.l1.go = "FDM_hull_checkmaterials_1";
				RemoveCharacterGoods(pchar, GOOD_SHIPSILK, amount);
				npchar.quest.FDMshipsilk = sti(npchar.quest.FDMshipsilk) + amount;
				AddQuestRecord("renovate_fdm", "3");
				AddQuestUserData("renovate_fdm", "sGood", "ship silk"); 
			}
		break;

		case "FDM_ropes": // канаты
			amount = 170 - sti(npchar.quest.FDMropes);
			iRop = GetSquadronGoods(pchar, GOOD_ROPES);
			iTemp = amount-iRop;
			if (iTemp > 0) 
			{
				dialog.text = "Voyons voir... J'ai besoin de "+FindRussianQtyString(amount)+" de cordages. Vous avez apporté "+FindRussianQtyString(iRop)+"Donc, tu dois encore m'apporter "+FindRussianQtyString(iTemp)+".";
				link.l1 = "Merci ! Je vous donnerai le reste bientôt";
				link.l1.go = "FDM_hull_checkmaterials_1";
				RemoveCharacterGoods(pchar, GOOD_ROPES, iRop);
				npchar.quest.FDMropes = sti(npchar.quest.FDMropes) + iRop;
				AddQuestRecord("renovate_fdm", "2");
				AddQuestUserData("renovate_fdm", "sGood", "ropes");
				AddQuestUserData("renovate_fdm", "sQty", FindRussianQtyString(iTemp));
			}
			else
			{
				dialog.text = "Voyons voir... J'ai besoin de  "+FindRussianQtyString(amount)+" de cordages. Vous avez apporté "+FindRussianQtyString(iRop)+"Par conséquent, nous en avons fini avec les cordages !";
				link.l1 = "Merci!";
				link.l1.go = "FDM_hull_checkmaterials_1";
				RemoveCharacterGoods(pchar, GOOD_ROPES, amount);
				npchar.quest.FDMropes = sti(npchar.quest.FDMropes) + amount;
				AddQuestRecord("renovate_fdm", "3");
				AddQuestUserData("renovate_fdm", "sGood", "ropes");
			}
		break;

		case "FDM_hull_thinking":
			DialogExit();
			npchar.quest.FDM_secondtime = true;
		break;

		case "FDM_hull_waitmoney":
			DialogExit();
			npchar.quest.FDM_hull = "hull_waitmoney";
		break;

		case "FDM_hull_givemoney":
			dialog.text = "Eh bien, as-tu apporté l'argent";
			if(sti(pchar.money) >= 250000)
			{
    			link.l2 = "Oui, je l'ai fait. 250 000 pesos, comme convenu.";
    			link.l2.go = "FDM_hull_waitmaterials";
            }
            else
            {
    			link.l1 = "Pas encore, attends, maître.";
    			link.l1.go = "exit";
            }
		break;

		case "FDM_hull_building":
			DialogExit();
			SetLaunchFrameFormParam("Five days passed..."+ NewStr() +"Master Alexus completed the job", "", 0, 5);
			WaitDate("", 0, 0, 5, 0, 10); //Pass time
			LaunchFrameForm();
			RefreshLandTime();
			RecalculateJumpTable();
			Whr_UpdateWeather();
			RealShips[sti(Pchar.Ship.Type)].BaseType = SHIP_RENOVATED_FDM;
			RealShips[sti(Pchar.Ship.Type)].Name = "NewFlyingdutchman1";
			RealShips[sti(Pchar.Ship.Type)].BaseName = "NewFlyingdutchman";
			/* RealShips[sti(Pchar.Ship.Type)].CannonsQuantity = 58;
			RealShips[sti(Pchar.Ship.Type)].CannonsQuantityMax = 58;
			RealShips[sti(Pchar.Ship.Type)].CannonsQuantityMin = 58;
			RealShips[sti(Pchar.Ship.Type)].rcannon = 24;
			RealShips[sti(Pchar.Ship.Type)].lcannon = 24;
			RealShips[sti(Pchar.Ship.Type)].fcannon = 6;
			RealShips[sti(Pchar.Ship.Type)].bcannon = 4; */
			if(Get_My_Cabin() == "My_Cabin") RealShips[sti(Pchar.Ship.Type)].CabinType = "Cabin";	
			else RealShips[sti(Pchar.Ship.Type)].CabinType = "Cabin_Huge";
			SetShipSailsFromFile(pchar, "ships/parus_silk.tga");
			SetSailsColor(pchar, 0);//White cotton sail
			RealShips[sti(Pchar.Ship.Type)].HP = GetCharacterShipBaseHP(pchar);
			pchar.ship.hp = GetCharacterShipBaseHP(pchar);
			DeleteAttribute(pchar, "ship.hulls");
			DeleteAttribute(pchar, "ship.blots");	
			CloseQuestHeader("renovate_fdm");
		break;
		//<-- Xenon
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

void checkMatherial_repair(ref Pchar, ref NPChar, int good, int goodType)
{
	int amount;
	string Matherial = "Matherial" + goodType;
	amount = GetSquadronGoods(Pchar, good) - sti(NPChar.Repair.(Matherial));
	
	if (amount < 0)
    {
		amount = amount + sti(NPChar.Repair.(Matherial));
    }
    else
    {
		amount = sti(NPChar.Repair.(Matherial));
    }
    RemoveCharacterGoods(Pchar, good, amount);
    NPChar.Repair.(Matherial) = sti(NPChar.Repair.(Matherial)) - amount;
}

int GetMaterialQtyRepair( ref _chr, int MaterialNum )
{
	if ( sti(_chr.Ship.Type) == SHIP_NOTUSED) return 0;
	
	int   	shipCurHP   = sti(RealShips[sti(_chr.Ship.Type)].HP);
	int   	shipBaseHP	= sti(RealShips[sti(_chr.Ship.Type)].BaseHP);	
	int   	shipClass   = sti(RealShips[sti(_chr.Ship.Type)].Class);
	int     shipWeight  = CWT2Tonnes(sti(RealShips[sti(_chr.Ship.Type)].Weight));
	int     HPPrice     = shipWeight * (1.2 - makefloat(shipCurHP)/makefloat(shipBaseHP));
	int     modifier    = (2 * MOD_SKILL_ENEMY_RATE) + sti(RealShips[sti(_chr.Ship.Type)].MinCrew)/2 + 1;	

	float   fQuest 	= 1.0;
	if(CheckAttribute(&RealShips[sti(_chr.Ship.Type)], "QuestShip")) 
	{
		fQuest  = 1.3;
		HPPrice = HPPrice * 2;
	}					
	
	int     Matherial1 = makeint(fQuest * (10 + MOD_SKILL_ENEMY_RATE) * (7 - shipClass) / 2) + rand(modifier);
	int     Matherial2 = makeint(fQuest * (10 + MOD_SKILL_ENEMY_RATE) * (7 - shipClass) / 2) + rand(modifier);
	int     Matherial3 = makeint(fQuest * (10 + MOD_SKILL_ENEMY_RATE) * (7 - shipClass) / 2) + rand(modifier);
	int     Matherial4 = makeint(fQuest * (10 + MOD_SKILL_ENEMY_RATE) * (7 - shipClass) / 2) + rand(modifier);
		
	if(MaterialNum == 0) return HPPrice;	
	if(MaterialNum == 1) return Matherial1;
	if(MaterialNum == 2) return Matherial2;
	if(MaterialNum == 3) return Matherial3;
	if(MaterialNum == 4) return Matherial4;
	
	return 0;
}
