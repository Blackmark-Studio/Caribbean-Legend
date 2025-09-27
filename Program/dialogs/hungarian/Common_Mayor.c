// boal 25/04/04 общий диалог мэры
#include "DIALOGS\%language%\Rumours\Common_rumours.c"  //homo 25/06/06
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref aData;
	aref Link, NextDiag, arName;

	DeleteAttribute(&Dialog,"Links");

	ref FortChref; // фортовый командер
	ref arItem;
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Mayor\" + NPChar.City + "_Mayor.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
    ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 25/06/06

    FortChref = GetFortCommander(NPChar.City); // будет или фортовик или сам губернатор

    ref offref;
    int i, cn, iRank, iDay;
    int qty;
    string attrLoc, QuestName, sTemp;
	bool bOk, bOk1, bOk2;
	
    if (CheckNPCQuestDate(npchar, "Card_date"))
	{
		SetNPCQuestDate(npchar, "Card_date");
		npchar.money = 5000 + (rand(10)+1) * makeint(100 * sti(PChar.rank) * (10.0 / MOD_SKILL_ENEMY_RATE));
	}
	// генератор ИДХ по кейсу -->
	attrLoc   = Dialog.CurrentNode;
  	if (findsubstr(attrLoc, "GetPrisonerIdx_" , 0) != -1)
 	{
        i = findsubstr(attrLoc, "_" , 0);
	 	pchar.GenQuest.GetPrisonerIdx = strcut(attrLoc, i+1, strlen(attrLoc)-1); // индех в конце
 	    Dialog.CurrentNode = "sell_prisoner_2";
 	}
 	// генератор ИДХ по кейсу <--
 	
	switch (Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOff");
		break;
		
		case "fight":
            Pchar.quest.ArestInResidenceEnd.win_condition.l1          = "ExitFromLocation";
		    Pchar.quest.ArestInResidenceEnd.win_condition.l1.location = Pchar.location;
		    Pchar.quest.ArestInResidenceEnd.win_condition             = "ArestInResidenceEnd";
		    Pchar.quest.ArestInResidenceEnd.ResidenceLocation = Pchar.location;
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;

			LAi_LockFightMode(Pchar, true); // ножками путь убегает
		    LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
		    LAi_group_Attack(NPChar, Pchar); // не работает на бессмертного мера :(
			i = GetCharIDXByParam("CityType", "location", Pchar.location); // фантом солдат
			if (i != -1)
			{
			    LAi_group_Attack(&Characters[i], Pchar);
			}
		break;
		
		case "First time":
            NextDiag.TempNode = "First time";
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar, 
					LinkRandPhrase("Meg merted mutatni magad az otthonomban?! Nagyon bátor vagy, vagy bolond...", "Hogy engedhették az idióta ôreim, hogy egy ellenség betörjön a palotámba? Ezért valakinek a fejét fogom venni.", "Úgy látszik, az ôreim egy rézpénzt sem érnek, ha valami gazember a rezidenciámban szaladgál, és a holmimban turkál..."), 
					LinkRandPhrase("Mit akarsz, "+ GetSexPhrase("gazember","ördög") +"?! A katonáim már a nyomodban vannak"+ GetSexPhrase(", mocskos kalóz","") +"!", +"gyilkos, azonnal hagyd el a rezidenciámat! Ôrség!", "Nem félek tôled, "+ GetSexPhrase("gazember","patkány") +"! Hamarosan felakasztanak az erôdünkben!"));
				link.l1 = NPCharRepPhrase(pchar,
					RandPhraseSimple("A katonáitok értéktelenek.", "Próbálj meg elkapni."), 
					RandPhraseSimple("Fogd be a szád, " + GetWorkTypeOfMan(npchar, "") + ", vagy én fogom be helyetted!", "Maradj csendben, haver, és életben maradsz."));
				link.l1.go = "fight";
				break;
			} 
			if (sti(NPChar.nation) == PIRATE)
            {
				if (CheckAttribute(pchar, "GenQuest.CaptainComission") && CheckAttribute(pchar, "GenQuest.CaptainComission.PiratesCity") && NPChar.city == pchar.GenQuest.CaptainComission.PiratesCity)
				{
					dialog.text = "Mire van szükséged?";
					link.l1 = "Beszélni akartam veled egy fontos munkáról.";
					link.l1.go = "quests";
					break;
				}
				if (CheckAttribute(pchar, "GenQuest.Marginpassenger") && pchar.GenQuest.Marginpassenger == "cabin" && NPChar.city == "LeFransua")
				{
					dialog.text = "Mire van szükséged?";
					link.l1 = "Beszélni akartam veled egy fontos munkáról.";
					link.l1.go = "quests";
					break;
				}
					dialog.text = "Nincs mirôl beszélni, uram. Elfoglalt vagyok.";
					link.l1 = "Elnézést kérek.";
					link.l1.go = "Exit";
            }
			if (sti(NPChar.nation) != PIRATE && ChangeCharacterHunterScore(Pchar, NationShortName(sti(NPChar.nation)) + "hunter", 0) > 10)
            {
				iTotalTemp = ChangeCharacterHunterScore(Pchar, NationShortName(sti(NPChar.nation)) + "hunter", 0);
                dialog.text = "Nézd csak, ki van ott! Ez a"+ GetSexPhrase("","") +" " + GetFullName(pchar) + ". Tudjátok, nemrég küldtem ki kalózvadászokat, hogy visszahozzanak titeket ide. Ha tudtam volna, hogy betáncolsz az ajtómon, félretettem volna a pénzemet.";
                if (sti(pchar.Money) >= iTotalTemp*6000)
                {
                    link.l1 = "Épp most akartam rendezni a számláinkat.";
				    link.l1.go = "arestFree_1";
                }
				link.l2 = "Itt az ideje, hogy gyorsan távozzak.";
				link.l2.go = "arest_1";
				break;
            }
			if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
			{
    			dialog.text = "Betörés! Ôrség! Riadó! Gyilkosság!";
				link.l1 = "Basszus!";
				link.l1.go = "fight"; 
				break;
			}
			//--> Jason, Бремя гасконца
			if (CheckAttribute(pchar, "questTemp.Sharlie.Citcount") && npchar.city == "FortFrance")
			{
    			dialog.text = "Mit akar, monsieur?";
				link.l1 = "Üdvözlöm, felség. Charles de Maure vagyok, nemrég érkeztem Párizsból. Michel de Monper-t keresem.";
                link.l1.go = "Sharlie";
				npchar.quest.meeting = "1"; // patch-6
				DelLandQuestMark(characterFromId("FortFrance_Mayor"));
				break;
			}
			
			if (CheckAttribute(pchar, "questTemp.Sharlie.Lock") && npchar.city == "FortFrance")
			{
				if (CheckAttribute(pchar, "questTemp.Sharlie.Pardon"))
				{
					dialog.text = "Ó, ön az, uram... Elnézést kell kérnem a durvaságomért. Elnézést kérek, messze vagyunk Párizs finomságaitól itt a gyarmatokon.";
					link.l1 = "Természetesen, felség.";
					link.l1.go = "Sharlie_2";
				}
				else
				{
					dialog.text = "Szeretne valamit, Charles?";
					link.l1 = "Van egy kérdésem...";
					link.l1.go = "quests";
					link.l2 = "Nem, semmit.";
					link.l2.go = "exit";
				}
				if (CheckAttribute(pchar, "questTemp.Sharlie.Junglejew"))
				{
					link.l3 = "Monsieur, találtam egy bandita holttestet a dzsungelben. Az indiánok ölték meg. Fülbevalók voltak a testén, úgy tûnik, Európából hozták ide. Talán az egyik nemesé volt a városában?";
					link.l3.go = "Sharlie_junglejew";
				}
				npchar.quest.meeting = "1"; // patch-6
				break;
			}			
			//<-- Бремя гасконца
			//--> Sinistra, Травля крысы
			if (CheckAttribute(pchar, "questTemp.TK_TravlyaKrys") && npchar.city == "FortFrance")
			{
    			dialog.text = "Isten hozta a Karib-tengeren, de Maure kapitány. Ezúttal tényleg.";
				link.l1 = "Köszönöm, excellenciás uram.";
                link.l1.go = "TK_TravlyaKrys";
				DelLandQuestMark(npchar);
				break;
			}
			// Jason НСО
			// belamour legendary edition фикс проверки мундира с мушкетом
			if (CheckAttribute(pchar, "questTemp.Patria.Governor") && npchar.city == "Marigo" && IsUniformEquip())
			{
    			dialog.text = "Örülök, hogy látom, kormányzó úr! Hogy van? Minden rendben van Sint Maartenen.";
				link.l1 = "Nincs idôm maradni. Folytassa a jó munkát.";
				link.l1.go = "exit";
				link.l2 = "A munkáról akartam beszélni.";
				link.l2.go = "quests";   //(перессылка в файл города)
				link.l8 = "Mit szólnál egy szerencsejátékhoz?";
				link.l8.go = "Play_Game";
				break;
			}
			// belamour legendary edition фикс проверки мундира с мушкетом
			if (CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE && IsUniformEquip())
			{
    			dialog.text = "Istenem, de örülök, hogy látom, fôkormányzó úr! Minden nagyszerû itt a mi szerény kis kolóniánkon! Kérem, foglaljon helyet, utasítom a szolgákat, hogy terítsenek...";
				link.l1 = "Nem szükséges. Nem jöttem sokáig. Folytassátok a jó munkát.";
				link.l1.go = "exit"; 
				link.l2 = "A munkáról akartam beszélni.";
				link.l2.go = "quests";   //(перессылка в файл города)
				link.l8 = "Mit szólnál egy szerencsejátékhoz?";
				link.l8.go = "Play_Game";
				break;
			}
			// belamour legendary edition фикс проверки мундира с мушкетом
			if (CheckAttribute(pchar, "questTemp.Patria.GenGovernor") &&  IsUniformEquip())
			{
    			dialog.text = "Ki van itt? A francia gyarmatok fôkormányzója! Mit szeretne, kegyelmes uram? Üljön le, utasítom a szolgáimat, hogy hozzanak bort és friss gyümölcsöt.";
				link.l1 = "Ne aggódjon, csak azért jöttem ide, mert a szigetre látogattam, és nem mehettem el köszönés nélkül.";
				link.l1.go = "exit"; 
				link.l2 = "A munkáról akartam beszélni.";
				link.l2.go = "quests";   //(перессылка в файл города)
				link.l8 = "Mit szólnál egy szerencsejátékhoz?";
				link.l8.go = "Play_Game";
				break;
			}		
			//--> Jason, Португалец
			if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "MartiniqueGovernor" && npchar.city == "FortFrance")
			{
    			dialog.text = "Ó, hát itt van, kapitány úr! Meg kell mondjam, nem sietted el a dolgot.";
				link.l1 = "A lehetô legkorábban érkeztem, excellenciás uram. Azt mondták, sürgôs dolga van.";
				link.l1.go = "Portugal"; 
				break;
			}			
			//<-- Португалец
            
            if (npchar.quest.meeting == "0")
			{
				dialog.text = "Az embereim azt mondták, hogy ön nagyon kitartóan kért meghallgatást. A nevem " + GetFullName(npchar) +
                              ". Én vagyok a "+ GetCityName(NPChar.city) + "város kormányzója, a " + NationKingsName(npchar)+
                              "alattvalója. És most kérem, mit akar " + GetAddress_Form(NPChar) + "?";
				link.l1 = "A nevem " + GetFullName(pchar) + ".";
				link.l1.go = "node_1";
				npchar.quest.meeting = "1";
				if(startHeroType == 4 && NPChar.location == "SantaCatalina_townhall")
				{
					dialog.text = TimeGreeting() +", Miss MacArthur.";
					link.l1 = TimeGreeting() +", Excellenciás uram.";
					link.l1.go = "Helen_node_1"
				}
			}
			else
			{
               	//ОСАДЫ homo
				if (CheckAttribute(&Colonies[FindColony(npchar.City)],"Siege"))
                {

                    makearef(aData, NullCharacter.Siege);
                    
                    if (CheckAttribute(aData, "HelpColony") && sti(aData.HelpColony) == true )
                    {
                        dialog.text = "Ez minden?";
                        link.l1 = "Igen, uram. Nem akarom tovább feltartani.";
                        link.l1.go = "exit";

                    }
                    else
                    {
                        dialog.text = "Sajnálom, hogy felzaklatom, de most nincs idôm beszélni önnel. Mint tudnia kell, a kolóniánkat megtámadta a "+NationNamePeople(sti(aData.nation))+". Még mindig gondoskodom a védelmünkrôl.";
                        link.l1 = "Szeretném felajánlani a segítségemet az erôd védelmében.";
                        link.l1.go = "siege_task";
                        link.l2 = "Akkor nem fogom tovább feltartani.";
            			link.l2.go = "exit";
                    }
                }
                else
                {//->
                    makearef(aData, NullCharacter.Siege);
                    if (CheckAttribute(aData, "PlayerHelpMayor") && sti(aData.PlayerHelpMayor) == true
                    && CheckAttribute(aData, "HelpColony") && sti(aData.HelpColony) == true )
                    {
                        AddMoneyToCharacter(Pchar,(sti(aData.iSquadronPower)*1500));
                        ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 20);
                        ChangeCharacterComplexReputation(pchar,"nobility", 10);
                        AddCharacterExpToSkill(GetMainCharacter(), "Leadership", 180);
                        AddCharacterExpToSkill(GetMainCharacter(), "Sailing", 200);
                        AddCharacterExpToSkill(GetMainCharacter(), "Accuracy", 200);
                        AddCharacterExpToSkill(GetMainCharacter(), "Cannons", 200);
                        //--> слухи
                        SiegeRumour("They say that you had helped us to repel the "+NationNameSK(sti(aData.nation))+" squadron and to defend our colony! We are grateful to you, "+ GetAddress_Form(NPChar)+".", aData.Colony, sti(aData.conation), -1, 15, 3);
			            //<-- слухи
                        DeleteAttribute(aData, "PlayerHelpMayor");
                        DeleteAttribute(aData, "HelpColony");
                        dialog.text = "Ó, te vagy az, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+", örülök, hogy látlak. Jó hír a kolóniánknak - sikerült visszaverni a "+NationNameSK(sti(aData.nation))+" betolakodókat. Ebben neked is részed van, úgyhogy itt a jutalmad - "+(sti(aData.iSquadronPower)*1500)+" pezó. Tessék.";
                        link.l1 = "Köszönöm, " + GetAddress_FormToNPC(NPChar) + ", öröm veled üzletelni!";
                        link.l1.go = "exit";
                    }
                    else
                    {
   						//--> дача квеста найти кольцо в борделе
						if (rand(4) == 4 && pchar.questTemp.different == "free" && GetNpcQuestPastDayWOInit(npchar, "questTakeRing") > 365 && sti(pchar.questTemp.HorseQty) > 10)
						{// Addon-2016 Jason
							if (npchar.city == "Bridgetown" || npchar.city == "Charles" || npchar.city == "FortFrance" || npchar.city == "Marigo" || npchar.city == "Panama" || npchar.city == "PortRoyal" || npchar.city == "SantoDomingo" || npchar.city == "Tortuga")
							{
        						dialog.text = "Van egy feladatom számodra, de ez kissé szokatlan.";
								link.l1 = "Ezek azok a feladatok, amikben a legjobb vagyok.";
        						link.l1.go = "TakeRing_1";
								SaveCurrentNpcQuestDateParam(npchar, "questTakeRing");
								break;
							}
						}
						//<-- дача квеста найти кольцо в борделе    				
						dialog.text = RandPhraseSimple("Ó, már megint te vagy az? Mit akarsz tôlem ezúttal?",
                                      "Elvonod a figyelmemet a városom ügyeirôl. Mit akarsz, " +GetAddress_Form(NPChar)+"?");
						if (npchar.city != "Panama") // Addon-2016 Jason
						{
							link.l1 = "Szeretnék beszélni veled a "+ NationNameGenitive(sti(NPChar.nation))+".";
							link.l1.go = "work";
						}
						// Warship Генер "Пираты на необитайке" - сдаём пиратов властям
						if(CheckAttribute(PChar, "Quest.PiratesOnUninhabited_OnShore") || CheckAttribute(PChar, "Quest.PiratesOnUninhabited_ShipSink"))
						{
							link.l11 = XI_ConvertString(PChar.GenQuest.PiratesOnUninhabited.StartShore + "Gen") + " Találtam néhány kalózt. Jelenleg az összes " + PChar.GenQuest.PiratesOnUninhabited.PiratesCount + " a fedélzeten van. Át akarom adni ôket a hatóságoknak.";
							link.l11.go = "PiratesOnUninhabited_1";
						}
						
        				link.l2 = "Egy fontos témáról akartam beszélni veled.";
						if(CheckAttribute(pchar,"questTemp.ReasonToFast") && !CheckAttribute(pchar,"questTemp.ReasonToFast.SpeakOther") && !CheckAttribute(pchar, "questTemp.ReasonToFast.cantSpeakOther") && (pchar.questTemp.ReasonToFast.city == NPChar.city))
						{
							link.l2.go = "ReasonToFast_Mayor1";
						}
						else
						{
							link.l2.go = "quests";   //(перессылка в файл города)
						}	
						if(CheckAttribute(pchar,"GenQuest.CaptainComission") && (pchar.GenQuest.CaptainComission.variant == "A2") && (pchar.GenQuest.CaptainComission.City == NPChar.city))
						{
							if(pchar.GenQuest.CaptainComission == "Begin_1" && !CheckAttribute(pchar,"GenQuest.CaptainComission.SpeakMayor")) 
							{
								link.l12 = "Van egy kapitány a járôr parancsnoka " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"név") + "Acc")) + " nevû " + pchar.GenQuest.CaptainComission.Name + ", hogyan tudok találkozni vele?";
								link.l12.go = "CapComission_Mayor1";
							}	
							if(CheckAttribute(pchar,"GenQuest.CaptainComission.PrisonFree"))
							{
								link.l12 = "Az ôrjárat egykori parancsnoka " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"név") + "Acc")) + " " + pchar.GenQuest.CaptainComission.Name + " beleegyezett, hogy felfedje a rejtekhelyét a hatóságoknak.";
								link.l12.go = "CapComission_Mayor9";
							}
							if(pchar.GenQuest.CaptainComission == "GetGoodsSuccess")
							{
								link.l12 = "Az ôrjárat egykori parancsnoka " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"név") + "Acc")) + " " + pchar.GenQuest.CaptainComission.Name + " felfedte elôttem a rejtekhelyét.";
								link.l12.go = "CapComission_Mayor13";
							}
						}
						if(CheckAttribute(pchar,"GenQuest.ShipWreck") && pchar.GenQuest.ShipWreck == "SailorsOnShore" && GetQuestPastDayParam("GenQuest.ShipWreck") < 25  && sti(npchar.nation) == sti(pchar.GenQuest.ShipWreck.Nation))
						{
							if(!CheckAttribute(pchar,"GenQuest.ShipWreck.SpeakMayor"))
							{
								iDay = GetQuestPastDayParam("GenQuest.ShipWreck");
								if(CheckAttribute(pchar, "GenQuest.ShipWreck.Mutiny"))
								{
									link.l13 = UpperFirst(XI_ConvertString(pchar.GenQuest.ShipWreck.Shore + "Dat")) + " Találkoztam a kapitánnyal " + pchar.GenQuest.ShipWreck.Name + " és a matrózokkal, akiket a kalóz " + pchar.GenQuest.ShipWreck.BadName + "partra vetett. " +
										"Sajnos már túl sok emberem volt a hajón, és nem tudtam ôket a fedélzetre venni. De hagytam nekik ellátmányt és fegyvereket. Ha egy mentôhajó nem veszi fel ôket " + (30 - iDay) + " napokon belül, akkor nem tudom, hogy élve találja-e meg ôket vagy sem.";
									link.l13.go = "ShipWreck1";
								}
								else
								{
									link.l13 = UpperFirst(XI_ConvertString(pchar.GenQuest.ShipWreck.Shore + "Gen")) + " Találkoztam a hajótörött hajó matrózaival '" + pchar.GenQuest.ShipWreck.ShipTypeName + "' a kapitányukkal. " + 
										"Sajnos, már túl sok ember volt a hajón, és nem tudtam felvenni ôket a fedélzetre. De hagytam nekik ellátmányt és fegyvereket. Ha egy mentôhajó nem veszi fel ôket " + (30 - iDay) + " napokon belül, akkor nem tudom, hogy élve találja-e meg ôket vagy sem.";
									link.l13.go = "ShipWreck1";							
								}
							}	
						}
        				if (GetPrisonerQty() > 0)
        				{
                            link.l3 = "Szeretnék egy foglyot feladni.";
        				    link.l3.go = "sell_prisoner";
        				}
        				if (npchar.Default  == npchar.location) // если не в тюрьме
        				{
        					if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
        					{
        						link.l4 = "Meg kell oldanom néhány pénzügyi kérdést veled.";
        						link.l4.go = "LoanForAll";//(перессылка в кредитный генератор)
        					}
        				}
						//-->> сдача найденного в борделе кольца
						if (CheckCharacterItem(pchar, "MayorsRing"))
						{
							if (pchar.questTemp.different.TakeMayorsRing == "toBrothel")
							{
        						link.l5 = "Sikerült megtalálnom a gyûrûdet. Tessék, tessék.";
        						link.l5.go = "TakeRing_S1";
							}
							else
							{
        						link.l5 = "Nálam van a jegygyûrûd. Az egyik... dolgozó lánynál volt a bordélyházban.";
        						link.l5.go = "TakeRing_S3";
							}
						}
						//<<-- сдача найденного в борделе кольца 
						
						//--> Jason, генер почтового курьера 2 уровня
						if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.LevelUp"))
						{
							if (pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
							{
							link.l14 = "Üzenetet hoztam a "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen")+"városból.";
							link.l14.go = "Postcureer_LevelUp_ForAll";
							}
						}
						//<-- генер почтового курьера 2 уровня
						
						// Warship, 16.05.11. Квест "Правосудие на продажу" -->
						if(CheckAttribute(PChar, "GenQuest.JusticeOnSale.MayorWait") && CheckAttribute(PChar, "GenQuest.JusticeOnSale.CityId") && NPChar.location == PChar.GenQuest.JusticeOnSale.CityId + "_townhall")
						{
							link.l15 = UpperFirst(GetAddress_FormToNPC(NPChar)) + ", megtaláltam egy csempészbandát, amelynek vezetôjét nemrég fogták el az ôrök. Most a szökését tervezik. A hajójuk '" + PChar.GenQuest.JusticeOnSale.ShipName + "' a " + XI_ConvertString(PChar.GenQuest.JusticeOnSale.ShoreId + "Dat") + "kikötôben van.";
							link.l15.go = "JusticeOnSale_1";
						}
						
						if(CheckAttribute(PChar, "GenQuest.JusticeOnSale.ShipSink") && CheckAttribute(PChar, "GenQuest.JusticeOnSale.CityId") && NPChar.location == PChar.GenQuest.JusticeOnSale.CityId + "_townhall")
						{
							link.l15 = UpperFirst(GetAddress_FormToNPC(NPChar)) + ", A csempészbanda már nincs többé!";
							link.l15.go = "JusticeOnSale_7";
						}
						// <--Правосудие на продажу
						//Jason --> Регата
						if (CheckAttribute(pchar, "questTemp.Regata.ToPortRoyal") && NPChar.location == "Portroyal_townhall")
						{
							link.l16 = "A regattára jöttem. Itt a meghívóm.";
							link.l16.go = "Regata";
						}
        				//link.l7 = "I would like to know where the Governor-General of " + NationNameGenitive(sti(NPChar.nation)) + "is.";
        				link.l8 = "Talán szeretnél egy kis szerencsejátékkal pihenni?";
        			    link.l8.go = "Play_Game";
        				link.l10 = "Kérem, bocsásson meg, de a kötelesség hív.";
        				link.l10.go = "exit";
                    }
                }//<-
			}
		break;
		
		// Warship Генер "Пираты на необитайке"
		case "PiratesOnUninhabited_1":
			offref = CharacterFromID("PirateOnUninhabited_0");
			qty = makeint(sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) * (sti(offref.rank) * (800 + GetCharacterSPECIALSimple(NPChar, SPECIAL_L) * 100) + GetCharacterSkillToOld(offref, "Leadership") * 500 + GetCharacterSkillToOld(PChar, "commerce") * 500) / 20);
			
			PChar.GenQuest.PiratesOnUninhabited.MoneyForPirates = qty;
			
			dialog.text = "Nagyon jó. Összehangolt erôfeszítésekkel kell küzdenünk ez ellen a közös csapás ellen. Azonnal küldök egy hajót értük. Biztos lehet benne, hogy kevesebb, mint egy héten belül akasztófán lógnak majd. Ó, és természetesen jutalom is jár - " + FindRussianMoneyString(qty) + ".";
			link.l1 = "Köszönöm, felség. Mindig örömömre szolgál. ";
			link.l1.go = "PiratesOnUninhabited_2";
			link.l2 = "Nem. Ha jobban meggondolom, ez nem lesz jó.";
			link.l2.go = "exit";
		break;
		
		case "PiratesOnUninhabited_2":
			offref = CharacterFromID("PirateOnUninhabited_0");
			
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.PiratesOnUninhabited.MoneyForPirates));
			
			RemovePassenger(PChar, offref);
			RemoveCharacterCrew(PChar, sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) - 1);
			
			sTemp = "PiratesOnUnnhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTemp, "PiratesOnUninhabited", "12");
			AddQuestUserData(sTemp, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sTemp, "mayorName", GetFullName(NPChar));
			CloseQuestHeader(sTemp);
			
			PChar.Quest.PiratesOnUninhabited_OnShore.over = "yes";
			PChar.Quest.PiratesOnUninhabited_OnMayak.over = "yes";
			
			if(CheckAttribute(PChar, "Quest.PiratesOnUninhabited_ShipSink"))
			{
				PChar.Quest.PiratesOnUninhabited_ShipSink.over = "yes";
				
				PChar.GenQuest.PiratesOnUninhabited.ClearShip = true;
				Map_ReleaseQuestEncounter("PiratesOnUninhabited_BadPirate"); // Убираем с глобалки
			}
			
			DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
			
			DialogExit();
		break;
		
		// ------------------------- Повод для спешки -----------------------------
		case "ReasonToFast_Mayor1":
			dialog.text = "Csupa fül vagyok, kapitány.";
			link.l1 = "Egy bûnözôi összejátszásról akartam beszámolni, ami a helyôrségük egyik tisztje és a kalózok között történt... (magyarázza az ügyet).";
			if(sti(pchar.reputation.nobility) < 41)
			{
				link.l1.go = "ReasonToFast_BMayor";			
			}
			else
			{
				link.l1.go = "ReasonToFast_GMayor";	
			}
			pchar.questTemp.ReasonToFast.SpeakOther = true;			
		break;
		
		case "ReasonToFast_GMayor":
			if(pchar.questTemp.ReasonToFast == "PatrolSuccess_1") 
			{ 
				// вилка_А
				dialog.text = "Köszönöm, "+ GetSexPhrase("mister","miss") +"! Azonnal elrendelem annak az árulónak a letartóztatását.\nSok pénzt költhetett, sajnos a kincstárunk üres...";
				link.l1 = "Nem a pénzért tettem, excellenciás uram.";
				link.l1.go = "ReasonToFast_GMayor_11";				
				if(pchar.questTemp.ReasonToFast.chain == "A0") ReasonToFast_RemoveVictim();
				if(pchar.questTemp.ReasonToFast.chain == "A1") pchar.quest.ReasonToFast_ClearLakey.over = "yes";
			}			
			if(pchar.questTemp.ReasonToFast == "PatrolSuccess_2") 
			{ 
				// получена карта
				dialog.text = "Köszönöm! Le fogom tartóztatni azt a gazembert.\nGondolj csak bele! Épp azon voltam, hogy a tizedik szolgálati évéért aranyhegyû szablyával tüntessem ki! Megmentettél egy komoly blamázstól!";
				link.l2 = "Az igazságszolgáltatás a maga jutalma.";
				link.l2.go = "ReasonToFast_GMayor_21";			
			}
			if(pchar.questTemp.ReasonToFast == "PatrolDied") 
			{ 
				// патруль перебит
				dialog.text = "Mis"+ GetSexPhrase("ter","s") +" de Maure, nem lehet csak úgy, tanúk nélkül megölni egy gyanúsítottat! Most még bizonyítékot sem tudunk szerezni a bûncselekményeirôl! Csak így tudom megakadályozni, hogy letartóztassanak emberölésért.";
				link.l3 = "Avast, önvédelem volt, excellenciás uram.";
				link.l3.go = "ReasonToFast_GMayor_31";
				pchar.questTemp.ReasonToFast.speakAfterPatrolDied = true;	
				pchar.quest.ReasonToFast_SpeakMayor.over = "yes";
			}			
		break;
		
		case "ReasonToFast_BMayor":
			if(pchar.questTemp.ReasonToFast == "PatrolSuccess_1") 
			{ 				
				dialog.text = "Kapitány, felfogtad, hogy mi a faszt tettél?!!! Már több mint egy hónapja állítottam fel ezt a csapdát! És most, csak a saját szórakoztatásodra, tönkretetted az ôrjáratunk találkozóját a " + GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_GEN) + " és most idejössz, hogy ezzel dicsekedj?!!! Talán most már meg tudod mondani, hogy mivel magyarázzam meg ennek az akciónak a költségeit és kiadásait?!";
				link.l1 = "Felség, én csak megoldottam a problémádat, ha úgy nézzük, egész idô alatt neked kellett volna fizetned nekem!";
				link.l1.go = "ReasonToFast_BMayor_1";
				pchar.questTemp.ReasonToFast = "speakSuccess_chain_A";				
				if(pchar.questTemp.ReasonToFast.chain == "A0") ReasonToFast_RemoveVictim();
				if(pchar.questTemp.ReasonToFast.chain == "A1") pchar.quest.ReasonToFast_ClearLakey.over = "yes";
			}
			if(pchar.questTemp.ReasonToFast == "PatrolSuccess_2") 
			{ 
				// получена карта
				dialog.text = "Hadd lássam ezt a térképet\nEz most komolyan mondod? Ez a rongyos papírdarab a bizonyíték?";
				link.l2 = "Ugyan már, kegyelmes uram, legyen észnél.";
				link.l2.go = "ReasonToFast_BMayor_1";
				TakeItemFromCharacter(pchar, "mapQuest");				
				pchar.questTemp.ReasonToFast = "speakSuccess_chain_B";
			}
			if(pchar.questTemp.ReasonToFast == "PatrolDied") 
			{ 
				// патруль перебит
				dialog.text = "Nocsak, nocsak, most már tudjuk, mi történt az ôrjáratommal. Legalább azzal, hogy idejöttél, megkíméltél minket attól, hogy a gyilkost keressük.";
				link.l3 = "Felség! Csak nem akarja megérteni a lényeget...";
				link.l3.go = "ReasonToFast_BMayor_1";			
				pchar.questTemp.ReasonToFast = "speakSuccess_chain_A";
				pchar.quest.ReasonToFast_SpeakMayor.over = "yes";
			}		
		break;
		
		case "ReasonToFast_GMayor_11":
			dialog.text = "Lehet, hogy idióta vagy, de legalább hasznos idióta. Tessék - fogd ezt a térképet; egy kalóznál találtam, akit a múlt héten akasztottunk fel. Ha Isten is úgy akarja, talán megtalálod a kincsét, bár ezt elég valószínûtlennek tartom...";
			link.l1 = "Köszönöm, ez nagyon nagylelkû tôled!";
			link.l1.go = "exit";
			AddQuestRecord("ReasonToFast", "15");
			ChangeCharacterComplexReputation(pchar,"nobility", 1); 
			GiveItem2Character(pchar, "mapQuest"); 
			arItem = ItemsFromID("mapQuest");
			ReasonToFast_GenerateTreasureMap(arItem);
			pchar.questTemp.ReasonToFast.state = "chain_A"; // вилка_А, наводки не генерим
			pchar.questTemp.ReasonToFast = "GetMap";			
			ReasonToFast_SetHunterCoastal();
		break;
		
		case "ReasonToFast_GMayor_21":
			dialog.text = "Dicséretes a buzgalmad. Kérlek, fogadd el ezt a kardot jutalmul - ez a legkevesebb, amit tehetek. Ó, és a térképet megtarthatod magadnak. Biztos vagyok benne, hogy sok ilyen hamisítvány van a Karib-tengeren.";
			link.l1 = "Köszönöm, ez nagyon nagylelkû tôled!";
			link.l1.go = "exit";
			AddQuestRecord("ReasonToFast", "14");
			ChangeCharacterComplexReputation(pchar,"nobility", 1); 
			GiveItem2Character(pchar, pchar.questTemp.ReasonToFast.p6);
			pchar.questTemp.ReasonToFast.state = "chain_B"; // была получена карта
			pchar.questTemp.ReasonToFast = "GetMap";			
			ReasonToFast_SetHunterCoastal();
		break;
		case "ReasonToFast_GMayor_31":
			dialog.text = "Talán, talán... Nos, mondjuk úgy, hogy ezt az üzletet az isteni igazságszolgáltatás és a mi Urunk akarata döntötte el.";
			link.l1 = "Köszönöm, ez nagyon nagylelkû tôled!";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar,"nobility", 1); 
			AddQuestRecord("ReasonToFast", "16");
			CloseQuestHeader("ReasonToFast");
			DeleteAttribute(pchar,"ReasonToFast");
		break;
		
		case "ReasonToFast_BMayor_1":
			dialog.text = "Fogd be a szád, fiam! Vagy ôrült vagy, vagy az ellenségeinkkel szövetkezel! Ôrség, fogjátok el ezt az idiótát!";
			link.l1 = "Ha kezet emelsz rám, elveszíted!";
			link.l1.go = "fight";
		
			pchar.quest.ReasonToFast_ExitFromTown.win_condition.l1			= "EnterToSea";           	
            pchar.quest.ReasonToFast_ExitFromTown.function    				= "ReasonToFast_ExitFromTownFight";						
			pchar.questTemp.ReasonToFast.canSpeakSailor = true;
			pchar.TownEscape = true;
			Flag_PIRATE();
		break;
		
		// ------------------------- Повод для спешки -----------------------------
		
		// --------------------------Операция 'Галеон'-----------------------------
		case "CapComission_Mayor1":
			dialog.text = "Ez most lehetetlen. Letartóztatásban van és a tárgyalásra vár.";
			link.l1 = "Tényleg? És mivel gyanúsítják?";			
			link.l1.go = "CapComission_Mayor2";
		break;
		
		case "CapComission_Mayor2":
			dialog.text = "Sajnos, ez nem gyanú, hanem bizonyított tény. Információink szerint járôrözésnek álcázva hajókat fosztogatott. Kereskedôktôl árut kobzott el, majd csempészeknek és kalózoknak adta el. Kár... ha belegondolunk, hogy egykor az egyik legjobb kapitánynak tartották, akit a Korona rendelkezett...";
			link.l1 = "És ki szolgáltatta a bizonyítékot?";
			link.l1.go = "CapComission_Mayor3";				
		break;
		
		case "CapComission_Mayor3":
			dialog.text = "Egyik áldozata jelentést írt, amelyben részletesen leírta az esetet, beleértve a dátumot, a megtámadott hajó nevét és az elkobzott áruk mennyiségét. " +
				"Higgye el, a számok elég lenyûgözôek. Azon a napon járôr " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"név"))) + " kapitány " + pchar.GenQuest.CaptainComission.Name + " valóban szolgálatban volt. A kapitány a jelentésében az esetet kalózhajóval való találkozásként írta le, de rakományt egyáltalán nem említett.";
			link.l1 = "De volt egyáltalán rakomány?";
			link.l1.go = "CapComission_Mayor4";
			pchar.GenQuest.CaptainComission.SpeakMayor = true;
		break;
		
		case "CapComission_Mayor4":
			dialog.text = "Ez nem kétséges. A sértett fél nagyon ismert ember, és nem alázná meg magát rágalmazással és becsületsértéssel. Jelenleg járôreink a kapitány rejtekhelyét keresik. " +
				"Amint megtalálják, a kapitány megjelenhet a bíróságon\nHa ebben az ügyben segítséget nyújt nekünk, nagyon hálásak leszünk önnek.";
			link.l1 = "Valószínûleg nem. Nem ismerem eléggé a környéket ahhoz, hogy egy rejtekhelyet keressek. Elnézést, mennem kell.";
			link.l1.go = "CapComission_Mayor5";
			link.l2 = "Talán... Mennyi idôm van még?";
			link.l2.go = "CapComission_Mayor6";	
		break;
		
		case "CapComission_Mayor5":
			AddQuestRecord("CaptainComission2", "49");
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Gen")));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			pchar.GenQuest.CaptainComission = "MayorTalkBad";
			CaptainComission_GenerateCaptainInPrison();
			DialogExit();
		break;
		
		case "CapComission_Mayor6":
			dialog.text = "Úgy vélem, hogy két nap múlva az ôrjáratok a maga segítsége nélkül is megtalálják a rejtekhelyet, úgyhogy igyekeznie kellene."; 
			link.l1 = "Igen, rajta vagyok. De meg kell látogatnom a " + pchar.GenQuest.CaptainComission.Name + "kapitányt. Meg lehet ezt oldani?";
			link.l1.go = "CapComission_Mayor7";
		break;
		
		case "CapComission_Mayor7":
			dialog.text = "Nem lesz gond. Tájékoztatom az erôd parancsnokát a látogatásodról.";
			link.l1 = "Köszönöm, uram. Most pedig, kérem, bocsásson meg.";
			link.l1.go = "CapComission_Mayor8";
		break;
		
		case "CapComission_Mayor8":
			AddQuestRecord("CaptainComission2", "50");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sSex1", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Gen")));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);			
			AddQuestUserData("CaptainComission2", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			OfficersReaction("good");
			pchar.GenQuest.CaptainComission.MayorTalkGood = true;
			pchar.GenQuest.CaptainComission = "MayorTalkGood";
			pchar.quest.CaptainComission_TimeIsOver.over = "yes";
			SetFunctionTimerConditionParam("CaptainComission_GetSecretTimeIsOut", 0, 0, 2, MakeInt(24 - GetHour()), false);
			CaptainComission_GenerateCaptainInPrison();
			DialogExit();
		break;
		
		case "CapComission_Mayor9":
			dialog.text = "Kitûnô! Hol van a kincs?";
			link.l1 = "Még fogalmam sincs. Nem mutatta meg a pontos helyet.";
			link.l1.go = "CapComission_Mayor10";
		break;
		
		case "CapComission_Mayor10":
			dialog.text = "Hmm, micsoda véletlen! Tudod, ô 'nem mutatott' nem mutatta meg a pontos helyet...";
			link.l1 = "Dolgozom rajta.";
			link.l1.go = "CapComission_Mayor11";
		break;
		
		case "CapComission_Mayor11":
			dialog.text = "Not anymore\nGuards! Vigyétek vissza a foglyot a kamrákba\nSzabadon távozhattok, " + GetFullName(pchar) + ".";
			link.l1 = "De a kormányzó...";
			link.l1.go = "CapComission_Mayor12";
		break;
		
		case "CapComission_Mayor12":
			sld = CharacterFromID("CapComission_1");
			sld.lifeDay = 0;
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_SetActorType(sld);
            LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", -1);			
			pchar.quest.CapComission_DeletePrisonGroup.win_condition.l1 = "ExitFromLocation";
            pchar.quest.CapComission_DeletePrisonGroup.win_condition.l1.location = pchar.location;
            pchar.quest.CapComission_DeletePrisonGroup.win_condition = "CaptainComission_DeletePrisonGroup";									
			ChangeOfficersLoyality("bad_all", 1);
			ChangeCharacterComplexReputation(pchar,"nobility", -4);			
			AddQuestRecord("CaptainComission2", "23");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("CaptainComission2");
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			DialogExit();
		break;
		
		case "CapComission_Mayor13":
			pchar.quest.CaptainComission_SpeakMayorGoods.over = "yes";
			dialog.text = "Kitûnô! És hol fogjuk keresni a kincsét?";
			link.l1 = "A " + RandPhraseSimple(RandPhraseSimple("északi","nyugati"),RandPhraseSimple("keleti","déli")) + " végében " + XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Gen") + " a szikla lábánál van egy nagy fülke, amelynek bejárata kövekkel van kirakva. Ez a rejtekhely.";
			link.l1.go = "CapComission_Mayor14";
		break;
		
		case "CapComission_Mayor14":
			dialog.text = "Kiváló munka! És hol van maga a " + pchar.GenQuest.CaptainComission.Name + " ? Azt mondták, hogy az erôd börtönébôl hoztátok el.";
			link.l1 = "Sajnos, elpusztult a csempészekkel való csetepatéban.";
			link.l1.go = "CapComission_Mayor15";
		break;
		
		case "CapComission_Mayor15":
			dialog.text = "Ez rossz... Ez nagyon rossz, "+ GetSexPhrase("mister","miss") +" " + GetFullName(pchar) + ". Nyilvánosan akartam kivégezni, 'hogy bátorítsam a többieket.'" + 
				"úgy sem kerülte volna el a bitófát\nSzóval, mivel technikailag megszegte a törvényt, törvénytelenül engedett szabadon egy foglyot, de mégsem mentette meg, ezt nem tudom javítani a jelentésben. Ezért nem kapsz jutalmat... De személyesen szeretném megköszönni. Fogadja el az ajándékomat - egy harcoló kapitány számára nagyon hasznos dolog. ";
			link.l1 = "Köszönöm. Mindig örömmel szolgálok.";	
			link.l1.go = "CapComission_Mayor16";
		break;
		
		case "CapComission_Mayor16":
			AddQuestRecord("CaptainComission2", "30");
			AddQuestUserData("CaptainComission2", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			CloseQuestHeader("CaptainComission2");
			GiveItem2Character(pchar, pchar.GenQuest.CaptainComission.Prize);
			ChangeCharacterComplexReputation(pchar,"nobility", 4);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 10);
			OfficersReaction("good");
			DeleteAttribute(pchar,"GenQuest.CaptainComission.MayorTalkGood");
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			DialogExit();
		break;
		// --------------------------Операция 'Галеон'-----------------------------
		
		// -------------------------- Генератор "Кораблекрушенцы" ------------
		case "ShipWreck1":
			if(iDay > 15)
			{
				dialog.text = RandPhraseSimple("Hogyan csinálod? Legalább tizenöt napba telik eljutni oda, még akkor is, ha széllel együtt hajózunk!","Kapitány " + GetFullName(pchar) + ", a felelôtlenséged megdöbbent! Miért nem szóltál nekem errôl korábban?");
				link.l1 = "Hát, nem is tudom, mit mondjak...";
				link.l1.go = "ShipWreck2";
			}
			else
			{
				dialog.text = "Ez nagyszerû hír! Már elvesztettük a reményt, hogy a " + pchar.GenQuest.ShipWreck.Name + "  újra életben látjuk. Azonnal küldök egy mentôcsapatot. Ó, és kérem, fogadja el ezt a jutalmat a mentésben való hatékonyságáért és részvételéért.";
				link.l1 = "Köszönöm, Felség. Örülök, hogy segíthettem. Biztos vagyok benne, hogy az expedíció idôben odaér.";
				link.l1.go = "ShipWreck3";	
			}
			pchar.GenQuest.ShipWreck.SpeakMayor = true;
			pchar.quest.ShipWreck_MeetInShore.over = "yes";
			pchar.quest.ShipWreck_SaveSailors.over = "yes"; // belamour gen таймер на 30 дней тоже нужно снять
		break;
		
		case "ShipWreck2":
			dialog.text = "Wow....Mit is mondhatnék még? Menj, és tanulmányozd a tengerjogot, fiú! Mindegy, mindent megteszek, hogy megmentsem ezeket az embereket.";
			link.l1 = "Felség, de elég élelmet hagytam nekik. Van idôd, biztosíthatlak...";
			link.l1.go = "ShipWreck4";
		break;
		
		case "ShipWreck3":
			addMoneyToCharacter(pchar, sti(pchar.rank) * 300 + 3000 + rand(3000));
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
			AddQuestRecord("ShipWrecked", "14");
			AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("",""));
			AddQuestUserData("ShipWrecked", "sCity", XI_ConvertString("Colony" + NPChar.city + "Gen")); // belamour gen просто NPChar.city ничего не даст
			AddQuestUserData("ShipWrecked", "ShoreName", XI_ConvertString(pchar.GenQuest.ShipWreck.Shore + "Gen")); // belamour gen
			CloseQuestHeader("ShipWrecked");
			DeleteAttribute(pchar, "GenQuest.ShipWreck.SpeakMayor");		
			DialogExit();
			AddDialogExitQuest("ShipWreck_RemoveSailorsFromShore");
		break;		
		
		case "ShipWreck4":
			ChangeCharacterComplexReputation(pchar,"nobility", -5);
			AddQuestRecord("ShipWrecked", "13");
			AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("",""));
			AddQuestUserData("ShipWrecked", "sCity", XI_ConvertString("Colony" + NPChar.city + "Gen")); // belamour gen просто NPChar.city ничего не даст
			AddQuestUserData("ShipWrecked", "ShoreName", XI_ConvertString(pchar.GenQuest.ShipWreck.Shore + "Gen")); // belamour gen
			CloseQuestHeader("ShipWrecked");
			DeleteAttribute(pchar, "GenQuest.ShipWreck.SpeakMayor");		
			DialogExit();
			AddDialogExitQuest("ShipWreck_RemoveSailorsFromShore");
		break;
		// -------------------------- Генератор "Кораблекрушенцы" ------------
		
		// ---------------------- найти кольцо в борделе ----------------------------
		case "TakeRing_1":
			dialog.text = "Tudom, hogy te, hogy is mondjam... "+ GetSexPhrase("bordélyházak törzsvendége vagy","szeretsz idônként bordélyházakat látogatni") +". És ezért úgy döntöttem, hogy segítségért fordulok önhöz\n"+
				"Tudja, szégyellem bevallani, de nemrég jártam ott...";
			link.l1 = "És mi a baj vele? A szex egy teljesen természetes dolog, tudod...";
			link.l1.go = "TakeRing_2";
		break;
		case "TakeRing_2":
			dialog.text = "Ó, nem, nem prédikálok, nem. A helyzet az, hogy egy alkalommal túl sokat ittam, és elvesztettem a jegygyûrûmet...";
			link.l1 = "Na, ez már probléma. Sajnálom.";
			link.l1.go = "TakeRing_3";
		break;
		case "TakeRing_3":
			dialog.text = "Nincs szükségem arra, hogy bárki is sajnáljon engem. Vissza kell kapnom a gyûrûmet. Ha sikerül visszaszerezned éjfél elôtt, nagyon nagylelkû leszek. Ha nem sikerül, a feleségem megöl.";
			link.l1 = "Értem... És pontosan hol veszíthetted el? Emlékszik valamire konkrétan?";
			link.l1.go = "TakeRing_4";
		break;
		case "TakeRing_4":
			dialog.text = "Sajnos, nem. Semmire.";
			link.l1 = "Értem. Nos, akkor keressük meg.";
			link.l1.go = "TakeRing_5";
			link.l2 = "Tudod, " + GetAddress_FormToNPC(NPChar) + ", azt hiszem, ezt inkább kihagyom. Kérem, bocsásson meg...";
			link.l2.go = "TakeRing_6";
		break;	
		case "TakeRing_5":
			dialog.text = "Kitûnô! De ne feledd - éjfél elôtt meg kell találnod.";
			link.l1 = "Emlékszem. Hamarosan visszajövök.";
			link.l1.go = "exit";
			pchar.questTemp.different = "TakeMayorsRing";
			pchar.questTemp.different.TakeMayorsRing = "toBrothel";
			pchar.questTemp.different.TakeMayorsRing.Id = GetFullName(npchar);
			pchar.questTemp.different.TakeMayorsRing.city = npchar.city;	
			pchar.questTemp.different.TakeMayorsRing.price = sti(pchar.rank)*100+1000;
			sld = ItemsFromID("MayorsRing");
			sld.CityName = XI_ConvertString("Colony" + npchar.city + "Gen");
			//ложим кольцо в итем
			if (rand(3) != 2)
			{				
				switch (rand(2))
				{
					case 0: sTemp = "_Brothel_room";  break;
					case 1: sTemp = "_Brothel";  break;
					case 2: sTemp = "_SecBrRoom";  break;
				}
				sld.shown = true;
				sld.startLocation = pchar.questTemp.different.TakeMayorsRing.city + sTemp;
				sld.startLocator = "item" + (rand(4)+1);
				pchar.questTemp.different.TakeMayorsRing.item = true; //флаг кольцо валяется в итемах
				Log_QuestInfo("The ring is at " + sld.startLocation + ", in locator " + sld.startLocator);
			}
			SetTimerFunction("TakeMayorsRing_null", 0, 0, 1); //освобождаем разрешалку на миниквесты 
			ReOpenQuestHeader("SeekMayorsRing");
			AddQuestRecord("SeekMayorsRing", "1");
			AddQuestUserData("SeekMayorsRing", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData("SeekMayorsRing", "sName", pchar.questTemp.different.TakeMayorsRing.Id);
		break;	
		case "TakeRing_6":
			dialog.text = "Ó? Hát, ez igazán váratlanul ért... Nos, akkor sok szerencsét, kapitány.";
			link.l1 = "Ég veled!";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
		break;

		case "TakeRing_S1":
			dialog.text = "Ez az én gyûrûm! Megmentette az életemet!";
			link.l1 = "Semmiség, uram.";
			link.l1.go = "TakeRing_S2";
			TakeItemFromCharacter(pchar, "MayorsRing");
		break;
		case "TakeRing_S2":
			dialog.text = "Itt a pénze a jól végzett munkáért! Nagyon hálás vagyok önnek!";
			link.l1 = "Örülök, hogy segíthettem, uram, de kérem, legközelebb legyen óvatosabb.";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar,"nobility", 5);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 10);
			AddCharacterExpToSkill(pchar, "Leadership", 50);
			AddCharacterExpToSkill(pchar, "Fortune", 50);
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.different.TakeMayorsRing.price));
			pchar.questTemp.different = "free";
			pchar.quest.TakeMayorsRing_null.over = "yes"; //снимаем таймер
			AddQuestRecord("SeekMayorsRing", "7");
			AddQuestUserData("SeekMayorsRing", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			CloseQuestHeader("SeekMayorsRing");
			DeleteAttribute(pchar, "questTemp.different.TakeMayorsRing");
		break;
		case "TakeRing_S3":
			dialog.text = "Uram, könyörülj rajtam! Tényleg abba kéne hagynom az ivást...";
			link.l1 = "Az biztos! Itt a gyûrûje.";
			link.l1.go = "TakeRing_S4";
		break;
		case "TakeRing_S4":
			dialog.text = "Igen, igen, köszönöm szépen. Az adósod vagyok! Itt a pénzed a jól végzett munkáért!";
			link.l1 = "Köszönöm " + GetAddress_FormToNPC(NPChar) + ".";
			link.l1.go = "exit";
			TakeItemFromCharacter(pchar, "MayorsRing");
			ChangeCharacterComplexReputation(pchar,"nobility", 3);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 3);
			AddCharacterExpToSkill(pchar, "Leadership", 50);
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.different.TakeMayorsRing.price));
			pchar.questTemp.different = "free";
			pchar.quest.TakeMayorsRing_null.over = "yes"; //снимаем таймер
			AddQuestRecord("SeekMayorsRing", "7");
			AddQuestUserData("SeekMayorsRing", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			CloseQuestHeader("SeekMayorsRing");
			DeleteAttribute(pchar, "questTemp.different.TakeMayorsRing");
		break;
		// ---------------------- найти кольцо в борделе ----------------------------

		case "node_1":
            //ОСАДЫ homo
			if (CheckAttribute(&Colonies[FindColony(npchar.City)],"Siege"))
            {

                makearef(aData, NullCharacter.Siege);
                

                if (CheckAttribute(aData, "HelpColony") && sti(aData.HelpColony) == true )
                {
                    dialog.text = "Már mindent megbeszéltünk, nem igaz?";
                    link.l1 = "Igen, így van. Nem akarom tovább feltartani.";
                    link.l1.go = "exit";

                }
                else
                {
                    dialog.text = "Sajnálom, hogy felzaklatlak, de most nincs idôm beszélgetni veled. Mint tudnod kell, a kolóniánkat megtámadta a "+NationNamePeople(sti(aData.nation))+". Gondoskodnom kell a védelmünkrôl.";
                    link.l1 = "Nos, csak fel akartam ajánlani a segítségemet az erôd védelmében.";
                    link.l1.go = "siege_task";
                    link.l2 = "Akkor nem fogom tovább feltartani.";
        			link.l2.go = "exit";
                }
            }
            else
            {//->
                makearef(aData, NullCharacter.Siege);
                if (CheckAttribute(aData, "PlayerHelpMayor") && sti(aData.PlayerHelpMayor) == true
                && CheckAttribute(aData, "HelpColony") && sti(aData.HelpColony) == true )
                {
                    AddMoneyToCharacter(Pchar,(sti(aData.iSquadronPower)*3000));
                    ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 20);
                    ChangeCharacterComplexReputation(pchar,"nobility", 10);
                    AddCharacterExpToSkill(GetMainCharacter(), "Leadership", 180);
                    AddCharacterExpToSkill(GetMainCharacter(), "Sailing", 200);
                    AddCharacterExpToSkill(GetMainCharacter(), "Accuracy", 200);
                    AddCharacterExpToSkill(GetMainCharacter(), "Cannons", 200);
                    //--> слухи
                    SiegeRumour("They say that you had helped us to repel the "+NationNameSK(sti(aData.nation))+" squadron and defend our colony! We are grateful to you, "+ GetAddress_Form(NPChar)+".", aData.Colony, sti(aData.conation), -1, 15, 3);
		            //<-- слухи
                    DeleteAttribute(aData, "PlayerHelpMayor");
                    DeleteAttribute(aData, "HelpColony");
                    dialog.text = "Ó, te vagy az, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+", örülök, hogy látlak. Jó hírek - sikerült visszavernünk a "+NationNameSK(sti(aData.nation))+" betolakodókat. Te is kivetted a részed ebbôl, és itt a jutalmad - "+(sti(aData.iSquadronPower)*1500)+" pezó. Tessék.";
                    link.l1 = "Köszönöm, " + GetAddress_FormToNPC(NPChar) + ", öröm veled üzletelni!";
                    link.l1.go = "exit";
                }
                else
                {
                    if (CheckAttribute(aData, "PlayerHelpMayor")) DeleteAttribute(aData, "PlayerHelpMayor");
                    dialog.text = "Szóval mi volt az oka, hogy idejöttél és elvonod a figyelmemet a fontos államügyekrôl?";
					if (npchar.city != "Panama") // Addon-2016 Jason
					{
						link.l1 = "A "+ NationNameGenitive(sti(NPChar.nation))+"akartam dolgozni.";
						link.l1.go = "work";
					}
					// Warship Генер "Пираты на необитайке" - сдаём пиратов властям
					if(CheckAttribute(PChar, "Quest.PiratesOnUninhabited_OnShore") || CheckAttribute(PChar, "Quest.PiratesOnUninhabited_ShipSink"))
					{
						link.l11 = XI_ConvertString(PChar.GenQuest.PiratesOnUninhabited.StartShore + "Dat") + " Találkoztam néhány kalózzal. Mind " + PChar.GenQuest.PiratesOnUninhabited.PiratesCount + " a fedélzeten vannak jelenleg. Át akarom adni ôket a hatóságoknak.";
						link.l11.go = "PiratesOnUninhabited_1";
					}
					
        			link.l2 = "Egy fontos ügyrôl akartam beszélni önnel.";
					if(CheckAttribute(pchar,"questTemp.ReasonToFast") && !CheckAttribute(pchar,"questTemp.ReasonToFast.SpeakOther") && !CheckAttribute(pchar, "questTemp.ReasonToFast.cantSpeakOther") && (pchar.questTemp.ReasonToFast.city == NPChar.city))
					{
						link.l2.go = "ReasonToFast_Mayor1";
					}
					else
					{					
						link.l2.go = "quests";
					}	
					if(CheckAttribute(pchar,"GenQuest.CaptainComission") && (pchar.GenQuest.CaptainComission.variant == "A2") && (pchar.GenQuest.CaptainComission.City == NPChar.city))
					{
						if(pchar.GenQuest.CaptainComission == "Begin_1" && !CheckAttribute(pchar,"GenQuest.CaptainComission.SpeakMayor")) 
						{
							link.l12 = "Van egy kapitány a járôr parancsnoka " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"név") + "Acc")) + " nevû " + pchar.GenQuest.CaptainComission.Name + ", hogyan találkozhatok vele?";
							link.l12.go = "CapComission_Mayor1";
						}	
						if(CheckAttribute(pchar,"GenQuest.CaptainComission.PrisonFree"))
						{
							link.l12 = "A járôrszolgálatot irányító egykori kapitány " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"név") + "Acc")) + " " + pchar.GenQuest.CaptainComission.Name + " beleegyezett, hogy felfedje a rejtekhelyét a hatóságoknak.";
							link.l12.go = "CapComission_Mayor9";
						}
						if(pchar.GenQuest.CaptainComission == "GetGoodsSuccess")
						{
							link.l12 = "A járôrszolgálatot irányító volt kapitány  " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"név") + "Acc")) + " " + pchar.GenQuest.CaptainComission.Name + " felfedte elôttem a rejtekhelyét.";
							link.l12.go = "CapComission_Mayor13";
						}
					}
					if(CheckAttribute(pchar,"GenQuest.ShipWreck") && pchar.GenQuest.ShipWreck == "SailorsOnShore" && GetQuestPastDayParam("GenQuest.ShipWreck") < 25 && sti(npchar.nation) == sti(pchar.GenQuest.ShipWreck.Nation))
					{
						if(!CheckAttribute(pchar,"GenQuest.ShipWreck.SpeakMayor"))
						{
							iDay = GetQuestPastDayParam("GenQuest.ShipWreck");
							if(CheckAttribute(pchar, "GenQuest.ShipWreck.Mutiny"))
							{
								link.l13 = UpperFirst(XI_ConvertString(pchar.GenQuest.ShipWreck.Shore + "Dat")) + " Találkoztam egy kapitánnyal " + pchar.GenQuest.ShipWreck.Name + " és matrózaival, akiket a kalóz " + pchar.GenQuest.ShipWreck.BadName + "partra vetett. " +
									"sajnos már túl sok ember volt a hajón, ezért nem tudtam ôket a fedélzetre venni. De élelmet és fegyvert hagytam nekik. Ha a mentôhajó nem veszi fel ôket " + (30 - iDay) + " napokon belül, akkor nem tudom, hogy még életben találja-e ôket vagy sem.";
								link.l13.go = "ShipWreck1";
							}
							else
							{
								link.l13 = UpperFirst(XI_ConvertString(pchar.GenQuest.ShipWreck.Shore + "Dat")) + " Találkoztam egy áldozatul esett hajóroncs tengerészeivel '" + pchar.GenQuest.ShipWreck.ShipTypeName + "' kapitányukkal. " + 
									"Sajnos, már túl sok ember volt a hajón, ezért nem tudtam ôket felvenni a fedélzetre. De élelmet és fegyvert hagytam nekik. Ha a mentôhajó nem veszi fel ôket " + (30 - iDay) + " napon belül, akkor nem tudom, hogy még életben találja-e ôket vagy sem.";
								link.l13.go = "ShipWreck1";							
							}	
						}	
					}					
					//--> Jason, генер почтового курьера 2 уровня
						if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.LevelUp"))
						{
							if (pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
							{
							link.l14 = "Üzenetem van a "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen")+"városból.";
							link.l14.go = "Postcureer_LevelUp_ForAll";
							}
						}
					//<-- генер почтового курьера 2 уровня
					
					// --> Warship, 16.05.11. Квест "Правосудие на продажу".
					if(CheckAttribute(PChar, "GenQuest.JusticeOnSale.MayorWait") && CheckAttribute(PChar, "GenQuest.JusticeOnSale.CityId") && NPChar.location == PChar.GenQuest.JusticeOnSale.CityId + "_townhall")
					{
						link.l15 = "Uram, megtaláltam egy csempészbandát, amelynek vezetôjét nemrég fogták el az ôrök. Most a szökését tervezik. A hajójuk '" + PChar.GenQuest.JusticeOnSale.ShipName + "' a " + XI_ConvertString(PChar.GenQuest.JusticeOnSale.ShoreId + "Gen") + "kikötôben van.";
						link.l15.go = "JusticeOnSale_1";
					}
					//<-- Правосудие на продажу
					
        			if (GetPrisonerQty() > 0)
        			{
                        link.l3 = "Át kell adnom a foglyul ejtett kapitányt a hatóságoknak.";
        			    link.l3.go = "sell_prisoner";
        			}
					//Jason --> Регата
					if (CheckAttribute(pchar, "questTemp.Regata.ToPortRoyal") && NPChar.location == "Portroyal_townhall")
					{
						link.l4 = "A regattára jöttem. Itt a meghívóm.";
						link.l4.go = "Regata";
					}
        			link.l5 = "Talán szeretnél egy kis szünetet tartani?";
        			link.l5.go = "Play_Game";
        			link.l10 = "Ez csak egy udvariassági látogatás volt, " + GetAddress_FormToNPC(NPChar) + ".";
        			link.l10.go = "node_2";
                }
    		}//<-
		break;
		
		case "Helen_node_1":
            //ОСАДЫ homo
			if (CheckAttribute(&Colonies[FindColony(npchar.City)],"Siege"))
            {

                makearef(aData, NullCharacter.Siege);
                

                if (CheckAttribute(aData, "HelpColony") && sti(aData.HelpColony) == true )
                {
                    dialog.text = "Már mindent megbeszéltünk, nem igaz?";
                    link.l1 = "Igen, így van. Nem akarom tovább feltartani.";
                    link.l1.go = "exit";

                }
                else
                {
                    dialog.text = "Sajnálom, hogy felzaklatlak, de most nincs idôm beszélgetni veled. Mint tudnod kell, a kolóniánkat megtámadta a "+NationNamePeople(sti(aData.nation))+". Gondoskodnom kell a védelmünkrôl.";
                    link.l1 = "Nos, csak fel akartam ajánlani a segítségemet az erôd védelmében.";
                    link.l1.go = "siege_task";
                    link.l2 = "Akkor nem fogom tovább feltartani.";
        			link.l2.go = "exit";
                }
            }
            else
            {//->
                makearef(aData, NullCharacter.Siege);
                if (CheckAttribute(aData, "PlayerHelpMayor") && sti(aData.PlayerHelpMayor) == true
                && CheckAttribute(aData, "HelpColony") && sti(aData.HelpColony) == true )
                {
                    AddMoneyToCharacter(Pchar,(sti(aData.iSquadronPower)*3000));
                    ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 20);
                    ChangeCharacterComplexReputation(pchar,"nobility", 10);
                    AddCharacterExpToSkill(GetMainCharacter(), "Leadership", 180);
                    AddCharacterExpToSkill(GetMainCharacter(), "Sailing", 200);
                    AddCharacterExpToSkill(GetMainCharacter(), "Accuracy", 200);
                    AddCharacterExpToSkill(GetMainCharacter(), "Cannons", 200);
                    //--> слухи
                    SiegeRumour("They say that you had helped us to repel the "+NationNameSK(sti(aData.nation))+" squadron and defend our colony! We are grateful to you, "+ GetAddress_Form(NPChar)+".", aData.Colony, sti(aData.conation), -1, 15, 3);
		            //<-- слухи
                    DeleteAttribute(aData, "PlayerHelpMayor");
                    DeleteAttribute(aData, "HelpColony");
                    dialog.text = "Ó, te vagy az, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+", örülök, hogy látlak. Jó hírek - sikerült visszavernünk a "+NationNameSK(sti(aData.nation))+" betolakodókat. Te is kivetted a részed ebbôl, és itt a jutalmad - "+(sti(aData.iSquadronPower)*1500)+" pezó. Tessék.";
                    link.l1 = "Köszönöm, " + GetAddress_FormToNPC(NPChar) + ", öröm veled üzletelni!";
                    link.l1.go = "exit";
                }
                else
                {
                    if (CheckAttribute(aData, "PlayerHelpMayor")) DeleteAttribute(aData, "PlayerHelpMayor");
                    dialog.text = "Mi szél hozta ide? Azt hittem, hogy minden ügyedet elintézted a... patrónusoddal. De beszélj, mindig szívesen meghallgatlak.";
					if (npchar.city != "Panama") // Addon-2016 Jason
					{
						link.l1 = "A "+ NationNameGenitive(sti(NPChar.nation))+"akartam dolgozni.";
						link.l1.go = "work";
					}
					// Warship Генер "Пираты на необитайке" - сдаём пиратов властям
					if(CheckAttribute(PChar, "Quest.PiratesOnUninhabited_OnShore") || CheckAttribute(PChar, "Quest.PiratesOnUninhabited_ShipSink"))
					{
						link.l11 = XI_ConvertString(PChar.GenQuest.PiratesOnUninhabited.StartShore + "Dat") + " Találkoztam néhány kalózzal. Mind " + PChar.GenQuest.PiratesOnUninhabited.PiratesCount + " a fedélzeten vannak jelenleg. Át akarom adni ôket a hatóságoknak.";
						link.l11.go = "PiratesOnUninhabited_1";
					}
					
        			link.l2 = "Egy fontos ügyrôl akartam beszélni önnel.";
					if(CheckAttribute(pchar,"questTemp.ReasonToFast") && !CheckAttribute(pchar,"questTemp.ReasonToFast.SpeakOther") && !CheckAttribute(pchar, "questTemp.ReasonToFast.cantSpeakOther") && (pchar.questTemp.ReasonToFast.city == NPChar.city))
					{
						link.l2.go = "ReasonToFast_Mayor1";
					}
					else
					{					
						link.l2.go = "quests";
					}	
					if(CheckAttribute(pchar,"GenQuest.CaptainComission") && (pchar.GenQuest.CaptainComission.variant == "A2") && (pchar.GenQuest.CaptainComission.City == NPChar.city))
					{
						if(pchar.GenQuest.CaptainComission == "Begin_1" && !CheckAttribute(pchar,"GenQuest.CaptainComission.SpeakMayor")) 
						{
							link.l12 = "Van egy kapitány a járôr parancsnoka " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"név") + "Acc")) + " nevû " + pchar.GenQuest.CaptainComission.Name + ", hogyan találkozhatok vele?";
							link.l12.go = "CapComission_Mayor1";
						}	
						if(CheckAttribute(pchar,"GenQuest.CaptainComission.PrisonFree"))
						{
							link.l12 = "A járôrszolgálatot irányító egykori kapitány " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"név") + "Acc")) + " " + pchar.GenQuest.CaptainComission.Name + " beleegyezett, hogy felfedje a rejtekhelyét a hatóságoknak.";
							link.l12.go = "CapComission_Mayor9";
						}
						if(pchar.GenQuest.CaptainComission == "GetGoodsSuccess")
						{
							link.l12 = "A járôrszolgálatot irányító volt kapitány  " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"név") + "Acc")) + " " + pchar.GenQuest.CaptainComission.Name + " felfedte elôttem a rejtekhelyét.";
							link.l12.go = "CapComission_Mayor13";
						}
					}
					if(CheckAttribute(pchar,"GenQuest.ShipWreck") && pchar.GenQuest.ShipWreck == "SailorsOnShore" && GetQuestPastDayParam("GenQuest.ShipWreck") < 25 && sti(npchar.nation) == sti(pchar.GenQuest.ShipWreck.Nation))
					{
						if(!CheckAttribute(pchar,"GenQuest.ShipWreck.SpeakMayor"))
						{
							iDay = GetQuestPastDayParam("GenQuest.ShipWreck");
							if(CheckAttribute(pchar, "GenQuest.ShipWreck.Mutiny"))
							{
								link.l13 = UpperFirst(XI_ConvertString(pchar.GenQuest.ShipWreck.Shore + "Dat")) + " Találkoztam egy kapitánnyal " + pchar.GenQuest.ShipWreck.Name + " és matrózaival, akiket a kalóz " + pchar.GenQuest.ShipWreck.BadName + "partra vetett. " +
									"sajnos már túl sok ember volt a hajón, ezért nem tudtam ôket a fedélzetre venni. De élelmet és fegyvert hagytam nekik. Ha a mentôhajó nem veszi fel ôket " + (30 - iDay) + " napokon belül, akkor nem tudom, hogy még életben találja-e ôket vagy sem.";
								link.l13.go = "ShipWreck1";
							}
							else
							{
								link.l13 = UpperFirst(XI_ConvertString(pchar.GenQuest.ShipWreck.Shore + "Dat")) + " Találkoztam egy áldozatul esett hajóroncs tengerészeivel '" + pchar.GenQuest.ShipWreck.ShipTypeName + "' kapitányukkal. " + 
									"Sajnos, már túl sok ember volt a hajón, ezért nem tudtam ôket felvenni a fedélzetre. De élelmet és fegyvert hagytam nekik. Ha a mentôhajó nem veszi fel ôket " + (30 - iDay) + " napon belül, akkor nem tudom, hogy még életben találja-e ôket vagy sem.";
								link.l13.go = "ShipWreck1";							
							}	
						}	
					}					
					//--> Jason, генер почтового курьера 2 уровня
						if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.LevelUp"))
						{
							if (pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
							{
							link.l14 = "Üzenetem van a "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen")+"városból.";
							link.l14.go = "Postcureer_LevelUp_ForAll";
							}
						}
					//<-- генер почтового курьера 2 уровня
					
					// --> Warship, 16.05.11. Квест "Правосудие на продажу".
					if(CheckAttribute(PChar, "GenQuest.JusticeOnSale.MayorWait") && CheckAttribute(PChar, "GenQuest.JusticeOnSale.CityId") && NPChar.location == PChar.GenQuest.JusticeOnSale.CityId + "_townhall")
					{
						link.l15 = "Uram, megtaláltam egy csempészbandát, amelynek vezetôjét nemrég fogták el az ôrök. Most a szökését tervezik. A hajójuk '" + PChar.GenQuest.JusticeOnSale.ShipName + "' a " + XI_ConvertString(PChar.GenQuest.JusticeOnSale.ShoreId + "Gen") + "kikötôben van.";
						link.l15.go = "JusticeOnSale_1";
					}
					//<-- Правосудие на продажу
					
        			if (GetPrisonerQty() > 0)
        			{
                        link.l3 = "Át kell adnom a foglyul ejtett kapitányt a hatóságoknak.";
        			    link.l3.go = "sell_prisoner";
        			}
					//Jason --> Регата
					if (CheckAttribute(pchar, "questTemp.Regata.ToPortRoyal") && NPChar.location == "Portroyal_townhall")
					{
						link.l4 = "A regattára jöttem. Itt a meghívóm.";
						link.l4.go = "Regata";
					}
        			link.l5 = "Talán szeretnél egy kis szünetet tartani?";
        			link.l5.go = "Play_Game";
        			link.l10 = "Ez csak egy udvariassági látogatás volt, " + GetAddress_FormToNPC(NPChar) + ".";
        			link.l10.go = "node_2";
                }
    		}//<-
		break;
		
		case "Play_Game":
			//==> прибыла инспекция на Святом Милосердии
			if (CheckAttribute(npchar, "quest.SantaMisericordia"))
			{
    			dialog.text = "Ne most! Ellenôrzést tartunk, don de Alamida a városban van. Ó, minden évben ugyanaz, mivel érdemeltem ki ezt...";
				link.l1 = "Ahogy mondod. Nem akarom zavarni.";
				link.l1.go = "exit"; 
				break;
			}
			//<== прибыла инспекция на Святом Милосердии
			dialog.text = "Hmm, és milyen játékokat szeretsz?";
			link.l1 = "Akarsz kártyázni egy kis pénzért?";
			link.l1.go = "Card_Game";
   			link.l2 = "Mit szólnál egy kis kockadobáshoz póker-jokerben?";
			link.l2.go = "Dice_Game";
			link.l10 = "Kérem, bocsásson meg, de a kötelesség hív.";
			link.l10.go = "exit";
		break;
		
		//  карты -->
        case "Card_Game":
            if (!CheckNPCQuestDate(npchar, "Card_date_Yet") || sti(PChar.rank) < 4 || isBadReputation(pchar, 50) || GetCharacterSkillToOld(pchar, SKILL_LEADERSHIP) < rand(5))
            {
                SetNPCQuestDate(npchar, "Card_date_Yet");
				// belamour legendary edition фикс проверки мундира с мушкетом
				if(IsUniformEquip()) dialog.text = "Bocsásson meg, monsignore, de erre most nincs idôm. Talán majd legközelebb."; // Jason НСО
                else dialog.text = "Nem játszom kalózokkal!";
    			link.l1 = "Ahogy óhajtja.";
    			link.l1.go = "exit";
			}
			else
			{
				if (CheckNPCQuestDate(npchar, "Card_date_begin"))
				{
					dialog.text = "Miért nem? A kikapcsolódás jót tesz a szívnek, de nem a pénztárcának...";
	    			link.l1 = "Kiváló.";
	    			link.l1.go = "Cards_begin";
	    			link.l2 = "Mik a játékszabályok?";
	    			link.l2.go = "Cards_Rule";
    			}
    			else
    			{
					dialog.text = "Nem, mára végeztem. Van még dolgom.";
	    			link.l1 = "Ahogy óhajtja.";
	    			link.l1.go = "exit";
				}
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
			dialog.text = "Elôször is, egyezzünk meg a fogadásról.";
			link.l1 = "Játsszunk 1000 darab pesóért.";
			link.l1.go = "Cards_Node_100";
			link.l2 = "Játsszunk 5000 pesóért.";
			link.l2.go = "Cards_Node_500";
			link.l3 = "Azt hiszem, mennem kell.";
			link.l3.go = "exit";
		break;

		case "Cards_Node_100":
			//belamour legendary edition 
			bOk1 = isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && GetNationRelation(npchar.nation, sti(Items[sti(pchar.EquipedPatentId)].Nation)) != RELATION_ENEMY;
			bOk2 = CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && GetNationRelation(npchar.nation, FRANCE) != RELATION_ENEMY;
			bOk = bOk1 || bOk2;
            if (!CheckCardsGameSmallRate() && !bOk)
		    {
                dialog.text = "Te egy hírhedt csaló vagy. Nem játszom veled.";
                link.l1 = "Ez mind hazugság!";
			    link.l1.go = "exit";
			    break;
		    }

			if (sti(pchar.Money) < 3000)
		    {
                dialog.text = "Viccelsz, " + GetAddress_Form(NPChar) + "? Nincs pénzed!";
                link.l1 = "Megtörténik.";
			    link.l1.go = "exit";
			    break;
		    }
		    if (sti(npchar.Money) < 3000)
		    {
                dialog.text = "Nincs pénzed! Végeztem a kártyázással - mielôtt pénzsóvárnak neveznek, és arra kényszerítenek, hogy elhagyjam a posztomat.";
                link.l1 = "Kár.";
			    link.l1.go = "exit";
			    break;
		    }
   			dialog.text = "Rendben, játsszunk 1000 darab pesóért.";
			link.l1 = "Kezdjük el!";
			link.l1.go = "Cards_begin_go";
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
            pchar.GenQuest.Cards.iRate     = 1000;
            pchar.GenQuest.Cards.SitType   = false;
		break;

		case "Cards_Node_500":
			//belamour legendary edition 
			bOk1 = isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && GetNationRelation(npchar.nation, sti(Items[sti(pchar.EquipedPatentId)].Nation)) != RELATION_ENEMY;
			bOk2 = CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && GetNationRelation(npchar.nation, FRANCE) != RELATION_ENEMY;
			bOk = bOk1 || bOk2;
            if (!CheckCardsGameSmallRate() && !bOk)
		    {
                dialog.text = "Te egy hírhedt csaló vagy. Nem játszom veled.";
                link.l1 = "Ez mind hazugság! Hát, mindegy.";
			    link.l1.go = "exit";
			    break;
		    }
			if (!CheckCardsGameBigRate())
		    {
                dialog.text = "Azt mondják, nagyon jó játékos vagy. Nem fogok nagy tétekben játszani veled.";
                link.l1 = "Esetleg csökkenthetnénk a tétet?";
			    link.l1.go = "Cards_Node_100";
				link.l2 = "Sajnálom, de mennem kell.";
			    link.l2.go = "exit";
			    break;
		    }

			if (sti(pchar.Money) < 15000)
		    {
                dialog.text = "Viccelsz, " + GetAddress_Form(npchar) + "? Nincs 15000 darab pesód!";
                link.l1 = "Emelek!";
			    link.l1.go = "exit";
			    break;
		    }
		    if (sti(npchar.Money) < 15000)
		    {
                dialog.text = "Nem, ezek a tétek kiürítik a város kincstárát.";
                link.l1 = "Ahogy óhajtja.";
			    link.l1.go = "exit";
			    break;
		    }
   			dialog.text = "Rendben, játsszunk 5000 darab pesóért.";
			link.l1 = "Kezdjük el!";
			link.l1.go = "Cards_begin_go";
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
            pchar.GenQuest.Cards.iRate     = 5000;
            pchar.GenQuest.Cards.SitType   = false;
		break;

		case "Cards_begin_go":
            SetNPCQuestDate(npchar, "Card_date_begin");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
            LaunchCardsGame();
		break;
	    // карты <--

	    //  Dice -->
        case "Dice_Game":
            if (!CheckNPCQuestDate(npchar, "Dice_date_Yet") || sti(PChar.rank) < 4 || isBadReputation(pchar, 50) || GetCharacterSkillToOld(pchar, SKILL_LEADERSHIP) < rand(5))
            {
                SetNPCQuestDate(npchar, "Dice_date_Yet");
				// belamour legendary edition фикс проверки мундира с мушкетом
				if(IsUniformEquip()) dialog.text = "Bocsásson meg, monsignore, de erre most nincs idôm. Talán majd legközelebb."; // Jason НСО
                else dialog.text = "Nem fogok kalózokkal játszani!";
    			link.l1 = "Ahogy óhajtja.";
    			link.l1.go = "exit";
			}
			else
			{
				if (CheckNPCQuestDate(npchar, "Dice_date_begin"))
				{
					dialog.text = "Miért ne? A pihenés jót tesz a szívnek... de nem a pénztárcának...";
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
			dialog.text = "Elôször is, egyezzünk meg a fogadásról.";
			link.l1 = "Játsszunk 500 darab pesóra kockánként.";
			link.l1.go = "Dice_Node_100";
			link.l2 = "Játsszunk 2000 darab pesóra kockánként.";
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
                dialog.text = "Te egy hírhedt csaló vagy. Nem játszom veled.";
                link.l1 = "Ez mind hazugság! Hát, mindegy.";
			    link.l1.go = "exit";
			    break;
		    }

			if (sti(pchar.Money) < 3000)
		    {
                dialog.text = "Viccelsz, " + GetAddress_Form(NPChar) + "? Nincs pénzed!";
                link.l1 = "Megtörténik.";
			    link.l1.go = "exit";
			    break;
		    }
		    if (sti(npchar.Money) < 3000)
		    {
                dialog.text = "Ez az! Végeztem a szerencsejátékkal - mielôtt még tékozlónak neveznének, és arra kényszerítenének, hogy elhagyjam a posztomat...";
                link.l1 = "Kár.";
			    link.l1.go = "exit";
			    break;
		    }
   			dialog.text = "Rendben, játsszunk 500 darab pesóra.";
			link.l1 = "Kezdjük el!";
			link.l1.go = "Dice_begin_go";
			pchar.GenQuest.Dice.npcharIdx = npchar.index;
            pchar.GenQuest.Dice.iRate     = 500;
            pchar.GenQuest.Dice.SitType   = false;
		break;

		case "Dice_Node_500":
			//belamour legendary edition 
			bOk1 = isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && GetNationRelation(npchar.nation, sti(Items[sti(pchar.EquipedPatentId)].Nation)) != RELATION_ENEMY;
			bOk2 = CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && GetNationRelation(npchar.nation, FRANCE) != RELATION_ENEMY;
			bOk = bOk1 || bOk2;
            if (!CheckDiceGameSmallRate() && !bOk)
		    {
                dialog.text = "Te egy hírhedt csaló vagy. Nem játszom veled.";
                link.l1 = "Ez mind hazugság! Hát, mindegy.";
			    link.l1.go = "exit";
			    break;
		    }
			if (!CheckDiceGameBigRate())
		    {
                dialog.text = "Azt mondják, nagyon jó játékos vagy. Nem fogok nagy tétekben játszani veled.";
                link.l1 = "Esetleg csökkenthetnénk a tétet?";
			    link.l1.go = "Dice_Node_100";
				link.l2 = "Sajnálom, de mennem kell.";
			    link.l2.go = "exit";
			    break;
		    }

			if (sti(pchar.Money) < 15000)
		    {
                dialog.text = "Viccelsz, " + GetAddress_Form(NPChar) + "? Nincs 15000 darab pesód!";
                link.l1 = "Emelek!";
			    link.l1.go = "exit";
			    break;
		    }
		    if (sti(npchar.Money) < 15000)
		    {
                dialog.text = "Nem, ezek a fogadások biztosan kiürítik a város kincstárát.";
                link.l1 = "Ahogy óhajtja.";
			    link.l1.go = "exit";
			    break;
		    }
   			dialog.text = "Jól van, játsszunk 2000 darab pesóra kockánként.";
			link.l1 = "Kezdjük el!";
			link.l1.go = "Dice_begin_go";
			pchar.GenQuest.Dice.npcharIdx = npchar.index;
            pchar.GenQuest.Dice.iRate     = 2000;
            pchar.GenQuest.Dice.SitType   = false;
		break;

		case "Dice_begin_go":
            SetNPCQuestDate(npchar, "Dice_date_begin");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
            LaunchDiceGame();
		break;
	    // Dice <--
		case "node_2":
			dialog.text = "Ebben az esetben megkérném, hogy hagyja el a dolgozószobámat, és ne zavarjon a munkámban.";
			link.l1 = "Igen, igen, természetesen. Elnézést a zavarásért.";
			link.l1.go = "exit";
		break;

		//---------------------------- генератор квестов мэра -------------------------------
		case "work": 
            dialog.text = "Ez egy poloska. Értesítsd a fejlesztôket róla.";
        	link.l1 = "Köszönöm, ez egy nagyszerû játék!";
        	link.l1.go = "exit";
			
			//==> прибыла инспекция на Святом Милосердии
			if (CheckAttribute(npchar, "quest.SantaMisericordia"))
			{
    			dialog.text = "Ne most! Ellenôrzést tartunk, don de Alamida a városban van. Ó, minden évben ugyanaz, mivel érdemeltem ki ezt...";
				link.l1 = "Ahogy mondod. Nem akarom zavarni.";
				link.l1.go = "exit"; 
				break;
			}
			//<== прибыла инспекция на Святом Милосердии
			//==> взят ли какой-либо квест
			if (CheckAttribute(pchar, "GenQuest.questName"))
			{		 				
				//--> Федот, да не тот
				QuestName = pchar.GenQuest.questName;
				if (pchar.GenQuest.(QuestName).MayorId != npchar.id) 
				{					
					dialog.text = RandPhraseSimple("Amennyire én tudom, már van egy küldetésed, amit a " + XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.(QuestName).MayorId)].city+"Gen") + "kormányzója adott neked. Fejezze be a már elvégzett feladatát, és akkor beszélhetünk.", 
						"Hmm, nem te voltál az a " + XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.(QuestName).MayorId)].city+"Voc") + " , ahol a helyi kormányzótól kaptál parancsot? Igen, így van. Elôször fejezd be azt a küldetést.");
					link.l1 = RandPhraseSimple("Értem...", "Understood..."+ GetSexPhrase("","") +", "+ GetAddress_FormToNPC(NPChar) + ".");
					link.l1.go = "exit";					
					break;
				}
				//<--Федот, да не тот
				//-------- взят квест уничтожения банды ---------->>
				if (QuestName == "DestroyGang")
				{
					switch (pchar.GenQuest.DestroyGang)
					{
						makearef(arName, pchar.GenQuest.DestroyGang);
						case "":
							dialog.text = LinkRandPhrase("A banditák felkutatására irányuló küldetést " + GetFullName(arName) + " már kiadták neked. Most teljesítsd!", 
								"Már kaptál egy küldetést, hogy felkutass egy banditát, akinek a neve " + GetFullName(arName) + ". Várom az eredményeket!", 
								"Míg te a rezidenciámon vesztegeted az idôdet, addig " + GetFullName(arName) + " a telepeseinket rabolja ki! Munkára fel!");
							link.l1 = RandPhraseSimple("Rendben, " + GetAddress_FormToNPC(NPChar) + ".", "elfoglalt vagyok vele, "+ GetAddress_FormToNPC(NPChar) + ".");
							link.l1.go = "exit";		
						break;
						case "Late":
							dialog.text = RandPhraseSimple("A neked adott idô, hogy megtaláld és kiiktasd a banditát, lejárt. És milyen jelentéseket kapok, mit gondolsz? És megmondom neked - " + GetFullName(arName) + " még mindig él és virul! Most pedig magyarázkodj, " + GetAddress_Form(NPChar) + ".",
								"A neked adott idô, hogy likvidáld azt a gazembert, akit " + GetFullName(arName) + "névre kereszteltek, lejárt. Még mindig azt mondják nekem, hogy egyáltalán nem történt elôrelépés. Mi a helyzet?");
							link.l1 = "Nem tudtam a kijelölt idôre elvégezni a munkáját, " + GetAddress_FormToNPC(NPChar) + ".";
							link.l1.go = "All_Late";		
						break;
						case "Found":
							dialog.text = RandPhraseSimple("Szóval, mit mondasz? Sikerült likvidálni az említett banditát? " + GetFullName(arName) + " végre meghalt?", "Csak egy dolgot árulj el: " + GetFullName(arName) + " halott vagy él?");
							link.l1 = "Sajnos még mindig él, " + GetAddress_FormToNPC(NPChar) + ". Sikerült megkeresnem, de túlerôben voltam, és kénytelen voltam visszavonulni. Ez a bandita egy igazán kemény fattyú. Sajnálom.";
							link.l1.go = "All_Found";		
						break;
						case "Execute":
							dialog.text = RandPhraseSimple("Szóval, mit mondasz? Sikerült likvidálni az említett banditát? " + GetFullName(arName) + " végre meghalt?", "Csak egy dolgot árulj el: " + GetFullName(arName) + " halott vagy él?");
							link.l1 = "Meghalt, " + GetAddress_FormToNPC(NPChar) + ".";
							link.l1.go = "All_Execute";		
							AddCharacterExpToSkill(PChar, "Leadership", 180);
							ChangeCharacterComplexReputation(pchar,"authority", 1);
						break;
					}
				}
				//-------- контркурьер ---------->>
				if (QuestName == "TakePostcureer")
				{
					switch (pchar.GenQuest.TakePostcureer)
					{
						case "":
							dialog.text = LinkRandPhrase("Már kiadtak neked egy küldetést egy futárhajó elfogására. Most teljesítsd!", 
								"Már van egy küldetésed egy futárhajó elfogására! Várom az eredményeket!", 
								"Amíg te a rezidenciámon vesztegeted az idôdet, addig a dokumentumok, amelyekre szükségem van, egyenesen az ellenségünk kezébe csúsznak! Munkára fel!");
							link.l1 = RandPhraseSimple("Rendben, " + GetAddress_FormToNPC(NPChar) + ".", "elfoglalt vagyok vele, "+ GetAddress_FormToNPC(NPChar) + ".");
							link.l1.go = "exit";		
						break;
						case "Late":
							dialog.text = RandPhraseSimple("A futárhajó felkutatására és elfogására adott idô lejárt. És milyen jelentéseket kapok, mit gondolsz? És megmondom neked - a dokumentumok, amiket vártam, egyenesen az ellenségünk kezébe kerültek! Most méltóztassék magyarázkodni, " + GetAddress_Form(NPChar) + ".",
								"Minden határidô, amit arra adtak, hogy a futárhajóról elkapja a dokumentumokat, lejárt. Még mindig nem történt semmilyen elôrelépés. Mi ez az egész?");
							link.l1 = "Nem tudtam idôben elvégezni a munkát, " + GetAddress_FormToNPC(NPChar) + ".";
							link.l1.go = "All_Late";		
						break;
						case "Found":
							dialog.text = RandPhraseSimple("Szóval, mit mondasz? Sikerült megörökíteni a dokumentumokat?", "Csak egy dolgot árulj el - sikerült biztosítani a levelezést?");
							link.l1 = "Sajnos nem, " + GetAddress_FormToNPC(NPChar) + ". A hajót megtaláltam, de a dokumentumok elkerültek.";
							link.l1.go = "All_Found";		
						break;
						case "Execute":
							dialog.text = RandPhraseSimple("Szóval, mit mondasz? Sikerült megörökíteni a dokumentumokat?", "Csak egy dolgot árulj el - sikerült biztosítani a levelezést?");
							link.l1 = "Igen, " + GetAddress_FormToNPC(NPChar) + ". Nálam vannak. Tessék.";
							link.l1.go = "All_Execute";		
							AddCharacterExpToSkill(PChar, "Leadership", 200);
							AddCharacterExpToSkill(PChar, "Fortune", 300);
							AddCharacterExpToSkill(PChar, "Sneak", 150);
							RemoveItems(pchar, "ContraPostLetters", 1);
							ChangeCharacterComplexReputation(pchar,"authority", 1);
						break;
					}
				}
				//-------- контрфрахт - арсенал ---------->>
				if (QuestName == "TakeArsenalship")
				{
					switch (pchar.GenQuest.TakeArsenalship)
					{
						case "":
							dialog.text = LinkRandPhrase("Már kiadtak neked egy katonai szállítóhajó megsemmisítésére irányuló küldetést. Most teljesítsd!", 
								"Ön már kapott egy küldetést egy katonai szállítójármû megsemmisítésére! Várom az eredményeket!", 
								"Amíg te a rezidenciámon vesztegeted az idôdet, a lôport és a lôszert egyenesen az ellenséges ágyúkba szállítják! Lássatok munkához!");
							link.l1 = RandPhraseSimple("Rendben, " + GetAddress_FormToNPC(NPChar) + ".", "elfoglalt vagyok vele, "+ GetAddress_FormToNPC(NPChar) + ".");
							link.l1.go = "exit";		
						break;
						case "Late":
							dialog.text = RandPhraseSimple("A katonai szállítóhajó felkutatására és megsemmisítésére adott idô lejárt. És milyen jelentéseket kapok, mit gondolsz? És megmondom - az ellenséges konvoj sikeresen elérte a célját! Most méltóztassék magyarázkodni, " + GetAddress_Form(NPChar) + ".",
								"Az ellenséges katonai szállítmány megsemmisítésére adott összes határidô lejárt. Még mindig nem történt semmiféle elôrelépés. Mi a helyzet?");
							link.l1 = "Nem tudtam végrehajtani a feladatot a megadott idô alatt, " + GetAddress_FormToNPC(NPChar) + ".";
							link.l1.go = "All_Late";		
						break;
						case "Found":
							dialog.text = RandPhraseSimple("Szóval, mit mondasz? Sikerült megsemmisíteni az ellenséges szállítóhajót?", "Csak egy dolgot árulj el - az az ellenséges leltár a tengerfenéken pihen?");
							link.l1 = "Sajnos nem, " + GetAddress_FormToNPC(NPChar) + ". Megtaláltam a konvojt, de nem sikerült elsüllyesztenem a szükséges hajót.";
							link.l1.go = "All_Found";		
						break;
						case "Execute":
							dialog.text = RandPhraseSimple("Szóval, mit mondasz? Sikerült elpusztítani az ellenséges szállítóhajót?", "Csak egy dolgot árulj el - az ellenséges arzenál a tengerfenéken pihen?");
							link.l1 = "Igen, " + GetAddress_FormToNPC(NPChar) + ". Az ellenségünk nem fogja megkapni azt a lôport és lôszert.";
							link.l1.go = "All_Execute";		
							AddCharacterExpToSkill(PChar, "Leadership", 220);
							AddCharacterExpToSkill(PChar, "Fortune", 300);
							AddCharacterExpToSkill(PChar, "Sneak", 150);
							ChangeCharacterComplexReputation(pchar,"authority", 1);
						break;
					}
				}
				//-------- ОЗГ - пират ---------->>
				if (QuestName == "TakePirateship")
				{
					switch (pchar.GenQuest.TakePirateship)
					{
						case "":
							dialog.text = LinkRandPhrase("Egy kalóz likvidálására vonatkozó küldetést már kiadtak neked. Most teljesítsd!", 
								"Már kaptál egy küldetést egy kalózhajó megsemmisítésére! Várom az eredményeket!", 
								"Amíg te a rezidenciámon vesztegeted az idôdet, addig az a mocskos kalóz újabb áldozatot szed le! Munkára fel!");
							link.l1 = RandPhraseSimple("Rendben, " + GetAddress_FormToNPC(NPChar) + ".", "elfoglalt vagyok vele, "+ GetAddress_FormToNPC(NPChar) + ".");
							link.l1.go = "exit";		
						break;
						case "Late":
							dialog.text = RandPhraseSimple("A kalóz felkutatására és likvidálására adott idô lejárt. És milyen jelentéseket kapok, mit gondolsz? És megmondom neked - az a mocskos kalóz még mindig a hajóinkat fosztogatja! Most pedig méltóztassanak magyarázkodni, " + GetAddress_Form(NPChar) + ".",
								"A kalózhajó elpusztítására adott összes határidô lejárt. Még mindig nem történt semmiféle elôrelépés. Mi a helyzet?");
							link.l1 = "Nem tudtam idôben elvégezni a munkáját, " + GetAddress_FormToNPC(NPChar) + ".";
							link.l1.go = "All_Late";		
						break;
						case "Found":
							dialog.text = RandPhraseSimple("Szóval, mit mondasz? Sikerült elpusztítani a kalózhajót?", "Csak egyet árulj el - az a mocskos kalóz végre a tengerfenéken pihen?");
							link.l1 = "Sajnos nem, " + GetAddress_FormToNPC(NPChar) + ". Sikerült felkutatnom ezt a gazembert, de nem sikerült elsüllyesztenem a hajóját.";
							link.l1.go = "All_Found";		
						break;
						case "Execute":
							dialog.text = RandPhraseSimple("Szóval, mit mondasz? Sikerült elpusztítani a kalózhajót?", "Csak egyet árulj el - az a mocskos kalóz végre a tengerfenéken pihen?");
							link.l1 = "Igen, " + GetAddress_FormToNPC(NPChar) + ". Ez a gazember többé nem fogja zavarni a kereskedelmi hajózásunkat.";
							link.l1.go = "All_Execute";		
							AddCharacterExpToSkill(PChar, "Leadership", 250);
							AddCharacterExpToSkill(PChar, "Fortune", 300);
							AddCharacterExpToSkill(PChar, "Sneak", 150);
							ChangeCharacterComplexReputation(pchar,"authority", 1);
						break;
					}
				}
					//-------- ОЗГ - пассажир ---------->>
				if (QuestName == "TakePassenger")
				{
					switch (pchar.GenQuest.TakePassenger)
					{
						case "":
							dialog.text = LinkRandPhrase("A bûnözô felkutatására vonatkozó küldetést már kiadták neked. Most teljesítsd!", 
								"Ön már kapott egy küldetést, hogy keressen fel egy bûnözôt! Várom az eredményeket!", 
								"Amíg te a rezidenciámon vesztegeted az idôdet, addig az a mocskos gazember tovább vitorlázik! Azonnal folytassa a rábízott küldetést!");
							link.l1 = RandPhraseSimple("Rendben, " + GetAddress_FormToNPC(NPChar) + ".", "elfoglalt vagyok vele, "+ GetAddress_FormToNPC(NPChar) + ".");
							link.l1.go = "exit";		
						break;
						case "Late":
							dialog.text = RandPhraseSimple("Az idô, amit arra kaptál, hogy megtaláld azt a gazembert, lejárt. És milyen jelentéseket kapok, mit gondolsz? És megmondom neked - sikeresen megérkezett a célállomásra, majd eltûnt a semmibe! Most méltóztassék magyarázkodni, " + GetAddress_Form(NPChar) + ".",
								"A bûnözô megtalálására adott összes határidô lejárt. Még mindig nem történt semmilyen elôrelépés. Mi a helyzet?");
							link.l1 = "Nem voltam képes végrehajtani a feladatot a fent említett idô alatt, " + GetAddress_FormToNPC(NPChar) + ".";
							link.l1.go = "All_Late";		
						break;
						case "Found":
							dialog.text = RandPhraseSimple("Szóval, mit mondasz? Elkaptad a gonosztevôt?", "Csak egy dolgot árulj el - az a mocskos gazember a fogdában van, betömve a száját és megbilincselve?");
							link.l1 = "Sajnos nem, " + GetAddress_FormToNPC(NPChar) + ". Nem sikerült elkapnom a gazembert. A hajóval együtt, amin volt, elsüllyedt.";
							link.l1.go = "All_Found";		
						break;
						case "Execute":
							dialog.text = RandPhraseSimple("Szóval, mit mondasz? Elkaptad a gonosztevôt?", "Csak egy dolgot árulj el - az a mocskos gazember a fogdában van, betömve a száját és megbilincselve?");
							link.l1 = "Igen, " + GetAddress_FormToNPC(NPChar) + ". Kérem, küldje a katonáit a mólóhoz, és én átadom önnek.";
							link.l1.go = "All_Execute";		
							AddCharacterExpToSkill(PChar, "Leadership", 250);
							AddCharacterExpToSkill(PChar, "Fortune", 300);
							AddCharacterExpToSkill(PChar, "Sneak", 200);
							ChangeCharacterComplexReputation(pchar,"authority", 1);
							sld = &Characters[sti(Pchar.GenQuest.TakePassenger.PrisonerIDX)];
							ReleasePrisoner(sld); //освободили пленника
							sld.lifeday = 0;
						break;
					}
				}
				//-------- таможенный патруль ---------->>
				if (QuestName == "CustomPatrol")
				{
					switch (pchar.GenQuest.CustomPatrol)
					{
						case "":
							dialog.text = LinkRandPhrase("A csempészek felkutatására már kiadtak neked egy küldetést. Most teljesítsd!", 
								"Már kapott egy küldetést, hogy keresse fel a csempészeket! Várom az eredményeket!", 
								"Amíg te a rezidenciámon vesztegeted az idôdet, addig azok a csempészek újabb üzletre készülnek! Azonnal folytasd a rád bízott küldetést!");
							link.l1 = RandPhraseSimple("Rendben, " + GetAddress_FormToNPC(NPChar) + ".", "elfoglalt vagyok vele, "+ GetAddress_FormToNPC(NPChar) + ".");
							link.l1.go = "exit";		
						break;
						case "Late":
							dialog.text = RandPhraseSimple("A csempészek felkutatására adott idô lejárt. És milyen jelentéseket kapok, mit gondolsz? És megmondom neked - boldogan eladták az összes árujukat! Most pedig méltóztassanak magyarázkodni, " + GetAddress_Form(NPChar) + ".",
								"A csempészek felkutatására adott összes határidô lejárt. Még mindig nem történt semmiféle elôrelépés. Mi a helyzet?");
							link.l1 = "Nem tudtam idôben végrehajtani a feladatát, " + GetAddress_FormToNPC(NPChar) + ".";
							link.l1.go = "All_Late";		
						break;
						case "Found":
							dialog.text = RandPhraseSimple("Szóval, mit mondasz? Volt már dolgod a csempészekkel?", "Csak egy dolgot árulj el - tönkretetted a csempészek üzletét?");
							link.l1 = "Sajnos nem, " + GetAddress_FormToNPC(NPChar) + ". Nem sikerült meghiúsítanom a gazemberek tervét.";
							link.l1.go = "All_Found";		
						break;
						case "Execute":
							dialog.text = RandPhraseSimple("Szóval, mit mondasz? Volt már dolgod a csempészekkel?", "Csak egy dolgot árulj el - tönkretetted a csempészek üzletét?");
							link.l1 = "Igen, " + GetAddress_FormToNPC(NPChar) + ". Utolértem ôket, és mindkét fél, vevô és eladó hajóit egyaránt kiküszöböltem.";
							link.l1.go = "All_Execute";		
							AddCharacterExpToSkill(PChar, "Leadership", 200);
							AddCharacterExpToSkill(PChar, "Fortune", 300);
							AddCharacterExpToSkill(PChar, "Sneak", 300);
							ChangeCharacterComplexReputation(pchar,"authority", 1);
						break;
					}
				}
				//-------- Дезертир ---------->>
				if (QuestName == "FindFugitive")
				{
					switch (pchar.GenQuest.FindFugitive)
					{
						case "":
							dialog.text = LinkRandPhrase("A dezertôr felkutatására már kiadtak egy küldetést. Most teljesítsd!", 
								"Ön már kapott egy küldetést a dezertôr felkutatására! Várom az eredményeket!", 
								"Amíg te a rezidenciámon vesztegeted az idôdet, addig az a dezertôr elárulhatja államtitkainkat! Azonnal folytassa a rábízott küldetést!");
							link.l1 = RandPhraseSimple("Rendben, " + GetAddress_FormToNPC(NPChar) + ".", "elfoglalt vagyok vele, "+ GetAddress_FormToNPC(NPChar) + ".");
							link.l1.go = "exit";		
						break;
						case "Late":
							dialog.text = RandPhraseSimple("A dezertôr felkutatására adott idô lejárt. És milyen jelentéseket kapok, mit gondolsz? És megmondom neked - semmi eredmény, egyáltalán semmi! Most méltóztassék magyarázkodni, " + GetAddress_Form(NPChar) + ".",
								"A dezertôr megtalálására adott összes határidô lejárt. Még mindig semmi elôrelépés nem történt. Mi a helyzet?");
							link.l1 = "Nem tudtam idôben elvégezni a munkáját, " + GetAddress_FormToNPC(NPChar) + ".";
							link.l1.go = "All_Late";		
						break;
						case "Found":
							dialog.text = RandPhraseSimple("Szóval, mit mondasz? Elfogtátok a dezertôrt?", "Csak egy dolgot árulj el - a dezertôr a fogdában van, betömve a szájkosárral és a bilincsekkel?");
							link.l1 = "Sajnos nem, " + GetAddress_FormToNPC(NPChar) + ". Nem sikerült elkapnom azt a gazembert. A "+XI_ConvertString("Colony"+pchar.GenQuest.FindFugitive.City)+"településen találtam meg a nyomát, de éppen az érkezésem elôtti napon indult délnek egy kalózhajón. Gondolom, most azokkal a szerencselovagokkal van.";
							link.l1.go = "All_Found";		
						break;
						case "Execute":
							dialog.text = RandPhraseSimple("Ó, nos... Itt van a "+pchar.GenQuest.FindFugitive.Name+"... Szép munka, kapitány! Nehéz volt a keresés?", "Ó, micsoda vendégeink vannak! Helló, "+pchar.GenQuest.FindFugitive.Name+"! Szép munka, kapitány! Sokat fáradoztál a kereséssel?");
							link.l1 = "Hogyan kell mondani, " + GetAddress_FormToNPC(NPChar) + ". Bármi is volt az - a küldetésed teljesült.";
							link.l1.go = "All_Execute";		
							AddCharacterExpToSkill(PChar, "Leadership", 300);
							AddCharacterExpToSkill(PChar, "Fortune", 300);
							AddCharacterExpToSkill(PChar, "Sneak", 200);
							ChangeCharacterComplexReputation(pchar, "authority", 1);
							sld = &Characters[sti(Pchar.GenQuest.FindFugitive.PrisonerIDX)];
							ReleasePrisoner(sld); //освободили пленника
							LAi_SetActorType(sld);
							sld.lifeday = 0;
							pchar.quest.FindFugitive_Over.over = "yes"; //снимаем таймер
							chrDisableReloadToLocation = false;//открыть локацию
						break;
					}
				}
				//------ проникновение во враждебный город ------------>>
				if (QuestName == "Intelligence")
				{
					switch (pchar.GenQuest.Intelligence)
					{
						case "":
							if (GetQuestPastDayParam("GenQuest.Intelligence") > sti(pchar.GenQuest.Intelligence.Terms))
							{
								dialog.text = RandPhraseSimple("A levél kézbesítésére adott idô lejárt. És úgy veszem észre, hogy nem sikerült.",
									"Az idô lejárt. Még mindig nem történt semmilyen elôrelépés. Mi a helyzet?");
								link.l1 = "Nem tudtam elvégezni a munkáját, " + GetAddress_FormToNPC(NPChar) + ".";
								link.l1.go = "All_Late";	
							}
							else
							{
								dialog.text = LinkRandPhrase("Már kiadtak egy küldetést, hogy kézbesítsen nekem egy levelet. Most pedig teljesítsd!", 
									"Már van egy küldetésed, hogy kézbesíts egy levelet egyenesen nekem! Várom az eredményeket, szükségem van arra a levélre, amilyen gyorsan csak lehet!", 
									"Amíg te a lakhelyemen vesztegeted az idôdet, addig az információ, amire nagy szükségem van, még mindig annak a személynek a kezében van, akinek el kellene küldenie nekem! Haladéktalanul folytassa a rábízott küldetést!");
								link.l1 = RandPhraseSimple("Rendben, " + GetAddress_FormToNPC(NPChar) + ".", "Azonnal hozzálátok, "+ GetAddress_FormToNPC(NPChar) + ".");
								link.l1.go = "exit";	
							}
						break;
						case "Execute":
							dialog.text = RandPhraseSimple("Kézbesítette már a levelet, amit várok?", "Mondd meg most - megvan?!");
							link.l1 = "Igen, megvan. Ahogy megbeszéltük - személyesen neked kézbesítve.";
							if (GetQuestPastDayParam("GenQuest.Intelligence") > sti(pchar.GenQuest.Intelligence.Terms))
							{
								link.l1.go = "Intelligence_ExecuteLate";
								AddCharacterExpToSkill(PChar, "Sneak", 300);
							}
							else
							{
								link.l1.go = "All_Execute";		
								AddCharacterExpToSkill(PChar, "Leadership", 100);
								AddCharacterExpToSkill(PChar, "Sneak", 300);
							}
							TakeItemFromCharacter(pchar, "sicretLetter");
							DeleteAttribute(ItemsFromID("sicretLetter"), "City");
							DeleteAttribute(ItemsFromID("sicretLetter"), "Mayor");
						break;
					}
				}
				break;
			}
			sTemp = npchar.city;
			//занят ПГГ
			i = CheckAvailableTaskForNPC(NPChar, PGG_TASK_WORKONMAYOR);
			if (i != -1)
			{
				dialog.text = "Sajnos, ma nem tudok munkát adni neked. Az utolsót a " + GetFullName(&Characters[i])
					+ "végezte el. Jöjjön holnap, hátha elôkerül valami.";
				link.l1 = "Ó, a fenébe! Nincs szerencsém...";
				link.l1.go = "exit";
				break;
			}
