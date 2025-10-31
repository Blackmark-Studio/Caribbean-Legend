#include "DIALOGS\%language%\Rumours\Common_rumours.c"  //homo 25/06/06
string sProf;		//  без оффа hasert	
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag, arCapBase, arCapLocal;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	// доп повека
	if (!CheckAttribute(NPChar, "Portman")) NPChar.Portman = 0;
	if (!CheckAttribute(NPChar, "PortManPrice")) NPChar.PortManPrice = (0.06 + frnd()*0.1);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\PortMan\" + NPChar.City + "_PortMan.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 25/06/06

    int i, cn, iTemp;
    ref chref, compref; // без оффа hasert
	ref rRealShip;
    string attrL, sTitle, sCapitainId, s1;
	string sColony;
    
	String sLastSpeakDate = LastSpeakDate();
	
	// Warship 25.07.09 Генер "Сгоревшее судно". Даты отказа ГГ - если отказал, то предложит снова только на след сутки
	if(CheckAttribute(NPChar, "Quest.BurntShip.LastQuestDate") && NPChar.Quest.BurntShip.LastQuestDate != sLastSpeakDate)
	{
		DeleteAttribute(NPChar, "Quest.BurntShip");
	}
    
    bool ok;
    int iTest = FindColony(NPChar.City); // город магазина
    ref rColony;
    string sFrom_sea = "";
	npchar.quest.qty = CheckCapitainsList(npchar); //для списка кэпов

	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
		sFrom_sea = rColony.from_sea;
	}
	
	attrL = Dialog.CurrentNode;
	// hasert блок для сторожа ==>
	if(HasSubStr(attrL, "ShipStockManBack11_"))
	{
		i = findsubstr(attrL, "_" , 0);
		NPChar.StoreWithOff = 1;
		NPChar.ShipToStoreIdx = strcut(attrL, i+1, strlen(attrL)-1); // индех в конце
		Dialog.CurrentNode = "ShipStockManBack";
	}
	
	if(HasSubStr(attrL, "ShipStockManBack22_"))
	{
		i = findsubstr(attrL, "_" , 0);
		NPChar.StoreWithOff = 0;
		NPChar.ShipToStoreIdx = strcut(attrL, i+1, strlen(attrL)-1); // индех в конце
		Dialog.CurrentNode = "ShipStockManBack";
	}

	if(HasSubStr(attrL, "ShipStockManBack2_"))
	{
		i = findsubstr(attrL, "_" , 0);
		AddMoneyToCharacter(Pchar, -sti(NPChar.MoneyForShip));

		chref = GetCharacter(sti(NPChar.ShipToStoreIdx));//сторож

		////DownCrewExp(chref,GetNpcQuestPastDayParam(chref, "ShipInStockMan.Date"));

        int iChar = GetPassenger(PChar, sti(strcut(attrL, i+1, strlen(attrL)-1))); //выбранный пассажир
		compref = GetCharacter(iChar);

		DeleteAttribute(compref,"ship");//зачем-то стираем корабль офицера, хотя его там и не должно быть
		compref.ship = "";

		aref    arTo, arFrom;

		makearef(arTo, compref.ship);
		makearef(arFrom, chref.Ship);
		CopyAttributes(arTo, arFrom);

		// снимем пассажира -->
		CheckForReleaseOfficer(iChar);//увольнение офицера с должностей, если он не просто пассажир
		RemovePassenger(pchar, compref);
		// снимем пассажира <--
		SetCompanionIndex(pchar, -1, iChar);
		PortmanDelBakSkill(compref);
		DeleteAttribute(chref, "ShipInStockMan");
		if(CheckAttribute(chref, "DontNullShip"))
		{
			DeleteAttribute(chref, "DontNullShip");
			DeleteAttribute(NPChar, "DontNullShipBeliz");
		}
		chref.id = "ShipInStockMan";//сбрасываем индекс к стандартному, чтобы этот номер массива в следующий раз можно было занять
		DeleteAttribute(chref,"ship");//затираем данные корабля у сторожа
		chref.ship = "";
		LAi_SetCurHP(chref, 0.0);//ещё и убивать непися, чтоб точно очистился из массива?

		NPChar.Portman	= sti(NPChar.Portman) - 1;
		pchar.ShipInStock = sti(pchar.ShipInStock) - 1;
		Dialog.CurrentNode = "exit";//закрываем диалог, ещё одно подтверждение уже не справшиваем
	}
	
	if(HasSubStr(attrL, "ShipStockMan11_"))
	{
		i = findsubstr(attrL, "_" , 0);
		NPChar.StoreWithOff = 1;
		NPChar.ShipToStoreIdx = GetCompanionIndex(PChar, sti(strcut(attrL, i+1, strlen(attrL)-1))); // индех в конце
		Dialog.CurrentNode = "ShipStock_2";
	}

	if(HasSubStr(attrL, "ShipStockMan22_"))
	{
		i = findsubstr(attrL, "_" , 0);
		NPChar.StoreWithOff = 0;
		NPChar.ShipToStoreIdx = GetCompanionIndex(PChar, sti(strcut(attrL, i+1, strlen(attrL)-1))); // индех в конце
		Dialog.CurrentNode = "ShipStock_2";
	}
    //  <=== hasert
    
	if(HasSubStr(attrL, "BurntShip19_"))
	{
		i = findsubstr(attrL, "_" , 0);
	 	NPChar.Quest.BurntShip.ShipCompanionIndex = strcut(attrL, i + 1, strlen(attrL) - 1); // индех в конце
 	    Dialog.CurrentNode = "BurntShip19";
	}
    
	switch(Dialog.CurrentNode)
	{
        case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "fight":
			DialogExit();
            NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "First time":
			NextDiag.TempNode = "First time";
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar, 
					LinkRandPhrase("A városban riadót fújtak, és most mindenki téged keres. A helyedben én nem maradnék ott.", "Az összes városôr téged keresve pásztázza a várost. Nem vagyok bolond, hogy szóba álljak veled!", "Fuss, "+ GetSexPhrase("pajtás","lány") +", mielôtt a katonák kilyuggatnak..."), 
					LinkRandPhrase("Mit akarsz, "+ GetSexPhrase("gazember","büdös") +"?! A városôrök máris a szagodra csaptak, nem jutsz messzire, mocskos kalóz!", "gyilkos, azonnal hagyd el a házamat! Ôrség!", "Nem félek tôled, "+ GetSexPhrase("gazember","patkány") +"! Hamarosan felakasztanak az erôdünkben, nem jutsz messzire..."));
				link.l1 = NPCharRepPhrase(pchar,
					RandPhraseSimple("Heh, a riasztó nekem sosem jelent problémát...", "Soha nem fognak elkapni."), 
					RandPhraseSimple("Fogd be a szád, " + GetWorkTypeOfMan(npchar, "") + ", és talán nem tépem ki a mocskos nyelvedet!", "Heh, " + GetWorkTypeOfMan(npchar, "") + ", és mindenki ott - kapjátok el a kalózokat! Ezt mondom én neked, haver: maradj csendben, és életben maradsz..."));
				link.l1.go = "fight";
				break;
			}
			//Jason, фрахт
			if (CheckAttribute(pchar, "questTemp.WPU"))
			{
				if (pchar.questTemp.WPU.Fraht == "fail" && pchar.questTemp.WPU.Fraht.Nation == npchar.nation)
				{
					dialog.text = "Ó, tudom, hogy ki vagy. Azzal szerzôdtél, hogy szállítasz, de ehelyett elloptad a rakományt! Ôrség, ôrség!";
					Link.l1 = "Aaargh!";
					Link.l1.go = "exit";
					LAi_group_Attack(NPChar, Pchar);
					break;
				}
			}
			//фрахт
			//--> Jason Бремя гасконца
			if (CheckAttribute(pchar, "questTemp.Sharlie.Lock"))
			{
				dialog.text = "Mit tehetek önért, monsieur?";
				Link.l1 = "Üzleti ügyben jöttem...";
				Link.l1.go = "quests";
				Link.l2 = "Sajnálom, de mennem kell.";
				Link.l2.go = "exit";
				NPChar.quest.meeting = "1"; // patch-6
				break;
			}			
			//<-- Бремя гасконца
			if(NPChar.quest.meeting == "0")
			{
				
				dialog.text = "Üdvözlet, " + GetAddress_Form(NPChar) + ". Nem hiszem, hogy már találkoztunk volna. Én vagyok "  + GetFullName(npchar)+ " - a kikötômester.";
				Link.l1 = "Hello, " + GetFullName(NPChar) + ". Én vagyok " + GetFullName(PChar) + ", kapitánya '" + PChar.ship.name + "'.";
				if(startHeroType == 4 && NPChar.location == "SantaCatalina_portoffice")
				{
					dialog.text = "MacArthur kapitány, ahogy mindig emlékeztetem, nem kell minden alkalommal bejelentkeznie nálam. Ne aggódjon.";
					link.l1 = "Hagyd abba, Mister "+npchar.lastname+" Én is olyan vagyok, mint bárki más.";
					Link.l1.go = "node_2";
					break;
				}
				NPChar.quest.meeting = "1";
			}
			else
			{
				dialog.text = LinkRandPhrase("Üdvözlet, " + GetAddress_Form(NPChar) + ". Van valami dolga velem?",
                                    "Üdvözlöm, " + GetFullName(Pchar) + ". Láttam a hajóját a kikötônkbe érkezni, és biztos voltam benne, hogy eljön hozzám.",
                                    "Ó, kapitány " + GetFullName(Pchar) + ". Mi szél hozta ide hozzám?");
				Link.l1 = "Hello, " + GetFullName(NPChar) + ". Beszélni akartam veled.";
			}
			Link.l1.go = "node_2";
		break;
		
		case "node_2":
			// Церковный генератор 1
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.AskPortMan") && PChar.GenQuest.ChurchQuest_1.AskPortMan_InColony == NPChar.city)
			{
				dialog.text = "Kiváló. Állok rendelkezésére, " + GetFullName(PChar) + ".";
				if(!CheckAttribute(PChar, "GenQuest.ChurchQuest_1.CapFullInfo"))	// Получаем полную инфу
				{
					if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.NoMoneyToPortMan"))
					{
						dialog.text = "Szóval, mi van a pénzzel? Van legalább ezer pezód számomra?";
						if(sti(PChar.Money) >= 1000)
						{
							link.l1 = "Igen, van"+ GetSexPhrase("","") +". Ez pontosan ezer pezó. Most pedig az információ!";
							link.l1.go = "Church_GenQuest1_Node_FillFullInfo_3";
						}
						else
						{
							link.l1 = LinkRandPhrase("Nem, még nem...", "Még nem...", "Még nem, de hamarosan hozom...");
							link.l1.go = "exit";
						}
					}
					else
					{
						link.l1 = "Kérem, engedje meg, hogy elmagyarázzam a probléma lényegét. Én és régi barátom, kapitány  " + PChar.GenQuest.ChurchQuest_1.CapFullName + ", csak néhány órával maradtunk le egymásról, és sürgôs dolgom van vele. Most be kell érnem ôt, de nincs tudomásom"+ GetSexPhrase("","") +" hollétérôl.";
						link.l1.go = "Church_GenQuest1_Node_FillFullInfo";
					}
				}
				else	// Полная инфа уже есть
				{
					link.l1 = "Kikötômester, uram, szükségem lenne néhány információra a '" + PChar.GenQuest.ChurchQuest_1.CapShipName + "' nevû hajóról, melynek tulajdonosa a kapitány " + PChar.GenQuest.ChurchQuest_1.CapFullName + ".";
					if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.NextColonyIsLast")) // Он здесь, в этой колонии!		
						link.l1.go = "Church_GenQuest1_Node_CapOnThisColony_1";
					else // Отправляет в рандомную колонию
						link.l1.go = "Church_GenQuest1_Node_FillInfoOfCapColony_1";
				}				
				break;
			}		
//-------------------------------------------//Jason, фрахт---------------------------------------------------
				if (CheckAttribute(PChar, "questTemp.WPU.Fraht.TargetPortmanID") && CheckAttribute(PChar, "questTemp.WPU.Fraht.LevelUp") && pchar.questTemp.WPU.Fraht.TargetPortmanID == npchar.id)
				{
					dialog.text = "Kiváló. Állok rendelkezésére, " + GetFullName(PChar) + ".";
					Link.l1 = "A kolóniájuknak szánt rakomány a hajóm rakterében van.";
					Link.l1.go = "Fraht_completeLevelUp";
					break;
				}
				if (CheckAttribute(PChar, "questTemp.WPU.Fraht.TargetPortmanID") && pchar.questTemp.WPU.Fraht != "lost" && pchar.questTemp.WPU.Fraht.TargetPortmanID == npchar.id)
				{
					dialog.text = "Kiváló. Állok rendelkezésére, " + GetFullName(PChar) + ".";
					Link.l1 = "A kolóniájuknak szánt rakomány a hajóm rakterében van.";
					Link.l1.go = "Fraht_complete";
					break;
				}
			
				if (CheckAttribute(PChar, "questTemp.WPU.Fraht.TargetPortmanID") && pchar.questTemp.WPU.Fraht == "lost" && pchar.questTemp.WPU.Fraht.Nation == npchar.nation)
				{
					if (pchar.questTemp.WPU.Fraht.TargetPortmanID == npchar.id)
					{
						dialog.text = "Ó, hát végre eljöttél. Ôszintén szólva, nem számítottam rá, hogy visszajössz. Már kérvényeztük a hatóságoknál, hogy körözött személynek nyilvánítsanak. Szóval, mi a mondanivalója?";
						Link.l1 = "Elôre nem látható körülmények miatt nem tudtam idôben leszállítani a rakományt. De szeretném békésen rendezni ezt a konfliktust. Elhoztam a rakományát, és remélem, hogy meg tudunk egyezni.";
						Link.l1.go = "Fraht_complete_bad";
					}
					else
					{
						dialog.text = "Ó, tudom, hogy ki maga. Azzal szerzôdtél, hogy leszállítod a rakományt, de ehelyett elloptad! Ôrség, ôrség!";
						Link.l1 = "Aaargh!";
						Link.l1.go = "exit";
						LAi_group_Attack(NPChar, Pchar);
					}
				}
// <-- фрахт
//-------------------------------------------//Jason, почта---------------------------------------------------	
		
				if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.TargetPortmanID") && pchar.questTemp.WPU.Postcureer != "lost" && pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
				{
					dialog.text = "Kiváló. Állok rendelkezésére, " + GetFullName(PChar) + ".";
					Link.l1 = "A kolóniájuknak szállítottam a postát.";
					Link.l1.go = "Postcureer_complete";
					break;
				}
			
				if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.TargetPortmanID") && pchar.questTemp.WPU.Postcureer == "lost" && pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
				{
					dialog.text = "Ó, hát végre eljöttél. Ôszintén szólva, már azt hittük, hogy meghaltál... Hát, azt hiszem, még jó, hogy csak egy tökfej vagy, és nem egy halott ember.";
					Link.l1 = "Elôre nem látható körülmények miatt nem tudtam idôben kézbesíteni a postát. De itt van.";
					Link.l1.go = "Postcureer_complete_bad";
					break;
				}
			
				if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.fail") && pchar.questTemp.WPU.Postcureer.StartCity == npchar.city)
				{
					dialog.text = "Mi történt? Úgy nézel ki, mint akit felmelegített a halál.";
					Link.l1 = "" + GetAddress_FormToNPC(NPChar) + ", Igazad volt, amikor figyelmeztettél a veszélyre. Két fekete ruhás férfi támadt rám a kikötôi hivatal kijáratánál, és... nos, elvették tôlem a csomagot.";
					Link.l1.go = "Postcureer_complete_fail";
					break;
				}
// <-- почта
//-------------------------------------------//Jason, эскорт---------------------------------------------------	
				if(CheckAttribute(PChar, "questTemp.WPU.Escort.TargetPortmanID") && CheckAttribute(pchar, "questTemp.WPU.Escort.LevelUp_0") && pchar.questTemp.WPU.Escort.TargetPortmanID == npchar.id)
				{
					dialog.text = "Kiváló. Állok rendelkezésére, " + GetFullName(PChar) + ".";
					Link.l1 = "A kikötômester küldött ide "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen")+". Arra kértek, hogy kísérjek el egy hajót, amely fegyvereket és lôszert szállít. Itt vannak a papírjaim.";
					Link.l1.go = "Escort_LUGo_0";
					break;
				}
				if(CheckAttribute(PChar, "questTemp.WPU.Escort.TargetPortmanID") && CheckAttribute(pchar, "questTemp.WPU.Escort.LevelUpGo_0") && npchar.location == pchar.questTemp.WPU.Escort.StartCity +"_portoffice")
				{
					dialog.text = "Kiváló. Állok rendelkezésére, " + GetFullName(PChar) + ".";
					Link.l1 = "Elkísértem a hajót a fegyverekkel, ahogy megbeszéltük.";
					Link.l1.go = "Escort_LUGo_complete";
					break;
				}
				if(CheckAttribute(PChar, "questTemp.WPU.Escort.TargetPortmanID") && CheckAttribute(pchar, "questTemp.WPU.Escort.LevelUp_1WM") && pchar.questTemp.WPU.Escort == "current" && npchar.location == pchar.questTemp.WPU.Escort.StartCity +"_portoffice")
				{
					dialog.text = "Kiváló. Állok rendelkezésére, " + GetFullName(PChar) + ".";
					Link.l1 = "Megtaláltam az eltûnt hajót és a kikötôjükbe hoztam. A hajó kapitányának már jelentenie kellett volna.";
					Link.l1.go = "Escort_LU1WM_complete";
					break;
				}
				if(CheckAttribute(PChar, "questTemp.WPU.Escort.TargetPortmanID") && CheckAttribute(pchar, "questTemp.WPU.Escort.LevelUp_1VSP") && pchar.questTemp.WPU.Escort == "win" && npchar.location == pchar.questTemp.WPU.Escort.StartCity +"_portoffice")
				{
					dialog.text = "Kiváló. Állok rendelkezésére, " + GetFullName(PChar) + ".";
					Link.l1 = "Megtaláltam az eltûnt hajót és a kikötôjükbe hoztam. A hajó kapitányának már jelentenie kellett volna.";
					Link.l1.go = "Escort_LU1VSP_complete";
					break;
				}
				if(CheckAttribute(PChar, "questTemp.WPU.Escort.TargetPortmanID") && CheckAttribute(pchar, "questTemp.WPU.Escort.LevelUp_1VSP") && pchar.questTemp.WPU.Escort == "sink" && npchar.location == pchar.questTemp.WPU.Escort.StartCity +"_portoffice")
				{
					dialog.text = "Kiváló. Állok rendelkezésére, " + GetFullName(PChar) + ".";
					Link.l1 = "Megtaláltam az eltûnt hajót a "+XI_ConvertString(pchar.questTemp.WPU.Current.TargetIslandID)+"sziget partjainál. A kapitánya egyenlôtlen harcot vívott a túlerôben lévô kalózerôkkel. Segítettem, ahogy tudtam, sajnos hiába: az átkozott gazemberek elsüllyesztették a hajót. Ekkor már csak annyit tehettem, hogy megbosszulom.";
					Link.l1.go = "Escort_LU1VSP_completeSink";
					break;
				}
				if(CheckAttribute(PChar, "questTemp.WPU.Escort.TargetPortmanID") && CheckAttribute(pchar, "questTemp.WPU.Escort.LevelUp_1S") && pchar.questTemp.WPU.Escort == "win" && npchar.location == pchar.questTemp.WPU.Escort.StartCity +"_portoffice")
				{
					dialog.text = "Kiváló. Állok rendelkezésére, " + GetFullName(PChar) + ".";
					Link.l1 = "Megtaláltam az eltûnt hajót a "+XI_ConvertString(pchar.questTemp.WPU.Current.TargetIslandID)+"sziget partjainál. Nos, igazából nem a hajót, hanem a legénységébôl mintegy félszáz embert és a kapitányt. Most már biztonságban vannak - a legénység felszállt a hajómra, és a kapitány most az önök városában van - gondolom, már meglátogatta önöket.";
					Link.l1.go = "Escort_LU1S_complete";
					break;
				}
				if(CheckAttribute(PChar, "questTemp.WPU.Escort.TargetPortmanID") && CheckAttribute(pchar, "questTemp.WPU.Escort.LevelUp_2") && pchar.questTemp.WPU.Escort == "win" && npchar.location == pchar.questTemp.WPU.Escort.StartCity +"_portoffice")
				{
					dialog.text = "Kiváló. Állok rendelkezésére, " + GetFullName(PChar) + ".";
					Link.l1 = "Teljesítettem a megbízatását. A kereskedelmi konvojt megtámadó kalózraj megsemmisült.";
					Link.l1.go = "Escort_LU2_complete";
					break;
				}
				if (CheckAttribute(PChar, "questTemp.WPU.Escort.TargetPortmanID") && CheckAttribute(pchar, "questTemp.WPU.Escort.Bonus") && pchar.questTemp.WPU.Escort.Bonus != "fail" && pchar.questTemp.WPU.Escort.TargetPortmanID == npchar.id)
				{
					dialog.text = "Kiváló. Állok rendelkezésére, " + GetFullName(PChar) + ".";
					Link.l1 = "Én vagyok a kísérôhajó kapitánya. Azért jöttem, hogy jelentse, hogy a kereskedelmi hajókat a kikötôbe hoztam.";
					Link.l1.go = "Escort_complete";
					break;
				}
				if (CheckAttribute(PChar, "questTemp.WPU.Escort.TargetPortmanID") && CheckAttribute(pchar, "questTemp.WPU.Escort.Bonus") && pchar.questTemp.WPU.Escort.Bonus == "fail" && pchar.questTemp.WPU.Escort.TargetPortmanID == npchar.id)
				{
					dialog.text = "Kiváló. Állok rendelkezésére, " + GetFullName(PChar) + ".";
					Link.l1 = "Én vagyok a kísérôhajó kapitánya. Azért küldtek, hogy két kereskedelmi hajót és rakományt hozzak a kikötôbe, de sajnos mindkét kísérôhajó elsüllyedt egy ellenséges konvojjal folytatott csata során. A rakományt azonban így is sikerült leszállítanom.";
					Link.l1.go = "Escort_fail";
					break;
				}
				if (CheckAttribute(PChar, "questTemp.WPU.Escort.TargetPortmanID") && pchar.questTemp.WPU.Escort.TargetPortmanID == npchar.id && !CheckAttribute(PChar, "questTemp.WPU.Escort.LevelUp"))
				{
					dialog.text = "Kiváló. Állok rendelkezésére, " + GetFullName(PChar) + ".";
					Link.l1 = "Én vagyok a kísérôhajó kapitánya. Azért jöttem, hogy jelentse, hogy a kereskedelmi hajókat a kikötôbe hoztam.";
					Link.l1.go = "Escort_complete";
					break;
				}
// <-- эскорт
			if(startHeroType == 4 && NPChar.location == "SantaCatalina_portoffice" && NPChar.quest.meeting == "0")
			{
				NPChar.quest.meeting = "1";
				dialog.text = "Milyen kellemes ezt hallani. Sokan elbizakodottak lettek volna a helyedben. Szóval, miben segíthetek én és a feljegyzéseim?";
			}
			else dialog.text = "Kiváló. Állok rendelkezésére, " + GetFullName(PChar) + ".";
			if (npchar.city != "Panama") // Captain Beltrop, 24.12.2020, запрет брать задания и ставить корабли в ПУ Панамы
			{
				Link.l2 = "Van olyan munkája, amit elvállalhatnék? Vagy esetleg egy szerzôdés?";
				Link.l2.go = "Work_check"; //квесты
				Link.l3 = "Kiköthetném itt az egyik hajómat egy kis idôre?";
				Link.l3.go = "ShipStock_1";
			}
			if (sti(NPChar.Portman) > 0)
			{
                Link.l4 = "Be akarom gyûjteni a hajómat.";
    			Link.l4.go = "ShipStockReturn_1";
			}
			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
			{
				link.l5 = "Azért jöttem, hogy pénzügyi ügyekrôl beszéljünk.";
				link.l5.go = "LoanForAll";//(перессылка в кредитный генератор)	
			}
  			if (CheckAttribute(pchar, "GenQuest.Intelligence") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "") //квест мэра - на связь с нашим шпионом
			{
				link.l7 = RandPhraseSimple("Egy bizonyos ember kérésére vagyok itt. A neve kormányzó " + GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) + ".", 
					GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) + " küldött hozzád. Azért jöttem, hogy elvigyek valamit...");
				link.l7.go = "IntelligenceForAll";
			}
			link.l6 = "Szeretnék többet megtudni azokról a kapitányokról, akik regisztráltak a kikötôi hatóságnál.";
			link.l6.go = "CapitainList";
			link.l61 = "Megosztanátok velem valamilyen betekintést az egyedi, egyedi hajókról és legendás kapitányaikról?";
			link.l61.go = "UniqueShips";
			
			link.l8 = "Én mással foglalkozom.";
			// Warship 26.07.09 Генер "Сгоревшее судно"
			if(CheckAttribute(NPChar, "Quest.BurntShip") && !CheckAttribute(NPChar, "Quest.BurntShip.LastQuestDate"))
			{
				if(CheckAttribute(NPChar, "Quest.BurntShip.TimeIsOver")) // Просрочено
				{
					link.l8.go = "BurntShip10";
				}
				else
				{
					if(CheckAttribute(NPChar, "Quest.BurntShip.TwoDaysWait"))
					{
						if(GetNpcQuestPastDayParam(NPChar, "Quest.BurntShip.TwoDaysWait") >= 2)
						{
							link.l8.go = "BurntShip17";
						}
						else
						{
							link.l8.go = "quests";
						}
					}
					else
					{
						link.l8.go = "BurntShip12";
					}
				}
			}
			else
			{
				link.l8.go = "quests";
			}
			if(CheckAttribute(pchar,"GenQuest.EncGirl"))
			{
				if(pchar.GenQuest.EncGirl == "toLoverFather" && pchar.GenQuest.EncGirl.LoverFather == "portman_keeper" && pchar.GenQuest.EncGirl.LoverCity == npchar.city)
				{
					link.l9 = "Jó napot, a fia meghívására jöttem."; 
					link.l9.go = "EncGirl_4";
					pchar.quest.EncGirl_GetLoverFather.over = "yes";
				}	
				if(pchar.GenQuest.EncGirl == "toParents" || pchar.GenQuest.EncGirl == "FindLover")
				{
					if(pchar.GenQuest.EncGirl.Father == "portman_keeper" && npchar.city == pchar.GenQuest.EncGirl.city)
					{
						link.l9 = "A lányáról van szó...";
						link.l9.go = "EncGirl_1";
					}
				}
			}
			if (CheckCharacterItem(pchar, "CaptainBook"))
			{
				if(pchar.questTemp.different == "free")
				{
					link.l10 = "Véletlenül belebotlottam ebbe a csomagba, ami a hajó iratait tartalmazza.";
					link.l10.go = "ShipLetters_out1";				
				}
				else
				{
					if(pchar.questTemp.different.GiveShipLetters.city == npchar.city)
					{
						link.l10 = "Véletlenül bukkantam erre a csomagra a hajó irataival, valaki biztos elvesztette ôket.";
						if(!CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakPortman"))
						{
							link.l10.go = "ShipLetters_Portman1_1";						
						}
						else
						{
							link.l10.go = "ShipLetters_Portman2";
						}
					}
				}		
			}												
			Link.l15 = "Köszönöm. Köszönöm. Viszontlátásra.";
			Link.l15.go = "exit";
		break;

		case "Church_GenQuest1_Node_FillFullInfo":
			dialog.text = "A problémája könnyen megoldható. Menjen el a navigációs szolgálat tisztviselôjéhez, aki minden információt megadhat a barátja hajójának útvonaláról.";
			link.l1 = "Sajnos, ez nem olyan egyszerû. A barátom átnevezte a hajóját az önök kikötôjében... vallási okokból.";
			link.l1.go = "Church_GenQuest1_Node_FillFullInfo_2";
		break;
			
		case "Church_GenQuest1_Node_FillFullInfo_2":
			dialog.text = "Értem. Ez egy kicsit bonyolultabbá teszi a dolgokat. Át kell kutatnom a hajólajstrom bejegyzéseit, és ez eltart egy darabig. És az idô pénz, ahogy azt bizonyára tudja.";
			if(sti(pchar.money) >= 1000)
			{
				link.l1 = "Tökéletesen megértem ezt, mister " + GetFullName(NPChar) + ", és megfelelôen felkészültem arra, hogy értékeljem az idejét ... mondjuk, egy tousand pezó összegben.";
				link.l1.go = "Church_GenQuest1_Node_FillFullInfo_3";
			}
			else
			{
				DeleteAttribute(pchar, "GenQuest.ChurchQuest_1.CurPortManColony"); // Можно будет спросить.
				link.l1 = "Kár, mert jelenleg nincs nálam pénz... Majd késôbb visszajövök...";
				link.l1.go = "exit";
			}
		break;
			
		case "Church_GenQuest1_Node_FillFullInfo_3":
			sColony = GetColonyExpect2Colonies(NPChar.city, PChar.GenQuest.ChurchQuest_1.QuestTown);
			PChar.GenQuest.ChurchQuest_1.CapGoToColony = sColony;
			if(CheckAttribute(pchar, "GenQuest.ChurchQuest_1.NoMoneyToPortMan"))
			{
				dialog.text = "Tökéletes! Lássuk csak... egy pillanat... itt... jobbra. A hajó átnevezését bejegyezték, és a hajó, amely ezentúl '" + PChar.GenQuest.ChurchQuest_1.CapShipName + "' kapitány által irányított " + PChar.GenQuest.ChurchQuest_1.CapFullName + " néven lesz ismert, ma elindult a " + XI_ConvertString("Colony" + sColony + "Gen") + "felé.";
				DeleteAttribute(pchar, "GenQuest.ChurchQuest_1.NoMoneyToPortMan");
			}
			else
				dialog.text = "Ó! Te tényleg megérted, hogy nagyon elfoglalt ember vagyok, és örülök, hogy ezt értékeled! Lássuk csak... egy pillanat... itt... rendben. A hajó átnevezését bejegyezték, és a hajó, amely ezentúl '" + PChar.GenQuest.ChurchQuest_1.CapShipName + "' kapitány által irányított " + PChar.GenQuest.ChurchQuest_1.CapFullName + " nevet viseli, ma kihajózott a " + XI_ConvertString("Colony" + sColony + "Gen") + "felé.";			
				link.l1 = "Köszönöm, uram, nagy szívességet tett nekem.";
				link.l1.go = "Church_GenQuest1_Node_FillFullInfo_4";
				AddMoneyToCharacter(pchar, -1000);
		break;
			
		case "Church_GenQuest1_Node_FillFullInfo_4":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "4");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.CapGoToColony + "Gen"));
			AddQuestUserData(sQuestTitle, "sShipName", PChar.GenQuest.ChurchQuest_1.CapShipName);	
			PChar.GenQuest.ChurchQuest_1.AskPortMan_InColony = PChar.GenQuest.ChurchQuest_1.CapGoToColony;
			PChar.GenQuest.ChurchQuest_1.CapFullInfo = true;
		break;
			
		case "Church_GenQuest1_Node_FillInfoOfCapColony_1":
			dialog.text = "Mit akar pontosan tudni?";
			link.l1 = "Meg tudná mondani, hogy a kapitány hajója járt-e már a kikötôben?";
			link.l1.go = "Church_GenQuest1_Node_FillInfoOfCapColony_2";
		break;
						
		case "Church_GenQuest1_Node_FillInfoOfCapColony_2":
			PChar.GenQuest.ChurchQuest_1.CapGoToColony = GetColonyExpect2Colonies(NPChar.city, PChar.GenQuest.ChurchQuest_1.QuestTown);
			dialog.text = "Hmm... És megkérdezhetem, hogy miért kérdezed?";
			link.l1 = "Üzleti ügyeim vannak vele. De ha nem futott be a kikötôjébe, vagy nem tudja...";
			link.l1.go = "Church_GenQuest1_Node_FillInfoOfCapColony_3";
		break;
			
		case "Church_GenQuest1_Node_FillInfoOfCapColony_3":
			dialog.text = "Igen. De dicsértessék minden szent, éppen ma reggel szabadított meg minket a jelenlététôl, és elindult a " + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.CapGoToColony + "Acc") + ". És ôszintén sajnálok mindenkit, akinek vele kell foglalkoznia.";
			link.l1 = "Ebben az esetben sok szerencsét kívánok - és köszönöm a segítséget.";
			link.l1.go = "Church_GenQuest1_Node_FillInfoOfCapColony_4";
		break;
			
		case "Church_GenQuest1_Node_FillInfoOfCapColony_4":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "5");
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.CapGoToColony + "Voc")); // belamour gen
			AddQuestUserData(sQuestTitle, "sName", PChar.GenQuest.ChurchQuest_1.CapFullName);
			PChar.GenQuest.ChurchQuest_1.AskPortMan_InColony = PChar.GenQuest.ChurchQuest_1.CapGoToColony; // Спрашиваем портмана в колонии, куда отправился кэп.
			if(rand(2) == 1) 
			{
				Log_TestInfo("The next colony is the last");
				PChar.GenQuest.ChurchQuest_1.NextColonyIsLast = true; // Флаг - следующая колония будет последней
			}
		break;
			
		case "Church_GenQuest1_Node_CapOnThisColony_1":
			dialog.text = "Mit akar tudni, "+ GetSexPhrase("mister","miss") +" " + GetFullName(PChar) + "?";
			link.l1 = "Meg tudná mondani, hogy ez a kapitány a kikötôjükben járt-e vagy sem?";
			link.l1.go = "Church_GenQuest1_Node_CapOnThisColony_2";
		break;
			
		case "Church_GenQuest1_Node_CapOnThisColony_2":
			dialog.text = "Hmm, az biztos. És azt kell mondanom, hogy türelmetlenül várom azt az áldott pillanatot, amikor végre elhagyja ezt a régóta szenvedett kikötôt.";
			link.l1 = "Úgy érti, hogy a hajója még mindig itt van?";
			link.l1.go = "Church_GenQuest1_Node_CapOnThisColony_3";
		break;
			
		case "Church_GenQuest1_Node_CapOnThisColony_3":
			dialog.text = "Igen, kegyelmes "+ GetSexPhrase("uram","hölgy") +". Az egész kikötô, kezdve a legalacsonyabb rakodóktól kezdve a révészszolgálat vezetôjéig, imádkozik a gyors távozásáért. A hajója nemrég hagyta el a szárazdokkot, ahol azonnal megjavították, de addigra a gáláns kapitánya már összeveszett minden ácsmesterrel, és három tétel kiválasztott deszkát is visszautasított a hajó bôréhez. De holnap a mi legkegyelmesebb és mindent látó Urunk megszabadít minket ettôl... ettôl a csapástól, ettôl a tüskétôl!";
			link.l1 = "Most pedig nyugodjon meg, uram " + NPChar.Name + ", és gondoljon arra, hogy valakinek még mindig nehezebb dolga lesz. Ön már túl van ezen a próbán, míg én még nem találkoztam a kapitányával. És most, ha megbocsátanak...";
			link.l1.go = "Church_GenQuest1_Node_CapOnThisColony_4";
		break;
			
		case "Church_GenQuest1_Node_CapOnThisColony_4":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "6");
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown));
//			PChar.GenQuest.ChurchQuest_1.NeedToDialogWithSailors = true; // Спрашиваем моряков
			PChar.GenQuest.ChurchQuest_1.NeedToDialogWithCap = true; // Говорим с капитаном
