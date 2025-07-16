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
					dialog.text = "Ciao, capitano. Accidenti, non hai idea di quanto io sia felice di vederti!";
					link.l1 = "Ciao. Mi permetta di presentarmi - "+GetFullName(PChar)+". Sono lieto di vederti vivo e vegeto anch'io, sono venuto qui appositamente per cercarti - e la tua nave.";
					link.l1.go = "WM_Captain";
					break;
				}
				if (CheckAttribute(PChar, "questTemp.WPU.Escort.LevelUp_1WM") && pchar.questTemp.WPU.Escort == "wait" && NPChar.id == "WMCaptain")
				{
					dialog.text = "Hai portato il materiale che ho richiesto?";
					if (sti(pchar.questTemp.WPU.Escort.Planks) - GetSquadronGoods(pchar, GOOD_PLANKS) <= 0 && sti(pchar.questTemp.WPU.Escort.Sailcloth) - GetSquadronGoods(pchar, GOOD_SAILCLOTH) <= 0 && sti(pchar.questTemp.WPU.Escort.Linen) - GetSquadronGoods(pchar, GOOD_COTTON) <= 0)
					{
						link.l1 = "Sì. Tutto ciò di cui hai bisogno per riparare la tua nave è nella mia stiva.";
						link.l1.go = "WM_Captain_5";
					}
					else
					{
						link.l1 = "No, ci sto ancora lavorando.";
						link.l1.go = "exit";
					}
					break;
				}
				if (CheckAttribute(PChar, "questTemp.WPU.Escort.LevelUp_1VSP") && pchar.questTemp.WPU.Escort == "toCap" && NPChar.id == "WMCaptain")
				{
					dialog.text = "Ciao, "+GetAddress_Form(NPChar)+". Il mio nome è "+GetFullName(NPChar)+", Io sono il capitano di questa nave. Permettete che vi esprima la mia più sincera gratitudine per il vostro aiuto in una lotta con questa maledetta feccia di pirati - se non fosse stato per il vostro intervento, le cose avrebbero potuto prendere una brutta piega per noi. Ci avete effettivamente salvato, accidenti!";
					link.l1 = "Non era niente,  "+GetAddress_FormToNPC(NPChar)+". Permettimi di presentarmi - "+GetFullName(PChar)+", sono venuto da te su richiesta del padrone del porto "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen")+". Mi ha informato sugli infortuni della vostra carovana e mi ha mandato a trovare la vostra nave.";
					link.l1.go = "VSP_Captain";
					break;
				}
				//<-- эскорт 2 уровень
				
				if(CheckAttribute(NPChar, "surrendered"))
				{
					Pchar.GenQuest.MoneyForCaptureShip = makeint(Group_GetLiveCharactersNum( GetGroupIDFromCharacter(NPChar)))*(8 - sti(RealShips[sti(NPChar.Ship.Type)].Class))*(1+rand(10))*500);
					if(HasShipTrait(pchar, "trait14")) Pchar.GenQuest.MoneyForCaptureShip = makeint(sti(Pchar.GenQuest.MoneyForCaptureShip) * 1.35);
					dialog.text = "Fermati, potresti uccidermi in questo modo. Cosa vuoi da me?";
					//выкуп
					link.l1 = "Risolviamo questa questione pacificamente. Il riscatto, suppongo, sarà la decisione migliore. Una somma di "+Pchar.GenQuest.MoneyForCaptureShip+" i pesos mi andranno benissimo, "+GetAddress_FormToNPC(NPChar)+". E dopo puoi sparire!";
					link.l1.go = "surrender1";
					// обираем до нитки
					link.l2 = "Mi piacerebbe vedere cosa avete nella vostra stiva. E dopo di ciò, tu e il tuo equipaggio potete andare dove volete.";
					link.l2.go = "surrender2";
					break;
				}
				
				//Голландский Гамбит, против всех
				if (CheckAttribute(PChar, "questTemp.HWIC.Self") && pchar.questTemp.HWIC.Self == "MeetingStivesant" && NPChar.id == "Stivesant")
				{
					dialog.text = "Salve, signore. Felice di vederla. Probabilmente il Capitano Longway salirà a bordo più tardi, giusto?";
					link.l1 = "Buon pomeriggio, signor Stuyvesant. Mi permetta di presentarmi - "+GetFullName(pchar)+". Longway non verrà, non è sulla 'Meifeng'.";
					link.l1.go = "Stivesant_1";
					pchar.quest.QuestShipsTerms_Over.over = "yes"; //снять таймер
					break;
				}
				if (CheckAttribute(PChar, "questTemp.HWIC.Self") && pchar.questTemp.HWIC.Self == "FleutOnTrinidad" && NPChar.id == "Keller")
				{
					DelLandQuestMark(npchar);
					dialog.text = "Ahoy, capitano. Cosa ti ha portato alla mia flauto?";
					link.l1 = "Buon pomeriggio, signor Keller. Mi permetta di presentarmi - "+GetFullName(pchar)+". Sono venuto a cercare il tuo aiuto in una questione insolita.";
					link.l1.go = "Keller_1";
					break;
					//Голландский гамбит
				}
				// belamour рыбацкое судно -->
				if(npchar.id == "FishingBoatCap")
				{
					if(!CheckAttribute(pchar, "GenQuest.FishingBoatSecondTime"))
					{
						Dialog.text = TimeGreeting()+", "+GetAddress_Form(NPChar)+"! Io sono il capitano di "+GetFullName(NPChar)+". Cosa ti porta a bordo della mia nave?";
						link.l1 = "E buon giorno a te. Cosa stai facendo in questa baia?";
						link.l1.go = "FishingBoat";
						break;
					}
					else
					{
						Diag.CurrentNode = "first time";
						dialog.text = "C'è qualcos'altro di cui vorresti parlare?";
						link.l1 = "Volevo"+GetSexPhrase("","")+"per scoprire le ultime notizie dall'arcipelago.";
						link.l1.go = "rumours_capitan";
						if(CheckAttribute(pchar,"GenQuest.FishingBoatDialogEnb"))
						{
							link.l2 = "Mostrami di nuovo, per favore, che tipo di gingilli hai in vendita. ";
							link.l2.go = "Торговля";
							if(pchar.GenQuest.FishingBoatDialogEnb != "нет особых товаров")
							{
								link.l3 = "Mmm, forse cerca di più nella stiva - forse troverai qualcosa da vendere?";
								link.l3.go = "Особые товары";
							}
						}
						link.l4 = "Niente di speciale, sono solo venuto a salutarti!";
						link.l4.go = "exit";	
						break;
					}
				}
				// <-- рыбацкое судно
				
				//belamour legendary edition диалоги, если герой имеет звания и заслуги перед отечеством -->
				// генерал губернатор
				if(CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE)
				{
					Dialog.text = "Governatore Generale, Vostra Grazia, saluti! Cosa posso fare per voi?";
					link.l1 = "Ho un affare per te!";
					link.l1.go = "quests";
					link.l2 = "Niente di speciale, sono solo venuto a salutarti!";
					link.l2.go = "exit";
					break;
				}
				// вице адмирал
				if(isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && sti(Items[sti(pchar.EquipedPatentId)].Nation) == npchar.nation)
				{
					Dialog.text = "Benvenuto a bordo della mia nave, Viceammiraglio! Cosa posso fare per te?";
					link.l1 = "Ho degli affari per te!";
					link.l1.go = "quests";
					link.l2 = "Niente di speciale, sono venuto solo per salutarti!";
					link.l2.go = "exit";
					break;
				}
				// Офицер с патентом
				if(IsOfficerFullEquip() && sti(Items[sti(pchar.EquipedPatentId)].Nation) == npchar.nation)
				{
					Dialog.text = "Contento di vedere un collega, Capitano! Come posso aiutare?";
					link.l1 = "Ho un affare per te!";
					link.l1.go = "quests";
					link.l2 = "Niente di speciale, sono solo venuto a salutarti!";
					link.l2.go = "exit";
					break;
				}			
				// <-- legendary edition
                if (CheckAttribute(NPChar, "EncType")  && NPChar.EncType == "war")
                {
    			    Dialog.text = TimeGreeting()+", "+GetAddress_Form(NPChar)+"! Sono "+GetFullName(NPChar)+" - capitano di una nave appartenente alla "+NationKingsName(NPChar)+". flotta. Cosa ti ha portato a bordo della mia nave?";
    			}
    			else
                {
    			    Dialog.text = TimeGreeting()+", "+GetAddress_Form(NPChar)+"! Sono il capitano "+GetFullName(NPChar)+". Cosa ti ha portato a bordo della mia nave?";
    			}
    			link.l1 = "Il mio nome è "+GetFullName(Pchar)+". Ho degli affari con te!";
    			link.l1.go = "quests";
                link.l2 = "Oh, niente, solo "+GetSexPhrase("venne","venuto")+" per salutarti!";
    			link.l2.go = "exit";
            }
            else
            {
                Dialog.text = "Non hai notato, , "+GetAddress_Form(NPChar)+", che siamo in una battaglia? Non è il momento di parlare!";
    			link.l1 = "Assolutamente d'accordo! Ritornerò alla mia nave.";
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
					Dialog.text = TimeGreeting()+", "+GetAddress_Form(NPChar)+"! Sono il capitano di "+GetFullName(NPChar)+". Cosa ti porta a bordo della mia nave?";
					link.l1 = "E buon giorno a te. Cosa stai facendo in questa baia?";
					link.l1.go = "FishingBoat";
					break;
				}
				else
				{
					dialog.text = "C'è altro di cui vorresti parlare?";
					link.l1 = "Volevo"+GetSexPhrase("","")+"per scoprire le ultime novità dall'arcipelago.";
					link.l1.go = "rumours_capitan";
					if(CheckAttribute(pchar,"GenQuest.FishingBoatDialogEnb"))
					{
						link.l2 = "Mostrami di nuovo, per favore, che tipo di gingilli hai in vendita. ";
						link.l2.go = "Торговля";
						if(pchar.GenQuest.FishingBoatDialogEnb != "no special goods")
						{
							link.l3 = "Mah, forse cerca di più nella stiva - forse si troverà qualcosa da vendere?";
							link.l3.go = "Особые товары";
						}
					}
					link.l4 = "Niente di speciale, sono solo venuto a salutarti!";
					link.l4.go = "exit";	
					break;
				}
			}
			// <-- рыбацкое судно
            if (!CheckAttribute(NPChar, "MainCaptanId")  || NPChar.MainCaptanId == pchar.GenQuest.CaptainId)
            {
                Dialog.text = "Ti sto ascoltando molto attentamente,  "+GetAddress_Form(NPChar)+".";
                link.l1 = "Voglio sapere le ultime notizie dell'arcipelago.";
                //homo 25/06/06
                link.l1.go = "rumours_capitan";
                //belamour legendary edition 
				bOk1 = isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && GetNationRelation(npchar.nation, sti(Items[sti(pchar.EquipedPatentId)].Nation)) != RELATION_ENEMY;
				bOk2 = CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && GetNationRelation(npchar.nation, FRANCE) != RELATION_ENEMY;
				bOk = bOk1 || bOk2;
                if (CheckAttribute(NPChar, "EncGroupName") && !bOk) // только для фантомов грабеж
                {
                    link.l2 = RandPhraseSimple("Hai idea di chi sono? Credo che sia perfettamente chiaro che le mie pistole possono trasformare la tua vecchia tinozza in un colabrodo. Risolviamo questo in modo pacifico. Il riscatto mi sembra una buona soluzione.","Solo noi ... e il mare ... Cosa ne pensi di calmare i miei uomini ... per la tua stessa sicurezza?");
                    link.l2.go = "Talk_board";
                }
                if (CheckAttribute(NPChar, "Ship.Mode") && NPChar.Ship.Mode == "Trade")
                {
	           		link.l3 = "Da dove vieni?";
	    			link.l3.go = "price_1";
	    			link.l4 = "Vuoi fare un scambio?";
	    			link.l4.go = "Trade_1";
    			}
				//--> квест мэра, поиски пирата
				if (CheckAttribute(pchar, "GenQuest.DestroyPirate"))
				{
	    			link.l6 = "Cerco una nave pirata che agisce in queste acque. Hai visto qualcosa di sospetto?";
	    			link.l6.go = "MQ_step_1";
				}
				//<-- квест мэра, поиски пирата
    			link.l5 = "Vuoi rilassarti?";
			    link.l5.go = "Play_Game";
                link.l9 = "Suppongo che dovrei andare.";
    			link.l9.go = "exit";
			}
			else
			{
                Dialog.text = "Non sono autorizzato a trattare con te. Parla con il comandante del nostro squadrone. Il suo nome è  "+GetFullName(characterFromID(NPChar.MainCaptanId))+", lo puoi trovare sul "+XI_ConvertString(RealShips[sti(characters[GetCharacterIndex(NPChar.MainCaptanId)].Ship.Type)].BaseName)+" '"+characters[GetCharacterIndex(NPChar.MainCaptanId)].Ship.Name+"'.'";
                link.l1 = "Grazie. Farò come dici tu.";
                link.l1.go = "exit";
                Diag.TempNode = "Go_away_Good";
			}
        break;
        case "Trade_1":
			dialog.text = "Perché no?";
			link.l1 = "Andiamo a vedere la merce.";
			link.l1.go = "Trade_2";
			link.l2 = "Ho cambiato idea.";
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
			dialog.text = "Cosa stai suggerendo?";
			link.l1 = "Vuoi giocare a carte per dei soldi seri?";
			link.l1.go = "Card_Game";
   			link.l2 = "Che ne dici di giocare a dadi nel poker-joker?";
			link.l2.go = "Dice_Game";
			link.l10 = "Mi dispiace, ma ho degli affari da sbrigare.";
			link.l10.go = "exit";
		break;
        // карты -->
        case "Card_Game":
            if (!CheckNPCQuestDate(npchar, "Card_date_Yet") || isBadReputation(pchar, 30) || GetCharacterSkillToOld(pchar, SKILL_LEADERSHIP) < rand(3))
            {
                SetNPCQuestDate(npchar, "Card_date_Yet");
                dialog.text = "Non giocherò con i furfanti!";
    			link.l1 = "Come desideri.";
    			link.l1.go = "exit";
			}
			else
			{
                dialog.text = "Perché no? Certamente non mi dispiacerebbe una pausa...";
    			link.l1 = "Eccellente.";
    			link.l1.go = "Cards_begin";
    			link.l2 = "Quali sono le regole?";
    			link.l2.go = "Cards_Rule";
			}
		break;

		case "Cards_Rule":
   			dialog.text = CARDS_RULE;
			link.l1 = "Bene, allora cominciamo!";
			link.l1.go = "Cards_begin";
			link.l3 = "No, non è per me...";
			link.l3.go = "exit";
		break;

		case "Cards_begin":
			Dialog.text = "Prima concordiamo sulla scommessa.";
			link.l1 = "Giochiamo per 100 pesos.";
			link.l1.go = "Cards_Node_100";
			link.l2 = "Giochiamo per 500 pesos.";
			link.l2.go = "Cards_Node_500";
			link.l3 = "Suppongo che dovrei andare.";
			link.l3.go = "exit";
		break;

		case "Cards_Node_100":
		    if (sti(pchar.Money) < 300)
		    {
                dialog.text = "Stai scherzando o cosa? Non hai soldi!";
                link.l1 = "Succede.";
			    link.l1.go = "exit";
			    break;
		    }
		    if (sti(npchar.Money) < 300)
		    {
                dialog.text = "Bene, basta così, o non avrò abbastanza soldi per mantenere la nave...";
                link.l1 = "Peccato.";
			    link.l1.go = "exit";
			    break;
		    }
   			dialog.text = "Bene, giochiamo per 100 monete.";
			link.l1 = "Iniziamo!";
			link.l1.go = "Cards_begin_go";
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
            pchar.GenQuest.Cards.iRate     = 100;
            pchar.GenQuest.Cards.SitType   = false;
		break;

		case "Cards_Node_500":
		    if (sti(pchar.Money) < 1500)
		    {
                dialog.text = "Stai scherzando o cosa? Non hai 1500 pesos!";
                link.l1 = "Li troverò!";
			    link.l1.go = "exit";
			    break;
		    }
		    if (sti(npchar.Money) < 1500)
		    {
                dialog.text = "No, queste scommesse mi faranno sicuramente finire alla fine.";
                link.l1 = "Come desideri.";
			    link.l1.go = "exit";
			    break;
		    }
   			dialog.text = "Bene, giochiamo per 500 monete.";
			link.l1 = "Iniziamo!";
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
                dialog.text = "Non giocherò con i furfanti!";
    			link.l1 = "Come desideri.";
    			link.l1.go = "exit";
			}
			else
			{
				if (CheckNPCQuestDate(npchar, "Dice_date_begin"))
				{
					dialog.text = "Perché no! Rilassarsi è sempre buono per la salute... ma non sempre per il borsellino...";
	    			link.l1 = "Eccellente.";
	    			link.l1.go = "Dice_begin";
	    			link.l2 = "Quali sono le regole del nostro gioco?";
	    			link.l2.go = "Dice_Rule";
    			}
    			else
    			{
					dialog.text = "No, ho finito per oggi. Ho cose da fare.";
	    			link.l1 = "Come desideri.";
	    			link.l1.go = "exit";
				}
			}
		break;

		case "Dice_Rule":
   			dialog.text = DICE_RULE;
			link.l1 = "Bene, allora cominciamo!";
			link.l1.go = "Dice_begin";
			link.l3 = "No, non fa per me...";
			link.l3.go = "exit";
		break;

		case "Dice_begin":
			Dialog.text = "Concordiamo prima sulla scommessa.";
			link.l1 = "Giochiamo per 50 pesos.";
			link.l1.go = "Dice_Node_100";
			link.l2 = "Giochiamo per 200 pesos.";
			link.l2.go = "Dice_Node_500";
			link.l3 = "Suppongo che dovrei andare.";
			link.l3.go = "exit";
		break;

		case "Dice_Node_100":
			//belamour legendary edition 
			bOk1 = isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && GetNationRelation(npchar.nation, sti(Items[sti(pchar.EquipedPatentId)].Nation)) != RELATION_ENEMY;
			bOk2 = CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && GetNationRelation(npchar.nation, FRANCE) != RELATION_ENEMY;
			bOk = bOk1 || bOk2;
            if (!CheckDiceGameSmallRate() && !bOk)
		    {
                dialog.text = "Sei ben noto come un"+GetSexPhrase("imbroglione","imbroglione")+".. Non giocherò mai a dadi con te.";
                link.l1 = "È tutto falso! Bene, così sia.";
			    link.l1.go = "exit";
			    break;
		    }

			if (sti(pchar.Money) < 300)
		    {
                dialog.text = "Stai scherzando o cosa? Non hai soldi!";
                link.l1 = "Accade.";
			    link.l1.go = "exit";
			    break;
		    }
		    if (sti(npchar.Money) < 300)
		    {
                dialog.text = "Basta così! Ho finito con il gioco d'azzardo - prima che mi etichettino come un peculatore e mi costringano a lasciare la nave.";
                link.l1 = "Peccato.";
			    link.l1.go = "exit";
			    break;
		    }
   			dialog.text = "Bene, giochiamo per 50 monete.";
			link.l1 = "Iniziamo!";
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
                dialog.text = "Sei ben noto come un"+GetSexPhrase("imbroglione","imbroglione")+". Non giocherò mai a dadi con te.";
                link.l1 = "È tutto bugie! Beh, sia così.";
			    link.l1.go = "exit";
			    break;
		    }
			if (!CheckDiceGameBigRate())
		    {
                dialog.text = "Ho sentito dire che sei un giocatore molto bravo. Non giocherò a poste alte con te.";
                link.l1 = "Dobbiamo abbassare la scommessa, forse?";
			    link.l1.go = "Dice_Node_100";
				link.l2 = "Mi dispiace, ma devo andare.";
			    link.l2.go = "exit";
			    break;
		    }

			if (sti(pchar.Money) < 1500)
		    {
                dialog.text = "Stai scherzando o cosa? Non hai 1500 pesos!";
                link.l1 = "Li troverò!";
			    link.l1.go = "exit";
			    break;
		    }
		    if (sti(npchar.Money) < 1500)
		    {
                dialog.text = "No, queste scommesse mi porteranno sicuramente alla fine.";
                link.l1 = "Come desideri.";
			    link.l1.go = "exit";
			    break;
		    }
   			dialog.text = "Bene, giochiamo per 200 monete.";
			link.l1 = "Iniziamo!";
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
	                Dialog.Text = "Perché vuoi saperlo? Questa è la mia privacy.";
					Link.l1 = "Come desideri.";
					Link.l1.go = "exit";
	            }
	            else
	            {
                    sld = &Characters[iMoney];
                    pchar.PriceList.ShipStoreIdx = iMoney;
                    
					Dialog.Text = "Vengo dalla città di"+GetCityName(sld.City)+".";
					Link.l1 = "Quali sono i prezzi dei beni nel negozio locale?";
					Link.l1.go = "price_2";
					Link.l9 = "Dovrei andare.";
					Link.l9.go = "exit";
				}
			}
			else
			{
                Dialog.Text = "Ti ho già detto tutto. Non infastidirmi per niente.";
				Link.l1 = "Sì, hai ragione. Addio.";
				Link.l1.go = "exit";
            }
		break;
		
		case "price_2":
            sld = &Characters[sti(pchar.PriceList.ShipStoreIdx)];
			SetPriceListByStoreMan(&Colonies[FindColony(sld.City)]);
			Dialog.Text = "Eccolo... (hai ricevuto la lista dei prezzi)..";
			Link.l1 = "Grazie mille!";
			Link.l1.go = "exit";
			PlaySound("interface\important_item.wav");
		break;
		
        case "Talk_board":
            if ((Group_GetCharactersNum(NPChar.EncGroupName) - Group_GetDeadCharactersNum(NPChar.EncGroupName)) > GetCompanionQuantity(PChar) && rand(11) > GetCharacterSkillToOld(PChar, SKILL_FORTUNE))
            {
                Dialog.text = "Ah-ah-ah! Ottimo scherzo, ho più navi. Torna alla tua nave e affonda con essa.";
                link.l1 = "Più non significa più forte, compagno.";
                link.l1.go = "Boarding";
            }
            else
            {
                if(rand(21) > (GetSummonSkillFromNameToOld(PChar, SKILL_GRAPPLING) + GetSummonSkillFromNameToOld(PChar, SKILL_LEADERSHIP)) )
                {
                    Dialog.text = "Capitano, non avresti dovuto fare i tuoi sporchi affari a bordo della mia nave. Ma mostrerò pietà e ti permetterò di tornare sulla tua nave per affogare con essa.";
                    link.l1 = "Vedremo, chi diventerà il cibo per gli squali oggi!";
                    link.l1.go = "Boarding";
                }
                else
                {
                    Pchar.GenQuest.MoneyForCaptureShip = makeint(100 + (Group_GetCharactersNum(NPChar.EncGroupName) - Group_GetDeadCharactersNum(NPChar.EncGroupName))*(8 - sti(RealShips[sti(NPChar.Ship.Type)].Class))*(1+rand(10))*500);
					if(HasShipTrait(pchar, "trait14")) Pchar.GenQuest.MoneyForCaptureShip = makeint(sti(Pchar.GenQuest.MoneyForCaptureShip) * 1.35);
                    Dialog.text = RandSwear()+"Sì, ho sentito molto parlare delle tue oltraggi. Così sia, ma ricorda "+XI_ConvertString(NationShortName(sti(NPChar.nation))+"cacciatore")+" non lo lascerò impunito!";
                    link.l1 = "Eccellente. Una somma di "+Pchar.GenQuest.MoneyForCaptureShip+" i pesos mi andranno bene, "+GetAddress_FormToNPC(NPChar)+".";
                    link.l1.go = "Capture";
                    link.l2 = "Oh, non importa. Stavo solo scherzando"+GetSexPhrase("","")+"!";
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
            Dialog.Text = "Ecco a te - e ora sparisci!";
			Link.l1 = "Bene! E rimani anche tu in salute, amico!";
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
			Dialog.Text = "Cosa altro vuoi da me?";
			Link.l1 = "Niente.";
			Link.l1.go = "exit";
			Diag.TempNode = "surrender_goaway";
		break;
		
		case "surrender2":			
			dialog.text = "Sembra che non ho altra scelta se non sottomettermi a te.";
			link.l1 = "Vai avanti, ora!";
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
			Link.l1 = RandPhraseSimple(RandSwear()+"Questo è molto interessante. Un'altra domanda?","Solo un altro affare.");
			Link.l1.go = "quests";
			Link.l2 = RandPhraseSimple("Grazie, e dovrei andare.","Tutto il meglio.");
			Link.l2.go = "exit";
			Diag.TempNode = "quests";
		break;
		
		case "Go_away":
			Dialog.Text = "Esci dalla mia nave!";
			Link.l1 = "Sto già andando via.";
			Link.l1.go = "exit";
			Diag.TempNode = "Go_away";
		break;
		
		case "Go_away_Good":
			Dialog.Text = "La nostra conversazione è finita. Non ho intenzione di dirti nulla di nuovo "+GetAddress_Form(NPChar)+".";
			Link.l1 = "Bene. Ci vediamo in mare!";
			Link.l1.go = "exit";
			Diag.TempNode = "Go_away_Good";
		break;

        case "Capture":
            Diag.TempNode = "Go_away";
            Dialog.Text = "Eccoti - e ora via!";
			Link.l1 = "Bene!";
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
            Dialog.Text = "Aspetta, potresti uccidermi in questo modo. Cosa vuoi da me?";
			Link.l1 = "Per ucciderti!";
			Link.l1.go = "QuestAboardCabinDialog_1";
			Link.l2 = "Arrenditi!";
			Link.l2.go = "QuestAboardCabinDialog_2";
			Link.l3 = "Dacci la mappa, Billy (c)";  // предмет, далее не ясно или  QuestAboardCabinDialog_1 или QuestAboardCabinDialog_2
			Link.l3.go = "QuestAboardCabinDialog_3";  // можно закодить покидание корабля, но экипаж уже вырезан и тп...
        break;
        
        case "QuestAboardCabinDialog_1":
			Dialog.Text = "Bene, vedremo, bastardo!";
			Link.l1 = "E cosa dovrei vedere?";
			Link.l1.go = "exit";
			// тут можно восстановить НР противника (NPChar) или добавить парочку гардов против ГГ
			LAi_SetCurHPMax(NPChar);
			AddDialogExitQuestFunction("QuestAboardCabinDialogExitWithBattle"); // тут ругань обратно
		break;
		
		case "QuestAboardCabinDialog_2":
			Dialog.Text = "Bene, hai vinto!";
			Link.l1 = "Decisione intelligente!";
			Link.l1.go = "exit";
			AddDialogExitQuestFunction("QuestAboardCabinDialogSurrender");
		break;
		
		case "QuestAboardCabinDialog_3":
			Dialog.Text = "Spero che tu ti soffochi con!";
			Link.l1 = "Molto bene, mettiti nelle manette e chiudi la bocca, prigioniero.";
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
			Dialog.Text = ""+GetSexPhrase("Venuto qui","Venuto qui")+", ha combinato un pasticcio"+GetSexPhrase("","")+",e ha preso tutto"+GetSexPhrase("","")+", ora vuoi farmi diventare uno schiavo? Mai!";
			Link.l1 = "Allora preparati a morire.";
			Link.l1.go = "QuestAboardCabinDialog_1";
		break;
		//eddy. квест мэра, поиски пирата
		case "MQ_step_1":
			Dialog.Text = "No, non ho visto nessuna nave sospetta che sembrava di pirati.";
			Link.l1 = "Capisco.";
			Link.l1.go = "exit";
		break;
		
		//homo Наводка на купца
		case "MerchantTrap_Abordage":

			Dialog.Text = "Nel nome di "+NationKingsName(NPChar)+" arrenditi, "+GetSexPhrase("sporco pirata","sgualdrina ripugnante!")+"! Allora la tua vita sarà risparmiata fino a un tribunale equo, dove sarai giudicato per tutto "+NationNameSK(sti(NPChar.nation))+"navi che hai depredato"+GetSexPhrase("","")+".";
			Link.l1 = "Vaffanculo! Dovresti arrenderti!";
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
					dialog.text = "Sua Eccellenza, Governatore Generale! La sto ascoltando attentamente, ma la prego di essere breve: stiamo combattendo con "+fort+", e devo dirigere il corso della battaglia.";
				}
				else
				{
					if(isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && sti(Items[sti(pchar.EquipedPatentId)].Nation) == npchar.nation)
					{
						dialog.text = "Viceammiraglio! Ti ascolto attentamente, ma ho poco tempo: stiamo combattendo con "+fort+", e devo dirigere il corso della battaglia.";
					}
					else
					{
						dialog.text = "Ti sto ascoltando, ma esponiamo rapidamente lo scopo della tua visita, stiamo lottando con "+fort+", e devo dirigere il corso della battaglia.";
					}
				}
                link.l1 = "Ecco perché sono qui,  "+GetAddress_FormToNPC(NPChar)+".";
                link.l1.go = "attack_fort";

                link.l2 = "In tal caso non ruberò più del tuo tempo. Addio, "+GetAddress_FormToNPC(NPChar)+".";
                link.l2.go = "exit";
    			
            }
            else
            {
                Dialog.text = "Non sono autorizzato a trattare con te. Parla con il comandante del nostro squadrone. Il suo nome è  "+GetFullName(rchar)+", puoi trovarlo su "+XI_ConvertString(RealShips[sti(rchar.Ship.Type)].BaseName)+" ''"+rchar.Ship.Name+"''.";
                link.l1 = "Grazie. Farò come dici tu.";
                link.l1.go = "exit";
            
            }
            Diag.TempNode = "Siegehelp";
            
		break;
		
		case "attack_fort":
                dialog.text = "E cosa intendi?";
                link.l1 = "Posso aiutarti a schiacciare il forte della colonia di "+GetConvertStr(aData.Colony+" Città","LocLables.txt")+" e conquistare la città, e un bottino, risultando nel caso del nostro successo, dividiamo tra di noi.";
                link.l1.go = "Siegehelp_1";
                link.l2 = "Effettivamente, il mio affare non vale la pena del tuo tempo. Addio, "+GetAddress_FormToNPC(NPChar)+".";
                link.l2.go = "exit";
                Diag.TempNode = "Siegehelp_0";
		break;
		
		case "Siegehelp_0":
            Dialog.text = "Di nuovo tu? Pensavo che avessimo già discusso tutto.";
            link.l1 = "Hai ragione. Credo di aver dimenticato"+GetSexPhrase("","")+".";
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
                dialog.text = "E quale parte del bottino ti aspetti di ricevere?";
                link.l1 = "Una metà.";
                link.l1.go = "Big_part";
                link.l2 = "Un terzo.";
                link.l2.go = "Middle_part";
                link.l3 = "Un quarto.";
                link.l3.go = "Small_part";
            }
            else
            {
                dialog.text = "Non ho bisogno dei tuoi servizi, capitano! Prenderò questa colonia da solo e non ho bisogno di aiuto per farlo.";
                link.l1 = "Perché sei così sicuro, "+GetAddress_FormToNPC(NPChar)+", chiunque può avere un colpo di sfortuna.";
                link.l1.go = "attack_fort_03";
                link.l2 = "In questo caso non prenderò più del tuo tempo, "+GetAddress_FormToNPC(NPChar)+". Addio!";
                link.l2.go = "exit";
            }
			Diag.TempNode = "Siegehelp_0";

		break;
		
		case "attack_fort_03":
            if((sti(aData.iSquadronPower)*SquadronDamage - (ifortPower)*fortDamage) < 4000)
            {
                dialog.text = "D'altra parte, le mie navi sono piuttosto danneggiate in questa battaglia, e i rinforzi certamente non farebbero male. Se sei d'accordo su "+GetPart(4)+", allora, immagino, potremmo arrivare a un accordo.";
                link.l1 = "Questo mi conviene, "+GetAddress_FormToNPC(NPChar)+". Cercherò di assaltare il forte, e tu ci supporterai con il fuoco dei cannoni della tua nave.";
                link.l1.go = "attack_fort_04";
                aData.PartAttaksFort = 4;
                link.l2 = "Non sono così a buon mercato, "+GetAddress_FormToNPC(NPChar)+". Mi dispiace per la distrazione"+GetSexPhrase("","")+"ti distolgo dagli affari importanti. Addio!";
                link.l2.go = "exit";
            }else{
                dialog.text = "Ci sono abbastanza navi nel mio squadrone per ridurre questa fortezza in polvere - è solo questione di tempo. E ora, potresti per favore lasciare la mia nave? La vittoria mi aspetta!";
                link.l1 = "Ebbene, in tal caso, "+GetAddress_FormToNPC(NPChar)+", permettetemi di prendere il mio congedo. Addio!";
                link.l1.go = "exit";
            }
		    Diag.TempNode = "Siegehelp_0";
		break;
		case "Big_part":
            if( (sti(aData.iSquadronPower)*SquadronDamage - (ifortPower)*fortDamage) <= -1500)
            {
                dialog.text = "Le cannoniere del forte hanno danneggiato gravemente le mie navi, e potremmo sicuramente essere la parte perdente nella prossima battaglia. Accetto il tuo aiuto e concordo con i tuoi termini.";
                link.l1 = "Eccellente, "+GetAddress_FormToNPC(NPChar)+", in tal caso tenteremo di assaltare il forte, e tu ci supporterai con il fuoco dei cannoni della tua nave.";
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
					dialog.text = "Vostra Eccellenza, devo ancora riferire sui progressi dell'operazione ... Almeno lasciate che "+GetPart(4)+".";
				}
				else
				{
                dialog.text = "Non è troppo, capitano? Avete "+GetNumShips(GetCompanionQuantity(PChar))+", e il mio squadrone ha "+GetNumShips(Group_GetCharactersNum(sGroup))+". Posso offrirti "+GetPart(4)+". E consideralo giusto.";
				}
                aData.PartAttaksFort = 4;
                link.l1 = "Sono d'accordo"+GetSexPhrase("","")+", "+GetAddress_FormToNPC(NPChar)+", in tal caso assalterò il forte, e tu ci supporterai con il fuoco delle cannoniere della tua nave.";
                link.l1.go = "attack_fort_04";
                link.l2 = "Sfortunatamente, non credo, "+GetAddress_FormToNPC(NPChar)+". Non c'è altro da discutere. Addio.";
                link.l2.go = "exit";
            }
            Diag.TempNode = "Siegehelp_0";
        break;
        
        case "attack_fort_04":
            dialog.text = "Non appena il forte sarà catturato, cominceremo a sbarcare squadre sulla riva, e poi continueremo a combattere nella città stessa, dove spero di incontrarti.";
            link.l1 = "Così sia. A presto, "+GetAddress_FormToNPC(NPChar)+"!";
            link.l1.go = "exit";
            Diag.TempNode = "Siegehelp_0";
            PChar.quest.Union_with_Escadra = "Yes";
        break;

        case "Middle_part":
            if((sti(aData.iSquadronPower)*SquadronDamage - (ifortPower)*fortDamage) <= -600)
            {
                dialog.text = "Credo che accetterò le tue condizioni. Un'operazione congiunta aumenterà le mie possibilità di vincere questa battaglia. Se tutto va come previsto, riceverai la tua parte del bottino.";
                link.l1 = "È fantastico che siamo arrivati a un accordo, "+GetAddress_FormToNPC(NPChar)+". Ordinerò ai miei uomini di assaltare il forte immediatamente.";
                link.l1.go = "attack_fort_04";
                aData.PartAttaksFort = 3;
            }else{
				// belamour legendary edition
				bOk1 = isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation);
				bOk2 = CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE;
				bOk = bOk1 || bOk2;
				if(bOk)
				{
					dialog.text = "Vostra Eccellenza, devo ancora riferire sui progressi dell'operazione ... Almeno lasciatemi "+GetPart(4)+".";
				}
				else
				{
                dialog.text = "Non è troppo, capitano? Hai "+GetNumShips(GetCompanionQuantity(PChar))+", e il mio squadrone ha "+GetNumShips(Group_GetCharactersNum(sGroup))+". Posso offrirti "+GetPart(4)+". E consideralo giusto.";
				}
                link.l1 = "Io "+GetSexPhrase("d'accordo","d'accordo")+", "+GetAddress_FormToNPC(NPChar)+", in tal caso assalterò il forte, e tu ci sosterrai con il fuoco dei cannoni della tua nave.";
                link.l1.go = "attack_fort_04";
                aData.PartAttaksFort = 4;
                link.l2 = "Sfortunatamente, non penso di sì, "+GetAddress_FormToNPC(NPChar)+". Non c'è altro da discutere. Addio.";
                link.l2.go = "exit";
            }
            Diag.TempNode = "Siegehelp_0";
        break;

        case "Small_part":
            dialog.text = "Le mie navi sono stanche, e qualsiasi forza fresca è benvenuta in questa situazione. Accetto il tuo aiuto e sono d'accordo con i tuoi termini.";
            link.l1 = "Sono contento"+GetSexPhrase("","")+", "+GetAddress_FormToNPC(NPChar)+".. Ordinerò immediatamente ai miei uomini di iniziare l'assalto al forte.";
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
            dialog.text = "Ciao, capitano! È stata sicuramente una battaglia dura, ma siamo riusciti a spezzare la furiosa resistenza dei difensori della città. Abbiamo saccheggiato "+sti(aData.loot)+" pesos. Secondo il nostro accordo, la tua parte è "+ilt+". Please accept this money; you certainly deserve every last coin of it. And now please excuse me, but I must return to my business.";
            link.l1 = "In tal caso, vi lascio, "+GetAddress_FormToNPC(NPChar)+". Addio!";
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
            dialog.text = "Ahoy, capitano! Hai affari con me?";
            link.l1 = "No, "+GetAddress_FormToNPC(NPChar)+". Addio!";
            link.l1.go = "exit";
            Diag.TempNode = "no_return_02";
		break;
		
		case "GoldSquadron":
            ref rch = Group_GetGroupCommander("Sea_Head_of_Gold_Squadron");
            if (NPChar.id == rch.id)
            {
    			dialog.text = "Ti sto ascoltando, ma per favore sii veloce riguardo allo scopo della tua visita, non ho molto tempo. Ho una missione importante e segreta, e mi è stato ordinato di affondare tutte le navi sospette in mare aperto, che potrebbero presentare un pericolo per il nostro convoglio.";                          
                link.l1 = "In tal caso non prenderò più del tuo tempo. Buona fortuna, "+GetAddress_FormToNPC(NPChar)+".";
                link.l1.go = "exit";

            }
            else
            {
                Dialog.text = "Non sono autorizzato a trattare con te. Parla con il comandante del nostro squadrone. Il suo nome è "+GetFullName(rch)+", puoi trovarlo su "+XI_ConvertString(RealShips[sti(rch.Ship.Type)].BaseName)+" ''"+rch.Ship.Name+"''.";
                link.l1 = "Grazie. Farò come dici.";
                link.l1.go = "exit";

            }
            Diag.TempNode = "GoldSquadron";
		break;
		
		case "WM_Captain":
			dialog.text = "Piacere di conoscerti, e il mio nome è "+GetFullName(npchar)+". Quindi sei venuto ad aiutarci? In tal caso sono particolarmente contento, dato che la nostra situazione attuale è davvero critica - siamo soli sulla costa di un'isola disabitata, la nave è a malapena navigabile, l'equipaggio ha subito pesanti perdite...";
			link.l1 = "Come ho sentito, hai avuto una battaglia con i pirati, e poi c'è stata quella tempesta...";
			link.l1.go = "WM_Captain_1";
			pchar.quest.DesIsland_Over.over = "yes";//снять прерывание
		break;
		
		case "WM_Captain_1":
			dialog.text = "Corretto. La mia nave è stata gravemente danneggiata nella battaglia - abbiamo dovuto resistere perfino a un attacco di abbordaggio guidato da quei bastardi pirati. Poi, siamo stati sorpresi da una tempesta... oh, non voglio nemmeno pensarci. Siamo stati portati su questa spiaggia inospitale. Avevamo pregato tutto il giorno la Vergine Benedetta per salvarci dalla tempesta e per mantenere le nostre catene d'ancora intere\nE eccoci qui. Abbiamo riparato la nostra nave per una settimana, ma guarda tu stesso: sono rimasti solo cinquanta uomini e ci mancano anche le assi di legno - e dove dovremmo prenderle? Dalla giungla? Ovviamente. Lavorando duro ogni giorno eppure abbiamo solo la quinta parte del materiale totale necessario\nNavigare con tali danni è come commettere suicidio. Ora capisci come ci stiamo qui, capitano...";
			link.l1 = "Sì... La tua situazione è invidiabile. Pensiamo a cosa potremmo intraprendere e come posso aiutarti.";
			link.l1.go = "WM_Captain_2";
		break;
		
		case "WM_Captain_2":
			dialog.text = "Eh, vorrei avessimo abbastanza assi e tela da vele - in tal caso ripareremmo la nostra nave in una settimana\nCapitano, dal momento che sei venuto qui di proposito, forse potresti visitare il porto più vicino e comprare i materiali di cui abbiamo bisogno? Questo risolverebbe il nostro problema. Non preoccuparti delle monete, compenserò tutte le spese.";
			link.l1 = "Certo. Cosa devi esattamente consegnare, e quanto?";
			link.l1.go = "WM_Captain_3";
		break;
		
		case "WM_Captain_3":
			pchar.questTemp.WPU.Escort.Planks = 300 + hrand(5)*10;
			pchar.questTemp.WPU.Escort.Sailcloth = 150 + hrand(10)*10;
			pchar.questTemp.WPU.Escort.Linen = 70 + hrand(7)*10;
			dialog.text = "Ho già capito tutto questo. Considerando quello che abbiamo già, mi serve "+FindRussianQtyString(sti(pchar.questTemp.WPU.Escort.Planks))+" assi, "+FindRussianQtyString(sti(pchar.questTemp.WPU.Escort.Sailcloth))+" tela da vela e "+FindRussianQtyString(sti(pchar.questTemp.WPU.Escort.Linen))+" cotone. Con questi materiali, riusciremmo a riparare la nave in una settimana e poi potremmo metterci in viaggio.";
			link.l1 = "Bene. Ti porterò tutti i materiali di cui hai bisogno. Aspettami - tornerò non più tardi di dieci giorni.";
			link.l1.go = "WM_Captain_4";
		break;
		
		case "WM_Captain_4":
			dialog.text = "Grazie mille, capitano! Questo mi toglie un peso dalla mente. Staremo aspettando e pregando per il tuo ritorno di successo!";
			link.l1 = "Non ti preoccupare. Presto avrai tutto ciò di cui hai bisogno per la riparazione.";
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
			dialog.text = "Non vediamo l'ora del tuo ritorno, capitano!";
			link.l1 = "Salpate le ancore!";
			link.l1.go = "exit";
			Diag.TempNode = "WM_Captain_again";
		break;
		
		case "WM_Captain_5":
			dialog.text = "Eccellente! Ora possiamo iniziare a riparare la nave!";
			link.l1 = "I miei uomini vi daranno una mano - in questo modo sarà più veloce. Inoltre, devo accompagnarvi alla colonia di "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity)+", quindi quanto prima avremo finito con le riparazioni, meglio è per me.";
			link.l1.go = "WM_Captain_6";
		break;
		
		case "WM_Captain_6":
			pchar.questTemp.WPU.Current.TargetIslandID.Shore = SelectQuestShoreLocationFromSea(pchar.questTemp.WPU.Current.TargetIslandID);
			dialog.text = "Davvero, non ho idea di come ringraziarti adeguatamente, capitano... Per favore, ordina di scaricare i materiali in una baia chiamata "+XI_ConvertString(pchar.questTemp.WPU.Current.TargetIslandID.Shore)+" - lì abbiamo tutto pronto per le riparazioni.";
			link.l1 = "Bene. Ci incontreremo sulla riva.";
			link.l1.go = "exit";
			AddQuestRecord("Escort", "29");
			AddQuestUserData("Escort", "sShore", XI_ConvertString(pchar.questTemp.WPU.Current.TargetIslandID.Shore+"Gen"));
			pchar.quest.DisasterShip_WMC.win_condition.l1 = "location";
			pchar.quest.DisasterShip_WMC.win_condition.l1.location = pchar.questTemp.WPU.Current.TargetIslandID.Shore;
			pchar.quest.DisasterShip_WMC.function = "RepairShip_Prepare";
			Diag.TempNode = "WM_Captain_repeat";
		break;
		
		case "WM_Captain_repeat":
			dialog.text = "Quando inizieremo le riparazioni, capitano? Ti aspetterò sulla riva.";
			link.l1 = "Sì, certo. Sto andando ora.";
			link.l1.go = "exit";
			Diag.TempNode = "WM_Captain_repeat";
		break;
		
		case "Repair_start":
			dialog.text = "Bene, sembra che tutto sia pronto per la riparazione. Penso che dovremmo finire in circa cinque giorni.";
			link.l1 = "Molto bene! Avevo intenzione di esplorare quest'isola comunque, quindi farò buon uso di questo tempo.";
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
			dialog.text = "Ebbene, è tutto. Abbiamo finito con le riparazioni, e la nave è pronta a salpare. Quando partiamo, capitano?";
			link.l1 = "Se sei pronto, non vedo motivo di indugiare. Pesa le ancore!";
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
			log_info("You have 25 days to escort "+pchar.questTemp.WPU.Escort.ShipBaseName+" '"+pchar.questTemp.WPU.Escort.ShipName+"' al porto di "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen")+"");
			pchar.quest.DisasterShip_final.win_condition.l1 = "location";
			pchar.quest.DisasterShip_final.win_condition.l1.location = pchar.questTemp.WPU.Escort.StartCity +"_town";
			pchar.quest.DisasterShip_final.function = "WMShip_final";
		break;
		
		case "WMShip_final":
			pchar.quest.Escort_fail.over = "yes";
			pchar.quest.DisasterShipWM_Over.over = "yes";//снимаем оба прерывания
			RemoveCharacterCompanion(Pchar, characterFromID("WMCaptain"));//удаляем компаньона
			pchar.questTemp.WPU.Escort.LevelUp_1Money = sti(pchar.questTemp.WPU.Escort.Planks)*15+sti(pchar.questTemp.WPU.Escort.Sailcloth)*9+sti(pchar.questTemp.WPU.Escort.Linen)*45;//деньги за материалы
			dialog.text = "Voglio ringraziarti ancora una volta, capitano - mi hai aiutato moltissimo, a me e al mio equipaggio, a uscire da quella situazione difficile. Come promesso, compenserò i costi dei materiali necessari per riparare la mia nave. Ecco "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.LevelUp_1Money))+", per favore, prendili. E questo è il mio regalo personale per te.";
			link.l1 = "Ero felice di aiutarti.";
			link.l1.go = "WMShip_final_1";
		break;
		
		case "WMShip_final_1":
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.WPU.Escort.LevelUp_1Money));
			TakeNItems(pchar, "obereg_"+(hrand(10)+1), 1);
			dialog.text = "E ora, è il momento di dire addio, capitano. Non dimenticate di visitare l'autorità portuale - vi stanno aspettando lì. Arrivederci!";
			link.l1 = "Buona giornata, "+npchar.name+"!";
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
			dialog.text = "Davvero? E io pensavo che ci avessero dimenticato. Sì, la mia nave ha avuto la peggio di tutte. Siamo stati lasciati a lottare con gli elementi della natura dopo che la tempesta ha costretto i pirati a interrompere l'attacco alla nostra carovana. Siamo stati portati su questa costa inospitale\nAbbiamo passato alcuni giorni a ripararci e a riposare. Questi pagani ci hanno attaccato di nuovo, appena stavamo per salpare\nE poi la tempesta ci ha colpito di nuovo - pensavamo che il Signore avesse finalmente deciso di finirci, ma tu sei arrivato. Grazie alla Santa Maria! Grazie ancora, capitano!";
			link.l1 = "È tutto finito, "+GetAddress_FormToNPC(NPChar)+". Ora devo scortarti a "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen")+", per proteggerlo da altri possibili guai. Sei pronto a partire ora? La tempesta ha già iniziato a diminuire.";
			link.l1.go = "VSP_Captain_1";
		break;
		
		case "VSP_Captain_1":
			dialog.text = "Ma certo! Più presto lasciamo questo posto, più tranquilli saranno i miei uomini - hanno già sofferto troppo. Mettiamoci in viaggio!";
			link.l1 = "Solo segui la mia nave - e calma il tuo equipaggio, non c'è nulla da temere ora.";
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
			log_info("Hai 25 giorni per scortare "+pchar.questTemp.WPU.Escort.ShipBaseName+" '"+pchar.questTemp.WPU.Escort.ShipName+"' al porto di "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen")+"");
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
			dialog.text = "Dobbiamo salpare, capitano?";
			link.l1 = "Certo. Ora ritornerò alla mia nave.";
			link.l1.go = "exit";
			Diag.TempNode = "VSP_Captain_again";
		break;
		
		case "VSPShip_final":
			pchar.quest.Escort_fail.over = "yes";
			pchar.quest.DisasterShipWM_Over.over = "yes";//снимаем оба прерывания
			RemoveCharacterCompanion(Pchar, characterFromID("WMCaptain"));//удаляем компаньона
			pchar.questTemp.WPU.Escort.LevelUp_1Money = 10000+sti(pchar.rank)*200;
			dialog.text = "Voglio ringraziarti ancora una volta, capitano - tu e il tuo equipaggio mi avete aiutato enormemente a uscire da questo pasticcio. Ecco"+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.LevelUp_1Money))+". L'intero equipaggio ha contribuito, quindi nemmeno pensare di rinunciarci. E questo è il mio regalo personale per te.";
			link.l1 = "Ero felice di aiutarti!";
			link.l1.go = "WMShip_final_1";
		break;
		
		case "SShip_final":
			pchar.questTemp.WPU.Escort.LevelUp_1Money = 5000+sti(pchar.rank)*100;
			RemovePassenger(Pchar, npchar);//удаляем пассажира
			dialog.text = "Voglio ringraziarti di nuovo, capitano, per aver salvato i nostri culi da questo pasticcio. Prendi, accetta queste monete - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.LevelUp_1Money))+"  e qui, prendi questo dono. Non è molto, ma è tutto quello che posso fare per ringraziarti per quello che hai fatto. Per favore, non rifiutare l'offerta\nIl mio ex equipaggio è stupito da te e dalla tua lotta con gli indiani e i pirati. Tutti desiderano unirsi a te. Spero che non rifiuterai la richiesta di servizi leali da marinai che hanno appena perso la loro nave?";
			link.l1 = "Certo, no. Lo terrò volentieri. Ero felice di aiutarti!";
			link.l1.go = "WMShip_final_1";
		break;
		
		//Голландский Гамбит
		case "Stivesant_1":
			DelLandQuestMark(npchar);
			dialog.text = "Bene. Ma, signore, potrebbe spiegare cosa sta succedendo qui? Come mai sei al comando della 'Meifeng'! È successo qualcosa a Longway?";
			link.l1 = "Ho tutte le spiegazioni di cui hai bisogno - e anche altre informazioni importanti.";
			link.l1.go = "Stivesant_2";			
		break;
		
		case "Stivesant_2":
			dialog.text = "Allora sono tutto orecchie.";
			link.l1 = "C'è stato un colpo di stato a Willemstad. Lucas Rodenburg ha preso il posto del governatore e ha messo Matthias Beck in prigione su un ridicolo sospetto che avesse collegamenti con l'intelligence britannica.";
			link.l1.go = "Stivesant_3";			
		break;
		
		case "Stivesant_3":
			dialog.text = "Hmm... Signore, le cose che mi stai raccontando sono davvero sorprendenti. Non molto tempo fa ho ricevuto notizie da Willemstad, e non c'era nulla di simile.";
			link.l1 = "Per favore ascoltami, signor Stuyvesant. Devi aver ricevuto le notizie attraverso Rodenburg, e lui deve essere sicuro che non arriverai a Curacao.";
			link.l1.go = "Stivesant_4";			
		break;
		
		case "Stivesant_4":
			dialog.text = "Signore, mi piace sempre meno quello che dici. Chi diavolo sei?";
			link.l1 = "Sono solo un capitano e solo un uomo non indifferente al destino dei colonisti olandesi. Lucas Rodenburg ha ordinato a Longway di distruggere la tua nave e ucciderti. E siccome 'Meifeng' non avrebbe suscitato sospetti, l'avrebbe fatto senza alcuno sforzo.";
			link.l1.go = "Stivesant_5";			
		break;
		
		case "Stivesant_5":
			dialog.text = "Allora, intendi dire che Lucas...";
			link.l1 = "Deciso di rimuovere te dal potere nel modo più semplice possibile - eliminandoti semplicemente. Eccetto te, non c'è un'altra persona in grado di opporre una resistenza significativa all'influenza di Rodenburg sull'Arcipelago.";
			link.l1.go = "Stivesant_6";			
		break;
		
		case "Stivesant_6":
			dialog.text = "Non posso crederci!";
			link.l1 = "Non sono caduto in quella trappola con Beck collegato ai servizi segreti inglesi e ho intrapreso la mia indagine. Ho scoperto che 'Meifeng', carico di tagliagole scelti, è partito per Philipsburg. Li ho inseguiti e ho ingaggiato battaglia. Longway è stato catturato, e mi ha dato tutte queste informazioni, compreso il tuo luogo di rifugio.";
			link.l1.go = "Stivesant_7";			
		break;
		
		case "Stivesant_7":
			dialog.text = "Hm... Sembra probabile. Nessuno, tranne Rodenburg, sapeva o poteva sapere del mio programma e del mio percorso! Accidenti! È tradimento! Dov'è Longway?!";
			link.l1 = "L'ho liberato in cambio della sua confessione volontaria. Devo dire, non era troppo desideroso di eseguire l'ordine di Rodenburg, ma non poteva nemmeno ignorarlo. Ha anche detto che non tornerà al servizio di Rodenburg - questo ultimo sporco affare ha fatto traboccare il vaso.";
			link.l1.go = "Stivesant_8";			
		break;
		
		case "Stivesant_8":
			dialog.text = "Va bene... Capitano "+GetFullName(pchar)+", andrai con me a Willemstad. Navigherai sulla 'Meifeng' davanti alla mia nave. Se ciò che hai detto è vero, Lucas deve essere arrestato, e tu fornirai il tuo aiuto in questo. Ma se mi hai mentito... Puoi solo incolpare te stesso.";
			link.l1 = "Per me, non ha senso mentirti, signore. Affrettiamoci!";
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
			dialog.text = "Capitano, vai a 'Meifeng'. È ora per noi di salpare.";
			link.l1 = "Sì, mio signore, naturalmente.";
			link.l1.go = "exit";
			Diag.TempNode = "Stivesant_10";
		break;
		
		case "Keller_1":
			dialog.text = "Molto interessante! Per favore, racconta la tua storia. Farò del mio meglio per aiutarti.";
			link.l1 = "Signor Keller, ricordate quando avete incontrato un flauto sulla vostra strada per Willemstad alcuni mesi fa. C'era una famiglia di rifugiati ebrei a bordo. Avete cenato su quella nave e poi avete proseguito il vostro viaggio.";
			link.l1.go = "Keller_2";
		break;
		
		case "Keller_2":
			dialog.text = "Sì, immagino di sì... Sì, lo ricordo molto chiaramente ora. Allora, qual è l'affare?";
			link.l1 = "Quel flauto fu affondato dai pirati proprio quel giorno. Solo due rifugiati riuscirono a salvarsi - Salomone e sua figlia Abigail. Trovarono rifugio su un'isola a poche miglia dal luogo dell'attacco. Ho bisogno di trovare quell'isola. Potresti per favore ricordare dove hai incontrato quel flauto? È molto importante.";
			link.l1.go = "Keller_3";
		break;
		
		case "Keller_3":
			dialog.text = "E questo è tutto ciò di cui hai bisogno? Conosco quest'isola. È molto vicina, tra Trinidad e Curaçao. Una piccola isola deserta disabitata. Non ci sono nemmeno gli indiani lì.";
			link.l1 = "E conosci le sue coordinate approssimative?";
			link.l1.go = "Keller_4";
		break;
		
		case "Keller_4":
			dialog.text = "Posso darti le coordinate esatte. Si trova a 12  48'  Nord e 64  41'  Ovest. Cercalo lì. L'isola è piuttosto piccola, ma dovresti essere in grado di localizzarla facilmente.";
			link.l1 = "Grazie, signor Keller! Mi hai aiutato molto. Addio.";
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
			dialog.text = "Volevi qualcos'altro, capitano?";
			link.l1 = "No, grazie. Stavo già tornando alla mia nave.";
			link.l1.go = "exit";
			Diag.TempNode = "Keller_6";
		break;
		
		// belamour рыбацкое судно -->
		case "FishingBoat":
			pchar.GenQuest.FishingBoatSecondTime = true;
			dialog.text = "Niente di speciale, questa è una barca da pesca, qui pesciamo. Devi guadagnarti da vivere in qualche modo.";
			link.l1 = "Sì, concordo, questi sono i tempi...";
			link.l1.go = "FishingBoat_1";			
		break;
		
		case "FishingBoat_1":
			Diag.TempNode = "FishingBoat_1";
			dialog.text = "Allora, cosa vuoi?";
			link.l1 = "Volevo"+GetSexPhrase("","")+"per scoprire le ultime notizie dall'arcipelago.";
            link.l1.go = "rumours_capitan";
			link.l2 = "Come vanno le tue catture oggi? Puoi vendere? Non mi farebbero male delle provviste...";
			link.l2.go = "FishingBoat_2";
			link.l3 = "Niente di speciale, sono solo venuto a salutarti!";
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
				
				dialog.text = "La pesca è buona oggi, basta avere tempo per tirare fuori le reti. Possiamo venderla a te, anche più economico che in un negozio - comunque, vendiamo pesce a un commerciante locale. Se convertiamo tutto questo in provviste... Ora abbiamo "+iTemp+" di esso, possiamo venderlo a un prezzo di "+iMoney+" pesos a testa. Quanto ne prenderai?";
				link.l1.edit = 3;
				link.l1 = "";	
				link.l1.go = "Количество вбитого провианта";
				link.l2 = "Sai, ho cambiato idea sull'acquisto delle tue provviste.";	
				link.l2.go = "exit";
				
			}
			if(GetDataDay() > 10 && GetDataDay() < 21) 
			{
				Diag.TempNode = "FishingBoat_1";
				dialog.text = "Sì, qualcosa, per essere onesti, non ci sono pesci affatto... Oggi quasi non abbiamo pescato nulla. Ma sono rimasti dei arpioni superflui - pensavano di catturare qualche grosso pesce o una balena, se avessi avuto fortuna... Forse hai bisogno di arpioni?";
				link.l1 = "No, non sono interessato ad arpioni.";
				link.l1.go = "exit";
				link.l2 = "Mmm, un arpione è anche una cosa utile nelle mani giuste. Probabilmente lo comprerò.";
				link.l2.go = "Гарпуны";
			}
			if(GetDataDay() > 20)
			{
				dialog.text = "Sì, qualcosa, per essere onesto, non ci sono affatto pesci ... Oggi non ho quasi pescato nulla. Quindi non c'è molto da vendere. A meno che ... Ho qualche gingillo, forse qualcosa ti interesserà. Ti piacerebbe vedere?";
				link.l1 = "No, non sono interessato a gingilli.";
				link.l1.go = "exit";
				link.l2 = "È un peccato che non ci sia preda. Beh, diamo almeno un'occhiata ai tuoi gingilli - improvvisamente qualcosa attirerà ...";
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
				dialog.text = "Sei troppo... Non ho tanto! Puoi comprare di meno?";
				link.l1.edit = 3;
				link.l1 = "";	
				link.l1.go = "Количество вбитого провианта повтор";	
				link.l2 = "Sai, ho cambiato idea riguardo all'acquisto delle tue provviste.";	
				link.l2.go = "exit";
			}	
			if(iQty < 1)
			{
				dialog.text = "Stai scherzando con me? Hai bisogno di provviste o no? Se sì, quanto?";
				link.l1.edit = 3;
				link.l1 = "";	
				link.l1.go = "Количество вбитого провианта повтор";	
				link.l2 = "Sai, ho cambiato idea sull'acquisto delle tue provviste.";	
				link.l2.go = "exit";
			}
			if(iQty > 0 && iQty <= iTemp)
			{
				dialog.text = "Affare fatto! "+sti(iQty*iMoney)+" pesos.";
				if(sti(pchar.money) < iQty*iMoney)
				{
					link.l1 = "Mmm, non ho così tanti soldi. Un'altra volta.";
					link.l1.go = "exit";
				}
				else
				{
					link.l1 = "Affare fatto! Trascina le merci sulla mia nave.";
					link.l1.go = "Удачная покупка";
					link.l2 = "Sai, ho cambiato idea riguardo all'acquisto delle tue provviste.";
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
				dialog.text = "Sei troppo... Non ho così tanto! Puoi comprare meno?";
				link.l1.edit = 3;
				link.l1 = "";	
				link.l1.go = "Количество вбитого провианта";	
				link.l2 = "Sai, ho cambiato idea riguardo all'acquisto delle tue provviste.";	
				link.l2.go = "exit";
			}	
			if(iQty < 1)
			{
				dialog.text = "Stai scherzando? Hai bisogno di provviste o no? Se sì, quanto?";
				link.l1.edit = 3;
				link.l1 = "";	
				link.l1.go = "Количество вбитого провианта";	
				link.l2 = "Sai, ho cambiato idea riguardo all'acquisto delle tue provviste.";	
				link.l2.go = "exit";
			}
			if(iQty > 0 && iQty <= iTemp)
			{
				dialog.text = "Affare fatto! "+sti(iQty*iMoney)+" pesos.";
				if(sti(pchar.money) < iQty*iMoney)
				{
					link.l1 = "Mmm, non ho così tanti soldi. Un'altra volta.";
					link.l1.go = "exit";
				}
				else
				{
					link.l1 = "Affare fatto! Trasporta la merce sulla mia nave.";
					link.l1.go = "Удачная покупка";
					link.l2 = "Sai, ho cambiato idea riguardo all'acquisto delle tue provviste.";
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
				dialog.text = "Abbiamo "+iTemp+" pezzi. Possiamo vendere per cento pesos un arpione. Quanto ne hai bisogno?";
				link.l1.edit = 3;
				link.l1 = "";	
				link.l1.go = "Количество вбитых гарпунов";
				link.l2 = "Sai, ho cambiato idea, non ho bisogno dei arpioni.";	
				link.l2.go = "exit";
		break;
		
		case "Количество вбитых гарпунов":
   
			iQty = sti(dialogEditStrings[3]);
			iTemp = makeint(pchar.GenQuest.FishingBoatITemp);
			pchar.GenQuest.FishingBoatIQty = iQty;
			Diag.TempNode = "FishingBoat_1";
			if(iQty > iTemp)
			{
				dialog.text = "Sei troppo... Non ho così tanto! Puoi comprare di meno?";
				link.l1.edit = 3;
				link.l1 = "";	
				link.l1.go = "Количество вбитых гарпунов заново";	
				link.l2 = "Sai, ho cambiato idea, non ho bisogno dei arpioni.";	
				link.l2.go = "exit";
			}	
			if(iQty < 1)
			{
				dialog.text = "Stai scherzando con me? Hai bisogno di arpioni o no? Se sì, quanti?";
				link.l1.edit = 3;
				link.l1 = "";	
				link.l1.go = "Количество вбитых гарпунов заново";	
				link.l2 = "Sai, ho cambiato idea, non ho bisogno dei arpioni.";	
				link.l2.go = "exit";
			}
			if(iQty > 0 && iQty <= iTemp)
			{
				dialog.text = "Affare fatto! "+sti(iQty*100)+" pesos.";
				if(sti(pchar.money) < iQty*100)
				{
					link.l1 = "Mmm, non ho così tanti soldi. Un'altra volta.";
					link.l1.go = "exit";
				}
				else
				{
					link.l1 = "Affare fatto! Troverò un utilizzo per loro.";
					link.l1.go = "Удачная покупка гарпунов";
					link.l2 = "Sai, ho cambiato idea, non ho bisogno dei arpioni.";
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
				dialog.text = "Sei troppo ... Non ho così tanto! Puoi comprare di meno?";
				link.l1.edit = 3;
				link.l1 = "";	
				link.l1.go = "Количество вбитых гарпунов";	
				link.l2 = "Sai, ho cambiato idea, non ho bisogno dei arpioni.";	
				link.l2.go = "exit";
			}	
			if(iQty < 1)
			{
				dialog.text = "Stai scherzando con me? Hai bisogno di arpioni o no? Se sì, quanti?";
				link.l1.edit = 3;
				link.l1 = "";	
				link.l1.go = "Количество вбитых гарпунов";	
				link.l2 = "Sai, ho cambiato idea, non ho bisogno dei rampini.";	
				link.l2.go = "exit";
			}
			if(iQty > 0 && iQty <= iTemp)
			{
				dialog.text = "Affare fatto! "+sti(iQty*100)+" pesos.";
				if(sti(pchar.money) < iQty*100)
				{
					link.l1 = "Mah, non ho così tanti soldi. Un'altra volta.";
					link.l1.go = "exit";
				}
				else
				{
					link.l1 = "Affare fatto! Troverò un utilizzo per loro.";
					link.l1.go = "Удачная покупка гарпунов";
					link.l2 = "Sai, ho cambiato idea, non ho bisogno dei arpioni.";
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
				dialog.text = "No, non c'è nient'altro. È una barca da pesca! Cosa altro potrebbe esserci?";
				link.l1 = "Bene, ho capito.";
				link.l1.go = "exit";
			}
			else if(hrand(2, "&SpeGoo") == 1)
			{
				if(ChangeContrabandRelation(pchar, 0) > 5)
				{
					
					dialog.text = "Ebbene ... ho una piccola cosa qui ... l'ho conservata, pensavo di venderla a qualcuno. Ma te la farò pagare cara! E non offrirò una seconda volta. Vuoi dare un'occhiata?";
					link.l1 = "Mostrami, vediamo che tipo di cosetta.";
					link.l1.go = "Особые товары предметы";
				}
				else
				{
					Diag.TempNode = "First time";
					Diag.CurrentNode = "First time";
					pchar.GenQuest.FishingBoatDialogEnb = "no special goods";
					dialog.text = "No, non c'è altro. È una barca da pesca! Cosa altro potrebbe esserci?";
					link.l1 = "Bene, ho capito.";
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
					
					dialog.text = "Ebbene ... Ne ho uno buono qui ... Per puro caso l'ho trovato sulla riva della baia. È "+iQty+" "+sTemp+". Il prezzo per pezzo è "+iMoney+". Ma venderò tutto in una volta e non offrirò una seconda volta. E così che nessun estraneo lo sappia ... capisci?";
					link.l1 = "No, non voglio la merce discutibile, grazie. Non dirò a nessuno, non preoccuparti.";
					link.l1.go = "exit";
					if(sti(pchar.money) >= iMoney*iQty)
					{
						link.l2 = "Ti capisco. Ma la merce ne vale la pena. La prendo. Faglielo consegnare alla mia nave.";
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
				dialog.text = "È "+GetConvertStr("itmname_"+sTemp,"DescrizioneArticoli.txt")+". Sono riuscito a ottenere ... beh, non importa da dove. Pensavo di venderlo a qualche intenditore. Te lo darò per soli 10 000 pesos! Lo prenderai?";
				if(sti(pchar.money) > 9999)
				{
					link.l1 = "Lo prenderò, ovviamente! La cosa è in piedi.";
					link.l1.go = "Купили особый товар";
				}
				link.l2 = "No, non ne ho bisogno. Non prenderò. ";
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