//navy <--
			if (!CheckAttribute(npchar, "work_date") || GetNpcQuestPastDayParam(npchar, "work_date") > 2 || bBettaTestMode)
    		{	
				SaveCurrentNpcQuestDateParam(npchar, "work_date");
				if(CheckAttribute(pchar, "questTemp.StatusCity") && pchar.questTemp.StatusCity == npchar.city)
				{
					dialog.text = "Épp idôben jött, kapitány. Egy sürgôs problémával kell foglalkoznom, ami a kolóniánkra irányuló csempészáruval kapcsolatos. Gondolom, a hajója tengerjáró és harcra kész.";
					link.l1 = "A hajóm mindig tengerrevaló és harcra kész. Kérem, meséljen többet a közelgô küldetésrôl, kegyelmes uram.";
					link.l1.go = "CustomPatrol";
					break;
				}
				if (rand(5) > 4 && !bBettaTestMode && pchar.location == "Panama_townhall") // patch-5
				{
					dialog.text = LinkRandPhrase("Egyelôre nincs munkám számodra. Holnap, gondolom...", 
						"Sajnos, ma nincs munkám számodra. Kérem, nézzen vissza egy-két nap múlva.", 
						"Ma nincs semmi, amit fel tudnék ajánlani Önnek. Örülök, ha máskor is találkozunk.");
					link.l1 = "Értem, " + GetAddress_FormToNPC(NPChar) + ".";
					link.l1.go = "exit";
				}
				else
				{
					sTemp = GetSpyColony(npchar);
					// не даём задание пробраться во вражеский город, если у нации ГГ нет врагов
					if (sTemp == "none")
						i = 1 + hrand(6);
					else
						i = hrand(7);
					switch (i)
					{
						//========== пробраться во вражеский город ============//Jason: оставляем, как годный
						case 0:
							pchar.GenQuest.Intelligence.Terms = hrand(10) + (42 - MOD_SKILL_ENEMY_RATE); //сроки выполнения задания
							pchar.GenQuest.Intelligence.Money = ((hrand(4) + 6) * 2000) + (sti(pchar.rank) * 1000 + 10000); //вознаграждение
							pchar.GenQuest.Intelligence.City = sTemp; //враждебная колония
                            sTemp = ", ...ami a " + XI_ConvertString(colonies[FindColony(pchar.GenQuest.Intelligence.City)].islandLable+"Dat");                         
							dialog.text = "Van egy küldetésem számodra, ami komoly kockázatokkal jár. Szükségem van rád, hogy beosonj a " + XI_ConvertString("Colony"+pchar.GenQuest.Intelligence.City+"Acc") + sTemp + ", ott találkozz egy bizonyos személlyel, majd szállítsd el nekem, amit ô kér tôled.";
							link.l1 = "Hmm, nem hiszem, hogy a " + XI_ConvertString("Colony"+pchar.GenQuest.Intelligence.City+"Dat") + " oldalon szívesen látott vendég leszek...";
							link.l1.go = "Intelligence";
						break;
						//========== квест уничтожения банды ============ //Jason: оставляем, как классику
						case 1:
							pchar.GenQuest.DestroyGang.Terms = hrand(2) + 2; //сроки выполнения задания
							pchar.GenQuest.DestroyGang.Money = ((hrand(6)+4)*500)+(sti(pchar.rank)*300+2000); //вознаграждение
							makearef(arName, pchar.GenQuest.DestroyGang);
							arName.nation = PIRATE;
							arName.sex = "man";
							SetRandomNameToCharacter(arName); //имя бандита в структуру квеста	
							dialog.text = "Most van egy küldetésem számodra. A dzsungelben a " + XI_ConvertString("Colony"+npchar.city+"Gen") + " közelében megjelent egy rablóbanda, és tudom, hogy az egyik fôkolompos a " + GetFullName(arName) + "névre hallgat. Keressétek fel és likvidáljátok ezt a bandát.";
							link.l1 = "Valahogy korlátozottak a feltételeim?";
							link.l1.go = "DestroyGang";
						break;
						
						//========== контркурьер - отобрать почту ============
						case 2:
							dialog.text = "Igen, van egy küldetésem a számodra. Ahhoz, hogy teljesíteni tudd, gyorsaságot kell mutatnod, és némi jártasságot a tengeri harcban is. Készen állsz arra, hogy megmutasd, mit érsz?";
							link.l1 = "Felség, elárulna több részletet a küldetésrôl?";
							link.l1.go = "TakePostcureer";
						break;
						
						//========== контрфрахт - потопить корабль с боеприпасами ============
						case 3:
							dialog.text = "Igen, van egy küldetésem számodra. Ahhoz, hogy teljesíteni tudd, kiemelkedô bátorságot kell mutatnod, és némi jártasságot a tengeri harcban. Készen állsz, hogy megmutasd, mit érsz?";
							link.l1 = "Felség, elárulna további részleteket a közelgô küldetésrôl?";
							link.l1.go = "TakeArsenalship";
						break;
						//========== ОЗГ - охотник на пирата ============
						case 4:
							dialog.text = "Igen, fontos küldetésem van számodra. Ahhoz, hogy teljesítsd, minden képességedet be kell vetned. Ez kalózokkal kapcsolatos...";
							link.l1 = "Kalózok? Elmondanád nekem részletesebben, hogy mit várnak tôlem?";
							link.l1.go = "TakePirateship";
						break;
						//========== ОЗГ - охотник на пассажира ============
						case 5:
							dialog.text = "Épp idôben érkezett, uram. Van egy sürgôs küldetésem, ami pont megfelel önnek. Egy bizonyos személyt kell felkutatni és elfogni...";
							link.l1 = "Egy embervadászat? Elmondaná részletesebben, hogy mit várnak tôlem?";
							link.l1.go = "TakePassenger";
						break;
						//========== Патруль - таможенник ============
						case 6:
							dialog.text = "Épp idôben, kapitány. Egy sürgôs problémával kell foglalkoznom, ami a kolóniánkra irányuló árucsempészettel kapcsolatos. Gondolom, a hajója tengerjáró és harcra kész?";
							link.l1 = "A hajóm mindig tengerrevaló és harcra kész. Kérem, meséljen többet a közelgô küldetésrôl, kegyelmes uram.";
							link.l1.go = "CustomPatrol";
						break;
							//========== Найти дезертира ============
						case 7:
							dialog.text = "Van egy küldetésem az ön számára, ami több karibi település meglátogatását jelenti. Készen áll a hosszú útra?";
							link.l1 = "Igen, az embereim és én készen állunk az azonnali indulásra? Pontosan mit kell tennem?";
							link.l1.go = "FindFugitive";
						break;
					}
				}
			}
			else
			{
				dialog.text = LinkRandPhrase("Ma nem tudok munkát ajánlani.", "Ma már nincs több állás az Ön számára.", "Ma már nincs több állás, sajnálom. Jöjjön el holnap újra, és meglátjuk...");
				link.l1 = RandPhraseSimple("Kár...", "Ah, milyen kár, "+ GetAddress_FormToNPC(NPChar) + ". ");
        		link.l1.go = "exit";
			}
		//---------------------------- генератор квестов мэра -------------------------------
		break;

		case "sell_prisoner":
            dialog.text = "Kit szeretnél kiváltani?";

            qty = 1;
            for(i=0; i < GetPassengersQuantity(pchar); i++)
            {
                cn = GetPassenger(pchar,i);
                if(cn != -1)
                {
                    offref = GetCharacter(cn);
                    if(CheckAttribute(offref,"prisoned"))
                    {
        	            if(sti(offref.prisoned)==true && GetRemovable(offref)) // ставим только фантомов
        	            {
                            attrLoc = "l"+qty;
                            link.(attrLoc)    = GetFullName(offref) + " - " + NationNameMan(sti(offref.nation)) + ".";
                            link.(attrLoc).go = "GetPrisonerIdx_" + offref.index;
                            qty++;
                        }
                    }
                }
            }
			link.l99 = "Senki.";
			link.l99.go = "exit";
		break;
		
		case "sell_prisoner_2":
            offref = GetCharacter(sti(pchar.GenQuest.GetPrisonerIdx));
            attrLoc =  "Tehát ez a kapitány " + GetFullName(offref) + ", " + NationNameMan(sti(offref.nation))+ ".";
            // цена зависит от губернатора
            qty = makeint(sti(offref.rank)*(800 + GetCharacterSPECIALSimple(NPChar, SPECIAL_L)*100) + GetCharacterSkillToOld(offref, "Leadership")*500 + GetCharacterSkillToOld(pchar, "commerce")*500);
			if(HasShipTrait(pchar, "trait14")) qty = makeint(qty * 1.35);
            if (sti(offref.nation) == sti(NPChar.nation))
            {
                attrLoc = attrLoc + " Kész vagyok kifizetni a váltságdíjat honfitársamért  " + FindRussianMoneyString(qty) + "összegben.";
            }
            else
            {
                if (sti(offref.nation) == PIRATE)
                {
                    qty = qty / 5;
                    attrLoc = attrLoc + " Tudok adni " + FindRussianMoneyString(qty) + "  ezért a galambmadárért. Aztán azonnal kivégezzük a gazembert.";

                }
                else
                {
                    qty = qty / 2;
                    attrLoc = attrLoc + " " + FindRussianMoneyString(qty) + "Egy pezóval sem adok többet ezért az emberért.";
                }
            }
			dialog.text = attrLoc;
			pchar.PrisonerSellPrice =  qty;
			link.l1 = "Megegyeztünk. Ô a tiéd, " + GetAddress_FormToNPC(NPChar) + ".";
			link.l1.go = "sell_prisoner_3";
			link.l3 = "Nem. Az nem lesz jó.";
			link.l3.go = "exit";
		break;


		case "sell_prisoner_3":
			dialog.text = "Ez jó.";
			link.l1 = "Minden jót.";
			link.l1.go = "exit";
			OfficersReaction("bad");

			offref = GetCharacter(sti(pchar.GenQuest.GetPrisonerIdx));
			AddMoneyToCharacter(pchar, sti(pchar.PrisonerSellPrice));
			if (sti(offref.nation) == sti(NPChar.nation))
            {
                AddCharacterExpToSkill(pchar, "Commerce", 25);
            }
            else
            {
                if (sti(offref.nation) == PIRATE)
                {
                    ChangeCharacterComplexReputation(pchar,"nobility", -2);
                }
                else
                {
                    AddCharacterExpToSkill(pchar, "Commerce", 5);
                }
            }

        	offref.location = "";
        	ReleasePrisoner(offref); // освободили пленника
		break;
		////   CAPTURE //////////
		case "CAPTURE_Main":
            NextDiag.TempNode = "CAPTURE_Main";
			AfterTownBattle();  // всё, все свободны
			
			// --> Левассер
			if (pchar.location == "Tortuga_townhall" && CheckAttribute(pchar, "questTemp.Sharlie.Hardcore_Tortuga"))
			{
                dialog.Text = "Arrgh! Mi ez a gyalázat, de Maure? Mióta támadnak a franciák a saját honfitársaikra?!";
                Link.l1 = "Francois Longvillier de Poincy fôkormányzó parancsára Önt, Monseiur Levasseur, eltávolítjuk Tortuga kormányzójának posztjáról és halálra ítéljük! És én vagyok az, aki végrehajtja ezt az ítéletet!";
                Link.l1.go = "levasser";
				break;
			}
			// <-- Левассер
            // fix от грабежа 5 раз на дню -->
            if (!CheckNPCQuestDate(npchar, "GrabbingTownDate"))
			{
                dialog.Text = "Ön már mindent elvett. Mi kell még?";
                Link.l1 = "Igen, igaz, rossz város.";
                Link.l1.go = "Exit_City";

                NPChar.NoGiveMoney = true;

            	ChangeCharacterHunterScore(GetMainCharacter(), NationShortName(sti(NPChar.nation)) + "hunter", 20);
                // вернём диалог после разговора и спрячем
                SetReturn_Gover_Dialog_Exit(NPChar);
				break;
			}
			SetNPCQuestDate(npchar, "GrabbingTownDate");
			// fix от грабежа 5 раз на дню <--

            if (CheckAttribute(FortChref, "Fort.Mode") && sti(FortChref.Fort.Mode) != FORT_DEAD)
            { // а форт-то ЖИВ, значит с суши прошли
                dialog.Text = "Példátlan szemtelenség! Hamarosan megérkezik az erôsítés az erôdbôl, és ezért megfizetsz!";
                Link.l2 = "Nem fogok itt maradni, amíg meg nem érkeznek. Csak fizess, és elhagyjuk ezt a várost.";
                Link.l2.go = "Summ";
                Pchar.HalfOfPaymentByCity = true; // токо половина денег
            }
            else
            {
				dialog.Text = "Ezúttal nyertél, de tudd, hogy kalózvadászaink egy osztaga le fog vadászni téged, és minden pezsgôt kitép a mocskos kalózhúsodból!";
	            if (!bWorldAlivePause || bBettaTestMode)
	            {
	                int iColony = FindColony(npchar.city);
					if (!CheckAttribute(&colonies[iColony], "notCaptured")) //незахватываемые города
					{
						if (CheckAttribute(FortChref, "Default.Prison"))
	    				{
	    					Link.l1 = "Csendet! Ez a város mostantól az enyém; ami pedig a kalózvadászaitokat illeti - egyenesen Davy Joneshoz küldöm ôket' Lockerbe. Hé, fiúk, fogjátok meg ezt a disznót, és tegyétek rács mögé!";
	    				}
	    				else
	    				{
	    					Link.l1 = "Ez a város most már az enyém. Fiúk, kísérjétek az ex-kormányzót az új 'negyedébe', heh heh.";
	    				}
	    				Link.l1.go = "City";
					}
				}
				if (!isCityHasFort(NPChar.City))
	            {
	                Link.l2 = "Erôsítés az erôdbôl? Csak fizessetek egy szép váltságdíjat, és elhagyjuk a várost.";
				}
				else
				{
	            	Link.l2 = "Egy csapat kalózvadász? Hmm... Csak fizessetek, és elhagyjuk a várost.";
	            }
				Link.l2.go = "Summ";

                bOk = !bWorldAlivePause || bBettaTestMode;
	            if (isMainCharacterPatented() && bOk && !CheckAttribute(&colonies[iColony], "notCaptured")) //не даем захватить колонию
	            {
					// восстановим нацию патента
					PChar.nation = GetBaseHeroNation();
					
					dialog.Text = "Példátlan szemtelenség! Hogy merészelitek megtámadni a " + NationNameGenitive(sti(NPChar.nation)) + "kolóniát?! Drágán meg fogtok fizetni a kiontott vérért és a kárért, amit államunknak okoztatok.";
	                Link.l1 = "Mostantól kezdve ez a kolónia az enyém. Aki úgy dönt, hogy vitatja a hatalmamat, egyenesen a pokolra kerül.";
	                Link.l1.go = "City_patent";
	                Link.l2 = "Állj le. A " + NationNameGenitive(sti(PChar.nation)) + "nevében cselekszem. Ettôl a ponttól kezdve ez a kolónia a " + NationKingsCrown(PChar) + "!";
	                Link.l2.go = "City_nation";
	                Link.l3 = "Szép város ez itt. Igazi tragédia lenne, ha hamuvá égne, és a kormányzóját felakasztanák a fôtéren. Meg kellene beszélnünk a váltságdíj nagyságát, amit hajlandóak lennének fizetni, hogy megakadályozzák ezt a tragédiát. ";
	                Link.l3.go = "Summ_patent";
	            }
            }
        break;
		
		// --> Левассер
		case "levasser":
            dialog.Text = "Poincy?! Átkozott pápista fattyú! Majd én elintézem... és neked véged, gazember! Nem jutsz ki innen élve - személyesen végzek veled!";
			Link.l1 = "Kímélj meg a prédikálásodtól, eretnek. Amikor a hugenotta lelkedet a pokolba küldöm, add át Lucifernek és Jean Calvinnak a legjobb kívánságaimat. En garde!";
			Link.l1.go = "levasser_1";
        break;
		
		case "levasser_1":
			chrDisableReloadToLocation = true;//закрыть локацию
            DialogExit();
			LAi_SetImmortal(npchar, false);
			ChangeCharacterAddressGroup(npchar, pchar.location, "goto", "goto6");
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "LevasserDiedResidence");
			AddDialogExitQuest("MainHeroFightModeOn");	
        break;
		// <-- Левассер
        
        case "City":
            ChangeCharacterHunterScore(GetMainCharacter(), NationShortName(sti(NPChar.nation)) + "hunter", 40);
            AddCharacterExpToSkill(GetMainCharacter(), "Leadership", 400);

            Pchar.GenQuestFort.fortCharacterIdx = FortChref.index;
            AddDialogExitQuest("Residence_Captured_Any");

            Statistic_AddValue(Pchar, NationShortName(sti(NPChar.nation)) + "_TakeTown", 1);
            // ремонт
            RepairAllShips();
            Log_Info("Minden hajót megjavítottál.");
            //  СЖ -->
			ReOpenQuestHeader("Gen_CityCapture");
	        AddQuestRecordInfo("Gen_CityCapture", "t3");
			AddQuestUserData("Gen_CityCapture", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Gen_CityCapture", "sCity", XI_ConvertString("colony" + NPChar.City));
			//  СЖ <--
            NextDiag.CurrentNode = "Prison";
			DialogExit();
        break;

        case "City_patent":
            ChangeCharacterComplexReputation(GetMainCharacter(),"nobility", -20); // пираты мы, но у нас патент
            dialog.Text = "Ezúttal gyôztél, de tudd, hogy a századunk hamarosan megérkezik, és nem marad belôled semmi!";
			Link.l1 = "Fogd be a szád. Ez a város mostantól az enyém; ami a századodat illeti - egyenesen a pokolba küldöm. Fiúk, kísérjétek az ex-kormányzót az új 'negyedébe', heh heh.";
			Link.l1.go = "City";
        break;

        case "Exit_for_pay":
			dialog.Text = "Mi másra van még szükséged tôlem?";
            Link.l1 = "Csak ellenôrzöm, hogy nem hagytam-e ki valamit...";
            Link.l1.go = "exit";

            NextDiag.TempNode = "Exit_for_pay";
		break;

        case "Exit_City":
		    NextDiag.CurrentNode = "Exit_for_pay";
		    Pchar.GenQuestFort.fortCharacterIdx = FortChref.index;
		    if (sti(NPChar.NoGiveMoney) == false) // себе берем
		    {
				// вернём диалог после разговора и спрячем
				SetReturn_Gover_Dialog_Exit(NPChar);
				AddDialogExitQuestFunction("TWN_ExitForPay");
            }
            DialogExit();
        break;

        case "Summ":
            dialog.Text = "Nincs más választásom, mint elfogadni a feltételeidet. Fogja a rohadt pénzét, és azonnal hagyja el a kolóniánkat.";
            Link.l1 = "Öröm volt önnel üzletelni.";
            Link.l1.go = "Exit_City";
            NPChar.NoGiveMoney = false;

            ChangeCharacterHunterScore(GetMainCharacter(), NationShortName(sti(NPChar.nation)) + "hunter", 30);
            AddCharacterExpToSkill(GetMainCharacter(), SKILL_FORTUNE, 300);
            AddCharacterExpToSkill(GetMainCharacter(), "Commerce", 300);

            Statistic_AddValue(Pchar, NationShortName(sti(NPChar.nation)) + "_GrabbingTown", 1);
            //  СЖ -->
			ReOpenQuestHeader("Gen_CityCapture");
	        AddQuestRecordInfo("Gen_CityCapture", "t2");
			AddQuestUserData("Gen_CityCapture", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Gen_CityCapture", "sCity", XI_ConvertString("colony" + NPChar.City));
			//  СЖ <--
        break;

        case "Summ_patent":
            dialog.Text = "Rendben, mondja meg a feltételeit...";
            Link.l1 = "Aye, vae victis! Kezdjétek el számolni a pénzt.";
            Link.l1.go = "Summ";
            ChangeCharacterComplexReputation(GetMainCharacter(),"nobility", -10); // не на службе
        break;

        case "City_nation":
			dialog.Text = "Rendben, megadjuk magunkat a kegyelmednek.";
			Link.l1 = "Azt tanácsolnám, hogy hagyják el a várost, amilyen hamar csak tudják - a közelgô változások nagyon árthatnak az egészségüknek. Viszlát.";
			Link.l1.go = "Exit_City";
			NPChar.NoGiveMoney = true;

            ChangeCharacterComplexReputation(GetMainCharacter(),"nobility", 5);
            AddCharacterExpToSkill(GetMainCharacter(), "Leadership", 600);
            AddCharacterExpToSkill(GetMainCharacter(), "Sneak", 400);
            SetNationRelationBoth(sti(PChar.nation), sti(NPChar.nation), RELATION_ENEMY);

            PChar.questTemp.DontSetNewDialogToMayor = true; // иначе может сменить диалог и сбойнуть
            PChar.questTemp.DontNullDeposit = true;    // чтоб не нулили ростовщика
            SetCaptureTownByNation(NPChar.City, sti(PChar.nation));
            DeleteAttribute(PChar, "questTemp.DontSetNewDialogToMayor");
            AddDialogExitQuestFunction("LaunchColonyInfoScreen"); // табличка
            //  СЖ -->
	    	sTemp =  GetNationNameByType(sti(PChar.nation));
			ReOpenQuestHeader("Gen_CityCapture");
	        AddQuestRecordInfo("Gen_CityCapture", "t1");
			AddQuestUserData("Gen_CityCapture", "sCity", XI_ConvertString("colony" + NPChar.City));
			AddQuestUserData("Gen_CityCapture", "sNation", XI_ConvertString(sTemp + "Gen"));
			//  СЖ <--
			AddTitleNextRate(sti(PChar.nation), 1);  // счетчик звания
            SetCharacterRelationBoth(sti(FortChref.index), GetMainCharacterIndex(), RELATION_FRIEND);// нечего не даёт, тк работает OtherChar - а это губер, но он и так друг
            UpdateRelations();

            // 22.03.05  fix вернём диалог после разговора и спрячем
            //  внутри диалога не работало
            SetReturn_Gover_Dialog_Exit(NPChar);

            Statistic_AddValue(Pchar, NationShortName(sti(NPChar.nation)) + "_TakeTown", 1);
	    break;
	    
	    case "Prison":
			dialog.Text = "Mit akarsz még tôlem, gazember?";
            Link.l3 = "Hogy tetszik excellenciádnak az új szobája? Elég tágas? Nos, most már mennem kell!";
            Link.l3.go = "exit";
            NextDiag.TempNode = "Prison";
		break;
		
		case "arestFree_1":
			dialog.text = "Megnyugodni? És ezt hogy képzeled?";
            link.l1 = "Azt hiszem, egy " + iTotalTemp*6000 + " pezó összeg még megmenthet, nem igaz?";
			link.l1.go = "arestFree_2";
			link.l2 = "Nem. És itt az ideje, hogy elmenjek. Üdvözlettel.";
			link.l2.go = "arest_1";
		break;

		case "arestFree_2":
            if (GetCharacterSkillToOld(PChar, SKILL_FORTUNE) >= hrand(7) && iTotalTemp < 21)
            {
    			dialog.text = "Azt hiszem, így is elintézhetnénk az incidensünket. Még nem mentél olyan messzire, hogy a helyzetet helyrehozhatatlanná tedd.";
    		    link.l1 = "Kiváló. Nagyon örülök. Kérem, fogadja el az adományomat.";
    		    link.l1.go = "Exit";
    		    AddMoneyToCharacter(pchar, -iTotalTemp*6000);
    		    ChangeCharacterHunterScore(Pchar, NationShortName(sti(NPChar.nation)) + "hunter", -iTotalTemp);
    		    AddCharacterExpToSkill(pchar, "Fortune", 100);
            }
            else
            {
    			dialog.text = "Megvesztegetést ajánl nekem? Ó, nem! A gonosz tetteidért csak egy módon lehet vezekelni... Ôrség! Tegyétek "+ GetSexPhrase("ôt","ôt") +" vasra!";
    		    link.l1 = "Várjatok!";
    		    link.l1.go = "arest_2";
    		    AddCharacterExpToSkill(pchar, "Fortune", 10);
            }
		break;

		case "arest_1":
			dialog.text = "Persze, itt az idô. Elkísérünk. Ôrség! Elfogni "+ GetSexPhrase("ôt","ôt") +"!";
		    link.l1 = "Nem lehet!";
		    link.l1.go = "fight";
		break;

		case "arest_2":
			dialog.text = "Rengeteg idôtök volt gondolkodni! Ôrség!";
			link.l1 = "Nem fogtok egykönnyen elkapni!";
		    link.l1.go = "fight";
		break;    
		/////////////////////////////////////////////////////////////////////////////////////////////////
		//	Уничтожение банды
		/////////////////////////////////////////////////////////////////////////////////////////////////
		case "DestroyGang":
			dialog.text = "Természetesen. A küldetés teljesítéséhez adok neked " + FindRussianDaysString(sti(pchar.GenQuest.DestroyGang.Terms)) + ", és a jutalmad siker esetén " + FindRussianMoneyString(sti(pchar.GenQuest.DestroyGang.Money)) + "lesz.";
			link.l1 = "Igen, elfogadom a feladatot.";
		    link.l1.go = "DestroyGang_agree";
			link.l2 = "Hmm... Nem, azt hiszem, kihagyom.";
		    link.l2.go = "All_disagree";
		break;
		case "DestroyGang_agree":
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_complete";
			pchar.GenQuest.questName = "DestroyGang"; //тип квеста
			pchar.GenQuest.DestroyGang.Location = GetGangLocation(npchar); //определяем локацию,где банда
			pchar.GenQuest.DestroyGang.MayorId  = npchar.id; //Id мэра, чтобы знать, кто дал квест
			if (pchar.GenQuest.DestroyGang.Location == "none") //на всякий случай
			{
				dialog.text = "Várj, elfelejtettem a tegnapi jelentést. A lényeg az, hogy ez a banda már elhagyta a szigetünket. Szóval le kell mondanom a küldetést.";
				link.l1 = "Értem. Kár érte.";
				link.l1.go = "exit";
				DeleteAttribute(pchar, "GenQuest." + pchar.GenQuest.questName);
				DeleteAttribute(pchar, "GenQuest.questName");
			}
			else
			{
				dialog.text = "Nos, remek! A rezidenciámon várom önt és a jelentéseit.";
				link.l1 = "Nem fogom sokáig váratni, " + GetAddress_FormToNPC(NPChar) + ".";
				link.l1.go = "exit";
				pchar.quest.DestroyGang.win_condition.l1 = "location";
				pchar.quest.DestroyGang.win_condition.l1.location = pchar.GenQuest.DestroyGang.Location;
				pchar.quest.DestroyGang.win_condition = "DestroyGang_fight";
				pchar.quest.DestroyGang.again = true; //тупо дожидаться своего часа бандиты не будут
				SetTimerCondition("AllMayorsQuests_Late", 0, 0, sti(pchar.GenQuest.DestroyGang.Terms), false);
				//==> энкаунтеров в квестовой локации не будет 
				locations[FindLocation(pchar.GenQuest.DestroyGang.Location)].DisableEncounters = true;
				ReOpenQuestHeader("MayorsQuestsList");
				AddQuestRecord("MayorsQuestsList", "1");
				AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+npchar.city+"Gen"));
				AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
				makearef(arName, pchar.GenQuest.DestroyGang);
				AddQuestUserData("MayorsQuestsList", "GangName", GetFullName(arName));
				AddQuestUserData("MayorsQuestsList", "sDay", FindRussianDaysString(sti(pchar.GenQuest.DestroyGang.Terms)));
				AddQuestUserData("MayorsQuestsList", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.DestroyGang.Money)));
			}
		break;
		/////////////////////////////////////////////////////////////////////////////////////////////////
		//	Контркурьер
		/////////////////////////////////////////////////////////////////////////////////////////////////
		case "TakePostcureer":
			//установка параметров
			pchar.GenQuest.questName = "TakePostcureer"; //тип квеста
			// belamour legendary edition враждебную нацию квестодателя, а не героя -->
			pchar.GenQuest.TakePostcureer.Nation = FindEnemyNation2Character(sti(npchar.index)); //вражеская нация
			iTemp = 1;
			while (iTemp < 10 && sti(pchar.GenQuest.TakePostcureer.Nation) == PIRATE) {
				pchar.GenQuest.TakePostcureer.Nation = FindEnemyNation2Character(sti(npchar.index));
				iTemp += 1;
			}
			if (iTemp == 10 && sti(pchar.GenQuest.TakePostcureer.Nation) == PIRATE) {
				dialog.text = LinkRandPhrase("Ma nem tudok munkát ajánlani.", "Ma már nincs több állás az Ön számára.", "Ma már nincs több állás, sajnálom. Jöjjön el holnap újra, és meglátjuk...");
				link.l1 = RandPhraseSimple("Kár...", "Ah, milyen kár, "+ GetAddress_FormToNPC(NPChar) + ". ");
        		link.l1.go = "exit";
				
				if (CheckAttribute(pchar, "GenQuest.questName")) {
					QuestName = pchar.GenQuest.questName;
					DeleteAttribute(pchar, "GenQuest." + QuestName);
					DeleteAttribute(pchar, "GenQuest.questName");
				}
				
				break;
			}
			pchar.GenQuest.TakePostcureer.City = FindQuestCity(npchar, "enemy",sti(pchar.GenQuest.TakePostcureer.Nation), false, false);
			// <-- legendary edition
			pchar.GenQuest.TakePostcureer.Island = GetArealByCityName(pchar.GenQuest.TakePostcureer.City);
			pchar.GenQuest.TakePostcureer.Terms = GetMaxDaysFromIsland2Island(Islands[GetCharacterCurrentIsland(PChar)].id, pchar.GenQuest.TakePostcureer.Island)+5;
			pchar.GenQuest.TakePostcureer.LoginDay = sti(pchar.GenQuest.TakePostcureer.Terms)-1;
			pchar.GenQuest.TakePostcureer.ShipType = SelectCureerShipType();
			pchar.GenQuest.TakePostcureer.ShipName = GenerateRandomNameToShip(sti(pchar.GenQuest.TakePostcureer.Nation));
			pchar.GenQuest.TakePostcureer.Cannon = SelectLevelCannonParameter(sti(pchar.GenQuest.TakePostcureer.ShipType));
			pchar.GenQuest.TakePostcureer.Money = ((hrand(5)+hrand(6, "1")+4)*2000)+(sti(pchar.rank)*500);
			dialog.text = "Természetesen. Meg kell keresnie egy "+NationNameGenitive(sti(pchar.GenQuest.TakePostcureer.Nation))+" nevû futárhajót '"+pchar.GenQuest.TakePostcureer.ShipName+"', fel kell szállnia rá, és el kell hoznia nekem a papírokat, amelyeket a kapitányi kabinban kell megtalálnia. Ez a hajó a "+XI_ConvertString("Colony"+pchar.GenQuest.TakePostcureer.City+"Gen")+" közelében fog elhaladni, körülbelül a "+FindRussianDaysString(pchar.GenQuest.TakePostcureer.Terms)+".";
			link.l1 = "Rendben, elfogadom a küldetést. És milyen papírokat keressek?";
		    link.l1.go = "TakePostcureer_agree";
			link.l2 = "Hmm... Nem, azt hiszem, kihagyom.";
		    link.l2.go = "All_disagree";
		break;
		
		case "TakePostcureer_agree":
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_complete";
			pchar.GenQuest.TakePostcureer.MayorId  = npchar.id; //Id мэра, чтобы знать, кто дал квест
			dialog.text = "Posta. Nagyon fontos papírok vannak számomra. De nem kell keresgélnie az iratok között, csak hozza el nekem az egész csomagot. Fizetni fogok neked "+FindRussianMoneyString(sti(pchar.GenQuest.TakePostcureer.Money))+"\nSzóval, várlak téged és a munkád eredményét a lakásomon.";
			link.l1 = "Nem fogom sokáig váratni, " + GetAddress_FormToNPC(NPChar) + ".";
			link.l1.go = "exit";
			pchar.quest.TakePostcureer.win_condition.l1 = "location";
			pchar.quest.TakePostcureer.win_condition.l1.location = pchar.GenQuest.TakePostcureer.Island;
			pchar.quest.TakePostcureer.win_condition.l2 = "Timer";
			pchar.quest.TakePostcureer.win_condition.l2.date.hour  = sti(GetTime());
			pchar.quest.TakePostcureer.win_condition.l2.date.day   = GetAddingDataDay(0, 0, sti(pchar.GenQuest.TakePostcureer.LoginDay));
			pchar.quest.TakePostcureer.win_condition.l2.date.month = GetAddingDataMonth(0, 0, sti(pchar.GenQuest.TakePostcureer.LoginDay));
			pchar.quest.TakePostcureer.win_condition.l2.date.year  = GetAddingDataYear(0, 0, sti(pchar.GenQuest.TakePostcureer.LoginDay));
			pchar.quest.TakePostcureer.function = "TakePostcureer_CreateShip";
			SetTimerCondition("AllMayorsQuests_Late", 0, 0, sti(pchar.GenQuest.TakePostcureer.Terms), false);
			ReOpenQuestHeader("MayorsQuestsList");
			AddQuestRecord("MayorsQuestsList", "3");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+npchar.city+"Gen"));
			AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
			AddQuestUserData("MayorsQuestsList", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.TakePostcureer.City+"Gen"));
			AddQuestUserData("MayorsQuestsList", "sDay", FindRussianDaysString(sti(pchar.GenQuest.TakePostcureer.Terms)));
			AddQuestUserData("MayorsQuestsList", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.TakePostcureer.Money)));
			AddQuestUserData("MayorsQuestsList", "sNation", NationNameGenitive(sti(pchar.GenQuest.TakePostcureer.Nation)));
			AddQuestUserData("MayorsQuestsList", "sShipName", pchar.GenQuest.TakePostcureer.ShipName);
		break;
		
		/////////////////////////////////////////////////////////////////////////////////////////////////
		//	Контрфрахт - уничтожить корабль с арсеналом
		/////////////////////////////////////////////////////////////////////////////////////////////////
		case "TakeArsenalship":
			//установка параметров
			pchar.GenQuest.questName = "TakeArsenalship"; //тип квеста
			// belamour legendary edition враждебную нацию квестодателя, а не героя -->
			pchar.GenQuest.TakeArsenalship.Nation = FindEnemyNation2Character(sti(npchar.index));
			iTemp = 1;
			while (iTemp < 10 && sti(pchar.GenQuest.TakeArsenalship.Nation) == PIRATE) {
				pchar.GenQuest.TakeArsenalship.Nation = FindEnemyNation2Character(sti(npchar.index));
				iTemp += 1;
			}
			if (iTemp == 10 && sti(pchar.GenQuest.TakeArsenalship.Nation) == PIRATE) {
				dialog.text = LinkRandPhrase("Ma nem tudok munkát ajánlani.", "Ma már nincs több állás az Ön számára.", "Ma már nincs több állás, sajnálom. Jöjjön el holnap újra, és meglátjuk...");
				link.l1 = RandPhraseSimple("Kár...", "Ah, milyen kár, "+ GetAddress_FormToNPC(NPChar) + ". ");
        		link.l1.go = "exit";
				
				if (CheckAttribute(pchar, "GenQuest.questName")) {
					QuestName = pchar.GenQuest.questName;
					DeleteAttribute(pchar, "GenQuest." + QuestName);
					DeleteAttribute(pchar, "GenQuest.questName");
				}
				
				break;
			}
			pchar.GenQuest.TakeArsenalship.City = FindQuestCity(npchar, "enemy",sti(pchar.GenQuest.TakeArsenalship.Nation), false, false);
			// <-- legendary edition
			pchar.GenQuest.TakeArsenalship.Island = GetArealByCityName(pchar.GenQuest.TakeArsenalship.City);
			pchar.GenQuest.TakeArsenalship.Terms = GetMaxDaysFromIsland2Island(Islands[GetCharacterCurrentIsland(PChar)].id, pchar.GenQuest.TakeArsenalship.Island)+5;
			pchar.GenQuest.TakeArsenalship.LoginDay = sti(pchar.GenQuest.TakeArsenalship.Terms)-1;
			pchar.GenQuest.TakeArsenalship.ShipType = SelectArsenalShipType(FLAG_SHIP_TYPE_RAIDER);
			pchar.GenQuest.TakeArsenalship.ShipTypeA = SelectArsenalShipType(FLAG_SHIP_TYPE_WAR + FLAG_SHIP_TYPE_UNIVERSAL);
			pchar.GenQuest.TakeArsenalship.ShipName = GenerateRandomNameToShip(sti(pchar.GenQuest.TakeArsenalship.Nation));
			pchar.GenQuest.TakeArsenalship.Cannon = SelectLevelCannonParameter(sti(pchar.GenQuest.TakeArsenalship.ShipType));
			pchar.GenQuest.TakeArsenalship.CannonA = SelectLevelCannonParameter(sti(pchar.GenQuest.TakeArsenalship.ShipTypeA)); // Addon 2016-1 Jason пиратская линейка
			pchar.GenQuest.TakeArsenalship.Money = ((hrand(5)+hrand(6, "1")+4)*1800)+(sti(pchar.rank)*500);
			dialog.text = "Természetesen. Meg kell találnod egy katonai szállítóhajót "+NationNameGenitive(sti(pchar.GenQuest.TakeArsenalship.Nation))+", fedélzetén lôporral és lôszerrel; a hajó neve '"+pchar.GenQuest.TakeArsenalship.ShipName+"', találd meg és semmisítsd meg. Ezzel meggyengítjük az ellenséget\nA szállítóhajó kísérettel fog elhajózni a kolónia "+XI_ConvertString("Colony"+pchar.GenQuest.TakeArsenalship.City)+", és körülbelül "+FindRussianDaysString(pchar.GenQuest.TakeArsenalship.Terms)+", úgyhogy sietni kell.";
			link.l1 = "Rendben, elfogadom. El kell süllyesztenem az arzenálhajót, vagy megpróbáljam elfoglalni?";
		    link.l1.go = "TakeArsenalship_agree";
			link.l2 = "Hmm... Nem, azt hiszem, kihagyom.";
		    link.l2.go = "All_disagree";
		break;
		
		case "TakeArsenalship_agree":
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_complete";
			pchar.GenQuest.TakeArsenalship.MayorId  = npchar.id; //Id мэра, чтобы знать, кто дал квест
			dialog.text = "Nem érdekel, ez rajtad múlik. A lényeg az, hogy ez a rakomány ne érjen célba. Ha sikerül, fizetek neked "+FindRussianMoneyString(sti(pchar.GenQuest.TakeArsenalship.Money))+"... Nem tartom tovább fel, kapitány úr.";
			link.l1 = "Nem fogom sokáig váratni, " + GetAddress_FormToNPC(NPChar) + ".";
			link.l1.go = "exit";
			pchar.quest.TakeArsenalship.win_condition.l1 = "location";
			pchar.quest.TakeArsenalship.win_condition.l1.location = pchar.GenQuest.TakeArsenalship.Island;
			pchar.quest.TakeArsenalship.win_condition.l2 = "Timer";
			pchar.quest.TakeArsenalship.win_condition.l2.date.hour  = sti(GetTime());
			pchar.quest.TakeArsenalship.win_condition.l2.date.day   = GetAddingDataDay(0, 0, sti(pchar.GenQuest.TakeArsenalship.LoginDay));
			pchar.quest.TakeArsenalship.win_condition.l2.date.month = GetAddingDataMonth(0, 0, sti(pchar.GenQuest.TakeArsenalship.LoginDay));
			pchar.quest.TakeArsenalship.win_condition.l2.date.year  = GetAddingDataYear(0, 0, sti(pchar.GenQuest.TakeArsenalship.LoginDay));
			pchar.quest.TakeArsenalship.function = "TakeArsenalship_CreateShip";
			SetTimerCondition("AllMayorsQuests_Late", 0, 0, sti(pchar.GenQuest.TakeArsenalship.Terms), false);
			ReOpenQuestHeader("MayorsQuestsList");
			AddQuestRecord("MayorsQuestsList", "8");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+npchar.city+"Gen"));
			AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
			AddQuestUserData("MayorsQuestsList", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.TakeArsenalship.City));
			AddQuestUserData("MayorsQuestsList", "sDay", FindRussianDaysString(sti(pchar.GenQuest.TakeArsenalship.Terms)));
			AddQuestUserData("MayorsQuestsList", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.TakeArsenalship.Money)));
			AddQuestUserData("MayorsQuestsList", "sNation", NationNameGenitive(sti(pchar.GenQuest.TakeArsenalship.Nation)));
			AddQuestUserData("MayorsQuestsList", "sShipName", pchar.GenQuest.TakeArsenalship.ShipName);
		break;
		
		/////////////////////////////////////////////////////////////////////////////////////////////////
		//	ОЗГ - уничтожить корабль пиратов
		/////////////////////////////////////////////////////////////////////////////////////////////////
		case "TakePirateship":
			//установка параметров
			pchar.GenQuest.questName = "TakePirateship"; //тип квеста
			pchar.GenQuest.TakePirateship.City = FindQuestCity(npchar, "all", -1, true, true); // belamour legendary edition 
			pchar.GenQuest.TakePirateship.Island = GetArealByCityName(pchar.GenQuest.TakePirateship.City);
			pchar.GenQuest.TakePirateship.Terms = GetMaxDaysFromIsland2Island(Islands[GetCharacterCurrentIsland(PChar)].id, pchar.GenQuest.TakePirateship.Island)+5;
			pchar.GenQuest.TakePirateship.ShipType = SelectPirateShipType();
			pchar.GenQuest.TakePirateship.ShipName = GenerateRandomNameToShip(PIRATE);
			pchar.GenQuest.TakePirateship.Name = GenerateRandomName(PIRATE, "man");
			pchar.GenQuest.TakePirateship.Cannon = SelectLevelCannonParameter(sti(pchar.GenQuest.TakePirateship.ShipType));
			pchar.GenQuest.TakePirateship.Money = ((hrand(5)+hrand(6, "1")+4)*2400)+(sti(pchar.rank)*500);
			dialog.text = "Természetesen. Nagyon felháborít egy kalózkapitány tevékenysége, akinek a neve "+pchar.GenQuest.TakePirateship.Name+". Ez a gazember beleesett abba a szokásba, hogy a mi kereskedelmi hajóinkat fosztogatja, ami óriási kárt okoz a gyarmatok közötti kereskedelemnek. Most itt a tökéletes alkalom, hogy megszabaduljunk ettôl a szemétládától, mert történetesen tudom, hol bujkál jelenleg. Készen állsz arra, hogy ezt a szajhát Isten ítélôszékére küldd?";
			link.l1 = "Megtiszteltetés lenne! Hol találom ezt a kalózt?";
		    link.l1.go = "TakePirateship_agree";
			link.l2 = "Hmm... Nem, azt hiszem, kihagyom.";
		    link.l2.go = "All_disagree";
		break;
		
		case "TakePirateship_agree":
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_complete";
			pchar.GenQuest.TakePirateship.MayorId  = npchar.id; //Id мэра, чтобы знать, кто дал квест
			dialog.text = "A legközelebbi "+FindRussianDaysString(pchar.GenQuest.TakePirateship.Terms)+" hajója a '"+pchar.GenQuest.TakePirateship.ShipName+"' nevet viselô hajója a "+XI_ConvertString("Colony"+pchar.GenQuest.TakePirateship.City+"Gen")+"közeli partoknál fog cirkálni. Találjátok meg és öljétek meg. Küldjétek a hajóval etetni a halakat, szálljatok fel a hajóra - nem érdekel. Csak az érdekel, hogy az átkozott kalóz ne szennyezze tovább a tengerünket a jelenlétével\nEzért a feladatért hajlandó vagyok fizetni neked "+FindRussianMoneyString(sti(pchar.GenQuest.TakePirateship.Money))+". Ne vesztegesse az idôt, kapitány: ez a gazember nem fog várni önre "+XI_ConvertString("Colony"+pchar.GenQuest.TakePirateship.City+"Gen")+". Menjetek, és Isten segítsen titeket!";
			link.l1 = "Máris horgonyt vetünk, " + GetAddress_FormToNPC(NPChar) + "! Nem fog sokáig várni.";
			link.l1.go = "exit";
			pchar.quest.TakePirateship.win_condition.l1 = "location";
			pchar.quest.TakePirateship.win_condition.l1.location = pchar.GenQuest.TakePirateship.Island;
			pchar.quest.TakePirateship.function = "TakePirateship_CreateShip";
			SetTimerCondition("AllMayorsQuests_Late", 0, 0, sti(pchar.GenQuest.TakePirateship.Terms), false);
			ReOpenQuestHeader("MayorsQuestsList");
			AddQuestRecord("MayorsQuestsList", "9");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+npchar.city+"Gen"));
			AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
			AddQuestUserData("MayorsQuestsList", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.TakePirateship.City+"Gen"));
			AddQuestUserData("MayorsQuestsList", "sDay", FindRussianDaysString(sti(pchar.GenQuest.TakePirateship.Terms)));
			AddQuestUserData("MayorsQuestsList", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.TakePirateship.Money)));
			AddQuestUserData("MayorsQuestsList", "sName", pchar.GenQuest.TakePirateship.Name);
			AddQuestUserData("MayorsQuestsList", "sShipName", pchar.GenQuest.TakePirateship.ShipName);
		break;
		
		/////////////////////////////////////////////////////////////////////////////////////////////////
		//	ОЗГ - захватить пассажира
		/////////////////////////////////////////////////////////////////////////////////////////////////
		case "TakePassenger":
			//установка параметров
			pchar.GenQuest.questName = "TakePassenger"; //тип квеста
			pchar.GenQuest.TakePassenger.Nation = FindEnemyNation2Character(sti(npchar.index));//вражеская нация
			iTemp = 1;
			while (iTemp < 10 && sti(pchar.GenQuest.TakePassenger.Nation) == PIRATE) {
				pchar.GenQuest.TakePassenger.Nation = FindEnemyNation2Character(sti(npchar.index));
				iTemp += 1;
			}
			if (iTemp == 10 && sti(pchar.GenQuest.TakePassenger.Nation) == PIRATE) {
				dialog.text = LinkRandPhrase("Ma nem tudok munkát ajánlani.", "Ma már nincs több állás az Ön számára.", "Ma már nincs több állás, sajnálom. Jöjjön el holnap újra, és meglátjuk...");
				link.l1 = RandPhraseSimple("Kár...", "Ah, milyen kár, "+ GetAddress_FormToNPC(NPChar) + ". ");
        		link.l1.go = "exit";
				
				if (CheckAttribute(pchar, "GenQuest.questName")) {
					QuestName = pchar.GenQuest.questName;
					DeleteAttribute(pchar, "GenQuest." + QuestName);
					DeleteAttribute(pchar, "GenQuest.questName");
				}
				
				break;
			}
			pchar.GenQuest.TakePassenger.City = FindQuestCity(npchar, "enemy", sti(pchar.GenQuest.TakePassenger.Nation), false, false); // belamour legendary edition
			pchar.GenQuest.TakePassenger.CityA = SelectAnyColony(pchar.GenQuest.TakePassenger.City);
			pchar.GenQuest.TakePassenger.Terms1 = GetMaxDaysFromIsland2Island(Islands[GetCharacterCurrentIsland(PChar)].id, GetArealByCityName(pchar.GenQuest.TakePassenger.City));
			pchar.GenQuest.TakePassenger.Terms2 = GetMaxDaysFromIsland2Island(GetArealByCityName(pchar.GenQuest.TakePassenger.City), GetArealByCityName(pchar.GenQuest.TakePassenger.CityA))+1;
			pchar.GenQuest.TakePassenger.Terms = sti(pchar.GenQuest.TakePassenger.Terms1)+sti(pchar.GenQuest.TakePassenger.Terms2);
			pchar.GenQuest.TakePassenger.ShipType = SelectCureerShipType();
			pchar.GenQuest.TakePassenger.ShipName = GenerateRandomNameToShip(sti(pchar.GenQuest.TakePassenger.Nation));
			pchar.GenQuest.TakePassenger.Name = GenerateRandomName(sti(pchar.GenQuest.TakePassenger.Nation), "man");
			pchar.GenQuest.TakePassenger.Cannon = SelectLevelCannonParameter(sti(pchar.GenQuest.TakePassenger.ShipType));
			pchar.GenQuest.TakePassenger.Money = ((hrand(5)+hrand(6, "1")+4)*2200)+(sti(pchar.rank)*500);
			string sText = SelectPassText();
			dialog.text = "Természetesen. Egy "+pchar.GenQuest.TakePassenger.Name+"nevû gazemberrôl beszélek. "+sText+" Már jó ideje kerestem ôt, és most végre megbízható információhoz jutottam, hogy hol található. Szeretném, ha elhoznád nekem ezt az embert, méghozzá élve. Nyilvánosan akarom felakasztani a városunk fôterén. Készen állsz a küldetésre?";
			link.l1 = "Készen állok, " + GetAddress_FormToNPC(NPChar) + ". Hol találom ezt a gazembert?";
		    link.l1.go = "TakePassenger_agree";
			link.l2 = "Hmm... Nem, azt hiszem, kihagyom.";
		    link.l2.go = "All_disagree";
		break;
		
		case "TakePassenger_agree":
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_complete";
			pchar.GenQuest.TakePassenger.MayorId  = npchar.id; //Id мэра, чтобы знать, кто дал квест
			dialog.text = "Éppen a "+FindRussianDaysString(pchar.GenQuest.TakePassenger.Terms1)+", ô, mint egy hajó utasaként a '"+pchar.GenQuest.TakePassenger.ShipName+"'nevû hajón fog kihajózni a "+XI_ConvertString("Colony"+pchar.GenQuest.TakePassenger.City+"Gen")+" és a "+XI_ConvertString("Colony"+pchar.GenQuest.TakePassenger.CityA+"Acc")+". Neked "+FindRussianDaysString(pchar.GenQuest.TakePassenger.Terms)+" kell megtalálnod ezt a hajót a megadott útszakaszon, felszállni és elfogni ezt a fattyút. Ha követed ezt az utasítást, fizetek neked "+FindRussianMoneyString(sti(pchar.GenQuest.TakePassenger.Money))+". Sok szerencsét, kapitány!";
			link.l1 = "Nem vesztegetem tovább az idôt, " + GetAddress_FormToNPC(NPChar) + "! Azonnal vitorlát bontok.";
			link.l1.go = "exit";
			SetFunctionTimerCondition("TakePassenger_CreateShip", 0, 0, sti(pchar.GenQuest.TakePassenger.Terms1), false);
			SetTimerCondition("AllMayorsQuests_Late", 0, 0, sti(pchar.GenQuest.TakePassenger.Terms), false);
			ReOpenQuestHeader("MayorsQuestsList");
			AddQuestRecord("MayorsQuestsList", "10");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+npchar.city+"Gen"));
			AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
			AddQuestUserData("MayorsQuestsList", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.TakePassenger.City+"Gen"));
			AddQuestUserData("MayorsQuestsList", "sCityA", XI_ConvertString("Colony"+pchar.GenQuest.TakePassenger.CityA+"Acc"));
			AddQuestUserData("MayorsQuestsList", "sDay1", FindRussianDaysString(sti(pchar.GenQuest.TakePassenger.Terms1)));
			AddQuestUserData("MayorsQuestsList", "sDay2", FindRussianDaysString(sti(pchar.GenQuest.TakePassenger.Terms)));
			AddQuestUserData("MayorsQuestsList", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.TakePassenger.Money)));
			AddQuestUserData("MayorsQuestsList", "sName", pchar.GenQuest.TakePassenger.Name);
			AddQuestUserData("MayorsQuestsList", "sShipName", pchar.GenQuest.TakePassenger.ShipName);
		break;
		
		/////////////////////////////////////////////////////////////////////////////////////////////////
		//	Таможенный патруль
		/////////////////////////////////////////////////////////////////////////////////////////////////
		case "CustomPatrol":
			//установка параметров
			pchar.GenQuest.questName = "CustomPatrol"; //тип квеста
			pchar.GenQuest.CustomPatrol.Nation = sti(npchar.nation);//нация
			pchar.GenQuest.CustomPatrol.Island = Islands[GetCharacterCurrentIsland(PChar)].id;
			pchar.GenQuest.CustomPatrol.LoginDay = rand(4)+1;
			pchar.GenQuest.CustomPatrol.Loginlocator = rand(3)+4;
			pchar.GenQuest.CustomPatrol.ShipType = SelectCustomPatrolShipType(FLAG_SHIP_TYPE_WAR + FLAG_SHIP_TYPE_UNIVERSAL);
			pchar.GenQuest.CustomPatrol.ShipTypeA = SelectCustomPatrolShipType(FLAG_SHIP_TYPE_RAIDER);
			pchar.GenQuest.CustomPatrol.Cannon = SelectLevelCannonParameter(sti(pchar.GenQuest.CustomPatrol.ShipType));
			pchar.GenQuest.CustomPatrol.Money = ((hrand(5)+hrand(6, "1")+4)*1400)+(sti(pchar.rank)*300);
			dialog.text = "Megbízható információim vannak arról, hogy egy kapitány csempészekkel üzletet kötött néhány rabszolga eladásáról. Mint az önök elôtt is ismeretes, a gyarmatainkon a magánszemélyek ilyen ügyletei csempészárunak minôsülnek\nA probléma abból áll, hogy nem tudom sem a pontos idôpontot, sem a dátumot, sem a helyet, ahol a csempészek találkoznak. Csak az ismert, hogy a legközelebbi öt napban a mi szigetünkön fog megvalósulni egy bûnügyi tranzakció. Hogy még rosszabb legyen, minden járôrhajóm vagy javításon van, vagy más feladatokban vesz részt, és nem találják ezeket a gazembereket\nAzt javaslom, hogy foglalkozzanak ezzel a feladattal - keressék fel a csempészeket, és a legradikálisabb módszerekkel bánjanak el velük, csináljanak példát belôlük. Készen állsz erre a küldetésre?";
			link.l1 = "Készen állok, " + GetAddress_FormToNPC(NPChar) + ". Mondja, van további információja? Mint például a kapitány neve, a hajó neve vagy típusa?";
		    link.l1.go = "CustomPatrol_agree";
			link.l2 = "Hmm... Nem, azt hiszem, kihagyom.";
		    link.l2.go = "All_disagree";
		break;
		
		case "CustomPatrol_agree":
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_complete";
			pchar.GenQuest.CustomPatrol.MayorId  = npchar.id; //Id мэра, чтобы знать, кто дал квест
			dialog.text = "A forrásom most mondta, hogy az üzlet elôkészítés alatt áll, és be is fogják fejezni. Ennyi. Szóval csak nézzenek meg alaposabban minden gyanús hajót a vizeinken. Ha sikerrel jársz, fizetek neked egy összeget "+FindRussianMoneyString(sti(pchar.GenQuest.CustomPatrol.Money))+"\nTovábbá a körülményekre való tekintettel felhatalmazlak, hogy összeszedd az összes csempészárut, amit találsz. Természetesen nem hivatalosan, feltéve, hogy nem fogja eladni a városunkban.";
			link.l1 = "Egészen zseniális. Jól van, rátérek a kolóniátok vizeinek járôrözésére, " + GetAddress_FormToNPC(NPChar) + ".";
			link.l1.go = "exit";
			SetTimerCondition("AllMayorsQuests_Late", 0, 0, 6, false);
			pchar.quest.CustomPatrol.win_condition.l1 = "location";
			pchar.quest.CustomPatrol.win_condition.l1.location = pchar.GenQuest.CustomPatrol.Island;
			pchar.quest.CustomPatrol.win_condition.l2 = "Timer";
			pchar.quest.CustomPatrol.win_condition.l2.date.hour  = sti(GetTime()+rand(8));
			pchar.quest.CustomPatrol.win_condition.l2.date.day   = GetAddingDataDay(0, 0, sti(pchar.GenQuest.CustomPatrol.LoginDay));
			pchar.quest.CustomPatrol.win_condition.l2.date.month = GetAddingDataMonth(0, 0, sti(pchar.GenQuest.CustomPatrol.LoginDay));
			pchar.quest.CustomPatrol.win_condition.l2.date.year  = GetAddingDataYear(0, 0, sti(pchar.GenQuest.CustomPatrol.LoginDay));
			pchar.quest.CustomPatrol.function = "CustomPatrol_CreateShip";
			ReOpenQuestHeader("MayorsQuestsList");
			AddQuestRecord("MayorsQuestsList", "11");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+npchar.city+"Gen"));
			AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
			AddQuestUserData("MayorsQuestsList", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.CustomPatrol.Money)));
		break;
		
		/////////////////////////////////////////////////////////////////////////////////////////////////
		//	Найти дезертира
		/////////////////////////////////////////////////////////////////////////////////////////////////
		case "FindFugitive":
			//установка параметров
			pchar.GenQuest.questName = "FindFugitive"; //тип квеста
			pchar.GenQuest.FindFugitive.Startcity = npchar.city;
			pchar.GenQuest.FindFugitive.City = SelectFugitiveCity();
			pchar.GenQuest.FindFugitive.Chance = rand(2);
			pchar.GenQuest.FindFugitive.Name = GenerateRandomName(sti(npchar.Nation), "man");
			pchar.GenQuest.FindFugitive.Money = ((hrand(5)+hrand(6, "1")+4)*2600)+(sti(pchar.rank)*600);
			sText = SelectFugitiveText();
			log_testinfo(pchar.GenQuest.FindFugitive.City);
			log_testinfo(FindRussianDaysString(sti(pchar.GenQuest.FindFugitive.Chance)));
			dialog.text = "Mindent részletesen elmondok. Egy nagyon csúnya történet történt - "+sText+". Kollégáit és barátait kikérdezve, úgy véljük, nem alaptalanul, hogy a dezertôr a kalózok közé menekült az egyik településükön\nAzt javaslom, látogassanak el a kalózfészekbe, találják meg a szökevényt, tartóztassák le és szállítsák ide. A dezertálás súlyos bûncselekmény, és nem maradhat büntetlenül. Készen állsz erre a küldetésre?";
			link.l1 = "Készen állok, " + GetAddress_FormToNPC(NPChar) + ". Meg tudod mondani a dezertôr nevét?";
		    link.l1.go = "FindFugitive_agree";
			link.l2 = "Hmm... Nem, azt hiszem, kihagyom.";
		    link.l2.go = "All_disagree";
		break;
		
		case "FindFugitive_agree":
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_complete";
			pchar.GenQuest.FindFugitive.MayorId  = npchar.id; //Id мэра, чтобы знать, кто дал квест
			dialog.text = "Igen, természetesen. A neve "+pchar.GenQuest.FindFugitive.Name+". Erôsen kétlem, hogy az egyenruháját viselné, szóval nézzétek meg közelebbrôl mindenféle söpredéket. Egy hónapot adok a keresésre, mert attól tartok, hogy utána már nem lenne értelme keresni. Ha sikerrel jársz, fizetek neked egy összeget "+FindRussianMoneyString(sti(pchar.GenQuest.FindFugitive.Money))+".";
			link.l1 = "Nem vesztegetem tovább az idôt, " + GetAddress_FormToNPC(NPChar) + "! Azonnal vitorlát bontok.";
			link.l1.go = "exit";
			SetTimerCondition("AllMayorsQuests_Late", 0, 0, 30, false);
			ReOpenQuestHeader("MayorsQuestsList");
			AddQuestRecord("MayorsQuestsList", "12");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+npchar.city+"Gen"));
			AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
			AddQuestUserData("MayorsQuestsList", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.FindFugitive.Money)));
			AddQuestUserData("MayorsQuestsList", "sName", pchar.GenQuest.FindFugitive.Name);
			//создаем дезертира
			sld = GetCharacter(NPC_GenerateCharacter("Fugitive", "citiz_"+(21+rand(9)), "man", "man", sti(pchar.rank)+MOD_SKILL_ENEMY_RATE, sti(npchar.nation), 30, true, "soldier"));
			SetFantomParamFromRank(sld, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE, true);
			sld.name = pchar.GenQuest.FindFugitive.Name;
			sld.lastname = "";
			sld.dialog.FileName = "MayorQuests_dialog.c";
			sld.greeting = "marginal";
		break;
		/////////////////////////////////////////////////////////////////////////////////////////////////
		//	Проникновение во враждебный город
		/////////////////////////////////////////////////////////////////////////////////////////////////
		case "Intelligence":
			dialog.text = "Értem. Talán egy " + FindRussianMoneyString(sti(pchar.GenQuest.Intelligence.Money)) + " jutalom jó ösztönzô lesz számodra.";
			link.l1 = "Igen, ez tisztességes pénz... Elfogadom ezt a küldetést.";
		    link.l1.go = "Intelligence_agree";
			link.l2 = "Hmm... Nem, azt hiszem, visszautasítom. Ez túl veszélyes.";
		    link.l2.go = "All_disagree";
		break;
		case "Intelligence_agree":
			if (pchar.GenQuest.Intelligence.City == "none" || isBadReputation(pchar, 30)) //на всякий случай
			{
				dialog.text = "Bár nem mondhatom, hogy teljesen megbízom benned... Azt hiszem, nem adom neked ezt a küldetést.";
				link.l1 = "Oh, nos... Kár, de nem tehetek semmit.";
				link.l1.go = "exit";
				DeleteAttribute(pchar, "GenQuest." + pchar.GenQuest.questName);
			}
			else
			{
				npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_complete";
				pchar.GenQuest.questName = "Intelligence"; //тип квеста
				sTemp = pchar.GenQuest.Intelligence.City;
				switch (rand(4))
				{
					case 0:	sTemp += "_Priest";		break;
					case 1:	sTemp += "_trader";		break;
					case 2:	sTemp += "_shipyarder"; break;
					case 3:	sTemp += "_usurer";	    break;
					case 4:	sTemp += "_PortMan";	break;
				}
				pchar.GenQuest.Intelligence.SpyId = sTemp; //Id нашего шпиона в городе
				dialog.text = "Nagyszerû! Most pedig térjünk rá az üzletre. A " + XI_ConvertString("Colony"+pchar.GenQuest.Intelligence.City+"Dat") + " -ban meg kell találnod egy helyi " + GetWorkTypeOfMan(&characters[GetCharacterIndex(sTemp)], "Gen") + 
					", a neve " + GetFullName(&characters[GetCharacterIndex(sTemp)]) + ". Megmondod neki a nevemet, és ô ad neked egy csomag dokumentumot. Hogy ezt a csomagot a kezembe adjam, adok neked " + FindRussianDaysString(sti(pchar.GenQuest.Intelligence.Terms)) + ". És tartsd észben, hogy mindent titokban kell csinálni. Ha az ön álcája leleplezôdik, az ügynök nem fogja megkockáztatni, hogy megpróbálja felvenni a kapcsolatot. Világos?";
				link.l1 = "Igen, értem, " + GetAddress_FormToNPC(NPChar) + ". Azonnal elkezdem.";
				link.l1.go = "exit";
				pchar.GenQuest.Intelligence.MayorId  = npchar.id; //Id мэра, чтобы знать, кто дал квест
				SaveCurrentQuestDateParam("GenQuest.Intelligence"); //запись даты получения квеста
				ReOpenQuestHeader("MayorsQuestsList");
				AddQuestRecord("MayorsQuestsList", "6");
				AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+npchar.city+"Gen"));
				AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
				AddQuestUserData("MayorsQuestsList", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Intelligence.City+"Acc"));
				AddQuestUserData("MayorsQuestsList", "sIsland", XI_ConvertString(colonies[FindColony(pchar.GenQuest.Intelligence.City)].islandLable+"Dat"));
				AddQuestUserData("MayorsQuestsList", "sWho", GetWorkTypeOfMan(&characters[GetCharacterIndex(sTemp)], "Gen"));
				AddQuestUserData("MayorsQuestsList", "SpyName", GetFullName(&characters[GetCharacterIndex(sTemp)]));			
				AddQuestUserData("MayorsQuestsList", "sDay", FindRussianDaysString(sti(pchar.GenQuest.Intelligence.Terms)));
				AddQuestUserData("MayorsQuestsList", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Intelligence.Money)));
				AddQuestUserData("MayorsQuestsList", "sCity2", XI_ConvertString("Colony"+pchar.GenQuest.Intelligence.City+"Dat"));
			}
		break;
		case "Intelligence_ExecuteLate":
			QuestName = pchar.GenQuest.questName;
			pchar.GenQuest.(QuestName).Money = sti(pchar.GenQuest.(QuestName).Money) / 2);
			dialog.text = RandPhraseSimple("Nem rossz. De nem tartottad be a határidôt, és ezért egy kicsit csökkentenem kell a jutalmadat. Mostantól a díjazásod " + FindRussianMoneyString(sti(pchar.GenQuest.(QuestName).Money)) + "lesz. Tessék.", 
				"Ez jó. De a határidôt nem tudtad tartani, és én már vártam ezeket a leveleket. Elrontottad a terveimet, ezért kénytelen vagyok egy kicsit csökkenteni a jutalmadat. Mégis, örömmel adom át neked a megérdemelt jutalmadat - " + FindRussianMoneyString(sti(pchar.GenQuest.(QuestName).Money))  + ". Tessék.");
			link.l1 = "Nem mondanám, hogy ez nekem kedves, de végül is a határidôket valóban megsértették. Szóval nincs panaszom, " + GetAddress_FormToNPC(NPChar) + ".";
		    link.l1.go = "All_Execute_1";
			//--> слухи
			AddSimpleRumour(RandPhraseSimple("Tudod, a kormányzó " + GetFullName(npchar) + " nem nagyon örül a kapitány gyorsaságának " + GetMainCharacterNameGen() + ".", 
				"kormányzó " + GetFullName(npchar) + " nem nagyon elégedett a kapitánnyal " + GetMainCharacterNameDat() + ", "+ GetSexPhrase("aki","aki") +" teljesítette a parancsát, de nem idôben..."), sti(npchar.nation), 5, 1);
			//<-- слухи
		break;
		
		// -------------- общий набор для всех квестов мэра ------------------
		case "All_disagree":
			dialog.text = "Csalódást okozol nekem!";
			link.l1 = "Sajnálom, " + GetAddress_FormToNPC(NPChar) + ", de nem tudom elfogadni ezt a munkát.";
		    link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			
			if (CheckAttribute(pchar, "GenQuest.questName"))
			{
				QuestName = pchar.GenQuest.questName;
				DeleteAttribute(pchar, "GenQuest." + QuestName);
				DeleteAttribute(pchar, "GenQuest.questName");
			}
		break;
		case "All_Late":
			QuestName = pchar.GenQuest.questName;
			dialog.text = RandPhraseSimple("Nos, nagyon rossz - mi mást mondhatnék. Számítottam rád - és kiderült, hogy csak az idômet vesztegettem. Csalódott vagyok.", 
				"Nos, azt kell mondanom, hogy teljesen csalódtam benned... Rengeteg ember van a lakhelyemen, akik mindig készen állnak arra, hogy ilyen ügyeket intézzenek nekem - és én rád pazaroltam az idômet. Hát igen...");
			link.l1 = "Sajnálom, " + GetAddress_FormToNPC(NPChar) + ", mindent megtettem, amit tudtam.";
		    link.l1.go = "exit";
			//--> слухи
			AddSimpleRumour(LinkRandPhrase("Tudod, a kormányzó " + GetFullName(npchar) + " nagyon elégedetlen a kapitánnyal " + GetMainCharacterNameDat() + ". Képzeljék csak el - nem teljesítette idôben a feladatát!", 
				"kormányzó " + GetFullName(npchar) + " kissé bosszús, hogy egy kapitány " + GetFullName(pchar) + " vállat vont, de nem teljesítette idôben a feladatát. Kár érte...", 
				"hallottam, hogy a kormányzó " + GetFullName(npchar) + " nagyon elégedetlen önnel, kapitány " + GetFullName(pchar) + ", mivel nem tartotta be a határidôt, miközben megpróbálta teljesíteni a feladatát."), sti(npchar.nation), 5, 1);
			//<-- слухи
			ChangeCharacterComplexReputation(pchar,"nobility", -4);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
			DeleteAttribute(pchar, "GenQuest." + QuestName);
			DeleteAttribute(pchar, "GenQuest.questName");
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_common"; //реплику вертаем
			SaveCurrentNpcQuestDateParam(npchar, "work_date"); //сразу ещё один не даем
			CloseQuestHeader("MayorsQuestsList");
		break;
		case "All_Found":
			QuestName = pchar.GenQuest.questName;
			dialog.text = RandPhraseSimple("Egyszerûen meg vagyok döbbenve! Sikerült megtalálnod a célpontodat, de nem törôdtél a fölényed biztosításának eszközeivel - ez rendkívüli vakmerôség. Csalódott vagyok!", 
				"Nos, azt kell mondanom, hogy csalódtam benned... Nem elég megtalálni a célpontot - kell, hogy legyenek eszközeid a megsemmisítésére. Sok gyilkos van a rezidenciámon, akik mindig készen állnak arra, hogy ilyen megbízásokat teljesítsenek nekem. Mégis mit gondoltam, amikor hozzád fordultam?");
			link.l1 = "Sajnálom, " + GetAddress_FormToNPC(NPChar) + ", de nem vagyok hajlandó vakmerôen kockáztatni a saját életemet.";
		    link.l1.go = "exit";
			//--> слухи
			AddSimpleRumour(LinkRandPhrase("Tudod, a kormányzó " + GetFullName(npchar) + " nagyon elégedetlen a kapitánnyal " + GetMainCharacterNameDat() + ". Képzeld, "+ GetSexPhrase("kiderült, hogy ô egy egyenesen gyáva","kiderült, hogy ô egy egyenesen gyáva") +"!", 
				"kormányzó " + GetFullName(npchar) + " kissé bosszús, hogy egy kapitány " + GetFullName(pchar) + " elvállalta a munkát, de saját határozatlansága miatt nem tudta végrehajtani. Hej-héj, mit akarnak a kapitányok!", 
				"hallottam, hogy a kormányzó " + GetFullName(npchar) + " nagyon elégedetlen veled, kapitány " + GetFullName(pchar) + ". Azt mondják, hogy maga nem más, mint egy gyáva"+ GetSexPhrase("","") +"..."), sti(npchar.nation), 5, 1);
			//<-- слухи
			ChangeCharacterComplexReputation(pchar,"nobility", -6);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
			DeleteAttribute(pchar, "GenQuest." + QuestName);
			DeleteAttribute(pchar, "GenQuest.questName");
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_common"; //реплику вертаем
			SaveCurrentNpcQuestDateParam(npchar, "work_date"); //сразу ещё один не даем
			CloseQuestHeader("MayorsQuestsList");
			AddQuestRecord("MayorsQuestsList", "21");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+npchar.city+"Gen"));
			AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
		break;
		case "All_Execute":
			QuestName = pchar.GenQuest.questName;
			dialog.text = RandPhraseSimple("Kiváló hír! Nos, itt az ideje, hogy összegezzünk. Az Ön díja " + FindRussianMoneyString(sti(pchar.GenQuest.(QuestName).Money)) + "lesz. Tessék.", 
				"Excellent! Ez az út a legjobb mindenkinek... Nos, örömmel adom át az önnek járó jutalmat - " + FindRussianMoneyString(sti(pchar.GenQuest.(QuestName).Money))  + ". Tessék.");
			link.l1 = "Köszönöm, " + GetAddress_FormToNPC(NPChar) + ", " + RandPhraseSimple("öröm veled üzletelni!", "Kellemesen meglepett a települések tisztasága.");
		    link.l1.go = "All_Execute_1";
			//--> слухи
			AddSimpleRumour(LinkRandPhrase("Tudod, a kormányzó " + GetFullName(npchar) + "  dicsérte szorgalmáért"+ GetSexPhrase("egy kapitányt","egy fiatal hölgyet") +" " + GetMainCharacterNameGen() + ".", 
				"kormányzó " + GetFullName(npchar) + " dicséri a kapitányt " + GetMainCharacterNameGen() + ", "+ GetSexPhrase("ô","ô") +" mindig hibátlanul teljesít, ha a kormányzó megbízatásairól van szó. Pótolhatatlan személy a kormányzó számára, mondom én...", 
				"hallottam, hogy a kormányzó " + GetFullName(npchar) + " nagyon elégedett önnel, kapitány " + GetFullName(pchar) + ". Önt nagyon gondos és alapos tisztnek tartja. Ezt nagyon jó hallani, kapitány..."), sti(npchar.nation), 5, 1);
			//<-- слухи
		break;
		case "All_Execute_1":
			QuestName = pchar.GenQuest.questName;
			dialog.text = RandPhraseSimple("Nagyon jó. Jöjjön el hozzám máskor is - talán találok magának másik munkát.", "Nos, remek! Gondolom, megint ilyen munkát fogok neked ajánlani.");
			link.l1 = RandPhraseSimple("Remek.", "Jó.");
		    link.l1.go = "exit";
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.(QuestName).Money));
			CloseQuestHeader("MayorsQuestsList");
			ChangeCharacterComplexReputation(pchar,"nobility", 4);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			AddCharacterExpToSkill(PChar, "Leadership", 180);
			OfficersReaction("good"); // dlc
			
			DeleteAttribute(pchar, "GenQuest." + QuestName);
			DeleteAttribute(pchar, "GenQuest.questName");
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_common"; //реплику вертаем
			SaveCurrentNpcQuestDateParam(npchar, "work_date"); //сразу ещё один не даем
			// инкремент в базу заданий мэров
			sTemp = npchar.City;
			if (!CheckAttribute(pchar, "GenQuest.MayorQuestsList." + sTemp)) pchar.GenQuest.MayorQuestsList.(sTemp) = 0;
			pchar.GenQuest.MayorQuestsList.(sTemp) = sti(pchar.GenQuest.MayorQuestsList.(sTemp)) + 1;
		break;