//			SetFunctionLocationCondition("Church_GenQuest1_ChangeCapitanLocation", "Deck_Near_Ship", true);
			PChar.GenQuest.ChurchQuest_1.CurPortManColony = NPChar.city;
			Group_SetAddress("ChurchGenQuest1_CapGroup", colonies[FindColony(NPChar.City)].Island, "IslandShips1", "Ship_1"); // Ставим кэпа в порту колонии
			Characters[GetCharacterIndex("ChurchGenQuest1_Cap")].Nation = sti(NPChar.Nation); // Сменим нацию, чтоб вражды не было
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_1.AskPortMan"); // Больше не спрашиваем
//			if(rand(1) == 0) PChar.GenQuest.ChurchQuest_1.CapWaitOnTavern = true;
			sld = CharacterFromID("ChurchGenQuest1_Cap");
			sld.DeckDialogNode = "ChurchGenQuest_1_DeckDialog_1";
		break;
						
		case "ShipLetters_out1":
			dialog.text = "Hadd nézzem meg! Igen, valóban, az irataimban ez a készlet érvénytelennek van jelölve. Nagyon kedves öntôl, hogy talált egy percet, hogy felkeressen és átadja nekem ezeket a papírokat. El a széllel, kapitány!";
			link.l1 = "Köszönjük!";
			link.l1.go = "exit";
			TakeItemFromCharacter(pchar, "CaptainBook"); 			
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //снимаем таймер 
			AddQuestRecord("GiveShipLetters", "10");			
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit(); 
		break;
				
		case "ShipLetters_Portman1_1":
			pchar.questTemp.different.GiveShipLetters.speakPortman = true;
			s1 = "Hadd nézzem meg! Igen, ez a hajó és a kapitánya is szerepel az irataimban. ";
			s1 = s1 + "Az ön lelkiismeretessége, kapitány, dicsôséget hoz magára! Természetesen az erôfeszítései nem maradhatnak jutalom nélkül.  ";
			dialog.text = s1 + "Mondd, megfelelô jutalomnak tartasz egy " + sti(pchar.questTemp.different.GiveShipLetters.price1) + " pezó összeget?";
			link.l1 = "Természetesen nem!";
			link.l1.go = "exit";
			link.l2 = "Nos, szerény összeg, de akkor sem volt nagy dolog. Igen, elfogadom az ajánlatát, "  + npchar.name +".";
			link.l2.go = "ShipLetters_Portman1_2";
		break;
		
		case "ShipLetters_Portman1_2" :
			TakeItemFromCharacter(pchar, "CaptainBook"); 
			addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price1)); 			
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //снимаем таймер 
			AddQuestRecord("GiveShipLetters", "5");			
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit(); 
		break;
		
		case "ShipLetters_Portman2":
			dialog.text = "Elfogadja az ajánlatomat?";
			link.l1 = "Természetesen nem!";
			link.l1.go = "exit";
			link.l2 = "Talán. Bár biztos vagyok benne, hogy ezek a papírok sokkal többet érnek.";
			link.l2.go = "ShipLetters_Portman2_1";
		break;
		
		case "ShipLetters_Portman2_1":
			TakeItemFromCharacter(pchar, "CaptainBook"); 
			addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price1)); 			
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //снимаем таймер 
			AddQuestRecord("GiveShipLetters", "6");			
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit(); 		
		break;

		case "EncGirl_1":
			dialog.text = "Csupa fül vagyok.";
			link.l1 = "Elhoztam a szökevényét.";
			link.l1.go = "EncGirl_2";
		break;
		
		case "EncGirl_2":
			dialog.text = "Ó, kapitány, nagyon köszönöm! Hogy van? Megsérült? Miért szökött el? Miért?\nHát nem érti? A vôlegény egy gazdag és fontos ember! A fiatalság naiv és ostoba... sôt kegyetlen. Ezt ne feledje!";
			link.l1 = "Nos, te vagy az apja, és a végsô döntés a tiéd, de én nem sietnék az esküvôvel...";
			link.l1.go = "EncGirl_3";
		break;
		
		case "EncGirl_3":
			dialog.text = "Mit tudsz te? Vannak saját gyermekei? Nincsenek? Ha lesz egy, jöjjön el hozzám, és akkor majd beszélgetünk.\njutalmat ígértem annak, aki visszaviszi a családjához.";
			link.l1 = "Köszönöm. Köszönöm. Tartsd rajta a szemed. Van egy olyan érzésem, hogy nem fog leállni.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("EncGirl_ToLoverParentsExit");
		break;
		
		case "EncGirl_4":
			if(sti(pchar.GenQuest.EncGirl.LoverFatherAngry) == 0)
			{
				dialog.text = "Ó, te vagy az a "+ GetSexPhrase("kapitány, aki elhozta","ifjú hölgyet, aki elhozta") +" tékozló fiamat egy fiatal arával?";
				link.l1 = "Igen, segítettem nekik megszökni.";
				link.l1.go = "EncGirl_5";
			}
			else
			{
				dialog.text = "Ó, gyere, jótevôm. Valószínûleg jutalomra vársz?";
				link.l1 = "Nos, jól megvagyok jutalom nélkül is, a hálád is megteszi.";
				link.l1.go = "EncGirl_6";			
			}
		break;
		
		case "EncGirl_5":
			dialog.text = "Nagyon hálás vagyok neked, hogy nem hagytad magára a gyermekemet a legnagyobb bajban, és segítettél neki kiutat találni ebbôl a kényes helyzetbôl. Engedje meg, hogy megköszönjem, és kérem, fogadja el ezt a szerény összeget és egy személyes ajándékot tôlem.";
			link.l1 = "Köszönöm. Örömömre szolgált, hogy segíthettem ennek a fiatal párnak.";
			link.l1.go = "EncGirl_5_1";
		break;
		
		case "EncGirl_6":
			dialog.text = "Köszönöm. Milyen köszönet?! Fél éve már, hogy ez a tökfej munka nélkül lóg itt - és nézzétek meg, van elég ideje szerelmi ügyekre is! Az ô korában én már a saját vállalkozásomat vezettem! Pff! Egy kormányzónak van egy házasulandó lánya - és ez a tökfilkó egy rokonok nélküli ribancot hozott a házamba, és még az áldásomat is kérni merte!";
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
		
		case "node_4":
			//--> дача миниквестов начальника порта. 
			if (rand(2) < 2 && pchar.questTemp.different == "free" && GetNpcQuestPastDayWOInit(npchar, "quest.meeting") > 7)
			{
				dialog.text = LinkRandPhrase("Igen, az istenit! Van egy munkám a számodra!", 
					"Ha! Épp idôben jöttél! Van egy megoldandó problémám.", 
					"De hát persze! Persze, hogy van munkám számodra! Tudod, mostanában elárasztanak a problémák...");
				link.l1 = "Akkor kérem térjen a lényegre, " + GetAddress_FormToNPC(NPChar) + ".";
				link.l1.go = "PortmanQuest";
				SaveCurrentNpcQuestDateParam(npchar, "quest.meeting");
				break;
			}
			
			// Warship 25.07.09 Генер "Сгоревшее судно"
			if(hrand(4) == 2 && !CheckAttribute(NPChar, "Quest.BurntShip"))
			{
				dialog.text = "Istenem! Kapitány " + GetFullName(PChar) + ", épp idôben jöttél! Ekkora szerencsétlenség történt, ekkora csapás... A hajó leégett a kikötôi hatóság felügyelete alatt az útszakaszon! A biztonságiak figyelmetlensége miatt a hajó leégett... vízvonalig égett...\n" + "Uram, mivel érdemeltem ki ilyen büntetést? Hûséges szolga voltam annyi éven át...";
				link.l1 = "Szóval, mi ez a nagy dolog? Egy hajó leégett? És mire való a biztosítási szerzôdés? Vagy úgy döntöttél, hogy nem biztosítod, hogy spórolj a pénzeden, és most megeszed a szíved?";
				link.l1.go = "BurntShip4";
				link.l2 = "A hajógyár jobban fog ebben segíteni neked, mint én. Pár hónap múlva helyreállítják a régit, vagy akár újat is építhetnek. Bocsánat, de nem vagyok hajóépítô...";
				link.l2.go = "BurntShip2";
				break;
			}
			//<-- дача миниквестов начальника порта.

			dialog.text = "A kormányzó törôdik a polgárai jólétével, ezért mindig van néhány munkalehetôsége. A kocsmában lehetnek kereskedôk, akiket érdekelhet a segítség, és a boltban is szükség van teherhajó kapitányokra.";
			Link.l1 = "Még egy kérdésem lenne.";
			Link.l1.go = "node_2";
			Link.l2 = "Köszönöm. Köszönöm. Viszontlátásra.";
			Link.l2.go = "exit";
		break;

///Jason-----------------------новые генераторы накопительного типа для портмана----------------------------
		int iTime, idaysQty, iGoods, iGoodsQty, amount;
		case "Work_check"://фейс-контроль - общая проверка профпригодности ГГ и выбор задания
			//--> проверка миниквестов начальника порта. 
			if (npchar.quest == "PortmansJornal") //взят квест на судовой журнал
			{
				dialog.text = "Meg kellett volna találnod a " + npchar.quest.PortmansJornal.capName + " kapitányt, és visszaadnod neki a hajónaplóját. Sikerült?";
				link.l1 = "Nem, még nem...";
				link.l1.go = "PortmanQuest_NF";
				break;
			}
			if (npchar.quest == "PortmansSeekShip" || npchar.quest == "SeekShip_sink") //взят квест на поиски украденного корабля
			{
				dialog.text = "Elkötelezte magát, hogy felkutat egy lopott " + GetStrSmallRegister(XI_ConvertString(npchar.quest.PortmansSeekShip.shipTapeName)) + " '" + npchar.quest.PortmansSeekShip.shipName + "'. Addig nem lesz más feladat számodra, amíg ezzel nem végeztél.";
				link.l1 = "Folytatom a keresést, csak várj.";
				link.l1.go = "exit";
				link.l2 = "Fel akarom adni a megbízást.";
				link.l2.go = "SeekShip_break";
				break;
			}
			if (npchar.quest == "SeekShip_success") //украденный корабль взят на абордаж
			{
				dialog.text = "Megígérted, hogy felkutatod a lopott " + GetStrSmallRegister(XI_ConvertString(npchar.quest.PortmansSeekShip.shipTapeName)) + " '" + npchar.quest.PortmansSeekShip.shipName + "'. Megtetted?";
				bool bOk = false;
				for (i=0; i<=COMPANION_MAX; i++)
				{
					cn = GetCompanionIndex(pchar, i);
					if(cn != -1)
					{
						sld = &characters[cn];
						if (sld.ship.name == npchar.quest.PortmansSeekShip.shipName && 
							RealShips[sti(sld.ship.type)].BaseName == npchar.quest.PortmansSeekShip.shipTapeName &&
							RealShips[sti(sld.Ship.Type)].basetype == npchar.quest.PortmansSeekShip.shipTape)
						{
							if (i == 0)
							{	//если нужный корабль - у ГГ
								sld.Ship.Type = GenerateShip(SHIP_TARTANE, true);
								SetBaseShipData(sld);
								SetCrewQuantityFull(sld);
							}
							else
							{
								RemoveCharacterCompanion(pchar, sld);
								AddPassenger(pchar, sld, false);
							}
							bOk = true;
						}
					}
				}				
				if (bOk)
				{
					link.l1 = "Igen, megtaláltam, most a kikötôben van. Elviheted.";
					link.l1.go = "SeekShip_good";
				}
				else
				{
					link.l1 = "Folytatom a keresést, csak várj.";
					link.l1.go = "exit";
				}
				link.l2 = "Fel akarom adni a megbízást.";
				link.l2.go = "SeekShip_break";
				break;
			}
			//<-- проверка миниквестов начальника порта. 
			ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
			if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)//проверка на наличие корабля в порту
			{
				if (!CheckAttribute(npchar, "work_date") || GetNpcQuestPastDayParam(npchar, "work_date") >= 2)//проверка повтора
				{
					if (sti(NPChar.nation) != PIRATE && GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)//проверка межнациональных отношений
					{
						dialog.text = RandPhraseSimple("Nincs munka azoknak, akik a " + NationNameGenitive(sti(pchar.nation)) + "zászló alatt hajóznak ! Azonnal hagyja el az irodámat!", "Nem fogok együttmûködni a " + NationNameAblative(sti(pchar.nation)) + ". Távozzanak!");
						link.l1 = RandPhraseSimple("Nos, ahogy kívánod...", "Nos, ahogy kívánod...");
						link.l1.go = "exit";
						break;
					}
					if (isBadReputation(pchar,40)) // проверка репутации ГГ с вызывающим доверие belamour legendary edition
					{
						dialog.text = "A hírneve nem ébreszt bennem bizalmat. Nem fogok együttmûködni veled. Viszontlátásra.";
						link.l1 = "Mi? Ez mind hazugság.";
						link.l1.go = "exit";
						break;
					}
					if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 5)//при низком авторитете не даем
					{
						dialog.text = "Nem akarom megsérteni, kapitány, de... Attól tartok, nem lenne képes teljesíteni a megbízásomat - egyszerûen nincs tapasztalata. Nem tudok szerzôdést kötni magával.";
						link.l1 = "Értem, értem. Nos, ahogy mondja.";
						link.l1.go = "exit";
						break;
					}
					dialog.Text = "Hmm... Nos, ez attól függ, hogy milyen munka érdekel.";
					link.l1 = "Felajánlhatnám, hogy kibérelheti a hajómat teherszállításra.";
					Link.l1.go = "Fraht_begin";		//фрахты
					link.l2 = "Szeretnék plusz pénzt keresni azzal, hogy kereskedôket kísérek.";
					Link.l2.go = "escort_begin";	//эскорт
					link.l3 = "Szeretnék plusz pénzt keresni azzal, hogy postát szállítok.";
					Link.l3.go = "cureer_begin";	//доставка почты
					Link.l4 = "Nos, talán fel tudna ajánlani valamit?";
					Link.l4.go = "node_4"; 			//судовой журнан, угнанное судно, сгоревшее судно
				}
				else
				{
					dialog.Text = "Mára nem maradt semmi. Jöjjön máskor.";
					link.l1 = "Rendben.";
					Link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "Nem látom a hajóját a kikötôben. Feküdj le, aztán gyere vissza hozzám - megpróbálunk találni neked valamit.";
				link.l1 = "Rendben, meg is teszem.";
				link.l1.go = "exit";
			}
		break;
		
		case "escort_begin"://эскорт
		SaveCurrentNpcQuestDateParam(npchar, "work_date"); // mitrokosta безусловно сохраняем
		
		if (hrand(5) > 1)
		{
			if (GetCompanionQuantity(pchar) < 3 && or(sti(RealShips[sti(pchar.Ship.Type)].Spec) == SHIP_SPEC_WAR, sti(RealShips[sti(pchar.Ship.Type)].Spec) == SHIP_SPEC_RAIDER)) 
			{
				if (pchar.questTemp.WPU.Escort == "begin" || pchar.questTemp.WPU.Escort == "late" || pchar.questTemp.WPU.Escort == "win" || CheckAttribute(pchar, "questTemp.WPU.Escort.LevelUp")) 
				{ // если заняты
					dialog.text = "Sajnos, semmi ilyesmit nem tudok felajánlani. Ugorjon be újra pár nap múlva.";
					link.l1 = "Rendben, meg is teszem.";
					link.l1.go = "exit";
				} 
				else 
				{ // если не заняты
					if (sti(pchar.questTemp.WPU.Escort.count) > 3 && hrand(1) == 1) 
					{ // 2 уровень
						dialog.text = "Ön már többször is sikeresen kísért kereskedelmi hajókat. Azt hiszem, van egy megbízásom, ami megfelelne önnek.";
						link.l1 = "Csupa fül vagyok.";
						link.l1.go = "Escort_LevelUp";
					} 
					else 
					{ // 1 уровень
						if (sti(RealShips[sti(pchar.Ship.Type)].BaseType) == SHIP_GALEON_H && 2500 - makeint(GetCharacterFreeSpace(pchar, GOOD_RUM)) < 0 && !CheckAttribute(pchar, "questTemp.WPU.Fraht.TargetPortmanID")) { // если на ТГ
							dialog.text = "Van egy munkám csak neked. Két kereskedelmi hajó van a kikötôben, amelyeknek már útnak kellett volna indulniuk. A helyzet az, hogy a kísérôhajójuk megsérült, és még mindig a szükséges javításokra vár, így nem tudnak egyhamar elindulni.\nAz ön hajója történetesen ideális a feladatra - ráadásul még további rakományt kell elhelyeznem a rakterében. Természetesen a fizetés dupla lesz - mind a szállítmányért, mind a kíséretért.";
							link.l1 = "Milyen érdekes ajánlat! Elfogadom!";
							link.l1.go = "escort_bonus";
							link.l2 = "Köszönöm, de ez nem az én munkám.";
							link.l2.go = "exit";
						} 
						else 
						{ // просто эскорт
							dialog.text = "Van egy munkám csak az ön számára. Két kereskedelmi hajó fekszik jelenleg a kikötônkben - kíséretre van szükségük. Felajánlom, hogy elkíséred ezeket a hajókat a célállomásukig. Megteszed?";
							link.l1 = "Érdekes ajánlat! Elfogadom!";
							link.l1.go = "escort";
							link.l2 = "Köszönöm, de ez nem az én munkám.";
							link.l2.go = "exit";
						}
					}
				}
			}
			else
			{
				//не тот тип корабля
				dialog.text = "Meg kellett volna próbálnod a tartánon őrködni. Ehhez a munkához szüksége van egy tisztességes tűzerővel rendelkező hajóra-katonai vagy raider.";
				link.l1 = "Oké, értem.";
				link.l1.go = "exit";
			}
		}
		else
		{
			//нет работы
			dialog.text = "Sajnos, semmi ilyesmit nem tudok felajánlani. Ugorjon be újra pár nap múlva.";
			link.l1 = "Rendben, meg is teszem.";
			link.l1.go = "exit";
		}
		break;
		
		case "cureer_begin"://доставка почты
		SaveCurrentNpcQuestDateParam(npchar, "work_date");
		
		if (hrand(5) > 1)
		{
			if (sti(RealShips[sti(pchar.Ship.Type)].Spec) == SHIP_SPEC_RAIDER)
			{
				if (pchar.questTemp.WPU.Postcureer == "begin" || pchar.questTemp.WPU.Postcureer == "late" || pchar.questTemp.WPU.Postcureer == "lost" || pchar.questTemp.WPU.Postcureer == "fail" || CheckAttribute(pchar, "questTemp.WPU.Postcureer.LevelUp"))
				{ 
					// если заняты
					dialog.text = "Sajnos, semmi ilyesmit nem tudok felajánlani. Ugorjon be újra pár nap múlva.";
					link.l1 = "Rendben, meg is teszem.";
					link.l1.go = "exit";
				} 
				else 
				{ 
					// если не заняты
					if (sti(pchar.questTemp.WPU.Postcureer.count) > 3 && hrand(1) == 1) 
					{ //если 2 уровень
						dialog.text = "Szóval... Ön már több munkát is elvállalt futárként, és legjobb tudomásom szerint elég sikeres volt benne. Valószínûleg meg tudsz birkózni a feladattal, amit most rád bízok.";
						link.l1 = "Csupa fül vagyok, " + GetAddress_FormToNPC(NPChar) + ".";
						link.l1.go = "Postcureer_LevelUp";
					} 
					else 
					{ // первый уровень
						dialog.text = "Látom, van egy gyors hajód. Felajánlhatok neked egy futármunkát - posta és kereskedelmi papírok kézbesítése.";
						link.l1 = "Ez érdekes. Egyetértek. Hová kell mennem?";
						link.l1.go = "Postcureer";
						link.l2 = "Köszönöm, de ez nem az én munkám.";
						link.l2.go = "exit";
					}
				}
			}
			else
			{
				//не тот тип корабля
				dialog.text = "Sajnálom, de nincs semmim a számodra. Az ilyen jellegű feladatok elvégzéséhez fürge raider hajóra van szükség, és jobb, ha teherfuvarozást vállal a sajátjára.";
				link.l1 = "Oké, értem.";
				link.l1.go = "exit";
			}
		}
		else
		{
			//нет работы
			dialog.text = "Sajnos, semmi ilyesmit nem tudok felajánlani. Ugorjon be újra pár nap múlva.";
			link.l1 = "Rendben, meg is teszem.";
			link.l1.go = "exit";
		}
		break;

