// boal 08/04/06 общий диалог верфи
#include "DIALOGS\%language%\Rumours\Common_rumours.c"  //homo 25/06/06
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sTemp;
	string s2;
	
	int iShipClass = GetCharacterShipClass(PChar); // Если корабля нет, вернет 7 (лодка)
	int iRank = sti(PChar.rank);
	int iSumm, iType;
	
	ref rRealShip;
	ref shTo;
	aref refShip;
	string attr;
	float fTmp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Shipyard\" + NPChar.City + "_Shipyard.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 16/06/06
    bool ok;
    int iTest = FindColony(NPChar.City); // город магазина
    ref rColony;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	
	int Material, WorkPrice;
	int amount;
	int	iCannonDiff;
	
	// генератор парусов по кейсу -->
	string attrLoc   = Dialog.CurrentNode;
	int i;
  	if (findsubstr(attrLoc, "SailsColorIdx_" , 0) != -1)
 	{
        i = findsubstr(attrLoc, "_" , 0);
	 	NPChar.SailsColorIdx = strcut(attrLoc, i+1, strlen(attrLoc)-1); // индех в конце
 	    Dialog.CurrentNode = "SailsColorDone";
 	}
 	if (findsubstr(attrLoc, "SailsTypeChooseIDX_" , 0) != -1)
 	{
        i = findsubstr(attrLoc, "_" , 0);
	 	NPChar.SailsTypeChooseIDX = strcut(attrLoc, i+1, strlen(attrLoc)-1); // индех в конце
 	    Dialog.CurrentNode = "SailsTypeChoose2";
 	}
	if(!CheckAttribute(NPChar, "ExpMeeting"))
	{
		NPChar.ExpMeeting = true;
		notification("Elsô hajógyári látogatás " + XI_ConvertString("Colony" +NPChar.City + "Gen"), "Carpenter");
		AddCharacterExpToSkill(pchar, SKILL_REPAIR, 10.0);
	}
 	// генератор парусов по кейсу <--
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "ship_tunning_not_now":  // аналог выхода, со старых времен, много переделывать.
            LockControl("DlgDown3", false);
			LockControl("DlgUp3", false);
			DialogExit();
			NextDiag.CurrentNode = "First time";  // выход для тюнинга, нужно тут из-за LoadSegment
		break;
		
		case "ship_tunning_not_now_1":  
			LockControl("DlgDown3", false);
			LockControl("DlgUp3", false);
			DialogExit();
			NextDiag.CurrentNode = "First time";  
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "First time":
            if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar, 
					LinkRandPhrase("A városban riadó van, és mindenki téged keres. A helyedben én nem maradnék itt.", "Az összes városôr téged keresve pásztázza a várost. Nem vagyok bolond, és nem állok szóba veled!", "Fuss, "+ GetSexPhrase("pajtás","lány") +", mielôtt a katonák szitává változtatnak..."), 
					LinkRandPhrase("Mit akarsz, "+ GetSexPhrase("gazember","büdös") +"?! A városôrök már a szagodat fogják, nem jutsz messzire, mocskos kalóz!", "gyilkos, azonnal hagyd el a házamat! Ôrség!", "Nem félek tôled, "+ GetSexPhrase("gazember","patkány") +"! Hamarosan felakasztanak az erôdünkben, nem jutsz messzire..."));
				link.l1 = NPCharRepPhrase(pchar,
					RandPhraseSimple("Heh, a riasztó nem jelent számomra problémát...", "Soha nem fognak elkapni."), 
					RandPhraseSimple("Fogd be a szád, " + GetWorkTypeOfMan(npchar, "") + ", vagy kitépem a nyelved!", "Heh, " + GetWorkTypeOfMan(npchar, "") + ", és ott is - kalózokat fogni! Ezt mondom én neked, pajtás: maradj csendben, és nem halsz meg!"));
				link.l1.go = "fight";
				break;
			}
			
