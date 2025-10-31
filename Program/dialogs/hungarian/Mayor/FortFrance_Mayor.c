// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Mit akarsz? Kérdezzen csak.", "Figyelek rád, mi a kérdés?"), "Már másodszor próbálod megkérdezni...", "Már harmadszorra próbálod újra megkérdezni...",
                          "Mikor lesz már vége?! Elfoglalt ember vagyok, a kolónia ügyein dolgozom, és te még mindig próbálsz kérdezni valamit!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Meggondoltam magam...", "Most nem. Rossz helyen és rossz idôben."), "Igaz... De késôbb, nem most...",
                      "Megkérdezem... De egy kicsit késôbb...", "Sajnálom, " + GetAddress_FormToNPC(NPChar) + "...", npchar, Dialog.CurrentNode);			  
			link.l1.go = "exit";
			/* //--> Бремя гасконца
			if (CheckAttribute(pchar, "questTemp.Sharlie.Junglejew"))
			{
				link.l1 = "Monsieur, találtam egy bandita holttestet a dzsungelben. Az indiánok ölték meg. Fülbevalók voltak a testén, úgy tûnik, Európából hozták ide. Talán az egyik nemesé volt a városában?";
                link.l1.go = "Sharlie_junglejew";
			}
			//<-- Бремя гасконца */
			//--> Sinistra, Травля крысы
			if (CheckAttribute(pchar, "questTemp.TK_Potopil"))
			{
				link.l1 = "Excellenciás uram, a tett megtörtént! Sajnálattal közlöm azonban, hogy a bûnözô nem élte túl az eljegyzést, ezért nem kerül kivégzésre.";
                link.l1.go = "TK_Potopil";
			}
			if (CheckAttribute(pchar, "questTemp.TK_Plen"))
			{
				link.l1 = "Excellenciás uram, a feladat teljesítve! A fogoly a fogdámban várja a sorsát.";
                link.l1.go = "TK_Plen";
			}
			//<-- Травля крысы
			// Jason НСО
			if (CheckAttribute(pchar, "questTemp.Patria") && pchar.questTemp.Patria == "epizode_9_continue" && !CheckAttribute(npchar, "quest.frigate"))
			{
				link.l1 = "Philippe de Poincy fôkormányzó parancsára érkeztem, hogy átvegyem az önök fegyveres fregattjának parancsnokságát.";
                link.l1.go = "patria";
			}
			if (CheckAttribute(npchar, "quest.frigate.wait") && GetCompanionQuantity(pchar) < COMPANION_MAX)
			{
				link.l1 = "Készen állok, hogy a fregattot felvegyem a századomba.";
                link.l1.go = "patria_2";
			}
			// Jason Дороже золота
			if (CheckAttribute(pchar, "questTemp.GoldenGirl") && pchar.questTemp.GoldenGirl == "message")
			{
				link.l1 = "A meghívására érkeztem, Monsieur...";
                link.l1.go = "goldengirl";
			}
			if (CheckAttribute(pchar, "questTemp.GoldenGirl") && pchar.questTemp.GoldenGirl == "girl_prisoner")
			{
				link.l1 = "Nem volt szerencsés, uram.";
                link.l1.go = "goldengirl_10";
			}
			// andre39966 ===> В плену великого улова.
			if (CheckAttribute(pchar, "questTemp.VPVL_Magor_Dialogue"))
			{
				link.l1 = "Excellenciás uram, információ birtokába jutottam egy illegális kereskedelemrôl, ami hamarosan ezeken a partokon fog zajlani. Megkockáztatom, hogy ez az ügy méltónak bizonyulhat a figyelmére.";
				link.l1.go = "VPVL_Magor_1";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.VPVL_GovernorDialogueAvailable"))
			{
				link.l1 = "Excellenciás uram, híreket keresek arról a csempészhajóról, amirôl beszéltünk.";
				link.l1.go = "VPVL_Magor_4";
			}
			//  <=== В плену великого улова.  
		break;
		
		case "Sharlie_junglejew":
			dialog.text = "Lássuk, mit tudsz... Hihetetlen! Ez egyszerûen hihetetlen, Charles! Ezek a feleségem fülbevalói. Még mielôtt elhagytam Európát és a gyarmatokra jöttem, neki ajándékoztam. Néhány hónapja rejtélyes körülmények között eltûntek. Tudtam, hogy ellopták!\nCharles, nagyon örülök, hogy egyenesen hozzám jöttél, és nem adtad el a kereskedôknek azt, ami nekem oly kedves. Meghálálom a szívességet. Ahogy hallottam, hajót fogsz venni? Mivel úgy döntöttél, hogy részt veszel a tengerészetben, kétségtelenül szükséged lesz szigetvilágunk térképére. Tessék, vedd el. Biztos vagyok benne, hogy jól fog jönni!";
			link.l1 = "Köszönöm, felség!";
			link.l1.go = "Sharlie_junglejew_1";
		break;
		
		case "Sharlie_junglejew_1":
			DialogExit();
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "jewelry25", 1);
			GiveItem2Character(pchar, "map_normal");
			AddQuestRecord("SharlieE", "2");
			CloseQuestHeader("SharlieE");
			DeleteAttribute(pchar, "questTemp.Sharlie.Junglejew");
			if(!CheckAttribute(pchar, "questTemp.Sharlie.Pardon"))
			{
				DelLandQuestMark(npchar);
			}
		break;
		
		//--> Sinistra, Травля крысы
		case "TK_Potopil":
			dialog.text = "Ez sajnálatos, Charles, de meg kell elégednünk a jelenlegi helyzettel. Itt a jutalmad: ötezer pezó, adók után.";
			link.l1 = "Örömmel szolgálom St. Pierre-t és magát személyesen. Bár a csata nehéz volt, mégis találtam benne némi örömöt.";
			link.l1.go = "TK_Potopil_3";
			link.l2 = "Kihívást jelentô csata volt, excellenciás uram. A hajóm jelentôs károkat szenvedett. Lehetséges lenne, hogy kárpótoljanak a veszteségeimért?";
			link.l2.go = "TK_Potopil_4";
			DeleteAttribute(pchar, "questTemp.TK_Potopil");
			AddCharacterExpToSkill(pchar, "Accuracy", 20);
			AddCharacterExpToSkill(pchar, "Cannons", 20);
			AddCharacterExpToSkill(pchar, "Grappling", 20);
			AddCharacterExpToSkill(pchar, "Defence", 20);
			
			CloseQuestHeader("TravlyaKrys");
		break;
		
		case "TK_Potopil_3":
			dialog.text = "Bravó, Charles! Nincs kétségem afelôl, hogy messzire fogsz emelkedni a ranglétránkon.";
			link.l1 = "A viszontlátásra, excellenciás uram.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 5000);
			ChangeCharacterNationReputation(pchar, FRANCE, 5);
		break;
		
		case "TK_Potopil_4":
			dialog.text = "Meg kell mondanom, egy kicsit meglepett a kérése, Charles... Rendben, tekintsen úgy, hogy jóakaratom jeléül kap tôlem személyesen még kétezer pesót. Viszontlátásra.";
			link.l1 = "Köszönöm, excellenciás uram.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 7000);
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			ChangeCharacterNationReputation(pchar, FRANCE, 2);
		break;
		
		case "TK_Plen":
			dialog.text = "Kiváló, Charles! Örömmel fogja hallani, hogy a sikere segíteni fogja máltai barátait egy kényes mûveletben... Itt a jutalma: nyolcezer pezó, adók után.";
			link.l1 = "Örömmel szolgálom St. Pierre-t, a rendet és téged személyesen. Bár a harc kihívást jelentett, némi elégedettséget találtam benne.";
			link.l1.go = "TK_Plen_3";
			link.l2 = "Kemény csata volt, excellenciás uram. A hajóm jelentôs károkat szenvedett. Kérhetek kártérítést a veszteségeimért?";
			link.l2.go = "TK_Plen_4";
			AddCharacterExpToSkill(pchar, "Accuracy", 20);
			AddCharacterExpToSkill(pchar, "Cannons", 20);
			AddCharacterExpToSkill(pchar, "Grappling", 20);
			AddCharacterExpToSkill(pchar, "Defence", 20);
			CloseQuestHeader("TravlyaKrys");
			DeleteAttribute(pchar, "questTemp.TK_Plen");
			sld = CharacterFromID("TK_Heiter2");
			RemovePassenger(pchar, sld);
			sld.lifeday = 0;
		break;
		
		case "TK_Plen_3":
			dialog.text = "Bravó, Charles! Biztos vagyok benne, hogy messzire jutsz.";
			link.l1 = "A viszontlátásra, excellenciás uram.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 8000);
			ChangeCharacterNationReputation(pchar, FRANCE, 5);
		break;
		
		case "TK_Plen_4":
			dialog.text = "Gondolom, megérdemelte. Tartson meg még kétezer dollárt tôlem személyesen, jóakaratom jeléül. Köszönöm, barátom.";
			link.l1 = "Köszönöm, excellenciás uram.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 10000);
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			ChangeCharacterNationReputation(pchar, FRANCE, 2);
		break;
		//<-- Травля крысы
		
		// Jason НСО
		case "patria":
			if (GetCompanionQuantity(pchar) > 4)
			{
				dialog.text = "A hajó készen áll, de nincs szabad hely a századában. Kapitány, csökkentse a századát és térjen vissza, akkor azonnal átadom a fregattot.";
				link.l1 = "Rendben.";
				link.l1.go = "patria_1";
			}
			else
			{
				dialog.text = "Igen, természetesen, a hajó készen áll a kihajózásra. A kapitánya tisztában van vele, és minden parancsát teljesíteni fogja.";
				link.l1 = "Akkor elindulunk. Viszontlátásra, felség.";
				link.l1.go = "patria_3";
			}
		break;
		
		case "patria_1":
			DialogExit();
			npchar.quest.frigate.wait = "true";
		break;
		
		case "patria_2":
			DeleteAttribute(npchar, "quest.frigate.wait");
			dialog.text = "Kitûnô. Készüljön fel az új hajója fogadására. A kapitánya tisztában van vele, és minden parancsát követni fogja.";
			link.l1 = "Akkor elindulunk. Viszontlátásra, felség.";
			link.l1.go = "patria_3";
		break;
		
		case "patria_3":
			DialogExit();
			npchar.quest.frigate = "true";
			Patria_BastionFrigateMrt(); // присоединяем фрегат
		break;
		
		// Jason Дороже золота
		case "goldengirl":
			dialog.text = "Charles de Maure kapitány, végre!Már nagyon vártalak! Kérem, jöjjön be, csatlakozzon hozzám.";
			link.l1 = "Önnek is jó napot, Excellenciád. Az ilyen udvariassága mögött mindig van valami ok. Ezúttal mi az? Kalózok, spanyolok, vörösbôrû kannibálok?";
			link.l1.go = "goldengirl_1";
		break;
		
		case "goldengirl_1":
			dialog.text = "Ne ironizáljon, kapitány. Nem az én hibám, hogy mindig bajba kerülünk, te és én. De kérlek, ne aggódj, ezúttal nem lesz lövöldözés... valószínûleg.";
			link.l1 = "Érdekel, folytasd csak. Miben lehetek a segítségére?";
			link.l1.go = "goldengirl_2";
		break;
		
		case "goldengirl_2":
			dialog.text = "Hallottál már Madame Botot remek intézményérôl? Az ostrom alatt a mi... bordélyházunk hamuvá égett. Egy nap egy bizonyos hölgy önként jelentkezett, hogy újjáépíti.";
			link.l1 = "Tûz egy bordélyházban és nélkülem? Egyébként engem is lelôttek a spanyolok aznap.";
			link.l1.go = "goldengirl_3";
		break;
		
		case "goldengirl_3":
			dialog.text = "A fenébe, Charles, mi bajod van ma? A szellemességed nem helyénvaló! Még ha ez nem is állami ügy, mégis fontos ügy, számomra, személy szerint! Szükségem van a segítségedre! Az Isten szerelmére, szedd össze magad és hallgass meg!";
			link.l1 = "Bocsásson meg, Excellenciás Uram. Hatalmas megkönnyebbülést érzek, ennyi az egész. Hogy ôszinte legyek, belefáradtam ebbe az állandó csatározásba és harcba. Arra számítottam, hogy elkezdesz belerángatni az erôszak újabb körébe. Kérlek, folytasd. Soha nem hallottam errôl a Madame Botot-ról.";
			link.l1.go = "goldengirl_4";
		break;
		
		case "goldengirl_4":
			dialog.text = "Rendben, szóval ez a tiszteletreméltó hölgy egy teljesen új szintre emelte az intézményt. Ez most már a magas és nemes társaság helye, nem pedig egy patkánylyuk, mint régen. Az elôkelôségek, a drága borok és a korlátlan szerencsejáték helye. Mindent a saját szemével fog látni!";
			link.l1 = "Excellenciád, nem vagyok prûd, és a leírásod nagyon színes volt, de miért mondod ezt nekem?";
			link.l1.go = "goldengirl_5";
		break;
		
		case "goldengirl_5":
			dialog.text = "Mert rajta vagy a listán, mi másért?! Látod, bûntudatom van a márkiné miatt, és megígértem, hogy holnap bemutatlak neki az egyik partiján. Juliana nem gyakran tesz ilyet, úgyhogy kérem, legyen olyan kedves és csatlakozzon hozzánk. Ezúttal nem lesz verekedés, lövöldözés és kergetôzés, ígérem. Minden udvarias és méltóságteljes lesz: bor, gyönyörû nôk, kártya és egyéb nemes élvezetek.";
			link.l1 = "Kártyák és kurvák. Régen volt már, egy másik életben. Bár még mindig nem követlek. Miért én?";
			link.l1.go = "goldengirl_6";
		break;
		
		case "goldengirl_6":
			dialog.text = "Süket vagy? Juliana Botot, ô... fényes és híres arcokat gyûjt. Ôk teszik a partijait különlegessé és frissé. Ön elég nagy hírnévre tett szert, a márkinô már régóta várt arra, hogy a vendége legyen. Az én botlásom adott neki egy lehetôséget, és nem fogok élni vele, ha nem hajlandó újra fogadni engem. Ez minden, amit kapok, ha nem szállítalak neki!";
			link.l1 = "Excellenciád, te egy jóképû özvegy és kormányzó vagy... Miért érdekel téged egyáltalán egy kurtizán véleménye? Nekik kellene keresniük az ön jóindulatát, nem pedig fordítva.";
			link.l1.go = "goldengirl_7";
		break;
		
		case "goldengirl_7":
			dialog.text = "Botot márkiné Henry de Levi-Vantadur gróf védelme alatt áll - aki ôfelsége kegyelmébôl Új-Franciaország észak-amerikai államainak feje. Hidd el, Charles, itt senki sem akar neki keresztbe tenni.";
			link.l1 = "Majdnem megfogtál - azt hittem, itt csak a kéjrôl és az amourról van szó. Most már látom, hogy ez végig politika volt. Triviális, de várható volt. Rendben, segítek neked. Édes lesz visszatérni a fiatalságom napjaihoz, csak egy éjszakára.";
			link.l1.go = "goldengirl_8";
		break;
		
		case "goldengirl_8":
			dialog.text = "Kapitány, ön kétségtelenül tapasztalt ember, de ne próbáljon úgy tenni, mintha öregember lenne. Ez nem csak a politikáról szól. Nagyra értékelem Juliana jelenlétét, és hálás vagyok a segítségéért. Ez fontos nekem személyesen, ôszintén. Jöjjön el Botot márkinéhoz holnap alkonyat után. Ígérem, hogy a politika nem fogja elrontani az éjszakát.";
			link.l1 = "Bor, kártya, nôk. Mint a régi szép idôkben. Viszontlátásra, Excellenciád!";
			link.l1.go = "goldengirl_9";
		break;
		
		case "goldengirl_9":
			DialogExit();
			bDisableFastReload = true;//закрыть переход
			pchar.quest.GoldenGirl_bronca.win_condition.l1 = "location";
			pchar.quest.GoldenGirl_bronca.win_condition.l1.location = "FortFrance_town";
			pchar.quest.GoldenGirl_bronca.function = "GoldenGirl_GirlAngry";
			if(bImCasual) NewGameTip("Felfedezô mód: az idôzítô nincs kikapcsolva. Tartsd be a határidôt!");
			SetFunctionTimerCondition("GoldenGirl_TimeOver", 0, 0, 2, false); // таймер до завтрашней полуночи
			SetFunctionTimerCondition("GoldenGirl_BrothelDoor", 0, 0, 1, false); // таймер на закрытие дверей борделя
			pchar.quest.GoldenGirl_eventstart.win_condition.l1 = "Timer";
			pchar.quest.GoldenGirl_eventstart.win_condition.l1.date.hour  = 21.00;
			pchar.quest.GoldenGirl_eventstart.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.GoldenGirl_eventstart.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.GoldenGirl_eventstart.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.GoldenGirl_eventstart.win_condition.l2 = "location";
			pchar.quest.GoldenGirl_eventstart.win_condition.l2.location = "FortFrance_SecBrRoom"; // возможно закрыть бордель и вход только через боковую комнату
			pchar.quest.GoldenGirl_eventstart.function = "GoldenGirl_Party"; // таймер на начало вечеринки
			pchar.questTemp.GoldenGirl = "brothel";
			AddQuestRecord("GoldenGirl", "2");
		break;
		
		case "goldengirl_10":
			dialog.text = "Charles, mi történt, pokolian nézel ki!";
			link.l1 = "Angerran, baszd meg, Chievous, excellenciás uram. Ellopta a fregattomat tegnap este. Megölte a legénységemet és elhajózott a ködben.";
			link.l1.go = "goldengirl_11";
		break;
		
		case "goldengirl_11":
			dialog.text = "Kellemetlen fordulat, megértem, de higgye el - az ilyen kimenetel eléggé kielégítô. Önnek nincs égetô szüksége hajókra és emberekre, miközben de Levi Vantadur jelentôs összeget fizet azért, hogy eltitkolja az igazságot egy bizonyos nemrégiben lezajlott párbaj mögött. Vagy ingyen emlékezni fog a szerepünkre az eltitkolásban, ami szintén elég sokat ér. De Chievous kétszer is tisztességtelen dolgokat tett, de most már messze van, míg nekünk még tisztességes lapjaink vannak ellene.";
			link.l1 = "Háromszor, excellenciás uram. Angerran beismerte a csalást a kártyapartiunk során. De pénzzel nem fog fizetni, ha erre gondolsz. Átlépte a határt. Ma reggel volt egy bizonyos személy azon a hajón... nagyon kedves nekem! Nem hagyom, hogy az a szemétláda bármi rosszat tegyen neki! Hallod ezt, Jacques, nem hagyom!";
			link.l1.go = "goldengirl_12";
		break;
		
		case "goldengirl_12":
			dialog.text = "Azt hiszem, tudom, kirôl beszélsz - emlékszem, hogy láttalak valami... lánnyal, aki férfinak volt öltözve és állig felfegyverkezve, mint egy kalóz. Charles, ne légy idióta! Szerencséd volt, elkerülted a hatalmas bajokat, és most mi van, megint megpróbálod magad belerángatni ôket? Hagyd abba. De Chievous menekül - hála Istennek! Ami pedig a 'barátnôdet illeti' - fogadd meg a barátod tanácsát - menj el Juliannához, és felejtsd el ezt az egészet.";
			link.l1 = "Szó sem lehet róla, excellenciás uram. Vannak dolgok, amiket nem tudsz megérteni, rendben? Most pedig mondj el mindent, amit tudsz errôl a fattyúról. Hová mehetett Saint Pierre-bôl? És ne próbáljon megint lebeszélni - én baszakodtam a Holland Társasággal, baszakodtam kalózbárókkal, fôkormányzókkal, még a Szent Inkvizícióval is! Engem nem könnyû elijeszteni. Vissza fogom szerezni, bármi áron!";
			link.l1.go = "goldengirl_13";
		break;
		
		case "goldengirl_13":
			dialog.text = "Charles, elgondolkodtál már azon, hogy ki nevezi ki a fôkormányzókat? Ez egy teljesen más világ! Alig értél hozzá, ez meghaladja a felfogóképességedet, olyan vagy, mint egy gyerek egy lôporraktárban. És arra kérsz, hogy adjak át neked egy égô gyertyát. Ami a fôkormányzókat illeti: de Poincy maga soha nem lépi át a grófot sem pénzügyekben, sem politikai kérdésekben. A vicekirály, a köznép körében oly népszerû kifejezés, Henri de Levi Vantadurnak nagyon is megfelelne.";
			link.l1 = "És itt vagyok én, aki meg akarom nyúzni az egyetlen férfi örökösét, tudom, mit kockáztatok. Most csak annyit mondj: tudsz valami hasznosat, ami segíthetne nekem?";
			link.l1.go = "goldengirl_14";
		break;
		
		case "goldengirl_14":
			dialog.text = "A másik nap ezt a pisztolyodra való átállást a barátságunk végének tekinteném, Charles. De megértem a jelenlegi lelkiállapotodat. Éppen ezért kész vagyok elfelejteni ezt az egészet. Nem tudok semmi hasznosat a számodra, a fregatt kora reggel nyugatra indult. Meg kellene látogatnod a márkinét... Várjon, ne így! Julianna sokat tud az ellenségedrôl, és egy ideig személyesen... ismerte az apját. Kérdezd meg tôle. Velem ellentétben ô nem fog megállítani téged.";
			link.l1 = "Ez a terv. Viszlát, excellenciás uram. Köszönöm, hogy idôt szakított rám.";
			link.l1.go = "goldengirl_15";
		break;
		
		case "goldengirl_15":
			DialogExit();
			LocatorReloadEnterDisable("FortFrance_town", "reload9_back", false); 
			LocatorReloadEnterDisable("FortFrance_town", "reload91", false);
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_58";
			LAi_SetOwnerType(sld);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			pchar.questTemp.GoldenGirl = "find_girl";
		break;
		
		// В плену великого улова, andre39966
		case "VPVL_Magor_1":
			dialog.text = "Csempészárut mondott? Hmm... nagyon érdekes. Kérem, világosítson fel a felfedezésének részleteirôl.";
			link.l1 = "Három nappal ezelôtt egy csempészáruval megrakott hajó horgonyt vetett a Le Marin-öbölben. A hajó nem érkezett meg a találkozóhelyére, de jó okom van azt hinni, hogy hamarosan kiköt. Talán az emberei megszervezhetnének egy megfelelô üdvözlést ezeknek a rablóknak, amikor megérkeznek, excellenciás uram.";
			link.l1.go = "VPVL_Magor_2";
			pchar.questTemp.VPVL_DontSpawnSmugglersShip = true; 
			DelLandQuestMark(npchar);
		break;

		case "VPVL_Magor_2":
			dialog.text = "Egy névtelen hajó, mely névtelen rakományt szállít... És azt hiszi, hogy ilyen ködös információk alapján küldjem ki Ôfelsége csapatait?";
			link.l1 = "Kegyelmes uram, elismerem, hogy a részletek kevéssé ismertek. De kérem, engedje meg, hogy elmondjam, hogyan jutott birtokomba ez az információ. (Cutscene)";
			link.l1.go = "VPVL_Magor_3";
		break;

		case "VPVL_Magor_3":
			dialog.text = "Rendben, akkor most próbára tesszük az intelligenciádat. Ha egy csempészárut szállító hajó valóban lehorgonyozna Le Marin partjainál, a koronának tett szolgálataiért bôséges jutalmat kapnak. Térjen vissza hozzám három napon belül' idôben. Addigra a bizonytalanság ködének fel kell oszlania.";
			link.l1 = "Kitûnô. Akkor három nap múlva találkozunk.";
			link.l1.go = "VPVL_Delete_Spawn_Ship";
			AddDialogExitQuest("VPVL_SetGovernorDialogueFlag");
			AddQuestRecord("VPVL", "6");
		break;

		case "VPVL_Magor_4":
			dialog.text = "Ah, kapitány! Örülök, hogy újra fogadhatom. Az intelligenciája valóban nagyon értékesnek bizonyult. Az embereim pontosan ott fogták el a hajót, ahol ön jelezte. Itt van százötven spanyol dublon, frissen verve, és nehéz az erszényben. Fogadja hálám jeléül.";
			link.l1 = "Alázatos köszönetem, excellenciád. 'Ez a szerencse, hogy az én kis információm a korona érdekeit szolgálta. Ha újra alkalom adódik, tudd, hogy kardkarom és éles szemem továbbra is rendelkezésedre áll.";
			link.l1.go = "VPVL_Delete_Flag";
			AddItems(PChar, "gold_dublon", 150);
			ChangeCharacterNationReputation(pchar, FRANCE, 5);
			DelLandQuestMark(npchar);
		break;

		case "VPVL_Delete_Flag":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.VPVL_GovernorDialogueAvailable");
			DeleteAttribute(pchar, "questTemp.VPVL_DontSpawnSmugglersShip");
		break;

		case "VPVL_Delete_Spawn_Ship":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.VPVL_Magor_Dialogue");
			AddDialogExitQuest("VPVL_KillCapitanOfSmuggler");
		break;
		// <=== В плену великого улова
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
