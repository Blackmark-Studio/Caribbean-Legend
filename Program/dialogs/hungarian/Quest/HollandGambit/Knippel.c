// Чарли Книппель - старый артиллерист
void ProcessDialogEvent()
{
	ref NPChar, sld, rItm, rItem;
	aref Link, NextDiag, rType;
	int i, iTemp, amount;
	string 	sAttr, sGun, sBullet, attrL;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	sAttr = Dialog.CurrentNode;
	if (findsubstr(sAttr, "SetGunBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	NPChar.SetGunBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
 	    Dialog.CurrentNode = "SetGunBullets2";
 	}
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
		//ветка на взятие 2 варианта прохождения - за Англию
		if(CheckAttribute(pchar, "questTemp.HWIC.CanTake") && !CheckAttribute(pchar, "questTemp.HWIC.CanTake.Eng") && !CheckAttribute(npchar, "quest.HWICTake") && !CheckAttribute(pchar, "questTemp.HWIC.Holl") && !CheckAttribute(pchar, "questTemp.HWIC.Self"))
		{
			dialog.text = "Ahoy haver, láncot lôttek a seggembe! Mi szél hozott ide?";
			link.l1 = "Láncot lôttek a... mibe? Ó, nem érdekes, csak köszönni akartam.";
			link.l1.go = "exit";
			link.l2 = "Üdvözlöm, Mr. Knippel. Ha, már értem, miért hívják Knippelnek. Egyébként, azt beszélik, hogy ön az angol haditengerészetnél szolgált. Van egy remek hajóm és egy képzett legénységem. Szeretném felajánlani magam és a hajómat az angol korona... ööö... nemzetközösség szolgálatára. Tudna nekem tanácsot adni, vagy ajánlani valakit, esetleg segíteni ebben a kérdésben?";
			link.l2.go = "Knippel_check";
			break;
		}
		//за Голландию
		if (CheckAttribute(pchar, "questTemp.HWIC.Holl"))
		{
			if (pchar.questTemp.HWIC.Holl == "toKnippel")
			{
				dialog.text = "Ahoymatey, láncot lôttek a seggembe! Mi szél hozta ide?";
				link.l1 = "Üdvözlöm, Mr. Knippel. Ha, már értem, miért hívják Knippelnek. Az a hír járja, hogy ön az angol haditengerészetnél szolgált, ezért szeretném a segítségét kérni...";
				link.l1.go = "Dominica";
				DelLandQuestMark(npchar);
				break;
			}
			dialog.text = "Lánclövés a seggemet! Mit akarsz, haver?";
			link.l1 = "Nem, semmit. Elmegyek.";
			link.l1.go = "exit";
			break;
		}
		//за Англию
		if (CheckAttribute(pchar, "questTemp.HWIC.Eng"))
		{
			if (pchar.questTemp.HWIC.Eng == "TakeHollConvoy")
			{
				dialog.text = "Ahoy kapitány, hallottam néhány pletykát egy ezüst konvojról, amit elfogtak...";
				link.l1 = "Ön jól informált, Mr. Knippel.";
				link.l1.go = "HollConvoy_Check";
				DelLandQuestMark(npchar);
				DelMapQuestMarkCity("SentJons");
				break;
			}
			if (pchar.questTemp.HWIC.Eng == "Wait")
			{
				dialog.text = "Kérdés, kapitány?";
				link.l1 = "Nem, semmit. Elmegyek.";
				link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.HWIC.Eng == "Start_main")
			{
				dialog.text = "Örülök, hogy látom, kapitány! A parancsnokom, Richard Fleetwood személyesen akart idejönni, hogy megismerje önt, de tegnap este baleset történt... Valaki megpróbálta megölni az utca közepén, láncot lôtt a seggembe!";
				link.l1 = "Az lehetetlen! Mit csináltak az ôrök?";
				link.l1.go = "Fleetwood_house";
				DelLandQuestMark(npchar);
				break;
			}
			dialog.text = "Kérdés, kapitány?";
			link.l1 = "Nem, semmit. Elmegyek.";
			link.l1.go = "exit";
		break;
		}
			dialog.text = "Hé, haver, láncot lôttek a seggembe! Mi szél hozott ide?";
			link.l1 = "Helló, csak beugrottam.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

//-------------------------------------------за Голландию--------------------------------------------------	
		case "Dominica":
			dialog.text = "Ahoy, tényleg így van? És hogyan segíthet neked egy öreg tengerész, aki régen földönfutó volt, pajtás?";
			link.l1 = "Nézd... Én csak egy egyszerû kapitány vagyok, és rendszeresen közlekedem Martinique és Curacao között. Szóval kétszer is megtámadott egy szellemhajó Martinique-tól nem messze... De a helyzet az, hogy ô nem egy Fata Morgana vagy Repülô Hollandi. Képes voltam egyszerû ágyúgolyókkal széttépni a vitorláit!";
			link.l1.go = "Dominica_1";			
		break;
		
		case "Dominica_1":
			dialog.text = "Tényleg? Ez egyáltalán nem jellemzô egy szellemhajóra, hogy a vitorlákat szilárd lövésektôl veszítse el, borzongass meg...";
			link.l1 = "Csak azért maradtunk életben, mert a hajóm le tudta gyôzni a széllel szemben vitorlázva. Legutóbb az összes rakományomat ki kellett dobnom a fedélzetre, hogy a hajótestemet eléggé megkönnyítsem a meneküléshez... el tudja képzelni a veszteséget? Szívszorító!";
			link.l1.go = "Dominica_2";			
		break;
		
		case "Dominica_2":
			dialog.text = "Fújjon le, kapitány...";
			link.l1 = "Mathias Beck, Curacao kormányzója egyszerûen félresöpörte a panaszaimat. Azt mondta, hogy a szellemhajóról szóló mesék badarságok, és hogy az ôreim részegek a grogtól. Martinique kormányzója megígérte, hogy ôrjáratot küld oda, de a szemei elárulták, hogy nem ér rá semmit sem tenni.  Nem térhetek vissza Martinique-ra, amíg az a rohadt kalóz 'ghost' kószál ott ólálkodik. A hajóm kicsi, ahogy a legénységem is, valószínû, hogy a harmadik találkozást sem éljük túl vele...";
			link.l1.go = "Dominica_3";			
		break;
		
		case "Dominica_3":
			dialog.text = "Ez nagy kár, pajtás. De hogyan segíthetek?";
			link.l1 = "Az itteni matrózoktól hallottam, hogy volt itt St. John's-ban egy Richard Fleetwood nevû kapitány, aki ugyanerre a szellemhajóra vadászott. Személyesen nem ismerem ôt, ezért mesélem el ezt a történetet neked, talán tovább tudnád adni neki a szerencsétlenségem történetét? Biztos vagyok benne, hogy a mocskos kalóz valahol Dominika vad partjai közelében bujkál, és Barbados és Martinique között portyázik.";
			link.l1.go = "Dominica_4";			
		break;
		
		case "Dominica_4":
			dialog.text = "Barbados és Martinique között? Ya har! Egy kövér és gazdag kereskedelmi útvonal. Ez nagyon úgy hangzik, mintha Bilgerat tenné.";
			link.l1 = "Nem vagyok gazdag vagy kövér, és nincs pénzem arra, hogy megvesztegessek egy tengerészkapitányt katonai kíséretért. De ha Sir Fleetwood már vadászik erre a bilgeratra, megmondaná neki, hogy hol találja ezt 'Flying Dutchman'?";
			link.l1.go = "Dominica_5";			
		break;
		
		case "Dominica_5":
			dialog.text = "Jól tetted, hogy idejöttél, pajtás. Elmondom a történetét a megfelelô embereknek, láncot lôttek a májamba! Hamarosan újra kereskedni fogsz Martinique-kal.";
			link.l1 = "Remélem, hogy Isten meghallgatja szavait! Köszönöm, hogy meghallgattál, Charlie. Remélem a legjobbakat. Viszlát, és kerüld el a láncos lövést!";
			link.l1.go = "Dominica_6";			
		break;
		
		case "Dominica_6":
			DialogExit();	
			pchar.questTemp.HWIC.Holl = "toDominica";
			AddQuestRecord("Holl_Gambit", "1-17");
			pchar.quest.toDominica.win_condition.l1 = "location";
			pchar.quest.toDominica.win_condition.l1.location = "Dominica";
			pchar.quest.toDominica.function = "PrepareToFleetwoodAttack";
			DelMapQuestMarkShore("Shore1");
			DelMapQuestMarkShore("Shore2");
			AddMapQuestMarkIsland("Dominica", true);
		break;

//----------------------------------------------за Англию--------------------------------------------------	
		case "Knippel_check"://начинаем проверять нашего ГГ по всем статьям
			if(makeint(PChar.reputation.nobility) < 48)//низкая репа
			{
				// belamour legendary edition покажем критерии
				notification("Túl alacsony a hírneve! (Adventurer)", "None");
				PlaySound("Voice\English\hambit\Charlie Knippel-04.wav");
				dialog.text = "A víg öreg Angliának nincs szüksége a gazemberek szolgálataira, láncos lövés a seggemet! Tisztelettel, elhúzhatsz a picsába.";
				link.l1 = "Hé, hé, haver, vigyázz a szádra, vagy összevarrom!";
				link.l1.go = "exit";
				break;
			}
			else
			{
				notification("Reputáció ellenôrzés átment", "None");
			}
			if(GetSummonSkillFromName(pchar, SKILL_SAILING) < 30)//низкая навигация
			{
				dialog.text = "Kapitány, ôszinte leszek. Még egy vizes zsákból sem tudnál kivitorlázni. Gyere vissza, ha már jobban értesz a navigáláshoz, érted?";
				// belamour legendary edition покажем критерии  -->
				notification("Képességpróba Sikertelen (30)", SKILL_SAILING);
				//<--
				dialog.text = "Cao'n, a flottánknak tapasztalt kapitányokra van szüksége, nem bénákra. Gyere vissza, ha elsajátítottad a navigáció mûvészetét.";							 
				link.l1 = "Értem... Akkor majd késôbb találkozunk.";
				link.l1.go = "exit";
				break;
			}
			else
			{
				notification("Képességellenôrzés megfelelt", SKILL_SAILING);
			}
			dialog.text = "Ahoj, épp idôben jöttél, kapitány, láncos lövés a seggem! Richard nem tudta, kire számíthatna ebben a kockázatos vállalkozásban, még azt is fontolgatta, hogy visszautasítja... Szóval a lehetôségek kismadarai édesen énekelnek ma a füledben. Ha a mi elvárásainknak megfelelôen teljesítesz, akkor egy bizonyos nagyon fontos embernek foglak ajánlani. Van elég sörét a gatyádban, hogy megbirkózz vele?";
			link.l1 = "Tele vagyok sörétekkel, Mr. Knippel.";
			link.l1.go = "Knippel_task";
		break;
		
		case "Knippel_task"://первое задание
			DelLandQuestMark(npchar);
			DelLandQuestMark(characterFromId("Bridgetown_tavernkeeper"));
			DelLandQuestMark(characterFromId("Lucas"));
			DelMapQuestMarkCity("Bridgetown");
			DelMapQuestMarkCity("Villemstad");
			DelMapQuestMarkCity("SentJons");
			dialog.text = "Ar har! Látom, felállt a farkad, kapitány! Hamarosan villogó tûz fog következni! Most jól figyelj. A Holland Nyugat-indiai Társaság ezüstflottája egy-két napja hagyta el Willemstadot Curacaón. Philipsburg felé hajózik. A flottában ezúttal csak néhány hajó van. Egyetlen gálya, a rakterében az ezüsttel, két kísérôhajóval együtt. Kapjátok el az ezüst flottát, fogjátok el a keleti gályát az ezüst rakománnyal, és vigyétek Antiguára. A kísérôket elsüllyesztheted, ôk feláldozhatók. Láncra lôheted a májukat, yar!";
			link.l1 = "A napjaik meg vannak számlálva.";
			link.l1.go = "Knippel_task_1";
			DelLandQuestMark(npchar);
		break;
		
		case "Knippel_task_1":
			dialog.text = "Néhány tanács, kapitány. A Curacao és Sint Maarten közötti kereskedelmi útvonal nem messze fekszik Szent Kristóf partjaitól. Azt tanácsolnám, hogy ott készítsenek elô egy rajtaütést. Készítsék fel magukat és a hajójukat erre az összecsapásra. A Nyugat-indiai Társasággal való összeütközés nem egy séta a parkban egy csinos lánnyal.";
			link.l1 = "Tudom, mibe keveredek, de értékelem az ôszinteségét, Mr. Knippel. Visszajövök a holland ezüsttel.";
			link.l1.go = "Knippel_task_2";			
		break;
		
		case "Knippel_task_2":
			DialogExit();
			npchar.quest.HWICTake = "true";
			pchar.questTemp.HWIC.CanTake.Eng = "true";//признак, что английка уже бралась
			HWICSilverConvoyInWorld();
			AddQuestRecord("Holl_Gambit", "2-1");
			ReOpenQuestHeader("Holl_Gambit"); // данила ,чтобы вышел из архива. 																				   
			pchar.questTemp.HWIC.Eng = "begin";
			SetFunctionTimerCondition("HollConvoy_Over", 0, 0, 15, false);
		break;
		
		case "HollConvoy_Check"://начинаем проверять
			int iHal = 0;
			for(i = 0; i < COMPANION_MAX; i++)
			{
				iTemp = GetCompanionIndex(PChar, i);
				if(iTemp > 0)
				{
					sld = GetCharacter(iTemp);
					pchar.questTemp.HWIC.Eng.CompanionIndex = sld.Index;
					if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_GALEON_L) iHal++;
				}
			}//признак наличия ТГ в компаньонах
			if (iHal > 0)
			{
				amount = sti(pchar.questTemp.HWIC.Eng.SlvQty) - GetSquadronGoods(pchar, GOOD_SILVER);
				if (amount <= 0)
				{
					dialog.text = "Nem kell elmondania, mi történt, kapitány. Mindenrôl tájékoztattak, amíg a vámos a hajóját vizsgálta... Jól csinálta, kapitány. Kiválóan! Nem hangzott könnyûnek, a lánc a seggembe lôtt!";
					link.l1 = "Jó érzés, hogy értékelik.";
					link.l1.go = "HollConvoy_complete";
				}
				else
				{
					dialog.text = "Nem kell elmondanod, mi történt, haver. Mindenrôl tájékoztattak, amíg a vámos a hajóját vizsgálta... Nem hoztad vissza az egész ezüstöt, láncos a seggembe lôttél! Pontosan tudom, hogy mennyi ezüst volt azon a kelet-indiai hajón, pezóra pontosan. Ennek a küldetésnek nem csak az volt a célja, hogy próbára tegye a harci képességeidet, hanem az is, hogy a becsületességedet. Ez utóbbin megbuktál. Takarodj a házamból, patkány!";
					link.l1 = "Akkor a pokolba veled, együgyû!";
					link.l1.go = "HollConvoy_fail";
				}
			}
			else
			{
				dialog.text = "Vigyázz, pajtás. Nem látom a holland kelet-indiai embert a századodban. Mondtam, hogy hozd ide, mint zsákmányt. Eladtad, és a pénzt megtartottad magadnak, mi?";
				link.l1 = "Várj, nekem kellett volna elhoznom a hajót? Azt hittem, csak az ezüstöt akarod.";
				link.l1.go = "HollConvoy_noShip";
			}
		break;
		
		case "HollConvoy_noShip":
			dialog.text = "Charlie Knippel-t senki sem nézheti bolondnak, pajtás! Tisztán emlékszem, mit mondtam magának, és mit nem. Megszegted a megállapodásunk feltételeit, és egyetlen becsületes angol sem fog veled dolgozni, itt nincs helye a gazembereknek. Takarodj a házamból, patkány!";
			link.l1 = "Akkor a pokolba veled, együgyû!";
			link.l1.go = "HollConvoy_fail";
		break;
		
		case "HollConvoy_fail":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "2-3");
			CloseQuestHeader("Holl_Gambit");
			DeleteAttribute(pchar, "questTemp.HWIC.Eng");//зачищаем для возможности отката к голландскому варианту
			pchar.questTemp.HWIC.Fail2 = "true";
		break;
		
		case "HollConvoy_complete":
			dialog.text = "Látogasson meg holnap, és bemutatom a patrónusomnak. Ô majd felajánl neked valami olyan munkát, ami méltó a képességeidhez. Plusz gondoskodik a... pénzügyi ösztönzésedrôl. Tûnés!";
			link.l1 = "Rendben, Mr. Knippel. Holnap itt leszek.";
			link.l1.go = "exit";
			npchar.greeting = "knippel_2";
			AddDialogExitQuestFunction("HollConvoy_Remove");
			AddQuestRecord("Holl_Gambit", "2-4");
			SetTimerFunction("EnglandGambit_2_ZadanieStart", 0, 0, 1);
			pchar.questTemp.HWIC.Eng = "Wait";
			AddSimpleRumourCity("Azt mondják, hogy elfogtál egy ezüsttel teli holland hajót. Szép munka! Maga egy bátor tengerész, kapitány! Isten éltessen!", "SentJons", 10, 3, "");
		break;
		
		case "Fleetwood_house":
			dialog.text = "Ugyanezt kérdeztem magamtól... Valami szemétláda ôrölt borsot szórt Fleetwood kapitány szemébe, és mellkason szúrta, mielôtt Richardnak még sikerült volna megragadnia a pengéjét. A gyilkos abban reménykedett, hogy egyetlen szúrással végezhet a kapitánnyal, hiszen nem volt ideje egy másikra, de nem sikerült neki. Fleetwood kapitány mindig kurírszalagot visel a kabátja alatt\nA mocskos söpredéknek, láncra lôve a máját, sikerült elmenekülnie és a földre kerülnie. Úgy tûnik, vannak barátai a városban. Az egyetlen részlet, amire a kapitány emlékszik, hogy a bérgyilkosnak csak egy szeme van. Ez azonban nem sokat segít, rengeteg hozzá hasonló küklopsz kóborol mostanában a dokkokban\nRichard rengeteg vért vesztett, és a bors iszonyúan irritálta a szemét, úgyhogy már majdnem vak...";
			link.l1 = "Ôrölt bors? Ez elég drága módja annak, hogy megvakítson valakit. Fleetwood nagyon felhúzhatott valakit. Sajnálom a kapitányát. Találtak már valamit a támadó után?";
			link.l1.go = "Fleetwood_house_1";
		break;
		
		case "Fleetwood_house_1":
			dialog.text = "Fleetwood kapitány tengerészgyalogosai átkutatták az egész várost és a helyi öblöket, de nem találtak semmit, láncot lôttek a nyakukba! Ha nem találtuk meg rögtön a támadás után, akkor most már nincs esélyünk megtalálni a rohadékot. Fleetwood kapitánynak sok ellensége van... De, kapitány, a parancsnokom a baleset ellenére is látni akarja magát. Most a házában pihen, úgyhogy menjünk el hozzá. Kövessetek!";
			link.l1 = "Menjen elôre, Mr. Knippel.";
			link.l1.go = "Fleetwood_house_2";
		break;
		
		case "Fleetwood_house_2":
			chrDisableReloadToLocation = true;//закрыть локацию
			bDisableFastReload = true;//закроем быстрый переход
			LocatorReloadEnterDisable("SentJons_town", "reload1_back", true);
			LocatorReloadEnterDisable("SentJons_town", "reload2_back", true);
			LocatorReloadEnterDisable("SentJons_town", "gate_back", true);//чтобы не сбежал
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "SentJons_town", "reload", "houseH1", "OpenTheDoors", -1);
			pchar.quest.Knippel_Outside.win_condition.l1 = "location";
			pchar.quest.Knippel_Outside.win_condition.l1.location = "SentJons_town";
			pchar.quest.Knippel_Outside.function = "Knippel_GoTown";
			LocatorReloadEnterDisable("SentJons_town", "houseSP3", true);
			sld = characterFromId("Fleetwood");
			LAi_SetStayType(sld);
			ChangeCharacterAddressGroup(sld, "SentJons_houseSP3_room", "goto", "goto1");
			AddLandQuestMark(sld, "questmarkmain");
			pchar.GenQuestBox.SentJons_houseSP3_room = true;
			pchar.GenQuestBox.SentJons_houseSP3_room.box1.money = 110000;
		break;
		
		case "InFleetwoodHouse":
			dialog.text = "Fleetwood kapitány fent van a szobájában. Menjetek hozzá, már vár titeket. Én itt maradok.";
			link.l1 = "Értettem, Mr. Knippel. Máris indulok.";
			link.l1.go = "exit";	
		break;
		
		case "Knippel_ToOfficer":
			dialog.text = "Figyeljen, kapitány... Fleetwood kapitány biztonságban és jó kezekben van. Segíteni akarok, hogy bosszút álljon azon a szemétládán, aki megtámadta. Felajánlom a szolgálataimat, mint tüzértiszt. A vívásban nem vagyok túl jó, ahhoz túl öreg vagyok, de a topgallantokat ezer lépésrôl le tudom ütni egy kereskedelmi hajóról.";
			link.l1 = "Na ezt szeretném látni. Üdvözlöm a fedélzeten, Mr. Knippel!";
			link.l1.go = "Knippel_ToOfficer_1";	
		break;
		
		case "Knippel_ToOfficer_1":
			LocatorReloadEnterDisable("SentJons_town", "reload1_back", false);
			LocatorReloadEnterDisable("SentJons_town", "reload2_back", false);
			LocatorReloadEnterDisable("SentJons_town", "gate_back", false);//откроем локаторы
			//Книппеля - в офицеры
			npchar.quest.OfficerPrice = sti(pchar.rank)*500;
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(npchar.id);
			npchar.OfficerWantToGo.DontGo = true; //не пытаться уйти
			npchar.HalfImmortal = true;//полубессмертен
			npchar.loyality = 20;
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			SetFunctionTimerCondition("GotoBridgetownOver", 0, 0, 30, false);//на все дела - 1 месяц
			AddSimpleRumourCity("Azt mondják, hogy maga Sir Richard Fleetwood is adós az önnel való kapcsolatával. Ön nagyon fontos ember a városunkban, uram.", "SentJons", 10, 3, "");
		break;
		
		case "hired":
			dialog.text = "Ahoj kapitány! Szüksége van valamire?";
			link.l1 = "Nem, semmit.";
			link.l1.go = "exit";
			NextDiag.TempNode = "hired";
		break;
		
		case "MC_GoAway":
			PlaySound("Voice\English\hambit\Charlie Knippel-07.wav");
			if (pchar.questTemp.HWIC.Eng == "MirageFail")
			{
				dialog.text = "Te egy komplett bohóc vagy, pajtás, lánclövés a seggembe! Elmulasztottál egy elemi feladatot - a 'Mirage elfogása 'ValkyrieValkyrie' \nSzemélyzetünk nem szolgál tovább a parancsnokságod alatt. Biztosak vagyunk benne, hogy Sir Fleetwood helyeselni fogja a döntésünket, ô ugyanolyan kevéssé szereti az idiótákat, mint mi.";
				link.l1 = "Baszd meg te és a mestered!";
				link.l1.go = "exit";
			}
			if (pchar.questTemp.HWIC.Eng == "GotoBridgetown" || pchar.questTemp.HWIC.Eng == "SeekVanBerg")
			{
				dialog.text = "Te egy komplett idióta vagy, haver, láncot lôttél a seggembe! Túl sok idôt vesztegettünk a személyes problémáid megoldására\nA legénységünk nem szolgál téged tovább. Biztosak vagyunk benne, hogy Sir Fleetwood jóváhagyja a döntésünket, ô is ugyanolyan kevéssé szereti az idiótákat, mint mi.";
				link.l1 = "Baszd meg te és a mestered!";
				link.l1.go = "exit";
			}
			if (pchar.questTemp.HWIC.Eng == "VanBergFailInWorld")
			{
				dialog.text = "Te egy komplett idióta vagy, haver, láncot lôttél a seggembe! Azt mondták neked, hogy játssz egy magányos kereskedôt a 'Valkyrie', és mit csináltál? Elijesztetted a kalózt a flottilláddal!\nBiztosak vagyunk benne, hogy Sir Fleetwood helyeselni fogja a döntésünket, ô ugyanúgy nem szereti az idiótákat, mint mi.";
				link.l1 = "Baszd meg te és a mestered!";
				link.l1.go = "exit";
			}
			if (pchar.questTemp.HWIC.Eng == "MirageTake")
			{
				dialog.text = "Te egy komplett idióta vagy, haver, láncot lôttél a seggembe! Úgy döntöttél, hogy másra pazarolod az idônket, mint a 'Mirage' elfogására és Antigua felé hajózásra?\nA legénységünk nem szolgál téged tovább. Biztosak vagyunk benne, hogy Sir Fleetwood jóváhagyja majd a döntésünket, ô ugyanúgy nem szereti az idiótákat, mint mi.";
			link.l1 = "Baszd meg te és a mestered!";
			link.l1.go = "exit";
			}
			PChar.quest.Munity = "Deads";
			LAi_LocationFightDisable(&Locations[FindLocation("Ship_deck")], false);
			if(sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_VALCIRIA)//если сам на Валькирии
			{
				pchar.Ship.Type = GenerateShipExt(SHIP_TARTANE, true, pchar);
				pchar.Ship.name = "Boat";
				SetBaseShipData(pchar);
				SetCrewQuantityOverMax(PChar, 0);
			}
			else
			{
				for(i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if(iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_VALCIRIA)
						{
							pchar.questTemp.HWIC.Eng.CompanionIndex = sld.Index;
							sld = GetCharacter(sti(pchar.questTemp.HWIC.Eng.CompanionIndex));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
			}
			LAi_CharacterDisableDialog(npchar);
			LAi_SetImmortal(npchar, true);
			ChangeCharacterAddressGroup(npchar, "SentJons_houseH1", "goto", "goto1");//Книппеля домой
			pchar.questTemp.HWIC.Eng = "end";
			pchar.questTemp.HWIC.Detector = "eng_fail";
			CloseQuestHeader("Holl_Gambit");
		break;
		
		case "OnCuracao":
			pchar.quest.HWICEng_toBarbadosOver.over = "yes";//снять прерывание
			dialog.text = "Üdvözletem, kapitány. Örülök, hogy látom!";
			link.l1 = "Üdvözlöm, Mr. Knippel. Van pénze? Adja ide, és menjünk Willemstadba Abigailért. Csatlakozik hozzám?";
			link.l1.go = "OnCuracao_1";	
		break;
		
		case "OnCuracao_1":
			dialog.text = "Kapitány, figyeljen... Nem kell most sehova sem mennünk.";
			link.l1 = "Mirôl beszélsz? Ez badarság!";
			link.l1.go = "OnCuracao_2";	
		break;
		
		case "OnCuracao_2":
			dialog.text = "Van egy levelem Fleetwood kapitánytól önnek. És a pénz. De ez a pénz nem Abigail apjának lesz, hanem neked. Kétszázezer pezó. Olvasd el a levelet, és próbáld meg nem túl szigorúan ítélni...";
			link.l1 = "Mi a fene folyik itt manapság?! Újabb kellemetlen meglepetés? Add ide a levelet!";
			link.l1.go = "OnCuracao_3";	
		break;
		
		case "OnCuracao_3":
			DialogExit();
			NextDiag.CurrentNode = "OnCuracao_4";
			AddMoneyToCharacter(pchar, 200000);
			LAi_SetCitizenType(npchar);
			npchar.lifeday = 1;//ещё денек пусть погуляет по пляжу
			pchar.quest.Holland_ShoreAttack.win_condition.l1 = "location";
			pchar.quest.Holland_ShoreAttack.win_condition.l1.location = "Curacao";
			pchar.quest.Holland_ShoreAttack.function = "CreateHollandShorePatrol";//патруль в прибрежных водах
			LocatorReloadEnterDisable("SentJons_town", "basement1_back", false);//открыть подземелье
			pchar.questTemp.HWIC.Eng = "MerdokMeeteng";
			AddQuestRecordInfo("LetterFromFleetwood", "1");
			AddQuestRecord("Holl_Gambit", "2-23");
			AddLandQuestMark(npchar, "questmarkmain");
		break;
		
		case "OnCuracao_4":
			dialog.text = "Olvastad, kapitány? Ôszinte leszek. Szégyellem magam Fleetwood kapitány miatt, és azért, amit tett, láncot lôtt a... á, bassza meg! Rodenburg feldühödött, amikor megtudta, hogy Abigailnek viszonya van Richarddal. Gyalogos járôrök pásztázzák Curacaót, és a Cég katonai hajói cirkálnak a helyi vizeken. El kell tûnnünk innen a fenébe.\n Kapitány, kell egy tüzér? Nincs szükségem luxusra - csak egy normális, rendszeres tengeri adagra. A vívásban nem vagyok olyan jó, ahhoz túl öreg vagyok, de a topgallantokat ezer lépésrôl le tudom verni egy kereskedelmi hajóról.";
			link.l1 = "Hát a fenébe is, szeretném látni, ahogy ezt megcsinálja, Mr. Knippel. Üdvözlöm a legénységben!";
			link.l1.go = "Knippel_hire";
			link.l2 = "Sajnálom, hogy egyáltalán segítettem nektek, angol gazembereknek. Nem tudom, hogyan mászhatnék ki ebbôl a szarból. Menj a saját utadon, elegem van a meglepetésekbôl.";
			link.l2.go = "Knippel_exit";
			DelLandQuestMark(npchar);
		break;
		
		case "Knippel_hire":
			DialogExit();
			DeleteAttribute(npchar, "LifeDay");
			npchar.quest.OfficerPrice = sti(pchar.rank)*200;
			npchar.OfficerWantToGo.DontGo = true;
			DeleteAttribute(npchar, "CompanionDisable");//теперь можем и в компаньоны
			DeleteAttribute(npchar, "HalfImmortal");
			npchar.loyality = MAX_LOYALITY;
			npchar.OfficerImmortal = true;
			npchar.Health.HP       = 60.0; 
			npchar.Health.maxHP    = 60.0;
			SetCharacterPerk(npchar, "ShipEscape");
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, true);
			npchar.Payment = true;
			LAi_SetImmortal(npchar, false);
			LAi_SetHP(npchar, 120, 120);
			LAi_SetOfficerType(npchar);
			npchar.greeting = "knippel_hire";
			NextDiag.CurrentNode = "Knippel_officer";
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			SaveCurrentNpcQuestDateParam(npchar, "HiredDate");
			
			//Sinistra - через 2 месяца стартует личный квест Чарли Книппеля "Длинные тени старых грехов"
			SetTimerCondition("DTSG_Start", 0, 0, 60, false);
		break;
		
		case "Knippel_exit":
			DialogExit();
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2", "none", "", "", "", -1);
		break;
		
//------------------------------------------------против всех-----------------------------------------------
		case "Knippel_abordage":
			dialog.text = "Vigyázz, te fattyú! Miért támadtátok meg ezt a békés holland hajót? Nincs nálam semmi értékes áru vagy arany, láncot lôttek a seggembe!";
			link.l1 = "Holland hajó? Haha! Ne nevettess, 'Hollandi'. megtámadtam a brigantinedet, hogy elfogjalak, kedves Charlie. Üdvözöllek a raktáramban. Beszélgetni fogunk arról, hogy hová hajózol és miért...";
			link.l1.go = "Knippel_abordage_1";	
		break;
		
		case "Knippel_abordage_1":
			AddQuestRecord("Holl_Gambit", "3-20");
            pchar.quest.Knippel_DieHard.over = "yes";
		    DoQuestCheckDelay("LAi_ReloadBoarding", 1.0);
            DialogExit();
			LAi_SetPlayerType(pchar);
			pchar.questTemp.HWIC.Self = "KnippelPrisoner";
			npchar.lifeday = 0;
			SetFunctionTimerCondition("RemoveKnippelOver", 0, 0, 1, false);//таймер до конца суток, ибо нефиг
		break;
		
		case "Knippel_prisoner":
			DelLandQuestMark(npchar);
			PlaySound("Voice\English\hambit\Charlie Knippel-07.wav");
			dialog.text = "Te egy ördög vagy, kalóz... A pokolban fogsz égni minden bûnödért! Cseszd meg...";
			link.l1 = "Nyugi, prédikátor. Úgy prédikálsz, mint egy puritán. Jobb lenne, ha elôbb a lelked állapotával foglalkoznál.";
			link.l1.go = "Knippel_prisoner_1";
		break;
		
		case "Knippel_prisoner_1":
			dialog.text = "Mit tervezel, gazember? Mit akarsz a parancsnokomtól és a szegény holland lánytól?";
			link.l1 = "Ez nem a te dolgod, Charlie. Nincs rád többé szükségem. Kelj fel!";
			link.l1.go = "Knippel_prisoner_2";	
		break;
		
		case "Knippel_prisoner_2":
			dialog.text = "Meg akarsz ölni? Méltó egy ilyen szemétládához, mint te. *köpköd* Baszd meg!";
			link.l1 = "Kelj fel, Charlie. Mondd el az utolsó imáidat.";
			link.l1.go = "Knippel_prisoner_3";	
		break;
		
		case "Knippel_prisoner_3":
			DialogExit();
			LAi_SetActorType(pchar);
			sld = characterFromId("KnippelClone");
			LAi_SetActorType(sld);
			LAi_ActorAnimation(sld, "Ground_StandUp", "Kill_Knippel", 3.5);
			pchar.quest.RemoveKnippelOver.over = "yes";//снять таймер
		break;
		
		//--> ----------------------------------- офицерский блок ------------------------------------------
		case "Knippel_officer":
			dialog.text = "Ahoj kapitány, a lánc a seggembe lôtt!";
			if (CheckAttribute(pchar, "questTemp.Dolly_Tieyasal") && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				Link.l4 = "Mr. Knippel, Tayasal ôsi, elveszett indiai városába megyek. Tisztázzuk, ez egy nagyon veszélyes utazás lesz, és egyben szokatlan is - ezen a... mágikus bálványon keresztül kell oda eljutnunk. Csatlakozol hozzám?";
				Link.l4.go = "tieyasal";
			}
			
			////////////////////////казначей///////////////////////////////////////////////////////////
           	// boal отчёт о корабле
			if(CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
			{
			    Link.l11 = "Mr. Knippel, adjon teljes jelentést a hajóról.";
			    Link.l11.go = "QMASTER_1";
				
			    // Warship. Автозакупка товара
				Link.l12 = "Azt akarom, hogy minden alkalommal, amikor kikötünk, vásároljon bizonyos árukat.";
				Link.l12.go = "QMASTER_2";
			}
			
			if (CheckAttribute(NPChar, "IsCompanionClone"))//////////////////компаньон//////////////////////////////////////////////
			{
				//dialog.text = "Az Ön utasítására érkeztem, kapitány.";
				Link.l2 = "Több parancsot kell kiadnom önnek.";
				Link.l2.go = "Companion_Tasks";
				NextDiag.TempNode = "Knippel_officer";// не забыть менять в зависисомости от оффа
				break;
			}
			Link.l1 = "Hallgassa meg a parancsaimat!";
            Link.l1.go = "stay_follow";
			link.l2 = "Semmiség. Lelépni!";
			link.l2.go = "exit";
			NextDiag.TempNode = "Knippel_officer";
		break;
		
		/////////////////////////// ответы для казначея ///////////////////////////////////
		case "QMASTER_1":
			dialog.Text = "Süllyessz el... A fegyverek rendben vannak, kicseréljük azokat, amelyek felrobbannak, és szárazon és biztonságban tartjuk a puskaporunkat. Milyen jelentést várt, kapitány? Én egy öreg ágyúöntô vagyok, nem egy tárcavezetô. Láncra lôttem a seggem, de én vagyok a legjobb ágyús a Karib-tengeren, ne feledje!";
			Link.l1 = "Ne vitatkozzunk, Mr. Knippel, maga érti a szakmáját. Majd én magam találok egy pénztárost, ne aggódjon.";
			Link.l1.go = "exit";
		break;	

		case "QMASTER_2":
			dialog.text = "Azt akarja, hogy az öreg Charlie az ágyúfedélzetet cserélje le a hátsó fedélzetre? Kapitány, én hajókat süllyesztek el, nem harcolok minden egyes pesóért. És biztos vagyok benne, hogy az elsô kolónián, ahol ezt kipróbáljuk, ki fognak nyúlni.";
			link.l1 = "De persze, Mr. Knippel... El kéne kezdenem keresni egy megfelelô pénztáros után.";
			link.l1.go = "exit";
		break;
		
		//Указания для компаньона 19.02.08 -->/////////////////////////////////////////////////////////////////////////////////////////
		case "Companion_Tasks":
			dialog.Text = "Hallgatlak téged.";
			Link.l1 = "A beszállásról van szó.";
			Link.l1.go = "Companion_TaskBoarding";
			Link.l2 = "A hajójáról van szó.";
			Link.l2.go = "Companion_TaskChange";
			if (bBettaTestMode) // Только при бета-тесте
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
			Link.l1 = "Szeretném, ha a beszállás után nem cserélné el a hajóját egy másikra. A hajója túl értékes.";
			Link.l1.go = "Companion_TaskChangeNo";
			Link.l2 = "Amikor ellenséges hajókra szállsz fel, elviheted ôket magadnak, ha történetesen tisztességesek.";
			Link.l2.go = "Companion_TaskChangeYes";
			break;

		case "Companion_TaskBoardingNo":
			dialog.Text = "Igenis!";
			Link.l1 = "Pihenj.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = false;
			break;

		case "Companion_TaskBoardingYes":
			dialog.Text = "Úgy lesz.";
			Link.l1 = "Pihenj.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = true;
			break;

		case "Companion_TaskChangeNo":
			dialog.Text = "Igenis!";
			Link.l1 = "Úgy lesz.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = false;
			break;

		case "Companion_TaskChangeYes":
			dialog.Text = "Úgy lesz.";
			Link.l1 = "Pihenj.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = true;
			break;
			//	<========////////////////////////////////////////

		case "stay_follow":
            dialog.Text = "Rendelések?";
            Link.l1 = "Álljatok ide!";
            Link.l1.go = "Boal_Stay";
            Link.l2 = "Kövessetek és tartsátok a lépést!";
            Link.l2.go = "Boal_Follow";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			if(sGun != "")
			{
				rItm = ItemsFromID(sGun);
				if(CheckAttribute(NPChar, "chr_ai.gun.bulletNum") && sti(NPChar.chr_ai.gun.bulletNum) > 1)
				{
					Link.l3 = "Változtassátok meg a lôszer típusát a lôfegyvereitekhez.";
					Link.l3.go = "SetGunBullets";
				}	
			}		
		break;
		
		case "SetGunBullets":
			Dialog.Text = "A lôszer típusának kiválasztása:";
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
			NextDiag.CurrentNode = NextDiag.TempNode;
			rItem = ItemsFromID(sBullet);
			notification(GetFullName(NPChar)+" "+XI_ConvertString("AmmoSelectNotif")+GetConvertStr(rItem.name, "ItemsDescribe.txt")+"", "AmmoSelect");
			DeleteAttribute(NPChar,"SetGunBullets");
			DialogExit();
		break;		
		
        case "Boal_Stay":
            Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
            AddDialogExitQuestFunction("LandEnc_OfficerStay");
            dialog.Text = "Megváltoztatjuk a rendelkezést!";
            Link.l1 = "Elmehetnek.";
            Link.l1.go = "Exit";
            Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
        break;
        
        case "Boal_Follow":
            SetCharacterTask_FollowCharacter(Npchar, PChar);
            dialog.Text = "Megváltoztatjuk a rendelkezést!";
            Link.l1 = "Elmehetnek.";
            Link.l1.go = "Exit";
        break;
	//<-- ----------------------------------- офицерский блок ----------------------------------------
	
	// на Тайясаль
		case "tieyasal":
			dialog.text = "Szolgálatom alatt nagyon kötôdöm hozzád, "+pchar.name+", és nem hagyom cserben a kapitányomat. Ha kell, a pokolba is követnélek. Én veled vagyok!";
			link.l1 = "Köszönöm, Knippel úr! Örülök, hogy igazam volt veled kapcsolatban.";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "Mikor kezdjük el, láncot lôttek a szemembe?";
			link.l1 = "Kicsit késôbb. Fel kell készülnünk rá.";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			DialogExit();
			AddQuestRecord("Tieyasal", "22");
			npchar.quest.Tieyasal = "teleport";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//--> блок реагирования на попытку залезть в сундук
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Maga egy "+ GetSexPhrase("tolvaj, uram! Ôrök, vigyétek","tolvajt, lány! Ôrök, vigyétek") +"!!!", "Csak nézd meg ezt! Abban a pillanatban, hogy hátat fordítottam, úgy döntöttél, hogy megnézed a mellkasomat! Vigyétek a tolvajt!!!", "ôrök! Rablás! Elkapni a tolvajt!!!");
			link.l1 = "A francba!";
			link.l1.go = "exit";
			LAi_group_Attack(NPChar, Pchar);
		break;
		//<-- блок реагирования на попытку залезть в сундук
	}
}
