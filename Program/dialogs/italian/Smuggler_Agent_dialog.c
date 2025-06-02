void ProcessDialogEvent()
{
	ref NPChar, her;
	aref Link, NextDiag;
	bool bOk = false;
    bool bOk2;
    
	int Sum, nRel, nDay, iChurchQuest2_Summ;
	ref sld;
	
	// Церковный квест № 2 -->
	if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskContra_1") && !CheckAttribute(PChar, "GenQuest.ChurchQuest_2.Summ_To_Contra"))
	{
		iChurchQuest2_Summ = sti(PChar.rank)*100 + (rand(3)+1)*100;
		PChar.GenQuest.ChurchQuest_2.Summ_To_Contra = sti(iChurchQuest2_Summ);
	}
	// <-- Церковный квест № 2
	
	string sColony;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
    string iDay, iMonth;
	iDay = environment.date.day;
	iMonth = environment.date.month;
	string lastspeak_date = iday + " " + iMonth;

	// belamour legendary edition
	bool MCGovernon = CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE;
	bool MCAdmiral = isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation);

	if (!CheckAttribute(npchar, "quest.trade_date"))
    {
        npchar.quest.trade_date = "";
    }

	//тереть нафиг аттрибут при прошествии дней (navy fix)
	if (CheckAttribute(pchar, "GenQuest.contraTravel.days") && GetQuestPastDayParam("contraTravel") > sti(PChar.GenQuest.contraTravel.days))
	{
		DeleteAttribute(pchar, "GenQuest.contraTravel");
		CloseQuestHeader("Gen_ContrabandTravel");
	}

	switch(Dialog.CurrentNode)
	{
        case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Smuggling_exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			PlaceSmugglersOnShore(Pchar.quest.contraband.CurrentPlace);
			Pchar.quest.Contraband.active = true;
			pchar.GenQuest.Contraband.GuardNation = npchar.nation;
			pchar.GenQuest.Contraband.SmugglerId  = npchar.id;				
			SetAllContraGoods(&Stores[sti(Pchar.GenQuest.Contraband.StoreIdx)], npchar);
			ReOpenQuestHeader("Gen_Contraband");
            if (GetIslandByCityName(npchar.city) == "Mein")
            {
            	AddQuestRecord("Gen_Contraband", "t1_1");
            }
            else
            {
	            AddQuestRecord("Gen_Contraband", "t1");
				AddQuestUserData("Gen_Contraband", "sIsland", XI_ConvertString(GetIslandByCityName(npchar.city)));
			}
			AddQuestUserData("Gen_Contraband", "sLoc", GetConvertStr(Pchar.quest.contraband.CurrentPlace, "LocLables.txt"));
				
			DialogExit();
		break;
		
		case "First time":											
			//--> Jason если идёт первая часть квеста Шарля
			if (CheckAttribute(pchar, "questTemp.Sharlie.Lock"))
            {
				dialog.text = "Signore, lascia questo posto. Dubito che abbiamo qualcosa di cui parlare.";
				link.l1 = "Oh, davvero? Non ti piace la mia faccia? Bene, me ne vado...";
				link.l1.go = "exit";
				break;
			}
			//<-- идёт первая часть квеста Шарля
			//--> Addon-2016 Jason блокировка контры во избежание конфликтов с квестами
			if (CheckAttribute(pchar, "GenQuest.Smugglersblock") && pchar.GenQuest.Smugglersblock == npchar.location)
            {
				dialog.text = "Nessun affare oggi.";
				link.l1 = "Vedo.";
				link.l1.go = "exit";
				break;
			}
			//--> прибыла инспекция на Святом Милосердии
			if (CheckAttribute(npchar, "quest.SantaMisericordia"))
			{
				dialog.text = "I miei amici ed io siamo estremamente occupati oggi.";
				link.l1 = "Ma ho bisogno...";
				link.l1.go = "SantaMisericordia_1";
				break;
			}
			//<-- прибыла инспекция на Святом Милосердии
			//--> Jason Цена чахотки
			if (CheckAttribute(pchar, "questTemp.Consumption.Contra"))
            {
				dialog.text = "Cosa vuoi, capitano?";
				link.l1 = "Possiamo parlare un po'?";
				link.l1.go = "Consumption";
				break;
			}
			//<-- Цена чахотки
			
			if(NPChar.quest.meeting == "0")
			{
				Dialog.Text = "Cosa vuoi, capitano? Non conosco il tuo nome e non posso dirti il mio.";
				Link.l1 = "Sono il capitano "+GetFullName(pchar)+".";
				Link.l1.go = "meeting";
				NPChar.quest.meeting = "1"; 
			}
			else
			{
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.GetRumour") && GetQuestPastDayParam("GenQuest.CaptainComission.GetRumour") < 1)
				{
					if(!CheckAttribute(pchar,"GenQuest.CaptainComission.SpeakContra"))
					{
						pchar.GenQuest.CaptainComission.SpeakContra = true;
						dialog.text = "Nessun affare oggi. Ci sono pattuglie in ogni baia, il nostro governatore sta cercando un carico che è stato confiscato da qualche capitano di"+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")+"Acc"))+" "+pchar.GenQuest.CaptainComission.Name+" e lui lo ha nascosto da qualche parte.";
						link.l1 = "E dove si trova questo capitano"+pchar.GenQuest.CaptainComission.Name+"?";
						link.l1.go = "CapComission_1";
						break;
					}
					else
					{
						dialog.text = "Nessun affare oggi.";
						link.l1 = "Vedo.";
						link.l1.go = "exit";					
						break;
					}
				}

				if(pchar.questTemp.Slavetrader == "FindMayak" && Islands[GetCharacterCurrentIsland(pchar)].id == pchar.questTemp.Slavetrader.EsIsland)
				{
					dialog.text = "Nessun affare oggi.";
					link.l1 = "Vedo.";
					link.l1.go = "exit";
					break;
				}
				
				if(npchar.id == "Bridgetown_Smuggler" && CheckAttribute(pchar, "questTemp.BM_blockSmuggler"))
				{
					dialog.text = "Nessun affare oggi.";
					link.l1 = "Vedo.";
					link.l1.go = "exit";
					break;
				}

				Dialog.Text = "Cosa vuoi, capitano?";
				if (LAi_group_GetPlayerAlarm() > 0)
				{
	       			Dialog.Text = RandPhraseSimple("Sii veloce, "+GetSexPhrase("amico","ragazza")+", cosa vuoi? Ti stanno inseguendo!","Dichiara il tuo affare e fallo in fretta! I soldati ti stanno inseguendo e non abbiamo molto tempo...");
				}
				// belamour legendary edition
				bOk2 = MCGovernon || MCAdmiral;
				if(FindContrabandGoods(PChar) != -1 && !bOk2)
				{
					Link.l1 = "Vorrei comprare o vendere qualcosa.";
					Link.l1.go = "Meeting_3";
				}

				if (CheckAttribute(pchar, "GenQuest.contraTravel.active") && sti(pchar.GenQuest.contraTravel.active) == true)
					Link.l2 = "Sul viaggio...";
				else
					Link.l2 = "Devo arrivare in un posto.";
				Link.l2.go = "Travel";
				if (CheckCharacterItem(pchar, "CaptainBook") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakSmuggler"))
				{
					if((pchar.questTemp.different.GiveShipLetters.city == npchar.city) && CheckAttribute(pchar, "questTemp.different.GiveShipLetters"))
					{
						link.l3 = "Ho qualcosa di 'speciale' e penso che potrebbe interessarti. Dai un'occhiata!";
						link.l3.go = "SM_ShipLetters_1";
					}	
				}				

				//Jason --> мини-квест Бесчестный конкурент
				if(CheckAttribute(PChar, "questTemp.Shadowtrader.seeksmugglers") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_tavern")
				{
					Link.l8 = "Ho un affare insolito per te.";
					Link.l8.go = "Shadowtrader_smugglers";
				}
				// <-- мини-квест Бесчестный конкурент
				//--> Торговля по закону
				if(CheckAttribute(PChar, "questTemp.TPZ_ContraInfo") && NPChar.location == "BasTer_tavern")
				{
					Link.l8 = "Ascolta, amico, ho bisogno di una spedizione di vino e rum. Quanto più, tanto meglio.";
					Link.l8.go = "TPZ_smugglers_1";
				}
				// <-- Торговля по закону
				//Jason --> генератор сбыта бакаута
				if(NPChar.location == "Marigo_tavern" && CheckAttribute(PChar, "GenQuest.Bakaut") && !CheckAttribute(PChar, "GenQuest.Bakaut.Info"))
				{
					Link.l9 = "Devo incontrare Michael Rosenkraft. Ho la merce che potrebbe interessarlo.";
					Link.l9.go = "bakaut";
				}
				// <-- генератор сбыта бакаута
				
				// Церковный генератор №2 -->
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskContra_1") && NPChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_tavern")
				{
					Link.l4 = "Devo scoprire qualcosa, amico.";
					Link.l4.go = "Contra_GenQuest_Church_2_1";
				}
				
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskContra_2") && NPChar.location == PChar.GenQuest.ChurchQuest_2.Contra_Colony + "_tavern")
				{
					Link.l5 = "Un tuo collega e mio buon amico da  "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_2.QuestTown+"Gen")+" mi hanno detto che sei a conoscenza di certi affari.";
					Link.l5.go = "Contra_GenQuest_Church_2_Contra2_1";
				}
				// <-- Церковный генератор №2
				
				Link.l7 = "Niente. Ci vediamo.";
				Link.l7.go = "Exit";				
			}
		break;
		
		case "CapComission_1":
			if(pchar.GenQuest.CaptainComission.variant == "A2")
			{
				dialog.text = "Nel seminterrato del forte dove altrimenti? Quel capitano può rivelare l'oro nascosto alle autorità in qualsiasi momento e non ci resterà nulla. Non pensare a nessun affare fino a quando questa confusione non sarà finita.";
				link.l1 = "Ascolta, conosci ogni singolo pezzo di quest'isola. Davvero non hai idea di dove sia il capitano "+pchar.GenQuest.CaptainComission.Name+"dov'è la scorta?";
				link.l1.go = "CapComission_4";
			}
			if(pchar.GenQuest.CaptainComission.variant == "A3")
			{
				dialog.text = "Immagino al cielo. È stato impiccato con il suo equipaggio. Ma non hanno menzionato nella sentenza di morte che si trattava di una nave pirata.";
				link.l1 = "E perché sei così sicuro che la nave fosse una pirata?";
				link.l1.go = "CapComission_2";
			}	
		break;
		
		case "CapComission_2":
			dialog.text = "Avevamo osservato la battaglia dalla roccia. In un cannocchiale abbiamo visto la nave sotto la Jolly Roger. Poi, come cinque ore dopo, abbiamo visto un flash nel buio, sembrava un colpo dalla sala della polvere da sparo. Abbastanza tempo per spostare il carico sulla riva.";
			link.l1 = "Non sai dove si trova il capitano "+pchar.GenQuest.CaptainComission.Name+"'s stash? Conosci ogni pezzo di quest'isola.";
			link.l1.go = "CapComission_3";
		break;
		
		case "CapComission_3":
			dialog.text = "No. E lo stiamo cercando anche noi, ma non per il divertimento del governatore...";
			link.l1 = "Vedo.... Buona giornata.";
			link.l1.go = "exit";
			AddQuestRecord("CaptainComission2", "38");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Acc")));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sShipTypeQuest", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name") + "Gen")));
		break;
		
		case "CapComission_4":
			dialog.text = "No. E lo stiamo cercando anche noi, ma non per l'amusement del governatore... he-he";
			link.l1 = "Capisco... Buona giornata.";
			link.l1.go = "exit";
			AddQuestRecord("CaptainComission2", "19");
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Gen"))); // belamour gen
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
		break;
				
		case "SM_ShipLetters_1":
			pchar.questTemp.different.GiveShipLetters.speakSmuggler = true;
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 0)
			{
				dialog.text = "Perché hai deciso così? Sono un onesto costiero. Vai a cercare un altro compratore.";
				link.l1 = "Grazie...";
				link.l1.go = "exit";
			}
			else
			{
				if(!CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakUsurer_1"))
				{
					dialog.text = "Perché no? Forse troverò un uso per il tuo 'carico'. Prendi "+sti(pchar.questTemp.different.GiveShipLetters.price2)+" monete e dimenticatene.";
					link.l1 = "No, grazie.";
					link.l1.go = "SM_ShipLetters_2";	
					link.l2 = "E hai indovinato correttamente, sto cominciando a dimenticare questo!";
					link.l2.go = "SM_ShipLetters_3";
				}
				else
				{
					if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 1)
					{
						dialog.text = "Esattamente! Sono davvero curioso ora. Suppongo che se ti pago "+sti(pchar.questTemp.different.GiveShipLetters.price3)+" monete e non ti importerà affatto di quei documenti.";
						link.l1 = "No, grazie.";
						link.l1.go = "SM_ShipLetters_2";
						link.l2 = "E hai ragione. Me ne sono già dimenticato.";
						link.l2.go = "SM_ShipLetters_3";
					}
					if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 2)
					{
						dialog.text = "Ecco, questa è un'occasione per prendere quel maledetto insolente! Sono davvero, davvero curioso. Guarda, ti pagherò "+sti(pchar.questTemp.different.GiveShipLetters.price4)+" in oro e dimenticherai completamente i documenti sul tavolo?";
						link.l1 = "Non lo farò.";
						link.l1.go = "SM_ShipLetters_2";
						link.l2 = "Bene, affare fatto!";
						link.l2.go = "SM_ShipLetters_3";
					}
				}
			}
		break;
		
		case "SM_ShipLetters_2":
			dialog.text = "Va bene, va bene, ma smetti di farti altri nemici.";
			link.l1 = "Anche a te!";
			link.l1.go = "exit";
		break;
		
		case "SM_ShipLetters_3":
			TakeItemFromCharacter(pchar, "CaptainBook"); 
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 1)
			{
				if(!CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakUsurer_1"))
				{
					addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price2)); 
				}
				else
				{
					addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price3)); 
				}
			}
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 2)
			{
				if(!CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakUsurer_1"))
				{
					addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price2)); 
				}
				else
				{
					addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price4)); 
				}
			}
						
			if((sti(pchar.questTemp.different.GiveShipLetters.variant) == 0) || (sti(pchar.questTemp.different.GiveShipLetters.variant) == 2))
			{	
				ChangeCharacterComplexReputation(pchar,"nobility", -1); 
				OfficersReaction("bad"); 
			}	
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //снимаем таймер 
			AddQuestRecord("GiveShipLetters", "7");			
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "Meeting":
			if(CheckAttribute(pchar,"GenQuest.CaptainComission.GetRumour") && GetQuestPastDayParam("GenQuest.CaptainComission.GetRumour") < 2)
			{
				if(!CheckAttribute(pchar,"GenQuest.CaptainComission.SpeakContra"))
				{
					pchar.GenQuest.CaptainComission.SpeakContra = true;
					dialog.text = "Nessun affare oggi. Ci sono pattuglie in ogni baia, il nostro governatore sta cercando un carico che è stato confiscato da qualche capitano di"+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")+"Acc"))+" "+pchar.GenQuest.CaptainComission.Name+" e lui l'ha nascosto da qualche parte.";
					link.l1 = "E dove si trova questo capitano"+pchar.GenQuest.CaptainComission.Name+"?";
					link.l1.go = "CapComission_1";
					break;
				}
				else
				{
					dialog.text = "Nessun affare oggi.";
					link.l1 = "Vedo.";
					link.l1.go = "exit";					
					break;
				}
			}
			
			if(pchar.questTemp.Slavetrader == "FindMayak" && Islands[GetCharacterCurrentIsland(pchar)].id == pchar.questTemp.Slavetrader.EsIsland)
			{
				dialog.text = "Nessun affare oggi.";
				link.l1 = "Vedo.";
				link.l1.go = "exit";
				break;
			}
			
			if(npchar.id == "Bridgetown_Smuggler" && CheckAttribute(pchar, "questTemp.BM_blockSmuggler"))
			{
				dialog.text = "Nessun affare oggi.";
				link.l1 = "Vedo.";
				link.l1.go = "exit";
				break;
			}
			
			Dialog.Text = "Come posso aiutarti, capitano?";
			
			bOk2 = MCGovernon || MCAdmiral;
			if(FindContrabandGoods(PChar) != -1 && !bOk2)
			{
				Link.l1 = "Voglio comprare o vendere roba.";
				Link.l1.go = "Meeting_1";
			}
			
			Link.l2 = "Ho bisogno di arrivare in un posto.";
			Link.l2.go = "Travel";				
			
			//Jason --> мини-квест Бесчестный конкурент
			if(CheckAttribute(PChar, "questTemp.Shadowtrader.seeksmugglers") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_tavern")
			{
				Link.l8 = "Ho un affare piuttosto insolito per te.";
				Link.l8.go = "Shadowtrader_smugglers";
			}
			// <-- мини-квест Бесчестный конкурент
			//--> Торговля по закону
				if(CheckAttribute(PChar, "questTemp.TPZ_ContraInfo") && NPChar.location == "BasTer_tavern")
				{
					Link.l8 = "Ascolta, amico, ho bisogno di una spedizione di vino e rum. Quanto più, tanto meglio.";
					Link.l8.go = "TPZ_smugglers_1";
				}
			// <-- Торговля по закону
			//Jason --> генератор сбыта бакаута
			if(NPChar.location == "Marigo_tavern" && CheckAttribute(PChar, "GenQuest.Bakaut") && !CheckAttribute(PChar, "GenQuest.Bakaut.Info"))
			{
				Link.l9 = "Ho bisogno di incontrare Michael Rosenkraft. Ho la merce che potrebbe interessargli.";
				Link.l9.go = "bakaut";
			}
			// <-- генератор сбыта бакаута
			
			// Церковный генератор №2 -->
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskContra_1") && NPChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_tavern")
			{
				Link.l3 = "Devo scoprire qualcosa, amico.";
				Link.l3.go = "Contra_GenQuest_Church_2_1";
			}
			
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskContra_2") && NPChar.location == PChar.GenQuest.ChurchQuest_2.Contra_Colony + "_tavern")
			{
				Link.l3 = "Un tuo collega e mio buon amico da  "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_2.QuestTown+"Gen")+" ha detto che sei a conoscenza di un certo affare.";
				Link.l3.go = "Contra_GenQuest_Church_2_Contra2_1";
			}
			// <-- Церковный генератор №2

			Link.l5 = "Niente. Ci vediamo.";
			Link.l5.go = "Exit";				
		break;

		// Церковный генератор №2 -->
		case "Contra_GenQuest_Church_2_1":
			iChurchQuest2_Summ = PChar.GenQuest.ChurchQuest_2.Summ_To_Contra;
			dialog.text = "Non sono un amico per te. E potrebbe costarti caro.";
				link.l1 = "Mh. Ho bisogno di sapere qualcosa che non costi più di "+FindRussianMoneyString(iChurchQuest2_Summ)+".";
				link.l1.go = "Contra_GenQuest_Church_2_2";
			break;
			
		case "Contra_GenQuest_Church_2_2":
			iChurchQuest2_Summ = PChar.GenQuest.ChurchQuest_2.Summ_To_Contra;
			if(sti(PChar.money) >= iChurchQuest2_Summ)
			{
				dialog.text = "Dammi le tue monete. E sappi che non otterrai molto per una somma come questa.";
				link.l1 = "Vedi, mi sono mancati i miei amici. Ero in ritardo per un incontro, e non hanno aspettato per me...";
				link.l1.go = "Contra_GenQuest_Church_2_3";
				AddMOneyToCharacter(PChar, -iChurchQuest2_Summ);
				DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.AskContra_1");
				DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.Summ_To_Contra");
			}
			else
			{
				dialog.text = "Ah, non hai una moneta! Vieni quando avrai del denaro.";
				link.l1 = "Certo, ci sto.";
				link.l1.go = "exit";
			}
			break;
			
		case "Contra_GenQuest_Church_2_3":
				dialog.text = "E perché hai bisogno di me?";
				link.l1 = "Non sono in città e non possiedono una nave. Ecco perché ho pensato: forse alcuni dei tuoi soci di affari hanno fatto loro un favore?";
				link.l1.go = "Contra_GenQuest_Church_2_4";
			break;
			
		case "Contra_GenQuest_Church_2_4":
			sColony = QuestGetColony(PChar.GenQuest.ChurchQuest_2.QuestTown);
			dialog.text = "Capisco... Ho incontrato alcuni ragazzi, hanno detto che devono scappare dall'isola e non importa dove. In questi casi non chiediamo le ragioni, solo del pagamento. Avevamo un viaggio verso "+XI_ConvertString("Colony"+sColony+"Acc")+" , "+XI_ConvertString(locations[FindLocation(sColony+"_Città")].IslandID+"Dat")+" . Possiamo portarti lì, se ci mettiamo d'accordo sul denaro.";
			link.l1 = "Grazie, ma ho la mia propria nave.";
			link.l1.go = "exit";
			sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "8");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sCity", XI_ConvertString("Colony" + sColony + "Acc"));
			AddQuestUserData(sQuestTitle, "sIsland", XI_ConvertString(locations[FindLocation(sColony + "_Town")].IslandID + "Voc"));
			PChar.GenQuest.ChurchQuest_2.AskContra_2 = true;
			PChar.GenQuest.ChurchQuest_2.Contra_Colony = sColony;
		break;
			
		case "Contra_GenQuest_Church_2_Contra2_1":
			dialog.text = "Mai avuto affari con te.";
			link.l1 = "Riusciremo a sistemarlo. Hai portato i miei amici qui poco tempo fa. Ho perso un incontro con "+GetSexPhrase("loro","loro")+".";
			link.l1.go = "Contra_GenQuest_Church_2_Contra2_2";
		break;
			
		case "Contra_GenQuest_Church_2_Contra2_2":
			string sGenLocation = IslandGetLocationFromType(locations[FindLocation(PChar.GenQuest.ChurchQuest_2.Contra_Colony + "_Town")].IslandID, "Shore");
			PChar.GenQuest.ChurchQuest_2.QuestGangShore = sGenLocation;
			PChar.GenQuest.ChurchQuest_2.BanditsInShore = true;
			dialog.text = "Mh, li abbiamo messi a terra a "+XI_ConvertString(sGenLocation+"Gen")+"... Sai, sarebbe meglio che fossero tuoi amici, altrimenti non ti consiglio di disturbarli in altro caso.";
			link.l1 = "Grazie per la tua preoccupazione, ma sono ben armato e molto affascinante.";
			link.l1.go = "exit";
			SetFunctionLocationCondition("Church_GenQuest2_GenerateBandits", sGenLocation, false);
			sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "9");
			AddQuestUserData(sQuestTitle, "sShore", XI_ConvertString(sGenLocation + "Gen")); // belamour gen
			locations[FindLocation(sGenLocation)].DisableEncounters = true;
			SetFunctionTimerCondition("Church_GenQuest2_TimeIsLeft", 0, 0, 1, false);
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.AskContra_2");
		break;
		// <-- Церковный генератор №2

		case "Meeting_1":
			Dialog.Text = "Hm... e come mi riguarda? Probabilmente ti sei perso, capitano. Vai al negozio e vendi o compra lì quello che desideri.";
			Link.l1 = "No, ho bisogno di te.";
			Link.l1.go = "Meeting_2";				
			Link.l2 = "Grazie per il tuo consiglio. Buona giornata.";
			Link.l2.go = "exit";				
		break;

		case "Meeting_2":
			Dialog.Text = "Per cosa?";
			Link.l1 = "Forse, saresti interessato a qualche merce speciale? O forse, hai qualcosa da offrirmi in cambio?"Link.l1.go ="Meeting_3";				
		break;

		case "Meeting_3":
			int iTmp = false;
			int iChIdx, i;

			// поиск мин.  те старшего класса
			for (i=0; i<COMPANION_MAX; i++)
			{
				iChIdx = GetCompanionIndex(GetMainCharacter(), i);
				if (iChIdx>=0)
				{
					sld = GetCharacter(iChIdx);
            		if (GetCharacterShipClass(sld) < ((MOD_SKILL_ENEMY_RATE/5.0) + 1.5)) iTmp = true;
				}
			}
			
			if (iTmp)
			{
				dialog.text = NPCStringReactionRepeat("Perché la prossima volta non prendi un uomo di guerra reale. La tua nave può essere individuata facilmente dal forte. Non rischieremo le nostre teste. Vieni su una piccola nave singola la prossima volta.","Dovrei ripetermi? Trova una nave più piccola e poi ne parleremo.","Sei davvero così idiota? Trovati una scuna o una brigata. Solo in quel caso avremo affari.","Oh, che idiota...","block",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Bene, ti ho capito.","Capisco, volevo solo precisare qualcosa.","No, non un idiota, solo un avaro. Pensavo che qualcosa fosse cambiato. Prenderei qualche pinnace in più...","Guarda allo specchio...",npchar,Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);	
				break;
			}
			bOk  = CheckAttribute(pchar, "GenQuest.contraTravel.active") && (sti(pchar.GenQuest.contraTravel.active) == true);
			bOk2 = CheckAttribute(Pchar, "quest.Contraband.Active") && (sti(Pchar.quest.Contraband.Active) == true);
			bool bOk3 = CheckAttribute(Pchar, "questTemp.pirateStartQuest") && (Pchar.questTemp.pirateStartQuest == "3");
			if (bOk)
			{
			    if (GetQuestPastDayParam("contraTravel") > sti(PChar.GenQuest.contraTravel.days))
				{  // просрочка
					DeleteAttribute(PChar, "GenQuest.contraTravel");
					CloseQuestHeader("Gen_ContrabandTravel");
					bOk = false;
				}
			}

//navy --> PGG
			if (CheckFreeServiceForNPC(NPChar, "Smugglers") != -1)
			{
				Dialog.Text = "Scusa, "+GetSexPhrase("amico","ragazza")+", siamo già impegnati. Torna tra qualche giorno.";
				Link.l1 = "Peccato...";
				Link.l1.go = "Exit";		
				break;
			}
//navy <--

			if (bOk || bOk2 || bOk3)
			{
				Dialog.Text = "Che ne dici se prima finiamo i nostri affari in corso?";
				Link.l1 = "Suppongo tu abbia ragione.";
				Link.l1.go = "Exit";				
			}
			else
			{
                if (npchar.quest.trade_date != lastspeak_date)
    			{
                    npchar.quest.trade_date = lastspeak_date;
                    
                    if (ChangeContrabandRelation(pchar, 0) > 5)
                    {
                        Pchar.quest.contraband.CurrentPlace = SelectSmugglingLocation();
						Pchar.quest.contraband.City = NPChar.city;
                        if (Pchar.quest.contraband.CurrentPlace != "None")//boal fix
                        {
                            if (ChangeContrabandRelation(pchar, 0) >= 70)
                            {
                                Dialog.Text = "So che possiamo fare affari con te. Ti aspetteremo a "+GetConvertStr(Pchar.quest.contraband.CurrentPlace,"LocLables.txt")+".";
                            }
                            else
                            {
            				    Dialog.Text = "Mm... Forse, possiamo trovarti un acquirente. Ti aspetteremo a "+GetConvertStr(Pchar.quest.contraband.CurrentPlace,"LocLables.txt")+".";
            				}
            				Link.l1 = "Bene. Ci vediamo lì.";
            				Link.l1.go = "Smuggling_exit";
        				}
        				else
        				{   //boal fix
                            Dialog.Text = "Nessun affare oggi. Vieni qui domani.";
            				Link.l1 = "Bene.";
            				Link.l1.go = "Exit";
        				}
    				}
    				else
    				{
                        Dialog.Text = "Davvero pensi che qualcuno vorrà lavorare con te dopo tutto questo? Faresti meglio a ritenerti fortunato che non abbiamo mandato i cacciatori di taglie per te.";
        				Link.l1 = "Peccato. Nessuna possibilità per me di diventare un contrabbandiere.";
        				Link.l1.go = "Exit";
    				}
				}
				else
				{
                    Dialog.Text = "Nessun affare oggi. Vieni qui domani.";
    				Link.l1 = "Bene.";
    				Link.l1.go = "Exit";
				}
			}
		break;
////////////////////////////////////////////////////////////////////////////////
//	Корсарское метро
////////////////////////////////////////////////////////////////////////////////
		case "Travel":
//navy --> PGG
			if (CheckFreeServiceForNPC(NPChar, "Smugglers") != -1)
			{
				Dialog.Text = "Scusa, "+GetSexPhrase("amico","ragazza")+", siamo già occupati. Torna tra qualche giorno.";
				Link.l1 = "Peccato.";
				Link.l1.go = "Exit";		
				break;
			}
//navy <--
			//если нет корабля у ГГ и нет компаньонов все ок
			if (sti(pchar.ship.type) == SHIP_NOTUSED && GetCompanionQuantity(pchar) == 1 && GetPassengersQuantity(pchar) == 0)
			{
				//случай если уже была инфа
				if (CheckAttribute(pchar, "GenQuest.contraTravel.active") && sti(pchar.GenQuest.contraTravel.active) == true)
				{
					//платил уже
					if (CheckAttribute(pchar, "GenQuest.contraTravel.payed") && sti(pchar.GenQuest.contraTravel.payed) == true)
					{
						Dialog.Text = "Pensavo che avessimo già concluso l'affare?";
						Link.l2 = "Certo!";
					}
					//не платил, значит можно запалатить пока не вышел срок.
					else
					{
						if(GetQuestPastDayParam("contraTravel") == sti(PChar.GenQuest.contraTravel.days))
						{
							Dialog.Text = "Hai portato i soldi?";
							Link.l1 = "Sì.";
							Link.l1.go = "Travel_pay";
							Link.l3 = "Ho cambiato idea...";
							Link.l3.go = "Travel_abort";
							Link.l2 = "Non ancora.";
						}
						else
						{
                            if (GetQuestPastDayParam("contraTravel") < sti(PChar.GenQuest.contraTravel.days))
							{
								Dialog.Text = "Ti ho già detto tutto.";
								Link.l2 = "Esattamente.";
								Link.l1 = "Ho cambiato idea...";
								Link.l1.go = "Travel_abort";
							}
							else // просрочка
							{
							    Dialog.Text = "Non posso aiutarti oggi. Vieni tra due giorni e forse avremo qualcosa per te.";
								Link.l2 = "Peccato.";
								DeleteAttribute(PChar, "GenQuest.contraTravel");
								CloseQuestHeader("Gen_ContrabandTravel");
							}
						}
					}
				}
				//если не было договора, обговариваем условия
				else
				{
					nRel = ChangeContrabandRelation(pchar, 0);
					//если нормальные отношения и количество подстав меньше 20, работаем....
					if (nRel > 0 && Statistic_AddValue(PChar, "contr_TravelKill", 0) < 20)
					{
						//бухта...
						pchar.GenQuest.contraTravel.CurrentPlace = SelectSmugglingLocation();
						aref arTmp; makearef(arTmp, pchar.GenQuest.contraTravel);
						SetSmugglersTravelDestination(arTmp);
						//за сколько доставят 
						pchar.GenQuest.contraTravel.price = (sti(PChar.rank)*250 + (100 - nRel)*10 + rand(30)*20) + sti(arTmp.destination.days)*100;
						
						//если метро активно, и нет пассажиров у ГГ, и ещё сегодня не виделись, есть доступная бухта, и ранд ...
						bOk = !bPauseContrabandMetro && CheckNPCQuestDate(npchar, "Travel_Talk") && 
							Pchar.GenQuest.contraTravel.CurrentPlace != "None" && rand(50) < nRel;
                        bOk2 = CheckAttribute(Pchar, "quest.Contraband.Active") && (sti(Pchar.quest.Contraband.Active) == true);
						if (bOk && !bOk2)
						{
							nDay = 1 + rand(3);
							SetNPCQuestDate(npchar, "Travel_Talk");
							SaveCurrentQuestDateParam("contraTravel");

							Dialog.Text = "Bene, possiamo portarti a "+GetConvertStr(locations[FindLocation(pchar.GenQuest.contraTravel.destination.loc)].id,"LocLables.txt")+" vicino "+XI_ConvertString("Colony"+pchar.GenQuest.contraTravel.destination+"Gen")+" per "+pchar.GenQuest.contraTravel.price+" oro. Porta i soldi dentro "+FindRussianDaysString(nDay)+". La nave ti aspetterà a "+GetConvertStr(locations[FindLocation(Pchar.GenQuest.contraTravel.CurrentPlace)].id,"LocLables.txt")+" esattamente 24 ore.";

							pchar.GenQuest.contraTravel.days = nDay;
							Link.l1 = "Funziona per me.";
							Link.l1.go = "Travel_agree";
							Link.l2 = "No grazie.";
						}
						else
						{
							Dialog.Text = "Non posso aiutarti oggi. Vieni tra due giorni e forse avremo qualcosa per te.";
							Link.l2 = "Peccato.";
						}
					}
					//нет, посылаем в сад
					else
					{
                        Dialog.Text = "Davvero pensi che qualcuno vorrà lavorare con te dopo tutto questo? Dovresti essere grato che non abbiamo mandato i cacciatori di taglie per te. Vattene!";
        				Link.l2 = "Eh, nessuna fortuna ancora.";
					}

				}
			}
			//корабль есть, посылаем в сад...
			else 
			{
				if(GetPassengersQuantity(pchar) != 0)
				{
					Dialog.Text = "No, non vi porteremo tutti. Solo uno di voi.";
					Link.l2 = RandSwear()+"Non ne ho bisogno comunque!";
				}
				else
				{
					Dialog.Text = "Perché non usi la tua nave? No, non ti porteremo.";
					Link.l2 = "Bene, come desideri.";
				}
			}
			Link.l2.go = "Exit";
			break;

		//отмена
		case "Travel_abort":
			ChangeContrabandRelation(pchar, -2);
			DeleteAttribute(PChar, "GenQuest.contraTravel");
			CloseQuestHeader("Gen_ContrabandTravel");
			Dialog.Text = "Come vuoi.";
			Link.l1 = "";
			Link.l1.go = "Exit";
			break;

		//ГГ согласен ехать
		case "Travel_agree":
			ReOpenQuestHeader("Gen_ContrabandTravel");
			AddQuestRecord("Gen_ContrabandTravel", "1");
			AddQuestUserData("Gen_ContrabandTravel", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Gen_ContrabandTravel", "sLoc", GetConvertStr(pchar.GenQuest.contraTravel.CurrentPlace, "LocLables.txt"));
			AddQuestUserData("Gen_ContrabandTravel", "sLocTo", GetConvertStr(pchar.GenQuest.contraTravel.destination.loc, "LocLables.txt"));
			AddQuestUserData("Gen_ContrabandTravel", "sPlaceTo", XI_ConvertString("Colony" + pchar.GenQuest.contraTravel.destination + "Gen"));
			AddQuestUserData("Gen_ContrabandTravel", "sDays", FindRussianDaysString(sti(pchar.GenQuest.contraTravel.days)));
			AddQuestUserData("Gen_ContrabandTravel", "sPrice", pchar.GenQuest.contraTravel.price);

			//активируем квест
			pchar.GenQuest.contraTravel.active = true;
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			break;

		//ГГ согласен платить
		case "Travel_pay":
			//денег хватает?
			Sum = sti(pchar.GenQuest.contraTravel.price);
			if (sti(pchar.money) >= Sum)
			{
				AddMoneyToCharacter(pchar, -1*Sum);
				//ставим флаг оплаты
				pchar.GenQuest.contraTravel.payed = true;
				Dialog.Text = "È stato un piacere fare affari con te. Non fare tardi sulla nave.";
				Link.l1 = "Cercherò.";
				AddQuestRecord("Gen_ContrabandTravel", "2");
				AddQuestUserData("Gen_ContrabandTravel", "sSex", GetSexPhrase("",""));
				
				//ставим контру.
				PlaceSmugglersOnShore(PChar.GenQuest.contraTravel.CurrentPlace);
				//корабль на волнах в бухте....
				Sum = sti(pchar.GenQuest.contraTravel.destination.days);
				sld = GetCharacter(NPC_GenerateCharacter("Abracham_Gray", "citiz_46", "man", "man", 5, PIRATE, Sum + 2, true, "hunter"));
				//воскресим...
				sld.nation = PIRATE;
				SetRandomNameToCharacter(sld);
				SetMerchantShip(sld, rand(GOOD_PAPRIKA));
				SetFantomParamHunter(sld);
				SetCaptanModelByEncType(sld, "pirate");
				SetCharacterShipLocation(sld, PChar.GenQuest.contraTravel.CurrentPlace);

				SetTimerCondition("RemoveTravelSmugglers", 0, 0, 1, false);
			}
			//нет, посылаем в сад...
			else
			{
				Dialog.Text = "Sembra che tu non abbia abbastanza soldi."Link.l1 ="Che peccato, tornerò più tardi.";
			}
			Link.l1.go = "Exit";
		break;  
////////////////////////////////////////////////////////////////////////////////
//	END OF Корсарское метро
////////////////////////////////////////////////////////////////////////////////
				
		//Jason --> мини-квест Бесчестный конкурент
		case "Shadowtrader_smugglers":
			dialog.text = "Molto interessante. Mostra quello che hai.";
			link.l1 = "Ho sentito dire che c'è un negozio clandestino dove si possono scambiare merci molto 'speciali' a un prezzo allettante e tu hai aiutato a avviare questo negozio. Vorrei parlare con il suo proprietario.";
			link.l1.go = "Shadowtrader_fail";
			link.l2 = "Ho sentito dire che esiste un negozio sotterraneo dove si possono scambiare merci molto 'speciali' a un prezzo allettante. Devo salpare tra qualche giorno e non ho abbastanza soldi per comprare tutto ciò di cui ho bisogno nel negozio locale, quindi ho bisogno e voglio risparmiare qualche moneta... alcune persone mi hanno detto che tu puoi aiutarmi in questo.";
			link.l2.go = "Shadowtrader_smugglers_1";
			DeleteAttribute(pchar, "questTemp.Shadowtrader.seeksmugglers");
			DelLandQuestMark(npchar);
		break;
		
		case "Shadowtrader_fail":
			dialog.text = "Di cosa stai parlando? Non ti capisco. Non abbiamo aperto un negozio qui, è assurdo, ah-ah! Se vuoi fare affari allora portaci delle merci e parleremo nel nostro solito modo... Un negozio, ah!";
			link.l1 = "Mm...";
			link.l1.go = "exit";
			pchar.questTemp.Shadowtrader = "true";
			AddQuestRecord("Shadowtrader", "3");
			CloseQuestHeader("Shadowtrader");
			DeleteAttribute(pchar, "questTemp.Shadowtrader_block");
		break;
		
		case "Shadowtrader_smugglers_1":
			dialog.text = "Vuoi uno sconto? Facile. Vieni alla porta del maestro del porto quando è buio. Il nostro uomo ti incontrerà e ti porterà nel posto giusto. ";
			link.l1 = "Bene. Ci sarò!";
			link.l1.go = "Shadowtrader_smugglers_2";		
		break;
		
		case "Shadowtrader_smugglers_2":
			pchar.questTemp.Shadowtrader.SeekTrader = "true";
			AddLandQuestMarkToPhantom("baster_prison", "basterJailOff");
			AddQuestRecord("Shadowtrader", "5");
			AddQuestUserData("Shadowtrader", "sCity", XI_ConvertString("Colony"+pchar.questTemp.Shadowtrader.City+"Gen"));
			SetFunctionTimerCondition("ShadowtraderTimeSmugglers_Over", 0, 0, 2, false);
			int iNation = pchar.questTemp.Shadowtrader.nation;
			int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+3;
			sld = GetCharacter(NPC_GenerateCharacter("ShadowAgent_1", "citiz_"+(rand(9)+41), "man", "man", iRank, iNation, 2, true, "quest"));
			SetFantomParamFromRank(sld, iRank, true);
			GiveItem2Character(sld, "blade_04");
			EquipCharacterbyItem(sld, "blade_04");
			LAi_SetCitizenType(sld);
			sld.dialog.Filename = "Common_citizen.c";
			sld.dialog.currentnode = "First time";	
			sld.greeting = "cit_common"; 
			sld.city = pchar.questTemp.Shadowtrader.City;
			LAi_SetImmortal(sld, true);
			ChangeCharacterAddressGroup(sld, pchar.questTemp.Shadowtrader.City +"_town", "goto", "goto1");
			pchar.quest.Shadowtrader_SMG.win_condition.l1 = "locator";
			pchar.quest.Shadowtrader_SMG.win_condition.l1.location = pchar.questTemp.Shadowtrader.City + "_town";
			pchar.quest.Shadowtrader_SMG.win_condition.l1.locator_group = "reload";
			pchar.quest.Shadowtrader_SMG.win_condition.l1.locator = "reload10_back";
			pchar.quest.Shadowtrader_SMG.win_condition.l2 = "Night";
			pchar.quest.Shadowtrader_SMG.function = "ShadowAgent";
			DialogExit();
		break;
		// <-- Бесчестный конкурент
		//--> Торговля по закону
		case "TPZ_smugglers_1":
			dialog.text = "Ah, quel furfante dietro il bancone ti ha mandato, vero?";
			link.l1 = "Ha importanza? Puoi prenderlo, o dovrei cercare qualcun altro?";
			link.l1.go = "TPZ_smugglers_2";
			DelLandQuestMark(npchar);
		break;
		
		case "TPZ_smugglers_2":
			dialog.text = "Posso procurarti qualsiasi cosa tu voglia, capisci? Purché il compenso sia adeguato. Ma quel maledetto governatore ha stretto le viti. Non tocchiamo più l'alcol - troppo rumoroso, si può sentire a un miglio di distanza, i profitti sono miseri, e il rischio di danzare alla fine di una corda è altissimo. Quindi, senza offesa.";
			link.l1 = "Mmm... E dici che puoi procurare qualsiasi cosa.";
			link.l1.go = "TPZ_smugglers_3";		
		break;
		
		case "TPZ_smugglers_3":
			dialog.text = "Posso! Solo che non voglio. C'è questo tizio, vive proprio accanto alla residenza del governatore, ci credi? Ha-ha. Che sciocco... Cosa stavo dicendo? Ah, giusto. Lui vende tranquillamente alcol sotto banco. Proprio sotto la parrucca impolverata del governatore, ha-ha. Chiedigli, forse ti darà un indizio. I suoi volumi sono piccoli, roba da bambini veramente, ma è qualcosa.";
			link.l1 = "Non di grande aiuto, ma grazie comunque.";
			link.l1.go = "TPZ_smugglers_4";		
		break;
		
		case "TPZ_smugglers_4":
			DialogExit();
			AddQuestRecord("TPZ", "3");
			DeleteAttribute(pchar, "questTemp.TPZ_ContraInfo");
			
			// проведаем дом Кристиана
			sld = GetCharacter(NPC_GenerateCharacter("TPZ_Kristian", "citiz_17", "man", "man", 1, FRANCE, -1, false, "quest"));
			sld.name = "Christian";
			sld.lastname = "Deluce";
			LAi_SetOwnerType(sld);
			sld.dialog.filename = "Quest\MiniEvents\TradingByLaw_dialog.c";
			sld.dialog.currentnode = "Kristian";
			ChangeCharacterAddressGroup(sld, "BasTer_houseF3", "barmen", "stay");
			sld.City = "BasTer";
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			AddLandQuestMark(sld, "questmarkmain");
		break;
		//<-- Торговля по закону

		//--> Цена чахотки
		case "Consumption":
			dialog.text = "Qui ci sono molti festaioli e se non hai affari, signore, bevi o parla con loro. Questo posto è affollato.";
			link.l1 = "Proviamo di nuovo. Ti pagherò per il tuo tempo e la mia curiosità. Ho bisogno di risposte.";
			link.l1.go = "Consumption_1";
		break;
		
		case "Consumption_1":
			if (sti(pchar.money) >= 3002)
			{
				dialog.text = "Pagherà, ah! Il mio tempo non è a buon mercato, signore, costa 3000 pesos più questa bevanda disgustosa che chiamano erroneamente rum.";
				link.l1 = "Affare fatto! Ora parlami di uno dei tuoi che ha passato metà dell'anno nella prigione locale e poi è passato a miglior vita. Cosa gli è successo?";
				link.l1.go = "Consumption_2";
			}
			else
			{
				dialog.text = "È meglio che riempia le tue tasche con argento o oro, che sarebbe meglio. Poi vieni a parlare, non ho tempo per parlare con te gratuitamente.";
				link.l1 = "...";
				link.l1.go = "exit";
			}
		break;
		
		case "Consumption_2":
			AddMoneyToCharacter(pchar, -3002);
			dialog.text = "Ricordo quello, anche se non capisco perché tu sia interessato. Il ragazzo è davvero impazzito dietro quelle sbarre. È diventato un ubriacone e parlava sempre di qualche assurdità riguardo a un morbo che portava via la gente e da cui nessuno era al sicuro. Diceva che quel morbo aveva un nome e non osava nemmeno pronunciarlo ad alta voce. Se lo fai - verrà a prenderti anche te.";
			link.l1 = "E cosa gli è successo dopo?";
			link.l1.go = "Consumption_3";
		break;
		
		case "Consumption_3":
			dialog.text = "La storia ha una fine strana, signore. All'inizio, a gente del posto e marinai piaceva la sua favola, ma alla fine si erano stancati. Succede sempre con ogni favola. Così lo provocarono a dire il nome. Il poveretto cercava di resistere ma non poteva sopportare le derisioni e lo urlò letteralmente\nNessuno sentì nulla di speciale, le candele non si spensero, ma la povera anima fu trovata morta la mattina seguente dietro la taverna con la gola tagliata.";
			link.l1 = "Non vedo alcuna magia qui. Dimmi il nome.";
			link.l1.go = "Consumption_4";
		break;
		
		case "Consumption_4":
			dialog.text = "Ricordo il nome, ma dannazione, non lo dirò ad alta voce. C'è qualcosa di sinistro in tutto questo. Non vedi?";
			link.l1 = "Ehi, amico, ti ho dato un portafoglio pieno di monete, ricordi? Quindi, potresti gentilmente dirmi il nome?";
			link.l1.go = "Consumption_5";
		break;
		
		case "Consumption_5":
			dialog.text = "Oh non finirà bene, signore, credimi... (abbassando la voce) Ha detto - Juan...";
			link.l1 = "Maledetto tu! Juan? È solo un nome comune ed è piuttosto popolare qui. Perché è così speciale?";
			link.l1.go = "Consumption_6";
		break;
		
		case "Consumption_6":
			dialog.text = "Non lo so, ma l'uomo che ha pronunciato questo nome è stato ucciso. Fidati del mio istinto, c'è qualcosa di molto sbagliato con questo nome. È tutto quello che volevi sapere?";
			link.l1 = "Suppongo di sì. Puoi comprarti da bere. Ci vediamo!";
			link.l1.go = "Consumption_7";
		break;
		
		case "Consumption_7":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.Consumption.Contra");
			pchar.questTemp.Consumption.AskJuan = 0;
			pchar.questTemp.Consumption = "current";
			AddQuestRecord("Consumption", "6");
		break;
		//<-- Цена чахотки
		
		//Jason --> генератор сбыта бакаута
		case "bakaut":
			dialog.text = "È così? Bene. Il signor Rosenkraft ha bisogno di una partita di legno di ferro, ma non meno di "+FindRussianQtyString(sti(pchar.GenQuest.Bakaut.Value))+". Hai abbastanza carico?";
			if (GetSquadronGoods(pchar, GOOD_SANDAL) >= sti(pchar.GenQuest.Bakaut.Value))
			{
				link.l1 = "Certo. Dove posso trovare il signor Rosenkraft?";
				link.l1.go = "bakaut_1";
			}
			else
			{
				link.l1 = "Mh. Non ho così tanto al momento.";
				link.l1.go = "bakaut_no";
			}
		break;
		
		case "bakaut_no":
			dialog.text = "Non disturbare il mio signore Rosenkraft allora. Vieni quando avrai abbastanza carico.";
			link.l1 = "Bene.";
			link.l1.go = "exit";
		break;
		
		case "bakaut_1":
			dialog.text = "La sua galeone sarà in navigazione vicino alle coste di "+XI_ConvertString(pchar.GenQuest.Bakaut.Island+"Gen")+" per diversi giorni. Quindi non fare tardi - potrebbe navigare verso un altro luogo dell'arcipelago.";
			link.l1 = "Bene, accelererò. Grazie!";
			link.l1.go = "bakaut_2";
		break;
		
		case "bakaut_2":
			DialogExit();
			sld = characterFromId("Rozencraft");
			sld.DeckDialogNode = "bakaut";
			DeleteAttribute(sld, "DontDeskTalk"); // можно выслать шлюпку
			pchar.GenQuest.Bakaut.Info = "true";
			ReOpenQuestHeader("Bakaut");
			AddQuestRecord("Bakaut", "1");
			AddQuestUserData("Bakaut", "sIsland", XI_ConvertString(pchar.GenQuest.Bakaut.Island+"Gen"));
			AddQuestUserData("Bakaut", "sDays", FindRussianDaysString(sti(pchar.GenQuest.Bakaut.DaysQty)));
			AddQuestUserData("Bakaut", "sQty", FindRussianQtyString(sti(pchar.GenQuest.Bakaut.Value)));
			// таймер
			pchar.quest.Bakaut_Rozencraft_Find.win_condition.l1 = "Timer";
			pchar.quest.Bakaut_Rozencraft_Find.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.Bakaut_Rozencraft_Find.win_condition.l1.date.day   = GetAddingDataDay(0, 0, sti(pchar.GenQuest.Bakaut.DaysQty));
			pchar.quest.Bakaut_Rozencraft_Find.win_condition.l1.date.month = GetAddingDataMonth(0, 0, sti(pchar.GenQuest.Bakaut.DaysQty));
			pchar.quest.Bakaut_Rozencraft_Find.win_condition.l1.date.year  = GetAddingDataYear(0, 0, sti(pchar.GenQuest.Bakaut.DaysQty));
			pchar.quest.Bakaut_Rozencraft_Find.function = "Bakaut_RozencraftRemove";
		break;
		// <-- генератор сбыта бакаута
		
		//--> прибыла инспекция на Святом Милосердии
		case "SantaMisericordia_1":
			dialog.text = "E ho bisogno di vivere fino a domani. La maledetta 'Mercy' è in città. Vattene.";
			link.l1 = "Così drammatico...";
			link.l1.go = "exit";
		break;
		//<-- прибыла инспекция на Святом Милосердии
	}
}
