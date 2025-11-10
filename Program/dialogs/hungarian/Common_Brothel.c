void ProcessDialogEvent()
{
	ref NPChar, sld, location;
	aref Link, NextDiag;
	string sTemp,sTemp1, str, str1;
	int	s1,s2,s3,s4,s5,p1, iColony, crewWhoreCost, charWhoreCost = 0;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
		
    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Brothel\" + NPChar.City + "_Brothel.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	crewWhoreCost = 50 + 7 * MOD_SKILL_ENEMY_RATE - hrand(40);
	charWhoreCost = 2460 + sti(pchar.rank) * 40;
	
	switch(Dialog.CurrentNode)
	{
		// ============= хозяйка борделя =============
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar, 
					LinkRandPhrase(""+ GetSexPhrase("Milyen lányok, kedvesem?! A fél helyôrség a nyomodban van, és te egyenesen a bordélyházba jössz!","Tûnj el, jó? A fél helyôrség a nyomodban van!") +"", "Minden városôr téged keres. Nem vagyok bolond, hogy ebben a pillanatban szolgáltatásokat nyújtsak neked ...", "Nincs itt semmi keresnivalód!"), 
					LinkRandPhrase(""+ GetSexPhrase("Csak merészelj a lányaimhoz nyúlni, és élve megnyúzlak!","Tûnj el, te görény!") +"", "Mocskos"+ GetSexPhrase("","") +" gyilkos, hagyd el a létesítményemet, most! Ôrség!", "Nem félek tôled, "+ GetSexPhrase("gazember","patkány") +"! Hamarosan felakasztanak az erôdünkben, nem jutsz messzire..."));
				link.l1 = NPCharRepPhrase(pchar,
					RandPhraseSimple("Heh, a riasztó nekem sosem jelent problémát...", "Soha nem fognak elkapni."), 
					RandPhraseSimple("Csak fogd be, hülye vénasszony.", "Fogd be, ha nem akarsz problémát..."));
				link.l1.go = "exit";
				break;
			}
			//--> Мерзкий Божок
			if (CheckAttribute(pchar, "questTemp.ChickenGod.HostessDialog")) {
				dialog.text = "Ó, Istenem! Hogy jutottál be ide? Kedves kapitány, kérem távozzon - könyörgöm! A létesítményünk jelenleg zárva van!";
				link.l1 = "Örülök, hogy látlak, kedves " + npchar.name + ". Rajta voltam a vendéglistán. Az ilyen létesítményekben azonban még a vendégeknek is fizetniük kell, így... Kérem, ne nehezítsék meg a dolgomat, de szeretnék fizetni a szobáért.";
				link.l1.go = "chicken_god";
				
				DeleteAttribute(pchar, "questTemp.ChickenGod.HostessDialog");
				break;
			}
			//<-- Мерзкий Божок
			//--> туториал Мартиника
			if (CheckAttribute(pchar, "questTemp.Sharlie.Gigolo") && pchar.questTemp.Sharlie.Gigolo == "start" && npchar.location == "FortFrance_SecBrRoom")
			{
				DelLandQuestMark(npchar);
				link.l1 = "Figyelj, Aurora, szükségem van egy lányra az éjszakára. És haza akarom vinni magammal. Meg tudod ezt oldani?";
                link.l1.go = "Gigolo";
				break;
			}
			//<-- туториал Мартиника
			//Jason --> Заносчивый аристократ
			if (!CheckAttribute(pchar, "GenQuest.Badboy") && !CheckAttribute(npchar, "quest.Badboy") && !CheckAttribute(pchar, "questTemp.ZA.Block") && makeint(environment.time) > 15.0 && makeint(environment.time) < 21.0 && sti(pchar.questTemp.HorseQty) > 4)
			{
				dialog.text = "Maga egy olyan tekintélyes ember. Ráadásul a lányaim nagyon kedvelik önt. Szeretném megkérni egy kis szívességre a létesítményem számára.";
				link.l5 = "Ez hízelgô, az biztos. Mi az, amiben a segítségemre van szüksége?";
				link.l5.go = "Badboy";
				link.l8 = "Sajnálom, de jelenleg nem érek rá.";
				link.l8.go = "exit";
				npchar.quest.Badboy = "true";
				break;
			}
			
			if (CheckAttribute(pchar, "GenQuest.Badboy.Complete") || CheckAttribute(pchar, "GenQuest.Badboy.Continue"))
			{
				if (npchar.City == pchar.GenQuest.Badboy.Brothel.City)
				{
					dialog.text = "Ó, visszatértél! Elintézted, hogy az a "+pchar.GenQuest.Badboy.Brothel.Name+" békén hagyja a lányaimat?";
					link.l5 = "Igen. Többé nem fog itt mutatkozni.";
					link.l5.go = "Badboy_complete";
				break;
				}
			}
			// <-- Заносчивый аристократ
			
			//--> Jason Португалец
			if (CheckAttribute(pchar, "questTemp.HWIC.Detector") || SandBoxMode)
			{
				bool bOk = (pchar.questTemp.HWIC.Detector == "holl_win") || (pchar.questTemp.HWIC.Detector == "eng_win") || (pchar.questTemp.HWIC.Detector == "self_win") || SandBoxMode;
				if (!CheckAttribute(pchar, "questTemp.Portugal") && bOk && !CheckAttribute(npchar, "quest.Portugal") && npchar.location == "Marigo_SecBrRoom" && makeint(environment.time) > 6.0 && makeint(environment.time) < 22.0 && sti(pchar.rank) >= 7)
				{
					DelMapQuestMarkCity("marigo");
					DelLandQuestMark(npchar);
					dialog.text = "Kapitány, kérhetek egy szívességet?";
					link.l5 = "Önnek, asszonyom, bármit, amit csak akar! Szolgálatára állok!";
					link.l5.go = "Portugal";
					link.l8 = "Sajnálom, de jelenleg nem érek rá.";
					link.l8.go = "exit";
					npchar.quest.Portugal = "true";
					DelLandQuestMark(npchar);
					break;
				}
			}
			if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "HostressMoney" && npchar.location == "Marigo_SecBrRoom")
			{
				DelLandQuestMark(npchar);
				dialog.text = "Beszélt már Hugóval, kapitány úr?";
				if (sti(pchar.money) >= 10000)
				{
					link.l1 = "Továbbá, asszonyom, itt van a pénze. Minden a legkedvezôbben alakult...";
					link.l1.go = "Portugal_3";
				}
				else
				{
					link.l1 = "Igen, átadtam neki a kérését.";
					link.l1.go = "Portugal_exit";
				}
				break;
			}
			//<--Португалец
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Retribution") && pchar.questTemp.Mtraxx.Retribution == "brothel" && npchar.location == "Tortuga_SecBrRoom")
			{
				dialog.text = "Ó, ezt nézd meg! Charlie Prince, egy híres kalóz! Hús-vér testben!";
				link.l1 = RandSwear()+"Hello, Janette. Marcus Tyrex megbízásából vagyok itt.";
				link.l1.go = "mtraxx_R";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Retribution") && pchar.questTemp.Mtraxx.Retribution == "brothel_repeat" && npchar.location == "Tortuga_SecBrRoom")
			{
				dialog.text = "Készen állsz egy felejthetetlen helyreállító kezelésre, bátor korzóm?";
				if (sti(pchar.money) >= 31000)
				{
					link.l1 = "Én vagyok az! Charlie Prince nem pazarolja a szavakat, ahogy a pénzt sem, ha-ha!";
					link.l1.go = "mtraxx_R2";
				}
				else
				{
					link.l1 = "Majdnem... Azt hiszem, elvesztettem egy pénztárcát a létesítményedben... Visszajövök a pénzzel!";
					link.l1.go = "exit";
				}
				break;
			}
			
			if (npchar.quest.meeting == "0")
			{
				dialog.text = RandPhraseSimple(TimeGreeting() + ". Üdvözöllek a szeretet házában. A nevem " + npchar.name + ", és én vagyok a tulajdonos. "+ GetSexPhrase("Mit tehetek érted, " + GetAddress_Form(NPChar) + "?","Ôszintén szólva kicsit meglepôdtem, hogy itt látom, " + GetAddress_Form(NPChar) + ", de biztosíthatom, hogy nem csak férfiaknak nyújtunk szolgáltatásokat.") +"",
				TimeGreeting() + ". Üdvözlöm Önt, "+ GetSexPhrase("idegen","fiatal hölgy") +", szerény létesítményemben. Engedje meg, hogy bemutatkozzam, én vagyok "+ NPChar.Name + " - a nôi érintésre éhes férfiak számára fenntartott menedékhely tulajdonosa. "+ GetSexPhrase("Mit tehetek önért?","Bár a hölgyeknek is van egy-két dolog...") +"");
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = RandPhraseSimple(TimeGreeting() + ". Miben segíthetek, " + GetAddress_Form(NPChar) + "?",
				TimeGreeting() + ". Mit tehetek önért, " + GetAddress_Form(NPChar) + "?");
			}
			if (!CheckAttribute(pchar, "questTemp.Sharlie.Gigolo"))//не идёт квест девочки
			{
				if (!CheckAttribute(pchar, "GenQuest.BrothelLock"))// нет запрета от Мэри 280313
				{
					link.l2 = npchar.name + ", Szeretnék egy kis idôt tölteni az egyik lányoddal.";
					link.l2.go = "Hostess_1";
				}
			}
			if (!CheckAttribute(pchar, "questTemp.Sharlie.Lock")) // не идёт старт Шарля
			{
				if (sti(pchar.ship.type) != SHIP_NOTUSED && GetCrewQuantity(pchar) > 0) // Rebbebion - а смысл, если нет как корабля, так и команды?
				{
					link.l3 = "Régen volt már, hogy utoljára elkényeztettem az embereimet. Rendelhetek egy nagy tételben lányokat a fiaimnak?";
					link.l3.go = "ForCrew";
				}
			}
			link.l4 = "Lenne egy kérdésem.";
			if (CheckCharacterItem(pchar, "CaptainBook") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakBrothelMadam"))
			{
				if((pchar.questTemp.different.GiveShipLetters.city == npchar.city) && CheckAttribute(pchar, "questTemp.different.GiveShipLetters"))
				{
					link.l4.go = "ShipLetters_1";// генератор  "Найденные документы"
				}
				else
				{
					link.l4.go = "quests";
				}	
			}
			else
			{
				link.l4.go = "quests";//(перессылка в файл города)
			}	
			//-->> квест поиска кольца мэра
			if (pchar.questTemp.different == "TakeMayorsRing" && pchar.questTemp.different.TakeMayorsRing.city == npchar.city && GetNpcQuestPastDayWOInit(npchar, "TakeMayorsRing") > 7)
			{
				link.l5 = "Figyeljen, " + npchar.name + ", a kormányzó gyûrûjét keresem. Az önök létesítményében pihent, és valószínûleg itt vesztette el.";
				link.l5.go = "TakeMayorsRing_H1";
				SaveCurrentNpcQuestDateParam(npchar, "TakeMayorsRing");
			}
			//<<-- квест поиска кольца мэра

			// belamour ночной приключенец -->
			if(CheckAttribute(pchar, "GenQuest.NightAdventureVar") && pchar.GenQuest.NightAdventureVar == "NightAdventure_NobleWhoreMoney")
			{
				link.l8 = "Nézze, szeretném a legjobb lányt elvinni, akije van.";
				link.l8.go = "NA_Girl";
			}
			// <-- приключенец
			link.l9 = "Nem érdekes, már megyek is.";
			link.l9.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "ShipLetters_1":
				pchar.questTemp.different.GiveShipLetters.speakBrothelMadam = true;
				dialog.text = RandPhraseSimple("Mit akarsz, szépfiú?","Hallgatom magát, kapitány.");
				link.l1 = "Figyeljen, " + npchar.name + ", ezeket a papírokat az önök intézményének egyik magántermében találtam ...";
				link.l1.go = "ShipLetters_2";				
		break;
		
		case "ShipLetters_2":
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 0)
			{
				dialog.text = "Hadd nézzem! Hmm... valami kapitány elvesztette az iratait, igaz? Azt hiszem, meg kellene kérdeznie a kikötômestert errôl.";
				link.l1 = "Talán, talán...";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Hadd nézzem meg! Ó! A névbôl ítélve, ezek az én nagyra becsült ügyfelemé, városunk egy méltó polgáráé. Én magam is átadhatom neki ezeket az iratokat.";
				link.l1	= "Valószínûleg nem...";
				link.l1.go = "exit";
				link.l2 = "Kitûnô! Mindig örülök, ha segíthetek egy jó embernek és egy méltó intézménynek.";
				link.l2.go = "ShipLetters_3";										
			}	
		break;
		
		case "ShipLetters_3":
			TakeItemFromCharacter(pchar, "CaptainBook"); 
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //снимаем таймер 
			AddQuestRecord("GiveShipLetters", "2");			
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters"); 
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
        case "Hostess_1":
			if (!CheckAttribute(npchar, "quest.selected"))
			{
				if (CheckNPCQuestDate(npchar, "quest.date"))
				{
					dialog.text = ""+ GetSexPhrase("Mindig örömmel szolgáljuk ki az ügyfelet. Most mondd csak, szépfiú - választottál már valakit, vagy nem nagyon érdekel?","Nos, a lányaim biztosan tudnak... segíteni. Választottál már valakit, vagy nem nagyon érdekel?") +"";
					Link.l1 = ""+ GetSexPhrase("Heh, nekem csak egy kurva kell, méghozzá most rögtön. Nem érdekel melyik, a lányaid mind jól néznek ki...","Bárki jó lesz, ha tudja a kötelességét, természetesen...") +"";
					Link.l1.go = "Hostess_NotChoice";	
					Link.l2 = "Igen, van egy, "+ GetSexPhrase("aki megtetszett...","ô lenne a legszebb...") +"";
					Link.l2.go = "Hostess_Choice";
				}
				else
				{
					dialog.text = "Ma nem tudok neked szabad lányokat adni, már így is túl sok vendégünk van. Jöjjön el holnap, és nem fogja megbánni!";
					Link.l1 = "Kár, épp most kezdtem el élvezni.";
					Link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "Hmm... Már kifizette a lányt. Ne zavarjon, kérem.";
				Link.l1 = "Rendben, megyek.";
				Link.l1.go = "exit";	
			}
		break;

        case "Hostess_NotChoice":
			sld = GetFreeHorseRef(npchar.city);
			location = &locations[FindLocation(npchar.city + "_Brothel")];
			if (sld.id == "none" || GetNpcQuestPastDayParam(location, "Brothel_date") > 98)
			{
				dialog.text = "Most nincs szabad lányom, pár nap múlva nézz vissza.";
				Link.l1 = "Rendben, ahogy mondod.";
				Link.l1.go = "exit";	
			}
			else
			{
				// belamour legendary edition Орден Святого Людовика -->
				if(IsEquipTalisman9() && npchar.nation == FRANCE)
				{
					dialog.text = ""+ GetSexPhrase("Nos, csôdör, ez kiváló!","Mindegyikük ügyes, biztos lehetsz benne.") +"Egy gyönyörû lányt tudok ajánlani, a neve " + GetFullName(sld) + ", ô most szabad.\nOh, mi ez, amit ott ilyen szerényen rejtegetsz?! Ez a legmagasabb kitüntetés Franciaországban? Az a hír járja, hogy ennek a jelvénynek a viselôi nem csak a csatatéren legendásak... Hát, tudod, mire gondolok, a filibusterem... Különben is, bárki megtiszteltetésnek venné, ha megérintené a 'rendedet', , úgyhogy ma az én intézményem rovására pihensz. A visszautasításokat nem fogadjuk el, szépfiú.";
					Link.l1 = "Persze, hogy egyetértek, milyen kérdések lehetnek?!";
					Link.l1.go = "Hostess_NotChoice_agree";	
					npchar.quest.choiceIdx = sld.index;
					break;
				}
				// <-- legendary edition
				dialog.text = ""+ GetSexPhrase("Nos, kiváló, csôdöröm!","Mindannyian nagyon ügyesek abban, amit csinálnak, efelôl nincs kétségem.") +" tudok ajánlani egy nagyon szép lányt, a neve " + GetFullName(sld) + ", és jelenleg szabad. Ez az öröm kerülni fog neked " + FindRussianMoneyString(sti(sld.quest.price) + charWhoreCost) + ". Egyetértesz?";
				Link.l1 = "Nem. Azt hiszem, nem. Túl drága...";
				Link.l1.go = "exit";
				if (sti(pchar.money) >= (sti(sld.quest.price) + charWhoreCost))
				{
					Link.l2 = "Persze, hogy utasíthatnám vissza?!";
					Link.l2.go = "Hostess_NotChoice_agree";	
					npchar.quest.choiceIdx = sld.index;
				}
				else
				{
					Link.l1 = "Ó, a fenébe, nincs nálam annyi pénz...";
					Link.l1.go = "exit";
				}
			}
		break;
		
        case "Hostess_NotChoice_agree":
			sld = &characters[sti(npchar.quest.choiceIdx)];
			if (sti(pchar.money) >= (sti(sld.quest.price) + charWhoreCost))
			{
				dialog.text = "Finom, "+ GetSexPhrase("jóképû","gyönyörû") +". " + sld.name + " vár rád a második emeleti különteremben.";
				Link.l1 = ""+ GetSexPhrase("Jó, jövök, akkor","Jó, jövök, akkor") +"...";
				Link.l1.go = "exit";
				// belamour legendary edition деньги только без ордена или адмиральского мундира
				if(IsEquipTalisman9())
				{
					if(npchar.nation != FRANCE) AddMoneyToCharacter(pchar, -(sti(sld.quest.price) + charWhoreCost));
				}
				else
				{
					AddMoneyToCharacter(pchar, -(sti(sld.quest.price) + charWhoreCost));
				}
				sld.dialog.currentnode = "Horse_ReadyFack";			
				//--> таймер на возврат, чтобы не вечно ждали
				str = npchar.city;
				pchar.quest.(str).win_condition.l1            = "Timer";
				pchar.quest.(str).win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
				pchar.quest.(str).win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
				pchar.quest.(str).win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
				pchar.quest.(str).win_condition               = "Brothel_checkVisitTime";	
				pchar.quest.(str).HorseId = sld.id;
				pchar.quest.(str).locator = sld.location.locator;
				//<-- таймер на возврат, чтобы не вечно ждали
				ChangeCharacterAddressGroup(sld, npchar.city + "_Brothel_room", "goto", "goto"+(rand(2)+1));
				LocatorReloadEnterDisable(npchar.city + "_Brothel", "reload2_back", false); //открываем комнату
				npchar.quest.selected = true; //флаг взял девку у хозяйки
				SetNPCQuestDate(npchar, "quest.date"); //дату взятия запишем
				for(int n=0; n<MAX_CHARACTERS; n++)
				{
					makeref(sld, Characters[n]);
					if (sld.location == npchar.city+"_Brothel" && CheckAttribute(sld, "CityType") && sld.CityType == "horse")
					{
						sld.dialog.currentnode = "Horse_4";
					}
				}
				
				// генератор найденных бумаг
				
				// belamour legendary edition не давать квесты губернатору и адмиралу
				bool MCGovernon = CheckAttribute(pchar, "questTemp.Patria.GenGovernor");
				bool MCAdmiral = isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4;
				
				if ((rand(4) == 1) && (pchar.questTemp.different == "free") && (!CheckCharacterItem(pchar, "CaptainBook")) && GetNpcQuestPastDayWOInit(npchar, "questShipLetters") > 10 && !MCGovernon && !MCAdmiral ) 
				{					
					pchar.questTemp.different = "GiveShipLetters";
					pchar.questTemp.different.GiveShipLetters = "toBrothel";
					pchar.questTemp.different.GiveShipLetters.Id = GetFullName(npchar);
					pchar.questTemp.different.GiveShipLetters.city = npchar.city;	
					pchar.questTemp.different.GiveShipLetters.variant = rand(2);
					p1 = rand(20 - MOD_SKILL_ENEMY_RATE) + 1; // даем хотя бы один день
					s1 = rand(80 - pchar.rank - p1) * 50 + rand(100);
					s2 = s1 * 2;
					s3 = s1 * rand(GetCharacterSPECIAL(pchar, "Szerencse")) + s1;
					s4 = s2 + s3;
					s5 = s4 * GetCharacterSPECIAL(pchar, "Karizma");
					pchar.questTemp.different.GiveShipLetters.price1 = s1;
					pchar.questTemp.different.GiveShipLetters.price2 = s2;
					pchar.questTemp.different.GiveShipLetters.price3 = s3;
					pchar.questTemp.different.GiveShipLetters.price4 = s4;
					pchar.questTemp.different.GiveShipLetters.price5 = s5;
										
					sld = ItemsFromID("CaptainBook");
					sld.CityName = XI_ConvertString("Colony" + npchar.city + "Gen");
					//ложим бумаги в итем								
					sTemp = "_Brothel_room";	
					sTemp1 = "_town";					
					sld.shown = true;
					sld.startLocation = pchar.questTemp.different.GiveShipLetters.city + sTemp;
					sld.startLocator = "item" + (rand(4)+1);
					sld.endLocation = pchar.questTemp.different.GiveShipLetters.city + sTemp1;
					pchar.questTemp.different.GiveShipLetters.item = true; //флаг -  бумаги валяются в итемах
					Log_QuestInfo("The papers are in location " + sld.startLocation + ", in locator " + sld.startLocator + " p1 : " + p1);
					
					pchar.quest.CheckShipLetters.win_condition.l1 = "location";
					pchar.quest.CheckShipLetters.win_condition.l1.location = sld.endLocation;
					pchar.quest.CheckShipLetters.function = "CheckShipLetters";
					
					SetTimerFunction("GiveShipLetters_null", 0, 0, p1); //освобождаем разрешалку на миниквесты 
					SaveCurrentNpcQuestDateParam(npchar, "questShipLetters");					
				}
				// генератор - "Повод для спешки"
				if((rand(5) == 2) && !CheckAttribute(pchar, "questTemp.ReasonToFast") && GetNpcQuestPastDayWOInit(npchar, "questReasonToFast") > 20 && !CheckAttribute(pchar, "questTemp.Sharlie.Lock") && !MCGovernon && !MCAdmiral) // Addon-2016 Jason
				{
					iColony = FindColony(npchar.city);	
					if( sti(Colonies[iColony].HeroOwn) == false && npchar.city != "Panama" && npchar.city != "Charles")
					{
						pchar.questTemp.ReasonToFast = "Begin";
						pchar.questTemp.ReasonToFast.city = npchar.city;
						sTemp1 = "_town";					
						pchar.quest.CheckReasonToFast.win_condition.l1 = "location";
						pchar.quest.CheckReasonToFast.win_condition.l1.location = npchar.city + sTemp1;
						pchar.quest.CheckReasonToFast.function = "ReasonToFast_CheckHorse";
						SaveCurrentNpcQuestDateParam(npchar, "questReasonToFast");	
					}	
				}				
			}
			else
			{
				dialog.text = "Ó, látod, az a baj, hogy " + sld.name + " nem egy olcsó lány, az ára " + FindRussianMoneyString(sti(sld.quest.price) + charWhoreCost) + ". És úgy látom, hogy jelenleg nem engedheted meg magadnak. Gyere vissza, ha gazdag leszel"+ GetSexPhrase(", kedves","") +"...";
				Link.l1 = "Ez az én szerencsém...";
				Link.l1.go = "exit";
			}
		break;

        case "Hostess_Choice":
			dialog.text = "Mindig örülök, amikor a lányok és a vásárlók meleg érzelmeket táplálnak egymás iránt... Mondd meg a nevét.";
			Link.l1.edit = 9;
			Link.l1 = "";
			Link.l1.go = "Hostess_Choice_1";	
		break;
		
        case "Hostess_Choice_1":
			sld = CheckHorsesName(npchar.city, 9);
			if (sld.id == "none")
			{
				dialog.text = "Hmm... biztos tévedsz. Nincs ilyen lány a létesítményemben. Talán rosszul értette a nevét.";
				Link.l1 = "Hmm... de épp most beszéltem vele.";
				Link.l1.go = "Hostess_Choice_2";				
				Link.l2 = "Talán. Jobb lenne, ha még egyszer megkérdezné a nevét, csak a biztonság kedvéért. Majd késôbb beszélünk errôl.";
				Link.l2.go = "exit";	
			}
			else
			{
				dialog.text = GetFullName(sld) + ", róla beszélsz?";
				Link.l1 = "Igen, róla.";
				Link.l1.go = "Hostess_NotChoice_agree";				
				Link.l2 = "Nem, nem róla van szó.";
				Link.l2.go = "Hostess_Choice_2";
				npchar.quest.choiceIdx = sld.index;
			}
		break;
		
        case "Hostess_Choice_2":
			dialog.text = "Akkor talán még egyszer meg kellene mondania a nevét, és talán rájövök, hogy kirôl beszél.";
			Link.l1.edit = 9;
			Link.l1 = "";
			Link.l1.go = "Hostess_Choice_1";
			Link.l2 = "Talán. Jobb lenne, ha még egyszer megkérdezné a nevét, csak a biztonság kedvéért. Majd késôbb beszélünk errôl.";
			Link.l2.go = "exit";	
		break;
		//==> команда
		case "ForCrew":
			dialog.text = "Hmm... Szeretnék segíteni a srácoknak 'leengedni egy kis gôzt'? Tudod, ez az én létesítményem jó hírû, és nekem vannak a legjobb lányaim. De ismerek néhány kikötôi szajhát, és ôk szívesen kedveskednek a matrózoknak. Ez önnek " + FindRussianMoneyString(GetCrewQuantity(pchar)*crewWhoreCost) + "költségébe fog kerülni.";			
			link.l1 = "Rendben, egyetértek.";
			link.l1.go = "ForCrew_1";
			link.l2 = "Gondolom, anélkül is boldogulnak...";
			link.l2.go = "exit";
		break;
		
		case "ForCrew_1":
		    if (sti(Pchar.money) >= GetCrewQuantity(pchar)*crewWhoreCost && GetCrewQuantity(pchar)>0)
		    {
		        AddMoneyToCharacter(Pchar, -makeint(GetCrewQuantity(pchar)*crewWhoreCost));
	            AddCrewMorale(Pchar, 10);
				ChangeCharacterComplexReputation(pchar,"authority", 1);
	            LAi_Fade("", "");
                AddTimeToCurrent(5 + rand(1), rand(30));
			    DialogExit();
		    }
		    else
		    {
		        dialog.text = "Nem az én dolgom, de úgy gondolom, hogy elôször is elég pénzt kellene keresni ahhoz, hogy legénységet alkalmazzanak, és csak azután aggódni a szelleméért.";
			    link.l1 = "Valószínûleg igazad van...";
			    link.l1.go = "exit";
		    }
		break;
		
		case "Woman_FackYou":
			dialog.text = "Kedvesem, mit csinálsz?! Pedig rendes kapitánynak tûntél... Ezúttal nem fogsz 'fly' menekülni, szépfiú. Az ôrök levágják a szárnyaidat...";
			link.l1 = "Fogd be, vén banya.";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
		break;
		
		//поиски кольца губернатора
		case "TakeMayorsRing_H1":
			dialog.text = "Nem találtam gyûrût.";
			link.l1 = "És a lányaid?";
			link.l1.go = "TakeMayorsRing_H2";
		break;
		
		case "TakeMayorsRing_H2":
			dialog.text = "Ôk sem. Ha egy vendég elfelejt vagy elveszít valamit, a lányaim elhozzák nekem. De a kormányzó gyûrûjét senki sem hozta el nekem.";
			link.l1 = "Értem... De lehet, hogy úgy döntöttek, hogy megtartják maguknak?";
			link.l1.go = "TakeMayorsRing_H3";
		break;
		
		case "TakeMayorsRing_H3":
			dialog.text = "Nem valószínû. A lányok megtarthatják a vásárlóktól kapott ajándékokat, de ez minden.";
			link.l1 = "Értem. Nos, köszönöm, " + npchar.name + ".";
			link.l1.go = "exit";
		break;
		
		case "Hostess_inSexRoom":
			dialog.text = "Ó, hát itt vagy...";
			link.l1 = "Itt vagyok, hölgyem!";
			link.l1.go = "exit";
			pchar.quest.SexWithHostess_null.over = "yes"; //нулим таймер на не пришёл
			NextDiag.TempNode = "First time";
			if (CheckAttribute(pchar, "questTemp.RomNaTroih_Pogovoril"))
			{
				sld = CharacterFromID(pchar.RomNaTroih_Shluha);
				dialog.text = "" + sld.name + "! Hôsöm, látom, hogy nem vesztegetted az idôdet odalent!";
				link.l1 = "Remélem, megbocsátja nekem ezt a gyengeséget, királynôm?";
				link.l1.go = "RomNaTroih_2";
			}
			AddDialogExitQuestFunction("SexWithHostess_fack");
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			DeleteAttribute(pchar, "questTemp.RomNaTroih");
            if(IsEquipCharacterByArtefact(pchar, "totem_03")) 	
			{
				AddCharacterHealth(pchar, 10);
				AddCharacterMaxHealth(pchar, 1.0);
			}
			else AddCharacterHealth(pchar, 5);
		break;
		
		// ================================== рядовой состав =======================================
        case "Horse_talk":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar, 
					LinkRandPhrase("Jobb, ha elhagyod az intézményt!", "A város összes ôre téged keres! Jobb, ha elmész...", "Nagy zûrt csináltál, és most itt bukkansz fel?! Nem, ezúttal nem..."), 
					LinkRandPhrase("Tûnj el!", "Mocskos gyilkos, takarodj innen! Ôrség!", "Nem félek tôled,"+ GetSexPhrase("gazember","patkány") +"! Hamarosan felakasztanak az erôdünkben, nem jutsz messzire..."));
				link.l1 = NPCharRepPhrase(pchar,
					RandPhraseSimple("Heh, a riasztó nekem sosem jelent problémát...", "Soha nem fognak elkapni."), 
					RandPhraseSimple("Heh, milyen hülye kurva vagy...", "Fogd be a szád, kurva, vagy én fogom be valami mással..."));
				link.l1.go = "exit";
				break;
			}
			dialog.text = NPCStringReactionRepeat("Hello, " + GetAddress_Form(NPChar) + ""+ GetSexPhrase("",", hee-hee...") +". Látni kell a hölgyet és ki kell tölteni a rendelést.", 
				"Már megint te? Kérem, beszéljen az ôrrel. Az irodájában van.", 
				"Nézze, " + GetAddress_Form(NPChar) + ""+ GetSexPhrase(", remélem, hogy más dolgokban is olyan makacs, mint a beszédben... Ismét","Ismét") +" kérem, hogy keresse fel a létesítmény tulajdonosát.", 
				"Ó, " + GetAddress_Form(NPChar) + ""+ GetSexPhrase(", hát nem vagy te egy makacs!",", Hee-hee... Makacs vagy, ugye?") +" Látnia kell a hölgyet és ki kell töltenie a rendelést.", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Rendben, "+ GetSexPhrase("szépség, ","") +"megvan"+ GetSexPhrase("","") +".", "Igen, persze...",
                      ""+ GetSexPhrase("Ne legyenek kétségeid, szépségem, olyan makacs és erôs vagyok, mint egy bika!","Igen, igen...") +"", ""+ GetSexPhrase("Ó, a fenébe, biztos kihagytam valamit... Sajnálom, kedvesem.","Jól van, rendben.") +"", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			Link.l2 = "És hol van?";
			Link.l2.go = "Horse_1";
			Link.l3 = LinkRandPhrase(""+ GetSexPhrase("Ó, szépségem, fogadok, hogy belefulladnék a szemeidbe...","Gyönyörû vagy, bébi!") +"", ""+ GetSexPhrase("Tudod, még sosem találkoztam ilyen gyönyörû nôvel!","Tudod, még sosem találkoztam ilyen kedves csajjal!") +"", ""+ GetSexPhrase("Drágám, gyönyörû vagy!","A fenébe, már annyira untam azokat a parasztokat... És te olyan bájos vagy!") +"");
			if (!CheckAttribute(npchar, "quest.choice"))
			{
				Link.l3.go = "Horse_2";
			}
			else
			{
				Link.l3.go = "HorseChoice_" + npchar.quest.choice;
			}
			//-->> квест поиска кольца мэра
			if (pchar.questTemp.different == "TakeMayorsRing" && pchar.questTemp.different.TakeMayorsRing.city == npchar.city && GetNpcQuestPastDayWOInit(npchar, "TakeMayorsRing") > 7)
			{
				link.l5 = LinkRandPhrase("Figyelj, "+ GetSexPhrase("szépség","drága") +", nem találtál itt véletlenül egy jegygyûrût? Egy férfi úgy tûnik, hogy elvesztette...", 
					"Drágám, nem láttál itt egy jegygyûrût vagy valami hasonlót?", 
					"Figyelj, "+ GetSexPhrase("cicám","bébi") +", nem láttál errefelé jegygyûrût?");
				link.l5.go = "TakeMayorsRing_S1";
				SaveCurrentNpcQuestDateParam(npchar, "TakeMayorsRing");
			}
			//<<-- квест поиска кольца мэра
			
			// Addon 2016-1 Jason пиратская линейка
			if (pchar.location == "santodomingo_brothel" && CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "jewelry_1" && npchar.id == "HorseGen_"+reload_location_index+"_2")
			{
				link.l6 = "Szia, édesem. Marcus Tyrex küldött, nézd meg ezt a borostyán nyakláncot...";
				link.l6.go = "mtraxx";
			}
			NextDiag.TempNode = "Horse_talk";
		break;
		
        case "Horse_1":
			dialog.text = "Az irodájában van. Innen az utcai kijárattal szemben lévô ajtón keresztül, vagy a ház másik oldalán lévô utcán keresztül juthat oda. A neve " + characters[GetCharacterIndex(npchar.city + "_Hostess")].name + ".";
			Link.l1 = "Értem, "+ GetSexPhrase("édesem","drágám") +", köszönöm.";
			Link.l1.go = "exit";			
		break;
		
        case "Horse_2":
			if (rand(1))
			{
				dialog.text = LinkRandPhrase("Jaj, de jó ilyet hallani! Hé, jelenleg szabad vagyok, szóval ha engem választasz, nem fogod megbánni...", "Tényleg így gondolod? Tudod, ez olyan aranyos... Figyelj, jelenleg szabad vagyok, szóval engem választhatsz."+ GetSexPhrase(" Ígérem neked a szerelem tengerét és a simogatás óceánját...","") +"", ""+ GetSexPhrase("Gondolod? Ó, nagyon hízelgô. Tudod, ritkán hallok ilyen bókokat...","Ó, kislányom... ha tudnád, mennyire elegem van a parasztokból...") +" Hé, figyelj, most éppen szabad vagyok, úgyhogy nyugodtan választhatsz engem, hogy boldoggá tegyelek. Nem fogok csalódást okozni, ígérem...");
				if (CheckAttribute(pchar, "questTemp.RomNaTroih") && !CheckAttribute(pchar, "questTemp.RomNaTroih_Pogovoril"))
				{
					link.l1 = "Kedvesem, pontosan ezt akartam tenni! Milyen szerencse, hogy a háziasszonya már elintézett egy privát találkozót velem az emeleten. Szeretne csatlakozni?";
					Link.l1.go = "RomNaTroih_1";
					pchar.questTemp.RomNaTroih_Pogovoril = true;
					break;
				}
				link.l1 = "Nos, akkor téged választalak!";
				Link.l1.go = "Horse_3";		
				Link.l2 = ""+ GetSexPhrase("Nem, ez csak egy bók volt egy kedves hölgynek","Ez csak egy bók volt") +".";
				Link.l2.go = "exit";
				npchar.quest.choice = 0; //был базар, но ГГ потом отказался
			}
			else
			{
				dialog.text = LinkRandPhrase(""+ GetSexPhrase("Tudod, mit mondok, édesem? Nincs szükségem erre az olcsó beszédre. Csinálj üzletet, vagy menj el!","Csak ez hiányzott! Bókok a nôktôl!") +"", ""+ GetSexPhrase("Te is azok közé tartozol, akik szerint a nôk a fülükkel szeretnek? Nos, kedvesem, ez egyszerûen nem igaz. Ha engem akarsz, akkor fizess a madame-nak, és ments meg az üres szavaidtól.","Lass, ne pazarold magad üres fecsegésre. Ha komolyan gondolod az üzletet - akkor fizess...") +"", ""+ GetSexPhrase("Ó, még egy érzéki szeretô... Csak fizess és a tiéd vagyok. Ilyen egyszerû az egész, mindenféle szelíd ostobaság nélkül!","Mi van veled, drágám? Ha kényeztetni akarod magad a gyönyörökben, akkor csak fizess, és hagyd abba ezt a sok ostobaságot!") +"");
				link.l1 = "Ó, micsoda fogás!";
				Link.l1.go = "exit";
				npchar.quest.choice = 2; //ГГ послали
			}
		break;
		
        case "Horse_3":
			dialog.text = characters[GetCharacterIndex(npchar.city + "_Hostess")].name + " minden formalitást elvégez a kabinetjében. Menjen el hozzá"+ GetSexPhrase(", hôsöm,","") +" és mondja ki a nevem - " + npchar.name + ". Várni fogok rád...";
			Link.l1 = "Értem, drágám, hamarosan visszajövök...";
			Link.l1.go = "exit";
			npchar.quest.choice = 1; //она согласная
			SetNPCQuestDate(npchar, "quest.choice");
		break;
		
        case "Horse_4": 
			dialog.text = NPCStringReactionRepeat("Ön már fizetett.", 
				"Mondtam neked 'menj fel'.", 
				"fel, fiatalember.", 
				"Egyesek olyan lassan gondolkodnak...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Igen, tudom.", "Emlékszem.",
                      "Ó, ne ismételd magad, emlékszem.", "Hmm, hogy érted?.", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "Horse_4";
		break;
		
		//===>> реакция на попытки пофлиртовыть, если флирт уже был
        case "HorseChoice_0": 
			if (!CheckAttribute(npchar, "quest.sexHappend"))
			{
				dialog.text = NPCStringReactionRepeat("Csak nem egészen értem magát."+ GetSexPhrase(" Elôször bókolsz, aztán visszalépsz a szavaidtól. Milyen furcsa egy típus...","") +"", 
					"Már megint bókolsz?.", 
					"Az ôr az irodájában van. Megvan?", 
					"Nem szabad sértegetnünk a vásárlóinkat, de te tényleg csak kérdezed"+ GetSexPhrase("","") +"...", "block", 1, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Csak úgy történt, ahogy történt...", "Rendben, meglesz.",
						"Igen, értem.", "Bocsáss meg, szerelmem.", npchar, Dialog.CurrentNode);
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Köszönöm a bókot. Ha el akarsz vinni, csak menj és keresd meg a hölgyet. A szokásos üzlet.";
				Link.l1 = "Értem, értem.";
				Link.l1.go = "exit";
			}
		break;
		
        case "HorseChoice_1": 
			if (!CheckAttribute(npchar, "quest.sexHappend"))
			{
				if (!CheckNPCQuestDate(npchar, "quest.choice"))
				{
					dialog.text = NPCStringReactionRepeat(""+ GetSexPhrase("Kedvesem, már mindent megbeszéltünk. ","") +"Ne várakoztass meg túl sokáig...", 
						""+ GetSexPhrase("Hmm... Figyelj, kedvesem, én","én") +" nagyon szépnek találom a szavaidat, meg minden, de nem térnél a tárgyra...", 
						"Talán megbeszélhetnéd ezt a madame-mal, ugye?", 
						"Hm... Nem is tudom, mit mondjak...", "block", 1, npchar, Dialog.CurrentNode);
					link.l1 = HeroStringReactionRepeat("Soha nem tennék ilyet, várjatok meg!", "Certainly!",
							"Természetesen, ahogy mondod!", "Már rohanok is a madame-odhoz...", npchar, Dialog.CurrentNode);
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = "Vártam rád, de nem jöttél és nem vittél el... Nem mondhatnám, hogy tetszett...";
					Link.l1 = "Tudod, csak úgy történt, ahogy történt...";
					Link.l1.go = "exit";
					npchar.quest.choice = 0; //был базар, но ГГ потом отказался
				}
			}
			else
			{
				dialog.text = "Ó, már megint te vagy az én "+ GetSexPhrase("dicsô korzóm","szép lány") +"! Ha megint engem akarsz, gyere el az asszonyhoz, nem fogsz csalódni..."+ GetSexPhrase(" Egyébként felismertelek kedves, de nekünk azt mondták, hogy minden ügyféllel egyformán kell beszélni, nem lehet kedvenc, elnézést kérek érte...","") +"";
				Link.l1 = "Ne aggódj, drágám. Várj rám csak egy kicsit, "+ GetSexPhrase("cukorfalat","cukorfalat") +", és hamarosan újra találkozunk négyszemközt.";
				Link.l1.go = "exit";
				Link.l2 = "Nagyon szép, hogy emlékszel rám, de ezt az éjszakát nem tölthetem veled, sajnálom.";
				Link.l2.go = "HorseChoice_1_Add";
			}
		break;
		
        case "HorseChoice_2": 
			if (!CheckAttribute(npchar, "quest.sexHappend"))
			{
				dialog.text = NPCStringReactionRepeat("Tehát,"+ GetSexPhrase(" kedves barátom,","") +" jobb, ha az üzleti életben foglalatoskodsz. Hasznosabb lesz, mintha nem csinálnál semmit.", 
					""+ GetSexPhrase("Hmm, miért ","miért") +" mondod újra és újra ugyanazokat a dolgokat?", 
					"Hé, ez nem elég?!", 
					"Hm, micsoda meglepetés, semmi új"+ GetSexPhrase(", megint ezek a hülye próbálkozások a bájolgásra! Ha szexelni akarsz velem, menj a madame-hoz, te tollas!","...") +"", "block", 1, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Igen, hallottam"+ GetSexPhrase("","") +" , hogy...", "Hmm, így alakul...",
						"Hmm, talán ez elég, vagy talán nem ...", "Vigyázz a nyelvedre"+ GetSexPhrase(", kecske","") +"...", npchar, Dialog.CurrentNode);
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Ó, már megint te vagy az! "+ GetSexPhrase("És megint azok a hülye bókok. Semmi sem változik ebben a világban... Ha ","Csak emlékeztetôül: ha ") +"akarsz"+ GetSexPhrase("jól érezni magad","jól érezni magad") +" velem, fizess a létesítmény tulajdonosának. Nem érdekelnek a szavaid.";
				Link.l1 = "Ez nem nagy meglepetés...";
				Link.l1.go = "exit";
			}
		break;
		
        case "HorseChoice_1_Add":
			dialog.text = "Nem mondhatom, hogy boldoggá tett... Kár érte.";
			Link.l1 = "Sajnálom...";
			Link.l1.go = "exit";
			npchar.quest.choice = 0;
		break;
		
		//===>> секс
        case "Horse_ReadyFack":
			// Addon 2016-1 Jason пиратская линейка
			if (pchar.location == "SantoDomingo_Brothel_room" && CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "jewelry_2" && npchar.name == "Gabriela")
			{
				dialog.text = "Ah, végre megérkeztél! Remek! Szabadon beszélhetünk, senki sem figyel...";
				Link.l1 = "Szóval a spanyol volt az, aki a kék borostyánt adta neked?";
				Link.l1.go = "mtraxx_2";
				DelLandQuestMark(npchar);
				DelMapQuestMarkCity("SantoDomingo");
				break;
			}
			if (!CheckAttribute(npchar, "quest.choice")) npchar.quest.choice = 0;
			switch(npchar.quest.choice)
			{
				case "0":
					dialog.text = RandPhraseSimple("Nagyon örülök, hogy látlak. "+ GetSexPhrase("Szóval, mi lesz a következô lépés?","Mi lenne, ha jól éreznénk magunkat?") +"", "Ne légy szégyenlôs"+ GetSexPhrase(", érezd magad otthon legalább két órára.",". Képes leszek szórakoztatni, ne legyenek kétségeid.") +"");
					Link.l1 = RandPhraseSimple("Nem hiszem, hogy unalmas lesz...", ""+ GetSexPhrase("Érezzük jól magunkat, bébi!","Ne vesztegessük az idôt!") +"");
				break;
				case "1":
					dialog.text = "Ó, már megint te vagy az, az én "+ GetSexPhrase("dicsôséges korzóm! Ígértem neked valamit, és kész vagyok megtartani a szavamat","szép lány! Soha nem fogod elfelejteni a következô két órát") +"...";
					Link.l1 = "Ez csábítóan hangzik...";	
				break;
				case "2":
					dialog.text = "Ohh, itt vagy, végre. Ne vesztegessük az idôt!";
					Link.l1 = ""+ GetSexPhrase("Ne csináljuk, punci...","Most pedig mutasd meg, mit tudsz...") +"";
				break;
			}
			if (pchar.sex == "woman")
			{
				Link.l1.go = "exit";
				NextDiag.TempNode = "Horse_AfterSex";
				AddDialogExitQuest("PlaySex_1");
				// кач от борделя
				if (CheckNPCQuestDate(pchar, "BrothelSex"))
				{
					if(IsEquipCharacterByArtefact(pchar, "totem_03")) 	AddCharacterHealth(pchar, 10);
					else 												AddCharacterHealth(pchar, 5);
					SetNPCQuestDate(pchar, "BrothelSex");
				}
				// изменение статусов
				ChangeCharacterComplexReputation(pchar,"nobility", -1);
				AddCharacterExpToSkill(pchar, "Leadership", 30);
				AddCharacterExpToSkill(pchar, "FencingS", -15);
				AddCharacterExpToSkill(pchar, "Pistol", -15);
			}
			else
			{
				pchar.horsekiss = npchar.id;
				Link.l1.go = "Horse_Kiss";
			}
			//--> кол-во посещений
			if (!CheckAttribute(npchar, "quest.sexHappend")) npchar.quest.sexHappend = 1;
			else npchar.quest.sexHappend = sti(npchar.quest.sexHappend) + 1;
			pchar.GenQuest.BrothelCount = sti(pchar.GenQuest.BrothelCount) + 1; // для Данек
			Achievment_SetStat(23, 1);
			//<-- кол-во посещений
			str = npchar.city;
			pchar.quest.(str).win_condition.l1 = "ExitFromLocation";
			pchar.quest.(str).win_condition.l1.location = pchar.location;
			pchar.quest.(str).win_condition = "Brothel_checkVisitTime";
			pchar.questTemp.HorseQty = sti(pchar.questTemp.HorseQty) + 1; //счетчик
		break;
		
		case "Horse_Kiss":
			DialogExit();
			
			StartQuestMovie(true, false, true);
			LAi_SetActorType(pchar);
			LAi_Fade("Horse_Kiss", "");
		break;

        case "Horse_AfterSex":
			if (CheckAttribute(pchar, "questTemp.ReasonToFast") && pchar.questTemp.ReasonToFast == "Begin")
			{
				dialog.text = "Kapitány, miért vagy ilyen csendes?";
				link.l1 = LinkRandPhrase("Nos, ez vagyok én.", "Majd legközelebb beszélünk.", RandPhraseSimple("Nem fizetek a beszélgetésért.", "De te, "+ GetSexPhrase("szépség","drága") +", nem voltál olyan csendes egész idô alatt."));
				link.l1.go = "exit";
				link.l2 = ""+ GetSexPhrase("Egyszerûen nagyszerû voltál, majdnem elvesztettem az eszem! Nagyon ritka alkalom, amikor egy nô egyszerre ilyen szép és dögös","Ohh, te aztán tudod, hogyan kell egy nônek örömet szerezni... Annyira izgatott vagyok.") +".";
				link.l2.go = "Horse_ReasonToFast_1";
			}
			else
			{
				switch(npchar.quest.choice)
				{
					case "0":
						dialog.text = LinkRandPhrase("Tetszett?", "Szóval, mit mondhatsz? Minden rendben volt?", "Szóval,"+ GetSexPhrase(" corsair, van, minden"," minden") +" rendben?");
						Link.l1 = RandPhraseSimple(""+ GetSexPhrase("Természetesen minden rendben","Ön biztosan tudja a kötelességeit") +".", ""+ GetSexPhrase("Minden rendben van, bébi","Tudod, nagyon örültem") +".");
						Link.l1.go = "exit";
					break;
					case "1":
						dialog.text = LinkRandPhrase("Szóval, betartottam az ígéretemet?", "Szóval,"+ GetSexPhrase(" tetszettem neked",", tetszett neked") +"?", "Remélem, "+ GetSexPhrase("elégedett voltál, mert én nagyon-nagyon elégedett vagyok","elégedett voltál, mert mindent megtettem") +"...");
						Link.l1 = RandPhraseSimple("Igen, nagyon tetszett.", ""+ GetSexPhrase("Nagyon jól éreztük magunkat, gyönyörû voltál!","Minden egyszerûen fantasztikus volt!") +"");	
						Link.l1.go = "exit";
					break;
					
					case "2":
						dialog.text = RandPhraseSimple("Nos, ennyi volt, menned kell.", "Az ön ideje lejárt,"+ GetSexPhrase(" kapitány,","") +".");
						Link.l1 = RandPhraseSimple("Igen, viszlát...", "Viszlát és köszönöm...");
						Link.l1.go = "exit";
					break;
				}
				NextDiag.TempNode = "Horse_AfterSex_2";
			}	
		break;
		
        case "Horse_AfterSex_2":
			if(CheckAttribute(pchar,"GenQuest.EncGirl") && pchar.GenQuest.EncGirl == "Bag_BrothelRoom" && !CheckCharacterItem(pchar, "leather_bag"))
			{
				dialog.text = "Szóval, hogy tetszett itt?";
				link.l1 = "Mondd csak szépségem, nem láttál sehol egy markolózsákot?";
				link.l1.go = "EncGirl_GetBag";
			}
			else
			{
				dialog.text = LinkRandPhrase("Ugorj be néha újra...", "Viszlát. Bármikor várunk rád...", "Örülünk, ha újra itt találkozunk...");
				Link.l1 = "Rendben...";
				Link.l1.go = "exit";
				NextDiag.TempNode = "Horse_AfterSex_2";
			}	
		break;
		
		case "EncGirl_GetBag":
			dialog.text = "Az a barna mellkas volt az a markolat?";
			link.l1 = "Igen, valami ilyesmi...";
			link.l1.go = "EncGirl_GetBag1";	
		break;
		
		case "EncGirl_GetBag1":
			dialog.text = "Mivel a láda tulajdonosa nem jelent meg, a madame elvitte a budoárjába.";
			link.l1 = "Köszönöm, bébi. Viszlát.";
			link.l1.go = "exit";
			pchar.GenQuest.EncGirl = "Bag_BrothelHostess";
			NextDiag.TempNode = "Horse_AfterSex_2";
		break;
		
		// --> генератор - "A reason to hurry"
		case "Horse_ReasonToFast_1":
			dialog.text = "Akkor ugorj be bármikor, mindig örülök, ha látlak. Te olyan "+ GetSexPhrase("szelíd vagy, nem olyan, mint azok a többiek","szelíd, nem olyan, mint azok a parasztok") +" nincs köszönés, nincs búcsúzkodás, és gyakran még bántani is próbálnak....";
			link.l1 = "Hogy érted ezt?";
			link.l1.go = "Horse_ReasonToFast_2";
		break;
		
		case "Horse_ReasonToFast_2":
			pchar.questTemp.ReasonToFast.speakHorse = true;
			dialog.text = "Volt egy fôtörzsôrmester elôtted. Általában nem látogat meg minket, de most valami ördög hozta ide. Ráadásul engem választott... Nyögdécselt, miközben néhány percig fölöttem volt, majd alacsony képzettségûnek nevezett, és elsietett valami öbölbe. Olyan gyorsan lelépett, hogy majdnem otthagyta a nadrágját, ha-ha-ha-ha...";
			link.l1 = "Nem tudod, "+ GetSexPhrase("szépség","drágám") +", kik is a férfiak valójában? Azt mondta a feleségének, hogy elmegy a bordélyházba 'inspekcióra', aztán azt mondta a szeretôjének, hogy siet a feleségéhez, de az egyetlen dolog, amit mindig is akart, hogy járôrözni menjen abba az öbölbe. "+ GetSexPhrase("Ha-ha-ah!..","Ha-ha-ha!") +"";
			link.l1.go = "Horse_ReasonToFast_3";
		break;
		
		case "Horse_ReasonToFast_3":
			NextDiag.TempNode = "Horse_AfterSex_2";			
			ReOpenQuestHeader("ReasonToFast");
			AddQuestRecord("ReasonToFast", "1");
			pchar.questTemp.ReasonToFast = "SpeakHorse";
			pchar.questTemp.ReasonToFast.GuardNation = npchar.nation;
			pchar.questTemp.ReasonToFast.cantSpeakOther = true;
			ReasonToFast_InitVariables();
			string TargetLocation = SelectQuestShoreLocation();
			if(TargetLocation != "")
			{ 
				Locations[FindLocation(TargetLocation)].DisableEncounters = true;
				LAi_LocationDisableOfficersGen(TargetLocation, true);
				pchar.quest.ReasonToFast_MeetPatrol.win_condition.l1 = "location";
				pchar.quest.ReasonToFast_MeetPatrol.win_condition.l1.location = TargetLocation;
				pchar.quest.ReasonToFast_MeetPatrol.function = "ReasonToFast_MeetPatrolShore";
				pchar.questTemp.ReasonToFast.PatrolLocation = TargetLocation;
			}	
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();		
		break;
		// <-- генератор "A reason to hurry"
		
		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//поиски кольца мэра
		case "TakeMayorsRing_S1":
			if (CheckAttribute(pchar, "questTemp.different.TakeMayorsRing.item")) //если валяется в итемах
			{
				dialog.text = LinkRandPhrase("Nem, drágám, sajnálom, de nem. Szívesen segítenék neked, de nem tudok.", 
					"Nem, "+ GetSexPhrase("jóképû","ifjú hölgy") +", nem láttam semmilyen gyûrût...", 
					"Sajnálom, de nem. Nem láttam semmilyen gyûrût.");
				link.l1 = "Kár... Nos, azért köszönöm.";
				link.l1.go = "exit";
			}
			else
			{
				if (npchar.id == "HorseGen_"+reload_location_index+"_1")
				{
					dialog.text = "A kormányzó gyûrûjére gondol?";
					link.l1 = "Pontosan, bébi!";
					link.l1.go = "TakeMayorsRing_S2";
				}
				else
				{
					dialog.text = LinkRandPhrase("Nem, drágám, sajnálom, de nem. Szívesen segítenék neked - de nem tudok.", 
						"Nem, "+ GetSexPhrase("jóképû","ifjú hölgy") +", nem láttam semmilyen gyûrût...", 
						"Sajnálom, de nem. Nem láttam semmilyen gyûrût.");
					link.l1 = "Kár... Nos, azért köszönöm.";
					link.l1.go = "exit";
				}
			}
		break;

		case "TakeMayorsRing_S2":
			dialog.text = "Sajnálom, de a gyûrût ajándékba kaptam, így nem vagyok köteles visszaadni.";
			link.l1 = "Ajándékba?! És ki adta neked?";
			link.l1.go = "TakeMayorsRing_S3";
		break;
		
		case "TakeMayorsRing_S3":
			dialog.text = "Természetesen magától a kormányzótól!";
			link.l1 = "De ô... enyhén szólva is részeg volt. Nem emlékszik semmire.";
			link.l1.go = "TakeMayorsRing_S4";
		break;
		
		case "TakeMayorsRing_S4":
			dialog.text = "És nekem mi közöm van hozzá? Ha részeg volt, az az ô problémája, nem az enyém!";
			link.l1 = "Tényleg veszekedni akarsz vele? Ez egy jegygyûrû, és ezt te is tudod... Csak add vissza, egy ilyen apróság nem éri meg a fáradságot.";
			link.l1.go = "TakeMayorsRing_S5";
		break;
		
		case "TakeMayorsRing_S5":
			if (rand(1) && sti(pchar.money)>5000)
			{
				dialog.text = "Nos, visszaadom a gyûrût, de te fizetsz nekem ötezer pezót.";
				link.l1 = "Rendben, fogd a pénzed, és add ide a gyûrût.";
				link.l1.go = "TakeMayorsRing_S6";
			}
			else
			{
				dialog.text = "Ó, hát jó. Hadd legyen az övé!";
				link.l1 = "Az biztos, drágám!";
				link.l1.go = "exit";
				GiveItem2Character(pchar, "MayorsRing");
				pchar.questTemp.different.TakeMayorsRing = "HorseTakenRing";
				AddQuestRecord("SeekMayorsRing", "3");
				AddQuestUserData("SeekMayorsRing", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
				AddQuestUserData("SeekMayorsRing", "sName", GetFullName(npchar));
			}
		break;
		
		case "TakeMayorsRing_S6":
			dialog.text = "Tessék...";
			link.l1 = "Rendben, akkor. Köszönöm a segítséget, drágám.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -5000);
			GiveItem2Character(pchar, "MayorsRing");
			pchar.questTemp.different.TakeMayorsRing = "HorseTakenRingMoney";
			AddQuestRecord("SeekMayorsRing", "2");
			AddQuestUserData("SeekMayorsRing", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData("SeekMayorsRing", "sName", GetFullName(npchar));
		break;
		
		//Jason --> Заносчивый аристократ
		case "Badboy":
			pchar.GenQuest.Badboy.Brothel.City = npchar.city; //город квестодателя
			//log_info(pchar.GenQuest.Badboy.Brothel.City); // patch-6
			pchar.GenQuest.Badboy.Brothel.nation = npchar.nation;
			pchar.GenQuest.Badboy.Brothel.Name = GenerateRandomName_Generator(sti(npchar.nation), "man");
			dialog.text = "Tudja, van egy kellemetlen ügyfelünk - "+pchar.GenQuest.Badboy.Brothel.Name+". És nagyon idegesít minket minden alkalommal, amikor jön! Elôször a kocsmában rúg be, aztán átjön ide, felszed egy lányt, és heves felháborodást csinál\nés a legrosszabb, hogy nemesi származású! Kormányzónk távoli rokona, így kénytelenek vagyunk elszenvedni minden kicsapongását. Talán rá tudnád venni azt a fiatal pimasz férfit, hogy... hát... egy kicsit lenyugodjon... hogy ne látogassa tovább a létesítményemet?";
			link.l1 = "A kormányzó rokona, azt mondod? Hmmm... Inkább nem akarok összetûzésbe kerülni a hatóságokkal. Nagyon sajnálom.";
			link.l1.go = "exit";
			link.l2 = "Azt hiszem, ezt el tudom intézni. Mondja csak, hol találom azt az ócskavasat?";
			link.l2.go = "Badboy_1";
		break;
		
		case "Badboy_1":
			dialog.text = "Ilyenkor általában már a kocsmában van. Ott berúg, aztán átjön látogatóba.";
			link.l1 = "Értem. Nos, valószínûleg ott találkozom vele.";
			link.l1.go = "exit";
			//создаем дебошира
			int iRank, iType, b;
			string sBlade, sPistol;
			if (sti(pchar.rank) < 6) iType = 0;
			if (sti(pchar.rank) >= 6 && sti(pchar.rank) < 16) iType = 1;
			if (sti(pchar.rank) >= 16) iType = 2;
			switch (iType)
			{
				case 0:
					iRank = 6;
					sBlade = "blade_12";
					sPistol = "pistol1";
					b = 25;
				break;
				case 1:
					iRank = sti(pchar.rank)+10;
					sBlade = "blade_09";
					sPistol = "pistol1";
					b = 65;
				break;
				case 2:
					iRank = sti(pchar.rank)+5;
					sBlade = "blade_14";
					sPistol = "pistol1";
					b = 40;
				break;
			}
			sld = GetCharacter(NPC_GenerateCharacter("Badboy", "citiz_"+(7+rand(1)), "man", "man", iRank, HOLLAND, -1, true, "citizen"));
			FantomMakeCoolFighter(sld, iRank, b, b, sBlade, sPistol, "bullet", makeint(iRank*5));
			sld.name = pchar.GenQuest.Badboy.Brothel.Name;
			sld.lastname = "";
			sld.dialog.FileName = "Quest\Other_quests_NPC.c";
			sld.dialog.currentnode = "Badboy";
			sld.greeting = "noble_male"; // patch-6
			LAi_SetLoginTime(sld, 15, 22);
			LAi_SetSitType(sld);
			FreeSitLocator(pchar.GenQuest.Badboy.Brothel.City + "_tavern", "sit1");
			ChangeCharacterAddressGroup(sld, pchar.GenQuest.Badboy.Brothel.City + "_tavern", "sit", "sit1");
			pchar.GenQuest.Badboy.Brothel.Type = iType; //запомним тип
			pchar.GenQuest.Badboy.Brothel = "true";
		break;
		
		case "Badboy_complete":
			dialog.text = "Ó, te aztán igazi férfi vagy, nem igaz? Mindig tudtam, hogy számíthatok rád...";
			link.l1 = "Mindig örülök, ha segíthetek egy ilyen kedves hölgynek és a... gyámjainak.";
			link.l1.go = "Badboy_complete_1";
		break;
		
		case "Badboy_complete_1":
			dialog.text = "Nem csak bátor vagy, hanem nagyon gáláns is. Különleges módon szeretném megköszönni neked - úgy, ahogy csak egy nô köszönheti meg egy férfinak. Ezt soha nem fogod elfelejteni, ígérem. Gyere fel, bátor tengerész...";
			link.l1 = "...";
			link.l1.go = "Badboy_complete_2";
		break;
		
		case "Badboy_complete_2":
			pchar.questTemp.different.HostessSex.city = pchar.GenQuest.Badboy.Brothel.City;
			AddDialogExitQuestFunction("SexWithHostess_goToRoom");
			SetTimerFunction("SexWithHostess_null", 0, 0, 1); 
			DialogExit();
			if (sti(pchar.GenQuest.Badboy.Brothel.Type) != 2)
			{
				DeleteAttribute(pchar, "GenQuest.Badboy");
			}
			else
			{
				pchar.quest.Badboy_Brothel.win_condition.l1 = "location";
				pchar.quest.Badboy_Brothel.win_condition.l1.location = pchar.GenQuest.Badboy.Brothel.City +"_town";
				pchar.quest.Badboy_Brothel.function = "Badboy_friends";
				DeleteAttribute(pchar, "GenQuest.Badboy.Continue"); // patch-6
			}
			SaveCurrentQuestDateParam("questTemp.Badboy");
			if (!CheckAttribute(pchar, "questTemp.RomNaTroih"))
			{
				pchar.questTemp.RomNaTroih = true;
			}
		break;
		// <-- Заносчивый аристократ
		
		//Португалец
		case "Portugal":
			dialog.text = "Van egy férfi, aki tartozik nekem egy kis pénzzel... Nem tudom, hogy mondjam...";
			link.l1 = "Nincs mit mondanom. Megkeresem, és az utolsó pezóig kirázom, csak egy pillantásért a te kifürkészhetetlen szemedbe! Csak mondd meg a nevét!";
			link.l1.go = "Portugal_1";
		break;
		
		case "Portugal_1":
			dialog.text = "Nem, nem, nem, nem értett meg helyesen, kapitány úr! Ez az ember... ne tegyen semmi rosszat vele. Csak emlékeztesse az adósságára. A neve Hugo Avendell, és gondolom, ott találja meg, ahol nagyon olcsó piát árulnak. Csak az Isten szerelmére, ne alkalmazzon rá erôszakot!\nCsak mondja... emlékeztesse, hogy megígérte, hogy fizet. Nem akarok kapcsolatba lépni az ôrrel, de vannak tiszti barátaim, úgyhogy mondja meg neki, hogy várok, és minden tiszteletem az övé, de legkésôbb holnap kénytelen leszek intézkedni. Csak emlékeztesse az ígéretére.";
			link.l1 = "Az ön szava az én törvényem, asszonyom. Örömmel teljesítem a kérését.";
			link.l1.go = "Portugal_2";
		break;
		
		case "Portugal_2":
			DialogExit();
			sld = InitHugo("Hugo","Avendell");
			FreeSitLocator("Marigo_tavern", "sit_front1");
			ChangeCharacterAddressGroup(sld, "Marigo_tavern", "sit", "sit_front1");
			AddLandQuestMark(sld, "questmarkmain");
			SetFunctionTimerCondition("Portugal_BeginOver", 0, 0, 2, false);
			pchar.questTemp.Portugal = "begin";
		break;
		
		case "Portugal_exit":
			dialog.text = "Köszönöm, kapitány. Remélem, hogy kellô óvatosságot fog tanúsítani.";
			link.l1 = "Ebben biztos vagyok, asszonyom. Most pedig engedje meg, hogy távozzak.";
			link.l1.go = "exit";
			sld = characterFromId("Avendel");
			sld.lifeday = 0;
			pchar.questTemp.Portugal = "end";
		break;
		
		case "Portugal_3":
			AddMoneyToCharacter(pchar, -10000);
			dialog.text = "Jaj, ne! Ne mondja, hogy valami szörnyûséget tett vele... Nem volt pénze, és én tudtam! Csak ugyanabban a kisvárosban nôttünk fel, soha nem fordulnék az ôrökhöz! Csak egy kicsit rá akartam ijeszteni... felrázni, mielôtt belefullad az üvegbe!";
			link.l1 = "Hmm... Mindazonáltal, itt a pénze. És ne aggódjon Hugo miatt, jól van... Legalábbis az lesz, ha kijózanodik.";
			link.l1.go = "Portugal_4";
		break;
		
		case "Portugal_4":
			dialog.text = "Ó, kapitány, maga ezt nem érti! Ô volt az egyik... nos, tudja, fejvadászoknak hívják ôket - zsoldosok, kalózok és rablók nyomába erednek, és kiiktatják ôket. De, finoman szólva sem volt a legszerencsésebb\nNem is olyan régen, végül elpártolt, elvesztette a legénységét és a hajóját, azóta nap mint nap a bögréje fenekén úszik. Én, a régi emlékezet kedvéért, megengedem neki, hogy néha idejöjjön. Most már olyan... olyan szánalmas. Ô volt a legjóképûbb férfi a mi városunkban, La Manche partján, és nézd meg most\nTudom, hogy ígért neked valamit, és te zsebbôl fizettél! Odaadom ezt a pénzt, csak ne tegyen vele semmi rosszat, könyörgöm, kapitány úr!";
			link.l1 = "Rendben, rendben, madame, értem. Tartsa meg a pénzt, a magáé. Ami a barátját illeti, ígérem, hogy nem fogom bántani. És most engedje meg, hogy távozzak, van egy kis dolgom. Én is örülök, hogy segíthettem egy ilyen gyönyörû hölgynek.";
			link.l1.go = "Portugal_5";
		break;
		
		case "Portugal_5":
			DialogExit();
			sld = characterFromId("Avendel");
			sld.dialog.currentnode = "Avendel_tavern_7";
			AddLandQuestMark(sld, "questmarkmain");
			pchar.questTemp.Portugal = "AvendelTavern";
		break;
		
		// Addon 2016-1 Jason пиратская линейка
		case "mtraxx":
            dialog.text = "Csitt, halkabban... Menj, kérd meg Lolita asszonyt, hogy randizzon velem. Aztán gyere fel az emeletre, ahol szabadon beszélgethetünk. És addig egy szót se... Hé, matróz, menj és fizess a Madame-nak, mielôtt hozzám érsz! (kuncog)";
			link.l1 = "Máris megyek, édesem...";
			link.l1.go = "mtraxx_1";
		break;
		
		case "mtraxx_1":
           DialogExit();
		   chrDisableReloadToLocation = false;
		   pchar.questTemp.Mtraxx = "jewelry_2";
		break;
		
		case "mtraxx_2":
			pchar.quest.Mtraxx_JewelrySDMOver.over = "yes"; //снять таймер
            dialog.text = "Nem, én nem. Elmondom az egész történetet, csak ne szakíts félbe.";
			link.l1 = "Csupa fül vagyok!";
			link.l1.go = "mtraxx_3";
		break;
		
		case "mtraxx_3":
            dialog.text = "Rendben. Körülbelül egy hete egy katonai hajó érkezett Santo Domingóba. Megsérült, vagy egy viharban, vagy egy harcban, így a javítás azonnal megkezdôdött, és a legénység az erôdbe költözött. A kapitánya azonban minden szabadidejét itt töltötte. Már két napja egyfolytában ivott és pihent az egyik lány kíséretében. Ô volt az, aki megszerezte a drágakövet, és nem is egyet. A végtelenségig dicsekedett vele - Lolita megengedi, hogy megtartsuk a vásárlókat' prezentál\nA buta lány nem is tudta az ajándék valódi értékét, én viszont rögtön felmértem. Amikor elmesélte, hogy a részeg kapitány egy borostyánnal teli hegyrôl dicsekedett, azonnal küldtem egy levelet Tyrexnek...";
			link.l1 = "";
			link.l1.go = "mtraxx_4";
		break;
		
		case "mtraxx_4":
            dialog.text = "A kapitány következô érkezésekor mindent úgy intéztem, hogy a kedvenc lánya egy másik ügyféllel volt elfoglalva, és megkaptam a 'munkát' magamnak. Megpróbáltam kiszedni belôle a koordinátákat, sajnos hiába. Csak azzal dicsekedett, hogy olyan gazdag lesz, mint Crassus, és visszamegy az Óvilágba\nEgy szót sem szólt a helyszínrôl. Csak annyit tudtam meg, hogy a hajóját megjavították, és Havannába hajózik, ahol majd megpróbál megszervezni egy küldetést a megfelelô irányba. Végül is nem ô a hajó tulajdonosa.";
			link.l1 = "Tehát most Havannában van?";
			link.l1.go = "mtraxx_5";
		break;
		
		case "mtraxx_5":
            dialog.text = "Két nappal ezelôtt hajnalban kihajózott. Maga itt a tengerész, maga számol.";
			link.l1 = "A kapitány neve, a hajó típusa és neve, bármi?";
			link.l1.go = "mtraxx_6";
		break;
		
		case "mtraxx_6":
            dialog.text = "Mi az, bolondnak nézel engem? A neve Esberdo Cabanas, a Cantavro kapitánya. Azt hiszem, a tengerészek szkúnernek hívják.";
			link.l1 = "És ez minden, amit tud?";
			link.l1.go = "mtraxx_7";
		break;
		
		case "mtraxx_7":
            dialog.text = "Mit akarsz még? Biztos vagyok benne, hogy Havanna elôtt utol tudod érni. De ne vesztegesd az idôt, nem hiszem, hogy hosszú pihenôt tart, mielôtt elhagyja Kubát a rejtekhelye felé, és akkor már veszett ügy. Ha jobban belegondolok, maradhatnál egy-két órát, végül is te fizettél érte.";
			link.l1 = "Jó érv, drágám. Két óra nem sokat számít...";
			// belamour legendary edition -->
			link.l1.go = "mtraxx_7S";
			link.l2 = "Majd máskor, drágám. Gondolj arra, hogy adj magadnak egy ebédszünetet. Menj el a templomba, vagy valami másra.";
			link.l2.go = "mtraxx_7NS";
			sTotalTemp = npchar.id;
			AddMapQuestMarkCity("Havana", false);
			AddLandQuestMark(characterFromId("Havana_PortMan"), "questmarkmain");
		break;
		
		case "mtraxx_7S":
            DialogExit();
			pchar.GenQuest.BrothelCount = sti(pchar.GenQuest.BrothelCount) + 1; // для Данек
			Achievment_SetStat(23, 1);
			//<-- кол-во посещений
			str = npchar.city;
			pchar.quest.(str).win_condition.l1 = "ExitFromLocation";
			pchar.quest.(str).win_condition.l1.location = pchar.location;
			pchar.quest.(str).win_condition = "Brothel_checkVisitTime";
			pchar.questTemp.HorseQty = sti(pchar.questTemp.HorseQty) + 1; //счетчик
			AddDialogExitQuest("PlaySex_1");
			// кач от борделя
			if (CheckNPCQuestDate(pchar, "BrothelSex"))
			{
				if(IsEquipCharacterByArtefact(pchar, "totem_03")) 	
				{
					AddCharacterHealth(pchar, 10);
					AddCharacterMaxHealth(pchar, 1.0);
				}
				else AddCharacterHealth(pchar, 5);
				SetNPCQuestDate(pchar, "BrothelSex");
			}
			// изменение статусов
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			AddCharacterExpToSkill(pchar, "Leadership", 30);
			AddCharacterExpToSkill(pchar, "FencingS", -15);
			AddCharacterExpToSkill(pchar, "Pistol", -15);
		break;
		
		case "mtraxx_7NS":
            DialogExit();
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			AddQuestRecord("Roger_1", "3");
			pchar.questTemp.Mtraxx = "jewelry_3";
			SetFunctionTimerCondition("Mtraxx_JewelryHavanaOver", 0, 0, 7, false); // таймер
			ChangeCharacterAddressGroup(npchar, "none", "", "");
			pchar.quest.mtr_jewelry_havana.win_condition.l1 = "location";
			pchar.quest.mtr_jewelry_havana.win_condition.l1.location = "Cuba2";
			pchar.quest.mtr_jewelry_havana.function = "Mtraxx_HavanaInfo";
			DeleteAttribute(pchar, "questTemp.Mtraxx.AffairOfHonor");
			DeleteAttribute(pchar, "questTemp.ZA.Block");
		break;
		// <-- legendary edition
		case "mtraxx_R":
            dialog.text = "O-ó... Milyen kár. És én még azt hittem, hogy itt nyaralsz. A lányaimnak annyira hiányoznak a bátor korzók. Rendben, akkor beszéljetek, mi a feladatotok?";
			link.l1 = "Marcus megbízott, hogy két napon át vezessek egy pokoli bulit a létesítményedben, igyam meg az összes bort és dugjak meg minden lányt. Mikor kezdjük?";
			link.l1.go = "mtraxx_R1";
		break;
		
		case "mtraxx_R1":
            dialog.text = "Ah, Charlie herceg, a humorod éles, mint a szablyád! Majdnem feldühítettél... Lányok! Vendégünk van, egy különleges vendég! Hozzatok bort és ételt!";
			if (sti(pchar.money) >= 31000)
			{
				link.l1 = "Hívjatok ide minden csinos lányt! Pihenni és szórakozni fogunk! Yo-ho-ho!...";
				link.l1.go = "mtraxx_R2";
			}
			else
			{
				link.l1 = "Várj egy percet, Janette. El kell hoznom az aranyat a hajómról neked és a hölgyeidnek. Egy perc múlva találkozunk!";
				link.l1.go = "exit";
				pchar.questTemp.Mtraxx.Retribution = "brothel_repeat";
				chrDisableReloadToLocation = false;
			}
		break;
		
		case "mtraxx_R2":
			AddMoneyToCharacter(pchar, -30000);
            dialog.text = "Bárcsak minden vendégünk olyan kedves, jóképû és nagylelkû lenne, mint te... Tökéletes kikapcsolódást biztosítunk. Lányok!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_RetributionInBrothel");
		break;
		// belamour ночной приключенец
		case "NA_Girl":
            dialog.text = "Ó, szóval van itt egy mûértô, hee hee ... Nocsak, nocsak, nekem is van egy ilyen lányom. De nem olcsó: "+makeint(pchar.GenQuest.NightAdventure_money)+" pezó."; 
			link.l1 = "Áll az alku.";
			link.l1.go = "NA_Girl_1";
		break;
		
		case "NA_Girl_1":
			AddMoneyToCharacter(pchar, -makeint(pchar.GenQuest.NightAdventure_money));
            dialog.text = "Ez nagyszerû, kedvesem. A Szerelem Papnôje várni fog rád az emeleten. Hidd el, nem fogod megbánni."; 
			link.l1 = "Már most sem bánom.";
			link.l1.go = "NA_Girl_2";
		break;
		
		case "NA_Girl_2":
			DialogExit();
			pchar.GenQuest.NightAdventureVar = "NightAdventure_NobleWhore"; 
			sld = characterFromId(pchar.GenQuest.NightAdventureId);
			sld.dialog.currentnode = "NightAdventure_NobleWhore_7";
		break;
		// <-- приключенец
		
		case "chicken_god":
			dialog.text = "Neked és Agueybana úrnak? Persze, hogy akarod. Az tízezer lesz, kapitány.";
			if (sti(pchar.money) >= 10000) {
				link.l1 = "Várj, ne így!... A francba! Mindegy, itt a fizetés.";
				link.l1.go = "chicken_god_pay";
			} else {
				link.l2 = "Kaphatok kölcsönt?";
				link.l2.go = "chicken_god_notpay";
			}
		break;
		
		case "chicken_god_pay":
			dialog.text = "Jó szórakozást, kapitány. Kérem, jöjjön vissza, ha nyitva vagyunk. A mi létesítményünk mindenféle kikapcsolódást biztosít a nemes férfiak és nôk számára.";
			link.l1 = "...";
			link.l1.go = "chicken_god_pay_1";
		break;
		
		case "chicken_god_pay_1":
			dialog.text = "";
			link.l1 = "Madam " + npchar.name + ", meg tudná legalább magyarázni, hogy mi folyik itt? Tudja egyáltalán a kormányzó, hogy egy hónapja egy bennszülött a vezetôjük? Egyetlen település sem élheti túl, ha egy bordélyház egy napra bezár, ezt megmondhatom!";
			link.l1.go = "chicken_god_pay_2";
		break;
		
		case "chicken_god_pay_2":
			dialog.text = "A szoba az öné, kapitány. És most, ha megbocsátanak...";
			link.l1 = "Elbûvölô. Viszlát, asszonyom.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_PayForRoom");
		break;
		
		case "chicken_god_notpay":
			dialog.text = "Miért, Uram, miért? Takarodjon innen! Menj el, menj el, nem bírom tovább! Szemétláda!";
			link.l1 = "Ez jól ment.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("ChickenGod_NotPayForRoom");
		break;
		
		//-->> Sinistra Ром на троих
		case "RomNaTroih_1":
			dialog.text = "Mhm... Általában nem szoktam ilyet csinálni... de hajlandó vagyok megkockáztatni önért. Ez az ön szerencsenapja, kapitány!";
			link.l1 = "Gyerünk!";
			link.l1.go = "exit";
			pchar.RomNaTroih_Shluha = npchar.id;
		break;
		
		case "RomNaTroih_2":
			dialog.text = "Mérges vagyok rád, kapitány... De megkegyelmezek neked, ha elég keményen dolgozol érte.";
			link.l1 = "Ó, úgy lesz. Nyissunk bort?";
			link.l1.go = "exit";
			Achievment_Set("ach_CL_105");
		break;
		//<<-- Sinistra Ром на троих
	}
}

