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
				dialog.text = "Panowie, opuśćcie to miejsce. Wątpię, czy mamy o czym rozmawiać.";
				link.l1 = "Ach, naprawdę? Nie podoba ci się moja twarz? Dobrze, odchodzę...";
				link.l1.go = "exit";
				break;
			}
			//<-- идёт первая часть квеста Шарля
			//--> Addon-2016 Jason блокировка контры во избежание конфликтов с квестами
			if (CheckAttribute(pchar, "GenQuest.SmugglersBlock") && pchar.GenQuest.SmugglersBlock == npchar.location)
            {
				dialog.text = "Brak interesów dzisiaj.";
				link.l1 = "Widzę.";
				link.l1.go = "exit";
				break;
			}
			//--> прибыла инспекция на Святом Милосердии
			if (CheckAttribute(npchar, "quest.SantaMisericordia"))
			{
				dialog.text = "Ja i moi przyjaciele jesteśmy dzisiaj niezwykle zajęci.";
				link.l1 = "Ale ja potrzebuję...";
				link.l1.go = "SantaMisericordia_1";
				break;
			}
			//<-- прибыла инспекция на Святом Милосердии
			//--> Jason Цена чахотки
			if (CheckAttribute(pchar, "questTemp.Consumption.Contra"))
            {
				dialog.text = "Co chcesz, kapitanie?";
				link.l1 = "Czy możemy trochę porozmawiać?";
				link.l1.go = "Consumption";
				break;
			}
			//<-- Цена чахотки
			
			if(NPChar.quest.meeting == "0")
			{
				Dialog.Text = "Co chcesz, kapitanie? Nie znam twojego imienia i nie mogę ci powiedzieć swojego.";
				Link.l1 = "Jestem kapitanem "+GetFullName(pchar)+".";
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
						dialog.text = "Brak interesów dzisiaj. Patrole są na każdej zatoce, nasz gubernator szuka ładunku, który skonfiskował jakiś kapitan od"+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Imię")+"Acc"))+" "+pchar.GenQuest.CaptainComission.Name+" i zostało przez niego gdzieś schowane.";
						link.l1 = "A gdzie jest ten kapitan"+pchar.GenQuest.CaptainComission.Name+"?";
						link.l1.go = "CapComission_1";
						break;
					}
					else
					{
						dialog.text = "Brak interesów dzisiaj.";
						link.l1 = "Widzę.";
						link.l1.go = "exit";					
						break;
					}
				}

				if(pchar.questTemp.Slavetrader == "FindMayak" && Islands[GetCharacterCurrentIsland(pchar)].id == pchar.questTemp.Slavetrader.EsIsland)
				{
					dialog.text = "Nie ma dzisiaj interesów.";
					link.l1 = "Widzę.";
					link.l1.go = "exit";
					break;
				}
				
				if(npchar.id == "Bridgetown_Smuggler" && CheckAttribute(pchar, "questTemp.BM_BlockSmuggler"))
				{
					dialog.text = "Nie ma dzisiaj interesów.";
					link.l1 = "Widzę.";
					link.l1.go = "exit";
					break;
				}

				Dialog.Text = "Co chcesz, kapitanie?";
				if (LAi_group_GetPlayerAlarm() > 0)
				{
	       			Dialog.Text = RandPhraseSimple("Bądź szybki, "+GetSexPhrase("kumpel","dziewczyna")+", co chcesz? Gonią cię!","Mów swoją sprawę i rób to szybko! Żołnierze cię gonią i nie mamy dużo czasu...");
				}
				// belamour legendary edition
				bOk2 = MCGovernon || MCAdmiral;
				if(FindContrabandGoods(PChar) != -1 && !bOk2)
				{
					Link.l1 = "Chciałbym coś kupić lub sprzedać.";
					Link.l1.go = "Meeting_3";
				}

				if (CheckAttribute(pchar, "GenQuest.contraTravel.active") && sti(pchar.GenQuest.contraTravel.active) == true)
					Link.l2 = "O podróży...";
				else
					Link.l2 = "Muszę dotrzeć do jednego miejsca.";
				Link.l2.go = "Travel";
				if (CheckCharacterItem(pchar, "CaptainBook") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakSmuggler"))
				{
					if((pchar.questTemp.different.GiveShipLetters.city == npchar.city) && CheckAttribute(pchar, "questTemp.different.GiveShipLetters"))
					{
						link.l3 = "Mam 'specjalny' towar i myślę, że mógłby cię zainteresować. Rzuć okiem!";
						link.l3.go = "SM_ShipLetters_1";
					}	
				}				

				//Jason --> мини-квест Бесчестный конкурент
				if(CheckAttribute(PChar, "questTemp.Shadowtrader.seeksmugglers") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_tavern")
				{
					Link.l8 = "Mam dla ciebie niezwykły interes.";
					Link.l8.go = "Shadowtrader_smugglers";
				}
				// <-- мини-квест Бесчестный конкурент
				
				//--> Торговля по закону
				if(CheckAttribute(PChar, "questTemp.TPZ_ContraInfo") && NPChar.location == "BasTer_tavern")
				{
					Link.l8 = "Słuchaj, przyjacielu, potrzebuję partii wina i rumu. Dużo i szybko.";
					Link.l8.go = "TPZ_smugglers_1";
				}
				// <-- Торговля по закону

				//Jason --> генератор сбыта бакаута
				if(NPChar.location == "Marigo_tavern" && CheckAttribute(PChar, "GenQuest.Bakaut") && !CheckAttribute(PChar, "GenQuest.Bakaut.Info"))
				{
					Link.l9 = "Muszę spotkać się z Michaelem Rosenkraftem. Mam ładunek, który go zainteresuje.";
					Link.l9.go = "bakaut";
				}
				// <-- генератор сбыта бакаута
				
				// Церковный генератор №2 -->
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskContra_1") && NPChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_tavern")
				{
					Link.l4 = "Muszę coś dowiedzieć się, kumplu.";
					Link.l4.go = "Contra_GenQuest_Church_2_1";
				}
				
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskContra_2") && NPChar.location == PChar.GenQuest.ChurchQuest_2.Contra_Colony + "_tavern")
				{
					Link.l5 = "Kolega z twojego grona i mój dobry przyjaciel z  "+XI_ConvertString("Kolonia"+PChar.GenQuest.ChurchQuest_2.QuestTown+"Gen")+" powiedział, że jesteś świadomy pewnych interesów.";
					Link.l5.go = "Contra_GenQuest_Church_2_Contra2_1";
				}
				// <-- Церковный генератор №2
				
				Link.l7 = "Nic. Do zobaczenia.";
				Link.l7.go = "Exit";				
			}
		break;
		
		case "CapComission_1":
			if(pchar.GenQuest.CaptainComission.variant == "A2")
			{
				dialog.text = "W piwnicy fortu, gdzie indziej? Ten kapitan może ujawnić skład władzom w dowolnym momencie i dla nas nic nie zostanie. Nie myśl o żadnym interesie, dopóki ten zamęt się nie skończy.";
				link.l1 = "Słuchaj, znasz każdy kawałek tej wyspy. Naprawdę nie masz pojęcia, gdzie jest kapitan "+pchar.GenQuest.CaptainComission.Name+"schowek jest?";
				link.l1.go = "CapComission_4";
			}
			if(pchar.GenQuest.CaptainComission.variant == "A3")
			{
				dialog.text = "Do niebios, zgaduję. Został powieszony razem z załogą. Ale w wyroku śmierci nie wspomniano, że to był piracki statek.";
				link.l1 = "A dlaczego jesteś tak pewien, że to była piracka łajba?";
				link.l1.go = "CapComission_2";
			}	
		break;
		
		case "CapComission_2":
			dialog.text = "Obserwowaliśmy walkę ze skały. W lunetce zobaczyliśmy statek pod Jolly Roger. Potem, jakieś pięć godzin później, zobaczyliśmy błysk w ciemności, wyglądało to na wybuch z prochowni. Wystarczająco dużo czasu, aby przemieścić ładunek na brzeg.";
			link.l1 = "Czy nie wiesz, gdzie jest kapitan "+pchar.GenQuest.CaptainComission.Name+"'s stash? Znasz każdy kawałek tej wyspy.";
			link.l1.go = "CapComission_3";
		break;
		
		case "CapComission_3":
			dialog.text = "Nie. I my też go szukamy, ale nie dla rozrywki gubernatora...";
			link.l1 = "Rozumiem.... Miłego dnia.";
			link.l1.go = "exit";
			AddQuestRecord("CaptainComission2", "38");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Acc")));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sShipTypeQuest", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name") + "Gen")));
		break;
		
		case "CapComission_4":
			dialog.text = "Nie. A my też go szukamy, ale nie dla rozrywki gubernatora... he-he";
			link.l1 = "Rozumiem... Miłego dnia.";
			link.l1.go = "exit";
			AddQuestRecord("CaptainComission2", "19");
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Gen"))); // belamour gen
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
		break;
				
		case "SM_ShipLetters_1":
			pchar.questTemp.different.GiveShipLetters.speakSmuggler = true;
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 0)
			{
				dialog.text = "Dlaczego tak postanowiłeś? Jestem uczciwym przemytnikiem. Szukaj innego nabywcy.";
				link.l1 = "Dzięki...";
				link.l1.go = "exit";
			}
			else
			{
				if(!CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakUsurer_1"))
				{
					dialog.text = "Dlaczego nie? Może znajdę zastosowanie dla twojego 'ładunku'. Weź "+sti(pchar.questTemp.different.GiveShipLetters.price2)+" monety i zapomnij o tym.";
					link.l1 = "Nie, dziękuję.";
					link.l1.go = "SM_ShipLetters_2";	
					link.l2 = "I zgadłeś to poprawnie, zaczynam o tym zapominać!";
					link.l2.go = "SM_ShipLetters_3";
				}
				else
				{
					if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 1)
					{
						dialog.text = "Dokładnie! Teraz jestem naprawdę ciekawy. Przypuszczam, że jeśli ci zapłacę "+sti(pchar.questTemp.different.GiveShipLetters.price3)+" monet nie będzie ci wcale zależało na tych papierach.";
						link.l1 = "Nie, dziękuję.";
						link.l1.go = "SM_ShipLetters_2";
						link.l2 = "I masz rację. Już o nich zapomniałem.";
						link.l2.go = "SM_ShipLetters_3";
					}
					if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 2)
					{
						dialog.text = "Teraz to jest szansa, żeby złapać tego bezczelnego faceta! Naprawdę, naprawdę jestem ciekaw. Słuchaj, zapłacę ci "+sti(pchar.questTemp.different.GiveShipLetters.price4)+" w złocie i całkowicie zapomnisz o dokumentach na stole?";
						link.l1 = "Nie zrobię tego.";
						link.l1.go = "SM_ShipLetters_2";
						link.l2 = "Dobrze, umowa stoi!";
						link.l2.go = "SM_ShipLetters_3";
					}
				}
			}
		break;
		
		case "SM_ShipLetters_2":
			dialog.text = "Dobrze, dobrze, ale przestań tworzyć więcej wrogów.";
			link.l1 = "Również ci życzę!";
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
					dialog.text = "Nie ma dziś żadnych interesów. Patroluje każdą zatokę, nasz gubernator szuka ładunku, który został skonfiskowany przez pewnego kapitana."+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Imię")+"Acc"))+" "+pchar.GenQuest.CaptainComission.Name+" a schował to gdzieś.";
					link.l1 = "A gdzie jest ten kapitan"+pchar.GenQuest.CaptainComission.Name+"?";
					link.l1.go = "CapComission_1";
					break;
				}
				else
				{
					dialog.text = "Nie ma dzisiaj interesów.";
					link.l1 = "Widzę.";
					link.l1.go = "exit";					
					break;
				}
			}
			
			if(pchar.questTemp.Slavetrader == "FindMayak" && Islands[GetCharacterCurrentIsland(pchar)].id == pchar.questTemp.Slavetrader.EsIsland)
			{
				dialog.text = "Nie ma interesów dzisiaj.";
				link.l1 = "Widzę.";
				link.l1.go = "exit";
				break;
			}
			
			if(npchar.id == "Bridgetown_Smuggler" && CheckAttribute(pchar, "questTemp.BM_BlockSmuggler"))
			{
				dialog.text = "Brak interesu dzisiaj.";
				link.l1 = "Widzę.";
				link.l1.go = "exit";
				break;
			}
			
			Dialog.Text = "Jak mogę ci pomóc, kapitanie?";
			
			bOk2 = MCGovernon || MCAdmiral;
			if(FindContrabandGoods(PChar) != -1 && !bOk2)
			{
				Link.l1 = "Chcę coś kupić lub sprzedać.";
				Link.l1.go = "Meeting_1";
			}
			
			Link.l2 = "Muszę dostać się do jednego miejsca.";
			Link.l2.go = "Travel";				
			
			//Jason --> мини-квест Бесчестный конкурент
			if(CheckAttribute(PChar, "questTemp.Shadowtrader.seeksmugglers") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_tavern")
			{
				Link.l8 = "Mam dla ciebie dość nietypowy interes.";
				Link.l8.go = "Shadowtrader_smugglers";
			}
			// <-- мини-квест Бесчестный конкурент
			
			//--> Торговля по закону
			if(CheckAttribute(PChar, "questTemp.TPZ_ContraInfo") && NPChar.location == "BasTer_tavern")
			{
				Link.l8 = "Słuchaj, przyjacielu, potrzebuję partii wina i rumu. Dużo i szybko.";
				Link.l8.go = "TPZ_smugglers_1";
			}
			// <-- Торговля по закону

			//Jason --> генератор сбыта бакаута
			if(NPChar.location == "Marigo_tavern" && CheckAttribute(PChar, "GenQuest.Bakaut") && !CheckAttribute(PChar, "GenQuest.Bakaut.Info"))
			{
				Link.l9 = "Muszę spotkać się z Michaelem Rosenkraftem. Mam ładunek, który go zainteresuje.";
				Link.l9.go = "bakaut";
			}
			// <-- генератор сбыта бакаута
			
			// Церковный генератор №2 -->
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskContra_1") && NPChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_tavern")
			{
				Link.l3 = "Muszę coś dowiedzieć się, kumpel.";
				Link.l3.go = "Contra_GenQuest_Church_2_1";
			}
			
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskContra_2") && NPChar.location == PChar.GenQuest.ChurchQuest_2.Contra_Colony + "_tavern")
			{
				Link.l3 = "Kolega z twojej załogi i mój dobry przyjaciel z  "+XI_ConvertString("Colonia"+PChar.GenQuest.ChurchQuest_2.QuestTown+"Gen")+" powiedział, że wiesz o pewnym interesie.";
				Link.l3.go = "Contra_GenQuest_Church_2_Contra2_1";
			}
			// <-- Церковный генератор №2

			Link.l5 = "Nic. Do zobaczenia.";
			Link.l5.go = "Exit";				
		break;

		// Церковный генератор №2 -->
		case "Contra_GenQuest_Church_2_1":
			iChurchQuest2_Summ = PChar.GenQuest.ChurchQuest_2.Summ_To_Contra;
			dialog.text = "Nie jestem dla ciebie kumplem. I może cię to kosztować.";
				link.l1 = "Hm. Muszę wiedzieć coś, co kosztuje nie więcej niż "+FindRussianMoneyString(iChurchQuest2_Summ)+".";
				link.l1.go = "Contra_GenQuest_Church_2_2";
			break;
			
		case "Contra_GenQuest_Church_2_2":
			iChurchQuest2_Summ = PChar.GenQuest.ChurchQuest_2.Summ_To_Contra;
			if(sti(PChar.money) >= iChurchQuest2_Summ)
			{
				dialog.text = "Daj mi swoje monety. I wiedz, że za taką sumę nie dostaniesz wiele.";
				link.l1 = "Widzisz, tęskniłem za moimi przyjaciółmi. Spóźniłem się na spotkanie, a oni na mnie nie poczekali...";
				link.l1.go = "Contra_GenQuest_Church_2_3";
				AddMOneyToCharacter(PChar, -iChurchQuest2_Summ);
				DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.AskContra_1");
				DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.Summ_To_Contra");
			}
			else
			{
				dialog.text = "Ha, nie masz monety! Przyjdź, kiedy zdobędziesz trochę pieniędzy.";
				link.l1 = "Rzeczywiście, zajmę się tym.";
				link.l1.go = "exit";
			}
			break;
			
		case "Contra_GenQuest_Church_2_3":
				dialog.text = "A dlaczego mnie potrzebujesz?";
				link.l1 = "Oni nie są w mieście i nie mają statku. Dlatego pomyślałem: może niektórzy z twoich partnerów biznesowych zrobili im przysługę?";
				link.l1.go = "Contra_GenQuest_Church_2_4";
			break;
			
		case "Contra_GenQuest_Church_2_4":
			sColony = QuestGetColony(PChar.GenQuest.ChurchQuest_2.QuestTown);
			dialog.text = "Rozumiem... Spotkałem kilku facetów, powiedzieli, że muszą uciec z wyspy i nie obchodziło ich dokąd. W takich przypadkach nie pytamy o powody, tylko o zapłatę. Mieliśmy rejs do "+XI_ConvertString("Colony"+sColony+"Acc")+" , "+XI_ConvertString(locations[FindLocation(sColony+"_Miasto")].IslandID+"To")+" . Możemy cię tam zawieźć, jeśli się zgodzimy co do pieniędzy.";
			link.l1 = "Dzięki, ale mam swój własny statek.";
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
			dialog.text = "Nigdy nie prowadziłem z tobą interesów.";
			link.l1 = "Możemy to naprawić. Przywiozłeś moich przyjaciół tu niedawno. Przegapiłem spotkanie z "+GetSexPhrase("ich","oni")+".";
			link.l1.go = "Contra_GenQuest_Church_2_Contra2_2";
		break;
			
		case "Contra_GenQuest_Church_2_Contra2_2":
			string sGenLocation = IslandGetLocationFromType(locations[FindLocation(PChar.GenQuest.ChurchQuest_2.Contra_Colony + "_Town")].IslandID, "Shore");
			PChar.GenQuest.ChurchQuest_2.QuestGangShore = sGenLocation;
			PChar.GenQuest.ChurchQuest_2.BanditsInShore = true;
			dialog.text = "Hm, wysadziliśmy ich na brzeg przy "+XI_ConvertString(sGenLocation+"Gen")+"... Wiesz, lepiej, żeby byli twoimi przyjaciółmi, bo inaczej nie radzę ci ich przeszkadzać.";
			link.l1 = "Dzięki za troskę, ale jestem dobrze uzbrojony i bardzo uroczy.";
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
			Dialog.Text = "Hm... a jak to mnie dotyczy? Chyba się zgubiłeś, kapitanie. Idź do sklepu i sprzedaj tam albo kup, co tylko chcesz.";
			Link.l1 = "Nie, potrzebuję cię.";
			Link.l1.go = "Meeting_2";				
			Link.l2 = "Dzięki za twoją radę. Miłego dnia.";
			Link.l2.go = "exit";				
		break;

		case "Meeting_2":
			Dialog.Text = "Za co?";
			Link.l1 = "Być może zainteresują Cię jakieś specjalne towary? A może masz coś do zaoferowania mi w zamian?"Link.l1.go ="Spotkanie_3";				
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
				dialog.text = NPCStringReactionRepeat("Dlaczego następnym razem nie weźmiesz królewskiego okrętu wojennego. Twój statek można łatwo dostrzec z fortu. Nie będziemy ryzykować naszych głów. Przyjdź następnym razem na jednym małym statku.","Czy powinienem powtarzać? Znajdź mniejszy statek, a potem porozmawiamy.","Czy naprawdę jesteś takim idiota? Znajdź sobie szkuner lub bryg. Tylko wtedy będziemy mieć interesy.","Och, taki idiota...","block",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Dobrze, zrozumiałem cię.","Rozumiem, chciałem tylko coś doprecyzować.","Nie, nie idiota, tylko skąpiec. Myślałem, że coś się zmieniło. Wziąłbym jeszcze kilka pinnasów...","Spójrz w lustro...",npchar,Dialog.CurrentNode);
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
				Dialog.Text = "Przepraszam, "+GetSexPhrase("kumpel","dziewczyna")+", jesteśmy już zajęci. Wróć za kilka dni.";
				Link.l1 = "Szkoda...";
				Link.l1.go = "Exit";		
				break;
			}
