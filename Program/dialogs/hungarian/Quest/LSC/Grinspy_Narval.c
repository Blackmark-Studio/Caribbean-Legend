// Дональд Гринспи - лидер нарвалов
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Mi az? Mit akarsz?";
				link.l1 = TimeGreeting()+". A nevem "+GetFullName(pchar)+". Szeretnék találkozni a klán vezetôjével.";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, "+GetFullName(pchar)+"! Akarsz valamit?";
				link.l5 = "Csak üdvözölni akartalak. Viszlát!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "Most már ismersz engem. A nevem Donald Greenspen, és ne dühítsen fel engem vagy az embereimet. És ne próbálja meglátogatni a 'San Gabriel' , amíg nem kap jelszót. A bolt ingyenesen látogatható, mindenkinek kereskednie kell. Van kérdés?";
			link.l2 = "Nem, megoldom. Viszlát.";
			link.l2.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
	// ----------------------------------после разгрома Чада и Мэри на Каролине---------------------------
		case "shark":
			dialog.text = "Milyen üzleted van számomra?";
			link.l1 = "Egy nagyon kellemetlen, Donald. Tegnap este merényletet követtek el Steven ellen. A klánod harcosai is részt vettek benne.";
			link.l1.go = "shark_1";
		break;
		
		case "shark_1":
			dialog.text = "Errôl nem tudok. Miért gondolod, hogy az én embereim voltak?";
			link.l1 = "Mert ott voltam. Láthatjuk a különbséget az embereid, a kalózok és a Rivadók között. A csoportot Mary Casper és Chad Kapper vezette. Szükséged van még bizonyítékokra?";
			link.l1.go = "shark_2";
		break;
		
		case "shark_2":
			dialog.text = "Csak azt tudom biztosítani, hogy nekem és az embereimnek semmi közünk hozzá.";
			link.l1 = "Errôl az admirálisnak kell meggyôzôdnie, és ez nem lesz könnyû. Dodson nagyon dühös az összes narválra a támadás után. Háborút fog hirdetni nektek - leállítja az ellátást, és minden adandó alkalommal lövöldözni fog az embereitekre. És ez nem csak szavakból áll.";
			link.l1.go = "shark_3";
		break;
		
		case "shark_3":
			dialog.text = "Remélem, az admirális megérti, hogy mit fog tenni. Kételkedik abban, hogy az én embereim is tudnak lôni?";
			link.l1 = "Szerintem igen. Készen áll arra, hogy a 'San Augustine' erôddé alakítsa, és addig harcoljon, amíg mindannyian éhen nem halnak. Emellett Dodson beszélni fog Rivadossal, és együttmûködést ajánl nekik. Az admirális és Rivados ellen együtt nem lesz esélyetek.";
			link.l1.go = "shark_4";
		break;
		
		case "shark_4":
			dialog.text = "Bassza meg! De mi nem veszünk részt ebben a kísérletben! Miért kell az egész klánnak fizetnie annak a hülye lánynak, Marynek és egy rakás söpredéknek a legénységembôl?\nMellesleg, beszéljünk a logikáról, Marlow megölésével Dodson maga provokálta Mary-t és a katonáimat. Pontosan ez történik, ha ilyen aljasságot követsz el.";
			link.l1 = "Semmit sem értesz. Magát becsapták. Miért vagy olyan biztos benne, hogy Dodson ölte meg Alant? Valójában azt hiszi, hogy maga tette, hogy elfoglalja a helyét...";
			link.l1.go = "shark_5";
		break;
		
		case "shark_5":
			dialog.text = "Leszarom, hogy mit gondol. Minden bizonyíték ellene szól. Csak ô és az emberei jutottak be a börtönbe. Alan az ô kezében volt. Red Mary sokat mesélt nekem. Mielôtt Alant meggyilkolták, Dodson személyesen látogatta meg a börtönt, és ezt nem gyakran teszi.";
			link.l1 = "Látta a halálát?";
			link.l1.go = "shark_6";
		break;
		
		case "shark_6":
			dialog.text = "A fenébe! Persze, hogy nem láttam.";
			link.l1 = "És Chimiset is. Igen-igen, Rivados varázsló, aki Alan mellett ült. Ôt is ott gyilkolták meg nemrég. Egy nappal a halála elôtt jártam a börtönben, és beszélgettem vele. Milrow-t Chad Kapper, a Shark hajóskapitánya ölte meg.";
			link.l1.go = "shark_7";
		break;
		
		case "shark_7":
			dialog.text = "Ez igaz?";
			link.l1 = "Gondoljon bele: Chimiset nem érdekelte az admirálissal való kapcsolata. Nem volt oka hazudni. Az öreg varázsló félt Chadtôl, feltételezte, hogy ô lesz a következô. Igaza volt, Chad megölte ôt, amint megtudta, hogy az admirális szabadon fogja engedni.";
			link.l1.go = "shark_8";
		break;
		
		case "shark_8":
			dialog.text = "De miért akarta Kapper Alan halálát?";
			link.l1 = "A fenébe is, hát nem érti igazán? Már mondtam, hogy Kapper Red Maryvel dolgozott. El akarta foglalni Shark pozícióját, és erre egy ravasz tervet készített. Alan Milrow megölése és a pletykák terjesztése arról, hogy Sharknak köze van a halálához, ellenségessé tette a Narwhal klánt az admirálissal szemben...";
			link.l1.go = "shark_9";
		break;
		
		case "shark_9":
			dialog.text = "";
			link.l1 = "A buta Mary bízott benne, és a barátja igazi gyilkosának oldalára állt. Meggyôztek néhány narválcápát, hogy csatlakozzon hozzájuk, Marynek bizonyára könnyû dolga volt. Aztán megszerveztek egy támadást az admirális ellen Fazio kabinjában, aki kénytelen volt megírni egy meghívót az admirálisnak...";
			link.l1.go = "shark_10";
		break;
		
		case "shark_10":
			dialog.text = "";
			link.l1 = "Van egy levelem Faziótól, ami mindent megmagyaráz. Chimiset megölte Chad, mint veszélyes tanút. Együttmûködött a narválokkal, és Rivados nagyon örülne, ha ezt a Cápával való beszélgetésük során hallaná. Könnyen bebizonyítjuk Fekete Eddie-nek, hogy Chad a maguk fajtából lett, ha megmutatjuk ezt a levelet.";
			link.l1.go = "shark_11";
		break;
		
		case "shark_11":
			dialog.text = "Hm. Minden ászod megvan, akkor mit keresel itt? Akarsz tôlem valamit, igaz?";
			link.l1 = "Igen, akarok. Mert azt hiszem, hogy ez az egész Chad terve volt, és te nem vagy benne. Chad megcsalta Mary-t, ô hívta a barátait a klánodból, hogy segítsenek neki, ez egy egész történet. Legalábbis nem találtam bizonyítékot ellened vagy bármelyik másik narvál ellen...";
			link.l1.go = "shark_12";
		break;
		
		case "shark_12":
			dialog.text = "";
			link.l1 = "De ez nem jelenti azt, hogy nem maradt más összeesküvô. Azt akarom, hogy keressétek meg ôket. Akkor talán mészárlás nélkül elintézhetjük a dolgokat.";
			link.l1.go = "shark_13";
		break;
		
		case "shark_13":
			dialog.text = "Már mondtam, hogy az embereim közül senki más nem vett részt benne. Marlow halála után Mary lényegében elhagyta a klánt, és bezárkózott a kunyhójába. Igazából fogalmam sincs, hogyan sikerült rávennie másokat, hogy részt vegyenek benne, de úgy tûnik, sikerült neki. Esküszöm, hogy sem én, sem bárki más a klánomból nem cselekszik az admirális ellen.\nTúl sok embert vesztettünk mostanában, ezért nem akarunk most belelépni egy zûrös ügybe. Nem félek az admirális támadásától, még Rivadossal összefogva sem. A narválok igazi harcosok, és ezt be fogjuk bizonyítani az utolsó csatánkban. De ez értelmetlen lenne\nMár eldöntöttük, hogy békét kötünk az admirálissal. A Rivados az más kérdés, mi nem tárgyalunk a Negrókkal. Kész vagyok személyesen bocsánatot kérni az admirálistól, bocsánatot kérni a gyanúmért, amit Milrow halála és az életére irányuló támadás okozott. A Bibliára esküszöm, hogy bizonyítsam ôszinteségemet. Magának és Dodsonnak ez megfelel?";
			link.l1 = "Nekem igen. Biztos benne, hogy nem kell trükköket várni az embereitôl?";
			link.l1.go = "shark_14";
		break;
		
		case "shark_14":
			dialog.text = "Abszolút. Tájékoztatom a klánomat Alan Milrow valódi gyilkosáról. Az embereim viszonya az admirálishoz azonnal megváltozik, biztosíthatom önöket. Mondja, szükség lesz ezután mészárlásra?";
			link.l1 = "Nem, nem lesz. Azért vagyok itt, hogy megakadályozzam. Bízom magában, Donald, és megpróbálom meggyôzni Sharkot. Van még néhány érvem... Viszlát, Donald!";
			link.l1.go = "shark_15";
		break;
		
		case "shark_15":
			DialogExit();
			sld = characterFromId("Dodson");
			sld.dialog.currentnode = "narval"; // ноду Акуле
			AddQuestRecord("SharkHunt", "26");
			NextDiag.CurrentNode = "narval_wait";
		break;
		
		case "narval_wait":
			dialog.text = "Beszéltél már az admirálissal? Van valami eredmény?";
			link.l1 = "Már dolgozom rajta. Késôbb találkozunk...";
			link.l1.go = "exit";
			NextDiag.TempNode = "narval_wait";
		break;
		
		case "shark_16":
			dialog.text = "Beszéltél már az admirálissal? Van valami eredmény?";
			link.l1 = "Igen, van. A bocsánatkérésedet elfogadom, a klánod vádja nem állja meg a helyét. Sôt, van még valami, Shark felajánlja neked, hogy látogass el hozzá, hogy megbeszéljük a Narwhals és a kalózok közötti jövôbeli békés megállapodás feltételeit.";
			link.l1.go = "shark_17";
		break;
		
		case "shark_17":
			dialog.text = "Hogy ôszinte legyek, nem számítottam rá... Ez egy nagyszerû hír. Talán még a klánunk ellátásának árait és a Rivadosra vonatkozó új politikát is át tudjuk majd gondolni.";
			link.l1 = "Ez csak téged és az admirálist érinti.";
			link.l1.go = "shark_18";
		break;
		
		case "shark_18":
			dialog.text = "Igen, természetesen. Nagy szolgálatot tettél a Narwhal klánnak azzal, hogy megakadályoztad az embereim értelmetlen vérontását, sôt talán még a teljes megsemmisülését is. Fogadd el hálám jeléül ezt a tornyos muskétát, nem fogsz találni más ilyen fegyvert\nMellett, ugyanúgy látogathatod a korlátozott területeinket, mint bármelyik klántag.";
			link.l1 = "Köszönöm! Viszontlátásra, sok dolgom van még.";
			link.l1.go = "shark_19";
		break;
		
		case "shark_19":
			GiveItem2Character(pchar, "mushket6"); 
			Log_Info("Kaptál egy torony egérkardot");
			PlaySound("interface\important_item.wav");
			dialog.text = "Sok szerencsét. Ha bármi kérdésed van, keress meg.";
			link.l1 = "Megvan. Viszlát!";
			link.l1.go = "exit";
			CloseQuestHeader("SharkHunt");
			bDisableFastReload = false; // belamour legendary edition
			pchar.questTemp.LSC.nrv_friend = "true"; //флаг на проход по кораблям нарвалов
			NextDiag.TempNode = "grinspy_wait";
			for (i=1; i<=6; i++)
			{
				sld = CharacterFromID("NarvalSold_"+i);
				LAi_SetWarriorType(sld);
				LAi_warrior_SetStay(sld, true);
			}
			for (i=1; i<=3; i++)
			{
				sld = CharacterFromID("NarvalProt_"+i);
				LAi_SetWarriorType(sld);
				LAi_warrior_SetStay(sld, true);
			}
			AddSimpleRumourCityTip("Azt mondják, hogy Donald, Greenspen, a Narwhals vezetôjének barátja vagy. Nos, Rivados most már utál téged...", "LostShipsCity", 5, 2, "LSC", "");
			AddSimpleRumourCityTip("Azt mondják, hogy most már narvál vagy. Vagy az admirális parancsnoksága alatt szolgálsz? Nem értem...", "LostShipsCity", 5, 2, "LSC", "");
			AddSimpleRumourCityTip("Hallottam, hogy békét kötöttél az admirális és a Narwhals között. Hm, Rivados biztos megôrült emiatt...", "LostShipsCity", 5, 2, "LSC", "");
			AddSimpleRumourCityTip("Tehát Chad Kapper volt Alan Milrow gyilkosa! Ez meglepô!", "LostShipsCity", 5, 2, "LSC", "");
		break;
		
		case "grinspy_wait": // стал другом
			if (pchar.questTemp.LSC == "return" && !CheckAttribute(npchar, "quest.return_isl"))
			{
				dialog.text = "Ho! "+GetFullName(pchar)+"! Te... nem, ez lehetetlen! Te élsz?!";
				link.l1 = "A halálomról szóló hírek egy kicsit tévesek voltak, Donald. Ha-ha, örülök, hogy látlak!";
				link.l1.go = "exit";
				npchar.quest.return_isl = "true";
				break;
			}
			dialog.text = "A-ah, barátom "+GetFullName(pchar)+"! Szükséged van valamire?";
			link.l1 = "Nem, nem kell. Csak üdvözölni akartalak.";
			link.l1.go = "exit";
			NextDiag.TempNode = "grinspy_wait";
		break;
		
		case "negotiations":
			dialog.text = "Milyen üzleted van számomra?";
			link.l1 = "Egy nagyon kellemetlen dologra, Donald. Volt egy merénylet Steven életére. A klánod harcosai is részt vettek benne.";
			link.l1.go = "negotiations_1";
		break;
		
		case "negotiations_1":
			dialog.text = "Errôl nem tudok. Miért gondolod, hogy az én embereim is benne voltak?";
			link.l1 = "Mert én személyesen öltem meg néhányat közülük Chad Kapperrel, az admirális hajóskapitányával együtt, aki felelôs ezért az egész zûrzavarért. Egyedül nem volt képes rá, ezért az embereid sokat segítettek neki. Az admirális tudja ezt, és nagyon-nagyon dühös.";
			link.l1.go = "negotiations_2";
		break;
		
		case "negotiations_2":
			dialog.text = "Az én embereim? Pontosan kiket, meg tudja nevezni ôket?";
			link.l1 = "Nem mutatkoztak be. Csak lövöldöztek és vívtak. Az emberei vakmerôek. Még a sajátjaikat is megtámadják. A pokolba velem vagy az admirálissal, de megkísérlik megölni a lányt?";
			link.l1.go = "negotiations_3";
		break;
		
		case "negotiations_3":
			dialog.text = "Hm. Kirôl beszélsz?";
			if (pchar.questTemp.LSC.Mary == "alive")
			{
				link.l1 = "Kirôl beszélek? A Red Mary elleni támadásról beszélek. Két narvál megpróbálta megölni. A kritikus pillanatban jutottam el a kabinjához egy véletlen folytán. Megölték volna, ha késôbb jövök. Nem kérdeztem meg a nevüket, sajnálom, nem volt idôm beszélgetni velük, de Mary azt mondta, hogy narválok voltak.";
				link.l1.go = "negotiations_4";
			}
			else
			{
				link.l1 = "Kikrôl beszélek? A Vörös Mária elleni támadásról beszélek, és arról a két narwhalról, akik megölték ôt."
				link.l1.go = "negotiations_6";
			}
		break;
		
		case "negotiations_4":
			dialog.text = "Micsoda? - Nem tudom. Miért nem mondta el nekem?! Azonnal cselekedtem volna!";
			link.l1 = "Nemrég még a kunyhóját is félt elhagyni. Nemrég vitatkozott veled, miért kellett volna hozzád rohannia és a segítségedet kérnie?";
			link.l1.go = "negotiations_5";
		break;
		
		case "negotiations_5":
			dialog.text = "Nem veszekedtem vele! Lehetetlen dolgokat követelt tôlem, durván elbeszélgettünk, és én elküldtem. De ez nem jelenti azt, hogy...";
			link.l1 = "Rendben, mindegy. Végül is, most már minden probléma megoldódott. De a férfiak között vannak gazemberek, ez tény.";
			link.l1.go = "negotiations_7";
		break;
		
		case "negotiations_6":
			dialog.text = "Ez tény. Narwhalok ölték meg? Miért? Miért?";
			link.l1 = "Chad Kapper parancsára, Donald. Túl sokat tudott, és nem akart segíteni Chadnek. És most szegény lány meghalt!";
			link.l1.go = "negotiations_7";
		break;
		
		case "negotiations_7":
			dialog.text = "Esküszöm, nem tudtam róla!";
			link.l1 = "Persze, hogy nem... De beszéljünk az admirálisról. Chad Kapper szervezte a merényletet, és az emberei segítettek neki. Megpróbálták megmérgezni Dodsont, és én alig tudtam megakadályozni.";
			link.l1.go = "negotiations_8";
		break;
		
		case "negotiations_8":
			dialog.text = "Én nem rendeltem el semmi ilyesmit. Dodson tisztában van vele, hogy nem támogatom a néhai Alan politikáját, és úgy gondolom, hogy egy sovány kompromisszum jobb, mint egy kövér per.";
			link.l1 = "Biztosítania kell benne az admirálist, és ez nem lesz könnyû. Dodson nagyon dühös az összes Narwhalra a kísérlet után. Ô fog hadat üzenni nektek.";
			link.l1.go = "negotiations_9";
		break;
		
		case "negotiations_9":
			dialog.text = "Remélem, hogy az admirális megérti a tetteit. Kételkedik abban, hogy az embereim vissza tudnak lôni?";
			link.l1 = "De igen. Úgy gondolja, hogy a klánotok egy banditacsapat, és el kell pusztítani, mielôtt elkezdenétek mindenkit megölni. Különben is, erôs kapcsolataink vannak Rivadosszal. Egyszerûen beszélhetek Fekete Eddie-vel, és felajánlhatom neki a szövetséget. Nem fogsz mindannyiunkkal szembeszállni.";
			link.l1.go = "negotiations_10";
		break;
		
		case "negotiations_10":
			if (pchar.questTemp.LSC.Mary == "alive") sTemp = "Hívd fel Red Mary-t, ha nem hiszel nekem, és kérdezd meg tôle! Ô majd megerôsíti.";
			else sTemp = "Van egy levelem Chad-tôl Mary-nek, ami mindent bizonyít.";
			dialog.text = "Bassza meg! Miért kell az egész klánnak fizetnie néhány idióta tetteiért? Ne hidd, hogy megijedtem. Harcosok vagyunk, és ezt az utolsó csatánkban is be fogjuk bizonyítani. De én igazságot akarok. Valójában az admirális a felelôs Alan Milrow megöléséért a börtönben.";
			link.l1 = "Hogyan lehetsz te a vezetô, Donald... Nem tudsz sem Maryrôl, sem Alanrôl. Chad Kapper ölte meg. "+sTemp+" Azért tette, hogy a Narwhalok ellenségessé váljanak az admirálissal szemben, és néhányukat a maga oldalára rángassa.";
			link.l1.go = "negotiations_11";
		break;
		
		case "negotiations_11":
			dialog.text = "Értem. Rendben. Beszélgessünk másképp. Valamilyen célból van itt, igaz? Mit akarsz?";
			link.l1 = "Nem akarok véres felfordulást a szigeten. Nem akarom, hogy emberek haljanak meg. Nem tetszik az ötlet, hogy az összes narwhalt ki kell irtani, bár biztosíthatlak, hogy Rivados és mi képesek vagyunk erre. Azt is gondolom, hogy az egész klánnak nem szabad felelnie néhány szemétláda tetteiért...";
			link.l1.go = "negotiations_12";
		break;
		
		case "negotiations_12":
			dialog.text = "";
			link.l1 = "De az én szavazatom nem lesz elég - hivatalosan is biztosítanod kellene az admirálist, hogy a kísérletet nem te hagytad jóvá, és a klánod nem tervezi Dodson megölését.";
			link.l1.go = "negotiations_13";
		break;
		
		case "negotiations_13":
			dialog.text = "Mit tehetnék? Kész vagyok bocsánatot kérni a kísérletért és a Marlow halálával kapcsolatos gyanúmért. Biztosíthatom, hogy a narválok nem terveznek semmit ellene, és a szent Bibliára esküszöm. Ön és Dodson ezt elegendônek találják?";
			link.l1 = "Igen. Biztos vagyok benne, hogy Dodsonnak is megfelel, ha személyesen látogatja meg. De elôbb elmondom neki a szándékaitokat, és aztán újra meglátogatlak az eredményekkel.";
			link.l1.go = "negotiations_14";
		break;
		
		case "negotiations_14":
			dialog.text = "Rendben. Várni fogok.";
			link.l1 = "Hamarosan visszajövök...";
			link.l1.go = "negotiations_15";
		break;
		
		case "negotiations_15":
			DialogExit();
			sld = characterFromId("Dodson");
			sld.dialog.currentnode = "peace"; // ноду Акуле
			sld = characterFromId("Dexter");
			sld.dialog.currentnode = "First time"; 
			LAi_SetStayTypeNoGroup(sld);
			ChangeCharacterAddressGroup(sld, "SanAugustineResidence", "goto", "goto11");
			AddQuestRecord("SharkHunt", "56");
			NextDiag.CurrentNode = "narval_wait";
		break;
		
		case "negotiations_17":
			dialog.text = "Beszéltél már az admirálissal? Van valami eredmény?";
			link.l1 = "Igen. Ha hivatalos látogatást teszel nála, akkor a probléma megoldódik.";
			link.l1.go = "negotiations_18";
		break;
		
		case "negotiations_18":
			dialog.text = "Hogy ôszinte legyek, nem számítottam rá... Ez nagyszerû hír.";
			link.l1 = "Igen, tudod, én is örülök neki.";
			link.l1.go = "negotiations_19";
		break;
		
		case "negotiations_19":
			dialog.text = "Nagy szolgálatot tettél a Narvál klánnak azzal, hogy megakadályoztad az értelmetlen mészárlást, és talán még a népem teljes kiirtását is. Neked adom ezt a tornyos muskétát - nem fogsz találni más hasonló fegyvert. Emellett minden korlátozás nélkül látogathatod a hajóinkat.";
			if (pchar.questTemp.LSC.Mary == "alive") 
			{
				link.l1 = "Köszönöm. Nagyon értékes ajándék. Igen, Donald, még egy dolog: kössön békét Vörös Máriával. Forrófejû, de ôszinte és becsületes. A veled való vitatkozás miatt elszakadt a klántól, és ez majdnem az életébe került.";
				link.l1.go = "negotiations_20";
			}
			else
			{
				link.l1 = "Köszönöm. Nagyon értékes ajándék. És nagyon örülök, hogy ilyen jól végzôdött.";
				link.l1.go = "negotiations_21";
			}
		break;
		
		case "negotiations_20":
			dialog.text = "Mondd meg neki, hogy kérem, bocsásson meg nekem, amiért megbántottam ôt és azt a két szemetet, akik meg merték támadni. Ti ketten... barátok vagytok, igazam van?";
			link.l1 = "Igazad van, Donald. Megmondom neki. És nagyon örülök, hogy minden ilyen jól végzôdött.";
			link.l1.go = "negotiations_21";
		break;
		
		case "negotiations_21":
			GiveItem2Character(pchar, "mushket6"); 
			Log_Info("Kaptál egy torony muskétát");
			PlaySound("interface\important_item.wav");
			dialog.text = "Sok szerencsét. Ha bármi kérdésed van, keress meg.";
			link.l1 = "Jól van. Viszlát!";
			link.l1.go = "exit";
			CloseQuestHeader("SharkHunt");
			bDisableFastReload = false; // belamour legendary edition
			pchar.questTemp.LSC.nrv_friend = "true"; //флаг на проход по кораблям нарвалов
			NextDiag.TempNode = "grinspy_wait";
			sld = characterFromId("Mary");
			sld.quest.donald = "true";
			LocatorReloadEnterDisable("CeresSmithy", "reload3", false);
			LocatorReloadEnterDisable("CeresSmithy", "reload4", false); // открываем Церес изнутри
			for (i=1; i<=6; i++)
			{
				sld = CharacterFromID("NarvalSold_"+i);
				LAi_SetWarriorType(sld);
				LAi_warrior_SetStay(sld, true);
			}
			for (i=1; i<=3; i++)
			{
				sld = CharacterFromID("NarvalProt_"+i);
				LAi_SetWarriorType(sld);
				LAi_warrior_SetStay(sld, true);
			}
			// здесь почищу весь хлам, который накопился
			DeleteAttribute(pchar, "questTemp.LSC.Donald_enter"); // атрибут гардов
			DeleteAttribute(pchar, "questTemp.LSC.Florentina");
			DeleteAttribute(pchar, "questTemp.LSC.Dodson_poison");
			DeleteAttribute(pchar, "questTemp.LSC.Dodson_warning");
			DeleteAttribute(pchar, "questTemp.LSC.Whiskey_clear");
			DeleteAttribute(pchar, "questTemp.LSC.CapperDie_Aeva");
			AddSimpleRumourCityTip("Azt mondják, hogy Donald, Greenspen, a Narwhals vezetôjének barátja vagy. Nos, Rivados most már utál téged...", "LostShipsCity", 5, 2, "LSC", "");
			AddSimpleRumourCityTip("Azt mondják, hogy most már narvál vagy. Vagy az admirális parancsnoksága alatt szolgálsz? Nem értem...", "LostShipsCity", 5, 2, "LSC", "");
			AddSimpleRumourCityTip("Hallottam, hogy békét kötöttél az admirális és a Narwhals között. Hm, Rivados biztos megôrült emiatt...", "LostShipsCity", 5, 2, "LSC", "");
			AddSimpleRumourCityTip("Tehát Chad Kapper volt Alan Milrow gyilkosa! Ez meglepô!", "LostShipsCity", 5, 2, "LSC", "");
			AddSimpleRumourCityTip("Vigyázz Vörös Máriára, mert szerencsés vagy, hogy vele lehetsz - olyan vakmerô! Mindig bajba kerül...", "LostShipsCity", 20, 5, "LSC", "");
		break;
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Mit csinálsz ott, ah? Tolvaj!", "Csak nézd meg ezt! Amint elmerültem az elmélkedésben, úgy döntöttél, hogy megnézed a mellkasomat!", "Úgy döntöttél, hogy megnézed a ládámat? Ezt nem úszod meg!");
			link.l1 = "Basszus!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Mi?! Úgy döntöttél, hogy megnézed a ládámat? Ezt nem úszod meg!";
			link.l1 = "Ostoba lány!";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//замечание по обнажённому оружию
		case "LSCNotBlade":
			dialog.text = LinkRandPhrase("Figyeljen, jobb, ha elveszi a fegyverét. Ideges leszek tôle.", "Tudod, a pengével való rohangálást itt nem tolerálják. Vidd el.", "Figyelj, ne játszd a középkori lovagot, aki karddal rohangál. Vidd el, nem illik hozzád...");
			link.l1 = LinkRandPhrase("Jól van.", "Persze.", "Ahogy mondod...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "Figyeljen, én a város polgára vagyok, és arra kérem, hogy tartsa vissza a pengéjét.", "Figyelj, a város polgára vagyok, és arra kérnélek, hogy tartsd vissza a pengédet.");
				link.l1 = LinkRandPhrase("Jól van.", "Persze.", "Ahogy mondod...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, "Légy óvatos, haver, amikor fegyverrel futsz. Ideges tudok lenni...", "Nem szeretem, ha a férfiak fegyverrel a kezükben sétálnak elôttem. Megijeszt...");
				link.l1 = RandPhraseSimple("Megvan.", "Elviszem.");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;
// <-- специальные реакции
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