///--> ------фрахт со свободным выбором пункта назначения, оплаты и вида груза из предложенного списка---------

		case "Fraht_begin":
			if (hrand(4) < 4)
			{
				if (pchar.questTemp.WPU.Fraht == "begin" || pchar.questTemp.WPU.Fraht == "late" || pchar.questTemp.WPU.Fraht == "lost" || CheckAttribute(pchar, "questTemp.WPU.Escort.Bonus"))//проверка на занятость
				{
					dialog.Text = "De úgy hallottam, hogy a hajóját már kibérelték. Nem adhatok önnek több szállítmányt. Teljesítse a már vállalt kötelezettségeit.";
					link.l1 = "Igen, valószínûleg igaza van.";
					Link.l1.go = "exit";
					break;
				}
				if (1500 - makeint(GetCharacterFreeSpace(pchar, GOOD_RUM)) > 0)//мало места - не даем
				{
					dialog.text = "Túl kevés hely van a raktérben. Tágasabb hajóra van szükségem egy rakományhoz. Javaslom, hogy nézz utána a boltban - a helyi kereskedô gyakran bérel hajókat kisebb szállítmányok szállítására.";
					link.l1 = "Értem, értem. Nos, ahogy mondja.";
					link.l1.go = "exit";
					break;
				}
				if (pchar.questTemp.WPU.Fraht.count > 3 && rand(1) == 0)
				{
					dialog.text = "Nekem jelenleg nincs semmi megfelelô. De már több sikeres szállítást is végrehajtottál. Van egy bizonyos munkám, amit kifejezetten rád bíznék.";
					link.l1 = "Hallgatom. Miféle munkát?";
					link.l1.go = "Fraht_LevelUp";
					break;
				}
				dialog.Text = "Nos, többféle bérlési lehetôséget is tudok ajánlani.";
				link.l1 = "Lássuk csak...";
				Link.l1.go = "Fraht_choise";
			}
			else
			{
				dialog.Text = "Mára már nincs több fuvar. Jöjjön máskor.";
				link.l1 = "Hát jó.";
				Link.l1.go = "exit";
			}
		break;
	
		int iFrahtGoods1, iFrahtGoods2, iFrahtGoods3, iFrahtGoods;
		int iFrahtGoodsQty1, iFrahtGoodsQty2, iFrahtGoodsQty3;
		case "Fraht_choise":
			//выбираем города
			pchar.questTemp.WPU.Fraht.City1 = findCurrentCity1(npchar);
			pchar.questTemp.WPU.Fraht.City2 = findCurrentCity2(npchar);
			pchar.questTemp.WPU.Fraht.City3 = findCurrentCity3(npchar);
			//выбираем товары
			iFrahtGoods1 = hrand(GOOD_PAPRIKA);
			iFrahtGoods2 = hrand(GOOD_PAPRIKA-3);
			iFrahtGoods3 = hrand(GOOD_PAPRIKA-7);
			pchar.questTemp.WPU.Fraht.Goods1 = iFrahtGoods1;
			pchar.questTemp.WPU.Fraht.Goods2 = iFrahtGoods2;
			pchar.questTemp.WPU.Fraht.Goods3 = iFrahtGoods3;
			//определим количество
			iFrahtGoodsQty1 = makeint(GetCharacterFreeSpace(pchar, iFrahtGoods1))/(1+frand(0.5));
			iFrahtGoodsQty2 = makeint(GetCharacterFreeSpace(pchar, iFrahtGoods2))/(1+frand(0.5));
			iFrahtGoodsQty3 = makeint(GetCharacterFreeSpace(pchar, iFrahtGoods3))/(1+frand(0.5));
			if (sti(iFrahtGoodsQty1) > 10000) iFrahtGoodsQty1 = 10000 + rand(500);
			if (sti(iFrahtGoodsQty2) > 10000) iFrahtGoodsQty2 = 10000 + rand(500);
			if (sti(iFrahtGoodsQty3) > 10000) iFrahtGoodsQty3 = 10000 + rand(500);
			pchar.questTemp.WPU.Fraht.GoodsQty1 = iFrahtGoodsQty1;
			pchar.questTemp.WPU.Fraht.GoodsQty2 = iFrahtGoodsQty2;
			pchar.questTemp.WPU.Fraht.GoodsQty3 = iFrahtGoodsQty3;
			pchar.questTemp.WPU.Fraht.StartCity = npchar.city;//город квестодателя
			pchar.questTemp.WPU.Fraht.Chance = rand(4);//форс-мажор
			//определим сроки с учётом рандома
			int daysQty1 = GetMaxDaysFromIsland2Island(GetArealByCityName(pchar.questTemp.WPU.Fraht.StartCity), GetArealByCityName(pchar.questTemp.WPU.Fraht.City1));
			int daysQty2 = GetMaxDaysFromIsland2Island(GetArealByCityName(pchar.questTemp.WPU.Fraht.StartCity), GetArealByCityName(pchar.questTemp.WPU.Fraht.City2));
			int daysQty3 = GetMaxDaysFromIsland2Island(GetArealByCityName(pchar.questTemp.WPU.Fraht.StartCity), GetArealByCityName(pchar.questTemp.WPU.Fraht.City3));
			pchar.questTemp.WPU.Fraht.DaysQty1 = makeint(sti(daysQty1)*(frand(1.3)+0.7));
			pchar.questTemp.WPU.Fraht.DaysQty2 = makeint(sti(daysQty2)*(frand(1.3)+0.7));
			pchar.questTemp.WPU.Fraht.DaysQty3 = makeint(sti(daysQty3)*(frand(1.3)+0.7));
			//установим цену исходя из объёма груза, дальности и сроков
			pchar.questTemp.WPU.Fraht.Money1 = (makeint((sti(iFrahtGoodsQty1) * sti(Goods[iFrahtGoods1].Weight) / sti(Goods[iFrahtGoods1].Units))))*(sti(daysQty1)*2)*sti(daysQty1)/sti(pchar.questTemp.WPU.Fraht.DaysQty1);
			pchar.questTemp.WPU.Fraht.Money2 = (makeint((sti(iFrahtGoodsQty2) * sti(Goods[iFrahtGoods2].Weight) / sti(Goods[iFrahtGoods2].Units))))*(sti(daysQty2)*2)*sti(daysQty2)/sti(pchar.questTemp.WPU.Fraht.DaysQty2);
			pchar.questTemp.WPU.Fraht.Money3 = (makeint((sti(iFrahtGoodsQty3) * sti(Goods[iFrahtGoods3].Weight) / sti(Goods[iFrahtGoods3].Units))))*(sti(daysQty3)*2)*sti(daysQty3)/sti(pchar.questTemp.WPU.Fraht.DaysQty3);
			if (hrand(5) < 4)//три варианта
			{
				dialog.text = "A következô változatok állnak rendelkezésre:\n" +
					"rakomány " + GetGoodsNameAlt(iFrahtGoods1)+ " mennyiségben " + FindRussianQtyString(iFrahtGoodsQty1) + " a város " + XI_ConvertString("Colony" + pchar.questTemp.WPU.Fraht.City1) + ", a " +  FindRussianDaysString(pchar.questTemp.WPU.Fraht.DaysQty1) + ". Fizetés - " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money1)) + "\nrakomány " + GetGoodsNameAlt(iFrahtGoods2)+ " összegben " + FindRussianQtyString(iFrahtGoodsQty2) + " városnak " + XI_ConvertString("Colony" + pchar.questTemp.WPU.Fraht.City2) + ", a " +  FindRussianDaysString(pchar.questTemp.WPU.Fraht.DaysQty2) + ". Fizetés - " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money2)) + "\ncargo " + GetGoodsNameAlt(iFrahtGoods3)+ " összegben " + FindRussianQtyString(iFrahtGoodsQty3) + " a város " + XI_ConvertString("Colony" + pchar.questTemp.WPU.Fraht.City3) + ", a " +  FindRussianDaysString(pchar.questTemp.WPU.Fraht.DaysQty3) + ". Fizetés - " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money3)) + "\nMit választ?";
				Link.l1 = "Én a második változatot választom - charter a városba " + XI_ConvertString("Colony" + pchar.questTemp.WPU.Fraht.City1) + " megrakott " + GetGoodsNameAlt(iFrahtGoods1)+ ".";
				Link.l1.go = "Fraht_Choise_1";
				Link.l2 = "Én a harmadik változatot választom - charter a városba " + XI_ConvertString("Colony" + pchar.questTemp.WPU.Fraht.City2) + " megrakott " + GetGoodsNameAlt(iFrahtGoods2)+ ".";
				Link.l2.go = "Fraht_Choise_2";
				Link.l3 = "Én a harmadik változatot választom - charter a városba " + XI_ConvertString("Colony" + pchar.questTemp.WPU.Fraht.City3) + " megrakott " + GetGoodsNameAlt(iFrahtGoods3)+ ".";
				Link.l3.go = "Fraht_Choise_3";
			}
			else //два варианта
			{
				dialog.text = "A következô változatok állnak rendelkezésre:\n" +
					"rakomány " + GetGoodsNameAlt(iFrahtGoods1)+ " mennyiségben " + FindRussianQtyString(iFrahtGoodsQty1) + " a város " + XI_ConvertString("Colony" + pchar.questTemp.WPU.Fraht.City1) + ", a " +  FindRussianDaysString(pchar.questTemp.WPU.Fraht.DaysQty1) + ". Fizetés - " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money1)) + "\nrakomány " + GetGoodsNameAlt(iFrahtGoods2)+ " összegben " + FindRussianQtyString(iFrahtGoodsQty2) + " a város " + XI_ConvertString("Colony" + pchar.questTemp.WPU.Fraht.City2) + ", a " +  FindRussianDaysString(pchar.questTemp.WPU.Fraht.DaysQty2) + ". Fizetés - " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money2)) + "\nMit választ?";
				Link.l1 = "Én az elsô változatot választom - charter a városba " + XI_ConvertString("Colony" + pchar.questTemp.WPU.Fraht.City1) + " megrakott " + GetGoodsNameAlt(iFrahtGoods1)+ ".";
				Link.l1.go = "Fraht_Choise_1";
				Link.l2 = "Én a második változatot választom - charter a városba " + XI_ConvertString("Colony" + pchar.questTemp.WPU.Fraht.City2) + " megrakott " + GetGoodsNameAlt(iFrahtGoods2)+ ".";
				Link.l2.go = "Fraht_Choise_2";
			}
			Link.l4 = "Sajnos nincs semmi megfelelô számomra.";
			Link.l4.go = "exit";
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
		break;
	
		case "Fraht_Choise_1":
			dialog.text = "Nos, remek! Elintézem a szükséges dokumentumokat, te pedig felkészítheted a hajódat a berakodásra.";
			link.l1 = "Megteszek minden tôlem telhetôt!";
			link.l1.go = "Fraht_Forcemajor";
			AddCharacterGoods(pchar, sti(pchar.questTemp.WPU.Fraht.Goods1), sti(pchar.questTemp.WPU.Fraht.GoodsQty1));
			iFrahtGoods1 = pchar.questTemp.WPU.Fraht.Goods1;
			ReOpenQuestHeader("Fraht");
			AddQuestRecord("Fraht", "1");
			AddQuestUserData("Fraht", "sGoods", GetGoodsNameAlt(iFrahtGoods1));
			AddQuestUserData("Fraht", "sGoodQty", FindRussianQtyString(sti(pchar.questTemp.WPU.Fraht.GoodsQty1)));
			AddQuestUserData("Fraht", "sDay", FindRussianDaysString(sti(pchar.questTemp.WPU.Fraht.DaysQty1)));
			AddQuestUserData("Fraht", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money1)));
			AddQuestUserData("Fraht", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.StartCity+"Gen"));
			AddQuestUserData("Fraht", "sTargetColony",XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.City1+"Gen"));
			SetFunctionTimerCondition("FrahtTime_Over", 0, 0, sti(pchar.questTemp.WPU.Fraht.DaysQty1), false);
			pchar.questTemp.WPU.Fraht.TargetPortmanID = pchar.questTemp.WPU.Fraht.City1+"_portman";
			pchar.questTemp.WPU.Fraht.GoodsAverigePrice = sti(Goods[iFrahtGoods1].Cost);//цена единицы товара
			pchar.questTemp.WPU.Fraht.GoodsAverigeCost = sti(Goods[iFrahtGoods1].Cost)*sti(pchar.questTemp.WPU.Fraht.GoodsQty1);//средняя стоимость товара
			pchar.questTemp.WPU.Fraht.Goods = sti(pchar.questTemp.WPU.Fraht.Goods1);
			pchar.questTemp.WPU.Fraht.GoodsQty = sti(pchar.questTemp.WPU.Fraht.GoodsQty1);
			pchar.questTemp.WPU.Fraht.Money = sti(pchar.questTemp.WPU.Fraht.Money1);
		break;
	
		case "Fraht_Choise_2":
			dialog.text = "Nos, remek! Elintézem a szükséges dokumentumokat, te pedig felkészítheted a hajódat a berakodásra.";
			link.l1 = "Megteszek minden tôlem telhetôt!";
			link.l1.go = "Fraht_Forcemajor";
			AddCharacterGoods(pchar, sti(pchar.questTemp.WPU.Fraht.Goods2), sti(pchar.questTemp.WPU.Fraht.GoodsQty2));
			iFrahtGoods2 = pchar.questTemp.WPU.Fraht.Goods2;
			ReOpenQuestHeader("Fraht");
			AddQuestRecord("Fraht", "1");
			AddQuestUserData("Fraht", "sGoods", GetGoodsNameAlt(iFrahtGoods2));
			AddQuestUserData("Fraht", "sGoodQty", FindRussianQtyString(sti(pchar.questTemp.WPU.Fraht.GoodsQty2)));
			AddQuestUserData("Fraht", "sDay", FindRussianDaysString(sti(pchar.questTemp.WPU.Fraht.DaysQty2)));
			AddQuestUserData("Fraht", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money2)));
			AddQuestUserData("Fraht", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.StartCity+"Gen"));
			AddQuestUserData("Fraht", "sTargetColony",XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.City2+"Gen"));
			SetFunctionTimerCondition("FrahtTime_Over", 0, 0, sti(pchar.questTemp.WPU.Fraht.DaysQty2), false);
			pchar.questTemp.WPU.Fraht.TargetPortmanID = pchar.questTemp.WPU.Fraht.City2+"_portman";
			pchar.questTemp.WPU.Fraht.GoodsAverigePrice = sti(Goods[iFrahtGoods2].Cost);//цена единицы товара
			pchar.questTemp.WPU.Fraht.GoodsAverigeCost = sti(Goods[iFrahtGoods2].Cost)*sti(pchar.questTemp.WPU.Fraht.GoodsQty2);//средняя стоимость товара
			pchar.questTemp.WPU.Fraht.Goods = sti(pchar.questTemp.WPU.Fraht.Goods2);
			pchar.questTemp.WPU.Fraht.GoodsQty = sti(pchar.questTemp.WPU.Fraht.GoodsQty2);
			pchar.questTemp.WPU.Fraht.Money = sti(pchar.questTemp.WPU.Fraht.Money2);
		break;
	
		case "Fraht_Choise_3":
			dialog.text = "Nos, remek! Elintézem a szükséges dokumentumokat, te pedig felkészítheted a hajódat a berakodásra.";
			link.l1 = "Megteszek minden tôlem telhetôt!";
			link.l1.go = "Fraht_Forcemajor";
			AddCharacterGoods(pchar, sti(pchar.questTemp.WPU.Fraht.Goods3), sti(pchar.questTemp.WPU.Fraht.GoodsQty3));
			iFrahtGoods3 = pchar.questTemp.WPU.Fraht.Goods3;
			ReOpenQuestHeader("Fraht");
			AddQuestRecord("Fraht", "1");
			AddQuestUserData("Fraht", "sGoods", GetGoodsNameAlt(iFrahtGoods3));
			AddQuestUserData("Fraht", "sGoodQty", FindRussianQtyString(sti(pchar.questTemp.WPU.Fraht.GoodsQty3)));
			AddQuestUserData("Fraht", "sDay", FindRussianDaysString(sti(pchar.questTemp.WPU.Fraht.DaysQty3)));
			AddQuestUserData("Fraht", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money3)));
			AddQuestUserData("Fraht", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.StartCity+"Gen"));
			AddQuestUserData("Fraht", "sTargetColony",XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.City3+"Gen"));
			SetFunctionTimerCondition("FrahtTime_Over", 0, 0, sti(pchar.questTemp.WPU.Fraht.DaysQty3), false);
			pchar.questTemp.WPU.Fraht.TargetPortmanID = pchar.questTemp.WPU.Fraht.City3+"_portman";
			pchar.questTemp.WPU.Fraht.GoodsAverigePrice = sti(Goods[iFrahtGoods3].Cost);//цена единицы товара
			pchar.questTemp.WPU.Fraht.GoodsAverigeCost = sti(Goods[iFrahtGoods3].Cost)*sti(pchar.questTemp.WPU.Fraht.GoodsQty3);//средняя стоимость товара
			pchar.questTemp.WPU.Fraht.Goods = sti(pchar.questTemp.WPU.Fraht.Goods3);
			pchar.questTemp.WPU.Fraht.GoodsQty = sti(pchar.questTemp.WPU.Fraht.GoodsQty3);
			pchar.questTemp.WPU.Fraht.Money = sti(pchar.questTemp.WPU.Fraht.Money3);
		break;
	
		case "Fraht_Forcemajor":
			pchar.questTemp.WPU.Fraht = "begin";
			sld = characterFromId(pchar.questTemp.WPU.Fraht.TargetPortmanID);
			pchar.questTemp.WPU.Fraht.Nation = sld.nation;//нация получателя
			pchar.questTemp.WPU.Current.TargetIslandID = GetCharacterCurrentIslandId(sld);//ИД целевого ареала
			pchar.questTemp.WPU.Fraht.TargetCity = FindTownOnIsland(pchar.questTemp.WPU.Current.TargetIslandID);
			pchar.questTemp.WPU.Fraht.count = sti(pchar.questTemp.WPU.Fraht.count)+1;//считаем сделанные фрахты
			if (pchar.questTemp.WPU.Fraht.Chance > 3) TraderHunterOnMap(false);//запуск ДУ на глобалке
			if (pchar.questTemp.WPU.Fraht.Chance == 2) FrahtHunterOnSea();//создание ДУ в акватории
			DialogExit();
		break;
	
		case "Fraht_complete":
		ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)//проверка на наличие корабля в порту
		{
			iFrahtGoods = makeint(pchar.questTemp.WPU.Fraht.Goods);
			amount = sti(pchar.questTemp.WPU.Fraht.GoodsQty) - GetSquadronGoods(pchar, sti(pchar.questTemp.WPU.Fraht.Goods));
			if (amount > 0)
			{
				dialog.text = "Lássuk csak. Egy " + GetGoodsNameAlt(iFrahtGoods)+ " mennyiségû " + FindRussianQtyString(pchar.questTemp.WPU.Fraht.GoodsQty) + "rakományt kellett volna szállítania. De ahogy látom, nem' szállította le a teljes szállítmányt - " + FindRussianQtyString(sti(amount)) + " hiányzik.";
				link.l1 = "Ezer cápa! Biztos azok az átkozott patkányok! De ne aggódj, " + GetAddress_FormToNPC(NPChar) + ", megveszem a hiányzó mennyiséget, és leadom az egész tételt.";
				link.l1.go = "Fraht_complete_3";
				break;
			}
			dialog.text = "Lássuk csak. Egy rakományt kellett volna szállítania " + GetGoodsNameAlt(iFrahtGoods)+ " mennyiségben " + FindRussianQtyString(pchar.questTemp.WPU.Fraht.GoodsQty) + ". Így van?";
			link.l1 = "Teljesen helyes, " + GetAddress_FormToNPC(NPChar) + ".";
			link.l1.go = "Fraht_complete_1";
		}
		else
		{
			dialog.text = "Nem látom a hajóját a kikötôben. Feküdjön le, aztán jöjjön vissza hozzám, aztán majd beszélünk.";
			link.l1 = "Rendben, meg is teszem.";
			link.l1.go = "exit";
		}
		break;
	
		case "Fraht_complete_1":
			if (pchar.questTemp.WPU.Fraht == "late")//опоздали
			{
				iTime = makeint(GetQuestPastDayParam("questTemp.Fraht.Late"))+1;
				pchar.questTemp.WPU.Fraht.DayLate = iTime;
				pchar.questTemp.WPU.Fraht.PercentLate = iTime/0.2;
				pchar.questTemp.WPU.Fraht.Money = makeint(sti(pchar.questTemp.WPU.Fraht.Money) - sti(pchar.questTemp.WPU.Fraht.Money)*sti(pchar.questTemp.WPU.Fraht.PercentLate)/100);//снижаем оплату согласно числа дней опоздания
				dialog.text = "Hm... De elkéstél " + FindRussianDaysString(iTime)+ " . Ezért le kell csökkentenem a fuvardíjat. A szerzôdés szerint a bírság a teljes összeg öt százaléka minden egyes késedelmes nap után. Most pedig kérem, vegye fel a " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money)) + ", és próbálja meg a jövôben betartani a szerzôdést.";
				link.l1 = "Nos, ez legalább valami.";
				link.l1.go = "Fraht_complete_2";
				break;
			}
			dialog.text = "Köszönöm a munkáját. Kérjük, vegye fel a fizetést - " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money)) + ".";
			link.l1 = "Köszönjük!";
			link.l1.go = "Fraht_complete_2";
		break;
	
		case "Fraht_complete_2":
			if (pchar.questTemp.WPU.Fraht == "begin")
			{
				pchar.quest.FrahtTime_Over.over = "yes";
				AddQuestRecord("Fraht", "2");
			}
			else
			{
				pchar.quest.FrahtTime_FullOver.over = "yes";//снять второй таймер
				pchar.questTemp.WPU.Fraht.count = sti(pchar.questTemp.WPU.Fraht.count)-1;//опоздавший рейс не засчитываем
				AddQuestRecord("Fraht", "4");
				AddQuestUserData("Fraht", "sDay", FindRussianDaysString(pchar.questTemp.WPU.Fraht.DayLate));
				AddQuestUserData("Fraht", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money)));
			}
			RemoveCharacterGoods(pchar, sti(pchar.questTemp.WPU.Fraht.Goods), sti(pchar.questTemp.WPU.Fraht.GoodsQty));
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.WPU.Fraht.Money));
			CloseQuestHeader("Fraht");
			DeleteAttribute(pchar, "questTemp.WPU.Fraht.TargetPortmanID");
			DeleteAttribute(pchar, "questTemp.WPU.Current.TargetIslandID");
			pchar.questTemp.WPU.Fraht = "complete";
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
			AddCharacterExpToSkill(pchar, "Sailing", 100);//навигация
			AddCharacterExpToSkill(pchar, "Commerce", 100);//торговля
			AddCharacterExpToSkill(pchar, "Leadership", 50);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
			ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Fraht.Nation), 2);
			Group_DeleteGroup("Fraht_Attack");
			DialogExit();
		break;
	
		case "Fraht_complete_bad":
			dialog.text = "Leszállította a szállítmányt? Nagyon szép. Valójában magunknak kellett megvennünk, hogy átadjuk a címzettnek! És elég drága volt, ne feledje. Tehát, ha vissza akarja állítani a jóindulatát, akkor meg kell térítenie a költségeinket, és a büntetést is ki kell fizetnie. Ami a rakományt illeti, megtarthatja - nekünk már nincs rá szükségünk.";
			link.l1 = "Igen, persze. Mennyiért?";
			link.l1.go = "Fraht_complete_bad_1";
		break;
	
		case "Fraht_complete_bad_1":
			pchar.questTemp.WPU.Fraht.GoodsAverigeCost = sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost)*3;
			dialog.text = "Az áruk árának háromszorosa. Ez az összeg " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost)) + ".";
			if (sti(Pchar.money) >= sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost))
			{
				link.l1 = "Ez elég sok. De az üzlet az üzlet. Rendben, itt a pénzed.";
				link.l1.go = "Fraht_complete_pay";
			}
			link.l2 = "Megôrültél? Ilyen felháborító összeget követelni a kapzsiság határa! Nem kapsz tôlem semmit!";
			link.l2.go = "Fraht_complete_fail";
		break;
	
		case "Fraht_complete_pay":
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost));
			dialog.text = "Bölcs döntés. Most már látom, hogy valóban komoly ember vagy. Azt hiszem, a jövôben még dolgozhatunk együtt.";
			link.l1 = "Köszönöm, és most mennem kell.";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar,"nobility", 12);
			ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Fraht.Nation), 30);
			if (CheckAttribute(pchar, "questTemp.WPU.Escort.Bonus"))
			{
				AddQuestRecord("Escort", "8");
				AddQuestUserData("Escort", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost)));
				CloseQuestHeader("Escort");
				pchar.questTemp.WPU.Escort = "complete";
				DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
				DeleteAttribute(pchar, "questTemp.WPU.Escort.Bonus");
			}
			else
			{
				AddQuestRecord("Fraht", "6");
				AddQuestUserData("Fraht", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost)));
				CloseQuestHeader("Fraht");
				pchar.questTemp.WPU.Fraht = "complete";
				DeleteAttribute(pchar, "questTemp.WPU.Fraht.TargetPortmanID");
			}
			DeleteAttribute(pchar, "questTemp.WPU.Current.TargetIslandID");
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
			AddCharacterExpToSkill(pchar, "Sailing", 100);//навигация
			AddCharacterExpToSkill(pchar, "Commerce", 50);//торговля
			AddCharacterExpToSkill(pchar, "Leadership", 70);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 70);//везение
		break;
	
		case "Fraht_complete_fail":
			dialog.text = "Ó, értem... Nos, ebben az esetben soha többé ne mutatkozzon a " + NationNameGenitive(sti(pchar.questTemp.WPU.Fraht.Nation)) + "egyetlen kikötôi hatóságnál sem ! Tûnj el!";
			link.l1 = "Biztos nem maradtam le semmirôl...";
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.WPU.Escort.Bonus"))
			{
				AddQuestRecord("Escort", "9");
				AddQuestUserData("Escort", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost)));
				CloseQuestHeader("Escort");
				pchar.questTemp.WPU.Escort = "complete";
				DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
				DeleteAttribute(pchar, "questTemp.WPU.Escort.Bonus");
			}
			else
			{
				AddQuestRecord("Fraht", "7");
				CloseQuestHeader("Fraht");
				DeleteAttribute(pchar, "questTemp.WPU.Fraht.TargetPortmanID");
			}
			DeleteAttribute(pchar, "questTemp.WPU.Current.TargetIslandID");
			pchar.questTemp.WPU.Fraht = "fail";
			ChangeCharacterComplexReputation(pchar,"nobility", -10);
		break;
	
		case "Fraht_complete_3":
			dialog.text = "Siess, a címzett már tudja, hogy megérkezett a hajód, és aggódik a rakományáért.";
			link.l1 = "Ebben az esetben nem fogok több idôt vesztegetni!";
			link.l1.go = "exit";
		break;
	//фрахт <--
	
/// -------------------------------работа курьером по доставке почты-------------------------------------

		case "Postcureer":
			pchar.questTemp.WPU.Postcureer.City = findCurrentCity2(npchar);
			pchar.questTemp.WPU.Postcureer.StartCity = npchar.city;//город квестодателя
			pchar.questTemp.WPU.Postcureer.Chance = rand(4);//форс-мажор
			idaysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(pchar.questTemp.WPU.Postcureer.StartCity), GetArealByCityName(pchar.questTemp.WPU.Postcureer.City));
			pchar.questTemp.WPU.Postcureer.DaysQty = makeint(sti(idaysQty)*(frand(0.3)+0.7)); 
			if (sti(pchar.questTemp.WPU.Postcureer.DaysQty) == 1) pchar.questTemp.WPU.Postcureer.DaysQty = 2;
			pchar.questTemp.WPU.Postcureer.Money = (sti(idaysQty)*1000)*sti(idaysQty)/sti(pchar.questTemp.WPU.Postcureer.DaysQty)*(1+frand(0.2));
			dialog.text = "Ezt a csomagot a " + XI_ConvertString("Colony" + pchar.questTemp.WPU.Postcureer.City) + ", a " +  FindRussianDaysString(pchar.questTemp.WPU.Postcureer.DaysQty) + ", a lehetô leghamarabb a kikötôi hatósághoz kell eljuttatni. Fizetés - " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money))".";
			link.l1 = "Egyetértek!";
			link.l1.go = "Postcureer_1";
			link.l2 = "Hmm... De én nem arra megyek. Sajnálom, de vissza kell utasítanom.";
			link.l2.go = "exit";
		break;
	
		case "Postcureer_1":
			dialog.text = "Kiváló! Számítok rád. Itt a csomag.";
			link.l1 = "Azonnal útnak indulok!";
			link.l1.go = "exit";
			GiveItem2Character(pchar, "PostLetters");
			pchar.questTemp.WPU.Postcureer = "begin";
			pchar.questTemp.WPU.Postcureer.TargetPortmanID = pchar.questTemp.WPU.Postcureer.City +"_portman";//ИД портмана
			sld = characterFromId(pchar.questTemp.WPU.Postcureer.TargetPortmanID);
			pchar.questTemp.WPU.Postcureer.Nation = sld.nation;//нация получателя
			pchar.questTemp.WPU.Current.TargetIslandID = GetCharacterCurrentIslandId(sld);//ИД целевого ареала
			pchar.questTemp.WPU.Postcureer.EnemyNation = GetEnemyNationToMainCharacter();//вражеская нация
			i = 0;
			while (sti(pchar.questTemp.WPU.Postcureer.EnemyNation) == PIRATE)
			{
				pchar.questTemp.WPU.Postcureer.EnemyNation = GetEnemyNationToMainCharacter();
				i++;
				if(i > 5) pchar.questTemp.WPU.Postcureer.EnemyNation = FindEnemyNation2NationWithoutPirates(sti(pchar.BaseNation));
			}
			pchar.questTemp.WPU.Postcureer.count = sti(pchar.questTemp.WPU.Postcureer.count)+1;//считаем сделанные доставки
			//запустить регату при счетчике > 4
			if (!CheckAttribute(pchar, "questTemp.RegataGo") && sti(pchar.questTemp.WPU.Postcureer.count) > 4)
			{
				pchar.questTemp.RegataGo = "true";
				pchar.questTemp.Regata.CureerCity = FindFriendCityToMC(true);//город, в котором вестовой подойдет
				if (pchar.questTemp.Regata.CureerCity == "PortRoyal") pchar.questTemp.Regata.CureerCity = "SentJons";
				pchar.quest.Regata_Cureer.win_condition.l1 = "location";
				pchar.quest.Regata_Cureer.win_condition.l1.location = pchar.questTemp.Regata.CureerCity+"_town";
				pchar.quest.Regata_Cureer.function = "PrepareToRegata";
				log_testinfo(pchar.questTemp.Regata.CureerCity);
			}
			if (pchar.questTemp.WPU.Postcureer.Chance > 3) EnemyNationHunterOnMap(false);//запуск перехватчиков на глобалке
			if (pchar.questTemp.WPU.Postcureer.Chance == 2) FrahtHunterOnSea();//создание перехватчиков в акватории
			ReOpenQuestHeader("Postcureer");
			AddQuestRecord("Postcureer", "1");
			AddQuestUserData("Postcureer", "sDay", FindRussianDaysString(sti(pchar.questTemp.WPU.Postcureer.DaysQty)));
			AddQuestUserData("Postcureer", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money)));
			AddQuestUserData("Postcureer", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen"));
			AddQuestUserData("Postcureer", "sTargetColony",XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.City)); // belamour gen
			AddQuestUserData("Postcureer", "sSex1", GetSexPhrase("",""));
			SetFunctionTimerCondition("PostcureerTime_Over", 0, 0, sti(pchar.questTemp.WPU.Postcureer.DaysQty), false);
		break;
	
		case "Postcureer_complete":
			if (pchar.questTemp.WPU.Postcureer == "late")//опоздали
			{
				iTime = makeint(GetQuestPastDayParam("questTemp.Postcureer.Late"))+1;
				pchar.questTemp.WPU.Postcureer.DayLate = iTime;
				pchar.questTemp.WPU.Postcureer.PercentLate = iTime/0.1;
				pchar.questTemp.WPU.Postcureer.Money = makeint(sti(pchar.questTemp.WPU.Postcureer.Money) - sti(pchar.questTemp.WPU.Postcureer.Money)*sti(pchar.questTemp.WPU.Postcureer.PercentLate)/100);//снижаем оплату согласно числа дней опоздания
				dialog.text = "Hm... De elkéstél " + FindRussianDaysString(iTime)+ " . Ezért le kell csökkentenem a fizetését a munkáért. A szerzôdés szerint a kötbér a teljes összeg öt százaléka minden egyes késedelmes nap után. Most pedig kérem, vegye fel a " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money)) + ", és próbálja meg a jövôben betartani a szerzôdést.";
				link.l1 = "Nos, ez legalább valami.";
				link.l1.go = "Postcureer_complete_1";
				break;
			}
			dialog.text = "Köszönöm a munkáját. Kérjük, vegye fel a fizetést - " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money)) + ".";
			link.l1 = "Köszönjük!";
			link.l1.go = "Postcureer_complete_1";
		break;
	
		case "Postcureer_complete_1":
			if (pchar.questTemp.WPU.Postcureer == "begin")
			{
				pchar.quest.PostcureerTime_Over.over = "yes";
				AddQuestRecord("Postcureer", "2");
			}
			else
			{
				pchar.quest.PostcureerTime_FullOver.over = "yes";//снять второй таймер
				pchar.questTemp.WPU.Postcureer.count = sti(pchar.questTemp.WPU.Postcureer.count)-1;//опоздавший рейс не засчитываем
				AddQuestRecord("Postcureer", "4");
				AddQuestUserData("Postcureer", "sDay", FindRussianDaysString(pchar.questTemp.WPU.Postcureer.DayLate));
				AddQuestUserData("Postcureer", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money)));
				AddQuestUserData("Postcureer", "sSex", GetSexPhrase("",""));
			}
			RemoveItems(PChar, "PostLetters", 1);
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.WPU.Postcureer.Money));
			CloseQuestHeader("Postcureer");
			DeleteAttribute(pchar, "questTemp.WPU.Postcureer.TargetPortmanID");
			DeleteAttribute(pchar, "questTemp.WPU.Current.TargetIslandID");
			pchar.questTemp.WPU.Postcureer = "complete";
			AddCharacterExpToSkill(pchar, "Sailing", 100);//навигация
			AddCharacterExpToSkill(pchar, "Sneak", 100);//скрытность
			AddCharacterExpToSkill(pchar, "Leadership", 100);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
			ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Postcureer.Nation), 2);
			Group_DeleteGroup("Fraht_Attack");
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
			Achievment_Set("ach_CL_118");
			DialogExit();
		break;
	
		case "Postcureer_complete_bad":
			dialog.text = "És most mihez kezdjünk vele? Az emberek isten tudja mióta vártak rá, és te csak ma hoztad el. Rendben, add ide nekem - talán még lesz valami haszna. És remélem, megérti, hogy most már nem kell fizetni érte.";
			link.l1 = "Persze, hogy értem. Fogja a csomagját. Viszontlátásra.";
			link.l1.go = "exit";
			RemoveItems(PChar, "PostLetters", 1);
			CloseQuestHeader("Postcureer");
			DeleteAttribute(pchar, "questTemp.WPU.Postcureer.TargetPortmanID");
			DeleteAttribute(pchar, "questTemp.WPU.Current.TargetIslandID");
			Group_DeleteGroup("Fraht_Attack");
			pchar.questTemp.WPU.Postcureer = "fail";
		break;
	