//<-- осады homo
		case "siege_task":
            makearef(aData, NullCharacter.Siege);
            aData.HelpColony = true;
			dialog.text = "Ezekben a nehéz idôkben minden segítség nagyon jól jön. Elfogadjuk a segítségeteket - segítsetek megvédeni a kolóniánkat, és megjutalmazunk titeket.";
			link.l1 = "Akkor ne vesztegessük az idôt.";
		    link.l1.go = "exit";
		break;
		
		//Jason --> Бремя гасконца
		case "Sharlie":
			dialog.text = "Michel de Monper-t keresi? Érdekes... És mire van rá szüksége?";
			link.l1 = "A testvére vagyok. Az apám mondta, hogy Michel bajban van és segítségre van szüksége, ezért...";
			link.l1.go = "Sharlie_1";			
		break;
		
		case "Sharlie_1":
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "First time";
			DelLandQuestMark(sld);
			dialog.text = "Te vagy az? Nem emlékszem, hogy Monsieur de Monper-nek lett volna testvére... Tudja, uram, maga nagyon gyanús nekem... ezért letartóztatom további nyomozás céljából. Hadnagy úr! Vegye ôrizetbe ezt az embert!";
			link.l1 = "De ôlordsága!";
			link.l1.go = "exit";
			if (GetCharacterIndex("SharlieKnown") != -1)
			{
				sld = characterFromId("SharlieKnown");
				sld.lifeday = 0;
			}	
			AddDialogExitQuestFunction("Sharlie_enterSoldiers");
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "Sharlie_2":
			QuestPointerDelLoc("Fortfrance_town", "reload", "reload3_back");
			dialog.text = "És még mindig szeretnék jóvátételt kérni. Tessék - kérem, vegye el ezt a kardot, ezt a pisztolyt és ezt a könnyû páncélt - ez az én ajándékom önnek. Azt hiszem, hasznosnak fogja találni ezeket a dolgokat.";
			link.l1 = "Köszönöm, uram. Tekintettel arra, hogy az ôrök elvitték mindenemet, ez nagyon jól fog jönni.";
			// belamour legendary edition -->
			link.l1.go = "Sharlie_5";		
			link.l2 = "Köszönöm, uram. Van még valami más módja, hogy segítsen nekem? Úriember az úriembernek? Magad is láthatod, milyen szörnyû helyzetben vagyok!";
			link.l2.go = "Sharlie_3";	
		break;
		
		case "Sharlie_3":
			dialog.text = "Nos, Charles... (az íróasztal között turkál) Tessék, tartsd meg ezt a szent amulettet a szerencsédért. Már nem tudok segíteni, sajnálom. Itt, a kolóniákon csak magadra kell támaszkodnod.";
			link.l1 = "Legalábbis valamire. Köszönöm az ajándékot, uram.";
			link.l1.go = "Sharlie_4";
		break;
		
		case "Sharlie_4":
			DialogExit();
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			AddCharacterExpToSkill(pchar, "Commerce", 10);
			Log_Info("Kaptál felszerelést");
			Log_Info("Megkaptad a 'szentelt víz' amulettet.");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "amulet_7");
			TakeNItems(pchar, "blade_08", 1);
			if(GetCharacterEquipByGroup(pchar, BLADE_ITEM_TYPE) == "")
			{
				EquipCharacterbyItem(pchar, "blade_08");
			}
			TakeNItems(pchar, "pistol1", 1);
			TakeNItems(pchar, "cirass5", 1);
			pchar.quest.Sharlie_PardonOver.over = "yes";
			DeleteAttribute(pchar, "questTemp.Sharlie.Pardon");
			if(!CheckAttribute(pchar, "questTemp.Sharlie.Junglejew"))
			{
				DelLandQuestMark(npchar);
			}
			if(CheckAttribute(pchar,"systeminfo.tutorial.Amulet"))
			{
				DoQuestFunctionDelay("Tutorial_Amulet", 0.1);
			}
		break;
		
		case "Sharlie_5":
			// <-- legendary edition
			DialogExit();
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			AddCharacterExpToSkill(pchar, "Leadership", 10);
			Log_Info("Kaptál felszerelést");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "blade_08", 1);
			if(GetCharacterEquipByGroup(pchar, BLADE_ITEM_TYPE) == "")
			{
				EquipCharacterbyItem(pchar, "blade_08");
			}
			TakeNItems(pchar, "pistol1", 1);
			TakeNItems(pchar, "cirass5", 1);
			pchar.quest.Sharlie_PardonOver.over = "yes";
			DeleteAttribute(pchar, "questTemp.Sharlie.Pardon");
			if(!CheckAttribute(pchar, "questTemp.Sharlie.Junglejew"))
			{
				DelLandQuestMark(npchar);
			}
		break;
		//<-- Бремя гасконца
		
		//Sinistra --> Травля крысы		
		case "TK_TravlyaKrys":
			dialog.text = "A sors fintora, Charles... Nem gyakran látunk valakit ilyen gyorsan felemelkedni a mi világunkban. Van egy olyan érzésem, hogy mi ketten jól kijövünk majd egymással.";
			link.l1 = "Megtiszteltetés lenne. Talán van egy feladata számomra?";
			link.l1.go = "TK_TravlyaKrys_2";
			DeleteAttribute(pchar, "questTemp.TK_TravlyaKrys");
			PChar.quest.TK_Timer.over = "yes";
		break;
		
		case "TK_TravlyaKrys_2":
			dialog.text = "Hát persze! Különösen azután, hogy sikeresen összecsaptál Barbazon egyik kalózával Le Francois közelében...";
			link.l1 = "Nem mondhatnám, hogy kellemes emlékeim vannak arról a találkozásról. Ki is az a Barbazon?";
			link.l1.go = "TK_TravlyaKrys_3";
		break;
		
		case "TK_TravlyaKrys_3":
			dialog.text = "Jacques Barbazon, más néven Jacques a Jóember, a Le Françcois-i bandita fészek vezetôje. Ô az egyik úgynevezett kalózbáró, aki kalózkodással és csempészettel okoz gondot a Kis-Antillákon. Hírhedt bûnözô, és jegyezd meg, hogy egy napon a St. Pierre-i akasztófán végzi majd a sorsát!";
			link.l1 = "Elnézést, de nem ön az igazi hatóság Martinique-on? Nem tudná egyszerûen eltüntetni azt a fészket? Én már jártam ott, és higgye el, nem sok látnivaló van ott.";
			link.l1.go = "TK_TravlyaKrys_4";
		break;
		
		case "TK_TravlyaKrys_4":
			dialog.text = "Azt tanácsolnám, hogy ne dicsekedj a szigetem kevésbé pikáns helyeinek ismeretével, Charles. Ez nem illik egy nemeshez. Ami a kérdésedet illeti\nNem mindent lehet megoldani a világunkban nyers erôvel. Politikai és üzleti érdekek játszanak közre. De ne menjünk bele felesleges részletekbe: Van egy konkrét feladatom, amihez nyers erôre van szükség.";
			link.l1 = "Kérem, folytassa.";
			link.l1.go = "TK_TravlyaKrys_5";
		break;
		
		case "TK_TravlyaKrys_5":
			dialog.text = "Barbazon vonzza a kisstílû bandákat, akik könnyû aranyra éhesek. Néha odadob egy csontot az egyiküknek, csak hogy lássa, ahogy mindannyian harcolnak érte. Alkalmanként munkára fogadja a túlélôt, de leggyakrabban kidobja ôket, és higgyétek el, nincs veszélyesebb, mint egy kétségbeesett kalóz, aki itt kóborol.";
			link.l1 = "Azt hiszem, megértem, de nem biztos, hogy készen állok rá. Csak nemrég vettem át a hajóm parancsnokságát, és még mindig tanulom a dolgokat, hogy úgy mondjam...";
			link.l1.go = "TK_TravlyaKrys_6";
		break;
		
		case "TK_TravlyaKrys_6":
			dialog.text = "Badarság! Már megízlelte a gyôzelem ízét - jobban, mint a legtöbb lógós a tisztjeim közül! A város ötezer pezóval jutalmazza, ha elsüllyeszti Barbazon újabb patkányát, adómentesen. Nyolcezret, ha élve hozod be a kalózt - természetesen a megfelelô kivégzésért.";
			link.l1 = "Nekem bizonyára jól jönne a pénz. Hol találom ezt a kalózt?";
			link.l1.go = "TK_TravlyaKrys_7";
			link.l2 = "Sajnálom, de nem hiszem, hogy még készen állok egy ilyen feladatra.";
			link.l2.go = "TK_TravlyaKrys_Otkaz";
		break;
		
		case "TK_TravlyaKrys_Otkaz":
			dialog.text = "Ez szégyen, Charles. Ebben az esetben nem tartalak fel tovább.";
			link.l1 = "Viszlát, excellenciás uram.";
			link.l1.go = "exit";
		break;
		
		case "TK_TravlyaKrys_7":
			dialog.text = "Örülök, hogy a fedélzeten vagy, Charles. A hírszerzési jelentéseink szerint a Hater, egy lugger, most készül elindulni Le Francoisból. Nem engedhetjük meg magunknak a késlekedést, úgyhogy vitorlát bontunk és támadásba lendülünk. Ne aggódj, barátom, sikerrel jársz.";
			link.l1 = "Isten kegyelmével, excellenciád.";
			link.l1.go = "TK_TravlyaKrys_8";			
		break;
		
		case "TK_TravlyaKrys_8":
			DialogExit();
			SetQuestHeader("TravlyaKrys");
			AddQuestRecord("TravlyaKrys", "1");
			
			sld = GetCharacter(NPC_GenerateCharacter("TK_Heiter", "mercen_8", "man", "man", sti(PChar.rank), PIRATE, -1, true, "pirate"));
			sld.name = "Daniel";
			sld.lastname = "Montbars";
			FantomMakeSmallSailor(sld, SHIP_LUGGER, "Hater", CANNON_TYPE_CANNON_LBS3, 20, 40, 20, 25, 35);
			SetCharacterGoods(sld, GOOD_GOLD, 1);
			sld.AlwaysEnemy = true;
			sld.AlwaysSandbankManeuver = true;
			sld.DontRansackCaptain = true;
			
			Group_FindOrCreateGroup("HeiterAttack");
			Group_SetType("HeiterAttack", "pirate");
			Group_AddCharacter("HeiterAttack", "TK_Heiter");

			Group_SetGroupCommander("HeiterAttack", "TK_Heiter");
			Group_SetTaskAttack("HeiterAttack", PLAYER_GROUP);
			Group_SetAddress("HeiterAttack", "Martinique", "Quest_Ships", "Quest_Ship_6");
			Group_LockTask("HeiterAttack");
			
			PChar.quest.TK_Potopil.win_condition.l1 = "Character_sink";
			PChar.quest.TK_Potopil.win_condition.l1.character = "TK_Heiter";
			PChar.quest.TK_Potopil.win_condition = "TK_Potopil";
		break;
		//<-- Травля крысы
		
		//Jason --> Португалец
		case "Portugal":
			dialog.text = "Persze, hogy sikerül, kapitány! Ezért zavartalak.";
			link.l1 = "Akkor csupa fül vagyok.";
			link.l1.go = "Portugal_1";
		break;
		
		case "Portugal_1":
			dialog.text = "A helyi halászok tegnap este egy furcsa hajót láttak a sziget közelében. Mint mondták, egy hatalmas hadihajó volt, olyan, mint egy csatahajó, zászlók és jelzôlámpák nélkül. Nem hiszem, hogy ez a hajó valóban nagyobb lehet egy fregattnál, de még az is túlzás lenne már!";
			link.l1 = "A félelem a vakondtúrást hegyekké változtatja, az biztos... de mi értelme?";
			link.l1.go = "Portugal_2";
		break;
		
		case "Portugal_2":
			dialog.text = "Én csak önhöz fordulok, kapitány. A kereskedelmi partnereimet megijesztik ezek a pletykák - azt hiszik, hogy kalózok vagy spanyol magánhajósok, és ez rosszat tesz a kereskedelemnek. Ami a legrosszabb - jelenleg nincsenek hadihajók a kolónián, csak néhány sloop a védelemre és egy öreg, csempészvadászatra alkalmas schooner\nnem hagyhatom ôrizetlenül... Mindenesetre most, hogy a titokzatos hajóról szóló pletykát már a fél város ismeri! Kérem, csatlakozzon a hajójával, hogy segítsen nekünk megtalálni - ismerem magát tisztességes kapitánynak, és még ha tényleg csak egy fregatt is, a maga ágyúi meggyôzhetik, hogy máshol keressen zsákmányt!";
			link.l1 = "Monsieur... Valójában, más terveim voltak...";
			link.l1.go = "Portugal_3";
		break;
		
		case "Portugal_3":
			dialog.text = "Kérem, kapitány! Csak néhány napra, amíg ezek a nyugtalan pletykák lecsillapodnak! És természetesen fizetünk az idejéért. 10.000 darab pesó megfelel?";
			link.l1 = "Hmm... de, excellenciás uram, én...";
			link.l1.go = "Portugal_4";
		break;
		
		case "Portugal_4":
			dialog.text = "És megduplázzuk, ha valóban harcba száll ezzel a hajóval, és megháromszorozzuk, ha elsüllyeszti! Nos, mit szól hozzá?";
			link.l1 = "Rendben, úgyis azt terveztem, hogy itt maradok pár napot.";
			link.l1.go = "Portugal_5";
		break;
		
		case "Portugal_5":
			dialog.text = "Kitûnô, sosem kételkedtem önben, kapitány úr! Ne feledje - csak két nap a mi vizeinken - és a pénz az öné. És ha kénytelen lesz csatába vonulni, akkor az eredménynek megfelelôen fizetjük ki.";
			link.l1 = "Értettem, excellenciás uram. Megegyeztünk, és most visszatérek a hajómra.";
			link.l1.go = "Portugal_6";
		break;
		
		case "Portugal_6":
			dialog.text = "Várni fogom a visszatérését, kapitány!";
			link.l1 = "Engedje meg, hogy elbúcsúzzak.";
			link.l1.go = "Portugal_7";
		break;
		
		case "Portugal_7":
			DialogExit();
			AddQuestRecord("Portugal", "10");
			NextDiag.CurrentNode = "Portugal_8";
			LocatorReloadEnterDisable("Fortfrance_town", "reload1_back", false);
			LocatorReloadEnterDisable("Fortfrance_town", "reload2_back", false);
			LocatorReloadEnterDisable("Fortfrance_town", "gate_back", false);//открыть выходы из города
			bDisableFastReload = true;//закрыть быстрый переход
			pchar.GenQuest.CannotWait = true;//запрет ожидания
			pchar.quest.Portugal_Seapatrol.win_condition.l1 = "location";
			pchar.quest.Portugal_Seapatrol.win_condition.l1.location = "Martinique";
			pchar.quest.Portugal_Seapatrol.function = "PortugalSeapatrolGo";
			pchar.quest.Portugal_SeapatrolAvendel.win_condition.l1 = "location";
			pchar.quest.Portugal_SeapatrolAvendel.win_condition.l1.location = "Fortfrance_town";
			pchar.quest.Portugal_SeapatrolAvendel.function = "AvendelSpeach";
		break;
		
		case "Portugal_8":
			dialog.text = "Kapitány, azt hiszem, megegyeztünk, hogy két napig járôrözik a part menti vizeinken!";
			link.l1 = "Igen, természetesen. Emlékszem rá.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Portugal_8";
		break;
		
		case "Portugal_9":
			dialog.text = "Nos, az alku részét teljesítette. Itt a jutalma - 10.000 pezó, ahogy megegyeztünk.";
			link.l1 = "Köszönöm! Amint látja, az aggodalmai alaptalanok voltak. Sok szerencsét!";
			link.l1.go = "Portugal_10";
		break;
		
		case "Portugal_10":
			DialogExit();
			AddMoneyToCharacter(pchar, 10000);
			NextDiag.CurrentNode = "First time";
			pchar.quest.MartiniqueGovernorOver.over = "yes"; //снять таймер
		break;
		//<-- Португалец
		
		// Warship, 16.05.11. Генер "Правосудие на продажу".
		case "JusticeOnSale_1":
			dialog.text = "Oh " + GetAddress_Form(NPChar) + ", megleptél! Tényleg ilyen szemtelenek lettek ezek a gazemberek? Azonnal értesítenem kell a parancsnokot és egy parti ôrjáratot kell oda küldenem!";
			link.l1 = "Örömmel segítettem. Most már elmehetek?";
			link.l1.go = "JusticeOnSale_2";
			
			DeleteAttribute(PChar, "GenQuest.JusticeOnSale.MayorWait");
			DeleteAttribute(PChar, "GenQuest.JusticeOnSale.PrisonWait");
			
			DeleteQuestCondition("JusticeOnSale_MapEnter");
		break;
		
		case "JusticeOnSale_2":
			dialog.text = "Természetesen, kapitány. Tessék - kérem, fogadja el személyesen tôlem ezt a szerény jutalmat.";
			link.l1 = "Köszönöm.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("JusticeOnSale_DlgExitAfterMayor_1");
		break;
		
		case "JusticeOnSale_4":
			dialog.text = "Igaza van, kapitány! Nem hagyhatjuk így! Arra kérlek, hogy menjetek a " + XI_ConvertString(PChar.GenQuest.JusticeOnSale.ShoreId + "Dat") + ", találjátok meg a hajójukat és tartóztassátok le az egész bandát! Ha ellenállnak - alkalmazzanak erôt és ne habozzanak!";
			link.l1 = "Engedje meg, hogy elbúcsúzzak.";
			link.l1.go = "JusticeOnSale_5";
		break;
		
		case "JusticeOnSale_5":
			dialog.text = "Most menjetek. Hajózzatok oda, és gondoskodjatok róla, hogy senki se meneküljön meg az igazságszolgáltatás elôl. Úgy gondolom, hogy elôször ki kell szállnod a partra, és utána gondoskodhatsz a hajóról.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("JusticeOnSale_DlgExitAfterMayor_2");
		break;
		
		case "JusticeOnSale_7":
			dialog.text = "Köszönöm a segítséget. Azok a gazemberek megkapták a magukét. Kérem, engedjék meg, hogy személyesen adjam át ezt a szerény jutalmat a részemrôl. Nagyra értékelem a rendet és a békét a városomban.";
			link.l1 = "...";
			link.l1.go = "JusticeOnSale_8";
		break;
		
		case "JusticeOnSale_8":
			AddMoneyToCharacter(PChar, sti(PChar.rank) * 300 + hrand(1000));
			DeleteAttribute(PChar, "GenQuest.JusticeOnSale");
			DialogExit();
		break;
		//<-- Правосудие на продажу
		
			//--> Jason регата
		case "Regata":
			// belamour legendary edition -->
			if(sti(pchar.rank) < 20)
			{
				notification("20. szint szükséges", "None");
				dialog.text = "Ah, csodálatos, örülök, hogy látom, kapitány! Hallottam a tehetségedrôl, de gyere, ha tényleg készen állsz.";
				link.l1 = "Igen, persze. Ahogy óhajtja.";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Ó, remek, örülök, hogy látom, kapitány! Épp idôben érkeztél - a regatta néhány nap múlva kezdôdik. Átolvasta már a regatta szabályait, amelyeket bizonyára egy rendtag adott át önnek?";
				link.l1 = "Igen, uram, olvastam.";
				link.l1.go = "Regata_1";
				RemoveItems(PChar, "letter_open", 1);//уберем письмо
				DeleteAttribute(pchar, "questTemp.Regata.ToPortRoyal"); // patch-5
			}
		break;
		
		case "Regata_1":
			dialog.text = "És felkészültél 50000 pezóra - a belépôdíjra, amely hozzájárul a díjalaphoz?";
			if (makeint(Pchar.money) >= 50000)
			{
				link.l1 = "Igen, természetesen. Kérem, fogadja el a díjamat.";
				link.l1.go = "Regata_2";
			}
			link.l2 = "Jelenleg egy kicsit szûkében vagyok a pénznek. De a szükséges összeget mindenképpen elô fogom teremteni.";
			link.l2.go = "Regata_nomoney";
		break;
		
		case "Regata_2":
			dialog.text = "Nagyon jó. Ha nyersz - ötszörösen visszakapod a pénzed. Most jobban meg kell ismerkedned a regatta szabályaival\nMinden részletet megtudhatsz Sir Henry Stivensontól, neki a rezidencia egyik szobájában kell lennie. Menjetek oda hozzá - ô majd mindent elmagyaráz.";
			link.l1 = "Rendben. Pontosan ezt fogom tenni.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -50000);
			pchar.quest.Regata_Guber.win_condition.l1 = "location";
			pchar.quest.Regata_Guber.win_condition.l1.location = "Portroyal_Roomtownhall";
			pchar.quest.Regata_Guber.function = "PrepareToRegataInPortroyal";
			pchar.questTemp.Regata.Begin = "true";
			NextDiag.TempNode = "First time";
		break;
		
		case "Regata_nomoney":
			dialog.text = "Rendben, de kérem, ne tartson túl sokáig, kapitány. A regatta hamarosan kezdôdik.";
			link.l1 = "Értem, értem. Megpróbálom elhozni a pénzt, amilyen hamar csak tudom.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Regata_1";
			pchar.questTemp.Regata.nomoney = "true";
		break;
		
		//регата-финал
		case "Regata_Final":
			dialog.text = "Aha! És itt van a regatta gyôztese! Jó napot Kapitány " + GetFullName(pchar) + "! Engedje meg, hogy gratuláljak ehhez a megérdemelt sikerhez! A regatta gyôztesei mindig is népszerûek voltak az angol gyarmatokon - és nem véletlenül.";
			link.l1 = "Köszönöm, uram!";
			link.l1.go = "Regata_complete";
		break;
		
		case "Regata_complete":
			dialog.text = "Most ugorjunk a legkellemesebbre - a jutalmazási ceremóniára. Az elsô helyezett díja 250 000 pezó. Gratulálunk!";
			link.l1 = "Köszönjük!";
			link.l1.go = "Regata_complete_1";
		break;
		
		case "Regata_complete_1":
			AddMoneyToCharacter(pchar, 250000);
			// belamour legendary edition в регате только один приз -->
			GiveItem2Character(pchar, "blade_26");
			GiveItem2Character(pchar, "cirass4");
			GiveItem2Character(pchar, "bussol");
			
			dialog.text = "Emellett értékes nyereményeket is kapsz: a legendás toledói acélrapír 'Asoleda', egy milánói páncélkészletet és egy finom iránytût. Mind a tiéd.";
			// <-- legendary edition
			link.l1 = "Nagyon örülök, uram. Tényleg nem számítottam ilyen nagylelkûségre.";
			link.l1.go = "Regata_complete_2";
		break;
		
		case "Regata_complete_2":
			dialog.text = "Az angol gyarmatok összes alattvalója nevében köszönöm, hogy részt vettél a regattán, és még egyszer gratulálok a gyôzelmedhez! Ha fogadást kötöttél, menj Sir Henry Stevensonhoz, és vedd át a nyereményedet, ha még nem tetted meg. Sok szerencsét, kapitány!";
			link.l1 = "Köszönöm a kedves szavakat, uram! Viszont engedje meg, hogy én is megköszönjem, hogy lehetôséget biztosított nekem, hogy részt vehessek egy ilyen nagyszerû eseményen. Most pedig engedjék meg, hogy távozzak.";
			link.l1.go = "Regata_complete_3";
		break;
		
		case "Regata_complete_3":
			DialogExit();
			NextDiag.CurrentNode = "First time";
		break;
		//<-- регата
	}
}

