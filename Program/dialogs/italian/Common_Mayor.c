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
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase("Hai osato mostrare il tuo volto nella mia casa?! Molto coraggioso da parte tua, o stupido...","Come hanno fatto le mie guardie idiote a lasciare che un nemico entrasse nel mio palazzo? Qualcuno pagherà con la testa per questo.","Sembra che le mie guardie non valgano un soldo bucato, se qualche mascalzone si aggira nella mia residenza e fruga tra le mie cose..."),LinkRandPhrase("Di che cosa avete bisogno, "+GetSexPhrase("birbante","diavolo")+"?! I miei soldati sono già sulle tue tracce"+GetSexPhrase(", sporco pirata","")+"!",+"Assassino, lascia subito la mia residenza! Guardie!","Non ho paura di te, "+GetSexPhrase("furbo","ratto")+"! Presto sarai impiccato nel nostro forte!"));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("I tuoi soldati non valgono nulla.","Cerca di prendermi."),RandPhraseSimple("Chiudi la bocca, "+GetWorkTypeOfMan(npchar,"")+", o lo chiuderò io per te!","Taci compagno e resterai vivo."));
				link.l1.go = "fight";
				break;
			} 
			if (sti(NPChar.nation) == PIRATE)
            {
				if (CheckAttribute(pchar, "GenQuest.CaptainComission") && CheckAttribute(pchar, "GenQuest.CaptainComission.PiratesCity") && NPChar.city == pchar.GenQuest.CaptainComission.PiratesCity)
				{
					dialog.text = "Di cosa hai bisogno?";
					link.l1 = "Volevo parlare con te di un lavoro importante.";
					link.l1.go = "quests";
					break;
				}
				if (CheckAttribute(pchar, "GenQuest.Marginpassenger") && pchar.GenQuest.Marginpassenger == "cabin" && NPChar.city == "LeFransua")
				{
					dialog.text = "Di cosa hai bisogno?";
					link.l1 = "Volevo parlare con te di un lavoro importante.";
					link.l1.go = "quests";
					break;
				}
					dialog.text = "Non c'è nulla di cui parlare, signore. Sono occupato.";
					link.l1 = "Le mie scuse.";
					link.l1.go = "Exit";
            }
			if (sti(NPChar.nation) != PIRATE && ChangeCharacterHunterScore(Pchar, NationShortName(sti(NPChar.nation)) + "hunter", 0) > 10)
            {
				iTotalTemp = ChangeCharacterHunterScore(Pchar, NationShortName(sti(NPChar.nation)) + "hunter", 0);
                dialog.text = "Oh, guarda chi c'è! È"+GetSexPhrase("","")+" "+GetFullName(pchar)+". Sai, ho appena mandato dei cacciatori di pirati per riportarti qui. Se avessi saputo che saresti entrato a ballare dalla mia porta, avrei risparmiato i miei soldi.";
                if (sti(pchar.Money) >= iTotalTemp*6000)
                {
                    link.l1 = "Stavo proprio per sistemare i nostri conti.";
				    link.l1.go = "arestFree_1";
                }
				link.l2 = "È ora per me di fare una rapida uscita.";
				link.l2.go = "arest_1";
				break;
            }
			if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
			{
    			dialog.text = "Un'intrusione! Guardie! Allarme! Assassinio!";
				link.l1 = "Merda!";
				link.l1.go = "fight"; 
				break;
			}
			//--> Jason, Бремя гасконца
			if (CheckAttribute(pchar, "questTemp.Sharlie.Citcount") && npchar.city == "FortFrance")
			{
    			dialog.text = "Cosa desidera, signore?";
				link.l1 = "Salve, Sua Grazia. Sono Charles de Maure, appena arrivato da Parigi. Sto cercando Michel de Monper.";
                link.l1.go = "Sharlie";
				npchar.quest.meeting = "1"; // patch-6
				DelLandQuestMark(characterFromId("FortFrance_Mayor"));
				break;
			}
			
			if (CheckAttribute(pchar, "questTemp.Sharlie.Lock") && npchar.city == "FortFrance")
			{
				if (CheckAttribute(pchar, "questTemp.Sharlie.Pardon"))
				{
					dialog.text = "Oh, sei tu, signore... Devo scusarmi per la mia maleducazione. Le mie scuse, qui nelle colonie siamo lontani dalle cortesie di Parigi.";
					link.l1 = "Certo, Vostra Grazia.";
					link.l1.go = "Sharlie_2";
				}
				else
				{
					dialog.text = "Volevi qualcosa, Charles?";
					link.l1 = "Ho una domanda...";
					link.l1.go = "quests";
					link.l2 = "No, niente.";
					link.l2.go = "exit";
				}
				if (CheckAttribute(pchar, "questTemp.Sharlie.Junglejew"))
				{
					link.l3 = "Signore, ho trovato un cadavere di bandito nella giungla. È stato ucciso dagli indiani. C'erano orecchini sul suo corpo, sembra che fossero portati qui dall'Europa. Forse appartenevano a uno dei nobili della vostra città?";
					link.l3.go = "Sharlie_junglejew";
				}
				npchar.quest.meeting = "1"; // patch-6
				break;
			}			
			//<-- Бремя гасконца
			//--> Sinistra, Травля крысы
			if (CheckAttribute(pchar, "questTemp.TK_TravlyaKrys") && npchar.city == "FortFrance")
			{
    			dialog.text = "Benvenuto ai Caraibi, Capitano de Maure. Questa volta, per davvero.";
				link.l1 = "Grazie, Vostra Eccellenza.";
                link.l1.go = "TK_TravlyaKrys";
				DelLandQuestMark(npchar);
				break;
			}
			// Jason НСО
			// belamour legendary edition фикс проверки мундира с мушкетом
			if (CheckAttribute(pchar, "questTemp.Patria.Governor") && npchar.city == "Marigo" && IsUniformEquip())
			{
    			dialog.text = "È un piacere vederti, Governatore! Come stai? Tutto è sotto controllo a Sint Maarten.";
				link.l1 = "Non ho tempo per restare. Continua il buon lavoro.";
				link.l1.go = "exit";
				link.l2 = "Volevo parlare di lavoro.";
				link.l2.go = "quests";   //(перессылка в файл города)
				link.l8 = "Che ne dici di una partita a sorte?";
				link.l8.go = "Play_Game";
				break;
			}
			// belamour legendary edition фикс проверки мундира с мушкетом
			if (CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE && IsUniformEquip())
			{
    			dialog.text = "Mio Dio, lieto di vedervi, Governatore Generale! Tutto è fantastico qui nella nostra umile piccola colonia! Prego, prendete posto, ordinerò ai servi di apparecchiare la tavola...";
				link.l1 = "Non c'è bisogno. Non sono venuto per molto tempo. Continua il buon lavoro.";
				link.l1.go = "exit"; 
				link.l2 = "Volevo parlare di lavoro.";
				link.l2.go = "quests";   //(перессылка в файл города)
				link.l8 = "Che ne dici di un gioco di fortuna?";
				link.l8.go = "Play_Game";
				break;
			}
			// belamour legendary edition фикс проверки мундира с мушкетом
			if (CheckAttribute(pchar, "questTemp.Patria.GenGovernor") &&  IsUniformEquip())
			{
    			dialog.text = "Chi abbiamo qui! Monsieur Governatore Generale delle Colonie Francesi! Cosa desidera, Vostra Grazia? Siediti, ordinerò ai miei servi di portare vino e frutta fresca.";
				link.l1 = "Non preoccuparti, sono venuto qui solo perché stavo visitando l'isola, e non potevo semplicemente passare senza dire ciao.";
				link.l1.go = "exit"; 
				link.l2 = "Volevo parlare del lavoro.";
				link.l2.go = "quests";   //(перессылка в файл города)
				link.l8 = "Che ne dici di un gioco d'azzardo?";
				link.l8.go = "Play_Game";
				break;
			}		
			//--> Jason, Португалец
			if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "MartiniqueGovernor" && npchar.city == "FortFrance")
			{
    			dialog.text = "Oh, eccoti qui, capitano! Devo dire, hai preso il tuo tempo.";
				link.l1 = "Sono arrivato alla prima opportunità, Vostra Eccellenza. Mi è stato detto che avete affari urgenti?";
				link.l1.go = "Portugal"; 
				break;
			}			
			//<-- Португалец
            
            if (npchar.quest.meeting == "0")
			{
				dialog.text = "I miei uomini mi hanno detto che insistevi molto per ottenere un'udienza. Il mio nome è "+GetFullName(npchar)+". Sono il governatore della città di "+GetCityName(NPChar.city)+", soggetto di "+NationKingsName(npchar)+". E ora, per favore, cosa desideri "+GetAddress_Form(NPChar)+"?";
				link.l1 = "Il mio nome è "+GetFullName(pchar)+".";
				link.l1.go = "node_1";
				npchar.quest.meeting = "1";
				if(startHeroType == 4 && NPChar.location == "SantaCatalina_townhall")
				{
					dialog.text = TimeGreeting()+", Signorina MacArthur.";
					link.l1 = TimeGreeting()+", Vostra Eccellenza.";
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
                        dialog.text = "È tutto?";
                        link.l1 = "Sì signore. Non vi ritardo ulteriormente.";
                        link.l1.go = "exit";

                    }
                    else
                    {
                        dialog.text = "Mi dispiace contrariarti, ma non ho tempo per parlare con te al momento. Come dovresti sapere, la nostra colonia è stata attaccata da "+NationNamePeople(sti(aData.nation))+". Sto ancora provvedendo alle nostre difese.";
                        link.l1 = "Voglio offrire il mio aiuto nella difesa del forte.";
                        link.l1.go = "siege_task";
                        link.l2 = "Allora non ti tratterrò ulteriormente.";
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
                        dialog.text = "Oh, sei tu, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+", Sono felice di vederti. Buone notizie per la nostra colonia - siamo riusciti a respingere il "+NationNameSK(sti(aData.nation))+" invasori. Anche tu hai un ruolo in questo, quindi ecco la tua ricompensa - "+(sti(aData.iSquadronPower)*1500)+" pezzi di otto. Ecco a te.";
                        link.l1 = "Grazie, "+GetAddress_FormToNPC(NPChar)+", piacere di fare affari con te!";
                        link.l1.go = "exit";
                    }
                    else
                    {
   						//--> дача квеста найти кольцо в борделе
						if (rand(4) == 4 && pchar.questTemp.different == "free" && GetNpcQuestPastDayWOInit(npchar, "questTakeRing") > 365 && sti(pchar.questTemp.HorseQty) > 10)
						{// Addon-2016 Jason
							if (npchar.city == "Bridgetown" || npchar.city == "Charles" || npchar.city == "FortFrance" || npchar.city == "Marigo" || npchar.city == "Panama" || npchar.city == "PortRoyal" || npchar.city == "SantoDomingo" || npchar.city == "Tortuga")
							{
        						dialog.text = "Ho un compito per te, ma è un po' insolito.";
								link.l1 = "Questi sono i compiti in cui sono più bravo.";
        						link.l1.go = "TakeRing_1";
								SaveCurrentNpcQuestDateParam(npchar, "questTakeRing");
								break;
							}
						}
						//<-- дача квеста найти кольцо в борделе    				
						dialog.text = RandPhraseSimple("Oh, sei tu di nuovo? Cosa vuoi da me questa volta?","Tu mi distrai dagli affari della mia città. Cosa vuoi, "+GetAddress_Form(NPChar)+"?");
						if (npchar.city != "Panama") // Addon-2016 Jason
						{
							link.l1 = "Voglio parlare con te del lavorare per "+NationNameGenitive(sti(NPChar.nation))+".";
							link.l1.go = "work";
						}
						// Warship Генер "Пираты на необитайке" - сдаём пиратов властям
						if(CheckAttribute(PChar, "Quest.PiratesOnUninhabited_OnShore") || CheckAttribute(PChar, "Quest.PiratesOnUninhabited_ShipSink"))
						{
							link.l11 = XI_ConvertString(PChar.GenQuest.PiratesOnUninhabited.StartShore+"Gen")+" Ho trovato dei pirati. Tutti "+PChar.GenQuest.PiratesOnUninhabited.PiratesCount+" sono a bordo al momento. Voglio consegnarli alle autorità.";
							link.l11.go = "PiratesOnUninhabited_1";
						}
						
        				link.l2 = "Stavo per parlarti di un argomento importante.";
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
								link.l12 = "C'è un capitano al comando della pattuglia "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")+"Acc"))+" nominato "+pchar.GenQuest.CaptainComission.Name+", come posso vederlo?";
								link.l12.go = "CapComission_Mayor1";
							}	
							if(CheckAttribute(pchar,"GenQuest.CaptainComission.PrisonFree"))
							{
								link.l12 = "Ex capitano al comando della pattuglia "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")+"Acc"))+" "+pchar.GenQuest.CaptainComission.Name+" ha accettato di rivelare il suo nascondiglio alle autorità.";
								link.l12.go = "CapComission_Mayor9";
							}
							if(pchar.GenQuest.CaptainComission == "GetGoodsSuccess")
							{
								link.l12 = "Ex capitano al comando della pattuglia "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")+"Acc"))+" "+pchar.GenQuest.CaptainComission.Name+" ha rivelato a me il suo nascondiglio.";
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
									link.l13 = UpperFirst(XI_ConvertString(pchar.GenQuest.ShipWreck.Shore+"Dat"))+" Ho incontrato il capitano "+pchar.GenQuest.ShipWreck.Name+" e i suoi marinai che furono messi a terra dai pirati "+pchar.GenQuest.ShipWreck.BadName+". "+"Sfortunatamente, avevo già troppi uomini sulla mia nave e non potevo prenderli a bordo. Ma li ho lasciati con provviste e armi. Se una nave di soccorso non li raccoglie entro "+(30 - iDay)+" giorni, poi non so se li troverò vivi o no.";
									link.l13.go = "ShipWreck1";
								}
								else
								{
									link.l13 = UpperFirst(XI_ConvertString(pchar.GenQuest.ShipWreck.Shore+"Gen"))+" Ho incontrato marinai dalla nave naufragata '"+pchar.GenQuest.ShipWreck.ShipTypeName+"' con il loro capitano. "+"Sfortunatamente, avevo già troppi uomini sulla mia nave e non potevo prenderli a bordo. Ma li ho lasciati con provviste e armi. Se una nave di soccorso non li raccoglie entro "+(30 - iDay)+" giorni, poi non so se li troverà vivi o no.";
									link.l13.go = "ShipWreck1";							
								}
							}	
						}
        				if (GetPrisonerQty() > 0)
        				{
                            link.l3 = "Desidero consegnare un prigioniero.";
        				    link.l3.go = "sell_prisoner";
        				}
        				if (npchar.Default  == npchar.location) // если не в тюрьме
        				{
        					if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
        					{
        						link.l4 = "Devo risolvere alcune questioni finanziarie con te.";
        						link.l4.go = "LoanForAll";//(перессылка в кредитный генератор)
        					}
        				}
						//-->> сдача найденного в борделе кольца
						if (CheckCharacterItem(pchar, "MayorsRing"))
						{
							if (pchar.questTemp.different.TakeMayorsRing == "toBrothel")
							{
        						link.l5 = "Sono riuscito a trovare il tuo anello. Eccolo qui.";
        						link.l5.go = "TakeRing_S1";
							}
							else
							{
        						link.l5 = "Ho il tuo anello nuziale. Una delle... ragazze che lavorano nel bordello lo aveva.";
        						link.l5.go = "TakeRing_S3";
							}
						}
						//<<-- сдача найденного в борделе кольца 
						
						//--> Jason, генер почтового курьера 2 уровня
						if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.LevelUp"))
						{
							if (pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
							{
							link.l14 = "Porto un messaggio dalla città di "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen")+".";
							link.l14.go = "Postcureer_LevelUp_ForAll";
							}
						}
						//<-- генер почтового курьера 2 уровня
						
						// Warship, 16.05.11. Квест "Правосудие на продажу" -->
						if(CheckAttribute(PChar, "GenQuest.JusticeOnSale.MayorWait") && CheckAttribute(PChar, "GenQuest.JusticeOnSale.CityId") && NPChar.location == PChar.GenQuest.JusticeOnSale.CityId + "_townhall")
						{
							link.l15 = UpperFirst(GetAddress_FormToNPC(NPChar))+", ho localizzato una banda di contrabbandieri il cui capo è stato recentemente catturato dalle guardie. Ora stanno tramando la sua fuga. La loro nave '"+PChar.GenQuest.JusticeOnSale.ShipName+"' è ormeggiato a "+XI_ConvertString(PChar.GenQuest.JusticeOnSale.ShoreId+"Dat")+".";
							link.l15.go = "JusticeOnSale_1";
						}
						
						if(CheckAttribute(PChar, "GenQuest.JusticeOnSale.ShipSink") && CheckAttribute(PChar, "GenQuest.JusticeOnSale.CityId") && NPChar.location == PChar.GenQuest.JusticeOnSale.CityId + "_townhall")
						{
							link.l15 = UpperFirst(GetAddress_FormToNPC(NPChar))+", la banda di contrabbandieri non esiste più!";
							link.l15.go = "JusticeOnSale_7";
						}
						// <--Правосудие на продажу
						//Jason --> Регата
						if (CheckAttribute(pchar, "questTemp.Regata.ToPortRoyal") && NPChar.location == "Portroyal_townhall")
						{
							link.l16 = "Sono qui per la regata. Ecco il mio invito.";
							link.l16.go = "Regata";
						}
        				//link.l7 = "Vorrei sapere dove si trova il Governatore Generale di "+NationNameGenitive(sti(NPChar.nation))+"è.";
        				link.l8 = "Forse, vuoi fare una pausa giocando a un gioco di fortuna?";
        			    link.l8.go = "Play_Game";
        				link.l10 = "Mi scusi, ma il dovere chiama.";
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
			
			dialog.text = "Molto bene. Dobbiamo combattere questa comune piaga con i nostri sforzi concertati. Immediatamente invierò una nave per prenderli. State tranquilli che saranno impiccati in meno di una settimana. Oh, e naturalmente, c'è una ricompensa dovuta - "+FindRussianMoneyString(qty)+".";
			link.l1 = "Grazie, Vostra Grazia. Sempre un piacere.";
			link.l1.go = "PiratesOnUninhabited_2";
			link.l2 = "No. A pensarci bene, non va bene.";
			link.l2.go = "exit";
		break;
		
		case "PiratesOnUninhabited_2":
			offref = CharacterFromID("PirateOnUninhabited_0");
			
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.PiratesOnUninhabited.MoneyForPirates));
			
			RemovePassenger(PChar, offref);
			RemoveCharacterCrew(PChar, sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) - 1);
			
			sTemp = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
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
			dialog.text = "Sono tutto orecchie, capitano.";
			link.l1 = "Volevo parlarvi di una certa collusione criminale tra un ufficiale della vostra guarnigione e dei pirati... (spiega la questione).";
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
				dialog.text = "Grazie, "+GetSexPhrase("signore","signorina")+"! Ordinerò immediatamente l'arresto di quel traditore.\nDevi aver speso un sacco di soldi, ahimè, la nostra tesoreria è vuota...";
				link.l1 = "Non l'ho fatto per i soldi, vostra Eccellenza.";
				link.l1.go = "ReasonToFast_GMayor_11";				
				if(pchar.questTemp.ReasonToFast.chain == "A0") ReasonToFast_RemoveVictim();
				if(pchar.questTemp.ReasonToFast.chain == "A1") pchar.quest.ReasonToFast_ClearLakey.over = "yes";
			}			
			if(pchar.questTemp.ReasonToFast == "PatrolSuccess_2") 
			{ 
				// получена карта
				dialog.text = "Ti ringrazio! Farò arrestare quel mascalzone.\nPensa solo! Stavo per premiarlo con una sciabola con impugnatura d'oro per i suoi dieci anni di servizio! Mi hai salvato da un imbarazzo serio!";
				link.l2 = "La giustizia è la sua stessa ricompensa.";
				link.l2.go = "ReasonToFast_GMayor_21";			
			}
			if(pchar.questTemp.ReasonToFast == "PatrolDied") 
			{ 
				// патруль перебит
				dialog.text = "Signorina"+GetSexPhrase("ter","s")+" de Maure, non puoi semplicemente uccidere un sospetto senza testimoni! Ora non possiamo nemmeno ottenere prove dei suoi crimini! Posso a malapena impedirti di essere arrestato per omicidio colposo.";
				link.l3 = "Arrestatevi, era in legittima difesa, Vostro Eccellenza.";
				link.l3.go = "ReasonToFast_GMayor_31";
				pchar.questTemp.ReasonToFast.speakAfterPatrolDied = true;	
				pchar.quest.ReasonToFast_SpeakMayor.over = "yes";
			}			
		break;
		
		case "ReasonToFast_BMayor":
			if(pchar.questTemp.ReasonToFast == "PatrolSuccess_1") 
			{ 				
				dialog.text = "Capitano, ti rendi conto di quello che cazzo hai fatto?!! Ho preparato questa trappola per più di un mese! E ora, solo per il tuo divertimento, hai rovinato l'incontro della nostra pattuglia con "+GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_GEN)+" e ora vieni qui a vantartene?!! Forse, puoi dirmi ora, come dovrei giustificare tutte le spese e i costi di questa operazione?!";
				link.l1 = "Vostra Grazia, ho appena risolto il vostro problema, se ci pensate avreste dovuto pagarmi tutto questo tempo!";
				link.l1.go = "ReasonToFast_BMayor_1";
				pchar.questTemp.ReasonToFast = "speakSuccess_chain_A";				
				if(pchar.questTemp.ReasonToFast.chain == "A0") ReasonToFast_RemoveVictim();
				if(pchar.questTemp.ReasonToFast.chain == "A1") pchar.quest.ReasonToFast_ClearLakey.over = "yes";
			}
			if(pchar.questTemp.ReasonToFast == "PatrolSuccess_2") 
			{ 
				// получена карта
				dialog.text = "Fammi vedere questa mappa\nStai scherzando adesso? Questo pezzo di carta logoro è una prova?";
				link.l2 = "Su, Sua Grazia, sia ragionevole.";
				link.l2.go = "ReasonToFast_BMayor_1";
				TakeItemFromCharacter(pchar, "mapQuest");				
				pchar.questTemp.ReasonToFast = "speakSuccess_chain_B";
			}
			if(pchar.questTemp.ReasonToFast == "PatrolDied") 
			{ 
				// патруль перебит
				dialog.text = "Beh beh, ora sappiamo cosa è successo alla mia pattuglia. Almeno venendo qui ci hai risparmiato la necessità di cercare l'assassino.";
				link.l3 = "Vostra Grazia! State solo rifiutando di vedere il punto...";
				link.l3.go = "ReasonToFast_BMayor_1";			
				pchar.questTemp.ReasonToFast = "speakSuccess_chain_A";
				pchar.quest.ReasonToFast_SpeakMayor.over = "yes";
			}		
		break;
		
		case "ReasonToFast_GMayor_11":
			dialog.text = "You may be an idiot but you are at least a useful idiot. Here - take this map; found it on a pirate who we hanged last week. God willing, perhaps you will find his treasure, although I find it quite unlikely...";
			link.l1 = "Grazie, è molto generoso da parte tua!";
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
			dialog.text = "La tua zelo è lodevole. Per favore accetta questa spada come ricompensa - è il minimo che posso fare. Oh, e puoi tenere la mappa per te. Sono certo che ci sono un sacco di tali falsi nei Caraibi.";
			link.l1 = "Grazie, è molto generoso da parte tua!";
			link.l1.go = "exit";
			AddQuestRecord("ReasonToFast", "14");
			ChangeCharacterComplexReputation(pchar,"nobility", 1); 
			GiveItem2Character(pchar, pchar.questTemp.ReasonToFast.p6);
			pchar.questTemp.ReasonToFast.state = "chain_B"; // была получена карта
			pchar.questTemp.ReasonToFast = "GetMap";			
			ReasonToFast_SetHunterCoastal();
		break;
		case "ReasonToFast_GMayor_31":
			dialog.text = "Forse, forse... Diciamo solo che questo affare è stato deciso dalla giustizia divina e dalla volontà del nostro Signore.";
			link.l1 = "Grazie, è molto generoso da parte tua!";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar,"nobility", 1); 
			AddQuestRecord("ReasonToFast", "16");
			CloseQuestHeader("ReasonToFast");
			DeleteAttribute(pchar,"ReasonToFast");
		break;
		
		case "ReasonToFast_BMayor_1":
			dialog.text = "Tieni a freno la lingua ragazzo! Sei o pazzo o in lega con i nostri nemici! Guardie, afferrate questo idiota!";
			link.l1 = "Metti una mano su di me e la perderai!";
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
			dialog.text = "Proprio ora è impossibile. È sotto arresto in attesa di processo.";
			link.l1 = "È lui? E di cosa è sospettato?";			
			link.l1.go = "CapComission_Mayor2";
		break;
		
		case "CapComission_Mayor2":
			dialog.text = "Sfortunatamente, non è sospetto, ma un fatto provato. Abbiamo informazioni che lui depredava le navi sotto la maschera di pattugliamento. Confiscava merci dai mercanti e poi le vendeva a contrabbandieri e pirati. È un peccato...pensare che una volta era considerato uno dei migliori capitani che la Corona avesse mai avuto...";
			link.l1 = "E chi ti ha fornito le prove?";
			link.l1.go = "CapComission_Mayor3";				
		break;
		
		case "CapComission_Mayor3":
			dialog.text = "Una delle sue vittime ha scritto un rapporto, dove ha descritto l'incidente in dettaglio, incluso la data, il nome della nave saccheggiata e la quantità di merci confiscate."+"Fidati di me, i numeri sono davvero impressionanti. In quel giorno di pattuglia "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")))+" capitano "+pchar.GenQuest.CaptainComission.Name+" era effettivamente in servizio. Il capitano ha descritto questo incidente come un incontro con una nave pirata nel suo rapporto, ma non ha menzionato affatto alcun carico.";
			link.l1 = "Ma c'era del tutto un carico?";
			link.l1.go = "CapComission_Mayor4";
			pchar.GenQuest.CaptainComission.SpeakMayor = true;
		break;
		
		case "CapComission_Mayor4":
			dialog.text = "Non c'è dubbio. La parte offesa è un uomo molto noto e non si abbasserebbe a diffamare e calunniare. Al momento le nostre pattuglie stanno cercando la cache del capitano. "+"Una volta trovato, il capitano può comparire in tribunale\nSe ci fornisci assistenza in questo caso, ti saremo molto grati.";
			link.l1 = "Probabilmente no. Non conosco abbastanza bene la zona locale per cercare una cache. Mi scuso, devo andare.";
			link.l1.go = "CapComission_Mayor5";
			link.l2 = "Forse... Quanto tempo ho?";
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
			dialog.text = "Credo che tra due giorni le pattuglie possano localizzare la cache senza il tuo aiuto, quindi dovresti sbrigarti."; 
			link.l1 = "Sì, me ne sto occupando. Ma dovrò fare visita al capitano "+pchar.GenQuest.CaptainComission.Name+". Può essere organizzato?";
			link.l1.go = "CapComission_Mayor7";
		break;
		
		case "CapComission_Mayor7":
			dialog.text = "Non sarà un problema. Informerò il comandante del forte della tua visita.";
			link.l1 = "Grazie. Ora, per favore scusami.";
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
			dialog.text = "Eccellente! Dove si trova il tesoro?";
			link.l1 = "Non ho ancora idea. Non mi ha indicato la posizione esatta.";
			link.l1.go = "CapComission_Mayor10";
		break;
		
		case "CapComission_Mayor10":
			dialog.text = "Mmm, che coincidenza! Sai, lui 'non ha indicato' nemmeno a me la posizione esatta...";
			link.l1 = "Sto lavorando su di esso.";
			link.l1.go = "CapComission_Mayor11";
		break;
		
		case "CapComission_Mayor11":
			dialog.text = "Non più\nGuardie! Riportate il prigioniero nelle camere\nSei libero di andare, "+GetFullName(pchar)+".";
			link.l1 = "Ma governatore...";
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
			dialog.text = "Eccellente! E dove andremo a cercare il suo tesoro?";
			link.l1 = "Nel "+RandPhraseSimple(RandPhraseSimple("settentrionale","occidentale"),RandPhraseSimple("orientale","meridionale"))+" fine di "+XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore+"Gen")+" ai piedi della scogliera c'è una grande nicchia, l'ingresso è pieno di pietre. Quello è il nascondiglio.";
			link.l1.go = "CapComission_Mayor14";
		break;
		
		case "CapComission_Mayor14":
			dialog.text = "Ottimo lavoro! E dove è "+pchar.GenQuest.CaptainComission.Name+" lui stesso? Mi è stato detto che l'hai preso dalle segrete del forte.";
			link.l1 = "Sfortunatamente, è perito in uno scontro con i contrabbandieri.";
			link.l1.go = "CapComission_Mayor15";
		break;
		
		case "CapComission_Mayor15":
			dialog.text = "Questo è brutto... Questo è molto brutto, "+GetSexPhrase("signore","signorina")+" "+GetFullName(pchar)+". Stavo per eseguire la sua esecuzione in pubblico, 'per incoraggiare gli altri.'"+"Comunque, non avrebbe evitato la forca\nQuindi, poiché hai tecnicamente violato la legge, liberando illegalmente un prigioniero, ma comunque non lo hai salvato, non posso risolvere questo nel rapporto. Pertanto, non ottieni una ricompensa... Ma vorrei ringraziarti personalmente. Accetta il mio dono - una cosa molto utile per un capitano combattente. ";
			link.l1 = "Grazie. Sempre felice di servire.";	
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
				dialog.text = RandPhraseSimple("Come fai? Ci vogliono almeno quindici giorni per arrivare a quel posto anche quando si naviga con il vento!","Capitano "+GetFullName(pchar)+", la tua irresponsabilità mi stupisce! Perché non me ne hai parlato prima?");
				link.l1 = "Bene, non so nemmeno cosa dire...";
				link.l1.go = "ShipWreck2";
			}
			else
			{
				dialog.text = "Queste sono ottime notizie! Avevamo già perso la speranza di vedere "+pchar.GenQuest.ShipWreck.Name+"  di nuovo vivo. Invierò immediatamente una squadra di soccorso. Oh, e per favore accetta questa ricompensa per la tua efficienza e partecipazione al loro salvataggio.";
				link.l1 = "Grazie, Vostra Grazia. Sono lieto di essere stato in grado di aiutare. Sono sicuro che la spedizione arriverà lì in tempo.";
				link.l1.go = "ShipWreck3";	
			}
			pchar.GenQuest.ShipWreck.SpeakMayor = true;
			pchar.quest.ShipWreck_MeetInShore.over = "yes";
			pchar.quest.ShipWreck_SaveSailors.over = "yes"; // belamour gen таймер на 30 дней тоже нужно снять
		break;
		
		case "ShipWreck2":
			dialog.text = "Caspita... Cosa c'è da dire? Vai e studia la Legge del Mare, ragazzo! Comunque, farò del mio meglio per salvare queste persone.";
			link.l1 = "Vostra Grazia, ma li ho lasciati con abbastanza provviste. Avete tempo, vi assicuro ...";
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
			dialog.text = "Sono consapevole che tu, come dire... "+GetSexPhrase("sei un assiduo frequentatore di bordelli","mi piace visitare i bordelli di tanto in tanto")+". E quindi ho deciso di rivolgermi a te per aiuto\n"+"Sai, mi vergogno ad ammetterlo, ma ero lì di recente...";
			link.l1 = "E che c'è di male? Il sesso è una cosa perfettamente naturale, lo sai...";
			link.l1.go = "TakeRing_2";
		break;
		case "TakeRing_2":
			dialog.text = "Oh, no, non sto predicando, no. Il fatto è che in una occasione avevo bevuto troppo e ho perso il mio anello di matrimonio...";
			link.l1 = "Ecco un problema. Mi dispiace.";
			link.l1.go = "TakeRing_3";
		break;
		case "TakeRing_3":
			dialog.text = "Non ho bisogno che nessuno si dispiaccia per me. Ho bisogno del mio anello indietro. Se riesci a riportarlo prima della mezzanotte, sarò molto generoso. Se fallisci, mia moglie mi ucciderà.";
			link.l1 = "Capisco... E dove esattamente potresti averlo perso? Ricordi qualcosa in particolare?";
			link.l1.go = "TakeRing_4";
		break;
		case "TakeRing_4":
			dialog.text = "Sfortunatamente, no. Non una cosa.";
			link.l1 = "Capisco. Beh, allora cerchiamolo.";
			link.l1.go = "TakeRing_5";
			link.l2 = "Sai, "+GetAddress_FormToNPC(NPChar)+", Credo che rifiuterò questa volta. Mi scusi...";
			link.l2.go = "TakeRing_6";
		break;	
		case "TakeRing_5":
			dialog.text = "Eccellente! Ma ricorda - devi trovarlo prima della mezzanotte.";
			link.l1 = "Ricordo. Tornerò presto.";
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
			dialog.text = "Oh? Beh, questo è davvero inaspettato... Beh, buona fortuna a te, allora, capitano.";
			link.l1 = "Addio.";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
		break;

		case "TakeRing_S1":
			dialog.text = "È il mio anello! Hai salvato la mia vita!";
			link.l1 = "Non è niente, signore.";
			link.l1.go = "TakeRing_S2";
			TakeItemFromCharacter(pchar, "MayorsRing");
		break;
		case "TakeRing_S2":
			dialog.text = "Ecco i tuoi soldi per un lavoro ben fatto! Ti sono molto grato!";
			link.l1 = "Contento di aiutare signore, per favore stia più attento la prossima volta.";
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
			dialog.text = "Signore, abbi pietà! Dovrei davvero smettere di bere così tanto...";
			link.l1 = "Questo è certo! Ecco il tuo anello.";
			link.l1.go = "TakeRing_S4";
		break;
		case "TakeRing_S4":
			dialog.text = "Sì, sì, grazie mille. Sono in debito con te! Ecco i tuoi soldi per un lavoro ben fatto!";
			link.l1 = "Grazie "+GetAddress_FormToNPC(NPChar)+".";
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
                    dialog.text = "Abbiamo già discusso tutto, non è vero?";
                    link.l1 = "Corretto. Non ti ritardo ulteriormente.";
                    link.l1.go = "exit";

                }
                else
                {
                    dialog.text = "Mi dispiace disturbarti, ma non ho tempo per parlare con te al momento. Come dovresti sapere, la nostra colonia è stata attaccata da "+NationNamePeople(sti(aData.nation))+". Devo provvedere alle nostre difese.";
                    link.l1 = "Beh, volevo solo offrire il mio aiuto nella difesa del forte.";
                    link.l1.go = "siege_task";
                    link.l2 = "Allora non ti tratterrò ulteriormente.";
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
                    dialog.text = "Oh, sei tu, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+", Sono contento di vederti. Buone notizie - siamo riusciti a respingere il "+NationNameSK(sti(aData.nation))+" invasori. Anche tu hai fatto la tua parte in questo, ed ecco la tua ricompensa - "+(sti(aData.iSquadronPower)*1500)+" pezzi di otto. Ecco a te.";
                    link.l1 = "Grazie, "+GetAddress_FormToNPC(NPChar)+", piacere di fare affari con te!";
                    link.l1.go = "exit";
                }
                else
                {
                    if (CheckAttribute(aData, "PlayerHelpMayor")) DeleteAttribute(aData, "PlayerHelpMayor");
                    dialog.text = "Allora, qual è stato il motivo per cui sei venuto qui a distrarmi da importanti affari di stato?";
					if (npchar.city != "Panama") // Addon-2016 Jason
					{
						link.l1 = "Volevo lavorare per "+NationNameGenitive(sti(NPChar.nation))+".";
						link.l1.go = "work";
					}
					// Warship Генер "Пираты на необитайке" - сдаём пиратов властям
					if(CheckAttribute(PChar, "Quest.PiratesOnUninhabited_OnShore") || CheckAttribute(PChar, "Quest.PiratesOnUninhabited_ShipSink"))
					{
						link.l11 = XI_ConvertString(PChar.GenQuest.PiratesOnUninhabited.StartShore+"Dat")+" Ho incontrato alcuni pirati. Tutti "+PChar.GenQuest.PiratesOnUninhabited.PiratesCount+" sono a bordo al momento. Voglio consegnarli alle autorità.";
						link.l11.go = "PiratesOnUninhabited_1";
					}
					
        			link.l2 = "Stavo per parlarti di un affare importante.";
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
							link.l12 = "C'è un capitano al comando della pattuglia "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")+"Acc"))+" nominato "+pchar.GenQuest.CaptainComission.Name+", come posso incontrarlo?";
							link.l12.go = "CapComission_Mayor1";
						}	
						if(CheckAttribute(pchar,"GenQuest.CaptainComission.PrisonFree"))
						{
							link.l12 = "Ex capitano al comando della pattuglia "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")+"Acc"))+" "+pchar.GenQuest.CaptainComission.Name+" ha accettato di rivelare il suo nascondiglio alle autorità.";
							link.l12.go = "CapComission_Mayor9";
						}
						if(pchar.GenQuest.CaptainComission == "GetGoodsSuccess")
						{
							link.l12 = "Ex capitano al comando della pattuglia  "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")+"Acc"))+" "+pchar.GenQuest.CaptainComission.Name+" mi ha rivelato il suo nascondiglio.";
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
								link.l13 = UpperFirst(XI_ConvertString(pchar.GenQuest.ShipWreck.Shore+"Dat"))+" Ho incontrato un capitano "+pchar.GenQuest.ShipWreck.Name+" e i suoi marinai che furono messi a terra dai pirati "+pchar.GenQuest.ShipWreck.BadName+". "+"Sfortunatamente, avevo già troppi uomini sulla mia nave e quindi non potevo prenderli a bordo. Ma ho lasciato loro cibo e armi. Se la nave di soccorso non li raccoglie entro "+(30 - iDay)+" giorni, poi non so se li troverò ancora vivi o no.";
								link.l13.go = "ShipWreck1";
							}
							else
							{
								link.l13 = UpperFirst(XI_ConvertString(pchar.GenQuest.ShipWreck.Shore+"Dat"))+" Ho incontrato marinai da un naufragio vittima della nave '"+pchar.GenQuest.ShipWreck.ShipTypeName+"' con il loro capitano. "+"Sfortunatamente, avevo già troppi uomini sulla mia nave e quindi non potevo prenderli a bordo. Ma ho lasciato loro cibo e armi. Se la nave di soccorso non li raccoglie entro "+(30 - iDay)+" giorni, poi non so se li troveranno ancora vivi o no.";
								link.l13.go = "ShipWreck1";							
							}	
						}	
					}					
					//--> Jason, генер почтового курьера 2 уровня
						if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.LevelUp"))
						{
							if (pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
							{
							link.l14 = "Ho un messaggio dalla città di "+XI_ConvertString("Colonìa"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen")+".";
							link.l14.go = "Postcureer_LevelUp_ForAll";
							}
						}
					//<-- генер почтового курьера 2 уровня
					
					// --> Warship, 16.05.11. Квест "Правосудие на продажу".
					if(CheckAttribute(PChar, "GenQuest.JusticeOnSale.MayorWait") && CheckAttribute(PChar, "GenQuest.JusticeOnSale.CityId") && NPChar.location == PChar.GenQuest.JusticeOnSale.CityId + "_townhall")
					{
						link.l15 = "Milord, ho localizzato una banda di contrabbandieri il cui capo è stato recentemente catturato dalle guardie. Ora stanno tramando la sua fuga. La loro nave '"+PChar.GenQuest.JusticeOnSale.ShipName+"' è ormeggiato a "+XI_ConvertString(PChar.GenQuest.JusticeOnSale.ShoreId+"Gen")+".";
						link.l15.go = "JusticeOnSale_1";
					}
					//<-- Правосудие на продажу
					
        			if (GetPrisonerQty() > 0)
        			{
                        link.l3 = "Devo consegnare il capitano prigioniero alle autorità.";
        			    link.l3.go = "sell_prisoner";
        			}
					//Jason --> Регата
					if (CheckAttribute(pchar, "questTemp.Regata.ToPortRoyal") && NPChar.location == "Portroyal_townhall")
					{
						link.l4 = "Sono qui per la regata. Ecco il mio invito.";
						link.l4.go = "Regata";
					}
        			link.l5 = "Forse vorresti fare una pausa?";
        			link.l5.go = "Play_Game";
        			link.l10 = "Era solo una visita di cortesia, "+GetAddress_FormToNPC(NPChar)+".";
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
                    dialog.text = "Abbiamo già discusso di tutto, non è vero?";
                    link.l1 = "Corretto. Non ti tratterrò più a lungo.";
                    link.l1.go = "exit";

                }
                else
                {
                    dialog.text = "Mi dispiace disturbarti, ma al momento non ho tempo di parlare con te. Come dovresti sapere, la nostra colonia è stata attaccata da "+NationNamePeople(sti(aData.nation))+". Devo vedere alle nostre difese.";
                    link.l1 = "Ebbene, volevo solo offrire il mio aiuto nella difesa del forte.";
                    link.l1.go = "siege_task";
                    link.l2 = "Allora non ti ritarderò ulteriormente.";
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
                    dialog.text = "Oh, sei tu, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+", Sono felice di vederti. Buone notizie - siamo riusciti a respingere il "+NationNameSK(sti(aData.nation))+" invasori. Anche tu hai fatto la tua parte in questo, ed ecco la tua ricompensa - "+(sti(aData.iSquadronPower)*1500)+" pezzi di otto. Ecco a te.";
                    link.l1 = "Grazie, "+GetAddress_FormToNPC(NPChar)+", piacere di fare affari con te!";
                    link.l1.go = "exit";
                }
                else
                {
                    if (CheckAttribute(aData, "PlayerHelpMayor")) DeleteAttribute(aData, "PlayerHelpMayor");
                    dialog.text = "Cosa ti porta da me? Pensavo che tu gestissi tutti i tuoi affari con il tuo... patrono. Ma parla, sono sempre lieto di ascoltarti.";
					if (npchar.city != "Panama") // Addon-2016 Jason
					{
						link.l1 = "Volevo lavorare per "+NationNameGenitive(sti(NPChar.nation))+".";
						link.l1.go = "work";
					}
					// Warship Генер "Пираты на необитайке" - сдаём пиратов властям
					if(CheckAttribute(PChar, "Quest.PiratesOnUninhabited_OnShore") || CheckAttribute(PChar, "Quest.PiratesOnUninhabited_ShipSink"))
					{
						link.l11 = XI_ConvertString(PChar.GenQuest.PiratesOnUninhabited.StartShore+"Dat")+" Ho incontrato alcuni pirati. Tutti "+PChar.GenQuest.PiratesOnUninhabited.PiratesCount+" sono a bordo al momento. Voglio consegnarli alle autorità.";
						link.l11.go = "PiratesOnUninhabited_1";
					}
					
        			link.l2 = "Stavo per parlarti di un affare importante.";
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
							link.l12 = "C'è un capitano al comando della pattuglia "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")+"Acc"))+" nominato "+pchar.GenQuest.CaptainComission.Name+", come posso incontrarlo?";
							link.l12.go = "CapComission_Mayor1";
						}	
						if(CheckAttribute(pchar,"GenQuest.CaptainComission.PrisonFree"))
						{
							link.l12 = "Ex capitano al comando della pattuglia "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")+"Acc"))+" "+pchar.GenQuest.CaptainComission.Name+" ha accettato di rivelare il suo nascondiglio alle autorità.";
							link.l12.go = "CapComission_Mayor9";
						}
						if(pchar.GenQuest.CaptainComission == "GetGoodsSuccess")
						{
							link.l12 = "Ex capitano al comando della pattuglia  "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")+"Acc"))+" "+pchar.GenQuest.CaptainComission.Name+" ha rivelato a me il suo nascondiglio.";
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
								link.l13 = UpperFirst(XI_ConvertString(pchar.GenQuest.ShipWreck.Shore+"Dat"))+" Ho incontrato un capitano "+pchar.GenQuest.ShipWreck.Name+" e i suoi marinai che sono stati messi a terra dai pirati "+pchar.GenQuest.ShipWreck.BadName+". "+"Sfortunatamente, avevo già troppi uomini sulla mia nave e quindi non potevo prenderli a bordo. Ma ho lasciato loro cibo e armi. Se la nave di soccorso non li raccoglie entro "+(30 - iDay)+" giorni, poi non so se li troveranno ancora vivi o no.";
								link.l13.go = "ShipWreck1";
							}
							else
							{
								link.l13 = UpperFirst(XI_ConvertString(pchar.GenQuest.ShipWreck.Shore+"Dat"))+" Ho incontrato marinai da un naufragio vittima della nave '"+pchar.GenQuest.ShipWreck.ShipTypeName+"' con il loro capitano. "+"Sfortunatamente, avevo già troppi uomini sulla mia nave e quindi non potevo prenderli a bordo. Ma ho lasciato loro cibo e armi. Se la nave di soccorso non li raccoglie entro "+(30 - iDay)+" giorni, poi non so se li troverò ancora vivi o no.";
								link.l13.go = "ShipWreck1";							
							}	
						}	
					}					
					//--> Jason, генер почтового курьера 2 уровня
						if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.LevelUp"))
						{
							if (pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
							{
							link.l14 = "Ho un messaggio dalla città di "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen")+".";
							link.l14.go = "Postcureer_LevelUp_ForAll";
							}
						}
					//<-- генер почтового курьера 2 уровня
					
					// --> Warship, 16.05.11. Квест "Правосудие на продажу".
					if(CheckAttribute(PChar, "GenQuest.JusticeOnSale.MayorWait") && CheckAttribute(PChar, "GenQuest.JusticeOnSale.CityId") && NPChar.location == PChar.GenQuest.JusticeOnSale.CityId + "_townhall")
					{
						link.l15 = "Milord, ho localizzato una banda di contrabbandieri il cui capo è stato recentemente catturato dalle guardie. Ora stanno tramando la sua fuga. La loro nave '"+PChar.GenQuest.JusticeOnSale.ShipName+"' è ormeggiato a "+XI_ConvertString(PChar.GenQuest.JusticeOnSale.ShoreId+"Gen")+".";
						link.l15.go = "JusticeOnSale_1";
					}
					//<-- Правосудие на продажу
					
        			if (GetPrisonerQty() > 0)
        			{
                        link.l3 = "Devo consegnare il capitano prigioniero alle autorità.";
        			    link.l3.go = "sell_prisoner";
        			}
					//Jason --> Регата
					if (CheckAttribute(pchar, "questTemp.Regata.ToPortRoyal") && NPChar.location == "Portroyal_townhall")
					{
						link.l4 = "Sono qui per la regata. Ecco il mio invito.";
						link.l4.go = "Regata";
					}
        			link.l5 = "Forse vorresti fare una pausa?";
        			link.l5.go = "Play_Game";
        			link.l10 = "Era solo una visita di cortesia, "+GetAddress_FormToNPC(NPChar)+".";
        			link.l10.go = "node_2";
                }
    		}//<-
		break;
		
		case "Play_Game":
			//==> прибыла инспекция на Святом Милосердии
			if (CheckAttribute(npchar, "quest.SantaMisericordia"))
			{
    			dialog.text = "Non adesso! Abbiamo un'ispezione, don de Alamida è in città. Oh, ogni anno la stessa cosa, cosa ho fatto per meritare questo...";
				link.l1 = "Come dici tu. Non ti distrarrò.";
				link.l1.go = "exit"; 
				break;
			}
			//<== прибыла инспекция на Святом Милосердии
			dialog.text = "Uhm, e quali tipi di giochi preferisci?";
			link.l1 = "Vuoi giocare a carte per dei soldi seri?";
			link.l1.go = "Card_Game";
   			link.l2 = "Che ne dici di tirare qualche dado a poker-joker?";
			link.l2.go = "Dice_Game";
			link.l10 = "Mi scusi, ma il dovere chiama.";
			link.l10.go = "exit";
		break;
		
		//  карты -->
        case "Card_Game":
            if (!CheckNPCQuestDate(npchar, "Card_date_Yet") || sti(PChar.rank) < 4 || isBadReputation(pchar, 50) || GetCharacterSkillToOld(pchar, SKILL_LEADERSHIP) < rand(5))
            {
                SetNPCQuestDate(npchar, "Card_date_Yet");
				// belamour legendary edition фикс проверки мундира с мушкетом
				if(IsUniformEquip()) dialog.text = "Chiedo perdono, monsignore, ma non ho tempo per questo ora. Forse la prossima volta."; // Jason НСО
                else dialog.text = "Non gioco d'azzardo con i pirati!";
    			link.l1 = "Come desideri.";
    			link.l1.go = "exit";
			}
			else
			{
				if (CheckNPCQuestDate(npchar, "Card_date_begin"))
				{
					dialog.text = "Perché no! Rilassarsi fa bene al cuore, ma non al borsellino...";
	    			link.l1 = "Eccellente.";
	    			link.l1.go = "Cards_begin";
	    			link.l2 = "Quali sono le regole del nostro gioco?";
	    			link.l2.go = "Cards_Rule";
    			}
    			else
    			{
					dialog.text = "No, ho finito per oggi. Ho cose da fare.";
	    			link.l1 = "Come desideri.";
	    			link.l1.go = "exit";
				}
			}
		break;

		case "Cards_Rule":
   			dialog.text = CARDS_RULE;
			link.l1 = "Ebbene, cominciamo allora!";
			link.l1.go = "Cards_begin";
			link.l3 = "No, non fa per me...";
			link.l3.go = "exit";
		break;

		case "Cards_begin":
			dialog.text = "Prima concordiamo sulla scommessa.";
			link.l1 = "Giochiamo per 1000 pezzi di otto.";
			link.l1.go = "Cards_Node_100";
			link.l2 = "Giochiamo per 5000 pezzi di otto.";
			link.l2.go = "Cards_Node_500";
			link.l3 = "Immagino che io debba andare.";
			link.l3.go = "exit";
		break;

		case "Cards_Node_100":
			//belamour legendary edition 
			bOk1 = isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && GetNationRelation(npchar.nation, sti(Items[sti(pchar.EquipedPatentId)].Nation)) != RELATION_ENEMY;
			bOk2 = CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && GetNationRelation(npchar.nation, FRANCE) != RELATION_ENEMY;
			bOk = bOk1 || bOk2;
            if (!CheckCardsGameSmallRate() && !bOk)
		    {
                dialog.text = "Sei un noto baro. Non giocherò d'azzardo con te.";
                link.l1 = "È tutto bugie!";
			    link.l1.go = "exit";
			    break;
		    }

			if (sti(pchar.Money) < 3000)
		    {
                dialog.text = "Stai scherzando, "+GetAddress_Form(NPChar)+"? Non hai soldi!";
                link.l1 = "Succede.";
			    link.l1.go = "exit";
			    break;
		    }
		    if (sti(npchar.Money) < 3000)
		    {
                dialog.text = "Ecco fatto! Ho finito con le carte - prima che mi chiamino uno spendaccione e mi costringano a lasciare il mio incarico.";
                link.l1 = "Peccato.";
			    link.l1.go = "exit";
			    break;
		    }
   			dialog.text = "Bene, giochiamo per 1000 pezzi di otto.";
			link.l1 = "Iniziamo!";
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
                dialog.text = "Sei un noto baro. Non giocherò d'azzardo con te.";
                link.l1 = "È tutto falso! Beh, comunque sia.";
			    link.l1.go = "exit";
			    break;
		    }
			if (!CheckCardsGameBigRate())
		    {
                dialog.text = "Dicono che tu sia un giocatore molto bravo. Non giocherò con te a puntate alte.";
                link.l1 = "Dovremmo abbassare la puntata, forse?";
			    link.l1.go = "Cards_Node_100";
				link.l2 = "Mi dispiace, ma devo andare.";
			    link.l2.go = "exit";
			    break;
		    }

			if (sti(pchar.Money) < 15000)
		    {
                dialog.text = "Stai scherzando, "+GetAddress_Form(npchar)+"? Non hai 15000 pezzi di otto!";
                link.l1 = "Li alzerò!";
			    link.l1.go = "exit";
			    break;
		    }
		    if (sti(npchar.Money) < 15000)
		    {
                dialog.text = "No, queste scommesse svuoteranno la tesoreria della città.";
                link.l1 = "Come desideri.";
			    link.l1.go = "exit";
			    break;
		    }
   			dialog.text = "Bene, giochiamo per 5000 pezzi di otto.";
			link.l1 = "Iniziamo!";
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
				if(IsUniformEquip()) dialog.text = "Chiedo scusa, monsignore, ma non ho tempo per questo adesso. Forse la prossima volta."; // Jason НСО
                else dialog.text = "Non giocherò d'azzardo con i pirati!";
    			link.l1 = "Come desideri.";
    			link.l1.go = "exit";
			}
			else
			{
				if (CheckNPCQuestDate(npchar, "Dice_date_begin"))
				{
					dialog.text = "Perché no! Rilassarsi fa bene al cuore... ma non al portafoglio...";
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
			dialog.text = "Concordiamo prima sulla scommessa.";
			link.l1 = "Giochiamo per 500 pezzi di otto per dado.";
			link.l1.go = "Dice_Node_100";
			link.l2 = "Giochiamo per 2000 pezzi di otto per dado.";
			link.l2.go = "Dice_Node_500";
			link.l3 = "Immagino che debba andare.";
			link.l3.go = "exit";
		break;

		case "Dice_Node_100":
			//belamour legendary edition 
			bOk1 = isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && GetNationRelation(npchar.nation, sti(Items[sti(pchar.EquipedPatentId)].Nation)) != RELATION_ENEMY;
			bOk2 = CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && GetNationRelation(npchar.nation, FRANCE) != RELATION_ENEMY;
			bOk = bOk1 || bOk2;
            if (!CheckDiceGameSmallRate() && !bOk)
		    {
                dialog.text = "Sei un noto baro. Non giocherò d'azzardo con te.";
                link.l1 = "Sono tutte bugie! Beh, comunque sia.";
			    link.l1.go = "exit";
			    break;
		    }

			if (sti(pchar.Money) < 3000)
		    {
                dialog.text = "Stai scherzando, "+GetAddress_Form(NPChar)+"? Non hai soldi!";
                link.l1 = "Succede.";
			    link.l1.go = "exit";
			    break;
		    }
		    if (sti(npchar.Money) < 3000)
		    {
                dialog.text = "È finita! Ho finito con il gioco d'azzardo - prima che mi chiamino uno spendaccione e mi costringano a lasciare il mio incarico...";
                link.l1 = "Peccato.";
			    link.l1.go = "exit";
			    break;
		    }
   			dialog.text = "Bene, giochiamo per 500 pezzi da otto.";
			link.l1 = "Iniziamo!";
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
                dialog.text = "Sei un noto baro. Non giocherò d'azzardo con te.";
                link.l1 = "È tutto falso! Beh, comunque sia.";
			    link.l1.go = "exit";
			    break;
		    }
			if (!CheckDiceGameBigRate())
		    {
                dialog.text = "Dicono che tu sia un giocatore molto bravo. Non giocherò a posta alta con te.";
                link.l1 = "Dovremmo abbassare la scommessa, forse?";
			    link.l1.go = "Dice_Node_100";
				link.l2 = "Mi dispiace, ma devo andare.";
			    link.l2.go = "exit";
			    break;
		    }

			if (sti(pchar.Money) < 15000)
		    {
                dialog.text = "Stai scherzando, "+GetAddress_Form(NPChar)+"? Non hai 15000 pezzi di otto!";
                link.l1 = "Li solleverò!";
			    link.l1.go = "exit";
			    break;
		    }
		    if (sti(npchar.Money) < 15000)
		    {
                dialog.text = "No, queste scommesse svuoteranno certamente il tesoro della città.";
                link.l1 = "Come desideri.";
			    link.l1.go = "exit";
			    break;
		    }
   			dialog.text = "Bene, giochiamo per 2000 pezzi di otto per dado.";
			link.l1 = "Iniziamo!";
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
			dialog.text = "In tal caso ti chiederei di lasciare il mio studio e smettere di distrarmi dal mio lavoro";
			link.l1 = "Sì, sì, naturalmente. Mi dispiace di disturbarti.";
			link.l1.go = "exit";
		break;

		//---------------------------- генератор квестов мэра -------------------------------
		case "work": 
            dialog.text = "Questo è un bug. Informa gli sviluppatori al riguardo.";
        	link.l1 = "Grazie, è un ottimo gioco!";
        	link.l1.go = "exit";
			
			//==> прибыла инспекция на Святом Милосердии
			if (CheckAttribute(npchar, "quest.SantaMisericordia"))
			{
    			dialog.text = "Non ora! Abbiamo un'ispezione, don de Alamida è in città. Oh, ogni anno la stessa cosa, cosa ho fatto per meritare questo...";
				link.l1 = "Come dici tu. Non ti distrarrò.";
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
					dialog.text = RandPhraseSimple("Per quanto posso capire, hai già una missione assegnata dal governatore di "+XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.(QuestName).MayorId)].city+"Gen")+". Finisci il lavoro che hai già e poi parleremo.","Mmm, non eri tu in "+XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.(QuestName).MayorId)].city+"Voc")+" dove hai preso ordini dal governatore locale? Sì, è corretto. Termina prima quella missione.");
					link.l1 = RandPhraseSimple("Capisco...","Capito..."+GetSexPhrase("","")+", "+GetAddress_FormToNPC(NPChar)+".");
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
							dialog.text = LinkRandPhrase("Una missione per localizzare il bandito "+GetFullName(arName)+" ti è già stato assegnato. Ora adempilo!","Hai già una missione per localizzare un bandito di nome "+GetFullName(arName)+". Sto aspettando i risultati!","Mentre tu stai perdendo il tuo tempo nella mia residenza, "+GetFullName(arName)+" sta derubando i nostri coloni! Mettiti al lavoro!");
							link.l1 = RandPhraseSimple("Bene, "+GetAddress_FormToNPC(NPChar)+".","Sono occupato con questo, "+GetAddress_FormToNPC(NPChar)+".");
							link.l1.go = "exit";		
						break;
						case "Late":
							dialog.text = RandPhraseSimple("Il tempo concesso per localizzare ed eliminare quel bandito è finito. E che tipo di rapporti sto ricevendo, cosa pensi? E ti dirò - "+GetFullName(arName)+" è ancora vivo e vegeto! Ora spiegati, "+GetAddress_Form(NPChar)+".","Il tempo a tua disposizione per eliminare quel mascalzone di nome "+GetFullName(arName)+", è esaurito. Eppure, mi dicono che non è stato fatto alcun progresso. Cosa succede?");
							link.l1 = "Non sono riuscito a svolgere il vostro compito nel tempo prestabilito, "+GetAddress_FormToNPC(NPChar)+".";
							link.l1.go = "All_Late";		
						break;
						case "Found":
							dialog.text = RandPhraseSimple("Allora, cosa dici? Sei riuscito a eliminare il bandito menzionato? "+GetFullName(arName)+" è finalmente morto?","Dimmi solo una cosa - è "+GetFullName(arName)+" vivo o morto?");
							link.l1 = "Sfortunatamente, ancora vivo, "+GetAddress_FormToNPC(NPChar)+". Sono riuscito a trovarlo, ma ero in svantaggio e sono stato costretto a ritirarmi. Quel bandito è un vero bastardo tosto. Mi dispiace.";
							link.l1.go = "All_Found";		
						break;
						case "Execute":
							dialog.text = RandPhraseSimple("Allora, cosa dici? Sei riuscito a eliminare il bandito menzionato?"+GetFullName(arName)+" è finalmente morto?","Dimmi solo una cosa - è "+GetFullName(arName)+" morto o vivo?");
							link.l1 = "È morto, "+GetAddress_FormToNPC(NPChar)+".";
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
							dialog.text = LinkRandPhrase("Ti è già stata assegnata una missione per catturare una nave corriere. Ora adempilo!","Hai già una missione per catturare una nave corriere! Sto aspettando i risultati!","Mentre tu sprechi il tuo tempo nella mia residenza, i documenti di cui ho bisogno stanno finendo direttamente nelle mani del nostro nemico! Mettiti al lavoro!");
							link.l1 = RandPhraseSimple("Bene, "+GetAddress_FormToNPC(NPChar)+".","Sono occupato con questo, "+GetAddress_FormToNPC(NPChar)+".");
							link.l1.go = "exit";		
						break;
						case "Late":
							dialog.text = RandPhraseSimple("Il tempo che ti è stato dato per localizzare e catturare quella nave corriere è finito. E che tipo di rapporti sto ricevendo, secondo te? E ti dirò - i documenti che mi aspettavo sono finiti proprio nelle mani del nostro nemico! Ora degnati di spiegarti, "+GetAddress_Form(NPChar)+".","Tutti i termini dati a te per catturare i documenti dalla nave del corriere, sono scaduti. Eppure, non si è fatto alcun progresso. Che cos'è questo?");
							link.l1 = "Non sono riuscito a svolgere il lavoro in tempo, "+GetAddress_FormToNPC(NPChar)+".";
							link.l1.go = "All_Late";		
						break;
						case "Found":
							dialog.text = RandPhraseSimple("Allora, cosa dici? Sei riuscito a catturare i documenti?","Dimmi solo una cosa - sei riuscito a garantire la corrispondenza?");
							link.l1 = "Sfortunatamente, no, "+GetAddress_FormToNPC(NPChar)+". Ho localizzato la nave, ma i documenti mi hanno sfuggito.";
							link.l1.go = "All_Found";		
						break;
						case "Execute":
							dialog.text = RandPhraseSimple("Allora, cosa dici? Sei riuscito a catturare i documenti?","Dimmi solo una cosa - sei riuscito a mettere al sicuro la corrispondenza?");
							link.l1 = "Sì, "+GetAddress_FormToNPC(NPChar)+". Li ho. Ecco a te.";
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
							dialog.text = LinkRandPhrase("Ti è già stata assegnata una missione per distruggere un trasporto militare. Ora adempila!","Hai già una missione per distruggere un trasporto militare! Sto aspettando i risultati!","Mentre tu perdi tempo nella mia residenza, polvere da sparo e munizioni vengono consegnate direttamente ai cannoni nemici! Mettiti al lavoro!");
							link.l1 = RandPhraseSimple("Bene, "+GetAddress_FormToNPC(NPChar)+".","Sono impegnato con questo, "+GetAddress_FormToNPC(NPChar)+".");
							link.l1.go = "exit";		
						break;
						case "Late":
							dialog.text = RandPhraseSimple("Il tempo a tua disposizione per localizzare e distruggere quel trasporto militare è finito. E quali tipi di rapporti credi che stia ricevendo, secondo te? E ti dirò - il convoglio nemico ha raggiunto con successo la sua destinazione! Ora degnati di spiegarti, "+GetAddress_Form(NPChar)+".","Tutti i termini dati a te per distruggere il trasporto militare nemico, sono scaduti. Eppure, non sono stati fatti progressi. Cosa succede?");
							link.l1 = "Non sono riuscito a eseguire il vostro compito nel tempo assegnato, "+GetAddress_FormToNPC(NPChar)+".";
							link.l1.go = "All_Late";		
						break;
						case "Found":
							dialog.text = RandPhraseSimple("Allora, cosa dici? Sei riuscito a distruggere il trasporto nemico?","Dimmi solo una cosa - quel nemico sta riposando sul fondo del mare?");
							link.l1 = "Sfortunatamente, no, "+GetAddress_FormToNPC(NPChar)+". Ho localizzato il convoglio, ma non sono riuscito a affondare la nave richiesta.";
							link.l1.go = "All_Found";		
						break;
						case "Execute":
							dialog.text = RandPhraseSimple("Allora, cosa ne dici? Sei riuscito a distruggere quel trasporto nemico?","Dimmi solo una cosa - l'arsenale nemico riposa sul fondo del mare?");
							link.l1 = "Sì, "+GetAddress_FormToNPC(NPChar)+". Il nostro nemico non riceverà quella polvere da sparo e munizioni.";
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
							dialog.text = LinkRandPhrase("Ti è già stata assegnata una missione per eliminare un pirata. Ora adempila!","Hai già una missione per distruggere una nave pirata! Sto aspettando i risultati!","Mentre tu stai perdendo il tuo tempo nella mia residenza, quel sporco pirata sta depredando un'altra vittima! Mettiti al lavoro!");
							link.l1 = RandPhraseSimple("Bene, "+GetAddress_FormToNPC(NPChar)+".","Sono occupato con questo, "+GetAddress_FormToNPC(NPChar)+".");
							link.l1.go = "exit";		
						break;
						case "Late":
							dialog.text = RandPhraseSimple("Il tempo che ti è stato dato per localizzare ed eliminare il pirata è finito. E che tipo di rapporti credi che stia ricevendo? E ti dirò - quel sporco pirata sta ancora predando le nostre navi! Ora degnati di spiegarti, "+GetAddress_Form(NPChar)+".","Tutti i termini dati per distruggere la nave pirata sono scaduti. Eppure, non si è fatto alcun progresso. Cosa succede?");
							link.l1 = "Non sono riuscito a svolgere il vostro incarico in tempo, "+GetAddress_FormToNPC(NPChar)+".";
							link.l1.go = "All_Late";		
						break;
						case "Found":
							dialog.text = RandPhraseSimple("Allora, cosa dici? Sei riuscito a distruggere la nave pirata?","Dimmi solo una cosa - quel sporco pirata riposa finalmente sul fondo del mare?");
							link.l1 = "Sfortunatamente, no, "+GetAddress_FormToNPC(NPChar)+". Sono riuscito a trovare quel mascalzone, ma non sono riuscito a affondare la sua nave.";
							link.l1.go = "All_Found";		
						break;
						case "Execute":
							dialog.text = RandPhraseSimple("Allora, cosa dici? Sei riuscito a distruggere la nave pirata?","Dimmi solo una cosa - quel sporco pirata riposa finalmente sul fondo del mare?");
							link.l1 = "Sì, "+GetAddress_FormToNPC(NPChar)+". Quel mascalzone non disturberà più il nostro commercio marittimo.";
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
							dialog.text = LinkRandPhrase("Ti è già stata assegnata una missione per cercare un criminale. Ora adempila!","Hai già una missione per cercare un criminale! Sto aspettando i risultati!","Mentre tu stai perdendo il tuo tempo nella mia residenza, quel lurido furfante continua a navigare! Prosegui immediatamente con la missione che ti è stata affidata!");
							link.l1 = RandPhraseSimple("Bene, "+GetAddress_FormToNPC(NPChar)+".","Sono occupato con questo, "+GetAddress_FormToNPC(NPChar)+".");
							link.l1.go = "exit";		
						break;
						case "Late":
							dialog.text = RandPhraseSimple("Il tempo dato a te per localizzare quel mascalzone è finito. E che tipo di rapporti sto ricevendo, come pensi? E ti dirò - è arrivato con successo a destinazione e poi è sparito nel nulla! Ora degnati di spiegarti, "+GetAddress_Form(NPChar)+".","Tutti i termini dati a te per trovare il criminale, sono scaduti. Eppure, non si è fatto alcun progresso. Cosa succede?");
							link.l1 = "Non sono riuscito a eseguire il vostro compito nel tempo predetto, "+GetAddress_FormToNPC(NPChar)+".";
							link.l1.go = "All_Late";		
						break;
						case "Found":
							dialog.text = RandPhraseSimple("Allora, cosa ne dici? Hai catturato il malfattore?","Dimmi solo una cosa - quel sudicio mascalzone è nella tua stiva, imbavagliato e incatenato?");
							link.l1 = "Sfortunatamente, no, "+GetAddress_FormToNPC(NPChar)+". Non sono riuscito a catturare il malfattore. È affondato con la nave su cui si trovava.";
							link.l1.go = "All_Found";		
						break;
						case "Execute":
							dialog.text = RandPhraseSimple("Allora, cosa ne dici? Hai catturato il malfattore?","Ditemi solo una cosa - quel sudicio furfante è nella vostra stiva, imbavagliato e ammanettato?");
							link.l1 = "Sì, "+GetAddress_FormToNPC(NPChar)+". Per favore, manda i tuoi soldati al molo, e io te lo consegnerò.";
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
							dialog.text = LinkRandPhrase("Una missione per cercare i contrabbandieri ti è già stata affidata. Ora adempila!","Hai già una missione per cercare i contrabbandieri! Sto aspettando i risultati!","Mentre tu stai perdendo tempo nella mia residenza, quei contrabbandieri si stanno preparando a concludere un altro affare! Procedi immediatamente con la missione che ti è stata affidata!");
							link.l1 = RandPhraseSimple("Bene, "+GetAddress_FormToNPC(NPChar)+".","Sono occupato con questo, "+GetAddress_FormToNPC(NPChar)+".");
							link.l1.go = "exit";		
						break;
						case "Late":
							dialog.text = RandPhraseSimple("Il tempo assegnato per localizzare i contrabbandieri è finito. E che tipo di rapporti credi che sto ricevendo? E te lo dirò - hanno venduto con gioia tutte le loro merci! Ora degnati di spiegarti, "+GetAddress_Form(NPChar)+".","Tutti i termini dati a te per trovare i contrabbandieri, sono scaduti. Eppure, non è stato fatto alcun progresso. Che succede?");
							link.l1 = "Non sono riuscito a eseguire il tuo incarico in tempo, "+GetAddress_FormToNPC(NPChar)+".";
							link.l1.go = "All_Late";		
						break;
						case "Found":
							dialog.text = RandPhraseSimple("Allora, cosa ne dici? Hai affrontato i contrabbandieri?","Dimmi solo una cosa - hai rovinato l'affare di quei contrabbandieri?");
							link.l1 = "Sfortunatamente, no, "+GetAddress_FormToNPC(NPChar)+". Non sono riuscito a sventare i piani di quei mascalzoni.";
							link.l1.go = "All_Found";		
						break;
						case "Execute":
							dialog.text = RandPhraseSimple("Allora, che dici? Hai sistemato i contrabbandieri?","Dimmi solo una cosa - hai rovinato l'affare di quei contrabbandieri?");
							link.l1 = "Sì, "+GetAddress_FormToNPC(NPChar)+". Li ho raggiunti ed eliminato le navi di entrambe le parti, compratore e venditore allo stesso modo.";
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
							dialog.text = LinkRandPhrase("Ti è già stata assegnata una missione per cercare il disertore. Ora adempila!","Hai già una missione per cercare il disertore! Sto aspettando i risultati!","Mentre stai perdendo tempo nella mia residenza, quel disertore potrebbe tradire i nostri segreti di Stato! Prosegui immediatamente con la missione che ti è stata affidata!");
							link.l1 = RandPhraseSimple("Bene, "+GetAddress_FormToNPC(NPChar)+".","Sono occupato con questo, "+GetAddress_FormToNPC(NPChar)+".");
							link.l1.go = "exit";		
						break;
						case "Late":
							dialog.text = RandPhraseSimple("Il tempo che ti è stato dato per localizzare il disertore è finito. E che tipo di rapporti sto ricevendo, secondo te? E ti dirò - nessun risultato, proprio nessuno! Ora degnati di spiegarti, "+GetAddress_Form(NPChar)+".","Tutti i termini dati a te per trovare il disertore, sono scaduti. Eppure, non si è fatto alcun progresso. Che succede?");
							link.l1 = "Non sono riuscito a svolgere il tuo lavoro in tempo, "+GetAddress_FormToNPC(NPChar)+".";
							link.l1.go = "All_Late";		
						break;
						case "Found":
							dialog.text = RandPhraseSimple("Allora, cosa dici? Hai catturato il disertore?","Dimmi solo una cosa - quel disertore è nella tua stiva, imbavagliato e ammanettato?");
							link.l1 = "Sfortunatamente, no, "+GetAddress_FormToNPC(NPChar)+". Non sono riuscito a catturare quel mascalzone. Ho trovato la sua traccia nel insediamento di "+XI_ConvertString("Colony"+pchar.GenQuest.FindFugitive.City)+", ma proprio il giorno prima del mio arrivo è partito verso sud su una nave pirata. Immagino che ora sia con quei signori della fortuna.";
							link.l1.go = "All_Found";		
						break;
						case "Execute":
							dialog.text = RandPhraseSimple("Oh beh... Ecco il nostro "+pchar.GenQuest.FindFugitive.Name+"... Ottimo lavoro, capitano! Hai avuto difficoltà nella ricerca?","Oh, che ospiti abbiamo! Ciao, "+pchar.GenQuest.FindFugitive.Name+"! Ottimo lavoro, capitano! Hai speso molto impegno nella tua ricerca?");
							link.l1 = "Come dire, "+GetAddress_FormToNPC(NPChar)+". Qualunque cosa fosse - la tua missione è stata compiuta.";
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
								dialog.text = RandPhraseSimple("Il tempo a tua disposizione per consegnare la lettera è finito. E presumo che tu abbia fallito.","È scaduto il tempo. Eppure, non si è fatto alcun progresso. Che succede?");
								link.l1 = "Non sono riuscito a svolgere il vostro lavoro, "+GetAddress_FormToNPC(NPChar)+".";
								link.l1.go = "All_Late";	
							}
							else
							{
								dialog.text = LinkRandPhrase("Ti è già stata affidata una missione per consegnarmi una lettera. Ora adempila!","Hai già una missione per consegnarmi una lettera direttamente! Sto aspettando i risultati, ho bisogno di quella lettera il più presto possibile!","Mentre tu sprechi il tuo tempo nella mia residenza, le informazioni di cui ho disperatamente bisogno sono ancora nelle mani della persona che dovrebbe inviarmele! Prosegui immediatamente con la missione che ti è stata affidata!");
								link.l1 = RandPhraseSimple("Bene, "+GetAddress_FormToNPC(NPChar)+".","Mi metterò al lavoro subito, "+GetAddress_FormToNPC(NPChar)+".");
								link.l1.go = "exit";	
							}
						break;
						case "Execute":
							dialog.text = RandPhraseSimple("Hai consegnato la lettera che sto aspettando?","Dimmi adesso - ce l'hai?!");
							link.l1 = "Sì, l'ho fatto. Come abbiamo concordato - consegnato a te, personalmente.";
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
				dialog.text = "Purtroppo, oggi non ho un lavoro per te. L'ultimo è stato fatto da "+GetFullName(&Characters[i])+". Vieni domani, forse apparirà qualcosa.";
				link.l1 = "Oh, dannazione! Nessuna fortuna...";
				link.l1.go = "exit";
				break;
			}