/// ---------------------------работа в качестве эскорта для торговых кораблей----------------------------

		case "escort":
			pchar.questTemp.WPU.Escort.ShipName1 = GenerateRandomNameToShip(sti(npchar.nation));//имена кораблей
			pchar.questTemp.WPU.Escort.ShipName2 = GenerateRandomNameToShip(sti(npchar.nation));
			pchar.questTemp.WPU.Escort.Goods1 = rand(GOOD_PAPRIKA);
			pchar.questTemp.WPU.Escort.Goods2 = rand(GOOD_PAPRIKA);
			pchar.questTemp.WPU.Escort.City = findCurrentCity1(npchar);//целевой город
			pchar.questTemp.WPU.Escort.StartCity = npchar.city;//город квестодателя
			pchar.questTemp.WPU.Escort.Chance = rand(4);//форс-мажор
			idaysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(pchar.questTemp.WPU.Escort.StartCity), GetArealByCityName(pchar.questTemp.WPU.Escort.City));
			pchar.questTemp.WPU.Escort.DaysQty = makeint(sti(idaysQty)*(frand(0.5)+1)); 
			pchar.questTemp.WPU.Escort.Money = (sti(idaysQty)*2000)*sti(idaysQty)/sti(pchar.questTemp.WPU.Escort.DaysQty)*(1+frand(0.2));
			dialog.text = "Tehát, neked kell kísérni a hajókat '" + pchar.questTemp.WPU.Escort.ShipName1 + "' és '" + pchar.questTemp.WPU.Escort.ShipName2 + "' a városba " + XI_ConvertString("Colony" + pchar.questTemp.WPU.Escort.City) + ", a " +  FindRussianDaysString(pchar.questTemp.WPU.Escort.DaysQty) + ". Fizetés - " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money))". Mindkét hajónak épségben és épségben kell célba érnie. A hajókat a helyi kikötôi hatóság tisztviselôjénél adjátok le. Ô lesz az, aki ki is fogja fizetni neked a munkát.";
			link.l1 = "Minden világosnak tûnik. Folytathatom?";
			link.l1.go = "escort_1";
			link.l2 = "Hmm... De én nem arra megyek. Sajnálom, de vissza kell utasítanom.";
			link.l2.go = "exit";
		break;
	
		case "escort_1":
			dialog.text = "Csak rajta. Azok a hajók mostantól a te parancsnokságod alatt állnak.";
			link.l1 = "Akkor kihajózom!";
			link.l1.go = "escort_add_ships";
			pchar.questTemp.WPU.Escort = "begin";
			pchar.questTemp.WPU.Escort.ShipNation = npchar.nation;//нация отправителя
			pchar.questTemp.WPU.Escort.TargetPortmanID = pchar.questTemp.WPU.Escort.City +"_portman";//ИД портмана
			sld = characterFromId(pchar.questTemp.WPU.Escort.TargetPortmanID);
			pchar.questTemp.WPU.Escort.Nation = sld.nation;//нация получателя
			pchar.questTemp.WPU.Current.TargetIslandID = GetCharacterCurrentIslandId(sld);//ИД целевого ареала
			pchar.questTemp.WPU.Escort.EnemyNation = GetEnemyNationToMainCharacter();//вражеская нация
			i = 0;
			while (sti(pchar.questTemp.WPU.Escort.EnemyNation) == PIRATE)
			{
				pchar.questTemp.WPU.Escort.EnemyNation = GetEnemyNationToMainCharacter();
				i++;
				if(i > 5) pchar.questTemp.WPU.Escort.EnemyNation = FindEnemyNation2NationWithoutPirates(sti(pchar.BaseNation));
			}
			pchar.questTemp.WPU.Escort.count = sti(pchar.questTemp.WPU.Escort.count)+1;//считаем сделанные эскорты
			if (pchar.questTemp.WPU.Escort.Chance > 3) EnemyNationHunterOnMap(false);//запуск перехватчиков на глобалке
			if (pchar.questTemp.WPU.Escort.Chance == 3) TraderHunterOnMap(false);//запуск ДУ на глобалке
			if (pchar.questTemp.WPU.Escort.Chance < 2) FrahtHunterOnSea();//создание перехватчиков в акватории
			ReOpenQuestHeader("Escort");
			AddQuestRecord("Escort", "1");
			AddQuestUserData("Escort", "sDay", FindRussianDaysString(sti(pchar.questTemp.WPU.Escort.DaysQty)));
			AddQuestUserData("Escort", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money)));
			AddQuestUserData("Escort", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen"));
			AddQuestUserData("Escort", "sTargetColony",XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.City)); // belamour gen
			SetFunctionTimerCondition("EscortTime_Over", 0, 0, sti(pchar.questTemp.WPU.Escort.DaysQty), false);
		break;
	
		case "escort_add_ships":
			int iGoods1, iGoods2, iSpace1, iSpace2, ShipType, Rank;
			int iNation = pchar.questTemp.WPU.Escort.ShipNation;
			int iLifeday = sti(pchar.questTemp.WPU.Escort.DaysQty)+10;
			string sTemp;
	        for (i=1; i<=2; i++)
	        {
				ShipType = GetRandomShipType(GetClassFlag(sti(RealShips[sti(pchar.Ship.Type)].Class)), FLAG_SHIP_TYPE_MERCHANT, FLAG_SHIP_NATION_ANY);
				Rank = 5 * (6 - sti(RealShips[sti(pchar.Ship.Type)].Class)) + rand(5);
				if (i == 1) sTemp = pchar.questTemp.WPU.Escort.ShipName1;
				if (i == 2) sTemp = pchar.questTemp.WPU.Escort.ShipName2;
				if (i == 2) ShipType = SHIP_FLEUT;//один всегда флейт
	            sld = GetCharacter(NPC_GenerateCharacter("EscortCaptain_"+i, "trader_"+(rand(15)+1), "man", "man", Rank, iNation, iLifeday, true, "citizen"));
				FantomMakeSmallSailor(sld, ShipType, sTemp, -1, 10+rand(10), 10+rand(10), 10+rand(10), 10+rand(10), 10+rand(10));
				DeleteAttribute(sld, "SaveItemsForDead");
				DeleteAttribute(sld, "DontClearDead");
				SetCharacterGoods(sld, GOOD_FOOD, 400+rand(200));
				SetCharacterGoods(sld, GOOD_MEDICAMENT, 60+rand(30));
	            iGoods1 = sti(pchar.questTemp.WPU.Escort.Goods1);
				iSpace1 = GetCharacterFreeSpace(sld, iGoods1);
				iSpace1 = makeint(iSpace1/2 + rand(iSpace1/2));
				iGoods2 = sti(pchar.questTemp.WPU.Escort.Goods2);
				iSpace2 = GetCharacterFreeSpace(sld, iGoods2);
				iSpace2 = makeint(iSpace2/2 + rand(iSpace2/2));
				if (i == 1) SetCharacterGoods(sld, iGoods1, iSpace1);
				if (i == 2) SetCharacterGoods(sld, iGoods2, iSpace2);
				sld.CompanionEnemyEnable = false; //всегда друзья
	            SetCompanionIndex(pchar, -1, sti(sld.index));
				sld.loyality = MAX_LOYALITY;
				SetCharacterRemovable(sld, false);
				sld.Dialog.Filename = "Common_portman.c";
				sld.dialog.currentnode = "Escort_companion";
				pchar.quest.Escort_fail.win_condition.l1 = "NPC_Death";
				pchar.quest.Escort_fail.win_condition.l1.character = "EscortCaptain_1";
				pchar.quest.Escort_fail.win_condition.l2 = "NPC_Death";
				pchar.quest.Escort_fail.win_condition.l2.character = "EscortCaptain_2";
				pchar.quest.Escort_fail.function = "Escort_failed";
	        }
			if (pchar.questTemp.WPU.Escort.Chance > 3) EnemyNationHunterOnMap(false);//запуск перехватчиков на глобалке
			if (pchar.questTemp.WPU.Escort.Chance == 3) TraderHunterOnMap(false);//запуск ДУ на глобалке
			if (pchar.questTemp.WPU.Escort.Chance < 2) FrahtHunterOnSea();//создание перехватчиков в акватории
			DialogExit();
		break;
	
		case "Escort_complete":
		ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)//проверка на наличие корабля в порту
		{
			//проверяем, все ли корабли
			if (GetCharacterIndex("EscortCaptain_1") == -1 || GetCharacterIndex("EscortCaptain_2") == -1)
			{
				dialog.text = "Hmm... Csak egy hajót látok a kíséretedben. Ez így van?";
				link.l1 = "Igen, " + GetAddress_FormToNPC(NPChar) + ". Egy másik elsüllyedt egy ellenséges századdal vívott csatában.";
				if (CheckAttribute(pchar, "questTemp.WPU.Escort.Bonus")) 
				{
					link.l1.go = "EscortBonus_complete_fail";
				}
				else
				{
					link.l1.go = "Escort_complete_fail";
				}
				break;
			}
			iGoods = pchar.questTemp.WPU.Escort.Goods;
			if (CheckAttribute(pchar, "questTemp.WPU.Escort.Bonus")) 
			{
				//pchar.questTemp.WPU.Escort.Money = sti(pchar.questTemp.WPU.Escort.Money)+sti(pchar.questTemp.WPU.Escort.BonusMoney);
				pchar.questTemp.WPU.Escort.Money = sti(pchar.questTemp.WPU.Escort.TotalMoney);
				amount = sti(pchar.questTemp.WPU.Escort.GoodsQty) - GetSquadronGoods(pchar, sti(pchar.questTemp.WPU.Escort.Goods));
				if (amount > 0)
				{
					dialog.text = "Rendben, akkor. Úgy volt, hogy hajókat kísérsz és szállítod a " + GetGoodsNameAlt(iGoods)+ " mennyiségû " + FindRussianQtyString(sti(pchar.questTemp.WPU.Escort.GoodsQty)) + "rakományt. De látom, hogy nem szállítottad le a teljes szállítmányt - hiányzik " + FindRussianQtyString(sti(amount)) + " .";
					link.l1 = "Ezer cápa! Biztos azok az átkozott patkányok! De ne aggódj, " + GetAddress_FormToNPC(NPChar) + ", megveszem a hiányzó mennyiséget, és leadom az egész tételt.";
					link.l1.go = "Fraht_complete_3";
					break;
				}
			}
			if (pchar.questTemp.WPU.Escort == "late")//опоздали
			{
				iTime = makeint(GetQuestPastDayParam("questTemp.Escort.Late"))+1;
				pchar.questTemp.WPU.Escort.DayLate = iTime;
				pchar.questTemp.WPU.Escort.PercentLate = iTime/0.1;
				pchar.questTemp.WPU.Escort.Money = makeint(sti(pchar.questTemp.WPU.Escort.Money) - sti(pchar.questTemp.WPU.Escort.Money)*sti(pchar.questTemp.WPU.Escort.PercentLate)/100);//снижаем оплату согласно числа дней опоздания
				dialog.text = "Hm... De elkéstél " + FindRussianDaysString(iTime)+ " . Ezért le kell csökkentenem a munkáért járó fizetését. A szerzôdés szerint a bírság a teljes összeg öt százaléka minden egyes késedelmes nap után. Most pedig kérem, vegye fel a " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money)) + ", és próbálja meg a jövôben betartani a szerzôdést.";
				link.l1 = "Nos, ez legalább valami.";
				link.l1.go = "Escort_complete_1";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.WPU.Escort.Bonus")) 
			{
				dialog.text = "Rendben, akkor. Úgy volt, hogy hajókat kísérsz és szállítod a " + GetGoodsNameAlt(iGoods)+ " rakományt " + FindRussianQtyString(sti(pchar.questTemp.WPU.Escort.GoodsQty)) + "mennyiségben. Köszönöm a munkádat. Kérem, vegye át a fizetségét - " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money)) + ".";
			}
			else
			{
				dialog.text = "Köszönöm a munkáját. Kérjük, vegye fel a fizetést - " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money)) + ".";
			}
			link.l1 = "Köszönjük!";
			link.l1.go = "Escort_complete_1";
		}
		else
		{
			dialog.text = "Nem látom a hajóját a kikötôben. Feküdjön le, aztán jöjjön vissza hozzám, aztán majd beszélünk.";
			link.l1 = "Rendben, meg is teszem.";
			link.l1.go = "exit";
		}
		break;
	
		case "Escort_complete_1":
			pchar.quest.Escort_fail.over = "yes";//снять прерывание
			if (pchar.questTemp.WPU.Escort == "begin")
			{
				pchar.quest.EscortTime_Over.over = "yes";//снять таймер
				AddQuestRecord("Escort", "2");
			}
			else
			{
				pchar.questTemp.WPU.Escort.count = sti(pchar.questTemp.WPU.Escort.count)-1;//опоздавший рейс не засчитываем
				pchar.quest.EscortTime_FullOver.over = "yes";//снять второй таймер
				if (CheckAttribute(pchar, "questTemp.WPU.Escort.Bonus"))
				{
					pchar.questTemp.WPU.Fraht.count = sti(pchar.questTemp.WPU.Fraht.count)-1;//опоздавший рейс не засчитываем
				}
				AddQuestRecord("Escort", "4");
				AddQuestUserData("Escort", "sDay", FindRussianDaysString(pchar.questTemp.WPU.Escort.DayLate));
				AddQuestUserData("Escort", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money)));
			}
			RemoveCharacterCompanion(Pchar, characterFromID("EscortCaptain_1"));//удалим компаньонов
			RemoveCharacterCompanion(Pchar, characterFromID("EscortCaptain_2"));
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.WPU.Escort.Money));
			if (CheckAttribute(pchar, "questTemp.WPU.Escort.Bonus")) RemoveCharacterGoods(pchar, sti(pchar.questTemp.WPU.Escort.Goods), sti(pchar.questTemp.WPU.Escort.GoodsQty));
			CloseQuestHeader("Escort");
			DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
			DeleteAttribute(pchar, "questTemp.WPU.Current.TargetIslandID");
			DeleteAttribute(pchar, "questTemp.WPU.Escort.Bonus");
			pchar.questTemp.WPU.Escort = "complete";
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
			AddCharacterExpToSkill(pchar, "Sailing", 100);//навигация
			AddCharacterExpToSkill(pchar, "Defence", 100);//защита
			AddCharacterExpToSkill(pchar, "Leadership", 100);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
			ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Escort.Nation), 2);
			Group_DeleteGroup("Fraht_Attack");
			DialogExit();
		break;
	
		case "escort_bonus":
			pchar.questTemp.WPU.Escort.ShipName1 = GenerateRandomNameToShip(sti(npchar.nation));//имена кораблей
			pchar.questTemp.WPU.Escort.ShipName2 = GenerateRandomNameToShip(sti(npchar.nation));
			pchar.questTemp.WPU.Escort.Goods = 	hrand(GOOD_PAPRIKA);//для ГГ
			pchar.questTemp.WPU.Escort.Goods1 = hrand(GOOD_PAPRIKA-3);
			pchar.questTemp.WPU.Escort.Goods2 = hrand(GOOD_PAPRIKA-5);
			iGoods = pchar.questTemp.WPU.Escort.Goods;
			iGoodsQty = makeint(GetCharacterFreeSpace(pchar, iGoods))-(50+rand(100));//количество груза
			pchar.questTemp.WPU.Escort.GoodsQty = iGoodsQty;
			pchar.questTemp.WPU.Escort.City = findCurrentCity1(npchar);//целевой город
			pchar.questTemp.WPU.Escort.StartCity = npchar.city;//город квестодателя
			pchar.questTemp.WPU.Escort.Chance = rand(4);//форс-мажор
			idaysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(pchar.questTemp.WPU.Escort.StartCity), GetArealByCityName(pchar.questTemp.WPU.Escort.City));
			pchar.questTemp.WPU.Escort.DaysQty = makeint(sti(idaysQty)*(frand(0.5)+1));//дни
			pchar.questTemp.WPU.Escort.Money = (sti(idaysQty)*2000)*sti(idaysQty)/sti(pchar.questTemp.WPU.Escort.DaysQty)*(1+frand(0.2));//оплата за сопровождение
			pchar.questTemp.WPU.Escort.BonusMoney = (makeint((sti(iGoodsQty) * sti(Goods[iGoods].Weight) / sti(Goods[iGoods].Units))))*(sti(idaysQty)*2)*sti(idaysQty)/sti(pchar.questTemp.WPU.Escort.DaysQty);//оплата за фрахт
			pchar.questTemp.WPU.Escort.TotalMoney = sti(pchar.questTemp.WPU.Escort.Money)+sti(pchar.questTemp.WPU.Escort.BonusMoney); // общая сумма
			dialog.text = "Tehát, neked kell kísérned a hajókat '" + pchar.questTemp.WPU.Escort.ShipName1 + "' és '" + pchar.questTemp.WPU.Escort.ShipName2 + "' városba " + XI_ConvertString("Colony" + pchar.questTemp.WPU.Escort.City) + ", a " +  FindRussianDaysString(pchar.questTemp.WPU.Escort.DaysQty) + ". Fizetés - " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money))+ "\nAz önök hajójára helyezem a rakományt " + GetGoodsNameAlt(iGoods)+ " összegben " + FindRussianQtyString(iGoodsQty) + ". Fizetés a szállításért - " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.BonusMoney))+".";
			link.l1 = "Minden világosnak tûnik. Folytathatom?";
			link.l1.go = "escort_bonus_1";
			link.l2 = "Hmm... De én nem arra megyek. Sajnálom, de vissza kell utasítanom.";
			link.l2.go = "exit";
		break;
	
		case "escort_bonus_1":
			dialog.text = "Kitûnô! Vedd át a század parancsnokságát.";
			link.l1 = "Akkor kihajózom!";
			link.l1.go = "escort_add_ships";
			iGoods = pchar.questTemp.WPU.Escort.Goods;
			AddCharacterGoods(pchar, sti(pchar.questTemp.WPU.Escort.Goods), sti(pchar.questTemp.WPU.Escort.GoodsQty));
			pchar.questTemp.WPU.Escort = "begin";
			pchar.questTemp.WPU.Escort.Bonus = "true";
			pchar.questTemp.WPU.Escort.ShipNation = npchar.nation;//нация отправителя
			pchar.questTemp.WPU.Escort.TargetPortmanID = pchar.questTemp.WPU.Escort.City +"_portman";//ИД портмана
			sld = characterFromId(pchar.questTemp.WPU.Escort.TargetPortmanID);
			pchar.questTemp.WPU.Escort.Nation = sld.nation;//нация получателя
			pchar.questTemp.WPU.Current.TargetIslandID = GetCharacterCurrentIslandId(sld);//ИД целевого ареала
			pchar.questTemp.WPU.Escort.EnemyNation = GetEnemyNationToMainCharacter();//вражеская нация
			i = 0;
			while (sti(pchar.questTemp.WPU.Escort.EnemyNation) == PIRATE)
			{
				pchar.questTemp.WPU.Escort.EnemyNation = GetEnemyNationToMainCharacter();
				i++;
				if(i > 5) pchar.questTemp.WPU.Escort.EnemyNation = FindEnemyNation2NationWithoutPirates(sti(pchar.BaseNation));
			}
			pchar.questTemp.WPU.Escort.count = sti(pchar.questTemp.WPU.Escort.count)+1;//считаем сделанные эскорты
			pchar.questTemp.WPU.Fraht.count = sti(pchar.questTemp.WPU.Fraht.count)+1;//считаем сделанные фрахты
			if (pchar.questTemp.WPU.Escort.Chance > 3) EnemyNationHunterOnMap(false);//запуск перехватчиков на глобалке
			if (pchar.questTemp.WPU.Escort.Chance == 3) TraderHunterOnMap(false);//запуск ДУ на глобалке
			if (pchar.questTemp.WPU.Escort.Chance < 3) FrahtHunterOnSea();//создание перехватчиков в акватории
			ReOpenQuestHeader("Escort");
			AddQuestRecord("Escort", "6");
			AddQuestUserData("Escort", "sDay", FindRussianDaysString(sti(pchar.questTemp.WPU.Escort.DaysQty)));
			AddQuestUserData("Escort", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money)));
			AddQuestUserData("Escort", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen"));
			AddQuestUserData("Escort", "sTargetColony",XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.City));
			AddQuestUserData("Escort", "sGoods", GetGoodsNameAlt(iGoods));
			AddQuestUserData("Escort", "sGoodQty", FindRussianQtyString(sti(pchar.questTemp.WPU.Escort.GoodsQty)));
			AddQuestUserData("Escort", "sMoney1", FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.BonusMoney)));
			pchar.questTemp.WPU.Fraht.GoodsAverigePrice = sti(Goods[iGoods].Cost);//цена единицы товара
			pchar.questTemp.WPU.Fraht.GoodsAverigeCost = sti(Goods[iGoods].Cost)*sti(pchar.questTemp.WPU.Escort.GoodsQty);//средняя стоимость товара
			SetFunctionTimerCondition("EscortTime_Over", 0, 0, sti(pchar.questTemp.WPU.Escort.DaysQty), false);
		break;
	
		case "Escort_complete_fail":
			dialog.text = "Hihetetlen! És mi szükségünk van rád? Hogy engedhetted meg, hogy ez megtörténjen?! Remélem, megérti, hogy a jutalom most már szóba sem jöhet.";
			link.l1 = "Persze, hogy értem... Nos, üdvözlöm.";
			link.l1.go = "exit";
			pchar.quest.Escort_fail.over = "yes";//снять прерывание
			pchar.quest.EscortTime_Over.over = "yes";//снять прерывание // patch-2
			if (GetCharacterIndex("EscortCaptain_1") == -1) RemoveCharacterCompanion(pchar, characterFromID("EscortCaptain_2"));
			else RemoveCharacterCompanion(pchar, characterFromID("EscortCaptain_1"));
			AddQuestRecord("Escort", "11");
			CloseQuestHeader("Escort");
			pchar.questTemp.WPU.Escort.count = sti(pchar.questTemp.WPU.Escort.count)-1;//рейс не засчитываем
			DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
			DeleteAttribute(pchar, "questTemp.WPU.Current.TargetIslandID");
			pchar.questTemp.WPU.Escort = "complete";
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
			AddCharacterExpToSkill(pchar, "Sailing", 50);//навигация
			AddCharacterExpToSkill(pchar, "Defence", 150);//защита
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
			Group_DeleteGroup("Fraht_Attack");
		break;
	
		case "EscortBonus_complete_fail":
			if (GetCharacterIndex("EscortCaptain_1") == -1) RemoveCharacterCompanion(pchar, characterFromID("EscortCaptain_2"));
			else RemoveCharacterCompanion(pchar, characterFromID("EscortCaptain_1"));//удалим компаньона
			pchar.quest.Escort_fail.over = "yes";//снять прерывание
			amount = sti(pchar.questTemp.WPU.Escort.GoodsQty) - GetSquadronGoods(pchar, sti(pchar.questTemp.WPU.Escort.Goods));
			pchar.questTemp.WPU.Escort.GoodsQty = GetSquadronGoods(pchar, sti(pchar.questTemp.WPU.Escort.Goods));
			if (pchar.questTemp.WPU.Escort == "begin")
			{
				pchar.quest.EscortTime_Over.over = "yes";//снять таймер
				pchar.questTemp.WPU.Escort.MinusMoney = makeint(sti(pchar.questTemp.WPU.Escort.BonusMoney) - sti(pchar.questTemp.WPU.Fraht.GoodsAverigePrice)*sti(amount));
				if (sti(pchar.questTemp.WPU.Escort.MinusMoney) < 0) amount = 101;
				if (amount > 0 && amount <= 100)
				{
					pchar.questTemp.WPU.Escort.BonusMoney = sti(pchar.questTemp.WPU.Escort.MinusMoney);
					dialog.text = "Hihetetlen! És mi szükségünk volt rád? Hogy engedhetted ezt megtörténni?! Remélem, megérti, hogy a kíséretért járó jutalom most már szóba sem jöhet... Nem csak ez, de a rakomány is kevés - " + FindRussianQtyString(sti(amount)) + "\nÁltalában csak az elfogadható állapotban leszállított áruk fuvardíját fizetem ki, csökkentve a hiányzó tételek értékével. Szerezd meg a " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.BonusMoney))+ " és mehetsz, ahová akarsz.";
					link.l1 = "Nos, ez legalább valami.";
					link.l1.go = "EscortBonus_complete_fail_1";
					break;
				}
				if (amount > 100)
				{
					dialog.text = "Hihetetlen! És mi szükségünk volt rád? Hogy engedhetted ezt megtörténni?! Remélem, megérti, hogy a kíséretért járó jutalom most már szóba sem jöhet... Nem csak ez, de a rakományból is óriási hiány van.\nNincs idôm arra, hogy megvárjam, amíg megszerezzétek a hiányzó árut. Így hát teljes mértékben kompenzálnia kell a költségeket - " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost))+ ". Ami a rakományt illeti, azt megtarthatod.";
					if (sti(pchar.money) >= sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost))
					{
						link.l1 = "Rendben, ne gôzzön túlságosan. Itt a pénzed.";
						link.l1.go = "EscortBonus_complete_fail_2";
					}
					link.l2 = "Mindannyian megôrültetek? Ez szó szerint zsarolás! Nem adok semmit!";
					link.l2.go = "EscortBonus_complete_fail_3";
					break;
				}
				dialog.text = "Hihetetlen! És mi szükségünk volt rád? Hogy engedhetted ezt megtörténni?! Remélem, megérti, hogy a kíséretért járó bármilyen jutalom most már szóba sem jöhet.\nÁltalában csak az önök által elvitt áruk fuvardíját fizetem ki. Szerezd meg a " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.BonusMoney))+ " és mehetsz, ahová csak akarsz.";
				link.l1 = "Nos, ez legalább valami.";
				link.l1.go = "EscortBonus_complete_fail_1";
				break;
			}
			if (pchar.questTemp.WPU.Escort == "late")
			{
				pchar.quest.EscortTime_FullOver.over = "yes";//снять второй таймер
				iTime = makeint(GetQuestPastDayParam("questTemp.Escort.Late"))+1;
				pchar.questTemp.WPU.Escort.DayLate = iTime;
				pchar.questTemp.WPU.Escort.PercentLate = iTime/0.1;
				pchar.questTemp.WPU.Escort.BonusMoney = makeint(sti(pchar.questTemp.WPU.Escort.BonusMoney) - sti(pchar.questTemp.WPU.Escort.BonusMoney)*sti(pchar.questTemp.WPU.Escort.PercentLate)/100);//снижаем оплату согласно числа дней опоздания
				if (amount > 0)
				{
					dialog.text = "Hihetetlen! És mi szükségünk volt rád? Hogy engedhetted ezt megtörténni?! Remélem, megérti, hogy a kíséretért járó jutalom mostantól szóba sem jöhet... Elvesztettetek egy hajót, késve érkeztetek " + FindRussianDaysString(iTime)+ " , és ráadásul a rakomány is hiányzik - " + FindRussianQtyString(sti(amount)) + "\nNincs idôm megvárni, hogy megszerezzétek a hiányzó árut. Így a költséget teljes egészében önnek kell megtérítenie " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost))+ ". Ami a rakományt illeti, azt megtarthatja.";
					if (sti(pchar.money) >= sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost))
					{
						link.l1 = "Rendben, ne gôzzön túlságosan. Itt a pénzed.";
						link.l1.go = "EscortBonus_complete_fail_2";
					}
					link.l2 = "Mindannyian megôrültetek? Ez szó szerint zsarolás! Nem adok semmit!";
					link.l2.go = "EscortBonus_complete_fail_3";
					break;
				}
				dialog.text = "Hihetetlen! És mi szükségünk volt rád? Hogy engedhetted ezt megtörténni?! Remélem, megérti, hogy a kíséretért járó jutalom mostantól szóba sem jöhet... Különben is, késve érkeztek " + FindRussianDaysString(iTime)+ " .\nSzóval csökkentenem kellett a fuvarért járó fizetséget. A megállapodás szerint a bírság az eredeti összeg 10 százaléka a késés minden egyes napjára. Most pedig fogd a " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.BonusMoney)) + ", és mehetsz.";
				link.l1 = "Nos, ez legalább valami.";
				link.l1.go = "EscortBonus_complete_fail_1";
				break;
			}
		break;
	
		case "EscortBonus_complete_fail_1"://потеряли корабль, время и груз в норме или частично
			AddQuestRecord("Escort", "12");
			AddQuestUserData("Escort", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.BonusMoney)));
			CloseQuestHeader("Escort");
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.WPU.Escort.BonusMoney));
			RemoveCharacterGoods(pchar, sti(pchar.questTemp.WPU.Escort.Goods), sti(pchar.questTemp.WPU.Escort.GoodsQty));
			pchar.questTemp.WPU.Escort.count = sti(pchar.questTemp.WPU.Escort.count)-1;//рейс не засчитываем
			DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
			DeleteAttribute(pchar, "questTemp.WPU.Current.TargetIslandID");
			DeleteAttribute(pchar, "questTemp.WPU.Escort.Bonus");
			pchar.questTemp.WPU.Escort = "complete";
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
			AddCharacterExpToSkill(pchar, "Sailing", 50);//навигация
			AddCharacterExpToSkill(pchar, "Defence", 150);//защита
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
			AddCharacterExpToSkill(pchar, "Commerce", 100);//торговля
			Group_DeleteGroup("Fraht_Attack");
			DialogExit();
		break;
	
		case "EscortBonus_complete_fail_2"://потеряли корабль и груз, время норма или нет, мир
			AddQuestRecord("Escort", "13");
			AddQuestUserData("Escort", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost)));
			CloseQuestHeader("Escort");
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost));
			pchar.questTemp.WPU.Escort.count = sti(pchar.questTemp.WPU.Escort.count)-1;//рейс не засчитываем
			pchar.questTemp.WPU.Escort.count = sti(pchar.questTemp.WPU.Fraht.count)-1;//рейс не засчитываем
			DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
			DeleteAttribute(pchar, "questTemp.WPU.Current.TargetIslandID");
			DeleteAttribute(pchar, "questTemp.WPU.Escort.Bonus");
			pchar.questTemp.WPU.Escort = "complete";
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
			AddCharacterExpToSkill(pchar, "Sailing", 50);//навигация
			AddCharacterExpToSkill(pchar, "Defence", 150);//защита
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
			AddCharacterExpToSkill(pchar, "Commerce", 50);//торговля
			Group_DeleteGroup("Fraht_Attack");
			DialogExit();
		break;
	
		case "EscortBonus_complete_fail_3"://потеряли корабль и груз, время норма или нет, война
			dialog.text = "Ó, értem... Nos, ebben az esetben soha többé ne mutatkozzon a " + NationNameGenitive(sti(pchar.questTemp.WPU.Escort.Nation)) + "egyetlen kikötôi hatóságnál sem ! Tûnj el!";
			link.l1 = "Biztos nem maradtam le semmirôl...";
			link.l1.go = "exit";
			AddQuestRecord("Escort", "14");
			AddQuestUserData("Escort", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigeCost)));
			CloseQuestHeader("Escort");
			pchar.questTemp.WPU.Escort.count = 0;//счетчик в ноль
			pchar.questTemp.WPU.Escort.count = 0;//счетчик в ноль
			DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
			DeleteAttribute(pchar, "questTemp.WPU.Current.TargetIslandID");
			DeleteAttribute(pchar, "questTemp.WPU.Escort.Bonus");
			pchar.questTemp.WPU.Escort = "complete";
			pchar.questTemp.WPU.Fraht = "fail";
			ChangeCharacterComplexReputation(pchar,"nobility", -10);
			ChangeCharacterHunterScore(pchar, NationShortName(sti(pchar.questTemp.WPU.Escort.Nation)) + "hunter", 30);
			pchar.questTemp.WPU.Fraht.Nation = pchar.questTemp.WPU.Escort.Nation;
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
			Group_DeleteGroup("Fraht_Attack");
		break;
	
		case "Escort_fail"://потеряли 2 корабля
			dialog.text = "Ez nagyon, nagyon rossz! Mire béreltük fel magát, meg tudja mondani? Hogy ôrizzék a hajókat? Vagy csak lógni?";
			link.l1 = "Értem én. Az ellenség egyszerûen túl erôs volt, és... de minek vitatkozni - ami történt, az már megtörtént. De a rakomány - a rakomány még mindig sértetlen! Szóval rendezzük el a dolgot.";
			link.l1.go = "Escort_fail_complete";
		break;
	
		case "Escort_fail_complete":
			iFrahtGoods = makeint(pchar.questTemp.WPU.Escort.Goods);
			amount = sti(pchar.questTemp.WPU.Escort.GoodsQty) - GetSquadronGoods(pchar, sti(pchar.questTemp.WPU.Escort.Goods));
			if (amount > 0)
			{
				dialog.text = "Lássuk csak. Egy " + GetGoodsNameAlt(iFrahtGoods)+ " mennyiségû " + FindRussianQtyString(pchar.questTemp.WPU.Escort.GoodsQty) + "rakományt kellett volna szállítania. De látom, hogy még' nem szállítottad le a teljes szállítmányt - hiányzik " + FindRussianQtyString(sti(amount)) + " .";
				link.l1 = "Ezer cápa! Biztos azok az átkozott patkányok! De ne aggódj, " + GetAddress_FormToNPC(NPChar) + ", megveszem a hiányzó mennyiséget, és leadom az egész tételt.";
				link.l1.go = "Fraht_complete_3";
				break;
			}
			dialog.text = "Lássuk csak. Egy rakományt kellett volna szállítania " + GetGoodsNameAlt(iFrahtGoods)+ " mennyiségben " + FindRussianQtyString(pchar.questTemp.WPU.Escort.GoodsQty) + ". Így van?";
			link.l1 = "Teljesen helyes, " + GetAddress_FormToNPC(NPChar) + ".";
			link.l1.go = "Escort_fail_complete_1";
		break;
	
		case "Escort_fail_complete_1":
			DeleteAttribute(pchar, "questTemp.WPU.Escort.Bonus");
			pchar.questTemp.WPU.Escort.Money = makeint(sti(pchar.questTemp.WPU.Escort.BonusMoney)/2);
			if (pchar.questTemp.WPU.Escort == "late")//опоздали
			{
				iTime = makeint(GetQuestPastDayParam("questTemp.Escort.Late"))+1;
				pchar.questTemp.WPU.Escort.DayLate = iTime;
				pchar.questTemp.WPU.Escort.PercentLate = iTime/0.1;
				pchar.questTemp.WPU.Escort.Money = makeint(sti(pchar.questTemp.WPU.Escort.Money) - sti(pchar.questTemp.WPU.Escort.Money)*sti(pchar.questTemp.WPU.Escort.PercentLate)/100);//снижаем оплату согласно числа дней опоздания
				dialog.text = "Hmm... Nemcsak a rád bízott hajókat vesztetted el, hanem elkéstél a " + FindRussianDaysString(iTime)+ ". Így kénytelen voltam csökkenteni a fuvardíjat. Mivel nem tudtad megmenteni a hajókat, megfeleztem a fuvardíjat, és ez a legtöbb, amit felajánlhatok neked.\nA szerzôdés szerint ráadásul a bírság az eredeti összeg 10 százaléka minden egyes késedelmes nap után. Most pedig vegye a " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money)) + ", és induljon.";
				link.l1 = "Nos, ez legalább valami.";
				link.l1.go = "Escort_fail_complete_2";
				break;
			}
			dialog.text = "Nos, bár rendkívül bosszant, hogy nem tudtad megvédeni a rád bízott hajókat, de legalább az árut leszállítottad. Mivel nem tudtad megmenteni a hajókat, megfeleztem a fuvardíjat, és ez a legtöbb, amit felajánlhatok neked. Most pedig vegye fel a fizetségét - " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money)) + " és mehet, ahová csak akar.";
			link.l1 = "Nos, ez legalább valami.";
			link.l1.go = "Escort_fail_complete_2";
		break;
	
		case "Escort_fail_complete_2":
			if (pchar.questTemp.WPU.Escort == "begin")
			{
				pchar.quest.EscortTime_Over.over = "yes";
				AddQuestRecord("Escort", "17");
				AddQuestUserData("Escort", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money)));
			}
			else
			{
				pchar.quest.EscortTime_FullOver.over = "yes";//снять второй таймер
				AddQuestRecord("Escort", "18");
				AddQuestUserData("Escort", "sDay", FindRussianDaysString(pchar.questTemp.WPU.Escort.DayLate));
				AddQuestUserData("Escort", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money)));
			}
			pchar.questTemp.WPU.Fraht.count = sti(pchar.questTemp.WPU.Fraht.count)-1;//фейловый рейс не засчитываем
			RemoveCharacterGoods(pchar, sti(pchar.questTemp.WPU.Escort.Goods), sti(pchar.questTemp.WPU.Escort.GoodsQty));
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.WPU.Escort.Money));
			CloseQuestHeader("Escort");
			DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
			DeleteAttribute(pchar, "questTemp.WPU.Current.TargetIslandID");
			pchar.questTemp.WPU.Escort = "complete";
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
			AddCharacterExpToSkill(pchar, "Sailing", 50);//навигация
			AddCharacterExpToSkill(pchar, "Commerce", 50);//торговля
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
			Group_DeleteGroup("Fraht_Attack");
			DialogExit();
		break;
	
//-------------------------------------задания 2 уровня для курьера---------------------------------------------
		case "Postcureer_LevelUp":
			pchar.questTemp.WPU.Postcureer.City = findCurrentCity2(npchar);//целевой город
			pchar.questTemp.WPU.Postcureer.StartCity = npchar.city;//город квестодателя
			idaysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(pchar.questTemp.WPU.Postcureer.StartCity), GetArealByCityName(pchar.questTemp.WPU.Postcureer.City));
			pchar.questTemp.WPU.Postcureer.DaysQty = makeint(sti(idaysQty)*(frand(0.3)+0.6));//дни
			pchar.questTemp.WPU.Postcureer.Money = (sti(idaysQty)*3000)*sti(idaysQty)/sti(pchar.questTemp.WPU.Postcureer.DaysQty)*(1+frand(0.2));//оплата
			pchar.questTemp.WPU.Postcureer.Chance = rand(4);//форс-мажор
			pchar.questTemp.WPU.Postcureer.StartNation = npchar.nation;//нация отправителя
			pchar.questTemp.WPU.Postcureer.TargetPortmanID = pchar.questTemp.WPU.Postcureer.City +"_portman";//ИД портмана
			sld = characterFromId(pchar.questTemp.WPU.Postcureer.TargetPortmanID);
			pchar.questTemp.WPU.Postcureer.Nation = sld.nation;//нация получателя
			pchar.questTemp.WPU.Current.TargetIslandID = GetCharacterCurrentIslandId(sld);//ИД целевого ареала
			pchar.questTemp.WPU.Postcureer.EnemyNation = GetEnemyNationToMainCharacter();//вражеская нация
			i = 0;
			while (sti(pchar.questTemp.WPU.Postcureer.EnemyNation) == PIRATE)
			{
				pchar.questTemp.WPU.Postcureer.EnemyNation = GetEnemyNationToMainCharacter();
				i++;
				if(i > 5) pchar.questTemp.WPU.Postcureer.EnemyNation = FindEnemyNation2NationWithoutPirates(sti(pchar.BaseNation));
			}

			switch (rand(3))
			{
				case 0:
					dialog.text = "Sürgôs hivatalos küldeményt kell eljuttatnia "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.City+"Gen")+" város kormányzójának, legkésôbb "+FindRussianDaysString(sti(pchar.questTemp.WPU.Postcureer.DaysQty))+". Légy nagyon óvatos - az ellenségeink is vadászhatnak erre a küldeményre. Fizetés a küldeményért - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money))+".";
					link.l1 = "Egyetértek!";
					link.l1.go = "Postcureer_LevelUp_Go";
					link.l2 = "Nem, azt hiszem, kihagyom.";
					link.l2.go = "Postcureer_LevelDown";
					pchar.questTemp.WPU.Postcureer.TargetPortmanID = pchar.questTemp.WPU.Postcureer.City +"_Mayor";//ИД губера
					if (pchar.questTemp.WPU.Postcureer.TargetPortmanID == "Villemstad_Mayor") pchar.questTemp.WPU.Postcureer.TargetPortmanID = "hol_guber"; // фикс Матиаса Бека #717
					pchar.questTemp.WPU.Current.Add = "a dispatch for the governor";
					pchar.questTemp.WPU.Current.Item = "letter_2";//предмет
					pchar.questTemp.WPU.Current.Itemdescr = "itmdescr_letter_2_PortmanLevelUp1";//описание
				break;
			
				case 1:
					dialog.text = "Ezeket a papírokat legkésôbb a "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.City+"Gen")+" üzlet tulajdonosának kell eljuttatnia a "+FindRussianDaysString(sti(pchar.questTemp.WPU.Postcureer.DaysQty))+". Ez a legfrissebb összefoglaló a szigetország üzleteinek árairól - értékes kereskedelmi dokumentum. Vigyázni kell - a versenytársak vadászatot rendezhetnek. Fizetés a szállításért - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money))+".";
					link.l1 = "Egyetértek!";
					link.l1.go = "Postcureer_LevelUp_Go";
					link.l2 = "Nem, azt hiszem, kihagyom.";
					link.l2.go = "Postcureer_LevelDown";
					pchar.questTemp.WPU.Postcureer.TargetPortmanID = pchar.questTemp.WPU.Postcureer.City +"_trader";//ИД торговца
