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
					dialog.text = "Hallo, Kapitän. Verdammt, Sie haben keine Ahnung, wie froh ich bin, Sie zu sehen!";
					link.l1 = "Hallo. Erlauben Sie mir, mich vorzustellen - "+GetFullName(PChar)+". Ich bin auch froh, dich lebendig und munter zu sehen, ich bin extra hierher gekommen, um dich - und dein Schiff - zu suchen.";
					link.l1.go = "WM_Captain";
					break;
				}
				if (CheckAttribute(PChar, "questTemp.WPU.Escort.LevelUp_1WM") && pchar.questTemp.WPU.Escort == "wait" && NPChar.id == "WMCaptain")
				{
					dialog.text = "Haben Sie das Material gebracht, das ich angefordert habe?";
					if (sti(pchar.questTemp.WPU.Escort.Planks) - GetSquadronGoods(pchar, GOOD_PLANKS) <= 0 && sti(pchar.questTemp.WPU.Escort.Sailcloth) - GetSquadronGoods(pchar, GOOD_SAILCLOTH) <= 0 && sti(pchar.questTemp.WPU.Escort.Linen) - GetSquadronGoods(pchar, GOOD_COTTON) <= 0)
					{
						link.l1 = "Ja. Alles, was du brauchst, um dein Schiff zu reparieren, ist in meinem Laderaum.";
						link.l1.go = "WM_Captain_5";
					}
					else
					{
						link.l1 = "Nein, ich arbeite noch daran.";
						link.l1.go = "exit";
					}
					break;
				}
				if (CheckAttribute(PChar, "questTemp.WPU.Escort.LevelUp_1VSP") && pchar.questTemp.WPU.Escort == "toCap" && NPChar.id == "WMCaptain")
				{
					dialog.text = "Ahoi, "+GetAddress_Form(NPChar)+". Mein Name ist "+GetFullName(NPChar)+", ich bin der Kapitän dieses Schiffes. Lassen Sie mich meine aufrichtigste Dankbarkeit für Ihre Hilfe in einem Kampf mit diesem verdammten Piratengesindel ausdrücken - wenn Sie nicht eingegriffen hätten, hätte es für uns ziemlich düster aussehen können. Sie haben uns tatsächlich gerettet, verdammt nochmal!";
					link.l1 = "Es war nichts,  "+GetAddress_FormToNPC(NPChar)+". Darf ich mich vorstellen - "+GetFullName(PChar)+", Ich kam zu Ihnen auf Antrag des Hafenmeisters "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen")+". Er hat mich über die Missgeschicke Ihrer Karawane informiert und mich geschickt, um Ihr Schiff zu finden.";
					link.l1.go = "VSP_Captain";
					break;
				}
				//<-- эскорт 2 уровень
				
				if(CheckAttribute(NPChar, "surrendered"))
				{
					Pchar.GenQuest.MoneyForCaptureShip = makeint(Group_GetLiveCharactersNum( GetGroupIDFromCharacter(NPChar)))*(8 - sti(RealShips[sti(NPChar.Ship.Type)].Class))*(1+rand(10))*500);
					if(HasShipTrait(pchar, "trait14")) Pchar.GenQuest.MoneyForCaptureShip = makeint(sti(Pchar.GenQuest.MoneyForCaptureShip) * 1.35);
					dialog.text = "Halt ein, du könntest mich auf diese Weise töten. Was willst du von mir?";
					//выкуп
					link.l1 = "Lassen wir diese Angelegenheit friedlich klären. Lösegeld, denke ich, wird die beste Entscheidung sein. Eine Summe von "+Pchar.GenQuest.MoneyForCaptureShip+" Pesos werden mir gut passen, "+GetAddress_FormToNPC(NPChar)+". Und danach kannst du dich verlaufen!";
					link.l1.go = "surrender1";
					// обираем до нитки
					link.l2 = "Ich würde gerne sehen, was du in deinem Laderaum hast. Und danach kannst du und deine Crew gehen, wohin ihr wollt.";
					link.l2.go = "surrender2";
					break;
				}
				
				//Голландский Гамбит, против всех
				if (CheckAttribute(PChar, "questTemp.HWIC.Self") && pchar.questTemp.HWIC.Self == "MeetingStivesant" && NPChar.id == "Stivesant")
				{
					dialog.text = "Hallo, Mynheer. Schön, Sie zu sehen. Kapitän Longway wird wahrscheinlich später an Bord kommen, oder?";
					link.l1 = "Guten Nachmittag, Mynheer Stuyvesant. Erlauben Sie mir, mich vorzustellen - "+GetFullName(pchar)+". Longway wird nicht kommen, er ist nicht auf 'Meifeng'.";
					link.l1.go = "Stivesant_1";
					pchar.quest.QuestShipsTerms_Over.over = "yes"; //снять таймер
					break;
				}
				if (CheckAttribute(PChar, "questTemp.HWIC.Self") && pchar.questTemp.HWIC.Self == "FleutOnTrinidad" && NPChar.id == "Keller")
				{
					DelLandQuestMark(npchar);
					dialog.text = "Ahoi, Kapitän. Was hat dich zu meiner Flöte gebracht?";
					link.l1 = "Guten Nachmittag, Herr Keller. Darf ich mich vorstellen - "+GetFullName(pchar)+". Ich bin gekommen, um Ihre Hilfe in einer ungewöhnlichen Angelegenheit zu erbitten.";
					link.l1.go = "Keller_1";
					break;
					//Голландский гамбит
				}
				// belamour рыбацкое судно -->
				if(npchar.id == "FishingBoatCap")
				{
					if(!CheckAttribute(pchar, "GenQuest.FishingBoatSecondTime"))
					{
						Dialog.text = TimeGreeting()+", "+GetAddress_Form(NPChar)+"! Ich bin der Kapitän von "+GetFullName(NPChar)+". Was bringt dich an Bord meines Schiffes?";
						link.l1 = "Und einen guten Tag wünsche ich Ihnen. Was tun Sie in dieser Bucht?";
						link.l1.go = "FishingBoat";
						break;
					}
					else
					{
						Diag.CurrentNode = "first time";
						dialog.text = "Gibt es noch etwas, über das Sie sprechen möchten?";
						link.l1 = "Ich wollte"+GetSexPhrase("","")+", um die neuesten Nachrichten aus dem Archipel zu erfahren.";
						link.l1.go = "rumours_capitan";
						if(CheckAttribute(pchar,"GenQuest.FishingBoatDialogEnb"))
						{
							link.l2 = "Zeig mir bitte noch einmal, welche Art von Krimskrams du zum Verkauf hast. ";
							link.l2.go = "Торговля";
							if(pchar.GenQuest.FishingBoatDialogEnb != "no special goods")
							{
								link.l3 = "Hmm, vielleicht suchst du im Laderaum nach mehr - vielleicht findet sich etwas zum Verkauf?";
								link.l3.go = "Особые товары";
							}
						}
						link.l4 = "Nichts Besonderes, ich bin nur gekommen, um dich zu begrüßen!";
						link.l4.go = "exit";	
						break;
					}
				}
				// <-- рыбацкое судно
				
				//belamour legendary edition диалоги, если герой имеет звания и заслуги перед отечеством -->
				// генерал губернатор
				if(CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE)
				{
					Dialog.text = "Gouverneur General, Eure Gnaden, Grüße! Was kann ich für Euch tun?";
					link.l1 = "Ich habe Geschäft für dich!";
					link.l1.go = "quests";
					link.l2 = "Nichts Besonderes, bin nur gekommen, um dich zu begrüßen!";
					link.l2.go = "exit";
					break;
				}
				// вице адмирал
				if(isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && sti(Items[sti(pchar.EquipedPatentId)].Nation) == npchar.nation)
				{
					Dialog.text = "Willkommen an Bord meines Schiffes, Vizeadmiral! Was kann ich für Sie tun?";
					link.l1 = "Ich habe Geschäft für dich!";
					link.l1.go = "quests";
					link.l2 = "Nichts Besonderes, ich kam nur, um dich zu grüßen!";
					link.l2.go = "exit";
					break;
				}
				// Офицер с патентом
				if(IsOfficerFullEquip() && sti(Items[sti(pchar.EquipedPatentId)].Nation) == npchar.nation)
				{
					Dialog.text = "Freut mich, einen Kameraden zu sehen, Kapitän! Wie kann ich helfen?";
					link.l1 = "Ich habe Geschäfte für dich!";
					link.l1.go = "quests";
					link.l2 = "Nichts Besonderes, ich kam nur, um dich zu begrüßen!";
					link.l2.go = "exit";
					break;
				}			
				// <-- legendary edition
                if (CheckAttribute(NPChar, "EncType")  && NPChar.EncType == "war")
                {
    			    Dialog.text = TimeGreeting()+", "+GetAddress_Form(NPChar)+"! Ich bin "+GetFullName(NPChar)+" - Kapitän eines Schiffes, das der "+NationKingsName(NPChar)+". Flotte. Was hat dich an Bord meines Schiffes gebracht?";
    			}
    			else
                {
    			    Dialog.text = TimeGreeting()+", "+GetAddress_Form(NPChar)+"! Ich bin Kapitän "+GetFullName(NPChar)+". Was hat dich an Bord meines Schiffes gebracht?";
    			}
    			link.l1 = "Mein Name ist "+GetFullName(Pchar)+". Ich habe Geschäfte mit dir!";
    			link.l1.go = "quests";
                link.l2 = "Ach, nichts, nur "+GetSexPhrase("kam","kam")+", dich zu begrüßen!";
    			link.l2.go = "exit";
            }
            else
            {
                Dialog.text = "Hast du nicht bemerkt, , "+GetAddress_Form(NPChar)+", dass wir in einer Schlacht sind? Es ist nicht die Zeit zum Reden!";
    			link.l1 = "Absolut einverstanden! Ich werde zu meinem Schiff zurückkehren.";
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
					Dialog.text = TimeGreeting()+", "+GetAddress_Form(NPChar)+"! Ich bin der Kapitän von "+GetFullName(NPChar)+". Was verschafft mir die Ehre deines Besuchs auf meinem Schiff?";
					link.l1 = "Und einen guten Tag für dich. Was machst du in dieser Bucht?";
					link.l1.go = "FishingBoat";
					break;
				}
				else
				{
					dialog.text = "Gibt es noch etwas, über das Sie sprechen möchten?";
					link.l1 = "Ich wollte"+GetSexPhrase("","")+" um die neuesten Nachrichten aus dem Archipel zu erfahren.";
					link.l1.go = "rumours_capitan";
					if(CheckAttribute(pchar,"GenQuest.FishingBoatDialogEnb"))
					{
						link.l2 = "Zeigen Sie mir bitte noch einmal, welche Art von Krimskrams Sie zum Verkauf haben. ";
						link.l2.go = "Торговля";
						if(pchar.GenQuest.FishingBoatDialogEnb != "no special goods")
						{
							link.l3 = "Hmm, vielleicht im Laderaum nach mehr suchen - vielleicht findet sich etwas zum Verkauf?";
							link.l3.go = "Особые товары";
						}
					}
					link.l4 = "Nichts Besonderes, ich kam nur, um dich zu begrüßen!";
					link.l4.go = "exit";	
					break;
				}
			}
			// <-- рыбацкое судно
            if (!CheckAttribute(NPChar, "MainCaptanId")  || NPChar.MainCaptanId == pchar.GenQuest.CaptainId)
            {
                Dialog.text = "Ich höre Ihnen sehr aufmerksam zu,  "+GetAddress_Form(NPChar)+".";
                link.l1 = "Ich möchte die neuesten Nachrichten des Archipels erfahren.";
                //homo 25/06/06
                link.l1.go = "rumours_capitan";
                //belamour legendary edition 
				bOk1 = isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && GetNationRelation(npchar.nation, sti(Items[sti(pchar.EquipedPatentId)].Nation)) != RELATION_ENEMY;
				bOk2 = CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && GetNationRelation(npchar.nation, FRANCE) != RELATION_ENEMY;
				bOk = bOk1 || bOk2;
                if (CheckAttribute(NPChar, "EncGroupName") && !bOk) // только для фантомов грабеж
                {
                    link.l2 = RandPhraseSimple("Hast du eine Ahnung, wer ich bin? Ich denke, es ist völlig klar, dass meine Kanonen aus deinem alten Kahn ein Sieb machen können. Lassen wir das auf friedliche Weise klären. Ein Lösegeld ist für mich eine gute Entscheidung.","Nur wir... und das Meer... Was hältst du davon, meine Männer zu besänftigen... für deine eigene Sicherheit?");
                    link.l2.go = "Talk_board";
                }
                if (CheckAttribute(NPChar, "Ship.Mode") && NPChar.Ship.Mode == "Trade")
                {
	           		link.l3 = "Wo kommst du her?";
	    			link.l3.go = "price_1";
	    			link.l4 = "Möchtest du handeln?";
	    			link.l4.go = "Trade_1";
    			}
				//--> квест мэра, поиски пирата
				if (CheckAttribute(pchar, "GenQuest.DestroyPirate"))
				{
	    			link.l6 = "Ich suche nach einem Piratenschiff, das in diesen Gewässern operiert. Haben Sie etwas Verdächtiges gesehen?";
	    			link.l6.go = "MQ_step_1";
				}
				//<-- квест мэра, поиски пирата
    			link.l5 = "Möchtest du dich entspannen?";
			    link.l5.go = "Play_Game";
                link.l9 = "Ich denke, ich sollte gehen.";
    			link.l9.go = "exit";
			}
			else
			{
                Dialog.text = "Ich bin nicht befugt, mit Ihnen zu verhandeln. Sprechen Sie mit dem Kommandeur unserer Staffel. Sein Name ist  "+GetFullName(characterFromID(NPChar.MainCaptanId))+", du kannst ihn auf dem "+XI_ConvertString(RealShips[sti(characters[GetCharacterIndex(NPChar.MainCaptanId)].Ship.Type)].BaseName)+" '"+characters[GetCharacterIndex(NPChar.MainCaptanId)].Ship.Name+"'.";
                link.l1 = "Danke. Ich werde tun, wie du sagst.";
                link.l1.go = "exit";
                Diag.TempNode = "Go_away_Good";
			}
        break;
        case "Trade_1":
			dialog.text = "Warum nicht?";
			link.l1 = "Lass uns die Waren ansehen.";
			link.l1.go = "Trade_2";
			link.l2 = "Ich habe meine Meinung geändert.";
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
			dialog.text = "Was schlägst du vor?";
			link.l1 = "Möchtest du eine Partie Karten um richtiges Geld spielen?";
			link.l1.go = "Card_Game";
   			link.l2 = "Wie wäre es mit einigen Würfeln im Poker-Joker?";
			link.l2.go = "Dice_Game";
			link.l10 = "Es tut mir leid, aber ich habe etwas zu tun.";
			link.l10.go = "exit";
		break;
        // карты -->
        case "Card_Game":
            if (!CheckNPCQuestDate(npchar, "Card_date_Yet") || isBadReputation(pchar, 30) || GetCharacterSkillToOld(pchar, SKILL_LEADERSHIP) < rand(3))
            {
                SetNPCQuestDate(npchar, "Card_date_Yet");
                dialog.text = "Ich werde nicht mit Gaunern spielen!";
    			link.l1 = "Wie du wünschst.";
    			link.l1.go = "exit";
			}
			else
			{
                dialog.text = "Warum nicht? Ich hätte sicherlich nichts gegen eine Pause...";
    			link.l1 = "Ausgezeichnet.";
    			link.l1.go = "Cards_begin";
    			link.l2 = "Was sind die Regeln?";
    			link.l2.go = "Cards_Rule";
			}
		break;

		case "Cards_Rule":
   			dialog.text = CARDS_RULE;
			link.l1 = "Nun, dann lass uns anfangen!";
			link.l1.go = "Cards_begin";
			link.l3 = "Nein, das ist nichts für mich...";
			link.l3.go = "exit";
		break;

		case "Cards_begin":
			Dialog.text = "Lassen wir uns zuerst auf die Wette einigen.";
			link.l1 = "Lass uns um 100 Pesos spielen.";
			link.l1.go = "Cards_Node_100";
			link.l2 = "Lass uns um 500 Pesos spielen.";
			link.l2.go = "Cards_Node_500";
			link.l3 = "Ich denke, ich sollte gehen.";
			link.l3.go = "exit";
		break;

		case "Cards_Node_100":
		    if (sti(pchar.Money) < 300)
		    {
                dialog.text = "Machst du Witze oder was? Du hast kein Geld!";
                link.l1 = "Es geschieht.";
			    link.l1.go = "exit";
			    break;
		    }
		    if (sti(npchar.Money) < 300)
		    {
                dialog.text = "Nun, das reicht, sonst habe ich nicht genug Geld, um das Schiff zu unterhalten...";
                link.l1 = "Schade.";
			    link.l1.go = "exit";
			    break;
		    }
   			dialog.text = "Gut, lass uns um 100 Münzen spielen.";
			link.l1 = "Lass uns anfangen!";
			link.l1.go = "Cards_begin_go";
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
            pchar.GenQuest.Cards.iRate     = 100;
            pchar.GenQuest.Cards.SitType   = false;
		break;

		case "Cards_Node_500":
		    if (sti(pchar.Money) < 1500)
		    {
                dialog.text = "Machst du Witze oder was? Du hast keine 1500 Pesos!";
                link.l1 = "Ich werde sie finden!";
			    link.l1.go = "exit";
			    break;
		    }
		    if (sti(npchar.Money) < 1500)
		    {
                dialog.text = "Nein, diese Wetten werden mich sicherlich am Ende kriegen.";
                link.l1 = "Wie du wünschst.";
			    link.l1.go = "exit";
			    break;
		    }
   			dialog.text = "Gut, wir spielen um 500 Münzen.";
			link.l1 = "Lass uns beginnen!";
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
                dialog.text = "Ich werde nicht mit Gaunern spielen!";
    			link.l1 = "Wie du wünschst.";
    			link.l1.go = "exit";
			}
			else
			{
				if (CheckNPCQuestDate(npchar, "Dice_date_begin"))
				{
					dialog.text = "Warum nicht! Entspannung ist immer gut für die Gesundheit... aber nicht immer für die Brieftasche...";
	    			link.l1 = "Ausgezeichnet.";
	    			link.l1.go = "Dice_begin";
	    			link.l2 = "Wie lauten die Regeln unseres Spiels?";
	    			link.l2.go = "Dice_Rule";
    			}
    			else
    			{
					dialog.text = "Nein, ich habe für heute genug. Ich habe Dinge zu erledigen.";
	    			link.l1 = "Wie du wünschst.";
	    			link.l1.go = "exit";
				}
			}
		break;

		case "Dice_Rule":
   			dialog.text = DICE_RULE;
			link.l1 = "Nun, dann lass uns beginnen!";
			link.l1.go = "Dice_begin";
			link.l3 = "Nein, das ist nichts für mich...";
			link.l3.go = "exit";
		break;

		case "Dice_begin":
			Dialog.text = "Lassen wir uns zuerst auf die Wette einigen.";
			link.l1 = "Lass uns um 50 Pesos spielen.";
			link.l1.go = "Dice_Node_100";
			link.l2 = "Lass uns um 200 Pesos spielen.";
			link.l2.go = "Dice_Node_500";
			link.l3 = "Ich denke, ich sollte gehen.";
			link.l3.go = "exit";
		break;

		case "Dice_Node_100":
			//belamour legendary edition 
			bOk1 = isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && GetNationRelation(npchar.nation, sti(Items[sti(pchar.EquipedPatentId)].Nation)) != RELATION_ENEMY;
			bOk2 = CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && GetNationRelation(npchar.nation, FRANCE) != RELATION_ENEMY;
			bOk = bOk1 || bOk2;
            if (!CheckDiceGameSmallRate() && !bOk)
		    {
                dialog.text = "Du bist bekannt als ein"+GetSexPhrase("Schwindler","Schwindler")+".. Ich werde niemals mit dir würfeln.";
                link.l1 = "Es ist alles Lügen! Nun, sei es so.";
			    link.l1.go = "exit";
			    break;
		    }

			if (sti(pchar.Money) < 300)
		    {
                dialog.text = "Scherzt du oder was? Du hast kein Geld!";
                link.l1 = "Es passiert.";
			    link.l1.go = "exit";
			    break;
		    }
		    if (sti(npchar.Money) < 300)
		    {
                dialog.text = "Genug ist genug! Ich habe genug vom Glücksspiel - bevor sie mich als Unterschlagend beschimpfen und mich zwingen, das Schiff zu verlassen.";
                link.l1 = "Schade.";
			    link.l1.go = "exit";
			    break;
		    }
   			dialog.text = "Gut, spielen wir um 50 Münzen.";
			link.l1 = "Lass uns beginnen!";
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
                dialog.text = "Du bist bekannt als ein"+GetSexPhrase("Betrüger","Schwindler")+". Ich werde niemals mit dir würfeln.";
                link.l1 = "Das sind alles Lügen! Nun, sei es so.";
			    link.l1.go = "exit";
			    break;
		    }
			if (!CheckDiceGameBigRate())
		    {
                dialog.text = "Ich habe gehört, dass du ein sehr guter Spieler bist. Ich werde nicht um hohe Einsätze mit dir spielen.";
                link.l1 = "Sollen wir vielleicht den Einsatz senken?";
			    link.l1.go = "Dice_Node_100";
				link.l2 = "Es tut mir leid, aber ich muss gehen.";
			    link.l2.go = "exit";
			    break;
		    }

			if (sti(pchar.Money) < 1500)
		    {
                dialog.text = "Machst du Witze oder was? Du hast keine 1500 Pesos!";
                link.l1 = "Ich werde sie finden!";
			    link.l1.go = "exit";
			    break;
		    }
		    if (sti(npchar.Money) < 1500)
		    {
                dialog.text = "Nein, diese Wetten werden mich am Ende sicherlich kriegen.";
                link.l1 = "Wie du wünschst.";
			    link.l1.go = "exit";
			    break;
		    }
   			dialog.text = "Gut, spielen wir um 200 Münzen.";
			link.l1 = "Lass uns anfangen!";
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
	                Dialog.Text = "Warum wollen Sie das wissen? Das ist meine Privatsphäre.";
					Link.l1 = "Wie du wünschst.";
					Link.l1.go = "exit";
	            }
	            else
	            {
                    sld = &Characters[iMoney];
                    pchar.PriceList.ShipStoreIdx = iMoney;
                    
					Dialog.Text = "Ich komme aus der Stadt"+GetCityName(sld.City)+".";
					Link.l1 = "Wie sind die Preise für Waren im örtlichen Laden?";
					Link.l1.go = "price_2";
					Link.l9 = "Ich sollte gehen.";
					Link.l9.go = "exit";
				}
			}
			else
			{
                Dialog.Text = "Ich habe dir schon alles erzählt. Belästige mich nicht umsonst.";
				Link.l1 = "Ja, du hast recht. Lebewohl.";
				Link.l1.go = "exit";
            }
		break;
		
		case "price_2":
            sld = &Characters[sti(pchar.PriceList.ShipStoreIdx)];
			SetPriceListByStoreMan(&Colonies[FindColony(sld.City)]);
			Dialog.Text = "Hier hast du... (du hast die Preisliste erhalten)..";
			Link.l1 = "Vielen Dank!";
			Link.l1.go = "exit";
			PlaySound("interface\important_item.wav");
		break;
		
        case "Talk_board":
            if ((Group_GetCharactersNum(NPChar.EncGroupName) - Group_GetDeadCharactersNum(NPChar.EncGroupName)) > GetCompanionQuantity(PChar) && rand(11) > GetCharacterSkillToOld(PChar, SKILL_FORTUNE))
            {
                Dialog.text = "Ha-ha-ha! Großer Witz, ich habe mehr Schiffe. Kehre zu deinem Schiff zurück und ertrinke damit.";
                link.l1 = "Mehr bedeutet nicht stärker, Kumpel.";
                link.l1.go = "Boarding";
            }
            else
            {
                if(rand(21) > (GetSummonSkillFromNameToOld(PChar, SKILL_GRAPPLING) + GetSummonSkillFromNameToOld(PChar, SKILL_LEADERSHIP)) )
                {
                    Dialog.text = "Kapitän, Sie hätten Ihr schmutziges Geschäft nicht an Bord meines Schiffes machen sollen. Aber ich werde Gnade zeigen und Sie zu Ihrem Schiff zurückkehren lassen, um mit ihm zu ertrinken.";
                    link.l1 = "Wir werden sehen, wer heute zum Hai-Futter wird!";
                    link.l1.go = "Boarding";
                }
                else
                {
                    Pchar.GenQuest.MoneyForCaptureShip = makeint(100 + (Group_GetCharactersNum(NPChar.EncGroupName) - Group_GetDeadCharactersNum(NPChar.EncGroupName))*(8 - sti(RealShips[sti(NPChar.Ship.Type)].Class))*(1+rand(10))*500);
					if(HasShipTrait(pchar, "trait14")) Pchar.GenQuest.MoneyForCaptureShip = makeint(sti(Pchar.GenQuest.MoneyForCaptureShip) * 1.35);
                    Dialog.text = RandSwear()+"Ja, ich habe viel von deinen Empörungen gehört. So sei es, aber erinnere dich "+XI_ConvertString(NationShortName(sti(NPChar.nation))+"hunter")+" wird es nicht ungestraft lassen!";
                    link.l1 = "Ausgezeichnet. Eine Summe von "+Pchar.GenQuest.MoneyForCaptureShip+" Pesos werden mir gut passen, "+GetAddress_FormToNPC(NPChar)+".";
                    link.l1.go = "Capture";
                    link.l2 = "Ach, vergiss es. Ich habe nur gescherzt"+GetSexPhrase("","")+"!";
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
            Dialog.Text = "Hier hast du - und jetzt verschwinde!";
			Link.l1 = "Schön! Und bleib auch du gesund, Freund!";
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
			Dialog.Text = "Was willst du sonst noch von mir?";
			Link.l1 = "Nichts.";
			Link.l1.go = "exit";
			Diag.TempNode = "surrender_goaway";
		break;
		
		case "surrender2":			
			dialog.text = "Scheint so, als hätte ich keine andere Wahl, als mich Ihnen zu unterwerfen.";
			link.l1 = "Mach weiter, jetzt!";
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
			Link.l1 = RandPhraseSimple(RandSwear()+"Das ist sehr interessant. Noch eine Frage?","Nur eine weitere Affäre.");
			Link.l1.go = "quests";
			Link.l2 = RandPhraseSimple("Danke, und ich sollte gehen.","Alles Gute.");
			Link.l2.go = "exit";
			Diag.TempNode = "quests";
		break;
		
		case "Go_away":
			Dialog.Text = "Raus aus meinem Schiff!";
			Link.l1 = "Ich gehe schon.";
			Link.l1.go = "exit";
			Diag.TempNode = "Go_away";
		break;
		
		case "Go_away_Good":
			Dialog.Text = "Unser Gespräch ist beendet. Ich werde dir nichts Neues erzählen "+GetAddress_Form(NPChar)+".";
			Link.l1 = "In Ordnung. Wir sehen uns auf See!";
			Link.l1.go = "exit";
			Diag.TempNode = "Go_away_Good";
		break;

        case "Capture":
            Diag.TempNode = "Go_away";
            Dialog.Text = "Hier hast du es - und jetzt hau ab!";
			Link.l1 = "Schön!";
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
            Dialog.Text = "Halt ein, du könntest mich auf diese Weise töten. Was willst du von mir?";
			Link.l1 = "Um dich zu töten!";
			Link.l1.go = "QuestAboardCabinDialog_1";
			Link.l2 = "Ergib dich!";
			Link.l2.go = "QuestAboardCabinDialog_2";
			Link.l3 = "Gib uns die Karte, Billy (c)";  // предмет, далее не ясно или  QuestAboardCabinDialog_1 или QuestAboardCabinDialog_2
			Link.l3.go = "QuestAboardCabinDialog_3";  // можно закодить покидание корабля, но экипаж уже вырезан и тп...
        break;
        
        case "QuestAboardCabinDialog_1":
			Dialog.Text = "Nun, wir werden sehen, du Bastard!";
			Link.l1 = "Und was muss ich sehen?";
			Link.l1.go = "exit";
			// тут можно восстановить НР противника (NPChar) или добавить парочку гардов против ГГ
			LAi_SetCurHPMax(NPChar);
			AddDialogExitQuestFunction("QuestAboardCabinDialogExitWithBattle"); // тут ругань обратно
		break;
		
		case "QuestAboardCabinDialog_2":
			Dialog.Text = "Gut, du hast gewonnen!";
			Link.l1 = "Kluge Entscheidung!";
			Link.l1.go = "exit";
			AddDialogExitQuestFunction("QuestAboardCabinDialogSurrender");
		break;
		
		case "QuestAboardCabinDialog_3":
			Dialog.Text = "Hoffe, du verschluckst dich daran!";
			Link.l1 = "Sehr gut, leg die Fesseln an und halt den Mund, Gefangener.";
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
			Dialog.Text = ""+GetSexPhrase("Kam hierher","Kam hierher")+", machte einen Saustall"+GetSexPhrase("","")+",und nahm alles"+GetSexPhrase("","")+", jetzt willst du mich zu einem Sklaven machen? Niemals!";
			Link.l1 = "Dann bereite dich auf den Tod vor.";
			Link.l1.go = "QuestAboardCabinDialog_1";
		break;
		//eddy. квест мэра, поиски пирата
		case "MQ_step_1":
			Dialog.Text = "Nein, ich habe kein verdächtiges Schiff gesehen, das wie Piraten aussah.";
			Link.l1 = "Ich sehe.";
			Link.l1.go = "exit";
		break;
		
		//homo Наводка на купца
		case "MerchantTrap_Abordage":

			Dialog.Text = "Im Namen von "+NationKingsName(NPChar)+" kapituliere, "+GetSexPhrase("schmutziger Pirat","verdammte Dirne!")+"! Dann wird dein Leben verschont, bis zu einem fairen Tribunal, wo du für alles beurteilt wirst "+NationNameSK(sti(NPChar.nation))+"Schiffe, die du geplündert hast"+GetSexPhrase("","")+".";
			Link.l1 = "Zum Teufel mit dir! Du solltest dich ergeben!";
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
					dialog.text = "Eure Exzellenz, Gouverneur General! Ich höre Ihnen aufmerksam zu, bitte Sie aber, sich kurz zu fassen: wir kämpfen gerade mit "+fort+", und ich muss den Verlauf der Schlacht lenken.";
				}
				else
				{
					if(isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && sti(Items[sti(pchar.EquipedPatentId)].Nation) == npchar.nation)
					{
						dialog.text = "Vizeadmiral! Ich höre Ihnen genau zu, aber ich habe wenig Zeit: wir kämpfen mit "+fort+", und ich muss den Verlauf der Schlacht lenken.";
					}
					else
					{
						dialog.text = "Ich höre Ihnen zu, aber lassen Sie uns schnell den Zweck Ihres Besuchs klären, wir kämpfen mit "+fort+", und ich muss den Verlauf der Schlacht lenken.";
					}
				}
                link.l1 = "Darum bin ich hier,  "+GetAddress_FormToNPC(NPChar)+".";
                link.l1.go = "attack_fort";

                link.l2 = "In diesem Fall werde ich nicht mehr Ihre Zeit in Anspruch nehmen. Lebewohl, "+GetAddress_FormToNPC(NPChar)+".";
                link.l2.go = "exit";
    			
            }
            else
            {
                Dialog.text = "Ich bin nicht berechtigt, mit Ihnen zu verhandeln. Sprechen Sie mit dem Kommandeur unseres Geschwaders. Sein Name ist  "+GetFullName(rchar)+", du kannst ihn auf finden "+XI_ConvertString(RealShips[sti(rchar.Ship.Type)].BaseName)+" ''"+rchar.Ship.Name+"''.";
                link.l1 = "Danke. Ich werde tun, wie du sagst.";
                link.l1.go = "exit";
            
            }
            Diag.TempNode = "Siegehelp";
            
		break;
		
		case "attack_fort":
                dialog.text = "Und was meinst du damit?";
                link.l1 = "Ich kann Ihnen helfen, das Fort der Kolonie zu zerstören "+GetConvertStr(aData.Colony+" Stadt","LocLables.txt")+" und erobern die Stadt, und eine Beute, im Falle unseres Erfolges, teilen wir unter uns auf.";
                link.l1.go = "Siegehelp_1";
                link.l2 = "Eigentlich ist mein Geschäft kaum Ihrer Zeit wert. Auf Wiedersehen, "+GetAddress_FormToNPC(NPChar)+".";
                link.l2.go = "exit";
                Diag.TempNode = "Siegehelp_0";
		break;
		
		case "Siegehelp_0":
            Dialog.text = "Du schon wieder? Ich dachte, wir hätten bereits alles besprochen.";
            link.l1 = "Du hast recht. Ich glaube, ich habe es vergessen"+GetSexPhrase("","")+".";
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
                dialog.text = "Und welchen Anteil an der Beute erwartest du zu erhalten?";
                link.l1 = "Ein Halbes.";
                link.l1.go = "Big_part";
                link.l2 = "Ein Drittel.";
                link.l2.go = "Middle_part";
                link.l3 = "Ein Viertel.";
                link.l3.go = "Small_part";
            }
            else
            {
                dialog.text = "Ich brauche Ihre Dienste nicht, Kapitän! Ich werde diese Kolonie selbst erobern und ich brauche dabei keine Hilfe.";
                link.l1 = "Warum bist du so sicher, "+GetAddress_FormToNPC(NPChar)+", jeder kann einen Schlag des Unglücks haben.";
                link.l1.go = "attack_fort_03";
                link.l2 = "In diesem Fall werde ich nicht mehr Ihrer Zeit in Anspruch nehmen, "+GetAddress_FormToNPC(NPChar)+". Lebewohl!";
                link.l2.go = "exit";
            }
			Diag.TempNode = "Siegehelp_0";

		break;
		
		case "attack_fort_03":
            if((sti(aData.iSquadronPower)*SquadronDamage - (ifortPower)*fortDamage) < 4000)
            {
                dialog.text = "Andererseits sind meine Schiffe in dieser Schlacht ziemlich beschädigt und Verstärkungen würden sicherlich nicht schaden. Wenn du zustimmst, "+GetPart(4)+", dann, schätze ich, könnten wir uns auf eine Vereinbarung einigen.";
                link.l1 = "Das passt mir, "+GetAddress_FormToNPC(NPChar)+". Ich werde versuchen, das Fort anzugreifen, und Sie werden uns mit dem Feuer Ihrer Schiffskanonen unterstützen.";
                link.l1.go = "attack_fort_04";
                aData.PartAttaksFort = 4;
                link.l2 = "Ich bin nicht so billig, "+GetAddress_FormToNPC(NPChar)+". Es tut mir leid für die Ablenkung"+GetSexPhrase("","")+" Sie von dringenden Angelegenheiten ab. Auf Wiedersehen!";
                link.l2.go = "exit";
            }else{
                dialog.text = "Es gibt genug Schiffe in meinem Geschwader, um diese Festung zu Staub zu reduzieren - es ist nur eine Frage der Zeit. Und jetzt, könnten Sie bitte mein Schiff verlassen? Der Sieg wartet auf mich!";
                link.l1 = "Nun, in diesem Fall, "+GetAddress_FormToNPC(NPChar)+", erlaube mir zu gehen. Lebewohl!";
                link.l1.go = "exit";
            }
		    Diag.TempNode = "Siegehelp_0";
		break;
		case "Big_part":
            if( (sti(aData.iSquadronPower)*SquadronDamage - (ifortPower)*fortDamage) <= -1500)
            {
                dialog.text = "Die Kanonen der Festung haben meine Schiffe schwer beschädigt, und wir könnten sicherlich die unterlegene Seite in der kommenden Schlacht sein. Ich akzeptiere Ihre Hilfe und stimme Ihren Bedingungen zu.";
                link.l1 = "Ausgezeichnet, "+GetAddress_FormToNPC(NPChar)+", in diesem Fall werden wir versuchen, das Fort anzugreifen, und Sie werden uns mit dem Feuer Ihrer Schiffskanonen unterstützen.";
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
					dialog.text = "Eure Exzellenz, ich muss noch über den Fortschritt der Operation berichten ... Lassen Sie uns zumindest "+GetPart(4)+".";
				}
				else
				{
                dialog.text = "Ist es nicht zu viel, Kapitän? Sie haben "+GetNumShips(GetCompanionQuantity(PChar))+", und mein Geschwader hat "+GetNumShips(Group_GetCharactersNum(sGroup))+". Ich kann Ihnen anbieten "+GetPart(4)+". Und betrachte es als fair.";
				}
                aData.PartAttaksFort = 4;
                link.l1 = "Ich stimme zu"+GetSexPhrase("","")+", "+GetAddress_FormToNPC(NPChar)+", in diesem Fall werde ich das Fort angreifen, und Sie werden uns mit dem Feuer Ihrer Schiffskanonen unterstützen.";
                link.l1.go = "attack_fort_04";
                link.l2 = "Leider glaube ich nicht, "+GetAddress_FormToNPC(NPChar)+". Es gibt nichts mehr zu besprechen. Lebewohl.";
                link.l2.go = "exit";
            }
            Diag.TempNode = "Siegehelp_0";
        break;
        
        case "attack_fort_04":
            dialog.text = "Sobald das Fort erobert ist, werden wir damit beginnen, Landungspartien am Ufer zu stationieren, und dann werden wir in der Stadt selbst weiterkämpfen, wo ich hoffe, Sie zu treffen.";
            link.l1 = "So sei es. Bis bald, "+GetAddress_FormToNPC(NPChar)+"!";
            link.l1.go = "exit";
            Diag.TempNode = "Siegehelp_0";
            PChar.quest.Union_with_Escadra = "Yes";
        break;

        case "Middle_part":
            if((sti(aData.iSquadronPower)*SquadronDamage - (ifortPower)*fortDamage) <= -600)
            {
                dialog.text = "Ich denke, ich werde Ihren Bedingungen zustimmen. Eine gemeinsame Operation wird meine Chancen erhöhen, diesen Kampf zu gewinnen. Wenn alles nach Plan läuft, erhalten Sie Ihren Anteil an der Beute.";
                link.l1 = "Es ist großartig, dass wir eine Vereinbarung getroffen haben, "+GetAddress_FormToNPC(NPChar)+". Ich werde meinen Männern sofort befehlen, das Fort anzugreifen.";
                link.l1.go = "attack_fort_04";
                aData.PartAttaksFort = 3;
            }else{
				// belamour legendary edition
				bOk1 = isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation);
				bOk2 = CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE;
				bOk = bOk1 || bOk2;
				if(bOk)
				{
					dialog.text = "Eure Exzellenz, ich muss immer noch über den Fortschritt der Operation berichten ... Lassen Sie uns zumindest "+GetPart(4)+".";
				}
				else
				{
                dialog.text = "Ist es nicht zu viel, Kapitän? Sie haben "+GetNumShips(GetCompanionQuantity(PChar))+", und meine Staffel hat "+GetNumShips(Group_GetCharactersNum(sGroup))+". Ich kann Ihnen anbieten "+GetPart(4)+". Und betrachte es als fair.";
				}
                link.l1 = "Ich "+GetSexPhrase("zustimmen","zustimmen")+", "+GetAddress_FormToNPC(NPChar)+", in diesem Fall werde ich das Fort angreifen, und du wirst uns mit dem Feuer deiner Schiffskanonen unterstützen.";
                link.l1.go = "attack_fort_04";
                aData.PartAttaksFort = 4;
                link.l2 = "Leider glaube ich nicht, "+GetAddress_FormToNPC(NPChar)+". Es gibt nichts mehr zu besprechen. Lebewohl.";
                link.l2.go = "exit";
            }
            Diag.TempNode = "Siegehelp_0";
        break;

        case "Small_part":
            dialog.text = "Meine Schiffe sind müde, und jede frische Kraft ist in dieser Situation willkommen. Ich nehme deine Hilfe an und stimme deinen Bedingungen zu.";
            link.l1 = "Ich bin froh"+GetSexPhrase("","")+", "+GetAddress_FormToNPC(NPChar)+".. Ich werde sofort meinen Männern befehlen, die Festung anzugreifen.";
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
            dialog.text = "Hallo, Kapitän! Das war sicherlich eine harte Schlacht, aber wir haben es geschafft, den wütenden Widerstand der Stadtbewahrer zu brechen. Wir haben geplündert "+sti(aData.loot)+" Pesos. Gemäß unserer Vereinbarung ist dein Anteil "+ilt+". Please accept this money; you certainly deserve every last coin of it. And now please excuse me, but I must return to my business.";
            link.l1 = "In diesem Fall werde ich dich verlassen, "+GetAddress_FormToNPC(NPChar)+". Lebewohl!";
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
            dialog.text = "Ahoi, Kapitän! Haben Sie Geschäfte mit mir?";
            link.l1 = "Nein, "+GetAddress_FormToNPC(NPChar)+". Auf Wiedersehen!";
            link.l1.go = "exit";
            Diag.TempNode = "no_return_02";
		break;
		
		case "GoldSquadron":
            ref rch = Group_GetGroupCommander("Sea_Head_of_Gold_Squadron");
            if (NPChar.id == rch.id)
            {
    			dialog.text = "Ich höre Ihnen zu, aber bitte seien Sie schnell mit dem Ziel Ihres Besuchs, ich habe nicht viel Zeit. Ich habe eine wichtige und geheime Mission, und ich bin auch angewiesen, alle verdächtigen Schiffe auf hoher See zu versenken, die eine Gefahr für unseren Konvoi darstellen könnten.";                          
                link.l1 = "In diesem Fall werde ich nicht mehr Ihrer Zeit in Anspruch nehmen. Viel Glück, "+GetAddress_FormToNPC(NPChar)+".";
                link.l1.go = "exit";

            }
            else
            {
                Dialog.text = "Ich bin nicht befugt, mit dir zu verhandeln. Sprich mit dem Kommandanten unserer Staffel. Sein Name ist "+GetFullName(rch)+", du kannst ihn auf "+XI_ConvertString(RealShips[sti(rch.Ship.Type)].BaseName)+" ''"+rch.Ship.Name+"''.";
                link.l1 = "Danke. Ich werde tun, wie du sagst.";
                link.l1.go = "exit";

            }
            Diag.TempNode = "GoldSquadron";
		break;
		
		case "WM_Captain":
			dialog.text = "Schön dich zu treffen, mein Name ist "+GetFullName(npchar)+". Also bist du gekommen, um uns zu helfen? In diesem Fall freue ich mich besonders, denn unsere aktuelle Situation ist in der Tat kritisch - wir sind allein an den Ufern einer unbewohnten Insel, das Schiff ist kaum seetüchtig, die Besatzung hat schwere Verluste erlitten...";
			link.l1 = "Wie ich gehört habe, hattest du einen Kampf mit Piraten, und dann gab es diesen Sturm...";
			link.l1.go = "WM_Captain_1";
			pchar.quest.DesIsland_Over.over = "yes";//снять прерывание
		break;
		
		case "WM_Captain_1":
			dialog.text = "Richtig. Mein Schiff wurde in der Schlacht schwer beschädigt - wir mussten sogar einem Enterangriff von diesen Piratenbastarden standhalten. Später hat uns ein Sturm erwischt... oh, ich will gar nicht daran denken. Wir wurden an dieses unfreundliche Ufer getrieben. Wir beteten einen ganzen Tag zur Heiligen Jungfrau, um uns vor dem Sturm zu retten und unsere Ankerketten ganz zu halten\nUnd hier sind wir. Wir reparieren unser Schiff seit einer Woche, aber sieh selbst: nur noch fünfzig Männer übrig und uns fehlen auch Holzplanken - und wo sollen wir die herkriegen? Aus dem Dschungel? Offensichtlich. Wir arbeiten jeden Tag hart und doch haben wir nur den fünften Teil des gesamten benötigten Materials\nMit solchen Schäden zu segeln, ist so gut wie Selbstmord. Jetzt siehst du, wie es uns hier ergeht, Kapitän...";
			link.l1 = "Ja... Deine Situation ist nicht beneidenswert. Lass uns überlegen, was wir unternehmen könnten und wie ich dir helfen kann.";
			link.l1.go = "WM_Captain_2";
		break;
		
		case "WM_Captain_2":
			dialog.text = "Eh, ich wünschte, wir hätten genug Planken und Segeltuch - in diesem Fall könnten wir unser Schiff in einer Woche reparieren\nKapitän, da Sie extra hierher gekommen sind, könnten Sie vielleicht den nächsten Hafen besuchen und die Materialien kaufen, die wir brauchen? Das würde unser Problem lösen. Machen Sie sich keine Sorgen um Münzen, ich werde alle Ausgaben kompensieren.";
			link.l1 = "Natürlich. Was genau müssen Sie liefern und wie viel?";
			link.l1.go = "WM_Captain_3";
		break;
		
		case "WM_Captain_3":
			pchar.questTemp.WPU.Escort.Planks = 300 + hrand(5)*10;
			pchar.questTemp.WPU.Escort.Sailcloth = 150 + hrand(10)*10;
			pchar.questTemp.WPU.Escort.Linen = 70 + hrand(7)*10;
			dialog.text = "Ich habe das alles schon herausgefunden. Angesichts dessen, was wir bereits haben, benötige ich "+FindRussianQtyString(sti(pchar.questTemp.WPU.Escort.Planks))+" Bretter, "+FindRussianQtyString(sti(pchar.questTemp.WPU.Escort.Sailcloth))+" Segeltuch und "+FindRussianQtyString(sti(pchar.questTemp.WPU.Escort.Linen))+" Baumwolle. Mit diesen Materialien könnten wir das Schiff in einer Woche reparieren und dann könnten wir in See stechen.";
			link.l1 = "Gut. Ich werde dir alle Materialien bringen, die du brauchst. Warte auf mich - Ich komme spätestens in zehn Tagen zurück.";
			link.l1.go = "WM_Captain_4";
		break;
		
		case "WM_Captain_4":
			dialog.text = "Vielen Dank, Kapitän! Das ist eine Last weniger auf meinem Geist. Wir werden warten und für Ihre erfolgreiche Rückkehr beten!";
			link.l1 = "Mach dir keine Sorgen. Bald wirst du alles haben, was du für die Reparatur brauchst.";
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
			dialog.text = "Wir werden sehnsüchtig auf Ihre Rückkehr warten, Kapitän!";
			link.l1 = "Anker lichten!";
			link.l1.go = "exit";
			Diag.TempNode = "WM_Captain_again";
		break;
		
		case "WM_Captain_5":
			dialog.text = "Ausgezeichnet! Jetzt können wir anfangen, das Schiff zu reparieren!";
			link.l1 = "Meine Männer werden dir helfen - auf diese Weise wird es schneller gehen. Außerdem muss ich dich zur Kolonie begleiten "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity)+", also je eher wir mit den Reparaturen fertig sind, desto besser für mich.";
			link.l1.go = "WM_Captain_6";
		break;
		
		case "WM_Captain_6":
			pchar.questTemp.WPU.Current.TargetIslandID.Shore = SelectQuestShoreLocationFromSea(pchar.questTemp.WPU.Current.TargetIslandID);
			dialog.text = "Wirklich, ich habe keine Ahnung, wie ich Ihnen gebührend danken soll, Kapitän... Bitte befehlen Sie, die Materialien in einer Bucht namens "+XI_ConvertString(pchar.questTemp.WPU.Current.TargetIslandID.Shore)+" - da haben wir alles bereit zur Reparatur.";
			link.l1 = "Gut. Wir treffen uns am Ufer.";
			link.l1.go = "exit";
			AddQuestRecord("Escort", "29");
			AddQuestUserData("Escort", "sShore", XI_ConvertString(pchar.questTemp.WPU.Current.TargetIslandID.Shore+"Gen"));
			pchar.quest.DisasterShip_WMC.win_condition.l1 = "location";
			pchar.quest.DisasterShip_WMC.win_condition.l1.location = pchar.questTemp.WPU.Current.TargetIslandID.Shore;
			pchar.quest.DisasterShip_WMC.function = "RepairShip_Prepare";
			Diag.TempNode = "WM_Captain_repeat";
		break;
		
		case "WM_Captain_repeat":
			dialog.text = "Wann beginnen wir mit der Reparatur, Kapitän? Ich werde auf dich am Ufer warten.";
			link.l1 = "Ja, natürlich. Ich gehe jetzt.";
			link.l1.go = "exit";
			Diag.TempNode = "WM_Captain_repeat";
		break;
		
		case "Repair_start":
			dialog.text = "Nun, alles scheint bereit für die Reparaturen zu sein. Ich denke, wir sollten in etwa fünf Tagen fertig sein.";
			link.l1 = "Sehr gut! Ich hatte sowieso vor, diese Insel zu erkunden, also werde ich diese Zeit gut nutzen.";
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
			dialog.text = "Nun, das war's. Wir sind fertig mit den Reparaturen und das Schiff ist bereit zum Auslaufen. Wann legen wir ab, Kapitän?";
			link.l1 = "Wenn du bereit bist, sehe ich keinen Grund, noch länger zu warten. Lichten wir den Anker!";
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
			dialog.text = "Ich möchte Ihnen noch einmal danken, Kapitän - Sie haben mir und meiner Mannschaft sehr geholfen, aus dieser Klemme herauszukommen. Wie versprochen, werde ich die Kosten für die zur Reparatur meines Schiffes benötigten Materialien übernehmen. Hier sind "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.LevelUp_1Money))+", bitte, nimm sie. Und das ist mein persönliches Geschenk an dich.";
			link.l1 = "Ich habe Ihnen gerne geholfen.";
			link.l1.go = "WMShip_final_1";
		break;
		
		case "WMShip_final_1":
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.WPU.Escort.LevelUp_1Money));
			TakeNItems(pchar, "obereg_"+(hrand(10)+1), 1);
			dialog.text = "Und nun ist es Zeit, Lebewohl zu sagen, Kapitän. Vergessen Sie nicht, die Hafenbehörde zu besuchen - dort wird auf Sie gewartet. Auf Wiedersehen!";
			link.l1 = "Hab einen schönen Tag, "+npchar.name+"!";
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
			dialog.text = "So ist es also? Und ich dachte, sie hätten uns vergessen. Ja, mein Schiff hat es am schlimmsten getroffen. Nachdem der Sturm die Piraten gezwungen hatte, unseren Karawanenangriff abzubrechen, wurden wir den Elementen der Natur überlassen. Wir wurden an dieses unwirtliche Ufer gespült\nVerbrachten ein paar Tage mit Reparaturen und Ruhe. Diese Heiden griffen uns wieder an, sobald wir absegeln wollten\nUnd dann hat uns der Sturm wieder erwischt - wir dachten, der Herr habe sich endlich dazu entschlossen, uns zu erledigen, aber du bist gekommen. Dank der Heiligen Maria! Danke nochmal, Kapitän!";
			link.l1 = "Es ist alles vorbei, "+GetAddress_FormToNPC(NPChar)+". Jetzt muss ich Sie begleiten zu "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen")+", um es vor weiteren möglichen Schwierigkeiten zu schützen. Sind Sie bereit, jetzt zu gehen? Der Sturm hat bereits nachgelassen.";
			link.l1.go = "VSP_Captain_1";
		break;
		
		case "VSP_Captain_1":
			dialog.text = "Aber natürlich! Je früher wir diesen Ort verlassen, desto ruhiger werden meine Männer sein - sie haben schon zu viel gelitten. Lass uns in See stechen!";
			link.l1 = "Folge einfach meinem Schiff - und beruhige deine Mannschaft, es gibt jetzt nichts mehr zu fürchten.";
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
			dialog.text = "Sollen wir in See stechen, Kapitän?";
			link.l1 = "Sicher. Ich kehre jetzt zu meinem Schiff zurück.";
			link.l1.go = "exit";
			Diag.TempNode = "VSP_Captain_again";
		break;
		
		case "VSPShip_final":
			pchar.quest.Escort_fail.over = "yes";
			pchar.quest.DisasterShipWM_Over.over = "yes";//снимаем оба прерывания
			RemoveCharacterCompanion(Pchar, characterFromID("WMCaptain"));//удаляем компаньона
			pchar.questTemp.WPU.Escort.LevelUp_1Money = 10000+sti(pchar.rank)*200;
			dialog.text = "Ich möchte Ihnen noch einmal danken, Kapitän - Sie haben mir und meiner Crew sehr geholfen, aus dieser Klemme herauszukommen. Hier sind"+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.LevelUp_1Money))+". Die gesamte Crew hat dazu beigetragen, also denke nicht einmal daran, es abzulehnen. Und das ist mein persönliches Geschenk an dich.";
			link.l1 = "Ich war froh, Ihnen helfen zu können!";
			link.l1.go = "WMShip_final_1";
		break;
		
		case "SShip_final":
			pchar.questTemp.WPU.Escort.LevelUp_1Money = 5000+sti(pchar.rank)*100;
			RemovePassenger(Pchar, npchar);//удаляем пассажира
			dialog.text = "Ich möchte Ihnen nochmals danken, Kapitän, dass Sie unsere Ärsche aus diesem Schlamassel gerettet haben. Hier, nehmen Sie diese Münzen - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.LevelUp_1Money))+"  und hier, nimm dieses Geschenk. Es ist nicht viel, aber das ist alles, was ich tun kann, um dir für das zu danken, was du getan hast. Bitte, lehne das Angebot nicht ab\nMeine ehemalige Crew ist von dir und deinem Kampf mit den Indianern und Piraten begeistert. Alle von ihnen möchten sich dir anschließen. Ich hoffe, du wirst den Antrag auf treue Dienste von Seeleuten, die gerade ihr Schiff verloren haben, nicht ablehnen?";
			link.l1 = "Natürlich nicht. Ich behalte es gerne. Ich habe dir gerne geholfen!";
			link.l1.go = "WMShip_final_1";
		break;
		
		//Голландский Гамбит
		case "Stivesant_1":
			DelLandQuestMark(npchar);
			dialog.text = "Gut. Aber, mein Herr, könnten Sie erklären, was hier vor sich geht? Wie kommt es, dass Sie das Kommando über die 'Meifeng' haben! Ist etwas mit Longway passiert?";
			link.l1 = "Ich habe alle Erklärungen, die du brauchst - und auch einige andere wichtige Informationen.";
			link.l1.go = "Stivesant_2";			
		break;
		
		case "Stivesant_2":
			dialog.text = "Dann bin ich ganz Ohr.";
			link.l1 = "Es gab einen Putsch in Willemstad. Lucas Rodenburg hat die Stelle des Gouverneurs eingenommen und Matthias Beck wegen des lächerlichen Verdachts, er hätte Verbindungen zum britischen Geheimdienst, ins Gefängnis gesteckt.";
			link.l1.go = "Stivesant_3";			
		break;
		
		case "Stivesant_3":
			dialog.text = "Hmm... Mynheer, die Dinge, die Sie mir erzählen, sind wirklich überraschend. Ich hatte vor nicht allzu langer Zeit Nachrichten aus Willemstad erhalten, und darin stand nichts dergleichen.";
			link.l1 = "Bitte hören Sie mir zu, Mynheer Stuyvesant. Sie müssen die Nachricht durch Rodenburg bekommen haben, und er muss sicher sein, dass Sie nicht nach Curacao kommen werden.";
			link.l1.go = "Stivesant_4";			
		break;
		
		case "Stivesant_4":
			dialog.text = "Herr, mir gefällt immer weniger, was Sie sagen. Wer sind Sie überhaupt?";
			link.l1 = "Ich bin nur ein Kapitän und nur ein Mann, der nicht gleichgültig gegenüber dem Schicksal der holländischen Kolonisten ist. Lucas Rodenburg hat Longway befohlen, dein Schiff zu zerstören und dich auch zu töten. Und da 'Meifeng' bei dir keinen Verdacht erregen würde, hätte er es ohne jede Anstrengung ausgeführt.";
			link.l1.go = "Stivesant_5";			
		break;
		
		case "Stivesant_5":
			dialog.text = "Also, du meinst, dass Lucas...";
			link.l1 = "Entschieden, dich auf einfachste Weise von der Macht zu entfernen - indem wir dich einfach beseitigen. Abgesehen von dir gibt es keine andere Person in der Region, die dem Einfluss Rodenburgs auf den Archipel nennenswerten Widerstand leisten könnte.";
			link.l1.go = "Stivesant_6";			
		break;
		
		case "Stivesant_6":
			dialog.text = "Ich kann es nicht glauben!";
			link.l1 = "Ich bin nicht auf diesen Mist mit Beck hereingefallen, der mit dem englischen Geheimdienst in Verbindung steht, und habe meine eigene Untersuchung durchgeführt. Ich fand heraus, dass 'Meifeng', beladen mit ausgewählten Cutthroats, nach Philipsburg aufgebrochen ist. Ich habe sie verfolgt und ihnen Schlacht geliefert. Longway wurde gefangen genommen, und er gab mir all diese Informationen, einschließlich deines Aufenthaltsortes.";
			link.l1.go = "Stivesant_7";			
		break;
		
		case "Stivesant_7":
			dialog.text = "Hm... Das scheint wahrscheinlich. Niemand, außer Rodenburg, wusste oder könnte über meinen Zeitplan und Route Bescheid wissen! Verdammt! Das ist Verrat! Wo ist Longway?!";
			link.l1 = "Ich habe ihn im Austausch für sein freiwilliges Geständnis freigelassen. Ich muss sagen, er war nicht allzu begierig, Rodenburgs Befehl auszuführen, aber er konnte ihn auch nicht ignorieren. Er sagte auch, dass er nicht in Rodenburgs Dienst zurückkehren würde - diese letzte schmutzige Affäre brachte sein Fass zum Überlaufen.";
			link.l1.go = "Stivesant_8";			
		break;
		
		case "Stivesant_8":
			dialog.text = "In Ordnung... Kapitän "+GetFullName(pchar)+", du wirst mit mir nach Willemstad fahren. Du wirst auf 'Meifeng' vor meinem Schiff segeln. Wenn das, was du gesagt hast, wahr ist, muss Lucas verhaftet werden, und du wirst dabei helfen. Aber wenn du mich angelogen hast... Du hast nur dich selbst zu beschuldigen.";
			link.l1 = "Für mich gibt es keinen Grund, Ihnen zu lügen, mein Herr. Lassen Sie uns uns beeilen!";
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
			dialog.text = "Kapitän, geh zu 'Meifeng'. Es ist Zeit für uns, in See zu stechen.";
			link.l1 = "Ja, Mynheer, natürlich.";
			link.l1.go = "exit";
			Diag.TempNode = "Stivesant_10";
		break;
		
		case "Keller_1":
			dialog.text = "Sehr interessant! Bitte, erzähl mir deine Geschichte. Ich werde versuchen, mein Bestes zu tun, um zu helfen.";
			link.l1 = "Herr Keller, erinnern Sie sich, wie Sie vor einigen Monaten auf dem Weg nach Willemstad eine Flöte getroffen haben. An Bord war eine Familie jüdischer Flüchtlinge. Sie haben an Bord dieses Schiffes diniert und dann Ihre Reise fortgesetzt.";
			link.l1.go = "Keller_2";
		break;
		
		case "Keller_2":
			dialog.text = "Ja, ich denke schon... Ja, ich erinnere mich jetzt ganz klar daran. Also, was ist der Deal?";
			link.l1 = "Die Flöte wurde an jenem Tag von Piraten versenkt. Nur zwei Flüchtlinge konnten sich retten - Salomon und seine Tochter Abigail. Sie fanden Zuflucht auf einer Insel, nur wenige Meilen entfernt von dem Ort des Angriffs. Ich muss diese Insel finden. Könnten Sie sich bitte daran erinnern, wo Sie diese Flöte getroffen haben? Das ist sehr wichtig.";
			link.l1.go = "Keller_3";
		break;
		
		case "Keller_3":
			dialog.text = "Und das ist alles, was du brauchst? Ich kenne diese Insel. Sie liegt ganz in der Nähe, zwischen Trinidad und Curacao. Eine kleine, unbewohnte Wüsteninsel. Dort gibt es nicht einmal Indianer.";
			link.l1 = "Und kennen Sie die ungefähren Koordinaten?";
			link.l1.go = "Keller_4";
		break;
		
		case "Keller_4":
			dialog.text = "Ich kann Ihnen die genauen Koordinaten geben. Es liegt bei 12  48'  Nord und 64  41'  West. Suchen Sie dort. Die Insel ist ziemlich klein, aber Sie sollten sie leicht finden können.";
			link.l1 = "Danke, mein Herr Keller! Sie haben mir sehr geholfen. Auf Wiedersehen.";
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
			dialog.text = "Brauchten Sie noch etwas, Kapitän?";
			link.l1 = "Nein, danke. Ich war bereits auf dem Weg zurück zu meinem Schiff.";
			link.l1.go = "exit";
			Diag.TempNode = "Keller_6";
		break;
		
		// belamour рыбацкое судно -->
		case "FishingBoat":
			pchar.GenQuest.FishingBoatSecondTime = true;
			dialog.text = "Nichts Besonderes, das ist ein Fischerboot, wir fangen hier Fische. Man muss sich irgendwie durchschlagen.";
			link.l1 = "Ja, ich stimme zu, das sind die Zeiten...";
			link.l1.go = "FishingBoat_1";			
		break;
		
		case "FishingBoat_1":
			Diag.TempNode = "FishingBoat_1";
			dialog.text = "Also, was willst du?";
			link.l1 = "Ich wollte"+GetSexPhrase("","")+", um die neuesten Nachrichten aus dem Archipel zu erfahren.";
            link.l1.go = "rumours_capitan";
			link.l2 = "Wie sind Ihre Fänge heute? Können Sie verkaufen? Vorräte würden mir nicht schaden...";
			link.l2.go = "FishingBoat_2";
			link.l3 = "Nichts Besonderes, bin nur zum Grüßen gekommen!";
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
				
				dialog.text = "Der Fang ist heute gut, wir haben gerade genug Zeit, die Netze einzuholen. Wir können es Ihnen sogar billiger verkaufen als im Laden - wir verkaufen den Fisch sowieso an einen lokalen Händler. Wenn wir das alles in Proviant umrechnen... Wir haben jetzt "+iTemp+" davon können wir es zu einem Preis von "+iMoney+" Pesos pro Stück. Wie viele nimmst du?";
				link.l1.edit = 3;
				link.l1 = "";	
				link.l1.go = "Количество вбитого провианта";
				link.l2 = "Weißt du, ich habe meine Meinung geändert, deine Vorräte zu kaufen.";	
				link.l2.go = "exit";
				
			}
			if(GetDataDay() > 10 && GetDataDay() < 21) 
			{
				Diag.TempNode = "FishingBoat_1";
				dialog.text = "Ja, etwas, um ehrlich zu sein, gibt es überhaupt keine Fische ... Heute wurde fast nichts gefangen. Aber die Harpunen blieben überflüssig - sie dachten, sie würden einen großen Fisch oder einen Wal fangen, wenn Sie Glück hätten ... Brauchen Sie vielleicht Harpunen?";
				link.l1 = "Nein, ich habe kein Interesse an Harpunen.";
				link.l1.go = "exit";
				link.l2 = "Hmm, ein Harpun ist auch in den richtigen Händen ein nützliches Ding. Ich werde wahrscheinlich kaufen.";
				link.l2.go = "Гарпуны";
			}
			if(GetDataDay() > 20)
			{
				dialog.text = "Ja, etwas, um ehrlich zu sein, gibt es überhaupt keine Fische ... Heute wurde fast nichts gefangen. Also gibt es nicht viel zu verkaufen. Es sei denn ... Ich habe ein paar Krimskrams, vielleicht wird Sie etwas interessieren. Möchten Sie sehen?";
				link.l1 = "Nein, ich bin nicht an Krimskrams interessiert.";
				link.l1.go = "exit";
				link.l2 = "Es ist schade, dass es keinen Fang gibt. Nun, lass uns wenigstens deine Kinkerlitzchen ansehen - plötzlich wird etwas anziehen ...";
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
				dialog.text = "Du verlangst zu viel... Ich habe nicht so viel! Könntest du weniger kaufen?";
				link.l1.edit = 3;
				link.l1 = "";	
				link.l1.go = "Количество вбитого провианта повтор";	
				link.l2 = "Weißt du, ich habe meine Meinung geändert über den Kauf deiner Vorräte.";	
				link.l2.go = "exit";
			}	
			if(iQty < 1)
			{
				dialog.text = "Machst du Witze mit mir? Brauchst du Proviant oder nicht? Wenn ja, wie viel?";
				link.l1.edit = 3;
				link.l1 = "";	
				link.l1.go = "Количество вбитого провианта повтор";	
				link.l2 = "Weißt du, ich habe meine Meinung geändert, deine Vorräte zu kaufen.";	
				link.l2.go = "exit";
			}
			if(iQty > 0 && iQty <= iTemp)
			{
				dialog.text = "Abgemacht! "+sti(iQty*iMoney)+" Pesos.";
				if(sti(pchar.money) < iQty*iMoney)
				{
					link.l1 = "Hmm, ich habe nicht so viel Geld. Ein anderes Mal.";
					link.l1.go = "exit";
				}
				else
				{
					link.l1 = "Abgemacht! Schleppt die Ware zu meinem Schiff.";
					link.l1.go = "Удачная покупка";
					link.l2 = "Sie wissen, ich habe meine Meinung über den Kauf Ihrer Vorräte geändert.";
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
				dialog.text = "Du verlangst zu viel... Ich habe nicht so viel! Könntest du weniger kaufen?";
				link.l1.edit = 3;
				link.l1 = "";	
				link.l1.go = "Количество вбитого провианта";	
				link.l2 = "Sie wissen, ich habe meine Meinung geändert, Ihre Vorräte zu kaufen.";	
				link.l2.go = "exit";
			}	
			if(iQty < 1)
			{
				dialog.text = "Machst du Witze? Brauchst du Vorräte oder nicht? Wenn ja, wie viel?";
				link.l1.edit = 3;
				link.l1 = "";	
				link.l1.go = "Количество вбитого провианта";	
				link.l2 = "Weißt du, ich habe meine Meinung geändert, deine Vorräte zu kaufen.";	
				link.l2.go = "exit";
			}
			if(iQty > 0 && iQty <= iTemp)
			{
				dialog.text = "Abgemacht! "+sti(iQty*iMoney)+" Pesos.";
				if(sti(pchar.money) < iQty*iMoney)
				{
					link.l1 = "Hmm, ich habe nicht so viel Geld. Ein anderes Mal.";
					link.l1.go = "exit";
				}
				else
				{
					link.l1 = "Abgemacht! Schleppe die Waren zu meinem Schiff.";
					link.l1.go = "Удачная покупка";
					link.l2 = "Sie wissen, ich habe meine Meinung über den Kauf Ihrer Verpflegung geändert.";
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
				dialog.text = "Wir haben "+iTemp+" Stücke. Wir können für hundert Pesos einen Harpunen verkaufen. Wie viel brauchst du?";
				link.l1.edit = 3;
				link.l1 = "";	
				link.l1.go = "Количество вбитых гарпунов";
				link.l2 = "Weißt du, ich habe meine Meinung geändert, ich brauche die Harpunen nicht.";	
				link.l2.go = "exit";
		break;
		
		case "Количество вбитых гарпунов":
   
			iQty = sti(dialogEditStrings[3]);
			iTemp = makeint(pchar.GenQuest.FishingBoatITemp);
			pchar.GenQuest.FishingBoatIQty = iQty;
			Diag.TempNode = "FishingBoat_1";
			if(iQty > iTemp)
			{
				dialog.text = "Du bist zu viel... Ich habe nicht so viel! Kannst du weniger kaufen?";
				link.l1.edit = 3;
				link.l1 = "";	
				link.l1.go = "Количество вбитых гарпунов заново";	
				link.l2 = "Weißt du, ich habe meine Meinung geändert, ich brauche die Harpunen nicht.";	
				link.l2.go = "exit";
			}	
			if(iQty < 1)
			{
				dialog.text = "Willst du mich veräppeln? Brauchst du Harpunen oder nicht? Wenn ja, wie viele?";
				link.l1.edit = 3;
				link.l1 = "";	
				link.l1.go = "Количество вбитых гарпунов заново";	
				link.l2 = "Weißt du, ich habe meine Meinung geändert, ich brauche die Harpunen nicht.";	
				link.l2.go = "exit";
			}
			if(iQty > 0 && iQty <= iTemp)
			{
				dialog.text = "Abgemacht! "+sti(iQty*100)+" Pesos.";
				if(sti(pchar.money) < iQty*100)
				{
					link.l1 = "Hmm, ich habe nicht so viel Geld. Ein andermal.";
					link.l1.go = "exit";
				}
				else
				{
					link.l1 = "Abgemacht! Ich werde eine Verwendung für sie finden.";
					link.l1.go = "Удачная покупка гарпунов";
					link.l2 = "Weißt du, ich habe meine Meinung geändert, ich brauche die Harpunen nicht.";
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
				dialog.text = "Du verlangst zu viel... Ich habe nicht so viel! Könntest du weniger kaufen?";
				link.l1.edit = 3;
				link.l1 = "";	
				link.l1.go = "Количество вбитых гарпунов";	
				link.l2 = "Weißt du, ich habe es mir anders überlegt, ich brauche die Harpunen nicht.";	
				link.l2.go = "exit";
			}	
			if(iQty < 1)
			{
				dialog.text = "Scherzt du? Brauchst du Harpunen oder nicht? Wenn ja, wie viele?";
				link.l1.edit = 3;
				link.l1 = "";	
				link.l1.go = "Количество вбитых гарпунов";	
				link.l2 = "Weißt du, ich habe es mir anders überlegt, ich brauche die Harpunen nicht.";	
				link.l2.go = "exit";
			}
			if(iQty > 0 && iQty <= iTemp)
			{
				dialog.text = "Abgemacht! "+sti(iQty*100)+" Pesos.";
				if(sti(pchar.money) < iQty*100)
				{
					link.l1 = "Hmm, ich habe nicht so viel Geld. Ein andermal.";
					link.l1.go = "exit";
				}
				else
				{
					link.l1 = "Abgemacht! Ich werde eine Verwendung für sie finden.";
					link.l1.go = "Удачная покупка гарпунов";
					link.l2 = "Weißt du, ich habe es mir anders überlegt, ich brauche die Harpunen nicht.";
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
				dialog.text = "Nein, es gibt nichts anderes. Es ist ein Fischerboot! Was könnte hier sonst sein?";
				link.l1 = "Gut, ich verstehe.";
				link.l1.go = "exit";
			}
			else if(hrand(2, "&SpeGoo") == 1)
			{
				if(ChangeContrabandRelation(pchar, 0) > 5)
				{
					
					dialog.text = "Nun ... Ich habe hier eine kleine Sache ... Ich habe sie aufbewahrt, dachte daran, sie an jemanden zu verkaufen. Aber ich werde viel dafür verlangen! Und ich werde kein zweites Mal anbieten. Willst du schauen?";
					link.l1 = "Zeig mir, lass uns sehen, was für eine Kleinigkeit du bist.";
					link.l1.go = "Особые товары предметы";
				}
				else
				{
					Diag.TempNode = "First time";
					Diag.CurrentNode = "First time";
					pchar.GenQuest.FishingBoatDialogEnb = "no special goods";
					dialog.text = "Nein, es gibt nichts anderes. Es ist ein Fischerboot! Was könnte hier sonst sein?";
					link.l1 = "Gut, ich verstehe. ";
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
					
					dialog.text = "Nun ... Ich habe hier einen guten ... Rein zufällig habe ich ihn am Ufer der Bucht gefunden. Es ist "+iQty+" "+sTemp+". Der Preis pro Stück beträgt "+iMoney+". Aber ich werde alles auf einmal verkaufen und kein zweites Mal anbieten. Und damit kein Außenstehender davon erfährt ... verstehen Sie?";
					link.l1 = "Nein, ich will die fragwürdigen Waren nicht, danke. Ich werde es niemandem sagen, mach dir keine Sorgen.";
					link.l1.go = "exit";
					if(sti(pchar.money) >= iMoney*iQty)
					{
						link.l2 = "Ich verstehe dich. Aber die Waren sind es wert. Ich nehme sie. Lass sie zu meinem Schiff liefern.";
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
				dialog.text = "Es ist "+GetConvertStr("itmname_"+sTemp,"ItemsBeschreiben.txt")+". Hat es geschafft zu bekommen ... nun, egal woher. Dachte, es an einen Kenner zu verkaufen. Ich gebe es Ihnen für nur 10.000 Pesos! Nehmen Sie es?";
				if(sti(pchar.money) > 9999)
				{
					link.l1 = "Ich nehme es natürlich! Das Ding steht. ";
					link.l1.go = "Купили особый товар";
				}
				link.l2 = "Nein, ich brauche es nicht. Ich werde es nicht nehmen. ";
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