//Jason ---------------------------------------Бремя гасконца------------------------------------------------
			if (CheckAttribute(pchar, "questTemp.Sharlie.Lock") && pchar.location == "Fortfrance_shipyard")
			{
				if (CheckAttribute(pchar, "questTemp.Sharlie.Rum") || CheckAttribute(pchar, "questTemp.Sharlie.Gigolo") || CheckAttribute(pchar, "questTemp.Sharlie.RescueDaughter"))
				{
					dialog.text = "Akar valamit, Monsieur?";
					Link.l1 = "Azért jöttem, hogy megnézzem a hajóit... De most egy kicsit elfoglalt vagyok - még mindig van egy befejezetlen ügyem. Majd késôbb bejövök, ha végeztem vele.";
					Link.l1.go = "exit";
					break;
				}
				if (pchar.questTemp.Sharlie == "ship" || pchar.questTemp.Sharlie == "ship_fast") // Addon 2016-1 Jason пиратская линейка 1
				{
					dialog.text = "Akar valamit, Monsieur?";
					Link.l1 = "Nézze, szeretnék egy hajót vásárolni önöktôl.";
					Link.l1.go = "Sharlie";
					break;
				}
				dialog.text = "Szeretne még valamit, uram?";
				Link.l1 = "Nem, azt hiszem, nem.";
				Link.l1.go = "exit";
				NextDiag.TempNode = "First time";
				NPChar.quest.meeting = "1";
				break;
			}
	//<-- Бремя гасконца
			// Addon-2016 Jason, французские миниквесты (ФМК) ФМК-Мартиника
			if (CheckAttribute(pchar, "questTemp.FMQM.Oil") && pchar.location == "Fortfrance_shipyard")
			{
				if (pchar.questTemp.FMQM == "remove_oil")
				{
					dialog.text = "Ez az, kapitány. A munka elvégeztetett. Most jön a kellemes rész - az érmék hangja. Adjon egy percet...";
					link.l1 = "...";
					link.l1.go = "FMQM_oil_1";
					break;
				}
				if (pchar.questTemp.FMQM == "remove_oil1")
				{
					dialog.text = "Várjon, tiszt úr! Kérem, várjon! Ez valami tévedés lehet. Monsieur, a kapitánynak ehhez semmi köze, csak azért kötött ki, hogy megjavíttassa a hajóját. Épp indulni készült. És milyen hordók? Mirôl beszél?";
					link.l1 = "";
					link.l1.go = "FMQM_oil_2";
					break;
				}
				if (pchar.questTemp.FMQM == "remove_oil2")
				{
					dialog.text = "Tiszt úr, megismétlem: a kapitány azért jött ide, hogy kifizesse a hajójavítást. Ezek a hordók az én tulajdonom, és csak termelési célokra szolgálnak. Hajóépítô mester vagyok, és ez a gyanta az általam épített hajókhoz kell.";
					link.l1 = "";
					link.l1.go = "FMQM_oil_3";
					break;
				}
				if (pchar.questTemp.FMQM == "remove_oil3")
				{
					dialog.text = "Ó, kapitány úr! Fogalma sincs, milyen rosszul éreztem magam. Két nap a tömlöcben, patkányok, egerek és nyomorult alakok kíséretében! Minden kapcsolatomat fel kellett használnom, hogy kihúzzam magam onnan. Ah, a friss levegô!";
					link.l1 = "Együttérzek önnel, mester. Mi van a gyantánkkal? És az érméim?";
					link.l1.go = "FMQM_oil_4";
					DelLandQuestMark(npchar);
					break;
				}
			}
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "silk_13" && pchar.location == "PortRoyal_shipyard")
			{
				dialog.text = "Ó, már megint te vagy az! Felismerlek, fiatalember! Te voltál az, aki nemrég kérdezett arról, hogy... növelhetnéd a hajód sebességét selyem vitorlavászonnal, igaz?";
				link.l1 = "A memóriád becsületére válik, mester."; 
				link.l1.go = "mtraxx_x";
				break;
			}
			
			if(NPChar.quest.meeting == "0") // первая встреча
			{
				dialog.Text = GetNatPhrase(npchar, LinkRandPhrase("Ha! Egy igazi öreg só jött szerény mûhelyembe! Új vagy a helyi vizeken, kapitány?","Isten hozta, uram! Ha nem idegen a tenger és van hajója - éppen a legjobb helyre jött!","Üdvözlöm, uram! Szerencséje van - ez a legjobb hajómûhely az egész Brit Újvilágban."), LinkRandPhrase("Monsieur, gondolom, ön egy daliás kapitány, ugye? Ha igen, akkor jól tette, hogy ellátogatott szerény hajógyáramba!","Elôször van itt, Monsieur Kapitány? Jöjjön be és ismerje meg ezt az öreg hajóépítôt.","Legyen szerencsénk megismerni egymást, Monsieur! Egy hajót simogatni kell, akárcsak egy nôt - és mi, franciák, ebben szakértôk vagyunk! Higgye el, nem fogja megbánni, hogy idejött!"), LinkRandPhrase("Még sosem láttam itt, Senor. Örülök, hogy találkoztunk!","Üdvözlöm a tengerek bátor hódítóját! Te tengerész vagy, ugye? Én pedig a helyi hajóépítô vagyok, meg kellene ismernünk egymást.","Helló, Caballero! Örömmel üdvözöllek a mûhelyemben!"),LinkRandPhrase("Jó napot, Mynheer. Még nem találkoztunk, ugye? Van valami dolga velem?","Üdvözlöm, Mynheer kapitány. Ne lepôdj meg, elég sok kapitánnyal találkoztam már, így elsô látásra rájöttem, hogy te is kapitány vagy.","Jöjjön be, Mynheer. Én vagyok a helyi hajóépítô. Örülök, hogy megismerhetem."));
				Link.l1 = LinkRandPhrase("Én is örülök, hogy találkoztunk. A nevem "+GetFullName(pchar)+", és új vagyok ezeken a helyeken. Ezért úgy döntöttem, hogy beugrom.","Csak nem tudtam elmenni mellette - tudod, az a frissen gyalult deszkák illata... Én vagyok "+GetFullName(pchar)+", hajóskapitány '"+pchar.ship.name+"'.","Engedje meg, hogy bemutatkozzam - "+GetFullName(pchar)+", hajóskapitány '"+pchar.ship.name+"', örülök, hogy megismerhetem. Szóval, önök itt hajókat építenek és javítanak, ugye?");
				Link.l1.go = "meeting";
				NPChar.quest.meeting = "1";
				if(startHeroType == 4 && NPChar.location == "SantaCatalina_shipyard")
				{
					dialog.text = "Üdvözlöm, MacArthur kapitány.";
					link.l1 = "Hívjon csak Helénának, Mister "+npchar.lastname+". "+TimeGreeting()+".";
					Link.l1.go = "Helen_meeting";
				}
			}
			else
			{
				dialog.Text = pcharrepphrase(LinkRandPhrase(LinkRandPhrase("Ó! A helyi víz rémsége, kapitány "+GetFullName(pchar)+"! Mit tehetek önért?","Térjünk rögtön a tárgyra, "+GetAddress_Form(NPChar)+", nincs idôm csevegni. Javításra van szüksége, vagy csak a kádját szeretné kicserélni?","Ó, hát nem "+GetFullName(pchar)+"! Mi a helyzet, "+GetAddress_Form(NPChar)+"? Valami baj történt a kádjával?"),LinkRandPhrase("Mire van szüksége, kapitány? Egy perc nyugalom - mindig ez a sok csirkefogó, micsoda átkozott nap...","Helló, "+GetAddress_Form(NPChar)+". Azt kell mondanom, hogy a látogatásod elijesztette az összes vendégemet. Remélem, a rendelésed fedezi a káromat?","Velem üzletel, "+GetAddress_Form(NPChar)+"? Nos, akkor lásson hozzá, és igyekezzen gyorsan."),LinkRandPhrase("Mi szél hozta hozzám, Mister "+GetFullName(pchar)+"? Megértem, hogy a hajójának nehéz dolga lehet, figyelembe véve az életmódját...","Örömmel üdvözlök egy nemest... ó, elnézést, "+GetAddress_Form(NPChar)+", másnak néztem önt. Mit akartál?","Nem igazán kedvelem az ön fajtáját, kapitány úr, de azért nem fogom elkergetni. Mit akartál?")),LinkRandPhrase(LinkRandPhrase("Nagyon örülök, hogy látom, Mister "+GetFullName(pchar)+"! Szóval, hogy megy? Javíttatni kell, vagy gondozásra szorul?","Üdvözlöm, "+GetAddress_Form(NPChar)+"! Kapitány "+GetFullName(pchar)+" mindig szívesen látott vendég a mûhelyemben!","Ó, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"! Ismét meglátogattál! Remélem, a szépséged jól van, ugye?"),LinkRandPhrase(""+GetAddress_Form(NPChar)+", annyira örülök, hogy újra látlak! Hogy van a gyönyörû hajód? Szükséged van segítségre?","Ó, "+GetAddress_Form(NPChar)+", üdvözletem! Hogy vagytok? Esetleg nyikorognak az árbocok, vagy ki kell tisztítani a fenékpadot? A srácaim mindent megtesznek érted!","Jó napot, kapitány "+GetFullName(pchar)+". Örülök, hogy ismét beugrott, és mindig kész vagyok segíteni."),LinkRandPhrase("Örülök, hogy itt van, kapitány úr! Ön egy nagyon kedves ügyfél, "+GetAddress_Form(NPChar)+", és kívánom, hogy maradjon is az.","Ó, "+GetAddress_Form(NPChar)+" "+GetFullName(pchar)+"! Nagyon örülök, hogy itt van! Mit tehetek érted?","Kapitány úr, ismét meglátogatott "+XI_ConvertString("Colony"+npchar.City+"Acc")+"! Higgye el, szívesen segítünk Önnek.")));
				Link.l1 = pcharrepphrase(RandPhraseSimple(RandPhraseSimple("Szerezd meg a hangszereidet, mester, és maradj csendben, rendben? Nem vagyok olyan hangulatban.","Ne fecsegj, haver! A segítségedre van szükségem, nem pedig a fecsegésedre."),RandPhraseSimple("Én fizetek - te pedig dolgozol. Csendben. Világos?","Hé, haver, kergesd el ôket - én vagyok az, a kedvenc ügyfeled!")),RandPhraseSimple(RandPhraseSimple("Én is örülök, hogy látlak, mester. Sajnos, nincs sok idôm, úgyhogy térjünk a tárgyra.","Én is örülök, hogy látlak, pajtás. Akarsz segíteni a kedvenc ügyfelednek?"),RandPhraseSimple("Jó napot, pajtás. Térjünk rögtön az üzletre. Ígérem, legközelebb biztosan leülünk egy üveggel.","Örülök, hogy látlak, mester. Mindig öröm látni téged, de most szükségem van a segítségedre.")));
				Link.l1.go = "Shipyard";
				if (GetNationRelation2MainCharacter(sti(NPChar.nation)) != RELATION_ENEMY) 
				{
					link.l11 = "Ágyúkra van szükségem a hajómhoz.";
					link.l11.go = "Cannons";					
				}	
				
				if(NPChar.city == "PortRoyal" || NPChar.city == "Havana" || NPChar.city == "Villemstad" || NPChar.city == "Charles" || NPChar.city == "PortoBello")
				{
					link.l22 = "Tudsz nekem valami különlegeset ajánlani, olyat, amit más hajógyárban nem találok?";
					link.l22.go = "ship_tunning";
				}
				
				link.l15 = "Nincs olyan munkád, amihez idegenek segítségére lenne szükséged?";
			    link.l15.go = "Tasks";
				// Jason Исла Мона 
				if (CheckAttribute(pchar, "questTemp.IslaMona") && pchar.questTemp.IslaMona == "tools" && !CheckAttribute(npchar, "quest.IslaMonaTools"))
				{
					link.l20 = "Szeretnék egy európai minôségû építô-, kovács- és mérôszerszámkészletet vásárolni. Tudna nekem segíteni?";
					link.l20.go = "IslaMona";
				}
				if (CheckAttribute(npchar, "quest.IslaMonaMoney"))
				{
					link.l20 = "Hoztam dublont egy építôszerszámkészletért.";
					link.l20.go = "IslaMona_7";
				}
				//Jason --> генератор Призонер
				if (CheckAttribute(pchar, "GenQuest.Findship.Shipyarder") && NPChar.location == pchar.GenQuest.Findship.Shipyarder.City + "_shipyard")
				{
					ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
					if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
					{
						for(i = 1; i < COMPANION_MAX; i++)
						{
							int iTemp = GetCompanionIndex(PChar, i);
							if(iTemp > 0)
							{
								sld = GetCharacter(iTemp);
								if(GetRemovable(sld) && sti(RealShips[sti(sld.ship.type)].basetype) == sti(pchar.GenQuest.Findship.Shipyarder.ShipType))
								{
									pchar.GenQuest.Findship.Shipyarder.CompanionIndex = sld.Index;
									pchar.GenQuest.Findship.Shipyarder.OK = 1;
									pchar.GenQuest.Findship.Shipyarder.ShipName = sld.Ship.Name;
									pchar.GenQuest.Findship.Shipyarder.Money = makeint(GetShipSellPrice(sld, CharacterFromID(NPChar.city + "_shipyarder"))*1.5);
								}
							}
						}
					}
					if (sti(pchar.GenQuest.Findship.Shipyarder.OK) == 1)
					{
						link.l16 = "Elküldtem neked "+pchar.GenQuest.Findship.Shipyarder.ShipBaseName+", ahogy kérted.";
						link.l16.go = "Findship_check";
					}// <-- генератор Призонер
				}
				//Jason --> генератор Неудачливый вор
				if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && CheckCharacterItem(pchar, "Tool") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_shipyard")
				{
					link.l17 = "Sikerült megkeresnem a tolvajt és megszerezni a "+pchar.GenQuest.Device.Shipyarder.Type+".";
					link.l17.go = "Device_complete";
				}
				// <-- генератор Неудачливый вор
				if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && RealShips[sti(Pchar.Ship.Type)].BaseType != SHIP_CURSED_FDM) // mitrokosta фикс ломаных диалогов
				{
					link.l12 = "Meg akarom változtatni a vitorláim kinézetét.";
					link.l12.go = "SailsGerald";
				}
				Link.l2 = "Csak beszélgetni akartam.";
				Link.l2.go = "quests"; //(перессылка в файл города)
				// -->
    			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
				{
					link.l3 = "Szeretnék beszélni veled a pénzügyekrôl.";
					link.l3.go = "LoanForAll";
				}
  				if (CheckAttribute(pchar, "GenQuest.Intelligence") && CheckAttribute(pchar, "GenQuest.Intelligence.SpyId") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "") //квест мэра - на связь с нашим шпионом
				{
					link.l7 = RandPhraseSimple("Egy ember kérésére vagyok itt. A neve kormányzó " + GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) + ".", 
						GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) + " küldött önhöz. Azért jöttem, hogy elvigyek valamit...");
					link.l7.go = "IntelligenceForAll";
				}
				//Jason, генер почтового курьера 2 уровня
				if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.LevelUp"))
				{
					if (pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
					{
						link.l14 = "A hajó rajzát a "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen")+"oldalról hoztam.";
						link.l14.go = "Postcureer_LevelUp_ForAll";
					}
				} // patch-6
				if(CheckAttribute(pchar,"GenQuest.EncGirl"))
				{
					if(pchar.GenQuest.EncGirl == "toLoverFather" && pchar.GenQuest.EncGirl.LoverFather == "shipyard_keeper" && pchar.GenQuest.EncGirl.LoverCity == npchar.city)
					{
						link.l7 = "Jó napot, a fia meghívására jöttem."; 
						link.l7.go = "EncGirl_4";
						pchar.quest.EncGirl_GetLoverFather.over = "yes";
					}	
					if(pchar.GenQuest.EncGirl == "toParents" || pchar.GenQuest.EncGirl == "FindLover")
					{
						if(pchar.GenQuest.EncGirl.Father == "shipyard_keeper" && npchar.city == pchar.GenQuest.EncGirl.city)
						{
							link.l8 = "A lányáról van szó...";
							link.l8.go = "EncGirl_1";
						}
					}
				}								
				Link.l9 = "Mennem kell.";
				Link.l9.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "Meeting":
				dialog.Text = "Nagyon örülök, hogy találkozhatok egy új ügyféllel. A hajógyáram a szolgálatára áll.";
				Link.l1 = "Kiváló, " + GetFullName(NPChar) + ". Nézzük meg, mit tudsz nekem ajánlani.";
				Link.l1.go = "Shipyard";
				if (GetNationRelation2MainCharacter(sti(NPChar.nation)) != RELATION_ENEMY) 
				{
					link.l13 = "Ágyúkra van szükségem a hajómhoz.";
					link.l13.go = "Cannons";
				}									
				link.l15 = "Nincs olyan munkád, amihez idegenek segítségére lenne szükséged?";
			    link.l15.go = "Tasks";
				
				if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && RealShips[sti(Pchar.Ship.Type)].BaseType != SHIP_CURSED_FDM) // mitrokosta фикс ломаных диалогов
				{
					link.l12 = "Meg akarom változtatni a vitorláim kinézetét.";
					link.l12.go = "SailsGerald";
				}
				Link.l2 = "Csak beszélgetni akartam.";		
				link.l2.go = "quests";
				// -->
    			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
				{
					link.l3 = "Szeretnék beszélni veled a pénzügyekrôl.";
					link.l3.go = "LoanForAll";//(перессылка в файл города)
				}
  				if (CheckAttribute(pchar, "GenQuest.Intelligence") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "") //квест мэра - на связь с нашим шпионом
				{
					link.l7 = RandPhraseSimple("Egy ember kérésére vagyok itt. A neve kormányzó " + GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) + ".", 
						GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) + " küldött önhöz. Azért jöttem, hogy elvigyek valamit...");
					link.l7.go = "IntelligenceForAll";
				}
				//Jason, генер почтового курьера 2 уровня
				if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.LevelUp"))
				{
					if (pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
					{
						link.l14 = "A hajó rajzát a "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen")+"városból szállítottam.";
						link.l14.go = "Postcureer_LevelUp_ForAll";
					}
				}

				if(CheckAttribute(pchar,"GenQuest.EncGirl"))
				{
					if(pchar.GenQuest.EncGirl == "toLoverFather" && pchar.GenQuest.EncGirl.LoverFather == "shipyard_keeper" && pchar.GenQuest.EncGirl.LoverCity == npchar.city)
					{
						link.l8 = "Jó napot, a fia meghívására jöttem."; 
						link.l8.go = "EncGirl_4";
						pchar.quest.EncGirl_GetLoverFather.over = "yes";
					}	
					if(pchar.GenQuest.EncGirl == "toParents" || pchar.GenQuest.EncGirl == "FindLover")
					{
						if(pchar.GenQuest.EncGirl.Father == "shipyard_keeper" && npchar.city == pchar.GenQuest.EncGirl.city)
						{
							link.l9 = "A lányáról van szó...";
							link.l9.go = "EncGirl_1";
						}
					}
				}
				if (CheckCharacterItem(pchar, "CaptainBook") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakShipyard"))
				{
					if(CheckAttribute(pchar, "questTemp.different.GiveShipLetters") && (pchar.questTemp.different.GiveShipLetters.city == npchar.city))
					{
						link.l10 = "Mit tud nekem mondani a dokumentumok tulajdonosáról?";
						link.l10.go = "ShipLetters_6";// генератор  "Найденные документы"
					}		
				}	
				Link.l11 = "Most mennem kell, köszönöm.";
				Link.l11.go = "exit";
				NextDiag.TempNode = "First time";
		break;
		
		case "Helen_Meeting":
				dialog.Text = "Természetesen, MacArthur kapitány, ahogy kívánja. Mire van szüksége ma?";
				Link.l1 = "Kiváló, " + GetFullName(NPChar) + ". Nézzük meg, mit tudsz nekem ajánlani.";
				Link.l1.go = "Shipyard";
				if (GetNationRelation2MainCharacter(sti(NPChar.nation)) != RELATION_ENEMY) 
				{
					link.l13 = "Ágyúkra van szükségem a hajómhoz.";
					link.l13.go = "Cannons";
				}									
				link.l15 = "Nincs olyan munkád, amihez idegenek segítségére lenne szükséged?";
			    link.l15.go = "Tasks";
				
				if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && RealShips[sti(Pchar.Ship.Type)].BaseType != SHIP_CURSED_FDM) // mitrokosta фикс ломаных диалогов
				{
					link.l12 = "Meg akarom változtatni a vitorláim kinézetét.";
					link.l12.go = "SailsGerald";
				}
				Link.l2 = "Csak beszélgetni akartam.";		
				link.l2.go = "quests";
				// -->
    			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
				{
					link.l3 = "Szeretnék beszélni veled a pénzügyekrôl.";
					link.l3.go = "LoanForAll";//(перессылка в файл города)
				}
  				if (CheckAttribute(pchar, "GenQuest.Intelligence") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "") //квест мэра - на связь с нашим шпионом
				{
					link.l7 = RandPhraseSimple("Egy ember kérésére vagyok itt. A neve kormányzó " + GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) + ".", 
						GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) + " küldött önhöz. Azért jöttem, hogy elvigyek valamit...");
					link.l7.go = "IntelligenceForAll";
				}
				//Jason, генер почтового курьера 2 уровня
				if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.LevelUp"))
				{
					if (pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
					{
						link.l14 = "A hajó rajzát a "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen")+"városból szállítottam.";
						link.l14.go = "Postcureer_LevelUp_ForAll";
					}
				}

				if(CheckAttribute(pchar,"GenQuest.EncGirl"))
				{
					if(pchar.GenQuest.EncGirl == "toLoverFather" && pchar.GenQuest.EncGirl.LoverFather == "shipyard_keeper" && pchar.GenQuest.EncGirl.LoverCity == npchar.city)
					{
						link.l8 = "Jó napot, a fia meghívására jöttem."; 
						link.l8.go = "EncGirl_4";
						pchar.quest.EncGirl_GetLoverFather.over = "yes";
					}	
					if(pchar.GenQuest.EncGirl == "toParents" || pchar.GenQuest.EncGirl == "FindLover")
					{
						if(pchar.GenQuest.EncGirl.Father == "shipyard_keeper" && npchar.city == pchar.GenQuest.EncGirl.city)
						{
							link.l9 = "A lányáról van szó...";
							link.l9.go = "EncGirl_1";
						}
					}
				}
				if (CheckCharacterItem(pchar, "CaptainBook") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakShipyard"))
				{
					if(CheckAttribute(pchar, "questTemp.different.GiveShipLetters") && (pchar.questTemp.different.GiveShipLetters.city == npchar.city))
					{
						link.l10 = "Mit tud nekem mondani a dokumentumok tulajdonosáról?";
						link.l10.go = "ShipLetters_6";// генератор  "Найденные документы"
					}		
				}	
				Link.l11 = "Most mennem kell, köszönöm.";
				Link.l11.go = "exit";
				NextDiag.TempNode = "First time";
		break;

		case "ship_tunning":
			dialog.text = "A hajógyárunk híres a hajók fejlesztésérôl. Érdekli a dolog, kapitány?";
			Link.l1 = LinkRandPhrase("Kiváló! Talán megnézhetnéd a hajómat, és elmondhatnád, hogyan lehetne javítani rajta?",
			          "Ez nagyon érdekes, mester! És mit tudsz tenni a hajómért?",
					  "Hmm... Tudod, megszoktam a hajómat, de ha valami igazán érdekeset ajánlasz, akkor elgondolkodom rajta. Mit szólsz hozzá?");
			Link.l1.go = "ship_tunning_start";
		break;
				
		case "ship_tunning_start" :		
			ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
			if (sti(Pchar.Ship.Type) == SHIP_NOTUSED || ok)
			{				
				if (sti(RealShips[sti(pchar.Ship.Type)].Class) >= 7)
				{
					dialog.Text = "Errr... Én nem foglalkozom hajókkal. Egy régi kád attól még egy régi kád marad, akármennyi erôfeszítést is teszel bele.";
					Link.l1 = "Értem...";
					Link.l1.go = "ship_tunning_not_now_1";
					break;
				}
				// belamour legendary edition -->
				if(!TuningAvailable())
				{
					dialog.Text = "Szóval... lássuk, mi van itt... Igen - " + XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName) + ". A hajód már most is rendelkezik a maximálisan javított jellemzôkkel, attól tartok, hogy további munkának nincs értelme és csak árthat.";
					Link.l1 = "Értem...";
					Link.l1.go = "ship_tunning_not_now_1";
					break;
				}
				// <-- legendary edition							
				if(GetHullPercent(pchar) < 100 || GetSailPercent(pchar) < 100)
				{
					dialog.Text = "Mielôtt javítanál egy hajót, teljesen meg kell javítani. Ezt is meg lehet tenni itt a hajógyáramban.";
					Link.l1 = "Megértettem...";
					Link.l1.go = "ship_tunning_not_now_1";
					break;
				}
				
				s2 = "Rendben, lássuk, mi van itt... Aha " + XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName) + ".";
				// belamour legendary edition -->
				if(NPChar.city == "PortRoyal")
				{
					s2 = s2 + " A mi hajógyárunk híres a hajó teljesítményének javításáról, növelni tudjuk akár a maximális sebességet, akár a széllel szembeni szöget.";
				}
				if(NPChar.city == "Havana" || NPChar.city == "PortoBello")
				{
					s2 = s2 + " A mi hajógyárunkban növelhetjük az ágyúk maximális számát vagy a hajó teherbírását.";
				}
				if(NPChar.city == "Villemstad")
				{
					s2 = s2 + " Az én embereim meg tudják erôsíteni a hajótestet, vagy növelni a legénység maximális létszámát.";
				}
				if(NPChar.city == "Charles")
				{
					s2 = s2 + " Ennél a hajógyárnál javíthatjuk a manôverezôképességet vagy csökkenthetjük a legénységben lévô matrózok minimális számát.";
				}	
				
				dialog.Text = s2;
				
				if(NPChar.city == "PortRoyal")
				{
					// belamour legendary edition -->
					ok = (!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.SpeedRate")) && 
						 (!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.WindAgainst"));
					if(ok)
					{
						Link.l1 = "Növelje a sebességet.";
						Link.l1.go = "ship_tunning_SpeedRate";
						Link.l2 = "Növelni a széllel szembeni szöget.";
						Link.l2.go = "ship_tunning_WindAgainst";
						Link.l3 = "Kapaszkodj! Meggondoltam magam.";
						Link.l3.go = "ship_tunning_not_now_1";
						break;
					}	
					else
					{
						if(!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.SpeedRate"))
						{
							Link.l1 = "Növelje a sebességet.";
							Link.l1.go = "ship_tunning_SpeedRate";
							Link.l2 = "Kapaszkodj! Meggondoltam magam.";
							Link.l2.go = "ship_tunning_not_now_1";
							break;
						}
						if(!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.WindAgainst"))
						{
							Link.l1 = "Növelni a széllel szembeni szöget.";
							Link.l1.go = "ship_tunning_WindAgainst";
							Link.l2 = "Kapaszkodj! Meggondoltam magam.";
							Link.l2.go = "ship_tunning_not_now_1";	
							break;
						}
						Link.l1 = LinkRandPhrase("Ó! Az én hajóm már így is javult. Nos, köszönöm, hogy idôt szakított rám!",
						                         "Köszönöm, mester, de már van egy fejlesztésem, és pontosan az, amit említettél nekem. Sok sikert a többi hajóhoz és kapitányukhoz!",
												 "Heh! Gondolom, a hajómat már korábban is átépítette egy elôzô tulajdonos - bizonyára éppen ebben a hajógyárban, Nos, azt hiszem, meg kell köszönnöm neki az elôrelátását, neked és a srácoknak pedig a kiváló munkát!");
						Link.l1.go = "ship_tunning_not_now_1";					
					}
						// <-- legendary edition
				}
				if(NPChar.city == "Havana" || NPChar.city == "PortoBello")
				{
					ok = (!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.Cannon")) && 
						 (!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.Capacity"));
					if(ok)
					{	
						if(GetPossibilityCannonsUpgrade(pchar, true) > 0)
						{	
							Link.l1 = "Növelje az ágyúk maximális számát.";
							Link.l1.go = "ship_c_quantity";
						}	
							Link.l2 = "Növelje a saját súlyt.";
							Link.l2.go = "ship_tunning_Capacity";
						Link.l3 = "Várjatok! Meggondoltam magam.";
						Link.l3.go = "ship_tunning_not_now_1";
						break;
					}
					else
					{
						if(!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.Cannon"))
						{
							if(GetPossibilityCannonsUpgrade(pchar, true) > 0)
							{	
								Link.l1 = "Növelje az ágyúk maximális számát.";
								Link.l1.go = "ship_c_quantity";
								Link.l2 = "Várjatok! Meggondoltam magam.";
								Link.l2.go = "ship_tunning_not_now_1";	
								break;
							}	
						}
						if(!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.Capacity"))
						{
							Link.l1 = "Növelje a saját súlyt.";
							Link.l1.go = "ship_tunning_Capacity";
							Link.l2 = "Várjatok! Meggondoltam magam.";
							Link.l2.go = "ship_tunning_not_now_1";	
							break;
						}
						Link.l1 = LinkRandPhrase("Ó! Az én hajóm már így is javult. Nos, köszönöm, hogy idôt szakított rám!",
												 "Köszönöm, mester, de már van egy fejlesztésem, és pontosan az, amit említettél nekem. Sok sikert a többi hajóhoz és kapitányukhoz!",
												 "Heh! Gondolom, a hajómat már korábban is átépítette egy elôzô tulajdonos - bizonyára éppen ebben a hajógyárban, Nos, azt hiszem, meg kell köszönnöm neki az elôrelátását, neked és a srácoknak pedig a kiváló munkát!");
						Link.l1.go = "ship_tunning_not_now_1";	
					// <-- legendary edition
					}						
				}
				if(NPChar.city == "Villemstad")
				{
					ok = (!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.HP")) && 
						 (!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.MaxCrew"));
					if(ok)
					{
						Link.l1 = "Növelje a hajótest tartósságát.";
						Link.l1.go = "ship_tunning_HP";
						Link.l2 = "Növelje a legénység helyét.";
						Link.l2.go = "ship_tunning_MaxCrew";
						Link.l3 = "Várjatok! Meggondoltam magam.";
						Link.l3.go = "ship_tunning_not_now_1";
						break;
					}	
					else
					{
						// belamour legendary edition -->
						if(!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.HP"))
						{
							Link.l1 = "Növelje a hajótest tartósságát.";
							Link.l1.go = "ship_tunning_HP";
							Link.l2 = "Várjatok! Meggondoltam magam.";
							Link.l2.go = "ship_tunning_not_now_1";
							break;
						}
						if(!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.MaxCrew"))
						{
							Link.l1 = "Növelje a legénység helyét.";
							Link.l1.go = "ship_tunning_MaxCrew";
							Link.l2 = "Várjatok! Meggondoltam magam.";
							Link.l2.go = "ship_tunning_not_now_1";
							break;	
						}
						Link.l1 = LinkRandPhrase("Ó! Az én hajóm már így is javult. Nos, köszönöm, hogy idôt szakított rám!",
						                         "Köszönöm, mester, de már van egy fejlesztésem, és pontosan az, amit említettél nekem. Sok sikert a többi hajóhoz és kapitányukhoz!",
												 "Heh! Gondolom, a hajómat már korábban is átépítette egy elôzô tulajdonos - bizonyára éppen ebben a hajógyárban, Nos, azt hiszem, meg kell köszönnöm neki az elôrelátását, neked és a srácoknak pedig a kiváló munkát!");
						Link.l1.go = "ship_tunning_not_now_1";	
						// <-- legendary edition
					}
				}
				if(NPChar.city == "Charles")
				{
					ok = (!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.TurnRate")) && 
						 (!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.MinCrew"));
					if(ok)
					{		
						Link.l1 = "Növelje a kormányozhatóságot.";
						Link.l1.go = "ship_tunning_TurnRate";
						if(sti(RealShips[sti(pchar.Ship.Type)].Class) < 5)
						{
							Link.l2 = "Csökkentse a legénység minimális méretét.";
							Link.l2.go = "ship_tunning_MinCrew";
						}	
						Link.l3 = "Várjatok! Meggondoltam magam.";
						Link.l3.go = "ship_tunning_not_now_1";
						break;
					}
					else
					{
						// belamour legendary edition -->
						if(!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.TurnRate"))
						{
							Link.l1 = "Növelje a kormányozhatóságot.";
							Link.l1.go = "ship_tunning_TurnRate";
							Link.l2 = "Várjatok! Meggondoltam magam.";
							Link.l2.go = "ship_tunning_not_now_1";
							break;
						}
						if(!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.MinCrew"))
						{
							if(sti(RealShips[sti(pchar.Ship.Type)].Class) < 5)
							{
								Link.l1 = "Csökkentse a legénység minimális méretét.";
								Link.l1.go = "ship_tunning_MinCrew";
								Link.l2 = "Várjatok! Meggondoltam magam.";
								Link.l2.go = "ship_tunning_not_now_1";
								break;
							}	
						}
						// <-- legendary edition				
					}
					Link.l1 = LinkRandPhrase("Ó! Az én hajóm már így is javult. Nos, köszönöm, hogy idôt szakított rám!",
						                         "Köszönöm, mester, de már van egy fejlesztésem, és pontosan az, amit említettél nekem. Sok sikert a többi hajóhoz és kapitányukhoz!",
												 "Heh! Gondolom, a hajómat már korábban is átépítette egy elôzô tulajdonos - bizonyára éppen ebben a hajógyárban, Nos, azt hiszem, meg kell köszönnöm neki az elôrelátását, neked és a srácoknak pedig a kiváló munkát!");
					Link.l1.go = "ship_tunning_not_now_1";	
				}								
			}
			else
			{
				dialog.Text = "Hol van a hajó? Most szórakozol velem, vagy mi?";
			    Link.l1 = "Ó, az én hibám, valóban... Sajnálom.";
			    Link.l1.go = "ship_tunning_not_now_1";
			}			
		break;
		
		////////////////////////////////////////// Capacity ////////////////////////////////////////////////////
		case "ship_tunning_Capacity":
			Material 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 );
			WorkPrice 	= GetMaterialQtyUpgrade(pchar, NPChar, 2 );			
			s2 = "Nos, lássuk mit tudunk csinálni. Jelenleg a hajótok önsúlya... " + sti(RealShips[sti(pchar.Ship.Type)].Capacity);			
			s2 = s2 + ". A könnyebb válaszfalakhoz szükségem lesz: vasfa - " + Material + ".";
			s2 = s2 + " A munkámért fizetségként elfogadom: " + WorkPrice + " láda dublonokat - a költségeim fedezésére. Ez minden. Ó, és készpénz elôre.";			
            dialog.Text = s2;
			Link.l1 = "Egyetértek. Elfogadom a feltételeidet. Elhozom, amire csak szüksége van.";
			Link.l1.go = "ship_tunning_Capacity_start";
			Link.l2 = "Nem. Ez nem tetszik nekem.";
			Link.l2.go = "ship_tunning_not_now_1";
		break;
		
		case "ship_tunning_Capacity_start":
		    amount = GetMaterialQtyUpgrade(pchar, NPChar, 2 );
			// belamour legendary edition туда сюда бегать - та ещё морока -->
			if(GetCharacterItem(pchar,"chest") + CheckItemMyCabin("chest") >= amount)		    
			{
				if(GetCharacterItem(pchar,"chest") >= amount)
				{				
					TakeNItems(pchar,"chest", -amount);
				}
				else
				{
					iSumm = amount - sti(GetCharacterItem(pchar,"chest"));
					TakeNItems(pchar,"chest", -sti(GetCharacterItem(pchar,"chest")));
					GetItemMyCabin("chest", iSumm);
					Log_Info("A kabinból ládányi dublont vittek el: " + iSumm+ " db.");
				}
				// <-- legendary edtion
			    NPChar.Tuning.Money  		= amount;
			    NPChar.Tuning.Matherial 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 );			    
			    NPChar.Tuning.ShipType      = Pchar.Ship.Type;
			    NPChar.Tuning.ShipName      = RealShips[sti(Pchar.Ship.Type)].BaseName;			    
				NextDiag.TempNode = "ship_tunning_Capacity_again";
                dialog.text = "Remek. Várom az anyagot.";
			    link.l1 = LinkRandPhrase("Biztosíthatom, hogy nem kell sokáig várnia. Meg tudom oldani az ilyen problémákat, rendben?",
										 "Tekintse úgy, hogy már megvan, és tartsa meg nekem a dokkolót. Olyan gyors leszek, mint a szél.",
										 "Természetesen. Csak meg kell látogatnom néhány személyt, akiknek megvan a kért cucc, ha-ha!");
			    link.l1.go = "Exit";			    
			    ReOpenQuestHeader("ShipTuning");
			    AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "A munkájához, hogy növelje a tonnatartalmat " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName + "Voc")) + " '" + pchar.ship.name + "'"+
				" hajósnak szüksége van: vasfára - " + NPChar.Tuning.Matherial + ". Elôre letétet fizettek " + NPChar.Tuning.Money + " láda dublont.");
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_not_now_1";
                dialog.text = "Nem látom a letétet...";
				link.l1 = "Majd késôbb benézek.";
				link.l1.go = "Exit";								
			}
		break;
				
		case "ship_tunning_Capacity_again":
		    if (sti(NPChar.Tuning.ShipType) == sti(Pchar.Ship.Type) && NPChar.Tuning.ShipName == RealShips[sti(Pchar.Ship.Type)].BaseName && TuningAvailable())
		    {
                NextDiag.TempNode = "ship_tunning_Capacity_again";
				dialog.Text = "Az idô telik, és a hajó már vár. Mindent elhoztál, amit kértem?";
			    Link.l1 = "Igen, sikerült találnom valamit.";
			    Link.l1.go = "ship_tunning_Capacity_again_2";
			    Link.l2 = "Nem, még mindig rajta vagyok.";
			    Link.l2.go = "Exit";
			}
			else
			{
			    DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
			    dialog.Text = "Mis"+ GetSexPhrase("ter","s") +", megváltoztatta a hajóját, mióta megállapodtunk? Nem kellett volna.";
			    Link.l1 = "Sajnos, a körülmények miatt! Kár, hogy a letét elveszett...";
			    Link.l1.go = "Exit";
				DeleteAttribute(pchar,"achievment.Tuning");
			    AddQuestRecord("ShipTuning", "Lose");
			    CloseQuestHeader("ShipTuning");
			}
		break;
		
		case "ship_tunning_Capacity_again_2":
		    checkMatherial(Pchar, NPChar, GOOD_SANDAL);		
		    if(sti(NPChar.Tuning.Matherial) < 1)
			{
				DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
                dialog.text = "Kiváló, most már mindenem megvan, amire szükségem van. Akkor elkezdek dolgozni.";
			    link.l1 = "Várok.";
			    link.l1.go = "ship_tunning_Capacity_complite";
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_Capacity_again";
				dialog.Text = "Még mindig szükségem van: vasfa - " + sti(NPChar.Tuning.Matherial) + ".";
				link.l1 = "Rendben.";
				link.l1.go = "Exit";
                AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "Hoznom kell: vasfa - "+ sti(NPChar.Tuning.Matherial) + ".");
			}
		break;
		
		case "ship_tunning_Capacity_complite":
		    AddTimeToCurrent(6, 30);
		    shTo = &RealShips[sti(Pchar.Ship.Type)];
		    DeleteAttribute(NPChar, "Tuning");
		    // изменим
			if(!CheckAttribute(shTo, "Bonus_Capacity"))
			{
				if(sti(shTo.Spec) == SHIP_SPEC_UNIVERSAL)
				{
					shTo.Capacity        = sti(shTo.Capacity) + makeint(sti(shTo.Capacity)* 0.35);
				}
				else
				{
					shTo.Capacity        = sti(shTo.Capacity) + makeint(sti(shTo.Capacity)/5);
				}
			}
			else
			{
				
				if(sti(shTo.Spec) == SHIP_SPEC_UNIVERSAL)
				{
					shTo.Capacity        = makeint((sti(shTo.Capacity) - sti(shTo.Bonus_Capacity)) * 1.35 + sti(shTo.Bonus_Capacity));
				}
				else
				{
					shTo.Capacity        = makeint((sti(shTo.Capacity) - sti(shTo.Bonus_Capacity)) * 1.2 + sti(shTo.Bonus_Capacity));
				}
			}
	        shTo.Tuning.Capacity = true;

	        // finish <--
            NextDiag.TempNode = "First time";
			dialog.Text = "...Úgy tûnik, ez minden... Most már teljesen feltöltheted a rakományodat, garantálom a munkám minôségét.";
			Link.l1 = "Köszönöm! Majd én tesztelem.";
			Link.l1.go = "Exit";
			if(!CheckAttribute(pchar, "achievment.Tuning.stage2") && CheckAttribute(shTo,"Tuning.Cannon") && CheckAttribute(shTo,"Tuning.Capacity")) 
			
			{
				pchar.achievment.Tuning.stage2 = true;
			}	
			TuningAvailable();
			AddQuestRecord("ShipTuning", "End");
			CloseQuestHeader("ShipTuning");
			
			notification("Sokat tanultál a hajó szerkezetérôl!", "none");
			AddCharacterExpToSkill(pchar, SKILL_COMMERCE, 5.0 * makefloat(GetMaterialQtyUpgrade(pchar, NPChar, 2 )));
		break;
		
		////////////////////////////////////////// SpeedRate ////////////////////////////////////////////////////
		case "ship_tunning_SpeedRate":
			Material 	= GetMaterialQtyUpgrade(pchar, NPChar,  1 );			
			WorkPrice 	= GetMaterialQtyUpgrade(pchar, NPChar,  2 );
			s2 = "Akkor lássuk, mit tudunk csinálni. Jelenleg a hajótok sebessége " + stf(RealShips[sti(Pchar.Ship.Type)].SpeedRate);	
			s2 = s2 + " csomók. A vitorlák cseréjéhez szükségem lesz: vitorlaselyem - "+ Material + ".";
			s2 = s2 + " A munkámért fizetségként elfogadom: " + WorkPrice + " láda dublonokat - a költségeim fedezésére. Ez minden. Ó, és készpénz elôre.";						
            dialog.Text = s2;
			Link.l1 = "Egyetértek. Elfogadom a feltételeidet. Elhozom, amire csak szüksége van.";
			Link.l1.go = "ship_tunning_SpeedRate_start";
			Link.l2 = "Nem. Ez nem tetszik nekem.";
			Link.l2.go = "ship_tunning_not_now_1";
		break;
			
		case "ship_tunning_SpeedRate_start":
			amount = GetMaterialQtyUpgrade(pchar, NPChar, 2 );
			// belamour legendary edition туда сюда бегать - та ещё морока -->
			if(GetCharacterItem(pchar,"chest") + CheckItemMyCabin("chest") >= amount)		    
			{
				if(GetCharacterItem(pchar,"chest") >= amount)
				{				
					TakeNItems(pchar,"chest", -amount);
				}
				else
				{
					iSumm = amount - sti(GetCharacterItem(pchar,"chest"));
					TakeNItems(pchar,"chest", -sti(GetCharacterItem(pchar,"chest")));
					GetItemMyCabin("chest", iSumm);
					Log_Info("A kabinból ládányi dublont vittek el: " + iSumm+ " db.");
				}
				// <-- legendary edtion	
			    NPChar.Tuning.Money  		= amount;
			    NPChar.Tuning.Matherial 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 ); 			    
			    NPChar.Tuning.ShipType   	= Pchar.Ship.Type;
			    NPChar.Tuning.ShipName   	= RealShips[sti(Pchar.Ship.Type)].BaseName;
				NextDiag.TempNode = "ship_tunning_SpeedRate_again";
                dialog.text = "Remek. Várom az anyagot.";
				link.l1 = LinkRandPhrase("Biztosíthatom, hogy nem kell sokáig várnia. Meg tudom oldani az ilyen problémákat, rendben?",
										 "Tekintse úgy, hogy már megvan, és tartsa meg nekem a dokkolót. Olyan gyors leszek, mint a szél.",
										 "Természetesen. Csak meg kell látogatnom néhány személyt, akiknek megvan a kért cucc, ha-ha!");
			    link.l1.go = "Exit";
			    ReOpenQuestHeader("ShipTuning");
			    AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "Munkájához a sebesség növeléséhez a " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName + "Voc")) + " '" + pchar.ship.name + "'" +
				" hajósnak szüksége van: hajóselyem - " + NPChar.Tuning.Matherial + ". Mivel a letétet a " + NPChar.Tuning.Money + " ládák dublonokért fizették ki.");
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_not_now_1";
                dialog.text = "Nem látom a letétet...";
				link.l1 = "Majd késôbb benézek.";
				link.l1.go = "Exit";								
			}
		break;
		
		case "ship_tunning_SpeedRate_again":
		    if (sti(NPChar.Tuning.ShipType) == sti(Pchar.Ship.Type) && NPChar.Tuning.ShipName == RealShips[sti(Pchar.Ship.Type)].BaseName && TuningAvailable())
		    {
                NextDiag.TempNode = "ship_tunning_SpeedRate_again";
				dialog.Text = "Az idô telik, és a hajó már vár. Mindent elhoztál, amit kértem?";
			    Link.l1 = "Igen, sikerült találnom valamit.";
			    Link.l1.go = "ship_tunning_SpeedRate_again_2";
			    Link.l2 = "Nem, még mindig rajta vagyok.";
			    Link.l2.go = "Exit";
			}
			else
			{
			    DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
				dialog.Text = "Mis"+ GetSexPhrase("ter","s") +", megváltoztatta a hajóját, mióta megállapodtunk? Nem kellett volna.";
			    Link.l1 = "Sajnos, a körülmények miatt! Kár, hogy a letét elveszett...";
			    Link.l1.go = "Exit";			    
				DeleteAttribute(pchar,"achievment.Tuning");	
			    AddQuestRecord("ShipTuning", "Lose");
			    CloseQuestHeader("ShipTuning");
			}
		break;
		
		case "ship_tunning_SpeedRate_again_2":
		    checkMatherial(Pchar, NPChar, GOOD_SHIPSILK);		    
		    if(sti(NPChar.Tuning.Matherial) < 1)
			{
				DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
                dialog.text = "Kiváló, most már mindenem megvan, amire szükségem van. Akkor elkezdek dolgozni.";
			    link.l1 = "Várok.";
			    link.l1.go = "ship_tunning_SpeedRate_complite";
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_SpeedRate_again";
				dialog.Text = "Még mindig szükségem van: hajóselyem - "+ sti(NPChar.Tuning.Matherial) + ".";
				link.l1 = "Rendben.";
				link.l1.go = "Exit";
                AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText",  "Hoznom kell: hajóselyem - "+ sti(NPChar.Tuning.Matherial) + ".");
			}
		break;
		
		case "ship_tunning_SpeedRate_complite":
		    AddTimeToCurrent(6, 30);
		    shTo = &RealShips[sti(Pchar.Ship.Type)];
		    DeleteAttribute(NPChar, "Tuning");
		    // изменим
			if(!CheckAttribute(shTo, "Bonus_SpeedRate"))
			{
				if(sti(shTo.Spec) == SHIP_SPEC_UNIVERSAL)
				{
					shTo.SpeedRate        = (stf(shTo.SpeedRate) + stf(shTo.SpeedRate) * 0.35);
				}
				else
				{
					shTo.SpeedRate        = (stf(shTo.SpeedRate) + stf(shTo.SpeedRate)/5.0);
				}
			}
			else
			{
				if(sti(shTo.Spec) == SHIP_SPEC_UNIVERSAL)
				{
					shTo.SpeedRate        = (stf(shTo.SpeedRate) - stf(shTo.Bonus_SpeedRate)) * 1.3 + stf(shTo.Bonus_SpeedRate);
				}
				else
				{
					shTo.SpeedRate        = (stf(shTo.SpeedRate) - stf(shTo.Bonus_SpeedRate)) * 1.2 + stf(shTo.Bonus_SpeedRate);
				}
			}
	        shTo.Tuning.SpeedRate = true;
			
			if(!CheckAttribute(pchar, "achievment.Tuning.stage1") && CheckAttribute(shTo, "Bonus_SpeedRate") &&  CheckAttribute(shTo,"Tuning.WindAgainst")) 
			{
				pchar.achievment.Tuning.stage1 = true;
			}	
            TuningAvailable();
            NextDiag.TempNode = "First time";
			dialog.Text = "... Minden készen áll, kapitány. Teljes vitorlázással fogd a szelet. Nézzétek meg, ha van kedvetek!";
			Link.l1 = "Köszönöm! Majd én tesztelem.";
			Link.l1.go = "Exit";			
			AddQuestRecord("ShipTuning", "End");
			CloseQuestHeader("ShipTuning");
			notification("Sokat tanultál a hajó szerkezetérôl!", "none");
			AddCharacterExpToSkill(pchar, SKILL_SAILING, 5.0 * makefloat(GetMaterialQtyUpgrade(pchar, NPChar, 2 )));
		break;
		
		////////////////////////////////////////// TurnRate ////////////////////////////////////////////////////
		case "ship_tunning_TurnRate":
			Material  = GetMaterialQtyUpgrade(pchar, NPChar, 1 );			
			WorkPrice = GetMaterialQtyUpgrade(pchar, NPChar, 2 );
			s2 = "Akkor lássuk, mit tehetünk. Jelenleg a hajótok irányíthatósága... " + stf(RealShips[sti(Pchar.Ship.Type)].TurnRate);			
			s2 = s2 + " Ahhoz, hogy új vitorlákat adjak hozzá, hogy felrázzam, szükségem lesz: kötelekre - "+ Material + ".";
			s2 = s2 + " A munkámért fizetségként elfogadom: " + WorkPrice + " láda dublonokat - a költségeim fedezésére. Ez minden. Ó, és készpénz elôre.";										
            dialog.Text = s2;
			Link.l1 = "Egyetértek. Elfogadom a feltételeidet. Elhozom, amire csak szüksége van.";
			Link.l1.go = "ship_tunning_TurnRate_start";
			Link.l2 = "Nem. Ez nem tetszik nekem.";
			Link.l2.go = "ship_tunning_not_now_1";
		break;
		
		case "ship_tunning_TurnRate_start":
			amount = GetMaterialQtyUpgrade(pchar, NPChar, 2 );
			// belamour legendary edition туда сюда бегать - та ещё морока
			if(GetCharacterItem(pchar,"chest") + CheckItemMyCabin("chest") >= amount)		    
			{
				if(GetCharacterItem(pchar,"chest") >= amount)
				{				
					TakeNItems(pchar,"chest", -amount);
				}
				else
				{
					iSumm = amount - sti(GetCharacterItem(pchar,"chest"));
					TakeNItems(pchar,"chest", -sti(GetCharacterItem(pchar,"chest")));
					GetItemMyCabin("chest", iSumm);
					Log_Info("A kabinból ládányi dublont vittek el: " + iSumm+ " db.");
				}
				// <-- legendary edtion	
			    NPChar.Tuning.Money  		= amount;
				NPChar.Tuning.Matherial 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 ); 			    
			    NPChar.Tuning.ShipType      = Pchar.Ship.Type;
			    NPChar.Tuning.ShipName      = RealShips[sti(Pchar.Ship.Type)].BaseName;
				NextDiag.TempNode = "ship_tunning_TurnRate_again";
                dialog.text = "Remek. Várom az anyagot.";
				link.l1 = LinkRandPhrase("Biztosíthatom, hogy nem kell sokáig várnia. Meg tudom oldani az ilyen problémákat, rendben?",
										 "Tekintse úgy, hogy már megvan, és tartsa meg nekem a dokkolót. Olyan gyors leszek, mint a szél.",
										 "Természetesen. Csak meg kell látogatnom néhány személyt, akiknek megvan a kért cucc, ha-ha!");			    
			    link.l1.go = "Exit";			    
			    ReOpenQuestHeader("ShipTuning");
			    AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "A munkájához, hogy növelje a mozgékonyságot a " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName + "Voc")) + " '" + pchar.ship.name + "'" +
				" hajósnak szüksége van: kötelek - " + NPChar.Tuning.Matherial + ". Elôre letétet fizettek  " + NPChar.Tuning.Money + " láda dublont.");
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_not_now_1";
                dialog.text = "Nem látom a letétet...";
				link.l1 = "Majd késôbb benézek.";
				link.l1.go = "Exit";								
			}
		break;
		
		case "ship_tunning_TurnRate_again":
		    if (sti(NPChar.Tuning.ShipType) == sti(Pchar.Ship.Type) && NPChar.Tuning.ShipName == RealShips[sti(Pchar.Ship.Type)].BaseName && TuningAvailable())
		    {
                NextDiag.TempNode = "ship_tunning_TurnRate_again";
				dialog.Text = "Az idô telik, és a hajó már vár. Mindent elhoztál, amit kértem?";
			    Link.l1 = "Igen, sikerült szállítanom valamit.";
			    Link.l1.go = "ship_tunning_TurnRate_again_2";
			    Link.l2 = "Nem, még mindig rajta vagyok.";
			    Link.l2.go = "Exit";
			}
			else
			{
			    DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
				dialog.Text = "Mis"+ GetSexPhrase("ter","s") +", megváltoztatta a hajóját, mióta megállapodtunk? Nem kellett volna.";
			    Link.l1 = "Sajnos, a körülmények miatt! Kár, hogy a letét elveszett...";
			    Link.l1.go = "Exit";			    
				DeleteAttribute(pchar,"achievment.Tuning");	
			    AddQuestRecord("ShipTuning", "Lose");
			    CloseQuestHeader("ShipTuning");
			}
		break;
		
		case "ship_tunning_TurnRate_again_2":
		    checkMatherial(Pchar, NPChar, GOOD_ROPES);		
		    if(sti(NPChar.Tuning.Matherial) < 1)
			{
				DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
                dialog.text = "Kiváló, most már mindenem megvan, amire szükségem van. Akkor elkezdek dolgozni.";
			    link.l1 = "Várlak.";
			    link.l1.go = "ship_tunning_TurnRate_complite";
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_TurnRate_again";
				dialog.Text = "Még mindig szükségem van: kötelek - "+ sti(NPChar.Tuning.Matherial) + ".";
				link.l1 = "Rendben.";
				link.l1.go = "Exit";
                AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "Hoznom kell: köteleket - "+ sti(NPChar.Tuning.Matherial) + ".");
			}
		break;
		
		case "ship_tunning_TurnRate_complite":
		    AddTimeToCurrent(6, 30);
		    shTo = &RealShips[sti(Pchar.Ship.Type)];
		    DeleteAttribute(NPChar, "Tuning");
		    // изменим
			if(!CheckAttribute(shTo, "Bonus_TurnRate"))
			{
				shTo.TurnRate        = (stf(shTo.TurnRate) + stf(shTo.TurnRate)/5.0);
			}
			else
			{
				shTo.TurnRate        = (stf(shTo.TurnRate) - stf(shTo.Bonus_TurnRate)) * 1.2 + stf(shTo.Bonus_TurnRate);
			}	

	        shTo.Tuning.TurnRate = true;
			if(!CheckAttribute(pchar, "achievment.Tuning.stage4") && CheckAttribute(shTo,"Tuning.TurnRate") && CheckAttribute(shTo,"Tuning.MinCrew")) 
			{
				pchar.achievment.Tuning.stage4 = true;
			}	
            TuningAvailable();
			dialog.Text = "... Most már mindennek készen kell állnia... Ellenôrizze a kormánykereket, kapitány!";
			Link.l1 = "Köszönöm! Majd én tesztelem.";
			Link.l1.go = "Exit";
			AddQuestRecord("ShipTuning", "End");
			CloseQuestHeader("ShipTuning");
			notification("Sokat tanultál a hajó szerkezetérôl!", "none");
			AddCharacterExpToSkill(pchar, SKILL_SAILING, 5.0 * makefloat(GetMaterialQtyUpgrade(pchar, NPChar, 2 )));
		break;
		
		////////////////////////////////////////// MaxCrew ////////////////////////////////////////////////////
		case "ship_tunning_MaxCrew":
			Material  = GetMaterialQtyUpgrade(pchar, NPChar, 1 );
			WorkPrice = GetMaterialQtyUpgrade(pchar, NPChar, 2 );				
			s2 = "Akkor lássuk, mit tehetünk. Jelenleg a legénységed maximális létszáma a túlterheléssel együtt " + sti(RealShips[sti(Pchar.Ship.Type)].MaxCrew) + " ember.";			
			s2 = s2 + " Szükségem lesz: vasfa - "+ Material + ".";
			s2 = s2 + " A munkámért fizetségként elfogadom: " + WorkPrice + " láda dublonokat - a költségeim fedezésére. Ez minden. Ó, és készpénz elôre.";									
            dialog.Text = s2;
			Link.l1 = "Egyetértek. Elfogadom a feltételeidet. Elhozom, amire csak szüksége van.";
			Link.l1.go = "ship_tunning_MaxCrew_start";
			Link.l2 = "Nem. Ez nem tetszik nekem.";
			Link.l2.go = "ship_tunning_not_now_1";
		break;
		
		case "ship_tunning_MaxCrew_start":
			amount = GetMaterialQtyUpgrade(pchar, NPChar, 2 );
			// belamour legendary edition туда сюда бегать - та ещё морока -->
			if(GetCharacterItem(pchar,"chest") + CheckItemMyCabin("chest") >= amount)		    
			{
				if(GetCharacterItem(pchar,"chest") >= amount)
				{				
					TakeNItems(pchar,"chest", -amount);
				}
				else
				{
					iSumm = amount - sti(GetCharacterItem(pchar,"chest"));
					TakeNItems(pchar,"chest", -sti(GetCharacterItem(pchar,"chest")));
					GetItemMyCabin("chest", iSumm);
					Log_Info("A kabinból ládányi dublont vittek el: " + iSumm+ " db.");
				}
				// <-- legendary edtion		
			    NPChar.Tuning.Money  		= amount;
			    NPChar.Tuning.Matherial 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 ); 			    
			    NPChar.Tuning.ShipType      = Pchar.Ship.Type;
			    NPChar.Tuning.ShipName      = RealShips[sti(Pchar.Ship.Type)].BaseName;
				NextDiag.TempNode = "ship_tunning_MaxCrew_again";
                dialog.text = "Remek. Várom az anyagot.";
				link.l1 = LinkRandPhrase("Biztosíthatom, hogy nem kell sokáig várnia. Meg tudom oldani az ilyen problémákat, rendben?",
										 "Tekintse úgy, hogy már megvan, és tartsa meg nekem a dokkolót. Olyan gyors leszek, mint a szél.",
										 "Természetesen. Csak meg kell látogatnom néhány személyt, akiknek megvan a kért cucc, ha-ha!");
			    link.l1.go = "Exit";			    
			    ReOpenQuestHeader("ShipTuning");
			    AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "A legénység növelésére tett erôfeszítéseikért " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName + "Voc")) + " '" + pchar.ship.name + "'" +
				" hajósnak szüksége van: vasfa - " + NPChar.Tuning.Matherial + ". Elôre letétet fizettek " + NPChar.Tuning.Money + " láda dublont.");
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_not_now_1";
                dialog.text = "Nem látom a letétet...";
				link.l1 = "Majd késôbb benézek.";
				link.l1.go = "Exit";								
			}
		break;
		
		case "ship_tunning_MaxCrew_again":
		    if (sti(NPChar.Tuning.ShipType) == sti(Pchar.Ship.Type) && NPChar.Tuning.ShipName == RealShips[sti(Pchar.Ship.Type)].BaseName  && TuningAvailable())
		    {
                NextDiag.TempNode = "ship_tunning_MaxCrew_again";
				dialog.Text = "Az idô telik, és a hajó már vár. Mindent elhoztál, amit kértem?";
			    Link.l1 = "Igen, sikerült találnom valamit.";
			    Link.l1.go = "ship_tunning_MaxCrew_again_2";
			    Link.l2 = "Nem, még mindig rajta vagyok.";
			    Link.l2.go = "Exit";
			}
			else
			{
			    DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
				dialog.Text = "Mis"+ GetSexPhrase("ter","s") +", megváltoztatta a hajóját, mióta megállapodtunk? Nem kellett volna.";
			    Link.l1 = "Sajnos, a körülmények miatt! Kár, hogy a letét elveszett...";				
			    Link.l1.go = "Exit";
				DeleteAttribute(pchar,"achievment.Tuning");
			    AddQuestRecord("ShipTuning", "Lose");
			    CloseQuestHeader("ShipTuning");
			}
		break;
		
		case "ship_tunning_MaxCrew_again_2":
		    checkMatherial(Pchar, NPChar, GOOD_SANDAL);		    
		    if(sti(NPChar.Tuning.Matherial) < 1)
			{
				DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
                dialog.text = "Kiváló, most már mindenem megvan, amire szükségem van. Akkor elkezdek dolgozni.";
			    link.l1 = "Várok.";
			    link.l1.go = "ship_tunning_MaxCrew_complite";
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_MaxCrew_again";
				dialog.Text = "Még mindig szükségem van: vasfa - "+ sti(NPChar.Tuning.Matherial) + ".";
				link.l1 = "Rendben.";
				link.l1.go = "Exit";
                AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "Hoznom kell: vasfa - "+ sti(NPChar.Tuning.Matherial) + ".");
			}
		break;
		
		case "ship_tunning_MaxCrew_complite":
		    AddTimeToCurrent(6, 30);
		    shTo = &RealShips[sti(Pchar.Ship.Type)];
		    DeleteAttribute(NPChar, "Tuning");
		    
	        if(sti(shTo.Spec) == SHIP_SPEC_UNIVERSAL)
			{
				shTo.MaxCrew        = sti(shTo.MaxCrew) + makeint(sti(shTo.MaxCrew) * 0.35);
			}
			else
			{
				shTo.MaxCrew        = sti(shTo.MaxCrew) + makeint(sti(shTo.MaxCrew)/5);
			}
	        shTo.Tuning.MaxCrew = true;
			if(!CheckAttribute(pchar, "achievment.Tuning.stage3") && CheckAttribute(shTo,"Tuning.MaxCrew") && CheckAttribute(shTo,"Tuning.HP")) 
			
			{
				pchar.achievment.Tuning.stage3 = true;
			}	
            TuningAvailable();
            NextDiag.TempNode = "First time";
			dialog.Text = "... Kész van, kapitány. Most már felvehet több matrózt, lesz elég hely mindenkinek.";
			Link.l1 = "Köszönöm! Majd én tesztelem.";
			Link.l1.go = "Exit";
			
			AddQuestRecord("ShipTuning", "End");
			CloseQuestHeader("ShipTuning");
			notification("Sokat tanultál a hajó szerkezetérôl!", "none");
			AddCharacterExpToSkill(pchar, SKILL_DEFENCE, 5.0 * makefloat(GetMaterialQtyUpgrade(pchar, NPChar, 2 )));
			AddCharacterExpToSkill(pchar, SKILL_GRAPPLING, 5.0 * makefloat(GetMaterialQtyUpgrade(pchar, NPChar, 2 )));
		break;

		
		////////////////////////////////////////// MinCrew ////////////////////////////////////////////////////
		case "ship_tunning_MinCrew":
			Material 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 );			
			WorkPrice 	= GetMaterialQtyUpgrade(pchar, NPChar, 2 );				
			s2 = "Akkor lássuk, mit tehetünk. Jelenleg a legénységedhez szükséges minimális matrózok száma " + sti(RealShips[sti(Pchar.Ship.Type)].MinCrew) + " ember.";			
			s2 = s2 + " A hajó irányíthatóságának javítása és a legénységben szükséges matrózok számának csökkentése érdekében szükségem lesz: kötelekre - "+ Material + ".";
			s2 = s2 + " A munkámért fizetségként elfogadom: " + WorkPrice + " láda dublonokat - a költségeim fedezésére. Ez minden. Ó, és készpénz elôre.";									
            dialog.Text = s2;
			Link.l1 = "Egyetértek. Elfogadom a feltételeidet. Elhozom, amire csak szüksége van.";
			Link.l1.go = "ship_tunning_MinCrew_start";
			Link.l2 = "Nem. Ez nem tetszik nekem.";
			Link.l2.go = "ship_tunning_not_now_1";
		break;
		
		case "ship_tunning_MinCrew_start":
			amount = GetMaterialQtyUpgrade(pchar, NPChar, 2 );
			// belamour legendary edition туда сюда бегать - та ещё морока -->
			if(GetCharacterItem(pchar,"chest") + CheckItemMyCabin("chest") >= amount)		    
			{
				if(GetCharacterItem(pchar,"chest") >= amount)
				{				
					TakeNItems(pchar,"chest", -amount);
				}
				else
				{
					iSumm = amount - sti(GetCharacterItem(pchar,"chest"));
					TakeNItems(pchar,"chest", -sti(GetCharacterItem(pchar,"chest")));
					GetItemMyCabin("chest", iSumm);
					Log_Info("A kabinból ládányi dublont vittek el: " + iSumm+ " db.");
				}
				// <-- legendary edtion		
			    NPChar.Tuning.Money  		= amount;
			    NPChar.Tuning.Matherial 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 ); 			    
			    NPChar.Tuning.ShipType      = Pchar.Ship.Type;
			    NPChar.Tuning.ShipName      = RealShips[sti(Pchar.Ship.Type)].BaseName;
				NextDiag.TempNode = "ship_tunning_MinCrew_again";
                dialog.text = "Remek. Várom az anyagot.";
				link.l1 = LinkRandPhrase("Biztosíthatom, hogy nem kell sokáig várnia. Meg tudom oldani az ilyen problémákat, rendben?",
										 "Tekintse úgy, hogy már megvan, és tartsa meg nekem a dokkolót. Olyan gyors leszek, mint a szél.",
										 "Természetesen. Csak meg kell látogatnom néhány személyt, akiknek megvan a kért cucc, ha-ha!");
			    link.l1.go = "Exit";			    
			    ReOpenQuestHeader("ShipTuning");
			    AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "Munkájához, hogy csökkentse a minimálisan szükséges legénység létszámát a " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName + "Voc")) + " '" + pchar.ship.name + "'" +			
				" hajósnak szüksége van: kötelekre - " + NPChar.Tuning.Matherial + ". Elôre letétet fizettek " + NPChar.Tuning.Money + " láda dublont.");
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_not_now_1";
                dialog.text = "Nem látom a letétet...";
				link.l1 = "Majd késôbb benézek.";
				link.l1.go = "Exit";								
			}
		break;
		
		case "ship_tunning_MinCrew_again":
		    if (sti(NPChar.Tuning.ShipType) == sti(Pchar.Ship.Type) && NPChar.Tuning.ShipName == RealShips[sti(Pchar.Ship.Type)].BaseName  && TuningAvailable())
		    {
                NextDiag.TempNode = "ship_tunning_MinCrew_again";
				dialog.Text = "Az idô telik, és a hajó már vár. Mindent elhoztál, amit kértem?";
			    Link.l1 = "Igen, sikerült találnom valamit.";
			    Link.l1.go = "ship_tunning_MinCrew_again_2";
			    Link.l2 = "Nem, még mindig rajta vagyok.";
			    Link.l2.go = "Exit";
			}
			else
			{
			    DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
				dialog.Text = "Mis"+ GetSexPhrase("ter","s") +", megváltoztatta a hajóját, mióta megállapodtunk? Nem kellett volna.";
			    Link.l1 = "Sajnos, a körülmények miatt! Kár, hogy a letét elveszett...";
			    Link.l1.go = "Exit";			    
				DeleteAttribute(pchar,"achievment.Tuning");	
			    AddQuestRecord("ShipTuning", "Lose");
			    CloseQuestHeader("ShipTuning");
			}
		break;
		
		case "ship_tunning_MinCrew_again_2":
		    checkMatherial(Pchar, NPChar, GOOD_ROPES);		    
		    if(sti(NPChar.Tuning.Matherial) < 1)
			{
				DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
                dialog.text = "Kiváló, most már mindenem megvan, amire szükségem van. Akkor elkezdek dolgozni.";
			    link.l1 = "Várok.";
			    link.l1.go = "ship_tunning_MinCrew_complite";
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_MinCrew_again";
				dialog.Text = "Még mindig szükségem van: kötelek - "+ sti(NPChar.Tuning.Matherial) + ".";
				link.l1 = "Rendben.";
				link.l1.go = "Exit";
                AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "Hoznom kell: köteleket - "+ sti(NPChar.Tuning.Matherial) + ".");
			}
		break;
		
		case "ship_tunning_MinCrew_complite":
		    AddTimeToCurrent(6, 30);
		    shTo = &RealShips[sti(Pchar.Ship.Type)];
		    DeleteAttribute(NPChar, "Tuning");
		    // изменим
	        if(sti(shTo.Spec) == SHIP_SPEC_UNIVERSAL)
			{
				shTo.MinCrew        = sti(shTo.MinCrew) - makeint(sti(shTo.MinCrew) * 0.35);
			}
			else
			{
				shTo.MinCrew        = sti(shTo.MinCrew) - makeint(sti(shTo.MinCrew)/5);
			}
			if(sti(shTo.MinCrew) < 1) shTo.MinCrew = 1;
	        shTo.Tuning.MinCrew = true;
			
			if(!CheckAttribute(pchar, "achievment.Tuning.stage4")  && CheckAttribute(shTo,"Tuning.TurnRate") && CheckAttribute(shTo,"Tuning.MinCrew")) 
			{
				pchar.achievment.Tuning.stage4 = true;
			}	
            TuningAvailable();
            NextDiag.TempNode = "First time";
			dialog.Text = "... Kész, kapitány! Most már kevesebb matróz tudja irányítani a hajót, ugyanazzal az összteljesítménnyel.";
			Link.l1 = "Köszönöm! Majd én tesztelem.";
			Link.l1.go = "Exit";
			
			AddQuestRecord("ShipTuning", "End");
			CloseQuestHeader("ShipTuning");
			notification("Sokat tanultál a hajó szerkezetérôl!", "none");
			AddCharacterExpToSkill(pchar, SKILL_DEFENCE, 5.0 * makefloat(GetMaterialQtyUpgrade(pchar, NPChar, 2 )));
			AddCharacterExpToSkill(pchar, SKILL_GRAPPLING, 5.0 * makefloat(GetMaterialQtyUpgrade(pchar, NPChar, 2 )));
		break;
		
		////////////////////////////////////////// HP ////////////////////////////////////////////////////
		case "ship_tunning_HP":
			Material 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 );
			WorkPrice 	= GetMaterialQtyUpgrade(pchar, NPChar, 2 );			
			s2 = "Lássuk hát, mit tehetünk. Jelenleg a hajótest " + sti(RealShips[sti(Pchar.Ship.Type)].HP);			
			s2 = s2 + ". A hajótest megerôsítéséhez szükségem lesz: gyantára - "+ Material + ".";
			s2 = s2 + " A munkámért fizetségként elfogadom: " + WorkPrice + " láda dublonokat - a költségeim fedezésére. Ez minden. Ó, és készpénz elôre.";									
            dialog.Text = s2;
			Link.l1 = "Egyetértek. Elfogadom a feltételeidet. Elhozom, amire csak szüksége van.";
			Link.l1.go = "ship_tunning_HP_start";
			Link.l2 = "Nem. Ez nem tetszik nekem.";
			Link.l2.go = "ship_tunning_not_now_1";
		break;
		
		case "ship_tunning_HP_start":
			amount = GetMaterialQtyUpgrade(pchar, NPChar, 2 );
			// belamour legendary edition туда сюда бегать - та ещё морока -->
			if(GetCharacterItem(pchar,"chest") + CheckItemMyCabin("chest") >= amount)		    
			{
				if(GetCharacterItem(pchar,"chest") >= amount)
				{				
					TakeNItems(pchar,"chest", -amount);
				}
				else
				{
					iSumm = amount - sti(GetCharacterItem(pchar,"chest"));
					TakeNItems(pchar,"chest", -sti(GetCharacterItem(pchar,"chest")));
					GetItemMyCabin("chest", iSumm);
					Log_Info("A kabinból ládányi dublont vittek el: " + iSumm+ " db.");
				}
				// <-- legendary edtion		
			    NPChar.Tuning.Money  		= amount;
			    NPChar.Tuning.Matherial 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 ); 			    
			    NPChar.Tuning.ShipType      = Pchar.Ship.Type;
			    NPChar.Tuning.ShipName      = RealShips[sti(Pchar.Ship.Type)].BaseName;
				NextDiag.TempNode = "ship_tunning_HP_again";
                dialog.text = "Remek. Várom az anyagot.";
				link.l1 = LinkRandPhrase("Biztosíthatom, hogy nem kell sokáig várnia. Meg tudom oldani az ilyen problémákat, rendben?",
										 "Tekintse úgy, hogy már megvan, és tartsa meg nekem a dokkolót. Olyan gyors leszek, mint a szél.",
										 "Természetesen. Csak meg kell látogatnom néhány személyt, akiknek megvan a kért cucc, ha-ha!");
			    link.l1.go = "Exit";
			    ReOpenQuestHeader("ShipTuning");
			    AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "A hajótest szilárdságának növelésére tett erôfeszítéseihez " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName + "Voc")) + " '" + pchar.ship.name + "'" +			
				" hajósnak szüksége van: gyantára - " + NPChar.Tuning.Matherial + ". Elôre letétet fizettek " + NPChar.Tuning.Money + " láda dublont.");
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_not_now_1";
                dialog.text = "Nem látom a letétet...";
				link.l1 = "Majd késôbb benézek.";
				link.l1.go = "Exit";								
			}
		break;
		
		case "ship_tunning_HP_again":
		    if (sti(NPChar.Tuning.ShipType) == sti(Pchar.Ship.Type) && NPChar.Tuning.ShipName == RealShips[sti(Pchar.Ship.Type)].BaseName && TuningAvailable())
		    {
                NextDiag.TempNode = "ship_tunning_HP_again";
				dialog.Text = "Az idô telik, és a hajó már vár. Mindent elhoztál, amit kértem?";
			    Link.l1 = "Igen, sikerült találnom valamit.";
			    Link.l1.go = "ship_tunning_HP_again_2";
			    Link.l2 = "Nem, még mindig rajta vagyok.";
			    Link.l2.go = "Exit";
			}
			else
			{
			    DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
				dialog.Text = "Mis"+ GetSexPhrase("ter","s") +", megváltoztatta a hajóját, mióta megállapodtunk? Nem kellett volna.";
			    Link.l1 = "Sajnos, a körülmények miatt! Kár, hogy a letét elveszett...";
			    Link.l1.go = "Exit";			    
				DeleteAttribute(pchar,"achievment.Tuning");	
			    AddQuestRecord("ShipTuning", "Lose");
			    CloseQuestHeader("ShipTuning");
			}
		break;
		
		case "ship_tunning_HP_again_2":
		    checkMatherial(Pchar, NPChar, GOOD_OIL);		
		    if(sti(NPChar.Tuning.Matherial) < 1)
			{
				DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
                dialog.text = "Kiváló, most már mindenem megvan, amire szükségem van. Akkor elkezdek dolgozni.";
			    link.l1 = "Várok.";
			    link.l1.go = "ship_tunning_HP_complite";
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_HP_again";
				dialog.Text = "Még mindig szükségem van: gyanta - "+ sti(NPChar.Tuning.Matherial) + ".";
				link.l1 = "Rendben.";
				link.l1.go = "Exit";
                AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "Hoznom kell: gyantát - "+ sti(NPChar.Tuning.Matherial) + ".");
			}
		break;
		
		case "ship_tunning_HP_complite":
		    AddTimeToCurrent(6, 30);
		    shTo = &RealShips[sti(Pchar.Ship.Type)];
		    DeleteAttribute(NPChar, "Tuning");
		    // изменим
			if(!CheckAttribute(shTo, "Bonus_HP"))
			{
				if(sti(shTo.Spec) == SHIP_SPEC_UNIVERSAL)
				{
					shTo.HP        = sti(shTo.HP) + makeint(sti(shTo.HP) * 0.35);
				}
				else
				{
					shTo.HP        = sti(shTo.HP) + makeint(sti(shTo.HP)/5);
				}
			}
			else
			{
				if(sti(shTo.Spec) == SHIP_SPEC_UNIVERSAL)
				{
					if(sti(shTo.HP) > sti(shTo.Bonus_HP)) // иначе апгрейд будет умножать отрицательное значение
					{
						shTo.HP    = makeint((sti(shTo.HP) - sti(shTo.Bonus_HP)) * 1.35 + sti(shTo.Bonus_HP));
					}
				}
				else
				{
					if(sti(shTo.HP) > sti(shTo.Bonus_HP)) // иначе апгрейд будет умножать отрицательное значение
					{
						shTo.HP    = makeint((sti(shTo.HP) - sti(shTo.Bonus_HP)) * 1.2 + sti(shTo.Bonus_HP));
					}
				}
			}
	        shTo.Tuning.HP = true;
			ProcessHullRepair(pchar, 100.0); // у нпс при апгрейде есть, здесь тоже должно быть

			if(!CheckAttribute(pchar, "achievment.Tuning.stage3") && CheckAttribute(shTo,"Tuning.MaxCrew") && CheckAttribute(shTo,"Tuning.HP")) 
			{
				pchar.achievment.Tuning.stage3 = true;
			}	
			TuningAvailable();
            NextDiag.TempNode = "First time";
			
			dialog.Text = "... Ez elég lesz... Garantálom, hogy mostantól az ellenségeidnek sokkal nehezebb lesz darabokra tépni a hajód burkolatát!";
			Link.l1 = "Heh, ezt elhiszem neked! Köszönöm, mester.";
			Link.l1.go = "Exit";
			
			AddQuestRecord("ShipTuning", "End");
			CloseQuestHeader("ShipTuning");
			notification("Sokat tanultál a hajó szerkezetérôl!", "none");
			AddCharacterExpToSkill(pchar, SKILL_DEFENCE, 5.0 * makefloat(GetMaterialQtyUpgrade(pchar, NPChar, 2 )));
			AddCharacterExpToSkill(pchar, SKILL_REPAIR, 5.0 * makefloat(GetMaterialQtyUpgrade(pchar, NPChar, 2 )));
		break;
		
		////////////////////////////////////////// WindAgainst ////////////////////////////////////////////////////
		case "ship_tunning_WindAgainst":
			Material 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 );
			WorkPrice 	= GetMaterialQtyUpgrade(pchar, NPChar, 2 );
			fTmp = 180.0 - (acos(1 - stf(RealShips[sti(Pchar.Ship.Type)].WindAgainstSpeed)) * 180.0/PI);
			s2 = "Akkor lássuk, mit tehetünk. Jelenleg a vitorlák szél általi vitorlázási pontja " + makeint(fTmp) + " fok.";
			// belamour legendary edition если спускать курс по ветру, то это даунгрейд
			s2 = s2 + " A hajó széllel szemben történô gyorsításához szükségem lesz: hajóselyem - "+ Material + ",";
			s2 = s2 + " A munkámért fizetségként elfogadom: " + WorkPrice + " láda dublonokat - a költségeim fedezésére. Ez minden. Ó, és készpénz elôre.";									
            dialog.Text = s2;
			Link.l1 = "Egyetértek. Elfogadom a feltételeidet. Elhozom, amire csak szüksége van.";
			Link.l1.go = "ship_tunning_WindAgainst_start";
			Link.l2 = "Nem. Ez nem tetszik nekem.";
			Link.l2.go = "ship_tunning_not_now_1";
		break;

		case "ship_tunning_WindAgainst_start":
			amount = GetMaterialQtyUpgrade(pchar, NPChar, 2 );
			// belamour legendary edition туда сюда бегать - та ещё морока -->
			if(GetCharacterItem(pchar,"chest") + CheckItemMyCabin("chest") >= amount)		    
			{
				if(GetCharacterItem(pchar,"chest") >= amount)
				{				
					TakeNItems(pchar,"chest", -amount);
				}
				else
				{
					iSumm = amount - sti(GetCharacterItem(pchar,"chest"));
					TakeNItems(pchar,"chest", -sti(GetCharacterItem(pchar,"chest")));
					GetItemMyCabin("chest", iSumm);
					Log_Info("A kabinból ládányi dublont vittek el: " + iSumm+ " db.");
				}
				// <-- legendary edtion		
			    NPChar.Tuning.Money  		= amount;
			    NPChar.Tuning.Matherial    	= GetMaterialQtyUpgrade(pchar, NPChar, 1 );			    
			    NPChar.Tuning.ShipType      = Pchar.Ship.Type;
			    NPChar.Tuning.ShipName      = RealShips[sti(Pchar.Ship.Type)].BaseName;
				NextDiag.TempNode = "ship_tunning_WindAgainst_again";
                dialog.text = "Remek. Várom az anyagot.";
				link.l1 = LinkRandPhrase("Biztosíthatom, hogy nem kell sokáig várnia. Meg tudom oldani az ilyen problémákat, rendben?",
										 "Tekintse úgy, hogy már megvan, és tartsa meg nekem a dokkolót. Olyan gyors leszek, mint a szél.",
										 "Természetesen. Csak meg kell látogatnom néhány személyt, akiknek megvan a kért cucc, ha-ha!");
			    link.l1.go = "Exit";

			    ReOpenQuestHeader("ShipTuning");
			    AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "A szél szögének megváltoztatásával kapcsolatos munkájához " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName + "Voc")) + " '" + pchar.ship.name + "'" +			
				" hajósnak szüksége van: hajóselyem - " + NPChar.Tuning.Matherial + ". Elôre letétet fizettek " + NPChar.Tuning.Money + " láda dublont.");
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_not_now_1";
                dialog.text = "Nem látom a letétet...";
				link.l1 = "Majd késôbb benézek.";
				link.l1.go = "Exit";
			}
		break;

		case "ship_tunning_WindAgainst_again":
		    if (sti(NPChar.Tuning.ShipType) == sti(Pchar.Ship.Type) && NPChar.Tuning.ShipName == RealShips[sti(Pchar.Ship.Type)].BaseName  && TuningAvailable())
		    {
                NextDiag.TempNode = "ship_tunning_WindAgainst_again";
			    dialog.Text = "Az idô telik, és a hajó már vár. Mindent elhoztál, amit kértem?";
			    Link.l1 = "Igen, sikerült szállítanom valamit.";
			    Link.l1.go = "ship_tunning_WindAgainst_again_2";
			    Link.l2 = "Nem, még mindig rajta vagyok.";
			    Link.l2.go = "Exit";
			}
			else
			{
			    DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
				dialog.Text = "Mis"+ GetSexPhrase("ter","s") +", megváltoztatta a hajóját, mióta megállapodtunk? Nem kellett volna.";
			    Link.l1 = "Sajnos, a körülmények miatt! Kár, hogy a letét elveszett...";
			    Link.l1.go = "Exit";
				DeleteAttribute(pchar,"achievment.Tuning");
			    AddQuestRecord("ShipTuning", "Lose");
			    CloseQuestHeader("ShipTuning");
			}
		break;

		case "ship_tunning_WindAgainst_again_2":
		    checkMatherial(Pchar, NPChar, GOOD_SHIPSILK);
		    if(sti(NPChar.Tuning.Matherial) < 1)
			{
				DeleteAttribute(NPChar, "Tuning");
                NextDiag.TempNode = "First time";
                dialog.text = "Kiváló, most már mindenem megvan, amire szükségem van. Akkor elkezdek dolgozni.";
			    link.l1 = "Várok.";
			    link.l1.go = "ship_tunning_WindAgainst_complite";
			}
			else
			{
				NextDiag.TempNode = "ship_tunning_WindAgainst_again";
                dialog.Text = "Még mindig szükségem van: hajóselyem - "+ sti(NPChar.Tuning.Matherial) + ".";
				link.l1 = "Rendben.";
				link.l1.go = "Exit";
                AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "Hoznom kell: hajóselyem - "+ sti(NPChar.Tuning.Matherial) + ".");
			}
		break;

		case "ship_tunning_WindAgainst_complite":
		    AddTimeToCurrent(6, 30);
		    shTo = &RealShips[sti(Pchar.Ship.Type)];
		    DeleteAttribute(NPChar, "Tuning");
		    // изменим			
			// belamour legendary edtion чем больше WindAgainstSpeed, тем круче к ветру
	        if(sti(shTo.Spec) == SHIP_SPEC_UNIVERSAL)
			{
				shTo.WindAgainstSpeed   = stf(shTo.WindAgainstSpeed) + 0.35 * stf(shTo.WindAgainstSpeed);	
			}
			else
			{
				shTo.WindAgainstSpeed   = stf(shTo.WindAgainstSpeed) + 0.20 * stf(shTo.WindAgainstSpeed);
			}
			if (stf(shTo.WindAgainstSpeed) > 1.985) shTo.WindAgainstSpeed = 1.985;
	        shTo.Tuning.WindAgainst = true;

			if(!CheckAttribute(pchar, "achievment.Tuning.stage1") && CheckAttribute(shTo, "Bonus_SpeedRate") &&  CheckAttribute(shTo,"Tuning.WindAgainst")) 
			{
				pchar.achievment.Tuning.stage1 = true;
			}	
            TuningAvailable();
            NextDiag.TempNode = "First time";
			dialog.Text = "... Kész, kapitány! A hajód mostantól sokkal gyorsabban fog felfelé haladni.";
			Link.l1 = "Köszönöm! Majd én tesztelem.";
			Link.l1.go = "Exit";

			AddQuestRecord("ShipTuning", "End");
			CloseQuestHeader("ShipTuning");
			notification("Sokat tanultál a hajó szerkezetérôl!", "none");
			AddCharacterExpToSkill(pchar, SKILL_SAILING, 5.0 * makefloat(GetMaterialQtyUpgrade(pchar, NPChar, 2 )));
		break;
						
		////////////////////////////////////////// только количество орудий  ////////////////////////////////////////////////////	
		case "ship_c_quantity":
			Material 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 );			
			WorkPrice 	= GetMaterialQtyUpgrade(pchar, NPChar, 2 );			
			s2 = "Lássuk, mit lehet ott tenni. Jelenleg a hajódon lévô ágyúk száma " + sti(RealShips[sti(Pchar.Ship.Type)].CannonsQuantity) + ", a maximálisan lehetséges szám pedig - " + sti(RealShips[sti(Pchar.Ship.Type)].CannonsQuantityMax) + ".";			
			s2 = s2 + " Azonnal megmondom, hogy nem lesz olcsó. Szükségem lesz: gyanta - "+ Material + ",";
			s2 = s2 + " A munkámért fizetségként elfogadom: " + WorkPrice + " láda dublonokat - a költségeim fedezésére. Ez minden. Ó, és készpénz elôre.";						
			dialog.Text = s2;		
			Link.l1 = "Egyetértek. Elfogadom a feltételeidet. Elhozom, amire csak szüksége van.";
			Link.l1.go = "ship_c_quantity_start";		
			Link.l2 = "Nem. Ez nem tetszik nekem.";
			Link.l2.go = "ship_tunning_not_now_1";
		break;
		
		case "ship_c_quantity_start":
			amount = GetMaterialQtyUpgrade(pchar, NPChar, 2 );
			// belamour legendary edition туда сюда бегать - та ещё морока -->
			if(GetCharacterItem(pchar,"chest") + CheckItemMyCabin("chest") >= amount)		    
			{
				if(GetCharacterItem(pchar,"chest") >= amount)
				{				
					TakeNItems(pchar,"chest", -amount);
				}
				else
				{
					iSumm = amount - sti(GetCharacterItem(pchar,"chest"));
					TakeNItems(pchar,"chest", -sti(GetCharacterItem(pchar,"chest")));
					GetItemMyCabin("chest", iSumm);
					Log_Info("A kabinból ládányi dublont vittek el: " + iSumm+ " db.");
				}
				// <-- legendary edtion		
			    NPChar.Tuning.Money  		= amount;
				NPChar.Tuning.Cannon 		= true;				
				NPChar.Tuning.Matherial 	= GetMaterialQtyUpgrade(pchar, NPChar, 1 ); 				
				NPChar.Tuning.ShipType      = Pchar.Ship.Type;
				NPChar.Tuning.ShipName      = RealShips[sti(Pchar.Ship.Type)].BaseName;											    
				NextDiag.TempNode = "ship_c_quantity_again";
				dialog.text = "Remek. Várom az anyagot.";
				link.l1 = LinkRandPhrase("Biztosíthatom, hogy nem kell sokáig várnia. Meg tudom oldani az ilyen problémákat, rendben?",
										 "Tekintse úgy, hogy már megvan, és tartsa meg nekem a dokkolót. Olyan gyors leszek, mint a szél.",
										 "Természetesen. Csak meg kell látogatnom néhány személyt, akiknek megvan a kért cucc, ha-ha!");
				link.l1.go = "Exit";			    
				ReOpenQuestHeader("ShipTuning");
				AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "Az ágyúk számának növelésére irányuló munkájához a " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName + "Voc")) + " '" + pchar.ship.name + "'" +						
				" hajóépítônek szüksége van: gyanta - " + NPChar.Tuning.Matherial + ". Elôre letétet fizettek " + NPChar.Tuning.Money + " láda dublont.");				
			}		
			else
			{ 
				NextDiag.TempNode = "ship_tunning_not_now_1";
				dialog.text = "Nem látom a letétet...";
				link.l1 = "Majd késôbb benézek.";
				link.l1.go = "Exit";
			}
		break;		
		
		case "ship_c_quantity_again":	
			if (sti(NPChar.Tuning.ShipType) == sti(Pchar.Ship.Type) && NPChar.Tuning.ShipName == RealShips[sti(Pchar.Ship.Type)].BaseName && TuningAvailable())
			{
				NextDiag.TempNode = "ship_c_quantity_again";
				dialog.Text = "Az idô telik, és a hajó már vár. Mindent elhoztál, amit kértem?";
				Link.l1 = "Igen, sikerült találnom valamit.";
				Link.l1.go = "ship_c_quantity_again_2";
				Link.l2 = "Nem, még mindig rajta vagyok.";
				Link.l2.go = "Exit";
			}		
			else
			{
				DeleteAttribute(NPChar, "Tuning");
				NextDiag.TempNode = "First time";
				dialog.Text = "Mis"+ GetSexPhrase("ter","s") +", megváltoztatta a hajóját, mióta megállapodtunk? Nem kellett volna.";
			    Link.l1 = "Sajnos, a körülmények miatt! Kár, hogy a letét elveszett...";
				Link.l1.go = "Exit";
				DeleteAttribute(pchar,"achievment.Tuning");
				AddQuestRecord("ShipTuning", "Lose");
				CloseQuestHeader("ShipTuning");
			}		
		break;
		
		case "ship_c_quantity_again_2":		
			checkMatherial(Pchar, NPChar, GOOD_OIL);
			if(sti(NPChar.Tuning.Matherial) < 1)
			{
				DeleteAttribute(NPChar, "Tuning");
				NextDiag.TempNode = "First time";
				dialog.text = "Kiváló, most már mindenem megvan, amire szükségem van. Akkor elkezdek dolgozni.";
				link.l1 = "Várok.";
				link.l1.go = "ship_c_quantity_complite";
			}
			else
			{
				NextDiag.TempNode = "ship_c_quantity_again";
				dialog.Text = "Még mindig szükségem van: gyanta - "+ sti(NPChar.Tuning.Matherial) + ".";
				link.l1 = "Rendben.";
				link.l1.go = "Exit";
				AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", "Hoznom kell: gyantát - "+ sti(NPChar.Tuning.Matherial) + ".");
			}		
		break;
		
		case "ship_c_quantity_complite":
			AddTimeToCurrent(6, 30);
			shTo = &RealShips[sti(Pchar.Ship.Type)];
			DeleteAttribute(NPChar, "Tuning");		
			makearef(refShip, pchar.Ship);
			
			iCannonDiff = sti(refShip.CannonDiff);
			iCannonDiff -= 1;
								
			for (i = 0; i < sti(shTo.cannonr); i++)
			{
				attr = "c" + i;										
					
				if(i < (sti(shTo.cannonr) - iCannonDiff) )	
				{
					if( stf(refShip.Cannons.Borts.cannonr.damages.(attr)) > 1.0 )
					{
						refShip.Cannons.Borts.cannonr.damages.(attr) = 1.0; 
					}	
				}					
			}	
			for (i = 0; i < sti(shTo.cannonl); i++)
			{
				attr = "c" + i;
				if(i < (sti(shTo.cannonl) - iCannonDiff) )	
				{
					if( stf(refShip.Cannons.Borts.cannonl.damages.(attr)) > 1.0 )
					{
						refShip.Cannons.Borts.cannonl.damages.(attr) = 1.0; 
					}	
				}										
			}	
			
			if(CheckAttribute(shTo,"CannonsQuantityMax")) 	shTo.Cannons = sti(shTo.CannonsQuantityMax) - iCannonDiff * 2;
			else										    shTo.Cannons = sti(shTo.CannonsQuantity) - iCannonDiff * 2;
			
			shTo.CannonsQuantity = sti(shTo.Cannons);
		
			refShip.Cannons = sti(shTo.Cannons);
			refShip.CannonDiff = iCannonDiff;			

			shTo.Tuning.Cannon = true;
			
			if(!CheckAttribute(pchar, "achievment.Tuning.stage2") && CheckAttribute(shTo,"Tuning.Cannon") && CheckAttribute(shTo,"Tuning.Capacity")) 
			{
				pchar.achievment.Tuning.stage2 = true;
			}	
			TuningAvailable();
			NextDiag.TempNode = "First time";
			dialog.Text = "... Ez az, kapitány. Használhatsz további ágyúkat - már ha vannak, he-he.";
			Link.l1 = "Köszönjük!";
			Link.l1.go = "Exit";
			
			AddQuestRecord("ShipTuning", "End");
			CloseQuestHeader("ShipTuning");
			notification("Sokat tanultál a hajó szerkezetérôl!", "none");
			AddCharacterExpToSkill(pchar, SKILL_ACCURACY, 5.0 * makefloat(GetMaterialQtyUpgrade(pchar, NPChar, 2 )));
			AddCharacterExpToSkill(pchar, SKILL_CANNONS, 5.0 * makefloat(GetMaterialQtyUpgrade(pchar, NPChar, 2 )));
		break;
		
		case "Tasks":
			//--> Jason генератор Поиск корабля
			if (hrand(4) == 2 && !CheckAttribute(pchar, "GenQuest.Findship.Shipyarder") && sti(pchar.rank) < 19)
			{
				if (!CheckAttribute(npchar, "Findship") || GetNpcQuestPastDayParam(npchar, "Findship") >= 60) 
				{
					SelectFindship_ShipType(); //выбор типа корабля
					pchar.GenQuest.Findship.Shipyarder.ShipBaseName =  GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Findship.Shipyarder.ShipType), "Name") + "Acc")); // new
					pchar.GenQuest.Findship.Shipyarder.City = npchar.city; //город квестодателя
					dialog.text = "Van egy megoldásra váró problémám. Van egy megrendelésem egy hajóra - "+pchar.GenQuest.Findship.Shipyarder.ShipBaseName+". Azonban a hajógyáramban most nincs ilyen hajó, és két hónapon belül sincs lehetôségem beszerezni egyet.\nHa tudtok adni nekem egy ilyen hajót - nagyon hálás leszek, és kifizetem az eladási ár másfélszeresét.";
					link.l1 = "Érdekes ajánlat. Egyetértek!";
					link.l1.go = "Findship";
					link.l2 = "Ez engem nem érdekel.";
					link.l2.go = "Findship_exit";
					SaveCurrentNpcQuestDateParam(npchar, "Findship");
					break;
				}
				
			}//<-- генератор Поиск корабля
			//Jason --> генератор Неудачливый вор
			if (hrand(6) == 1 && !CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && sti(pchar.rank) < 10 && npchar.city != "Charles")
			{
				if (!CheckAttribute(npchar, "Device")) 
				{
					switch (hrand(4))
					{
						case 0:  
							pchar.GenQuest.Device.Shipyarder.Type = "belsô mérômûszer";
							pchar.GenQuest.Device.Shipyarder.Describe = "two hammered strips, connected with a joint unriveted on both ends";
						break; 
						case 1:  
							pchar.GenQuest.Device.Shipyarder.Type = "Svéd széles fejsze";
							pchar.GenQuest.Device.Shipyarder.Describe = "an axe on a long straight handle with a thin semicircular blade";
						break; 
						case 2:  
							pchar.GenQuest.Device.Shipyarder.Type = "groover";
							pchar.GenQuest.Device.Shipyarder.Describe = "a small axe, looking like a farmer's mattock";
						break; 
						case 3:  
							pchar.GenQuest.Device.Shipyarder.Type = "raktárszint";
							pchar.GenQuest.Device.Shipyarder.Describe = "two wooden bars of equal length, linked by the same third one, which has in the middle a rotating liquid-filled plate with an air bubble";
						break;
						case 4:  
							pchar.GenQuest.Device.Shipyarder.Type = "barsik";
							pchar.GenQuest.Device.Shipyarder.Describe = "an ordinary flail, but the chain is rod-shaped and only moves in one direction";
						break; 
					}
					dialog.text = "Épp idôben érkeztél. Talán tudna segíteni nekem. Éppen tegnap valaki ellopott tôlem egy nagyon értékes eszközt - "+pchar.GenQuest.Device.Shipyarder.Type+". Nincs lehetôségem egy másikat készíteni, és nem engedhetem meg magamnak az idôt és a költségeket, hogy Európából rendeljek. És nélküle nem tudok normálisan hajókat építeni, tudod?\nA legbosszantóbb pedig az, hogy erre a dologra senkinek sincs szüksége, csak a hajóépítôknek, és én vagyok az egyetlen hajóépítô a kolónián. Ez a tolvaj nem fogja eladni senkinek, és csak úgy kidobja. Talán megpróbálod felkutatni a tolvajt, kérdezôsködni a városban, de nekem egyszerûen nincs idôm távol lenni a hajógyártól - sürgôsen speciális megrendeléseket kell teljesítenem.";
					link.l1 = "Rendben, akkor megpróbálom. Mondd csak, hogy nézett ki az a... szerkezeted?";
					link.l1.go = "Device";
					link.l2 = "Ez engem nem érdekel.";
					link.l2.go = "Device_exit";
					SaveCurrentNpcQuestDateParam(npchar, "Device");
					break;
				}//<-- генератор Неудачливый вор
			}
			dialog.text = "Nekem nincs semmi ilyesmim.";
			link.l1 = "Ahogy mondja.";
			link.l1.go = "exit";
		break;
		
		case "Findship_exit":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Findship.Shipyarder");
		break;
		
		case "Device_exit":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Device.Shipyarder");
		break;
		
		//--> Jason генератор Поиск корабля
		case "Findship":
			pchar.GenQuest.Findship.Shipyarder = "begin";
			pchar.GenQuest.Findship.Shipyarder.Name = GetFullName(npchar);
			pchar.GenQuest.Findship.Shipyarder.City = npchar.city;
			ReOpenQuestHeader("Findship");
			AddQuestRecord("Findship", "1");
			AddQuestUserData("Findship", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Findship.Shipyarder.City+"Gen"));
			AddQuestUserData("Findship", "sName", pchar.GenQuest.Findship.Shipyarder.Name);
			AddQuestUserData("Findship", "sShip", pchar.GenQuest.Findship.Shipyarder.ShipBaseName);
			SetFunctionTimerCondition("Findship_Over", 0, 0, 60, false);
			DialogExit();
		break;
		
		case "Findship_check":
			dialog.text = "Kitûnô! Nagyon örülök, hogy ilyen gyorsan sikerült. Hol van az a hajó?";
			link.l1 = "Jelenleg a hajó a kikötôben van; a neve '"+pchar.GenQuest.Findship.Shipyarder.ShipName+"'.";
				link.l1.go = "Findship_complete";
				break;
		
		case "Findship_complete":
			pchar.quest.Findship_Over.over = "yes";//снять прерывание
			sld = GetCharacter(sti(pchar.GenQuest.Findship.Shipyarder.CompanionIndex));
			RemoveCharacterCompanion(PChar, sld);
			AddPassenger(PChar, sld, false);
			dialog.text = "Itt a pénzed - "+FindRussianMoneyString(sti(pchar.GenQuest.Findship.Shipyarder.Money))+". Köszönöm a munkát. Ne felejtsen el újra felkeresni. Viszontlátásra!";
			link.l1 = "Viszlát, " + npchar.name + ".";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Findship.Shipyarder.Money));
			AddQuestRecord("Findship", "3");
			AddQuestUserData("Findship", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Findship.Shipyarder.Money)));
			CloseQuestHeader("Findship");
			DeleteAttribute(pchar, "GenQuest.Findship.Shipyarder");
		break;
		//<-- генератор Поиск корабля
		
		//Jason --> генератор Неудачливый вор
		case "Device":
			pchar.GenQuest.Device.Shipyarder.Chance1 = rand(6);
			pchar.GenQuest.Device.Shipyarder.Chance2 = rand(3);
			pchar.GenQuest.Device.Shipyarder.Chance3 = rand(2);
			pchar.GenQuest.Device.Shipyarder.Chance4 = rand(4);
			pchar.GenQuest.Device.Shipyarder.Money = 12000+rand(8000);
			//генерируем тип корабля для бонуса сейчас, чтобы не сливали
			if (sti(pchar.rank) < 5) iType = sti(RandPhraseSimple(its(SHIP_BARKENTINE), its(SHIP_SLOOP)));
			if (sti(pchar.rank) >= 5 && sti(pchar.rank) < 11) iType = sti(RandPhraseSimple(its(SHIP_SHNYAVA), its(SHIP_BARQUE)));
			if (sti(pchar.rank) >= 11 && sti(pchar.rank) < 16) iType = sti(RandPhraseSimple(its(SHIP_BRIG), its(SHIP_FLEUT)));
			if (sti(pchar.rank) >= 16) iType = sti(LinkRandPhrase(its(SHIP_CORVETTE), its(SHIP_POLACRE), its(SHIP_GALEON_L)));
			pchar.GenQuest.Device.Shipyarder.Bonus = iType;
			dialog.text = "Természetesen megpróbálom egyszerû szavakkal elmagyarázni. Úgy néz ki, mint "+pchar.GenQuest.Device.Shipyarder.Describe+". Egyedi a maga nemében, így nagyon könnyen felismerhetô. Ha elhozza nekem ezt a hangszert, busásan megfizetem.";
			link.l1 = "Megvan. Azonnal elkezdem a keresést!";
			link.l1.go = "exit";
			pchar.GenQuest.Device.Shipyarder = "begin";
			pchar.GenQuest.Device.Shipyarder.Name = GetFullName(npchar);
			pchar.GenQuest.Device.Shipyarder.City = npchar.city;
			pchar.GenQuest.Device.Shipyarder.Nation = npchar.Nation;
			ReOpenQuestHeader("Device");
			AddQuestRecord("Device", "1");
			AddQuestUserData("Device", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Device.Shipyarder.City+"Voc"));
			AddQuestUserData("Device", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Device", "sName", pchar.GenQuest.Device.Shipyarder.Type);
			AddQuestUserData("Device", "sDesc", pchar.GenQuest.Device.Shipyarder.Describe);
			SetFunctionTimerCondition("Device_Over", 0, 0, 30, false);
		break;
		
		case "Device_complete":
			pchar.quest.Device_Over.over = "yes";//снять прерывание
			dialog.text = "Megcsináltad! Fogalma sincs, mennyire hálás vagyok! Már minden reményemet elvesztettem, hogy újra láthatom a hangszeremet.";
			link.l1 = "Tessék, tessék.";
			link.l1.go = "Device_complete_1";
		break;
		
		case "Device_complete_1":
			RemoveItems(PChar, "Tool", 1);
			dialog.text = "Az erôfeszítéseidért fizetni fogok neked "+FindRussianMoneyString(sti(pchar.GenQuest.Device.Shipyarder.Money))+". Remélem, hogy ez egy méltó jutalom lenne.";
			link.l1 = "Köszönjük!";
			link.l1.go = "Device_complete_2";
		break;
		
		case "Device_complete_2":
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Device.Shipyarder.Money));
			ChangeCharacterComplexReputation(pchar,"nobility", 5); 
			AddCharacterExpToSkill(pchar, "Leadership", 100);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 100);//скрытность
			AddQuestRecord("Device", "10");
			AddQuestUserData("Device", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Device.Shipyarder.Money)));
			CloseQuestHeader("Device");
			if (sti(pchar.GenQuest.Device.Shipyarder.Chance4) == 3)
			{
				dialog.text = "Emellett szeretnék egy ajánlatot tenni, további hálám jeléül.";
				link.l1 = "Ez érdekes. Nos, csak rajta - szeretem a kellemes meglepetéseket.";
				link.l1.go = "Device_complete_3";
			}
			else
			{
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Device.Shipyarder");
			}
		break;
		
		case "Device_complete_3":
			iType = sti(pchar.GenQuest.Device.Shipyarder.Bonus);
			dialog.text = "Most indítottam egy új hajót - "+ GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(iType, "Név") + "Acc")) +". Erre a hajóra már több vevô is van, de neked adok elsôbbséget. Ha tetszik ez a hajó, és nem ijedsz meg az árától - megveheted.";
			link.l1 = "Heh! Persze, nézzük meg!";
			link.l1.go = "Device_complete_4";
			link.l2 = "Köszönöm, de a jelenlegi hajóm tökéletesen megfelel nekem, és nem akarom lecserélni.";
			link.l2.go = "Device_complete_5";
		break;
		
		case "Device_complete_4":
			iType = sti(pchar.GenQuest.Device.Shipyarder.Bonus);
			FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_TARTANE, NPChar), "ship1");
			FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_LUGGER, NPChar), "ship2");
			FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_LUGGER, NPChar), "ship3");
			FillShipParamShipyard(NPChar, GenerateStoreShipExt(iType, NPChar), "ship10");
			DialogExit();
			LaunchShipyard(npchar);
			DeleteAttribute(pchar, "GenQuest.Device.Shipyarder");
			SaveCurrentNpcQuestDateParam(npchar, "shipyardDate"); // лесник , митрокоста		   
		break;
		
		case "Device_complete_5":
			dialog.text = "Nos, ahogy óhajtja. Még egyszer köszönöm - és sok szerencsét!";
			link.l1 = "Neked is sok szerencsét!";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "GenQuest.Device.Shipyarder");
		break;
		// <-- генератор Неудачливый вор
		
		case "ShipLetters_6":
			pchar.questTemp.different.GiveShipLetters.speakShipyard = true;
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 0)
			{
				dialog.text = "Hadd nézzem meg... Nem, nem volt senki hozzá hasonló. Azt hiszem, ezzel kapcsolatban a kikötômesterhez kellene fordulnia.";
				link.l1 = "Persze...";
				link.l1.go = "exit";
			}
			else
			{
				sTemp = "Hadd nézzem meg, kapitány! A-ha! Ezek egy jó barátom, a kedvenc vásárlóm hajójának papírjai! Biztos vagyok benne, hogy rendkívül boldog lesz a leleted miatt, és megérdemelten megjutalmaz téged.";
				sTemp = sTemp + "I guess I can offer you " + sti(pchar.questTemp.different.GiveShipLetters.price2) + " pesos on his behalf";
				dialog.text = sTemp;
				link.l1	= "Nem, nem hiszem...";
				link.l1.go = "exit";
				link.l2 = "Köszönöm, " + GetFullName(NPChar) + "! Kérem, adja át üdvözletemet a barátjának.";
				link.l2.go = "ShipLetters_7";				
			}	
		break;

		case "ShipLetters_7":
			TakeItemFromCharacter(pchar, "CaptainBook"); 
			addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price2)); 
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //снимаем таймер 
			AddQuestRecord("GiveShipLetters", "4");		
			AddQuestUserData("GiveShipLetters", "sSex", GetSexPhrase("",""));		
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters"); 		
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "EncGirl_1":
			dialog.text = "Figyelmesen hallgatlak.";
			link.l1 = "Elhoztam a szökevényt.";
			link.l1.go = "EncGirl_2";
		break;
		
		case "EncGirl_2":
			dialog.text = "Ó, Kapitány, nagyon köszönöm! Hogy van? Megsérült? Miért szökött el? Miért?\nHát nem érti? A vôlegény egy gazdag és fontos ember! A fiatalság naiv és ostoba... sôt kegyetlen. Ezt ne feledje!";
			link.l1 = "Nos, te vagy az apja, és a végsô döntés a tiéd, de én nem sietnék az esküvôvel...";
			link.l1.go = "EncGirl_3";
		break;
		
		case "EncGirl_3":
			dialog.text = "Mit tudsz te? Vannak saját gyermekei? Nincsenek? Ha lesz egy, jöjjön el hozzám, és beszélgetünk.\njutalmat ígértem annak, aki visszaviszi a családjához.";
			link.l1 = "Köszönöm. Köszönöm. Tartsd rajta a szemed. Van egy olyan érzésem, hogy nem fog leállni.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("EncGirl_ToLoverParentsExit");
		break;		
		
		case "EncGirl_4":
			if(sti(pchar.GenQuest.EncGirl.LoverFatherAngry) == 0)
			{
				dialog.text = "Ó, szóval te vagy az a kapitány, aki a tékozló fiamnak fiatal menyasszonyt hozott?";
				link.l1 = "Igen, én voltam.";
				link.l1.go = "EncGirl_5";
			}
			else
			{
				dialog.text = "Ó, ott "+ GetSexPhrase("ô, a mi jótevônk","ô, a mi jótevônk") +". Jutalomra számítasz, ugye?";
				link.l1 = "Nos, én jól megvagyok jutalom nélkül is, a jó szavad is megteszi.";
				link.l1.go = "EncGirl_6";			
			}
		break;
		
		case "EncGirl_5":
			dialog.text = "Nagyon hálás vagyok neked, hogy nem hagytad magára a gyermekemet a legnagyobb bajban, és segítettél neki, hogy kiutat találjon egy kényes helyzetbôl. Engedje meg, hogy megköszönjem, és kérem, fogadja el ezt a szerény összeget és a személyes ajándékomat.";
			link.l1 = "Köszönöm. Örömömre szolgált, hogy segíthettem ennek a fiatal párnak.";
			link.l1.go = "EncGirl_5_1";
		break;
		
		case "EncGirl_6":
			dialog.text = "Köszönöm. Milyen köszönet?! Már fél éve, hogy az a tökfej munka nélkül lóg - és nézzenek oda, van ideje szerelmi ügyekre is! Amikor én annyi idôs voltam, mint ô, már a saját vállalkozásomat vezettem! Pff! Egy kormányzónak van egy házasulandó lánya - és ez a tökfilkó egy rokonok nélküli ribancot hozott a házamba, és még az áldásomat is kérni merte!";
			link.l1 = "Hmm... Úgy tûnik, nem hiszel az ôszinte érzésekben?";
			link.l1.go = "EncGirl_6_1";		
		break;
		
		case "EncGirl_5_1":
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.EncGirl.sum));
			GiveItem2Character(pchar, pchar.GenQuest.EncGirl.item);
			AddQuestRecord("JungleGirl", "18");
			CloseQuestHeader("JungleGirl");
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "EncGirl_6_1":
			dialog.text = "Milyen érzésekben? Miféle érzésekrôl beszélsz? Érzelmek... hogy lehet valaki ennyire könnyelmû a te korodban?! Szégyelld magad, hogy engedsz a fiatalok szeszélyeinek, és kerítônôként viselkedsz! Nemcsak egy lányt vettél el az otthonától, hanem tönkretetted a zöldfülû életemet is. Nem lesz köszönet neked. Búcsúzzatok el!";
			link.l1 = "Rendben, és minden jót neked is...";
			link.l1.go = "EncGirl_6_2";
		break;
		
		case "EncGirl_6_2":
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			AddQuestRecord("JungleGirl", "19");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl", "sSex1", GetSexPhrase("",""));
			CloseQuestHeader("JungleGirl");
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();		
		break;
		
		case "shipyard":
			if(CheckAttribute(npchar, "TrialDelQuestMark"))
			{
				DeleteAttribute(npchar, "TrialDelQuestMark");
				DelLandQuestMark(npchar);
				DelMapQuestMarkCity("PortRoyal");
			}
            ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		    if (sti(Pchar.Ship.Type) == SHIP_NOTUSED || ok)
			{
			    NextDiag.CurrentNode = NextDiag.TempNode;
				DialogExit();
				LaunchShipyard(npchar);
			}
			else
			{
			    dialog.text = NPCharRepPhrase(npchar, pcharrepphrase("Most viccelsz velem? Hol van a hajód? Nem látom a kikötôben!",
				                                                     "Az ördögre esküszöm, nem fogsz átverni! A hajója nincs a kikötôben!"),
													  pcharrepphrase("Nem látom a hajóját a kikötôben, kapitány " +GetFullName(pchar)+ ". Nagyon remélem, hogy nem a 'repülô holland'?",
													                 "kapitány, sokkal egyszerûbb a mólóról felrakodni a rakományt. Vigye a hajóját a kikötôbe, és jöjjön vissza."));
				link.l1 = NPCharRepPhrase(npchar, pcharrepphrase("" +RandSwear()+"Micsoda baj! Jól van, öreg ravasz, hamarosan találkozunk!",
				                                                 "Nem akartalak becsapni, " +GetFullName(npchar)+ ", egy hajó a sziget túloldalán."),
												  pcharrepphrase("Nem. A hajómat a 'Fekete Gyöngynek'! hívják. Mi történt az arcoddal? Sápadt... Haha! Vicc volt!",
												                 "Köszi a tanácsot, biztosan megcsinálom."));
			    link.l1.go = "exit";
			}
		break;
		
		case "Cannons":
            ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		    if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
			    NextDiag.CurrentNode = NextDiag.TempNode;
				DialogExit();
    			LaunchCannons(sti(rColony.StoreNum));
			}
			else
			{
			    dialog.text = NPCharRepPhrase(npchar, pcharrepphrase("Most viccelsz velem? Hol van a hajód? Nem látom a kikötôben!",
				                                                     "Az ördögre esküszöm, nem fogsz átverni! A hajója nincs a kikötôben!"),
													  pcharrepphrase("Nem látom a hajóját a kikötôben, kapitány " +GetFullName(pchar)+ ". Nagyon remélem, hogy nem a 'repülô holland'?",
													                 "kapitány, sokkal egyszerûbb a mólóról felrakodni a rakományt. Vigye a hajóját a kikötôbe, és jöjjön vissza."));
				link.l1 = NPCharRepPhrase(npchar, pcharrepphrase("" +RandSwear()+"Micsoda baj! Jól van, öreg ravasz, hamarosan találkozunk!",
				                                                 "Nem akartalak becsapni, " +GetFullName(npchar)+ ", egy hajó a sziget túloldalán."),
												  pcharrepphrase("Nem. A hajómat a 'Fekete Gyöngynek'! hívják. Mi történt az arcoddal? Sápadt... Haha! Vicc volt!",
												                 "Köszi a tanácsot, biztosan megcsinálom."));
			    link.l1.go = "exit";
			}
		break;
		
		case "SailsGerald":
            ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		    if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
			    dialog.text = "A vitorlák színének megváltoztatása " +
				              FindRussianMoneyString(GetSailsTuningPrice(Pchar, npchar, SAILSCOLOR_PRICE_RATE))+
							  ", a címer megváltoztatása " +
							  FindRussianMoneyString(GetSailsTuningPrice(Pchar, npchar, SAILSGERALD_PRICE_RATE)) +
							  ", a vitorlák cseréje - a hajótól függ.";
							  
			    link.l1 = "Válassz egy új színt.";
			    link.l1.go = "SailsColorChoose";
			    link.l2 = "Új címer ábrázolása.";
			    link.l2.go = "SailsGeraldChoose";
				link.l3 = "Telepíts egyedi vitorlákat."; 
				link.l3.go = "SailsTypeChoose";
			    Link.l9 = "Meggondoltam magam.";
				Link.l9.go = "exit";
			}
			else
			{
			    dialog.text = NPCharRepPhrase(npchar, pcharrepphrase("Most viccelsz velem? Hol van a hajód? Nem látom a kikötôben!","Az ördögre esküszöm, nem fogsz átverni! A hajója nincs a kikötôben!"),pcharrepphrase("Nem látom a hajóját a kikötôben, kapitány " +GetFullName(pchar)+ ". Nagyon remélem, hogy nem a 'repülô holland'?","kapitány, sokkal egyszerûbb a mólóról felrakodni a rakományt. Vigye a hajóját a kikötôbe, és jöjjön vissza."));
				link.l1 = NPCharRepPhrase(npchar, pcharrepphrase("" +RandSwear()+"Micsoda baj! Jól van, öreg ravasz, hamarosan találkozunk!","Nem akartalak becsapni, " +GetFullName(npchar)+ ", egy hajó a sziget túloldalán."), pcharrepphrase("Nem. A hajómat a 'Fekete Gyöngynek'! hívják. Mi történt az arcoddal? Sápadt... Haha! Vicc volt!","Köszi a tanácsot, biztosan megcsinálom."));
			    link.l1.go = "exit";
			}
		break;
		
		case "SailsTypeChoose":
			dialog.text = "Milyen vitorlákat szeretne felszerelni? Jelenleg a " + GetSailsType(sti(RealShips[sti(Pchar.Ship.Type)].ship.upgrades.sails))+".";
            Link.l6 = "Szeretném telepíteni "+GetSailsType(6) + ".";
			Link.l6.go = "SailsTypeChooseIDX_6";
			Link.l7 = "Szeretném telepíteni "+GetSailsType(7)  + ".";
			Link.l7.go = "SailsTypeChooseIDX_7";
			Link.l8 = "Szeretném telepíteni "+GetSailsType(8)  + ".";
			Link.l8.go = "SailsTypeChooseIDX_8";
			Link.l9 = "Szeretném telepíteni "+GetSailsType(9)  + ".";
			Link.l9.go = "SailsTypeChooseIDX_9";
			Link.l10 = "Szeretném telepíteni "+GetSailsType(10)  + ".";
			Link.l10.go = "SailsTypeChooseIDX_10";
			Link.l11 = "Szeretném telepíteni "+GetSailsType(11)  + ".";
			Link.l11.go = "SailsTypeChooseIDX_11";
			attrLoc = "l" + sti(RealShips[sti(Pchar.Ship.Type)].ship.upgrades.sails);
			DeleteAttribute(Link, attrLoc);
		    Link.l99 = "Meggondoltam magam.";
			Link.l99.go = "exit";
		break;
		
		case "SailsTypeChoose2":
            NPChar.SailsTypeMoney = GetSailsTypePrice(sti(RealShips[sti(Pchar.Ship.Type)].ship.upgrades.sails),
			                                          sti(NPChar.SailsTypeChooseIDX),
													  stf(NPChar.ShipCostRate),
													  sti(RealShips[sti(Pchar.Ship.Type)].Price));
													  
			dialog.text = "Jelenleg a "+GetSailsType(sti(RealShips[sti(Pchar.Ship.Type)].ship.upgrades.sails))+", a "+ GetSailsType(sti(NPChar.SailsTypeChooseIDX))+"van kiválasztva. A csere költsége "+ FindRussianMoneyString(sti(NPChar.SailsTypeMoney)) +". Folytassa?";

			if (sti(NPChar.SailsTypeMoney) <= sti(Pchar.Money))
			{
	            Link.l1 = "Igen.";
				Link.l1.go = "SailsTypeChooseDone";
			}
		    Link.l99 = "Nem.";
			Link.l99.go = "exit";
		break;
		
		case "SailsTypeChooseDone":
			AddMoneyToCharacter(Pchar, -sti(NPChar.SailsTypeMoney));
			dialog.text = "Kiváló! Minden rendben lesz.";
		    Link.l9 = "Köszönjük!";
			Link.l9.go = "exit";

			RealShips[sti(Pchar.Ship.Type)].ship.upgrades.sails = sti(NPChar.SailsTypeChooseIDX);
			WaitDate("",0,0,0, 1, 30);
		break;
		
		case "SailsColorChoose":
			if (GetSailsTuningPrice(Pchar, npchar, SAILSCOLOR_PRICE_RATE) <= sti(Pchar.Money))
			{
				dialog.text = "Milyen színt válasszunk? Az ár " + FindRussianMoneyString(GetSailsTuningPrice(Pchar, npchar, SAILSCOLOR_PRICE_RATE)) + ".";
				for (i = 0; i < SAILS_COLOR_QUANTITY; i++)
				{
					if (CheckSailsColor(Pchar, i))
					{
						attrLoc = "l" + i;
						Link.(attrLoc) = XI_ConvertString(SailsColors[i].name);
						Link.(attrLoc).go = "SailsColorIdx_" + i;
					}
				}
			    Link.l99 = "Meggondoltam magam.";
				Link.l99.go = "exit";
			}
			else
			{
				dialog.text = "Jöjjön, ha lesz pénze.";
			    Link.l9 = "Rendben.";
				Link.l9.go = "exit";	
			}
		break;
		
		case "SailsColorDone":
			AddMoneyToCharacter(Pchar, -GetSailsTuningPrice(Pchar, npchar, SAILSCOLOR_PRICE_RATE));
			dialog.text = "Egyetértek. A vitorlákat "+ GetStrSmallRegister(XI_ConvertString(SailsColors[sti(NPChar.SailsColorIdx)].name)) +" színûre festjük.";
		    Link.l9 = "Köszönjük!";
			Link.l9.go = "exit";
			
			SetSailsColor(Pchar, sti(NPChar.SailsColorIdx));
			WaitDate("",0,0,0, 1, 30);
		break;
		
		case "SailsGeraldChoose":
			if(GetSailsTuningPrice(Pchar, npchar, SAILSGERALD_PRICE_RATE) <= sti(Pchar.Money))
			{
				if(CheckSailsGerald(Pchar) && CanSetSailsGerald(PChar)) // Warship fix 04.06.09
				{
					NextDiag.CurrentNode = NextDiag.TempNode;
					DialogExit();
					LaunchSailsGeraldScreen(npchar);
				}
				else
				{
				    dialog.text = "Sajnos, a hajójukon nem lehet címer.";
				    Link.l9 = "Kár.";
					Link.l9.go = "exit";
				}
			}
			else
			{
				dialog.text = "Jöjjön vissza, ha megvan a pénz.";
			    Link.l9 = "Rendben.";
				Link.l9.go = "exit";	
			}
		break;