//					pchar.questTemp.WPU.Current.Add = "сводку цен для хозяина магазина";
					pchar.questTemp.WPU.Current.Add = "a price list for the store owner";     // LDH 23Jan17 translated
					pchar.questTemp.WPU.Current.Item = "letter_2";//предмет
					pchar.questTemp.WPU.Current.Itemdescr = "itmdescr_letter_2_PortmanLevelUp2";//описание
				break;
			
				case 2:
					dialog.text = "Ezt az iratcsomót legkésôbb "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.City+"Gen")+" a "+FindRussianDaysString(sti(pchar.questTemp.WPU.Postcureer.DaysQty))+"városában kell eljuttatnia az uzsorásnak. Ez nagyon fontos információ a devizaárfolyamokról és a részvényárfolyamokról. Legyen nagyon óvatos - néhány kétes alak máris érdekelt abban, hogy megszerezze ezt a csomagot. Fizetés a szállításért - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money))+".";
					link.l1 = "Egyetértek!";
					link.l1.go = "Postcureer_LevelUp_Go";
					link.l2 = "Nem, azt hiszem, kihagyom.";
					link.l2.go = "Postcureer_LevelDown";
					pchar.questTemp.WPU.Postcureer.TargetPortmanID = pchar.questTemp.WPU.Postcureer.City +"_usurer";//ИД ростовщика
					pchar.questTemp.WPU.Current.Add = "a packet of information for the moneylender";   // LDH 23Jan17 translated
					pchar.questTemp.WPU.Current.Item = "letter_2";//предмет
					pchar.questTemp.WPU.Current.Itemdescr = "itmdescr_letter_2_PortmanLevelUp3";//описание
				break;
			
				case 3:
					dialog.text = "Ezt a csomagot legkésôbb a "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.City+"Gen")+" dokkmesterhez kell eljuttatnia a "+FindRussianDaysString(sti(pchar.questTemp.WPU.Postcureer.DaysQty))+"városba. Az új "+RandPhraseSimple(LinkRandPhrase("brigg","korvett","fregatt"), LinkRandPhrase("flotta","pinnace","gálya"))+"tervrajzait tartalmazza, egyedi technológiai terveket alkalmazva. Remélem, megérti, hogy vannak más... érdeklôdôk is, ezért diszkréten kell eljárnia. Fizetés a szállításért - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money))+".";
					link.l1 = "Egyetértek!";
					link.l1.go = "Postcureer_LevelUp_Go";
					link.l2 = "Nem, azt hiszem, kihagyom.";
					link.l2.go = "Postcureer_LevelDown";
					pchar.questTemp.WPU.Postcureer.TargetPortmanID = pchar.questTemp.WPU.Postcureer.City +"_shipyarder";//ИД верфиста
					pchar.questTemp.WPU.Current.Add = "the draft of a new ship for the owner of the shipyard";
					pchar.questTemp.WPU.Current.Item = "ShipyardsMap";//предмет
					pchar.questTemp.WPU.Current.Itemdescr = "itmdescr_ShipyardsMap_PortmanLevelUp4";//описание
				break;
			}
		break;
	
		case "Postcureer_LevelUp_Go":
			dialog.text = "Aztán fogd a papírokat és indulj el. Sok szerencsét... és a Mindenható vigyázzon önre.";
			link.l1 = "Köszönjük!";
			link.l1.go = "Forsmajor_choose";
			pchar.questTemp.WPU.Postcureer = "begin";
			pchar.questTemp.WPU.Postcureer.LevelUp = "true";
			pchar.questTemp.WPU.Postcureer.count = sti(pchar.questTemp.WPU.Postcureer.count) + 1;
			//запустить регату при счетчике > 4
			if (!CheckAttribute(pchar, "questTemp.RegataGo") && sti(pchar.questTemp.WPU.Postcureer.count) > 4)
			{
				pchar.questTemp.RegataGo = "true";
				pchar.questTemp.Regata.CureerCity = FindFriendCityToMC(true);//город, в котором вестовой подойдет
				if (pchar.questTemp.Regata.CureerCity == "PortRoyal") pchar.questTemp.Regata.CureerCity = "SentJons";
				pchar.quest.Regata_Cureer.win_condition.l1 = "location";
				pchar.quest.Regata_Cureer.win_condition.l1.location = pchar.questTemp.Regata.CureerCity+"_town";
				pchar.quest.Regata_Cureer.function = "PrepareToRegata";
				log_testinfo(pchar.questTemp.Regata.CureerCity);
			}
			GiveItem2Character(pchar, pchar.questTemp.WPU.Current.Item);
			ChangeItemDescribe(pchar.questTemp.WPU.Current.Item, pchar.questTemp.WPU.Current.Itemdescr);
			ReOpenQuestHeader("Postcureer");
			AddQuestRecord("Postcureer", "6");
			AddQuestUserData("Postcureer", "sDay", FindRussianDaysString(sti(pchar.questTemp.WPU.Postcureer.DaysQty)));
			AddQuestUserData("Postcureer", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money)));
			AddQuestUserData("Postcureer", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen"));
			AddQuestUserData("Postcureer", "sTargetColony",XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.City)); // belamour gen
			AddQuestUserData("Postcureer", "sText", pchar.questTemp.WPU.Current.Add);
			AddQuestUserData("Postcureer", "sSex1", GetSexPhrase("",""));
			SetFunctionTimerCondition("PostcureerTime_Over", 0, 0, sti(pchar.questTemp.WPU.Postcureer.DaysQty), false);
		break;
	
		case "Postcureer_LevelDown":
			dialog.text = "Kár, valóban... Igazából az ilyen jellegû ajánlatokat általában nem dobják fel. De ez amúgy is a te döntésed.";
			link.l1 = "Igen, ez az én döntésem, " + GetAddress_FormToNPC(NPChar) + ".";
			link.l1.go = "exit";
			pchar.questTemp.WPU.Postcureer.count = sti(pchar.questTemp.WPU.Postcureer.count) - 1;//за отказ от спецзадания счетчик скрутим
		break;
	
		case "Forsmajor_choose":
			switch (sti(pchar.questTemp.WPU.Postcureer.Chance))
			{
				case 0://охотники в городе прибытия + ДУ
					pchar.quest.Postcureer_Hunter.win_condition.l1 = "Hely";
					pchar.quest.Postcureer_Hunter.win_condition.l1.location = pchar.questTemp.WPU.Postcureer.City + "_town";
					pchar.quest.Postcureer_Hunter.function = "PostcureerGopHuntersOnLand";
					TraderHunterOnMap(false);
				break;
		
				case 1://создание скоростного перехватчика на глобалке
					EnemyNationHunterOnMap(true);
				break;
		
				case 2://запуск ДУ на глобалке и в порту прибытия
					TraderHunterOnMap(false);
					FrahtHunterOnSea();
				break;
		
				case 3://наёмники в стартовом городе
					pchar.quest.Postcureer_Hunter.win_condition.l1 = "Hely";
					pchar.quest.Postcureer_Hunter.win_condition.l1.location = pchar.questTemp.WPU.Postcureer.StartCity + "_town";
					pchar.quest.Postcureer_Hunter.function = "PostcureerProfHuntersOnLand";
				break;
		
				case 4://агент
					pchar.quest.Postcureer_Hunter.win_condition.l1 = "Hely";
					pchar.quest.Postcureer_Hunter.win_condition.l1.location = pchar.questTemp.WPU.Postcureer.StartCity + "_town";
					pchar.quest.Postcureer_Hunter.function = "PostcureerAgent";
				break;
			}
			DialogExit();
		break;

		case "Postcureer_complete_fail":
			dialog.text = "A francba! Szóval mégiscsak lenyomoztak téged. Kár, hogy nem vagy katona, kapitány - akkor talán másképp alakultak volna a dolgok... Hogy néztek ki?";
			link.l1 = "Két erôs, zömök, fekete ruhás férfi, félmaszkkal az arcukon, botokkal és kétcsövû puskákkal felfegyverkezve...";
			link.l1.go = "Postcureer_complete_fail_1";
		break;

		case "Postcureer_complete_fail_1":
			dialog.text = "Azonnal értesítem a kormányzót, hogy kezdje el keresni ôket. Rendben, viszlát, " + GetAddress_Form(NPChar) + ". Kár, hogy nem vagy katona...";
			link.l1 = "Nagyon sajnálom, " + GetAddress_FormToNPC(NPChar) + ", ami történt. Nos, viszlát.";
			link.l1.go = "exit";
			if (pchar.questTemp.WPU.Postcureer == "begin") pchar.quest.PostcureerTime_Over.over = "yes";//снять таймер
			if (pchar.questTemp.WPU.Postcureer == "late") pchar.quest.PostcureerTime_FullOver.over = "yes";//снять второй таймер
			CloseQuestHeader("Postcureer");
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			pchar.questTemp.WPU.Postcureer.count = sti(pchar.questTemp.WPU.Postcureer.count)-3;//скрутим счетчик
			DeleteAttribute(pchar, "questTemp.WPU.Postcureer.TargetPortmanID");
			DeleteAttribute(pchar, "questTemp.WPU.Current");
			DeleteAttribute(pchar, "questTemp.WPU.Postcureer.LevelUp");
			DeleteAttribute(pchar, "questTemp.WPU.Postcureer.fail");
			pchar.questTemp.WPU.Postcureer = "complete";
		break;
	
//----------------------------------------задания 2 уровня фрахт------------------------------------------

	case "Fraht_LevelUp":
		rColony = GetColonyByIndex(FindColony(npchar.city));
		pchar.questTemp.WPU.Fraht.StartCity = npchar.city;//город квестодателя
		pchar.questTemp.WPU.Fraht.Nation = npchar.nation;//нация получателя
		switch (rand(4))//для тестов
		{
			case 0:
				pchar.questTemp.WPU.Fraht.Goods = GOOD_CHOCOLATE + hrand(makeint(GOOD_TOBACCO - GOOD_CHOCOLATE));
				iGoods = pchar.questTemp.WPU.Fraht.Goods;
				//iGoodsQty = 3000 + sti(pchar.rank)*30*(hrand(9)+1);
				iGoodsQty = 1000+sti(pchar.rank)*10*(hrand(9)+1); // min 1100 max 5000
				pchar.questTemp.WPU.Fraht.GoodsQty = iGoodsQty;
				pchar.questTemp.WPU.Fraht.GoodsAverigePrice = sti(Goods[iGoods].Cost)*2;//двойная цена единицы товара
				pchar.questTemp.WPU.Fraht.Money = sti(Goods[iGoods].Cost)*sti(pchar.questTemp.WPU.Fraht.GoodsQty)*2;//двойная стоимость товара
				pchar.questTemp.WPU.Current.Add = "double";
				// 08Mar17 "month" was "moths"
				dialog.text = "A közelmúltban drámaian megnôtt a kereslet egy bizonyos áru iránt a kolóniánkon. A helyi boltokban már nincs raktáron. Ezért azt szeretném, ha a " + GetGoodsNameAlt(iGoods)+ " mennyiségben " + FindRussianQtyString(iGoodsQty) + ", és hajlandó vagyok a dupláját - " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigePrice)) + " darabonként - fizetni. Ez az összeg " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money)) + "lesz. Ja, és próbáljátok tartani az egy hónapos határidôt - nem fogok tudni tovább várni az árura.";
				link.l1 = "Rendben, elfogadom a küldetést.";
				link.l1.go = "Fraht_LevelUp_Go";
				link.l2 = "Sajnálom, hogy csalódást kell okoznom, de jelenleg nem tudom teljesíteni.";
				link.l2.go = "Fraht_LevelDown";
				SetNull2StoreGood(rColony, sti(pchar.questTemp.WPU.Fraht.Goods));
			break;
		
			case 1:
				pchar.questTemp.WPU.Fraht.Goods = GOOD_EBONY + hrand(makeint(GOOD_CINNAMON - GOOD_EBONY));
				iGoods = pchar.questTemp.WPU.Fraht.Goods;
				//iGoodsQty = 1500 + sti(pchar.rank)*20*(hrand(9)+1);
				iGoodsQty = 600+sti(pchar.rank)*5*(hrand(6)+1); // min 630 max 2000
				pchar.questTemp.WPU.Fraht.GoodsQty = iGoodsQty;
				pchar.questTemp.WPU.Fraht.GoodsAverigePrice = sti(Goods[iGoods].Cost)*2;//двойная цена единицы товара
				pchar.questTemp.WPU.Fraht.Money = sti(Goods[iGoods].Cost)*sti(pchar.questTemp.WPU.Fraht.GoodsQty)*2;//двойная стоимость товара
				pchar.questTemp.WPU.Current.Add = "double";
				// 08Mar17 "month" was "moths"
				dialog.text = "A közelmúltban drámaian megnôtt a kereslet egy bizonyos áru iránt a kolóniánkon. A helyi boltokban már nincs raktáron. Ezért azt szeretném, ha a " + GetGoodsNameAlt(iGoods)+ " mennyiségben " + FindRussianQtyString(iGoodsQty) + ", és hajlandó vagyok a dupláját - " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigePrice)) + " darabonként - fizetni. Ez az összeg " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money)) + "lesz. Ja, és próbáljátok tartani az egy hónapos határidôt - nem fogok tudni tovább várni az árura.";
				link.l1 = "Rendben, elfogadom a küldetést.";
				link.l1.go = "Fraht_LevelUp_Go";
				link.l2 = "Sajnálom, hogy csalódást kell okoznom, de jelenleg nem tudom teljesíteni.";
				link.l2.go = "Fraht_LevelDown";
				SetNull2StoreGood(rColony, sti(pchar.questTemp.WPU.Fraht.Goods));
			break;
		
			case 2:
				//pchar.questTemp.WPU.Fraht.Goods = GOOD_BOMBS + hrand(makeint(GOOD_POWDER - GOOD_BOMBS));
				pchar.questTemp.WPU.Fraht.Goods = GOOD_BOMBS;
				iGoods = pchar.questTemp.WPU.Fraht.Goods;
				//iGoodsQty = 15000 + sti(pchar.rank)*300*(hrand(9)+1);
				iGoodsQty = 5000+sti(pchar.rank)*10*(hrand(9)+1); // min 5100 max 9000
				pchar.questTemp.WPU.Fraht.GoodsQty = iGoodsQty;
				pchar.questTemp.WPU.Fraht.GoodsAverigePrice = sti(Goods[iGoods].Cost)*3;//тройная цена единицы товара
				pchar.questTemp.WPU.Fraht.Money = makeint((sti(Goods[iGoods].Cost)*sti(pchar.questTemp.WPU.Fraht.GoodsQty)*3)/20);//тройная стоимость товара
				pchar.questTemp.WPU.Current.Add = "triple";
				// 08Mar17 "month" was "moths"
				dialog.text = "Gyarmatunk arzenáljából drasztikusan hiányzik " + GetGoodsNameAlt(iGoods)+ ". A helyi boltokban már nincs raktáron. Ezért azt szeretném, ha rendelkezésemre bocsátanátok " + GetGoodsNameAlt(iGoods)+ " mennyiségben " + FindRussianQtyString(iGoodsQty) + ", és hajlandó vagyok a háromszorosát - " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigePrice)) + " darabonként - kifizetni. Ez az összeg " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money)) + "lesz. Ja, és próbáljátok tartani az egy hónapos határidôt - nem fogok tudni tovább várni az árura.";
				link.l1 = "Rendben, elfogadom a küldetést.";
				link.l1.go = "Fraht_LevelUp_Go";
				link.l2 = "Sajnálom, hogy csalódást kell okoznom, de jelenleg nem tudom teljesíteni.";
				link.l2.go = "Fraht_LevelDown";
				SetNull2StoreGood(rColony, sti(pchar.questTemp.WPU.Fraht.Goods));
			break;
		
			case 3:
				pchar.questTemp.WPU.Fraht.Goods = GOOD_MEDICAMENT;
				iGoods = pchar.questTemp.WPU.Fraht.Goods;
				iGoodsQty = 7000 + sti(pchar.rank)*300*(hrand(9)+1);
				pchar.questTemp.WPU.Fraht.GoodsQty = iGoodsQty;
				pchar.questTemp.WPU.Fraht.GoodsAverigePrice = sti(Goods[iGoods].Cost)*3;//тройная цена единицы товара
				pchar.questTemp.WPU.Fraht.Money = makeint((sti(Goods[iGoods].Cost)*sti(pchar.questTemp.WPU.Fraht.GoodsQty)*3)/30);//тройная стоимость товара
				pchar.questTemp.WPU.Current.Add = "triple";
				// 08Mar17 "month" was "moths"
				dialog.text = "A kolóniánkban nemrégiben kitört láz után hiányoznak az orvosi felszerelések - és a boltokban már semmi sincs. A kormányzó félti a városlakók biztonságát. Ezért azt szeretném, ha " + GetGoodsNameAlt(iGoods)+ " mennyiségben " + FindRussianQtyString(iGoodsQty) + ", és hajlandó vagyok a háromszorosát fizetni - " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigePrice)) + " csomagonként. Ez az összeg " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money)) + "lesz. Ja, és próbáljátok tartani az egy hónapos határidôt - nem fogok tudni tovább várni az árura.";
				link.l1 = "Rendben, elfogadom a küldetést.";
				link.l1.go = "Fraht_LevelUp_Go";
				link.l2 = "Sajnálom, hogy csalódást kell okoznom, de jelenleg nem tudom teljesíteni.";
				link.l2.go = "Fraht_LevelDown";
				SetNull2StoreGood(rColony, sti(pchar.questTemp.WPU.Fraht.Goods));
			break;
		
			case 4:
				pchar.questTemp.WPU.Fraht.Goods = GOOD_FOOD;
				iGoods = pchar.questTemp.WPU.Fraht.Goods;
				iGoodsQty = 15000 + sti(pchar.rank)*300*(hrand(9)+1);
				pchar.questTemp.WPU.Fraht.GoodsQty = iGoodsQty;
				pchar.questTemp.WPU.Fraht.GoodsAverigePrice = sti(Goods[iGoods].Cost)*2;//двойная цена единицы товара
				pchar.questTemp.WPU.Fraht.Money = makeint((sti(Goods[iGoods].Cost)*sti(pchar.questTemp.WPU.Fraht.GoodsQty)*2)/10);//двойная стоимость товара
				pchar.questTemp.WPU.Current.Add = "double";
				// 08Mar17 "month" was "moths"
				dialog.text = "A rossz termés után kolóniánknak állandóan importált élelmiszerre van szüksége. Jelenleg a készleteink szinte teljesen kiürültek, és a boltok polcairól már jó ideje letöröltek mindent. Szeretném megkérni, hogy szállítson nekem " + GetGoodsNameAlt(iGoods)+ " mennyiségben " + FindRussianQtyString(iGoodsQty) + ", és hajlandó vagyok a dupláját fizetni - " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.GoodsAverigePrice)) + " csomagonként. Ez az összeg " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money)) + "lesz. Ja, és próbáljátok tartani az egy hónapos határidôt - nem fogok tudni tovább várni az árura.";
				link.l1 = "Rendben, elfogadom a küldetést.";
				link.l1.go = "Fraht_LevelUp_Go";
				link.l2 = "Sajnálom, hogy csalódást kell okoznom, de jelenleg nem tudom teljesíteni.";
				link.l2.go = "Fraht_LevelDown";
				SetNull2StoreGood(rColony, sti(pchar.questTemp.WPU.Fraht.Goods));
			break;
		}
	break;
		
	case "Fraht_LevelDown":
		DialogExit();
		pchar.questTemp.WPU.Fraht.count = sti(pchar.questTemp.WPU.Fraht.count)-1;//скрутим счетчик
	break;
		
	case "Fraht_LevelUp_Go":
		dialog.text = "Kitûnô! Nagyon örülök, hogy beleegyezett. Remélem, hamarosan újra találkozunk.";
		link.l1 = "Természetesen, " + GetAddress_FormToNPC(NPChar) + ".";
		link.l1.go = "exit";
		pchar.questTemp.WPU.Fraht = "begin";
		pchar.questTemp.WPU.Fraht.LevelUp = "true";
		pchar.questTemp.WPU.Fraht.count = sti(pchar.questTemp.WPU.Fraht.count) + 1;
		pchar.questTemp.WPU.Fraht.TargetPortmanID = pchar.questTemp.WPU.Fraht.StartCity +"_portman";//ИД портмана
		iGoods = pchar.questTemp.WPU.Fraht.Goods;
		ReOpenQuestHeader("Fraht");
		AddQuestRecord("Fraht", "8");
		AddQuestUserData("Fraht", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money)));
		AddQuestUserData("Fraht", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Fraht.StartCity+"Gen"));
		AddQuestUserData("Fraht", "sGoods", GetGoodsNameAlt(iGoods));
		AddQuestUserData("Fraht", "sGoodQty", FindRussianQtyString(sti(pchar.questTemp.WPU.Fraht.GoodsQty)));
		AddQuestUserData("Fraht", "sText", pchar.questTemp.WPU.Current1.Add);
		SetFunctionTimerCondition("FrahtTimeLevelUp_Over", 0, 0, 30, false);
	break;
	
	case "Fraht_completeLevelUp":
	ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
	if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)//проверка на наличие корабля в порту
	{
		iGoods = makeint(pchar.questTemp.WPU.Fraht.Goods);
		amount = sti(pchar.questTemp.WPU.Fraht.GoodsQty) - GetSquadronGoods(pchar, sti(pchar.questTemp.WPU.Fraht.Goods));
		if (amount > 0)
		{
			dialog.text = "Most viccelsz velem? Nincs meg az általam rendelt árumennyiség!";
			link.l1 = "Sajnálom, az én hibám...";
			link.l1.go = "exit";
		}
		else
		{
			dialog.text = "Rendben, egy " + GetGoodsNameAlt(iGoods)+ " mennyiségû " + FindRussianQtyString(pchar.questTemp.WPU.Fraht.GoodsQty) + "rakományt kellett volna szállítanod. Kiváló, köszönöm szépen. Itt a fizetség - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Fraht.Money))+".";
			link.l1 = "Öröm veled üzletelni, " + GetAddress_FormToNPC(NPChar) + "!";
			link.l1.go = "Fraht_completeLevelUp_1";
		}
	}
	else
	{
		dialog.text = "Nem látom a hajóját a kikötôben. Feküdjön le, aztán jöjjön vissza hozzám, aztán majd beszélünk.";
		link.l1 = "Rendben, meg is teszem.";
		link.l1.go = "exit";
	}
	break;
	
	case "Fraht_completeLevelUp_1":
		pchar.quest.FrahtTimeLevelUp_Over.over = "yes";//снять таймер
		AddQuestRecord("Fraht", "2");
		CloseQuestHeader("Fraht");
		RemoveCharacterGoods(pchar, sti(pchar.questTemp.WPU.Fraht.Goods), sti(pchar.questTemp.WPU.Fraht.GoodsQty));
		AddMoneyToCharacter(pchar, sti(pchar.questTemp.WPU.Fraht.Money));
		DeleteAttribute(pchar, "questTemp.WPU.Fraht.TargetPortmanID");
		DeleteAttribute(pchar, "questTemp.WPU.Current1"); // лесник  Current1 вместо Current
		DeleteAttribute(pchar, "questTemp.WPU.Fraht.LevelUp");
		pchar.questTemp.WPU.Fraht = "complete";
		AddCharacterExpToSkill(pchar, "Sailing", 100);//навигация
		AddCharacterExpToSkill(pchar, "Commerce", 200);//торговля
		AddCharacterExpToSkill(pchar, "Leadership", 150);//авторитет
		AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
		ChangeCharacterComplexReputation(pchar,"nobility", 2);
		ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Fraht.Nation), 2);
		DialogExit();
	break;
	
