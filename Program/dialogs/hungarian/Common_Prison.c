// городские тюрьмы
void ProcessDialogEvent()
{
	int amount, iGunQty, iGunGoods, iGunPrice, iTemp;
	int iTest;
	ref NPChar, sld, location;
	ref arItem;
	ref rColony;
	aref Link, NextDiag;
	string sTemp;
	float locx, locy, locz;
	bool  ok;
	// belamour для ночного приключения -->
	int i;
	int SoldQty = 0;
	int SoldNum[10];
	// <--

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Prison\" + NPChar.City + "_Prison.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--

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
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "NoMoreTalkExit":
			LAi_CharacterDisableDialog(npchar);
			DialogExit();
		break;
		//---------------- Начальник тюрьмы ------------------
		case "First_officer":
			dialog.text = RandPhraseSimple("Én vagyok a börtönigazgató. Mire van itt szüksége?", "Mire van szüksége? Miért jött a börtönbe?");
			NextDiag.TempNode = "First_officer";
			if(startHeroType == 4 && NPChar.location == "SantaCatalina_prison" && !CheckAttribute(pchar, "questTemp.HelenSCprison"))
			{
				dialog.text = "Miss MacArthur? Meglep, hogy látom. Amennyire tudom, nem tartóztattunk le senkit sem az ön, sem Swenson kapitány legénységébôl.";
				link.l1 = "Én csak itt vagyok, uram. Ez nem megengedett? Nem beszélgettem a foglyokkal a háta mögött.";
				link.l1.go = "Helen_meeting";
				pchar.questTemp.HelenSCprison = true;
				break;
			}
			// --> Sinistra Длинные тени старых грехов
			if(CheckAttribute(pchar,"questTemp.DTSG_AntiguaTrevoga") && npchar.city == "SentJons")
			{
				dialog.text = "Charles de Maure... Le kellene tartóztatnunk, és a tisztjével együtt, de... a bankban történt incidens sajnálatos félreértésnek minôsült.";
				link.l1 = "Tetszik, ahogyan ezt a beszélgetést elkezdte, Mr. "+GetFullName(NPChar)+". Mindent meg tudok magyarázni.";
				link.l1.go = "DTSG_AntiguaTrevoga_2";
				break;
			}
			// <-- Длинные тени старых грехов
			
			//--> Бремя гасконца
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "jailskiper")
			{
				link.l1 = "Biztos úr, úgy hallottam, hogy van egy Folke Deluc nevû férfi a börtönében. Tehetek valamit, hogy kiszabadítsam?";
                link.l1.go = "Sharlie";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "freeskiper")
			{
				link.l1 = "Biztos úr, ismét én vagyok az, Folke Deluc fogolyról van szó. Megvásároltam az adósságát, és azt akarom, hogy engedjék szabadon és adják át nekem. Itt vannak az adósságpapírjai, nézze meg.";
                link.l1.go = "Sharlie_3";
				break;
			}	
			//<-- Бремя гасконца
			
			//belamour legendary edition диалоги, если герой имеет звания и заслуги перед отечеством -->
			// Офицер с патентом
			if(IsOfficerFullEquip())
			{
				dialog.text = "Üdvözlöm, kapitány. Mi szél hozta ide?";
			}
			// вице-адмирал
			if(isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation))
			{
				dialog.text = "Üdvözlöm, admirális-helyettes! Miben segíthetek?";
			}
			// генерал-губернатор
			if(CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE)
			{
				dialog.text = "Ôexcellenciája, fôkormányzó úr! Van valami parancsa?";
			}
			// <-- legendary edition
			link.l1 = "Ó, semmi különös, tudja, csak körülnéztem a városban, ezért bolyongtam ide alkalomadtán.";
			link.l1.go = "exit";
			link.l2 = "Egy kis üzletrôl akartam beszélni.";
			if (CheckCharacterItem(pchar, "CaptainBook") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakFort"))
			{
				if((pchar.questTemp.different.GiveShipLetters.city == npchar.city) && CheckAttribute(pchar, "questTemp.different.GiveShipLetters"))
				{
					link.l2.go = "F_ShipLetters_1";
				}
				else
				{
					link.l2.go = "quests";
				}		
			}
			else
			{
				if(CheckAttribute(pchar,"questTemp.ReasonToFast") && !CheckAttribute(pchar,"questTemp.ReasonToFast.SpeakOther") && !CheckAttribute(pchar, "questTemp.ReasonToFast.cantSpeakOther") && (pchar.questTemp.ReasonToFast.city == NPChar.city))
				{
					link.l2.go = "ReasonToFast_Prison1";
				}
				else
				{
					link.l2.go = "quests";
				}	
			}
			if (!sti(pchar.questTemp.jailCanMove))
			{
				link.l4 = "Szeretnék bejönni a börtönbe.";
				link.l4.go = "ForGoodMove";		
			}
			if (CheckAttribute(pchar, "questTemp.jailCanMove.City") && npchar.city == pchar.questTemp.jailCanMove.City)
			{
				link.l5 = "Hé, meg tudnád mondani, hogy a " + GetFullName(characterFromId(pchar.questTemp.jailCanMove.prisonerId)) + "nevû elítélt milyen bûncselekményért ül?";
				link.l5.go = "KnowAboutPrisoner";	
			}
			
			if(CheckAttribute(pchar,"GenQuest.CaptainComission") && (pchar.GenQuest.CaptainComission.variant == "A2") && (pchar.GenQuest.CaptainComission.City == NPChar.city))
			{
				if(!CheckAttribute(pchar,"GenQuest.CaptainComission.PrisonFree"))
				{
					bool zMsm = (CheckAttribute(pchar,"GenQuest.CaptainComission.GetRumour")) && (!CheckAttribute(pchar,"GenQuest.CaptainComission.SpeakMayor"));
					if(pchar.GenQuest.CaptainComission == "MayorTalkBad" || zMsm) //говорил с губером и отказался или узнал слухи, но не говорил с губером
					{
						link.l6 = "Úgy hallottam, hogy a volt járôrkapitány " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"név") + "Acc")) + " " + pchar.GenQuest.CaptainComission.Name + " itt van ôrizetben. Beszélhetek vele?";
						link.l6.go = "CapComission_PrisonBad1";
					}
					if(pchar.GenQuest.CaptainComission == "MayorTalkGood")
					{
						link.l6 = "Én " + GetFullName(pchar) + ", a kormányzó nevében és parancsára " + XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen") + "kell beszélnem a volt kapitánnyal " + pchar.GenQuest.CaptainComission.Name + ".";
						link.l6.go = "CapComission_PrisonGood1";
					}
				}	
			}
			if(CheckAttribute(pchar,"GenQuest.EncGirl"))
			{
				if(pchar.GenQuest.EncGirl == "toParents" || pchar.GenQuest.EncGirl == "FindLover")
				{
					if(pchar.GenQuest.EncGirl.Father == "fort_keeper"  && npchar.city == pchar.GenQuest.EncGirl.city)
					{
						link.l9 = "A lányáról van szó...";
						link.l9.go = "EncGirl_1";
					}
				}
			}
			
			if (CheckAttribute(pchar, "GenQuest.Marginpassenger") && pchar.GenQuest.Marginpassenger == "begin" && NPChar.location == pchar.GenQuest.Marginpassenger.City + "_prison")
			{
				link.l12 = "Dolgom van önnel, tiszt úr. Úgy vélem, hogy érdekelni fogja, mivel a feladataihoz kapcsolódik.";
				link.l12.go = "Marginpassenger";
			}
			
			// Warship, 16.05.11. Генер "Justice for sale".
			if(CheckAttribute(PChar, "GenQuest.JusticeOnSale.PrisonWait") && CheckAttribute(PChar, "GenQuest.JusticeOnSale.CityId") && NPChar.location == PChar.GenQuest.JusticeOnSale.CityId + "_prison")
			{
				link.l13 = "Egy bizonyos emberrôl szeretnék beszélni - " + PChar.GenQuest.JusticeOnSale.SmugglerName + ". Ô az ön foglya, ha nem tévedek.";
				link.l13.go = "JusticeOnSale_1";
			}
			
			// --> belamour ночной приключенец
			if(CheckAttribute(pchar,"GenQuest.NightAdventureToJail"))
			{
				link.l14 = "Üdvözlöm, biztos úr. Amennyire én tudom, nemrég egy részeg polgárt vettek ôrizetbe, miután megpróbált összeverekedni egy ôrrel az utcán."; 
				link.l14.go = "NightAdventure_CitizenHomie";
			}
			
			if(CheckAttribute(pchar,"GenQuest.NightAdventureToPrisoner"))
			{
				link.l14 = "Biztos úr, beszéltem az ôrrel, és ô visszavonta az állításait. Itt van egy utalvány tôle."; 
				link.l14.go = "NightAdventure_HomieToPrisoner";
			}
			// <-- приключенец
			NextDiag.TempNode = "First_officer";
		break;
		
		// --> Jason Похититель
		case "Marginpassenger":
			dialog.text = "Igen? Mi az, amit hajlandó elmondani nekem?";
			link.l1 = "Nemrégiben megállított az utcán egy "+pchar.GenQuest.Marginpassenger.Name+" , aki felajánlotta, hogy szervezzek meg egy piszkos ügyet: egy "+pchar.GenQuest.Marginpassenger.q1Name+"nevû személy elfogását, majd váltságdíj kiváltását. Ez "+pchar.GenQuest.Marginpassenger.Text+"...";
			link.l1.go = "Marginpassenger_1";
		break;
		
		case "Marginpassenger_1":
			dialog.text = "Hmm... Ez nagyon érdekes - folytassa, kérem!";
			link.l1 = "Tudta a hajó nevét, amelyen "+pchar.GenQuest.Marginpassenger.q1Name+" tervezte, hogy elhajózik. Ez a "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Marginpassenger.ShipType), "név")))+" neve '"+pchar.GenQuest.Marginpassenger.ShipName+"'. Azt is megmondta, hogy mikor indulhatott volna el az a hajó.";
			link.l1.go = "Marginpassenger_2";
		break;
	
		case "Marginpassenger_2":
			dialog.text = "És azt javasolta, hogy fogd el az utast, majd követelj érte váltságdíjat?";
			link.l1 = "Pontosan. A váltságdíjért a "+XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Targetcity)+", egy bizonyos "+pchar.GenQuest.Marginpassenger.q2Name+"nevû személyhez fordulnék. Fizettem neki ezért az információért, de természetesen nem akartam elrabolni azt a személyt.";
			link.l1.go = "Marginpassenger_3";
		break;
		
		case "Marginpassenger_3":
			dialog.text = "Ezért úgy döntöttél, hogy meglátogatsz, és elmondod nekem?";
			link.l1 = "Pontosan. Biztos vagyok benne, hogy annak a gazembernek a tettei veszélyeztetik a városod polgárait, és remélem, hogy megfelelô intézkedéseket fogsz tenni.";
			link.l1.go = "Marginpassenger_4";
		break;
		
		case "Marginpassenger_4":
			dialog.text = "Teljesen igazad volt, amikor hozzám fordultál, "+GetAddress_Form(NPChar)+"! Ez a gazember, "+pchar.GenQuest.Marginpassenger.Name+", már régóta a nyomunkban van. Nyomozni fogok, és ha minden, amit mondtál, beigazolódik, akkor fél évre rács mögé dugjuk ezt a szemetet. Ez majd megtanítja, hogy ne szôjön ilyen cselszövéseket a tisztelt polgárok ellen!\nNos, az ön ôszinteségéért és a jó ügy szolgálatára való hajlandóságáért természetesen jelenteni fogom a tettét a kormányzónak, ami természetesen hatással lesz az önhöz való hozzáállására... tudja, pozitív értelemben. Köszönöm a segítségét, kapitány!";
			link.l1 = "Hmm... Szívesen, örömmel segítettem. Viszontlátásra!";
			link.l1.go = "Marginpassenger_5";
		break;
		
		case "Marginpassenger_5":
			DialogExit();
			NextDiag.CurrentNode = "First_officer";
			AddQuestRecord("Marginpassenger", "20");
			AddQuestUserData("Marginpassenger", "sName", pchar.GenQuest.Marginpassenger.Name);
			CloseQuestHeader("Marginpassenger");
			pchar.quest.Marginpassenger_InWorld.over = "yes"; //снять таймер
			DeleteAttribute(Pchar, "GenQuest.Marginpassenger");
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 5);
			AddCharacterExpToSkill(pchar, "Leadership", 100);//авторитет
			ChangeContrabandRelation(pchar, -25);
			if (GetCharacterIndex("MarginCap") != -1)
			{
				sld = characterFromId("MarginCap");
				sld.lifeday = 0;
				Map_ReleaseQuestEncounter(sld.id);
				Group_DeleteGroup("Sea_MarginCap1");
			}
		break;
		//<-- Похититель

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
			dialog.text = "Mit tudsz te? Vannak saját gyermekei? Nincsenek? Ha lesz egy, jöjjön el hozzám, és beszélgetünk.\njutalmat ígértem annak, aki visszaviszi a családjához.";
			link.l1 = "Köszönöm. Köszönöm. Tartsd rajta a szemed. Van egy olyan érzésem, hogy nem fog leállni.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("EncGirl_ToLoverParentsExit");
		break;
		
		// ------------------------- Повод для спешки -----------------------------
		case "ReasonToFast_Prison1":
			pchar.questTemp.ReasonToFast.SpeakOther = true;
			dialog.text = "Csupa fül vagyok, kapitány.";
			link.l1 = "Egy bûnös összejátszásról szeretnék beszámolni önöknek, amely a helyôrségük egyik tisztje és a kalózok között (magyarázza az ügyet).";
			if(makeint(pchar.reputation.nobility) < 41)
			{
				link.l1.go = "ReasonToFast_Prison_BadRep";			
			}
			else
			{
				link.l1.go = "ReasonToFast_Prison_GoodRep";	
			}
		break;
		case "ReasonToFast_Prison_GoodRep":
			if(pchar.questTemp.ReasonToFast == "PatrolSuccess_1") 
			{ 
				// вилка_А
				dialog.text = "Köszönöm,"+ GetSexPhrase("mister","miss") +"! Azonnal kiadom a parancsot a gazember letartóztatására.\nMindamellett, hogy önnek költségei keletkeztek, és az önkormányzat pénztára sajnos üres...";
				link.l1 = "Uram! Nem a pénzért tettem...";
				link.l1.go = "ReasonToFast_Prison_GoodRep_11";
				
				if(pchar.questTemp.ReasonToFast.chain == "A0") ReasonToFast_RemoveVictim();
				if(pchar.questTemp.ReasonToFast.chain == "A1") pchar.quest.ReasonToFast_ClearLakey.over = "yes";
			}
			if(pchar.questTemp.ReasonToFast == "PatrolSuccess_2") 
			{ 
				// получена карта
				dialog.text = "Köszönöm, "+ GetSexPhrase("mister","miss") +"! Azonnal kiadom a parancsot a gazember letartóztatására.\nGondoljon bele! Személyi fegyverrel akartuk jutalmazni a kiváló szolgálatért. Milyen jó, hogy minden tisztázódott, és nincs mit szégyellnem!";
				link.l1 = "Mindig örömmel szolgálom az igazságot.";
				link.l1.go = "ReasonToFast_Prison_GoodRep_21";			
			}
			if(pchar.questTemp.ReasonToFast == "PatrolDied") 
			{ 
				// патруль перебит
				dialog.text = "Mi"+ GetSexPhrase("ster","ss") +"! Már jó ideje gyanúsítottuk azt a tisztet és a söpredékét piszkos ügyekben, de úgy gondolom, hogy elhamarkodottan cselekedett, amikor tanúk nélkül bánt el velük.";
				link.l1 = "Uram! De meg kellett védenem magam...";
				link.l1.go = "ReasonToFast_Prison_GoodRep_31";	
				pchar.questTemp.ReasonToFast.speakAfterPatrolDied = true;	
				pchar.quest.ReasonToFast_SpeakMayor.over = "yes";	
			}
		break;
		
		case "ReasonToFast_Prison_BadRep":
			if(pchar.questTemp.ReasonToFast == "PatrolSuccess_1") 
			{ 
				// вилка_А
				dialog.text = "Kapitány, felfogta, hogy mit tett?! Már több mint egy hónapja próbáljuk felállítani ezt a csapdát! És most, csak a maga szórakoztatására, tönkretette az ôrjáratunk találkozóját a hírnökkel " + GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_GEN) + " és most idejön dicsekedni?! Talán most már meg tudod mondani, hogyan kellene megmagyaráznom ennek az akciónak a költségeit és kiadásait?!";
				link.l1 = "Felség! Csak nem akarja megérteni a lényeget...";
				link.l1.go = "ReasonToFast_Prison_BadRep1";
				pchar.questTemp.ReasonToFast = "speakSuccess_chain_A";
				
				if(pchar.questTemp.ReasonToFast.chain == "A0") ReasonToFast_RemoveVictim();
				if(pchar.questTemp.ReasonToFast.chain == "A1") pchar.quest.ReasonToFast_ClearLakey.over = "yes";
			}
			if(pchar.questTemp.ReasonToFast == "PatrolSuccess_2") 
			{ 
				// получена карта
				dialog.text = "Hadd nézzem meg ezt a térképet...\nSmindenki viccel? Ez a szakadt pergamendarab egy bizonyíték?";
				link.l1 = "Felség! Csak nem akarja megérteni a lényeget...";
				link.l1.go = "ReasonToFast_Prison_BadRep1";
				TakeItemFromCharacter(pchar, "mapQuest");	
				pchar.questTemp.ReasonToFast = "speakSuccess_chain_B";	
			}
			if(pchar.questTemp.ReasonToFast == "PatrolDied") 
			{ 
				// патруль перебит
				dialog.text = "Na, ez aztán az eredeti indoklás az egész ôrjáratozó csoport megsemmisítésére. Nos, legalább azzal, hogy idejöttél, megkíméltél minket attól, hogy megkeressük a gyilkost.";
				link.l1 = "Felség! Csak nem akarja megérteni a lényeget...";
				link.l1.go = "ReasonToFast_Prison_BadRep1";			
				pchar.questTemp.ReasonToFast = "speakSuccess_chain_A";
				pchar.quest.ReasonToFast_SpeakMayor.over = "yes";
			}		
		break;
		
		case "ReasonToFast_Prison_GoodRep_11":
			dialog.text = "Ennek ellenére úgy gondolom, hogy az erôfeszítéseidet még mindig meg kellene jutalmazni. Tessék, fogd ezt a térképet; egy kalóz holmijában találtuk, aki nemrég került az akasztófára. Ha Isten is úgy akarja, talán tényleg megtaláljátok azt a kincset, bár ezt elég valószínûtlennek tartom...";
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
		case "ReasonToFast_Prison_GoodRep_21":
			dialog.text = "Dicséretes a buzgalmad. Kérlek, fogadd el ezt a pengét jutalmul - ez a legkevesebb, amit tehetek érted. Ó, és ezt a térképet megtarthatod magadnak. Biztos vagyok benne, hogy sok ilyen hamisítvány van a szigetvilágban.";
			link.l1 = "Köszönöm, ez nagyon nagylelkû tôled!";
			link.l1.go = "exit";
			AddQuestRecord("ReasonToFast", "14");
			ChangeCharacterComplexReputation(pchar,"nobility", 1); 
			GiveItem2Character(pchar, pchar.questTemp.ReasonToFast.p6);
			pchar.questTemp.ReasonToFast.state = "chain_B"; // была получена карта
			pchar.questTemp.ReasonToFast = "GetMap";			
			ReasonToFast_SetHunterCoastal();
		break;
		case "ReasonToFast_Prison_GoodRep_31":
			dialog.text = "Lehet, lehet, lehet... Nos, mondjuk úgy, hogy ezt az üzletet az isteni igazságszolgáltatás és a mi Urunk akarata döntötte el.";
			link.l1 = "Köszönöm, ez nagyon nagylelkû tôled!";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar,"nobility", 1); 
			AddQuestRecord("ReasonToFast", "16");
			CloseQuestHeader("ReasonToFast");
			DeleteAttribute(pchar,"ReasonToFast");			
		break;
		
		case "ReasonToFast_Prison_BadRep1":
			dialog.text = "Ne merészelj kioktatni! Számomra nyilvánvaló, hogy együttmûködsz ezekkel a gazemberekkel! Guards, seize this 'well-wisher'!";
			link.l1 = "Nem lehet!";
			link.l1.go = "fight";
			
			pchar.quest.ReasonToFast_ExitFromTown.win_condition.l1			= "EnterToSea";           	
            pchar.quest.ReasonToFast_ExitFromTown.function    				= "ReasonToFast_ExitFromTownFight";
			pchar.questTemp.ReasonToFast.canSpeakSailor = true;			
			pchar.TownEscape = true;
			Flag_PIRATE();
		break;
		// ------------------------- Повод для спешки -----------------------------
		
		// -------------------------- Операция 'Галеон' ----------------------------
		case "CapComission_PrisonBad1":
			dialog.text = "És mi dolgod van vele?";
			link.l1 = "Több magánügyet kell megbeszélnem.";
			link.l1.go = "CapComission_PrisonBad2";
		break;
		
		case "CapComission_PrisonBad2":
			dialog.text = "Kapitány, közvetlen parancsom van arra, hogy mindenkit, aki a " + pchar.GenQuest.CaptainComission.Name + "felôl érdeklôdik, ôrizetbe vegyek és további kihallgatásra küldjek a rezidenciára.";
			link.l1 = "Szépen berendezkedett! Maguk a foglyok jönnek magukhoz, hogy letartóztassák ôket!";
			link.l1.go = "CapComission_PrisonBad3";
		break;
		
		case "CapComission_PrisonBad3":
			dialog.text = "És mindemellett azt kérem, hogy adják le a fegyvereiket!";
			link.l1 = "Cseszd meg! Akkor vegyék el tôlem erôszakkal!";
			link.l1.go = "fight";
			CaptainComission_GenerateCaptainInPrison(); // данила . на всякий случай ,чтобы сгенерился нормально.
			AddDialogExitQuest("CaptainComission_GenerateCapJail");
		break;
		
		case "CapComission_PrisonGood1":
			dialog.text = "Igen, persze. Parancsot kaptam a kormányzótól, hogy segítsek önnek ebben az ügyben. Most már meglátogathatja a foglyot.";
			link.l1 = "Köszönöm...";
			link.l1.go = "exit";
			pchar.questTemp.jailCanMove = true;
			AddDialogExitQuest("CaptainComission_GenerateCapJail");
		break;
		
		case "CapComission_PrisonFree1":
		if(CheckAttribute(pchar,"GenQuest.CaptainComission"))// лесник . разделение диалога если кеп убит или нет
		{
			dialog.text = "Kapitány úr, nincs felhatalmazásom arra, hogy ezt a foglyot kiengedjem az ôrizetbôl. Engedélyt kell kérnie a kormányzótól.";
			link.l1 = "Biztos úr, én a vizsgálat érdekében cselekszem. A fogoly beleegyezett, hogy együttmûködik a hatóságokkal, és felfedi a rejtekhelyet. Az idô sürget - a csempészek megtalálhatják az értékes szállítmányt, és akkor a lakosság számára elveszik.";
			link.l1.go = "CapComission_PrisonFree2";
		}
         else
		 {
         	dialog.text = "Nem kellett volna megölnie, kapitány... Nekem azonban mindegy. Téged kell kivégeznünk helyette. Ôrség! Fogjátok el!";
            link.l2 = "Rossz embert választottál, hogy baszakodj vele!...";
             link.l2.go = "fight";
			 NextDiag.TempNode = "First_officer";
			NextDiag.CurrentNode = NextDiag.TempNode; 
			AddDialogExitQuest("OpenTheDoors");
		 }			 
		break;
		
		case "CapComission_PrisonFree2":
			dialog.text = "De ki tudnám jelölni a kíséretét.";
			link.l1 = "Nincs rá szükség - van elég ôröm. Különben is, nem szeretném, ha nyilvánosságra kerülne a rejtekhely helye.";
			link.l1.go = "CapComission_PrisonFree3";
		break;
		
		case "CapComission_PrisonFree3":
			dialog.text = "Hmm... ó, nos. De a fejeddel fogsz felelni érte.";
			link.l1 = "Hát persze.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First_officer";
			NextDiag.CurrentNode = NextDiag.TempNode; 
			AddDialogExitQuest("OpenTheDoors");
		break;
		// -------------------------- Операция 'Галеон' ----------------------------
		
		case "F_ShipLetters_1":
			dialog.text = "Beszélj most, hallgatlak.";
			link.l1 = "Van nálam néhány hajó dokumentációja. A tulajdonosa bizonyára elvesztette, és úgy vélem, ez talán érdekelheti önt.";
			link.l1.go = "F_ShipLetters_2";
			pchar.questTemp.different.GiveShipLetters.speakFort = true;
		break;
		
		case "F_ShipLetters_2":			
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 0)
			{
				dialog.text = "Lószart! Ne vonja el a figyelmemet a munkámról! Menjen a kikötôi hatóságokhoz, ha érdekli!";
				link.l1 = "Nos, köszönöm, azt hiszem...";
				link.l1.go = "exit";
			}
			else
			{
				if(!CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakUsurer_1"))
				{
					dialog.text = "Igen, a helyi tulajdonos. Talán egy " + sti(pchar.questTemp.different.GiveShipLetters.price2) + " pezó jutalom lesz a megfelelô jutalom az éberségéért, kapitány.";
					link.l1 = "Talán nem.";
					link.l1.go = "F_ShipLetters_3";	
					link.l2 = "Nagylelkû ajánlat. Akkor az iratok az önöké!";
					link.l2.go = "F_ShipLetters_4";
				}
				else
				{
					if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 1)
					{
						dialog.text = "Ó, ez igazán érdekes! Azt hiszem, a városi kincstár szívesen fizet neked "+ sti(pchar.questTemp.different.GiveShipLetters.price4) +" pezó az illegális kereskedelem elleni küzdelemben való közremûködésedért.";
						link.l1 = "Talán nem.";
						link.l1.go = "F_ShipLetters_3";
						link.l2 = "Nagylelkû ajánlat. Akkor az iratok az önöké!";
						link.l2.go = "F_ShipLetters_4";
					}
					if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 2)
					{
						dialog.text = "Ó, Uram! Milyen jó, hogy eljöttél hozzám. Gondolom, az én rossz csillagzatú kollégám szívesen fizet önnek " + sti(pchar.questTemp.different.GiveShipLetters.price3) + " pezót, hogy elkerülje ennek az ügynek a nyilvánosságra kerülését.";
						link.l1 = "Talán nem.";
						link.l1.go = "F_ShipLetters_3";
						link.l2 = "Nagylelkû ajánlat. Akkor az iratok az önöké!";
						link.l2.go = "F_ShipLetters_4";
					}
				}
			}
		break;
		
		case "F_ShipLetters_3":
			dialog.text = "Ez az én városom, kapitány.";
			link.l1 = "Ezt nem fogom elfelejteni.";
			link.l1.go = "exit";
		break;
		
		case "F_ShipLetters_4":
			TakeItemFromCharacter(pchar, "CaptainBook"); 
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 1)
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
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 2)
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
						
			if((sti(pchar.questTemp.different.GiveShipLetters.variant) == 0) || (sti(pchar.questTemp.different.GiveShipLetters.variant) == 2))
			{	
				ChangeCharacterComplexReputation(pchar,"nobility", -1); 
				OfficersReaction("bad"); 
			}	
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //снимаем таймер 
			AddQuestRecord("GiveShipLetters", "8");			
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		
        case "ForGoodMove":
			//belamour legendary edition диалоги, если герой имеет звания и заслуги перед отечеством -->
			// генерал-губернатор
			if(CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE)
			{
				dialog.text = "Természetesen mindent láthat - itt van egy teljes rendem!";
				link.l1 = "Nos, nézzük meg, hadnagy úr!";
				link.l1.go = "exit";
				pchar.questTemp.jailCanMove = true;
				break;
			}
			// вице-адмирал
			if(isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation))
			{
				dialog.text = "Természetesen, excellenciás uram. Átmehet.";
				link.l1 = "Köszönöm, tiszt úr.";
				link.l1.go = "exit";
				pchar.questTemp.jailCanMove = true;
				break;
			}
			// Офицер с патентом
			if(IsOfficerFullEquip() && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation))
			{
				dialog.text = "Nos, nem látom okát, hogy visszautasítsam - elvégre Ön a hajó kapitánya a " + NationNameGenitive(sti(npchar.nation)) + "szolgálatában. Jöjjön be."; 
				link.l1 = "Köszönöm, tiszt úr.";
				link.l1.go = "exit";
				pchar.questTemp.jailCanMove = true;
				break;
			}
			// <-- legendary edition
			dialog.text = NPCStringReactionRepeat("De miért van rá szükséged? Hidd el, semmi sem ér kamatot, kivéve a tolvajokat és a banditákat.", "Ezt a kívánságodat már megbeszéltük.", 
				"Már megint? Már kétszer is beszéltünk róla!", "Hmm, megint...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Mindazonáltal szeretnék csatlakozni a kazamaták körbejárásához. Nagyon érdekel!", "Igen, pontosan. De szerettem volna beszélni róla.", 
				"Nos, talán harmadszorra...", "Remélem, hogy a foglyaid nem hagynak el.", npchar, Dialog.CurrentNode);
			link.l1.go = "ForGoodMove_1";
		break;
		
        case "ForGoodMove_1":
			pchar.questTemp.jailCanMove.money = 20+hrand(3)*10;
			if (sti(colonies[FindColony(npchar.city)].jail))
			{
				dialog.text = "Nos, nem látom okát, hogy visszautasítsam. " + FindRussianDublonString(sti(pchar.questTemp.jailCanMove.money)) + " - és amíg nem hagyja el a börtönt, szabadon járkálhat a folyosókon, sôt beszélgethet a rabokkal is.";
				if (PCharDublonsTotal() >= sti(sti(pchar.questTemp.jailCanMove.money)))
				{
					link.l1 = "Egyetértek, itt vannak az érméid!";
					link.l1.go = "ForGoodMove_agree";
				}
				link.l2 = "Ez nem fog menni. Túl sok a céltalan bolyongás a folyosókon.";
				link.l2.go = "exit";
			}
			else
			{
				dialog.text = RandPhraseSimple("Nem, ezt szigorúan tiltja a szabályzat. Micsoda? Azt hiszi, hogy cirkusz van itt? Tûnjön el, és ne vonja el a figyelmemet a feladataimról.", "Nem engedhetem, hogy idegen emberek járkáljanak a börtönömben. Kérem, ne zavarjanak!");
				link.l1 = "Rendben, ahogy mondod...";
				link.l1.go = "exit";
			}
		break;
		
        case "ForGoodMove_agree":
            dialog.text = "Rendben, most már elkezdheted a kirándulást...";
			link.l1 = "Köszönöm, biztos úr.";
			link.l1.go = "exit";
			pchar.questTemp.jailCanMove = true;
			RemoveDublonsFromPCharTotal(sti(pchar.questTemp.jailCanMove.money)));
		break;
		
        case "KnowAboutPrisoner":
			switch (pchar.questTemp.jailCanMove.ownerPrison)
			{
				case "0": sTemp = "Gyilkosságért."; break;
				case "1": sTemp = "Kalózkodással vádolják."; break;
				case "2": sTemp = "Banditizmusért és rablásért."; break;
				case "3": sTemp = "Lopáson kapták."; break;
				case "4": sTemp = "piti lopásért."; break;
				case "5": sTemp = "Csalásra."; break;
				case "6": sTemp = "csavargásért és koldulásért."; break;
			}
			dialog.text = sTemp;
			// генерал-губернатор
			if(CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE)
			{
				link.l1 = "Értem... Adja át nekem, biztos úr, aztán majd én magam döntök a fogoly sorsáról.";
				link.l1.go = "KnowAboutPrisoner_gengov";
			DeleteAttribute(pchar, "questTemp.jailCanMove.City");
		break;
			}
			// вице-адмирал
			if(isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation))
			{
				link.l1 = "Értem... Adja át nekem, biztos úr, aztán majd én magam döntök a fogoly sorsáról.";
				link.l1.go = "KnowAboutPrisoner_admiral";
				DeleteAttribute(pchar, "questTemp.jailCanMove.City");
				break;
			}
			link.l1 = "Értem... És van lehetôség kiváltásra, óvadékra... vagy más módon történô szabadon bocsátásra?";
			link.l1.go = "KnowAboutPrisoner_" + pchar.questTemp.jailCanMove.ownerPrison;
			DeleteAttribute(pchar, "questTemp.jailCanMove.City");
		break;
		
        case "KnowAboutPrisoner_0":
			dialog.text = "Természetesen nem. Ez a bitófára való madár egyenesen a pokolba fog kerülni. A Kormányzó különleges ellenôrzés alatt tartja az ügyét!";
			link.l1 = "Heh, értem...";
			link.l1.go = "notFree_exit";
		break;	
		
		case "KnowAboutPrisoner_1":
			dialog.text = "Most viccelsz? Már régen az akasztófára kellett volna mennie! Biztosan hamarosan kötéllel fog megházasodni. Felejtsd el.";
			link.l1 = "Megvan. És már el is felejtettem...";
			link.l1.go = "notFree_exit";
		break;
		
        case "KnowAboutPrisoner_2":
			dialog.text = "Nem hiszem. Sok bajt okozott a városlakóknak. Szóval ne kérdezze.";
			link.l1 = "Hmm, értem.";
			link.l1.go = "notFree_exit";
		break;
		
        case "KnowAboutPrisoner_3":
			dialog.text = "Valószínûleg nem. Ô egy tolvaj, és egy tolvajnak börtönben kell maradnia.";
			link.l1 = "Jól mondta, hadnagy úr!";
			link.l1.go = "notFree_exit";
		break;
		
        case "KnowAboutPrisoner_4":
			dialog.text = "Nem is tudom, tényleg. Csak egy apróságot lopott. Nem engedhetem szabadon, de börtönben rohadni hagyni biztosan nem helyes.";
			link.l1 = "Nos, akkor adja át nekem, hadnagy úr. Kifizetem érte az óvadékot - természetesen ésszerû összeget.";
			link.l1.go = "KnowAboutPrisoner_free";
		break;
		
        case "KnowAboutPrisoner_5":
			dialog.text = "Szabadon engedi? Ez valószínûnek tûnik. Véleményem szerint nincs értelme itt tartani ezt a pitiáner csalót.";
			link.l1 = "Nos, akkor adja át nekem, hadnagy úr. Kifizetem érte az óvadékot - természetesen ésszerû összeget.";
			link.l1.go = "KnowAboutPrisoner_free";
		break;
		
		case "KnowAboutPrisoner_6":
			dialog.text = "Hmm... Van értelme a szavaidnak. Ez a csavargó nem tartozik ide - csak mocskot és betegségeket terjeszt...";
			link.l1 = "Nos, akkor adja át nekem, hadnagy úr. Kifizetem érte az óvadékot - természetesen ésszerû összeget.";
			link.l1.go = "KnowAboutPrisoner_free";
		break;
		
        case "KnowAboutPrisoner_free":
			pchar.questTemp.jailCanMove.ownerPrison.money = 50+hrand(10)*10;
			dialog.text = "Rendben, megegyeztünk. " + FindRussianDublonString(sti(pchar.questTemp.jailCanMove.ownerPrison.money)) + " a szögre, és most azonnal elviheted.";
			if (PCharDublonsTotal() >= sti(pchar.questTemp.jailCanMove.ownerPrison.money))
			{
				link.l1 = LinkRandPhrase("Kiváló! Egyetértek!","Megállapodtunk, biztos úr!","Excellent. Kész vagyok kifizetni ezt a hozzájárulást.");
				link.l1.go = "KnowAboutPrisoner_agree";
			}
			link.l2 = "Nem, az túl drága. Azt hiszem, inkább kihagyom.";
			link.l2.go = "KnowAboutPrisoner_exit";
		break;
		
        case "KnowAboutPrisoner_agree":
			dialog.text = "Rendben, mehet a cellájába, és vigye magával azt a rongyost.";
			link.l1 = "Köszönjük!";
			link.l1.go = "exit";
			pchar.questTemp.jailCanMove = true;
			RemoveDublonsFromPCharTotal(sti(pchar.questTemp.jailCanMove.ownerPrison.money));
			Log_Info("Megkaptad " + FindRussianDublonString(sti(pchar.questTemp.jailCanMove.ownerPrison.money)) + "");
			DeleteAttribute(pchar, "questTemp.jailCanMove.ownerPrison");
			sld = characterFromId(pchar.questTemp.jailCanMove.prisonerId)
			LAi_CharacterEnableDialog(sld);
			sld.dialog.currentnode = "ToPrisonHead_canMove";
		break;
		
        case "KnowAboutPrisoner_exit":
			dialog.text = "Nos, ez a te döntésed. Nem adok még egy esélyt...";
			link.l1 = "Nincs rá szükség.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.jailCanMove.ownerPrison");
			sld = characterFromId(pchar.questTemp.jailCanMove.prisonerId);
			LAi_CharacterEnableDialog(sld);
			sld.dialog.currentnode = "ToPrisonHead_expansive";
		break;
		
        case "notFree_exit":
			sld = characterFromId(pchar.questTemp.jailCanMove.prisonerId);
			LAi_CharacterEnableDialog(sld);
			sld.dialog.currentnode = "ToPrisonHead_notFree";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		// belamour legendary edition -->
		// генерал-губернатор
		case "KnowAboutPrisoner_gengov":
			dialog.text = "Természetesen, excellenciás uram, ha úgy kívánja, akkor vigye ezt a szerencsétlent. Csak óvatosan, még mindig bûnözô...";
			link.l1 = "Ez nagyszerû. Ne aggódjon hadnagy, tudom mit csinálok.";
			link.l1.go = "exit";
			pchar.questTemp.jailCanMove = true;
			DeleteAttribute(pchar, "questTemp.jailCanMove.ownerPrison");
			sld = characterFromId(pchar.questTemp.jailCanMove.prisonerId)
			LAi_CharacterEnableDialog(sld);
			sld.dialog.currentnode = "ToPrisonHead_canMove";
		break;
		// вице-адмирал
		case "KnowAboutPrisoner_admiral":
			dialog.text = "Hát... Nem is tudom... Valójában nem engedhetem el a foglyokat. De ön még mindig admirálishelyettes, így valószínûleg joga van elvinni ezt a bûnözôt.";
			link.l1 = "Ez nagyszerû. Ne aggódjon hadnagy, tudom mit csinálok.";
			link.l1.go = "exit";
			pchar.questTemp.jailCanMove = true;
			DeleteAttribute(pchar, "questTemp.jailCanMove.ownerPrison");
			sld = characterFromId(pchar.questTemp.jailCanMove.prisonerId)
			LAi_CharacterEnableDialog(sld);
			sld.dialog.currentnode = "ToPrisonHead_canMove";
		break;
		// <-- legendary edition
		//---------------- Протектор ------------------
        case "First_protector":
			// генерал-губернатор
			if(CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE)
			{
				dialog.text = "Fôkormányzó úr, excellenciás uram! Jöjjön be, de legyen óvatos: ezektôl a bûnözôktôl bármit várhat...";
				link.l1 = "Ne aggódjon, katona, majd én elintézem, ha bármi történik.";
				link.l1.go = "exit";
				NextDiag.TempNode = "First_protector";
				break;
			}
			// вице-адмирал
			if(isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation))
			{
				dialog.text = "Üdvözletem, admirális-helyettes úr! Én vagyok itt szolgálatban: Gondoskodom róla, hogy senki ne lépjen be vagy távozzon engedély nélkül. De önnek természetesen joga van szabadon járni itt.";
				link.l1 = "Hát ez csodálatos.";
				link.l1.go = "exit";
				NextDiag.TempNode = "First_protector";
				break;
			}
			if (sti(pchar.questTemp.jailCanMove))
			{
				dialog.text = RandPhraseSimple("Átmehetsz, az igazgató engedélyt adott rá.", "Parancsot kaptam a börtönigazgatótól. Szabadon átmehet.");
				link.l1 = "Nagyon jó.";
				link.l1.go = "exit";
				DeleteAttribute(pchar, "questTemp.jailCanMove.ownerPrison.money");
			}
			else
			{
				dialog.text = RandPhraseSimple("A börtönigazgató külön engedélye nélkül nem mehet tovább!", "Csak a börtönigazgatónak tartozom felelôsséggel! Ha az ô engedélye nélkül próbálsz tovább menni, véged van!");
				link.l1 = RandPhraseSimple("Látom", "Rendben") + ", katona.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "First_protector";
		break;
		//---------------- Солдаты ------------------
        case "First_soldier":
            dialog.text = RandPhraseSimple("Szolgálatban vagyok, ne zavarjon.", "Menjen tovább, nem beszélhetek magával.");
			link.l1 = "Rendben, katona.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First_soldier";
		break;
		//---------------- Заключенные ------------------
        case "First_prisoner": 
			if (GetNationRelation2MainCharacter(sti(npchar.nation)) == RELATION_ENEMY)
			{
				dialog.text = LinkRandPhrase("Ho-ho, hát nem nagyszerû idôtöltés!", "vágd ôket, "+ GetSexPhrase("pajtás","lass") +", vágd!!!", "Ó, a pokolba! Elvesztettem minden reményemet, hogy láthatom a börtönôröm holttestét!");
				link.l1 = RandPhraseSimple("Heh!", "Arrgh!");
				link.l1.go = "NoMoreTalkExit";
				if (rand(10) > 6 && !CheckAttribute(pchar, "questTemp.Sharlie.Lock") && !CheckAttribute(pchar, "GenQuest.PrisonQuestLock") && !CheckAttribute(pchar, "quest.GivePrisonFree") && !CheckAttribute(pchar, "quest.GivePrisonFree_Over") && !CheckAttribute(pchar, "quest.DeliverToBander")) // Addon 2016-1 Jason пиратская линейка
				{
					dialog.text = RandPhraseSimple("Várj, "+ GetSexPhrase("haver","lass") +"!!! Engedjetek el!", "Figyelj, "+ GetSexPhrase("pajtás","lass") +", nyisd ki a cellát.");
					link.l1 = "Miért?";
					link.l1.go = "Prisoner_1"; // на квест освобождения заключённого
				}
			}
			else
			{
				dialog.text = LinkRandPhrase("Rablással vádolnak, de nem vagyok bûnös!", "Arrgh, te ápolt söpredék... Szeretnél egy kicsit a cellámban ülni?! Kheh-heh-heh...", "Nem vagyok bûnös!");
				link.l1 = RandPhraseSimple("Pofa be!", "Le se szarlak...");
				link.l1.go = "NoMoreTalkExit";
				if (rand(10) > 6 && !CheckAttribute(pchar, "questTemp.Sharlie.Lock") && !CheckAttribute(pchar, "GenQuest.PrisonQuestLock") && !CheckAttribute(pchar, "quest.GivePrisonFree_Over") && !CheckAttribute(pchar, "quest.GivePrisonFree") && !CheckAttribute(pchar, "quest.DeliverToBander") && !sti(colonies[FindColony(npchar.city)].HeroOwn)) // Addon 2016-1 Jason пиратская линейка
				{
					dialog.text = RandPhraseSimple("Várj, "+ GetSexPhrase("haver","lass") +", ne gyere olyan gyorsan!", "Ne siess, "+ GetSexPhrase("haver","lass") +", beszélgessünk.");
					link.l1 = "Miért?";
					if (rand(1))
					{
						link.l1.go = "Prisoner_1"; // на квест освобождения заключённого
					}
					else
					{
						link.l1.go = "Deliver_1"; // на квест передачу весточки
					}
				}
			}
		break;
		// -------------------- освобождение заключённого --------------------
        case "Prisoner_1":
            dialog.text = "Figyelj rám, haver. Ne hidd, hogy nem nézek ki jól, meg ilyenek. Csak ki kell jutnom innen...";
			link.l1 = "Micsoda?!";
			link.l1.go = "Prisoner_2";
			GetChestPlaceName();
			pchar.questTemp.jailCanMove.prisonerId = npchar.id; //запомним Id
			pchar.questTemp.jailCanMove.IsTrue = rand(4); //вид клада
			pchar.questTemp.jailCanMove.Item1 = GenQuestPrison_GenerateArtefact();
			pchar.questTemp.jailCanMove.Item2 = GenQuestPrison_GenerateBlade();
			pchar.questTemp.jailCanMove.Name = GetFullName(npchar); //имя перца
			npchar.nation = PIRATE;
		break;
        case "Prisoner_2":
            dialog.text = "Mit hallottál? Segíts nekem, és én vissza tudom fizetni...";
			link.l1 = "Na ez érdekes. Ki vagy te, és mit tudsz ajánlani nekem?";
			link.l1.go = "Prisoner_3";
		break;
        case "Prisoner_3":
            dialog.text = "A nevem " + GetFullName(npchar) + ". Van néhány cuccom elrejtve egy biztonságos helyen. Csak szedjetek ki innen és vigyetek a " + XI_ConvertString(pchar.questTemp.jailCanMove.islandId + "Acc") + ". Ott, egy barlangban van a kincsem. Megszerezzük és megosztjuk!";
			link.l1 = "És neked mi van a rejtekhelyeden? És honnan tudhatom, hogy igazat mondasz?";
			link.l1.go = "Prisoner_4";
		break;
        case "Prisoner_4":
            dialog.text = "Esküszöm, hogy igazat mondok! Ami a rejtekhelyet illeti - van egy kincs és pénz...";
			link.l1 = "Nem, haver. Nem kockáztatom a bôrömet egy kétes értékû rejtekhelyért. Sajnálom...";
			link.l1.go = "Prisoner_5";
			if (GetNationRelation2MainCharacter(sti(npchar.nation)) != RELATION_ENEMY)
			{			
				// belamour legendary edition адмирал и губернатор может договориться без денег
				bool bAdmiral = isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation);
				bool bGenGov = CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == GetBaseHeroNation());
				if(!bAdmiral && !bGenGov)
				{
				link.l2 = "Nos, talán érdemes lenne kockáztatni... A következôket javaslom: Kiiktatom az ôröket a börtönben, és elviszlek a hajómra. Ha minden jól megy, szeretném, ha végig mellettem maradnál, amíg el nem érjük a barlangot a  " + XI_ConvertString(pchar.questTemp.jailCanMove.islandId + "Voc") + ". Megegyeztünk?"; // belamour gen
				link.l2.go = "Prisoner_agree"; //силовой способ вызволения
				}
				link.l3 = "Rendben, megpróbálok segíteni neked. Beszélek a börtönigazgatóval. Talán ki tudlak majd szabadítani.";
				link.l3.go = "ToPrisonHead_agree"; //мирный способ вызволения
			}
			else
			{
				link.l2 = "Rendben, hiszek neked és kinyitom a celládat. Azt akarom, hogy végig mellettem maradj, amíg el nem érünk a barlanghoz a " + XI_ConvertString(pchar.questTemp.jailCanMove.islandId + "Voc") + ". Megegyeztünk?";
				link.l2.go = "Prisoner_agree_3"; //силовой способ вызволения, когда тюремщики убиты
			}
		break;
        case "Prisoner_5":
            dialog.text = RandPhraseSimple("A fenébe veled, te gazember!", "A fenébe is, te szemétláda!");
			link.l1 = RandPhraseSimple("És minden jót neked is. Viszontlátásra...", "A Holdnak nincs szüksége kutyaugatásra...");
			link.l1.go = "NoMoreTalkExit";
		break;
        case "Prisoner_agree":
            dialog.text = "Jól van. Nem vagyok abban a helyzetben, hogy válogatós legyek.";
			link.l1 = "Rendben, rendben. Most feltöröm a zárat, hogy kijuttassalak, és áttörünk. Készen állsz?";
			link.l1.go = "Prisoner_agree_1";
		break;
        case "Prisoner_agree_1":
            dialog.text = "Igen, "+ GetSexPhrase("pajtás","lass") +", készen állok!";
			link.l1 = "Akkor lássunk hozzá!";
			link.l1.go = "Prisoner_agree_2";
		break;
        case "Prisoner_agree_2":
			string slai_group = GetNationNameByType(sti(npchar.nation))  + "_citizens";
			LAi_group_AttackGroup(slai_group, LAI_GROUP_PLAYER);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			ReOpenQuestHeader("GivePrisonFree");
			AddQuestRecord("GivePrisonFree", "1");
            AddQuestUserData("GivePrisonFree", "sCity", XI_ConvertString("Colony"+npchar.city+"Gen"));
            AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
            AddQuestUserData("GivePrisonFree", "sIsland", XI_ConvertString(pchar.questTemp.jailCanMove.islandId+"Voc"));
			pchar.quest.GivePrisonFree_Death.win_condition.l1 = "NPC_Death";
			pchar.quest.GivePrisonFree_Death.win_condition.l1.character = npchar.id;
			pchar.quest.GivePrisonFree_Death.win_condition = "GivePrisonFree_Death";
			Pchar.quest.GivePrisonFree.win_condition.l1 = "location";
			Pchar.quest.GivePrisonFree.win_condition.l1.location = pchar.questTemp.jailCanMove.placeId;
			Pchar.quest.GivePrisonFree.win_condition = "GivePrisonFree";			
			DeleteAttribute(npchar, "LifeDay");
			GiveItem2Character(npchar, "unarmed");
			EquipCharacterbyItem(npchar, "unarmed");
			GetCharacterPos(npchar, &locx, &locy, &locz);	
			ChangeCharacterAddressGroup(npchar, npchar.location, "reload", LAi_FindNearestFreeLocator("reload", locx, locy, locz));
			LAi_SetActorType(npchar);
			LAi_group_Register("DeliveQuest_Prison");
			LAi_group_SetRelation("DeliveQuest_Prison", LAI_GROUP_PLAYER, LAI_GROUP_FRIEND);
			//LAi_group_SetAlarmReaction(LAI_GROUP_PLAYER, "DeliveQuest_Prison", LAI_GROUP_ENEMY, LAI_GROUP_FRIEND);
			LAi_group_MoveCharacter(npchar, "DeliveQuest_Prison");
			LAi_ActorFollowEverywhere(npchar, "", -1);
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

        case "Prisoner_agree_3":
            dialog.text = "Jól van. Nem vagyok abban a helyzetben, hogy válogatós legyek.";
			link.l1 = "Rendben. Kövessetek, amilyen gyorsan csak tudtok - még el kell jutnunk a hajómra. Ne késlekedjetek!";
			link.l1.go = "Prisoner_agree_4";
		break;
        case "Prisoner_agree_4":
			ReOpenQuestHeader("GivePrisonFree");
			AddQuestRecord("GivePrisonFree", "1");
            AddQuestUserData("GivePrisonFree", "sCity", XI_ConvertString("Colony"+npchar.city+"Gen"));
            AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
            AddQuestUserData("GivePrisonFree", "sIsland", XI_ConvertString(pchar.questTemp.jailCanMove.islandId+"Voc"));
			pchar.quest.GivePrisonFree_Death.win_condition.l1 = "NPC_Death";
			pchar.quest.GivePrisonFree_Death.win_condition.l1.character = npchar.id;
			pchar.quest.GivePrisonFree_Death.win_condition = "GivePrisonFree_Death";
			Pchar.quest.GivePrisonFree.win_condition.l1 = "location";
			Pchar.quest.GivePrisonFree.win_condition.l1.location = pchar.questTemp.jailCanMove.placeId;
			Pchar.quest.GivePrisonFree.win_condition = "GivePrisonFree";
			DeleteAttribute(npchar, "LifeDay");
			GiveItem2Character(npchar, "unarmed");
			EquipCharacterbyItem(npchar, "unarmed");
			GetCharacterPos(npchar, &locx, &locy, &locz);	
			ChangeCharacterAddressGroup(npchar, npchar.location, "reload", LAi_FindNearestFreeLocator("reload", locx, locy, locz));
			LAi_SetActorType(npchar);
			LAi_group_Register("DeliveQuest_Prison");
			LAi_group_SetRelation("DeliveQuest_Prison", LAI_GROUP_PLAYER, LAI_GROUP_FRIEND);
			//LAi_group_SetAlarmReaction(LAI_GROUP_PLAYER, "DeliveQuest_Prison", LAI_GROUP_ENEMY, LAI_GROUP_FRIEND);
			LAi_group_MoveCharacter(npchar, "DeliveQuest_Prison");
			LAi_ActorFollowEverywhere(npchar, "", -1);
			DialogExit();
		break;

        case "ToPrisonHead_agree":
            dialog.text = "Nos, megpróbálhatod. Remélem, sikerülni fog! De ne vesztegessétek az idôt - pár nap múlva már itt sem leszek...";
			link.l1 = "Várjatok itt, mindent elintézek.";
			link.l1.go = "NoMoreTalkExit";
			pchar.questTemp.jailCanMove.City = npchar.City; //город
			pchar.questTemp.jailCanMove.ownerPrison = rand(6); //характер преступления
			SetTimerCondition("GivePrisonFree_Over", 0, 0, 2, false);
			AddQuestRecord("GivePrisonFree", "5");
			AddQuestUserData("GivePrisonFree", "sSex", GetSexPhrase("",""));
            AddQuestUserData("GivePrisonFree", "sCity", XI_ConvertString("Colony"+npchar.city+"Gen"));
            AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
		break;

        case "ToPrisonHead_canMove":
            dialog.text = "Nos, mit mondasz, "+ GetSexPhrase("haver","lass") +"?";
			link.l1 = "Mindent elintéztem, és innen már elviszlek.";
			link.l1.go = "ToPrisonHead_canMove_1";
		break;
        case "ToPrisonHead_canMove_1":
            dialog.text = "Akkor menjünk innen! Ó, Uram, milyen boldog vagyok!";
			link.l1 = "Foglaljuk össze. Azt akarom, hogy végig mellettem maradj, amíg el nem érünk a barlanghoz a " + XI_ConvertString(pchar.questTemp.jailCanMove.islandId + "Dat") + ", nem maradsz le egy lépésnél tovább. Csak a biztonság kedvéért. Egyetértesz?";
			link.l1.go = "ToPrisonHead_canMove_2";
		break;
        case "ToPrisonHead_canMove_2":
            dialog.text = "Persze, hogy egyetértek! Annál is inkább, mert nem vagyok abban a helyzetben, hogy választhassak.";
			link.l1 = "Akkor szabad vagy.";
			link.l1.go = "ToPrisonHead_canMove_exit";
		break;
        case "ToPrisonHead_canMove_exit":
			pchar.quest.GivePrisonFree_Over.over = "yes";
			ReOpenQuestHeader("GivePrisonFree");
			AddQuestRecord("GivePrisonFree", "1");
            AddQuestUserData("GivePrisonFree", "sCity", XI_ConvertString("Colony"+npchar.city+"Gen"));
            AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
            AddQuestUserData("GivePrisonFree", "sIsland", XI_ConvertString(pchar.questTemp.jailCanMove.islandId+"Voc"));
			pchar.quest.GivePrisonFree_Death.win_condition.l1 = "NPC_Death";
			pchar.quest.GivePrisonFree_Death.win_condition.l1.character = npchar.id;
			pchar.quest.GivePrisonFree_Death.win_condition = "GivePrisonFree_Death";
			Pchar.quest.GivePrisonFree.win_condition.l1 = "location";
			Pchar.quest.GivePrisonFree.win_condition.l1.location = pchar.questTemp.jailCanMove.placeId;
			Pchar.quest.GivePrisonFree.win_condition = "GivePrisonFree";			
			DeleteAttribute(npchar, "LifeDay");
			GiveItem2Character(npchar, "unarmed");
			EquipCharacterbyItem(npchar, "unarmed");
			GetCharacterPos(npchar, &locx, &locy, &locz);	
			ChangeCharacterAddressGroup(npchar, npchar.location, "reload", LAi_FindNearestFreeLocator("reload", locx, locy, locz));
			LAi_SetActorType(npchar);
			LAi_group_Register("DeliveQuest_Prison");
			LAi_group_SetRelation("DeliveQuest_Prison", LAI_GROUP_PLAYER, LAI_GROUP_FRIEND);
			//LAi_group_SetAlarmReaction(LAI_GROUP_PLAYER, "DeliveQuest_Prison", LAI_GROUP_ENEMY, LAI_GROUP_FRIEND);
			LAi_group_MoveCharacter(npchar, "DeliveQuest_Prison");
			LAi_ActorFollowEverywhere(npchar, "", -1);
			DialogExit();
		break;

        case "ToPrisonHead_notFree":
			switch (pchar.questTemp.jailCanMove.ownerPrison)
			{
				case "0": sTemp = "gyilkosság"; break;
				case "1": sTemp = "kalózkodás"; break;
				case "2": sTemp = "brigantéria"; break;
				case "3": sTemp = "tolvajlás"; break;
			}
            dialog.text = "Nos, mit mondasz, "+ GetSexPhrase("haver","lass") +"?";
			link.l1 = "Nem tudtam elintézni a szabadon bocsátásodat. Önt a " + sTemp + "vádakkal vádolják, ezért nem lehet óvadék ellenében szabadlábra helyezni.";
			link.l1.go = "ToPrisonHead_notFree_1";
			DeleteAttribute(pchar, "questTemp.jailCanMove.ownerPrison");
		break;
		
        case "ToPrisonHead_notFree_1":
            dialog.text = "De engem megrágalmaztak! Ó, ördög! És most mit fogok tenni? Élve fogok itt megrohadni!";
			link.l1 = "Sajnálom, pajtás, de nem tehetek semmit érted.";
			link.l1.go = "ToPrisonHead_notFree_2";
			link.l2 = "Csak egy esélyem maradt - erôszakkal kiszabadítani téged. Most feltöröm a zárat, hogy kiszabadítsalak, és áttörünk. Készen állsz?";
			link.l2.go = "Prisoner_agree_1";
			pchar.quest.GivePrisonFree_Over.over = "yes";
		break;
		
        case "ToPrisonHead_notFree_2":
            dialog.text = RandPhraseSimple("Átkozottak vagytok!", "A francba, elszakítottál, te kurva...");
			link.l1 = "És minden jót neked is. Viszlát...";
			link.l1.go = "NoMoreTalkExit";
			AddQuestRecord("GivePrisonFree", "7");
            AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
			DeleteAttribute(pchar, "questTemp.jailCanMove.islandId");	
			DeleteAttribute(pchar, "questTemp.jailCanMove.placeId");
			DeleteAttribute(pchar, "questTemp.jailCanMove.prisonerId");
			DeleteAttribute(pchar, "questTemp.jailCanMove.IsTrue");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Sum");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Name");
		break;

        case "ToPrisonHead_expansive":
			dialog.text = "Szóval, van valami jó hír, "+ GetSexPhrase("pajtás","lass") +"?";
			link.l1 = "Az óvadék a szabadulásodért túl magas, nincs annyi pénzem. Abba kell hagynom a segítségedet.";
			link.l1.go = "ToPrisonHead_notFree_2";
			pchar.quest.GivePrisonFree_Over.over = "yes";
		break;
		//==> в месте, где клад припрятан
        case "PrisonerInPlace":
			switch (sti(pchar.questTemp.jailCanMove.IsTrue))
			{
				case 0:
					dialog.text = "Figyelj, mindent átnéztem, de nem találtam kincset. Kár, hogy így alakult. Valaki biztosan kiásta elôttünk.";
					link.l1 = "És az hogy lehet?!";
					link.l1.go = "PrisonerInPlace_1";
				break;
				case 1:
					dialog.text = "Megtaláltam! A kincs még mindig ott van, ahol hagytam.";
					link.l1 = "Kitûnô. Nos, akkor váljunk szét?";
					link.l1.go = "Node_1";
				break;
				case 2:
					dialog.text = "Nos, itt is van, a rejtekhelyem. Nem sok minden, de ez minden, amim van. Ahogy megbeszéltük, a fele a tiéd.";
					link.l1 = "Igen, a kincs valóban szerény. Nos, még mindig jobb, mint a semmi.";
					link.l1.go = "Node_2";
				break;
				case 3:
					dialog.text = "Kapitány, sajnálom, de... Nincs kincs.";
					link.l1 = "Micsoda?! Átvertél, te gazember! Kihoztalak arra a szigetre - és miért? Ezt nem úszod meg!";
					link.l1.go = "Node_3";
				break;
				case 4:
                    ok = GetCharacterItem(pchar, "map_full") == 0 && GetCharacterItem(PChar, "map_part2") == 0;
                    if(GetCharacterItem(PChar, "map_part1") > 0 && !ok) // Первая половинка есть, но вторую дать нельзя
                    {
                        dialog.text = "Figyelj, mindent átnéztem, de nem találtam kincset. Kár, hogy így alakult. Valaki biztosan kiásta elôttünk.";
                        link.l1 = "És az hogy lehet?!";
                        link.l1.go = "PrisonerInPlace_1";
                    }
                    else
                    {
                        dialog.text = "Az istenit... Hogy lehet ez? Ez nem lehet!";
                        link.l1 = "Mi a helyzet, haver? Hol van a kincs? Ne mondd, hogy nincs!";
                        link.l1.go = "Node_4";
                    }
				break;
			}
		break;
			
		case "Node_1":
			dialog.text = "Persze, ahogy megbeszéltük. A kincs fele a tiéd.";
			link.l1 = "Szent Isten, most már biztosan sok értékes dolog van!";
			link.l1.go = "PrisonerInPlace_3";
			Log_Info("Megkaptad a kincsbôl a részed");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "icollection", 1+hrand(1));
			TakeNItems(pchar, "chest", 4+hrand(4));
			TakeNItems(pchar, "jewelry1", 70+rand(15));
			TakeNItems(pchar, "jewelry2", 50+rand(15));
			TakeNItems(pchar, "jewelry3", 60+rand(15));
			TakeNItems(pchar, "jewelry4", 40+rand(10));
			TakeNItems(pchar, "jewelry5", 10+rand(10));
			TakeNItems(pchar, "jewelry46", 60+rand(20));
			TakeNItems(pchar, "jewelry47", 40+rand(15));
			TakeNItems(pchar, "jewelry40", 60+rand(20));
			AddQuestRecord("GivePrisonFree", "3_1");
			AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
			CloseQuestHeader("GivePrisonFree");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item1");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item2");
		break;
			
		case "Node_2":
			dialog.text = "Kapitány, ott van még az az indiai tárgy is, többek között. A részed mellett az is a tiéd lehet.";
			link.l1 = "Hát, legalább valami értékeset a szabadulásodhoz! Add ide nekem.";
			link.l1.go = "PrisonerInPlace_3";
			Log_Info("Megkaptad a kincsbôl a részed");
			PlaySound("interface\important_item.wav");
			sTemp = pchar.questTemp.jailCanMove.Item1;
			TakeNItems(pchar, sTemp, 1);
			TakeNItems(pchar, "jewelry5", 40+rand(10));
			TakeNItems(pchar, "jewelry6", 20+rand(20));
			TakeNItems(pchar, "jewelry17", 80+rand(20));
			TakeNItems(pchar, "jewelry13", 10+rand(10));
			TakeNItems(pchar, "jewelry10", 20+rand(20));
			TakeNItems(pchar, "jewelry12", 50+rand(20));
			TakeNItems(pchar, "jewelry11", rand(2)+1);
			AddQuestRecord("GivePrisonFree", "3_2");
			AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
			CloseQuestHeader("GivePrisonFree");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item1");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item2");
		break;
			
		case "Node_3":
			dialog.text = "Várjon, kapitány, ne izguljon, hadd mondjam. Én is tengerész vagyok, akárcsak ön. Tévedésbôl kerültem börtönbe, esküszöm. Te voltál az egyetlen esélyem a szökésre, és hazudnom kellett neked a kincsrôl.\nNincs kincs, de egy jó dolgot elrejtettem ott. Vedd el, és hagyj békében elmenni. Talán egy nap egy csatában segít majd túlélni.";
			link.l1 = "Rendben, amúgy sem vártam tôled sokat. Hála Istennek, hogy nem vagyok haragtartó.";
			link.l1.go = "PrisonerInPlace_3";
			Log_Info("Kaptál felszerelést");
			PlaySound("interface\important_item.wav");
			sTemp = pchar.questTemp.jailCanMove.Item2;
			TakeNItems(pchar, sTemp, 1);
			AddQuestRecord("GivePrisonFree", "3_3");
			AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
			CloseQuestHeader("GivePrisonFree");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item1");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item2");
		break;
			
		case "Node_4":
			dialog.text = "Ne!!! Nincs ott! Átkozott selejt... Kapitány, teljesen biztos voltam benne, hogy itt találom! De úgy tûnik, tévedtem! Valami azon a papírdarabon tényleg nem volt világos...";
			link.l1 = "Ó, nos... Komoly bajban vagy, pajtás. De azért szeretném meghallgatni a magyarázatát.";
			link.l1.go = "Node_4_1";
		break;
			
		case "Node_4_1":
			dialog.text = "Volt egy darabka térképem. Az egy igazi térkép volt, esküszöm! De nagyon nehéz megmondani, hogy melyik sziget volt rajta... Azt hittem, itt van... De, mint látod, tévedtem.";
			link.l1 = "Milyen papírdarab? Add ide azonnal!";
			link.l1.go = "Node_4_2";
		break;
			
		case "Node_4_2":
			AddMapPart();
			dialog.text = "Persze, fogd meg. Kapitány, engedjen el... kérem. Tényleg azt hittem, hogy a kincs ott van. Talán majd kitalálod, hogy hol van, és elviszed magadnak. Könyörgöm.";
			link.l1 = "Értem... Valóban, nehéz bármit is kitalálni ebbôl a roncsból. A térkép második felére van szükség. Rendben, tûnjetek el. Most már látom, hogy nem a te hibád volt.";
			link.l1.go = "PrisonerInPlace_4";
		break;
			
		case "PrisonerInPlace_1":
			dialog.text = "Nagyon egyszerû, "+ GetSexPhrase("haver","lass") +". Az életben minden megtörténik.\nHát itt vagy - ha akarod: maradj, keress tovább. Nos, nekem mennem kell!\nViszlát, "+ GetSexPhrase("barátom","lass") +", köszönöm, hogy megmentetted az életemet. Mindig emlékezni fogok rád!";
			link.l1 = "Gazember! Azt hiszed, hogy hagyom, hogy megúszd ezt?! Hé! Várj, gyáva!";
			link.l1.go = "PrisonerInPlace_2";
			AddQuestRecord("GivePrisonFree", "4");
			AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
			CloseQuestHeader("GivePrisonFree");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item1");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item2");
		break;
			
        case "PrisonerInPlace_2":
			LAi_group_Delete("EnemyFight");
			DeleteAttribute(pchar, "questTemp.jailCanMove.islandId");	
			DeleteAttribute(pchar, "questTemp.jailCanMove.placeId");
			DeleteAttribute(pchar, "questTemp.jailCanMove.prisonerId");
			DeleteAttribute(pchar, "questTemp.jailCanMove.IsTrue");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Sum");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Name");
			chrDisableReloadToLocation = false;
			LAi_LocationDisableMonstersGen(pchar.location, false);
			npchar.lifeDay = 0;
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_SetActorType(npchar);
            LAi_ActorRunToLocation(NPChar, "reload", "reload1_back", "none", "", "", "", -1);
			DialogExit();

            Pchar.quest.DeletePrisonGroup.win_condition.l1 = "ExitFromLocation";
            Pchar.quest.DeletePrisonGroup.win_condition.l1.location = pchar.location;
            Pchar.quest.DeletePrisonGroup.win_condition = "DeletePrisonGroup";
		break;
		
        case "PrisonerInPlace_3":
			dialog.text = "Tessék, tessék. Köszönöm! Köszönöm!";
			link.l1 = "Ég veled...";
			link.l1.go = "PrisonerInPlace_2";
		break;
		
        case "PrisonerInPlace_4":
			dialog.text = "Köszönöm, kapitány! Imádkozni fogok érted, amíg csak élek!";
			link.l1 = "Ó, fogd be! Menjetek békében...";
			link.l1.go = "PrisonerInPlace_2";
			AddQuestRecord("GivePrisonFree", "3_4");
            AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
			AddQuestUserData("GivePrisonFree", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("GivePrisonFree");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item1");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item2");
		break;
        
		// -------------------- освобождение заключённого --------------------
		// ------------------------ передать маляву --------------------------
        case "Deliver_1":
			dialog.text = "Engem úgy hívnak " + GetFullName(npchar) + ". Van egy kérésem hozzád, he-he-he...";
			link.l1 = "Mi a baj?";
			link.l1.go = "Deliver_2";
		break;
        case "Deliver_2":
			dialog.text = "Szükségem van egy levélre, hogy kiküldjenek a börtönbôl. Megtennéd?";
			link.l1 = "És mit kapok érte?";
			link.l1.go = "Deliver_3";
		break;
        case "Deliver_3":
			dialog.text = "A haverok nem fognak csalódást okozni, ígérem... Na és? Benne vagy?";
			link.l1 = "Nem, nem érdekel.";
			link.l1.go = "Prisoner_5";
			link.l2 = "Nos, ha nem igényel túl sok erôfeszítést tôlem, akkor meg tudom csinálni.";
			link.l2.go = "Deliver_agree";
		break;
        case "Deliver_agree":
			dialog.text = "Rendben. Most jól figyelj rám. Két cimborám egy házban várja az üzenetemet, nehogy egy razzia során lefoglalják ôket. De fogalmam sincs, hogy pontosan melyik ház az. Át kell kutatnod.";
			link.l1 = "Hogy érted, hogy átkutatni?";
			link.l1.go = "Deliver_4";
		break;
        case "Deliver_4":
			dialog.text = "Keresni, mint a keresés. Körbefutod a várost, bekukkantasz a házakba. Ha eljutsz a megfelelô helyre, nem fognak beszélgetés nélkül kiengedni. De tartsd észben, hogy legfeljebb még két napig maradnék ott. Szóval ne késlekedjetek.";
			link.l1 = "Értem. Nos, akkor add át az üzenetedet.";
			link.l1.go = "Deliver_5";
		break;
        case "Deliver_5":
			pchar.questTemp.jailCanMove.Deliver.locationId = GetBanderLocation(npchar); //Id коммона
			if (pchar.questTemp.jailCanMove.Deliver.locationId == "none")
			{
				dialog.text = "Hmm, tudod, én csak nem kedvellek téged. Meggondoltam magam. Gyere, ne állj ott!";
				link.l1 = "Nézzenek oda! Nos, ahogy óhajtja...";
				link.l1.go = "NoMoreTalkExit";
				DeleteAttribute(pchar, "questTemp.jailCanMove.Deliver");
			}
			else
			{
				dialog.text = "Tessék. Köszönöm, "+ GetSexPhrase("haver","lass") +"!";
				link.l1 = "Egyáltalán nem.";
				link.l1.go = "NoMoreTalkExit";
				GiveItem2Character(Pchar, "Malyava");
				pchar.questTemp.jailCanMove.Deliver.Id = npchar.id; //Id зэка
				pchar.questTemp.jailCanMove.Deliver.name = GetFullName(npchar); //имя зэка
				pchar.questTemp.jailCanMove.Deliver.City = npchar.city; //город (Id колонии)
				pchar.questTemp.jailCanMove.Deliver.good = rand(3); //опрокинут или нет
				pchar.questTemp.jailCanMove.Deliver.price = rand(6)*500+500; //цена услуги
				pchar.quest.DeliverToBander.win_condition.l1 = "location";
				pchar.quest.DeliverToBander.win_condition.l1.location = pchar.questTemp.jailCanMove.Deliver.locationId;
				pchar.quest.DeliverToBander.win_condition = "DeliverToBander";
				pchar.quest.DeliverToBander.again = true; 
				SetTimerCondition("DeliverToBander_over", 0, 0, 2, false);
				ReOpenQuestHeader("GivePrisonFree");
				AddQuestRecord("GivePrisonFree", "8");
				AddQuestUserData("GivePrisonFree", "sSex", GetSexPhrase("",""));
				AddQuestUserData("GivePrisonFree", "sCity", XI_ConvertString("Colony"+npchar.city+"Gen"));
				AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Deliver.name);
			}
		break;
		
		// Warship, 16.05.11. Генер "Justice for sale".
		case "JusticeOnSale_1":
			dialog.text = "Igen, letartóztatták csempészet vádjával. De miért érdekel téged az az akasztófamadár, " + GetAddress_Form(NPChar) + "?";
			link.l1 = "A bandája azt tervezi, hogy megszökteti és folytatja a piszkos ügyeit.";
			link.l1.go = "JusticeOnSale_2";
			link.l2 = "Úgy hallottam, hogy nem bûnös.";
			link.l2.go = "JusticeOnSale_3";
			
			DeleteAttribute(PChar, "GenQuest.JusticeOnSale.PrisonWait");
		break;
		
		case "JusticeOnSale_2":
			dialog.text = "Értesíteni kell a kormányzót, " + GetAddress_Form(NPChar) + ", ezeket a gazembereket mind el kell kapni!";
			link.l1 = "Úgy lesz.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First_officer";
		break;
		
		case "JusticeOnSale_3":
			dialog.text = "Figyelj, " + GetFullName(PChar) + ", azt a fickót elfogták, miközben tiltott árut próbált eladni, pont a városban! Hogy állíthatja, hogy nem bûnös?";
			link.l1 = "Úgy hallottam, hogy a vád alaptalan volt, és nincs bizonyítékod, nem igaz? Nem lehet csak úgy ôrizetbe venni egy embert, akit igazságtalanul vádoltak.";
			link.l1.go = "JusticeOnSale_4";
		break;
		
		case "JusticeOnSale_4":
			dialog.text = "Nincsenek sem tanúink, sem áruink, de ez nem változtat semmin, kapitány " + GetFullName(PChar) + "! Az illetô egyértelmûen bûnös - és talán nem csak illegális kereskedelemben. Akárhogy is - miért érdekli a fogoly?";
			link.l1 = "Talán az én szavam lehet az óvadék azért a szerencsétlen fogolyért?";
			link.l1.go = "JusticeOnSale_5_WithoutMoney";
			
			if(sti(PChar.money) >= 5000)
			{
				link.l2 = "Talán ez az 5000 pezó lehet az óvadék a szerencsétlen fogolyért?";
				link.l2.go = "JusticeOnSale_5";
			}
		break;
		
		case "JusticeOnSale_5_WithoutMoney":
			if(GetCharacterSkill(PChar, SKILL_LEADERSHIP) > hrand(100) || sti(PChar.money) < 5000)
			{
				dialog.text = "Rendben, " + GetAddress_Form(NPChar) + ", fogd azt a gazembert és menj, mielôtt meggondolom magam.";
				link.l1 = "Jó látni az igazság gyôzelmét, nem gondolja?";
				link.l1.go = "JusticeOnSale_6";
			}
			else
			{
				dialog.text = "Nem, " + GetAddress_Form(NPChar) + ", ez nem fog menni.";
				link.l1 = "Akkor talán ez az 5000 pezó lehet a nyomósabb érv?";
				link.l1.go = "JusticeOnSale_5";
			}
		break;
		
		case "JusticeOnSale_5":
			dialog.text = "Rendben, " + GetAddress_Form(NPChar) + ", fogd azt a gazembert és menj, mielôtt meggondolom magam.";
			link.l1 = "Jó látni az igazság gyôzelmét, nem gondolja?";
			link.l1.go = "JusticeOnSale_6";
			AddMoneyToCharacter(PChar, -5000);
			PChar.GenQuest.JusticeOnSale.PrisonMoney = true;
		break;
		
		case "JusticeOnSale_6":
			DialogExit();
			sld = GetCharacter(NPC_GenerateCharacter("JusticeOnSale_Smuggler", "mercen_"+(rand(9)+1), "man", "man", sti(PChar.rank)+5, PIRATE, -1, true, "marginal"));
			SetFantomParamFromRank(sld, sti(PChar.rank)+5, true);
			sld.name = PChar.GenQuest.JusticeOnSale.SmugglerName;
			sld.lastName = "";
			sld.dialog.filename = "GenQuests_Dialog.c";
			sld.dialog.currentnode = "First time";
			sld.greeting = "Enc_Raiders"; 
			AddPassenger(PChar, sld, false);
			SetCharacterRemovable(sld, false);
			PChar.GenQuest.JusticeOnSale.SmugglerModel = sld.model;
			DeleteAttribute(PChar, "GenQuest.JusticeOnSale.MayorWait");
			sld = &Locations[FindLocation(PChar.GenQuest.JusticeOnSale.ShoreId)];
			sld.DisableEncounters = true;
			PChar.Quest.JusticeOnSale_ShoreEnterWithSmuggler.win_condition.l1  = "location";
			PChar.Quest.JusticeOnSale_ShoreEnterWithSmuggler.win_condition.l1.location = PChar.GenQuest.JusticeOnSale.ShoreId;
			PChar.Quest.JusticeOnSale_ShoreEnterWithSmuggler.function = "JusticeOnSale_ShoreEnterWithSmuggler";
			Log_Info("Csempészkapitány egy táblán");
			PlaySound("interface\notebook.wav");
			LAi_Fade("", "");
			WaitDate("",0,0,0,0,60); // 280313 // лесник. прокрутка времени было так WaitDate("",0,0,0,2,5);
		break;
		// --> belamour ночной приключенец
		case "NightAdventure_CitizenHomie":
			dialog.text = "Igen, volt egy ilyen erôszakos. Egy ôrszemmel szemben durván viselkedett, majd verekedésbe keveredett. Semmi több: néhány napig rács mögött fog ülni - majd kijózanodik. Miért érdekel téged ô? Ön kapitánynak látszik, és ez a részeges nem úgy néz ki, mint egy tengerész.";
			link.l1 = "Igen, így van, kapitány vagyok. Az a helyzet, hogy ez a részeges egy régi ismerôsöm. Csak ne beszéljen errôl senkinek, kérem. Ha jól értem, még csak fegyvert sem ragadott. Talán ezúttal elengedné a kérésemre?";
			link.l1.go = "NightAdventure_CitizenHomie_1";
		break;
		
		case "NightAdventure_CitizenHomie_1":
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_CitizenHomie") // отпустил под честное слово
			{
				dialog.text = "Igen, jó barátom. Ne aggódjon, nem mondom el senkinek. Valójában nem is tudott rendesen ütni, csak próbálkozás volt - ezért tették börtönbe. Ha már kérdezi, az ön iránti tiszteletbôl elengedem. Csak figyelmeztessük, hogy legközelebb tartsa magát kordában. Vagy még jobb, ha kevesebbet iszik.";
				link.l1 = "Köszönöm, tiszt úr.";
				link.l1.go = "NightAdventure_CitizenHomieOK";
			}
			
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_CitizenHomieSolderNM" || pchar.GenQuest.NightAdventureVar == "NightAdventure_CitizenHomieSolderGM") // поговорить с солдатом
			{
				dialog.text = "Igen, jó barátom. Ne aggódj, nem mondom el senkinek. Csak az a baj, hogy sikerült arcon ütnie az ôrszemet, mielôtt megkötözték. Szóval nem engedhetem ki. Kivéve persze, ha az ôrség beleegyezik, hogy visszavonja a követeléseit. Beszélhetsz vele te magad, ma a városban járôrözik.";
				link.l1 = "Nem, attól tartok, ha megütötte az ôrt, akkor nem tudok segíteni rajta. Pár napig ülnie kell majd. Elnézést a zavarásért, biztos úr.";
				link.l1.go = "CitizenHomieEnd";
				link.l2 = "Oké, megyek és megpróbálok tárgyalni az ôrrel.";
				link.l2.go = "NightAdventure_CitizenHomieSolder";
			}
			
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_CitizenHomieOfficer") // выплата офицеру
			{
				dialog.text = "Igen, jó barátom. Ne aggódjon, nem mondom el senkinek. Az a helyzet, hogy a fegyveres erôk egy tagját megtámadni szolgálat közben bûncselekmény. Félúton találkozhatunk, és elengedhetem, de csak óvadék ellenében.";
				link.l1 = "És mennyit kell fizetnem érte?";
				link.l1.go = "NightAdventure_CitizenHomieOfficer";
			}
		break;
		
		case "NightAdventure_CitizenHomieOK":
			DialogExit();
			DeleteAttribute(pchar,"GenQuest.NightAdventureToJail");
			SetFunctionLocationCondition("NightAdventure_CitizenHomieOK", npchar.City+"_town", false);
		break;
		
		case "NightAdventure_CitizenHomieEnd":
			DialogExit();
			DeleteAttribute(pchar,"GenQuest.NightAdventureToJail");
			pchar.quest.NightAdventure_SeaExit.over = "yes";
			pchar.quest.NightAdventure_JungleExit.over = "yes";
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
		break;
		
		case "NightAdventure_CitizenHomieSolder":
			DialogExit();
			DeleteAttribute(pchar,"GenQuest.NightAdventureToJail");
			for(i=0; i<MAX_CHARACTERS; i++)
			{
				if(Characters[i].location != npchar.City+"_town") continue;
				if(Characters[i].chr_ai.type != "patrol") continue;
				while(SoldQty < 10) // на всякий случай, чтобы не было выхода за границы массива
				{                   // генерируется 7 солдат + 3 мушкетера
					SoldNum[SoldQty] = Characters[i].index;
					SoldQty++;
				}
			}
			iTemp = rand(SoldQty);
			pchar.GenQuest.NightAdventureSolNum = SoldNum[iTemp];
		break;
		
		case "NightAdventure_HomieToPrisoner":
			DeleteAttribute(pchar,"GenQuest.NightAdventureToPrisoner");
			pchar.quest.NightAdventure_SeaExit.over = "yes";
			pchar.quest.NightAdventure_JungleExit.over = "yes";
			SetFunctionLocationCondition("NightAdventure_CitizenHomieOK", npchar.City+"_town", false);
			dialog.text = "*olvas* Szóval... szóval... Nos, mivel az ôrségnek nincs panasza, akkor nekem sincs, viheti a barátját. Csak figyelmeztesse, hogy legközelebb uralkodjon magán. Még jobb, ha kevesebbet iszik.";
			link.l1 = "Köszönöm, tiszt úr.";
			link.l1.go = "exit";
		break;
		
		case "NightAdventure_CitizenHomieOfficer":
			dialog.text = "Nos, mivel nem ragadott fegyvert, ez csak 1500 pezó.";
			link.l1 = "Attól tartok, nem vagyok hajlandó ennyit adni. Nos, tekintve, hogy csak pár napig van itt, azt hiszem, nem fog fájni neki. Talán kevesebbet fog inni.";
			link.l1.go = "NightAdventure_CitizenHomieEnd";
			if(sti(pchar.money) >= 1500)
			{
				link.l2 = "Rendben, kész vagyok letenni az óvadékot.";
				link.l2.go = "NightAdventure_CitizenHomieOfficer_1";
			}
		break;
		
		case "NightAdventure_CitizenHomieOfficer_1":
			AddMoneyToCharacter(pchar, -1500);
			DeleteAttribute(pchar,"GenQuest.NightAdventureToJail");
			pchar.quest.NightAdventure_SeaExit.over = "yes";
			pchar.quest.NightAdventure_JungleExit.over = "yes";
			SetFunctionLocationCondition("NightAdventure_CitizenHomieOK", npchar.City+"_town", false);
			dialog.text = "Elmehetsz a barátodért. Csak figyelmeztesse, hogy legközelebb uralkodjon magán. Vagy még jobb, ha kevesebbet iszik.";
			link.l1 = "Köszönöm, tiszt úr.";
			link.l1.go = "exit";
		break;
		// <-- ночной приключенец
		
		// --> Sinistra Путеводная звезда
		case "PZ_BasTer_ComendantDialog":
			if (CheckAttribute(pchar, "questTemp.PZ_BasTerOpozdal"))
			{
				dialog.text = "Köszönöm, hogy beleegyeztél, hogy eljössz, ahelyett, hogy mészárlást rendeznél. Legalább valaki mostanában értelmesen viselkedik.";
				link.l1 = "Szóval, minek köszönhetem ezt a figyelmet, tiszt úr? Van valami köze ahhoz, hogy egy kínai férfit keresek?";
				link.l1.go = "PZ_BasTer_ComendantDialog_Opozdal_1";
			}
			else
			{
				dialog.text = "Még jó, hogy önként jött hozzánk. Elég volt mostanában a csôcselékbôl.";
				link.l1 = "Nos, mint látja, én nem tartozom az erôszakosok közé. Azonban... miért vagyok itt, biztos úr? Már megkérdeztem az embereit, de nem kaptam választ - talán azért, mert egy bizonyos kínai embert keresek a városban?";
				link.l1.go = "PZ_BasTer_ComendantDialog_1";
			}
			DeleteQuestCondition("PZ_BasTerPeshera");
			npchar.Dialog.Filename = "Common_Prison.c";
			npchar.Dialog.CurrentNode = "First_officer";
		break;
		// <-- Путеводная звезда
		case "Helen_meeting":
			dialog.text = "Hát persze, hogy nem! Kérem, jöjjön be. Mindig szívesen látjuk a börtönünkben. Ezt persze jó értelemben mondom. Szóval, mire van szüksége?";
			link.l1 = "Ó, semmi különös, tudja, csak körülnéztem a városban, ezért bolyongtam ide alkalomadtán.";
			link.l1.go = "exit";
			link.l2 = "Egy kis üzletrôl akartam beszélni.";
			link.l2.go = "quests";
			if (!sti(pchar.questTemp.jailCanMove))
			{
				link.l4 = "Szeretnék bejönni a börtönbe.";
				link.l4.go = "ForGoodMove";		
			}
			NextDiag.TempNode = "First_officer";
		break;
	}
}