//--> -------------------------------------------Бремя гасконца---------------------------------------------------
		case "Sharlie":
			dialog.text = "Sajnálom, hogy csalódást kell okoznom, Monsieur, de jelenleg nincsenek eladó hajóim.";
			link.l1 = "Ez nagyon furcsa, 'mert nekem azt mondták, hogy van egy vadonatúj lugger a hajógyárukban.";
			link.l1.go = "Sharlie_1";
		break;
		
		case "Sharlie_1":
			if (GetQuestPastDayParam("questTemp.Sharlie_ship") > 3)
			{
				dialog.text = "Tudod, hogy valószínûleg a luggerrôl van szó, amelyért Michel de Monper háromezer pezó óvadékot fizetett? Tehát ez a hajó már el van adva, mert a szerzôdés szerint a teljes összeget legkésôbb egy héttel a hajó vízre szállása után kellett volna kifizetni.\nMinden határidô lejárt, és nem kaptam meg a pénzt, így a lugger el lett adva. Nagyon sajnálom, uram.";
				link.l1 = "Igen, ez valóban elég szerencsétlen volt... De biztos, hogy nincs más eladó hajója?";
				link.l1.go = "Sharlie_6";
			}
			else
			{
			dialog.text = "Hmm. Igen, valóban. De...";
			link.l1 = "És már van rá foglaló - ötezer pezó. Michel de Monper, aki letétbe helyezte a pénzt, minden jogot megadott nekem erre a hajóra.";
			link.l1.go = "Sharlie_2";
			}
		break;
		
		case "Sharlie_2":
			int iDay = 3-sti(GetQuestPastDayParam("questTemp.Sharlie_ship"));
			sTemp = "Csak annyit kell tennie. "+FindRussianDaysString(iDay)+"";
			if (iDay == 0) sTemp = "Ma van az utolsó nap.";
			dialog.text = "Nos, ha már így alakult, akkor folytassuk a beszélgetésünket, uram. Ahogy helyesen rámutatott, megvan az ötezer pezó foglaló a hajóra. De a hajó teljes értéke szerintem tizenötezer pezó, a lôszerrel együtt. Tehát fizessen nekem tízezret, és a hajó az öné.\nA szerzôdés szerint a pénzt legkésôbb egy héttel a hajó vízre szállása után kell kifizetnie. "+sTemp+", és utána szabadon eladhatom a hajót egy másik vevônek. És ne feledje, már van is egy, úgyhogy jobb, ha siet.";
			if (sti(Pchar.money) >= 10000)
			{
				link.l1 = "Nem kell sietni. A szükséges összeg már most is nálam van. Tessék, tessék.";
				link.l1.go = "Sharlie_4";
			}
			link.l2 = "Rendben, rendben. Megkapja a pénzét, uram. Nem fog sokáig várakoztatni.";
			link.l2.go = "exit";
			NextDiag.TempNode = "Sharlie_3";
		break;
		
		case "Sharlie_3":
			if (CheckAttribute(pchar, "questTemp.Sharlie.Rum") || CheckAttribute(pchar, "questTemp.Sharlie.Gigolo") || CheckAttribute(pchar, "questTemp.Sharlie.RescueDaughter"))
			{
				dialog.text = "Segíthetek, uram?";
				Link.l1 = "Csak beugrottam, hogy megnézzem, milyen hajóik vannak... De most egy kicsit elfoglalt vagyok - van egy befejezetlen ügyem, amit el kell intéznem. Amint végeztem vele, visszatérek.";
				Link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.Sharlie == "ship" || pchar.questTemp.Sharlie == "ship_fast") // Addon 2016-1 Jason пиратская линейка 1
			{	
				if (GetQuestPastDayParam("questTemp.Sharlie_ship") > 3)
				{
					dialog.text = "Monsieur, figyelmeztettem, hogy csak három nap áll a rendelkezésére. Ezek lejártak, és ön még mindig nem hozott nekem pénzt, így az üzletünk lejárt, és én eladtam a hajót egy másik vevônek. Ne vegye sértésnek.";
					link.l1 = "Igen, ez valóban elég szerencsétlen volt... De biztos, hogy nincs más eladó hajója?";
					link.l1.go = "Sharlie_6";
				}
				else
				{
					dialog.text = "Hozott nekem tízezret, uram?";
					if (sti(Pchar.money) >= 10000)
					{
						link.l1 = "Persze, hogy hoztam. Tessék, tessék.";
						link.l1.go = "Sharlie_4";
					}
					link.l2 = "Nem, még dolgozom rajta.";
					link.l2.go = "exit";
					NextDiag.TempNode = "Sharlie_3";
				}
			}
		break;
		
		case "Sharlie_4":
			AddMoneyToCharacter(pchar, -10000);
			DelLandQuestMark(npchar);
			QuestPointerDelLoc("fortfrance_town", "reload", "reload5_back");
			dialog.text = "Akkor engedje meg, hogy gratuláljak a sikeres vásárláshoz. A hajó az öné. Remélem, jó szolgálatot tesz majd.";
			link.l1 = "Köszönjük!";
			link.l1.go = "Sharlie_5";
		break;
		
		case "Sharlie_5":
			NextDiag.CurrentNode = "First time";
			DialogExit();
			pchar.questTemp.Sharlie.Ship = "lugger";
			pchar.questTemp.Sharlie = "crew";
			//стартовый люггер
			pchar.Ship.Type = GenerateShipHand(pchar, SHIP_LUGGER, 6, 800, 40, 610, 16000, 15.2, 58.8, 1.42);
			SetMaxShipStats(pchar);
			SetBaseShipData(pchar);
			ResetShipCannonsDamages(pchar);
			SetShipCannonsDamagesNull(pchar);
			NullCharacterGoods(pchar);
			SetCrewQuantityOverMax(PChar, 0);
			/* UpgradeShipParameter(pchar, "SpeedRate");
			UpgradeShipParameter(pchar, "TurnRate");
			UpgradeShipParameter(pchar, "WindAgainstSpeed");
			UpgradeShipParameter(pchar, "HP");
			UpgradeShipParameter(pchar, "MaxCrew");
			UpgradeShipParameter(pchar, "Capacity");
			//UpgradeShipParameter(pchar, "Cannons");
			pchar.ship.HP = 732; */
			//UpgradeShipFull(pchar);
			UpgradeShipParameter(pchar, "Capacity");
			RealShips[sti(pchar.Ship.Type)].ship.upgrades.hull  = "q"; // belamour особый скин
			AddLandQuestMark(characterFromId("FortFrance_tavernkeeper"), "questmarkmain");
			AddCharacterGoods(pchar, GOOD_BALLS, 100);
			AddCharacterGoods(pchar, GOOD_GRAPES, 100);
			AddCharacterGoods(pchar, GOOD_KNIPPELS, 100);
			AddCharacterGoods(pchar, GOOD_BOMBS, 100);
			AddCharacterGoods(pchar, GOOD_POWDER, 220);
			pchar.Ship.name = "Adeline";
			pchar.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS6;
			AddQuestRecord("Sharlie", "6");
			bDisableFastReload = false;//открыть переход
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			if (GetCharacterIndex("GigoloMan") != -1)
			{
				sld = characterFromId("GigoloMan");
				sld.lifeday = 0;
			}
			pchar.GenQuest.StoreGoods.StoreIdx = Fortfrance_STORE;
			pchar.GenQuest.StoreGoods.Starting = true; // заполняем магазин
			bNoEatNoRats  = true; // отменяем еду и крыс
			GiveItem2Character(pchar, "map_normal");
		break;
		
		case "Sharlie_6":
			if (sti(Pchar.money) >= 15000)
				{
					dialog.text = "Hmm... Nos, igazából van egy, de nem vagyok benne biztos, hogy megfelelne neked.";
					link.l1 = "Nos, nem engedhetem meg magamnak, hogy túl válogatós legyek. Mutasd meg, mid van!";
					link.l1.go = "Sharlie_7";
				}
				else
				{
					dialog.text = "Figyeljen, Monsieur, elôször csináljon egy halom pénzt, aztán kérdezzen a hajókról, rendben? Itt senki sem ad semmit ingyen. Világosan fejeztem ki magam?";
					link.l1 = "Teljesen világosan, bár nem volt szükség a gorombaságra. Rendben, majd visszajövök, ha megvan a pénz.";
					link.l1.go = "exit";
					NextDiag.TempNode = "Sharlie_shipwait";
				}
		break;
		
		case "Sharlie_7":
			dialog.text = "Akkor nézd. Nemrég vettem egy sloopot elfogadható áron. Ez egy korábbi kalózhajó volt, korábbi tulajdonosai már biztonságban vannak, számos bûncselekmény miatt. A hajó ôszintén szólva nem olyan jó, mint egy lugger, és súlyos sérülésekkel is rendelkezik, de még mindig ki tud menni a tengerre.\nNincs most idôm megjavítani - minden emberem egy megrendelt brigg építésével van elfoglalva, így ugyanolyan állapotban veheted meg tôlem, amilyenben van. Ezt figyelembe véve a szokásosnál olcsóbban adom el, miközben a raktér tartalmát is beleszámítom - tizenötezer pezó.";
			link.l1 = "Megegyeztünk. Hajózható, és csak ez számít. Guadeloupe karnyújtásnyira van - ott megjavíttatom, ha nincs ilyen lehetôsége.";
			link.l1.go = "Sharlie_8";
		break;
		
		case "Sharlie_8":
			AddMoneyToCharacter(pchar, -15000);
			DelLandQuestMark(npchar);
			QuestPointerDelLoc("fortfrance_town", "reload", "reload5_back");
			dialog.text = "Akkor engedje meg, hogy gratuláljak a sikeres vásárláshoz. A hajó az öné. Remélem, jó szolgálatot tesz majd.";
			link.l1 = "Köszönjük!";
			link.l1.go = "Sharlie_9";
		break;
		
		case "Sharlie_9":
			NextDiag.CurrentNode = "First time";
			DialogExit();
			pchar.questTemp.Sharlie.Ship = "sloop";
			pchar.questTemp.Sharlie = "crew";
			//стартовый шлюп
			pchar.Ship.Type = GenerateShipExt(SHIP_SLOOP, true, pchar);
			SetMaxShipStats(pchar);
			SetBaseShipData(pchar);
			ResetShipCannonsDamages(pchar);
			SetShipCannonsDamagesNull(pchar);
			NullCharacterGoods(pchar);
			SetCrewQuantityOverMax(PChar, 0);
			/* UpgradeShipParameter(pchar, "SpeedRate");
			UpgradeShipParameter(pchar, "TurnRate");
			UpgradeShipParameter(pchar, "WindAgainstSpeed");
			UpgradeShipParameter(pchar, "HP");
			UpgradeShipParameter(pchar, "MaxCrew"); */
			UpgradeShipParameter(pchar, "Capacity");
			AddCharacterGoods(pchar, GOOD_BALLS, 51);
			AddCharacterGoods(pchar, GOOD_GRAPES, 39);
			AddCharacterGoods(pchar, GOOD_KNIPPELS, 54);
			AddCharacterGoods(pchar, GOOD_BOMBS, 36);
			AddCharacterGoods(pchar, GOOD_POWDER, 231);
			pchar.Ship.name = "Black Hound";
			pchar.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS3;
			AddQuestRecord("Sharlie", "6");
			bDisableFastReload = false;//открыть переход
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			if (GetCharacterIndex("GigoloMan") != -1)
			{
				sld = characterFromId("GigoloMan");
				sld.lifeday = 0;
			}
			pchar.GenQuest.StoreGoods.StoreIdx = Fortfrance_STORE;
			pchar.GenQuest.StoreGoods.Starting = true; // заполняем магазин
			bNoEatNoRats  = true; // отменяем еду и крыс
			GiveItem2Character(pchar, "map_normal");
		break;
		
		case "Sharlie_shipwait":
			dialog.text = "Szóval, Monsieur, visszajött a pénzzel?";
			if (sti(Pchar.money) >= 15000)
			{
				link.l1 = "Igen, azt hiszem, van annyi, hogy megengedhetek magamnak egy ócska hajót.";
				link.l1.go = "Sharlie_7";
			}
			else
			{
				link.l1 = "Nekem még nincs elég. Csak beugrottam, hogy körülnézzek...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Sharlie_shipwait";
			}
		break;