//navy <--

			if (bOk || bOk2 || bOk3)
			{
				Dialog.Text = "A może najpierw skończymy nasze obecne sprawy?";
				Link.l1 = "Przypuszczam, że masz rację.";
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
                                Dialog.Text = "Wiem, że możemy z tobą handlować. Będziemy czekać na "+GetConvertStr(Pchar.quest.contraband.CurrentPlace,"LocLables.txt")+".";
                            }
                            else
                            {
            				    Dialog.Text = "Hm... Być może, znajdziemy dla ciebie kupca. Będziemy na ciebie czekać w "+GetConvertStr(Pchar.quest.contraband.CurrentPlace,"LocLables.txt")+".";
            				}
            				Link.l1 = "W porządku. Do zobaczenia tam.";
            				Link.l1.go = "Smuggling_exit";
        				}
        				else
        				{   //boal fix
                            Dialog.Text = "Nie ma dzisiaj interesów. Przyjdź tu jutro.";
            				Link.l1 = "Dobrze.";
            				Link.l1.go = "Exit";
        				}
    				}
    				else
    				{
                        Dialog.Text = "Czy naprawdę myślisz, że ktoś będzie chciał z tobą pracować po tym wszystkim? Lepiej ciesz się, że nie wysłaliśmy za tobą łowców nagród.";
        				Link.l1 = "Szkoda. Nie mam szansy stać się przemytnikiem.";
        				Link.l1.go = "Exit";
    				}
				}
				else
				{
                    Dialog.Text = "Nie ma interesów dzisiaj. Przyjdź tu jutro.";
    				Link.l1 = "Dobrze.";
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
				Dialog.Text = "Przepraszam, "+GetSexPhrase("kumpel","dziewczyna")+", jesteśmy już zajęci. Wróć za kilka dni.";
				Link.l1 = "Szkoda.";
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
						Dialog.Text = "Miałem wrażenie, że już załatwiliśmy ten interes?";
						Link.l2 = "Rzeczywiście!";
					}
					//не платил, значит можно запалатить пока не вышел срок.
					else
					{
						if(GetQuestPastDayParam("contraTravel") == sti(PChar.GenQuest.contraTravel.days))
						{
							Dialog.Text = "Czy przyniosłeś pieniądze?";
							Link.l1 = "Tak.";
							Link.l1.go = "Travel_pay";
							Link.l3 = "Zmieniłem zdanie...";
							Link.l3.go = "Travel_abort";
							Link.l2 = "Jeszcze nie.";
						}
						else
						{
                            if (GetQuestPastDayParam("contraTravel") < sti(PChar.GenQuest.contraTravel.days))
							{
								Dialog.Text = "Już ci wszystko powiedziałem.";
								Link.l2 = "Dokładnie.";
								Link.l1 = "Zmieniłem zdanie...";
								Link.l1.go = "Travel_abort";
							}
							else // просрочка
							{
							    Dialog.Text = "Nie mogę ci dzisiaj pomóc. Przyjdź za dwa dni, a może znajdziemy coś dla ciebie.";
								Link.l2 = "Szkoda.";
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

							Dialog.Text = "No cóż, możemy cię dostać do "+GetConvertStr(locations[FindLocation(pchar.GenQuest.contraTravel.destination.loc)].id,"LocLables.txt")+" blisko "+XI_ConvertString("Kolonia"+pchar.GenQuest.contraTravel.destination+"Gen")+" za "+pchar.GenQuest.contraTravel.price+" złoto. Przynieś pieniądze "+FindRussianDaysString(nDay)+". Statek będzie na ciebie czekać przy "+GetConvertStr(locations[FindLocation(Pchar.GenQuest.contraTravel.CurrentPlace)].id,"LocLables.txt")+" dokładnie 24 godziny.";

							pchar.GenQuest.contraTravel.days = nDay;
							Link.l1 = "Jestem za.";
							Link.l1.go = "Travel_agree";
							Link.l2 = "Nie, dziękuję.";
						}
						else
						{
							Dialog.Text = "Nie mogę ci dzisiaj pomóc. Przyjdź za dwa dni, a może będziemy mieć coś dla ciebie.";
							Link.l2 = "Szkoda.";
						}
					}
					//нет, посылаем в сад
					else
					{
                        Dialog.Text = "Czy naprawdę myślisz, że ktoś będzie chciał z tobą współpracować po tym wszystkim? Powinieneś być wdzięczny, że nie wysłaliśmy za tobą łowców nagród. Znikaj!";
        				Link.l2 = "Ech, znowu pech.";
					}

				}
			}
			//корабль есть, посылаем в сад...
			else 
			{
				if(GetPassengersQuantity(pchar) != 0)
				{
					Dialog.Text = "Nie, nie zabierzemy was wszystkich. Tylko jednego z was.";
					Link.l2 = RandSwear()+"I tak tego nie potrzebuję!";
				}
				else
				{
					Dialog.Text = "Dlaczego nie użyjesz swojego własnego statku? Nie, nie zabierzemy Cię.";
					Link.l2 = "Dobrze, jak sobie życzysz.";
				}
			}
			Link.l2.go = "Exit";
			break;

		//отмена
		case "Travel_abort":
			ChangeContrabandRelation(pchar, -2);
			DeleteAttribute(PChar, "GenQuest.contraTravel");
			CloseQuestHeader("Gen_ContrabandTravel");
			Dialog.Text = "Cokolwiek chcesz.";
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
				Dialog.Text = "Miło było z tobą robić interesy. Nie spóźnij się na statek.";
				Link.l1 = "Spróbuję.";
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
				Dialog.Text = "Wygląda na to, że nie masz wystarczająco dużo pieniędzy."Link.l1 ="Jaka szkoda, wrócę później.";
			}
			Link.l1.go = "Exit";
		break;  