//navy <--
			if (!CheckAttribute(npchar, "work_date") || GetNpcQuestPastDayParam(npchar, "work_date") > 2 || bBettaTestMode)
    		{	
				SaveCurrentNpcQuestDateParam(npchar, "work_date");
				if(CheckAttribute(pchar, "questTemp.StatusCity") && pchar.questTemp.StatusCity == npchar.city)
				{
					dialog.text = "Sei arrivato proprio in tempo, capitano. Devo affrontare un problema urgente legato al contrabbando di merci nella nostra colonia. Suppongo che la tua nave sia in grado di navigare e pronta per la battaglia.";
					link.l1 = "La mia nave è sempre pronta per il mare e per la battaglia. Per favore, mi dica di più sulla prossima missione, vostra grazia.";
					link.l1.go = "CustomPatrol";
					break;
				}
				if (rand(5) > 4 && !bBettaTestMode && pchar.location == "Panama_townhall") // patch-5
				{
					dialog.text = LinkRandPhrase("Per ora non ho lavoro per te. Vieni domani, suppongo...","Purtroppo, non ho lavoro per te oggi. Per favore, torna tra un giorno o due.","Oggi non c'è nulla che potrei proporti. Sarò lieto di vederti un altro giorno.");
					link.l1 = "Capisco, "+GetAddress_FormToNPC(NPChar)+".";
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
                            sTemp = ", which is on " + XI_ConvertString(colonies[FindColony(pchar.GenQuest.Intelligence.City)].islandLable+"Dat");                         
							dialog.text = "Ho una missione per te, che comporta seri rischi. Ho bisogno che tu ti intrufoli in "+XI_ConvertString("Colony"+pchar.GenQuest.Intelligence.City+"Acc")+sTemp+", incontra una certa persona là e poi consegnami quello che ti avrebbe dato.";
							link.l1 = "Mmm, non penso che in "+XI_ConvertString("Colony"+pchar.GenQuest.Intelligence.City+"Dat")+" Sarò un ospite gradito...";
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
							dialog.text = "Proprio ora ho una missione per te. Nella giungla vicino "+XI_ConvertString("Colony"+npchar.city+"Gen")+" è apparso un gruppo di ladri, e so che il capo si chiama "+GetFullName(arName)+". Trova ed elimina questa banda di teppisti.";
							link.l1 = "Sono in qualche modo limitato nei termini?";
							link.l1.go = "DestroyGang";
						break;
						
						//========== контркурьер - отобрать почту ============
						case 2:
							dialog.text = "Sì, ho una missione per te. Per completarla, dovrai dimostrare rapidità e anche un certo talento nel combattimento navale. Sei pronto a dimostrare il tuo valore?";
							link.l1 = "Vostra Grazia, potete rivelare più dettagli sulla missione?";
							link.l1.go = "TakePostcureer";
						break;
						
						//========== контрфрахт - потопить корабль с боеприпасами ============
						case 3:
							dialog.text = "Sì, ho una missione per te. Per portarla a termine, dovrai dimostrare un coraggio eccezionale e anche un certo talento nel combattimento navale. Sei pronto a dimostrare il tuo valore?";
							link.l1 = "Sua Grazia, può rivelare ulteriori dettagli sulla missione imminente?";
							link.l1.go = "TakeArsenalship";
						break;
						//========== ОЗГ - охотник на пирата ============
						case 4:
							dialog.text = "Sì, ho una missione importante per te. Per compierla, dovrai usare tutte le tue abilità. Questo coinvolge i pirati...";
							link.l1 = "Pirati? Potresti dirmi più dettagliatamente cosa si aspettano da me, allora?";
							link.l1.go = "TakePirateship";
						break;
						//========== ОЗГ - охотник на пассажира ============
						case 5:
							dialog.text = "Arrivate proprio in tempo, signore. Ho una missione urgente, che vi si addice perfettamente. Implica cercare e catturare una certa persona...";
							link.l1 = "Una caccia all'uomo? Potresti dirmi più dettagliatamente cosa si aspetta da me?";
							link.l1.go = "TakePassenger";
						break;
						//========== Патруль - таможенник ============
						case 6:
							dialog.text = "Sei arrivato proprio in tempo, capitano. Devo affrontare un problema urgente legato al contrabbando di merci nella nostra colonia. Immagino che la tua nave sia in grado di navigare e pronta per la battaglia?";
							link.l1 = "La mia nave è sempre pronta a navigare e pronta per la battaglia. Per favore, raccontami di più sulla missione imminente, vostra grazia.";
							link.l1.go = "CustomPatrol";
						break;
							//========== Найти дезертира ============
						case 7:
							dialog.text = "Ho una missione per te che comporta la visita di diverse insediamenti nei Caraibi. Sei pronto per un lungo viaggio?";
							link.l1 = "Sì, i miei uomini ed io siamo pronti a partire subito. Cosa dovrò fare esattamente?";
							link.l1.go = "FindFugitive";
						break;
					}
				}
			}
			else
			{
				dialog.text = LinkRandPhrase("Oggi non posso offrirti nessun lavoro.","Oggi non ci sono più lavori per te.","Non ci sono più lavori per oggi, mi dispiace. Torna domani, e vedremo...");
				link.l1 = RandPhraseSimple("Peccato...","Ah, che peccato, "+GetAddress_FormToNPC(NPChar)+". ");
        		link.l1.go = "exit";
			}
		//---------------------------- генератор квестов мэра -------------------------------
		break;

		case "sell_prisoner":
            dialog.text = "Chi vorresti riscattare?";

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
			link.l99 = "Nessuno.";
			link.l99.go = "exit";
		break;
		
		case "sell_prisoner_2":
            offref = GetCharacter(sti(pchar.GenQuest.GetPrisonerIdx));
            attrLoc =  "So, this is captain " + GetFullName(offref) + ", " + NationNameMan(sti(offref.nation))+ ".";
            // цена зависит от губернатора
            qty = makeint(sti(offref.rank)*(800 + GetCharacterSPECIALSimple(NPChar, SPECIAL_L)*100) + GetCharacterSkillToOld(offref, "Leadership")*500 + GetCharacterSkillToOld(pchar, "commerce")*500);
			if(HasShipTrait(pchar, "trait14")) qty = makeint(qty * 1.35);
            if (sti(offref.nation) == sti(NPChar.nation))
            {
                attrLoc = attrLoc + " I am ready to pay the ransom for my compatriot in the amount of  " + FindRussianMoneyString(qty) + ".";
            }
            else
            {
                if (sti(offref.nation) == PIRATE)
                {
                    qty = qty / 5;
                    attrLoc = attrLoc + " I can give " + FindRussianMoneyString(qty) + "  for this gallowsbird. And then we'll execute the scoundrel at once.";

                }
                else
                {
                    qty = qty / 2;
                    attrLoc = attrLoc + " " + FindRussianMoneyString(qty) + "for that man, not a peso more.";
                }
            }
			dialog.text = attrLoc;
			pchar.PrisonerSellPrice =  qty;
			link.l1 = "Affare fatto. È tutto tuo, "+GetAddress_FormToNPC(NPChar)+".";
			link.l1.go = "sell_prisoner_3";
			link.l3 = "No. Non va bene.";
			link.l3.go = "exit";
		break;


		case "sell_prisoner_3":
			dialog.text = "Questo è buono.";
			link.l1 = "Tutto il meglio.";
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
                dialog.Text = "Arrgh! Che è questa oltraggio, de Maure? Da quando i francesi attaccano i loro stessi compatrioti?!";
                Link.l1 = "Per ordine del Governatore Generale Francois Longvillier de Poincy, tu, Monsieur Levasseur, sei rimosso dal tuo incarico di governatore di Tortuga e condannato a morte! E sarò io a eseguire questa sentenza!";
                Link.l1.go = "levasser";
				break;
			}
			// <-- Левассер
            // fix от грабежа 5 раз на дню -->
            if (!CheckNPCQuestDate(npchar, "GrabbingTownDate"))
			{
                dialog.Text = "Hai già preso tutto. Di cosa hai ancora bisogno?";
                Link.l1 = "Sì, certo, città sbagliata.";
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
                dialog.Text = "Insolenza senza precedenti! Presto arriveranno i rinforzi dal forte e pagherai per questo!";
                Link.l2 = "Non starò qui ad aspettare il loro arrivo. Pagami, e lasceremo questa città.";
                Link.l2.go = "Summ";
                Pchar.HalfOfPaymentByCity = true; // токо половина денег
            }
            else
            {
				dialog.Text = "Hai vinto questa volta, ma sappi che uno squadrone dei nostri cacciatori di pirati ti darà la caccia e strapperà ogni peso dalla tua sporca carne di pirata!";
	            if (!bWorldAlivePause || bBettaTestMode)
	            {
	                int iColony = FindColony(npchar.city);
					if (!CheckAttribute(&colonies[iColony], "notCaptured")) //незахватываемые города
					{
						if (CheckAttribute(FortChref, "Default.Prison"))
	    				{
	    					Link.l1 = "Silence! This town belongs to me from now on; as for your piratehunters - I'll send them straight to Davy Jones' Locker. Hey lads, grab this pig and put it behind bars.";
	    				}
	    				else
	    				{
	    					Link.l1 = "Questa città ora appartiene a me. Ragazzi, accompagnate l'ex-governatore ai suoi nuovi 'quartieri', eheh.";
	    				}
	    				Link.l1.go = "City";
					}
				}
				if (!isCityHasFort(NPChar.City))
	            {
	                Link.l2 = "Rinforzi dal forte? Basta pagarmi un bel riscatto, e lasceremo la tua città.";
				}
				else
				{
	            	Link.l2 = "Uno squadrone di cacciatori di pirati? Hmm ... Basta pagarmi e lasceremo la tua città.";
	            }
				Link.l2.go = "Summ";

                bOk = !bWorldAlivePause || bBettaTestMode;
	            if (isMainCharacterPatented() && bOk && !CheckAttribute(&colonies[iColony], "notCaptured")) //не даем захватить колонию
	            {
					// восстановим нацию патента
					PChar.nation = GetBaseHeroNation();
					
					dialog.Text = "Insolenza senza precedenti! Come osi attaccare la colonia appartenente a "+NationNameGenitive(sti(NPChar.nation))+"?! Pagherai caro per il sangue che hai versato e per i danni che hai inflitto al nostro stato.";
	                Link.l1 = "Da questo momento in poi, questa colonia appartiene a me. Chiunque decida di contestare la mia autorità va dritto all'inferno.";
	                Link.l1.go = "City_patent";
	                Link.l2 = "Calma. Io agisco nel nome di "+NationNameGenitive(sti(PChar.nation))+". Da questo punto in poi questa colonia appartiene a "+NationKingsCrown(PChar)+"!";
	                Link.l2.go = "City_nation";
	                Link.l3 = "Bella città che avete qui. Sarebbe una vera tragedia se fosse bruciata fino a diventare cenere e il suo governatore impiccato nella piazza della città. Dovremmo discutere l'ammontare del riscatto che siete disposti a pagare per prevenire tale tragedia.";
	                Link.l3.go = "Summ_patent";
	            }
            }
        break;
		
		// --> Левассер
		case "levasser":
            dialog.Text = "Poincy?! Dannazione, quel bastardo papista! Me ne occuperò... e tu sei spacciato, mascalzone! Non uscirai vivo da qui - ti finirò personalmente!";
			Link.l1 = "Risparmiati le tue prediche, eretico. Quando manderò la tua anima Ugonotta all'inferno, dai i miei migliori auguri a Lucifero e Jean Calvin. In guardia!";
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
            Log_Info("All ships have been repaired.");
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
            dialog.Text = "Hai vinto questa volta, ma sappi che il nostro squadrone arriverà presto e non lascerà nulla di te!";
			Link.l1 = "Shut your mouth. This town belongs to me from now on; as for your squadron - I'll send it straight to Hell. Boys, escort the ex-governor to his new 'quarters', heh heh.";
			Link.l1.go = "City";
        break;

        case "Exit_for_pay":
			dialog.Text = "Di che altro hai bisogno da me?";
            Link.l1 = "Solo sto controllando se mi è sfuggito qualcosa...";
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
            dialog.Text = "Non ho altra scelta se non accettare le vostre condizioni. Prendete i vostri maledetti soldi e lasciate subito la nostra colonia.";
            Link.l1 = "Un piacere fare affari con te.";
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
            dialog.Text = "Bene, dichiara le tue condizioni...";
            Link.l1 = "Sì, vae victis! Inizia a contare i tuoi soldi.";
            Link.l1.go = "Summ";
            ChangeCharacterComplexReputation(GetMainCharacter(),"nobility", -10); // не на службе
        break;

        case "City_nation":
			dialog.Text = "Bene, ci arrendiamo alla tua misericordia.";
			Link.l1 = "Ti consiglierei di lasciare la città il prima possibile - i cambiamenti imminenti potrebbero essere molto dannosi per la tua salute. Addio.";
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
			dialog.Text = "Cosa altro vuoi da me, mascalzone?";
            Link.l3 = "Come si trova Sua Eccellenza nella sua nuova stanza? Abbastanza spaziosa? Bene, ora devo andare!";
            Link.l3.go = "exit";
            NextDiag.TempNode = "Prison";
		break;
		
		case "arestFree_1":
			dialog.text = "Risolvere? E come te lo immagini?";
            link.l1 = "Credo che una somma di "+iTotalTemp*6000+" i pesos possono ancora salvarmi, non è vero?";
			link.l1.go = "arestFree_2";
			link.l2 = "No. Ed è ora per me di andare. I miei migliori saluti.";
			link.l2.go = "arest_1";
		break;

		case "arestFree_2":
            if (GetCharacterSkillToOld(PChar, SKILL_FORTUNE) >= hrand(7) && iTotalTemp < 21)
            {
    			dialog.text = "Immagino che potremmo risolvere il nostro incidente in questo modo. Non sei ancora andato così lontano da rendere la situazione irreparabile.";
    		    link.l1 = "Eccellente. Sono molto contento. Per favore, accetta la mia donazione.";
    		    link.l1.go = "Exit";
    		    AddMoneyToCharacter(pchar, -iTotalTemp*6000);
    		    ChangeCharacterHunterScore(Pchar, NationShortName(sti(NPChar.nation)) + "hunter", -iTotalTemp);
    		    AddCharacterExpToSkill(pchar, "Fortune", 100);
            }
            else
            {
    			dialog.text = "Mi stai offrendo una tangente? Oh no! I tuoi malvagi misfatti possono essere espiati in un solo modo... Guardie! Mettete "+GetSexPhrase("lui","lei")+" in catene!";
    		    link.l1 = "Aspetta!";
    		    link.l1.go = "arest_2";
    		    AddCharacterExpToSkill(pchar, "Fortune", 10);
            }
		break;

		case "arest_1":
			dialog.text = "Certo, è ora. Ti accompagneremo. Guardie! Prendete "+GetSexPhrase("lui","lei")+"!";
		    link.l1 = "Assolutamente no!";
		    link.l1.go = "fight";
		break;

		case "arest_2":
			dialog.text = "Hai avuto tutto il tempo per pensare! Guardie!";
			link.l1 = "Non mi prenderai facilmente!";
		    link.l1.go = "fight";
		break;    
		/////////////////////////////////////////////////////////////////////////////////////////////////
		//	Уничтожение банды
		/////////////////////////////////////////////////////////////////////////////////////////////////
		case "DestroyGang":
			dialog.text = "Certo. Per realizzare questa missione, ti sto dando "+FindRussianDaysString(sti(pchar.GenQuest.DestroyGang.Terms))+", e la tua ricompensa in caso di successo sarà "+FindRussianMoneyString(sti(pchar.GenQuest.DestroyGang.Money))+".";
			link.l1 = "Sì, accetto questo compito.";
		    link.l1.go = "DestroyGang_agree";
			link.l2 = "Uhm... No, penso che rifiuterò.";
		    link.l2.go = "All_disagree";
		break;
		case "DestroyGang_agree":
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_complete";
			pchar.GenQuest.questName = "DestroyGang"; //тип квеста
			pchar.GenQuest.DestroyGang.Location = GetGangLocation(npchar); //определяем локацию,где банда
			pchar.GenQuest.DestroyGang.MayorId  = npchar.id; //Id мэра, чтобы знать, кто дал квест
			if (pchar.GenQuest.DestroyGang.Location == "none") //на всякий случай
			{
				dialog.text = "Aspetta, ho appena dimenticato il rapporto di ieri. Il punto è che questa banda ha già lasciato la nostra isola. Quindi devo annullare la missione.";
				link.l1 = "Capisco. Un peccato.";
				link.l1.go = "exit";
				DeleteAttribute(pchar, "GenQuest." + pchar.GenQuest.questName);
				DeleteAttribute(pchar, "GenQuest.questName");
			}
			else
			{
				dialog.text = "Bene, ottimo! Ti aspetterò nella mia residenza per te e i tuoi rapporti.";
				link.l1 = "Non ti farò aspettare a lungo, "+GetAddress_FormToNPC(NPChar)+".";
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
				dialog.text = LinkRandPhrase("Oggi non posso offrirti nessun lavoro.","Oggi non ci sono più lavori per te.","Non ci sono più lavori per oggi, mi dispiace. Torna domani, vedremo...");
				link.l1 = RandPhraseSimple("Peccato...","Ah, che peccato, "+GetAddress_FormToNPC(NPChar)+". ");
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
			pchar.GenQuest.TakePostcureer.Money = ((hrand(5)+hrand(6)+4)*2000)+(sti(pchar.rank)*500);
			dialog.text = "Certo. Dovrai localizzare una nave corriere di "+NationNameGenitive(sti(pchar.GenQuest.TakePostcureer.Nation))+" con il nome di '"+pchar.GenQuest.TakePostcureer.ShipName+"', sali a bordo e portami i documenti, che dovresti essere in grado di trovare nella cabina del capitano. Questa nave passerà vicino "+XI_ConvertString("Colony"+pchar.GenQuest.TakePostcureer.City+"Gen")+" all'incirca in "+FindRussianDaysString(pchar.GenQuest.TakePostcureer.Terms)+".";
			link.l1 = "Bene, accetto questa missione. E che tipo di documenti dovrei cercare?";
		    link.l1.go = "TakePostcureer_agree";
			link.l2 = "Mmm... No, penso di passare.";
		    link.l2.go = "All_disagree";
		break;
		
		case "TakePostcureer_agree":
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_complete";
			pchar.GenQuest.TakePostcureer.MayorId  = npchar.id; //Id мэра, чтобы знать, кто дал квест
			dialog.text = "Posta. Ci sono documenti molto importanti per me. Ma non c'è bisogno che tu cerchi tra i documenti, basta che mi porti tutto il pacco. Ti pagherò "+FindRussianMoneyString(sti(pchar.GenQuest.TakePostcureer.Money))+"\nQuindi, ti aspetterò e il risultato del tuo lavoro nella mia residenza.";
			link.l1 = "Non ti farò aspettare a lungo, "+GetAddress_FormToNPC(NPChar)+".";
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
				dialog.text = LinkRandPhrase("Oggi non posso offrirti nessun lavoro.","Oggi non ci sono più lavori per te.","Non ci sono più lavori per oggi, mi dispiace. Torna domani, e vedremo...");
				link.l1 = RandPhraseSimple("Peccato...","Ah, che peccato, "+GetAddress_FormToNPC(NPChar)+". ");
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
			pchar.GenQuest.TakeArsenalship.Money = ((hrand(5)+hrand(6)+4)*1800)+(sti(pchar.rank)*500);
			dialog.text = "Certo. Dovrai localizzare un trasporto militare di "+NationNameGenitive(sti(pchar.GenQuest.TakeArsenalship.Nation))+", with gunpowder and ammunition on board; the name of the vessel is '"+pchar.GenQuest.TakeArsenalship.ShipName+"', find and destroy it. We'll weaken our enemy by doing that\nThe transport will sail with an escort to the colony "+XI_ConvertString("Colony"+pchar.GenQuest.TakeArsenalship.City)+", and will be approximately in "+FindRussianDaysString(pchar.GenQuest.TakeArsenalship.Terms)+", so you should hurry.";
			link.l1 = "Va bene, accetto. Devo affondare la nave dell'arsenale o dovrei tentare di catturarla?";
		    link.l1.go = "TakeArsenalship_agree";
			link.l2 = "Mmm... No, penso che passerò.";
		    link.l2.go = "All_disagree";
		break;
		
		case "TakeArsenalship_agree":
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_complete";
			pchar.GenQuest.TakeArsenalship.MayorId  = npchar.id; //Id мэра, чтобы знать, кто дал квест
			dialog.text = "Non me ne importa, sta a te. La cosa importante è che questo carico non deve raggiungere la sua destinazione. Se ci riesci, ti pagherò "+FindRussianMoneyString(sti(pchar.GenQuest.TakeArsenalship.Money))+"... Non ti ritardo più, capitano.";
			link.l1 = "Non ti farò aspettare a lungo, "+GetAddress_FormToNPC(NPChar)+".";
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
			pchar.GenQuest.TakePirateship.Money = ((hrand(5)+hrand(6)+4)*2400)+(sti(pchar.rank)*500);
			dialog.text = "Certo. Sono davvero infastidito dalle attività di un capitano pirata, il cui nome è "+pchar.GenQuest.TakePirateship.Name+". Quel mascalzone ha preso l'abitudine di saccheggiare i nostri mercanti, cosa che danneggia enormemente il commercio tra le colonie. Ora è il momento perfetto per sbarazzarsi di quel bastardo, perché per caso so dove si nasconde al momento. Sei pronto a mandare questo figlio di puttana al Giudizio di Dio?";
			link.l1 = "Sarebbe un onore! Dove posso trovare questo pirata?";
		    link.l1.go = "TakePirateship_agree";
			link.l2 = "Uhm... No, penso che passerò.";
		    link.l2.go = "All_disagree";
		break;
		
		case "TakePirateship_agree":
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_complete";
			pchar.GenQuest.TakePirateship.MayorId  = npchar.id; //Id мэра, чтобы знать, кто дал квест
			dialog.text = "Nel più vicino "+FindRussianDaysString(pchar.GenQuest.TakePirateship.Terms)+" la sua nave con il nome di '"+pchar.GenQuest.TakePirateship.ShipName+"' sarà in crociera nei pressi delle coste "+XI_ConvertString("Colony"+pchar.GenQuest.TakePirateship.City+"Gen")+". Trovalo e uccidilo. Mandalo a nutrire i pesci con la nave, prendi la nave - non mi importa. L'unica cosa che mi importa è che quel maledetto pirata smetterà di contaminare il nostro mare con la sua presenza\nPer questo compito sono disposto a pagarti "+FindRussianMoneyString(sti(pchar.GenQuest.TakePirateship.Money))+". Non perdere tempo, capitano: questo mascalzone non ti aspetterà a "+XI_ConvertString("Colony"+pchar.GenQuest.TakePirateship.City+"Gen")+". Vai, e che Dio ti aiuti!";
			link.l1 = "Già alzando l'ancora, "+GetAddress_FormToNPC(NPChar)+"! Non dovrai aspettare a lungo.";
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
				dialog.text = LinkRandPhrase("Oggi non posso offrirti alcun incarico.","Oggi non ci sono più lavori per te.","Non ci sono più lavori per oggi, mi dispiace. Torna domani, e vedremo...");
				link.l1 = RandPhraseSimple("Peccato...","Ah, che peccato, "+GetAddress_FormToNPC(NPChar)+". ");
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
			pchar.GenQuest.TakePassenger.Money = ((hrand(5)+hrand(6)+4)*2200)+(sti(pchar.rank)*500);
			string sText = SelectPassText();
			dialog.text = "Certo. Sto parlando di un mascalzone di nome "+pchar.GenQuest.TakePassenger.Name+". "+sText+"Lo stavo cercando da molto tempo, e ora ho finalmente ottenuto informazioni affidabili, dove può essere trovato. Ho bisogno che tu mi porti quell'uomo, per tutti i mezzi vivo. Voglio impiccarlo in pubblico nella nostra piazza della città. Sei pronto a intraprendere questa missione?";
			link.l1 = "Sono pronto, "+GetAddress_FormToNPC(NPChar)+". Dove posso trovare quel mascalzone?";
		    link.l1.go = "TakePassenger_agree";
			link.l2 = "Mmm... No, credo che passerò.";
		    link.l2.go = "All_disagree";
		break;
		
		case "TakePassenger_agree":
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_complete";
			pchar.GenQuest.TakePassenger.MayorId  = npchar.id; //Id мэра, чтобы знать, кто дал квест
			dialog.text = "Appena in "+FindRussianDaysString(pchar.GenQuest.TakePassenger.Terms1)+", lui, come un passeggero su una nave di nome '"+pchar.GenQuest.TakePassenger.ShipName+"', salperà da "+XI_ConvertString("Colony"+pchar.GenQuest.TakePassenger.City+"Gen")+" e vai a "+XI_ConvertString("Colony"+pchar.GenQuest.TakePassenger.CityA+"Acc")+". Hai "+FindRussianDaysString(pchar.GenQuest.TakePassenger.Terms)+" per trovare questa nave sul segmento di percorso specificato, sali a bordo e sequestra quel bastardo. Se segui questa istruzione, ti pagherò "+FindRussianMoneyString(sti(pchar.GenQuest.TakePassenger.Money))+". Buona fortuna a te, capitano!";
			link.l1 = "Non sprecherò più tempo, "+GetAddress_FormToNPC(NPChar)+"! Metterò subito le vele.";
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
			pchar.GenQuest.CustomPatrol.Money = ((hrand(5)+hrand(6)+4)*1400)+(sti(pchar.rank)*300);
			dialog.text = "Ho informazioni affidabili che un certo capitano ha organizzato una transazione con dei contrabbandieri per la vendita di alcuni schiavi. Come dovrebbe essere noto a te, tali transazioni da parte di privati nelle nostre colonie sono considerate come merci di contrabbando\nIl problema è che non conosco né l'orario esatto, né la data né il luogo, dove i contrabbandieri si incontreranno. Si sa solo che una transazione criminale sarà compiuta durante i prossimi cinque giorni sulla nostra isola. Per peggiorare le cose, tutte le mie navi di pattuglia sono o in riparazione o impegnate per altri compiti e non possono trovare questi furfanti\nTi suggerisco di occuparti di questo compito - rintracciare i contrabbandieri e occuparti di loro con i metodi più radicali, farne un esempio. Sei pronto ad affrontare questa missione?";
			link.l1 = "Sono pronto, "+GetAddress_FormToNPC(NPChar)+". Dimmi, hai ulteriori informazioni? Come il nome del capitano, il nome o il tipo della sua nave?";
		    link.l1.go = "CustomPatrol_agree";
			link.l2 = "Hmm... No, penso che passerò.";
		    link.l2.go = "All_disagree";
		break;
		
		case "CustomPatrol_agree":
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_complete";
			pchar.GenQuest.CustomPatrol.MayorId  = npchar.id; //Id мэра, чтобы знать, кто дал квест
			dialog.text = "La mia fonte mi ha appena detto che si sta preparando un accordo che sarà completato. È tutto. Quindi basta dare un'occhiata più da vicino a tutte le navi sospette nelle nostre acque. Se avrai successo, ti pagherò una somma di "+FindRussianMoneyString(sti(pchar.GenQuest.CustomPatrol.Money))+"\nInoltre, date le circostanze, ti autorizzo a raccogliere tutto il carico di contrabbando che puoi trovare. Non ufficialmente, ovviamente, a condizione che non lo vendi nella nostra città.";
			link.l1 = "Molto generoso. Bene, mi metterò a pattugliare le acque della vostra colonia, "+GetAddress_FormToNPC(NPChar)+".";
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
			pchar.GenQuest.FindFugitive.Money = ((hrand(5)+hrand(6)+4)*2600)+(sti(pchar.rank)*600);
			sText = SelectFugitiveText();
			log_testinfo(pchar.GenQuest.FindFugitive.City);
			log_testinfo(FindRussianDaysString(sti(pchar.GenQuest.FindFugitive.Chance)));
			dialog.text = "Ti racconterò tutto nei dettagli. Si è verificato un fatto molto brutto - "+sText+". Intervistando i suoi colleghi e amici, crediamo, non senza motivo, che il disertore si sia rifugiato tra i pirati in uno dei loro insediamenti\nTi suggerisco di visitare il nido dei pirati, trovare il fuggitivo, arrestarlo e consegnarlo qui. La diserzione è un grave reato, e non può rimanere impunita. Sei pronto a prendere questa missione?";
			link.l1 = "Sono pronto, "+GetAddress_FormToNPC(NPChar)+". Puoi dirmi il nome del disertore?";
		    link.l1.go = "FindFugitive_agree";
			link.l2 = "Mmm... No, penso che rifiuterò.";
		    link.l2.go = "All_disagree";
		break;
		
		case "FindFugitive_agree":
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_complete";
			pchar.GenQuest.FindFugitive.MayorId  = npchar.id; //Id мэра, чтобы знать, кто дал квест
			dialog.text = "Sì, certo. Il suo nome è "+pchar.GenQuest.FindFugitive.Name+". Dubito molto che indosserà la sua uniforme, quindi dai un'occhiata più da vicino a ogni sorta di feccia. Ti do un mese per la ricerca, perché, temo, non avrebbe senso cercarlo dopo. Se riesci, ti pagherò una somma di "+FindRussianMoneyString(sti(pchar.GenQuest.FindFugitive.Money))+".";
			link.l1 = "Non sprecherò più tempo, "+GetAddress_FormToNPC(NPChar)+"! Salperò immediatamente.";
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
			dialog.text = "Capisco. Forse, una ricompensa di "+FindRussianMoneyString(sti(pchar.GenQuest.Intelligence.Money))+" sarà un buon incentivo per te.";
			link.l1 = "Sì, sono soldi decenti... Accetterò questa missione.";
		    link.l1.go = "Intelligence_agree";
			link.l2 = "Mmm... No, credo che rifiuterò. È troppo pericoloso.";
		    link.l2.go = "All_disagree";
		break;
		case "Intelligence_agree":
			if (pchar.GenQuest.Intelligence.City == "none" || isBadReputation(pchar, 30)) //на всякий случай
			{
				dialog.text = "Sebbene, non posso dire che posso fidarmi completamente di te... penso che non ti darò questa missione.";
				link.l1 = "Oh bene... È un peccato, ma non c'è nulla che io possa fare.";
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
				dialog.text = "Ottimo! Ora passiamo agli affari. In "+XI_ConvertString("Colony"+pchar.GenQuest.Intelligence.City+"Dat")+"devi trovare un locale"+GetWorkTypeOfMan(&characters[GetCharacterIndex(sTemp)],"Gen")+", il suo nome è "+GetFullName(&characters[GetCharacterIndex(sTemp)])+". Dirai a lui il mio nome e lui ti darà un pacchetto di documenti. Per consegnare questo pacchetto nelle mie mani ti do "+FindRussianDaysString(sti(pchar.GenQuest.Intelligence.Terms))+". E ricorda che tutto deve essere fatto in segreto. Se la tua copertura viene compromessa, l'agente non rischierà di tentare di prendere contatto. È chiaro?";
				link.l1 = "Sì, ho capito, "+GetAddress_FormToNPC(NPChar)+". Comincerò immediatamente.";
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
			dialog.text = RandPhraseSimple("Non male. Ma non hai rispettato la scadenza, quindi devo ridurre un po' la tua ricompensa. Ora il tuo compenso sarà "+FindRussianMoneyString(sti(pchar.GenQuest.(QuestName).Money))+". Ecco a te.","Va bene. Ma non hai rispettato la scadenza, e io stavo aspettando queste lettere. Hai rovinato i miei piani, e quindi sono costretto a ridurre un po' la tua ricompensa. Comunque, sono lieto di darti il tuo dovuto premio - "+FindRussianMoneyString(sti(pchar.GenQuest.(QuestName).Money))+". Ecco a te.");
			link.l1 = "Non direi che mi piace, ma alla fine, i termini sono stati effettivamente violati. Quindi non ho lamentele, "+GetAddress_FormToNPC(NPChar)+".";
		    link.l1.go = "All_Execute_1";
			//--> слухи
			AddSimpleRumour(RandPhraseSimple("You know, governor " + GetFullName(npchar) + " are not very pleased with the quickness of a captain " + GetMainCharacterNameGen() + ".", 
				"Governor " + GetFullName(npchar) + " is not very pleased with captain " + GetMainCharacterNameDat() + ", "+ GetSexPhrase("who","who") +" complied with his orders, but did not in due time..."), sti(npchar.nation), 5, 1);
			//<-- слухи
		break;
		
		// -------------- общий набор для всех квестов мэра ------------------
		case "All_disagree":
			dialog.text = "Mi stai deludendo!";
			link.l1 = "Mi dispiace, "+GetAddress_FormToNPC(NPChar)+", ma non posso accettare questo lavoro.";
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
			dialog.text = RandPhraseSimple("Ebbene, molto male - che altro posso dire. Contavo su di te - e si scopre che ho semplicemente sprecato il mio tempo. Sono deluso.","Ebbene, devo dire che sono completamente deluso da te... Ci sono molte persone nella mia residenza sempre pronte a sbrigare queste faccende per me - e ho sprecato il mio tempo con te. Vabbè...");
			link.l1 = "Mi dispiace, "+GetAddress_FormToNPC(NPChar)+", Ho fatto tutto il possibile.";
		    link.l1.go = "exit";
			//--> слухи
			AddSimpleRumour(LinkRandPhrase("You know, governor " + GetFullName(npchar) + " is very displeased with captain " + GetMainCharacterNameDat() + ". Just imagine - he failed to fulfill his assignment in time!", 
				"Governor " + GetFullName(npchar) + " is slightly annoyed that a captain " + GetFullName(pchar) + " put his shoulder to the wheel, but fail to fulfill his assignment in time. That's too bad...", 
				"I heard that governor " + GetFullName(npchar) + " is very displeased with you, captain " + GetFullName(pchar) + ", since you failed to meet the deadline while trying to fulfill his assignment."), sti(npchar.nation), 5, 1);
			//<-- слухи
			ChangeCharacterComplexReputation(pchar,"nobility", -4);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
			DeleteAttribute(pchar, "GenQuest." + QuestName);
			DeleteAttribute(pchar, "GenQuest.questName");
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_common"; //реплику вертаем
			SaveCurrentNpcQuestDateParam(npchar, "work_date"); //сразу еще один не даем
			CloseQuestHeader("MayorsQuestsList");
		break;
		case "All_Found":
			QuestName = pchar.GenQuest.questName;
			dialog.text = RandPhraseSimple("Sono semplicemente scioccato! Sei riuscito a localizzare il tuo obiettivo ma non ti sei preoccupato dei mezzi per garantire la tua superiorità - questa è estrema imprudenza. Sono deluso!","Bene, devo dire che sono deluso da te... Trovare il tuo bersaglio non basta - devi avere i mezzi per distruggerlo. Ci sono molti tagliagole nella mia residenza sempre pronti a sbrigare queste faccende per me. Cosa stavo pensando quando mi sono rivolto a te?");
			link.l1 = "Mi dispiace, "+GetAddress_FormToNPC(NPChar)+", ma semplicemente non sono disposto a rischiare la mia vita in modo sconsiderato.";
		    link.l1.go = "exit";
			//--> слухи
			AddSimpleRumour(LinkRandPhrase("You know, governor " + GetFullName(npchar) + " is very displeased with captain " + GetMainCharacterNameDat() + ". Imagine, "+ GetSexPhrase("he turned out to be a downright coward","she turned out to be a downright coward") +"!", 
				"Governor " + GetFullName(npchar) + " is slightly annoyed that a captain " + GetFullName(pchar) + " took the job, but failed to carry it out because of their own indecision. Hee-hee, what wilt captains!", 
				"I heard that Governor " + GetFullName(npchar) + " very displeased with you, Captain " + GetFullName(pchar) + ". They say you're nothing but a coward"+ GetSexPhrase("","") +"..."), sti(npchar.nation), 5, 1);
			//<-- слухи
			ChangeCharacterComplexReputation(pchar,"nobility", -6);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
			DeleteAttribute(pchar, "GenQuest." + QuestName);
			DeleteAttribute(pchar, "GenQuest.questName");
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_common"; //реплику вертаем
			SaveCurrentNpcQuestDateParam(npchar, "work_date"); //сразу еще один не даем
			CloseQuestHeader("MayorsQuestsList");
			AddQuestRecord("MayorsQuestsList", "21");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+npchar.city+"Gen"));
			AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
		break;
		case "All_Execute":
			QuestName = pchar.GenQuest.questName;
			dialog.text = RandPhraseSimple("Ottima notizia! Beh, è ora di fare un bilancio. La tua tariffa sarà "+FindRussianMoneyString(sti(pchar.GenQuest.(QuestName).Money))+". Ecco a te.","Eccellente! Questo modo è il migliore per tutti... Bene, sono felice di darti la tua giusta ricompensa - "+FindRussianMoneyString(sti(pchar.GenQuest.(QuestName).Money))+". Eccoti.");
			link.l1 = "Grazie, "+GetAddress_FormToNPC(NPChar)+", "+RandPhraseSimple("piacere fare affari con te!","Sono piacevolmente sorpreso dalla chiarezza degli insediamenti.");
		    link.l1.go = "All_Execute_1";
			//--> слухи
			AddSimpleRumour(LinkRandPhrase("You know, governor " + GetFullName(npchar) + "  was praising for diligence"+ GetSexPhrase("a captain","a young lady") +" " + GetMainCharacterNameGen() + ".", 
				"Governor " + GetFullName(npchar) + " is praising captain " + GetMainCharacterNameGen() + ", "+ GetSexPhrase("he","she") +" is always a flawless performer when it comes to governor's assignments. An irreplaceable person for the governor, I say...", 
				"I heard that governor " + GetFullName(npchar) + " is very much pleased with you, captain " + GetFullName(pchar) + ". He defines you as a very careful and thorough officer. That's very nice to hear, captain..."), sti(npchar.nation), 5, 1);
			//<-- слухи
		break;
		case "All_Execute_1":
			QuestName = pchar.GenQuest.questName;
			dialog.text = RandPhraseSimple("Molto bene. Puoi tornare a trovarmi - forse, troverò un altro lavoro per te.","Bene, fantastico! Immagino che ti offrirò di nuovo questi lavori.");
			link.l1 = RandPhraseSimple("Fantastico.","Bene.");
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
			SaveCurrentNpcQuestDateParam(npchar, "work_date"); //сразу еще один не даем
			// инкремент в базу заданий мэров
			sTemp = npchar.City;
			if (!CheckAttribute(pchar, "GenQuest.MayorQuestsList." + sTemp)) pchar.GenQuest.MayorQuestsList.(sTemp) = 0;
			pchar.GenQuest.MayorQuestsList.(sTemp) = sti(pchar.GenQuest.MayorQuestsList.(sTemp)) + 1;
		break;
