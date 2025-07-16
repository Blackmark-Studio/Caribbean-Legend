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
					dialog.text = "Witaj, kapitanie. Cholera, nie masz pojęcia, jak bardzo cieszę się, że cię widzę!";
					link.l1 = "Cześć. Pozwól, że się przedstawię - "+GetFullName(PChar)+". Cieszę się, że też cię widzę całego i zdrowego, specjalnie tu przybyłem, żeby cię szukać - i twojego statku.";
					link.l1.go = "WM_Captain";
					break;
				}
				if (CheckAttribute(PChar, "questTemp.WPU.Escort.LevelUp_1WM") && pchar.questTemp.WPU.Escort == "wait" && NPChar.id == "WMCaptain")
				{
					dialog.text = "Czy przyniosłeś materiał, o który prosiłem?";
					if (sti(pchar.questTemp.WPU.Escort.Planks) - GetSquadronGoods(pchar, GOOD_PLANKS) <= 0 && sti(pchar.questTemp.WPU.Escort.Sailcloth) - GetSquadronGoods(pchar, GOOD_SAILCLOTH) <= 0 && sti(pchar.questTemp.WPU.Escort.Linen) - GetSquadronGoods(pchar, GOOD_COTTON) <= 0)
					{
						link.l1 = "Tak. Wszystko, czego potrzebujesz do naprawy swojego statku, jest w mojej ładowni.";
						link.l1.go = "WM_Captain_5";
					}
					else
					{
						link.l1 = "Nie, jeszcze nad tym pracuję.";
						link.l1.go = "exit";
					}
					break;
				}
				if (CheckAttribute(PChar, "questTemp.WPU.Escort.LevelUp_1VSP") && pchar.questTemp.WPU.Escort == "toCap" && NPChar.id == "WMCaptain")
				{
					dialog.text = "Ahoy, "+GetAddress_Form(NPChar)+". Nazywam się "+GetFullName(NPChar)+", jestem kapitanem tego statku. Pozwól mi wyrazić najszczerszą wdzięczność za twoją pomoc w walce z tą przeklętą piracką szumowiną - gdybyś nie interweniował, mogło się dla nas skończyć dość ponuro. Naprawdę nas uratowałeś, cholera!";
					link.l1 = "To nic,  "+GetAddress_FormToNPC(NPChar)+". Pozwól, że się przedstawię - "+GetFullName(PChar)+", przyszedłem do ciebie na prośbę mistrza portu "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen")+". Poinformował mnie o nieszczęściach twojej karawany i wysłał mnie, aby znaleźć twój statek.";
					link.l1.go = "VSP_Captain";
					break;
				}
				//<-- эскорт 2 уровень
				
				if(CheckAttribute(NPChar, "surrendered"))
				{
					Pchar.GenQuest.MoneyForCaptureShip = makeint(Group_GetLiveCharactersNum( GetGroupIDFromCharacter(NPChar)))*(8 - sti(RealShips[sti(NPChar.Ship.Type)].Class))*(1+rand(10))*500);
					if(HasShipTrait(pchar, "trait14")) Pchar.GenQuest.MoneyForCaptureShip = makeint(sti(Pchar.GenQuest.MoneyForCaptureShip) * 1.35);
					dialog.text = "Zaczekaj, możesz mnie w ten sposób zabić. Czego ode mnie chcesz?";
					//выкуп
					link.l1 = "Rozwiążmy tę sprawę pokojowo. Wydaje mi się, że okup będzie najlepszym rozwiązaniem. Suma "+Pchar.GenQuest.MoneyForCaptureShip+" pesos będą mi pasować, "+GetAddress_FormToNPC(NPChar)+". A potem możesz się zgubić!";
					link.l1.go = "surrender1";
					// обираем до нитки
					link.l2 = "Chciałbym zobaczyć, co masz w ładowni. A potem ty i twoja załoga możecie iść, gdzie chcecie.";
					link.l2.go = "surrender2";
					break;
				}
				
				//Голландский Гамбит, против всех
				if (CheckAttribute(PChar, "questTemp.HWIC.Self") && pchar.questTemp.HWIC.Self == "MeetingStivesant" && NPChar.id == "Stivesant")
				{
					dialog.text = "Witaj, panie. Miło cię widzieć. Kapitan Longway pewnie wstąpi na pokład później, prawda?";
					link.l1 = "Dzień dobry, panie Stuyvesant. Pozwól mi się przedstawić - "+GetFullName(pchar)+". Longway nie przyjdzie, nie jest na 'Meifeng'.";
					link.l1.go = "Stivesant_1";
					pchar.quest.QuestShipsTerms_Over.over = "yes"; //снять таймер
					break;
				}
				if (CheckAttribute(PChar, "questTemp.HWIC.Self") && pchar.questTemp.HWIC.Self == "FleutOnTrinidad" && NPChar.id == "Keller")
				{
					DelLandQuestMark(npchar);
					dialog.text = "Ahoj, kapitanie. Co przyprowadziło cię do mojego fletu?";
					link.l1 = "Dzień dobry, panie Keller. Pozwól, że się przedstawię - "+GetFullName(pchar)+". Przyszedłem po twoją pomoc w pewnej niezwykłej sprawie.";
					link.l1.go = "Keller_1";
					break;
					//Голландский гамбит
				}
				// belamour рыбацкое судно -->
				if(npchar.id == "FishingBoatCap")
				{
					if(!CheckAttribute(pchar, "GenQuest.FishingBoatSecondTime"))
					{
						Dialog.text = TimeGreeting()+", "+GetAddress_Form(NPChar)+"! Jestem kapitanem "+GetFullName(NPChar)+". Co cię sprowadza na mój statek?";
						link.l1 = "Dzień dobry panu. Co pan robi w tej zatoce?";
						link.l1.go = "FishingBoat";
						break;
					}
					else
					{
						Diag.CurrentNode = "first time";
						dialog.text = "Czy jest jeszcze coś, o czym chciałbyś porozmawiać?";
						link.l1 = "Chciałem"+GetSexPhrase("","")+"aby dowiedzieć się najnowszych wiadomości z archipelagu.";
						link.l1.go = "rumours_capitan";
						if(CheckAttribute(pchar,"GenQuest.FishingBoatDialogEnb"))
						{
							link.l2 = "Pokaż mi jeszcze raz, proszę, jakie błyskotki masz na sprzedaż.";
							link.l2.go = "Торговля";
							if(pchar.GenQuest.FishingBoatDialogEnb != "no special goods")
							{
								link.l3 = "Hmm, może poszukaj więcej w ładowni - może coś znajdzie się na sprzedaż?";
								link.l3.go = "Особые товары";
							}
						}
						link.l4 = "Nic specjalnego, tylko przyszedłem cię przywitać!";
						link.l4.go = "exit";	
						break;
					}
				}
				// <-- рыбацкое судно
				
				//belamour legendary edition диалоги, если герой имеет звания и заслуги перед отечеством -->
				// генерал губернатор
				if(CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE)
				{
					Dialog.text = "Gubernatorze Generalny, Wasza Łaska, witam! Co mogę dla Was zrobić?";
					link.l1 = "Mam dla ciebie interes!";
					link.l1.go = "quests";
					link.l2 = "Nic specjalnego, po prostu przyszedłem cię przywitać!";
					link.l2.go = "exit";
					break;
				}
				// вице адмирал
				if(isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && sti(Items[sti(pchar.EquipedPatentId)].Nation) == npchar.nation)
				{
					Dialog.text = "Witaj na pokładzie mojego statku, Wiceadmirał! Co mogę dla Ciebie zrobić?";
					link.l1 = "Mam dla ciebie interes!";
					link.l1.go = "quests";
					link.l2 = "Nic specjalnego, po prostu przyszedłem cię przywitać!";
					link.l2.go = "exit";
					break;
				}
				// Офицер с патентом
				if(IsOfficerFullEquip() && sti(Items[sti(pchar.EquipedPatentId)].Nation) == npchar.nation)
				{
					Dialog.text = "Cieszę się, że widzę kolegę po fachu, Kapitanie! Jak mogę pomóc?";
					link.l1 = "Mam dla ciebie interes!";
					link.l1.go = "quests";
					link.l2 = "Nic specjalnego, po prostu przyszedłem cię przywitać!";
					link.l2.go = "exit";
					break;
				}			
				// <-- legendary edition
                if (CheckAttribute(NPChar, "EncType")  && NPChar.EncType == "war")
                {
    			    Dialog.text = TimeGreeting()+", "+GetAddress_Form(NPChar)+"! Jestem "+GetFullName(NPChar)+" - kapitan statku należącego do "+NationKingsName(NPChar)+". flota. Co cię przywiodło na pokład mojego statku?";
    			}
    			else
                {
    			    Dialog.text = TimeGreeting()+", "+GetAddress_Form(NPChar)+"! Jestem kapitanem "+GetFullName(NPChar)+". Co cię przyprowadziło na pokład mojego statku?";
    			}
    			link.l1 = "Mam na imię "+GetFullName(Pchar)+". Mam do ciebie pewną sprawę!";
    			link.l1.go = "quests";
                link.l2 = "Oh, nic, tylko "+GetSexPhrase("przyszedł","przyszedł")+", aby cię powitać!";
    			link.l2.go = "exit";
            }
            else
            {
                Dialog.text = "Czy nie zauważyłeś, , "+GetAddress_Form(NPChar)+", że jesteśmy w bitwie? To nie czas na rozmowę!";
    			link.l1 = "Zgadzam się bez zastrzeżeń! Wrócę na mój statek.";
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
					Dialog.text = TimeGreeting()+", "+GetAddress_Form(NPChar)+"! Jestem kapitanem "+GetFullName(NPChar)+". Co przynosi cię na mój statek?";
					link.l1 = "I dobry dzień dla ciebie. Co robisz w tej zatoce?";
					link.l1.go = "FishingBoat";
					break;
				}
				else
				{
					dialog.text = "Czy jest coś jeszcze, o czym chciałbyś porozmawiać?";
					link.l1 = "Chciałem"+GetSexPhrase("","")+", aby dowiedzieć się najnowszych wiadomości z archipelagu.";
					link.l1.go = "rumours_capitan";
					if(CheckAttribute(pchar,"GenQuest.FishingBoatDialogEnb"))
					{
						link.l2 = "Pokaż mi jeszcze raz, proszę, jakie bibeloty masz na sprzedaż. ";
						link.l2.go = "Торговля";
						if(pchar.GenQuest.FishingBoatDialogEnb != "no special goods")
						{
							link.l3 = "Hmm, może poszukaj więcej w ładowni - może coś znajdzie się na sprzedaż?";
							link.l3.go = "Особые товары";
						}
					}
					link.l4 = "Nic specjalnego, przyszedłem tylko cię powitać!";
					link.l4.go = "exit";	
					break;
				}
			}
			// <-- рыбацкое судно
            if (!CheckAttribute(NPChar, "MainCaptanId")  || NPChar.MainCaptanId == pchar.GenQuest.CaptainId)
            {
                Dialog.text = "Słucham cię bardzo uważnie,  "+GetAddress_Form(NPChar)+".";
                link.l1 = "Chcę znać najnowsze wieści z archipelagu.";
                //homo 25/06/06
                link.l1.go = "rumours_capitan";
                //belamour legendary edition 
				bOk1 = isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && GetNationRelation(npchar.nation, sti(Items[sti(pchar.EquipedPatentId)].Nation)) != RELATION_ENEMY;
				bOk2 = CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && GetNationRelation(npchar.nation, FRANCE) != RELATION_ENEMY;
				bOk = bOk1 || bOk2;
                if (CheckAttribute(NPChar, "EncGroupName") && !bOk) // только для фантомов грабеж
                {
                    link.l2 = RandPhraseSimple("Czy masz pojęcie, kim jestem? Myślę, że jest całkiem jasne, że moje działa mogą zrobić sito z twojego starego kubła. Rozwiążmy to w pokojowy sposób. Okup to dla mnie dobra decyzja.","Tylko my... i morze... Co sądzisz o uspokojeniu moich ludzi... dla własnego bezpieczeństwa?");
                    link.l2.go = "Talk_board";
                }
                if (CheckAttribute(NPChar, "Ship.Mode") && NPChar.Ship.Mode == "Trade")
                {
	           		link.l3 = "Skąd przybywasz?";
	    			link.l3.go = "price_1";
	    			link.l4 = "Chcesz handlować?";
	    			link.l4.go = "Trade_1";
    			}
				//--> квест мэра, поиски пирата
				if (CheckAttribute(pchar, "GenQuest.DestroyPirate"))
				{
	    			link.l6 = "Szukam pirackiego statku działającego w tych wodach. Widziałeś coś podejrzanego?";
	    			link.l6.go = "MQ_step_1";
				}
				//<-- квест мэра, поиски пирата
    			link.l5 = "Chcesz się zrelaksować?";
			    link.l5.go = "Play_Game";
                link.l9 = "Chyba powinienem iść.";
    			link.l9.go = "exit";
			}
			else
			{
                Dialog.text = "Nie jestem upoważniony do rozmowy z tobą. Porozmawiaj z dowódcą naszego szwadronu. Jego imię to "+GetFullName(characterFromID(NPChar.MainCaptanId))+", możesz go znaleźć na "+XI_ConvertString(RealShips[sti(characters[GetCharacterIndex(NPChar.MainCaptanId)].Ship.Type)].BaseName)+" '"+characters[GetCharacterIndex(NPChar.MainCaptanId)].Ship.Name+"'.'";
                link.l1 = "Dzięki. Zrobię jak mówisz.";
                link.l1.go = "exit";
                Diag.TempNode = "Go_away_Good";
			}
        break;
        case "Trade_1":
			dialog.text = "Dlaczego nie?";
			link.l1 = "Chodźmy zobaczyć towary.";
			link.l1.go = "Trade_2";
			link.l2 = "Zmieniłem zdanie.";
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
			dialog.text = "Co sugerujesz?";
			link.l1 = "Chcesz zagrać w karty o poważne pieniądze?";
			link.l1.go = "Card_Game";
   			link.l2 = "Co powiesz na rzucenie kostką w poker-joker?";
			link.l2.go = "Dice_Game";
			link.l10 = "Przykro mi, ale mam trochę spraw do załatwienia.";
			link.l10.go = "exit";
		break;
        // карты -->
        case "Card_Game":
            if (!CheckNPCQuestDate(npchar, "Card_date_Yet") || isBadReputation(pchar, 30) || GetCharacterSkillToOld(pchar, SKILL_LEADERSHIP) < rand(3))
            {
                SetNPCQuestDate(npchar, "Card_date_Yet");
                dialog.text = "Nie będę grał w hazard z łotrami!";
    			link.l1 = "Jak sobie życzysz.";
    			link.l1.go = "exit";
			}
			else
			{
                dialog.text = "Dlaczego nie? Na pewno nie przeszkadzałby mi przerwa...";
    			link.l1 = "Świetnie.";
    			link.l1.go = "Cards_begin";
    			link.l2 = "Jakie są zasady?";
    			link.l2.go = "Cards_Rule";
			}
		break;

		case "Cards_Rule":
   			dialog.text = CARDS_RULE;
			link.l1 = "No cóż, zaczynajmy więc!";
			link.l1.go = "Cards_begin";
			link.l3 = "Nie, to nie dla mnie...";
			link.l3.go = "exit";
		break;

		case "Cards_begin":
			Dialog.text = "Zgódźmy się najpierw na zakład.";
			link.l1 = "Zagrajmy za 100 peso.";
			link.l1.go = "Cards_Node_100";
			link.l2 = "Zagrajmy za 500 pesos.";
			link.l2.go = "Cards_Node_500";
			link.l3 = "Chyba powinienem iść.";
			link.l3.go = "exit";
		break;

		case "Cards_Node_100":
		    if (sti(pchar.Money) < 300)
		    {
                dialog.text = "Czy żartujesz, czy co? Nie masz pieniędzy!";
                link.l1 = "Dzieje się.";
			    link.l1.go = "exit";
			    break;
		    }
		    if (sti(npchar.Money) < 300)
		    {
                dialog.text = "No, wystarczy, inaczej nie będę miał wystarczająco pieniędzy na utrzymanie statku...";
                link.l1 = "Szkoda.";
			    link.l1.go = "exit";
			    break;
		    }
   			dialog.text = "Dobrze, zagrajmy za 100 monet.";
			link.l1 = "Zaczynajmy!";
			link.l1.go = "Cards_begin_go";
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
            pchar.GenQuest.Cards.iRate     = 100;
            pchar.GenQuest.Cards.SitType   = false;
		break;

		case "Cards_Node_500":
		    if (sti(pchar.Money) < 1500)
		    {
                dialog.text = "Żartujesz czy co? Nie masz 1500 pesos!";
                link.l1 = "Ja ich znajdę!";
			    link.l1.go = "exit";
			    break;
		    }
		    if (sti(npchar.Money) < 1500)
		    {
                dialog.text = "Nie, te zakłady na pewno mnie kiedyś zgubią.";
                link.l1 = "Jak sobie życzysz.";
			    link.l1.go = "exit";
			    break;
		    }
   			dialog.text = "Dobrze, zagramy za 500 monet.";
			link.l1 = "Zaczynajmy!";
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
                dialog.text = "Nie będę grał w hazard z oszustami!";
    			link.l1 = "Jak sobie życzysz.";
    			link.l1.go = "exit";
			}
			else
			{
				if (CheckNPCQuestDate(npchar, "Dice_date_begin"))
				{
					dialog.text = "Dlaczego nie! Relaks zawsze jest dobry dla zdrowia... ale nie zawsze dla sakiewki...";
	    			link.l1 = "Świetnie.";
	    			link.l1.go = "Dice_begin";
	    			link.l2 = "Jakie są zasady naszej gry?";
	    			link.l2.go = "Dice_Rule";
    			}
    			else
    			{
					dialog.text = "Nie, na dzisiaj koniec. Mam co robić.";
	    			link.l1 = "Jak sobie życzysz.";
	    			link.l1.go = "exit";
				}
			}
		break;

		case "Dice_Rule":
   			dialog.text = DICE_RULE;
			link.l1 = "No to zaczynajmy!";
			link.l1.go = "Dice_begin";
			link.l3 = "Nie, to nie dla mnie...";
			link.l3.go = "exit";
		break;

		case "Dice_begin":
			Dialog.text = "Zgódźmy się najpierw na zakład.";
			link.l1 = "Zagrajmy za 50 pesos.";
			link.l1.go = "Dice_Node_100";
			link.l2 = "Zagrajmy za 200 pesos.";
			link.l2.go = "Dice_Node_500";
			link.l3 = "Chyba powinienem iść.";
			link.l3.go = "exit";
		break;

		case "Dice_Node_100":
			//belamour legendary edition 
			bOk1 = isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && GetNationRelation(npchar.nation, sti(Items[sti(pchar.EquipedPatentId)].Nation)) != RELATION_ENEMY;
			bOk2 = CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && GetNationRelation(npchar.nation, FRANCE) != RELATION_ENEMY;
			bOk = bOk1 || bOk2;
            if (!CheckDiceGameSmallRate() && !bOk)
		    {
                dialog.text = "Jesteś dobrze znany jako"+GetSexPhrase("oszust","oszust")+".. Nigdy nie będę z tobą grać w kości.";
                link.l1 = "To wszystko kłamstwa! Cóż, niech będzie.";
			    link.l1.go = "exit";
			    break;
		    }

			if (sti(pchar.Money) < 300)
		    {
                dialog.text = "Czy żartujesz, czy co? Nie masz pieniędzy!";
                link.l1 = "To się zdarza.";
			    link.l1.go = "exit";
			    break;
		    }
		    if (sti(npchar.Money) < 300)
		    {
                dialog.text = "Dość! Skończyłem z hazardem - zanim nazwą mnie defraudantem i zmuszą do opuszczenia statku.";
                link.l1 = "Szkoda.";
			    link.l1.go = "exit";
			    break;
		    }
   			dialog.text = "Dobrze, zagramy za 50 monet.";
			link.l1 = "Zaczynajmy!";
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
                dialog.text = "Jesteś dobrze znany jako"+GetSexPhrase("oszust","oszust")+". Nigdy nie będę z tobą grał w kości.";
                link.l1 = "To wszystko kłamstwa! No cóż, niech tak będzie.";
			    link.l1.go = "exit";
			    break;
		    }
			if (!CheckDiceGameBigRate())
		    {
                dialog.text = "Słyszałem, że jesteś bardzo dobrym graczem. Nie będę grał z tobą na wysokie stawki.";
                link.l1 = "Czy może obniżymy zakład?";
			    link.l1.go = "Dice_Node_100";
				link.l2 = "Przykro mi, ale muszę iść.";
			    link.l2.go = "exit";
			    break;
		    }

			if (sti(pchar.Money) < 1500)
		    {
                dialog.text = "Żartujesz czy co? Nie masz 1500 peso!";
                link.l1 = "Znajdę ich!";
			    link.l1.go = "exit";
			    break;
		    }
		    if (sti(npchar.Money) < 1500)
		    {
                dialog.text = "Nie, te zakłady na pewno mnie w końcu zgubią.";
                link.l1 = "Jak sobie życzysz.";
			    link.l1.go = "exit";
			    break;
		    }
   			dialog.text = "Dobrze, zagrajmy za 200 monet.";
			link.l1 = "Zaczynajmy!";
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
	                Dialog.Text = "Dlaczego chcesz wiedzieć? To jest moja prywatność.";
					Link.l1 = "Jak sobie życzysz.";
					Link.l1.go = "exit";
	            }
	            else
	            {
                    sld = &Characters[iMoney];
                    pchar.PriceList.ShipStoreIdx = iMoney;
                    
					Dialog.Text = "Przychodzę z miasta"+GetCityName(sld.City)+".";
					Link.l1 = "Jakie są ceny towarów w lokalnym sklepie?";
					Link.l1.go = "price_2";
					Link.l9 = "Powinienem iść.";
					Link.l9.go = "exit";
				}
			}
			else
			{
                Dialog.Text = "Już ci wszystko powiedziałem. Nie zawracaj mi głowy bez powodu.";
				Link.l1 = "Tak, masz rację. Do widzenia.";
				Link.l1.go = "exit";
            }
		break;
		
		case "price_2":
            sld = &Characters[sti(pchar.PriceList.ShipStoreIdx)];
			SetPriceListByStoreMan(&Colonies[FindColony(sld.City)]);
			Dialog.Text = "Proszę... (otrzymałeś listę cen)..";
			Link.l1 = "Dziękuję bardzo!";
			Link.l1.go = "exit";
			PlaySound("interface\important_item.wav");
		break;
		
        case "Talk_board":
            if ((Group_GetCharactersNum(NPChar.EncGroupName) - Group_GetDeadCharactersNum(NPChar.EncGroupName)) > GetCompanionQuantity(PChar) && rand(11) > GetCharacterSkillToOld(PChar, SKILL_FORTUNE))
            {
                Dialog.text = "Ha-ha-ha! Świetny żart, mam więcej statków. Wróć do swojego statku i utop się z nim.";
                link.l1 = "Więcej nie znaczy silniejszy, kumplu.";
                link.l1.go = "Boarding";
            }
            else
            {
                if(rand(21) > (GetSummonSkillFromNameToOld(PChar, SKILL_GRAPPLING) + GetSummonSkillFromNameToOld(PChar, SKILL_LEADERSHIP)) )
                {
                    Dialog.text = "Kapitanie, nie powinieneś robić swojego brudnego interesu na pokładzie mojego statku. Ale okażę litość i pozwolę ci wrócić na swój statek, aby zatonąć z nim.";
                    link.l1 = "Zobaczymy, kto stanie się dzisiaj jedzeniem dla rekina!";
                    link.l1.go = "Boarding";
                }
                else
                {
                    Pchar.GenQuest.MoneyForCaptureShip = makeint(100 + (Group_GetCharactersNum(NPChar.EncGroupName) - Group_GetDeadCharactersNum(NPChar.EncGroupName))*(8 - sti(RealShips[sti(NPChar.Ship.Type)].Class))*(1+rand(10))*500);
					if(HasShipTrait(pchar, "trait14")) Pchar.GenQuest.MoneyForCaptureShip = makeint(sti(Pchar.GenQuest.MoneyForCaptureShip) * 1.35);
                    Dialog.text = RandSwear()+"Tak, słyszałem dużo o twoich skandalach. Niech będzie, ale pamiętaj "+XI_ConvertString(NationShortName(sti(NPChar.nation))+"łowca")+" nie pozwolę na to bezkarnie!";
                    link.l1 = "Świetnie. Suma "+Pchar.GenQuest.MoneyForCaptureShip+" pesos będzie dla mnie odpowiednie, "+GetAddress_FormToNPC(NPChar)+".";
                    link.l1.go = "Capture";
                    link.l2 = "Och, nieważne. Po prostu żartowałem"+GetSexPhrase("","")+"!";
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
            Dialog.Text = "Proszę, a teraz znikaj!";
			Link.l1 = "Fajnie! A ty też trzymaj się zdrowo, przyjacielu!";
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
			Dialog.Text = "Co jeszcze ode mnie chcesz?";
			Link.l1 = "Nic.";
			Link.l1.go = "exit";
			Diag.TempNode = "surrender_goaway";
		break;
		
		case "surrender2":			
			dialog.text = "Wygląda na to, że nie mam innego wyjścia, jak tylko poddać się Tobie.";
			link.l1 = "Idź już, teraz!";
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
			Link.l1 = RandPhraseSimple(RandSwear()+"To jest bardzo interesujące. Kolejne pytanie?","Tylko kolejna sprawa.");
			Link.l1.go = "quests";
			Link.l2 = RandPhraseSimple("Dzięki, powinienem już iść.","Wszystkiego najlepszego.");
			Link.l2.go = "exit";
			Diag.TempNode = "quests";
		break;
		
		case "Go_away":
			Dialog.Text = "Zejdź z mojego statku!";
			Link.l1 = "Już odchodzę.";
			Link.l1.go = "exit";
			Diag.TempNode = "Go_away";
		break;
		
		case "Go_away_Good":
			Dialog.Text = "Nasza rozmowa się skończyła. Nie powiem ci niczego nowego "+GetAddress_Form(NPChar)+".";
			Link.l1 = "W porządku. Do zobaczenia na morzu!";
			Link.l1.go = "exit";
			Diag.TempNode = "Go_away_Good";
		break;

        case "Capture":
            Diag.TempNode = "Go_away";
            Dialog.Text = "Proszę cię - a teraz wynoś się!";
			Link.l1 = "Świetnie!";
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
            Dialog.Text = "Poczekaj, możesz mnie w ten sposób zabić. Czego ode mnie chcesz?";
			Link.l1 = "Aby cię zabić!";
			Link.l1.go = "QuestAboardCabinDialog_1";
			Link.l2 = "Poddać się!";
			Link.l2.go = "QuestAboardCabinDialog_2";
			Link.l3 = "Daj nam mapę, Billy (c)";  // предмет, далее не ясно или  QuestAboardCabinDialog_1 или QuestAboardCabinDialog_2
			Link.l3.go = "QuestAboardCabinDialog_3";  // можно закодить покидание корабля, но экипаж уже вырезан и тп...
        break;
        
        case "QuestAboardCabinDialog_1":
			Dialog.Text = "No cóż, zobaczymy, łajdaku!";
			Link.l1 = "I co muszę zobaczyć?";
			Link.l1.go = "exit";
			// тут можно восстановить НР противника (NPChar) или добавить парочку гардов против ГГ
			LAi_SetCurHPMax(NPChar);
			AddDialogExitQuestFunction("QuestAboardCabinDialogExitWithBattle"); // тут ругань обратно
		break;
		
		case "QuestAboardCabinDialog_2":
			Dialog.Text = "Dobrze, wygrałeś!";
			Link.l1 = "Mądre decyzja!";
			Link.l1.go = "exit";
			AddDialogExitQuestFunction("QuestAboardCabinDialogSurrender");
		break;
		
		case "QuestAboardCabinDialog_3":
			Dialog.Text = "Mam nadzieję, że się na tym udusisz!";
			Link.l1 = "Bardzo dobrze, wskakuj w kajdany i zamknij swoją gębę, więźniu.";
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
			Dialog.Text = ""+GetSexPhrase("Przybyłem tutaj","Przyszedłem tutaj")+", zrobił bałagan"+GetSexPhrase("","")+",i zabrał wszystko"+GetSexPhrase("","")+", teraz chcesz ze mnie zrobić niewolnika? Nigdy!";
			Link.l1 = "Wtedy przygotuj się na śmierć.";
			Link.l1.go = "QuestAboardCabinDialog_1";
		break;
		//eddy. квест мэра, поиски пирата
		case "MQ_step_1":
			Dialog.Text = "Nie, nie widziałem żadnego podejrzanego statku, który wyglądałby jak piraci.";
			Link.l1 = "Widzę.";
			Link.l1.go = "exit";
		break;
		
		//homo Наводка на купца
		case "MerchantTrap_Abordage":

			Dialog.Text = "W imię "+NationKingsName(NPChar)+" poddaj się, "+GetSexPhrase("brudny pirat","plugawa wench!")+"! Wtedy twoje życie zostanie oszczędzone do czasu sprawiedliwego trybunału, gdzie zostaniesz osądzony za wszystko "+NationNameSK(sti(NPChar.nation))+"statki, które splądrowałeś"+GetSexPhrase("","")+".";
			Link.l1 = "Spieprzaj! Powinieneś się poddać!";
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
					dialog.text = "Wasza Ekscelencjo, Gubernatorze Generalny! Słucham Pana uważnie, ale proszę o zwięzłość: walczymy z "+fort+", i muszę kierować przebiegiem bitwy.";
				}
				else
				{
					if(isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && sti(Items[sti(pchar.EquipedPatentId)].Nation) == npchar.nation)
					{
						dialog.text = "Wiceadmirał! Słucham cię uważnie, ale mam mało czasu: walczymy z "+fort+", a muszę kierować przebiegiem bitwy.";
					}
					else
					{
						dialog.text = "Słucham cię, ale szybko wyjaśnij cel twojej wizyty, toczymy walkę z "+fort+", i muszę kierować przebiegiem bitwy.";
					}
				}
                link.l1 = "Dlatego tu jestem,  "+GetAddress_FormToNPC(NPChar)+".";
                link.l1.go = "attack_fort";

                link.l2 = "W takim razie nie będę już więcej zajmować ci czasu. Do widzenia, "+GetAddress_FormToNPC(NPChar)+".";
                link.l2.go = "exit";
    			
            }
            else
            {
                Dialog.text = "Nie jestem upoważniony do rozmowy z tobą. Porozmawiaj z dowódcą naszego szwadronu. Nazywa się  "+GetFullName(rchar)+", możesz go znaleźć na "+XI_ConvertString(RealShips[sti(rchar.Ship.Type)].BaseName)+"''"+rchar.Ship.Name+"''.";
                link.l1 = "Dzięki. Zrobię jak mówisz.";
                link.l1.go = "exit";
            
            }
            Diag.TempNode = "Siegehelp";
            
		break;
		
		case "attack_fort":
                dialog.text = "A co masz na myśli?";
                link.l1 = "Mogę ci pomóc w zdobyciu fortu kolonii "+GetConvertStr(aData.Colony+" Miasto","LocLables.txt")+" i zdobyć miasto, a także łup, który w przypadku naszego sukcesu, podzielimy między nas.";
                link.l1.go = "Siegehelp_1";
                link.l2 = "Właściwie, moje interesy są ledwie warte twojego czasu. Do widzenia, "+GetAddress_FormToNPC(NPChar)+".";
                link.l2.go = "exit";
                Diag.TempNode = "Siegehelp_0";
		break;
		
		case "Siegehelp_0":
            Dialog.text = "Znowu ty? Myślałem, że już wszystko omówiliśmy.";
            link.l1 = "Masz rację. Chyba zapomniałem"+GetSexPhrase("","")+".";
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
                dialog.text = "I jaki udział w łupie spodziewasz się otrzymać?";
                link.l1 = "Połowa.";
                link.l1.go = "Big_part";
                link.l2 = "Jedna trzecia.";
                link.l2.go = "Middle_part";
                link.l3 = "Kwadrans.";
                link.l3.go = "Small_part";
            }
            else
            {
                dialog.text = "Nie potrzebuję twoich usług, kapitanie! Sam przejmę tę kolonię i nie potrzebuję pomocy w tym.";
                link.l1 = "Dlaczego jesteś taki pewny, "+GetAddress_FormToNPC(NPChar)+", każdy może mieć złą passę.";
                link.l1.go = "attack_fort_03";
                link.l2 = "W takim razie nie będę już więcej marnować twojego czasu, "+GetAddress_FormToNPC(NPChar)+". Żegnaj!";
                link.l2.go = "exit";
            }
			Diag.TempNode = "Siegehelp_0";

		break;
		
		case "attack_fort_03":
            if((sti(aData.iSquadronPower)*SquadronDamage - (ifortPower)*fortDamage) < 4000)
            {
                dialog.text = "Z drugiej strony, moje statki są dość uszkodzone w tej bitwie, a posiłki na pewno by nie zaszkodziły. Jeśli się zgadzasz "+GetPart(4)+", wtedy, chyba, moglibyśmy dojść do porozumienia.";
                link.l1 = "To mi pasuje, "+GetAddress_FormToNPC(NPChar)+". Spróbuję zaatakować fort, a ty wesprzesz nas ogniem armat twojego statku.";
                link.l1.go = "attack_fort_04";
                aData.PartAttaksFort = 4;
                link.l2 = "Nie jestem taki tani, "+GetAddress_FormToNPC(NPChar)+". Przepraszam za rozproszenie"+GetSexPhrase("","")+" odciągnąłem cię od pilnych spraw. Do widzenia!";
                link.l2.go = "exit";
            }else{
                dialog.text = "W moim składzie jest wystarczająco dużo statków, aby zmienić ten fort w proch - to tylko kwestia czasu. A teraz, czy mógłbyś opuścić mój statek? Czeka na mnie zwycięstwo!";
                link.l1 = "No cóż, w takim razie, "+GetAddress_FormToNPC(NPChar)+", pozwól mi odejść. Żegnaj!";
                link.l1.go = "exit";
            }
		    Diag.TempNode = "Siegehelp_0";
		break;
		case "Big_part":
            if( (sti(aData.iSquadronPower)*SquadronDamage - (ifortPower)*fortDamage) <= -1500)
            {
                dialog.text = "Fortowe działa mocno uszkodziły moje statki, a my z pewnością możemy być przegraną stroną w nadchodzącej bitwie. Akceptuję twoją pomoc i zgadzam się na twoje warunki.";
                link.l1 = "Świetnie, "+GetAddress_FormToNPC(NPChar)+", w takim razie spróbujemy zaatakować fort, a ty wesprzesz nas ogniem z dział twojego statku.";
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
					dialog.text = "Wasza Wysokość, muszę jeszcze zgłosić postęp operacji ... Przynajmniej "+GetPart(4)+".";
				}
				else
				{
                dialog.text = "Czy to nie za dużo, kapitanie? Masz "+GetNumShips(GetCompanionQuantity(PChar))+", a mój dywizjon ma "+GetNumShips(Group_GetCharactersNum(sGroup))+". Mogę ci zaoferować "+GetPart(4)+". I uważaj to za sprawiedliwe.";
				}
                aData.PartAttaksFort = 4;
                link.l1 = "Zgadzam się"+GetSexPhrase("","")+", "+GetAddress_FormToNPC(NPChar)+", w takim razie zaatakuję fort, a ty wesprzesz nas ogniem z dział twojego statku.";
                link.l1.go = "attack_fort_04";
                link.l2 = "Niestety, nie sądzę, "+GetAddress_FormToNPC(NPChar)+". Nie ma więcej do omówienia. Żegnaj.";
                link.l2.go = "exit";
            }
            Diag.TempNode = "Siegehelp_0";
        break;
        
        case "attack_fort_04":
            dialog.text = "Jak tylko fort zostanie zdobyty, zaczniemy wysadzać desant na brzegu, a potem będziemy kontynuować walkę w samym mieście, gdzie mam nadzieję spotkać się z tobą.";
            link.l1 = "Tak niech będzie. Do zobaczenia wkrótce, "+GetAddress_FormToNPC(NPChar)+"!";
            link.l1.go = "exit";
            Diag.TempNode = "Siegehelp_0";
            PChar.quest.Union_with_Escadra = "Yes";
        break;

        case "Middle_part":
            if((sti(aData.iSquadronPower)*SquadronDamage - (ifortPower)*fortDamage) <= -600)
            {
                dialog.text = "Myślę, że zgodzę się na twoje warunki. Wspólna operacja zwiększy moje szanse na wygranie tej walki. Jeśli wszystko pójdzie zgodnie z planem, otrzymasz swoją część łupów.";
                link.l1 = "To świetnie, że doszliśmy do porozumienia, "+GetAddress_FormToNPC(NPChar)+". Zarządzę moim ludziom natychmiastowy szturm na fort.";
                link.l1.go = "attack_fort_04";
                aData.PartAttaksFort = 3;
            }else{
				// belamour legendary edition
				bOk1 = isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation);
				bOk2 = CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE;
				bOk = bOk1 || bOk2;
				if(bOk)
				{
					dialog.text = "Wasza Ekscelencjo, muszę jeszcze zgłosić postęp operacji ... Przynajmniej "+GetPart(4)+".";
				}
				else
				{
                dialog.text = "Czy to nie za dużo, kapitanie? Masz "+GetNumShips(GetCompanionQuantity(PChar))+", a mój szwadron ma "+GetNumShips(Group_GetCharactersNum(sGroup))+". Mogę ci zaoferować "+GetPart(4)+". I uważaj to za sprawiedliwe.";
				}
                link.l1 = "Ja "+GetSexPhrase("zgadzam się","zgadzam się")+", "+GetAddress_FormToNPC(NPChar)+", w takim razie zaatakuję fort, a ty wesprzesz nas ogniem dział swojego statku.";
                link.l1.go = "attack_fort_04";
                aData.PartAttaksFort = 4;
                link.l2 = "Niestety, nie sądzę, "+GetAddress_FormToNPC(NPChar)+". Nie ma więcej do omówienia. Do widzenia.";
                link.l2.go = "exit";
            }
            Diag.TempNode = "Siegehelp_0";
        break;

        case "Small_part":
            dialog.text = "Moje statki są zmęczone, a każda świeża siła jest mile widziana w tej sytuacji. Akceptuję twoją pomoc i zgadzam się na twoje warunki.";
            link.l1 = "Cieszę się"+GetSexPhrase("","")+", "+GetAddress_FormToNPC(NPChar)+".. Natychmiast każę moim ludziom rozpocząć szturm na fort.";
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
            dialog.text = "Witaj, kapitanie! To na pewno była ciężka bitwa, ale udało nam się złamać zaciekły opór obrońców miasta. Splądrowaliśmy "+sti(aData.loot)+" pesos. Zgodnie z naszą umową, twoja część to "+ilt+". Please accept this money; you certainly deserve every last coin of it. And now please excuse me, but I must return to my business.";
            link.l1 = "W takim razie, zostawię cię, "+GetAddress_FormToNPC(NPChar)+". Żegnaj!";
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
            dialog.text = "Ahoy, kapitanie! Masz do mnie jakieś sprawy?";
            link.l1 = "Nie, "+GetAddress_FormToNPC(NPChar)+". Do widzenia!";
            link.l1.go = "exit";
            Diag.TempNode = "no_return_02";
		break;
		
		case "GoldSquadron":
            ref rch = Group_GetGroupCommander("Sea_Head_of_Gold_Squadron");
            if (NPChar.id == rch.id)
            {
    			dialog.text = "Słucham cię, ale proszę, bądź szybki w kwestii celu swojej wizyty, nie mam dużo czasu. Mam ważną i tajną misję, a także dostałem rozkaz zatapiania wszystkich podejrzanych statków na otwartym morzu, które mogłyby stanowić jakiekolwiek zagrożenie dla naszego konwoju.";                          
                link.l1 = "W takim razie nie będę już więcej zajmował twojego czasu. Powodzenia, "+GetAddress_FormToNPC(NPChar)+".";
                link.l1.go = "exit";

            }
            else
            {
                Dialog.text = "Nie jestem upoważniony do rozmowy z tobą. Porozmawiaj z dowódcą naszego dywizjonu. Nazywa się "+GetFullName(rch)+", możesz go znaleźć na "+XI_ConvertString(RealShips[sti(rch.Ship.Type)].BaseName)+" ''"+rch.Ship.Name+"''.";
                link.l1 = "Dzięki. Zrobię jak mówisz.";
                link.l1.go = "exit";

            }
            Diag.TempNode = "GoldSquadron";
		break;
		
		case "WM_Captain":
			dialog.text = "Miło cię poznać, a moje imię to "+GetFullName(npchar)+". Więc przyszedłeś nam pomóc? W takim razie jestem szczególnie zadowolony, ponieważ nasza obecna sytuacja jest naprawdę krytyczna - jesteśmy sami na brzegach niezamieszkanej wyspy, statek jest ledwo zdolny do pływania, załoga poniosła ciężkie straty...";
			link.l1 = "Jak słyszałem, walczyłeś z piratami, a potem była ta burza...";
			link.l1.go = "WM_Captain_1";
			pchar.quest.DesIsland_Over.over = "yes";//снять прерывание
		break;
		
		case "WM_Captain_1":
			dialog.text = "Prawda. Mój statek został mocno uszkodzony w bitwie - musieliśmy nawet stawić czoła atakowi abordażowemu, którym dowodzili ci pirackie bękarty. Później złapała nas burza... och, nawet nie chcę o tym myśleć. Zostaliśmy zaniesieni na ten nieprzyjazny brzeg. Cały dzień modliliśmy się do Najświętszej Marii Panny, aby ocaliła nas od burzy i utrzymała nasze łańcuchy kotwiczne w jednym kawałku\nI oto jesteśmy. Naprawiamy nasz statek od tygodnia, ale zobacz sam: zostało tylko pięćdziesięciu mężczyzn, a nam brakuje także desek - i skąd mamy je wziąć? Z dżungli? Oczywiście. Ciężko pracujemy każdego dnia, a mimo to mamy tylko piątą część potrzebnego materiału\nPłynięcie z takim uszkodzeniem to jak samobójstwo. Teraz widzisz, jak nam tu idzie, kapitanie...";
			link.l1 = "Tak... Twoja sytuacja jest nie do pozazdroszczenia. Pomyślmy, co moglibyśmy podjąć i jak mogę ci pomóc.";
			link.l1.go = "WM_Captain_2";
		break;
		
		case "WM_Captain_2":
			dialog.text = "Ech, żałuję, że nie mamy wystarczającej ilości desek i płótna żaglowego - w takim przypadku naprawilibyśmy nasz statek w tydzień\nKapitanie, skoro przyszedłeś tu specjalnie, może odwiedziłbyś najbliższy port i kupił materiały, których potrzebujemy? To rozwiązałoby nasz problem. Nie martw się o monety, zrekompensuję wszystkie wydatki.";
			link.l1 = "Oczywiście. Co dokładnie musisz dostarczyć i ile?";
			link.l1.go = "WM_Captain_3";
		break;
		
		case "WM_Captain_3":
			pchar.questTemp.WPU.Escort.Planks = 300 + hrand(5)*10;
			pchar.questTemp.WPU.Escort.Sailcloth = 150 + hrand(10)*10;
			pchar.questTemp.WPU.Escort.Linen = 70 + hrand(7)*10;
			dialog.text = "Już wszystko to rozgryzłem. Biorąc pod uwagę to, co już mamy, potrzebuję "+FindRussianQtyString(sti(pchar.questTemp.WPU.Escort.Planks))+" deski, "+FindRussianQtyString(sti(pchar.questTemp.WPU.Escort.Sailcloth))+" płótno żaglowe i "+FindRussianQtyString(sti(pchar.questTemp.WPU.Escort.Linen))+" bawełna. Z tymi materiałami, udałoby nam się naprawić statek w ciągu tygodnia, a potem moglibyśmy wypłynąć.";
			link.l1 = "Dobrze. Przyniosę ci wszystkie materiały, których potrzebujesz. Czekaj na mnie - wrócę nie później niż za dziesięć dni.";
			link.l1.go = "WM_Captain_4";
		break;
		
		case "WM_Captain_4":
			dialog.text = "Dzięki wielkie, kapitanie! To jest kamień z serca. Będziemy czekać i modlić się o twój pomyślny powrót!";
			link.l1 = "Nie martw się. Wkrótce będziesz miał wszystko, czego potrzebujesz do naprawy.";
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
			dialog.text = "Z niecierpliwością czekamy na twój powrót, kapitanie!";
			link.l1 = "Podnieść kotwice!";
			link.l1.go = "exit";
			Diag.TempNode = "WM_Captain_again";
		break;
		
		case "WM_Captain_5":
			dialog.text = "Świetnie! Teraz możemy zacząć naprawiać statek!";
			link.l1 = "Moji ludzie ci pomogą - tak będzie szybciej. Poza tym, muszę cię towarzyszyć do kolonii "+XI_ConvertString("Kolonia"+pchar.questTemp.WPU.Escort.StartCity)+", więc im szybciej skończymy z naprawami, tym lepiej dla mnie.";
			link.l1.go = "WM_Captain_6";
		break;
		
		case "WM_Captain_6":
			pchar.questTemp.WPU.Current.TargetIslandID.Shore = SelectQuestShoreLocationFromSea(pchar.questTemp.WPU.Current.TargetIslandID);
			dialog.text = "Naprawdę, nie mam pojęcia, jak właściwie Ci podziękować, kapitanie... Proszę, rozładuj materiały w zatoce o nazwie "+XI_ConvertString(pchar.questTemp.WPU.Current.TargetIslandID.Shore)+" - tam mamy wszystko gotowe do naprawy.";
			link.l1 = "Dobrze. Spotkamy się na brzegu.";
			link.l1.go = "exit";
			AddQuestRecord("Escort", "29");
			AddQuestUserData("Escort", "sShore", XI_ConvertString(pchar.questTemp.WPU.Current.TargetIslandID.Shore+"Gen"));
			pchar.quest.DisasterShip_WMC.win_condition.l1 = "location";
			pchar.quest.DisasterShip_WMC.win_condition.l1.location = pchar.questTemp.WPU.Current.TargetIslandID.Shore;
			pchar.quest.DisasterShip_WMC.function = "RepairShip_Prepare";
			Diag.TempNode = "WM_Captain_repeat";
		break;
		
		case "WM_Captain_repeat":
			dialog.text = "Kiedy zaczniemy naprawy, kapitanie? Będę na ciebie czekać na brzegu.";
			link.l1 = "Tak, oczywiście. Wychodzę teraz.";
			link.l1.go = "exit";
			Diag.TempNode = "WM_Captain_repeat";
		break;
		
		case "Repair_start":
			dialog.text = "Cóż, wszystko wydaje się gotowe do naprawy. Myślę, że powinniśmy skończyć za około pięć dni.";
			link.l1 = "Bardzo dobrze! I tak zamierzałem zbadać tę wyspę, więc dobrze wykorzystam ten czas.";
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
			dialog.text = "No cóż, to wszystko. Skończyliśmy naprawy, a statek jest gotowy do wypłynięcia. Kiedy odpływamy, kapitanie?";
			link.l1 = "Jeśli jesteś gotowy, nie widzę sensu w zwlekanie. Podnieśmy kotwice!";
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
			dialog.text = "Chciałbym jeszcze raz podziękować, kapitanie - bardzo mi i mojej załodze pomogłeś wyjść z tego kłopotu. Tak jak obiecałem, pokryję koszty materiałów potrzebnych do naprawy mojego statku. Oto "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.LevelUp_1Money))+", proszę, weź to. A to jest mój osobisty prezent dla ciebie.";
			link.l1 = "Cieszę się, że mogłem ci pomóc.";
			link.l1.go = "WMShip_final_1";
		break;
		
		case "WMShip_final_1":
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.WPU.Escort.LevelUp_1Money));
			TakeNItems(pchar, "obereg_"+(hrand(10)+1), 1);
			dialog.text = "I teraz, czas się pożegnać, kapitanie. Nie zapomnij odwiedzić portowego urzędu - tam na ciebie czekają. Do zobaczenia!";
			link.l1 = "Miłego dnia, "+npchar.name+"!";
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
			dialog.text = "Czy tak? A myślałem, że nas zapomnieli. Tak, mój statek najbardziej ucierpiał. Pozostawiono nas, abyśmy borykali się z żywiołami natury po tym, jak burza zmusiła piratów do przerwania ataku na naszą karawanę. Zostaliśmy przeniesieni na to niegościnne wybrzeże\nSpędziliśmy kilka dni naprawiając i odpoczywając. Ci poganinie zaatakowali nas znowu, jak tylko zamierzaliśmy odpłynąć\nA potem burza uderzyła w nas znowu - myśleliśmy, że Pan w końcu zdecydował się na nas skończyć, ale przybyłeś. Dzięki Świętej Maryi! Dziękuję Ci jeszcze raz, kapitanie!";
			link.l1 = "To już koniec, "+GetAddress_FormToNPC(NPChar)+". Teraz muszę cię odprowadzić do "+XI_ConvertString("Kolonia"+pchar.questTemp.WPU.Escort.StartCity+"Gen")+", aby chronić go przed innymi możliwymi problemami. Czy jesteś gotowy wyruszyć teraz? Burza już zaczęła ustępować.";
			link.l1.go = "VSP_Captain_1";
		break;
		
		case "VSP_Captain_1":
			dialog.text = "Ależ oczywiście! Im szybciej opuścimy to miejsce, tym spokojniejsi będą moi ludzie - już za dużo wycierpieli. Wypływajmy!";
			link.l1 = "Po prostu podążaj za moim statkiem - i uspokój swoją załogę, teraz nie ma się czego bać.";
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
			dialog.text = "Czy powinniśmy odpłynąć, kapitanie?";
			link.l1 = "Pewnie. Teraz wrócę do mojego statku.";
			link.l1.go = "exit";
			Diag.TempNode = "VSP_Captain_again";
		break;
		
		case "VSPShip_final":
			pchar.quest.Escort_fail.over = "yes";
			pchar.quest.DisasterShipWM_Over.over = "yes";//снимаем оба прерывания
			RemoveCharacterCompanion(Pchar, characterFromID("WMCaptain"));//удаляем компаньона
			pchar.questTemp.WPU.Escort.LevelUp_1Money = 10000+sti(pchar.rank)*200;
			dialog.text = "Chcę jeszcze raz podziękować, kapitanie - bardzo mi i mojej załodze pomogłeś wyjść z tego tarapatów. Oto są"+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.LevelUp_1Money))+". Cała załoga dorzuciła się, więc nawet nie myśl o rezygnacji. A to jest mój osobisty prezent dla ciebie.";
			link.l1 = "Cieszę się, że mogłem ci pomóc!";
			link.l1.go = "WMShip_final_1";
		break;
		
		case "SShip_final":
			pchar.questTemp.WPU.Escort.LevelUp_1Money = 5000+sti(pchar.rank)*100;
			RemovePassenger(Pchar, npchar);//удаляем пассажира
			dialog.text = "Chcę jeszcze raz podziękować, kapitanie, za uratowanie naszych tyłków z tego bałaganu. Proszę, przyjmij te monety - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.LevelUp_1Money))+"  a tu, przyjmij ten podarunek. To nie wiele, ale to wszystko, co mogę zrobić, aby podziękować ci za to, co zrobiłeś. Proszę, nie odrzucaj oferty\nMoi byli towarzysze są pełni podziwu dla ciebie i twojego walki z Indianami i piratami. Wszyscy chcą dołączyć do ciebie. Mam nadzieję, że nie odrzucisz prośby o lojalne usługi od marynarzy, którzy właśnie stracili swój statek?";
			link.l1 = "Oczywiście, nie. Chętnie to zatrzymam. Cieszę się, że mogłem ci pomóc!";
			link.l1.go = "WMShip_final_1";
		break;
		
		//Голландский Гамбит
		case "Stivesant_1":
			DelLandQuestMark(npchar);
			dialog.text = "Dobrze. Ale, panie, czy mógłbyś wyjaśnić, co się tu dzieje? Jak to się stało, że dowodzisz 'Meifeng'! Czy coś się stało z Longway?";
			link.l1 = "Mam wszystkie wyjaśnienia, których potrzebujesz - a także kilka innych ważnych informacji.";
			link.l1.go = "Stivesant_2";			
		break;
		
		case "Stivesant_2":
			dialog.text = "W takim razie słucham uważnie.";
			link.l1 = "Miał miejsce zamach stanu w Willemstad. Lucas Rodenburg zajął miejsce gubernatora i wsadził Matthiasa Becka do więzienia na absurdalne podejrzenie, że miał kontakty z brytyjskim wywiadem.";
			link.l1.go = "Stivesant_3";			
		break;
		
		case "Stivesant_3":
			dialog.text = "Hmm... Mynheer, rzeczy, które mi mówisz, są naprawdę zaskakujące. Otrzymałem wiadomości z Willemstad nie tak dawno temu, i nie było tam nic takiego.";
			link.l1 = "Proszę mnie wysłuchać, panie Stuyvesant. Musiał pan dostać wiadomości od Rodenburga, a on musi być pewien, że nie dostaniesz się na Curacao.";
			link.l1.go = "Stivesant_4";			
		break;
		
		case "Stivesant_4":
			dialog.text = "Panowie, coraz mniej podoba mi się to, co mówisz. Kim właściwie jesteś?";
			link.l1 = "Jestem tylko kapitanem i tylko człowiekiem, który nie jest obojętny na los holenderskich kolonistów. Lucas Rodenburg polecił Longway'owi zniszczyć twój statek i też cię zabić. A ponieważ 'Meifeng' nie wzbudziłby u ciebie podejrzeń, zrobiłby to bez żadnego wysiłku.";
			link.l1.go = "Stivesant_5";			
		break;
		
		case "Stivesant_5":
			dialog.text = "Czyli chcesz powiedzieć, że Lucas...";
			link.l1 = "Zdecydowałem usunąć cię z władzy najprostszym możliwym sposobem - po prostu eliminując cię. Oprócz ciebie, nie ma w regionie innej osoby, która mogłaby stawić jakikolwiek znaczący opór wpływom Rodenburga na Archipelagu.";
			link.l1.go = "Stivesant_6";			
		break;
		
		case "Stivesant_6":
			dialog.text = "Nie mogę w to uwierzyć!";
			link.l1 = "Nie dałem się nabrać na te bzdury o Becku powiązanym z angielskim wywiadem i przeprowadziłem własne śledztwo. Dowiedziałem się, że 'Meifeng', załadowany wybrańcami bandytów, wyruszył do Philipsburga. Ścigałem ich i stoczyłem z nimi bitwę. Longway został schwytany, a on dał mi wszystkie te informacje, w tym o twoim miejscu pobytu.";
			link.l1.go = "Stivesant_7";			
		break;
		
		case "Stivesant_7":
			dialog.text = "Hm... To wydaje się prawdopodobne. Nikt, oprócz Rodenburga, nie wiedział i nie mógł wiedzieć o moim harmonogramie i trasie! Cholera! To zdrada! Gdzie jest Longway?!";
			link.l1 = "Wypuściłem go w zamian za jego dobrowolne wyznanie. Muszę powiedzieć, że nie był zbyt chętny do wykonania rozkazu Rodenburga, ale nie mógł go także zignorować. Powiedział również, że nie wróci do służby u Rodenburga - ta ostatnia brudna sprawa przelała czarę goryczy.";
			link.l1.go = "Stivesant_8";			
		break;
		
		case "Stivesant_8":
			dialog.text = "W porządku... Kapitanie "+GetFullName(pchar)+", pojedziesz ze mną do Willemstad. Popłyniesz na 'Meifeng' przed moim statkiem. Jeśli to, co powiedziałeś, jest prawdą, Lucas musi zostać aresztowany, a ty udzielisz mi w tym pomocy. Ale jeśli mnie okłamałeś... Tylko siebie możesz obwiniać.";
			link.l1 = "Dla mnie, nie ma sensu kłamać ci, meneer. Pośpieszmy!";
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
			dialog.text = "Kapitanie, idź do 'Meifeng'. Czas dla nas wypłynąć.";
			link.l1 = "Tak, panie, oczywiście.";
			link.l1.go = "exit";
			Diag.TempNode = "Stivesant_10";
		break;
		
		case "Keller_1":
			dialog.text = "Bardzo interesujące! Proszę, opowiedz swoją historię. Postaram się zrobić wszystko, co w mojej mocy, aby pomóc.";
			link.l1 = "Pan Keller, czy pamiętasz, jak spotkałeś flet na swojej drodze do Willemstad kilka miesięcy temu. Na pokładzie był rodzinę żydowskich uciekinierów. Jadłeś na pokładzie tego statku, a potem kontynuowałeś swoją podróż.";
			link.l1.go = "Keller_2";
		break;
		
		case "Keller_2":
			dialog.text = "Tak, chyba tak... Tak, teraz pamiętam to całkiem jasno. Więc, o co chodzi?";
			link.l1 = "Flet został zatopiony przez piratów właśnie tego dnia. Tylko dwóch uchodźców zdołało się uratować - Solomon i jego córka Abigail. Znaleźli schronienie na wyspie zaledwie kilka mil stąd, gdzie doszło do ataku. Muszę znaleźć tę wyspę. Czy mógłbyś przypomnieć, gdzie spotkałeś ten flet? To bardzo ważne.";
			link.l1.go = "Keller_3";
		break;
		
		case "Keller_3":
			dialog.text = "I to wszystko, czego potrzebujesz? Znam tę wyspę. Jest bardzo blisko, między Trynidadem a Curaçao. Mała, niezamieszkana pustynna wyspa. Nawet nie ma tam Indian.";
			link.l1 = "A czy znasz jego przybliżone współrzędne?";
			link.l1.go = "Keller_4";
		break;
		
		case "Keller_4":
			dialog.text = "Mogę ci powiedzieć dokładne współrzędne. Jest to na 12  48'  Północy i 64  41'  Zachodu. Szukaj tam. Wyspa jest dość mała, ale powinieneś być w stanie łatwo ją zlokalizować.";
			link.l1 = "Dziękuję, panie Keller! Bardzo mi pomogłeś. Do widzenia.";
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
			dialog.text = "Czy chciałbyś coś jeszcze, kapitanie?";
			link.l1 = "Nie, dziękuję. Właśnie wracałem do mojego statku.";
			link.l1.go = "exit";
			Diag.TempNode = "Keller_6";
		break;
		
		// belamour рыбацкое судно -->
		case "FishingBoat":
			pchar.GenQuest.FishingBoatSecondTime = true;
			dialog.text = "Nic specjalnego, to jest łódź rybacka, łowimy tutaj ryby. Trzeba jakoś zarabiać na życie.";
			link.l1 = "Tak, zgadzam się, to są czasy...";
			link.l1.go = "FishingBoat_1";			
		break;
		
		case "FishingBoat_1":
			Diag.TempNode = "FishingBoat_1";
			dialog.text = "No więc, czego chcesz?";
			link.l1 = "Chciałem"+GetSexPhrase("","")+"aby dowiedzieć się najnowszych wiadomości z archipelagu.";
            link.l1.go = "rumours_capitan";
			link.l2 = "Jakie są twoje dzisiejsze połowy? Możesz sprzedać? Prozja by mi nie zaszkodziła...";
			link.l2.go = "FishingBoat_2";
			link.l3 = "Nic specjalnego, tylko przyszedłem cię powitać!";
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
				
				dialog.text = "Dzisiejszy połów jest dobry, wystarczy tylko zdążyć wyciągnąć sieci. Możemy to sprzedać ci, nawet taniej niż w sklepie - i tak sprzedajemy ryby lokalnemu kupcowi. Jeśli przeliczymy to wszystko na zapasy... Teraz mamy "+iTemp+" z tego, możemy sprzedać to za cenę "+iMoney+" pesos za sztukę. Ile weźmiesz?";
				link.l1.edit = 3;
				link.l1 = "";	
				link.l1.go = "Количество вбитого провианта";
				link.l2 = "Wiesz, zmieniłem zdanie na temat kupowania twoich zapasów.";	
				link.l2.go = "exit";
				
			}
			if(GetDataDay() > 10 && GetDataDay() < 21) 
			{
				Diag.TempNode = "FishingBoat_1";
				dialog.text = "Tak, coś, szczerze mówiąc, nie ma wcale ryb... Prawie nic dzisiaj nie złowiliśmy. Ale harpunami zostały nam nadmiarowe - myśleliśmy, że złapiemy jakąś dużą rybę lub wieloryba, jeśli mieliśmy szczęście... Może potrzebujesz harpunów?";
				link.l1 = "Nie, harpuny mnie nie interesują.";
				link.l1.go = "exit";
				link.l2 = "Hmm, harpun to także użyteczna rzecz w odpowiednich rękach. Chyba kupię.";
				link.l2.go = "Гарпуны";
			}
			if(GetDataDay() > 20)
			{
				dialog.text = "Tak, coś, szczerze mówiąc, wcale nie ma ryb... Dziś prawie nic nie złowiono. Więc nie ma zbyt wiele do sprzedania. Chyba że... Mam kilka drobiazgów, może coś cię zainteresuje. Chciałbyś zobaczyć?";
				link.l1 = "Nie, nie jestem zainteresowany błyskotkami.";
				link.l1.go = "exit";
				link.l2 = "Szkoda, że nie ma żadnej zdobyczy. No dobrze, zobaczmy przynajmniej na twoje cacka - nagle coś przyciągnie ...";
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
				dialog.text = "Jesteś zbyt drogi... Nie mam tyle! Możesz kupić mniej?";
				link.l1.edit = 3;
				link.l1 = "";	
				link.l1.go = "Количество вбитого провианта повтор";	
				link.l2 = "Wiesz, zmieniłem zdanie co do zakupu twoich zapasów.";	
				link.l2.go = "exit";
			}	
			if(iQty < 1)
			{
				dialog.text = "Czy żartujesz ze mną? Czy potrzebujesz prowiantu, czy nie? Jeśli tak, ile?";
				link.l1.edit = 3;
				link.l1 = "";	
				link.l1.go = "Количество вбитого провианта повтор";	
				link.l2 = "Wiesz, zmieniłem zdanie na temat kupna twoich zapasów.";	
				link.l2.go = "exit";
			}
			if(iQty > 0 && iQty <= iTemp)
			{
				dialog.text = "Zgoda! "+sti(iQty*iMoney)+" pesos.";
				if(sti(pchar.money) < iQty*iMoney)
				{
					link.l1 = "Hmm, nie mam tyle pieniędzy. Innym razem.";
					link.l1.go = "exit";
				}
				else
				{
					link.l1 = "Zgoda! Przeciągnij towary na mój statek.";
					link.l1.go = "Удачная покупка";
					link.l2 = "Wiesz, zmieniłem zdanie na temat kupowania twoich zapasów.";
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
				dialog.text = "Jesteś zbyt wymagający... Nie mam tyle! Czy możesz kupić mniej?";
				link.l1.edit = 3;
				link.l1 = "";	
				link.l1.go = "Количество вбитого провианта";	
				link.l2 = "Wiesz, zmieniłem zdanie na temat kupna twoich zapasów.";	
				link.l2.go = "exit";
			}	
			if(iQty < 1)
			{
				dialog.text = "Czy żartujesz ze mnie? Potrzebujesz zapasów czy nie? Jeśli tak, to ile?";
				link.l1.edit = 3;
				link.l1 = "";	
				link.l1.go = "Количество вбитого провианта";	
				link.l2 = "Wiesz, zmieniłem zdanie na temat kupna twoich zapasów.";	
				link.l2.go = "exit";
			}
			if(iQty > 0 && iQty <= iTemp)
			{
				dialog.text = "Umowa!"+sti(iQty*iMoney)+" pesos.";
				if(sti(pchar.money) < iQty*iMoney)
				{
					link.l1 = "Hmm, nie mam tyle pieniędzy. Innym razem.";
					link.l1.go = "exit";
				}
				else
				{
					link.l1 = "Zgoda! Przeciągnij towary na mój statek.";
					link.l1.go = "Удачная покупка";
					link.l2 = "Wiesz, zmieniłem zdanie na temat kupna twoich zapasów.";
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
				dialog.text = "Mamy "+iTemp+" sztuki. Możemy sprzedać za sto peso za harpun. Ile potrzebujesz?";
				link.l1.edit = 3;
				link.l1 = "";	
				link.l1.go = "Количество вбитых гарпунов";
				link.l2 = "Wiesz, zmieniłem zdanie, nie potrzebuję harpunów.";	
				link.l2.go = "exit";
		break;
		
		case "Количество вбитых гарпунов":
   
			iQty = sti(dialogEditStrings[3]);
			iTemp = makeint(pchar.GenQuest.FishingBoatITemp);
			pchar.GenQuest.FishingBoatIQty = iQty;
			Diag.TempNode = "FishingBoat_1";
			if(iQty > iTemp)
			{
				dialog.text = "Jesteś zbyt wymagający... Nie mam tyle! Czy możesz kupić mniej?";
				link.l1.edit = 3;
				link.l1 = "";	
				link.l1.go = "Количество вбитых гарпунов заново";	
				link.l2 = "Wiesz, zmieniłem zdanie, nie potrzebuję harpunów.";	
				link.l2.go = "exit";
			}	
			if(iQty < 1)
			{
				dialog.text = "Czy żartujesz ze mnie? Potrzebujesz harpunów czy nie? Jeśli tak, ile?";
				link.l1.edit = 3;
				link.l1 = "";	
				link.l1.go = "Количество вбитых гарпунов заново";	
				link.l2 = "Wiesz, zmieniłem zdanie, nie potrzebuję harpunów.";	
				link.l2.go = "exit";
			}
			if(iQty > 0 && iQty <= iTemp)
			{
				dialog.text = "Zgoda! "+sti(iQty*100)+" pesos.";
				if(sti(pchar.money) < iQty*100)
				{
					link.l1 = "Hmm, nie mam tyle pieniędzy. Innym razem.";
					link.l1.go = "exit";
				}
				else
				{
					link.l1 = "Zgoda! Znajdę dla nich zastosowanie.";
					link.l1.go = "Удачная покупка гарпунов";
					link.l2 = "Wiesz, zmieniłem zdanie, nie potrzebuję harpunów.";
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
				dialog.text = "Jesteś zbyt wymagający... Nie mam tyle! Czy możesz kupić mniej?";
				link.l1.edit = 3;
				link.l1 = "";	
				link.l1.go = "Количество вбитых гарпунов";	
				link.l2 = "Wiesz, zmieniłem zdanie, nie potrzebuję harpunów.";	
				link.l2.go = "exit";
			}	
			if(iQty < 1)
			{
				dialog.text = "Czy żartujesz ze mnie? Czy potrzebujesz harpunów, czy nie? Jeśli tak, ile?";
				link.l1.edit = 3;
				link.l1 = "";	
				link.l1.go = "Количество вбитых гарпунов";	
				link.l2 = "Wiesz, zmieniłem zdanie, nie potrzebuję harpunów.";	
				link.l2.go = "exit";
			}
			if(iQty > 0 && iQty <= iTemp)
			{
				dialog.text = "Zgoda! "+sti(iQty*100)+" pesos.";
				if(sti(pchar.money) < iQty*100)
				{
					link.l1 = "Hmm, nie mam tyle pieniędzy. Innym razem.";
					link.l1.go = "exit";
				}
				else
				{
					link.l1 = "Zgoda! Znajdę dla nich zastosowanie.";
					link.l1.go = "Удачная покупка гарпунов";
					link.l2 = "Wiesz, zmieniłem zdanie, nie potrzebuję harpunów.";
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
				dialog.text = "Nie, nie ma nic więcej. To łódź rybacka! Co jeszcze mogłoby tu być?";
				link.l1 = "Dobrze, rozumiem.";
				link.l1.go = "exit";
			}
			else if(hrand(2, "&SpeGoo") == 1)
			{
				if(ChangeContrabandRelation(pchar, 0) > 5)
				{
					
					dialog.text = "Cóż ... Mam tu jedną małą rzecz ... Zachowałem to, myślałem, że sprzedam to komuś. Ale za to wezmę dużo! I nie zaoferuję drugi raz. Czy chcesz popatrzeć?";
					link.l1 = "Pokaż mi, zobaczmy, co to za mała rzecz.";
					link.l1.go = "Особые товары предметы";
				}
				else
				{
					Diag.TempNode = "First time";
					Diag.CurrentNode = "First time";
					pchar.GenQuest.FishingBoatDialogEnb = "no special goods";
					dialog.text = "Nie, nic więcej tu nie ma. To łódź rybacka! Co jeszcze tu może być?";
					link.l1 = "Dobrze, rozumiem.";
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
					
					dialog.text = "Cóż ... Mam tutaj jedno dobro ... Czysto przypadkowo znalazłem to na brzegu zatoki. To jest "+iQty+" "+sTemp+". Cena za sztukę wynosi "+iMoney+". Ale sprzedam wszystko naraz i nie zaoferuję drugi raz. I aby żaden obcy nie wiedział o tym ... rozumiesz?";
					link.l1 = "Nie, nie chcę tych wątpliwej jakości towarów, dziękuję. Nikomu nie powiem, nie martw się.";
					link.l1.go = "exit";
					if(sti(pchar.money) >= iMoney*iQty)
					{
						link.l2 = "Rozumiem cię. Ale towary są tego warte. Biorę to. Niech go dostarczą do mojego statku.";
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
				dialog.text = "To "+GetConvertStr("itmname_"+sTemp,"OpisPrzedmiotów.txt")+". Udało mi się zdobyć ... no, nie ważne gdzie. Myślałem sprzedać to jakiemuś smakoszowi. Dam ci to za tylko 10 000 pesos! Weźmiesz to?";
				if(sti(pchar.money) > 9999)
				{
					link.l1 = "Wezmę to, oczywiście! Rzecz stoi.";
					link.l1.go = "Купили особый товар";
				}
				link.l2 = "Nie, nie potrzebuję tego. Nie wezmę. ";
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
