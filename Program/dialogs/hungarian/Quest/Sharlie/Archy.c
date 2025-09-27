// Арчибальд Колхаун
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Szükséged van valamire?";
			link.l1 = "Nem, semmit.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "portroyal":
			dialog.text = "Ha, Monsieur de Maure!  Üdvözöljük Port Royalban!  Emlékszik még rám?";
			link.l1 = "Maga Mr. Calhoun, ugye? Henry Calhoun?";
			link.l1.go = "portroyal_1";
		break;
		
		case "portroyal_1":
			dialog.text = "Majdnem... Archibald Calhoun.";
			link.l1 = "Ó, bocsásson meg, Monsieur. Igen, emlékszem önre. A Catoche-foknál találkoztunk, az öbölben. A kapitánya is önnel volt, William Patterson. Felismertem a századát.";
			link.l1.go = "portroyal_2";
		break;
		
		case "portroyal_2":
			dialog.text = "Teljesen igaza van! Kérem, bocsásson meg a kapitányomnak. Mindig udvariatlan azokkal, akiket nem ismer. Kiválóan teljesítettek, Diego de Montoya erôdjét ostromolták, amire véletlenül rávetettük a karmainkat...";
			link.l1 = "Az igazság kedvéért hozzáteszem, hogy a kapitányotok által mutatott elôzetes elôkészületek nélkül kétséges, hogy egyáltalán képes lettem volna a spanyol ágyúk tüze alatt a nyereségre futni. A parancsnokuk megtalálta, amit keresett?";
			link.l1.go = "portroyal_3";
		break;
		
		case "portroyal_3":
			dialog.text = "Igen. Elég mélyen belemászott az erôd alatti kazamatákba, és talált valamiféle archívumot. Kimondhatatlanul elégedett volt. Egyébként, ha nem bánja, hogy megkérdezem, mi késztette arra, hogy megtámadja azt az erôdöt a dzsungelben?";
			link.l1 = "Miután Saint-Pierre-ben vereséget szenvedett tôlem, Don Diego elkezdett egy tervet kidolgozni, és végül nyílt támadást intézett Kuba ellen. Aztán megszakította a harcot, és a hegyekbe menekült Main felé. Nos, elhatároztam, hogy egyszer s mindenkorra megszabadulok attól a sárga kutyától, hogy soha többé ne bolygassa a franciákat.";
			link.l1.go = "portroyal_4";
		break;
		
		case "portroyal_4":
			dialog.text = "Igen, hallottam néhány legendás történetet Charles de Maure kapitány hôstetteirôl. Most a saját szememmel láttam...";
			link.l1 = "Igen, hallottam pár dolgot William Paterson bátorságáról is. Szerencsés vagy, hogy ilyen kapitányod van.";
			link.l1.go = "portroyal_5";
		break;
		
		case "portroyal_5":
			dialog.text = "Szerencsémre ez igaz. Bár manapság olyan fontos emberré vált, az elôkelô társaság, a közönség, a bálok, a parádék és a magánpartik emberévé... A kormányzói palotából nem lehet ôt elôcsalogatni, akármikor megérkezünk Port Royalba. Tulajdonképpen most is ott van.\nCaptain Charles de Maure, megtenne egy szívességet egy skót részegesnek? Csatlakozzon a társaságomhoz, és beszélgessünk! Elegem van abból, hogy mindig ugyanazokat az arcokat látom, és úgy tûnik, önnel jót lehet beszélgetni. Jöjjön el hozzám, lazítsunk és igyunk egy hordó kiváló whiskyt. Én fizetek!";
			link.l1 = "Hm... csábító, de...";
			link.l1.go = "portroyal_6";
		break;
		
		case "portroyal_6":
			dialog.text = "Ó, hagyja abba, kapitány, magának is pihennie kell néha. Egyébként van néhány finom elôételem, egyenesen a helyi kereskedô boltjából. Éppen a bolt felett bérelek egy szobát. Amikor csak kedvetek van egy kis harapnivalóhoz vagy italhoz, csak sétáljatok le a földszintre, és máris kész, haha! Kényelmes, ugye? Gyere, menjünk!";
			link.l1 = "Rábeszéltél!";
			link.l1.go = "portroyal_7";
		break;
		
		case "portroyal_7":
			dialog.text = "Nagyszerû. Gyere utánam!";
			link.l1 = "...";
			link.l1.go = "portroyal_8";
		break;
		
		case "portroyal_8":
			DialogExit();
			NextDiag.CurrentNode = "portroyal_9";
			LAi_SetActorType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload6_back", "PortRoyal_store", "goto", "goto2", "GuardOT_ArchyIntoStore", -1);
			LAi_ActorFollow(pchar, npchar, "", -1);
		break;
		
		case "portroyal_9":
			LAi_SetSitType(Pchar);
			dialog.text = "Látod, milyen szép itt? Kellemes és hideg... Itt van néhány whisky hordó! Fenékig, kapitány!";
			link.l1 = "Nos, igyunk a szerencsés találkozásunkra és a kellemes ismerkedésre!";
			link.l1.go = "portroyal_10";
		break;
		
		case "portroyal_10":
			dialog.text = "Örülök!... Ah! Ön nemrég érkezett a Karib-tengerre, igaz, Monsieur de Maure?";
			link.l1 = "Viszonylag nemrég... vagy nem is olyan régen. Nem is tudom, hogy mondjam. Úgy érzem, mintha a fél életemet itt töltöttem volna.";
			link.l1.go = "portroyal_11";
		break;
		
		case "portroyal_11":
			dialog.text = "Ó, ismerem ezt az érzést... Bár én is régóta itt vagyok már. És amikor partra szálltam azon az átkozott szigeten, ahonnan William megmentett... Óóóó, az biztos, hogy olyan érzés, mintha a fél életemnek búcsút mondtam volna ott.";
			link.l1 = "Érdekes! Melyik sziget volt az?";
			link.l1.go = "portroyal_12";
		break;
		
		case "portroyal_12":
			dialog.text = "Willy régi barátom, még akkor ismertük egymást, amikor még Skócia szép levegôjét szívtam... Szép idôk voltak. Elég bolond voltam ahhoz, hogy összevesszek az átkozott pápistákkal és magával az inkvizítorral, ezért szervezett rám egy merényletet. Akkoriban kereskedô voltam, saját furulyám volt.\nEh, azon az átkozott napon a hajómat megtámadták a spanyolok, kalóznak öltözve. Bátran harcoltunk, de sikerült sarokba szorítaniuk minket, mint a patkányokat! Az öreg Colhaun még akkor sem vesztette el a fejét, és egy hordó vízzel és néhány deszkával a fedélzetre ugrott.\nKihasználtam a sötétséget, és elúsztam a hajómtól, a katonák által észrevétlenül. A túlélési esélyek nem voltak túl jók, de a hajón maradni azt jelentette, hogy egyáltalán nincs esélyem. Két nap múlva valami elhagyatott sziget partján vetettem ki magam.\nEkkor már egy ideje a Karib-tengeren éltem, mégsem hallottam róla addig soha! Kicsi és teljesen lakatlan... és két évet töltöttem ott, ami egy örökkévalóságnak tûnt. Még mindig nem tudom, hogyan sikerült megôriznem az eszemet.";
			link.l1 = "Két évet éltél egy lakatlan szigeten?";
			link.l1.go = "portroyal_13";
		break;
		
		case "portroyal_13":
			dialog.text = "Az biztos, hogy sikerült, átkozott hely! Még jó, hogy volt friss víz. Rákokkal, kagylókkal, halakkal és madarakkal táplálkoztam. Ezért neveztem el Rák-szigetnek. Fegyverem nem volt, ezért elsajátítottam a szigonyt, a lándzsát és a nyilat, mint egy vadember! Ohoo! Igyál, igyál, kapitány! Nem bánom, ha a fütykölôm is megnedvesedik...";
			link.l1 = "Igen... nem irigyellek.";
			link.l1.go = "portroyal_14";
		break;
		
		case "portroyal_14":
			dialog.text = "Tessék! Pontosan ezt mondtam én is, amikor elôször tettem a lábam annak a nagy homokdarabnak a partjára: 'Vén Archy, a helyzeted nem irigylésre méltó, de nem is reménytelen!' És tudod, mi tartott életben, kapitány?";
			link.l1 = "Egy hajó, amelyik elhaladt a sziget mellett?";
			link.l1.go = "portroyal_15";
		break;
		
		case "portroyal_15":
			dialog.text = "Nem! A munka mentett meg! Munka, hit és élni akarás! Felfedeztem az egész szigetet, minden szegletét, és jutalmul kaptam egy ládát, tele ácsszerszámokkal, írószerekkel és egyéb apróságokkal. Tudod, mit mondtam magamnak abban a pillanatban? Tölts még, kapitány, csak tölts még!\nmondtam: Archie, dolgoznod kell azon, hogy az elmédet a helyén tartsd, és Isten mindent megadott neked ahhoz, hogy elkezdj hozzáfogni. Most már látod! Elkezdtem építeni egy házat egy öböl közelében, és tudod mit? Ez megmentett a beteg gondolatoktól és adott okot az életre!";
			link.l1 = "Ön egy élô inspiráció, Calhoun úr. Nem minden ember lenne képes ilyen helyzetben sokat, ha egyáltalán bármit is tenni...";
			link.l1.go = "portroyal_16";
		break;
		
		case "portroyal_16":
			dialog.text = "Igen, az öreg Calhaun nem véletlenül született Skóciában! Így van! Mi vagyunk a hegyek fiai - erôsek, bátrak és szívósak, sokkal jobbak, mint azok a mocsári pehelysúlyúak. Öntsd tovább... Rendben, mirôl is beszéltem? Igen! Keményen dolgoztam, és építettem magamnak egy rendes házat. Naplót is indítottam, hogy mindennapi írásaimban megírhassam szerencsétlenségeimet. A naplót magammal vittem, amikor Willy megmentett.\nMost itt tartom ezen az asztalon, és a meleg, puha ágyban újraolvasom minden alkalommal, amikor Port Royalban tartózkodunk.\nMindent leírtam bele, mindent, ami velem történt, mielôtt és miután oda kerültem. Ez az egyik oka annak, hogy még mindig velem van az elmém.";
			link.l1 = "Szóval kiderült, hogy Mr. Paterson szedte ki magát a szigetrôl? De hogyan találhatta meg? Azt mondta...";
			link.l1.go = "portroyal_17";
		break;
		
		case "portroyal_17":
			dialog.text = "Igen, igen, a sziget nincs jelölve semmilyen térképen. De Willy, ô az öreg Willy! Ô bármire képes! És megtalálta azt az istenverte szigetet, és megmentett engem, és ezért életem végéig hálás leszek. Igen...";
			link.l1 = "Szereti kiszolgálni Mr. Paterson-t? Szeretne megint a saját erôforrásaiból menni?";
			link.l1.go = "portroyal_18";
		break;
		
		case "portroyal_18":
			dialog.text = "Elegem van a függetlenségbôl. Willy fiatal és sikeres, és én is régi barátja vagyok. Mi másra van szükségem? Nem, életem végéig Willyvel leszek, vagy legalábbis addig, amíg ki nem rúg, amikor legközelebb berúgok, haha! Ha már a részegségnél tartunk, öntsd ki magad!";
			link.l1 = "Akh...(ivás) Mondja, Mr. Calhoun. Úgy hallottam, hogy maga kincsvadász volt. Valóban így van, vagy ez csak ostobaság?";
			link.l1.go = "portroyal_19";
		break;
		
		case "portroyal_19":
			dialog.text = "Ki mondta ezt neked? Nos, nincs értelme titkolni. Régen én is az voltam. Bár nem alakult jól, pontosan a kincsvadászat vezetett el az átkozott jezsuitákhoz és a szigethez. A szent atyák halálra kínoztak egy embert miattam, én magam pedig... ó, maradjon a múlt a múltban.\nEléggé megfizettem a bûneimért, és remélem, hogy a jövôben soha nem ismétlem meg ôket. Nem, Willy ezt nem fogja hagyni, ebben biztos vagyok!";
			link.l1 = "Figyelj, Archibald. Hallottál már valaha egy Miguel Dichoso nevû emberrôl?";
			link.l1.go = "portroyal_20";
		break;
		
		case "portroyal_20":
			dialog.text = "Még sosem hallottam ezt a nevet. Ki ez a férfi?";
			link.l1 = "Ó, semmi érdekes... csak egy férfi, aki szeret kalandokat és kincseket keresni. De mivel még nem hallottál róla, nem fogunk beszélni róla.";
			link.l1.go = "portroyal_21";
		break;
		
		case "portroyal_21":
			dialog.text = "Igen, ne beszéljünk! Beszéljünk inkább a régi Európáról! Emlékszem, húsz évvel ezelôtt Skóciában...";
			link.l1 = "...";
			link.l1.go = "portroyal_22";
		break;
		
		case "portroyal_22":
			DialogExit();
			AddDialogExitQuest("GuardOT_MCOutFromArchyRoom");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
