// разговор с капитаном на палубе  Boal
//homo 25/06/06
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, Diag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);
	//belamour рыбацкое судно
	int i, iTemp, iQty;
	string sTemp;
    //homo Осады
    aref aData;
    makearef(aData, NullCharacter.Siege);
    string sCap, sGroup;
    string fort;
	bool bOk, bOk1, bOk2;

    if (CheckAttribute(aData, "nation"))
    {
	    sCap = NationShortName(sti(aData.nation))+"SiegeCap_";
	    sGroup = "Sea_"+sCap+"1";
	    
	   // string myships  = GetCompanionQuantity(PChar);
       // string escships = Group_GetCharactersNum(sGroup);
        
        switch(sti(aData.conation))
        {
            case 0:  fort = "English fort"; break;
            case 1:  fort = "French fort"; break;
            case 2:  fort = "Spanish fort"; break;
            case 3:  fort = "Dutch fort"; break;
            case 4:  fort = "Pirate fort"; break;
        }
        int ifortPower = sti(colonies[FindColony(aData.colony)].FortValue);
        int fortDamage = CheckFortInjuri();
        int SquadronDamage = CheckSquadronInjuri();
        
    }

    int iMoney;
	ref sld;
    
    if (CheckNPCQuestDate(npchar, "Card_date"))
	{
		SetNPCQuestDate(npchar, "Card_date");
		npchar.money = 3000 + rand(10) * makeint(100 * sti(PChar.rank) * (10.0 / MOD_SKILL_ENEMY_RATE));
	}
	else
	{
		if(sti(npchar.money) > CAP_MAX_MONEY || sti(npchar.money) < CAP_MIN_MONEY) 	
		{
			npchar.money = CAP_MIN_MONEY + rand(CAP_NORM);
		}
	}
    //homo 26/06/06
	ProcessCommonDialogRumors(NPChar, Link, Diag);
	switch(Dialog.CurrentNode)
	{
        case "Exit":
			DialogExit();
			Diag.CurrentNode = Diag.TempNode;
		break;
		
		case "First time":
			if (!bDisableMapEnter)
			{
				//--> Jason эскорт 2 уровень
				if (CheckAttribute(PChar, "questTemp.WPU.Escort.LevelUp_1WM") && pchar.questTemp.WPU.Escort == "begin" && NPChar.id == "WMCaptain")
				{
					dialog.text = "Bonjour, capitaine. Nom de Dieu, tu n'as aucune idée de combien je suis heureux de te voir!";
					link.l1 = "Salut. Permettez-moi de me présenter - "+GetFullName(PChar)+". Je suis ravi de vous voir vivant et en pleine forme aussi, je suis venu ici spécifiquement pour vous chercher - et votre navire.";
					link.l1.go = "WM_Captain";
					break;
				}
				if (CheckAttribute(PChar, "questTemp.WPU.Escort.LevelUp_1WM") && pchar.questTemp.WPU.Escort == "wait" && NPChar.id == "WMCaptain")
				{
					dialog.text = "Avez-vous apporté le matériel que j'ai demandé ?";
					if (sti(pchar.questTemp.WPU.Escort.Planks) - GetSquadronGoods(pchar, GOOD_PLANKS) <= 0 && sti(pchar.questTemp.WPU.Escort.Sailcloth) - GetSquadronGoods(pchar, GOOD_SAILCLOTH) <= 0 && sti(pchar.questTemp.WPU.Escort.Linen) - GetSquadronGoods(pchar, GOOD_COTTON) <= 0)
					{
						link.l1 = "Oui. Tout ce dont vous avez besoin pour réparer votre navire est dans ma cale.";
						link.l1.go = "WM_Captain_5";
					}
					else
					{
						link.l1 = "Non, je travaille encore dessus.";
						link.l1.go = "exit";
					}
					break;
				}
				if (CheckAttribute(PChar, "questTemp.WPU.Escort.LevelUp_1VSP") && pchar.questTemp.WPU.Escort == "toCap" && NPChar.id == "WMCaptain")
				{
					dialog.text = "Ahoy, "+GetAddress_Form(NPChar)+". Mon nom est "+GetFullName(NPChar)+", je suis le capitaine de ce navire. Permettez-moi d'exprimer ma plus sincère gratitude pour votre aide dans un combat avec cette maudite racaille pirate - si vous n'aviez pas interféré, les choses auraient pu mal tourner pour nous. Vous nous avez réellement sauvés, bon sang !";
					link.l1 = "Ce n'était rien,  "+GetAddress_FormToNPC(NPChar)+". Permettez-moi de me présenter - "+GetFullName(PChar)+", je suis venu à vous à la demande du maître de port "+XI_ConvertString("Colonie"+pchar.questTemp.WPU.Escort.StartCity+"Gén")+". Il m'a informé sur les malheurs de votre caravane et m'a envoyé trouver votre navire.";
					link.l1.go = "VSP_Captain";
					break;
				}
				//<-- эскорт 2 уровень
				
				if(CheckAttribute(NPChar, "surrendered"))
				{
					Pchar.GenQuest.MoneyForCaptureShip = makeint(Group_GetLiveCharactersNum( GetGroupIDFromCharacter(NPChar)))*(8 - sti(RealShips[sti(NPChar.Ship.Type)].Class))*(1+rand(10))*500);
					if(HasShipTrait(pchar, "trait14")) Pchar.GenQuest.MoneyForCaptureShip = makeint(sti(Pchar.GenQuest.MoneyForCaptureShip) * 1.35);
					dialog.text = "Attends, tu pourrais me tuer de cette façon. Qu'est-ce que tu veux de moi ?";
					//выкуп
					link.l1 = "Réglons cette affaire pacifiquement. Une rançon, je suppose, sera la meilleure décision. Une somme de "+Pchar.GenQuest.MoneyForCaptureShip+" des pesos me conviendront bien, "+GetAddress_FormToNPC(NPChar)+". Et après ça, tu peux te perdre !";
					link.l1.go = "surrender1";
					// обираем до нитки
					link.l2 = "Je voudrais voir ce que tu as dans ta cale. Et après cela, toi et ton équipage pouvez aller où vous voulez.";
					link.l2.go = "surrender2";
					break;
				}
				
				//Голландский Гамбит, против всех
				if (CheckAttribute(PChar, "questTemp.HWIC.Self") && pchar.questTemp.HWIC.Self == "MeetingStivesant" && NPChar.id == "Stivesant")
				{
					dialog.text = "Bonjour, monsieur. Heureux de vous voir. Le Capitaine Longway viendra probablement à bord plus tard, n'est-ce pas?";
					link.l1 = "Bon après-midi, monsieur Stuyvesant. Permettez-moi de me présenter - "+GetFullName(pchar)+". Longway ne viendra pas, il n'est pas sur le 'Meifeng'.";
					link.l1.go = "Stivesant_1";
					pchar.quest.QuestShipsTerms_Over.over = "yes"; //снять таймер
					break;
				}
				if (CheckAttribute(PChar, "questTemp.HWIC.Self") && pchar.questTemp.HWIC.Self == "FleutOnTrinidad" && NPChar.id == "Keller")
				{
					DelLandQuestMark(npchar);
					dialog.text = "Ahoy, capitaine. Qu'est-ce qui vous amène à ma flûte?";
					link.l1 = "Bon après-midi, monsieur Keller. Permettez-moi de me présenter - "+GetFullName(pchar)+". Je suis venu chercher votre aide pour une affaire inhabituelle.";
					link.l1.go = "Keller_1";
					break;
					//Голландский гамбит
				}
				// belamour рыбацкое судно -->
				if(npchar.id == "FishingBoatCap")
				{
					if(!CheckAttribute(pchar, "GenQuest.FishingBoatSecondTime"))
					{
						Dialog.text = TimeGreeting()+", "+GetAddress_Form(NPChar)+"! Je suis le capitaine de "+GetFullName(NPChar)+". Qu'est-ce qui vous amène à bord de mon navire?";
						link.l1 = "Et bonjour à vous. Que faites-vous dans cette baie?";
						link.l1.go = "FishingBoat";
						break;
					}
					else
					{
						Diag.CurrentNode = "first time";
						dialog.text = "Y a-t-il autre chose que vous aimeriez discuter ?";
						link.l1 = "Je voulais"+GetSexPhrase("","")+" pour découvrir les dernières nouvelles de l'archipel.";
						link.l1.go = "rumours_capitan";
						if(CheckAttribute(pchar,"GenQuest.FishingBoatDialogEnb"))
						{
							link.l2 = "Montrez-moi encore, s'il vous plaît, quel genre de babioles vous avez en vente. ";
							link.l2.go = "Торговля";
							if(pchar.GenQuest.FishingBoatDialogEnb != "no special goods")
							{
								link.l3 = "Hmm, peut-être chercher plus dans la cale - peut-être quelque chose sera trouvé à vendre?";
								link.l3.go = "Особые товары";
							}
						}
						link.l4 = "Rien de spécial, je suis juste venu te saluer!";
						link.l4.go = "exit";	
						break;
					}
				}
				// <-- рыбацкое судно
				
				//belamour legendary edition диалоги, если герой имеет звания и заслуги перед отечеством -->
				// генерал губернатор
				if(CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE)
				{
					Dialog.text = "Gouverneur Général, Votre Grâce, salutations ! Que puis-je faire pour vous ?";
					link.l1 = "J'ai du travail pour toi !";
					link.l1.go = "quests";
					link.l2 = "Rien de spécial, je suis juste venu te saluer !";
					link.l2.go = "exit";
					break;
				}
				// вице адмирал
				if(isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && sti(Items[sti(pchar.EquipedPatentId)].Nation) == npchar.nation)
				{
					Dialog.text = "Bienvenue à bord de mon navire, Vice-amiral ! Que puis-je faire pour vous ?";
					link.l1 = "J'ai du travail pour toi !";
					link.l1.go = "quests";
					link.l2 = "Rien de spécial, je suis juste venu pour te saluer !";
					link.l2.go = "exit";
					break;
				}
				// Офицер с патентом
				if(IsOfficerFullEquip() && sti(Items[sti(pchar.EquipedPatentId)].Nation) == npchar.nation)
				{
					Dialog.text = "Heureux de voir un camarade de travail, Capitaine ! Comment puis-je vous aider ?";
					link.l1 = "J'ai une affaire pour vous !";
					link.l1.go = "quests";
					link.l2 = "Rien de spécial, je suis juste venu vous saluer!";
					link.l2.go = "exit";
					break;
				}			
				// <-- legendary edition
                if (CheckAttribute(NPChar, "EncType")  && NPChar.EncType == "war")
                {
    			    Dialog.text = TimeGreeting()+", "+GetAddress_Form(NPChar)+"! Je suis "+GetFullName(NPChar)+" - capitaine d'un navire appartenant à la "+NationKingsName(NPChar)+". flotte. Qu'est-ce qui t'a amené à bord de mon navire?";
    			}
    			else
                {
    			    Dialog.text = TimeGreeting()+", "+GetAddress_Form(NPChar)+"! Je suis capitaine "+GetFullName(NPChar)+". Qu'est-ce qui vous a amené à bord de mon navire?";
    			}
    			link.l1 = "Mon nom est "+GetFullName(Pchar)+". J'ai quelques affaires avec toi!";
    			link.l1.go = "quests";
                link.l2 = "Oh, rien, juste "+GetSexPhrase("est venu","est venu")+" pour vous saluer !";
    			link.l2.go = "exit";
            }
            else
            {
                Dialog.text = "N'avez-vous pas remarqué, , "+GetAddress_Form(NPChar)+", que nous sommes en pleine bataille? Ce n'est pas le moment de parler!";
    			link.l1 = "Absolument d'accord! Je retournerai à mon navire.";
    			link.l1.go = "exit";
            }
			Diag.TempNode = "first time";
 		break;

        case "quests":
			// belamour рыбацкое судно -->
			if(npchar.id == "FishingBoatCap")
			{
				if(!CheckAttribute(pchar, "GenQuest.FishingBoatSecondTime"))
				{
					Dialog.text = TimeGreeting()+", "+GetAddress_Form(NPChar)+"! Je suis le capitaine de "+GetFullName(NPChar)+". Qu'est-ce qui vous amène à bord de mon navire?";
					link.l1 = "Et bonjour à vous. Que faites-vous dans cette baie?";
					link.l1.go = "FishingBoat";
					break;
				}
				else
				{
					dialog.text = "Y a-t-il autre chose que vous aimeriez discuter ?";
					link.l1 = "Je voulais"+GetSexPhrase("","")+" pour découvrir les dernières nouvelles de l'archipel.";
					link.l1.go = "rumours_capitan";
					if(CheckAttribute(pchar,"GenQuest.FishingBoatDialogEnb"))
					{
						link.l2 = "Montrez-moi encore une fois, s'il vous plaît, quel genre de bibelots vous avez à vendre. ";
						link.l2.go = "Торговля";
						if(pchar.GenQuest.FishingBoatDialogEnb != "no special goods")
						{
							link.l3 = "Hmm, peut-être chercher plus dans la cale - peut-être quelque chose sera trouvé à vendre?";
							link.l3.go = "Особые товары";
						}
					}
					link.l4 = "Rien de spécial, je suis juste venu vous saluer !";
					link.l4.go = "exit";	
					break;
				}
			}
			// <-- рыбацкое судно
            if (!CheckAttribute(NPChar, "MainCaptanId")  || NPChar.MainCaptanId == pchar.GenQuest.CaptainId)
            {
                Dialog.text = "Je vous écoute très attentivement,  "+GetAddress_Form(NPChar)+".";
                link.l1 = "Je veux savoir les dernières nouvelles de l'archipel.";
                //homo 25/06/06
                link.l1.go = "rumours_capitan";
                //belamour legendary edition 
				bOk1 = isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && GetNationRelation(npchar.nation, sti(Items[sti(pchar.EquipedPatentId)].Nation)) != RELATION_ENEMY;
				bOk2 = CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && GetNationRelation(npchar.nation, FRANCE) != RELATION_ENEMY;
				bOk = bOk1 || bOk2;
                if (CheckAttribute(NPChar, "EncGroupName") && !bOk) // только для фантомов грабеж
                {
                    link.l2 = RandPhraseSimple("Avez-vous la moindre idée de qui je suis ? Je pense qu'il est parfaitement clair que mes canons peuvent transformer votre vieille baignoire en passoire. Réglons cela de manière pacifique. Une rançon me semble une bonne décision.","Rien que nous... et la mer... Que pensez-vous d'apaiser mes hommes... pour votre propre sécurité ?.");
                    link.l2.go = "Talk_board";
                }
                if (CheckAttribute(NPChar, "Ship.Mode") && NPChar.Ship.Mode == "Trade")
                {
	           		link.l3 = "D'où venez-vous ?";
	    			link.l3.go = "price_1";
	    			link.l4 = "Tu veux faire du commerce?";
	    			link.l4.go = "Trade_1";
    			}
				//--> квест мэра, поиски пирата
				if (CheckAttribute(pchar, "GenQuest.DestroyPirate"))
				{
	    			link.l6 = "Je cherche un navire pirate agissant dans ces eaux. Avez-vous vu quelque chose de suspect?";
	    			link.l6.go = "MQ_step_1";
				}
				//<-- квест мэра, поиски пирата
    			link.l5 = "Tu veux te détendre ?";
			    link.l5.go = "Play_Game";
                link.l9 = "Je suppose que je devrais y aller.";
    			link.l9.go = "exit";
			}
			else
			{
                Dialog.text = "Je ne suis pas autorisé à traiter avec vous. Parlez au commandant de notre escadron. Son nom est  "+GetFullName(characterFromID(NPChar.MainCaptanId))+", vous pouvez le trouver sur le "+XI_ConvertString(RealShips[sti(characters[GetCharacterIndex(NPChar.MainCaptanId)].Ship.Type)].BaseName)+" '"+characters[GetCharacterIndex(NPChar.MainCaptanId)].Ship.Name+".'.";
                link.l1 = "Merci. Je ferai comme tu dis.";
                link.l1.go = "exit";
                Diag.TempNode = "Go_away_Good";
			}
        break;
        case "Trade_1":
			dialog.text = "Pourquoi pas?";
			link.l1 = "Allons voir les marchandises.";
			link.l1.go = "Trade_2";
			link.l2 = "J'ai changé d'avis.";
			link.l2.go = "exit";
		break;
		
		case "Trade_2":
            Partition_GetCargoCostCoeff("after");
			FillShipStore(NPChar);
	    	pchar.shiptrade.character = NPChar.id;
   			Diag.CurrentNode = Diag.TempNode;
		    DialogExit();
		    DeleteAttribute(pchar, "PriceList.StoreManIdx"); // не вести лог по кораблям
		    LaunchStore(SHIP_STORE);
		break;
		
        case "Play_Game":
			dialog.text = "Que suggérez-vous ?";
			link.l1 = "Veux-tu jouer à un jeu de cartes pour de l'argent sérieux ?";
			link.l1.go = "Card_Game";
   			link.l2 = "Que diriez-vous de lancer quelques dés au poker-joker?";
			link.l2.go = "Dice_Game";
			link.l10 = "Je suis désolé, mais j'ai des affaires à faire.";
			link.l10.go = "exit";
		break;
        // карты -->
        case "Card_Game":
            if (!CheckNPCQuestDate(npchar, "Card_date_Yet") || isBadReputation(pchar, 30) || GetCharacterSkillToOld(pchar, SKILL_LEADERSHIP) < rand(3))
            {
                SetNPCQuestDate(npchar, "Card_date_Yet");
                dialog.text = "Je ne jouerai pas aux dés avec des escrocs !";
    			link.l1 = "Comme vous voulez.";
    			link.l1.go = "exit";
			}
			else
			{
                dialog.text = "Pourquoi pas? Je ne refuserais certainement pas une pause...";
    			link.l1 = "Excellent.";
    			link.l1.go = "Cards_begin";
    			link.l2 = "Quelles sont les règles ?";
    			link.l2.go = "Cards_Rule";
			}
		break;

		case "Cards_Rule":
   			dialog.text = CARDS_RULE;
			link.l1 = "Eh bien, commençons alors!";
			link.l1.go = "Cards_begin";
			link.l3 = "Non, ce n'est pas pour moi...";
			link.l3.go = "exit";
		break;

		case "Cards_begin":
			Dialog.text = "D'accordons d'abord sur le pari.";
			link.l1 = "Jouons pour 100 pesos.";
			link.l1.go = "Cards_Node_100";
			link.l2 = "Jouons pour 500 pesos.";
			link.l2.go = "Cards_Node_500";
			link.l3 = "Je suppose que je devrais partir.";
			link.l3.go = "exit";
		break;

		case "Cards_Node_100":
		    if (sti(pchar.Money) < 300)
		    {
                dialog.text = "Tu plaisantes ou quoi? Tu n'as pas d'argent!";
                link.l1 = "Cela arrive.";
			    link.l1.go = "exit";
			    break;
		    }
		    if (sti(npchar.Money) < 300)
		    {
                dialog.text = "Eh bien, c'est assez, ou je n'aurai pas assez d'argent pour entretenir le navire...";
                link.l1 = "Dommage.";
			    link.l1.go = "exit";
			    break;
		    }
   			dialog.text = "D'accord, jouons pour 100 pièces.";
			link.l1 = "Commençons !";
			link.l1.go = "Cards_begin_go";
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
            pchar.GenQuest.Cards.iRate     = 100;
            pchar.GenQuest.Cards.SitType   = false;
		break;

		case "Cards_Node_500":
		    if (sti(pchar.Money) < 1500)
		    {
                dialog.text = "Tu plaisantes ou quoi? Tu n'as pas 1500 pesos!";
                link.l1 = "Je les trouverai!";
			    link.l1.go = "exit";
			    break;
		    }
		    if (sti(npchar.Money) < 1500)
		    {
                dialog.text = "Non, ces paris me feront certainement finir à la fin.";
                link.l1 = "Comme vous voulez.";
			    link.l1.go = "exit";
			    break;
		    }
   			dialog.text = "D'accord, jouons pour 500 pièces.";
			link.l1 = "Commençons !";
			link.l1.go = "Cards_begin_go";
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
            pchar.GenQuest.Cards.iRate     = 500;
            pchar.GenQuest.Cards.SitType   = false;
		break;

		case "Cards_begin_go":
            Diag.CurrentNode = Diag.TempNode;
			DialogExit();
            LaunchCardsGame();
		break;
	    // карты <--
	    //  Dice -->
        case "Dice_Game":
            if (!CheckNPCQuestDate(npchar, "Dice_date_Yet") || isBadReputation(pchar, 30) || GetCharacterSkillToOld(pchar, SKILL_LEADERSHIP) < rand(3))
            {
                SetNPCQuestDate(npchar, "Dice_date_Yet");
                dialog.text = "Je ne vais pas jouer aux jeux de hasard avec des escrocs!";
    			link.l1 = "Comme vous voulez.";
    			link.l1.go = "exit";
			}
			else
			{
				if (CheckNPCQuestDate(npchar, "Dice_date_begin"))
				{
					dialog.text = "Pourquoi pas! Se détendre est toujours bon pour la santé... mais pas toujours pour le porte-monnaie...";
	    			link.l1 = "Excellent.";
	    			link.l1.go = "Dice_begin";
	    			link.l2 = "Quelles sont les règles de notre jeu?";
	    			link.l2.go = "Dice_Rule";
    			}
    			else
    			{
					dialog.text = "Non, j'en ai fini pour aujourd'hui. J'ai des choses à faire.";
	    			link.l1 = "Comme vous voulez.";
	    			link.l1.go = "exit";
				}
			}
		break;

		case "Dice_Rule":
   			dialog.text = DICE_RULE;
			link.l1 = "Eh bien, commençons alors!";
			link.l1.go = "Dice_begin";
			link.l3 = "Non, ce n'est pas pour moi...";
			link.l3.go = "exit";
		break;

		case "Dice_begin":
			Dialog.text = "D'accordons d'abord sur le pari.";
			link.l1 = "Jouons pour 50 pesos.";
			link.l1.go = "Dice_Node_100";
			link.l2 = "Jouons pour 200 pesos.";
			link.l2.go = "Dice_Node_500";
			link.l3 = "Je suppose que je devrais y aller.";
			link.l3.go = "exit";
		break;

		case "Dice_Node_100":
			//belamour legendary edition 
			bOk1 = isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && GetNationRelation(npchar.nation, sti(Items[sti(pchar.EquipedPatentId)].Nation)) != RELATION_ENEMY;
			bOk2 = CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && GetNationRelation(npchar.nation, FRANCE) != RELATION_ENEMY;
			bOk = bOk1 || bOk2;
            if (!CheckDiceGameSmallRate() && !bOk)
		    {
                dialog.text = "Vous êtes bien connu en tant que"+GetSexPhrase("tricheur","tricheur")+".. Je ne lancerai jamais les dés avec toi.";
                link.l1 = "C'est tous des mensonges ! Eh bien, soit.";
			    link.l1.go = "exit";
			    break;
		    }

			if (sti(pchar.Money) < 300)
		    {
                dialog.text = "Tu plaisantes ou quoi? Tu n'as pas d'argent!";
                link.l1 = "Ça arrive.";
			    link.l1.go = "exit";
			    break;
		    }
		    if (sti(npchar.Money) < 300)
		    {
                dialog.text = "C'est assez ! J'en ai fini avec les jeux d'argent - avant qu'ils ne me traitent de peculateur et me forcent à quitter le navire.";
                link.l1 = "Dommage.";
			    link.l1.go = "exit";
			    break;
		    }
   			dialog.text = "D'accord, jouons pour 50 pièces.";
			link.l1 = "Commençons !";
			link.l1.go = "Dice_begin_go";
			pchar.GenQuest.Dice.npcharIdx = npchar.index;
            pchar.GenQuest.Dice.iRate     = 50;
            pchar.GenQuest.Dice.SitType   = false;
		break;

		case "Dice_Node_500":
			//belamour legendary edition 
			bOk1 = isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && GetNationRelation(npchar.nation, sti(Items[sti(pchar.EquipedPatentId)].Nation)) != RELATION_ENEMY;
			bOk2 = CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && GetNationRelation(npchar.nation, FRANCE) != RELATION_ENEMY;
			bOk = bOk1 || bOk2;
            if (!CheckDiceGameSmallRate() && !bOk)
		    {
                dialog.text = "Vous êtes bien connu en tant que"+GetSexPhrase("tricheur","tricheur")+". Je ne jouerai jamais aux dés avec toi.";
                link.l1 = "C'est tous des mensonges! Eh bien, soit.";
			    link.l1.go = "exit";
			    break;
		    }
			if (!CheckDiceGameBigRate())
		    {
                dialog.text = "J'ai entendu dire que vous êtes un très bon joueur. Je ne jouerai pas à des enjeux élevés avec vous.";
                link.l1 = "Devrions-nous diminuer le pari, peut-être?";
			    link.l1.go = "Dice_Node_100";
				link.l2 = "Je suis désolé, mais je dois partir.";
			    link.l2.go = "exit";
			    break;
		    }

			if (sti(pchar.Money) < 1500)
		    {
                dialog.text = "Tu plaisantes ou quoi? Tu n'as pas 1500 pesos!";
                link.l1 = "Je les trouverai!";
			    link.l1.go = "exit";
			    break;
		    }
		    if (sti(npchar.Money) < 1500)
		    {
                dialog.text = "Non, ces paris me ruineront certainement à la fin.";
                link.l1 = "Comme vous voulez.";
			    link.l1.go = "exit";
			    break;
		    }
   			dialog.text = "D'accord, jouons pour 200 pièces.";
			link.l1 = "Commençons !";
			link.l1.go = "Dice_begin_go";
			pchar.GenQuest.Dice.npcharIdx = npchar.index;
            pchar.GenQuest.Dice.iRate     = 200;
            pchar.GenQuest.Dice.SitType   = false;
		break;

		case "Dice_begin_go":
            SetNPCQuestDate(npchar, "Dice_date_begin");
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
            LaunchDiceGame();
		break;
	    // Dice <--
        case "price_1":
			if (CheckNPCQuestDate(npchar, "trade_date"))
			{
                SetNPCQuestDate(npchar, "trade_date");
				iMoney = findPriceStoreMan(NPChar);
	            if (iMoney == -1)
	            {
	                Dialog.Text = "Pourquoi voulez-vous savoir? C'est ma vie privée.";
					Link.l1 = "Comme vous voulez.";
					Link.l1.go = "exit";
	            }
	            else
	            {
                    sld = &Characters[iMoney];
                    pchar.PriceList.ShipStoreIdx = iMoney;
                    
					Dialog.Text = "Je viens de la ville de"+GetCityName(sld.City)+".";
					Link.l1 = "Quels sont les prix des marchandises au magasin local?";
					Link.l1.go = "price_2";
					Link.l9 = "Je devrais partir.";
					Link.l9.go = "exit";
				}
			}
			else
			{
                Dialog.Text = "Je vous ai déjà tout dit. Ne me dérangez pas pour rien.";
				Link.l1 = "Ouais, tu as raison. Adieu.";
				Link.l1.go = "exit";
            }
		break;
		
		case "price_2":
            sld = &Characters[sti(pchar.PriceList.ShipStoreIdx)];
			SetPriceListByStoreMan(&Colonies[FindColony(sld.City)]);
			Dialog.Text = "Voici... (vous avez reçu la liste des prix)..";
			Link.l1 = "Merci beaucoup!";
			Link.l1.go = "exit";
			PlaySound("interface\important_item.wav");
		break;
		
        case "Talk_board":
            if ((Group_GetCharactersNum(NPChar.EncGroupName) - Group_GetDeadCharactersNum(NPChar.EncGroupName)) > GetCompanionQuantity(PChar) && rand(11) > GetCharacterSkillToOld(PChar, SKILL_FORTUNE))
            {
                Dialog.text = "Ha-ha-ha! Bonne blague, j'ai plus de navires. Retourne à ton navire et coule avec lui.";
                link.l1 = "Plus ne signifie pas plus fort, mon pote.";
                link.l1.go = "Boarding";
            }
            else
            {
                if(rand(21) > (GetSummonSkillFromNameToOld(PChar, SKILL_GRAPPLING) + GetSummonSkillFromNameToOld(PChar, SKILL_LEADERSHIP)) )
                {
                    Dialog.text = "Capitaine, vous n'auriez pas dû faire vos sales affaires à bord de mon navire. Mais je ferai preuve de miséricorde et vous laisserai retourner sur votre navire pour y couler avec lui.";
                    link.l1 = "Nous verrons, qui va devenir la nourriture des requins aujourd'hui !";
                    link.l1.go = "Boarding";
                }
                else
                {
                    Pchar.GenQuest.MoneyForCaptureShip = makeint(100 + (Group_GetCharactersNum(NPChar.EncGroupName) - Group_GetDeadCharactersNum(NPChar.EncGroupName))*(8 - sti(RealShips[sti(NPChar.Ship.Type)].Class))*(1+rand(10))*500);
					if(HasShipTrait(pchar, "trait14")) Pchar.GenQuest.MoneyForCaptureShip = makeint(sti(Pchar.GenQuest.MoneyForCaptureShip) * 1.35);
                    Dialog.text = RandSwear()+"Oui, j'ai entendu parler de vos outrages. Soit, mais souvenez-vous "+XI_ConvertString(NationShortName(sti(NPChar.nation))+"chasseur")+" ne le laissera pas impuni !";
                    link.l1 = "Excellente. Une somme de "+Pchar.GenQuest.MoneyForCaptureShip+" pesos me conviendront parfaitement, "+GetAddress_FormToNPC(NPChar)+".";
                    link.l1.go = "Capture";
                    link.l2 = "Oh, ne t'en fais pas. Je plaisantais simplement"+GetSexPhrase("","")+"!";
                    link.l2.go = "exit";
                }
            }
            // тут нужен учёт запрета повторного наезда
            Diag.TempNode = "Go_away";
			sld = characterFromId(pchar.GenQuest.CaptainId);
            sld.talk_date_Go_away =  lastspeakdate(); // boal злопамятность :)
        break;
		
		case "surrender1" :
			Diag.TempNode = "surrender_goaway";
            Dialog.Text = "Voici pour toi - et maintenant, déguerpis!";
			Link.l1 = "Chouette! Et reste en bonne santé aussi, mon ami!";
			Link.l1.go = "exit";
			sld = characterFromId(pchar.GenQuest.CaptainId);
            sld.talk_date_Go_away = lastspeakdate();
			AddMoneyToCharacter(pchar, sti(Pchar.GenQuest.MoneyForCaptureShip));
			ChangeCharacterComplexReputation(pchar,"nobility", -2); 		
			ChangeCharacterComplexReputation(pchar,"authority", 1.0); 							
			AddCharacterExpToSkill(pchar, "Leadership", 20);
			ChangeCharacterHunterScore(pchar, NationShortName(sti(NPChar.nation)) + "hunter", GetIntByCondition(HasShipTrait(pchar, "trait23"), 7 + rand(10), 3 + rand(5)));
		break;
		
		case "surrender_goaway":
			Dialog.Text = "Qu'est-ce que tu veux de plus de moi ?";
			Link.l1 = "Rien.";
			Link.l1.go = "exit";
			Diag.TempNode = "surrender_goaway";
		break;
		
		case "surrender2":			
			dialog.text = "Semble, je n'ai pas d'autre choix que de me soumettre à toi.";
			link.l1 = "Passe ton chemin, maintenant !";
			link.l1.go = "surrender3";				
		break;
						
		case "surrender3":
			Diag.TempNode = "surrender_goaway";
			sld = characterFromId(pchar.GenQuest.CaptainId);
            sld.talk_date_Go_away = lastspeakdate();
			DialogExit(); 
			LaunchTransferMain(pchar, sld, "Transfer");
		break;
				
        case "rumours":
			Dialog.Text = SelectRumour(); // to_do
			Link.l1 = RandPhraseSimple(RandSwear()+"C'est très intéressant. Une autre question?","Juste une autre affaire.");
			Link.l1.go = "quests";
			Link.l2 = RandPhraseSimple("Merci, et je devrais partir.","Tout le meilleur.");
			Link.l2.go = "exit";
			Diag.TempNode = "quests";
		break;
		
		case "Go_away":
			Dialog.Text = "Sors de mon navire!";
			Link.l1 = "Je suis déjà en train de partir.";
			Link.l1.go = "exit";
			Diag.TempNode = "Go_away";
		break;
		
		case "Go_away_Good":
			Dialog.Text = "Notre conversation est terminée. Je ne vais rien te dire de nouveau "+GetAddress_Form(NPChar)+".";
			Link.l1 = "D'accord. A te revoir en mer !";
			Link.l1.go = "exit";
			Diag.TempNode = "Go_away_Good";
		break;

        case "Capture":
            Diag.TempNode = "Go_away";
            Dialog.Text = "Voici pour toi - et maintenant sors !";
			Link.l1 = "Sympa !";
			Link.l1.go = "exit";
			AddMoneyToCharacter(pchar, sti(Pchar.GenQuest.MoneyForCaptureShip));
			ChangeCharacterComplexReputation(pchar,"nobility", -5);			
			AddCharacterExpToSkill(pchar, "Leadership", 20);
			ChangeCharacterHunterScore(pchar, NationShortName(sti(NPChar.nation)) + "hunter", GetIntByCondition(HasShipTrait(pchar, "trait23"), 7 + rand(10), 3 + rand(5)));
        break;

        case "Boarding":
            if (CheckAttribute(NPChar, "MainCaptanId"))
            {
                PChar.StartBattleAfterDeck = true;
                PChar.StartBattleMainCaptanId = NPChar.MainCaptanId;
                PChar.StartBattleEncGroupName = NPChar.EncGroupName;
            }
            DialogExit();
            Diag.CurrentNode = Diag.TempNode;
        break;
        
        case "QuestAboardCabinDialog":  // тестовый диалог, в игре не работает, для метода SetQuestAboardCabinDialog
			Diag.TempNode = "QuestAboardCabinDialog";
            Dialog.Text = "Attends, tu pourrais me tuer comme ça. Que veux-tu de moi?";
			Link.l1 = "Pour te tuer !";
			Link.l1.go = "QuestAboardCabinDialog_1";
			Link.l2 = "Rends-toi!";
			Link.l2.go = "QuestAboardCabinDialog_2";
			Link.l3 = "Donne-nous la carte, Billy (c)";  // предмет, далее не ясно или  QuestAboardCabinDialog_1 или QuestAboardCabinDialog_2
			Link.l3.go = "QuestAboardCabinDialog_3";  // можно закодить покидание корабля, но экипаж уже вырезан и тп...
        break;
        
        case "QuestAboardCabinDialog_1":
			Dialog.Text = "Eh bien, on verra, salaud !";
			Link.l1 = "Et qu'est-ce que je dois voir?";
			Link.l1.go = "exit";
			// тут можно восстановить НР противника (NPChar) или добавить парочку гардов против ГГ
			LAi_SetCurHPMax(NPChar);
			AddDialogExitQuestFunction("QuestAboardCabinDialogExitWithBattle"); // тут ругань обратно
		break;
		
		case "QuestAboardCabinDialog_2":
			Dialog.Text = "D'accord, tu as gagné!";
			Link.l1 = "Décision intelligente!";
			Link.l1.go = "exit";
			AddDialogExitQuestFunction("QuestAboardCabinDialogSurrender");
		break;
		
		case "QuestAboardCabinDialog_3":
			Dialog.Text = "Esperons que tu t'etouffes avec!";
			Link.l1 = "Très bien, mets-toi enchaîné et ferme ta gueule, prisonnier.";
			if (rand(1) == 1)  // пример!!!
			{
				Link.l1.go = "QuestAboardCabinDialog_2";
			}
			else
			{
			    Link.l1.go = "QuestAboardCabinDialog_3_1";
			}
			TakeNItems(NPChar, "Chest", -1);
			TakeNItems(pchar, "Chest", 1);
		break;
		
		case "QuestAboardCabinDialog_3_1":
			Dialog.Text = ""+GetSexPhrase("Venu ici","Venu ici")+", a fait un gâchis"+GetSexPhrase("","")+",et a tout pris"+GetSexPhrase("","")+", maintenant tu veux faire de moi un esclave? Jamais!";
			Link.l1 = "Alors préparez-vous à mourir.";
			Link.l1.go = "QuestAboardCabinDialog_1";
		break;
		//eddy. квест мэра, поиски пирата
		case "MQ_step_1":
			Dialog.Text = "Non, je n'ai pas vu de navire suspect qui ressemblait à des pirates.";
			Link.l1 = "Je vois.";
			Link.l1.go = "exit";
		break;
		
		//homo Наводка на купца
		case "MerchantTrap_Abordage":

			Dialog.Text = "Au nom de "+NationKingsName(NPChar)+" capitule, "+GetSexPhrase("sale pirate","garce répugnante!")+"! Alors, votre vie sera épargnée jusqu'à un tribunal équitable, où vous serez jugé pour tout "+NationNameSK(sti(NPChar.nation))+"navires que vous avez pillés"+GetSexPhrase("","")+".";
			Link.l1 = "Va te faire foutre! Tu devrais te rendre!";
			Link.l1.go = "exit";
			LAi_SetCurHPMax(NPChar);
			AddDialogExitQuestFunction("QuestAboardCabinDialogExitWithBattleNoParam"); // тут ругань обратно
		break;
		
		case "Siegehelp":		
            ref rchar = Group_GetGroupCommander(sGroup);
            if (NPChar.id == rchar.id)
            {
    			if(CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE)
				{
					dialog.text = "Votre Excellence, Gouverneur Général ! Je vous écoute attentivement, mais je vous prie d'être bref : nous luttons avec "+fort+", et je dois diriger le cours de la bataille.";
				}
				else
				{
					if(isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && sti(Items[sti(pchar.EquipedPatentId)].Nation) == npchar.nation)
					{
						dialog.text = "Vice-amiral! Je vous écoute attentivement, mais j'ai peu de temps : nous sommes en lutte avec "+fort+", et je dois diriger le cours de la bataille.";
					}
					else
					{
						dialog.text = "Je vous écoute, mais exposons rapidement le but de votre visite, nous luttons avec "+fort+", et j'ai besoin de diriger le cours de la bataille.";
					}
				}
                link.l1 = "C'est pourquoi je suis ici,  "+GetAddress_FormToNPC(NPChar)+".";
                link.l1.go = "attack_fort";

                link.l2 = "Dans ce cas, je ne prendrai pas plus de votre temps. Adieu, "+GetAddress_FormToNPC(NPChar)+".";
                link.l2.go = "exit";
    			
            }
            else
            {
                Dialog.text = "Je ne suis pas autorisé à traiter avec vous. Parlez au commandant de notre escadron. Son nom est  "+GetFullName(rchar)+", vous pouvez le trouver sur "+XI_ConvertString(RealShips[sti(rchar.Ship.Type)].BaseName)+"''"+rchar.Ship.Name+"''.";
                link.l1 = "Merci. Je ferai comme tu dis.";
                link.l1.go = "exit";
            
            }
            Diag.TempNode = "Siegehelp";
            
		break;
		
		case "attack_fort":
                dialog.text = "Et qu'est-ce que tu veux dire ?";
                link.l1 = "Je peux vous aider à écraser le fort de la colonie de "+GetConvertStr(aData.Colony+" Ville","LocLables.txt")+" et capture la ville, et une proie, ce qui résulte dans le cas de notre succès, nous divisons parmi nous.";
                link.l1.go = "Siegehelp_1";
                link.l2 = "En fait, mes affaires ne valent guère votre temps. Adieu, "+GetAddress_FormToNPC(NPChar)+".";
                link.l2.go = "exit";
                Diag.TempNode = "Siegehelp_0";
		break;
		
		case "Siegehelp_0":
            Dialog.text = "Encore toi? Je pensais que nous avions déjà tout discuté.";
            link.l1 = "Tu as raison. J'imagine que j'ai oublié"+GetSexPhrase("","")+".";
			link.l1.go = "exit";
			NPChar.DeckDialogNode = "Siegehelp_0";
            Diag.TempNode = "Siegehelp_0";

		break;
		
		case "Siegehelp_1":
            SiegeResult("");
			// belamour legendary edition
			bOk1 = isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation);
			bOk2 = CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE;
			bOk = bOk1 || bOk2;
            if (sti(aData.win)==0 || bOk)
            {
                dialog.text = "Et quelle part du butin vous attendez-vous à recevoir?";
                link.l1 = "Une moitié.";
                link.l1.go = "Big_part";
                link.l2 = "Un tiers.";
                link.l2.go = "Middle_part";
                link.l3 = "Un quart.";
                link.l3.go = "Small_part";
            }
            else
            {
                dialog.text = "Je n'ai pas besoin de vos services, capitaine! Je vais saisir cette colonie par moi-même et je n'ai besoin d'aucune aide pour ce faire.";
                link.l1 = "Pourquoi es-tu si sûr, "+GetAddress_FormToNPC(NPChar)+", n'importe qui peut avoir une veine de malchance.";
                link.l1.go = "attack_fort_03";
                link.l2 = "Dans ce cas, je ne prendrai plus de votre temps, "+GetAddress_FormToNPC(NPChar)+". Adieu!";
                link.l2.go = "exit";
            }
			Diag.TempNode = "Siegehelp_0";

		break;
		
		case "attack_fort_03":
            if((sti(aData.iSquadronPower)*SquadronDamage - (ifortPower)*fortDamage) < 4000)
            {
                dialog.text = "D'un autre côté, mes navires sont assez endommagés dans cette bataille, et des renforts ne feraient certainement pas de mal. Si vous êtes d'accord sur "+GetPart(4)+", alors, je suppose, nous pourrions parvenir à un accord.";
                link.l1 = "Cela me convient, "+GetAddress_FormToNPC(NPChar)+". J'essaierai d'assauter le fort, et vous nous soutiendrez avec le feu de vos canons de navire.";
                link.l1.go = "attack_fort_04";
                aData.PartAttaksFort = 4;
                link.l2 = "Je ne suis pas si bon marché, "+GetAddress_FormToNPC(NPChar)+". Je suis désolé pour la distraction"+GetSexPhrase("","")+" vous des affaires pressantes. Au revoir!";
                link.l2.go = "exit";
            }else{
                dialog.text = "Il y a assez de navires dans ma flotte pour réduire ce fort en poussière - ce n'est qu'une question de temps. Et maintenant, pourriez-vous quitter mon navire, s'il vous plaît? La victoire m'attend!";
                link.l1 = "Eh bien, dans ce cas, "+GetAddress_FormToNPC(NPChar)+", permettez-moi de prendre congé. Adieu!";
                link.l1.go = "exit";
            }
		    Diag.TempNode = "Siegehelp_0";
		break;
		case "Big_part":
            if( (sti(aData.iSquadronPower)*SquadronDamage - (ifortPower)*fortDamage) <= -1500)
            {
                dialog.text = "Les canons du fort ont gravement endommagé mes navires, et nous pourrions sûrement être le côté perdant dans la bataille à venir. J'accepte votre aide et je suis d'accord sur vos conditions.";
                link.l1 = "Excellent, "+GetAddress_FormToNPC(NPChar)+", dans ce cas, nous tenterons d'attaquer le fort, et vous nous soutiendrez avec le feu de vos canons de navire.";
                link.l1.go = "attack_fort_04";
                aData.PartAttaksFort = 2;
            }
            else
            {
				// belamour legendary edition
				bOk1 = isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation);
				bOk2 = CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE;
				bOk = bOk1 || bOk2;
				if(bOk)
				{
					dialog.text = "Votre Excellence, je dois encore rapporter sur l'avancement de l'operation ... Allons au moins "+GetPart(4)+".";
				}
				else
				{
                dialog.text = "N'est-ce pas trop, capitaine? Vous avez "+GetNumShips(GetCompanionQuantity(PChar))+", et mon escadron a "+GetNumShips(Group_GetCharactersNum(sGroup))+". Je peux vous offrir "+GetPart(4)+". Et considérez cela comme juste.";
				}
                aData.PartAttaksFort = 4;
                link.l1 = "Je suis d'accord"+GetSexPhrase("","")+", "+GetAddress_FormToNPC(NPChar)+", dans ce cas, j'attaquerai le fort, et vous nous soutiendrez avec le feu de vos canons de navire.";
                link.l1.go = "attack_fort_04";
                link.l2 = "Malheureusement, je ne pense pas, "+GetAddress_FormToNPC(NPChar)+". Il n'y a plus rien à discuter. Adieu.";
                link.l2.go = "exit";
            }
            Diag.TempNode = "Siegehelp_0";
        break;
        
        case "attack_fort_04":
            dialog.text = "Dès que le fort sera capturé, nous commencerons à déployer des troupes d'assaut sur la rive, puis nous continuerons à nous battre dans la ville elle-même, où j'espère vous rencontrer.";
            link.l1 = "Ainsi soit-il. A bientôt, "+GetAddress_FormToNPC(NPChar)+"!";
            link.l1.go = "exit";
            Diag.TempNode = "Siegehelp_0";
            PChar.quest.Union_with_Escadra = "Yes";
        break;

        case "Middle_part":
            if((sti(aData.iSquadronPower)*SquadronDamage - (ifortPower)*fortDamage) <= -600)
            {
                dialog.text = "Je pense que je vais accepter vos conditions. L'opération conjointe augmentera mes chances de gagner ce combat. Si tout se passe comme prévu, vous recevrez votre part du butin.";
                link.l1 = "C'est formidable que nous soyons parvenus à un accord, "+GetAddress_FormToNPC(NPChar)+". J'ordonnerai à mes hommes d'assauter le fort immédiatement.";
                link.l1.go = "attack_fort_04";
                aData.PartAttaksFort = 3;
            }else{
				// belamour legendary edition
				bOk1 = isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation);
				bOk2 = CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE;
				bOk = bOk1 || bOk2;
				if(bOk)
				{
					dialog.text = "Votre Excellence, je dois encore faire un rapport sur l'avancement de l'opération ... Allons au moins "+GetPart(4)+".";
				}
				else
				{
                dialog.text = "N'est-ce pas trop, capitaine? Vous avez "+GetNumShips(GetCompanionQuantity(PChar))+", et mon escadron a "+GetNumShips(Group_GetCharactersNum(sGroup))+". Je peux vous offrir "+GetPart(4)+". Et considérez-le juste.";
				}
                link.l1 = "Je "+GetSexPhrase("d'accord","d'accord")+", "+GetAddress_FormToNPC(NPChar)+", dans ce cas, j'attaquerai le fort et vous nous soutiendrez avec le feu de vos canons de navire.";
                link.l1.go = "attack_fort_04";
                aData.PartAttaksFort = 4;
                link.l2 = "Malheureusement, je ne pense pas, "+GetAddress_FormToNPC(NPChar)+". Il n'y a plus rien à discuter. Adieu.";
                link.l2.go = "exit";
            }
            Diag.TempNode = "Siegehelp_0";
        break;

        case "Small_part":
            dialog.text = "Mes navires sont fatigués, et toute force fraîche est la bienvenue dans cette situation. J'accepte votre aide et je suis d'accord avec vos conditions.";
            link.l1 = "Je suis content"+GetSexPhrase("","")+", "+GetAddress_FormToNPC(NPChar)+".. Je vais immédiatement ordonner à mes hommes de commencer l'assaut du fort.";
            link.l1.go = "attack_fort_04";
            aData.PartAttaksFort = 4;
            Diag.TempNode = "Siegehelp_0";
        break;
		
		case "Talk_Capture_City":
            AfterTownBattle();  // все, все свободны
            LAi_LoginInCaptureTown(NPChar, false);
            aData.win = 1;
            EndOfTheSiege("End");
            NPChar.location = "";
            int ilt = makeint(sti(aData.loot)/sti(aData.PartAttaksFort));
            dialog.text = "Bonjour, capitaine! C'était certainement une bataille difficile, mais nous avons réussi à briser la résistance furieuse des défenseurs de la ville. Nous avons pillé "+sti(aData.loot)+" pesos. Selon notre accord, votre part est "+ilt+". Please accept this money; you certainly deserve every last coin of it. And now please excuse me, but I must return to my business.";
            link.l1 = "Dans ce cas, je vous laisse, "+GetAddress_FormToNPC(NPChar)+". Adieu!";
            link.l1.go = "exit";
            //AddDialogExitQuest("End_Siege_and_Attaks_City");

            Diag.TempNode = "no_return_02";
            AddMoneyToCharacter(PChar, ilt);
            ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 20);
            ChangeCharacterComplexReputation(PChar,"nobility", 10);
            AddCharacterExpToSkill(GetMainCharacter(), "Leadership", 80);
            AddCharacterExpToSkill(GetMainCharacter(), "Sailing", 100);
            AddCharacterExpToSkill(GetMainCharacter(), "Defence", 100);
            AddCharacterExpToSkill(GetMainCharacter(), "Accuracy", 100);
            AddCharacterExpToSkill(GetMainCharacter(), "Cannons", 100);
            AddCharacterExpToSkill(GetMainCharacter(), "Fortune", 80);
            aData.loot = sti(aData.loot) - ilt;
            if (CheckAttribute(PChar, "quest.LeaveTown")) Pchar.quest.LeaveTown.over = "yes";
            //--> слухи
            SiegeRumour("I've been told that you had helped our squadron in the assault of the "+NationNameSK(sti(aData.conation))+" colony - "+GetConvertStr(aData.Colony+" Town", "LocLables.txt")+"! We're so thankfull to you, "+ GetAddress_Form(NPChar)+".", "", sti(aData.nation), -1, 30, 3);
            //<-- слухи
		break;

        case "no_return_02":
            dialog.text = "Ahoy, capitaine ! Avez-vous des affaires avec moi ?";
            link.l1 = "Non, "+GetAddress_FormToNPC(NPChar)+". Au revoir!";
            link.l1.go = "exit";
            Diag.TempNode = "no_return_02";
		break;
		
		case "GoldSquadron":
            ref rch = Group_GetGroupCommander("Sea_Head_of_Gold_Squadron");
            if (NPChar.id == rch.id)
            {
    			dialog.text = "Je vous écoute, mais soyez rapide quant à l'objectif de votre visite, je n'ai pas beaucoup de temps. J'ai une mission importante et secrète, et on m'a également ordonné de couler tous les navires suspects en pleine mer, qui pourraient présenter un danger pour notre convoi.";                          
                link.l1 = "Dans ce cas, je ne prendrai plus de votre temps. Bonne chance, "+GetAddress_FormToNPC(NPChar)+".";
                link.l1.go = "exit";

            }
            else
            {
                Dialog.text = "Je ne suis pas autorisé à traiter avec vous. Parlez au commandant de notre escadron. Son nom est "+GetFullName(rch)+", vous pouvez le trouver sur "+XI_ConvertString(RealShips[sti(rch.Ship.Type)].BaseName)+" ''"+rch.Ship.Name+"''.";
                link.l1 = "Merci. Je ferai comme tu dis.";
                link.l1.go = "exit";

            }
            Diag.TempNode = "GoldSquadron";
		break;
		
		case "WM_Captain":
			dialog.text = "Heureux de vous rencontrer, et mon nom est "+GetFullName(npchar)+". Alors vous êtes venu nous aider? Dans ce cas, je suis particulièrement heureux, car notre situation actuelle est vraiment critique - nous sommes seuls sur les rives d'une île inhabitée, le navire est à peine navigable, l'équipage a subi de lourdes pertes...";
			link.l1 = "Comme j'ai entendu, vous avez eu une bataille avec des pirates, et puis il y a eu cette tempête...";
			link.l1.go = "WM_Captain_1";
			pchar.quest.DesIsland_Over.over = "yes";//снять прерывание
		break;
		
		case "WM_Captain_1":
			dialog.text = "C'est exact. Mon navire a été gravement endommagé dans la bataille - nous avons même dû résister à une attaque d'abordage menée par ces maudits pirates. Plus tard, une tempête nous a attrapés... oh, je ne veux même pas y penser. Nous avons été emportés sur ce rivage inhospitalier. Nous avons prié toute la journée la Sainte Vierge pour nous sauver de la tempête et pour garder nos chaînes d'ancre en un seul morceau\nEt nous voici. Nous avons réparé notre navire pendant une semaine, mais regardez par vous-même : il ne reste que cinquante hommes et nous manquons aussi de planches de bois - et où sommes-nous censés les trouver ? Dans la jungle ? Evidemment. Travaillant dur chaque jour et pourtant nous n'avons que le cinquième du matériel total nécessaire\nNaviguer avec de tels dommages est aussi bon que le suicide. Maintenant vous voyez comment nous nous en sortons ici, capitaine...";
			link.l1 = "Ouais... Votre situation n'est pas enviable. Réfléchissons à ce que nous pourrions entreprendre et comment je peux vous aider.";
			link.l1.go = "WM_Captain_2";
		break;
		
		case "WM_Captain_2":
			dialog.text = "Eh, je souhaite que nous avions assez de planches et de toile à voile - dans ce cas, nous réparerions notre navire en une semaine\nCapitaine, puisque vous êtes venu ici exprès, peut-être pourriez-vous visiter le port le plus proche et acheter les matériaux dont nous avons besoin? Cela résoudrait notre problème. Ne vous inquiétez pas pour les pièces, je compenserai toutes les dépenses.";
			link.l1 = "Bien sûr. Que devez-vous livrer exactement, et combien ?";
			link.l1.go = "WM_Captain_3";
		break;
		
		case "WM_Captain_3":
			pchar.questTemp.WPU.Escort.Planks = 300 + hrand(5)*10;
			pchar.questTemp.WPU.Escort.Sailcloth = 150 + hrand(10)*10;
			pchar.questTemp.WPU.Escort.Linen = 70 + hrand(7)*10;
			dialog.text = "J'ai déjà tout compris. Considérant ce que nous avons déjà, j'ai besoin "+FindRussianQtyString(sti(pchar.questTemp.WPU.Escort.Planks))+" planches, "+FindRussianQtyString(sti(pchar.questTemp.WPU.Escort.Sailcloth))+" toile à voile et "+FindRussianQtyString(sti(pchar.questTemp.WPU.Escort.Linen))+" coton. Avec ces matériaux, nous pourrions réparer le navire en une semaine et ensuite nous pourrions mettre les voiles.";
			link.l1 = "D'accord. Je vous apporterai tous les matériaux dont vous avez besoin. Attendez-moi - je reviendrai au plus tard dans dix jours.";
			link.l1.go = "WM_Captain_4";
		break;
		
		case "WM_Captain_4":
			dialog.text = "Merci beaucoup, capitaine ! C'est un poids en moins sur mon esprit. Nous attendrons et prierons pour votre retour réussi !";
			link.l1 = "Ne vous inquiétez pas. Bientôt, vous aurez tout ce dont vous avez besoin pour la réparation.";
			link.l1.go = "exit";
			AddQuestRecord("Escort", "27");
			AddQuestUserData("Escort", "sSName", pchar.questTemp.WPU.Escort.ShipName);
			AddQuestUserData("Escort", "sIsland", XI_ConvertString("Colony"+pchar.questTemp.WPU.Current.TargetIslandID));
			AddQuestUserData("Escort", "sQty1", FindRussianQtyString(sti(pchar.questTemp.WPU.Escort.Planks)));
			AddQuestUserData("Escort", "sQty2", FindRussianQtyString(sti(pchar.questTemp.WPU.Escort.Sailcloth)));
			AddQuestUserData("Escort", "sQty3", FindRussianQtyString(sti(pchar.questTemp.WPU.Escort.Linen)));
			Diag.TempNode = "WM_Captain_again";
			SetFunctionTimerCondition("WM_Captain_Over", 0, 0, 11, false);
			pchar.questTemp.WPU.Escort = "wait";
		break;
		
		case "WM_Captain_again":
			dialog.text = "Nous attendrons avec impatience votre retour, capitaine!";
			link.l1 = "Lever l'ancre !";
			link.l1.go = "exit";
			Diag.TempNode = "WM_Captain_again";
		break;
		
		case "WM_Captain_5":
			dialog.text = "Excellent! Maintenant nous pouvons commencer à réparer le navire!";
			link.l1 = "Mes hommes vous donneront un coup de main - de cette façon, ce sera plus rapide. De plus, je dois vous accompagner à la colonie de "+XI_ConvertString("Colonie"+pchar.questTemp.WPU.Escort.StartCity)+", donc plus vite nous aurons fini avec les réparations, mieux ce sera pour moi.";
			link.l1.go = "WM_Captain_6";
		break;
		
		case "WM_Captain_6":
			pchar.questTemp.WPU.Current.TargetIslandID.Shore = SelectQuestShoreLocationFromSea(pchar.questTemp.WPU.Current.TargetIslandID);
			dialog.text = "Vraiment, je n'ai aucune idée de comment vous remercier convenablement, capitaine... Veuillez ordonner de décharger les matériaux dans une crique appelée "+XI_ConvertString(pchar.questTemp.WPU.Current.TargetIslandID.Shore)+" - là, nous avons tout préparé pour la réparation.";
			link.l1 = "D'accord. Nous nous retrouverons sur le rivage.";
			link.l1.go = "exit";
			AddQuestRecord("Escort", "29");
			AddQuestUserData("Escort", "sShore", XI_ConvertString(pchar.questTemp.WPU.Current.TargetIslandID.Shore+"Gen"));
			pchar.quest.DisasterShip_WMC.win_condition.l1 = "location";
			pchar.quest.DisasterShip_WMC.win_condition.l1.location = pchar.questTemp.WPU.Current.TargetIslandID.Shore;
			pchar.quest.DisasterShip_WMC.function = "RepairShip_Prepare";
			Diag.TempNode = "WM_Captain_repeat";
		break;
		
		case "WM_Captain_repeat":
			dialog.text = "Quand commencerons-nous les réparations, capitaine? Je vous attendrai sur le rivage.";
			link.l1 = "Oui, bien sûr. Je pars maintenant.";
			link.l1.go = "exit";
			Diag.TempNode = "WM_Captain_repeat";
		break;
		
		case "Repair_start":
			dialog.text = "Eh bien, tout semble prêt pour la réparation. Je pense que nous devrions avoir terminé dans environ cinq jours.";
			link.l1 = "Très bien! J'allais de toute façon explorer cette île, alors je vais bien utiliser ce temps.";
			link.l1.go = "Repair_start_1";
		break;
		
		case "Repair_start_1":
			DialogExit();
			pchar.quest.WM_Captain_Over.over = "yes";//снять прерывание
			sld = characterFromId("WMCaptain");
			LAi_SetImmortal(sld, false);
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", 5.0);
			RemoveCharacterGoods(pchar, GOOD_PLANKS, sti(pchar.questTemp.WPU.Escort.Planks));
			RemoveCharacterGoods(pchar, GOOD_SAILCLOTH, sti(pchar.questTemp.WPU.Escort.Sailcloth));
			RemoveCharacterGoods(pchar, GOOD_COTTON, sti(pchar.questTemp.WPU.Escort.Linen));
			DoQuestFunctionDelay("RepairShip_WithoutMasts", 5.0);
		break;
		
		case "Repair_end":
			dialog.text = "Eh bien, c'est tout. Nous avons terminé les réparations et le navire est prêt à prendre la mer. Quand partons-nous, capitaine?";
			link.l1 = "Si tu es prêt, je ne vois aucun intérêt à rester là. Levez les ancres !";
			link.l1.go = "Repair_end_1";
		break;
		
		case "Repair_end_1":
			DialogExit();
			sld = characterFromId("WMCaptain");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 5.0);
			AddQuestRecord("Escort", "30");
			AddQuestUserData("Escort", "sSName", pchar.questTemp.WPU.Escort.ShipName);
			AddQuestUserData("Escort", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity));
			SetFunctionTimerCondition("DisasterShipWM_Over", 0, 0, 25, false);
			log_info("You have 25 days to escort "+pchar.questTemp.WPU.Escort.ShipBaseName+" '"+pchar.questTemp.WPU.Escort.ShipName+"' to the port of "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen")+"");
			pchar.quest.DisasterShip_final.win_condition.l1 = "location";
			pchar.quest.DisasterShip_final.win_condition.l1.location = pchar.questTemp.WPU.Escort.StartCity +"_town";
			pchar.quest.DisasterShip_final.function = "WMShip_final";
		break;
		
		case "WMShip_final":
			pchar.quest.Escort_fail.over = "yes";
			pchar.quest.DisasterShipWM_Over.over = "yes";//снимаем оба прерывания
			RemoveCharacterCompanion(Pchar, characterFromID("WMCaptain"));//удаляем компаньона
			pchar.questTemp.WPU.Escort.LevelUp_1Money = sti(pchar.questTemp.WPU.Escort.Planks)*15+sti(pchar.questTemp.WPU.Escort.Sailcloth)*9+sti(pchar.questTemp.WPU.Escort.Linen)*45;//деньги за материалы
			dialog.text = "Je veux vous remercier encore une fois, capitaine - vous nous avez beaucoup aidé, moi et mon équipage, à sortir de cette égratignure. Comme je l'ai promis, je compenserai les coûts des matériaux nécessaires à la réparation de mon navire. Voici "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.LevelUp_1Money))+", s'il vous plaît, prenez-les. Et ceci est mon cadeau personnel pour vous.";
			link.l1 = "J'étais heureux de vous aider.";
			link.l1.go = "WMShip_final_1";
		break;
		
		case "WMShip_final_1":
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.WPU.Escort.LevelUp_1Money));
			TakeNItems(pchar, "obereg_"+(hrand(10)+1), 1);
			dialog.text = "Et maintenant, il est temps de dire au revoir, capitaine. N'oubliez pas de visiter l'autorité portuaire - on vous attend là-bas. À bientôt !";
			link.l1 = "Passe une bonne journée, "+npchar.name+"!";
			link.l1.go = "WMShip_final_2";
		break;
		
		case "WMShip_final_2":
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			DialogExit();
			sld = characterFromId("WMCaptain");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "", 5.0);
			if (CheckAttribute(PChar, "questTemp.WPU.Escort.LevelUp_1WM")) AddQuestRecord("Escort", "31");
			if (CheckAttribute(PChar, "questTemp.WPU.Escort.LevelUp_1VSP")) AddQuestRecord("Escort", "37");
			if (CheckAttribute(PChar, "questTemp.WPU.Escort.LevelUp_1S")) AddQuestRecord("Escort", "40");
			AddQuestUserData("Escort", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.LevelUp_1Money)));
			AddQuestUserData("Escort", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen"));
			AddQuestUserData("Escort", "sSName", pchar.questTemp.WPU.Escort.ShipName);
		break;
		
		case "VSP_Captain":
			dialog.text = "Est-ce ainsi? Et je pensais qu'ils nous avaient oubliés. Ouais, mon navire a eu le pire de tous. Nous avons été laissés à lutter contre les éléments de la nature après que la tempête a forcé les pirates à arrêter une attaque de notre caravane. Nous avons été portés à ce rivage inhospitalier\nNous avons passé quelques jours à réparer et à nous reposer. Ces païens nous ont attaqués à nouveau, dès que nous allions naviguer loin\nEt puis la tempête nous a frappé à nouveau - nous avons pensé que le Seigneur avait finalement décidé de nous finir, mais vous êtes arrivé. Merci à la Sainte Marie! Merci encore, capitaine!";
			link.l1 = "C'est fini, "+GetAddress_FormToNPC(NPChar)+". Maintenant, je dois vous escorter jusqu'à "+XI_ConvertString("Colonie"+pchar.questTemp.WPU.Escort.StartCity+"Gén")+", afin de le protéger d'autres ennuis possibles. Êtes-vous prêt à partir maintenant? La tempête a déjà commencé à diminuer.";
			link.l1.go = "VSP_Captain_1";
		break;
		
		case "VSP_Captain_1":
			dialog.text = "Mais bien sûr ! Plus tôt nous quitterons cet endroit, plus mes hommes seront calmes - ils ont déjà trop souffert. Mettons les voiles !";
			link.l1 = "Suivez simplement mon navire - et calmez votre équipage, il n'y a plus rien à craindre maintenant.";
			link.l1.go = "VSP_Captain_2";
		break;
		
		case "VSP_Captain_2":
			pchar.quest.DisasterShip_GetOut.over = "yes";
			DialogExit();
			Group_DelCharacter("WMShip", "WMCaptain");//иначе будет клон
			sld = characterFromId("WMCaptain");
			LAi_SetImmortal(sld, false);
			SetCharacterRemovable(sld, false);
			sld.CompanionEnemyEnable = false; //всегда друзья
			SetCompanionIndex(pchar, -1, sti(sld.index));
			sld.loyality = MAX_LOYALITY;
			AddQuestRecord("Escort", "36");
			AddQuestUserData("Escort", "sSName", pchar.questTemp.WPU.Escort.ShipName);
			SetFunctionTimerCondition("DisasterShipWM_Over", 0, 0, 25, false);
			log_info("You have 25 days to escort "+pchar.questTemp.WPU.Escort.ShipBaseName+" '"+pchar.questTemp.WPU.Escort.ShipName+"' to the port of"+XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen")+"");
			pchar.questTemp.WPU.Escort = "win";
			pchar.quest.Escort_fail.win_condition.l1 = "NPC_Death";//прерывание на потопление сопровождаемого
			pchar.quest.Escort_fail.win_condition.l1.character = "WMCaptain";
			pchar.quest.Escort_fail.function = "DisasterShipWM_failed";
			pchar.quest.DisasterShip_final.win_condition.l1 = "location";
			pchar.quest.DisasterShip_final.win_condition.l1.location = pchar.questTemp.WPU.Escort.StartCity +"_town";
			pchar.quest.DisasterShip_final.function = "WMShip_final";
			Diag.currentnode = "VSP_Captain_again";
			Delete_EscortStorm();//уберем шторм
		break;
		
		case "VSP_Captain_again":
			dialog.text = "Doit-on mettre les voiles, capitaine?";
			link.l1 = "Bien sûr. Je vais retourner à mon navire maintenant.";
			link.l1.go = "exit";
			Diag.TempNode = "VSP_Captain_again";
		break;
		
		case "VSPShip_final":
			pchar.quest.Escort_fail.over = "yes";
			pchar.quest.DisasterShipWM_Over.over = "yes";//снимаем оба прерывания
			RemoveCharacterCompanion(Pchar, characterFromID("WMCaptain"));//удаляем компаньона
			pchar.questTemp.WPU.Escort.LevelUp_1Money = 10000+sti(pchar.rank)*200;
			dialog.text = "Je veux vous remercier encore une fois, capitaine - vous nous avez grandement aidés, moi et mon équipage, à sortir de ce pétrin. Voici"+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.LevelUp_1Money))+". Tout l'équipage a contribué, alors ne pense même pas à y renoncer. Et ceci est mon cadeau personnel pour toi.";
			link.l1 = "J'étais heureux de vous aider!";
			link.l1.go = "WMShip_final_1";
		break;
		
		case "SShip_final":
			pchar.questTemp.WPU.Escort.LevelUp_1Money = 5000+sti(pchar.rank)*100;
			RemovePassenger(Pchar, npchar);//удаляем пассажира
			dialog.text = "Je veux vous remercier encore une fois, capitaine, de nous avoir sauvé le cul de ce pétrin. Tenez, acceptez ces pièces - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.LevelUp_1Money))+"  et voici, prenez ce cadeau. Ce n'est pas grand-chose, mais c'est tout ce que je peux faire pour vous remercier de ce que vous avez fait. S'il vous plaît, ne refusez pas l'offre\nMon ancien équipage est ébahi par vous et votre combat contre les Indiens et les pirates. Tous souhaitent vous rejoindre. J'espère que vous n'allez pas refuser une demande de services loyaux de marins qui viennent de perdre leur navire?";
			link.l1 = "Bien sûr, pas du tout. Je le garderai avec plaisir. J'étais ravi de vous aider !";
			link.l1.go = "WMShip_final_1";
		break;
		
		//Голландский Гамбит
		case "Stivesant_1":
			DelLandQuestMark(npchar);
			dialog.text = "D'accord. Mais, monsieur, pourriez-vous expliquer ce qui se passe ici? Comment se fait-il que vous commandez le 'Meifeng'! Quelque chose est-il arrivé à Longway?";
			link.l1 = "J'ai toutes les explications dont vous avez besoin - et aussi d'autres informations importantes.";
			link.l1.go = "Stivesant_2";			
		break;
		
		case "Stivesant_2":
			dialog.text = "Alors je suis tout ouïe.";
			link.l1 = "Il y a eu un coup d'Etat à Willemstad. Lucas Rodenburg a pris la place du gouverneur et a mis Matthias Beck en prison sur une suspicion ridicule qu'il avait des liens avec les renseignements britanniques.";
			link.l1.go = "Stivesant_3";			
		break;
		
		case "Stivesant_3":
			dialog.text = "Hmm... Mynheer, les choses que vous me dites sont vraiment surprenantes. J'avais reçu des nouvelles de Willemstad il n'y a pas si longtemps, et il n'y avait rien de tel dedans.";
			link.l1 = "Ecoutez-moi, monsieur Stuyvesant. Vous devez avoir reçu les nouvelles par Rodenburg, et il doit être sûr que vous n'arriverez pas à Curaçao.";
			link.l1.go = "Stivesant_4";			
		break;
		
		case "Stivesant_4":
			dialog.text = "Monsieur, j'aime de moins en moins ce que vous dites. Qui êtes-vous donc?";
			link.l1 = "Je suis juste un capitaine et juste un homme qui n'est pas indifférent au sort des colons hollandais. Lucas Rodenburg a ordonné à Longway de détruire votre navire et de vous tuer aussi. Et comme 'Meifeng' ne vous aurait pas rendu méfiant, il l'aurait exécuté sans aucun effort.";
			link.l1.go = "Stivesant_5";			
		break;
		
		case "Stivesant_5":
			dialog.text = "Alors, tu veux dire que Lucas...";
			link.l1 = "Décidé de vous éliminer du pouvoir de la manière la plus simple possible - en vous éliminant tout simplement. À part vous, il n'y a aucune autre personne dans la région capable de résister significativement à l'influence de Rodenburg sur l'Archipel.";
			link.l1.go = "Stivesant_6";			
		break;
		
		case "Stivesant_6":
			dialog.text = "Je n'arrive pas à le croire !";
			link.l1 = "Je n'ai pas cru à ces conneries avec Beck lié au renseignement anglais et j'ai mené ma propre enquête. J'ai découvert que 'Meifeng', chargé de coupe-gorges triés sur le volet, est parti pour Philipsburg. Je les ai poursuivis et leur ai livré bataille. Longway a été capturé, et il m'a donné toutes ces informations, y compris votre position.";
			link.l1.go = "Stivesant_7";			
		break;
		
		case "Stivesant_7":
			dialog.text = "Hm... Cela semble probable. Personne, sauf pour Rodenburg, ne connaissait ou ne pouvait connaître mon emploi du temps et ma route ! Nom de Dieu ! C'est de la trahison ! Où est Longway ?!";
			link.l1 = "Je l'ai libéré en échange de sa confession volontaire. Je dois dire, il n'était pas trop désireux d'exécuter l'ordre de Rodenburg, mais il ne pouvait pas non plus l'ignorer. Il a également dit qu'il ne retournerait pas au service de Rodenburg - cette dernière sale affaire a fait déborder sa coupe.";
			link.l1.go = "Stivesant_8";			
		break;
		
		case "Stivesant_8":
			dialog.text = "D'accord... Capitaine "+GetFullName(pchar)+", vous irez à Willemstad avec moi. Vous naviguerez sur le 'Meifeng' devant mon navire. Si ce que vous avez dit est vrai, Lucas doit être arrêté, et vous fournirez votre aide à cet égard. Mais si vous m'avez menti... Vous n'avez que vous-même à blâmer.";
			link.l1 = "Pour moi, il n'y a aucun sens à te mentir, monsieur. Allons-nous vite!";
			link.l1.go = "Stivesant_9";			
		break;
		
		case "Stivesant_9":
			DialogExit();
			Diag.CurrentNode = "Stivesant_10";
			AddQuestRecord("Holl_Gambit", "3-52");
			pchar.questTemp.HWIC.Self = "WayWithStivesant";
			Group_DelCharacter("Stivesant_Halleon", "Stivesant");
			SetCharacterRemovable(npchar, false);
			npchar.CompanionEnemyEnable = false; //всегда друзья
			SetCompanionIndex(pchar, -1, sti(npchar.index));
			npchar.loyality = 40;
			DeleteAttribute(npchar, "LifeDay");
			pchar.quest.Seek_Piter.win_condition.l1 = "location";
			pchar.quest.Seek_Piter.win_condition.l1.location = "Villemstad_town";
			pchar.quest.Seek_Piter.win_condition.l2 = "Day";
			pchar.quest.Seek_Piter.function = "StivesantOnStreet";
			pchar.quest.Terms_Over.win_condition.l1 = "Timer";
			pchar.quest.Terms_Over.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.Terms_Over.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 15);
			pchar.quest.Terms_Over.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 15);
			pchar.quest.Terms_Over.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 15);
			pchar.quest.Terms_Over.function = "QuestShipsTerms_Over";
			AddMapQuestMarkCity("Villemstad", false);
		break;
		
		case "Stivesant_10":
			dialog.text = "Capitaine, allez à 'Meifeng'. Il est temps pour nous de mettre les voiles.";
			link.l1 = "Oui, monsieur, bien sûr.";
			link.l1.go = "exit";
			Diag.TempNode = "Stivesant_10";
		break;
		
		case "Keller_1":
			dialog.text = "Très intéressant ! S'il vous plaît, racontez votre histoire. J'essaierai de faire de mon mieux pour aider.";
			link.l1 = "Mynheer Keller, vous souvenez-vous comment vous avez rencontré une flûte sur votre chemin vers Willemstad il y a plusieurs mois. Il y avait une famille de réfugiés juifs à bord. Vous avez dîné à bord de ce navire puis avez poursuivi votre voyage.";
			link.l1.go = "Keller_2";
		break;
		
		case "Keller_2":
			dialog.text = "Oui, je suppose que oui... Oui, je m'en souviens très clairement maintenant. Alors, quel est le marché?";
			link.l1 = "La flûte a été coulée par des pirates ce jour-là. Seuls deux réfugiés ont réussi à se sauver - Solomon et Abigail, sa fille. Ils ont trouvé refuge sur une île à seulement quelques miles de l'endroit où l'attaque a eu lieu. J'ai besoin de trouver cette île. Pourriez-vous vous rappeler où vous avez rencontré cette flûte ? C'est très important.";
			link.l1.go = "Keller_3";
		break;
		
		case "Keller_3":
			dialog.text = "Et c'est tout ce dont vous avez besoin? Je connais cette île. Elle est très proche, entre Trinidad et Curacao. Une petite île déserte inhabitée. Il n'y a même pas d'Indiens là-bas.";
			link.l1 = "Et connaissez-vous ses coordonnées approximatives ?";
			link.l1.go = "Keller_4";
		break;
		
		case "Keller_4":
			dialog.text = "Je peux vous donner les coordonnées exactes. C'est à 12  48'  Nord et 64  41'  Ouest. Cherchez-le là-bas. L'île est plutôt petite, mais vous devriez pouvoir la localiser facilement.";
			link.l1 = "Merci, monsieur Keller ! Vous m'avez beaucoup aidé. Au revoir.";
			link.l1.go = "Keller_5";
		break;
		
		case "Keller_5":
			DialogExit();
			Diag.CurrentNode = "Keller_6";
			pchar.quest.Keller_fail.over = "yes";
			pchar.questTemp.HWIC_Coordinates = "true"; //атрибут координат на поиск острова через каюту
			DeleteAttribute(pchar, "questTemp.HWICMC");
			AddQuestRecord("Holl_Gambit", "3-66");
		break;
		
		case "Keller_6":
			dialog.text = "Vouliez-vous autre chose, capitaine?";
			link.l1 = "Non, merci. Je retournais déjà à mon navire.";
			link.l1.go = "exit";
			Diag.TempNode = "Keller_6";
		break;
		
		// belamour рыбацкое судно -->
		case "FishingBoat":
			pchar.GenQuest.FishingBoatSecondTime = true;
			dialog.text = "Rien de spécial, c'est un bateau de pêche, nous attrapons du poisson ici. Il faut bien gagner sa vie d'une manière ou d'une autre.";
			link.l1 = "Oui, je suis d'accord, ce sont les temps...";
			link.l1.go = "FishingBoat_1";			
		break;
		
		case "FishingBoat_1":
			Diag.TempNode = "FishingBoat_1";
			dialog.text = "Alors, que voulez-vous ?";
			link.l1 = "Je voulais"+GetSexPhrase("","")+" pour découvrir les dernières nouvelles de l'archipel.";
            link.l1.go = "rumours_capitan";
			link.l2 = "Comment sont vos prises aujourd'hui? Pouvez-vous vendre? Les provisions ne me feraient pas de mal...";
			link.l2.go = "FishingBoat_2";
			link.l3 = "Rien de spécial, je suis juste venu vous saluer !";
    		link.l3.go = "exit";	
	
		break;
		
		case "FishingBoat_2":
			if(GetDataDay() < 11) 
			{
				if(sti(RealShips[sti(npchar.ship.type)].basetype) == SHIP_TARTANE) iTemp = 100 + hrand(100);
				else iTemp = 200 + hrand(100);
				iMoney = sti(GetCurrentIslandGoodsPrice(GOOD_FOOD)*0.66);
				pchar.GenQuest.FishingBoatITemp = iTemp;
				pchar.GenQuest.FishingBoatIMoney = iMoney;
				
				dialog.text = "La pêche est bonne aujourd'hui, il suffit d'avoir le temps de sortir les filets. Nous pouvons vous la vendre, même moins cher qu'en magasin - de toute façon, nous vendons du poisson à un marchand local. Si nous traduisons tout cela en provisions... Nous avons maintenant "+iTemp+" de cela, nous pouvons le vendre à un prix de "+iMoney+" pesos pièce. Combien allez-vous prendre?";
				link.l1.edit = 3;
				link.l1 = "";	
				link.l1.go = "Количество вбитого провианта";
				link.l2 = "Vous savez, j'ai changé d'avis sur l'achat de vos provisions.";	
				link.l2.go = "exit";
				
			}
			if(GetDataDay() > 10 && GetDataDay() < 21) 
			{
				Diag.TempNode = "FishingBoat_1";
				dialog.text = "Oui, quelque chose, pour être honnête, il n'y a pas de poisson du tout ... Presque rien n'a été attrapé aujourd'hui. Mais les harpons sont restés superflus - ils pensaient attraper un gros poisson ou une baleine, si vous aviez de la chance ... Peut-être avez-vous besoin de harpons?";
				link.l1 = "Non, je ne suis pas intéressé par les harpons.";
				link.l1.go = "exit";
				link.l2 = "Hmm, un harpon est aussi une chose utile entre les bonnes mains. J'achèterai probablement.";
				link.l2.go = "Гарпуны";
			}
			if(GetDataDay() > 20)
			{
				dialog.text = "Oui, quelque chose, pour être honnête, il n'y a pas de poisson du tout ... Presque rien n'a été attrapé aujourd'hui. Alors il n'y a pas grand-chose à vendre. À moins que ... J'ai quelques babioles, peut-être que quelque chose vous intéressera. Voulez-vous voir?";
				link.l1 = "Non, je ne suis pas intéressé par des babioles.";
				link.l1.go = "exit";
				link.l2 = "C'est dommage qu'il n'y ait pas de prise. Eh bien, regardons au moins vos bibelots - soudain quelque chose attirera ...";
				link.l2.go = "Торговля";
			}	
		break;
		
		case "Количество вбитого провианта":
			Diag.TempNode = "FishingBoat_1";
			iQty = sti(dialogEditStrings[3]);
			iTemp = makeint(pchar.GenQuest.FishingBoatITemp);
			pchar.GenQuest.FishingBoatIQty = iQty;
			iMoney = makeint(pchar.GenQuest.FishingBoatIMoney);
			if(iQty > iTemp)
			{
				dialog.text = "Tu en demandes trop... Je n'ai pas autant ! Peux-tu acheter moins ?";
				link.l1.edit = 3;
				link.l1 = "";	
				link.l1.go = "Количество вбитого провианта повтор";	
				link.l2 = "Tu sais, j'ai changé d'avis sur l'achat de tes provisions.";	
				link.l2.go = "exit";
			}	
			if(iQty < 1)
			{
				dialog.text = "Tu te moques de moi? As-tu besoin de provisions ou non? Si oui, combien?";
				link.l1.edit = 3;
				link.l1 = "";	
				link.l1.go = "Количество вбитого провианта повтор";	
				link.l2 = "Tu sais, j'ai changé d'avis sur l'achat de tes provisions.";	
				link.l2.go = "exit";
			}
			if(iQty > 0 && iQty <= iTemp)
			{
				dialog.text = "Marché conclu ! "+sti(iQty*iMoney)+" pesos.";
				if(sti(pchar.money) < iQty*iMoney)
				{
					link.l1 = "Hmm, je n'ai pas beaucoup d'argent. Une autre fois.";
					link.l1.go = "exit";
				}
				else
				{
					link.l1 = "Marché conclu ! Amenez les marchandises à mon navire.";
					link.l1.go = "Удачная покупка";
					link.l2 = "Vous savez, j'ai changé d'avis sur l'achat de vos provisions.";
					link.l2.go = "exit";
				}
			}
		break;
		
		case "Количество вбитого провианта повтор":
			Diag.TempNode = "FishingBoat_1";
			iQty = sti(dialogEditStrings[3]);
			iTemp = makeint(pchar.GenQuest.FishingBoatITemp);
			pchar.GenQuest.FishingBoatIQty = iQty;
			iMoney = makeint(pchar.GenQuest.FishingBoatIMoney);
			if(iQty > iTemp)
			{
				dialog.text = "Tu en demandes trop... Je n'ai pas autant! Peux-tu acheter moins?";
				link.l1.edit = 3;
				link.l1 = "";	
				link.l1.go = "Количество вбитого провианта";	
				link.l2 = "Vous savez, j'ai changé d'avis sur l'achat de vos provisions.";	
				link.l2.go = "exit";
			}	
			if(iQty < 1)
			{
				dialog.text = "Tu te moques de moi? As-tu besoin de provisions ou non? Si oui, combien?";
				link.l1.edit = 3;
				link.l1 = "";	
				link.l1.go = "Количество вбитого провианта";	
				link.l2 = "Tu sais, j'ai changé d'avis sur l'achat de tes provisions.";	
				link.l2.go = "exit";
			}
			if(iQty > 0 && iQty <= iTemp)
			{
				dialog.text = "Marché conclu !"+sti(iQty*iMoney)+" pesos.";
				if(sti(pchar.money) < iQty*iMoney)
				{
					link.l1 = "Hmm, je n'ai pas tant d'argent. Une autre fois.";
					link.l1.go = "exit";
				}
				else
				{
					link.l1 = "Marché conclu ! Transportez les marchandises sur mon navire.";
					link.l1.go = "Удачная покупка";
					link.l2 = "Vous savez, j'ai changé d'avis sur l'achat de vos provisions.";
					link.l2.go = "exit";
				}
			}
		break;
		
		case "Удачная покупка":
			Diag.TempNode = "First time";
			Diag.CurrentNode = "First time";
			iQty = makeint(pchar.GenQuest.FishingBoatIQty);
			iMoney = makeint(pchar.GenQuest.FishingBoatIMoney);
			iTemp = iQty*iMoney;
			DialogExit();
			SetCharacterGoods(pchar, GOOD_FOOD, GetCargoGoods(pchar, GOOD_FOOD)+iQty);
			AddMoneyToCharacter(pchar, -iTemp);
		break;
		
		case "Гарпуны":
				Diag.TempNode = "FishingBoat_1";
				iTemp = 5+hrand(5);
				pchar.GenQuest.FishingBoatITemp = iTemp;
				dialog.text = "Nous avons "+iTemp+" des morceaux. Nous pouvons vendre pour cent pesos pour un harpon. Combien en avez-vous besoin?";
				link.l1.edit = 3;
				link.l1 = "";	
				link.l1.go = "Количество вбитых гарпунов";
				link.l2 = "Tu sais, j'ai changé d'avis, je n'ai pas besoin des harpons.";	
				link.l2.go = "exit";
		break;
		
		case "Количество вбитых гарпунов":
   
			iQty = sti(dialogEditStrings[3]);
			iTemp = makeint(pchar.GenQuest.FishingBoatITemp);
			pchar.GenQuest.FishingBoatIQty = iQty;
			Diag.TempNode = "FishingBoat_1";
			if(iQty > iTemp)
			{
				dialog.text = "Tu en demandes trop... Je n'ai pas autant! Peux-tu acheter moins?";
				link.l1.edit = 3;
				link.l1 = "";	
				link.l1.go = "Количество вбитых гарпунов заново";	
				link.l2 = "Tu sais, j'ai changé d'avis, je n'ai pas besoin des harpons.";	
				link.l2.go = "exit";
			}	
			if(iQty < 1)
			{
				dialog.text = "Tu te moques de moi? As-tu besoin de harpons ou non? Si oui, combien?";
				link.l1.edit = 3;
				link.l1 = "";	
				link.l1.go = "Количество вбитых гарпунов заново";	
				link.l2 = "Tu sais, j'ai changé d'avis, je n'ai pas besoin des harpons.";	
				link.l2.go = "exit";
			}
			if(iQty > 0 && iQty <= iTemp)
			{
				dialog.text = "Marché conclu! "+sti(iQty*100)+" pesos.";
				if(sti(pchar.money) < iQty*100)
				{
					link.l1 = "Hmm, je n'ai pas tant d'argent. Une autre fois.";
					link.l1.go = "exit";
				}
				else
				{
					link.l1 = "Marché conclu ! Je trouverai une utilité pour eux.";
					link.l1.go = "Удачная покупка гарпунов";
					link.l2 = "Tu sais, j'ai changé d'avis, je n'ai pas besoin des harpons.";
					link.l2.go = "exit";
				}
			}
		break;
		
		case "Количество вбитых гарпунов заново":
			iQty = sti(dialogEditStrings[3]);
			iTemp = makeint(pchar.GenQuest.FishingBoatITemp);
			pchar.GenQuest.FishingBoatIQty = iQty;
			Diag.TempNode = "FishingBoat_1";
			if(iQty > iTemp)
			{
				dialog.text = "Vous en demandez trop... Je n'ai pas autant ! Pouvez-vous acheter moins ?";
				link.l1.edit = 3;
				link.l1 = "";	
				link.l1.go = "Количество вбитых гарпунов";	
				link.l2 = "Tu sais, j'ai changé d'avis, je n'ai pas besoin des harpons.";	
				link.l2.go = "exit";
			}	
			if(iQty < 1)
			{
				dialog.text = "Tu te moques de moi? As-tu besoin de harpons ou non? Si oui, combien?";
				link.l1.edit = 3;
				link.l1 = "";	
				link.l1.go = "Количество вбитых гарпунов";	
				link.l2 = "Tu sais, j'ai changé d'avis, je n'ai pas besoin des harpons.";	
				link.l2.go = "exit";
			}
			if(iQty > 0 && iQty <= iTemp)
			{
				dialog.text = "Marché conclu! "+sti(iQty*100)+" pesos.";
				if(sti(pchar.money) < iQty*100)
				{
					link.l1 = "Hmm, je n'ai pas autant d'argent. Une autre fois.";
					link.l1.go = "exit";
				}
				else
				{
					link.l1 = "Marché conclu ! Je trouverai une utilité pour eux.";
					link.l1.go = "Удачная покупка гарпунов";
					link.l2 = "Tu sais, j'ai changé d'avis, je n'ai pas besoin des harpons.";
					link.l2.go = "exit";
				}
			}
		break;
		
		case "Удачная покупка гарпунов":
			DialogExit();
			Diag.TempNode = "First time";
			Diag.CurrentNode = "First time";
			iQty = makeint(pchar.GenQuest.FishingBoatIQty);
			TakeNItems(pchar, "slave_01", iQty);
			AddMoneyToCharacter(pchar, -iQty*100);
			
		break;
		
		case "Торговля":
			DialogExit();
			Diag.TempNode = "First time";
			Diag.CurrentNode = "First time";
			if(!CheckAttribute(pchar,"GenQuest.FishingBoatDialogEnb")) pchar.GenQuest.FishingBoatDialogEnb = true;
			LaunchItemsTrade(NPChar, 0);
		break;
		
		case "Особые товары":
			if(hrand(2, "&SpeGoo") == 0)
			{
				Diag.TempNode = "First time";
				Diag.CurrentNode = "First time";
				pchar.GenQuest.FishingBoatDialogEnb = "no special goods";
				dialog.text = "Non, il n'y a rien d'autre. C'est un bateau de pêche! Qu'est-ce qui pourrait être ici?";
				link.l1 = "D'accord, je comprends.";
				link.l1.go = "exit";
			}
			else if(hrand(2, "&SpeGoo") == 1)
			{
				if(ChangeContrabandRelation(pchar, 0) > 5)
				{
					
					dialog.text = "Eh bien ... J'ai une petite chose ici ... Je l'ai gardée, je pensais la vendre à quelqu'un. Mais je vais en demander beaucoup ! Et je n'offrirai pas une seconde fois. Tu veux regarder?";
					link.l1 = "Montre-moi, voyons ce genre de petite chose.";
					link.l1.go = "Особые товары предметы";
				}
				else
				{
					Diag.TempNode = "First time";
					Diag.CurrentNode = "First time";
					pchar.GenQuest.FishingBoatDialogEnb = "no special goods";
					dialog.text = "Non, il n'y a rien d'autre. C'est un bateau de pêche! Qu'est-ce qui pourrait être ici?";
					link.l1 = "D'accord, je comprends. ";
					link.l1.go = "exit";
				}
			}
			else
			{
				pchar.GenQuest.FishingBoatDialogEnb = "no special goods";
				Diag.TempNode = "First time";
				Diag.CurrentNode = "First time";
				if(ChangeContrabandRelation(pchar, 0) > 5)
				{
					if(GetDataDay() < 8)
					{	
						iMoney = GetStoreGoodsPrice(&Stores[SantaCatalina_STORE], GOOD_SANDAL, PRICE_TYPE_BUY, pchar, 1);
						iTemp = GOOD_SANDAL;
						sTemp = "units of backout";
					}
					if(GetDataDay() > 7 && GetDataDay() < 15)
					{
						iMoney = GetStoreGoodsPrice(&Stores[PortSpein_STORE], GOOD_OIL, PRICE_TYPE_BUY, pchar, 1);
						iTemp = GOOD_OIL;
						sTemp = "barrels of ship tar"; 
					}
					if(GetDataDay() > 14 && GetDataDay() < 22) 
					{
						iMoney = GetStoreGoodsPrice(&Stores[BasTer_STORE], GOOD_ROPES, PRICE_TYPE_BUY, pchar, 1);
						iTemp = GOOD_ROPES;
						sTemp = "bays of ship ropes"; 
					}
					if(GetDataDay() > 21) 
					{
						iMoney = GetStoreGoodsPrice(&Stores[Villemstad_STORE], GOOD_SHIPSILK, PRICE_TYPE_BUY, pchar, 1);
						iTemp = GOOD_SHIPSILK;
						sTemp = "rolls of ship silk";
					}
					iQty = 20 + sti(rand(6)*5);
					pchar.GenQuest.FishingBoatITemp = iTemp;
					pchar.GenQuest.FishingBoatIMoney = iMoney;
					pchar.GenQuest.FishingBoatIQty = iQty;
					
					dialog.text = "Eh bien ... J'ai ici une bonne chose ... Purement par hasard, je l'ai trouvée sur le rivage de la baie. C'est "+iQty+" "+sTemp+". Le prix par pièce est "+iMoney+". Mais je ne vendrai tout qu'une seule fois et je ne proposerai pas une seconde fois. Et pour que personne d'extérieur ne le sache ... comprends?";
					link.l1 = "Non, je ne veux pas des marchandises douteuses, merci. Je ne dirai à personne, ne t'inquiète pas.";
					link.l1.go = "exit";
					if(sti(pchar.money) >= iMoney*iQty)
					{
						link.l2 = "Je vous comprends. Mais les marchandises en valent la peine. Je les prends. Faites-les livrer à mon navire.";
						link.l2.go = "Купили стратегический товар";
					}
				}
			}
		break;
		
		case "Особые товары предметы":
			pchar.GenQuest.FishingBoatDialogEnb = "no special goods";
			Diag.TempNode = "First time";
			Diag.CurrentNode = "First time";
			if(ChangeContrabandRelation(pchar, 0) > 5)
			{
				switch(GetDataDay())
				{
					case 21: sTemp = "mushket1";  break;
					case 22: sTemp = "cirass5";   break;
					case 23: sTemp = "blade_16";  break;
					case 24: sTemp = "blade_04";  break;
					case 25: sTemp = "blade_06";  break;
					case 26: sTemp = "compass1";  break;
					case 27: sTemp = "clock2";    break;
					case 28: sTemp = "pistol4";   break;
					case 29: sTemp = "pistol2";   break;
					case 30: sTemp = "obereg_9";  break;
					case 31: sTemp = "obereg_10"; break;	
				}
				pchar.GenQuest.FishingBoatSTemp = sTemp;
				dialog.text = "C'est "+GetConvertStr("itmname_"+sTemp,"DescriptionDesObjets.txt")+". J'ai réussi à obtenir ... eh bien, peu importe où. Pensais à vendre à un connaisseur. Je te le donnerai pour seulement 10 000 pesos! Tu le prends?";
				if(sti(pchar.money) > 9999)
				{
					link.l1 = "Je le prendrai, bien sûr ! La chose est debout. ";
					link.l1.go = "Купили особый товар";
				}
				link.l2 = "Non, je n'en ai pas besoin. Je ne prendrai pas. ";
				link.l2.go = "exit";
			}
		
		break;
		
		case "Купили особый товар":
			Diag.TempNode = "First time";
			Diag.CurrentNode = "First time";
			DialogExit();
			sTemp = pchar.GenQuest.FishingBoatSTemp;
			if(GetDataDay() != 23 || GetDataDay() != 24 || GetDataDay() != 25) 
			{
				TakeNItems(pchar, sTemp, 1);
			}
			else
			{
				sTemp = GetGeneratedItem(sTemp);
				GiveItem2Character(pchar, sTemp);
			}
			AddMoneyToCharacter(pchar, -10000);
		break;
		
		case "Купили стратегический товар":
			Diag.TempNode = "First time";
			Diag.CurrentNode = "First time";
			iQty = makeint(pchar.GenQuest.FishingBoatIQty);
			iMoney = makeint(pchar.GenQuest.FishingBoatIMoney);
			iTemp = makeint(pchar.GenQuest.FishingBoatITemp);
			DialogExit();
			SetCharacterGoods(pchar, iTemp, GetCargoGoods(pchar,iTemp)+iQty);
			AddMoneyToCharacter(pchar, -iMoney*iQty);
		break;
		// <-- рыбацкое судно
	}
}

