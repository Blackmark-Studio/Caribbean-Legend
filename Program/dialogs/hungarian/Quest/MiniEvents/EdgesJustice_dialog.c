void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			dialog.text = "Mit szeretne?";
			link.l1 = "Semmi.";
			link.l1.go = "exit";
		break;

		case "Naemnik":
			dialog.text = "Jó vagy"+GetSexPhrase("","ess")+"... átkozottul jó"+GetSexPhrase("","ess")+". De mielôtt befejeznéd a munkát, hallgass meg. Biztos vagyok benne, hogy a mondanivalóm érdekelni fog.";
			link.l1 = "Gondolom, elmondhatod az utolsó szavaidat, mielôtt meghalsz. De ne reménykedjen. Nem hagyod el ezt a barlangot.";
			link.l1.go = "Naemnik_2";
		break;

		case "Naemnik_2":
			dialog.text = "Kikötôfônök, mi? A fejemért küldött?";
			link.l1 = "Éles vagy, mint mindig.";
			link.l1.go = "Naemnik_3";
		break;

		case "Naemnik_3":
			dialog.text = "Azért küldött, hogy megölj, ugye? Nem megtalálni, nem elfogni - megölni.";
			link.l1 = "Nem, nem megtalálni, hanem megölni. És akkor mi van?";
			link.l1.go = "Naemnik_4";
		break;

		case "Naemnik_4":
			dialog.text = "Ha... te egy igazi "+GetSexPhrase("tökfej vagy","kis bolond")+". Belegondoltál már abba, hogy miért volt olyan fontos neki, hogy inkább meghaljak, minthogy egy cellában rohadjak? Nem? Fogalmad sincs, hogy kit akarsz megmenteni. Az a kikötôi pók hazugságok hálóját szôtte az egész hely fölé, és te, "+GetSexPhrase("fiú","drága")+", mélyen benne ragadtál.\nAzt hiszed, ô egy becsületes hivatalnok? Ha! Csak akkor álmodik becsületességrôl, amikor alszik. Információkat ad el kalózoknak és hollandoknak. Elárulja azokat, akik megbíznak benne. Egy ilyen féregnek, mint ô, a föld alatt a helye!";
			link.l1 = "És ki ne taposná a földet a csizmájával. Maga sem úgy néz ki, mint egy szerzetes.";
			link.l1.go = "Naemnik_5";
		break;

		case "Naemnik_5":
			dialog.text = "Nem vagyok szerzetes, és nem is teszek úgy, mintha az lennék. A pengém sosem hazudik. Egy pillantás, és az ember tudja, hogy a halál eljött érte. Nem mosolygok a prédámra, vagy rázok kezet vele, tudván, hogy már eleve halálra van ítélve. Nem. A szándékom egyértelmû. Az a bürokrata?\nElárul mindenkit, aki bízik benne, miközben úgy tesz, mintha segítene. Rosszabb, mint bármelyik szemétláda, akit valaha is sírba tettem.";
			link.l1 = "Tegyük fel, hogy az igazat mondja. Ki bérelt fel?";
			link.l1.go = "Naemnik_6";
		break;

		case "Naemnik_6":
			dialog.text = "Nem mondok nevet - nem is tudom. De ô valaki, akit az a szemétláda bántott. Egy ember, aki igazságot akar szolgáltatni... vagy bosszút állni. Nevezze, aminek akarja. Ötszáz dublont annak a rohadt hivatalnoknak a fejéért! Segíts nekem, és osztozunk a pénzen.";
			link.l1 = "Elég a beszédbôl! Bármit mondanál, hogy mentsd a szánalmas bôrödet. Hagytam, hogy beszélj, most itt az ideje meghalni.";
			link.l1.go = "Naemnik_7";
			link.l2 = "Szép mese. De nem fogok hinni neked csak úgy. Van valami a szavadon kívül? Bizonyíték, tanúk? Vagy ez is csak egy újabb trükk, hogy kicselezd a halált?";
			link.l2.go = "Naemnik_8";
		break;
		
		case "Naemnik_7":
			DialogExit();
			LAi_SetFightMode(pchar, true);
			
			sld = CharacterFromID("GS_Naemnik");
			LAi_SetImmortal(sld, false);
			LAi_SetCurHPMax(sld);
			LAi_GetCharacterMaxEnergy(sld);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheckFunction("EnemyFight", "GS_UbivaemNaemnika");
		break;
		
		case "Naemnik_8":
			dialog.text = "Ezeket a pergameneket egy kalóz szállásán találták, egy tengeri kutyában, akit a patrónusom legyôzött a harcban. A gazember nem mástól kapta az információt, mint magától a kikötôi fônöktôl. Ebben aprólékosan fel vannak jegyezve a hajók útvonalai, indulási idejük és rakományuk jellege. Ugyanezeket a hajókat késôbb kifosztották, legénységüket lemészárolták, vagy eltûntek a végtelen kék\nJegyezzétek meg jól - a feljegyzésekben szereplô pártavonások pontosan megegyeznek a hivatalos manifesztekben szereplôvel. Ez a bizonyíték leleplezi az árulót. A patrónusom azt kívánja, hogy ezeket az iratokat a holttesténél találják meg. A bírói emelvény nem lenne elég\nEz a feketerigó túl nagy hatalommal rendelkezik, számtalan korrupt szövetségesével a zsebében. Ha bíróság elé kerülne, kiszabadulna az igazságszolgáltatás markából. Az ilyen férgek nem érdemelnek helyet Isten lélegzô teremtményei között. Az ilyen áruláshoz csak a tartós gyalázatos halál illik.";
			link.l1 = "Áruló kutya! Az emberek rábízzák a vagyonukat, ô pedig elárulja az életüket gyilkosoknak és rablóknak! Számítson rám a szövetségeseként ebben. Az ilyen teremtmény nem érdemel helyet Isten mennyei alatt.";
			link.l1.go = "Naemnik_9";
			GiveItem2Character(PChar, "GS_letters");
			AddQuestRecordInfo("GS_Letters", "1");
		break;

		case "Naemnik_9":
			dialog.text = "Kulcsot szereztem a lakásához - azon az asztaloson keresztül, aki a bútorokat javította abban az urasági kastélyban. Minden a terv szerint haladt, amíg rá nem jöttem, hogy megosztja a lakrészét. Amikor beléptem, hogy igazságot szolgáltassak, a felesége is jelen volt\nA váratlan társasága elgondolkodtatott. A véréért nem tûztek ki vérdíjat, és a korona emberei sokkal nagyobb buzgalommal vadásznának arra, aki megöl egy tekintélyes nôt. Ezért megváltoztattam a tervemet, és inkább a vámház közelében leselkedtem rá.";
			link.l1 = "Pokol tüze és kárhozat! Most az egész város éberen ôrködik - nem csaphatunk le nyíltan, ahogyan azt korábban megtehettük volna. Mi marad nekünk?";
			link.l1.go = "Naemnik_10";
		break;

		case "Naemnik_10":
			dialog.text = "Ôrködtem a város felett, és vártam, amíg a felfordulás elül. Kísérletem után az a gyáva patkány sietett elrejteni a feleségét. A saját szememmel láttam, ahogy felszállt egy hajóra, és elhagyta a kikötôt\nMost egyedül maradt - tökéletes alkalom, hogy befejezzük, amit elkezdtünk. A sötétség leple alatt besurranhatsz a búvóhelyére, és véget vethetsz ennek az ügynek. Aztán hagyd ott ezeket a kárhozatos papírokat, ahol nem lehet eltéveszteni, hogy mindenki megtudja, milyen aljas romlottság bujkál a szívében\nDe számomra a város kapui el vannak zárva. Te azonban... te sikerrel járhatsz ott, ahol én nem. Egyetlen ôr sem keresi az arcodat; könnyedén átmész az ôrségükön. A háza a városi börtön közelében van. Ötszáz dublont! A jutalom fele a tiéd lesz, ha az áruló holtan fekszik.";
			link.l1 = "Úgy legyen. A saját kezemmel küldöm el ezt a gazembert, hogy találkozzon a teremtôjével. Ezek az iratok a lakásában maradnak, hogy mindenki megtudja az igazságot az árulásáról. Várjatok a visszatérésemre. Visszatérek, amint igazságot szolgáltattam.";
			link.l1.go = "Naemnik_11";
		break;
		
		case "Naemnik_11":
			DialogExit();
			chrDisableReloadToLocation = false;
			locations[FindLocation("Beliz_Cave")].DisableEncounters = false;
			AddQuestRecord("GS", "5");
			AddQuestUserData("GS", "sSex", GetSexPhrase("","а"));
			
			sld = CharacterFromID("GS_Naemnik");
			LAi_SetWarriorType(sld);
			LAi_SetCurHPMax(sld);
			LAi_GetCharacterMaxEnergy(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PEACE);
			NextDiag.CurrentNode = "Naemnik_12";
			
			sld = &Locations[FindLocation("Beliz_town")];
			sld.reload.l11.open_for_night = 1;
			sld = &Locations[FindLocation("Beliz_houseS5_room2")];
			sld.locators_radius.item.button01 = 1.0;
			
			pchar.quest.GS_SoldatyDoma.win_condition.l1 = "Hour";
			pchar.quest.GS_SoldatyDoma.win_condition.l1.start.hour = 0.00;
			pchar.quest.GS_SoldatyDoma.win_condition.l1.finish.hour = 5.00;
			PChar.quest.GS_SoldatyDoma.win_condition.l2 = "location";
			PChar.quest.GS_SoldatyDoma.win_condition.l2.location = "Beliz_houseS5";
			PChar.quest.GS_SoldatyDoma.function = "GS_SoldatyDoma";
		break;
		
		case "Naemnik_12":
			dialog.text = "Miért állsz ott dermedten, mintha a lábad mészben ragadt volna?";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Naemnik_12";
		break;

		case "Portman_1":
			dialog.text = "És te? Mi a fene? Hogy jutottál be ide?";
			link.l1 = "Hogy hogyan kerültem ide, az egyáltalán nem számít. És azt hiszem, mélyen legbelül megérted, hogy miért jöttem.";
			link.l1.go = "Portman_2";
			DelLandQuestMark(npchar);
		break;

		case "Portman_2":
			dialog.text = "Nem, nem értem! Ha a jutalomért jöttél, akkor gyere holnap az adminisztrációra, mindent megadok neked.";
			link.l1 = "Ne játszd az ártatlant! Mindent tudok. Eladtad a tippeket az ügyfeleidrôl' hajókról a kalózoknak. Egy ilyen aljas ember nem érdemli meg, hogy ilyen pozíciót töltsön be. Sôt, azt sem érdemli meg, hogy becsületes emberek között éljen. Uram, az ön helye a saját fajtája között van - a pokolban.";
			link.l1.go = "Portman_3";
		break;

		case "Portman_3":
			dialog.text = "Ó, nem-nem-nem! Ne! Teljesen félreértetted! Kényszerítettek... Eljöttek hozzám, és megfenyegettek, hogy a családommal foglalkoznak, ha nem segítek nekik... nem érted...";
			link.l1 = "Elegem van a szánalmas kifogásaidból! A kezemben vannak a jegyzeteid, amin a borravalóért követeled a százalékodat! A képmutatásod undorító, és nem áll szándékomban tovább tûrni. Vegye elô a fegyverét és védje meg magát, ha van hozzá bátorsága!";
			link.l1.go = "Portman_4";
		break;
		
		case "Portman_4":
			DialogExit();
			LAi_LocationFightDisable(loadedLocation, false);
			LAi_SetFightMode(pchar, true);
			
			sld = CharacterFromID("Beliz_portman_clone");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheckFunction("EnemyFight", "GS_PortmanDead");
		break;
		
		case "Naemnik_21":
			dialog.text = "Szóval, mi a hír? Befejezôdött az üzletünk?";
			link.l1 = "Kételkedtél bennem? A szerencsétlen erôsen erôlködött, hogy valami szánalmas kifogást csikarjon ki az ajkai közül, de mindhiába. Úgy helyeztem el a kárhozatos papírokat, hogy ne lehessen eltéveszteni, ahogy megbeszéltük.";
			link.l1.go = "Naemnik_22";
		break;

		case "Naemnik_22":
			dialog.text = "Az ilyen gyáva férgek, mint ô, örökké azt hiszik, hogy aljas hazugságokkal és pénzzel kegyelmet szerezhetnek az igazságszolgáltatás pengéjétôl.";
			link.l1 = "Nos, a gondolatai nem zavarják tovább. Adja át a fizetségemet, és én elmegyek.";
			link.l1.go = "Naemnik_23";
		break;

		case "Naemnik_23":
			dialog.text = "Itt vannak a duplontok, melyeket jogosan érdemeltetek ki. Szép munka, ezt elismerem. De jegyezd meg jól - ha a kezemben keményebb acél lett volna, amikor elôször kereszteztük a pengéket, a sorsunk talán egészen másképp alakult volna... a te örökös sajnálatodra. Ezekben a szûk kamrákban egy rendes fegyver nem tud igazat lóbálni, ezért nem volt nálam más, csak ez a nyomorult fogpiszkáló, arra gondolva, hogy gyors gazdasággal intézlek el téged\nHa elôre láttam volna, hogyan alakulnak a dolgok, egy olyan pengével fegyverkeztem volna fel, ami jobban illik egy ilyen erôs emberhez, mint én.";
			link.l1 = "Ha! Elhunyt barátunk azt állította, hogy úgy vagy felfegyverkezve, mint Roland maga a Roncesvalles-i szurdok elôtt! Micsoda paladinnak bizonyultál.";
			link.l1.go = "Naemnik_24";
			AddItems(pchar, "gold_dublon", 250);
		break;

		case "Naemnik_24":
			dialog.text = "Heh. A félelem hatalmas árnyakat vet, nem igaz? A saját szemeddel láttad a szánalmas evôvassal, amivel majdnem átszúrtam dobogó szívedet.";
			link.l1 = "Arra célzol, hogy nehezebb acéllal a kezedben, méltó ellenfélnek bizonyultál volna számomra?";
			link.l1.go = "Naemnik_25";
		break;

		case "Naemnik_25":
			dialog.text = "A közepes súlyú pengék kezelésében senki sem múlja felül a tudásomat - erre életem vérére esküszöm. Kételkedsz? Akkor hát legyen. Átadok néhány ravasz manôvert, ami számtalan veszélyen keresztül megóvott engem. Figyelj jól - ezek nem puszta hencegés, hanem bölcsesség, amely egy napon megmenthet téged a korai sírtól. Az ilyen titkos tudást ritkán osztják meg mással, csak a legméltóbb tanítványokkal.";
			link.l1 = "...";
			link.l1.go = "Naemnik_26";
		break;
		
		case "Naemnik_26":
			DialogExit();
			SetLaunchFrameFormParam("Egy óra telik el...", "Run_Function", 0, 4.0);
			SetLaunchFrameRunFunctionParam("GS_Spravedlivost_2", 0.0);
			LaunchFrameForm();
		break;

		case "Naemnik_27":
			dialog.text = "...";
			link.l1 = "Látom, valóban mestere vagy a mesterségednek. Köszönöm a tanításodat. De ha az üzletünk befejezôdött, nekem mennem kell.";
			link.l1.go = "Naemnik_28";
			AddComplexSelfExpToScill(0, 500, 0, 0);
		break;

		case "Naemnik_28":
			dialog.text = "Ég veled, "+GetSexPhrase("Kapitány","szép hölgy")+". Reméljük, nem keresztezzük többé a pengéket. Szomorú lennék, ha elküldenélek a teremtôdhöz. Ha-ha.";
			link.l1 = "Még akkor sem lenne esélyed, ha három lapot tartanék a szélben és egy lábon egyensúlyoznék! Ég veled, árus.";
			link.l1.go = "Naemnik_29";
		break;
		
		case "Naemnik_29":
			DialogExit();
			chrDisableReloadToLocation = false;
			locations[FindLocation("Beliz_Cave")].DisableEncounters = false;
			LAi_SetPlayerType(pchar);
			
			LAi_SetWarriorType(npchar);
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PEACE);
			
			AddQuestRecord("GS", "7");
			CloseQuestHeader("GS");
			
			AddSimpleRumourCity("Azt beszélik, hogy a kikötôi fônököt holtan találták a saját házában. A holttestén olyan iratokat találtak, amelyek bizonyítják, hogy köze volt a hajók eltûnéséhez. Képzelje csak el, milyen szégyent hozott a városunkra...", "Beliz", 30, 1, "");
			AddSimpleRumourCity("Hallottad a híreket? Valaki beosont a kikötôfônök házába, megölte az ôröket, és kivitte ôt. A holttestén feljegyzéseket találtak az eltûnt hajók útvonaláról - saját kezûleg írva! A korona szolgája, de valójában áruló! Azt kapta, amit megérdemelt! És hol volt a kormányzó ennyi éven át?", "Beliz", 30, 1, "");
			AddSimpleRumourCity("A kikötômester halott! Megölték a saját otthonában! Az ôröket lemészárolták, és a vagyona között voltak az eltûnt hajók útvonalait feltérképezô feljegyzések. Semmi kétség - ô állt az eltûnések mögött! Az igazságszolgáltatás végre utolérte a gazembert.", "Beliz", 30, 1, "");
			break;
	}
}