void GetChestPlaceName()
{
	string islandId;
	int iTemp = rand(3);
	switch (iTemp)
	{
		case 0: 
			pchar.questTemp.jailCanMove.islandId = "Bermudák";
			pchar.questTemp.jailCanMove.placeId = "Bermudes_Cavern";
		break;
		case 1: 
			pchar.questTemp.jailCanMove.islandId = "Kajmán";
			pchar.questTemp.jailCanMove.placeId = "Caiman_Grot";
		break;
		case 2: 
			pchar.questTemp.jailCanMove.islandId = "Dominika";
			pchar.questTemp.jailCanMove.placeId = "Dominica_Grot";
		break;
		case 3: 
			pchar.questTemp.jailCanMove.islandId = "Terk";
			pchar.questTemp.jailCanMove.placeId = "Terks_Grot";
		break;
	}
}

string GetBanderLocation(ref npchar)
{
    aref	arCommon, arRld, arRld2;
    int	i, n, Qty, Qty2;
	string LocId; 
	string	storeArray [50];
	int howStore = 0;
    makearef(arRld, Locations[FindLocation(npchar.city + "_town")].reload);
	Qty = GetAttributesNum(arRld);
    if (CheckAttribute(pchar, "GenQuest.SeekSpy.Location")) //если взят квест мэра по поиску шпиона
	{
		for (i=0; i<Qty; i++)
		{
    		arCommon = GetAttributeN(arRld, i);
			LocId = arCommon.go;
    		if (findsubstr(LocId, "Common" , 0) != -1 && LocId != pchar.GenQuest.SeekSpy.Location)
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
					if (findsubstr(LocId, "Common" , 0) != -1 && LocId != pchar.GenQuest.SeekSpy.Location && arCommon.name != "reload1") // mitrokosta fix
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
					if (findsubstr(LocId, "Common" , 0) != -1 && arCommon.name != "reload1") // mitrokosta fix
    				{
						storeArray[howStore] = LocId;
						howStore++; 
					}
				}
			}	
		}
	}
	if (howStore == 0) return "none";
	LocId = storeArray[rand(howStore-1)];
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