//<-- -----------------------------------------Бремя гасконца-----------------------------------------------------
		// Addon-2016 Jason, французские миниквесты (ФМК) ФМК-Мартиника
		case "FMQM_oil_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(npchar, "goto", "goto5", "FMQM_Looking", -1);
			pchar.questTemp.FMQM = "remove_oil1";
		break;
		
		case "FMQM_oil_2":
			DialogExit();
			LAi_SetActorType(npchar);
			sld = characterFromId("FMQM_officer");
			sld.Dialog.currentnode = "officer_3";
			LAi_SetActorType(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
			pchar.questTemp.FMQM = "remove_oil2";
		break;
		
		case "FMQM_oil_3":
			DialogExit();
			LAi_SetActorType(npchar);
			sld = characterFromId("FMQM_officer");
			sld.Dialog.currentnode = "officer_5";
			LAi_SetActorType(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
			pchar.questTemp.FMQM = "remove_oil3";
		break;
		
		case "FMQM_oil_4":
			dialog.text = "Sajnos, barátom, de mindketten szenvedtünk itt. Elkobozták a gyantát, ráadásul rengeteg pénzt pazaroltam el az óvadékomra. És honnan a fenébôl tudtak a mi akciónkról? Biztos az egyik munkásom... Majd én elintézem, az Úr irgalmazzon a bûnösnek!";
			link.l1 = "Vagyis minden erôfeszítésem hiábavaló volt...";
			link.l1.go = "FMQM_oil_5";
		break;
		
		case "FMQM_oil_5":
			dialog.text = "Nagyon sajnálom, kapitány. Itt nem tehetünk semmit, a sors néha nagyon szar.";
			link.l1 = "Értem... Rendben, akkor én most elmegyek. Viszontlátásra!";
			link.l1.go = "FMQM_oil_6";
		break;
		
		case "FMQM_oil_6":
			DialogExit();
			AddQuestRecord("FMQ_Martinique", "12");
			pchar.questTemp.FMQM = "officer";
			pchar.quest.FMQM_advice.win_condition.l1 = "location";
			pchar.quest.FMQM_advice.win_condition.l1.location = "FortFrance_town";
			pchar.quest.FMQM_advice.function = "FMQM_GuideAdvice";
			DeleteAttribute(pchar, "questTemp.FMQM.Oil");
		break;
		
		// Addon 2016-1 Jason пиратская линейка
		case "mtraxx_x":
            dialog.text = "Szeretnék visszatérni erre a beszélgetésre. Hajlandó vagyok tisztességes árengedményt adni... egy igen tekintélyes árengedményt a hajóján végzett munkáért... ha ad nekem némi extra selymet...";
			link.l1 = "Mester, térjünk a lényegre. Ígérem, hogy nem vagyok kém, és nem is tartozom D'Oyley ezredes emberei közé. Sôt, Marcus Tyrexnek dolgozom, a név, amit már ismerhet. Tehát, terítsük ki a kártyákat az asztalra. Tudom, hogy állandóan szükséged van selyem vitorlavászonra, és Marcus Tyrex hajlandó elhozni neked. Szintén folyamatosan. Azonban csak abban az esetben, ha megegyezünk az árban. Akkor rögtön rátérhetünk erre, mester?";
			link.l1.go = "mtraxx_x_1";
		break;
		
		case "mtraxx_x_1":
            dialog.text = "Rendben. Úgy tûnik, nincs más választásom - vagy D'Oyley-nek dolgozol, és börtönbe küldesz, vagy tönkremegyek, ha nem találok sürgôsen egy tekintélyes mennyiségû selyemszállítmányt. Hajlandó vagyok 25 dublont fizetni darabonként, de csak nagy szállítmányért, legalább 100 tekercsért.";
			link.l1 = "Akkor megegyeztünk. Biztos vagyok benne, hogy Tyrex képes havonta 100 tekercsnyi szállítmányt biztosítani.";
			link.l1.go = "mtraxx_x_2";
		break;
		
		case "mtraxx_x_2":
            dialog.text = "Az nagyon jó lenne! Azonnal meg tudnám venni az elsô adagot.";
			link.l1 = "Most még nem tudom megtenni, de nem tart sokáig. Egy hajó a szükséges rakománnyal jelenleg Capsterville-ben van, azonnal oda tartok, és elküldöm önnek. Hol fogunk kirakodni?";
			link.l1.go = "mtraxx_x_3";
		break;
		
		case "mtraxx_x_3":
            dialog.text = "Rendezzük így. Minden hónap 10. és 15. napja között, minden este, az embereim várják a látogatóit az öbölnél... nem, várjon, inkább a Negril-foknál. Hosszú lesz az út, de ott sokkal kevesebb az ôrjárat... A jelszó a következô lesz: 'A merchant of Lyons'.";
			link.l1 = "Megegyeztünk, mester. Azonnal Capsterville-be megyek.";
			link.l1.go = "mtraxx_x_4";
		break;
		
		case "mtraxx_x_4":
            dialog.text = "Remélem, a hajód gyorsan megérkezik, nagy szükségem van új selyemre.";
			link.l1 = "Ne aggódj, minden rendben lesz. Isten éltessen!";
			link.l1.go = "mtraxx_x_5";
		break;
		
		case "mtraxx_x_5":
			DialogExit();
            AddQuestRecord("Roger_2", "21");
			pchar.questTemp.Mtraxx = "silk_10"; // покупатель найден
			sld = characterFromId("Jeffry");
			sld.DeckDialogNode = "Jeffry_9";
		break;
		// Jason Исла Мона
		case "IslaMona":
			if (CheckAttribute(pchar, "questTemp.IslaMona.Shipyarder") && pchar.questTemp.IslaMona.Shipyarder == npchar.id)
			{
				if (sti(NPChar.nation) != PIRATE && ChangeCharacterHunterScore(Pchar, NationShortName(sti(NPChar.nation)) + "hunter", 0) > 10)
				{
					dialog.text = "Nem, "+pchar.name+". Semmi bajom veled, de elôbb oldd meg a problémáidat az én országommal. Egy ilyen értékes leltár eladása a korona ellenségének félreérthetô lenne.";
					link.l1 = "Igen, és amikor tisztázatlan eredetû csempészárut csempészel hajókra, akkor a legjobb barátok vagytok? Várjatok, amíg megoldom ezt a félreértést.";
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = "Mondjuk úgy. Miért? Miért? Építesz valamit?";
					link.l1 = "Nem, egy nagyon különleges megbízást teljesítek. Egy ültetvényvezetônek.";
					link.l1.go = "IslaMona_1";
				}
			}
			else
			{
				npchar.quest.IslaMonaTools = "true";
				dialog.text = "Nem tudok segíteni.";
				link.l1 = "Kár érte!";
				link.l1.go = "exit";
			}
		break;
		
		case "IslaMona_1":
            dialog.text = "Értem, értem. Remélem, ez a menedzser eleget biztosított önnek, mert én sokat kérnék egy ilyen készletért. Nagyon szerencsés, hogy nemrég érkezett a nagyvárosból.";
			link.l1 = "Mennyibe kerül?";
			link.l1.go = "IslaMona_2";
		break;
		
		case "IslaMona_2":
			pchar.questTemp.IslaMona.Shipyarder.Money = 1000;
            dialog.text = "Ezer arany dublont.";
			link.l1 = "Látom, túlmelegszik. Jól vagyok. Elviszem.";
			link.l1.go = "IslaMona_7";
			link.l2 = "Ez túl sok. Kétlem, hogy lesz még egy olyan vevô az egész készletre, mint én. Egy része el fog fogyni, egy részét pedig ellopják a helyi csavargók. Mit szólnál egy kis kedvezményhez?";
			link.l2.go = "IslaMona_3";
		break;
		
		case "IslaMona_3":
			if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) < 60)
			{
				notification("Képességpróba Sikertelen (60)", SKILL_COMMERCE);
				dialog.text = "Garantálom, hogy elôkerül. Az ár nem változik. Mit szólsz hozzá? Nem várok sokáig.";
				link.l1 = "Rendben, rendben, rendben. Elviszem.";
				link.l1.go = "IslaMona_7";
				AddCharacterExpToSkill(pchar, "Commerce", 200);
			}
			else
			{
				notification("Képességellenôrzés megfelelt", SKILL_COMMERCE);
				pchar.questTemp.IslaMona.Shipyarder.Money = 900;
				dialog.text = "Rendben, akkor százért. Kilencszáz. Nem megyek lejjebb. Ne is kérdezze.";
				link.l1 = "És nem is fogok. Egyetértek.";
				link.l1.go = "IslaMona_7";
				link.l2 = "Miért nem adsz még egy kicsit többet? Mint nagykereskedô. És akkor majd rendelek tôled javításokat és festékeket, meg a legszaftosabb figurát.";
				link.l2.go = "IslaMona_4";
				AddCharacterExpToSkill(pchar, "Fortune", 100);
			}
		break;
		
		case "IslaMona_4":
            if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) < 85)
			{
				notification("Képességpróba Sikertelen (85)", SKILL_COMMERCE);
				dialog.text = "Az sem érdekel, ha egy élô szajhát rendelsz. Kilencszáz.";
				link.l1 = "Rendben, rendben, rendben. Elviszem.";
				link.l1.go = "IslaMona_7";
				AddCharacterExpToSkill(pchar, "Commerce", 400);
			}
			else
			{
				notification("Képességellenôrzés megfelelt", SKILL_COMMERCE);
				pchar.questTemp.IslaMona.Shipyarder.Money = 800;
				dialog.text = "Biztos vagy benne? Nem felejted el? Rendben, vágjunk le még egy százat. De ennyi!";
				link.l1 = "Nem felejtem el. Megegyeztünk!";
				link.l1.go = "IslaMona_7";
				link.l2 = "Nos, hogy is mondjam...";
				link.l2.go = "IslaMona_5";
				AddCharacterExpToSkill(pchar, "Fortune", 200);
			}
		break;
		
		case "IslaMona_5":
            dialog.text = "Elképzelhetetlen! "+pchar.name+", elfelejtették eltávolítani a sörétdarabot a koponyádból? Kapzsi, mint egy skorpió! Mindannyian hallottunk a legutóbbi kalandjaidról! Te már kiérdemelted az aranyat, ne akadályozz másokat abban, hogy ôk is kiérdemeljék a magukét. Még egy szó, és nem adom el ezernél kevesebbért.";
			link.l1 = "Jól van, jól van! Nyugalom! Egyetértek.";
			link.l1.go = "IslaMona_7";
			link.l2 = "De, "+npchar.name+", nekem kisgyerekeim vannak! Rájuk is gondolnom kell! Nem kapsz elég pénzt a becsületes fuvarozásért, tudod jól!";
			link.l2.go = "IslaMona_6";
		break;
		
		case "IslaMona_6":
            if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) < 100)
			{
				notification("Képességpróba Sikertelen (100)", SKILL_COMMERCE);
				pchar.questTemp.IslaMona.Shipyarder.Money = 1000;
				dialog.text = "A bordélyházi lányok gyermekei nem számítanak, "+pchar.name+". Elegem van belôled. Ezer dublont a hordóra, vagy búcsút mondunk.";
				link.l1 = "Hogy érted, hogy nem? Aha. Egyetértek, te egy csaló vagy.";
				link.l1.go = "IslaMona_7";
				AddCharacterExpToSkill(pchar, "Commerce", 800);
			}
			else
			{
				notification("Képességellenôrzés megfelelt", SKILL_COMMERCE);
				pchar.questTemp.IslaMona.Shipyarder.Money = 700;
				dialog.text = "Nem tudtam, hogy vannak gyerekeid. És hogy ennyire rosszul állnak a dolgok. Rendben, ne panaszkodj. Hétszáz. Ez majdnem veszteség.";
				link.l1 = "Nem felejtem el. Megegyeztünk!";
				link.l1.go = "IslaMona_7";
				AddCharacterExpToSkill(pchar, "Fortune", 400);
				Achievment_SetStat(106, 1);
			}
		break;
		
		case "IslaMona_7":
            dialog.text = "Szóval, tartozol nekem "+sti(pchar.questTemp.IslaMona.Shipyarder.Money)+" dublonnal.";
			if (PCharDublonsTotal() >= sti(pchar.questTemp.IslaMona.Shipyarder.Money))
			{
				link.l1 = "Tessék, neked adom az utolsót, nekem már nem maradt semmim.";
				link.l1.go = "IslaMona_8";
			}
			else
			{
				if (PCharDublonsTotal() < 1)
				{
					link.l1 = "Várj, megyek az uzsoráshoz, hogy eladósodjak.";
					link.l1.go = "IslaMona_money_exit";
				}
				else
				{
					link.l1 = "Minden, ami nálam van "+FindRussianDublonString(PCharDublonsTotal())+". Fogd ezt, én meg elmegyek az uzsorásokhoz.";
					link.l1.go = "IslaMona_money";
				}
			}
		break;
		
		case "IslaMona_money":
			pchar.questTemp.IslaMona.Shipyarder.Money = sti(pchar.questTemp.IslaMona.Shipyarder.Money)-PCharDublonsTotal();
			Log_Info("Adtál... "+FindRussianDublonString(PCharDublonsTotal())+"");
			RemoveDublonsFromPCharTotal(PCharDublonsTotal());
			PlaySound("interface\important_item.wav");
            dialog.text = "Ne sajnálj engem, neked van egy kabinszekrényed tele arannyal. Tartozol nekem "+FindRussianDublonString(sti(pchar.questTemp.IslaMona.Shipyarder.Money))+".";
			link.l1 = "";
			link.l1.go = "IslaMona_money_exit";
		break;
		
		case "IslaMona_money_exit":
            NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			npchar.quest.IslaMonaMoney = "true";
			pchar.questTemp.IslaMona = "dublon";
		break;
		
		case "IslaMona_8":
			Log_Info("Adtál... "+FindRussianDublonString(sti(pchar.questTemp.IslaMona.Shipyarder.Money))+"");
			RemoveDublonsFromPCharTotal(sti(pchar.questTemp.IslaMona.Shipyarder.Money));
			PlaySound("interface\important_item.wav");
            dialog.text = "Ez nagyszerû. A teljes összeg a helyén van. A szerszámokat a hajódra szállítják. Ezek nehéz ládák.";
			link.l1 = "Köszönöm, "+npchar.name+"!";
			link.l1.go = "IslaMona_9";
		break;
		
		case "IslaMona_9":
            NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			GiveItem2Character(pchar, "islamona_toolbox");
			DeleteAttribute(pchar, "questTemp.IslaMona.Shipyarder");
			DeleteAttribute(npchar, "quest.IslaMonaMoney");
			AddQuestRecord("IslaMona", "2");
			pchar.questTemp.IslaMona = "get_tools";
		break;
	}
}