string GetGangLocation(ref npchar)
{
    int n;
	string island = GetArealByCityName(npchar.city);
	string LocationId, sAreal;
	int storeArray[2];
	SetArraySize(&storeArray, MAX_LOCATIONS);  
    int howStore = 0;

	for(n=0; n<MAX_LOCATIONS; n++)
	{				
		if (GiveArealByLocation(&locations[n]) == island)
		{			
			//==> на всякий случай
			if (CheckAttribute(&locations[n], "DisableEncounters") && locations[n].DisableEncounters == true) continue;
			LocationId = locations[n].id;
			if (findsubstr(LocationId, "jungle" , 0) != -1 || findsubstr(LocationId, "Shore" , 0) != -1 || findsubstr(LocationId, "CaveEntrance" , 0) != -1)
			{
				storeArray[howStore] = n;
				howStore++;
			}
		}
	}
	if (howStore == 0) return "none";
	n = storeArray[hrand(howStore-1)];
	return locations[n].id;
}

string GetSpyLocation(ref npchar)
{
    aref	arCommon, arRld, arRld2;
    int	i, n, Qty, Qty2;
	string LocId; 
	string	storeArray [50];
	int howStore = 0;
    makearef(arRld, Locations[FindLocation(npchar.city + "_town")].reload);
	Qty = GetAttributesNum(arRld);
    if (CheckAttribute(pchar, "questTemp.jailCanMove.Deliver.locationId")) //если взят квест по доставке малявы
	{
		for (i=0; i<Qty; i++)
		{
    		arCommon = GetAttributeN(arRld, i);
			LocId = arCommon.go;
    		if (findsubstr(LocId, "Common" , 0) != -1 && LocId != pchar.questTemp.jailCanMove.Deliver.locationId)
    		{			
				storeArray[howStore] = LocId;
				howStore++; 
			}
			if (arCommon.label != "Sea")
			{	
				makearef(arRld2, Locations[FindLocation(LocId)].reload);
				Qty2 = GetAttributesNum(arRld2);
				for (n=0; n<Qty2; n++)
				{
    				arCommon = GetAttributeN(arRld2, n);
					LocId = arCommon.go;
					if (findsubstr(LocId, "Common" , 0) != -1 && LocId != pchar.questTemp.jailCanMove.Deliver.locationId && LocId != "CommonPackhouse_1" && LocId != "CommonPackhouse_2")
    				{
						storeArray[howStore] = LocId;
						howStore++; 					
					}
				}
			}	
		}
	}
	else
	{
		for (i=0; i<Qty; i++)
		{
    		arCommon = GetAttributeN(arRld, i);
			LocId = arCommon.go;
    		if (findsubstr(LocId, "Common" , 0) != -1)
    		{			
				storeArray[howStore] = LocId;
				howStore++; 
			}
			if (arCommon.label != "Sea")
			{	
				makearef(arRld2, Locations[FindLocation(LocId)].reload);
				Qty2 = GetAttributesNum(arRld2);
				for (n=0; n<Qty2; n++)
				{
    				arCommon = GetAttributeN(arRld2, n);
					LocId = arCommon.go;
					if (findsubstr(LocId, "Common" , 0) != -1 && LocId != "CommonPackhouse_1" && LocId != "CommonPackhouse_2")
    				{
						storeArray[howStore] = LocId;
						howStore++; 					
					}
				}
			}	
		}
	}
	if (howStore == 0) return "none";
	LocId = storeArray[hrand(howStore-1)];
	SetOpenDoorCommonLoc(npchar.city, LocId); //открываем дверь
	for(n=0; n<MAX_CHARACTERS; n++)
	{
		if (CheckAttribute(&characters[n], "locations") && characters[n].locations == LocId) 
		{			
			characters[n].lifeDay = 0;
		}
	}
	return LocId;
}

