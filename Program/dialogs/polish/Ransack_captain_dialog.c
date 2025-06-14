// BOAL диалог пленников - в трюме
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	ref offref;
    int i, cn;
    int qty;
    string attrLoc, sTmp;
    
	switch(Dialog.CurrentNode)
	{
		// -----------------------------------Диалог первый - первая встреча
		case "First time":
		//--> Jason, Ложный след
		if (CheckAttribute(pchar, "questTemp.FalseTrace.Prisoner") && GetFullName(npchar) == pchar.questTemp.FalseTrace.CapName)
		{
			dialog.text = "Co chcesz, kapitanie? Omówić mój okup? Chciałbym, żebyś wiedział, że zależy mi na losie tej dziewczyny...";
			link.l1 = "Mówisz o Katerine Rayner? Już jestem o tym poinformowany, "+pchar.questTemp.FalseTrace.CapName+". Poprosiła mnie, aby porozmawiać z tobą.";
			link.l1.go = "FalseTrace_Prisoner";
			break;	
		}
		//<-- Ложный след
		
		// Addon-2016 Jason ФМК-Гваделупа
		if (CheckAttribute(pchar, "questTemp.FMQG") && pchar.questTemp.FMQG != "fail" && CheckAttribute(pchar, "questTemp.FMQG.Prisoner") && GetFullName(npchar) == pchar.questTemp.FMQG.Prisoner)
		{
			dialog.text = "";
			link.l1 = "Zobacz teraz, don Juanie, zdrada to zło...";
			link.l1.go = "FMQG";
			break;	
		}
			if (sti(NPChar.nation) == PIRATE)
			{
				dialog.text = RandSwear()+"Jestem twoim więźniem, "+GetAddress_Form(NPChar)+". Ale chciałbym, żebyś wiedział, że "+NationNameNominative(sti(NPChar.nation))+" nigdy nie płaci za swoich ludzi. Jesteśmy zdani tylko na siebie.";
				link.l1 = "Cóż... Widzę, że nie będe mieć z ciebie żadnego zysku. Przynajmniej mogę cię oddać jako przestępcę w dowolnej kolonii.";
				link.l1.go = "offender";
				if (FindFreeRandomOfficer() > 0)
				{
					link.l2 = "Spójrz, jesteś uzdolnionym wojownikiem i desperacko potrzebuję ludzi jakich jak ty. Czy chciałbyś służyć pod moim dowództwem?";
					link.l2.go = "free_to_officer";
				}	
			}
			else
			{
				dialog.text = RandSwear()+"Jestem twoim więźniem, "+GetAddress_Form(NPChar)+". "+NationNameNominative(sti(NPChar.nation))+" zapłaci każdą cenę za mą wolność.";
				if(NPChar.EncType == "trade" && FindFreeRandomOfficer() > 0 && CheckAttribute(NPChar, "Back.Ship.Mode") && NPChar.Back.Ship.Mode == "trade")
				{
					link.l1 = "Spójrz, jesteś umiejętnym marynarzem, a ja potrzebuję ludzi jak ty. Czy chciałbyś służyć pod moim dowództwem?";
					link.l1.go = "free_to_officer_trader";
				}
			}
			attrLoc = Sea_FindNearColony();
			if (attrLoc != "none") 
			{
                link.l3 = "Nie jesteśmy daleko od "+GetConvertStr(attrLoc+" Miasto","LocLables.txt")+". Mogę cię więc tu puścić.";
			    link.l3.go = "free_withoutFee";
			}
			else
			{
                link.l3 = "Idź do bosmana, powiedz mu, aby dał ci szafkę. Możesz wylądować w następnym porcie.";
			    link.l3.go = "free_withoutFee_2";
			}			
			link.l4 = "Sądze, że będzie z ciebie świetny niewolnik - silny i posłuszny.";
			link.l4.go = "Slave_1";
			link.l5 = "Zignorowałeś rozkaz opuszczenia żagli i stawiłeś opór. Za to zostaniesz powieszony. Bosman już otrzymał moje rozkazy.";
			link.l5.go = "PunishmentAction";
			link.l99 = "Zdaje sobie z tego sprawę.";
			link.l99.go = "exit";
			NextDiag.TempNode = "second time"; 
		break;
		
		case "second time":
			if(CheckAttribute(NPChar,"Hold_GenQuest") && !CheckAttribute(pchar,"GenQuest.Hold_GenQuest"))
			{
				switch(sti(NPChar.Hold_GenQuest.variant))
				{				
					case 0: // "tip-off"
						dialog.text = RandPhraseSimple("Kapitanie, czy chciałbyś wysłuchać mojej propozycji dotyczącej bardziej dochodowej wersji mojego okupu?","Rozumiem, że w moim miejscu nie ma miejsca na targowanie się, ale czy chciałbyś usłyszeć moją propozycję?");
						link.l1 = "Słucham.";	
						link.l1.go = "free_tip_off";
					break;
					
					case 1:
						dialog.text = "Kapitanie, dlaczego nie uwolnisz mnie? Nie jestem dla ciebie wartością. Jeśli sprzedasz mnie niewolnikom, dostaniesz tylko kilka monet i złą sławę.";
						link.l1 = "A jeśli po prostu cię zwolnię, nie dostanę niczego...";
						link.l1.go = "free_by_hoard";
						attrLoc = Sea_FindNearColony();
						if (attrLoc != "none") 
						{
							link.l2 = "Zignorowałeś rozkaz opuszczenia żagli i stawiałeś opór siłą. Zostaniesz za to powieszony. Bosman już otrzymał moje rozkazy.";
							link.l2.go = "PunishmentAction";							
						}
						else
						{
							link.l2 = "Jesteś naprawdę uparty, więc myślę, że mogę dać ci to, czego chcesz. Jesteś teraz wolnym człowiekiem. Opuść mój statek.";
							link.l2.go = "free_in_sea";
						}
						link.l3 = LinkRandPhrase("Nie testuj mojej cierpliwości. Jesteś już szczęściarzem, że wciąż żyjesz.","Mam dla ciebie swoje własne plany.","Przypuszczam, że w przyszłości możesz mi jeszcze posłużyć.");
						link.l3.go = "exit";	
					break;
					
					case 2: // "ransom"
						dialog.text = "Kapitanie, ta niepewność mnie zabija. Czy mogę wiedzieć, co planujesz ze mną zrobić?";
						link.l1 = "Czy masz coś do zaoferowania mi?";
						link.l1.go = "free_buyout";
						link.l2 = RandPhraseSimple("Nie mam jeszcze żadnych pomysłów na Ciebie.",RandPhraseSimple("Plany? Kulka armatnia na twojej szyi? Żartuję, ha!","Jesteś moim więźniem i mam pełne prawo robić z tobą, co tylko zechcę. Twoje zdanie tutaj nie ma żadnej wartości."));
						link.l2.go = "exit";
					break;										
				}
				NextDiag.TempNode = "second time"; 
			}
			else
			{
				if (sti(NPChar.nation) == PIRATE)
				{
					dialog.text = "Kapitanie, czemu po prostu nie pozwolisz mi odejść? Nie potrzebujesz mnie. Wybór bycia piratem był dla mnie jedyną opcją, bo nie mam żadnych cennych umiejętności czy wykształcenia. Moim marzeniem było zarobić trochę pieniędzy i potem przejść na emeryturę.";
					if (FindFreeRandomOfficer() > 0)
					{
						link.l2 = "Spójrz, jesteś wytrawnym wojownikiem, a potrzebuję twardzieli jak ty. Czy chciałbyś być moim oficerem?";
						link.l2.go = "free_to_officer";
					}				
					link.l3 = LinkRandPhrase("Nie ma dla ciebie litości. Na morzu jest wielu łotrów. Przynajmniej jeden mniej będzie teraz tam pływał.","Jakieś problemy, 'wilku morski'? Zostań tutaj i bądź cicho.","Galgen czeka na wszystkich twojego rodzaju. Sprzedam cię władzom i to będzie wielka lekcja dla każdego pirata.");	
					link.l3.go = "exit";
				}
				else
				{
					if(NPChar.EncType == "trade")
					{
						dialog.text = "Kapitanie, błagam cię... Wypuść mnie. Mam rodzinę i dzieci, które bez mnie nie poradzą sobie.";
						if (FindFreeRandomOfficer() > 0 && CheckAttribute(NPChar, "Back.Ship.Mode") && NPChar.Back.Ship.Mode == "trade")
						{
							link.l2 = "Patrz, jesteś zręcznym marynarzem i potrzebuję takich ludzi jak ty. Czy chciałbyś służyć pod moim dowództwem?";
							link.l2.go = "free_to_officer_trader";
						}
						link.l3 = LinkRandPhrase("Mam swoje plany na ciebie.","Przypuszczam, że w przyszłości możesz mi jeszcze być przydatny.","Jesteś moim więźniem i mam pełne prawo robić z tobą, co tylko chcę.");
						link.l3.go = "exit";
					}
					if(NPChar.EncType == "war")
					{
						dialog.text = RandPhraseSimple("Kapitanie, przegrałem walkę i błagam Cię o litość.","Kapitanie, błagam o twoją hojność. Rozumiem, że nie ma powodu traktować mnie jak jeńca wojennego, więc proszę cię o litość. Daję ci słowo, że uniknę spotkania z tobą na morzu.");
						link.l2 = LinkRandPhrase("Nie testuj mojej cierpliwości. Jesteś już szczęściarzem, że wciąż żyjesz.",RandPhraseSimple("Mam dla ciebie swoje plany.","Przypuszczam, że w przyszłości możesz mi jeszcze przydać."),RandPhraseSimple("Jesteś moim więźniem i mam pełne prawo robić z tobą, co chcę. Twoje zdanie tu nic nie znaczy.","Jesteś... no cóż, byłeś kapitanem okrętu wojennego i byłś świadomy ryzyka. Nie próbuj przedstawiać się tu jako święty."));
						link.l2.go = "exit";	
						if (isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 1)
						{
							if(sti(Items[sti(pchar.EquipedPatentId)].Nation) == sti(NPChar.nation) && FindFreeRandomOfficer() > 0)
							{
								link.l3 = "Spójrz, jesteś uzdolnionym wojownikiem, a potrzebuję takich gardłojadów jak ty. Czy chciałbyś być moim oficerem?";
								link.l3.go = "free_to_officer";
							}
						}
					}
				}
				attrLoc = Sea_FindNearColony();
				if (attrLoc != "none") 
				{
					link.l4 = "Nie jesteśmy daleko od "+GetConvertStr(attrLoc+" Miasto","LocLables.txt")+". A mogę cię tu wypuścić.";
					link.l4.go = "free_withoutFee";
				}
				else
				{
					if(NPChar.EncType == "trade" || NPChar.EncType == "pirate")
					{
						link.l4 = "Idź do bosmana, powiedz mu, aby dał ci szafkę. Możesz wysiąść w następnym porcie.";
						link.l4.go = "free_withoutFee_4";			
					}	
					else
					{
						link.l4 = "Do diabła z tobą! Idź do bosmana, powiedz mu, żeby dał ci szafkę. Możesz wysiąść w następnym porcie. I pamiętaj, że nasze następne spotkanie będzie ostatnim.";
						link.l4.go = "free_withoutFee_4";
					}
				}				
				link.l5 = "Zignorowałeś rozkaz opuszczenia żagli i stawiłeś opór siłą. Za to zostaniesz powieszony. Bosman już otrzymał moje rozkazy.";
				link.l5.go = "PunishmentAction";
				NextDiag.TempNode = "second time"; 
			}	
		break;
		
		case "offender":
			dialog.text = "Przestępca? Żartujesz sobie,"+GetAddress_Form(NPChar)+"!";
			link.l1 = "Bez żartów. Jesteś piratem.";
			link.l1.go = "exit";
		break;
		
		case "free_to_officer":
			if ((GetSummonSkillFromName(pchar, "Leadership") + 20) <= GetSummonSkillFromName(npchar, "Leadership"))
			{
				dialog.text = "Służyć pod twoim dowództwem? Lepiej bym karmił rekiny!";
				link.l1 = "Uważaj na swój język, albo go nakarmisz.";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Aby być twoim oficerem, "+GetAddress_Form(NPChar)+"? Zgadzam się. Znam swoją robotę i nie mam nic do stracenia.";
				link.l1 = "Zgoda! Idź i wykonaj swoją robotę.";
				link.l1.go = "free_to_officer_Hire";
				link.l2 = "Poczekaj chwilę, zmieniłem zdanie.";
				link.l2.go = "exit";
			}
		break;

		case "free_to_officer_trader":
			if (GetSummonSkillFromName(pchar, "Leadership") <= GetSummonSkillFromName(npchar, "Leadership"))
			{
				dialog.text = LinkRandPhrase("To kusząca oferta... ale muszę ją odrzucić. Z zasady.","Przykro mi, ale po tym co zrobiłeś moim przyjaciołom... To jest niemożliwe.","Nie, kapitanie. Po całym tym terrorze nie mogę już więcej tego robić. Złożyłem ślubowanie, że jeśli Najświętsza Dziewica usłyszy moje modlitwy i da mi wolność, nie będę już więcej żeglować.");
				link.l1 = "To twój wybór. Nie będę uparty.";	
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Dlaczego nie? Jestem złym kapitanem, straciłem mój statek i nic dla mnie nie zostało na brzegu. Poza rachunkami i długami...";
				link.l1 = "Zgoda! Idź do bosmana i odbierz swoje racje. Trochę później przydzielę ci stanowisko na moim statku.";	
				link.l1.go = "free_to_officer_Hire";
				link.l2 = "Poczekaj chwilę, zmieniłem zdanie.";
				link.l2.go = "exit";
			}
		break;
		
		case "free_to_officer_Hire":
            NPChar.Dialog.Filename = "Enc_Officer_dialog.c";
            NPChar.greeting = "Gr_Officer";
            NPChar.loyality = 5 + rand(10);
		    if (sti(NPChar.reputation) > 41)
		    {
		        NPChar.alignment = "good";
		    }
		    else
		    {
		        NPChar.alignment = "bad";
		    }
            ReleasePrisoner(NPChar); // освободили пленника
            DeleteAttribute(NPChar, "LifeDay") // постоянный
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
			// тут трем накопивщиеся сабли и корабли 290704 BOAL -->
			DeleteAttribute(Npchar, "Ship");
			Npchar.Ship.Type = SHIP_NOTUSED;
            DeleteAttribute(Npchar, "Fellows"); // его офицеры
            Npchar.Fellows.Passengers.id0 = Npchar.index; // свой пассажир

			Npchar.Fellows.Passengers.boatswain = "-1";
			Npchar.Fellows.Passengers.navigator = "-1";
			Npchar.Fellows.Passengers.doctor = "-1";
			Npchar.Fellows.Passengers.cannoner = "-1";
			Npchar.Fellows.Passengers.treasurer = "-1";
			Npchar.Fellows.Passengers.carpenter = "-1";
            
			if(CheckAttribute(NPChar,"Hold_GenQuest")) DeleteAttribute(NPChar, "Hold_GenQuest");
			
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			DialogExit();
        break;
				
		case "Slave_1":
			dialog.text = "Ale "+GetAddress_Form(NPChar)+", nie możesz tego zrobić! Poddałem się.";
            link.l1 = "Zamknij swoją gębę! ... Zwiąż go.";
			link.l1.go = "Slave_2";
			link.l99 = "Dobrze. Zostań tutaj, dopóki nie zdecyduję...";
			link.l99.go = "exit";
		break;
		
		case "Slave_2":
			OfficersReaction("bad");		
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
            if (rand(5) == 1)
            {
    			dialog.text = "Nie ma mowy! Lepiej się zabić, niż zostać niewolnikiem!";
                link.l1 = "Przestań! To jest rozkaz!... Bosman! Posprzątaj ładunek...";
    			link.l1.go = "free_in_sea_4";
			}			
			else
			{
                if (rand(1) == 1)
                {
                    if (GetPrisonerQty() > 1)
                    {
                        dialog.text = "Rzeźnik! Chłopcy, dołączcie do mnie, nie mamy nic do stracenia!";
                        link.l1 = "Zły wybór, panie. Buntów się sam i bardzo szybko z nimi rozprawiam...";
            			link.l1.go = "free_in_sea_battle_all";
                    }
					else
					{
						dialog.text = "Nie ma mowy! Wolałbym umrzeć w walce!";
						link.l1 = "Jak sobie życzysz...";
						link.l1.go = "free_in_sea_battle_1";
					}	
    			}
    			else
    			{
					dialog.text = "Och, zgadzam się. Nie mam wyboru.";
                    link.l1 = "Wspaniale. Lepiej być żywym niewolnikiem niż martwym bohaterem.";
        			link.l1.go = "Slave_3";				
    			}			
			}
		break;

		case "Slave_3":
            ReleasePrisoner(NPChar); //  пленника в рабы
        	LAi_SetActorType(NPChar);
        	LAi_ActorRunToLocation(NPChar, "reload", "reload1", "none", "", "", "", 4.0);
        	ChangeCharacterComplexReputation(pchar,"nobility", -6);
        	DialogExit();
        	AddCharacterGoodsSimple(pchar, GOOD_SLAVES, 1);
        break;

		case "free_withoutFee":
			dialog.text = "Oh, "+GetAddress_Form(NPChar)+", czy naprawdę jesteś tak dobry i wypuszczasz mnie bez okupu?";
            link.l1 = "Tak, jestem. Jesteś teraz wolny,"+GetFullName(NPChar);
			link.l1.go = "free_withoutFee_2";
			link.l99 = "Hm... Masz rację! Potrzebuję więcej czasu na decyzję.";
			link.l99.go = "exit";
		break;

		case "free_withoutFee_2":
			dialog.text = "Dziękuję, "+GetFullName(PChar)+"! Będę się za ciebie modlić.";
            link.l1 = "Idź teraz i staraj się pozostać przy życiu, inaczej moja hojność okaże się na próżno.";
			link.l1.go = "free_withoutFee_3";
			OfficersReaction("good");
		break;
		
		case "free_withoutFee_3":
            ReleasePrisoner(NPChar); // освободили пленника
        	LAi_SetActorType(NPChar);
        	LAi_ActorRunToLocation(NPChar, "reload", "reload1", "none", "", "", "", 4.0);
        	ChangeCharacterComplexReputation(pchar,"nobility", 2);
        	DialogExit();
        break;	

		case "free_withoutFee_4":	
			switch(NPChar.EncType)
			{
				case "pirate":
					dialog.text = RandPhraseSimple("Dziękuję Ci, kapitanie. Nigdy nie zapomnę o Twojej dobroci. Zamierzam porzucić tę pracę i naprawiać małe łodzie w spokojnych portach. Potrafię to robić.","Dziękuję, kapitanie! Przysięgam, porzucę ten niewdzięczny zawód i zostanę rybakiem.");
					link.l1 = "Jeśli mówisz prawdę, to życzę ci szczęścia, a jeśli nie, to módl się, abyśmy się nigdy więcej nie spotkali...";	
				break;
				case "trade":
					dialog.text = "Nie wiem nawet, jak ci podziękować, kapitanie. Już straciłem nadzieję. Opowiem wszystkim o twojej dobroci. Daję ci słowo, że zapalę dla ciebie świecę! Tylko pozwól mi dotrzeć do kościoła.";
					link.l1 = "Do widzenia. A następnym razem nawet nie próbuj się opierać. Strzelaj do mnie, a będzie to wyrok śmierci dla ciebie i twojej załogi.";
				break;
				case "war":
					dialog.text = "Dziękuję ci, kapitanie. Będę za ciebie modlić się.";
					link.l1 = "Powodzenia, i pamiętaj, jeśli zdecydujesz się polować na mnie, to będzie twój koniec.";
				break;
			}
			link.l1.go = "free_withoutFee_3";
		break;
		
		case "free_in_sea_battle_1":
            ReleasePrisoner(NPChar); // освободили пленника        	
        	LAi_LocationFightDisable(&Locations[FindLocation("My_Deck")], false);
            LAi_SetFightMode(Pchar, true);
            LAi_SetWarriorType(NPChar);
            LAi_group_MoveCharacter(NPChar, LAI_GROUP_TmpEnemy);
            LAi_group_SetHearRadius(LAI_GROUP_TmpEnemy, 100.0);
            LAi_group_FightGroupsEx(LAI_GROUP_TmpEnemy, LAI_GROUP_PLAYER, true, Pchar, -1, false, false);
            LAi_group_SetRelation(LAI_GROUP_TmpEnemy, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_SetCheck(LAI_GROUP_TmpEnemy, "My_Deck_Battle_End");
            LAi_group_SetRelation(LAI_GROUP_TmpEnemy, "Prisoner", LAI_GROUP_NEITRAL);
        	DialogExit();
        break;		

		case "free_in_sea_battle_all":
			//ugeen --> привет Сиварду !!! после релиза пленников кол-во пассажиров уменьшается и цикл нихрена дальше не срабатывал
			for(int j = GetPassengersQuantity(pchar) - 1; j > -1; j--)
            {
                cn = GetPassenger(pchar, j);
                if(cn != -1)
                {
                    offref = GetCharacter(cn);
                    if (CheckAttribute(offref,"prisoned"))
                    {
        	            if(sti(offref.prisoned)==true && GetRemovable(offref)) // ставим только фантомов
        	            {
                        	ReleasePrisoner(offref); // освободили пленника
							LAi_SetWarriorType(offref);
							LAi_warrior_DialogEnable(offref, false);
                            LAi_group_MoveCharacter(offref, LAI_GROUP_TmpEnemy);
                        }
                    }
                }
            }
            LAi_LocationFightDisable(&Locations[FindLocation("My_Deck")], false);
            LAi_SetFightMode(Pchar, true);
			LAi_group_SetHearRadius(LAI_GROUP_TmpEnemy, 100.0);
            LAi_group_FightGroupsEx(LAI_GROUP_TmpEnemy, LAI_GROUP_PLAYER, true, Pchar, -1, false, false);
            LAi_group_SetRelation(LAI_GROUP_TmpEnemy, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_SetCheck(LAI_GROUP_TmpEnemy, "My_Deck_Battle_End");
        	DialogExit();
        break;
		
		case "free_in_sea_4":
        	ReleasePrisoner(NPChar); // освободили пленника
            NPChar.location = "";
	        LAi_KillCharacter(NPChar);
        	DialogExit();
        break;

		case "PunishmentAction":
			dialog.text = "Ale "+GetAddress_Form(NPChar)+", nie możesz tego zrobić! Poddałem się.";
			link.l1 = "Tylko po odejściu twoich ludzi. Zdradziłeś ich... Bosmanie! Weź go.";
			link.l1.go = "PunishmentAction1";
			link.l2 = "Cóż... Potrzebuję czasu, aby o tym pomyśleć. Zostań tu.";
			link.l2.go = "exit";
        break;

		case "PunishmentAction1":
			OfficersReaction("bad");		
			ChangeCharacterComplexReputation(pchar,"nobility", -2);			
			AddCharacterExpToSkill(Pchar, "Leadership", -150);
			if (rand(1) == 1)
            {
                if (GetPrisonerQty() > 1)
                {
                    dialog.text = "Rzeźnik! Chłopaki, nie mamy nic do stracenia!";
                    link.l1 = "Zły wybór, panie. Buntów sobie radzę sam i to bardzo szybko...";
					link.l1.go = "free_in_sea_battle_all";
                }
				else
				{
					dialog.text = "Nie ma mowy! Wolałbym umrzeć w walce!";
					link.l1 = "Jak sobie życzysz...";
					link.l1.go = "free_in_sea_battle_1";
				}	
    		}
			else
    		{
				dialog.text = "Przynajmniej daj mi trochę czasu na modlitwę...";
                link.l1 = "Módl się, jeśli chcesz.";
        		link.l1.go = "PunishmentAction2";				
    		}						
		break;
		
		case "PunishmentAction2":
        	ReleasePrisoner(NPChar); // освободили пленника
            NPChar.location = "";		
			NPChar.LifeDay = 0;
			LAi_CharacterDisableDialog(NPChar);
			DialogExit();
		break;
		
		case "free_tip_off":
			dialog.text = "Mam interesującą informację, która może być użyteczna dla człowieka takiego jak ty. Ale potrzebuję twoich gwarancji, że w zamian dostanę swoją wolność.";
			link.l1 = "Jak mogę dać ci moje gwarancje, jeśli nawet nie znam twojej propozycji? Wątpię, czy twoje informacje cokolwiek mi dadzą.";
			link.l1.go = "free_tip_off_0";
			link.l2 = "Mogę ci dać tylko moje słowo.";
			link.l2.go = "free_tip_off_1";
		break;
		
		case "free_tip_off_0":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);			
			DeleteAttribute(NPChar, "Hold_GenQuest");
			DialogExit();
		break;
		
		case "free_tip_off_1":
			switch(NPChar.EncType)
			{
				case "trade":
					sTmp = "He proposed me a freight but this guy was too greedy and I rejected the offer.";  
				break;
				case "war":
					sTmp = "I have escorted him a few times as a commander of a convoy.";
				break;
				case "pirate":
					sTmp = "I had an idea to rob him once but I have never had a single chance to do that.";
				break;
			}
			dialog.text = "Dobrze, to mi wystarczy. Teraz prosto do rzeczy, w "+XI_ConvertString("Kolonia"+NPChar.Hold_GenQuest.City+"Głos")+" mieszka bogaty kupiec "+NPChar.Hold_GenQuest.Name+". "+"Zarobił swoje bogactwo na swoim statku '"+NPChar.Hold_GenQuest.ShipName+" sprzedający "+GetStrSmallRegister(XI_ConvertString(Goods[sti(NPChar.Hold_GenQuest.Goods)].Name+"Acc"))+" z trasą : "+XI_ConvertString("Kolonia"+NPChar.Hold_GenQuest.FromCity)+" - "+XI_ConvertString("Colonia"+NPChar.Hold_GenQuest.ToCity)+". "+"Gdy ma za dużo ładunku, płaci za eskortę."+sTmp+"Jestem pewien, że ta informacja jest dla ciebie cenniejsza niż życie jednego człowieka.";
			link.l1 = "Wątpię, że ta informacja będzie dla mnie przydatna. Nie będę polować na spokojnych handlarzy.";	
			link.l1.go = "free_tip_off_0";
			link.l2 = "Nie jestem pewien, czy te informacje mi pomogą, ale dałem ci swoje słowo. Bosman przydzieli ci miejsce w mojej załodze i wypuści cię w najbliższym porcie.";
			link.l2.go = "free_tip_off_2";			
		break;
		
		case "free_tip_off_2":
			dialog.text = "Dziękuję, kapitanie! Nie miałem wątpliwości co do twojej uczciwości!";
			link.l1 = RandPhraseSimple(RandPhraseSimple("Chciałbym móc powiedzieć to samo o tobie","Przykro mi, ale nie mogę powiedzieć tego samego o tobie."),RandPhraseSimple("Idź i pamiętaj, że następnym razem nie będę tak hojny.","Idź i trzymaj się z dala od mojej drogi. Następnym razem nie uwierzę ci tak łatwo."));
			link.l1.go = "free_tip_off_3";
		break;
		
		case "free_tip_off_3":
			pchar.GenQuest.Hold_GenQuest.Goods 			= NPChar.Hold_GenQuest.Goods;			
			pchar.GenQuest.Hold_GenQuest.Nation 		= NPChar.Hold_GenQuest.Nation; 
			pchar.GenQuest.Hold_GenQuest.Name 			= NPChar.Hold_GenQuest.Name;
			pchar.GenQuest.Hold_GenQuest.ToCity 		= NPChar.Hold_GenQuest.ToCity;
			pchar.GenQuest.Hold_GenQuest.FromCity 		= NPChar.Hold_GenQuest.FromCity; 
			pchar.GenQuest.Hold_GenQuest.ShipName 		= NPChar.Hold_GenQuest.ShipName;				
			pchar.GenQuest.Hold_GenQuest.City 			= NPChar.Hold_GenQuest.City;
			pchar.GenQuest.Hold_GenQuest.CapName		= GetFullName(NPChar);
			pchar.GenQuest.Hold_GenQuest.Island			= GetArealByCityName(pchar.GenQuest.Hold_GenQuest.City); 
			pchar.GenQuest.Hold_GenQuest.Speak_Tavern 	= true;
			
			ReOpenQuestHeader("HoldQuest");
			AddQuestRecord("HoldQuest", "1");
			AddQuestUserData("HoldQuest", "sName", GetFullName(NPChar));
			AddQuestUserData("HoldQuest", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.Hold_GenQuest.Goods)].Name + "Acc"))); 
			AddQuestUserData("HoldQuest", "sCityFrom", XI_ConvertString("Colony" + pchar.GenQuest.Hold_GenQuest.FromCity));
			AddQuestUserData("HoldQuest", "sCityTo", XI_ConvertString("Colony" + pchar.GenQuest.Hold_GenQuest.ToCity));
			AddQuestUserData("HoldQuest", "sShipName", pchar.GenQuest.Hold_GenQuest.ShipName);
			
			SetFunctionTimerCondition("Hold_GenQuest_SetMerchant_pre", 0, 0, 1+rand(2), false);
			SetFunctionTimerCondition("Hold_GenQuest_MerchantOver", 0, 0, 30, false);
			
            ReleasePrisoner(NPChar); // освободили пленника
        	LAi_SetActorType(NPChar);
			NPChar.LifeDay = 0;
        	LAi_ActorRunToLocation(NPChar, "reload", "reload1", "none", "", "", "", 4.0);
        	DialogExit();			
		break;
	
		case "free_buyout":
			dialog.text = "I mam dla ciebie propozycję. W "+XI_ConvertString("Colonia"+NPChar.Hold_GenQuest.City+"Głos")+" mieszka mój przyjaciel, "+NPChar.Hold_GenQuest.Name+" to jego imię. Kiedyś prowadziliśmy razem interesy."+"Znajdź go tam. Jestem pewien, że zapłaci ci dużą sumę. On mi dłużny, a ja sam sobie z nim poradzę.";
			link.l1 = "Twój przyjaciel, co? Zobaczmy go.";	
			link.l1.go = "free_buyout1";
			link.l2 = "Dlaczego miałbym szukać twojego przyjaciela, skoro mogę dostać okup już w pierwszym porcie?";
			link.l2.go = "free_tip_off_0";
		break;
	
		case "free_buyout1":
			LAi_CharacterDisableDialog(NPChar);
			
			pchar.GenQuest.Hold_GenQuest.City 		= NPChar.Hold_GenQuest.City;			
			pchar.GenQuest.Hold_GenQuest.Nation 	= NPChar.Hold_GenQuest.Nation;
			pchar.GenQuest.Hold_GenQuest.Name 		= NPChar.Hold_GenQuest.Name;
			pchar.GenQuest.Hold_GenQuest.CapName	= GetFullName(NPChar);
			pchar.GenQuest.Hold_GenQuest.CapId		= NPChar.Id;
			pchar.GenQuest.Hold_GenQuest.TavernVariant = rand(1);
			pchar.GenQuest.Hold_GenQuest.Speak_Tavern = false;
			
			ReOpenQuestHeader("HoldQuest");
			AddQuestRecord("HoldQuest", "6");
			AddQuestUserData("HoldQuest", "sName", GetFullName(NPChar));
			AddQuestUserData("HoldQuest", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.Hold_GenQuest.City + "Voc")); 
			AddQuestUserData("HoldQuest", "sNameChar", NPChar.Hold_GenQuest.Name);
			DialogExit();
		break;

		case "free_by_hoard":
			dialog.text = "Właściwie znam jednego człowieka, który ma wspaniały skarb, ale nie ma jaj by go użyć.";
			link.l1 = "Co masz na myśli?";
			link.l1.go = "free_by_hoard1";
			link.l2 = "Oszczędź mi swoich opowieści. Lepiej martw się o swoją duszę.";
			link.l2.go = "free_tip_off_0";
		break;
		
		case "free_by_hoard1":
			dialog.text = "Mówię ci historię, która prowadzi do wielkich skarbów. W zamian potrzebuję twojego słowa, że wypuścisz mnie w następnym porcie.";
			link.l1 = "Samo zdecyduję, kiedy i co z tobą zrobić. Twoje 'historie' nie zrobią różnicy.";
			link.l1.go = "free_tip_off_0";
			link.l2 = "Słucham. Masz moje słowo.";
			link.l2.go = "free_by_hoard2";
		break;
		
		case "free_by_hoard2":
			dialog.text = "Ufam tak honorowemu "+GetSexPhrase("człowiek","kobieta")+". Ludzie jak ty zawsze dotrzymują słowa! Nie ważne, czy cały świat płonie, ty dotrzymasz swojego słowa! Czy mam rację, kapitanie?";
			link.l1 = "Opowiedz mi swoją historię, albo teraz cię wypuszczę... za burtę i bez głowy.";
			link.l1.go = "free_by_hoard4";
		break;
		
		case "free_by_hoard4":
			dialog.text = "Haha, dobry żart... Teraz słuchaj. Jest jeden kumpel w "+XI_ConvertString("Kolonia"+NPChar.Hold_GenQuest.City+"Głos")+" o nazwie "+NPChar.Hold_GenQuest.Name+", był naprawdę lekkomyślnym facetem w swojej młodości. Miał wiele 'transakcji' w tamtych czasach..."+"Więc pewnego razu w tawernie powiedział mi, że był członkiem "+GetName(NAMETYPE_VIP,NPChar.Hold_GenQuest.PirateName,NAME_ACC)+" gang i widział, jak ci piraci chowali skarb."+" Pięciu jego kumpli zginęło przez ten skarb... Krążyły plotki, że został złapany i powieszony, ale prawda jest taka, że wycofał się z biznesu i założył rodzinę. Pamiętał miejsce, gdzie ukrył skarb, nawet narysował mapę. Zaproponował mi, żebym towarzyszył mu w poszukiwaniu skarbu. Jest człowiekiem bardzo przesądnym, skarb był pokryty krwią, więc boi się tam iść sam. Przyznaję, z tego samego powodu ja też nie zdecydowałem się tam iść. "+"Był gotów sprzedać mapę, ale po co mi ona, skoro i tak nigdy tam nie pójdę...\nTo moja historia... Myślę, że taki odważny człowiek jak ty znajdzie ją przydatną, a mapa jest dość tania, tak przy okazji.";
			link.l1 = "I czy naprawdę sugerujesz, żebym to kupił? Twoja historia jest nieprawdziwa, więc łamię naszą umowę.";
			link.l1.go = "free_tip_off_0";
			link.l2 = "Ciekawa historia, choć nie do końca w niej wierzę. Ale masz moje słowo, idź i powiedz bosmanowi, żeby dał ci szafkę. Jesteś wolny.";
			link.l2.go = "free_by_hoard5";
		break;
		
		case "free_by_hoard5":
			dialog.text = "Dziękuję ci, kapitanie! Teraz widzę cenę słowa jednego "+GetSexPhrase("szlachcicu!","pani!");
			link.l1 = "Odejdź i nie stawaj mi na drodze. Następnym razem nie puści cię tak łatwo.");
			link.l1.go = "free_by_hoard6";
		break;
		
		case "free_by_hoard6":
			pchar.GenQuest.Hold_GenQuest.City 		= NPChar.Hold_GenQuest.City;			
			pchar.GenQuest.Hold_GenQuest.Nation 	= NPChar.Hold_GenQuest.Nation;
			pchar.GenQuest.Hold_GenQuest.Name 		= NPChar.Hold_GenQuest.Name;
			pchar.GenQuest.Hold_GenQuest.PirateName	= NPChar.Hold_GenQuest.PirateName;
			pchar.GenQuest.Hold_GenQuest.CapName	= GetFullName(NPChar);
			pchar.GenQuest.Hold_GenQuest.TavernVariant = rand(1) + 2;
			pchar.GenQuest.Hold_GenQuest.Sum		= 10000 + rand(10000);
			pchar.GenQuest.Hold_GenQuest.Treasure	= rand(1);
			pchar.GenQuest.Hold_GenQuest.Speak_Tavern = false;
			
			ReOpenQuestHeader("HoldQuest");
			AddQuestRecord("HoldQuest", "12");
			AddQuestUserData("HoldQuest", "sName", GetFullName(NPChar));
			AddQuestUserData("HoldQuest", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.Hold_GenQuest.City + "Voc")); 
			AddQuestUserData("HoldQuest", "sNameChar", pchar.GenQuest.Hold_GenQuest.Name);
			AddQuestUserData("HoldQuest", "sPirateName", GetName( NAMETYPE_VIP, pchar.GenQuest.Hold_GenQuest.PirateName, NAME_ACC));
			
            ReleasePrisoner(NPChar); // освободили пленника
        	LAi_SetActorType(NPChar);
			NPChar.LifeDay = 0;
        	LAi_ActorRunToLocation(NPChar, "reload", "reload1", "none", "", "", "", 4.0);
        	DialogExit();					
		break;
		
		case "free_in_sea":
			dialog.text = "Ale, "+GetAddress_Form(NPChar)+", jesteśmy na otwartym morzu! To tak, jakbym był skazany na śmierć!";
			link.l1 = "To jest to, czego chciałeś. Żegnaj. Bosman wykona moje polecenie.";
			link.l1.go = "PunishmentAction1";
			link.l2 = "Dobrze, jeszcze nie zdecydowałem.";
			link.l2.go = "exit";
		break;		
		
		//--> Jason, Ложный след
		case "FalseTrace_Prisoner":
			dialog.text = "Katerine! Naprawdę poprosiła cię, żebyś tutaj przyszedł? Taka cudowna dziewczyna...";
			link.l1 = "Zostawmy poezję kapitanie, i porozmawiajmy o poważniejszych rzeczach. Opowiem ci o obecnej sytuacji i oczekuję od ciebie odpowiedzi. Twoja odpowiedź zadecyduje o twoim i Katerine losie.";
			link.l1.go = "FalseTrace_Prisoner_1";
		break;
		
		case "FalseTrace_Prisoner_1":
			dialog.text = "Słucham, kapitanie.";
			link.l1 = "Znalazłem się na twoim fluita, ponieważ Adam Rayner, mąż Kateriny, powiedział mi, że na twoim statku jest mnóstwo srebra. Ten sztuczka pozwoliła mu odebrać kobietę, która kiedyś do niego należała i uciekła od niego do ciebie.";
			link.l1.go = "FalseTrace_Prisoner_2";
		break;
		
		case "FalseTrace_Prisoner_2":
			dialog.text = "Adam? Ten łajdak? To wszystko było jego planem! Teraz widzę... Tak, pomogłem Katrine uciec trzy miesiące temu. Ta biedna dziewczyna, nie masz pojęcia, jak ją traktował...";
			link.l1 = "Ona była jego żoną i nie obchodziło mnie, co się stało, to nie moja sprawa. Popełniłem błąd, wchodząc na twój galeon, ale teraz jest za późno, żeby o tym rozmawiać. Adam obiecał mi zapłacić za moją pomoc.";
			link.l1.go = "FalseTrace_Prisoner_3";
		break;
		
		case "FalseTrace_Prisoner_3":
			dialog.text = "Adam złożył obietnicę? Ha-ha! I mu zaufałeś? Kapitanie, czy w ogóle wiesz, jaki on jest? On...";
			link.l1 = "Katerine już dużo mi o nim powiedziała i włożyła w to wiele wysiłku. Ale jego propozycja ma sens i choć nie mam powodu, aby ufać temu łajdakowi, może tym razem mówi prawdę. Więc przejdźmy od razu do rzeczy...";
			link.l1.go = "FalseTrace_Prisoner_4";
		break;
		
		case "FalseTrace_Prisoner_4":
			dialog.text = "";
			link.l1 = "Miałem zamiar odkupić cię od władz i dostarczyć Adama z Katerine do "+XI_ConvertString("Kolonia"+pchar.questTemp.FalseTrace.QuestCity+"Acc")+", a potem uzyskaj od Adama informacje o złocie Zeza-Solly'ego i popłynąć do niego. Ale Katerine przekonała mnie, aby najpierw porozmawiać z tobą, powiedziała, że możesz zaoferować mi coś lepszego i bardziej niezawodnego niż zaoferował Adam, w zamian za wasze życie i wolność.";
			link.l1.go = "FalseTrace_Prisoner_5";
		break;
		
		case "FalseTrace_Prisoner_5":
			dialog.text = "";
			link.l1 = "Dlatego tu stoję i rozmawiam z tobą. Skończyłem. Teraz twoja kolej. Pomyśl o moich słowach i słowach Katerine, i daj mi swoje pomysły. Nie masz dużo czasu.";
			link.l1.go = "FalseTrace_Prisoner_6";
		break;
		
		case "FalseTrace_Prisoner_6":
			dialog.text = "Kapitanie! Chociaż nie uważam, że jesteś dobrym człowiekiem, ale wysłuchałeś błagań biednej dziewczyny i przybyłeś tutaj. Pokazuje mi to, że możesz być honorowy i współczujący. Nie potrzebuję czasu, jestem gotowa przedstawić ci swoją propozycję.";
			link.l1 = "Naprawdę? Doskonale! Cóż, słucham.";
			link.l1.go = "FalseTrace_Prisoner_7";
		break;
		
		case "FalseTrace_Prisoner_7":
			dialog.text = "Zaarestujesz Adama Raynera i zakujesz go w kajdany. Potem zabierzesz mnie i Katerine do "+XI_ConvertString("Colonia"+pchar.questTemp.FalseTrace.TargetCity)+". Nie ląduj w mieście, przecież to ty zatopiłeś mój galeon, wysadź nas wszystkich trzech na "+XI_ConvertString(pchar.questTemp.FalseTrace.TargetShore+"Gen")+"\nPoprosiłbym cię również o broń. Pójdziemy do miasta przez dżunglę i upewniam się, że ta kanalia zapłaci nie tylko za swoje przestępstwa, ale i za twoje. On na to zasługuje\nMasz moje słowo, że twoje imię nie wyjdzie na jaw. W zamian dostaniesz prawdziwe informacje dotyczące statku z złotem wroga\nTo nie będzie dla ciebie wielkim wyzwaniem, ale ma zęby, zdobędziesz dobre łupy. Dużo lepsze niż moje okup i 'tak zwane' skarby Zezowatego Solly. Czy mamy umowę?";
			link.l1 = "Nie podoba mi się twój plan. Myślę, że lokalne władze zorganizują na mnie polowanie, jak tylko opuszczę brzegi "+XI_ConvertString(pchar.questTemp.FalseTrace.TargetShore+"Gen")+". Nie, kapitanie, nie zamierzam ryzykować swoją głową. Nasza rozmowa jest zakończona.";
			link.l1.go = "FalseTrace_Prisoner_8";
			link.l2 = "Cóż, wygląda na to, że Katerine miała rację. Podoba mi się twoja propozycja. Adam Rayner zostanie aresztowany. Zaraz to załatwię. Zostaniesz zwolniony po aresztowaniu Adama. Do zobaczenia, kapitanie!";
			link.l2.go = "FalseTrace_Prisoner_9";
		break;
		
		case "FalseTrace_Prisoner_8":
			DialogExit();
			AddQuestRecord("FalseTrace", "9");
			AddQuestUserData("FalseTrace", "sCity", XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity));
			AddDialogExitQuestFunction("SetCheckForSolly");
			bQuestDisableMapEnter = false;
			LAi_CharacterDisableDialog(npchar);
			DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
		break;
		
		case "FalseTrace_Prisoner_9":
			DialogExit();
			AddQuestRecord("FalseTrace", "10");
			pchar.quest.FalseTraceSollyOver.over = "yes"; //снять таймер
			AddDialogExitQuestFunction("SetCheckForGoldShip");
			LAi_CharacterDisableDialog(npchar);
			pchar.questTemp.FalseTrace.PrisonerID = npchar.id;
			Pchar.questTemp.FalseTrace.PrisonerIDX = GetCharacterIndex(npchar.id);
		break;
		//<-- Ложный след
		
		// Addon-2016 Jason ФМК-Гваделупа
		case "FMQG":
			dialog.text = "Jesteś tutaj, żeby kaznodziejować, czy prowadzić biznes?";
			link.l1 = "Aby prowadzić interesy, potrzebuję twojego partnera w zbrodni - Bertranda Pinette. Jestem w głębokim gównie z powodu niego, gdzie mogę go znaleźć, co?";
			link.l1.go = "FMQG_1";
		break;
		
		case "FMQG_1":
			dialog.text = "Dlaczego myślisz, że ci to powiem?";
			link.l1 = "To twoja gęba na szafocie. Zabiorę cię do Basse-Terre, oddam gubernatorowi i otrzymam nagrodę za schwytanie dezertera, który zorganizował ucieczkę Carlosa de Milyar. Decyduj. Albo mówisz mi o lokalizacji Pinette, albo obaj płyniemy na Gwadelupę.";
			link.l1.go = "FMQG_2";
		break;
		
		case "FMQG_2":
			dialog.text = "Więc wszystko wiesz... Dobrze, powiem ci wszystko, co wiem o Bertrandzie Pinette, ale w zamian uwolnisz mnie.";
			link.l1 = "Więc powiedz mi. Wyląduję cię w Zatoce Mosquito, tak jak ostatnim razem. Ale jeśli mi skłamiesz, wrócę i podpalę tę plantację, którą podarował ci don Carlos, a także poinformuję Basse-Terre o twoim miejscu pobytu, więc nie będę jedynym, kto cię poluje.";
			link.l1.go = "FMQG_3";
		break;
		
		case "FMQG_3":
			dialog.text = "Pierwsze, wyląduj mnie tam. To sprawi, że poczuję się bezpieczniej i przysięgam, że opowiem ci wszystko.";
			link.l1 = "Dobrze. To nie jest tak, jakbyś miał gdziekolwiek iść.";
			link.l1.go = "FMQG_4";
		break;
		
		case "FMQG_4":
			DialogExit();
			AddQuestRecord("FMQ_Guadeloupe", "16");
			LAi_CharacterDisableDialog(npchar);
			pchar.questTemp.FMQG.PrisonerID = npchar.id;
			Pchar.questTemp.FMQG.PrisonerIDX = GetCharacterIndex(npchar.id);
			pchar.quest.FMQG_SailMoskitos.win_condition.l1 = "location";
			pchar.quest.FMQG_SailMoskitos.win_condition.l1.location = "Shore47";
			pchar.quest.FMQG_SailMoskitos.function = "FMQG_ArriveMoskitos";
			pchar.questTemp.FMQG = "to_moskitos";
			AddMapQuestMarkShore("Shore47", true);
			bDisableMapEnter = false; // Rebbebion, теперь можно
		break;
		
		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		
	}
}