string findShipyardCity(ref NPChar)
{
	int n, nation;
    int storeArray[2];
	SetArraySize(&storeArray, MAX_COLONIES); 
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		nation = GetNationRelation(sti(npchar.nation), sti(colonies[n].nation));
		if (sti(colonies[n].nation) != PIRATE && colonies[n].id != "Panama" && colonies[n].nation != "none" && GetIslandByCityName(npchar.city) != colonies[n].islandLable) //не на свой остров
		{
			if (GetCharacterIndex(colonies[n].id + "_shipyarder") != -1)
			{
				storeArray[howStore] = n;
				howStore++;
			}
		}
	}
	if (howStore == 0) return "none";
	nation = storeArray[rand(howStore-1)];
	return colonies[nation].id;
}

// проверка какой уже цвет есть
bool CheckSailsColor(ref chr, int col)
{
	int    st = GetCharacterShipType(chr);
	ref    shref;
	
	if (st != SHIP_NOTUSED)
	{
		shref = GetRealShip(st); 
		st = -1;
		if (!CheckAttribute(shref, "ShipSails.SailsColor"))  st = 0; // нету - это белый
		if (CheckAttribute(shref, "SailsColorIdx"))  st = sti(shref.SailsColorIdx);
		if (st == col) return false;
	}
	return true;		
}

