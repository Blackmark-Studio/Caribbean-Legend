// диалоги персонажей по пиратской линейке // Addon 2016-1 Jason пиратская линейка
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;
	string sTemp, attrL;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	attrL = Dialog.CurrentNode;
	
	if(HasSubStr(attrL, "ShipStockManBack_"))
 	{
        i = findsubstr(attrL, "_" , 0);
	 	NPChar.ShipToStoreIdx = strcut(attrL, i+1, strlen(attrL)-1); // индех в конце
 	    Dialog.CurrentNode = "ShipStockManBack";
 	}

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
        case "First time":
			dialog.text = "Mit szeretne?";
			link.l1 = "Mennem kell...";
			link.l1.go = "exit";
		break;
		
		// Лопе Монторо
		case "Mtr_officer":
			if (pchar.questTemp.Mtraxx != "fail" && pchar.questTemp.Mtraxx == "jewelry_5")
			{
				pchar.quest.Mtraxx_JewelryHavanaOver.over = "yes"; //снять таймер
				dialog.text = "Az isten szerelmére, ki a fene vagy te?";
				link.l1 = "Jó napot, don Lope. Bár még nem ismerkedtünk meg, de most már épp itt az ideje. Fôleg most, hogy olyan szívesen segítek neked kijutni ebbôl a nehéz helyzetbôl...";
				link.l1.go = "Mtr_officer_1";
			}
			else
			{
				dialog.text = "Mit szeretne?";
				link.l1 = "Mennem kell...";
				link.l1.go = "exit";
			}
		break;
		
		case "Mtr_officer_1":
            dialog.text = "Segíthetek? Nekem? Micsoda fordulat! Felvilágosítana, senor, honnan ered ez a nagylelkûség?";
			link.l1 = "Hát persze. Az ön egykori kapitányát, Esberdo Cabanast keresem, és nincs sok idôm... lehetôleg azon a helyen szeretnék találkozni vele, amit titokban tart. Még jobb lenne, ha elôbb érnék oda, mint ô.";
			link.l1.go = "Mtr_officer_2";
			DelLandQuestMark(npchar);
		break;
		
		case "Mtr_officer_2":
            dialog.text = "Ha-ha! Mondtam ennek a szánalmas idiótának, hogy tartsa a száját! A kék borostyán, igazam van?";
			link.l1 = "Jó irányban gondolkodik, jó uram.";
			link.l1.go = "Mtr_officer_3";
		break;
		
		case "Mtr_officer_3":
            dialog.text = "Akkor siessünk. Szívesen elmondanék minden részletet, ha megtalálják a módját, hogy kijuttassanak innen. Tudja, hogy kerültem ebbe a lyukba?";
			link.l1 = "Összességében igen, tudom.";
			link.l1.go = "Mtr_officer_4";
		break;
		
		case "Mtr_officer_4":
            dialog.text = "Halálrészeg voltam, amikor ez történt. Bassza meg az a rohadt csapos! Nem emlékszem semmire. Mindent csak akkor tudtam meg, amikor a 'Cantavro'. rakterében ébredtem fel... Mindez a hátunk mögött lenne, ha egyszerûen elhajóznánk, a parancsnok és az alcalde is hajlandó volt a másik irányba fordulni. De az az átkozott don Esberdo egyszerûen börtönbe juttatott. Gondolod, hogy azért tette ', hogy helyesen cselekedjen'? Ha csak, ez a gazember csak meg akarta tartani a részemet a borostyánból\nÉn voltam az, aki megemlítette, hogy több borostyán lehet a víz alatt, mint amit a parton találtunk. Én voltam az, aki megtalálta a módját, hogy megszerezze. Úgy volt, hogy bôséges részesedést kapok, de... ó, az a rohadék! Ugh, de elég ebbôl. Sem az alcalde, sem a parancsnok, sem a don de Toledo nem örül annak, hogy itt tartanak rohadni. Ha nem lenne az a paraszt és a tehén felesége, aki a galambdúcokat lobogtatja... akárhogy is, nem ellenzik, hogy segíts nekem\nbeszélj a kormányzóval, tégy úgy, mintha a régi barátom lennél Európából - ezt magam is megerôsítem. Egyébként mi a neved?";
			link.l1 = ""+GetFullName(pchar)+".";
			link.l1.go = "Mtr_officer_5";
		break;
		
		case "Mtr_officer_5":
            dialog.text = ""+GetFullName(pchar)+", csodálatos. Menjen el don Diego de Toledóhoz, és kérjen tôle tanácsot. Ne feledd, csak három napod van, a 'Cantavro' kergetése után már értelmetlen lenne. Engedjetek szabadon, és én megadok nektek mindent, amire szükségetek van ahhoz, hogy elbánjatok azzal a szemétládával, Cabanasszal.";
			link.l1 = "Azonnal megyek a kormányzóhoz, don Lope. Mindent megteszek, hogy megoldjam ezt a helyzetet mindkettônk érdekében.";
			link.l1.go = "Mtr_officer_6";
		break;
		
		case "Mtr_officer_6":
            DialogExit();
			pchar.questTemp.Mtraxx = "jewelry_6";
			LAi_CharacterDisableDialog(npchar);
			AddQuestRecord("Roger_1", "8");
			SetFunctionTimerCondition("Mtraxx_TimeclearPrison", 0, 0, 4, false); // таймер
			if(bImCasual) NewGameTip("Felfedezô mód: az idôzítô nincs kikapcsolva. Tartsd be a határidôt!");
			AddLandQuestMark(characterFromId("Havana_Mayor"), "questmarkmain");
		break;
		
		case "Mtr_officer_7":
			pchar.quest.Mtraxx_TimeclearPrison.over = "yes"; //снять таймер
            dialog.text = "Szóval, a szélhámos és az órabéres tyúkja bosszút állt, és én végre végeztem ezzel a lyukkal. Hálás vagyok, uram, megtette a magáét. Most engedje meg, hogy én is megtegyem a magamét.";
			link.l1 = "Csupa fül vagyok!";
			link.l1.go = "Mtr_officer_8";
			DelLandQuestMark(npchar);
		break;
		
		case "Mtr_officer_8":
            dialog.text = "Jól van. Az elôzô ôrjáratunk során viharba kerültünk, ami miatt fel kellett hagynunk az útvonalunkkal. A Nyugati-fô partján szálltunk partra, nem messze a Szúnyog-parttól, hogy friss vizet szerezzünk. Ott jó mennyiségû kék borostyánt találtunk. Kutatást végeztem, és találtam egy halom belôle a víz alatt. Jobb felszerelésre volt szükségünk a begyûjtéséhez, ezért úgy döntöttünk, hogy késôbb visszatérünk\nEsberdo öt hosszú csónakot vásárolt Havannában az indiánoknak, hogy merüljenek és gyûjtsék a borostyánt. A történet további részét ismered - a söpredék megszabadult tôlem, és elhajózott. Keressétek meg a Kékestôl északra fekvô Mosquitoes Coastnál, és siessetek - számításaim szerint csak hét napotok van, hogy odaérjetek. Remélem, a gyülekezés közepén elkapjátok a rohadékot, elviszitek az összes borostyánját, és számtalanszor leszúrjátok a hasát. Azért légy óvatos, a volt kapitányom képzett harcos és tengerész. Isten éltessen, senor.";
			link.l1 = "Neked is, Lope. Viszontlátásra!";
			link.l1.go = "Mtr_officer_9";
		break;
		
		case "Mtr_officer_9":
            DialogExit();
			pchar.questTemp.Mtraxx = "jewelry_10";
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			AddQuestRecord("Roger_1", "12");
			SetFunctionTimerCondition("Mtraxx_TimeclearGulf", 0, 0, 7, false); // таймер
			pchar.quest.mtr_jewelry_gulf.win_condition.l1 = "location";
			pchar.quest.mtr_jewelry_gulf.win_condition.l1.location = "Santacatalina";
			pchar.quest.mtr_jewelry_gulf.function = "Mtraxx_JewelryGulf";
			DeleteAttribute(pchar, "GenQuest.PrisonQuestLock");
			DelMapQuestMarkCity("Havana");
			AddMapQuestMarkShore("Shore53", true);
		break;
		
		// Росарио Гусман
		case "Mtr_rosario":
            dialog.text = "Szeretne kérdezni valamit, uram?";
			link.l1 = "Ami don Montorót illeti. Régi ismerôsök vagyunk, és nagyon feldúlt voltam, amikor értesültem a szerencsétlenségérôl. Don Diego de Toledo küldött hozzád, azt mondta, hogy te már megpróbáltad kiszabadítani közös barátunkat...";
			link.l1.go = "Mtr_rosario_1";
		break;
		
		case "Mtr_rosario_1":
            dialog.text = "Hm... senor, ez egy kicsit... váratlanul ért, de örülök, hogy találkozhatok Lope barátjával! Már egy ideje nem volt szerencséje, és most ez...";
			link.l1 = "Mit tehetünk érte? Egy nemes hidalgó nem rohadhat meg a társadalom söpredéke között!";
			link.l1.go = "Mtr_rosario_2";
		break;
		
		case "Mtr_rosario_2":
            dialog.text = "Egy üzletember! Egyszerre könnyû és nehéz segíteni szegény Lope-nak. Beszélgettem azzal a haszonlesôvel, akivel szegény Lope szerencsétlenül összeveszett. Beleegyezett, hogy ötszáz dublonnáért félúton találkozunk. Nem kis összeg az ô és a felesége 'szenvedéseiért'. Sajnos, a kért összegnek csak a felét sikerült összegyûjtenem - kétszázötven dublont.";
			link.l1 = "Tehát, ha szerzek még kétszázötven dublont, akkor don Lope szabad lesz?";
			link.l1.go = "Mtr_rosario_3";
		break;
		
		case "Mtr_rosario_3":
            dialog.text = "Igen. A kapzsi fattyú megígérte, hogy elterjesztem, hogy Lope megtérítette neki az összes kárt. És megkéri a kormányzót, hogy kegyelmezzen neki.";
			if (PCharDublonsTotal() >= 250) // belamour legendary edition
			{
				link.l1 = "A szükséges összeg most is nálam van. Tessék, hadd fulladjon meg ez a kapzsi burzsoá.";
				link.l1.go = "Mtr_rosario_4";
			}
			link.l2 = "Mindent megteszek, hogy minél hamarabb megkapja a pénzt.";
			link.l2.go = "Mtr_rosario_5";
		break;
		
		case "Mtr_rosario_4":
			RemoveDublonsFromPCharTotal(250); // belamour legendary edition
			PlaySound("interface\important_item.wav");
            dialog.text = "Nem hiszek a saját fülemnek! Senor, önt biztosan az Úr küldte!";
			link.l1 = "Mikor engedik szabadon az emberünket?";
			link.l1.go = "Mtr_rosario_8";
			DelLandQuestMark(npchar);
		break;
		
		case "Mtr_rosario_5":
            dialog.text = "Örömmel hallom, senor. Ön Lope igazi barátja és igazi nemesember.";
			link.l1 = "Viszontlátásra!";
			link.l1.go = "Mtr_rosario_6";
		break;
		
		case "Mtr_rosario_6":
            DialogExit();
			AddQuestRecord("Roger_1", "10");
			npchar.dialog.currentnode = "Mtr_rosario_7";
		break;
		
		case "Mtr_rosario_7":
            dialog.text = "Elhoztad a pénzt?";
			if (PCharDublonsTotal() >= 250) // belamour legendary edition
			{
				link.l1 = "A szükséges összeg most is nálam van. Tessék, hadd fulladjon meg ez a kapzsi burzsoá.";
				link.l1.go = "Mtr_rosario_4";
			}
			link.l2 = "Még mindig rajta vagyok.";
			link.l2.go = "Mtr_rosario_7_1";
		break;
		
		case "Mtr_rosario_7_1":
            DialogExit();
			npchar.dialog.currentnode = "Mtr_rosario_7";
		break;
		
		case "Mtr_rosario_8":
            dialog.text = "Ma este elviszem a pénzt a ravasz fattyúnak. Azt hiszem, délre meglesz a parancs a barátunk szabadon bocsátásáról. És remélem, hogy késôbb összegyûlünk, hogy együtt ünnepeljünk?";
			link.l1 = "Hogyne, don Rosario. Most már mennem kell. Viszlát!";
			link.l1.go = "Mtr_rosario_9";
		break;
		
		case "Mtr_rosario_9":
            DialogExit();
			AddQuestRecord("Roger_1", "11");
			npchar.lifeday = 1;
			SaveCurrentNpcQuestDateParam(NPChar, "LifeTimeCreate");
			npchar.dialog.currentnode = "Mtr_rosario_10";
			pchar.quest.mtr_prisoner.win_condition.l1 = "Timer";
			pchar.quest.mtr_prisoner.win_condition.l1.date.hour  = 12;
			pchar.quest.mtr_prisoner.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.mtr_prisoner.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.mtr_prisoner.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.mtr_prisoner.function = "Mtraxx_PrisonerFree";
		break;
		
		case "Mtr_rosario_10":
            dialog.text = "Hamarosan a barátunk szabad lesz!";
			link.l1 = "...";
			link.l1.go = "exit";
			npchar.dialog.currentnode = "Mtr_rosario_10";
		break;
		
		// Лысый Джеффри
		case "Jeffry":
			pchar.quest.Mtraxx_SilkCPVOver.over = "yes"; //снять прерывание
            dialog.text = "Hé, mi a fenét keresel a hajómon? Nem hiszem, hogy megkaptad a meghívásomat, mi?";
			link.l1 = "Nyugodj meg, Geffrey. Tyrexbôl jöttem a hajóselyem ügyében.";
			link.l1.go = "Jeffry_1";
		break;
		
		case "Jeffry_1":
            dialog.text = "Nos, akkor beszéljünk. Mit tervez? Már beszéltem a csempészekkel, ha engem kérdezel, jó árat kínálnak az áruért...";
			link.l1 = "És mennyit, ha megkérdezhetem?";
			link.l1.go = "Jeffry_2";
		break;
		
		case "Jeffry_2":
            dialog.text = "1300 pezó egy tekercs. Szerintem ez egy jó ár.";
			link.l1 = "Igen, és Tyrex 4 aranyat kér egy tekercsért. Egy érmével sem kevesebbet. És úgy értem, dublont. Azt a feladatot adta, hogy találjak egy megfelelô vevôt ezért az árért.";
			link.l1.go = "Jeffry_3";
		break;
		
		case "Jeffry_3":
            dialog.text = "Ha-ha-ha, fiú, micsoda szerencse! Marcusnak bizony van étvágya! Hát akkor menj, keress egy ilyen vevôt, pompás lenne nézni, ahogy próbálkozol.";
			link.l1 = "Igen, ez az egész kibaszottul vicces és fergeteges. Boldognak tûnök? Nem nézek ki boldognak. Szóval azt javaslom, hogy hagyd abba a röhögést és segíts nekem.";
			link.l1.go = "Jeffry_4";
		break;
		
		case "Jeffry_4":
            dialog.text = "Jól van, jól van, haver... Jézusom, nem nagyon szereted a vicceket, mi? De megértem, nem téged kell hibáztatni Tyrex fantáziálásaiért, mindannyian megkapjuk a magunkét, hidd el. És miben segíthetnék én neked? Boltban nem lehet eladni, a vámosok sem jöhetnek szóba, csak a csempészek maradtak. Kinek van még szüksége rá? Van valami ötleted?";
			link.l1 = "Hispaniola óta gondolkodom rajta... Mindegy. Csak két hónapom van, hogy találjak egy rendes vevôt. Valamit tenni kell ezzel kapcsolatban. A parancs az, hogy szálljon le a legközelebbi öbölben és végezze el a javításokat.";
			link.l1.go = "Jeffry_5";
		break;
		
		case "Jeffry_5":
            dialog.text = "Két hónap?! Mi a fene? Ah, csessze meg. A 'Kígyó' kell egy javítás és tisztítás, különben még egy bárkát sem lesz képes levadászni. Hé, francia kurvák! Kopasz Geffrey legénysége két hónapig Capsterville-ben marad! Ha-ha-ha!... Nos, sok szerencsét, haver, az értelmetlen keresésedhez. Ha találsz egy idiótát, aki hajlandó kifizetni Marcus árát ezért az átkozott selyemért - tudod, hol találsz meg.";
			link.l1 = "Várj! Adj egy tekercset ebbôl a selyembôl. Meg kell mutatnom az árut a potenciális vevôknek.";
			link.l1.go = "Jeffry_6";
		break;
		
		case "Jeffry_6":
            dialog.text = "Persze, nem probléma. Elviheted magaddal egy hosszúhajón... Hé, fiúk! Dobjatok egy bála selymet a kapitány hajójára!";
			link.l1 = "Jól van. Akkor majd találkozunk, ha megtaláltam a vevôt!";
			link.l1.go = "Jeffry_7";
		break;
		
		case "Jeffry_7":
            DialogExit();
			AddQuestRecord("Roger_2", "3");
			npchar.DeckDialogNode = "Jeffry_8";
			npchar.dialog.currentnode = "Jeffry_8";
			pchar.questTemp.Mtraxx = "silk_2";
			AddCharacterGoods(pchar, GOOD_SHIPSILK, 1);
			if(bImCasual) NewGameTip("Felfedezô mód: az idôzítô nincs kikapcsolva. Tartsd be a határidôt!");
			SetFunctionTimerCondition("Mtraxx_SilkTimeOver", 0, 0, 61, false); // таймер
		break;
		
		case "Jeffry_8":
            dialog.text = "Még valami, haver?";
			link.l1 = "Egyelôre semmi...";
			link.l1.go = "Jeffry_8_1";
		break;
		
		case "Jeffry_8_1":
            DialogExit();
			npchar.DeckDialogNode = "Jeffry_8";
			npchar.dialog.currentnode = "Jeffry_8";
		break;
		
		case "Jeffry_9":
			pchar.quest.Mtraxx_SilkTimeOver.over = "yes";
            dialog.text = "Hogy vagy, haver?";
			link.l1 = "Remekül. Találtam egy vevôt. 5 dublont egy tekercsért. Azt hiszem, Tyrexnek tetszeni fog.";
			link.l1.go = "Jeffry_10";
		break;
		
		case "Jeffry_10":
            dialog.text = "Kizárt dolog! Te vagy a leleményes ördög fia! Hogy csináltad ezt, mi?";
			link.l1 = "Ez egy hosszú történet, Geffrey. Most figyelj. A jamaicai Cape Negrilbe 10. és 15. között kell megérkezned. Ott várnak majd rád éjszakánként. A jelszó: 'A merchant of Lyons'. Megvan? Ismételje meg!";
			link.l1.go = "Jeffry_11";
		break;
		
		case "Jeffry_11":
            dialog.text = "Egy lyoni kereskedô. Megvan. Meg kell mondanom a pénztárosomnak, hogy írja le, ô az egyetlen ember itt, aki tud írni. Ha-ha!";
			link.l1 = "Van száz tekercs a raktérben?";
			link.l1.go = "Jeffry_12";
		break;
		
		case "Jeffry_12":
            dialog.text = "Nekem még több van.";
			link.l1 = "Pompás. Akkor itt az ideje, hogy vitorlát bontsanak. Ne hagyj cserben!";
			link.l1.go = "Jeffry_13";
		break;
		
		case "Jeffry_13":
            dialog.text = "Nyugi, haver, minden úgy lesz, ahogy kell.";
			link.l1 = "Isten éltessen, Geffrey. Talán még találkozunk.";
			link.l1.go = "Jeffry_14";
		break;
		
		case "Jeffry_14":
            DialogExit();
            AddQuestRecord("Roger_2", "22");
			pchar.questTemp.Mtraxx = "silk_14"; // к Тираксу
			sld = characterFromId("Terrax");
			sld.dialog.currentnode = "mtraxx_12";
			pchar.quest.mtraxx_hide_jeffry.win_condition.l1 = "MapEnter";
			pchar.quest.mtraxx_hide_jeffry.function = "Mtraxx_SilkHideJeffry";
		break;
		
		case "Jeffry_15":
            dialog.text = "Ho-ho-ho! Ravasz Charlie Prince, hús-vér ember! Jó volt újra látni téged, haver!";
			link.l1 = "Kopasz Geffrey! Charlie Prince-t mondtál? Ha!";
			link.l1.go = "Jeffry_15x";
		break;
		
		case "Jeffry_15x":
            dialog.text = "Még sosem hallottad a második neved? Most már így hívnak La Vegában.";
			link.l1 = "Értem, honnan jött Charlie, de miért Prince?";
			link.l1.go = "Jeffry_15y";
		break;
		
		case "Jeffry_15y":
            dialog.text = "Hát, te vagy az egyetlen nemes fia annak a kurvának La Vegában! Ha-ha-ha-ha! Hogy vagy? Voltál Pasquale boltjában? Vásároltál a vén szemétládától?";
			link.l1 = "Soha többé!";
			link.l1.go = "Jeffry_16";
		break;
		
		case "Jeffry_16":
            dialog.text = "K-ha! Miért, nem tetszett neked? Sózott marhahúst adott el neked a rum áráért?";
			link.l1 = "Rosszabb! Egy holland karavánról kaptam tôle egy ébenfával megrakott nyomot. Nem volt könnyû megtalálni, felszállni a kereskedôhöz, aztán meg megvédeni azt a kurva fát néhány tucat patkánytól! És képzeld, a rohadék 150 pesót fizetett nekem egy darabért. Egy darab kibaszott ébenfáért, Geffrey!";
			link.l1.go = "Jeffry_17";
		break;
		
		case "Jeffry_17":
            dialog.text = "Biztosíthatlak, hogy ez mindig megtörténik. Lavoisier már egy tucat hozzád hasonló jófiúval kefélt. Valójában fizetett neked valamit, ami ritka tôle. Mi nem fogadjuk el a 'vezetését' még akkor sem, ha éhezünk.";
			link.l1 = "Köszönöm barátom, legalább most már tudom, hogy nem én voltam az elsô és egyetlen idióta! De ezúttal a szemétláda elcseszte magát. Gondoskodom róla, hogy megbánja azt a napot, amikor meglátott engem.";
			link.l1.go = "Jeffry_18";
		break;
		
		case "Jeffry_18":
            dialog.text = "Hé, hé, hé! Várj herceg, nyugodj meg egy kicsit. Ez a szélhámos itt érinthetetlen. Ha ki mered fosztani, Marcus ott lesz a seggeden. Mondd csak, Tyrex küldött téged Lavoisier-hez?";
			link.l1 = "Hm. Igen... De miért?";
			link.l1.go = "Jeffry_19";
		break;
		
		case "Jeffry_19":
            dialog.text = "Figyelj... (lehalkítja a hangját) Azt mondják, hogy a négyszemû osztozik Marcusszal. Most már érted? Ezért nem merészeli egyetlen kalóz sem megtámadni Lavoisier hajóit, különben végük van.";
			link.l1 = "Megjegyeztem. Köszönöm a figyelmeztetést, Geffrey. Isten veled és Isten áldjon!";
			link.l1.go = "Jeffry_20";
		break;
		
		case "Jeffry_20":
            dialog.text = "Neked is, haver.";
			link.l1 = "...";
			link.l1.go = "Jeffry_21";
		break;
		
		case "Jeffry_21":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "OpenTheDoors", 15.0);
			AddQuestRecord("Roger_4", "10");
			CloseQuestHeader("Roger_4");
			QuestSetCurrentNode("Terrax", "mtraxx_34"); // релиз-правка
			bDisableFastReload = false;
			pchar.questTemp.Mtraxx.CharleePrince = "true"; // атрибут - ГГ известный пират
			pchar.questTemp.CharleePrince = true; // атрибут для найма команды 
		break;
		
		case "Jeffry_22":
            dialog.text = "Ho-ho-ho Herceg! Kíváncsi voltam, ki csinálta a tûzijátékot! Hoztam egy csapat muskétást, hátha a spanyolok voltak.";
			link.l1 = "Geffrey? Te is itt vagy? De hogyan? Te is megvetted a kincses térképet?";
			link.l1.go = "Jeffry_23";
			QuestPointerDelLoc("Judgement_dungeon_05", "reload", "reload1");
			QuestPointerDelLoc("Judgement_dungeon_04", "reload", "reload1");
		break;
		
		case "Jeffry_23":
            dialog.text = "Haver, én nem pazarolom a pénzem ilyen szarságokra. Egy utazó naplóját hozták nekem, aki arról írt, hogy biztonságos átjáró vezet ezekbe a tömlöcökbe.";
			link.l1 = "Ki hozta neked?";
			link.l1.go = "Jeffry_24";
		break;
		
		case "Jeffry_24":
            dialog.text = "Valami drogos. Csak száz pezó kellett neki egy italra.";
			link.l1 = "Tortugán történt?";
			link.l1.go = "Jeffry_25";
		break;
		
		case "Jeffry_25":
            dialog.text = "Nem. Barbadoson volt? Prince, miért aggódsz ennyire? Minél többen vagyunk, annál gyorsabb lesz a kincsek elszállítása!";
			link.l1 = "Nem tetszik ez nekem. Nem hiszek az ilyen véletlenekben. Lehet, hogy Camilla apja írta ezt a naplót?";
			link.l1.go = "Jeffry_26";
		break;
		
		case "Jeffry_26":
            dialog.text = "Ki az a Camilla?";
			link.l1 = "Az a lány, aki kétszáz pezóért eladott nekem egy térképet errôl a helyrôl!";
			link.l1.go = "Jeffry_27";
		break;
		
		case "Jeffry_27":
            dialog.text = "Heh... Herceg, túl sokat gondolkodsz. Menjünk kincset keresni. Gyerünk, gyerünk!";
			link.l1 = "Nem szükséges. Már megtaláltam ôket... Lent vannak a börtönben, vasrácsok mögött. Be kell törnünk ôket. Figyelj Geffrey, van még valami! Pelly, a késes is itt volt!";
			link.l1.go = "Jeffry_28";
		break;
		
		case "Jeffry_28":
            dialog.text = "Bicska? Hát akkor ez a mi szerencsenapunk! De hol van most?";
			link.l1 = "Lent... halott. A kincs közelében találkoztam vele. Dühös lett, ordítani kezdett a kapzsiságtól. Aztán ô és a társai megtámadtak engem.";
			link.l1.go = "Jeffry_29";
		break;
		
		case "Jeffry_29":
            dialog.text = "Hm... Pelly-nek mindig is balszerencséje volt a pénzzel. Biztos megôrült, amikor meglátta az aranyat.";
			link.l1 = "Lehet, hogy így van... de Geffrey, te nem érted! Mindhárman idejöttünk! És mindannyian ugyanazt az ólmot kaptuk! Szerinted véletlen volt? Valaki nyilvánvalóan azt akarja, hogy mindannyian egy helyen legyünk, és ez a hely olyan, mint egy sírbolt.";
			link.l1.go = "Jeffry_30";
		break;
		
		case "Jeffry_30":
            dialog.text = "Láttad az aranyat?";
			link.l1 = "A saját szememmel láttam. Több hatalmas láda tele érmékkel és rudakkal.";
			link.l1.go = "Jeffry_31";
		break;
		
		case "Jeffry_31":
            dialog.text = "Akkor miért aggódsz, herceg? Menjünk elôre, nézzük meg ezeket a rudakat. Aztán majd megosztjuk az aranyat.";
			link.l1 = "Ah, igazad lehet, mindegy... Gyerünk, menjünk.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_RetributionWithJeffry");
		break;
		
		case "Jeffry_32":
            //PlaySound("Voice\English\LE\Jeffry\Jeffry_gold.wav");
			dialog.text = "Micsoda látványosság! Ez egy nagy halom arany! Most már értem, hogy miért ôrült meg Cutlass. Nagyon szerencsések vagyunk, herceg! Mit gondolsz, mennyi aranyat fogunk itt találni?";
			link.l1 = "Rengeteget. Majd megtudjuk, ha elintézzük ezeket a rudakat.";
			link.l1.go = "Jeffry_33";
		break;
		
		case "Jeffry_33":
            dialog.text = "Igen, a rács nagyon erôs, nem fogjuk puszta kézzel vagy karddal eltörni. Igazad van, pajtás - szerszámokat vagy sok puskaport kell találnunk. Hé, nézzétek! Mi ez?";
			link.l1 = "...";
			link.l1.go = "Jeffry_34";
		break;
		
		case "Jeffry_34":
            DialogExit();
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("Mtraxx_RetributionJeffryMushketer", 0.1);
		break;
		
		case "Jeffry_35":
            PlaySound("Voice\English\LE\Jeffry\Jeffry_mozila.wav");
			dialog.text = RandSwear()+"Micsoda kibaszott muff!";
			link.l1 = "Te kibaszott kígyó!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_RetributionJeffryFight");
		break;
		
		// Билли Сипатый
		case "Billy":
			pchar.quest.Mtraxx_BillySeaTimeOver.over = "yes"; //снять таймер
			PlaySound("VOICE\English\LE\Billy\Billy_01.wav");
            dialog.text = "Cápa nyeld le, ha már megtörtént a 'Légyhal' az idén... fiúk, vendégünk van itt! Mi a baj az életedben pajtás, hogy úgy döntöttél, meglátogatod a régi kádamat?";
			link.l1 = "Üdvözletem! Te vagy az a Husky Billy, ugye?";
			link.l1.go = "Billy_1";
		break;
		
		case "Billy_1":
            dialog.text = "Nem találja ki a hangomból, kapitány? Régen a brit és spanyol kereskedôk összeszarták magukat. Dicsô idôk voltak azok!... Most az öreg Billy arra vár, hogy élete véget érjen kedvenc szigete partjainál, drága hosszú hajóján...";
			link.l1 = "Van egy üzletem a számodra, Billy. Azt mondták, mindent tudsz arról, hogy mi folyik itt Jamaica körül. Tényleg így van?";
			link.l1.go = "Billy_2";
		break;
		
		case "Billy_2":
            dialog.text = "Ha ezt mondták, akkor biztos így van, nem gondolja? Ne rángasd a rákot a golyóinál fogva, beszélj. Mi dolga van velem?";
			link.l1 = "Igen, így van. Van egy hajóépítô Port Royalban. Különleges szolgáltatásokat nyújt az ügyfeleinek, és szüksége van hajóselyemre a termeléséhez és az említett szolgáltatásokhoz. Mivel itt illegális ezzel az áruval kereskedni, illegális árusítót talált magának. Tudni akarom, hogy ki és hogyan látja el ôt hajóselyemmel.";
			link.l1.go = "Billy_3";
		break;
		
		case "Billy_3":
            dialog.text = "Ho-ho-ho, ezt nézzétek! D'Oyley ezredesnek dolgozol, fiam?";
			link.l1 = "Már megint itt vagyunk! Nem, én Marcus Tyrexszel dolgozom. Ô szeretne egy kis részesedést a hajóselyem piacból, és ez a hajóépítô szent szar, hogy foglalkozzon 'unfamiliar' emberekkel...";
			link.l1.go = "Billy_4";
		break;
		
		case "Billy_4":
            dialog.text = "Ó, a Kódôrnek dolgozol! Ezek nagyszerû hírek... ha persze nem hazudik. Nem érdekelnek a hajóépítôk, tartóztass le egyet - jön a másik. Az öreg lányomra viszont igen. A 'repülôhal' rossz állapotban van. Megértettél?\nHozd nekem egy másik hosszú csónakot, egy újat, és egy tekercs hajóselymet, olyat, amilyenrôl te beszélsz - Billy majd csinál belôle egy rendes vitorlát, hogy aztán cseszegethesse az ôrjáratokat, ha-ha-ha! Cserébe Billy mindent el fog mondani a hajóépítôrôl és a selyem forrásáról. Bízz bennem fiam, mindent tudok, amit tudni akarsz, csak meg kell gyôzôdnöm róla, hogy becsületes kalóz vagy, és nem valami seggnyaló vörös kabátos!";
			link.l1 = "Egy új hosszú hajó? Mi lenne, ha adnék neked annyi pénzt, hogy megvehesd magadnak? Még extrát is adok hozzá.";
			link.l1.go = "Billy_5";
		break;
		
		case "Billy_5":
            dialog.text = "He-eh, kapitány, az öreg Billy nem szívesen látott vendég a városban. Port Royalban túl jól emlékeznek rám, és nem szívesen akasztanának fel a régi barátaim között azon a sziklán. Szóval, fiam, várom, hogy szállítson nekem egy új, friss, hosszú hajót. Három napig fogok várni a Negril-foknál. És ne feledkezz meg a selyemrôl sem!";
			link.l1 = "Jól van, Billy. Megkapod a hosszú csónakodat és egy tekercs hajóselymet. Hamarosan visszajövök.";
			link.l1.go = "Billy_6";
		break;
		
		case "Billy_6":
            dialog.text = " Rendben, Billy várni fog rád a parton, kapitány. Hamarosan találkozunk!";
			link.l1 = "...";
			link.l1.go = "Billy_7";
		break;
		
		case "Billy_7":
            DialogExit();
			AddQuestRecord("Roger_2", "8");
			npchar.dialog.currentnode = "Billy_8";
			pchar.questTemp.Mtraxx = "silk_7";
			SetFunctionTimerCondition("Mtraxx_BillyTimeOver", 0, 0, 3, false); // таймер
			pchar.quest.mtr_billy_coast.win_condition.l1 = "ExitFromLocation";
			pchar.quest.mtr_billy_coast.win_condition.l1.location = pchar.location;
			pchar.quest.mtr_billy_coast.function = "Mtraxx_BillyOnCoast";
			locations[FindLocation("shore35")].DisableEncounters = true; //энкаутеры закрыть
			npchar.DontDeskTalk = true;
			if(bImCasual) NewGameTip("Felfedezô mód: az idôzítô nincs kikapcsolva. Tartsd be a határidôt!");
		break;
		
		case "Billy_8":
			PlaySound("VOICE\English\LE\Billy\Billy_02.wav");
            dialog.text = "Mi az? Hoztál már nekem egy hosszú csónakot?";
			link.l1 = "Te egy tréfamester vagy, mi, Billy?";
			link.l1.go = "exit";
		break;
		
		case "Billy_9":
            dialog.text = "Szóval, kapitány, mi lesz a friss, új hosszú csónakommal?";
			if(Companion_CheckShipType(SHIP_TARTANE) && GetSquadronGoods(pchar, GOOD_SHIPSILK) > 0)
			{
				link.l1 = "Kész, Husky. Egy tekercs hajóselyemmel együtt szállítják le a raktérben. Szabadon elsüllyesztheted a régi kádadat.";
				link.l1.go = "Billy_11";
			}
			else
			{
				PlaySound("VOICE\English\LE\Billy\Billy_02.wav");
				link.l1 = "Én még mindig rajta vagyok. Várjatok!";
				link.l1.go = "Billy_10";
			}
		break;
		
		case "Billy_10":
			DialogExit();
			npchar.dialog.currentnode = "Billy_9";
		break;
		
		case "Billy_11":
			PlaySound("VOICE\English\LE\Billy\Billy_03.wav");
			pchar.quest.Mtraxx_BillyTimeOver.over = "yes"; //снять прерывание
            dialog.text = "Baszd meg oldalról! Ez a legjobb hír az öreg Billy életének utolsó öt évében! Heh, egy jó ok, hogy feltörjük ezt az üveget...";
			link.l1 = "Kihagyom. Szóval a selyemszállítóval kapcsolatban?";
			link.l1.go = "Billy_12";
		break;
		
		case "Billy_12":
            dialog.text = "Kár, ihatnánk a friss új 'Flying Fish'! Mindegy... Ide figyelj, fiam\nAz angol zászló alatt közlekedô brigantin minden hónap közepén, valahol 10. és 15. között érkezik Portland Cove-ba. Halálomig nem kapok rumot, ha tényleg angol! A neve a 'Utrecht' és délnyugatról érkezik, ahol Curacao fekszik. Egyértelmûen egy holland hajóskapitányról van szó, látszik, hogy\nmindig ugyanaz a csapat találkozik velük a parton, élén a fômesterrel, azzal a ravasz hajóépítôvel. Ô a hollandok által ott kirakott hajóselyem átvevôje. Biztos vagyok benne, hogy ez a hajóselyem, hiszen csak a hollandok csomagolják így.";
			link.l1 = "Azt mondtad, minden hónapban?";
			link.l1.go = "Billy_13";
		break;
		
		case "Billy_13":
            dialog.text = "Valóban fiam, az elmúlt évben egyetlen hónapot sem hagytam ki. Ha beszélgetni akarsz ezzel a komor szakállas társasággal, akkor azt javaslom, hogy minden hónap 10-tôl 15-ig várd ôket Portland Cove-ban, minden hónap 10-én és 15-én este. Erre esküszöm a hosszúhajóm friss, új selyemvitorlájára!";
			link.l1 = "Heh! Úgy látszik, a pénzemet okkal költöttem el. Isten éltessen, Billy, és vigyázz, hogy az öreg seggedet ne engedd el az ôrjáratokat, különben nagyon felbosszantasz.";
			link.l1.go = "Billy_14";
		break;
		
		case "Billy_14":
            dialog.text = "Ha, az öreg Billy hamarosan igazi mókára készül Jamaica partjainál! Isten éltessen, kapitány! Jó vadászatot!";
			link.l1 = "Neked is, Billy!";
			link.l1.go = "Billy_15";
		break;
		
		case "Billy_15":
            DialogExit();
			npchar.lifeday = 0;
			pchar.questTemp.Mtraxx = "silk_8";
			chrDisableReloadToLocation = true;//закрыть локацию
			locations[FindLocation("shore35")].DisableEncounters = false; //энкаутеры открыть
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "sea", "none", "", "", "OpenTheDoors", 20.0);
			AddDialogExitQuestFunction("Mtraxx_BillyTakeShip");
			AddQuestRecord("Roger_2", "9");
			//
			if (GetDataDay() >= 1 && GetDataDay() <= 9)
			{
				DoQuestFunctionDelay("Mtraxx_SilkCreateSmuggler", 1.0);
			}
			
			if (GetDataDay() >= 10 && GetDataDay() <= 15)
			{
				int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+2;
				if (iRank > 45) iRank = 45;
				Group_FindOrCreateGroup("Mtr_Utreht");
				sld = GetCharacter(NPC_GenerateCharacter("Cap_Utreht", "mercen_19", "man", "man", iRank, ENGLAND, -1, true, "quest"));
				FantomMakeCoolSailor(sld, SHIP_BRIGANTINE, "Utrecht", CANNON_TYPE_CULVERINE_LBS18, 50, 50, 50);
				FantomMakeCoolFighter(sld, iRank, 50, 50, "blade_13", "pistol5", "bullet", 100);
				sld.name = "Joachim";
				sld.lastname = "Gusen";
				sld.DontRansackCaptain = true;
				sld.AnalizeShips = true;
				sld.Coastal_Captain = true; // правки прогона 3
				DeleteAttribute(sld, "SaveItemsForDead");
				sld.Ship.Mode = "pirate";
				SetSailsColor(sld, 2);
				sld.ship.Crew.Morale = 40+MOD_SKILL_ENEMY_RATE*4;
				sld.Ship.Crew.Exp.Sailors = 60+MOD_SKILL_ENEMY_RATE*4;
				sld.Ship.Crew.Exp.Cannoners = 40+MOD_SKILL_ENEMY_RATE*4;
				sld.Ship.Crew.Exp.Soldiers = 40+MOD_SKILL_ENEMY_RATE*4;
				if (MOD_SKILL_ENEMY_RATE > 4) SetCharacterPerk(sld, "MusketsShoot");
				SetCharacterGoods(sld, GOOD_SHIPSILK, 80);

				Group_AddCharacter("Mtr_Utreht", "Cap_Utreht");
				Group_SetGroupCommander("Mtr_Utreht", "Cap_Utreht");
				Group_SetTaskAttackInMap("Mtr_Utreht", PLAYER_GROUP);
				Group_SetAddress("Mtr_Utreht", "Jamaica", "Quest_Ships", "Quest_Ship_4");
				Group_SetTaskRunaway("Mtr_Utreht", PLAYER_GROUP);
				Group_LockTask("Mtr_Utreht");
				
				pchar.quest.mtr_silksmuggler_AfterBattle.win_condition.l1 = "Group_Death";
				pchar.quest.mtr_silksmuggler_AfterBattle.win_condition.l1.group = "Mtr_Utreht";
				pchar.quest.mtr_silksmuggler_AfterBattle.function = "Mtraxx_SilkSmugglerAfterBattle";
				
				SetTimerFunction("Mtraxx_SilkSmugglerFail", 0, 0, 2);
			}
			
			if (GetDataDay() >= 16 && GetDataDay() <= 20)
			{
				SetTimerFunction("Mtraxx_SilkCreateSmuggler", 0, 0, 15);
			}
			if (GetDataDay() >= 21 && GetDataDay() <= 26)
			{
				SetTimerFunction("Mtraxx_SilkCreateSmuggler", 0, 0, 10);
			}
			if (GetDataDay() >= 27 && GetDataDay() <= 31)
			{
				SetTimerFunction("Mtraxx_SilkCreateSmuggler", 0, 0, 5);
			}
		break;
		
		// мастеровой с верфи Порт-Ройаля
		case "Mtr_acceptor_fight":
            LAi_group_Delete("EnemyFight");
			DialogExit();
			chrDisableReloadToLocation = true;
			LAi_LocationFightDisable(&Locations[FindLocation("shore36")], false);
			for (i=1; i<=4; i++)
			{
				sld = characterFromId("Mtr_acceptor_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Mtraxx_SilkWrongTalk");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Mtr_acceptor":
            dialog.text = "Hé, matróz, most érkeztél Jamaikára, mi?";
			link.l1 = "Hm. Igen, így van. Mi a baj?";
			link.l1.go = "Mtr_acceptor_1";
		break;
		
		case "Mtr_acceptor_1":
            dialog.text = "Láttál valamit a közeli tengeren?";
			link.l1 = "Igen, láttam. Valami brigantin harcba keveredett egy angol járôrkorvettel. A britek keményen megütötték ôket, a hollandok menekülés közben megszabadultak a rakományuktól.";
			link.l1.go = "Mtr_acceptor_2";
		break;
		
		case "Mtr_acceptor_2":
            dialog.text = "Miért vagy olyan biztos benne, hogy holland volt? Egyetlen épeszû hollandnak sem jutna eszébe, hogy Port Royal közelébe menjen...";
			link.l1 = "Angol színeket viselt, mégis a neve... A 'Utrecht'. Nem túl brit, mi? Hollandok voltak, mondom én, talán még csempészek is. Az ôrjárat biztosan számított rájuk.";
			link.l1.go = "Mtr_acceptor_3";
		break;
		
		case "Mtr_acceptor_3":
            dialog.text = "Bassza meg!";
			link.l1 = "Úgy tûnik, nem igazán örül ennek...";
			link.l1.go = "Mtr_acceptor_4_1";
			link.l2 = "Itt várták ezt a brigantint?";
			link.l2.go = "Mtr_acceptor_7";
		break;
		
		case "Mtr_acceptor_4_1":
            dialog.text = "Miért vártam volna?";
			link.l1 = "Jöjjön, jöjjön. Tudom, kik maguk. Ön a Port Royal-i hajógyár mûvezetôje, és arra vár, hogy a brigantin leszállítsa a különleges rakományt.";
			link.l1.go = "Mtr_acceptor_wrong";
			link.l2 = "Az arcodra van írva, ott van az arcodon!";
			link.l2.go = "Mtr_acceptor_4_2";
		break;
		
		case "Mtr_acceptor_wrong":
            dialog.text = "Argh! Fiúk, ez egy álruhás ôrjárat! Végezzétek ki ôket, és tûnjetek innen a pokolba!";
			link.l1 = "A francba! Várj, te vagy a...";
			link.l1.go = "Mtr_acceptor_fight";
		break;
		
		case "Mtr_acceptor_4_2":
            dialog.text = "Bunkó vagy, 'tengeri farkas'? Vigyázz a szádra, vagy...";
			link.l1 = "Gyerünk már. Nyilvánvalóan idegesnek tûnsz. Tényleg arra vártál, hogy ezek a hollandok megérkezzenek?";
			link.l1.go = "Mtr_acceptor_4_3";
			link.l2 = "Vagy mi? Megtanítasz nekem egy életre szóló leckét?";
			link.l2.go = "Mtr_acceptor_6";
		break;
		
		case "Mtr_acceptor_4_3":
            dialog.text = "És mi van, ha igen? Miért érdekel ez téged?";
			if (GetSquadronGoods(pchar, GOOD_SHIPSILK) >= 20)
			{
				link.l1 = "Nem érdekel. Te vagy itt a várakozó fél, nem én. Egy örökkévalóság áll elôtted.";
				link.l1.go = "Mtr_acceptor_4_4";
			}
			link.l2 = "Ó, minden okom megvan rá, hogy érdekeljen. Tudom, hogy mi volt a brigantin rakterében. Hajóselyem. Emiatt vagy itt, igaz?";
			link.l2.go = "Mtr_acceptor_wrong";
		break;
		
		case "Mtr_acceptor_4_4":
            dialog.text = "Hm... Örökkévalóság?";
			link.l1 = "Az örökkévalóságba telik, hogy visszajöjjön a tenger fenekérôl. A brigantinedet elsüllyesztette egy járôrkorvett, haver. Csak úgy. Habár a háborúban vannak nyeremények és veszteségek is. Jó pénzt fogok keresni azon az elsüllyedt hollandon.";
			link.l1.go = "Mtr_acceptor_4_5";
		break;
		
		case "Mtr_acceptor_4_5":
            dialog.text = "És pontosan hogyan, vajon hogyan?";
			link.l1 = "Eladom, amit a fedélzetre dobtak, miközben menekülni próbáltak. Szinte minden elveszett, de az értékes hajóselyem úgy úszott, mint a... parafa. A nagy részét sikerült megmentenem, úgyhogy holnap a városba megyek, hogy vevôt találjak rá. Az ember sosem tudja, hol nyer, hol veszít.";
			link.l1.go = "Mtr_acceptor_4_6";
		break;
		
		case "Mtr_acceptor_4_6":
            dialog.text = "Várjon!";
			link.l1 = "Caramba! Most mi lesz?";
			link.l1.go = "Mtr_acceptor_4_7";
		break;
		
		case "Mtr_acceptor_4_7":
            dialog.text = "Mennyi selymet sikerült összegyûjtened?";
			link.l1 = "És miért érdekel ez téged? Ez az én selyem! Vagy te vagy a kormányzó kutyája? Te vagy a...";
			link.l1.go = "Mtr_acceptor_4_8";
		break;
		
		case "Mtr_acceptor_4_8":
            dialog.text = "Tartsd a kardodat hüvelyben, tengerész. Nem vagyok kutya és nem vagyok spicli. A helyi hajógyárban dolgozunk... Ez a selyem a miénk volt, és ha jól tudom, most már a tiéd. Megveszem az egészet tôled, szükségünk van erre a selyemre, haver.";
			link.l1 = "Tényleg? Érdekes... Mennyiért?";
			link.l1.go = "Mtr_acceptor_4_9";
		break;
		
		case "Mtr_acceptor_4_9":
			i = GetSquadronGoods(pchar, GOOD_SHIPSILK);
            dialog.text = "Kétezer és fél egy tekercs. Ez jó ár, ennél jobbat nem találsz.";
			link.l1 = "Úgy tûnik, szerencsém volt! Van "+FindRussianQtyString(i)+". Mutassa meg a pénzt, és azonnal megrendelem a partra szállítását.";
			if (i > 80) link.l1.go = "Mtr_acceptor_4_11";
			else link.l1.go = "Mtr_acceptor_4_10";
		break;
		
		case "Mtr_acceptor_4_10":
            dialog.text = "Áll az alku!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_CargoSilk");
			AddCharacterExpToSkill(pchar, "Fortune", 300);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 300);//скрытность
		break;
		
		case "Mtr_acceptor_4_11":
            dialog.text = "Hm... Joachimnak csak nyolcvan tekercset kellett volna szállítania - kizárt, hogy ennyit meg tudnál menteni... ami azt jelenti, hogy vagy piszkos játékot próbálsz játszani, vagy... besúgó vagy! Fiúk, öljétek meg és tûnjetek innen a pokolba!";
			link.l1 = "Bassza meg!";
			link.l1.go = "Mtr_acceptor_fight";
		break;
		
		case "Mtr_acceptor_5":
            dialog.text = "";
			link.l1 = "Nagyszerû üzlet, haver! Miért vagy ilyen borús? Aggódsz a hollandok miatt a tenger fenekén? Szarságok történnek, ne aggódj emiatt!";
			link.l1.go = "Mtr_acceptor_5_1";
		break;
		
		case "Mtr_acceptor_5_1":
            dialog.text = "Igen, persze... Ôk voltak a rendszeres szállítóink. Honnan szerezzük most a selymet? Mindig hiányt szenvedünk belôle, és az egész kereskedelem D'Oyley ezredes közvetlen irányítása alatt áll. Bah a fenébe...";
			link.l1 = "Hm... Figyelj, barátom, azt hiszem, ebben tudok segíteni.";
			link.l1.go = "Mtr_acceptor_5_2";
		break;
		
		case "Mtr_acceptor_5_2":
            dialog.text = "Tényleg? És hogyan képzeled, hogy segítesz nekünk? Minden hónapban szállítasz nekünk egy adag száz tekercset?";
			link.l1 = "Én? Hmm, valószínûleg nem, de Marcus Tyrex igen. Hallottál már róla?";
			link.l1.go = "Mtr_acceptor_5_3";
		break;
		
		case "Mtr_acceptor_5_3":
            dialog.text = "K-ha! Szóval, te kalóz vagy?";
			link.l1 = "Nem, csak különleges alkalmakkor üzletelek velük. Biztosan tudom, hogy Marcus állandóan kap egy csomó hajóselymet, és bárkinek eladja, aki megengedheti magának. És itt most nem 2500 pezóról beszélek egy tekercsért, azt mondanám, ha minden tekercsért 5 dublont tudsz neki aranyban fizetni, akkor belefojtja a vízbe, erre számíthatsz.";
			link.l1.go = "Mtr_acceptor_5_4";
		break;
		
		case "Mtr_acceptor_5_4":
            dialog.text = "Ezek érdekes hírek... Marcus Tyrexet mondtad? Csak dublonokban?";
			link.l1 = "Ugyan már haver, tényleg nem mindegy neked, hogy kitôl kapod a selymet? És a pénz az pénz, a bankban bármikor válthatsz pesót dublonnákra. És akkor mi van, súgjak egy-két szót rólad a kódôr fülébe? Úgyis La Vegába megyek.";
			link.l1.go = "Mtr_acceptor_5_5";
		break;
		
		case "Mtr_acceptor_5_5":
            dialog.text = "Nagyon jó. Akkor kössünk üzletet. Ezek a feltételeink: minden hónap 10. és 15. között egy adag száz tekercs. Itt fogunk várni... várjatok, változtassuk meg a találkozóhelyet, ez a hely most veszélyeztetett. A Negril-foknál fogunk várakozni, Maroon város közelében, ott biztonságosabb lesz. A jelszó - 'A merchant of Lyons'.";
			link.l1 = "Megegyeztünk, barátom. Pokoli utazás volt! Tyrex fizet nekem egy-két dublont egy ilyen vevôért! Ha-ha! Rendben, mennem kell. Várd Tyrex hajóját a jövô hónapban. Sok szerencsét neked és a családodnak!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_CargoSilkWin");
		break;
		
		case "Mtr_acceptor_6":
            dialog.text = "Nem lesz szükséged életleckékre, miután megtanítottunk az udvariasságra.";
			link.l1 = "Keményen viselkedsz, ács? Rendben, várj tovább a brigantidra, bár az eltart egy darabig.";
			link.l1.go = "Mtr_acceptor_6_1";
			if (GetSquadronGoods(pchar, GOOD_SHIPSILK) >= 20)
			{
				link.l2 = "Hé, tanár úr, nekem is van néhány leckém a számodra!";
				link.l2.go = "Mtr_acceptor_6_2";
			}
		break;
		
		case "Mtr_acceptor_6_1":
            dialog.text = "Ács? A fenébe is, honnan tudod? K-ha! Bassza meg, fiúk, ez egy álruhás ôrjárat! Öljétek meg és tûnjetek innen a pokolba!";
			link.l1 = "Basszus!";
			link.l1.go = "Mtr_acceptor_fight";
		break;
		
		case "Mtr_acceptor_6_2":
            dialog.text = "Hagyjál minket békén, te halpikkely, nincs idônk. Tûnjetek el!";
			link.l1 = "Egy bizonyos holland hajóra vársz? Sok szerencsét hozzá. Egy örökkévalóság áll elôttetek.";
			link.l1.go = "Mtr_acceptor_4_4";
		break;
		
		case "Mtr_acceptor_7":
            dialog.text = "Mi a fenérôl beszélsz?";
			link.l1 = "Értem. De ha mégis, felejtsd el. Nem jön, hála egy járôrkorvettnek. Egy távcsövön keresztül láttam a harc végét. Olyan gyorsan történt, és nem messze innen.";
			link.l1.go = "Mtr_acceptor_7_1";
		break;
		
		case "Mtr_acceptor_7_1":
            dialog.text = "Ismétlem, nem várunk senkire és semmire, és...";
			link.l1 = "Nézze, leszarom. Nem tartozom a városi ôrjárathoz, és nem érdekelnek a tetteitek, én magam sem vagyok angyal. Ha csempésznek - az a maguk dolga. Én csak figyelmeztetni akartalak. Sok szerencsét neked, haver.";
			link.l1.go = "Mtr_acceptor_7_2";
		break;
		
		case "Mtr_acceptor_7_2":
            dialog.text = "Várj... Biztos vagy benne, hogy a 'Utrecht' elsüllyedt?";
			link.l1 = "Teljesen. Megpróbált elmenekülni, mindent eldobott, ami a rakterében volt, még az értékes hajóselymet sem kímélték, de ilyen drasztikus intézkedések nem segíthettek egy korvett sebességbeli elônyével szemben.";
			link.l1.go = "Mtr_acceptor_7_3";
		break;
		
		case "Mtr_acceptor_7_3":
            dialog.text = "Milyen kár... és mihez kezdjünk a selyem nélkül? A fenébe is!";
			link.l1 = "Szükséged van hajóselyemre?";
			link.l1.go = "Mtr_acceptor_7_4";
		break;
		
		case "Mtr_acceptor_7_4":
            dialog.text = "Miért kérdezed, eladod?";
			link.l1 = "Én nem, de ismerek egy embert, aki igen. Nagylelkû és rendszeres vevôt keres. Gondolod, hogy be tudsz illeszkedni?";
			link.l1.go = "Mtr_acceptor_7_5";
		break;
		
		case "Mtr_acceptor_7_5":
            dialog.text = "És ki az az ember?";
			link.l1 = "Marcus Tyrex, La Vega bárója, ismertebb nevén a Kódôr. Folyamatosan kap hajóselymet, így mindig van mit eladnia. Gondolom, fontolóra veszi, hogy önnek is eladja, ha elég magas az ára.";
			link.l1.go = "Mtr_acceptor_7_6";
		break;
		
		case "Mtr_acceptor_7_6":
            dialog.text = "Szóval kalóz vagy?";
			link.l1 = "Miért érdekel téged? Elintézhetek egy üzletet közted és Tyrex között, ha van hozzá merszed. Ha nem - akkor viszlát.";
			link.l1.go = "Mtr_acceptor_7_7";
		break;
		
		case "Mtr_acceptor_7_7":
            dialog.text = "Jól van, jól van, ne légy mérges. Dehogynem. Üzletet akarok kötni Tyrexszel. De mi a hasznod belôle?";
			link.l1 = "Ha jó árat kínálsz a rakományért, valószínûleg tisztességes összeget kapok Marcustól a segítségemért. Szóval, mi lesz az?";
			link.l1.go = "Mtr_acceptor_7_8";
		break;
		
		case "Mtr_acceptor_7_8":
            dialog.text = "5 dublont egy tekercsért. Ez a legjobb ár, amit kaphat, higgye el nekem.";
			link.l1 = "5 aranyérme? Hm. Nem rossz. Azt hiszem, Tyrex sokat köszönhet nekem egy ilyen vevôért. Nagyon jó üzlet, majd szólok neki. Azonban, ha hazudtál nekem az árat illetôen, akkor a te segged a tét.";
			link.l1.go = "Mtr_acceptor_7_9";
		break;
		
		case "Mtr_acceptor_7_9":
            dialog.text = "Ne aggódjon, mi becsületes emberek vagyunk. Ezek a feltételeink: minden hónap 10. és 15. között száz tekercset kapunk. Itt fogunk várni... várjatok, változtassuk meg a találkozóhelyet, ez a hely már kompromittált. Negril-foknál várunk, Maroon város közelében, ott biztonságosabb lesz. A jelszó - 'A merchant of Lyons'.";
			link.l1 = "Megvan. Várjuk meg az elsô szállítmányt a jövô hónapban.";
			link.l1.go = "Mtr_acceptor_7_10";
		break;
		
		case "Mtr_acceptor_7_10":
            dialog.text = "Tudasd Tyrexszel, hogy ezúttal több szállítmányt hozhat, erre a hónapra selyem nélkül maradtunk.";
			link.l1 = "Úgy lesz. Isten éltessen, barátom.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_CargoSilkWin");
			AddCharacterExpToSkill(pchar, "Sneak", 300);//скрытность
		break;
		
		// Тесак Пелли
		case "Pelly":
            dialog.text = "Ahoy! Mi szél hozott a hajóm fedélzetére, barátom?";
			link.l1 = "Hé, Olló. Marcus Tyrex küldött. Maracaibo felé menetelünk.";
			link.l1.go = "Pelly_1";
		break;
		
		case "Pelly_1":
            dialog.text = "A-ah, végre. Szóval te leszel az új fônököm ezen az úton. Ez az. Hogy hívják az új admirálisomat?";
			link.l1 = "Kapitány "+GetFullName(pchar)+".";
			link.l1.go = "Pelly_2";
		break;
		
		case "Pelly_2":
            dialog.text = "Rendek, admirális "+GetFullName(pchar)+"?";
			link.l1 = "A Maracaibo-tóhoz külön-külön fogunk elhajózni. Éjszaka kell odaérni, és titokban partra szállni a Guajira-öbölben. Várjatok ott rám, és közben állítsatok fel egy kis tábort. Ami engem illet, én a spanyol kikötôben fogok partra szállni.";
			link.l1.go = "Pelly_3";
		break;
		
		case "Pelly_3":
            dialog.text = "Igenis, admirális!";
			link.l1 = "Mennyi idôbe telik, amíg odaérsz?";
			link.l1.go = "Pelly_4";
		break;
		
		case "Pelly_4":
            dialog.text = "Hmmm... Körülbelül egy hét múlva lesz. Egy nappal kevesebb, egy nappal több, minden a széltôl függ.";
			link.l1 = "A széltôl függ. Akkor ne vesztegessük az idôt. Találkozunk a Guajira-öbölben, barátom.";
			link.l1.go = "Pelly_5";
		break;
		
		case "Pelly_5":
            dialog.text = "Igenis, admirális!";
			link.l1 = "...";
			link.l1.go = "Pelly_6";
		break;
		
		case "Pelly_6":
            DialogExit();
			AddQuestRecord("Roger_3", "3");
			LAi_CharacterDisableDialog(npchar);
			npchar.DontDeskTalk = true;
			Mtraxx_PlantContinue();
		break;
		
		case "Pelly_7":
            dialog.text = "Parancs, admirális?";
			link.l1 = "Egyelôre semmi. Elfoglalt vagyok a hadmûveletünkkel.";
			link.l1.go = "Pelly_wait";
			if (pchar.questTemp.Mtraxx == "plant_3")
			{
				link.l1 = "Készítsen elô egy tágas ládát a parton. Fegyvereket fogunk gyûjteni benne a bebörtönzött testvéreinknek.";
				link.l1.go = "Pelly_7_1";
			}
			if (pchar.questTemp.Mtraxx == "plant_6" && CheckAttribute(pchar, "questTemp.mtraxx_PlantInfoTovar"))
			{
				dialog.text = "Szóval, mi a helyzet Szépfiúval? Viszket a kezem, hogy kiontsak egy kis Don-vért!";
				link.l1 = "Ez bonyolultabb, mint gondoltuk. Azt mondta, hogy az ültetvényen túlságosan éberek az ôrök. Az egyetlen módja a fegyverek becsempészésének az áruba rejtve van. Sürgôsen szereznünk kell egy szállítmány kávét, koprát vagy vaníliát - a helyi ültetvényes ezekkel foglalkozik, semmi mással.";
				link.l1.go = "Pelly_70";
				DelLandQuestMark(npchar);
			}
			if (pchar.questTemp.Mtraxx == "plant_8" && pchar.location.from_sea == "Shore37")
			{
				link.l1 = "Hagyjátok el a tábort, és gyûjtsetek össze egy rohamosztagot. Ideje indulni, a sötétség leple alatt támadunk.";
				link.l1.go = "Pelly_11";
				DelLandQuestMark(npchar);
			}
		break;
		
		case "Pelly_wait":
             DialogExit();
			 npchar.dialog.currentnode = "Pelly_7";
		break;
		
		case "Pelly_7_1":
            dialog.text = "Figyeljen, admirális, gondolkodtam...";
			link.l1 = "Mi ez, Terrax azért fizet, hogy gondolkodj, ahelyett, hogy a kardodat lóbálnád, mi, Olló?";
			link.l1.go = "Pelly_35";
		break;
		
		case "Pelly_8":
            dialog.text = "Ho! Lázadás az ültetvényen, igazam van, admirális? Lángok! Ebbôl aranyat fogunk szerezni!...";
			link.l1 = "Szükségem van egy ládára a parton, Olló.";
			link.l1.go = "Pelly_9";
		break;
		
		case "Pelly_9":
            dialog.text = "Azonnal, admirális!";
			link.l1 = "...";
			link.l1.go = "Pelly_10";
		break;
		
		case "Pelly_10":
            DialogExit();
			npchar.dialog.currentnode = "Pelly_7";
			pchar.questTemp.Mtraxx = "plant_4";
			pchar.questTemp.Mtraxx.Chest = "true";
			// подгружаем сундук в локу и меняем локаторы
			int n = Findlocation("Shore37");
			Locations[n].models.always.locators = "shore03_q_locators";
			locations[n].models.always.chest = "chest_quest";
			Locations[n].models.always.chest.locator.group = "box";
			Locations[n].models.always.chest.locator.name = "private1";
			Locations[n].models.always.chest.tech = "DLightModel";
			DoQuestReloadToLocation("Shore37", "goto", "goto5", "Mtraxx_PlantChestReady");
		break;
		
		case "Pelly_11":
            dialog.text = "Azonnal, admirális!";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PlantPrepareMarch");
		break;
		
		case "Pelly_12":
            dialog.text = "Az emberek készen állnak, admirális!";
			link.l1 = "Elôre!";
			link.l1.go = "Pelly_13";
		break;
		
		case "Pelly_13":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			chrDisableReloadToLocation = false;
		break;
		
		case "Pelly_14":
            dialog.text = "Admirális, úgy tûnik, Tyrex barátja, akit meg kellett volna mentenünk, már... halott.";
			link.l1 = "Igen, de semmit sem lehetett tenni. Láttad az ôröket, szerencsénk volt, hogy életben maradtunk.";
			link.l1.go = "Pelly_15";
		break;
		
		case "Pelly_15":
            dialog.text = "Admirális, Marcus dühös lesz rád. Ne menj most hozzá. Elmegyek. Neked is menned kéne.";
			link.l1 = "Igen...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PlantFailFinal");
		break;
		
		case "Pelly_16":
            dialog.text = "Rossz hírek, admirális. Egy spanyol hajóraj közeledik felénk keletrôl. Nincs idônk menekülni.";
			link.l1 = "Hányan vannak?";
			link.l1.go = "Pelly_17";
		break;
		
		case "Pelly_17":
            dialog.text = "Három hajó. Sok ágyúval. Meg vagyunk baszva."; // лесникПОСЛЕДНЕЕ
			link.l1 = "Majd meglátjuk.";// Жан, ты отправляйся на борт к Тесаку. Тесак, поднимешь испанский флаг и на всех парусах прочь отсюда - глядишь, за торговца сойдёшь. А я пойду прямо на испанцев - отвлеку их от вас. Увидимся в Ла Веге у Тиракса.";
			link.l1.go = "Pelly_181";
		break;
		case "Pelly_181":
	    	DialogExit();
		   sld = characterFromId("Mrt_Rocur");
		   sld.Dialog.currentnode = "Pelly_182";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		case "Pelly_182":
		   dialog.text = ""; 
		   link.l1 = "Jean, menj Cutlass hajójára.";
		   link.l1.go = "Pelly_183"; 
		break;
		case "Pelly_183":
		     DialogExit();
			sld = characterFromId("Pelly");
			sld.Dialog.currentnode = "Pelly_18";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		case "Pelly_18":
            dialog.text = "";//"De...";
			link.l1 = "Cutlass fel kellene emelned a spanyol zászlót, és elhúznod innen a pokolba. Majd én elterelem a figyelmüket rólad. Találkozunk La Vegában.";//"Отставить! Tesak, Jean Picardért felelsz a fejeddel Tiraxnak. Mindenki a fedélzetre!";
			link.l1.go = "Pelly_19";
		break;
		
		case "Pelly_19":
            dialog.text = "De...";
			link.l1 = "Nincs de! Cutlass, a te seggedet kockáztatod, ha Picard nem jut el Tyrex helyére. Mindenki a fedélzetre!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PlantSeaEscape");
		break;
		
		case "Pelly_20":
            dialog.text = "Parancsok, admirális?";
			link.l1 = "Készüljenek a harcra. A parancsomra támadjanak!";
			link.l1.go = "Pelly_21";
		break;
		
		case "Pelly_21":
            dialog.text = "Igenis, admirális... a parancsára!";
			link.l1 = "...";
			link.l1.go = "Pelly_22";
		break;
		
		case "Pelly_22":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			chrDisableReloadToLocation = false;
		break;
		
		case "Pelly_23":
            dialog.text = "Ho-ho! Helló, herceg. Mi szél hozta Tortugára?";
			link.l1 = "Marcus feladata megint. Figyelj, Cutlass, miért nem enged be az a fattyú, aki ebben a házban lakik?";
			link.l1.go = "Pelly_24";
		break;
		
		case "Pelly_24":
            dialog.text = "Gaspard Goldenteeth? Csak megbízható társaival dolgozik. Másoknak ajánlásra lenne szükségük, hogy vele dolgozzanak. Akarsz eladni néhány csillogó csecsebecsét? Kezeskedhetek érted, ha akarod...";
			link.l1 = "Szóval uzsorás? Mi az érdeke?";
			link.l1.go = "Pelly_25";
		break;
		
		case "Pelly_25":
            dialog.text = "Testvér, valamit kihagysz. Gaspard nem uzsorás, menj a "+GetFullName(characterFromId("Tortuga_usurer"))+" ha szükséged van rá. Goldenteeth drágaköveket és mindenféle ékszereket vásárol. Egyébként jól fizet és soha nem kérdez hülyeségeket. Minden kalózkapitány az ügyfele.";
			link.l1 = "Értem... Azt mondták, hogy néhányan közülük még a pénzüket is rábízzák...";
			link.l1.go = "Pelly_26";
		break;
		
		case "Pelly_26":
            dialog.text = "Ha-ha! Hazug volt az, aki ezt mondta neked, menj és köpj a szemérmetlen szemébe. Gaspard csak ékszerekkel dolgozik, mindig is így volt. Miért lenne gondja mások pénzével?";
			link.l1 = "Értem. Köszönöm, Cutlass, találkozunk a tengeren!";
			link.l1.go = "Pelly_27";
			link.l2 = "Hmm, valóban. Szóval, csecsebecséket vásárol? Érdekes... Azt mondod, szólsz egy jó szót az érdekemben?";
			link.l2.go = "Pelly_27z";
		break;
		
		case "Pelly_27":
            dialog.text = "Viszlát, herceg.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_WolfreekReadLogbookThird");
		break;
		
		case "Pelly_27z":
            dialog.text = "Természetesen! Most már közénk tartozol, hehe! Várj itt egy pillanatra.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_WolfreekPellyTalkGems");
		break;
		
		case "Pelly_28z":
            dialog.text = "Minden el van intézve! Most már Aranyfog tudja, hogy Charlie herceg jöhet hozzá csecsebecséket árulni. Csak azt tartsa szem elôtt, hogy az ára, bár jó, még mindig alacsonyabb, mint amit azok a fukar uzsorások fizetnek. De ô mindent tonnaszámra vesz meg! És felesleges kérdések nélkül, ahogy már mondtam.";
			link.l1 = "Ez az én jóképû legényem! Szép munka, Paul! Most már van hová kipakolnom a zsákmányt!";
			link.l1.go = "Pelly_29z";
		break;
		
		case "Pelly_29z":
            dialog.text = "Nem, Jean Picard a 'Handsome', én vagyok a 'Cutlass', haha! Viszlát, herceg!";
			link.l1 = "Köszönöm, Olló, sok szerencsét a tengeren!";
			link.l1.go = "Pelly_27";
		break;
		
		case "Pelly_28":
			PlaySound("VOICE\English\LE\Pelly\Pelly_03.wav");
            dialog.text = "Három madarat hoztam neked, herceg. A szekrényekben és az ágy alatt rejtôzködve találtam ôket. Szépek, mi? Ha-ha-ha-ha!";
			link.l1 = "Azt mondom, hogy valóban azok. És ápoltak is. Don Stubborn biztos nagyon törôdik velük.";
			link.l1.go = "Pelly_29";
		break;
		
		case "Pelly_29":
            DialogExit();
			sld = CharacterFromID("Mtr_CartahenaMayorClone");
			sld.dialog.currentnode = "CartahenaMayor_8";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Pelly_30":
			PlaySound("VOICE\English\LE\Pelly\Pelly_04.wav");
            dialog.text = "Mindenki hódoljon! Mi a faszt keresel itt, herceg?";
			link.l1 = "Bicska? Követtem a hangokat és a zajt, de soha nem gondoltam volna, hogy te leszel az. Hogy a fenébe kerültél ide?";
			link.l1.go = "Pelly_31";
			QuestPointerDelLoc("Judgement_dungeon_01", "reload", "reload2_back");
			QuestPointerDelLoc("Judgement_dungeon_02", "reload", "reload2");
			QuestPointerDelLoc("Judgement_dungeon_03", "reload", "reload2");
			QuestPointerDelLoc("Judgement_dungeon_04", "reload", "reload2");
			QuestPointerDelLoc("Judgement_dungeon_05", "quest", "pelly");
		break;
		
		case "Pelly_31":
            dialog.text = "Nem, te miért vagy itt! Te mindig itt vagy! Tyrex biztos téged küldött a kincsért, igaz? Caramba, megint elkéstem...";
			link.l1 = "Tyrex? Nem... vettem egy térképet egy szajhától. Valószínûleg eladott neked egy másolatot, mi? Tortugán? Micsoda ravasz ribanc. De nem hazudott - nézd ezt a halom aranyat! Visszajövök még több emberrel, hogy elhozzam ezt az egészet...";
			link.l1.go = "Pelly_32";
		break;
		
		case "Pelly_32":
            dialog.text = "A pokolba is, ez egy rakás arany! De nem a tiéd vagy Tyrexé! Én találtam meg elôször! Ez az enyém! Nem számít, hogyan szereztem tudomást róla! Semmi közöd hozzá!";
			link.l1 = "Nyugodj meg, Olló, miért vagy ilyen dühös? Nézd ezt a kupacot - legalább egymillió van benne. Talán még több is! Elég lesz mindkettônknek!";
			link.l1.go = "Pelly_33";
		break;
		
		case "Pelly_33":
            dialog.text = "Mindig jobb szeletet kapsz a pitébôl, herceg! De ezúttal nem! A kincs az enyém! Én találtam meg elôször!";
			link.l1 = "A fenébe, Paul, mi bajod van? Nem tudnánk megegyezni? Ennek az aranynak még a fele is egy vagyon. Soha nem volt még ekkora összeg a kezedben. Ráadásul egy nap találhatnék egy jövedelmezô nyomot, és elmondhatnám neked.";
			link.l1.go = "Pelly_34";
		break;
		
		case "Pelly_34":
            dialog.text = "Meg akarsz baszni, Prince? Kizárt dolog! Nem adok neked egyetlen érmét, egyetlen guinea-t sem! Elkéstél!\nA-ah, látom, mire készülsz! Kizárt, hogy megkapd ezt az aranyat!!!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_RetributionPellyFight");
		break;
		
		case "Pelly_35": //
            dialog.text = "Fergeteges. Tényleg. Maga egy komikus, admirális. De igaz - Marcus nem szereti azokat, akik megpróbálnak túljárni az eszén, mint te. De az okos embereket értékeli.";
			link.l1 = "Rendben, rendben. Szóval, mi jár a fejében?";
			link.l1.go = "Pelly_36";
		break;
		
		case "Pelly_36":
            dialog.text = "Valami, amire te és Jóképû nyilván nem gondoltatok. Lázadást tervezel az ültetvényen. Remek ötlet - ha a cél a fosztogatás vagy a káosz. De...";
			link.l1 = "De mi? Te a lázadás ellen vagy? Félelemkeltés?";
			link.l1.go = "Pelly_37";
		break;
		
		case "Pelly_37":
            dialog.text = "Engem? Soha. De gondolj bele, mi lesz, ha Jóképûnek vége lesz a mészárlás során. Mit mondunk Marcusnak? Megmondom neked - nem fog számítani, hogy mit mondunk. Úgyis elkapja a bôrünket.";
			link.l1 = "Hmm. Szóval mi a te zseniális terved? Valahogy ki kell juttatnunk innen.";
			link.l1.go = "Pelly_38";
		break;
		
		case "Pelly_38":
            dialog.text = "Valahogy ki kell ôt juttatnunk valahogy. Ezért... miért nem vesszük meg? Kifelé... Hivatalosan. Egy maréknyi aranyért bárkit megvehetünk ezektôl a szemétládáktól - még a saját anyjukat is. Mit mondhatnék szegény Jeanról?";
			link.l1 = "Ha! Olló, komolyan azt akarod mondani, hogy menjek be egy ültetvényre, és kérjem meg, hogy megvehessem Picardot? Azt is mondjam meg, hogy kinek dolgozom, csak a vicc kedvéért? Elment az eszed?";
			link.l1.go = "Pelly_39";
		break;
		
		case "Pelly_39":
            dialog.text = "Nem kell ezt mondanod. Sôt, épp ellenkezôleg - tegyél úgy, mintha kereskedô lennél. Persze, nincs meg benned a szerephez a kellô bátorság, de kalóznak sem nézel ki. Ne vegye sértésnek, admirális, de ez az igazság. Csak lépj be az ültetvényre, viselkedj magabiztosan, és kérj Jeant. A tulajdonos talán sejti, hogy ki vagy, de nem fogja mutatni. Ahogy mondtam - egy maréknyi aranyfóka szája.";
			link.l1 = "És mennyibe kerülne nekünk ez a... kéznyi arany? Az egész hegyet?";
			link.l1.go = "Pelly_40";
		break;
		
		case "Pelly_40":
            dialog.text = "Talán. De inkább váljunk meg az aranytól, mint a fejünktôl. Nem tétlenkedtem, amíg te a parton voltál - öltöztem át valami kevésbé kalózos ruhába, és kérdezôsködtem az ültetvényrôl és szerény tulajdonosáról.";
			link.l1 = "És mit találtál, Olló?";
			link.l1.go = "Pelly_41";
		break;
		
		case "Pelly_41":
            dialog.text = "Piaci árakat, hogy úgy mondjam. Nem ez az elsô alkalom, hogy egy értékes fogoly az ölében landol. Általában az akasztófán kötnek ki, vagy ami még rosszabb - az inkvizíció tömlöcében.";
			link.l1 = "És mennyiért adja el ôket?";
			link.l1.go = "Pelly_42";
		break;
		
		case "Pelly_42":
            dialog.text = "Egy fontos emberért? Ötszáz érméért. Természetesen dublonokban.";
			link.l1 = "ÖTSZÁZ?!";
			link.l1.go = "Pelly_43";
		break;
		
		case "Pelly_43":
            dialog.text = "Ültetvényesek, mit vártatok?";
			link.l1 = "Ennyiért egy kisebb hadsereget is felszerelhetnék! Akkor mi a fenéért halmozok fel arzenált a hajómon egy felkeléshez? Ez elég lesz egy kis háborúra.";
			link.l1.go = "Pelly_44";
		break;
		
		case "Pelly_44":
            dialog.text = "A fegyverek késôbb jól jönnek majd a legénységednek. Szóval, mit mondasz?";
			if (IsCharacterPerkOn(pchar, "Trustworthy"))
			{
				if (PCharDublonsTotal() >= 500)
				{
					link.l1 = "(Megbízható) csak annyit mondok, hogy vicces lesz, ha Terrax' jutalom kevesebb lesz, mint amit itt elköltünk. De igazad van - az életünk többet ér. Nálam vannak a dublonok.";
					link.l1.go = "Pelly_45";
				}
				link.l2 = "Nekem most nincs ennyi aranyhegyem.";
				link.l2.go = "Pelly_44_1";
				Notification_Perk(true, "Trustworthy");
			}
			else Notification_Perk(false, "Trustworthy");
			link.l3 = "Tudod mit, Cutlass? Felejtsd el. Kalózok vagyunk, vagy mi? És Jean? Vagy csak a csinos arca az egyetlen elônye? Készíts egy ládát - maradunk az eredeti tervnél.";
			link.l3.go = "Pelly_62";
		break;
		
		case "Pelly_44_1":
            dialog.text = "Meglepôdnék, ha így lenne - ez egy hatalmas összeg. Rendben, ha készen állsz, vagy ha kitalálsz valami jobbat, keress meg.";
			link.l1 = "Úgy lesz. Várjon itt.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Pelly_44_2";
		break;
		
		case "Pelly_44_2":
			dialog.text = "Nos, admirális, összeszedett elég aranyat, hogy megmentse Picardot?";
			if (PCharDublonsTotal() >= 500)
			{
				link.l1 = "Igen, végre sikerült. Reméljük, hogy mûködik.";
				link.l1.go = "Pelly_45";
			}
			link.l2 = "Még dolgozom rajta, Cutlass.";
			link.l2.go = "exit";
			link.l3 = "Nem adom a nehezen megkeresett pénzemet azoknak a kapzsi ültetvényeseknek! Készítsd elô a ládát - úgy fogunk viselkedni, mint a Szerencse Urai. Ez az én döntésem.";
			link.l3.go = "Pelly_9";
			NextDiag.TempNode = "Pelly_44_2";
		break;
		
		case "Pelly_45":
            dialog.text = "Hûha. Még új vagy a csapatban, és máris ennyi pénzzel dobálózol!";
			link.l1 = "A pénz nem minden. De a Terrax' dicsôségben sütkérezni? Felbecsülhetetlen.";
			link.l1.go = "Pelly_46";
			pchar.questTemp.mtraxx_PlantVykup = true;
		break;
		
		case "Pelly_46":
            dialog.text = "Ezzel nem lehet vitatkozni. De ahogy mondtad, nem csak a pénzrôl van szó - van valami más fontos, Admirális.";
			link.l1 = "Most már kíváncsi vagyok. Mire?";
			link.l1.go = "Pelly_47";
		break;
		
		case "Pelly_47":
            dialog.text = "Mondtam, hogy mindent felderítettem az ültetvényrôl. Beleértve azt is, hogy milyen árukra van itt kereslet és milyenek a piacon. Ha törvényes kereskedônek akarod kiadni magad, akkor jobb, ha felhalmozod azokat, ahelyett, hogy egy halom aranyat dobsz az ültetvényes asztalára.";
			link.l1 = "Van értelme. Milyen árukról beszélünk?";
			link.l1.go = "Pelly_48";
		break;
		
		case "Pelly_48":
            dialog.text = "Nos, az élô árut leszámítva, a helyi ültetvénytulajdonos kávét, koprát és vaníliát vásárol, kereskedik és továbbértékesíti. Szóval...";
			link.l1 = "Gyorsan fel kell töltenem valahol ezeket. Vagy lecsapni egy karavánra, és remélni, hogy az elhozza, amire szükségem van.";
			link.l1.go = "Pelly_49";
		break;
		
		case "Pelly_49":
            dialog.text = "Nem akármilyen karaván. Nem szívesen válok meg tôle, de van egy ólom, amit félretettem magamnak. Hamarosan felbukkan egy karaván, ami pontosan azt szállítja, amire szükséged van. De van egy kikötés...";
			link.l1 = "Ó, most mi van?";
			link.l1.go = "Pelly_50";
		break;
		
		case "Pelly_50":
            dialog.text = "Francia zászló alatt van.";
			link.l1 = "Micsoda?!";
			link.l1.go = "Pelly_51";
		break;
		
		case "Pelly_51":
            dialog.text = "Megértem a frusztrációdat, ha-ha. A döntés a tiéd... Admirális. Akarja a részleteket?";
			link.l1 = "A fenébe is... Rendben, mondd el. Nincs sok idônk - ha maga vagy én nem csípjük el ôket, akkor majd valaki más.";
			link.l1.go = "Pelly_52";
			// link.l2 = "I don't touch the French unless I have no choice. End of discussion.";
			// link.l2.go = "Pelly_51_1";
		break;
		
		case "Pelly_51_1":
            dialog.text = "Akkor jobb lesz, ha elkezdi összeszedni az összes árut, méghozzá gyorsan, mielôtt Pretty Boy-t eladják valakinek. Én sem maradhatok itt örökké.";
			link.l1 = "Gondoltam.";
			link.l1.go = "Pelly_51_2";
		break;
		
		case "Pelly_51_2": // добываем товары сами
            DialogExit();
			
			LAi_SetActorType(npchar);
			AddQuestRecord("Roger_3", "28");
			SetTimerCondition("Mtraxx_PlantCaravanGuadeloupe", 0, 0, 14, false);
			SetTimerCondition("Mtraxx_PlantCaravanGuadeloupe_time", 0, 0, 45, false);
		break;
		
		case "Pelly_52":
            dialog.text = "Ez már jobban tetszik! Tudtam, hogy megvan benned... Admirális. Szóval, a helyzet a következô: megbízható kapcsolatom nemrég jelentette, hogy körülbelül két héten belül egy francia karaván, amely kávét és fûszereket szállít, megjelenik Guadeloupe vizein. Nagy és jól felfegyverzett, úgyhogy készüljenek fel alaposan.";
			link.l1 = "Mi más választásom van.";
			link.l1.go = "Pelly_53";
		break;
		
		case "Pelly_53": // наводка на караван с нужными товарами
            DialogExit();
			
			LAi_SetActorType(npchar);
			AddQuestRecord("Roger_3", "28");
			SetTimerCondition("Mtraxx_PlantCaravanGuadeloupe", 0, 0, 14, false);
			SetTimerCondition("Mtraxx_PlantCaravanGuadeloupe_time", 0, 0, 45, false);
		break;
		
		case "Pelly_54": // провал выкупа Красавчика
            dialog.text = "Lefelé néz, admirális. Hol van Szépfiú? Minden elszállt a csatornán?";
			link.l1 = "Igen, így van. Tisztes pénzt kerestem, de az a makacs öszvér nem volt hajlandó eladni nekem Picardot - még egy rakás dublonnáért sem!";
			link.l1.go = "Pelly_55";
		break;
		
		case "Pelly_55":
            dialog.text = "Micsoda bolond! És most mi lesz?";
			link.l1 = "Már megegyeztem az ültetvényessel, hogy kirakodják az árut. Vissza kell térnünk az eredeti tervhez - most vagy soha!";
			link.l1.go = "Pelly_56";
		break;
		
		case "Pelly_56":
            dialog.text = "De még semmit sem készítettünk elô Szépfiúnak és a többieknek!";
			link.l1 = "Nincs idônk! Szálljatok fel a hajókra - fegyvereket és gyógyszereket csempészünk a rakterünkbôl az áruszállító zsákokba. És ne felejtsétek el kitûzni a spanyol zászlót!";
			link.l1.go = "Pelly_57";
		break;
		
		case "Pelly_57":
            dialog.text = "Úgy hangzik, mint egy terv.";
			link.l1 = "Egyébként sincs idônk semmi másra. Mozgás! A kirakodás hamarosan megtörténik.";
			link.l1.go = "Pelly_58";
		break;
		
		case "Pelly_58":
            DialogExit();
			DoQuestFunctionDelay("Mtraxx_PlantWaitDay", 1.0);
		break;
		
		case "Pelly_59":
            dialog.text = "Nézd csak, ki van itt! Jóképû! És az ép arcodból és a hûvös járásodból ítélve, gondolom, minden simán ment?";
			link.l1 = "A zökkenômentesen még alábecsülés is - nem csak hogy elkerültem a harcot és visszavásároltam Jeant, de még pénzt is kerestem. A terved hibátlanul mûködött, Paul. Minden csendes a horizonton?";
			link.l1.go = "Pelly_60";
		break;
		
		case "Pelly_60":
            dialog.text = "Olyan csend, amilyen csak lehet. Visszamész Marcushoz?";
			link.l1 = "Rendben.";
			link.l1.go = "Pelly_61";
		break;
		
		case "Pelly_61":
            DialogExit();
			AddDialogExitQuestFunction("Mtraxx_PlantSuccessfulRedemption");
		break;
		
		case "Pelly_62":
            dialog.text = "Hmm, ahogy kívánja, Admirális. De ha valami történik Szépfiúval, gondoskodom róla, hogy Terrax megtudja, hogy figyelmen kívül hagytad a tanácsomat. Minden készen áll a kitörésre?";
			link.l1 = "Hadd ellenôrizzem le még egyszer, és számoljam meg, mi van a ládában.";
			link.l1.go = "Pelly_63";
		break;
		
		case "Pelly_63":
            dialog.text = "Biztos lehet benne. Segíthetek egy kis pénzért és az erôfeszítéseim fedezésére, heh-heh.";
			link.l1 = "Mit szólsz hozzá?";
			link.l1.go = "Pelly_64";
		break;
		
		case "Pelly_64":
            dialog.text = "Van egy kapcsolatom, egy fegyverkereskedô Maracaibóban. Álcázom magam, beosonok, fizetek neki, és elintézem, hogy a fegyvereket idecsempésszék. De ez sokba fog kerülni - arany dublonokba, hogy pontos legyek.";
			link.l1 = "És miért nem mutattál be már korábban ennek a fickónak? Mennyibe fog ez nekem kerülni?";
			link.l1.go = "Pelly_65";
		break;
		
		case "Pelly_65":
            dialog.text = "Bemutassalak az összes informátoromnak is? Igen, persze. Költségekkel, kockázatokkal és az én részemmel együtt... körülbelül annyiba fog kerülni, mint a váltságdíj Szépfiúért.";
			link.l1 = "Olló, istenfélelem...";
			link.l1.go = "Pelly_66";
		break;
		
		case "Pelly_66":
            dialog.text = "Nem félek sem Istentôl, sem öntôl, admirális. De Marcus' harag, ha nem sikerül megmentenünk Jeant? Az egy másik történet. Szóval, mi legyen? Segítsek a ládával?";
			if (PCharDublonsTotal() >= 500)
			{
				link.l1 = "Rendben, rajta - már így is elég idôt vesztegettünk. Tessék, ez a megfelelô mennyiség lesz.";
				link.l1.go = "Pelly_68";
			}
			link.l2 = "Ez rengeteg pénz, Paul. Át kell gondolnom.";
			link.l2.go = "Pelly_67";
			link.l3 = "Ez túl drága egy kis tétel fegyverért, amit sokkal olcsóbban is megvehetek nagyban! Nem, köszönöm, majd én elintézem.";
			link.l3.go = "Pelly_67_1";
		break;
		
		case "Pelly_67":
            dialog.text = "Nos, gondolkozz csak. De ne feledd - amíg gondolkozol, a zúzódások száma Szépfiú arcán és testén óráról órára nô, he-he-he-he.";
			link.l1 = "Hozom a dublont...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Pelly_67_2";
		break;
		
		case "Pelly_67_1":
            dialog.text = "Nem a szállítmány méretérôl van szó, hanem az idôzítésrôl és a kockázatokról. De ahogy akarod.";
			link.l1 = "Bízz bennem, tudom. Csak készítsd elô a ládát - innen átveszem.";
			link.l1.go = "Pelly_10";
		break;
		
		case "Pelly_67_2":
            dialog.text = "Készen áll, admirális? Kell segítség a fegyverekkel, vagy még mindig kevés az arany?";
			if (PCharDublonsTotal() >= 500)
			{
				link.l1 = "Végre van elég! Fogd és intézd el ezt a dolgot - kezd az idegeimre menni.";
				link.l1.go = "Pelly_68";
			}
			link.l2 = "Vigyázz a hangodra, Olló. Készen állok, de több idôre van szükségem, hogy összeszedjem a pénzt.";
			link.l2.go = "Pelly_67";
			link.l3 = "Ez túl drága egy kis tétel fegyverért, amit sokkal olcsóbban is megvehetek nagyban! Nem, köszönöm, majd én elintézem.";
			link.l3.go = "Pelly_67_1";
		break;
		
		case "Pelly_68":
            dialog.text = "Ó, micsoda egy rakás dubloon ez! De ne aggódj - minden érme a tervhez fog tartozni. Különben Marcus késôbb kiásna a sírból, heh-heh. Most pedig menj el Szépfiúhoz, Admirális, és mondd meg neki, hogy minden készen áll.";
			link.l1 = "Itt én adom a parancsokat. Most pedig induljatok.";
			link.l1.go = "Pelly_69";
			RemoveDublonsFromPCharTotal(500);
		break;
		
		case "Pelly_69":
            DialogExit();
			sld = characterFromId("Pelly");
			sld.dialog.currentnode = "Pelly_7";
			pchar.questTemp.Mtraxx = "plant_5";
			AddQuestRecord("Roger_3", "30");
			sld = characterFromId("Mrt_Rocur");
			LAi_CharacterEnableDialog(sld);
			sld.dialog.currentnode = "rocur_wait";
			sld.greeting = "Rocur_02";
			AddLandQuestMark(sld, "questmarkmain");
		break;
		
		case "Pelly_70":
            dialog.text = "Igen, ez egy probléma. Mi a terve, admirális?";
			link.l1 = "Gyorsan fel kell töltenem valahol ezeket. Vagy lecsapni egy karavánra, és remélni, hogy az elhozza, amire szükségem van.";
			link.l1.go = "Pelly_49";
			DeleteAttribute(pchar, "questTemp.mtraxx_PlantInfoTovar");
		break;
		
		// Жан Пикар
		case "rocur":
            dialog.text = "Mit akarsz tôlem?";
			link.l1 = "Barátom, Jean Picardot keresem. Van rá esély, hogy ugyanazt a nevet viseli?";
			link.l1.go = "rocur_1";
		break;
		
		case "rocur_1":
            dialog.text = "Van rá esély. De nem emlékszem az arcára.";
			link.l1 = "Ne legyen túl durva, Jean. Marcus Tyrex küldött ide. Az a parancsom, hogy vigyem ki innen.";
			link.l1.go = "rocur_2";
		break;
		
		case "rocur_2":
            dialog.text = "Marcus? Tsh-sh... Csitt. Sajnálom, barátom, ezt nem tudtam. De nem kéne itt beszélnünk, mindenhol ott vannak a kibaszott ôrök, és mindig hallgatóznak... Látom, szívesen látott vendég vagy a spanyolok között, keress meg éjjel az egyik kunyhóban és beszélgetünk. Várni fogok rád, testvér.";
			link.l1 = "...";
			link.l1.go = "rocur_3";
		break;
		
		case "rocur_3":
            DialogExit();
			AddQuestRecord("Roger_3", "6");
			LAi_CharacterDisableDialog(npchar);
			Mtraxx_PlantMakeMaxRocurClone();
		break;
		
		case "rocur_4":
            dialog.text = "Nos, itt biztonságos... Mi a neved, testvér?";
			link.l1 = "Kapitány "+GetFullName(pchar)+". Most mondd el, hogy kerültél ebbe a szarba. Tyrex mindent tudni akar.";
			link.l1.go = "rocur_5";
		break;
		
		case "rocur_5":
            dialog.text = "Egy idegen szólított meg egy willemstadi kocsmában... Arra kért, hogy legyek a társa egy holland karaván kifosztásánál. Nekem volt egy brigantim, neki egy polákja, ráadásul egy nagyon különleges. Így hát levadásztunk egy karavánt Caracastól nem messze, és kifosztottuk... Éjszaka volt, épp a zsákmányt osztottuk szét, amikor egy hatalmas spanyol gálya tûnt fel a sötétben\nTársam elmenekült, én is. De az én sérült brigantínomnak nem volt módja elmenekülni egy gálya és két másik hajó elôl. Felszálltak ránk, és minden túlélôt eladtak ide, mint a marhákat.";
			link.l1 = "Értem. Azt hiszed, baleset volt? Én a gályáról beszélek.";
			link.l1.go = "rocur_6";
		break;
		
		case "rocur_6":
            dialog.text = "A pokolba is, ha tudnám. Lehet, hogy lövöldözést hallottak, nem messze volt a Main-tól.";
			link.l1 = "Nem volt messze a Main-tól. Lehetséges. Találkozott már az egykori társával? Ki volt az?";
			link.l1.go = "rocur_7";
		break;
		
		case "rocur_7":
            dialog.text = "Még sosem találkoztam vele. Azt mondta, Ignacio Marco a neve, egy angol magánhajós. Komoly ember benyomását keltette, ezért is egyeztem bele, hogy részt veszek ebben a vállalkozásban. Tapasztalt matróz és kapitány, az biztos, daliás legénység áll mögötte, és a polákja egy szépség, nem minden nap látni ilyen hajót.";
			link.l1 = "Ignacio Marco? Egy angol kalóz? Spanyol?";
			link.l1.go = "rocur_8";
		break;
		
		case "rocur_8":
            dialog.text = "Ô portugál, nem spanyol. Mi a baj az angol hadlevéllel? Sok spanyol van a fajtánkban, ezt te is tudod.";
			link.l1 = "Értem. Rendben, beszéljünk a menekülésedrôl. Van valami ötleted?";
			link.l1.go = "rocur_9";
		break;
		
		case "rocur_9":
            dialog.text = "Mik a számok?";
			link.l1 = "Az én hajóm, egy barquentine és a Pelly the Cutlass emberei. A hajóm Maracaibo kikötôjében állomásozik. A Cutlass partra szállt a Guajira-öbölben, és ott tábort vert.";
			link.l1.go = "rocur_10";
		break;
		
		case "rocur_10":
            dialog.text = "Hmm...";
			link.l1 = "Mi az, azt várta, hogy Tyrex ide küldi a hadihajóját?";
			link.l1.go = "rocur_11";
		break;
		
		case "rocur_11":
            dialog.text = "Nem számítottam semmire. Igazából meglep, hogy Marcus nem feledkezett meg rólam.";
			link.l1 = "Nyilvánvalóan nem. Szóval, van valami ötleted?";
			link.l1.go = "rocur_12";
		break;
		
		case "rocur_12":
            dialog.text = "Innen nincs esély a szökésre - ez az ültetvény túl jól ôrzött, és vad dzsungel van körülötte. Megrohamozni sincs értelme, nincs elég embered, ráadásul a közelben van egy erôd.";
			link.l1 = "Talán te és a fiaid tudnátok segíteni nekünk odabentrôl? Üssétek ôket keményen hátulról.";
			link.l1.go = "rocur_13";
		break;
		
		case "rocur_13":
            dialog.text = "Mivel? Puszta kézzel és rozsdás bozótvágó késsel?";
			link.l1 = "És mi lenne, ha lenne fegyveretek?";
			link.l1.go = "rocur_14";
		break;
		
		case "rocur_14":
            dialog.text = "Nos, ebben az esetben a pokolra küldtük volna ôket. Van azonban egy probléma, mindent ellenôriznek, amit beviszel, nincs az az isten, hogy fegyvert csempéssz. Szóval azt javaslom, felejtsd el ezt.";
			link.l1 = "És mégis, jelenleg ez a legjobb lehetôségünk. Majd kitalálom, hogyan szállíthatnánk neked és az embereidnek fegyvereket... Mondjátok, hányan vagytok képesek harcolni?";
			link.l1.go = "rocur_15";
		break;
		
		case "rocur_15":
            dialog.text = "Harminc fô, azt mondanám.";
			link.l1 = "Akkor harminc szablya... A kézifegyverek is sokat számítanának, azt hiszem.";
			link.l1.go = "rocur_16";
		break;
		
		case "rocur_16":
            dialog.text = "Kapitány, komolyan gondolja ezt?";
			link.l1 = "Igen, komolyan. Szándékosan érkeztem ide, a viccelôdés nem tartozik ide. Mi mást tudna még használni?";
			link.l1.go = "rocur_17";
		break;
		
		case "rocur_17":
            dialog.text = "Rendben... Legalább próbáljuk meg. Egyszerû hideg acélra van szükségünk - a fiaimat nem arra képezték ki, hogy csicsás pengékkel és hasonlókkal dolgozzanak. Ugyanez elmondható a kézifegyverekrôl is, a legolcsóbb is megteszi. Ha szereznél nekünk egy-két muskétát, az is sokat segítene, van pár fiúm, akik jól bánnak a muskétákkal. Golyók, puskapor. A gyógyító italokat a legjobban örömmel fogadjuk.";
			link.l1 = "Megvan. Pengéket és fejszéket a hajó arzenáljából lehet venni. A többit már nehezebb megszerezni. Majd szólok, ha megvan minden.";
			link.l1.go = "rocur_18";
		break;
		
		case "rocur_18":
            dialog.text = "Kérlek, siess, testvér. Nincs itt fél évünk, ez a kibaszott marhamunka egytôl egyig megöl minket. Ha szükséged lesz rám - gyere hozzám esténként.";
			link.l1 = "Értettem, haver. Várj, megpróbálom nem megvárakoztatni. És légy óvatos, ne adj okot arra, hogy leírjanak.";
			link.l1.go = "rocur_19";
		break;
		
		case "rocur_19":
            DialogExit();
			AddQuestRecord("Roger_3", "7");
			npchar.dialog.currentnode = "rocur_wait";
			pchar.questTemp.Mtraxx = "plant_3";
			pchar.questTemp.Mtraxx.MagicBox = "Baster";
			AddLandQuestMark(characterFromId("Fadey"), "questmarkmain");
			AddMapQuestMarkCity("baster", false);
			pchar.quest.Mtraxx_PlantPrepareTimeOver.over = "yes"; //снять таймер
			SetFunctionTimerCondition("Mtraxx_SeekWeaponOver", 0, 0, 30, false); // таймер
		break;
		
		case "rocur_wait":
            dialog.text = "Van valami hír, haver? Összeszedted a fegyvereket?";
			if (pchar.questTemp.Mtraxx == "plant_5")
			{
				link.l1 = "Igen. Egy láda lôszerrel a Guajira-öbölben van. Már csak azt kell kitalálni, hogyan csempésszük be az ültetvényre.";
				link.l1.go = "rocur_20";
			}
			else
			{
				link.l1 = "Rajta vagyok. Várjon, várjon.";
				link.l1.go = "rocur_wait_1";
			}
		break;
		
		case "rocur_wait_1":
            DialogExit();
			npchar.dialog.currentnode = "rocur_wait";
		break;
		
		case "rocur_20":
            dialog.text = "Rendben, kapitány. Már gondolkodtam azon, hogy hogyan fogjuk ezt végrehajtani.";
			link.l1 = "Örömmel hallom. Mi jár a fejében?";
			link.l1.go = "rocur_21";
			DelLandQuestMark(npchar);
		break;
		
		case "rocur_21":
            dialog.text = "Ezen az ültetvényen cukrot termelnek és kakaóbabot termesztenek. Néha a vezetôje maga adja el az árut, így jövedelmezôbb. Tegyen neki egy ajánlatot. Ne pénzzel, hanem áruval fizess neki. Valamivel, amit dobozokba tudsz tenni, mint például kopra, vanília vagy kávé. Tegyél némi erôfeszítést az alkudozásba, de ne vidd túlzásba\nFegyvereket rejts el egy-két ládába, és tegyél rájuk jeleket. Este szervezzétek meg a cserét, hogy egy éjszakára kint kelljen hagyniuk a dobozokat\nAz éjjel megtaláljuk a megjelölt dobozokat, felfegyverkezünk, és pokollá tesszük a spanyolokat. Természetesen a ti segítségetekkel.";
			link.l1 = "Szép gondolat, testvér! Nagyon jó, tetszik ez a terv. Tartsuk magunkat hozzá.";
			link.l1.go = "rocur_22";
		break;
		
		case "rocur_22":
            dialog.text = "Még egy utolsó dolog - csak egyféle árut ajánljatok fel cserére. Többféle áru - több kocka, amit az ôrök ellenôriznek.";
			link.l1 = "Egyetértek. Akkor csak egyféle árut fogok választani. Kávét, vaníliát és koprát mondtál?";
			link.l1.go = "rocur_23";
		break;
		
		case "rocur_23":
            dialog.text = "Igen. Ez jó üzletnek fog tûnni az ültetvény vezetôjének.";
			link.l1 = "Megvan. Majd szólok, ha az üzlet megköttetett.";
			link.l1.go = "rocur_24";
		break;
		
		case "rocur_24":
            DialogExit();
			AddQuestRecord("Roger_3", "9");
			npchar.dialog.currentnode = "rocur_wait_2";
			pchar.questTemp.Mtraxx = "plant_6";
			pchar.questTemp.mtraxx_PlantInfoTovar = true;
			AddLandQuestMark(characterFromId("Pelly"), "questmarkmain");
		break;
		
		case "rocur_wait_2":
            dialog.text = "Menj barátom, az idô aranyat ér, és nekünk nincs...";
			link.l1 = "";
			link.l1.go = "rocur_wait_3";
		break;
		
		case "rocur_wait_3":
            DialogExit();
			npchar.dialog.currentnode = "rocur_wait_2";
		break;
		
		case "rocur_25":
            dialog.text = "...";
			link.l1 = "(csendesen) Az üzlet megköttetett. A dobozokat holnap este szállítják az ültetvényre. A dobozok, amelyekre szükségük van, egy 'W' betûvel vannak jelölve. A többin az ábécé többi betûje van. Készítsétek fel az embereiteket. Hajnal elôtt, valahol három óra körül fogunk támadni.";
			link.l1.go = "rocur_25x";
			DelLandQuestMark(npchar);
		break;
		
		case "rocur_25x":
            dialog.text = "A jelére indulunk...";
			link.l1 = "";
			link.l1.go = "rocur_26";
		break;
		
		case "rocur_26":
            DialogExit();
			LAi_CharacterDisableDialog(npchar);
			DoQuestFunctionDelay("Mtraxx_PlantWaitDay", 3.0);
		break;
		
		case "rocur_27":
            dialog.text = "Végre! Hamarosan újra látom a tengert! Már elfelejtettem a látványát és az illatát. Szép munka, kapitány! Tartozom neked.";
			link.l1 = "Ne aggódj emiatt, majd késôbb elintézzük... Most pedig szálljunk be, és tûnjünk el innen!";
			link.l1.go = "rocur_28";
		break;
		
		case "rocur_28":
            DialogExit();
			sld = characterFromId("Pelly");
			sld.Dialog.currentnode = "Pelly_16";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "rocur_29":
            dialog.text = "Üdvözlet "+pchar.name+". Örülök, hogy újra látlak, és annak is örülök, hogy társam vagy ebben a kalandban. Kemény lesz ez a munka, de biztos vagyok benne, hogy végigcsináljuk.";
			link.l1 = "Örülök, hogy újra találkoztunk, Picard. Csupa fül vagyok, meséljen nekem errôl a kalandjáról.";
			link.l1.go = "rocur_30";
		break;
		
		case "rocur_30":
            dialog.text = "Már elmondtam Marcusnak, most én mondom el neked. Amikor rabszolga voltam a maracaibói ültetvényen, tanultam valamit a spanyoloktól. Elég beszédesek, ha részegek... Figyelj, a Maracaibo öböltôl délkeletre van egy kis falu. Két hegy között van elrejtve, mélyen a dzsungelben. Pokoli neve van: Santiago-de-Los-Caballeros-de-Merida. Nevezzük Meridának\nNem hangzik még túl érdekesen, mi? A falut körülvevô hegyek drágakövekben gazdagnak bizonyultak. Smaragdok, opálok és legendás tûzopálok\nAmennyire én tudom, Merida telepesei nem szóltak a fôkormányzónak ezekrôl a drágakövekrôl. Bármilyen hamar meg fogja tudni, ezért érdemes még a spanyol gyarmati tisztek érkezése elôtt ellátogatni Meridába.";
			link.l1 = "Ki akarod fosztani a települést?";
			link.l1.go = "rocur_31";
		break;
		
		case "rocur_31":
            dialog.text = "Pontosan. Elveszett a dzsungel és a hegyek között, egy kis helyôrséggel - könnyû fohász egy korzikai egységnek. Ráadásul messze vannak a tengertôl, nem számítanak arra, hogy bárki megtámadja ôket, csak a lándzsás és íjas vademberek.";
			link.l1 = "Mennyire vagy biztos benne, hogy a településen valóban vannak drágakövek?";
			link.l1.go = "rocur_32";
		break;
		
		case "rocur_32":
            dialog.text = "Ha kalandjainknak hamis nyomra bukkanunk, magam is a hajótokon fogok szolgálni tisztként vagy matrózként, fedélzetet takarítok és számtalan partraszállásban harcolok, amíg adósságom nektek és Marcusnak el nem törlôdik.";
			link.l1 = "Értem... Rendben, tudod, hogyan juthatsz el Meridába?";
			link.l1.go = "rocur_33";
		break;
		
		case "rocur_33":
            dialog.text = "Természetesen nem ismerem a pontos utat a dzsungeleken keresztül, de majd felfogadunk egy vezetôt az indiánoktól. A Maracaibo-tótól délre kell leszállnunk, keresnünk kell egy indián falut, és megkeresni azokat, akik tudják, hogyan juthatunk oda.";
			link.l1 = "...";
			link.l1.go = "rocur_34";
		break;
		
		case "rocur_34":
            DialogExit();
			sld = characterFromId("Terrax");
			sld.Dialog.currentnode = "mtraxx_38";
			LAi_SetActorType(sld);
			LAi_ActorSetHuberMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "rocur_35":
            dialog.text = "Kapitány mélységesen sajnálom a nyelvezetemet, de mi a faszért nem vagyunk még Meridában? Mi? Köpött a közös ügyünkre! A kobold és én nélküled megyünk. Mindent megmagyarázok Tyrexnek, neked pedig menned kell. Tessék, itt van 50 000 pezó a segítségedért Maracaibóban, kölcsönkértem a barátaimtól. Isten veled, te átkozott szégyen, én jobbat gondoltam rólad.";
			link.l1 = "Hmm... Sajnálom.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_MeridaTimeOverFail");
		break;
		
		case "rocur_36":
            dialog.text = "Itt is vagyunk. Dzsungel elôttünk. Elôször is, meg kell találnunk egy indián falut, és kérdezôsködni egy vezetô után.";
			link.l1 = "Gyerünk, csináljuk. Luke, van valami mondanivalód... vagy esetleg egy tanácsod?";
			link.l1.go = "rocur_37";
		break;
		
		case "rocur_37":
            DialogExit();
			sld = characterFromId("Lepricon");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "rocur_38":
            dialog.text = "Merida helyôrségének vége. Nem számítok komolyabb ellenállásra a faluban. Gyerünk, indulás!";
			link.l1 = "Töltés!!!";
			link.l1.go = "rocur_39";
		break;
		
		case "rocur_39":
            DialogExit();
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("Merida_ExitTown", "reload1_back", true);
			pchar.quest.mtraxx_merida_town.win_condition.l1 = "location";
			pchar.quest.mtraxx_merida_town.win_condition.l1.location = "Merida_Town";
			pchar.quest.mtraxx_merida_town.function = "Mtraxx_MeridaTown";
			Mtraxx_MeridaCheckOurWarriors();
			AddQuestRecord("Roger_5", "16");
		break;
		
		case "rocur_40":
            dialog.text = "Kész van! Nem maradtak hôsök. Most már beszélnünk kellene ennek a 'városnak a kormányzójával'. remélem, hogy meggyôzhetô típus.";
			link.l1 = "Egyetértek, gyôzzük meg ôt!... Jean! Kövessetek!";
			link.l1.go = "rocur_41";
		break;
		
		case "rocur_41":
            DialogExit();
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("Merida_Town", "gate_back", true);
			pchar.quest.mtraxx_merida_townhall.win_condition.l1 = "location";
			pchar.quest.mtraxx_merida_townhall.win_condition.l1.location = "Merida_townhall";
			pchar.quest.mtraxx_merida_townhall.function = "Mtraxx_MeridaTownhall";
			sld = characterFromId("Mrt_Rocur");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			sld = characterFromId("Lepricon");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			AddQuestRecord("Roger_5", "17");
		break;
		
	case "rocur_42": //злой вариант
            DialogExit();
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("Merida_Town", "reload3", true); 
			pchar.questTemp.Mtraxx = "merida_success";
			pchar.quest.mtraxx_merida_exit.win_condition.l1 = "location";
			pchar.quest.mtraxx_merida_exit.win_condition.l1.location = "Merida_Town";
			pchar.quest.mtraxx_merida_exit.function = "Mtraxx_MeridaExit";
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			
			sld = characterFromId("Merida_Head");
			LAi_SetActorType(sld);
			
			pchar.questTemp.Mtraxx_MeridaZloVariant = true;
			
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "reload", "reload1", "Mtraxx_MeridaExitResidensia", -1);
		break;
		
		case "rocur_43": //мирный вариант
            DialogExit();
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("Merida_Town", "reload3", true); 
			pchar.questTemp.Mtraxx = "merida_success";
			pchar.quest.mtraxx_merida_exit.win_condition.l1 = "location";
			pchar.quest.mtraxx_merida_exit.win_condition.l1.location = "Merida_Town";
			pchar.quest.mtraxx_merida_exit.function = "Mtraxx_MeridaExit";
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			
			sld = characterFromId("Merida_Head");
			LAi_SetActorType(sld);
			
			sld = characterFromId("Mrt_Rocur");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "goto", "goto2", "Mtraxx_MeridaGiveJewelry", -1);
			
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "reload", "reload1", "Mtraxx_MeridaExitResidensia", -1);
		break;
		
		case "rocur_44":
			if (CheckAttribute(pchar, "questTemp.Mtraxx_MeridaKamushki"))
			{
            	dialog.text = "Szép munka, "+pchar.name+"! Ideje felosztani a részvényeket. Már megvannak a számok. A ládában majdnem 2000 drágakô volt: 1560 smaragd, 1032 opál és 363 tûzopál. A te részed a harmadik: 350 smaragd, 244 opál és 63 tûzopál. Tessék, vedd el ôket.";
            }
            else
           	{
           	dialog.text = "Szép munka, "+pchar.name+"! Ideje felosztani a részvényeket. Már megvannak a számok. A ládában majdnem 2000 drágakô volt: 1050 smaragd, 732 opál és 189 tûzopál. A te részed a harmadik: 350 smaragd, 244 opál és 63 tûzopál. Tessék, vedd el ôket.";
           	}
			link.l1 = "Nagyszerû!";
			link.l1.go = "rocur_45";
		break;
		
		case "rocur_45":
			PlaySound("interface\important_item.wav");
			if (CheckAttribute(pchar, "questTemp.Mtraxx_MeridaKamushki"))
			{
				TakeNItems(pchar, "jewelry4", 520);
				TakeNItems(pchar, "jewelry16", 334);
				TakeNItems(pchar, "jewelry14", 121);
			}
			else
			{
				TakeNItems(pchar, "jewelry4", 350);
				TakeNItems(pchar, "jewelry16", 244);
				TakeNItems(pchar, "jewelry14", 63);
			}
            dialog.text = "Most pedig beszéljünk arról, mivel tartozom neked a megmentésemért. Úgy tudom, komoly kiadásai voltak. Milyen kártérítést tartana méltányosnak? A drágakövekbôl származó részembôl fizetek.";
			link.l1 = "A te részed harmada is elég lesz. Neked is szükséged van pénzre - hogy hajót vegyél és elláss egy hajót, hogy kifizesd a legénységedet...";
			link.l1.go = "rocur_46";
		break;
		
		case "rocur_46":
			PlaySound("interface\important_item.wav");
			if (CheckAttribute(pchar, "questTemp.Mtraxx_MeridaKamushki"))
			{
				TakeNItems(pchar, "jewelry4", 173);
				TakeNItems(pchar, "jewelry16", 111);
				TakeNItems(pchar, "jewelry14", 40);
			}
			else
			{
				TakeNItems(pchar, "jewelry4", 116);
				TakeNItems(pchar, "jewelry16", 81);
				TakeNItems(pchar, "jewelry14", 21);
			}
            dialog.text = "Köszönöm, barátom! Azt hittem, hogy nem kevesebbet kérsz, mint a felét. Most tényleg pénzre van szükségem. Tessék, fogd a drágaköveket.";
			link.l1 = "Micsoda rajtaütés Jean! Irány Hispaniola, Tyrex.";
			link.l1.go = "rocur_47";
		break;
		
		case "rocur_47":
            DialogExit();
			chrDisableReloadToLocation = false;
			pchar.questTemp.Mtraxx = "merida_gohome";
			AddQuestRecord("Roger_5", "18");
			sld = characterFromId("Mrt_Rocur");
			LAi_SetWarriorType(sld);
			LAi_CharacterDisableDialog(sld); // релиз-правка
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, false);
			sld = characterFromId("Lepricon");
			LAi_SetWarriorType(sld);
			LAi_CharacterDisableDialog(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, false);
			sld = characterFromId("Terrax");
			sld.dialog.currentnode = "mtraxx_40";
			pchar.quest.mtraxx_merida_lavega.win_condition.l1 = "location";
			pchar.quest.mtraxx_merida_lavega.win_condition.l1.location = "Hispaniola1";
			pchar.quest.mtraxx_merida_lavega.function = "Mtraxx_IgnasioKitty";
			// таймер на доплыть домой 40 дней
			SetFunctionTimerCondition("Mtraxx_MeridaReturnLate", 0, 0, 40, false);
			DeleteAttribute(pchar, "GenQuest.HunterLongPause");
		break;
		
		case "rocur_48":
            dialog.text = "Ó, micsoda találkozó! Örülök, hogy találkoztunk, "+pchar.name+". Hogy van?";
			link.l1 = "Egész jól. Nemrég találtam meg Vörös Farkas kincseit. Most Martinique-ra megyünk, hogy találkozzunk egy közös barátunkkal. Akarod látni Tyrexet?";
			link.l1.go = "rocur_49";
		break;
		
		case "rocur_49":
            dialog.text = "Aha. Beszélni akarok vele Pasquale Lavoisier-rôl. Marcus küldött ahhoz a félig bandita, félig kereskedôhöz. Megtettem, amit kért, ô pedig valami szarral fizetett, azt állítva, hogy rohadt jó fizetség. Legszívesebben ott helyben kinyírtam volna a köcsögöt, ahol állt, de Marcus megkért, hogy bánjak vele tisztelettel... aztán majd ô elintézi ezt a bajt.";
			link.l1 = "Sajnálom, de Marcus nem tesz semmit. Négyszemû üzletel vele.";
			link.l1.go = "rocur_50";
		break;
		
		case "rocur_50":
            dialog.text = "Mi a fasz?";
			link.l1 = "Igen, de én nem szóltam neked errôl, rendben? Lavoisier nem is olyan régen engem is átvert. Tyrex megkért, hogy segítsek neki, ahogy téged is megkért. Isla Tesoro-ban figyelmeztettek, hogy a Négyszemûvel való szembefordulás ugyanaz, mint Marcusszal. Szóval azt javaslom, felejtsd el ezt az egészet. Nem te vagy ebben sem az elsô, sem az utolsó.";
			link.l1.go = "rocur_51";
		break;
		
		case "rocur_51":
            dialog.text = "Értem. Akkor téged is átvertek azok ketten?";
			link.l1 = "Nos, igen. Arra gondoltam, hogy a négyszemûnek is okozok némi gondot, mielôtt többet megtudok róla. Nem éri meg.";
			link.l1.go = "rocur_52";
		break;
		
		case "rocur_52":
            dialog.text = "Megpróbálnád visszafizetni a szemétládának, ha tudnád, hogy soha senki nem fog rájönni?";
			link.l1 = "Ha! Hát persze, hogy nem! Bár nem tudom, hogyan. Támadja Lavoisier fuvoláit, és egy fényes napon a matrózai berúgnak, és mindent kifecsegnek. Nem tudod, hogy mûködik ez?";
			link.l1.go = "rocur_53";
		break;
		
		case "rocur_53":
            dialog.text = "Most Martinique felé tartasz? Mikor érkezel újra La Vegába?";
			link.l1 = "Marcus három hetet adott nekem.";
			link.l1.go = "rocur_54";
		break;
		
		case "rocur_54":
            dialog.text = "Próbálj meg két hét alatt odaérni. Átgondolom... Keress meg a Gonaives-öbölben 14 nap múlva. Menj egyenesen oda, és ne lépj be La Vegába.";
			link.l1 = "Látom, hogy készülsz valamire, ha-ha. Hát jó. Megpróbálom.";
			link.l1.go = "rocur_55";
		break;
		
		case "rocur_55":
            dialog.text = "Jobb, ha megpróbálod. Viszlát!";
			link.l1 = "...";
			link.l1.go = "rocur_56";
		break;
		
		case "rocur_56":
            DialogExit();
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload3", "none", "", "", "", 10.0);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			ReOpenQuestHeader("Roger_4");
			AddQuestRecord("Roger_4", "11");
			pchar.quest.mtraxx_pasq_gonaiv.win_condition.l1 = "Timer";
			pchar.quest.mtraxx_pasq_gonaiv.win_condition.l1.date.hour  = 1.0;
			pchar.quest.mtraxx_pasq_gonaiv.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 14);
			pchar.quest.mtraxx_pasq_gonaiv.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 14);
			pchar.quest.mtraxx_pasq_gonaiv.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 14);
			pchar.quest.mtraxx_pasq_gonaiv.win_condition.l2 = "location";
			pchar.quest.mtraxx_pasq_gonaiv.win_condition.l2.location = "Shore34";
			pchar.quest.mtraxx_pasq_gonaiv.function = "Mtraxx_PasqualeJanGonaiv";
			SetFunctionTimerCondition("Mtraxx_PasqualeJanTimer", 0, 0, 10, false); // правки прогона 3
			SetFunctionTimerCondition("Mtraxx_PasqualeJanTimeOver", 0, 0, 15, false);
			if(bImCasual) NewGameTip("Felfedezô mód: az idôzítô nincs kikapcsolva. Tartsd be a határidôt!");
			pchar.questTemp.Mtraxx.Pasquale.Grabbing = "true";
		break;
		
		case "rocur_57":
			if (pchar.location.from_sea != "Shore34")
			{
				dialog.text = RandSwear()+"Hol van a hajód? La Vegáról érkezett ide? Merde! Arra kértem, hogy észrevétlenül és titokban jöjjön ide. A tervemnek annyi. A fenébe!";
				link.l1 = "Hm...";
				link.l1.go = "rocur_58";
			}
			if (GetOfficersQuantity(pchar) > 0)
			{
				dialog.text = "Tessék , "+pchar.name+". Jó, hogy itt vagy. Küldd vissza a társaidat a hajóra. Ez egy magánbeszélgetés.";
				link.l1 = "Rendben.";
				link.l1.go = "rocur_59";
			}
			else
			{
				dialog.text = "Tessék , "+pchar.name+". Jó, hogy itt vagy.  Van egy üzletem a számodra. Készen állsz meghallgatni?";
				link.l1 = "Persze!";
				link.l1.go = "rocur_61";
			}
		break;
		
		case "rocur_58":
            DialogExit();
			Group_DelCharacter("RocurSeaGroup", "Mrt_Rocur");
			Group_DeleteGroup("RocurSeaGroup");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "sea", "none", "", "", "OpenTheDoors", 10.0);
			AddQuestRecord("Roger_4", "14");
			CloseQuestHeader("Roger_4");
		break;
		
		case "rocur_59":
            DialogExit();
			LAi_SetStayType(npchar);
			npchar.dialog.currentnode = "rocur_60";
		break;
		
		case "rocur_60":
            if (GetOfficersQuantity(pchar) > 0)
			{
				dialog.text = "Már mondtam - küldje el a tisztjeit!";
				link.l1 = "Igen-igen, értem.";
				link.l1.go = "rocur_59";
			}
			else
			{
				dialog.text = "Remek. Most már szabadon beszélhetünk. Van egy üzletem a számodra. Készen állsz meghallgatni?";
				link.l1 = "Persze!";
				link.l1.go = "rocur_61";
			}
		break;
		
		case "rocur_61":
            dialog.text = "Jól ismeri La Vegát?";
			link.l1 = "Hát... Azt hiszem, igen. Miért kérdezed?";
			link.l1.go = "rocur_62";
			npchar.greeting = "";
		break;
		
		case "rocur_62":
            dialog.text = "Észrevetted már a boltos házat a helyi boltból jobbra? Az egyetlen nagy ház a kunyhók között.";
			link.l1 = "A mindig zárva lévô? Igen, láttam. Mi van vele?";
			link.l1.go = "rocur_63";
		break;
		
		case "rocur_63":
            dialog.text = "Szépen észrevetted - mindig zárva van. Amíg ön Martinique-on volt küldetésen, közös barátunk, Lavoisier három napig itt tartózkodott Marcus Tyrex vendégeként. Ebben a házban töltötték az idejüket rumot iszogatva és szórakozva.";
			link.l1 = "Hm...";
			link.l1.go = "rocur_64";
		break;
		
		case "rocur_64":
            dialog.text = "Aztán Lavoisier emberei néhány dobozt és csomagot hurcoltak be a házba. Aztán elment. Ami Marcust illeti, minden nap néhány órát töltött ott.";
			link.l1 = "Valami ötlet?";
			link.l1.go = "rocur_65";
		break;
		
		case "rocur_65":
            dialog.text = "Milyen javaslatok? Biztos vagyok benne, hogy ez a ház Lavoisier bázisa lehet La Vegában. Az ablakon keresztül nem sokat láttam, de vannak ott tárolt áruk. Úgy gondolom, hogy a négyszemûnek megvan a pénze, hogy visszafizesse, amivel tartozik nekünk.";
			link.l1 = "Nocsak, nocsak... Be akarsz törni? Mi van a zárt ajtóval? Nehéz és masszív, kizárt, hogy csendben betörjünk.";
			link.l1.go = "rocur_66";
		break;
		
		case "rocur_66":
            dialog.text = ""+pchar.name+", ...azt hiszed, hogy hülye vagyok? Már megoldottam a dolgot. A kulcsot a zár viaszmaszkjából készítettem. Elég sokba került, de ez az én problémám.";
			link.l1 = "Heh! Akkor miért vársz rám?";
			link.l1.go = "rocur_67";
		break;
		
		case "rocur_67":
            dialog.text = "Így biztonságosabb lesz, ráadásul te vagy az egyetlen, akiben megbízhatok. Egy fej jó, két fej jobb, és négy szem jobb, mint kettô.";
			link.l1 = "Hát igen, Lavoisier-t keresztezve annyi szemet vesz, amennyi neki van, ha-ha-ha-ha! De mi lesz Tyrexszel? Mi van, ha belép a házba, miközben Pasquale holmiját ellenôrizzük?";
			link.l1.go = "rocur_68";
		break;
		
		case "rocur_68":
            dialog.text = "Nem fog. Éjfélre mindig visszamegy a saját házába. Készen állsz a La Vegába menni jövô éjjel? Soha nem fogják észrevenni, hogy ki baszta el ôket: te még mindig Martinique-on vagy, én pedig egy hete elhagytam La Vegát.";
			link.l1 = "Szívesen megdugnám a négyszemû enculét. De mondd csak Jean, hogyan fogjuk a hordókat és a ládákat kivinni a házból?";
			link.l1.go = "rocur_69";
		break;
		
		case "rocur_69":
            dialog.text = "Biztos vagyok benne, hogy ott értékesebb dolgokat találunk, mint ládákat és hordókat áruval, amelyek sokkal könnyebbek lesznek. Szóval, benne vagy?";
			link.l1 = "A pokolba is, igen, benne vagyok!";
			link.l1.go = "rocur_70";
		break;
		
		case "rocur_70":
            dialog.text = "Remek, örülök, hogy nem tévedtem veled kapcsolatban. Most pihenjünk egy kicsit, éjfélkor indulunk La Vegába.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PasqualeNight");
		break;
		
		case "rocur_71":
            dialog.text = "Ideje indulni. Ki kéne rabolnunk ezt a rohadékot, és még hajnal elôtt eltûnni onnan.";
			link.l1 = "Elôre!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PasqualeNightMarch");
			SetLocationCapturedState("LaVega_town", true);
			LAi_LoginInCaptureTown(npchar, true);
		break;
		
		case "rocur_72":
            dialog.text = "Csitt... Most pedig induljatok, csendben, Pasquale házához. Kövessetek.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PasqualeNightToHouse");
		break;
		
		case "rocur_73":
            dialog.text = "Nézzétek ezt - mennyi cucc hever szanaszét. Kezdjük. Nézz meg egy ládát az ajtó mellett, majd menj fel az emeletre és foglalj el egy szobát. Én itt maradok: Ismerem az értéktárgyak elrejtésének trükkjeit a kacatok között. Tartsd nyitva a szemed és a füled, és maradj távol az ablakoktól.";
			link.l1 = "Rendben...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PasqualeNightInHouse");
		break;
		
		case "rocur_74":
            dialog.text = ""+pchar.name+", Mi van nálad? Valami érdekeset?";
			link.l1 = "Gyere és nézd meg. Ez itt valami.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PasqualeJanSeeGirl");
		break;
		
		case "rocur_75":
            dialog.text = "A francba! Most már értem, miért jön Tyrex minden nap erre a helyre. Ez nem csak a négyszemûek raktára, hanem egy bordélyház is.";
			link.l1 = "Úgy néz ki, mintha rabszolga lenne itt.";
			link.l1.go = "rocur_76";
		break;
		
		case "rocur_76":
            dialog.text = "Persze. Nézz csak rá - nyilvánvalóan egy kikötôi kurva... Balszerencsét hoz nekünk. Meg kell ölnünk.";
			link.l1 = "Tényleg meg kell ölnünk?";
			link.l1.go = "rocur_77";
		break;
		
		case "rocur_77":
            dialog.text = "Látta az arcunkat és hallotta a nevedet. Mindent el fog mondani Tyrexnek.";
			link.l1 = "Hm...";
			link.l1.go = "rocur_78";
		break;
		
		case "rocur_78":
            dialog.text = "A te döntésed. Az ô élete a tiédbe kerülhet.";
			link.l1 = "";
			link.l1.go = "rocur_79";
		break;
		
		case "rocur_79":
            DialogExit();
			sld = characterFromId("Mirabella");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "rocur_80":
            dialog.text = "Eszedbe se jusson megbízni ebben a szajhában. Holnap Tyrex mindent tudni fog. Akarsz egy fekete jelet kapni?";
			link.l1 = "Nem, nem akarom. És nem akarom megölni a szajhát - hasznát veszem. Velem jön.";
			link.l1.go = "rocur_81";
		break;
		
		case "rocur_81":
            dialog.text = "Ne légy idióta! El fog szökni, amint lehetôsége lesz rá. Nézd meg a homlokát, látod a bélyeget? Ô egy tolvaj.";
			link.l1 = "Hm. Valószínûleg igazad van, Jean. Rendben, végezz vele, és tûnjünk el innen.";
			link.l1.go = "rocur_82";
			link.l2 = "Nem tervezem, hogy a hajómon tartom. Van egy helyem a számára, ahonnan soha nem fog elszökni, és nincsenek fülek sem, amelyek meghallják a sikolyait. Ô is ott fogja folytatni a munkáját... Egy személyes kurva, ingyen, he-he!";
			link.l2.go = "rocur_84";
		break;
		
		case "rocur_82":
            DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "goto", "goto6", "", 5);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "goto", "goto7", "Mtraxx_PasqualeJanKillGirl", 5);
		break;
		
		case "rocur_83":
			ChangeCharacterComplexReputation(pchar, "nobility", -10);
            dialog.text = "Ennyi, most már kizárt, hogy bármit is mondjon Marcusnak...";
			link.l1 = "Szegény lány... hah hát ahogy mondani szokták, a szerencse szuka...";
			link.l1.go = "rocur_86";
		break;
		
		case "rocur_84":
            DialogExit();
			sld = characterFromId("Mirabella");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "rocur_85":
            dialog.text = "Ön egy kedves ember, "+pchar.name+". Miért akarod magadat vele zaklatni? Áh, mindegy, a te döntésed. Gondoskodj róla, hogy csendben legyen, amíg elmegyünk.";
			link.l1 = "Ha nem lesz az - halott.";
			link.l1.go = "rocur_86";
		break;
		
		case "rocur_86":
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Pasquale.Grabbing.Chest")) sTemp = "Egy kicsit. Egy láda tele dublonnal, egy marék rubin, Hispaniola térképe és némi rum.";
			else sTemp = "Semmi értékeset.";
            dialog.text = "Mit találtál?";
			link.l1 = sTemp;
			link.l1.go = "rocur_87";
		break;
		
		case "rocur_87":
			Log_Info("Két kincsgyûjteményt kaptál.");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "icollection", 2);
            dialog.text = "Több szerencsét az én oldalamon. Tessék, vedd el a részed. Soha nem tudnám mindet magammal vinni a partra. A négyszemûek teljes egészében kifizettek minket.";
			link.l1 = "Pompás! Szép munka, Jean!";
			link.l1.go = "rocur_88";
		break;
		
		case "rocur_88":
            dialog.text = "Most menjetek!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PasqualeNightOutHouse");
		break;
		
		case "rocur_89":
			PlaySound("VOICE\English\LE\Rocur\Rocur_04.wav");
            dialog.text = "Nagyszerû. Kész is van. Szép csendben. Most menjünk vissza a hajókhoz.";
			link.l1 = "Hah, jó ötlet.";
			link.l1.go = "rocur_89_1";
			//AddDialogExitQuestFunction("Mtraxx_PasqualeNightGulf");
		break;
		
		case "rocur_89_1":
			DialogExit();
			DoFunctionReloadToLocation("shore34", "goto", "goto13", "Mtraxx_PasqualeFinal");
		break;
		
		case "rocur_90":
			PlaySound("VOICE\English\LE\Rocur\Rocur_05.wav");
            dialog.text = "Nos, "+pchar.name+". Itt az ideje, hogy elváljanak útjaink. Nem vagyok biztos benne, hogy valaha is találkozunk még, de tudd, hogy öröm volt megismerni téged barátom.";
			link.l1 = "Ah, gyere most, gyakran fogunk találkozni La Vegában.";
			link.l1.go = "rocur_91";
			SetLocationCapturedState("LaVega_town", false);
			LAi_LoginInCaptureTown(npchar, false);
		break;
		
		case "rocur_91":
            dialog.text = "Nem. Végeztem Tyrexszel. Ez a Lavoisier-rel való balhé volt az utolsó csepp a pohárban.";
			link.l1 = "Hmm... Értem, csak felejtsd el. Megkaptuk, ami jogosan a miénk. Tyrex jövedelmezô nyomokat ad, nem igaz? Legutóbb több mint félmilliót kerestem Vörös Farkas kincsébôl.";
			link.l1.go = "rocur_92";
		break;
		
		case "rocur_92":
            dialog.text = "Mondd csak, sokat fáradoztál a megtalálásával?";
			link.l1 = "Hát... Nem volt könnyû. Rengeteget gondolkodtam, utaztam és harcoltam. Azt hiszem, megérte.";
			link.l1.go = "rocur_93";
		break;
		
		case "rocur_93":
            dialog.text = "Mennyit fizettél Tyrexnek?";
			link.l1 = "Egyharmadot.";
			link.l1.go = "rocur_94";
		break;
		
		case "rocur_94":
            dialog.text = "Mi volt az ô szerepe ebben az üzletben? Mit csinált pontosan Marcus?";
			link.l1 = "Hm... Ô adta nekem Vörös Farkas naplóját...";
			link.l1.go = "rocur_95";
		break;
		
		case "rocur_95":
            dialog.text = "És ez minden? Ez minden?";
			link.l1 = "Hát... Különben sosem tudtam volna meg Wulfric kapitányról...";
			link.l1.go = "rocur_96";
		break;
		
		case "rocur_96":
            dialog.text = ""+pchar.name+", nem látod, hogy Tyrex másokat kényszerít a piszkos munkára? Azt hiszed, hogy ô adna neked feladatot a kincs megtalálására, ha egyedül is meg tudná csinálni? A pokolba is, dehogy! Lefogadom, hogy elôször megpróbálta maga megcsinálni, és amikor elbaszta az egészet, téged hívott, hogy végezd el a munkát. És amíg te gondolkodtál, heteket töltöttél a tengeren, harcoltál és kockáztattad a saját életedet, addig ez a szemétláda az undorító négyszemû barátjával együtt a La Vegában dugta a kurvát. És ezért is kapott negyedmillió pezót. Csak úgy\nAzt hiszed, hogy a kutyáját, a koboldját küldte, hogy segítsen nekünk a Merida elleni rajtaütésünkben? Nem, biztos akart lenni abban, hogy az érdekeltségei biztonságban vannak. Mindent, amit Marcus egyedül is meg tud csinálni, azt meg is teszi, vagy egyedül, vagy Vágók, Kopaszok, Koboldok és más hülye idióták segítségével, akik fillérekért dolgoznak neki. Az olyan emberek, mint te és én, olyan nyomokat kapunk, amelyeket Marcus túl hülye ahhoz, hogy egyedül végrehajtsa\nEmlékszel minden feladatra, amit neki végeztél? Számold meg, mennyit keresett rajtad. Elegem van ebbôl. Most már van pénzem, egy remek corvette-em és hûséges legénységem... mostantól szabadúszó vagyok. Jamaikába megyek, talán ott kapok egy hadlevéllel.";
			link.l1 = "Nem hiszem, hogy igazad van Tyrexszel kapcsolatban... De sok szerencsét kívánok Jean! Remélem sikerrel jársz majd Jamaikában.";
			link.l1.go = "rocur_97";
		break;
		
		case "rocur_97":
            dialog.text = "Úgy lesz. Sok szerencsét neked is, és gondolj arra, amit mondtam. Marcus' bitchnek lenni nem a legjobb szerep számodra, tudom, hogy sokkal többre vagy képes. Nos... viszlát testvér! Isten éltessen!";
			link.l1 = "Jó vadászatot, Jean!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PasqualeAddComplete");
		break;
		
		case "rocur_98":
            dialog.text = ""+pchar.name+", Mondd csak, hogyan töltöttünk ennyi idôt a dzsungelben? A tervemnek annyi. Eh... Viszlát, haver...";
			link.l1 = "Heh...";
			link.l1.go = "rocur_99";
		break;
		
		case "rocur_99":
            DialogExit();
		    LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", 10.0);
			sld.lifeday = 0;
			Group_DeleteGroup("RocurSeaGroup");
			AddQuestRecord("Roger_4", "18");
			CloseQuestHeader("Roger_4");
		break;
		
		case "rocur_100":
			if (CheckAttribute(pchar, "questTemp.Mtraxx_MeridaZloVariant"))
			{
				dialog.text = "Ideje indulni, fiúk. A fenébe, Herceg, megleptél. Felgyújtottál egy egész várost, de nem voltál hajlandó bepiszkolni a kezed, amikor fontos volt.";
				link.l1 = "Nem én rendeltem el a város felgyújtását!";
				link.l1.go = "rocur_101";
			}
			else
			{
				dialog.text = "Ideje indulni, fiúk. Lucas, kihagytad. A herceg ragyogóan kezelte a dolgot - és jó hasznot hozott!";
				link.l1 = "Mi lesz a várossal, Szépfiú?! A szavamat adtam!";
				link.l1.go = "rocur_102";
			}
			sld = CharacterFromID("Lepricon");
			CharacterTurnToLoc(sld, "reload", "reload3");
		break;
		
		case "rocur_101":
            dialog.text = "Legalább nem próbáltad megmenteni. Különben az embereink elôbb kibeleztek volna téged. Nehéz napjuk volt. Megérdemelték, hogy kiengedjék a gôzt. Majd hozzászoksz. Minden adottságod megvan hozzá.";
			link.l1 = "Köszönöm a tanácsot, de nem emlékszem, hogy kértem volna. Gyerünk, menjünk.";
			link.l1.go = "rocur_103";
		break;
		
		case "rocur_102":
            dialog.text = " Azt hittem, viccelsz. Nos... túl elhamarkodott voltál. A városnak vége. Mindig így van ez, amikor a Parti Testvérek munkához látnak. Majd hozzászoksz.";
			link.l1 = "Nem vagyok benne biztos, hogy meg fogom. Rendben, menjünk.";
			link.l1.go = "rocur_103";
		break;
		
		case "rocur_103":
            DialogExit();
			LAi_SetPlayerType(pchar);
			DeleteAttribute(pchar, "questTemp.lockedMusic");
			EndQuestMovie();
			locCameraTarget(PChar);
			locCameraFollow();
			sld = characterFromId("Tagofa");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			Mtraxx_MeridaCheckOurWarriors();
			AddQuestRecord("Roger_5", "12");
		break;
		
		case "rocur_104":
            dialog.text = "Haver... mi volt ez az elôbb?";
			link.l1 = "Mi az, nem érted? Megvettelek. Egyszer azt mondtad, hogy hozzáférhetek a spanyolokhoz, úgyhogy éltem vele.";
			link.l1.go = "rocur_105";
		break;
		
		case "rocur_105":
            dialog.text = "Megértettem - nem vagyok hülye. De nem egy másik terven dolgoztunk?";
			link.l1 = "Nos, Cutlass és én úgy gondoltuk, hogy nem lenne helyes, ha egy felkelés vagy üldözés során holtan végeznéd, ezért úgy döntöttünk, hogy megveszünk téged.";
			link.l1.go = "rocur_106";
		break;
		
		case "rocur_106":
            dialog.text = "Hah, ne sértegess! Elvégre én vagyok Terrax egyik kapitánya. Tudom, hogy kell tartani a pengét.";
			link.l1 = "Ebben nem kételkedem, de komolyan felháborít, hogy szabad vagy?";
			link.l1.go = "rocur_107";
		break;
		
		case "rocur_107":
            dialog.text = "Nem, nem - hálás vagyok. Csak... nem volt egy kicsit sok az a sok arany? Rosszul vagyok, ha csak rágondolok. Az ültetvény viszont olyan fényesnek tûnt, mint egy csiszolt ezüsttálca.";
			link.l1 = "Igen, 'Az évszázad üzlete,' deed. Kicsit csíp, persze. De az idô drágább, mint az arany, Jean. Pisztolyok és gyógyszerek keresése mindannyiuknak...";
			link.l1.go = "rocur_108";
		break;
		
		case "rocur_108":
            dialog.text = "Hálás vagyok, de haver, te egy bolond vagy... - Ne vedd sértésnek. Mondtam, hogy a fiúk nem bánnak jól a karddal. De bárki meg tudja húzni a ravaszt. Bármilyen pisztolyt és gyógyszert hozhattál volna a raktérbôl, ahogy a baltákat és a fejszéket is - nem válogatnak.";
			link.l1 = "Hmm, ôszintén szólva, erre nem is gondoltam... Mindegy, menjünk - Cutlass valószínûleg kezd türelmetlenkedni.";
			link.l1.go = "rocur_109";
		break;
		
		case "rocur_109":
			DialogExit();
			DoFunctionReloadToLocation("Shore37", "goto", "goto6", "Mtraxx_PlantPlantVykup_3");
		break;
		
		// Люк Лепрекон
		case "lepricon":
            dialog.text = "Üdvözlet, kapitány "+GetFullName(pchar)+". Luke, a kobold áll a szolgálatodra! Azt mondták, hogy Dél-Main dzsungelébe megyünk.";
			link.l1 = "Pontosan. Szálljatok be a hosszú csónakokba, azonnal indulunk.";
			link.l1.go = "lepricon_1";
		break;
		
		case "lepricon_1":
            dialog.text = "Hagyja, hogy egy öreg kalóz adjon egy tanácsot, kapitány. Mivel a Selva felé tartunk - biztosan találkozunk majd az indiánokkal. Vigyél magaddal ajándékot nekik. Az indián harcosok imádják a szép pisztolyokat, különösen a párbajpisztolyokat. Szeretik az iránytûket és a kémszemüvegeket is. Varázstárgyként kezelik ôket\nA nôik az olcsó ékszereket és csecsebecséket, például a tükröket és a kagylókat kedvelik. Ha harcba keveredünk velük, használjunk harsonákat és arquebusokat: a grabancslövés általában nagyon jó a páncélt nem viselô ellenségek ellen. Ami magát a települést illeti, olyan fegyvereket javaslok, amelyek képesek papírkartácsot használni.";
			link.l1 = "Nagyon jó, Luke. A szavaidat tudomásul vettem. Üdvözöllek a fedélzeten.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_MeridaSail");
		break;
		
		case "lepricon_2":
            dialog.text = "Találkozz a törzsfônökkel, amint a faluba érünk. És hozzatok ajándékokat, különben nincs értelme. Feltétlenül kérdezz meg valakit a népe közül, hogy tud-e titkos átjárókról az elôtted elterülô dzsungelben, és kérdezd meg azokat, akik nem félnek az utazástól. Én is veletek tartok, szóljatok hozzám, ha bármilyen nehézségbe ütköznétek.";
			link.l1 = "Gyerünk! Jean, Luke - kövessetek!";
			link.l1.go = "exit";
			npchar.greeting = "Lepricon_02";
			AddDialogExitQuestFunction("Mtraxx_MeridaSeekVillage");
		break;
		
		case "lepricon_3":
            dialog.text = "Van kérdés, kapitány?";
			link.l1 = "Egyelôre semmi, Luke.";
			link.l1.go = "lepricon_3x";
			if (pchar.questTemp.Mtraxx == "merida_advice")
			{
				link.l1 = "Igen! Beszéltem a törzsfônökükkel, megajándékoztam, és késôbb összehívta a rézbôrûeket egy találkozóra. Vannak közöttük olyanok, akik tudják, hogyan juthatnak el Meridába, de senki sem akar menni - félnek egy másik törzstôl, a capongoktól. Azok szarrá rémítik a helyieket. A rézbôrû fattyú azt állítja, hogy nincs esélyünk egyedül megtalálni az utat, és hogy nincs olyan vezetô, akit felfogadhatnánk. Akkor most mit csináljunk, mi?!";
				link.l1.go = "lepricon_4";
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Merida.Potion") && GetCharacterItem(pchar, "potion3") >= 12)
			{
				link.l2 = "Van nálam ellenszer.";
				if (GetCharacterItem(pchar, "potion3") > 42) link.l2.go = "lepricon_7";
				else link.l2.go = "lepricon_6";
			}
		break;
		
		case "lepricon_3x":
           DialogExit();
		   npchar.dialog.currentnode = "lepricon_3";
		break;
		
		case "lepricon_4":
            dialog.text = "Hmm, értem... Kapitány, tudnia kell, hogy a gyávaságot gyakran legyôzi a kapzsiság. Ígérjen olyan nagylelkû jutalmat, hogy az ember elvállalja a munkát... Tudja, mit? Próbáljon meg egy sokkal ravaszabb lehetôséget - a nôiket. Ajándékozza meg ôket, és kérdezzen az embereikrôl, és jó eséllyel megtalálja a vezetôt, akire szükségünk van. Ígérj neki egy halom gyöngyöt és tükröt a férje segítségéért. Légy nagylelkû és ígérj sokat, gyôzd meg ôket.";
			link.l1 = "Heh! Hát a legkevesebb, amit tehetek, hogy megpróbálom, bár nem vagyok benne biztos, hogy sikerülni fog...";
			link.l1.go = "lepricon_5_1";
			DelLandQuestMark(npchar);
		break;
		
		case "lepricon_5_1":
            dialog.text = "Hát, van még egy lehetôség... De nem éppen egy nagyszerû, ha érted, mire gondolok.";
			link.l1 = "Másik lehetôség? Adja rám! Nem vagyok túl lelkes ahhoz, hogy az indiai nôkhöz trappoljak, és könyörögjek nekik, hogy gyôzzék meg a férjeiket, hogy csatlakozzanak hozzánk.";
			link.l1.go = "lepricon_5_2";
		break;
		
		case "lepricon_5_2":
            dialog.text = "Ez a lehetôség egyidôs az idôvel. Mutasd meg nekik, hogy jobban kell félniük tôled, mint a Kapongoktól. Tudod... Elmondhatnád a fônöknek, hogy a kalózaid mit tehetnek a falu összes nôjével, különösen a feleségével és a lányaival. Még a kínzással is megfenyegethetnéd ôket... Mindenesetre biztos vagyok benne, hogy kitalálsz valamit, amivel ráveheted ezeket az indiánokat, hogy féljenek tôled. Én személy szerint nem vagyok híve ennek az útvonalnak, és ennek megvan az oka.";
			link.l1 = "Okok? Például? Szerintem ez egy elég hatékony és egyszerû megoldásnak tûnik.";
			link.l1.go = "lepricon_5_3";
		break;
		
		case "lepricon_5_3":
            dialog.text = "Elôször is, utána nem leszünk a város sztárjai. Lehet, hogy csapdába sétálunk, vagy más kellemetlen helyzetbe kerülünk. Másodszor pedig, nos... egyszerûen nem érzem helyesnek. Egy dolog fegyveres ellenfeleket kiiktatni, de teljesen más dolog nôket fenyegetni. Azt javaslom, hogy találjunk egy módot, hogy az indiánokat... diplomatikusabban kezeljük.";
			link.l1 = "Értem, majd átgondolom a dolgot. Talán megpróbálok gyöngyökkel udvarolni egy hölgynek... Vagy talán kitalálok valami fantáziadús kínzási módot a fônök lányainak, haha!";
			link.l1.go = "lepricon_5";
		break;
		
		case "lepricon_5":
            dialog.text = "Még egy dolog kapitány, a fônök szerint lehet, hogy egy ellenséges indián törzzsel fogunk találkozni a dzsungelben, nagyon valószínû, hogy csak egy kis csapat kannibál, de jobb félni, mint megijedni. Ha harcias törzsrôl van szó, megmérgezik a fegyvereiket, ezért gondoskodjon arról, hogy az emberei rendelkezzenek ellenszerekkel\nMi és az embereim mindig rengeteg bájitalt tartunk magunknál. Ami a kalózokat illeti... Csak hozzátok el nekem az ellenszereket, és én majd szétosztom ôket az embereitek között. Legalább egy tucat bájitalra van szükségem ehhez. Hozz magadnak és a tisztjeidnek is.";
			link.l1 = "Rendben. Hozom az ellenszereket.";
			link.l1.go = "lepricon_5x";
		break;
		
		case "lepricon_5x":
           DialogExit();
		   npchar.dialog.currentnode = "lepricon_3";
		   pchar.questTemp.Mtraxx = "merida_advice2";
		   pchar.questTemp.Mtraxx.Merida.Women = "true";
		   pchar.questTemp.Mtraxx.Merida.Potion = "true";
		   AddQuestRecord("Roger_5", "8");
		   sld = characterFromId("Hayamee");
		   LAi_CharacterEnableDialog(sld);
		   AddLandQuestMark(sld, "questmarkmain");
		  // LocatorReloadEnterDisable("Shore_ship3", "boat", false); 
		   bQuestDisableMapEnter = false;
		   DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");// выпустим в море
		   SetFunctionTimerCondition("Mtraxx_MeridaPotionLate", 0, 0, 10, false); // таймер, чтобы не ходил долго
		break;
		
		case "lepricon_6":
			i = GetCharacterItem(pchar, "potion3");
			RemoveItems(pchar, "potion3", i);
			pchar.questTemp.Mtraxx.Merida.Antidote = i;
            dialog.text = "Rendben. Add ide ôket. A többit majd én elintézem.";
			link.l1 = "Így ni...";
			link.l1.go = "lepricon_8";
		break;
		
		case "lepricon_7":
			RemoveItems(pchar, "potion3", 42);
			pchar.questTemp.Mtraxx.Merida.Antidote = 42;
            dialog.text = "Negyvenkét fôzet elég lesz. A többit tartsd meg magadnak.";
			link.l1 = "Rendben...";
			link.l1.go = "lepricon_8";
		break;
		
		case "lepricon_8":
            DialogExit();
		    npchar.dialog.currentnode = "lepricon_3";
			DeleteAttribute(pchar, "questTemp.Mtraxx.Merida.Potion");
		break;
		
		case "lepricon_9":
            dialog.text = "Kapitány, az indiánjaid - Hayami és Tagofa már túl régóta várták, hogy átadd a nekik ígért ajándékokat, és elmentek egy másik faluba táncolni és kasheerit inni. Van egy olyan érzésem, hogy az önök módszere nem fog nekünk jót tenni. Sajnálom, de te ebbôl kimaradsz. Picard fogja vezetni az expedíciót.";
			link.l1 = "Akkor csesszék meg mindannyian!";
			link.l1.go = "exit";
			AddQuestRecord("Roger_5", "19");
			AddDialogExitQuestFunction("Mtraxx_MeridaHayameeFail");
		break;
		
		case "lepricon_10":
            dialog.text = "Kapitány, mi a fene? Túl sok idôt vesztettünk a semmiért! Van egy olyan érzésem, hogy a maga módszere nem vezet jóra. Sajnálom, de maga kimarad ebbôl az egészbôl. Picard fogja vezetni az expedíciót.";
			link.l1 = "Akkor csesszék meg mindannyian!";
			link.l1.go = "exit";
			AddQuestRecord("Roger_5", "20");
			AddDialogExitQuestFunction("Mtraxx_MeridaHayameeFail");
		break;
		
		case "lepricon_11":
            dialog.text = "Kapitány, mi a fene? Tíz napja volt, hogy bôrt és deszkákat találjon. Maracaibo városa nincs messze innen! Az az érzésem, hogy a maga üzleti módszere nem fog nekünk jót tenni. Sajnálom, de önöknek ebbôl ki kell szállniuk. Picard fogja vezetni az expedíciót.";
			link.l1 = "Akkor csesszék meg mindannyian!";
			link.l1.go = "exit";
			AddQuestRecord("Roger_5", "20");
			AddDialogExitQuestFunction("Mtraxx_MeridaHayameeFail");
		break;
		
		case "lepricon_12":
            dialog.text = "Kapitány, sajnálom, de nekem már régen La Vegában kellett volna lennem, ahogy önnek is. Biztosan elfelejtett engem és Marcust. Mindenesetre, én most elmegyek. Folytassa, amit csinál, én pedig mindent elmagyarázok Marcusnak. Viszlát, kár, jobbat gondoltam rólad.";
			link.l1 = "Hmph...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_MeridaReturnFail");
		break;
		
		case "lepricon_13":
			PlaySound("VOICE\English\LE\Leprikon\Lepricon_03.wav");
            dialog.text = "Szóval, ha jól értem, összevesztetek. Nem sikerült megosztani a zsákmányt, igaz, Charlie Prince?";
			link.l1 = "Leprechaun? Hát itt vagy... Nem nagy meglepetés. Igen, a kapzsi fattyúk leköpték a kódot, és megpróbáltak megölni.";
			link.l1.go = "lepricon_14";
			QuestPointerDelLoc("Judgement_dungeon_05", "reload", "reload1");
			QuestPointerDelLoc("Judgement_dungeon_04", "reload", "reload1");
			QuestPointerDelLoc("Judgement_dungeon_03", "reload", "reload1");
			QuestPointerDelLoc("Judgement_dungeon_02", "reload", "reload1");
			QuestPointerDelLoc("Judgement_dungeon_01", "quest", "lepricon");
		break;
		
		case "lepricon_14":
            dialog.text = "Igen, eléggé megvertek téged, Prince. Úgy nézel ki, mint egy vizes szar\nMit mondtál a kódexrôl? Hadd világosítsalak fel: Marcusszal dolgoztam, aki állítólag ennek a kódexnek az ôrzôje, annyiszor láttam már, hogy férfiak köptek rá, hogy meg sem merem számolni. Néhányan közülük szörnyû árat fizettek érte. Néhányan közülük nem\nMegtehetsz bármit, amit csak akarsz, ha a díj fedezi. Különösen, ha senki sem figyel.";
			link.l1 = "Szóval... te is a kincsért jöttél?";
			link.l1.go = "lepricon_15";
		break;
		
		case "lepricon_15":
            dialog.text = "Micsoda ostoba kérdés. Mi mást csinálnék itt, olyan messze a hazámtól, Hispaniolán? Bár végül is okosabb vagyok mindannyiótoknál: ismerem a ti rohadt kalóz természeteteket. Csak vártam, hagytam, hogy ti patkányok széttépjétek egymást, és csak egy ellenség maradt életben, de sebesülten és fáradtan.";
			link.l1 = "Ellenséget? Így követitek a patrónusotok kódexét?! Embereket öl ezért!";
			link.l1.go = "lepricon_16";
		break;
		
		case "lepricon_16":
            dialog.text = "Nem vagyok a Kódfejedelem alattvalója, nem vagyok kalóz. Még hajóm sincs - egy kádat kellett bérelnem, hogy idejussak. Nem vagyok más, csak egy kalóz dióhéjban. Vadász vagyok, bivalyokra vadászom és buccant készítek. A kibaszott spanyolok, akik azt állítják, hogy mi, a francia kalózok elrontjuk a megélhetésüket, arra kényszerítettek, hogy támogatást és védelmet kérjek Marcustól. Ezért néha segítek neki az üzletében\nBár nem vagyok kalóz, én és az embereim jól harcolunk, láttál minket akcióban.";
			link.l1 = "Együtt portyáztunk és harcoltunk a koboldokkal. Fedeztük egymást, kockáztattuk az életünket, hogy megmentsük a másikat. Ez neked mind semmi, de semmi?";
			link.l1.go = "lepricon_17";
		break;
		
		case "lepricon_17":
			PlaySound("VOICE\English\LE\Leprikon\Lepricon_04.wav");
            dialog.text = "Ôszinte leszek veled, Prince: sosem kedveltelek. Egy felemás alak vagy. Egy pimasz fiatalember, aki rajong az italokért és a bukott nôkért, aki végzett néhány jövedelmezô munkát Tyrexnek, és nagy kalóznak képzelte magát\nMellesleg természetednél fogva hentes vagy. Azt hiszed, Cartagena nagyobb súlyt adott neked a Testvériségen belül? Ho-ho, ó, a pokolba is, csak az olyan szörnyetegek között, mint amilyen te vagy.";
			link.l1 = "Ó, ez nagyon vicces! Ha-ha-ha, egy igazi angyal mondja ezt! Te vén fattyú!";
			link.l1.go = "lepricon_18";
		break;
		
		case "lepricon_18":
            dialog.text = "Azt hiszem, mostanra már mindent tisztáztunk. Ideje befejezni ezt a komédiát. Az ördögök már túl régóta várnak rád a pokolban.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_RetributionLepriconFight");
		break;
		
		case "lepricon_19":
			if (CheckAttribute(pchar, "questTemp.Mtraxx_MeridaZapugivanieIndeets"))
			{
				dialog.text = "Tetszik, mi?";
				link.l1 = "Vissza!";
				link.l1.go = "lepricon_20";
			}
			else
			{
				dialog.text = "Nos, mit gondolsz?";
				link.l1 = "Ez nem vicces, kobold. Mi a fene?! Nem én rendeltem el a mészárlást! Nem gondolod, hogy ez már túl sok?! Terrax nem fog örülni!";
				link.l1.go = "lepricon_24";
			}
		break;
		
		case "lepricon_20":
            dialog.text = "Akkor miért nézel ilyen bûnösnek? Nem élvezed? Hadd mondjam el neked - a dolgok csak rosszabbak lesznek. Azt hiszed, a mai mészárlás csak azért történt, mert ez egy ilyen nap? Hah, persze. Ez már rutin. Picard még csak meg sem rezzent. Számukra ez is csak egy újabb nap, amikor azt csinálják, amit szeretnek.";
			link.l1 = "És mi van veled? Csak átutazóban?";
			link.l1.go = "lepricon_21";
		break;
		
		case "lepricon_21":
            dialog.text = "Nem vagyok kalóz. És inkább nem vennék részt a mai eseményekben. És... ha ennyire felzaklatott a nôi testek látványa Merida megfeketedett talaján, miért viselkedtél úgy, ahogy az indiánokkal, herceg?";
			link.l1 = "Mit kellett volna tennem? Dobjak el mindent, és kússzak Marcushoz egy bocsánatkéréssel?";
			link.l1.go = "lepricon_22";
		break;
		
		case "lepricon_22":
            dialog.text = "Csak azt hittem, hogy önök már teljesen átvették ezt, és úgy gondolkodnak és viselkednek, mint a Tirax kapitányai. De nem! Túl puhány vagy ehhez a munkához. Jobb lenne, ha odaadnád a részed Marcusnak, és farkadat behúzva távoznál. Ez nem a te hivatásod.";
			link.l1 = "Nem neked kell döntened helyettem, kobold. És biztosan nincs jogod sértegetni engem. Nem adom oda a részemet senkinek. Tisztességesen megosztom Terrax-szal.";
			link.l1.go = "lepricon_23";
		break;
		
		case "lepricon_23":
            dialog.text = "Persze. De jobb, ha elmegyünk, mielôtt elájulsz.";
			link.l1 = "Ez nem vicces, a fenébe is.";
			link.l1.go = "lepricon_30";
		break;
		
		case "lepricon_24":
            dialog.text = "Akkor nem ismered jól. Mégis, mivel a mai események nem okoznak örömet, hallgasd meg, mit tudok ajánlani.";
			link.l1 = "Mit tudsz te ezek után ajánlani?!";
			link.l1.go = "lepricon_25";
		break;
		
		case "lepricon_25":
            dialog.text = "Jobb lenne, ha igyekeznél meghallgatni, fiú.";
			link.l1 = "Hmm, nem tetszik a hangnemed, Lucas, de jó, menj csak.";
			link.l1.go = "lepricon_26";
		break;
		
		case "lepricon_26":
            dialog.text = "Megengedhetem magamnak - régebb óta élek, mint te, herceg. Szóval éles szemem van, nem csak a lövöldözésre. Akarod tudni, mit vettem észre?";
			link.l1 = "Csak mondd ki!";
			link.l1.go = "lepricon_27";
		break;
		
		case "lepricon_27":
            dialog.text = "Nem vagy a helyén. Igen, jó vagy. Jól haladsz. De csak azért, mert erôs kapitány vagy, nem pedig azért, mert ez az igazi hivatásod. Nem tudom, hogyan fordultál a Terrax felé, vagy miért, de hidd el, ez nem a te dolgod.";
			link.l1 = "Nekem... van egy célom. Nem mondhatom el, mi az.";
			link.l1.go = "lepricon_28";
		break;
		
		case "lepricon_28":
            dialog.text = "És közelebb jutottál már hozzá?";
			link.l1 = "Még nem.";
			link.l1.go = "lepricon_29";
		break;
		
		case "lepricon_29":
            dialog.text = "Nos, ha még a mai nap sem hozott közelebb, akkor itt már nincs mit nyerni. Te jó fiú vagy, herceg. Emberként bántál az indiánokkal. A sors iróniája, hogy itt kötöttél ki, nálunk. Azt tanácsolom: add a részedet Terraxnak, hogy elkerülj mindenféle problémát, és kerüld el ezt az egészet - mentsd a lelked, amíg lehet.";
			link.l1 = "Majd meggondolom.";
			link.l1.go = "lepricon_30";
		break;
		
		case "lepricon_30":
			DialogExit();
			locCameraFromToPos(21.35, 1.54, 0.05, true, 25.55, 0.46, -0.91);
			if (CheckAttribute(pchar, "questTemp.Mtraxx_MeridaZloVariant"))
			{
				PlaySound("People Fight\PistolShot.wav");
				DoQuestFunctionDelay("Mtraxx_MeridaGorit_5", 2.0);
			}
			else
			{
				DoQuestFunctionDelay("Mtraxx_MeridaGorit_5", 0.5);
			}
		break;
		
		// Тагофа - проводник к Мериде
		case "tagofa":
            dialog.text = "Tagofa üdvözöl téged, a tenger fia. Akarod, hogy mutassak neked utat a hegyekben lévô spanyol településhez?";
			link.l1 = "Úgy van. Látom, hogy jól beszélsz a nyelvünkön, ellentétben a néped többi tagjával.";
			link.l1.go = "tagofa_1";
		break;
		
		case "tagofa_1":
            dialog.text = "Tagofának gyakran volt dolga a yalanauival... Az utunk nagy részét egy folyón fogjuk megtenni. Hosszú csónakokra lesz szükségük. Vannak ilyenek?";
			link.l1 = "Nektek van? Kölcsönkérhetnénk ôket egy kis idôre...";
			link.l1.go = "tagofa_2";
		break;
		
		case "tagofa_2":
            dialog.text = "A mi falunk kicsi, nagyon kevés hosszú csónakunk van, és mindegyik csak halászatra használható. Nekünk jó hosszú csónakokra van szükségünk, olyanokra, amelyek hosszú utat bírnak ki, mint a ti hajóitok.";
			link.l1 = "Hmm... Akkor hat hosszú csónakra lesz szükségünk. A hajón nincs annyi.";
			link.l1.go = "tagofa_3";
		break;
		
		case "tagofa_3":
            dialog.text = "Akkor építsd meg ôket. Ti, fehér emberek, meg tudjátok javítani az óriási hajótokat a parton, biztosan tudtok néhány hosszú csónakot készíteni.";
			link.l1 = "Heh, úgy tûnik, igazad van, Tagofa. Vigyél el minket a folyóhoz, remélem nincs messze innen?";
			link.l1.go = "tagofa_4";
		break;
		
		case "tagofa_4":
            dialog.text = "Nincs messze. Gyertek utánam.";
			link.l1 = "...";
			link.l1.go = "tagofa_5";
		break;
		
		case "tagofa_5":
           DialogExit();
		   chrDisableReloadToLocation = true;
		   npchar.dialog.currentnode = "tagofa_6";
		   LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Mtraxx_MeridaGotoRiver", 5.0);
		break;
		
		case "tagofa_6":
            dialog.text = "Itt van a folyó, amirôl beszéltem neked. Innen indulunk tovább. Te megépíted a csónakokat, aztán indulunk.";
			link.l1 = "Értettem, Tagofa. Majd szólok, ha végeztünk.";
			link.l1.go = "tagofa_7";
		break;
		
		case "tagofa_7":
            DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.dialog.currentnode = "tagofa_8";
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			pchar.questTemp.Mtraxx = "merida_boats";
			pchar.questTemp.Mtraxx.Boats = "true";
			chrDisableReloadToLocation = false;
			DoQuestCheckDelay("TalkSelf_Quest", 2.0);
			// Лепрекона - гулять
			sld = characterFromId("Lepricon");
			sld.dialog.currentnode = "lepricon_3";
			LAi_SetWarriorType(sld);
			LAi_warrior_DialogEnable(sld, true);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			SetFunctionTimerCondition("Mtraxx_MeridaBoatLate", 0, 0, 10, false); // таймер, чтобы не ходил долго
		break;
		
		case "tagofa_8":
            dialog.text = "Készen vannak a csónakok, fehér törzsfônök?";
			link.l1 = "Igen, készen. Az embereim mindjárt felszállnak rájuk.";
			link.l1.go = "tagofa_9";
		break;
		
		case "tagofa_9":
            dialog.text = "Nagyon jó. Szállj fel velem együtt az elsôre. Tagofa megmutatja az utat.";
			link.l1 = "";
			link.l1.go = "tagofa_10";
		break;
		
		case "tagofa_10":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2", "none", "", "", "Mtraxx_MeridaRiverTrip", -1);
			chrDisableReloadToLocation = true;
		break;
		
		case "tagofa_11":
            dialog.text = "A folyó része kész. Innen már nem leszünk messze a spanyol településtôl. Ott van az ösvény, maradjatok rajta, és nem fogunk eltévedni. Sikerült megkerülnünk egy Capong vadászokkal teli erdôt, de itt is az ô földjük van. Óvatosnak kell lennünk.";
			link.l1 = "Ne aggódjatok. Kiirtjuk ôket, amint megmutatják ronda, festett arcukat.";
			link.l1.go = "tagofa_12";
		break;
		
		case "tagofa_12":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			pchar.quest.mtraxx_merida_warning.win_condition.l1 = "locator";
			pchar.quest.mtraxx_merida_warning.win_condition.l1.location = "Serpentine2";
			pchar.quest.mtraxx_merida_warning.win_condition.l1.locator_group = "quest";
			pchar.quest.mtraxx_merida_warning.win_condition.l1.locator = "detector1";
			pchar.quest.mtraxx_merida_warning.function = "Mtraxx_MeridaWarning";
			chrDisableReloadToLocation = false;
		break;
		
		case "tagofa_13":
			StartQuestMovie(true, false, true);
            dialog.text = "";
			link.l1 = "Hé! Tagofa! Nézzétek! Mi az ott... az ösvény közepén? Valami indián izé.";
			link.l1.go = "tagofa_14";
			locCameraFromToPos(7.63, 9.07, 11.73, true, 2.97, 9.02, 7.70);
			CharacterTurnToLoc(pchar, "quest", "quest1");
		break;
		
		case "tagofa_14":
            DialogExit();
			LAi_SetActorType(pchar);
			LAi_FadeLong("Mtraxx_MeridaWarningCutscene", "");
			locCameraSleep(true);
		break;
		
		case "tagofa_15":
            dialog.text = "Ez a Capongs jele. Egy figyelmeztetés. Azt mondja, hogy állj meg és ne menj tovább. A Capongok már kiszúrtak minket.";
			link.l1 = "És mi van, ha tovább megyünk? Megtámadnak minket?";
			link.l1.go = "tagofa_16";
		break;
		
		case "tagofa_16":
            dialog.text = "Igen, fehér törzsfônök. Biztosan fenyegetônek tûnsz számukra, hiszen még nem támadtak ránk. És mégis kitettek egy jelet neked.";
			link.l1 = "Baszd meg a táblát. Tovább megyünk... Mindenki figyeljen ide! Fegyverbe! Készüljetek! Figyelem! Ha ezek a vademberek megmutatják ronda arcukat, mindet megöljük!";
			link.l1.go = "tagofa_17";
		break;
		
		case "tagofa_17":
            DialogExit();
			EndQuestMovie();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			pchar.quest.mtraxx_merida_capong.win_condition.l1 = "location";
			pchar.quest.mtraxx_merida_capong.win_condition.l1.location = "Merida_jungle_01";
			pchar.quest.mtraxx_merida_capong.function = "Mtraxx_MeridaPrepareCapongAttack";
		break;
		
		case "tagofa_18":
            dialog.text = "Fehér fônök és az emberei szétverték a capongokat, Tagofa le van nyûgözve. A spanyol város közel van. Van egy völgy, ahol egy vízesést látunk. Tagofa nem megy a spanyolokhoz. A vízesés mellett várlak majd rád.";
			link.l1 = "Rendben. Induljatok!";
			link.l1.go = "tagofa_19";
		break;
		
		case "tagofa_19":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			chrDisableReloadToLocation = false;
			pchar.quest.mtraxx_merida_exittown.win_condition.l1 = "location";
			pchar.quest.mtraxx_merida_exittown.win_condition.l1.location = "Merida_ExitTown";
			pchar.quest.mtraxx_merida_exittown.function = "Mtraxx_MeridaExitTown";
			Mtraxx_MeridaCheckOurWarriors();
			AddQuestRecord("Roger_5", "15");
		break;
		
		case "tagofa_20":
            dialog.text = "Visszatértünk, fehér fônök. Tagofa megtette, amit ígért.";
			link.l1 = "Köszönöm, Tagofa. Jól csináltad.";
			link.l1.go = "tagofa_21";
		break;
		
		case "tagofa_21":
            dialog.text = "Tagofának mennie kell. Hayami nagyon vár rám. Viszlát, a tenger fia.";
			link.l1 = "Sok szerencsét, a szelva fia. Add át üdvözletem a feleségednek. És köszönöm, hogy segítettél nekünk.";
			link.l1.go = "tagofa_22";
		break;
		
		case "tagofa_22":
            DialogExit();
			chrDisableReloadToLocation = false;
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 20.0);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			pchar.quest.mtraxx_merida_final.win_condition.l1 = "location";
			pchar.quest.mtraxx_merida_final.win_condition.l1.location = "Shore_ship3";
			pchar.quest.mtraxx_merida_final.function = "Mtraxx_MeridaFinal";
			ChangeIndianRelation(7.0);
		break;
		
		// дозорный у Мериды
		case "merida_guard":
            dialog.text = "Hé! Ki vagy te és mit akarsz?";
			link.l1 = "El kell jutnunk Meridába, és beszélnünk kell a kormányzóval, vagy bárki mással, aki helyettesítheti ôt...";
			link.l1.go = "merida_guard_1";
		break;
		
		case "merida_guard_1":
            dialog.text = "Nem engedünk idegeneket Meridába. Tûnjetek el!";
			link.l1 = "Pal két napig keményen eveztünk, aztán indiánok hordáival küzdöttünk, hogy ne csak úgy elmenjünk. Ismétlem, beszélni akarok a falud fejével! Van egy... üzleti ajánlatunk a számára, igen! És ha mindannyian beleegyezünk, a falud érintetlenül marad.";
			link.l1.go = "merida_guard_2";
		break;
		
		case "merida_guard_2":
            dialog.text = "Te most fenyegetôzöl, Ladron?";
			link.l1 = "Ezt meg honnan tudod? Ah igen, valóban, fenyegetôzöm. Vagy békével vagy erôszakkal kapjuk meg, amiért itt vagyunk, és tiéd a megtiszteltetés, hogy dönts a falud sorsáról.";
			link.l1.go = "merida_guard_3";
		break;
		
		case "merida_guard_3":
            dialog.text = "Soha nem fogsz belépni Meridába, te kibaszott kalóz! Riadó! Ellenség a kapuknál!";
			link.l1 = "Micsoda ésszerûtlen úriember...";
			link.l1.go = "merida_guard_4";
		break;
		
		case "merida_guard_4":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2", "none", "", "", "", 10.0);
			DoQuestFunctionDelay("Mtraxx_MeridaHouseGuards", 5.0);
		break;
		
		// мэр Мериды
		case "merida_head":
            dialog.text = "Átkozott ladronok! Mit akarsz tôlünk?! Ez egy kis, szerény település. Nincs se aranyunk, se ezüstünk! Honnan tudtatok rólunk?";
			link.l1 = "Ó, ne játssza az ártatlant és a tanácstalan, excellenciás uram. Az egész világ tele van pletykákkal az opáljaitokról.";
			link.l1.go = "merida_head_1";
		break;
		
		case "merida_head_1":
            dialog.text = "És te okoztad ezt az istentelen mészárlást... pletykák miatt?! Senkit sem kíméltél! Szörnyek... Tudd meg: a lelôhelyek messze vannak innen. Nincs itt semmi keresnivalótok. Távozzatok.";
			link.l1 = "Ti kezdtétek ezt az istentelen mészárlást. A civilek a katonáiddal együtt harcoltak. Soha nem fogom elhinni, hogy ilyen értelmetlen hôsiesség lehetséges csak azért, hogy megvédjetek néhány csupasz falat.";
			link.l1.go = "merida_head_2";
		break;
		
		case "merida_head_2":
            dialog.text = "Tudod te, hogy mennyi erôfeszítésbe került ezeket a falakat felépíteni? Nem béreltünk külsôs építôket, mi magunk építettük ôket, tégláról téglára. Minden egyes lakó. Még én is, ezekkel a kezekkel.";
			link.l1 = "Megható történet... És mi van a bútorokkal? Azt is maguk készítették? Milyen szép faragott szék. És az asztal. És a szekrények. Ez pácolt tölgyfa? Vagy ébenfa? Kicsit túl fényûzô egy 'szerény településhez,' nem gondolja?";
			link.l1.go = "merida_head_3";
		break;
		
		case "merida_head_3":
            dialog.text = "Az erkölcs elhomályosította az elmédet, Ladron.";
			link.l1 = "Nem kell bonyolítani a dolgokat, kormányzó úr. Vagy megbánja.";
			link.l1.go = "merida_head_4";
		break;
		
		case "merida_head_4":
            dialog.text = "Meg akarsz kínozni, te átkozott kalóz? Kár érted - én hiszek a Mindenható Istenben. És mártírként fogok felemelkedni, ha túlzásba viszed.";
			link.l1 = "Hm-m...";
			link.l1.go = "merida_head_5";
		break;

		case "merida_head_5":
			StartInstantDialog("Mrt_Rocur", "merida_head_6", "Quest\Roger.c");
		break;
		
		case "merida_head_6":
            dialog.text = "Barátom, nem fog így beszélni. Hadd intézzem én.";
			link.l1 = "Oh?";
			link.l1.go = "merida_head_7";
		break;
		
		case "merida_head_7":
            dialog.text = "Emlékszem mindenre, amit azok a felfuvalkodott spanyolok tettek velem azon az átkozott ültetvényen. Szívesen megmutatom, herceg. És mesélek pár történetet, ha már itt vagyok. Nem fogsz unatkozni.";
			link.l1 = "És mi van, ha elragadtatod magad?";
			link.l1.go = "merida_head_8";
		break;
		
	case "merida_head_8":
            dialog.text = "Nem fog szépen beszélni. Ismerem a fajtáját.";
			if (IsCharacterPerkOn(pchar, "Trustworthy") && sti(pchar.reputation.nobility) >= 50 && GetSummonSkillFromName(pchar, SKILL_Leadership) >= 50)
			{
				link.l1 = "(megbízható) (becsület) (vezetés) Mára elég volt a vér, Jean. Majd én magam elintézem.";
				link.l1.go = "merida_head_dobro_1";
				Notification_Perk(true, "Trustworthy");
				Notification_Reputation(true, 50, "low");
				notification("Képességellenôrzés megfelelt", SKILL_Leadership);
			}
			else
			{
				if (!IsCharacterPerkOn(pchar, "Megbízható")) Notification_Perk(false, "Trustworthy");
				if (sti(pchar.reputation.nobility) < 50) Notification_Reputation(false, 50, "low");
				if (GetCharacterSkill(pchar, SKILL_LEADERSHIP) < 50) notification("Képességpróba Sikertelen (50)", SKILL_LEADERSHIP);
			}
			link.l2 = "Csináld csak. Nem avatkozom bele. És nem is fogom nézni.";
			link.l2.go = "merida_head_zlo_1";
		break;
		
		case "merida_head_zlo_1":
            dialog.text = "Ha nem állnék az adósod, lenne pár jó szavam hozzád... A francba! Gyerünk, gyerünk. Most jön az igazi munka.";
			link.l1 = "Ne erôltesd túl magad.";
			link.l1.go = "rocur_42";
		break;
		
		case "merida_head_dobro_1":
            dialog.text = "Ahogy óhajtja, barátom. Jó lesz nézni.";
			link.l1 = "Ne vigyorogj túl hamar.";
			link.l1.go = "merida_head_dobro_2";
		break;
		
		case "merida_head_dobro_2":
			StartInstantDialog("Merida_Head", "merida_head_dobro_3", "Quest\Roger.c");
		break;
		
		case "merida_head_dobro_3":
            dialog.text = "Azt mondod, hogy magad intézed el, vérontás nélkül, te átkozott ladron? Semmit sem tudsz mondani, amivel köveket varázsolhatsz a semmibôl!";
			link.l1 = "minél hamarabb megjelennek, kormányzó úr. Különben a földdel tesszük egyenlôvé a várost, és mindenkit megölünk, kivéve magát. Nem tetszik ez a megoldás, de hajlandó vagyok kompromisszumot kötni a becsületemmel az ügyem érdekében. A te kötelességed viszont az, hogy megvédd a civileket, a túlélô katonákat és Merida munkásait. Vagy inkább 'mártírként' mártírrá válnál az ô szenvedésük árán? Ez nekem nem hangzik túl istenfélônek.";
			link.l1.go = "merida_head_dobro_4";
		break;
		
		case "merida_head_dobro_4":
            dialog.text = "A fenébe...\nEz... a mellkasába. Csak kíméld meg a városlakókat!";
			if (GetSummonSkillFromName(pchar, SKILL_Sneak) >= 50)
			{
				link.l1 = "(Settenkedik) Minden a ládában van?";
				link.l1.go = "merida_head_dobro_vnimatelnost_1";
				notification("Képességellenôrzés megfelelt", SKILL_Sneak);
			}
			else
			{
				link.l1 = "Tartom a szavam. Viszlát, kormányzó.";
				link.l1.go = "merida_head_dobro_5";
				notification("Képességpróba Sikertelen (50)", SKILL_SNEAK);
			}
		break;
		
		case "merida_head_dobro_vnimatelnost_1":
            dialog.text = "A pokolba veled!\nA ládának is van egy hamis alja. Mindent vigyetek!!!";
			link.l1 = "...";
			link.l1.go = "merida_head_dobro_vnimatelnost_2";
			pchar.questTemp.Mtraxx_MeridaKamushki = true;
		break;
		
		case "merida_head_dobro_vnimatelnost_2":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "goto", "goto2", "Mtraxx_MeridaOpenChest", -1);
			sld = characterFromId("Mrt_Rocur");
			LAi_SetActorType(sld);
		break;
		
		case "merida_head_dobro_vnimatelnost_3":
            dialog.text = "Lassan, herceg. Sajnálom, hogy alábecsültelek.";
			link.l1 = "Elégedett?";
			link.l1.go = "merida_head_dobro_7";
		break;
		
		case "merida_head_dobro_5":
			StartInstantDialog("Mrt_Rocur", "merida_head_dobro_6", "Quest\Roger.c");
		break;
		
		case "merida_head_dobro_6":
            dialog.text = "Simán, Herceg.";
			link.l1 = "Elégedett?";
			link.l1.go = "merida_head_dobro_7";
		break;
		
		case "merida_head_dobro_7":
            dialog.text = "Több mint... De... majd meglátod magad. Menj csak, én még egy kicsit kutakodom.";
			link.l1 = "...";
			link.l1.go = "rocur_43";
		break;
		
		/*case "merida_head_99999":
            DialogExit();
			sld = characterFromId("Mrt_Rocur");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "goto", "goto2", "Mtraxx_MeridaGiveJewelry", -1);
		break;*/
		
		case "merida_head_sleep":
            dialog.text = "Megígérted, hogy elhagyod a várost, amint megkapod a drágaköveket... Most már nálad vannak, és a ladronjaid felgyújtották a házainkat! Hazug vagy és gonosz kalóz! Remélem, hogy a pokol lángjai ilyen forróak lesznek számodra!!!";
			link.l1 = "";
			link.l1.go = "exit";
			locCameraFromToPos(19.18, 1.28, -0.28, true, 24.88, 1.62, -1.19);
			AddDialogExitQuest("Mtraxx_RetributionSleep2");
		break;
		
		// капитан пинаса Китти
		case "kittycap":
            dialog.text = TimeGreeting()+", Kedves uram. Mi a célod itt?";
			link.l1 = "Tyrexbôl jöttem. Azt mondták, hogy kísérjem el a hajóját Bridgetownba. Készen áll?";
			link.l1.go = "kittycap_1";
		break;
		
		case "kittycap_1":
            dialog.text = "Nos, végre! Igen, a legénységem készen áll az azonnali indulásra!";
			link.l1 = "Pompás. Vitorlákat fel, kapitány. Induljunk!";
			link.l1.go = "kittycap_2";
		break;
		
		case "kittycap_2":
		    DialogExit();
            LAi_CharacterDisableDialog(npchar);
			Group_DelCharacter("Mtr_Kitty", "Mtr_KittyCap");
			SetCharacterRemovable(npchar, false);
			npchar.CompanionEnemyEnable = false; //всегда друзья
			LAi_SetImmortal(npchar, false);
			SetCompanionIndex(pchar, -1, sti(npchar.index));
			npchar.loyality = MAX_LOYALITY;
		    pchar.quest.mtraxx_ignasio_sail.win_condition.l1 = "location";
			pchar.quest.mtraxx_ignasio_sail.win_condition.l1.location = "Bridgetown_town";
			pchar.quest.mtraxx_ignasio_sail.function = "Mtraxx_IgnasioArrive";
			SetFunctionTimerCondition("Mtraxx_IgnasioTimeOver", 0, 0, 30, false);
			pchar.quest.mtraxx_ignasio_sinkkitty.win_condition.l1 = "NPC_Death";
			pchar.quest.mtraxx_ignasio_sinkkitty.win_condition.l1.character = "Mtr_KittyCap";
			pchar.quest.mtraxx_ignasio_sinkkitty.function = "Mtraxx_IgnasioKittySink";
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
		break;
		
		case "kittycap_3":
            dialog.text = "Köszönöm, hogy segít nekem, kapitány! Veled az oldalamon olyan biztonságban voltam, mintha az erôd falai mögött lettem volna.";
			link.l1 = "Hah, ne is említsd, haver! Minden Marcusnál van. Sok szerencsét neked, haver!";
			link.l1.go = "kittycap_4";
		break;
		
		case "kittycap_4":
            DialogExit();
			npchar.lifeday = 0;
			RemoveCharacterCompanion(pchar, npchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 30.0);
			Mtraxx_IgnasioCreateMarko();
			AddCharacterExpToSkill(pchar, "Sailing", 200);
		break;
		
		// Игнасио Марко
		case "ignasio":
            PlaySound("Voice\English\LE\Ignasio_Marko\Ignasio_01.wav");
			dialog.text = "Üdvözlet a bátor kapitánynak! Hadd mutatkozzam be - egy angol magánhajós, Ignacio Marco a Toreróról.";
			link.l1 = TimeGreeting()+", barátom. Kapitány "+GetFullName(pchar)+" szolgálatára. Miben segíthetek?";
			link.l1.go = "ignasio_1";
		break;
		
		case "ignasio_1":
            PlaySound("Voice\English\LE\Ignasio_Marko\Ignasio_02.wav");
			dialog.text = "Ó, én ismerlek téged! Monseniour "+GetFullName(pchar)+"! A forrásokról és a pártfogóidról szóló pletykák eljutottak hozzám az egész szigetvilágban. Azt hiszem, az ajánlatom igen érdekes lesz számodra.";
			link.l1 = "Milyen ajánlat?";
			link.l1.go = "ignasio_2";
		break;
		
		case "ignasio_2":
            dialog.text = "Menjünk el egy tavernába egy italra. Mindent el fogok mondani. Ez nem egy utcai beszélgetés.";
			link.l1 = "Rendben van... Menjünk!";
			link.l1.go = "ignasio_3";
		break;
		
		case "ignasio_3":
            DialogExit();
			FreeSitLocator("Bridgetown_tavern", "sit_front2");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "Bridgetown_tavern", "sit", "sit_front2", "Mtraxx_IgnasioInTavern", -1);
		break;
		
		case "ignasio_4":
			LAi_SetSitType(pchar);
            dialog.text = "Egy kört, kapitány?";
			link.l1 = "Persze!";
			link.l1.go = "ignasio_5";
		break;
		
		case "ignasio_5":
			LAi_Fade("", "");
            dialog.text = "Heh, itt nem keverik a rumot vízzel...";
			link.l1 = "És nem kezelik a vendégeket rothadt hallal, igen-igen. Szóval, mi a helyzet?";
			link.l1.go = "ignasio_6";
		break;
		
		case "ignasio_6":
            dialog.text = "Tetszik az egyenessége, monsieur. Mondja csak, tud az angolok és a hollandok közötti kereskedelmi háborúról?";
			link.l1 = "Igen. Öröm volt részt venni benne.";
			link.l1.go = "ignasio_7";
		break;
		
		case "ignasio_7":
            PlaySound("Voice\English\LE\Ignasio_Marko\Ignasio_02.wav");
			dialog.text = "Akkor nem kell magyarázkodnia. Angol magánhajósként az ô oldalukon harcolok ebben a háborúban. Maga többnyire szabadúszó. Ami közömbössé tesz téged, hogy melyik oldal ellen harcolsz...";
			link.l1 = "Majdnem. Nem megyek át Franciaországon, sajnálom.";
			link.l1.go = "ignasio_8";
		break;
		
		case "ignasio_8":
            dialog.text = "Mindenképpen, kapitány! Szóval, egyenesen a lényegre térve: Curacao és Trinidad között van egy kis lakott sziget, nincs rajta a térképeken... A közelmúlt óta, mondhatnám, hogy nagyon is a közelmúlt óta, a hollandok elkezdték használni ideiglenes megállónak, hogy feltöltôdjenek és javítsanak. Úgy tûnik, hogy úgy gondolják, hogy csak ôk ismerik ezt a szigetet. Tévedés. He-he\nPár nappal ezelôtt egy ezüst karavánt ért egy... vihar, és most a hollandok ezen a szigeten javítják a hajóikat. A zászlóshajó elvesztette az árbocát, így a javítás eltart egy ideig. A hollandok a javítással vannak elfoglalva, és a legénység nagyrészt szétszóródott a szigeten...";
			link.l1 = "És akkor hirtelen felbukkanunk, hogy megmentsük a helyzetet?";
			link.l1.go = "ignasio_9";
		break;
		
		case "ignasio_9":
            dialog.text = "Pontosan, kapitány. Egyedül nem tudom megcsinálni, de veled együtt - ez egy teljesen más történet. Megkockáztatja? Van egy nagyszerû hajóm, a legénység nagyszerû, és van egy jó adag tapasztalatom. A képességei... szintén dicséretesek.";
			link.l1 = "Mennyi idônk van?";
			link.l1.go = "ignasio_10";
		break;
		
		case "ignasio_10":
            dialog.text = "Rengeteg, ha nem vesztegetjük el, és nem indulunk el azonnal.";
			link.l1 = "Akkor lôszerrel és fegyverekkel töltsük fel a hajót, Ignacio Marco kapitány, és vesszük fel a vitorlákat. Mik a sziget pontos koordinátái?";
			link.l1.go = "ignasio_11";
		break;
		
		case "ignasio_11":
            dialog.text = "12'40 észak, 64'11 nyugat. Megvan?";
			if (CheckAttribute(pchar, "questTemp.HWIC.Isladecoche")) link.l1 = "Ha! Deja vu... Megvan.";
			else link.l1 = "Megvan.";
			link.l1.go = "ignasio_12";
		break;
		
		case "ignasio_12":
            dialog.text = "Irány a 'Torero'. Várni fogom, kapitány!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_IgnasioAddMarko");
		break;
		
		case "ignasio_13":
            PlaySound("Voice\English\LE\Ignasio_Marko\Ignasio_03.wav");
			dialog.text = "Pokoli egy harc, igaz, kapitány? Most jön a kellemes rész: osszuk fel a részünket. A fele az enyém és az embereimé.";
			link.l1 = "Rendben, csináljuk...";
			link.l1.go = "ignasio_14";
		break;
		
		case "ignasio_14":
			LAi_Fade("", "");
			WaitDate("", 0, 0, 0, 3, 10); 
			pchar.questTemp.Mtraxx.Silver = GetSquadronGoods(pchar, GOOD_SILVER)-sti(pchar.questTemp.Mtraxx.Silver);
			pchar.questTemp.Mtraxx.Mahogany = GetSquadronGoods(pchar, GOOD_MAHOGANY)-sti(pchar.questTemp.Mtraxx.Mahogany);
			if (sti(pchar.questTemp.Mtraxx.Silver) < 100)
			{
				dialog.text = "Kapitány, mi az? Hol van az ezüstünk? Elsüllyesztette a zsákmányunkat?";
				if (sti(pchar.questTemp.Mtraxx.Mahogany) < 200) 
				{
					link.l1 = "Hm...";
					link.l1.go = "ignasio_15_1";
				}
				else
				{
					link.l1 = "Az ezüst valahogy kárba veszett, bár szereztünk némi vörösfenyôt. Osszuk fel.";
					link.l1.go = "ignasio_15_11";
				}
				break;
			}
			if (sti(pchar.questTemp.Mtraxx.Silver) < 300 && sti(pchar.questTemp.Mtraxx.Silver) > 100)
			{
				dialog.text = "Hm... Ez szegényes. Azt hittem, sokkal több lesz.";
				link.l1 = "Megvan, amink van.";
				link.l1.go = "ignasio_15_2";
				break;
			}
			if (sti(pchar.questTemp.Mtraxx.Silver) < 700 && sti(pchar.questTemp.Mtraxx.Silver) > 300)
			{
				dialog.text = "Nem rossz, nem rossz. Bár azt hittem, hogy több lesz.";
				link.l1 = "Megvan, amink van.";
				link.l1.go = "ignasio_15_3";
				break;
			}
            dialog.text = "Szép munka, Monseniour. Ez egy szép díj...";
			link.l1 = "Ebben nem tudok nem egyetérteni önnel, kapitány.";
			link.l1.go = "ignasio_15_4";
		break;
		
		case "ignasio_15_1":
			dialog.text = "Úgy látszik, komoly baj van a fejeddel. Elmegyünk! Fiúk!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_IgnasioEscape");
		break;
		
		case "ignasio_15_11":
			RemoveCharacterGoods(pchar, GOOD_MAHOGANY, makeint(sti(pchar.questTemp.Mtraxx.Mahogany)/2));
			dialog.text = "Legalább kapunk valamit ebbôl... Fiúk! Gyerünk, menjünk!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_IgnasioEscape");
		break;
		
		case "ignasio_15_2":
			RemoveCharacterGoods(pchar, GOOD_SILVER, makeint(sti(pchar.questTemp.Mtraxx.Silver)/2));
			RemoveCharacterGoods(pchar, GOOD_MAHOGANY, makeint(sti(pchar.questTemp.Mtraxx.Mahogany)/2));
            dialog.text = "Ez valami. Váljanak el útjaink.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_IgnasioEscape");
		break;
		
		case "ignasio_15_3":
            RemoveCharacterGoods(pchar, GOOD_SILVER, makeint(sti(pchar.questTemp.Mtraxx.Silver)/2));
			RemoveCharacterGoods(pchar, GOOD_MAHOGANY, makeint(sti(pchar.questTemp.Mtraxx.Mahogany)/2));
            dialog.text = "Ez nem semmi. Váljanak el útjaink. Végül is ez egy siker, heh!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_IgnasioEscape");
		break;
		
		case "ignasio_15_4":
			RemoveCharacterGoods(pchar, GOOD_SILVER, makeint(sti(pchar.questTemp.Mtraxx.Silver)/2));
			RemoveCharacterGoods(pchar, GOOD_MAHOGANY, makeint(sti(pchar.questTemp.Mtraxx.Mahogany)/2));
            dialog.text = "Nagyon jövedelmezô találkozónk volt. Talán nem ez volt az utolsó alkalom, hogy együtt üzleteltünk, kapitány!";
			link.l1 = "Hívjatok, ha találtok még kövér kereskedôket, he-he!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_IgnasioEscape");
		break;
		
		case "ignasio_boarding":
			PlaySound("Voice\English\LE\Ignasio_Marko\Ignasio_04.wav");
            dialog.text = "Feltételezem, ez nem véletlen, kapitány?";
			link.l1 = "Nem lennél okos, ha nem látnád. Tartozol nekem az elôkészítésért. Tudod, mirôl beszélek. És tartozol nekem, amiért felültettem Jean Picard barátomat. Ôt eladták az ültetvényre a maga ármánykodása után... Elvesztetted Ignacio-t. Felakasztalak, de a büntetésedet enyhítheted...";
			link.l1.go = "ignasio_boarding_1";
		break;
		
		case "ignasio_boarding_1":
            dialog.text = "Azon tûnôdöm, hogy mit tehetnék, hogy megsajnáljon engem?";
			link.l1 = "Információra van szükségem. A raktérbe teszlek, ahol megbeszéljük a havannai programodat...";
			link.l1.go = "ignasio_boarding_2";
		break;
		
		case "ignasio_boarding_2":
            dialog.text = RandSwear()+" Erre nem számítottam! Ne is gondolj rá. Barbazon pillanatok alatt megtudja, hogy áruló vagyok. Jobb, ha nem tudod, mit tesz azokkal, akik elárulták ôt. Láttam.";
			link.l1 = "Szóval az akasztás jobb megoldás?";
			link.l1.go = "ignasio_boarding_3";
		break;
		
		case "ignasio_boarding_3":
            dialog.text = "Inkább meghalok a harcban!";
			link.l1 = "...";
			link.l1.go = "ignasio_boarding_4";
		break;
		
		case "ignasio_boarding_4":
            DialogExit();
			LAi_SetCurHPMax(npchar);
			LAi_GetCharacterMaxEnergy(npchar);
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "spy_sailor":
            dialog.text = "Kapitány! Kapitány! Gyorsan! A spanyol katonai osztag üldöz minket!";
			link.l1 = RandSwear()+"Erre számítottam... Ugyanez történt Picarddal is. Látta, hányan voltak odakint?";
			link.l1.go = "spy_sailor_1";
		break;
		
		case "spy_sailor_1":
            dialog.text = "Igen, kapitány. Három hajó. A zászlóshajójuk egy gálya, a legnagyobb, amit valaha láttam, és gyorsan halad, a másik kettô egy korvett és egy xebec.";
			link.l1 = "Mindenki a fedélzetre. Talán még menekülhetünk.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_IgnasioOurEscape");
		break;
		
		// индей-кариб в гроте Порто-Белло
		case "grot_canib":
            dialog.text = "Haya! Átkozott yalanaui jön az erdônkbe! Öljétek meg! Haya!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_WolfreekGrotFight");
		break;
		
		// бандит у пещеры Панамы
		case "cave_bandit":
            dialog.text = "Hé! Mi a fenét keresel itt? Ellopod mások' holmiját? Hát, neked annyi!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_WolfreekCaveFight");
		break;
		
		case "carpenter":
            dialog.text = "Hé! Mindenki maradjon ott! Vagy mindannyiótokat elintézem egy grapeshot sortûzzel! "+RandSwear()+"";
			link.l1 = "Most nem megyünk sehova. De figyelj haver - kizárt, hogy egy lövéssel megölj mindannyiunkat. Néhányan közülünk darabokra vágnak, amíg te újratöltesz. Jobb lenne, ha most azonnal beszélgetnénk.";
			link.l1.go = "carpenter_1";
			locCameraFromToPos(-71.57, 14.57, -130.20, true, -63.78, 11.36, -125.50);
		break;
		
		case "carpenter_1":
            dialog.text = "Te vagy itt a fônök? Válaszolj!";
			link.l1 = "Kapitány vagyok "+GetFullName(pchar)+". És te vagy Vörös Farkas helyettese, amíg ô távol van, igazam van?";
			link.l1.go = "carpenter_2";
		break;
		
		case "carpenter_2":
            dialog.text = "Mit keresel itt kapitány "+GetFullName(pchar)+"? Ide nem hívunk vendégeket!";
			link.l1 = "Mi a neved? Tudni akarom, kivel beszélek.";
			link.l1.go = "carpenter_3";
		break;
		
		case "carpenter_3":
            dialog.text = "A nevem Rodgar Janssen.";
			link.l1 = "Látom, hogy ti itt sötétségben vagytok. Már nincs kapitányotok. És a korvettetek is eltûnt. A 'Freyját' a spanyolok szétbombázták nem messze Hispaniolától. A legénységét az utolsó szálig megölték...";
			link.l1.go = "carpenter_4";
		break;
		
		case "carpenter_4":
            dialog.text = RandSwear()+" Wulfric... Aahhh-ghhhhhhhhh!!! ... De honnan tudhatom, hogy igazat mondasz?";
			link.l1 = "Nálam van a volt kapitányod naplója! Van néhány tárgyunk Freyja roncsaiból. A naplónak köszönhetôen megtaláltam ezt a szigetet és ezt a... gordonyt.";
			link.l1.go = "carpenter_5";
		break;
		
		case "carpenter_5":
            dialog.text = "Heh! Még mindig tartozol nekem egy válasszal: miért vagy itt ezen az ismeretlen földön?";
			link.l1 = "Nem fogok hazudni, haver. Azt mondják, Vörös Farkasnak elég nagy vagyona volt. Azért vagyok itt, hogy megtaláljam, mivel a hajóján nem találtak ilyen kincset. Úgy vélem, a jó embereké kell, hogy legyen, Wulfricnak most úgysem használnak.";
			link.l1.go = "carpenter_6";
		break;
		
		case "carpenter_6":
            dialog.text = "Ha! Pajtás, csalódást kell okoznom neked: sem én, sem a legénységbôl senki más nem látta Wolf kincseit. Túl kockázatos volt megkérdezni ôt.";
			link.l1 = "Akkor talán a faludban kellene keresnem ôket. Elveszed a fegyveredet, vagy kezdjem el megrohamozni a falut? Nincs esélyed, Rodgar. Hozok fegyvert és több embert, ha kell.";
			link.l1.go = "carpenter_7";
		break;
		
		case "carpenter_7":
            dialog.text = "Mielôtt meghalunk, egy csomó rohadékot elviszünk a pokolba! Talán téged is!";
			link.l1 = "Biztos vagy benne? Nincs kapitányotok, nincs hajótok, és senki sem fog megmenteni titeket. Még ha el is megyek, hamarosan éhen fogtok halni!";
			link.l1.go = "carpenter_8";
		break;
		
		case "carpenter_8":
            dialog.text = "Hmm... van valami javaslatod?";
			link.l1 = "Igen, van. Lépjen hátrébb a fegyvertôl, és tartsa kordában az embereit. Esküszöm, hogy nem fogom bántani sem magát, sem az embereit. Ha akarsz, csatlakozhatsz a legénységemhez, vagy elviszünk egy civilizációba.";
			link.l1.go = "carpenter_9";
		break;
		
		case "carpenter_9":
            dialog.text = "Esküdjön meg az emberei elôtt hangosan és tisztán!";
			link.l1 = "Esküszöm! A szavamat adom: sem magának, sem az embereinek nem esik bántódása.";
			link.l1.go = "carpenter_10";
		break;
		
		case "carpenter_10":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_11";
			LAi_SetActorType(npchar);
			LAi_ActorDialog(npchar, pchar, "", -1, 0);
			for (i=1; i<=2; i++) // 
			{
				sld = CharacterFromID("Islamona_fort_pirate_"+i);
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			}
		break;
		
		case "carpenter_11":
            dialog.text = "Remélem, megtartja a szavát, kapitány.";
			link.l1 = "Mindig is így teszek. Hányan maradtatok?";
			link.l1.go = "carpenter_12";
		break;
		
		case "carpenter_12":
            dialog.text = "Mindannyiunkat lát. Három. A többiek meghaltak a dzsungelben, amikor megtámadtak titeket. Mondtam nekik, hogy ne tegyék, de nem hallgattak rám...";
			link.l1 = "Értem...";
			link.l1.go = "carpenter_13";
		break;
		
		case "carpenter_13":
            dialog.text = "Az élelmiszer kezdett elfogyni. Elkezdtünk papagájokra vadászni. A 'Freyja' túl sokáig volt távol. Megvolt a gyanúnk, és beigazolódott.";
			link.l1 = "Hála Istennek, hogy úgy döntöttem, kincsvadászatra megyek. Mit gondolsz, hova rejtette el ôket?";
			link.l1.go = "carpenter_14";
		break;
		
		case "carpenter_14":
            dialog.text = "Már mondtam: senki sem látta ôket. Wulfric óvatosan bánt a részével, soha nem hagyta veszendôbe menni. Tisztességes volt velünk, de mindenki, aki megpróbálta megtalálni a rejtekhelyét, eltûnt. Szabadon átkutathatjátok a falut, ha akarjátok.";
			link.l1 = "Ez a tervem. Hol van Vörös Farkas háza?";
			link.l1.go = "carpenter_15";
		break;
		
		case "carpenter_15":
            dialog.text = "Az egyetlen kétszintes épület, ami itt van.";
			link.l1 = "Ez az egyetlen ház, ami a házban van. Egyébként, mi a foglalkozásod?";
			link.l1.go = "carpenter_16";
		break;
		
		case "carpenter_16":
			worldMap.labels.islamona.icon = 5;
			worldMap.labels.islamona.text = CheckingTranslate(LanguageOpenFile("LocLables.txt"),"Islamona");
            dialog.text = "Ács vagyok, és ez a kettô a segédem. Mi szoktuk javítani és görbíteni a 'Freyja' elôtt. Hasznunkra lehetnénk a csapatában.";
			link.l1 = "Értem. Rendben, benne vagytok, a részleteket majd késôbb megbeszéljük. Fogd ezt a fegyvert a bejáratnál. És Rodgar, ne hagyd el a falut, amíg én a rejtekhelyet keresem.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_WolfreekInFort");
		break;
		
		case "carpenter_17":
            dialog.text = "Parancs, kapitány?";
			if (CheckAttribute(pchar, "questTemp.Mtraxx.WolfreekGord"))
			{
				link.l1 = "Igen. A kapitányotok kincseit megtalálták. Jól elrejtette ôket, de én túljártam az eszén!";
				link.l1.go = "carpenter_18";
				break;
			}
			// Jason Исла Мона -->
			if (CheckAttribute(pchar, "questTemp.IslaMona") && pchar.questTemp.IslaMona == "start")
			{
				link.l1 = "Rodgar, mit gondolsz, tudunk még valamit kezdeni ezzel a bázissal?";
				link.l1.go = "IslaMona";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona") && pchar.questTemp.IslaMona == "get_tools")
			{
				link.l1 = "Rodgar, elhoztam a szerszámokat. Már ki kellett volna szállítani ôket.";
				link.l1.go = "IslaMona_8";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona") && pchar.questTemp.IslaMona == "himenes")
			{
				link.l1 = "Üdvözöllek benneteket! Ô Rodrigo Jimenez, egy kis, de nagyon szorgalmas közösség vezetôje Cadizból. Senor Jimenez szívesen beleegyezett, hogy ideiglenesen letelepedjen a földünkön, és segítsen nekünk az építkezésben.";
				link.l1.go = "IslaMona_12";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona") && pchar.questTemp.IslaMona == "nextday")
			{
				link.l1 = "Rodgar, hogy vagy? Van valami jó tanácsod számomra?";
				link.l1.go = "IslaMona_18";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona") && pchar.questTemp.IslaMona == "stalk")
			{
				link.l1 = "Rodgar, kérnék egy szívességet.";
				link.l1.go = "IslaMona_20";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona") && pchar.questTemp.IslaMona == "dublon_wait" && PCharDublonsTotal() >=600)
			{
				link.l1 = "Hoztam neked dublont, csak ne pazarold el mindet azonnal piára.";
				link.l1.go = "IslaMona_24";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona") && pchar.questTemp.IslaMona == "storage" && !CheckAttribute(pchar, "questTemp.IslaMona.Food") && IslaMona_CheckFood())
			{
				link.l1 = "Rodgar, ellenôrizd a raktárat. Hoztam gyógyszert és élelmiszert.";
				link.l1.go = "IslaMona_30";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona") && pchar.questTemp.IslaMona == "village")
			{
				link.l1 = "Helló, Rodgar, hogy mennek a dolgok az új településen?";
				link.l1.go = "IslaMona_32";
				break;
			}
			if (!CheckAttribute(npchar, "quest.stalk")) // ремонт кораблей
			{
				link.l2 = "Rodgar, a hajómat meg kell javítani. Te és az embereid készen álltok?";
				link.l2.go = "repair";
			}
			link.l3 = "Rodgar, szeretném itt hagyni az egyik hajómat.";
			if (CheckAttribute(npchar, "portman.info")) link.l3.go = "shipstock";
			else link.l3.go = "shipstock_info";
			if (CheckAttribute(npchar, "portman") && sti(npchar.portman > 0))
			{
				link.l4 = "Rodgar, szeretném visszavinni az egyik hajómat.";
				link.l4.go = "shipstockreturn";
			}
			if (!CheckAttribute(npchar, "storadge"))
			{
				link.l5 = "Nézd, van itt egy üres épület, amit raktárnak használhatnék?";
				link.l5.go = "storadge";
			}
			if (CheckAttribute(npchar, "storadge"))
			{
				link.l5 = "Rodgar, szeretnék látni egy raktárat.";
				link.l5.go = "storadge_3";
			}
			if (CheckAttribute(npchar, "crew"))
			{
				link.l6 = "Rodgar, a csapat egy részét a szigeten akarom hagyni.";
				link.l6.go = "crew";
			}
			if (CheckAttribute(npchar, "crew") && sti(npchar.crew.qty) > 0)
			{
				link.l7 = "Rodgar, szeretném magammal vinni a tengerészeimet vissza a tengerre.";
				link.l7.go = "crew_3";
			}// <-- Исла Мона
			link.l99 = "Még semmi...";
			link.l99.go = "carpenter_exit";
		break;
		
		case "Crew":
			DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			LaunchHireCrew();
		break;
		
		case "carpenter_exit":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
		break;
		
		case "carpenter_18":
            dialog.text = "Gratulálok a sapkához. Mi lesz a következô lépés? Elmegyünk?";
			link.l1 = "Régóta vagytok itt?";
			link.l1.go = "carpenter_19";
		break;
		
		case "carpenter_19":
            dialog.text = "Már túl régóta. Már egy éve, hogy Wulfric engem tett meg itt vezetônek.";
			link.l1 = "Úgy döntöttem, hogy ez a titkos bázis túl jó ahhoz, hogy elpazaroljuk. A falu most már az enyém. Itt hagyhatlak téged és az embereidet, ha akarod. Rum, élelem, gyógyszer - mind a tiéd.";
			link.l1.go = "carpenter_20";
		break;
		
		case "carpenter_20":
            dialog.text = "Az nagyszerû lenne, kapitány. Megszoktam az életet ezen a parton, ezen a szigeten.";
			link.l1 = "Pompás. Egyébként, mi a sziget neve?";
			link.l1.go = "carpenter_21";
		break;
		
		case "carpenter_21":
            dialog.text = "Isla Mona.";
			link.l1 = "Isla Mona... Talán egy nap több házat és építményt fogunk itt építeni... De majd késôbb. Most ugyanezt a szerepet fogjátok itt betölteni, de egy új kapitány alatt.";
			link.l1.go = "carpenter_22";
		break;
		
		case "carpenter_22":
            dialog.text = "Megegyeztünk. Csak vigyázz magadra, kapitány, és ne felejts el ellátni minket élelemmel.";
			link.l1 = "Persze, Rodgar. Sok szerencsét, el kell hajóznom La Vegára.";
			link.l1.go = "carpenter_exit";
			npchar.portman = 0;
			AddDialogExitQuestFunction("Mtraxx_WolfreekComplete");
		break;
		//------------------------------------------------------------ Исла Мона ------------------------------------
		case "IslaMona":
			sTemp = "";
			if (GetCharacterIndex("Mirabella") != -1) sTemp = ", nem számolva a nôddel.";
            dialog.text = "Nehéz megmondani, Cap. A néhai Wulfric sosem hagyott itt két tucat embernél többet. Jelenleg csak hárman vagyunk,"+sTemp+". Nem sokat tehetünk.";
			link.l1 = "Azt akarod mondani, hogy ha többen élnének itt, akkor teljes értékû településsé lehetne alakítani ezt a helyet?";
			link.l1.go = "IslaMona_1";
		break;
		
		case "IslaMona_1":
            dialog.text = "A sziget kicsi, így nem lehet kolóniát építeni rajta, de egy település teljesen lehetséges! Lehet halászni, madarakra és kecskékre vadászni, gyümölcsöt gyûjteni. El tudjuk tartani magunkat, de nem fogunk meggazdagodni belôle.\nDe van egy dolog, amit nem egészen értek, Cap. Miért van erre szükséged?";
			link.l1 = "Ez az én otthonom, az én földem, az én népem. Mit számít nekem, ha nem gondoskodom róluk?";
			link.l1.go = "IslaMona_2_1";
			link.l2 = "Pénzt akarok befektetni egy értékes üzletbe.";
			link.l2.go = "IslaMona_2_2";
			link.l3 = "Ez a kis sziget a régió szívében van. Bölcs dolog lenne egy teljes értékû és titkos katonai bázissá alakítani.";
			link.l3.go = "IslaMona_2_3";
			link.l4 = "Aggódom érted, Rodgar, mindannyian teljesen elvadultatok.";
			link.l4.go = "IslaMona_2_4";
		break;
		
		case "IslaMona_2_1":
            dialog.text = "Furcsa egy alak vagy. Hát, mindegy. Legalább lesz mit csinálni...";
			link.l1 = "";
			link.l1.go = "IslaMona_3";
			AddCharacterExpToSkill(pchar, "Defence", 2000);//защита
		break;
		
		case "IslaMona_2_2":
            dialog.text = "Furcsa egy alak vagy. Hát, mindegy. Legalább lesz mit csinálni...";
			link.l1 = "";
			link.l1.go = "IslaMona_3";
			AddCharacterExpToSkill(pchar, "Commerce", 1500);//торговля
		break;
		
		case "IslaMona_2_3":
            dialog.text = "Furcsa egy alak vagy. Hát, mindegy. Legalább lesz mit csinálni...";
			link.l1 = "";
			link.l1.go = "IslaMona_3";
			AddComplexSelfExpToScill(250, 250, 250, 250);//оружие
		break;
		
		case "IslaMona_2_4":
            dialog.text = "Furcsa egy alak vagy. Hát, mindegy. Legalább lesz mit csinálni...";
			link.l1 = "";
			link.l1.go = "IslaMona_3";
			AddCharacterExpToSkill(pchar, "Leadership", 1000);//авторитет
		break;
		
		case "IslaMona_3":
            dialog.text = "Elôször is, nagyon különleges személyeket kell találnia. Olyanokat, akiket meg lehet gyôzni, hogy ebbe a vadonba költözzenek, hogy ott éljenek és dolgozzanak évekig, a külvilágtól teljesen elszigetelve. Ilyen különleges embereket kell keresni. Remélhetôleg nem csak egyet. Végül is, nem utasíthatja a legénységét, hogy itt éljen, legalábbis még nem. A telepesek nem akarnák elhagyni a megszokott otthonaikat és a stabil munkájukat. És nekünk sincs szükségünk itt csavargókra és más alkalmatlanokra.\nMellett a szigetet körülvevô titoktartás kérdése mindig is jelen lesz. Ha valakinek elmondod, azonnal ott lesz a veszély, hogy vadászok fognak nyomozni.";
			link.l1 = "Értem, van valami javaslatod?";
			link.l1.go = "IslaMona_4";
		break;
		
		case "IslaMona_4":
            dialog.text = "Nem, kapitány. Túl régóta vagyok itt, és teljesen elszakadtam a civilizált élettôl.";
			link.l1 = "Nagyszerû, ez hasznos!";
			link.l1.go = "IslaMona_5";
		break;
		
		case "IslaMona_5":
            dialog.text = "Én fával dolgozom, nem emberekkel. És ennek nagyon örülök, ha-ha! Egyébként az embereken kívül még egy sor jó minôségû kovács- és építôszerszámot is ide kell hoznod. Ezeket csak a régi Európában gyártják, így elég sokba fognak kerülni. Kérdezd meg a hajógyárak, a nagyobbak tulajdonosait.";
			link.l1 = "Minden világos. Összefoglaljuk: ha ezt a bázist valami nagyobbá akarom tenni, akkor több telepest és szerszámot kell idehoznom?";
			link.l1.go = "IslaMona_6";
		break;
		
		case "IslaMona_6":
            dialog.text = "Ez így van!";
			link.l1 = "Meglátom, mit tehetek.";
			link.l1.go = "IslaMona_7";
		break;
		
		case "IslaMona_7":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			AddQuestRecord("IslaMona", "1");
			pchar.questTemp.IslaMona = "tools";
			IslaMona_SelectShipyard();
		break;
		
		case "IslaMona_8":
            dialog.text = "Igenis, kapitány! Készen állunk a kolóniaépítésre! Drága volt?";
			link.l1 = "Egy vagyonba került, remélem, megérte!";
			link.l1.go = "IslaMona_9_1";
			link.l2 = "Pár évvel ezelôtt azt mondtam volna, hogy nagyon drága. De most... Nem is tudom.";
			link.l2.go = "IslaMona_9_2";
		break;
		
		case "IslaMona_9_1":
			AddCharacterExpToSkill(pchar, "Commerce", 600);
            dialog.text = "Nem elégedhetett meg azzal, ami már megvolt, ugye? Mindenesetre készülj fel arra, hogy a kiadásaid csak nôni fognak. Megoldották már a kérdést a telepesekkel?";
			link.l1 = "Nem, Rodgar. Még nem találtam ki, hol találom ôket. Elvégre nekem nincsenek szuverén jogaim arra, hogy településeket létesítsek ezeken a vizeken.";
			link.l1.go = "IslaMona_10";
		break;
		
		case "IslaMona_9_2":
			AddCharacterExpToSkill(pchar, "Leadership", 300);
            dialog.text = "Nem elégedhetett meg azzal, ami már megvolt, ugye? Mindenesetre készülj fel arra, hogy a kiadásaid csak nôni fognak. Megoldották már a kérdést a telepesekkel?";
			link.l1 = "Nem, Rodgar. Még nem találtam ki, hol találom ôket. Elvégre nekem nincsenek szuverén jogaim arra, hogy településeket létesítsek ezeken a vizeken.";
			link.l1.go = "IslaMona_10";
		break;
		
		case "IslaMona_10":
            dialog.text = "Ezeken a vizeken, kapitány, minden nap káosz uralkodik. Hallgassa meg, mit mondanak az emberek, lehet, hogy meglát egy rejtett lehetôséget. Egyelôre gondoskodom az eszközökrôl.";
			link.l1 = "Rendben, figyelni fogom az ilyen jellegû információkat.";
			link.l1.go = "IslaMona_11";
		break;
		
		case "IslaMona_11":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			AddQuestRecord("IslaMona", "3");
			RemoveItems(pchar, "islamona_toolbox", 1);
			pchar.questTemp.IslaMona = "rumours";
			AddRumor("They say some criminals have been cast out to one of the uninhabited islands! It seems they're such fierce monsters that even the executioner and the holy fathers wouldn't want to deal with them! But why do they always bring such people to us?!", 1, "all", "none", 0, (2022 - STARTGAME_YEAR) * 365, "IslaMona_TerksRumour", "none");
		break;
		
		case "IslaMona_12":
            dialog.text = "Spanyolok? Ugye csak viccel, kapitány? Azt hittem, hogy a Le Francois-iakból hoztál idiótákat, nem pedig ezeket...";
			link.l1 = "";
			link.l1.go = "IslaMona_13";
		break;
		
		case "IslaMona_13":
            DialogExit();
			LAi_SetActorType(npchar);
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_18";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "IslaMona_14":
            dialog.text = "Európából jöttél? Hehe, nem nehéz megmondani. Ne aggódj, majd megszokod.";
			link.l1 = "Jimenez, egy ideig nálam fogsz lakni. Van ott egy pince, rengeteg hely. Rodgar, hoztam a szerszámokat, és a telepeseket is. Mi a következô lépés?";
			link.l1.go = "IslaMona_15";
		break;
		
		case "IslaMona_15":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_20";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "IslaMona_16":
            dialog.text = "Holnap találkozunk, kapitány. Egy nap múlva beszélünk, amint ezek a... telepesek letelepednek a kincseikkel...";
			link.l1 = "Rendben, holnap folytatjuk.";
			link.l1.go = "IslaMona_17";
		break;
		
		case "IslaMona_17":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			LAi_SetWarriorType(npchar);
			IslaMona_HimenesWait();
		break;
		
		case "IslaMona_18":
            dialog.text = "Kapitány, beszéljen a spanyolokkal. Ô már teljesen el van foglalva a munkájával.";
			link.l1 = "Értettem, meglesz.";
			link.l1.go = "IslaMona_19";
			link.l2 = "Valami baj van?";
			link.l2.go = "IslaMona_18_1";
		break;
		
		case "IslaMona_18_1":
			AddCharacterExpToSkill(pchar, "Leadership", 100);
            dialog.text = "Kapitány, én már évek óta a srácokkal vagyok itt. A spanyolok nyüzsgése kezd az idegeimre menni.";
			link.l1 = "Nincs konfliktus! És megtiltom neked és az embereidnek, hogy akár csak a nôik irányába nézzetek! Legalábbis egyelôre... Ha a dolgok elfajulnak, fogjatok egy csónakot és menjetek... halászni pár napra.";
			link.l1.go = "IslaMona_18_2";
		break;
		
		case "IslaMona_18_2":
            dialog.text = "Igenis, uram!";
			link.l1 = "Tökéletes. Rendben, megnézem, mire készül.";
			link.l1.go = "IslaMona_19";
		break;
		
		case "IslaMona_19":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			IslaMona_SetHimenesNextDay();
		break;
		
		case "IslaMona_20":
            dialog.text = "Már tudom, kapitány. A spanyol azt akarja, hogy felfedezzük a szigetet? Ugráljunk a sziklákon egy térképpel, mint egy rakás idióta?";
			link.l1 = "Így van, Rodgar.";
			link.l1.go = "IslaMona_21";
		break;
		
		case "IslaMona_21":
            dialog.text = "Hatszáz dublon, és megteszem.";
			link.l1 = "Megôrültél? Megharapott egy helyi pók vagy egy mérges kígyó? Mit fogsz csinálni egy láda arannyal egy lakatlan szigeten? Eltemetem?";
			link.l1.go = "IslaMona_22";
		break;
		
		case "IslaMona_22":
            dialog.text = "Gyerünk, kapitány. Egy nap elhagyjuk ezt a helyet, és kinek lesz ránk szüksége a nagyvilágban érme nélkül? Persze, van egy kis rejtekhelyünk, de ez közel sem elég. Wulfric soha nem rendezte az adósságát velem és a legényekkel az utolsó vállalkozásaiért.\nEgy dolog hónapokig lustálkodni a parton, és félévente egyszer kiszolgálni a flottát. De minden nap keményen dolgozni a szilárd talajon, mint egy elátkozott kalóz - az egy teljesen más történet! Ez egy munka, és a munkáért fizetni kell. Fizet a legénységének, ugye, kapitány?";
			link.l1 = "Jól hangzik. Megszerzem a 600 dublont. Remélem, nem várja el a fizetséget elôre, ugye?";
			link.l1.go = "IslaMona_23";
			link.l2 = "Van egy másik ajánlatom. A szárazföldön dolgozol, nem a tengeren kaparod le a pajorokat a hajókról. Jelenleg nagy szükségünk van erre a fajta munkára.";
			link.l2.go = "IslaMona_25";
		break;
		
		case "IslaMona_23":
			ChangeCharacterComplexReputation(pchar, "nobility", 10);
			AddCharacterExpToSkill(pchar, "Leadership", 500);
			AddQuestRecord("IslaMona", "7");
            dialog.text = "Kapitány, én kész vagyok azonnal kezdeni, de az embereim sokkal keményebben fognak dolgozni, ha dublont látnak a kezükben. Ígérem, hogy nem hagyunk egy feltáratlan területet sem ezen a szigeten.";
			if (PCharDublonsTotal() >= 600)
			{
				link.l1 = "Rendben. Itt van az aranyad. Csak ne pazaroljátok azonnal italra.";
				link.l1.go = "IslaMona_24";
			}
			else
			{
				link.l1 = "Rendben, elhozom a dublónokat.";
				link.l1.go = "IslaMona_24_1";
			}
		break;
		
		case "IslaMona_24_1":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			pchar.questTemp.IslaMona = "dublon_wait";
		break;
		
		case "IslaMona_24":
			RemoveDublonsFromPCharTotal(600);
			Log_Info("600 dublont adtál oda.");
			PlaySound("interface\important_item.wav");
            dialog.text = "Ha-ha! Ebben igaza van, kapitány! Ó, és majdnem elfelejtettem. Most már elég sokan élnek itt, és szükségük van valami ennivalóra. Láttad azokat a hölgyeket? Nem szoktak hozzá a túléléshez és a földbôl való táplálkozáshoz. Nem fognak segíteni.";
			link.l1 = "Csak azt ne mondd, hogy még több kalózt kell keresnem, hogy segítsenek neked.";
			link.l1.go = "IslaMona_26";
		break;
		
		case "IslaMona_25":
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
			ChangeCharacterComplexReputation(pchar, "authority", 5);
			pchar.questTemp.IslaMona.Nodublon = "true"; // дублоны не заплатил
			AddQuestRecord("IslaMona", "8");
            dialog.text = "Igenis, kapitány! Készen állunk a szárazföldi munkára! Ó, és még valami, majdnem elfelejtettem. Most már elég sokan élnek itt, és szükségük van valami ennivalóra. Láttad azokat a hölgyeket? Nem szoktak hozzá a túléléshez és a földbôl való táplálkozáshoz. Nem fognak segíteni.";
			link.l1 = "Ne mondd, hogy nekem is kalózokat kell keresnem, hogy segítsek neked...";
			link.l1.go = "IslaMona_26";
		break;
		
		case "IslaMona_26":
            dialog.text = "Nem, miért tennénk? Kiképezzük és felkészítjük közülük a legképzettebbeket a megélhetésre. De amíg az a csodálatos pillanat el nem érkezik, nektek kell ellátnotok minket élelemmel. Pár ezer adag hajóélelmiszer elég lesz. És egy centnernyi gyógyszer a jövôre nézve. Pakoljátok ki mindezt a hajókról a szigeten lévô raktárunkba.";
			link.l1 = "Rendben. Mennyi idôre van szükségük a felderítô küldetéshez?";
			link.l1.go = "IslaMona_27";
		break;
		
		case "IslaMona_27":
            dialog.text = "Két-három nap múlva végzünk, már találtunk néhány érdekes dolgot.";
			link.l1 = "Nagyszerû!";
			link.l1.go = "IslaMona_28";
		break;
		
		case "IslaMona_28":
            dialog.text = "Amint végeztünk, egyenesen ahhoz a nevetô spanyolhoz menjetek. Az ôrültnek le kell vonnia a következtetéseket a munkánkból.";
			link.l1 = "Látom, már majdnem barátok vagytok. Akkor három nap múlva meglátogatom. Nos, akkor a munkára. Sok szerencsét mindannyiunknak!";
			link.l1.go = "IslaMona_29";
		break;
		
		case "IslaMona_29":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			npchar.quest.stalk = "true";
			AddQuestRecord("IslaMona", "9");
			pchar.questTemp.IslaMona = "storage";
			SetFunctionTimerCondition("IslaMona_StalkFin", 0, 0, 3, false);
		break;
		
		case "IslaMona_30":
            dialog.text = "Hûha! Köszönöm, kapitány. Most már van idônk felkészíteni a hölgyeket erre az ôrült életre a vadonban.";
			link.l1 = "Csak vigyázzatok, nehogy kalózokat csináljatok belôlük! Köszönöm, Rodgar";
			link.l1.go = "IslaMona_31";
		break;
		
		case "IslaMona_31":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			pchar.questTemp.IslaMona.Food = "true";
			AddQuestRecord("IslaMona", "10");
			IslaMona_RemoveFood();
		break;
		
		case "IslaMona_32":
            dialog.text = "Kapitány! Meg kell mondjam, kezdtem magam kényelmetlenül érezni, hogy itt élek.";
			link.l1 = "Miért, Rodgar? Hiányzik a szegénység és a romlás varázsa?";
			link.l1.go = "IslaMona_33";
		break;
		
		case "IslaMona_33":
            dialog.text = "Így is mondhatjuk. Most már a civilizáció még ide is eljutott. És a magamfajtáknak nincs helyük benne.";
			link.l1 = "Vegyél magadnak egy jabotot és egy botot. Jól be fog illeszkedni.";
			link.l1.go = "IslaMona_34";
		break;
		
		case "IslaMona_34":
            dialog.text = "Inkább menjünk a spanyolodhoz, és beszéljük meg a felderítés eredményeit. Van még egy ôrült ötletem...";
			link.l1 = "Most beszéltem vele! Rendben, menjünk, Rodgar.";
			link.l1.go = "IslaMona_37";
			link.l2 = "Hogy tetszik vele dolgozni?";
			link.l2.go = "IslaMona_35";
		break;
		
		case "IslaMona_35":
            dialog.text = "Magasan képzett és szorgalmas emberek! És Jimenez valóban egy mester. Régen az ilyen emberekért jó sok aranyat lehetett volna kapni. És a lányaik is gyönyörûek...";
			link.l1 = "Hallani sem akarok errôl, Rodgar! Menjünk, beszéljünk a mesterünkkel!";
			link.l1.go = "IslaMona_36_1";
			link.l2 = "Ha nem bírják a munkát, akkor eladjuk ôket. De tartsátok meg a lányokat, ha-ha! Menjünk, beszéljünk a mesterrel... ";
			link.l2.go = "IslaMona_36_2";
		break;
		
		case "IslaMona_36_1":
			ChangeCharacterComplexReputation(pchar, "nobility", 6);
            dialog.text = "Komolyan, kapitány? Csak vicceltem, menjünk...";
			link.l1 = "";
			link.l1.go = "IslaMona_37";
		break;
		
		case "IslaMona_36_2":
			ChangeCharacterComplexReputation(pchar, "nobility", -6);
            dialog.text = "Tudtam, hogy támogatni fogsz, kapitány! Menjünk...";
			link.l1 = "";
			link.l1.go = "IslaMona_37";
		break;
		
		case "IslaMona_37":
            DialogExit();
			DoQuestReloadToLocation("IslaMona_TwoFloorHouse", "goto", "goto5", "IslaMona_HouseDialog");
		break;
		
		case "IslaMona_38":
            dialog.text = "Nem nevet, kapitány...";
			link.l1 = "";
			link.l1.go = "IslaMona_39";
		break;
		
		case "IslaMona_39":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_48";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_40":
            dialog.text = "Az is, kapitány. Majd késôbb megbeszéljük...";
			link.l1 = "";
			link.l1.go = "IslaMona_41";
		break;
		
		case "IslaMona_41":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_52";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_42":
            dialog.text = "Az úrnak igaza van, kapitány. Egyikünk sem fogja a hátát törni a dzsungelben. Lehet, hogy az üzlet piszkos, de másképp nem lehet ebbôl a helybôl többet kihozni, mint egy kalózfészekbôl.";
			link.l1 = "";
			link.l1.go = "IslaMona_43";
		break;
		
		case "IslaMona_43":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_58";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_44":
            dialog.text = "Kapitány, amikor felépíti a gyárat, a rabszolgáknak védelemre lesz szükségük. Az én embereim majd gondoskodnak róla. Az egyikük még villámmal is lô, mint Thor. Semmi sem motivál jobban a munkára, mint egy vadász távcsô. Egy fegyverünk már van, most kell egy második. Bármilyen muskéta megteszi.";
			link.l1 = "";
			link.l1.go = "IslaMona_45";
		break;
		
		case "IslaMona_45":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_60";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_46":
            dialog.text = "És az embereimnek ugyanennyi aranyra és még egy tucat üveg jó rumra lesz szükségük.";
			link.l1 = "Mennyi fát tudsz majd szállítani minden egyes tételben? És miért van szükséged aranyra?";
			link.l1.go = "IslaMona_47";
		break;
		
		case "IslaMona_47":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_62";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_48":
            dialog.text = "Nos, elôször is, az élet szabadidô nélkül értelmetlen, és hamarosan még a jámbor, hehe, katolikusok is elkezdenek falra mászni. Másodszor pedig, ha van a szigeten egy kocsma, akkor a legénység egy részét itt hagyhatod készenlétben. Tudod, elég nehéz meggyôzni az embereket, hogy ingyen éljenek vademberként a tengerparton lévô kunyhókban egy egész éven át. De ha van a közelben egy település, ahol van taverna, meleg étel, zene és szórakozás... Mi másra van szüksége egy tengerésznek a parton töltött szabadságon?";
			link.l1 = "Kurvák?";
			link.l1.go = "IslaMona_49";
			link.l2 = "Italok?";
			link.l2.go = "IslaMona_49";
		break;
		
		case "IslaMona_49":
            dialog.text = "Igazad van, de oldjuk meg a problémákat egyesével. Elôször is, újjáépítjük a házadat...";
			link.l1 = "...";
			link.l1.go = "IslaMona_50";
		break;
		
		case "IslaMona_50":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_65";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_51":
            dialog.text = "Erre nem is gondolt, kapitány.";
			link.l1 = "Köszönöm, Rodgar. Úgy tudom, hogy mostantól több hajót is kiszolgálhatok ebben a kis öbölben, igaz?";
			link.l1.go = "IslaMona_52";
		break;
		
		case "IslaMona_52":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_harbour_4";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_53":
            dialog.text = "Üdvözletem, kapitány! Azért jöttél, hogy megbeszéljük a munkát?";
			link.l1 = "Nem, egyáltalán nem. Csak hiányoltam az északi fiziognómiáját.";
			link.l1.go = "IslaMona_54";
		break;
		
		case "IslaMona_54":
            dialog.text = "Sétáljunk egyet? Megmutatom a gyárat.";
			link.l1 = "Vezessenek.";
			link.l1.go = "IslaMona_55";
		break;
		
		case "IslaMona_55":
            DialogExit();
			IslaMona_PlantationGo();
		break;
		
		case "IslaMona_56":
            dialog.text = "H-hic! Kapitány, ünnepelünk!";
			link.l1 = "Rodgar! Rodrigo! A francba!";
			link.l1.go = "IslaMona_57";
		break;
		
		case "IslaMona_57":
            dialog.text = "Mi a baj, k-k-kapitány? Nem tetszik a falak színe?";
			link.l1 = "Csak most vettem észre, hogy ti ketten ugyanazt a nevet viselitek! Ha-ha-ha-ha! Egy spanyol és egy kalóz, akiknek ugyanaz a nevük, kocsmát építettek egy lakatlan szigeten, és együtt iszogatnak, mintha az indián istenek mindenkit felfalnának, és napfelkeltére vége lenne a világnak! Ha-ha! Én is veled vagyok!";
			link.l1.go = "IslaMona_58";
		break;
		
		case "IslaMona_58":
            dialog.text = "Ha-ha-ha! Ez igaz! Egészségünkre!";
			link.l1 = "Egészségünkre!";
			link.l1.go = "IslaMona_59";
		break;
		
		case "IslaMona_59":
            DialogExit();
			npchar.dialog.currentnode = "IslaMona_60";
			IslaMona_ReloadTavern();
		break;
		
		case "IslaMona_60":
            dialog.text = "Kérsz egy italt, sapka?";
			link.l1 = "Kocsmáros leszel, Rodgar?";
			link.l1.go = "IslaMona_61";
		break;
		
		case "IslaMona_61":
            dialog.text = "Ideiglenesen! A spanyolok különösen értékelik, ha egy kalóz vigyáz a pultra - ez számukra az igazi egzotikum és kaland. De összességében szép itt minden. Ha úgy döntesz, hogy a legénységed bármelyik tagját tartalékban hagyod ezen a településen, csak szólj - elintézem.";
			link.l1 = "De hol fognak lakni?";
			link.l1.go = "IslaMona_62";
		break;
		
		case "IslaMona_62":
            dialog.text = "Egyszerû - építünk néhány kunyhót a parton. Így a kocsmából a partra fognak futni. Csak emlékeztetôül, ez a sziget nem fog háromszáz embernél többet befogadni, úgyhogy ezt tartsátok szem elôtt a jövôre nézve. Néha kérni fogjuk, hogy hozzanak rumot és bort, ezért jó lenne, ha ön, kapitány, elôre fel tudná tölteni az árut a raktárban.";
			link.l1 = "Ezt megjegyzem. Nos akkor, compadre. Szórakoztasd a spanyolokat és tarts szünetet. Csak kérlek, ne igyál addig, amíg az egész falu le nem ég - azt a látványt nem tudnám elviselni!";
			link.l1.go = "IslaMona_63";
		break;
		
		case "IslaMona_63":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			//LocatorReloadEnterDisable("IslaMona_TwoFloorHouse", "reload1", false);
			//LocatorReloadEnterDisable("IslaMona_TwoFloorHouse", "reload3", false);
			npchar.crew = "true"; // можно оставлять матросов
			npchar.crew.qty = 0;
			pchar.questTemp.IslaMona.Tavern = "done"; // флаг - таверна построена и сдана
			// belamour обнулим матросов-->
			ref rTown = GetColonyByIndex(FindColony(loadedLocation.fastreload));
			rTown.Ship.crew.quantity = 0;
			rTown.Ship.crew.morale = 0;
			rTown.Ship.Crew.Exp.Sailors   = 0;
			rTown.Ship.Crew.Exp.Cannoners = 0;
			rTown.Ship.Crew.Exp.Soldiers  = 0;
			ChangeCrewExp(rTown, "Sailors", 0);  // приведение к 1-100
			ChangeCrewExp(rTown, "Cannoners", 0);
			ChangeCrewExp(rTown, "Soldiers", 0);
			
		break;
		
		case "IslaMona_64":
            dialog.text = "Kapitány! Átkozottul örülök, hogy látlak! Hála Freyjának, épp idôben érkeztél!";
			link.l1 = "Igen, megint nagy bajba keveredtünk. Hola, Rodrigo!";
			link.l1.go = "IslaMona_65";
		break;
		
		case "IslaMona_65":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_church_13";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_66":
            dialog.text = "Nincsenek áldozatok. A túlélô spanyolok értek el minket elôször, jelentették, hogy lehetséges, hogy még több vendéggel találkozunk, és sikerült szinte az összes élelmiszert és felszerelést a környékrôl a településre vinni. A rabszolgákkal persze nem alakult túl jól a helyzet.";
			link.l1 = "";
			link.l1.go = "IslaMona_67";
		break;
		
		case "IslaMona_67":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_church_16";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_68":
            dialog.text = "Mi van, ha nyílt támadásba rángatnak minket?";
			link.l1 = "Akkor fegyverek nélkül dolgozunk. Mint egy felvonuláson, együtt vonulunk a kapukhoz, aztán csak hátulról csapunk le rájuk. Te tartod a kapukat és támogatod ôket. Ennyi, sok szerencsét nekünk!";
			link.l1.go = "IslaMona_69";
		break;
		
		case "IslaMona_69":
            DialogExit();
			AddQuestRecord("IslaMona", "21");
			pchar.quest.islamona_def_jungle1.win_condition.l1 = "locator";
			pchar.quest.islamona_def_jungle1.win_condition.l1.location = "IslaMona_jungle_01";
			pchar.quest.islamona_def_jungle1.win_condition.l1.locator_group = "encdetector";
			pchar.quest.islamona_def_jungle1.win_condition.l1.locator = "enc04";
			pchar.quest.islamona_def_jungle1.function = "IslaMona_DefSoldiersInJungle"; // встреча с французами
			LAi_LocationFightDisable(&Locations[FindLocation("IslaMona_jungle_01")], true);//запретить драться
		break;
		
		case "IslaMona_70":
            dialog.text = "Hurrá, kapitány!";
			link.l1 = "Egyetértek! Ez akkora durranás volt, hogy nekem is kedvem lett volna lefeküdni. Srácok, mit pakoltatok be?";
			link.l1.go = "IslaMona_71";
		break;
		
		case "IslaMona_71":
            dialog.text = "Dupla adagot, kapitány. Így ez az egy lövés elriasztja ôket a további harctól!";
			link.l1 = "Nem aggódtál, hogy a fegyver felrobban a gyengéd bánásmódtól?";
			link.l1.go = "IslaMona_72";
		break;
		
		case "IslaMona_72":
            dialog.text = "Van egy különleges talizmánom, amit Wulfrictól kaptam. Valami emlék a mi szülôföldünkrôl, Dániából. Menjünk a kocsmába, kapitány? Mindannyian fáradtak vagyunk a mai nap után.";
			link.l1 = "Igen, az nagyszerû lenne. Játsszunk egy kis kártyát - fogadjunk a csodás talizmánodra.";
			link.l1.go = "IslaMona_73";
		break;
		
		case "IslaMona_73":
            dialog.text = "Ha-ha, ilyen isteni teljesítmény után, kapitány, talán még ezt a lehetôséget is megfontolom!";
			link.l1 = "";
			link.l1.go = "IslaMona_74";
		break;
		
		case "IslaMona_74":
            DialogExit();
			sld = characterFromId("IM_fraofficer");
			sld.dialog.currentnode = "FraOfficer_18";
			LAi_CharacterEnableDialog(sld);
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_75":
            dialog.text = "Kapitány, hallotta ezt? Még mindig cseng a fülem. Kinek a gyászos hangja volt ez?";
			link.l1 = "Ez, Rodgar, egy élô kérdés. Vigyék a gyárba, tegyék láncra, és várják a további utasításokat.";
			link.l1.go = "IslaMona_76";
		break;
		
		case "IslaMona_76":
            dialog.text = "Igenis, kapitány!";
			link.l1 = "";
			link.l1.go = "IslaMona_77";
		break;
		
		case "IslaMona_77":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 5.0);
			sld = characterFromId("IM_fraofficer");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "", 5.0);
			for (i=1; i<=5; i++) 
			{
				sld = characterFromId("IM_soldier_"+i);
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "", 5.0);
			}
			for(i=4; i<=7; i++)
			{
				sld = characterFromId("IM_fra_sailor_"+i);
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "", 5.0);
			}
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_church_20";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "IslaMona_78":
            dialog.text = "Kapitány, azért jött, hogy megoldja a fogoly problémáját? Belefáradtam az ôrködésbe.";
			link.l1 = "Meg kell ölnünk. Túl nagy a kockázat, így nincs más választásunk. Különben jobb, ha nem mutatkozom a francia gyarmatokon.";
			link.l1.go = "IslaMona_79";
			link.l2 = "Nem engedhetem el, különben jobb, ha nem mutatkozom a francia gyarmatokon. Tegyétek bilincsbe, és hagyjátok dolgozni a gyárban. Jobb, mint megölni.";
			link.l2.go = "IslaMona_80";
		break;
		
		case "IslaMona_79":
            dialog.text = "Megvan! Csináljuk gyorsan. Rajta, kapitány. Holnap találkozunk.";
			link.l1 = "";
			link.l1.go = "IslaMona_81";
		break;
		
		case "IslaMona_80":
            dialog.text = "Hûha. Maga aztán a gonosz zseni. Nem szeretnék az ellenséged lenni. Nos, akkor elôbb magyarázkodnunk kell vele. Csak rajta, kapitány. Holnap találkozunk.";
			link.l1 = "";
			link.l1.go = "IslaMona_81";
			pchar.questTemp.IslaMona.Fraprisoner = "true";
		break;
		
		case "IslaMona_81":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "none", "", "", "IslaMona_DefFraPrisonerFin", 10.0); /// идёт внутрь фактории - УСТАНОВИТЬ ЛОКАТОР
		break;
		
		case "IslaMona_82":
            dialog.text = "Micsoda mészárlás! Kár, hogy az ágyúból nem tudtunk lôni, de egyenesen a csapdájába rohantak - jó volt nézni!";
			link.l1 = "Igen, sok vért ontottunk ezen a földön. De úgy látszik, ezen a világon nem lehet másképp otthont építeni.";
			link.l1.go = "IslaMona_83";
		break;
		
		case "IslaMona_83":
            dialog.text = "Ne foglalkozzon vele túl sokat, kapitány. Maga a sors hozta ôket Isla Monára. És hadd mondjam el, a sors eléggé ribanc tud lenni!";
			link.l1 = "A sors, vagy a sziget?";
			link.l1.go = "IslaMona_84";
		break;
		
		case "IslaMona_84":
            dialog.text = "Mindkettô szerepet játszott.";
			link.l1 = "Haha! És mindketten gyönyörûek! Rendben, bátor viking. Gyûjtsd össze a trófeákat és távolítsd el ezeket a testeket. Temessétek el ôket méltósággal. Végül is a mieink...";
			link.l1.go = "IslaMona_85";
		break;
		
		case "IslaMona_85":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_church_20a";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "IslaMona_86":
            dialog.text = "Igenis, kapitány. Így van, kapitány! Rodrigo olyan szépen mondta, hogy könnyet csalt a szemembe. Világos, miért akarják a szentatyák karóba húzni a seggét!";
			link.l1 = "";
			link.l1.go = "IslaMona_87";
			locCameraFromToPos(1.36, 1.32, 0.31, true, 3.44, 0.20, -0.50);
		break;
		
		case "IslaMona_87":
            DialogExit();
			if (GetCharacterIndex("Mirabella") != -1)
			{
				sld = characterFromId("Mirabella");
				sld.dialog.currentnode = "mirabelle_46";
				LAi_SetActorType(sld);
				LAi_ActorDialogDelay(sld, pchar, "", 0.0);
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1 && CheckPassengerInCharacter(pchar, "Mary"))
				{
					sld = characterFromId("Mary");
					sld.dialog.currentnode = "IslaMona_2";
					LAi_SetActorType(sld);
					LAi_ActorDialogDelay(sld, pchar, "", 0.0);
				}
				else
				{
					if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1 && CheckPassengerInCharacter(pchar, "Helena"))
					{
						sld = characterFromId("Helena");
						sld.dialog.currentnode = "IslaMona_2";
						LAi_SetActorType(sld);
						LAi_ActorDialogDelay(sld, pchar, "", 0.0);
					}
					else
					{
						sld = characterFromId("Himenes_companion_1");
						sld.dialog.currentnode = "island_man_2";
						LAi_SetActorType(sld);
						LAi_ActorDialogDelay(sld, pchar, "", 0.0);
					}
				}
			}
		break;
		
		case "IslaMona_88":
            dialog.text = "Rodrigo, és én pont itt futottam össze a prelátusunkkal a budoárban... És hadd mondjam el, ez a legjobb hely Santiagóban!";
			link.l1 = "A legjobb hely, ha a prelátusokat is szereted.";
			link.l1.go = "IslaMona_89";
		break
		
		case "IslaMona_89":
            DialogExit();
			sld = characterFromId("Himenes");
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_90":
            dialog.text = "Igen, igazi kalóz lett abból a gazember és eretnek Rodrigóból, valóban.";
			link.l1 = "Egyébként, világosíts fel, Rodgar. Miért van olyan kevés spanyol kalóz?";
			link.l1.go = "IslaMona_91";
		break;
		
		case "IslaMona_91":
            dialog.text = "Miért olyan kevés? Úgy érted, kalózkapitányok? Nos, rengeteg van belôlük, csak többnyire a sevillai Casa de Contratación alatt tevékenykednek. Olyan, mint a katonai hírszerzés, csak valamiért kereskedôháznak hívják...";
			link.l1 = "";
			link.l1.go = "IslaMona_92";
		break;
		
		case "IslaMona_92":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_77";
			LAi_ActorSetSitMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_93":
            dialog.text = "Igen, miért nem küldesz nekik egy üzenetet, és hívod át ôket. Hát, mindegyiküknek van szabadalma, és idealisták is. Általában nem rabolják ki a saját fajtájukat, csak ha a razzia nem volt sikeres, ha-ha! Csak Puerto Principe-be ugranak be, és állandóan összeütközésbe kerülnek Pastorral.\nEgyikük mostanában tûnt ki... Diego de Montoya. Éppen amikor utoljára Wulfric-kal mentem hadjáratra, sokat hallottam a kalandjairól. Neked, kapitány, van valami közös vele. És ugyanakkor nagyon is különbözik... Különben is, mirôl beszélek? Töltsünk még egy kört, és játsszunk egy kis kártyát.";
			link.l1 = "Nincs nálad pénz. Ugye nem a dublonokra játszol?";
			link.l1.go = "IslaMona_94";
		break;
		
		case "IslaMona_94":
            dialog.text = "Egy-egy pezó a tét. Játsszunk húszig? Hymenes, benne vagy?";
			link.l1 = "";
			link.l1.go = "IslaMona_95";
		break;
		
		case "IslaMona_95":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_79";
			LAi_ActorSetSitMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_96":
            dialog.text = "Játsszunk, kapitány?";
			if (sti(pchar.money) >= 20)
			{
				link.l1 = "Kezdjük!";
				link.l1.go = "IslaMona_97";
			}
			link.l2 = "Én is passzolok, Rodgar. Pezó ide vagy oda, az emberek így is, úgy is elveszítik a hajókat. Szigetekkel. Érezzétek jól magatokat itt, én meg még körülnézek egy kicsit.";
			link.l2.go = "IslaMona_98";
		break;
		
		case "IslaMona_97": // игра в карты
            DialogExit();
			pchar.questTemp.GoldenGirl.Game.IslaMona = "true"; // атрибут квестовой игры
			npchar.money = 20;
			pchar.questTemp.IslaMona.Money = sti(pchar.money);
			pchar.money = 20;
			// вызов интерфейса игры
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
            pchar.GenQuest.Cards.iRate     = 1; // ставка
			LaunchCardsGame();
		break;
		
		case "IslaMona_98": // выход из-за стола
            DialogExit();
			IslaMona_ChurchTavernStandUp();
		break;
		
		case "IslaMona_99":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Win"))
			{
				dialog.text = "Passzolj! Nocsak, nocsak, nem játszom veled tovább! Biztos vagyok benne, hogy csaltál, kapitány! És egy csalót csak úgy elengedni nem lenne helyes!";
				link.l1 = "Hallgatlak, Rodgar.";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Fail"))
				{
					dialog.text = "Én nyertem, kapitány. De nem hagyhatom, hogy csak úgy üres kézzel távozz, haha!";
					link.l1 = "Rendben, te gazember. Ez egy lecke lesz számomra...";
				}
				else
				{
					dialog.text = "Én nyertem, kapitány. De nem hagyhatom, hogy csak úgy üres kézzel távozz, haha!";
					link.l1 = "Rendben, te gazember. Ez egy lecke lesz számomra...";
				}
			}
			link.l1.go = "IslaMona_100";
		break;
		
		case "IslaMona_100":
            dialog.text = "Ah, gyerünk! Esélyt adtál nekem és a legénységemnek egy igazi életre, távol a szûkös szállásoktól, az állott víztôl, és annak a kockázatától, hogy egy szilánkot kapjunk a... koponyába. Tessék. Ezt a bûbájt Wulfric hozta a távoli Dániából, majd átadta nekem, hogy... heh, ne kelljen túl sokat kutakodnom a pincéjében. Nekem már nincs rá szükségem, de neked... ó, nagyon hasznosnak fogod találni.";
			link.l1 = "Köszönöm, Rodgar. Valóban, egy hasznos tárgy. És gyönyörû is...";
			link.l1.go = "IslaMona_101_1";
			link.l2 = "Tartsd meg, Rodgar. Nélküled ez a hely nem létezne. Hagyd, hogy emlékeztessen a hazádra.";
			link.l2.go = "IslaMona_101_2";
		break;
		
		case "IslaMona_101_1":
			GiveItem2Character(pchar, "talisman3");
			Log_Info("Megkaptad Thor kalapácsát.");
			PlaySound("interface\important_item.wav");
            dialog.text = "Örülök, hogy tetszett, kapitány. Még egy kört?";
			link.l1 = "Ti pihenjetek itt, én pedig körülnézek még egy kicsit.";
			link.l1.go = "IslaMona_102";
		break;
		
		case "IslaMona_101_2":
			ChangeCharacterComplexReputation(pchar, "nobility", 10);
			AddCharacterExpToSkill(pchar, "Fortune", 2000);
            dialog.text = "Ahogy kívánod! Akkor adok egyet egy szerencsehölgynek, haha! Még egy kört?";
			link.l1 = "Ti pihenjetek itt, én pedig körülnézek még egy kicsit.";
			link.l1.go = "IslaMona_102";
		break;
		
		case "IslaMona_102":
            DialogExit();
			DeleteAttribute(pchar, "questTemp.GoldenGirl.Game");
			DeleteAttribute(pchar, "GenQuest.Cards");
			pchar.money = sti(pchar.money)+sti(pchar.questTemp.IslaMona.Money);
			DeleteAttribute(pchar, "questTemp.IslaMona.Money");
			IslaMona_ChurchTavernStandUp();
		break;
		
		case "IslaMona_103":
            dialog.text = "Nos, kapitány. Elintézted a dolgokat a spanyolokkal, megünnepeltük az ünneplést, és a fejfájás is enyhült egy kicsit. Az élet szép!";
			link.l1 = "Mire készülsz, Rodgar?";
			link.l1.go = "IslaMona_104";
		break;
		
		case "IslaMona_104":
			sTemp = "";
            if (CheckAttribute(pchar, "questTemp.IslaMona.MiraRodgar")) sTemp = "Majd én megbarátkozom a nôvel. ";
			dialog.text = "Vadászni fogok, mint mindig, szemmel tartom a... a kocsmánkat, a rabszolgákat rugdosom a gyárban. Tökéletes nyugdíjazás.";
			link.l1 = "Csak öt évvel vagy idôsebb nálam, Rodgar. És mi a helyzet veled, Rodrigo? Hogy vagy?";
			link.l1.go = "IslaMona_105";
		break;
		
		case "IslaMona_105":
            DialogExit();
			sld = characterFromId("Himenes");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		// <-- Исла Мона
		
		case "repair":
			if (CheckSelfRepairConditions())
			{
				dialog.text = "Hogyne, kapitány! Csak deszkákra és vitorlavászonra van szükségünk. Menj a leszállóhelyedre, és utasítsd a legénységet, hogy készítsék elô az anyagokat.";
				link.l1 = "Máris megyek. Gyorsan.";
				link.l1.go = "repair_1";
			}
			else
			{
				dialog.text = "Persze, kapitány, de ahogy én látom, a hajójának most nincs szüksége javításra.";
				link.l1 = "Csak megkérdeztem...";
				link.l1.go = "carpenter_exit";
			}
		break;
		
		case "repair_1":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			chrDisableReloadToLocation = true;
			DoQuestReloadToLocation(Pchar.location.from_sea, "reload", "sea", "Mtraxx_WolfreekRepairShore");
		break;
		
		case "shipstock_info":
			npchar.portman.info = "true";
            dialog.text = "Lehetséges, kapitány. De van néhány megkötés: ezen a szigeten csak két hely van, ami alkalmas erre. Továbbá nem hagyhat itt senkit, csak egyetlen tisztet minden hajóra. Egyszerûen nincs elég erôforrásunk, hogy itt tartsuk a legénységet. Még nem. Végül, nincs hely az elsô rangú hajóknak.";
			link.l1 = "Megvan. Kész vagyok itt hagyni egy hajót.";
			link.l1.go = "shipstock";
			link.l2 = "Rendben, elôkészítem.";
			link.l2.go = "carpenter_exit";
		break;
		
		case "shipstock":
			if(CheckAttribute(pchar,"questTemp.IslaMona.Harbour") && pchar.questTemp.IslaMona.Harbour == "done")
			{
				if(sti(npchar.portman) == 3)
				{
					dialog.text = "Kapitány, már három hajója van a dokkban lehorgonyozva. Nincs több szabad hely.";
					link.l1 = "Igaza van, elfelejtettem.";
					link.l1.go = "carpenter_exit";
					break;
				}
				else
				{
					if(CheckAttribute(npchar,"FstClassInHarbour") && sti(npchar.portman) > 0)
					{
						dialog.text = "Kapitány, már van egy elsô osztályú hajó a dokkban. Nincs több szabad hely.";
						link.l1 = "Igaza van, elfelejtettem.";
						link.l1.go = "carpenter_exit";
						break;
					}
				}
			}
			else
			{
				if (sti(npchar.portman) == 2)
				{
					dialog.text = "Kapitány, két hajója már lehorgonyzott a dokknál. Nincs több szabad hely.";
					link.l1 = "Igaza van, elfelejtettem.";
					link.l1.go = "carpenter_exit";
					break;
				}
			}
			if (GetCompanionQuantity(pchar) < 2)
			{
				dialog.text = "Kapitány, csak egy hajója van.";
				link.l1 = "Hm... kevesebbet kéne innom...";
				link.l1.go = "carpenter_exit";
				break;
			}
            dialog.text = "Melyik hajót akarja itt hagyni?";
			for(i=1; i<COMPANION_MAX; i++)
			{
				int cn = GetCompanionIndex(PChar, i);
				if( cn > 0 )
				{
					ref chref = GetCharacter(cn);
					if (!GetRemovable(chref)) continue;

					attrL = "l"+i;
					Link.(attrL) = XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName) + " '" + chref.Ship.Name + "'.";
					Link.(attrL).go = "ShipStockMan_" + i;
				}
			}
			Link.l9 = "Várj, meggondoltam magam.";
			Link.l9.go = "carpenter_exit";
		break;
		
		case "ShipStockMan_1":
            NPChar.ShipToStoreIdx = GetCompanionIndex(PChar, 1);
			dialog.text = "Lássuk csak...";
			Link.l1 = "Nagyon jó.";
			Link.l1.go = "ShipStock_2";
			Link.l2 = "Várj, meggondoltam magam.";
			Link.l2.go = "carpenter_exit";
		break;

		case "ShipStockMan_2":
            NPChar.ShipToStoreIdx = GetCompanionIndex(PChar, 2);
			dialog.text = "Lássuk csak...";
			Link.l1 = "Nagyon jó.";
			Link.l1.go = "ShipStock_2";
			Link.l2 = "Várj, meggondoltam magam.";
			Link.l2.go = "carpenter_exit";
		break;

		case "ShipStockMan_3":
            NPChar.ShipToStoreIdx = GetCompanionIndex(PChar, 3);
			dialog.text = "Lássuk csak...";
			Link.l1 = "Nagyon jó.";
			Link.l1.go = "ShipStock_2";
			Link.l2 = "Várj, meggondoltam magam.";
			Link.l2.go = "carpenter_exit";
		break;
		
		case "ShipStockMan_4":
            NPChar.ShipToStoreIdx = GetCompanionIndex(PChar, 4);
			dialog.text = "Lássuk csak...";
			Link.l1 = "Nagyon jó.";
			Link.l1.go = "ShipStock_2";
			Link.l2 = "Várj, meggondoltam magam.";
			Link.l2.go = "carpenter_exit";
		break;
		
		case "ShipStock_2":
            chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
			if(CheckAttribute(pchar,"questTemp.IslaMona.Harbour") && pchar.questTemp.IslaMona.Harbour == "done")
			{
				if(sti(RealShips[sti(chref.Ship.Type)].Class) < 2 && sti(npchar.portman) > 0)
				{
					dialog.text = "Kapitány, már említettem korábban, hogy a horgonyzóhelyünk csak egy elsô osztályú hajót tud befogadni. Túl nagy a rendelkezésre álló helyhez képest.";
					Link.l1 = "Igaza van, elfelejtettem.";
					Link.l1.go = "carpenter_exit";
					break;
				}
			}
			else
			{
				if (sti(RealShips[sti(chref.Ship.Type)].Class) < 2)
				{
					dialog.text = "Kapitány, az elsô osztályú hajók túl nagyok a mi partjainkhoz. Ezt már mondtam.";
					Link.l1 = "Igaza van, elfelejtettem.";
					Link.l1.go = "carpenter_exit";
					break;
				}
			}
			if (sti(chref.Ship.Crew.Quantity) > 0 && !CheckAttributeEqualTo(pchar, "questTemp.IslaMona.Tavern", "complete"))
			{
				dialog.text = "Kapitány, vigye az egész legénységet a zászlóshajójára, kivéve egy tisztet.";
				Link.l1 = "Á, igen! Megteszem!";
				Link.l1.go = "carpenter_exit";
				break;
			}
			dialog.Text = "Tehát, itt kell tartanunk egy"+XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName+"Acc")+" nevû '"+chref.Ship.Name+"'. Ugye?";
			Link.l1 = "Rendben.";
			Link.l1.go = "ShipStock_3";
			Link.l2 = "Várj, meggondoltam magam.";
			Link.l2.go = "carpenter_exit";
		break;
		
		case "ShipStock_3":
            LeaveShipIslaMona(&NPChar);
			dialog.text = "Rendben, elvisszük egy biztonságos kikötôbe.";
			Link.l1 = "Kiváló!";
			Link.l1.go = "carpenter_exit";
		break;
		
		case "shipstockreturn":
            if (GetCompanionQuantity(pchar) < COMPANION_MAX)
			{
				dialog.text = "Melyik hajót választja, kapitány?";
				cn = 1;
				for (i=1; i<MAX_CHARACTERS; i++)
				{
					makeref(chref, Characters[i]);
					if (CheckAttribute(chref, "ShipInStockMan"))
					{
						if (chref.ShipInStockMan == NPChar.id)
						{
							attrL = "l"+cn;
							Link.(attrL)    = XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName) + " '" + chref.Ship.Name + "'.";
							Link.(attrL).go = "ShipStockManBack_" + i;
							cn++;
						}
					}
				}
				link.l9 = "Várj, meggondoltam magam.";
				link.l9.go = "carpenter_exit";
			}
			else
			{
				dialog.text = "Kapitány, a századában nincs hely még egy hajónak.";
				link.l1 = "Hm. Úgy tûnik, igazad van.";
				link.l1.go = "carpenter_exit";
			}
		break;
		
		 case "ShipStockManBack":
			if (AttributeIsTrue(NPChar, "StoreWithOff") && FindFreeRandomOfficer() < 1 ) {
				dialog.text = "Kap, úgy tűnik, nincs hely még egy tiszt számára a legénységedben.";
				link.l1 = "Lehet, hogy igazad van. Visszatérek később – addig vigyázz itt, hogy senki ne birtokolja át a hajómat.";
				link.l1.go = "exit";
				break;
			}
            chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
			dialog.Text = "Elviszi a hajót?";
			link.l1 = "Igen.";
			link.l1.go = "ShipStockManBack2";
			link.l2 = "Várj, meggondoltam magam.";
			link.l2.go = "carpenter_exit";
		break;
		
		case "ShipStockManBack2":
			DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			if(CheckAttribute(npchar,"FstClassInHarbour")) DeleteAttribute(npchar,"FstClassInHarbour");
			chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
			DeleteAttribute(chref, "ShipInStockMan");
			SetCompanionIndex(pchar, -1, sti(NPChar.ShipToStoreIdx));
			npchar.portman = sti(npchar.portman)-1;
            pchar.ShipInStock = sti(pchar.ShipInStock)-1;
		break;
		
		case "storadge":
            dialog.text = "Itt? Nem. De Wulfric épített egy hatalmas pajtát nem messze innen. Egy masszív épületet, jól beborítva pálmalevelekkel és kátrányos vitorlavászonnal. Van benne egy zár, és egy olyan rakománynak való helyiség, ami egy tucat kereskedelmi hajót is meg tudna tölteni\nEz most üres, de van hozzá kulcsom, ha meg akarod vizsgálni. Megnézhetjük?";
			link.l1 = "Persze! Egyébként: mi van a patkányokkal ezen a szigeten? Elrontják az árumat a pajtában?";
			link.l1.go = "storadge_1";
		break;
		
		case "storadge_1":
            dialog.text = "Farkasnak is megvan rá a fedezete: két macskát hozott ide a szárazföldrôl. A hímekrôl azonban megfeledkezett, így ezek az ôrült szôrû szukák minden alkalommal, amikor eljön a szezonjuk, pocsék hangokat adnak ki. De az egerekre és a patkányokra egész jól vadásznak. Ne aggódjon emiatt, kapitány. Az áruja biztonságban lesz a kártevôktôl és a széltôl.";
			link.l1 = "Nagyszerû! Jó hasznát veszem majd. Tartsd meg magadnak a kulcsot, és mutasd meg nekem ezt a raktárat.";
			link.l1.go = "storadge_2";
		break;
		
		case "storadge_2":
			DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			npchar.city = "islamona";
			npchar.Storage.Activate = true;
			SaveCurrentNpcQuestDateParam(npchar, "Storage.Date");
			npchar.MoneyForStorage = 0;
			npchar.storadge = true;
			LaunchStorage(29);
		break;
		
		case "storadge_3":
            dialog.text = "Kövess, kapitány.";
			link.l1 = "...";
			link.l1.go = "storadge_4";
		break;
		
		case "storadge_4":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			LaunchStorage(29);
		break;
		
		// Мирабель
		case "mirabelle":
			PlaySound("Voice\English\Girl_Q.wav");
            dialog.text = "Ah...";
			link.l1 = "Hát akkor... Egy lány... Mit keresel itt?";
			link.l1.go = "mirabelle_1";
		break;
		
		case "mirabelle_1":
			PlaySound("Voice\English\Girl_Q.wav");
            dialog.text = "Ó...";
			link.l1 = "...";
			link.l1.go = "mirabelle_2";
		break;
		
		case "mirabelle_2":
            DialogExit();
			npchar.dialog.currentnode = "mirabelle_3";
			sld = characterFromId("Mrt_Rocur");
			sld.dialog.currentnode = "rocur_74";
			ChangeCharacterAddressGroup(sld, "LaVega_TwoFloorHouse", "goto", "goto8");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.5);
		break;
		
		case "mirabelle_3":
			PlaySound("Voice\English\LE\Mirabel\Mirabel_01.wav");
            dialog.text = "Senor! Senor "+pchar.name+" ne öljön meg, kérem! Könyörgöm! Nem mondok Tyrexnek semmit! Gyûlölöm azt a szörnyeteget! Könyörgöm, por favor!";
			link.l1 = "...";
			link.l1.go = "mirabelle_4";
		break;
		
		case "mirabelle_4":
			DialogExit();
            npchar.dialog.currentnode = "mirabelle_5";
			npchar.greeting = "mirabella_goodgirl";
			sld = characterFromId("Mrt_Rocur");
			sld.dialog.currentnode = "rocur_80";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "mirabelle_5":
            dialog.text = "";
			link.l1 = "Hé, kislány! Hallottad ezt? Velem jössz, vagy ez a kemény fattyú megöl téged.";
			link.l1.go = "mirabelle_6";
		break;
		
		case "mirabelle_6":
            dialog.text = "Veled megyek, senor, bárhová is visz!";
			link.l1 = "Akkor jó. Tartsd a szádat, vagy megöllek, ha elkezdesz kiabálni vagy Tyrexet hívni. Mi a neved?";
			link.l1.go = "mirabelle_7";
		break;
		
		case "mirabelle_7":
            dialog.text = "Mirabelle...";
			link.l1 = "Viselkedj jól, Mirabelle, és ez szépen fog végzôdni számodra. Maradj közel hozzám, és ne csapj zajt.";
			link.l1.go = "mirabelle_8";
		break;
		
		case "mirabelle_8":
            dialog.text = "Esküszöm, hogy nem megyek, senor.";
			link.l1 = "...";
			link.l1.go = "mirabelle_9";
		break;
		
		case "mirabelle_9":
            DialogExit();
            npchar.dialog.currentnode = "mirabelle_10";
			LAi_SetImmortal(npchar, true);
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			sld = characterFromId("Mrt_Rocur");
			sld.dialog.currentnode = "rocur_85";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
			pchar.questTemp.Mtraxx.Mirabella = "true";
		break;
		
		case "mirabelle_10":
            dialog.text = "Senor?";
			link.l1 = "Jól csináltad, kislány, ezért kedvellek. Most pedig megyünk a hajómra, ahol egy kis kabinban leszel egy ideig. Sajnálom, de nem akarom, hogy Tyrexhez szaladj, és mondj neki bármit.";
			link.l1.go = "mirabelle_11";
		break;
		
		case "mirabelle_11":
            dialog.text = "Szó sem lehet róla, señor! Soha nem mennék el Tyrexhez, ahhoz a szemétládához! Utálom ôt! Gyûlölöm!";
			link.l1 = "Woah! Mit csinált veled?";
			link.l1.go = "mirabelle_12";
		break;
		
		case "mirabelle_12":
            dialog.text = "Sok mindent... Gyûlölöm, gyûlölöm!";
			link.l1 = "Látom. Amint megérkezünk, egy elég puccos házban fogsz lakni. Egyedül. Tarts jó hangulatban, és senki sem fog bántani téged. Most menj egy hosszúhajóra... Mirabelle.";
			link.l1.go = "mirabelle_13";
		break;
		
		case "mirabelle_13":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "sea", "none", "", "", "OpenTheDoors", 20.0);
			pchar.quest.mtraxx_pasq_mirabella.win_condition.l1 = "location";
			pchar.quest.mtraxx_pasq_mirabella.win_condition.l1.location = "Shore75";
			pchar.quest.mtraxx_pasq_mirabella.function = "Mtraxx_PasqualeMirabella";
			pchar.quest.mtraxx_pasq_mirabella1.win_condition.l1 = "location";
			pchar.quest.mtraxx_pasq_mirabella1.win_condition.l1.location = "Shore77";
			pchar.quest.mtraxx_pasq_mirabella1.function = "Mtraxx_PasqualeMirabella";
			AddPassenger(pchar, npchar, false);//добавить пассажира
			SetCharacterRemovable(npchar, false);
			SetFunctionTimerCondition("Mtraxx_MirabellaSailOver", 0, 0, 30, false); // месяц на доплыть до Исла Моны
		break;
		
		case "mirabelle_14":
            dialog.text = "Megérkeztünk, senor?";
			link.l1 = "Igen, édesem. Ez az én falum és az én házam. Az enyém ez a hely. Bár ritka vendég vagyok itt - túl sok a munka odakint. Gondoskodj róla, hogy tisztán tartsd a házamat, amíg itt laksz, különben odaadlak Rodgarnak és az ácsoknak. Nyugodtan sétálgass a szigeten, nagyon szép, de úgysem lehet elmenekülni elôle.";
			link.l1.go = "mirabelle_15";
			// belamour legendary edition -->
			link.l2 = "Nos, itt vagyunk. Ez az otthonom. Ezen a szigeten minden az enyém. Nem járok ide gyakran - végül is a hajón élek, de valakinek mégiscsak vigyáznia kell a házra. Rodgar kegyesen beleegyezett, hogy átadja ezt a megtisztelô szerepet önnek. Annyit sétálhatsz, amennyit csak akarsz, akár a dzsungelben, akár a tengerparton, de mindenképpen legyen valaki a kísérôd, mert még mindig vannak vadállatok a környéken. Mindenesetre hajó nélkül nem mehetsz el innen.";
			link.l2.go = "mirabelle_15a";
		break;
		
		case "mirabelle_15a":
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
            dialog.text = "Nincs hová menekülnöm, senor "+pchar.name+". Nincs senkim, és senkinek sincs szüksége rám. Hacsak nem ad el egy bordélyháznak...";
			link.l1 = "A tûzhelynél van egy lejáró, ami a föld alá vezet, ne menj oda, mert beleesel a barlangba és eltöröd a csontjaidat, vagy nem tudsz visszajutni, és lehet, hogy éhen halsz. És akkor kár lesz, hogy hiába mentettelek meg.";
			link.l1.go = "mirabelle_16";
		break;
		
		case "mirabelle_15":
			ChangeCharacterComplexReputation(pchar,"nobility", -10);
			// <-- legendary edition
            dialog.text = "Nincs hová mennem senor "+pchar.name+". Nincs családom és nincs hasznom. Lehet, hogy megint egy bordélyházban végzem.";
			link.l1 = "Van egy lejáró, ami a barlangba vezet, maradj távol tôle. Sötét és veszélyes odalent.";
			link.l1.go = "mirabelle_16";
		break;
		
		case "mirabelle_16":
            dialog.text = "Távol maradok, uram.";
			link.l1 = "Van egy hálószoba is az emeleten. Kövessenek.";
			link.l1.go = "mirabelle_17";
		break;
		
		case "mirabelle_17":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			pchar.quest.mtraxx_islamona_mirabella1.win_condition.l1 = "location";
			pchar.quest.mtraxx_islamona_mirabella1.win_condition.l1.location = "IslaMona_TwoFloorRoom";
			pchar.quest.mtraxx_islamona_mirabella1.function = "Mtraxx_PasqualeMirabellaRoom";
		break;
		
		case "mirabelle_18":
            dialog.text = "";
			link.l1 = "Ott van. Megmutattam az egész házat. Nem rosszabb, mint Tyrex háza, ahol korábban éltél. Remélem, tetszik.";
			link.l1.go = "mirabelle_19";
		break;
		
		case "mirabelle_19":
            dialog.text = "Igen, uram. Nagyszerû háza van. Megígérem, hogy jól vigyázok rá, amíg távol vagy.";
			link.l1 = "Örülök, hogy ilyen együttmûködô velem. Remélem, hogy ôszinte. Legyen ôszinte velem, különben megbánja, hogy nem. Légy jó kislány, és ne szomoríts el, és jó leszek hozzád. Charlie Prince betartja a szavát!";
			link.l1.go = "mirabelle_20";
			// belamour legendary edition -->
			link.l2 = "Hiszek neked, kedvesem. Azt hiszem, itt nagyobb biztonságban leszel, mint bilincsbe verve abban a sötét raktárhelyiségben, ahol Tyrex tartott téged.";
			link.l2.go = "mirabelle_20a";
		break;
		
		case "mirabelle_20a":
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
            dialog.text = "Köszönöm senor "+pchar.name+". Köszönöm, hogy nem engedte, hogy a... companero megöljön. Ön olyan kedves hozzám...";
			link.l1 = "Heh, és vicces vagy,... És az arcod is szép, még a bélyeggel a homlokodon is. Remélem, minden más is a helyén van... Nos, most mutasd meg a kapitányodnak, hogy mit tudsz. Pihenjünk pár órát a tengeri gurulás után.";
			link.l1.go = "mirabelle_21";
			link.l2 = "Rendben. Ennyi, nekem még sok dolgom van. Te pedig telepedj le, találkozz Rodgarral és a fiúkkal. Ha visszajöttem, majd beszélgetünk még egy kicsit.";
			link.l2.go = "mirabelle_21a";
		break;
		
		case "mirabelle_20":
			ChangeCharacterComplexReputation(pchar,"nobility", -5);
			// <-- legendary edition
            dialog.text = "Köszönöm senor "+pchar.name+". Köszönöm, hogy nem engedte, hogy a... companero megöljön. Ön nagyon kedves.";
			link.l1 = "Heh, te egy vicces kis édes... És szép arcod is van a bélyeg ellenére. Remélem a többi is a helyén van... Most mutasd meg a kapitányodnak, hogy mire vagy képes.";
			link.l1.go = "mirabelle_21";
			// belamour legendary edition -->
			link.l2 = "Rendben. Ennyi, nekem még sok dolgom van. Te pedig telepedj le, találkozz Rodgarral és a fiúkkal. Ha visszajöttem, majd beszélgetünk még egy kicsit.";
			link.l2.go = "mirabelle_21a";
		break;
		
		case "mirabelle_21a":
			AddCharacterExpToSkill(pchar, "Leadership", 400);
			AddCharacterExpToSkill(pchar, "Fortune", 400);
			pchar.questTemp.Mtraxx.MirabellaFirstTimeSex = true;
            DialogExit();
			npchar.InOurHouse = true;
		    npchar.dialog.currentnode = "mirabelle_26";
		    chrDisableReloadToLocation = false;
			pchar.quest.mtraxx_mirabella_setlife.win_condition.l1 = "MapEnter";
			pchar.quest.mtraxx_mirabella_setlife.function = "Mtraxx_MirabellaSetLife";
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
		break;
		
		case "mirabelle_21":
			DialogExit();
			
			pchar.questTemp.Mtraxx.MirabellaFirstTimeKiss = true;
			sld = characterFromId("Mirabella");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, pchar);
			StartQuestMovie(true, false, true);
			LAi_SetActorType(pchar);
			LAi_Fade("IslaMona_MirabelleKiss", "");
		break;
		
		case "mirabelle_22":
			PlaySound("Voice\English\LE\Mirabel\Mirabel_07.wav");
            dialog.text = "Senor "+pchar.name+" olyan édes vagy... Te egy igazi úriember vagy. Nemrég érkezhetett Európából.";
			link.l1 = "Ne hízelegj nekem, te kis hazug, beveszem. Heh, te jó vagy, Mirabelle! Tyrexnek jó ízlése van, he-he-he...";
			link.l1.go = "mirabelle_23";
			locCameraFromToPos(0.55, 1.64, -1.09, true, 0.63, -0.30, -3.12);
		break;
		
		case "mirabelle_23":
            dialog.text = "Én nem. Te egy úriember vagy. De valamiért úgy teszel, mintha goromba lennél. Mhmm... Nekem nagyon tetszett. Várom, hogy újra lássalak...";
			link.l1 = "Ah igen, egy úriember... egy szerencsés úriember, ha-ha! Rendben, édesem, most már nyugodj meg itt.";
			link.l1.go = "mirabelle_24";
		break;
		
		case "mirabelle_24":
            dialog.text = "Viszlát, senor.";
			link.l1 = "...";
			// belamour legendary edition -->
			if(CheckAttribute(pchar,"questTemp.Mtraxx.MirabellaFirstTimeSex"))
			{
				link.l1.go = "mirabelle_28";
				DeleteAttribute(pchar,"questTemp.Mtraxx.MirabellaFirstTimeSex");
			}
			else link.l1.go = "mirabelle_25";
			// <-- legendary edition
		break;
		
		case "mirabelle_25":
            DialogExit();
			npchar.InOurHouse = true;
		    npchar.dialog.currentnode = "mirabelle_26";
			LAi_SetStayType(npchar);
		    chrDisableReloadToLocation = false;
			pchar.quest.mtraxx_mirabella_setlife.win_condition.l1 = "MapEnter";
			pchar.quest.mtraxx_mirabella_setlife.function = "Mtraxx_MirabellaSetLife";
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
		break;
		
		case "mirabelle_26":
            dialog.text = TimeGreeting()+", senor "+pchar.name+"! Nagyon örülök, hogy látom. Hogy van?";
			link.l1 = RandSwear()+""+RandPhraseSimple("Reszkessetek, reszkessetek, reszkessetek!","Ó, jobb élni és meghalni, a bátor fekete zászló alatt, amit lobogtatok!")+" Charlie Prince jól van, édesem.";
			link.l1.go = "mirabelle_26x";
			if (!CheckAttribute(pchar, "questTemp.MirabelleBlock")) {
				if (!CheckAttribute(npchar, "sex_date") || GetNpcQuestPastDayParam(npchar, "sex_date") >= 1)
				{
					link.l2 = "Édesem, mi lenne, ha egy kicsit boldogabbá tennél egy kapitányt?";
					link.l2.go = "mirabelle_sex";
				}
			}
		break;
		
		case "mirabelle_26x":
            DialogExit();
		    npchar.dialog.currentnode = "mirabelle_26";
		break;
		
		case "mirabelle_sex":
            dialog.text = "Magáért bármit, senor!";
			link.l1 = RandPhraseSimple("Készítsétek a markolókat!","Felszállni 'em!");
			link.l1.go = "mirabelle_sex_1";
		break;
		
		case "mirabelle_sex_1":
            DialogExit();
			
			StartQuestMovie(true, false, true);
			LAi_SetActorType(pchar);
			LAi_Fade("", "");
			
			LAi_SetActorType(npchar);
			// belamour legendary edition -->
			if(CheckAttribute(pchar,"questTemp.Mtraxx.MirabellaFirstTimeSex")) npchar.dialog.currentnode = "mirabelle_22";
		    else npchar.dialog.currentnode = "mirabelle_27";
			// <-- legendary edition
			if (pchar.location == "IslaMona_TwoFloorRoom") DoQuestCheckDelay("IslaMona_MirabelleKiss", 0.5);
			else DoQuestReloadToLocation("IslaMona_TwoFloorRoom", "goto", "goto2", "IslaMona_MirabelleKiss");
		break;
		
		case "mirabelle_27":
            dialog.text = "Mhm... Senor, maga egy varázsló! Remélem neked is tetszett? Mindent megtettem, amit tudtam.";
			link.l1 = "Nagyszerûen csináltad, édesem.";
			link.l1.go = "mirabelle_28";
			locCameraFromToPos(0.55, 1.64, -1.09, true, 0.63, -0.30, -3.12);
		break;
		
		case "mirabelle_28":
            DialogExit();
		    npchar.dialog.currentnode = "mirabelle_26";
			LAi_SetStayType(npchar);
			SaveCurrentNpcQuestDateParam(npchar, "sex_date");
		break;
		
		case "mirabelle_sleep":
            dialog.text = "Ez nem igaz, nem igaz! Senor "+pchar.name+" jó és kedves! Csak úgy tesz, mintha gonosz kalóz lenne! Ön az, senor "+pchar.name+"?";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionSleep6_1");
		break;
		
		case "mirabelle_29":
            dialog.text = TimeGreeting()+", senor "+pchar.name+"! Nagyon örülök, hogy látlak. Hogy van? Miért vagy ilyen szomorú?";
			link.l1 = "Helló, Mirabelle. Miért gondolod, hogy szomorú vagyok?";
			link.l1.go = "mirabelle_30";
		break;
		
		case "mirabelle_30":
            dialog.text = "Hát, látom. Nem vagy a szokásos önmagad. Akarod, hogy felvidítsalak? Gyerünk, gyerünk! Szedtem néhány igazán édes gyümölcsöt a dzsungelbôl, és a hal, amit Rodgar és a fiai tegnap fogtak, megsült és még meleg.";
			link.l1 = "Várj. Beszélni akarok veled.";
			link.l1.go = "mirabelle_31";
		break;
		
		case "mirabelle_31":
            dialog.text = "Persze, senor, ahogy akarja. Csupa fül vagyok.";
			link.l1 = "Mondd el, hogyan kerültél Tyrex kezébe, és miért van a homlokodon egy tolvaj jele. Ne félj, soha nem foglak bántani. Csak a történetedet akarom hallani.";
			link.l1.go = "mirabelle_32";
		break;
		
		case "mirabelle_32":
            dialog.text = "Ah, senor! A történetem rövid és unalmas. Puerto Ricóban születtem, az apám fehér férfi volt, az anyám indián. Soha nem láttam az apámat. Gyerekkoromban szolga voltam, és amikor felnôttem, elkövettem azt a butaságot, hogy elloptam a gazdám ékszereit. Soha nem volt sajátom, és annyira szerettem volna egyet, csak hogy egy napra kipróbálhassam a viselését. Persze, mindent kiderítettek\nMegtörtént a tárgyalás, megkorbácsoltak, megbélyegeztek és San Juan börtönébe zártak. Túl sokáig maradtam ott: az egyik tiszt alkut kötött egy fônökkel, és egy marék aranydublónért eladtak egy Philipsburgi bordélyházba\nEgy évet töltöttem ott, vagy egy évet. Egy szerencsétlen napon meglátogatott minket Tyrex és a szemüveges pocsék barátja.";
			link.l1 = "Pasquale Lavoisier...";
			link.l1.go = "mirabelle_33";
		break;
		
		case "mirabelle_33":
            dialog.text = "Igen-igen, a neve senor Pasquale Lavoisier volt. Fogalmam sincs, mit láttak bennem, de nem sokkal a látogatásuk után Tyrex megvásárolt Madame Johannától, és egy ládákkal és árukkal teli, zárt házban helyezett el. Ez volt életem legrosszabb idôszaka, még rosszabb, mint a San Juan-i börtönben töltött napok. Tyrex minden nap meglátogatott, hacsak nem volt a tengerben, és akkor szabadon lélegezhettem, de minden alkalommal, amikor senor Lavoisier jött, én... I.... Ez volt a legrosszabb mind közül. Senor "+pchar.name+", por favor, nem beszélhetek errôl?\nNem tudom, mennyi ideig voltam ott. Aztán jöttél és elvittél abból a szörnyû házból. Nagyon szerencsés voltam, hogy ilyen kedves voltál.";
			link.l1 = "Kedves? Mirabelle, de én is ugyanezt tettem veled: Elvittelek egy szigetre és bezártalak egy házba.";
			link.l1.go = "mirabelle_34";
		break;
		
		case "mirabelle_34":
            dialog.text = "Nem, senor, ez nem igaz. Be vagyok ide zárva? Minden nap sétálok egyet a szigeten. Csodálatos és békés hely. Sok házimunkát kell végeznem? Egyáltalán nem, és egyébként is hozzászoktam. És nem olyan vagy, mint Tyrex, nem olyan, mint a kereskedô barátja. Mindig örülök, ha látlak, olyan fiatal és jóképû vagy. És úriember is...";
			link.l1 = "Mirabelle, szeretnéd, hogy elvigyelek valamelyik városba? Adok neked elég pénzt. Hová? Válassza bármelyik kolóniát.";
			link.l1.go = "mirabelle_35";
		break;
		
		case "mirabelle_35":
            dialog.text = "Senor, nem akar elzavarni? Kérem, ne tegye, te lo ruego!";
			link.l1 = "Hát... Azt hittem, vissza akar térni a normális élethez...";
			link.l1.go = "mirabelle_36";
		break;
		
		case "mirabelle_36":
            dialog.text = "Ah, senor "+pchar.name+", és mi vár rám? Hogyan fogok férjhez menni, mint megjelölt félvér? Megint eladnak egy bordélyházba. Kérem, ne küldjön el. Szeretem ezt a helyet, sehol máshol nem éreztem magam ilyen békésnek és biztonságosnak, csak itt. Rodgar és a fiai jó fiúk, barátok vagyunk, és soha nem bántottak, mindegyikük az életét kockáztatná értem. Szeretem velük tölteni az idôt, és ez jó móka! Néha tüzet rakunk a tengerparton, én pedig szambát táncolok. Kérem, senor, bármit megteszek önért, csak hadd maradjak!";
			link.l1 = "Rendben, Mirabelle, maradj itt, ha már ennyire szereted ezt a helyet. Csak tudd, hogy itt nem vagy fogoly, bármikor megkérhetsz, hogy vigyelek el innen.";
			link.l1.go = "mirabelle_37";
		break;
		
		case "mirabelle_37":
            dialog.text = "Kedves jó senor, köszönöm! Köszönöm! Köszönöm! Soha nem fogok ilyesmit kérni - én ennek a szigetnek a foglya akarok maradni... és a te foglyod, te-hee... Olyan kedves vagy ma, de szomorú! Nem énekelsz és nem káromkodsz, ahogy szoktál.";
			link.l1 = "Lehet, hogy énekelek, de káromkodni nem fogok, Mirabelle. És... Sajnálom, ha valaha is goromba voltam veled.";
			link.l1.go = "mirabelle_38";
		break;
		
		case "mirabelle_38":
            dialog.text = "Szigorú és szigorú leszel, mint egy angol lord... Ah... senor, akarja, hogy táncoljak és énekeljek ma este? Csak önnek. Most pedig gyere velem! Nincs jobb gyógyír a szomorúságra, mint a szerelem. Annyira hiányoztál.";
			link.l1 = "Hah! Jó érv, drága lányom... Gyerünk, menjünk.";
			link.l1.go = "mirabelle_39";
		break;
		
		case "mirabelle_39":
            DialogExit();
			LAi_SetActorType(npchar);
		    npchar.dialog.currentnode = "mirabelle_40";
			if (pchar.location == "IslaMona_TwoFloorRoom") DoQuestCheckDelay("IslaMona_MirabelleKiss", 0.5);
			else DoQuestReloadToLocation("IslaMona_TwoFloorRoom", "goto", "goto2", "IslaMona_MirabelleKiss");
		break;
		
		case "mirabelle_40":
			PlaySound("Voice\English\LE\Mirabel\Mirabel_07.wav");
            dialog.text = "Ah, senor "+pchar.name+", olyan gyengéd volt ma, mhm... Elégedett velem, kedves capitán?";
			link.l1 = "Minden elragadó volt, Mirabelle.";
			link.l1.go = "mirabelle_41";
			locCameraFromToPos(0.55, 1.64, -1.09, true, 0.63, -0.30, -3.12);
		break;
		
		case "mirabelle_41":
            DialogExit();
		    npchar.dialog.currentnode = "mirabelle_42";
			LAi_SetStayType(npchar);
			SaveCurrentNpcQuestDateParam(npchar, "sex_date");
		break;
		
		case "mirabelle_42":
			bool bMary = GetCharacterIndex("Mary") != -1 && CheckAttribute(pchar, "questTemp.LSC.Mary_officer");
			bool bHelena = GetCharacterIndex("Helena") != -1 && CheckAttribute(pchar, "questTemp.Saga.Helena_officer");
            dialog.text = TimeGreeting()+", senor "+pchar.name+"! Nagyon örülök, hogy látlak! Hogy vagy?";
			link.l1 = ""+LinkRandPhrase("Én is örülök, hogy látlak, kislányom.", "Szia, Mirabelle. Te mindig ugyanolyan vagy - vidám és gyönyörû, milyen kellemes látvány.","Szia, szépségem. Lenyûgözôen nézel ki!")+"Jól vagyok. Remélem te is jól vagy.";
			link.l1.go = "mirabelle_42x";
			if (!bMary && !bHelena && !CheckAttribute(npchar,"quest.rodgar")) // прогона 3
			{
				if (!CheckAttribute(npchar, "sex_date") || GetNpcQuestPastDayParam(npchar, "sex_date") >= 1)
				{
					link.l2 = "Mirabelle, máris elkezdett hiányozni te és a menyecskéd. Megcsókolod a tengeri farkasodat?";
					link.l2.go = "mirabelle_43";
				}
			}
		break;
		
		case "mirabelle_42x":
            DialogExit();
		    npchar.dialog.currentnode = "mirabelle_42";
		break;
		
		case "mirabelle_43":
            dialog.text = "Á, édes kapitányom, te is hiányoztál! Gyerünk, a szélén vagyok!";
			link.l1 = "...";
			link.l1.go = "mirabelle_39";
		break;
		
		// Jason Исла Мона
		case "mirabelle_44":
			dialog.text = "Kapitány Úr! Kapitány "+pchar.name+"! Annyira boldog vagyok! Megmentesz minket!";
			link.l1 = "Én is örülök, hogy látlak, Mirabelle. Szóval, mi a helyzet a veszteségekkel?";
			link.l1.go = "mirabelle_45";
		break;
		
		case "mirabelle_45":
            DialogExit();
		    npchar.dialog.currentnode = "mirabelle_42";
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_66";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "mirabelle_46":
			dialog.text = "Kapitány, kapitány, köszönöm! Te vagy a legjobb, a legkedvesebb! Nemcsak megmentettél a szörnyektôl, hanem új életet is adtál nekem! Mindannyiunkra!";
			link.l1 = "";
			link.l1.go = "mirabelle_47";
			locCameraFromToPos(1.25, 1.28, 0.71, false, 2.28, -0.20, 1.91);
		break;
		
		case "mirabelle_47":
            DialogExit();
		    npchar.dialog.currentnode = "mirabelle_42";
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1 && CheckPassengerInCharacter(pchar, "Mary"))
			{
				sld = characterFromId("Mary");
				sld.dialog.currentnode = "IslaMona_2";
				LAi_SetActorType(sld);
				LAi_ActorDialogDelay(sld, pchar, "", 0.0);
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1 && CheckPassengerInCharacter(pchar, "Helena"))
				{
					sld = characterFromId("Helena");
					sld.dialog.currentnode = "IslaMona_2";
					LAi_SetActorType(sld);
					LAi_ActorDialogDelay(sld, pchar, "", 0.0);
				}
				else
				{
					sld = characterFromId("Himenes_companion_1");
					sld.dialog.currentnode = "island_man_2";
					LAi_SetActorType(sld);
					LAi_ActorDialogDelay(sld, pchar, "", 0.0);
				}
			}
		break;
		
		case "mirabelle_48":
			dialog.text = "Kapitány úr!";
			link.l1 = "Üdvözlöm magát is, szépségem. Nem unatkozol, ugye?";
			link.l1.go = "mirabelle_49";
		break;
		
		case "mirabelle_49":
			dialog.text = "Ah, kapitány! Mióta megmentettél abból a szörnyû házból, az életem színesebb és vidámabb lett.";
			link.l1 = "Boldog vagy?";
			link.l1.go = "mirabelle_50";
		break;
		
		case "mirabelle_50":
			dialog.text = "Persze, hogy boldog vagyok! És szeretném megosztani ezt a boldogságot önnel... Várni foglak a szobádban, az emeleten.";
			link.l1 = "Micsoda nô...";
			link.l1.go = "mirabelle_51";
		break;
		
		case "mirabelle_51":
			DialogExit();
			LAi_SetActorType(npchar);
		    npchar.dialog.currentnode = "mirabelle_40";
			DoQuestFunctionDelay("IslaMona_ChurchReloadToRoom", 0.5);
			pchar.questTemp.IslaMona.Mirabelle = "true";
		break;
		
		case "mirabelle_52":
			dialog.text = "Kapitány úr!";
			link.l1 = "Üdvözlöm magát is, szépségem. Nem unatkozol, ugye?";
			link.l1.go = "mirabelle_53";
		break;
		
		case "mirabelle_53":
			dialog.text = "Ah, kapitány! Mióta megmentettél abból a szörnyû házból, az életem színesebb és vidámabb lett.";
			link.l1 = "Boldog vagy?";
			link.l1.go = "mirabelle_54";
		break;
		
		case "mirabelle_54":
			dialog.text = "Nagyon! Kivéve...";
			link.l1 = "Értem, kérni akarsz tôlem valamit?";
			link.l1.go = "mirabelle_55";
		break;
		
		case "mirabelle_55":
			dialog.text = "Igen, kapitány úr! Szeretném... megosztani a boldogságomat egy bizonyos férfival...";
			link.l1 = "Nem bánja?";
			link.l1.go = "mirabelle_56";
		break;
		
		case "mirabelle_56":
			dialog.text = "Nem, nem, kapitány. Boldogok lennénk együtt, ezt biztosan tudom. Csak... megengedné?";
			link.l1 = "Maga jobban megérdemli ezt, mint bárki más. De én nem fogok összeházasodni veletek, ne is kérdezd!";
			link.l1.go = "mirabelle_57";
		break;
		
		case "mirabelle_57":
			dialog.text = "Ha-ha! Az én uram! Köszönöm, Kapitány Úr. Nem tudom, mit mondanak önrôl a nagyvilágban, de én mindig a legkedvesebb és legragyogóbb embert láttam önben.";
			link.l1 = "Sok szerencsét, Mirabelle.";
			link.l1.go = "mirabelle_58";
		break;
		
		case "mirabelle_58":
			DialogExit();
			npchar.quest.rodgar = true;
		    npchar.dialog.currentnode = "mirabelle_42";
		break;
		
		// губернатор Картахены
		case "CartahenaMayor":
            dialog.text = "Kibaszott ladrones! Mindegy, a futárunk már úton van Porto Bellóba. Hamarosan megérkezik a századunk és...";
			link.l1 = TimeGreeting()+", Felség. Örülök, hogy egy ilyen gyönyörû kastélyban láthatom. Remélem, megtartja, miután elmentünk. Én a helyedben nem számítanék a századra, ráadásul nem maradunk itt három napnál tovább. Lefogadom, megérti, hogy Porto Bello nemes donijai nem fognak ideérkezni olyan hamar, hogy segítsenek önöknek. Szóval térjünk rögtön a tárgyra, rendben?";
			link.l1.go = "CartahenaMayor_1";
		break;
		
		case "CartahenaMayor_1":
            dialog.text = "Máris az üzletrôl beszélünk? Nézd az ablakot! Nézzétek, mit mûvelnek a gyilkosok az utcákon és a házakban!";
			link.l1 = "Ó, felség, ez semmi ahhoz képest, amit ôk fognak csinálni, ha nem leszel elég együttmûködô. Remélem, megérti, kik ezek az emberek...";
			link.l1.go = "CartahenaMayor_2";
		break;
		
		case "CartahenaMayor_2":
            dialog.text = "Tudom, hogy mire képes az az átkozottul gonosz ember, Charlie Prince kalóz! Tudom, ki a fônöke! Idôvel kiégetjük a Hispaniolán lévô banditák rejtekhelyét! Mennyiért?";
			link.l1 = "Ne pazarolja a szavakat, kedves kormányzóm. Jobb, ha ad nekem 250 000 pesót.";
			link.l1.go = "CartahenaMayor_3";
		break;
		
		case "CartahenaMayor_3":
            dialog.text = "Micsoda?! A pimaszságod határtalan! Ez rablás!";
			link.l1 = "Ez rablás, természetesen. Mi más lehetne? Gyûjtsétek össze az eliteket, a kereskedôket és a kereskedôket, gyûjtsétek az aranyat egy nagy ládába, mert különben... Sokkal rosszabbá teszem a helyzetet neked és a népednek.";
			link.l1.go = "CartahenaMayor_4";
		break;
		
		case "CartahenaMayor_4":
            dialog.text = "Kibaszott kalóz! Bastardo! Eretnek! Vete a la mierda!";
			link.l1 = "A mocskos nyelved miatt 300 000-re emelem a váltságdíjat.";
			link.l1.go = "CartahenaMayor_5";
		break;
		
		case "CartahenaMayor_5":
            dialog.text = "QUEMAR EN EL INFIERNO, HIJO DE PUTA!!!";
			link.l1 = "350 000. Tovább akarsz menni?";
			link.l1.go = "CartahenaMayor_6";
		break;
		
		case "CartahenaMayor_6":
            dialog.text = "Nincs ennyi pénz a városban!";
			link.l1 = "Hazudsz. Ez nem lehet. Legalább egymilliót össze tudnánk itt gyûjteni, de attól tartok, nincs elég idônk rá. Ezért leszek kedves és nagylelkû. Tudod az összeget. Menj és szerezd meg.";
			link.l1.go = "CartahenaMayor_7";
		break;
		
		case "CartahenaMayor_7":
            dialog.text = "Még egyszer mondom neked, Charlie Prince: Cartagenában nincs ilyen pénz!";
			link.l1 = "Ó... hogy lehetsz ilyen unalmas. Bicska! Keress körül és hozz ide mindenkit, akit találsz. Keressetek jól! És mi itt várunk, te kegyelmes...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_CartahenaInResidence");
		break;
		
		case "CartahenaMayor_8":
            dialog.text = "";
			link.l1 = "Hé, senor 'Stubborn'! Nem gondolta meg magát a jó Cartagena városában történô pénzgyûjtéssel kapcsolatban?.... Mi történt, miért vagy ilyen komolyan?! Jól vagy? Hozzak neked egy kis vizet?";
			link.l1.go = "CartahenaMayor_9";
		break;
		
		case "CartahenaMayor_9":
            dialog.text = "";
			link.l1 = "Ha jól értem, ez a két hölgy a feleséged és a lányod, igazam van? A harmadik lány úgy néz ki, mint egy szolga, úgy tûnik, nem törôdsz vele, úgyhogy nem fogunk neki ártani, de ez a két szépség talán kap egy kis figyelmet a fegyveres testvéremtôl, Senor Cutlass-tól. Úgy tûnik, tetszenek neki, senor. És akkor mi van? Te fogod intézni a váltságdíjat?";
			link.l1.go = "CartahenaMayor_10";
		break;
		
		case "CartahenaMayor_10":
            dialog.text = "I... Idôre lesz szükségem.";
			link.l1 = "Aha! Most már beszélsz! Szóval, ki itt a fattyú? Leszarta, hogy az embereim terrorizálják a polgárait, de a két nôje teljesen más tészta, igaz? Te mertél velem alkudozni, bunkó? Megmutatom, mit jelent keresztbe tenni Charlie Prince-nek!";
			link.l1.go = "CartahenaMayor_10x";
		break;
		
		case "CartahenaMayor_10x":
            dialog.text = "";
			link.l1 = "Menj és szedd össze a kibaszott váltságdíjat. 350 000 és egy pesóval sem kevesebb. Egy napotok van. Mi itt maradunk, iszunk egy kis bort, és elvegyülünk ezekkel az édes nôkkel... Légy gyors, amigo, különben én és a barátom, Senor Cutlass, beleszeretünk a szépségeidbe, és akkor neked is váltságdíjat kell fizetned értük. Elôre! Indulás!";
			link.l1.go = "CartahenaMayor_11";
		break;
		
		case "CartahenaMayor_11":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "Mtraxx_CartahenaResidenceWait", 5.0);
		break;
		
		case "CartahenaMayor_12":
			AddMoneyToCharacter(pchar, 350000);
            dialog.text = "Fogd a vérdíjadat, Charlie herceg!";
			link.l1 = "Összegyûjtötted a váltságdíjat? Pompás! De egy órát késtél, kedves kormányzóm. Ez a plusz egy óra megértette velem és a Cutlass-szal, hogy az életünk túlságosan unalmas lesz e szépségek nélkül, akik olyan kedvesek és beszédesek voltak velünk...";
			link.l1.go = "CartahenaMayor_13";
		break;
		
		case "CartahenaMayor_13":
            dialog.text = "Te... te!";
			link.l1 = "Á, túlságosan ideges vagy a munkád miatt, barátom. Csak vicceltem... Bicska! Gyerünk, indulunk!";
			link.l1.go = "CartahenaMayor_14";
		break;
		
		case "CartahenaMayor_14":
            DialogExit();
			AddQuestRecord("Roger_9", "7");
			AddDialogExitQuestFunction("Mtraxx_CartahenaToFort");
		break;
		
		// Камилла
		case "camilla":
			PlaySound("Voice\English\hambit\Girls_3.wav");
            dialog.text = "Ó, szóval ez itt Charlie Herceg, a híres kalóz, a spanyol déli partok réme!";
			link.l1 = RandSwear()+"Heh, nem is tudtam, hogy ilyen népszerû vagyok Tortugán. Mi a neved, édes lány?";
			link.l1.go = "camilla_1";
		break;
		
		case "camilla_1":
            dialog.text = "A nevem Camilla.";
			link.l1 = "Camilla... Ismertem egy ugyanilyen nevû lányt Franciaországban. Olyan régen volt!";
			link.l1.go = "camilla_2";
		break;
		
		case "camilla_2":
			PlaySound("ambient\tavern\orijka_003.wav");
            dialog.text = "";
			link.l1 = "(hányva) ... basszus....Sajnálom hercegnôm, de Prince ma este eléggé részeg. Szóval... hum... miért jöttél hozzám?";
			link.l1.go = "camilla_3";
		break;
		
		case "camilla_3":
            dialog.text = "Több okból is. Vagy talán semmiért.";
			link.l1 = "Istenem, ez túl bonyolult. Úgy tûnik, te egy rejtély vagy, kislány.";
			link.l1.go = "camilla_4";
		break;
		
		case "camilla_4":
            dialog.text = "Minden lánynak kell, hogy legyen egy rejtélye.";
			link.l1 = "Úgy tûnik, azt akarod, hogy megoldjam ezt a rejtélyt. Nem? Én vagyok a lányos' rejtélyek megoldásának mestere, esküszöm! Elmenjünk egy kocsmába, és igyunk egy kis bort? Megszerzem neked a legjobb finomságot!";
			link.l1.go = "camilla_5";
		break;
		
		case "camilla_5":
            dialog.text = "Mmm... Szeretem a kemény fiúkat. De nem fogok bort inni a földszinten részeg aljasok közelében. Szerezz nekünk egy szobát, ott iszunk és beszélgetünk.";
			link.l1 = RandSwear()+"Dögös vagy! Gyere utánam!";
			link.l1.go = "camilla_6";
		break;
		
		case "camilla_6":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			pchar.quest.mtraxx_retribution_tavern.win_condition.l1 = "locator";
			pchar.quest.mtraxx_retribution_tavern.win_condition.l1.location = "Tortuga_town";
			pchar.quest.mtraxx_retribution_tavern.win_condition.l1.locator_group = "reload";
			pchar.quest.mtraxx_retribution_tavern.win_condition.l1.locator = "reload4_back";
			pchar.quest.mtraxx_retribution_tavern.function = "Mtraxx_RetributionToTavern";
		break;
		
		case "camilla_7":
			PlaySound("Voice\English\hambit\Gr_officiant_1.wav");
            dialog.text = "Gyerünk, gyerünk... Öntsd ki, ne várakoztasd meg a hölgyet!";
			link.l1 = "Persze, édesem!";
			link.l1.go = "camilla_8";
		break;
		
		case "camilla_8":
			LAi_Fade("", "");
			PlaySound("ambient\tavern\krujki_005.wav");
			PlaySound("ambient\tavern\naliv_003.wav");
			PlaySound("ambient\tavern\glotok_001.wav");
			WaitDate("", 0, 0, 0, 1, 5);
            dialog.text = "Mmm... Ha belegondolok, itt vagyok egyedül Charlie Prince-szel, és kiváló bort iszom...";
			link.l1 = "Élvezni fogod ezt az utat velem, ígérem! Charlie Prince gyengéd és kedves a hölgyekkel, akik alávetik magukat neki. Aláveted magad, hercegnôm?";
			link.l1.go = "camilla_9";
		break;
		
		case "camilla_9":
            dialog.text = "Tee-hee... Természetesen, édesem! Az ígéreteid olyan csábítóan hangzanak, tudod...";
			link.l1 = "Nos, akkor ne vesztegessük az idôt, szépségem?";
			link.l1.go = "camilla_10";
		break;
		
		case "camilla_10":
            dialog.text = "Ó! Imádom! Igazi férfiak!...";
			link.l1 = "...";
			link.l1.go = "camilla_11";
		break;
		
		case "camilla_11":
            DialogExit();
			pchar.GenQuest.FrameLockEsc = true;
			bDisableCharacterMenu = true;
			ResetSound();
			WaitDate("", 0, 0, 0, 2, 30);
			SetLaunchFrameFormParam("", "", 0, 5.1);
			SetLaunchFrameFormPic("loading\inside\censored1.tga");
			PlayStereoSound("sex\sex2.wav");
			LaunchFrameForm();
			if(IsEquipCharacterByArtefact(pchar, "totem_03")) 	
			{
				AddCharacterHealth(pchar, 6);
				AddCharacterMaxHealth(pchar, 1.0);
			}
			else AddCharacterHealth(pchar, 3);
			LAi_SetCurHPMax(pchar);
			DoQuestCheckDelay("Mtraxx_RetributionRoomSex", 5.1);
		break;
		
		case "camilla_12":
            dialog.text = "Mmm...";
			link.l1 = "Tetszett, hercegnôm?";
			link.l1.go = "camilla_13";
		break;
		
		case "camilla_13":
            dialog.text = "Persze! Remélem, én is tetszettem neked.";
			link.l1 = "Heh! Még a fejem is kristálytiszta most!";
			link.l1.go = "camilla_14";
		break;
		
		case "camilla_14":
            dialog.text = "Herceg, van egy kérésem a számodra. Segítenél nekem?";
			link.l1 = "Hozok neked egy csillagot az égbôl, ha-ha! Gyerünk, gyerünk.";
			link.l1.go = "camilla_15";
		break;
		
		case "camilla_15":
            dialog.text = "El kell jutnom La Vegába, hogy meglátogassam Tyrexet. Félek tôle, de ti együtt üzleteltek. Kérlek, vigyél el hozzá.";
			link.l1 = "Ezt nézzétek! És miért akarna egy ilyen kedves, törékeny lány találkozni a Kódex Ôrzôjével?";
			link.l1.go = "camilla_16";
		break;
		
		case "camilla_16":
            dialog.text = "Ez az édes, törékeny lány szeretne egy kis pénzt keresni. A néhai apám és a testvéreim nem sok pénzt hagytak rám. Tyrex ezt helyre tudja hozni.";
			link.l1 = "Tényleg? És hogyan? Akarsz egy spanyol gálya nyomára bukkanni? Ha-ha!";
			link.l1.go = "camilla_17";
		break;
		
		case "camilla_17":
            dialog.text = "A karavánok és városok kifosztása kemény fickók' üzlete, akárcsak te, édesem. Van egy másik üzletem Marcusnak. Információkat vásárol és ad el, igaz? Van valamim... Én magam nem tudom használni, de ô igen. Én elégedett leszek, ha csak egy kis kamatot kapok belôle.";
			link.l1 = "Érdekes! Mesélj még.";
			link.l1.go = "camilla_18";
		break;
		
		case "camilla_18":
            dialog.text = "Hm... nem is tudom...";
			link.l1 = "Ó, ugyan már. Tekintsen engem Tyrex jobbkezének, mostanra már sokat kutattam neki, higgye el. Ha az információd megéri - én magam is megveszem.";
			link.l1.go = "camilla_19";
		break;
		
		case "camilla_19":
            dialog.text = "Rendben. Többet mondok, de nem mondok részleteket, amíg nem kapom meg a pénzt. Megegyeztünk, drágám?";
			link.l1 = "Persze, szépfiú. Charlie Prince nem szúrja el a partnereit... tudod, hogy értem, ha-ha-ha-ha! Folytasd csak, csupa fül vagyok.";
			link.l1.go = "camilla_20";
		break;
		
		case "camilla_20":
            dialog.text = "... Az apám egy kereskedelmi szkúnán volt kapitány. Egy nap valahogy tudomást szerzett egy régi spanyol bányásztelepülésrôl, amely mélyen a Main dzsungelében feküdt. Húsz évvel ezelôtt földrengés pusztította el. A bányászok elhagyták, és a titkos járatok feledésbe merültek. Egyet kivéve. Apám találta meg\nVitte oda a testvéreimet és egy idegenvezetôt, és ôk megtalálták a helyet, amely tele volt évekkel ezelôtt bányászott és olvasztott arannyal. Rengeteg aranyat. Legalább egymillió pezó. Apám visszatért egy hajóra, hogy embereket szerezzen az arany elszállításához, de megdöbbenve tapasztalta, hogy eltûnt. Úgy tûnik, az elsôtisztje lázadást szított, és otthagyták ôt és a testvéreimet az elhagyatott partokon\népítettek egy hosszú csónakot, és végighajóztak a part mentén, kétségbeesetten keresve egy lakott helyet, de... (zokog) egy vihar csapott le rájuk, és az én (zokog) testvéreim meghaltak. Apám életben maradt, de nem sokáig élt, miután hazatért - a testvéreim halála lassan napról napra megölte ôt. Mielôtt meghalt, készített egy térképet, és nekem adta\nAzt mondta, hogy ha férjhez megyek, a férjem menjen oda, szerezze meg az aranyat, és úgy fogunk élni, mint a királyok. Persze, hogy így lesz, de én nem engedem, hogy a férjem bemenjen azokba az elátkozott dzsungelekbe. Még egyszer nem! Egymillió pezó, mondta apám, de ez nem az én súlycsoportom. Ilyen díjat csak a legjobb és legkeményebb emberek kaphatnak - olyanok, mint Marcus Tyrex. Ezért fogok találkozni vele.";
			link.l1 = "Mennyit kér a térképért?";
			link.l1.go = "camilla_21";
		break;
		
		case "camilla_21":
            dialog.text = "Kétszáz aranydublon. Ez semmi a díjhoz képest. Tyrex bele fog egyezni, ebben biztos vagyok. Olyan gazdag, mint Crassus.";
			link.l1 = "Heh! És mi van, ha ez az egész csak egy trükk?";
			link.l1.go = "camilla_22";
		break;
		
		case "camilla_22":
            dialog.text = "Öngyilkosnak tûnök? Megpróbálok keresztbe tenni Tyrexnek? Édesem, jobb szegénységben élni, mint egyáltalán nem élni. Szóval, elviszel oda? Kérlek...";
			link.l1 = "Hol van a térkép? Megmutatnád nekem?";
			link.l1.go = "camilla_23";
		break;
		
		case "camilla_23":
            dialog.text = "A papom biztonságban tartja. Megmutatom neked 200 dublonnáért.";
			link.l1 = "Rendben van! Megveszem. Az idegenek a kocsmákban néha sokkal többet kérnek a szemétért.";
			link.l1.go = "camilla_24";
		break;
		
		case "camilla_24":
            dialog.text = "Tényleg? Igaz ez, drágám? Annyira örülök, hogy nem megyek La Vegába! Hogy ôszinte legyek, félek Marcustól. Egyébként én is félek tôled... de egy kicsit kevésbé.";
			link.l1 = "Egy ilyen édes kislánynak nem kell félnie tôlem. Hová vigyem a pénzt?";
			link.l1.go = "camilla_25";
		break;
		
		case "camilla_25":
            dialog.text = "Kössünk egy üzletet: keress meg a templomunkban bármelyik nap reggel tíz órától délután egy óráig. Sokkal nagyobb biztonságban fogom érezni magam e szent hely védelme alatt. Ott fogjuk megkötni az üzletet.";
			link.l1 = "Még mindig félsz tôlem? Ha-ha! Ne Camilla, nem foglak becsapni. Charlie herceg nem tenne ilyen aljas dolgot kétszáz dublonnáért, ráadásul ki akarlak segíteni.";
			link.l1.go = "camilla_26";
		break;
		
		case "camilla_26":
            dialog.text = "Csodálatos. Rendben van, szépfiú, várni fogok rád... Köszönöm a ma este együtt töltött csodálatos idôt! Annyira boldog vagyok, hogy találkoztunk!";
			link.l1 = "Hamarosan találkozunk, szépségem.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_RetributionOutRoom");
		break;
		
		case "camilla_27":
			PlaySound("Voice\English\hambit\Girls_3.wav");
            dialog.text = "Szóval? Elhoztad a pénzt, édesem?";
			if (PCharDublonsTotal() >= 200) // belamour legendary edition
			{
				link.l1 = "Igen. Itt az aranyad, és most add ide a térképet.";
				link.l1.go = "camilla_28";
			}
			else
			{
				link.l1 = "Mindjárt megyek érte.";
				link.l1.go = "camilla_27x";
			}
		break;
		
		case "camilla_27x":
            DialogExit();
			npchar.dialog.currentnode = "camilla_27";
		break;
		
		case "camilla_28":
			RemoveDublonsFromPCharTotal(200); // belamour legendary edition
			GiveItem2Character(pchar, "mapEnrico"); 
            dialog.text = "Köszönöm, drágám... Tessék, itt van. Apám emlékére esküszöm - ez a térkép nem hamisítvány, egyenesen oda vezet, ahová menned kell...";
			link.l1 = "Jó, édesem. Mi lenne, ha megünnepelnénk az egyezségünket, mint a múltkor?";
			link.l1.go = "camilla_29";
		break;
		
		case "camilla_29":
            dialog.text = "Szeretnék, herceg, de a papom elôtti gyónásra készülök, ezért most kénytelen vagyok távol maradni minden kísértéstôl. Csináljuk legközelebb.";
			link.l1 = "Uh, csak ugratsz, kislány. Rendben! Nincs vesztegetni való idônk: mindjárt vitorlát bontunk. Esküszöm, megduplázom a kamatot, ha apád térképe valóban elvezet az aranyhoz.";
			link.l1.go = "camilla_30";
		break;
		
		case "camilla_30":
            dialog.text = "Olyan nagylelkû vagy, drágám. Bon voyage!";
			link.l1 = "Yo-ho-ho!";
			link.l1.go = "camilla_31";
		break;
		
		case "camilla_31":
            DialogExit();
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
			AddQuestRecord("Roger_10", "2");
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			pchar.quest.mtraxx_retribution_carataska.win_condition.l1 = "location";
			pchar.quest.mtraxx_retribution_carataska.win_condition.l1.location = "shore10";
			pchar.quest.mtraxx_retribution_carataska.function = "Mtraxx_RetributionCarataska";
			pchar.questTemp.Mtraxx.Retribution = "carataska";
		break;
		
		case "camilla_sleep":
            dialog.text = "A fattyúid megölték az apámat és a testvéreimet. A Cartagena elleni támadásotok minden ottani családnak gyászt hozott. Remélem, most már féltek, annyira féltek, mint mi, Cartagena polgárai, amikor a bestiáitok jól érezték magukat az utcákon és a házakban. A pokolban fogsz égni, Charlie Prince.";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionSleep4");
		break;
		
		// дон Энрико - народный мститель
		case "enrico":
			PlaySound("Voice\English\LE\Zorro\Don_Enriko_01.wav");
            dialog.text = "Kevés olyan dolog van a világon, ami annyira örülök, mint amikor a patkányokat nézem, ahogy a dobozban széttépik egymást!\nCsak a legerôsebb és legundorítóbb patkány marad életben. Akkor már csak annyi a dolgod, hogy megszorongasd...";
			link.l1 = "Argh! Ki vagy te?!";
			link.l1.go = "enrico_1";
		break;
		
		case "enrico_1":
			PlaySound("Voice\English\LE\Zorro\Don_Enriko_02.wav");
            dialog.text = "Én don Enrico vagyok. Az angol söpredék Foxnak hív, a hollandok Vosnak, a franciák Renaudnak. De én jobban szeretem a spanyol otthoni becenevemet - Zorro. Büntetem a gonoszt, amely kínozza és terrorizálja a köznépet, a nép legkevésbé védett részét\nEz a mai tárgyalás Marcus Tyrex négy kalózáról fog ítélkezni: Boldog Jeffry, Pelly a Vágtató, Luke a Leprechaun és Charlie Prince - ezek a banditák felelôsek a Meridában és Cartagenában elkövetett mészárlásért. Az utolsó Szépfiú Jean nevû fattyú nem jelent meg itt, ô lehet a legokosabb közülük.";
			link.l1 = "Micsoda?!";
			link.l1.go = "enrico_2";
		break;
		
		case "enrico_2":
            dialog.text = "Te egy szemétláda vagy, Charlie Prince, de nem vagy idióta. Azt hiszem, már rájöttem. Ez egy csapda, amit én állítottam nektek hamis térképek, okmányok, szavak és arany és ezüst ígéretek segítségével. Mindannyiótokat becsalogattalak ezekbe a tömlöcökbe, ahol egymást pusztítottátok el undorító tulajdonságaitoktól vezérelve: irigység, kapzsiság, aljasság és gátlástalanság. Ez valóban csak egy nemezis volt!";
			link.l1 = "Camilla... Tudhattam volna, hogy valami nincs rendben azzal a lánnyal!";
			link.l1.go = "enrico_3";
		break;
		
		case "enrico_3":
            dialog.text = "Egy Camilla nevû lány békés életet élt Cartagenában az apjával és a testvéreivel, éppen férjhez készült menni, amikor te és az ördögeid megtámadtátok a várost. A kalózaitok mindenkit megöltek, aki közel állt hozzá, ezért a lány megesküdött, hogy bármit megtesz, hogy megbosszulja ôket. Kemény szerep volt ez számára. Még egy olyan fattyúval is le kellett feküdnie, aki a családja haláláért felelôs. Félek elképzelni, mit érezhetett a tett közben\nA szegény lány napokig a templomban imádkozott megbocsátásért. A véres dublont, amit tôled kapott, azoknak az áldozatoknak adományozta, akik a legjobban szenvedtek a támadásodtól. Most egy kolostorban van, szegény lélek. Összetörted az életét, te szemétláda! Gondoljatok bele! Gondoljatok bele, hány Camillát, Isabelát, Rositát erôszakoltatok meg és tettetek özveggyé! Hány Juant, Carlosét, Pedrót öltetek meg és kínoztatok meg a fattyak!\nEmlékezzetek Meridára! Emlékezzetek, hogyan ígértétek meg a város vezetôjének, hogy nem gyújtjátok fel a várost, majd az egész helyet porig égettétek!";
			link.l1 = "Soha nem akartam ezt tenni! Amikor elhagytam a rezidenciát, már mindenütt tûz volt. Ezt nem én rendeltem el...";
			link.l1.go = "enrico_4";
		break;
		
		case "enrico_4":
            dialog.text = "Te vagy a felelôs a kalózaid tetteiért. Halottak lógnak a nyakadon, és hamarosan a pokolba hurcolnak!";
			link.l1 = "Gyertek akkor! Huh? Harcoljatok velem! Ezt akarod, igaz?! Akkor csináljuk!";
			link.l1.go = "enrico_5";
		break;
		
		case "enrico_5":
            PlaySound("Voice\English\LE\Zorro\Don_Enriko_03.wav");
            if (CharacterIsAlive("Tonzag") && CheckPassengerInCharacter(pchar, "Tonzag"))
			{
				dialog.text = "Nem, Charlie Prince. Ne nyúlj a fegyveredért, nincs értelme... Könnyedén megölhetnélek, de a gyors halál nem elég egy olyan szemétládának, mint te. Örökre ebben a börtönben maradsz. Az ajtót, amin ide bejöttél, kívülrôl egy kô zárja el, a mögöttem lévô ajtó is el lesz zárva, ráadásul erôs rácsok is védik. Ez az, nincs más kiút, csak ez a két ajtó\nMi a... Bezártam az összes ajtót!";
				link.l1 = "Mi folyik itt...";
				link.l1.go = "exit";
				AddDialogExitQuest("Mtraxx_RetributionEnricoAndTonzag");
			}
			else
			{
				dialog.text = "Nem, Charlie Prince. Ne nyúlj a fegyveredért, nincs értelme... Könnyedén megölhetnélek, de a gyors halál nem elég egy olyan szemétládának, mint te. Örökre ebben a börtönben maradsz. Az ajtót, amin ide bejöttél, kívülrôl egy kô zárja el, a mögöttem lévô ajtó is el lesz zárva, ráadásul erôs rácsok is védik. Ez az, nincs más kiút, csak ez a két ajtó\nalatt víz van, így lesz elég idôd átgondolni a tetteidet. Egyedül itt, a sötétben talán megbánod, amit tettél, mielôtt éhen halsz vagy megôrülsz\nEgy utolsó dolog - a lenti kincs hamisítvány. Az aranyrudak nem mások, mint színes ólom. A doubloonok viszont valódiak, de csak kevés van belôlük, ami elég ahhoz, hogy a ládák belsejében lévô köveket elfedje. Méltó vég a kalózoknak, mi? Egy hamis kincsért öltétek egymást, herceg. Isten veled. Imádkozz a bûnös lelkedért, Charlie herceg, ha még emlékszel rá...";
		// belamour legendary edition -->
				link.l1 = "Épp most öltem meg Marcus Tyrex teljes elôôrsét! Azt hiszed, ezek a rozsdás rudak megállítanak?! A saját fejeddel fogom eltörni!";
				link.l1.go = "enrico_5a";
				link.l2 = "Talán megérdemeltem. De nem adom fel, hallod?! Megtalálom a módját, mindig megtalálom!";
				link.l2.go = "enrico_5b";
			}
		break;
		
		case "enrico_5a":
			AddCharacterHealth(pchar, 5);
			AddCharacterExpToSkill(pchar, "FencingL", 400);
			AddCharacterExpToSkill(pchar, "FencingS", 400);
			AddCharacterExpToSkill(pchar, "FencingH", 400);
			AddCharacterExpToSkill(pchar, "Pistol", 400);
            DialogExit();
			AddDialogExitQuestFunction("Mtraxx_RetributionEnricoGo");
		break;
		
		case "enrico_5b":
			AddCharacterExpToSkill(pchar, "Leadership", 1200);
			ChangeCharacterComplexReputation(pchar, "nobility", 15);
            DialogExit();
			AddDialogExitQuestFunction("Mtraxx_RetributionEnricoGo");
		break;
		// <-- legendary edition
		
		case "enrico_Tonzag_1":
			dialog.text = "Igazad van, az ajtó megbízható, még ha öreg is. Köszönöm, hogy nem engedted le a kaput - feltartott volna. De nem sokáig.";
			link.l1 = "Hercule Tonzag, Kopasz Gaston! Sejthettem volna, hogy egy olyan valaki, mint te, a herceg és a hozzá hasonlók pártjára áll. Szerencsés vagyok, hogy itt találkoztam veled.";
			link.l1.go = "enrico_Tonzag_2";
			sld = CharacterFromID("Zorro");
			CharacterTurnToLoc(sld, "quest", "door");
		break;
		
		case "enrico_Tonzag_2":
			dialog.text = "Szerencsés, azt mondja? Nos, ha sietsz a halálba... Bár azt hittem, hogy nem, hiszen hagytad éhen halni, ahelyett, hogy szembenéztél volna vele.";
			link.l1 = "Gyávasággal vádolsz? Milyen ostoba vagy. Ahogy a Hercegnek is mondtam, a halál túl könnyû büntetés lenne számára. Ô nem ellenfél számomra.";
			link.l1.go = "enrico_Tonzag_3";
		break;
		
		case "enrico_Tonzag_3":
			dialog.text = "És te nem vagy ellenfél számomra, Don.";
			link.l1 = "Tíz évvel ezelôtt? Igen, persze. De most? Aligha. Ráadásul...";
			link.l1.go = "enrico_Tonzag_4";
		break;
		
		case "enrico_Tonzag_4":
			dialog.text = "Ráadásul mi? Mi ez a drámai szünet? Bár, figyelembe véve a farsangi maszkodat... Kicsit korai lenne számolni velem, nem?";
			link.l1 = "Betörted az ajtót, de a nyers erô önmagában nem lesz elég nálam. Milyenek a reflexeid? A látásod? Csak egy szemmel. Még mindkettô megvan.";
			link.l1.go = "enrico_Tonzag_5";
		break;
		
		case "enrico_Tonzag_5":
			dialog.text = "Legalábbis egyelôre. Heh-heh.";
			link.l1 = "Porto Bello-ért rosszabb kínzást érdemelsz, mint a herceg!";
			link.l1.go = "enrico_Tonzag_6";
		break;
		
		case "enrico_Tonzag_6":
			dialog.text = "Ó, szóval hallottad, mit tettem? Gondolom, egy darabig még pletykálni fognak róla a tieid között. Akkor tudod, min mentem keresztül.";
			link.l1 = "Öreg vagy, Tonzag, és ezúttal az arroganciád lesz a veszted. És igen, nem most hallottam róla - Cartagena, Merida a te kezed munkája. Akárcsak Porto Bello.";
			link.l1.go = "enrico_Tonzag_7";
		break;
		
		case "enrico_Tonzag_7":
			dialog.text = "Hízelgésnek vettem volna, de nem, nem az én mûvem. Bár távolról hasonlónak tûnhet. Túl amatôr. De még Porto Bellóban is voltak... incidensek.";
			link.l1 = "Incidensek?! Aznap egy ember meghalt... És tekintve, hogy te kezdted azt a mészárlást, még mindig téged hibáztatlak érte, még akkor is, ha te magad nem öltél meg mindenkit. Én téged hibáztatlak minden 'incidentért.'";
			link.l1.go = "enrico_Tonzag_8";
		break;
		
		case "enrico_Tonzag_8":
			dialog.text = "Egy ember, azt mondod... Sokan haltak meg azon a napon. Legyen pontos.";
			link.l1 = "Igazán, nincs szíve, ha ezt mondhatja! De válaszolok: az, akit nem kellett volna megölnöd. Az apámat, Don de la Vegát. Ha ô élne, nem választottam volna ezt az utat, és ti mindannyian életben lennétek.";
			link.l1.go = "enrico_Tonzag_9";
		break;
		
		case "enrico_Tonzag_9":
			dialog.text = "Fogd be a szád, kölyök. A drága feleségem... szintén ott halt meg.";
			link.l1 = "Részvétet vársz? Nem fogsz kapni. Ez az Úr büntetése számodra. Úgy tûnik, van szíved - kicsi és fekete. És a pengémmel fogom megtalálni.";
			link.l1.go = "enrico_Tonzag_10";
		break;
		
		case "enrico_Tonzag_10":
			dialog.text = "Ó, a dráma a szívemrôl. Tévedsz, ha azt hiszed, hogy láttál már rosszabbat, mint én.";
			link.l1 = "Azt hiszed, hogy csak egy elkényeztetett gazdag fiatal vagyok, aki pénzt pazarol? Tudd meg ezt: Egy dublont sem költöttem szerencsejátékra vagy nôkre! Mindent a hozzád hasonlók elleni harcba fektettem, és ennek szenteltem az életemet!";
			link.l1.go = "enrico_Tonzag_11";
		break;
		
		case "enrico_Tonzag_11":
			dialog.text = "És miért? Nem tûnik túl sikeresnek. A kereskedelmi útvonalak még mindig hemzsegnek a kalózoktól. Egyedül vagy a keresztes hadjáratodban. És ôk egy egész légió.";
			link.l1 = "Valakinek muszáj. Legalább valakinek. És talán azzal, hogy megölök egy kalózkapitányt, megmentek néhány életet.";
			link.l1.go = "enrico_Tonzag_12";
		break;
		
		case "enrico_Tonzag_12":
			dialog.text = "Bolond. Idealista. És... bizonyos értelemben nemes, mondhatnám, ha nem lennének a módszereid. Becstelen, mint az ellenségei. Végül is, maga sem... jobb.";
			link.l1 = "Ne prédikálj nekem! A becsület azoké, akik követik a törvényeit. Megértelek. Úgy gondolkodom, mint te. És büntetek.";
			link.l1.go = "enrico_Tonzag_13";
		break;
		
		case "enrico_Tonzag_13":
			dialog.text = "Igazad van. Téged tanítani értelmetlen. Szóval, nem fogunk békésen elválni. De te nem érdekelsz engem, Don Enrico. Még az idômet sem éri meg.";
			link.l1 = "Mit akarsz...";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionEnricoAndTonzag2");
		break;
		
		case "enrico_Tonzag_14": // после выстрела в Зорро в подземелье
            dialog.text = "Jól van, kapitány? Figyelmeztettem, hogy legyen óvatos. Hallgatnom kellett volna a megérzésemre.";
			link.l1 = "Igen, jól vagyok. Köszönöm, Hercule. Csak egy kicsit...";
			link.l1.go = "enrico_Tonzag_15";
		break;
		
		case "enrico_Tonzag_15":
            dialog.text = "...sokkolt? Ne félj beismerni - ez normális egy ilyen korban és egy ilyen helyzetben. Különben is, ez a Don jól manipulál.";
			link.l1 = "Aha. Bár úgy tûnt, hogy fél tôled. Ez meglepett. De ez is visszahozott az eszembe. Egyébként, még mindig él? Úgy tûnik. Nem kellene háttal állnod neki.";
			link.l1.go = "enrico_Tonzag_16";
		break;
		
		case "enrico_Tonzag_16":
            dialog.text = "Élve, de megdöbbenve. Kezd magához térni. A fejét kellett volna céloznia, nem a törzsét - kiderült, hogy a mi nemes hidalgónk könnyû, de erôs mellényt visel a kabátja alatt. Heh, még Fleetwood is ragaszkodott egy egyszerû ponthoz. Máskülönben már egy vértócsa lenne itt.";
			link.l1 = "És hogy kerültél ide? Ugyanott, ahol ô?";
			link.l1.go = "enrico_Tonzag_17";
		break;
		
		case "enrico_Tonzag_17":
            dialog.text = "Erre most nincs idô. Hamarosan talpra áll. Egyelôre felemeljük ezt a kaput.";
			link.l1 = "Mi... mi? Persze, lehet, hogy te vagy Herkules, de...";
			link.l1.go = "enrico_Tonzag_18";
		break;
		
		case "enrico_Tonzag_18":
            dialog.text = "Az én fiatalkoromban a férfiakat keményre kovácsolták. Ezeknek a zsanéroknak rövidek a csapjai. Gyerünk, segítsen nekem, kapitány - lehet, hogy Herkules vagyok, de öregszem.";
			link.l1 = "Rendben, háromra! És emeljük!";
			link.l1.go = "enrico_Tonzag_19";
		break;
		
		case "enrico_Tonzag_19":
            DialogExit();
			locCameraSleep(true);
			LAi_FadeLong("Mtraxx_RetributionEnricoAndTonzag6", "");
		break;
		
		case "enrico_Tonzag_20": // окружили Зорро
            dialog.text = "Azt hiszed, hogy minden tervemet tönkretetted és nyertél? Ez persze váratlanul ért, de azért sok mindent számításba vettem!";
			link.l1 = "Mint az a könnyû mellvért a ruhád alatt. Miért az, és nem egy teljes köpeny a tetején? Csak azért, hogy a kabátodat mutogasd?";
			link.l1.go = "enrico_Tonzag_21";
		break;
		
		case "enrico_Tonzag_21":
            dialog.text = "Nem vagyok szûz, herceg. Az okok pusztán praktikusak - a teljes mellvért túlságosan korlátozza a mozgásomat. Mindenkinek megvan a saját megközelítése.";
			link.l1 = "Pedig itt vagyok én, egy francia, aki már hozzászokott a mellény viseléséhez, nem úgy, mint egy spanyol. Az irónia. És most mi lesz? Nem tudott csapdába ejteni minket. Mindenre felkészültél... A párbaj is szerepelt a lehetôségek között? Vagy a penge - és még a cuirass is - mindenre való, kivéve az igazi harcokat?";
			link.l1.go = "enrico_Tonzag_22";
		break;
		
		case "enrico_Tonzag_22":
            dialog.text = "Engem is gyávának akarsz nevezni? Ahogy mondtam, hosszú szenvedést érdemelsz, nem pedig párbajban való halált. Mi értelme, ha a lelketeknek nem lesz ideje elviselni és felfogni minden bûnötöket itt, a Földön?";
			link.l1 = "A pokolba vezetô út jó szándékkal van kikövezve, ahogy mondani szokták... És az áldozataitok kínzása nem szennyezné be a saját lelketeket?";
			link.l1.go = "enrico_Tonzag_23";
		break;
		
		case "enrico_Tonzag_23":
            dialog.text = "Soha. Soha. Mert hû maradok magamhoz és az elveimhez.";
			link.l1 = "Aha, nem úgy, mint mi. Annyit mondtál arról, hogy mi aljas söpredék vagyunk, egy csepp becsület nélkül, szóval... miért ne felelnénk meg az elvárásaidnak? Majd mi elintézzük magunkat. Együtt.";
			link.l1.go = "enrico_Tonzag_24";
			link.l2 = "Van egy ajánlatom a számodra, Don Enrico. Kihívlak egy párbajra, itt és most. Mint nemes a nemessel.";
			link.l2.go = "enrico_Tonzag_26";
		break;
		
		case "enrico_Tonzag_24":
            dialog.text = "Hm-m. Máskülönben nem lenne esélyed. Tonzag persze trükkös lesz... Szóval elôször veled foglalkozom.";
			link.l1 = "Mintha hagyná, hogy ezt tedd.";
			link.l1.go = "enrico_Tonzag_25";
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
			AddComplexSelfExpToScill(100, 100, 100, 100);
		break;
		
		case "enrico_Tonzag_25":
            DialogExit();
			EndQuestMovie();
			LAi_SetFightMode(pchar, true);
			
			sld = CharacterFromID("Tonzag");
			LAi_SetImmortal(sld, false);
			LAi_SetCheckMinHP(sld, 1, true, "TonzagRanen");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			
			sld = CharacterFromID("Zorro");
			LAi_SetImmortal(sld, false);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "Mtraxx_RetributionEnricoAndTonzag7");
		break;
		
		case "enrico_Tonzag_26":
            dialog.text = "És te? Egy nemes? Talán egy “herceg vagy,” de kétlem, hogy egy csepp nemesi vér is van benned.";
			link.l1 = "Elárultad nekem az igazi neved. Én is elárulom az enyémet. Charles de Maure vagyok. És eléggé megsértettük egymás becsületét ahhoz, hogy mindkettônknek joga van elégtételt követelni. Védje magát, Don Enrico.";
			link.l1.go = "enrico_Tonzag_27";
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			AddCharacterExpToSkill(pchar, "Leadership", 300);
		break;
		
		case "enrico_Tonzag_27":
            dialog.text = "De ne bánja meg késôbb a döntését.";
			link.l1 = "Sok döntést megbántam már életemben, de ez nem tartozik közéjük. En garde!";
			link.l1.go = "enrico_Tonzag_28";
		break;
		
		case "enrico_Tonzag_28":
			DialogExit();
			EndQuestMovie();
			LAi_SetFightMode(pchar, true);
			
			sld = CharacterFromID("Tonzag");
			LAi_SetImmortal(sld, true);
			LAi_SetActorType(sld);
			
			sld = CharacterFromID("Zorro");
			LAi_SetImmortal(sld, false);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "Mtraxx_RetributionEnricoAndTonzag7");
		break;
		
		case "enrico_Tonzag_29": // после победы над Зорро
            dialog.text = "Jól van, kapitány? A mi nemes hidalgónk nem csak a mellényt viselte - megmérgezte a pengéjét is. Tessék, fogd ezt. Mindig hordok magammal párat, amikor a dzsungelben sétálok - sosem tudhatod, mikor harap egy kígyó, vagy mikor dob egy vörösbôrû mérgezett nyilat.";
			link.l1 = "Köszönöm, Hercule. Köszönöm, Hercule, jól vagyok. Az idôben történô érkezése segített összeszedni magam.";
			link.l1.go = "enrico_Tonzag_30";
			GiveItem2Character(PChar, "potion3");
			LAi_UseAtidoteBottle(pchar);
			LAi_UseAtidoteBottle(npchar);
		break;
		
		case "enrico_Tonzag_30":
            dialog.text = "Szóra sem érdemes. Menjünk, kiviszlek innen - említette a bejáratot kövekkel eltorlaszolva. Találtam egy másik átjárót, egy rövidebb utat.";
			link.l1 = "Mondja, Hercule... mi történt pontosan Porto Bellóban? És mikor?";
			link.l1.go = "enrico_Tonzag_31";
		break;
		
		case "enrico_Tonzag_31":
            dialog.text = "Ma nincs kedvem errôl beszélni. De talán majd valamikor, egy pohár bor vagy valami erôsebb mellett. Most azonban tûnjünk el innen - a porontynak igaza volt, öregszem. Pihenni akarok a hajón.";
			link.l1 = "Akkor menj elôre.";
			link.l1.go = "enrico_Tonzag_32";
		break;
		
		case "enrico_Tonzag_32":
            DoQuestReloadToLocation("Shore10", "goto", "goto2", "Mtraxx_RetributionEnricoAndTonzag8");
		break;
		
		case "mishelle_sleep":
            dialog.text = "Mondd, testvér - hogyan váltál ilyen undorítóvá? Amikor azt mondtam neked, hogy ismerkedj meg a kalózokkal, nem arra gondoltam, hogy városokat gyújtasz fel, ártatlan civileket gyilkolsz és nôket kínzol. Még egy háborút is lehet becsülettel és méltósággal vívni\nSzégyent hoztál a családunkra. Még jó, hogy apánk nincs itt: belehalt volna a szégyenbe, ha megtudja, hogy a fiából kalóz és bandita lett!";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionSleep5");
		break;
		
		case "mishelle_sleep_1":
            dialog.text = "Testvér! Testvér!\nHallasz engem?\nA két ajtó egyike mögött van egy átjáró. Az ajtót ki lehet nyitni. Egy kulcs van a közeledben!\nKeresd meg a lépcsôn. A lépcsôn!...";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionSleep7");
		break;
		
		case "terrax_sleep":
            dialog.text = "Ha-ha-ha-ha, helló, én bátor gyilkosom! Miért vagy ilyen szomorú? A tenger, az arany, a rum és a nôk - mi hiányzik még? Emlékszel az elsô találkozásunkra? Már akkor is mondtam neked - olyan férfiakra van szükségem, akik nem félnek a puskaporszagtól, vagy hogy kivéreztessék a vörös folyókat. Túlszárnyaltad minden reményemet! Igazi kalóz lettél, Charlie Prince! Ha-ha-ha-ha!";
			link.l1 = "";
			link.l1.go = "terrax_sleep_1";
			locCameraSleep(false);
		break;
		
		case "terrax_sleep_1":
            dialog.text = "Egy igazi kibaszott kalóz! Ah-ah-ha-ha-ha!";
			link.l1 = "";
			link.l1.go = "terrax_sleep_2";
		break;
		
		case "terrax_sleep_2":
			Mtraxx_RetributionSleepSkeletons();
            dialog.text = "Ua-ha-ha-ha-ha-ha-ha!!!";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionSleep6");
		break;

		// belamour legendary edition -->
		case "SlavesTrader":
            dialog.text = "Ki vagy te? Mit keresel itt? Válaszolj gyorsan!";
			link.l1 = "Fadeybôl jöttem, egy adag fekete csontért jöttem. Figyelmeztetnie kellett volna téged.";
			link.l1.go = "SlavesTrader_1";
		break;
		
		case "SlavesTrader_1":
            dialog.text = "Hah! Ne izzadj a bôrödön, barátom. Felismertünk téged, Moscovit adott rólad részletes leírást. Azt is kérte, hogy ne sértôdjünk meg az ár miatt. Tehát, figyelembe véve az Öntôl már kapott 10 000 ezüst elôleget. Vagy, ha aranyban fizetsz, akkor csak 50 dublont. Nos, hogy döntöttél? Ne húzd a macska farkát!";
			if(PCharDublonsTotal() >= 50)
			{
				link.l1 = "50 dublont fizetek. Ez sokkal kifizetôdôbb.";
				link.l1.go = "SlavesTrader_Dub";
			}
			if(sti(Pchar.money) >= 10000)
			{
				link.l2 = "10 000 pezót fogok fizetni.";
				link.l2.go = "SlavesTrader_P";
			}
			link.l3 = "Sajnálom, de most nem engedhetek meg magamnak rabszolgákat.";
			link.l3.go = "SlavesTrader_X";
		break;
		
		case "SlavesTrader_Dub":
			RemoveDublonsFromPCharTotal(50);
            dialog.text = "Ez nagyszerû. Jelezz az embereidnek, hogy vigyék az árut.";
			link.l1 = "Természetesen.";
			link.l1.go = "SlavesTrader_End";
		break;
		
		case "SlavesTrader_P":
			AddMoneyToCharacter(pchar, -10000);
            dialog.text = "Ez nagyszerû. Jelezz az embereidnek, hogy vigyék az árut.";
			link.l1 = "Természetesen.";
			link.l1.go = "SlavesTrader_End";
		break;
		
		case "SlavesTrader_End":
			DialogExit();
			AddQuestRecord("Roger_3", "25");
            pchar.questTemp.Mtraxx.GiveMeSlaves = "Deal";
			SetCharacterGoods(pchar, GOOD_SLAVES, (GetCargoGoods(pchar, GOOD_SLAVES) + 50));
			Log_Info("Ötven rabszolgát szállítanak "+PChar.Ship.Name);
			for(i=1; i<=3; i++)
			{
				sld = characterFromId("Mtraxx_SlavesSeller"+i);
				ChangeCharacterAddressGroup(sld, "none", "", "");
				sld.lifeday = 0;
			}
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation("Shore29")], false); 
			DeleteAttribute(&locations[FindLocation("Shore29")],"DisableEncounters"); //энкаунтеры открыть
		break;
		
		case "SlavesTrader_X":
            dialog.text = "Ahogy óhajtja. Erre az árura mindig lesz vevô. Viszlát, barátom.";
			link.l1 = "Viszontlátásra.";
			link.l1.go = "SlavesTrader_EndX";
		break;
		
		case "SlavesTrader_EndX":
			DialogExit();
			AddQuestRecord("Roger_3", "26");
			pchar.questTemp.Mtraxx.GiveMeSlaves = "WithoutSlaves";
			for(i=1; i<=3; i++)
			{
				sld = characterFromId("Mtraxx_SlavesSeller"+i);
				ChangeCharacterAddressGroup(sld, "none", "", "");
				sld.lifeday = 0;
			}
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation("Shore29")], false); 
			DeleteAttribute(&locations[FindLocation("Shore29")],"DisableEncounters"); //энкаунтеры открыть
		break;
		// диалог Гаспара Златозубого Xenon
		case "GasparGold_meeting":
            dialog.text = "Üdvözlöm, kapitány. Ön Charlie Prince, ha nem tévedek? Ne aggódjon, a falaimnak nincsenek fülei. Ôszintén szólva, nem érdekel a neve. Csak az számít, hogy magát ajánlották nekem, ami azt jelenti, hogy üzletet köthetünk.";
			link.l1 = "Üdvözlet neked is, Gaspard ‘Goldentooth.' Mégis nem igazán érdekel, hogy hívnak. Hallottam, hogy esetleg érdekelne néhány csecsebecse?";
			link.l1.go = "GasparGold_meeting_01";
		break;
		
		case "GasparGold_meeting_01":
            dialog.text = "Így van. Senki sem fog nálam jobb árat ajánlani. Nos, kivéve talán a zálogházakat, de azok nem vesznek sokat. Kész vagyok megvenni mindent, amit kínál. Még az értéktárgyakat sem kell személyesen elhoznia hozzám: Van egy hátsó ajtóm, ami egy félreesô mólóra vezet. Nyugodtan eladhatod nekem az összes csecsebecsédet, amit a hajódon lévô ládákban tárolsz.";
			link.l1 = "Nos, ez kiváló! Örülök, hogy megismerhetem.";
			link.l1.go = "GasparGold";
		break;
		
		case "GasparGold_story":
			npchar.mtraxx.story = true;
            dialog.text = "Ez már az én személyes ügyem. Jobb szeretném, ha nem avatkozna bele. Csak annyit mondok, hogy mindent kézben tartok, így kockázatmentesen kereskedhet velem. A többi nem tartozik magára.";
			link.l1 = "Nos, a kockázatmentesség az, ami a leginkább számít! Van még valami, amit meg akartam kérdezni...";
			link.l1.go = "GasparGold";
		break;
		
		case "GasparGold":
			NextDiag.TempNode = "GasparGold";
            dialog.text = "Miben segíthetek? Szeretne megszabadulni néhány felesleges gyöngytôl vagy drágakôtôl? Esetleg arany, ezüst, ékszerek? Mindet megveszem.";
			if(!CheckAttribute(npchar,"mtraxx.story"))
			{
				link.l1 = "Mondd csak, milyen érzés lopott holmikat felvásárolni? Nem félsz a hatóságoktól?";
				link.l1.go = "GasparGold_story";
			}
			link.l2 = "Van itt valami... Szeretném elcserélni egy kis kemény pénzre.";
			link.l2.go = "GasparGold_01";
		break;
		
		case "GasparGold_01":
            dialog.text = "Nos, akkor cseréljünk. Dublont vagy pezót?";
			link.l1 = "Váltsunk pesót - nincs szükség dubloonokra. A rendes pénzt mindenhol elfogadják.";
			link.l1.go = "GasparGold_peso";
			link.l2 = "Kitalálta - nekem kifejezetten dubloonokra van szükségem. Szóval csak azokért fogok eladni.";
			link.l2.go = "GasparGold_dub";
			link.l3 = "Jelenleg nincs semmi eladó. Csak biztos akartam lenni benne, hogy készen állsz értékes tárgyakat vásárolni, ha lesznek. A következô alkalomig!";
			link.l3.go = "exit";
		break;
		
		// окно торговли
		case "GasparGold_peso":
            Nextdiag.CurrentNode = Nextdiag.TempNode;
			DialogExit();
			LaunchItemsTrade(NPChar, 0);
		break;
		
		case "GasparGold_dub":
            Nextdiag.CurrentNode = Nextdiag.TempNode;
			DialogExit();
			LaunchItemsTrade(NPChar, 1);
		break;
		
		// Диалоги после угроз вождю индейцев Кумване
		case "MeridaObsuzhdenie_Bad_1":
            dialog.text = "Még mindig a megfélemlítéshez folyamodsz, Kapitány? Még kintrôl is hallottam fenyegetéseket.";
			link.l1 = "Nem hagytak más választást. Ajándékokat ajánlottam ennek a Tagofa feleségének a segítségéért. Még csak meg sem hallgatott. Most hagyd, hogy a fônök beszéljen velük. És ha nem sikerül észhez térítenie ezeket a makacs fickókat, saját kezûleg tépem ki a szívét a mellkasából. És egyébként ki az a Yahahu?";
			link.l1.go = "MeridaObsuzhdenie_Bad_2";
			ChangeShowIntarface();
		break;
		
		case "MeridaObsuzhdenie_Bad_2":
            dialog.text = "Nem kellett volna elrontanod a kapcsolatot az indiánokkal. Nekünk kalózoknak csak egy kard és egy hajó a szövetségesünk. De mivel ez a te döntésed, hát legyen. És Yahahu egy gonosz démon. Semmi mást nem tudok róla.";
			link.l1 = "...";
			link.l1.go = "MeridaObsuzhdenie_Bad_3";
		break;
		
		case "MeridaObsuzhdenie_Bad_3":
            StartInstantDialog("Mrt_Rocur", "MeridaObsuzhdenie_Bad_4", "Quest\Roger.c");
		break;
		
		case "MeridaObsuzhdenie_Bad_4":
            dialog.text = "Meggyôzésre vesztegetni az idôt, kobold - nem bölcs dolog. Vagy inkább lemondanál a gazdag zsákmányról, és fenntartanád a jó kapcsolatokat az indiánokkal?";
			link.l1 = "...";
			link.l1.go = "MeridaObsuzhdenie_Bad_5";
		break;
		
		case "MeridaObsuzhdenie_Bad_5":
            StartInstantDialog("Lepricon", "MeridaObsuzhdenie_Bad_6", "Quest\Roger.c");
		break;
		
		case "MeridaObsuzhdenie_Bad_6":
            dialog.text = "Inkább mindkettôt.";
			link.l1 = "Nem fog mûködni, ha mindkét táborban egy lábon állsz. Ezúttal nem. Elég a vitából, már mindent megtettünk. Holnap a törzsfônök tájékoztat minket Tagofa döntésérôl, és remélem, nem fog csalódást okozni. Különben... Szélsôséges intézkedéseket kell hoznom. Amit természetesen szeretnék elkerülni.";
			link.l1.go = "MeridaObsuzhdenie_Bad_7";
		break;
		
		case "MeridaObsuzhdenie_Bad_7":
			DialogExit();
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar, "GenQuest.CannotWait"); //разрешить отдыхать
			ChangeShowIntarface();
			
            sld = characterFromId("Lepricon");
			sld.dialog.Filename = "Quest\Roger.c";
			sld.dialog.currentnode = "lepricon_3";
			LAi_SetWarriorType(sld);
			
			sld = characterFromId("Mrt_Rocur");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
		break;
		
		case "MeridaObsuzhdenie_Good_1":
            dialog.text = "Nos, hogy mennek a dolgok? Lesz idegenvezetônk?";
			link.l1 = "Nem, Jean, nem fogunk. A fônök és az egész törzs úgy fél a kapongoktól, mint az ördög a tömjéntôl. Úgy tûnik, el kell hagynunk a tervünket.";
			link.l1.go = "MeridaObsuzhdenie_Good_2";
			ChangeShowIntarface();
		break;
		
		case "MeridaObsuzhdenie_Good_2":
            StartInstantDialog("Lepricon", "MeridaObsuzhdenie_Good_3", "Quest\Roger.c");
		break;
		
		case "MeridaObsuzhdenie_Good_3":
            dialog.text = "Terrax nem fog örülni ennek a fordulatnak.";
			link.l1 = "Szerinted én hihetetlenül boldog vagyok, hogy így alakultak a dolgok? A gyáva Lokono nem akar kikezdeni a Kapongokkal. Sem a meggyôzés, sem a jutalom nem csábítja ôket.";
			link.l1.go = "MeridaObsuzhdenie_Good_4";
		break;
		
		case "MeridaObsuzhdenie_Good_4":
            StartInstantDialog("Mrt_Rocur", "MeridaObsuzhdenie_Good_5", "Quest\Roger.c");
		break;
		
		case "MeridaObsuzhdenie_Good_5":
            dialog.text = "Akkor fenyegetést kell alkalmaznunk. Mondd meg nekik, hogy porig égeted az átkozott falujukat, és addig kínzod a túlélôket, amíg valaki bele nem egyezik, hogy vezessen minket.";
			link.l1 = "Jean, teljesen elment az eszed? Nem fogom felgyújtani ártatlan emberek otthonát. És pláne nem kínzom meg ôket.";
			link.l1.go = "MeridaObsuzhdenie_Good_6";
		break;
		
		case "MeridaObsuzhdenie_Good_6":
            dialog.text = "Charles Prince a jótevô mintaképe. Soha nem vártam tôled ilyen gyengédségkitöréseket.";
			link.l1 = "Ez nem gyengédség, Jóképû. Nos, majd megkínzunk néhány indiait félholtra. Bosszúból egyenesen a kapongok kezére vezet minket, és eltûnik a csak általa ismert ösvényeken. Nem fogom így kockáztatni a népem életét.";
			link.l1.go = "MeridaObsuzhdenie_Good_7";
		break;
		
		case "MeridaObsuzhdenie_Good_7":
            dialog.text = "Ebben az esetben a kobold és én elmegyünk. Itt van ötvenezer ezüst, amiért kiszabadítottál a maracaibói ültetvényekrôl. Egy új hajóra tartogattam. És azt tanácsolom neked: maradj távol Marcus' látóterébôl egy ideig. Viszlát, Charles Prince.";
			link.l1 = "Viszlát, Jean.";
			link.l1.go = "MeridaObsuzhdenie_Good_8";
			AddMoneyToCharacter(pchar, 50000);
		break;
		
		case "MeridaObsuzhdenie_Good_8":
            DialogExit();
			chrDisableReloadToLocation = false;
			ChangeShowIntarface();
			AddQuestRecord("Roger_5", "8b");
			CloseQuestHeader("Roger_5");
			
			sld = characterFromId("Lepricon");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1", "", "", "", "", -1);
			sld.location = "None";
			RemovePassenger(pchar, sld);
			
			sld = characterFromId("Mrt_Rocur");
			LAi_type_actor_Reset(sld);
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1", "", "", "", "", -1);
			sld.location = "None";
			RemovePassenger(pchar, sld);
			
			sld = characterFromId("Terrax");
			sld.dialog.currentnode = "First time";
		break;
		
		// Немезида. Диалоги с офицерами после взрыва бочонков с порохом
		// Тонзаг
		case "Nemezida_Tonzag_1":
            dialog.text = "A környékrôl mindenki ide fog rohanni! Biztos, hogy jó ötlet volt felrobbantani azokat a fákat, kapitány?";
			link.l1 = "A francba! Talán jobb lett volna, ha mindenki fejszével dolgozik... De most már túl késô.";
			link.l1.go = "Nemezida_Tonzag_2";
		break;
		
		case "Nemezida_Tonzag_2":
            dialog.text = "Ez igaz. Meg kell birkóznunk azzal, amink van. Készüljetek.";
			link.l1 = "Te is, Hercule.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada2");
		break;
		
		case "Nemezida_Tonzag_3":
            dialog.text = "Még mindig erre jönnek. Szóval, ezekkel is foglalkozzunk?";
			link.l1 = "Mi van, ha nincs vége? Nem azért vagyunk itt, hogy ilyen bajba kerüljünk.";
			link.l1.go = "Nemezida_Tonzag_4";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Tonzag_4":
            dialog.text = "Nos, mindennek vége van... De igazad van. Vonuljunk vissza. És gyorsan.";
			link.l1 = "Siessünk!";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada4");
		break;
		
		case "Nemezida_Tonzag_5":
            dialog.text = "Olyan könyörtelenek, hogy utolértek minket. Van itt egy ösvény, bemenjünk? Könnyebb lesz tartani a vonalat.";
			link.l1 = "Várj, Hercule. Hallod ezt? Valaki már bent van. Te és a srácok intézzétek a dolgokat. Én bemegyek, mielôtt elviszik a kincset - kétlem, hogy bárki véletlenül betévedt volna oda.";
			link.l1.go = "Nemezida_Tonzag_6";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Tonzag_6":
            dialog.text = "Rendben, rendben. De légy óvatos, rossz érzésem van ezzel kapcsolatban.";
			link.l1 = "Neked is! Én megyek oda.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada6");
		break;
		
		case "Nemezida_Tonzag_7": // на берегу
            dialog.text = "Akar mondani valamit, kapitány? Egész úton a hajóig elmélyülten gondolkodott.";
			link.l1 = "Igen, így van. Azon gondolkodtam, hogy mit csináltam mostanában. A Terraxról és... hogy hova vezetett ez engem. Közelebb jutottam a bátyám megmentéséhez? Vagy hogy hazamehessek?";
			link.l1.go = "Nemezida_Tonzag_8";
		break;
		
		case "Nemezida_Tonzag_8":
            dialog.text = "Hm-m. Jó kérdés. És mik a válaszaid?";
			link.l1 = "Csak még egy kérdés. Ha eddig értelmetlen volt, akkor most is értelmetlen lesz? Terrax nem fog segíteni. Sem a bátyámmal, sem Tortugával.";
			link.l1.go = "Nemezida_Tonzag_9";
		break;
		
		case "Nemezida_Tonzag_9":
            dialog.text = "Valószínûleg nem. Neki nincs rá szüksége. Meglepô, hogy csak most jöttél rá. De mi a következô kérdésed?";
			link.l1 = "Mi a fenéért futottam egész idô alatt Terrax után, mint egy öleb, és húztam ki neki a gesztenyét a tûzbôl?!";
			link.l1.go = "Nemezida_Tonzag_10";
		break;
		
		case "Nemezida_Tonzag_10":
            dialog.text = "Na, ez egy jó kérdés. Egy megfelelô kérdés. Ezúttal tudsz válaszolni?";
			link.l1 = "Inkább egy elhatározás. Ma szerencsém volt. De lesz-e még egyszer szerencsém? Fontos tudni, mikor kell abbahagyni. És... tisztelni magad. Elegem van.";
			link.l1.go = "Nemezida_Tonzag_11";
		break;
		
		case "Nemezida_Tonzag_11":
            dialog.text = "Úgy döntöttél, hogy véget vetsz a Terrax-szal való együttmûködésednek?";
			link.l1 = "Igen. Vannak fontosabb dolgaim is. Család, barátok. Velük együtt fogom elérni a céljaimat. És nem így. És még ha meg is teszem... nem Marcusszal. A magam ura leszek. A saját döntéseimet hozom meg.";
			link.l1.go = "Nemezida_Tonzag_12";
		break;
		
		case "Nemezida_Tonzag_12":
            dialog.text = "A férfi, akit egykor követtem, újra beszél. Ne keveredj megint rossz emberekkel. Ne pazarold el a lehetôséget, ami egykoron lenyûgözött.";
			link.l1 = "Megvan, Hercule. És még egyszer köszönöm. Ezúttal azért, mert segítettél, hogy teljesen rájöjjek. Már nem vagyok herceg, csak egy lakáj. Charles de Maure vagyok, egy büszke nemes. Szálljunk fel a hajóra - mindketten fáradtak vagyunk.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionFinal_Tonzag");
		break;
		
		// Книппель
		case "Nemezida_Knippel_1":
            dialog.text = "Ez aztán a fene nagy robbanás volt, uram - knippel a tathoz! Pont úgy hangzott, mint egy szélárnyék a Valkûrrôl. De attól tartok, hogy azok a fickók ott is észrevették...";
			link.l1 = "Ha észrevették, az az ô bajuk. Senki sem hívta ôket ide. Készen állsz, hogy megleckéztesd ôket, Charlie?";
			link.l1.go = "Nemezida_Knippel_2";
		break;
		
		case "Nemezida_Knippel_2":
            dialog.text = "Mindig készen állok, uram!";
			link.l1 = "Készen állok, Charlie! Lássunk hozzá.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada2");
		break;
		
		case "Nemezida_Knippel_3":
            dialog.text = "Attól tartok, hamarosan újabb társaságunk lesz, kapitány. Mi a parancs?";
			link.l1 = "Mélyebbre megyünk a dzsungelbe és elbújunk - nincs mód arra, hogy mindet elhárítsuk, és amúgy sem azért vagyunk itt.";
			link.l1.go = "Nemezida_Knippel_4";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Knippel_4":
			PlaySound("VOICE\English\hambit\Charlie Knippel-05.wav");
            dialog.text = "Igenis, uram.";
			link.l1 = "Akkor induljunk!";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada4");
		break;
		
		case "Nemezida_Knippel_5":
            dialog.text = "Lenyomoztak minket, kapitány! De itt elrejtôzhetünk - úgy tûnik, ez az ösvény vezet valahová, bár szerintem már van ott valaki.";
			link.l1 = "Nem fogunk menedéket keresni! Úgy tûnik, valaki más is megneszelte a kincset. Itt a terv: Én megnézem, mi történik, mielôtt elviszik az egészet, te pedig itt tartod fel ôket a fiúkkal!";
			link.l1.go = "Nemezida_Knippel_6";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Knippel_6":
			PlaySound("VOICE\English\hambit\Charlie Knippel-05.wav");
            dialog.text = "Igenis, uram.";
			link.l1 = "Remek. Most megyek lefelé! Bízom benne, hogy elintézed itt a dolgokat.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada6");
		break;
		
		case "Nemezida_Knippel_7": // на берегу
            dialog.text = "Khe-khe... Jól van, uram?";
			link.l1 = "Charlie! A legjobb idôpontot választottad, hogy aggódj miattam. Tartogasd a szavaidat. Jól bírja? A hajón kellett volna hagynom téged, és helyette több embert vinnem...";
			link.l1.go = "Nemezida_Knippel_8";
		break;
		
		case "Nemezida_Knippel_8":
            dialog.text = "Csak egy karcolás, uram. Kicsit fáradt vagyok. Soha nem harcoltam így, még fiatalabb koromban sem! De úgy elvertem ôket, hogy az örökkévalóságig hallani fogják a knippelteket!";
			link.l1 = "Királyi Haditengerészet, régi iskola! Úgy tûnik, úgy harcoltál, mint egy oroszlán, Charlie. De még így is alig tudsz állni. Ne blöffölj - mennyire súlyos a sebed?";
			link.l1.go = "Nemezida_Knippel_9";
		break;
		
		case "Nemezida_Knippel_9":
            dialog.text = "Semmi komoly, kapitány, csak kimerült. A mögötted lévô bejárat szinte azonnal összeomlott, és mi még sokáig védekeztünk azokkal az emberekkel. A végén egyedül maradtam, sebesülten. Így hát idejöttem, hogy megtisztítsam az utat és elsôsegélyt kapjak.";
			link.l1 = "Értem. Nos, ma megtetted a magadét. Ami engem illet... Elbuktam. Mindannyiunkat becsaptak és egymás ellen uszítottak valakinek a szórakoztatására - még csak kincs sem volt. És nem én voltam az egyetlen bolond.";
			link.l1.go = "Nemezida_Knippel_10";
		break;
		
		case "Nemezida_Knippel_10":
            dialog.text = "Kudarcot vallottál? De ön életben van, uram. Mi történt? Megszöktél?";
			link.l1 = "Nem, de azért volt egy kis futás. Sajnálom, öreg barátom, de ami odabent történt, azt nem mondom el senkinek - még a legközelebbi barátaimnak sem. Azonban levontam a szükséges következtetéseket.";
			link.l1.go = "Nemezida_Knippel_11";
		break;
		
		case "Nemezida_Knippel_11":
            dialog.text = "Milyen következtetéseket vont le, uram? Nem mindig értem az érvelését. Az én filozófiám egyszerû - egy jó culverin és knippelek az árbocon.";
			link.l1 = "Mondja, biztos ölt már spanyolokat, mint ahogy én is tettem nemrég. Még a Királyi Haditengerészetnél. És késôbb, Fleetwooddal.";
			link.l1.go = "Nemezida_Knippel_12";
		break;
		
		case "Nemezida_Knippel_12":
            dialog.text = "Igen, így van. Spanyolok, hollandok és sokan mások is. Ahogy Dick egyszer mondta, a mi szolgálatunk veszélyes és igényes. De miért kérdezi? Mire akarsz kilyukadni?";
			link.l1 = "Megmagyarázom. De elôbb egy másik kérdés. Kételkedtél valaha is abban, hogy mit csinálsz és miért csinálod, Charlie?";
			link.l1.go = "Nemezida_Knippel_13";
		break;
		
		case "Nemezida_Knippel_13":
            dialog.text = "Hm-m. Azt mondtam magamnak, hogy a korona érdekében cselekszem. A parancsok miatt aggódni hálátlan munka - úgyis követni kell ôket.";
			link.l1 = "A Korona... Nos, megvolt rá az okod. Nekem nem is volt - Michel azt mondta, hogy menjek Terrax közelébe. De vajon megérte az összes áldozatot? Nekem vagy neki segített? Igen, igen, nem szeretjük a dónokat... de mindannyian emberek vagyunk.";
			link.l1.go = "Nemezida_Knippel_14";
		break;
		
		case "Nemezida_Knippel_14":
            dialog.text = "Azt hiszem, kezdem érteni, mire akar kilyukadni, uram.";
			link.l1 = "De mi mindannyian emberek vagyunk. Mondja, amikor Fleetwood elment, örült, hogy nem kellett többé holland kereskedôkre lônie? Néhányan közülük becsületes emberek voltak.";
			link.l1.go = "Nemezida_Knippel_15";
		break;
		
		case "Nemezida_Knippel_15":
            dialog.text = "Soha nem gondoltam erre, kapitány. De annyit mondhatok, hogy mindig is szerettem ön mellett szolgálni, uram. Legyek átkozott, ha hazudok, knippel a nyakamban!";
			link.l1 = "Ha-ha-ha-ha, rendben. De mondd csak - szerinted kinek volt rosszabb? Magának, aki parancsot követett? Vagy nekem, akit nem kényszerítettek arra, amit tettem?";
			link.l1.go = "Nemezida_Knippel_16";
		break;
		
		case "Nemezida_Knippel_16":
            dialog.text = "Nem tudom, uram...";
			link.l1 = "Én sem. De ez nem számít. Ami számít, az az, hogy többé nem akarok semmi közöm a Terraxhoz. Elég volt. Nincs többé Charlie Prince. Csak Charles de Maure.";
			link.l1.go = "Nemezida_Knippel_17";
		break;
		
		case "Nemezida_Knippel_17":
            dialog.text = "De nem ez volt a terved része, hogy megmentsd a bátyádat?";
			link.l1 = "Így volt. De a végén egyáltalán nem segített rajtam. Szóval ha valaha is újra ilyesmit kell tennem - csakis az én döntésem lesz. És csak akkor, ha valóban közelebb visz a célomhoz.";
			link.l1.go = "Nemezida_Knippel_18";
		break;
		
		case "Nemezida_Knippel_18":
            dialog.text = "Remélem, tudja, mit csinál, kapitány. És hogy nem fog úgy végezni, mint Terrax. Vagy egy akasztófán.";
			link.l1 = "Én is remélem. De abban biztos vagyok, hogy mostantól az én céljaim és érdekeim lesznek az elsôk. Most pedig lássuk el a sebeit.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionFinal_Officers");
		break;
		
		// Лонгвэй
		case "Nemezida_Longway_1":
            dialog.text = "A robbanásod figyelemfelkeltô, kapitány úr. Úgy tûnik, egy ellenséges osztag közeledik felénk.";
			link.l1 = "A francba! ...Gondolod, hogy volt jobb módja is annak, hogy elbánjunk azokkal a fákkal? És te mit tettél volna?";
			link.l1.go = "Nemezida_Longway_2";
		break;
		
		case "Nemezida_Longway_2":
            dialog.text = "Nem tudom. De azt tudom, hogy most mit kell tennem - foglalkozni azokkal az emberekkel.";
			link.l1 = "Nos, ez így van rendjén. Gondolom, pontosan ezt fogjuk tenni.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada2");
		break;
		
		case "Nemezida_Longway_3":
            dialog.text = "Új emberek jönnek, kapitány úr.";
			link.l1 = "Igen, észrevettem, köszönöm, Longway. De nincs idônk ezekre, úgyhogy vonuljunk vissza a dzsungelbe - talán elveszítenek minket.";
			link.l1.go = "Nemezida_Longway_4";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Longway_4":
            dialog.text = "Hmm, persze elbírnánk velük, de ahogy mondtad.";
			link.l1 = "Nincs szükségünk erre a harcra, úgyhogy menjünk tovább.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada4");
		break;
		
		case "Nemezida_Longway_5":
            dialog.text = "Nem hagyják magukat, és el fognak kapni minket, kapitány úr! Mondtam, hogy korábban kellett volna megölnünk ôket. Felállítsunk egy csapdát abban a barlangban? Bár úgy tûnik, valaki már ott van.";
			link.l1 = "Jobb, ha itt állítunk csapdát a fiúkkal! Amit nem fogok kihagyni, az a kincs. Úgy tûnik, valaki más is megneszelte a kincset... Úgyhogy megyek és megnézem magam.";
			link.l1.go = "Nemezida_Longway_6";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Longway_6":
            dialog.text = "Légy óvatos, kapitány úr. Ne feledd, még egy nagy sárkány is meghalt egyszer egy aranyhegy tetején.";
			link.l1 = "Ezt észben tartom, Longway. Próbáljunk meg ma mindannyian nem meghalni.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada6");
		break;
		
		case "Nemezida_Longway_7": // на берегу
            dialog.text = "Kapitány úr, úgy tûnik, sikerült elmenekülnöd onnan.";
			link.l1 = "Meglepôdtél, Longway? Bár be kell vallanom, én magam is meglepôdtem. Úgy tûnik, te vagy az egyetlen, aki élve megúszta. De hogy sikerült?";
			link.l1.go = "Nemezida_Longway_8";
		break;
		
		case "Nemezida_Longway_8":
            dialog.text = "Egy csapat szedett-vedett macska nem tud legyôzni egy tigrist. Egy kígyófészek sem tud legyôzni egy sárkányt. A fehér emberek közül kevés méltó ellenfele van az enyémnek.";
			link.l1 = "De ne feledd, Longway, egy csapat kutya is képes széttépni egy oroszlánt.";
			link.l1.go = "Nemezida_Longway_9";
		break;
		
		case "Nemezida_Longway_9":
            dialog.text = "És most a kapitány úr megosztja a bölcsességét Longway-jel? Kár, hogy nem fogadtad meg a tanácsomat korábban.";
			link.l1 = "A sárkányról az aranyhegyen? Igaz, majdnem azzá váltam - majdnem meghaltam, ami azt illeti. De nem az aranyhegyen - ott nem volt ilyen. Helyette valami mást találtam, ami ugyanolyan fontos volt.";
			link.l1.go = "Nemezida_Longway_10";
		break;
		
		case "Nemezida_Longway_10":
            dialog.text = "Legközelebb, 'majdnem' lehet, hogy nem történik meg. Mit talált, kapitány úr?";
			link.l1 = "Igen, most már látom. Amit találtam, az... bölcsesség volt. Tapasztalat. Megértés. Egy döntés. Mondd, Longway, mit csináltunk mostanában?";
			link.l1.go = "Nemezida_Longway_11";
		break;
		
		case "Nemezida_Longway_11":
            dialog.text = "Kalózok vagyunk. Az új gazdádnak, Lord Terraxnak dolgoztunk. Csempészünk, városokat fosztogatunk, ölünk, mentünk és segítünk a népének.";
			link.l1 = "Ô nem az én uram, tudod. De a fenébe is, olyan tökéletesen leírtad az egészet! Elfelejtettem a büszkeségemet, az önbecsülésemet, és úgy követtem ôt, mint egy öleb.";
			link.l1.go = "Nemezida_Longway_12";
		break;
		
		case "Nemezida_Longway_12":
            dialog.text = "Longway megérti önt, kapitány úr. Én is van Merdennek és Rodenburgnak dolgoztam, megfeledkezve a becsületrôl, a büszkeségrôl és a tiszteletrôl egy nagyra becsült cél érdekében.";
			link.l1 = "Mondja, elítéli magát ezért? Gyûlöli magát?";
			link.l1.go = "Nemezida_Longway_13";
		break;
		
		case "Nemezida_Longway_13":
            dialog.text = "Elítéled? Néha. Gyûlölöd? Nem. Tudom és emlékszem, hogy ki vagyok. Emlékszem a célomra, a vezércsillagomra. Semmi sem fontosabb az életben. És neked van célod?";
			link.l1 = "Nem egy vezércsillag, mint neked, de mégis egy fontos cél, igen - megmenteni a testvéremet. De én eltértem ettôl a céltól. És ezt nem engedhetem meg magamnak, hogy megismétlôdjön.";
			link.l1.go = "Nemezida_Longway_14";
		break;
		
		case "Nemezida_Longway_14":
            dialog.text = "Hadd osszam meg veled a Mennyei Birodalom egy másik bölcsességét. Nincsenek teljesen jó vagy rossz emberek. Minden emberben van Yin - sötétség és tudatlanság - és Yang - fény és bölcsesség. Az egyensúly mindenkiben eltolódik.";
			link.l1 = "Tehát az én Yangom Charles de Maure. Az én Yinem pedig Charlie Prince. Bár talán még Charles de Maure-nak is sötét és nehéz döntéseket kell majd hoznia egy nap.";
			link.l1.go = "Nemezida_Longway_15";
		break;
		
		case "Nemezida_Longway_15":
            dialog.text = "Ilyen az élet, kapitány úr. Minden embernek kell sötét és világos döntéseket hoznia.";
			link.l1 = "Mégis a Prince maszkja szinte összeolvadt velem. De levetem magamról. Charles de Mort nemesember, nem pedig kifutófiú. Mostantól kezdve csak az lesz. Visszaszerzem a büszkeségemet és a méltóságomat. Mostantól a magam ura vagyok.";
			link.l1.go = "Nemezida_Longway_16";
		break;
		
		case "Nemezida_Longway_16":
            dialog.text = "Hosszan helyeslem a döntését, kapitány úr.";
			link.l1 = "Köszönöm, Longway. Egyébként nem bánod, hogy nem vagy szabad kapitány? Szolgálsz engem, ahogy te mondod, 'az urad'?.";
			link.l1.go = "Nemezida_Longway_17";
		break;
		
		case "Nemezida_Longway_17":
            dialog.text = "Hm-m. Longway-nek hiányzik, hogy a saját hajóját irányítsa. De az enyém felismeri a magáét. Hogy tiszteletet és bölcsességet mutattál az enyémnek, ellentétben a tipikus fehér barbárokkal. Talán az enyémek más életet szeretnének. De nem bánom, hogy segítettem neked.";
			link.l1 = "Ezt örömmel hallom, Longway. Most pedig... hagyjuk el ezt a helyet és a Yin ösvényét. És hozzunk több Yangot az életünkbe. Jól értettem?";
			link.l1.go = "Nemezida_Longway_18";
		break;
		
		case "Nemezida_Longway_18":
            dialog.text = "Igen, így van. Remélem, mostantól sokkal jobb Daót követsz.";
			link.l1 = "Dao?";
			link.l1.go = "Nemezida_Longway_19";
		break;
		
		case "Nemezida_Longway_19":
            dialog.text = "Az utat, kapitány úr. Vagy az Esszencia. De a mi esetünkben - az Út.";
			link.l1 = "Bármit is tartogat a jövôbeni utam, nem térek el újra attól, ami igazán számít. Hagyjuk el ezt a helyet, Longway.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionFinal_Officers");
		break;
		
		// Тичингиту
		case "Nemezida_Tichingitu_1":
            dialog.text = "Charles kapitány, sokan jönnek erre. A füstjelzésed vonzotta ôket. És nyilvánvalóan nem a barátaink.";
			link.l1 = "Ó, bárcsak csak egy 'füstjel lenne,' ahogy te nevezted - visszhangzott az egész dzsungelben. Nincs más választásunk - védjük meg magunkat. Egy egész osztag hátba támadására biztosan nincs szükségünk.";
			link.l1.go = "Nemezida_Tichingitu_2";
		break;
		
		case "Nemezida_Tichingitu_2":
            dialog.text = "Igen, Charles kapitány. Csapjatok le elôször!";
			link.l1 = "Támadás! Ne spóroljatok a golyókkal!";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada2");
		break;
		
		case "Nemezida_Tichingitu_3":
            dialog.text = "Jönnek még! Még több ember.";
			link.l1 = "Vonulj vissza a dzsungelbe, Tichingitu! Elbújunk és kivárjuk. Kincsekért jöttem ide, nem harcolni!";
			link.l1.go = "Nemezida_Tichingitu_4";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Tichingitu_4":
            dialog.text = "Ha szükséges, csapdát állíthatunk a dzsungelben.";
			link.l1 = "Ez igaz. Most pedig induljunk - gyorsan, de csendben.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada4");
		break;
		
		case "Nemezida_Tichingitu_5":
            dialog.text = "Charles kapitány, nézze! Van egy átjáró elôttünk. Lépéseket és hangokat hallok onnan.";
			link.l1 = "Valaki más is rájött a kincsre? A francba! Te is hallod ezt a zajt mögöttünk? Úgy tûnik, utolérték ôket. Tichingitu! Megyek, megnézem, mi van elôttünk. Tartsd fel ôket a fiúkkal!";
			link.l1.go = "Nemezida_Tichingitu_6";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Tichingitu_6":
            dialog.text = "Megpróbáljuk! Menjetek!";
			link.l1 = "Számítok rád!";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada6");
		break;
			
		case "Nemezida_Tichingitu_7": // на берегу
            dialog.text = "Charles kapitány! Te túléled! Tichingitu örüljön ennek.";
			link.l1 = "Köszönöm, barátom. Én is boldog vagyok. Örülök, hogy túléltem, és hogy jól vagy. Úgy tûnik, te vagy az egyetlen, aki megmaradt az egész csapatból. Sokan voltak? Tényleg jól visszatartottad ôket.";
			link.l1.go = "Nemezida_Tichingitu_8";
		break;
		
		case "Nemezida_Tichingitu_8":
            dialog.text = "Sokaknak. De az enyém az egyik legjobb harcos a mi Maskog falunkból. Mi történt veled ott? Megtaláltad a kincset, amit kerestél?";
			link.l1 = "Nem, Tichingitu. Becsaptak minket - nem volt ott kincs. Mondd csak, mit gondolsz arról, amit mostanában csináltunk?";
			link.l1.go = "Nemezida_Tichingitu_9";
		break;
		
		case "Nemezida_Tichingitu_9":
            dialog.text = "Mit csináltunk, Charles kapitány? Vitorláztunk. Legyôztük az ellenségeinket.";
			link.l1 = "Úgy tûnik, nem értesz engem. Akkor mondd csak, szomorú vagy amiatt, hogy számûztek a törzsedbôl? Vissza akarsz menni, hiányoznak a testvéreid?";
			link.l1.go = "Nemezida_Tichingitu_10";
		break;
		
		case "Nemezida_Tichingitu_10":
            dialog.text = "Persze, hiányoznak a barátaim és a családom. De visszamenni? Az otthonom nem létezik többé nélküle... nélküle. Különben is, ott van az a gonosz prérifarkas, a sámán!";
			link.l1 = "Sajnálom, nem akartam ezt felhozni. Tudod, nemrég csatlakoztam egy törzshöz, hogy úgy mondjam. A hozzám hasonló kapitányok törzséhez. De végül rájöttem, hogy ez csak egy csapat sakál, akik tengeri farkasoknak képzelik magukat...";
			link.l1.go = "Nemezida_Tichingitu_11";
		break;
		
		case "Nemezida_Tichingitu_11":
            dialog.text = "És mi történt? Most mihez kezdünk?";
			link.l1 = "Jó kérdés. Majdnem én is sakál lettem azokkal a sakálokkal. Szóval, ez'nekem elég. A barátaim és a csapatom - ez az én 'törzsem.";
			link.l1.go = "Nemezida_Tichingitu_12";
		break;
		
		case "Nemezida_Tichingitu_12":
            dialog.text = "Tichingitu örül, hogy megtaláltad a törzsedet, Charles kapitány.";
			link.l1 = "Köszönöm, barátom. Szükségem volt rá, hogy ezt mondjam. Te és én mindketten a saját vezetôink és törzsünk vagyunk. És most itt az ideje, hogy visszatérjünk az igazán fontos dolgokhoz.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionFinal_Officers");
		break;
		
		// Айронс
		case "Nemezida_Irons_1":
            dialog.text = "Valaki jön! És a hangokból ítélve nem azért, hogy velünk ünnepelje a hálaadást.";
			link.l1 = "Átkozott gyökerek! Jól van, most kell elbánnunk ezekkel a gazemberekkel - jobb most, mint amikor a kincset a hajóra cipeljük.";
			link.l1.go = "Nemezida_Irons_2";
		break;
		
		case "Nemezida_Irons_2":
            dialog.text = "Ebben igazad van. Készen álltok?";
			link.l1 = "Nem kellett volna kérdezned. Nem mintha lenne más választásunk.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada2");
		break;
		
		case "Nemezida_Irons_3":
            dialog.text = "Mindenütt ott vannak, mint a patkányok a londoni nyomornegyedben, bíró úr! Mi a terv - tartsuk a frontot és lôjünk ki a fiúkkal?";
			link.l1 = "Ne most, vonuljatok vissza! A kincsért jöttünk, nem harcolni!";
			link.l1.go = "Nemezida_Irons_4";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Irons_4":
            dialog.text = "Heh, nincs ellenvetésem.";
			link.l1 = "Akkor gyorsabban!";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada4");
		break;
		
		case "Nemezida_Irons_5":
            dialog.text = "Hé, kapitány, nézze - úgy tûnik, ez az ösvény vezet valahová. És a zajból ítélve elég élénknek tûnik!";
			link.l1 = "Lehet, hogy valaki más is tudomást szerzett a kincsrôl? Tommy, hallod ezt? Utolértek minket. Rendben, én megyek elôre, ti pedig üdvözöljétek ôket!";
			link.l1.go = "Nemezida_Irons_6";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Irons_6":
            dialog.text = "Most hallom! Akárkik is ôk, jobb, ha sietsz, he-he-he. Máskülönben mi értelme volt idáig vándorolni?!";
			link.l1 = "Ó, nem szeretném, ha ez lenne a helyzet.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada6");
		break;
		
		case "Nemezida_Irons_7": // на берегу
            dialog.text = "Á, maga az, kapitány! Hû, túlélted. Nem fogok hazudni - nem számítottam rá. De örülök, ne értsen félre, heh-heh.";
			link.l1 = "Én sem számítottam rá, én sem hazudok. De a tény, hogy túlélted - egyáltalán nem vagyok meglepve. Elszöktél?";
			link.l1.go = "Nemezida_Irons_8";
		break;
		
		case "Nemezida_Irons_8":
            dialog.text = "Rosszat tettél velem! Tommy Irons sosem fut el! Csak erôsítésért jön vissza. De nem volt rá szükség - az embereim és én egyedül is megbirkóztunk vele, bár ismét én vagyok az egyetlen, aki élve megúszta, heh...";
			link.l1 = "Talán ezúttal erôsítésért kellett volna menned. De én... Elfutottam.";
			link.l1.go = "Nemezida_Irons_9";
		break;
		
		case "Nemezida_Irons_9":
            dialog.text = "Elfutottál? Heh, megint megleptél. Pedig igazából hozzád akartam rohanni, amint végeztem! Jobb vagyok, mint bármilyen erôsítés, tudod. Csak az van, hogy...";
			link.l1 = "Mi a baj, Tom?";
			link.l1.go = "Nemezida_Irons_10";
		break;
		
		case "Nemezida_Irons_10":
            dialog.text = "A fenébe, amíg én itt babráltam, a mögötted lévô bejáratot elzárták a kövek. Nem tudtam átjutni. Még az is kínos, hogy olyan sokáig tartott, amíg megtisztítottam, és nem tudtam segíteni neked. Kicsit eltévedtem egyedül, miközben visszataláltam a srácokért, hogy segítsek eltüntetni a köveket... Mire visszaértem, te már itt voltál.";
			link.l1 = "Igen, talán szégyellni fogom magam, ha bevallom, mi történt ma velem.";
			link.l1.go = "Nemezida_Irons_11";
		break;
		
		case "Nemezida_Irons_11":
            dialog.text = "És mi történt? Ne félj, mondd el! De ha valami vicceset, akkor nevetni fogok, csak hogy tudd. Hogy is lehetne másképp? A barátja felajánlja a vállát, és a könyökével megböki a nevetésben.";
			link.l1 = "Hát te aztán tudsz vigasztalni. Mondd csak, Tommy! Azt mondtad, hogy szeretsz kalózkodni. Örültél, hogy velem együtt visszatértél hozzá?";
			link.l1.go = "Nemezida_Irons_12";
		break;
		
		case "Nemezida_Irons_12":
            dialog.text = "Úgy fogalmazok, hogy így fogalmazok. Akár kalóz vagyok, akár nem, amit mindig is rohadtul szerettem, az a kaland! Látom, a válaszom nem elégített ki. Ez a dolog, a nagy dolgok, nem az én világom.";
			link.l1 = "Nem arról van szó, hogy nem elégít ki. De nem errôl akartam beszélni. Tudod... Rájöttem, hogy Tiraqs-szal teljesen eltértem a céljaimtól. És... Charlie Prince valamiféle lakáj volt, nem egy bátor kalózkapitány, érted, Tom? Nekem ennyi elég.";
			link.l1.go = "Nemezida_Irons_13";
		break;
		
		case "Nemezida_Irons_13":
            dialog.text = "Megértettem. Ezért is lepôdtem meg, hogy hagytad, hogy Terrax így irányítson téged. Nem is úgy tûnt, mintha te lettél volna.";
			link.l1 = "Talán tényleg Charlie Prince voltam akkoriban. De hogy visszatérünk-e a kalózkodáshoz vagy sem, majd én eldöntöm! És csak akkor, ha tényleg az én érdekeimet szolgálja és közelebb visz a célomhoz!";
			link.l1.go = "Nemezida_Irons_14";
		break;
		
		case "Nemezida_Irons_14":
            dialog.text = "Na, ez már jobban tetszik! De azt akarom mondani, hogy akár Charlie Prince, akár Charles de Maure - attól még te vagy. Szóval veled mindig átkozottul érdekes volt!";
			link.l1 = "Örülök, hogy ezt hallom, Tommy.";
			link.l1.go = "Nemezida_Irons_15";
		break;
		
		case "Nemezida_Irons_15":
            dialog.text = "Ne feledd, szinte senki sem segít rajtad kívül. Jobb azt csinálni, amit szeretsz, akár egyedül is, mint hagyni, hogy mások döntsenek helyetted!";
			link.l1 = "Ez igaz. Pontosan ezt éreztem a Terrax-szal kapcsolatban is. Még ha újra követni is fogok valakit, csak méltó feltételek mellett, nem pedig úgy, mint valami átkozott kifutófiú!";
			link.l1.go = "Nemezida_Irons_16";
		break;
		
		case "Nemezida_Irons_16":
            dialog.text = "Igazad van! Most pedig tûnjünk el innen - a lábaim máris inognak.";
			link.l1 = "Hé, épp ezt akartam mondani, ha-ha. De igazad van, menjünk. Sok fontos munka vár ránk, Tom. Nem ilyen dolgok.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionFinal_Officers");
		break;
		
		// Алонсо
		case "Nemezida_Alonso_1":
            dialog.text = "Kapitány, úgy tûnik, társaságot kaptunk! Nem vagyunk egyedül.";
			link.l1 = "Pont erre volt szükségünk... Rendben, foglalkozzunk velük most. Késôbb csak még több gondot okoznak.";
			link.l1.go = "Nemezida_Alonso_2";
		break;
		
		case "Nemezida_Alonso_2":
            dialog.text = "Igenis, kapitány.";
			link.l1 = "Készüljetek!";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada2");
		break;
		
		case "Nemezida_Alonso_3":
            dialog.text = "Egyre többen vannak!";
			link.l1 = "Akkor nincs értelme folytatni! Vissza! Lerázzuk ôket, és egyenesen a kincsek felé tartunk!";
			link.l1.go = "Nemezida_Alonso_4";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Alonso_4":
            dialog.text = "Igenis, kapitány!";
			link.l1 = "Mozgás, mozgás!";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada4");
		break;
		
		case "Nemezida_Alonso_5":
            dialog.text = "Kapitány, úgy tûnik, van itt egy bejárat! És valaki már bent van.";
			link.l1 = "Jól figyeljetek - követnek minket. Én bemegyek és megnézem, amíg te tartod ezt a helyet. Fedezzetek, fiúk!";
			link.l1.go = "Nemezida_Alonso_6";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Alonso_6":
            dialog.text = "Igenis, kapitány!";
			link.l1 = "Maradjatok a helyeteken. Sok szerencsét nektek - mindannyiunknak!";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada6");
		break;
		
		//--> блок реагирования на попытку залезть в сундук
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Te "+ GetSexPhrase("tolvaj vagy, látom! Ôrök, fogjátok el","tolvaj, látom! Ôrség, fogjátok el") +"!!!", "Nem hiszem el! Egy pillanatra elfordultam - és máris a holmimba merülsz! Állítsatok meg egy tolvajt!!!", "Ôrség! Rablás! Állítsanak meg egy tolvajt!!!");
			link.l1 = "Aaaah, ördög!!!";
			link.l1.go = "fight";
		break;
		
		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		//<-- блок реагирования на попытку залезть в сундук
		
		// <-- legendary edition
	}
}
