// колдун ривадос - Чимисет
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
			dialog.text = "Kérsz valamit?";
			link.l1 = "Nem, nem érdekes.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		//-------------------------------------в тюрьме на Тартарусе-----------------------------
		// вариант R
		case "KillChad":
			dialog.text = "Várj! Állj! Könyörgöm, hallgass rám, mielôtt hibát követsz el.";
			link.l1 = "Hallgatlak... Remélem, hogy van egy ésszerû érved, hogy megállíts...";
			link.l1.go = "KillChad_1";
			LAi_RemoveCheckMinHP(npchar); //убираем проверяльщик, если ещё есть
		break;
		
		case "KillChad_1":
			dialog.text = "Hogy megöltél, ugye? Hallottam, hogy Chaddel beszélgetsz odafent, és nem hibáztatlak - valószínûleg bárki ugyanezt tenné. De tévedsz, ha azt hiszed, hogy Chad elenged, miután megöltél.";
			link.l1 = "Hm... Érdekes, és miért nem tenné? Csak azt tudom, hogy meg kell majd izzadnom, hogy kijussak innen, ha nem öllek meg egyszerûen.";
			link.l1.go = "KillChad_2";
		break;
		
		case "KillChad_2":
			dialog.text = "Egyáltalán nem lesz jövôd, ha megölsz engem. Figyelj, Narwhals és Chad hajlandóak megszabadulni tôlem, de túlságosan félnek tôlem ahhoz, hogy ezt ôk maguk tegyék meg - a gyilkosom örökre el lesz átkozva. Ezért azt akarják, hogy te végezd el a piszkos munkát\nChad tisztában van vele, hogy te nem Rivados vagy, ô csak átver téged. Ha egyszer megölsz engem - ugyanezt teszik veled is, és a holttestedet használják fel Shark átverésére.";
			link.l1 = "Sharkot? Steve Dodson? Ô tényleg itt van? És magyarázzátok meg végre - kik azok a Rivadosok?";
			link.l1.go = "KillChad_3";
		break;
		
		case "KillChad_3":
			dialog.text = "Heh, úgy tûnik, hogy nem itt élsz... De ez nem a megfelelô idô a mesélésre. Meg kell mentenünk magunkat. Van egy tervem.";
			link.l1 = "Tudod mit, varázsló, nemrég tettem egy utat valami misztikus portálon keresztül, és alig éltem túl, úgyhogy az átkaid nem ijesztenek meg. Elegem van - itt az ideje, hogy végezzek veled.";
			link.l1.go = "KillChad_fightfail";
			link.l2 = "Rendben, bízom benned. Mi a terv?";
			link.l2.go = "KillChad_4";
		break;
		
		case "KillChad_fightfail":
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "afraid", "", -1);
			LAi_SetImmortal(npchar, false);
			pchar.quest.LSC_fightfail.win_condition.l1 = "NPC_Death";
			pchar.quest.LSC_fightfail.win_condition.l1.character = "Chimiset";
			pchar.quest.LSC_fightfail.function = "LSC_Fightfail_Final";
		break;
		
		case "KillChad_4":
			dialog.text = "Ott van egy láda. Tisztességes fegyvereket és bájitalokat tartalmaz. Zárva van, de a zár régi és sérült, ezért keress egy feszítôvasat, amivel feltörheted\nVégy mindent a ládából, fegyverezd fel magad, és menj a lépcsôhöz. Ez egy jó védekezô pozíció, kénytelenek lesznek egyenként harcolni veled, csak vigyázz a muskétásokkal\nremélem, hogy jól bánsz a pengével, én már túl öreg vagyok ahhoz, hogy segítsek harcolni. Ha sikerül mindet megölnöd, és közben életben maradsz - garantálom neked Rivados, a családom védelmét...";
			link.l1 = "Jó... Imádkozzatok az isteneitekhez értem - a harc kemény lesz. Azok a fiúk odafent nagyon komolyan néznek ki.";
			link.l1.go = "KillChad_5";
		break;
		
		case "KillChad_5":
			DialogExit();
			pchar.quest.LSC_fightfail.over = "yes"; //снять прерывание
			LAi_SetImmortal(npchar, true);
			ref location = &Locations[FindLocation(pchar.location)];
			location.private1.key = "crowbar";
			location.private1.key.delItem = true;
			NextDiag.CurrentNode = "KillChad_6";
		break;
		
		case "KillChad_6":
			dialog.text = "Ne vesztegessétek az idôt! Nyisd ki a zárat gyorsan...";
			link.l1 = "Igen, igen, úton vagyok.";
			link.l1.go = "exit";
			NextDiag.TempNode = "KillChad_6";
		break;
		
		case "Chad_die":
			dialog.text = "Szép munka! Te tényleg a vívás mestere vagy. Tartozom neked, idegen. Mondd, mi a neved?";
			link.l1 = ""+pchar.name+". "+GetFullName(pchar)+". És mi a tiéd?";
			link.l1.go = "Chad_die_1";
		break;
		
		case "Chad_die_1":
			dialog.text = "A nevem Chimiset, Rivados sámánja vagyok és a fônökünk - Fekete Eddie - tanácsadója. Örülni fog, ha megtudja, hogy kiszabadítottál és megmentetted az életemet. Chimiset, Fekete Eddie és minden Rivados barátja vagy. Mostantól kezdve mindig szívesen látott vendég leszel a mi Védelmezônkön...";
			link.l1 = "Várjatok... Chimiset, ha még mindig nem értetted volna meg, csak néhány órája érkeztem ide. Elmagyaráznád nekem, hol vagyok, kik a Rivadosok, és hol találom Shark Dodson-t?";
			link.l1.go = "Chad_die_2";
		break;
		
		case "Chad_die_2":
			dialog.text = "Ezt a helyet az Elhagyott hajók városának nevezik. Bár ez inkább gúnyolódásnak hangzik. Ez nem egy nagy város. Ez a hely egy sziget, amelyet több száz halott hajóból alakítottak ki. A közepe alkalmas lakóhelynek. Olyan emberek lakják, akik túlélték a megmagyarázhatatlan viharok okozta hajótöréseket, amelyek ide vezették ôket\nRivados egy klán, olyan emberek csoportja, akik már régóta együtt élnek. Három másik csoport is él itt: a Narwhal klán, ôk a mi ellenségeink, a Shark Dodson kalózai és az egyszerû emberek. Shark tulajdonképpen a sziget feje, admirálisnak nevezi magát\nNemrég érkezett, és erôszakos módon ragadta magához a hatalmat. Elfoglalta a 'San Augustine' , ahol az élelmiszerkészleteinket tároltuk. Most a Shark által megnevezett árakon kell megvennünk a készleteket. Úgy tûnik, hogy már járt abban a raktárban\nChad Kapper volt Shark hajóskapitánya és a börtön egyik vezetôje. Layton Dexter volt Shark elsô tisztje, neki is van némi befolyása. Ôk hárman és kalózaik meghatározó erôt képviselnek az egész szigeten a Rivadókkal és a Narwhalokkal szemben.";
			link.l1 = "Miért akarta Chad Kapper, hogy megöljelek?";
			link.l1.go = "Chad_die_3";
		break;
		
		case "Chad_die_3":
			dialog.text = "Csád kapcsolatot létesített a narválokkal, az ellenségeinkkel. Az ô segítségükkel akarta megölni Sharkot, és átvenni a helyét. A Narwhals haragszik az admirálisra Alan Milrow, a volt vezetôjük halála miatt. Azt hiszik, hogy Shark a felelôs a haláláért, de tévednek. Tudom, ki tette. Chad volt. Én vagyok az egyetlen szemtanúja ennek a bûnténynek\nEzért nem engedhetett szabadon Chad, mégis félt, hogy nekem is baja esik. A kalózok rettenthetetlenek a csatákban, de nagyon babonásak. Ezért akart felhasználni téged. Chad és Narwhals megölte volna Sharkot, és Rivadost hibáztatta volna.";
			link.l1 = "Valóban? Mondd el, miért...";
			link.l1.go = "Chad_die_4";
		break;
		
		case "Chad_die_4":
			dialog.text = ""+pchar.name+", barátom, beszéljünk késôbb. Sietnünk kell, mielôtt Shark kalózai megjelennek. Kutassátok át Chad testét és vegyétek el a kulcsait. De elôbb nézd meg az íróasztalát, lehet, hogy érdekes papírok vannak ott\nMenj Shark Dodsonhoz, ôt a 'San Augustine', egy nagy hajóban találod, ami a többiektôl távol zuhant le, van egy híd, ami a 'Pluto'. nevû hajóról vezet hozzá, mondd el neki, hogy Chad árulást tervez, és mondd el, hogy a Narwhals áll az egész mögött, és nekünk, Rivadosoknak semmi közünk hozzá.\nÖrömmel adok neked minden információt, amire szükséged van errôl a szigetrôl, a klánomról és másokról, amint megérkezel a lakhelyünkre, a Védôre. Tûnjünk el innen!";
			link.l1 = "Rendben, Chimiset. Késôbb találkozunk a... 'Protector'. Menjünk innen!";
			link.l1.go = "Chad_die_5";
		break;
		
		case "Chad_die_5":
			dialog.text = "Még egy dolog. A hajóink, beleértve a 'Protector', is, csak idegenek számára engedélyezettek. Rivadosnak kell lenned, vagy ismerned kell a jelszót, hogy beléphess. Elmondanám, de az hetente változik, és én túl régóta vagyok itt, így nem tudom az aktív jelszót\n Elôször a 'San Augustine' t kell meglátogatnod. Elmondom a mieinknek, hogy ki vagy, amíg a Sharkkal beszélgetsz, várni fognak rád. De ne menj a 'Protector' most, elôbb beszélj Sharkkal, és hadd találkozzak elôbb az embereimmel, különben Rivados ellenséges lesz veled szemben.";
			link.l1 = "Értem. Elindulok San Augustine-ba 'Viszlát!";
			link.l1.go = "Chad_die_6";
		break;
		
		case "Chad_die_6":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Notsearchbody");
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			pchar.quest.LSC_LetterChad.win_condition.l1 = "item";
			pchar.quest.LSC_LetterChad.win_condition.l1.item = "letter_chad";
			pchar.quest.LSC_LetterChad.function = "LSC_LetterChad_Find";
			sld = characterFromId("SharkMush_17");
			sld.lifeday = 0;
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("SharkSold_1"+(i+3));
				sld.lifeday = 0;
			}
			AddSimpleRumourCityTip("Ha, azt mondják, hogy a Rivados klán barátja vagy. Ez érdekes. Gratulálok...", "LostShipsCity", 5, 1, "LSC", "");
			AddSimpleRumourCityTip("Azt mondják, hogy megmentetted a Rivados varázsló Chimiset a 'Tartarustól'. Most már szívesen látott vendég vagy a hajóikon.", "LostShipsCity", 5, 1, "LSC", "");
			AddSimpleRumourCityTip("Tehát te voltál az, aki kiszabadította Chimiset-et! Érdekes. Most már a Rivados barátja vagy, de a Narwhals ellensége. Nem tudom, hogy gratuláljak-e neked, vagy szimpatizáljak...", "LostShipsCity", 5, 1, "LSC", "");
		break;
		
		// вариант N
		case "prisoner":
			dialog.text = "Mit akarsz tôlem, idegen?";
			link.l1 = "A neved Chimiset, igaz?";
			link.l1.go = "prisoner_1";
		break;
		
		case "prisoner_1":
			dialog.text = "Igen, én vagyok. Van valami dolgod velem, vagy csak beszélgetni akarsz?";
			link.l1 = "Van egy kis megbeszélnivalóm. Az admirálistól, Shark Dodsontól jöttem ide. Parancsot hoztam, hogy szabadon engedjelek, de egy feltétellel: válaszolnod kell néhány kérdésemre.";
			link.l1.go = "prisoner_2";
		break;
		
		case "prisoner_2":
			dialog.text = "Dodson úgy döntött, hogy elenged? Örömmel hallom. Tegye fel a kérdéseit. Remélem, hogy nincs benne semmi trükk, különben hiábavaló lenne az izgalmam.";
			link.l1 = "Semmi trükk, csak a segítségére van szükségem. Mondd csak, Chimiset, van egy furcsa kôbálvány ezen a szigeten? Éjfélkor arannyá változik. Ne nézz ôrültnek...";
			link.l1.go = "Friend_2";
		break;
		
		case "prisoner_3":
			dialog.text = "Van még kérdésed?";
			link.l1 = "Igen, van. Ismer egy Fehér Fiú nevû embert?";
			link.l1.go = "prisoner_4";
		break;
		
		case "prisoner_4":
			dialog.text = "Fehér fiú? Persze, ismerem ôt. Ez Olle Christiansen, a helyi idióta beceneve. Ô már felnôtt, és nem néz ki többé fiúnak, bár az esze még mindig gyerekes.";
			link.l1 = "Valóban? Mondja, hol találom meg?";
			link.l1.go = "prisoner_5";
		break;
		
		case "prisoner_5":
			dialog.text = "Bárhol a városunkban. Gyakran megtaláljuk a boltban, a kocsmában vagy az utcán sétálva. Fehér haja van, fel fogod ismerni.";
			link.l1 = "Kitûnô! Még egy kérdés: találkozott itt egy Nathaniel Hawk nevû férfival? Biztosan felbukkant itt egy ideje, és lehet, hogy súlyos beteg.";
			link.l1.go = "prisoner_6";
		break;
		
		case "prisoner_6":
			dialog.text = "Ebben nem tudok segíteni, idegen. Nem ismerek ilyen nevû embert. Biztosíthatom, hogy nem a Rivados' hajón van, és nem is tartózkodhat a semleges területen. Bár ugyanezt nem mondhatom el a Narwhals' territóriumokról, Rivados nem látogatja ôket.";
			link.l1 = "Hát, azért köszönöm... Sokat segítettél nekem, Chimiset!";
			link.l1.go = "prisoner_7";
		break;
		
		case "prisoner_7":
			dialog.text = "Ennyi? Shark most már szabadon enged?";
			link.l1 = "Igen. Nincs más kérésem. Chad Kapper kiszabadít téged. Nos, nekem mennem kell...";
			link.l1.go = "prisoner_8";
		break;
		
		case "prisoner_8":
			dialog.text = "Hagyd abba! Várjatok... Gyere vissza.";
			link.l1 = "Van még valami, amit el akarsz mondani?";
			link.l1.go = "prisoner_9";
		break;
		
		case "prisoner_9":
			dialog.text = "Nem egészen... (leereszkedô hang) Látom, hogy nem Kapper emberei közé tartozik. Ne bízzon benne. Ô egy mocskos söpredék. Nemrég szenvtelenül megölte a fegyvertelen Alan Milrow-t egy széles karddal. Ô volt a Narwhal klán vezetôje. Nem láttam elôre, hogy ez lesz, Chad csak a cellája közelébe ment, és kivégezte ôt\Sôt, hallottam olyan pletykákat is, hogy az Admirális saját emberei terveznek merényletet elkövetni ellene. Mesélj errôl Sharknak. És mondd meg neki, hogy többet fogok mondani, ha szemtôl szembe beszélünk.";
			link.l1 = "Hm. Rendben, elmondom Dodsonnak. Viszlát!";
			link.l1.go = "prisoner_10";
		break;
		
		case "prisoner_10":
			DialogExit();
			sld = characterFromId("Capper");
			sld.quest.chimiset_talk = "true"; // разговор с Чимисетом состоялся
			if (!CheckAttribute(npchar, "quest.capper_talk")) chrDisableReloadToLocation = true;//закрыть локацию
			else chrDisableReloadToLocation = false;//открыть локацию
			sld = characterFromId("Dodson");
			sld.dialog.currentnode = "entrance_10"; // ноду Акуле
			LSC_SetWhiteBoy(); // поставим белого мальчика
			NextDiag.CurrentNode = "prisoner_11";
			AddQuestRecord("SharkHunt", "20");
		break;
		
		case "prisoner_11":
			dialog.text = "Menj Sharkhoz, és mondj el neki mindent, amit elmondtam. Eh, remélem hamarosan kinyitják ezt a ketrecet...";
			link.l1 = "Igen, igen, igen. Már úton vagyok.";
			link.l1.go = "exit";
			NextDiag.TempNode = "prisoner_11";
		break;
		
		//------------------------беседа на Протекторе, если был старт через Тартарус-----------------
		case "Friend":
			dialog.text = "Hát itt vagy, kedves barátom. Még egyszer köszönöm, hogy megmentettél és bíztál bennem, Kapper helyett. Ezeket az amuletteket adom neked jutalmul. Biztos vagyok benne, hogy hasznosnak fogod találni ôket.";
			link.l1 = "Köszönöm! Erre nem számítottam...";
			link.l1.go = "Friend_1";
		break;
		
		case "Friend_1":
			GiveItem2Character(pchar, "indian_1");
			GiveItem2Character(pchar, "indian_11");
			GiveItem2Character(pchar, "amulet_1");
			PlaySound("interface\important_item.wav");
			dialog.text = "És most már készen állok arra, hogy meghallgassalak. Kérdezni akartál tôlem valamit, igazam van?";
			link.l1 = "Igazad van, Chimiset. Szükségem van a segítségedre. Elôször is, tudnom kell, hogy van-e egy furcsa kôbálvány ezen a szigeten? Éjfélkor arannyá változik. Ne gondolja, hogy ôrült vagyok...";
			link.l1.go = "Friend_2";
		break;
		
		// нода пересечения
		case "Friend_2":
			dialog.text = "Igen, értem, mire gondolsz, barátom. A saját szememmel láttam az indiai istenek szobrát. Bár csak a hajnali nap sugarai alatt válik arannyá, a holdé nem... sokszor áldoztunk fel gonosz narválokat, és az isten mindet felfalt. De már nincs a szigeten.";
			link.l1 = "Hogyhogy nincs?! Azt mondod, hogy hirtelen eltûnt?!";
			link.l1.go = "Friend_3";
		break;
		
		case "Friend_3":
			dialog.text = "Nem egészen így. Ez a szobor a 'San Geronimo'. belsejében volt. Ez a hajó a szoborral együtt süllyedt el néhány évvel ezelôtt.";
			link.l1 = "Micsoda balszerencse! Úgy tûnik, most már lehetetlen elhagyni a szigetet... És hol volt az a hajó?";
			link.l1.go = "Friend_4";
		break;
		
		case "Friend_4":
			dialog.text = "Nem messze a narválok területeitôl, a 'Phoenix'. nevû hajó roncsainak közelében, jó idôben láthatod a tengerfenéken pihenô hajót.";
			link.l1 = "Ha! Tehát a zátonyon fekszik? Akkor oda tudok úszni...";
			link.l1.go = "Friend_5";
		break;
		
		case "Friend_5":
			dialog.text = "Nem lehet, barátom. Elôször is, túl mélyen van odalent, másodszor, sok óriásrák van ott. Darabokra tépnek, mielôtt elérnéd a 'San Geronimo'.San Geronimót.";
			link.l1 = "Hm. Rendben, átgondolom. Legalább azt tudom, hogy a szobor létezik, és ez a legfontosabb.";
			if (CheckAttribute(npchar, "quest.chimiset_die")) link.l1.go = "prisoner_3";
			else
			{	
				if (CheckAttribute(pchar, "questTemp.LSC.Mary")) link.l1.go = "freedom_1";
				else link.l1.go = "Friend_6";
			}
			AddQuestRecord("LSC", "4");
		break;
		// нода пересечения
		
		case "Friend_6":
			dialog.text = "Látom, hogy több kérdésed is van. Kérdezz nyugodtan, barátom.";
			link.l1 = "Shark Dodson megkért, hogy találjam meg Chad bûntársait. Találtam egy levelet Chad ládájában. Valami mesterlövészrôl és egy pisztolyról van benne szó. Úgy tûnik, hogy távolról akarják meggyilkolni Cápát. Van valami ötleted?";
			link.l1.go = "Friend_7";
		break;
		
		case "Friend_7":
			dialog.text = "Hm. Le fogják lôni az admirálist? Gondolkodnom kell... A helyzet az, hogy az admirális szinte soha nem hagyja el a rezidenciáját, és amikor mégis, fél tucat kalóz védi. De van egy szokása, késô esténként szeret a tat körül sétálgatni\nKét pozícióból lôhet egy mesterlövész az admirális rezidenciájára - a 'Santa Florentina' orrábólFuryés a árbocából 'Fury'. De egy mesterlövész mégsem lesz képes megölni az admirálist ezekbôl a pozíciókból, sasszemû mesterlövésznek kell lennie ahhoz, hogy ilyen lövést leadjon. Emellett kiváló puskára is szüksége lenne. Körbe kellene kérdezôsködnie a szigeten, hogy kiknek van hozzáférése ilyen lôfegyverekhez.";
			link.l1 = "Heh, úgy tûnik, igazad van, a levélben van valami fegyverrôl... Láttál valakit, akinek ilyen fegyvere van?";
			link.l1.go = "Friend_8";
		break;
		
		case "Friend_8":
			dialog.text = "Nem, még életemben nem láttam ilyen fegyvert. Kérdezd meg az embereket, talán valaki elmondja neked.";
			link.l1 = "Rendben... Mindenesetre, az információi értékesek, köszönöm! Nos, az utolsó kérdés, bár nem várom el, hogy válaszolj... Hallottál már a Fehér Fiúról?";
			link.l1.go = "Friend_9";
		break;
		
		case "Friend_9":
			dialog.text = "Fehér fiú? Persze, ismerem. Ez Olle Christiansen beceneve, a helyi idióta. Ô már felnôtt, és már nem néz ki fiúnak, bár az esze még mindig gyerekes.";
			link.l1 = "Valóban? Mondja meg, hol találom?";
			link.l1.go = "Friend_10";
		break;
		
		case "Friend_10":
			dialog.text = "Bárhol a városunkban. Gyakran megtalálható a boltban, a kocsmában vagy az utcán. Fehér haja van - biztosan felismered.";
			link.l1 = "Nagyszerû! Köszönöm, Chimiset, sokat segítettél nekem!";
			link.l1.go = "Friend_11";
		break;
		
		case "Friend_11":
			dialog.text = "Mindig szívesen segítek! Gyere el hozzám, ha lesz még kérdésed.";
			link.l1 = "Persze! Most mennem kell. Viszlát!";
			if (CheckAttribute(pchar, "questTemp.LSC.Mary")) link.l1.go = "freedom_2";
			else link.l1.go = "Friend_12";
		break;
		
		case "Friend_12":
			DialogExit();
			NextDiag.CurrentNode = "Chimiset_wait";
			LSC_SetWhiteBoy(); // ставим Белого Мальчика в магазин
			pchar.questTemp.Saga.SharkHunt = "search_mush_1"; // флаг на магазин - поиск мушкета
			AddQuestRecord("SharkHunt", "11");
		break;
		
		case "freedom":
			dialog.text = "És ott van az én kedves barátom, akinek a szabadságomat, sôt talán az életemet is köszönhetem. Köszönöm, hogy segítettél a testvéreimnek megmenteni engem attól a mocskos Kapper-tôl. Ezeket az amuletteket adom neked jutalmul. Biztos vagyok benne, hogy hasznosnak fogod találni ôket.";
			link.l1 = "Köszönöm! Erre nem számítottam...";
			link.l1.go = "Friend_1";
		break;
		
		case "freedom_1":
			dialog.text = "Kérsz még valamit, fehér barátom?";
			link.l1 = "Mondd csak, Chimiset, ismered a Fehér Fiút?";
			link.l1.go = "Friend_9";
		break;
		
		case "freedom_2":
			DialogExit();
			NextDiag.CurrentNode = "Chimiset_wait";
			LSC_SetWhiteBoy(); // ставим Белого Мальчика в магазин
		break;
		
		//--> информационный блок
		case "Chimiset_wait": // стал другом
			if (pchar.questTemp.LSC == "return" && !CheckAttribute(npchar, "quest.return_isl"))
			{
				dialog.text = "Ó! Fehér barátom "+pchar.name+"! Nem fulladtál meg? A szellemek megmentettek, tudom, hogy...";
				link.l1 = "Jól vagyok és élek, Chimiset. Szellemek? Talán igazad van, mindez Kukulcan miatt történt...";
				link.l1.go = "exit";
				npchar.quest.return_isl = "true";
				break;
			}
			dialog.text = "Mi szél hozott ide, jó barátom?";
			/*if (!CheckAttribute(npchar, "quest.story"))
			{
				link.l1 = "Mondd el, hogyan halt meg a narválok vezetôje. Te voltál az egyetlen, aki látta.";
				link.l1.go = "story";
			}*/
			if (!CheckAttribute(npchar, "quest.crab"))
			{
				link.l2 = "Említetted a rákokat az alján a 'San GeronimoSan Geronimo közelében'. Le tudnád írni ezeket a szörnyeket?";
				link.l2.go = "crab";
			}
			link.l9 = "Semmi különös, Chimiset. Csak látni akartalak.";
			link.l9.go = "exit";
			NextDiag.TempNode = "Chimiset_wait";
		break;
		
		case "story":
			dialog.text = "Alan Milrow halálának történetét itt fogjuk megírni.";
			link.l1 = "Rendben!";
			link.l1.go = "exit";
			npchar.quest.story = "true";
			NextDiag.TempNode = "Chimiset_wait";
		break;
		
		case "crab":
			dialog.text = "Senki sem tudja, honnan jöttek, és miért értek el ilyen gigantikus méreteket. Nem sokat tudunk ezekrôl a vadállatokról. Léteznek, sokan látták ôket. Csoportosan, hajók között' roncsok között lehet ôket megtalálni sekély vizekben. A tenger fenekén leselkednek, halakra vadásznak, és megesznek minden szemetet, amit lerakunk\nEzek valódi fenyegetést jelentenek. Fogóik súlyos sebeket okozhatnak, állkapcsuk is veszélyes mérget bocsát ki, hasonlóan a tengeri halak mérgéhez. Ha megmérgezik és nem kezelik, az ember találkozik a teremtôvel. Szerencsére a méreg helyi gyógynövényekbôl készült ellenszerrel semlegesíthetô\nVolt közöttünk egy rákvadász. Ô hozta a húsukat, pokolian finom étel. De ami a legfontosabb: gyakran hozta ezeknek a szörnyeknek a karmát és a méreggel teli állkapcsát. ezek voltak a fô összetevôi néhány bájitalomnak. Kár, hogy már régen nem hozott nekem senki ilyesmit...";
			link.l1 = "És hol van most az a vadász?";
			link.l1.go = "crab_1";
		break;
		
		case "crab_1":
			dialog.text = "Fogadd meg a célzást. Fel kell készülnöd arra, hogy te magad is prédává válsz, miközben vadászol azokra a vadállatokra. Egy nap egyszerûen nem tért vissza. Ezért figyelmeztetlek titeket, hogy legyetek óvatosak és figyelmesek ezeknek a lényeknek a közelében.";
			link.l1 = "Értem...";
			link.l1.go = "exit";
			npchar.quest.crab = "true";
			NextDiag.TempNode = "Chimiset_wait";
		break;
		//<-- информационный блок
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}