bool CheckSailsGerald(ref chr)
{
    int    st = GetCharacterShipType(chr);
	ref    shref;
	if (st != SHIP_NOTUSED)
	{
		shref = GetRealShip(st);
		if (CheckAttribute(shref, "GeraldSails"))  return true;
	}
	return false;
}

string GetSailsType(int _type)
{
	string sSail;
	
	switch (_type)
	{
	    case 1 : sSail = ""+XI_ConvertString("sails_1")+""; break;
	    case 2 : sSail = ""+XI_ConvertString("sails_2")+""; break;
	    case 3 : sSail = ""+XI_ConvertString("sails_3")+""; break;
		case 4 : sSail = ""+XI_ConvertString("sails_4")+""; break;
		case 5 : sSail = ""+XI_ConvertString("sails_5")+""; break;
		case 6 : sSail = ""+XI_ConvertString("sails_6")+""; break;
		case 7 : sSail = ""+XI_ConvertString("sails_7")+""; break;
		case 8 : sSail = ""+XI_ConvertString("sails_8")+""; break;
		case 9 : sSail = ""+XI_ConvertString("sails_9")+""; break;
		case 10 : sSail = ""+XI_ConvertString("sails_10")+""; break;
		case 11 : sSail = ""+XI_ConvertString("sails_11")+""; break;
	}
	return sSail;
}

