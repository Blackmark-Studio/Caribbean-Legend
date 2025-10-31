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
			dialog.text = "Mit akarsz, kapitány? A váltságdíjamról akar beszélni? Szeretném, ha tudná, hogy érdekel a lány sorsa...";
			link.l1 = "Katerine Raynerrôl beszélsz? Már tájékoztattak róla, "+pchar.questTemp.FalseTrace.CapName+". Ô kért meg, hogy beszéljek veled.";
			link.l1.go = "FalseTrace_Prisoner";
			break;	
		}
		//<-- Ложный след
		
		// Addon-2016 Jason ФМК-Гваделупа
		if (CheckAttribute(pchar, "questTemp.FMQG") && pchar.questTemp.FMQG != "fail" && CheckAttribute(pchar, "questTemp.FMQG.Prisoner") && GetFullName(npchar) == pchar.questTemp.FMQG.Prisoner)
		{
			dialog.text = "";
			link.l1 = "Látja, don Juan, az árulás rossz...";
			link.l1.go = "FMQG";
			break;	
		}
			if (sti(NPChar.nation) == PIRATE)
			{
				dialog.text = RandSwear() + "A foglyod vagyok, " + GetAddress_Form(NPChar) + ". De szeretném, ha tudnád, hogy " + NationNameNominative(sti(NPChar.nation)) + " soha nem fizetnek az embereikért. Mi mindannyian magunkért vagyunk.";
				link.l1 = "Hát... Látom, hogy nem fogok hasznot húzni belôled. Legalább váltságdíjat tudok fizetni érted, mint bûnözôért bármelyik kolónián.";
				link.l1.go = "offender";
				if (FindFreeRandomOfficer() > 0)
				{
					link.l2 = "Nézd, te egy képzett harcos vagy, és szükségem van az olyan emberekre, mint te. Szeretnél a parancsnokságom alatt szolgálni?";
					link.l2.go = "free_to_officer";
				}	
			}
			else
			{
				dialog.text = RandSwear() + "A foglyod vagyok, " + GetAddress_Form(NPChar) + ". " + NationNameNominative(sti(NPChar.nation)) + " jó árat fogok fizetni a szabadságomért.";
				if(NPChar.EncType == "trade" && FindFreeRandomOfficer() > 0 && CheckAttribute(NPChar, "Back.Ship.Mode") && NPChar.Back.Ship.Mode == "trade")
				{
					link.l1 = "Nézd, te egy képzett tengerész vagy, és szükségem van a hozzád hasonló emberekre. Szeretnél a parancsnokságom alatt szolgálni?";
					link.l1.go = "free_to_officer_trader";
				}
			}
			attrLoc = Sea_FindNearColony();
			if (attrLoc != "none") 
			{
                link.l3 = "Nem vagyunk messze a " + GetConvertStr(attrLoc +" várostól", "LocLables.txt") + ". És itt is elengedhetlek.";
			    link.l3.go = "free_withoutFee";
			}
			else
			{
                link.l3 = "Menj a hajóskapitányhoz, mondd meg neki, hogy adjon neked egy szekrényt. A következô kikötôben partra szállhattok.";
			    link.l3.go = "free_withoutFee_2";
			}			
			link.l4 = "Gondolom, nagyszerû rabszolgát faragok belôled - erôset és engedelmeset.";
			link.l4.go = "Slave_1";
			link.l5 = "Figyelmen kívül hagytad a parancsot, hogy engedd le a vitorlákat, és erôvel ellenálltál. Ezért fel fognak akasztani. A csónakmester már megkapta a parancsomat.";
			link.l5.go = "PunishmentAction";
			link.l99 = "Tudom.";
			link.l99.go = "exit";
			NextDiag.TempNode = "second time"; 
		break;
		
		case "second time":
			if(CheckAttribute(NPChar,"Hold_GenQuest") && !CheckAttribute(pchar,"GenQuest.Hold_GenQuest"))
			{
				switch(sti(NPChar.Hold_GenQuest.variant))
				{				
					case 0: // "tipp"
						dialog.text = RandPhraseSimple("Kapitány, szeretné meghallgatni a javaslatomat a váltságdíjam jövedelmezôbb változatáról?",
							"Megértem, hogy nálam nincs helye cserekereskedelemnek, de meghallgatná a javaslatomat?");
						link.l1 = "Hallgatlak.";	
						link.l1.go = "free_tip_off";
					break;
					
					case 1:
						dialog.text = "Kapitány, miért nem enged el egyszerûen? Nincs értékem az ön számára. Ha eladsz rabszolga-kereskedôknek, csak néhány érmét és rossz hírnevet kapsz.";
						link.l1 = "És ha egyszerûen elengedlek, akkor semmit sem kapok...";
						link.l1.go = "free_by_hoard";
						attrLoc = Sea_FindNearColony();
						if (attrLoc != "none") 
						{
							link.l2 = "Figyelmen kívül hagytad a parancsot, hogy engedd le a vitorlákat, és erôvel ellenálltál. Ezért fel fognak akasztani. A csónakmester már megkapta a parancsomat.";
							link.l2.go = "PunishmentAction";							
						}
						else
						{
							link.l2 = "Nagyon ragaszkodsz hozzá, úgyhogy azt hiszem, meg tudom adni neked, amit akarsz. Most már szabad ember vagy. Hagyd el a hajómat.";
							link.l2.go = "free_in_sea";
						}
						link.l3 = LinkRandPhrase("Ne tegye próbára a türelmemet. Már az is szerencsés ember, hogy életben maradt.",
							"Megvannak a saját terveim veled.","Feltételezem, hogy a jövôben még hasznomra lehetsz.");
						link.l3.go = "exit";	
					break;
					
					case 2: // "váltságdíj"
						dialog.text = "Kapitány, ez a bizonytalanság megöl engem. Megkérdezhetem, hogy mit tervez velem?";
						link.l1 = "Van valami, amit fel tud ajánlani nekem?";
						link.l1.go = "free_buyout";
						link.l2 = RandPhraseSimple("Még nincs semmi ötletem veled kapcsolatban.",
							RandPhraseSimple("tervek? Ágyúgolyó a nyakadon? Csak vicceltem, ha!","A foglyom vagy, és minden jogom megvan hozzá, hogy azt csináljak veled, amit akarok. A saját véleményednek itt nincs értéke."));
						link.l2.go = "exit";
					break;										
				}
				NextDiag.TempNode = "second time"; 
			}
			else
			{
				if (sti(NPChar.nation) == PIRATE)
				{
					dialog.text = "Kapitány, miért nem enged el? Nincs rám szüksége. A kalózkodás volt az egyetlen lehetôség számomra, mert nem rendelkezem értékes képességekkel vagy képzettséggel. Az volt a vágyam, hogy pénzt keressek, és aztán visszavonulhassak.";
					if (FindFreeRandomOfficer() > 0)
					{
						link.l2 = "Nézd, te egy képzett harcos vagy, és szükségem van az olyan mészárosokra, mint te. Szeretnél a tisztem lenni?";
						link.l2.go = "free_to_officer";
					}				
					link.l3 = LinkRandPhrase("Nincs kegyelem neked. A tengeren sok a gengszter. Most legalább eggyel kevesebben fognak hajózni.",
						" Bármilyen probléma, 'tengeri farkas'? maradj itt és maradj csendben.",
						"akasztófa vár a fajtádra. Eladlak titeket a hatóságoknak, és ez nagy lecke lesz minden kalóznak.");	
					link.l3.go = "exit";
				}
				else
				{
					if(NPChar.EncType == "trade")
					{
						dialog.text = "Kapitány, könyörgöm... Engedj el. Családom és gyerekeim vannak, és nem fognak nélkülem élni.";
						if (FindFreeRandomOfficer() > 0 && CheckAttribute(NPChar, "Back.Ship.Mode") && NPChar.Back.Ship.Mode == "trade")
						{
							link.l2 = "Nézd, te egy képzett tengerész vagy, és szükségem van a hozzád hasonló emberekre. Szeretnél a parancsnokságom alatt szolgálni?";
							link.l2.go = "free_to_officer_trader";
						}
						link.l3 = LinkRandPhrase("Megvannak a saját terveim veled kapcsolatban.","Gondolom, hogy a jövôben még hasznomra lehetsz.","A foglyom vagy, és minden jogom megvan hozzá, hogy azt tegyek veled, amit akarok.");
						link.l3.go = "exit";
					}
					if(NPChar.EncType == "war")
					{
						dialog.text = RandPhraseSimple("Kapitány, elvesztettem egy harcot, és kegyelemért könyörgök. ",
							"Kapitány, könyörgöm a nagylelkûségedért. Megértem, hogy nincs oka arra, hogy hadifogolyként bánjon velem, ezért kérem, hogy kíméljen meg. Szavamat adom, hogy elkerülöm a találkozást a tengeren.");
						link.l2 = LinkRandPhrase("Ne tegye próbára a türelmemet. Már az is szerencsés ember, hogy életben maradt.", 
							RandPhraseSimple("Megvannak a saját terveim veled.","Feltételezem, hogy a jövôben még hasznomra lehetsz."),
							RandPhraseSimple("A foglyom vagy, és minden jogom megvan hozzá, hogy azt tegyek veled, amit akarok. A saját véleményednek itt nincs értéke.",
							"Ön... nos, ön egy hadihajó kapitánya volt, és tisztában volt a kockázatokkal. Ne próbáld magad itt szentként beállítani."));
						link.l2.go = "exit";	
						if (isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 1)
						{
							if(sti(Items[sti(pchar.EquipedPatentId)].Nation) == sti(NPChar.nation) && FindFreeRandomOfficer() > 0)
							{
								link.l3 = "Nézd, te egy képzett harcos vagy, és szükségem van az olyan mészárosokra, mint te. Szeretnél a tisztem lenni?";
								link.l3.go = "free_to_officer";
							}
						}
					}
				}
				attrLoc = Sea_FindNearColony();
				if (attrLoc != "none") 
				{
					link.l4 = "Nem vagyunk messze a " + GetConvertStr(attrLoc +" várostól", "LocLables.txt") + ". És itt is elengedhetlek.";
					link.l4.go = "free_withoutFee";
				}
				else
				{
					if(NPChar.EncType == "trade" || NPChar.EncType == "pirate")
					{
						link.l4 = "Menj a hajóskapitányhoz, mondd meg neki, hogy adjon neked egy szekrényt. A következô kikötôben partra szállhattok.";
						link.l4.go = "free_withoutFee_4";			
					}	
					else
					{
						link.l4 = "A fenébe veled! Menj a hajóskapitányhoz, mondd meg neki, hogy adjon neked egy szekrényt. A következô kikötôben partra szállhatsz. És ne feledd, hogy a következô találkozásunk lesz az utolsó.";
						link.l4.go = "free_withoutFee_4";
					}
				}				
				link.l5 = "Figyelmen kívül hagytad a parancsot, hogy engedd le a vitorlákat, és erôvel ellenálltál. Ezért fel fognak akasztani. A csónakmester már megkapta a parancsomat.";
				link.l5.go = "PunishmentAction";
				NextDiag.TempNode = "second time"; 
			}	
		break;
		
		case "offender":
			dialog.text = "Bûnözô? Viccelsz velem," + GetAddress_Form(NPChar) + "!";
			link.l1 = "Nem viccelek. Te kalóz vagy.";
			link.l1.go = "exit";
		break;
		
		case "free_to_officer":
			if ((GetSummonSkillFromName(pchar, "Leadership") + 20) <= GetSummonSkillFromName(npchar, "Leadership"))
			{
				dialog.text = "A te parancsnokságod alatt szolgálok? Jobb, ha megetetem a cápákat!";
				link.l1 = "Vigyázz a nyelvedre, különben megeteted ôket.";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Hogy a tisztje legyen, " + GetAddress_Form(NPChar) + "? Egyetértek. Tudom a munkámat, és nincs vesztenivalóm.";
				link.l1 = "Megegyeztünk! Menj és végezd a munkád.";
				link.l1.go = "free_to_officer_Hire";
				link.l2 = "Várj egy kicsit, meggondoltam magam.";
				link.l2.go = "exit";
			}
		break;

		case "free_to_officer_trader":
			if (GetSummonSkillFromName(pchar, "Leadership") <= GetSummonSkillFromName(npchar, "Leadership"))
			{
				dialog.text = LinkRandPhrase("Csábító ajánlat... de vissza kell utasítanom. Elvbôl.",
					"Sajnálom, de azok után, amit a barátaimmal tettél... Ez lehetetlen.",
					"Nem, kapitány. Ennyi terror után nem tudom tovább végezni ezt a munkát. Fogadalmat tettem, hogy ha a Boldogságos Szûz meghallgatja imáimat és megadja nekem a szabadságot, nem hajózom tovább.");
				link.l1 = "A te döntésed. Nem leszek kitartó.";	
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Miért nem? Rossz kapitány vagyok, elvesztettem a hajómat, és a parton nem maradt számomra semmi. Kivéve a számlákat és az adósságokat...";
				link.l1 = "Megegyeztünk! Menj a hajóskapitányhoz, és vedd fel a járandóságaidat. Kicsit késôbb adok neked egy helyet a hajómon.";	
				link.l1.go = "free_to_officer_Hire";
				link.l2 = "Várj egy kicsit, meggondoltam magam.";
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
			dialog.text = "De " + GetAddress_Form(NPChar) + ", ezt nem teheted meg! Megadtam magam.";
            link.l1 = "Fogd be a szád! ... Kötözzétek meg.";
			link.l1.go = "Slave_2";
			link.l99 = "Rendben. Maradj itt, amíg nem döntök...";
			link.l99.go = "exit";
		break;
		
		case "Slave_2":
			OfficersReaction("bad");		
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
            if (rand(5) == 1)
            {
    			dialog.text = "Ne már! Inkább megölöm magam, minthogy rabszolga legyek!";
                link.l1 = "Hagyjátok abba! Ez parancs! Csónakos! Tisztítsd meg a rakományt...";
    			link.l1.go = "free_in_sea_4";
			}			
			else
			{
                if (rand(1) == 1)
                {
                    if (GetPrisonerQty() > 1)
                    {
                        dialog.text = "Mészáros! Srácok, csatlakozzatok hozzám, nincs vesztenivalónk!";
                        link.l1 = "Rossz választás, hölgyeim. A lázadásokat én magam intézem el, és nagyon gyorsan...";
            			link.l1.go = "free_in_sea_battle_all";
                    }
					else
					{
						dialog.text = "Kizárt dolog! Inkább meghalok a harcban!";
						link.l1 = "Ahogy akarod...";
						link.l1.go = "free_in_sea_battle_1";
					}	
    			}
    			else
    			{
					dialog.text = "Ó, egyetértek. Nincs más választásom.";
                    link.l1 = "Nagyszerû. Jobb egy lélegzô rabszolgának lenni, mint egy halott hôsnek.";
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
			dialog.text = "Ó, " + GetAddress_Form(NPChar) + ", tényleg ilyen kedves vagy, és váltságdíj nélkül elengedsz?";
            link.l1 = "Igen, így van. Most már szabad vagy," + GetFullName(NPChar);
			link.l1.go = "free_withoutFee_2";
			link.l99 = "Hm... Igazad van! Több idôre van szükségem, hogy eldöntsem.";
			link.l99.go = "exit";
		break;

		case "free_withoutFee_2":
			dialog.text = "Köszönöm, "+GetFullName(PChar) + "! Imádkozni fogok érted.";
            link.l1 = "Menj most, és próbálj meg életben maradni, különben a nagylelkûségem hiábavaló lesz.";
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
					dialog.text = RandPhraseSimple("Köszönöm, kapitány. Soha nem felejtem el a kedvességét. Otthagyom ezt a munkát, és békés kikötôkben fogok kis hajókat javítani. Meg tudom csinálni.",
						"Köszönöm, kapitány úr! Esküszöm, felhagyok ezzel a hálátlan foglalkozással, és halász leszek.");
					link.l1 = "Ha ôszinte vagy, akkor sok szerencsét kívánok, ha nem, akkor imádkozz, hogy soha többé ne találkozzunk...";	
				break;
				case "trade":
					dialog.text = "Nem is tudom, hogyan köszönjem meg, kapitány. Már elvesztettem a reményt. Mindenkinek el fogom mesélni a kedvességét. Szavamat adom, hogy gyertyát gyújtok önért! Csak hadd jussak el egy templomba.";
					link.l1 = "Viszontlátásra. És legközelebb meg se próbáljon ellenállni. Ha rám lôsz, az halálos ítélet lesz számodra és a bandád számára.";
				break;
				case "war":
					dialog.text = "Köszönöm, kapitány. Imádkozni fogok önért.";
					link.l1 = "Sok szerencsét, és ne feledje, ha úgy dönt, hogy levadászik engem, az lesz a maga vége.";
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
			dialog.text = "De " + GetAddress_Form(NPChar) + ", ezt nem teheted meg! Megadtam magam.";
			link.l1 = "Csak miután az emberei elmentek. Elárulta ôket... Csónakos! Vigyétek!";
			link.l1.go = "PunishmentAction1";
			link.l2 = "Hát... Idôre van szükségem, hogy átgondoljam. Maradj itt.";
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
                    dialog.text = "Mészáros! Srácok, nincs vesztenivalónk!";
                    link.l1 = "Rossz választás, hölgyeim. A lázadásokat én magam intézem el, és nagyon gyorsan...";
					link.l1.go = "free_in_sea_battle_all";
                }
				else
				{
					dialog.text = "Kizárt dolog! Inkább meghalok a harcban!";
					link.l1 = "Ahogy akarod...";
					link.l1.go = "free_in_sea_battle_1";
				}	
    		}
			else
    		{
				dialog.text = "Legalább adjatok egy kis idôt imádkozni...";
                link.l1 = "Imádkozz, ha akarsz.";
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
			dialog.text = "Van egy érdekes információm, ami hasznos lehet egy olyan embernek, mint te. De szükségem van a garanciátokra, hogy cserébe megkapom a szabadságomat.";
			link.l1 = "Hogyan adhatnék garanciát, ha nem is ismerem az ajánlatát? Kétlem, hogy az információi egyáltalán bármit is adnának nekem.";
			link.l1.go = "free_tip_off_0";
			link.l2 = "Csak a szavamat tudom adni.";
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
					sTmp = "Fuvart ajánlott nekem, de ez a fickó túl mohó volt, és én visszautasítottam az ajánlatot.";  
				break;
				case "war":
					sTmp = "Néhányszor elkísértem ôt, mint konvojparancsnok.";
				break;
				case "pirate":
					sTmp = "Egyszer volt egy ötletem, hogy kiraboljam, de erre még soha nem volt lehetôségem.";
				break;
			}
			dialog.text = "Jól van. Nekem elég lesz. Most pedig egyenesen az üzlethez, a " + XI_ConvertString("Colony" + NPChar.Hold_GenQuest.City + "Voc") + " lakik egy gazdag kereskedô " + NPChar.Hold_GenQuest.Name + ". " + 
				"vagyonát hajóján szerezte '" + NPChar.Hold_GenQuest.ShipName + " árulja " + GetStrSmallRegister(XI_ConvertString(Goods[sti(NPChar.Hold_GenQuest.Goods)].Name + "Acc")) + " útvonalon : " + XI_ConvertString("Colony" + NPChar.Hold_GenQuest.FromCity) + " - " + XI_ConvertString("Colony" + NPChar.Hold_GenQuest.ToCity) +". " + 
				"Ha túl sok rakománya van, fizet egy kísérôért." + sTmp + " Biztos vagyok benne, hogy ez az információ értékesebb az Ön számára, mint egy egyedülálló férfi élete.";
			link.l1 = "Kétlem, hogy ez az információ hasznos lehet számomra. Nem fogok békés kereskedôkre vadászni.";	
			link.l1.go = "free_tip_off_0";
			link.l2 = "Nem biztos, hogy ez az információ hasznomra válik, de a szavamat adtam. A csónakmester a legénységemhez helyez téged, és a legközelebbi kikötôben elenged.";
			link.l2.go = "free_tip_off_2";			
		break;
		
		case "free_tip_off_2":
			dialog.text = "Köszönöm, kapitány! Nem kételkedtem az ôszinteségedben!";
			link.l1 = RandPhraseSimple(RandPhraseSimple("Bárcsak ugyanezt mondhatnám rólad","Sajnálom, de nem mondhatom el ugyanezt rólad."),
				RandPhraseSimple("Menj és ne feledd, hogy legközelebb nem leszek ilyen nagylelkû.","Menj és ne állj az utamba. Legközelebb nem fogok ilyen könnyen hinni neked."));
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
			dialog.text = "És van egy javaslatom számodra. A " + XI_ConvertString("Colony" + NPChar.Hold_GenQuest.City + "Voc") + " lakik a barátom, " + NPChar.Hold_GenQuest.Name + " a neve. Egyszer volt egy közös üzletünk." +
				"keresd meg ôt ott. Biztos vagyok benne, hogy nagy összeget fog fizetni neked. Tartozik nekem, és én magam fogok vele foglalkozni.";
			link.l1 = "A barátod, mi? Hadd lássuk.";	
			link.l1.go = "free_buyout1";
			link.l2 = "Miért keresném a barátodat, ha már az elsô kikötôben váltságdíjat kaphatok?";
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
			dialog.text = "Valójában ismerek egy embert, akinek van egy szép kincse, de nincs mersze használni.";
			link.l1 = "Hogy érti ezt?";
			link.l1.go = "free_by_hoard1";
			link.l2 = "Kímélj meg a történeteidtôl. Inkább a lelkedért aggódj.";
			link.l2.go = "free_tip_off_0";
		break;
		
		case "free_by_hoard1":
			dialog.text = "Elmondom neked a történetet, amely egy nagy kincshez vezet. A szavadat kérem cserébe, hogy elengedsz a következô kikötôben.";
			link.l1 = "Magam fogom eldönteni, hogy mikor és mit tegyek veled. A te 'történeteid' nem fognak változtatni.";
			link.l1.go = "free_tip_off_0";
			link.l2 = "Hallgatlak. A szavamat adom.";
			link.l2.go = "free_by_hoard2";
		break;
		
		case "free_by_hoard2":
			dialog.text = "Bízom egy ilyen becsületes "+ GetSexPhrase("férfiban","nôben") +". Az olyan emberek, mint te, mindig megtartják a szavukat! Nem számít, ha az egész világ lángol, te megtartod a szavad! Igazam van, kapitány?";
			link.l1 = "Mondd el a történeted, vagy azonnal elengedlek... a fedélzetre és fej nélkül.";
			link.l1.go = "free_by_hoard4";
		break;
		
		case "free_by_hoard4":
			dialog.text = "Ha-ha, jó vicc... Most figyelj. Van egy haver a " + XI_ConvertString("Colony" + NPChar.Hold_GenQuest.City + "Voc") + 
				" -ban, a neve " + NPChar.Hold_GenQuest.Name + ", ô egy nagyon vakmerô fickó volt fiatal korában. Rengeteg 'deál' volt neki akkoriban..." + 
				"Szóval egyszer a kocsmában elmesélte, hogy ô is tagja volt a " + GetName( NAMETYPE_VIP, NPChar.Hold_GenQuest.PirateName, NAME_ACC) + " bandának, és látta, hogy azok a kalózok hogyan ássák el a kincset." +
				" Öt haverját ölette meg a kincs miatt... Voltak olyan pletykák, hogy elkapták és felakasztották, de az igazság az, hogy visszavonult az üzlettôl, és így alapított családot. Emlékezett a kincs helyére, még térképet is rajzolt. Felajánlotta, hogy elkísérem a kincs keresésére. Babonás ember ô, a kincset vér borította, ezért fél egyedül odamenni. Bevallom, én sem mertem ugyanezen okból. "+ 
                "Kész volt eladni a térképet, de minek nekem, ha úgysem megyek oda soha...\nEz az én történetem... Szerintem egy ilyen bátor embernek, mint te, hasznos lehet, és a térkép egyébként elég olcsó.";
			link.l1 = "És tényleg azt javaslod, hogy vegyem meg? A történeted nem igaz, úgyhogy felbontom a megállapodásunkat.";
			link.l1.go = "free_tip_off_0";
			link.l2 = "Érdekes történet, bár nem igazán hiszek benne. De a szavamat adom, menj és szólj a csónakosnak, hogy adjon neked egy szekrényt. Szabad vagy.";
			link.l2.go = "free_by_hoard5";
		break;
		
		case "free_by_hoard5":
			dialog.text = "Köszönöm, kapitány! Most már látom, hogy egy "+ GetSexPhrase("úriember szavának ára van!","hölgy!");
			link.l1 = "Menj és ne állj az utamba. Legközelebb nem engedlek el ilyen könnyen.");
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
			dialog.text = "De, " + GetAddress_Form(NPChar) + ", a nyílt tengeren vagyunk! Ez ugyanaz, mintha kivégeztek volna!";
			link.l1 = "Ezt akartad. Viszlát. A csónakos teljesíti a parancsomat.";
			link.l1.go = "PunishmentAction1";
			link.l2 = "Rendben, még nem döntöttem.";
			link.l2.go = "exit";
		break;		
		
		//--> Jason, Ложный след
		case "FalseTrace_Prisoner":
			dialog.text = "Katerine! Tényleg megkért, hogy gyere ide? Milyen csodálatos lány...";
			link.l1 = "Maradjunk távol a költô kapitánytól, és beszéljünk komolyabb dolgokról. Elmondom neked a jelenlegi helyzetet, és várom a választ tôled. A válaszod fogja meghatározni a te és Katerine sorsát.";
			link.l1.go = "FalseTrace_Prisoner_1";
		break;
		
		case "FalseTrace_Prisoner_1":
			dialog.text = "Figyelek, kapitány.";
			link.l1 = "Azért szálltam fel a flottátok fedélzetére, mert Adam Rayner, Katerin férje azt mondta, hogy sok ezüst van a hajótokon. Ez a trükk lehetôvé tette, hogy elvigyen egy nôt, aki egykor az övé volt, és elszökött tôle hozzád.";
			link.l1.go = "FalseTrace_Prisoner_2";
		break;
		
		case "FalseTrace_Prisoner_2":
			dialog.text = "Adam? Az a fattyú? Az egész az ô terve volt! Most már értem... Igen, három hónappal ezelôtt segítettem Katrine-nek megszökni. Szegény lány, fogalmad sincs, hogyan bánt vele...";
			link.l1 = "A felesége volt, és engem nem érdekel, hogy mi történt, nem tartozik rám. Hibát követtem el, amikor beszálltam a folyosóra, de már túl késô errôl beszélni. Adam megígérte, hogy fizet a segítségemért.";
			link.l1.go = "FalseTrace_Prisoner_3";
		break;
		
		case "FalseTrace_Prisoner_3":
			dialog.text = "Adam ígéretet tett? Ha-ha! És te bíztál benne? Kapitány, tudja egyáltalán, milyen ember ô? Ô...";
			link.l1 = "Katerine már sokat mesélt róla, és nagyon sokat tett érte. De az ajánlatának van értelme, és bár nincs okom megbízni ebben a szemétládában, de talán ezúttal igazat mond. Szóval térjünk a lényegre...";
			link.l1.go = "FalseTrace_Prisoner_4";
		break;
		
		case "FalseTrace_Prisoner_4":
			dialog.text = "";
			link.l1 = "Úgy volt, hogy váltságdíjat követelek a hatóságoktól, és átadom Ádámot Katerine-nel együtt a "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity+"Acc")+", majd megszerzem Ádámtól az információt a kancsal-szemû Solly aranyáról, és elhajózom hozzá. De Katerine meggyôzött, hogy elôbb beszéljek veletek, azt mondta, hogy talán valami jobb és megbízhatóbb ajánlatot tudtok tenni, mint Adam, cserébe az életetekért és a szabadságotokért.";
			link.l1.go = "FalseTrace_Prisoner_5";
		break;
		
		case "FalseTrace_Prisoner_5":
			dialog.text = "";
			link.l1 = "Ezért állok itt és beszélek veletek. Befejeztem. Most ti következtek. Gondolkodjatok el az én szavaimon és Katerine szavain, és mondjátok el az ötleteiteket. Nincs sok idôtök.";
			link.l1.go = "FalseTrace_Prisoner_6";
		break;
		
		case "FalseTrace_Prisoner_6":
			dialog.text = "Kapitány úr! Bár nem hiszem, hogy jó ember vagy, de meghallgattad egy szegény lány könyörgését, és idejöttél. Ez azt mutatja nekem, hogy tudsz becsületes lenni és szánalmat érezni. Nincs szükségem idôre, kész vagyok átadni az ajánlatomat.";
			link.l1 = "Tényleg? Kitûnô! Nos, akkor hallgatlak.";
			link.l1.go = "FalseTrace_Prisoner_7";
		break;
		
		case "FalseTrace_Prisoner_7":
			dialog.text = "Letartóztatja Adam Raynert, és láncra veri. Aztán engem és Katerine-t elvisznek a "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.TargetCity)+". Ne szállj le a városban, elvégre te voltál az, aki elsüllyesztette a flottámat, dobj le mindhármunkat a " + XI_ConvertString(pchar.questTemp.FalseTrace.TargetShore+"Gen") + "\nFegyvert is kérnék tôled. A dzsungelen keresztül megyünk a városba, és gondoskodom róla, hogy a söpredék ne csak a bûneiért fizessen, hanem a tiédért is. Megérdemli\nA szavamat adom, hogy a neved nem fog felmerülni. Cserébe igaz információt adok neked egy ellenséges állam aranyat tartalmazó hajóról\nEz nem lesz nagy kihívás számodra, de foga van, szép zsákmányt szerzel. Sokkal jobbat, mint az én váltságdíjam és 'úgynevezett' Squint-szemû Solly kincsei. Megegyeztünk?";
			link.l1 = "Nem tetszik a terved. Azt hiszem, hogy a helyi hatóságok vadászatot szerveznek rám, amint elhagyom a " + XI_ConvertString(pchar.questTemp.FalseTrace.TargetShore+"Gen") + "partjait. Nem, kapitány, nem fogom kockáztatni a fejemet. A beszélgetésünknek vége.";
			link.l1.go = "FalseTrace_Prisoner_8";
			link.l2 = "Nos, úgy tûnik, Katerine-nek igaza volt. Tetszik az ajánlatod. Adam Raynert le fogják tartóztatni. Azonnal elintézem. Miután letartóztattuk Adamet, szabadon engedjük. Viszlát, kapitány!";
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
			dialog.text = "Prédikálni vagy üzletelni jött?";
			link.l1 = "Az üzlethez. Szükségem van a bûntársára, Bertrand Pinette-re. Miatta vagyok nagy szarban. Hol találom meg?";
			link.l1.go = "FMQG_1";
		break;
		
		case "FMQG_1":
			dialog.text = "Miért gondolja, hogy ezt elmondom magának?";
			link.l1 = "A maga segge a tét. Elviszem Basse-Terre-be, átadom a kormányzónak, és jutalmat kapok egy dezertôr elfogásáért, aki megszervezte Carlos de Milyar szökését. A te döntésed. Vagy elmondja nekem Pinette tartózkodási helyét, vagy mindketten Guadeloupe felé vesszük az irányt.";
			link.l1.go = "FMQG_2";
		break;
		
		case "FMQG_2":
			dialog.text = "Tehát mindent tudsz... Rendben, elmondok mindent, amit Bertrand Pinette-rôl tudok, de cserébe szabadon enged.";
			link.l1 = "Akkor menj és mondd el. A Mosquito öbölben fogok leszállni, ahogy legutóbb is tettem. De ha hazudsz nekem, visszatérek, és felgyújtom azt az ültetvényt, amit don Carlos ajándékozott neked, és Basse-Terre-t is értesítem a hollétedrôl, hogy ne csak én legyek az egyetlen, aki vadászik rád.";
			link.l1.go = "FMQG_3";
		break;
		
		case "FMQG_3":
			dialog.text = "Elôször is, tegyél le ott. Ettôl majd nagyobb biztonságban érzem magam, és esküszöm, hogy mindent elmondok.";
			link.l1 = "Rendben. Nem mintha bárhová is mennél.";
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
