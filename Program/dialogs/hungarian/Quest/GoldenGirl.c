// диалоги персонажей по квесту Дороже золота
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;
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
			link.l1 = "Mennem kell...";
			link.l1.go = "exit";
		break;
		
		// вестовой в Сен Пьере
		case "fraofficer":
			dialog.text = "Charles de Maure kapitány! Végre! Ôexcellenciája Jacques Dille do Parkuet látni akarja önt! Ez sürgôs!";
			link.l1 = "Miért nem vagyok meglepve? Rendben, kérem, mondja meg Ôexcellenciájának, hogy hamarosan jövök.";
			link.l1.go = "fraofficer_1";
		break;
		
		case "fraofficer_1":
			DialogExit();
			chrDisableReloadToLocation = false;//открыть локацию
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "", 10.0);
			LocatorReloadEnterDisable("FortFrance_town", "reload1_back", true);
			LocatorReloadEnterDisable("FortFrance_town", "reload2_back", true);
			LocatorReloadEnterDisable("FortFrance_town", "gate_back", true);//закрыть выходы из города
			LAi_LocationDisableOfficersGen("FortFrance_townhall", true);//офицеров не пускать
			pchar.questTemp.GoldenGirl = "message";
			AddQuestRecord("GoldenGirl", "1");
		break;
		
		// маркиза Джулиана Бото
		case "Julianna":
			dialog.text = "A szemem csal, ha ez maga Charles de Maure! Nem túl gyakran fogadok ilyen fogadtatásokat, és örülök, hogy sikerült idôt szakítania szerény kolostoromra. Szerencsés vagyok! Ez megérdemel egy tósztot!";
			link.l1 = "Üdvözlöm, asszonyom. Bocsássa meg, hogy esetleg csalódást okozok a modoromban - nagyon régen voltam utoljára ilyen... eseményeken. Egy hajó etikettje alárendeltségre, tiszta sálra és egy csésze frissítô kávéra szûkül minden reggel.";
			link.l1.go = "Julianna_1";
		break;
		
		case "Julianna_1":
			dialog.text = "Olyan bájos, kapitány úr, hogy még mindig magánál van a párizsi gloss. Látom félénk pillantását e fûszerezett és sózott maszk alatt. Ne aggódjon, annyira örülök, hogy végre találkozunk, hogy sok mindent meg tudok bocsátani magának. Egyelôre. Majd meglátjuk, hogy mi lesz velünk a jövôben. Bort? Vöröset vagy fehéret?";
			link.l1 = "Tökéletes pillanat egy rumos vicchez, de sajnos nincs hozzá kedvem, sajnálom. Szívesen megiszom bármit, amit a csinos kezed tölt nekem.";
			link.l1.go = "Julianna_2";
		break;
		
		case "Julianna_2":
			dialog.text = "Szép volt. De ragaszkodom hozzá. A borízlés sokat elárul egy emberrôl, és én ma este mindent meg akarok tudni rólad. Szóval újra megkérdezem: vörös vagy fehér?";
			link.l1 = "Ahogy akarod. Látom, hogy vöröset iszik. Én is - én is szeretnék megtudni valamit rólad.";
			link.l1.go = "Julianna_3";
			link.l2 = "Ebben az esetben én fehéret iszom, de te választasz. Ennek mindkét irányban mûködnie kell, nem gondolja?";
			link.l2.go = "Julianna_4";
		break;
		
		case "Julianna_3":
			pchar.questTemp.GoldenGirl.Vine = "red";
			dialog.text = "Nagyszerû, akkor most én jövök? Ez itt a burgundi Pinot Noir, a borászok úgy hívják 'a naughty girl'. Nem egy könnyen kezelhetô fajta, és az utóíze is eléggé megtévesztô tud lenni. Elégedett?";
			link.l1 = "Pinot Noir, mi? Nekem megfelel. Megbízhatatlan és titokzatos, elsôre sivár íz, de hagyja egy kicsit lélegezni, és meglepôdik. Árnyalatok és ízek könnyed tánca, egy tapasztalt ínyenc választása. Az elsô benyomás hazudik, nem igaz? A szemére iszom, hölgyem!";
			link.l1.go = "Julianna_5";
		break;
		
		case "Julianna_4":
			pchar.questTemp.GoldenGirl.Vine = "white";
			dialog.text = "Pompás, akkor most én jövök? Csodálatos Sauvignon Blanc-om van, egyenesen a Loire völgyébôl. Elég vad, szinte érzed, ahogy pukkan a nyelveden. És a cseresznye a tetején - egy kis puskaporos jegy. Gondolom, van valami közös bennetek.";
			link.l1 = "Én jobbra számítottam, talán valami rizlingre. Hát legyen ez az egyszerû, nyár és lôpor illatú brutál. Hallottál már arról, hogy egyesek összekeverik a pipi de chattel? Iszom a mosolyodra, ami olyan fényes, mint ezek a zafírok!";
			link.l1.go = "Julianna_5";
		break;
		
		case "Julianna_5":
			dialog.text = "Figyelemre méltó, Charles! Szólíthatlak így? Nem tévedtem veled kapcsolatban, máskor te lennél az éjszakám sztárja. De sajnos, kapitányom, ma erôs vetélytársa van. Úgy tûnik, hogy egy botrány küszöbén állunk, látja?";
			link.l1 = "Dühös hangokat hallok. Ki ez a kellemetlen úr, és mit tett, hogy nem tetszett a mi drága kormányzónknak?";
			link.l1.go = "Julianna_6";
		break;
		
		case "Julianna_6":
			dialog.text = "Ez 'kellemetlen' monsieur Angerran de Chievous, de Levi Vantadur gróf el nem ismert fattyúja. Ön az ô vitatémájukat szórakoztatja. De Chievous évek óta próbálja elnyerni a kegyeimet, és követett ide, azt gondolván, hogy helyettesítheti az apját helyettem. Bár nem törvényes fiú, de gazdag és hatalmas. A makacsság a másik tulajdonsága, egyeseknél ez helyettesíti a bölcsességet. Éppen az érkezésed elôtt kezdtek el vitatkozni Jacques-kal a nyilvánvaló témáról. Az ô kiválósága mindig megható módon védelmez engem, látnod kellene! Gyere, figyeljük meg, hogy ezúttal mi lesz a vége.";
			link.l1 = "Bajt érzek a levegôben... Miért van mindig valami bökkenô, még egy ilyen csodálatos éjszakában is...";
			link.l1.go = "Julianna_7";
		break;
		
		case "Julianna_7":
			dialog.text = "Tessék, Charles?";
			link.l1 = "Felejtsd el. Kérem, mutasson be a tolakodó barátjának, aztán majd meglátjuk...";
			link.l1.go = "Julianna_8";
		break;
		
		case "Julianna_8":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "quest", "quest1", "GoldenGirl_PartyTalk", -1);
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
		break;
		
		case "Julianna_9":
			dialog.text = "Monsieur, engedje meg, hogy bemutassam Önnek kedves vendégemet - Charles de Maure kapitány, hús-vér személyében megtisztelt bennünket látogatásával! Ilyen híres személyiségek nem gyakran vendégeskednek nálunk.";
			link.l1 = "...";
			link.l1.go = "Julianna_10";
		break;
		
		case "Julianna_10":
			DialogExit();
			sld = characterFromId("FortFrance_Mayor");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.3);
		break;
		
		case "Julianna_11":
			dialog.text = "Charles, nem tetszik, hova vezet ez az egész! Jacques süket az érveimre, míg Angerran biztosan készül valamire. Ennek a harcnak célja volt, és szükségem van a segítségedre!";
			link.l1 = "Attól tartok, nem tudlak követni... Mit is tehetnék itt? Már így is visszautasította, hogy párbajozzak velem...";
			link.l1.go = "Julianna_12";
		break;
		
		case "Julianna_12":
			dialog.text = "Kapitány, kérem, ne okozzon csalódást. Az elôbb még a beszélgetések virtuóza voltál, most pedig a világod kettészakadt olyan dolgokra, amiket karddal meg tudsz bökni, és olyanokra, amiket nem. Gondolkodjon a dobozon kívül! Romboljuk el Angerran játékát. Egyedül akarja kihívni szegény Jacques-ot, de az csak unalmas! Rendezzünk egy tornát! Itt több úriember is komoly téteket tud támogatni, és a szerencséje már legendásan ismert! Talán a kártyák ma este kedvezni fognak neki?";
			link.l1 = "Nem egészen értem, hogyan akadályozza meg de Chievous-t abban, hogy harcoljon a mi édes kormányzónkkal, de benne vagyok, milady. Bármit, hogy elvethessem azt a kis mosolyát.";
			link.l1.go = "Julianna_13";
		break;
		
		case "Julianna_13":
			dialog.text = "Pompás, most menjen az asztalhoz, és egyen valamit, hosszú lesz az éjszaka. Ha készen vagytok, gyertek ki az elôszobába, több helyiségre lesz szükségünk. Addig is rendezek egy mûsort, rábeszélve másokat, hogy adjanak nekem látványosságokat és nagy tétû játékokat. Talán még kiabálni is fogok velük, hogy ezek a farkak észrevegyék az unalomba fulladó hölgyet. Kérem, ne avatkozzanak közbe, senkinek sem szabad megtudnia, hogy ma este egy csapatban vagyunk. Késôbb találkozunk, kapitányom!";
			link.l1 = "Bármit is mond, asszonyom, bármit is mond...";
			link.l1.go = "Julianna_14";
		break;
		
		case "Julianna_14":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "barmen", "stay", "GoldenGirl_JulianaPause", -1);
			AddQuestRecord("GoldenGirl", "4");
		break;
		
		case "Julianna_15":
			dialog.text = "Nos, gratulálok, sikerült! Egy kis büszkeség, némi elôítélet és voilá! Csinálj egy unott arcot, figyelnek minket. Hadd higgyék, hogy az ivás érdekel, nem én\nEgy verseny kezdôdik, nagy a tét, nincs második esély és visszavágó. Valahogy tudom, hogy már hozzászoktál ehhez. Meg fogod oldani. Ne feledd, Angerran biztosan készül valamire, lépni fog Jacques barátunk ellen, de a te érkezéseddel nem számolt. Legyél az ászom a kezében, mert a magabiztos, önelégült arcát látva sosem jó jel. Nyolc játékosunk van, de gondoskodtam róla, hogy a döntôig ne találkozz vele\nOh! Az elsô ellenfeled! Ezredes és az erôdünk parancsnoka. Tenger kontra szárazföld - méltó kihívás a katonai tapasztalattal rendelkezô vendégeknek! Taps!";
			link.l1 = "";
			link.l1.go = "Julianna_16";
		break;
		
		case "Julianna_16":
			DialogExit();
			DoQuestCheckDelay("GoldenGirl_CreateColonel", 0.5);
		break;
		
		case "Julianna_17":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Win")) 
			{
				dialog.text = "Nagyszerûen csináltad, Charles, egyszerûen nagyszerûen. Angerran és Jacques mindjárt szembe kerülnek egymással. Kár, hogy nem hallgattak rájuk, és nem halasztották el a tornát egy héttel. Igazán sztárparti pletykákat gyûjthetnék össze, amelyekbôl Párizsba utaznának! Nos, talán majd legközelebb. Úgy tûnik, hogy a következô ellenfeled méltó vetélytársa a szerencsédnek, egy igazi tengeri farkas, Moreno kapitány! Kapitányok, kérem!";
				link.l1 = "";
			}
			else
			{
				dialog.text = "Sajnos a szerencséje cserbenhagyta, kapitány. Sajnálom, de a játéknak vége. Angerran már Jacques ellen játszik, úgyhogy mennem kell. Viszontlátásra.";
				link.l1 = "Örömömre szolgált... asszonyom.";
			}
			link.l1.go = "Julianna_18";
		break;
		
		case "Julianna_18":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Cards");
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Win")) GoldenGirl_CreateCaptainMoreno();
			else GoldenGirl_CardsFail();
		break;
		
		case "Julianna_19":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Win")) 
			{
				dialog.text = "Gratulálok a megérdemelt gyôzelméhez, kapitány! Még mindig nem világos, hogy ki lesz az ellenfele a döntôben... Lépjünk félre egy kicsit. Halkabban, és figyelje azt az asztalt. Nézd, ott megy! Kezdem látni, mire készül Angerran! Sweet Jacques-ot már megfosztotta a pénzétôl, de nem engedi el az asztaltól. Amikor arra jártam, a szegény szerencsétlen néhány iratra játszott egy egész hajónyi rakományt. Sajnos a szerencse ma este nem az ô oldalán áll. Vagy valaki azt mondta neki, hogy ne legyen.";
				link.l1 = "Gondolod, hogy de Chievous csal?";
				link.l1.go = "Julianna_21";
			}
			else
			{
				dialog.text = "Sajnos a szerencséje cserbenhagyta, kapitány. Sajnálom, de a játéknak vége. Angerran már Jacques ellen játszik, úgyhogy mennem kell. Viszontlátásra.";
				link.l1 = "Örömömre szolgált... asszonyom.";
				link.l1.go = "Julianna_20";
			}
		break;
		
		case "Julianna_20":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Cards");
			GoldenGirl_CardsFail();
		break;
		
		case "Julianna_21":
			dialog.text = "Ha akarja, megteheti, de nincs rá bizonyítékom. A mi kedves kormányzónk jól bánik a kártyákkal, de az ellenfele is. Angerran még csak a szemét sem rebbentette, amikor a fregattjára játszott, képzelje csak el. Ha ezt a párbajt Párizsban vagy Lionban vívnánk, legenda lenne belôle, Charles! Mindazonáltal lehet, hogy ma este csak szerencséje van. Menjünk oda hozzájuk, és gyôzôdjünk meg róla a saját szemünkkel.";
			link.l1 = "...";
			link.l1.go = "Julianna_22";
		break;
		
		case "Julianna_22":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Cards");
			DeleteAttribute(pchar, "questTemp.GoldenGirl.Game");
			LAi_SetActorType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(pchar, "quest", "quest3", "GoldenGirl_Talking", -1); 
			LAi_ActorFollow(npchar, pchar, "", 10.0);
		break;
		
		case "Julianna_23":
			dialog.text = "Charles, fogj meg, vagy elesek... Vagy nem fogok - ezek az idióták észre sem fogják venni, hogy cselezek. Láttad ezt? Jacques, a fenébe a hülyeségeddel! Mint egy gyerek, Jézusom! Egy ostoba gyerek!";
			link.l1 = "Márkiné, nem hiszem, hogy értem magát.  Mi folyik ott az asztalnál? Mire játszanak?";
			link.l1.go = "Julianna_24";
		break;
		
		case "Julianna_24":
			dialog.text = "Majd én, Charles. A mi édes, ostoba Jacques-unk játszott velem. Angerran megtalálta egyetlen gyenge pontját, és a megfelelô pillanatban eltalálta.";
			link.l1 = "A francba! De én vagyok a következô a tornán, visszasakkozhatom a rohadt hajóját! Miért? Miért?";
			link.l1.go = "Julianna_25";
		break;
		
		case "Julianna_25":
			dialog.text = "Mert Angerran nagyon átgondolta, és mindent végigtervezett. Figyelj rám, nincs sok idônk. Neked is ugyanezt kell tenned vele. Fosszátok meg mindenétôl, vegyétek el az összes pénzét, az összes hajóját, provokáljátok! Vegyétek rá, hogy elveszítse a fejét a hírnévre, a becsületre, a szenvedélyre, bármire! Láttad, hogyan kell ezt ma este csinálni. Állítsd sarokba, és kényszerítsd, hogy tétet állítson fel\nKönyörgöm, Charles! Mindenre kész vagyok, de nem megyek hozzá. Így nem! Még Vantadur gróf sem áll ki egy becsületes kártyanyerés ellen, a kisujját sem mozdítja, hogy segítsen rajtam. Látod, a kártyák kurvára szentek a nemes embereknek, a fene egye meg ôket! Te vagy az utolsó és egyetlen reményem, Charles!";
			link.l1 = "Ne temesse még el a kormányzónkat, asszonyom. Talán visszaszerzi a hajóját? A szerencse asszonya egy szeszélyes... nô.";
			link.l1.go = "Julianna_26";
		break;
		
		case "Julianna_26":
			dialog.text = "Még mindig nem érted, ugye? A szerencsének nincs helye annál az asztalnál! Angerran de Chievous dönt mindenrôl. Ô találta ki, hogyan kaphat meg engem, és hogyan tarthatja távol az apját ettôl az egésztôl. Fogalmam sincs, mióta tervezi ezt, de mostanra már majdnem gyôzött. A játék az övé, és nekünk csak egy esélyünk van arra, hogy megtörjük. Tessék, fogd ezt! Meg fogom cselezni, adok egy-két percet. Használd okosan.";
			link.l1 = "Marquise... Valaki segítsen! A hölgy nem érzi jól magát! Gyorsan!";
			link.l1.go = "Julianna_27";
		break;
		
		case "Julianna_27":
			DialogExit();
			sld = characterFromId("Angerran");
			sld.dialog.currentnode = "Angerran_5";
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload3");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.5);
			GiveItem2Character(pchar, "obereg_5");
			GiveItem2Character(pchar, "totem_13");
			Log_Info("Ön amulettet kapott 'Teknôc'");
			Log_Info("Amulettet kaptál 'Joker'");
			PlaySound("interface\important_item.wav");
		break;
		
		case "Julianna_28":
			dialog.text = "Nem, nem, jól vagyok... Kicsit fülledt itt a levegô... Nagyon sajnálom, uraim. Egy pillanatra magára hagyom önöket egy kis friss levegôre. Folytathatják nélkülem is.";
			link.l1 = "...";
			link.l1.go = "Julianna_29";
		break;
		
		case "Julianna_29":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3", "Location_reserve_02", "goto", "goto1", "", 10.0); // уходит
			sld = characterFromId("Angerran");
			sld.dialog.currentnode = "Angerran_7";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			sld = characterFromId("FortFrance_Mayor");
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload3");
		break;
		
		case "Julianna_30":
			dialog.text = "Nem most és nem St. Pierre-ben, de ismerek valakit. Megígérem, Angerran, hogy ez egy méltó festmény lesz...";
			link.l1 = "...";
			link.l1.go = "Julianna_31";
		break;
		
		case "Julianna_31":
			DialogExit();
			sld = characterFromId("Angerran");
			sld.dialog.currentnode = "Angerran_21";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Julianna_32":
			dialog.text = "Angerran, te lehetetlen vagy! Tanulj meg veszíteni! Ez csak egy játék, és nem lehet mindent elôre megjósolni. Igya meg a borát, és öltözzön fel - a szabályok maradnak - egy vesztes elhagyja a mi kényelmes partinkat.";
			link.l1 = "Marquise, várjon...";
			link.l1.go = "Julianna_33";
		break;
		
		case "Julianna_33":
			DialogExit();
			sld = characterFromId("Angerran");
			sld.dialog.currentnode = "Angerran_24";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Julianna_34":
			dialog.text = "Ez már túl messzire megy, uraim! Azonnal hagyják abba! Mindannyian nagyon fáradtak vagyunk a fárasztó éjszaka után, és attól tartok, meg kell kérnem a vendégeimet, hogy búcsúzzanak el. Folytathatják a vitát holnap, ahogy az a becsületes emberekhez illik, hacsak meg nem gondolják magukat. De itt senki nem fog karon fogni, világos?";
			link.l1 = "...";
			link.l1.go = "Julianna_35";
		break;
		
		case "Julianna_35":
			DialogExit();
			sld = characterFromId("Angerran");
			sld.dialog.currentnode = "Angerran_27";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Julianna_36":
			dialog.text = "Charles, attól tartok, meg kell kérnem, hogy te is távozz. Menj fel az emeletre, és foglalj magadnak egy szobát. Mindent elintézek. Hálás vagyok mindenért, amit értem tettél, minden mértéket meghaladóan, de szükségem van egy kis idôre magamra, és te bizonyára rettenetesen fáradt vagy.";
			link.l1 = "Nem túl rossz, asszonyom, de egy ágyra nem mondok nemet. Ez az alkalmi parti jobban megütött, mint egy hatalmas ellenséges hajóraj. Megértem, hogy ez az egész önnek sem volt könnyû, márkinô. Pihenjen egy kicsit, és ne aggódjon, nem tartozik nekem semmivel. Most csak egy kis alvásra van szükségem.";
			link.l1.go = "Julianna_37";
		break;
		
		case "Julianna_37":
			dialog.text = "Gondoskodom róla, hogy délre felébreszthessék. Már hajnalodik, úgyhogy nem tudok már jó éjszakát kívánni. Aludj jól.";
			link.l1 = "Maga is, márkinô.";
			link.l1.go = "Julianna_38";
		break;
		
		case "Julianna_38":
			DialogExit();
			GoldenGirl_SleepInBrothel();
		break;
		
		case "Julianna_39":
			dialog.text = "Tessék, Charles. Hogy ôszinte legyek, egyáltalán nem aludtam, de te kipihentnek tûnsz. Te hogy aludtál? A reggeli már úton van.";
			link.l1 = "Az ön vendégszeretete legendás, asszonyom, de attól tartok, nincs idôm kiélvezni. Ôexcellenciája, de Chievous' másodpercek, az általam nyert hajók - az összes, vár rám.";
			link.l1.go = "Julianna_40";
		break;
		
		case "Julianna_40":
			dialog.text = "Nem csak a hajókat nyerte meg. Ez egy másik dolog, amirôl kérdezni akartam, Charles...";
			link.l1 = "Nem vagyok sem Jacques, sem Angerran, márki. Nem játszom a nôkkel, hogy elnyerjem a kegyeiket. Nem tartozik nekem semmivel.";
			link.l1.go = "Julianna_41";
			link.l2 = "A védelmem alatt állsz, márkinô. Sem Jacques, sem Angerran nem fogja magát zaklatni, ezt megígérhetem.";
			link.l2.go = "Julianna_42";
		break;
		
		case "Julianna_41":
			pchar.questTemp.GoldenGirl.J1 = "true";
			dialog.text = "Ön vagy mesésen becsületes, vagy szerelmes, Charles. És nem belém. De még egyszer, örökké hálás leszek neked teljes szívembôl. Ha bármiben a segítségedre lehetek - csak szólj.";
			link.l1 = "Julianne, az idô rohan, és a legnehezebb feladat elôtt állok. De Chievous egy söpredék, és még egy becsületes párbaj is gyorsan végzôdhet úgy, mint amit tegnap este megfigyelhettünk. Beszéljünk késôbb, amikor mindez végleg lezárult. Köszönöm a lehetôséget, hogy nyugodtan aludhattam, és várom a viszontlátást.";
			link.l1.go = "Julianna_43";
		break;
		
		case "Julianna_42":
			pchar.questTemp.GoldenGirl.J2 = "true";
			dialog.text = "Hálás vagyok neked teljes szívembôl, Charles... Hidd el, hogy a jutalmadnak lenni számomra is egyfajta gyôzelem. Mondjuk folytathatnánk ezt a beszélgetést egy... privátabb környezetben?";
			link.l1 = "Julianne, az idô rohan, és a legnehezebb feladat elôtt állok. De Chievous egy söpredék, és még egy becsületes párbaj is gyorsan végzôdhet úgy, mint amit tegnap este megfigyelhettünk. Beszéljünk késôbb, amikor mindez végleg lezárult. Köszönöm a lehetôséget, hogy nyugodtan aludhattam, és várom a viszontlátást.";
			link.l1.go = "Julianna_43";
		break;
		
		case "Julianna_43":
			dialog.text = "Akkor nem fogom tovább feltartani, kapitányom. De ne feledje, Angerran veszélyes. Nem tudom megítélni a harci képességeit, de több háborúban is részt vett, és harcolt Rocroiban. Hallottam néhány párbajról is, amit megnyert, fôleg pisztollyal. Legfôképp pedig, ahogy te magad is észrevetted, álnok típus. Kérlek, légy óvatos, és kérlek, hogy utána találkozzunk!";
			link.l1 = "Az óvatosság bámulatosan illik önhöz, márkinô. Higgye el, de Chievous nem az elsô fattyú, aki az utamba áll. Majd én megoldom. Most már tényleg el kellene mennem Ôexcellenciájához, hogy megbeszéljük a párbajügyet.";
			link.l1.go = "Julianna_44";
		break;
		
		case "Julianna_44":
			dialog.text = "Isten éltessen, kapitányom! És mondja meg Jacques-nak, hogy tartsa magát minél távolabb az otthonom ajtajától.";
			link.l1 = "Szavamat adom. Viszlát, márkiné!";
			link.l1.go = "Julianna_45";
		break;
		
		case "Julianna_45":
			DialogExit();
			GoldenGirl_ToGovernor();
		break;
		
		case "Julianna_46":
			dialog.text = "Kapitány, megcsinálta, micsoda megkönnyebbülés! Hogy ment? Vérzik?!";
			link.l1 = "Ez nem az én vérem... legalábbis nem az egész. Marquise, hol van de Chievous?";
			link.l1.go = "Julianna_47";
		break;
		
		case "Julianna_47":
			dialog.text = "Épp ugyanezt akartam kérdezni - nem tette le? Mi történt? Miért látom a fél város ôrségét odakint?";
			link.l1 = "Mondtam a kormányzónak, hogy veszélyben lehetsz. De Chievous megsebesült és elmenekült, ránk szabadította a banditáit. Mészárlás volt. Bár az ilyen történetek nem a te szép füleidnek valók. Vége van. Szabad vagy tôle és a mi 'sweet' Jacquesunktól.";
			link.l1.go = "Julianna_48";
		break;
		
		case "Julianna_48":
			dialog.text = "Ez nagyon rossz, Charles. Az olyan ellenségeket, mint Angerran de Chievous, végleg meg kell ölni, ha van rá lehetôség. Sok éve ismerem ezt az embert - nem egy megbocsátó típus. Elôbb vagy utóbb megtalálja az utat a bosszúhoz. De nem tetszik, ahogy görnyedsz, elintézték a sebedet?";
			link.l1 = "Csak egy karcolás, volt már sokkal rosszabb is. Fáj egy kicsit, ennyi. Köszönöm, hogy törôdik velem, asszonyom, de mennem kell...";
			link.l1.go = "Julianna_49";
		break;
		
		case "Julianna_49":
			dialog.text = "Kapitány, ön játszott értem, kockáztatva a hajóit és a vagyonát, ön harcolt értem egy üzletben, kockáztatva az életét és a karrierjét. A legkevesebb, amit tehetek önért, hogy ellátom a sebeit, és adok egy helyet, ahol biztonságban pihenhet. Nem! Nem akarok többet hallani errôl. Fogd meg a kezem és kövess fel velem az emeletre. A szobád már vár rád.";
			link.l1 = "Elfogadom az ajánlatát, asszonyom, köszönöm. De inkább nem terhelném magát. Majd én magam megyek fel az emeletre.";
			link.l1.go = "Julianna_50";
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.J2") && pchar.questTemp.GoldenGirl.Vine == "red")
			{
				link.l2 = "Márkiné, ön az ôrangyalom. Attól tartok, most én vagyok az, aki tartozik önnek.";
				link.l2.go = "Julianna_52";
			}
		break;
		
		case "Julianna_50":
			dialog.text = "Charles, te a lovagiasság példaképe vagy! Istenre esküszöm, ha így folytatod, elveszítem a fejem! Rendben, lovagom, elküldöm hozzád Denise-t, ô majd ellátja a sebeidet, ahogyan azt egy rendes orvos tenné.";
			link.l1 = "Köszönöm, márkinô. Ha a szívem nem lenne elfoglalva, szívesen játszanék veled. De sajnos! Jó éjszakát!";
			link.l1.go = "Julianna_51";
		break;
		
		case "Julianna_51":
			DialogExit();
			DoQuestReloadToLocation("FortFrance_Brothel_room", "goto", "goto1", "GoldenGirl_WithoutJulianna"); // найти нужные локаторы
		break;
		
		case "Julianna_52":
			dialog.text = "Ebben az esetben azt követelem, hogy azonnal engedelmeskedj nekem. Fogd meg a kezem és tedd, amit mondok. Denise! Hozd fel a szöszt, forralt bort és valami ennivalót! Menjünk, kapitányom. És ne feledje - ezúttal nincs vita!";
			link.l1 = "Ahogy mondja, márkinô, a magáé vagyok.";
			link.l1.go = "Julianna_53";
		break;
		
		case "Julianna_53":
			DialogExit();
			pchar.questTemp.GoldenGirl.JulianaSex = "true";
			DoQuestReloadToLocation("FortFrance_Brothel_room", "goto", "goto1", "GoldenGirl_KissJulianna");
			sld = characterFromId("Julianna");
			ChangeCharacterAddressGroup(sld, "FortFrance_Brothel_room", "goto", "goto2");
		break;
		
		case "Julianna_54":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.JulianaSex"))
			{
				dialog.text = "Jó reggelt, Charles. Hogy vannak azok a karcolások?";
				link.l1 = "Hála az erôfeszítéseidnek, úgy érzem, újjászülettem. Kérem, fogadja ôszinte hálámat, Julianna.";
				link.l1.go = "Julianna_56";
			}
			else
			{
				dialog.text = "Jó reggelt, hôsöm. Hogy vannak azok a karcolások?";
				link.l1 = "Köszönöm az aggodalmát, asszonyom, teljesen jól vagyok. Egy vagyont fizetnék azért, hogy az ön Denise-ét a hajóorvosomként használhassam. Ô egy csoda!";
				link.l1.go = "Julianna_55";
			}
		break;
		
		case "Julianna_55":
			dialog.text = "Attól tartok, nem lesz könnyû megszervezni. De soha nem merném komoly ok nélkül felébreszteni önt. Higgye el, féltlenül vigyáztam az álmát, de ez az ember odalent nagyon kitartó. Azt mondja, hogy a legénységed tagja, és hogy ez sürgôs.";
			link.l1 = "A legénységem? Jól tette, hogy felébresztett, márkinô! Azonnal indulok.";
			link.l1.go = "Julianna_57";
		break;
		
		case "Julianna_56":
			dialog.text = "Más körülmények között megtenném, kapitányom, de el kell halasztanunk. Egy rendkívül mûveletlen úr várja önt odalent. Azt mondja, hogy a legénységéhez tartozik, és sürgôs a dolog.";
			link.l1 = "Majd visszatérünk rá, asszonyom, ha visszajöttem. Remélem, nem a spanyolok újabb ostromáról van szó.";
			link.l1.go = "Julianna_57";
		break;
		
		case "Julianna_57":
			DialogExit();
			DoQuestReloadToLocation("FortFrance_town", "reload", "reload9_back", "GoldenGirl_BadNews");
		break;
		
		case "Julianna_58":
			dialog.text = "Charles, hát visszajöttél! Milyen híreket hozott az embere? Még csak el sem köszöntél!";
			link.l1 = "Elnézést kérek, márkiné. De Chievous megint mocskosan játszott. Ellopta a hajómat, és ma éjjel elhajózott. Az egyik megbízható tisztem azon a hajón volt, és nem hagyhatom annak a fattyúnak a kezében.";
			link.l1.go = "Julianna_59";
		break;
		
		case "Julianna_59":
			dialog.text = "Ôt? Egy nôi tiszt állomásozik a hajóján? Ez ellenkezik mindennel, amit a tengerészetrôl tudok. Mibôl gondolja, hogy még életben van?";
			link.l1 = "Remélem. Julianna, eddig csak a remény maradt nekem. Többet kell megtudnom Angerran de Chievousról. Mindenképpen ki kell derítenem, hová ment! Vissza kell hoznom ôt!";
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.JulianaSex")) link.l1.go = "Julianna_62";
			else link.l1.go = "Julianna_60";
		break;
		
		case "Julianna_60":
			dialog.text = "Most már értem! Valóban szerelmes vagy, lovagom! Szívesen odaadnám a fél életemet egy ilyen hûségért és ragaszkodásért, egy pillanatig sem gondolkodnék!";
			link.l1 = "Nem tettem fogadalmat, de ez a nô nagyon sokat jelent nekem, márkiné.";
			link.l1.go = "Julianna_61";
		break;
		
		case "Julianna_61":
			dialog.text = "Ez a féltékenység megható. Hallgassa meg, Károly, kész vagyok féltékennyé válni önért! De melyik kurtizán maradhat süket az igaz szerelem hangjára? Különben is, megmentettél, lovagom, természetesen segítek neked. Kérdezd csak.";
			link.l1 = "Köszönöm. Köszönöm. Ön már jó ideje ismeri de Chievous-t. Hová mehetett a nagy felhajtás után, hogy kivárja apja haragját?";
			link.l1.go = "Julianna_64";
		break;
		
		case "Julianna_62":
			dialog.text = "Mi lenne, ha elcsábítanám egy villásreggelivel? Két napig nem gondolt erre a... lányra, talán még egy napot tud várni?";
			link.l1 = "Márki, tisztában vagyok vele, hogy milyen képet vághatok a szemében, de ami történt, megtörtént. Még ha nem is tettem fogadalmat, a szívem az övé. Könyörgöm, értsen meg és segítsen nekem.";
			link.l1.go = "Julianna_63";
		break;
		
		case "Julianna_63":
			dialog.text = "Gyerünk, Charles! Egy kurtizán elôtt szerelmi beszéddel védekezel? Rég nem nevettem már így! Annyira hihetetlen vagy! Nyugi, ami ebben a házban történt, az ebben a házban marad. Emlékszem, mivel tartozom neked. Kérdezd csak.";
			link.l1 = "Köszönöm. Köszönöm. Ön már jó ideje ismeri de Chievous-t. Hová mehetett a nagy felhajtás után, hogy kivárja apja haragját?";
			link.l1.go = "Julianna_64";
		break;
		
		case "Julianna_64":
			dialog.text = "Az igazat megvallva, még ha Angerran de Chievous meghívása nem is a legkellemesebb dolog, politikailag mégis nagyon hasznos. Ô bárhol szívesen látott vendég, beleértve a Franciaországgal szövetséges nemzeteket is. De én csak egy embert ismerek a közelben, aki mindig nyújt neki kezet és menedéket. Francois de Lyon, Guadeloupe gyarmatunk kormányzója. Ô de Levi Vantadur gróf régi munkatársa, és mindig is gyengéje volt ennek a fattyúnak.";
			link.l1 = "Guadeloupe legyen! Ez a legjobb nyom, amiben reménykedni mertem! Ha ma este kihajózunk, csak egy nappal leszünk mögöttük.";
			link.l1.go = "Julianna_65";
		break;
		
		case "Julianna_65":
			dialog.text = "Várj, Charles, van még valami. Nemrég kaptam egy levelet neked. Azt hittem, hogy valami köze van a párbajhoz, de már nem vagyok benne biztos. Itt van.";
			link.l1 = "Nincs rajta pecsét, de a papír drága. Nem tetszik ez nekem...";
			link.l1.go = "Julianna_66";
		break;
		
		case "Julianna_66":
			DialogExit();
			AddQuestRecordInfo("GG_Letter_1", "1");
			chrDisableReloadToLocation = true;
			npchar.dialog.currentnode = "Julianna_67";
			LAi_SetStayType(npchar);
		break;
		
		case "Julianna_67":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "Gyerünk, Charles! Ne hagyj bizonytalanságban, tôle jött?";
			link.l1 = "Igen, tôle. Életben van! Elfogta, miközben ellopta a hajómat. Most azt javasolja, hogy találkozzunk és beszéljük meg ezt civilizált környezetben. Ahogy mondtad, Guadeloupe, Basse-Terre.";
			link.l1.go = "Julianna_68";
		break;
		
		case "Julianna_68":
			dialog.text = "Monseniour de Lyons biztosan Leve Vantadur fiát fogja választani helyetted. De Chievous talán megint csapdát állít neked! Nagyon erôs ellenséget szereztél magadnak azzal, hogy megvédtél engem, Charles. Bárcsak segíthetnék neked, de attól tartok, hogy csak annyit tehetek, hogy megkérlek, légy óvatos.";
			link.l1 = "Julianne, soha nem jutottam volna el az Újvilágban, ha mindig a közvetlen megközelítést választom. A kétes ügyek nem a legerôsebb területem, de tudom, hogyan kell játszani.";
			link.l1.go = "Julianna_69";
		break;
		
		case "Julianna_69":
			DialogExit();
			npchar.dialog.currentnode = "Julianna_70";
			LAi_SetOwnerType(npchar);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			chrDisableReloadToLocation = false;
			GoldenGirl_ToBaster();
		break;
		
		case "Julianna_70":
			dialog.text = "Van valami hír, kapitány?";
			link.l1 = "Sajnos, semmi...";
			link.l1.go = "Julianna_71";
		break;
		
		case "Julianna_71":
			DialogExit();
			npchar.dialog.currentnode = "Julianna_70";
		break;
		
		case "Julianna_72":
			dialog.text = "Isten hozott, Charles! Örülök, hogy élsz és virulsz. Mi újság?";
			link.l1 = "Minden, amit eddig tudtunk de Chievous képességeirôl, kiderült, hogy súlyosan alulértékelt. A szemétláda fogva tartja a... tisztemet, és csak két hetem van a váltságdíj beszedésére. Attól tartok, hogy ez a segítséged nélkül nem fog menni.";
			link.l1.go = "Julianna_73";
		break;
		
		case "Julianna_73":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.JulianaSex"))
			{
				dialog.text = "Charles, a szerelmed eléggé szélvirág, mégis nagyon sokat köszönhetek neked, és segítek neked, ahogy csak tudok. Miben lehetek a szolgálatodra?";
			}
			else
			{
				dialog.text = "Charles, már mondtam, hogy soha nem fogom elfelejteni, amit értem tettél. Mindent megteszek, amit csak tudok, hogy megháláljam. Készen állok, de nem egészen értem, hogyan lehetek ebben a segítségedre?";
			}
			link.l1 = "Kérlek, ülj le, Julianna. Látod, Angerran váltságdíja... te vagy. És nem hivatalos pártfogásra gondolok, hanem úgy értem, mint egy megkötözött fogoly a rakterében.";
			link.l1.go = "Julianna_74";
		break;
		
		case "Julianna_74":
			dialog.text = "Elakadt a szavam... De az arcod azt mutatja, hogy ez nem vicc. Elment az esze?";
			link.l1 = "Inkább azt hiszi, hogy én voltam. Elég kétségbeesett ahhoz, hogy minden lehetséges határt átlépjen.";
			link.l1.go = "Julianna_75";
		break;
		
		case "Julianna_75":
			dialog.text = "És mit kérdezel tôlem? Hogy ne sikítsak az elrablásom alatt? Kapitány, nem gondolja, hogy ez egy kicsit túl nagy kérés? Sokkal tartozom önnek, de megmenteni valaki más szerelmét azzal, hogy a saját életemet egy dicstelen fattyú kezébe adom... Ön itt a lovagiasság, míg én egy rendkívül realista és anyagias nô vagyok.";
			link.l1 = "Attól tartok, asszonyom, pontosan ezt kérem öntôl. Pakolja össze a holmiját, indulunk. Nagyon sajnálom, de az idô szorít.";
			link.l1.go = "Julianna_76";
			link.l2 = "Márki, én nem rabolok el olyan nôket, akik bíznak bennem. És ez lehet a mi esélyünk.";
			link.l2.go = "Julianna_81";
		break;
		
		case "Julianna_76":
			dialog.text = "Tele vagy meglepetésekkel, Charles. Hallottad ezt? Ez volt az összes kegyelem, amit irántad éreztem, csak úgy összetört. Szerelem vagy sem, nem engedem, hogy elrabolj. Ôrség! Segítség! Bárki!!!!";
			link.l1 = "És én még azt hittem, hogy barátok vagyunk.";
			link.l1.go = "Julianna_77";
		break;
		
		case "Julianna_77":
			DialogExit();
			LAi_SetActorType(npchar);
			GoldenGirl_PatrolInBrothel();
		break;
		
		case "Julianna_78":
			dialog.text = "Ez felháborító! Mivé változtattad a társalgómat?! Miféle démoni rémség ez? Charles, térj már észhez! Te egy nemes vagy, nem egy átkozott kalóz!!!";
			link.l1 = "Már bocsánatot kértem tôled. Megkértelek, hogy ne bonyolítsd tovább a dolgokat - nem hallgattál rám. Hidd el, nem tetszik, amit teszek, de nincs más választásom. Bármit megteszek annak a nônek az érdekében.";
			link.l1.go = "Julianna_79";
		break;
		
		case "Julianna_79":
			dialog.text = "Miféle hölgy választana egy ilyen lovagot, mint te? Majd én magam megyek, tartsa távol tôlem a kezét! Nem egy tehenet lopsz, mutass egy kis méltóságot!";
			link.l1 = "Jól van. Jöjjön velem, asszonyom. Maradjon a hátam mögött, és tartsa lehajtott fejjel - lehet, hogy lövöldözni kezdenek.";
			link.l1.go = "Julianna_80";
		break;
		
		case "Julianna_80":
			DialogExit();
			LAi_SetActorType(npchar);
			npchar.greeting = "Marquesa_again";
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 10.0);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			pchar.quest.goldengirl_alarm.win_condition.l1 = "location";
			pchar.quest.goldengirl_alarm.win_condition.l1.location = "FortFrance_Town";
			pchar.quest.goldengirl_alarm.function = "GoldenGirl_AlarmSP";
			pchar.quest.goldengirl_dominica_alarm.win_condition.l1 = "location";
			pchar.quest.goldengirl_dominica_alarm.win_condition.l1.location = "Dominica";
			pchar.quest.goldengirl_dominica_alarm.function = "GoldenGirl_DominicaAlarm";
			ChangeCharacterComplexReputation(pchar, "nobility", -15);
			ChangeCharacterNationReputation(pchar, FRANCE, -50);
			ChangeOfficersLoyality("bad_all", 5);
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sTemp = sld.name;
			AddQuestRecord("GoldenGirl", "14");
			AddQuestUserData("GoldenGirl", "sName", sTemp);
			pchar.questTemp.GoldenGirl = "dominica_alarm"; // флаг - силовое решение
			pchar.questTemp.GoldenGirl.Julianna_Prisoner = "true";
		break;
		
		case "Julianna_81":
			dialog.text = "Egy pillanatra azt hittem, hogy egyáltalán nem ismerlek, Charles. Ez a tekintet... De akkor mit akarsz tenni? Milyen esélyt említettél?";
			link.l1 = "Miért használ engem a szemétláda, hogy elkapjon téged? Miért szervezte meg azt a kártyapartit ahelyett, hogy csak úgy elvitte volna, amit akart? Mitôl fél?";
			link.l1.go = "Julianna_82";
		break;
		
		case "Julianna_82":
			dialog.text = "Semmi esélyt. Sajnos, de az okok mindezek mögött unalmasan primitívek. Henri gróf még mindig gyengéd érzelmeket táplál irántam. Angerran sokat kockáztatna, ha akaratom ellenére bármit is tenne velem. Sajnálom, Charles, de ez zsákutca. Mindent tagadni fog, és megússza a dolgot. Senki sem fog hinni a szavainak, az elrablónak, míg az apja tönkreteszi.";
			link.l1 = "A fenébe is! Bárcsak ne fajult volna idáig... Készüljön, márkinô, mennünk kell. És igen, arra kérlek, hogy maradj csendben.";
			link.l1.go = "Julianna_76";
			link.l2 = "De a fattyúnak az apján kívül más gyengesége is lehet, igaz? Nem tökéletes, épp ellenkezôleg, a tökéletesség ellentéte!";
			link.l2.go = "Julianna_83";
		break;
		
		case "Julianna_83":
			dialog.text = "Nem tudom, hogy ez hasznos lesz-e... nekünk. Angerrannak volt némi dolga a helyi kalózbáróval. Jacques Baraban?";
			link.l1 = "Barbazon, asszonyom. Szép pár, mindketten! De Jacques a Kedves nem szeret engem, és nem indíthatok támadást Le Francois ellen szilárd bizonyosság nélkül.";
			link.l1.go = "Julianna_84";
		break;
		
		case "Julianna_84":
			if (CheckAttribute(pchar, "questTemp.Portugal.GG1"))
			{
				dialog.text = "Már megint túl egyenes vagy, lovagom. Emlékszik Moreno kapitányra? A második szerencsejátékos ellenfeledre? Fogadok, hogy Angerran miatt jött ide. Biztos tud valami értékeset a számunkra.";
				link.l1 = "Moreno kapitány, hah! Igen, persze. Még mindig itt van a városban? Hol találom?";
				link.l1.go = "Julianna_85";
			}
			else
			{
				dialog.text = "Már megint túl egyenes vagy, lovagom. Valaki mindig tud valamit, és nem mindenki tudja befogni a száját bizonyos helyzetekben. Az én... tanítványaim hallanak dolgokat ebben a házban. Adj egy napot, és többet fogok megtudni, vagy keresek neked valakit, aki tud.";
				link.l1 = "Márki, azt hittem, hogy az aggodalom illik hozzád, de a harag még jobban illik hozzád. Köszönöm, hogy reményt ébresztettél bennem!";
				link.l1.go = "Julianna_86";
			}
		break;
		
		case "Julianna_85":
			pchar.questTemp.GoldenGirl.Portugal = "true";
			dialog.text = "Igen, még mindig itt van, és megkíméllek a keresésétôl. Jöjjön ide holnap este - Moreno kapitány itt fogja várni önt, ebben a szobában. Bárcsak többet tehetnék, de nem tehetem, Charles.";
			link.l1 = "Ez már így is több mint elég, márkinô. Vele az oldalamon sokkal könnyebb lesz a dolgom. Köszönöm. Köszönöm. Viszlát holnap este.";
			link.l1.go = "Julianna_87";
		break;
		
		
		case "Julianna_86":
			pchar.questTemp.GoldenGirl.Portugal = "false";
			dialog.text = "Bárcsak más helyzetben hallottam volna ezt tôled, Charles. Gyere el hozzám holnap este. Remélem, megkapod, amire szükséged van.";
			link.l1 = "Még egyszer köszönöm, Julianna! Akkor holnap este.";
			link.l1.go = "Julianna_87";
		break;
		
		case "Julianna_87":
			DialogExit();
			npchar.dialog.currentnode = "Julianna_70";
			LAi_SetOwnerType(npchar);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			SetFunctionTimerCondition("GoldenGirl_JuliannaOneDay", 0, 0, 1, false); // таймер
		break;
		
		case "Julianna_88":
			pchar.quest.GoldenGirl_JuliannaOneDayFail.over = "yes"; //снять прерывание
			if (pchar.questTemp.GoldenGirl.Portugal == "true")
			{
				dialog.text = "Tessék, barátom! Moreno kapitány már várja magát.";
				link.l1 = "...";
				link.l1.go = "Julianna_89";
			}
			else
			{
				dialog.text = "Charles, azt hiszem, találtam valamit. Emlékszel Moreno kapitányra? Aki ellened játszott azon a beteg estén?";
				link.l1 = "Emlékszem, micsoda csavargó. Mi van vele?";
				link.l1.go = "Julianna_102";
			}
		break;
		
		case "Julianna_89":
			DialogExit();
			LAi_SetActorType(npchar);
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_9";
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload3");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			chrDisableReloadToLocation = true;
		break;
		
		case "Julianna_90":
			dialog.text = "Mindig is tudtam, Bartolomeo de la Cueva. Ez az, amiért egyáltalán eljutottál a partimra. Olyan volt, mintha jalapenót tennék a vacsorához. Tudom, hogy te és a fiaid már néhány hete a szigeten szaglásznak. Tudom, hogy ennek valahogyan köze kell, hogy legyen Le Francois és Angerran de Chievous kalózbáróhoz. Meséljen el mindent a barátomnak, és cserébe mi titokban tartjuk a legendás nevét. Ellenkezô esetben hívom az ôröket, akik már az ajtók mögött állnak. Hívtam ôket, amikor megérkeztél.";
			link.l1 = "...";
			link.l1.go = "Julianna_91";
		break;
		
		case "Julianna_91":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_12";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Julianna_92":
			dialog.text = "Nem csak ôket! Angerran egy nyakláncot ajándékozott nekem, egy gyönyörû nyakláncot! Nagy és tiszta gyöngyök, köztük ez, sötét, mint a déli éjszaka, középen. De hát a helyi ékszerészektôl rendelte!";
			link.l1 = "...";
			link.l1.go = "Julianna_93";
		break;
		
		case "Julianna_93":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_18";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Julianna_94":
			dialog.text = "Fogadok, hogy nem csak azért tette, hogy egy luxusajándékkal kedveskedjen nekem. Bár ez az ajándék volt az utolsó mentsvára, hogy az illem határain belül elnyerje a kegyeimet. Angerrannak nincsenek címei és földjei, még a fregattja is csak az övé marad, amíg az apja másként nem dönt. Hatalmával és befolyásával él, de saját bevételi forrása nincs. Talán belefáradt az apai adományokra való várakozásba, és úgy döntött, hogy rendbe hozza az anyagi helyzetét?";
			link.l1 = "Várjon, asszonyom! A kártyajáték! Ha igazunk van, és de Chievous elôre kitervelte az egészet, akkor bizonyára sok pénz kellett neki a tétekre, hogy elég keményen sarokba szoríthassa a kormányzónkat. Ha egy szülôktôl ilyen pénzt kérne, az felhívhatná a nem kívánt figyelmét a dologra. A már ellopott kincsek ellopása a kalózoktól csendes és biztonságos módszernek tûnik a szükséges pénz megszerzésére. Senki sem tudná meg!";
			link.l1.go = "Julianna_95";
		break;
		
		case "Julianna_95":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_21";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Julianna_96":
			dialog.text = "Ránk, Charles! Angerran ezúttal nem úszhatja meg a dolgot. Túl messzire ment a pozíciója felettem, és szeretnék segíteni neked, hogy ezt elintézd.";
			link.l1 = "";
			link.l1.go = "Julianna_97";
		break;
		
		case "Julianna_97":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_23";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Julianna_98":
			dialog.text = "Egy vesztes kalóz és egy majdnem szerelmes kurtizán. Charles, egy álomcsapatot szereztél magadnak!";
			link.l1 = "Mindazonáltal köszönöm mindkettôtöknek. Tisztelettel! Most ezt egy kicsit át kell gondolnom, és tervet kell vezetnem.";
			link.l1.go = "Julianna_99";
		break;
		
		case "Julianna_99":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_25";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Julianna_100":
			dialog.text = "Ebben a házban bármi van, amire a vendégei vágynak. Majd én intézkedem. Csatlakozz hozzánk, ha készen állsz, Charles.";
			link.l1 = "Rendben, asszonyom.";
			link.l1.go = "Julianna_101";
		break;
		
		case "Julianna_101":
			DialogExit(); // фин 3
			AddQuestRecord("GoldenGirl", "22");
			npchar.Dialog.currentnode = "Julianna_119";
			LAi_SetOwnerType(npchar);
		break;
		
		case "Julianna_102":
			dialog.text = "Semmi, de valaki a városban keresi ôt. Aktívan érdeklôdnek ön és a többi vendég után, akik aznap este itt voltak. Még nem tudom, mi folyik itt, de biztos vagyok benne, hogy nagyobb dologba csöppent bele, mint gondolná. ";
			link.l1 = "Valami nagyobbat? Hogy érted ezt, Julianne?";
			link.l1.go = "Julianna_103";
		break;
		
		case "Julianna_103": // запускаем Кортни
			chrDisableReloadToLocation = true;
			DialogExit();
			sld = characterFromId("Cortny");
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_104":
			dialog.text = "Angerran... Úgy értem, Monseniour de Chievous egy csodálatos gyöngynyakláncot adott nekem ajándékba. Az egyik gyöngy fekete volt, mint az éjszaka. Azt hittem, hogy csak egy hamisítvány, egy szép történettel a hátterében. Soha nem viseltem, nem akartam hamis reményeket kelteni, de olyan igézôen szép.";
			link.l1 = "";
			link.l1.go = "Julianna_105";
		break;
		
		case "Julianna_105":
			DialogExit();
			sld = characterFromId("Cortny");
			sld.dialog.currentnode = "Cortny_7";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Julianna_106":
			dialog.text = "Mit fogsz tenni, Charles? Van fogalmad arról, hogy mi folyik itt?";
			link.l1 = "Még nem, de majd fogok. De Chievous nyakig benne van valami komoly dologban, és ez az én esélyem. A hazája nem merne hozzányúlni, de a brit hatóságok talán igen. Inkább nem rabolnám el, Julianne.";
			link.l1.go = "Julianna_107";
		break;
		
		case "Julianna_107":
			dialog.text = "Ez nagyon kedves tôled, Charles, de nem túl vicces.";
			link.l1 = "";
			link.l1.go = "Julianna_108";
		break;
		
		case "Julianna_108":
			DialogExit();
			chrDisableReloadToLocation = false;
			pchar.quest.goldengirl_time_cortny.win_condition.l1 = "Timer";
			pchar.quest.goldengirl_time_cortny.win_condition.l1.date.hour  = 20.00;
			pchar.quest.goldengirl_time_cortny.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.goldengirl_time_cortny.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.goldengirl_time_cortny.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.goldengirl_time_cortny.function = "GoldenGirl_TimeCortny";
			pchar.quest.goldengirl_time_cortny.win_condition.l1 = "Timer";
			pchar.quest.goldengirl_time_cortny_fail.win_condition.l1.date.hour  = 23.00;
			pchar.quest.goldengirl_time_cortny_fail.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.goldengirl_time_cortny_fail.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.goldengirl_time_cortny_fail.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.goldengirl_time_cortny_fail.function = "GoldenGirl_TimeCortnyFail";
			if(bImCasual) NewGameTip("Felfedezô mód: az idôzítô nincs kikapcsolva. Tartsd be a határidôt!");
			AddQuestRecord("GoldenGirl", "17");
		break;
		
		case "Julianna_109":
			dialog.text = "Charles, tanultál valamit? Idegesnek tûnsz... Mi a baj?";
			link.l1 = "A francba! Bárcsak másképp lennének a dolgok... Pakold össze a cuccaidat, mennünk kell, Marquise. Kérlek, ne csinálj semmi bajt.";
			link.l1.go = "Julianna_76";
		break;
		
		case "Julianna_110":
			pchar.quest.goldengirl_time_cortny_fail.over = "yes"; //снять прерывание
			dialog.text = "Charles, gyere be. A báró már itt van, és kellemesen elbeszélgettünk. Épp most meséltem neki az érdeklôdésérôl a folyamatban lévô események iránt.";
			link.l1 = "Julianne, nem vagyok benne biztos, hogy bölcs dolog volt...";
			link.l1.go = "Julianna_111";
		break;
		
		case "Julianna_111":
			DialogExit();
			sld = characterFromId("Cortny");
			sld.dialog.currentnode = "Cortny_14";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_112":
			dialog.text = "Baronet, úgy tûnik, hogy az emberei elejtettek valamit az ajtó mögött! Megmondaná nekik, hogy viselkedjenek jobban?";
			link.l1 = "";
			link.l1.go = "Julianna_113";
		break;
		
		case "Julianna_113":
			DialogExit();
			sld = characterFromId("Cortny");
			sld.dialog.currentnode = "Cortny_17";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_114":
			dialog.text = "Szörnyû! Most mit tegyünk?!";
			link.l1 = "A francba! Bárcsak másképp lennének a dolgok... Pakold össze a cuccaidat, mennünk kell, Marquise. Kérlek, ne csinálj semmi bajt.";
			link.l1.go = "Julianna_76";
		break;
		
		case "Julianna_115":
			dialog.text = "Mindenható Istenem! Mit csináltak a nappalimmal, uraim?! Ez olyan, mint egy középkori rémálom! Kik ezek az emberek? És hol vannak az ôrök?";
			link.l1 = "Jól vagy, Julianne? Jól vagyok, Julianne. Fogadok, hogy az ôrök a jól megérdemelt kenôpénzüket egy kocsmában költik el. Báró úr, gratulálok - sikerült nagyon felbosszantania Goodman Jacket. Az ilyen rendetlen és rosszul elôkészített merényletkísérlet egyáltalán nem az ô stílusa.";
			link.l1.go = "Julianna_116";
		break;
		
		case "Julianna_116":
			DialogExit();
			sld = characterFromId("Cortny");
			sld.dialog.currentnode = "Cortny_21";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_117":
			dialog.text = "Elnézést kérek, hogy megzavarom az izgalmas beszélgetéseteket, de hacsak valamelyikôtök meg nem sérült, akkor menjünk át egy kabinetbe. Egy ilyen látvány nem túl megnyugtató egy hölgy számára... Csak a plafon vérmentes!";
			link.l1 = "Akkor menjen fel az emeletre, márkinô. Tényleg le kéne feküdnie egy kicsit, távol ettôl a sok vértôl. Cortney báró és én majd megbeszéljük a dolgot. Folytathatjuk?";
			link.l1.go = "Julianna_118";
		break;
		
		case "Julianna_118":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3", "Location_reserve_02", "goto", "goto2", "", 20.0);
			sld = characterFromId("Cortny");
			sld.dialog.currentnode = "Cortny_24";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_119":
			dialog.text = "Charles, kész megosztani velünk a tervét?";
			link.l1 = "Majdnem. Mondja, de Chievous pedáns típus? Rendben tartja a könyveit és a naplóit?";
			link.l1.go = "Julianna_120";
		break;
		
		case "Julianna_120":
			dialog.text = "Angerran a pénzügyek terén az idôhúzás megtestesítôje! Több papírt ír alá, mint bármelyik bankár, akit ismerek. Gondolom, már gyerekkora óta ilyen, amikor még azt sem tudta, ki az apja, és szegénységben élt az utcán.";
			link.l1 = "Pompás! Most pedig szükségünk van a naplójára és a könyveire! Megfelelnek majd bizonyítéknak a britek számára. Ki kell találnunk, hogyan szerezzük meg ôket! Bárcsak tudtam volna errôl, amikor a hajója a birtokomban volt... sóhajtok.";
			link.l1.go = "Julianna_121";
		break;
		
		case "Julianna_121":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_27";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_122":
			dialog.text = "Várj, Charles, tényleg azt hiszed, hogy a történtek után megengedem, hogy eladjam magam de Chievousnak, mint valami tanyasi kecske?";
			link.l1 = "Ne aggódj, Julianne, csak néhány napba telik. Ígérem, hogy úgy fognak bánni veled, mint egy felbecsülhetetlen értékû kínai vázával. Javítson ki, ha tévedek, de de Chievous soha nem fog megjelenni a börzén?";
			link.l1.go = "Julianna_123";
		break;
		
		case "Julianna_123":
			dialog.text = "Biztos vagyok benne. Angerran Francois de Lyons szárnyai alatt fog várakozni, és soha nem mer majd találkozni önnel a nyílt tengeren. De ami az én fogságomat illeti...";
			link.l1 = "";
			link.l1.go = "Julianna_124";
		break;
		
		case "Julianna_124":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_29";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_125":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.JulianaSex"))
			{
				dialog.text = "Charles, sajnálom, hogy félbeszakítom, de nem felejtetted el megkérdezni a véleményemet minderrôl? Hetekig azokban a nyikorgó koporsókban... Felfogtad egyáltalán, hogy mit kérsz tôlem?! Nyilvánvalóan ragaszkodsz ahhoz a... lányhoz, de én nem tartozom a legénységedhez! Sajnálom, de ez az egész nem hangzik komoly szerelmi történetnek.";
				link.l1 = "Attól tartok, márkinô, ragaszkodnom kell hozzá. Nem engedhetem meg magamnak, hogy elveszítsem ôt.";
				link.l1.go = "Julianna_127";
				link.l2 = "Mindannyian követünk el hibákat, Julianna. Ezt neked kéne a legjobban tudnod. Arra kérlek, hogy segíts nekem.";
				link.l2.go = "Julianna_126";
			}
			else
			{
				dialog.text = "Charles, elnézést, hogy félbeszakítom, de nem felejtetted el megkérdezni a véleményemet minderrôl? Hetek azokban a nyikorgó koporsókban... Felfogod egyáltalán, hogy mit kérsz tôlem?! Az érzéseid méltóak a klasszikus lovagi irodalomhoz, de én csak egy közönséges kurtizán vagyok. Csodállak és segíteni akarok neked, de mindennek van határa!";
				link.l1 = "";
				link.l1.go = "Julianna_128";
			}
		break;
		
		case "Julianna_126":
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			ChangeCharacterComplexReputation(pchar, "authority", -1);
			if(sti(pchar.reputation.nobility) > 65)
			{
				pchar.questTemp.GoldenGirl.Julianna_Helper = "true";
				dialog.text = "Megértem, Charles. Szeretnék hinni a tökéletes igaz szerelemben, de azt hiszem, ilyen nem létezik ezen a világon.";
				link.l1 = "Köszönöm, márkinô. Ezúttal mindent rendbe fogok hozni. Sokat tanultam ebbôl a történetbôl, és imádkozom, hogy ne fizessek túl szörnyû árat azért, amit tettem.";
				link.l1.go = "Julianna_129";
			}
			else
			{
				dialog.text = "Te döntöttél, én végig támogattalak, de most már elég volt. Mindent feláldozni a szerelemért, amit már a hálószobámban elhagytál. Mindez nagyon megható, Charles, de én már nem vagyok ilyen fiatal és naiv.";
				link.l1 = "Attól tartok, márkinô, ragaszkodnom kell hozzá. Nem engedhetem meg magamnak, hogy elveszítsem ôt.";
				link.l1.go = "Julianna_127";
			}
		break;
		
		case "Julianna_127":
			pchar.questTemp.GoldenGirl.Julianna_Prisoner = "true";
			dialog.text = "Nos, kapitány, tégy, amit akarsz. Nem fogok ellenállni, de legyen tisztában azzal, hogy akaratom ellenére teszem.";
			link.l1 = "Gondolj rólam, amit akarsz, Julianna, kiérdemeltem. De vissza fogom szerezni ôt, nem számít, mi lesz az ára\nJulianna, figyelj, tudom, mit kérek tôled. Hogy mindent hátrahagyj, és hagyd, hogy mások belerángassanak egy megkérdôjelezhetô szerencsejátékba. De ebben a pillanatban te vagy az egyetlen reményem! Szükségem van a segítségedre ebben, és halálomig az adósod leszek!";
			link.l1.go = "Julianna_129";
		break;
		
		case "Julianna_128":
			pchar.questTemp.GoldenGirl.Julianna_Helper = "true";
			dialog.text = "Rendben, kapitány. Végül is, Angerrant végleg el kell pusztítani. Segítek neked, de áruld el, hogyan fogsz megmenteni a hajójáról?";
			link.l1 = "...";
			link.l1.go = "Julianna_129";
		break;
		
		case "Julianna_129":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_31";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_130":
			dialog.text = "Várj. Elveheted a nyakláncgyöngyömet, az angolok fekete gyöngyre vadásznak, igaz? Ez majd ráveszi ôket, hogy meghallgassanak téged. Mi lesz a következô?";
			link.l1 = "Ezután a fedélzetre veszem a nyomozót, és elhajózunk Guadeloupe-ra. Hivatalos keresést fogunk indítani a de Chievous fregatton, amikor az visszatér önnel a fedélzeten. A Merkúr-ügy egy komoly incidens volt, amely a szövetségesünket érintette, így De Lyonnak engedélyeznie kell!";
			link.l1.go = "Julianna_131";
		break;
		
		case "Julianna_131":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_33";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_132":
			if(CheckAttribute(pchar, "questTemp.GoldenGirl.Julianna_Prisoner"))
			{
				dialog.text = "Mindenkinek azt fogja mondani, hogy az ô emberei mentettek meg a fogságból. És vegye tudomásul, kapitány, még nem döntöttem el, hogy mit mondok nekik.";
				link.l1 = "Ha semmit sem mondok, az is jó lesz, márkinô. Higgye el, elhurcolom magát, és Angerrant mindenért megfizettetni.";
			}
			else
			{
				dialog.text = "Elmondom nekik, hogy idegenek raboltak el, egyenesen a házamból, hogy Angerran hajójára tegyenek. Úgy fog tûnni, mintha zsoldosokat fizetett volna az elrablásomért.";
				link.l1 = "Egy újabb szög Angerran koporsójába, márkinô.";
			}
			link.l1.go = "Julianna_133";
		break;
		
		case "Julianna_133":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_35";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_134":
			if(CheckAttribute(pchar, "questTemp.GoldenGirl.Julianna_Prisoner"))
			{
				dialog.text = "Adj idôt reggelig, hacsak nem akarsz zsákban vinni. Küldj néhány embert is, hogy segítsenek nekem - egy szoborszerû nô nem utazhat mindenféle árucikk nélkül. Charles, megmentettél, és én is segítek neked, továbbá kérlek, fogadd el ezt a felbecsülhetetlen értékû fekete gyöngyöt, az én ajándékomat neked. Ha ez sikerül, akkor kvittek vagyunk.";
				link.l1 = "Ahogy mondod, márkinô. Isten éltessen benneteket! Találkozunk itt, ha vége lesz.";
			}
			else
			{
				dialog.text = "Napkeltére készen leszek az indulásra. Nem fogok egy raktárcsarnokban zötykölôdni, úgyhogy gondoskodjatok róla, hogy egy tisztességes szobát, vagy minek nevezzétek, készítsetek elô nekem. Charles, tessék, fogd ezt. Ez értékes fekete gyöngy. Tudom, hogy többe kerül, mint ez a hely, de van, amit nem lehet aranyban mérni. Remélem, hasznodra lesz. Isten segítsen rajtad!";
				link.l1 = "Isten éltessen benneteket! Találkozunk itt, ha vége lesz.";
			}
			link.l1.go = "Julianna_135";
		break;
		
		case "Julianna_135":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 15.0);
			sld = characterFromId("GG_Moreno");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", 10.0);
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sTemp = sld.name;
			AddQuestRecord("GoldenGirl", "23");
			AddQuestUserData("GoldenGirl", "sName", sTemp);
			chrDisableReloadToLocation = false;
			pchar.questTemp.GoldenGirl = "antigua";
			// убрать фрегат Шиво
			pchar.quest.goldengirl_AngerranCap_AfterBattle.over = "yes";
			Group_DeleteGroup("GG_AngerranGroup");
			sld = characterFromId("GG_AngerranCap");
			sld.lifeday = 0;
			GiveItem2Character(pchar, "blackpearl"); // черная жемчужина 
		break;
		
		case "Julianna_136":
			if(CheckAttribute(pchar, "questTemp.GoldenGirl.Julianna_Prisoner"))
			{
				dialog.text = "Gratulálok, kapitány. A terve sikerrel járt. Micsoda hatalmas botrányt rendezett! Az angolok elvitték Angerrant és a hajóját minden tartalmával együtt, kivéve engem.";
				link.l1 = "Sir William még elköszönni sem jött el. Megígérte, hogy bocsánatot kér.";
				link.l1.go = "Julianna_137";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
				else sld = characterFromId("Mary");
				dialog.text = "Charles, megcsináltuk! Bármelyik pillanatban elengedhetnek! El kell hagynunk a szigetet, amilyen gyorsan csak lehet. A kormányzó nagyon feldúlt Angerran nemrég történt letartóztatása miatt.";
				link.l1 = "Örülök, hogy látlak, Julianne. Hogy vagy, Julianne? Hogy ment a csere? Jól van?";
				link.l1.go = "Julianna_140";
			}
		break;
		
		case "Julianna_137":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "Feltételezem, túlságosan elfoglalt volt ehhez. Mint most a kormányzónk. Jobb, ha elhagyod a várost, mielôtt még emlékezne a létezésedre. Valóban szerette Henri fiát, de a brit lapok teljesen sarokba szorították. Én nem várnám meg, amíg úgy dönt, hogy minden frusztrációját önre zúdítja.";
			link.l1 = "Elég tisztességes. Ráadásul Martinique-on vár rám. Hogy ment a csere? Jól van?";
			link.l1.go = "Julianna_138";
		break;
		
		case "Julianna_138":
			dialog.text = "Bocsásson meg, de nem akarok errôl beszélni. Kérdezd inkább ôt. Viszlát, kapitány. Egyedül fogok visszatérni. Ki kell pihennem magam a tengerbôl - Francois elég kedves házigazda, ha nem unalmas brit hivatalnokok zaklatják.";
			link.l1 = "Ôszintén sajnálom mindezt, Madame. Mindenesetre köszönöm az együttmûködését. Örömmel hallom, hogy új... barátra tett szert.";
			link.l1.go = "Julianna_139";
		break;
		
		case "Julianna_139":
			dialog.text = "Köszönöm önnek is, Charles, hogy megtartotta a szavát. Keresse meg Bartholomew-t a házamban St. Pierre-ben. Viszontlátásra. Még találkozunk.";
			link.l1 = "Viszlát, Julianne. Isten éltessen.";
			link.l1.go = "Julianna_143";
		break;
		
		case "Julianna_140":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "Nem láttam ôt, de Bartholomew élve és egészségesen vitte el. Az az angol letartóztatta de Chievous-t és a tulajdonát a helyi kormányzó orra elôtt - egy szót sem szólt! Csodálatos!";
			link.l1 = "Tudja, meglepôen simán ment, tekintve a letartóztatás hátterét. Bár késôbb még vissza kellett volna sülnie. Mindegy! Azonnal Martinique-ra kell mennem, minél elôbb találkoznom kell vele!";
			link.l1.go = "Julianna_141";
		break;
		
		case "Julianna_141":
			dialog.text = "Kétségtelenül sok mondanivalótok van egymásnak. Ó, Charles, bárcsak lenne mellettem egy olyan férfi, akinek ilyen tûz van a szemében. Siessünk, nagyon hiányzik a forró fürdô és a tiszta lepedô. Bartholomew vár minket a házamban St. Pierre-ben.";
			link.l1 = "Igen, a tengeri utazások romantikája túlértékelt. Az én kabinom az öné lesz, márkinô, ez a legkevesebb, amit tehetek. Jöjjön, kérem.";
			link.l1.go = "Julianna_142";
		break;
		
		case "Julianna_142":
			dialog.text = "Már mindent megtettél értem, amit csak lehetett, Charles. Újra hitet adtál egy cinikus nônek.";
			link.l1 = "Én is, Julianne. Én is.";
			link.l1.go = "Julianna_143";
		break;
		
		case "Julianna_143":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "goto", "goto13", "none", "", "", "GoldenGirl_BasterReloadJail", 7.0);
			if(CheckAttribute(pchar, "questTemp.GoldenGirl.Julianna_Prisoner"))
			{
				ChangeCharacterComplexReputation(pchar, "fame", 15);
				ChangeCharacterComplexReputation(pchar, "nobility", -10);
				ChangeCharacterNationReputation(pchar, ENGLAND, 10);
			}
			else
			{
				ChangeCharacterComplexReputation(pchar, "fame", 15);
				ChangeCharacterNationReputation(pchar, ENGLAND, 20);
			}
		break;
		
		case "Julianna_144":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.JulianaSex"))
			{
				dialog.text = "Charles, annyira örülök, hogy eljöttél! Hogy van a hölgyed? Jól van?";
				link.l1 = "Minden rendben, hála neked, Julianne. El akartam mondani neked még egyszer. Csodálatos nô vagy, és örökké az adósod leszek bátorságodért és leleményességedért.";
				link.l1.go = "Julianna_145";
			}
			else
			{
				dialog.text = "Charles, annyira örülök, hogy eljöttél! Hogy van a hölgyed? Jól van?";
				link.l1 = "Minden rendben, hála neked, Julianne. El akartam mondani neked még egyszer. Csodálatos nô vagy, és örökké az adósod leszek bátorságodért és leleményességedért.";
				link.l1.go = "Julianna_148";
			}
		break;
		
		case "Julianna_145":
			dialog.text = "Talán én vagyok az, aki az adósod. Elvégre megmentettél két rendkívül idegesítô pártfogótól. Azt hiszem, még mindig tartozom neked. Kérj bármit, Charles.";
			link.l1 = "Ebben az esetben egy kis szívességet szeretnék kérni, hölgyem. Tehetne valamit, hogy kvittek legyünk.";
			link.l1.go = "Julianna_146";
		break;
		
		case "Julianna_146":
			dialog.text = "Csupa fül vagyok, kapitányom. Mi lenne az?";
			link.l1 = "Az emberek hibáznak, de ettôl még nem lesz rossz a világ. Emlékezz erre, és légy boldog, Julianne. Megérdemled, hogy boldog légy.";
			link.l1.go = "Julianna_147";
		break;
		
		case "Julianna_147":
			dialog.text = "I... Megpróbálom, Charles. Köszönöm, Charles. Meglátogatnál néha... mint barát? Mindig szívesen látlak nálam!";
			link.l1 = "Nagyra értékelem, marquise. Viszontlátásra, és ne feledje, mit ígért nekem.";
			link.l1.go = "Julianna_149";
		break;
		
		case "Julianna_148":
			dialog.text = "Úgy tûnik, mégsem volt elég csodálatos... de örülök, hogy jól végzôdött számodra. Nem tartozol nekem semmivel, azok után, amit tettél, nem tudom eléggé megköszönni! Gyere el hozzám, amikor a parton vagy. Nálam mindig szívesen látlak, mint barátot!";
			link.l1 = "Köszönöm, márkinô. Minden jót kívánok. Viszontlátásra!";
			link.l1.go = "Julianna_149";
		break;
		
		case "Julianna_149":
			DialogExit();
			npchar.dialog.currentnode = "Julianna_150";
		break;
		
		case "Julianna_150":
			dialog.text = "Charles, barátom, milyen udvariatlan vagy - ilyen ritkán látogatsz meg engem! Hiányoztál, tudod? Kérsz egy kis bort? Meghalok, hogy izgalmas történeteket hallgassak elsô kézbôl! És kipróbálni a híres szerencsédet!";
			link.l1 = "Marquise, csak köszönni akartam, és meg akartam gyôzôdni róla, hogy jól vagy.";
			link.l1.go = "Julianna_149";
		break;
		
		case "Julianna_":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "Julianna_";
		break;
		
		// Жак Дьель дю Парке
		case "governor":
			dialog.text = "Hát itt vagy, barátom! Örülök, hogy újra látlak!";
			link.l1 = "...";
			link.l1.go = "governor_1";
		break;
		
		case "governor_1":
			DialogExit();
			sld = characterFromId("Angerran");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.3);
		break;
		
		case "governor_2":
			dialog.text = "Nos, ahogy a barátommal bánik, nem hagy más választást, monsieur. Elfogadom a kihívását. Hely és idô?";
			link.l1 = "Itt és most. Hívja a szolgákat, mondd meg nekik, hogy hozzanak gyertyákat, egy ilyen hangulatos félhomály nem lesz jó. Ennek a helynek világosnak kell lennie, mint a nap!";
			link.l1.go = "governor_3";
		break;
		
		case "governor_3":
			DialogExit();
			LAi_SetStayType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			bDisableCharacterMenu = false;//лоченые интерфейсы
			sld = characterFromId("FortFrance_Mayor");
			sld.dialog.currentnode = "governor_4";
			LAi_SetActorType(sld);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
			sld = characterFromId("Angerran");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload3", "none", "", "", "", 5.0);
		break;
		
		case "governor_4":
			dialog.text = "Barátom, kérem, ne vegye ezt túl személyesnek. Angerran egy undok alak, ez igaz, de nem kellene ôt szidni. Hagyd ezt rám.";
			link.l1 = "Biztos, excellenciás uram? Olyan részeg, mint a szállásmesterem egy hét tengerparton töltött idô után, de a kardjával biztosan tud bánni. Az ilyen dolgokat azonnal meg tudom mondani.";
			link.l1.go = "governor_5";
		break;
		
		case "governor_5":
			dialog.text = "Isten ments, Charles! Nem fogok párbajozni vele. Játszani fogunk, a kártya a civilizált emberek fegyvere. Kiszárítom, és elküldöm hozzád, hogy kölcsönért könyörögjön, hogy biztonságban visszatérhessen Québecbe.";
			link.l1 = "Ez egy jó terv. De ha engem kérdezel, én inkább holtan szeretném látni a fattyút, mint szegényt. Isten éltessen, Excellenciád!";
			link.l1.go = "governor_6";
		break;
		
		case "governor_6":
			DialogExit();
			sld = characterFromId("FortFrance_Mayor");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload3", "none", "", "", "", 5.0);
			sld = characterFromId("Julianna");
			sld.Dialog.currentnode = "Julianna_11";
			sld.greeting = "Marquesa_needhelp";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "governor_7":
			dialog.text = "A fenébe is, Angerran, ott nem lehet tízes! Kizárt dolog!";
			link.l1 = "Ez vádaskodás volt? Az ön üzletében volt, monsieur.";
			link.l1.go = "governor_8";
		break;
		
		case "governor_8":
			dialog.text = "Nem az volt. Én csak... egy kicsit túl izgatott vagyok, és elnézést kérek. Baleset volt, és követelek egy esélyt a visszavágóra! Ezt a hajót... vissza kell szereznem! Vagy csessze meg a játékot, csak mondja meg, mennyiért hajlandó eladni nekem? Nevezze meg az árat, és holnap dél elôtt kifizetem!";
			link.l1 = "Sajnos, de teljes szívembôl hiszem, hogy a szerencsejáték zsákmányát nem lehet visszavásárolni. Csak visszanyerni lehet. A fuvola most már az enyém, és nem áll szándékomban eladni. Sajnálom, hogy a szenvedélyed ilyen helyzetbe hozott, néha reálisabban kellene látnunk a lehetôségeinket... Talán van még több hajópapírod?";
			link.l1.go = "governor_9";
		break;
		
		case "governor_9":
			dialog.text = "Te egy szemétláda vagy, Angerran, és sarokba szorítottál. Azt hiszem, tudok olyan tétet adni, amit elfogadsz.";
			link.l1 = "...";
			link.l1.go = "governor_10";
		break;
		
		case "governor_10":
			DialogExit();
			LAi_SetStayType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			bDisableCharacterMenu = false;//лоченые интерфейсы
			sld = characterFromId("Julianna");
			sld.Dialog.currentnode = "Julianna_23";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "governor_11":
			dialog.text = "Charles, te vagy az egyetlen reményem, könyörgöm, segíts nekem! Azt a fuvolát és a rakományát már eladták a holland társaságnak. Holnap át kell adnom nekik az összes dokumentumot. Úgy gondoltam, hogy itt maradok egész éjszakára, ezért hoztam magammal ôket. Katasztrofális helyzetbe kerülök, ha az üzlet meghiúsul!";
			link.l1 = "De 'cuki Jacques', nem értesz egyet azzal, hogy az általad favorizált nô most még katasztrofálisabb helyzetbe került? Nekem is volt részem szerencsejátékban, és megértek valamit, ha egy hajóért játszol, még akkor is, ha nem a sajátod. De egy nôre fogadni?! Meglepettél, igazán! És most már csak az üzleted sorsa érdekel?";
			link.l1.go = "governor_12";
		break;
		
		case "governor_12":
			dialog.text = "Ne ítélkezz felettem, Charles. Egy befolyásos gróf volt szeretôjének kedvezni, és még csak egy kicsit szerelmesnek is lenni, semmi ahhoz képest, hogy egymillió pezóval tartozol Peter Stuyvesantnak. Hogyan magyarázzam ezt meg az ügynökének? Képzeld el a hírnevét!";
			link.l1 = "Nekem is volt már hasonló adósságom, de nekem egyáltalán nem volt semmim, és mégis jól jártam. És te is így fogsz tenni. Viszlát, Jacques. Nem ígérek semmit, és meg sem kérdezem, hogy milyen szállítmány ér egymilliót, hogy a furulyában tartanád.";
			link.l1.go = "governor_13";
		break;
		
		case "governor_13":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3", "Location_reserve_02", "goto", "goto5", "", 10.0); // уходит
			LocatorReloadEnterDisable("FortFrance_SecBrRoom", "reload3", false); // открыть доступ в малую комнату
		break;
		
		case "governor_14":
			dialog.text = "Tessék, Charles. Épp érted akartam küldeni. De Chievous ragaszkodik a párbajhoz, és máris elutasít minden esélyt a megbékélésre. A kártyákkal jól boldogultál, de biztos vagy benne, hogy ezt akarod folytatni?";
			link.l1 = "Van egy olyan viszketô gyanúm, excellenciád, hogy te akartad ezt a végeredményt egész idô alatt. Ezért azt mondom, hogy igen. Ezt végleg meg kell oldani. Mi a helyzet a párbaj feltételeivel?";
			link.l1.go = "governor_15";
		break;
		
		case "governor_15":
			dialog.text = "Túlságosan a fejedben vagy, barátom. A világunk egyes részei még mindig nem körülötted forognak. Hidd el, mélységesen csalódott vagyok amiatt, ahogy tegnap este minden alakult. Nagyon mélyen. De elôbb beszéljük meg a... nyereményed sorsát.";
			link.l1 = "Igen, persze. Tudni akarod, hogyan adjam vissza a fuvoládat, vagy hogy van Madame Julianne?";
			link.l1.go = "governor_16";
		break;
		
		case "governor_16":
			dialog.text = "Látom, hogy megváltoztattad a nem helyénvaló iróniádat a bosszúállás miatt? Charles, mi egy oldalon állunk, ezt ne felejtsd el.";
			link.l1 = "Vitatható érv, excellenciás uram. Hogy finoman fogalmazzak. Most hol kezdjük: a hajón vagy a hölgyön?";
			link.l1.go = "governor_17";
		break;
		
		case "governor_17":
			dialog.text = "Természetesen a Stuyvesant-ügylet - az ügynöke egész délelôtt várt rám, és én már kifogytam a kifogásokból. Szükségem van a fuvola papírjaira, Charles.";
			link.l1 = "Jó, rendben. A tiéd. Nem hiszem, hogy de Chievous becsületesen játszott, ezért a tulajdonát az ár feléért visszakaphatja. 150 000.";
			link.l1.go = "governor_18";
			link.l2 = "Örömmel teszek eleget a kérésnek. Mit mondott, mennyibe került a hajó? 500 000? Nekem megfelel.";
			link.l2.go = "governor_19";
		break;
		
		case "governor_18":
			AddMoneyToCharacter(pchar, 135000);
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			ChangeCharacterComplexReputation(pchar, "fame", 3);
			dialog.text = "Nos, ez négyszázhatvanezer pezó lesz adókkal együtt. Megegyeztünk. 135 000.";
			link.l1 = "Figyelj... Kezdek belefáradni a vitába. Szóval fizessen, szerezze meg a papírokat és legyen kész.";
			link.l1.go = "governor_20";
		break;
		
		case "governor_19":
			AddMoneyToCharacter(pchar, 300000);
			ChangeCharacterComplexReputation(pchar, "authority", 3);
			AddCharacterExpToSkill(pchar, "Leadership", 400);
			dialog.text = "Nem sajnálod a régi barátokat, igaz Charles? Nos, az adókkal együtt...";
			link.l1 = "A kártyaadósságnak és a barátságnak semmi köze egymáshoz, excellenciás uram. Vagy maga fizeti az adót, mint vevô, vagy én adom el a hajót Le Francois-ban. Ne feledje, nem használom ki a helyzetét... egyelôre.";
			link.l1.go = "governor_20";
		break;
		
		case "governor_20":
			dialog.text = "Rendben, legyen. Most pedig, a párbaj. Nem akarok gondot de Levi Vantadur gróffal, ezért mindennek a lehetô legjobban kell mennie. Hallottad, Charles? A törvény szerint! Két tisztet küldök a helyôrségembôl, hogy elkísérjék - mindketten nemes és köztiszteletben álló emberek. Ôk lesznek a segédeid a rendes... társaid helyett. Azt akarom, hogy minden kristálytiszta legyen, amíg az üzlet el nem készül!";
			link.l1 = "Milyen kedves tôled. És mi van, ha a mi jó barátunk úgy dönt, hogy mocskos játékot ûz? Inkább bízom a hátam olyan emberekre, akiket barátomnak hívok, és akik tudják, mit kell tenni ilyen helyzetekben, mint olyanokra, akik jó családba születtek.";
			link.l1.go = "governor_21";
		break;
		
		case "governor_21":
			dialog.text = "Charles, ne viselkedj úgy, mintha ez a párbaj csak kettônk között lenne. Ez egy komoly dolog. De Chievous nem olyan ember, akit meg lehet ölni és csak úgy megúszni. Bármilyen kimenetelû lesz, nyomozás fogja követni, talán még a bíróság is. Szükségünk lesz megbízható tanúkra. Látod, én gondoskodom rólad! A legfontosabb azonban az, hogy nem ölheted meg\nMegértem, Angerran elszánt, és valószínûleg tisztességes harcos, de, Charles, nem ölheted meg! Megsebesítheted, sôt megalázhatod, de itt állj meg! Ha megölöd - annak következményei lesznek, és egyikünk sem lesz képes kitérni vagy túlélni ôket. Bár de Levi Vantadur gróf soha nem ismerte el hivatalosan a fattyát, nincs más fia. A dühének nem lesz vége.";
			link.l1 = "Csodálatos, tehát inkább hagyjam magam megölni, minthogy a feldühödött gróf kirúgjon a helytartói székbôl?";
			link.l1.go = "governor_22";
		break;
		
		case "governor_22":
			dialog.text = "Attól tartok, ha nem hallgatsz rám, nem sokáig fogjuk túlélni Angerran de Chievous-t. Emlékezz erre, és légy óvatos. A párbaj ma este tíz órára van kitûzve a városkapuk mögött. A tisztjeim ott találkoznak veled. És most az utolsó pont: Madame Julianne Botot - hogy van?";
			link.l1 = "Tudni akarod, hogy kihasználtam-e már a nyereményemet? Nem, excellenciás uram, még nem vagy soha - ez nem számít. Ami számít, az az, hogy örökre eltûnik a márki házából. Kristálytisztán fogalmazott. Nem ítélhetem el érte. Julianne maga fogja kiválasztani a következô pártfogóját.";
			link.l1.go = "governor_23";
		break;
		
		case "governor_23":
			dialog.text = "Te aztán tudod, hogyan kell meglepni, Charles. Mindegy, nekem egy unalmas megbeszélésre kell mennem a Társaság ügynökével. Neked is menned kellene, készülj fel, és emlékszem, mire figyelmeztettelek.";
			link.l1 = "Mindenképpen megpróbálom, excellenciás uram. De ez egy harc, úgyhogy nem ígérhetek semmit. Köszönöm, hogy segítesz nekem.";
			link.l1.go = "governor_24";
		break;
		
		case "governor_24":
			DialogExit();
			GoldenGirl_GovernorOut();
		break;
		
		case "governor_25":
			dialog.text = "Te élsz, Charles! Micsoda megkönnyebbülés, hogy sikerült? Ez vér?! De Chievous túlélte?";
			link.l1 = "Sajnos igen. Megsebesült, de nem súlyosan. Menekülnie kellett, de a verôlegényeit is ránk uszította. Röviden, ennek a vérnek egy része nem az enyém.";
			link.l1.go = "governor_26";
		break;
		
		case "governor_26":
			dialog.text = "Szemétláda! És az embereim? Életben vannak, hogy tanúskodjanak a történtekrôl?";
			if (sti(pchar.questTemp.GoldenGirl.Officer) > 1)
			{
				link.l1 = "Jól vannak, excellenciás uram. Kicsit megverték ôket, de túlélik.";
				link.l1.go = "governor_27_1";
			}
			else
			{
				if (sti(pchar.questTemp.GoldenGirl.Officer) == 1)
				{
					link.l1 = "Nem mindegyikük, excellenciás uram. Egy úrnak nem sikerült - de Chievous vette a fáradságot, hogy muskétásokat hozzon magával. Nem tehettem semmit.";
					link.l1.go = "governor_27_2";
				}
				else 
				{
					link.l1 = "Elszabadult a pokol, excellenciás uram. Mindkét bátor úr elesett a harcban. Ha ôk nem lettek volna, a dolgok csúnyán elfajultak volna számomra. De Chievous rendezett egy kibaszott nagy rajtaütést.";
					link.l1.go = "governor_27_3";
				}
			}
		break;
		
		case "governor_27_1":
			dialog.text = "Pompás! Megszerzem az írásos vallomásaikat megbízható tanúk jelenlétében. De Chievous megfizet ezért!";
			link.l1 = "Nem hiszem, hogy a legkisebb kárt is okozhatnánk a nevének. Inkább megtalálom és magam végzem el a munkát, minden figyelmeztetésed ellenére. Egy ilyen gyáva nem érdemli meg, hogy éljen.";
			link.l1.go = "governor_28";
			ChangeCharacterComplexReputation(pchar, "nobility", 6);
			ChangeCharacterComplexReputation(pchar, "authority", 6);
			ChangeCharacterComplexReputation(pchar, "fame", 6);
		break;
		
		case "governor_27_2":
			dialog.text = "Szörnyû. De legalább egy tanútól kapunk írásos vallomást. De Chievous fizetni fog ezért!";
			link.l1 = "Nem hiszem, hogy a legkisebb kárt is okozhatnánk a nevének. Inkább megtalálom ôt, hogy magam fejezzem be a munkát, minden figyelmeztetésed ellenére. Egy ilyen gyáva nem érdemli meg, hogy éljen.";
			link.l1.go = "governor_28";
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
			ChangeCharacterComplexReputation(pchar, "authority", 3);
			ChangeCharacterComplexReputation(pchar, "fame", 3);
		break;
		
		case "governor_27_3":
			dialog.text = "Átkozott legyen! Jó emberek voltak, Charles! Esküszöm, a rohadék megfizet!";
			link.l1 = "Nem hiszem, hogy a legkisebb kárt is okozhatnánk a nevének. Inkább megtalálom ôt, hogy magam fejezzem be a munkát, minden figyelmeztetésed ellenére. Egy ilyen gyáva nem érdemli meg, hogy éljen.";
			link.l1.go = "governor_28";
		break;
		
		case "governor_28":
			dialog.text = "Felejtsd el, Charles. A szemétláda minden szükséges kárt maga okozott. Lefogadom, hogy most menekül, valami szegény kolónia mocskában bujkál. Nem valószínû, hogy veszélyt jelentene rád. Ez a gazemberség csak egy menekülô kígyó harapása volt. Úgy tûnik, te is megsérültél, orvosra van szükséged?";
			link.l1 = "Köszönöm az aggodalmát, excellenciás uram, de jól vagyok.";
			link.l1.go = "governor_29";
		break;
		
		case "governor_29":
			dialog.text = "Jó tudni. Most már szabadon lélegezhetsz, ennek a történetnek vége. Pihenj és térj vissza a dolgodhoz. Egyébként, ami azt illeti... Nem fejeztük be az elôzô beszélgetésünket a legutóbbi nyereményeirôl. Eldöntötted már, hogy mit fogsz csinálni vele?";
			link.l1 = "Nem egészen értelek, Jacques. Mi az? A márkinôre gondolsz? A francba! Madam Botot! De Chievous menekül, már nem jelent veszélyt rám, de kétségbeesett, és bármire képes! Mennem kell! Küldje az ôröket a márkinô házához! Azonnal!";
			link.l1.go = "governor_30";
		break;
		
		case "governor_30":
			DialogExit();
			GoldenGirl_ToJulianna();
		break;
		
		case "governor_":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "governor_";
		break;
		
		case "Angerran":
			if (pchar.questTemp.Sharlie == "escape")
			{
				dialog.text = "Egy híres kapitányt mondott? Aki visszaverte a spanyol támadást, ami majdnem felperzselte ezt a kis várost? Igen, értem. Mi a méreg?";
			}
			else
			{
				dialog.text = "Egy híres kapitányt mondtál? Még sosem hallottam magáról... Mi a mérge?";
			}
			link.l1 = "...";
			if (pchar.questTemp.GoldenGirl.Vine == "red") link.l1.go = "Angerran_1";
			else link.l1.go = "Angerran_2";
		break;
		
		case "Angerran_1":
			dialog.text = "Pinot Noir, ugyanolyan, mint a mi gyönyörû háziasszonyunk? Biztos vagy benne, hogy tudsz ízlelni ennyi tengeri só után? Normális esetben a maga kaliberû emberek inkább olyan dolgokat isznak, amik feloldanak egy öreg csizmát.";
			link.l1 = "Ha ez egy javaslat volt, hogy együtt sétáljunk át a kapun, akkor benne vagyok. Én sem kedvelem magát, és örülök, hogy az érzés kölcsönös. Hagyjuk a dumát, úgysem vagy jó benne. A feltételek és a fegyverek kiválasztását rád bízom.";
			link.l1.go = "Angerran_3";
		break;
		
		case "Angerran_2":
			dialog.text = "Egy csokor mocsok és macskahúgy? Elbûvölô! Ezt a savanyú szart nem is érlelik hordóban, mert úgysem lesz belôle bor, soha. Mondd csak, a tengeri só ilyen keményre kalapálja az ízt?";
			link.l1 = "Ha ez egy javaslat volt, hogy együtt sétáljunk át a kapun, akkor benne vagyok. Én sem kedvelem magát, és örülök, hogy az érzés kölcsönös. Hagyjuk a dumát, úgysem vagy jó benne. A feltételek és a fegyverek kiválasztását rád bízom.";
			link.l1.go = "Angerran_3";
		break;
		
		case "Angerran_3":
			dialog.text = "Ha, milyen bátor fiú! Most pedig nyugodj meg és tartsd a távolságot. Nem egy kocsmában vagyunk, és nem vagyok az ivócimborád. Maga jóval az osztályom alatt van, nem is kellene beszélgetnünk, de a hölgy kérte. Nos, Jacques-nak és nekem van egy befejezetlen ügyünk...";
			link.l1 = "";
			link.l1.go = "Angerran_4";
		break;
		
		case "Angerran_4": // перекидываем pchar на Ангеррана и говорим с губером
			DialogExit();
			LAi_SetActorType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Angerran"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			sld = characterFromId("FortFrance_Mayor");
			sld.dialog.currentnode = "governor_2";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
			bDisableCharacterMenu = true;//лоченые интерфейсы
		break;
		
		case "Angerran_5":
			dialog.text = "Julianne, jól vagy? Vizet, ti idióták! Hozzatok vizet!";
			link.l1 = "...";
			link.l1.go = "Angerran_6";
		break;
		
		case "Angerran_6":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.Dialog.currentnode = "Julianna_28";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Angerran_7":
			dialog.text = "Igazad van, itt nagyon meleg van. Eddig nagyon szórakoztató volt a meccs, de a finálé elôtt tartsunk egy kis szünetet. Viszlát, viszlát Jacques - emlékszel a tornánk feltételeire?\nÉs itt van Charles de Maure, igaz? Egy kapitány, akinek rossz ízlése van a borhoz, emlékszem rád. Ne aggódj, miután itt végeztem, csak vizet fogsz inni. Szóval ne siessen, élvezze a pillanatot, igyon valamit. Ha készen áll, jöjjön velem ebbe a kis szobába. Kényelmesebb környezetben fejezzük be az éjszakát...";
			link.l1 = "Alig várom, 'monsieur'.";
			link.l1.go = "Angerran_8";
		break;
		
		case "Angerran_8":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3", "Location_reserve_02", "goto", "goto6", "GoldenGirl_AngerranCards", 10.0); // уходит
			sld = characterFromId("FortFrance_Mayor");
			sld.dialog.currentnode = "governor_11";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Angerran_9":
			dialog.text = "Hát itt vagy, végre. Készen áll, hogy megváljon a pénzétôl?";
			link.l1 = "Inkább a magáét adnám hozzá. Kérem, kérem!";
			link.l1.go = "Angerran_10";
		break;
		
		case "Angerran_10":
			dialog.text = "Jól mondta, sajnos a mi kedves kormányzónk ragaszkodott a szabályok megváltoztatásához közvetlenül a szégyenletes veresége elôtt. Most kénytelenek vagyunk még valamit hozzátenni a pénzhez, ami a tét. A téteket mindkét félnek egyenlônek kell elismernie. Az én tétem az ezüst fuvola.";
			link.l1 = "Ugyan már, ez unalmas - pár hét portyázás alatt ötöt is megszerezhetek aranyból. Adjatok valami nagyobbat.";
			link.l1.go = "Angerran_11";
		break;
		
		case "Angerran_11":
			if (sti(RealShips[sti(pchar.ship.type)].Class) < 2)
			{
				dialog.text = "Igen, láttam a hajódat, és be kell vallanom, hogy valóban szép látvány. Akkor emeljük fel - két hajó egy ellen. A fregattom és a fuvolám ezüsttel a te hajód ellen?";
				link.l1 = "Méltó játék! Madam Botot tévedett - ez a párbaj legendákba fog kerülni. Megegyeztünk!";
			}
			else
			{
				if (sti(RealShips[sti(pchar.ship.type)].Class) <= 3)
				{
					dialog.text = "Nézd csak, a kapitányunk egy rossz fiú! A kalózkodás azonban szent dolog. Mit szólnátok egy hadihajóhoz? Egy fregatt, 48 ágyúval. Gyorsabb, mint sok korvett - a királyi hajógyárak terméke, amelyet a világ legjobb hajóépítôi még továbbfejlesztettek. Az általa szállított culverineknek kiváló a hatótávolsága és a pontossága. Mit szólsz hozzá?";
					link.l1 = "Sokkal jobb, benne vagyok! Gyerünk!";
				}
				else
				{
					dialog.text = "Hallottam, hogy itt horgonyzott le, kapitány. Legyen hálás, hogy beleegyeztem, hogy elfogadom a régi kádját karónak. Jöjjön, hacsak nem utasítja vissza.";
					link.l1 = "Rendben, igaza van. Gyerünk, menjünk.";
				}
			}
			link.l1.go = "Angerran_12";
		break;
		
		case "Angerran_12":
			DialogExit();
			npchar.money = 200000;
			pchar.questTemp.GoldenGirl.Game.G3 = "true"; // атрибут квестовой игры
			// вызов интерфейса игры
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
            pchar.GenQuest.Cards.iRate     = 10000; // ставка
            pchar.GenQuest.Cards.SitType   = false;
			LaunchCardsGame();
		break;
		
		case "Angerran_13":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Win"))
			{
				if (sti(RealShips[sti(pchar.ship.type)].Class) < 2)
				{
					dialog.text = "Vége a játéknak, kapitány, megkapta, amit akart. Kárörvendjen, ha akar. Javaslom, hogy holnap délben beszéljük meg a fregattom kivásárlásának feltételeit.";
					link.l1 = "Ennyi? Ôszintén hiszem, ahogy maga is, hogy amit egy szerencsejátékban elvesztettünk, azt nem lehet visszavásárolni, csak visszanyerni. Vagy eladhatom fûrészáruért a helyi halászoknak, és mesélhetek nekik a nagylelkû adományáról.";
					link.l1.go = "Angerran_15";
				}
				else
				{
					if (sti(RealShips[sti(pchar.ship.type)].Class) <= 3)
					{
						dialog.text = "Így szólt a Fortuna. Ez igen furcsán alakult. Gratulálok. De Maure kapitány. Javaslom, hogy holnap délben beszéljük meg a fregattom kivásárlásának feltételeit.";
						link.l1 = "Ilyen hamar? Csalódást okozunk a többi vendégnek, monsieur. Ha jól emlékszem, még mindig van egy hajójuk. Ôszintén hiszem, ahogy ön is, hogy amit egy szerencsejátékban elveszítünk, azt nem lehet visszavásárolni, csak visszanyerni.";
						link.l1.go = "Angerran_16";
					}
					else
					{
						dialog.text = "A Fortuna tehát elmondta a véleményét. Ez nagyon furcsán alakult. Gratulálok. De Maure kapitány. Megérdemelt egy tisztességes italt, próbálja ki a Sangiovese-t. Feltételezem, Jacques jól meg fogja fizetni önnek ezt a kádat, úgy tûnik, érzéseket táplál iránta, sokkal nagyobbakat, mint más bizonyos dolgok iránt. Elég lesz egy tisztességes borra.";
						link.l1 = "Máris feladod? Csalódást okozunk a többi vendégnek, monsieur. Ha jól emlékszem, van még egy hajójuk. Az ön fregattját hívom ezüsttel szemben a fuvolámmal, mivel a saját hajómat túl szerénynek tartotta.";
						link.l1.go = "Angerran_17";
					}
				}
			}
			else
			{
				dialog.text = "Balszerencse, kapitány. Mindazonáltal nagyra értékelem a bátorságát, ráadásul ma jó kedvem van. Elveszem az aranyadat, de a hajódat megtarthatod. Tûnj a szemem elôl, és kérlek, a jövôben kerüld a szerencsejátékot. Egy nap még megöli magát.";
				link.l1 = "Nagyon nemes önöktôl, erre nem számítottam. Viszontlátásra, Monsieur de Chievous.";
				link.l1.go = "Angerran_14";
			}
		break;
		
		case "Angerran_14":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Cards");
			GoldenGirl_CardsFail();
		break;
		
		case "Angerran_15":
			dialog.text = "Jelentôs különbség van a kárörvendés és a legyôzött ellenfél kigúnyolása között, monsieur de Maure.";
			link.l1 = "Máris legyôzöttnek tekinti magát? De minden olyan jól kezdôdött... ah! Madam Botot, higgye el, hogy a szalonja most kapott egy újabb gazdag történetet a mondás és a tett közötti különbségekrôl!";
			link.l1.go = "Angerran_15_1";
		break;
		
		case "Angerran_15_1":
			dialog.text = "Mit akar még? Nekem nincs több hajó az övem mögött, mint ahogyan annyi pénzem sincs, hogy akár csak egy hajóra is elég legyen. A dubloonokra való szerencsejáték nem komoly, azok után, amit ma este is láttunk.";
			link.l1 = "Ön kevésbé leleményes, mint a mi édes Jacques Dille do Parkuet-ünk? Megajándékozom a legszebb lehetôséggel, hogy bebizonyítsa, nem minden szerelem eladó. A szerencse sem adja el a kegyeit. Az ezüsthajó és a fregattod kontra az, amit az aranynál is többre becsülsz.";
			link.l1.go = "Angerran_15_2";
		break;
		
		case "Angerran_15_2":
			dialog.text = "Kapitány, ez még csak nem is vicces. Essünk túl rajta - hamarosan hajnalodik. Holnap megbeszéljük a fregattom kivásárlását.";
			link.l1 = "Rendben, megvan - három hajó! Beleértve egy igazi hadihajót az Újvilág legdrágább... nos, legdrágább hölgyével szemben. Vissza tudsz utasítani egy ilyen tétet?";
			link.l1.go = "Angerran_15_3";
		break;
		
		case "Angerran_15_3":
			dialog.text = "Ez ôrültség lenne. Bár, ez ôrültség, Monsieur de Maure. Kérem, kérem. De ne feledje, az ön ötlete volt.";
			link.l1 = "Ez lesz az a legenda, amit egy évig zárt ajtók mögött fognak ízlelgetni! Hé, még több bort és gyertyát! A játéknak folytatódnia kell!";
			link.l1.go = "Angerran_18";
		break;
		
		case "Angerran_16":
			dialog.text = "Nemrég még úgy gondoltad, hogy ez a fuvola méltatlan tét a hajóink ellen. Mi változott?";
			link.l1 = "Meguntam. Fûszerezzük meg a párbajunkat - a te fregattod és az én hajóm ellen...";
			link.l1.go = "Angerran_16_1";
		break;
		
		case "Angerran_16_1":
			dialog.text = "A fuvola, amit olyan rosszul értékeltél? Véletlenül nem lázas? Nem nézel ki túl jól.";
			link.l1 = "Tökéletesen jól vagyok, köszönöm. Nem hallgatott rám. A kettô az egyhez tét nem egészen látványos, ez így van, úgyhogy egyenlítsük ki az esélyeket! Nem minden értéket lehet aranyban mérni, nem gondolja? Vagy talán csak nem szeretnél inkább a széllel harcolni, ha valami nem a terved szerint alakul, ezért változtatsz irányt? Akkor kár, úgy tûnik, tévedtem veled kapcsolatban. Madam Botot, azt hiszem, a szalonja most kapott egy újabb gazdag történetet a mondás és a tett közötti különbségekrôl...";
			link.l1.go = "Angerran_16_2";
		break;
		
		case "Angerran_16_2":
			dialog.text = "Ne próbáljon a bôröm alá férkôzni, monsieur de Maure, ahhoz ön túl naiv.";
			link.l1 = "Igenis, uram. Az akarat hiánya nem bûn... kivéve persze, ha az ember katona. Vagy nemesember, a családi becsület, mint talán tudja, olykor nagy teher. Bár nem valószínû, hogy egyáltalán ismeri az ilyen dilemmákat.";
			link.l1.go = "Angerran_16_3";
		break;
		
		case "Angerran_16_3":
			dialog.text = "Párbajt akarsz kezdeni, vagy egy játékot akarsz folytatni?";
			link.l1 = "Mindkettô megfelelne. Addig is hitelt adok a márki borkollekciójának, amíg összeszedi magát.";
			link.l1.go = "Angerran_16_4";
		break;
		
		case "Angerran_16_4":
			dialog.text = "Hát legyen. Ennek az éjszakának rendesen véget kell vetni. Két nagy hajó az ezüsttel teli öreg kád ellen, és Új-Franciaország legjobb asszonya! Lélegezzen mélyebben, monsieur de Maure, ez a máglya legenda lesz az elôkelô társaság pletykái között.";
			link.l1 = "Az ön veresége valóban legenda lesz, monsieur de Chievous. Hozzon még bort és gyertyákat! Gyerünk, csináljuk!";
			link.l1.go = "Angerran_18";
		break;
		
		case "Angerran_17":
			dialog.text = "Elvesztette a fejét a szerencse miatt, Monsieur de Maure. Kockáztat itt, a szívesség hiánya rövid.";
			link.l1 = "A rövid kegy az út az igaz szerelemhez. Ami a megvásárolt hûségrôl is elmondható. Az csak megvetéshez vagy unalomhoz vezet.";
			link.l1.go = "Angerran_17_1";
		break;
		
		case "Angerran_17_1":
			dialog.text = "A próbálkozásai, hogy a bôröm alá férkôzzön, szórakoztatnak engem. Jobb lenne, ha megkérdezné Juliana asszonykát olyan dolgokról, mint a szívesség, a szerelem és minden más, amit meg lehet venni vagy nem. De siess - holnap elhagyja a várost.";
			link.l1 = "Legalábbis az ön ismeretei a témában egyoldalúak. Szerencse úrnô kegyét sem nyeréssel, sem fizetéssel itt nem nyerheted el, így a szerelmét sem ismerheted meg. Bátorság kell hozzá, monsieur, és rendíthetetlen akarat a kockázatvállaláshoz. Arról nem is beszélve, hogy a... földi hölgyek is értékelik ezeket a dolgokat. Két hajómat hívom az önöké ellen, benne vannak?";
			link.l1.go = "Angerran_17_2";
		break;
		
		case "Angerran_17_2":
			dialog.text = "Szeretné ezt lelkesen folytatni? Rendben, mindegy. De legalább egy kis drámát tegyünk bele, monsieur de Maure. Mondott valamit a szerelemrôl és az árakról? Ezúton javaslom, hogy kiegyenlítsük a téteket - az ön kádja és az ezüst fuvola az én fregattom és Új-Franciaország legjobb asszonya ellen. Most mit mond?";
			link.l1 = "Azt mondom, hogy ön határozottan tudja, hogyan kell stílusosan játszani, monsieur! Több bort és gyertyát! Gyerünk, menjünk!";
			link.l1.go = "Angerran_18";
		break;
		
		case "Angerran_18":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.GoldenGirl.Game"); // fix 22-03-20
			npchar.money = 70000; // на 2 кона
			pchar.questTemp.GoldenGirl.Game.G4 = "true"; // атрибут квестовой игры
			// вызов интерфейса игры
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
            pchar.GenQuest.Cards.iRate     = 10000; // ставка
            pchar.GenQuest.Cards.SitType   = false;
			LaunchCardsGame();
		break;
		
		case "Angerran_19":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Win"))
			{
				dialog.text = "Hihetetlen, monsieur de Maure, ez egyszerûen hihetetlen!";
				link.l1 = "Bizony ám, Európa a rokroi csata óta nem ismert ilyen vereséget, monsieur de Chievous. Egy mûvész, aki valahol bennem él, reszket a vágytól, hogy egy ilyen történelmi pillanatot leképezzen. Kár, hogy már nem rajzolok úgy, mint fiatalkoromban. De talán Julianne asszony körül kell lennie egy tehetséges mûvésznek, igazam van?";
				link.l1.go = "Angerran_20";
			}
			else
			{
				dialog.text = "Balszerencse, kapitány. Mindazonáltal nagyra értékelem a bátorságát, ráadásul ma jó kedvem van. Elveszem az aranyadat, de a hajódat megtarthatod. Tûnj a szemem elôl, és kérlek, a jövôben kerüld a szerencsejátékot. Egy nap még megöli magát.";
				link.l1 = "Nagyon nemes önöktôl, erre nem számítottam. Viszontlátásra, Monsieur de Chievous.";
				link.l1.go = "Angerran_14";
			}
		break;
		
		case "Angerran_20":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_30";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Angerran_21":
			dialog.text = "Nem, nem érti. Ez annyira hihetetlen, hogy ez egyszerûen nem lehet!";
			link.l1 = "Mindannyian láttuk a kártyákat, monsieur de Chievous - Fortuna sosem hazudik.";
			link.l1.go = "Angerran_22";
		break;
		
		case "Angerran_22":
			dialog.text = "A szerencse nem, de ön, Monsieur de Maure, igen! Nekem úgy tûnik, hogy az ön arcátlansága mögött nem csupán szenvedély állt, hanem terv is. Ön hazug és csaló - ezt kész vagyok minden vendég elôtt megerôsíteni.";
			link.l1 = "...";
			link.l1.go = "Angerran_23";
		break;
		
		case "Angerran_23":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_32";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Angerran_24":
			dialog.text = "";
			link.l1 = "Monsieur de Chievous, jól hallottam? Készen áll arra, hogy ne csak szavakkal erôsítse meg a gyanúját? Úgy tûnik, hogy a sértegetései túl messzire mennek, és én, önnel ellentétben, becsülöm a családom becsületét.";
			link.l1.go = "Angerran_25";
		break;
		
		case "Angerran_25":
			dialog.text = "Második fiam, egy csaló és egy szélhámos nem fog velem a családi becsületrôl beszélni! Fogd be, Julianne, majd késôbb beszélek veled! Charles de Maure, ragaszkodom hozzá, hogy azonnal elégtételt adj! Kard vagy pisztoly?";
			link.l1 = "Mindkettô. Ôszintén szólva, örülök, hogy meggondoltad magad. Emlékszik, azt javasoltam, hogy sétáljunk egyet a kapu elôtt? Mit mondtál a méltatlan osztályomról? Talán a kártyajáték mégiscsak bátorságot adott neked?";
			link.l1.go = "Angerran_26";
		break;
		
		case "Angerran_26":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_34";
			sld.greeting = "Marquesa_vecherkonchen";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Angerran_27":
			dialog.text = "Túl nagy becsület, de egyetértek a márkinôvel. Úgy végzek veled, mint egy nemesemberrel, de Maure, még ha nem is érdemled meg. Holnap délben párbajra hívom ki önt, a kormányzó ôexcellenciáján keresztül. Jöjjön el hozzá egyedül, vagy küldje el a segédeit, hogy megbeszéljük a feltételeket. Viszlát. Asszonyom, tisztelettel.";
			link.l1 = "...";
			link.l1.go = "Angerran_28";
		break;
		
		case "Angerran_28":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 10.0); // уходит
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_36";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Angerran_29":
			dialog.text = "Hát itt vagy, a szerencse kedvence. Remélem, gondoskodtál a dolgaidról? Nem felejtetted el bevallani? Azt mondják, hogy a pokol elég kellemetlen lehet nélküle.";
			link.l1 = "A beszéd olcsó, monsieur. Nem tudsz rendesen kártyázni, most tegyük próbára a vívótudásodat... Táncoljunk!";
			link.l1.go = "Angerran_30";
		break;
		
		case "Angerran_30":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation("FortFrance_ExitTown")], false);
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("GG_SecundantGG_"+i);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PEACE);
			}
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("GG_SecundantAG_"+i);
				LAi_SetActorType(sld);
				LAi_ActorRunToLocator(sld, "goto", "goto1"+(7+i), "", -1);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PEACE);
			}
			LAi_group_Delete("EnemyFight");
			LAi_SetCheckMinHP(npchar, 10, true, "GoldenGirl_Duel"); 
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Angerran_31":
			dialog.text = "Szép... egy, a fenébe is. De én még élek!";
			link.l1 = "A sebe nem néz ki jól, de azért mutassa meg magát egy orvosnak. Nyilvánvaló, hogy így nem mehet tovább, ha így folytatja, akkor meg fog halni. Úgy tûnik, itt végeztünk. Én nyertem, és nem csaltam. Visszaadom neked a hajódat, te pedig elhagyod St. Pierre-t. Soha többé nem látjuk egymást.";
			link.l1.go = "Angerran_32";
		break;
		
		case "Angerran_32":
			dialog.text = "Micsoda hatalmas lovagiasság! Nézze, monsieur de Maure, lehet, hogy ön született kardforgató, de a kártyában egészen biztosan csalt. Háromszor is megbabráltam a paklit. Háromszor a fenébe! A világon semmi csoda nem menthette volna meg, de maga mégis nyert! Bárcsak tudnám, hogy csináltad... Mindegy, hamarosan mindent elmondasz az ördögnek. Adjatok nekik, fiúk!";
			link.l1 = "Te szemétláda! Megkegyelmeztem neked, és te így hálálod meg?! Fegyverbe, uraim!";
			link.l1.go = "Angerran_33";
		break;
		
		case "Angerran_33":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload3", "none", "", "", "", 20.0);
			LAi_RemoveCheckMinHP(npchar); 
            LAi_SetCurHPMax(npchar);
			GoldenGirl_DuelNext();
		break;
		
		case "Angerran_34":
			dialog.text = "Bevallom, Monseniour de Maure, egy kicsit meglepett, hogy itt látom. Ez azt jelenti, hogy nem tévedtem veled kapcsolatban, és a vadlány jelent neked valamit?";
			link.l1 = "Vajon mi a véleménye jó barátjának, de Lyonsnak arról, hogy tiszteket rabol el a haditengerészetünk köztiszteletben álló kapitányaitól? Talán megkérhetnénk, hogy csatlakozzon hozzánk, és elmondhatnánk neki az egész történetet?";
			link.l1.go = "Angerran_35";
		break;
		
		case "Angerran_35":
			dialog.text = "Ez egy kicsit sem fog segíteni, higgye el nekem. Én is jobban bántam a szajháddal, mint egy fogságba esett tábornokkal. Egyelôre. De minden megváltozhat, és ez csak rajtad múlik, Charles.";
			link.l1 = "Nem emlékszem, hogy volt egy szeretô' fotózásunk veled. Ne Charles engem, Monseniour de Chievous. Térjen a lényegre, és mondja meg, mit akar tôlem?";
			link.l1.go = "Angerran_36";
		break;
		
		case "Angerran_36":
			dialog.text = "Tôled? Semmit, Isten ments! Te és én épp most rendeztünk le egy szerencsétlen veszekedést egy botrányos kártyaparti után, ittunk néhány pohárral, és jó öreg' barátokként hagytuk el ezt a szobát.";
			link.l1 = "Angerran, jól nézel ki a nemrég szerzett sérülésed ellenére, és ennek az értéktelen csevegésnek minden perce arra késztet, hogy ezt helyrehozzam. Még a gondolat is egyre jobban vonz, hogy tönkretegyem Francois de Lyons finom szônyegeit.";
			link.l1.go = "Angerran_37";
		break;
		
		case "Angerran_37":
			dialog.text = "De a jó öreg Francois szereti ezeket a szônyegeket, Charles. Mindenki szeret valamit. Ha már itt vagy, biztosan szereted a kis barátnôdet is. Kész vagyok visszaadni ôt neked a tulajdonomért cserébe. Elrontottad a játékot, és bár általában nem szoktam megbocsátani az ilyen vétkeket, neked kivételt tehetek. Megadod nekem a díjat, amire annyira vágyom, és én is megadom neked. Aztán szépen elválnak útjaink. Ennyit a szerelemrôl.";
			link.l1 = "Azt hiszed, hogy úgy hordom a márkit, mint egy kibaszott ékszert a táskámban? Ez badarság! Hogy adhatnám ôt neked?!";
			link.l1.go = "Angerran_38";
		break;
		
		case "Angerran_38":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "Egyáltalán nem érdekel, Charles. Két heted van, hogy megbirkózz vele. És igen, azt akarom, hogy ezt a díjat titokban kapja meg. Mondjuk, valami kapitány, aki megnyert egy nevetségesen drága kurtizánt, de ennek ellenére nem sikerült elnyernie a kegyeit, csinálhatna valami ostobaságot, nem igaz? Gondolod, hogy már eléggé elkeseredett vagy, Charles?";
			link.l1 = "Elôbb látni akarom a tisztemet, hogy megbizonyosodjak róla, hogy még él-e.";
			link.l1.go = "Angerran_39";
		break;
		
		case "Angerran_39":
			dialog.text = "Szó sem lehet róla. Bíznia kell a szavamban. Biztonságos helyen van, és ott is marad, amíg meg nem kapom a zsákmányt. De ha továbbra is ragaszkodik ahhoz, hogy elôbb lássa, szívesen elnézem önnek, és elküldöm önnek egy részét. Melyik a kedvence? Egy fül, egy orr, vagy néhány ujj?";
			link.l1 = "Ha kezet emelsz rá, te szemétláda, puszta kézzel fojtalak meg, Istenre esküszöm! Ne tegyél próbára, baszd meg!";
			link.l1.go = "Angerran_40";
		break;
		
		case "Angerran_40":
			dialog.text = "Nyugodj meg. Minden, ami most történni fog, teljesen a te hibád. Nem szeretem az erôszakot, csak akkor használom, ha muszáj. Ne kényszeríts. Csak add át nekem a zsákmányt a Scott-foknál, Dominicán, kevesebb mint két hét múlva, és megkapod, ami a tiéd. Nem érdekel, hogyan fogod csinálni. Ha lopni akarsz - lopj, elvégre kalóz vagy, csak jól öltözött.";
			link.l1 = "Átkozottul képzelôdsz, nagy különbség van egy kalóz és egy rohadt rabszolgakereskedô között...";
			link.l1.go = "Angerran_41";
		break;
		
		case "Angerran_41":
			dialog.text = "Lélegezzen mélyebben, mindjárt divatosan felvonulunk az öreg Francois elôtt. Most már barátok vagyunk, emlékszel? Mosolyogj, Charles, gyerünk! Váljanak el útjaink. Cape Scott Head, Dominika, két hét múlva. Ne késs el!";
			link.l1 = "Ott találkozunk.";
			link.l1.go = "Angerran_42";
		break;
		
		case "Angerran_42":
			DialogExit();
			DoQuestReloadToLocation("Baster_townhall", "goto", "goto1", "GoldenGirl_AfterBaster");
		break;
		
		case "Cortny":
			PlaySound("VOICE\English\LE\Cortny\Cortny_01.wav");
			dialog.text = "Jó estét, Botot asszony, de Maure kapitány. Kérem, hogy maradjanak nyugodtak.";
			link.l1 = "Marquise, mögöttem, most! Monseniour, mi ez az egész?!";
			link.l1.go = "Cortny_1";
		break;
		
		case "Cortny_1":
			PlaySound("VOICE\English\LE\Cortny\Cortny_02.wav");
			dialog.text = "Egy tucatnyi emberem van az ajtó mögött, és az állam által engedélyezett vészhelyzetben. Az ôrök nem fognak segíteni. Ezért kérem, tegye el a kardját, uram. Csak beszélni szeretnék. Egyelôre.";
			link.l1 = "Monseniour, ki maga és hogy került ide?! Magyarázatot kellene adnia!";
			link.l1.go = "Cortny_2";
		break;
		
		case "Cortny_2":
			dialog.text = "Engedje meg, hogy bemutatkozzam - Sir William Cortney, Cortney báró. Most pedig nyugodjunk meg és beszélgessünk.";
			link.l1 = "Rendben, Cortney úr, mindannyian halljuk.";
			link.l1.go = "Cortny_3";
		break;
		
		case "Cortny_3":
			dialog.text = "Kérem, bocsássák meg, hogy hallgatózom, de a jelenlegi körülmények nem hagynak más választást. Bár itt St. Pierre-ben névtelen maradok, az angol korona megbízásából egy rendkívül fontos nyomozást folytatok. Egy tengerbe veszett kurír hajóval kapcsolatban. Hallott már a Regina nevû brigantiról? ";
			link.l1 = "Én nem, és nem követem a maga kétes tippjeit, Monseniour. Én egy becsületes kapitány vagyok...";
			link.l1.go = "Cortny_4";
		break;
		
		case "Cortny_4":
			dialog.text = "A legkevésbé sem érdekelnek az önök sötét kis ügyletei, uram. Kicsit utánanéztem önnek, és hogy ôszinte legyek, önre gyanakodtam elôször, amikor meghallottam, hogy ön Martinique-on járt, közvetlenül a Regina eltûnése után. Ön azonban nem idióta, és az emberei nem játszadoztak itt gyöngyökkel. Ezért egyelôre kikerült a gyanúm alól.";
			link.l1 = "Gyöngyök? Milyen gyöngyökrôl fecseg?";
			link.l1.go = "Cortny_5";
		break;
		
		case "Cortny_5":
			dialog.text = "Kézzel válogatott, nagyméretû gyöngyök a spanyol West Main mûveleteibôl. A gyöngyök is feketék, ami azt jelenti, hogy rendkívül ritkák, hallottál már ilyesmirôl?";
			link.l1 = "Gondolom, mégis mindig azt hittem, hogy ez is csak egy újabb tengerész baromság. Ugyanaz, mint a repülô hollandról szóló történetek. Julianne, mi a baj?";
			link.l1.go = "Cortny_6";
		break;
		
		case "Cortny_6":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_104";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Cortny_7":
			dialog.text = "Meg kell kérnem, hogy mutassa be itt, asszonyom. Rendkívül fontos dologról van szó. Addig is, uram, el kell mondania mindent Moreno kapitányról. Gyanítom, hogy tôle kapta azt a nyomot. Nagyon kíváncsi vagyok a szerepére ebben a darabban.";
			if (CheckAttribute(pchar, "questTemp.Portugal"))
			{
				link.l1 = "Moreno nem az igazi neve, Monseniour Cortney. A neve Hernando Vasquez, más néven a Véres Don, egy spanyol kalóz, aki az Albatros - a hírhedt portugál Bartholomew hajójának - szállásmestere volt.";
				link.l1.go = "Cortny_8";
			}
			else
			{
				link.l1 = "Csak néhány szót váltottunk egymással. Nincs sok mondanivalóm. Úgy nézett ki, mint egy igazi tengeri farkas.";
				link.l1.go = "Cortny_9";
			}
		break;
		
		case "Cortny_8":
			dialog.text = "Nahát, nahát. És megkérdezhetem, honnan tudja ezt?";
			link.l1 = "Ismertem a kapitányát. Valójában én fogtam el és adtam át a hollandoknak. Hosszú történet. Kár, hogy akkoriban nem kaptam el magát Vasquezt...";
			link.l1.go = "Cortny_10";
		break;
		
		case "Cortny_9":
			dialog.text = "Maga is egy tengeri farkas, uram. Nem hiszem, hogy nem vett észre többet.";
			link.l1 = "Csak egy enyhe akcentust, a kinézetét és a viselkedését. Lefogadom, hogy spanyol, Cortney monsieur.";
			link.l1.go = "Cortny_10";
		break;
		
		case "Cortny_10":
			dialog.text = "Ez egy játékmegszakító, uram. És ez rossz. Asszonyom, megtalálta a nyakláncot? Hadd vizsgáljam meg\nIgen, ez valóban az egyik spanyol fekete gyöngy. Nézze csak meg, ez a tengerész baromság eléggé valódi. Már csak azt kell kideríteni, hogy az a de Chievous hogyan jutott egy ilyenhez. Egyébként ô nem de Levy Vantadur herceg fattyúja?";
			link.l1 = "Igen, ô az. Amennyire tudjuk, a helyi kalózbáróval üzletelt Le Francois-ban. Talán tôle vette ezt a gyöngyöt?";
			link.l1.go = "Cortny_11";
		break;
		
		case "Cortny_11":
			dialog.text = "Lehetséges. De nekem egyáltalán nem tetszik a spanyol nyomozás. Mindenesetre köszönöm az együttmûködését. Attól tartok, holnap ugyanebben az idôpontban újra meg kell látogatnom önt. Szeretném kérni de Maure kapitány jelenlétét is. Talán több kérdésem is lesz önhöz. Most Le Francois-hoz kell mennem.";
			link.l1 = "Monseniour Cortney, várjon. Talán csatlakozhatnék önökhöz? Jacques Barbazon nem azzal érdemelte ki a becenevét, hogy szeretô és szelíd ember, ráadásul ez az ügy engem is érdekel.";
			link.l1.go = "Cortny_12";
		break;
		
		case "Cortny_12":
			dialog.text = "Kapitány, meghatódtam az aggodalmától, de nemet mondok. Ez egy állami ügy. A gazember tudja, hol a helye, és nem merne kezet emelni a korona küldöttjére, különben a szánalmas falujának vége! Ismét elnézést kérek a tolakodásért, asszonyom. Jó estét, asszonyom.";
			link.l1 = "Találkozunk holnap este, báró úr.";
			link.l1.go = "Cortny_13";
		break;
		
		case "Cortny_13":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_106";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Cortny_14":
			PlaySound("VOICE\English\LE\Cortny\Cortny_03.wav");
			dialog.text = "Ne haragudjon rá, kapitány úr! Nagyon meggyôzô tudok lenni. A története lenyûgözô, tényleg. Azt hiszem, hasznát vehetném.";
			link.l1 = "Elégedettnek tûnik. Hogy ment Le Francois-ban?";
			link.l1.go = "Cortny_15";
		break;
		
		case "Cortny_15":
			dialog.text = "Ahogy vártam, az ön bárója szelíd volt, mint egy bárány. Mindent elmondott, amit hallani akartam. Mint mondtam, rendkívül meggyôzô tudok lenni.";
			link.l1 = "";
			link.l1.go = "Cortny_16";
		break;
		
		case "Cortny_16":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_112";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Cortny_17":
			dialog.text = "Ma egyedül jöttem ide, nincsenek embereim az ajtó mögött. Mi a fene?!";
			link.l1 = "Rossz érzésem van ezzel kapcsolatban. Julianne, álljon mögém, most! Báró úr, a korona követei ugyanolyan jól harcolnak, mint ahogyan beszélnek?";
			link.l1.go = "Cortny_18";
		break;
		
		case "Cortny_18":
			DialogExit();
			GoldenGirl_CortnyBandosFight();
		break;
		
		case "Cortny_19":
			PlaySound("VOICE\English\LE\Cortny\Cortny_03.wav");
			dialog.text = "Maga aztán tud bánni a karddal, kapitány! Ôszintén szólva, nem volt egy sétagalopp. Kik voltak ezek az emberek?";
			link.l1 = "Meg kéne kérdeznünk a barátaikat - hallottam több lépést. Bárcsak az ôrök lennének...";
			link.l1.go = "Cortny_20";
		break;
		
		case "Cortny_20":
			DialogExit();
			GoldenGirl_CortnyMercenFight();
		break;
		
		case "Cortny_21":
			dialog.text = "Hihetetlen! Azt hiszed, hogy ez a szemétláda meg merte tenni mindezt?! Meg fog fizetni, esküszöm!";
			link.l1 = "Lélegezzen! Barbazon ki fogja húzni a seggét a vádak alól. Azt fogja mondani, hogy ez csak egy átlagos razzia volt, amit pitiáner betörôk követtek el egy gazdag házban. Különben is, ô egy átkozott kalóz, miért érdekelnék a hatóságok! Mindazonáltal most már biztos vagyok benne, hogy sikerült valami igazán életképes dolgot megtudnia. Arra kérlek, hogy oszd meg velem ezt a tudást.";
			link.l1.go = "Cortny_22";
		break;
		
		case "Cortny_22":
			dialog.text = "Nem mondhatok nemet, ugye? Különben a következô kísérlet talán sikerrel járna? Rendben, úgy teszek, mintha nem vettem volna észre a fenyegetés jelét a hangjában. Tegyük fel, hogy viszonzom a szívességet. A Kedves Jacques nem adott el gyöngyöket a nemes fattyadnak. Ô vásárolt. Ez az.";
			link.l1 = "Tehát de Chievous volt az, aki elfogta a Reginát? Egy gazember ô, de nehéz elhinni, hogy közönséges kalózkodásra alacsonyodott volna le.";
			link.l1.go = "Cortny_23";
		break;
		
		case "Cortny_23":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_117";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Cortny_24":
			dialog.text = "A Reginát aligha nevezném egy kalóz szokásos zsákmányának, kapitány. Feltételezzük, hogy legalább fél tucat fekete gyöngy volt nála. Még egyetlen fekete gyöngy is felbecsülhetetlen értékû. Mindenképpen találkoznom kell ezzel a Sir de Chievous-szal, bármi áron.";
			link.l1 = "Segíthetek, Monseniour. De elôbb hadd tisztázzak valamit. Úgy tûnik, nem érdekel Botot asszony nyaklánca, tehát nem a gyöngyök miatt van itt. Mi volt még a Regina fedélzetén?";
			link.l1.go = "Cortny_25";
		break;
		
		case "Cortny_25":
			dialog.text = "Nagyon jó, úgy veszem, hogy a körülményekre való tekintettel többet kell majd mondanom.... Tudja, a rakomány nem olyan fontos, mint maga a hajó. A Regina nevû currier brigantint a Trinidad-i San Jose kikötôjébe rendelték. A kapitánya információkat gyûjtött, és elvégzett nekünk néhány... megbízást\nAz utolsó megbízása az volt, hogy elszállítsa a zsákmányt, amit a kapitányainknak sikerült kiszedniük a spanyol gyöngymûveletekbôl. Három évnyi erôfeszítésünkbe került, hogy megszerezzük ezt a nyomot. A fekete gyöngyök bizonyára jelentôsek, de a Regina elvesztése végzetes. Nem véletlen volt, valaki, aki tudott a gyöngyeirôl, bizonyára tudott a többirôl is.";
			link.l1 = "Pompás, szóval mégiscsak hírszerzési szolgáltatásról van szó! Attól félsz, hogy az egész kémhálózat, amit kiépítettél, veszélyben van? Most már látom a bajok teljes terjedelmét.";
			link.l1.go = "Cortny_26";
		break;
		
		case "Cortny_26":
			dialog.text = "Hallott már John Thurloe-ról? Ô a Korona hírszerzés vezetôje. Egy nap Londonban leszek, és személyesen neki fogok beszámolni a Regina sorsáról. Meg kell találnom, hol van a tégla, és... el kell intéznem a forrást. Ráadásul ott van még az a titokzatos Moreno kapitánya is. Ha a spanyolok lenyomozták a gyarmati kémhálózatunkat, évek kemény és fáradságos munkája megy délre!";
			link.l1 = "Tudod, mindez kezd értelmet nyerni, ha az összképet nézzük. Kezdem azt hinni, hogy valaki spanyol akcentussal beszélt de Chievousnak a Regináról és a fekete gyöngyökrôl.";
			link.l1.go = "Cortny_27";
		break;
		
		case "Cortny_27":
			dialog.text = "Egyformán gondolkodunk. Nincs jobb módja egy leleplezett kémhálózat kihasználásának. Egy diplomáciai incidens egy ilyen magas rangú emberrel... Egy ilyen incidens súlyosan károsíthatja a brit-francia kapcsolatokat, csak megfelelô nyomokat kell táplálni, és csak várni kell a nemzetközi botrányra. Talán még a fekete gyöngyökrôl szóló nyomot is szándékosan adták be nekünk.";
			link.l1 = "Azok az átkozott kasztíliaiak, igaz? Szóval mit tegyünk de Chievousszal?";
			link.l1.go = "Cortny_28";
		break;
		
		case "Cortny_28":
			dialog.text = "Hogy ôszinte legyek, fogalmam sincs. Ha ez egy spanyol provokáció, akkor bölcsebb lenne, ha egyszerûen figyelmen kívül hagynánk. De meg kell tudnom, hogyan szerzett tudomást a Regináról, és milyen rosszul néz ki a hálózatunk a spanyol gyarmatokon. Az életemmel is tartozom neked, és szándékomban áll visszafizetni.";
			link.l1 = "Ôszinteséget az ôszinteségért, báró úr. Minden segítség jól jönne. Már eléggé elkeseredett vagyok ahhoz, hogy fontolóra vegyem a márkinô elrablását.";
			link.l1.go = "Cortny_29";
		break;
		
		case "Cortny_29":
			dialog.text = "Ugye tudod, hogy de Chievous így tünteti el a nyomait? Olyan könnyû lesz rád kenni az egész zûrzavart, beleértve a Regina eltûnését is. Ezért a következôt javaslom. Marquise Botot közölte velem, hogy de Chievous nem vesz részt a cserén, és biztonságban marad Basse-Terre-ben. Vagy rájött, hogy milyen zûrzavarba keveredett, vagy kezd gyanút fogni. Olyan óvatos lesz, mint egy konyhai egér. Ezért megyek veled Dominikára.";
			link.l1 = "De az ô foglya az én prioritásom, nem kockáztathatom az életét! Ô egy túsz, aki cserére vár!";
			link.l1.go = "Cortny_30";
		break;
		
		case "Cortny_30":
			dialog.text = "Ne aggódjon - nyomást fogok gyakorolni Jacques Dille do Parkuet-ra, és elfogatóparancsot szerzek de Chievous hajójára. Kétlem, hogy az emberei tisztában vannak a helyzetükkel, különben óvatosabban bánnának azokkal a gyöngyökkel. Elmegyünk hozzájuk egy hosszúhajóval, és közvetlenül átadjuk nekik a parancsot.";
			link.l1 = "Igen, emlékszem a kényszerítô képességedre, Monseniour, de ez kockázatos. Méghozzá súlyos.";
			link.l1.go = "Cortny_31";
		break;
		
		case "Cortny_31":
			dialog.text = "Teljesen igazad van, de vállalnod kell, ha el akarod fogadni a segítségemet. Amint végeztünk Dominicában, elmegyek Basse-Terre-be, és követelem de Lyon kormányzótól, hogy adja át az ellenfelét. A hatalmam megengedi. Nem hagyhatjuk, hogy de Chievous elszökjön.";
			link.l1 = "Tényleg készen áll erre, Monseniour? Ez háborút indíthat el, nem igaz?";
			link.l1.go = "Cortny_32";
		break;
		
		case "Cortny_32":
			dialog.text = "Lefogadom, hogy soha nem engednék meg, hogy ez megtörténjen. Egyértelmûen kizárt dolog, mivel már tudjuk az igazságot. A politika egy kurva, kapitány. Ígérem, hogy de Chievous-t be fogom vezetni a brit börtönökbe, csak neked személyesen. Ez eléggé úgy hangzik, mint egy olyan megoldás, amit még az apja is elfogadható árnak tartana.";
			link.l1 = "Nem mondhatom, hogy tetszik a terve, de nem látok más megoldást.";
			link.l1.go = "Cortny_33";
		break;
		
		case "Cortny_33":
			dialog.text = "Biztosíthatom, hogy sikerülni fog. Most el kell mennem a kormányzóhoz, és parancsot kell adnom az embereimnek. Ha találkozik a márkinôvel, mondja meg neki, hogy megtarthatja a gyöngyöt, hálából a nyomozásban nyújtott segítségéért.";
			link.l1 = "Köszönöm, báró úr. Találkozunk a hajómon, hamarosan kihajózunk.";
			link.l1.go = "Cortny_34";
		break;
		
		case "Cortny_34":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "GoldenGirl_CortnyPassenger", 15.0);
		break;
		
		case "Cortny_35":
			PlaySound("VOICE\English\LE\Cortny\Cortny_02.wav");
			dialog.text = "William Cortney, Cortney báró, szolgálatára. A Brit Birodalom által rám ruházott hatalomnál fogva, megbízható szövetségesének, Franciaországnak minden támogatásával, az ön hajóját ezennel letartóztatom. Itt vannak a papírok, kérem, olvassa el ôket, és mondja meg az embereinek, hogy ne nyúljanak a fegyverekhez. Önt ôrizetbe vettük, de még nem tartóztattuk le. Ha nem csinálnak semmi ostobaságot, az elsô kikötôben szabadon engedik önöket.";
			link.l1 = "Báró úr, vissza kell szereznem a... a tisztemet!";
			link.l1.go = "Cortny_36";
		break;
		
		case "Cortny_36":
			PlaySound("VOICE\English\LE\Cortny\Cortny_04.wav");
			dialog.text = "Ne aggódjon kapitány, elkísérem a hajójára. Kérem, hogy most azonnal térjen vissza a hosszúhajóra. Átveszem a hajó parancsnokságát, és elhajózom Basse-Terre-be. Nyugodtan hagyjon itt minket, ha nem áll szándékában személyesen kigúnyolni a fôellenségét. Csak arra kérem, hogy néhány emberét adja át nekem, hogy segítsen nekünk eljutni Guadeloupe-ba.";
			link.l1 = "Rendben, Monseniour. Inkább nem. Küldje el neki a legrosszabb üdvözletemet. Viszontlátásra és még egyszer köszönöm!";
			link.l1.go = "Cortny_37";
		break;
		
		case "Cortny_37":
			DialogExit();
			DoQuestReloadToLocation("Shore27", "goto", "goto13", "GoldenGirl_DominicaCortnyFinal");
		break;
		
		case "Cortny_38":
			PlaySound("VOICE\English\LE\Cortny\Cortny_04.wav");
			dialog.text = "Charles, örülök, hogy látlak. Reménykedtem a visszatérésedben, de nem igazán hittem benne.";
			link.l1 = "Hasonlóképpen, báró úr. Azért jött, hogy meglátogassa a márkinét? Egyébként hol van?";
			link.l1.go = "Cortny_39";
		break;
		
		case "Cortny_39":
			dialog.text = "Még mindig nem érted, ugye? Elmenekült. Továbbá Angerran de Chievous ôszinte bocsánatkérését küldi. Sikerült meggyôznöm arról, hogy te sosem voltál része a játéknak, mégis csak egy újabb áldozata. Akárcsak ô. A jóember nem vette a fáradságot, hogy írjon, de mélységesen sajnálja, ahogy a dolgok alakultak.";
			link.l1 = "Mélységesen sajnálja, ugye?! Mirôl beszélsz, Monseniour?";
			link.l1.go = "Cortny_40";
		break;
		
		case "Cortny_40":
			dialog.text = "Te és én, mi elnéztük a legfontosabbat. Honnan értesült a gyöngyökrôl? Ki hívta meg azt a spanyol kapitányt ebbe a házba? Ki késztethette ezt a fattyút arra, hogy ilyen zsákmányt hajszoljon?";
			link.l1 = "Komolyan beszélsz? Ez nem lehet...";
			link.l1.go = "Cortny_41";
		break;
		
		case "Cortny_41":
			dialog.text = "Határozottan lehet. Marquise tökéletesen játszotta a szerepét, szinte végighúzta az egészet. Egy nyomozásunknak köszönhetôen azonban úgy közelítettem meg de Chievous-t, mint aki nem tolvaj és kalóz, hanem mint a csalás áldozata, ami ô. Elég hamar rájött, hogy mibe rángatta bele a nô, azonban nem volt bizonyítéka, és úgy döntött, hogy magától cselekszik. Tudja, mi történt ezután.";
			link.l1 = "Úgy érti, hogy mindezt a márki szervezte meg? De Chievous úgy vette be, mint egy gondatlan csecsemô!";
			link.l1.go = "Cortny_42";
		break;
		
		case "Cortny_42":
			dialog.text = "Pontosan. A szenvedély nagyon veszélyes dolog, Charles! Emlékszel arra az éjszakára, amikor ebben a házban játszottál? Angerran úgy akarta kicsikarni a marquise-ból a szükséges bizonyítékokat, hogy pártfogást szerez fölötte. Igen, csalt, de kétségbeesett volt, miután a reménytelen szenvedély éveit a legpusztítóbb árulás zárta le! De te közbeléptél, bajnokának nevezted magad, és sikerrel jártál ebben a szerepben. De Chievous úgy vélte, hogy ön és ô egy véleményen vannak. Ellopott egy hajót, amelyet elvesztett veled szemben, hogy megakadályozza, hogy megszerezd a rönkjeit. Arra használta fel a tisztedet, hogy megpróbálja ôt és téged - halálos ellenségeit, ahogy ô hitte - egymásnak ugrasztani.";
			link.l1 = "Elfogytak a szavaim!";
			link.l1.go = "Cortny_43";
		break;
		
		case "Cortny_43":
			dialog.text = "Most már tudod, hogy van ez, Charles! A márkinô okos, lélegzetelállítóan szép és nem kevésbé veszélyes. Nem tudom, meddig manipulálta Új-Franciaország legjobbjait. Azt mondanám, hogy sok éven át. Mindegy, ez már nem tartozik rád. Örülök, hogy újra találkoztunk, de még több szobát kell felforgatnom, ez egy nagy ház. Valószínûleg nem fogunk találni semmit, de legalább meg kell próbálnunk\nEgy dolgot még, mielôtt elválnak útjaink. Tessék, fogd ezt. Egy emléktárgy, amire emlékezni fogsz. Talán majd megajándékozod vele a barátnôdet, ha készen állsz. Nagyon szerencsés vagy, tudod. Fôleg de Chievoushoz képest, szegény szerencsétlen!";
			link.l1 = "Igaza van, az vagyok. Isten önnel, és sok sikert a keresésben, báró úr!";
			link.l1.go = "Cortny_44";
		break;
		
		case "Cortny_44":
			DialogExit();
			DoQuestReloadToLocation("FortFrance_Town", "reload", "reload9", "GoldenGirl_SPFinal");
		break;
		
		case "Cortny_45": // фин 3
			PlaySound("VOICE\English\LE\Cortny\Cortny_03.wav");
			dialog.text = "Milyen szép napunk van ma, nem igaz, kapitány? Hallottam a hôstetteidrôl, de sosem gondoltam, hogy egy banális kalóz vagy. Micsoda arcátlanság - eljönni a St. Jones-ba azok után, amit tett!";
			link.l1 = "Lehet, hogy kalóz vagyok, ez igaz, uram, de vajon úgy nézek ki, mint egy idióta? Mi a fenéért jöttem volna ide, miután kifosztottam a Mercury-t és megszabadítottam a spanyol gyöngyöktôl?";
			link.l1.go = "Cortny_46";
		break;
		
		case "Cortny_46":
			dialog.text = "Bevallom, ez az egyetlen oka annak, hogy most ezt a beszélgetést folytatod, ahelyett, hogy egy hurokkal hadonásznál. Látod, van egy apró részlet, amit eltitkoltunk ebben az ügyben. És most nem a gyöngyrôl beszélek, amit nálad találtunk. Hanem a brigantin nevérôl.";
			link.l1 = "Ez mit jelent?";
			link.l1.go = "Cortny_47";
		break;
		
		case "Cortny_47":
			PlaySound("VOICE\English\LE\Cortny\Cortny_04.wav");
			dialog.text = "A Regina egy currier brigantine, amely az elmúlt két évben San Jose kikötôjébe volt bejelentkezve. A kapitánya információkat gyûjtött nekünk, és emellett... mindenféle megbízásokat teljesített. Hivatalosan is keressük a hajót az általa szállított diplomáciai posta miatt. Ez nem egy nagy trükk, elismerem. Mégis, a hajó valódi nevét nem tudhatnánk meg anélkül, hogy a kapitány kabinját alaposan átkutatnánk.";
			link.l1 = "Vak voltam, de most már látok. Kérem, hallgasson meg, uram, megmagyarázom!";
			link.l1.go = "Cortny_48";
		break;
		
		case "Cortny_48":
			dialog.text = "Nos, próbálja meg jobban, kapitány. Az élete forog kockán.";
			link.l1 = "Semmi közöm ehhez a kémsztorihoz! Ahogy a spanyoloknak sincs. A hálózata biztonságban van, ne aggódjon. Azonban volt egy tégla, és valaki felhasználta. És aztán vitába keveredtem ezzel a valakivel. Bizonyítékokat találtam a Merkúr-üzletben való részvételére, és ezeket akartam felhasználni, hogy legyôzzem.";
			link.l1.go = "Cortny_48_1";
		break;
		
		case "Cortny_48_1":
			dialog.text = "";
			link.l1 = "Isten a tanúm, én ezt az ügyet közönséges kalózkodásnak gondoltam, eszembe sem jutott, hogy a Korona intelligenciájának köze van hozzá! Nekem csak ez a gyöngy van a birtokomban, mégis nagyon jól tudom, mikor és hol találhat még többet.";
			link.l1.go = "Cortny_49";
		break;
		
		case "Cortny_49":
			dialog.text = "Hallott már John Thurloe-ról? Ô a koronai hírszerzés vezetôje. Egy nap Londonban leszek, és személyesen neki fogok beszámolni a Mercury sorsáról. Ezért adja meg a nevét annak a szerencsétlen ellenfelének.";
			link.l1 = "Angerran de Chievous, gróf de Levy Vantadur fattyú. Feltételezem, hogy a Merkúrt csak a kapribogyó' plunder szállítójának tartotta. Tudhatott a gyöngyökrôl, de fogalma sem volt a brit hírszerzés kapcsolatáról.";
			link.l1.go = "Cortny_50";
		break;
		
		case "Cortny_50":
			dialog.text = "Nem okoz csalódást, kapitány, ezt meg kell hagyni! Micsoda választék a szórakozásból és az ellenségekbôl! Hát jó. Milyen más bizonyítéka van a gyöngyön kívül?";
			link.l1 = "De Chievousnak van egy fregattja. Régebben az enyém volt... csak egy éjszakára, mégis sikerült tanulnom valamit. Rendkívül pedáns ember, a naplójából mindent megtudhatsz a Merkúr elleni támadásáról. Egészen biztos vagyok benne, hogy még mindig birtokolja a díj egy részét is. Talán még több fekete gyöngyöt is, ha több is lenne.";
			link.l1.go = "Cortny_51";
		break;
		
		case "Cortny_51":
			dialog.text = "Több mint egy, erre lehet számítani. Soha nem tennénk ki a Reginát egy rakás közönséges gyöngyért. Remélem, megérti, hogy feltétlenül beszélnem kell Monseniour de Chievous-val. Nem érdekelnek a gyöngyök, de többet kell megtudnom a szivárgásról. A feletteseim el fognak temetni, ha nem adok teljes képet nekik.";
			link.l1 = "Szívesen szervezek önnek egy találkozót, de sietnünk kell! Ebben a pillanatban de Chievous fregattja úton van Guadeloupe felé, ahol a tulajdonosa jelenleg a helyi kormányzó védelme alatt tartózkodik. Biztos vagyok benne, hogy tisztában van azzal, hogy mit tett, és a lehetô leghamarabb elmenekül az Újvilágból.";
			link.l1.go = "Cortny_52";
		break;
		
		case "Cortny_52":
			dialog.text = "Ezek nagyon komoly vádak nagyon komoly emberektôl, kapitány. Tisztában van vele, hogy milyen... szarvihar kerekedhet utána? Egy szövetséges zászló alatt közlekedô hajó megtámadása? Ez komolyan megnehezítheti két nagy nemzet kapcsolatát. Nehezen tudom elképzelni, hogy milyen mélyen sikerült a bôre alá férkôznie, hogy ennyit akar kockáztatni.";
			link.l1 = "Elvett tôlem valamit, milord. Valamit, ami nekem a legértékesebb. Többet, mint az életem. Ezt helyre kell hoznom. Ha ez háborúhoz vezet, akkor a hazámat fogom szolgálni a zászlaja alatt. Mindazonáltal, de Chievous megkapja, amit megérdemel, és ô az egyetlen, aki hibáztatható!";
			link.l1.go = "Cortny_53";
		break;
		
		case "Cortny_53":
			dialog.text = "Mondták már önnek, hogy ön nagy veszélyt rejt magában, kapitány úr? Kész háborút kirobbantani a fél földkerekségen, hogy elérje a célját? Rendben van, csináljuk a maga módján! Elmegyek önnel Basse-Terre-be. Nem engedhetem el ezt a nyomot. Elküldök egy írnokot, hogy írja le a bizonyítékait, amíg én elôkészítem a hajómat.";
			link.l1 = "Köszönöm, uram. De itt nincs vesztegetni való idônk, figyelmeztetem!";
			link.l1.go = "Cortny_54";
		break;
		
		case "Cortny_54":
			dialog.text = "De Maure kapitány, idôben odaérünk, nem kételkedem önben. Ha azonban ez a kaland nem fog sikerülni... érti? Még egy rendes sírt sem ígérhetek.	";
			link.l1 = "Igenis, uram. Teljesen megértelek.";
			link.l1.go = "Cortny_55";
		break;
		
		case "Cortny_55":
			DialogExit();
			npchar.dialog.currentnode = "Cortny_56";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "goto", "goto13", "Baster_Townhall", "goto", "goto4", "GoldenGirl_ReloadToBaster", 10.0);
		break;
		
		case "Cortny_56":
			dialog.text = "A kocka el van vetve, kapitány. Találkozót kértem Angerran de Chievous-szal. A fregattját azonnal átkutatjuk, amint megérkezik. Francois de Lyon kételkedik, de az irataim pecsétjei egyelôre visszatartják. Arra kérem, hogy maradjon a városban, amíg a helyzet nem rendezôdik.";
			link.l1 = "Természetesen, uram, megértem.";
			link.l1.go = "Cortny_57";
		break;
		
		case "Cortny_57":
			dialog.text = "Akkor remélem, hogy ezt is megérti. Add át a kardodat az uraknak odaát, és kövesd ôket, így biztos vagyok benne, hogy betartod az ígéretedet.";
			link.l1 = "Hihetetlen... Cortney uram, komolyan mondja?!";
			link.l1.go = "Cortny_58";
		break;
		
		case "Cortny_58":
			dialog.text = "Halálosan komolyan. Még mindig az egyik fô gyanúsítottam vagy, és ilyen körülmények között elengedni téged nagy ostobaság lenne tôlem. Bocsánatot fogok kérni öntôl, ha és amennyiben a szavai igaznak bizonyulnak.";
			link.l1 = "";
			link.l1.go = "Cortny_59";
		break;
		
		case "Cortny_59":
			DialogExit();
			GoldenGirl_BasterArest();
		break;
		
		case "comendant":
			dialog.text = "Üdvözlöm, Monsieur de Maure. Mehetünk?";
			link.l1 = "Örömmel, mik a szabályok? Hogy ôszinte legyek, túlságosan lefoglalt az étel, és valószínûleg félreértettem a feltételeket.";
			link.l1.go = "comendant_1";
		break;
		
		case "comendant_1":
			dialog.text = "A szabályok egyszerûek. 10 000 pezó egy kártyáért, addig játszunk, amíg egyikünk meg nem adja magát. A nyugtákat és a hiteleket nem fogadjuk el.";
			link.l1 = "Nekem megfelel. Csináljuk, ezredes.";
			link.l1.go = "comendant_2";
		break;
		
		case "comendant_2":
			DialogExit();
			npchar.money = 70000;
			pchar.questTemp.GoldenGirl.Game.G1 = "true"; // атрибут квестовой игры
			// вызов интерфейса игры
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
            pchar.GenQuest.Cards.iRate     = 10000; // ставка
            pchar.GenQuest.Cards.SitType   = false;
			LaunchCardsGame();
		break;
		
		case "comendant_3":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Win"))
			{
				dialog.text = "A francba! Soha többé! Rendben, Monsieur de Maure, sok szerencsét a következô fordulóban.";
				link.l1 = "Örömmel, ezredes. Viszontlátásra.";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Fail"))
				{
					dialog.text = "Jól küzdött, de Fortuna úrnônek megvolt a maga terve. Viszlát, Monsieur de Maure. Köszönöm a játékot.";
					link.l1 = "Igen, azt hiszem, túlbecsültem magam. Viszlát, ezredes.";
				}
				else
				{
					dialog.text = "Úgy döntött, hogy visszautasítja a további játékot, és ezzel elismerte vereségét! Dicsôségesen harcoltál, de a szerencse másképp döntött. Viszlát, Monsieur de Maure, köszönöm a játékot.";
					link.l1 = "Igen, azt hiszem, túlbecsültem magam. Viszlát, ezredes.";
				}
			}
			link.l1.go = "comendant_4";
		break;
		
		case "comendant_4":
			DialogExit();
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "none", "", "", "", 20.0);
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_17";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		// Португалец или Васкез
		case "moreno":
			if (CheckAttribute(pchar, "questTemp.Portugal")) // был квест
			{
				if (CheckAttribute(pchar, "questTemp.Portugal.GG1")) // португалец
				{
					dialog.text = "Charles de Maure kapitány, micsoda meglepetés!";
					link.l1 = "Kapitány. Moreno a seggem! Mi szél hozta ide?";
					link.l1.go = "moreno_1";
				}
				else
				{
					if (CheckAttribute(pchar, "questTemp.Portugal.GG2")) // васкез враждебный
					{
						pchar.questTemp.GoldenGirl.Vaskez = "true";
						dialog.text = "Charles de Maure kapitány, örvendek.";
						link.l1 = "Találkoztunk már korábban, monsieur... Moreno?";
						link.l1.go = "moreno_5";
					}
					else // васкез нейтральный
					{
						dialog.text = "Charles de Maure kapitány, örvendek.";
						link.l1 = "Találkoztunk már korábban, monsieur... Moreno?";
						link.l1.go = "moreno_4";
					}
				}
			}
			else  // васкез нейтральный
			{
				dialog.text = "Charles de Maure kapitány, örvendek.";
				link.l1 = "Találkoztunk már korábban, monsieur... Moreno?";
				link.l1.go = "moreno_4";
			}
		break;
		
		case "moreno_1":
			dialog.text = "Ez egy hosszú történet. Ugyanaz, mint mindig, kapitány. Látom a szemében, hogy kérdései vannak. Csak maradjon csendben, és tegyen úgy, mintha egy egyszerû tengerészen gúnyolódna.";
			link.l1 = "Igen, jól áll neked ez a puccos öltöny, egyszerû barátom. Azt mondanám, tudod, hogy kell viselni.";
			link.l1.go = "moreno_3";
		break;
		
		case "moreno_3":
			dialog.text = "Csak ritka alkalmakkor, szerencsére. A mai nap. Játsszunk, kapitány. Az emberek figyelnek, nem illik megvárakoztatni ôket.";
			link.l1 = "Rendben, majd késôbb beszélünk. Megegyeztünk... Moreno kapitány, ha kérhetem.";
			link.l1.go = "moreno_6";
		break;
		
		case "moreno_4":
			dialog.text = "Ismerem magát egy kicsit, de ez most lényegtelen. Ossza ki a lapokat, de Maure kapitány, az emberek show-t akarnak.";
			link.l1 = "Kíváncsi vagyok. Különösen a spanyol akcentusa és Botot asszony kreditjei miatt. Rendben. Tenger a tenger ellen, rajta!";
			link.l1.go = "moreno_6";
		break;
		
		case "moreno_5":
			dialog.text = "Emlékszem magára. Amikor ön és a volt kapitányom felnyársalták az embereimet Le Francois-ban. Az a szemétláda úgyis azt kapta, amit megérdemelt, nem a maga segítsége nélkül, ha jól emlékszem. De ne várjon a hálámra, maga ölte meg Franz Garke-ot, és én nem bocsátok meg magának miatta.";
			link.l1 = "A portugálok szállásmestere? A véres Don, igaz? Ez az éjszaka egyre jobb és jobb lesz. Gyerünk, csináljuk!";
			link.l1.go = "moreno_6";
		break;
		
		case "moreno_6":
			DialogExit();
			npchar.money = 110000;
			pchar.questTemp.GoldenGirl.Game.G2 = "true"; // атрибут квестовой игры
			// вызов интерфейса игры
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
            pchar.GenQuest.Cards.iRate     = 10000; // ставка
            pchar.GenQuest.Cards.SitType   = false;
			LaunchCardsGame();
		break;
		
		case "moreno_7":
			if (!CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Win") && !CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Fail"))
			{
				dialog.text = "Úgy döntöttél, hogy visszautasítod a további játékot, és ezzel beismerted a vereséget! Gondolom, Fortuna úrnônek is volt mondanivalója. Viszlát, kapitány.";
				link.l1 = "Én is, Monsieur Moreno. Köszönöm a játékot.";
				link.l1.go = "moreno_8";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Portugal")) // был квест
			{
				if (CheckAttribute(pchar, "questTemp.Portugal.GG1")) // португалец
				{
					dialog.text = "Gondolom, Lady Fortune is megmondta a magáét. Viszlát, kapitány, talán még találkozunk.";
					link.l1 = "Én is, Monsieur Moreno. Köszönöm a játékot.";
					link.l1.go = "moreno_8";
				}
				else
				{
					if (CheckAttribute(pchar, "questTemp.Portugal.GG2")) // васкез враждебный
					{
						dialog.text = "Gondolom, Lady Fortune-nak volt egy mondása. Viszlát, kapitány, talán még találkozunk más körülmények között, he-he-he.";
						link.l1 = "Alig várom, Monsieur Moreno.";
						link.l1.go = "moreno_8";
					}
					else // васкез нейтральный
					{
						dialog.text = "Ez az. Fortuna döntött, kapitány. Viszontlátásra.";
						link.l1 = "Viszlát, Monsieur Moreno.";
						link.l1.go = "moreno_8";
					}
				}
			}
			else  // васкез нейтральный
			{
				dialog.text = "Ez az. Fortuna döntött, kapitány. Viszontlátásra.";
				link.l1 = "Viszlát, Monsieur Moreno.";
				link.l1.go = "moreno_8";
			}
		break;
		
		case "moreno_8":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "none", "", "", "", 20.0);
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_19";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "moreno_9":
			dialog.text = "Örülök, hogy látom, Monseniour de Maure kapitány! Hogy ôszinte legyek, bármit vártam, beleértve a teljes ôrséget is, de önt nem.";
			link.l1 = "Monseniour Moreno, valami gondja van a helyi tisztviselôkkel? Egyébként én is örülök, hogy látlak, ha-ha!";
			link.l1.go = "moreno_10";
		break;
		
		case "moreno_10":
			dialog.text = "Mondom, nem lehet visszautasítani a háziasszonyunk meghívását. Legalábbis egy ilyen meghívást nem. Ugyan már Charles, hagyd abba ezt a komédiázást. Marquise biztosra vette, hogy tudom, hogy ismeri a valódi személyazonosságomat.";
			link.l1 = "...";
			link.l1.go = "moreno_11";
		break;
		
		case "moreno_11":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_90";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_12":
			dialog.text = "Asszonyom, ön elbûvölô! Ez az új barátja egyszer már megpróbált feladni engem. Tulajdonképpen nem sült el túl jól, sôt, annyiszor mentette meg a szánalmas seggemet, hogy már nem tudom megszámolni. Mindenesetre most már tartozom neki, úgyhogy nincs szükség fenyegetésre, ne aggódjon.";
			link.l1 = "Köszönöm, Bartholomew. Angerran de Chievous rendkívül kellemetlen helyzetbe szorított, és feltétlenül le kell ôt buktatnom. Egy számomra nagyon kedves ember élete múlik ezen. Bízz bennem, ezúttal semmi sem állíthat meg.";
			link.l1.go = "moreno_13";
		break;
		
		case "moreno_13":
			dialog.text = "Elég, kapitány, barátok vagyunk, igaz? Emlékszel arra a versenyre a fél szigetvilágon keresztül? Az ilyesmi sokat jelent nekem. Mindent megteszek, hogy segítsek neked. Hallottál már a Merkúrról?";
			link.l1 = "Az meg mi? Egy hajó?";
			link.l1.go = "moreno_14";
		break;
		
		case "moreno_14":
			dialog.text = "Egy brit brigantin, hogy pontos legyek. Az volt a szerepe, hogy D'Oyley ezredes magánhajósai zsákmányát szállítsa, akik kifosztották a spanyol gyöngyházüzleteket a Nyugati-folyón. Azokat, amelyek idônként legendás fekete gyöngyöket halásznak, hallott már róla? Ha információforrásom megbízható, akkor több ilyen gyöngyöt tároltak a Mercury-n. Egy hónappal ezelôtt lesben álltam Martinique és Guadeloupe között, és vártam ezekre a derék urakra. De hiába! Egy hetet töltöttünk a tengeren, mire kudarcot kellett vallani.";
			link.l1 = "Rendben, tehát a forrásod mégsem volt megbízható, és nem kaptál díjat magadnak. Mi köze van mindehhez de Chievousnak?";
			link.l1.go = "moreno_15";
		break;
		
		case "moreno_15":
			dialog.text = "Ugyanezt gondoltam, amíg meg nem tudtam, hogy a Mercury nem jelent meg Antiguán. Képzeljék el a meglepetésemet, amikor Curacao közelében látták, és Martinique közelében semmiképpen sem tudott elhaladni mellettem. A britek dühöngenek! Képzeljék el, hogy lemaradnak egy ilyen díjról, meg minden! Mindenesetre kíváncsi lettem, és nyomozni kezdtem, arról a különleges valakirôl, aki mindenkinek elrontotta a szórakozást. Az ilyen zsákmányt nem lehet gyorsan eladni, ezért elmentem Le Francoisba, hogy megtaláljam a szemetet, és megszerezzem, amivel tartozik nekem.";
			link.l1 = "A története ismerôsen cseng. Hallottál már valaha a szóról 'Karma'? Te biztosan tudod, hogyan találhatod meg a bajokat a hátsódon. De még mindig nem értem, hogy ez nekem mi hasznomra válhat?";
			link.l1.go = "moreno_16";
		break;
		
		case "moreno_16":
			dialog.text = "Ne siettesse, kapitány, mindjárt elmesélem a történetem legjobb részét. Az a mosdatlan, jól öltözött barátja - a fiai feltûnôen nagy gyöngyszemeket hagytak a helyi boltokban. A spanyol gyöngymûveletek büszkesége, amit nagy számban elpazaroltak.";
			link.l1 = "...";
			link.l1.go = "moreno_17";
		break;
		
		case "moreno_17":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_92";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_18":
			dialog.text = "Hallottad, kapitány?";
			link.l1 = "Gondolod, hogy de Chievous lopott gyöngyöket vett Jacques the Kind-tôl és az embereitôl? Attól tartok, ez... nem elég.";
			link.l1.go = "moreno_19";
		break;
		
		case "moreno_19":
			dialog.text = "De igen, kapitány. Nem vett, hanem eladott! Beszéltem errôl Barbazon-nal, és ô megerôsítette, hogy egy jelentôs tétel tökéletes gyöngyöt vásárolt valamelyik társától. Utána elküldte Európába. Megvan az a fekete gyöngy is a nyakláncban, és az is, hogy de Chievous hajója átment a javítómûhelyeken. A munkások elmondták, hogy a fregattján tizenkétfontosoktól lyukasak voltak a lyukak. Ki az, aki épeszû, hogy megtámadna egy fregattot ilyen babákkal?";
			link.l1 = "Úgy hangzik, mint a mi brigantinunk! Ráadásul emlékszem, hogy de Chievous azzal dicsekedett, milyen gyors a fregattja. De miért ez az ôrület? Egy darabban vagyunk Nagy-Britanniával, miért kockáztatnánk ennyit, és miért? A fekete gyöngyök rendkívül ritkák, de nem elérhetetlenek.";
			link.l1.go = "moreno_20";
		break;
		
		case "moreno_20":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_94";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_21":
			dialog.text = "És itt tévedett! A britek már hivatalos vizsgálatot indítottak a Mercury eltûnése ügyében, bár ôk csak eltûnt futárhajónak nevezik, fedélzetén néhány fontos irattal. Minden nyomot bôkezûen jutalmaznak, a felelôsöket szigorúan megbüntetik. A legjobb az egészben, hogy Antiguára küldtek egy különleges nemes tisztviselôt, aki most fáradhatatlanul kutakodik az ügyben. Nem emlékszem a nevére, flancos, mint az önelégült arca, de örülök, hogy nem rám vadászik!";
			link.l1 = "Na ez már valami! Úgy tûnik, hogy nagyon akarják azokat a fekete gyöngyöket. Vajon mennyi volt belôlük a Merkúron, és hogyan lehet mindez a tudás hasznomra?";
			link.l1.go = "moreno_22";
		break;
		
		case "moreno_22":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_96";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_23":
			dialog.text = "Miért, a söpredéknek sikerült felbosszantania önt is, márkinô? Szemétláda! Én is önnel vagyok, de Maure kapitány! Senki sem meri ellopni a portugál Bartolomeo zsákmányát!";
			link.l1 = "";
			link.l1.go = "moreno_24";
		break;
		
		case "moreno_24":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_98";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_25":
			dialog.text = "Szükségem van egy rendes italra ennyi beszéd után. Márkiné, mivel most már barátok vagyunk...";
			link.l1 = "Nem hiszem, hogy van rum ebben a házban, Bartholomew.";
			link.l1.go = "moreno_26";
		break;
		
		case "moreno_26":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_100";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_27":
			dialog.text = "Ja, persze, csak a fregattját hívta fel a brit nyomozó figyelmét! Ha ez a tervünk, akkor nem ismerem fel a jó öreg de Maure kapitányunkat!";
			link.l1 = "Nevetni fogsz, de ez a terv. Mindkettôtök segítségére szükségem lesz. Asszonyom - a felbérelt kalóz foglya leszel - Bartholomew, ez a te részed.";
			link.l1.go = "moreno_28";
		break;
		
		case "moreno_28":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_122";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_29":
			dialog.text = "És errôl a gazemberségemrôl is! Bartolomeo a portugál soha nem rabolt el nôt!";
			link.l1 = "És nem is fog, de de Chievous emberei számára annak fog tûnni. Ráadásul nem kell megmondani nekik a nevét. Vidd a hajónkra a hölgyet, és találkozzatok Angerran fregattjával a Scott-fok közelében. Cseréljétek el Juliannát a tisztemre, és térjetek vissza Martinique-ra. Aztán várjon meg engem és a márkinét.";
			link.l1.go = "moreno_30";
		break;
		
		case "moreno_30":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_125";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_31":
			dialog.text = "Ez az egész nagyon érdekes volt, Charles, te egy született lovag vagy. De hogy a fenébe adjuk vissza a csere után?";
			link.l1 = "Majd én elintézem. Nincs sok idônk, úgyhogy váljunk szét. Te és a márkinô Dominikára mentek, míg én St. Jonesba sietek. Megkeresem D'Oyley ezredest vagy azt a brit nyomozót, és elmondom neki, ki a felelôs a Merkúr eltûnéséért.";
			link.l1.go = "moreno_32";
		break;
		
		case "moreno_32":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_130";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_33":
			dialog.text = "Gondolt már arra a szarviharra, ami egy ilyen incidens után biztosan bekövetkezik, kapitány? Ebben a pillanatban Antigua egy darázsfészek, és maga azt mondja nekem, hogy dobjak rá egy követ. Emlékszem, hogy a háborúk kevesebb miatt kezdôdtek!";
			link.l1 = "Egyszerre csak egy probléma... Vissza fogom hozni, bármi áron! Hagyjuk, hogy de Levy Vantadur maga takarítsa el a mocskot, ha tényleg olyan erôs, mint mondják! De Chievous-nak is nehéz lesz megmagyaráznia, hogy Madame Botot hogyan került a hajójára.";
			link.l1.go = "moreno_34";
		break;
		
		case "moreno_34":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_132";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_35":
			if(CheckAttribute(pchar, "questTemp.GoldenGirl.Julianna_Prisoner"))
			{
				dialog.text = "Készen állsz? Egy imára! Marquise, készen áll az elrablásra?";
			}
			else
			{
				dialog.text = "Készen állsz? Egy imára! Marquise, mennyi idôbe telik összepakolni?";
			}
			link.l1 = "";
			link.l1.go = "moreno_36";
		break;
		
		case "moreno_36":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_134";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "secundant": // fix 22-03-20
			dialog.text = TimeGreeting()+", ...Monsieur de Maure. A nevem "+GetFullName(npchar)+", ez pedig "+GetFullName(characterFromId("GG_SecundantGG_2"))+". Ôexcellenciája arra kért minket, hogy legyünk tanúi az ön és Monsieur de Chievous párbajának.";
			link.l1 = "Jó estét, uraim. Remélem, minden simán megy, és senki sem fog meghalni ma este. De azért készüljenek fel mindenre. Ez 'gentleman' lehet csalódás.";
			link.l1.go = "secundant_1";
		break;
		
		case "secundant_1":
			dialog.text = "A nyugtalanságuk alaptalan. A párbaj elôre meghatározott feltételei szerint, semmilyen körülmények között nem avatkozhatnak bele másodpercek. De azért köszönjük, hogy figyelmeztetett minket. Az ellenfél megérkezett. Isten éltessen, kapitány. Ôexcellenciája megkért, hogy mondjam meg önnek, hogy imádkozni fog az ön... óvatosságáért.";
			link.l1 = "Biztos vagyok benne, hogy sokat fog segíteni. Mindegy, kezdjük el.";
			link.l1.go = "secundant_2";
		break;
		
		case "secundant_2":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "goto", "goto8", "", 5); 
			sld = characterFromId("Angerran");
			LAi_SetImmortal(sld, false);
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			for (i=1; i<=2; i++)
			{
				ref chr = characterFromId("GG_SecundantAG_"+i);
				LAi_SetActorType(chr);
				LAi_ActorFollow(chr, sld, "", 10.0);
			}
		break;
		
		case "sailor":
			dialog.text = "Kapitány, van egy kis gondunk. A hajónk... nos, nincs többé.";
			link.l1 = "Várj, mi?! Hogyan, ki? Egy teljes ôrségnek kellett volna rajta állomásoznia, szóval mi a faszról beszélsz?!";
			link.l1.go = "sailor_1";
		break;
		
		case "sailor_1":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "Nem, kapitány, nem a hajó. Fényes. A fregatt, amit tegnap nyertél, szóval most már a miénk is, igaz? Csak egy tucatnyi legénységet küldtünk oda. Azt mondta, ez elég lesz.";
			link.l1 = "Csak hagyd abba, baszd meg, és mondd el pontosan, mi történt az elejétôl fogva!";
			link.l1.go = "sailor_2";
		break;
		
		case "sailor_2":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "Fogalmam sincs, kapitány. A fregatt a hajnali ködben kihajózott. Az ôrség néhány órával késôbb vette észre a hiányát, amikor a köd megszûnt.";
			link.l1 = "Ez egyszerûen nem lehet! Soha nem tenne ilyet velem! Bár... a fenébe is, nemrég veszekedtünk. Lehet, hogy ô...";
			link.l1.go = "sailor_3";
		break;
		
		case "sailor_3":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "Az ember attól tart, hogy még rosszabb, kapitány. A halászok kora reggel megtalálták a két fiút a legénységbôl. Mindketten halottak, elvágott torokkal.";
			link.l1 = "Kibaszott rémálom! De Chievous! Ellopta a hajóját, amíg én a márkinôvel voltam elfoglalva! Remélem, életben marad... Ha csak egy hajszálnyit is veszít, én...";
			link.l1.go = "sailor_4";
		break;
		
		case "sailor_4":
			dialog.text = "Kiadná a parancsot a fiúknak, hogy készüljenek, kapitány? Két óra múlva kihajózhatunk, egész délelôtt mindenki ideges volt, különösen a másodparancsnoka, alig tudtuk megakadályozni, hogy utánuk hajózzon.";
			link.l1 = "Túl korán van még ehhez. Át kell... gondolnom a dolgot, rendesen, és beszélnem kell valakivel. Igen, uram. Készítsék elô a hajót! Mindenki álljon készen, amint visszatérek, indulunk.";
			link.l1.go = "sailor_5";
		break;
		
		case "sailor_5":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 10.0);
			GoldenGirl_GirlPrisoner();
		break;
		
		case "off_brothel":
			dialog.text = "De Maure kapitány, mi folyik itt? Valaki megtámadta a hölgyet?";
			link.l1 = "Nem kellett volna idejönnie. Nos, Isten a tanúm, nem akartam ezt.";
			link.l1.go = "off_brothel_1";
		break;
		
		case "off_brothel_1":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_group_Delete("EnemyFight");
			for (i=1; i<=4; i++)
			{
				sld = characterFromId("GG_PatrolBrl_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "GoldenGirl_BrothelAfterFight");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "Cap_Nayad":
			dialog.text = "Monseniour, már majdnem elvesztettük a reményt, hogy itt leszel. Látom Botot márkinét a hosszúhajójában. Meg sem kérdezem, hogy történt. A társa már várja önt. Biztonságban van, vigye magával és tûnjön el innen.";
			link.l1 = "Ha egy ujjal is hozzáérsz, darabokra tépem a vén kádadat!";
			link.l1.go = "Cap_Nayad_1";
		break;
		
		case "Cap_Nayad_1":
			dialog.text = "Micsoda váratlan gondoskodó magatartás. Ne aggódjon, úgy tartották fogva, mint egy fogoly királynôt. A fenyegetéseid nem érdekelnek engem. Egyébként Chevalier de Chievous üdvözletét küldi.";
			link.l1 = "Csessze meg ôt és az üdvözletét. Hol van az én... tisztem? Kezdjük a cserét.";
			link.l1.go = "Cap_Nayad_2";
		break;
		
		case "Cap_Nayad_2":
			DialogExit();
			DoQuestReloadToLocation("Shore27", "goto", "goto13", "GoldenGirl_DominicaAlarmFinal");
		break;
		
		case "Cap_Nayad_3":
			dialog.text = "Monseniour, már majdnem elvesztettük a reményt, hogy itt leszel. A társa már várja önt. Biztonságban van... várjon, ki a fene ez? Hol van a márkinô?";
			link.l1 = "";
			link.l1.go = "Cap_Nayad_4";
		break;
		
		case "Cap_Nayad_4":
			DialogExit();
			LAi_SetActorType(npchar);
			chrDisableReloadToLocation = true;
			GoldenGirl_CortnySetOnDeck();
		break;
		
		case "antigua_officer":
			dialog.text = "A kardja, uram. És semmi tréfa, a fiúk mostanában kissé idegesek. Nem akarsz golyót kapni, ugye?";
			link.l1 = "Komolyan mondod? Rendben, vedd el, de légy óvatos, többe kerül, mint a laktanyád. Találkozót követelek Cortney báróval, excellenciás uram!";
			link.l1.go = "antigua_officer_1";
		break;
		
		case "antigua_officer_1":
			dialog.text = "Ne aggódjon, biztos vagyok benne, hogy talál majd idôt arra, hogy meglátogassa önt.";
			link.l1 = "Amikor segíteni próbálsz valakinek...";
			link.l1.go = "antigua_officer_2";
		break;
		
		case "antigua_officer_2":
			DialogExit();
			chrDisableReloadToLocation = false;
			DoFunctionReloadToLocation("SentJons_prison", "goto", "goto9", "");
			WaitDate("", 0, 0, 1, 0, 10); //крутим время
			RecalculateJumpTable();
			RemoveCharacterEquip(pchar, BLADE_ITEM_TYPE);
			RemoveCharacterEquip(pchar, GUN_ITEM_TYPE);
			RemoveCharacterEquip(pchar, MUSKET_ITEM_TYPE);
			RemoveCharacterEquip(pchar, CIRASS_ITEM_TYPE);
			sld = characterFromId("Cortny");
			sld.dialog.currentnode = "Cortny_45"; 
			LAi_SetActorTypeNoGroup(sld);
			ChangeCharacterAddressGroup(sld, "SentJons_prison", "goto", "goto13");
			DoQuestFunctionDelay("GoldenGirl_CortnyInJail", 10.0);
			bDisableCharacterMenu = true;//лочим F2
		break;
		
		case "baster_officer":
			dialog.text = "Ez sem tetszik nekem, Monseniour. Sajnos, ennek a szemtelen britnek olyan tekintélye van, hogy még Monseniour de Lyon sem tehet ellene sokat. Elnézést kérek, kapitány, adja át a kardját, kérem.";
			link.l1 = "Remélem, Monseniour de Chievous nem fog velem egy cellában lakni. Menjünk, uraim, hullafáradt vagyok. Végre egy kis alvás.";
			link.l1.go = "baster_officer_1";
		break;
		
		case "baster_officer_1":
			DialogExit();
			chrDisableReloadToLocation = false;
			DoFunctionReloadToLocation("Baster_prison", "goto", "goto9", "");
			WaitDate("", 0, 0, 2, 0, 10); //крутим время
			RecalculateJumpTable();
			sld = characterFromId("Cortny");
			sld.lifeday = 0; // Captain Beltrop, убираем Кортни
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_136"; 
			LAi_SetActorTypeNoGroup(sld);
			ChangeCharacterAddressGroup(sld, "Baster_prison", "goto", "goto13");
			DoQuestFunctionDelay("GoldenGirl_JuliannaInJail", 7.0);
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sTemp = sld.name;
			AddQuestRecord("GoldenGirl", "24");
			AddQuestUserData("GoldenGirl", "sName", sTemp);
		break;
		
		case "statist_1":
			dialog.text = "Nem akarok udvariatlan lenni, uram, de most nincs idôm beszélgetni, látja, mi folyik itt. Nem akarok lemaradni semmirôl!";
			link.l1 = "Ahogy óhajtja, uram.";
			link.l1.go = "statist_1a";
		break;
		
		case "statist_1_1":
			dialog.text = "Ez az este be fog vonulni a történelembe, érzem! Az emberek Versailles-ig beszélni fognak róla! Az én Marianne-om el lesz ragadtatva, és minden részletet tudni akar majd. Kérem, uram, lépjen félre, elállja a kilátást.";
			link.l1 = "Már megyek is, uram, élvezze a mûsort, és üdvözölje a felejthetetlen Marianne-t... bárki is legyen az.";
			link.l1.go = "statist_1a";
		break;
		
		case "statist_1a":
			DialogExit();
			npchar.dialog.currentnode = "statist_1_1"; 
		break;
		
		case "statist_2":
			dialog.text = "Hah! Szóval, itt van Monsieur de Maure! Elnézést... Charles de Maure kapitány! Kérem, csatlakozzon hozzám, itt van egy csodálatos borválogatás a jó öreg világból. Mivel szeretné kezdeni az estét: van egy újdonság - Cabernet Sauvignon a mi szeretett Gironde partjairól, vagy elhalványuló klasszikus - olasz Sangiovese?";
			link.l1 = "Köszönöm, monsieur, iszom önnel, de egy kicsit késôbb.";
			link.l1.go = "statist_2a";
		break;
		
		case "statist_2_1":
			dialog.text = "Ó, de Maure kapitány! Szeretne még egy kis bort... hick? Nézze meg, mit szolgáltak fel nekünk az imént - 1643-as évjáratú Syrah-t, éppen a Rhone-völgy északi dombjairól. Ez, a fenébe is, egy igazi gyöngyszem! És az évjárat minden szempontból kiváló volt, mondom nektek... egy vereség a spanyoloktól a Gat-foknál megérte! Egyébként ... tudjátok, miért csinál mindenki ilyen nagy hûhót? Valaki rosszul érzi magát? Hát - mindegy, egészségedre...";
			link.l1 = "Legalább valaki tiszteleg a csemegék elôtt. Au Revoir, Monsieur.";
			link.l1.go = "statist_2a";
		break;
		
		case "statist_2a":
			DialogExit();
			npchar.dialog.currentnode = "statist_2_1"; 
		break;
		
		case "statist_3":
			dialog.text = "Ó, Charles de Maure kapitány, hallottam önrôl, mint mindenki más ebben a városban! hadd mutatkozzam be - "+GetFullName(npchar)+", nagy megtiszteltetés önnel találkozni, higgye el! Tényleg jóban van a kormányzóval? Be tudna mutatni minket egymásnak? Szeretném kifejezni a legmélyebb tiszteletemet neki és...";
			link.l1 = "Talán késôbb. Jó estét, uram.";
			link.l1.go = "statist_3a";
		break;
		
		case "statist_3_1":
			dialog.text = "Monsieur de Maure, látta ezt?! Nagyrabecsült kormányzónk és maga Monsieur de Chievous - azt hittem, hogy itt megölik egymást! Nagyszerû! Botot márki ma felülmúlta önmagát - ez az egész olyan átkozottul izgalmas! Türelmetlenül várom a folytatást. Egyébként talán most jött el a megfelelô pillanat? Megígérte, hogy bemutat... ";
			link.l1 = "Nem emlékszem, hogy bármit is ígértem volna. Sajnálom, de mennem kell.";
			link.l1.go = "statist_3a";
		break;
		
		case "statist_3a":
			DialogExit();
			npchar.dialog.currentnode = "statist_3_1"; 
		break;
		
		case "statist_4":
			dialog.text = "Monsieur de Maure, végre eljutott a zseniális madame Botot szalonjába! Már többször híresztelte, hogy látni akarja önt. Sikerült felmérnie a 'pupilláit'? Igen, az olyan sztárok, mint a márkinô, nem az olyan egyszerû halandóknak valók, mint ön és én. De hidd el: ezek a hölgyek igazi mûalkotások. Talán kevésbé lenyûgözôek, de mégis - mint Michelangelo és mondjuk Tiziano.";
			link.l1 = "Érdekes összehasonlítás, monsieur. Nos, hagyom, hogy élvezze az éjszakát....";
			link.l1.go = "statist_4a";
		break;
		
		case "statist_4_1":
			dialog.text = "Nem, itt mindig vicces, de most egyértelmûen luxusbotrányszagú a levegô, érzi? Lady Jacqueline vár rám odafent, de még mindig nem tudok elszakadni a játékasztaloktól! Ôlordsága és monsieur de Chievous méltó ellenfelek, és rendkívül elszántak. Úgy tûnik, hogy a fogadások ma nem csak a csillagokig repülnek, hanem egyenesen az ördögökig meg fogják törni az égboltot!";
			link.l1 = "Az ördögök lent vannak, monsieur. Az égboltozat mögött angyaloknak kell lenniük.";
			link.l1.go = "statist_4a";
		break;
		
		case "statist_4a":
			DialogExit();
			npchar.dialog.currentnode = "statist_4_1"; 
		break;
		
		case "statist_5":
			dialog.text = "Nos, legalább egy szép találkozás! Már találkoztunk, de Maure kapitány, de aligha emlékszik rá. "+GetFullName(npchar)+" - A helyôrség hatodik gyalogos századának kapitánya voltam, önnel együtt harcoltam az utcáinkon a spanyolokkal. Igaz, kaptam egy golyót a térdembe, és a csata nagy részében azt csodáltam, ahogy ugyanez a bordélyház ég, míg én az árokban feküdtem. Most itt - megint egy civil, és megint csodálom, de most már belülrôl.";
			link.l1 = "Örülök, hogy megismerhetem, monsieur. Aznap nagyon meleg volt, de bevallom, azóta ez a hely lényegesen szebb lett!";
			link.l1.go = "statist_5a";
		break;
		
		case "statist_5_1":
			dialog.text = "És hogy tetszik az itteni hangulat, kapitány úr? Úgy tûnik, hogy ezek a világiak úgy döntöttek, hogy egy istenverte rendetlenséget csinálnak! Érdekes, lehet a kormányzói széket úgy játszani, mint a kártyában a fogadást? Ne feledje a szavamat - acéllal fog végzôdni. Kár, hogy a térdemmel az ilyen szórakozások már nem nekem valók. Azonban valahol láttam Jacqueline-t - az ô úriemberét komolyan szenvedélyesen érdekli, ami történik... Azt hiszem, megyek és szerencsét próbálok, amíg itt még minden nyugodt.";
			link.l1 = "Jó döntés, sok sikert kívánok, monsieur. Nekem pedig vissza kell mennem a... wallies-hez.";
			link.l1.go = "statist_5a";
		break;
		
		case "statist_5a":
			DialogExit();
			npchar.dialog.currentnode = "statist_5_1"; 
		break;
	}
} 