int GetSailsTypePrice(int _asis, int _tobe, float _shipCostRate, int _price)
{
	int ret;
	ret = _tobe - _asis;
	
	if (ret < 0) ret = 0;
	
	return makeint((ret*_price*0.05 + _price*0.05)*_shipCostRate / 10) * 10;
}

void SelectFindship_ShipType()
{
	int iRank;
	if (sti(pchar.rank) < 7) iRank = 0;
	if (sti(pchar.rank) >= 7 && sti(pchar.rank) < 11) iRank = 1;
	if (sti(pchar.rank) >= 11 && sti(pchar.rank) < 20) iRank = 2;
	if (sti(pchar.rank) >= 20 && sti(pchar.rank) <= 27) iRank = 3;
	
	int iShip = SHIP_WAR_TARTANE;
	switch (iRank)
	{
		case 0:
			iShip = sti(RandPhraseSimple(its(GetRandomShipType(FLAG_SHIP_CLASS_6, FLAG_SHIP_TYPE_ANY, FLAG_SHIP_NATION_ANY)), 
										 its(GetRandomShipType(FLAG_SHIP_CLASS_5, FLAG_SHIP_TYPE_MERCHANT + FLAG_SHIP_TYPE_UNIVERSAL, FLAG_SHIP_NATION_ANY))));
		break;
		case 1:  
			iShip = sti(LinkRandPhrase(its(GetRandomShipType(FLAG_SHIP_CLASS_6, FLAG_SHIP_TYPE_WAR + FLAG_SHIP_TYPE_RAIDER, FLAG_SHIP_NATION_ANY)), 
									   its(GetRandomShipType(FLAG_SHIP_CLASS_5, FLAG_SHIP_TYPE_ANY, FLAG_SHIP_NATION_ANY)),
									   its(GetRandomShipType(FLAG_SHIP_CLASS_4, FLAG_SHIP_TYPE_MERCHANT + FLAG_SHIP_TYPE_UNIVERSAL, FLAG_SHIP_NATION_ANY))));
		break; 
		case 2:  
			iShip = sti(LinkRandPhrase(its(GetRandomShipType(FLAG_SHIP_CLASS_5, FLAG_SHIP_TYPE_WAR + FLAG_SHIP_TYPE_RAIDER, FLAG_SHIP_NATION_ANY)), 
									   its(GetRandomShipType(FLAG_SHIP_CLASS_4, FLAG_SHIP_TYPE_ANY, FLAG_SHIP_NATION_ANY)),
									   its(GetRandomShipType(FLAG_SHIP_CLASS_3, FLAG_SHIP_TYPE_MERCHANT + FLAG_SHIP_TYPE_UNIVERSAL, FLAG_SHIP_NATION_ANY))));
		break;
		case 3:  
			iShip = sti(LinkRandPhrase(its(GetRandomShipType(FLAG_SHIP_CLASS_4, FLAG_SHIP_TYPE_WAR + FLAG_SHIP_TYPE_RAIDER, FLAG_SHIP_NATION_ANY)), 
									   its(GetRandomShipType(FLAG_SHIP_CLASS_3, FLAG_SHIP_TYPE_ANY, FLAG_SHIP_NATION_ANY)),
									   its(GetRandomShipType(FLAG_SHIP_CLASS_2, FLAG_SHIP_TYPE_MERCHANT + FLAG_SHIP_TYPE_UNIVERSAL, FLAG_SHIP_NATION_ANY))));
		break;
	}
	
	pchar.GenQuest.Findship.Shipyarder.ShipType = iShip;
}

