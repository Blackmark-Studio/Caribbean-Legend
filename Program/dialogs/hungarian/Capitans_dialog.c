// разговор с капитаном на палубе  Boal
//homo 25/06/06
#include "DIALOGS\%language%\Rumours\Common_rumours.c"

int iEncPow = -1;
int iCapBattleDifficulty = -1; // Действует, пока не выгружен этот диалог

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
            case 0:  fort = "Angol erôd"; break;
            case 1:  fort = "Francia erôd"; break;
            case 2:  fort = "Spanyol erôd"; break;
            case 3:  fort = "Holland erôd"; break;
            case 4:  fort = "Kalóz erôd"; break;
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
					dialog.text = "Helló, kapitány. Az istenit, fogalmad sincs, mennyire örülök, hogy látlak!";
					link.l1 = "Szia. Engedd meg, hogy bemutatkozzam - " + GetFullName(PChar) + ". Örülök, hogy téged is élve és virulva látlak, kifejezetten azért jöttem ide, hogy megkeresselek - és a hajódat.";
					link.l1.go = "WM_Captain";
					break;
				}
				if (CheckAttribute(PChar, "questTemp.WPU.Escort.LevelUp_1WM") && pchar.questTemp.WPU.Escort == "wait" && NPChar.id == "WMCaptain")
				{
					dialog.text = "Elhoztad az anyagot, amit kértem?";
					if (sti(pchar.questTemp.WPU.Escort.Planks) - GetSquadronGoods(pchar, GOOD_PLANKS) <= 0 && sti(pchar.questTemp.WPU.Escort.Sailcloth) - GetSquadronGoods(pchar, GOOD_SAILCLOTH) <= 0 && sti(pchar.questTemp.WPU.Escort.Linen) - GetSquadronGoods(pchar, GOOD_COTTON) <= 0)
					{
						link.l1 = "Igen. Minden, amire szüksége van a hajója megjavításához, a raktáramban van.";
						link.l1.go = "WM_Captain_5";
					}
					else
					{
						link.l1 = "Nem, még dolgozom rajta.";
						link.l1.go = "exit";
					}
					break;
				}
				if (CheckAttribute(PChar, "questTemp.WPU.Escort.LevelUp_1VSP") && pchar.questTemp.WPU.Escort == "toCap" && NPChar.id == "WMCaptain")
				{
					dialog.text = "Ahoy, " + GetAddress_Form(NPChar) + ". A nevem " + GetFullName(NPChar) + ", én vagyok a hajó kapitánya. Engedjék meg, hogy kifejezzem ôszinte hálámat a segítségükért a harcban ezzel az átkozott kalóz söpredékkel - ha nem avatkoznak közbe, a dolgok elég zordan alakulhattak volna számunkra. Te tényleg megmentettél minket, az istenit!";
					link.l1 = "Semmiség volt,  " + GetAddress_FormToNPC(NPChar) + ". Engedje meg, hogy bemutatkozzam - " + GetFullName(PChar) + ", a kikötômester "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen")+"kérésére jöttem önhöz. Ô tájékoztatott a karavánotok balszerencséjérôl, és elküldött, hogy keressem meg a hajótokat.";
					link.l1.go = "VSP_Captain";
					break;
				}
				//<-- эскорт 2 уровень
				
				if(CheckAttribute(NPChar, "surrendered"))
				{
					CalcBattleDifficulty();
                    if(iEncPow == -1) iEncPow = 0;
					Pchar.GenQuest.MoneyForCaptureShip = (70 + hrand(60, "&CapSur"+NPChar.id)) * iEncPow;
					if(HasShipTrait(pchar, "trait14")) Pchar.GenQuest.MoneyForCaptureShip = makeint(sti(Pchar.GenQuest.MoneyForCaptureShip) * 1.35);
					dialog.text = "Várj, lehet, hogy így megölsz. Mit akarsz tôlem?";
					//выкуп
					link.l1 = "Oldjuk meg ezt az ügyet békésen. A váltságdíj, azt hiszem, a legjobb döntés lesz. Egy "+Pchar.GenQuest.MoneyForCaptureShip+" pezó összeg nekem megfelel, "+GetAddress_FormToNPC(NPChar)+". És utána eltûnhetsz!";
					link.l1.go = "surrender1";
					// обираем до нитки
					link.l2 = "Szeretném látni, hogy mit tart a kezében. És utána maga és a legénysége mehet, ahová csak akar.";
					link.l2.go = "surrender2";
					break;
				}
				
				//Голландский Гамбит, против всех
				if (CheckAttribute(PChar, "questTemp.HWIC.Self") && pchar.questTemp.HWIC.Self == "MeetingStivesant" && NPChar.id == "Stivesant")
				{
					dialog.text = "Hello, mynheer. Örülök, hogy látlak. Longway kapitány valószínûleg késôbb jön a fedélzetre, igaz?";
					link.l1 = "Jó napot, mynheer Stuyvesant. Engedje meg, hogy bemutatkozzam - " + GetFullName(pchar) + ". Longway nem fog jönni, ô nem 'Meifeng'..";
					link.l1.go = "Stivesant_1";
					pchar.quest.QuestShipsTerms_Over.over = "yes"; //снять таймер
					break;
				}
				if (CheckAttribute(PChar, "questTemp.HWIC.Self") && pchar.questTemp.HWIC.Self == "FleutOnTrinidad" && NPChar.id == "Keller")
				{
					DelLandQuestMark(npchar);
					dialog.text = "Ahoy, kapitány. Mi szél hozta a fuvolámhoz?";
					link.l1 = "Jó napot, mynheer Keller. Engedje meg, hogy bemutatkozzam - " + GetFullName(pchar) + ". A segítségét kérem egy szokatlan ügyben.";
					link.l1.go = "Keller_1";
					break;
					//Голландский гамбит
				}
				// belamour рыбацкое судно -->
				if(npchar.id == "FishingBoatCap")
				{
					if(!CheckAttribute(pchar, "GenQuest.FishingBoatSecondTime"))
					{
						Dialog.text = TimeGreeting() + ", "+ GetAddress_Form(NPChar)+"! Én vagyok a "+ GetFullName(NPChar) +"kapitánya . Mi szél hozott a hajóm fedélzetére?";
						link.l1 = "Jó napot kívánok. Mit keres ebben az öbölben?";
						link.l1.go = "FishingBoat";
						break;
					}
					else
					{
						Diag.CurrentNode = "first time";
						dialog.text = "Szeretne még valamit megbeszélni?";
						link.l1 = "A"+ GetSexPhrase("","") +" akartam megtudni a legfrissebb híreket a szigetvilágból.";
						link.l1.go = "rumours_capitan";
						if(CheckAttribute(pchar,"GenQuest.FishingBoatDialogEnb"))
						{
							link.l2 = "Mutasd meg még egyszer, kérlek, milyen csecsebecséket árulsz. ";
							link.l2.go = "Торговля";
							if(pchar.GenQuest.FishingBoatDialogEnb != "no special goods")
							{
								link.l3 = "Hmm, talán nézzünk szét a raktérben - talán találunk valamit eladásra?";
								link.l3.go = "Особые товары";
							}
						}
						link.l4 = "Semmi különös, csak üdvözölni jöttem!";
						link.l4.go = "exit";	
						break;
					}
				}
				// <-- рыбацкое судно
				
				//belamour legendary edition диалоги, если герой имеет звания и заслуги перед отечеством -->
				// генерал губернатор
				if(CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE)
				{
					Dialog.text = "Fôkormányzó úr, kegyelmes uram, üdvözletem! Mit tehetek önért?";
					link.l1 = "Üzleti ügyben jöttem!";
					link.l1.go = "quests";
					link.l2 = "Semmi különös, csak üdvözölni jöttem!";
					link.l2.go = "exit";
					break;
				}
				// вице адмирал
				if(isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && sti(Items[sti(pchar.EquipedPatentId)].Nation) == npchar.nation)
				{
					Dialog.text = "Üdvözlöm a hajóm fedélzetén, admirális-helyettes! Mit tehetek önért?";
					link.l1 = "Üzleti ügyben jöttem!";
					link.l1.go = "quests";
					link.l2 = "Semmi különös, csak üdvözölni jöttem!";
					link.l2.go = "exit";
					break;
				}
				// Офицер с патентом
				if(IsOfficerFullEquip() && sti(Items[sti(pchar.EquipedPatentId)].Nation) == npchar.nation)
				{
					Dialog.text = "Örülök, hogy látok egy munkatársat, kapitány! Miben segíthetek?";
					link.l1 = "Üzleti ügyben jöttem!";
					link.l1.go = "quests";
					link.l2 = "Semmi különös, csak üdvözölni jöttem!";
					link.l2.go = "exit";
					break;
				}			
				// <-- legendary edition
                if (CheckAttribute(NPChar, "EncType")  && NPChar.EncType == "war")
                {
    			    Dialog.text = TimeGreeting() + ", "+ GetAddress_Form(NPChar)+"! Én vagyok "+ GetFullName(NPChar) +" - a "+NationKingsName(NPChar)+". flottához tartozó hajó kapitánya. Mi hozta önt a hajóm fedélzetére?";
    			}
    			else
                {
    			    Dialog.text = TimeGreeting() + ", "+ GetAddress_Form(NPChar)+"! Kapitány vagyok "+ GetFullName(NPChar) +". Mi szél hozott a hajómra?";
    			}
    			link.l1 = "A nevem " + GetFullName(Pchar) + ". Van egy kis üzletem az Ön számára!";
    			link.l1.go = "quests";
                link.l2 = "Ó, semmi, csak "+ GetSexPhrase("jött","jött") +" köszönteni!";
    			link.l2.go = "exit";
            }
            else
            {
                Dialog.text = "Nem vetted észre, , " + GetAddress_Form(NPChar) + ", hogy csatában vagyunk? Nincs idô a beszélgetésre!";
    			link.l1 = "Teljesen egyetértek! Visszatérek a hajómra.";
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
					Dialog.text = TimeGreeting() + ", "+ GetAddress_Form(NPChar)+"! Én vagyok a "+ GetFullName(NPChar) +"kapitánya . Mi szél hozott a hajóm fedélzetére?";
					link.l1 = "Jó napot kívánok. Mit keres ebben az öbölben?";
					link.l1.go = "FishingBoat";
					break;
				}
				else
				{
					dialog.text = "Szeretne még valamit megbeszélni?";
					link.l1 = "A"+ GetSexPhrase("","") +" akartam megtudni a legfrissebb híreket a szigetvilágból.";
					link.l1.go = "rumours_capitan";
					if(CheckAttribute(pchar,"GenQuest.FishingBoatDialogEnb"))
					{
						link.l2 = "Mutasd meg még egyszer, kérlek, milyen csecsebecséket árulsz. ";
						link.l2.go = "Торговля";
						if(pchar.GenQuest.FishingBoatDialogEnb != "no special goods")
						{
							link.l3 = "Hmm, talán nézzünk szét a raktérben - talán találunk valamit eladásra?";
							link.l3.go = "Особые товары";
						}
					}
					link.l4 = "Semmi különös, csak üdvözölni jöttem!";
					link.l4.go = "exit";	
					break;
				}
			}
			// <-- рыбацкое судно
            if (!CheckAttribute(NPChar, "MainCaptanId")  || NPChar.MainCaptanId == pchar.GenQuest.CaptainId)
            {
                Dialog.text = "Nagyon figyelmesen hallgatlak,  " + GetAddress_Form(NPChar)+".";
                link.l1 = "Tudni akarom a legfrissebb híreket a szigetvilágról.";
                //homo 25/06/06
                link.l1.go = "rumours_capitan";
                //belamour legendary edition 
				bOk1 = isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && GetNationRelation(npchar.nation, sti(Items[sti(pchar.EquipedPatentId)].Nation)) != RELATION_ENEMY;
				bOk2 = CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && GetNationRelation(npchar.nation, FRANCE) != RELATION_ENEMY;
				bOk = bOk1 || bOk2;
                if (CheckAttribute(NPChar, "EncGroupName") && !bOk) // только для фантомов грабеж
                {
                    iCapBattleDifficulty = CalcBattleDifficulty();
                    link.l2 = "(Шанс " + iCapBattleDifficulty + "%%) " + RandPhraseSimple("Van fogalma arról, hogy ki vagyok? Azt hiszem, teljesen világos, hogy a fegyvereim szitává változtathatják az öreg kádadat. Oldjuk meg ezt békésen. A váltságdíj számomra jó döntés.",
                                               "Csak mi... és a tenger... Mit gondolsz arról, hogy az embereimet lecsillapítod... a saját biztonságod érdekében?");
                    link.l2.go = "Talk_board";
                }
                if (CheckAttribute(NPChar, "Ship.Mode") && NPChar.Ship.Mode == "Trade")
                {
	           		link.l3 = "Honnan jöttél?";
	    			link.l3.go = "price_1";
	    			link.l4 = "Akarsz kereskedni?";
	    			link.l4.go = "Trade_1";
    			}
				//--> квест мэра, поиски пирата
				if (CheckAttribute(pchar, "GenQuest.DestroyPirate"))
				{
	    			link.l6 = "Egy kalózhajót keresek, ami ezeken a vizeken tevékenykedik. Láttál valami gyanúsat?";
	    			link.l6.go = "MQ_step_1";
				}
				//<-- квест мэра, поиски пирата
    			link.l5 = "Akarsz pihenni?";
			    link.l5.go = "Play_Game";
                link.l9 = "Azt hiszem, mennem kell.";
    			link.l9.go = "exit";
			}
			else
			{
                Dialog.text = "Nem vagyok felhatalmazva, hogy magával foglalkozzak. Beszéljen az osztagunk parancsnokával. A neve  " + GetFullName(characterFromID(NPChar.MainCaptanId))+
                              ", megtalálod ôt a " + XI_ConvertString(RealShips[sti(characters[GetCharacterIndex(NPChar.MainCaptanId)].Ship.Type)].BaseName) + " '" + characters[GetCharacterIndex(NPChar.MainCaptanId)].Ship.Name + "'oldalon.";
                link.l1 = "Köszönöm. Köszönöm. Azt teszem, amit mond.";
                link.l1.go = "exit";
                Diag.TempNode = "Go_away_Good";
			}
        break;
        case "Trade_1":
			dialog.text = "Miért ne?";
			link.l1 = "Nézzük meg az árut.";
			link.l1.go = "Trade_2";
			link.l2 = "Meggondoltam magam.";
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
			dialog.text = "Mit javasolsz?";
			link.l1 = "Akarsz kártyázni egy kis pénzért?";
			link.l1.go = "Card_Game";
   			link.l2 = "Mit szólnál egy kis kockadobáshoz póker-jokerben?";
			link.l2.go = "Dice_Game";
			link.l10 = "Sajnálom, de dolgom van.";
			link.l10.go = "exit";
		break;
        // карты -->
        case "Card_Game":
            if (!CheckNPCQuestDate(npchar, "Card_date_Yet") || isBadReputation(pchar, 30) || GetCharacterSkillToOld(pchar, SKILL_LEADERSHIP) < rand(3))
            {
                SetNPCQuestDate(npchar, "Card_date_Yet");
                dialog.text = "Nem fogok csalókkal játszani!";
    			link.l1 = "Ahogy óhajtja.";
    			link.l1.go = "exit";
			}
			else
			{
                dialog.text = "Miért ne? Nem bánnám, ha szünetet tarthatnék...";
    			link.l1 = "Kiváló.";
    			link.l1.go = "Cards_begin";
    			link.l2 = "Mik a szabályok?";
    			link.l2.go = "Cards_Rule";
			}
		break;

		case "Cards_Rule":
   			dialog.text = CARDS_RULE;
			link.l1 = "Nos, akkor kezdjük el!";
			link.l1.go = "Cards_begin";
			link.l3 = "Nem, ez nem nekem való...";
			link.l3.go = "exit";
		break;

		case "Cards_begin":
			Dialog.text = "Elôször is, egyezzünk meg a fogadásról.";
			link.l1 = "Játsszunk 100 pezóért.";
			link.l1.go = "Cards_Node_100";
			link.l2 = "Játsszunk 500 pezóért.";
			link.l2.go = "Cards_Node_500";
			link.l3 = "Azt hiszem, mennem kell.";
			link.l3.go = "exit";
		break;

		case "Cards_Node_100":
		    if (sti(pchar.Money) < 300)
		    {
                dialog.text = "Most viccelsz, vagy mi? Nincs pénzed!";
                link.l1 = "Megtörténik.";
			    link.l1.go = "exit";
			    break;
		    }
		    if (sti(npchar.Money) < 300)
		    {
                dialog.text = "Nos, ennyi elég, különben nem lesz elég pénzem a hajó fenntartására...";
                link.l1 = "Kár.";
			    link.l1.go = "exit";
			    break;
		    }
   			dialog.text = "Rendben, játsszunk 100 érméért.";
			link.l1 = "Kezdjük el!";
			link.l1.go = "Cards_begin_go";
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
            pchar.GenQuest.Cards.iRate     = 100;
            pchar.GenQuest.Cards.SitType   = false;
		break;

		case "Cards_Node_500":
		    if (sti(pchar.Money) < 1500)
		    {
                dialog.text = "Most viccelsz, vagy mi? Nincs 1500 pezód!";
                link.l1 = "Majd én megkeresem!";
			    link.l1.go = "exit";
			    break;
		    }
		    if (sti(npchar.Money) < 1500)
		    {
                dialog.text = "Nem, ezek a fogadások a végén biztosan engem fognak elkapni.";
                link.l1 = "Ahogy óhajtja.";
			    link.l1.go = "exit";
			    break;
		    }
   			dialog.text = "Rendben, játsszunk 500 érmével.";
			link.l1 = "Kezdjük el!";
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
                dialog.text = "Nem fogok csalókkal játszani!";
    			link.l1 = "Ahogy óhajtja.";
    			link.l1.go = "exit";
			}
			else
			{
				if (CheckNPCQuestDate(npchar, "Dice_date_begin"))
				{
					dialog.text = "Miért is ne! A pihenés mindig jót tesz az egészségnek... de nem mindig a pénztárcának...";
	    			link.l1 = "Kiváló.";
	    			link.l1.go = "Dice_begin";
	    			link.l2 = "Mik a játékszabályok?";
	    			link.l2.go = "Dice_Rule";
    			}
    			else
    			{
					dialog.text = "Nem, mára végeztem. Van még dolgom.";
	    			link.l1 = "Ahogy óhajtja.";
	    			link.l1.go = "exit";
				}
			}
		break;

		case "Dice_Rule":
   			dialog.text = DICE_RULE;
			link.l1 = "Nos, akkor kezdjük el!";
			link.l1.go = "Dice_begin";
			link.l3 = "Nem, ez nem nekem való...";
			link.l3.go = "exit";
		break;

		case "Dice_begin":
			Dialog.text = "Elôször is, egyezzünk meg a fogadásról.";
			link.l1 = "Játsszunk 50 pezóért.";
			link.l1.go = "Dice_Node_100";
			link.l2 = "Játsszunk 200 pezóért.";
			link.l2.go = "Dice_Node_500";
			link.l3 = "Azt hiszem, mennem kell.";
			link.l3.go = "exit";
		break;

		case "Dice_Node_100":
			//belamour legendary edition 
			bOk1 = isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && GetNationRelation(npchar.nation, sti(Items[sti(pchar.EquipedPatentId)].Nation)) != RELATION_ENEMY;
			bOk2 = CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && GetNationRelation(npchar.nation, FRANCE) != RELATION_ENEMY;
			bOk = bOk1 || bOk2;
            if (!CheckDiceGameSmallRate() && !bOk)
		    {
                dialog.text = "Te közismert vagy, mint"+ GetSexPhrase("csaló","csaló") +"... Soha nem fogok kockáztatni veled.";
                link.l1 = "Ez mind hazugság! Hát, legyen.";
			    link.l1.go = "exit";
			    break;
		    }

			if (sti(pchar.Money) < 300)
		    {
                dialog.text = "Most viccelsz, vagy mi? Nincs pénzed!";
                link.l1 = "Megtörténik.";
			    link.l1.go = "exit";
			    break;
		    }
		    if (sti(npchar.Money) < 300)
		    {
                dialog.text = "Elég legyen! Végeztem a szerencsejátékkal - mielôtt még csalónak bélyegeznek és arra kényszerítenek, hogy elhagyjam a hajót.";
                link.l1 = "Kár.";
			    link.l1.go = "exit";
			    break;
		    }
   			dialog.text = "Rendben, játsszunk 50 érméért.";
			link.l1 = "Kezdjük el!";
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
                dialog.text = "Ön közismert, mint"+ GetSexPhrase("csaló","csaló") +". Soha nem fogok kockáztatni veled.";
                link.l1 = "Ez mind hazugság! Hát, legyen.";
			    link.l1.go = "exit";
			    break;
		    }
			if (!CheckDiceGameBigRate())
		    {
                dialog.text = "Úgy hallottam, hogy nagyon jó játékos vagy. Nem fogok nagy tétekkel játszani veled.";
                link.l1 = "Esetleg csökkenthetnénk a tétet?";
			    link.l1.go = "Dice_Node_100";
				link.l2 = "Sajnálom, de mennem kell.";
			    link.l2.go = "exit";
			    break;
		    }

			if (sti(pchar.Money) < 1500)
		    {
                dialog.text = "Most viccelsz, vagy mi? Nincs 1500 pezód!";
                link.l1 = "Majd én megkeresem!";
			    link.l1.go = "exit";
			    break;
		    }
		    if (sti(npchar.Money) < 1500)
		    {
                dialog.text = "Nem, ezek a fogadások a végén biztosan engem fognak elkapni.";
                link.l1 = "Ahogy óhajtja.";
			    link.l1.go = "exit";
			    break;
		    }
   			dialog.text = "Rendben, játsszunk 200 érmével.";
			link.l1 = "Kezdjük el!";
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
	                Dialog.Text = "Miért akarod tudni? Ez az én magánéletem.";
					Link.l1 = "Ahogy óhajtja.";
					Link.l1.go = "exit";
	            }
	            else
	            {
                    sld = &Characters[iMoney];
                    pchar.PriceList.ShipStoreIdx = iMoney;
                    
					Dialog.Text = "A" + GetCityName(sld.City) + "városból jövök.";
					Link.l1 = "Milyenek az árak a helyi boltban?";
					Link.l1.go = "price_2";
					Link.l9 = "Mennem kell.";
					Link.l9.go = "exit";
				}
			}
			else
			{
                Dialog.Text = "Már mindent elmondtam. Ne zavarjon a semmiért.";
				Link.l1 = "Igen, igazad van. Viszontlátásra.";
				Link.l1.go = "exit";
            }
		break;
		
		case "price_2":
            sld = &Characters[sti(pchar.PriceList.ShipStoreIdx)];
			SetPriceListByStoreMan(&Colonies[FindColony(sld.City)]);
			Dialog.Text = "Tessék... (megkapta az árlistát)...";
			Link.l1 = "Köszönöm szépen!";
			Link.l1.go = "exit";
			PlaySound("interface\important_item.wav");
		break;
		
        case "Talk_board":
            bOk = iCapBattleDifficulty > hrand(98);
            //if ((Group_GetCharactersNum(NPChar.EncGroupName) - Group_GetDeadCharactersNum(NPChar.EncGroupName)) > GetCompanionQuantity(PChar) && rand(11) > GetCharacterSkillToOld(PChar, SKILL_FORTUNE))
            if(!bOk && iCapBattleDifficulty <= 33)
            {
                Dialog.text = "Ha-ha-ha-ha! Remek vicc, több hajóm van. Térj vissza a hajódhoz és fulladj meg vele.";
                link.l1 = "A több nem jelenti azt, hogy erôsebb, haver.";
                link.l1.go = "Boarding";
            }
            else
            {
                if(!bOk)
                {
                    Dialog.text = "Kapitány, nem kellett volna a mocskos dolgait a hajóm fedélzetén végeznie. De könyörületes leszek, és hagyom, hogy visszatérj a hajódra, hogy megfulladj vele együtt.";
                    link.l1 = "Majd meglátjuk, ki lesz ma a cápa eledele!";
                    link.l1.go = "Boarding";
                }
                else
                {
                    if(iEncPow == -1) iEncPow = 0;
                    Pchar.GenQuest.MoneyForCaptureShip = (70 + hrand(60, "&CapSur"+NPChar.id)) * iEncPow;
					if(HasShipTrait(pchar, "trait14")) Pchar.GenQuest.MoneyForCaptureShip = makeint(sti(Pchar.GenQuest.MoneyForCaptureShip) * 1.35);
                    Dialog.text = RandSwear() + "Igen, sokat hallottam a felháborodásaidról. Úgy legyen, de ne feledjétek " +
                                  XI_ConvertString(NationShortName(sti(NPChar.nation))+"vadász") + " nem hagyja büntetlenül!";
                    link.l1 = "Kiváló. Egy "+Pchar.GenQuest.MoneyForCaptureShip+" pezó összeg megfelel nekem, "+GetAddress_FormToNPC(NPChar)+".";
                    link.l1.go = "Capture";
                    link.l2 = "Ó, nem érdekes. Csak vicceltem"+ GetSexPhrase("","") +"!";
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
            Dialog.Text = "Tessék - és most tûnj el!";
			Link.l1 = "Szép volt! És te is maradj egészséges, barátom!";
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
			Dialog.Text = "Mit akarsz még tôlem?";
			Link.l1 = "Semmi.";
			Link.l1.go = "exit";
			Diag.TempNode = "surrender_goaway";
		break;
		
		case "surrender2":			
			dialog.text = "Úgy tûnik, nincs más választásom, minthogy behódoljak neked.";
			link.l1 = "Menj tovább, most!";
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
			Link.l1 = RandPhraseSimple(RandSwear() + "Ez nagyon érdekes. Egy másik kérdés?",
                                     "Csak egy újabb ügy.");
			Link.l1.go = "quests";
			Link.l2 = RandPhraseSimple("Köszönöm, és mennem kell.",
                                     "Minden jót.");
			Link.l2.go = "exit";
			Diag.TempNode = "quests";
		break;
		
		case "Go_away":
			Dialog.Text = "Takarodj a hajómról!";
			Link.l1 = "Már megyek is.";
			Link.l1.go = "exit";
			Diag.TempNode = "Go_away";
		break;
		
		case "Go_away_Good":
			Dialog.Text = "A beszélgetésünknek vége. Nem mondok semmi újat "+GetAddress_Form(NPChar)+".";
			Link.l1 = "Rendben, rendben. Találkozunk a tengeren!";
			Link.l1.go = "exit";
			Diag.TempNode = "Go_away_Good";
		break;

        case "Capture":
            Diag.TempNode = "Go_away";
            Dialog.Text = "Tessék - és most kifelé!";
			Link.l1 = "Nagyszerû!";
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
            Dialog.Text = "Várj, lehet, hogy így megölsz. Mit akarsz tôlem?";
			Link.l1 = "Megölni téged!";
			Link.l1.go = "QuestAboardCabinDialog_1";
			Link.l2 = "Adjátok meg magatokat!";
			Link.l2.go = "QuestAboardCabinDialog_2";
			Link.l3 = "Add ide a térképet, Billy (c)";  // предмет, далее не ясно или  QuestAboardCabinDialog_1 или QuestAboardCabinDialog_2
			Link.l3.go = "QuestAboardCabinDialog_3";  // можно закодить покидание корабля, но экипаж уже вырезан и тп...
        break;
        
        case "QuestAboardCabinDialog_1":
			Dialog.Text = "Majd meglátjuk, te szemétláda!";
			Link.l1 = "És mit kell látnom?";
			Link.l1.go = "exit";
			// тут можно восстановить НР противника (NPChar) или добавить парочку гардов против ГГ
			LAi_SetCurHPMax(NPChar);
			AddDialogExitQuestFunction("QuestAboardCabinDialogExitWithBattle"); // тут ругань обратно
		break;
		
		case "QuestAboardCabinDialog_2":
			Dialog.Text = "Rendben, nyertél!";
			Link.l1 = "Okos döntés!";
			Link.l1.go = "exit";
			AddDialogExitQuestFunction("QuestAboardCabinDialogSurrender");
		break;
		
		case "QuestAboardCabinDialog_3":
			Dialog.Text = "Remélem, megfulladsz tôle!";
			Link.l1 = "Nagyon jó, vedd a bilincset és fogd be a szád, fogoly.";
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
			Dialog.Text = ""+ GetSexPhrase("Idejöttél","Idejöttél") +", rendetlenséget csináltál"+ GetSexPhrase("","") +",és mindent elvettél"+ GetSexPhrase("","") +", most meg rabszolgát akarsz csinálni belôlem? Soha!";
			Link.l1 = "Akkor készülj a halálra.";
			Link.l1.go = "QuestAboardCabinDialog_1";
		break;
		//eddy. квест мэра, поиски пирата
		case "MQ_step_1":
			Dialog.Text = "Nem, nem láttam egy gyanús hajót sem, ami kalóznak tûnt volna.";
			Link.l1 = "Értem, értem.";
			Link.l1.go = "exit";
		break;
		
		//homo Наводка на купца
		case "MerchantTrap_Abordage":

			Dialog.Text = "A "+NationKingsName(NPChar)+" megadás nevében, "+ GetSexPhrase("mocskos kalóz","mocskos szajha!") +"! Akkor az életed megkíméljük egy igazságos bíróságig, ahol elítélnek minden "+NationNameSK(sti(NPChar.nation))+"hajóért, amit kifosztottál"+ GetSexPhrase("","") +".";
			Link.l1 = "Cseszd meg! Meg kell adnod magad!";
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
					dialog.text = "Excellenciád, fôkormányzó úr! Figyelmesen hallgatom önt, de kérem, hogy legyen rövid: a " + fort +
                          "harcolunk, és nekem kell irányítanom a csata menetét.";
				}
				else
				{
					if(isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && sti(Items[sti(pchar.EquipedPatentId)].Nation) == npchar.nation)
					{
						dialog.text = "Admirális-helyettes! Figyelmesen hallgatom, de kevés idôm van: a " + fort +
                          "harcolunk, és nekem kell irányítanom a csata menetét.";
					}
					else
					{
						dialog.text = "Figyelek rád, de gyorsan fektessük le a látogatásod célját, harcolunk a " + fort +
                          ", és nekem kell irányítanom a csata menetét.";
					}
				}
                link.l1 = "Ezért vagyok itt,  " + GetAddress_FormToNPC(NPChar) + ".";
                link.l1.go = "attack_fort";

                link.l2 = "Ebben az esetben nem rabolom tovább az idejét. Viszlát, "+ GetAddress_FormToNPC(NPChar) + ".";
                link.l2.go = "exit";
    			
            }
            else
            {
                Dialog.text = "Nem vagyok felhatalmazva arra, hogy veled foglalkozzak. Beszéljen a századunk parancsnokával. A neve  " + GetFullName(rchar)+
                              ", megtalálod ôt a " + XI_ConvertString(RealShips[sti(rchar.Ship.Type)].BaseName) + " ''" + rchar.Ship.Name + "''.címen.";
                link.l1 = "Köszönöm. Köszönöm. Azt teszem, amit mond.";
                link.l1.go = "exit";
            
            }
            Diag.TempNode = "Siegehelp";
            
		break;
		
		case "attack_fort":
                dialog.text = "Hogy érti ezt?";
                link.l1 = "Tudok segíteni egy zúzás a vár a kolónia a " +GetConvertStr(aData.Colony+" Town", "LocLables.txt")+ " és elfoglalni a várost, és a zsákmány, ami abban az esetben a siker, mi osztjuk magunk között.";
                link.l1.go = "Siegehelp_1";
                link.l2 = "Valójában az én üzletem aligha éri meg az idejét. Viszlát, "+ GetAddress_FormToNPC(NPChar) + ".";
                link.l2.go = "exit";
                Diag.TempNode = "Siegehelp_0";
		break;
		
		case "Siegehelp_0":
            Dialog.text = "Már megint te? Azt hittem, már mindent megbeszéltünk.";
            link.l1 = "Igazad van. Azt hiszem, elfelejtettem"+ GetSexPhrase("","") +".";
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
                dialog.text = "És milyen részesedésre számítasz a zsákmányból?";
                link.l1 = "A felét.";
                link.l1.go = "Big_part";
                link.l2 = "Egyharmad.";
                link.l2.go = "Middle_part";
                link.l3 = "Negyedét.";
                link.l3.go = "Small_part";
            }
            else
            {
                dialog.text = "Nincs szükségem a szolgálataira, kapitány! Egyedül fogom elfoglalni ezt a kolóniát, és ehhez nincs szükségem segítségre.";
                link.l1 = "Miért vagy olyan biztos benne, " + GetAddress_FormToNPC(NPChar) + ", bárkit érhet balszerencse.";
                link.l1.go = "attack_fort_03";
                link.l2 = "Ebben az esetben nem rabolom tovább az idejét, " + GetAddress_FormToNPC(NPChar) + ". Viszontlátásra!";
                link.l2.go = "exit";
            }
			Diag.TempNode = "Siegehelp_0";

		break;
		
		case "attack_fort_03":
            if((sti(aData.iSquadronPower)*SquadronDamage - (ifortPower)*fortDamage) < 4000)
            {
                dialog.text = "Másrészt a hajóim eléggé megsérültek ebben a csatában, és az erôsítés biztosan nem ártana. Ha egyetértesz a " + GetPart(4) + ", akkor, azt hiszem, megegyezhetünk.";
                link.l1 = "Ez nekem megfelel, " + GetAddress_FormToNPC(NPChar) + ". Én megpróbálom megtámadni az erôdöt, te pedig a hajód ágyúinak tüzével támogatsz minket.";
                link.l1.go = "attack_fort_04";
                aData.PartAttaksFort = 4;
                link.l2 = "Nem vagyok olyan olcsó, " + GetAddress_FormToNPC(NPChar) + ". Sajnálom, hogy elvonom"+ GetSexPhrase("","") +" figyelmét a sürgetô ügyektôl. Viszontlátásra!";
                link.l2.go = "exit";
            }else{
                dialog.text = "Elég hajó van a pazarlásomban ahhoz, hogy ezt az erôdöt porrá zúzzam - csak idô kérdése. És most kérem, hagyja el a hajómat. A gyôzelem vár rám!";
                link.l1 = "Nos, ebben az esetben, " + GetAddress_FormToNPC(NPChar) + ", engedje meg, hogy távozzam. Viszontlátásra!";
                link.l1.go = "exit";
            }
		    Diag.TempNode = "Siegehelp_0";
		break;
		case "Big_part":
            if( (sti(aData.iSquadronPower)*SquadronDamage - (ifortPower)*fortDamage) <= -1500)
            {
                dialog.text = "Az erôd ágyúi súlyosan megrongálták a hajóimat, és a közelgô csatában biztosan mi leszünk a vesztesek. Elfogadom a segítségedet és elfogadom a feltételeidet.";
                link.l1 = "Kiváló, " + GetAddress_FormToNPC(NPChar) + ", ebben az esetben megpróbáljuk megtámadni az erôdöt, és önök támogatni fognak minket a hajójuk ágyúinak tüzével.";
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
					dialog.text = "Excellenciád, még mindig jelentést kell tennem a mûvelet elôrehaladásáról... Legalább " + GetPart(4) +".";
				}
				else
				{
                dialog.text = "Nem túl sok ez, kapitány? Önnek van " + GetNumShips(GetCompanionQuantity(PChar)) +
                              ", az én századomnak pedig " + GetNumShips(Group_GetCharactersNum(sGroup)) + ". Én felajánlhatom önnek " + GetPart(4) +
                              ". És tekintse ezt igazságosnak.";
				}
                aData.PartAttaksFort = 4;
                link.l1 = "Egyetértek"+ GetSexPhrase("","") +", " + GetAddress_FormToNPC(NPChar) + ", ebben az esetben én megrohamozom az erôdöt, ön pedig hajója ágyúinak tüzével támogat minket.";
                link.l1.go = "attack_fort_04";
                link.l2 = "Sajnos nem hiszem, " + GetAddress_FormToNPC(NPChar) + ". Nincs több megbeszélnivaló. Búcsúzom.";
                link.l2.go = "exit";
            }
            Diag.TempNode = "Siegehelp_0";
        break;
        
        case "attack_fort_04":
            dialog.text = "Amint az erôdöt elfoglaltuk, megkezdjük a partraszálló csapatok telepítését a parton, majd magában a városban folytatjuk a harcot, ahol remélem, hogy találkozunk.";
            link.l1 = "Úgy legyen. Hamarosan találkozunk, " + GetAddress_FormToNPC(NPChar) + "!";
            link.l1.go = "exit";
            Diag.TempNode = "Siegehelp_0";
            PChar.quest.Union_with_Escadra = "Yes";
        break;

        case "Middle_part":
            if((sti(aData.iSquadronPower)*SquadronDamage - (ifortPower)*fortDamage) <= -600)
            {
                dialog.text = "Azt hiszem, egyetértek a feltételeiddel. A közös hadmûvelet növelni fogja az esélyeimet, hogy megnyerjem ezt a harcot. Ha minden a tervek szerint alakul, megkapod a részed a zsákmányból.";
                link.l1 = "Nagyszerû, hogy sikerült megállapodnunk, " + GetAddress_FormToNPC(NPChar) + ". Azonnal megparancsolom az embereimnek, hogy támadják meg az erôdöt.";
                link.l1.go = "attack_fort_04";
                aData.PartAttaksFort = 3;
            }else{
				// belamour legendary edition
				bOk1 = isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation);
				bOk2 = CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE;
				bOk = bOk1 || bOk2;
				if(bOk)
				{
					dialog.text = "Excellenciád, még mindig jelentést kell tennem a mûvelet elôrehaladásáról... Legalább " + GetPart(4) +".";
				}
				else
				{
                dialog.text = "Nem túl sok ez, kapitány? Önnek van " + GetNumShips(GetCompanionQuantity(PChar)) + ", az én századomnak pedig " + GetNumShips(Group_GetCharactersNum(sGroup)) + ". Én felajánlhatom önnek " + GetPart(4) + ". És tekintse ezt igazságosnak.";
				}
                link.l1 = "Én "+ GetSexPhrase("egyetértek","egyetértek") +", " + GetAddress_FormToNPC(NPChar) + ", ebben az esetben én megrohamozom az erôdöt, te pedig a hajód ágyúinak tüzével támogatsz minket.";
                link.l1.go = "attack_fort_04";
                aData.PartAttaksFort = 4;
                link.l2 = "Sajnos nem hiszem, " + GetAddress_FormToNPC(NPChar) + ". Nincs több megbeszélnivaló. Búcsúzom.";
                link.l2.go = "exit";
            }
            Diag.TempNode = "Siegehelp_0";
        break;

        case "Small_part":
            dialog.text = "A hajóim elfáradtak, és ebben a helyzetben minden friss erô jól jön. Elfogadom a segítségedet és egyetértek a feltételeiddel.";
            link.l1 = "Örülök"+ GetSexPhrase("","") +", " + GetAddress_FormToNPC(NPChar) + "... Azonnal utasítom az embereimet, hogy kezdjék meg az erôd megtámadását.";
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
            dialog.text = "Helló, kapitány! Ez bizony kemény csata volt, de sikerült megtörnünk a város védelmezôinek dühös ellenállását. Kifosztottuk " + sti(aData.loot)+
                          " pezót. Az egyezségünk értelmében a te részed "+ilt+
                          ". Kérlek, fogadd el ezt a pénzt; minden bizonnyal minden egyes érmét megérdemelsz belôle. És most kérem, bocsássanak meg, de vissza kell térnem a dolgaimhoz.";
            link.l1 = "Ebben az esetben itt hagylak, " + GetAddress_FormToNPC(NPChar) + ". Viszontlátásra!";
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
            dialog.text = "Ahoy, kapitány! Van valami dolgod velem?";
            link.l1 = "Nem, " + GetAddress_FormToNPC(NPChar) + ". Viszlát!";
            link.l1.go = "exit";
            Diag.TempNode = "no_return_02";
		break;
		
		case "GoldSquadron":
            ref rch = Group_GetGroupCommander("Sea_Head_of_Gold_Squadron");
            if (NPChar.id == rch.id)
            {
    			dialog.text = "Hallgatlak, de kérlek, siess a látogatásod céljával, nincs sok idôm. Fontos és titkos küldetésem van, és azt a parancsot is kaptam, hogy süllyesszek el minden gyanús hajót a nyílt tengeren, amely bármilyen veszélyt jelenthet a konvojunkra.";                          
                link.l1 = "Ebben az esetben nem rabolom tovább az idejét. Sok szerencsét, "+ GetAddress_FormToNPC(NPChar) + ".";
                link.l1.go = "exit";

            }
            else
            {
                Dialog.text = "Nem vagyok felhatalmazva arra, hogy veled foglalkozzak. Beszéljen a századunk parancsnokával. A neve " + GetFullName(rch)+
                              ", megtalálod ôt a " + XI_ConvertString(RealShips[sti(rch.Ship.Type)].BaseName) + " ''" + rch.Ship.Name + "''.címen.";
                link.l1 = "Köszönöm. Ahogy mondod.";
                link.l1.go = "exit";

            }
            Diag.TempNode = "GoldSquadron";
		break;
		
		case "WM_Captain":
			dialog.text = "Örülök, hogy megismerhetem, és a nevem " + GetFullName(npchar) + ". Szóval azért jöttél, hogy segíts nekünk? Ebben az esetben különösen örülök, hiszen a jelenlegi helyzetünk valóban kritikus - egyedül vagyunk egy lakatlan sziget partjainál, a hajó aligha hajózható, a legénység súlyos veszteségeket szenvedett...";
			link.l1 = "Ahogy hallottam, volt egy kalózokkal vívott csatátok, aztán ott volt az a vihar...";
			link.l1.go = "WM_Captain_1";
			pchar.quest.DesIsland_Over.over = "yes";//снять прерывание
		break;
		
		case "WM_Captain_1":
			dialog.text = "Helyes. A hajóm súlyosan megsérült a csatában - még egy partraszállási támadást is ki kellett állnunk, amit azok a kalóz rohadékok vezettek. Késôbb egy vihar elkapott minket... ó, nem is akarok belegondolni. Elvittek minket erre a barátságtalan partra. Egész nap imádkoztunk a Boldogságos Szûzanyához, hogy mentsen meg minket a vihartól és tartsa egyben a horgonyláncainkat\nÉs most itt vagyunk. Egy hete javítgatjuk a hajónkat, de nézd meg magad: csak ötven emberünk maradt, és fadeszkák is hiányoznak - és honnan szerezzük ôket? Dzsungelbôl? Nyilvánvalóan. Minden nap keményen dolgozunk, és mégis csak az összes szükséges anyag ötödével rendelkezünk\nS ilyen sérülésekkel hajózni egyenlô az öngyilkossággal. Most már látja, hogy állunk itt, kapitány...";
			link.l1 = "Igen... A helyzetetek nem irigylésre méltó. Gondoljuk át, mire vállalkozhatnánk, és hogyan tudnék segíteni.";
			link.l1.go = "WM_Captain_2";
		break;
		
		case "WM_Captain_2":
			dialog.text = "Eh, bárcsak lenne elég deszkánk és vitorlavászonunk - ebben az esetben egy hét alatt megjavíthatnánk a hajónkat\nKapitány úr, ha már direkt idejött, talán felkeresné a legközelebbi kikötôt, és megvenné a szükséges anyagokat? Ez megoldaná a problémánkat. Ne aggódjatok az érmék miatt, minden költséget megtérítek.";
			link.l1 = "Természetesen. Pontosan mit kell szállítaniuk, és mennyit?";
			link.l1.go = "WM_Captain_3";
		break;
		
		case "WM_Captain_3":
			pchar.questTemp.WPU.Escort.Planks = 300 + hrand(5)*10;
			pchar.questTemp.WPU.Escort.Sailcloth = 150 + hrand(10)*10;
			pchar.questTemp.WPU.Escort.Linen = 70 + hrand(7)*10;
			dialog.text = "Én már minderre rájöttem. Figyelembe véve, hogy mi van már meg, szükségem van "+FindRussianQtyString(sti(pchar.questTemp.WPU.Escort.Planks))+" deszkákra, "+FindRussianQtyString(sti(pchar.questTemp.WPU.Escort.Sailcloth))+" vitorlavászonra és "+FindRussianQtyString(sti(pchar.questTemp.WPU.Escort.Linen))+" pamutra. Ezekkel az anyagokkal egy hét alatt sikerülne megjavítanunk a hajót, és akkor máris vitorlát bonthatnánk.";
			link.l1 = "Rendben. Hozok neked minden anyagot, amire szükséged van. Várjatok meg - legkésôbb tíz nap múlva visszatérek.";
			link.l1.go = "WM_Captain_4";
		break;
		
		case "WM_Captain_4":
			dialog.text = "Köszönöm szépen, kapitány! Most már könnyebb a dolgom. Várni fogjuk és imádkozni fogunk a sikeres visszatérésedért!";
			link.l1 = "Ne aggódjatok. Hamarosan meglesz minden, ami a javításhoz szükséges.";
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
			dialog.text = "Kíváncsian várjuk a visszatérését, kapitány!";
			link.l1 = "Horgonyt felhúzni!";
			link.l1.go = "exit";
			Diag.TempNode = "WM_Captain_again";
		break;
		
		case "WM_Captain_5":
			dialog.text = "Kitûnô! Most már elkezdhetjük a hajó javítását!";
			link.l1 = "Az embereim segítenek neked - így gyorsabban fog menni. Emellett el kell kísérjelek a "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity)+"kolóniára, úgyhogy minél hamarabb végzünk a javítással, annál jobb nekem.";
			link.l1.go = "WM_Captain_6";
		break;
		
		case "WM_Captain_6":
			pchar.questTemp.WPU.Current.TargetIslandID.Shore = SelectQuestShoreLocationFromSea(pchar.questTemp.WPU.Current.TargetIslandID);
			dialog.text = "Tényleg, fogalmam sincs, hogyan köszönjem meg, kapitány... Kérem, rendelje el, hogy az anyagokat a " + XI_ConvertString(pchar.questTemp.WPU.Current.TargetIslandID.Shore) + " nevû öbölben rakodják ki - ott van minden készen a javításra.";
			link.l1 = "Rendben. A parton találkozunk.";
			link.l1.go = "exit";
			AddQuestRecord("Escort", "29");
			AddQuestUserData("Escort", "sShore", XI_ConvertString(pchar.questTemp.WPU.Current.TargetIslandID.Shore+"Gen"));
			pchar.quest.DisasterShip_WMC.win_condition.l1 = "location";
			pchar.quest.DisasterShip_WMC.win_condition.l1.location = pchar.questTemp.WPU.Current.TargetIslandID.Shore;
			pchar.quest.DisasterShip_WMC.function = "RepairShip_Prepare";
			Diag.TempNode = "WM_Captain_repeat";
		break;
		
		case "WM_Captain_repeat":
			dialog.text = "Mikor kezdjük a javítást, kapitány? Várni fogom a parton.";
			link.l1 = "Igen, természetesen. Most indulok.";
			link.l1.go = "exit";
			Diag.TempNode = "WM_Captain_repeat";
		break;
		
		case "Repair_start":
			dialog.text = "Nos, úgy tûnik, minden készen áll a javításhoz. Azt hiszem, öt nap múlva készen leszünk.";
			link.l1 = "Nagyon jó! Úgyis fel akartam fedezni ezt a szigetet, úgyhogy jól fogom kihasználni ezt az idôt.";
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
			dialog.text = "Nos, ennyi volt. A javítással végeztünk, és a hajó készen áll a kihajózásra. Mikor indulunk, kapitány?";
			link.l1 = "Ha készen állsz, nem látom értelmét, hogy ott maradjak. Horgonyt felhúzni!";
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
			log_info("25 nap áll rendelkezésére, hogy elkísérje "+pchar.questTemp.WPU.Escort.ShipBaseName+" '"+pchar.questTemp.WPU.Escort.ShipName+"' a kikötôbe. "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen")+"");
			pchar.quest.DisasterShip_final.win_condition.l1 = "location";
			pchar.quest.DisasterShip_final.win_condition.l1.location = pchar.questTemp.WPU.Escort.StartCity +"_town";
			pchar.quest.DisasterShip_final.function = "WMShip_final";
		break;
		
		case "WMShip_final":
			pchar.quest.Escort_fail.over = "yes";
			pchar.quest.DisasterShipWM_Over.over = "yes";//снимаем оба прерывания
			RemoveCharacterCompanion(Pchar, characterFromID("WMCaptain"));//удаляем компаньона
			pchar.questTemp.WPU.Escort.LevelUp_1Money = sti(pchar.questTemp.WPU.Escort.Planks)*15+sti(pchar.questTemp.WPU.Escort.Sailcloth)*9+sti(pchar.questTemp.WPU.Escort.Linen)*45;//деньги за материалы
			dialog.text = "Még egyszer szeretném megköszönni, kapitány úr - nagyban segített nekem és a legénységemnek, hogy kijussunk abból a szerencsétlenségbôl. Ahogy ígértem, megtérítem a hajóm javításához szükséges anyagok költségeit. Itt vannak "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.LevelUp_1Money))+", kérem, vegye el ôket. És ez az én személyes ajándékom neked.";
			link.l1 = "Örülök, hogy segíthettem neked.";
			link.l1.go = "WMShip_final_1";
		break;
		
		case "WMShip_final_1":
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.WPU.Escort.LevelUp_1Money));
			TakeNItems(pchar, "obereg_"+(hrand(10)+1), 1);
			dialog.text = "És most itt az ideje elbúcsúzni, kapitány. Ne felejtsd el meglátogatni a kikötôi hatóságot - ott várnak rád. Viszlát!";
			link.l1 = "További szép napot, " + npchar.name + "!";
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
			dialog.text = "Valóban? Én meg azt hittem, hogy elfelejtettek minket. Igen, az én hajóm kapta a legrosszabbat. Magunkra hagytak minket, hogy megküzdjünk a természet elemeivel, miután a vihar arra kényszerítette a kalózokat, hogy megállítsák a karavánunk elleni támadást. Erre a barátságtalan partra vittek minket\nPár napot javítással és pihenéssel töltöttünk. Ez a pogányok ismét megtámadtak minket, amint elhajóztunk volna\nAztán a vihar ismét lecsapott ránk - azt hittük, az Úr végre úgy döntött, hogy végez velünk, de megérkeztél. Hála a Szûz Máriának! Még egyszer köszönöm, kapitány úr!";
			link.l1 = "Mindennek vége, " + GetAddress_FormToNPC(NPChar) + ". Most el kell kísérnem a "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen")+", hogy megvédjem az esetleges további bajoktól. Készen állsz az indulásra? A vihar már elkezdett alábbhagyni.";
			link.l1.go = "VSP_Captain_1";
		break;
		
		case "VSP_Captain_1":
			dialog.text = "De persze! Minél hamarabb elhagyjuk ezt a helyet, annál nyugodtabbak lesznek az embereim - már így is túl sokat szenvedtek. Vitorlát bontunk!";
			link.l1 = "Csak kövessétek a hajómat - és nyugtassátok meg a legénységet, most már nincs mitôl félni.";
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
			log_info("25 nap áll rendelkezésére, hogy elkísérje "+pchar.questTemp.WPU.Escort.ShipBaseName+" '"+pchar.questTemp.WPU.Escort.ShipName+"' a kikötôbe."+XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen")+"");
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
			dialog.text = "Elhajózhatunk, kapitány?";
			link.l1 = "Persze. Most visszatérek a hajómra.";
			link.l1.go = "exit";
			Diag.TempNode = "VSP_Captain_again";
		break;
		
		case "VSPShip_final":
			pchar.quest.Escort_fail.over = "yes";
			pchar.quest.DisasterShipWM_Over.over = "yes";//снимаем оба прерывания
			RemoveCharacterCompanion(Pchar, characterFromID("WMCaptain"));//удаляем компаньона
			pchar.questTemp.WPU.Escort.LevelUp_1Money = 10000+sti(pchar.rank)*200;
			dialog.text = "Még egyszer szeretném megköszönni, kapitány - nagyban segített nekem és a legénységemnek, hogy kijussunk ebbôl a helyzetbôl. Itt vannak"+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.LevelUp_1Money))+". Az egész legénység beszállt, szóval eszébe se jusson lemondani róla. Ez pedig az én személyes ajándékom neked.";
			link.l1 = "Örültem, hogy segíthettem neked!";
			link.l1.go = "WMShip_final_1";
		break;
		
		case "SShip_final":
			pchar.questTemp.WPU.Escort.LevelUp_1Money = 5000+sti(pchar.rank)*100;
			RemovePassenger(Pchar, npchar);//удаляем пассажира
			dialog.text = "Szeretném még egyszer megköszönni, kapitány, hogy megmentette a seggünket ebbôl a szarból. Tessék, fogadd el ezeket az érméket - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.LevelUp_1Money))+"  és tessék, fogadd el ezt az ajándékot. Nem sok, de ez minden, amit tehetek, hogy megköszönjem, amit tett. Kérlek, ne utasítsd vissza az ajánlatot\nA volt legénységem csodálkozik rajtad és az indiánokkal és kalózokkal folytatott harcodon. Mindannyian szeretnének csatlakozni hozzád. Remélem, hogy nem utasítod vissza a hajójukat elvesztett tengerészek hûséges szolgálataira vonatkozó kérvényt?";
			link.l1 = "Természetesen nem. Szívesen megtartom. Örömmel segítettem nektek!";
			link.l1.go = "WMShip_final_1";
		break;
		
		//Голландский Гамбит
		case "Stivesant_1":
			DelLandQuestMark(npchar);
			dialog.text = "Jól van. De, mynheer, elmagyaráznád, hogy mi történik itt? Hogy lehet, hogy te vagy a parancsnok 'Meifeng'! Történt valami Longway-jel?";
			link.l1 = "Minden magyarázatot tudok, amire szükséged van - és néhány más fontos információt is.";
			link.l1.go = "Stivesant_2";			
		break;
		
		case "Stivesant_2":
			dialog.text = "Akkor csupa fül vagyok.";
			link.l1 = "Volt egy puccs Willemstadban. Lucas Rodenburg átvette a kormányzó helyét, és börtönbe záratta Matthias Becket, mert azt gyanították, hogy kapcsolatban állt a brit hírszerzéssel.";
			link.l1.go = "Stivesant_3";			
		break;
		
		case "Stivesant_3":
			dialog.text = "Hmm... Mynheer, a dolgok, amiket mondasz, igazán meglepôek. Nem is olyan régen kaptam híreket Willemstadból, és semmi ilyesmi nem volt benne.";
			link.l1 = "Kérem, hallgasson meg, mynheer Stuyvesant. Bizonyára Rodenburgon keresztül kapta a hírt, és ô biztos benne, hogy nem jut el Curacaóra.";
			link.l1.go = "Stivesant_4";			
		break;
		
		case "Stivesant_4":
			dialog.text = "Uram, egyre kevésbé tetszik, amit mond. Ki maga?";
			link.l1 = "Én csak egy kapitány vagyok, és csak egy ember, akinek nem közömbös a holland telepesek sorsa. Lucas Rodenburg utasította Longwayt, hogy pusztítsa el a hajóját, és ölje meg magát is. És mivel 'Meifeng' nem keltett volna gyanút önben, minden erôfeszítés nélkül végrehajtotta volna.";
			link.l1.go = "Stivesant_5";			
		break;
		
		case "Stivesant_5":
			dialog.text = "Tehát azt akarja mondani, hogy Lucas...";
			link.l1 = "Úgy döntött, hogy a lehetô legegyszerûbb módon távolítja el önt a hatalomból - egyszerûen kiiktatja önt. Rajtad kívül nincs más személy a térségben, aki képes lenne jelentôs ellenállást tanúsítani Rodenburg befolyásával szemben a szigetvilágban.";
			link.l1.go = "Stivesant_6";			
		break;
		
		case "Stivesant_6":
			dialog.text = "Ezt nem hiszem el!";
			link.l1 = "Én nem dôltem be annak a szarságnak, amit az angol hírszerzéssel kapcsolatban álló Beck mondott, és elvégeztem a saját nyomozásomat. Rájöttem, hogy 'Meifeng', tele van válogatott gyilkosokkal, és elindult Philipsburgba. Lerohantam ôket, és csatát adtam nekik. Longwayt elfogták, és ô adta át nekem ezeket az információkat, beleértve az ön tartózkodási helyét is.";
			link.l1.go = "Stivesant_7";			
		break;
		
		case "Stivesant_7":
			dialog.text = "Hm... Ez valószínûnek tûnik. Rodenburgon kívül senki sem tudott vagy tudhatott a menetrendemrôl és az útvonalamról! Az istenit! Ez árulás! Hol van Longway?!";
			link.l1 = "Szabadon engedtem ôt az önkéntes vallomásáért cserébe. Meg kell mondanom, nem volt túlságosan lelkes Rodenburg parancsát végrehajtani, de nem is hagyhatta figyelmen kívül. Azt is mondta, hogy nem fog visszatérni Rodenburg szolgálatába - ez az utolsó piszkos ügy kiöntötte a poharát.";
			link.l1.go = "Stivesant_8";			
		break;
		
		case "Stivesant_8":
			dialog.text = "Rendben... Kapitány " + GetFullName(pchar) + ", velem jön Willemstadba. Elhajózol 'Meifeng' a hajóm elôtt. Ha igaz, amit mondtál, Lucast le kell tartóztatni, és te ebben a segítségedre leszel. De ha hazudtál nekem... Csak magadat hibáztathatod.";
			link.l1 = "Számomra nincs értelme hazudni neked, mynheer. Siessünk!";
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
			dialog.text = "Kapitány, menjen a Meifenghez 'Itt az ideje, hogy kihajózzunk.";
			link.l1 = "Igen, mynheer, természetesen.";
			link.l1.go = "exit";
			Diag.TempNode = "Stivesant_10";
		break;
		
		case "Keller_1":
			dialog.text = "Nagyon érdekes! Kérem, mesélje el a történetét. Megpróbálok mindent megtenni, hogy segítsek.";
			link.l1 = "Mynheer Keller, emlékszik, hogy néhány hónappal ezelôtt találkozott egy fuvolával Willemstadba menet. Egy zsidó menekült család volt rajta. Ön annak a hajónak a fedélzetén vacsorázott, majd folytatta útját.";
			link.l1.go = "Keller_2";
		break;
		
		case "Keller_2":
			dialog.text = "Igen, azt hiszem... Igen, most már tisztán emlékszem rá. Szóval, mi a helyzet?";
			link.l1 = "A furulyát még aznap elsüllyesztették a kalózok. Csak két menekültnek sikerült megmenekülnie - Salamon és Abigail, a lánya. Ôk egy szigeten találtak menedéket, alig néhány mérföldnyire attól a helytôl, ahol a támadás történt. Meg kell találnom azt a szigetet. Felidézné, hogy hol találkozott azzal a fuvolával? Ez nagyon fontos.";
			link.l1.go = "Keller_3";
		break;
		
		case "Keller_3":
			dialog.text = "És ez minden, amire szüksége van? Ismerem ezt a szigetet. Nagyon közel van, Trinidad és Curacao között. Egy kis lakatlan, sivatagos sziget. Még indiánok sincsenek ott.";
			link.l1 = "És tudja a hozzávetôleges koordinátáit?";
			link.l1.go = "Keller_4";
		break;
		
		case "Keller_4":
			dialog.text = "Meg tudom mondani a pontos koordinátákat. Északon 12 48'  és nyugaton 64 41'  van. Keressétek ott. A sziget elég kicsi, de könnyen meg kell találnod.";
			link.l1 = "Köszönöm, mynheer Keller! Sokat segítettél nekem. Viszontlátásra.";
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
			dialog.text = "Akart még valamit, kapitány?";
			link.l1 = "Nem, köszönöm. Már vissza akartam térni a hajómra.";
			link.l1.go = "exit";
			Diag.TempNode = "Keller_6";
		break;
		
		// belamour рыбацкое судно -->
		case "FishingBoat":
			pchar.GenQuest.FishingBoatSecondTime = true;
			dialog.text = "Semmi különös, ez egy halászhajó, itt halat fogunk. Valahogy meg kell keresni a megélhetést.";
			link.l1 = "Igen, egyetértek, ezekben az idôkben...";
			link.l1.go = "FishingBoat_1";			
		break;
		
		case "FishingBoat_1":
			Diag.TempNode = "FishingBoat_1";
			dialog.text = "Szóval, mit akarsz?";
			link.l1 = "A"+ GetSexPhrase("","") +" akartam megtudni a legfrissebb híreket a szigetvilágból.";
            link.l1.go = "rumours_capitan";
			link.l2 = "Milyen a mai fogásod? El tudod adni? Az élelmiszer nem ártana nekem...";
			link.l2.go = "FishingBoat_2";
			link.l3 = "Semmi különös, csak üdvözölni jöttem!";
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
				
				dialog.text = "Ma jó a fogás, csak van idônk kihúzni a hálókat. Eladhatjuk neked, még olcsóbban is, mint a boltban - egyébként is, mi egy helyi kereskedônek adjuk el a halat. Ha mindezt lefordítjuk élelmiszerekre... Most van belôle "+iTemp+" , akkor darabonként "+iMoney+" pezó áron tudjuk eladni. Mennyit veszel el?";
				link.l1.edit = 3;
				link.l1 = "";	
				link.l1.go = "Количество вбитого провианта";
				link.l2 = "Tudod, meggondoltam magam, hogy megvegyem az élelmiszert.";	
				link.l2.go = "exit";
				
			}
			if(GetDataDay() > 10 && GetDataDay() < 21) 
			{
				Diag.TempNode = "FishingBoat_1";
				dialog.text = "Igen, valami, hogy ôszinte legyek, egyáltalán nincsenek halak... Szinte semmit sem fogtunk ma. De a szigonyok fölöslegesek maradtak - gondolták, hogy kifognak néhány nagy halat vagy egy bálnát, ha szerencséjük van ... Talán szükség van szigonyokra?";
				link.l1 = "Nem, engem nem érdekel a szigony.";
				link.l1.go = "exit";
				link.l2 = "Hmm, a szigony is hasznos dolog a megfelelô kezekben. Valószínûleg megveszem.";
				link.l2.go = "Гарпуны";
			}
			if(GetDataDay() > 20)
			{
				dialog.text = "Igen, valamit, hogy ôszinte legyek, egyáltalán nincs hal ... Szinte semmit sem fogtunk ma. Szóval nincs mit eladni. Hacsak... Van néhány csecsebecsém, talán valami érdekelhet. Szeretné megnézni?";
				link.l1 = "Nem, nem érdekelnek a csecsebecsék.";
				link.l1.go = "exit";
				link.l2 = "Kár, hogy nincs fogás. Nos, legalább nézzük meg a csecsebecséit - hirtelen valami vonzani fog ...";
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
				dialog.text = "Túl sok vagy... Nekem nincs annyi! Nem tudnál kevesebbet venni?";
				link.l1.edit = 3;
				link.l1 = "";	
				link.l1.go = "Количество вбитого провианта повтор";	
				link.l2 = "Tudod, meggondoltam magam, hogy megvegyem az élelmiszert.";	
				link.l2.go = "exit";
			}	
			if(iQty < 1)
			{
				dialog.text = "Most viccelsz velem? Szükséged van ellátmányra vagy sem? Ha igen, mennyit?";
				link.l1.edit = 3;
				link.l1 = "";	
				link.l1.go = "Количество вбитого провианта повтор";	
				link.l2 = "Tudod, meggondoltam magam, hogy megvegyem az élelmiszert.";	
				link.l2.go = "exit";
			}
			if(iQty > 0 && iQty <= iTemp)
			{
				dialog.text = "Megegyeztünk! "+sti(iQty*iMoney)+" pezó.";
				if(sti(pchar.money) < iQty*iMoney)
				{
					link.l1 = "Hmm, nincs annyi pénzem. Majd máskor.";
					link.l1.go = "exit";
				}
				else
				{
					link.l1 = "Megegyeztünk! Vigyétek az árut a hajómra.";
					link.l1.go = "Удачная покупка";
					link.l2 = "Tudod, meggondoltam magam, hogy megvegyem az élelmiszert.";
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
				dialog.text = "Túl sok vagy... Nekem nincs annyi! Nem tudnál kevesebbet venni?";
				link.l1.edit = 3;
				link.l1 = "";	
				link.l1.go = "Количество вбитого провианта";	
				link.l2 = "Tudod, meggondoltam magam, hogy megvegyem az élelmiszert.";	
				link.l2.go = "exit";
			}	
			if(iQty < 1)
			{
				dialog.text = "Most viccelsz velem? Szükséged van ellátmányra vagy sem? Ha igen, mennyit?";
				link.l1.edit = 3;
				link.l1 = "";	
				link.l1.go = "Количество вбитого провианта";	
				link.l2 = "Tudod, meggondoltam magam, hogy megvegyem az élelmiszert.";	
				link.l2.go = "exit";
			}
			if(iQty > 0 && iQty <= iTemp)
			{
				dialog.text = "Megegyeztünk! "+sti(iQty*iMoney)+" pezó.";
				if(sti(pchar.money) < iQty*iMoney)
				{
					link.l1 = "Hmm, nincs annyi pénzem. Majd máskor.";
					link.l1.go = "exit";
				}
				else
				{
					link.l1 = "Megegyeztünk! Vigyétek az árut a hajómra.";
					link.l1.go = "Удачная покупка";
					link.l2 = "Tudod, meggondoltam magam, hogy megvegyem az élelmiszert.";
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
				dialog.text = "Van "+iTemp+" darab. Száz pezóért tudunk eladni egy szigonyt. Mennyi kell?";
				link.l1.edit = 3;
				link.l1 = "";	
				link.l1.go = "Количество вбитых гарпунов";
				link.l2 = "Tudod, meggondoltam magam, nincs szükségem a szigonyokra.";	
				link.l2.go = "exit";
		break;
		
		case "Количество вбитых гарпунов":
   
			iQty = sti(dialogEditStrings[3]);
			iTemp = makeint(pchar.GenQuest.FishingBoatITemp);
			pchar.GenQuest.FishingBoatIQty = iQty;
			Diag.TempNode = "FishingBoat_1";
			if(iQty > iTemp)
			{
				dialog.text = "Túl sok vagy... Nekem nincs annyi! Nem tudnál kevesebbet venni?";
				link.l1.edit = 3;
				link.l1 = "";	
				link.l1.go = "Количество вбитых гарпунов заново";	
				link.l2 = "Tudod, meggondoltam magam, nincs szükségem a szigonyokra.";	
				link.l2.go = "exit";
			}	
			if(iQty < 1)
			{
				dialog.text = "Viccelsz velem? Szükséged van szigonyokra vagy sem? Ha igen, mennyiért?";
				link.l1.edit = 3;
				link.l1 = "";	
				link.l1.go = "Количество вбитых гарпунов заново";	
				link.l2 = "Tudod, meggondoltam magam, nincs szükségem a szigonyokra.";	
				link.l2.go = "exit";
			}
			if(iQty > 0 && iQty <= iTemp)
			{
				dialog.text = "Megegyeztünk! "+sti(iQty*100)+" pezó.";
				if(sti(pchar.money) < iQty*100)
				{
					link.l1 = "Hmm, nincs annyi pénzem. Majd máskor.";
					link.l1.go = "exit";
				}
				else
				{
					link.l1 = "Megegyeztünk! Majd találok rá valami hasznot.";
					link.l1.go = "Удачная покупка гарпунов";
					link.l2 = "Tudod, meggondoltam magam, nincs szükségem a szigonyokra.";
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
				dialog.text = "Túl sok vagy... Nekem nincs annyi! Nem tudnál kevesebbet venni?";
				link.l1.edit = 3;
				link.l1 = "";	
				link.l1.go = "Количество вбитых гарпунов";	
				link.l2 = "Tudod, meggondoltam magam, nincs szükségem a szigonyokra.";	
				link.l2.go = "exit";
			}	
			if(iQty < 1)
			{
				dialog.text = "Viccelsz velem? Szükséged van szigonyokra vagy sem? Ha igen, mennyiért?";
				link.l1.edit = 3;
				link.l1 = "";	
				link.l1.go = "Количество вбитых гарпунов";	
				link.l2 = "Tudod, meggondoltam magam, nincs szükségem a szigonyokra.";	
				link.l2.go = "exit";
			}
			if(iQty > 0 && iQty <= iTemp)
			{
				dialog.text = "Megegyeztünk! "+sti(iQty*100)+" pezó.";
				if(sti(pchar.money) < iQty*100)
				{
					link.l1 = "Hmm, nincs annyi pénzem. Majd máskor.";
					link.l1.go = "exit";
				}
				else
				{
					link.l1 = "Megegyeztünk! Majd találok rá valami hasznot.";
					link.l1.go = "Удачная покупка гарпунов";
					link.l2 = "Tudod, meggondoltam magam, nincs szükségem a szigonyokra.";
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
				dialog.text = "Nem, nincs más. Ez egy halászhajó! Mi más lehetne itt?";
				link.l1 = "Rendben, értem.";
				link.l1.go = "exit";
			}
			else if(hrand(2, "&SpeGoo") == 1)
			{
				if(ChangeContrabandRelation(pchar, 0) > 5)
				{
					
					dialog.text = "Nos... Van itt egy apróság... Megtartottam, gondoltam eladom valakinek. De sokat kérnék érte! És nem fogom másodszorra felajánlani. Megnézed?";
					link.l1 = "Mutasd meg, lássuk, miféle apróság.";
					link.l1.go = "Особые товары предметы";
				}
				else
				{
					Diag.TempNode = "First time";
					Diag.CurrentNode = "First time";
					pchar.GenQuest.FishingBoatDialogEnb = "no special goods";
					dialog.text = "Nem, nincs más. Ez egy halászhajó! Mi más lehetne itt?";
					link.l1 = "Rendben, értem. ";
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
						sTemp = "egységnyi visszalépés";
					}
					if(GetDataDay() > 7 && GetDataDay() < 15)
					{
						iMoney = GetStoreGoodsPrice(&Stores[PortSpein_STORE], GOOD_OIL, PRICE_TYPE_BUY, pchar, 1);
						iTemp = GOOD_OIL;
						sTemp = "hordónyi kátrány"; 
					}
					if(GetDataDay() > 14 && GetDataDay() < 22) 
					{
						iMoney = GetStoreGoodsPrice(&Stores[BasTer_STORE], GOOD_ROPES, PRICE_TYPE_BUY, pchar, 1);
						iTemp = GOOD_ROPES;
						sTemp = "hajókötelek öblei"; 
					}
					if(GetDataDay() > 21) 
					{
						iMoney = GetStoreGoodsPrice(&Stores[Villemstad_STORE], GOOD_SHIPSILK, PRICE_TYPE_BUY, pchar, 1);
						iTemp = GOOD_SHIPSILK;
						sTemp = "tekercs hajóselyem";
					}
					iQty = 20 + sti(rand(6)*5);
					pchar.GenQuest.FishingBoatITemp = iTemp;
					pchar.GenQuest.FishingBoatIMoney = iMoney;
					pchar.GenQuest.FishingBoatIQty = iQty;
					
					dialog.text = "Nos... Van itt egy jó dolog... Teljesen véletlenül találtam az öböl partján. Ez a "+iQty+" "+sTemp+". Az ára darabonként "+iMoney+". De csak egyszerre adok el mindent, másodszorra nem ajánlom fel. És hogy senki kívülálló ne tudjon róla ... megértettétek?";
					link.l1 = "Nem, nem akarom a kérdéses árut, köszönöm. Nem mondom el senkinek, ne aggódj.";
					link.l1.go = "exit";
					if(sti(pchar.money) >= iMoney*iQty)
					{
						link.l2 = "Megértelek. De az áru megéri. Elviszem. Szállíttassa a hajómra.";
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
				dialog.text = "Ez a "+GetConvertStr("itmname_"+sTemp, "ItemsDescribe.txt")+". Sikerült ... nos, mindegy hova. Gondoltam eladom valami ínyencnek. Csak 10 000 pezóért adom! Elfogadod?";
				if(sti(pchar.money) > 9999)
				{
					link.l1 = "Persze, hogy elfogadom! Az a dolog áll. ";
					link.l1.go = "Купили особый товар";
				}
				link.l2 = "Nem, nincs rá szükségem. Nem veszem el. ";
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
       case 0: numships = "nincs hajó"; break;
       case 1: numships = "egy hajó";      break;
       case 2: numships = "két hajó";       break;
       case 3: numships = "három hajó";       break;
       case 4: numships = "négy hajó";    break;
       case 5: numships = "öt hajó";     break;
       case 6: numships = "hat hajó";    break;
    }
    return numships;
}

string GetPart(int part)
{
    string numpart;
    switch(part)
    {
       case 0: numpart = ""; break;
       case 1: numpart = "minden zsákmány"; break;
       case 2: numpart = "a zsákmány fele"; break;
       case 3: numpart = "a zsákmány harmada"; break;
       case 4: numpart = "a zsákmány negyede";      break;
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

int CalcBattleDifficulty()
{
    UpdatePlayerSquadronPower();

    float encPow = 0.0;
    float pchPow = stf(PChar.Squadron.RawPower);

    string sTemp;
    if(CheckAttribute(CharacterRef, "SeaAI.Group.Name"))
        sTemp = CharacterRef.SeaAI.Group.Name;
    else return 0;

    int	iGroupIndex = Group_FindGroup(sTemp);
    if (iGroupIndex < 0)
    {
        Log_TestInfo("НЕТ ГРУППЫ В CalcBattleDifficulty");
        trace("НЕТ ГРУППЫ В CalcBattleDifficulty");
        return 0;
    }

    ref rGroup = Group_GetGroupByIndex(iGroupIndex);
    if (!CheckAttribute(rGroup, "Quest")) return 0;

    aref aCompanions, aCharInfo;
    makearef(aCompanions, rGroup.Quest);
    int qty = GetAttributesNum(aCompanions);

    ref rChar, rShip;
    int iShipType, idx;
    for(int i = 0; i < qty; i++)
    {
        aCharInfo = GetAttributeN(aCompanions, i);
        idx = sti(aCharInfo.index);
        if(idx == -1) continue;
        rChar = GetCharacter(idx);
        if(!CheckAttribute(rChar, "index") || rChar.index == "none" || LAi_IsDead(rChar)) continue;
        iShipType = sti(rChar.Ship.Type);
        if(iShipType == SHIP_NOTUSED) continue;
        rShip = GetRealShip(iShipType);
        encPow += GetRealShipPower(rChar);
    }

    iEncPow = encPow;

    if(pchPow == 0.0)
    {
        if(encPow == 0.0) return 50;
        return 0;
    }

    float fRatio = (encPow * 0.9) / pchPow;

    if(fRatio >= 1.7) return 0; // Кирдык
    // От 50 шанс быстро падает к 0
    if(fRatio >= 1.0)
    {
        return MakeInt(100 * 0.5 * pow((1.7 - fRatio) / 0.7, 2.5));
    }
    // От 50 шанс медленно растёт к 100
    return MakeInt(100 * (0.5 + 0.5 * pow((1 - fRatio), 0.5)));
}