////////////////////////////////////////////////////////////////////////////////
//	END OF Корсарское метро
////////////////////////////////////////////////////////////////////////////////
				
		//Jason --> мини-квест Бесчестный конкурент
		case "Shadowtrader_smugglers":
			dialog.text = "Bardzo interesujące. Pokaż co masz.";
			link.l1 = "Słyszałem, że istnieje podziemny sklep, gdzie można handlować bardzo 'specjalnymi' towarami po kuszącej cenie, a ty pomogłeś go rozpocząć. Chciałbym porozmawiać z jego właścicielem.";
			link.l1.go = "Shadowtrader_fail";
			link.l2 = "Słyszałem, że jest podziemny sklep, gdzie można handlować bardzo 'specjalnymi' towarami za kuszącą cenę. Muszę odpłynąć za kilka dni i nie mam wystarczająco dużo pieniędzy, aby kupić wszystko, czego potrzebuję w lokalnym sklepie, więc potrzebuję i chcę zaoszczędzić trochę monety... niektórzy ludzie mówili mi, że możesz mi w tym pomóc.";
			link.l2.go = "Shadowtrader_smugglers_1";
			DeleteAttribute(pchar, "questTemp.Shadowtrader.seeksmugglers");
			DelLandQuestMark(npchar);
		break;
		
		case "Shadowtrader_fail":
			dialog.text = "O czym ty mówisz? Nie rozumiem cię. Nie zaczęliśmy tutaj sklepu, to nonsens, ha-ha! Jeśli chcesz handlować, przynieś nam towary, a my porozmawiamy w nasz zwykły sposób... Sklep, ha!";
			link.l1 = "Hm...";
			link.l1.go = "exit";
			pchar.questTemp.Shadowtrader = "true";
			AddQuestRecord("Shadowtrader", "3");
			CloseQuestHeader("Shadowtrader");
			DeleteAttribute(pchar, "questTemp.Shadowtrader_Block");
		break;
		
		case "Shadowtrader_smugglers_1":
			dialog.text = "Chcesz zniżki? Łatwo. Przyjdź do drzwi kapitana portu, gdy będzie ciemno. Nasz człowiek spotka się z tobą i zaprowadzi cię we właściwe miejsce. ";
			link.l1 = "Dobrze. Będę tam!";
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
			dialog.text = "Ha, ten łajdak zza lady cię przysłał, co?";
			link.l1 = "A co to za różnica? Dasz radę to załatwić, czy mam szukać kogoś innego?";
			link.l1.go = "TPZ_smugglers_2";
			DelLandQuestMark(npchar);
		break;
		
		case "TPZ_smugglers_2":
			dialog.text = "Mogę zdobyć wszystko, kumasz? Byleby płacili porządnie. Ale ten przeklęty gubernator całkiem nas przycisnął. Z alkoholem już się nie bawimy – szkło brzęczy, słychać z daleka, zysk żaden, a ryzyko zawisnąć na szubienicy ogromne. Więc wybacz.";
			link.l1 = "Tia... A mówisz, że możesz wszystko zdobyć.";
			link.l1.go = "TPZ_smugglers_3";		
		break;
		
		case "TPZ_smugglers_3":
			dialog.text = "Bo mogę! Po prostu nie chcę. Jest tu jeden facet, mieszka tuż obok rezydencji, wyobrażasz sobie? Ha-ha. Co za głupek... Gdzie to ja? A, tak. On po cichu handluje jakimś alkoholem spod lady. Prosto pod nosem gubernatora, ha-ha. Zapytaj go, może coś ci podpowie. Ilości ma dziecięce, ale zawsze coś.";
			link.l1 = "Niewiele pomogłeś, ale dzięki i za to.";
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
			dialog.text = "Jest tu wielu biesiadników i jeśli nie masz tu żadnych spraw, panie, napij się lub porozmawiaj z nimi. To miejsce jest zatłoczone.";
			link.l1 = "Spróbujmy jeszcze raz. Zapłacę ci za twój czas i moją ciekawość. Potrzebuję odpowiedzi.";
			link.l1.go = "Consumption_1";
		break;
		
		case "Consumption_1":
			if (sti(pchar.money) >= 3002)
			{
				dialog.text = "On zapłaci, ha! Mój czas nie jest tani, panie, kosztuje 3000 pesos plus ten obrzydliwy napój, który błędnie nazywają rumem.";
				link.l1 = "Zgoda! Teraz opowiedz mi o jednym z twoich, który spędził pół roku w miejscowym więzieniu, a potem odszedł. Co się z nim stało?";
				link.l1.go = "Consumption_2";
			}
			else
			{
				dialog.text = "Lepiej napełnij swoje kieszenie srebrem lub co lepiej złotem. Potem przyjdź i pogadaj, nie mam czasu rozmawiać z tobą za darmo.";
				link.l1 = "...";
				link.l1.go = "exit";
			}
		break;
		
		case "Consumption_2":
			AddMoneyToCharacter(pchar, -3002);
			dialog.text = "Pamiętam to, choć nie rozumiem, dlaczego cię to interesuje. Ten dzieciak naprawdę oszalał za tymi kratami. Stał się pijakiem i zawsze gadał jakieś bzdury o spożyciu, które zabierało ludzi i nikt nie był przed nim bezpieczny. Mówił, że to spożycie ma imię i nawet nie śmiej go głośno wymawiać. Jeśli to zrobisz - przyjdzie i zabierze także ciebie.";
			link.l1 = "I co się z nim potem stało?";
			link.l1.go = "Consumption_3";
		break;
		
		case "Consumption_3":
			dialog.text = "Historia ma dziwny koniec, seniorze. Początkowo miejscowi i marynarze lubili jego opowieść, ale w końcu mieli jej dość. Zawsze tak jest z każdą bajką. Więc sprowokowali go, by powiedział imię. Chłopak stawiał opór, ale nie mógł znieść drwin i dosłownie wykrzyczał je\nNikt niczego specjalnego nie poczuł, świece nie zgasły, ale biedna dusza została znaleziona martwa następnego ranka za karczmą z przeciętym gardłem.";
			link.l1 = "Nie widzę tu żadnej magii. Powiedz mi imię.";
			link.l1.go = "Consumption_4";
		break;
		
		case "Consumption_4":
			dialog.text = "Pamiętam to nazwisko, ale do diabła, nie powiem tego na głos. W tym wszystkim jest coś złowieszczy. Czy tego nie widzisz?";
			link.l1 = "Hej, kumplu, otrzymałeś ode mnie portfel pełen monet, pamiętasz? Więc czy mógłbyś mi uprzejmie powiedzieć imię?";
			link.l1.go = "Consumption_5";
		break;
		
		case "Consumption_5":
			dialog.text = "Oh, nie skończy się dobrze, señor, uwierz mi... (ściszając głos) Powiedział - Juan...";
			link.l1 = "Cholera, z tobą! Juan? To tylko zwyczajne imię i jest tutaj dość popularne. Dlaczego jest takie wyjątkowe?";
			link.l1.go = "Consumption_6";
		break;
		
		case "Consumption_6":
			dialog.text = "Nie wiem, ale człowiek, który wymienił to imię, został zabity. Ufaj moim przeczuciom, coś jest bardzo nie tak z tym imieniem. Czy to wszystko, co chciałeś wiedzieć?";
			link.l1 = "Zakładam, że tak. Możesz kupić sobie drinka. Do zobaczenia!";
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
			dialog.text = "Czy tak? Dobrze. Mynheer Rosenkraft potrzebuje partii żelaznodrzewa, ale nie mniej niż "+FindRussianQtyString(sti(pchar.GenQuest.Bakaut.Value))+". Czy masz wystarczająco dużo ładunku?";
			if (GetSquadronGoods(pchar, GOOD_SANDAL) >= sti(pchar.GenQuest.Bakaut.Value))
			{
				link.l1 = "Tak. Gdzie mogę znaleźć pana Rosenkrafta?";
				link.l1.go = "bakaut_1";
			}
			else
			{
				link.l1 = "Hm. Nie mam teraz tyle.";
				link.l1.go = "bakaut_no";
			}
		break;
		
		case "bakaut_no":
			dialog.text = "Nie przeszkadzaj panu Rosenkraftowi. Przyjdź, kiedy będziesz miał wystarczająco dużo ładunku.";
			link.l1 = "Dobrze.";
			link.l1.go = "exit";
		break;
		
		case "bakaut_1":
			dialog.text = "Jego galeon będzie krążyć blisko brzegów "+XI_ConvertString(pchar.GenQuest.Bakaut.Island+"Gen")+" przez kilka dni. Więc nie spóźniaj się - może popłynąć do innego miejsca archipelagu.";
			link.l1 = "Dobrze, przyspieszę. Dzięki!";
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
			dialog.text = "A ja muszę dożyć do jutra. Przeklęta 'Łaska' jest w mieście. Wyjdź.";
			link.l1 = "Takie dramaty...";
			link.l1.go = "exit";
		break;
		//<-- прибыла инспекция на Святом Милосердии
	}
}
