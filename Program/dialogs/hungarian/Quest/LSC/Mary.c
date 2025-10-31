// Мэри Каспер - взаимная любовь и офицер
void ProcessDialogEvent()
{
	ref NPChar, sld, rItm, rItem;
	aref Link, NextDiag, rType;
	int i;
	int iTime, iAddTime;
	string 	sTemp, sAttr, sGun, sBullet, attrL;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	sAttr = Dialog.CurrentNode;
	if (findsubstr(sAttr, "SetGunBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	NPChar.SetGunBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
 	    Dialog.CurrentNode = "SetGunBullets2";
 	}
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Mire van szükséged?";
			link.l1 = "Nem, semmi.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
	// ---------------------------------покушение на Акулу - вариант R --------------------------------
		// разговор в каюте Адольфа
		case "Cabin":
			dialog.text = "Marcello, én ismerem ôt. Rivados és a kalózok barátja. Adolf soha nem dolgozna vele. Szagold meg a levegôt... érzed a lôpor szagát? És vér van a falon... Megölte Adolfot, és most megpróbál átverni minket! Biztos az admirálisnak dolgozik! Öljétek meg!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LSC_Cabin_fight");
		break;
		
		// на улице
		case "Town":
			dialog.text = "Ó, elnézést... Megkérhetem, hogy segítsen nekem?";
			link.l1 = "Hm. Mindig kész vagyok segíteni egy gyönyörû hölgynek. Mi a probléma?";
			link.l1.go = "Town_1";
		break;
		
		case "Town_1":
			dialog.text = "Nézd, vettem egy ládát, tele mindenféle fémdarabokkal Sessile Gallardtól. Ô a 'Eva'. Jurgen megígérte, hogy kovácsol nekem valami jót, rendben... Megvettem, igen, de nem tudom elhozni neki. Olyan ostoba vagyok!\nHátha tudnál segíteni nekem cipelni a ládát 'Eva' Nárfal tömbjéhez 'Esmeralda'? kérlek, nagyon hálás lennék!";
			link.l1 = "És ennyi? Persze, kisasszony, segítek. Nem nagy gond.";
			link.l1.go = "Town_2";
		break;
		
		case "Town_2":
			dialog.text = "Köszönöm, köszönöm! Megmutatom a ládát.";
			link.l1 = "Asszonyom...";
			link.l1.go = "Town_3";
		break;
		
		case "Town_3":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "reload", "reload41", "LSC_EnterAevaWithMary", -1);
			LAi_ActorFollow(pchar, npchar, "", -1);
		break;
		
		case "Town_4":
			dialog.text = "És itt vagyunk... Most mondd meg, te fattyú, hol van a kulcs?!";
			link.l1 = "Hûha! Ha, úgy tûnik, nincs szükség segítségre... Mary.";
			link.l1.go = "Town_5";
		break;
		
		case "Town_5":
			dialog.text = "Okos fiú, mi? Kevesebb beszédet, a fenébe is! Hol van a kulcs? Add ide, vagy megbánod!";
			link.l1 = "Milyen bunkó! Micsoda rossz nyelv egy ilyen gyönyörû lánytól. Milyen kulcs?";
			link.l1.go = "Town_6";
		break;
		
		case "Town_6":
			dialog.text = "A kulcs, amit Adolf Barbier-tôl vettél el. És ne tagadja, látták, hogy elhagyta a kabinját. Adolf halott, és a maga mûve volt... Adja ide a kulcsot!";
			link.l1 = "Szóval mégiscsak maga volt... Ez egy hiba volt, kislány, egy nagyon nagy hiba!";
			link.l1.go = "Town_7";
		break;
		
		case "Town_7":
			PlaySound("Voice\English\LSC\Mary Casper-04.wav");
			dialog.text = "Mit mondtál? A fenébe is, te nem egy közönséges rabló vagy! Az admirálisnak dolgozik! Kapjátok el, fiúk!";
			link.l1 = "...";
			link.l1.go = "Cabin_fight";
		break;
		
	// ---------------------------------покушение на Акулу - вариант N --------------------------------
		case "caroline":
			dialog.text = "Chad, ez ô! A francba, egy segédet hozott ide! Fiúk, öljétek meg mindet!";
			link.l1 = "...";
			link.l1.go = "caroline_1";
		break;
		
		case "caroline_1":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			// Акулу к бою
			sld = characterFromId("Dodson");
			LAi_SetImmortal(sld, false);
			LAi_SetWarriorType(sld);
			sld.cirassId = Items_FindItemIdx("cirass1");
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			// устанавливаем 4 толстых нарвалов
			int iRank = 20+MOD_SKILL_ENEMY_RATE*2;
			int iScl = 65;
			for (i=1; i<=4; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("MaryGuard_"+i, "citiz_5"+(i+4), "man", "man", iRank, PIRATE, -1, true, "soldier"));
				if(i == 4) 
				{
					FantomMakeCoolFighter(sld, iRank, iScl, iScl, "topor_07", "pistol11", "bullet", iScl*2);
					sld.DontClearDead = true;
					sld.SaveItemsForDead = true;
				}
				else FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_19", "pistol5", "bullet", iScl*2);
				if (i < 3) ChangeCharacterAddressGroup(sld, "CarolineBank", "reload", "reload3");
				else ChangeCharacterAddressGroup(sld, "CarolineBank", "reload", "reload2");
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			// Мэри и Чада к бою
			sld = characterFromId("Capper");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "LSC_MarynChadDie");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
	// ---------------------------------покушение на Акулу - вариант M --------------------------------
		case "mary":
			dialog.text = "Épp idôben jöttetek... Én magam sosem bántam volna el velük... Fuh! Hogy ôszinte legyek, azt hittem, hogy végeztem!";
			link.l1 = "Úgy harcoltál, mint egy valkûr! Még sosem láttam ilyen gyönyörû lányt ilyen erôteljesen harcolni...";
			link.l1.go = "mary_1";
		break;
		
		case "mary_1":
			dialog.text = "Ha-ha, úriember vagy, nem igaz: bókolsz, miközben a kardod még mindig a kezedben van. Köszönöm a segítségét. Megmentetted az életemet, rendben! Mutatkozzon be, úriember, még sosem láttam önt. Új vagy itt?";
			link.l1 = "A nevem "+GetFullName(pchar)+", de a gyönyörû hölgyek hívhatnak "+pchar.name+". Új vagyok itt? Hm... az vagyok.";
			link.l1.go = "mary_2";
		break;
		
		case "mary_2":
			dialog.text = "Mondhatom, biztosan észrevettem volna egy ilyen jóképû férfit a környéken. A nevem Mary, Mary Casper. Bár engem Vörös Máriának hívnak. Ez azért van, mert vörös hajú vagyok, rendben.";
			link.l1 = "Örülök, hogy megismerhetem, Mary...";
			link.l1.go = "mary_3";
		break;
		
		case "mary_3":
			dialog.text = "Ó, kétszeresen is örülök... tekintve, hogy már rég halott lennék, ha te nem lennél! Az a szemét Chad nem blöffölt. Micsoda féreg! És bolond voltam, hogy nyitva hagytam az alsó ajtókat. Így jutottál be, ugye?";
			link.l1 = "Igen. Körbeúsztam a szigeten, hogy találjak egy helyet, ahol kijuthatok.";
			link.l1.go = "mary_4";
		break;
		
		case "mary_4":
			dialog.text = "Értem. Ez a nem zárt ajtó majdnem megölt engem. Jurgen maga kovácsolta nekem a zárakat, a megfelelô kulcs nélkül nem lehet kinyitni, és a zárfeltörés sem segít. Különben sem maradok nyugton, amíg valaki megpróbál bejutni - a pisztolyom négy csöve négy lyukat hagy egy ajtón vagy egy testen, ha-ha!\nDe az átkozott Chad nem hagy békén. Már gyilkosokat is küldött 'perszegyôzködni' engem, hogy álljak az ô oldalára, határozottan komolyan gondolja a dolgot. Ha te nem lettél volna, igent mondtam volna. Itt kell maradnom az ostrom alatt, "+pchar.name+", rendben! Hála Istennek, ezt elôre megjósoltam, van elég készletem, és Jürgen a szomszédom, nem veszekedtem vele.";
			link.l1 = "Mary, miért nem mesélsz többet a problémáidról? Látom, hogy szükséged van a segítségemre, de egy szót sem értettem abból, ami a szádból jött.";
			link.l1.go = "mary_5";
		break;
		
		case "mary_5":
			dialog.text = "Igen, segítségre van szükségem, rendben! Most már egyedül vagyok. Összevesztem Donalddal, aztán Chadrôl kiderült, hogy gazember. Ó, bocsánat, már megint pezsgek. Rendben, akkor elmondom, milyen helyzetbe kerültem...";
			link.l1 = "Ne feledjétek, hogy új vagyok itt, így még nem sokat értek. Ki az a Chad, aki megpróbál 'persuade' vagy megölni téged? Ki az a Donald?";
			link.l1.go = "mary_6";
		break;
		
		case "mary_6":
			dialog.text = "Chad egy kalóz Shark Dodson admirális legénységébôl, börtönôr a 'Tartarus'....";
			link.l1 = "Várj! Mit mondtál? Shark Dodson? Ô itt van?";
			link.l1.go = "mary_7";
		break;
		
		case "mary_7":
			dialog.text = "Biztosan ma este érkezett, ha ezt még nem tudja. Hol máshol lenne Shark, mint itt? A gondjaim akkor kezdôdtek, amikor néhány hónapja idejött. Bár, elismerem, ez mind Narwhals' és Rivados' hibája. Amikor Shark idejött a legénységével, bázist akart létesíteni, de a mi népünk és Rivados nagyon nem tetszett neki az ötlet. Éjszaka megtámadták Shark briggjét, és felgyújtották\nJobb, ha nem teszik! Shark legénysége tele van ördögökkel, nem emberekkel, rendben. Elôször ellenséges hajókat semmisítettek meg, majd partra szálltak, és igazi mészárlásba kezdtek. A Narwhals visszavonult, a Rivadosok pedig elfutottak, amilyen gyorsan csak tudtak. Végül a kalózok elfoglalták San Augustine-t, ahol a Sziget ellátmányának és készleteinek nagy részét tartják, majd elfoglalták Tartarust\nA cápa bebörtönözte a vezetônket, Alan Milrow-t, aki egyben a... közeli barátom is volt, és a Rivados varázslóját, Chimiset. Tartarosz ketreceiben rohadni küldte ôket, mint a vadállatokat. Innen könnyen el lehet úszni a Tartaroszba, és sikerült néhányszor meglátogatnom Alant. Ott találkoztam Chad Kapperrel, Shark börtönôrnek osztotta be. Megkértem Chadet, hogy engedje szabadon Alant, pénzt ígértem neki, de ô félt szembeszállni az admirálissal\nAztán Alant meggyilkolták a börtönben. Chad elmondta, hogy Shark tette ezt, rendben. Így hát elmentem Donaldhoz, akit Alan helyett vezérnek választottak, és követeltem, hogy azonnal támadják meg a kalózokat, ô azonban visszautasította, azt mondta, hogy azok a tengeri ördögök túl kemények nekünk. Ekkor megmondtam neki, hogy baszódjon meg\nAz embereim ebben a kérdésben semmit sem érnek, ezért megegyeztem Kapperrel, a söpredék Shark helyét akarta átvenni. Volt egy tervünk - kicsalogatni az admirálist az erôdjébôl valami árnyékos helyre, és ott megölni. Találtunk is egy mesterlövészt egy jó puskával. Ô a Fury árbocáról lôhette le az admirálist\nAz érdekes az, hogy tegnapelôtt éjjel meglátogattam a Tartarust, valami fontosat akartam mondani Chadnak a tervünkkel kapcsolatban. Kiúsztam a hajóhoz, és véletlenül meghallottam, hogy Chad két Narwhallal beszélget. Kiderült, hogy nem a Cápa ölte meg Alant. Hanem Chad. Aztán titokban pletykákat terjesztett az admirális érintettségérôl\nMiatta ölte meg. Elôször játékszernek akart az ágyába vinni. Másodszor, arra akart felhasználni, hogy megszabaduljon Sharktól - tudta, hogy én mindig bosszút állnék. El tudod képzelni? Micsoda gyáva alak!";
			link.l1 = "Igen, találkoztam már a hozzá hasonlókkal...";
			link.l1.go = "mary_8";
		break;
		
		case "mary_8":
			dialog.text = "A köcsög még rosszabb! Ô... Nem találok szavakat, hogy leírjam azt a szörnyeteget! Akkor elmentem, másnap reggel megtaláltam, és elmondtam neki mindent, amit gondoltam róla. Igen, megmondtam neki, hogy semmi közöm az admirális elleni összeesküvéséhez.";
			link.l1 = "És ez nyilvánvalóan nem tetszett neki... Ezt dühbôl tette, Mary. Óvatosabbnak kellene lenned.";
			link.l1.go = "mary_9";
		break;
		
		case "mary_9":
			dialog.text = "Nem tudom, nem tudtam befogni a számat. Az a szemét megölte Alant, és megpróbált felhasználni engem, hogy elérje a piszkos céljait! Söpredék! Igen, persze, dühös lett, és megígérte, hogy ezt még megbánom. Azt mondtam, levágom a golyóit, és megetetem a rákokkal!\nMegfenyegetett, hogy utánam küldi a narválos haverjait, ha nem gondolom meg magam. Nevettem, nem gondoltam, hogy egy narvál kezet merne emelni rám.";
			link.l1 = "Úgy tûnik, tévedtél.";
			link.l1.go = "mary_10";
		break;
		
		case "mary_10":
			dialog.text = "Igen, "+pchar.name+", alábecsültem Chadet és túlbecsültem magamat. Megtalálta azokat a szemeteket, akik megtámadtak egy magányos lányt a saját kunyhójában. És most mit tegyek? Nem bízhatok senkiben. Még a saját embereimben sem bízhatok. Ezek ketten narválok, mindkettôjüket ismertem, rendben. Amíg Chad életben van - veszélyben vagyok, még többet fog küldeni, semmi kétség\nFélek kisétálni, a mesterlövész, akit Shark meggyilkolására találtunk, Rivados területérôl lelôhet, és könnyen elmenekülhet. Nem megyek Donaldhoz, nem fog hallgatni rám\nAdmirális? Nem tudom megmagyarázni a szerepemet a merényletének elôkészítésében! El fog küldeni rohadni a 'Tartarus', celláiba, abban biztos vagyok! Bassza meg, csapdába estem. Itt fogok ülni töltött fegyverekkel, amíg el nem fogynak a készleteim, aztán... Fogalmam sincs, mi lesz velem!";
			link.l1 = "Nos, ebben az esetben nincs más választásom, mint segíteni neked, mi? A helyzeted amúgy is beleillik a terveimbe...";
			link.l1.go = "mary_11";
		break;
		
		case "mary_11":
			dialog.text = "Szándékában áll segíteni nekem? De hogyan? Meg fogod ölni Chad-et?";
			link.l1 = "Ez a terv része, persze.";
			link.l1.go = "mary_12";
		break;
		
		case "mary_12":
			dialog.text = "Figyelj, "+pchar.name+", , értékelem a szándékaidat, de Chad nem a te zónádban van. Ô az admirális egyik legmegbízhatóbb barátja, és még ha el is jutsz hozzá - Shark kalózai megölnek, nem ismerik az igazságot, rendben.";
			link.l1 = "Nyugodj meg! Úgyis beszélnem kell Sharkkal.";
			link.l1.go = "mary_13";
		break;
		
		case "mary_13":
			dialog.text = "Szóval te is kalóz vagy?! Mesélj magadról, nézz magadra: betörtél hozzám, megmentetted az életem, megígérted, hogy segítesz minden jóképûnek, mégis semmit sem tudok rólad!";
			link.l1 = "Rendben... Nem vagyok kalóz, de jelenleg egy bizonyos Jan Svenson kalózbáróval dolgozom. Azért jöttem ide, hogy megtaláljam Nathaniel Hawkot. Hallottál már róla?";
			link.l1.go = "mary_14";
		break;
		
		case "mary_14":
			dialog.text = "Nem, ki ô?";
			link.l1 = "Egy másik híres kalóz. Kár, hogy még nem találkoztál vele, biztos itt van valahol. Én is Sharkot kerestem, de nem gondoltam, hogy itt találom.";
			link.l1.go = "mary_15";
		break;
		
		case "mary_15":
			dialog.text = "De hogy kerültél ide? Túl jól nézel ki egy hajótörés túlélôjéhez képest.";
			link.l1 = "És miért gondolod, hogy hajótörést szenvedtem?";
			link.l1.go = "mary_16";
		break;
		
		case "mary_16":
			dialog.text = "Ez az egyetlen módja, hogy idejussunk. Csak Shark valahogy ide hajózott.";
			link.l1 = "Nos, nem Cápa volt az egyetlen, mint láthatod.";
			link.l1.go = "mary_17";
		break;
		
		case "mary_17":
			dialog.text = "Szóval, van hajód? Remek!";
			link.l1 = "Ne izgulj ilyen hamar, Mary. Én egy bárkán keresztül jutottam ide, de az elsüllyedt a fenekére.";
			link.l1.go = "mary_18";
		break;
		
		case "mary_18":
			dialog.text = "A-ah... Nos, ahogy mondtam - egy hajótörés. Most itt ragadtál velünk, rendben.";
			link.l1 = "Mary, hadd mondjam el a tervemet. Említetted, hogy Chad meg akarja ölni Sharkot. Nekem élve kell Shark, Jan és én a kalózok fejévé tesszük. Ezért kell figyelmeztetnem ôt, mert a történeted alapján biztos vagyok benne, hogy Chad meg fogja kísérelni a segítségeddel vagy anélkül.";
			link.l1.go = "mary_19";
		break;
		
		case "mary_19":
			dialog.text = "Igen, valószínûleg. Megvannak az emberei, hogy ezt véghezvigye...";
			link.l1 = "Ez azt jelenti, hogy az elsôdleges célom az, hogy megnyerjem Shark bizalmát és megmentsem ôt. Aztán hivatalosan is eljutok Chadhez. Van valami bizonyítékod, ami bizonyítja a szándékait?";
			link.l1.go = "mary_20";
		break;
		
		case "mary_20":
			dialog.text = "Megkaptam a levelét, amit az egyik idióta hozott ide... a padlón. Fenyegetések és részletek vannak benne, amiket az admirális érdekesnek találhat. Várj! És mi lesz velem? Shark rájön, hogy együtt dolgoztam Chaddel!";
			link.l1 = "Mary, örökké itt fogsz ülni pisztollyal felfegyverkezve, és mindenki elôl elrejted a kedves arcodat? Tényleg azt hiszed, hogy én is egy vagyok azok közül az idióták közül, akik egy gyönyörû hölgyet akarnak megölni? Elôbb mutasd meg a levelet, hadd lássam, mit tehetek...";
			link.l1.go = "mary_21";
		break;
		
		case "mary_21":
			GiveItem2Character(pchar, "letter_chad_1");
			RemoveItems(npchar, "letter_chad_1", 1);
			dialog.text = "Tessék. Mit gondolsz?";
			link.l1 = "Várj egy kicsit... (olvasás). Igen, úgy tûnik, hogy Chad egy különleges fajtájú fattyú, aki ellepi ezt a Földet. Ez a levél elég lesz ahhoz, hogy Shark maga is hurkot akasszon Chad nyakába. Ne aggódjon, hölgyem, gondoskodom róla, hogy Shark semmit se sejtsen önrôl. Úgyis túlságosan lefoglalja majd Chad.";
			link.l1.go = "mary_22";
		break;
		
		case "mary_22":
			dialog.text = "Megteszed? Ígérd meg, rendben! Esküdj meg, hogy nem árulsz el!";
			link.l1 = "Mary, esküszöm neked, hogy nem foglak elárulni. Ne aggódj emiatt, nem azért mentettelek meg, hogy ezt lássam\nChad nem fog békén hagyni, az biztos, túl sokat tudsz. Maradj itt, amíg meg nem hal.";
			link.l1.go = "mary_23";
		break;
		
		case "mary_23":
			dialog.text = "Igen, itt maradok. Nem akarom, hogy lelôjön egy orvlövész, vagy hátba szúrjon.";
			link.l1 = "Jó kislány. Zárj be minden ajtót, az alsó ajtókat is. Csak egy kulcsod van?";
			link.l1.go = "mary_24";
		break;
		
		case "mary_24":
			dialog.text = "Nem. Van még egy. Akarod?";
			link.l1 = "Igen. Bízik bennem?";
			link.l1.go = "mary_25";
		break;
		
		case "mary_25":
			dialog.text = "Nos, ha az úriember, aki megmentette az életemet, elárul engem, akkor nincs értelme élni... Vedd el.";
			link.l1 = "Ne félj, szépségem! Nem hagylak cserben. Találkozunk, amint megoldom ezt a zûrzavart. Remélem, nem tart túl sokáig.";
			link.l1.go = "mary_26";
		break;
		
		case "mary_26":
			GiveItem2Character(pchar, "key_mary");
			dialog.text = "Semmi baj, pár hétig még kibírom ezt a helyet.";
			link.l1 = "Remek. Akkor nem vesztegetem az idôt. Kiviszem a hullákat és beszélek Sharkkal. Ô a 'San Augustine', van, igaz?";
			link.l1.go = "mary_27";
		break;
		
		case "mary_27":
			dialog.text = "Igen, ô mindig ott van. És kifelé ugyanúgy, ahogyan idejöttél - nem engedem, hogy a 'Ceres Smithy'.felsô fedélzetére lépj!";
			link.l1 = "Érdekes, és miért?";
			link.l1.go = "mary_28";
		break;
		
		case "mary_28":
			dialog.text = "Mert nem tudsz majd segíteni nekem, ha meghalsz. Ez a narválok' territóriuma, és meg fognak ölni, mint kívülállót.";
			link.l1 = "Hm... Megvan. Nos, Mary, viszlát. Visszajövök, amint biztonságos lesz.";
			link.l1.go = "mary_29";
		break;
		
		case "mary_29":
			dialog.text = "Bármikor találkozhatsz velem, amikor csak akarsz, nekem nincs ezzel semmi bajom. (kuncog)";
			link.l1 = "Viszontlátásra, szépségem!";
			link.l1.go = "mary_30";
		break;
		
		case "mary_30":
			DialogExit();
			LAi_SetOwnerType(npchar);
			NextDiag.CurrentNode = "mary_wait";
			npchar.greeting = "mary_3";
			AddQuestRecord("SharkHunt", "31");
			AddQuestRecordInfo("Chad_Mary_letter", "2");
			LocatorReloadEnterDisable("CeresSmithy", "reload6", false);
			LocatorReloadEnterDisable("CeresSmithy", "reload7", false); // открываем выходы
		break;
		
		case "mary_wait":
			dialog.text = "Hello, "+pchar.name+", van valami jó hír számomra? Jól vagy?";
			if (pchar.questTemp.Saga.SharkHunt == "mary_whiskey")
			{
				link.l1 = "Az admirális problémája megoldódott. Nem érdekli, hogy levadásszon téged, Chad árulása az egyetlen dolog, ami zavarja.";
				link.l1.go = "letters";
			}
			else
			{
				link.l1 = "Még nem, Mary. De mindent megteszek, amit tudok.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "mary_wait";
		break;
		
		case "letters":
			dialog.text = "Ó, hála Istennek! Köszönöm, nem felejtem el, rendben! Legalább nem fenyeget az admirális. És mi van Chaddel? Mit csinált Shark?";
			link.l1 = "Meggyôztük a rivadókat, hogy támadják meg. Layton Dexter ôröket vitt ki 'Tartarusból' és átadta a kulcsot Fekete Eddie-nek. A fekete fickók kiszabadították a varázslójukat, Chimiset, de nem sikerült megölniük Chadot. Megölték két narvál barátját, de ô elszökött, és valahol bujkál.";
			link.l1.go = "letters_1";
		break;
		
		case "letters_1":
			dialog.text = "A francba! Ez azt jelenti, hogy most még óvatosabbnak kell lennem...";
			link.l1 = "Nyugodj meg, Mary. Biztos vagyok benne, hogy vannak még fenyegetôbb emberek, akikkel foglalkoznia kell. Valószínûleg tudja, hogy kik ültették fel a Rivadókat, hogy megtámadják ôt. Bármit megtenne, hogy megölje Cápát, nem téged.";
			link.l1.go = "letters_2";
		break;
		
		case "letters_2":
			dialog.text = "Tényleg elhiszed ezt? Chad nem az a fajta, aki ilyen könnyen elengedi a dolgokat. Túl fáradt vagyok ahhoz, hogy tovább féljek...";
			link.l1 = "Hm. Nem gondoltam volna, hogy olyan hölgy vagy, aki könnyen megijed.";
			link.l1.go = "letters_3";
		break;
		
		case "letters_3":
			dialog.text = "Ha! Nem igaz? Nem félek a szemtôl-szembe harcolástól, de a seggemen ülni és várni, hogy megöljenek? Nagyon félek "+pchar.name+", rendben!...";
			link.l1 = "Bízz bennem Mary: Kapper tele van a tányérja az admirálissal, jelenleg... Szükségem van a tanácsodra.";
			link.l1.go = "letters_4";
		break;
		
		case "letters_4":
			dialog.text = "A tanácsomra? Miféle tanács?";
			link.l1 = "Eddie talált két levelet, amit Chad írt. Olvasd el ôket, talán tudod, mire készül. Végül is benne voltál a tervben Chaddel...";
			link.l1.go = "letters_5";
		break;
		
		case "letters_5":
			RemoveItems(pchar, "letter_chad", 1);
			RemoveItems(pchar, "letter_chad_1", 1);
			dialog.text = "Adja ide ôket... (olvasás). Axel a kereskedônk a 'Esmeralda', rendben. Chad valamiért whiskyt akart venni tôle. Furcsa! Chad csak rumot iszik, szerinte a whisky 'a parasztok holdudvara'....";
			link.l1 = "És mi van a második levéllel?";
			link.l1.go = "letters_6";
		break;
		
		case "letters_6":
			dialog.text = "Marcello? Marcello Cyclops, egy volt királyi vadász. Ô a fô oka annak, hogy nem vagyok hajlandó elhagyni ezt a kunyhót.";
			link.l1 = "Ô az a mesterlövész, akit felbéreltél?";
			link.l1.go = "letters_7";
		break;
		
		case "letters_7":
			dialog.text = "Igen, uram. Marcello egy legyet is le tud lôni negyven lábról, annak ellenére, hogy hiányzik a szeme, rendben. Az volt a feladata, hogy a Santa Florentina orrvitorlájáról, vagyis a Fury platformjáról egy nagy hatótávolságú stutzen segítségével leterítse Sharkot...";
			link.l1 = "Úgy tûnik, hogy Chad úgy döntött, hogy kiiktatja Sharkot. De akkor mi értelme van Evának? Cecille? Italok?";
			link.l1.go = "letters_8";
		break;
		
		case "letters_8":
			dialog.text = "Az Eva egy semleges hajó, Cecille pedig Cecille Halard, egy vicces öregasszony, aki ott lakik. Nemrég költözött oda a Santa Florentináról. Orelie Bertine az egyik barátja. Együtt éltek itt, még azelôtt, hogy én megszülettem volna, rendben.";
			link.l1 = "Hm. Badarság. Két nagydarab legény elbújik egy öregasszony elôl, hogy együtt igyanak egy hordó whiskyt. Hülyeség... Nem a legjobb idô az ivásra, Chad!";
			link.l1.go = "letters_9";
		break;
		
		case "letters_9":
			dialog.text = "Már mondtam, hogy nem iszik whiskyt. Csak rumot, valami nem stimmel.";
			link.l1 = "Rendben, mindegy. Tudod, hol találom a Küklopszot?";
			link.l1.go = "letters_10";
		break;
		
		case "letters_10":
			dialog.text = "Nem. Nagyon zárkózott. Minden nap madarakat lô a külsô gyûrûnél, és senki sem tudja, hol alszik. Korábban gyakran járt Rivadosban.";
			link.l1 = "Micsoda balszerencse... Nos, akkor megyek és beszélek Axellel. Talán ô majd jobban megérti a dolgot. Viszlát, Mary! Csukd be az ajtót!";
			link.l1.go = "letters_11";
		break;
		
		case "letters_11":
			dialog.text = ""+pchar.name+"! Kérlek, keresd meg Chad-et. Siess, nem aludtam a legutóbbi támadás óta.";
			link.l1 = "Tarts ki, drágám. Megteszek minden tôlem telhetôt.";
			link.l1.go = "letters_12";
		break;
		
		case "letters_12":
			DialogExit();
			NextDiag.CurrentNode = "mary_wait";
			pchar.questTemp.Saga.SharkHunt = "trader_whiskey"; // флаг на магазин - поиск виски
			AddQuestRecord("SharkHunt", "35");
		break;
		
		case "happy":
			dialog.text = ""+pchar.name+"! Hogy került ide? Azért jött, hogy...";
			link.l1 = "Igen, hogy megöljelek, Mary. Jurgen kunyhóján keresztül jött ide, és egy kötélen keresztül mászott le ide.";
			link.l1.go = "happy_1";
		break;
		
		case "happy_1":
			dialog.text = "Olyan bolond vagyok, hogy elfelejtettem ezt az utat! Chad tanította meg neki, biztos vagyok benne, rendben!";
			link.l1 = "Valószínûleg. Épphogy sikerült. Utánad jött.";
			link.l1.go = "happy_2";
		break;
		
		case "happy_2":
			dialog.text = "Én meg aludtam. Egy pillanat alatt megölt volna... De honnan tudtad, hogy ide tart?";
			link.l1 = "Én voltam... Én csak megtettem, Mary.";
			link.l1.go = "happy_3";
		break;
		
		case "happy_3":
			dialog.text = "Megint megmentettél, szépfiú. Mindig a legjobbkor jössz, rendben. Hogy csinálod ezt?";
			link.l1 = "Hát, nem is tudom. A sok tehetségem egyike. Az ostromnak vége - Chad Kapper halott, és az összes barátja is. Küklopsz volt az utolsó a rohadt bandájából.";
			link.l1.go = "happy_4";
		break;
		
		case "happy_4":
			dialog.text = "Tényleg? Igaz ez, "+pchar.name+"? Nem akarsz átverni, ugye?";
			link.l1 = "Egyáltalán nem. Pihenésre van szükségem az elmúlt napok eseményei után...";
			link.l1.go = "happy_5";
		break;
		
		case "happy_5":
			dialog.text = "Most végre szabadon lélegezhetek! Köszönöm... Nagyon köszönöm! Te vagy az én hôsöm, rendben!";
			link.l1 = "Imádom, ahogy ez hangzik, hogy a hôsöd vagyok. Örülök, hogy végre biztonságban vagy.";
			link.l1.go = "happy_6";
		break;
		
		case "happy_6":
			dialog.text = "Szóval?";
			link.l1 = "Mi az, szépségem?";
			link.l1.go = "happy_7";
		break;
		
		case "happy_7":
			dialog.text = "Miért állsz ott? Gyerünk, uraim.";
			link.l1 = "És mit csináljak?";
			link.l1.go = "happy_8";
		break;
		
		case "happy_8":
			dialog.text = "Te tényleg úriember vagy... Gyere ide és ölelj meg, csókolj meg végre, ezt akarod, látom, rendben!";
			link.l1 = "Mary...";
			link.l1.go = "happy_9";
		break;
		
		case "happy_9":
			DialogExit();
			LAi_Fade("LSC_MaryRomantic_1", "");
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			StartQuestMovie(true, false, true);
			PlayStereoOGG("music_romantic");
			pchar.questTemp.LSC.MaryBye = "true"; // атрибут обязательного прощания перед телепортацией
			LocatorReloadEnterDisable("LostShipsCity_town", "reload62", false);
			LocatorReloadEnterDisable("LostShipsCity_town", "reload63", false); // открываем Церес снаружи
		break;
		
		case "happy_10":
			dialog.text = "Ne hagyj itt...";
			link.l1 = "Itt vagyok, Mary, drágám...";
			link.l1.go = "happy_11";
		break;
		
		case "happy_11":
			dialog.text = "Minden várhat. Az admirális várni fog, a kalózok várni fognak. Ez az éjszaka csak kettônkrôl szól, rendben?!";
			link.l1 = "Persze...";
			link.l1.go = "happy_12";
		break;
		
		case "happy_12":
			dialog.text = "És az összes következô éjszaka is...";
			link.l1 = "Igen, Mary.";
			link.l1.go = "happy_13";
		break;
		
		case "happy_13":
			DialogExit();
			LSC_MaryLoveWaitTime();
			SetLaunchFrameFormParam("Másnap reggel...", "", 0, 4);
			LaunchFrameForm();
			DoQuestCheckDelay("LSC_MaryRomantic_5", 4.0);
		break;
		
	// ----------------------------------вместе с Мэри на Церес Смити------------------------------------------
		case "LSC_love":
			if (pchar.questTemp.LSC.Mary == "return") // эта нода важнее даже ругани с нарвалами
			{
				dialog.text = ""+pchar.name+"! Visszajöttél... nélküle. Így nem tudott elvenni téged tôlem!";
				link.l1 = "Mary, a gyanúja alaptalan volt. Te vagy az egyetlen számomra. Mindig veled voltam a gondolataimban és az álmaimban.";
				link.l1.go = "adversary_hire_return";
				break;
			}
			if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
			{
				dialog.text = ""+pchar.name+", Miért harcolsz a narválokkal? Az ô területükön élek, tulajdonképpen én is közéjük tartozom, ha esetleg elfelejtetted volna. Kérlek, menj el Fazióhoz és kössetek békét, könyörgöm neked.";
				link.l1 = "Rendben, Mary, megteszem, amit kérsz.";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LSC.FindDolly")) // нашёл статую - прощается
			{
				dialog.text = ""+pchar.name+", Valami nyugtalanít téged. Mi a baj?";
				link.l1 = "Mary, beszélnem kell veled.";
				link.l1.go = "dolly";
				break;
			}
			if (CheckAttribute(npchar, "quest.donald"))
			{
				dialog.text = ""+pchar.name+"! Minden narvál rólad beszél!";
				link.l1 = "Tényleg, drágám?";
				link.l1.go = "donald";
				break;
			}
			if (CheckAttribute(npchar, "quest.talisman")) // подарок
			{
				dialog.text = ""+pchar.name+"! Ez a kard hihetetlen! Még egyszer köszönöm!... Én is szeretnék neked ajándékot adni. Persze, nem hasonlít a tiédhez, de szeretném, ha elfogadnád, rendben.";
				link.l1 = "Mary, az ajándék értéke nem számít... Köszönöm, szerelmem.";
				link.l1.go = "talisman";
				break;
			}
			if (stf(environment.time) >= 5.0 && stf(environment.time) < 10.0) // утро
			{
				dialog.text = "Sûrû nap áll elôtted, "+pchar.name+"? Sok szerencsét!";
				if (CheckAttribute(npchar, "quest.narval_blade"))
				{
					link.l3 = "Mary, ma meg kell látogatnunk Jürgen-t.";
					link.l3.go = "narval";
				}
				link.l1 = "Köszönöm, Mary! Nincs kétségem afelôl.";
				link.l1.go = "exit";
				link.l2 = "Nem, Mary. Pihenni akarok itt egy kicsit. Nem bánod?";
				link.l2.go = "rest_morning"; // отдых
			}
			else
			{
				dialog.text = "Nos, "+pchar.name+", hogy vagy? Szokás szerint szaladgálsz a szigeten?";
				link.l1 = "Igen, Mary. Sok mindent kell még elintézni...";
				link.l1.go = "LSC_love_1";
			}
			NextDiag.TempNode = "LSC_love";
		break;
		
		case "LSC_love_1":
			if (stf(environment.time) >= 18.0 && stf(environment.time) < 22.0) //вечер
			{
				dialog.text = "Már este van, "+pchar.name+", milyen dolgokról beszélsz? Maradjatok itt, igyunk és pihenjünk, rendben! Ez várhat reggelig!";
				link.l1 = "(nevetés) Persze, szerelmem, mondj kevesebbet...";
				link.l1.go = "LSC_love_evening";
				if (sti(pchar.money) >= 500)
				{
					link.l2 = "Mary, menjünk ma a kocsmába!";
					link.l2.go = "LSC_tavern";
				}
				link.l3 = "Mary, drágám, most nagyon elfoglalt vagyok. Késôbb visszajövök.";
				link.l3.go = "LSC_love_2";
				break;
			}
			if (stf(environment.time) >= 10.0 && stf(environment.time) < 18.0) //день
			{
				dialog.text = "Ne felejts el meglátogatni este. És ne merészelj elkerülni engem, rendben!";
				if (CheckAttribute(npchar, "quest.narval_blade"))
				{
					link.l3 = "Mária, ma meg kell látogatnunk Jürgen-t.";
					link.l3.go = "narval";
				}
				link.l1 = "Persze, Mary, hogy tudnék? Biztosan meglátogatlak.";
				link.l1.go = "exit";
				link.l2 = "Nem, Mary. Ma este itt akarok pihenni. Nem bánod?";
				link.l2.go = "rest_afternoon"; // отдых
				NextDiag.TempNode = "LSC_love";
				break;
			}
			dialog.text = "Mirôl beszélsz? Már éjszaka van! Nem, te nem mész sehova, itt maradsz velem, rendben!";
			link.l1 = "(nevetve) ahogy akarod, drágám...";
			link.l1.go = "LSC_love_night";
			NextDiag.TempNode = "LSC_love";
		break;
		
		case "LSC_love_2":
			dialog.text = "Ne is...";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "LSC_love";
		break;
		
		// сходить в таверну
		case "LSC_tavern":
			dialog.text = LinkRandPhrase("Nagyszerû ötlet, "+pchar.name+", rendben! Egyetértek!","Aye, gyerünk, "+pchar.name+"! Sanchonak remek borgyûjteménye van, van mibôl válogatni!","Ó, szívesen, rendben! Sancho kocsmájában mindig jó móka és remek borválasztéka van!");
			link.l1 = "Gyerünk!";
			link.l1.go = "LSC_love_tavern";
		break;
		
		// --> отдых
		case "rest_morning":
			dialog.text = "Természetesen a "+pchar.name+"? Persze, pihenj egy kicsit, rendben!";
			link.l1 = "Délutánig maradok...";
			link.l1.go = "rest_day";
			link.l2 = "Én maradok estig...";
			link.l2.go = "rest_evening";
		break;
		
		case "rest_afternoon":
			dialog.text = "Természetesen a "+pchar.name+"? Persze, pihenj egy kicsit, rendben!";
			link.l1 = "Én maradok estig...";
			link.l1.go = "rest_evening";
		break;
		
		case "rest_day":
			DialogExit();
			iTime = sti(environment.time);
			iAddTime = 13 - iTime;
			WaitDate("",0,0,0,iAddtime,5);
			RecalculateJumpTable();
			LAi_Fade("", "");
			if (CheckAttribute(pchar, "questTemp.LSC.MaryBye")) NextDiag.CurrentNode = "LSC_love";
			else NextDiag.CurrentNode = "LSC_love_3";
		break;
		
		case "rest_evening":
			DialogExit();
			iTime = sti(environment.time);
			iAddTime = 18 - iTime;
			WaitDate("",0,0,0,iAddtime,5);
			RecalculateJumpTable();
			LAi_Fade("", "");
			if (CheckAttribute(pchar, "questTemp.LSC.MaryBye")) NextDiag.CurrentNode = "LSC_love";
			else NextDiag.CurrentNode = "LSC_love_3";
		break;
		// <-- отдых
		
	//--> если скоро уходит через портал
		case "LSC_love_3": 
			if (pchar.questTemp.LSC.Mary == "return") // эта нода важнее даже ругани с нарвалами
			{
				dialog.text = ""+pchar.name+"! Visszajöttél... nélküle. Így nem tudott elvenni téged tôlem!";
				link.l1 = "Mária, a gyanúd alaptalan volt. Nekem csak te vagy az egyetlen. Gondolataimban és álmaimban mindig veled voltam.";
				link.l1.go = "adversary_hire_return";
				break;
			} // 291112
			if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
			{
				dialog.text = ""+pchar.name+", Miért harcolsz a narválokkal? Az ô területükön élek, valójában én is közéjük tartozom, ha esetleg elfelejtetted volna. Kérlek, menj el Fazióhoz és kössetek békét, könyörgöm neked.";
				link.l1 = "Rendben, Mary, megteszem, amit kérsz.";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(npchar, "quest.talisman")) // подарок
			{
				dialog.text = ""+pchar.name+"! Ez a kard hihetetlenül jó! Még egyszer köszönöm! Szeretnék neked is adni egy ajándékot. Persze, az értéke nem ér fel a tiédhez, de szeretném, ha elfogadnád, rendben.";
				link.l1 = "Mary, az ajándék értéke nem számít... Köszönöm, szerelmem.";
				link.l1.go = "talisman";
				break;
			}
			if (stf(environment.time) >= 5.0 && stf(environment.time) < 10.0) // утро
			{
				dialog.text = "Máris elmegy, "+pchar.name+"? Sok szerencsét, és ne feledkezz meg rólam...";
				if (CheckAttribute(npchar, "quest.narval_blade"))
				{
					link.l3 = "Mary, ma meg kellene látogatnunk Jurgen-t.";
					link.l3.go = "narval";
				}
				link.l1 = "Persze, Mary.";
				link.l1.go = "exit";
				link.l2 = "Nem, Mary. Pihenni akarok itt egy kicsit. Nem bánod?";
				link.l2.go = "rest_morning"; // отдых
			}
			else
			{
				dialog.text = "Nem mész a Kukulcan izédre, "+pchar.name+"?";
				link.l1 = "Még nem, még készülök.";
				link.l1.go = "LSC_love_4";
			}
			NextDiag.TempNode = "LSC_love_3";
		break;
		
		case "LSC_love_4":
			if (stf(environment.time) >= 18.0 && stf(environment.time) < 22.0) //вечер
			{
				dialog.text = "Már este van, "+pchar.name+". Miért nem maradsz itt? Veled akarok lenni.";
				link.l1 = "Rendben, drágám, maradok...";
				link.l1.go = "LSC_love_evening";
				if (sti(pchar.money) >= 500)
				{
					link.l2 = "Mary, menjünk ma a kocsmába!";
					link.l2.go = "LSC_tavern";
				}
				break;
			}
			if (stf(environment.time) >= 10.0 && stf(environment.time) < 18.0) //день
			{
				dialog.text = "Sok szerencsét, és ne feledkezz meg rólam... Gyere el hozzám este, ha tudsz, rendben!";
				if (CheckAttribute(npchar, "quest.narval_blade"))
				{
					link.l3 = "Mária, ma találkoznunk kell Jurgen-nel.";
					link.l3.go = "narval";
				}
				link.l1 = "Rendben, drágám.";
				link.l1.go = "exit";
				link.l2 = "Mária, szeretnék itt pihenni egy kicsit. Rendben van?";
				link.l2.go = "rest_afternoon"; // отдых
				NextDiag.TempNode = "LSC_love_3";
				break;
			}
			dialog.text = "Mirôl beszélsz? Éjszaka van! Nem, nem mész sehova, itt maradsz, rendben?!";
			link.l1 = "(nevetve) Rendben, maradok...";
			link.l1.go = "LSC_love_night";
			NextDiag.TempNode = "LSC_love_3";
		break;
		// <-- скоро уходит через портал
		
	// --> взаимоотношения - секс и прочее
		case "LSC_love_tavern":
			DialogExit();
			sld = ItemsFromID("potionrum");
			sld.shown = true;
			sld.startLocation = "FleuronTavern";
			sld.startLocator = "bottle";
			DoQuestReloadToLocation("FleuronTavern", "quest", "sit2", "LSC_MaryTavern");
		break;
		
		case "LSC_love_evening":
			DialogExit();
			//if(CheckAttribute(PChar, "IsMushketer")) SetMainCharacterToMushketer("", false);
			LSC_MaryEveneng();
		break;
		
		case "LSC_love_night":
			DialogExit();
			LSC_MaryLove();
		break;
		
		case "LSC_love_morning":
			if (CheckAttribute(npchar, "quest.hire"))
			{
				dialog.text = "Kapitány "+pchar.name+"! Mary Casper rendôr készen áll, hogy az Ön parancsnoksága alatt szolgáljon!";
				link.l1 = "Szép munka, tiszt úr! Parancsolom, hogy azonnal szálljon fel a hajóra. De elôbb: csókolja meg a kapitányát!";
				link.l1.go = "LSC_mary_hire";
			}
			else
			{
				dialog.text = "Ez csodálatos volt, szerelmem... Jó reggelt, uram!";
				link.l1 = "Jó reggelt, drágám! Csodálatos vagy!";
				link.l1.go = "LSC_love_morning_1";
			}
		break;
		
		case "LSC_love_morning_1":
			DialogExit();
			LAi_SetOwnerType(npchar);
			if (CheckAttribute(pchar, "questTemp.LSC.MaryBye")) NextDiag.CurrentNode = "LSC_love";
			else NextDiag.CurrentNode = "LSC_love_3";
		break;
		// <-- взаимоотношения
		
		// стал другом нарвалам
		case "donald":
			dialog.text = "Beszéltél Donalddal? Igaz, hogy az admirális szövetséget akart kötni Rivadossal, és harcolni a Narwhals ellen? Igaz, hogy lebeszélted errôl? Béke lesz a kalózok és a Narwhals között, igaz?";
			link.l1 = "Igen, Mary. Így van.";
			link.l1.go = "donald_1";
		break;
		
		case "donald_1":
			dialog.text = ""+pchar.name+", Nem találom a szavakat... Azt is mondják, hogy Donald barátjának tekinti magát. Lehet, hogy te leszel az egyik Narwhal, rendben!";
			link.l1 = "Találkozz Donalddal, ha tudsz - ô is békét akar kötni veled. Arra kér, hogy bocsáss meg neki a szavaiért és azért, hogy nem tudott megvédeni attól a két szemétládától.";
			link.l1.go = "donald_2";
		break;
		
		case "donald_2":
			dialog.text = "A pokolba Donalddal! Bár ennek persze örülök. Majd találkozom vele. De te! Én... nem, nem így... Büszke vagyok rád, rendben!";
			link.l1 = "Te jó ég, Mary... te... ah, megdobogtatod a szívem!";
			link.l1.go = "exit";
			NextDiag.TempNode = "LSC_love";
			DeleteAttribute(npchar, "quest.donald");
		break;
		
		// ноды прощания
		case "dolly":
			dialog.text = "Beszélgessünk! Bajban vagy?";
			link.l1 = "Nem. Mary, emlékszel arra az estére, amikor elôször találkoztunk? Miután elintéztük azt a két fattyút, mondtam neked, hogy egy hajón érkeztem ide.";
			link.l1.go = "dolly_1";
		break;
		
		case "dolly_1":
			dialog.text = "Emlékszem, igen. A bárkád elsüllyedt, és neked kellett ideúsznod... rendben!";
			link.l1 = "Hazudtam. Akkor ôrültnek tartottál volna, ha elmondom az igazat. Nem volt bárka. Egy indián isten 'Kukulcan' megmagyarázhatatlan erejét használtam, hogy eljussak erre a helyre.";
			link.l1.go = "dolly_2";
		break;
		
		case "dolly_2":
			dialog.text = ""+pchar.name+"... Mirôl beszélsz? Kukulcan?";
			link.l1 = "Mary, kedvesem, hinned kell nekem, mert semmi racionális nincs ebben, és ezt nem oszthatom meg senkivel, csak veled. Nathaniel Hawk úgy tûnt el, hogy megérintette az indián bálványt, üldözték, és az megmentette...";
			link.l1.go = "dolly_3";
		break;
		
		case "dolly_3":
			dialog.text = "";
			link.l1 = "Nathanielt kerestem. Beszélgettem egy indián sámánnal, és ugyanezt kellett tennem, mint Sólyomnak. Beleteleportáltak a 'San Augustine', rakterébe, a hajótestén lévô lyukon keresztül kijutottam, és a sors hozott el hozzád.";
			link.l1.go = "dolly_4";
		break;
		
		case "dolly_4":
			dialog.text = "Ez egy vicces történetnek kellene lennie az elsô találkozásunkról, amit egy nap elmesélünk a gyerekeinknek? Vagy megôrültél?";
			link.l1 = "Komolyan mondom, Mary. Megértem, hogy nehéz elhinni, és biztosan ôrültségnek tûnik neked, de kérlek, bízz bennem.";
			link.l1.go = "dolly_5";
		break;
		
		case "dolly_5":
			dialog.text = "Úgy tûnik, Eric történetei igazak voltak...";
			link.l1 = "Ki az az Eric? És mit mondott neked?";
			link.l1.go = "dolly_6";
		break;
		
		case "dolly_6":
			dialog.text = "Eric a helyiek egyike volt, egy öreg tengerész. Már halott. Gyerekkoromban mesélt nekem egy arany bálványról, egy szentélyrôl, ahol a Rivadók embereket áldoztak. Itt, a Szigeten\nAki megérintette, eltûnt, és soha többé nem látták. Azt hittem, hogy ezek csak mesék, amik a gyerekeket akarják megijeszteni.";
			link.l1 = "Ez igaz, Mary. Eric nem hazudott.";
			link.l1.go = "dolly_7";
		break;
		
		case "dolly_7":
			dialog.text = "Szerencsére a hajó, amelyen az a szörnyû bálvány volt, elsüllyedt. Soha nem láttam a saját szememmel.";
			link.l1 = "Megtaláltam, a fenekén nyugszik.";
			link.l1.go = "dolly_8";
		break;
		
		case "dolly_8":
			dialog.text = "Te merültél ott?! Az az átkozott feltaláló, Vedecker adta neked a ruháját? Rákok mászkálnak odalent, rendben! A rohadék! Veszélybe sodort téged!";
			link.l1 = "Mary, ne aggódj miattam. Megbirkózom a szörnyekkel. Nem olyan fenyegetôek, mint ahogy az emberek mondják. Az elsô napom óta keresem a szobrot ezen a szigeten, és végre megtaláltam.";
			link.l1.go = "dolly_9";
		break;
		
		case "dolly_9":
			dialog.text = "És most mi fog történni?";
			link.l1 = "Ez az egyetlen kiút innen. Egy ilyen bálványon keresztül jutottam ide, és ezt fogom használni, hogy visszajussak... Mary! Te sírsz? Mary! Hagyd abba!";
			link.l1.go = "dolly_10";
		break;
		
		case "dolly_10":
			if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Cápa, ";
			else sTemp = "";
			dialog.text = "Miért tenném? Sírni fogok, sírni akarok, rendben... (zokog) Az ilyenek mindig megtörténnek az én embereimmel! Megint egyedül leszek!";
			link.l1 = "Mit gondolsz, mi fog velem történni? Tényleg azt hiszed, hogy itt hagynálak?! Visszajövök érted, egy hajón. Magammal kell vinnem téged és "+sTemp+"Nathanielt is. Követsz engem a külvilágba?";
			link.l1.go = "dolly_11";
		break;
		
		case "dolly_11":
			dialog.text = "(könnyekben) Természetesen.... Persze, hogy fogok... Visszajössz értem, ugye? Hogy a fenébe akarsz visszajutni a szigetre? Csak Shark tudja, hogyan kell itt hajózni. És ne merészelj elfelejteni engem, különben elverlek, ha megtalállak!";
			link.l1 = "Mary, elég a vad gondolataidból! Persze, hogy visszajövök érted, ki más dobogtatná a szívemet ugyanúgy, mint azóta, hogy megismertelek? Ne aggódj, szerelmem, Shark megosztotta velem a koordinátákat és az útirányt. Megtalálom az utat hozzád.";
			link.l1.go = "dolly_12";
		break;
		
		case "dolly_12":
			dialog.text = "Azt mondtad, hogy egy szobor egyenesen Mainból hozott ide, de mi van, ha ez a szobor máshová visz, talán Afrikába? Mihez kezdjek akkor nélküled?!";
			link.l1 = "Kukulcan egy indián isten, valahová a Karib-tengeren belül vagy Main fog elvezetni. Már csak egy települést kell találnom, aztán könnyen megtalálom a hajómat és a legénységemet.";
			link.l1.go = "dolly_13";
		break;
		
		case "dolly_13":
			dialog.text = "(sírva) Ígérd meg... nem, esküdj meg, hogy visszajössz, rendben!";
			link.l1 = "Mary, kedvesem, esküszöm neked, hogy visszajövök. És elviszlek errôl a nyomorult helyrôl. Nem kell sokáig hiányolnod engem. Elég a könnyekbôl.";
			link.l1.go = "dolly_14";
		break;
		
		case "dolly_14":
			dialog.text = "Finom, "+pchar.name+"... ... Gyere vissza hozzám, várni fogok rád, rendben! Mikor mész el?";
			link.l1 = "Még nem tudom. Elôbb fel kell készülnöm, aztán lemerülök és megérintem a szobrot. Azt fogják mondani, hogy megfulladtam - ne higgy nekik. Minden rendben lesz.";
			link.l1.go = "dolly_15";
		break;
		
		case "dolly_15":
			dialog.text = "Megvan. "+pchar.name+", kedvesem, ölelj meg... Csókolj meg...";
			link.l1 = "Mary... Drága Mary...";
			link.l1.go = "dolly_16";
		break;
		
		case "dolly_16":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.LSC.MaryBye"); // можно телепортироваться
			DeleteAttribute(pchar, "questTemp.LSC.FindDolly");
			SetMusic("music_romantic");
			SetLaunchFrameFormParam("", "", 0, 15);
			SetLaunchFrameFormPic("loading\inside\kiss.tga");
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 10); //крутим время
			RecalculateJumpTable();
			NextDiag.CurrentNode = "LSC_love_3";
			npchar.greeting = "mary_5"; 
		break;
		
		// дарим Мэри палаш Нарвал
		case "narval":
			dialog.text = "Jürgen? Miért? Miért?";
			link.l1 = "Majd meglátod. Ez egy kellemes meglepetés lesz.";
			link.l1.go = "narval_1";
		break;
		
		case "narval_1":
			dialog.text = "Ó, milyen érdekes! Kellemes? Ez nagyszerû, rendben! Menjünk, mielôtt meghalok a kíváncsiságtól!";
			link.l1 = "Biztos vagyok benne, hogy tetszeni fog. Gyerünk, menjünk!";
			link.l1.go = "narval_2";
		break;
		
		case "narval_2":
			DialogExit();
			NextDiag.CurrentNode = "narval_wait";
			LocatorReloadEnterDisable("CeresSmithy", "reload6", true);
			LocatorReloadEnterDisable("CeresSmithy", "reload7", true);
			pchar.quest.LSC_PresentMary.win_condition.l1 = "ExitFromLocation";
			pchar.quest.LSC_PresentMary.win_condition.l1.location = pchar.location;
			pchar.quest.LSC_PresentMary.function = "LSC_GotoPresentMary";
		break;
		
		case "narval_wait":
			dialog.text = "Gyerünk, "+pchar.name+"!";
			link.l1 = "Persze...";
			link.l1.go = "exit";
			NextDiag.TempNode = "narval_wait";
		break;
		
		case "narval_3":
			dialog.text = "Nos, "+pchar.name+", , milyen meglepetést tartogatsz számomra?";
			link.l1 = "Mary! Jürgen és én úgy döntöttünk, hogy mindkettônk részérôl ajándékot készítünk neked. Ez egy egyedi penge, egy széles kard, amely a Narwhal nevet viseli. Ilyen kardból csak kettô van a világon: az elsô Alan Milrowé volt, ez a tiéd lesz. Különleges acélból készült, Jurgen mesteri kézzel kovácsolta, amely soha nem fog tompulni vagy rozsdásodni.";
			link.l1.go = "narval_4";
		break;
		
		case "narval_4":
			DialogExit();
			LAi_SetActorType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Schmidt"));
			PChar = GetMainCharacter();			
			LAi_SetPlayerType(PChar);
			sld = characterFromId("Mary");
			sld.dialog.currentnode = "narval_5";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "narval_5":
			dialog.text = "";
			link.l1 = "Kedves lányunk... Minden narvál tudja, hogy mennyit szenvedtél. Gondolom, megérdemled ezt a kardot, a Narwhal klán jelképét. Viseld büszkén. Ez a penge fenyegetést jelent majd ellenségeidre, és megvéd a csatában.";
			link.l1.go = "narval_6";
		break;
		
		case "narval_6":
			PlaySound("interface\important_item.wav");
			sld = characterFromId("Mary");
			RemoveCharacterEquip(sld, BLADE_ITEM_TYPE);
			RemoveItems(sld, "blade_17", 1);
			sTemp = GetBestGeneratedItem("blade_31");
			GiveItem2Character(sld, sTemp);
			EquipCharacterbyItem(sld, sTemp);
			sld = characterFromId("Blaze");
			dialog.text = "Jurgen? Ez... az enyém?";
			link.l1 = "Igen, Mary. "+sld.name+"  megkért, hogy készítsem el neked, és a tenger fenekérôl hozott néhány különleges vasat, ennek az anyagnak sem súlya, sem szilárdsága nem ér fel semmilyen acéllal. A lelkemet tettem ebbe a kardba, ahogyan egykor Alan kardjába is.";
			link.l1.go = "narval_7";
		break;
		
		case "narval_7":
			dialog.text = "Nem tudom, mit mondjak... Köszönöm, Jürgen! Köszönöm, rendben! Büszkén fogom viselni, és a pengének megfelelô értéket fogok képviselni, esküszöm, rendben! Nem edzettem eleget a karddal, de mostantól keményen fogok edzeni!";
			link.l1 = "Ebben nem kételkedem, kislány.";
			link.l1.go = "narval_8";
		break;
		
		case "narval_8":
			DialogExit();
			LAi_SetStayType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			PChar = GetMainCharacter();			
			LAi_SetPlayerType(PChar);
			sld = characterFromId("Mary");
			sld.dialog.currentnode = "narval_9";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "narval_9":
			dialog.text = ""+pchar.name+"... várj, nem... Te vagy a legjobb ember, akivel valaha találkoztam! Csodálatos vagy, tényleg! Tudod, hogy ez mennyit jelent nekem? Ez a kard a legjobb ajándék, amit valaha is kaphattam volna! Olyan sokat tettél már értem, kétszer is megmentetted az életemet, és mégis mindig meg tudsz lepni! Köszönöm, szerelmem!";
			link.l1 = "Nem is lehetett volna másképp, Mary. Továbbra is minden nap meg foglak lepni, az utolsó leheletemig! Mosolyod örömet okoz nekem, és örülök, hogy tetszik az ajándék.";
			link.l1.go = "narval_10";
		break;
		
		case "narval_10":
			dialog.text = "(kuncog) Köszönöm! Ilyen csodálatos penge, rendben! Erôs kézre van szükség, hogy bánjon vele... Alig várom, hogy elkezdhessek vele edzeni!";
			link.l1 = "Nem látok problémát. Siess a kabinodba, és próbáld ki az új széles kardodat!";
			link.l1.go = "narval_11";
		break;
		
		case "narval_11":
			dialog.text = "Ezt fogom tenni. Még egyszer köszönöm, uraim! "+pchar.name+"... Gyere el hozzám ma este, ha készen állsz... (kuncog)";
			link.l1 = "Természetesen, hölgyem. Este találkozunk.";
			link.l1.go = "narval_12";
		break;
		
		case "narval_12":
			DialogExit();
			EndQuestMovie();
			sld = characterFromId("Schmidt");
			sld.dialog.currentnode = "Jurgen";
			DeleteAttribute(sld, "quest.narval_blade");
			DeleteAttribute(npchar, "quest.narval_blade");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "CeresSmithy", "goto", "goto10", "LSC_MaryReturnNormal", -1);
			LocatorReloadEnterDisable("CeresSmithy", "reload6", false);
			LocatorReloadEnterDisable("CeresSmithy", "reload7", false); // открываем проход через трюм
			// владение Нарвалом повышает скилл ТО у Мэри и открывает перк тяжелой руки
			SetSelfSkill(npchar, 95, 50, 90, 90, 50);
			SetCharacterPerk(npchar, "HardHitter");
			npchar.quest.talisman = "true";
			npchar.quest.blade31 = "true";
		break;
		
		// Мэри дарит талисман
		case "talisman":
			dialog.text = "Tessék, nézze meg. Az egyik hajóban találtam a külsô gyûrûben, egy kapitányi ládában. Minden tapasztalt tengerész azt mondja, hogy ez a tárgy rendkívül értékes egy navigátor számára, képes megvédeni a hajót a legnagyobb viharoktól is. Néhányan közülük meg is akarták venni, de én nem adtam el... Szeretném, ha a tiéd lenne ez az amulett, drágám. Használd, hogy biztonságban legyél vele a tengeren.";
			link.l1 = "Köszönöm, Mary! Nagyon figyelmes tôled, szeretlek!";
			link.l1.go = "talisman_1";
		break;
		
		case "talisman_1":
			GiveItem2Character(pchar, "talisman2"); 
			PlaySound("interface\important_item.wav");
			Log_Info("Ön egy talizmánt kapott 'Jónás-tól.'");
			dialog.text = "Tényleg? Tetszik? Ó, ez nagyszerû! Annyira örülök, rendben!";
			link.l1 = "Ez egy nagyon ritka és értékes talizmán. Persze, hogy tetszik! Köszönöm, drágám!";
			link.l1.go = "talisman_2";
		break;
		
		case "talisman_2":
			DialogExit();
			DeleteAttribute(npchar, "quest.talisman");
		break;
		
	// --------------------------------------вернулся на Остров---------------------------------------------
		case "return":
			dialog.text = ""+pchar.name+"... Visszajöttél. Már vártalak, minden nap a horizontra néztem, rendben! Visszajöttél hozzám...";
			link.l1 = "Igen, Mary. Itt vagyok, ahogy ígértem. Hadd öleljelek meg, drágám!";
			link.l1.go = "return_1";
		break;
		
		case "return_1":
			dialog.text = "Ah, "+pchar.name+"... El sem tudod képzelni, mit éreztem! A narválok a halálodról beszéltek, azt mondták, hogy megfulladtál. Mindannyian biztosak voltak benne, hogy meghaltál. Én meg mondtam nekik, hogy élsz... Persze senki sem hitt nekem, azt hitték, hogy megôrültem azok után, ami történt.";
			link.l1 = "Mary... Drágám! Mi bajod van? Remegsz... Fázol?";
			link.l1.go = "return_2";
		break;
		
		case "return_2":
			dialog.text = "Nem, nem fázom. Én csak... Nem akarok itt beszélni róla. Gyere a kabinomba, ha végeztél. Kettesben akarok maradni veled, rendben... Nem mész most az admirálishoz és Nathanielhez?";
			link.l1 = "Igen. Beszélnem kell Sharkkal, és persze el kell vinnem Danielle-t Nathanielhez. Nem fog sokáig tartani. Hamarosan találkozunk, Mary.";
			link.l1.go = "return_3";
		break;
		
		case "return_3":
			dialog.text = "Alig várom, hogy... találkozzunk. Gyere minél hamarabb, rendben?";
			link.l1 = "...";
			link.l1.go = "return_4";
		break;
		
		case "return_4":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload62", "CeresSmithy", "goto", "goto11", "LSC_MaryWaitInCabin", 20.0);
		break;
		
		case "adversary":
			dialog.text = ""+pchar.name+"! Végre. Beszélnünk kell, rendben!";
			link.l1 = "Mi a baj, Mary? Látom, hogy valami bánt téged! Mi történt?";
			link.l1.go = "adversary_1";
		break;
		
		case "adversary_1":
			dialog.text = "Megtörtént... "+pchar.name+", ki az a kurva a hajódon?";
			link.l1 = "Ki az? Danielle-rôl beszélsz? De te már tudod...";
			link.l1.go = "adversary_2";
		break;
		
		case "adversary_2":
			dialog.text = "Nem, nem Danielle-rôl. Arra a szôkére gondolok, akit alig takarja ruha, és aki a hajód fedélzetén sétálgat! Láttam ôt a távcsövön keresztül, rendben!";
			link.l1 = "A-ah! Ez Helen McArthur. Ô is benne van ebben a furcsa történetben, akárcsak Danielle. Ô az én tisztem. Átmenetileg, természetesen.";
			link.l1.go = "adversary_3";
		break;
		
		case "adversary_3":
			dialog.text = "Tiszt? Ô egy tiszt?!";
			link.l1 = "Nos, igen. Mi a baj ezzel? Mary, a fenébe is! Féltékeny vagy!";
			link.l1.go = "adversary_4";
		break;
		
		case "adversary_4":
			dialog.text = "Mit gondolsz?!... (könnyekben) Egész idô alatt rád vártam, nem aludtam miattad, és te meg ide mersz jönni valami banyával....";
			link.l1 = "Mary! Ne sírj! Mi bajod van? Bárkit habozás nélkül kibelezel, mégis mindig nedves a szemed... Mary, kedvesem, Helen csak egy tiszt, aki ideiglenesen szolgál, amíg az igazságszolgáltatás meg nem történik, és a közös céljainkat el nem érjük, semmi több.";
			link.l1.go = "adversary_5";
		break;
		
		case "adversary_5":
			if (CheckAttribute(npchar, "quest.blade31")) 
			{
				sTemp = "Keményen edzettem a karddal, amit tôled kaptam, és távollétedben tökéletesen elsajátítottam.";
				notification("Nehézfegyverek +", "Mary");
			}
			else sTemp = "Keményen edzettem a pengékkel, és tökéletesen elsajátítottam ôket.";
			dialog.text = "(zokogva) Tiszt... Akkor én is a tiszted akarok lenni, rendben! Tudok harcolni, ezt te is tudod! "+sTemp+" És jól lövök! Lehet, hogy nincs tengerészeti tudásom, de gyorsan tanulok, tehetséges vagyok, rendben!";
			// проход первый - ГГ либо соглашается, либо нет, отказ ведет к полному разрыву
			link.l1 = "(egyetért) Mary... Én magam akartam felajánlani neked az állást. Nincs nálad jobb, képzettebb, tüzesebb lány! Azt akarom, hogy mellettem legyél!";
			link.l1.go = "adversary_hire";
			link.l2 = "(elutasít) Mary! Fedélzeti tisztnek lenni túl veszélyes! Nem érted, hogy mit kérsz. Nem kockáztathatom az életed.";
			link.l2.go = "adversary_fail";
		break;
		
		// отказ
		case "adversary_fail":
			dialog.text = "Te nem tudod? Szóval az a szôke kurva lehet tiszt, én meg nem? Hazudsz nekem, "+pchar.name+", egyszerûen nem akarsz velem lenni! (sírva) Az a lány jobb nálam, ugye?";
			link.l1 = "Mary, te ezt nem érted!";
			link.l1.go = "adversary_fail_1";
		break;
		
		case "adversary_fail_1":
			dialog.text = "Én igen! Láttam, hogy ragyogó szemei rád szegezôdtek! Ô nem csak egy tiszt, rendben! Megértem, hogy (zokog). Persze, nem versenyezhetek vele - ô tudja, hogyan kell vezetni egy hajót...";
			link.l1 = "Mary, mirôl beszélsz!";
			link.l1.go = "adversary_fail_2";
		break;
		
		case "adversary_fail_2":
			dialog.text = "Vége... (sírva) Menj el! Menj el a kurvádhoz! Én pedig itt maradok... Nem megyek sehova! Add ide a kulcsomat!";
			link.l1 = "De Mary...";
			link.l1.go = "adversary_fail_3";
		break;
		
		case "adversary_fail_3":
			RemoveItems(pchar, "key_mary", 1);
			dialog.text = "Menj el...";
			link.l1 = "...";
			link.l1.go = "adversary_fail_4";
		break;
		
		case "adversary_fail_4": // обидел Мэри - больше от неё ничего не получишь
			DialogExit();
			LAi_CharacterDisableDialog(npchar);//запрет диалога
			for (i=0; i<=3; i++)
			{
				LocatorReloadEnterDisable("LostShipsCity_town", "reload6"+i, true); // закрываем вход к Мэри
			}
			DoQuestReloadToLocation("LostShipsCity_town", "reload", "reload62", "");
			pchar.questTemp.LSC.Mary = "fail";
			AddQuestRecord("LSC", "23");
			bQuestDisableMapEnter = false; //открыть карту
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
		break;
		
		// соглашаемся
		case "adversary_hire":
			// проход второй - смотрим, Элен может стать подругой или нет
			bOk = (CheckAttribute(pchar, "questTemp.HelenDrinking.GaveCutlass")) && (sti(pchar.questTemp.Saga.HelenRelation) >= 6);
			if (bOk || sti(pchar.questTemp.Saga.HelenRelation) >= 5 || CharacterIsAlive("Longway"))
			{
				dialog.text = "Tényleg? Tényleg azt akarta, hogy én legyek a tisztje? "+pchar.name+", a fenébe is, el sem tudod képzelni, mennyire boldog vagyok! Annyira szeretnék a tiszted lenni... de nem egy hajón azzal a szôkével!";
				link.l1 = "Mary, de miért?!";
				link.l1.go = "adversary_hire_no";
			}
			else
			{
				dialog.text = "Tényleg? Tényleg azt akarta, hogy én legyek a tisztje? "+pchar.name+", a fenébe is, el sem tudod képzelni, mennyire boldog vagyok! Esküszöm, nem hagylak cserben, meglátod!";
				link.l1 = "Jézusom, Mária, drágám, te drága vagy. Az elôbb még sírtál, most meg felragyog az arcod! És, Mária, te nem csak egy újabb tiszt vagy nekem. Több vagy annál, és kétlem, hogy bármi módon is cserben tudnál hagyni.";
				link.l1.go = "adversary_hire_yes";
			}
		break;
		
		case "adversary_hire_no": // Мэри не пойдёт, пока не ГГ не расстанется с Элен. Выбирай, кто тебе милее...
			dialog.text = "Lehet, hogy te csak a tisztednek tekinted, bár kétlem, hogy ô csak a kapitányát látja benned. Láttam, hogy nézett rád, ismerem ezt a tekintetet, jól van! Csak én tudok ilyen pillantásokat vetni rád!";
			link.l1 = "Mary, drágám, de már megmondtam neked, hogy nem érzek iránta semmit, és kész! Semmi sincs köztünk! Esküszöm, a fenébe is! Szükségem van a segítségére, hogy a Parti Testvériségen belüli zûrzavarral foglalkozzam. Jan Svenson nem fog segíteni nekem Tortuga elfogásában, ha nem segítek neki, és szükségem van rá!";
			link.l1.go = "adversary_hire_no_1";
		break;
		
		case "adversary_hire_no_1":
			dialog.text = ""+pchar.name+", Kedvesem, ölelj meg... Sajnálom. Hiszek neked. De nem fogok tudni a közelében maradni, és nézni, ahogy flörtölni próbál veled, rendben! Végül is fogom a kardomat és kettéhasítom!";
			link.l1 = "Igen, ezt biztosan megteheted... Eléggé indulatos vagy, mi?";
			link.l1.go = "adversary_hire_no_2";
		break;
		
		case "adversary_hire_no_2":
			dialog.text = "És ha megölöm ôt - elhagysz engem, rendben... Sosem bocsátanám meg magamnak.";
			link.l1 = "Szóval mit javasolsz, Mary? Mit tegyek vele?";
			link.l1.go = "adversary_hire_no_3";
		break;
		
		case "adversary_hire_no_3":
			dialog.text = "Azt mondta, hogy ô egy ideiglenes tiszt. Csatlakozom önökhöz, amint a szárazföldön hagyják. Valami lakatlan szigeten reményeim szerint megfeneklik (kuncog) A világ végére is követni foglak, rendben! "+pchar.name+", kedvesem, tényleg jobb nálam?";
			link.l1 = "Hülyeség! Ne beszélj így, Mary, drágám, nincs nálad jobb nô!...";
			link.l1.go = "adversary_hire_no_4";
		break;
		
		case "adversary_hire_no_4":
			dialog.text = "Akkor bizonyítsd be nekem. Nem akarlak megosztani, "+pchar.name+"! Inkább egyedül maradok, minthogy mással osszalak meg, rendben...";
			link.l1 = "Rendben, Mary. Akkor kössünk üzletet. Nem szabadulhatok meg most Helentôl, ô fontos ehhez a törekvéshez. Segítek neki a problémáiban, Isla Tesoro úrnôjévé teszem, elengedem, és nem marad köztünk semmi. Remélhetôleg ez nem tart tovább egy-két hónapnál. Vársz rám ennyi ideig?";
			link.l1.go = "adversary_hire_no_5";
		break;
		
		case "adversary_hire_no_5":
			dialog.text = "Persze, hogy megvárom, rendben! Ez az én döntésem... Ha visszatérsz hozzám, az azt jelenti, hogy engem választottál helyette. És ha nem térsz vissza... akkor ez az én sorsom. Itt maradok, és megalapítom a saját klánomat. Casper klán...";
			link.l1 = "Megint sírsz? Mary, gyerünk. Elég ebbôl a hülyeségbôl! Mirôl beszélsz? Melyik klán... Buta lány, persze, hogy visszatérek, nem mernélek itt hagyni ezek között a rohadt öreg hajók között! Elárasztanád a szigetet a könnyeiddel!";
			link.l1.go = "adversary_hire_no_6";
		break;
		
		case "adversary_hire_no_6":
			dialog.text = "Térj vissza, amilyen hamar csak lehet... "+pchar.name+", édesem, csókolj meg, kérlek...";
			link.l1 = "Visszajövök. Ígérem!"; // ага, а мы посмотрим, обманешь или нет
			link.l1.go = "adversary_hire_no_7";
		break;
		
		case "adversary_hire_no_7":
			DialogExit();
			SetMusic("music_romantic");
			SetLaunchFrameFormParam("", "", 0, 15);
			SetLaunchFrameFormPic("loading\inside\kiss.tga");
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 10); //крутим время
			RecalculateJumpTable();
			NextDiag.CurrentNode = "LSC_love"; // оставляем штучки с Мэри на Острове в силе
			pchar.questTemp.LSC.MaryWait = "true";
			AddQuestRecord("LSC", "22");
			bQuestDisableMapEnter = false; //открыть карту
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
		break;
		
		// повторный разговор после расставания с Элен
		case "adversary_hire_return":
			dialog.text = "Most szórakozol velem? "+pchar.name+", tényleg nem felejtettél el engem?";
			link.l1 = "Persze, hogy elfelejtettem! Megcsaltalak valaha is? Sok mindenen mentem keresztül a szakításunk alatt, és nem áll szándékomban újra elválni tôled... a talizmánom.";
			link.l1.go = "adversary_hire_yes";
			DeleteAttribute(pchar, "questTemp.LSC.MaryWait");
		break;
		
		case "adversary_hire_yes": // Элен заведомо не друг - Мэри идёт сразу, либо если выбрал Мэри
			dialog.text = "Tényleg? "+pchar.name+"! Mindig követni foglak! Soha nem fogok hazudni neked, soha nem foglak elárulni, esküszöm!";
			link.l1 = "Hiszek neked, kedvesem... Én sem fogok."; // а куда же ты денешься )
			link.l1.go = "adversary_hire_yes_1";
		break;
		
		case "adversary_hire_yes_1":
			dialog.text = ""+pchar.name+", Drágám, ölelj meg... Együtt leszünk, ugye? Mondd el!";
			link.l1 = "Igen, együtt leszünk, Mary. Örökké.";
			link.l1.go = "adversary_hire_yes_2";
		break;
		
		case "adversary_hire_yes_2":
			dialog.text = "Mint Danielle és Nathaniel?";
			link.l1 = "(nevetés) Igen, pont mint ôk.";
			link.l1.go = "adversary_hire_yes_3";
		break;
		
		case "adversary_hire_yes_3":
			dialog.text = ""+pchar.name+"... Szeretlek! Hozzád megyek, ha akarod, rendben...";
			link.l1 = "Kedves Mary... Persze - majd késôbb megbeszéljük. Az életednek ezen a hajótemetôn vége, elôbb vigyünk ki innen - Isten hozott a hajóm fedélzetén és a nagyvilágban, szerelmem!";
			link.l1.go = "adversary_hire_yes_4";
		break;
		
		case "adversary_hire_yes_4":
			dialog.text = "Töltsük együtt az utolsó éjszakát ezen a szigeten, a 'Ceres Smithy'. csak mi ketten. Csak te és én... Nem engedlek el sehova, amíg el nem jön a reggel, rendben!";
			link.l1 = "Nos, nem az én hajómon vagyunk, úgyhogy követem a parancsodat... Drága Mary!";
			link.l1.go = "adversary_hire_yes_5";
		break;
		
		case "adversary_hire_yes_5":
			DialogExit();
			npchar.quest.hire = "true";
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			SetMusic("music_romantic");
			DoQuestCheckDelay("LSC_LastNight_CS", 3.0);
			bQuestDisableMapEnter = false; //открыть карту
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
		break;
		
		case "LSC_mary_hire":
			dialog.text = "Igenis, uram!";
			link.l1 = "...";
			link.l1.go = "LSC_mary_hire_1";
		break;
		
		case "LSC_mary_hire_1":
			DialogExit();
			DoQuestReloadToLocation("LostShipsCity_town", "reload", "reload62", "LSC_Mary_hire");
			if (pchar.questTemp.LSC.Mary != "return") AddQuestRecord("LSC", "24");
			pchar.questTemp.LSC.Mary = "officer";
			RemoveItems(pchar, "key_mary", 1);
		break;
		
	// --> консультации по морским сражениям
		case "sea_bomb":
			dialog.text = ""+pchar.name+"! Van egy ötletem...";
			link.l1 = ""+npchar.name+"? Itt nem biztonságos, és megparancsoltam, hogy maradj a hajón...";
			link.l1.go = "sea_bomb_1";
		break;
		
		case "sea_bomb_1":
			dialog.text = ""+pchar.name+", annyi puskapor van ezen az öreg teknôben, hogy ha felrobban, az egész sziget az égbe repül. Most már mindegy, hogy hol maradsz. Csak hallgassatok rám!";
			link.l1 = "Hallgatlak, kérlek, siess.";
			link.l1.go = "sea_bomb_2";
		break;
		
		case "sea_bomb_2":
			dialog.text = "A kalózkorvett és a fregatt. Azt hiszik, hogy mi is az övék vagyunk... Kés, rendben. Ez egy lehetôség lehet számunkra. Fogjunk néhány hordó puskaport, egy gyújtózsinórt, és hajózzunk feléjük.\nHa közelebb engednek minket, meggyújtjuk a gyújtózsinórt, a hordót az egyik hajónak dobjuk, és elhajózunk, amilyen gyorsan csak tudunk. Biztos tökéletes alkalom lehet, hogy tûzijátékot lássunk... Mit gondoltok?";
			link.l1 = "Kockázatos, de a terved talán beválik... Csak ha nem ismernek fel minket.";
			link.l1.go = "sea_bomb_3";
		break;
		
		case "sea_bomb_3":
			dialog.text = "Kockáztassuk meg, "+pchar.name+"?";
			link.l1 = "Jól van. Lássunk hozzá! Fiúk! Fogjatok három hordó puskaport! Elmegyünk innen a pokolba! Imádom a fantáziádat, "+npchar.name+"... Én magam sosem jutottam volna erre az ötletre.";
			link.l1.go = "sea_bomb_4";
		break;
		
		case "sea_bomb_4":
			dialog.text = "Mondtam, hogy van tehetségem!";
			link.l1 = "...";
			link.l1.go = "sea_bomb_5";
		break;
		
		case "sea_bomb_5":
			chrDisableReloadToLocation = false;
			DialogExit();
			LAi_SetOfficerType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			npchar.dialog.currentnode = "Mary_officer";
			pchar.questTemp.Saga.BarbTemptation.Bomb = "true";
			AddQuestRecord("BarbTemptation", "15");
			AddQuestUserData("BarbTemptation", "sName", "Mary");
			pchar.questTemp.Saga.BarbTemptation.adviser = "Mary";
		break;
		
		case "fugas":
			dialog.text = "Igen, persze, drágám. Mindig készen állok segíteni, rendben! Mi a baj?";
			link.l1 = "Jackman hajója a Sabo-Matila-öbölben van, a nehéz fregatt 'Centurion'. Ez a hajó egykor a Hawkes-ok tulajdona volt, tehát Jackman kabinjában fontos tárgyaknak és dokumentumoknak kell lenniük... fel kell szállnunk rá.";
			link.l1.go = "fugas_1";
		break;
		
		case "fugas_1":
			dialog.text = "Értem. Hogyan fogod ezt végrehajtani a mi kis madarunkon? Több emberük és ágyújuk van. Belenéztem a távcsôbe, rendben!";
			link.l1 = "Igazad van. Jackmannak legalább kétszer annyi embere van, mint nekünk, és mindegyikük képzett mészáros és zsoldos. Ôrültség lenne megfelelô elôkészületek nélkül a fedélzetre lépni. Egy elhúzódó tengeri csata sem jöhet szóba. Ezért más lehetôségeken gondolkodtam a feladat elvégzésére.";
			link.l1.go = "fugas_2";
		break;
		
		case "fugas_2":
			dialog.text = ""+pchar.name+", még nem ismertek fel minket ellenségként, akárcsak azok az idióták a törököknél... Megpróbálhatjuk újra a trükkünket...";
			link.l1 = "Mary, az imént mondtam, hogy fel kell szállnunk a fregattra, a süllyesztés nem jöhet szóba.";
			link.l1.go = "fugas_3";
		break;
		
		case "fugas_3":
			dialog.text = "Tudom, hogy "+pchar.name+". nem fogjuk elsüllyeszteni. Figyelj, fogunk néhány üres rumos hordót, és megtöltjük ôket puskaporral, grapeshot-tal és rövid gyújtózsinórral. Aztán közelebb hajózunk a fregattjukhoz, és a rögtönzött robbanóanyagot a fedélzetükre dobjuk.";
			link.l1 = "Ha! Tényleg azt hiszed, hogy ez mûködni fog?";
			link.l1.go = "fugas_4";
		break;
		
		case "fugas_4":
			dialog.text = "És miért is ne? Az ô szabaddeszkájuk magasabb, mint a miénk, de két-három ember egy csiga segítségével könnyedén fel tud emelni és el tud dobni egy teljesen megrakott hordót. Kiáltunk - 'Tessék, itt van egy kis ingyen rum Knive-tól! És a hordók felrobbannak, mielôtt még reagálni tudnának.";
			link.l1 = "A robbanó lövedék a legjobb embereit a fedélzeten darált hússá változtatja... A fenébe, ez csábítóan hangzik.";
			link.l1.go = "fugas_5";
		break;
		
		case "fugas_5":
			dialog.text = "Használjunk öt hordót. "+pchar.name+", megvan a meglepetés ereje. Semmit sem fognak sejteni! Azonnal el kell vitorláznunk, mielôtt azonban a fedélzetre szállnak.";
			link.l1 = "Nos, próbáljuk meg. Nem azonosíthatnak minket, mielôtt eldobjuk a hordókat... A fenébe is, nem lesz könnyû közel kerülni hozzájuk. Jackman nem olyan idióta, mint Ghoul volt.";
			link.l1.go = "fugas_6";
		break;
		
		case "fugas_6":
			dialog.text = "Kockáztassuk meg, "+pchar.name+"! Úgysem fog fájni.";
			link.l1 = "Jó érv, nincs vesztenivalónk... Készítsétek fel a fougasseseket!";
			link.l1.go = "fugas_7";
		break;
		
		case "fugas_7":
			dialog.text = "Úgy lesz, kapitányom! Tökéletesen felkészítem ôket, rendben!";
			link.l1 = "Hé, a szigeten nem hagyták, hogy elkábítsd azokat a rákokat, szóval most itt hagyom, hogy szétlôjj néhány kalóz segget... Mary, csodálatos vagy!";
			link.l1.go = "fugas_8";
		break;
		
		case "fugas_8":
			dialog.text = "Köszönöm, "+pchar.name+"! Nem hagylak cserben!";
			link.l1 = "Ebben nem kételkedem. Remélem, hogy mi vagyunk azok, akik nem hagyunk cserben azzal, hogy elcsesszük a tervedet... Fegyverbe!";
			link.l1.go = "fugas_9";
		break;
		
		case "fugas_9":
			DialogExit();
			npchar.dialog.currentnode = "Mary_officer";
			pchar.questTemp.Saga.BarbTemptation.Fugas = "true";
			AddQuestRecord("BarbTemptation", "21");
			DeleteAttribute(npchar, "quest.fugas");
		break;
		// <-- консультации по морским сражениям
		
		// --> суп из черепахи
		case "terrapin_grot":
			dialog.text = "Hát itt vagy! Nem volt könnyû megtalálni téged... Ez elképesztô volt, sapka! Soha nem láttam még ilyen lélegzetelállító ugrást! Mindig te vagy a hôsöm! Bár bevallom, majdnem szívrohamot kaptam tôled\nEgyszer még megölsz ezekkel a trükkökkel, kedvesem... Hát most ki a fene lenne ô? Ó "+pchar.name+", egy pillanatra hagytalak kicsúszni a kezeim közül, és a következô pillanatban már körülvesznek a ribancok hordái!";
			link.l1 = "Mary, ez 'slag' a Catherine Fox, Fox ezredes, a Sea Foxes parancsnokának lánya. El kell vinnünk Antiguára.";
			link.l1.go = "terrapin_grot_1";
		break;
		
		case "terrapin_grot_1":
			dialog.text = "Ó, tényleg? Micsoda öröm! Rendben, mesélni fogsz róla... ma este, amikor kettesben töltjük az éjszakát. Most pedig menjünk, sietnünk kell!";
			link.l1 = "Te vagy a legjobb, Mary. Mihez kezdenék nélküled? Catherine, gyere!";
			link.l1.go = "terrapin_grot_2";
		break;
		
		case "terrapin_grot_2":
			DialogExit();
			npchar.dialog.currentnode = "Mary_officer";
			LAi_SetOfficerType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			Terrapin_GotoShip();
		break;
		// <-- суп из черепахи
		
		// --> калеуче
		case "on_coast":
			dialog.text = "Végre felébredtél, drágám... Szemétláda! Soha többé ne ijessz rám így!";
			link.l1 = "Mary... drágám, mi történt? Szétrepedt a fejem...";
			link.l1.go = "on_coast_1";
		break;
		
		case "on_coast_1":
			dialog.text = "Amikor beléptünk a kapitány kabinjába, te a padlón feküdtél, mozdulatlanul, mint egy hulla. A szívem majd megdobbant! A srácok felkaptak, és a hajónkhoz vonszoltak - éppen idôben, mert a fedélzeten fekvô halottak újra emelkedni kezdtek\n Micsoda rémálom! Nem tudtunk velük mit kezdeni! Gyorsan elvágtuk a köteleket, és megpróbáltunk elhajózni, de a hajójukról érkezô sortûz súlyosan megrongálta a hajónkat, és elvesztettük az irányítást. Igazi ördögök voltak, bizony! Aztán felhúzták a vitorlákat, és egy szempillantás alatt eltûntek\nA hajónk zátonyra futott, így erre a partra kellett menekülnünk, mielôtt a vihar elpusztíthatta volna. Sok jó ember meghalt ma, de a hajó végül is túlélte...";
			link.l1 = "Szép munka, Mary... Mihez kezdenék nélküled?";
			link.l1.go = "on_coast_2";
		break;
		
		case "on_coast_2":
			dialog.text = "Talán megfulladtál volna, vagy a hajón maradtál volna, és a halottak széttépnének... Még mindig remeg a kezem!";
			link.l1 = "Köszönöm, szerelmem. Mióta vagyok kint?";
			link.l1.go = "on_coast_3";
		break;
		
		case "on_coast_3":
			dialog.text = "Egy egész napot. Kitisztítottam a sebeidet, gyógyszert adtam neked, és rumot öntöttem beléd. Hamarosan meggyógyulsz. És ne merészelj meghalni nekem!";
			link.l1 = "Ígérem, hogy ezúttal nem halok meg, drágám. Bár nem érzem magam túl jól...";
			link.l1.go = "on_coast_4";
		break;
		
		case "on_coast_4":
			dialog.text = "Az biztos... A 'Flying Dutchman', sapka volt az? Miért támadtak meg minket? És miért nem lôttek a beszállás elôtt?";
			link.l1 = "A kapitányuknak szüksége volt az amulettre, amirôl Tuttuathapakkal, az indiai sámánnal beszéltem. Ezért kellett a fedélzetre lépniük, de amint a kapitányuk elvette az amulettet, már nem volt ránk szükségük... Micsoda rémálom! Egy hajó, amelyen halottak vannak! Hihetetlen...";
			link.l1.go = "on_coast_5";
		break;
		
		case "on_coast_5":
			dialog.text = "Igen, úgy tûnik, a 'repülô holland' elôbb-utóbb eljön értünk. Ha lesz rá lehetôségem, elmegyek a templomba, gyújtok egy gyertyát a csodás szülésünkért, és imádkozom a mi Urunkhoz...";
			link.l1 = "Én is, Mary, azt hiszem. Vissza kell mennem abba a faluba. Tudatni Tuttuathapakkal, hogy mi történt. Az a hajó az amulett miatt támadott meg minket! Remélem, annak a vörösbôrû ördögnek van magyarázata arra, hogy mi a fenének volt rá egyáltalán szüksége azoknak az élôholtaknak.";
			link.l1.go = "on_coast_6";
		break;
		
		case "on_coast_6":
			dialog.text = "Rendben. De légy óvatos - a sebeid alig gyógyultak be.";
			link.l1 = "Te vagy az egyetlen gyógyszer, amire szükségem van. És... Mary, szeretlek...";
			link.l1.go = "on_coast_7";
		break;
		
		case "on_coast_7":
			dialog.text = "Én is szeretlek, drágám...";
			link.l1 = "...";
			link.l1.go = "on_coast_8";
		break;
		
		case "on_coast_8":
			chrDisableReloadToLocation = false;//открыть локацию
			DialogExit();
			npchar.dialog.currentnode = "Mary_officer";
			LAi_SetOfficerType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			AddQuestRecord("Caleuche", "5");
		break;
		// <-- калеуче
		
	// --> Мэри вне LSC
		// секс - Мэри не отказывает никогда
		case "cabin_sex":
			dialog.text = RandPhraseSimple(""+pchar.name+", nincs nagyobb boldogság számomra, mint a karjaidban lenni, rendben... Gyerünk, menjünk!",""+pchar.name+", szeretnék veled lenni minden ébren töltött pillanatban, ha lehetséges lenne. Gyerünk!");
			link.l1 = RandPhraseSimple("Te vagy a legjobb, szerelmem...","Csodálatos vagy, talizmánom...");
			link.l1.go = "exit";
			pchar.quest.sex_partner = Npchar.id;
			AddDialogExitQuestFunction("LoveSex_Cabin_Go");
		break;
		
		case "sex_after":
			dialog.text = RandPhraseSimple("Kedvesem, csodálatos voltál... mindig az vagy!","Nagyszerû volt!");
			link.l1 = RandPhraseSimple("Örülök, hogy boldog vagy, szerelmem...","Szeretlek Mary...");
			link.l1.go = "exit";
			NextDiag.TempNode = "Mary_officer";
			chrDisableReloadToLocation = false;//открыть локацию
			npchar.quest.daily_sex = true;
			DeleteAttribute(npchar, "quest.iwantsex"); // belamour для бесконфликтности квестов							
			SetFunctionTimerCondition("Mary_SexReady", 0, 0, 1, false);
		break;
		
		case "room_sex":
			if (CheckAttribute(pchar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "tavern")
			{
				dialog.text = ""+pchar.name+", Nincs nagyobb boldogság számomra, mint a karjaidban lenni, rendben... De ez nem a legjobb idôpont - el kell kapnunk azt a söpredék Thibaut-t, mielôtt elszökik.";
				link.l1 = "Igazad van, mint mindig, kislányom...";
				link.l1.go = "exit";
				break;
			}
			dialog.text = RandPhraseSimple(""+pchar.name+", nincs nagyobb boldogság számomra, mint a karjaidban lenni, rendben... Gyerünk, menjünk!",""+pchar.name+", minden pillanatban veled szeretnék lenni, ha lehetséges lenne. Gyerünk, menjünk!");
			link.l1 = RandPhraseSimple("Te vagy a legjobb, kislányom...","Csodálatos vagy, vörös hajú talizmánom...");
			link.l1.go = "room_sex_go";
		break;
		
		case "room_sex_go":
			DialogExit();
			pchar.quest.sex_partner = Npchar.id;
			chrDisableReloadToLocation = true;//закрыть локацию
			if (sti(pchar.money) >= 10) AddMoneyToCharacter(pchar, -10);
			if (npchar.chr_ai.type == "actor")
			{
				LAi_SetOfficerType(npchar);
				LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			}
			if (findsubstr(locations[FindLocation(pchar.location)].id, "tavern_upstairs" , 0) == -1)
			{
			//DoQuestReloadToLocation(pchar.location+"_upstairs", "quest", "quest4", "");
			DoFunctionReloadToLocation(pchar.location+"_upstairs", "quest", "quest4", "LoveSex_Room_Go");
			ChangeCharacterAddressGroup(npchar, pchar.location+"_upstairs", "quest", "quest3");
			} // patch-8
			//DoQuestFunctionDelay("LoveSex_Classic", 2.5);
			NextDiag.CurrentNode = "sex_after";
			npchar.greeting = "mary_hire";
		break;
		
		// требует секса, если давно не давал
		case "givemesex":
			dialog.text = RandPhraseSimple(""+pchar.name+", túl régen volt már, hogy szexeltünk... Teljesen megfeledkeztél rólam, rendben! Drágám, pihenni akarok, vegyünk egy szobát éjszakára, és hagyjuk a gondjainkat egy másik napra!",""+pchar.name+", túl elfoglalt voltál, és kezdem azt hinni, hogy teljesen megfeledkeztél rólam! Drágám, szeretnék... veled maradni négyszemközt. Vegyünk ki egy szobát éjszakára, rendben!",""+pchar.name+", elment az eszed? Szeretném veled tölteni az éjszakát, borozgatni és pihenni. Túlságosan elfoglalt voltál a tengeren, és teljesen megfeledkeztél rólam!");
			link.l1 = "Mary, drágám, mirôl beszélsz - 'teljesen megfeledkeztél rólam'? buta lány... De tényleg túlságosan elfoglalt voltam, a figyelmemet igénylô problémák végtelenek. Bocsáss meg nekem, szerelmem. Menjünk fel az emeletre, éjszakára csak a tiéd vagyok, a világ várhat!";
			link.l1.go = "room_sex_go";
		// belamour legendary edition -->
			link.l2 = RandPhraseSimple(RandPhraseSimple("Ma nem, kedvesem. Fáj a fejem.","Mary, drágám, hogy tudnék rólad megfeledkezni? Gyere, késôbb - van egy kis dolgunk..."),RandPhraseSimple("Mindig rád gondolok, Mary, de most nem engedhetjük meg magunknak, hogy pihenjünk.","Mary "+npchar.lastname+", ma nincs idônk ostobaságokra."));
			link.l2.go = "room_sex_goNS";
		break;
		
		case "room_sex_goNS":
		if(sti(pchar.reputation.fame) > 60)
		{
			ChangeCharacterComplexReputation(pchar,"authority", 2);
			if (npchar.chr_ai.type == "actor")
			{
				LAi_SetOfficerType(npchar);
				LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			}
			NextDiag.TempNode = "Mary_officer";
			chrDisableReloadToLocation = false;
			npchar.quest.daily_sex = true;
			DeleteAttribute(npchar, "quest.iwantsex"); 
			SetFunctionTimerCondition("Mary_SexReady", 0, 0, 1, false);
			pchar.quest.Mary_giveme_sex.over = "yes"; 
			pchar.quest.Mary_giveme_sex1.over = "yes";
			dialog.text = "Nos... Mi mást mondhatnék... Igenis, kapitány!";
			link.l1 = "...";
			link.l1.go = "exit";
		}
		else
		{
			if(bImCasual) Log_Info("To refuse Mary become more famous");
			ChangeCharacterComplexReputation(pchar,"authority", -2);
			dialog.text = "Charles...";
			link.l1 = "Mary, drágám, mirôl beszélsz - 'teljesen megfeledkeztél rólam'? buta lány... De tényleg elfoglalt voltam, ezek a problémák végtelenek. Bocsáss meg nekem, kislányom. Menjünk fel, a világ várhat!";
			link.l1.go = "room_sex_go";
		}
		break;
		// <-- legendary edition
		// ругается за то, что ходил по борделям, ГГ изворачивается
		case "brothel":
			dialog.text = "Igen, ott van! Már nem kedvelsz engem, ugye? Mondd meg nekem!";
			link.l1 = "Mi van?! Mary, milyen ostobaságot beszélsz? Miért gondolod ezt?";
			link.l1.go = "brothel_1";
		break;
		
		case "brothel_1":
			dialog.text = "Akkor miért látogattad azokat a ribancokat, azokat a bordélyházi kurvákat? Tudom, hogy igen, ne hazudj nekem! Nem tetszik valami bennem, amikor szeretkezünk, ugye? (sírva) Mondd meg...";
			link.l1 = "Mary, Mary... nyugodj meg, kérlek, kislányom. Igen, voltam már néhányszor a bordélyházban, de csak üzleti ügyben. Nem akartam szórakozni!";
			link.l1.go = "brothel_2";
		break;
		
		case "brothel_2":
			dialog.text = "És miféle 'üzleti ügyek' vittek fel az emeletre a baszószobába? (zokog) Hazudsz, "+pchar.name+"!";
			link.l1 = "Mary, kedvesem, hagyd abba végre... Tényleg volt néhány üzleti ügyem a bordélyház úrnôjével.  És néhányszor felmentem az emeletre. Legutóbb a kormányzó személyes ügyében - megkért, hogy keressem meg a jegygyûrûjét. Hogy utasíthattam volna vissza Ôexcellenciáját?";
			link.l1.go = "brothel_3";
		break;
		
		case "brothel_3":
			dialog.text = "";
			link.l1 = "És hogyan magyarázhattam volna meg a szeretônek, hogy az emeleti ágy alatt kell keresgélnem? Nem tudtam. Így hát egy kurvát kellett vennem éjszakára, hogy felengedjenek az emeletre... Másodszorra azt mondták nekem, hogy egy kereskedô elvesztette ott a hajója iratait. Megint fizetnem kellett egy lányért, hogy átkutathassam a szobát, és jól megfizettek az iratokért...";
			link.l1.go = "brothel_4";
		break;
		
		case "brothel_4":
			dialog.text = "";
			link.l1 = "Harmadszor a helyi parancsnoknak segítettem: Egy helyôrségi tisztrôl kellett kérdeznem a kurvákat. Ezt a tisztet kémkedéssel és kalózokkal való kapcsolattal gyanúsították. Végül elkaptuk, és szép jutalmat kaptam érte...";
			link.l1.go = "brothel_5";
		break;
		
		case "brothel_5":
			dialog.text = "";
			link.l1 = "Látja? Én mondom, az egész az üzletrôl szólt. Mary, te vagy az egyetlen, akit szeretek és akire szükségem van. Te vagy a legjobb, esküszöm! Tényleg azt hiszed, hogy valami mocskos kikötôi kurvát fogok csinálni, amikor te itt vagy nekem? Hogy gondolhatsz így rám!";
			link.l1.go = "brothel_6";
		break;
		
		case "brothel_6":
			dialog.text = ""+pchar.name+"... Ez mind igaz? Ôszinte vagy hozzám? Nem voltál velük?";
			link.l1 = "Mary, kedvesem, te vagy az egyetlen nô, akit szeretek, ez igaz. Gyere közelebb, drágám. Hadd öleljelek meg... Töröld le a könnyeidet, és kérlek, ne légy féltékeny! Soha többé nem fogok bordélyházba járni, ha ezt akarod!";
			link.l1.go = "brothel_7";
		break;
		
		case "brothel_7":
			dialog.text = "Igen, ezt akarom!... "+pchar.name+", féltékeny vagyok, mert szeretlek... És nem akarlak elveszíteni, rendben! Hallasz engem? Megölök minden ribancot, aki egy centivel is közelebb mer jönni hozzád!";
			link.l1 = "Nyugodj meg... Nem kell senkit sem megölni. És nem fogsz elveszíteni, ígérem. Minden rendben, nyugodj meg. Te vagy az egyetlenem és a legjobb lány a világon... Bízz bennem, hogy az vagy.";
			link.l1.go = "brothel_8";
		break;
		
		case "brothel_8":
			DialogExit();
			SetLaunchFrameFormParam("", "", 0, 5);
			SetLaunchFrameFormPic("loading\inside\kiss.tga");
			LaunchFrameForm();
			pchar.GenQuest.BrothelLock = true; // все, больше не походишь по борделям :)
			DeleteAttribute(pchar, "GenQuest.BrothelCount");
		break;
		
		// на Тайясаль
		case "tieyasal":
			dialog.text = ""+pchar.name+", micsoda furcsa kérdés? Én szeretlek téged. Megmentettél. Én vagyok a vörös hajú talizmánod - tényleg azt hiszed, hogy hagylak egyedül odamenni? Ne is számíts rá, rendben! Veled vagyok! Mikor indulunk?";
			link.l1 = "Igazad van, kedvesem, furcsa kérdés volt... Majd késôbb elmondom, amikor megyünk. Elôbb fel kell készülnünk.";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "Készen állok, kapitányom! Követni foglak a túlvilágra!";
			link.l1 = "Köszönöm, szerelmem...";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			DialogExit();
			AddQuestRecord("Tieyasal", "19");
			npchar.quest.Tieyasal = "teleport";
		break;
		
		// Jason Дороже золота
		case "GoldenGirl":
			pchar.quest.Mary_giveme_sex1.over = "yes"; // fix 22-03-20
			pchar.questTemp.MarySexBlock = "true"; // fix 22-03-20
			dialog.text = "Mi ez a nagy felfordulás, kapitány? Spanyolok, kalózok vagy még rosszabb?";
			link.l1 = "Ez rosszabb, Mary, sokkal rosszabb. A kormányzó egy rendkívül drága kurtizánnál szándékozik látogatást tenni, és nekem el kell kísérnem ôt, mint érdekszemélyt, ahogy azt a szeretônek megígérte. Unalmas beszélgetések, túlárazott bor és unalmas nemesek.";
			link.l1.go = "GoldenGirl_1";
			link.l2 = "Épp ellenkezôleg, egy nemes hölgy által vezetett társasági eseményre szóló meghívás terhe. Ôexcellenciája meglepett, amikor megkért, hogy kísérjem el, de hogy ôszinte legyek, alig várom, hogy eltereljem a gondolataimat.";
			link.l2.go = "GoldenGirl_3";
		break;
		
		case "GoldenGirl_1":
			dialog.text = "Valóban?! Egy kurtizán? Úgy mondod' ezt, mintha nem lenne nagy ügy, mi? Csak egy kis szórakozás Ôexcellenciájával? Charles, te most...";
			link.l1 = "Mary, nyugodj meg, kérlek! Nem azért megyek oda, hogy... ez nem egy bordélyház! Nos, bordélyház, de a fenébe is, ha nem vagyok nemes és szavahihetô ember. Tényleg nem bízik bennem? A kormányzó csak egy kis szívességet kért tôlem, és nekem kötelességem eleget tenni neki, ennyi az egész!";
			link.l1.go = "GoldenGirl_2";
		break;
		
		case "GoldenGirl_2":
			dialog.text = "Igen, hallottam egy pár 'nemesemberrôl' ilyenrôl, rendben. Láttam ôket a társaságodban is. Az udvariasság mindennapos szükséglet számukra! 'magas' társadalom, 'méltóságteljes' szórakozás a seggem! Még egy házasság sem akadályozza meg ôket abban, hogy meglátogassák ezeket a... hölgyeket. A francba, nem is tudtam, hogy te is olyan vagy, mint ôk. Mi még csak nem is... Csesszétek meg, mindannyian!";
			link.l1 = "Mary, várj! Baszd meg...";
			link.l1.go = "GoldenGirl_6";
		break;
		
		case "GoldenGirl_3":
			dialog.text = "Megérdemeltük a szabadságot. Szerinted elviselik, ha egy vörös kabátba öltözött hölgyet látnak? Képzeld el a suttogást a sarkokban! Valaki biztosan elájul, az jó móka lenne, nem?";
			link.l1 = "Mary, kedvesem, ez nem az a fajta parti, ahová egy hölgyet visznek... legalábbis egy olyan hölgyet, mint te. Nos, ez egy kicsit bonyolult, de hadd magyarázzam el...";
			link.l1.go = "GoldenGirl_4";
		break;
		
		case "GoldenGirl_4":
			dialog.text = "Hû, ne fáradj. Csak mondd meg egyenesen: nem vagyok elég jó azoknak a parókás faszoknak. Egy egyszerû lány, szórakozásból, mi? Túlságosan zavarban vagy, hogy megmutasd magad elôttem? Nem elég jó a puccos partikhoz, igaz, tisztelt Charles de Maure úr?";
			link.l1 = "Nem, egyáltalán nem. Ön csodálatos, és nem érdekel, hogy milyen benyomást keltünk a körülöttünk lévô emberekben. A kormányzó az én segítségemmel próbálja megoldani a problémáit, mint mindig. Olyan leszek, mint egy értékes trófea a teremben. Egy érdekes vendég, aki lenyûgözi a nemes semmirekellôket.";
			link.l1.go = "GoldenGirl_5";
		break;
		
		case "GoldenGirl_5":
			dialog.text = "Akkor tehát nem vagyok jó neked, ugye? Értem, rendben van, a nemesek a nemeseknek valók, a parasztok az egyszerû szórakozásra. Sok szerencsét a felsôbb osztályodhoz. Majd beszélünk, ha visszatértél a mi szerény földünkre, rendben?";
			link.l1 = "Mary, várj! Baszd meg...";
			link.l1.go = "GoldenGirl_7";
		break;
		
		case "GoldenGirl_6":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "GoldenGirl_GirlExit", 10.0);
			pchar.questTemp.GoldenGirl.Angry1 = "true";
		break;
		
		case "GoldenGirl_7":
			DialogExit();
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "GoldenGirl_GirlExit", 10.0);
			pchar.questTemp.GoldenGirl.Angry2 = "true";
		break;
		
		case "GoldenGirl_10":
			dialog.text = "Sok szerencsét a felsôbb osztályodhoz. Majd beszélünk, ha visszatértél szerény földünkre, igen.";
			link.l1 = "Mary, gyerünk!";
			link.l1.go = "GoldenGirl_11";
		break;
		
		case "GoldenGirl_11":
			DialogExit();
			NextDiag.CurrentNode = "GoldenGirl_10";
		break;
		
		case "GoldenGirl_12":
			dialog.text = "Ezt nézd meg, igen! Az elôkelô társaságban elveszett kapitányunk!";
			link.l1 = "...";
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Angry1")) link.l1.go = "GoldenGirl_13";
			else link.l1.go = "GoldenGirl_17";
		break;
		
		case "GoldenGirl_13":
			dialog.text = "Egész napra eltûntél a bordélyházban, és most a városban mindenki errôl beszél. Charles, mondj egyetlen jó okot, hogy miért most beszéljek veled, ahelyett, hogy mondjuk a Narwalnak mutogatnád a... hasadat? Nem sokat törôdsz velem, ugye?!";
			link.l1 = "Mary, mindent megmagyarázok, csak késôbb. Fel kéne készülnöm, és párbajra mennem. Nyugodtan megölhetsz, ha ezt túlélem. Addig is, kérlek, vigyázz az új hajónkra, rendben? Tegnap este nyertem egy kártyajátékban.";
			link.l1.go = "GoldenGirl_14";
		break;
		
		case "GoldenGirl_14":
			dialog.text = "Felejtsd el a hajót, mondtál valamit a párbajról, igaz? A helyiek mindenféle baromságokat mesélnek, amire én nem hallgatok. Azt mondják, hogy vagy a király fiával vagy magával a kibaszott pápával kell megküzdened. Mondd el, mi a fasz folyik itt?!";
			link.l1 = "Ez az ember egy nagyon befolyásos nemes fattyúja, de Levi Vantadur grófja. Ô volt az, aki elôször is kihívott engem, és meg kell nyernem a párbajt anélkül, hogy kárt tennék benne, hogy elkerüljem az apja haragját.";
			link.l1.go = "GoldenGirl_15";
		break;
		
		case "GoldenGirl_15":
			dialog.text = "Míg én a seggemen ülök a kádon, amit most nyertél? Megôrültél, Charles?";
			link.l1 = "Attól tartok, így kell lennie. A kormányzó biztosított nekem néhány nemes tisztet, akik a másodtisztjeim lesznek, hogy utána elkerüljük a zûrzavart. Téged vagy bármelyiküket nem vihetlek magammal a párbaj hivatalos tisztasága érdekében. Ez túl komoly, sajnálom.";
			link.l1.go = "GoldenGirl_16";
		break;
		
		case "GoldenGirl_16":
			dialog.text = "Tudod, mit fogok most tenni? Elmegyek arra az átkozott hajóra, és rendesen leiszom magam, aye! Csinálj, amit akarsz, de ha a nemes kurva nem fog megölni, esküszöm, hogy én magam teszem meg!";
			link.l1 = "Mary, minden rendben lesz, bízz bennem! Várjatok... Bassza meg! Már megint itt vagyunk!";
			link.l1.go = "GoldenGirl_21";
		break;
		
		case "GoldenGirl_17":
			dialog.text = "Ott van! Egész nap egy szót sem kaptunk tôled! Aggódtunk, amikor meghallottuk a piacon keringô pletykákat. Azt mondják, hogy hajókra és nôkre játszottál, és még párbajba is keveredtél valami koronás herceggel, vagy akár magával a pápával! Mi a fene folyik itt?";
			link.l1 = "Ez bonyolult, Mary. Eltart egy darabig, amíg elmagyarázom. De sikerült megnyernem egy fregattot. Neked kell vigyáznod rá, amíg én rendezem a vitámat az elôzô tulajdonosával.";
			link.l1.go = "GoldenGirl_18";
		break;
		
		case "GoldenGirl_18":
			dialog.text = "Szóval igazuk volt a párbajjal kapcsolatban, igaz? Ki az a nemes faszfej? Miért harcolsz vele?";
			link.l1 = "Muszáj lesz. Bonyolult, de röviden: megnyertem a hajóját és a... hölgyét. Nyilvánosan megvádolt csalással, és párbajra hívott ki. Ez az ember egy igen befolyásos nemes fattya, de Levi Vantadur gróf fattyúja. Mindent meg kell tennem, hogy ne bántsam ôt.";
			link.l1.go = "GoldenGirl_19";
		break;
		
		case "GoldenGirl_19":
			dialog.text = "Egy hölgy? Megértem, hogy egy hajóért játszanak, de... egy nô, tényleg? Igazat beszéltek az utcán, mi? Csak így beismered?! Mintha... az egyik idióta matrózod lennék?";
			link.l1 = "A fenébe is, Mary, ez egyáltalán nem így van! Ô szerezte meg a kormányzótól, én pedig visszaszereztem tôle, hogy szabadon engedjem, ennyi az egész. Semmi többrôl nincs szó, esküszöm!";
			link.l1.go = "GoldenGirl_20";
		break;
		
		case "GoldenGirl_20":
			dialog.text = "Hát, lehet, hogy nálatok, nemeseknél ez normális, de én nem vagyok ilyen, rendben! Tégy, amit akarsz, mondj, amit akarsz... menj és halj meg érte, ha akarsz! Én elmegyek arra a kibaszott hajóra, amit megnyertél, és leiszom magam. Azt hittem, hogy ez az egész valódi és... örökké fog tartani. Azt hiszem, túl sokat vártam!";
			link.l1 = "Mary, én leszarom azt a nôt! Csak várj, kérlek... Bassza meg! Már megint itt tartunk...";
			link.l1.go = "GoldenGirl_21";
		break;
		
		case "GoldenGirl_21":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "GoldenGirl_GirlToFregat", 15.0);
		break;
		
		case "GoldenGirl_24":
			dialog.text = "Charles, értem jöttél, rendben! Tudtam, sosem kételkedtem benne! Annyira örülök, hogy látlak!";
			link.l1 = "Én is, Mary! Egész idô alatt megölt engem ez az egész. Hála Istennek, hogy jól vagy!";
			link.l1.go = "GoldenGirl_25";
		break;
		
		case "GoldenGirl_25":
			if (pchar.questTemp.GoldenGirl == "alarm_fin")
			{
				dialog.text = "Egyébként, mit tettél pontosan, hogy ilyen könnyen elengedtek? Egy igazi verekedés vagy lövöldözés nélkül, rendben! Ó, és láttam ezt a gyönyörû hölgyet a fedélzeten, amikor kirángattak. Mi történt, Charles?";
			}
			else
			{
				dialog.text = "Pontosan mit tettél, hogy csak úgy elengedtek? Semmi verekedés, semmi lövés, rendben! Láttam néhány brit pávát a fedélzeten, amikor kihoztak. Mi volt ez az egész, Charles?";
			}
			link.l1 = "Csak az számít, hogy újra velem vagy. Cserbenhagytalak, Mary. Annyira sajnálom! Remélem, hogy a szívedben megtalálod a bocsánatot! Gyûlölöm, ahogyan a legutóbbi dolgok köztünk maradtak.";
			link.l1.go = "GoldenGirl_26";
		break;
		
		case "GoldenGirl_26":
			dialog.text = "Már megtörtént. Én is sajnálom, rendben? Bárcsak ne vettem volna annyira magamra a dolgaidat azzal a nôvel... ...akkor aznap éjjel rendes ôrséget állítottam volna fel. Soha nem kaptak volna el minket ilyen könnyen! Olyan ostoba voltam!";
			link.l1 = "A múlt az múlt. Szeretlek, és soha többé nem hagylak el így. Ígérem!";
			link.l1.go = "GoldenGirl_27";
		break;
		
		case "GoldenGirl_27":
			dialog.text = "Tudtam, hogy sosem hagynál el, rendben? Sajnálom, hogy valaha is kételkedtem benned, Charles! Úgy tûnik, jobb, ha nem tudom, hogy pontosan mit is tettél, ugye? Újra együtt vagyunk, és csak ez számít.";
			link.l1 = "Nincsenek titkaim elôtted. Elmondom neked...";
			link.l1.go = "GoldenGirl_28";
		break;
		
		case "GoldenGirl_28":
			DialogExit();
			SetLaunchFrameFormParam("Eltelt egy kis idô...", "", 0.1, 3.0);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 0);
			npchar.dialog.currentnode = "GoldenGirl_28_1";
			LAi_SetActorType(npchar);
			LAi_ActorDialogDelay(npchar, pchar, "", 4.0);
		break;
		
		case "GoldenGirl_28_1":
			if (pchar.questTemp.GoldenGirl == "alarm_fin")
			{
				dialog.text = "Micsoda történet... kétlem, hogy bárki más elhinné, rendben! Én már az elejétôl fogva tudtam! Tudtam, hogy a 'játékos' éjszakád vicces volt! Azok a nemes pávák... szívtelen állatok! Legalább nem tévedtem veled kapcsolatban, tudtam, hogy más vagy, rendben!";
				link.l1 = "Biztos vagyok benne, hogy sokan sokkal rosszabbnak tartanak engem. Egy igazi szörnyeteg a mesékbôl.";
			}
			else
			{
				dialog.text = "Micsoda történet... kétlem, hogy bárki más elhinné, rendben! Én már az elejétôl fogva tudtam! Tudtam, hogy a 'playful' night vicces üzlet! Politika, kémek, csalások... És te megint megmentettél minket, rendben?! Az én hôsöm!";
				link.l1 = "Ebben nem vagyok biztos. Valószínûleg néhány héten belül háború lesz Angliával. De megtettem, amit kellett, Mary. Te jelentesz nekem mindent.";
			}
			link.l1.go = "GoldenGirl_29";
		break;
		
		case "GoldenGirl_29":
			if (pchar.questTemp.GoldenGirl == "alarm_fin")
			{
				dialog.text = "Nem érdekel, mit gondolnak az emberek, ha így lesz, te leszel a szörnyetegem, Charles! A többiek vagy menjenek és sírjanak emiatt, vagy foglalkozzanak velem! Ne feledd, hogy mindig melletted maradok, rendben!";
			}
			else
			{
				dialog.text = "Tudom, Charles. Mindig is tudtam, de olyan jó hallani, hogy kimondod. Tudd meg - én mindig melletted leszek, rendben!";
			}
			link.l1 = "Soha nem kételkedtem ebben, Mary. Menjünk, a fiúk aggódnak. Ideje vitorlát bontani és elhúzni innen a fenébe. Ismét mellettem vagy, és a horizont magától nem megy sehova.";
			link.l1.go = "GoldenGirl_30";
		break;
		
		case "GoldenGirl_30":
			dialog.text = "Igenis, kapitány!";
			link.l1 = "";
			link.l1.go = "GoldenGirl_31";
		break;
		
		case "GoldenGirl_31":
			DialogExit();
			npchar.dialog.currentnode = "Mary_officer";
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "sea", "none", "", "", "GoldenGirl_GirlGoOnBoard", 10.0);
			GoldenGirl_MaryBlockDelete(); // fix 22-03-20
		break;
		
		case "GoldenGirl_32":
			dialog.text = "Charles, ez tényleg te vagy? Majdnem elvesztettem minden reményt, rendben! Istenem, annyira hiányoztál! Kérlek, kérlek, bocsáss meg nekem!";
			link.l1 = "Nem, bocsáss meg, nem láttam, hogy ez lesz... Hála Istennek, Mary, hogy eljöttél! Annyira boldog vagyok!";
			link.l1.go = "GoldenGirl_33";
		break;
		
		case "GoldenGirl_33":
			dialog.text = "Ha már a megbocsátásnál tartunk - hogy teljesen ôszinte legyek, azon gondolkodom, hogy lelôjelek vagy megöleljelek. Jobb, ha elmondod, mi a fene folyik itt, rendben?";
			link.l1 = "Szeretlek, Mary! Ez minden, amit el akartam mondani neked.";
			link.l1.go = "GoldenGirl_34";
		break;
		
		case "GoldenGirl_34":
			dialog.text = "Igen, mintha ez segítene, de... A fenébe, én is, Charles. Én is szeretlek, igen. Istenem, végre együtt vagyunk!";
			link.l1 = "És nem akarom azzal tölteni az idôt, hogy olyan dolgokról beszélgetünk, amik nem számítanak. Gyere velem, és nem merlek elhagyni ma este. Még akkor sem, ha leszakad az ég erre a nyomorult városra. Soha többé nem hagylak el. Soha többé.";
			link.l1.go = "GoldenGirl_35";
		break;
		
		case "GoldenGirl_35":
			dialog.text = "Úgy tûnik, jobb, ha nem tudom, hogy pontosan mit is tettél, ugye? Újra együtt vagyunk, és csak ez számít.";
			link.l1 = "Nincsenek titkaim elôtted. Elmondom neked...";
			link.l1.go = "GoldenGirl_36";
		break;
		
		case "GoldenGirl_36":
			DialogExit();
			SetLaunchFrameFormParam("Eltelt egy kis idô...", "", 0.1, 3.0);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 0);
			npchar.dialog.currentnode = "GoldenGirl_36_1";
			LAi_SetActorType(npchar);
			LAi_ActorDialogDelay(npchar, pchar, "", 4.0);
		break;
		
		case "GoldenGirl_36_1":
			dialog.text = "Azt mondod, hogy ez a márki segített neked visszahozni engem? És majdnem háborút indítottál Anglia és Franciaország között, igaz? Ne értsen félre - ez olyan romantikus meg minden, de mi lesz most? ";
			link.l1 = "Fogalmam sincs, Mary. Újra együtt vagyunk, a többi lényegtelen. Ha a hatalmon lévôk nem sikerül a szônyeg alá söpörniük... nos, én kész vagyok teljesíteni a kötelességemet a korona elôtt.";
			link.l1.go = "GoldenGirl_37";
		break;
		
		case "GoldenGirl_37":
			dialog.text = "És az a márkinô? Ôt is visszahoztad? A portugálok elismerôen beszéltek róla. Biztosított róla, hogy ellenálltál a közeledésének, mint a Bastille várának. Hinni akarok neki, de ezt tôled kell hallanom!";
			link.l1 = "Semmi sincs Botot asszony és köztem, Mária. Én segítettem neki, ô segített nekem, ez minden. Ha már Bartholomew-ról beszélünk, hol van?";
			link.l1.go = "GoldenGirl_38";
		break;
		
		case "GoldenGirl_38":
			dialog.text = "Elment, rendben. Elhajózott, miután idehozott engem. Soha nem akartam abba az átkozott kuplerájba menni, ezért kibérelt nekem egy szobát, elôre kifizette pár hétre, és csak úgy elment. Ó, majdnem elfelejtettem, rendben! Van egy levelem a számodra!";
			link.l1 = "Egy levél? Bartholomewtól, a portugáltól? Ez valami újdonság. Nem tetszik, hova vezet ez...";
			link.l1.go = "GoldenGirl_39";
		break;
		
		case "GoldenGirl_39":
			dialog.text = "Gyerünk, olvasd el. Megyek, megnézem a fiúkat. Valószínûleg aggódtak. Mindenki ideért? Remélem, nem bánod, ha iszunk egy-két pohárral odalent. Ne keverd magad még egy balhéba, rendben!";
			link.l1 = "Persze, de kérlek, légy óvatos velük, Mary. Inkább veled tölteném az estét, minthogy részeg hullákat kelljen visszahordanom a hajóra. Istenem, még mindig nem hiszem el, hogy visszakaptalak!";
			link.l1.go = "GoldenGirl_40";
		break;
		
		case "GoldenGirl_40":
			DialogExit();
			npchar.dialog.currentnode = "Mary_officer";
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "GoldenGirl_SPGirlReturn", 10.0);
			GoldenGirl_MaryBlockDelete(); // fix 22-03-20
		break;
		
		// Jason Долго и счастливо
		case "LongHappy":
			RemoveItems(pchar, "potionwine", 2);
			dialog.text = "A tengerpart, te, én és egy jó bor - Charles, ez annyira romantikus! Gyakrabban kéne ezt csinálnunk, rendben!";
			link.l1 = "Örülök, hogy tetszik. Azt hiszem, ezentúl több idôt szánunk egymásra az ilyen alkalmakra.";
			link.l1.go = "LongHappy_1";
		break;
		
		case "LongHappy_1":
			dialog.text = "Mirôl beszélsz? Valami történt a hajóval, mi? Miért térdelsz, szerelmem?";
			link.l1 = "Mert szeretlek, Mary. Te is tudod, én is tudom, mindenki tudja. Ezért itt és most, a tengerrel és az éggel szemben arra kérlek téged, Mary Casper - hogy add meg nekem azt a megtiszteltetést, hogy velem együtt állj az emberek és Isten elôtt annyi napig, amennyit a magasból kapunk. Én, Charles de Maure, chevalier de Monper, megkérdezlek téged - leszel-e a feleségem?";
			link.l1.go = "LongHappy_2";
		break;
		
		case "LongHappy_2":
			if (pchar.location == "Shore36")
			{
				dialog.text = "Megálmodtam, hogy halljam, rendben! Én... tudod a válaszomat, Charles... ó, bocsánat!";
				link.l1 = "Nem baj, ez csak bor, és sosem szerettem ezt az inget...";
				link.l1.go = "LongHappy_3";
			}
			else
			{
				dialog.text = "Charles, természetesen igen! Igen, igen, ezerszer is igen!!! Te... ez a hely... semmi sem tehet engem boldogabbá!!! Istenem, annyira boldog vagyok, rendben!";
				link.l1 = "Boldoggá tettél, Mary. És inni akarok rád, égô Karib Napom!";
				link.l1.go = "LongHappy_4";
			}
		break;
		
		case "LongHappy_3":
			DialogExit();
			chrDisableReloadToLocation = true;//закрыть локацию
			DoQuestFunctionDelay("LoveSex_Classic", 1.0);
			npchar.dialog.currentnode = "LongHappy_5";
			LAi_SetStayType(npchar);
		break;
		
		case "LongHappy_4":
			dialog.text = "Igyunk rád, kapitányom és jövendôbeli férjem, rendben! Te vagy a legjobb, ami valaha történt velem!";
			link.l1 = "De ez csak a kezdet - nekünk! És a közös jövônkre! Annyi minden van még elôttünk!";
			link.l1.go = "LongHappy_6";
		break;
		
		case "LongHappy_5":
			dialog.text = "Igyunk rád, kapitányom és jövendôbeli férjem, rendben! Te vagy a legjobb, ami valaha történt velem!";
			link.l1 = "De ez még csak a kezdet - nekünk! És a közös jövônknek! Annyi minden van még elôttünk!";
			link.l1.go = "LongHappy_6";
		break;
		
		case "LongHappy_6":
			DialogExit();
			chrDisableReloadToLocation = false;
			npchar.dialog.currentnode = "Mary_officer";
			LongHappy_MarryToSenPierre();
		break;
		
		case "LongHappy_7":
			dialog.text = "Charles, Benoit apát megint Martinique-on van, úgyhogy folytathatjuk, ugye? De nem fogok ruhát viselni, még egy istentisztelet kedvéért sem, remélem, nem sértôdsz meg?";
			link.l1 = "Mary, szeretlek bármilyen ruhában, és... nos, tudod... Bármit felvehetsz, amit csak akarsz, foglalkozom azzal, akinek ezzel problémája van! De csak konzultálni akartam veled a vendégekrôl és a szertartásról.";
			link.l1.go = "LongHappy_8";
		break;
		
		case "LongHappy_8":
			if (LongHappy_CheckSaga())
			{
				dialog.text = "Tudod, a legtöbben, akik ôszintén örülhetnek a boldogságunknak, még a városba sem léphetnek be, nemhogy a templomba, rendben. Ezért - házasodjunk meg itt, az összes fontos emberrel, ahogyan az várható volt, aztán hajózzunk át Isla Tessoróra, és ünnepeljünk rendesen, igazi barátokkal! Mit gondolsz, rendben?";
				link.l1 = "Nagyszerû lehetôség! Akkor csináljuk. Beszélek Benoit apáttal, de ki kell küldenünk a meghívókat és még...";
				link.l1.go = "LongHappy_9";
			}
			else // Сага провалена по времени или утоплен Центурион
			{
				dialog.text = "Tudod, nincs sok barátom, kivéve a srácokat a legénységbôl. Szóval hívjátok meg azokat, akiket szükségesnek tartotok, én meg csak örülök annak, ami van, rendben!";
				link.l1 = "Ahogy mondod, édesem. Beszélek Benoit apáttal, és mindent megszervezek, méltó vagy a legpompásabb ceremóniára.";
				link.l1.go = "LongHappy_9a";
			}
		break;
		
		case "LongHappy_9":
			dialog.text = "Ne aggódj, mint jó feleség, magamra vállalom az elôkészületek egy részét, rendben. Írok a barátainknak, és mindent elintézek, de elôbb mondd meg: hogyan képzeled ezt az esküvôt?";
			link.l1 = "Az én ideálom te, én és a legközelebbi barátaink. A sok hivatalos arc után itt Martinique-on, szeretnénk egy kis ôszinteséget.";
			link.l1.go = "LongHappy_10";
			link.l2 = "Emlékeznünk kell erre a napra. Hívjatok mindenkit! Senki sem maradhat ki!";
			link.l2.go = "LongHappy_11";
		break;
		
		case "LongHappy_9a":
			dialog.text = "Veled együtt, egy szertartás a hajó lelkészével a fedélzeten, a naplemente alatt a tengeren, elég lenne, rendben. De ha ezt akarod - ünnepelni fogunk! Charles... Most sírni fogok, ölelj meg, rendben...";
			link.l1 = "Mary...";
			link.l1.go = "LongHappy_9b";
		break;
		
		case "LongHappy_9b":
			dialog.text = "Ennyi, nyugodt vagyok, rendben. Sajnálom, ez az egész olyan szokatlan. De Charles, mint jó feleség, átveszem a szervezést. A fiúknak is kell szerveznünk egy partit, rendben, de nem valószínû, hogy az egész csapat elfér a templomban. Elintézem a kocsmával, de szükségünk lesz piára és pénzre - tudod, hogy a tengerészek szeretnek bulizni.";
			link.l1 = "Rendben, ezt 's mi 'fogjuk csinálni. Mire kell felkészülnöm?";
			link.l1.go = "LongHappy_9c";
		break;
		
		case "LongHappy_9c":
			pchar.questTemp.LongHappy.MarryMoney = 100000;
			pchar.questTemp.LongHappy.MarryRum = 100;
			if (sti(RealShips[sti(pchar.ship.type)].Class) < 2)
			{
				pchar.questTemp.LongHappy.MarryMoney = 200000;
				pchar.questTemp.LongHappy.MarryRum = 150;
			}
			if (GetCompanionQuantity(pchar) > 1)
			{
				pchar.questTemp.LongHappy.MarryMoney = 300000;
				pchar.questTemp.LongHappy.MarryRum = 200;
			}
			dialog.text = "Azt hiszem, a "+sti(pchar.questTemp.LongHappy.MarryMoney)+" pezó elég lesz, rendben. "+sti(pchar.questTemp.LongHappy.MarryRum)+" hordó rum, nincs rosszabb, mint kimaradni az italokból. Amint összeszedtél mindent, amire szükségünk van, gyere a kocsmába, a többit kitalálom.";
			link.l1 = "Rendben, drágám, majd én megcsinálom.";
			link.l1.go = "LongHappy_9d";
		break;
		
		case "LongHappy_9d":
			DialogExit();
			npchar.dialog.currentnode = "Mary_officer";
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "LongHappy_GirlNorm", 5.0);
			AddQuestRecord("LongHappy", "10_1");
			AddQuestUserData("LongHappy", "sName", "Mary");
			LongHappy_MarryGoToBenua();
		break;
		
		case "LongHappy_10":
			pchar.questTemp.LongHappy.SmallMarry = "true";
			dialog.text = "Értettem, csináljuk. De el kell majd látogatnunk Sharptownba, és mindent elôkészíteni. Szerintem ötven hordó rum és pár tucat hordó bor elég lesz, rendben. De a biztonság kedvéért szükségem lesz háromszázezer pezóra.";
			link.l1 = "Ez sok, de az alkalom megéri. Össze fogom kaparni, ne aggódjon. Most pedig beugrom az apát úrhoz, és elmegyek Sharptownba.";
			link.l1.go = "LongHappy_12";
		break;
		
		case "LongHappy_11":
			pchar.questTemp.LongHappy.BigMarry = "true";
			dialog.text = "Remek, akkor összehívunk mindenkit, rendben! De el kell majd látogatnunk Sharptownba, és mindent elôkészíteni - szükségünk lesz egy gályára tele piával!  Azt hiszem, száz hordó rum és ötven hordó bor elég lesz. De a biztonság kedvéért még ötszázezer pezót is adok hozzá. Ha az ünnepségnek gyorsan vége lesz, miféle ünnep az, igazam van?";
			link.l1 = "Igen, a barátainknak nem szabad szomjan halniuk - mindent meg fogok szerezni, ne aggódj! Most pedig beugrom az apát úrhoz, és elmegyek Sharptownba.";
			link.l1.go = "LongHappy_12";
		break;
		
		case "LongHappy_12":
			DialogExit();
			npchar.dialog.currentnode = "Mary_officer";
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "LongHappy_GirlNorm", 5.0);
			AddQuestRecord("LongHappy", "10");
			AddQuestUserData("LongHappy", "sName", "Mary");
			LongHappy_MarryGoToBenua();
		break;
		
		case "LongHappy_13":
			dialog.text = "Minden készen áll, Charles, igaz? Elintézem, hogy az italt kirakodják, elmegyek a helyi kocsmába, találkozom a báróval, és átadom a meghívókat. Várj itt, rendben?";
			link.l1 = "Te vagy a kormánynál, kedvesem! Akkor én majd csak szórakozom valahol. Tényleg nem gondoltam volna, hogy a maine-i dzsungelbe induló expedíciókat könnyebb elôkészíteni, mint egy esküvôt.";
			link.l1.go = "LongHappy_14";
		break;
		
		case "LongHappy_14":
			DialogExit();
			SetLaunchFrameFormParam("Több óra is eltelt...", "", 0.1, 3.0);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 4, 0);
			LongHappy_IslaTesoroRemoveGoods();
			npchar.dialog.currentnode = "LongHappy_15";
			LAi_SetActorType(npchar);
			LAi_ActorDialogDelay(npchar, pchar, "", 4.0);
		break;
		
		case "LongHappy_15":
			dialog.text = "Végeztünk, Charles, rendben! Mindent elintéztem, higgy nekem - csodálatos lesz! Egy dolog kínos: a helyi kocsma leégett valami lakoma közben egy hete. De már majdnem újjáépült, nagyobb és jobb, mint a régi, rendben! Mindannyian elférünk benne.";
			link.l1 = "Nagyon remélem, hogy ezt nem égetjük el. Nagyon tetszett a 'Old Woodpecker'! Egyébként még sok dolgunk van. Itt az ideje, hogy kihajózzunk. És igen, Mary - te vagy a legjobb, ugye tudod?";
			link.l1.go = "LongHappy_16";
		break;
		
		case "LongHappy_16":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "LongHappy_GirlNorm", 5.0);
			AddQuestRecord("LongHappy", "12");
			pchar.questTemp.LongHappy = "marry_wait";
			pchar.questTemp.LongHappy.DrinkReady = "true";
		break;
		
		case "LongHappy_17":
			dialog.text = "Szóval, indulunk, mi? A vendégek megérkeztek, a templom készen áll. Tudom, hogy közelebb vagyunk egymáshoz, mint sok házastárs, és ez csak néhány fontos szó egy gyönyörû teremben, de a fenébe is - abban az ôsi, ôslakos városban kevésbé aggódtam, rendben!";
			link.l1 = "Ez teljesen normális, szerelmem, teljesen normális. Én is ideges vagyok. Azt hiszem, Benoit atya már vár, odamegyek hozzá, és megtudom, mikor kezdôdik a szertartás.";
			link.l1.go = "LongHappy_18";
		break;
		
		case "LongHappy_18":
			dialog.text = "Rendben, sétálok egy kicsit a városban, készülôdni akarok, rendben! Charles, ugye megérted, hogy nincs visszaút?";
			link.l1 = "Mary, kedvesem, számomra nincs visszaút, mióta találkoztunk. Teljes szívembôl vártam ezt a napot. Ne aggódj, minden rendben lesz.";
			link.l1.go = "LongHappy_19";
		break;
		
		case "LongHappy_19":
			DialogExit();
			pchar.GenQuest.CannotWait = true;//запрет ожидания
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "OpenTheDoors", 5.0);
			AddQuestRecord("LongHappy", "14");
			AddQuestUserData("LongHappy", "sName", "Mary");
		break;
		
		case "LongHappy_20":
			dialog.text = "Igen.";
			link.l1 = "";
			link.l1.go = "LongHappy_21";
		break;
		
		case "LongHappy_21":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_27";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_22":
			dialog.text = "Igen.";
			link.l1 = "";
			link.l1.go = "LongHappy_23";
		break;
		
		case "LongHappy_23":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_29";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_24":
			dialog.text = "Igen.";
			link.l1 = "";
			link.l1.go = "LongHappy_25";
		break;
		
		case "LongHappy_25":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_31";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_26":
			dialog.text = "";
			link.l1 = "Én, Charles Henry de Maure, chevalier de Monper, feleségül veszlek téged, Mary Casper, hogy a mai naptól fogva a feleségem légy, jóban és rosszban, gazdagságban és szegénységben, betegségben és egészségben, amíg a halál el nem választ minket egymástól. Isten szent törvénye szerint, Isten jelenlétében teszem ezt a fogadalmat.";
			link.l1.go = "LongHappy_27";
		break;
		
		case "LongHappy_27":
			dialog.text = "Én, Mary Casper, téged, Charles de Maure-t, férjemül veszlek, hogy a mai naptól fogva jóban-rosszban, gazdagságban és szegénységben, betegségben és egészségben, amíg a halál el nem választ minket egymástól. Isten szent törvénye szerint, Isten jelenlétében teszem ezt a fogadalmat.";
			link.l1 = "";
			link.l1.go = "LongHappy_28";
		break;
		
		case "LongHappy_28":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_33";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_29":
			dialog.text = "Ámen.";
			link.l1 = "";
			link.l1.go = "LongHappy_30";
		break;
		
		case "LongHappy_30":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_35";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_31":
			dialog.text = "Ez hihetetlen, rendben! Én... Sírok, sajnálom Charles, én... az orrom vörös lett, ugye?";
			link.l1 = "Mary de Maure, feleségem, gyönyörû vagy ezen a napon is, mint minden más napon!";
			link.l1.go = "LongHappy_32";
		break;
		
		case "LongHappy_32":
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP")) dialog.text = "Köszönöm, Charles, köszönöm... Minden olyan ünnepélyes és csodálatos! Ez életem legszebb napja, rendben!!! Nézd, milyen boldog mindenki! De, itt az ideje, hogy körbejárd a vendégeket és fogadjátok a gratulációkat! Ha végeztél - gyere vissza - nézzük meg a srácokat a kocsmában.";
			else dialog.text = "Köszönöm, Charles, köszönöm... Minden olyan ünnepélyes és csodálatos! Ez életem legszebb napja, rendben!!! Nézd, milyen boldog mindenki! De, itt az ideje, hogy körbejárd a vendégeket, és elfogadd a gratulációkat! Ha végeztél, gyere vissza, várnak minket Sharptownban.";
			link.l1 = "Azonnal megyek, drágám. Egy csók és megyek!";
			link.l1.go = "LongHappy_33";
		break;
		
		case "LongHappy_33":
			DialogExit();
			LongHappy_MarryKiss();
		break;
		
		case "LongHappy_34":
			dialog.text = "Charles, szerelmem, beszéltél már a vendégekkel?";
			link.l1 = "Még nem, légy türelmes, édesem, hamarosan visszajövök.";
			link.l1.go = "LongHappy_34_1";
			link.l2 = "Igen, még soha nem hallottam ennyi gratulációt egyszerre. És tudod mit - a legtöbbjük ôszintén beszélt!";
			link.l2.go = "LongHappy_35";
		break;
		
		case "LongHappy_34_1":
			DialogExit();
			npchar.dialog.currentnode = "LongHappy_34";
		break;
		
		case "LongHappy_35":
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP")) 
			{
				dialog.text = "Igen, igen! Ôk is sok kellemes dolgot mondtak nekem! Persze nem mindenki, néhányan nyilván meglepôdtek a ruhámon, rendben! De én annyira boldog vagyok, hogy az emberek mondandójának a fele csak úgy elsiklik mellettem. És általában mindenki olyan aranyos. Charles, a srácok a kocsmában már várnak ránk - fog oda menni hozzájuk. Örülni fognak, hogy gratulálhatnak a kapitányuknak, rendben!";
				link.l1 = "Most azonnal indulunk. De szeretném ezt a napot egy romantikusabb helyen befejezni, mint a kikötôi kocsma szobája. Remélem, feleségem, nem bánja, ha ezt az éjszakát a kabinunkban tölti? Ráadásul most nincs ôrség a hajón...";
			}
			else
			{
				dialog.text = "Igen, igen! Ôk is sok kellemes dolgot mondtak nekem! Persze nem mindenki, néhányan nyilván meglepôdtek a ruhámon, rendben! De én annyira boldog vagyok, hogy az emberek mondanivalójának a fele csak úgy elmegy mellettem. És általában mindenki olyan aranyos. Charles! De Sharptownba várnak minket, mikor indulunk?";
				link.l1 = "Most rögtön. Nem engedhetjük, hogy a vendégeink megigyák az összes készletet! Remélem, feleségem, nem bánja, ha ezt az éjszakát a kabinunkban tölti?";
			}
			link.l1.go = "LongHappy_36";
		break;
		
		case "LongHappy_36":
			dialog.text = "Akár egy kunyhóban egy lakatlan szigeten, de persze csak veled együtt!";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP")) link.l1 = "Tudom, tudom. Én is szeretlek. Menjünk, mielôtt a fiúk megisszák az összes rumunkat és felgyújtják a kocsmát.";
			else link.l1 = "Igen. Én is szeretlek. Akkor - indulás!";
			link.l1.go = "LongHappy_37";
		break;
		
		case "LongHappy_37":
			DialogExit();
			npchar.dialog.currentnode = "LongHappy_38";
			LongHappy_MarryComplete();
		break;
		
		case "LongHappy_38":
			dialog.text = "Ó, drágám, annyira boldog vagyok! A mai egy csodálatos nap...";
			link.l1 = "";
			link.l1.go = "LongHappy_38_1";
		break;
		
		case "LongHappy_38_1":
			DialogExit();
			npchar.dialog.currentnode = "LongHappy_38";
		break;
		
		case "LongHappy_39":
			dialog.text = "Tépd le a mosdatlan fejét, Charles!";
			link.l1 = "";
			link.l1.go = "LongHappy_40";
		break;
		
		case "LongHappy_40":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Angerran") && CharacterIsAlive("Angerran")) // fix 02-04-20
			{
				sld = characterFromId("Angerran");
				sld.dialog.currentnode = "Shivo_6";
			}
			else 
			{
				sld = characterFromId("LH_Dussak");
				sld.dialog.currentnode = "Dussak_5";
			}
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "LongHappy_41":
			dialog.text = "Jól vagyok, rendben! Hogy van Nathan, életben van?";
			link.l1 = "Annyi vér... Dannie, lélegzik? Látom, hogy lélegzik!";
			link.l1.go = "LongHappy_42";
		break;
		
		case "LongHappy_42":
			DialogExit();
			sld = characterFromId("Danielle");
			sld.dialog.currentnode = "Danielle_9";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "LongHappy_43":
			dialog.text = "Gyorsabban, drágám, ne vesztegesd az idôt!";
			link.l1 = "";
			link.l1.go = "LongHappy_43_1";
		break;
		
		case "LongHappy_43_1":
			DialogExit();
			npchar.dialog.currentnode = "LongHappy_43";
		break;
		
		case "LongHappy_44":
			dialog.text = "Gyôztünk, rendben! Bocsáss meg, elkéstem. Az emeleten ragadtunk, egy tucatnyi ilyen szemétláda volt, szóval egy kicsit elfoglalt voltam!";
			link.l1 = "Semmi baj, elintéztem. Örülök, hogy végre befejezhettem a történetet Jacques-kal... végre. Megkapta, amit megérdemelt.";
			link.l1.go = "LongHappy_45";
		break;
		
		case "LongHappy_45":
			dialog.text = "Akkor fejezd be itt, és menj vissza Sharptownba! Meg kéne néznünk Nathan-t, rendben?! Az életét kockáztatta értünk!";
			link.l1 = "Igazad van, szerelmem. Menj, én mögötted vagyok.";
			if (CheckAttribute(pchar, "questTemp.LongHappy.Terrax.Prisoner")) link.l1.go = "LongHappy_46";
			else link.l1.go = "LongHappy_48";
		break;
		
		case "LongHappy_46":
			dialog.text = "Egyébként, drágám, megtaláltuk Marcust, rendben! A raktérben volt, megkötözve és eszméletlenül.";
			link.l1 = "Életben van?";
			link.l1.go = "LongHappy_47";
		break;
		
		case "LongHappy_47":
			dialog.text = "Megsérült, de rendbe fog jönni. Nem tudod megtörni a bárónkat, rendben! Most ébredt fel, és már alig várja a csatát.";
			link.l1 = "Ez a mi jó öreg Marcusunk! Nos, fejezzétek be itt és menjetek a partra.";
			link.l1.go = "LongHappy_48";
		break;
		
		case "LongHappy_48":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "LongHappy_BarbExit", -1);
		break;
		
		case "LongHappy_49":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_died") && CheckAttribute(pchar, "questTemp.LongHappy.Jino_died"))
			{
				dialog.text = "Annyira sajnálom, Charles, rendben, én... Elmentem sétálni. Láttam, hogy visszajöttél, hallottam, hogy mindenki él és gyôzött, de én... De mi bajom van velem, rendben!";
				link.l1 = "Minden rendben lesz, szerelmem, minden rendben lesz. Én is szomorú vagyok. De gyôztünk, és Jacques Barbazon megfizetett mindenért, amit tett.";
				link.l1.go = "LongHappy_50";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.LongHappy.Jino_died"))
				{
					dialog.text = "Nagyon rosszul érzem magam Gino miatt, Charles, rendben! Amikor megtudtam, nem hittem el! Hogy vagy?";
					link.l1 = "Én sem tudom elhinni... olyan hülyén alakult, nem így képzeltem el ezt a napot.";
				}
				else
				{
					dialog.text = "Megint nyertünk, rendben! A férjem a Parti Testvérek lázadó báróinak vihara! A barátok élnek és az ellenségek halottak - dicsôséges ajándék, rendben!";
					link.l1 = "Igen, micsoda ünnep, de megcsináltuk, szerelmem! Megcsináltuk.";
				}
				link.l1.go = "LongHappy_50";
			}
		break;
		
		case "LongHappy_50":
			dialog.text = "Alig tudsz megállni a lábadon, rendben! Gyere, Dannie talált nekünk egy házat itt a külvárosban, nem akarok most visszamenni a hajóra. Leülünk és iszunk az elesett barátainkra. Ez az egész túl sok egy józan fejnek, rendben.";
			link.l1 = "Igen, Mary, menjünk.";
			link.l1.go = "LongHappy_51";
		break;
		
		case "LongHappy_51":
			DialogExit();
			LongHappy_LogBook();
			DoQuestCheckDelay("LongHappy_MarryFinalizing", 0.5);
		break;
		
		case "LongHappy_52":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Jino_died"))
			{
				dialog.text = "Annyira sajnálom Ginót, Charles, rendben! Amikor megtudtam, nem tudtam elhinni! Hogy vagy?";
				link.l1 = "Én sem tudom elhinni... olyan hülyén alakult, nem így képzeltem el ezt a napot.";
			}
			else
			{
				dialog.text = "Elnézést a késésért, kedvesem, rendben! Elmentem sétálni, aztán láttam, hogy közeledsz, és rohantam, ahogy csak tudtam! Dannielle kirakott, amikor Gino azt mondta 'a veszély elmúlt', rendben! Annyira örülök, hogy már minden rendben van!";
				link.l1 = "Én is, drágám. És nyertünk. Barbazon halott, a bárók összegyûjtik a legénységük maradékát. A harcnak vége.";
			}
			link.l1.go = "LongHappy_53";
		break;
		
		case "LongHappy_53":
			dialog.text = "Charles, látom, hogy alig állsz a lábadon, de senki sem találja Tichingitu-t.";
			link.l1 = "Jan adott valami tippet... Nekem úgy tûnik, hogy a mi kemény maszkogónk elment a mámorba. Sétáljunk el a Sabo-Matila-öbölbe, néhányan látták, hogy abba az irányba távozik.";
			link.l1.go = "LongHappy_54";
		break;
		
		case "LongHappy_54":
			DialogExit();
			LongHappy_LogBook();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			pchar.quest.longhappy_shoregirl.win_condition.l1 = "location";
			pchar.quest.longhappy_shoregirl.win_condition.l1.location = "Shore_ship1";
			pchar.quest.longhappy_shoregirl.function = "LongHappy_SetShoreGirl";
		break;
		
		case "LongHappy_55":
			dialog.text = "Hát ez a mi szigorú bennszülöttünk, rendben! Gyerünk, Dannie talált nekünk egy házat itt a külvárosban - most már álmában járkál, Charles, rendben!";
			link.l1 = "Ott van ... rabolj el, gyönyörû squaw-m. És holnap minden csak egy rossz álomnak fog tûnni.";
			link.l1.go = "LongHappy_56";
		break;
		
		case "LongHappy_56":
			DialogExit();
			DoQuestCheckDelay("LongHappy_MarryFinalizing", 0.5);
		break;
		
		case "LongHappy_57":
			dialog.text = "Ne érts félre, férjem, a templomban minden csak fényûzés volt, de itt egyértelmûen lelkesebb a hangulat, rendben! Nos, ennyi, Charles, most, hogy minden gondon túl vagyunk, megnyugodhatunk.";
			link.l1 = "Nos, ez nem egészen 'all', a feleségem - az életünk együtt megy tovább! Általában elmondható, hogy ma kezdôdött csak el. Szóval, menjünk, igyunk egyet a srácokkal, aztán - hát, emlékszel: a kabin, a bor, és mi...";
			link.l1.go = "LongHappy_58";
		break;
		
		case "LongHappy_58":
			DialogExit(); // телепорт в каюту
			DoQuestReloadToLocation("My_Cabin", "rld", "loc1", "LongHappy_InSPcabin");
		break;
		
		case "LongHappy_59":
			dialog.text = "A férjem... Ez olyan édesnek hangzik, rendben! Most már az enyém vagy, örökre!";
			link.l1 = "Már régóta a tiéd vagyok, és örökké az leszek, szerelmem...";
			link.l1.go = "LongHappy_60";
		break;
		
		case "LongHappy_60":
			DialogExit();
			DoQuestFunctionDelay("LoveSex_Classic", 1.0);
			npchar.dialog.currentnode = "LongHappy_61";
			LAi_SetStayType(npchar);
		break;
		
		case "LongHappy_61":
			dialog.text = "Annyira boldog vagyok, Charles! És most már megint tovább kell mennünk, ugye?";
			link.l1 = "Persze, édesem! Egymás mellett, együtt és örökké!";
			link.l1.go = "LongHappy_62";
		break;
		
		case "LongHappy_62":
			DialogExit();
			LAi_SetOfficerType(npchar);
			npchar.dialog.currentnode = "Mary_officer";
			DoQuestReloadToLocation("FortFrance_town", "reload", "reload1", "LongHappy_InSPComplete");
		break;
		
		// Jason Исла Мона
		case "IslaMona":
			dialog.text = "Attól tartok, ez a járvány megviseli a lányaidat, Rodrigo. Foglald le ôket kötéssel vagy valamivel!";
			link.l1 = "Ez a beszélgetés nyilvánvalóan nem vezet sehova. Megegyeztünk, hogy holnap elmegyünk a templomba. Imádkozni... természetesen.";
			link.l1.go = "IslaMona_1";
		break;
		
		case "IslaMona_1":
			DialogExit();
			LAi_SetOfficerType(npchar);
			npchar.dialog.currentnode = "Mary_officer";
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_church_26";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_2":
			dialog.text = "Büszke vagyok rád, szerelmem!";
			link.l1 = "";
			link.l1.go = "IslaMona_3";
		break;
		
		case "IslaMona_3":
			DialogExit();
			npchar.dialog.currentnode = "Mary_officer";
			sld = characterFromId("Himenes_companion_1");
			sld.dialog.currentnode = "island_man_2";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_4":
			dialog.text = "Nos, Charles...";
			link.l1 = "Mi jár a fejedben, Mary?";
			link.l1.go = "IslaMona_5";
		break;
		
		case "IslaMona_5":
			dialog.text = "(nevetés) A tény, hogy én és Alan, ugyanazt akartuk csinálni a szigeten, amit ti itt csináltatok.";
			link.l1 = "A te... Alan?";
			link.l1.go = "IslaMona_6";
		break;
		
		case "IslaMona_6":
			dialog.text = "Igen, egy pokoli álmodozó volt, ti ketten nagyszerû barátok lehettetek volna, ha még élne!";
			link.l1 = "Nos, az ízlésünk egy dologban biztosan keresztezte egymást!";
			link.l1.go = "IslaMona_7";
		break;
		
		case "IslaMona_7":
			dialog.text = "Mi? Ha-ha-ha-ha! Hagyd abba, Charles!\nAkárhogy is, ez csodálatos, annyi örömet szereztünk ezeknek az embereknek!";
			link.l1 = "Mi adtunk nekik egy esélyt a boldogságra, de a többit ôk maguk csinálták. Szóval, mit gondolsz?";
			link.l1.go = "IslaMona_8";
		break;
		
		case "IslaMona_8":
			dialog.text = "Keress meg késôbb, és megtudod...";
			link.l1 = "A pokolba is, igen, meg fogom!";
			link.l1.go = "IslaMona_9";
		break;
		
		case "IslaMona_9":
			DialogExit();
			LAi_SetOfficerType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			DoQuestFunctionDelay("IslaMona_ChurchReloadToRoom", 0.5);
			ChangeCharacterAddressGroup(npchar, "IslaMona_TwoFloorRoom", "goto", "goto4");
			DoQuestFunctionDelay("LoveSex_Classic", 2.0);
			NextDiag.CurrentNode = "sex_after";
			npchar.greeting = "mary_hire";
			pchar.questTemp.IslaMona.Doorlock = "true";
		break;
		
		case "tonzag_jailed":
			dialog.text = "Szeretem a sötétséget és a szûk tereket. Nyugodtnak érzem magam tôle. Végre összeszedhetem a gondolataimat\nAmintha minden gond és baj... eltûnne, igen! Nagyon hiányzik ez az érzés...";
			link.l1 = "Orvoshoz kell menned.";
			link.l1.go = "tonzag_jailed_1";
			link.l2 = "Rendben. Olyan, mintha újra a 'Ceres Smithy-nél lennél.'.";
			link.l2.go = "tonzag_jailed_2";
			locCameraFromToPos(-15.50, 2.28, -1.23, true, -27.00, -10.60, -22.70);
		break;

		case "tonzag_jailed_1":
			dialog.text = "...Kár, hogy nem vagyok egyedül. Csendben, sötétben és magányban, igen. Az tökéletes lenne.";
			link.l1 = "Csak így tovább, Mary Casper.";
			link.l1.go = "exit";
		break;

		case "tonzag_jailed_2":
			dialog.text = "Egyszer egy rák mászott be az ágyamba, feldaraboltam és megettem. Megettem és megettem.";
			link.l1 = "Csak így tovább, Mary Casper.";
			link.l1.go = "exit";
		break;
		
		case "tonzag_aftershot":
			dialog.text = "Maszkos seggfej! Aú! Segíts, drágám - be kell törnünk a rácsot!";
			link.l1 = "Csendet! Próbálom kitalálni, mit tegyek!";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "Mary_officer";
			AddDialogExitQuestFunction("Tonzag_TichingituAfterShot");
		break;
		
		case "tonzag_after_boarding":
			dialog.text = "Drágám, ezek a maszkos ördögök mindenhol ott vannak! Hatalmas rést ütöttek a hajótesten, és úgy másznak át rajta, mint azok a rákok! Mindet le kell vágnunk, igen!";
			link.l1 = "Mary, maradj itt, keresd meg a rangidôs tisztet, és vedd át a parancsnokságot! Vidd ki a hajót a csatából, nem bírunk ki még egy partraszállást!";
			link.l1.go = "tonzag_after_boarding_1";
			DelLandQuestMark(npchar);
		break;
		
		case "tonzag_after_boarding_1":
			dialog.text = "És te hová mész? Nem hagylak elmenni!";
			link.l1 = "Segítenem kell Hercule-nak és a legénységnek! Bízz bennem, Mary!";
			link.l1.go = "tonzag_after_boarding_2";
		break;

		case "tonzag_after_boarding_2":
			dialog.text = "Igenis, drágám!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_GoToGunDeck");
		break;
		
		case "tonzag_after_victory":
			dialog.text = "Gyôzelem, igenis! Gyere hozzám, drágám! Szükségem van rád egy-két órára!";
			link.l1 = "Uh...";
			link.l1.go = "tonzag_after_victory_1";
			link.l2 = "Gyerünk!";
			link.l2.go = "tonzag_after_victory_1";
		break;

		case "tonzag_after_victory_1":
			dialog.text = "Hé, Hercule! Örülök, hogy látlak, ôsz szakállú!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_MaryBoardingDialog");
		break;

		case "tonzag_after_victory_2":
			dialog.text = "";
			link.l1 = "Mary, Mary, várj! Szükségem van a jelentésedre!";
			link.l1.go = "tonzag_after_victory_3";
		break;

		case "tonzag_after_victory_3":
			dialog.text = "Huh? Nos, nyertünk, igen! Az az átkozott hajó elmenekült. Kettéhasítottam az egyik rohadék koponyáját!\nFúú, átkozott gombok!";
			link.l1 = "Ó, Mary...";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_ShowFrame");
		break;
		
		case "tonzag_dead":
			dialog.text = "Istenem, ne nézz rám, drágám! Mindjárt... fúú!";
			link.l1 = "Tarts ki, kislány. Itt vagyok!";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "Mary_officer";
		break;

		//--> ----------------------------------- офицерский блок ------------------------------------------
		case "Mary_officer":
			// если шлялся по борделям - устроит небольшой скандал 
			if (sti(pchar.GenQuest.BrothelCount) >= 3 && LAi_grp_playeralarm == 0)
			{
				dialog.Text = ""+pchar.name+"! Beszélnem kell veled, rendben! Komolyan!";
				Link.l1 = "Mi történt, Mary? Valami baj van?";
				Link.l1.go = "brothel";
				break;
			}
			ref rLoc = &Locations[FindLocation(pchar.location)];
			dialog.text = LinkRandPhrase("Hallgatom, kedves kapitányom!","Igen, "+pchar.name+", csupa fül vagyok!","Van valami feladatod számomra, "+pchar.name+"?");
			if (CheckAttribute(pchar, "questTemp.Dolly_Tieyasal") && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				Link.l4 = "Mary, meglátogatom a régi indiai várost, Tayasalt. Nem fogok hazudni neked: ez az utazás nagyon veszélyes, sôt - teleportálást is tartalmaz a bálványon keresztül, amirôl meséltem neked. Követsz... velem?";
				Link.l4.go = "tieyasal";
			}
			////////////////////////казначей///////////////////////////////////////////////////////////
			// boal отчёт о корабле
			if(CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
			{
			    Link.l11 = "Mary, adj egy teljes hajójelentést.";
			    Link.l11.go = "QMASTER_1";
				
			    // Warship. Автозакупка товара
				Link.l12 = "Azt akarom, hogy minden alkalommal, amikor kikötünk, vásároljon bizonyos árukat.";
				Link.l12.go = "QMASTER_2";
			}

			if (CheckAttribute(npchar, "quest.fugas"))
			{
				Link.l3 = "Mary, szükségem van a tanácsodra.";
				Link.l3.go = "fugas";
			}
			Link.l1 = "Mary, van egy parancsom számodra...";
            Link.l1.go = "stay_follow";
			if (pchar.location == Get_My_Cabin() && !CheckAttribute(npchar, "quest.daily_sex"))
			{
				Link.l2 = RandPhraseSimple("Kedvesem, most azonnal akarlak. Rendben van ez neked?","Mary, mi lenne, ha... egy darabig együtt maradnánk? Csak mi ketten.");
				Link.l2.go = "cabin_sex";
			}
			if (rLoc.type == "tavern" && !CheckAttribute(npchar, "quest.daily_sex") && sti(pchar.money) >= 10)
			{
				Link.l2 = RandPhraseSimple("Mary, béreljünk ki egy szobát és maradjunk együtt?","Szerelmem, szeretnék veled maradni kettesben... mi lenne, ha kibérelnénk egy szobát, és néhány órára mindent elfelejtenénk?");
				Link.l2.go = "room_sex";
			}
			link.l9 = "Eddig semmi, Mary.";
			link.l9.go = "exit";
			NextDiag.TempNode = "Mary_officer";
		break;
		
		/////////////////////////// ответы для казначея ///////////////////////////////////
		case "QMASTER_1":
			dialog.Text = "Charles, ô egy szépség, tényleg! Megjavítottuk azt az ici-pici lyukat a vízvonal alatt, és megszárítottuk a vitorlákat. Mit vártál? Ne nézz így rám, soha nem tanultam pénztárosnak.";
			Link.l1 = "Sajnálom, Mary, tényleg nem gondoltam végig.";
			Link.l1.go = "exit";
		break;	

		case "QMASTER_2":
			dialog.text = "Charles, de én jól vagyok! Már megvan a ruhatáram és a pengém. De köszönöm, hogy megkérdezted, nagyon kedves tôled, rendben!";
			link.l1 = "De én nem is... Mindegy, felejtsd el, drágám, minden rendben.";
			link.l1.go = "exit";
		break;

		case "stay_follow":
            dialog.Text = "Rendelések?";
            Link.l1 = "Álljatok ide!";
            Link.l1.go = "Boal_Stay";
            Link.l2 = "Kövessetek és tartsátok a lépést!";
            Link.l2.go = "Boal_Follow";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			if(sGun != "")
			{
				rItm = ItemsFromID(sGun);
				if(CheckAttribute(NPChar, "chr_ai.gun.bulletNum") && sti(NPChar.chr_ai.gun.bulletNum) > 1)
				{
					Link.l3 = "Mary, cserélj lôszert lôfegyverre.";
					Link.l3.go = "SetGunBullets";
				}	
			}		
		break;
		
		case "SetGunBullets":
			Dialog.Text = "A lôszer típusának kiválasztása:";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(NPChar.chr_ai.gun.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetConvertStr(rItem.name, "ItemsDescribe.txt");
				Link.(attrL).go = "SetGunBullets1_" + i;
			}
		break;	

		case "SetGunBullets2":
			i = sti(NPChar.SetGunBullets) + 1; 
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(NPChar, GUN_ITEM_TYPE, sBullet);
			LAi_GunSetUnload(NPChar, GUN_ITEM_TYPE);
			NextDiag.CurrentNode = NextDiag.TempNode;
			rItem = ItemsFromID(sBullet);
			notification(GetFullName(NPChar)+" "+XI_ConvertString("AmmoSelectNotif")+GetConvertStr(rItem.name, "ItemsDescribe.txt")+"", "AmmoSelect");
			DeleteAttribute(NPChar,"SetGunBullets");
			DialogExit();
		break;		
		
        case "Boal_Stay":
            Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
            AddDialogExitQuestFunction("LandEnc_OfficerStay");
            dialog.Text = "Azonnal, kapitányom!";
            Link.l1 = "...";
            Link.l1.go = "Exit";
            Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
        break;
        
        case "Boal_Follow":
            SetCharacterTask_FollowCharacter(Npchar, PChar);
            dialog.Text = "Azonnal, kapitányom!";
            Link.l1 = "...";
            Link.l1.go = "Exit";
        break;
		//<-- ----------------------------------- офицерский блок ----------------------------------------
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
