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
				if (Pchar.quest.contraband.CurrentPlace == "shore30" || Pchar.quest.contraband.CurrentPlace == "shore31")
				{
					AddQuestUserData("Gen_Contraband", "sIsland", "Marie Galante");
				}
				if (Pchar.quest.contraband.CurrentPlace == "shore59")
				{
					AddQuestUserData("Gen_Contraband", "sIsland", "Tobago");
				}
				AddQuestUserData("Gen_Contraband", "sIsland", XI_ConvertString(GetIslandByCityName(npchar.city)));
			}
			AddQuestUserData("Gen_Contraband", "sLoc", GetConvertStr(Pchar.quest.contraband.CurrentPlace, "LocLables.txt"));
				
			DialogExit();
		break;
		
		case "First time":											
			//--> Jason если идёт первая часть квеста Шарля
			if (CheckAttribute(pchar, "questTemp.Sharlie.Lock"))
            {
				dialog.text = "Monsieur, hagyja el ezt a helyet. Kétlem, hogy lenne mirôl beszélnünk.";
				link.l1 = "Tényleg? Nem tetszik az arcom? Rendben, elmegyek...";
				link.l1.go = "exit";
				break;
			}
			//<-- идёт первая часть квеста Шарля
			//--> Addon-2016 Jason блокировка контры во избежание конфликтов с квестами
			if (CheckAttribute(pchar, "GenQuest.SmugglersBlock") && pchar.GenQuest.SmugglersBlock == npchar.location)
            {
				dialog.text = "Ma nincs üzlet.";
				link.l1 = "Értem, értem.";
				link.l1.go = "exit";
				break;
			}
			//--> прибыла инспекция на Святом Милосердии
			if (CheckAttribute(npchar, "quest.SantaMisericordia"))
			{
				dialog.text = "A barátaim és én ma nagyon elfoglaltak vagyunk.";
				link.l1 = "De szükségem van...";
				link.l1.go = "SantaMisericordia_1";
				break;
			}
			//<-- прибыла инспекция на Святом Милосердии
			//--> Jason Цена чахотки
			if (CheckAttribute(pchar, "questTemp.Consumption.Contra"))
            {
				dialog.text = "Mit akar, kapitány?";
				link.l1 = "Beszélhetnénk egy kicsit?";
				link.l1.go = "Consumption";
				break;
			}
			//<-- Цена чахотки
			
			if(NPChar.quest.meeting == "0")
			{
				Dialog.Text = "Mit akar, kapitány? Nem tudom a nevét, és az enyémet sem tudom megmondani.";
				Link.l1 = "Kapitány vagyok " + GetFullName(pchar) + ".";
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
						dialog.text = "Ma nincs üzlet. Minden öbölben járôrök járôröznek, a kormányosunk egy rakományt keres, amelyet valami kapitány" + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"név") + "Acc")) + " " + pchar.GenQuest.CaptainComission.Name + " elkobzott, és valahol elrejtette.";
						link.l1 = "És hol van ez a kapitány" + pchar.GenQuest.CaptainComission.Name + "?";
						link.l1.go = "CapComission_1";
						break;
					}
					else
					{
						dialog.text = "Ma nincs üzlet.";
						link.l1 = "Értem, értem.";
						link.l1.go = "exit";					
						break;
					}
				}

				if(pchar.questTemp.Slavetrader == "FindMayak" && Islands[GetCharacterCurrentIsland(pchar)].id == pchar.questTemp.Slavetrader.EsIsland)
				{
					dialog.text = "Ma nincs üzlet.";
					link.l1 = "Értem, értem.";
					link.l1.go = "exit";
					break;
				}
				
				if(npchar.id == "Bridgetown_Smuggler" && CheckAttribute(pchar, "questTemp.BM_BlockSmuggler"))
				{
					dialog.text = "Ma nincs üzlet.";
					link.l1 = "Értem, értem.";
					link.l1.go = "exit";
					break;
				}

				Dialog.Text = "Mit akar, kapitány?";
				if (LAi_group_GetPlayerAlarm() > 0)
				{
	       			Dialog.Text = RandPhraseSimple("Légy gyors, "+ GetSexPhrase("haver","lány") +", mit akarsz? Üldöznek téged!", "Beszélj a dolgodról, és tedd gyorsan! Katonák üldöznek téged, és nincs sok idônk...");
				}
				// belamour legendary edition
				bOk2 = MCGovernon || MCAdmiral;
				if(FindContrabandGoods(PChar) != -1 && !bOk2)
				{
					Link.l1 = "Szeretnék venni vagy eladni valamit.";
					Link.l1.go = "Meeting_3";
				}

				if (CheckAttribute(pchar, "GenQuest.contraTravel.active") && sti(pchar.GenQuest.contraTravel.active) == true)
					Link.l2 = "Az utazásról...";
				else
					Link.l2 = "El kell jutnom egy helyre.";
				Link.l2.go = "Travel";
				if (CheckCharacterItem(pchar, "CaptainBook") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakSmuggler"))
				{
					if((pchar.questTemp.different.GiveShipLetters.city == npchar.city) && CheckAttribute(pchar, "questTemp.different.GiveShipLetters"))
					{
						link.l3 = "Van egy 'special' stuffom, és úgy gondolom, hogy téged is érdekelne. Nézd meg!";
						link.l3.go = "SM_ShipLetters_1";
					}	
				}				

				//Jason --> мини-квест Бесчестный конкурент
				if(CheckAttribute(PChar, "questTemp.Shadowtrader.seeksmugglers") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_tavern")
				{
					Link.l8 = "Van egy szokatlan üzletem a számodra.";
					Link.l8.go = "Shadowtrader_smugglers";
				}
				// <-- мини-квест Бесчестный конкурент
				//--> Торговля по закону
				if(CheckAttribute(PChar, "questTemp.TPZ_ContraInfo") && NPChar.location == "BasTer_tavern")
				{
					Link.l8 = "Figyelj, barátom, szükségem van egy szállítmány borra és rumra. Minél többet, annál gyorsabban.";
					Link.l8.go = "TPZ_smugglers_1";
				}
				// <-- Торговля по закону
				//Jason --> генератор сбыта бакаута
				if(NPChar.location == "Marigo_tavern" && CheckAttribute(PChar, "GenQuest.Bakaut") && !CheckAttribute(PChar, "GenQuest.Bakaut.Info"))
				{
					Link.l9 = "Találkoznom kell Michael Rosenkrafttal. Van egy rakományom, ami érdekes lehet számára.";
					Link.l9.go = "bakaut";
				}
				// <-- генератор сбыта бакаута
				
				// Церковный генератор №2 -->
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskContra_1") && NPChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_tavern")
				{
					Link.l4 = "Ki kell találnom valamit, haver.";
					Link.l4.go = "Contra_GenQuest_Church_2_1";
				}
				
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskContra_2") && NPChar.location == PChar.GenQuest.ChurchQuest_2.Contra_Colony + "_tavern")
				{
					Link.l5 = "Egy kollégája és jó barátom a  " + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_2.QuestTown + "Gen") + " mondta, hogy ön tud valamilyen üzletrôl.";
					Link.l5.go = "Contra_GenQuest_Church_2_Contra2_1";
				}
				// <-- Церковный генератор №2
				
				Link.l7 = "Mi a baj? Semmi. Viszlát.";
				Link.l7.go = "Exit";				
			}
		break;
		
		case "CapComission_1":
			if(pchar.GenQuest.CaptainComission.variant == "A2")
			{
				dialog.text = "Az erôd alagsorában, hol máshol? Az a kapitány bármikor felfedheti a rejtekhelyet a hatóságoknak, és nem marad semmi nekünk. Ne gondolj semmiféle üzletre, amíg ennek a felhajtásnak nincs vége.";
				link.l1 = "Figyelj, te ismered a sziget minden egyes darabját. Tényleg fogalmad sincs, hol van a kapitány " + pchar.GenQuest.CaptainComission.Name + "rejtekhelye?";
				link.l1.go = "CapComission_4";
			}
			if(pchar.GenQuest.CaptainComission.variant == "A3")
			{
				dialog.text = "Az égben, azt hiszem. Felakasztották a legénységével együtt. De a halálos ítéletben nem említették, hogy kalózhajó volt.";
				link.l1 = "És miért vagy olyan biztos benne, hogy a hajó kalózhajó volt?";
				link.l1.go = "CapComission_2";
			}	
		break;
		
		case "CapComission_2":
			dialog.text = "A szikláról figyeltük a harcot. Egy távcsôvel láttuk a Jolly Roger alatti hajót. Aztán, úgy öt órával késôbb, egy villanást láttunk a sötétben, úgy nézett ki, mintha a puskaporos szobából jött volna egy csapás. Elég idô, hogy a rakományt a partra vigyük.";
			link.l1 = "Nem tudod, hol van a kapitány " + pchar.GenQuest.CaptainComission.Name +"'s rejtekhelye? Te ismered a sziget minden részét.";
			link.l1.go = "CapComission_3";
		break;
		
		case "CapComission_3":
			dialog.text = "Nem. És mi is keressük, de nem a kormányzó szórakoztatására...";
			link.l1 = "Értem.... Szép napot!";
			link.l1.go = "exit";
			AddQuestRecord("CaptainComission2", "38");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Acc")));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sShipTypeQuest", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name") + "Gen")));
		break;
		
		case "CapComission_4":
			dialog.text = "Nem. És mi is keressük, de nem a kormányzó szórakoztatására... he-he-he.";
			link.l1 = "Értem... Szép napot!";
			link.l1.go = "exit";
			AddQuestRecord("CaptainComission2", "19");
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Gen"))); // belamour gen
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
		break;
				
		case "SM_ShipLetters_1":
			pchar.questTemp.different.GiveShipLetters.speakSmuggler = true;
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 0)
			{
				dialog.text = "Miért döntöttél így? Én egy becsületes hullámvasutas vagyok. Menj és keress másik vevôt.";
				link.l1 = "Köszönjük...";
				link.l1.go = "exit";
			}
			else
			{
				if(!CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakUsurer_1"))
				{
					dialog.text = "Miért nem? Talán találok valami hasznát a 'cargo'. Vegye " + sti(pchar.questTemp.different.GiveShipLetters.price2) + " érméket, és felejtse el.";
					link.l1 = "Nem, köszönöm.";
					link.l1.go = "SM_ShipLetters_2";	
					link.l2 = "És jól tippeltél, ezt kezdem elfelejteni!";
					link.l2.go = "SM_ShipLetters_3";
				}
				else
				{
					if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 1)
					{
						dialog.text = "Pontosan! Most már tényleg kíváncsi vagyok. Feltételezem, hogy ha fizetek neked "+ sti(pchar.questTemp.different.GiveShipLetters.price3) +" érméket, akkor egyáltalán nem fogsz törôdni azokkal a papírokkal.";
						link.l1 = "Nem, köszönöm.";
						link.l1.go = "SM_ShipLetters_2";
						link.l2 = "És igazad van. Már el is felejtettem ôket.";
						link.l2.go = "SM_ShipLetters_3";
					}
					if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 2)
					{
						dialog.text = "Na, itt az alkalom, hogy elkapjuk azt a szemtelen fickót! Nagyon, nagyon kíváncsi vagyok. Nézd, fizetek neked " + sti(pchar.questTemp.different.GiveShipLetters.price4) + " aranyban, és te teljesen elfelejted a dokumentumokat az asztalon?";
						link.l1 = "Nem fogom.";
						link.l1.go = "SM_ShipLetters_2";
						link.l2 = "Rendben, megegyeztünk!";
						link.l2.go = "SM_ShipLetters_3";
					}
				}
			}
		break;
		
		case "SM_ShipLetters_2":
			dialog.text = "Rendben, rendben, de ne csinálj több ellenséget.";
			link.l1 = "Neked is!";
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
					dialog.text = "Ma nincs üzlet. Minden öbölben járôrök járôröznek, a kormányosunk egy rakományt keres, amelyet valami kapitány" + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"név") + "Acc")) + " " + pchar.GenQuest.CaptainComission.Name + " elkobzott, és valahol elrejtette.";
					link.l1 = "És hol van ez a kapitány" + pchar.GenQuest.CaptainComission.Name + "?";
					link.l1.go = "CapComission_1";
					break;
				}
				else
				{
					dialog.text = "Ma nincs üzlet.";
					link.l1 = "Értem, értem.";
					link.l1.go = "exit";					
					break;
				}
			}
			
			if(pchar.questTemp.Slavetrader == "FindMayak" && Islands[GetCharacterCurrentIsland(pchar)].id == pchar.questTemp.Slavetrader.EsIsland)
			{
				dialog.text = "Ma nincs üzlet.";
				link.l1 = "Értem, értem.";
				link.l1.go = "exit";
				break;
			}
			
			if(npchar.id == "Bridgetown_Smuggler" && CheckAttribute(pchar, "questTemp.BM_BlockSmuggler"))
			{
				dialog.text = "Ma nincs üzlet.";
				link.l1 = "Értem, értem.";
				link.l1.go = "exit";
				break;
			}
			
			Dialog.Text = "Miben segíthetek, kapitány?";
			
			bOk2 = MCGovernon || MCAdmiral;
			if(FindContrabandGoods(PChar) != -1 && !bOk2)
			{
				Link.l1 = "Szeretnék vásárolni vagy eladni valamit.";
				Link.l1.go = "Meeting_1";
			}
			
			Link.l2 = "El kell jutnom egy helyre.";
			Link.l2.go = "Travel";				
			
			//Jason --> мини-квест Бесчестный конкурент
			if(CheckAttribute(PChar, "questTemp.Shadowtrader.seeksmugglers") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_tavern")
			{
				Link.l8 = "Van egy elég szokatlan üzletem az ön számára.";
				Link.l8.go = "Shadowtrader_smugglers";
			}
			// <-- мини-квест Бесчестный конкурент
			//--> Торговля по закону
				if(CheckAttribute(PChar, "questTemp.TPZ_ContraInfo") && NPChar.location == "BasTer_tavern")
				{
					Link.l8 = "Figyelj, barátom, szükségem van egy szállítmány borra és rumra. Minél többet, annál gyorsabban.";
					Link.l8.go = "TPZ_smugglers_1";
				}
			// <-- Торговля по закону
			//Jason --> генератор сбыта бакаута
			if(NPChar.location == "Marigo_tavern" && CheckAttribute(PChar, "GenQuest.Bakaut") && !CheckAttribute(PChar, "GenQuest.Bakaut.Info"))
			{
				Link.l9 = "Találkoznom kell Michael Rosenkrafttal. Van egy rakományom, ami érdekes lehet számára.";
				Link.l9.go = "bakaut";
			}
			// <-- генератор сбыта бакаута
			
			// Церковный генератор №2 -->
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskContra_1") && NPChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_tavern")
			{
				Link.l3 = "Ki kell találnom valamit, haver.";
				Link.l3.go = "Contra_GenQuest_Church_2_1";
			}
			
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskContra_2") && NPChar.location == PChar.GenQuest.ChurchQuest_2.Contra_Colony + "_tavern")
			{
				Link.l3 = "Egy kollégája és jó barátom a  " + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_2.QuestTown + "Gen") + " azt mondta, hogy ön tisztában van néhány vállalkozással.";
				Link.l3.go = "Contra_GenQuest_Church_2_Contra2_1";
			}
			// <-- Церковный генератор №2

			Link.l5 = "Mi a baj? Semmi. Viszlát.";
			Link.l5.go = "Exit";				
		break;

		// Церковный генератор №2 -->
		case "Contra_GenQuest_Church_2_1":
			iChurchQuest2_Summ = PChar.GenQuest.ChurchQuest_2.Summ_To_Contra;
			dialog.text = "Nem vagyok a haverod. És ez sokba kerülhet neked.";
				link.l1 = "Hm. Tudnom kell valamit, ami nem kerül többe, mint " + FindRussianMoneyString(iChurchQuest2_Summ) + ".";
				link.l1.go = "Contra_GenQuest_Church_2_2";
			break;
			
		case "Contra_GenQuest_Church_2_2":
			iChurchQuest2_Summ = PChar.GenQuest.ChurchQuest_2.Summ_To_Contra;
			if(sti(PChar.money) >= iChurchQuest2_Summ)
			{
				dialog.text = "Add ide az érméidet. És tudd, hogy nem kapsz sokat egy ilyen összegért.";
				link.l1 = "Látod, hiányoztak a barátaim. Elkéstem egy találkozóról, és ôk nem vártak meg...";
				link.l1.go = "Contra_GenQuest_Church_2_3";
				AddMOneyToCharacter(PChar, -iChurchQuest2_Summ);
				DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.AskContra_1");
				DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.Summ_To_Contra");
			}
			else
			{
				dialog.text = "Ha, neked nincs pénzed! Gyere, ha lesz egy kis pénzed.";
				link.l1 = "Valóban, rajta vagyok.";
				link.l1.go = "exit";
			}
			break;
			
		case "Contra_GenQuest_Church_2_3":
				dialog.text = "És miért van rám szükséged?";
				link.l1 = "Nem a városban vannak, és nincs hajójuk. Ezért gondoltam: talán valamelyik üzlettársad tett nekik szívességet?";
				link.l1.go = "Contra_GenQuest_Church_2_4";
			break;
			
		case "Contra_GenQuest_Church_2_4":
			sColony = QuestGetColony(PChar.GenQuest.ChurchQuest_2.QuestTown);
			dialog.text = "Értem... Találkoztam néhány sráccal, akik azt mondták, hogy el kell menniük a szigetrôl, és nem érdekli ôket, hogy hova. Ilyen esetben nem kérdezzük az okokat, csak a fizetséget. Volt egy utunk a " + XI_ConvertString("Colony" + sColony + "Acc") + " , " + XI_ConvertString(locations[FindLocation(sColony + "_Town")].IslandID + "Dat") + " . Oda is el tudunk vinni, ha megegyezünk a pénzben.";
			link.l1 = "Köszönöm, de van saját hajóm.";
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
			dialog.text = "Soha nem üzleteltem veled.";
			link.l1 = "Meg tudjuk javítani. Nemrég hoztad ide a barátaimat. Lemaradtam egy találkozóról "+ GetSexPhrase("velük","velük") +".";
			link.l1.go = "Contra_GenQuest_Church_2_Contra2_2";
		break;
			
		case "Contra_GenQuest_Church_2_Contra2_2":
			string sGenLocation = IslandGetLocationFromType(locations[FindLocation(PChar.GenQuest.ChurchQuest_2.Contra_Colony + "_Town")].IslandID, "Shore");
			PChar.GenQuest.ChurchQuest_2.QuestGangShore = sGenLocation;
			PChar.GenQuest.ChurchQuest_2.BanditsInShore = true;
			dialog.text = "Hm, partra tettük ôket a " + XI_ConvertString(sGenLocation + "Gen") + "... Tudod, jobb lenne, ha a barátaid lennének, különben nem tanácsolom, hogy más esetben is zaklasd ôket.";
			link.l1 = "Köszönöm az aggodalmadat, de én jól felfegyverkezve és nagyon bájos vagyok.";
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
			Dialog.Text = "Hm... és mi közöm nekem ehhez? Valószínûleg elvesztetted magad, kapitány. Menjen a boltba, és adjon el vagy vegyen ott, amit csak akar.";
			Link.l1 = "Nem, szükségem van rád.";
			Link.l1.go = "Meeting_2";				
			Link.l2 = "Köszönöm a tanácsát. Szép napot!";
			Link.l2.go = "exit";				
		break;

		case "Meeting_2":
			Dialog.Text = "Mihez?";
			Link.l1 = "Talán érdekli valami különleges áru? Vagy talán van valami, amit felajánlhatna nekem helyette?"
			Link.l1.go = "Meeting_3";				
		break;

		case "Meeting_3":
			int iTmp = false;
			int iChIdx, i;
			
			float fMaxClass = ((MOD_SKILL_ENEMY_RATE/5.0) + 1.5);
			if (IsEquipCharacterByArtefact(pchar, "talisman21")) fMaxClass = 2.0;
			
			if (GetCompanionQuantity(pchar) > 1) iTmp = true;
			if (GetCharacterShipClass(pchar) < fMaxClass) iTmp = true;

			// поиск мин.  те старшего класса
			/* for (i=0; i<COMPANION_MAX; i++)
			{
				iChIdx = GetCompanionIndex(GetMainCharacter(), i);
				if (iChIdx>=0)
				{
					sld = GetCharacter(iChIdx);
            		if (GetCharacterShipClass(sld) < ((MOD_SKILL_ENEMY_RATE/5.0) + 1.5)) iTmp = true;
				}
			} */
			
			if (iTmp)
			{
				dialog.text = NPCStringReactionRepeat("Miért nem viszel legközelebb egy királyi hadihajót? Az erôdbôl könnyen észrevehetô a hajótok. Nem kockáztatjuk a fejünket. Legközelebb egy kis hajóval gyertek.", 
					"Ismételjem magam? Keress egy kisebb hajót, és akkor majd beszélünk.", 
					"Tényleg ennyire idióta vagy? Keress magadnak egy szkúnert vagy egy brigget. Csak abban az esetben lesz üzlet.",
					"Ó, milyen idióta...", "block", 1, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Rendben, megértettem.", 
					"Értem, csak pontosítani akartam valamit.",
					"Nem, nem idióta, csak egy csirkefogó. Gondoltam, hogy valami megváltozott. Én még pár pinnacot elvinnék...", 
					"Nézz a tükörbe...", npchar, Dialog.CurrentNode);
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
				Dialog.Text = "Sajnálom, "+ GetSexPhrase("haver","lány") +", már így is elfoglaltak vagyunk. Gyere vissza pár nap múlva.";
				Link.l1 = "Sajnálom...";
				Link.l1.go = "Exit";		
				break;
			}