//----------------------------------------задания 2 уровня эскорт ------------------------------------------

	case "Escort_LevelUp":
		pchar.questTemp.WPU.Escort.LevelUp = "true";//установим атрибут
		pchar.questTemp.WPU.Escort.StartCity = npchar.city;//город квестодателя
		pchar.questTemp.WPU.Escort.Nation = npchar.nation;//нация квестодателя
		pchar.questTemp.WPU.Escort.EnemyNation = GetEnemyNationToMainCharacter();//вражеская нация
		i = 0;
		while (sti(pchar.questTemp.WPU.Escort.EnemyNation) == PIRATE)
		{
			pchar.questTemp.WPU.Escort.EnemyNation = GetEnemyNationToMainCharacter();
			i++;
			if(i > 5) pchar.questTemp.WPU.Escort.EnemyNation = FindEnemyNation2NationWithoutPirates(sti(pchar.BaseNation));
		}
		switch (hrand(2))
		{
			case 0://приключения на необитаемых островах
				pchar.questTemp.WPU.Current.TargetIslandID = DesIsland();//выбор необитайки
				while (!isLocationFreeForQuests(pchar.questTemp.WPU.Current.TargetIslandID)) pchar.questTemp.WPU.Current.TargetIslandID = DesIsland();
				pchar.questTemp.WPU.Escort.ShipType = Escort_ShipType();//выбор корабля
				pchar.questTemp.WPU.Escort.ShipName = GenerateRandomNameToShip(sti(pchar.nation));//имя корабля
				pchar.questTemp.WPU.Escort.TargetPortmanID = pchar.questTemp.WPU.Escort.StartCity +"_portman";//ИД портмана
				pchar.questTemp.WPU.Escort.ShipBaseName = GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.questTemp.WPU.Escort.ShipType), "Name") + "Gen"));
				dialog.text = "Ez a szerencsétlenség tíz nappal ezelôtt történt... egy, a gyarmatunkra tartó kereskedelmi hajókból álló karavánt kalózok támadtak meg. A szélvihar a kalózokat visszavonulásra kényszerítette, de a kereskedelmi hajók szétszóródtak és szem elôl vesztették egymást. Végül az összes hajó különbözô kikötôkbe érkezett, kivéve egyet. \n"+pchar.questTemp.WPU.Escort.ShipBaseName+" '"+pchar.questTemp.WPU.Escort.ShipName+"' eltûnt, és sorsa ismeretlen maradt. Feltehetôen a "+XI_ConvertString(pchar.questTemp.WPU.Current.TargetIslandID)+"lakatlan sziget közelében található. Arra kérlek, hogy menjetek oda, derítsétek ki, mi történt az elveszett hajóval, és ha túlélte, hozzátok a kikötônkbe. A munka elvégzése után döntünk a díjazásotokról, de biztosíthatlak benneteket, hogy megéri.";
				link.l1 = "Természetesen egyetértek!";
				link.l1.go = "Escort_LevelUp_1";
				link.l2 = "Sajnálom, de ez a munka nem nekem való. Attól tartok, passzolok.";
				link.l2.go = "Escort_LevelUp_exit";
			break;
			case 1://защитить конвой вблизи текущего острова от пиратов
				pchar.questTemp.WPU.Current.TargetIslandID = Islands[GetCharacterCurrentIsland(PChar)].id;//текущий остров
				pchar.questTemp.WPU.Escort.TargetPortmanID = pchar.questTemp.WPU.Escort.StartCity +"_portman";//ИД портмана
				dialog.text = "Egy kereskedelmi karavánnak kellett volna megérkeznie a kolóniánkra, de mielôtt a kikötôbe ért volna, kalózok támadták meg. A csata épp most zajlik, miközben beszélgetünk. Az erôd ágyúinak hatótávolságán kívül van, és jelenleg nem áll rendelkezésemre kísérôhajó, így nem tudok segítséget nyújtani szegény kereskedôknek. Te egy gáláns kapitány vagy, ezért arra kérlek, hogy avatkozz közbe, és segíts a kereskedôknek visszaverni a támadást! Megtennéd?";
				link.l1 = "Természetesen! Ez becsületbeli ügy!";
				link.l1.go = "Escort_LevelUp_2";
				link.l2 = "Sajnálom, de ez a munka nem nekem való. Attól tartok, passzolok.";
				link.l2.go = "Escort_LevelUp_exit";
			break;
			case 2://встретить и довести
				pchar.questTemp.WPU.Escort.ShipName = GenerateRandomNameToShip(sti(pchar.nation));
				pchar.questTemp.WPU.Escort.ShipType = Escort_ShipType();
				pchar.questTemp.WPU.Escort.City = findCurrentCity1(npchar);//город, откуда забрать
				pchar.questTemp.WPU.Escort.TargetPortmanID = pchar.questTemp.WPU.Escort.City +"_portman";//ИД портмана
				sld = characterFromId(pchar.questTemp.WPU.Escort.TargetPortmanID);
				pchar.questTemp.WPU.Escort.Nation = sld.nation;//нация получателя
				pchar.questTemp.WPU.Current.TargetIslandID = GetCharacterCurrentIslandId(npchar);//ИД целевого ареала
				pchar.questTemp.WPU.Escort.DaysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(pchar.questTemp.WPU.Escort.StartCity), GetArealByCityName(pchar.questTemp.WPU.Escort.City));//расстояние в днях
				pchar.questTemp.WPU.Escort.Money = sti(pchar.questTemp.WPU.Escort.DaysQty)*2000+20000;
				pchar.questTemp.WPU.Escort.Chance = rand(1);
				dialog.text = "Egy hajó fegyverekkel és lôszerrel, amit a kolóniánk rendelt, nemrég érkezett a kolóniára "+XI_ConvertString(pchar.questTemp.WPU.Escort.City)+". Kísérôhajója zátonyra futott, súlyosan megsérült, és egyhamar nem tudja elhagyni a kikötôt. Nem kockáztathatjuk meg, hogy egy ilyen rakományt szállító kereskedelmi hajót egyedül küldjünk el.\nElvállalnátok, hogy elkíséritek a kolóniánkra? A munka díjazása "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money))+".";
				link.l1 = "Természetesen egyetértek!";
				link.l1.go = "Escort_LevelUp_0";
				link.l2 = "Sajnálom, de ez a munka nem nekem való. Attól tartok, passzolok.";
				link.l2.go = "Escort_LevelUp_exit";
			break;
		}
	break;
	
	case "Escort_LevelUp_exit":
		dialog.text = "Kár, valóban. Igazából számítottam rád...";
		link.l1 = "Én is sajnálom. Nos, amíg újra találkozunk, " + GetAddress_FormToNPC(NPChar) + ".";
		link.l1.go = "exit";
		pchar.questTemp.WPU.Escort.count = sti(pchar.questTemp.WPU.Escort.count)-1;//скрутим счетчик
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp");
		DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
	break;
	
	case "Escort_LevelUp_0":
		dialog.text = "Kiváló! Tudtam, hogy számíthatok rád. Kérem, igyekezzen minél gyorsabb lenni. Szerintem a "+FindRussianDaysString(pchar.questTemp.WPU.Escort.DaysQty)+" elég lesz a "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.City+"Gen")+". Tessék, vegye el ezeket az igazolványokat, amelyek igazolják a személyazonosságát. Hátszelet, kapitány!";
		link.l1 = "Ne aggódj, nem hagylak cserben.";
		link.l1.go = "Escort_LevelUp_0_go";
	break;
	
	case "Escort_LevelUp_0_go":
		ReOpenQuestHeader("Escort");
		AddQuestRecord("Escort", "19");
		AddQuestUserData("Escort", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money)));
		AddQuestUserData("Escort", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen"));
		AddQuestUserData("Escort", "sTargetColony",XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.City));
		AddQuestUserData("Escort", "sDay", FindRussianDaysString(pchar.questTemp.WPU.Escort.DaysQty));
		SetFunctionTimerCondition("EscortArsenalShip_Over", 0, 0, sti(pchar.questTemp.WPU.Escort.DaysQty)+1, false);
		DialogExit();
		pchar.questTemp.WPU.Escort = "begin";
		pchar.questTemp.WPU.Escort.LevelUp_0 = "true";
		pchar.questTemp.WPU.Escort.count = sti(pchar.questTemp.WPU.Escort.count)+1;
	break;
	
	case "Escort_LUGo_0":
	ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
	if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)//проверка на наличие корабля в порту
	{
		pchar.quest.EscortArsenalShip_Over.over = "yes";
		dialog.text = "Végre! Az a hajó már elég régóta szemet szúrt. Akkor vedd át a parancsnokságot. A hajó neve "+pchar.questTemp.WPU.Escort.ShipName+", és a kapitányát azonnal értesítjük az érkezésedrôl.";
		link.l1 = "Mondd meg neki, hogy készítse fel a hajóját az indulásra - én a lehetô leghamarabb indulok.";
		link.l1.go = "Escort_LUGo_01";
	}
	else
	{
		dialog.text = "Nem látom a hajóját a kikötôben. Feküdjön le egyelôre, és késôbb jöjjön vissza hozzám - akkor majd beszélünk.";
		link.l1 = "Úgy lesz.";
		link.l1.go = "exit";
	}
	break;
	
	case "Escort_LUGo_01"://добавляем компаньона
		int iShipType = sti(pchar.questTemp.WPU.Escort.ShipType);
		sTemp = pchar.questTemp.WPU.Escort.ShipName;
		sld = GetCharacter(NPC_GenerateCharacter("ArsenalShipCaptain", "citiz_41", "man", "man", 15, sti(pchar.nation), -1, true, "quest"));
		FantomMakeSmallSailor(sld, iShipType, sTemp, CANNON_TYPE_CANNON_LBS16, 65, 22, 24, 35, 33);
		SetFantomParamFromRank(sld, 15, true); 
		SetCaptanModelByEncType(sld, "war");
		SetCharacterGoods(sld, GOOD_FOOD, 500);
		SetCharacterGoods(sld, GOOD_BALLS, 5000);
		SetCharacterGoods(sld, GOOD_GRAPES, 3000);
		SetCharacterGoods(sld, GOOD_KNIPPELS, 3000);
		SetCharacterGoods(sld, GOOD_BOMBS, 5000);
		SetCharacterGoods(sld, GOOD_POWDER, 10000);
		SetCharacterGoods(sld, GOOD_WEAPON, 3000);
		sld.CompanionEnemyEnable = false; //всегда друзья
		SetCompanionIndex(pchar, -1, sti(sld.index));
		SetCharacterRemovable(sld, false);
		sld.loyality = MAX_LOYALITY;
		sld.Dialog.Filename = "Common_portman.c";
		sld.dialog.currentnode = "Escort_companion";
		DialogExit();
		AddQuestRecord("Escort", "20");
		AddQuestUserData("Escort", "sSName", pchar.questTemp.WPU.Escort.ShipName);
		pchar.quest.Escort_fail.win_condition.l1 = "NPC_Death";//прерывание на потопление сопровождаемого
		pchar.quest.Escort_fail.win_condition.l1.character = "ArsenalShipCaptain";
		pchar.quest.Escort_fail.function = "EscortArsenalShip_failed";
		SetFunctionTimerCondition("EscortArsenalShipGo_Over", 0, 0, sti(pchar.questTemp.WPU.Escort.DaysQty)+6, false);
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp_0");
		pchar.questTemp.WPU.Escort.LevelUpGo_0 = "true";
		if (sti(pchar.questTemp.WPU.Escort.Chance) == 0) EnemyNationHunterOnMap(true);//скоростной перехватчик
		else FrahtHunterOnSea();
	break;
	
	case "Escort_LUGo_complete":
	ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
	if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)//проверка на наличие корабля в порту
	{
		pchar.quest.Escort_fail.over = "yes";
		pchar.quest.EscortArsenalShipGo_Over.over = "yes";
		dialog.text = "Kiváló! Ismét bebizonyítottad, hogy lehet rád számítani. Köszönöm a jól végzett munkát. Kérem, fogadja el a fizetést - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Escort.Money))+". És ne felejtsen el idônként meglátogatni - mindig van egy-két munka egy olyan kapitánynak, mint ön.";
		link.l1 = "Örülök, hogy ezt hallom, " + GetAddress_FormToNPC(NPChar) + "! Természetesen az együttmûködésünk folytatódni fog. Üdvözlettel!";
		link.l1.go = "Escort_LUGo_complete_1";
	}
	else
	{
		dialog.text = "Nem látom a hajóját a kikötôben. Feküdjön le egyelôre, és késôbb jöjjön vissza hozzám - akkor majd beszélünk.";
		link.l1 = "Rendben, meg is teszem.";
		link.l1.go = "exit";
	}
	break;
	
	case "Escort_LUGo_complete_1":
		RemoveCharacterCompanion(Pchar, characterFromID("ArsenalShipCaptain"));
		sld = characterFromId("ArsenalShipCaptain");
		sld.lifeday = 0;//на всякий случай
		AddMoneyToCharacter(pchar, sti(pchar.questTemp.WPU.Escort.Money));
		ChangeCharacterComplexReputation(pchar,"nobility", 2);
		ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Escort.Nation), 2);
		AddQuestRecord("Escort", "24");
		AddQuestUserData("Escort", "sSName", pchar.questTemp.WPU.Escort.ShipName);
		CloseQuestHeader("Escort");
		DialogExit();
		pchar.questTemp.WPU.Escort = "complete";
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUpGo_0");
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp");
		DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
		AddComplexSeaExpToScill(100, 100, 100, 0, 100, 0, 0);
		AddComplexSelfExpToScill(30, 30, 30, 30);
		AddCharacterExpToSkill(pchar, "Leadership", 100);//авторитет
		SaveCurrentNpcQuestDateParam(npchar, "work_date");
	break;
	
	case "Escort_LevelUp_1":
		dialog.text = "Akkor biztonságos utat kívánok. És kérlek, ne késlekedj a kereséssel! Annak a hajónak a legénysége azonnali segítségre szorulhat.";
		link.l1 = "Megvan. Még ma útnak indulok!";
		link.l1.go = "Escort_LevelUp_1_select";
	break;
	
	case "Escort_LevelUp_1_select"://выберем приключение
		switch (rand(2))
		{
			case 0://весь побитый и остался без мачты
				pchar.quest.DisasterShip_WM.win_condition.l1 = "hely";
				pchar.quest.DisasterShip_WM.win_condition.l1.location = pchar.questTemp.WPU.Current.TargetIslandID;
				pchar.quest.DisasterShip_WM.function = "CreateDisasterShip_WithoutMasts";
				pchar.questTemp.WPU.Escort.LevelUp_1WM = "true";
			break;
			case 1://ведет бой с пиратусами в шторме
				pchar.quest.DisasterShip_VSP.win_condition.l1 = "hely";
				pchar.quest.DisasterShip_VSP.win_condition.l1.location = pchar.questTemp.WPU.Current.TargetIslandID;
				pchar.quest.DisasterShip_VSP.function = "CreateDisasterShip_VSPirate";
				for (i=0; i<MAX_ISLANDS; i++)//устроим шторм
				{				
					if (Islands[i].id == pchar.questTemp.WPU.Current.TargetIslandID)
					{
					Islands[i].alwaysStorm = true; 
					Islands[i].storm = true;
					Islands[i].tornado = true; 
					}
				}
				pchar.questTemp.WPU.Escort.LevelUp_1VSP = "true";
			break;
			case 2://потонул
				pchar.questTemp.WPU.Current.TargetIslandID.Shore = SelectQuestShoreLocationFromSea(pchar.questTemp.WPU.Current.TargetIslandID);
				pchar.quest.DisasterShip_S.win_condition.l1 = "location";
				pchar.quest.DisasterShip_S.win_condition.l1.location = pchar.questTemp.WPU.Current.TargetIslandID.Shore;
				pchar.quest.DisasterShip_S.function = "CreateDisasterShip_Crew";
				pchar.questTemp.WPU.Escort.LevelUp_1S = "true";
			break;
		}
		ReOpenQuestHeader("Escort");
		AddQuestRecord("Escort", "25");
		AddQuestUserData("Escort", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen"));
		AddQuestUserData("Escort", "sIsland", XI_ConvertString(pchar.questTemp.WPU.Current.TargetIslandID));
		AddQuestUserData("Escort", "sSName", pchar.questTemp.WPU.Escort.ShipName);
		AddQuestUserData("Escort", "sTargetColony",XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.City));
		SetFunctionTimerCondition("DesIsland_Over", 0, 0, 15, false);
		DialogExit();
		pchar.questTemp.WPU.Escort = "begin";
		pchar.questTemp.WPU.Escort.count = sti(pchar.questTemp.WPU.Escort.count)+1;
	break;
	
	case "Escort_LU1WM_complete":
	ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
	if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)//проверка на наличие корабля в порту
	{
		dialog.text = "Igen, már értesítettek. Kiváló munka, " + GetAddress_Form(NPChar) + "! Ismét bebizonyította, hogy Ön az, akire számíthatok. Kapja meg a jutalmát - 30.000 pezó.\nNe feledje, hogy idôrôl idôre meglátogasson - a magához hasonló emberek felbecsülhetetlen értékûek, és én mindig találok Önnek megfelelô munkát.";
		link.l1 = "Örömmel hallom, " + GetAddress_FormToNPC(NPChar) + "! Természetesen a továbbiakban is együtt fogunk mûködni. Minden jót!";
		link.l1.go = "Escort_LU1WM_complete_1";
	}
	else
	{
		dialog.text = "Nem látom a hajóját a kikötôben. Feküdjön le egyelôre, és késôbb jöjjön vissza hozzám - akkor majd beszélünk.";
		link.l1 = "Rendben, meg is teszem.";
		link.l1.go = "exit";
	}
	break;
	
	case "Escort_LU1WM_complete_1":
		sld = characterFromId("WMCaptain");
		sld.lifeday = 0;
		DialogExit();
		AddMoneyToCharacter(pchar, 30000);
		ChangeCharacterComplexReputation(pchar,"nobility", 5);
		ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Escort.Nation), 5);
		AddQuestRecord("Escort", "32");
		AddQuestUserData("Escort", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen"));
		AddQuestUserData("Escort", "sMoney", 30000);
		CloseQuestHeader("Escort");
		pchar.questTemp.WPU.Escort = "complete";
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp_1WM");
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp");
		DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
		AddCharacterExpToSkill(pchar, "Sailing", 100);//навигация
		AddCharacterExpToSkill(pchar, "Repair", 300);//починка
		AddCharacterExpToSkill(pchar, "Commerce", 100);//торговля
		AddCharacterExpToSkill(pchar, "Leadership", 100);//авторитет
		AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
		SaveCurrentNpcQuestDateParam(npchar, "work_date");
	break;
	
	case "Escort_LU1VSP_complete":
	ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
	if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)//проверка на наличие корабля в порту
	{
		dialog.text = "Igen, már mesélt a kalózokkal vívott csatáról, és arról, hogy milyen hôsiesen védted a hajóját. Kiváló munka, " + GetAddress_Form(NPChar) + "! Ismét bebizonyítottad, hogy te vagy az, akire számíthatok. Vedd át a jutalmadat - 50 000 pezó.\nNe feledd, hogy idôrôl idôre meglátogass - az olyan emberek, mint te, felbecsülhetetlen értékûek, és mindig találok neked megfelelô munkát.";
		link.l1 = "Örülök, hogy ezt hallom, " + GetAddress_FormToNPC(NPChar) + "! Természetesen az együttmûködésünk folytatódni fog. Üdvözlettel!";
		link.l1.go = "Escort_LU1VSP_complete_1";
	}
	else
	{
		dialog.text = "Nem látom a hajóját a kikötôben. Feküdjön le egyelôre, és késôbb jöjjön vissza hozzám - akkor majd beszélünk.";
		link.l1 = "Rendben, meg is teszem.";
		link.l1.go = "exit";
	}
	break;
	
	case "Escort_LU1VSP_complete_1":
		sld = characterFromId("WMCaptain");
		sld.lifeday = 0;
		DialogExit();
		AddMoneyToCharacter(pchar, 50000);
		ChangeCharacterComplexReputation(pchar,"nobility", 10);
		ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Escort.Nation), 6);
		AddQuestRecord("Escort", "32");
		AddQuestUserData("Escort", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen"));
		AddQuestUserData("Escort", "sMoney", 50000);
		CloseQuestHeader("Escort");
		pchar.questTemp.WPU.Escort = "complete";
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp_1VSP");
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp");
		DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
		AddComplexSeaExpToScill(100, 150, 150, 100, 0, 0, 0);
		AddComplexSelfExpToScill(50, 50, 50, 50);
		AddCharacterExpToSkill(pchar, "Leadership", 100);//авторитет
		AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
		SaveCurrentNpcQuestDateParam(npchar, "work_date");
	break;
	
	case "Escort_LU1VSP_completeSink":
		dialog.text = "Micsoda tragikus vég... Isten nyugosztalja a lelküket.";
		link.l1 = "Mindent megtettem, amit tudtam, " + GetAddress_FormToNPC(NPChar) + ". A vihar még rosszabbá tette a helyzetet.";
		link.l1.go = "Escort_LU1VSP_completeSink_1";
	break;
	
	case "Escort_LU1VSP_completeSink_1":
		dialog.text = "Hiszem, " + GetAddress_Form(NPChar) + ", hogy ön mindent megtett, amit csak tudott, hogy megmentse a hajót és azokat a szerencsétlen matrózokat. De sajnos... Nos, kérem, vegye át a jutalmát - 10000 pezó - és köszönöm a szolgálatát.";
		link.l1 = "Nincs mit megköszönnöd, " + GetAddress_FormToNPC(NPChar) + ". Nagyon sajnálom. Nos, viszlát.";
		link.l1.go = "Escort_LU1VSP_completeSink_2";
	break;
	
	case "Escort_LU1VSP_completeSink_2":
		DialogExit();
		AddMoneyToCharacter(pchar, 10000);
		ChangeCharacterComplexReputation(pchar,"nobility", 1);
		AddQuestRecord("Escort", "32");
		AddQuestUserData("Escort", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen"));
		AddQuestUserData("Escort", "sMoney", 10000);
		CloseQuestHeader("Escort");
		pchar.questTemp.WPU.Escort = "complete";
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp_1VSP");
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp");
		DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
		AddComplexSeaExpToScill(50, 50, 50, 50, 0, 0, 0);
		AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
		SaveCurrentNpcQuestDateParam(npchar, "work_date");
	break;
	
	case "Escort_LU1S_complete":
		dialog.text = "Igen, már mesélt nekem arról, hogy harcoltál a vörösbôrû pogányokkal, majd egy kalózhajóval - mint egy igazi hôs. Kiváló munka, " + GetAddress_Form(NPChar) + "! Ismét bebizonyítottad, hogy te vagy az, akire számíthatok.\nVegye meg a jutalmát - 40 000 pezó. Ne feledje, hogy idôrôl idôre látogasson el hozzám - az olyan emberek, mint Ön, felbecsülhetetlen értékûek, és mindig találok Önnek megfelelô munkát.";
		link.l1 = "Örülök, hogy ezt hallom, " + GetAddress_FormToNPC(NPChar) + "! Természetesen az együttmûködésünk folytatódni fog. Üdvözlettel!";
		link.l1.go = "Escort_LU1S_complete_1";
	break;
	
	case "Escort_LU1S_complete_1":
		sld = characterFromId("WMCaptain");
		sld.lifeday = 0;
		DialogExit();
		AddMoneyToCharacter(pchar, 40000);
		ChangeCharacterComplexReputation(pchar,"nobility", 8);
		ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Escort.Nation), 3);
		AddQuestRecord("Escort", "32");
		AddQuestUserData("Escort", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen"));
		AddQuestUserData("Escort", "sMoney", 40000);
		CloseQuestHeader("Escort");
		pchar.questTemp.WPU.Escort = "complete";
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp_1S");
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp");
		DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
		AddComplexSeaExpToScill(100, 150, 150, 100, 0, 0, 0);
		AddComplexSelfExpToScill(100, 100, 100, 100);
		AddCharacterExpToSkill(pchar, "Leadership", 100);//авторитет
		AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
		SaveCurrentNpcQuestDateParam(npchar, "work_date");
	break;
	
	case "Escort_LevelUp_2":
		dialog.text = "Tudtam, hogy számíthatok rád. Sok szerencsét, kapitány! Az egész kolónia gyôzelmet kíván!";
		link.l1 = "Megpróbálok megfelelni az elvárásaidnak. Most pedig kihajózom, és Isten segítsen minket!";
		link.l1.go = "Escort_LevelUp_2_go";
	break;
	
	case "Escort_LevelUp_2_go":
		ReOpenQuestHeader("Escort");
		AddQuestRecord("Escort", "41");
		AddQuestUserData("Escort", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen"));
		SetFunctionTimerCondition("CaravanNearIsland_Over", 0, 0, 2, false);
		pchar.questTemp.WPU.Escort.count = sti(pchar.questTemp.WPU.Escort.count)+1;
		pchar.quest.CaravanNearIsland_Start.win_condition.l1 = "location";
		pchar.quest.CaravanNearIsland_Start.win_condition.l1.location = pchar.questTemp.WPU.Current.TargetIslandID;
		pchar.quest.CaravanNearIsland_Start.function = "CreateCaravanNearIsland";
		pchar.questTemp.WPU.Escort.LevelUp_2 = "true";
		pchar.questTemp.WPU.Escort = "begin";
		DialogExit();
	break;
	
	case "Escort_LU2_complete":
		switch (sti(pchar.questTemp.WPU.Escort.LevelUp_2.Qty))
		{
			case 1:
				pchar.questTemp.WPU.Escort.LevelUp_2.Money = 10000;
				dialog.text = "Igen, az egész város figyelte a csatátokat. Szegény kereskedôk, sajnálom ôket. Nos, legalább egy hajót sikerült megmenteniük, így a 10000 pezó jutalmuk megérdemelt. Kérem, fogadja el - és köszönöm a segítségét.";
				link.l1 = "Nincs mit megköszönnöd... Sajnálatos, hogy nem nyertem meg döntôen ezt a csatát, de mindent megtettem, amit tudtam. Isten veled, " + GetAddress_FormToNPC(NPChar) + ".";
				link.l1.go = "Escort_LU2_complete_1";
			break;
			case 2:
				pchar.questTemp.WPU.Escort.LevelUp_2.Money = 25000;
				dialog.text = "Igen, az egész város figyelte a csatát, amit vívtatok - és nagyon ügyesen csináltátok, azt kell mondanom. Szegény kereskedô, annyira sajnálom ôt... De ha te nem lettél volna, egyikük sem menekült volna meg élve, így a 25000 pezó jutalmad nagyon is megérdemelt. Kérem, fogadja el - és köszönöm a segítségét.";
				link.l1 = "Nos, köszönöm, hogy elismerôen nyilatkoztál a tetteimrôl, de nem hiszem, hogy ez volt a legjobb csatám - még mindig elvesztettem egy hajót. Nos, a sors az sors, és ez ellen nincs mit tenni. Viszlát, " + GetAddress_FormToNPC(NPChar) + ".";
				link.l1.go = "Escort_LU2_complete_1";
			break;
			case 3:
				pchar.questTemp.WPU.Escort.LevelUp_2.Money = 50000;
				dialog.text = "Igen, az egész város figyelte a csatát, amit vívtatok - egyszerûen csodálatosak voltatok! Épp most vertétek szét azoknak a mocskos kalózoknak az egész századát! Most már megtanulták a leckét - kár, hogy ez már nem segít rajtuk. A jutalmad 50000 pezó - kérlek, fogadd el.";
				link.l1 = "Köszönöm a tetteim dicsérô értékelését! Mindig öröm segíteni. És most, " + GetAddress_FormToNPC(NPChar) + ", kérem engedje meg, hogy távozzak.";
				link.l1.go = "Escort_LU2_complete_1";
			break;
		}
	break;
	
	case "Escort_LU2_complete_1":
		iTemp = sti(pchar.questTemp.WPU.Escort.LevelUp_2.Qty);
		DialogExit();
		Group_DeleteGroup("CaravanShip");
		AddMoneyToCharacter(pchar, sti(pchar.questTemp.WPU.Escort.LevelUp_2.Money));
		ChangeCharacterComplexReputation(pchar,"nobility", iTemp*2);
		ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Escort.Nation), iTemp);
		AddQuestRecord("Escort", "32");
		AddQuestUserData("Escort", "sStartCity", XI_ConvertString("Colony"+pchar.questTemp.WPU.Escort.StartCity+"Gen"));
		AddQuestUserData("Escort", "sMoney", sti(pchar.questTemp.WPU.Escort.LevelUp_2.Money));
		CloseQuestHeader("Escort");
		AddCharacterExpToSkill(pchar, "Sailing", iTemp*35);//навигация
		AddCharacterExpToSkill(pchar, "Accuracy", iTemp*50);//меткость
		AddCharacterExpToSkill(pchar, "Cannons", iTemp*50);//орудия
		AddCharacterExpToSkill(pchar, "Grappling", iTemp*35);//абордаж
		AddCharacterExpToSkill(pchar, "Leadership", iTemp*40);//авторитет
		AddCharacterExpToSkill(pchar, "Fortune", iTemp*35);//везение
		AddCharacterExpToSkill(pchar, "FencingL", iTemp*35);//лёгкое оружие
		AddCharacterExpToSkill(pchar, "FencingS", iTemp*35);//среднее оружие
		AddCharacterExpToSkill(pchar, "FencingH", iTemp*35);//тяжелое оружие
		AddCharacterExpToSkill(pchar, "Pistol", iTemp*35); //пистоли
		pchar.questTemp.WPU.Escort = "complete";
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp_2");
		DeleteAttribute(pchar, "questTemp.WPU.Escort.LevelUp");
		DeleteAttribute(pchar, "questTemp.WPU.Escort.TargetPortmanID");
		SaveCurrentNpcQuestDateParam(npchar, "work_date");
	break;
	
		case "PortmanQuest_NF":
			dialog.text = "Hmm, ez rossz. Ebben az esetben a további munkád számomra szóba sem jöhet.";
			link.l1 = "Értettem. A következôt akartam mondani...";
			link.l1.go = "node_2";
		break;
		
		//сгоревшее судно
		case "BurntShip2":
			dialog.text = "Kár, kapitány... Kár, hogy nem hajlandó segíteni nekem.";
			link.l1 = "Ez nem az én akaratomon múlik, jóember. Meg kell értenie. Viszontlátásra.";
			link.l1.go = "exit";
			NPChar.Quest.BurntShip.LastQuestDate = sLastSpeakDate;
		break;
		
		case "BurntShip4":
			dialog.text = "Mi van magával, kapitány?! Nem szégyelli magát?! Hogy tehetted?! Tudom, mi a dolgom, már sok éve szolgálok. Vannak biztosítási szerzôdések, és a biztosító hajlandó fizetni, és biztosíthatom, hogy a biztosítási összeg egészen tisztességes.";
			link.l1 = "Mi a problémája, uram? Felrobbant egy puskaporos terem, voltak áldozatok, és most önnek kell bíróság elé állnia a gondatlansága miatt?";
			link.l1.go = "BurntShip5";
		break;
		
		case "BurntShip5":
			sCapitainId = GenerateRandomName(sti(NPChar.nation), "man");
			
			dialog.text = "Nem! Dehogyis! Uram, mentsd meg a lelkemet, különben elveszítem a fejemet. A raktér teljesen üres volt, hála az Úrnak, a Boldogságos Szûz Máriának!\n" +
				"És az a baj, hogy a hajó a... vagy inkább az egész Karib-tengeren jól ismert " + sCapitainId + "úré volt. És Európában épült különleges megrendelésre, rendkívüli tulajdonságokkal. " +
				"És ez a hajótulajdonos túlságosan büszke volt, és jobbra-balra dicsekedett, egyfajta tökfej, Isten bocsássa meg... Most mit mondjak neki? Inkább megölöm magam, esküszöm...";
			link.l1 = "Ó, most már látom, mi a baj, valóban. És mi volt olyan különleges a hajóban? Milyen szokatlan tulajdonságai voltak, amire a tulajdonosa olyan büszke volt?";
			link.l1.go = "BurntShip6";
			
			NPChar.Quest.BurntShip.ShipOwnerName = sCapitainId;
		break;
		
		case "BurntShip6":
			BurntShipQuest_FillStartParams(NPChar);
			
			attrL = NPChar.Quest.BurntShip.ShipAttribute;
			iTest = sti(NPChar.Quest.BurntShip.ShipType);
			
			switch(attrL)
			{
				case "speedrate":
					attrL = "A " + GetStrSmallRegister(XI_ConvertString(ShipsTypes[iTest].Name + "Acc")) + "'s szélsebessége több mint " + NPChar.Quest.BurntShip.ShipNeededValue + " csomó volt. Ez volt a magánhajós büszkesége... És most csak szólna az embereinek, hogy akasszanak fel az udvaron. Micsoda ördög hozta ôt a mi kikötônkbe azzal a kalózkáddal együtt...";
				break;
				
				case "turnrate":
					attrL = "A " + GetStrSmallRegister(XI_ConvertString(ShipsTypes[iTest].Name + "Acc")) + "'s manôverezôképessége több mint " + NPChar.Quest.BurntShip.ShipNeededValue + " egység volt. Ez volt a katona büszkesége... És most csak úgy agyonkorbácsoltatott volna. Micsoda ördög tanácsolta neki, hogy hagyja ott a kádját...";
				break;
				
				case "capacity":
					attrL = "Az ô " + GetStrSmallRegister(XI_ConvertString(ShipsTypes[iTest].Name + "Acc")) + "' holtteste több mint " + NPChar.Quest.BurntShip.ShipNeededValue + " egység volt. A kapzsiság rossz, én mondom neked. És most éppen felnégyeltetne a bíróságon. Miféle ördög tanácsolta neki, hogy hagyja ott a kádját...";
				break;
			}
			
			dialog.text = attrL;
			link.l1 = "És mit mondanak az emberek a kikötôben? Tényleg lehetetlen itt egy másikat építeni?";
			link.l1.go = "BurntShip7";
		break;
		
		case "BurntShip7":
			dialog.text = "Senki sem tudja. Még a közeli szigetre is elmentem, hogy megkérdezzem az embereket. Azt mondták, hogy van egy neves mester Isla Tesorón, aki a hajóépítésben szinte mindenre képes. De Isla Tesoro olyan rohadt messze van. Már csak az olyan szabad kapitányok segítségére számíthatok, mint ti. Talán te találsz nekem egy ilyen hajót. A többirôl pedig majd én gondoskodom\n" +
				"nagylelkûen megköszönöm, és a biztosító is ugyanezt fogja tenni. Az ügy szokatlan, tudod. Ki akarna felbosszantani egy ilyen hatalmas embert?";
			link.l1 = "Igen, ez nem lesz könnyû. És mennyi idôm van még?";
			link.l1.go = "BurntShip8";
			link.l2 = "Nem, pajtás, nem keveredhetek bele egy ilyen ügybe. Arról nem is beszélve, hogy nincs garancia arra, hogy egyáltalán létezik ilyen paraméterekkel rendelkezô hajó. Sajnálom...";
			link.l2.go = "BurntShip2";
		break;
		
		case "BurntShip8":
			dialog.text = "Hála Istennek, még van idô. A tulajdonos elhajózott Európába, és leghamarabb fél év múlva tér vissza.";
			link.l1 = "Hát, azt hiszem, majd én megoldom. Hozok neked egy hasonló hajót. De ezt tartsd észben - ha úgy döntesz, hogy túl szûkmarkú leszel, a szemed láttára égetem el!";
			link.l1.go = "BurntShip9";
		break;
		
		case "BurntShip9":
			dialog.text = "Mire céloz, kapitány? Bizonyára megértem, hogy idôre van szüksége - ez nem arról szól, hogy találjon egy véletlenszerû kádat a legközelebbi pocsolyában... Csak hozza ide a hajót, és mi megteszünk minden tôlünk telhetôt, erre számíthat...";
			link.l1 = "Remélem... Nos, várjatok rám és a jó hírekre. Viszontlátásra.";
			link.l1.go = "BurntShip9_exit";
		break;
		
		case "BurntShip9_exit":
			attrL = "BurntShipQuest_TimeIsOver_" + NPChar.Id;
			PChar.Quest.(attrL).win_condition.l1 = "Timer";
			PChar.Quest.(attrL).win_condition.l1.date.day = GetAddingDataDay(0, 6, 0);
			PChar.Quest.(attrL).win_condition.l1.date.month = GetAddingDataMonth(0, 6, 0);
			PChar.Quest.(attrL).win_condition.l1.date.year = GetAddingDataYear(0, 6, 0);
			PChar.Quest.(attrL).function = "BurntShipQuest_TimeIsOver";
			PChar.Quest.(attrL).PortmanId = NPChar.id;
			
			attrL = NPChar.Quest.BurntShip.ShipAttribute;
			
			iTest = sti(NPChar.Quest.BurntShip.ShipType);
			
			switch(attrL)
			{
				case "speedrate":
					attrL = "sebesség. A szélsebességnek a " + GetStrSmallRegister(XI_ConvertString(ShipsTypes[iTest].name + "Gen")) + " legalább a következô értéknek kell lennie " + NPChar.Quest.BurntShip.ShipNeededValue;
				break;
				
				case "turnrate":
					attrL = "manôverezôképesség. A " + GetStrSmallRegister(XI_ConvertString(ShipsTypes[iTest].name + "Gen")) + " manôverezôképessége nem lehet kevesebb, mint " + NPChar.Quest.BurntShip.ShipNeededValue;
				break;
				
				case "capacity":
					attrL = "tartsd. A " + GetStrSmallRegister(XI_ConvertString(ShipsTypes[iTest].name + "Gen")) + " tartása nem lehet kevesebb, mint " + NPChar.Quest.BurntShip.ShipNeededValue;
				break;
			}
			
			sTitle = "BurntShipQuest" + NPChar.location;
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "BurntShipQuest", "1");
			AddQuestUserDataForTitle(sTitle, "cityName", XI_ConvertString("Colony" + NPChar.city + "Dat"));
			AddQuestUserData(sTitle, "portmanName", GetFullName(NPChar));
			AddQuestUserData(sTitle, "cityName", XI_ConvertString("Colony" + NPChar.city + "Gen"));
			AddQuestUserData(sTitle, "text", attrL);
			
			NPChar.Quest.BurntShip.LastPortmanName = GetFullName(NPChar); // Запомнм имя
			
			DialogExit();
		break;
		
		// Вариант, когда не уложились в сроки
		case "BurntShip10":
			dialog.text = "Mirôl akartál beszélni?";
			link.l1 = "És hol van az egykori kikötômester, mister " + NPChar.Quest.BurntShip.LastPortmanName + "? Vele van dolgom.";
			link.l1.go = "BurntShip11";
		break;
		
		case "BurntShip11":
			dialog.text = "Már nincs itt. Képzelje el - felgyújtotta egy közismert személy hajóját, és zsebre vágta a biztosítási pénzt. Amíg a hatóságok ezt az egészet tisztázták, ô lemondott és elszökött Európába. Elég nagy szélhámos, nem igaz?";
			link.l1 = "Igen, hallottam ezt a történetet. Sajnálom, de mennem kell.";
			link.l1.go = "BurntShip11_exit";
		break;
		
		case "BurntShip11_exit":
			AddCharacterExpToSkill(pchar, "Sailing", 100);
			AddCharacterExpToSkill(pchar, "Fortune", 100);
			sTitle = "BurntShipQuest" + NPChar.location;
			AddQuestRecordEx(sTitle, "BurntShipQuest", "2");
			AddQuestUserData(sTitle, "portmanName", NPChar.Quest.BurntShip.LastPortmanName);
			CloseQuestHeader(sTitle);
			
			DeleteAttribute(NPChar, "Quest.BurntShip");
			NPChar.Quest.BurntShip.LastQuestDate = sLastSpeakDate;
			
			DialogExit();
		break;
		
		// Не просрочено - проверяем корабль
		case "BurntShip12":
			dialog.text = "Mirôl akartál beszélni?";
			link.l1 = "Egy szokatlan hajót hoztam önnek, pont azt, amit kért. Most várom a jutalmamat.";
			link.l1.go = "BurntShip14";
			link.l2 = "Tudod, " + GetFullName(NPChar) + ", még mindig nem találtam egyetlen hasonló hajót sem, mint amire szükséged van. Azt hiszem, feladom ezt a munkát. Sajnálom, ha cserben hagytalak...";
			link.l2.go = "BurntShip13";
		break;
		
		case "BurntShip13":
			dialog.text = "Kár, kapitány... Kár, hogy nem hajlandó segíteni nekem.";
			link.l1 = "Ez nem az én akaratomról szól, jóember. Kérem, értse meg. Viszontlátásra.";
			link.l1.go = "BurntShip13_exit";
		break;
		
		case "BurntShip13_exit":
			sTitle = "BurntShipQuest" + NPChar.location;
			CloseQuestHeader(sTitle);
			
			ChangeCharacterComplexReputation(pchar,"nobility", -5);
			DeleteAttribute(NPChar, "Quest.BurntShip");
			NPChar.Quest.BurntShip.LastQuestDate = sLastSpeakDate;
			
			DialogExit();
		break;
		
		case "BurntShip14":
			dialog.text = "Ó, tényleg! És mi a neve az új hajónknak?";
			
			sTitle = NPChar.Quest.BurntShip.ShipAttribute;
			ok = (sFrom_sea == "") || (Pchar.location.from_sea == sFrom_sea);
			
			if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
				for(i = 1; i < COMPANION_MAX; i++)
				{
					cn = GetCompanionIndex(PChar, i);
					
					if(cn > 0)
					{
						chref = GetCharacter(cn);
						
						sld = &RealShips[sti(chref.ship.type)];
						
						if(GetRemovable(chref) && sti(sld.basetype) == sti(NPchar.Quest.BurntShip.ShipType) &&
							stf(sld.(sTitle)) >= stf(NPChar.Quest.BurntShip.ShipNeededValue))
						{
							attrL = "l" + i;
							Link.(attrL) = chref.Ship.Name;
							Link.(attrL).go = "BurntShip15";
						}
					}
				}
			}
			
			link.l99 = "Elnézést, késôbb visszajövök.";
			link.l99.go = "exit";
		break;
		
		case "BurntShip15":
			AddCharacterExpToSkill(pchar, "Leadership", 200);
			AddCharacterExpToSkill(pchar, "Sailing", 300);
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			dialog.text = "Ó, kapitány, annyira örülök, hogy nem hagytál cserben! Micsoda "+ GetSexPhrase("remek fiatalember","remek fiatal hölgy") +" maga, szó szerint megmentette az életemet... Kérlek, el tudnál jönni a pénzedért pár nap múlva? Tudja, el kell intéznem a formaságokat a biztosítóval... Addig is elvégezhetne kisebb javításokat a hajón - tudja, felújíthatná a vitorlákat, befoltozhatná a lyukakat, a gondozás sem ártana...";
			link.l99 = "Megígértem, hogy valami csúnya dolgot teszek a hajóval, ha megpróbálsz átverni. Elfelejtetted?";
			link.l99.go = "BurntShip16";
		break;
		
		case "BurntShip16":
			dialog.text = "Nem, nem, persze, hogy nem! Hû maradok a szavamhoz, ne aggódj! Tudja, mivel tudom, hogy több kiadással jár majd az új hajó, úgymond, álcázása, ezért kölcsönadtam a biztosítási pénzt, amit a régi hajóra kaptam, kamatra. Remélem, megérti...";
			link.l1 = "Sokkal jobban megértem majd, ha a pénz a ládámba kerül. A viszontlátásig.";
			link.l1.go = "BurntShip16_exit";
		break;
		
		case "BurntShip16_exit":
			sTitle = "BurntShipQuest" + NPChar.location;
			AddQuestRecordEx(sTitle, "BurntShipQuest", "3");
			
			NPChar.Quest.BurntShip.TwoDaysWait = true;
			SaveCurrentNpcQuestDateParam(NPChar, "Quest.BurntShip.TwoDaysWait"); // Запомним дату
			
			sTitle = "BurntShipQuest" + NPChar.Id;
			PChar.Quest.(sTitle).over = "yes"; // Завершаем прерывание на время
			
			DialogExit();
		break;
		
		case "BurntShip17":
			dialog.text = "Mirôl akartál beszélni?";
			link.l1 = "A jutalmamért jöttem. Még mindig megvan a hajó, amire szükséged van.";
			link.l1.go = "BurntShip18";
		break;
		
		case "BurntShip18":
			dialog.text = "Emlékeztetnél a nevére? A memóriám már nem olyan, mint régen - tudod, az a sok zûrzavar...";
			
			sTitle = NPChar.Quest.BurntShip.ShipAttribute;
			ok = (sFrom_sea == "") || (Pchar.location.from_sea == sFrom_sea);
			
			if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
				for(i = 1; i < COMPANION_MAX; i++)
				{
					cn = GetCompanionIndex(PChar, i);
					
					if(cn > 0)
					{
						chref = GetCharacter(cn);
						
						sld = &RealShips[sti(chref.ship.type)];
						
						if(GetRemovable(chref) && sti(sld.basetype) == sti(NPchar.Quest.BurntShip.ShipType) &&
							stf(sld.(sTitle)) >= stf(NPChar.Quest.BurntShip.ShipNeededValue))
						{
							attrL = "l" + i;
							Link.(attrL) = chref.Ship.Name;
							Link.(attrL).go = "BurntShip19_" + i;
						}
					}
				}
			}
			
			link.l99 = "Elnézést, késôbb visszajövök.";
			link.l99.go = "exit";
		break;
		
		case "BurntShip19":
			sld = &Characters[GetCompanionIndex(PChar, sti(NPChar.Quest.BurntShip.ShipCompanionIndex))];
			cn = GetShipSellPrice(sld, CharacterFromID(NPChar.city + "_shipyarder")) * 3;
			rRealShip = GetRealShip(GetCharacterShipType(sld));
			if (sti(rRealShip.Stolen)) cn *= 3;
			
			dialog.text = "Igen, tökéletes. Kész vagyok átadni a jutalmadat, " + FindRussianMoneyString(cn) + ". A biztosító társaság így becsülte fel a kiégett hajó értékét. A biztosítási összeget kreditládákban fizetik ki - készpénz nincs, sajnálom.";
			link.l1 = "Ó, nem, ez az összeg nem felel meg nekem. Biztos vagyok benne, hogy ez a hajó sokkal drágább.";
			link.l1.go = "BurntShip21";
			link.l2 = "Így van. Örülök, hogy segíthettem. Viszlát!";
			link.l2.go = "BurntShip20_exit";
			NPChar.Quest.BurntShip.Money = cn;
		break;
		
		case "BurntShip20_exit":
			TakeNItems(pchar, "chest", makeint(sti(NPChar.Quest.BurntShip.Money)/12000));
			Log_Info("Kaptál kreditládát");
			PlaySound("interface\important_item.wav");
			sTitle = "BurntShipQuest" + NPChar.location;
			AddQuestRecordEx(sTitle, "BurntShipQuest", "4");
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "money", NPChar.Quest.BurntShip.Money);
			CloseQuestHeader(sTitle);
			
			ChangeCharacterComplexReputation(pchar,"nobility", 3);
			
			sld = &Characters[GetCompanionIndex(PChar, sti(NPChar.Quest.BurntShip.ShipCompanionIndex))];
			RemoveCharacterCompanion(PChar, sld);
			AddPassenger(PChar, sld, false);
			
			DeleteAttribute(NPChar, "Quest.BurntShip");
			NPChar.Quest.BurntShip.LastQuestDate = sLastSpeakDate;
			
			DialogExit();
		break;
		
		case "BurntShip21":
			dialog.text = "Mirôl beszél, kapitány?! Higgye el, tudom, mirôl beszélek. Ebbôl a pénzbôl két ilyen hajót is vehetnél!";
			link.l1 = "Azt hiszem, megtartom. Tudod, csak megkedveltem... Viszontlátásra.";
			link.l1.go = "BurntShip21_exit";
		break;
		
		case "BurntShip21_exit":
			ChangeCharacterComplexReputation(pchar,"nobility", -5);
			
			sTitle = "BurntShipQuest" + NPChar.location;
			AddQuestRecordEx(sTitle, "BurntShipQuest", "5");
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "money", NPChar.Quest.BurntShip.Money);
			CloseQuestHeader(sTitle);
			
			DeleteAttribute(NPChar, "Quest.BurntShip");
			NPChar.Quest.BurntShip.LastQuestDate = sLastSpeakDate;
			
			DialogExit();
		break;
		
		//--> миниквесты портмана
		case "PortmanQuest":
			if (hRand(5) == 2)
			{	//квест догнать и передать судовой журнал
				dialog.text = "Az egyik kapitány az irodámban felejtette a naplóját. Micsoda szétszórt agyú! Szeretném, ha utolérné és visszaadná neki.";
				link.l1 = "Ó, az könnyû lesz... Majd én elviszem!";
				link.l1.go = "PortmanQuest_1";
				link.l2 = "Nem, azt nem fogom elintézni. Ez az ô problémája.";
				link.l2.go = "node_2";
			}
			else
			{	//квест разыскать украденный корабль
				dialog.text = "Egy hajót loptak el az ottani kikötôhelyrôl. Azt akarom, hogy keresse meg az ellopott hajót, és hozza vissza.";
				link.l1 = "Hmm, nos, készen állok a nyomozásra.";
				link.l1.go = "SeekShip_1";
				link.l2 = "Sajnálom, de nem foglalkozom lopott hajók felkutatásával.";
				link.l2.go = "node_2";
			}
		break;
