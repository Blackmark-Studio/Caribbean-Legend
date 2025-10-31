// BOAL новый диалог офицера и компаньона 21/06/06
void ProcessDialogEvent()
{
	ref NPChar, d;
	aref Link, Diag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makeref(d, Dialog);
	makearef(Diag, NPChar.Dialog);
	
	ref    	sld, rItm, rItem;
	string 	attr, attrLoc, sGun, sBullet, attrL, sAttr;
	int    	iTemp, iTax, iFortValue, i;
	aref 	rType;
	
	sAttr = Dialog.CurrentNode;
	if (findsubstr(sAttr, "SetGunBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	NPChar.SetGunBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
 	    Dialog.CurrentNode = "SetGunBullets2";
 	}
	if (findsubstr(sAttr, "SetMusketBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	NPChar.SetMusketBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
 	    Dialog.CurrentNode = "SetMusketBullets2";
 	}
	
	switch(Dialog.CurrentNode)
	{
        case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = RandPhraseSimple("Heh, kapitány, a helyôrség fele most éppen magát üldözi. Bizonyára nem a legjobb alkalom, hogy felvegyék a legénységedbe!", "És átverekedni magunkat a hajóig? Nem, kapitány, majd máskor...");
				link.l1 = RandPhraseSimple("Ahogy kívánod...", "Igazából nem akartalak felvenni."); 
				link.l1.go = "exit";
				break;
			}
			Diag.TempNode = "OnceAgain";
			dialog.text = "Szüksége van egy tisztre, kapitány?";
			if (FindFreeRandomOfficer() > 0)
			{
    			Link.l1 = "Egy tiszt? És miben vagy jó?";
    			Link.l1.go = "Node_2";
			}
			Link.l2 = "Nem, van teljes felszerelésem.";
			Link.l2.go = "Exit";			
		break;
		
		case "CitizenNotBlade":
			dialog.text = "Kapitány, mit csinál? Tegye le a fegyvert, mielôtt nagy bajba kerül!";
			link.l1 = LinkRandPhrase("Jól van.", "Rendben.", "Ne aggódj, elrakom...");
			link.l1.go = "exit";
		break;
		
		case "hired":
			Diag.TempNode = "Hired";
			// только наняли -->
			if (IsCompanion(NPChar))
			{
				Dialog.text = "Ma végre kihajózunk!";
				link.l2 = "Igen... örülök.";
				link.l2.go = "Exit";
				break;
			}
			if (Npchar.location.group == "sit" && !isShipInside(pchar.location))
			{
				dialog.text = "Csak befejezem az italom, kapitány, aztán megyek a hajóra. Ne aggódj - idôben ott leszek.";
				Link.l1 = "Rendben. Ha elkésel, akkor a fedélzetet fogod felmosni!";
				Link.l1.go = "Exit";
				break;
			}
			// только наняли <--
   			dialog.text = "Mit akar, kapitány?";
			// диалог компаньона на корабле.
			if (CheckAttribute(NPChar, "IsCompanionClone"))
			{
				Link.l2 = "Több parancsot kell kiadnom önnek.";
				Link.l2.go = "Companion_Tasks";
				break;
			}
			
			// на Тайясаль
			if (CheckAttribute(pchar, "questTemp.Dolly_Tieyasal") && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				Link.l66 = ""+npchar.name+", egy régi indián városba, Tayasalba megyek. Ez egy veszélyes és szokatlan utazás lesz - egy teleportációs bálványon keresztül. Csatlakozik hozzám?";
				if(npchar.id == "Folke")
				{
					Link.l66 = ""+npchar.name+", Komoly kérésem van a számodra - egy igazi üzlet, öngyilkos, de átkozottul jövedelmezô. Szükségem van egy hûséges emberre egy ôsi indiai városba tartó küldetésre. Velem tartasz?";
				}
				if(npchar.id == "Duran")
				{
					Link.l66 = "Claude, egyszer panaszkodtál, hogy a zsoldosok alulfizetettek.";
				}
				Link.l66.go = "tieyasal";
			}
			
			if (isOfficer(Npchar)) // проверка для кампуса, где слотовые офы
			{
				Link.l2 = "Most hallgasd meg a parancsomat!";
				Link.l2.go = "stay_follow";
			}

           		// boal отчёт о корабле
			if(CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
			{
			    Link.l8 = "Adjon egy átfogó hajójelentést, " + GetStrSmallRegister(XI_ConvertString("kincstárnok")) + ".";
			    Link.l8.go = "QMASTER_1";
			        
			    // Warship. Автозакупка товара
			    if(!CheckAttribute(PChar, "TransferGoods.Enable"))
			    {
				    Link.l11 = "Azt akarom, hogy vásárolj árut, amíg a kolónián tartózkodunk.";
				    Link.l11.go = "TransferGoodsEnable";
			    }
			    else
			    {
				    Link.l11 = "Tudod, már nem kell árut vásárolnunk a gyarmatokon.";
				    Link.l11.go = "TransferGoodsDisable";
			    }
			}
			
			if (pchar.location != "My_Campus") // patch-5
			{
			Link.l4 = "Tiszt, a szolgálataira már nincs szükség.";
			Link.l4.go = "AsYouWish";
			}
			
			
			// по тек локации определим можно ли тут приказать  -->
			if(IsEntity(&loadedLocation))
			{
				if(CheckAttribute(loadedLocation, "fastreload"))
				{
					iTemp = FindColony(loadedLocation.fastreload);
					if(iTemp != -1)
					{
						sld = GetColonyByIndex(iTemp);
						if(sti(sld.HeroOwn) == true && !CheckAttribute(sld, "OfficerIdx"))
						{
							NPChar.ColonyIdx = iTemp;
							Link.l7 = "A város helyettesévé teszlek!";
							Link.l7.go = "Gover_Hire";
						}
					}
				}
			}
			
			Link.l9 = "Semmi. Pihenj!";
			Link.l9.go = "Exit";
		break;
		
		// Тайясаль
		case "tieyasal":
			if(npchar.id == "Folke")
			{
				dialog.text = "A fenébe, kapitány! Azt hittem, az elsô adandó alkalommal megszabadulsz tôlem, de megleptél, mint mindig. Persze, hogy veled vagyok, és köszönöm, hogy ennek az idiótának igazi tengeri farkaséletet adtál!";
				Link.l1 = "Így tovább, "+npchar.name+"!";
				Link.l1.go = "folke_tieyasal";
				break;
			}
			if(npchar.id == "Duran")
			{
				dialog.text = "A zsoldosok panaszkodtak, hogy a zsoldosok rosszul fizetnek. Tényleg ezt mondtam?";
				Link.l1 = "Igen, azt mondtad. Akkor figyelmesen végighallgattalak, és kész vagyok helyrehozni az igazságtalanságot.";
				Link.l1.go = "Duran_tieyasal";
				break;
			}
			dialog.text = LinkRandPhrase("Sajnálom, kapitány, de én nem erre írtam alá. Ne higgye, hogy gyáva vagyok, de nem vagyok hajlandó a biztos halállal szembenézni. Ennyire nem vagyok életunt - még nem. Kirúghatsz, ha akarsz.","Kapitány, elnézését kérem, de - nem. Tengerek, partraszállás, ellenséges városok - ez teljesen rendben van, de én nem akarok ezzel az indián boszorkánysággal szórakozni. Ha felháborít a válaszom, akkor felbonthatja a szerzôdésünket.","Ön lehetetlent akar, kapitány, és ezt maga is tudja. Senki sem fog élve visszajönni, beleértve magát is, úgyhogy passzolok. Ha a visszautasításomat a szerzôdés feltételeinek megszegésének tekinti, akkor felbonthatja a szerzôdést.");
			link.l1 = LinkRandPhrase("Nem hibáztatom magát, biztos úr. Tökéletesen megértem.","Kár, de megértem magát. Ezért is szóltam elôre.","Számítottam rád... De megértem a helyzetét, biztos úr.");
			link.l1.go = "tieyasal_1";
		break;
		
		case "Duran_tieyasal":
			dialog.text = "Heh! Akkor megemelnéd a fizetésemet?";
			Link.l1 = "Kizárt dolog! Egy ôsi indiai városba megyek. A munka öngyilkos, de aranyat fogok ott találni...";
			Link.l1.go = "Duran_tieyasal_2";
		break;
		
		case "Duran_tieyasal_2":
			dialog.text = "Nem érdekel az arany. Megtiszteltetés lenne, ha segíthetnék neked, Kapitány, ahogy egyszer nekem is segítettél. Mikor indulunk?";
			Link.l1 = "Jól mondtad, Claude! Legyetek teljes készenlétben - már nem tart sokáig.";
			Link.l1.go = "Duran_tieyasal_3";
		break;
		
		case "Duran_tieyasal_3":
			DialogExit();
			npchar.quest.Tieyasal = "teleport";
		break;
		
		case "folke_tieyasal":
			Achievment_Set("ach_CL_108");
			DialogExit();
			npchar.quest.Tieyasal = "teleport";
		break;
		
		case "tieyasal_1":
			DialogExit();
			npchar.quest.Tieyasal = "true";
		break;
		
		case "TransferGoodsEnable":
			if(sti(PChar.Ship.Type) == SHIP_NOTUSED)
	        {
				dialog.text = "Kapitány, milyen áru? Elôbb találnunk kell egy hajót!";
				Link.l1 = "Igen, igazad van.";
				Link.l1.go = "Exit";
				Diag.TempNode = "Hired";
				break;
	        }
	        	
			PChar.TransferGoods.Enable = true;
		//	PChar.TransferGoods.TreasurerID = NPChar.id;
			Dialog.text = "Meglesz, "+ GetSexPhrase("uram","miss") +" kapitány!";
			Link.l1 = "Pihenj.";
			Link.l1.go = "TransferGoodsEnable_2";
        break;
        	
		case "TransferGoodsEnable_2":
			Diag.CurrentNode = "Hired";
			DialogExit();
			LaunchTransferGoodsScreen(); // Интерфейс автозакупки товаров
		break;
		
		case "TransferGoodsDisable":
			DeleteAttribute(PChar, "TransferGoods.Enable");
			Dialog.text = "Meglesz, "+ GetSexPhrase("uram","miss") +" kapitány!";
			Link.l1 = "Pihenj.";
			Link.l1.go = "exit";
			Diag.TempNode = "Hired";
		break;
        
		case "ShowParam_exit":
			Diag.CurrentNode = "OnceAgain";
			NPChar.quest.meeting = true;
			DialogExit();
			
			PChar.SystemInfo.OnlyShowCharacter = true;
            LaunchCharacter(NPChar);
		break;
		
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();			
		break;

		case "exit_hire":
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();
			if(CheckAttribute(pchar,"systeminfo.tutorial.Fighter") && Npchar.quest.officertype == "fighter")
			{
				DeleteAttribute(pchar,"systeminfo.tutorial.Fighter");
				LaunchTutorial("Fighter", 1);
			}
		break;

		case "exit_fire":
			//navy -->
			if (CheckAttribute(NPChar, "PGGAi"))
			{
				pchar.questTemp.FiringOfficerIDX = NPChar.index;
				AddDialogExitQuestFunction("PGG_FireOfficer");
				DialogExit();			
				break;
			}
			//navy <--
			Diag.TempNode = "Fired";
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");

			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;

			DialogExit();			
		break;
		
		// boal 29.05.04 офицер хочет свалить -->
        case "WantToGo":
			if (npchar.id == "Duran" && !CheckAttribute(pchar, "questTemp.SKD_SobytieKlodDuran"))
			{
				SetTimerCondition("SKD_DuranTavern", 0, 0, 30, false);
				pchar.questTemp.SKD_SobytieKlodDuran = true;
			}
			chrDisableReloadToLocation = false;
			Diag.TempNode = "Hired";
			dialog.text = LinkRandPhrase(LinkRandPhrase("Kapitány, tudja, én... Nos, megkérném, hogy váltson le. Itt az ideje, hogy megállapodjak, megházasodjak és gyerekeket csináljak. Még mindig nincs saját otthonom, ha megöregszem, nem lesz, aki egy pohár vizet hozzon nekem.","Kapitány úr, kérem, engedje meg, hogy lemondjak. Ennyi éven át lógtam a világ körül, és még mindig nem láttam semmit. Csak egy új életet akarok élni, levetni a horgonyt, és más szemszögbôl látni a világot.","Kapitány úr, a tengerészeti szolgálat bizonyára szép dolog, jó haszon és kaland, de eljött az ideje, hogy magamra is gondoljak. Tudod, horgonyt vetni egy csendes kikötôben, házat venni, gyerekeket vállalni. Kérem, engedjen el."), LinkRandPhrase("Kapitány, tudja, nagyon sajnálom, de elegem van a sok szolgálatból, ôrségbôl és fegyelmezésbôl. Tudod, csak szeretnék legalább egy ideig szabad életet élni, de tisztában vagyok vele, hogy nem fogsz várni rám, úgyhogy... Elbocsátanál?","Kapitány, tudja... Van egy kis hajó, amit megengedhetek magamnak, szóval... Azt hiszem, itt az ideje, hogy saját vállalkozásba kezdjek. Kérem, el tudna engedni?","Kapitány, most ajánlottak fel egy állást a kikötôben. Valójában már régóta vágyom arra, hogy horgonyt vessek és házaséletet éljek. Kérem, engedje meg, hogy elmenjek. Tényleg nem hagyhatok ki egy ilyen lehetôséget."), LinkRandPhrase("Kapitány úr, nagyon beteg vagyok a tengertôl. Az orvosok folyton azt mondják, hogy ez egy idioszinkrázia. Kérem, az Isten szerelmére, engedjen el, különben egyszer csak átugrom a fedélzetre.","Kapitány, azt hiszem, itt az ideje, hogy letelepedjek, és találjak magamnak egy nyugodtabb helyet. Tudja, én félek. Félek a kóbor golyóktól, félek, hogy meghalok egy beszállás során. Imádkozom az Úrhoz, hogy tartson életben, és amikor becsukom a szemem, látom az összes ártatlan lelket, akit megöltem. Könyörögnek, hogy kíméljem meg ôket... Kérlek, mutass egy kis könyörületet, és engedj el.","Kapitány, régi sebeim fájnak, és a nemrég szerzett zúzódás minden egyes nap emlékeztet magára. Hamarosan elbocsát, és utána ki fog alkalmazni? Kérem, engedjen el, összefoltozom magam, és keresek egy nyugodtabb helyet."));
			Link.l1 = RandPhraseSimple(LinkRandPhrase("Végül mindannyian elmennek. Rendben, szabadon távozhatsz.","Megértem az érvelését. Elôbb-utóbb minden véget ér. Nos, akkor menj... és ne haragudj, ha valaha is megbántottalak.","Már megint ez? Szándékosan a lehetô legrosszabb pillanatot választottad, hogy elhagyj, igaz? Mindegy. Búcsúzz el."), LinkRandPhrase("Nehéz elhinni, amit mondasz... Rendben, pakolj össze és menj.","Te? Nem számítottam rá... Ennyi idô után, amikor egymás ellen harcoltunk... Hát, én nem állítalak meg. Isten éltessen.","Komolynak hangzik. Sok szerencsét kívánok, tudd, hogy hiányozni fogsz."));				
			Link.l1.go = "WantToGo_free";
			if (sti(Pchar.money) >= sti(NPChar.rank)*250)
			{
				Link.l2 = LinkRandPhrase("Értem... Szóval így állunk, mi? És én számítottam rád... Nos, ha már eldöntötted, akkor váljanak el útjaink. Vegye el a "+sti(NPChar.rank)*250+" pezót a hûséges szolgálatáért. És ne haragudj, ha valaha is megbántottalak.", "Nos, én nem neheztelek és nem emlékszem semmi rosszra. Ha így döntöttél, akkor menj. És vigyen "+sti(NPChar.rank)*250+" pezót, hogy újrakezdhesse, biztosan jól fog jönni.", "Értem... Hát, elôbb vagy utóbb ennek meg kellett történnie. Adok neked "+sti(NPChar.rank)*250+" pezót, hogy rendezd az életed. És vigyázz az egészségedre is, a tengerészeti szolgálat tele van megpróbáltatásokkal..."); 
				Link.l2.go = "Im_kind_A2_1";
			}
			Link.l3 = LinkRandPhrase("Szóval azt mondod... Nem veszed észre, hogy azzal, hogy most elmész, egyszerûen hátba szúrsz engem? Nem engedhetlek el most, eszedbe se jusson.", "Na ez aztán a hír! Tudod, az embereknek az ilyesmirôl elôre értesíteniük kellene engem! Szóval felejtsd el egy idôre a magánéletedet! Ha eljön az ideje, javasolni fogom neked, mikor vonulj vissza.", "Nincs lemondás. Mindenkit számon tartok. Nem engedhetek el mindenkit csak a személyes kívánsága miatt. Szolgáljatok, amíg mérlegelem, hogy megérdemlitek-e a szabadságot.");	
			Link.l3.go = "WantToGo_Stay";
		break;
		
		case "Im_kind_A2_1":
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*250)));
			ChangeOfficersLoyality("good_all", 1);
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			ChangeCharacterComplexReputation(pchar,"authority", 0.5);
			dialog.text = "Köszönöm, kapitány! Egy igazán váratlan nagylelkûség... Tudod, még mindig megvan néhány holmid, talán szeretnéd visszakapni ôket?";
			Link.l1 = "Talán... Manapság nem olyan könnyû jó pengét találni.";
			Link.l1.go = "Get_out_А2_chang";
			Link.l2 = "Ó, ne fáradjon. Tartsd meg ôket, mint emléket a szolgálataidról.";
			Link.l2.go = "WantToGo_free";
		break;
		
		case "WantToGo_Stay":
			dialog.text = RandPhraseSimple("De hogyan, kapitány úr? Még a rabszolgákat is a partra küldik. Én pedig nem vagyok rabszolga, így magam dönthetek a sorsomról!", "Kapitány, én mindvégig hûségesen szolgáltam önt. Nem érdemeltem meg a jogot, hogy magam dönthessek a sorsomról?");
			Link.l1 = LinkRandPhrase("Látom, hogy nem tarthatlak meg úgy, ahogy van. Rendben, mit szólnál egy kis anyagi támogatáshoz? Ez sosem fog fájni, abból a pénzbôl építhetsz magadnak egy hangulatos otthont egy csendes kikötôben, vagy gondoskodhatsz az egészségedrôl.", "Rendben, fogalmazzunk így. Milyen összeg vehetne rá, hogy átgondold a döntésedet?", "Igazad van. De mi van az egyszeri pénzbeli juttatással, az megváltoztatná a véleményedet?");
			Link.l1.go = "WantToGo_Stay_2";
			Link.l2 = PCharRepPhrase(	
				RandPhraseSimple("Ó, nem, barátom, itt tévedsz... Amíg a kocsmákban vesztegetted az idôdet a kelyhek után hajkurászva, addig magad dönthettél, de amint a hajóm fedélzetére léptél, akkor a kezembe adtad a sorsodat.", "Hmm. Na, ez aztán a komoly kijelentés. Úgy látszik, elfelejtetted, hogyan találtam rád, egy büdös kocsmában, egy réz nélkül a zsebedben. Még egyetlen aranypénzt sem lehet neked mutatni, mert azonnal rumot csinálsz belôle. 'Döntsd el a sorsomat...' Pfff! Micsoda vicc!"),
				LinkRandPhrase("Amíg a szolgálatomban állsz, addig én hozom a döntéseket. És most kérlek, térj vissza a kötelességedhez, mielôtt túlságosan feldühítesz!", "Hmm. Na, ez aztán a komoly kijelentés. De még nem dolgoztad le a neked elôre kifizetett pénzt. Tehát a demarche-odat lehet zsarolási kísérletnek tekinteni, igaz?", "Ó, értem... Mit is mondanak a hajószabályzatban? Itt a második bekezdés: 'Aki engedély nélkül próbál távozni, azt egy elhagyatott parton fogják kirakni egyetlen zacskó puskaporral, egy flaska vízzel, egy pisztollyal és egyetlen golyóval.' Nocsak, hogy tetszene ez?"));	
			Link.l2.go = "WantToGo_Stay_force";
		break;
		
	case "WantToGo_Stay_2":
		dialog.text = LinkRandPhrase("Nos, ez egy másik történet. "+sti(NPChar.rank)*500+" pezó a szögre, és én veled maradok.", "Nos, talán "+sti(NPChar.rank)*500+" pesoért maradhatnék, azt hiszem.", "Hát, ha úgy vesszük, "+sti(NPChar.rank)*500+" pesoért folytathatnám a szolgálatomat.");
		if (sti(Pchar.money) >= sti(NPChar.rank)*500)
		{
			Link.l1 = RandPhraseSimple("Rendben, egyetértek.", "Rendben. Bár kevesebbet is kérhetnél.", "Látom, elég nagy étvágyad van! De ígéretet tettem neked, nem igaz, és tartom magam a szavamhoz.");	
			Link.l1.go = "WantToGo_Stay_ForMoney";
		}
		Link.l2 = LinkRandPhrase("Ez egyszerûen túl sok. Ennyiért két tisztet is felvehetnék. Talán egyszerûbb lenne, ha elengednélek.", "Nos, maga aztán tényleg nagyra tartja magát. Rendben, elengedem. De majd meglátod magad, ha egyszer szabadlábon leszel, hogy az életed nem lesz olyan felhôtlen, mint amilyenre számítottál.", "Nem fogok ilyen pénzt fizetni. Elmehetsz, de ne is kérj vissza, nem bocsátom meg az árulást.");				
		Link.l2.go = "WantToGo_free";
	break;
	
	case "WantToGo_Stay_force":
		Npchar.loyality = makeint(Npchar.loyality) - 2;
		dialog.text = "Rendben, ha így mondod, akkor maradok. De tudd, hogy ezzel a saját akaratom ellen teszek.";
		Link.l1 = LinkRandPhrase("Nagyon jó. Térjen vissza a feladataihoz, és késôbb folytatjuk ezt a beszélgetést.", "Vissza a hajóra. És legközelebb gondolja meg újra, mielôtt nyugdíjazást kér.", "Valóban. A kötelesség az kötelesség, és még nem kellene a fantáziádnak hódolnod.");
		Link.l1.go = "exit";
	break;
	
	case "WantToGo_Stay_ForMoney":
		Diag.TempNode = "Hired";
		NPChar.greeting = "Gr_Officer";
		if(NPChar.id == "Duran") NPChar.greeting = "Duran_officer";
		ChangeCharacterComplexReputation(pchar,"authority", 0.2);
		AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*500)));
		Npchar.loyality = makeint(Npchar.loyality) + 1;    
		Diag.CurrentNode = Diag.TempNode;
		NPChar.quest.meeting = true;
		DialogExit();
		NPChar.location = "none";
		LAi_SetOfficerType(NPChar);
	break;
	
	case "WantToGo_free":
		//navy -->
		if (CheckAttribute(NPChar, "PGGAi"))
		{	
			pchar.questTemp.FiringOfficerIDX = NPChar.index;
			AddDialogExitQuestFunction("PGG_FireOfficer");
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();	
			break;
		}
		//navy <--
		Diag.TempNode = "WantToGo_free_Yet";
		Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
		AddDialogExitQuestFunction("LandEnc_OfficerFired");
		Diag.CurrentNode = Diag.TempNode;
		NPChar.quest.meeting = true;
		DialogExit();
	break;
	
	case "WantToGo_free_Yet":
		Diag.TempNode = "WantToGo_free_Yet";
		dialog.text = LinkRandPhrase ("Ezt nem hiszem el! Köszönöm, kapitány, ez olyan nagy könnyebbséget jelent nekem.", "Köszönöm, kapitány, hogy nem próbált meg lefogni. Tudja, tényleg szeretnék más dolgokat is kipróbálni az életben.", "Heh, most már hozzá kell szoknom az újonnan szerzett szabadságomhoz. Csak most kezdtem rájönni, mennyire elegem volt a flottaszolgálatból.");	
		Link.l1 = RandPhraseSimple("Nos, sok szerencsét neked.", "Most már szabad vagy. A szolgálatodnak vége.");
		Link.l1.go = "exit";
	break;
	// boal 29.05.04 офицер хочет свалить <--
		
	// пассажир возмущен игроком и сваливает -->
	case "WantToRemove":
		if (npchar.id == "Duran" && !CheckAttribute(pchar, "questTemp.SKD_SobytieKlodDuran"))
		{
			SetTimerCondition("SKD_DuranTavern", 0, 0, 30, false);
			pchar.questTemp.SKD_SobytieKlodDuran = true;
		}
        chrDisableReloadToLocation = false;
		if (Npchar.alignment == "good")
		{
			dialog.text = RandPhraseSimple(LinkRandPhrase("Kapitány, nem akarok a lelkiismeretem ellen cselekedni, és részt venni a rablásban.","Kapitány, nem kívánok többé részt venni a lázadásaidban. Tiszt vagyok, nem mészáros.","Kapitány, az önök bandita módszerei lehetetlenné teszik, hogy a legénységükben maradjak."), LinkRandPhrase("Kapitány, be kell ismernem, hogy az önöknél való alkalmazásom kiábrándító hiba volt. Nem vagyok hajlandó feláldozni a hírnevemet semmilyen pénzért.","Kapitány, ön a hajójára gyûjtötte az Újvilág leggonoszabb gyilkosait. Egy tisztességes embernek még rájuk nézni is undorító. Nem akarok tovább szolgálni egy ilyen legénységgel.","Kapitány, ön egy egész gazemberekbôl álló legénységet vett fel, nincs egyetlen tisztességes ember sem, akivel elbeszélgethetnék. Megvetem az ilyen szolgálatot.")) + " Viszlát.";
			Link.l1 = "Micsoda?! Ez egy katonai hajó, nem egy iskola! Akkor menj a pokolba!";
			Link.l1.go = "exit_fire_1";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l2 = "Tudtam, hogy hamarosan elmész... ez a szolgáltatás nem neked való. De ne vádolj engem semmivel. Itt van "+sti(NPChar.rank)*500+" pezó, jól fog jönni, amíg a kedvedre való munkát keresel.";
				Link.l2.go = "Im_kind_A2";
			}
			Link.l3 = LinkRandPhrase("Ó, szóval ezt a dallamot énekeled most. És mi van a részeddel minden egyes rablásból, nem égeti a kezed? Vagy azt tervezed, hogy visszavonulsz egy kolostorba, hogy bûneid bocsánatáért imádkozz? Akkor szólj egy szót értünk is! Ha-ha-ha-ha-ha-ha-ha-ha!", "Hmm. Na, ez aztán a komoly kijelentés. És hová nézett az ártatlan lelkiismereted, amíg együtt raboltuk ki a kereskedôket? Hogy akarod tisztára mosni? Vagy elárulsz minket, hogy tisztességes társaságban lógjunk az akasztófán?", "Ó, bravó! Úgy látszik, elfelejtetted, hogyan találtam rád, egy büdös kocsmában, egy réz nélkül a zsebedben. Csak hogy tudd, tisztként egy rézpénzt sem érsz. Maga értéktelen!");
			Link.l3.go = "WantToGo_stop";
		}
		else
		{
            dialog.text = RandPhraseSimple(LinkRandPhrase("Kapitány, nagyon nem szeretem az ön nemes játékait, és nem fogom feladni a szokásaimat az ön nyugalma kedvéért. Viszontlátásra.","Kapitány, nem maradhatok tovább a szolgálatában. Már így is annyi idôt elvesztegettem. Egyszerû magánzónak lenni már egy vagyont hozna nekem. Elmegyek.","Kapitány, az emberei undorodnak tôlem. Egyetlen tisztességes ember sincs, csak csicskások, olyan sincs, akivel társaságot lehetne alkotni, hogy együtt igyunk. Elmegyek."), LinkRandPhrase("Kapitány, veterán tiszt vagyok, és a hajója inkább hasonlít egy teherhajóra. Nem szeretem az ilyen szolgálatot. Viszontlátásra.","Kapitány, az egész legénysége csupa dísznadrág, nincs egyetlen ember sem, akivel inni vagy beszélgetni lehetne. Erôs ellenszenvvel viseltetem az ilyen kiszolgálás iránt. Viszontlátásra.","Kapitány, régebben azt hittem, hogy egy igazi korzó alatt szolgálok, de mi csak jótékonykodunk! Nem akarom tovább vesztegetni az idômet. Elmegyek."));
			Link.l1 = RandPhraseSimple("Értem. Figyelembe véve a hozzáállásodat, ennek elôbb-utóbb meg kellett volna történnie. Rendben, nem tartalak fel.", "A kijelentése nem volt váratlan. Ôszintén szólva, már jó ideje elégedetlen vagyok a hozzáállásoddal.") + " Sok szerencsét.";
			Link.l1.go = "exit_fire_1";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l2 = "Tudtam, hogy hamarosan elmész... ez a szolgáltatás nem neked való. De ne vádolj engem semmivel. Itt van "+sti(NPChar.rank)*500+" pezó, jól fog jönni, amíg új munkát keresel.";
				Link.l2.go = "Im_kind_A2";
			}
			Link.l3 = RandPhraseSimple("Hmm. Ez egy komoly kijelentés. De még nem dolgoztad le az összes elôre kifizetett pénzt. Tehát a demarche-od zsarolási kísérletnek tekinthetô, igaz?", "Ó, értem... Mit mondanak a hajó szabályai? Itt, a második bekezdés: 'Aki engedély nélkül próbál távozni, azt egy elhagyatott parton fogják partra tenni egyetlen zacskó puskaporral, egy flaska vízzel, egy pisztollyal és egyetlen golyóval.' Nocsak, mit szólna hozzá?");
			Link.l3.go = "WantToGo_stop";
		}
		break;
		
		case "WantToGo_stop":
			if (Npchar.alignment == "good")
			{
				dialog.text = LinkRandPhrase("Meg se próbálj sértegetni! Én pénzért dolgozom, de még mindig jogom van ahhoz, hogy olyan munkát válasszak, ami tetszik nekem!", "Szabad ember vagyok! És jogom van új munkát vállalni, amikor csak akarok!", "Nem vagyok rabszolga, hogy ételért dolgozzak, így a lelkiismeretem tiszta! De rablásokban többé nem veszek részt!");
				Link.l1 = "Nos, valójában tévedsz... Amíg a kocsmában ittál, addig olyan munkát választhattál, amilyet csak akartál... De amint a hajóm fedélzetére léptél, az egyetlen visszaútad egy ágyúgolyó lett, ami szétzúzza a nyakadat... És kitépett nyelvvel, hogy a másvilágon ne fecsegj ki semmit...";
				if (makeint(Pchar.Rank) > makeint(NPchar.Rank))
				{
					Link.l1.go = "WantToGo_stop_stay";
				}
				else
				{
					Link.l1.go = "WantToGo_stop_fight";	
				}
				Link.l2 = "Jól van, rendben. Elmehetsz... De Isten ments, hogy a nyílt tengeren találkozzunk. Esküszöm, meg fogod bánni azt a pillanatot, amikor úgy döntöttél, hogy nem maradsz mellettem.";
				Link.l2.go = "exit_fire_5";
			}
			else
			{
				dialog.text = LinkRandPhrase("Meg se próbálj megfélemlíteni! Pénzért dolgozom, de még mindig jogom van ahhoz, hogy a kedvemre való munkát válasszam!", "Szabad ember vagyok! És jogom van új munkát vállalni, amikor csak akarok!", "Nem vagyok a rabszolgád! És nem fogok tovább nyomorúságos életet élni a régi dézsádon!");
				Link.l1 = "Nos, valójában tévedsz... Amíg a kocsmában ittál, addig olyan munkát választhattál, amilyet csak akartál... De amint a hajóm fedélzetére léptél, az egyetlen visszaútad egy ágyúgolyó lett, ami szétzúzza a nyakadat... És kitépett nyelvvel, hogy a másvilágon ne fecsegj ki semmit...";
				// belamour legendary edition можно запугать офицера -->
				//if (makeint(Pchar.Rank) > makeint(NPchar.Rank) || CheckCharacterPerk(pchar, "IronWill"))
				if (makeint(Pchar.Rank) > makeint(NPchar.Rank))
				{
					Link.l1.go = "WantToGo_stop_stay";
				}
				else
				{
					Link.l1.go = "WantToGo_stop_fight";	
				}
				Link.l2 = "Jól van, rendben. Elmehetsz... De Isten ments, hogy a nyílt tengeren találkozzunk. Esküszöm, meg fogod bánni azt a pillanatot, amikor úgy döntöttél, hogy nem maradsz mellettem.";
				Link.l2.go = "exit_fire_5";
			}
		break;
		
		case "WantToGo_stop_stay":
			dialog.text = RandPhraseSimple("Ha így mondod, maradok, egyszerûen nincs más választásom. De ne feledje, hogy ezt nem önszántamból teszem...", "Rendben, ha így mondod, maradok. De tudd, hogy ezzel a saját akaratom ellenére teszem.");
			Link.l1 = RandPhraseSimple("Semmi baj... Szolgálj, amíg eldöntöm, mikor engedlek el.", "Ez jó. Szolgálj tovább... Majd én eldöntöm, mikor engedlek el.");
			Link.l1.go = "WantToGo_Munity"; //этот линк ведет к бегству
		break;
		
		case "WantToGo_stop_fight":
			dialog.text = NPCharRepPhrase(NPChar, "Soha nem kényszerítesz arra, hogy meggondoljam magam! Nincs jogod rabszolgaként tartani engem! Elmegyek, maradj távol, vagy véged van!", "Azt hiszed, megijeszthetsz egy veterán tisztet?! Nem egyszer voltam már hajszál híján a halálnak. És ha így nézzük, sokkal jobb egy tisztességes csatában meghalni, mint egy véres fosztogatás közben!");
			Link.l1 = NPCharRepPhrase(NPChar, "Nos... mindenki maga választja meg a sorsát. Remélem, imádkoztál, mielôtt hozzám jöttél.", "Ha tudtam volna, hogy ez fog történni, amikor felvettelek a kocsmánál, inkább hagytalak volna lógni az akasztófán. És most még nem késô elintézni...");
			Link.l1.go = "WantToGo_stop_fight_1";
			Link.l2 = NPCharRepPhrase(NPChar, "Hát, elmehetsz, ha ennyire szükséged van a szabadságodra. De én nem adok neked semmilyen ajánlást.", "Rendben. Elmehetsz... De Isten ments, hogy a nyílt tengeren találkozzunk. Esküszöm, meg fogod bánni a pillanatot, amikor úgy döntöttél, hogy nem maradsz mellettem.");
			Link.l2.go = "exit_fire_5";	
		break;
		
		case "WantToGo_stop_fight_1":
			ChangeOfficersLoyality("bad_all", 1);
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			ChangeCharacterComplexReputation(pchar,"authority", -1);
			dialog.text = NPCharRepPhrase(NPChar, "Ne félemlíts már meg! Ki merne kiállni ellenem a balekjaid közül? Ha én lennék a kapitány, mostanra már a pénzben hemperegnének! És azok után, hogy ennyi jótékonysági akcióba kezdtél, attól félsz, hogy a legénységed az én oldalamra áll?!", "Hagyd el a szokásaidat, nem fogsz megijeszteni! Viszlát!");
			Link.l1 = NPCharRepPhrase(NPChar, "Nem, haver, nem fogsz elég sokáig élni ahhoz, hogy az akasztófára kerülj. Ez a luxus nem neked való...", "Ne olyan gyorsan haver, még mindig nem vagyunk kvittek, tartozol nekem.");
			Link.l1.go = "Get_out_fight";
		break;	
		///////////////////////////////////////////////////////////////////////////////////
		case "WantToGo_Munity":	//zagolski. отыгрыш бегство офицера
			Diag.TempNode = "Hired";
			// belamour legendary edition в ближайшее время не подойдет от страха
			/* if(CheckCharacterPerk(pchar, "IronWill"))
			{
				Npchar.loyality = makeint(Npchar.loyality) + 3 + hrand(sti(GetSummonSkillFromNameToOld(pchar,SKILL_FORTUNE)+GetSummonSkillFromNameToOld(pchar,SKILL_LEADERSHIP)));
				log_info(GetFullName(Npchar)+" növelte a hûségét");
				log_testinfo("Loyalty has become: " + Npchar.loyality + " of " + MAX_LOYALITY);
			}
			else
			{ */
				if (!CheckAttribute(pchar, "questTemp.MutinyOfficerIDX"))
				{
					pchar.questTemp.MutinyOfficerIDX = npchar.index;
					npchar.quest.Mutiny = true; // mitrokosta доп защита от багов
					SetFunctionTimerCondition("mOfficer_fc", 0, 0, 1, false);
				}
			//}
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			NPChar.location = "none";
			LAi_SetOfficerType(NPChar);
			DialogExit();
		break;
		////////////////////////////////////////////////////////////////////
		// пассажир возмущен игроком и сваливает <--
		
		case "Node_2":
			dialog.text = NPCharRepPhrase(Npchar, RandSwear() + "Én vagyok a legjobb "+ XI_ConvertString(Npchar.quest.officertype) + " ezeken a vizeken. " + Npchar.quest.officertype_2 + "És kész vagyok szívességet tenni neked és szolgálni alattad.",
                                    "Nos, azt mondják, nem vagyok rossz " + XI_ConvertString(Npchar.quest.officertype) + ". " + Npchar.quest.officertype_2 + "Vigyél fel a hajódra, kapitány, és gyôzôdj meg róla a saját szemeddel.");
			Link.l1 = "És mennyit akarsz?";
			Link.l1.go = "price";
			Link.l2 = "És miféle szakember vagy te?";
			Link.l2.go = "ShowParam_exit";
			Link.l3 = "Sajnos, már van egy " + XI_ConvertString(Npchar.quest.officertype) + ".";
			Link.l3.go = "Exit";
		break;

		case "OnceAgain":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = RandPhraseSimple("Heh, kapitány, a fél helyôrség magát üldözi. Bizonyára nem a legjobb alkalom, hogy felvegyék a legénységedbe!", "És átverekedni magunkat a hajóig? Nem, kapitány, majd máskor...");
				link.l1 = RandPhraseSimple("Ahogy kívánod...", "Igazából nem akartalak felvenni."); 
				link.l1.go = "exit";
				break;
			}
			Diag.TempNode = "OnceAgain";
			dialog.text = "Meggondolta magát, kapitány? Úgy döntött, hogy egy új " + XI_ConvertString(Npchar.quest.officertype) + " nem ártana?";
			// boal -->
			if (FindFreeRandomOfficer() > 0)
			{
                Link.l1 = "Valami ilyesmi. Mennyit akarsz?";
                Link.l1.go = "price";
			}
			Link.l2 = "És mire vagy képes?";
			Link.l2.go = "ShowParam_exit";
			// boal <--
			Link.l3 = "Van egy teljes készletem. Viszlát.";
			Link.l3.go = "exit";
		break;

		case "price":
			dialog.text = "Azt hiszem, a " + Npchar.quest.OfficerPrice + " pezóban megegyezhetünk.";
			if(Npchar.rank >= 15)
			{
				dialog.text = "Azt hiszem, megegyezhetünk a " + (makeint(Npchar.quest.OfficerPrice) / 100 + 30) + " dubloonokban.";
			}	
			Link.l1 = "Nem túl sok ez egy kicsit?";
			Link.l1.go = "trade";
			Link.l2 = "Egyetértek. Tekintsd magad a legénység tagjának.";
			Link.l2.go = "hire";
			Link.l3 = "Nem éred meg ezt a pénzt.";
			Link.l3.go = "exit";
		break;

		case "trade":
			if (GetSummonSkillFromNameToOld(pchar, SKILL_COMMERCE) >= Rand(12) && (sti(Npchar.quest.OfficerPrice) - GetCharacterSkillToOld(Pchar, "commerce")*100) >= sti(Npchar.quest.OfficerLowPrice))// bug fix
			{
				Npchar.quest.OfficerPrice = makeint(makeint(Npchar.quest.OfficerPrice) - GetCharacterSkillToOld(Pchar, "commerce")*100); // пусть будет коммерция перса голой
				dialog.text = "Rendben... Azt hiszem, még a " + Npchar.quest.OfficerPrice + " pezóban is egyet tudnék érteni. Mit szólsz hozzá?";
				if(Npchar.rank >= 15)
				{
					dialog.text = "Azt hiszem, még a " + (makeint(Npchar.quest.OfficerPrice) / 100 + 30) + " dublonokkal is egyet tudnék érteni. Mit szólsz hozzá?";
				}
				Link.l1 = "Így már jobb. Benne vagy.";
				Link.l1.go = "hire";				
				Link.l2 = "Még mindig úgy gondolom, hogy ez egy kicsit sok. Viszlát.";
				Link.l2.go = "exit";
			}
			else
			{
				dialog.text = "Sajnálom, kapitány, de pontosan annyit érek, amennyit kértem. Ha ez túl sok neked, akkor keress valaki mást.";
				Link.l1 = "Rendben, egyetértek. Elviszlek.";
				Link.l1.go = "hire";				
				Link.l2 = "Ezt fogom tenni. Viszontlátásra.";
				Link.l2.go = "exit";
			}
		break;

		case "hire":
			dialog.text = "Látom, kevés a pénze, kapitány! Sajnálom, de én nem dolgozom hitelben.";
			Link.l1 = "Ó, az ördögbe!";
			Link.l1.go = "Exit";
			if(Npchar.rank < 15 && makeint(Pchar.money) >= makeint(Npchar.quest.OfficerPrice))
			{
				AddMoneyToCharacter(Pchar, -(makeint(Npchar.quest.OfficerPrice)));
				Diag.TempNode = "OnboardSoon";
				dialog.text = "Köszönöm, kapitány. Nem fogja megbánni a döntését.";
				Link.l1 = "Remélem is.";
				Link.l1.go = "Exit_hire";								
			}
			if(Npchar.rank >= 15 && PCharDublonsTotal() >= makeint((makeint(Npchar.quest.OfficerPrice) / 100 + 30)))
			{
				RemoveDublonsFromPCharTotal(makeint((makeint(Npchar.quest.OfficerPrice) / 100 + 30)));
				Diag.TempNode = "OnboardSoon";
				dialog.text = "Köszönöm, kapitány. Nem fogja megbánni a döntését.";
				Link.l1 = "Remélem is.";
				Link.l1.go = "Exit_hire";								
			}
		break;

		case "OnboardSoon":			
			Diag.TempNode = "OnboardSoon";
			dialog.text = "Csak befejezem az italomat, kapitány, aztán megyek a hajóra. Ne aggódjon, idôben odaérek.";
			Link.l1 = "Rendben. Ha elkésel, akkor a fedélzetet fogod felmosni!";
			Link.l1.go = "Exit";											
		break;
        
		case "QMASTER_1":
			if(sti(PChar.Ship.Type) == SHIP_NOTUSED)
			{
				dialog.text = "Kapitány, de magának nincs hajója!";
				Link.l1 = "Köszönöm, hogy emlékeztetett...";
				Link.l1.go = "Exit";
				Diag.TempNode = "Hired";
				break;
			}
			// Rebbebion, добавил фикс отображения знака процента
			dialog.text = "A patkányok maximális aktivitása az utazás során " +
			FloatToString(50.0 / (2.0+GetSummonSkillFromNameToOld(PChar, SKILL_REPAIR) + GetSummonSkillFromNameToOld(PChar,SKILL_SNEAK)), 1) +
			"%% a teljes rakomány mennyiségébôl. A "+GetCrewQuantity(PChar) + " hajósok számára napi " + makeint((GetCrewQuantity(PChar)+6) / 10) + " élelemre lesz szükségünk. Ez a szállított rabszolgákat nem számítva.";
			Link.l1 = "Köszönjük!";
			Link.l1.go = "Exit";
			Diag.TempNode = "Hired";
		break;
        
        // boal 05.09.03 offecer need to go to abordage -->
        case "stay_follow":
            dialog.text = "Mik a parancsaid?";
            Link.l1 = "Álljatok ide!";
            Link.l1.go = "Boal_Stay";
            Link.l2 = "Kövessetek és ne maradjatok le!";
            Link.l2.go = "Boal_Follow";
            // boal 05.09.03 offecer need to go to abordage <--
			if (npchar.id == "OffMushketer")
			{
				Link.l3 = "Azt akarom, hogy bizonyos távolságban maradjatok a célponttól.";
				Link.l3.go = "TargetDistance";
			}
			
			if(CheckAttribute(NPChar, "equip.gun"))
			{
				if(CheckAttribute(NPChar, "chr_ai.gun.bulletNum") && sti(NPChar.chr_ai.gun.bulletNum) > 1)
				{
					Link.l4 = "Meg kell változtatnunk a lôszer típusát a lôfegyveredhez.";
					Link.l4.go = "SetGunBullets";
				}	
			}
			if(CheckAttribute(NPChar, "equip.musket"))
			{
				if(CheckAttribute(NPChar, "chr_ai.musket.bulletNum") && sti(NPChar.chr_ai.musket.bulletNum) > 1)
				{
					Link.l5 = "Meg kell változtatnunk a lôszer típusát a muskétádhoz.";
					Link.l5.go = "SetMusketBullets";
				}
					Link.l6 = "Meg kell változtatnunk a harci fegyvertípusodat.";
					Link.l6.go = "SetPriorityMode";
			}
		break;

		case "SetGunBullets":
			Dialog.Text = "Válaszd kia lôszertípust:";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(NPChar.chr_ai.gun.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetConvertStr(rItem.name, "ItemsDescribe.txt");
				Link.(attrL).go = "SetGunBullets1_" + i;
			}
		break;	

		case "SetGunBullets2":
			i = sti(NPChar.SetGunBullets) + 1; 
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(NPChar, GUN_ITEM_TYPE, sBullet);
			LAi_GunSetUnload(NPChar, GUN_ITEM_TYPE);
			Diag.CurrentNode = Diag.TempNode;
			rItem = ItemsFromID(sBullet);
			notification(GetFullName(NPChar)+" "+XI_ConvertString("AmmoSelectNotif")+GetConvertStr(rItem.name, "ItemsDescribe.txt")+"", "AmmoSelect");
			DeleteAttribute(NPChar,"SetGunBullets");
			DialogExit();
		break;
		
		case "SetMusketBullets":
			Dialog.Text = "Válaszd kia lôszertípust:";
			sGun = GetCharacterEquipByGroup(NPChar, MUSKET_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(NPChar.chr_ai.musket.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetConvertStr(rItem.name, "ItemsDescribe.txt");
				Link.(attrL).go = "SetMusketBullets1_" + i;
			}
		break;	

		case "SetMusketBullets2":
			i = sti(NPChar.SetMusketBullets) + 1; 
			sGun = GetCharacterEquipByGroup(NPChar, MUSKET_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(NPChar, MUSKET_ITEM_TYPE, sBullet);
			LAi_GunSetUnload(NPChar, MUSKET_ITEM_TYPE);
			Diag.CurrentNode = Diag.TempNode;
			rItem = ItemsFromID(sBullet);
			notification(GetFullName(NPChar)+" "+XI_ConvertString("AmmoSelectNotif")+GetConvertStr(rItem.name, "ItemsDescribe.txt")+"", "AmmoSelect");
			DeleteAttribute(NPChar,"SetMusketBullets");
			DialogExit();
		break;
		
		case "SetPriorityMode":
			Dialog.Text = "A harc elején használni fogod:";
			Link.l1 = "Penge";
			Link.l1.go = "BladePriorityMode";
			Link.l2 = "Muskéta";
			Link.l2.go = "MusketPriorityMode";
		break;
		
		case "BladePriorityMode":
            SetPriorityMode(NPChar, 1);
			DialogExit();
		break;
		
		case "MusketPriorityMode":
			SetPriorityMode(NPChar, 2);
			DialogExit();
		break;
		
		case "TargetDistance":
			dialog.text = "Pontosan milyen távolságra, kapitány? Adja meg lépésekben, de legfeljebb 20 lépésben.";
			link.l1 = "";
			Link.l1.edit = 3;
			link.l1.go = "TargetDistance_1";			
		break;
		case "TargetDistance_1":
			iTemp = sti(dialogEditStrings[3]);
			if (iTemp < 0)
			{
				dialog.text = "Kapitány, jól van?";
				link.l1 = "Sajnálom, az én hibám...";
				link.l1.go = "exit";
				break;
			}
			if (iTemp == 0)
			{
				dialog.text = "Megállok a helyemen, de nem mozdulok. Ezt akarja tôlem, kapitány?";
				link.l1 = "Igen. Pontosan ez az, amire szükség van.";
				link.l1.go = "exit";
				npchar.MusketerDistance = 0;
				break;
			}
			if (iTemp > 20)
			{
				dialog.text = "Azt hiszem, már mondtam, hogy nem állhatok 20 lépésnél távolabb a célponttól.";
				link.l1 = "Rendben, tartsa a 20 méteres távolságot.";
				link.l1.go = "exit";
				npchar.MusketerDistance = 20.0;
				break;
			}
			dialog.text = "Értettem és figyelembe vettem.";
			link.l1 = "Rendben.";
			link.l1.go = "exit";
			npchar.MusketerDistance = iTemp;
		break;

		case "AsYouWish":
			// проверка на море -->
			if (bSeaActive)
			{
				attr = Sea_FindNearColony();
				if (attr == "none")
				{
					dialog.text = "Kapitány, bár tényleg nem értem az érvelését, nem beszélhetnénk ezt meg a parton? Vagy úgy döntött, hogy egyszerûen kidob a fedélzetre?";
					Link.l1 = "Hmm... Nem, nem így értettem. Maradj itt, amíg a kikötôbe nem érünk.";
					Link.l1.go = "Exit";	
					break;	
				}
			}
			// проверка на море <--
			if (makeint(PChar.reputation.nobility) >= 41 && makeint(NPChar.reputation) < 41) //герой против злодея
			{
				dialog.text = RandPhraseSimple(LinkRandPhrase("Ez újdonság!","Miért, az égvilágon?","Mi az oka?!"), RandPhraseSimple("Kapitány, maga megôrült? Ilyen híreket közölni a semmi apropóján!","Hûha! És mit tettem, hogy nem tetszett neked?"));
				Link.l1 = RandPhraseSimple(LinkRandPhrase("Úgy döntöttem, hogy rendet teszek a legénységben. És nem tetszenek a kollégáiddal való kapcsolataid","Az elônyeid nem voltak olyan jók, mint a felvételkor megbeszéltek. Szóval,","gazemberek és gazemberek a csapatomban nem maradnak! Ezért"), LinkRandPhrase("Tudomásomra jutott, hogy rumot lopsz, titokban kemény ivásra szoktatod a legénységemet, és ezzel csökkented a morálját. Ezért","elegem van a bandita modorodból, és nem fogom eltûrni. Ezért","állandóan a központi kabinban töltöd az idôdet egy kártya- vagy kockajátékra, elvonva ezzel a többi tiszt figyelmét a szolgálatteljesítésrôl. Ez nem folytatódhat a végtelenségig. Tehát,")) + " pakolja össze a holmiját, és hagyja el a hajót.";
				if (makeint(Pchar.Rank) > makeint(NPchar.Rank))
				{
					Link.l1.go = "Get_out_A1_peace";
				}
				else
				{
					Link.l1.go = "Get_out_A1_strife";
				}
				break;	
			}
			if (makeint(PChar.reputation.nobility) >= 41 && makeint(NPChar.reputation) >= 41) // герой против героя
			{
				dialog.text = RandPhraseSimple(RandPhraseSimple("Megtudhatnám, mi az oka ennek a döntésnek?","Nyilvánvaló, hogy egy ilyen döntés jól megalapozott?"), RandPhraseSimple("Magyarázza meg, kapitány","Ez eléggé váratlan. De azért szeretném tudni az okát."));
				Link.l1 = RandPhraseSimple(LinkRandPhrase("Teljesen elégedetlen vagyok a feladataihoz való hozzáállásával.","Sajnos, önbôl nem lett jó tiszt, és valószínûleg soha nem is lesz...","Ön jó tiszt, és a szolgálata tisztességes volt, de most útjaink elváltak. Ne kérdezd, hogy miért."), LinkRandPhrase("Figyelmeztettelek, hogy a rum iránti szenvedély tönkretesz téged. Hogyan bízhatnék egy olyan emberben a harcban, aki még a kardját sem képes hüvelyébe tenni?","Szörnyû tengerész és tiszt vagy... Szerintem inkább a parton, mint a tengeren.","Nem vagyok megelégedve a képzettségeddel, de most végre találtam egy tisztességes helyettest."));
				Link.l1.go = "Get_out_A2";
				break;	
			}
			if (makeint(PChar.reputation.nobility) < 41 && makeint(NPChar.reputation) >= 41) // злодей против героя 
			{		
				dialog.text = RandPhraseSimple(RandPhraseSimple("Hmm... Megtudhatnám az okát?","Ez egy komoly kijelentés. Megtudhatnám, hogy konkrétan mivel vagy elégedetlen?"), RandPhraseSimple("Magyarázza meg, kapitány.","Nyilvánvaló, hogy egy ilyen kijelentés jól megalapozott?"));
				Link.l1 = RandPhraseSimple(LinkRandPhrase("Teljesen elégedetlen vagyok a képesítéseddel, ezért","Sajnos nem bizonyultál tisztességes tisztnek. Ezért","elegem van a nemes modorodból. Nem fogom a végtelenségig tûrni ôket, ezért"), LinkRandPhrase("tudomásomra jutott, hogy engedetlenségre buzdítod a legénységet. Az én hajómon nem lesznek zavargások! És ne köszönd meg, hogy nem dobtalak ki korábban. Szóval","Nemes elveid ugyan megtisztelnek, de ellentétben állnak a szabad magánzó rablóéletével. Így","nem tetszik a kötelességeidhez való viszonyod. Tehát")) + " pakold össze a holmidat, és hagyd el a hajót.";
				if (makeint(Pchar.Rank) > makeint(NPchar.Rank))
				{
					Link.l1.go = "Get_out_A3_peace";
				}
				else
				{
					Link.l1.go = "Get_out_A3_strife";
				}	
				break;
	
			}
			if (makeint(PChar.reputation.nobility) < 41 && makeint(NPChar.reputation) < 41) // злодей против злодея
			{	
				dialog.text = RandPhraseSimple(LinkRandPhrase("Kapitány, erre tényleg nem számítottam! Talán elmagyarázná, hogy mi folyik itt?","Kapitány, mi bántja magát?!","Hogy érti ezt, kapitány?!"), RandPhraseSimple("Mi a fene, kapitány?! Tegnap még minden rendben volt, most meg itt vagyunk, mi történt?","Hûha! Talán megmagyaráznád magad?"));
				Link.l1 = RandPhraseSimple(LinkRandPhrase("Te egy totális lusta és haszontalan idióta vagy, még egy hajósfiú a hullámvasúton is jobban csinálná. Túl sokáig szenvedtem miattad. Szóval","már egy ideje azon gondolkodtam, hogy kirúglak, és most végre találtam egy rendes helyettest. Szóval","Tudomásomra jutott, hogy rumot lopsz, titokban kemény ivásra szoktatod a legénységemet, és ezzel csökkented a morálját. Ezért"), LinkRandPhrase("Amikor felvettelek, azzal dicsekedtél, hogy te vagy a legjobb tiszt az egész flottában, de kiderült, hogy csak egy semmirekellô vagy, ezért","figyelmeztettelek, hogy az ivási szokásodnak rossz vége lesz. Miért tartanék egy haszontalan részegest a hajón? Szóval","szolgálat helyett állandóan kóborolsz valahol, vagy kártyázol, vagy kockázol. Remélem, nem gondoltad, hogy ez így mehet örökké? Szóval")) + " pakold össze a holmidat és hagyd el a hajót.";
				Link.l1.go = "Get_out_A4";
				break;
			}
		break;
	
		case "Get_out_A1_peace":
			dialog.text = RandPhraseSimple(LinkRandPhrase("Szóval, hogy beszélsz most! Rendben, ahogy akarod. De megnyugodhatsz: Nem jövök vissza hozzád, még akkor sem, ha éhen halok!","Ôszintén szólva én sem nagyon szeretem a nemes játékaidat. Szóval szia...", "Ó, menj a pokolba! Maradj a nyalókáiddal. A 'hero', indeed!"), LinkRandPhrase("Igazából sosem szerettem téged kiszolgálni... Egy teherhajó van ott, nem egy rendes hajó. Inkább egy befejezô iskola...","Tudod, elegem van a legénységedbôl, az összes csicsás, csak kisgyerekek, egyetlen igazi férfi sincs...","Rendben, kapitány, ahogy mondja. De Isten tudja, hogy jól végeztem a munkámat..."));
			Link.l1 = "Várjon csak. Jelenleg nem hagyhatom el a hajót tiszt nélkül. De késôbb visszatérünk erre a beszélgetésre.";
			Link.l1.go = "exit_bad";
			Link.l2 = "Akkor menjen békével.";
			Link.l2.go = "Exit_Fire_1";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l3 = "Ne gôzölögj. Elôkészítettem neked egy végkielégítést - "+sti(NPChar.rank)*500+" pezó. Remélem, ezzel minden kérdés eloszlik.";
				Link.l3.go = "Get_out_А1_ForMoney";
			}
		break;

		case "Get_out_A1_strife":
			dialog.text = LinkRandPhrase("Elnézést! Hogy érti 'hagyja el a hajót'?! Nem azért tettem ki a fejemet a szôlôlövedéknek, hogy akkor dobj le, amikor csak akarsz!", "Ha! 'hagyd el a hajót'! Komolyan azt hiszed, hogy hagyom, hogy eldobj, mint egy kiscicát?!", "Nyugalom, kapitány, komoly emberek nem intézik így a dolgaikat. Nem hagyom, hogy úgy bánjanak velem, mint egy zöldfülûvel.");
			Link.l1 = "Rendben, egyelôre maradhatsz - de csak addig, amíg nem találok egy rendes helyettest." ;
			Link.l1.go = "exit_bad";
			Link.l2 = "Ismétlem, a szolgálata véget ért. Összepakolhatja a holmiját.";
			Link.l2.go = "Get_out_A1_strife_1";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l3 = "Ne gôzölögj. Készítettem neked "+sti(NPChar.rank)*500+" pezót. Remélem, ezzel minden kérdés eloszlik.";
				Link.l3.go = "Get_out_А1_ForMoney";
			}
		break;

		case "Get_out_A1_strife_1":
			dialog.text = RandPhraseSimple("Valójában nem égek a vágytól, hogy itt maradjak. De nem is megyek el kompenzáció nélkül!", "Most már biztosan nem maradok azon a vén kádadon, de elôbb kárpótolj!") + " "+sti(NPChar.rank)*1000+" pezót, és elfelejtjük egymást.";
			Link.l1 = "Kicsit felhúztam magam... Kérem, fogadja el bocsánatkérésemet, és menjen vissza a munkájához.";
			Link.l1.go = "exit_bad1";
			Link.l2 = "Milyen pénzrôl beszélsz, ha mindig is megkaptad a méltányos részedet? Ez nekem zsarolásnak tûnik!";
			Link.l2.go = "Get_out_А1_strife_battle";
			if (sti(Pchar.money) >= sti(NPChar.rank)*1000)
			{
				Link.l3 = "Jól van, rendben. Add vissza a felszerelést, és akkor megkapod, amit kértél.";
				Link.l3.go = "Get_out_А1_chang";
			}
		break;

		case "Get_out_А1_ForMoney":
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*500)));
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			ChangeCharacterComplexReputation(pchar,"authority", 0.5);
			dialog.text = "Ez már egy másik történet. Viszontlátásra!";
			Link.l1 = "Remélem, hogy az útjaink soha többé nem keresztezik egymást.";
			Link.l1.go = "Exit_Fire_1";
		break;

		case "Get_out_А1_strife_battle":
			dialog.text = LinkRandPhrase("Tekintsük ezt az erkölcsi kár megtérítésének. Nem tûröm az ilyen bánásmódot, és aki így mer velem bánni, az meg fogja bánni!", "Ez nem zsarolás, hanem kárpótlás ezért az ostoba idôpocsékolásért! És meg is fogom kapni, kerüljön bármibe is!", "Túl sok idôt pazaroltam arra, hogy egy ilyen puhány alatt szolgáljak, mint te. Egy vagyont kereshetnék kereskedelmi hajók kifosztásával. Szóval csak az elmaradt hasznomat akarom kompenzálni.");
			if (sti(Pchar.money) >= sti(NPChar.rank)*1000)
			{
				Link.l1 = "Rendben. Itt a pénzed... És most tûnj el!";
				Link.l1.go = "Get_out_А1_ForMoney_angry";
			}
			Link.l2 = "Úgy tûnik, elfelejtetted, hogy ki vagy! Nem hagyom, hogy az ilyen félkegyelmûek, mint te, kiabáljanak velem!";
			Link.l2.go = "Get_out_А1_strife_death";
		break;

		case "Get_out_А1_strife_death":
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			ChangeCharacterComplexReputation(pchar,"authority", -1);
			OfficersReaction("good");
			dialog.text = "Rajta, kapitány! Mutasd magad!";
			Link.l1 = "Isten tudja, nem akartam!";
			Link.l1.go = "Get_out_fight";
		break;
	
		case "Get_out_А1_ForMoney_angry":
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*1000)));
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			ChangeCharacterComplexReputation(pchar,"authority", 0.5);
			OfficersReaction("bad");
			dialog.text = "Ez már egy másik történet. Viszontlátásra!";
			Link.l1 = "Remélem, hogy az útjaink soha többé nem keresztezik egymást.";
			Link.l1.go = "Exit_Fire_1";
		break;

		case "Get_out_A2":
			dialog.text = RandPhraseSimple(LinkRandPhrase("Nos, akkor ez eldôlt. Viszlát, kapitány, és ne haragudjon...","Kár, kapitány. De Isten tudja, én megpróbáltam. Viszontlátásra.","Nos, kapitány, önnek bizony nehéz megfelelni! Rendben, sok szerencsét!"), LinkRandPhrase("Kár, kapitány. Tudja, szerettem magának dolgozni.","Igen, történnek dolgok... De nem neheztelek. Búcsúzzon el.","Igazságtalan velem szemben, kapitány. Mégis, tiszteletben tartom a döntését. Viszontlátásra."));
			Link.l1 = "Várj, meggondoltam magam. Térjünk vissza erre a beszélgetésre késôbb.";
			Link.l1.go = "exit_good";
			Link.l2 = "Ne bosszankodj. Sok szerencsét...";
			Link.l2.go = "exit_fire_2";
			Link.l3 = "Várj egy kicsit... Szépen felszereltelek. Add meg nekik a jelet, nem fogok egy hordát felszerelni...";
			Link.l3.go = "Return_items_A2";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l4 = "Várj egy kicsit... Nem akarlak üres kézzel elengedni. Tessék, itt van "+sti(NPChar.rank)*500+" pezó. Jól fog jönni, amíg új munkát keresel.";
			}
			Link.l4.go = "Im_kind_A2";
		break;

		case "Return_items_A2":
			ChangeOfficersLoyality("bad_all", 1);
			dialog.text = "Ó, persze, vidd vissza az egészet...";
			Link.l1 = "Tudom, hogy jól értesz engem...";
			Link.l1.go = "Get_out_А2_chang";
		break;

		case "Im_kind_A2":
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*500)));
			ChangeOfficersLoyality("good_all", 1);
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			ChangeCharacterComplexReputation(pchar,"authority", 0.5);
			dialog.text = "Köszönöm, kapitány! Egy igazán váratlan nagylelkûség... Tudod, még mindig megvan néhány holmid, talán szeretnéd visszakapni ôket?";
			Link.l1 = "Talán... Manapság nem olyan könnyû jó pengét találni...";
			Link.l1.go = "Get_out_А2_chang";
			Link.l2 = "Ó, ne aggódjon. Tartsd meg ôket a szolgálataid emlékére.";
			Link.l2.go = "exit_fire_2";
		break;

		case "Get_out_A3_peace":
			dialog.text = RandPhraseSimple(LinkRandPhrase("Rendben, ahogy kívánod. De nyugodt lehetsz: Nem jövök vissza hozzád, még akkor sem, ha éhen halok!!!","Kapitány, a maga bandita módszerei engem is megbetegítenek. Elôbb vagy utóbb ennek meg kellett történnie. És nem kell okokat kitalálni.","Akkor maradj a gyilkosokkal. Egy tisztességes ember még az arcát sem mutatná a hajójuk gyengélkedôjében. Micsoda bordélyház van itt, Isten bocsássa meg!"), LinkRandPhrase("Ôszintén szólva, én is utáltam a szolgálatomat önök alatt. Egy egész legénységnyi gazembert vettél fel, egyetlen tisztességes emberrel sem lehetett beszélgetni.","Igen, ha továbbra is így állsz a legénységedhez, hamarosan teljesen egyedül maradsz, és nem kell majd okokat kitalálnod.","Az ellenségeskedésünk kölcsönös, és ez megnyugtat. Viszontlátásra."));
			Link.l1 = "Várjatok. Most nem a legjobb idô a visszavonulásodra. De minden követelés áll.";
			Link.l1.go = "exit_bad";
			Link.l2 = "Menj, menj. Jól megleszek az elôadásaid nélkül is.";
			Link.l2.go = "exit_fire_3";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l3 = "Várj egy kicsit. Adok neked "+sti(NPChar.rank)*500+" pezót. Nem akarom, hogy a csatornában halj meg, hogy nekem legyen bûntudatom miatta.";
				Link.l3.go = "Get_out_А3_ForMoney";
			}
		break;

		case "Get_out_А3_ForMoney":
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*500)));
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			ChangeCharacterComplexReputation(pchar,"authority", 0.5);
			ChangeOfficersLoyality("good_all", 1);
			dialog.text = LinkRandPhrase("Nos, köszönöm. Viszlát...", "Köszönöm a megértését. Sok szerencsét.", "Most már végeztünk. Sok szerencsét...");
			Link.l1 = "Tudom, hogy jól értettél.";
			Link.l1.go = "exit_fire_3";
		break;
	
		case "Get_out_A3_strife":
			dialog.text = LinkRandPhrase("De kapitány úr, ebben az esetben zátonyra futottam. Tényleg hajlandó lennél a hajóról egyenesen a parvisra küldeni?", "Ön igazságtalan velem, kapitány. De nem fogok haragudni, ha tisztességes kártérítést kapok.", "És ez a hála a harci sebeimért? Hát, azt hiszem, pénzbeli kompenzáció nélkül nem megy.");
			Link.l1 = "Rendben, meggondoltam magam. Maradhatsz, de visszatérünk erre a beszélgetésre.";
			Link.l1.go = "exit_bad";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l2 = "Ó, ne aggódj emiatt. Tessék - "+sti(NPChar.rank)*500+" pezó. Ez majd kárpótolja a hajón töltött idejét.";
				Link.l2.go = "Get_out_А3_ForMoney";
				Link.l3 = "Odaadom a pénzt. Mégis, szépen felszerelkeztél hála nekem, és azt hiszem, helyénvaló visszaadni a cuccot.";
				Link.l3.go = "Return_items_A3";
			}
			Link.l4 = "Ó, tényleg? És mi lesz a részeddel, amit eddig rendszeresen kaptál?! Tudtam, hogy mindennek vége lesz a zsörtölôdésnek és a prémiumért való könyörgésnek.";
			Link.l4.go = "Get_out_A3_strife_1";
		break;

		case "Return_items_A3":
			dialog.text = "Tudtam, hogy ezt fogod mondani, de csak akkor kapod vissza a felszerelésedet, ha megkapom a "+sti(NPChar.rank)*1000+" pesót. Egyébként csak a holttestemen keresztül kaphatod meg!";
			Link.l1 = "Rendben, akkor vedd el a pénzed.";
			Link.l1.go = "Get_out_А3_chang";
			Link.l2 = "Megôrültél vagy mi?! Ekkora összeget követelsz azért, amit ingyen kaptál?! Most már látom, hogy a kapzsiságod egyértelmûen gyôzedelmeskedett a színlelt jóléted felett.";
			Link.l2.go = "Get_out_A3_strife_1";
		break;

		case "Get_out_A3_strife_1":
			dialog.text = "Ne merészelj sértegetni engem! Lehet, hogy nem én vagyok a legjobb a haditengerészetnél, de attól még harcoló tiszt vagyok. És engem tisztelni fognak, még egy ilyen ficsúr is, mint maga!";
			Link.l1 = "Ha még nem értette meg, még egyszer megismétlem: hagyja abba a könyörgést, tôlem nem kap semmit.";
			Link.l1.go = "Get_out_А3_strife_death";
		break;

		case "Get_out_А3_strife_death":
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			ChangeCharacterComplexReputation(pchar,"authority", -1);
			OfficersReaction("bad");
			dialog.text = "Hát, én még mindig kapok elégtételt!";
			Link.l1 = "Ó, ez aztán a kihívás, ugye? Ahogy akarod...";
			Link.l1.go = "Get_out_fight";
		break;

		case "Get_out_A4":
			dialog.text = RandPhraseSimple(LinkRandPhrase("Ez az én szerencsém! Szívemet-lelkemet beleadtam a szolgálatba, csak azért, hogy kirúgjanak anélkül, hogy még egy szolgálati juttatást is kapnék!","Micsoda szerencsétlenség?! Felvesznek, aztán szinte azonnal kirúgnak. Fogalmam sincs, melyik szentnek gyújtsak gyertyát manapság...","Jéééééés! Idén már harmadszor rúgnak ki, mindet hétfônként. Talán nem kéne megjelennem a kapitányok elôtt, ha másnapos vagyok."), LinkRandPhrase("Nos, ahogy kívánod. Imádkozz, hogy soha többé ne találkozzunk.","Ahogy óhajtja. De ne feledje, hogy ennél jobb tisztet nem fog találni.","Rendben, kapitány, ahogy mondja. De Isten tudja, hogy jól végeztem a munkámat..."));
			Link.l1 = "Várjatok. Most nem a legjobb idô a visszavonulásodra. De minden követelés áll.";
			Link.l1.go = "exit_good";
			Link.l2 = RandPhraseSimple("Tûnj el most. És hála Istennek, hogy ma jó kedvem van.", "Tûnj el most. Olyan jó tiszt vagy, mint amilyen jó a szar a golyók gyártására.");
			Link.l2.go = "exit_fire_4";
			if (sti(Pchar.money) >= sti(NPChar.rank)*500)
			{
				Link.l3 = "Várj egy kicsit. Adok neked "+sti(NPChar.rank)*500+" pezót. Nem akarom, hogy a csatornában halj meg, hogy nekem legyen bûntudatom miatta.";
				Link.l3.go = "Get_out_А4_ForMoney";
			}
			Link.l4 = "Várj egy kicsit... Szépen felszereltelek, add vissza a cuccaimat.";
			Link.l4.go = "Return_items_A4";
		break;

		case "Get_out_А4_ForMoney":
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*500)));
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			ChangeCharacterComplexReputation(pchar,"authority", 0.5);
			ChangeOfficersLoyality("good_all", 1);
			dialog.text = LinkRandPhrase("Ó, köszönöm, kapitány! Ez nagyon kedves öntôl...", "Köszönöm a megértését. Sok szerencsét.", "Most már végeztünk. Sok szerencsét...");
			Link.l1 = "Sok szerencsét. Remélem, nem pazarolod el az egészet az elsô kocsmában.";
			Link.l1.go = "exit_fire_4";
		break;

		case "Return_items_A4":
			if (makeint(Pchar.Rank) > makeint(NPchar.Rank))
			{
				dialog.text = LinkRandPhrase("És most elviszed a felszerelésemet! Ó, a pokolba vele! Megyek horgászni, esküszöm...", "Látom, úgy döntöttél, hogy teljesen kitakarítasz. Ó, hát... Most már csak egy út van számomra, a parvis felé...", "Ó, köszönöm szépen! Most úgy döntöttél, hogy kirabolsz. Ó, micsoda kegyetlen sors... Akkor vedd el, vedd el! Mit tehetnék egyébként...");
				Link.l1 = "Tûnj el. Olyan jó tiszt vagy, mint a szar, amibôl golyót lehet csinálni.";
				Link.l1.go = "Get_out_А4_chang_1";
			}
			else	
			{
				dialog.text = RandPhraseSimple("Ahogy óhajtja, kapitány, de elôbb legyen olyan kedves, és adja át nekem "+sti(NPChar.rank)*1000+" pesót. Legyen ez a kárpótlás az erkölcsi kárért.", "Rendben. De ettôl még szeretném megkapni "+sti(NPChar.rank)*1000+" pezót a kemény és hûséges szolgálatom kárpótlásaként.");
				if (sti(Pchar.money) >= sti(NPChar.rank)*1000)
				{
					Link.l1 = "Micsoda gazember! Rendben, itt a pénzed.";
					Link.l1.go = "Get_out_А4_chang";
				}
				Link.l2 = "Hát nem ôrültél meg?! Hogy merészelsz ennyi pénzt kérni azért, amit én magam adtam neked!";
				Link.l2.go = "Get_out_A4_strife";
				Link.l3 = "Ah-ha! Csak vicceltem! Hogy rúghatnék ki egy régi barátot, mint lyukas sapka!";
				Link.l3.go = "exit_bad1";
			}
		break;

		case "Get_out_A4_strife":
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			ChangeCharacterComplexReputation(pchar,"authority", -1);
			ChangeOfficersLoyality("bad_all", 1);
			dialog.text = "Hát akkor nem kapsz semmit! Egy lépést sem teszek, amíg nem hallom a pénzem csilingelését!";
			Link.l1 = RandPhraseSimple("Hamarosan hallani fogod a pengém csilingelését!", "Aztán lábbal elôre elragadlak!");
			Link.l1.go = "Get_out_fight";
		break;

		case "Get_out_fight":
			CheckForReleaseOfficer(GetCharacterIndex(Npchar.id));
			RemovePassenger(Pchar, Npchar);
			LAi_CharacterDisableDialog(NPChar);
			LAi_SetWarriorType(Npchar);
			LAi_group_MoveCharacter(Npchar, "TmpEnemy");
			LAi_group_SetHearRadius("TmpEnemy", 100.0);
			LAi_group_FightGroupsEx("TmpEnemy", LAI_GROUP_PLAYER, true, Pchar, -1, false, false);
			if (PChar.location == Get_My_Cabin() || findsubstr(PChar.location, "_tavern" , 0) != -1 || findsubstr(PChar.location, "_store" , 0) != -1)
            {
				LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
				LAi_group_SetCheck("TmpEnemy", "CannotFightCurLocation");
				LAi_group_SetCheck("TmpEnemy", "MainHeroFightModeOff");
            }
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

	    case "Get_out_А1_chang": // интерфейс обмена
			Diag.TempNode = "Fired_1";
			LAi_CharacterDisableDialog(NPChar);
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*1000)));
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			NPChar.rank = 0;	
			DialogExit();
			LaunchCharacterItemChange(npchar);
			RemovePassenger(Pchar, npchar);
		break;

		case "Get_out_А2_chang": // интерфейс обмена
			Diag.TempNode = "Fired_2";
			LAi_CharacterDisableDialog(NPChar);
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			NPChar.rank = 0;
			DialogExit();
			LaunchCharacterItemChange(npchar);
			RemovePassenger(Pchar, npchar);
		break;

		case "Get_out_А3_chang": // интерфейс обмена
			Diag.TempNode = "Fired_3";
			LAi_CharacterDisableDialog(NPChar);
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*1000)));
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			NPChar.rank = 0;
			DialogExit();
			LaunchCharacterItemChange(npchar);
			RemovePassenger(Pchar, npchar);
		break;

		case "Get_out_А4_chang_1": // интерфейс обмена
			Diag.TempNode = "Fired_4";
			LAi_CharacterDisableDialog(NPChar);
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			NPChar.rank = 0;	
			DialogExit();
			LaunchCharacterItemChange(npchar);
			RemovePassenger(Pchar, npchar);
		break;

		case "Get_out_А4_chang": // интерфейс обмена
			Diag.TempNode = "Fired_4";
			LAi_CharacterDisableDialog(NPChar);
			AddMoneyToCharacter(Pchar, -(makeint(sti(NPChar.rank)*1000)));
			ChangeCharacterComplexReputation(pchar,"nobility", 1);
			ChangeCharacterComplexReputation(pchar,"authority", 0.5);
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			NPChar.rank = 0;	
			DialogExit();
			LaunchCharacterItemChange(npchar);
			RemovePassenger(Pchar, npchar);
		break;

	    case "exit_bad":
			Npchar.loyality = makeint(Npchar.loyality) - 3;
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();
		break;

		case "exit_bad1":
			Npchar.loyality = makeint(Npchar.loyality) - 2;
			ChangeOfficersLoyality("bad_all", 1);
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			ChangeCharacterComplexReputation(pchar,"authority", -1);
			Diag.CurrentNode = Diag.TempNode;			
			NPChar.quest.meeting = true;
			DialogExit();
		break;

		case "exit_good":
			Npchar.loyality = makeint(Npchar.loyality) - 1;
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();
		break;

		case "exit_fire_1":	//navy -->			
			if (CheckAttribute(NPChar, "PGGAi"))
			{				
				pchar.questTemp.FiringOfficerIDX = NPChar.index;
				AddDialogExitQuestFunction("PGG_FireOfficer");
				DialogExit();
				break;
			}	//navy <--		
			Diag.TempNode = "Fired_1";
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");			
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();	
		break;

		case "exit_fire_2":	//navy -->		
			if (CheckAttribute(NPChar, "PGGAi"))
			{				
				pchar.questTemp.FiringOfficerIDX = NPChar.index;
				AddDialogExitQuestFunction("PGG_FireOfficer");	
				DialogExit();
				break;
			}	//navy <--	
			Diag.TempNode = "Fired_2";
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");			
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();	
		break;

		case "exit_fire_3":	//navy -->		
			if (CheckAttribute(NPChar, "PGGAi"))
			{				
				pchar.questTemp.FiringOfficerIDX = NPChar.index;
				AddDialogExitQuestFunction("PGG_FireOfficer");
				DialogExit();
				break;
			}	//navy <--	
			Diag.TempNode = "Fired_3";
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");			
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();	
		break;

		case "exit_fire_4":	//navy -->		
			if (CheckAttribute(NPChar, "PGGAi"))
			{				
				pchar.questTemp.FiringOfficerIDX = NPChar.index;
				AddDialogExitQuestFunction("PGG_FireOfficer");	
				DialogExit();
				break;
			}	//navy <--		
			Diag.TempNode = "Fired_4";
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");			
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();	
		break;

		case "exit_fire_5":	//navy -->		
			if (CheckAttribute(NPChar, "PGGAi"))
			{				
				pchar.questTemp.FiringOfficerIDX = NPChar.index;
				AddDialogExitQuestFunction("PGG_FireOfficer");
				DialogExit();
				break;
			}	//navy <--	
			Diag.TempNode = "Fired_1";
			OfficersReaction("good");
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerFired");			
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = true;
			DialogExit();	
		break;

		case "Fired_1":
			Diag.TempNode = "Fired_1";      
			dialog.text = "Most mi lesz?! Már mindent megbeszéltünk! Soha többé nem teszem be a lábam a hajódra.";
			Link.l1 = RandPhraseSimple("Tûnj el most. Végül is nem nagy veszteség.", "Rendben, akkor menj. Nem foglak visszatartani.");	
			Link.l1.go = "Exit";
		break;

		case "Fired_2":
			Diag.TempNode = "Fired_2"; 
			dialog.text = "Még valami, kapitány? Azt hittem, már mindent megbeszéltünk...";
			Link.l1 = "Nem, semmi. Csak el akartam búcsúzni...";	 
			Link.l1.go = "Exit";
		break;

		case "Fired_3":
			Diag.TempNode = "Fired_3"; 
			dialog.text = "Kapitány, már mindent megbeszéltünk és kifejeztük a követeléseinket. Ugye nem fogja azt mondani, hogy meggondolta magát?";
			Link.l1 = "Rendben, akkor menjen. Végül is nem nagy veszteség.";	 
			Link.l1.go = "Exit";
		break;

		case "Fired_4":
			Diag.TempNode = "Fired_4"; 
			dialog.text = "Kapitány, mi más kérdés lehetne még? Csak hogy elmondjam, nagyon megsértôdtem, és nem kívánok visszatérni...";
			Link.l1 = "Rendben, akkor menjen. Nem mintha annyira szükségem lett volna magára.";	 
			Link.l1.go = "Exit";
		break;
		
		// boal 05.09.03 offecer need to go to abordage -->
	    case "Boal_Stay":
            //SetCharacterTask_Stay(Characters[Npchar.index]); // it's a mistic but here doesn't work :(
            //Log_SetStringToLog(Npchar.id +" "+Npchar.index);
            Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
            AddDialogExitQuestFunction("LandEnc_OfficerStay");
		    Diag.TempNode = "Hired";
		    dialog.text = "Igenis, kapitány!";
		    Link.l1 = "Pihenj.";
		    Link.l1.go = "Exit";
		    Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
	    break;
		
	    case "Boal_Follow":
		    SetCharacterTask_FollowCharacter(Npchar, PChar); // it works here!!!
		    Diag.TempNode = "Hired";
		    dialog.text = "Igenis, kapitány!";
		    Link.l1 = "Pihenj.";
		    Link.l1.go = "Exit";
	    break;
        // boal 05.09.03 offecer need to go to abordage <--

		//////////////////////////////    офицер-наместник -->
		case "Gover_Hire":
            dialog.Text = "Kapitány! Megtiszteltetés lenne!";
            Link.l1 = "Tartsd fenn a rendet és virágoztasd fel a várost, én pedig idôrôl idôre elhajózom, hogy beszedjem a vámokat.";
			Link.l1.go = "Exit_Gover_Hire";
            Link.l2 = "Meggondoltam magam.";
            Link.l2.go = "Exit";
            Diag.TempNode = "Hired";
        break;

        case "Exit_Gover_Hire":
            sld = GetColonyByIndex(sti(NPChar.ColonyIdx));
            attr = sld.id + "_townhall";

            // снимем пассажира -->
			CheckForReleaseOfficer(sti(NPChar.index));
			RemovePassenger(pchar, NPChar);
			// снимем пассажира <--
		    sld.OfficerIdx = sti(NPChar.index);
			ChangeCharacterAddressGroup(NPChar, attr, "sit", "sit1");
			LAi_SetHuberTypeNoGroup(NPChar);
            SaveCurrentNpcQuestDateParam(NPChar, "StartTaxDate");
            SaveCurrentNpcQuestDateParam(NPChar, "GoverTalkDate");
            LAi_LoginInCaptureTown(NPChar, true);
			//  СЖ -->
			ReOpenQuestHeader("Gen_CityCapture");
            AddQuestRecordInfo("Gen_CityCapture", "t3_1");
			AddQuestUserData("Gen_CityCapture", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Gen_CityCapture", "sCity", XI_ConvertString("colony" + sld.id));
			AddQuestUserData("Gen_CityCapture", "sName", GetFullName(NPChar));
			//  СЖ <--
			Diag.CurrentNode = "Gover_Main";
            DialogExit();
        break;

        case "Gover_Main":
            iTemp = GetNpcQuestPastDayParam(NPChar, "GoverTalkDate");
            if (iTemp > 0)
            {
				dialog.Text = "Mi a parancsuk? Legutóbb a " + FindRussianDaysString(iTemp) + " elôtt látogatott meg.";
			}
			else
			{
			    dialog.Text = "Mik a parancsaid?";
			}

            Link.l1 = "Mennyi adópénzt " + NPCharSexPhrase(NPChar, "gyûjtöttek be", "gyûjtöttek be") + " eddig?";
        	Link.l1.go = "Gover_Tax";
            Link.l8 = "Szükség van rád a hajón, felmentelek a városi szolgálat alól.";
            Link.l8.go = "Gover_Fire";
			Link.l9 = "Minden jót.";
            Link.l9.go = "Exit";
            Diag.TempNode = "Gover_Main";
            SaveCurrentNpcQuestDateParam(NPChar, "GoverTalkDate");
        break;

        case "Gover_Tax":
            iTemp = GetNpcQuestPastDayParam(NPChar, "StartTaxDate");
            iTax  = makeint((GetCharacterSkillSimple(NPChar, SKILL_COMMERCE) + GetCharacterSkillSimple(NPChar, SKILL_LEADERSHIP)) / 2);
            sld = GetColonyByIndex(sti(NPChar.ColonyIdx));
			if (CheckAttribute(sld, "FortValue"))
			{
			    iFortValue = sti(sld.FortValue);
			}
			else
			{
			    iFortValue = 20;
			}
			NPChar.Gover_Tax_Sum = iFortValue*iTax*iTemp;
			dialog.Text = "A képességeim lehetôvé teszik a gyûjtést " + FindRussianMoneyString(iFortValue*iTax) + " naponta. Több mint " + FindRussianDaysString(iTemp) + " én " + NPCharSexPhrase(NPChar, "gyûjtöttem", "gyûjtöttem") + " " + FindRussianMoneyString(sti(NPChar.Gover_Tax_Sum)) + ".";
			if (sti(NPChar.Gover_Tax_Sum) > 0)
			{
			    Link.l1 = "El akarom venni az összes összegyûjtött adópénzt.";
            	Link.l1.go = "Gover_Tax_Get";
			}
			Link.l2 = "Köszönöm a szolgálatot!";
            Link.l2.go = "Exit";
        break;

        case "Gover_Tax_Get":
            SaveCurrentNpcQuestDateParam(NPChar, "StartTaxDate");
            AddMoneyToCharacter(Pchar, sti(NPChar.Gover_Tax_Sum));

			Diag.CurrentNode = "Gover_Main";
            DialogExit();
        break;

        case "Gover_Fire":
            dialog.Text = "Nagyszerû! Tudod, én nem vagyok szárazföldi csavargó.";
            Link.l8 = "Ez jó.";
            Link.l8.go = "exit_hire";
            Diag.TempNode = "Hired";
            sld = GetColonyByIndex(sti(NPChar.ColonyIdx));
            DeleteAttribute(sld, "OfficerIdx");
            //  СЖ -->
			ReOpenQuestHeader("Gen_CityCapture");
            AddQuestRecordInfo("Gen_CityCapture", "t3_2");
			AddQuestUserData("Gen_CityCapture", "sCity", XI_ConvertString("colony" + sld.id));
			AddQuestUserData("Gen_CityCapture", "sName", GetFullName(NPChar));
			//  СЖ <--
        break;
        //////////////////////////////    офицер-наместник <--

		//Указания для компаньона 19.02.08 -->
		case "Companion_Tasks":
			dialog.Text = "Hallgatlak téged.";
			Link.l1 = "A beszállásról van szó.";
			Link.l1.go = "Companion_TaskBoarding";
			Link.l2 = "A hajójáról van szó.";
			Link.l2.go = "Companion_TaskChange";
			if(bBettaTestMode) // Только при бета-тесте
			{
			    Link.l3 = "Azt akarom, hogy egy idôre hagyja el a századomat, és keresse a szerencséjét egyedül.";
			    Link.l3.go = "CompanionTravel";
			}
			Link.l8 = "Eddig semmi.";
			Link.l8.go = "exit";
		break;
		
		case "Companion_TaskBoarding":
			dialog.Text = "Szóval mi a kívánságod?";
			Link.l1 = "Ne szállj fel az ellenséges hajókra. Vigyázz magadra és a legénységre.";
			Link.l1.go = "Companion_TaskBoardingNo";
			Link.l2 = "Azt akarom, hogy szállj fel az ellenséges hajókra.";
			Link.l2.go = "Companion_TaskBoardingYes";
		break;
		
		case "Companion_TaskChange":
			dialog.Text = "Szóval mi a kívánságod?";
			Link.l1 = "Szeretném, ha nem cserélnéd el a hajódat egy másikra a beszállás után. Az túl értékes.";
			Link.l1.go = "Companion_TaskChangeNo";
			Link.l2 = "Amikor ellenséges hajókra szállsz fel, elviheted ôket magadnak, ha történetesen tisztességesek.";
			Link.l2.go = "Companion_TaskChangeYes";
		break;
		
		case "Companion_TaskBoardingNo":
			dialog.Text = "Igenis, kapitány.";
			Link.l1 = "Pihenj.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = false;
		break;
		
		case "Companion_TaskBoardingYes":
			dialog.Text = "Úgy lesz, kapitány.";
			Link.l1 = "Pihenj.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = true;
		break;
		
		case "Companion_TaskChangeNo":
			dialog.Text = "Igenis, kapitány.";
			Link.l1 = "Pihenj.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = false;
		break;
		
		case "Companion_TaskChangeYes":
			dialog.Text = "Úgy lesz, kapitány.";
			Link.l1 = "Pihenj.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = true;
		break;
		//<--
	
		// Самостоятельное плавание компаньона -->
		case "CompanionTravel":
			if(GetAttrValue(PChar, "CompanionTravel") == 3) // Если уже троих отпустил
			{
				dialog.Text = "Kapitány, nem hagyom el a századát, mert már három hajót elbocsátott.";
					Link.l1 = "Igen, talán igaza van.";
					Link.l1.go = "exit";
				break;
			}
		
			dialog.Text = "Semmi gond, kapitány. Melyik városban találkozunk?";
			for(iTemp=0; iTemp<MAX_COLONIES; iTemp++)
			{
				sld = &colonies[iTemp];
				attr = sld.ID;
				if(sld.nation == "none" || sld.nation == PIRATE || attr == "Panama" || attr == "FortOrange") continue;
				attrLoc = "l" + iTemp;
				Link.(attrLoc) = "A " + XI_ConvertString("Colony" + attr + "Dat");
				Link.(attrLoc).go = "CompanionTravelToColony_" + attr;
			}
				Link.l99 = "Meggondoltam magam.";
				Link.l99.go = "exit";
		break;
			
		case "CompanionTravel_EnemyColony":
			dialog.Text = "Kapitány, de nem várhatom meg a velünk szemben ellenséges kolónián!";
				Link.l1 = "Tudja, felejtse el ezeket az utazásokat...";
				Link.l1.go = "exit";
		break;
			
		case "CompanionTravel_NoCrew":
			dialog.Text = "Kapitány, a legénységben szinte nincs is tengerész! Milyen utazásról beszélsz?!";
				Link.l1 = "Így van, tényleg kevés a matrózunk...";
				Link.l1.go = "exit";
		break;
			
		case "CompanionTravel_NoFood":
			dialog.Text = "Kapitány, nincs elég tartalék a fedélzeten egy ilyen útra.";
				Link.l1 = "Igen, igazad van. Az utazás várhat...";
				Link.l1.go = "exit";
		break;
			
		case "CompanionTravel_NoHP":
			dialog.Text = "Kapitány, de a hajóm rossz állapotban van. Nem lenne bölcs dolog, ha ilyen körülmények között egyedül indulnék útnak!";
				Link.l1 = "Igen, igazad van. A hajódat meg kell javítani.";
				Link.l1.go = "exit";
		break;
		
		case "CompanionTravel_PrepareStart":
			dialog.Text = "Értem. Till " + XI_ConvertString("Colony" + characters[sti(NPChar.realcompanionidx)].CompanionTravel.ToColonyID + "Gen") + " menni " + sti(characters[sti(NPChar.realcompanionidx)].CompanionTravel.Days) + " napok, mit tegyek érkezéskor?";
				Link.l1 = "Feküdj a kolónia kikötôjében egy hónapig.";
				Link.l1.go = "CompanionTravel_PrepareStart_2";
				Link.l2 = "Tudod, már átgondoltam a dolgot. Maradj velem...";
				Link.l2.go = "exit";
		break;
		
		case "CompanionTravel_PrepareStart_2":
			dialog.Text = "Értem, kapitány. Azonnal indulok.";
				Link.l1 = "Igen, kérem.";
				Link.l1.go = "CompanionTravel_Start";
		break;
			
		case "CompanionTravel_Start":
			Diag.CurrentNode = "CompanionTravel_LastNode";
			NPChar.quest.meeting = true;
			CompanionTravel_SetTraveller(NPChar);
			DialogExit();
		break;
			
		case "CompanionTravel_LastNode":
			Dialog.text = RandPhraseSimple("Ma újra vitorlát bontok...",
			"Ne felejtsd el a találkozónkat a " + XI_ConvertString("Colony" + characters[sti(NPChar.realcompanionidx)].CompanionTravel.ToColonyID + "Dat") + ".");
				link.l2 = "...";
				link.l2.go = "Exit";
				Diag.TempNode = "CompanionTravel_LastNode";
		break;
			
		case "CompanionTravel_ToSquadron":
			if(GetCompanionQuantity(PChar) < COMPANION_MAX)
			{
				dialog.text = "Én is szeretném. Mostantól a hajóm ismét a te parancsnokságod alatt áll, kapitány.";
					Link.l1 = "Rendben.";
					Link.l1.go = "exit";
					Diag.TempNode = "hired";
					CompanionTravel_DeleteSpecialShipAttributes(NPChar);
					Group_DeleteAtEnd(NPChar.CompanionTravel.GroupID); // Потрем группу
					SetCompanionIndex(PChar, -1, sti(NPChar.index));
					PChar.CompanionTravel = sti(PChar.CompanionTravel) - 1; // Этого компаньона взяли обратно в эскадру
					DeleteAttribute(NPChar, "CompanionTravel");
			}
			else
			{
				dialog.text = "Kapitány, már öt hajód van a századodban - mit fogsz csinálni a hatodikkal? Nos, azt hiszem, inkább itt várlak meg a hajón. Az új társaid nem tûnnek megbízhatónak számomra. A hajóik hamarosan elsüllyednek, te pedig visszajössz értem.";
					Link.l1 = "Hé, nem vagy te okos? Admirálisnak kellene lenned, nem csak kapitánynak!";
					Link.l1.go = "exit";
					Diag.TempNode = "CompanionTravel_ToSquadron_2";
					NPChar.DeckDialogNode = "CompanionTravel_ToSquadron_2"; // ставим снова эту ноду
			}
		break;
			
		case "CompanionTravel_ToSquadron_2":
			dialog.text = "Ó, kapitány, visszatértél, ahogy mondtam. Szóval, most már van egy üres hely a századodban?";
			if(GetCompanionQuantity(PChar) < COMPANION_MAX)
			{
				Link.l1 = "Igen, " + NPChar.name + ", van egy. Üdvözöljük a században.";
				Link.l1.go = "exit";
				Diag.TempNode = "hired";
				CompanionTravel_DeleteSpecialShipAttributes(NPChar);
				Group_DeleteAtEnd(NPChar.CompanionTravel.GroupID);
				SetCompanionIndex(PChar, -1, sti(NPChar.index));
				PChar.CompanionTravel = sti(PChar.CompanionTravel) - 1; // Этого компаньона взяли обратно в эскадру
				DeleteAttribute(NPChar, "CompanionTravel");
			}
			else
			{
				Link.l1 = "Sajnos még nem.";
				Link.l1.go = "exit";
				Diag.TempNode = "CompanionTravel_ToSquadron_2";
				NPChar.DeckDialogNode = "CompanionTravel_ToSquadron_2";
			}
		break;
		// <-- Самостоятельное плавание компаньона
		
		case "tonzag_after_boarding":
			dialog.text = "Kapitány, a dolgok szarul állnak! Az ellenség szorosan fogva tart minket, attól tartok, nem engednek el, amíg meg nem halunk! Az embereink most nagy bajban vannak, és az ágyúszemélyzet nagy része kiesett!";
			link.l1 = "Segítek nekik. Vedd át a parancsnokságot és vigyél ki minket innen!";
			link.l1.go = "tonzag_after_boarding_1";
			DelLandQuestMark(npchar);
		break;
		
		case "tonzag_after_boarding_1":
			dialog.text = "Igenis, uram!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_GoToGunDeck");
		break;
		
		case "tonzag_after_victory":
			dialog.text = "Gyôzelem, kapitány! A partraszálló csapat megsemmisült, az ellenség a visszavonulást választotta, és dél felé vette az irányt. A hajó állapota elfogadható. A legénység él: " + GetCrewQuantity(pchar) + " emberek. Jelentés elkészült!";
			link.l1 = "Köszönjük! Rumot mindenkinek és erôsítsétek az ôrséget, amíg elérjük a kikötôt!";
			link.l1.go = "tonzag_after_victory_1";
		break;
		
		case "tonzag_after_victory_1":
			dialog.text = "Hurrá! Aye aye!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_AlonsoBoardingDialog");
		break;
	}
}