string GetSpyColony(ref NPChar)
{
    int storeArray[2];
	SetArraySize(&storeArray, MAX_COLONIES);
    int howStore = 0;
	string sChrId;

	for(int n=0; n<MAX_COLONIES; n++)
	{
		// Rebbebion, чуть изменил функцию, чтобы условно испанцы не просили пробраться к испанцам, французы к французам и т.д
		if (colonies[n].nation != "none" && sti(colonies[n].nation) != PIRATE && GetRelation2BaseNation(sti(colonies[n].nation)) == RELATION_ENEMY && colonies[n].id != "Panama" && colonies[n].id != "LosTeques" && colonies[n].id != "SanAndres" && colonies[n].id != npchar.City && colonies[n].nation != npchar.nation)
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	if (howStore == 0) return "none";
	return colonies[storeArray[Rand(howStore-1)]].id;
}

int SelectCureerShipType()
{
	int iClass = 6;
	int iRank = sti(pchar.rank);
	
	if(iRank < 6) iClass = 6;
	if(iRank >= 6 && iRank < 12) iClass = 6 - rand(1);
	if(iRank >= 12 && iRank < 21) iClass = 5 - rand(1);
	if(iRank >= 21) iClass = 4 - rand(1);
	
	return GetRandomShipType(GetClassFlag(iClass), FLAG_SHIP_TYPE_RAIDER + FLAG_SHIP_TYPE_UNIVERSAL, FLAG_SHIP_NATION_ANY);
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
	
	return GetRandomShipType(GetClassFlag(iClass), FLAG_SHIP_TYPE_RAIDER + FLAG_SHIP_TYPE_UNIVERSAL + FLAG_SHIP_TYPE_WAR, FLAG_SHIP_NATION_ANY);
}

int SelectCustomPatrolShipType(int iFlagType)
{
	if(CheckAttribute(pchar, "questTemp.StatusCity"))
	{
		return SHIP_CAREERLUGGER;
	}
	
	int iClass = 6;
	int iRank = sti(pchar.rank);
	
	if(iRank < 6) iClass = 6;
	if(iRank >= 6 && iRank < 12) iClass = 6 - rand(1);
	if(iRank >= 12 && iRank < 21) iClass = 5 - rand(1);
	if(iRank >= 21) iClass = 4 - rand(1);
	
	return GetRandomShipType(GetClassFlag(iClass), iFlagType, FLAG_SHIP_NATION_ANY);
}

int SelectArsenalShipType(int iFlagType)
{
	int iClass = 6;
	int iRank = sti(pchar.rank);
	
	if(iRank < 6) iClass = 6;
	if(iRank >= 6 && iRank < 12) iClass = 6 - rand(1);
	if(iRank >= 12 && iRank < 21) iClass = 5 - rand(1);
	if(iRank >= 21 && iRank < 30) iClass = 4 - rand(1);
	if(iRank >= 30) iClass = 2;
	
	return GetRandomShipType(GetClassFlag(iClass), iFlagType, FLAG_SHIP_NATION_ANY);
}

string SelectPassText()
{
	string sText;
	switch (hrand(5))
	{
		case 0: sText = "Az a Júdás, kihasználva a pozícióját, eladott egy fontos államtitkot egy ellenséges hatalomnak."; break;
		case 1: sText = "Az a hitvány gazember megölte a rokonát, egy közismert és nemes embert, hogy örökölje a vagyonát."; break;
		case 2: sText = "Az a gazember megsértette a családomat és engem személyesen."; break;
		case 3: sText = "Ez a tolvaj gazember tisztességes összeget lopott el a városunk kincstárából."; break;
		case 4: sText = "Ez a gazember közel egy tucat polgárunk haláláért felelôs."; break;
		case 5: sText = "Ez a gazember a kapcsolatait felhasználva megszerezte egy kereskedelmi hajót, majd ellopta és eladta a szomszédos hajógyárban."; break;
	}
	return sText;
}

string SelectFugitiveCity()
{
	string sCity;
	switch (rand(3))
	{
		case 0: sCity = "LaVega"; break;
		case 1: sCity = "PuertoPrincipe"; break;
		case 2: sCity = "LeFransua"; break;
		case 3: sCity = "FortOrange"; break;
	}
	return sCity;
}

string SelectFugitiveText()
{
	string sText;
	switch (hrand(5))
	{
		case 0: sText = "a helyôrségünk egyik altisztje dezertált, és egy kereskedelmi hajó fedélzetén elhagyta a kolóniát."; break;
		case 1: sText = "egyik tisztünk egyenesen szolgálat közben dezertált, és egy csempészhajó fedélzetén megszökött."; break;
		case 2: sText = "egy járôrbriggen szolgáló tengerésztisztünk ismeretlen okból dezertált, eltérített egy hosszú hajót és eltûnt rajta."; break;
		case 3: sText = "egyik börtönôrünk ismeretlen okból felmondta a szolgálatot, és egy magánhajó fedélzetén elhagyta kolóniánkat."; break;
		case 4: sText = "a helyôrségünk egyik katonája elhagyta ôrségben lévô ôrhelyét, elment az öbölbe, és egy ismeretlen hajó fedélzetén elhagyta ezt a helyet."; break;
		case 5: sText = "egyik katonatisztünk, egy járôrözô lugger kapitánya elhagyta hajóját a nyílt tengeren, és egy halászhajó hosszúhajóján délre ment."; break;
	}
	return sText;
}