ref GetFreeHorseRef(string City)
{
	ref rCharacter;
    int storeArray[8];
	int howStore = 0;
	for(int n=0; n<MAX_CHARACTERS; n++)
	{
		makeref(rCharacter, Characters[n]);
		if (rCharacter.location == City+"_Brothel" && CheckAttribute(rCharacter, "CityType") && rCharacter.CityType == "horse" && rCharacter.horse == "HorseStay")
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	if (howStore == 0) return &NullCharacter;
	return &characters[storeArray[rand(howStore-1)]];
}

ref CheckHorsesName(string City, int num)
{
	ref rCharacter;
	string sTemp, sSeeked;
	sSeeked = GetStrSmallRegister(dialogEditStrings[num]);
	for(int n=0; n<MAX_CHARACTERS; n++)
	{
		makeref(rCharacter, Characters[n]);
		if (rCharacter.location == City+"_Brothel" && CheckAttribute(rCharacter, "CityType") && rCharacter.CityType == "horse")
		{
			sTemp = GetStrSmallRegister(rCharacter.lastname + " " + rCharacter.name);
			if (findsubstr(sSeeked, sTemp , 0) != -1)
				return rCharacter;			
			sTemp = GetStrSmallRegister(rCharacter.lastname);
			if (findsubstr(sSeeked, sTemp , 0) != -1)
				return rCharacter;
			sTemp = GetStrSmallRegister(rCharacter.name);
			if (findsubstr(sSeeked, sTemp , 0) != -1)
				return rCharacter;
		}
	}
	return &NullCharacter;
}