//-------------------------------- квест доставки судового журнала до рассеяного кэпа ---------------------
		case "PortmanQuest_1":
			dialog.text = "Kiváló, itt van a hajónaplója... Tényleg nagy kô esett le a szívemrôl! Egy hajónapló elvesztése nagyon kellemetlen dolog. Mindig is sajnáltam azokat a kapitányokat...";
			link.l1 = "Nos, ez tényleg valami, ami miatt aggódni kell! Most pedig meséljen még arról a szétszórt kapitányról.";
			link.l1.go = "PortmanQuest_2";
			pchar.questTemp.different = "PortmansJornal";
			SetTimerFunction("SmallQuests_free", 0, 0, 1); //освобождаем разрешалку на миниквесты
			SetJornalCapParam(npchar);
			GiveItem2Character(pchar, "PortmansBook");
			pchar.questTemp.PortmansJornal.gem = GenQuestPortman_GenerateGem();
		break;
		case "PortmanQuest_2":
			dialog.text = "Igen, természetesen! A neve " + npchar.quest.PortmansJornal.capName + ", ô a " + GetStrSmallRegister(XI_ConvertString(npchar.quest.PortmansJornal.shipTapeName + "Gen")) + " nevû '" + npchar.quest.PortmansJornal.shipName + "'kapitánya. Nemrég vitorlát bontott, és elment " + XI_ConvertString("Colony" + npchar.quest.PortmansJornal.city + "Acc") + ".";
			link.l1 = "Értem. Rendben, megkeresem. És mi lesz a fizetséggel?";
			link.l1.go = "PortmanQuest_3";
		break;
		case "PortmanQuest_3":
			dialog.text = npchar.quest.PortmansJornal.capName + " Ô maga fog fizetni neked, ez az ô érdeke. Csak koncentrálj arra, hogy minél hamarabb elérd ôt, és minden rendben lesz.";
			link.l1 = "Értem, értem. Nos, akkor én megyek...";
			link.l1.go = "exit";
			sTitle = npchar.id + "PortmansBook_Delivery";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "PortmansBook_Delivery", "1");
			AddQuestUserDataForTitle(sTitle, "sCapName", npchar.quest.PortmansJornal.capName);
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.PortmansJornal.shipTapeName + "Gen")));
			AddQuestUserData(sTitle, "sShipName", npchar.quest.PortmansJornal.shipName);
			AddQuestUserData(sTitle, "sCapName", npchar.quest.PortmansJornal.capName);
			AddQuestUserData(sTitle, "sCapName2", npchar.quest.PortmansJornal.capName);
			AddQuestUserData(sTitle, "sTargetCity", XI_ConvertString("Colony" + npchar.quest.PortmansJornal.city + "Acc"));
			if (GetIslandByCityName(npchar.quest.PortmansJornal.city) != npchar.quest.PortmansJornal.city)
			{
				AddQuestUserData(sTitle, "sAreal", ", ...ami a " + XI_ConvertString(GetIslandByCityName(npchar.quest.PortmansJornal.city) + "Dat"));
			}			
		break;
		// -------------------------------- квест розыска украденного корабля ----------------------------------
		case "SeekShip_1":
			dialog.text = "Kiváló! Tudod, az ellopott hajó egy befolyásos személy tulajdona, ezért ez nagyon fontos nekem. Jól megfizetem a munkát...";
			link.l1 = "Értem. Meséljen még a hajóról és az ellopás körülményeirôl.";
			link.l1.go = "SeekShip_2";
			pchar.questTemp.different = "PortmansSeekShip";
			SetTimerFunction("SmallQuests_free", 0, 0, 1); //освобождаем разрешалку на миниквесты
			SetSeekShipCapParam(npchar);
		break;
		case "SeekShip_2":
			dialog.text = XI_ConvertString(npchar.quest.PortmansSeekShip.shipTapeName) + " a '" + npchar.quest.PortmansSeekShip.shipName + "' nevet éjjel ellopták " + FindRussianDaysString(rand(5)+10) + " . Az ôrt megölték.";
			link.l1 = "Az ôrt megölték. Mostanra már biztos messzire mentek. A nyomok már nem frissek, és ez a probléma.";
			link.l1.go = "SeekShip_3";
		break;
		case "SeekShip_3":
			dialog.text = "Igaz, de még mindig nem láttam értelmét, hogy azonnal riadót fújjak. A katonai hajó utolérhette volna ôket, de az csak darabokra robbantotta volna a hajót - és az nem éppen az, amire szükségem van.";
			link.l1 = "Értem. Nos, akkor elkezdem a keresést. Remélem, szerencsém lesz.";
			link.l1.go = "exit";
			sTitle = npchar.id + "Portmans_SeekShip";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "Portmans_SeekShip", "1");
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.PortmansSeekShip.shipTapeName+"Acc")));
			AddQuestUserData(sTitle, "sShipName", npchar.quest.PortmansSeekShip.shipName);
		break;

		case "SeekShip_break":
			dialog.text = "Kár - de aligha számíthattunk sikerre.";
			link.l1 = "Igen, már túl régen ellopták a hajót.";
			link.l1.go = "SeekShip_break_1";
		break;
		case "SeekShip_break_1":
			dialog.text = "Nos, azért köszönjük a segítségét, még ha az erôfeszítései nem is voltak olyan eredményesek, mint reméltük.";
			link.l1 = "Mindent megtettem, amit tudtam...";
			link.l1.go = "exit";
			sTemp = "SeekShip_checkAbordage" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание на абордаж
			cn = GetCharacterIndex("SeekCap_" + npchar.index);
			//если кэп-вор ещё жив - убираем его
			if (cn > 0)
			{
				characters[cn].LifeDay = 0; 
				Map_ReleaseQuestEncounter(characters[cn].id);
				group_DeleteGroup("SeekCapShip_" + characters[cn].index);
			}
			sTitle = npchar.id + "Portmans_SeekShip";
			AddQuestRecordEx(sTitle, "Portmans_SeekShip", "7");
			CloseQuestHeader(sTitle);
			DeleteAttribute(npchar, "quest.PortmansSeekShip");
			npchar.quest = ""; //освобождаем личный флаг квеста для портмана
			ChangeCharacterComplexReputation(pchar,"nobility", -7);
		break;	

		case "SeekShip_good":
			if (npchar.quest == "SeekShip_sink")
			{
				dialog.text = "Kitûnô! Bár gyanítom, hogy nem éppen ez az a hajó, amit elloptak... Ó, kit érdekel! Elviszem.";
				link.l1 = "Igen, valóban...";
				//npchar.quest.money = makeint(sti(npchar.quest.money) / 4); //снижаем оплату
				ChangeCharacterComplexReputation(pchar,"nobility", 5);
				ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 10);
                AddCharacterExpToSkill(GetMainCharacter(), "Leadership", 10);
                AddCharacterExpToSkill(GetMainCharacter(), "Sailing", 10);
                AddCharacterExpToSkill(GetMainCharacter(), "Commerce", 50);
                AddCharacterExpToSkill(GetMainCharacter(), "Cannons", 20);
			}
			else
			{
				dialog.text = "Kitûnô! Sokat segítettél nekem. El sem tudom képzelni, milyen nehéz volt.";
				link.l1 = "Igen, valóban...";
				ChangeCharacterComplexReputation(pchar,"nobility", 10);
				ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 20);
                AddCharacterExpToSkill(GetMainCharacter(), "Leadership", 100);
                AddCharacterExpToSkill(GetMainCharacter(), "Sailing", 150);
                AddCharacterExpToSkill(GetMainCharacter(), "Grappling", 100);
			}
			link.l1.go = "SeekShip_good_1";
		break;
		case "SeekShip_good_1":
			dialog.text = "Kész vagyok kifizetni neked a jutalmadat. A képezi a " + makeint(sti(npchar.quest.money)) + " in doubloons. Sajnos ennél többet nem tudok fizetni.";
			link.l1 = "Nos, ennyi elég lesz. Köszönöm és meleg üdvözletem.";
			link.l1.go = "exit";
			TakeNItems(pchar, "gold_dublon", sti(npchar.quest.money));
			sTitle = npchar.id + "Portmans_SeekShip";
			AddQuestRecordEx(sTitle, "Portmans_SeekShip", "6");
			CloseQuestHeader(sTitle);
			DeleteAttribute(npchar, "quest.PortmansSeekShip");
			npchar.quest = ""; //освобождаем личный флаг квеста для портмана
		break;

		//------------------------------> инфа по базе квествых кэпов
		//ВНИМАНИЕ. в квестбук должна заносится типовая строка по примеру   PortmansBook_Delivery  #TEXT   5
		//в список портмана заносим тайтл, заголовок и номер строки из quest_text.txt
		//ПРИМЕР: в конце метода  void SetCapitainFromCityToSea(string qName)
		case "CapitainList":
			if (sti(npchar.quest.qty) > 0)
			{
				dialog.text = "Több regisztrált kapitány is van. Érdekel valaki konkrétan?";
				makearef(arCapBase, npchar.quest.capitainsList); 
				for (i=0; i<sti(npchar.quest.qty); i++)
				{
    				arCapLocal = GetAttributeN(arCapBase, i);
					sCapitainId = GetAttributeName(arCapLocal);
					sld = characterFromId(sCapitainId);
					attrL = "l" + i;
					link.(attrL) = GetFullName(sld) + ", kapitánya " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Gen")) + " '" + sld.Ship.name + "'.";
					link.(attrL).go = "CapList_"+attrL;
				}
			}
			else
			{
				dialog.text = "Nincs olyan kapitány a listámon, aki érdekelhetné Önt.";
				link.l1 = "Értem. Nos, köszönöm az információt.";
				link.l1.go = "node_2";
			}
		break;
		case "CapList_l0":
			makearef(arCapBase, npchar.quest.capitainsList);
    		arCapLocal = GetAttributeN(arCapBase,  0);
			sCapitainId = GetAttributeName(arCapLocal);
			sld = characterFromId(sCapitainId);
			dialog.text = LinkRandPhrase("Nos, lássuk csak... A-ha! Ott! ", "Ah-ha... A-ha! Ott! ", "Rendben, akkor... ") +
				"kapitány " + GetFullName(sld) + " " + arCapLocal.date + " évben elhagyta a kikötônket és elhajózott " + XI_ConvertString("Colony" + arCapLocal + "Acc") + ".";
			link.l1 = "Köszönöm. Köszönöm. Szeretném újra átnézni a listát...";
			link.l1.go = "CapitainList";
			link.l2 = "Rendben, ez minden. Nem érdekel más kapitány.";
			link.l2.go = "node_2";
			//заносим запись в СЖ
			AddQuestRecordEx(arCapLocal.QBString1, arCapLocal.QBString2, arCapLocal.QBQty);
			AddQuestUserData(arCapLocal.QBString1, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(arCapLocal.QBString1, "sCapName", GetFullName(sld));
			AddQuestUserData(arCapLocal.QBString1, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Voc")));
			AddQuestUserData(arCapLocal.QBString1, "sShipName", sld.Ship.name);
			AddQuestUserData(arCapLocal.QBString1, "sDate", arCapLocal.date);
			AddQuestUserData(arCapLocal.QBString1, "sTargetCity", XI_ConvertString("Colony" + arCapLocal + "Acc"));
			if (GetIslandByCityName(arCapBase.(sCapitainId)) != arCapBase.(sCapitainId))
			{
				AddQuestUserData(arCapLocal.QBString1, "sAreal", " ami a " + XI_ConvertString(GetIslandByCityName(arCapBase.(sCapitainId)) + "Dat"));
			}
			//убираем из списка
			DeleteAttribute(arCapBase, sCapitainId); 
		break;
		case "CapList_l1":
			makearef(arCapBase, npchar.quest.capitainsList);
    		arCapLocal = GetAttributeN(arCapBase,  1);
			sCapitainId = GetAttributeName(arCapLocal);
			sld = characterFromId(sCapitainId);
			dialog.text = LinkRandPhrase("Nos, lássuk csak... A-ha! Ott! ", "Ah-ha... A-ha! Ott! ", "Rendben, akkor... ") +
				"kapitány " + GetFullName(sld) + " " + arCapLocal.date + " évben elhagyta a kikötônket és elhajózott " + XI_ConvertString("Colony" + arCapLocal + "Acc") + ".";
			link.l1 = "Köszönöm. Köszönöm. Szeretném újra átnézni a listát...";
			link.l1.go = "CapitainList";
			link.l2 = "Rendben, ez minden. Nem érdekel más kapitány.";
			link.l2.go = "node_2";
			//заносим запись в СЖ
			AddQuestRecordEx(arCapLocal.QBString1, arCapLocal.QBString2, arCapLocal.QBQty);
			AddQuestUserData(arCapLocal.QBString1, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(arCapLocal.QBString1, "sCapName", GetFullName(sld));
			AddQuestUserData(arCapLocal.QBString1, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Dat")));
			AddQuestUserData(arCapLocal.QBString1, "sShipName", sld.Ship.name);
			AddQuestUserData(arCapLocal.QBString1, "sDate", arCapLocal.date);
			AddQuestUserData(arCapLocal.QBString1, "sTargetCity", XI_ConvertString("Colony" + arCapLocal + "Acc"));
			if (GetIslandByCityName(arCapBase.(sCapitainId)) != arCapBase.(sCapitainId))
			{
				AddQuestUserData(arCapLocal.QBString1, "sAreal", " ami a " + XI_ConvertString(GetIslandByCityName(arCapBase.(sCapitainId)) + "Dat"));
			}
			//убираем из списка
			DeleteAttribute(arCapBase, sCapitainId); 
		break;
		case "CapList_l2":
			makearef(arCapBase, npchar.quest.capitainsList);
    		arCapLocal = GetAttributeN(arCapBase,  2);
			sCapitainId = GetAttributeName(arCapLocal);
			sld = characterFromId(sCapitainId);
			dialog.text = LinkRandPhrase("Nos, lássuk csak... A-ha! Ott! ", "Ah-ha... A-ha! Ott! ", "Rendben, akkor... ") +
				"kapitány " + GetFullName(sld) + " " + arCapLocal.date + " évben elhagyta a kikötônket és elhajózott " + XI_ConvertString("Colony" + arCapLocal + "Acc") + ".";
			link.l1 = "Köszönöm. Köszönöm. Szeretném újra átnézni a listát...";
			link.l1.go = "CapitainList";
			link.l2 = "Rendben, ez minden. Nem érdekel más kapitány.";
			link.l2.go = "node_2";
			//заносим запись в СЖ
			AddQuestRecordEx(arCapLocal.QBString1, arCapLocal.QBString2, arCapLocal.QBQty);
			AddQuestUserData(arCapLocal.QBString1, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(arCapLocal.QBString1, "sCapName", GetFullName(sld));
			AddQuestUserData(arCapLocal.QBString1, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Dat")));
			AddQuestUserData(arCapLocal.QBString1, "sShipName", sld.Ship.name);
			AddQuestUserData(arCapLocal.QBString1, "sDate", arCapLocal.date);
			AddQuestUserData(arCapLocal.QBString1, "sTargetCity", XI_ConvertString("Colony" + arCapLocal + "Acc"));
			if (GetIslandByCityName(arCapBase.(sCapitainId)) != arCapBase.(sCapitainId))
			{
				AddQuestUserData(arCapLocal.QBString1, "sAreal", " ami a " + XI_ConvertString(GetIslandByCityName(arCapBase.(sCapitainId)) + "Dat"));
			}
			//убираем из списка
			DeleteAttribute(arCapBase, sCapitainId); 
		break;
		case "CapList_l3":
			makearef(arCapBase, npchar.quest.capitainsList);
    		arCapLocal = GetAttributeN(arCapBase,  3);
			sCapitainId = GetAttributeName(arCapLocal);
			sld = characterFromId(sCapitainId);
			dialog.text = LinkRandPhrase("Nos, lássuk csak... A-ha! Ott! ", "Ah-ha... A-ha! Ott! ", "Rendben, akkor... ") +
				"kapitány " + GetFullName(sld) + " " + arCapLocal.date + " évben elhagyta a kikötônket és elhajózott " + XI_ConvertString("Colony" + arCapLocal + "Acc") + ".";
			link.l1 = "Köszönöm. Köszönöm. Szeretném újra átnézni a listát...";
			link.l1.go = "CapitainList";
			link.l2 = "Rendben, ez minden. Nem érdekel más kapitány.";
			link.l2.go = "node_2";
			//заносим запись в СЖ
			AddQuestRecordEx(arCapLocal.QBString1, arCapLocal.QBString2, arCapLocal.QBQty);
			AddQuestUserData(arCapLocal.QBString1, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(arCapLocal.QBString1, "sCapName", GetFullName(sld));
			AddQuestUserData(arCapLocal.QBString1, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Dat")));
			AddQuestUserData(arCapLocal.QBString1, "sShipName", sld.Ship.name);
			AddQuestUserData(arCapLocal.QBString1, "sDate", arCapLocal.date);
			AddQuestUserData(arCapLocal.QBString1, "sTargetCity", XI_ConvertString("Colony" + arCapLocal + "Acc"));
			if (GetIslandByCityName(arCapBase.(sCapitainId)) != arCapBase.(sCapitainId))
			{
				AddQuestUserData(arCapLocal.QBString1, "sAreal", " ami a " + XI_ConvertString(GetIslandByCityName(arCapBase.(sCapitainId)) + "Dat"));
			}
			//убираем из списка
			DeleteAttribute(arCapBase, sCapitainId); 
		break;
		case "CapList_l4":
			makearef(arCapBase, npchar.quest.capitainsList);
    		arCapLocal = GetAttributeN(arCapBase,  4);
			sCapitainId = GetAttributeName(arCapLocal);
			sld = characterFromId(sCapitainId);
			dialog.text = LinkRandPhrase("Nos, lássuk csak... A-ha! Ott! ", "Ah-ha... A-ha! Ott! ", "Rendben, akkor... ") +
				"kapitány " + GetFullName(sld) + " " + arCapLocal.date + " évben elhagyta a kikötônket és elhajózott " + XI_ConvertString("Colony" + arCapLocal + "Acc") + ".";
			link.l1 = "Köszönöm. Köszönöm. Szeretném újra átnézni a listát...";
			link.l1.go = "CapitainList";
			link.l2 = "Rendben, ez minden. Nem érdekel más kapitány.";
			link.l2.go = "node_2";
			//заносим запись в СЖ
			AddQuestRecordEx(arCapLocal.QBString1, arCapLocal.QBString2, arCapLocal.QBQty);
			AddQuestUserData(arCapLocal.QBString1, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(arCapLocal.QBString1, "sCapName", GetFullName(sld));
			AddQuestUserData(arCapLocal.QBString1, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Dat")));
			AddQuestUserData(arCapLocal.QBString1, "sShipName", sld.Ship.name);
			AddQuestUserData(arCapLocal.QBString1, "sDate", arCapLocal.date);
			AddQuestUserData(arCapLocal.QBString1, "sTargetCity", XI_ConvertString("Colony" + arCapLocal + "Acc"));
			if (GetIslandByCityName(arCapBase.(sCapitainId)) != arCapBase.(sCapitainId))
			{
				AddQuestUserData(arCapLocal.QBString1, "sAreal", " ami a " + XI_ConvertString(GetIslandByCityName(arCapBase.(sCapitainId)) + "Dat"));
			}
			//убираем из списка
			DeleteAttribute(arCapBase, sCapitainId); 
		break;
		//<--------------------------- инфа по базе квествых кэпов

		case "ShipStock_1":
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl") && pchar.questTemp.HWIC.Holl == "JacobTakeShip" && !CheckAttribute(npchar, "quest.HWICHoll"))
			{
			dialog.text = "Figyelek - melyik hajóra, milyen idôtartamra?";
    		Link.l1 = "Lucas Rodenburg küldött. Azt mondta, hogy ingyen kiköthetem itt a hajómat.";
    		Link.l1.go = "ShipStock_HWICHoll";
			DelLandQuestMark(npchar);
			break;
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng") && pchar.questTemp.HWIC.Eng == "GotoPortoffice" && !CheckAttribute(npchar, "quest.HWICEng"))
			{
			dialog.text = "Figyelek - melyik hajóra, milyen idôtartamra?";
    		Link.l1 = "Richard Fleetwood küldött. Azt mondta, hogy 10000 pezóért kiköthetem itt a zászlóshajómat.";
    		Link.l1.go = "ShipStock_HWICEng";
			break;
			}
            if (sti(NPChar.Portman) >= 3 || CheckAttribute(pchar, "questTemp.HWIC.TakeQuestShip"))
			{
                dialog.text = "Nos, ez így van. De sajnos jelenleg nem tudom fogadni a hajóját. Nincs szabad dokkolóhely.";
    			Link.l1 = "Kár érte.";
    			Link.l1.go = "exit";
			}
            else
            {
    			ok = (sFrom_sea == "") || (Pchar.location.from_sea == sFrom_sea);
			    if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
				{
					dialog.text = "És melyik hajót akarja itt hagyni?";
	    			for(i=1; i<COMPANION_MAX; i++)
					{
						cn = GetCompanionIndex(PChar, i);
						if(cn > 0)
						{ // hasert со сторожем.
							chref = GetCharacter(cn);
							if (!GetRemovable(chref)) continue;							
							attrL = "l"+i+COMPANION_MAX;
							Link.(attrL)	= XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName) + " '" + chref.Ship.Name + "'.";
							Link.(attrL).go = "ShipStockMan22_" + i;

						}
					}
	    			Link.l17 = "Nem érdekes, köszönöm.";
	    			Link.l17.go = "exit";
    			}
    			else
    			{
					dialog.text = "Hmm... Nem látom egyik hajótokat sem.";
	    			Link.l1 = "Csak a dokkolási lehetôségrôl akartam tudni.";
	    			Link.l1.go = "exit";
				}
			}
		break;

/*  //////////   hasert уже не надо но пусть висит ////////////////////////////////////
		case "ShipStockMan_1":
            NPChar.ShipToStoreIdx = GetCompanionIndex(PChar, 1);
			dialog.text = "Nézzük meg azt a hajót.";
			Link.l1 = "Rendben.";
			Link.l1.go = "ShipStock_2";
			Link.l2 = "Nem, meggondoltam magam.";
			Link.l2.go = "exit";
		break;

		case "ShipStockMan_2":
            NPChar.ShipToStoreIdx = GetCompanionIndex(PChar, 2);
			dialog.text = "Nézzük meg azt a hajót.";
			Link.l1 = "Rendben.";
			Link.l1.go = "ShipStock_2";
			Link.l2 = "Nem, meggondoltam magam.";
			Link.l2.go = "exit";
		break;

		case "ShipStockMan_3":
            NPChar.ShipToStoreIdx = GetCompanionIndex(PChar, 3);
			dialog.text = "Nézzük meg azt a hajót.";
			Link.l1 = "Rendben.";
			Link.l1.go = "ShipStock_2";
			Link.l2 = "Nem, meggondoltam magam.";
			Link.l2.go = "exit";
		break;
		
		case "ShipStockMan_4":
            NPChar.ShipToStoreIdx = GetCompanionIndex(PChar, 4);
			dialog.text = "Nézzük meg azt a hajót.";
			Link.l1 = "Rendben.";
			Link.l1.go = "ShipStock_2";
			Link.l2 = "Nem, meggondoltam magam.";
			Link.l2.go = "exit";
		break;
*/		
		case "ShipStock_2":
            /*chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
			if (CheckAttribute(pchar, "questTemp.GS_BelizSkidka") && npchar.id == "Beliz_portman" && !CheckAttribute(npchar, "DontNullShipBeliz") && sti(RealShips[sti(chref.Ship.Type)].Class) > 1)	// В Белизе скидка 50%
			{
				NPChar.MoneyForShip = GetPortManPriceExt(NPChar, chref)/2;
			}
			else
			{
				if (MOD_SKILL_ENEMY_RATE >= 6) NPChar.MoneyForShip = MOD_SKILL_ENEMY_RATE/2*GetPortManPriceExt(NPChar, chref); // для высокой сложности - 5x цена
				else NPChar.MoneyForShip = GetPortManPriceExt(NPChar, chref);
			}
			dialog.Text = XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName) + " '" + chref.Ship.Name + "', osztály " + RealShips[sti(chref.Ship.Type)].Class +
                     ", kikötési költség " + FindRussianMoneyString(sti(NPChar.MoneyForShip)) + " havonta, fizetés egy hónapra elôre.";
			Link.l1 = "Igen, ez megfelel nekem.";
			if (sti(Pchar.Money) >= sti(NPChar.MoneyForShip))
			{
			    Link.l1.go = "ShipStock_3";
			}
			else
			{
                Link.l1.go = "ShipStock_NoMoney";
			}
			Link.l2 = "Nem, meggondoltam magam.";
			Link.l2.go = "exit";*/
			chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
			PortmanCalculatePrices(NPChar, chref);
			dialog.Text = XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName) + " '" + chref.Ship.Name + "', osztály " + RealShips[sti(chref.Ship.Type)].Class +
										 ", kikötési díj " + FindRussianMoneyString(sti(NPChar.MoneyForShip)) + " havonta, előre fizetendő.";
			dialog.Text = dialog.Text + " Ha tiszttel és legénységgel hagyja itt, akkor velük együtt " + FindRussianMoneyString(sti(NPChar.MoneyForShip) + sti(NPChar.MoneyForCrew));

			Link.l1 = "Igen. Ez megfelel nekem.";
			if (sti(Pchar.Money) >= sti(NPChar.MoneyForShip)) Link.l1.go = "ShipStock_3";
			else  Link.l2.go = "ShipStock_NoMoney";

			Link.l2 = "Igen. Ez megfelel nekem. Hagyjuk a kapitánnyal és a legénységgel.";
			if (sti(Pchar.Money) >= (sti(NPChar.MoneyForShip) + sti(NPChar.MoneyForCrew))) Link.l2.go = "ShipStock_4";
			else Link.l2.go = "ShipStock_NoMoney";

			Link.l3 = "Nem, meggondoltam magam" + GetSexPhrase("","") + ".";
			Link.l3.go = "exit";
		break;

		case "ShipStock_NoMoney":
			dialog.text = "És nekem is megfelel, amint összegyûjti a szükséges összeget.";
			Link.l1 = "Hoppá... Majd késôbb visszajövök.";
			Link.l1.go = "exit";
		break;

		case "ShipStock_3":
		 	LeaveShipInPort(&NPChar, GetCharacter(sti(NPChar.ShipToStoreIdx)));
			dialog.text = "Rendben. Akkor veszi át, amikor szüksége lesz rá.";
			Link.l1 = "Köszönöm.";
			Link.l1.go = "exit";
		break;

		case "ShipStock_4":
		 	LeaveShipInPortWithCrew(&NPChar, GetCharacter(sti(NPChar.ShipToStoreIdx)));
			dialog.text = "Rendben. Akkor veszi át, amikor szüksége lesz rá.";
			Link.l1 = "Köszönöm.";
			Link.l1.go = "exit";
		break;

		case "ShipStockReturn_1":
            ok = (sFrom_sea == "") || (Pchar.location.from_sea == sFrom_sea);
		    if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
				if (GetCompanionQuantity(pchar) < COMPANION_MAX)
	            {
	                dialog.text = "Melyik hajót akarod elvinni?";
	                cn = 1;
	                for(i=1; i<MAX_CHARACTERS; i++)
					{
						makeref(chref, Characters[i]);
						if (CheckAttribute(chref, "ShipInStockMan"))
						{    
							if (chref.ShipInStockMan == NPChar.id)
							{
								attrL = "l"+cn;
								if(HasSubStr(chref.id, "ShipInStockMan_"))											  
								{ 
								Link.(attrL)	= XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName) + " '" + chref.Ship.Name + "'.";
								Link.(attrL).go = "ShipStockManBack22_" + i; 
								}
								else
								{  
								Link.(attrL)	= XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName) + " '" + chref.Ship.Name + "' és a tisztem " + GetFullName(chref) + ".";
								Link.(attrL).go = "ShipStockManBack11_" + i;
								}
								cn++;
							}
						}
					}
	
	    			Link.l99 = "Nem, meggondoltam magam.";
	    			Link.l99.go = "exit";
				}
				else
				{
	                dialog.text = "Van helyed egy másik hajónak?";
	    			Link.l1 = "Ó, igen, persze. Köszönöm. Köszönöm.";
	    			Link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "Hmm. Nem látom a zászlóshajóját a kikötôben. És csak itt viheti vissza a hajóit.";
    			Link.l1 = "Rendben, késôbb értük megyek.";
    			Link.l1.go = "exit";
			}
		break;

        case "ShipStockManBack":
            chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
			
			// Лимит офицеров не позволяет забрать  
			if (AttributeIsTrue(NPChar, "StoreWithOff") && FindFreeRandomOfficer() < 1 ) {  
				dialog.text = "Kapitány, úgy tűnik, nincs hely még egy tiszt számára a legénységben.";  
				link.l1 = "Hm... Akkor majd később visszajövök.";  
				link.l1.go = "exit";  
				break;  
			}

			// --> mitrokosta сюрприз для хитрецов поставивших бунтовщика в ПУ
			if (CheckAttribute(chref, "quest.Mutiny.date")) {
				dialog.text = "Lássuk csak... Ez a hajó a " + chref.quest.Mutiny.date + "kikötôbôl indult.";
				link.l1 = "Hogy érted 'left'? Itt kell lennie, a dokkokban!";
				link.l1.go = "ShipStockManMutiny";
				break;
			}
			// <--
            NPChar.MoneyForShip =  GetNpcQuestPastMonthParam(chref, "ShipInStockMan.Date") * sti(chref.ShipInStockMan.MoneyForShip);
			if (sti(NPChar.MoneyForShip) > 0)
			{
			    dialog.Text = "Fel akarod venni a hajódat? A kikötésért még mindig tartozik " + FindRussianMoneyString(sti(NPChar.MoneyForShip)) + ".";
			}
			else
			{
				dialog.Text = "Felvenni?";
			}
			if (sti(NPChar.MoneyForShip) <= sti(pchar.Money))
			{
				Link.l1 = "Igen.";
				Link.l1.go = "ShipStockManBack2";
			}
			Link.l2 = "Nem, meggondoltam magam.";
			Link.l2.go = "exit";
		break;
		
		case "ShipStockManBack2": // hasert новый кейс для сторожа.
			if (sti(NPChar.StoreWithOff))
			{   
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();

			AddMoneyToCharacter(Pchar, -sti(NPChar.MoneyForShip));
			chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
			DeleteAttribute(chref, "ShipInStockMan");
			if(CheckAttribute(chref, "DontNullShip"))
			{
				DeleteAttribute(chref, "DontNullShip");
				DeleteAttribute(NPChar, "DontNullShipBeliz");
			}
			SetCompanionIndex(pchar, -1, sti(NPChar.ShipToStoreIdx));

			NPChar.Portman	= sti(NPChar.Portman) - 1;
			pchar.ShipInStock = sti(pchar.ShipInStock) - 1;
			}
			else
			{   
			dialog.Text = "Melyik tisztednek adjam oda?";
			int _curCharIdx;
			int q = 0;
			int nListSize = GetPassengersQuantity(pchar);
			for(i=0; i<nListSize; i++)
				{
				_curCharIdx = GetPassenger(pchar,i);
				sld = GetCharacter(_curCharIdx);
					if (_curCharIdx!=-1)
					{
						ok = CheckAttribute(&characters[_curCharIdx], "prisoned") && sti(characters[_curCharIdx].prisoned) == true;

						if (!CheckAttribute(sld, "CompanionDisable"))
					    {
							if (!ok && GetRemovable(&characters[_curCharIdx]))
							{
								attrL = "l"+i;
								sProf = "";
								if (IsOfficer(sld)) sProf += " (vanguard)";
								if (sti(pchar.Fellows.Passengers.navigator) == sti(sld.index)) sProf += " (navigator)";
								if (sti(pchar.Fellows.Passengers.boatswain) == sti(sld.index)) sProf += " (boatswain)";
								if (sti(pchar.Fellows.Passengers.cannoner) == sti(sld.index)) sProf += " (cannoneer)";
								if (sti(pchar.Fellows.Passengers.doctor) == sti(sld.index)) sProf += " (surgeon)";
								if (sti(pchar.Fellows.Passengers.carpenter) == sti(sld.index)) sProf += " (carpenter)";
							    if (sti(pchar.Fellows.Passengers.treasurer) == sti(sld.index)) sProf += " (purser)";
								Link.(attrL)	= GetFullName(&characters[_curCharIdx]) + sProf;
								Link.(attrL).go = "ShipStockManBack2_" + i;
								q++;
							}
						}
					}
				}
			attrL = "l"+nListSize;
			if (q == 0)
				{
				Link.(attrL) = RandSwear() + "Elfelejtettem magammal hozni egy tisztet erre a hajóra.";
				Link.(attrL).go = "exit";
				}
			else
				{
				Link.(attrL) = "Nem, meggondoltam magam...";
				Link.(attrL).go = "exit";
				}
			}
		break;
		
		//--> Jason Голландский гамбит
		case "ShipStock_HWICHoll":
			if (GetCompanionQuantity(pchar) > 1)
			{
				dialog.text = "Igen, igen, tudom. De csak egy hajót vehetek fel az ingyenes kikötésért. Úgyhogy kérem, intézze el a dolgokat a századával, és aztán jöjjön vissza.";
				link.l1 = "Rendben, csak a zászlóshajót hozom.";
				link.l1.go = "exit";	
			}
			else
			{
				dialog.text = "Igen, igen, tudom. Rodenburg mynheer parancsára átvesszük a hajóját tárolásra, és biztosítunk egy ôrszolgálatot arra az idôre, amíg a hajója itt tartózkodik. Kérem, írja alá itt... és itt...";
				link.l1 = "Rendben... Ha jól értem, minden formalitást elintéztünk.";
				link.l1.go = "ShipStock_HWICHoll_1";	
			}
		break;
		
		case "ShipStock_HWICHoll_1":
			dialog.text = "Igen. Többé nem kell aggódnia a hajója miatt - mi majd vigyázunk rá. Visszatérhet a mynheer Rodenburgra.";
			link.l1 = "Köszönöm. Köszönöm. Viszontlátásra.";
			link.l1.go = "exit";	
			npchar.quest.HWICHoll = "done";
			pchar.Ship.Type = SHIP_NOTUSED;//все одно сгорит
			AddLandQuestMark(characterFromId("Lucas"), "questmarkmain");
			AddMapQuestMarkCity("Villemstad", true);
		break;
		
		case "ShipStock_HWICEng":
			if (GetCompanionQuantity(pchar) > 1)
			{
				dialog.text = "Igen, igen, tudom. De csak egy hajót vehetek fel az ingyenes kikötésért. Úgyhogy kérem, intézze el a dolgokat a századával, és aztán jöjjön vissza.";
				link.l1 = "Rendben, csak a zászlóshajót hozom.";
				link.l1.go = "exit";	
			}
			else
			{
				dialog.text = "Igen, természetesen. Van nálad pénz?";
				if(makeint(Pchar.money) >= 10000)
				{
					link.l1 = "Persze. Tessék.";
					link.l1.go = "ShipStock_HWICEng_1";	
				}
				else
				{
					link.l1 = "Nem. Mindjárt visszajövök.";
					link.l1.go = "exit";	
				}
			}
		break;
		
		case "ShipStock_HWICEng_1":
			dialog.text = "Jól van, rendben. Gondoskodunk a hajójáról és biztosítunk egy ôrszemet, amíg a hajója itt tartózkodik.";
			link.l1 = "Köszönjük!";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -10000);
			npchar.quest.HWICEng = "done";
			pchar.Ship.Type = SHIP_NOTUSED;//все одно сгорит
			DelLandQuestMark(npchar);
			AddLandQuestMark(characterFromId("Fleetwood"), "questmarkmain");
		break;
		//<-- Голландский гамбит
		case "Escort_companion":
			dialog.text = "Akart valamit, kapitány?";
			link.l1 = "Nem, semmit.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Escort_companion";
		break;
		
		// --> mitrokosta сюрприз для хитрецов поставивших бунтовщика в ПУ
		case "ShipStockManMutiny":
			chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
			DeleteAttribute(chref, "ShipInStockMan");
			NPChar.Portman    = sti(NPChar.Portman) - 1;
            pchar.ShipInStock = sti(pchar.ShipInStock) - 1;
			dialog.text = "Az ön tisztje " + GetFullName(chref) + " tájékoztatott" + NPCharSexPhrase(chref, "", "") + " engem, hogy " + NPCharSexPhrase(chref, "neki", "neki") + " az ön parancsára ki kellett mennie a tengerre. Nem tiltakoztam " + NPCharSexPhrase(chref, "neki", "neki") + ".";
			link.l1 = "Bassza meg! Nem volt ilyen parancs! Nem kellett volna rábíznom a hajómat erre a szemétládára! Eh, mindegy, úgysem tehetek semmit a veszteségem ellen.";
			link.l1.go = "ShipStockManMutiny1";
			// вот тут можно микроквестик сделать
			//link.l2 = "What a surprise... Did " + NPCharSexPhrase(chref, "he", "she") + " tell you, where they went, by any chance?";
			//link.l2.go = "ShipStockManMutiny2";
		break;
		
		case "ShipStockManMutiny1":
			chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
			chref.lifeday = 0;

			dialog.text = "Sajnálom, " + GetAddress_Form(NPChar) + ". Óvatosabbnak kellene lenned a beosztottjaiddal.";
			link.l1 = "Tudom, egy idióta vagyok. Viszlát, " + GetAddress_Form(NPChar) + ".";
			link.l1.go = "exit";
		break;
		// <--
		
		// уникальные корабли и легендарные капитаны -->
		case "UniqueShips":
			dialog.text = "Az egyedi hajók és a rájuk bízott személyek nem maradhatnak észrevétlenek a szigetvilágban. Ez az információ azonban jelentôs értéket képvisel, és nem adják könnyen.";
			if (sti(pchar.Money) >= 25000)
			{
				link.l1 = "Megértem. Elég lenne 25000 pezó, hogy bizonyítsam komoly szándékaimat?";
				link.l1.go = "UniqueShips_2";
			}
			else
			{
				link.l1 = "Rendben, akkor majd máskor.";
				link.l1.go = "node_2";
			}
		break;
		
		case "UniqueShips_2":
			dialog.text = "Valóban, ez elfogadható lenne. Melyik konkrét hajó érdekli?";
			if (GetDLCenabled(DLC_APPID_4) && !CheckAttribute(pchar, "questTemp.SantaMisericordia_InfoPU") && CharacterIsAlive("SantaMisericordia_cap"))
			{
				link.l1 = "Galleon 'Holy Mercy'.";
				link.l1.go = "UniqueShips_SantaMisericordia";
			}
			if (GetDLCenabled(DLC_APPID_5) && !CheckAttribute(pchar, "questTemp.LadyBeth_InfoPU") && CharacterIsAlive("LadyBeth_cap"))
			{
				link.l2 = "Havas ôrjárat 'Lady Beth'.";
				link.l2.go = "UniqueShips_LadyBeth";
			}
			if (GetDLCenabled(DLC_APPID_6) && !CheckAttribute(pchar, "questTemp.Memento_InfoPU") && CharacterIsAlive("Memento_cap"))
			{
				link.l3 = "Brig 'Memento'.";
				link.l3.go = "UniqueShips_Memento";
			}
			link.l99 = "Azt hiszem, eleget tudok.";
			link.l99.go = "node_2";
		break;
		
		case "UniqueShips_SantaMisericordia":
			AddMoneyToCharacter(pchar, -25000);
			AddQuestRecordInfo("LegendaryShips", "1");
			pchar.questTemp.SantaMisericordia_InfoPU = true;
			dialog.text = "Szent Irgalmasságot az Escorial küldte Európából, hogy felügyelje a spanyol gyarmatokat. Kapitánya, Don Alamida a spanyol korona híres szolgája, a korrupció és a bûnözés kíméletlen harcosa, a katolikus hit buzgó híve. A Holy Mercy a gyarmatok között hajózik, útját Havannában kezdi és fejezi be, és kizárólag a küldetésére összpontosít.\nAz Alamida minden kikötôben több napot, néha hosszabb idôt tölt. Azt mondják, ilyenkor még az utcán is lehet vele találkozni, de a helyiek nem különösebben vágynak az ilyen találkozásokra - a spanyolokban a senor csak félelmet és félelmet ébreszt.\nA Szent Irgalomnak tapasztalt és hûséges legénysége van, amelyet Alamida személyesen választ ki. Minden matróz kész az életével is megvédeni a hazáját és a kapitányt. Azt mondják, Don Fernando elrendelte, hogy a Holy Mercy-t soha nem szabad elfoglalni, és azt suttogják, hogy ha a legénységnek leküzdhetetlen esélyekkel kellene szembesülnie a fedélzetre lépéskor, akkor inkább a mélybe küldenék a hajót, minthogy lássák, ahogy a fedélzetre lépnek.";
			link.l1 = "Köszönjük szépen.";
			link.l1.go = "node_2";
		break;
		
		case "UniqueShips_LadyBeth":
			AddMoneyToCharacter(pchar, -25000);
			AddQuestRecordInfo("LegendaryShips", "2");
			pchar.questTemp.LadyBeth_InfoPU = true;
			dialog.text = "Lady Beth egy igazi szépség. Anglia tengeri géniuszának csodája, parancsnoka Albert Blackwood, a királyi haditengerészet egykori tisztje. Bizony, nem mindenkinek sikerül ilyen látványosan dezertálni! Otthagyta a szolgálatot, megölt egy fényes karriert, és ellopott egy hadihajót - mindezt kincsvadászatért!\nÉs nem hiába. Már annyit talált, hogy megvehette volna fél Barbadost, de még többet akar. Ha a tengeren találkozol vele - meg se próbáld meg feltartóztatni. Túl jó a hajó, a kapitány pedig tapasztalt és óvatos. Az utóbbi idôben Blackwood gyakran megfordult Kajmán-szigeteken - éjjel-nappal áskálódik, halálra dolgoztatja az embereket. Ha úgy döntesz, hogy utánanézel - vigyél magaddal nem kevesebb, mint hatvan embert és jó lôfegyvereket... Igazából még ez sem biztos, hogy elég lesz\nremélem, tudsz lôni, hiszen Fox ezredes egy századnyi egykori tengerészgyalogos gyalogos dezertált vele. Profik, semmi esetre sem olyanok, mint a közönséges gyilkosok. És soha ne támadjátok meg a francia kikötôkben - ott védelmet és pártfogókat kap, akik részesedést kapnak a leleteibôl.";
			link.l1 = "Köszönöm szépen.";
			link.l1.go = "node_2";
		break;
		
		case "UniqueShips_Memento":
			AddMoneyToCharacter(pchar, -25000);
			AddQuestRecordInfo("LegendaryShips", "3");
			pchar.questTemp.Memento_InfoPU = true;
			dialog.text = "A 'Memento' - egy igazi kalózlegenda. Egy fekete brigg, amelynek kapitánya Mortimer Grim.\n"+
			"Grim kizárólag rabszolgatartókra vadászik. Állítólag kiszabadítja a rabszolgákat, és kemény arannyal kivásárolja a halálraítélteket. Nemes ügy - ha a többit nem tudod.\n"+
			"Ha nem emberi rakományt szállítasz, Grim nem nyúl hozzád. Furcsa, de megvannak az elvei. De ha rabszolgákat tartasz a rakományodban... imádkozz, hogy ne láss fekete vitorlákat a horizonton.\n"+
			"A 'Memento' kalózparadicsomok között hajózik, de ritkán köt ki. A legénység hónapokig a fedélzeten él, mintha félne szilárd talajra lépni. A pletykák szerint a hajó egyszer túlélt egy szörnyû járványt - ezért olyan nehéz megölni a legénységet.\n"+
			"Ha azt tervezed, hogy felveszed velük a harcot, pakolj több ágyút. A 'Memento' fedélzetére lépni szinte lehetetlen - a legénység úgy harcol, mintha megszállottak lennének, mintha nem félnének a haláltól. Az egyetlen módja, hogy legyôzzük ôket, ha szilánkokra robbantjuk a hajót, és elvisszük a menedéküket. A szilánkok nem ijesztik meg ôket, de a közvetlen grapeshot-találatok - az már más kérdés.\n"+
			"Sok sikert. És ne feledjétek a halált.";
			link.l1 = "Köszönjük szépen.";
			link.l1.go = "node_2";
		break;
		
		// уникальные корабли и легендарные капитаны <--
	}
}

float BurntShipQuest_GetMaxNeededValue(int iShipType, string _param)
{
	float NeededValue = makefloat(GetBaseShipParamFromType(iShipType, _param));
	switch (_param)
	{
		case "speedrate":
			NeededValue += ((0.72 + frandSmall(0.30)) * (NeededValue/10.0)); 
		break;
		case "turnrate":
			NeededValue += ((0.72 + frandSmall(0.30)) * (NeededValue/10.0)); 
		break;
		case "capacity":
			NeededValue += ((0.72 + frandSmall(0.30)) * (NeededValue/8.0)); 
		break;
	}
	return NeededValue;
}

// Warship 25.07.09 Генер "A burnt vessel". Начальные иниты для портмана - тип разыскиваемого судна, выдающаяся характеристика и т.д.
void BurntShipQuest_FillStartParams(ref _npchar)
{
	int rank = sti(PChar.rank);
	int shipType, temp;
	float neededValue;
	String shipAttribute;
	
	// TODO Пересмотреть зависимость от ранга
	if(rank <= 5)
	{
		shipType = SHIP_LUGGER + rand(1);
		
		switch(shipType)
		{
			case SHIP_LUGGER:
				shipAttribute = "speedrate";
			break;
			
			case SHIP_SLOOP:
				temp = rand(2);
				
				if(temp == 2)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					if(temp == 1)
					{
						shipAttribute = "turnrate";
					}
					else
					{
						shipAttribute = "capacity";
					}
				}
			break;
		}
	}
	
	if(rank > 5 && rank <= 15)
	{
		shipType = SHIP_SCHOONER + rand(2);
		
		switch(shipType)
		{
			case SHIP_SCHOONER:
				if(rand(1) == 0)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					shipAttribute = "turnrate";
				}
			break;
			
			case SHIP_BARKENTINE:
				shipAttribute = "capacity";
			break;
			
			case SHIP_SHNYAVA:
				shipAttribute = "capacity";
			break;
		}
	}
	
	if(rank > 15 && rank <= 25)
	{
		shipType = SHIP_FLEUT + rand(3);
		
		switch(shipType)
		{
			case SHIP_FLEUT:
				shipAttribute = "turnrate";
			break;
			
			case SHIP_CARAVEL:
				if(rand(1) == 1)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					shipAttribute = "turnrate";
				}
			break;
			
			case SHIP_PINNACE:
				shipAttribute = "capacity";
			break;
			
			case SHIP_BRIGANTINE:
				if(rand(1) == 1)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					shipAttribute = "turnrate";
				}
			break;
			
		}
	}
	
	if(rank > 25 && rank <= 35)
	{
		shipType = SHIP_SCHOONER_W + rand(2);
		
		switch(shipType)
		{
			case SHIP_SCHOONER_W:
				if(rand(1) == 1)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					shipAttribute = "turnrate";
				}
			break;
			
			case SHIP_GALEON_L:
				shipAttribute = "capacity";
			break;
			
			case SHIP_CORVETTE:
				if(rand(1) == 1)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					shipAttribute = "capacity";
				}
			break;
		}
	}
	
	if(rank > 35)
	{
		shipType = SHIP_GALEON_H + rand(1);
		
		switch(shipType)
		{
			case SHIP_GALEON_H:
				temp = rand(2);
				
				if(temp == 0)
				{
					shipAttribute = "speedrate";
				}
				else
				{
					if(temp == 1)
					{
						shipAttribute = "turnrate";
					}
					else
					{
						shipAttribute = "capacity";
					}
				}
			break;
			
			case SHIP_FRIGATE:
				shipAttribute = "turnrate";
			break;
		}
	}
	
	neededValue = BurntShipQuest_GetMaxNeededValue(shipType, shipAttribute);
	
	Log_TestInfo("shipType == " + shipType);
	Log_TestInfo("ShipAttribute == " + shipAttribute);
	Log_TestInfo("ShipNeededValue == " + neededValue);
	
	_npchar.Quest.BurntShip.ShipType = shipType;
	_npchar.Quest.BurntShip.ShipAttribute = shipAttribute;
	
	if(shipAttribute != "capacity") // Чтобы трюм с десятичными не писался
	{
		_npchar.Quest.BurntShip.ShipNeededValue = FloatToString(neededValue, 2);
	}
	else
	{
		_npchar.Quest.BurntShip.ShipNeededValue = MakeInt(neededValue);
	}
}

