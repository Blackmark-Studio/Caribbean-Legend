// диалог по городам
// Это мастер тюнинга
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    string 	sTemp;
	int 	amount, iSan, iOil, iSil, iRop;
	int iTemp, iSum; // 280912
	ref 	shTo;
	string 	s1;
	
	switch (Dialog.CurrentNode)
	{		
		// -----------------------------------Диалог первый - первая встреча
		case "First time":  // перехват основного диалога, только один раз
			if(NPChar.quest.meeting == "0")
			{
				Dialog.Text = "Fúúú... Micsoda szörnyû klíma... A nevem " + GetFullName(npchar) + ", és az Isten verjen meg, ha nem én vagyok a legjobb hajóépítô ezeken az isten háta mögötti szigeteken. De ez a páratartalom csak úgy ledönt a lábamról...";
				Link.l1 = pcharrepphrase("Ezer cápa, csak egy öregember mormogása hiányzott. A nevem " + GetFullName(pchar) + ", gondolom hallottál már rólam.",
					"Nem a nedvesség, hanem az öregség, uram. A nevem " + GetFullName(pchar) + ", azt hiszem, hallott rólam.");
				Link.l1.go = "node_1";
				npchar.quest.meeting = "1";
			}
			else // нужно, если по квестам будет сброс на  "First time"
			{
				dialog.text = "Ó, már megint te, aki mindig a problémáidról beszélsz... (köhögés).";
				link.l1 = pcharrepphrase("Igazad van, megint én vagyok az. De beszéljünk az üzletrôl, amíg még nem adtad oda Istennek a lelkedet.",
					"A memóriád jól szolgál, és most, ha megengeded, térjünk rá néhány konkrétabb kérdésre.");
				link.l1.go = "node_3";
				link.l2 = pcharrepphrase("Belefáradtam a mormolásodba. Viszontlátásra.",
					"Itt az ideje, hogy elmenjek. Elnézést a zavarásért.");
				link.l2.go = "exit";
			}
			NextDiag.TempNode = "Master_Ship";
			Dialog.CurrentNode = "Master_Ship";
		break;
		
		case "Master_Ship":
		//Jason ----------------------------------- Хронометр Алекса ------------------------------------------
			if (CheckAttribute(npchar, "quest.sextant") && CheckAttribute(pchar, "questTemp.AlexClock") && pchar.location == "Pirates_shipyard" && !CheckAttribute(npchar, "quest.clock"))
			{
				dialog.text = "Aha, kapitány "+GetFullName(pchar)+"! Milyen jó, hogy benéztél hozzánk!";
				Link.l1 = "Úgy tûnik, szükséged van rám valamiben, nem igaz? Általában nem vagy ilyen udvarias.";
				Link.l1.go = "clock_begin";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.AlexClock") && pchar.questTemp.AlexClock == "clock" && pchar.location == "Pirates_shipyard")
			{
				dialog.text = "Látom, hogy üres kézzel tért vissza hozzám, kapitány! Mi történt a... vendégekkel?";
				Link.l1 = "Elmentek. Megkértem ôket, és elmentek.";
				Link.l1.go = "clock_complete";
				break;
			}
		//<-- хронометр Алекса
			dialog.text = "Ó, már megint te, aki mindig a problémáidról beszélsz... (köhögés)";
			link.l1 = pcharrepphrase("Igazad van, megint én vagyok az. De beszéljünk az üzletrôl, amíg még nem adtad oda Istennek a lelkedet.",
	            "A memóriád jól szolgál, és most, ha megengeded, térjünk rá néhány konkrétabb kérdésre.");
			link.l1.go = "node_3";
			link.l2 = pcharrepphrase("Belefáradtam a mormolásodba. Viszontlátásra.",
				"Itt az ideje, hogy elmenjek. Elnézést a zavarásért.");
			link.l2.go = "exit";
			NextDiag.TempNode = "Master_Ship";
		break;

		case "node_1":
			dialog.text = "A fiatalok manapság... Soha nem tisztelnek senkit. Forró fejûek, kemény kezûek, mi kell nektek?";
			link.l1 = pcharrepphrase("Így van. De elôbb-utóbb mindennek vége szakad, és úgy tûnik, hogy a te idôd is közel van...",
				"Valami azt súgja, hogy fiatal korodban te sem feltétlenül tisztelted az idôsebbeket. Igazam van?");
			link.l1.go = "node_2";
		break;

		case "node_2":
			dialog.text = "Ne vitatkozz az idôsebbekkel, kölyök.";
			link.l1 = pcharrepphrase("Nyugalom. Nyugodj meg. Ne erôltesd túl magad, különben szívrohamot kaphatsz. Nem akarom, hogy engem vádoljanak a Karib-tenger legjobb hajóépítôjének halálával. Térjünk a tárgyra.",
				"Megbocsátom a durvaságát, csak a kora iránti tiszteletbôl. És most, ha befejezte, térjünk a tárgyra.");
			link.l1.go = "node_3";
			link.l2 = pcharrepphrase("Rendben, elég volt a kioktatásból! Viszontlátásra!",
				"Látom, nem fogunk egy véleményen lenni. Viszontlátásra.");
			link.l2.go = "exit";
		break;

		case "node_3":
			dialog.text = "(köhögés)... Az emberek nem hagynak békén egy idôs embert. Ezúttal mit akarsz tôlem, " + GetAddress_Form(NPChar) + "? ";
			link.l1 = pcharrepphrase("A hajógyár szolgáltatásait kell igénybe vennem.","Szeretném igénybe venni a hajógyár szolgáltatásait.");
			link.l1.go = "shipyard_dlg";
            Link.l2 = "Lenne egy kérdésem.";
			Link.l2.go = "quests"; //(пересылка в файл города)
			// -->
			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
			{
				link.l3 = "A pénzügyekrôl szeretnék beszélni.";
				link.l3.go = "LoanForAll";//(перессылка в файл города)
			}
			link.l9 = pcharrepphrase("A francba, van néhány sürgôs ügyem, amit el kell intéznem, viszlát.", "Ideje mennem. Bocsánat.");
			link.l9.go = "exit";
			NextDiag.TempNode = "Master_Ship";
		break;
		
		case "shipyard_dlg":			
			dialog.Text = "Gyerünk, mit akarsz? Ne zaklass egy öregembert...";
			link.l2 = "Csak a hajógyár szolgáltatásait szeretném igénybe venni.";
			link.l2.go = "shipyard";
			link.l3 = "Fegyverekre van szükségem a hajóhoz.";
			link.l3.go = "Cannons";
			if(RealShips[sti(Pchar.Ship.Type)].BaseType != SHIP_CURSED_FDM)
			{
					link.l4 = "Meg akarom változtatni a vitorláim kinézetét.";
					link.l4.go = "SailsGerald";
			}
			if(RealShips[sti(Pchar.Ship.Type)].BaseType == SHIP_CURSED_FDM && !CheckAttribute(npchar, "quest.FDM_hull"))
			{
					link.l50 = "A hajóm eléggé... különleges. Szeretnék néhány változtatást eszközölni.";
					link.l50.go = "FDM";
			}
			/* if(RealShips[sti(Pchar.Ship.Type)].BaseType == SHIP_CURSED_FDM && CheckAttribute(npchar, "quest.FDM_cabin") && npchar.quest.FDM_cabin == "cabin" && GetCharacterItem(pchar, "Chest") > 0)
			{
					link.l50 = "Több ládám van a kabin átépítéséhez.";
					link.l50.go = "FDM_cabin_pay";
			} */
			// Xenon -->
			if(RealShips[sti(Pchar.Ship.Type)].BaseType == SHIP_CURSED_FDM && CheckAttribute(npchar, "quest.FDM_hull") && npchar.quest.FDM_hull == "hull_waitmoney")
			{
					link.l50 = "A hajó átépítése miatt vagyok itt.";
					link.l50.go = "FDM_hull_givemoney";
			}

			if(RealShips[sti(Pchar.Ship.Type)].BaseType == SHIP_CURSED_FDM && CheckAttribute(npchar, "quest.FDM_hull") && npchar.quest.FDM_hull == "hull_waitmaterials")
			{
					link.l50 = "A hajó átépítése miatt vagyok itt.";
					link.l50.go = "FDM_hull_checkmaterials";
			}
			// <-- Xenon
			link.l9 = pcharrepphrase("A francba, van néhány sürgôs ügyem, amit el kell intéznem, viszlát.", "Ideje mennem. Bocsánat.");
			Link.l9.go = "ship_tunning_not_now";
		break;
		
		///////////////////////////////  квестовые ветки
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Milyen kérdései vannak?", "Miben segíthetek?"), "Nemrég megpróbált feltenni nekem egy kérdést...", "Ilyen kíváncsi emberekkel még nem találkoztam sem a hajógyáramban, sem máshol ebben a városban.",
                          "Mi ez a sok kérdés? Az én munkám az, hogy hajókat építsek. Gondoskodjunk errôl.", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Meggondoltam magam...", "Jelenleg nincs mirôl beszélnem."), "Umph, hová tûnt a memóriám...",
                      "Hm, nos...", "Rendben, menjünk...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (!CheckAttribute(npchar, "Step_Door"))
			{
				link.l2 = "Figyelj, szeretnék átmenni, de az az ajtó zárva van...";
				link.l2.go = "Step_Door_1";
			}

			if ((pchar.questTemp.different == "GiveShipLetters") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakAlexus"))
			{
				link.l1 = "Szeretnék egy üzletet ajánlani.";
				link.l1.go = "Al_ShipLetters_1";// генератор  "Найденные документы"
				pchar.questTemp.different.GiveShipLetters.speakAlexus = true;
			}
			if(CheckAttribute(pchar, "questTemp.AlexClock") && pchar.questTemp.AlexClock == "go") // 280912
			{
				link.l1 = "A fregatt anyagai miatt vagyok itt.";
				link.l1.go = "clock";
			}
			if(CheckAttribute(pchar, "questTemp.Tieyasal") && pchar.questTemp.Tieyasal == "begin" && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				link.l1 = "Figyelj, "+npchar.name+", láttad mostanában Miguel Dichosót Isla Tesorón?";
				link.l1.go = "tieyasal";
			}
		break;
//*************************** Генератор - "Найденные судовые документы" **************
		
		case "Al_ShipLetters_1":
			dialog.text = "Mondd meg a feltételeidet.";
			s1 = "Szerencsém volt, hogy találtam egy teljesen legális hajódokumentum csomagot, amit még nem kértek átkutatásra.";
			s1 = s1 + "A hajó a tengeren van, és nem zárták ki a lajstromból, ne aggódj. Csak egy vak bolond tulajdonosnak volt szerencsétlensége, hogy elvesztette ezeket a papírokat...";
			link.l1 = s1;
			link.l1.go = "Al_ShipLetters_2";			
		break;
		case "Al_ShipLetters_2":
			s1 = "Hadd nézzem meg! Tényleg frissen kitöltöttnek tûnik. Nos, a szerencse az ön javára, uram! ";
			s1 = s1 + "Valójában szükségem volt egy ilyen csomagra. Én viszont felajánlom önnek " + sti(pchar.questTemp.different.GiveShipLetters.price5) + " pezót. Mit szól hozzá?";
			dialog.text = s1;
			link.l1 = "Igazi királyi nagylelkûség! Természetesen egyetértek!";
			link.l1.go = "Al_ShipLetters_3";
			link.l2 = "Nem, nem hiszem.";
			link.l2.go = "exit";
		break;
		case "Al_ShipLetters_3":
			TakeItemFromCharacter(pchar, "CaptainBook"); 
			addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price5)); 
			ChangeCharacterComplexReputation(pchar,"nobility", -1); 
			OfficersReaction("bad"); 
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //снимаем таймер 
			AddQuestRecord("GiveShipLetters", "9");			
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit(); 
		break;
		

//*************************** Открывание двери ***************************
 		case "Step_Door_1":
			dialog.text = "Így van. Ha át akarsz menni ezen az ajtón, 20000 pezót kell fizetned. Ha nem fizet, nem nyitom ki. Ez nem egy ingyenkonyha. És amúgy sem tanácsolom, hogy odamenjen. Jobb lesz neked, ha nem mész...";
			if(sti(pchar.money) >= 20000)
			{
    			link.l1 = "Itt a pénzed. Nyissa ki.";
    			link.l1.go = "Step_Door_2";
            }
            else
            {
    			link.l1 = "Nincs ennyi pénzem.";
    			link.l1.go = "Step_Door_3";
            }
            link.l2 = "Nem lehet! Soha nem fizetnék egy ajtóért.";
    		link.l2.go = "exit";
		break;
		
 		case "Step_Door_2":
			npchar.Step_Door = true; // fix
			dialog.text = "Menj be. Az ajtó nyitva van. Ne aggódj a köszönet miatt!";
			link.l1 = "Nem, miért nem. Köszönöm, " + npchar.name + "...";
			link.l1.go = "exit";
			LocatorReloadEnterDisable("Pirates_Shipyard", "reload2", false);
            AddMoneyToCharacter(pchar, -20000);
			pchar.quest.CloseBermudesDungeonDoor.win_condition.l1 = "MapEnter";
            pchar.quest.CloseBermudesDungeonDoor.win_condition = "CloseBermudesDungeonDoor";
		break;
		
 		case "Step_Door_3":
			dialog.text = "Nos, ha megvan, gyere vissza. Különben ne próbálj meggyôzni. Semmi értelme...";
			link.l1 = "Argh, teljesen elakadt a szavam!";
			link.l1.go = "exit";
		break;
		
	// ------------------------------------------- хронометр Ђлекса ----------------------------------------------// Addon-2016 Jason замена дублонов на песо везде
		case "clock_begin":
			dialog.text = "Ugyan már, ne légy ilyen szigorú egy öregemberrel... Tényleg szükségem van a segítségére, kapitány.";
			link.l1 = "Mondja, mester. Mi történt veled?";
			link.l1.go = "clock_begin_1";
		break;
		
		case "clock_begin_1":
			sTotalTemp = "Steven Dodson";
			if (pchar.questTemp.Alex.Clock == "terrax") sTotalTemp = "Marcus Tyrex";
			dialog.text = "A Parti Testvérek új vezetôje, "+sTotalTemp+", új hajót rendelt, egy fregattot. Elég nehéz feladatokat is kitûzött: védett hajótest, gyors sebesség és jó manôverezôképesség, plusz a lehetô legnagyobb kaliberû ágyúk\nMegértem, hogy egy admirális, bocsánat a testvérek vezetôjének hajója valami különleges kell legyen, de ez azt jelenti, hogy különleges anyagokra van szükségem az építéséhez. Bizonyára hallottál már róluk. Vasfa, gyanta, hajóselyem és kötelek...";
			link.l1 = "Mesélj errôl a Testvérek vezetôjének. Vagy félsz, hogy "+sTotalTemp+" levágják a fejedet ezért?";
			link.l1.go = "clock_begin_2";
		break;
		
		case "clock_begin_2":
			dialog.text = "Mondtam neki... A helyzet az, hogy az új vezetônknek nincs ideje és lehetôsége megtalálni és elhozni ezeket az anyagokat. Tudnod kell, hogy milyen ritkaság ez. És kizárt, hogy nélkülük képes leszek építeni egy fregattot az említett tulajdonságokkal.";
			link.l1 = "És valószínûleg azt javaslod, hogy nekem kell anyagokat találnom a hajóhoz?";
			link.l1.go = "clock_begin_3";
		break;
		
		case "clock_begin_3":
			dialog.text = "Nos, igen. Ön a vezetônk jó barátja. "+sTotalTemp+" maga mondja, hogy sokat köszönhet neked, és hogy mindenféle tiszteletet követel tôled... Ezért gondoltam: ha már a barátja vagy, akkor talán nem ellenzed, hogy segíts neki? És hogy ugyanakkor: ugye tisztában vagy vele, hogy milyen kellemetlen helyzetben vagyok? Minden anyagot kifizetek, "+sTotalTemp+" nem szûkmarkú az aranyával.";
			link.l1 = "Nagyon sajnálom, mester, de nem vagyok kevésbé elfoglalt, mint "+sTotalTemp+". Attól tartok, hogy az anyaggyûjtés egy örökkévalóságig is eltarthat. Úgyhogy jobb, ha valaki mást kérdezel.";
			link.l1.go = "clock_exit";
			link.l2 = "Nos, ha "+sTotalTemp+" rendelt egy hajót tôled - akkor természetesen megpróbálok segíteni. Tényleg barátok vagyunk, és a barátoknak segíteniük kell egymásnak. Hány anyagra van szükséged?";
			link.l2.go = "clock_begin_4";
		break;
		
		case "clock_exit":
			dialog.text = "Ez nagyon rossz. Tényleg nagyon rossz. Számítottam rád. Nos, ahogy mondani szokták, a nem nemet jelent...";
			link.l1 = "...";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.AlexClock");
		break;
		
		case "clock_begin_4":
			dialog.text = "Hiányzik 100 egység vasfa, 150 konténer gyanta, 110 tekercs hajóselyem és 90 tekercs kenderkötél. Mit gondolsz? Meg tudnád találni nekem mindezt négy hónap alatt? Nem hiszem, hogy több idôm lenne.";
			link.l1 = "De legalább megpróbálhatom. És ami a fizetséget illeti?";
			link.l1.go = "clock_begin_5";
		break;
		
		case "clock_begin_5":
			dialog.text = "Itt vannak az áraim: vasfa 4000 pezó darabonként, gyanta 1400 pezó konténerenként, selyem 2500 pezó tekercsenként, és kötél 1500 pezó tekercsenként. És ha mindezt elhozza nekem, akkor egy nagyon szép ajándékot kap tôlem.";
			link.l1 = "Vajon mi lehet az?";
			link.l1.go = "clock_begin_6";
		break;
		
		case "clock_begin_6":
			dialog.text = "Elôbb hozzátok el nekem az anyagokat. De biztosíthatlak: jól fog neked jönni, és a dolog egyedülálló. nincs még egy ilyen a Karib-tengeren, sôt az egész világon sem. Remélem, a kíváncsiság eme kis szikrája felkeltette az érdeklôdésedet, hogy összegyûjtsd nekem az anyagokat.";
			link.l1 = "Hát, te aztán ravasz vagy, mint egy kobold, mester! Rendben, megegyeztünk.";
			link.l1.go = "clock_begin_7";
		break;
		
		case "clock_begin_7":
			dialog.text = "Nagyon boldog vagyok. Alig várom, hogy visszatérj.";
			link.l1 = "Remélem, nem tart túl sokáig...";
			link.l1.go = "clock_begin_8";
		break;
		
		case "clock_begin_8":
			DialogExit();
			pchar.questTemp.AlexClock = "go";
			npchar.quest.clock = "true";
			SetFunctionTimerCondition("AlexClock_Over", 0, 0, 122, false); // таймер
			AddQuestRecord("alex_clock", "1");
			// запоминаем переменные
			pchar.questTemp.AlexClock.Sandal = 100;
			pchar.questTemp.AlexClock.Oil = 150;
			pchar.questTemp.AlexClock.Shipsilk = 110;
			pchar.questTemp.AlexClock.Ropes = 90;
		break;
		
		case "clock":
			dialog.text = "Kitûnô! Mit hoztál nekem ma?";
			if (GetSquadronGoods(pchar, GOOD_SANDAL) > 0 && !CheckAttribute(npchar, "quest.sandal"))
			{
				iSan = GetSquadronGoods(pchar, GOOD_SANDAL);
				link.l1 = "Vasfa, a "+FindRussianQtyString(iSan)+"összegben.";
				link.l1.go = "sandal";
			}
			if (GetSquadronGoods(pchar, GOOD_OIL) > 0 && !CheckAttribute(npchar, "quest.oil"))
			{
				iOil = GetSquadronGoods(pchar, GOOD_OIL);
				link.l2 = "Gyanták, a "+FindRussianQtyString(iOil)+"mennyiségben.";
				link.l2.go = "oil";
			}
			if (GetSquadronGoods(pchar, GOOD_SHIPSILK) > 0 && !CheckAttribute(npchar, "quest.shipsilk"))
			{
				iSil = GetSquadronGoods(pchar, GOOD_SHIPSILK);
				link.l3 = "Hajóselyem, a "+FindRussianQtyString(iSil)+"összegben.";
				link.l3.go = "shipsilk";
			}
			if (GetSquadronGoods(pchar, GOOD_ROPES) > 0 && !CheckAttribute(npchar, "quest.ropes"))
			{
				iRop = GetSquadronGoods(pchar, GOOD_ROPES);
				link.l4 = "Kenderkötél, a "+FindRussianQtyString(iRop)+"mennyiségben.";
				link.l4.go = "ropes";
			}
			link.l5 = "Jelenleg semmi. Csak meg akartam gyôzôdni róla, hogy még mindig van megállapodásunk.";
			link.l5.go = "exit";
		break;
		
		case "clock_1":
			if (CheckAttribute(npchar, "quest.sandal") && CheckAttribute(npchar, "quest.oil") && CheckAttribute(npchar, "quest.shipsilk") && CheckAttribute(npchar, "quest.ropes")) // все привез
			{
				dialog.text = "Csodálatos! Minden anyagot megkaptam a szükséges mennyiségben. Köszönöm szépen a segítségét, kapitány. Nagyon sokat segített nekem.";
				link.l1 = "Igen, bármikor, mester. Én is nagyon elégedett vagyok: Segítettem egy barátomnak, és jó pénzt kerestem. És most térjünk vissza a beszélgetésünkre a titokzatos tárgyról, amit ígért nekem.";
				link.l1.go = "clock_2";
			}
			else
			{
				dialog.text = "Van még valami meglepetés a számomra, kapitány?";
				link.l1 = "Sajnos, egyelôre ennyi. Csak várjon tovább.";
				link.l1.go = "exit";
				link.l2 = "Igen, van még egy dolog...";
				link.l2.go = "clock";
			}
		break;
		
		case "sandal": // бакаут
			amount = sti(pchar.questTemp.AlexClock.Sandal);
			iSan = GetSquadronGoods(pchar, GOOD_SANDAL);
			iTemp = amount-iSan;
			if (iTemp > 0) // ещё не все привез
			{
				iSum = 4000*iSan;
				dialog.text = "Rendben, rendben. Szükségem lesz még "+FindRussianQtyString(amount)+" vasfára. Hoztál nekem "+FindRussianQtyString(iSan)+". Szóval, már csak a "+FindRussianQtyString(iTemp)+"kell hoznod nekem. Rendben, 4000 pezó darabonként, a jutalmad összesen "+FindRussianMoneyString(iSum)+". Kérem, vegye el.";
				link.l1 = "Köszönöm! A többit hamarosan megkapod.";
				link.l1.go = "clock_1";
				RemoveCharacterGoods(pchar, GOOD_SANDAL, iSan);
				pchar.questTemp.AlexClock.Sandal = iTemp; // столько осталось довезти
				AddQuestRecord("alex_clock", "2");
				AddQuestUserData("alex_clock", "sGood", "ironwood");
				AddQuestUserData("alex_clock", "sQty", FindRussianQtyString(iTemp));
			}
			else
			{
				iSum = 4000*amount;
				dialog.text = "Rendben, rendben. Szükségem lesz még "+FindRussianQtyString(amount)+"  vasfára. Hoztál nekem "+FindRussianQtyString(iSan)+". Szóval, most már gondoskodtunk a vasfáról! Rendben, 4000 pezó darabonként, a jutalmad összesen "+FindRussianMoneyString(iSum)+". Kérem, vegyék el.";
				link.l1 = "Köszönöm!";
				link.l1.go = "clock_1";
				RemoveCharacterGoods(pchar, GOOD_SANDAL, amount);
				npchar.quest.sandal = "true";
				AddQuestRecord("alex_clock", "3");
				AddQuestUserData("alex_clock", "sGood", "ironwood");
			}
			AddMoneyToCharacter(pchar, iSum);
		break;
		
		case "oil": // смолы
			amount = sti(pchar.questTemp.AlexClock.Oil);
			iOil = GetSquadronGoods(pchar, GOOD_OIL);
			iTemp = amount-iOil;
			if (iTemp > 0) // ещё не все привез
			{
				iSum = 1400*iOil;
				dialog.text = "Rendben, rendben. Nekem is szükségem lesz "+FindRussianQtyString(amount)+" gyantára. Hoztál nekem "+FindRussianQtyString(iOil)+". Szóval, már csak a "+FindRussianQtyString(iTemp)+"kell hoznod nekem. Rendben, 1400 pezó egy konténerre, a jutalmad összesen "+FindRussianMoneyString(iSum)+". Kérem, vegye el.";
				link.l1 = "Köszönöm! A többit hamarosan megkapod.";
				link.l1.go = "clock_1";
				RemoveCharacterGoods(pchar, GOOD_OIL, iOil);
				pchar.questTemp.AlexClock.Oil = iTemp; // столько осталось довезти
				AddQuestRecord("alex_clock", "2");
				AddQuestUserData("alex_clock", "sGood", "resins");
				AddQuestUserData("alex_clock", "sQty", FindRussianQtyString(iTemp));
			}
			else
			{
				iSum = 1400*amount;
				dialog.text = "Rendben, rendben. Nekem is szükségem lesz "+FindRussianQtyString(amount)+" gyantára. Hoztál nekem "+FindRussianQtyString(iOil)+". Szóval, most már gondoskodtunk a gyantákról! Rendben, 1400 pezó egy konténer, a jutalmad összesen "+FindRussianMoneyString(iSum)+". Kérem, vegyék el.";
				link.l1 = "Köszönöm!";
				link.l1.go = "clock_1";
				RemoveCharacterGoods(pchar, GOOD_OIL, amount);
				npchar.quest.oil = "true";
				AddQuestRecord("alex_clock", "3");
				AddQuestUserData("alex_clock", "sGood", "resins");
			}
			AddMoneyToCharacter(pchar, iSum);
		break;
		
		case "shipsilk": // шёлк
			amount = sti(pchar.questTemp.AlexClock.Shipsilk);
			iSil = GetSquadronGoods(pchar, GOOD_SHIPSILK);
			iTemp = amount-iSil;
			if (iTemp > 0) // ещё не все привез
			{
				iSum = 2600*iSil;
				dialog.text = "Rendben, rendben. Nekem is szükségem lesz "+FindRussianQtyString(amount)+" selyemre. Hoztál nekem "+FindRussianQtyString(iSil)+". Szóval, már csak a "+FindRussianQtyString(iTemp)+"kell hoznod nekem. Rendben, 2600 pezó darabonként, a jutalmad összesen "+FindRussianMoneyString(iSum)+". Kérem, vegye el.";
				link.l1 = "Köszönöm! A többit hamarosan megkapod.";
				link.l1.go = "clock_1";
				RemoveCharacterGoods(pchar, GOOD_SHIPSILK, iSil);
				pchar.questTemp.AlexClock.Shipsilk = iTemp; // столько осталось довезти
				AddQuestRecord("alex_clock", "2");
				AddQuestUserData("alex_clock", "sGood", "silk");
				AddQuestUserData("alex_clock", "sQty", FindRussianQtyString(iTemp));
			}
			else
			{
				iSum = 2600*amount;
				dialog.text = "Jól van, rendben. Nekem is szükségem lesz "+FindRussianQtyString(amount)+" selyemre. Hoztál nekem "+FindRussianQtyString(iSil)+". Szóval, most már gondoskodtunk a selyemrôl! Tehát, 2600 pezó darabonként, a jutalmad összesen "+FindRussianMoneyString(iSum)+". Kérem, vegye el.";
				link.l1 = "Köszönöm!";
				link.l1.go = "clock_1";
				RemoveCharacterGoods(pchar, GOOD_SHIPSILK, amount);
				npchar.quest.shipsilk = "true";
				AddQuestRecord("alex_clock", "3");
				AddQuestUserData("alex_clock", "sGood", "silk");
			}
			AddMoneyToCharacter(pchar, iSum);
		break;
		
		case "ropes": // канаты
			amount = sti(pchar.questTemp.AlexClock.Ropes);
			iRop = GetSquadronGoods(pchar, GOOD_ROPES);
			iTemp = amount-iRop;
			if (iTemp > 0) // ещё не все привез
			{
				iSum = 1500*iRop;
				dialog.text = "Rendben, rendben. Nekem is szükségem lesz "+FindRussianQtyString(amount)+" kötelekre. Hoztál nekem "+FindRussianQtyString(iRop)+". Szóval, már csak a "+FindRussianQtyString(iTemp)+"kell hoznod nekem. Tehát, 1500 pezó darabonként, a jutalmad összesen "+FindRussianMoneyString(iSum)+". Kérem, vegye el.";
				link.l1 = "Köszönöm! A többit hamarosan megkapod.";
				link.l1.go = "clock_1";
				RemoveCharacterGoods(pchar, GOOD_ROPES, iRop);
				pchar.questTemp.AlexClock.Ropes = iTemp; // столько осталось довезти
				AddQuestRecord("alex_clock", "2");
				AddQuestUserData("alex_clock", "sGood", "ropes");
				AddQuestUserData("alex_clock", "sQty", FindRussianQtyString(iTemp));
			}
			else
			{
				iSum = 1500*amount;
				dialog.text = "Rendben, rendben. Nekem is szükségem lesz "+FindRussianQtyString(amount)+" kötelekre. Hoztál nekem "+FindRussianQtyString(iRop)+". Szóval, a kötelekrôl már gondoskodtunk. Rendben, 1500 pezó darabonként, a jutalmad összesen "+FindRussianMoneyString(iSum)+". Kérem, vegyék el.";
				link.l1 = "Köszönöm!";
				link.l1.go = "clock_1";
				RemoveCharacterGoods(pchar, GOOD_ROPES, amount);
				npchar.quest.ropes = "true";
				AddQuestRecord("alex_clock", "3");
				AddQuestUserData("alex_clock", "sGood", "ropes");
			}
			AddMoneyToCharacter(pchar, iSum);
		break;
		
		case "clock_2":
			dialog.text = "Igen, igen... az én dolgomról, természetesen. M-m-mmm... Hmmm... hol is... ahhh...";
			link.l1 = "Mi az, mester? Eléggé aggódónak tûnsz. Valami baj van? Valamilyen probléma?";
			link.l1.go = "clock_3";
		break;
		
		case "clock_3":
			dialog.text = "Pontosan. Problémák. Mostanában. Átkozott kincsvadászok...";
			link.l1 = "Nyugodj meg, nyugodj meg. Nem jó a te korodban így aggódni. Isten ments, hogy csak egy ütés választ el. Ki építené akkor a fregattot a Testvériség vezetôjének? Nyugodj meg, és magyarázd el nekem, kik ezek a kincsvadászok?";
			link.l1.go = "clock_4";
		break;
		
		case "clock_4":
			dialog.text = "Ott az asztalom mellett van egy ajtó. Egyenesen egy régi páncélterembe vezet. Ebben a páncélteremben, az egyik kincsesládában tartom a fémdobozt a tárgyakkal, amelyek velem voltak, amikor húsz évvel ezelôtt áthúztak azon az átkozott tölcséren, és itt kötöttem ki...";
			link.l1 = "Milyen tölcsér? Mirôl beszélsz?";
			link.l1.go = "clock_5";
		break;
		
		case "clock_5":
			dialog.text = "Ah, bocsánat a fantáziámért. Öregnek lenni nem könnyû, fiatalember. Bocsásson meg. De ez lényegtelen. Ami lényeges, az az, hogy a ládában van egy doboz ajándékkal a számodra, ami a várbörtönben fekszik, amit jelenleg néhány söpredék foglal el. Ezek nem a mi embereink, és nem is Isla Tesoróról jöttek\nKincsvadászok, valaki biztos elmondta nekik, hogy ez a hely tele van kincsekkel. Nem mernének itt mutatkozni, én azonban túlságosan félek ahhoz, hogy meglátogassam ôket, látod? Az arcuk...";
			link.l1 = "Értem. Nyisd ki az ajtót. Kiverem a hívatlan vendégeket.";
			link.l1.go = "clock_6";
		break;
		
		case "clock_6":
			dialog.text = "Csak így? Kivered ôket? Egyedül? Nem félsz? Van egy egész településünk, ami harcolni fog érted, ha csak kérsz...";
			link.l1 = "Kevesebb beszéd, több tett, mester. Nyisd ki ezt az ajtót, a többit bízd rám. Melyik ládában tartod a dolgaidat?";
			link.l1.go = "clock_7";
		break;
		
		case "clock_7":
			dialog.text = "A folyosó végén van egy csomó üres fahordó. Mögöttük a földön egy félreesô helyen egy kis láda áll. Rávertem egy lakatot, így kétlem, hogy azoknak a betolakodóknak sikerülne beletenniük a piszkos kezüket, még ha meg is találnák. Tessék, fogd a kulcsot.";
			link.l1 = "Örülök, hogy elôre gondolkodsz. Várjatok itt, és ne menjetek sehova.";
			link.l1.go = "clock_8";
		break;
		
		case "clock_8":
			DialogExit();
			GiveItem2Character(pchar, "key3"); 
			bDisableFastReload = true;//закрыть переход
			LocatorReloadEnterDisable("Pirates_Shipyard", "reload1_back", true);
			LocatorReloadEnterDisable("Pirates_Shipyard", "reload2", false);
			LAi_LocationDisableOfficersGen("Bermudes_Dungeon", true);//офицеров не пускать
			pchar.quest.Alex_Chest.win_condition.l1 = "location";
			pchar.quest.Alex_Chest.win_condition.l1.location = "Bermudes_Dungeon";
			pchar.quest.Alex_Chest.function = "AlexClock_Chest";
			pchar.quest.AlexClock_Over.over = "yes"; //снять прерывание
			pchar.questTemp.AlexClock = "chest";
			AddQuestRecord("alex_clock", "3");
		break;
		
		case "clock_complete":
			dialog.text = "Csak hallgattak rád és elmentek?";
			link.l1 = "Igen, így van. Végül udvarias, kedves fickók lettek. Elmagyaráztam nekik, hogy a jelenlétükkel megijesztik az öreg híres hajóácsot, és az öregséged iránti tiszteletbôl elhagyták az épületet. Nyugodtan lemehetsz oda, nem kell aggódnod.";
			link.l1.go = "clock_complete_1";
		break;
		
		case "clock_complete_1":
			dialog.text = "Ah-ha, gúnyolódsz egy öregemberen! Jól van, jól van. Add ide a dobozomat, kinyitom, és odaadom neked a készüléket, amit tisztességesen kiérdemeltél.";
			link.l1 = "Kérem, vegye el...";
			link.l1.go = "clock_complete_2";
		break;
		
		case "clock_complete_2":
			RemoveItems(pchar, "alexs_chest", 1);
			dialog.text = "Hála! Nyissuk ki. Tessék, fogd ezt. Automata mechanikus idôzítô, itt senki nem gyárt ilyen készülékeket, és a következô háromszáz évben senki sem fog... huh, elnézést, kérem, bocsásson meg az öregnek. Csak azt mondom, hogy ez a dolog egyedülálló\nMinden munkát magától végez, nem lesz szükséged hülye homokórákra és hasonlókra. Nincs hiba! Csak óvd a közvetlen ütésektôl és a víztôl, különben elveszíted. Még egy majom is tudja használni ezt az idôzítôt.";
			link.l1 = "Szerezd be ezt! Soha életemben nem láttam még ilyen csodát! Köszönöm, mester.";
			link.l1.go = "clock_complete_3";
		break;
		
		case "clock_complete_3":
			GiveItem2Character(pchar, "clock3");
			Log_Info("Kaptál egy automata mechanikus idôzítôt.");
			SetAlchemyRecipeKnown("sextant2");
			PlaySound("interface\important_item.wav");
			dialog.text = "Szívesen. Most már mindig tudni fogod, hogy mennyi az idô. Ne kérdezd, honnan van. Nem mondom meg.";
			link.l1 = "Mindenkinek vannak titkai, nem igaz, mester? Rendben... tartsd meg a titkaidat, és én nem fogok beleszólni a dolgaidba. Köszönöm az ajándékot!";
			link.l1.go = "clock_complete_4";
		break;
		
		case "clock_complete_4":
			dialog.text = "És köszönöm a segítségét, kapitány. Látogass meg néha. Ne feledkezz meg egy öreg hajósról.";
			link.l1 = "Mintha el tudnám felejteni... Mindenesetre én mindenképpen megteszem, Alexus a Mester. Viszontlátásra!";
			link.l1.go = "clock_complete_5";
		break;
		
		case "clock_complete_5":
			DialogExit();
			bDisableFastReload = false;
			LocatorReloadEnterDisable("Pirates_Shipyard", "reload2", true);
			LocatorReloadEnterDisable("Pirates_Shipyard", "reload1_back", false);
			LocatorReloadEnterDisable("Bermudes_Dungeon", "reload2_back", false);
			LAi_LocationDisableOfficersGen("Bermudes_Dungeon", false);
			AddQuestRecord("alex_clock", "5");
			CloseQuestHeader("alex_clock");
			DeleteAttribute(pchar, "questTemp.AlexClock");
			// belamour legendary edition на пару с Акулой
			pchar.questTemp.SharkGoldFleet.KGBB = true;
			if(CheckAttribute(pchar,"questTemp.SharkFrigate")) SetTimerCondition("SharkGoldFleet", 0, 0, 30, false);
		break;
	// <-- хронометр Алекса
		
		// город майя
		case "tieyasal":
			dialog.text = "Aha, Miguel! Régi ismerôsöm. Emlékszem rá. Minden apró részletrôl kérdezgetett újra és újra. De hogyan magyarázhattam volna el neki, hogyan épül fel belülrôl egy rádió, amikor még egy egyszerû távírót sem látott?";
			link.l1 = "Micsoda? Mirôl beszélsz, mester?";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "Ó, bocsánat, fiatalember. Ne nagyon figyeljen oda a beszédemre... Kíváncsi Michelünk kielégítette kíváncsiságát és eltûnt. Csak három nappal ezelôtt beszélgettünk.";
			link.l1 = "Hol van most Miguel, ha megkérdezhetem?";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			dialog.text = "Ki tudja. Talán Sharptownban intézi az ügyeit, vagy talán már elutazott Isla Tesoróból.";
			link.l1 = "Értem. Köszönöm, mester!";
			link.l1.go = "tieyasal_3";
		break;
		
		case "tieyasal_3":
			DialogExit();
			npchar.quest.tieyasal = "true";
		break;
		
		// Калеуче
		case "FDM":
			if(CheckAttribute(npchar, "quest.FDM_secondtime"))
				dialog.text = "Ismét a 'szellemhajóddal'... Tudniillik - csak abban a reményben dolgozom vele, hogy valami tisztességes lesz belôle. Egyébként hozzá sem nyúlnék. Szerintem a tengeren mindenki hasonló véleményen van. Mit akarsz ezúttal csinálni vele?";
			else	
				dialog.text = "Á, a 'szellemhajó'! anyák a gályáddal ijesztgetik a rosszcsont gyerekeket. És te úgy döntöttél, hogy megtartod azt az átkozott hajót ahelyett, hogy elsüllyesztenéd! A tengerészek reszketnek, amikor meglátják a hajódat a horizonton... Szóval, mit akarsz vele csinálni?";
			/*if (!CheckAttribute(npchar, "quest.FDM_cabin"))
			{
				link.l1 = "Tetszik az ötlet, hogy a kis gyávák halálra rémülnek. De a belseje elszomorít. Láttad a kabinját? Olyan, mint egy koporsó. Az a sok penész és por. Meg akarom javítani. Meg tudod csinálni, mester?";
				link.l1.go = "FDM_cabin";
			}
			if (!CheckAttribute(npchar, "quest.FDM_sails"))
			{
				link.l2 = "Elegem van ezekbôl a szakadt fekete rongyokból. Elismerem, ugyanolyan jól fogják a szelet, mint a normális vitorlák, de a kilátás... Undorító. Hófehér vitorlákat akarok. Benne vagy, mester?";
				link.l2.go = "FDM_sails";
			}*/
			
			if (!CheckAttribute(npchar, "quest.FDM_hull"))
			{
				link.l3 = "Nos, azt hiszem, itt az ideje, hogy valami rendes vitorlát csináljunk belôle. A hajó jó, a legénység megszokta, de egy tiszteletreméltó kapitánynak egyszerûen nem méltó egy olyan hajón vitorlázni, ami a felnôtteket is halálra rémíti, nemhogy a gyerekeket. Teljesen át akarom építeni, hogy a többi kapitány irigyelje, amikor meglátja a hajómat, ahelyett, hogy keresztet vetne magára. És ki máshoz fordulhatnék ezzel, mint a szigetvilág legjobb hajóépítôjéhez?";
				link.l3.go = "FDM_hull";
			}
		break;
		
		case "FDM_cabin":
			dialog.text = "Miért is ne? A kezeim még mindig egyenesek.";
			link.l1 = "...";
			link.l1.go = "FDM_cabin_s";
			//link.l2 = "Nincs értelme a túlzott luxusnak. Tartsuk meg a standardot.";
			//link.l2.go = "FDM_cabin_s";
		break;
		
		case "FDM_cabin_m":
			dialog.text = "Hagyd a színvonalat. Tíz láda dublon, és öt nap alatt kész lesz.";
			link.l1 = "Áll az alku!";
			link.l1.go = "FDM_cabin_m1";
			link.l2 = "Tíz láda? Másfél ezer dublon? Hm, idôre van szükségem, hogy átgondoljam az ilyen kiadásokat...";
			link.l2.go = "exit";
		break;
		
		case "FDM_cabin_s":
			dialog.text = "Hét láda dublont, és öt nap alatt meglesz.";
			link.l1 = "Áll az alku!";
			link.l1.go = "FDM_cabin_s1";
			link.l2 = "Hét láda? Több mint ezer dublont? Hm, idôre van szükségem, hogy átgondoljam az ilyen kiadásokat...";
			link.l2.go = "exit";
		break;
		
		case "FDM_cabin_m1":
			iTemp = GetCharacterItem(pchar, "Chest");
			npchar.quest.FDM_cabin = 10;
			npchar.quest.FDM_cabin.type = "Cabin_Huge";
			dialog.text = "Jó, akkor várom a fizetséget.";
			if (iTemp > 0)
			{
				link.l1 = "Nálam vannak a ládák. Lássuk csak. Tessék, "+FindRussianQtyString(iTemp)+".";
				link.l1.go = "FDM_cabin_pay";
			}
			else
			{
				link.l1 = "Mennem kell, és érméket kell tennem a ládákba.";
				link.l1.go = "FDM_cabin_wait";
			}
		break;
		
		case "FDM_cabin_s1":
			iTemp = GetCharacterItem(pchar, "Chest");
			npchar.quest.FDM_cabin.chest = 7;
			npchar.quest.FDM_cabin.type = "Cabin";
			dialog.text = "Jó, akkor várom a fizetséget.";
			if (iTemp > 0)
			{
				link.l1 = "Nálam vannak a ládák. Lássuk csak. Tessék, "+FindRussianQtyString(iTemp)+".";
				link.l1.go = "FDM_cabin_pay";
			}
			else
			{
				link.l1 = "Mennem kell, és érméket kell tennem a ládákba.";
				link.l1.go = "FDM_cabin_wait";
			}
		break;
		
		case "FDM_cabin_wait":
			DialogExit();
			npchar.quest.FDM_full = "cabin";
		break;
		
		case "FDM_cabin_pay":
			iTemp = GetCharacterItem(pchar, "Chest");
			amount = sti(npchar.quest.FDM_cabin.chest)-iTemp;
			Log_Info("Ládákat adtál Alexus mesternek.");
			PlaySound("interface\important_item.wav");
			if (amount <= 0) // всё принес
			{
				RemoveItems(pchar, "chest", sti(npchar.quest.FDM_cabin.chest));
				dialog.text = "Szóval, el kellett hoznod nekem "+FindRussianQtyString(sti(npchar.quest.FDM_cabin.chest))+" ládákat, elhoztad "+FindRussianQtyString(iTemp)+". Megkaptam a fizetséget. Most én jövök. Menjetek és sétáljatok körbe. Ne aggódj, mindent megteszek.";
				link.l1 = "Jó...";
				link.l1.go = "FDM_cabin_do";
			}
			else
			{
				RemoveItems(pchar, "chest", iTemp);
				dialog.text = "Szóval, el kellett hoznod nekem "+FindRussianQtyString(sti(npchar.quest.FDM_cabin.chest))+" ládákat, elhoztad "+FindRussianQtyString(iTemp)+". "+FindRussianQtyString(amount)+" ládák maradtak.";
				link.l1 = "Rendben, mester.";
				link.l1.go = "FDM_cabin_wait";
				npchar.quest.FDM_cabin.chest = amount;
			}
		break;
		
		case "FDM_cabin_do":
			DialogExit();
			SetLaunchFrameFormParam("Öt nappal késôbb..."+ NewStr() +"Alexus mester elvégezte a munkáját...", "", 0, 5);
			WaitDate("", 0, 0, 5, 0, 10); //крутим время
			LaunchFrameForm();
			RefreshLandTime();
			RecalculateJumpTable();
			Whr_UpdateWeather();
			shTo = &RealShips[sti(Pchar.Ship.Type)];
			shTo.CabinType = npchar.quest.FDM_cabin.type;
			if (CheckAttribute(npchar, "quest.FDM_sails")) npchar.quest.FDM_full = "done";
			else DeleteAttribute(npchar, "quest.FDM_full");
			npchar.quest.FDM_cabin = "done";
		break;
		
		case "FDM_sails":
			dialog.text = "Persze, meg tudom csinálni! Nos, nos... Ez azt jelenti, hogy ki kell dobnunk minden koszos, régi rongyot, és új, tiszta pamutból készült vitorlákat kell feltennünk. Sok munka vár itt ránk. Százezer pezó a munkára és az anyagokra. Megegyeztünk?";
			if (sti(Pchar.money) >= 100000)
			{
				link.l1 = "Persze, nekem megfelel. Megegyeztünk!";
				link.l1.go = "FDM_sails_do";
			}
			link.l2 = "Hm. Azt hiszem, át kell gondolnom...";
			link.l2.go = "exit";
		break;
		
		case "FDM_sails_do":
			AddMoneyToCharacter(pchar, -100000);
			dialog.text = "Jól van. Megvannak az érmék, ideje, hogy elvégezzem a munkámat. Sétálgass, amíg nem végeztem, és ne aggódj.";
			link.l1 = "Jó...";
			link.l1.go = "FDM_sails_done";
		break;
		
		case "FDM_sails_done":
			DialogExit();
			SetLaunchFrameFormParam("Két nappal késôbb..."+ NewStr() +"Alexus mester elvégezte a munkáját...", "", 0, 5);
			WaitDate("", 0, 0, 2, 0, 10); //крутим время
			LaunchFrameForm();
			RefreshLandTime();
			RecalculateJumpTable();
			Whr_UpdateWeather();
			SetShipSailsFromFile(pchar, "ships/parus_silk.tga");
			SetSailsColor(pchar, 0);//белый хлопковый парус
			npchar.quest.FDM_sails = "true";
			if (CheckAttribute(npchar, "quest.FDM_cabin")) npchar.quest.FDM_full = "done";
		break;
		//--> Xenon
		case "FDM_hull":
			dialog.text = "Nos, örülök, hogy végre ezt hallom. És igaz is - látszik, hogy rendes fickó vagy, mégis az ég tudja, min hajózol. De hadd figyelmeztesselek elôre, ez a munka nem csak néhány órára szól, és a falnak egy szép kis pénzébe kerül. ";
			link.l1 = "Oké, tudnál egy kicsit pontosabban fogalmazni?";
			link.l1.go = "FDM_hull_01";
		break;

		case "FDM_hull_01":
			dialog.text = "Alright, let's do the math... For a full rebuild of the ship's hull I'll need 150 units each of bakaut, ropes, ship silk and resin — and 10,000 gold doubloons. Don't look at me like that; most of the money will go on materials. This job is equivalent to dismantling the ship and building it again from scratch.";
			link.l1 = "No, I don't think so. I'm not ready to bring that many resources and hand over a pile of gold for the rebuild. I'll stick with what I have.";
			link.l1.go = "FDM_hull_thinking";
			link.l2 = "Eh, mit nem teszünk a hajónkért... Rendben, megegyeztünk.";
			link.l2.go = "FDM_hull_02";
		break;

		case "FDM_hull_02":
			dialog.text = "Rendben, kevesebb beszélgetés, több cselekvés. Várom a pénzt tôled, hogy elkezdhessek megvenni mindent, amire szükségem van. Amint megvan a pénz, elkezdheted hozni nekem az anyagokat. Én pedig elkezdek dolgozni a hajóján.";
			if(PCharDublonsTotal() >= 10000)
			{
    			link.l1 = "Nos, a pénz nem probléma. Nálam van. Tessék, mester.";
    			link.l1.go = "FDM_hull_waitmaterials";
            }
            else
            {
    			link.l1 = "Jelenleg nincs ennyi pénzem. Várj egy kicsit, majd hozok neked.";
    			link.l1.go = "FDM_hull_waitmoney";
            }
		break;

		case "FDM_hull_waitmaterials":
			RemoveDublonsFromPCharTotal(10000);
			npchar.quest.FDMsandal = 0;
			npchar.quest.FDMoil = 0;
			npchar.quest.FDMshipsilk = 0;
			npchar.quest.FDMropes = 0;
			AddQuestRecord("renovate_fdm", "1");

			npchar.quest.FDM_hull = "hull_waitmaterials";
			dialog.text = "Nem félsz egy kalóztelepülésen sétálgatni egy ilyen szép összeggel, hehe? Jó, viccelek, ezek mind becsületes emberek, a maguk módján. Most pedig várom az anyagokat. Emlékeztetôül: összesen 150 vasfát, 150 tekercs kötelet, 150 tekercs hajóselymet és 150 hordó gyantát kell hoznod.";
			link.l1 = "Tartsatok ki, elhozom nektek az anyagokat.";
			link.l1.go = "exit";
		break;

		case "FDM_hull_checkmaterials":
			dialog.text = "Nagyon jó! Mit hoztál nekem ma?";
			if (GetSquadronGoods(pchar, GOOD_SANDAL) > 0 && sti(npchar.quest.FDMsandal) < 150)
			{
				iSan = GetSquadronGoods(pchar, GOOD_SANDAL);
				link.l1 = "Vasfa a "+FindRussianQtyString(iSan)+"összegben.";
				link.l1.go = "FDM_sandal";
			}
			if (GetSquadronGoods(pchar, GOOD_OIL) > 0 && sti(npchar.quest.FDMoil) < 150)
			{
				iOil = GetSquadronGoods(pchar, GOOD_OIL);
				link.l2 = "Gyanta a "+FindRussianQtyString(iOil)+"mennyiségben.";
				link.l2.go = "FDM_oil";
			}
			if (GetSquadronGoods(pchar, GOOD_SHIPSILK) > 0 && sti(npchar.quest.FDMshipsilk) < 150)
			{
				iSil = GetSquadronGoods(pchar, GOOD_SHIPSILK);
				link.l3 = "Hajóselyem a "+FindRussianQtyString(iSil)+"összegben.";
				link.l3.go = "FDM_shipsilk";
			}
			if (GetSquadronGoods(pchar, GOOD_ROPES) > 0 && sti(npchar.quest.FDMropes) < 150)
			{
				iRop = GetSquadronGoods(pchar, GOOD_ROPES);
				link.l4 = "Kötelek a "+FindRussianQtyString(iRop)+"összegben.";
				link.l4.go = "FDM_ropes";
			} 
			link.l5 = "Még semmi. Csak meg akartam gyôzôdni róla, hogy az üzlet még áll.";
			link.l5.go = "exit";
		break;

		case "FDM_hull_checkmaterials_1":
			if (sti(npchar.quest.FDMsandal) > 149 && sti(npchar.quest.FDMoil) > 149 && sti(npchar.quest.FDMshipsilk) > 149 && sti(npchar.quest.FDMropes) > 149)
			{
				dialog.text = "Csodálatos! Minden anyagot megkaptunk. Most pedig, hadd vegyem le a kezedrôl azt a szörnyeteget. Végre, végre megfelelô kinézetet kap.";
				link.l1 = "Oké, elég a morgásból, mester. Kíváncsian várom az eredményt.";
				link.l1.go = "FDM_hull_building";
			}
			else
			{
				dialog.text = "Van még valami, ami feldobja a napomat, kapitány?";
				link.l1 = "Sajnos, egyelôre ennyi.";
				link.l1.go = "exit";
				link.l2 = "Igen, van még valamim a számodra...";
				link.l2.go = "FDM_hull_checkmaterials";
			}
		break;

		case "FDM_sandal": // бакаут
			amount = 150 - sti(npchar.quest.FDMsandal);
			iSan = GetSquadronGoods(pchar, GOOD_SANDAL);
			iTemp = amount-iSan;
			if (iTemp > 0) 
			{
				dialog.text = "Lássuk csak... Szükségem van "+FindRussianQtyString(amount)+" vasfára. Te hoztál "+FindRussianQtyString(iSan)+". vasfát. Ezért még mindig el kell hoznod nekem "+FindRussianQtyString(iTemp)+".";
				link.l1 = "Köszönöm! Hamarosan hozom a többit.";
				link.l1.go = "FDM_hull_checkmaterials_1";
				RemoveCharacterGoods(pchar, GOOD_SANDAL, iSan);
				npchar.quest.FDMsandal = sti(npchar.quest.FDMsandal) + iSan;
				AddQuestRecord("renovate_fdm", "2");
				AddQuestUserData("renovate_fdm", "sGood", "ironwood");
				AddQuestUserData("renovate_fdm", "sQty", FindRussianQtyString(iTemp));
			}
			else
			{
				dialog.text = "Lássuk csak... Még mindig szükségem van "+FindRussianQtyString(amount)+" vasfára. Hoztál nekem  "+FindRussianQtyString(iSan)+". Ezért végeztünk a vasfával!";
				link.l1 = "Köszönjük!";
				link.l1.go = "FDM_hull_checkmaterials_1";
				RemoveCharacterGoods(pchar, GOOD_SANDAL, amount);
				npchar.quest.FDMsandal = sti(npchar.quest.FDMsandal) + amount;
				AddQuestRecord("renovate_fdm", "3");
				AddQuestUserData("renovate_fdm", "sGood", "ironwood"); 
			}
		break;

		case "FDM_oil": // смолы
			amount = 150 - sti(npchar.quest.FDMoil);
			iOil = GetSquadronGoods(pchar, GOOD_OIL);
			iTemp = amount-iOil;
			if (iTemp > 0) 
			{
				dialog.text = "Lássuk csak... Szükségem van "+FindRussianQtyString(amount)+" gyantára. Te hoztál "+FindRussianQtyString(iOil)+". Ezért még mindig kell hoznod nekem "+FindRussianQtyString(iTemp)+".";
				link.l1 = "Köszönöm! Hamarosan hozom a többit.";
				link.l1.go = "FDM_hull_checkmaterials_1";
				RemoveCharacterGoods(pchar, GOOD_OIL, iOil);
				npchar.quest.FDMoil = sti(npchar.quest.FDMoil) + iOil;
				AddQuestRecord("renovate_fdm", "2");
				AddQuestUserData("renovate_fdm", "sGood", "resin");
				AddQuestUserData("renovate_fdm", "sQty", FindRussianQtyString(iTemp));
			}
			else
			{
				dialog.text = "Lássuk csak... Még mindig szükségem van "+FindRussianQtyString(amount)+" gyantára. Hoztál nekem "+FindRussianQtyString(iOil)+". Ezért végeztünk a gyantával!";
				link.l1 = "Köszönjük!";
				link.l1.go = "FDM_hull_checkmaterials_1";
				RemoveCharacterGoods(pchar, GOOD_OIL, amount);
				npchar.quest.FDMoil = makeint(npchar.quest.FDMoil) + amount;
				AddQuestRecord("renovate_fdm", "3");
				AddQuestUserData("renovate_fdm", "sGood", "resin");
			}
		break;

		case "FDM_shipsilk": // шёлк
			amount = 150 - sti(npchar.quest.FDMshipsilk);
			iSil = GetSquadronGoods(pchar, GOOD_SHIPSILK);
			iTemp = amount-iSil;
			if (iTemp > 0) 
			{
				dialog.text = "Lássuk csak... Szükségem van "+FindRussianQtyString(amount)+" hajóselyemre. Hoztál "+FindRussianQtyString(iSil)+". Ezért még mindig el kell hoznod nekem "+FindRussianQtyString(iTemp)+".";
				link.l1 = "Köszönöm! A többit hamarosan megkapod.";
				link.l1.go = "FDM_hull_checkmaterials_1";
				RemoveCharacterGoods(pchar, GOOD_SHIPSILK, iSil);
				npchar.quest.FDMshipsilk = sti(npchar.quest.FDMshipsilk) + iSil;
				AddQuestRecord("renovate_fdm", "2");
				AddQuestUserData("renovate_fdm", "sGood", "ship silk");
				AddQuestUserData("renovate_fdm", "sQty", FindRussianQtyString(iTemp));
			}
			else
			{
				dialog.text = "Lássuk csak... Még mindig szükségem van "+FindRussianQtyString(amount)+" hajóselyemre. Ezért még mindig el kell hoznod nekem "+FindRussianQtyString(iSil)+". Ezért végeztünk a hajóselyemmel.";
				link.l1 = "Köszönjük!";
				link.l1.go = "FDM_hull_checkmaterials_1";
				RemoveCharacterGoods(pchar, GOOD_SHIPSILK, amount);
				npchar.quest.FDMshipsilk = sti(npchar.quest.FDMshipsilk) + amount;
				AddQuestRecord("renovate_fdm", "3");
				AddQuestUserData("renovate_fdm", "sGood", "ship silk"); 
			}
		break;

		case "FDM_ropes": // канаты
			amount = 150 - sti(npchar.quest.FDMropes);
			iRop = GetSquadronGoods(pchar, GOOD_ROPES);
			iTemp = amount-iRop;
			if (iTemp > 0) 
			{
				dialog.text = "Lássuk csak... Szükségem van "+FindRussianQtyString(amount)+" kötélre. Hoztál "+FindRussianQtyString(iRop)+". Ezért még mindig hoznod kell nekem "+FindRussianQtyString(iTemp)+".";
				link.l1 = "Köszönöm! A többit hamarosan megkapod.";
				link.l1.go = "FDM_hull_checkmaterials_1";
				RemoveCharacterGoods(pchar, GOOD_ROPES, iRop);
				npchar.quest.FDMropes = sti(npchar.quest.FDMropes) + iRop;
				AddQuestRecord("renovate_fdm", "2");
				AddQuestUserData("renovate_fdm", "sGood", "ropes");
				AddQuestUserData("renovate_fdm", "sQty", FindRussianQtyString(iTemp));
			}
			else
			{
				dialog.text = "Lássuk csak... Szükségem van  "+FindRussianQtyString(amount)+" kötélre. Hoztál "+FindRussianQtyString(iRop)+". Ezért végeztünk a kötelekkel!";
				link.l1 = "Köszönjük!";
				link.l1.go = "FDM_hull_checkmaterials_1";
				RemoveCharacterGoods(pchar, GOOD_ROPES, amount);
				npchar.quest.FDMropes = sti(npchar.quest.FDMropes) + amount;
				AddQuestRecord("renovate_fdm", "3");
				AddQuestUserData("renovate_fdm", "sGood", "ropes");
			}
		break;

		case "FDM_hull_thinking":
			DialogExit();
			npchar.quest.FDM_secondtime = true;
		break;

		case "FDM_hull_waitmoney":
			DialogExit();
			npchar.quest.FDM_hull = "hull_waitmoney";
		break;

		case "FDM_hull_givemoney":
			dialog.text = "Nos, hoztál pénzt.";
			if(PCharDublonsTotal() >= 10000)
			{
    			link.l2 = "Yes, I brought it. 10,000 full-weight doubloons, as agreed.";
    			link.l2.go = "FDM_hull_waitmaterials";
            }
            else
            {
    			link.l1 = "Még nem, várjon, mester.";
    			link.l1.go = "exit";
            }
		break;

		case "FDM_hull_building":
			DialogExit();
			SetLaunchFrameFormParam("Öt nap telt el..."+ NewStr() +"Alexus mester befejezte a munkát...", "", 0, 5);
			WaitDate("", 0, 0, 5, 0, 10); //Pass time
			LaunchFrameForm();
			RefreshLandTime();
			RecalculateJumpTable();
			Whr_UpdateWeather();
			
			shTo = &RealShips[sti(pchar.Ship.Type)];
			object newShip;
			aref arTuning;
			CopyAttributes(&newShip, shTo);
			
			pchar.Ship.Type = GenerateShipExt(SHIP_RENOVATED_FDM, 0, pchar);
			
			if(CheckAttribute(newShip, "Tuning"))
			{
				makearef(arTuning, newShip.tuning);
				for (int iQty = 0; iQty < GetAttributesNum(arTuning); iQty++)
				{
					aref realTuning = GetAttributeN(arTuning, iQty);
					string tuningName = GetAttributeName(realTuning);
					UpgradeShipParameter(pchar, tuningName);
				}
			}
			SetShipSailsFromFile(pchar, "ships/parus_silk.tga");
			SetSailsColor(pchar, 0);//White cotton sail
			pchar.ship.hp = GetCharacterShipMaxHP(pchar);
			DeleteAttribute(pchar, "ship.hulls");
			DeleteAttribute(pchar, "ship.blots");	
			CloseQuestHeader("renovate_fdm");
			Achievment_Set("ach_CL_178");
		break;
		//<-- Xenon
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

void checkMatherial_repair(ref Pchar, ref NPChar, int good, int goodType)
{
	int amount;
	string Matherial = "Matherial" + goodType;
	amount = GetSquadronGoods(Pchar, good) - sti(NPChar.Repair.(Matherial));
	
	if (amount < 0)
    {
		amount = amount + sti(NPChar.Repair.(Matherial));
    }
    else
    {
		amount = sti(NPChar.Repair.(Matherial));
    }
    RemoveCharacterGoods(Pchar, good, amount);
    NPChar.Repair.(Matherial) = sti(NPChar.Repair.(Matherial)) - amount;
}