//navy <--

			if (bOk || bOk2 || bOk3)
			{
				Dialog.Text = "Mi lenne, ha elôbb befejeznénk a jelenlegi ügyeinket?";
				Link.l1 = "Azt hiszem, igazad van.";
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
                                Dialog.Text = "Tudom, hogy üzletet tudunk kötni önökkel. Várjuk a " + GetConvertStr(Pchar.quest.contraband.CurrentPlace, "LocLables.txt") + ".";
                            }
                            else
                            {
            				    Dialog.Text = "Hm... Talán találunk neked egy vevôt. Várjuk Önt a " + GetConvertStr(Pchar.quest.contraband.CurrentPlace, "LocLables.txt") + ".";
            				}
            				Link.l1 = "Rendben. Ott találkozunk.";
            				Link.l1.go = "Smuggling_exit";
        				}
        				else
        				{   //boal fix
                            Dialog.Text = "Ma nincs üzlet. Jöjjön ide holnap.";
            				Link.l1 = "Rendben.";
            				Link.l1.go = "Exit";
        				}
    				}
    				else
    				{
                        Dialog.Text = "Tényleg azt hiszed, hogy ezek után bárki is veled akar majd dolgozni? Örülj, hogy nem küldtünk érted fejvadászokat.";
        				Link.l1 = "Kár érte. Nincs esélyem, hogy csempész legyek.";
        				Link.l1.go = "Exit";
    				}
				}
				else
				{
                    Dialog.Text = "Ma nincs üzlet. Jöjjön ide holnap.";
    				Link.l1 = "Rendben.";
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
				Dialog.Text = "Sajnálom, "+ GetSexPhrase("haver","lány") +", már így is elfoglaltak vagyunk. Gyere vissza pár nap múlva.";
				Link.l1 = "Kár.";
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
						Dialog.Text = "Azt hittem, hogy már megegyeztünk az üzletrôl.";
						Link.l2 = "Valóban!";
					}
					//не платил, значит можно запалатить пока не вышел срок.
					else
					{
						if(GetQuestPastDayParam("contraTravel") == sti(PChar.GenQuest.contraTravel.days))
						{
							Dialog.Text = "Elhoztad a pénzt?";
							Link.l1 = "Igen.";
							Link.l1.go = "Travel_pay";
							Link.l3 = "Meggondoltam magam...";
							Link.l3.go = "Travel_abort";
							Link.l2 = "Még nem.";
						}
						else
						{
                            if (GetQuestPastDayParam("contraTravel") < sti(PChar.GenQuest.contraTravel.days))
							{
								Dialog.Text = "Már mindent elmondtam neked.";
								Link.l2 = "Pontosan.";
								Link.l1 = "Meggondoltam magam...";
								Link.l1.go = "Travel_abort";
							}
							else // просрочка
							{
							    Dialog.Text = "Ma nem tudok segíteni. Jöjjön el két nap múlva, és talán találunk valamit magának.";
								Link.l2 = "Kár.";
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

							Dialog.Text = "Nos, mi el tudunk juttatni a " + GetConvertStr(locations[FindLocation(pchar.GenQuest.contraTravel.destination.loc)].id, "LocLables.txt") + " közelébe " +
								XI_ConvertString("Colony" + pchar.GenQuest.contraTravel.destination + "Gen") + " aranyért " + pchar.GenQuest.contraTravel.price + " . Hozd a pénzt a " +
								FindRussianDaysString(nDay) + ". A hajó pontosan 24 óra múlva várni fog rád " +
								GetConvertStr(locations[FindLocation(Pchar.GenQuest.contraTravel.CurrentPlace)].id, "LocLables.txt") + " .";

							pchar.GenQuest.contraTravel.days = nDay;
							Link.l1 = "Nekem bevált.";
							Link.l1.go = "Travel_agree";
							Link.l2 = "Nem, köszönöm.";
						}
						else
						{
							Dialog.Text = "Ma nem tudok segíteni. Jöjjön el két nap múlva, és talán találunk valamit magának.";
							Link.l2 = "Kár.";
						}
					}
					//нет, посылаем в сад
					else
					{
                        Dialog.Text = "Tényleg azt hiszed, hogy bárki is veled akar majd dolgozni ezek után? Jobb, ha örülsz, hogy nem küldtünk érted fejvadászokat. Tûnjetek el!";
        				Link.l2 = "Huh, megint nincs szerencsém.";
					}

				}
			}
			//корабль есть, посылаем в сад...
			else 
			{
				if(GetPassengersQuantity(pchar) != 0)
				{
					Dialog.Text = "Nem, nem viszünk el mindenkit. Csak egyikôtöket.";
					Link.l2 = RandSwear() + "Nekem amúgy sincs rá szükségem!";
				}
				else
				{
					Dialog.Text = "Miért nem használod a saját hajódat? Nem, nem viszünk el titeket.";
					Link.l2 = "Rendben, ahogy akarod.";
				}
			}
			Link.l2.go = "Exit";
			break;

		//отмена
		case "Travel_abort":
			ChangeContrabandRelation(pchar, -2);
			DeleteAttribute(PChar, "GenQuest.contraTravel");
			CloseQuestHeader("Gen_ContrabandTravel");
			Dialog.Text = "Amit csak akarsz.";
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
				Dialog.Text = "Örülök, hogy üzletet kötöttünk. Ne késsenek a hajóról.";
				Link.l1 = "Megpróbálom.";
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
				Dialog.Text = "Úgy tûnik, nincs elég pénzed."
				Link.l1 = "Milyen kár, késôbb visszajövök.";
			}
			Link.l1.go = "Exit";
		break;  