// проверка количества материалов для корабельного тюнинга
void checkMatherial(ref Pchar, ref NPChar, int good)
{
    int amount;

    amount = GetSquadronGoods(Pchar, good) - sti(NPChar.Tuning.Matherial);
    if (amount < 0)
    {
       amount = amount + sti(NPChar.Tuning.Matherial);
    }
    else
    {
        amount = sti(NPChar.Tuning.Matherial);
    }
    RemoveCharacterGoods(Pchar, good, amount);
    NPChar.Tuning.Matherial = sti(NPChar.Tuning.Matherial) - amount;
}

/*
  _chr 		- ГГ
  NPChar 	- верфист
  MaterialNum -  номер материала для апгрейда 
	 1 - товар	 
	 2 - цена в дублонах(сундуки)
  Функция возвращает кол-во материала необходимого для данного типа апгрейда	  
*/

int GetMaterialQtyUpgrade( ref _chr, ref _nchar, int MaterialNum )
{
	if ( sti(_chr.Ship.Type) == SHIP_NOTUSED) return 0;
	
	float fQuestShip 	= 1.0;
	float LEcoeff       = 1.0; // legendary edition
		
	int   	shipClass     		= sti(RealShips[sti(_chr.Ship.Type)].Class);	
	int   	shipMinCrew   		= sti(RealShips[sti(_chr.Ship.Type)].MinCrew);	
	int 	shipPrice			= sti(RealShips[sti(_chr.Ship.Type)].Price);	
		
    if(shipClass == 4) LEcoeff = 0.38;
    if(shipClass > 4) LEcoeff = 0.25;
	if(CheckAttribute(&RealShips[sti(_chr.Ship.Type)], "QuestShip")) 	fQuestShip = 1.3;	

	if(MaterialNum == 1) 
	{
	int Material 	= makeint((40 * (8 - shipClass) + 25 * MOD_SKILL_ENEMY_RATE + hrand(shipMinCrew)) * fQuestShip * LEcoeff);
	if(Material < 1) 		Material 	= 1;
		return Material;
	}
	if(MaterialNum == 2)
	{
		int WorkPrice 	= 1;
		switch (shipClass)
		{
			case 1: 
				WorkPrice = 10;
			break;
			case 2: 
				WorkPrice = 7;
			break;
			case 3: 
				WorkPrice = 5;
			break;
			case 4: 
				WorkPrice = 3;
			break;
			case 5: 
				WorkPrice = 2;
			break;
			case 6: 
				WorkPrice = 1;
			break;
		}
		return WorkPrice;
	}
	
	return 0;
}
// belamour legendary edition тюнинг - проверка на сделанное
bool TuningAvailable()
{
	int num = 0;
    ref shTo = &RealShips[sti(Pchar.Ship.Type)];

	if(CheckAttribute(shTo, "Tuning.SpeedRate"))    num++;
	if(CheckAttribute(shTo, "Tuning.WindAgainst"))  num++;
	if(CheckAttribute(shTo, "Tuning.Cannon"))       num++;
	if(CheckAttribute(shTo, "Tuning.Capacity"))     num++;
	if(CheckAttribute(shTo, "Tuning.HP"))           num++;
	if(CheckAttribute(shTo, "Tuning.MaxCrew"))      num++;
	if(CheckAttribute(shTo, "Tuning.TurnRate"))     num++;
	if(CheckAttribute(shTo, "Tuning.MinCrew"))      num++;
	
	if(sti(shTo.Class) > 4 && num == 7 && !CheckAttribute(shTo, "Tuning.MinCrew"))
	{
		if(!CheckAttribute(shTo, "Tuning.All"))
        {
			if(sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_HIMERA) Achievment_Set("ach_CL_115");
			if(startHeroType == 4 && sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_SCHOONER_W)
			{
				if(pchar.ship.name == "Rainbow") Achievment_Set("ach_CL_126");
			}
            shTo.Tuning.All = true;
            Log_Info("A " + pchar.ship.name + "  hajó sebessége 5%-kal nô a globális térképen!");
        }
        return false;
	}
	
	if(num < 8) return true;
	else
    {
        if(!CheckAttribute(shTo, "Tuning.All"))
        {
			if(sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_HIMERA) Achievment_Set("ach_CL_115");
			if(startHeroType == 4 && sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_SCHOONER_W)
			{
				if(pchar.ship.name == "Rainbow") Achievment_Set("ach_CL_126");
			}
            shTo.Tuning.All = true;
            Log_Info("A " + pchar.ship.name + "  hajó sebessége 5%-kal nô a globális térképen!");
        }
        return false;
    }
}