string GenQuestPrison_GenerateArtefact() // артефакты
{
	string itemID;
	switch(rand(7))
	{
		case 0:
			itemID = "indian_5";
		break;
		case 1:
			itemID = "indian_7"; 
		break;
		case 2:
			itemID = "indian_8"; 
		break;
		case 3:
			itemID = "indian_9"; 
		break;
		case 4:
			itemID = "indian_10"; 
		break;
		case 5:
			itemID = "indian_11"; 
		break;
		case 6:
			itemID = "indian_3"; 
		break;
		case 7:
			itemID = "indian_6"; 
		break;
	}
	return itemID;
}

string GenQuestPrison_GenerateBlade() // клинки и другое
{
	string itemID;
	switch(rand(8))
	{
		case 0:
			itemID = GetGeneratedItem("blade_16");
		break;
		case 1:
			itemID = GetGeneratedItem("blade_15"); 
		break;
		case 2:
			itemID = GetGeneratedItem("blade_13"); 
		break;
		case 3:
			itemID = "cirass2"; 
		break;
		case 4:
			itemID = GetGeneratedItem("blade_10"); 
		break;
		case 5:
			itemID = "spyglass3"; 
		break;
		case 6:
			itemID = "cirass6"; 
		break;
		case 7:
			itemID = "cirass7"; 
		break;
		case 8:
			itemID = "cirass1"; 
		break;	
		
	}
	return itemID;
}