////////////////////////////////////////////////////////////////////////////////
//	END OF Корсарское метро
////////////////////////////////////////////////////////////////////////////////
				
		//Jason --> мини-квест Бесчестный конкурент
		case "Shadowtrader_smugglers":
			dialog.text = "Nagyon érdekes. Mutasd meg, mid van.";
			link.l1 = "Hallottam, hogy van egy földalatti bolt, ahol nagyon 'különleges' áruval lehet kereskedni, csábító áron, és te segítettél elindítani ezt a boltot. Szeretnék beszélni a tulajdonosával.";
			link.l1.go = "Shadowtrader_fail";
			link.l2 = "Úgy hallottam, hogy van egy földalatti bolt, ahol nagyon 'különleges' áruval lehet kereskedni, csábító áron. Pár nap múlva el kell vitorláznom, és nincs elég pénzem, hogy mindent megvegyek a helyi boltban, amire szükségem van, ezért szükségem van és szeretnék is egy kis pénzt félretenni... néhányan azt mondták, hogy ebben tudtok segíteni.";
			link.l2.go = "Shadowtrader_smugglers_1";
			DeleteAttribute(pchar, "questTemp.Shadowtrader.seeksmugglers");
			DelLandQuestMark(npchar);
		break;
		
		case "Shadowtrader_fail":
			dialog.text = "Mirôl beszélsz? Nem értelek. Nem mi nyitottunk itt boltot, ez hülyeség, ha-ha! Ha kereskedni akarsz, akkor hozz árut, és a szokásos módon fogunk beszélgetni... Egy bolt, ha!";
			link.l1 = "Hm...";
			link.l1.go = "exit";
			pchar.questTemp.Shadowtrader = "true";
			AddQuestRecord("Shadowtrader", "3");
			CloseQuestHeader("Shadowtrader");
			DeleteAttribute(pchar, "questTemp.Shadowtrader_Block");
		break;
		
		case "Shadowtrader_smugglers_1":
			dialog.text = "Akarsz kedvezményt? Nyugodtan. Gyertek a kikötômester ajtajánál, amikor besötétedik. Az emberünk találkozik veled és elvisz a megfelelô helyre. ";
			link.l1 = "Rendben. Ott leszek!";
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
			dialog.text = "Ha, az a gazember a pult mögött küldött téged, ugye?";
			link.l1 = "Számít ez? Meg tudod szerezni, vagy keressek valaki mást?";
			link.l1.go = "TPZ_smugglers_2";
			DelLandQuestMark(npchar);
		break;
		
		case "TPZ_smugglers_2":
			dialog.text = "Bármit meg tudok szerezni, amit csak akarsz, érted? Amíg a fizetés megfelelô. De az az átkozott kormányzó keményen bekeményített. Mi már nem nyúlunk a szeszhez - túlságosan bunkó, egy mérföldrôl is hallani, a profit fillérekbe kerül, és a kötél végén táncolás kockázata az egekbe szökik. Szóval, ne vegye sértésnek.";
			link.l1 = "Hmm... És azt mondod, hogy bármit meg tudsz szerezni.";
			link.l1.go = "TPZ_smugglers_3";		
		break;
		
		case "TPZ_smugglers_3":
			dialog.text = "Meg tudom! Csak nem akarom. Van egy fickó, aki a kormányzói palota mellett lakik, el tudod ezt hinni? Ha-ha. Micsoda bolond... Mit is mondtam? Ja, persze. Csendben árulja a piát az asztal alatt. Pont a kormányzó púderezett parókája alatt, ha-ha. Kérdezd meg tôle, talán ad neked egy nyomot. A mennyisége kicsi, gyerekes cucc, de ez is valami.";
			link.l1 = "Nem sok segítség, de azért köszi.";
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
			dialog.text = "Rengeteg mulatozó van itt, és ha nincs dolga, uram, igyon vagy beszélgessen velük. Itt nagy a nyüzsgés.";
			link.l1 = "Próbáljuk meg újra. Fizetek az idejéért és a kíváncsiságomért. Válaszokra van szükségem.";
			link.l1.go = "Consumption_1";
		break;
		
		case "Consumption_1":
			if (sti(pchar.money) >= 3002)
			{
				dialog.text = "Fizetni fog, ha! Az én idôm nem olcsó, uram, 3000 pezóba kerül, plusz ez az undorító ital, amit tévedésbôl rumnak hívnak.";
				link.l1 = "Megegyeztünk! Most pedig meséljen nekem egy olyan emberérôl, aki fél évet töltött a helyi börtönben, majd átment. Mi történt vele?";
				link.l1.go = "Consumption_2";
			}
			else
			{
				dialog.text = "Jobb lenne, ha ezüsttel vagy arannyal tömnéd tele a zsebeidet, ami jobb lenne. Akkor gyere és beszélgessünk, nincs idôm ingyen beszélgetni veled.";
				link.l1 = "...";
				link.l1.go = "exit";
			}
		break;
		
		case "Consumption_2":
			AddMoneyToCharacter(pchar, -3002);
			dialog.text = "Erre emlékszem, bár nem értem, miért érdekel ez téged. A kölyök tényleg megôrült a rácsok mögött. Részeges lett, és mindig valami ostobaságokat beszélt a fogyasztásról, ami elvitte az embereket, és senki sem volt biztonságban tôle. Azt mondta, hogy ennek a fogyasztásnak van neve, és még csak ki sem meri mondani hangosan. Ha megteszed - eljön és elvisz téged is.";
			link.l1 = "És mi történt vele ezután?";
			link.l1.go = "Consumption_3";
		break;
		
		case "Consumption_3":
			dialog.text = "A történetnek furcsa vége van, senior. Eleinte a helyieknek és a matrózoknak tetszett a meséje, de végül elegük lett belôle. Ez mindig megtörténik minden mesével. Ezért aztán provokálták, hogy kimondja a nevét. A fickó buzgón ellenkezett, de nem bírta elviselni a gúnyolódást, és szó szerint elsírta magát\nSenki nem érzett semmi különöset, a gyertyák nem aludtak ki, de a szerencsétlent másnap reggel holtan találták a kocsma mögött, átvágott torokkal.";
			link.l1 = "Nem látok itt semmilyen varázslatot. Mondd meg a nevét.";
			link.l1.go = "Consumption_4";
		break;
		
		case "Consumption_4":
			dialog.text = "Emlékszem a névre, de a fenébe is, nem fogom hangosan kimondani. Valami baljóslatú dolog van ebben az egészben. Nem látod?";
			link.l1 = "Hé, haver, kaptál tôlem egy tárcányi érmét, emlékszel? Szóval, megmondanád a nevet, kérlek?";
			link.l1.go = "Consumption_5";
		break;
		
		case "Consumption_5":
			dialog.text = "Nem lesz jó vége, senor, higgye el... (leeresztette a hangját) Azt mondta - Juan...";
			link.l1 = "A fenébe veled! Juan? Ez csak egy közönséges név, és itt elég népszerû. Miért olyan különleges?";
			link.l1.go = "Consumption_6";
		break;
		
		case "Consumption_6":
			dialog.text = "Nem tudom, de azt az embert, aki ezt a nevet mondta, megölték. Bízz bennem, valami nagyon nincs rendben ezzel a névvel. Ez minden, amit tudni akartál?";
			link.l1 = "Azt hiszem, igen. Meghívhatod magad egy italra. Viszlát!";
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
			dialog.text = "Valóban? Igen. Mynheer Rosenkraftnak szüksége van egy adag vasfára, de nem kevesebbre, mint "+FindRussianQtyString(sti(pchar.GenQuest.Bakaut.Value))+". Van elég rakományod?";
			if (GetSquadronGoods(pchar, GOOD_SANDAL) >= sti(pchar.GenQuest.Bakaut.Value))
			{
				link.l1 = "Van. Hol találom mynheer Rosenkraftot?";
				link.l1.go = "bakaut_1";
			}
			else
			{
				link.l1 = "Hm. Most nincs túl sok.";
				link.l1.go = "bakaut_no";
			}
		break;
		
		case "bakaut_no":
			dialog.text = "Akkor ne zavarja mynheer Rosenkraftot. Jöjjön, ha lesz elég rakománya.";
			link.l1 = "Rendben.";
			link.l1.go = "exit";
		break;
		
		case "bakaut_1":
			dialog.text = "Gályája több napon át a "+XI_ConvertString(pchar.GenQuest.Bakaut.Island+"Gen")+" partjainak közelében fog hajózni. Tehát ne késsen el - lehet, hogy a szigetcsoport egy másik pontjára hajózik.";
			link.l1 = "Rendben, gyorsítok. Köszönöm!";
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
			dialog.text = "És holnapig kell élnem. Az átkozott 'Mercy' a városban van. Menj el.";
			link.l1 = "Micsoda dráma...";
			link.l1.go = "exit";
		break;
		//<-- прибыла инспекция на Святом Милосердии
	}
}