//<-- осады homo
		case "siege_task":
            makearef(aData, NullCharacter.Siege);
            aData.HelpColony = true;
			dialog.text = "In questi tempi difficili qualsiasi aiuto sarebbe molto gradito. Accettiamo il tuo aiuto - aiutaci a difendere la nostra colonia, e sarai ricompensato.";
			link.l1 = "Allora non perdiamo tempo.";
		    link.l1.go = "exit";
		break;
		
		//Jason --> Бремя гасконца
		case "Sharlie":
			dialog.text = "Stai cercando Michel de Monper? Interessante... E per cosa ti serve?";
			link.l1 = "Sono suo fratello. Mio padre mi ha detto che Michel è in difficoltà e ha bisogno di aiuto, quindi io...";
			link.l1.go = "Sharlie_1";			
		break;
		
		case "Sharlie_1":
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "First time";
			DelLandQuestMark(sld);
			dialog.text = "Sei tu? Non ricordo che Monsieur de Monper avesse fratelli... Sai, monsieur, mi sembri molto sospetto... quindi ti arresto per ulteriori indagini. Tenente! Arresta quest'uomo!";
			link.l1 = "Ma Vostra Signoria!";
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
			dialog.text = "E tuttavia vorrei fare ammenda. Ecco - per favore prendi questa spada, questa pistola e questa armatura leggera - è il mio dono per te. Credo che troverai queste cose piuttosto utili.";
			link.l1 = "Grazie, signore. Considerando che le vostre guardie hanno preso tutto quello che possedevo, mi sarà molto utile.";
			// belamour legendary edition -->
			link.l1.go = "Sharlie_5";		
			link.l2 = "Grazie, signore. C'è un altro modo in cui potresti aiutarmi? Da gentiluomo a gentiluomo? Puoi vedere da solo in che terribile situazione mi trovo!";
			link.l2.go = "Sharlie_3";	
		break;
		
		case "Sharlie_3":
			dialog.text = "Ebbene, Charles... (frugando nella scrivania) Tieni, conserva questo sacro amuleto per buona fortuna. Non posso aiutarti di più, mi dispiace. Qui nelle colonie dovrai fare affidamento solo su te stesso.";
			link.l1 = "Bene, almeno qualcosa. Grazie per il regalo, signore.";
			link.l1.go = "Sharlie_4";
		break;
		
		case "Sharlie_4":
			DialogExit();
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			AddCharacterExpToSkill(pchar, "Commerce", 10);
			Log_Info("You'have received equipment");
			Log_Info("You have received the 'Holy Water' amulet");
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
			Log_Info("You'have received equipment");
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
			dialog.text = "Un vero colpo di scena, Charles... Non è frequente vedere qualcuno salire così rapidamente nel nostro mondo. Ho la sensazione che tu ed io andremo d'accordo benissimo.";
			link.l1 = "Sarebbe un onore. Forse avete un incarico per me?";
			link.l1.go = "TK_TravlyaKrys_2";
			DeleteAttribute(pchar, "questTemp.TK_TravlyaKrys");
			PChar.quest.TK_Timer.over = "yes";
		break;
		
		case "TK_TravlyaKrys_2":
			dialog.text = "Certo! Specialmente dopo il tuo successo nell'ingaggio con uno dei pirati di Barbazon vicino a Le Francois...";
			link.l1 = "Non posso dire di avere bei ricordi di quell'incontro. Chi diavolo è Barbazon?";
			link.l1.go = "TK_TravlyaKrys_3";
		break;
		
		case "TK_TravlyaKrys_3":
			dialog.text = "Jacques Barbazon, noto anche come Jacques il Buono, guida il nido di banditi a Le Françcois. È uno dei cosiddetti baroni dei pirati, che causano problemi con la pirateria e il contrabbando nelle Piccole Antille. È un criminale noto, e segna le mie parole, incontrerà la sua fine alla forca a St. Pierre un giorno!";
			link.l1 = "Scusatemi, ma non siete voi la vera autorità in Martinica? Non potete semplicemente eliminare quel nido? Ci sono stato, e credetemi, non c'è molto da vedere.";
			link.l1.go = "TK_TravlyaKrys_4";
		break;
		
		case "TK_TravlyaKrys_4":
			dialog.text = "Ti consiglierei di non vantarti della tua conoscenza dei luoghi meno rispettabili della mia isola, Charles. Non è degno di un nobile. Per quanto riguarda la tua domanda\nNon tutto nel nostro mondo può essere risolto con la forza bruta. Ci sono politica e interessi commerciali in gioco. Ma non entriamo in dettagli inutili: ho un compito specifico che richiede un po' di forza bruta.";
			link.l1 = "Per favore, continua.";
			link.l1.go = "TK_TravlyaKrys_5";
		break;
		
		case "TK_TravlyaKrys_5":
			dialog.text = "Barbazon attira piccole ciurme, affamate di oro facile. A volte, lancia un osso a uno di loro solo per guardare tutti combattere per esso. Ogni tanto, mette il sopravvissuto al lavoro, ma più spesso lo scaccia, e credimi, non c'è niente di più pericoloso di un pirata disperato in giro.";
			link.l1 = "Credo di capire, ma non sono sicuro di essere all'altezza. Ho preso il comando della mia nave solo di recente, e sto ancora imparando i trucchi del mestiere, per così dire...";
			link.l1.go = "TK_TravlyaKrys_6";
		break;
		
		case "TK_TravlyaKrys_6":
			dialog.text = "Sciocchezze! Hai già assaporato la vittoria - più di molti degli scansafatiche tra i miei ufficiali! La città ti ricompenserà con cinquemila pesos per aver affondato un altro dei ratti di Barbazon, esentasse. Ottomila se riporti il pirata vivo - per una giusta esecuzione, naturalmente.";
			link.l1 = "Certo che potrei usare i soldi. Dove posso trovare questo pirata?";
			link.l1.go = "TK_TravlyaKrys_7";
			link.l2 = "Mi dispiace, ma non credo di essere pronto per questo tipo di compito ancora.";
			link.l2.go = "TK_TravlyaKrys_Otkaz";
		break;
		
		case "TK_TravlyaKrys_Otkaz":
			dialog.text = "È un peccato, Charles. In tal caso, non ti tratterrò più a lungo.";
			link.l1 = "Arrivederci, Vostra Eccellenza.";
			link.l1.go = "exit";
		break;
		
		case "TK_TravlyaKrys_7":
			dialog.text = "Sono contento che tu sia a bordo, Charles. I nostri rapporti di intelligence indicano che l'Hater, un goletta, si sta attualmente preparando a partire da Le Francois. Non possiamo permetterci di ritardare, quindi salpa e attacca. Non preoccuparti, amico mio, avrai successo.";
			link.l1 = "Con la grazia di Dio, Vostra Eccellenza.";
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
			dialog.text = "Certo che puoi, capitano! Ecco perché ti ho disturbato.";
			link.l1 = "Allora ascolto attentamente.";
			link.l1.go = "Portugal_1";
		break;
		
		case "Portugal_1":
			dialog.text = "I pescatori locali hanno visto una strana nave vicino all'isola ieri notte. Dicono che fosse una enorme nave da guerra, come una nave di linea, senza alcuna bandiera o lanterna di segnale. Non penso che questa nave potesse essere effettivamente più grande di una fregata, ma anche quella sarebbe già troppo!";
			link.l1 = "La paura trasforma le talpe in montagne, questo è certo... ma qual è il punto?";
			link.l1.go = "Portugal_2";
		break;
		
		case "Portugal_2":
			dialog.text = "Mi rivolgo a te, capitano. I miei partner commerciali sono spaventati da queste voci - credono che siano pirati o corsari spagnoli, ed è un male per il commercio. Peggio di tutto - attualmente non ci sono navi da guerra nella colonia, solo un paio di sloop per la protezione e un vecchio schooner, adatto per la caccia ai contrabbandieri\nNon posso lasciarlo inosservato... Comunque, ora che la voce sulla nave misteriosa è conosciuta da metà della città! Per favore, unisciti con la tua nave per aiutarci a trovarla - ti conosco come un capitano decente, e anche se davvero c'è solo una fregata, i tuoi cannoni possono convincerla a cercare prede altrove!";
			link.l1 = "Signore... In realtà, avevo piani diversi...";
			link.l1.go = "Portugal_3";
		break;
		
		case "Portugal_3":
			dialog.text = "Per favore, capitano! Solo per un paio di giorni, finché questi pettegolezzi inquietanti non si calmano! E ovviamente sarai pagato per il tuo tempo. 10.000 pezzi di otto ti andrebbero bene?";
			link.l1 = "Uhm... ma, vostra Eccellenza, io...";
			link.l1.go = "Portugal_4";
		break;
		
		case "Portugal_4":
			dialog.text = "E raddoppieremo, se effettivamente entrerai in combattimento con questa nave, e lo triplicheremo se la affonderai! Allora, cosa ne dici?";
			link.l1 = "Bene, comunque avevo intenzione di rimanere qui per un paio di giorni.";
			link.l1.go = "Portugal_5";
		break;
		
		case "Portugal_5":
			dialog.text = "Eccellente, non ho mai davvero dubitato di te, monsieur capitano! Ricorda - solo due giorni nelle nostre acque - e il denaro è tuo. E se sarai costretto a entrare in battaglia, sarai pagato in base all'esito.";
			link.l1 = "Capisco, Vostra Eccellenza. Abbiamo un accordo e ora torno alla mia nave.";
			link.l1.go = "Portugal_6";
		break;
		
		case "Portugal_6":
			dialog.text = "Ti aspetterò al tuo ritorno, capitano!";
			link.l1 = "Permettetemi di prendere congedo.";
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
			dialog.text = "Capitano, credo che abbiamo fatto un accordo che tu avresti pattugliato le nostre acque costiere per due giorni!";
			link.l1 = "Sì, certo. Me lo ricordo.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Portugal_8";
		break;
		
		case "Portugal_9":
			dialog.text = "Ebbene, hai fatto la tua parte dell'accordo. Ecco la tua ricompensa - 10.000 pesos, come abbiamo concordato.";
			link.l1 = "Grazie! Come puoi vedere, le tue preoccupazioni erano infondate. Buona fortuna a te!";
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
			dialog.text = "Oh "+GetAddress_Form(NPChar)+", mi hai sorpreso! Quei mascalzoni sono davvero diventati così sfacciati? Devo avvisare immediatamente il comandante e inviare una pattuglia costiera lì!";
			link.l1 = "Ero felice di aiutare. Posso prendere il mio congedo ora?";
			link.l1.go = "JusticeOnSale_2";
			
			DeleteAttribute(PChar, "GenQuest.JusticeOnSale.MayorWait");
			DeleteAttribute(PChar, "GenQuest.JusticeOnSale.PrisonWait");
			
			DeleteQuestCondition("JusticeOnSale_MapEnter");
		break;
		
		case "JusticeOnSale_2":
			dialog.text = "Certo, capitano. Ecco - per favore, accetta questa modesta ricompensa personalmente da me.";
			link.l1 = "Grazie.";
			link.l1.go = "JusticeOnSale_3";
		break;
		
		case "JusticeOnSale_3":
			AddQuestRecord("JusticeOnSale", "5");
			CloseQuestHeader("JusticeOnSale");
			
			AddMoneyToCharacter(PChar, 1000 + sti(PChar.rank) * 30 * hrand(10));
			
			DeleteAttribute(PChar, "GenQuest.JusticeOnSale");
			
			DialogExit();
		break;
		
		case "JusticeOnSale_4":
			dialog.text = "Hai ragione, capitano! Non possiamo proprio lasciare le cose così! Ti chiederei di dirigerti verso "+XI_ConvertString(PChar.GenQuest.JusticeOnSale.ShoreId+"Dat")+", trova la loro nave e arresta tutta la loro banda! Se resistono - usa la forza e non esitare!";
			link.l1 = "Permettimi di prendere congedo.";
			link.l1.go = "JusticeOnSale_5";
		break;
		
		case "JusticeOnSale_5":
			dialog.text = "Ora vai. Naviga là e assicurati che nessuno sfugga alla giustizia. Penso che prima dovrai sbarcare sulla riva, e poi potrai occuparti della nave.";
			link.l1 = "...";
			link.l1.go = "JusticeOnSale_6";
		break;
		
		case "JusticeOnSale_6":
			sld = GetCharacter(NPC_GenerateCharacter("JusticeOnSale_ShipPirate", "", "man", "man", sti(PChar.rank) + 5, PIRATE, -1, true, "quest"));
			sld.Ship.Type = GenerateShipExt(sti(PChar.GenQuest.JusticeOnSale.ShipType), true, sld);
			sld.Ship.Name = PChar.GenQuest.JusticeOnSale.ShipName;
			SetBaseShipData(sld);
			SetCrewQuantityFull(sld);
			Fantom_SetCannons(sld, "pirate");
			Fantom_SetBalls(sld, "pirate");
			Fantom_SetUpgrade(sld, "pirate");
			SetCaptanModelByEncType(sld, "pirate");
			SetRandGeraldSail(sld, PIRATE);
			
			Character_SetAbordageEnable(sld, false);
			
			Group_FindOrCreateGroup("JusticeOnSaleGroup");
			Group_AddCharacter("JusticeOnSaleGroup", "JusticeOnSale_ShipPirate");
			Group_SetGroupCommander("JusticeOnSaleGroup", "JusticeOnSale_ShipPirate");
			Group_SetAddress("JusticeOnSaleGroup", PChar.curislandid, "reload", Island_GetLocationReloadLocator(PChar.curislandid, PChar.GenQuest.JusticeOnSale.ShoreId));
			Group_SetTaskNone("JusticeOnSaleGroup");
			Group_LockTask("JusticeOnSaleGroup");
			
			sld.AlwaysFriend = true;
			SetCharacterRelationBoth(sti(sld.index), GetMainCharacterIndex(), RELATION_FRIEND);
			
			SetCharacterShipLocation(sld, PChar.GenQuest.JusticeOnSale.ShoreId);

			DeleteAttribute(sld, "SinkTenPercent");
			DeleteAttribute(sld, "SaveItemsForDead");
			DeleteAttribute(sld, "DontClearDead");
			DeleteAttribute(sld, "AboardToFinalDeck");
			
			sld.AlwaysSandbankManeuver = true;
			sld.AnalizeShips = true;
			sld.DontRansackCaptain = true;
			
			sld = &Locations[FindLocation(PChar.GenQuest.JusticeOnSale.ShoreId)];
			sld.DisableEncounters = true;
			
			PChar.Quest.JusticeOnSale_ShoreEnterFromMayor.win_condition.l1  = "location";
			PChar.Quest.JusticeOnSale_ShoreEnterFromMayor.win_condition.l1.location = PChar.GenQuest.JusticeOnSale.ShoreId;
			PChar.Quest.JusticeOnSale_ShoreEnterFromMayor.function = "JusticeOnSale_ShoreEnterFromMayor";
			
			PChar.Quest.JusticeOnSale_PirateShip_Sink.win_condition.l1 = "Character_sink";
			PChar.Quest.JusticeOnSale_PirateShip_Sink.win_condition.l1.character = "JusticeOnSale_ShipPirate";
			PChar.Quest.JusticeOnSale_PirateShip_Sink.function = "JusticeOnSale_PirateShip_Sink";
			
			DialogExit();
		break;
		
		case "JusticeOnSale_7":
			dialog.text = "Grazie per il tuo aiuto. Quei mascalzoni hanno avuto ciò che meritavano. Per favore, permettimi di presentarti personalmente questo modesto premio da parte mia. Apprezzo molto l'ordine e la pace nella mia città.";
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
				notification("Level 20 required", "None");
				dialog.text = "Ah, meraviglioso, bello vederti, capitano! Ho sentito parlare delle tue abilità, ma vieni quando sei veramente pronto.";
				link.l1 = "Sì, certo. Come desideri.";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Oh, fantastico, sono felice di vederti, capitano! Sei arrivato proprio in tempo - la regata sta per iniziare tra pochi giorni. Hai letto le regole della regata, che un ordinanza dovrebbe averti consegnato?";
				link.l1 = "Sì, signore, l'ho fatto.";
				link.l1.go = "Regata_1";
				RemoveItems(PChar, "letter_open", 1);//уберем письмо
				DeleteAttribute(pchar, "questTemp.Regata.ToPortRoyal"); // patch-5
			}
		break;
		
		case "Regata_1":
			dialog.text = "E hai preparato 50000 pesos - la tua quota di iscrizione, che contribuirà al montepremi?";
			if (makeint(Pchar.money) >= 50000)
			{
				link.l1 = "Sì, certamente. Si prega di accettare la mia tariffa.";
				link.l1.go = "Regata_2";
			}
			link.l2 = "Al momento sono un po' a corto di soldi. Ma raccoglierò sicuramente l'importo richiesto.";
			link.l2.go = "Regata_nomoney";
		break;
		
		case "Regata_2":
			dialog.text = "Molto bene. Se vinci - riavrai i tuoi soldi quintuplicati. Ora devi conoscere meglio le regole della regata\nTutti i dettagli li puoi apprendere da Sir Henry Stivenson, dovrebbe essere in una stanza della residenza. Vai da lui - ti spiegherà tutto.";
			link.l1 = "Bene. Farò proprio così.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -50000);
			pchar.quest.Regata_Guber.win_condition.l1 = "location";
			pchar.quest.Regata_Guber.win_condition.l1.location = "Portroyal_Roomtownhall";
			pchar.quest.Regata_Guber.function = "PrepareToRegataInPortroyal";
			pchar.questTemp.Regata.Begin = "true";
			NextDiag.TempNode = "First time";
		break;
		
		case "Regata_nomoney":
			dialog.text = "Bene, ma per favore, non impiegare troppo tempo, capitano. La regata inizia molto presto.";
			link.l1 = "Capisco. Cercherò di portarti i soldi il più presto possibile.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Regata_1";
			pchar.questTemp.Regata.nomoney = "true";
		break;
		
		//регата-финал
		case "Regata_Final":
			dialog.text = "Aha! E qui abbiamo il vincitore della regata! Buongiorno Capitano "+GetFullName(pchar)+"! Permettimi di congratularmi con te per questo meritato successo! I vincitori della regata sono sempre stati popolari nelle colonie inglesi - e per buone ragioni.";
			link.l1 = "Grazie, signore!";
			link.l1.go = "Regata_complete";
		break;
		
		case "Regata_complete":
			dialog.text = "Ora passiamo alla parte più piacevole - la cerimonia di premiazione. Il premio per il primo posto è di 250.000 pesos. Congratulazioni!";
			link.l1 = "Grazie!";
			link.l1.go = "Regata_complete_1";
		break;
		
		case "Regata_complete_1":
			AddMoneyToCharacter(pchar, 250000);
			// belamour legendary edition в регате только один приз -->
			GiveItem2Character(pchar, "blade_26");
			GiveItem2Character(pchar, "cirass4");
			GiveItem2Character(pchar, "bussol");
			
			dialog.text = "Inoltre, riceverai un set di premi preziosi: la leggendaria spada di acciaio di Toledo 'Asoleda', un set di armatura milanese e una bussola di pregio. Tutto tuo.";
			// <-- legendary edition
			link.l1 = "Sono molto contento, signore. Davvero, non avrei potuto aspettarmi una tale generosità.";
			link.l1.go = "Regata_complete_2";
		break;
		
		case "Regata_complete_2":
			dialog.text = "A nome di tutti i sudditi delle colonie inglesi ti ringrazio per la tua partecipazione alla regata e ti congratulo ancora una volta per la tua vittoria! Se hai fatto una scommessa, vai da Sir Henry Stevenson e ritira le tue vincite se non l'hai ancora fatto. Buona fortuna a te, capitano!";
			link.l1 = "Grazie per le vostre gentili parole, signore! A mia volta, permettetemi di ringraziarvi per avermi dato l'opportunità di partecipare a un evento così grandioso. Ora, vi prego, permettetemi di prendere congedo.";
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
		case 0: sText = "That Judas, using his position, sold an important state secret to an enemy power."; break;
		case 1: sText = "That foul scoundrel killed his relative, a well-known and noble man, in order to inherit his fortune."; break;
		case 2: sText = "That foul scoundrel insulted my family and me personally."; break;
		case 3: sText = "This thieving rogue stole a decent sum of money from our city's treasury."; break;
		case 4: sText = "That villain is guilty of deaths of nearly a dozen of our citizens."; break;
		case 5: sText = "That rogue used his connection to take possession of a merchant vessel, and then he stole it and sold at the neighboring shipyard."; break;
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
		case 0: sText = "one of the junior officers in our garrison has deserted and left the colony on board of a merchant ship."; break;
		case 1: sText = "one of our officers deserted right on duty and escaped on board of a smuggler ship."; break;
		case 2: sText = "one of our naval officers serving on a patrol brig deserted for unknown reason, hijacked a long boat and disappeared on it."; break;
		case 3: sText = "one of our prison guards threw up his service for  unknown reason and left our colony aboard a private vessel."; break;
		case 4: sText = "one of the soldiers in our garrison abandoned his post while keeping guard, went to the cove and left this place aboard an unknown vessel."; break;
		case 5: sText = "one of our military officers, captain of a patrol lugger, abandoned his ship in the open sea and went south on a fishing long boat."; break;
	}
	return sText;
}
