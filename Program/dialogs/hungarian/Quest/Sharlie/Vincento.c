// отец Винсенто
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "santiago")
			{
				dialog.text = "Végre élôben látom a híres francia kapitányt "+GetFullName(pchar)+" . Sokat hallottam a hôstetteidrôl. Ön bátor katona, és remélem, hogy anyánk, a Szent Római Katolikus Egyház hûséges és hûséges fia. Ülj le, fiam. Miattam nem kell felállnod. Dominus vobiscum! ";
				link.l1 = "Et cum spiritu tuo, excellenciád. Hosszú és fáradságos volt az utam ide... Per aspera ad astra és minden...";
				link.l1.go = "utensil";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "twoitems" && !CheckAttribute(npchar, "quest.skinmap"))
			{
				dialog.text = "Igen, látom a szemedben, hogy híreid vannak számomra. Teljes figyelmem az öné.";
				link.l1 = "Méltóságos uram, megtaláltam az eltûnt titkárát...";
				link.l1.go = "guardoftruth";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth.Trinidad") && pchar.questTemp.Guardoftruth.Trinidad == "mayak")
			{
				dialog.text = "Híreket hoztál nekem San Joséból, fiam?";
				link.l1 = "Igen, excellenciás uram. Megállapítottam, mi történt közös ismerôsünkkel, Miguel Dichosoval és az elveszett fregattjával. Amint hajója Spanyolország felé tartva belépett az Atlanti-óceánba, azonnal ellenszélbe került, és visszasodródott a Karib-tengerre.";
				link.l1.go = "guardoftruth_10";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth.Archy") && pchar.questTemp.Guardoftruth.Archy == "begin")
			{
				dialog.text = "Pax vobiscum, fiam... Mit tehetek érted?";
				link.l1 = TimeGreeting()+", Excellenciád. Van valami hír a megállapodásunkkal kapcsolatban?"
				link.l1.go = "guardoftruth_17";
				break;
			}
			dialog.text = "Akarsz valamit, fiam?";
			link.l1 = "Nem, semmit, atyám.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "utensil":
			dialog.text = "'Menjetek be a szoros kapun; mert tágas a kapu és széles az út, amely a veszedelemre vezet, és sokan vannak, akik azon bemennek. Mert keskeny a kapu és nehéz az út, amely az életre vezet, és kevesen vannak, akik megtalálják.' Az igazság útja mindig nehéz, fiam. De az elért cél teljes mértékben megjutalmazza az igaz embert a tetteiért.";
			link.l1 = "Egyetértek, excellenciás uram. Elvégeztem az Ön által elém állított feladatokat. A gyáva kalóz, aki ellopta az értékes edényeket az Egyháztól, már a tiéd. Most visszaadom mindazt, amit elvittek: az ostensort, a keresztet és a füstölôt. Vigyétek ôket a santiagói plébániára.";
			link.l1.go = "utensil_1";
		break;
		
		case "utensil_1":
			RemoveItems(pchar, "jewelry33", 1);
			RemoveItems(pchar, "jewelry34", 1);
			RemoveItems(pchar, "jewelry35", 1);
			dialog.text = "Benedicite! Szívbôl köszönöm a Szûzanya Egyház és a Santiago plébánia iránti hûséges szolgálatodat, fiam. Munkáid nem maradnak jutalom nélkül. A plébánia hívei adományt gyûjtöttek a bátor harcosnak, aki visszaadta az ellopott tárgyakat, és én szívesen átadom neked a nevükben. 'A munkás méltó a bérére.'";
			link.l1 = "Köszönöm, excellenciás uram. Micsoda kellemes meglepetés!";
			link.l1.go = "utensil_2";
		break;
		
		case "utensil_2":
			GiveItem2Character(pchar, "chest");
			Log_Info("Kaptál egy láda dublont.");
			PlaySound("interface\important_item.wav");
			dialog.text = "Az Anyaszentegyház hûséges szolgálata mindig hûségesen meg van jutalmazva, "+pchar.name+". A magam részérôl remélem, hogy továbbra is elkötelezett harcos maradsz a kereszténység védelmében és védelmében, mert halálos fenyegetés lebeg felettünk, mint a mitikus Damoklész kardja.";
			link.l1 = "Mi lehet az, excellenciás uram?";
			link.l1.go = "utensil_3";
		break;
		
		case "utensil_3":
			dialog.text = "Talán arra rendeltettél, hogy bajnokunk legyél a világ sötét erôi és fejedelemségei elleni közelgô csatában, fiam, mert sok jel és elôjel utal arra, hogy valami gonosz közeledik.";
			link.l1 = "Jelek és elôjelek?";
			link.l1.go = "utensil_4";
		break;
		
		case "utensil_4":
			dialog.text = "Sok, fiam... Az egyik ilyen jel a te vágyad, hogy a pogány Tayasal elveszett indiai aranyát keresd, mert ami az ô tárházukban ôrzôdik, az pontosan az, ami veszélyt jelent az egész keresztény világra.";
			link.l1 = "Felvilágosítana egy kicsit errôl az aranyról, tisztelendô atyám? Az eltûnésének történetérôl már hallottam, de miféle veszélyrôl beszél?";
			link.l1.go = "utensil_5";
		break;
		
		case "utensil_5":
			dialog.text = "Figyelj jól, fiam, és tudd, hogy mindaz, amit most hallani fogsz, csak a te fülednek szól. Jóval azelôtt, hogy Miguel Dichoso elhozta volna azt a pogány kincset az ôsi indiánvárosból, az Itza indiánok egy foglyul ejtett emberét kérdezgettem a karibi küldetésünkrôl. Az Itza népe a maják leszármazottai, egy hatalmas birodalomé, amely évszázadokkal azelôtt elveszett, hogy még Cristobal Colon és emberei elôször tették volna be a lábukat az Újvilágba. A maja birodalom vasököllel uralkodott a környezô törzseken, és kimondhatatlan hatalmat kapott a démonokkal való pokoli alkuk révén. Sötét varázslatok, melyeket nemzedékek emberáldozatainak vérével vásároltak meg. \nEz az itzai férfi tudott Tayasalról, egy elveszett maja városról és a benne még mindig elzárt hihetetlen gonoszságról. Mindent elmondott nekünk, amit tudott. Ha ezeket a pecséteket felnyitják, a következmények apokaliptikusak lennének. Attól a pillanattól kezdve mindent megtettem, hogy megakadályozzam ennek a szörnyû gonoszságnak a felébredését. Kétségbeesetten írtam az Escorialnak és Rómának, hogy segítséget kérjek.\nAzok meghallgattak, és elküldték Don Ramon de Mendoza y Riba-t, aki Providence-ben alakította ki bázisát, és Tayasal keresésére indult. Ekkor derült ki, hogy a jó Don Mendosának... más motivációi voltak az elveszett város megtalálására. Ahelyett, hogy megakadályozta volna a világvégét, inkább a Mammont akarta szolgálni, mint Krisztust.\nEzért Isten elhagyta ôt, és a halál angyalát küldte a táborába. Minden cselekedete hiábavaló volt, és csak a spanyol katonák és a hûséges indián megtérôk értelmetlen halálához vezetett. Írtam az Escorialnak, hogy rangbeli alkalmatlanság miatt kérjem Ramon de Mendoza felmentését, és beleegyeztek, hogy felmentik a szolgálat alól, de...";
			link.l1 = "Miguel Dichoso megérkezett.";
			link.l1.go = "utensil_6";
		break;
		
		case "utensil_6":
			if (CheckAttribute(pchar, "questTemp.Dolly")) sTemp = "Kukulcan?! Sancta Maria, Mater Dei, ora pro nobis! Kukulcan megint, az a vén kígyó...";
			else sTemp = "Hm...";
			dialog.text = "Pontosan. Az ördög küldte kalandor megtalálta Tayasalt az ôsi maják kincseivel együtt. Don Mendosa öröme azonban rövid ideig tartott. Mindezek a kincsek eltûntek Dichosóval együtt, útban vissza Spanyolországba. Valószínû, hogy az aranyrudakkal és díszekkel együtt Miguel magával vitte az ördögiség egy ôsi forrását, egy Kukulcan nevû ôsi maja démonisten rémisztô maszkját is.";
			link.l1 = sTemp+"De milyen gonoszságról beszél, excellenciás uram? Honnan tud róla?";
			link.l1.go = "utensil_7";
		break;
		
		case "utensil_7":
			dialog.text = "Ez egy olyan gonoszság, amely a Karib-tenger, az Újvilág és talán az Óvilág minden megkeresztelt keresztényének halálát hozza. A vég úgy jön majd, mint tolvaj az éjszakában, és senki sem fogja észrevenni, hogy mi történt. És ennek elôjelei már most is mindenütt vannak!";
			link.l1 = "Milyen elôjelek? Nem értem...";
			link.l1.go = "utensil_8";
		break;
		
		case "utensil_8":
			dialog.text = "Fiam, tényleg olyan vak vagy, hogy észre sem veszed ôket? Huszonöt éve történnek, szinte megállás nélkül!";
			link.l1 = "Szelíden megemlíteném, méltóságos uram, hogy életem folyamata pontosan ennyi idôre van felsorolva, nem is beszélve arról, hogy életem nagy részét Európában éltem le. Tudatlanságomért némileg elnézést kell kérni.";
			link.l1.go = "utensil_9";
		break;
		
		case "utensil_9":
			dialog.text = "Értem, "+pchar.name+". Nos, nem vetted észre, hogy furcsa dolgok történtek a Karib-térségben, amint megérkeztél ide Európából? Nem találod furcsának, hogy a boszorkányság, a fekete mágia és más rituálék sokkal nagyobb erôvel bírnak itt, mint odahaza? Az indiai sámánok által elvarázsolt pogány amulettek olyan valódi erôvel rendelkeznek, amelyet bármely ember megtapasztalhat, ha csak a kezében tartja ôket.\nMég a mi keresztény alkimistáink is - Isten ébressze rá ôket, hogy belássák a tévedésüket! - elsajátították a varázslatos tárgyak készítésének mûvészetét. Nem veszik észre, hogy ezzel magát az ördögöt szolgálják. Nem érzed valami pokoli természetellenes jelenlétét, ami a perifériás látókörödön kívül leselkedik rád?";
			link.l1 = "Igazad van, atyám. Elôször meg is lepôdtem rajta, de mostanra azt hiszem, már megszoktam... Végül is ez az Új Világ!";
			link.l1.go = "utensil_10";
		break;
		
		case "utensil_10":
			dialog.text = "De ez nem volt mindig így. A sötétség, amirôl beszélek, körülbelül huszonöt évvel ezelôtt érkezett ide, és napról napra egyre nagyobb hatalmat nyer. Ez csak egy dolgot jelent: 'it' már eljött, 'it' már köztünk van, és 'it' munkában van...";
			link.l1 = "Kikrôl beszélsz? Ki ez a titokzatos 'it'?";
			link.l1.go = "utensil_11";
		break;
		
		case "utensil_11":
			dialog.text = "A keresztények esküdt ellensége, aki az Egyház és az egész kereszténység elpusztítására törekszik.";
			link.l1 = "...Az Antikrisztusról beszélsz?";
			link.l1.go = "utensil_12";
		break;
		
		case "utensil_12":
			dialog.text = "Hogy ez 'a' Antikrisztus vagy csak 'an' antikrisztus, nem merem megmondani. Nem számít, milyen nevet visel ez a fenevad, amikor halandó testbe öltözik, Megváltónk megtestesülésének groteszk paródiájaként. Ami fontos, az az, hogy mit fog tenni. Azért vagyok itt, hogy megállítsam, és ti segíteni fogtok nekem. De egy kicsit elragadtattuk magunkat. Ön a tettek embere. Valószínûleg szívesebben térne a tárgyra, és kihagyná a teológiát, igaz?";
			link.l1 = "Éppen ellenkezôleg, sok új és fontos dolgot tudtam meg Öntôl, excellenciás uram. Kész vagyok tovább hallgatni.";
			link.l1.go = "utensil_13";
		break;
		
		case "utensil_13":
			dialog.text = "Udvarias és jól nevelt vagy, fiam. Az jó. Most pedig térjünk vissza az észhez, amiért tanácskoztál velem. A közös célunk, hogy megtaláljuk a Dichoso által elrabolt Tayasal kincseit. Valószínûleg találunk majd egy fegyvert a kincsek között, amit felhasználhatunk az Ördög elleni közelgô csatában.";
			link.l1 = "De lehet, hogy Dichoso már elhagyta a Karib-térséget, és egy halom aranyon ül Spanyolországban?";
			link.l1.go = "utensil_14";
		break;
		
		case "utensil_14":
			dialog.text = "Nem. Bizonyítékom van rá, hogy ezek a kincsek még mindig itt vannak a Karib-tengeren. Még nem kell tudnia a forrásaimról, bíznia kell bennem. Emellett úgy gondolom, hogy Dichoso hazudott a bárónak.\nA Tayasal romjairól szóló története nem egyezik azzal, amit az Itza indián mondott nekem a kihallgatáson. Arról nem is beszélve, hogy az, hogy Dichoso volt az egyetlen túlélôje a Mosquito rajtaütésének, egy kicsit túl kényelmes volt.";
			link.l1 = "Gondolom, Don Mendosa is ezt hiszi, hiszen ô is rajtaütött Saint-Pierre-ben, hogy megtalálja Dichosót?";
			link.l1.go = "utensil_15";
		break;
		
		case "utensil_15":
			dialog.text = "A báró tettei nem tartoznak rád, fiam. Ôt csak az arany és a személyes nyereségvágy motiválja. Kapzsisága malomkô lesz a nyakán, miközben körülötte jó keresztény férfiak és nôk harcolnak a pokol erôivel.";
			link.l1 = "Van valami ötleted, hogy hol keressük Dichosót és a kincset?";
			link.l1.go = "utensil_16";
		break;
		
		case "utensil_16":
			dialog.text = "Minden percben gondolok rá, fiam, de semmi konkrétumot nem tudok mondani. De van itt egy ember, aki segíteni fog nekünk, egy genovai természetfilozófus. Azért hoztam ôt magammal, hogy segítsen kategorizálni az Újvilág olyan dolgait, amelyek hasznosak lehetnek az Egyház missziója számára. Tanúja volt az itzai indián kihallgatásának, és legjobb megítélésem szerint a hallott dolgok megdöbbentették és perverz módon vonzották.\nAz ördög úgy használta kíváncsiságát, mint egy csalizott farkashorgot, és megszállta ôt, testét és lelkét. Az Úr nagyszerû képességekkel ruházta fel az orvoslás és az alkímia terén, de a mi genovai emberünk a fekete mágia és a varázslás kísértésébe esett. Többször is beszélt a foglyul ejtett Itzával az engedélyem nélkül, majd eltûnt. Meg kell találnunk ôt, és meg kell mentenünk a lelkét.";
			link.l1 = "Gondolom, nekem kell megtalálnom ôt?";
			link.l1.go = "utensil_17";
		break;
		
		case "utensil_17":
			dialog.text = "Igen, fiam. Ô az elsô lépés a kincs és a fegyver megtalálásához, amelyet a minket fenyegetô gonosz erôk ellen használhatunk.";
			link.l1 = "Ki ez a genovai?";
			link.l1.go = "utensil_18";
		break;
		
		case "utensil_18":
			dialog.text = "A neve Gino Gvineili. Harminc éves, plusz-mínusz pár év. Tehetséges orvos és alkimista. Mint mondtam, most a fekete mágiát tanulmányozza. Legjobb értesüléseim szerint valahol a karibi angol gyarmatok között bujkál.\nKeresd meg Gino Gvineilit, fiam. Ha sikerült megtalálnod azt a kalózt, aki ellopta a templomi hajóinkat, akkor azt is sikerülni fog, hogy megtaláld az elszökött titkáromat, és idehozd. Szent Antal közbenjárásáért fogok imádkozni érted.";
			link.l1 = "Értem, excellenciás uram. Nem vesztegetek el több idôt. Viszlát késôbb!";
			link.l1.go = "utensil_19";
		break;
		
		case "utensil_19":
			DialogExit();
			AddQuestRecord("Guardoftruth", "35");
			bool bOk = (pchar.questTemp.HWIC.Detector == "holl_win") || (pchar.questTemp.HWIC.Detector == "eng_win") || (pchar.questTemp.HWIC.Detector == "self_win");
			if (CheckAttribute(pchar, "questTemp.HWIC.Detector") && bOk)
			{
				pchar.questTemp.Guardoftruth = "jino";
				AddQuestUserData("Guardoftruth", "sText", "Majdnem elárultam magam a meglepetéstôl felkiáltással. Vincento atya megparancsolta, hogy találjam meg és hozzam el neki szökött titkárát, egy Gino Gvineili nevû orvos-alkimistát. Ugyanaz a Gino, aki a Szent János-házam második emeletén lévô szabad szobát lakja!");
			}
			else
			{
				pchar.questTemp.Guardoftruth = "merdok";
				AddQuestUserData("Guardoftruth", "sText", "Meg kell találnom egy Gino Gvineili nevû embert, aki valahol az angol karibi gyarmatokon bujkál. Orvos és alkimista. Hol bujkálhat egy ilyen ember?");
			}
		break;
		
		case "guardoftruth":
			dialog.text = "Teljesen bíztam benne, hogy ezt fogod mondani, "+pchar.name+". Most a hitemet tovább erôsíti a bizonyosságom, hogy Önt maga az isteni Gondviselés küldte hozzám. Hol van az én nyomorult, tékozló fiam?";
			link.l1 = "Attól tartok, nem fog tetszeni, amit most hallani fogsz, de nincs más választásom. A titkárnôje meghalt.";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "Isten mentse meg a lelkét és bocsássa meg neki bûneit... Hogy történt, fiam?";
			link.l1 = "Megtaláltam Ginót Antiguán. Ott bujkált az egyik régi épületben, amit a laboratórium alatt építettek. Nem volt hajlandó csendben velem tartani. Miután meghallotta a nevedet, és látta, hogy kész vagyok erôszakot alkalmazni, hosszú ruhája redôi közül elôvett valami fiola tiszta folyadékot, és egy pillanat alatt kiitta...";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "";
			link.l1 = "És ekkor valami szörnyûség történt: elvörösödött, majd sötétkék lett. Görcsösen rángatózva a földre zuhant, és egy perc múlva szörnyû fájdalmak között meghalt. Erôs mandulaillat töltötte be a szobát.";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "Gino... Szegény bolond... Még élete utolsó percét is bûnben töltötte, öngyilkosságot követett el. Micsoda tragikus veszteség. Imádkozni fogok a lelkéért...";
			link.l1 = "Miután meghalt, átkutattam a lakását, és ezt a fóliót találtam ott. Lehet, hogy érdekelheti önöket, vagy talán segíthet nekünk a keresésben? Van itt néhány furcsa és ezoterikus feljegyzés...";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			RemoveItems(pchar, "Almanac", 1);
			Log_Info("Odaadtad az almanachot");
			PlaySound("interface\important_item.wav");
			dialog.text = "Ez szegény Gino almanachja. Minden felfedezésérôl feljegyzéseket írt bele. Add ide, fiam, tanulmányozni fogom, ami benne van. Talán találunk egy nyomot.\nNoha nem adtad vissza nekem Gino Gvineilit, elégedett vagyok az erôfeszítéseiddel, fiam. Most pedig van néhány hírem a számodra.";
			link.l1 = "A figyelmemet felkeltetted, atyám.";
			link.l1.go = "guardoftruth_5";
		break;
		
		case "guardoftruth_5":
			dialog.text = "Információim szerint Trinidad szigete volt az utolsó hely, ahol Dichoso fregattját látták. Egy hozzávetôleges idôpontot is tudok - 1654. április eleje.\nMenj el Trinidadra, és próbálj meg megtudni bármit a fregatt sorsáról: merre tartott, milyen tervei voltak a kapitánynak, bármit, amit csak találsz. Megértem, hogy hosszú idô telt el, és az emberek memóriája korlátozott, de egy fuldokló ember a szalmaszálakba kapaszkodik.";
			link.l1 = "Mindent megteszek, ami tôlem telik.";
			link.l1.go = "guardoftruth_6";
		break;
		
		case "guardoftruth_6":
			dialog.text = "Hadd lássam a levelét a biztonságos átkelésrôl. Hozzáteszem, hogy engedélyezem, hogy meglátogassa a San Jose kolóniát.";
			link.l1 = "Tessék.";
			link.l1.go = "guardoftruth_6a";
		break;
		
		case "guardoftruth_6a":
			RemoveItems(pchar, "VerifyPaper", 1);
			dialog.text = "Ennyi... ez minden. Ne felejtse el kitûzni a spanyol zászlót a hajójára. Lépj elôre és fogadd Isten áldását, fiam!";
			link.l1 = "Egy pillanat, felség. Feltehetek egy kérdést?";
			link.l1.go = "guardoftruth_7";
		break;
		
		case "guardoftruth_7":
			dialog.text = "Igen, természetesen. Mit szeretne tudni?";
			link.l1 = "A legutóbbi találkozásunkkor egy itza indiánról beszéltél, aki tájékoztatott téged Tayasalról. Sokat gondolkodtam rajta... Mondja csak, volt valamije az illetônek? Valamiféle tárgyak, írások, vagy bármi ilyesmi? Ez még hasznosnak bizonyulhat.";
			link.l1.go = "guardoftruth_8";
		break;
		
		case "guardoftruth_8":
			dialog.text = "Semmi különlegeset, fiam. Egy ágyékkötô, primitív ékszerek, egy bambuszpipa néhány gyógynövénnyel, és egy durva bôrdarab, amit szájpecekként használtak.\nMindezeket Don Ramon de Mendoza y Ribának küldték. De biztosíthatom önöket, hogy semmi érdekeset nem találtak.";
			link.l1 = "Értem. Köszönöm, atyám. A következô alkalomig!";
			link.l1.go = "guardoftruth_9";
		break;
		
		case "guardoftruth_9":
			DialogExit();
			GiveItem2Character(pchar, "VerifyPaper");
			ChangeItemDescribe("VerifyPaper", "itmdescr_VincentoPaper_A");
			AddQuestRecord("Guardoftruth", "38");
			npchar.quest.skinmap = "true";
			pchar.questTemp.Guardoftruth.Trinidad = "begin";
		break;
		
		case "guardoftruth_10":
			dialog.text = "A Mindenható áldjon meg és tartson meg téged... Mi történt végül Miguel Dichosóval? Megtudta?";
			link.l1 = "Sajnos nem. Az utolsó dolog, amit a szemtanúk elmondhattak nekem, az volt, hogy a Santa Quiteria-t az orkán erejû szél Martinique irányába vitte. Nem tudni biztosan, hogy a hajó megmenekült-e vagy elpusztult. De van egy olyan gyanúm, hogy Miguel Dichoso élve megúszta.";
			link.l1.go = "guardoftruth_11";
		break;
		
		case "guardoftruth_11":
			dialog.text = "Miért döntöttél így, fiam?";
			link.l1 = "A kulcs az, hogy a fregatt valahol Martinique irányában rejtôzött. És nemrég egy Diego de Montoya nevû gáláns caballero, aki maga is Don Ramon de Mendosa emberei közé tartozott, megtámadta Saint-Pierre-t azzal a céllal, hogy megtalálja Miguel Dichosót, aki állítólag ott bujkált.";
			link.l1.go = "guardoftruth_12";
		break;
		
		case "guardoftruth_12":
			dialog.text = "A báró úgy véli, Dichoso a franciáknál bujkált...";
			link.l1 = "Jól ismerem Saint-Pierre-t és Jacques Dyel du Parquet kormányzót, excellenciás uram. Senki sem ismerte ott a Miguel Dichoso nevû spanyol férfit. Meg tudná mondani, hogyan találom meg Diego de Montoyát? Szeretnék beszélni vele Dichoso-ról.";
			link.l1.go = "guardoftruth_13";
		break;
		
		case "guardoftruth_13":
			dialog.text = "Biztos, hogy hajlandó lenne beszélni veled, fiam? Nem hiszem, hogy hajlandó lenne, hacsak nem karddal és pisztollyal beszélgetsz.";
			link.l1 = "Lehet, hogy a neved talán jobb belátásra bírná?";
			link.l1.go = "guardoftruth_14";
		break;
		
		case "guardoftruth_14":
			dialog.text = "Ó, "+pchar.name+". Kétlem, hogy Don Mendosa esküdt embere hajlandó lenne megegyezni veled. Az, hogy parancsot adok neki, hogy érkezzen San Diegóba egy meghallgatásra velem, talán egy lehetôség lenne, de nem vagyok benne biztos, hogy Diego is tökéletesen ôszinte lenne velem.";
			link.l1 = "Milyen lépéseket tegyünk most, atyám?";
			link.l1.go = "guardoftruth_15";
		break;
		
		case "guardoftruth_15":
			dialog.text = "Hagyj magamra egy kis idôre, fiam. Fel kell dolgoznom, amit elmondtál, és össze kell raknom azokat a tényeket is, amelyekrôl már tudom a különbözô forrásaimból. Utána megmondom, mi a következô lépésünk. Ugorj be késôbb.";
			link.l1 = "Igen, felség. Úgy lesz. Rendszeresen ellenôrizni fogom...";
			link.l1.go = "guardoftruth_16";
		break;
		
		case "guardoftruth_16":
			DialogExit();
			AddQuestRecord("Guardoftruth", "43");
			pchar.questTemp.Guardoftruth.Trinidad = "end";
			pchar.quest.GuardOT_setSpaOfficer.win_condition.l1 = "ExitFromLocation";
			pchar.quest.GuardOT_setSpaOfficer.win_condition.l1.location = pchar.location;
			pchar.quest.GuardOT_setSpaOfficer.function = "GuardOT_SetSpaOfficerInTown";
			NextDiag.CurrentNode = "guardoftruth_wait";
		break;
		
		case "guardoftruth_wait":
			dialog.text = "Isten áldjon meg, fiam... Mit tehetek érted?";
			link.l1 = "Van valami híre, excellenciás uram?";
			link.l1.go = "guardoftruth_wait_1";
		break;
		
		case "guardoftruth_wait_1":
			dialog.text = "Jelenleg nincs, fiam. De ne ess kétségbe. Az embereim és én dolgozunk rajta. Ugorj be késôbb.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "guardoftruth_wait";
		break;
		
		case "guardoftruth_17":
			dialog.text = "Igen, fiam. Van néhány információm Miguel Dichosóról. Nem hiába hittem, hogy Dichoso még mindig él és a Karib-tengeren van. Úgy tûnik, Don Diego de Montoyának igaza volt. Bizonyítékot kaptunk egy embertôl, aki ismerte Miguel Dichosót az arcáról, hogy az eltûnt úriembert 1654 áprilisában, a Santa Quiteria eltûnése után látták a Martinique-on lévô Le Francois kalóztelepülésen...";
			link.l1 = "Tehát a fregatt Martinique partjainál süllyedt el?";
			link.l1.go = "guardoftruth_18";
		break;
		
		case "guardoftruth_18":
			dialog.text = "Lassíts, fiam. Jelenleg semmilyen információnk nincs arról, hogy abban az idôben bármilyen hajó is hajótörést szenvedett volna Martinique-on. És egy fregatt nem egy óceánjáró. A pusztulása bizonyára felkeltette volna a figyelmet, és hatalmas mentési lehetôséget teremtett volna a helyi hullarablók számára.";
			link.l1 = "Lehet, hogy érdemes lenne átkutatni a partvonalat és a partokat, hogy megtaláljuk, mi maradt a hajóból?";
			link.l1.go = "guardoftruth_19";
		break;
		
		case "guardoftruth_19":
			dialog.text = "A fiam, Don Diego de Montoya mindezt már megtette, eredménytelenül. Hallgassátok tovább. Providence-i forrásaim szerint a báró biztos benne, hogy a Santa Quiteria még mindig a Karib-tengeren hajózik, bár más néven.\nEzért vadászik olyan kétségbeesetten Miguel Dichosóra. Szavai szerint a Santa Quiteriát nem messze Isla Tesorótól látták, és nemrégiben angol zászló alatt látták egy katonai század kíséretében.";
			link.l1 = "Micsoda? Ez hihetetlen. Azt mondták, hogy egy ilyen méretû viharnak lehetetlen lenne ellenállni... És most a Santa Quiteria nem csak túlélte, de most angol zászló alatt hajózik? A két tény nem illik össze. Miért döntött úgy a báró, hogy a Santa Quiteria volt az? Tényleg olyan különleges hajó?";
			link.l1.go = "guardoftruth_20";
		break;
		
		case "guardoftruth_20":
			dialog.text = "Ó, igen. Ezt a fregattot a legmodernebb európai technikák felhasználásával építették. Az osztályához képest nagyon jól fel van fegyverezve, és a sebessége lehetôvé teszi, hogy lehagyjon bármit, ami túlerôben van. Ezt mondta a forrásom.";
			link.l1 = "És hogy hívják most, ha nem Santa Quiteria?";
			link.l1.go = "guardoftruth_21";
		break;
		
		case "guardoftruth_21":
			dialog.text = "Ezt sajnos nem tudom... Menjetek Isla Tesoróra, "+pchar.name+", és próbáljatok meg megtudni valamit Dichoso fregattjáról. Talán így sikerül megtalálnunk az egykori kapitányát is, két legyet ütünk egy csapásra. Vagy két patkány egy csapdával.";
			link.l1 = "Tekintse úgy, hogy kész, excellenciás uram!";
			link.l1.go = "guardoftruth_22";
		break;
		
		case "guardoftruth_22":
			DialogExit();
			AddQuestRecord("Guardoftruth", "59");
			// проверяем, жив ли Акула и где он, если жив
			if (GetCharacterIndex("Dodson") != -1)
			{
				sld = characterFromId("Dodson");
				if (sld.location == "Pirates_townhall") pchar.questTemp.Guardoftruth.Archy = "islatesoro";
				else pchar.questTemp.Guardoftruth.Archy = "islatesorotavern";
			}
			else pchar.questTemp.Guardoftruth.Archy = "islatesorotavern";
			SetTimerCondition("Map_SetNationCoolHanters", 0, 0, 5, false); // немного развлечений
		break;
		
		case "tieyasal":
			dialog.text = "Örülök, hogy úgy döntöttél, hogy találkozol velem, fiam.";
			link.l1 = "Üdvözlöm, excellenciás uram. Miután találkoztam Don Alonso de Maldonadóval, nem is gondoltam, hogy valaha is újra látlak.";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "Don Alonso de Maldonado megszegte a közvetlen parancsomat. Szigorúan megtiltottam neki, hogy szembeszálljon veled, fiam, tudtam, mi lesz a vége. És amit elôre láttam, valóra vált. Az volt a feladata, hogy Tayasalba kísérjen téged, hiszen már járt ott korábban is.\nAz ô századának és egy század spanyol katonának kellett volna megvédenie téged az Itza vagy a szúnyogok támadása ellen. Alonso méltatlanul cselekedett, önzô bosszúvágytól vezérelve.\nNemcsak a Tayasalba induló expedíciót bukta el, és ítélte halálra a rá bízott katonákat és hajókat, hanem a bizalmatlanság és az ellenem irányuló neheztelés magvait is elültette a szívetekben. Biztosíthatlak, fiam, hogy teljes mértékben a te oldaladon állok. Együtt kell fellépnünk a jelenlegi sötétség ellen.";
			link.l1 = "Szeretném ezt hinni.";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			dialog.text = "Biztos lehet benne, "+pchar.name+". Engem, Urunk és Megváltónk, Jézus Krisztus hûséges és elkötelezett szolgáját és Egyházának képviselôjét egy dolog motivál: hogy megakadályozzam a világvége eljövetelét, amíg minden léleknek esélye nem lesz hallani áldott Urunk szavát. Ez pedig azt jelenti, hogy meg kell állítani az ördögi szer jelenlegi, egy démonoktól megszállt indián kezében nyugvó ügynökét. Ezt rögtön sejtettem, és csak most váltam teljesen bizonyossá. Az Úr kiválasztott téged, mint az Ô bajnokát a Sátán elleni harcban.";
			link.l1 = "De mibôl gondolja ezt, atyám?";
			link.l1.go = "tieyasal_3";
		break;
		
		case "tieyasal_3":
			dialog.text = "Neked sikerült olyasmit elérned, amire sem én nem voltam képes sem én, sem az összes ügynököm segítségével, sem Mendosa báró és Don Diego, sem senki más. Sikerült megtalálnod azt az átkozott szigetet és felkutatnod Kukulcan ereklyéjét rajta. Ugye?";
			link.l1 = "Igen, nálam van Kukulcan maszkja.";
			link.l1.go = "tieyasal_4";
		break;
		
		case "tieyasal_4":
			dialog.text = "És azt állítaná, hogy mindez véletlenül történt? Véletlenül? 'Az ember szíve tervezi az útját, de az Úr határozza meg a lépéseit.' Fiam, a Mindenható vezetett téged erre az útra! Ô erôsítette meg kezedet a harcban, ô irányította lábadat a helyes útra, és ô védett meg a veszély idején! 'Nézd, az Úr kardja ítéletre száll Edomra, arra a népre, amelyet a pusztulásnak szenteltem!'.";
			link.l1 = "Öhm... Atyám, de a küldetés lényegében már teljesült. Nálam van a maszk. Ez nem azt jelenti, hogy Kukulcan megszállt páncélja nem tud belépni a történelmünkbe és megváltoztatni azt...?";
			link.l1.go = "tieyasal_5";
		break;
		
		case "tieyasal_5":
			dialog.text = "Tévedsz, fiam. A démon átléphet azon a kapun, függetlenül attól, hogy nála van-e ez a maszk vagy sem. A maszk csak megkönnyíti számára, hogy véghezvigye sötét tetteit. Az egyetlen dolog, ami megállíthatja ôt, az a pokol kapujának teljes elpusztítása.";
			link.l1 = "Don Alonso ugyanezt mondta nekem...";
			link.l1.go = "tieyasal_6";
		break;
		
		case "tieyasal_6":
			dialog.text = "És igaza volt! Urunk Jézus Krisztus és az Ô Boldogasszonya nevében arra hívlak, hogy vedd fel a keresztet a gonosz ellen, fiam! Nem utasíthatod vissza a rád bízott nagy feladatot. Én és az egész kereszténység tôled függ, fiam.";
			link.l1 = "Excellenciás uram, ez túl sok. Tényleg úgy érzem... mintha... kényelmetlenül érezném magam...";
			link.l1.go = "tieyasal_7";
		break;
		
		case "tieyasal_7":
			dialog.text = "A szerénységed jól áll neked, fiam, de ez nem a megfelelô idô a piruló szûz szerepére. Ne légy bátortalan és ne félj, mert az Úr, a te Istened elôtted jár, hogy gyôzelmet adjon neked! Menj bele ebbe a harcba szeretteidért, minden keresztényért... és ha nem értük, akkor a saját érdekedben, mert ha az a démon gyôztesen kerül ki, te is elpusztulsz mindenkivel együtt.";
			link.l1 = "Azt hiszem, meggyôzött engem, atyám. Haboztam a helyzetemmel kapcsolatban, hogy keresztes hadjáratot indítsak Tayasalba, de most már nincsenek kétségeim. Miben tudsz nekem segíteni?";
			link.l1.go = "tieyasal_8";
		break;
		
		case "tieyasal_8":
			dialog.text = "Csak két ember tudta, hogyan lehet eljutni Tayasalba: Alonso de Maldonado és Miguel Dichoso. Don Alonso meghalt. És Dichoso... Azt mondták nekem, hogy nemrég látták Sharptownban, Isla Tesoro-n. Talán még mindig ott van. Meg kell találnod Dichosót, és rá kell venned, hogy legyen az idegenvezetôd.\nAz arany vagy erôszak segítségével rá kell venned ezt az embert, hogy elvigyen téged Tayasalba. Ott megtalálod a pokol kapuit, és ott lepecsételed ôket.";
			link.l1 = "És mi lesz az emberekkel?";
			link.l1.go = "tieyasal_9";
		break;
		
		case "tieyasal_9":
			dialog.text = "A legutóbbi seregem Alonso de Maldonado parancsnoksága alatt állt. Sajnos, nincs lehetôségem arra, hogy újabb spanyol katonákból álló csapatot állítsak össze. A helyi helyôrségnél már minden kincsemet elköltöttem. A saját embereid segítségével kell megtenned, fiam. De minden másban segítek, amiben tudok.";
			link.l1 = "Miféle segítséget?";
			link.l1.go = "tieyasal_10";
		break;
		
		case "tieyasal_10":
			dialog.text = "Minden elônyünket ki kell használnunk ebben a harcban, mind anyagi, mind szellemi téren. Kértem Adrian atyát, hogy öt nap múlva csatlakozzon hozzám itt a kápolnában. Ô szent amuletteket hoz magával nektek. Amuletteket, amelyek segíthetik Krisztus harcosait a csatában. Mindenféle bájitalokkal is ellát benneteket. Ami engem illet, fogadd el ezt a pengét, fiam.\nEz a templomos lovagok ôsi kardja, ôseink félelmetes fegyvere. Még mindig éles, és az Egyház áldásától csillog. Csak a legnagyobb lovagoknak jutott a megtiszteltetés, hogy használhassák. Vedd el, birtokold büszkén, és zúzd szét hitünk ellenségeit Jézus Krisztus nevével az ajkadon!";
			link.l1 = "Köszönöm! Ez a kard teljesen lenyûgözô. Szótlan vagyok...";
			link.l1.go = "tieyasal_11";
		break;
		
		case "tieyasal_11":
			sTemp = GetBestGeneratedItem("blade_32");
			GiveItem2Character(pchar, sTemp);
			sld = ItemsFromID(sTemp);
			sld.Balance = 2.0;
			sld.Weight = 4.5;
			Log_Info("Megkaptad a Tanath-ot.");
			PlaySound("interface\important_item.wav");
			dialog.text = "Isten áldjon meg benneteket, "+GetFullName(pchar)+", ebben a közelgô csatában. Felruházlak benneteket a Szent Kereszttel. Mindenható Isten, kinek kezében nyugszik a gyôzelem, és aki Dávidnak is csodálatos erôt adott Góliát legyôzéséhez: alázatosan kérjük kegyelmedet, hogy életadó irgalmaddal áldd meg ezeket a fegyvereket; és add meg szolgádnak "+GetFullName(pchar)+" , aki viselni akarja ôket, hogy szabadon és gyôztesen használhassa ôket a Szûzanya Egyház védelmére minden látható és láthatatlan ellenség támadásaival szemben. Krisztus Urunk által. Ámen.";
			link.l1 = "Ámen!";
			link.l1.go = "tieyasal_12";
		break;
		
		case "tieyasal_12":
			dialog.text = "És most menj el, fiam. Isten vigyázzon rád, soha ne hagyjon el téged, se a keresésben, se az utadon, se a csatában. Keresd meg Miguel Dichosót, és az ô segítségével indulj el Tayasalba. Ne feledkezz meg Adrian atyáról, ô majd felszerel téged minden amulettel és gyógymóddal, amire szükséged lehet. És most itt az ideje, hogy visszatérjek Santiagóba. Viszlát, fiam. Vaya con Dios.";
			link.l1 = "Viszlát, Vincento atya...";
			link.l1.go = "tieyasal_13";
		break;
		
		case "tieyasal_13":
			DialogExit();
			NextDiag.CurrentNode = "first time";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Tieyasal_VinsentoGo", -1);
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
