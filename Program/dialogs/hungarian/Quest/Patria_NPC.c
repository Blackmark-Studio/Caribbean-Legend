// диалоги НПС по квесту НСО
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
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
			dialog.text = "Mit keresel?";
			link.l1 = "Semmi.";
			link.l1.go = "exit";
		break;
		
		// инспектор Ноэль Форже
		case "noel":
			dialog.text = "Örülök, hogy találkoztunk, kapitány!";
			link.l1 = "Én is örülök, hogy megismerhetem, Monsieur Forget. Ritka alkalom, hogy egy nagyvárosi vendéggel találkozom itt a vadonban...";
			link.l1.go = "noel_1";
		break;
		
		case "noel_1":
			DialogExit();
			sld = characterFromId("Puancie");
			sld.dialog.currentnode = "patria_3";
			LAi_SetActorType(sld);
			LAi_ActorSetSitMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "noel_2":
			dialog.text = "Örülök, hogy ezen az úton az ön hajóján leszek, kapitány. Chevalier de Poincy sok érdekes történetet mesélt önrôl. Biztos vagyok benne, hogy az étkezôben elköltött vacsora után bôven lesz mirôl beszélgetnünk. Egy pohár bor is jól jöhet.";
			link.l1 = "Én mindenben benne vagyok egy hangulatos beszélgetésben, különösen, ha jóllaktam. Szívesen leszek a társa, báró úr. ";
			link.l1.go = "noel_3";
		break;
		
		case "noel_3":
			dialog.text = "Tökéletes. Ha egy kolóniára megyünk, megkérném, hogy kísérjen el a kormányzóhoz, és én személyesen elmagyarázom neki, mit kell tennünk. Maga csak várjon, amíg én befejezem az ügyeimet. Megegyeztünk?";
			link.l1 = "Igenis, monsieur Forget. Isten hozta a fedélzeten!";
			link.l1.go = "noel_4";
		break;
		
		case "noel_4":
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 12.0);
		break;
		
		case "noel_5":
			dialog.text = "A Tortuga egy kis kolónia kapitánya. Becslésem szerint körülbelül három napba telik, amíg mindent megvizsgálok, amire szükségem van ezen a szigeten.";
			link.l1 = "Értettem, báró. Tehát három nap múlva idejövök önért. Sok szerencsét!";
			link.l1.go = "noel_6";
		break;
		
		case "noel_6":
			DialogExit();
			DoQuestReloadToLocation("Tortuga_town", "reload", "reload3", "Patria_VisiterTortuga");
		break;
		
		case "noel_7":
			dialog.text = "A munkám Tortugán befejezôdött, ideje felhúzni a horgonyt.";
			link.l1 = "Értettem, báró. Azonnal indulunk.";
			link.l1.go = "noel_8";
		break;
		
		case "noel_8":
			DialogExit();
			Patria_VisiterTortugaSail();
		break;
		
		case "noel_9":
			dialog.text = "Igen-igen, errôl mindenképpen beszámolunk Capsterville-ben. Egy ilyen fontos kolónia meghódításának veszélye... elképzelhetetlen, személyesen fogok gondoskodni arról, hogy Chevalier de Poincy szigorú és kíméletlen intézkedéseket hozzon! Kapitány, egy hétig maradok ezen a szigeten, rengeteg ültetvény van itt, idôbe telik.";
			link.l1 = "Értettem, báró úr. Hét nap múlva várom a kormányzói palotánál. Jó szórakozást, és ne dolgozza túl magát!";
			link.l1.go = "noel_10";
		break;
		
		case "noel_10":
			DialogExit();
			DoQuestReloadToLocation("PortPax_town", "reload", "reload3", "Patria_VisiterPortPax");
		break;
		
		case "noel_11":
			dialog.text = "Tessék, kapitány. A munkám Hipaniolán befejezôdött, ideje felhúzni a horgonyt.";
			link.l1 = "Értettem, báró. Azonnal indulunk.";
			link.l1.go = "noel_12";
		break;
		
		case "noel_12":
			DialogExit();
			Patria_VisiterPortPaxSail();
		break;
		
		case "noel_13":
			dialog.text = "Kapitány, ez a sziget ismerôsnek tûnik nekem. Ez nem a Szent Kristóf?";
			link.l1 = "Igen, báró úr, pontosan. Már majdnem ott vagyunk.";
			link.l1.go = "noel_14";
		break;
		
		case "noel_14":
			dialog.text = "Majdnem ott vagyunk?! Nem úgy volt, hogy Saint-Martinra is ellátogatunk? Az is a francia gyarmatokhoz tartozik.";
			link.l1 = "Sint Maartenre gondol? Az egy holland gyarmat, monsieur Forget.";
			link.l1.go = "noel_15";
		break;
		
		case "noel_15":
			dialog.text = "Tényleg? Párizsban úgy tekintették, hogy francia. Hogyhogy?";
			link.l1 = "Fogalmam sincs, báró úr. Amióta csak betettem a lábam a szigetvilágba, Sint Maarten holland gyarmat volt. Talán nem tudok valamit. Meg kellene beszélnie Chevalier de Poincyval errôl a kérdésrôl.";
			link.l1.go = "noel_16";
		break;
		
		case "noel_16":
			dialog.text = "Rendben, kapitány, legyen. Már majdnem Capsterville-ben vagyunk.";
			link.l1 = "...";
			link.l1.go = "noel_17";
		break;
		
		case "noel_17":
			DialogExit();
			Island_SetReloadEnableGlobal("Nevis", true);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 5.0);
			pchar.quest.Patria_visiter_fin.win_condition.l1 = "location";
			pchar.quest.Patria_visiter_fin.win_condition.l1.location = "Charles_Roomtownhall";
			pchar.quest.Patria_visiter_fin.function = "Patria_VisiterFin";
			pchar.questTemp.Patria = "epizode_2_return";
		break;
		
		case "noel_18":
			dialog.text = TimeGreeting()+", kapitány. Örülök, hogy látom. Hallottam, hogy elôléptették, kérem fogadja gratulációmat! Az igazat megvallva, ön valóban az egyik legértelmesebb és legtehetségesebb tiszt de Poincy szolgálatában.";
			link.l1 = "Köszönöm, uram.";
			link.l1.go = "noel_19";
		break;
		
		case "noel_19":
			dialog.text = "Végül, akkor már csak egy gyarmat maradt, Saint-Martin. Ôszintén szólva, már belefáradtam ezekbe az utazásokba. Örömmel fejezem be ezt a szemlét, és kezdem el a következô francia nyugat-indiai kereskedelmi hadjárat megszervezését. Készen állunk a horgony felszedésére?";
			link.l1 = "Igenis, báró úr. Szálljon be a fedélzetre.";
			link.l1.go = "noel_20";
		break;
		
		case "noel_20":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Patria_SanMartinBaron", 5.0);
		break;
		
		case "noel_21":
			dialog.text = "Kapitány, elmondaná, mi történt? Ez háborút jelent? Mi a fenéért süllyesztettek el minket majdnem a hollandok?";
			link.l1 = "Báró, én magam sem értek semmit! Biztos valami félreértésrôl van szó, semmi kétség.";
			link.l1.go = "noel_22";
		break;
		
		case "noel_22":
			dialog.text = "Kapitány, fogadni mernék, hogy ennek 'félreértésnek' van neve! Peter Stuyvesant, úgynevezett 'bérlô' a Saint-Martinból és a mi kedves Chevalier de Poincy társunk!";
			link.l1 = "Fogalmam sincs, báró úr. Jobb, ha sietünk Capsterville-be, és jelentjük ezt az ügyet a fôkormányzónak.";
			link.l1.go = "noel_23";
		break;
		
		case "noel_23":
			dialog.text = "Kétségtelenül pontosan ezt fogjuk tenni! És magyarázatot fogok követelni! Tudtam, hogy nagy hiba volt egy szigetet bérbe adni a hollandoknak! Tûnjünk el innen, amilyen gyorsan csak tudunk, kapitány, mielôtt valaki úgy dönt, hogy üldöz minket!";
			link.l1 = "Pontosan, monsieur...";
			link.l1.go = "noel_24";
		break;
		
		case "noel_24":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Patria_SanMartinBack", 5.0);
		break;
		
		case "noel_25":
			dialog.text = "Monsieur, elôször is hadd gratuláljak az elôléptetéséhez! Lelkesen támogattam monseigneur de Poincy döntését, hogy Önt admirális-helyettesi ranggal ruházza fel. Megérdemli ezt a címet! Nemrég tértem vissza Saint-Martinból. A Philipsburgi raktárakban revíziót végeztünk, minden holland árut elkoboztunk, és mostantól a francia kincstárhoz tartozik. Ön, mint a harci mûvelet parancsnoka, részesült a trófeákból. Egyetértek a Chevalierrel, hogy ez igazságos. Az ön áruit a Szent Kristóf áruház raktárába szállították, és bármikor átveheti ôket, amikor csak akarja.";
			link.l1 = "Köszönöm, báró úr. Hadd maradjanak ott az áruk egy ideig. Ha visszatérek Curacaóból, átveszem ôket.";
			link.l1.go = "noel_26";
		break;
		
		case "noel_26":
			dialog.text = "Sok szerencsét a következô hadjáratához, admirális-helyettes! Bízom benne, hogy gyôzelemmel tér vissza, és igazságosan megbünteti ezt a gazember Stuyvesantot.";
			link.l1 = "...";
			link.l1.go = "noel_27";
		break;
		
		case "noel_27":
			DialogExit();
			pchar.questTemp.Patria = "epizode_11_start";
			AddQuestRecord("Patria", "58");
			pchar.questTemp.Patria.GoodsSM = "true";
		break;
		
		case "noel_28":
			dialog.text = "Ki van itt nekünk! Charles de Maure ellentengernagy! Örülök, hogy látom! Mi dolga Kikötô-au-Prince-ben?";
			link.l1 = "Én is örülök, hogy megismerhetem, báró úr. Kötelességem miatt vagyok itt, udvariassági látogatást kellett tennem Jeremy Deschamps du Mussaca úrnál...";
			link.l1.go = "noel_29";
		break;
		
		case "noel_29":
			dialog.text = "Ez a találkozás valóban nagyon szerencsés, mert már régóta vártam arra, hogy személyesen találkozhassak önnel. Beszélni szeretnék önnel, de nem itt.";
			link.l1 = "Akkor menjünk a kocsmába, jó?";
			link.l1.go = "noel_30";
		break;
		
		case "noel_30":
			DialogExit();
			FreeSitLocator("PortPax_tavern", "sit_base1");
			DoQuestReloadToLocation("PortPax_tavern", "sit", "sit_base1", "Patria_CondotierTavern");
		break;
		
		case "noel_31":
			LAi_SetSitType(pchar);
			dialog.text = "Itt nincsenek nemkívánatos fülek, nyugodtan beszélgethetünk...";
			link.l1 = "Csupa fül vagyok, báró.";
			link.l1.go = "noel_32";
		break;
		
		case "noel_32":
			dialog.text = "Admirális-helyettes úr, ön becsületes embernek tûnik. Egy ilyen bátor tengerésztisztnek csak ilyennek kell lennie...";
			link.l1 = "Hmm... Nem hiszem, hogy teljesen megértettem önt, monsieur...";
			link.l1.go = "noel_33";
		break;
		
		case "noel_33":
			dialog.text = "Monsieur de Maure, azt akartam kérdezni: mit gondol hûbéruráról, Philippe de Poincy fôkormányzóról?";
			link.l1 = "A tisztnek nem az a kötelessége, hogy a parancsnokára gondoljon, hanem az, hogy kövesse a parancsait.";
			link.l1.go = "noel_34";
		break;
		
		case "noel_34":
			dialog.text = "Ó, hagyja csak, altábornagy úr, nem a laktanyában vagyunk, és nem a de Poincy-teremben. Mondom így: nem gondolja, hogy monsieur de Poincy... visszaél a hatalmával? Még mindig nem tudom elfelejteni, hogyan mentünk majdnem a lefolyóba a Saint-Martin erôd ágyúi alatt. Biztos vagyok benne, hogy a hollandok árulásának oka volt.";
			link.l1 = "Meg akarták hódítani a szigetet.";
			link.l1.go = "noel_35";
		break;
		
		case "noel_35":
			dialog.text = "Igen, igen, de miért pont abban a pillanatban, amikor úgy döntöttem, hogy megvizsgálom? Miért nem egy hónappal korábban? Vagy két hónappal késôbb? Nem hiszem, hogy ez véletlen volt, monseigneur. Nincs gyanúja? Mindketten az életünket kockáztattuk ott.";
			link.l1 = "Minden nap kockáztatom az életemet, monseigneur Forget. Azt hiszem, megérti, hogy...";
			link.l1.go = "noel_36";
		break;
		
		case "noel_36":
			dialog.text = "A bátorságához nem férhet kétség. De nem ezt akartam mondani. Tudja... Amikor a munkámat végeztem az önök által felszabadított Saint-Martinon, többször hallottam suttogást a helyiektôl valami bányáról a sziget mélyén. Próbáltam megkérdezni az embereket errôl, de csak hülyén viselkedtek. Féltek... Nyilvánvaló volt, hogy nem tûntem túl bizalomgerjesztônek, de ez csak megerôsítette a gyanúmat: lehet, hogy ez a titokzatos bánya az oka mindennek, Monsieur de Maure? A háborúkat az arany miatt vívják, igazam van?";
			link.l1 = "Számos bánya van a szigetvilágban. A legtöbbjüket kiürítették és értéktelenné váltak. Egyetlen nagy, mûködô aranybányáról tudok, ami a spanyolok tulajdonában van South Mainon. De Saint-Martinon soha nem hallottam aranybányászatról.";
			link.l1.go = "noel_37";
		break;
		
		case "noel_37":
			dialog.text = "Maga nagyon ért a beszédmûvészethez, admirális-helyettes! Értem: nem bízik bennem. Új vagyok itt... Monsieur de Maure, de Párizsban én vagyok a legjelentôsebb személy. A pénzügyminiszter a közeli barátom. Rendszeresen meglátogatom a királyt. Az én tekintélyem sokkal nagyobb, mint Philippe de Poincyé, természetesen formálisan, mert itt a fôkormányzó a legjogosabb személy. De az igazat megvallva, itt, a gyarmatokon a legerôsebb uralma az egyetlen szabály.";
			link.l1 = "Ebben teljesen egyetértek önnel.";
			link.l1.go = "noel_38";
		break;
		
		case "noel_38":
			dialog.text = "De nem így van ez Párizsban. Ott a legbefolyásosabb emberek a király és a pénzügyminiszter... az én közeli barátom. Monsieur de Maure, ön egy briliáns katona, de úgy vélem, hogy Phillip de Poincy a saját céljaira használja önt. Ön intelligens, ezért gyanakodnia kell. Bízhat bennem. Garantálom önnek a teljes titoktartást és a párizsi hatóságok támogatását. A címemre esküszöm.";
			link.l1 = "***HÛSÉGES MARADJON POINCYHOZ***";
			link.l1.go = "noel_39"; // развилка
			link.l2 = "***FELEJTSD EL A BÁRÓ PÁRTJÁT***";
			link.l2.go = "noel_53";
		break;
		
		case "noel_39":
			dialog.text = "";
			link.l1 = "Megértem önt, Monsieur Forger. A helyi gondolkodásmódot nem ismerô ember számára de Poincy tettei valóban furcsának tûnhetnek. Amikor elôször érkeztem a szigetvilágba, szó szerint sokkolt, ami itt történik. Még mindig emlékszem a legelsô szavakra, amelyeket mondtak nekem: 'Ha egy védtelen spanyol hajóval találkozik, megpróbálhat felszállni rá.' Elárulás, árulás, megtévesztés - ezek itt minden lépésnél jelen vannak. Kalózkodás, fosztogatás, rablás...";
			link.l1.go = "noel_40";
		break;
		
		case "noel_40":
			dialog.text = "";
			link.l1 = "Európában békében vagyunk Spanyolországgal. De itt ádáz ellenségek vagyunk. A hollandok ma barátságosnak és ártalmatlannak tûnnek, holnap pedig a Társaság tisztviselôje elkobozza az árudat, csak azért, mert hirtelen bejelentették, hogy tilos a behozatala, holott te ezt nem tudhattad. Az angol tiszt nyíltan kalózkodik, elsüllyeszti a Társaság hajóit, a Társaság pedig felbérel egy gyilkost, aki szellemhajónak álcázza magát, és rettegésben tartja az angol kereskedôket...";
			link.l1.go = "noel_41";
		break;
		
		case "noel_41":
			dialog.text = "";
			link.l1 = "Ebben a farkasbarlangban néha furcsa döntéseket kell hoznunk, amelyek nem egészen egyértelmûek egy mindezt nem ismerô ember számára. És ami számodra gyanúsnak tûnik, az valójában az egyetlen helyes cselekvés. Nehéz egyszerre több széken ülni, és mégis sikerül nyereséget küldeni az anyaállamnak. Chevalier de Poincy tökéletesen megbirkózik ezzel, tapasztalt menedzser és látnok politikus. Persze hibázhat, de hát mindannyian követünk el hibákat életünk egy bizonyos pontján...";
			link.l1.go = "noel_42";
		break;
		
		case "noel_42":
			dialog.text = "";
			link.l1 = "És számolni kell mindennel és mindenkivel. A spanyolok ambícióival, akik azt hiszik, hogy az egész Újvilág az övék, a holland kereskedôk kapzsiságával, az angolok hideg óvatosságával és kíméletlen brutalitásával. És még a kalózokkal is.";
			link.l1.go = "noel_43";
		break;
		
		case "noel_43":
			dialog.text = "Kalózokkal?!";
			link.l1 = "Igen, jól hallotta. A hollandok és az angolok aktívan együttmûködnek a kalózokkal... persze nem hivatalosan. A Parti Testvérek komoly erôt képviselnek, amely a régió bármelyik nemzetével kihívást jelenthet, állandó konfliktusban állnak mindenkivel, akivel csak találkoznak, és senki sem képes megállítani ôket. Az egyetlen dolog, ami egy kicsit kevésbé teszi ôket veszélyessé, az a tény, hogy szétszórtak, és a saját nevükben cselekszenek. Tudtad, hogy Tortuga egykori kormányzója, Levasseur tulajdonképpen államot hozott létre az államban, teljesen a kalózokra támaszkodva?";
			link.l1.go = "noel_44";
		break;
		
		case "noel_44":
			dialog.text = "Azt hiszem, hallottam errôl valamit...";
			link.l1 = "Tortuga kikötôjében állandóan kikötött néhány hatalmas magánhajó, amelyek a szigetet védték. Levasseur elárulta Franciaországot, és egyfajta helyi hatósággá vált. És most, miután a Tortugán lévô kalózfészket a mesterükkel együtt elpusztították, a kalózok szörnyen dühösek a franciákra...";
			link.l1.go = "noel_45";
		break;
		
		case "noel_45":
			dialog.text = "Ne is mondd!";
			link.l1 = "Igen. Meg kellett tennünk, különben Tortuga elveszett volna számunkra, bár az eredmény, amit elértünk, nem volt a legjobb. Most már egyetlen kereskedelmi francia hajó sem érezheti magát biztonságban a Karib-tengeren. A spanyolok, akiknek szintén nincs megállapodásuk a kalózbárókkal, legalább erôs gályákból és erôs hadihajókból álló flottával rendelkeznek, amelyek képesek visszaverni a filibustereket. Mint a hollandok a kelet-indiaiakkal és a Xebecekkel. De mi sajnos ilyesmivel nem büszkélkedhetünk. A francia kalózok pedig gyakran rabolják ki a francia kereskedôket.";
			link.l1.go = "noel_46";
		break;
		
		case "noel_46":
			dialog.text = "Ez ôrültség! Nem lehet ennek véget vetni?";
			link.l1 = "Sokan próbálkoztak már. A végén ahelyett, hogy harcolnának, arannyal vásárolják meg a hûségüket. Mármint a magánhajós szabadalmak kiadásával.";
			link.l1.go = "noel_47";
		break;
		
		case "noel_47":
			dialog.text = "Hmm...";
			link.l1 = "Szóval tapasztalatból szólva a francia kereskedelmi társaság itt a szigetvilágban nagyon rossz ötlet lenne. Most már érti, milyen nehézségekkel kell szembenéznie? Hány fattyú akar itt részesedni a bevételbôl? És nem fogják egykönnyen elengedni. És a kalózok, ôk elképzelhetetlen dolgokra képesek, nevezd ôket ôrültnek, ha akarod, de szinte mindig elérik a piszkos céljaikat? A kereskedelmi hajók védelméhez hatalmas katonai flottát kellene fenntartani, de vajon ez anyagi szempontból kifizetôdô lesz?";
			link.l1.go = "noel_48";
		break;
		
		case "noel_48":
			dialog.text = "De a francia kereskedôk itt valahogy boldogulnak?";
			link.l1 = "Pontosan, valahogy. Különösen most, amikor Levasseur kalózerôdjét Tortugán ostrom alá vették...";
			link.l1.go = "noel_49";
		break;
		
		case "noel_49":
			dialog.text = "Az ön szavai egybevágnak azzal, amit de Poincy mondott.";
			link.l1 = "Ez az igazság. Így van ez itt a szigetvilágban, mindig is így volt.";
			link.l1.go = "noel_50";
		break;
		
		case "noel_50":
			dialog.text = "Olyan buzgó vagy abban, amit mondasz. Még én sem tudtam sok mindent, és, igazad van: még mindig nem tudom. Azt hiszem, a Poincyval kapcsolatos gyanúm nem volt helytálló. Felnyitotta a szememet. Köszönöm, admirális-helyettes úr. De a francia miniszter a Társaság létrehozására számít. A királynak szüksége van a pénzre...";
			link.l1 = "Megértem. De kérem, vegye figyelembe, amit az imént mondtam, ha elkerülhetetlen a Francia Nyugat-India létrehozása, akkor kérem, gondoskodjon arról, hogy erôs katonai flottánk legyen, amely megvédi.";
			link.l1.go = "noel_51";
		break;
		
		case "noel_51":
			dialog.text = "Az ön kegyessége valóban csodálatra méltó, admirális-helyettes úr! Micsoda nemes vérmérséklet! Nem csodálom, hogy ilyen sokáig itt volt, és nem sietett haza. De majd még találkozunk: Fél év múlva visszatérek ide. A Francia Kereskedelmi Társaság felemelkedik. És a kalózokkal, azt hiszem, egy kicsit túlzol. Mindent egybevetve, vannak hadihajóink és bátor kapitányaink, mint például te.";
			link.l1 = "Sajnálom báró, de én csak egy ember vagyok, és rajtam kívül Franciaországnak csak egy erôs hajója van a szigetvilágban 'Eclatant', ez nem lesz elég, sokkal többet veszítünk, mint amennyit nyerünk.... Eh akármikor, ez van, ami van, gondolom addig is kitalálunk valamit... Mikor indulsz Franciaországba?";
			link.l1.go = "noel_52";
		break;
		
		case "noel_52":
			dialog.text = "Két hét múlva visszatérek Szent Kristófra, és onnan hazafelé veszem az irányt. Monsieur de Poincy adott nekem egy jó hajót - egy brigget, a 'Favory' és egy dicsô kapitányt. A hajó gyors, és a kapitány tapasztalt, de természetesen veled nagyobb biztonságban voltam. Emlékszem az utazásainkra a szigetvilágon keresztül, admirálishelyettes úr, valóban csodálatos élmény volt.";
			link.l1 = "Köszönöm kedves szavait, báró úr. Nos, azt hiszem, itt az ideje, hogy elváljunk...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Patria_CondotierToPirates");
		break;
		
		case "noel_53":
			dialog.text = "";
			link.l1 = "Itt mindenki kihasználja egymást. Chevalier már jóval azelôtt kihasznált engem a tetteihez, hogy a haditengerészet tisztje lettem volna.";
			link.l1.go = "noel_54";
		break;
		
		case "noel_54":
			dialog.text = "És ez elfogadható? Mit gondol?";
			link.l1 = "Nem. De a Chevalier nem hagyott más választást: vagy követem a parancsait, vagy a bátyám élete végéig rácsok mögött marad, és a családom jó hírneve tönkremegy.";
			link.l1.go = "noel_55";
		break;
		
		case "noel_55":
			dialog.text = "Szörnyû! Ez egyenesen terrorizmus! Volt valami oka az ilyen fenyegetésekre?";
			link.l1 = "A bátyámnak az volt a szerencsétlensége, hogy a megbízottja volt. Ahogy most én vagyok.";
			link.l1.go = "noel_56";
		break;
		
		case "noel_56":
			dialog.text = "Hol van most a bátyja?";
			link.l1 = "Sikerült kiszabadítanom, de már másnap elvesztettem, úgy döntött, hogy nem szolgál többé senki alatt.";
			link.l1.go = "noel_57";
		break;
		
		case "noel_57":
			dialog.text = "Tudtam, hogy Poincy nem az, akinek mondja magát! Farkas báránybôrben! Admirális-helyettes, bízhat bennem. Becsületes ember vagyok. És megmentem önt ettôl az igától 'patron' , ha kézzelfogható bizonyítékot találunk a bûnözôi tevékenységére. Tudsz valamit errôl az unalmas történetrôl Stuyvesantról? Beszélj nyíltan, és ne aggódj, te csak egy katona vagy, és kötelességed volt végrehajtani a parancsot.";
			link.l1 = "Tudom. Saint-Martinban valóban van egy bánya. Csak ott nem aranyat, hanem sót bányásznak. Nagy a kereslet a spanyolok részérôl. Poincy nem tudott közvetlenül kereskedni a spanyolokkal, ezért Stuyvesant közvetítôként mûködött.";
			link.l1.go = "noel_58";
		break;
		
		case "noel_58":
			dialog.text = "Tehát Poincy és Stuyvesant üzlettársak?";
			link.l1 = "Régen azok voltak. Miután kifejezte a Saint-Martin ellenôrzésére irányuló szándékát, Stuyvesant úgy döntött, hogy kiüti Poincyt a játékból, és maga viszi el a sóbányából származó összes hasznot. Poincy nem mondhatta el senkinek... De Stuyvesant elszámította magát, mint láthatjuk.";
			link.l1.go = "noel_59";
		break;
		
		case "noel_59":
			dialog.text = "Gondolod, hogy a bánya továbbra is mûködik?";
			link.l1 = "Ebben biztos vagyok. Úgy tûnik, hogy Poincy-nak most új kereskedelmi szövetségese van. Nem más, mint maga Doily ezredes.";
			link.l1.go = "noel_60";
		break;
		
		case "noel_60":
			dialog.text = "Tudunk bizonyítékot bemutatni a minisztériumnak?";
			link.l1 = "Hmm. A bánya megrohamozása során, amelyet egyébként spanyolok vezettek, nem hollandok, elfogtuk a tulajdonost. Még mindig a hajómon van. Beszélhet vele. Van rá esély, hogy a szabadságért cserébe sok érdekes dolgot fog mondani.";
			link.l1.go = "noel_61";
		break;
		
		case "noel_61":
			dialog.text = "Menjünk azonnal a hajójára. Parancsolja meg, hogy a foglyot szállítsák a kabinjába. Beszélni fogok vele.";
			link.l1 = "Rendben, menjünk.";
			link.l1.go = "exit";
			npchar.greeting = "noel_4";
			AddDialogExitQuestFunction("Patria_CondotierToCabin");
		break;
		
		case "noel_62":
			dialog.text = "Nagyszerû, admirális-helyettes úr. Beszélni fogok vele. Maradjon itt, kérem.";
			link.l1 = "Persze...";
			link.l1.go = "noel_63";
		break;
		
		case "noel_63":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "rld", "aloc1", "", -1);
			DoQuestFunctionDelay("Patria_CondotierInCabinTalk", 3.0);
		break;
		
		case "noel_64":
			dialog.text = "Leírtam a foglyotok összes bizonyítékát, és ô alá is írta. Most teljesítenünk kell, amit megígértem neki, amikor csak alkalmas alkalom adódik, álljunk meg Cartagenában, és engedjük, hogy partra szálljon. De te magad is hallottál mindent\nMicsoda gazember a mi Poincynk! Bérbe adott egy szigetet a hollandoknak, illegális tevékenységet folytatott ott, és megengedte a spanyoloknak, hogy odamenjenek és kezeljék a bányát! Félek elképzelni, mennyi pénz hiányzik a király kincstárából az ô önzése miatt!";
			link.l1 = "Vajon ez a bizonyíték elég lesz Poincy megvádolásához?";
			link.l1.go = "noel_65";
		break;
		
		case "noel_65":
			dialog.text = "Sajnos attól tartok, hogy nem. A bizonyíték nagyon fontos, de nem elég. De nem akarom, hogy belekeveredj ebbe az egészbe, mindketten megértjük az okokat.";
			link.l1 = "A spanyol beleegyezett, hogy tanúskodik a bizottsága elôtt, amikor az ideérkezik.";
			link.l1.go = "noel_66";
		break;
		
		case "noel_66":
			dialog.text = "Erre legkorábban hat hónap múlva kerül sor, és ki tudja, mi lesz ezzel a spanyollal, és megtaláljuk-e késôbb Cartagenában... Még több értékes bizonyítékra van szükségünk. Nevezetesen - bizonyíték arra, hogy a bánya folytatja titkos tevékenységét, és még mindig megtömi kedves fôkormányzónk zsebét.";
			link.l1 = "Tehát azt javasolja, hogy utazzunk Saint-Martinba?";
			link.l1.go = "noel_67";
		break;
		
		case "noel_67":
			dialog.text = "Igen. Tudja, hogy jutunk el a bányához?";
			link.l1 = "Igen, tudom.";
			link.l1.go = "noel_68";
		break;
		
		case "noel_68":
			dialog.text = "Aztán éjjel te és én beosonunk oda, csendben, hogy senki ne lássa, és megnézzük, mi folyik ott.";
			link.l1 = "Nagyon jó.";
			link.l1.go = "noel_69";
		break;
		
		case "noel_69":
			dialog.text = "De mi lesz a Chevalierrel? Most már értem, miért célzott nekem olyan bátran arra, hogy a francia kereskedelmi társaság létrehozása a szigetvilágon nem lenne nyereséges... Persze, hogy nagyon veszteséges lenne számára!";
			link.l1 = "Mivel most már szövetségesek vagyunk, báró úr, elmondom az igazat, Poincy megkért... hogy gyôzzem meg arról, hogy ne hozza létre itt a Kereskedelmi Társaságot.";
			link.l1.go = "noel_70";
		break;
		
		case "noel_70":
			dialog.text = "Szóval így áll a dolog! Remélem, hogy legalább nem arra kérte, hogy karddal vagy pisztollyal likvidáljon engem?";
			link.l1 = "Nem. Valami más módon kellett meggyôznie.";
			link.l1.go = "noel_71";
		break;
		
		case "noel_71":
			dialog.text = "Poincy fizetni fog ezért, de most azonnal Saint-Martinba kell hajóznunk. A spanyolokat utána átadjuk Main-nak. Indulunk, admirális-helyettes úr!";
			link.l1 = "Kicsit furcsának fog tûnni, hogy az én hajómon hagyja el a szigetet, nem gondolja?";
			link.l1.go = "noel_72";
		break;
		
		case "noel_72":
			dialog.text = "Nem hiszem. Nem kellett volna meggyôznie engem? Pontosan ezt tetted, haha! Igen, mielôtt Európába hajózunk, megmondom a lovagnak, hogy egyetértek az érveivel, és a Kereskedelmi Társaság nem jön létre. Hadd éljen egyelôre a hazugság boldog békéjében... Induljunk!";
			link.l1 = "...";
			link.l1.go = "noel_73";
		break;
		
		case "noel_73":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Patria_CondotierToSMartin", 5.0);
		break;
		
		case "noel_74":
			dialog.text = "Vezessen, admirális-helyettes. Az éjszaka elrejt minket a sötétség lepelével.";
			link.l1 = "Kövessenek...";
			link.l1.go = "noel_75";
		break;
		
		case "noel_75":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			pchar.quest.Patria_Condotier_inMine.win_condition.l1 = "location";
			pchar.quest.Patria_Condotier_inMine.win_condition.l1.location = "Location_reserve_03";
			pchar.quest.Patria_Condotier_inMine.function = "Patria_CondotierInMine";
		break;
		
		case "noel_76":
			dialog.text = "(suttogás) Láttam! Láttam! Láttad? Vöröskabátosok! Azok angol katonák!";
			link.l1 = "Megmondtam - Poincy most Doily ezredessel folytat üzletet.";
			link.l1.go = "noel_77";
		break;
		
		case "noel_77":
			dialog.text = "Igazad volt. Eleget láttam. Most pedig tûnjünk el innen, amilyen gyorsan csak tudunk, mielôtt észrevesznek!";
			link.l1 = "Egyetértek...";
			link.l1.go = "noel_78";
		break;
		
		case "noel_78":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			LAi_ActorRunToLocator(pchar, "reload", "reload2_back", "Patria_CondotierToBeach", -1);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
		break;
		
		case "noel_79":
			dialog.text = "Látod, hová vezetnek a 'kereskedelmi projektek' a mi kedves Chevalier-ünk! Az angolok úgy viselkednek, mint a házigazdák egy francia szigeten! Ez felháborító!";
			link.l1 = "El kell mennünk, különben valaki biztosan idejön. Nem engedhetjük meg magunknak, hogy felismerjenek minket.";
			link.l1.go = "noel_80";
		break;
		
		case "noel_80":
			dialog.text = "Admirálishelyettes úr, a Saint-Martin-i utazásunk alatt végig gondolkodtam, és valamit elhatároztam: el tudna nekem intézni egy találkozót Peter Stuyvesannal?";
			link.l1 = "Stuyvesant-tal? De miért?";
			link.l1.go = "noel_81";
		break;
		
		case "noel_81":
			dialog.text = "Egy volt üzlettársának komoly nyomai lehetnek, és komoly bizonyítékai Chevaliers' részvételére. Biztos vagyok benne, hogy Stuyvesant nem nagyon örül Poincy-nak, és bosszút akar állni, különösen a mostani események után...";
			link.l1 = "Azt hiszem, báró úr. Én személy szerint nem merek Stuyvesant palotájába menni. Túl kockázatos lenne számomra, azok után, amit velük tettem...";
			link.l1.go = "noel_82";
		break;
		
		case "noel_82":
			dialog.text = "Már gondoltam erre. Elmegyünk Curacaóba, partra szállunk egy, a várostól távol esô öbölben, és a bányából elküldjük a foglyul ejtett spanyolunkat egy levéllel együtt Stuyvesantnak. Ott nem fogom megemlíteni önt, helyette közlöm vele, hogy nyomozást vezetek Poincy ellen, vagy valami hasonlót. Azt hiszem, a holland eljön a randevúra.";
			link.l1 = "Hmm. Nem hiszem, hogy ez jó ötlet. A Stuyvesant nem bolond, elveszi, amit csak tud, talán még be is próbál bebörtönözni, és hatalmas váltságdíjat követel, de ha elhitetjük vele, hogy mindez Poincy miatt történt, akkor talán mellénk áll. Nos, ha ennyire elszántak vagytok, akkor próbáljuk meg.";
			link.l1.go = "noel_83";
		break;
		
		case "noel_83":
			DialogExit();
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("Shore40", "reload1_back", false);
			LocatorReloadEnterDisable("Shore40", "boat", false);
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_LocationDisableOfficersGen("shore40", false);
			LAi_LocationDisableOfficersGen("Location_reserve_01", false);
			LAi_LocationDisableOfficersGen("Location_reserve_03", false);
			pchar.quest.Patria_CondotierCuracao.win_condition.l1 = "location";
			pchar.quest.Patria_CondotierCuracao.win_condition.l1.location = "shore22";
			pchar.quest.Patria_CondotierCuracao.function = "Patria_CondotierOnCuracao";
			AddQuestRecord("Patria", "81");
		break;
		
		case "noel_84":
			dialog.text = "Monsieur de Maure, kérem, bocsássa meg ostobaságomat. Igaza volt Stuyvesant-tal kapcsolatban. Gondolhattam volna, hogy csak egy még nagyobb gazember hívhatta ki de Poincy-t!";
			link.l1 = "Hah! Egymillió... Poincy egymilliót akart, Stuyvesant egymilliót akar... Úgy tûnik, mintha körbe-körbe járnánk...";
			link.l1.go = "noel_85";
		break;
		
		case "noel_85":
			dialog.text = "Mirôl beszélsz, admirális-helyettes?";
			link.l1 = "Amikor megérkeztem a Karib-tengerre, Poincy azt akarta, hogy fizessek egymilliót váltságdíjként a bátyámért.";
			link.l1.go = "noel_86";
		break;
		
		case "noel_86":
			dialog.text = "És ennyit fizetett?";
			link.l1 = "Megdolgoztam érte, és kifizettem. Persze nem egy hónap alatt. Az igazat megvallva, akkoriban még csak egy szárazföldi csavargó voltam. Chevalier mégsem engedte el Michel-t.";
			link.l1.go = "noel_87";
		break;
		
		case "noel_87":
			dialog.text = "És ezután jelentkezett Poincy-nak dolgozni? Ôszintén szólva nem értem magát.";
			link.l1 = "Azért vonultam be, hogy Franciaországot és a szeretteimet szolgáljam, senki másnak nem engedelmeskedem, csak a királynak.";
			link.l1.go = "noel_88";
		break;
		
		case "noel_88":
			dialog.text = "Elnézést, Monsieur de Maure. Természetesen, ön Franciaországot és a királyt szolgálja! Poincy mindenért felelni fog! Beleértve minden fájdalmat, amit önnek okozott.";
			link.l1 = "Rendben, báró úr, találok egy milliót, amit meg tudok adni. Szálljon fel a fedélzetre... Megoldom ezt a problémát.";
			link.l1.go = "noel_89";
		break;
		
		case "noel_89":
			DialogExit();
			//chrDisableReloadToLocation = false; //17-add
			LAi_LocationFightDisable(&Locations[FindLocation("shore22")], false);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "sea", "none", "", "", "", 10.0);
			pchar.questTemp.Patria = "epizode_12_stivesant";
			AddQuestRecord("Patria", "83");
			if(bImCasual) NewGameTip("Felfedezô mód: az idôzítô nincs kikapcsolva. Tartsd be a határidôt!");
			SetFunctionTimerCondition("Patria_CondotierStivesantTimeOver", 0, 0, 30, false); // таймер на месяц
		break;
		
		case "noel_90":
			dialog.text = "Találkozni akart velem, admirális-helyettes?";
			link.l1 = "Igen. Találkozóm volt Stuyvesant-tal. Itt van a fôkönyve.";
			link.l1.go = "noel_91";
		break;
		
		case "noel_91":
			RemoveItems(pchar, "Reserve_item_01", 1);
			dialog.text = "Ezt nem hiszem el! Hmm, lássuk csak... (olvasás)";
			link.l1 = "...";
			link.l1.go = "noel_92";
		break;
		
		case "noel_92":
			LAi_Fade("", "");
			dialog.text = "Ez az! A mi drága Chevalier-ünknek végzete van. Amint ezt az egész könyvelést meglátja a pénzügyminiszter... El sem tudom képzelni, mi lesz vele. Még csak keresni sem kell majd a cartagenai spanyolt. Monsieur de Maure, tényleg milliókat fizetett ezért a könyvért?";
			link.l1 = "Igen. Ha mással próbálkozom, Franciaország elveszítheti a karibi gyarmatait egy polgárháború miatt, amit megnyerhetnék, de miféle admirális lennék, ha a saját népem ellen harcolnék.";
			link.l1.go = "noel_93";
		break;
		
		case "noel_93":
			dialog.text = "Ön valóban méltó a nevéhez. Esküszöm neked, admirális-helyettes, hogy visszaszerzed. Biztos vagyok benne, hogy Poincy ládáiban és uzsorásainál bôséges összeget fogunk találni. Csak arra kérem, hogy várjon hat hónapot, amíg visszatérek Európából egy megbízatással.";
			link.l1 = "És ne felejtsen el egy ezrednyi jól kiképzett és felfegyverzett katonát hozni. És egy olyan hajót, mint 'Eclatant'. Hiszem azt is, hogy aEclatant' kapitánya 'a mi oldalunkra áll, ha eljön az idô.";
			link.l1.go = "noel_94";
		break;
		
		case "noel_94":
			dialog.text = "Ne kételkedj benne, ô is becsületes ember. Rájöttem, hogy az erkölcsi értékek nagy szerepet játszanak a saját döntéseid meghozatalában. Nagyszerû munkát végeztél, hogy bíztál bennem és leleplezted ezt az állami bûnözôt. Most pedig vigyen el Capsterville-be, ahol beszámolok Poincy-nak a küldetésed sikerérôl - sikerült meggyôznöd, és lemondok a kereskedelmi társaság létrehozásának ötletérôl. Lehet, hogy Poincy még meg is jutalmazza ezért - nyugodt lelkiismerettel fogadja el a jutalmat, és ne aggódjon semmi miatt, éppen ön érdemelte meg. Nem fognak belerángatni ebbe az egészbe, és a neved nem lesz beszennyezve a felettesed vétkeivel, sôt, a legjobbakat fogom mondani rólad, amikor találkozom a királlyal. Forget báró becsületes ember, és állja a szavát.";
			link.l1 = "Ennek örülök, báró úr. Induljunk el!";
			link.l1.go = "noel_95";
		break;
		
		case "noel_95":
			DialogExit();
			chrDisableReloadToLocation = false;
			bQuestDisableMapEnter = false;//открыть карту
			Island_SetReloadEnableGlobal("Curacao", true);
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 5.0);
			pchar.questTemp.Patria = "epizode_12_baronwin";
			AddQuestRecord("Patria", "85");
			pchar.quest.Patria_CondotierBaron_win.win_condition.l1 = "location";
			pchar.quest.Patria_CondotierBaron_win.win_condition.l1.location = "Charles_town";
			pchar.quest.Patria_CondotierBaron_win.function = "Patria_CondotierBaronWin";
		break;
		
		case "noel_96":
			dialog.text = "Szóval, admirális-helyettes úr, végre megérkeztünk. A küldetésének vége, most már rajtam múlik. Menjen, intézze a saját ügyeit, védje meg Franciaország érdekeit, ahogyan eddig is tette. Körülbelül hat hónap múlva ez a hitvány történet véget ér. Elküldöm a futárt, hogy keressen meg, amikor szükség lesz rád. Viszontlátásra, Monsieur de Maure, nagy szerencsém volt, hogy itt egy becsületes emberrel találkoztam! A miniszter és a király hallani fog önrôl, ezt megígérem. És a legjobbakat fogják hallani.";
			link.l1 = "Köszönöm, báró úr. Bon Voyage!";
			link.l1.go = "noel_97";
		break;
		
		case "noel_97":
			DialogExit();
			AddQuestRecord("Patria", "86");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload3_back", "none", "", "", "OpenTheDoors", 15.0);
			SetFunctionTimerCondition("Patria_CondotierPuancieFinal", 0, 0, 1, false); // таймер
		break;
		
		case "noel_98":
			dialog.text = "Örülök, hogy látom, ellentengernagy úr. Újra itt vagyok, ahogy ígértem. És velem van a pénzügyminiszter elsô asszisztense, Olivier Bourdin báró.";
			link.l1 = "Hol van Chevalier de Poincy?";
			link.l1.go = "noel_99";
		break;
		
		case "noel_99":
			dialog.text = "Ahol lennie kellene, a börtönben. Letartóztatták, és Franciaországba viszik, hogy kivizsgálják és bíróság elé állítsák. Tekintettel a pozíciójára, a kivégzést biztosan elkerüli, de a hatalmas pénzbüntetést, a lefokozást és valószínûleg a börtönt nem kerülheti el.";
			link.l1 = "Békés volt a letartóztatás?";
			link.l1.go = "noel_100";
		break;
		
		case "noel_100":
			dialog.text = "Nem igazán. A Chevaliernek itt, a rezidencián egy egész ôrségnyi hûséges katonája volt. De mi elôre felkészültünk egy ilyen eszkalációra.";
			link.l1 = "Hát akkor gratulálok, báró úr! Talán most már a francia kereskedelmi társasággal fog foglalkozni?";
			link.l1.go = "noel_101";
		break;
		
		case "noel_101":
			dialog.text = "Én? Igen. Ôkegyelmessége Bourdin úr - Chevalier de Poincyval együtt megy vissza Franciaországba. És önnek, ellentengernagy úr, szintén számítania kell némi változásra. Mostantól új pozíciót kap. Ôméltósága majd többet fog mondani.";
			link.l1 = "...";
			link.l1.go = "noel_102";
		break;
		
		case "noel_102":
			DialogExit();
			LAi_SetActorType(npchar);
			sld = characterFromId("Finansist");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "noel_103":
			dialog.text = "Monsieur de Maure! Várjon egy percet!";
			link.l1 = "Igen, báró úr. Hallgatom.";
			link.l1.go = "noel_104";
		break;
		
		case "noel_104":
			dialog.text = "Ami az egymilliót illeti, amit a Stuyvesantnak fizetett... Errôl nem beszéltem a minisztériumnak, hogy... elkerüljem a kérdéseket, például, hogy egy francia tiszt hogyan jutott ennyi pénzhez. Ez káros lehetett volna számodra, mivel valószínûleg arra kérnének, hogy növeld a király' kincstárat a sajátoddal.";
			link.l1 = "Értem, köszönöm.";
			link.l1.go = "noel_105";
		break;
		
		case "noel_105":
			dialog.text = "Az összes pénzt, amit Poincy birtokában találtak Casterville-ben, Bourdin báró elkobozta. De mint kiderült, Poincy-nak volt egy rejtekhelye is, amelyet az angol uzsorások rejtettek el számára. Beszélni fogok vele a befektetések visszaszolgáltatásáról, és aztán megtalálom a módját, hogy kárpótoljam önt.";
			link.l1 = "Attól tartok, nem lesz könnyû dolga, hogy kivegyen valamit az angol uzsorások kezébôl.";
			link.l1.go = "noel_106";
		break;
		
		case "noel_106":
			dialog.text = "Egyetértek. De dolgozni fogunk rajta, és tájékoztatni fogom az eredményekrôl.";
			link.l1 = "Ahogy óhajtja.";
			link.l1.go = "noel_107";
		break;
		
		case "noel_107":
			dialog.text = "Admirálishelyettes úr, nem néz ki valami jól, vagy csak én látom így? Még csak most kapta meg a legmagasabb pozíciót a gyarmatokon!";
			link.l1 = "Nem, nem, egyáltalán nem... Csak minden olyan váratlanul történt, és egy kicsit elvesztettem a fonalat.";
			link.l1.go = "noel_108";
		break;
		
		case "noel_108":
			dialog.text = "Ne aggódjon. Majd megszokja az új helyzetét. És különben is, fél éven át elég sikeres voltál Saint-Martin kormányzójaként, úgyhogy ez nem lesz újdonság számodra.";
			link.l1 = "Ó, biztos vagyok benne, hogy meg fogom szokni. Voltam már rosszabb helyzetben is a Karib-tengeren töltött idôm alatt. Azt hiszem, ezt is meg fogom oldani.";
			link.l1.go = "noel_109";
		break;
		
		case "noel_109":
			// belamour legendary edition -->
			dialog.text = "Nos, rendben. Ráadásul van még egy meglepetésem a számodra. Biztos vagyok benne, hogy tetszeni fog. De elôbb megkérem, hogy menjen vissza a rezidenciára. Azt hiszem, valaki vár ránk ott.";
			link.l1 = "Ön lenyûgözött engem, Monsieur Forget. Nos, menjünk vissza.";
			link.l1.go = "noel_110";
		break;
		
		case "noel_110":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "ToEcliatonAward", -1);
			LAi_SetActorType(pchar);
			LAi_ActorFollow(pchar, npchar, "", -1);
		break;
		
		case "noel_111":
			dialog.text = "Minden rendben, Marquis. Egy igazi kapitánynak mindig a hajójáról kell elôször gondoskodnia, igaz? Charles, emlékszik Hubert Dassier márkira, a csatahajó kapitányára 'Eclatant'?...";
			link.l1 = "Persze, hogy emlékszem! Ha ô nem lett volna, ma már nem élnék. A legerôsebb barátság a tengerésztisztek között az egymás mellett vívott csatákból ered. És Monsieur Dassier-rôl kiderült, hogy hihetetlenül tapasztalt kapitány.";
			link.l1.go = "noel_112";
		break;
		
		case "noel_112":
			DialogExit();
			sld = characterFromId("Ecliaton_Cap");
			sld.dialog.currentnode = "ecliaton_cap_17";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "noel_113":
			dialog.text = "Admirális-helyettes úr, megtiszteltetés számomra, hogy a következôket közölhetem önnel. Amellett, hogy kineveztem önt a szigetvilág francia gyarmatainak megbízott fôkormányzójává, felvetettem a zászlóshajójának kérdését is.";
			link.l1 = "Zászlóshajó?";
			link.l1.go = "noel_114";
		break;
		
		case "noel_114":
			dialog.text = "Pontosan. Amennyire én tudom, amikor Franciaország szolgálatába állt, a könnyû fregatt 'Gryffondor' állt a rendelkezésére. Ez kétségtelenül csodálatos hajó, de mégis csak egy tisztnek való, nem pedig egy admirálishelyettesnek, és most már fôkormányzónak. Ön itt Franciaország arca. És a zászlóshajójának megfelelônek kell lennie. Ezért úgy döntöttünk, hogy az a hajó, amelyik az elsô csatáit itt a Karib-tengeren vívta, az ön századába kerül...";
			link.l1 = "Monsieur Forget, azt akarja mondani...";
			link.l1.go = "noel_115";
		break;
		
		case "noel_115":
			dialog.text = "Mostantól a francia haditengerészet büszkesége, a 66 ágyús hadihajó 'Eclatant' az Ön rendelkezésére áll! Ezt a döntést a király jóváhagyta!";
			link.l1 = "De báró úr, nem fogadhatom el csak úgy...";
			link.l1.go = "noel_116";
		break;
		
		case "noel_116":
			dialog.text = "De igen, Charles. Ezt nem szabad megvitatni. Franciaországban a 'Eclatant' egy kicsit kifejezetten neked fejlesztették, mert mint kiderült, a Karib-tengeren nincsenek olyan nagy tengeri csaták, mint Európában, és ezért az egyes hajókkal szemben magasabbak a követelmények. Itt mindent a hajó tulajdonságai és a kapitány tapasztalata dönt el. A 'Eclatant' megerôsítették a hajótestét, növelték a holtsúlyt és a legénység létszámát, kissé átépítették a vitorlázatot, hogy élesebb pályákat tudjon venni, és az összes ágyút is teljesen kicserélték negyvenkettes kaliberûre, ezek a legerôsebb ágyúk, amink van.";
			link.l1 = "Igen, most már ez a hajó egyszerûen a tengerek ura... De Monsieur Forget, mert ennek a hajónak a kapitánya Hubert Dassier márki. Nem vehetem el tôle...";
			link.l1.go = "noel_117";
		break;
		
		case "noel_117":
			dialog.text = "Csak azt nem mondtam még el önnek, hogy maga a márki is kifejezte erôs vágyát, hogy az ön parancsnoksága alatt szolgáljon... Monsieur Dassier?";
			link.l1 = "...";
			link.l1.go = "noel_118";
		break;
		
		case "noel_118":
			DialogExit();
			sld = characterFromId("Ecliaton_Cap");
			sld.dialog.currentnode = "ecliaton_cap_19";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "noel_119":
			dialog.text = "Igen, Monsieur Dassier, azt hiszem, nem tartjuk tovább fogva.";
			link.l1 = "...";
			link.l1.go = "noel_120";
		break;
		
		case "noel_120":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorTurnToLocator(pchar, "reload", "reload1");
			sld = characterFromId("Ecliaton_Cap");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "reload", "reload1", "EcliatonAwardNoelTalk", -1);
		break;
		
		case "noel_121":
			dialog.text = "Magunk között szólva, Charles, azt tanácsolom, hogy hagyja a márkit a szolgálatában. Biztosíthatom, hogy nem talál ilyen tapasztalt kapitányt.";
			link.l1 = "Higgye el, báró, volt szerencsém személyesen is meggyôzôdni róla a Spanyolország és Hollandia elleni harcok során. Monsieur Dassier valóban kiváló harcoló tiszt, és egyben a barátom is.";
			link.l1.go = "noel_122";
		break;
		
		case "noel_122":
			dialog.text = "Nos, engedje meg, hogy most elbúcsúzzam, kegyelmes fôkormányzó úr! A dolgok nem várhatnak: a kereskedelmi társaság létrehozásának munkálatai az elsô napon vannak. Hamarosan találkozunk!";
			link.l1 = "Sok szerencsét, Monsieur Forget. És sok szerencsét a kereskedelmi törekvéseihez!";
			link.l1.go = "noel_123";
		break;
		
		case "noel_123":
			DialogExit();
			// ставим Эклятон после апгрейда в Европе
			sld = characterFromId("Ecliaton_Cap");
			sld.dialog.currentnode = "ecliaton_cap_24";
			sld.DeckDialogNode = "ecliaton_cap_24";
			sld.Ship.Type = GenerateShipExt(SHIP_ECLIATON, true, sld);
			SetBaseShipData(sld);
			sld.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS42;
			UpgradeShipFull(sld);
			/* UpgradeShipParameter(sld, "SpeedRate");
			UpgradeShipParameter(sld, "TurnRate");
			UpgradeShipParameter(sld, "WindAgainstSpeed");
			UpgradeShipParameter(sld, "HP");
			UpgradeShipParameter(sld, "MaxCrew");
			sld.ship.HP = 11880; */
			sld.Ship.name = "Ecliaton";
			SetCrewQuantityFull(sld);
			AddCrewMorale(sld, 100);
			ChangeCrewExp(sld, "Sailors", 100);
			ChangeCrewExp(sld, "Cannoners", 100);
			ChangeCrewExp(sld, "Soldiers", 100);
			SetCharacterGoods(sld, GOOD_BALLS, 6000);
			SetCharacterGoods(sld, GOOD_GRAPES, 2000);
			SetCharacterGoods(sld, GOOD_KNIPPELS, 2000);
			SetCharacterGoods(sld, GOOD_BOMBS, 5000);
			SetCharacterGoods(sld, GOOD_FOOD, 4000);
			SetCharacterGoods(sld, GOOD_POWDER, 12000);
			SetCharacterGoods(sld, GOOD_WEAPON, 900);
			SetCharacterGoods(sld, GOOD_MEDICAMENT, 900);
			SetCharacterGoods(sld, GOOD_RUM, 200);
			SetCharacterGoods(sld, GOOD_PLANKS, 100);
			SetCharacterGoods(sld, GOOD_SAILCLOTH, 100);
			Group_AddCharacter("Ecliaton_group", "Ecliaton_Cap");
			Group_SetGroupCommander("Ecliaton_group", "Ecliaton_Cap");
			Group_SetAddress("Ecliaton_group", "Nevis", "quest_ships", "quest_ship_1");
			Group_SetTaskNone("Ecliaton_group");
			Group_LockTask("Ecliaton_group");
			
			bDisableFastReload = false;//открыть переход
			bQuestDisableMapEnter = false;//открыть карту
			AddQuestRecord("Patria", "90");
			CloseQuestHeader("Patria");
			DeleteAttribute(pchar, "questTemp.GoldenGirl_Block");	// Разрешаем квест Дороже Золота
			pchar.questTemp.Patria = "end"; // конец линейки
			pchar.questTemp.Patria.GenGovernor = "true"; // Шарль генерал-губернатор
			ChangeCharacterAddressGroup(npchar, "none", "", "");
			DoQuestReloadToLocation("Charles_Town", "reload", "reload3", "OpenTheDoors");
		break;
		// <-- legendary edition
		
		case "noel_final":
			dialog.text = "Engedje meg, hogy ôszinte elismerésemet fejezzem ki önnek, admirális-helyettes úr! Megmentette az életemet azzal, hogy megszabadított azoktól az átkozott kalózoktól. Köszönöm önnek és Philippe de Poincy-nak is. Be kell vallanom, hogy teljesen rosszul ítéltem meg ôt, és kérem, bocsásson meg nekem ezért. Önnek és a Chevaliernek igaza volt: a francia kereskedelmi társaságnak sok gondja lesz itt, és úgy néz ki, hogy itt csak pénzt veszíthetünk\nCsak tapasztalt emberek, mint Poincy, és olyan bátor katonák, mint önök, képesek ellenállni ezeknek a farkasoknak, akik itt minden szigeten élnek. El kell mennem a palotába, és utána minél elôbb Európába utazom, és elfelejtem ezt a rémálmot.";
			link.l1 = "Örülök, hogy minden jól végzôdött, báró úr. Viszontlátásra!";
			link.l1.go = "noel_final_1";
		break;
		
		case "noel_final_1":
			DialogExit();
			AddQuestRecord("Patria", "76");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload3_back", "none", "", "", "OpenTheDoors", 15.0);
			SetFunctionTimerCondition("Patria_CondotierPuancieFinal", 0, 0, 1, false); // таймер
		break;
		
		// капитан Эклятона
		case "ecliaton_cap":
			dialog.text = TimeGreeting()+", monsieur. Mi hozta önt a 'Eclatant fedélzetére?'?";
			link.l1 = TimeGreeting()+", ...monsieur. Engedje meg, hogy bemutatkozzam - Charles de Maure kapitány, a szigetvilág francia gyarmatainak fôkormányzójától, Chevalier de Poincy-tól jöttem. Parancsot kaptam, hogy vegyem a hajóját a századomba és a parancsnokságom alá. Itt van a levél...";
			// belamour legendary edition фикс проверки мундира с мушкетом
			if(IsUniformEquip()) link.l1.go = "ecliaton_cap_1";
			else link.l1.go = "ecliaton_cap_no";
		break;
		
		case "ecliaton_cap_no":
			dialog.text = "Ez valamiféle tévedés, monsieur. Ön a francia haditengerészet egyik hajóján áll, én pedig csak olyanok parancsaira hallgatok, akik a királyi haditengerészet szolgálatában állnak. Ön pedig nem úgy tûnik, mintha bármilyen jele lenne vagy tartozna ahhoz a flottához. Talán összetéveszti a hajónkat egy másikkal.";
			link.l1 = "De...";
			link.l1.go = "ecliaton_cap_no_1";
		break;
		
		case "ecliaton_cap_no_1":
			DialogExit();
			npchar.dialog.currentnode = "ecliaton_cap_no_2";
		break;
		
		case "ecliaton_cap_no_2":
			if(IsUniformEquip())
			{
				dialog.text = "Huh, még csak fel sem ismertem ebben az egyenruhában, kapitány úr. Nos, akkor hadd lássam a levelét, szeretném átnézni a tartalmát.";
				link.l1 = "Tessék.";
				link.l1.go = "ecliaton_cap_1";
			}
			else
			{
				dialog.text = "Már mindent megbeszéltünk, monseigneur...";
				link.l1 = "Hmm...";
				link.l1.go = "ecliaton_cap_no_1";
			}
		break;
		
		case "ecliaton_cap_1":
			RemoveItems(pchar, "Reserve_item_01", 1);
			dialog.text = "Nos, lássuk csak... (olvasás) Interesting. Szóval, én és a hajóm az ön parancsnoksága alá tartozunk, de Maure kapitány?";
			link.l1 = "Ez a fôkormányzó parancsa.";
			link.l1.go = "ecliaton_cap_2";
		break;
		
		case "ecliaton_cap_2":
			dialog.text = "Igen-igen, a parancsokat nem szabad megkérdôjelezni. Rendben van. Hadd mutatkozzam be: Hubert Dassier márki vagyok, a francia haditengerészet 66 ágyús hajójának, a 'Eclatant', nevû hajónak a kapitánya, ezzel a jól képzett legénységgel együtt, és becsületemre esküszöm, ez az egyik legjobb hajó, amivel Franciaország valaha rendelkezett.";
			link.l1 = "Örömmel hallom, mivel a fôkormányzótól kapott feladatunk jó navigációs és tüzérségi ismereteket igényel.";
			link.l1.go = "ecliaton_cap_3";
		break;
		
		case "ecliaton_cap_3":
			dialog.text = "Elmondaná a közelgô hadmûvelet részleteit?";
			link.l1 = "Természetesen. A spanyol Trinidad szigetére fogunk átköltözni, amely innen körülbelül egy hétre délkeletre található. Hirtelen megtámadjuk a San José kolóniát ôrzô erôdöt, és a földdel együtt a földbe döngöljük. Aztán megbeszéljük a spanyolokkal, hogy kárpótoljuk ôket a Saint-Pierre francia település elleni nemrégiben történt támadásért.";
			link.l1.go = "ecliaton_cap_4";
		break;
		
		case "ecliaton_cap_4":
			dialog.text = "Értem. Mikor indulunk?";
			link.l1 = "Amilyen hamar csak lehet. Egy hónapon belül be kell fejeznünk ezt a feladatot, így több mint elég idônk van.";
			if (GetCompanionQuantity(pchar) > 4) link.l1.go = "ecliaton_cap_5_1";
			else link.l1.go = "ecliaton_cap_5";
		break;
		
		case "ecliaton_cap_5":
			dialog.text = "Rendben, de Maure kapitány. A parancsára indulunk.";
			link.l1 = "";
			link.l1.go = "ecliaton_cap_6";
		break;
		
		case "ecliaton_cap_6":
			DialogExit();
			npchar.dialog.currentnode = "ecliaton_cap_wait";
			npchar.DeckDialogNode = "ecliaton_cap_wait";
			Patria_AddEcliaton();
		break;
		
		case "ecliaton_cap_wait":
			dialog.text = "Van bármilyen parancsa, vagy esetleg kérdése, de Maure kapitány?";
			link.l1 = "Még nem...";
			link.l1.go = "ecliaton_cap_wait_1";
		break;
		
		case "ecliaton_cap_wait_1":
			DialogExit();
			npchar.dialog.currentnode = "ecliaton_cap_wait";
			npchar.DeckDialogNode = "ecliaton_cap_wait";
		break;
		
		case "ecliaton_cap_5_1":
			dialog.text = "De, de Maure kapitány, elôször is kisebbre kell szabnia a századát - az én hajóm nem csatlakozhat önökhöz, különben túl nagy lesz a század.";
			link.l1 = "Huh. Igazad van. Egy hajót itt hagyok a kikötôben.";
			link.l1.go = "ecliaton_cap_5_2";
		break;
		
		case "ecliaton_cap_5_2":
			DialogExit();
			npchar.dialog.currentnode = "ecliaton_cap_5_3";
		break;
		
		case "ecliaton_cap_5_3":
			if (GetCompanionQuantity(pchar) > 4)
			{
				dialog.text = "Nem csökkentette még a hajóraját, monsieur?";
				link.l1 = "Igen, igen, emlékszem, dolgozom rajta.";
				link.l1.go = "ecliaton_cap_5_2";
			}
			else
			{
				dialog.text = "Tehát az 'Eclatant' készen áll, hogy csatlakozzon a századához, monsieur.";
				link.l1 = "Akkor én megyek a hajómra, ön pedig készüljön fel a tengerre.";
				link.l1.go = "ecliaton_cap_5";
			}
		break;
		
		case "ecliaton_cap_7":
			dialog.text = "Üdvözlöm, kapitány. Újabb csata vár ránk?";
			link.l1 = "Valóban. Még egyszer egyesítjük erôinket. Megrohamozzuk Philipsburgot. A fôkormányzó megbízott minket a hollandok kiûzésével Saint-Martinból.";
			link.l1.go = "ecliaton_cap_9";
			link.l2 = "A kapitányt, de egy kicsit késôbb. Majd megmondom, mikor. A 'Eclatant' bármelyik percben készen állhat a tengerre lépésre.";
			link.l2.go = "ecliaton_cap_8";
		break;
		
		case "ecliaton_cap_8":
			DialogExit();
			npchar.dialog.currentnode = "ecliaton_cap_7";
			npchar.DeckDialogNode = "ecliaton_cap_7";
		break;
		
		case "ecliaton_cap_9":
			dialog.text = "Minden tiszta. Nehéz küldetés lesz, monseigneur. Amennyire hallottam, a Philipsburgi erôdnek rengeteg ágyúja van.";
			link.l1 = "Biztos vagyok benne, barátom, de meg fogjuk oldani. Készüljetek a tengerre, hamarosan indulunk.";
			link.l1.go = "ecliaton_cap_10";
		break;
		
		case "ecliaton_cap_10":
			DialogExit();
			npchar.dialog.currentnode = "ecliaton_cap_wait";
			npchar.DeckDialogNode = "ecliaton_cap_wait";
			Patria_BastionAddEcliaton();
		break;
		
		case "ecliaton_cap_11":
			dialog.text = "Örülök, hogy a 'Eclatant', ellentengernagy fedélzetén látlak! Mik a parancsai?";
			link.l1 = "Készítse fel a 'Eclatantaz indulásra. Elôször Jamaica partjaihoz hajózunk, majd D' Oyley ezredes hajórajával együtt megtámadjuk Curacaót.";
			link.l1.go = "ecliaton_cap_13";
			link.l2 = "Lesznek parancsok, kapitány, de késôbb. Majd én megmondom, mikor. A 'Eclatant' bármelyik percben készen kell állnia a tengerre lépésre.";
			link.l2.go = "ecliaton_cap_12";
		break;
		
		case "ecliaton_cap_12":
			DialogExit();
			npchar.dialog.currentnode = "ecliaton_cap_11";
			npchar.DeckDialogNode = "ecliaton_cap_11";
		break;
		
		case "ecliaton_cap_13":
			dialog.text = "Az 'Eclatant' és legénysége készen áll, admirális-helyettes úr!";
			link.l1 = "Kitûnô. Akkor azonnal indulunk.";
			link.l1.go = "ecliaton_cap_14";
		break;
		
		case "ecliaton_cap_14":
			DialogExit();
			npchar.dialog.currentnode = "ecliaton_cap_wait";
			npchar.DeckDialogNode = "ecliaton_cap_wait";
			Patria_CuracaoAddEcliaton();
		break;
		
		// belamour legendary edition -->
		case "ecliaton_cap_15":
			dialog.text = "Elnézést uraim, nem tudtam korábban csatlakozni önökhöz, mert a hajón lévô parancsok kiadásával voltam elfoglalva. Már azt hittem, hogy eléggé elkéstem, mert nem találtam önöket a rezidencián, és ezért vissza akartam térni a hajóra...";
			link.l1 = "...";
			link.l1.go = "ecliaton_cap_16";
		break;
		
		case "ecliaton_cap_16":
			DialogExit();
			Lai_SetPlayerType(pchar);
			sld = characterFromId("Noel");
			sld.dialog.currentnode = "noel_111";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "ecliaton_cap_17":
			dialog.text = "Megtiszteltetés volt ön mellett harcolni, Monsieur de Maure! Azt kell mondanom, hogy ritkán találkozom ilyen hozzáértô és ügyes tisztekkel, mint ön. Biztos vagyok benne, hogy én magam nem tudtam volna ilyen gyorsan elbánni annak a trinidadi spanyol kolóniának az erôdjével!";
			link.l1 = "Alábecsüli magát, Monsieur Dassier. Együtt birkóztunk meg vele.";
			link.l1.go = "ecliaton_cap_18";
		break;
		
		case "ecliaton_cap_18":
			DialogExit();
			sld = characterFromId("Noel");
			sld.dialog.currentnode = "noel_113";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "ecliaton_cap_19":
			dialog.text = "Igen, így van. Bár márki vagyok, mégis tengerész vagyok. Számomra a karibi szigetvilág új, feltáratlan és tele van új kalandokkal. Legutóbb csak néhány hónapig voltam itt, de amikor visszatértem Európába, elkezdett hiányozni ez a hely. Szeretném itt szolgálni a hazánkat. Ön pedig egy nagyon tehetséges és tapasztalt kapitány, sikerült elnyernie ôszinte tiszteletemet és barátságomat. Megtiszteltetés lenne az Ön parancsnoksága alatt szolgálni, admirális-helyettes úr!";
			link.l1 = "Nos, én nem tudok, és mi több! - Nem akarom visszautasítani önt, Monsieur Dassier!";
			link.l1.go = "ecliaton_cap_20";
		break;
		
		case "ecliaton_cap_20":
			dialog.text = "Azt is megértem, hogy az Eclatant most az ön zászlóshajója, így tökéletesen megértem, ha úgy dönt, hogy személyesen veszi át a parancsnokságot. Ebben az esetben meghagyhat engem tisztjének, adhat nekem egy másik hajót, vagy egyszerûen felmenthet a kötelességeim alól - Monsieur Forget kedvesen megígérte nekem, hogy akkor majd talál nekem egy méltó állást a Francia Nyugat-indiai Társaság flottájában.";
			link.l1 = "Biztosíthatom barátom, hogy erre nem fog sor kerülni. Ön az egyik legjobb kapitány, akivel valaha találkoztam, és önnel az oldalamon megállíthatatlanok leszünk.";
			link.l1.go = "ecliaton_cap_21";
		break;
		
		case "ecliaton_cap_21":
			dialog.text = "Köszönöm, hogy ilyen hízelgôen értékeli képességeimet. És még valami, admirális-helyettes úr. Jelenleg nem tudom, mekkora az ön hajórajának létszáma, ezért a biztonság kedvéért a capsterville-i mólónál, az Eclatant kapitányi hídján várom önt. Amint úgy döntesz, hogy a parancsnokságod alá veszed a hajót - csak szólj.";
			link.l1 = "Rendben, Monsieur Dassier.";
			link.l1.go = "ecliaton_cap_22";
		break;
		
		case "ecliaton_cap_22":
			dialog.text = "Akkor engedélyt kérek a távozásra. Admirális-helyettes, báró...";
			link.l1 = "Hamarosan találkozunk, Monsieur Dassier.";
			link.l1.go = "ecliaton_cap_23";
		break;
		
		case "ecliaton_cap_23":
			DialogExit();
			sld = characterFromId("Noel");
			sld.dialog.currentnode = "noel_119";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
	
		case "ecliaton_cap_24":
			dialog.text = "Admirális-helyettes, üdvözlöm a fedélzeten. Szeretné az Eclatantot a parancsnoksága alá venni?";
			if (GetCompanionQuantity(pchar) > 4)
			{
				
				link.l1 = "Még nem, márki. Várjon a parancsra.";
				link.l1.go = "ecliaton_cap_24_1";
			}
			else
			{
				link.l1 = "Igen, márki, kérem, csatlakozzon a századomhoz. Ez a gyönyörû hajó Franciaország nagyságának és hatalmának jelképe lesz a Karib-tengeren!";
				link.l1.go = "ecliaton_cap_25";
			}
		break;
		
		case "ecliaton_cap_24_1":
			DialogExit();
			npchar.dialog.currentnode = "ecliaton_cap_24";
			npchar.DeckDialogNode = "ecliaton_cap_24";
		break;
		
		case "ecliaton_cap_25":
			dialog.text = "Egyetértek, excellenciás uram!";
			link.l1 = "... Most pedig lássuk, mire vagyunk igazán képesek!";
			link.l1.go = "ecliaton_cap_26";
		break;
		
		case "ecliaton_cap_26":
			DialogExit();
			DeleteAttribute(npchar, "ShipHideImmortal");
			SetCharacterRemovable(npchar, true);
			npchar.CompanionEnemyEnable = true; 
			npchar.Dialog.Filename = "Enc_Officer_dialog.c";
			npchar.Dialog.CurrentNode = "hired";
			npchar.DeckDialogNode = "hired";
			SetCompanionIndex(pchar, -1, sti(npchar.index));
			npchar.Payment = true;
			npchar.loyality = MAX_LOYALITY;
			npchar.OfficerWantToGo.DontGo = true;
			
			// удаление группы Эклятона, иначе клон-призрак
			pchar.quest.Patria_EcliatonDelGroup.win_condition.l1 = "ExitFromSea";
			pchar.quest.Patria_EcliatonDelGroup.function = "Patria_EcliatonDelGroup";
		break;
		// <-- legendary edition
		
		// д'Ойли на Антигуа
		case "doily":
			if (CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "end" && colonies[FindColony("Pirates")].nation == PIRATE)
			{
				PlaySound("Voice\English\LE\Doily\Edvard_Doily_01.wav");
				dialog.text = "Ó, micsoda ismeretség! Hát nem maga Charles de Maure kapitány?! Úgy hallottam, hogy ön most a francia haditengerészetnél van. Micsoda meglepetés, tekintve, hogy korábban, mondjuk, 'dolgozott' ...";
				link.l1 = "Üdvözlöm, uram. Az Isla Tesoro-ügyrôl beszél? Ó, de nem én írtam meg az angol törvényeket, amelyek szerint a sziget a felfedezô örökösére szállt, aki végrendelete szerint megtalálta. Tehát ebben nem vagyok bûnös, csak segítettem Miss Sharpnak, hogy megkapja azt, ami jog szerint az övé.";
				link.l1.go = "doily_1";
			}
			else
			{
				dialog.text = TimeGreeting()+", kapitány. Gondolom, a francia haditengerészet képviselôje fontos céllal érkezett Antiguára?";
				link.l1 = "Valóban, uram. A francia gyarmatok fôkormányzója, Philippe de Poincy küldött ide. Saint-Christopher-t a spanyol és a holland haditengerészet századai ostromolják. A Chevalier az ön és Sir Jonathan Fox segítségét is kéri. Itt a levele az ön számára, ezredes úr.";
				link.l1.go = "doily_3";
			}
		break;
		
		case "doily_1":
			dialog.text = "Kíváncsi vagyok, kapitány úr, mennyi pénzt keresett ezzel? Gondolom, elég sokat, hiszen sikerült kifizetnie a gazember Loxley szolgálatait, amelyek egyáltalán nem olcsók. Biztos vagyok benne, hogy a kalózbárók rendszeresen fizetnek önnek levonásokat, amiért a szigetet a birtokukban tartják. Mindketten pontosan tudjuk, hogy Helen Sharp csak egy álarc.";
			link.l1 = "Ezredes, azt is mindketten tudjuk, hogy a kalózbárók többnyire Anglia érdekében tevékenykednek, nem hivatalosan, ne feledje... Nélkülük elég nehéz lenne ellenállni a spanyolok hegemóniájának a térségben, nem gondolja? Tehát a politikusok szemszögébôl nézve az, hogy a Parti Testvérek megtartották maguknak a szigetet, talán még jövedelmezôbb is volt, mintha az Isla Tesoro angol haditengerészeti támaszpont lett volna...";
			link.l1.go = "doily_2";
		break;
		
		case "doily_2":
			dialog.text = "Ez vitathatatlanul igaz, kapitány, de... legyen, ahogy van. Gondolom, valami fontos céllal érkezett Antiguára? Talán ahhoz van köze, hogy a két korábbi szövetséges - Franciaország és Hollandia - viszonya jelentôsen megromlott?";
			link.l1 = "Így van. A francia gyarmatok fôkormányzója, Philippe de Poincy küldött. Saint-Christophert a spanyol és a holland haditengerészet ostromolja. A Chevalier a segítségét kéri. Itt a levele önnek, ezredes.";
			link.l1.go = "doily_3";
		break;
		
		case "doily_3":
			RemoveItems(pchar, "Reserve_item_01", 1);
			dialog.text = "Lássuk csak... (olvasás)";
			link.l1 = "";
			link.l1.go = "doily_3_1";
		break;
		
		case "doily_3_1":
			LAi_Fade("", "");
			dialog.text = "Hmm... nagyon érdekes! Kapitány, a parancsnoka tudja, hogyan keltse fel az érdeklôdésemet, nem olyan szokatlan, hogy az emberek ravasz rókának nevezik. Ezt már régen meg kellett volna tennünk, ahelyett, hogy a hollandokkal próbálunk barátkozni. Mivel nagyon jól tudjuk, hogy mit képvisel a holland társaság és az igazgatójuk. Nos, akkor úgy gondolom, hogy ebben a helyzetben tényleg nem kellene megtagadnunk a segítséget az ostromlott Casterville-tôl, és több mint elég csapatunk van ahhoz, hogy ezt lehetôvé tegyük.\nMilyen számú és típusú hajók vannak a századukban, kapitány?";
			link.l1 = "Hat hajót számoltam meg: egy nyolcvanágyús, harmadosztályú hadihajót és öt negyedosztályú hajót. Lehetnek még fregattjaik és gályáik is.";
			link.l1.go = "doily_4";
		break;
		
		case "doily_4":
			dialog.text = "Hmm... A mi századunkat, amely egy százágyús elsô osztályú hajóból, két negyedosztályú hajóból és egy nehéz fregattból áll, az övék ellen állíthatjuk.";
			if (!CheckAttribute(pchar, "questTemp.Patria.FailLugger"))
			{
				link.l1 = "Uram, van egy 66 ágyús hadihajónk is, a 'Eclatant', a Saint-Christopher védelem segítségére hajózik Guadeloupe partjairól.";
				link.l1.go = "doily_5";
			}
			else
			{
				link.l1 = "Az elsô osztályú hajó nagy segítség lesz a közelgô csatában.";
				link.l1.go = "doily_5_1";
			}
		break;
		
		case "doily_5":
			dialog.text = "Tökéletes. Ebben az esetben jóval az ellenségünk' tüzelési képessége felett vagyunk. A gyôzelem a miénk lesz.";
			link.l1 = "És ne feledkezzünk meg a saját hajómról sem, uram. Nem fogok kihagyni egy ilyen csatát, eszembe se jusson.";
			link.l1.go = "doily_6";
		break;
		
		case "doily_5_1":
			dialog.text = "Ez igaz. A casterville-i erôd segítségével együtt a gyôzelem a miénk lesz.";
			link.l1 = "És ne feledkezzünk meg a saját hajómról sem, uram. Nem fogok kihagyni egy ilyen csatát, eszembe se jusson.";
			link.l1.go = "doily_6";
		break;
		
		case "doily_6":
			dialog.text = "Természetesen, monsieur de Maure. Akárhogy is legyen, a szigetvilágban mindenütt hallani lehet az ön vitorlázó tehetségérôl szóló történeteket. Az ön zászlóshajója fogja vezetni az osztagot.";
			if (GetCompanionQuantity(pchar) > 1)
			{
				link.l1 = "Én a hajórajom többi hajóját várakoztatom, aztán visszajövök önhöz, és az ostromlottak segítségére sietünk.";
				link.l1.go = "doily_7_1";
			}
			else
			{
				link.l1 = "Hamarosan elôkészítem a hajómat, és az ostromlottak segítségére sietünk.";
				link.l1.go = "doily_8";
			}
		break;
		
		case "doily_7_1":
			DialogExit();
			npchar.dialog.currentnode = "doily_7_2";
		break;
		
		case "doily_7_2":
			dialog.text = "Szóval, készen állsz az indulásra?";
			if (GetCompanionQuantity(pchar) > 1)
			{
				link.l1 = "Várjon még egy kicsit, uram.";
				link.l1.go = "doily_7_1";
			}
			else
			{
				link.l1 = "Igenis, uram.";
				link.l1.go = "doily_8";
			}
		break;
		
		case "doily_8":
			dialog.text = "Akkor induljunk, és Isten segítsen minket!";
			link.l1 = "...";
			link.l1.go = "doily_9";
		break;
		
		case "doily_9":
			DialogExit();
			npchar.dialog.currentnode = "doily_10";
			chrDisableReloadToLocation = true;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", -1);
			AddQuestRecord("Patria", "42");
			Patria_SiegeAddEngSquadron();
		break;
		
		case "doily_10":
			dialog.text = "Van még kérdése, uram?";
			link.l1 = "Nincs, ezredes úr...";
			link.l1.go = "doily_11";
		break;
		
		case "doily_11":
			DialogExit();
			npchar.dialog.currentnode = "doily_10";
			npchar.DeckDialogNode = "doily_10";
		break;
		
		case "doily_12":
			PlaySound("Voice\English\LE\Doily\Edvard_Doily_02.wav");
			dialog.text = "Hozza a levelet a Stuyvesantnak, uram. Ha nem tudja, ki vagyok, hadd mutatkozzam be: Edward Doily ezredes, Kikötô-Royal kormányzója és ennek az expedíciónak a parancsnoka!\nAz igazat megvallva, nagy késztetést érzek arra, hogy a földdel tegyem egyenlôvé a Willemstad nevû banditák rejtekhelyét. A Karib-tenger legelvetemültebb, legkétszínûbb és legaljasabb szervezete, a Holland Nyugat-indiai Kereskedelmi Társaság, amely úgy gondolja, hogy a szigetvilágban minden kereskedelem kizárólag az ô joguk, és amely olyanokat bérel fel, mint Jacob van Berg és más kalózok, hogy elfogják és elsüllyesszék az angol kereskedôk hajóit...";
			link.l1 = "...";
			link.l1.go = "doily_13";
		break;
		
		case "doily_13":
			dialog.text = "Azért vagyok itt, hogy véget vessenek ezeknek a felháborító cselekedeteknek, és szerencséjükre diplomáciai utat javaslok. Egyelôre... De ha ennek a förtelmes szervezetnek az igazgatója nem érkezik ide a tárgyalásokra, akkor a földbe döngölöm az üzletét. Miután megrohamoztuk a várost, csak hamut hagyok hátra, és minden puskaport, amit találunk, az erôd pincéjébe rakunk, és felrobbantjuk. Ugyanez a sors vár majd az ültetvényeikre is, és maga Stuyvesant fog lógni a zászlóshajóm árbocán...";
			link.l1 = "...";
			link.l1.go = "doily_14";
		break;
		
		case "doily_14":
			dialog.text = "Több mint egy évre lesz szükséged ahhoz, hogy újjáépítsd a kolóniádat, és akkor már nem lesz idôd a terveidre és cselszövéseidre. Mondjátok el 'Mynheer igazgató' mindent, amit az imént mondtam, és ne higgyétek, hogy ezek csak viccek és üres ígéretek. Elfogyott a türelmem, úgyhogy tökéletesen meg kell értenetek engem. Megértette, biztos úr?!";
			link.l1 = "Minden tökéletesen világos, ezredes úr.";
			link.l1.go = "doily_15";
		break;
		
		case "doily_15":
			dialog.text = "Nagyszerû. Akkor menjen el. Pontosan egy napot adok, hogy átgondolja ezt. Ha huszonnégy óra múlva Peter Stuyvesant nem úgy fog itt állni, mint most ön, akkor azt okolja magának.";
			link.l1 = "...";
			link.l1.go = "doily_16";
		break;
		
		case "doily_16":
			DialogExit();
			LAi_SetStayType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			bDisableCharacterMenu = false;//лоченые интерфейсы
			sld = characterFromId("Doily_land");
			sld.dialog.currentnode = "doily_17";
			LAi_SetActorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "doily_17":
			dialog.text = "Szerintem az a csörgô kutya Stuyvesant ide fog jönni. És ha nem - csak magát okolhatja!";
			link.l1 = "...";
			link.l1.go = "doily_17_1";
		break;
		
		case "doily_17_1":
			DialogExit();
			npchar.dialog.currentnode = "doily_17";
			AddQuestRecord("Patria", "63");
			Patria_CuracaoParlamenterGo();
		break;
		
		case "doily_18": // д'Ойли на берегу
			dialog.text = "Jó munkát végzett az erôddel, monsieur de Maure. Most a szárazföldön közelítjük meg a város kapuit. Én innen elviszem az ágyúkat, az út itt rövidebb és könnyebb, ön pedig a Santa-Maria-foknál leszállítja a tengerészgyalogosok századát, és elindul Willemstad felé. Ha útközben ellenséggel találkozol, tudod, mit kell tenned. Senki sem maradhat mögöttünk.";
			link.l1 = "Természetesen, ezredes úr. A kapuknál találkozunk!";
			link.l1.go = "doily_19";
		break;
		
		case "doily_19":
			DialogExit();
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			AddQuestRecord("Patria", "61");
			npchar.dialog.currentnode = "doily_10";
			Patria_CuracaoGotoMarch();
		break;
		
		case "doily_20":
			dialog.text = "Nos, akkor úgy tûnik, hogy a küldetésünk elég sikeresen véget ért. Gratulálok, kapitány! Ó, elnézést - admirális-helyettes! Menjünk vissza a hajókra. Megmondom az embereimnek, hogy álljanak ôrt - az a bolond Stuyvesant valószínûleg nem fogja megkockáztatni, hogy megtámadjon minket, amíg mi visszavonulunk, de nem árt az óvatosság.";
			link.l1 = "Biztos vagyok benne, hogy a hollandok nem mernek megszegni egy most aláírt szerzôdést.";
			link.l1.go = "doily_21";
		break;
		
		case "doily_21":
			dialog.text = "Öröm volt önnel dolgozni, Monsieur de Maure. Azt hiszem, még egyszer találkozunk Kikötô-Royalban vagy Capsterville-ben.";
			link.l1 = "Kétségtelenül, ezredes úr. Most pedig szóljunk az embereinknek, hogy vonuljanak vissza.";
			link.l1.go = "doily_22";
		break;
		
		case "doily_22":
			DialogExit();
			AddQuestRecord("Patria", "64");
			Patria_CuracaoClear();
		break;
		
		case "doily_23":
			dialog.text = "Úgy tûnik, a hollandok végre megtanulták, hogy a tüzérségünk tüze alatt nem tudnak megközelíteni minket az erôdbôl azon a keskeny ösvényen. A városban rekedtek pedig valószínûleg nem kockáztatják meg a támadást, hacsak nem ôrültek meg teljesen. Most pedig szítsunk némi pánikot: bombázzuk a várost az ágyúinkkal. Az embereim a hajón meglátják, és úgy tesznek, mintha készülnének a partraszállásra. Egy-két óra múlva Stuyvesant összeszarja magát, és kész lesz elküldeni a fegyverszüneti követeket.";
			link.l1 = "Minden a tervünk szerint halad, ezredes! Csináljuk meg!";
			link.l1.go = "doily_24";
		break;
		
		case "doily_24":
			DialogExit();
			Patria_CuracaoTownBombing();
		break;
		
		// голландский парламентёр под стенами Виллемстада
		case "holoff":
			dialog.text = "Azért érkeztem ide, hogy megkezdjük a tárgyalásokat. Mik a követelései?";
			link.l1 = "Találkozót követelünk a Társaság igazgatójával, Peter Stuyvesant-tal. Konkrétan arról akarunk beszélni, hogy a társasága és a saját hibájából Willemstadot jelenleg a pusztulás fenyegeti.";
			link.l1.go = "holoff_1";
		break;
		
		case "holoff_1":
			dialog.text = "Rendben van, tájékoztatom mynheer Stuyvesantot errôl, és megszervezzük a biztonságos utat a városba a küldöttségük számára...";
			link.l1 = "És mi a helyzet a biztonságos kijárattal?";
			link.l1.go = "holoff_2";
		break;
		
		case "holoff_2":
			dialog.text = "Nem értem, mynheer?";
			link.l1 = "Azt kérdeztem: megszerveznétek nekünk egy biztonságos kijáratot a városból? Ebben nem vagyok biztos. Attól tartok, mynheer Stuyvesant talán úgy dönt, hogy fogságba ejti a követeinket. Ezért meghívom mynheer Stuyvesantot, hogy jelenjen meg itt a tárgyalásokon.";
			link.l1.go = "holoff_3";
		break;
		
		case "holoff_3":
			dialog.text = "De...";
			link.l1 = "Tiszt úr, mi diktáljuk a feltételeket. Az önök flottája megsemmisül, a helyôrség el van vágva a várostól, mi pedig úgy hatolunk át Willemstad védelmén, mint a fregate az evezôs csónakon, ha úgy döntünk, hogy megrohamozzuk a várost. Most pedig kapni fog egy levelet mynheer Stuyvesantnak, és átadja neki a meghívónkkal együtt...";
			link.l1.go = "holoff_4";
		break;
		
		case "holoff_4": // перекидываем pchar на офицера и говорим с д'Ойли
			DialogExit();
			LAi_SetActorType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Curacao_parlamenter_1"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Doily_land");
			sld.dialog.currentnode = "doily_12";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
			bDisableCharacterMenu = true;//лоченые интерфейсы
		break;
		
		// офицер-испанец на маяке Тринидада
		case "SanJoseSpanish":
			dialog.text = "Szóval, kapitány úr, azért hívta a fegyverszüneti követeket, mert követeléseit akarta diktálni?";
			link.l1 = "Teljesen igaza van, senor. Hadd magyarázzam el röviden, hogy miért érkeztem Trinidadba - ez a válaszunk az önök legutóbbi, Saint-Pierre elleni támadására. Jelentôs károkat okoztál a városnak, és most kénytelen leszel kárpótolni. A kártérítés ára háromszázezer pezó. És ez nem is olyan sok, tekintve, hogy milyen aljas tetteket követtek el a katonáitok Martinique-on.";
			link.l1.go = "SanJoseSpanish_1";
		break;
		
		case "SanJoseSpanish_1":
			dialog.text = "Elnézést, senor, de mi köze van San Josénak Saint-Pierre-hez? Miért kell a mi gyarmatunknak fizetnie?";
			link.l1 = "Mert a támadók spanyolok voltak, nem hollandok vagy angolok. Akkor a számlát Don de Mendosa számára a Gondviselésre teszi, ôszinte üdvözletemmel együtt. Amint megérti, ha megtagadja a kártérítés kifizetését, megparancsolom az embereimnek, hogy szálljanak partra, és akkor San José sokkal többet veszít. Biztos vagyok benne, hogy a kolóniátok kormányzója helyesen fog dönteni. Egy napjuk van a válaszadásra. Minden jót kívánok, senores.";
			link.l1.go = "SanJoseSpanish_2";
		break;
		
		case "SanJoseSpanish_2":
			DialogExit();
			npchar.dialog.currentnode = "SanJoseSpanish_3";
			Patria_SanJoseMayakSpanishGo();
		break;
		
		case "SanJoseSpanish_3":
			dialog.text = "";
			link.l1 = "Tehát, ha jól értem, a kormányzó helyesen döntött?";
			link.l1.go = "SanJoseSpanish_4";
		break;
		
		case "SanJoseSpanish_4":
			AddMoneyToCharacter(pchar, 300000);
			dialog.text = "Fogják a háromszázezer dollárt, és hagyják el a kolóniánkat.";
			link.l1 = "Kitûnô, senores. Biztosíthatom önöket - ez volt a legjobb megoldás. Remélem, ez elriasztja Don de Mendosát és másokat attól, hogy megtámadják a kolóniáinkat. Ne felejtsék el elküldeni az üzenetet a Gondviselésnek és neki személyesen. Minden jót kívánok, uraim.";
			link.l1.go = "SanJoseSpanish_5";
		break;
		
		case "SanJoseSpanish_5":
			DialogExit();
			Patria_SanJoseMayakSpanishFin();
		break;
		
		// вестовой на 5 задание
		case "fraofficer":
			dialog.text = "Charles de Maure kapitány, engedje meg, hogy jelentést tegyek: Chevalier Philippe de Poincy értesíteni akarja önt, hogy Noel Forget báró készen áll az indulásra Saint-Martinba, és várja önt a mólón.";
			link.l1 = "Kitûnô! Köszönöm, monsieur.";
			link.l1.go = "fraofficer_1";
		break;
		
		case "fraofficer_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "", 10.0);
			Patria_SanMartinSetBaron();
		break;
		
		case "fraofficer_2":
			dialog.text = "Charles de Maure kapitány! A fôkormányzó most azonnal keresi önt. Egy hatalmas ellenséges hajóraj jelent meg Saint-Christopher partjainál!";
			link.l1 = "Akkor ne vesztegessük az idôt!";
			link.l1.go = "fraofficer_3";
		break;
		
		case "fraofficer_3":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "", 10.0);
			chrDisableReloadToLocation = false;
			Patria_SiegeHovernor();
		break;
		
		// патруль у рудника
		case "engofficer":
			dialog.text = "Kik vagytok ti? Mit keres itt?";
			link.l1 = "Uhh...";
			link.l1.go = "engofficer_1";
		break;
		
		case "engofficer_1":
			dialog.text = "Idegenek nem léphetnek be ide! Kik vagytok ti, kémek? Elviszlek titeket a parancsnoki irodába, majd ôk elintéznek titeket.";
			link.l1 = "De mi nem mehetünk a parancsnoki irodába...";
			link.l1.go = "engofficer_2";
		break;
		
		case "engofficer_2":
			dialog.text = "Ha te magad nem mész, akkor erôszakkal kell elhurcolnunk téged! Adjátok át a fegyvereiteket!";
			link.l1 = "Nincs alku...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Patria_CondotierBeachFight");
		break;
		
		// бывший управляющий рудника
		case "miner":
			dialog.text = "";
			link.l1 = "Szóval, minden világos?";
			link.l1.go = "miner_1";
		break;
		
		case "miner_1":
			dialog.text = "Igen, monsieur. A levelet személyesen Peter Stuyvesant vagy Mathias Beck miniszter úrnak kell átadni.";
			link.l1 = "Biztos vagyok benne, hogy nem lesz gondja hajóval Willemstadból Cartagenába. Az út és a szállás kifizetéséhez szükséges pénzeszközöket átadtuk önnek. És ha esetleg szükség lenne rá - fél év múlva a francia bizottság elôtt megerôsíti a jelentéseit?";
			link.l1.go = "miner_2";
		break;
		
		case "miner_2":
			dialog.text = "Uram, én hûséges vagyok a szavamhoz.";
			link.l1 = "Rendben van. Akkor sok szerencsét kívánok. Ez az út Willemstadba vezet, kövesse. Nincs messze innen.";
			link.l1.go = "miner_3";
		break;
		
		case "miner_3":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "Patria_CondotierOnCuracaoWait", 15.0);
			AddQuestRecord("Patria", "82");
			ReleasePrisoner(npchar);
		break;
		
		// курьер в Капстервиль
		case "cureer":
			dialog.text = "Charles de Maure ellentengernagy, igaz?";
			link.l1 = "Pontosan. Kivel van szerencsém beszélni?";
			link.l1.go = "cureer_1";
		break;
		
		case "cureer_1":
			dialog.text = "Üzenetet hoztam önnek Noel Forget bárótól. Azt üzeni, hogy jöjjön minél hamarabb a kormányzó palotájába, Casterville-be.";
			link.l1 = "Ó! Nagyszerû hírek! Köszönöm, azonnal indulok!";
			link.l1.go = "cureer_2";
		break;
		
		case "cureer_2":
			DialogExit();
			chrDisableReloadToLocation = false;
			Patria_EuropePrepare();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 10.0);
		break;
		
		case "burden":
			dialog.text = "Üdvözlöm, tengernagy-helyettes úr. Forget báró mesélt nekem önrôl. Rengeteg történetet. Ôszinte köszönetemet fejezem ki önnek a Franciaország javát szolgáló hûséges és ragyogó szolgálatáért a gyarmatokon, valamint a csaló de Poincy ármánykodásának leleplezésében nyújtott segítségéért. Most én és a pénzügyminiszter személyesen fogunk vele foglalkozni, ön pedig átveszi korábbi parancsnoka helyét. Legalábbis egyelôre.";
			link.l1 = "De...";
			link.l1.go = "burden_1";
		break;
		
		case "burden_1":
			dialog.text = "No 'buts', vice-admiral! Ezt a döntést már meghozták és a király jóváhagyta. Itt van nálam egy személyesen általa aláírt parancs arról, hogy Önt bízza meg a szigetvilágban lévô francia gyarmatok tényleges fôkormányzójává. Nincs jobb jelöltünk erre a posztra. Az Ön kiemelkedô tapasztalata a hadviselésben, a régió és az itt mindenért felelôs emberek ismerete, az Ön képességei és tehetsége mind méltóak erre a magas és tiszteletre méltó pozícióra. Ha ôszinte lehetek önnel, arra számítok, hogy egy idô után ismét ön kapja meg ezt a pozíciót, a 'de facto' rész nélkül.";
			link.l1 = "De én arról álmodtam, hogy visszamegyek Párizsba...";
			link.l1.go = "burden_2";
		break;
		
		case "burden_2":
			dialog.text = "Franciaországnak szüksége van rád! A pénzügyminiszter most éppen haditengerészetet gyûjt Európában, és a mi jelenlétünk itt, a szigetországban sem marad észrevétlen. Az Ön fô feladata a gyarmatok megerôsítése és megerôsítése, valamint flottánk katonai erejének növelése lesz, míg Forget báró és a Francia Nyugat-Indiai Kereskedelmi Társaság a kereskedelemre és a hazai fejlesztésekre fog koncentrálni! És ki más, ha nem te, segíthetne a francia haditengerészet felkészítésében?\nSzóval, kezdj el dolgozni, fôkormányzó úr! Tudom, hogy nem szeretsz egész nap egy szobában ülni, de a feladatod nem is igényli ezt!";
			link.l1 = "Azonnal, felség! A parancsokat nem szabad megkérdôjelezni!";
			link.l1.go = "burden_3";
		break;
		
		case "burden_3":
			dialog.text = "Örülök, hogy jól értettél. És arra is megkérem, hogy látogasson el Chevalier de Poincyhoz: ragaszkodott hozzá, hogy találkozzon önnel. Nem tagadhatjuk meg tôle ezt az örömöt, mielôtt Párizsba indul, nem igaz? A börtönben fogja megtalálni.";
			link.l1 = "Rendben, felség...";
			link.l1.go = "burden_4";
		break;
		
		case "burden_4":
			DialogExit();
			DoQuestReloadToLocation("Charles_prison", "goto", "goto19", "Patria_EuropePuancieInPrison");
		break;
		
		// Портной Пуанси Xenon
		case "Tailor":
			dialog.text = "...késleltetni fogja, érti? Már hónapokkal ezelôtt megrendeltem ezeket az anyagokat!";
			link.l1 = "...";
			link.l1.go = "Tailor_01";
			CharacterTurnByChr(npchar, characterFromId("Charles_PortMan"));
		break;
		
		case "Tailor_01":
			DialogExit();
			sld = characterFromId("Charles_PortMan");
			sld.dialog.currentnode = "Tailor";
			LAi_SetActorType(pchar);
			LAi_ActorDialogNow(pchar, sld, "", -1);
		break;
		
		case "Tailor_02":
			dialog.text = "És hogyan rangsorolták, hogy mit vigyenek az elsô hajóra, és mit a másodikra?! Én nem csak egy egyszerû varrónô vagyok a pusztáról - még a fôkormányzótól, ôexcellenciája, chevalier de Poincy lovagtól is van parancsom!";
			link.l1 = "...";
			link.l1.go = "Tailor_03";
			CharacterTurnByChr(npchar, characterFromId("Charles_PortMan"));
		break;
		
		case "Tailor_03":
			DialogExit();
			Lai_SetPlayerType(pchar);
			sld = characterFromId("Charles_PortMan");
			sld.dialog.currentnode = "Tailor_02";
			LAi_SetActorType(pchar);
			LAi_ActorDialogNow(pchar, sld, "", -1);
		break;
		
		case "Tailor_04":
			dialog.text = "Nos, mi mást tehetnék most... Várni fogok. De ezt tudnia kell: A teljesítetlen parancsokért nem vállalok felelôsséget!";
			link.l1 = "Üdvözletem. Látom, bajban vagy?";
			link.l1.go = "Tailor_05";
			CharacterTurnByChr(npchar, characterFromId("Charles_PortMan"));
		break;
		
		case "Tailor_05":
			dialog.text = "Baj? Ez még enyhén szólva is! Ó, azt hiszem, felismerem magát... Maga az új admirális-helyettes, igaz?";
			link.l1 = "Gyorsan felkapja a fonalat. Így van, ön elôtt áll a francia gyarmatok második embere, a francia flotta ellentengernagya, Charles de Maure.";
			link.l1.go = "Tailor_06";
			link.l2 = "Hagyjuk a formaságokat, nem egy hajón vagyunk. És ne aggódjon, nem hívom az ôrséget csak azért, mert nem ismert fel azonnal. Csak szólítson Charles de Maure-nak.";
			link.l2.go = "Tailor_07";
			CharacterTurnByChr(npchar, pchar);
		break;
		
		case "Tailor_06":
			AddCharacterExpToSkill(pchar, "Leadership", 300);//харизма
			dialog.text = "Excellenciás uram, kérem, bocsásson meg, hogy nem ismertem fel azonnal! Igen, igaza van, nem várt körülmények közé kerültem.";
			link.l1 = "És mik lennének ezek a körülmények? Ha jól értem, nem hoztak önnek anyagot Párizsból?";
			link.l1.go = "Tailor_08";
		break;
		
		case "Tailor_07":
			AddCharacterExpToSkill(pchar, "Fortune", 300);//везение
			dialog.text = "Ó, köszönöm szépen. Igaza van, elôre nem látott körülményekkel találkoztam, ezért nem vettem észre azonnal, hogy ki áll elôttem.";
			link.l1 = "És mik lennének ezek a körülmények? Ha jól értem, nem hoztak önnek anyagot Párizsból?";
			link.l1.go = "Tailor_08";
		break;
		
		case "Tailor_08":
			dialog.text = "Igen, így van. Néhány hónappal ezelôtt rendeltem ôket. A kormányzó akkoriban írta alá a kinevezésedrôl szóló rendeletet, és ragaszkodott hozzá, hogy készítsem el az új admirális egyenruhához szükséges anyagokat, bízva abban, hogy a fôvárosban jóváhagyják.";
			link.l1 = "És az anyagokat nem szállították le, feltételezem?";
			link.l1.go = "Tailor_09";
		break;
		
		case "Tailor_09":
			dialog.text = "Képzelje csak el! Elmagyaráztam, hogy milyen fontos, és leadtam a megrendelést... De nekik sürgôsebb szállítmányokat kellett elintézniük! Most mit tegyek? Rendeljek egy évre elôre, remélve, hogy majd méltóztatnak elhozni nekem az anyagokat?";
			link.l1 = "Pontosan mi hiányzik? Talán a Karib-tengeren be lehet szerezni?";
			link.l1.go = "Tailor_10";
		break;
		
		case "Tailor_10":
			dialog.text = "Még ha lehetséges is, fogalmam sincs, hogy hol... Itt nem fogsz jó anyagokat találni. Bár... A régi tiszti kabátodat használhatnám alapnak, ha megengeded. Valószínûleg nem lesz rá szükséged, ha már admirális egyenruhád lesz, igaz?";
			link.l1 = "Ha lesz admirális egyenruhám, akkor természetesen nem lesz szükségem egy egyszerû tiszti kabátra. Mi másra?";
			link.l1.go = "Tailor_11";
		break;
		
		case "Tailor_11":
			dialog.text = "Szükségem van mandzsettagombokra és gallérra az egyenruhához. Általában közvetlenül a párizsi mûhelyektôl rendelem ôket. Még ha nagyon egyszerûek is, át tudom alakítani ôket, és szalonképesebbé tudom tenni. Bár ebben az esetben többre lesz szükségem belôlük...";
			link.l1 = "Mivel a Karib-térségben nincsenek párizsi mûhelyek, keresek egy egész adag helyi ruhát levehetô gallérral és mandzsettával. Mi van még?";
			link.l1.go = "Tailor_12";
		break;
		
		case "Tailor_12":
			dialog.text = "Az utolsó simításokhoz nagyon jó minôségû szövetekre van szükségem. Van egy fonóm, aki még durva szálakból is tud ilyen anyagot készíteni. De ehhez anyagra van szükségem - ideális esetben pamutra. Egy bála bôven elég lesz.";
			link.l1 = "Az is beszerezhetô. Mi a következô lépés?";
			link.l1.go = "Tailor_13";
		break;
		
		case "Tailor_13":
			dialog.text = "Úgy volt, hogy Párizsból szállítanak egy admirális trikornisát, de azt magam is elkészíthetem, ha megvan az anyag. Bár az önnek szánt trikolórnak szövetbôl kellett volna lennie, a Karib-tenger sós szelei és perzselô napsütése miatt a bôr jobb lenne. Tovább tartana.";
			link.l1 = "Megszerzem neked a bôrt; ne aggódj. Még bikákat sem kell majd üldöznöm Espanola dzsungelében. Ez minden?";
			link.l1.go = "Tailor_14";
		break;
		
		case "Tailor_14":
			dialog.text = "Lyonból is kiváló minôségû selymet kellett volna szállítaniuk. Könnyû, lélegzô, könnyen felszívja a nedvességet, és még gyorsabban szárad. És ami a legfontosabb, nem nyúlik és megtartja az alakját.";
			link.l1 = "Igen, értem, milyen selyemrôl beszélsz. Bár azt talán nehezebb lesz beszerezni a kolóniákon.";
			link.l1.go = "Tailor_15";
		break;
		
		case "Tailor_15":
			dialog.text = "Ennyit az anyagokról. Azt is hallottam, hogy megkapta Franciaország legmagasabb kitüntetését... A Szent Lajos-rendet nem úgy kell viselni, mint valami csecsebecsét az övön. Megvan a helye. Szóval, kérem, hozza el nekem, és én majd felvarrom, ahogy illik.";
			link.l1 = "Rendben, én is elhozom. Csak el ne veszítsd!";
			link.l1.go = "Tailor_16";
		break;
		
		case "Tailor_16":
			dialog.text = "Biztos, hogy nem! Az életemmel fogom ôrizni!";
			link.l1 = "Rendben. Ha ez minden, akkor megyek az anyagokért.";
			link.l1.go = "Tailor_17";
		break;
		
		case "Tailor_17":
			dialog.text = "Van még egy dolog... A szabószerszámaim használhatatlanná váltak. Rendeltem újakat Párizsból, de sajnos... Ha megkeresnéd a szükséges anyagokat és kölcsönadnád a szerszámokat, ha van - csak kölcsönadnád, majd késôbb szerzek újakat! - Azonnal nekiállnék varrni.";
			link.l1 = "Nos, mit tehetnék? Hozok neked mindent, amire szükséged van. Hol talállak meg? Ugye nem a kikötôi hivatalban vársz rám?";
			link.l1.go = "Tailor_18";
		break;
		
		case "Tailor_18":
			dialog.text = "A mûhelyem a mólónál lévô épületben van - amikor partra száll, jobbra lesz.";
			link.l1 = "Megegyeztünk. Megszerzem az anyagokat.";
			link.l1.go = "Tailor_19";
		break;
		
		case "Tailor_19":
			DialogExit();
			AddQuestRecord("Patria", "65_1");
			chrDisableReloadToLocation = false;
			ChangeCharacterAddressGroup(npchar, "Charles_houseS3", "barmen", "Stay");
			npchar.dialog.currentnode = "Tailor_20";
			LAi_SetOwnerType(npchar);
			pchar.questTemp.PatriaTailor = true;
		break;
		
		case "Tailor_20":
			dialog.text = "Üdvözletem, admirális-helyettes úr! Mindent elhozott, ami az új egyenruhájához szükséges?";
			link.l1 = "Még nem, nem volt rá idôm. Várjon, hozok mindent.";
			link.l1.go = "Tailor_20_exit";
			if(CheckCoatItems())
			{
				link.l2 = "Igen, mindent elhoztam. Itt van a régi kabátom, a rend és a szabószerszámok. A többi anyagot a matrózaim hamarosan elhozzák a mûhelyedbôl.";
				link.l2.go = "Tailor_21";
			}
		break;
		
		case "Tailor_20_exit":
			npchar.dialog.currentnode = "Tailor_20";
			DialogExit();
		break;
		
		case "Tailor_21":
			RemoveItems(pchar, "talisman9", 1);
			RemoveItems(pchar, "suit1", 1);
			RemoveItems(pchar, "tailor_tool", 1);
			RemoveCharacterGoods(pchar, GOOD_CLOTHES, 1);
			RemoveCharacterGoods(pchar, GOOD_COTTON, 1);
			RemoveCharacterGoods(pchar, GOOD_LEATHER, 1);
			RemoveCharacterGoods(pchar, GOOD_SHIPSILK, 1);
			dialog.text = "Csodálatos! Hogy ôszinte legyek, nem gondoltam, hogy mindezt be tudod szerezni. Én csak párizsi anyagokkal szoktam dolgozni, de úgy tûnik, hogy helyi anyagokból egészen tisztességes öltönyöket lehet készíteni.";
			link.l1 = "Mikorra készül el az új egyenruhám?";
			link.l1.go = "Tailor_22";
		break;
		
		case "Tailor_22":
			dialog.text = "Általában nem kevesebb, mint egy hét, de tekintve, hogy a megrendelô Franciaország két legmagasabb rangú tisztviselôje a gyarmatokon... Jöjjön el hozzám három napon belül, és ígérem, hogy minden a lehetô legjobban elkészül! Nem kell méretet vennünk, mindent a régi kabátja alapján készítek el.";
			link.l1 = "Nagyszerû! Akkor három nap múlva visszajövök.";
			link.l1.go = "Tailor_23";
		break;
		
		case "Tailor_23":
			DialogExit();
			npchar.dialog.currentnode = "Tailor_24";
			SetFunctionTimerCondition("Patria_Tailor_Done", 0, 0, 3, false);
		break;
		
		case "Tailor_24":
			if(CheckAttribute(pchar,"questTemp.PatriaTailorDone"))
			{
				dialog.text = "Admirális-helyettes úr! Örülök, hogy látom!";
				link.l1 = "Nos, az új egyenruháért jöttem, ahogy megbeszéltük.";
				link.l1.go = "Tailor_27";
			}
			else
			{
				dialog.text = "Üdvözlöm, admirális-helyettes úr! Elnézést kérek, de az egyenruhája még nincs kész.";
				link.l1 = "Nos, legalább egy kicsit megnézhetem, hogy mi történik?";
				link.l1.go = "Tailor_25";
			}
		break;
		
		case "Tailor_25":
			dialog.text = "Nem, nem, nem! Jelenleg teljesen szalonképtelenül néz ki, és nem akarok csalódást okozni az elvárásaidnak. Kérem, legyen türelemmel.";
			link.l1 = "Oké, várok.";
			link.l1.go = "Tailor_26";
		break;
		
		case "Tailor_26":
			DialogExit();
			npchar.dialog.currentnode = "Tailor_24";
		break;
		
		case "Tailor_27":
			dialog.text = "Igen, persze! El kell mondanom, hogy nem lett rosszabb, mint a Párizsban készültek! Igazad volt, még a gyarmatokon is lehet megfelelô anyagot találni, ha tudod, hol keresd. Egy pillanat. Itt is van! Kérem, nézze meg és próbálja fel.";
			link.l1 = "Köszönöm. Kiváló minôség! És jól áll.";
			link.l1.go = "Tailor_28";
		break;
		
		case "Tailor_28":
			dialog.text = "Nem csak jól! Büszkén viselheti ezt Franciaország ellentengernagyaként a gyarmatokon! És a rendje, ahogy ígértem, most már a helyén van, nem az övén lóg.";
			link.l1 = "Szép munka! Ha találkozik Chevalier de Poincyval, elmondhatja neki, hogy elégedett vagyok.";
			link.l1.go = "Tailor_29";
		break;
		
		case "Tailor_29":
			dialog.text = "Biztosan megmondom neki! Az egyenruha szolgáljon hûségesen! Sok szerencsét!";
			link.l1 = "Köszönöm! Viszontlátásra.";
			link.l1.go = "Tailor_30";
		break;
		
		case "Tailor_30":
			DialogExit();
			npchar.dialog.currentnode = "first time";
			npchar.lifeday = 0;
			DeleteAttribute(pchar,"questTemp.PatriaTailorDone");
			DeleteAttribute(pchar, "questTemp.PatriaTailor");
			//if(CheckAttribute (pchar, "IsMushketer")) SetMainCharacterToMushketer("", false);
			RemoveCharacterEquip(pchar, CIRASS_ITEM_TYPE);
			GiveItem2Character(pchar, "suit5");
			EquipCharacterbyItem(pchar, "suit5");
			GiveItem2Character(pchar, "hat5");
			EquipCharacterbyItem(pchar, "hat5");
			AddItems(pchar, "tailor_tool", 1);
			Log_Info("Megkaptad az ellentengernagy egyenruháját!");
			AddQuestRecord("Patria", "65_2");
		break;
		
		//belamour legendary edition
		case "BladeUpg":
			string sItem, attrL, attrB;
			ref rItem;
			aref arItems; 
			int i, n, iItemsNum;
			dialog.text = "Melyik pengét szeretnéd frissíteni?";
			
			i = 1;
			makearef(arItems, pchar.items);
			iItemsNum = GetAttributesNum(arItems);
			for(n=0; n<iItemsNum; n++)
			{
				sItem = GetAttributeName(GetAttributeN(arItems, n));
				rItem = ItemsFromID(sItem);
				if(!CheckAttribute(rItem, "groupID")) continue;
				if(rItem.groupID != BLADE_ITEM_TYPE) continue;
				if(rItem.price == 0) continue;
				if(IsEquipCharacterByItem(pchar, rItem.id)) continue;
				if(sItem != "" && rItem.groupID == BLADE_ITEM_TYPE) 
				{
					attrL = "l" + i;
					Link.(attrL) = GetConvertStr(rItem.name, "ItemsDescribe.txt") + ": Támadás - " + FloatToString(stf(rItem.attack),1) + ", egyensúly - " + FloatToString(stf(rItem.Balance),1) + ", súly - " + FloatToString(stf(rItem.Weight),1);
					Link.(attrL).go = "bladeindex_"+GetItemIndex(rItem.id);
					i++;
				}
			}
			
			link.l500 = "Meggondoltam magam.";
			link.l500.go = "exit";
		break;
	}
} 

bool CheckCoatItems()
{
	if(GetSquadronGoods(pchar, GOOD_CLOTHES) > 0
	&& GetSquadronGoods(pchar, GOOD_COTTON) > 0
	&& GetSquadronGoods(pchar, GOOD_LEATHER) > 0
	&& GetSquadronGoods(pchar, GOOD_SHIPSILK) > 0
	&& GetCharacterFreeItem(pchar, "talisman9") > 0
	&& GetCharacterFreeItem(pchar, "suit1") > 0
	&& GetCharacterFreeItem(pchar, "tailor_tool") > 0)
	return true;
	
	return false;
}
