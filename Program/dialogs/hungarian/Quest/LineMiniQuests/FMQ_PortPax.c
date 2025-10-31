// Addon-2016 Jason, французские миниквесты (ФМК) Порт-о-Пренс
void ProcessDialogEvent()
{
	ref sld, NPChar;
	aref Link, NextDiag;
	int i;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Egy nyilvánvaló bogár. Szólj róla a fejlesztôknek.";
			link.l1 = "Ó, meg fogom.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "officer":
			PlaySound("Voice\English\z_arest_02.wav");
			dialog.text = "Mi az ördög folyik itt, uraim? Harcot hallottam.";
			link.l1 = "Üdvözlöm, biztos úr, hallottam egy nô sikoltozását és...";
			link.l1.go = "officer_1";
		break;
		
		case "officer_1":
			DialogExit();
			sld = CharacterFromID("FMQP_noble");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "officer_2":
			dialog.text = "";
			link.l1 = ""+GetFullName(pchar)+". Kapitány "+GetFullName(pchar)+".";
			link.l1.go = "officer_3";
		break;
		
		case "officer_3":
			dialog.text = "Egyelôre szabadon távozhat, kapitány. Megnézem, mi történt itt, majd hívjuk, ha kérdésünk lenne.";
			link.l1 = "Rendben...";
			link.l1.go = "officer_4";
		break;
		
		case "officer_4":
			DialogExit();
			sld = CharacterFromID("FMQP_noble");
			sld.Dialog.currentnode = "noble_3";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "officer_5":
			PlaySound("Voice\English\z_arest_02.wav");
			dialog.text = "Mi az ördög folyik itt, uraim? Harcot hallottam.";
			link.l1 = "Huh... Tiszt úr, a kocsmárosnő kérésére vagyok itt — azt állította, hogy itt valakit meg fognak ölni, és ez sajnos igaznak bizonyult — ez a két gazember rátámadt erre a nemes úrra. Sajnos nem tudtam megmenteni a szegényt. A gazfickók végeztek vele.";
			link.l1.go = "officer_6";
		break;
		
		case "officer_6":
			dialog.text = "A fenébe a szememmel... Ez egy spanyol! Miért lenne itt? Hm. És ön kicsoda, "+GetAddress_Form(NPChar)+"?";
			link.l1 = ""+GetFullName(pchar)+". Kapitány "+GetFullName(pchar)+".";
			link.l1.go = "officer_7";
		break;
		
		case "officer_7":
			dialog.text = "Kapitány, egyelôre szabadon távozhat. A szavai egyeznek a tanúval'. Szükség esetén hívni fogjuk.";
			link.l1 = "Rendben...";
			link.l1.go = "officer_8";
		break;
		
		case "officer_8":
			DialogExit();
			DoQuestReloadToLocation("Portpax_town", "reload", "reload4", "");
		break;
		
		case "noble":
			dialog.text = "Engedje meg, hogy mindent elmagyarázzak, tiszt úr! Én, Don Domingo Ortiz Albalate Santo Domingóból, egy fiatal hölgy meghívására érkeztem Port-au-Prince-be. A találkozó várakozása közben egy kocsmában szálltam meg. Alig telt el két óra, amikor dos canallas malditas berontottak a szobámba, és ha nem a vészszerű segítség idejében, "+GetSexPhrase("ezt a jó señort, aki megjelent","ezt a gyönyörű señorítát, aki megjelent")+", komoly bajba kerültem volna.";
			link.l1 = "Don Domingo Ortiz Albalate? Maga spanyol?";
			link.l1.go = "noble_1";
		break;
		
		case "noble_1":
			dialog.text = "Olyan spanyol, mint maga Rey Felipe, ha! Szeretném megjegyezni, hogy a papírjaim buen ordenben vannak. Nemes vagyok Spanyolországból, nem valami kalóz!";
			link.l1 = "Don Domingo, ôszinte bocsánatkérésünk a szerencsétlen incidensért! Kérem, jöjjön velünk néhány kérdésre és egy üveg borra a helyôrségbe. Mindent elintézünk. Ami pedig Önt illeti...";
			link.l1.go = "noble_2";
		break;
		
		case "noble_2":
			DialogExit();
			sld = CharacterFromID("FMQP_off");
			sld.Dialog.currentnode = "officer_2";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "noble_3":
			PlaySound("Voice\English\LE\Domingo\Domingo_01.wav");
			dialog.text = ""+UpperFirst(GetAddress_Form(NPChar))+" Capitan! "+UpperFirst(GetAddress_Form(NPChar))+" Capitan! Esküszöm Santiagóra és a Boldogságos Szûzre, hogy ön nemes ember, és Kasztília igazi fia mindig megjutalmazza az ilyen nemességet! Szeretném, ha késôbb megjutalmaznának, amikor befejezem az itteni dolgaimat. Kérlek, tisztelj meg azzal, hogy meglátogatsz szerény házamban, Santo Domingóban! Közel van a város kapujához. Lakomát rendezek neked, "+GetSexPhrase("my buen amigo","mi salvadora")+"! Emlékezz a nevemre, Don Domingo Ortiz Albalate!";
			link.l1 = "...";
			link.l1.go = "noble_4";
		break;
		
		case "noble_4":
			DialogExit();
			AddMapQuestMarkCity("santodomingo", true);
			DoQuestReloadToLocation("Portpax_town", "reload", "reload4", "FMQP_AfterFightInTown");
		break;
		
		case "noble_5":
			dialog.text = "Capitan "+pchar.lastname+"?! Oh Madre de Dios! Micsoda katasztrófa! Ez egy mészárlás! Mi történt itt, "+GetSexPhrase("mi buen amigo","mi salvadora")+"? Kik ezek az emberek?";
			link.l1 = "Örülök, hogy látom, Don Domingo. Ezek itt... Azért jöttem, hogy meglátogassam. Látod azt a fickót ott? Ô Ugo, a szolgád, és ô...";
			link.l1.go = "noble_6";
		break;
		
		case "noble_6":
			dialog.text = "Ugo?! Ó, nem, téged becsaptak kapitány!";
			link.l1 = "Értem, úgy tûnik, sokszor megtörténik velem. Három gazember betört a házába, meggyilkolták a hûséges emberét, Ugót - a holttestét már az emeleten találtam -, majd csapdát állítottak önnek. Az én érkezésem nem volt része a tervüknek. Nem élték túl a találkozásunkat.";
			link.l1.go = "noble_7";
		break;
		
		case "noble_7":
			dialog.text = "Santa Maria, ora pro nobis! Úgy játszol a kardoddal, mint a toledói vívómesterek! Jó, hogy az én oldalamon állsz! Ó, szegény Ugo! Gyermekkorom óta ô nevelt fel, és most... hogy megöljenek a maldita canallasok!";
			link.l1 = "Don Domingo, úgy néz ki, még mindig veszélyben vagy. Az embere, Ugo, tudott valamit, olvassa el ezt a levelet. Egy asztalon találtam.";
			link.l1.go = "noble_8";
		break;
		
		case "noble_8":
			ChangeItemDescribe("letter_parol", "itmdescr_letter_parol");
			RemoveItems(pchar, "letter_parol", 1);
			dialog.text = "Add ide... (olvasás) Ez nem lehet... ó, ne! Ez hihetetlen! Tio Luis... De...";
			link.l1 = "Van valami nyom arra, hogy ki tette ezt?";
			link.l1.go = "noble_9";
		break;
		
		case "noble_9":
			dialog.text = "Csak gyanú... szörnyû gyanú, "+GetSexPhrase("mi buen amigo","mi salvadora")+"! Hogy tehetett ilyet az anyám bátyja?";
			link.l1 = "Beavatnál a részletekbe? Sajnálom, Don Domingo, de tapasztalatom szerint a rokonok gyakran a legrosszabb ellenségei az embernek...";
			link.l1.go = "noble_10";
		break;
		
		case "noble_10":
			dialog.text = "Si, igazad van, "+GetAddress_Form(NPChar)+"! Mindent el fogok mondani! Már kétszer megmentettél, és úgy tûnik, te vagy az egyetlen ember, akiben most megbízhatok! De hagyjuk el ezt a szörnyû helyet, rosszul vagyok tôle. Értesítenem kell az alcalde-ot errôl a zûrzavarról, ôk majd gondoskodnak szegény Ugo ügyérôl. Mi lenne, ha innánk egy kis bort a helyi tabernában, hogy megnyugtassuk az idegeinket?";
			link.l1 = "A te idegeidnek biztosan nagyobb szükségük van rá, mint az enyémeknek, menj elôre, senor!";
			link.l1.go = "noble_11";
		break;
		
		case "noble_11":
			DialogExit();
			chrDisableReloadToLocation = false;
			DoQuestReloadToLocation("Santodomingo_tavern", "sit", "sit_base2", "FMQP_InSantoDomingoTavern");
		break;
		
		case "noble_12":
			LAi_SetSitType(pchar);
			dialog.text = "Szóval, barátom, engedd meg, hogy elmeséljem neked a családom történetének egy... rövidített formáját. Anyám, Dona Isabella Ortiz, férjhez ment apámhoz, Ricardo Albalate márkihez, és a szokásoknak megfelelôen felvette a családi nevét. A bátyja, Luis Ortiz, helyôrségparancsnok volt a gyarmatokon, de anyám házassága után apám kinevezte egy Portobellótól nem messze lévô cukorültetvény vezetôjének\nEz egy hatalmas és gazdag ültetvény volt, nagyon jövedelmezô. Miután a szüleim néhány évvel ezelôtt tragikusan elhunytak a tengeren, én, mint egyetlen fiuk, mindent örököltem, beleértve az ültetvényt is. A nagybátyám megtartotta a pozícióját, és én elégedett voltam a bérleti díjjal, amit fizetett nekem. Mindig idôben fizetett.";
			link.l1 = "Szóval úgy gondolja, hogy a nagybátyja...";
			link.l1.go = "noble_13";
		break;
		
		case "noble_13":
			dialog.text = "Igen, azt hiszem. Jelenleg ô csak egy bérlô. Az ültetvény az enyém, nem az övé. De! Ha bármi történik velem - az ô tulajdonába kerül.";
			link.l1 = "Tudod, Domingo, ismertem olyan embereket, akik hidegvérrel meggyilkolták volna az összes rokonukat egy ennél sokkal kevésbé szaftos díjért.";
			link.l1.go = "noble_14";
		break;
		
		case "noble_14":
			dialog.text = "Nyilvánvalóan jobb társaságra van szükséged, Carlos. Az én kedves Ugo-m említette a nagybátyám papírjait az utolsó üzenetében... Ez egy közvetlen nyom. Ó, ezt nem akarom elhinni! De... az unokatestvéremet, Margarita Ortizt, aki Spanyolországban él, nemrég eljegyezték. Talán ez az oka, "+GetAddress_Form(NPChar)+" kapitány úr?";
			link.l1 = "A nagybátyjának hirtelen szüksége lehet egy kis pénzre...";
			link.l1.go = "noble_15";
		break;
		
		case "noble_15":
			dialog.text = "Pénz?! De persze... de ne feledje a márki címet! Azzal az unokatestvérem méltó párja lenne leendô férjének! Jesu Christo! Milyen ostoba voltam!";
			link.l1 = "Ez a nemesi cím többet ér, mint a cukorültetvény.";
			link.l1.go = "noble_16";
		break;
		
		case "noble_16":
			dialog.text = "Várj, "+GetAddress_Form(NPChar)+"! Most jutott eszembe, hogy nem ez volt az elsô merénylet az életem ellen! Néhány hete találkoztam egy koldussal az utcán! A részeg canalla olyan módon sértett meg, amit nem tudtam figyelmen kívül hagyni. Kiderült, hogy átkozottul jó vívó, acélt rántott, és még egy rapírral is sikerült megsebeznie, mielôtt megöltem volna.";
			link.l1 = "És hogy a fenébe kerültél egy Kikötô-au-Prince-i kocsmába? Említettél valami fiatal senorita-t?";
			link.l1.go = "noble_17";
		break;
		
		case "noble_17":
			dialog.text = "(vörösre vált) Uram... Igen kapitány, egy fiatal és csinos senorita volt a helyszínen... most már látom, hogy ô csak a csali volt a csapdához. Szemetek, szemetek vannak mindenütt, nem lehet megbízni senkiben! Szegény Ugo... most már halott.";
			link.l1 = "Tenned kellene valamit, Domingo. Mi lenne, ha Spanyolországba menekülnél?";
			link.l1.go = "noble_18";
		break;
		
		case "noble_18":
			dialog.text = "Spanyolországba? És az én ültetvényemet hagynád arra a gazemberre? Kapitány, én Domingo Ortiz Albalate márki vagyok!";
			link.l1 = "De...";
			link.l1.go = "noble_19";
		break;
		
		case "noble_19":
			dialog.text = ""+UpperFirst(GetAddress_Form(NPChar))+", kérhetem a segítségedet? Ugo halála óta nincs mellettem senki, akiben megbízhatnék. Már kétszer megmentettél! Kétszer! Sokkal tartozom neked, örökké az adósod vagyok, és mégis merek még egy szívességet kérni tôled. Esküszöm az Áldó Anyára, hogy meg fogom érni, hogy megéri a fáradozásodat!";
			if (startHeroType == 2)  
			{
				link.l1 = "Miben segíthetek Önnek, "+npchar.name+"?";
				link.l1.go = "noble_20";
			}
			else
			{
				link.l1 = "Rendben, spanyol létedre jó ember vagy. Mit tehetek érted, Domingo?";
				link.l1.go = "noble_20";
			}	
		break;
		
		case "noble_20":
			dialog.text = "Menjünk a portabellói ültetvényemre! Tudom, hogy a nagybátyám jelenleg Cartagenában van. Ugo említett néhány papírt, úgyhogy nézzük meg Don Luis Ortiz könyveit és iratait! Talán találunk valamit, ami segíthet nekünk, hogy leleplezzük a bûnös összeesküvését. Elég messze van Portobello, de teljes egészében kifizetem az út árát!";
			link.l1 = "Képtelenség lenne most visszautasítani önt, Don Domingo. Túl mélyen benne vagyok ahhoz, hogy most visszalépjek.";
			link.l1.go = "noble_21";
		break;
		
		case "noble_21":
			AddMoneyToCharacter(pchar, 20000);
			dialog.text = "Gracias a Dios, tudtam, hogy kisegítesz, amigo! Tessék, fogadja el ezt a húszezer pezót a Portobello-i út kifizetéseként. Mikor indulunk? Sietnünk kell, mielôtt a nagybátyám visszatér Cartagenából!";
			link.l1 = "Akkor ne vesztegessük az idôt.";
			if (startHeroType != 2 && CheckCharacterItem(pchar, "HolTradeLicence") && GetDaysContinueNationLicence(HOLLAND) >= 20 && GetNationRelation2MainCharacter(SPAIN) == RELATION_NEUTRAL) {link.l1.go = "noble_22";}
			else {link.l1.go = "noble_22x";}
		break;
		
		case "noble_22x":
			GiveNationLicence(HOLLAND, 20);
			dialog.text = "Itt van a Holland Nyugat-indiai Társaság engedélye. Húsz nap múlva jár le, csak írjuk bele a nevét. Rendben. Ezzel elkerülhetjük a Costa Gardával kapcsolatos problémákat.";
			link.l1 = "Kiváló!";
			link.l1.go = "noble_22";
		break;
		
		case "noble_22":
			dialog.text = "Most már feljöhetek a hajójára, kapitány?";
			link.l1 = "Tekintse magát megtisztelt vendégnek. Amint megfelelô szelet kapunk - kihajózunk.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQP_OnBoard");
			AddMapQuestMarkCity("portobello", true);
		break;
		
		case "noble_23":
			dialog.text = "Szóval, kapitány, itt vagyunk. Most meg kell találnunk a nagybátyám házát, és megnézni, mi van odabent.";
			link.l1 = "Don Domingo, számíthatunk bármilyen problémára az ôrséggel?";
			link.l1.go = "noble_24";
		break;
		
		case "noble_24":
			dialog.text = "Nem. Bár... Van rá esély, hogy Luis ellenem fordította ôket. Mindenesetre a diszkréció mindig a bátorság jobbik oldala. Keressük meg a házat, amire szükségünk van.";
			link.l1 = "Nem tudod már? Ez a te ültetvényed.";
			link.l1.go = "noble_25";
		break;
		
		case "noble_25":
			dialog.text = "Hm... Hogy teljesen ôszinte legyek, amikor utoljára itt voltam, még csak nyolc éves voltam. Mégis szándékomban áll ezt minél hamarabb rendbe hozni!";
			link.l1 = "Értem. Akkor kezdjünk el keresni. A nagybátyád háza a legnagyobb itt.";
			link.l1.go = "noble_26";
		break;
		
		case "noble_26":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			AddQuestRecord("FMQ_Portpax", "7");
		break;
		
		case "noble_27":
			dialog.text = "Mi van itt, "+GetAddress_Form(NPChar)+"?";
			link.l1 = "Nézze meg, Don Domingo. Úgy néz ki, mintha könyvelési feljegyzések lennének. Ez érdekes lehet.";
			link.l1.go = "noble_28";
		break;
		
		case "noble_28":
			ChangeItemDescribe("Almanac", "itmdescr_Almanac");
			RemoveItems(pchar, "Almanac", 1);
			dialog.text = "(olvasás) Hm... Igen. Ezt nézd meg... Ay caramba! Százezer pezó! És még százötvenezer! És itt... (lapozgatja a lapokat) Luis bácsi!";
			link.l1 = "Van valami érdekes?";
			link.l1.go = "noble_29";
		break;
		
		case "noble_29":
			dialog.text = "Bármi érdekes! Az én drága nagybátyámnak ötször nagyobb jövedelme volt, mint amit nekem mondott! Tolvaj! Sikkasztó!";
			link.l1 = "Nem mondhatnám, hogy meglepôdtem. Nem bízhatsz meg teljesen senkiben anélkül, hogy idôrôl idôre ne ellenôriznéd az üzlet tényleges helyzetét. Ez csak a józan ész.";
			link.l1.go = "noble_30";
		break;
		
		case "noble_30":
			dialog.text = "A józan ész a józan embereknek, talán. A neveltetésem elvakított az ilyen csalásra az általam becsületesnek hitt úriembereknél! Igazad van, mint mindig, Carlos! A saját nagybátyám lop tôlem! Mierda! Ez az én hibám, de helyre fogom hozni. Ez az ültetvény az enyém, és a nagybátyámat mától felmentették a szolgálat alól! Ô egy senki! Elintézem, hogy elintézzék!";
			link.l1 = "Don Domingo... Nem gondolja, hogy a nagybátyja nem értene egyet egy ilyen döntéssel?";
			link.l1.go = "noble_31";
		break;
		
		case "noble_31":
			dialog.text = "Nem érdekel, hogy egyetért-e vagy sem! Én vagyok Domingo Ortiz Albalate márki, Luis Ortiz pedig nem más, mint egy bérlô, méghozzá egy volt bérlô! És ô...";
			link.l1 = "Nyugodjon meg, senor. Ön ismeretlen arc itt, én pedig egy francia vagyok, aki holland jogosítvánnyal hajózik, és akinek... kockás múltja van a spanyol kalózellenes járôrökkel. Ami a nagybátyját illeti, ez a város gyakorlatilag az övé. Gondoljon az ôrségre és a helyi kormányzóra. Gondolja, hogy a maga oldalára állnak?";
			link.l1.go = "noble_32";
		break;
		
		case "noble_32":
			dialog.text = "Egy pengével a kezedbe csapsz a lényegre... Talán... Nem. A spanyol katonák soha nem mernének kezet emelni egy nemesre! A nagybátyám kihívhat engem, ha mer!";
			link.l1 = "Mégis, azt javaslom, hogy más utat válasszunk. Mit szólnál a bírósághoz?";
			link.l1.go = "noble_33";
		break;
		
		case "noble_33":
			dialog.text = "Ha! Igazad van, Carlos. Menjünk, beszéljünk a megfelelô hatóságokkal. A nagybátyám hibát követett el, amikor pontos részleteket írt le a jegyzeteibe a csempészekkel való üzleteirôl. Nagyon olcsón vett rabszolgákat tôlük. Ezek a könyvek nagy szolgálatot tesznek majd nekünk, kétlem, hogy a fattyú bármiben is ártani tudna nekem, amíg a tömlöcben ül. Menjünk! Portobellóba!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQP_PrepareUncle");
		break;
		
		case "noble_34":
			//PlaySound("Voice\English\LE\Domingo\Domingo_04.wav");
			dialog.text = "Ez nem más, mint egy mocskos és szemtelen hazugság! Hogy merészeli a szüleim jó hírnevét rontani a méltatlan nyelvével! Átkozott legyen, ezért megfizet! Húzd ki a kardod, te gyilkos!";
			link.l1 = "";
			link.l1.go = "noble_35";
		break;
		
		case "noble_35":
			DialogExit();
			sld = CharacterFromID("FMQP_Uncle");
			sld.Dialog.currentnode = "uncle_3";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "noble_36":
			PlaySound("Voice\English\LE\Domingo\Domingo_05.wav");
			dialog.text = "Luis bácsi a lelkének fenntartott helyen van - a pokolban... "+pchar.name+", téged az ôrangyalom küldött hozzám! Örülök, hogy nem bíztál ennek a gazembernek a szavában. Hogy ôszinte legyek, attól féltem, hogy csak úgy itt hagysz egyedül, hogy megküzdjek ezzel a canalla\nIgen, "+GetAddress_Form(NPChar)+", én magam sem vagyok tökéletes, de ez... ez a mocskos hazugság arról, hogy kalózokat béreltem fel a saját szüleim meggyilkolására! Engem hibáztatni ezért... ezért! Bah! Megérdemelt sors.";
			link.l1 = "Örülök, hogy sikerült, Don Domingo. És most mi lesz? Remélem, nem ütköztünk a spanyol törvényekbe.";
			link.l1.go = "noble_37";
		break;
		
		case "noble_37":
			dialog.text = "A törvénnyel? Ha-ha! Nem "+pchar.name+", megmutatom ezt a szép könyvelést, amiben a nagybátyám összes csempészete benne van. Ne feledkezz meg az ellenem elkövetett többszöri merényletrôl sem, rengeteg tanúnk van a legutóbbi próbálkozása után. Ne aggódj emiatt, "+GetAddress_Form(NPChar)+". Ez az én városom, itt az ideje, hogy megmutassam mindenkinek!";
			link.l1 = "Kérem, óvatosan mozogjon, senor. Hagyja, hogy jobbat gondoljanak magáról, mint amit néhai nagybátyjáról gondoltak.";
			link.l1.go = "noble_38";
		break;
		
		case "noble_38":
			dialog.text = "Ez a terv, kapitány. De nem kegyelmezek senkinek, aki szembe mer szállni velem. Hadd fejezzem ki ôszinte hálámat önnek, "+pchar.name+"! Kérlek, menj a tabernába, pihenj egy kicsit, igyál egy-két pohárral. Szívesen csatlakoznék hozzád, de igazad volt. Itt az ideje, hogy bölcsebbé váljak, és magam vegyem át az irányítást az ültetvény felett. Jöjjön ide holnap, kapitány!";
			link.l1 = "Rendben, Don Domingo. Holnap találkozunk.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQP_PlantatonPause");
		break;
		
		case "noble_39":
			DelLandQuestMark(npchar);
			PlaySound("VOICE\English\LE\Domingo\Domingo_05.wav");
			dialog.text = "Á, hát itt vagy, "+GetAddress_Form(NPChar)+"!";
			link.l1 = "Hogy van, don Domingo? Hogy van az ültetvénye?";
			link.l1.go = "noble_40";
		break;
		
		case "noble_40":
			dialog.text = "Az ültetvény nagyszerû, a pénzrôl nem mondhatom el ugyanezt - kiderült, hogy a kedves nagybátyám az összes pénzt a cartagenai bankba utalta. Sok ügyvéd' idôbe fog kerülni, hogy visszakapjam az aranyamat. De semmi baj, meg tudom csinálni. Ne szomorkodj, kapitány, megtartom az ígéretemet, hogy megjutalmazlak nemességedért, becsületességedért és barátságodért!";
			link.l1 = "Soha nem gondoltam jutalomra, amikor az ön oldalán harcoltam, senor...";
			link.l1.go = "noble_41";
		break;
		
		case "noble_41":
			dialog.text = "Tudom, kapitány, és ez sokat elmond a jellemérôl! Minden jó cselekedetet meg kell jutalmazni. Így hát, bár jelenleg nincs pénzem, parancsot adok, hogy rakodják meg a hajódat az ültetvényem árujával. Úgy értem kávéval, egy nagy adaggal. Biztos vagyok benne, hogy nagy haszonnal tudod majd eladni.";
			link.l1 = "Ó! Ez szép...";
			link.l1.go = "noble_42";
		break;
		
		case "noble_42":
			dialog.text = "Ezen kívül van még néhány dolog, ami számomra nem túl értékes, de a magadfajta tengerész számára nagy értéket képvisel. Egy szép távcsô és három amulett. Kérem, fogadja el ezeket, most már mind a magáé.";
			link.l1 = "Köszönetnyilvánítás!";
			link.l1.go = "noble_43";
		break;
		
		case "noble_43":
			Log_Info("Kaptál egy jó távcsövet");
			Log_Info("Kaptál három amulettet");
			PlaySound("interface\important_item.wav");
			dialog.text = "Végül, megajándékozlak a pengémmel, mérhetetlen hálám jeléül. Jól szolgált engem, most hadd szolgáljon téged még jobban. Nézz rá, és emlékezz jó spanyol barátodra - márki Domingo Albalate!";
			link.l1 = "Nagyon köszönöm, senor! Nem számítottam rá...";
			link.l1.go = "noble_44";
		break;
		
		case "noble_44":
			Log_Info("Kaptál egy kis kardot");
			PlaySound("interface\important_item.wav");
			RemoveCharacterEquip(npchar, BLADE_ITEM_TYPE);
			dialog.text = "És most, sajnos, el kell búcsúznom. Portobellóba kell mennem a kormányzóhoz, aztán Cartagenába... Összefoglalva, gondtalan életemnek vége, ideje felnôtt emberként élni.";
			link.l1 = "Nos, most már sokkal okosabb vagy...";
			link.l1.go = "noble_45";
		break;
		
		case "noble_45":
			dialog.text = "Ez igaz. Öröm volt, "+GetAddress_Form(NPChar)+"! Gyere el hozzám valamikor. Isten éltessen a tengeren!";
			link.l1 = "Önnek is ugyanezt az ültetvényes üzletben, don Domingo!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQP_ReceiveReward");
		break;
		
		case "noble_46":
			PlaySound("Voice\English\YoungMan02.wav");
			dialog.text = "Eh, elkéstünk, senor! Milyen kár, az én jó öreg nagybátyám már tisztességes takarítást végzett a papírjai között. Úgy látszik, szóltak neki Santo Domingóról, és ô megtette az óvintézkedéseket... De én ezt nem hagyom így! Meg kell keresnem Portobello kormányzóját, hogy jogi eljárást kezdeményezzek a nagybátyámmal szemben. Elegem van abból, hogy ô kezeli a vagyonom.";
			link.l1 = "Jó döntés.";
			link.l1.go = "noble_47";
		break;
		
		case "noble_47":
			dialog.text = "Köszönöm, kapitány úr! Nagyon örültem! Hálám jeléül megajándékozom a pengémmel. Jól szolgált engem, most hadd szolgáljon téged még jobban. Nézz rá, és emlékezz jó spanyol barátodra, Domingo Albalate márkira!";
			link.l1 = "Köszönöm szépen, senor! Nem számítottam rá...";
			link.l1.go = "noble_48";
		break;
		
		case "noble_48":
			Log_Info("Kaptál egy kis kardot");
			PlaySound("interface\important_item.wav");
			RemoveCharacterEquip(npchar, BLADE_ITEM_TYPE);
			GiveItem2Character(pchar, GetGeneratedItem("blade_16")); // belamour legendary edition используем GetGeneratedItem иначе пачка одинаковых клинков из первой части массива
			dialog.text = "És most, sajnos, el kell búcsúznom. Portobellóba kell mennem. Vége a gondtalan életemnek, ideje felnôttként élni. Isten éltessen a tengeren!";
			link.l1 = "Sok szerencsét a bácsikáddal, don Domingo! Biztos vagyok benne, hogy gyôzni fog!";
			link.l1.go = "noble_49";
		break;
		
		case "noble_49":
			DialogExit();
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("PortoBello_Plantation", "reload2_back", false);
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 40.0);
			pchar.questTemp.FMQP = "fail";
			AddQuestRecord("FMQ_Portpax", "13");
			CloseQuestHeader("FMQ_Portpax");
			sld = &Locations[FindLocation("PortoBello_Plantation")];
			sld.soldiers = true;
		break;
		
		case "uncle":
			PlaySound("Voice\English\OliverTrast02.wav");
			if (pchar.sex == "woman") { dialog.text = "Úgy tűnik, éppen időben érkeztem. A mihaszna unokaöcsém és az új szerelme, "+GetFullName(pchar)+" kapitánynő... Igen-igen, "+GetSexPhrase("fiatalember","szenyorita")+", ne lepődjön meg – már utánajártam önnek."; }
			else { dialog.text = "Úgy tűnik, éppen időben érkeztem. A mihaszna unokaöcsém és az ő őrangyala, "+GetFullName(pchar)+" kapitány... Igen-igen, "+GetSexPhrase("fiatalember","szenyorita")+", ne lepődjön meg – már utánajártam önnek."; }
			link.l1 = "Luis Ortiz?";
			link.l1.go = "uncle_1";
		break;
		
		case "uncle_1":
			dialog.text = "Igaza van, kapitány úr, de minden másban téved. Nem kellene beleütnie az orrát mások családi ügyeibe. Fogalma sincs, hogy kit véd. Az én züllött unokaöcsém, Domingo egy semmirekellô ficsúr, minden kocsma és bordélyház elsô számú látogatója, aki minden lányt megdug, vagy legalábbis megpróbál megdugni a láthatáron. Minden hónapban fizetem neki a lakbért, ô pedig napok alatt elpazarolja, mindig többet és többet követelve. Újra és újra. Állandó méltatlan viselkedése az anyját és a húgomat is megôrjítette\nHallottam olyan pletykákat, hogy ez a pajkos fiú még angol magánvadászokat is felbérelt és irányított Ricardo Albalate márki egy bizonyos hajójára, amelyet elsüllyesztettek azzal a méltó emberrel és az én drága húgommal együtt. Domingo annyira akarta a családunk pénzét, hogy ölni is képes volt érte... Sajnos nem sikerült elég bizonyítékot elôásnom ahhoz, hogy ezt a gazembert akasztófára küldjem.";
			link.l1 = "";
			link.l1.go = "uncle_2";
		break;
		
		case "uncle_2":
			DialogExit();
			sld = CharacterFromID("FMQP_noble");
			sld.Dialog.currentnode = "noble_34";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "uncle_3":
			if (pchar.sex == "woman") { dialog.text = "A kedves unokaöcsém, ahogy mindig is – a maga formájában. Sok zaj, pengék csattognak, poharak csilingelnek, de haszna kevés. Nem is értem, mit lát ön benne, szenyorita, hisz ő csak..."; }
			else { dialog.text = "A kedves unokaöcsém, ahogy mindig is – a maga formájában. Sok zaj, pengék csattognak, poharak csilingelnek, de haszna kevés. Nem tudom, mivel vette rá önt, hogy segítsen ennek az éretlen kölyöknek..."; }
			link.l1 = "Ha jól tudom, miután nem sikerült bizonyítékot elôásnia az unokaöccse ellen, bérgyilkosokat kezdett utána küldeni. Úgy hangzik, mintha egy egyszerû per is elég lett volna.";
			link.l1.go = "uncle_4";
		break;
		
		case "uncle_4":
			dialog.text = "Hazugságokat beszél. Domingónak rengeteg ellensége van. Elhagyott szeretôk és felszarvazott férjek sorát hagyta maga után. Csodálkozom, hogy sikerült egyáltalán túlélnie ilyen sokáig! Kérdezd meg tôle, hány esküvôt tett tönkre? Hány sértett vôlegényt sebesített meg vagy ölt meg?";
			link.l1 = "A szolgája, Ugo...";
			link.l1.go = "uncle_5";
		break;
		
		case "uncle_5":
			dialog.text = "Ah Ugo! A legrosszabb gazember mind közül! Ugo szerette a gazember urát. A gazdája minden bûne csak egy gyerekcsíny volt számára. Ne feledje, "+GetSexPhrase("fiatalember","señorita")+", a családi ügyek csak a családra tartoznak. Aki piszkálódik és kíváncsiskodik, az forró vízben találja magát.";
			link.l1 = "Most meg fenyegetsz engem.";
			link.l1.go = "uncle_6";
		break;
		
		case "uncle_6":
			int icpy = GetOfficersQuantity(pchar);
			iTotalTemp = 10000+10000*icpy;
			dialog.text = "Figyelmeztetés. Hallgasson ide, kapitány: "+GetSexPhrase("túl messzire ment, de ","")+"nem tekintem önt ellenségnek, csak egy megtévedt embernek. Ezért ajánlatom a következő: forduljon meg, és távozzon. Nem akarok vérontást. A családi ügyeinket megoldjuk magunk. "+GetSexPhrase("Hajlandó vagyok megtéríteni az unokaöcsém miatt felmerült költségeit:","És hogy könnyebben döntsön, hajlandó vagyok ennyit fizetni:")+" "+FindRussianMoneyString(iTotalTemp)+" készpénzben. Vegye el, és felejtse el ezt a helyet. Különben az őreim egyszerűen megölik.";
			link.l1 = "'A család az elsô' ez az, amit mindig mondok. Akkor semmi közöm hozzá, adja át a pénzt és 'vaya con Dios.'";
			link.l1.go = "uncle_7";
			link.l2 = "A történeted büdösebb, mint az ültetvényed trágyája. Don Domingo talán nem szent, de maga, senor, egy ördög!";
			link.l2.go = "uncle_8";
		break;
		
		case "uncle_7":
			AddMoneyToCharacter(pchar, iTotalTemp);
			dialog.text = "Tudtam, hogy maga értelmes ember. Fogja a pénzét és adios capitan. Próbáljon meg a jövôben nem turkálni mások' mocskos szennyesében - sosem értékelik.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQP_UncleExit");
		break;
		
		case "uncle_8":
			if (pchar.sex == "woman") {dialog.text = "Most már értem. Pont olyan vagy, mint az unokaöcsém – buta, meggondolatlan lány. Tökéletesen illesz hozzá. Itt az ideje, hogy leckét adjak nektek!";}
			else {dialog.text = "Most már értem. Semmiben sem különbözöl az unokaöcsémtől – ugyanolyan ostoba, beképzelt kölyök! Itt az ideje, hogy leckét adjak nektek!";}
			link.l1.go = "exit";
			AddDialogExitQuest("FMQP_UncleFight");
		break;
		
		case "ugo":
			pchar.quest.FMQP_SantoDomingoOver.over = "yes";
			PlaySound("Voice\English\Serve_senior.wav");
			dialog.text = TimeGreeting()+" "+GetAddress_Form(NPChar)+". Miben lehetek a szolgálatára?";
			link.l1 = "Üdvözletem. Elnézést, de ez itt Senor Domingo Albalate lakása?";
			link.l1.go = "ugo_1";
		break;
		
		case "ugo_1":
			dialog.text = "Si, ez az Albalate háza. Szerény, de kényelmes. A nevem Ugo, az ifjú urat szolgálom. Maga miatta van itt?";
			link.l1 = "Si, senor. Don Domingo nemrég meghívott magához. Nagyon meggyôzô volt. Beszélhetnék vele?";
			link.l1.go = "ugo_2";
		break;
		
		case "ugo_2":
			dialog.text = "Sajnos, "+GetSexPhrase("caballero","señorita")+", Don Domingo most nincs itthon. Személy szerint én magam szeretném tudni, hol találom azt a rossz fiút... eh, bocsánat, fiatal senor. Megkérdezhetem, hogy mit akar tôle?";
			link.l1 = "Hát... Véletlenül segítettem Don Domingónak. Megtámadta két gazember Kikötô-au-Prince egyik kocsmájában. Segítettem az urának megvédeni magát azoktól a... hogy is hívta ôket... maldita canalla. Don Domingo meghívott, hogy látogassam meg, miután befejezte a nyomozást. Úgy gondoltam, hogy mostanra már mindennek el kellett volna rendezôdnie, ezért vártam, hogy hazaérjen.";
			link.l1.go = "ugo_3";
		break;
		
		case "ugo_3":
			dialog.text = "Madre de Dios! Micsoda szörnyû történeteket mesélsz itt! Azonnal találkoznom kell a parancsnokkal - hogy figyelmeztessem, milyen veszélyek fenyegetik Don Domingót most! "+UpperFirst(GetAddress_Form(NPChar))+", dovete andare e io devo sbrigarmi!, önnek mennie kell, nekem pedig sietnem kell!";
			link.l1 = "Nyugalom, Ugo. Az ifjú urad biztonságban van. Említette, hogy a papírjai rendben vannak, már el kellett volna engedniük, ezért vagyok itt. Azt hiszem, hamarosan találkozunk vele.";
			link.l1.go = "ugo_4";
		break;
		
		case "ugo_4":
			dialog.text = "Ó! Hogy tehetted? Az a naiv fiú - és azoknak a békaevô franciáknak a kezében?! Nem is beszélve az életét fenyegetô ladronokról? Nem, látnom kell a parancsnokot! "+UpperFirst(GetAddress_Form(NPChar))+", kérem, menjen!";
			link.l1 = "Jól van, jól van, ne legyen ilyen rámenôs. Elmegyek.";
			link.l1.go = "ugo_exit";
			link.l2 = "Senor, miért ilyen ideges? Már mondtam, hogy nincs veszélyben a gazdája. Hadd maradjak itt, és várjam meg Senor Domingo érkezését, nagyon fáradt vagyok a hosszú út után, és értékelném a vendégszeretetét. Szeretnék egy kis hûvös, friss vizet és egy forró fürdôt, hogy kiöblítsem a sós szellôt a torkomból. Aztán mehetsz a helyi helyôrségbe, és azt csinálhatsz, amit akarsz.";
			link.l2.go = "ugo_5";
		break;
		
		case "ugo_exit":
			DialogExit();
			LocatorReloadEnterDisable("Santodomingo_town", "houseSp4", true);
			DoQuestReloadToLocation("SantoDomingo_town", "reload", "houseSp4", "FMQP_SDMFail");
		break;
		
		case "ugo_5":
			dialog.text = ""+UpperFirst(GetAddress_Form(NPChar))+", azonnal hagyja el ezt a házat!";
			link.l1 = "Ugo, nagyon kétlem, hogy egy szolgának szabadna így beszélnie egy úri látogatóval. Azt is kétlem, hogy Don Domingo jóváhagyná, hogy így bánjanak egy olyan emberrel, aki megmentette az életét!";
			link.l1.go = "ugo_6";
		break;
		
		case "ugo_6":
			dialog.text = "Tényleg? (felhív az emeletre) Srácok, gyertek le, van egy kis gond!";
			link.l1 = "Mi a fasz?";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQP_SantoDomingoFight");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