void SetJornalCapParam(ref npchar)
{
	//созадем рассеянного кэпа
	ref sld = GetCharacter(NPC_GenerateCharacter("PortmansCap_" + npchar.index, "", "man", "man", 20, sti(npchar.nation), -1, true, "citizen"));
	SetShipToFantom(sld, "trade", true);
	sld.Ship.Mode = "trade";
	SetCaptanModelByEncType(sld, "trade");
	sld.dialog.filename = "Quest\ForAll_dialog.c";
	sld.dialog.currentnode = "PortmansCap";
	sld.DeckDialogNode = "PortmansCap_inDeck";
	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	DeleteAttribute(sld, "AboardToFinalDeck");
	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "DontRansackCaptain");
	sld.AlwaysSandbankManeuver = true;
	sld.AnalizeShips = true;  //анализировать вражеские корабли при выборе таска
	sld.DontRansackCaptain = true; //не сдаваться
	SetCharacterPerk(sld, "ShipTurnRateUp");
	SetCharacterPerk(sld, "ShipTurnRateUp");
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER_OWN);
	//в морскую группу кэпа
	string sGroup = "PorpmansShip_" + sld.index;
	Group_FindOrCreateGroup(sGroup);
	Group_SetType(sGroup,"trade");
	Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
	Group_LockTask(sGroup);
	Group_AddCharacter(sGroup, sld.id);
	Group_SetGroupCommander(sGroup, sld.id);
	SetRandGeraldSail(sld, sti(sld.Nation)); 
	//записываем данные в структуры портмана и кэпа
	npchar.quest = "PortmansJornal"; //личный флаг квеста для портмана
	npchar.quest.PortmansJornal.capName = GetFullName(sld); //имя кэпа
	npchar.quest.PortmansJornal.shipName = sld.Ship.name; //имя корабля
	npchar.quest.PortmansJornal.shipTapeName = RealShips[sti(sld.Ship.Type)].BaseName; //название корабля
	npchar.quest.PortmansJornal.city = SelectNotEnemyColony(npchar); //определим колонию, куда ушел кэп
	sld.quest = "InMap"; //личный флаг рассеянного кэпа
	sld.quest.targetCity = npchar.quest.PortmansJornal.city; //продублируем колонию-цель в структуру кэпа
	sld.quest.firstCity = npchar.city; //капитану знать откуда вышел в самом начале
	sld.quest.stepsQty = 1; //количество выходов в море
	sld.quest.money = ((sti(RealShips[sti(sld.Ship.Type)].basetype)+1) * 150) + (sti(pchar.rank)*150); //вознаграждение
	Log_TestInfo("The absent-minded cap " + sld.id + " went to: " + sld.quest.targetCity);
	//определим бухту, куда ставить энкаунтер. чтобы сразу не генерился перед ГГ у города
	string sTemp = GetArealByCityName(npchar.city);
	sld.quest.baseShore = GetIslandRandomShoreId(sTemp);
	//на карту
	sld.mapEnc.type = "trade";
	sld.mapEnc.worldMapShip = "ranger";
	sld.mapEnc.Name = XI_ConvertString(npchar.quest.PortmansJornal.shipTapeName) + " '" + npchar.quest.PortmansJornal.shipName + "'";
	int daysQty = GetMaxDaysFromIsland2Island(sTemp, GetArealByCityName(sld.quest.targetCity))+5; //дней доехать даем с запасом
	Map_CreateTrader(sld.quest.baseShore, sld.quest.targetCity, sld.id, daysQty);
	//заносим Id кэпа в базу нпс-кэпов
	sTemp = sld.id;
	NullCharacter.capitainBase.(sTemp).quest = "jornal"; //идентификатор квеста
	NullCharacter.capitainBase.(sTemp).questGiver = "none"; //запомним Id квестодателя для затирки в случае чего
	NullCharacter.capitainBase.(sTemp).Tilte1 = npchar.id + "PortmansBook_Delivery"; //заголовок квестбука
	NullCharacter.capitainBase.(sTemp).Tilte2 = "PortmansBook_Delivery"; //имя квеста в квестбуке
	NullCharacter.capitainBase.(sTemp).checkTime = daysQty + 5;
    NullCharacter.capitainBase.(sTemp).checkTime.control_day = GetDataDay();
    NullCharacter.capitainBase.(sTemp).checkTime.control_month = GetDataMonth();
    NullCharacter.capitainBase.(sTemp).checkTime.control_year = GetDataYear();
}
//проверить список отметившихся квестовых кэпов
int CheckCapitainsList(ref npchar)
{
	int bResult = 0;
	if (!CheckAttribute(npchar, "quest.capitainsList")) return bResult;
	aref arCapBase, arCapLocal;
    makearef(arCapBase, npchar.quest.capitainsList);
    int	Qty = GetAttributesNum(arCapBase);
	if (Qty < 1) return bResult;
	string sCapitainId; 
	for (int i=0; i<Qty; i++)
    {
    	arCapLocal = GetAttributeN(arCapBase, i);
        sCapitainId = GetAttributeName(arCapLocal);
    	if (GetCharacterIndex(sCapitainId) > 0) //если ещё жив
    	{
			bResult++;			
    	}
		else
		{
			DeleteAttribute(arCapBase, sCapitainId);
			i--;
			Qty--;
		}
    }
	if (bResult > 5) bResult = 5;
	return bResult;
}

void SetSeekShipCapParam(ref npchar)
{
	//создаем кэпа-вора
	int Rank = sti(pchar.rank) + 5;
	if (Rank > 30) Rank = 30;
	ref sld = GetCharacter(NPC_GenerateCharacter("SeekCap_" + npchar.index, "", "man", "man", Rank, PIRATE, -1, true, "soldier"));
	SetSeekCapShip(sld);
	sld.Ship.Mode = "pirate";
	SetCaptanModelByEncType(sld, "pirate");
	sld.dialog.filename = "Quest\ForAll_dialog.c";
	sld.dialog.currentnode = "SeekCap";
	sld.DeckDialogNode = "SeekCap_inDeck";
	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	DeleteAttribute(sld, "AboardToFinalDeck");
	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "DontRansackCaptain");
	sld.AlwaysSandbankManeuver = true;
	sld.AnalizeShips = true;  //анализировать вражеские корабли при выборе таска
	sld.DontRansackCaptain = true; //не сдаваться
	SetCharacterPerk(sld, "FastReload");
	SetCharacterPerk(sld, "HullDamageUp");
	SetCharacterPerk(sld, "SailsDamageUp");
	SetCharacterPerk(sld, "CrewDamageUp");
	SetCharacterPerk(sld, "CriticalShoot");
	SetCharacterPerk(sld, "LongRangeShoot");
	SetCharacterPerk(sld, "CannonProfessional");
	SetCharacterPerk(sld, "ShipDefenseProfessional");
	SetCharacterPerk(sld, "ShipTurnRateUp");
	SetCharacterPerk(sld, "ShipTurnRateUp");


	SetCharacterPerk(sld, "AdvancedDefense");
	SetCharacterPerk(sld, "CriticalHit");
	SetCharacterPerk(sld, "Sliding");
	SetCharacterPerk(sld, "Tireless");
	SetCharacterPerk(sld, "HardHitter");
	SetCharacterPerk(sld, "GunProfessional");
	//в морскую группу кэпа
	string sGroup = "SeekCapShip_" + sld.index;
	Group_FindOrCreateGroup(sGroup);
	Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
	Group_LockTask(sGroup);
	Group_AddCharacter(sGroup, sld.id);
	Group_SetGroupCommander(sGroup, sld.id);
	SetRandGeraldSail(sld, sti(sld.Nation)); 
	//записываем данные в структуры портмана и кэпа
	npchar.quest = "PortmansSeekShip"; //личный флаг квеста для портмана
	npchar.quest.PortmansSeekShip.capName = GetFullName(sld); //имя кэпа-вора
	npchar.quest.PortmansSeekShip.shipName = sld.Ship.name; //имя украденного корабля
	npchar.quest.PortmansSeekShip.shipTapeName = RealShips[sti(sld.Ship.Type)].BaseName; //название украденного корабля
	npchar.quest.PortmansSeekShip.shipTape = RealShips[sti(sld.Ship.Type)].basetype; //тип украденного корабля
	npchar.quest.money = ((sti(RealShips[sti(sld.Ship.Type)].basetype)+1) * 10) + (sti(pchar.rank)*5); //вознаграждение
	// npchar.quest.chest = 12-sti(RealShips[sti(sld.Ship.Type)].Class); //в сундуках
	sld.quest = "InMap"; //личный флаг кэпа-вора
	sld.city = SelectAnyColony(npchar.city); //определим колонию, откуда кэп-вор выйдет
	sld.quest.targetCity = SelectAnyColony2(npchar.city, sld.city); //определим колонию, куда он придёт
	//Log_TestInfo("Thieving cap " + sld.id + " sailed out of: " + sld.city + " and went to: " + sld.quest.targetCity);
	sld.quest.cribCity = npchar.city; //город, откуда кэп-вор спер корабль
	//на карту
	sld.mapEnc.type = "trade";
	sld.mapEnc.worldMapShip = "Galleon_red";
	sld.mapEnc.Name = XI_ConvertString(npchar.quest.PortmansSeekShip.shipTapeName) + " '" + npchar.quest.PortmansSeekShip.shipName + "'";
	int daysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(sld.quest.targetCity), GetArealByCityName(sld.city))+3; //дней доехать даем с запасом
	Map_CreateTrader(sld.city, sld.quest.targetCity, sld.id, daysQty);
	//прерывание на абордаж
	string sTemp = "SeekShip_checkAbordage" + npchar.index;
	pchar.quest.(sTemp).win_condition.l1 = "Character_Capture";
	pchar.quest.(sTemp).win_condition.l1.character = sld.id;
	pchar.quest.(sTemp).function = "SeekShip_checkAbordage";
	pchar.quest.(sTemp).CapId = sld.id;
	//прерывание на потопление без абордажа
	sTemp = "SeekShip_checkSink" + npchar.index;
	pchar.quest.(sTemp).win_condition.l1 = "Character_sink";
	pchar.quest.(sTemp).win_condition.l1.character = sld.id;
	pchar.quest.(sTemp).function = "SeekShip_checkSink";
	pchar.quest.(sTemp).CapId = sld.id;
	//заносим Id кэпа в базу нпс-кэпов
	sTemp = sld.id;
	NullCharacter.capitainBase.(sTemp).quest = "robber"; //идентификатор квеста
	NullCharacter.capitainBase.(sTemp).questGiver = "none"; //запомним Id квестодателя для затирки в случае чего
	NullCharacter.capitainBase.(sTemp).Tilte1 = npchar.id + "Portmans_SeekShip"; //заголовок квестбука
	NullCharacter.capitainBase.(sTemp).Tilte2 = "Portmans_SeekShip"; //имя квеста в квестбуке
	NullCharacter.capitainBase.(sTemp).checkTime = daysQty + 5;
    NullCharacter.capitainBase.(sTemp).checkTime.control_day = GetDataDay();
    NullCharacter.capitainBase.(sTemp).checkTime.control_month = GetDataMonth();
    NullCharacter.capitainBase.(sTemp).checkTime.control_year = GetDataYear();
}

string GenQuestPortman_GenerateGem() // камни
{
	string itemID;
	switch(rand(5))
	{
		case 0:
			itemID = "jewelry1";	
		break;
		case 1:
			itemID = "jewelry2"; 
		break;
		case 2:
			itemID = "jewelry3"; 
		break;
		case 3:
			itemID = "jewelry3"; 
		break;
		case 4:
			itemID = "jewelry5"; 
		break;
		case 5:
			itemID = "jewelry6"; 
		break;
	}
	return itemID;
}

// --> Jason, новые мини-квесты
string findCurrentCity1(ref NPChar)//выбираем целевой город 1
{
	int n, nation;
    int storeArray[2];
	SetArraySize(&storeArray, MAX_COLONIES);
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		nation = GetNationRelation(sti(pchar.nation), sti(colonies[n].nation));
		if (nation != RELATION_ENEMY && colonies[n].id != "Panama" && colonies[n].id != "LosTeques" && colonies[n].id != "SanAndres" && colonies[n].nation != "none" && GetIslandByCityName(npchar.city) != colonies[n].islandLable) //на свой остров
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	if (howStore == 0) return "none";
	nation = storeArray[hrand(howStore-1)];
	return colonies[nation].id;
}

string findCurrentCity2(ref NPChar)//выбираем целевой город 2
{
	int n, nation;
    int storeArray[2];
	SetArraySize(&storeArray, MAX_COLONIES);
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		nation = GetNationRelation(sti(pchar.nation), sti(colonies[n].nation));
		if (nation != RELATION_ENEMY && colonies[n].id != "Panama" && colonies[n].id != "LosTeques" && colonies[n].id != "SanAndres" && colonies[n].nation != "none" && GetIslandByCityName(npchar.city) != colonies[n].islandLable) //на свой остров
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	if (howStore == 0) return "none";
	nation = storeArray[abs(hrand(howStore-1)-3)];
	return colonies[nation].id;
}

string findCurrentCity3(ref NPChar)//выбираем целевой город 3
{
	int n, nation;
    int storeArray[2];
	SetArraySize(&storeArray, MAX_COLONIES);
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		nation = GetNationRelation(sti(pchar.nation), sti(colonies[n].nation));
		if (nation != RELATION_ENEMY && colonies[n].id != "Panama" && colonies[n].id != "LosTeques" && colonies[n].id != "SanAndres" && colonies[n].nation != "none" && GetIslandByCityName(npchar.city) != colonies[n].islandLable) //на свой остров
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	if (howStore == 0) return "none";
	nation = storeArray[abs(hrand(howStore-1)-7)];
	return colonies[nation].id;
}

int Escort_ShipType()
{
	int iShipType;
	switch (rand(2))
	{
		case 0: iShipType = SHIP_FLEUT; 	break;
		case 1: iShipType = SHIP_GALEON_L; 	break;
		case 2: iShipType = SHIP_PINNACE;	break;
	}
	return iShipType;
}
//<-- новые мини-квесты



void SetSeekCapShip(ref _chr)
{
	int iRank;
	if (sti(pchar.rank) < 7) iRank = 0;
	if (sti(pchar.rank) >= 7 && sti(pchar.rank) < 11) iRank = 1;
	if (sti(pchar.rank) >= 11 && sti(pchar.rank) < 20) iRank = 2;
	if (sti(pchar.rank) >= 20 && sti(pchar.rank) < 27) iRank = 3;
	if (sti(pchar.rank) >= 27) iRank = 4;
	
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
		case 4:  
			iShip = sti(RandPhraseSimple(its(GetRandomShipType(FLAG_SHIP_CLASS_3, FLAG_SHIP_TYPE_WAR + FLAG_SHIP_TYPE_RAIDER, FLAG_SHIP_NATION_ANY)), 
										 its(GetRandomShipType(FLAG_SHIP_CLASS_2, FLAG_SHIP_TYPE_ANY, FLAG_SHIP_NATION_ANY))));
		break;
	}
	
	_chr.Ship.Type = GenerateShipExt(iShip, true, _chr);
	SetRandomNameToShip(_chr);
    SetBaseShipData(_chr);
    SetCrewQuantityFull(_chr);
    Fantom_SetCannons(_chr, "pirate");
    Fantom_SetBalls(_chr, "pirate");
	Fantom_SetUpgrade(_chr, "pirate");
	Fantom_SetGoods(_chr, "pirate");
}