string GetNumShips(int ship)
{
    string numships;
    switch(ship)
    {
       case 0: numships = "no ships"; break;
       case 1: numships = "one ship";      break;
       case 2: numships = "two ships";       break;
       case 3: numships = "three ships";       break;
       case 4: numships = "four ships";    break;
       case 5: numships = "five ships";     break;
       case 6: numships = "six ships";    break;
    }
    return numships;
}

string GetPart(int part)
{
    string numpart;
    switch(part)
    {
       case 0: numpart = ""; break;
       case 1: numpart = "all loot"; break;
       case 2: numpart = "half of the loot"; break;
       case 3: numpart = "third of the loot"; break;
       case 4: numpart = "quarter of the loot";      break;
    }
    return numpart;
}

int findPriceStoreMan(ref NPChar)
{
    ref ch;
	int n;
    int storeArray[40];
    int howStore = 0;

	for(n=0; n<MAX_CHARACTERS; n++)
	{
		makeref(ch,Characters[n]);
		if (CheckAttribute(ch, "Dialog.Filename") && ch.Dialog.Filename == "Common_Store.c") // магазин
		{
            //if (sti(ch.nation) !=  sti(NPChar.nation)) continue;
            if (ch.location == "none") continue; // фикс для новых, невидимых до поры островов
            storeArray[howStore] = n;
            howStore++;
            
            // homo 05/09/06
            if ( CheckAttribute(NPChar, "FromColony") && NPChar.FromColony == ch.City ) return n;
            //
		}
    }
    if (howStore == 0)
    {
        return -1;
    }
    else
    {
        return storeArray[rand(howStore-1)];
    }
}
